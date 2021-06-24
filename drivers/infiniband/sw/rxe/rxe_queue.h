<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#अगर_अघोषित RXE_QUEUE_H
#घोषणा RXE_QUEUE_H

/* क्रम definition of shared काष्ठा rxe_queue_buf */
#समावेश <uapi/rdma/rdma_user_rxe.h>

/* implements a simple circular buffer that can optionally be
 * shared between user space and the kernel and can be resized
 * the requested element size is rounded up to a घातer of 2
 * and the number of elements in the buffer is also rounded
 * up to a घातer of 2. Since the queue is empty when the
 * producer and consumer indices match the maximum capacity
 * of the queue is one less than the number of element slots
 */

काष्ठा rxe_queue अणु
	काष्ठा rxe_dev		*rxe;
	काष्ठा rxe_queue_buf	*buf;
	काष्ठा rxe_mmap_info	*ip;
	माप_प्रकार			buf_size;
	माप_प्रकार			elem_size;
	अचिन्हित पूर्णांक		log2_elem_size;
	u32			index_mask;
पूर्ण;

पूर्णांक करो_mmap_info(काष्ठा rxe_dev *rxe, काष्ठा mminfo __user *outbuf,
		 काष्ठा ib_udata *udata, काष्ठा rxe_queue_buf *buf,
		 माप_प्रकार buf_size, काष्ठा rxe_mmap_info **ip_p);

व्योम rxe_queue_reset(काष्ठा rxe_queue *q);

काष्ठा rxe_queue *rxe_queue_init(काष्ठा rxe_dev *rxe,
				 पूर्णांक *num_elem,
				 अचिन्हित पूर्णांक elem_size);

पूर्णांक rxe_queue_resize(काष्ठा rxe_queue *q, अचिन्हित पूर्णांक *num_elem_p,
		     अचिन्हित पूर्णांक elem_size, काष्ठा ib_udata *udata,
		     काष्ठा mminfo __user *outbuf,
		     /* Protect producers जबतक resizing queue */
		     spinlock_t *producer_lock,
		     /* Protect consumers जबतक resizing queue */
		     spinlock_t *consumer_lock);

व्योम rxe_queue_cleanup(काष्ठा rxe_queue *queue);

अटल अंतरभूत पूर्णांक next_index(काष्ठा rxe_queue *q, पूर्णांक index)
अणु
	वापस (index + 1) & q->buf->index_mask;
पूर्ण

अटल अंतरभूत पूर्णांक queue_empty(काष्ठा rxe_queue *q)
अणु
	u32 prod;
	u32 cons;

	/* make sure all changes to queue complete beक्रमe
	 * testing queue empty
	 */
	prod = smp_load_acquire(&q->buf->producer_index);
	/* same */
	cons = smp_load_acquire(&q->buf->consumer_index);

	वापस ((prod - cons) & q->index_mask) == 0;
पूर्ण

अटल अंतरभूत पूर्णांक queue_full(काष्ठा rxe_queue *q)
अणु
	u32 prod;
	u32 cons;

	/* make sure all changes to queue complete beक्रमe
	 * testing queue full
	 */
	prod = smp_load_acquire(&q->buf->producer_index);
	/* same */
	cons = smp_load_acquire(&q->buf->consumer_index);

	वापस ((prod + 1 - cons) & q->index_mask) == 0;
पूर्ण

अटल अंतरभूत व्योम advance_producer(काष्ठा rxe_queue *q)
अणु
	u32 prod;

	prod = (q->buf->producer_index + 1) & q->index_mask;

	/* make sure all changes to queue complete beक्रमe
	 * changing producer index
	 */
	smp_store_release(&q->buf->producer_index, prod);
पूर्ण

अटल अंतरभूत व्योम advance_consumer(काष्ठा rxe_queue *q)
अणु
	u32 cons;

	cons = (q->buf->consumer_index + 1) & q->index_mask;

	/* make sure all changes to queue complete beक्रमe
	 * changing consumer index
	 */
	smp_store_release(&q->buf->consumer_index, cons);
पूर्ण

अटल अंतरभूत व्योम *producer_addr(काष्ठा rxe_queue *q)
अणु
	वापस q->buf->data + ((q->buf->producer_index & q->index_mask)
				<< q->log2_elem_size);
पूर्ण

अटल अंतरभूत व्योम *consumer_addr(काष्ठा rxe_queue *q)
अणु
	वापस q->buf->data + ((q->buf->consumer_index & q->index_mask)
				<< q->log2_elem_size);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक producer_index(काष्ठा rxe_queue *q)
अणु
	u32 index;

	/* make sure all changes to queue
	 * complete beक्रमe getting producer index
	 */
	index = smp_load_acquire(&q->buf->producer_index);
	index &= q->index_mask;

	वापस index;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक consumer_index(काष्ठा rxe_queue *q)
अणु
	u32 index;

	/* make sure all changes to queue
	 * complete beक्रमe getting consumer index
	 */
	index = smp_load_acquire(&q->buf->consumer_index);
	index &= q->index_mask;

	वापस index;
पूर्ण

अटल अंतरभूत व्योम *addr_from_index(काष्ठा rxe_queue *q, अचिन्हित पूर्णांक index)
अणु
	वापस q->buf->data + ((index & q->index_mask)
				<< q->buf->log2_elem_size);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक index_from_addr(स्थिर काष्ठा rxe_queue *q,
					   स्थिर व्योम *addr)
अणु
	वापस (((u8 *)addr - q->buf->data) >> q->log2_elem_size)
		& q->index_mask;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक queue_count(स्थिर काष्ठा rxe_queue *q)
अणु
	वापस (q->buf->producer_index - q->buf->consumer_index)
		& q->index_mask;
पूर्ण

अटल अंतरभूत व्योम *queue_head(काष्ठा rxe_queue *q)
अणु
	वापस queue_empty(q) ? शून्य : consumer_addr(q);
पूर्ण

#पूर्ण_अगर /* RXE_QUEUE_H */
