<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश "rxe.h"
#समावेश "rxe_loc.h"
#समावेश "rxe_queue.h"

पूर्णांक करो_mmap_info(काष्ठा rxe_dev *rxe, काष्ठा mminfo __user *outbuf,
		 काष्ठा ib_udata *udata, काष्ठा rxe_queue_buf *buf,
		 माप_प्रकार buf_size, काष्ठा rxe_mmap_info **ip_p)
अणु
	पूर्णांक err;
	काष्ठा rxe_mmap_info *ip = शून्य;

	अगर (outbuf) अणु
		ip = rxe_create_mmap_info(rxe, buf_size, udata, buf);
		अगर (IS_ERR(ip)) अणु
			err = PTR_ERR(ip);
			जाओ err1;
		पूर्ण

		अगर (copy_to_user(outbuf, &ip->info, माप(ip->info))) अणु
			err = -EFAULT;
			जाओ err2;
		पूर्ण

		spin_lock_bh(&rxe->pending_lock);
		list_add(&ip->pending_mmaps, &rxe->pending_mmaps);
		spin_unlock_bh(&rxe->pending_lock);
	पूर्ण

	*ip_p = ip;

	वापस 0;

err2:
	kमुक्त(ip);
err1:
	वापस err;
पूर्ण

अंतरभूत व्योम rxe_queue_reset(काष्ठा rxe_queue *q)
अणु
	/* queue is comprised from header and the memory
	 * of the actual queue. See "struct rxe_queue_buf" in rxe_queue.h
	 * reset only the queue itself and not the management header
	 */
	स_रखो(q->buf->data, 0, q->buf_size - माप(काष्ठा rxe_queue_buf));
पूर्ण

काष्ठा rxe_queue *rxe_queue_init(काष्ठा rxe_dev *rxe,
				 पूर्णांक *num_elem,
				 अचिन्हित पूर्णांक elem_size)
अणु
	काष्ठा rxe_queue *q;
	माप_प्रकार buf_size;
	अचिन्हित पूर्णांक num_slots;

	/* num_elem == 0 is allowed, but unपूर्णांकeresting */
	अगर (*num_elem < 0)
		जाओ err1;

	q = kदो_स्मृति(माप(*q), GFP_KERNEL);
	अगर (!q)
		जाओ err1;

	q->rxe = rxe;

	/* used in resize, only need to copy used part of queue */
	q->elem_size = elem_size;

	/* pad element up to at least a cacheline and always a घातer of 2 */
	अगर (elem_size < cache_line_size())
		elem_size = cache_line_size();
	elem_size = roundup_घात_of_two(elem_size);

	q->log2_elem_size = order_base_2(elem_size);

	num_slots = *num_elem + 1;
	num_slots = roundup_घात_of_two(num_slots);
	q->index_mask = num_slots - 1;

	buf_size = माप(काष्ठा rxe_queue_buf) + num_slots * elem_size;

	q->buf = vदो_स्मृति_user(buf_size);
	अगर (!q->buf)
		जाओ err2;

	q->buf->log2_elem_size = q->log2_elem_size;
	q->buf->index_mask = q->index_mask;

	q->buf_size = buf_size;

	*num_elem = num_slots - 1;
	वापस q;

err2:
	kमुक्त(q);
err1:
	वापस शून्य;
पूर्ण

/* copies elements from original q to new q and then swaps the contents of the
 * two q headers. This is so that अगर anyone is holding a poपूर्णांकer to q it will
 * still work
 */
अटल पूर्णांक resize_finish(काष्ठा rxe_queue *q, काष्ठा rxe_queue *new_q,
			 अचिन्हित पूर्णांक num_elem)
अणु
	अगर (!queue_empty(q) && (num_elem < queue_count(q)))
		वापस -EINVAL;

	जबतक (!queue_empty(q)) अणु
		स_नकल(producer_addr(new_q), consumer_addr(q),
		       new_q->elem_size);
		advance_producer(new_q);
		advance_consumer(q);
	पूर्ण

	swap(*q, *new_q);

	वापस 0;
पूर्ण

पूर्णांक rxe_queue_resize(काष्ठा rxe_queue *q, अचिन्हित पूर्णांक *num_elem_p,
		     अचिन्हित पूर्णांक elem_size, काष्ठा ib_udata *udata,
		     काष्ठा mminfo __user *outbuf, spinlock_t *producer_lock,
		     spinlock_t *consumer_lock)
अणु
	काष्ठा rxe_queue *new_q;
	अचिन्हित पूर्णांक num_elem = *num_elem_p;
	पूर्णांक err;
	अचिन्हित दीर्घ flags = 0, flags1;

	new_q = rxe_queue_init(q->rxe, &num_elem, elem_size);
	अगर (!new_q)
		वापस -ENOMEM;

	err = करो_mmap_info(new_q->rxe, outbuf, udata, new_q->buf,
			   new_q->buf_size, &new_q->ip);
	अगर (err) अणु
		vमुक्त(new_q->buf);
		kमुक्त(new_q);
		जाओ err1;
	पूर्ण

	spin_lock_irqsave(consumer_lock, flags1);

	अगर (producer_lock) अणु
		spin_lock_irqsave(producer_lock, flags);
		err = resize_finish(q, new_q, num_elem);
		spin_unlock_irqrestore(producer_lock, flags);
	पूर्ण अन्यथा अणु
		err = resize_finish(q, new_q, num_elem);
	पूर्ण

	spin_unlock_irqrestore(consumer_lock, flags1);

	rxe_queue_cleanup(new_q);	/* new/old dep on err */
	अगर (err)
		जाओ err1;

	*num_elem_p = num_elem;
	वापस 0;

err1:
	वापस err;
पूर्ण

व्योम rxe_queue_cleanup(काष्ठा rxe_queue *q)
अणु
	अगर (q->ip)
		kref_put(&q->ip->ref, rxe_mmap_release);
	अन्यथा
		vमुक्त(q->buf);

	kमुक्त(q);
पूर्ण
