<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    buffer queues.
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2004  Chris Kennedy <c@groovy.org>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-queue.h"

पूर्णांक ivtv_buf_copy_from_user(काष्ठा ivtv_stream *s, काष्ठा ivtv_buffer *buf, स्थिर अक्षर __user *src, पूर्णांक copybytes)
अणु
	अगर (s->buf_size - buf->bytesused < copybytes)
		copybytes = s->buf_size - buf->bytesused;
	अगर (copy_from_user(buf->buf + buf->bytesused, src, copybytes)) अणु
		वापस -EFAULT;
	पूर्ण
	buf->bytesused += copybytes;
	वापस copybytes;
पूर्ण

व्योम ivtv_buf_swap(काष्ठा ivtv_buffer *buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < buf->bytesused; i += 4)
		swab32s((u32 *)(buf->buf + i));
पूर्ण

व्योम ivtv_queue_init(काष्ठा ivtv_queue *q)
अणु
	INIT_LIST_HEAD(&q->list);
	q->buffers = 0;
	q->length = 0;
	q->bytesused = 0;
पूर्ण

व्योम ivtv_enqueue(काष्ठा ivtv_stream *s, काष्ठा ivtv_buffer *buf, काष्ठा ivtv_queue *q)
अणु
	अचिन्हित दीर्घ flags;

	/* clear the buffer अगर it is going to be enqueued to the मुक्त queue */
	अगर (q == &s->q_मुक्त) अणु
		buf->bytesused = 0;
		buf->पढ़ोpos = 0;
		buf->b_flags = 0;
		buf->dma_xfer_cnt = 0;
	पूर्ण
	spin_lock_irqsave(&s->qlock, flags);
	list_add_tail(&buf->list, &q->list);
	q->buffers++;
	q->length += s->buf_size;
	q->bytesused += buf->bytesused - buf->पढ़ोpos;
	spin_unlock_irqrestore(&s->qlock, flags);
पूर्ण

काष्ठा ivtv_buffer *ivtv_dequeue(काष्ठा ivtv_stream *s, काष्ठा ivtv_queue *q)
अणु
	काष्ठा ivtv_buffer *buf = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->qlock, flags);
	अगर (!list_empty(&q->list)) अणु
		buf = list_entry(q->list.next, काष्ठा ivtv_buffer, list);
		list_del_init(q->list.next);
		q->buffers--;
		q->length -= s->buf_size;
		q->bytesused -= buf->bytesused - buf->पढ़ोpos;
	पूर्ण
	spin_unlock_irqrestore(&s->qlock, flags);
	वापस buf;
पूर्ण

अटल व्योम ivtv_queue_move_buf(काष्ठा ivtv_stream *s, काष्ठा ivtv_queue *from,
		काष्ठा ivtv_queue *to, पूर्णांक clear)
अणु
	काष्ठा ivtv_buffer *buf = list_entry(from->list.next, काष्ठा ivtv_buffer, list);

	list_move_tail(from->list.next, &to->list);
	from->buffers--;
	from->length -= s->buf_size;
	from->bytesused -= buf->bytesused - buf->पढ़ोpos;
	/* special handling क्रम q_मुक्त */
	अगर (clear)
		buf->bytesused = buf->पढ़ोpos = buf->b_flags = buf->dma_xfer_cnt = 0;
	to->buffers++;
	to->length += s->buf_size;
	to->bytesused += buf->bytesused - buf->पढ़ोpos;
पूर्ण

/* Move 'needed_bytes' worth of buffers from queue 'from' into queue 'to'.
   If 'needed_bytes' == 0, then move all buffers from 'from' into 'to'.
   If 'steal' != शून्य, then buffers may also taken from that queue अगर
   needed, but only अगर 'from' is the मुक्त queue.

   The buffer is स्वतःmatically cleared अगर it goes to the मुक्त queue. It is
   also cleared अगर buffers need to be taken from the 'steal' queue and
   the 'from' queue is the मुक्त queue.

   When 'from' is q_मुक्त, then needed_bytes is compared to the total
   available buffer length, otherwise needed_bytes is compared to the
   bytesused value. For the 'steal' queue the total available buffer
   length is always used.

   -ENOMEM is वापसed अगर the buffers could not be obtained, 0 अगर all
   buffers where obtained from the 'from' list and अगर non-zero then
   the number of stolen buffers is वापसed. */
