<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश "queueing.h"

काष्ठा multicore_worker __percpu *
wg_packet_percpu_multicore_worker_alloc(work_func_t function, व्योम *ptr)
अणु
	पूर्णांक cpu;
	काष्ठा multicore_worker __percpu *worker = alloc_percpu(काष्ठा multicore_worker);

	अगर (!worker)
		वापस शून्य;

	क्रम_each_possible_cpu(cpu) अणु
		per_cpu_ptr(worker, cpu)->ptr = ptr;
		INIT_WORK(&per_cpu_ptr(worker, cpu)->work, function);
	पूर्ण
	वापस worker;
पूर्ण

पूर्णांक wg_packet_queue_init(काष्ठा crypt_queue *queue, work_func_t function,
			 अचिन्हित पूर्णांक len)
अणु
	पूर्णांक ret;

	स_रखो(queue, 0, माप(*queue));
	ret = ptr_ring_init(&queue->ring, len, GFP_KERNEL);
	अगर (ret)
		वापस ret;
	queue->worker = wg_packet_percpu_multicore_worker_alloc(function, queue);
	अगर (!queue->worker) अणु
		ptr_ring_cleanup(&queue->ring, शून्य);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम wg_packet_queue_मुक्त(काष्ठा crypt_queue *queue)
अणु
	मुक्त_percpu(queue->worker);
	WARN_ON(!__ptr_ring_empty(&queue->ring));
	ptr_ring_cleanup(&queue->ring, शून्य);
पूर्ण

#घोषणा NEXT(skb) ((skb)->prev)
#घोषणा STUB(queue) ((काष्ठा sk_buff *)&queue->empty)

व्योम wg_prev_queue_init(काष्ठा prev_queue *queue)
अणु
	NEXT(STUB(queue)) = शून्य;
	queue->head = queue->tail = STUB(queue);
	queue->peeked = शून्य;
	atomic_set(&queue->count, 0);
	BUILD_BUG_ON(
		दुरत्व(काष्ठा sk_buff, next) != दुरत्व(काष्ठा prev_queue, empty.next) -
							दुरत्व(काष्ठा prev_queue, empty) ||
		दुरत्व(काष्ठा sk_buff, prev) != दुरत्व(काष्ठा prev_queue, empty.prev) -
							 दुरत्व(काष्ठा prev_queue, empty));
पूर्ण

अटल व्योम __wg_prev_queue_enqueue(काष्ठा prev_queue *queue, काष्ठा sk_buff *skb)
अणु
	WRITE_ONCE(NEXT(skb), शून्य);
	WRITE_ONCE(NEXT(xchg_release(&queue->head, skb)), skb);
पूर्ण

bool wg_prev_queue_enqueue(काष्ठा prev_queue *queue, काष्ठा sk_buff *skb)
अणु
	अगर (!atomic_add_unless(&queue->count, 1, MAX_QUEUED_PACKETS))
		वापस false;
	__wg_prev_queue_enqueue(queue, skb);
	वापस true;
पूर्ण

काष्ठा sk_buff *wg_prev_queue_dequeue(काष्ठा prev_queue *queue)
अणु
	काष्ठा sk_buff *tail = queue->tail, *next = smp_load_acquire(&NEXT(tail));

	अगर (tail == STUB(queue)) अणु
		अगर (!next)
			वापस शून्य;
		queue->tail = next;
		tail = next;
		next = smp_load_acquire(&NEXT(next));
	पूर्ण
	अगर (next) अणु
		queue->tail = next;
		atomic_dec(&queue->count);
		वापस tail;
	पूर्ण
	अगर (tail != READ_ONCE(queue->head))
		वापस शून्य;
	__wg_prev_queue_enqueue(queue, STUB(queue));
	next = smp_load_acquire(&NEXT(tail));
	अगर (next) अणु
		queue->tail = next;
		atomic_dec(&queue->count);
		वापस tail;
	पूर्ण
	वापस शून्य;
पूर्ण

#अघोषित NEXT
#अघोषित STUB
