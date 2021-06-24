<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * page_pool.c
 *	Author:	Jesper Dangaard Brouer <netoptimizer@brouer.com>
 *	Copyright (C) 2016 Red Hat, Inc.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>

#समावेश <net/page_pool.h>
#समावेश <net/xdp.h>

#समावेश <linux/dma-direction.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/mm.h> /* क्रम __put_page() */

#समावेश <trace/events/page_pool.h>

#घोषणा DEFER_TIME (msecs_to_jअगरfies(1000))
#घोषणा DEFER_WARN_INTERVAL (60 * HZ)

अटल पूर्णांक page_pool_init(काष्ठा page_pool *pool,
			  स्थिर काष्ठा page_pool_params *params)
अणु
	अचिन्हित पूर्णांक ring_qsize = 1024; /* Default */

	स_नकल(&pool->p, params, माप(pool->p));

	/* Validate only known flags were used */
	अगर (pool->p.flags & ~(PP_FLAG_ALL))
		वापस -EINVAL;

	अगर (pool->p.pool_size)
		ring_qsize = pool->p.pool_size;

	/* Sanity limit mem that can be pinned करोwn */
	अगर (ring_qsize > 32768)
		वापस -E2BIG;

	/* DMA direction is either DMA_FROM_DEVICE or DMA_BIसूचीECTIONAL.
	 * DMA_BIसूचीECTIONAL is क्रम allowing page used क्रम DMA sending,
	 * which is the XDP_TX use-हाल.
	 */
	अगर (pool->p.flags & PP_FLAG_DMA_MAP) अणु
		अगर ((pool->p.dma_dir != DMA_FROM_DEVICE) &&
		    (pool->p.dma_dir != DMA_BIसूचीECTIONAL))
			वापस -EINVAL;
	पूर्ण

	अगर (pool->p.flags & PP_FLAG_DMA_SYNC_DEV) अणु
		/* In order to request DMA-sync-क्रम-device the page
		 * needs to be mapped
		 */
		अगर (!(pool->p.flags & PP_FLAG_DMA_MAP))
			वापस -EINVAL;

		अगर (!pool->p.max_len)
			वापस -EINVAL;

		/* pool->p.offset has to be set according to the address
		 * offset used by the DMA engine to start copying rx data
		 */
	पूर्ण

	अगर (ptr_ring_init(&pool->ring, ring_qsize, GFP_KERNEL) < 0)
		वापस -ENOMEM;

	atomic_set(&pool->pages_state_release_cnt, 0);

	/* Driver calling page_pool_create() also call page_pool_destroy() */
	refcount_set(&pool->user_cnt, 1);

	अगर (pool->p.flags & PP_FLAG_DMA_MAP)
		get_device(pool->p.dev);

	वापस 0;
पूर्ण

काष्ठा page_pool *page_pool_create(स्थिर काष्ठा page_pool_params *params)
अणु
	काष्ठा page_pool *pool;
	पूर्णांक err;

	pool = kzalloc_node(माप(*pool), GFP_KERNEL, params->nid);
	अगर (!pool)
		वापस ERR_PTR(-ENOMEM);

	err = page_pool_init(pool, params);
	अगर (err < 0) अणु
		pr_warn("%s() gave up with errno %d\n", __func__, err);
		kमुक्त(pool);
		वापस ERR_PTR(err);
	पूर्ण

	वापस pool;
पूर्ण
EXPORT_SYMBOL(page_pool_create);

अटल व्योम page_pool_वापस_page(काष्ठा page_pool *pool, काष्ठा page *page);

noअंतरभूत
अटल काष्ठा page *page_pool_refill_alloc_cache(काष्ठा page_pool *pool)
अणु
	काष्ठा ptr_ring *r = &pool->ring;
	काष्ठा page *page;
	पूर्णांक pref_nid; /* preferred NUMA node */

	/* Quicker fallback, aव्योम locks when ring is empty */
	अगर (__ptr_ring_empty(r))
		वापस शून्य;

	/* Softirq guarantee CPU and thus NUMA node is stable. This,
	 * assumes CPU refilling driver RX-ring will also run RX-NAPI.
	 */
