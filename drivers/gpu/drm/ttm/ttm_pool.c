<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Christian Kथघnig
 */

/* Pooling of allocated pages is necessary because changing the caching
 * attributes on x86 of the linear mapping requires a costly cross CPU TLB
 * invalidate क्रम those addresses.
 *
 * Additional to that allocations from the DMA coherent API are pooled as well
 * cause they are rather slow compared to alloc_pages+map.
 */

#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/sched/mm.h>

#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/set_memory.h>
#पूर्ण_अगर

#समावेश <drm/tपंचांग/tपंचांग_pool.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_tt.h>

#समावेश "ttm_module.h"

/**
 * काष्ठा tपंचांग_pool_dma - Helper object क्रम coherent DMA mappings
 *
 * @addr: original DMA address वापसed क्रम the mapping
 * @vaddr: original vaddr वापस क्रम the mapping and order in the lower bits
 */
काष्ठा tपंचांग_pool_dma अणु
	dma_addr_t addr;
	अचिन्हित दीर्घ vaddr;
पूर्ण;

अटल अचिन्हित दीर्घ page_pool_size;

MODULE_PARM_DESC(page_pool_size, "Number of pages in the WC/UC/DMA pool");
module_param(page_pool_size, uदीर्घ, 0644);

अटल atomic_दीर्घ_t allocated_pages;

अटल काष्ठा tपंचांग_pool_type global_ग_लिखो_combined[MAX_ORDER];
अटल काष्ठा tपंचांग_pool_type global_uncached[MAX_ORDER];

अटल काष्ठा tपंचांग_pool_type global_dma32_ग_लिखो_combined[MAX_ORDER];
अटल काष्ठा tपंचांग_pool_type global_dma32_uncached[MAX_ORDER];

अटल काष्ठा mutex shrinker_lock;
अटल काष्ठा list_head shrinker_list;
अटल काष्ठा shrinker mm_shrinker;

/* Allocate pages of size 1 << order with the given gfp_flags */
अटल काष्ठा page *tपंचांग_pool_alloc_page(काष्ठा tपंचांग_pool *pool, gfp_t gfp_flags,
					अचिन्हित पूर्णांक order)
अणु
	अचिन्हित दीर्घ attr = DMA_ATTR_FORCE_CONTIGUOUS;
	काष्ठा tपंचांग_pool_dma *dma;
	काष्ठा page *p;
	व्योम *vaddr;

	/* Don't set the __GFP_COMP flag क्रम higher order allocations.
	 * Mapping pages directly पूर्णांकo an userspace process and calling
	 * put_page() on a TTM allocated page is illegal.
	 */
	अगर (order)
		gfp_flags |= __GFP_NOMEMALLOC | __GFP_NORETRY | __GFP_NOWARN |
			__GFP_KSWAPD_RECLAIM;

	अगर (!pool->use_dma_alloc) अणु
		p = alloc_pages(gfp_flags, order);
		अगर (p)
			p->निजी = order;
		वापस p;
	पूर्ण

	dma = kदो_स्मृति(माप(*dma), GFP_KERNEL);
	अगर (!dma)
		वापस शून्य;

	अगर (order)
		attr |= DMA_ATTR_NO_WARN;

	vaddr = dma_alloc_attrs(pool->dev, (1ULL << order) * PAGE_SIZE,
				&dma->addr, gfp_flags, attr);
	अगर (!vaddr)
		जाओ error_मुक्त;

	/* TODO: This is an illegal abuse of the DMA API, but we need to rework
	 * TTM page fault handling and extend the DMA API to clean this up.
	 */
	अगर (is_vदो_स्मृति_addr(vaddr))
		p = vदो_स्मृति_to_page(vaddr);
	अन्यथा
		p = virt_to_page(vaddr);

	dma->vaddr = (अचिन्हित दीर्घ)vaddr | order;
	p->निजी = (अचिन्हित दीर्घ)dma;
	वापस p;

