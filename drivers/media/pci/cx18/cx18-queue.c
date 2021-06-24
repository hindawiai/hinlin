<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 buffer queues
 *
 *  Derived from ivtv-queue.c
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx18-driver.h"
#समावेश "cx18-queue.h"
#समावेश "cx18-streams.h"
#समावेश "cx18-scb.h"
#समावेश "cx18-io.h"

व्योम cx18_buf_swap(काष्ठा cx18_buffer *buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < buf->bytesused; i += 4)
		swab32s((u32 *)(buf->buf + i));
पूर्ण

व्योम _cx18_mdl_swap(काष्ठा cx18_mdl *mdl)
अणु
	काष्ठा cx18_buffer *buf;

	list_क्रम_each_entry(buf, &mdl->buf_list, list) अणु
		अगर (buf->bytesused == 0)
			अवरोध;
		cx18_buf_swap(buf);
	पूर्ण
पूर्ण

व्योम cx18_queue_init(काष्ठा cx18_queue *q)
अणु
	INIT_LIST_HEAD(&q->list);
	atomic_set(&q->depth, 0);
	q->bytesused = 0;
पूर्ण

काष्ठा cx18_queue *_cx18_enqueue(काष्ठा cx18_stream *s, काष्ठा cx18_mdl *mdl,
				 काष्ठा cx18_queue *q, पूर्णांक to_front)
अणु
	/* clear the mdl अगर it is not to be enqueued to the full queue */
	अगर (q != &s->q_full) अणु
		mdl->bytesused = 0;
		mdl->पढ़ोpos = 0;
		mdl->m_flags = 0;
		mdl->skipped = 0;
		mdl->curr_buf = शून्य;
	पूर्ण

	/* q_busy is restricted to a max buffer count imposed by firmware */
	अगर (q == &s->q_busy &&
	    atomic_पढ़ो(&q->depth) >= CX18_MAX_FW_MDLS_PER_STREAM)
		q = &s->q_मुक्त;

	spin_lock(&q->lock);

	अगर (to_front)
		list_add(&mdl->list, &q->list); /* LIFO */
	अन्यथा
		list_add_tail(&mdl->list, &q->list); /* FIFO */
	q->bytesused += mdl->bytesused - mdl->पढ़ोpos;
	atomic_inc(&q->depth);

	spin_unlock(&q->lock);
	वापस q;
पूर्ण

काष्ठा cx18_mdl *cx18_dequeue(काष्ठा cx18_stream *s, काष्ठा cx18_queue *q)
अणु
	काष्ठा cx18_mdl *mdl = शून्य;

	spin_lock(&q->lock);
	अगर (!list_empty(&q->list)) अणु
		mdl = list_first_entry(&q->list, काष्ठा cx18_mdl, list);
		list_del_init(&mdl->list);
		q->bytesused -= mdl->bytesused - mdl->पढ़ोpos;
		mdl->skipped = 0;
		atomic_dec(&q->depth);
	पूर्ण
	spin_unlock(&q->lock);
	वापस mdl;
पूर्ण

अटल व्योम _cx18_mdl_update_bufs_क्रम_cpu(काष्ठा cx18_stream *s,
					  काष्ठा cx18_mdl *mdl)
अणु
	काष्ठा cx18_buffer *buf;
	u32 buf_size = s->buf_size;
	u32 bytesused = mdl->bytesused;

	list_क्रम_each_entry(buf, &mdl->buf_list, list) अणु
		buf->पढ़ोpos = 0;
		अगर (bytesused >= buf_size) अणु
			buf->bytesused = buf_size;
			bytesused -= buf_size;
		पूर्ण अन्यथा अणु
			buf->bytesused = bytesused;
			bytesused = 0;
		पूर्ण
		cx18_buf_sync_क्रम_cpu(s, buf);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cx18_mdl_update_bufs_क्रम_cpu(काष्ठा cx18_stream *s,
						काष्ठा cx18_mdl *mdl)
अणु
	काष्ठा cx18_buffer *buf;

	अगर (list_is_singular(&mdl->buf_list)) अणु
		buf = list_first_entry(&mdl->buf_list, काष्ठा cx18_buffer,
				       list);
		buf->bytesused = mdl->bytesused;
		buf->पढ़ोpos = 0;
		cx18_buf_sync_क्रम_cpu(s, buf);
	पूर्ण अन्यथा अणु
		_cx18_mdl_update_bufs_क्रम_cpu(s, mdl);
	पूर्ण
