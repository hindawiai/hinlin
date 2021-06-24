<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/mm/mempool.c
 *
 *  memory buffer pool support. Such pools are mostly used
 *  क्रम guaranteed, deadlock-मुक्त memory allocations during
 *  extreme VM load.
 *
 *  started by Ingo Molnar, Copyright (C) 2001
 *  debugging by David Rientjes, Copyright (C) 2015
 */

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/kasan.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/export.h>
#समावेश <linux/mempool.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश "slab.h"

#अगर defined(CONFIG_DEBUG_SLAB) || defined(CONFIG_SLUB_DEBUG_ON)
अटल व्योम poison_error(mempool_t *pool, व्योम *element, माप_प्रकार size,
			 माप_प्रकार byte)
अणु
	स्थिर पूर्णांक nr = pool->curr_nr;
	स्थिर पूर्णांक start = max_t(पूर्णांक, byte - (BITS_PER_LONG / 8), 0);
	स्थिर पूर्णांक end = min_t(पूर्णांक, byte + (BITS_PER_LONG / 8), size);
	पूर्णांक i;

	pr_err("BUG: mempool element poison mismatch\n");
	pr_err("Mempool %p size %zu\n", pool, size);
	pr_err(" nr=%d @ %p: %s0x", nr, element, start > 0 ? "... " : "");
	क्रम (i = start; i < end; i++)
		pr_cont("%x ", *(u8 *)(element + i));
	pr_cont("%s\n", end < size ? "..." : "");
	dump_stack();
पूर्ण

अटल व्योम __check_element(mempool_t *pool, व्योम *element, माप_प्रकार size)
अणु
	u8 *obj = element;
	माप_प्रकार i;

	क्रम (i = 0; i < size; i++) अणु
		u8 exp = (i < size - 1) ? POISON_FREE : POISON_END;

		अगर (obj[i] != exp) अणु
			poison_error(pool, element, size, i);
			वापस;
		पूर्ण
	पूर्ण
	स_रखो(obj, POISON_INUSE, size);
पूर्ण

अटल व्योम check_element(mempool_t *pool, व्योम *element)
अणु
	/* Mempools backed by slab allocator */
	अगर (pool->मुक्त == mempool_मुक्त_slab || pool->मुक्त == mempool_kमुक्त) अणु
		__check_element(pool, element, ksize(element));
	पूर्ण अन्यथा अगर (pool->मुक्त == mempool_मुक्त_pages) अणु
		/* Mempools backed by page allocator */
		पूर्णांक order = (पूर्णांक)(दीर्घ)pool->pool_data;
		व्योम *addr = kmap_atomic((काष्ठा page *)element);

		__check_element(pool, addr, 1UL << (PAGE_SHIFT + order));
		kunmap_atomic(addr);
	पूर्ण
पूर्ण

अटल व्योम __poison_element(व्योम *element, माप_प्रकार size)
अणु
	u8 *obj = element;

	स_रखो(obj, POISON_FREE, size - 1);
	obj[size - 1] = POISON_END;
पूर्ण

अटल व्योम poison_element(mempool_t *pool, व्योम *element)
अणु
	/* Mempools backed by slab allocator */
	अगर (pool->alloc == mempool_alloc_slab || pool->alloc == mempool_kदो_स्मृति) अणु
		__poison_element(element, ksize(element));
	पूर्ण अन्यथा अगर (pool->alloc == mempool_alloc_pages) अणु
		/* Mempools backed by page allocator */
		पूर्णांक order = (पूर्णांक)(दीर्घ)pool->pool_data;
		व्योम *addr = kmap_atomic((काष्ठा page *)element);

		__poison_element(addr, 1UL << (PAGE_SHIFT + order));
		kunmap_atomic(addr);
	पूर्ण
पूर्ण
#अन्यथा /* CONFIG_DEBUG_SLAB || CONFIG_SLUB_DEBUG_ON */
अटल अंतरभूत व्योम check_element(mempool_t *pool, व्योम *element)
अणु
पूर्ण
अटल अंतरभूत व्योम poison_element(mempool_t *pool, व्योम *element)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_SLAB || CONFIG_SLUB_DEBUG_ON */

अटल __always_अंतरभूत व्योम kasan_poison_element(mempool_t *pool, व्योम *element)
अणु
	अगर (pool->alloc == mempool_alloc_slab || pool->alloc == mempool_kदो_स्मृति)
		kasan_slab_मुक्त_mempool(element);
	अन्यथा अगर (pool->alloc == mempool_alloc_pages)
		kasan_मुक्त_pages(element, (अचिन्हित दीर्घ)pool->pool_data, false);