#अगर_घोषित CONFIG_NUMA
	pref_nid = (pool->p.nid == NUMA_NO_NODE) ? numa_mem_id() : pool->p.nid;
#अन्यथा
	/* Ignore pool->p.nid setting अगर !CONFIG_NUMA, helps compiler */
	pref_nid = numa_mem_id(); /* will be zero like page_to_nid() */
#पूर्ण_अगर

	/* Slower-path: Get pages from locked ring queue */
	spin_lock(&r->consumer_lock);

	/* Refill alloc array, but only अगर NUMA match */
	करो अणु
		page = __ptr_ring_consume(r);
		अगर (unlikely(!page))
			अवरोध;

		अगर (likely(page_to_nid(page) == pref_nid)) अणु
			pool->alloc.cache[pool->alloc.count++] = page;
		पूर्ण अन्यथा अणु
			/* NUMA mismatch;
			 * (1) release 1 page to page-allocator and
			 * (2) अवरोध out to fallthrough to alloc_pages_node.
			 * This limit stress on page buddy alloactor.
			 */
			page_pool_वापस_page(pool, page);
			page = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (pool->alloc.count < PP_ALLOC_CACHE_REFILL);

	/* Return last page */
	अगर (likely(pool->alloc.count > 0))
		page = pool->alloc.cache[--pool->alloc.count];

	spin_unlock(&r->consumer_lock);
	वापस page;
पूर्ण

/* fast path */
अटल काष्ठा page *__page_pool_get_cached(काष्ठा page_pool *pool)
अणु
	काष्ठा page *page;

	/* Caller MUST guarantee safe non-concurrent access, e.g. softirq */
	अगर (likely(pool->alloc.count)) अणु
		/* Fast-path */
		page = pool->alloc.cache[--pool->alloc.count];
	पूर्ण अन्यथा अणु
		page = page_pool_refill_alloc_cache(pool);
	पूर्ण

	वापस page;
पूर्ण

अटल व्योम page_pool_dma_sync_क्रम_device(काष्ठा page_pool *pool,
					  काष्ठा page *page,
					  अचिन्हित पूर्णांक dma_sync_size)
अणु
	dma_addr_t dma_addr = page_pool_get_dma_addr(page);

	dma_sync_size = min(dma_sync_size, pool->p.max_len);
	dma_sync_single_range_क्रम_device(pool->p.dev, dma_addr,
					 pool->p.offset, dma_sync_size,
					 pool->p.dma_dir);
पूर्ण

अटल bool page_pool_dma_map(काष्ठा page_pool *pool, काष्ठा page *page)
अणु
	dma_addr_t dma;

	/* Setup DMA mapping: use 'struct page' area क्रम storing DMA-addr
	 * since dma_addr_t can be either 32 or 64 bits and करोes not always fit
	 * पूर्णांकo page निजी data (i.e 32bit cpu with 64bit DMA caps)
	 * This mapping is kept क्रम lअगरeसमय of page, until leaving pool.
	 */
	dma = dma_map_page_attrs(pool->p.dev, page, 0,
				 (PAGE_SIZE << pool->p.order),
				 pool->p.dma_dir, DMA_ATTR_SKIP_CPU_SYNC);
	अगर (dma_mapping_error(pool->p.dev, dma))
		वापस false;

	page_pool_set_dma_addr(page, dma);

	अगर (pool->p.flags & PP_FLAG_DMA_SYNC_DEV)
		page_pool_dma_sync_क्रम_device(pool, page, pool->p.max_len);

	वापस true;
पूर्ण

अटल काष्ठा page *__page_pool_alloc_page_order(काष्ठा page_pool *pool,
						 gfp_t gfp)
