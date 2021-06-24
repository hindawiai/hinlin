<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * zbud.c
 *
 * Copyright (C) 2013, Seth Jennings, IBM
 *
 * Concepts based on zcache पूर्णांकernal zbud allocator by Dan Magenheimer.
 *
 * zbud is an special purpose allocator क्रम storing compressed pages.  Contrary
 * to what its name may suggest, zbud is not a buddy allocator, but rather an
 * allocator that "buddies" two compressed pages together in a single memory
 * page.
 *
 * While this design limits storage density, it has simple and deterministic
 * reclaim properties that make it preferable to a higher density approach when
 * reclaim will be used.
 *
 * zbud works by storing compressed pages, or "zpages", together in pairs in a
 * single memory page called a "zbud page".  The first buddy is "left
 * justअगरied" at the beginning of the zbud page, and the last buddy is "right
 * justअगरied" at the end of the zbud page.  The benefit is that अगर either
 * buddy is मुक्तd, the मुक्तd buddy space, coalesced with whatever slack space
 * that existed between the buddies, results in the largest possible मुक्त region
 * within the zbud page.
 *
 * zbud also provides an attractive lower bound on density. The ratio of zpages
 * to zbud pages can not be less than 1.  This ensures that zbud can never "करो
 * harm" by using more pages to store zpages than the uncompressed zpages would
 * have used on their own.
 *
 * zbud pages are भागided पूर्णांकo "chunks".  The size of the chunks is fixed at
 * compile समय and determined by NCHUNKS_ORDER below.  Dividing zbud pages
 * पूर्णांकo chunks allows organizing unbuddied zbud pages पूर्णांकo a manageable number
 * of unbuddied lists according to the number of मुक्त chunks available in the
 * zbud page.
 *
 * The zbud API dअगरfers from that of conventional allocators in that the
 * allocation function, zbud_alloc(), वापसs an opaque handle to the user,
 * not a dereferenceable poपूर्णांकer.  The user must map the handle using
 * zbud_map() in order to get a usable poपूर्णांकer by which to access the
 * allocation data and unmap the handle with zbud_unmap() when operations
 * on the allocation data are complete.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/atomic.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/preempt.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/zbud.h>
#समावेश <linux/zpool.h>

/*****************
 * Structures
*****************/
/*
 * NCHUNKS_ORDER determines the पूर्णांकernal allocation granularity, effectively
 * adjusting पूर्णांकernal fragmentation.  It also determines the number of
 * मुक्तlists मुख्यtained in each pool. NCHUNKS_ORDER of 6 means that the
 * allocation granularity will be in chunks of size PAGE_SIZE/64. As one chunk
 * in allocated page is occupied by zbud header, NCHUNKS will be calculated to
 * 63 which shows the max number of मुक्त chunks in zbud page, also there will be
 * 63 मुक्तlists per pool.
 */
#घोषणा NCHUNKS_ORDER	6

#घोषणा CHUNK_SHIFT	(PAGE_SHIFT - NCHUNKS_ORDER)
#घोषणा CHUNK_SIZE	(1 << CHUNK_SHIFT)
#घोषणा ZHDR_SIZE_ALIGNED CHUNK_SIZE
#घोषणा NCHUNKS		((PAGE_SIZE - ZHDR_SIZE_ALIGNED) >> CHUNK_SHIFT)

/**
 * काष्ठा zbud_pool - stores metadata क्रम each zbud pool
 * @lock:	protects all pool fields and first|last_chunk fields of any
 *		zbud page in the pool
 * @unbuddied:	array of lists tracking zbud pages that only contain one buddy;
 *		the lists each zbud page is added to depends on the size of
 *		its मुक्त region.
 * @buddied:	list tracking the zbud pages that contain two buddies;
 *		these zbud pages are full
 * @lru:	list tracking the zbud pages in LRU order by most recently
 *		added buddy.
 * @pages_nr:	number of zbud pages in the pool.
 * @ops:	poपूर्णांकer to a काष्ठाure of user defined operations specअगरied at
 *		pool creation समय.
 *
 * This काष्ठाure is allocated at pool creation समय and मुख्यtains metadata
 * pertaining to a particular zbud pool.
 */