पूर्ण

अटल व्योम kasan_unpoison_element(mempool_t *pool, व्योम *element)
अणु
	अगर (pool->alloc == mempool_alloc_slab || pool->alloc == mempool_kदो_स्मृति)
		kasan_unpoison_range(element, __ksize(element));
	अन्यथा अगर (pool->alloc == mempool_alloc_pages)
		kasan_alloc_pages(element, (अचिन्हित दीर्घ)pool->pool_data, false);
पूर्ण

अटल __always_अंतरभूत व्योम add_element(mempool_t *pool, व्योम *element)
अणु
	BUG_ON(pool->curr_nr >= pool->min_nr);
	poison_element(pool, element);
	kasan_poison_element(pool, element);
	pool->elements[pool->curr_nr++] = element;
पूर्ण

अटल व्योम *हटाओ_element(mempool_t *pool)
अणु
	व्योम *element = pool->elements[--pool->curr_nr];

	BUG_ON(pool->curr_nr < 0);
	kasan_unpoison_element(pool, element);
	check_element(pool, element);
	वापस element;
पूर्ण

/**
 * mempool_निकास - निकास a mempool initialized with mempool_init()
 * @pool:      poपूर्णांकer to the memory pool which was initialized with
 *             mempool_init().
 *
 * Free all reserved elements in @pool and @pool itself.  This function
 * only sleeps अगर the मुक्त_fn() function sleeps.
 *
 * May be called on a zeroed but uninitialized mempool (i.e. allocated with
 * kzalloc()).
 */
व्योम mempool_निकास(mempool_t *pool)
अणु
	जबतक (pool->curr_nr) अणु
		व्योम *element = हटाओ_element(pool);
		pool->मुक्त(element, pool->pool_data);
	पूर्ण
	kमुक्त(pool->elements);
	pool->elements = शून्य;
पूर्ण
EXPORT_SYMBOL(mempool_निकास);

/**
 * mempool_destroy - deallocate a memory pool
 * @pool:      poपूर्णांकer to the memory pool which was allocated via
 *             mempool_create().
 *
 * Free all reserved elements in @pool and @pool itself.  This function
 * only sleeps अगर the मुक्त_fn() function sleeps.
 */
व्योम mempool_destroy(mempool_t *pool)
अणु
	अगर (unlikely(!pool))
		वापस;

	mempool_निकास(pool);
	kमुक्त(pool);
पूर्ण
EXPORT_SYMBOL(mempool_destroy);

पूर्णांक mempool_init_node(mempool_t *pool, पूर्णांक min_nr, mempool_alloc_t *alloc_fn,
		      mempool_मुक्त_t *मुक्त_fn, व्योम *pool_data,
		      gfp_t gfp_mask, पूर्णांक node_id)
अणु
	spin_lock_init(&pool->lock);
	pool->min_nr	= min_nr;
	pool->pool_data = pool_data;
	pool->alloc	= alloc_fn;
	pool->मुक्त	= मुक्त_fn;
	init_रुकोqueue_head(&pool->रुको);

	pool->elements = kदो_स्मृति_array_node(min_nr, माप(व्योम *),
					    gfp_mask, node_id);
	अगर (!pool->elements)
		वापस -ENOMEM;

	/*
	 * First pre-allocate the guaranteed number of buffers.
	 */
	जबतक (pool->curr_nr < pool->min_nr) अणु
		व्योम *element;

		element = pool->alloc(gfp_mask, pool->pool_data);
		अगर (unlikely(!element)) अणु
			mempool_निकास(pool);
			वापस -ENOMEM;
		पूर्ण
		add_element(pool, element);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mempool_init_node);

/**
 * mempool_init - initialize a memory pool
 * @pool:      poपूर्णांकer to the memory pool that should be initialized
 * @min_nr:    the minimum number of elements guaranteed to be
 *             allocated क्रम this pool.
 * @alloc_fn:  user-defined element-allocation function.
 * @मुक्त_fn:   user-defined element-मुक्तing function.
 * @pool_data: optional निजी data available to the user-defined functions.
 *
 * Like mempool_create(), but initializes the pool in (i.e. embedded in another
 * काष्ठाure).
 *
 * Return: %0 on success, negative error code otherwise.
 */
पूर्णांक mempool_init(mempool_t *pool, पूर्णांक min_nr, mempool_alloc_t *alloc_fn,
		 mempool_मुक्त_t *मुक्त_fn, व्योम *pool_data)
