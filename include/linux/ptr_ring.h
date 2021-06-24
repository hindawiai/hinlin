<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Definitions क्रम the 'struct ptr_ring' dataकाष्ठाure.
 *
 *	Author:
 *		Michael S. Tsirkin <mst@redhat.com>
 *
 *	Copyright (C) 2016 Red Hat, Inc.
 *
 *	This is a limited-size FIFO मुख्यtaining poपूर्णांकers in FIFO order, with
 *	one CPU producing entries and another consuming entries from a FIFO.
 *
 *	This implementation tries to minimize cache-contention when there is a
 *	single producer and a single consumer CPU.
 */

#अगर_अघोषित _LINUX_PTR_RING_H
#घोषणा _LINUX_PTR_RING_H 1

#अगर_घोषित __KERNEL__
#समावेश <linux/spinlock.h>
#समावेश <linux/cache.h>
#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/त्रुटिसं.स>
#पूर्ण_अगर

काष्ठा ptr_ring अणु
	पूर्णांक producer ____cacheline_aligned_in_smp;
	spinlock_t producer_lock;
	पूर्णांक consumer_head ____cacheline_aligned_in_smp; /* next valid entry */
	पूर्णांक consumer_tail; /* next entry to invalidate */
	spinlock_t consumer_lock;
	/* Shared consumer/producer data */
	/* Read-only by both the producer and the consumer */
	पूर्णांक size ____cacheline_aligned_in_smp; /* max entries in queue */
	पूर्णांक batch; /* number of entries to consume in a batch */
	व्योम **queue;
पूर्ण;

/* Note: callers invoking this in a loop must use a compiler barrier,
 * क्रम example cpu_relax().
 *
 * NB: this is unlike __ptr_ring_empty in that callers must hold producer_lock:
 * see e.g. ptr_ring_full.
 */
अटल अंतरभूत bool __ptr_ring_full(काष्ठा ptr_ring *r)
अणु
	वापस r->queue[r->producer];
पूर्ण