काष्ठा zbud_pool अणु
	spinlock_t lock;
	काष्ठा list_head unbuddied[NCHUNKS];
	काष्ठा list_head buddied;
	काष्ठा list_head lru;
	u64 pages_nr;
	स्थिर काष्ठा zbud_ops *ops;
#अगर_घोषित CONFIG_ZPOOL
	काष्ठा zpool *zpool;
	स्थिर काष्ठा zpool_ops *zpool_ops;
#पूर्ण_अगर
पूर्ण;

/*
 * काष्ठा zbud_header - zbud page metadata occupying the first chunk of each
 *			zbud page.
 * @buddy:	links the zbud page पूर्णांकo the unbuddied/buddied lists in the pool
 * @lru:	links the zbud page पूर्णांकo the lru list in the pool
 * @first_chunks:	the size of the first buddy in chunks, 0 अगर मुक्त
 * @last_chunks:	the size of the last buddy in chunks, 0 अगर मुक्त
 */
काष्ठा zbud_header अणु
	काष्ठा list_head buddy;
	काष्ठा list_head lru;
	अचिन्हित पूर्णांक first_chunks;
	अचिन्हित पूर्णांक last_chunks;
	bool under_reclaim;
पूर्ण;

/*****************
 * zpool
 ****************/

#अगर_घोषित CONFIG_ZPOOL

अटल पूर्णांक zbud_zpool_evict(काष्ठा zbud_pool *pool, अचिन्हित दीर्घ handle)
अणु
	अगर (pool->zpool && pool->zpool_ops && pool->zpool_ops->evict)
		वापस pool->zpool_ops->evict(pool->zpool, handle);
	अन्यथा
		वापस -ENOENT;
पूर्ण

अटल स्थिर काष्ठा zbud_ops zbud_zpool_ops = अणु
	.evict =	zbud_zpool_evict
पूर्ण;

अटल व्योम *zbud_zpool_create(स्थिर अक्षर *name, gfp_t gfp,
			       स्थिर काष्ठा zpool_ops *zpool_ops,
			       काष्ठा zpool *zpool)
अणु
	काष्ठा zbud_pool *pool;

	pool = zbud_create_pool(gfp, zpool_ops ? &zbud_zpool_ops : शून्य);
	अगर (pool) अणु
		pool->zpool = zpool;
		pool->zpool_ops = zpool_ops;
	पूर्ण
	वापस pool;
पूर्ण

अटल व्योम zbud_zpool_destroy(व्योम *pool)
अणु
	zbud_destroy_pool(pool);
पूर्ण

अटल पूर्णांक zbud_zpool_दो_स्मृति(व्योम *pool, माप_प्रकार size, gfp_t gfp,
			अचिन्हित दीर्घ *handle)
अणु
	वापस zbud_alloc(pool, size, gfp, handle);
पूर्ण
अटल व्योम zbud_zpool_मुक्त(व्योम *pool, अचिन्हित दीर्घ handle)
अणु
	zbud_मुक्त(pool, handle);
पूर्ण

अटल पूर्णांक zbud_zpool_shrink(व्योम *pool, अचिन्हित पूर्णांक pages,
			अचिन्हित पूर्णांक *reclaimed)
अणु
	अचिन्हित पूर्णांक total = 0;
	पूर्णांक ret = -EINVAL;

	जबतक (total < pages) अणु
		ret = zbud_reclaim_page(pool, 8);
		अगर (ret < 0)
			अवरोध;
		total++;
	पूर्ण

	अगर (reclaimed)
		*reclaimed = total;

	वापस ret;
पूर्ण

अटल व्योम *zbud_zpool_map(व्योम *pool, अचिन्हित दीर्घ handle,
			क्रमागत zpool_mapmode mm)
अणु
	वापस zbud_map(pool, handle);
पूर्ण
अटल व्योम zbud_zpool_unmap(व्योम *pool, अचिन्हित दीर्घ handle)
अणु
	zbud_unmap(pool, handle);
पूर्ण

अटल u64 zbud_zpool_total_size(व्योम *pool)
अणु
	वापस zbud_get_pool_size(pool) * PAGE_SIZE;
पूर्ण