अणु
	काष्ठा page *page;

	gfp |= __GFP_COMP;
	page = alloc_pages_node(pool->p.nid, gfp, pool->p.order);
	अगर (unlikely(!page))
		वापस शून्य;

	अगर ((pool->p.flags & PP_FLAG_DMA_MAP) &&
	    unlikely(!page_pool_dma_map(pool, page))) अणु
		put_page(page);
		वापस शून्य;
	पूर्ण

	/* Track how many pages are held 'in-flight' */
	pool->pages_state_hold_cnt++;
	trace_page_pool_state_hold(pool, page, pool->pages_state_hold_cnt);
	वापस page;
पूर्ण

/* slow path */
noअंतरभूत
अटल काष्ठा page *__page_pool_alloc_pages_slow(काष्ठा page_pool *pool,
						 gfp_t gfp)
अणु
	स्थिर पूर्णांक bulk = PP_ALLOC_CACHE_REFILL;
	अचिन्हित पूर्णांक pp_flags = pool->p.flags;
	अचिन्हित पूर्णांक pp_order = pool->p.order;
	काष्ठा page *page;
	पूर्णांक i, nr_pages;

	/* Don't support bulk alloc क्रम high-order pages */
	अगर (unlikely(pp_order))
		वापस __page_pool_alloc_page_order(pool, gfp);

	/* Unnecessary as alloc cache is empty, but guarantees zero count */
	अगर (unlikely(pool->alloc.count > 0))
		वापस pool->alloc.cache[--pool->alloc.count];

	/* Mark empty alloc.cache slots "empty" क्रम alloc_pages_bulk_array */
	स_रखो(&pool->alloc.cache, 0, माप(व्योम *) * bulk);

	nr_pages = alloc_pages_bulk_array(gfp, bulk, pool->alloc.cache);
	अगर (unlikely(!nr_pages))
		वापस शून्य;

	/* Pages have been filled पूर्णांकo alloc.cache array, but count is zero and
	 * page element have not been (possibly) DMA mapped.
	 */
	क्रम (i = 0; i < nr_pages; i++) अणु
		page = pool->alloc.cache[i];
		अगर ((pp_flags & PP_FLAG_DMA_MAP) &&
		    unlikely(!page_pool_dma_map(pool, page))) अणु
			put_page(page);
			जारी;
		पूर्ण
		pool->alloc.cache[pool->alloc.count++] = page;
		/* Track how many pages are held 'in-flight' */
		pool->pages_state_hold_cnt++;
		trace_page_pool_state_hold(pool, page,
					   pool->pages_state_hold_cnt);
	पूर्ण

	/* Return last page */
	अगर (likely(pool->alloc.count > 0))
		page = pool->alloc.cache[--pool->alloc.count];
	अन्यथा
		page = शून्य;

	/* When page just alloc'ed is should/must have refcnt 1. */
	वापस page;
पूर्ण

/* For using page_pool replace: alloc_pages() API calls, but provide
 * synchronization guarantee क्रम allocation side.
 */
काष्ठा page *page_pool_alloc_pages(काष्ठा page_pool *pool, gfp_t gfp)
अणु
	काष्ठा page *page;

	/* Fast-path: Get a page from cache */
	page = __page_pool_get_cached(pool);
	अगर (page)
		वापस page;

	/* Slow-path: cache empty, करो real allocation */
	page = __page_pool_alloc_pages_slow(pool, gfp);
	वापस page;
पूर्ण
EXPORT_SYMBOL(page_pool_alloc_pages);

/* Calculate distance between two u32 values, valid अगर distance is below 2^(31)
 *  https://en.wikipedia.org/wiki/Serial_number_arithmetic#General_Solution
 */
#घोषणा _distance(a, b)	(s32)((a) - (b))

अटल s32 page_pool_inflight(काष्ठा page_pool *pool)
अणु
	u32 release_cnt = atomic_पढ़ो(&pool->pages_state_release_cnt);
	u32 hold_cnt = READ_ONCE(pool->pages_state_hold_cnt);
	s32 inflight;

	inflight = _distance(hold_cnt, release_cnt);

	trace_page_pool_release(pool, inflight, hold_cnt, release_cnt);
	WARN(inflight < 0, "Negative(%d) inflight packet-pages", inflight);

	वापस inflight;
