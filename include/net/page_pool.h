<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * page_pool.h
 *	Author:	Jesper Dangaard Brouer <netoptimizer@brouer.com>
 *	Copyright (C) 2016 Red Hat, Inc.
 */

/**
 * DOC: page_pool allocator
 *
 * This page_pool allocator is optimized क्रम the XDP mode that
 * uses one-frame-per-page, but have fallbacks that act like the
 * regular page allocator APIs.
 *
 * Basic use involve replacing alloc_pages() calls with the
 * page_pool_alloc_pages() call.  Drivers should likely use
 * page_pool_dev_alloc_pages() replacing dev_alloc_pages().
 *
 * API keeps track of in-flight pages, in-order to let API user know
 * when it is safe to dealloactor page_pool object.  Thus, API users
 * must make sure to call page_pool_release_page() when a page is
 * "leaving" the page_pool.  Or call page_pool_put_page() where
 * appropiate.  For मुख्यtaining correct accounting.
 *
 * API user must only call page_pool_put_page() once on a page, as it
 * will either recycle the page, or in हाल of elevated refcnt, it
 * will release the DMA mapping and in-flight state accounting.  We
 * hope to lअगरt this requirement in the future.
 */
#अगर_अघोषित _NET_PAGE_POOL_H
#घोषणा _NET_PAGE_POOL_H

#समावेश <linux/mm.h> /* Needed by ptr_ring */
#समावेश <linux/ptr_ring.h>
#समावेश <linux/dma-direction.h>

#घोषणा PP_FLAG_DMA_MAP		BIT(0) /* Should page_pool करो the DMA
					* map/unmap
					*/
#घोषणा PP_FLAG_DMA_SYNC_DEV	BIT(1) /* If set all pages that the driver माला_लो
					* from page_pool will be
					* DMA-synced-क्रम-device according to
					* the length provided by the device
					* driver.
					* Please note DMA-sync-क्रम-CPU is still
					* device driver responsibility
					*/
#घोषणा PP_FLAG_ALL		(PP_FLAG_DMA_MAP | PP_FLAG_DMA_SYNC_DEV)

/*
 * Fast allocation side cache array/stack
 *
 * The cache size and refill watermark is related to the network
 * use-हाल.  The NAPI budget is 64 packets.  After a NAPI poll the RX
 * ring is usually refilled and the max consumed elements will be 64,
 * thus a natural max size of objects needed in the cache.
 *
 * Keeping room क्रम more objects, is due to XDP_DROP use-हाल.  As
 * XDP_DROP allows the opportunity to recycle objects directly पूर्णांकo
 * this array, as it shares the same softirq/NAPI protection.  If
 * cache is alपढ़ोy full (or partly full) then the XDP_DROP recycles
 * would have to take a slower code path.
 */
#घोषणा PP_ALLOC_CACHE_SIZE	128
#घोषणा PP_ALLOC_CACHE_REFILL	64
काष्ठा pp_alloc_cache अणु
	u32 count;
	काष्ठा page *cache[PP_ALLOC_CACHE_SIZE];
पूर्ण;

काष्ठा page_pool_params अणु
	अचिन्हित पूर्णांक	flags;
	अचिन्हित पूर्णांक	order;
	अचिन्हित पूर्णांक	pool_size;
	पूर्णांक		nid;  /* Numa node id to allocate from pages from */
	काष्ठा device	*dev; /* device, क्रम DMA pre-mapping purposes */
	क्रमागत dma_data_direction dma_dir; /* DMA mapping direction */
	अचिन्हित पूर्णांक	max_len; /* max DMA sync memory size */
	अचिन्हित पूर्णांक	offset;  /* DMA addr offset */
पूर्ण;

काष्ठा page_pool अणु
	काष्ठा page_pool_params p;

	काष्ठा delayed_work release_dw;
	व्योम (*disconnect)(व्योम *);
	अचिन्हित दीर्घ defer_start;
	अचिन्हित दीर्घ defer_warn;

	u32 pages_state_hold_cnt;

	/*
	 * Data काष्ठाure क्रम allocation side
	 *
	 * Drivers allocation side usually alपढ़ोy perक्रमm some kind
	 * of resource protection.  Piggyback on this protection, and
	 * require driver to protect allocation side.
	 *
	 * For NIC drivers this means, allocate a page_pool per
	 * RX-queue. As the RX-queue is alपढ़ोy रक्षित by
	 * Softirq/BH scheduling and napi_schedule. NAPI schedule
	 * guarantee that a single napi_काष्ठा will only be scheduled
	 * on a single CPU (see napi_schedule).
	 */
	काष्ठा pp_alloc_cache alloc ____cacheline_aligned_in_smp;

	/* Data काष्ठाure क्रम storing recycled pages.
	 *
	 * Returning/मुक्तing pages is more complicated synchronization
	 * wise, because मुक्त's can happen on remote CPUs, with no
	 * association with allocation resource.
	 *
	 * Use ptr_ring, as it separates consumer and producer
	 * effeciently, it a way that करोesn't bounce cache-lines.
	 *
	 * TODO: Implement bulk वापस pages पूर्णांकo this काष्ठाure.
	 */
	काष्ठा ptr_ring ring;

	atomic_t pages_state_release_cnt;

	/* A page_pool is strictly tied to a single RX-queue being
	 * रक्षित by NAPI, due to above pp_alloc_cache. This
	 * refcnt serves purpose is to simplअगरy drivers error handling.
	 */
	refcount_t user_cnt;

	u64 destroy_cnt;