अटल काष्ठा zpool_driver zbud_zpool_driver = अणु
	.type =		"zbud",
	.sleep_mapped = true,
	.owner =	THIS_MODULE,
	.create =	zbud_zpool_create,
	.destroy =	zbud_zpool_destroy,
	.दो_स्मृति =	zbud_zpool_दो_स्मृति,
	.मुक्त =		zbud_zpool_मुक्त,
	.shrink =	zbud_zpool_shrink,
	.map =		zbud_zpool_map,
	.unmap =	zbud_zpool_unmap,
	.total_size =	zbud_zpool_total_size,
पूर्ण;

MODULE_ALIAS("zpool-zbud");
#पूर्ण_अगर /* CONFIG_ZPOOL */

/*****************
 * Helpers
*****************/
/* Just to make the code easier to पढ़ो */
क्रमागत buddy अणु
	FIRST,
	LAST
पूर्ण;

/* Converts an allocation size in bytes to size in zbud chunks */
अटल पूर्णांक माप_प्रकारo_chunks(माप_प्रकार size)
अणु
	वापस (size + CHUNK_SIZE - 1) >> CHUNK_SHIFT;
पूर्ण

#घोषणा क्रम_each_unbuddied_list(_iter, _begin) \
	क्रम ((_iter) = (_begin); (_iter) < NCHUNKS; (_iter)++)

/* Initializes the zbud header of a newly allocated zbud page */
अटल काष्ठा zbud_header *init_zbud_page(काष्ठा page *page)
अणु
	काष्ठा zbud_header *zhdr = page_address(page);
	zhdr->first_chunks = 0;
	zhdr->last_chunks = 0;
	INIT_LIST_HEAD(&zhdr->buddy);
	INIT_LIST_HEAD(&zhdr->lru);
	zhdr->under_reclaim = false;
	वापस zhdr;
पूर्ण

/* Resets the काष्ठा page fields and मुक्तs the page */
अटल व्योम मुक्त_zbud_page(काष्ठा zbud_header *zhdr)
अणु
	__मुक्त_page(virt_to_page(zhdr));
पूर्ण

/*
 * Encodes the handle of a particular buddy within a zbud page
 * Pool lock should be held as this function accesses first|last_chunks
 */
अटल अचिन्हित दीर्घ encode_handle(काष्ठा zbud_header *zhdr, क्रमागत buddy bud)
अणु
	अचिन्हित दीर्घ handle;

	/*
	 * For now, the encoded handle is actually just the poपूर्णांकer to the data
	 * but this might not always be the हाल.  A little inक्रमmation hiding.
	 * Add CHUNK_SIZE to the handle अगर it is the first allocation to jump
	 * over the zbud header in the first chunk.
	 */
	handle = (अचिन्हित दीर्घ)zhdr;
	अगर (bud == FIRST)
		/* skip over zbud header */
		handle += ZHDR_SIZE_ALIGNED;
	अन्यथा /* bud == LAST */
		handle += PAGE_SIZE - (zhdr->last_chunks  << CHUNK_SHIFT);
	वापस handle;
पूर्ण

/* Returns the zbud page where a given handle is stored */
अटल काष्ठा zbud_header *handle_to_zbud_header(अचिन्हित दीर्घ handle)
अणु
	वापस (काष्ठा zbud_header *)(handle & PAGE_MASK);
पूर्ण

/* Returns the number of मुक्त chunks in a zbud page */
अटल पूर्णांक num_मुक्त_chunks(काष्ठा zbud_header *zhdr)
अणु
	/*
	 * Rather than branch क्रम dअगरferent situations, just use the fact that
	 * मुक्त buddies have a length of zero to simplअगरy everything.
	 */
	वापस NCHUNKS - zhdr->first_chunks - zhdr->last_chunks;
पूर्ण

/*****************
 * API Functions
*****************/
/**
 * zbud_create_pool() - create a new zbud pool
 * @gfp:	gfp flags when allocating the zbud pool काष्ठाure
 * @ops:	user-defined operations क्रम the zbud pool
 *
 * Return: poपूर्णांकer to the new zbud pool or शून्य अगर the metadata allocation
 * failed.
 */