error_मुक्त:
	kमुक्त(dma);
	वापस शून्य;
पूर्ण

/* Reset the caching and pages of size 1 << order */
अटल व्योम tपंचांग_pool_मुक्त_page(काष्ठा tपंचांग_pool *pool, क्रमागत tपंचांग_caching caching,
			       अचिन्हित पूर्णांक order, काष्ठा page *p)
अणु
	अचिन्हित दीर्घ attr = DMA_ATTR_FORCE_CONTIGUOUS;
	काष्ठा tपंचांग_pool_dma *dma;
	व्योम *vaddr;

#अगर_घोषित CONFIG_X86
	/* We करोn't care that set_pages_wb is inefficient here. This is only
	 * used when we have to shrink and CPU overhead is irrelevant then.
	 */
	अगर (caching != tपंचांग_cached && !PageHighMem(p))
		set_pages_wb(p, 1 << order);
#पूर्ण_अगर

	अगर (!pool || !pool->use_dma_alloc) अणु
		__मुक्त_pages(p, order);
		वापस;
	पूर्ण

	अगर (order)
		attr |= DMA_ATTR_NO_WARN;

	dma = (व्योम *)p->निजी;
	vaddr = (व्योम *)(dma->vaddr & PAGE_MASK);
	dma_मुक्त_attrs(pool->dev, (1UL << order) * PAGE_SIZE, vaddr, dma->addr,
		       attr);
	kमुक्त(dma);
पूर्ण

/* Apply a new caching to an array of pages */
अटल पूर्णांक tपंचांग_pool_apply_caching(काष्ठा page **first, काष्ठा page **last,
				  क्रमागत tपंचांग_caching caching)
अणु
#अगर_घोषित CONFIG_X86
	अचिन्हित पूर्णांक num_pages = last - first;

	अगर (!num_pages)
		वापस 0;

	चयन (caching) अणु
	हाल tपंचांग_cached:
		अवरोध;
	हाल tपंचांग_ग_लिखो_combined:
		वापस set_pages_array_wc(first, num_pages);
	हाल tपंचांग_uncached:
		वापस set_pages_array_uc(first, num_pages);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/* Map pages of 1 << order size and fill the DMA address array  */
अटल पूर्णांक tपंचांग_pool_map(काष्ठा tपंचांग_pool *pool, अचिन्हित पूर्णांक order,
			काष्ठा page *p, dma_addr_t **dma_addr)
अणु
	dma_addr_t addr;
	अचिन्हित पूर्णांक i;

	अगर (pool->use_dma_alloc) अणु
		काष्ठा tपंचांग_pool_dma *dma = (व्योम *)p->निजी;

		addr = dma->addr;
	पूर्ण अन्यथा अणु
		माप_प्रकार size = (1ULL << order) * PAGE_SIZE;

		addr = dma_map_page(pool->dev, p, 0, size, DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(pool->dev, addr))
			वापस -EFAULT;
	पूर्ण

	क्रम (i = 1 << order; i ; --i) अणु
		*(*dma_addr)++ = addr;
		addr += PAGE_SIZE;
	पूर्ण

	वापस 0;
पूर्ण

/* Unmap pages of 1 << order size */
अटल व्योम tपंचांग_pool_unmap(काष्ठा tपंचांग_pool *pool, dma_addr_t dma_addr,
			   अचिन्हित पूर्णांक num_pages)
अणु
	/* Unmapped जबतक मुक्तing the page */
	अगर (pool->use_dma_alloc)
		वापस;

	dma_unmap_page(pool->dev, dma_addr, (दीर्घ)num_pages << PAGE_SHIFT,
		       DMA_BIसूचीECTIONAL);
पूर्ण

