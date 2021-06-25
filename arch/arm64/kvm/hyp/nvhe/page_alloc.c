<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Google LLC
 * Author: Quentin Perret <qperret@google.com>
 */

#समावेश <यंत्र/kvm_hyp.h>
#समावेश <nvhe/gfp.h>

u64 __hyp_vmemmap;

/*
 * Index the hyp_vmemmap to find a potential buddy page, but make no assumption
 * about its current state.
 *
 * Example buddy-tree क्रम a 4-pages physically contiguous pool:
 *
 *                 o : Page 3
 *                /
 *               o-o : Page 2
 *              /
 *             /   o : Page 1
 *            /   /
 *           o---o-o : Page 0
 *    Order  2   1 0
 *
 * Example of requests on this pool:
 *   __find_buddy_nocheck(pool, page 0, order 0) => page 1
 *   __find_buddy_nocheck(pool, page 0, order 1) => page 2
 *   __find_buddy_nocheck(pool, page 1, order 0) => page 0
 *   __find_buddy_nocheck(pool, page 2, order 0) => page 3
 */
अटल काष्ठा hyp_page *__find_buddy_nocheck(काष्ठा hyp_pool *pool,
					     काष्ठा hyp_page *p,
					     अचिन्हित पूर्णांक order)
अणु
	phys_addr_t addr = hyp_page_to_phys(p);

	addr ^= (PAGE_SIZE << order);

	/*
	 * Don't वापस a page outside the pool range -- it beदीर्घs to
	 * something अन्यथा and may not be mapped in hyp_vmemmap.
	 */
	अगर (addr < pool->range_start || addr >= pool->range_end)
		वापस शून्य;

	वापस hyp_phys_to_page(addr);
पूर्ण

/* Find a buddy page currently available क्रम allocation */
अटल काष्ठा hyp_page *__find_buddy_avail(काष्ठा hyp_pool *pool,
					   काष्ठा hyp_page *p,
					   अचिन्हित पूर्णांक order)
अणु
	काष्ठा hyp_page *buddy = __find_buddy_nocheck(pool, p, order);

	अगर (!buddy || buddy->order != order || list_empty(&buddy->node))
		वापस शून्य;

	वापस buddy;

पूर्ण

अटल व्योम __hyp_attach_page(काष्ठा hyp_pool *pool,
			      काष्ठा hyp_page *p)
अणु
	अचिन्हित पूर्णांक order = p->order;
	काष्ठा hyp_page *buddy;

	स_रखो(hyp_page_to_virt(p), 0, PAGE_SIZE << p->order);

	/*
	 * Only the first काष्ठा hyp_page of a high-order page (otherwise known
	 * as the 'head') should have p->order set. The non-head pages should
	 * have p->order = HYP_NO_ORDER. Here @p may no दीर्घer be the head
	 * after coallescing, so make sure to mark it HYP_NO_ORDER proactively.
	 */
	p->order = HYP_NO_ORDER;
	क्रम (; (order + 1) < pool->max_order; order++) अणु
		buddy = __find_buddy_avail(pool, p, order);
		अगर (!buddy)
			अवरोध;

		/* Take the buddy out of its list, and coallesce with @p */
		list_del_init(&buddy->node);
		buddy->order = HYP_NO_ORDER;
		p = min(p, buddy);
	पूर्ण

	/* Mark the new head, and insert it */
	p->order = order;
	list_add_tail(&p->node, &pool->मुक्त_area[order]);
पूर्ण

अटल व्योम hyp_attach_page(काष्ठा hyp_page *p)
अणु
	काष्ठा hyp_pool *pool = hyp_page_to_pool(p);

	hyp_spin_lock(&pool->lock);
	__hyp_attach_page(pool, p);
	hyp_spin_unlock(&pool->lock);
पूर्ण

अटल काष्ठा hyp_page *__hyp_extract_page(काष्ठा hyp_pool *pool,
					   काष्ठा hyp_page *p,
					   अचिन्हित पूर्णांक order)
अणु
	काष्ठा hyp_page *buddy;

	list_del_init(&p->node);
	जबतक (p->order > order) अणु
		/*
		 * The buddy of order n - 1 currently has HYP_NO_ORDER as it
		 * is covered by a higher-level page (whose head is @p). Use
		 * __find_buddy_nocheck() to find it and inject it in the
		 * मुक्त_list[n - 1], effectively splitting @p in half.
		 */
		p->order--;
		buddy = __find_buddy_nocheck(pool, p, p->order);
		buddy->order = p->order;
		list_add_tail(&buddy->node, &pool->मुक्त_area[buddy->order]);
	पूर्ण

	वापस p;
पूर्ण

व्योम hyp_put_page(व्योम *addr)
अणु
	काष्ठा hyp_page *p = hyp_virt_to_page(addr);

	अगर (hyp_page_ref_dec_and_test(p))
		hyp_attach_page(p);
पूर्ण

व्योम hyp_get_page(व्योम *addr)
अणु
	काष्ठा hyp_page *p = hyp_virt_to_page(addr);

	hyp_page_ref_inc(p);
पूर्ण

व्योम *hyp_alloc_pages(काष्ठा hyp_pool *pool, अचिन्हित पूर्णांक order)
अणु
	अचिन्हित पूर्णांक i = order;
	काष्ठा hyp_page *p;

	hyp_spin_lock(&pool->lock);

	/* Look क्रम a high-enough-order page */
	जबतक (i < pool->max_order && list_empty(&pool->मुक्त_area[i]))
		i++;
	अगर (i >= pool->max_order) अणु
		hyp_spin_unlock(&pool->lock);
		वापस शून्य;
	पूर्ण

	/* Extract it from the tree at the right order */
	p = list_first_entry(&pool->मुक्त_area[i], काष्ठा hyp_page, node);
	p = __hyp_extract_page(pool, p, order);

	hyp_spin_unlock(&pool->lock);
	hyp_set_page_refcounted(p);

	वापस hyp_page_to_virt(p);
पूर्ण

पूर्णांक hyp_pool_init(काष्ठा hyp_pool *pool, u64 pfn, अचिन्हित पूर्णांक nr_pages,
		  अचिन्हित पूर्णांक reserved_pages)
अणु
	phys_addr_t phys = hyp_pfn_to_phys(pfn);
	काष्ठा hyp_page *p;
	पूर्णांक i;

	hyp_spin_lock_init(&pool->lock);
	pool->max_order = min(MAX_ORDER, get_order(nr_pages << PAGE_SHIFT));
	क्रम (i = 0; i < pool->max_order; i++)
		INIT_LIST_HEAD(&pool->मुक्त_area[i]);
	pool->range_start = phys;
	pool->range_end = phys + (nr_pages << PAGE_SHIFT);

	/* Init the vmemmap portion */
	p = hyp_phys_to_page(phys);
	स_रखो(p, 0, माप(*p) * nr_pages);
	क्रम (i = 0; i < nr_pages; i++) अणु
		p[i].pool = pool;
		INIT_LIST_HEAD(&p[i].node);
	पूर्ण

	/* Attach the unused pages to the buddy tree */
	क्रम (i = reserved_pages; i < nr_pages; i++)
		__hyp_attach_page(pool, &p[i]);

	वापस 0;
पूर्ण