पूर्ण

/* Disconnects a page (from a page_pool).  API users can have a need
 * to disconnect a page (from a page_pool), to allow it to be used as
 * a regular page (that will eventually be वापसed to the normal
 * page-allocator via put_page).
 */
व्योम page_pool_release_page(काष्ठा page_pool *pool, काष्ठा page *page)
अणु
	dma_addr_t dma;
	पूर्णांक count;

	अगर (!(pool->p.flags & PP_FLAG_DMA_MAP))
		/* Always account क्रम inflight pages, even अगर we didn't
		 * map them
		 */
		जाओ skip_dma_unmap;

	dma = page_pool_get_dma_addr(page);

	/* When page is unmapped, it cannot be वापसed to our pool */
	dma_unmap_page_attrs(pool->p.dev, dma,
			     PAGE_SIZE << pool->p.order, pool->p.dma_dir,
			     DMA_ATTR_SKIP_CPU_SYNC);
	page_pool_set_dma_addr(page, 0);
skip_dma_unmap:
	/* This may be the last page वापसed, releasing the pool, so
	 * it is not safe to reference pool afterwards.
	 */
	count = atomic_inc_वापस(&pool->pages_state_release_cnt);
	trace_page_pool_state_release(pool, page, count);
पूर्ण
EXPORT_SYMBOL(page_pool_release_page);

/* Return a page to the page allocator, cleaning up our state */
अटल व्योम page_pool_वापस_page(काष्ठा page_pool *pool, काष्ठा page *page)
अणु
	page_pool_release_page(pool, page);

	put_page(page);
	/* An optimization would be to call __मुक्त_pages(page, pool->p.order)
	 * knowing page is not part of page-cache (thus aव्योमing a
	 * __page_cache_release() call).
	 */
पूर्ण

अटल bool page_pool_recycle_in_ring(काष्ठा page_pool *pool, काष्ठा page *page)
अणु
	पूर्णांक ret;
	/* BH protection not needed अगर current is serving softirq */
	अगर (in_serving_softirq())
		ret = ptr_ring_produce(&pool->ring, page);
	अन्यथा
		ret = ptr_ring_produce_bh(&pool->ring, page);

	वापस (ret == 0) ? true : false;
पूर्ण

/* Only allow direct recycling in special circumstances, पूर्णांकo the
 * alloc side cache.  E.g. during RX-NAPI processing क्रम XDP_DROP use-हाल.
 *
 * Caller must provide appropriate safe context.
 */
अटल bool page_pool_recycle_in_cache(काष्ठा page *page,
				       काष्ठा page_pool *pool)
अणु
	अगर (unlikely(pool->alloc.count == PP_ALLOC_CACHE_SIZE))
		वापस false;

	/* Caller MUST have verअगरied/know (page_ref_count(page) == 1) */
	pool->alloc.cache[pool->alloc.count++] = page;
	वापस true;
पूर्ण

/* If the page refcnt == 1, this will try to recycle the page.
 * अगर PP_FLAG_DMA_SYNC_DEV is set, we'll try to sync the DMA area क्रम
 * the configured size min(dma_sync_size, pool->max_len).
 * If the page refcnt != 1, then the page will be वापसed to memory
 * subप्रणाली.
 */
अटल __always_अंतरभूत काष्ठा page *
__page_pool_put_page(काष्ठा page_pool *pool, काष्ठा page *page,
		     अचिन्हित पूर्णांक dma_sync_size, bool allow_direct)