/* Give pages पूर्णांकo a specअगरic pool_type */
अटल व्योम tपंचांग_pool_type_give(काष्ठा tपंचांग_pool_type *pt, काष्ठा page *p)
अणु
	अचिन्हित पूर्णांक i, num_pages = 1 << pt->order;

	क्रम (i = 0; i < num_pages; ++i) अणु
		अगर (PageHighMem(p))
			clear_highpage(p + i);
		अन्यथा
			clear_page(page_address(p + i));
	पूर्ण

	spin_lock(&pt->lock);
	list_add(&p->lru, &pt->pages);
	spin_unlock(&pt->lock);
	atomic_दीर्घ_add(1 << pt->order, &allocated_pages);
पूर्ण

/* Take pages from a specअगरic pool_type, वापस शून्य when nothing available */
अटल काष्ठा page *tपंचांग_pool_type_take(काष्ठा tपंचांग_pool_type *pt)
अणु
	काष्ठा page *p;

	spin_lock(&pt->lock);
	p = list_first_entry_or_null(&pt->pages, typeof(*p), lru);
	अगर (p) अणु
		atomic_दीर्घ_sub(1 << pt->order, &allocated_pages);
		list_del(&p->lru);
	पूर्ण
	spin_unlock(&pt->lock);

	वापस p;
पूर्ण

/* Initialize and add a pool type to the global shrinker list */
अटल व्योम tपंचांग_pool_type_init(काष्ठा tपंचांग_pool_type *pt, काष्ठा tपंचांग_pool *pool,
			       क्रमागत tपंचांग_caching caching, अचिन्हित पूर्णांक order)
अणु
	pt->pool = pool;
	pt->caching = caching;
	pt->order = order;
	spin_lock_init(&pt->lock);
	INIT_LIST_HEAD(&pt->pages);

	mutex_lock(&shrinker_lock);
	list_add_tail(&pt->shrinker_list, &shrinker_list);
	mutex_unlock(&shrinker_lock);
पूर्ण

/* Remove a pool_type from the global shrinker list and मुक्त all pages */
अटल व्योम tपंचांग_pool_type_fini(काष्ठा tपंचांग_pool_type *pt)
अणु
	काष्ठा page *p;

	mutex_lock(&shrinker_lock);
	list_del(&pt->shrinker_list);
	mutex_unlock(&shrinker_lock);

	जबतक ((p = tपंचांग_pool_type_take(pt)))
		tपंचांग_pool_मुक्त_page(pt->pool, pt->caching, pt->order, p);
पूर्ण

/* Return the pool_type to use क्रम the given caching and order */
अटल काष्ठा tपंचांग_pool_type *tपंचांग_pool_select_type(काष्ठा tपंचांग_pool *pool,
						  क्रमागत tपंचांग_caching caching,
						  अचिन्हित पूर्णांक order)
अणु
	अगर (pool->use_dma_alloc)
		वापस &pool->caching[caching].orders[order];

#अगर_घोषित CONFIG_X86
	चयन (caching) अणु
	हाल tपंचांग_ग_लिखो_combined:
		अगर (pool->use_dma32)
			वापस &global_dma32_ग_लिखो_combined[order];

		वापस &global_ग_लिखो_combined[order];
	हाल tपंचांग_uncached:
		अगर (pool->use_dma32)
			वापस &global_dma32_uncached[order];

		वापस &global_uncached[order];
	शेष:
		अवरोध;
	पूर्ण
#पूर्ण_अगर

	वापस शून्य;
पूर्ण

/* Free pages using the global shrinker list */
अटल अचिन्हित पूर्णांक tपंचांग_pool_shrink(व्योम)
अणु
	काष्ठा tपंचांग_pool_type *pt;
	अचिन्हित पूर्णांक num_मुक्तd;
	काष्ठा page *p;

	mutex_lock(&shrinker_lock);
	pt = list_first_entry(&shrinker_list, typeof(*pt), shrinker_list);

	p = tपंचांग_pool_type_take(pt);
	अगर (p) अणु
		tपंचांग_pool_मुक्त_page(pt->pool, pt->caching, pt->order, p);
		num_मुक्तd = 1 << pt->order;
	पूर्ण अन्यथा अणु
		num_मुक्तd = 0;
	पूर्ण

	list_move_tail(&pt->shrinker_list, &shrinker_list);
	mutex_unlock(&shrinker_lock);

	वापस num_मुक्तd;