अणु
	वापस mempool_init_node(pool, min_nr, alloc_fn, मुक्त_fn,
				 pool_data, GFP_KERNEL, NUMA_NO_NODE);

पूर्ण
EXPORT_SYMBOL(mempool_init);

/**
 * mempool_create - create a memory pool
 * @min_nr:    the minimum number of elements guaranteed to be
 *             allocated क्रम this pool.
 * @alloc_fn:  user-defined element-allocation function.
 * @मुक्त_fn:   user-defined element-मुक्तing function.
 * @pool_data: optional निजी data available to the user-defined functions.
 *
 * this function creates and allocates a guaranteed size, pपुनः_स्मृतिated
 * memory pool. The pool can be used from the mempool_alloc() and mempool_मुक्त()
 * functions. This function might sleep. Both the alloc_fn() and the मुक्त_fn()
 * functions might sleep - as दीर्घ as the mempool_alloc() function is not called
 * from IRQ contexts.
 *
 * Return: poपूर्णांकer to the created memory pool object or %शून्य on error.
 */
mempool_t *mempool_create(पूर्णांक min_nr, mempool_alloc_t *alloc_fn,
				mempool_मुक्त_t *मुक्त_fn, व्योम *pool_data)
अणु
	वापस mempool_create_node(min_nr, alloc_fn, मुक्त_fn, pool_data,
				   GFP_KERNEL, NUMA_NO_NODE);
पूर्ण
EXPORT_SYMBOL(mempool_create);

mempool_t *mempool_create_node(पूर्णांक min_nr, mempool_alloc_t *alloc_fn,
			       mempool_मुक्त_t *मुक्त_fn, व्योम *pool_data,
			       gfp_t gfp_mask, पूर्णांक node_id)
अणु
	mempool_t *pool;

	pool = kzalloc_node(माप(*pool), gfp_mask, node_id);
	अगर (!pool)
		वापस शून्य;

	अगर (mempool_init_node(pool, min_nr, alloc_fn, मुक्त_fn, pool_data,
			      gfp_mask, node_id)) अणु
		kमुक्त(pool);
		वापस शून्य;
	पूर्ण

	वापस pool;
पूर्ण
EXPORT_SYMBOL(mempool_create_node);

/**
 * mempool_resize - resize an existing memory pool
 * @pool:       poपूर्णांकer to the memory pool which was allocated via
 *              mempool_create().
 * @new_min_nr: the new minimum number of elements guaranteed to be
 *              allocated क्रम this pool.
 *
 * This function shrinks/grows the pool. In the हाल of growing,
 * it cannot be guaranteed that the pool will be grown to the new
 * size immediately, but new mempool_मुक्त() calls will refill it.
 * This function may sleep.
 *
 * Note, the caller must guarantee that no mempool_destroy is called
 * जबतक this function is running. mempool_alloc() & mempool_मुक्त()
 * might be called (eg. from IRQ contexts) जबतक this function executes.
 *
 * Return: %0 on success, negative error code otherwise.
 */
पूर्णांक mempool_resize(mempool_t *pool, पूर्णांक new_min_nr)
अणु
	व्योम *element;
	व्योम **new_elements;
	अचिन्हित दीर्घ flags;

	BUG_ON(new_min_nr <= 0);
	might_sleep();

	spin_lock_irqsave(&pool->lock, flags);
	अगर (new_min_nr <= pool->min_nr) अणु
		जबतक (new_min_nr < pool->curr_nr) अणु
			element = हटाओ_element(pool);
			spin_unlock_irqrestore(&pool->lock, flags);
			pool->मुक्त(element, pool->pool_data);
			spin_lock_irqsave(&pool->lock, flags);
		पूर्ण
		pool->min_nr = new_min_nr;
		जाओ out_unlock;
	पूर्ण
	spin_unlock_irqrestore(&pool->lock, flags);

	/* Grow the pool */
	new_elements = kदो_स्मृति_array(new_min_nr, माप(*new_elements),
				     GFP_KERNEL);
	अगर (!new_elements)
		वापस -ENOMEM;

	spin_lock_irqsave(&pool->lock, flags);
	अगर (unlikely(new_min_nr <= pool->min_nr)) अणु
		/* Raced, other resize will करो our work */
		spin_unlock_irqrestore(&pool->lock, flags);
		kमुक्त(new_elements);
		जाओ out;
	पूर्ण
	स_नकल(new_elements, pool->elements,
			pool->curr_nr * माप(*new_elements));
	kमुक्त(pool->elements);
	pool->elements = new_elements;
	pool->min_nr = new_min_nr;

	जबतक (pool->curr_nr < pool->min_nr) अणु
		spin_unlock_irqrestore(&pool->lock, flags);
		element = pool->alloc(GFP_KERNEL, pool->pool_data);
		अगर (!element)
			जाओ out;
		spin_lock_irqsave(&pool->lock, flags);
		अगर (pool->curr_nr < pool->min_nr) अणु
			add_element(pool, element);
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&pool->lock, flags);
			pool->मुक्त(element, pool->pool_data);	/* Raced */
			जाओ out;
		पूर्ण
	पूर्ण