अणु
	/* This allocator is optimized क्रम the XDP mode that uses
	 * one-frame-per-page, but have fallbacks that act like the
	 * regular page allocator APIs.
	 *
	 * refcnt == 1 means page_pool owns page, and can recycle it.
	 *
	 * page is NOT reusable when allocated when प्रणाली is under
	 * some pressure. (page_is_pfmeदो_स्मृति)
	 */
	अगर (likely(page_ref_count(page) == 1 && !page_is_pfmeदो_स्मृति(page))) अणु
		/* Read barrier करोne in page_ref_count / READ_ONCE */

		अगर (pool->p.flags & PP_FLAG_DMA_SYNC_DEV)
			page_pool_dma_sync_क्रम_device(pool, page,
						      dma_sync_size);

		अगर (allow_direct && in_serving_softirq() &&
		    page_pool_recycle_in_cache(page, pool))
			वापस शून्य;

		/* Page found as candidate क्रम recycling */
		वापस page;
	पूर्ण
	/* Fallback/non-XDP mode: API user have elevated refcnt.
	 *
	 * Many drivers split up the page पूर्णांकo fragments, and some
	 * want to keep करोing this to save memory and करो refcnt based
	 * recycling. Support this use हाल too, to ease drivers
	 * चयनing between XDP/non-XDP.
	 *
	 * In-हाल page_pool मुख्यtains the DMA mapping, API user must
	 * call page_pool_put_page once.  In this elevated refcnt
	 * हाल, the DMA is unmapped/released, as driver is likely
	 * करोing refcnt based recycle tricks, meaning another process
	 * will be invoking put_page.
	 */
	/* Do not replace this with page_pool_वापस_page() */
	page_pool_release_page(pool, page);
	put_page(page);

	वापस शून्य;
पूर्ण

व्योम page_pool_put_page(काष्ठा page_pool *pool, काष्ठा page *page,
			अचिन्हित पूर्णांक dma_sync_size, bool allow_direct)
अणु
	page = __page_pool_put_page(pool, page, dma_sync_size, allow_direct);
	अगर (page && !page_pool_recycle_in_ring(pool, page)) अणु
		/* Cache full, fallback to मुक्त pages */
		page_pool_वापस_page(pool, page);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(page_pool_put_page);

/* Caller must not use data area after call, as this function overग_लिखोs it */
व्योम page_pool_put_page_bulk(काष्ठा page_pool *pool, व्योम **data,
			     पूर्णांक count)
अणु
	पूर्णांक i, bulk_len = 0;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा page *page = virt_to_head_page(data[i]);

		page = __page_pool_put_page(pool, page, -1, false);
		/* Approved क्रम bulk recycling in ptr_ring cache */
		अगर (page)
			data[bulk_len++] = page;
	पूर्ण

	अगर (unlikely(!bulk_len))
		वापस;

	/* Bulk producer पूर्णांकo ptr_ring page_pool cache */
	page_pool_ring_lock(pool);
	क्रम (i = 0; i < bulk_len; i++) अणु
		अगर (__ptr_ring_produce(&pool->ring, data[i]))
			अवरोध; /* ring full */
	पूर्ण
	page_pool_ring_unlock(pool);

	/* Hopefully all pages was वापस पूर्णांकo ptr_ring */
	अगर (likely(i == bulk_len))
		वापस;

	/* ptr_ring cache full, मुक्त reमुख्यing pages outside producer lock
	 * since put_page() with refcnt == 1 can be an expensive operation
	 */
	क्रम (; i < bulk_len; i++)
		page_pool_वापस_page(pool, data[i]);
पूर्ण
EXPORT_SYMBOL(page_pool_put_page_bulk);

अटल व्योम page_pool_empty_ring(काष्ठा page_pool *pool)
अणु
	काष्ठा page *page;

	/* Empty recycle ring */
	जबतक ((page = ptr_ring_consume_bh(&pool->ring))) अणु
		/* Verअगरy the refcnt invariant of cached pages */
		अगर (!(page_ref_count(page) == 1))
			pr_crit("%s() page_pool refcnt %d violation\n",
				__func__, page_ref_count(page));

		page_pool_वापस_page(pool, page);
	पूर्ण
पूर्ण