पूर्ण

काष्ठा cx18_mdl *cx18_queue_get_mdl(काष्ठा cx18_stream *s, u32 id,
	u32 bytesused)
अणु
	काष्ठा cx18 *cx = s->cx;
	काष्ठा cx18_mdl *mdl;
	काष्ठा cx18_mdl *पंचांगp;
	काष्ठा cx18_mdl *ret = शून्य;
	LIST_HEAD(sweep_up);

	/*
	 * We करोn't have to acquire multiple q locks here, because we are
	 * serialized by the single thपढ़ोed work handler.
	 * MDLs from the firmware will thus reमुख्य in order as
	 * they are moved from q_busy to q_full or to the dvb ring buffer.
	 */
	spin_lock(&s->q_busy.lock);
	list_क्रम_each_entry_safe(mdl, पंचांगp, &s->q_busy.list, list) अणु
		/*
		 * We should find what the firmware told us is करोne,
		 * right at the front of the queue.  If we करोn't, we likely have
		 * missed an mdl करोne message from the firmware.
		 * Once we skip an mdl repeatedly, relative to the size of
		 * q_busy, we have high confidence we've missed it.
		 */
		अगर (mdl->id != id) अणु
			mdl->skipped++;
			अगर (mdl->skipped >= atomic_पढ़ो(&s->q_busy.depth)-1) अणु
				/* mdl must have fallen out of rotation */
				CX18_WARN("Skipped %s, MDL %d, %d times - it must have dropped out of rotation\n",
					  s->name, mdl->id,
					  mdl->skipped);
				/* Sweep it up to put it back पूर्णांकo rotation */
				list_move_tail(&mdl->list, &sweep_up);
				atomic_dec(&s->q_busy.depth);
			पूर्ण
			जारी;
		पूर्ण
		/*
		 * We pull the desired mdl off of the queue here.  Something
		 * will have to put it back on a queue later.
		 */
		list_del_init(&mdl->list);
		atomic_dec(&s->q_busy.depth);
		ret = mdl;
		अवरोध;
	पूर्ण
	spin_unlock(&s->q_busy.lock);

	/*
	 * We found the mdl क्रम which we were looking.  Get it पढ़ोy क्रम
	 * the caller to put on q_full or in the dvb ring buffer.
	 */
	अगर (ret != शून्य) अणु
		ret->bytesused = bytesused;
		ret->skipped = 0;
		/* 0'ed पढ़ोpos, m_flags & curr_buf when mdl went on q_busy */
		cx18_mdl_update_bufs_क्रम_cpu(s, ret);
		अगर (s->type != CX18_ENC_STREAM_TYPE_TS)
			set_bit(CX18_F_M_NEED_SWAP, &ret->m_flags);
	पूर्ण

	/* Put any mdls the firmware is ignoring back पूर्णांकo normal rotation */
	list_क्रम_each_entry_safe(mdl, पंचांगp, &sweep_up, list) अणु
		list_del_init(&mdl->list);
		cx18_enqueue(s, mdl, &s->q_मुक्त);
	पूर्ण
	वापस ret;
पूर्ण

/* Move all mdls of a queue, जबतक flushing the mdl */
अटल व्योम cx18_queue_flush(काष्ठा cx18_stream *s,
			     काष्ठा cx18_queue *q_src, काष्ठा cx18_queue *q_dst)
अणु
	काष्ठा cx18_mdl *mdl;

	/* It only makes sense to flush to q_मुक्त or q_idle */
	अगर (q_src == q_dst || q_dst == &s->q_full || q_dst == &s->q_busy)
		वापस;

	spin_lock(&q_src->lock);
	spin_lock(&q_dst->lock);
	जबतक (!list_empty(&q_src->list)) अणु
		mdl = list_first_entry(&q_src->list, काष्ठा cx18_mdl, list);
		list_move_tail(&mdl->list, &q_dst->list);
		mdl->bytesused = 0;
		mdl->पढ़ोpos = 0;
		mdl->m_flags = 0;
		mdl->skipped = 0;
		mdl->curr_buf = शून्य;
		atomic_inc(&q_dst->depth);
	पूर्ण
	cx18_queue_init(q_src);
	spin_unlock(&q_src->lock);
	spin_unlock(&q_dst->lock);
पूर्ण

व्योम cx18_flush_queues(काष्ठा cx18_stream *s)
अणु
	cx18_queue_flush(s, &s->q_busy, &s->q_मुक्त);
	cx18_queue_flush(s, &s->q_full, &s->q_मुक्त);