पूर्णांक ivtv_queue_move(काष्ठा ivtv_stream *s, काष्ठा ivtv_queue *from, काष्ठा ivtv_queue *steal,
		    काष्ठा ivtv_queue *to, पूर्णांक needed_bytes)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;
	पूर्णांक from_मुक्त = from == &s->q_मुक्त;
	पूर्णांक to_मुक्त = to == &s->q_मुक्त;
	पूर्णांक bytes_available, bytes_steal;

	spin_lock_irqsave(&s->qlock, flags);
	अगर (needed_bytes == 0) अणु
		from_मुक्त = 1;
		needed_bytes = from->length;
	पूर्ण

	bytes_available = from_मुक्त ? from->length : from->bytesused;
	bytes_steal = (from_मुक्त && steal) ? steal->length : 0;

	अगर (bytes_available + bytes_steal < needed_bytes) अणु
		spin_unlock_irqrestore(&s->qlock, flags);
		वापस -ENOMEM;
	पूर्ण
	जबतक (steal && bytes_available < needed_bytes) अणु
		काष्ठा ivtv_buffer *buf = list_entry(steal->list.prev, काष्ठा ivtv_buffer, list);
		u16 dma_xfer_cnt = buf->dma_xfer_cnt;

		/* move buffers from the tail of the 'steal' queue to the tail of the
		   'from' queue. Always copy all the buffers with the same dma_xfer_cnt
		   value, this ensures that you करो not end up with partial frame data
		   अगर one frame is stored in multiple buffers. */
		जबतक (dma_xfer_cnt == buf->dma_xfer_cnt) अणु
			list_move_tail(steal->list.prev, &from->list);
			rc++;
			steal->buffers--;
			steal->length -= s->buf_size;
			steal->bytesused -= buf->bytesused - buf->पढ़ोpos;
			buf->bytesused = buf->पढ़ोpos = buf->b_flags = buf->dma_xfer_cnt = 0;
			from->buffers++;
			from->length += s->buf_size;
			bytes_available += s->buf_size;
			अगर (list_empty(&steal->list))
				अवरोध;
			buf = list_entry(steal->list.prev, काष्ठा ivtv_buffer, list);
		पूर्ण
	पूर्ण
	अगर (from_मुक्त) अणु
		u32 old_length = to->length;

		जबतक (to->length - old_length < needed_bytes) अणु
			ivtv_queue_move_buf(s, from, to, 1);
		पूर्ण
	पूर्ण
	अन्यथा अणु
		u32 old_bytesused = to->bytesused;

		जबतक (to->bytesused - old_bytesused < needed_bytes) अणु
			ivtv_queue_move_buf(s, from, to, to_मुक्त);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&s->qlock, flags);
	वापस rc;
पूर्ण

व्योम ivtv_flush_queues(काष्ठा ivtv_stream *s)
अणु
	ivtv_queue_move(s, &s->q_io, शून्य, &s->q_मुक्त, 0);
	ivtv_queue_move(s, &s->q_full, शून्य, &s->q_मुक्त, 0);
	ivtv_queue_move(s, &s->q_dma, शून्य, &s->q_मुक्त, 0);
	ivtv_queue_move(s, &s->q_predma, शून्य, &s->q_मुक्त, 0);
पूर्ण