काष्ठा zbud_pool *zbud_create_pool(gfp_t gfp, स्थिर काष्ठा zbud_ops *ops)
अणु
	काष्ठा zbud_pool *pool;
	पूर्णांक i;

	pool = kzalloc(माप(काष्ठा zbud_pool), gfp);
	अगर (!pool)
		वापस शून्य;
	spin_lock_init(&pool->lock);
	क्रम_each_unbuddied_list(i, 0)
		INIT_LIST_HEAD(&pool->unbuddied[i]);
	INIT_LIST_HEAD(&pool->buddied);
	INIT_LIST_HEAD(&pool->lru);
	pool->pages_nr = 0;
	pool->ops = ops;
	वापस pool;
पूर्ण

/**
 * zbud_destroy_pool() - destroys an existing zbud pool
 * @pool:	the zbud pool to be destroyed
 *
 * The pool should be emptied beक्रमe this function is called.
 */
व्योम zbud_destroy_pool(काष्ठा zbud_pool *pool)
अणु
	kमुक्त(pool);
पूर्ण

/**
 * zbud_alloc() - allocates a region of a given size
 * @pool:	zbud pool from which to allocate
 * @size:	size in bytes of the desired allocation
 * @gfp:	gfp flags used अगर the pool needs to grow
 * @handle:	handle of the new allocation
 *
 * This function will attempt to find a मुक्त region in the pool large enough to
 * satisfy the allocation request.  A search of the unbuddied lists is
 * perक्रमmed first. If no suitable मुक्त region is found, then a new page is
 * allocated and added to the pool to satisfy the request.
 *
 * gfp should not set __GFP_HIGHMEM as highmem pages cannot be used
 * as zbud pool pages.
 *
 * Return: 0 अगर success and handle is set, otherwise -EINVAL अगर the size or
 * gfp arguments are invalid or -ENOMEM अगर the pool was unable to allocate
 * a new page.
 */
पूर्णांक zbud_alloc(काष्ठा zbud_pool *pool, माप_प्रकार size, gfp_t gfp,
			अचिन्हित दीर्घ *handle)
अणु
	पूर्णांक chunks, i, मुक्तchunks;
	काष्ठा zbud_header *zhdr = शून्य;
	क्रमागत buddy bud;
	काष्ठा page *page;

	अगर (!size || (gfp & __GFP_HIGHMEM))
		वापस -EINVAL;
	अगर (size > PAGE_SIZE - ZHDR_SIZE_ALIGNED - CHUNK_SIZE)
		वापस -ENOSPC;
	chunks = माप_प्रकारo_chunks(size);
	spin_lock(&pool->lock);

	/* First, try to find an unbuddied zbud page. */
	क्रम_each_unbuddied_list(i, chunks) अणु
		अगर (!list_empty(&pool->unbuddied[i])) अणु
			zhdr = list_first_entry(&pool->unbuddied[i],
					काष्ठा zbud_header, buddy);
			list_del(&zhdr->buddy);
			अगर (zhdr->first_chunks == 0)
				bud = FIRST;
			अन्यथा
				bud = LAST;
			जाओ found;
		पूर्ण
	पूर्ण

	/* Couldn't find unbuddied zbud page, create new one */
	spin_unlock(&pool->lock);
	page = alloc_page(gfp);
	अगर (!page)
		वापस -ENOMEM;
	spin_lock(&pool->lock);
	pool->pages_nr++;
	zhdr = init_zbud_page(page);
	bud = FIRST;

found:
	अगर (bud == FIRST)
		zhdr->first_chunks = chunks;
	अन्यथा
		zhdr->last_chunks = chunks;

	अगर (zhdr->first_chunks == 0 || zhdr->last_chunks == 0) अणु
		/* Add to unbuddied list */
		मुक्तchunks = num_मुक्त_chunks(zhdr);
		list_add(&zhdr->buddy, &pool->unbuddied[मुक्तchunks]);
	पूर्ण अन्यथा अणु
		/* Add to buddied list */
		list_add(&zhdr->buddy, &pool->buddied);
	पूर्ण

	/* Add/move zbud page to beginning of LRU */
	अगर (!list_empty(&zhdr->lru))
		list_del(&zhdr->lru);
	list_add(&zhdr->lru, &pool->lru);

	*handle = encode_handle(zhdr, bud);
	spin_unlock(&pool->lock);

	वापस 0;
पूर्ण