पूर्ण

/*
 * Note, s->buf_pool is not रक्षित by a lock,
 * the stream better not have *anything* going on when calling this
 */
व्योम cx18_unload_queues(काष्ठा cx18_stream *s)
अणु
	काष्ठा cx18_queue *q_idle = &s->q_idle;
	काष्ठा cx18_mdl *mdl;
	काष्ठा cx18_buffer *buf;

	/* Move all MDLS to q_idle */
	cx18_queue_flush(s, &s->q_busy, q_idle);
	cx18_queue_flush(s, &s->q_full, q_idle);
	cx18_queue_flush(s, &s->q_मुक्त, q_idle);

	/* Reset MDL id's and move all buffers back to the stream's buf_pool */
	spin_lock(&q_idle->lock);
	list_क्रम_each_entry(mdl, &q_idle->list, list) अणु
		जबतक (!list_empty(&mdl->buf_list)) अणु
			buf = list_first_entry(&mdl->buf_list,
					       काष्ठा cx18_buffer, list);
			list_move_tail(&buf->list, &s->buf_pool);
			buf->bytesused = 0;
			buf->पढ़ोpos = 0;
		पूर्ण
		mdl->id = s->mdl_base_idx; /* reset id to a "safe" value */
		/* all other mdl fields were cleared by cx18_queue_flush() */
	पूर्ण
	spin_unlock(&q_idle->lock);
पूर्ण

/*
 * Note, s->buf_pool is not रक्षित by a lock,
 * the stream better not have *anything* going on when calling this
 */
व्योम cx18_load_queues(काष्ठा cx18_stream *s)
अणु
	काष्ठा cx18 *cx = s->cx;
	काष्ठा cx18_mdl *mdl;
	काष्ठा cx18_buffer *buf;
	पूर्णांक mdl_id;
	पूर्णांक i;
	u32 partial_buf_size;

	/*
	 * Attach buffers to MDLs, give the MDLs ids, and add MDLs to q_मुक्त
	 * Excess MDLs are left on q_idle
	 * Excess buffers are left in buf_pool and/or on an MDL in q_idle
	 */
	mdl_id = s->mdl_base_idx;
	क्रम (mdl = cx18_dequeue(s, &s->q_idle), i = s->bufs_per_mdl;
	     mdl != शून्य && i == s->bufs_per_mdl;
	     mdl = cx18_dequeue(s, &s->q_idle)) अणु

		mdl->id = mdl_id;

		क्रम (i = 0; i < s->bufs_per_mdl; i++) अणु
			अगर (list_empty(&s->buf_pool))
				अवरोध;

			buf = list_first_entry(&s->buf_pool, काष्ठा cx18_buffer,
					       list);
			list_move_tail(&buf->list, &mdl->buf_list);

			/* update the firmware's MDL array with this buffer */
			cx18_ग_लिखोl(cx, buf->dma_handle,
				    &cx->scb->cpu_mdl[mdl_id + i].paddr);
			cx18_ग_लिखोl(cx, s->buf_size,
				    &cx->scb->cpu_mdl[mdl_id + i].length);
		पूर्ण

		अगर (i == s->bufs_per_mdl) अणु
			/*
			 * The encoder करोesn't honor s->mdl_size.  So in the
			 * हाल of a non-पूर्णांकegral number of buffers to meet
			 * mdl_size, we lie about the size of the last buffer
			 * in the MDL to get the encoder to really only send
			 * us mdl_size bytes per MDL transfer.
			 */
			partial_buf_size = s->mdl_size % s->buf_size;
			अगर (partial_buf_size) अणु
				cx18_ग_लिखोl(cx, partial_buf_size,
				      &cx->scb->cpu_mdl[mdl_id + i - 1].length);
			पूर्ण
			cx18_enqueue(s, mdl, &s->q_मुक्त);
		पूर्ण अन्यथा अणु
			/* Not enough buffers क्रम this MDL; we won't use it */
			cx18_push(s, mdl, &s->q_idle);
		पूर्ण
		mdl_id += i;
	पूर्ण
पूर्ण

व्योम _cx18_mdl_sync_क्रम_device(काष्ठा cx18_stream *s, काष्ठा cx18_mdl *mdl)
अणु
	पूर्णांक dma = s->dma;
	u32 buf_size = s->buf_size;
	काष्ठा pci_dev *pci_dev = s->cx->pci_dev;
	काष्ठा cx18_buffer *buf;

	list_क्रम_each_entry(buf, &mdl->buf_list, list)
		pci_dma_sync_single_क्रम_device(pci_dev, buf->dma_handle,
					       buf_size, dma);