अटल अंतरभूत bool ptr_ring_full(काष्ठा ptr_ring *r)
अणु
	bool ret;

	spin_lock(&r->producer_lock);
	ret = __ptr_ring_full(r);
	spin_unlock(&r->producer_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत bool ptr_ring_full_irq(काष्ठा ptr_ring *r)
अणु
	bool ret;

	spin_lock_irq(&r->producer_lock);
	ret = __ptr_ring_full(r);
	spin_unlock_irq(&r->producer_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत bool ptr_ring_full_any(काष्ठा ptr_ring *r)
अणु
	अचिन्हित दीर्घ flags;
	bool ret;

	spin_lock_irqsave(&r->producer_lock, flags);
	ret = __ptr_ring_full(r);
	spin_unlock_irqrestore(&r->producer_lock, flags);

	वापस ret;
पूर्ण

अटल अंतरभूत bool ptr_ring_full_bh(काष्ठा ptr_ring *r)
अणु
	bool ret;

	spin_lock_bh(&r->producer_lock);
	ret = __ptr_ring_full(r);
	spin_unlock_bh(&r->producer_lock);

	वापस ret;
पूर्ण

/* Note: callers invoking this in a loop must use a compiler barrier,
 * क्रम example cpu_relax(). Callers must hold producer_lock.
 * Callers are responsible क्रम making sure poपूर्णांकer that is being queued
 * poपूर्णांकs to a valid data.
 */
अटल अंतरभूत पूर्णांक __ptr_ring_produce(काष्ठा ptr_ring *r, व्योम *ptr)
अणु
	अगर (unlikely(!r->size) || r->queue[r->producer])
		वापस -ENOSPC;

	/* Make sure the poपूर्णांकer we are storing poपूर्णांकs to a valid data. */
	/* Pairs with the dependency ordering in __ptr_ring_consume. */
	smp_wmb();

	WRITE_ONCE(r->queue[r->producer++], ptr);
	अगर (unlikely(r->producer >= r->size))
		r->producer = 0;
	वापस 0;
पूर्ण

/*
 * Note: resize (below) nests producer lock within consumer lock, so अगर you
 * consume in पूर्णांकerrupt or BH context, you must disable पूर्णांकerrupts/BH when
 * calling this.
 */
अटल अंतरभूत पूर्णांक ptr_ring_produce(काष्ठा ptr_ring *r, व्योम *ptr)
अणु
	पूर्णांक ret;

	spin_lock(&r->producer_lock);
	ret = __ptr_ring_produce(r, ptr);
	spin_unlock(&r->producer_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ptr_ring_produce_irq(काष्ठा ptr_ring *r, व्योम *ptr)
अणु
	पूर्णांक ret;

	spin_lock_irq(&r->producer_lock);
	ret = __ptr_ring_produce(r, ptr);
	spin_unlock_irq(&r->producer_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ptr_ring_produce_any(काष्ठा ptr_ring *r, व्योम *ptr)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&r->producer_lock, flags);
	ret = __ptr_ring_produce(r, ptr);
	spin_unlock_irqrestore(&r->producer_lock, flags);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ptr_ring_produce_bh(काष्ठा ptr_ring *r, व्योम *ptr)
अणु
	पूर्णांक ret;

	spin_lock_bh(&r->producer_lock);
	ret = __ptr_ring_produce(r, ptr);
	spin_unlock_bh(&r->producer_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम *__ptr_ring_peek(काष्ठा ptr_ring *r)
अणु
	अगर (likely(r->size))
		वापस READ_ONCE(r->queue[r->consumer_head]);
	वापस शून्य;
पूर्ण

/*
 * Test ring empty status without taking any locks.
 *
 * NB: This is only safe to call अगर ring is never resized.
 *
 * However, अगर some other CPU consumes ring entries at the same समय, the value
 * वापसed is not guaranteed to be correct.
 *
 * In this हाल - to aव्योम incorrectly detecting the ring
 * as empty - the CPU consuming the ring entries is responsible
 * क्रम either consuming all ring entries until the ring is empty,
 * or synchronizing with some other CPU and causing it to
 * re-test __ptr_ring_empty and/or consume the ring enteries
 * after the synchronization poपूर्णांक.
 *
 * Note: callers invoking this in a loop must use a compiler barrier,
 * क्रम example cpu_relax().
 */
अटल अंतरभूत bool __ptr_ring_empty(काष्ठा ptr_ring *r)
अणु
	अगर (likely(r->size))
		वापस !r->queue[READ_ONCE(r->consumer_head)];
	वापस true;
पूर्ण

अटल अंतरभूत bool ptr_ring_empty(काष्ठा ptr_ring *r)
अणु
	bool ret;

	spin_lock(&r->consumer_lock);
	ret = __ptr_ring_empty(r);
	spin_unlock(&r->consumer_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत bool ptr_ring_empty_irq(काष्ठा ptr_ring *r)
अणु
	bool ret;

	spin_lock_irq(&r->consumer_lock);
	ret = __ptr_ring_empty(r);
	spin_unlock_irq(&r->consumer_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत bool ptr_ring_empty_any(काष्ठा ptr_ring *r)
अणु
	अचिन्हित दीर्घ flags;
	bool ret;

	spin_lock_irqsave(&r->consumer_lock, flags);
	ret = __ptr_ring_empty(r);
	spin_unlock_irqrestore(&r->consumer_lock, flags);

	वापस ret;
पूर्ण

अटल अंतरभूत bool ptr_ring_empty_bh(काष्ठा ptr_ring *r)
अणु
	bool ret;

	spin_lock_bh(&r->consumer_lock);
	ret = __ptr_ring_empty(r);
	spin_unlock_bh(&r->consumer_lock);

	वापस ret;
पूर्ण

/* Must only be called after __ptr_ring_peek वापसed !शून्य */
अटल अंतरभूत व्योम __ptr_ring_discard_one(काष्ठा ptr_ring *r)
अणु
	/* Fundamentally, what we want to करो is update consumer
	 * index and zero out the entry so producer can reuse it.
	 * Doing it naively at each consume would be as simple as:
	 *       consumer = r->consumer;
	 *       r->queue[consumer++] = शून्य;
	 *       अगर (unlikely(consumer >= r->size))
	 *               consumer = 0;
	 *       r->consumer = consumer;
	 * but that is suboptimal when the ring is full as producer is writing
	 * out new entries in the same cache line.  Defer these updates until a
	 * batch of entries has been consumed.
	 */
	/* Note: we must keep consumer_head valid at all बार क्रम __ptr_ring_empty
	 * to work correctly.
	 */
	पूर्णांक consumer_head = r->consumer_head;
	पूर्णांक head = consumer_head++;

	/* Once we have processed enough entries invalidate them in
	 * the ring all at once so producer can reuse their space in the ring.
	 * We also करो this when we reach end of the ring - not mandatory
	 * but helps keep the implementation simple.
	 */
	अगर (unlikely(consumer_head - r->consumer_tail >= r->batch ||
		     consumer_head >= r->size)) अणु
		/* Zero out entries in the reverse order: this way we touch the
		 * cache line that producer might currently be पढ़ोing the last;
		 * producer won't make progress and touch other cache lines
		 * besides the first one until we ग_लिखो out all entries.
		 */
		जबतक (likely(head >= r->consumer_tail))
			r->queue[head--] = शून्य;
		r->consumer_tail = consumer_head;
	पूर्ण
	अगर (unlikely(consumer_head >= r->size)) अणु
		consumer_head = 0;
		r->consumer_tail = 0;
	पूर्ण
	/* matching READ_ONCE in __ptr_ring_empty क्रम lockless tests */
	WRITE_ONCE(r->consumer_head, consumer_head);
पूर्ण

अटल अंतरभूत व्योम *__ptr_ring_consume(काष्ठा ptr_ring *r)
अणु
	व्योम *ptr;

	/* The READ_ONCE in __ptr_ring_peek guarantees that anyone
	 * accessing data through the poपूर्णांकer is up to date. Pairs
	 * with smp_wmb in __ptr_ring_produce.
	 */
	ptr = __ptr_ring_peek(r);
	अगर (ptr)
		__ptr_ring_discard_one(r);

	वापस ptr;
पूर्ण

अटल अंतरभूत पूर्णांक __ptr_ring_consume_batched(काष्ठा ptr_ring *r,
					     व्योम **array, पूर्णांक n)
अणु
	व्योम *ptr;
	पूर्णांक i;

	क्रम (i = 0; i < n; i++) अणु
		ptr = __ptr_ring_consume(r);
		अगर (!ptr)
			अवरोध;
		array[i] = ptr;
	पूर्ण

	वापस i;
पूर्ण

/*
 * Note: resize (below) nests producer lock within consumer lock, so अगर you
 * call this in पूर्णांकerrupt or BH context, you must disable पूर्णांकerrupts/BH when
 * producing.
 */
अटल अंतरभूत व्योम *ptr_ring_consume(काष्ठा ptr_ring *r)
अणु
	व्योम *ptr;

	spin_lock(&r->consumer_lock);
	ptr = __ptr_ring_consume(r);
	spin_unlock(&r->consumer_lock);

	वापस ptr;
पूर्ण

अटल अंतरभूत व्योम *ptr_ring_consume_irq(काष्ठा ptr_ring *r)
अणु
	व्योम *ptr;

	spin_lock_irq(&r->consumer_lock);
	ptr = __ptr_ring_consume(r);
	spin_unlock_irq(&r->consumer_lock);

	वापस ptr;
पूर्ण

अटल अंतरभूत व्योम *ptr_ring_consume_any(काष्ठा ptr_ring *r)
अणु
	अचिन्हित दीर्घ flags;
	व्योम *ptr;

	spin_lock_irqsave(&r->consumer_lock, flags);
	ptr = __ptr_ring_consume(r);
	spin_unlock_irqrestore(&r->consumer_lock, flags);

	वापस ptr;
पूर्ण

अटल अंतरभूत व्योम *ptr_ring_consume_bh(काष्ठा ptr_ring *r)
अणु
	व्योम *ptr;

	spin_lock_bh(&r->consumer_lock);
	ptr = __ptr_ring_consume(r);
	spin_unlock_bh(&r->consumer_lock);

	वापस ptr;
पूर्ण

अटल अंतरभूत पूर्णांक ptr_ring_consume_batched(काष्ठा ptr_ring *r,
					   व्योम **array, पूर्णांक n)
अणु
	पूर्णांक ret;

	spin_lock(&r->consumer_lock);
	ret = __ptr_ring_consume_batched(r, array, n);
	spin_unlock(&r->consumer_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ptr_ring_consume_batched_irq(काष्ठा ptr_ring *r,
					       व्योम **array, पूर्णांक n)
अणु
	पूर्णांक ret;

	spin_lock_irq(&r->consumer_lock);
	ret = __ptr_ring_consume_batched(r, array, n);
	spin_unlock_irq(&r->consumer_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ptr_ring_consume_batched_any(काष्ठा ptr_ring *r,
					       व्योम **array, पूर्णांक n)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&r->consumer_lock, flags);
	ret = __ptr_ring_consume_batched(r, array, n);
	spin_unlock_irqrestore(&r->consumer_lock, flags);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ptr_ring_consume_batched_bh(काष्ठा ptr_ring *r,
					      व्योम **array, पूर्णांक n)
अणु
	पूर्णांक ret;

	spin_lock_bh(&r->consumer_lock);
	ret = __ptr_ring_consume_batched(r, array, n);
	spin_unlock_bh(&r->consumer_lock);

	वापस ret;
पूर्ण

/* Cast to काष्ठाure type and call a function without discarding from FIFO.
 * Function must वापस a value.
 * Callers must take consumer_lock.
 */
#घोषणा __PTR_RING_PEEK_CALL(r, f) ((f)(__ptr_ring_peek(r)))

#घोषणा PTR_RING_PEEK_CALL(r, f) (अणु \
	typeof((f)(शून्य)) __PTR_RING_PEEK_CALL_v; \
	\
	spin_lock(&(r)->consumer_lock); \
	__PTR_RING_PEEK_CALL_v = __PTR_RING_PEEK_CALL(r, f); \
	spin_unlock(&(r)->consumer_lock); \
	__PTR_RING_PEEK_CALL_v; \
पूर्ण)

#घोषणा PTR_RING_PEEK_CALL_IRQ(r, f) (अणु \
	typeof((f)(शून्य)) __PTR_RING_PEEK_CALL_v; \
	\
	spin_lock_irq(&(r)->consumer_lock); \
	__PTR_RING_PEEK_CALL_v = __PTR_RING_PEEK_CALL(r, f); \
	spin_unlock_irq(&(r)->consumer_lock); \
	__PTR_RING_PEEK_CALL_v; \
पूर्ण)

#घोषणा PTR_RING_PEEK_CALL_BH(r, f) (अणु \
	typeof((f)(शून्य)) __PTR_RING_PEEK_CALL_v; \
	\
	spin_lock_bh(&(r)->consumer_lock); \
	__PTR_RING_PEEK_CALL_v = __PTR_RING_PEEK_CALL(r, f); \
	spin_unlock_bh(&(r)->consumer_lock); \
	__PTR_RING_PEEK_CALL_v; \
पूर्ण)

#घोषणा PTR_RING_PEEK_CALL_ANY(r, f) (अणु \
	typeof((f)(शून्य)) __PTR_RING_PEEK_CALL_v; \
	अचिन्हित दीर्घ __PTR_RING_PEEK_CALL_f;\
	\
	spin_lock_irqsave(&(r)->consumer_lock, __PTR_RING_PEEK_CALL_f); \
	__PTR_RING_PEEK_CALL_v = __PTR_RING_PEEK_CALL(r, f); \
	spin_unlock_irqrestore(&(r)->consumer_lock, __PTR_RING_PEEK_CALL_f); \
	__PTR_RING_PEEK_CALL_v; \
पूर्ण)

/* Not all gfp_t flags (besides GFP_KERNEL) are allowed. See
 * करोcumentation क्रम vदो_स्मृति क्रम which of them are legal.
 */
अटल अंतरभूत व्योम **__ptr_ring_init_queue_alloc(अचिन्हित पूर्णांक size, gfp_t gfp)
अणु
	अगर (size > KMALLOC_MAX_SIZE / माप(व्योम *))
		वापस शून्य;
	वापस kvदो_स्मृति_array(size, माप(व्योम *), gfp | __GFP_ZERO);
पूर्ण

अटल अंतरभूत व्योम __ptr_ring_set_size(काष्ठा ptr_ring *r, पूर्णांक size)
अणु
	r->size = size;
	r->batch = SMP_CACHE_BYTES * 2 / माप(*(r->queue));
	/* We need to set batch at least to 1 to make logic
	 * in __ptr_ring_discard_one work correctly.
	 * Batching too much (because ring is small) would cause a lot of
	 * burstiness. Needs tuning, क्रम now disable batching.
	 */
	अगर (r->batch > r->size / 2 || !r->batch)
		r->batch = 1;
पूर्ण

अटल अंतरभूत पूर्णांक ptr_ring_init(काष्ठा ptr_ring *r, पूर्णांक size, gfp_t gfp)
अणु
	r->queue = __ptr_ring_init_queue_alloc(size, gfp);
	अगर (!r->queue)
		वापस -ENOMEM;

	__ptr_ring_set_size(r, size);
	r->producer = r->consumer_head = r->consumer_tail = 0;
	spin_lock_init(&r->producer_lock);
	spin_lock_init(&r->consumer_lock);

	वापस 0;
पूर्ण

/*
 * Return entries पूर्णांकo ring. Destroy entries that करोn't fit.
 *
 * Note: this is expected to be a rare slow path operation.
 *
 * Note: producer lock is nested within consumer lock, so अगर you
 * resize you must make sure all uses nest correctly.
 * In particular अगर you consume ring in पूर्णांकerrupt or BH context, you must
 * disable पूर्णांकerrupts/BH when करोing so.
 */
अटल अंतरभूत व्योम ptr_ring_unconsume(काष्ठा ptr_ring *r, व्योम **batch, पूर्णांक n,
				      व्योम (*destroy)(व्योम *))
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक head;

	spin_lock_irqsave(&r->consumer_lock, flags);
	spin_lock(&r->producer_lock);

	अगर (!r->size)
		जाओ करोne;

	/*
	 * Clean out buffered entries (क्रम simplicity). This way following code
	 * can test entries क्रम शून्य and अगर not assume they are valid.
	 */
	head = r->consumer_head - 1;
	जबतक (likely(head >= r->consumer_tail))
		r->queue[head--] = शून्य;
	r->consumer_tail = r->consumer_head;

	/*
	 * Go over entries in batch, start moving head back and copy entries.
	 * Stop when we run पूर्णांकo previously unconsumed entries.
	 */
	जबतक (n) अणु
		head = r->consumer_head - 1;
		अगर (head < 0)
			head = r->size - 1;
		अगर (r->queue[head]) अणु
			/* This batch entry will have to be destroyed. */
			जाओ करोne;
		पूर्ण
		r->queue[head] = batch[--n];
		r->consumer_tail = head;
		/* matching READ_ONCE in __ptr_ring_empty क्रम lockless tests */
		WRITE_ONCE(r->consumer_head, head);
	पूर्ण

करोne:
	/* Destroy all entries left in the batch. */
	जबतक (n)
		destroy(batch[--n]);
	spin_unlock(&r->producer_lock);
	spin_unlock_irqrestore(&r->consumer_lock, flags);
पूर्ण

अटल अंतरभूत व्योम **__ptr_ring_swap_queue(काष्ठा ptr_ring *r, व्योम **queue,
					   पूर्णांक size, gfp_t gfp,
					   व्योम (*destroy)(व्योम *))
अणु
	पूर्णांक producer = 0;
	व्योम **old;
	व्योम *ptr;

	जबतक ((ptr = __ptr_ring_consume(r)))
		अगर (producer < size)
			queue[producer++] = ptr;
		अन्यथा अगर (destroy)
			destroy(ptr);

	अगर (producer >= size)
		producer = 0;
	__ptr_ring_set_size(r, size);
	r->producer = producer;
	r->consumer_head = 0;
	r->consumer_tail = 0;
	old = r->queue;
	r->queue = queue;

	वापस old;
पूर्ण

/*
 * Note: producer lock is nested within consumer lock, so अगर you
 * resize you must make sure all uses nest correctly.
 * In particular अगर you consume ring in पूर्णांकerrupt or BH context, you must
 * disable पूर्णांकerrupts/BH when करोing so.
 */
अटल अंतरभूत पूर्णांक ptr_ring_resize(काष्ठा ptr_ring *r, पूर्णांक size, gfp_t gfp,
				  व्योम (*destroy)(व्योम *))
अणु
	अचिन्हित दीर्घ flags;
	व्योम **queue = __ptr_ring_init_queue_alloc(size, gfp);
	व्योम **old;

	अगर (!queue)
		वापस -ENOMEM;

	spin_lock_irqsave(&(r)->consumer_lock, flags);
	spin_lock(&(r)->producer_lock);

	old = __ptr_ring_swap_queue(r, queue, size, gfp, destroy);

	spin_unlock(&(r)->producer_lock);
	spin_unlock_irqrestore(&(r)->consumer_lock, flags);

	kvमुक्त(old);

	वापस 0;
पूर्ण

/*
 * Note: producer lock is nested within consumer lock, so अगर you
 * resize you must make sure all uses nest correctly.
 * In particular अगर you consume ring in पूर्णांकerrupt or BH context, you must
 * disable पूर्णांकerrupts/BH when करोing so.
 */
अटल अंतरभूत पूर्णांक ptr_ring_resize_multiple(काष्ठा ptr_ring **rings,
					   अचिन्हित पूर्णांक nrings,
					   पूर्णांक size,
					   gfp_t gfp, व्योम (*destroy)(व्योम *))
अणु
	अचिन्हित दीर्घ flags;
	व्योम ***queues;
	पूर्णांक i;

	queues = kदो_स्मृति_array(nrings, माप(*queues), gfp);
	अगर (!queues)
		जाओ noqueues;

	क्रम (i = 0; i < nrings; ++i) अणु
		queues[i] = __ptr_ring_init_queue_alloc(size, gfp);
		अगर (!queues[i])
			जाओ nomem;
	पूर्ण

	क्रम (i = 0; i < nrings; ++i) अणु
		spin_lock_irqsave(&(rings[i])->consumer_lock, flags);
		spin_lock(&(rings[i])->producer_lock);
		queues[i] = __ptr_ring_swap_queue(rings[i], queues[i],
						  size, gfp, destroy);
		spin_unlock(&(rings[i])->producer_lock);
		spin_unlock_irqrestore(&(rings[i])->consumer_lock, flags);
	पूर्ण

	क्रम (i = 0; i < nrings; ++i)
		kvमुक्त(queues[i]);

	kमुक्त(queues);

	वापस 0;

nomem:
	जबतक (--i >= 0)
		kvमुक्त(queues[i]);

	kमुक्त(queues);

noqueues:
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत व्योम ptr_ring_cleanup(काष्ठा ptr_ring *r, व्योम (*destroy)(व्योम *))
अणु
	व्योम *ptr;

	अगर (destroy)
		जबतक ((ptr = ptr_ring_consume(r)))
			destroy(ptr);
	kvमुक्त(r->queue);
पूर्ण

#पूर्ण_अगर /* _LINUX_PTR_RING_H  */
