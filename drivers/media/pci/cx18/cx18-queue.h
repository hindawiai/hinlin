<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  cx18 buffer queues
 *
 *  Derived from ivtv-queue.h
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#घोषणा CX18_DMA_UNMAPPED	((u32) -1)

/* cx18_buffer utility functions */

अटल अंतरभूत व्योम cx18_buf_sync_क्रम_cpu(काष्ठा cx18_stream *s,
	काष्ठा cx18_buffer *buf)
अणु
	pci_dma_sync_single_क्रम_cpu(s->cx->pci_dev, buf->dma_handle,
				s->buf_size, s->dma);
पूर्ण

अटल अंतरभूत व्योम cx18_buf_sync_क्रम_device(काष्ठा cx18_stream *s,
	काष्ठा cx18_buffer *buf)
अणु
	pci_dma_sync_single_क्रम_device(s->cx->pci_dev, buf->dma_handle,
				s->buf_size, s->dma);
पूर्ण

व्योम _cx18_mdl_sync_क्रम_device(काष्ठा cx18_stream *s, काष्ठा cx18_mdl *mdl);

अटल अंतरभूत व्योम cx18_mdl_sync_क्रम_device(काष्ठा cx18_stream *s,
					    काष्ठा cx18_mdl *mdl)
अणु
	अगर (list_is_singular(&mdl->buf_list))
		cx18_buf_sync_क्रम_device(s, list_first_entry(&mdl->buf_list,
							     काष्ठा cx18_buffer,
							     list));
	अन्यथा
		_cx18_mdl_sync_क्रम_device(s, mdl);
पूर्ण

व्योम cx18_buf_swap(काष्ठा cx18_buffer *buf);
व्योम _cx18_mdl_swap(काष्ठा cx18_mdl *mdl);

अटल अंतरभूत व्योम cx18_mdl_swap(काष्ठा cx18_mdl *mdl)
अणु
	अगर (list_is_singular(&mdl->buf_list))
		cx18_buf_swap(list_first_entry(&mdl->buf_list,
					       काष्ठा cx18_buffer, list));
	अन्यथा
		_cx18_mdl_swap(mdl);
पूर्ण

/* cx18_queue utility functions */
काष्ठा cx18_queue *_cx18_enqueue(काष्ठा cx18_stream *s, काष्ठा cx18_mdl *mdl,
				 काष्ठा cx18_queue *q, पूर्णांक to_front);

अटल अंतरभूत
काष्ठा cx18_queue *cx18_enqueue(काष्ठा cx18_stream *s, काष्ठा cx18_mdl *mdl,
				काष्ठा cx18_queue *q)
अणु
	वापस _cx18_enqueue(s, mdl, q, 0); /* FIFO */
पूर्ण

अटल अंतरभूत
काष्ठा cx18_queue *cx18_push(काष्ठा cx18_stream *s, काष्ठा cx18_mdl *mdl,
			     काष्ठा cx18_queue *q)
अणु
	वापस _cx18_enqueue(s, mdl, q, 1); /* LIFO */
पूर्ण

व्योम cx18_queue_init(काष्ठा cx18_queue *q);
काष्ठा cx18_mdl *cx18_dequeue(काष्ठा cx18_stream *s, काष्ठा cx18_queue *q);
काष्ठा cx18_mdl *cx18_queue_get_mdl(काष्ठा cx18_stream *s, u32 id,
	u32 bytesused);
व्योम cx18_flush_queues(काष्ठा cx18_stream *s);

/* queue MDL reconfiguration helpers */
व्योम cx18_unload_queues(काष्ठा cx18_stream *s);
व्योम cx18_load_queues(काष्ठा cx18_stream *s);

/* cx18_stream utility functions */
पूर्णांक cx18_stream_alloc(काष्ठा cx18_stream *s);
व्योम cx18_stream_मुक्त(काष्ठा cx18_stream *s);