पूर्ण

पूर्णांक cx18_stream_alloc(काष्ठा cx18_stream *s)
अणु
	काष्ठा cx18 *cx = s->cx;
	पूर्णांक i;

	अगर (s->buffers == 0)
		वापस 0;

	CX18_DEBUG_INFO("Allocate %s stream: %d x %d buffers (%d.%02d kB total)\n",
		s->name, s->buffers, s->buf_size,
		s->buffers * s->buf_size / 1024,
		(s->buffers * s->buf_size * 100 / 1024) % 100);

	अगर (((अक्षर __iomem *)&cx->scb->cpu_mdl[cx->मुक्त_mdl_idx + s->buffers] -
				(अक्षर __iomem *)cx->scb) > SCB_RESERVED_SIZE) अणु
		अचिन्हित bufsz = (((अक्षर __iomem *)cx->scb) + SCB_RESERVED_SIZE -
					((अक्षर __iomem *)cx->scb->cpu_mdl));

		CX18_ERR("Too many buffers, cannot fit in SCB area\n");
		CX18_ERR("Max buffers = %zu\n",
			bufsz / माप(काष्ठा cx18_mdl_ent));
		वापस -ENOMEM;
	पूर्ण

	s->mdl_base_idx = cx->मुक्त_mdl_idx;

	/* allocate stream buffers and MDLs */
	क्रम (i = 0; i < s->buffers; i++) अणु
		काष्ठा cx18_mdl *mdl;
		काष्ठा cx18_buffer *buf;

		/* 1 MDL per buffer to handle the worst & also शेष हाल */
		mdl = kzalloc(माप(काष्ठा cx18_mdl), GFP_KERNEL|__GFP_NOWARN);
		अगर (mdl == शून्य)
			अवरोध;

		buf = kzalloc(माप(काष्ठा cx18_buffer),
				GFP_KERNEL|__GFP_NOWARN);
		अगर (buf == शून्य) अणु
			kमुक्त(mdl);
			अवरोध;
		पूर्ण

		buf->buf = kदो_स्मृति(s->buf_size, GFP_KERNEL|__GFP_NOWARN);
		अगर (buf->buf == शून्य) अणु
			kमुक्त(mdl);
			kमुक्त(buf);
			अवरोध;
		पूर्ण

		INIT_LIST_HEAD(&mdl->list);
		INIT_LIST_HEAD(&mdl->buf_list);
		mdl->id = s->mdl_base_idx; /* a somewhat safe value */
		cx18_enqueue(s, mdl, &s->q_idle);

		INIT_LIST_HEAD(&buf->list);
		buf->dma_handle = pci_map_single(s->cx->pci_dev,
				buf->buf, s->buf_size, s->dma);
		cx18_buf_sync_क्रम_cpu(s, buf);
		list_add_tail(&buf->list, &s->buf_pool);
	पूर्ण
	अगर (i == s->buffers) अणु
		cx->मुक्त_mdl_idx += s->buffers;
		वापस 0;
	पूर्ण
	CX18_ERR("Couldn't allocate buffers for %s stream\n", s->name);
	cx18_stream_मुक्त(s);
	वापस -ENOMEM;
पूर्ण

व्योम cx18_stream_मुक्त(काष्ठा cx18_stream *s)
अणु
	काष्ठा cx18_mdl *mdl;
	काष्ठा cx18_buffer *buf;
	काष्ठा cx18 *cx = s->cx;

	CX18_DEBUG_INFO("Deallocating buffers for %s stream\n", s->name);

	/* move all buffers to buf_pool and all MDLs to q_idle */
	cx18_unload_queues(s);

	/* empty q_idle */
	जबतक ((mdl = cx18_dequeue(s, &s->q_idle)))
		kमुक्त(mdl);

	/* empty buf_pool */
	जबतक (!list_empty(&s->buf_pool)) अणु
		buf = list_first_entry(&s->buf_pool, काष्ठा cx18_buffer, list);
		list_del_init(&buf->list);

		pci_unmap_single(s->cx->pci_dev, buf->dma_handle,
				s->buf_size, s->dma);
		kमुक्त(buf->buf);
		kमुक्त(buf);
	पूर्ण
पूर्ण