पूर्ण;

काष्ठा page *page_pool_alloc_pages(काष्ठा page_pool *pool, gfp_t gfp);

अटल अंतरभूत काष्ठा page *page_pool_dev_alloc_pages(काष्ठा page_pool *pool)
अणु
	gfp_t gfp = (GFP_ATOMIC | __GFP_NOWARN);

	वापस page_pool_alloc_pages(pool, gfp);
पूर्ण

/* get the stored dma direction. A driver might decide to treat this locally and
 * aव्योम the extra cache line from page_pool to determine the direction
 */
अटल
अंतरभूत क्रमागत dma_data_direction page_pool_get_dma_dir(काष्ठा page_pool *pool)
अणु
	वापस pool->p.dma_dir;
पूर्ण

काष्ठा page_pool *page_pool_create(स्थिर काष्ठा page_pool_params *params);

#अगर_घोषित CONFIG_PAGE_POOL
व्योम page_pool_destroy(काष्ठा page_pool *pool);
व्योम page_pool_use_xdp_mem(काष्ठा page_pool *pool, व्योम (*disconnect)(व्योम *));
व्योम page_pool_release_page(काष्ठा page_pool *pool, काष्ठा page *page);
व्योम page_pool_put_page_bulk(काष्ठा page_pool *pool, व्योम **data,
			     पूर्णांक count);
#अन्यथा
अटल अंतरभूत व्योम page_pool_destroy(काष्ठा page_pool *pool)
अणु
पूर्ण

अटल अंतरभूत व्योम page_pool_use_xdp_mem(काष्ठा page_pool *pool,
					 व्योम (*disconnect)(व्योम *))
अणु
पूर्ण
अटल अंतरभूत व्योम page_pool_release_page(काष्ठा page_pool *pool,
					  काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत व्योम page_pool_put_page_bulk(काष्ठा page_pool *pool, व्योम **data,
					   पूर्णांक count)
अणु
पूर्ण
#पूर्ण_अगर

व्योम page_pool_put_page(काष्ठा page_pool *pool, काष्ठा page *page,
			अचिन्हित पूर्णांक dma_sync_size, bool allow_direct);

/* Same as above but will try to sync the entire area pool->max_len */
अटल अंतरभूत व्योम page_pool_put_full_page(काष्ठा page_pool *pool,
					   काष्ठा page *page, bool allow_direct)
अणु
	/* When page_pool isn't compiled-in, net/core/xdp.c doesn't
	 * allow रेजिस्टरing MEM_TYPE_PAGE_POOL, but shield linker.
	 */
#अगर_घोषित CONFIG_PAGE_POOL
	page_pool_put_page(pool, page, -1, allow_direct);
#पूर्ण_अगर
पूर्ण

/* Same as above but the caller must guarantee safe context. e.g NAPI */
अटल अंतरभूत व्योम page_pool_recycle_direct(काष्ठा page_pool *pool,
					    काष्ठा page *page)
अणु
	page_pool_put_full_page(pool, page, true);
पूर्ण

अटल अंतरभूत dma_addr_t page_pool_get_dma_addr(काष्ठा page *page)
अणु
	dma_addr_t ret = page->dma_addr[0];
	अगर (माप(dma_addr_t) > माप(अचिन्हित दीर्घ))
		ret |= (dma_addr_t)page->dma_addr[1] << 16 << 16;
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम page_pool_set_dma_addr(काष्ठा page *page, dma_addr_t addr)
अणु
	page->dma_addr[0] = addr;
	अगर (माप(dma_addr_t) > माप(अचिन्हित दीर्घ))
		page->dma_addr[1] = upper_32_bits(addr);
पूर्ण

अटल अंतरभूत bool is_page_pool_compiled_in(व्योम)
अणु
#अगर_घोषित CONFIG_PAGE_POOL
	वापस true;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool page_pool_put(काष्ठा page_pool *pool)
अणु
	वापस refcount_dec_and_test(&pool->user_cnt);
पूर्ण

/* Caller must provide appropriate safe context, e.g. NAPI. */
व्योम page_pool_update_nid(काष्ठा page_pool *pool, पूर्णांक new_nid);
अटल अंतरभूत व्योम page_pool_nid_changed(काष्ठा page_pool *pool, पूर्णांक new_nid)
अणु
	अगर (unlikely(pool->p.nid != new_nid))
		page_pool_update_nid(pool, new_nid);
पूर्ण

अटल अंतरभूत व्योम page_pool_ring_lock(काष्ठा page_pool *pool)
	__acquires(&pool->ring.producer_lock)
अणु
	अगर (in_serving_softirq())
		spin_lock(&pool->ring.producer_lock);
	अन्यथा
		spin_lock_bh(&pool->ring.producer_lock);
पूर्ण

अटल अंतरभूत व्योम page_pool_ring_unlock(काष्ठा page_pool *pool)
	__releases(&pool->ring.producer_lock)
अणु
	अगर (in_serving_softirq())
		spin_unlock(&pool->ring.producer_lock);
	अन्यथा
		spin_unlock_bh(&pool->ring.producer_lock);
पूर्ण

#पूर्ण_अगर /* _NET_PAGE_POOL_H */
