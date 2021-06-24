<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IOMMU mmap management and range allocation functions.
 * Based almost entirely upon the घातerpc iommu allocator.
 */

#समावेश <linux/export.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bug.h>
#समावेश <linux/iommu-helper.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/hash.h>
#समावेश <यंत्र/iommu-common.h>

अटल अचिन्हित दीर्घ iommu_large_alloc = 15;

अटल	DEFINE_PER_CPU(अचिन्हित पूर्णांक, iommu_hash_common);

अटल अंतरभूत bool need_flush(काष्ठा iommu_map_table *iommu)
अणु
	वापस ((iommu->flags & IOMMU_NEED_FLUSH) != 0);
पूर्ण

अटल अंतरभूत व्योम set_flush(काष्ठा iommu_map_table *iommu)
अणु
	iommu->flags |= IOMMU_NEED_FLUSH;
पूर्ण

अटल अंतरभूत व्योम clear_flush(काष्ठा iommu_map_table *iommu)
अणु
	iommu->flags &= ~IOMMU_NEED_FLUSH;
पूर्ण

अटल व्योम setup_iommu_pool_hash(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	अटल bool करो_once;

	अगर (करो_once)
		वापस;
	करो_once = true;
	क्रम_each_possible_cpu(i)
		per_cpu(iommu_hash_common, i) = hash_32(i, IOMMU_POOL_HASHBITS);
पूर्ण

/*
 * Initialize iommu_pool entries क्रम the iommu_map_table. `num_entries'
 * is the number of table entries. If `large_pool' is set to true,
 * the top 1/4 of the table will be set aside क्रम pool allocations
 * of more than iommu_large_alloc pages.
 */
व्योम iommu_tbl_pool_init(काष्ठा iommu_map_table *iommu,
			 अचिन्हित दीर्घ num_entries,
			 u32 table_shअगरt,
			 व्योम (*lazy_flush)(काष्ठा iommu_map_table *),
			 bool large_pool, u32 npools,
			 bool skip_span_boundary_check)
अणु
	अचिन्हित पूर्णांक start, i;
	काष्ठा iommu_pool *p = &(iommu->large_pool);

	setup_iommu_pool_hash();
	अगर (npools == 0)
		iommu->nr_pools = IOMMU_NR_POOLS;
	अन्यथा
		iommu->nr_pools = npools;
	BUG_ON(npools > IOMMU_NR_POOLS);

	iommu->table_shअगरt = table_shअगरt;
	iommu->lazy_flush = lazy_flush;
	start = 0;
	अगर (skip_span_boundary_check)
		iommu->flags |= IOMMU_NO_SPAN_BOUND;
	अगर (large_pool)
		iommu->flags |= IOMMU_HAS_LARGE_POOL;

	अगर (!large_pool)
		iommu->poolsize = num_entries/iommu->nr_pools;
	अन्यथा
		iommu->poolsize = (num_entries * 3 / 4)/iommu->nr_pools;
	क्रम (i = 0; i < iommu->nr_pools; i++) अणु
		spin_lock_init(&(iommu->pools[i].lock));
		iommu->pools[i].start = start;
		iommu->pools[i].hपूर्णांक = start;
		start += iommu->poolsize; /* start क्रम next pool */
		iommu->pools[i].end = start - 1;
	पूर्ण
	अगर (!large_pool)
		वापस;
	/* initialize large_pool */
	spin_lock_init(&(p->lock));
	p->start = start;
	p->hपूर्णांक = p->start;
	p->end = num_entries;
पूर्ण

अचिन्हित दीर्घ iommu_tbl_range_alloc(काष्ठा device *dev,
				काष्ठा iommu_map_table *iommu,
				अचिन्हित दीर्घ npages,
				अचिन्हित दीर्घ *handle,
				अचिन्हित दीर्घ mask,
				अचिन्हित पूर्णांक align_order)
अणु
	अचिन्हित पूर्णांक pool_hash = __this_cpu_पढ़ो(iommu_hash_common);
	अचिन्हित दीर्घ n, end, start, limit, boundary_size;
	काष्ठा iommu_pool *pool;
	पूर्णांक pass = 0;
	अचिन्हित पूर्णांक pool_nr;
	अचिन्हित पूर्णांक npools = iommu->nr_pools;
	अचिन्हित दीर्घ flags;
	bool large_pool = ((iommu->flags & IOMMU_HAS_LARGE_POOL) != 0);
	bool largealloc = (large_pool && npages > iommu_large_alloc);
	अचिन्हित दीर्घ shअगरt;
	अचिन्हित दीर्घ align_mask = 0;

	अगर (align_order > 0)
		align_mask = ~0ul >> (BITS_PER_LONG - align_order);

	/* Sanity check */
	अगर (unlikely(npages == 0)) अणु
		WARN_ON_ONCE(1);
		वापस IOMMU_ERROR_CODE;
	पूर्ण

	अगर (largealloc) अणु
		pool = &(iommu->large_pool);
		pool_nr = 0; /* to keep compiler happy */
	पूर्ण अन्यथा अणु
		/* pick out pool_nr */
		pool_nr =  pool_hash & (npools - 1);
		pool = &(iommu->pools[pool_nr]);
	पूर्ण
	spin_lock_irqsave(&pool->lock, flags);

 again:
	अगर (pass == 0 && handle && *handle &&
	    (*handle >= pool->start) && (*handle < pool->end))
		start = *handle;
	अन्यथा
		start = pool->hपूर्णांक;

	limit = pool->end;

	/* The हाल below can happen अगर we have a small segment appended
	 * to a large, or when the previous alloc was at the very end of
	 * the available space. If so, go back to the beginning. If a
	 * flush is needed, it will get करोne based on the वापस value
	 * from iommu_area_alloc() below.
	 */
	अगर (start >= limit)
		start = pool->start;
	shअगरt = iommu->table_map_base >> iommu->table_shअगरt;
	अगर (limit + shअगरt > mask) अणु
		limit = mask - shअगरt + 1;
		/* If we're स्थिरrained on address range, first try
		 * at the masked hपूर्णांक to aव्योम O(n) search complनिकासy,
		 * but on second pass, start at 0 in pool 0.
		 */
		अगर ((start & mask) >= limit || pass > 0) अणु
			spin_unlock(&(pool->lock));
			pool = &(iommu->pools[0]);
			spin_lock(&(pool->lock));
			start = pool->start;
		पूर्ण अन्यथा अणु
			start &= mask;
		पूर्ण
	पूर्ण

	/*
	 * अगर the skip_span_boundary_check had been set during init, we set
	 * things up so that iommu_is_span_boundary() merely checks अगर the
	 * (index + npages) < num_tsb_entries
	 */
	अगर ((iommu->flags & IOMMU_NO_SPAN_BOUND) != 0) अणु
		shअगरt = 0;
		boundary_size = iommu->poolsize * iommu->nr_pools;
	पूर्ण अन्यथा अणु
		boundary_size = dma_get_seg_boundary_nr_pages(dev,
					iommu->table_shअगरt);
	पूर्ण
	n = iommu_area_alloc(iommu->map, limit, start, npages, shअगरt,
			     boundary_size, align_mask);
	अगर (n == -1) अणु
		अगर (likely(pass == 0)) अणु
			/* First failure, rescan from the beginning.  */
			pool->hपूर्णांक = pool->start;
			set_flush(iommu);
			pass++;
			जाओ again;
		पूर्ण अन्यथा अगर (!largealloc && pass <= iommu->nr_pools) अणु
			spin_unlock(&(pool->lock));
			pool_nr = (pool_nr + 1) & (iommu->nr_pools - 1);
			pool = &(iommu->pools[pool_nr]);
			spin_lock(&(pool->lock));
			pool->hपूर्णांक = pool->start;
			set_flush(iommu);
			pass++;
			जाओ again;
		पूर्ण अन्यथा अणु
			/* give up */
			n = IOMMU_ERROR_CODE;
			जाओ bail;
		पूर्ण
	पूर्ण
	अगर (iommu->lazy_flush &&
	    (n < pool->hपूर्णांक || need_flush(iommu))) अणु
		clear_flush(iommu);
		iommu->lazy_flush(iommu);
	पूर्ण

	end = n + npages;
	pool->hपूर्णांक = end;

	/* Update handle क्रम SG allocations */
	अगर (handle)
		*handle = end;
bail:
	spin_unlock_irqrestore(&(pool->lock), flags);

	वापस n;
पूर्ण

अटल काष्ठा iommu_pool *get_pool(काष्ठा iommu_map_table *tbl,
				   अचिन्हित दीर्घ entry)
अणु
	काष्ठा iommu_pool *p;
	अचिन्हित दीर्घ largepool_start = tbl->large_pool.start;
	bool large_pool = ((tbl->flags & IOMMU_HAS_LARGE_POOL) != 0);

	/* The large pool is the last pool at the top of the table */
	अगर (large_pool && entry >= largepool_start) अणु
		p = &tbl->large_pool;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक pool_nr = entry / tbl->poolsize;

		BUG_ON(pool_nr >= tbl->nr_pools);
		p = &tbl->pools[pool_nr];
	पूर्ण
	वापस p;
पूर्ण

/* Caller supplies the index of the entry पूर्णांकo the iommu map table
 * itself when the mapping from dma_addr to the entry is not the
 * शेष addr->entry mapping below.
 */
व्योम iommu_tbl_range_मुक्त(काष्ठा iommu_map_table *iommu, u64 dma_addr,
			  अचिन्हित दीर्घ npages, अचिन्हित दीर्घ entry)
अणु
	काष्ठा iommu_pool *pool;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ shअगरt = iommu->table_shअगरt;

	अगर (entry == IOMMU_ERROR_CODE) /* use शेष addr->entry mapping */
		entry = (dma_addr - iommu->table_map_base) >> shअगरt;
	pool = get_pool(iommu, entry);

	spin_lock_irqsave(&(pool->lock), flags);
	biपंचांगap_clear(iommu->map, entry, npages);
	spin_unlock_irqrestore(&(pool->lock), flags);
पूर्ण