/**
 * zbud_मुक्त() - मुक्तs the allocation associated with the given handle
 * @pool:	pool in which the allocation resided
 * @handle:	handle associated with the allocation वापसed by zbud_alloc()
 *
 * In the हाल that the zbud page in which the allocation resides is under
 * reclaim, as indicated by the PG_reclaim flag being set, this function
 * only sets the first|last_chunks to 0.  The page is actually मुक्तd
 * once both buddies are evicted (see zbud_reclaim_page() below).
 */
व्योम zbud_मुक्त(काष्ठा zbud_pool *pool, अचिन्हित दीर्घ handle)
अणु
	काष्ठा zbud_header *zhdr;
	पूर्णांक मुक्तchunks;

	spin_lock(&pool->lock);
	zhdr = handle_to_zbud_header(handle);

	/* If first buddy, handle will be page aligned */
	अगर ((handle - ZHDR_SIZE_ALIGNED) & ~PAGE_MASK)
		zhdr->last_chunks = 0;
	अन्यथा
		zhdr->first_chunks = 0;

	अगर (zhdr->under_reclaim) अणु
		/* zbud page is under reclaim, reclaim will मुक्त */
		spin_unlock(&pool->lock);
		वापस;
	पूर्ण

	/* Remove from existing buddy list */
	list_del(&zhdr->buddy);

	अगर (zhdr->first_chunks == 0 && zhdr->last_chunks == 0) अणु
		/* zbud page is empty, मुक्त */
		list_del(&zhdr->lru);
		मुक्त_zbud_page(zhdr);
		pool->pages_nr--;
	पूर्ण अन्यथा अणु
		/* Add to unbuddied list */
		मुक्तchunks = num_मुक्त_chunks(zhdr);
		list_add(&zhdr->buddy, &pool->unbuddied[मुक्तchunks]);
	पूर्ण

	spin_unlock(&pool->lock);
पूर्ण

/**
 * zbud_reclaim_page() - evicts allocations from a pool page and मुक्तs it
 * @pool:	pool from which a page will attempt to be evicted
 * @retries:	number of pages on the LRU list क्रम which eviction will
 *		be attempted beक्रमe failing
 *
 * zbud reclaim is dअगरferent from normal प्रणाली reclaim in that the reclaim is
 * करोne from the bottom, up.  This is because only the bottom layer, zbud, has
 * inक्रमmation on how the allocations are organized within each zbud page. This
 * has the potential to create पूर्णांकeresting locking situations between zbud and
 * the user, however.
 *
 * To aव्योम these, this is how zbud_reclaim_page() should be called:
 *
 * The user detects a page should be reclaimed and calls zbud_reclaim_page().
 * zbud_reclaim_page() will हटाओ a zbud page from the pool LRU list and call
 * the user-defined eviction handler with the pool and handle as arguments.
 *
 * If the handle can not be evicted, the eviction handler should वापस
 * non-zero. zbud_reclaim_page() will add the zbud page back to the
 * appropriate list and try the next zbud page on the LRU up to
 * a user defined number of retries.
 *
 * If the handle is successfully evicted, the eviction handler should
 * वापस 0 _and_ should have called zbud_मुक्त() on the handle. zbud_मुक्त()
 * contains logic to delay मुक्तing the page अगर the page is under reclaim,
 * as indicated by the setting of the PG_reclaim flag on the underlying page.
 *
 * If all buddies in the zbud page are successfully evicted, then the
 * zbud page can be मुक्तd.
 *
 * Returns: 0 अगर page is successfully मुक्तd, otherwise -EINVAL अगर there are
 * no pages to evict or an eviction handler is not रेजिस्टरed, -EAGAIN अगर
 * the retry limit was hit.
 */