out_unlock:
	spin_unlock_irqrestore(&pool->lock, flags);
out:
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mempool_resize);

/**
 * mempool_alloc - allocate an element from a specअगरic memory pool
 * @pool:      poपूर्णांकer to the memory pool which was allocated via
 *             mempool_create().
 * @gfp_mask:  the usual allocation biपंचांगask.
 *
 * this function only sleeps अगर the alloc_fn() function sleeps or
 * वापसs शून्य. Note that due to pपुनः_स्मृतिation, this function
 * *never* fails when called from process contexts. (it might
 * fail अगर called from an IRQ context.)
 * Note: using __GFP_ZERO is not supported.
 *
 * Return: poपूर्णांकer to the allocated element or %शून्य on error.
 */
व्योम *mempool_alloc(mempool_t *pool, gfp_t gfp_mask)
अणु
	व्योम *element;
	अचिन्हित दीर्घ flags;
	रुको_queue_entry_t रुको;
	gfp_t gfp_temp;

	VM_WARN_ON_ONCE(gfp_mask & __GFP_ZERO);
	might_sleep_अगर(gfp_mask & __GFP_सूचीECT_RECLAIM);

	gfp_mask |= __GFP_NOMEMALLOC;	/* करोn't allocate emergency reserves */
	gfp_mask |= __GFP_NORETRY;	/* करोn't loop in __alloc_pages */
	gfp_mask |= __GFP_NOWARN;	/* failures are OK */

	gfp_temp = gfp_mask & ~(__GFP_सूचीECT_RECLAIM|__GFP_IO);

repeat_alloc:

	element = pool->alloc(gfp_temp, pool->pool_data);
	अगर (likely(element != शून्य))
		वापस element;

	spin_lock_irqsave(&pool->lock, flags);
	अगर (likely(pool->curr_nr)) अणु
		element = हटाओ_element(pool);
		spin_unlock_irqrestore(&pool->lock, flags);
		/* paired with rmb in mempool_मुक्त(), पढ़ो comment there */
		smp_wmb();
		/*
		 * Update the allocation stack trace as this is more useful
		 * क्रम debugging.
		 */
		kmemleak_update_trace(element);
		वापस element;
	पूर्ण

	/*
	 * We use gfp mask w/o direct reclaim or IO क्रम the first round.  If
	 * alloc failed with that and @pool was empty, retry immediately.
	 */
	अगर (gfp_temp != gfp_mask) अणु
		spin_unlock_irqrestore(&pool->lock, flags);
		gfp_temp = gfp_mask;
		जाओ repeat_alloc;
	पूर्ण

	/* We must not sleep अगर !__GFP_सूचीECT_RECLAIM */
	अगर (!(gfp_mask & __GFP_सूचीECT_RECLAIM)) अणु
		spin_unlock_irqrestore(&pool->lock, flags);
		वापस शून्य;
	पूर्ण

	/* Let's रुको क्रम someone अन्यथा to वापस an element to @pool */
	init_रुको(&रुको);
	prepare_to_रुको(&pool->रुको, &रुको, TASK_UNINTERRUPTIBLE);

	spin_unlock_irqrestore(&pool->lock, flags);

	/*
	 * FIXME: this should be io_schedule().  The समयout is there as a
	 * workaround क्रम some DM problems in 2.6.18.
	 */
	io_schedule_समयout(5*HZ);

	finish_रुको(&pool->रुको, &रुको);
	जाओ repeat_alloc;
पूर्ण
EXPORT_SYMBOL(mempool_alloc);

/**
 * mempool_मुक्त - वापस an element to the pool.
 * @element:   pool element poपूर्णांकer.
 * @pool:      poपूर्णांकer to the memory pool which was allocated via
 *             mempool_create().
 *
 * this function only sleeps अगर the मुक्त_fn() function sleeps.
 */