पूर्ण

/* Return the allocation order based क्रम a page */
अटल अचिन्हित पूर्णांक tपंचांग_pool_page_order(काष्ठा tपंचांग_pool *pool, काष्ठा page *p)
अणु
	अगर (pool->use_dma_alloc) अणु
		काष्ठा tपंचांग_pool_dma *dma = (व्योम *)p->निजी;

		वापस dma->vaddr & ~PAGE_MASK;
	पूर्ण

	वापस p->निजी;
पूर्ण

/**
 * tपंचांग_pool_alloc - Fill a tपंचांग_tt object
 *
 * @pool: tपंचांग_pool to use
 * @tt: tपंचांग_tt object to fill
 * @ctx: operation context
 *
 * Fill the tपंचांग_tt object with pages and also make sure to DMA map them when
 * necessary.
 *
 * Returns: 0 on successe, negative error code otherwise.
 */
पूर्णांक tपंचांग_pool_alloc(काष्ठा tपंचांग_pool *pool, काष्ठा tपंचांग_tt *tt,
		   काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	अचिन्हित दीर्घ num_pages = tt->num_pages;
	dma_addr_t *dma_addr = tt->dma_address;
	काष्ठा page **caching = tt->pages;
	काष्ठा page **pages = tt->pages;
	gfp_t gfp_flags = GFP_USER;
	अचिन्हित पूर्णांक i, order;
	काष्ठा page *p;
	पूर्णांक r;

	WARN_ON(!num_pages || tपंचांग_tt_is_populated(tt));
	WARN_ON(dma_addr && !pool->dev);

	अगर (tt->page_flags & TTM_PAGE_FLAG_ZERO_ALLOC)
		gfp_flags |= __GFP_ZERO;

	अगर (ctx->gfp_retry_mayfail)
		gfp_flags |= __GFP_RETRY_MAYFAIL;

	अगर (pool->use_dma32)
		gfp_flags |= GFP_DMA32;
	अन्यथा
		gfp_flags |= GFP_HIGHUSER;

	क्रम (order = min(MAX_ORDER - 1UL, __fls(num_pages)); num_pages;
	     order = min_t(अचिन्हित पूर्णांक, order, __fls(num_pages))) अणु
		bool apply_caching = false;
		काष्ठा tपंचांग_pool_type *pt;

		pt = tपंचांग_pool_select_type(pool, tt->caching, order);
		p = pt ? tपंचांग_pool_type_take(pt) : शून्य;
		अगर (p) अणु
			apply_caching = true;
		पूर्ण अन्यथा अणु
			p = tपंचांग_pool_alloc_page(pool, gfp_flags, order);
			अगर (p && PageHighMem(p))
				apply_caching = true;
		पूर्ण

		अगर (!p) अणु
			अगर (order) अणु
				--order;
				जारी;
			पूर्ण
			r = -ENOMEM;
			जाओ error_मुक्त_all;
		पूर्ण

		अगर (apply_caching) अणु
			r = tपंचांग_pool_apply_caching(caching, pages,
						   tt->caching);
			अगर (r)
				जाओ error_मुक्त_page;
			caching = pages + (1 << order);
		पूर्ण

		अगर (dma_addr) अणु
			r = tपंचांग_pool_map(pool, order, p, &dma_addr);
			अगर (r)
				जाओ error_मुक्त_page;
		पूर्ण

		num_pages -= 1 << order;
		क्रम (i = 1 << order; i; --i)
			*(pages++) = p++;
	पूर्ण

	r = tपंचांग_pool_apply_caching(caching, pages, tt->caching);
	अगर (r)
		जाओ error_मुक्त_all;

	वापस 0;

error_मुक्त_page:
	tपंचांग_pool_मुक्त_page(pool, tt->caching, order, p);

error_मुक्त_all:
	num_pages = tt->num_pages - num_pages;
	क्रम (i = 0; i < num_pages; ) अणु
		order = tपंचांग_pool_page_order(pool, tt->pages[i]);
		tपंचांग_pool_मुक्त_page(pool, tt->caching, order, tt->pages[i]);
		i += 1 << order;
	पूर्ण

	वापस r;
पूर्ण
EXPORT_SYMBOL(tपंचांग_pool_alloc);

/**
 * tपंचांग_pool_मुक्त - Free the backing pages from a tपंचांग_tt object
 *
 * @pool: Pool to give pages back to.
 * @tt: tपंचांग_tt object to unpopulate
 *
 * Give the packing pages back to a pool or मुक्त them
 */
व्योम tपंचांग_pool_मुक्त(काष्ठा tपंचांग_pool *pool, काष्ठा tपंचांग_tt *tt)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < tt->num_pages; ) अणु
		काष्ठा page *p = tt->pages[i];
		अचिन्हित पूर्णांक order, num_pages;
		काष्ठा tपंचांग_pool_type *pt;

		order = tपंचांग_pool_page_order(pool, p);
		num_pages = 1ULL << order;
		अगर (tt->dma_address)
			tपंचांग_pool_unmap(pool, tt->dma_address[i], num_pages);

		pt = tपंचांग_pool_select_type(pool, tt->caching, order);
		अगर (pt)
			tपंचांग_pool_type_give(pt, tt->pages[i]);
		अन्यथा
			tपंचांग_pool_मुक्त_page(pool, tt->caching, order,
					   tt->pages[i]);

		i += num_pages;
	पूर्ण

	जबतक (atomic_दीर्घ_पढ़ो(&allocated_pages) > page_pool_size)
		tपंचांग_pool_shrink();