पूर्णांक ivtv_stream_alloc(काष्ठा ivtv_stream *s)
अणु
	काष्ठा ivtv *itv = s->itv;
	पूर्णांक SGsize = माप(काष्ठा ivtv_sg_host_element) * s->buffers;
	पूर्णांक i;

	अगर (s->buffers == 0)
		वापस 0;

	IVTV_DEBUG_INFO("Allocate %s%s stream: %d x %d buffers (%dkB total)\n",
		s->dma != PCI_DMA_NONE ? "DMA " : "",
		s->name, s->buffers, s->buf_size, s->buffers * s->buf_size / 1024);

	s->sg_pending = kzalloc(SGsize, GFP_KERNEL|__GFP_NOWARN);
	अगर (s->sg_pending == शून्य) अणु
		IVTV_ERR("Could not allocate sg_pending for %s stream\n", s->name);
		वापस -ENOMEM;
	पूर्ण
	s->sg_pending_size = 0;

	s->sg_processing = kzalloc(SGsize, GFP_KERNEL|__GFP_NOWARN);
	अगर (s->sg_processing == शून्य) अणु
		IVTV_ERR("Could not allocate sg_processing for %s stream\n", s->name);
		kमुक्त(s->sg_pending);
		s->sg_pending = शून्य;
		वापस -ENOMEM;
	पूर्ण
	s->sg_processing_size = 0;

	s->sg_dma = kzalloc(माप(काष्ठा ivtv_sg_element),
					GFP_KERNEL|__GFP_NOWARN);
	अगर (s->sg_dma == शून्य) अणु
		IVTV_ERR("Could not allocate sg_dma for %s stream\n", s->name);
		kमुक्त(s->sg_pending);
		s->sg_pending = शून्य;
		kमुक्त(s->sg_processing);
		s->sg_processing = शून्य;
		वापस -ENOMEM;
	पूर्ण
	अगर (ivtv_might_use_dma(s)) अणु
		s->sg_handle = pci_map_single(itv->pdev, s->sg_dma,
				माप(काष्ठा ivtv_sg_element), PCI_DMA_TODEVICE);
		ivtv_stream_sync_क्रम_cpu(s);
	पूर्ण

	/* allocate stream buffers. Initially all buffers are in q_मुक्त. */
	क्रम (i = 0; i < s->buffers; i++) अणु
		काष्ठा ivtv_buffer *buf = kzalloc(माप(काष्ठा ivtv_buffer),
						GFP_KERNEL|__GFP_NOWARN);

		अगर (buf == शून्य)
			अवरोध;
		buf->buf = kदो_स्मृति(s->buf_size + 256, GFP_KERNEL|__GFP_NOWARN);
		अगर (buf->buf == शून्य) अणु
			kमुक्त(buf);
			अवरोध;
		पूर्ण
		INIT_LIST_HEAD(&buf->list);
		अगर (ivtv_might_use_dma(s)) अणु
			buf->dma_handle = pci_map_single(s->itv->pdev,
				buf->buf, s->buf_size + 256, s->dma);
			ivtv_buf_sync_क्रम_cpu(s, buf);
		पूर्ण
		ivtv_enqueue(s, buf, &s->q_मुक्त);
	पूर्ण
	अगर (i == s->buffers)
		वापस 0;
	IVTV_ERR("Couldn't allocate buffers for %s stream\n", s->name);
	ivtv_stream_मुक्त(s);
	वापस -ENOMEM;
पूर्ण

व्योम ivtv_stream_मुक्त(काष्ठा ivtv_stream *s)
अणु
	काष्ठा ivtv_buffer *buf;

	/* move all buffers to q_मुक्त */
	ivtv_flush_queues(s);

	/* empty q_मुक्त */
	जबतक ((buf = ivtv_dequeue(s, &s->q_मुक्त))) अणु
		अगर (ivtv_might_use_dma(s))
			pci_unmap_single(s->itv->pdev, buf->dma_handle,
				s->buf_size + 256, s->dma);
		kमुक्त(buf->buf);
		kमुक्त(buf);
	पूर्ण

	/* Free SG Array/Lists */
	अगर (s->sg_dma != शून्य) अणु
		अगर (s->sg_handle != IVTV_DMA_UNMAPPED) अणु
			pci_unmap_single(s->itv->pdev, s->sg_handle,
				 माप(काष्ठा ivtv_sg_element), PCI_DMA_TODEVICE);
			s->sg_handle = IVTV_DMA_UNMAPPED;
		पूर्ण
		kमुक्त(s->sg_pending);
		kमुक्त(s->sg_processing);
		kमुक्त(s->sg_dma);
		s->sg_pending = शून्य;
		s->sg_processing = शून्य;
		s->sg_dma = शून्य;
		s->sg_pending_size = 0;
		s->sg_processing_size = 0;
	पूर्ण
पूर्ण