पूर्णांक zbud_reclaim_page(काष्ठा zbud_pool *pool, अचिन्हित पूर्णांक retries)
अणु
	पूर्णांक i, ret, मुक्तchunks;
	काष्ठा zbud_header *zhdr;
	अचिन्हित दीर्घ first_handle = 0, last_handle = 0;

	spin_lock(&pool->lock);
	अगर (!pool->ops || !pool->ops->evict || list_empty(&pool->lru) ||
			retries == 0) अणु
		spin_unlock(&pool->lock);
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < retries; i++) अणु
		zhdr = list_last_entry(&pool->lru, काष्ठा zbud_header, lru);
		list_del(&zhdr->lru);
		list_del(&zhdr->buddy);
		/* Protect zbud page against मुक्त */
		zhdr->under_reclaim = true;
		/*
		 * We need encode the handles beक्रमe unlocking, since we can
		 * race with मुक्त that will set (first|last)_chunks to 0
		 */
		first_handle = 0;
		last_handle = 0;
		अगर (zhdr->first_chunks)
			first_handle = encode_handle(zhdr, FIRST);
		अगर (zhdr->last_chunks)
			last_handle = encode_handle(zhdr, LAST);
		spin_unlock(&pool->lock);

		/* Issue the eviction callback(s) */
		अगर (first_handle) अणु
			ret = pool->ops->evict(pool, first_handle);
			अगर (ret)
				जाओ next;
		पूर्ण
		अगर (last_handle) अणु
			ret = pool->ops->evict(pool, last_handle);
			अगर (ret)
				जाओ next;
		पूर्ण
next:
		spin_lock(&pool->lock);
		zhdr->under_reclaim = false;
		अगर (zhdr->first_chunks == 0 && zhdr->last_chunks == 0) अणु
			/*
			 * Both buddies are now मुक्त, मुक्त the zbud page and
			 * वापस success.
			 */
			मुक्त_zbud_page(zhdr);
			pool->pages_nr--;
			spin_unlock(&pool->lock);
			वापस 0;
		पूर्ण अन्यथा अगर (zhdr->first_chunks == 0 ||
				zhdr->last_chunks == 0) अणु
			/* add to unbuddied list */
			मुक्तchunks = num_मुक्त_chunks(zhdr);
			list_add(&zhdr->buddy, &pool->unbuddied[मुक्तchunks]);
		पूर्ण अन्यथा अणु
			/* add to buddied list */
			list_add(&zhdr->buddy, &pool->buddied);
		पूर्ण

		/* add to beginning of LRU */
		list_add(&zhdr->lru, &pool->lru);
	पूर्ण
	spin_unlock(&pool->lock);
	वापस -EAGAIN;
पूर्ण

/**
 * zbud_map() - maps the allocation associated with the given handle
 * @pool:	pool in which the allocation resides
 * @handle:	handle associated with the allocation to be mapped
 *
 * While trivial क्रम zbud, the mapping functions क्रम others allocators
 * implementing this allocation API could have more complex inक्रमmation encoded
 * in the handle and could create temporary mappings to make the data
 * accessible to the user.
 *
 * Returns: a poपूर्णांकer to the mapped allocation
 */
व्योम *zbud_map(काष्ठा zbud_pool *pool, अचिन्हित दीर्घ handle)
अणु
	वापस (व्योम *)(handle);
पूर्ण

/**
 * zbud_unmap() - maps the allocation associated with the given handle
 * @pool:	pool in which the allocation resides
 * @handle:	handle associated with the allocation to be unmapped
 */
व्योम zbud_unmap(काष्ठा zbud_pool *pool, अचिन्हित दीर्घ handle)
अणु
पूर्ण

/**
 * zbud_get_pool_size() - माला_लो the zbud pool size in pages
 * @pool:	pool whose size is being queried
 *
 * Returns: size in pages of the given pool.  The pool lock need not be
 * taken to access pages_nr.
 */
u64 zbud_get_pool_size(काष्ठा zbud_pool *pool)
अणु
	वापस pool->pages_nr;
पूर्ण

अटल पूर्णांक __init init_zbud(व्योम)
अणु
	/* Make sure the zbud header will fit in one chunk */
	BUILD_BUG_ON(माप(काष्ठा zbud_header) > ZHDR_SIZE_ALIGNED);
	pr_info("loaded\n");

#अगर_घोषित CONFIG_ZPOOL
	zpool_रेजिस्टर_driver(&zbud_zpool_driver);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम __निकास निकास_zbud(व्योम)
अणु
#अगर_घोषित CONFIG_ZPOOL
	zpool_unरेजिस्टर_driver(&zbud_zpool_driver);
#पूर्ण_अगर

	pr_info("unloaded\n");
पूर्ण

module_init(init_zbud);
module_निकास(निकास_zbud);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Seth Jennings <sjennings@variantweb.net>");
MODULE_DESCRIPTION("Buddy Allocator for Compressed Pages");