पूर्ण
EXPORT_SYMBOL(tपंचांग_pool_मुक्त);

/**
 * tपंचांग_pool_init - Initialize a pool
 *
 * @pool: the pool to initialize
 * @dev: device क्रम DMA allocations and mappings
 * @use_dma_alloc: true अगर coherent DMA alloc should be used
 * @use_dma32: true अगर GFP_DMA32 should be used
 *
 * Initialize the pool and its pool types.
 */
व्योम tपंचांग_pool_init(काष्ठा tपंचांग_pool *pool, काष्ठा device *dev,
		   bool use_dma_alloc, bool use_dma32)
अणु
	अचिन्हित पूर्णांक i, j;

	WARN_ON(!dev && use_dma_alloc);

	pool->dev = dev;
	pool->use_dma_alloc = use_dma_alloc;
	pool->use_dma32 = use_dma32;

	अगर (use_dma_alloc) अणु
		क्रम (i = 0; i < TTM_NUM_CACHING_TYPES; ++i)
			क्रम (j = 0; j < MAX_ORDER; ++j)
				tपंचांग_pool_type_init(&pool->caching[i].orders[j],
						   pool, i, j);
	पूर्ण
पूर्ण

/**
 * tपंचांग_pool_fini - Cleanup a pool
 *
 * @pool: the pool to clean up
 *
 * Free all pages in the pool and unरेजिस्टर the types from the global
 * shrinker.
 */
व्योम tपंचांग_pool_fini(काष्ठा tपंचांग_pool *pool)
अणु
	अचिन्हित पूर्णांक i, j;

	अगर (pool->use_dma_alloc) अणु
		क्रम (i = 0; i < TTM_NUM_CACHING_TYPES; ++i)
			क्रम (j = 0; j < MAX_ORDER; ++j)
				tपंचांग_pool_type_fini(&pool->caching[i].orders[j]);
	पूर्ण
पूर्ण

/* As दीर्घ as pages are available make sure to release at least one */
अटल अचिन्हित दीर्घ tपंचांग_pool_shrinker_scan(काष्ठा shrinker *shrink,
					    काष्ठा shrink_control *sc)