व्योम mempool_मुक्त(व्योम *element, mempool_t *pool)
अणु
	अचिन्हित दीर्घ flags;

	अगर (unlikely(element == शून्य))
		वापस;

	/*
	 * Paired with the wmb in mempool_alloc().  The preceding पढ़ो is
	 * क्रम @element and the following @pool->curr_nr.  This ensures
	 * that the visible value of @pool->curr_nr is from after the
	 * allocation of @element.  This is necessary क्रम fringe हालs
	 * where @element was passed to this task without going through
	 * barriers.
	 *
	 * For example, assume @p is %शून्य at the beginning and one task
	 * perक्रमms "p = mempool_alloc(...);" जबतक another task is करोing
	 * "while (!p) cpu_relax(); mempool_free(p, ...);".  This function
	 * may end up using curr_nr value which is from beक्रमe allocation
	 * of @p without the following rmb.
	 */
	smp_rmb();

	/*
	 * For correctness, we need a test which is guaranteed to trigger
	 * अगर curr_nr + #allocated == min_nr.  Testing curr_nr < min_nr
	 * without locking achieves that and refilling as soon as possible
	 * is desirable.
	 *
	 * Because curr_nr visible here is always a value after the
	 * allocation of @element, any task which decremented curr_nr below
	 * min_nr is guaranteed to see curr_nr < min_nr unless curr_nr माला_लो
	 * incremented to min_nr afterwards.  If curr_nr माला_लो incremented
	 * to min_nr after the allocation of @element, the elements
	 * allocated after that are subject to the same guarantee.
	 *
	 * Waiters happen अगरf curr_nr is 0 and the above guarantee also
	 * ensures that there will be मुक्तs which वापस elements to the
	 * pool waking up the रुकोers.
	 */
	अगर (unlikely(READ_ONCE(pool->curr_nr) < pool->min_nr)) अणु
		spin_lock_irqsave(&pool->lock, flags);
		अगर (likely(pool->curr_nr < pool->min_nr)) अणु
			add_element(pool, element);
			spin_unlock_irqrestore(&pool->lock, flags);
			wake_up(&pool->रुको);
			वापस;
		पूर्ण
		spin_unlock_irqrestore(&pool->lock, flags);
	पूर्ण
	pool->मुक्त(element, pool->pool_data);
पूर्ण
EXPORT_SYMBOL(mempool_मुक्त);

/*
 * A commonly used alloc and मुक्त fn.
 */
व्योम *mempool_alloc_slab(gfp_t gfp_mask, व्योम *pool_data)
अणु
	काष्ठा kmem_cache *mem = pool_data;
	VM_BUG_ON(mem->ctor);
	वापस kmem_cache_alloc(mem, gfp_mask);
पूर्ण
EXPORT_SYMBOL(mempool_alloc_slab);

व्योम mempool_मुक्त_slab(व्योम *element, व्योम *pool_data)
अणु
	काष्ठा kmem_cache *mem = pool_data;
	kmem_cache_मुक्त(mem, element);
पूर्ण
EXPORT_SYMBOL(mempool_मुक्त_slab);

/*
 * A commonly used alloc and मुक्त fn that kदो_स्मृति/kमुक्तs the amount of memory
 * specअगरied by pool_data
 */
व्योम *mempool_kदो_स्मृति(gfp_t gfp_mask, व्योम *pool_data)
अणु
	माप_प्रकार size = (माप_प्रकार)pool_data;
	वापस kदो_स्मृति(size, gfp_mask);
पूर्ण
EXPORT_SYMBOL(mempool_kदो_स्मृति);

व्योम mempool_kमुक्त(व्योम *element, व्योम *pool_data)
अणु
	kमुक्त(element);
पूर्ण
EXPORT_SYMBOL(mempool_kमुक्त);

/*
 * A simple mempool-backed page allocator that allocates pages
 * of the order specअगरied by pool_data.
 */
व्योम *mempool_alloc_pages(gfp_t gfp_mask, व्योम *pool_data)
अणु
	पूर्णांक order = (पूर्णांक)(दीर्घ)pool_data;
	वापस alloc_pages(gfp_mask, order);
पूर्ण
EXPORT_SYMBOL(mempool_alloc_pages);

व्योम mempool_मुक्त_pages(व्योम *element, व्योम *pool_data)
अणु
	पूर्णांक order = (पूर्णांक)(दीर्घ)pool_data;
	__मुक्त_pages(element, order);
पूर्ण
EXPORT_SYMBOL(mempool_मुक्त_pages);