अटल व्योम page_pool_मुक्त(काष्ठा page_pool *pool)
अणु
	अगर (pool->disconnect)
		pool->disconnect(pool);

	ptr_ring_cleanup(&pool->ring, शून्य);

	अगर (pool->p.flags & PP_FLAG_DMA_MAP)
		put_device(pool->p.dev);

	kमुक्त(pool);
पूर्ण

अटल व्योम page_pool_empty_alloc_cache_once(काष्ठा page_pool *pool)
अणु
	काष्ठा page *page;

	अगर (pool->destroy_cnt)
		वापस;

	/* Empty alloc cache, assume caller made sure this is
	 * no-दीर्घer in use, and page_pool_alloc_pages() cannot be
	 * call concurrently.
	 */
	जबतक (pool->alloc.count) अणु
		page = pool->alloc.cache[--pool->alloc.count];
		page_pool_वापस_page(pool, page);
	पूर्ण
पूर्ण

अटल व्योम page_pool_scrub(काष्ठा page_pool *pool)
अणु
	page_pool_empty_alloc_cache_once(pool);
	pool->destroy_cnt++;

	/* No more consumers should exist, but producers could still
	 * be in-flight.
	 */
	page_pool_empty_ring(pool);
पूर्ण

अटल पूर्णांक page_pool_release(काष्ठा page_pool *pool)
अणु
	पूर्णांक inflight;

	page_pool_scrub(pool);
	inflight = page_pool_inflight(pool);
	अगर (!inflight)
		page_pool_मुक्त(pool);

	वापस inflight;
पूर्ण

अटल व्योम page_pool_release_retry(काष्ठा work_काष्ठा *wq)
अणु
	काष्ठा delayed_work *dwq = to_delayed_work(wq);
	काष्ठा page_pool *pool = container_of(dwq, typeof(*pool), release_dw);
	पूर्णांक inflight;

	inflight = page_pool_release(pool);
	अगर (!inflight)
		वापस;

	/* Periodic warning */
	अगर (समय_after_eq(jअगरfies, pool->defer_warn)) अणु
		पूर्णांक sec = (s32)((u32)jअगरfies - (u32)pool->defer_start) / HZ;

		pr_warn("%s() stalled pool shutdown %d inflight %d sec\n",
			__func__, inflight, sec);
		pool->defer_warn = jअगरfies + DEFER_WARN_INTERVAL;
	पूर्ण

	/* Still not पढ़ोy to be disconnected, retry later */
	schedule_delayed_work(&pool->release_dw, DEFER_TIME);
पूर्ण

व्योम page_pool_use_xdp_mem(काष्ठा page_pool *pool, व्योम (*disconnect)(व्योम *))
अणु
	refcount_inc(&pool->user_cnt);
	pool->disconnect = disconnect;
पूर्ण

व्योम page_pool_destroy(काष्ठा page_pool *pool)
अणु
	अगर (!pool)
		वापस;

	अगर (!page_pool_put(pool))
		वापस;

	अगर (!page_pool_release(pool))
		वापस;

	pool->defer_start = jअगरfies;
	pool->defer_warn  = jअगरfies + DEFER_WARN_INTERVAL;

	INIT_DELAYED_WORK(&pool->release_dw, page_pool_release_retry);
	schedule_delayed_work(&pool->release_dw, DEFER_TIME);
पूर्ण
EXPORT_SYMBOL(page_pool_destroy);

/* Caller must provide appropriate safe context, e.g. NAPI. */
व्योम page_pool_update_nid(काष्ठा page_pool *pool, पूर्णांक new_nid)
अणु
	काष्ठा page *page;

	trace_page_pool_update_nid(pool, new_nid);
	pool->p.nid = new_nid;

	/* Flush pool alloc cache, as refill will check NUMA node */
	जबतक (pool->alloc.count) अणु
		page = pool->alloc.cache[--pool->alloc.count];
		page_pool_वापस_page(pool, page);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(page_pool_update_nid);