अणु
	अचिन्हित दीर्घ num_मुक्तd = 0;

	करो
		num_मुक्तd += tपंचांग_pool_shrink();
	जबतक (!num_मुक्तd && atomic_दीर्घ_पढ़ो(&allocated_pages));

	वापस num_मुक्तd;
पूर्ण

/* Return the number of pages available or SHRINK_EMPTY अगर we have none */
अटल अचिन्हित दीर्घ tपंचांग_pool_shrinker_count(काष्ठा shrinker *shrink,
					     काष्ठा shrink_control *sc)
अणु
	अचिन्हित दीर्घ num_pages = atomic_दीर्घ_पढ़ो(&allocated_pages);

	वापस num_pages ? num_pages : SHRINK_EMPTY;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
/* Count the number of pages available in a pool_type */
अटल अचिन्हित पूर्णांक tपंचांग_pool_type_count(काष्ठा tपंचांग_pool_type *pt)
अणु
	अचिन्हित पूर्णांक count = 0;
	काष्ठा page *p;

	spin_lock(&pt->lock);
	/* Only used क्रम debugfs, the overhead करोesn't matter */
	list_क्रम_each_entry(p, &pt->pages, lru)
		++count;
	spin_unlock(&pt->lock);

	वापस count;
पूर्ण

/* Prपूर्णांक a nice header क्रम the order */
अटल व्योम tपंचांग_pool_debugfs_header(काष्ठा seq_file *m)
अणु
	अचिन्हित पूर्णांक i;

	seq_माला_दो(m, "\t ");
	क्रम (i = 0; i < MAX_ORDER; ++i)
		seq_म_लिखो(m, " ---%2u---", i);
	seq_माला_दो(m, "\n");
पूर्ण

/* Dump inक्रमmation about the dअगरferent pool types */
अटल व्योम tपंचांग_pool_debugfs_orders(काष्ठा tपंचांग_pool_type *pt,
				    काष्ठा seq_file *m)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MAX_ORDER; ++i)
		seq_म_लिखो(m, " %8u", tपंचांग_pool_type_count(&pt[i]));
	seq_माला_दो(m, "\n");
पूर्ण

/* Dump the total amount of allocated pages */
अटल व्योम tपंचांग_pool_debugfs_footer(काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "\ntotal\t: %8lu of %8lu\n",
		   atomic_दीर्घ_पढ़ो(&allocated_pages), page_pool_size);
पूर्ण

/* Dump the inक्रमmation क्रम the global pools */
अटल पूर्णांक tपंचांग_pool_debugfs_globals_show(काष्ठा seq_file *m, व्योम *data)
अणु
	tपंचांग_pool_debugfs_header(m);

	mutex_lock(&shrinker_lock);
	seq_माला_दो(m, "wc\t:");
	tपंचांग_pool_debugfs_orders(global_ग_लिखो_combined, m);
	seq_माला_दो(m, "uc\t:");
	tपंचांग_pool_debugfs_orders(global_uncached, m);
	seq_माला_दो(m, "wc 32\t:");
	tपंचांग_pool_debugfs_orders(global_dma32_ग_लिखो_combined, m);
	seq_माला_दो(m, "uc 32\t:");
	tपंचांग_pool_debugfs_orders(global_dma32_uncached, m);
	mutex_unlock(&shrinker_lock);

	tपंचांग_pool_debugfs_footer(m);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(tपंचांग_pool_debugfs_globals);

/**
 * tपंचांग_pool_debugfs - Debugfs dump function क्रम a pool
 *
 * @pool: the pool to dump the inक्रमmation क्रम
 * @m: seq_file to dump to
 *
 * Make a debugfs dump with the per pool and global inक्रमmation.
 */
पूर्णांक tपंचांग_pool_debugfs(काष्ठा tपंचांग_pool *pool, काष्ठा seq_file *m)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!pool->use_dma_alloc) अणु
		seq_माला_दो(m, "unused\n");
		वापस 0;
	पूर्ण

	tपंचांग_pool_debugfs_header(m);

	mutex_lock(&shrinker_lock);
	क्रम (i = 0; i < TTM_NUM_CACHING_TYPES; ++i) अणु
		seq_माला_दो(m, "DMA ");
		चयन (i) अणु
		हाल tपंचांग_cached:
			seq_माला_दो(m, "\t:");
			अवरोध;
		हाल tपंचांग_ग_लिखो_combined:
			seq_माला_दो(m, "wc\t:");
			अवरोध;
		हाल tपंचांग_uncached:
			seq_माला_दो(m, "uc\t:");
			अवरोध;
		पूर्ण
		tपंचांग_pool_debugfs_orders(pool->caching[i].orders, m);
	पूर्ण
	mutex_unlock(&shrinker_lock);

	tपंचांग_pool_debugfs_footer(m);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_pool_debugfs);

/* Test the shrinker functions and dump the result */
अटल पूर्णांक tपंचांग_pool_debugfs_shrink_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा shrink_control sc = अणु .gfp_mask = GFP_NOFS पूर्ण;

	fs_reclaim_acquire(GFP_KERNEL);
	seq_म_लिखो(m, "%lu/%lu\n", tपंचांग_pool_shrinker_count(&mm_shrinker, &sc),
		   tपंचांग_pool_shrinker_scan(&mm_shrinker, &sc));
	fs_reclaim_release(GFP_KERNEL);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(tपंचांग_pool_debugfs_shrink);

#पूर्ण_अगर

/**
 * tपंचांग_pool_mgr_init - Initialize globals
 *
 * @num_pages: शेष number of pages
 *
 * Initialize the global locks and lists क्रम the MM shrinker.
 */
पूर्णांक tपंचांग_pool_mgr_init(अचिन्हित दीर्घ num_pages)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!page_pool_size)
		page_pool_size = num_pages;

	mutex_init(&shrinker_lock);
	INIT_LIST_HEAD(&shrinker_list);

	क्रम (i = 0; i < MAX_ORDER; ++i) अणु
		tपंचांग_pool_type_init(&global_ग_लिखो_combined[i], शून्य,
				   tपंचांग_ग_लिखो_combined, i);
		tपंचांग_pool_type_init(&global_uncached[i], शून्य, tपंचांग_uncached, i);

		tपंचांग_pool_type_init(&global_dma32_ग_लिखो_combined[i], शून्य,
				   tपंचांग_ग_लिखो_combined, i);
		tपंचांग_pool_type_init(&global_dma32_uncached[i], शून्य,
				   tपंचांग_uncached, i);
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	debugfs_create_file("page_pool", 0444, tपंचांग_debugfs_root, शून्य,
			    &tपंचांग_pool_debugfs_globals_fops);
	debugfs_create_file("page_pool_shrink", 0400, tपंचांग_debugfs_root, शून्य,
			    &tपंचांग_pool_debugfs_shrink_fops);
#पूर्ण_अगर

	mm_shrinker.count_objects = tपंचांग_pool_shrinker_count;
	mm_shrinker.scan_objects = tपंचांग_pool_shrinker_scan;
	mm_shrinker.seeks = 1;
	वापस रेजिस्टर_shrinker(&mm_shrinker);
पूर्ण

/**
 * tपंचांग_pool_mgr_fini - Finalize globals
 *
 * Cleanup the global pools and unरेजिस्टर the MM shrinker.
 */
व्योम tपंचांग_pool_mgr_fini(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MAX_ORDER; ++i) अणु
		tपंचांग_pool_type_fini(&global_ग_लिखो_combined[i]);
		tपंचांग_pool_type_fini(&global_uncached[i]);

		tपंचांग_pool_type_fini(&global_dma32_ग_लिखो_combined[i]);
		tपंचांग_pool_type_fini(&global_dma32_uncached[i]);
	पूर्ण

	unरेजिस्टर_shrinker(&mm_shrinker);
	WARN_ON(!list_empty(&shrinker_list));
पूर्ण
