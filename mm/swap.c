<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/mm/swap.c
 *
 *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 */

/*
 * This file contains the शेष values क्रम the operation of the
 * Linux VM subप्रणाली. Fine-tuning करोcumentation can be found in
 * Documentation/admin-guide/sysctl/vm.rst.
 * Started 18.12.91
 * Swap aging added 23.2.95, Stephen Tweedie.
 * Buffermem limits added 12.3.98, Rik van Riel.
 */

#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/swap.h>
#समावेश <linux/mman.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/percpu_counter.h>
#समावेश <linux/memremap.h>
#समावेश <linux/percpu.h>
#समावेश <linux/cpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/gfp.h>
#समावेश <linux/uपन.स>
#समावेश <linux/hugetlb.h>
#समावेश <linux/page_idle.h>
#समावेश <linux/local_lock.h>
#समावेश <linux/buffer_head.h>

#समावेश "internal.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/pagemap.h>

/* How many pages करो we try to swap or page in/out together? */
पूर्णांक page_cluster;

/* Protecting only lru_rotate.pvec which requires disabling पूर्णांकerrupts */
काष्ठा lru_rotate अणु
	local_lock_t lock;
	काष्ठा pagevec pvec;
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा lru_rotate, lru_rotate) = अणु
	.lock = INIT_LOCAL_LOCK(lock),
पूर्ण;

/*
 * The following काष्ठा pagevec are grouped together because they are रक्षित
 * by disabling preemption (and पूर्णांकerrupts reमुख्य enabled).
 */
काष्ठा lru_pvecs अणु
	local_lock_t lock;
	काष्ठा pagevec lru_add;
	काष्ठा pagevec lru_deactivate_file;
	काष्ठा pagevec lru_deactivate;
	काष्ठा pagevec lru_lazyमुक्त;
#अगर_घोषित CONFIG_SMP
	काष्ठा pagevec activate_page;
#पूर्ण_अगर
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा lru_pvecs, lru_pvecs) = अणु
	.lock = INIT_LOCAL_LOCK(lock),
पूर्ण;

/*
 * This path almost never happens क्रम VM activity - pages are normally
 * मुक्तd via pagevecs.  But it माला_लो used by networking.
 */
अटल व्योम __page_cache_release(काष्ठा page *page)
अणु
	अगर (PageLRU(page)) अणु
		काष्ठा lruvec *lruvec;
		अचिन्हित दीर्घ flags;

		lruvec = lock_page_lruvec_irqsave(page, &flags);
		del_page_from_lru_list(page, lruvec);
		__clear_page_lru_flags(page);
		unlock_page_lruvec_irqrestore(lruvec, flags);
	पूर्ण
	__ClearPageWaiters(page);
पूर्ण

अटल व्योम __put_single_page(काष्ठा page *page)
अणु
	__page_cache_release(page);
	mem_cgroup_unअक्षरge(page);
	मुक्त_unref_page(page);
पूर्ण

अटल व्योम __put_compound_page(काष्ठा page *page)
अणु
	/*
	 * __page_cache_release() is supposed to be called क्रम thp, not क्रम
	 * hugetlb. This is because hugetlb page करोes never have PageLRU set
	 * (it's never listed to any LRU lists) and no memcg routines should
	 * be called क्रम hugetlb (it has a separate hugetlb_cgroup.)
	 */
	अगर (!PageHuge(page))
		__page_cache_release(page);
	destroy_compound_page(page);
पूर्ण

व्योम __put_page(काष्ठा page *page)
अणु
	अगर (is_zone_device_page(page)) अणु
		put_dev_pagemap(page->pgmap);

		/*
		 * The page beदीर्घs to the device that created pgmap. Do
		 * not वापस it to page allocator.
		 */
		वापस;
	पूर्ण

	अगर (unlikely(PageCompound(page)))
		__put_compound_page(page);
	अन्यथा
		__put_single_page(page);
पूर्ण
EXPORT_SYMBOL(__put_page);

/**
 * put_pages_list() - release a list of pages
 * @pages: list of pages thपढ़ोed on page->lru
 *
 * Release a list of pages which are strung together on page.lru.  Currently
 * used by पढ़ो_cache_pages() and related error recovery code.
 */
व्योम put_pages_list(काष्ठा list_head *pages)
अणु
	जबतक (!list_empty(pages)) अणु
		काष्ठा page *victim;

		victim = lru_to_page(pages);
		list_del(&victim->lru);
		put_page(victim);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(put_pages_list);

/*
 * get_kernel_pages() - pin kernel pages in memory
 * @kiov:	An array of काष्ठा kvec काष्ठाures
 * @nr_segs:	number of segments to pin
 * @ग_लिखो:	pinning क्रम पढ़ो/ग_लिखो, currently ignored
 * @pages:	array that receives poपूर्णांकers to the pages pinned.
 *		Should be at least nr_segs दीर्घ.
 *
 * Returns number of pages pinned. This may be fewer than the number
 * requested. If nr_pages is 0 or negative, वापसs 0. If no pages
 * were pinned, वापसs -त्रुटि_सं. Each page वापसed must be released
 * with a put_page() call when it is finished with.
 */
पूर्णांक get_kernel_pages(स्थिर काष्ठा kvec *kiov, पूर्णांक nr_segs, पूर्णांक ग_लिखो,
		काष्ठा page **pages)
अणु
	पूर्णांक seg;

	क्रम (seg = 0; seg < nr_segs; seg++) अणु
		अगर (WARN_ON(kiov[seg].iov_len != PAGE_SIZE))
			वापस seg;

		pages[seg] = kmap_to_page(kiov[seg].iov_base);
		get_page(pages[seg]);
	पूर्ण

	वापस seg;
पूर्ण
EXPORT_SYMBOL_GPL(get_kernel_pages);

/*
 * get_kernel_page() - pin a kernel page in memory
 * @start:	starting kernel address
 * @ग_लिखो:	pinning क्रम पढ़ो/ग_लिखो, currently ignored
 * @pages:	array that receives poपूर्णांकer to the page pinned.
 *		Must be at least nr_segs दीर्घ.
 *
 * Returns 1 अगर page is pinned. If the page was not pinned, वापसs
 * -त्रुटि_सं. The page वापसed must be released with a put_page() call
 * when it is finished with.
 */
पूर्णांक get_kernel_page(अचिन्हित दीर्घ start, पूर्णांक ग_लिखो, काष्ठा page **pages)
अणु
	स्थिर काष्ठा kvec kiov = अणु
		.iov_base = (व्योम *)start,
		.iov_len = PAGE_SIZE
	पूर्ण;

	वापस get_kernel_pages(&kiov, 1, ग_लिखो, pages);
पूर्ण
EXPORT_SYMBOL_GPL(get_kernel_page);

अटल व्योम pagevec_lru_move_fn(काष्ठा pagevec *pvec,
	व्योम (*move_fn)(काष्ठा page *page, काष्ठा lruvec *lruvec))
अणु
	पूर्णांक i;
	काष्ठा lruvec *lruvec = शून्य;
	अचिन्हित दीर्घ flags = 0;

	क्रम (i = 0; i < pagevec_count(pvec); i++) अणु
		काष्ठा page *page = pvec->pages[i];

		/* block memcg migration during page moving between lru */
		अगर (!TestClearPageLRU(page))
			जारी;

		lruvec = relock_page_lruvec_irqsave(page, lruvec, &flags);
		(*move_fn)(page, lruvec);

		SetPageLRU(page);
	पूर्ण
	अगर (lruvec)
		unlock_page_lruvec_irqrestore(lruvec, flags);
	release_pages(pvec->pages, pvec->nr);
	pagevec_reinit(pvec);
पूर्ण

अटल व्योम pagevec_move_tail_fn(काष्ठा page *page, काष्ठा lruvec *lruvec)
अणु
	अगर (!PageUnevictable(page)) अणु
		del_page_from_lru_list(page, lruvec);
		ClearPageActive(page);
		add_page_to_lru_list_tail(page, lruvec);
		__count_vm_events(PGROTATED, thp_nr_pages(page));
	पूर्ण
पूर्ण

/* वापस true अगर pagevec needs to drain */
अटल bool pagevec_add_and_need_flush(काष्ठा pagevec *pvec, काष्ठा page *page)
अणु
	bool ret = false;

	अगर (!pagevec_add(pvec, page) || PageCompound(page) ||
			lru_cache_disabled())
		ret = true;

	वापस ret;
पूर्ण

/*
 * Writeback is about to end against a page which has been marked क्रम immediate
 * reclaim.  If it still appears to be reclaimable, move it to the tail of the
 * inactive list.
 *
 * rotate_reclaimable_page() must disable IRQs, to prevent nasty races.
 */
व्योम rotate_reclaimable_page(काष्ठा page *page)
अणु
	अगर (!PageLocked(page) && !PageDirty(page) &&
	    !PageUnevictable(page) && PageLRU(page)) अणु
		काष्ठा pagevec *pvec;
		अचिन्हित दीर्घ flags;

		get_page(page);
		local_lock_irqsave(&lru_rotate.lock, flags);
		pvec = this_cpu_ptr(&lru_rotate.pvec);
		अगर (pagevec_add_and_need_flush(pvec, page))
			pagevec_lru_move_fn(pvec, pagevec_move_tail_fn);
		local_unlock_irqrestore(&lru_rotate.lock, flags);
	पूर्ण
पूर्ण

व्योम lru_note_cost(काष्ठा lruvec *lruvec, bool file, अचिन्हित पूर्णांक nr_pages)
अणु
	करो अणु
		अचिन्हित दीर्घ lrusize;

		/*
		 * Hold lruvec->lru_lock is safe here, since
		 * 1) The pinned lruvec in reclaim, or
		 * 2) From a pre-LRU page during refault (which also holds the
		 *    rcu lock, so would be safe even अगर the page was on the LRU
		 *    and could move simultaneously to a new lruvec).
		 */
		spin_lock_irq(&lruvec->lru_lock);
		/* Record cost event */
		अगर (file)
			lruvec->file_cost += nr_pages;
		अन्यथा
			lruvec->anon_cost += nr_pages;

		/*
		 * Decay previous events
		 *
		 * Because workloads change over समय (and to aव्योम
		 * overflow) we keep these statistics as a भग्नing
		 * average, which ends up weighing recent refaults
		 * more than old ones.
		 */
		lrusize = lruvec_page_state(lruvec, NR_INACTIVE_ANON) +
			  lruvec_page_state(lruvec, NR_ACTIVE_ANON) +
			  lruvec_page_state(lruvec, NR_INACTIVE_खाता) +
			  lruvec_page_state(lruvec, NR_ACTIVE_खाता);

		अगर (lruvec->file_cost + lruvec->anon_cost > lrusize / 4) अणु
			lruvec->file_cost /= 2;
			lruvec->anon_cost /= 2;
		पूर्ण
		spin_unlock_irq(&lruvec->lru_lock);
	पूर्ण जबतक ((lruvec = parent_lruvec(lruvec)));
पूर्ण

व्योम lru_note_cost_page(काष्ठा page *page)
अणु
	lru_note_cost(mem_cgroup_page_lruvec(page, page_pgdat(page)),
		      page_is_file_lru(page), thp_nr_pages(page));
पूर्ण

अटल व्योम __activate_page(काष्ठा page *page, काष्ठा lruvec *lruvec)
अणु
	अगर (!PageActive(page) && !PageUnevictable(page)) अणु
		पूर्णांक nr_pages = thp_nr_pages(page);

		del_page_from_lru_list(page, lruvec);
		SetPageActive(page);
		add_page_to_lru_list(page, lruvec);
		trace_mm_lru_activate(page);

		__count_vm_events(PGACTIVATE, nr_pages);
		__count_memcg_events(lruvec_memcg(lruvec), PGACTIVATE,
				     nr_pages);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल व्योम activate_page_drain(पूर्णांक cpu)
अणु
	काष्ठा pagevec *pvec = &per_cpu(lru_pvecs.activate_page, cpu);

	अगर (pagevec_count(pvec))
		pagevec_lru_move_fn(pvec, __activate_page);
पूर्ण

अटल bool need_activate_page_drain(पूर्णांक cpu)
अणु
	वापस pagevec_count(&per_cpu(lru_pvecs.activate_page, cpu)) != 0;
पूर्ण

अटल व्योम activate_page(काष्ठा page *page)
अणु
	page = compound_head(page);
	अगर (PageLRU(page) && !PageActive(page) && !PageUnevictable(page)) अणु
		काष्ठा pagevec *pvec;

		local_lock(&lru_pvecs.lock);
		pvec = this_cpu_ptr(&lru_pvecs.activate_page);
		get_page(page);
		अगर (pagevec_add_and_need_flush(pvec, page))
			pagevec_lru_move_fn(pvec, __activate_page);
		local_unlock(&lru_pvecs.lock);
	पूर्ण
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम activate_page_drain(पूर्णांक cpu)
अणु
पूर्ण

अटल व्योम activate_page(काष्ठा page *page)
अणु
	काष्ठा lruvec *lruvec;

	page = compound_head(page);
	अगर (TestClearPageLRU(page)) अणु
		lruvec = lock_page_lruvec_irq(page);
		__activate_page(page, lruvec);
		unlock_page_lruvec_irq(lruvec);
		SetPageLRU(page);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम __lru_cache_activate_page(काष्ठा page *page)
अणु
	काष्ठा pagevec *pvec;
	पूर्णांक i;

	local_lock(&lru_pvecs.lock);
	pvec = this_cpu_ptr(&lru_pvecs.lru_add);

	/*
	 * Search backwards on the optimistic assumption that the page being
	 * activated has just been added to this pagevec. Note that only
	 * the local pagevec is examined as a !PageLRU page could be in the
	 * process of being released, reclaimed, migrated or on a remote
	 * pagevec that is currently being drained. Furthermore, marking
	 * a remote pagevec's page PageActive potentially hits a race where
	 * a page is marked PageActive just after it is added to the inactive
	 * list causing accounting errors and BUG_ON checks to trigger.
	 */
	क्रम (i = pagevec_count(pvec) - 1; i >= 0; i--) अणु
		काष्ठा page *pagevec_page = pvec->pages[i];

		अगर (pagevec_page == page) अणु
			SetPageActive(page);
			अवरोध;
		पूर्ण
	पूर्ण

	local_unlock(&lru_pvecs.lock);
पूर्ण

/*
 * Mark a page as having seen activity.
 *
 * inactive,unreferenced	->	inactive,referenced
 * inactive,referenced		->	active,unreferenced
 * active,unreferenced		->	active,referenced
 *
 * When a newly allocated page is not yet visible, so safe क्रम non-atomic ops,
 * __SetPageReferenced(page) may be substituted क्रम mark_page_accessed(page).
 */
व्योम mark_page_accessed(काष्ठा page *page)
अणु
	page = compound_head(page);

	अगर (!PageReferenced(page)) अणु
		SetPageReferenced(page);
	पूर्ण अन्यथा अगर (PageUnevictable(page)) अणु
		/*
		 * Unevictable pages are on the "LRU_UNEVICTABLE" list. But,
		 * this list is never rotated or मुख्यtained, so marking an
		 * evictable page accessed has no effect.
		 */
	पूर्ण अन्यथा अगर (!PageActive(page)) अणु
		/*
		 * If the page is on the LRU, queue it क्रम activation via
		 * lru_pvecs.activate_page. Otherwise, assume the page is on a
		 * pagevec, mark it active and it'll be moved to the active
		 * LRU on the next drain.
		 */
		अगर (PageLRU(page))
			activate_page(page);
		अन्यथा
			__lru_cache_activate_page(page);
		ClearPageReferenced(page);
		workingset_activation(page);
	पूर्ण
	अगर (page_is_idle(page))
		clear_page_idle(page);
पूर्ण
EXPORT_SYMBOL(mark_page_accessed);

/**
 * lru_cache_add - add a page to a page list
 * @page: the page to be added to the LRU.
 *
 * Queue the page क्रम addition to the LRU via pagevec. The decision on whether
 * to add the page to the [in]active [file|anon] list is deferred until the
 * pagevec is drained. This gives a chance क्रम the caller of lru_cache_add()
 * have the page added to the active list using mark_page_accessed().
 */
व्योम lru_cache_add(काष्ठा page *page)
अणु
	काष्ठा pagevec *pvec;

	VM_BUG_ON_PAGE(PageActive(page) && PageUnevictable(page), page);
	VM_BUG_ON_PAGE(PageLRU(page), page);

	get_page(page);
	local_lock(&lru_pvecs.lock);
	pvec = this_cpu_ptr(&lru_pvecs.lru_add);
	अगर (pagevec_add_and_need_flush(pvec, page))
		__pagevec_lru_add(pvec);
	local_unlock(&lru_pvecs.lock);
पूर्ण
EXPORT_SYMBOL(lru_cache_add);

/**
 * lru_cache_add_inactive_or_unevictable
 * @page:  the page to be added to LRU
 * @vma:   vma in which page is mapped क्रम determining reclaimability
 *
 * Place @page on the inactive or unevictable LRU list, depending on its
 * evictability.
 */
व्योम lru_cache_add_inactive_or_unevictable(काष्ठा page *page,
					 काष्ठा vm_area_काष्ठा *vma)
अणु
	bool unevictable;

	VM_BUG_ON_PAGE(PageLRU(page), page);

	unevictable = (vma->vm_flags & (VM_LOCKED | VM_SPECIAL)) == VM_LOCKED;
	अगर (unlikely(unevictable) && !TestSetPageMlocked(page)) अणु
		पूर्णांक nr_pages = thp_nr_pages(page);
		/*
		 * We use the irq-unsafe __mod_zone_page_state because this
		 * counter is not modअगरied from पूर्णांकerrupt context, and the pte
		 * lock is held(spinlock), which implies preemption disabled.
		 */
		__mod_zone_page_state(page_zone(page), NR_MLOCK, nr_pages);
		count_vm_events(UNEVICTABLE_PGMLOCKED, nr_pages);
	पूर्ण
	lru_cache_add(page);
पूर्ण

/*
 * If the page can not be invalidated, it is moved to the
 * inactive list to speed up its reclaim.  It is moved to the
 * head of the list, rather than the tail, to give the flusher
 * thपढ़ोs some समय to ग_लिखो it out, as this is much more
 * effective than the single-page ग_लिखोout from reclaim.
 *
 * If the page isn't page_mapped and dirty/ग_लिखोback, the page
 * could reclaim asap using PG_reclaim.
 *
 * 1. active, mapped page -> none
 * 2. active, dirty/ग_लिखोback page -> inactive, head, PG_reclaim
 * 3. inactive, mapped page -> none
 * 4. inactive, dirty/ग_लिखोback page -> inactive, head, PG_reclaim
 * 5. inactive, clean -> inactive, tail
 * 6. Others -> none
 *
 * In 4, why it moves inactive's head, the VM expects the page would
 * be ग_लिखो it out by flusher thपढ़ोs as this is much more effective
 * than the single-page ग_लिखोout from reclaim.
 */
अटल व्योम lru_deactivate_file_fn(काष्ठा page *page, काष्ठा lruvec *lruvec)
अणु
	bool active = PageActive(page);
	पूर्णांक nr_pages = thp_nr_pages(page);

	अगर (PageUnevictable(page))
		वापस;

	/* Some processes are using the page */
	अगर (page_mapped(page))
		वापस;

	del_page_from_lru_list(page, lruvec);
	ClearPageActive(page);
	ClearPageReferenced(page);

	अगर (PageWriteback(page) || PageDirty(page)) अणु
		/*
		 * PG_reclaim could be raced with end_page_ग_लिखोback
		 * It can make पढ़ोahead confusing.  But race winकरोw
		 * is _really_ small and  it's non-critical problem.
		 */
		add_page_to_lru_list(page, lruvec);
		SetPageReclaim(page);
	पूर्ण अन्यथा अणु
		/*
		 * The page's ग_लिखोback ends up during pagevec
		 * We moves tha page पूर्णांकo tail of inactive.
		 */
		add_page_to_lru_list_tail(page, lruvec);
		__count_vm_events(PGROTATED, nr_pages);
	पूर्ण

	अगर (active) अणु
		__count_vm_events(PGDEACTIVATE, nr_pages);
		__count_memcg_events(lruvec_memcg(lruvec), PGDEACTIVATE,
				     nr_pages);
	पूर्ण
पूर्ण

अटल व्योम lru_deactivate_fn(काष्ठा page *page, काष्ठा lruvec *lruvec)
अणु
	अगर (PageActive(page) && !PageUnevictable(page)) अणु
		पूर्णांक nr_pages = thp_nr_pages(page);

		del_page_from_lru_list(page, lruvec);
		ClearPageActive(page);
		ClearPageReferenced(page);
		add_page_to_lru_list(page, lruvec);

		__count_vm_events(PGDEACTIVATE, nr_pages);
		__count_memcg_events(lruvec_memcg(lruvec), PGDEACTIVATE,
				     nr_pages);
	पूर्ण
पूर्ण

अटल व्योम lru_lazyमुक्त_fn(काष्ठा page *page, काष्ठा lruvec *lruvec)
अणु
	अगर (PageAnon(page) && PageSwapBacked(page) &&
	    !PageSwapCache(page) && !PageUnevictable(page)) अणु
		पूर्णांक nr_pages = thp_nr_pages(page);

		del_page_from_lru_list(page, lruvec);
		ClearPageActive(page);
		ClearPageReferenced(page);
		/*
		 * Lazyमुक्त pages are clean anonymous pages.  They have
		 * PG_swapbacked flag cleared, to distinguish them from normal
		 * anonymous pages
		 */
		ClearPageSwapBacked(page);
		add_page_to_lru_list(page, lruvec);

		__count_vm_events(PGLAZYFREE, nr_pages);
		__count_memcg_events(lruvec_memcg(lruvec), PGLAZYFREE,
				     nr_pages);
	पूर्ण
पूर्ण

/*
 * Drain pages out of the cpu's pagevecs.
 * Either "cpu" is the current CPU, and preemption has alपढ़ोy been
 * disabled; or "cpu" is being hot-unplugged, and is alपढ़ोy dead.
 */
व्योम lru_add_drain_cpu(पूर्णांक cpu)
अणु
	काष्ठा pagevec *pvec = &per_cpu(lru_pvecs.lru_add, cpu);

	अगर (pagevec_count(pvec))
		__pagevec_lru_add(pvec);

	pvec = &per_cpu(lru_rotate.pvec, cpu);
	/* Disabling पूर्णांकerrupts below acts as a compiler barrier. */
	अगर (data_race(pagevec_count(pvec))) अणु
		अचिन्हित दीर्घ flags;

		/* No harm करोne अगर a racing पूर्णांकerrupt alपढ़ोy did this */
		local_lock_irqsave(&lru_rotate.lock, flags);
		pagevec_lru_move_fn(pvec, pagevec_move_tail_fn);
		local_unlock_irqrestore(&lru_rotate.lock, flags);
	पूर्ण

	pvec = &per_cpu(lru_pvecs.lru_deactivate_file, cpu);
	अगर (pagevec_count(pvec))
		pagevec_lru_move_fn(pvec, lru_deactivate_file_fn);

	pvec = &per_cpu(lru_pvecs.lru_deactivate, cpu);
	अगर (pagevec_count(pvec))
		pagevec_lru_move_fn(pvec, lru_deactivate_fn);

	pvec = &per_cpu(lru_pvecs.lru_lazyमुक्त, cpu);
	अगर (pagevec_count(pvec))
		pagevec_lru_move_fn(pvec, lru_lazyमुक्त_fn);

	activate_page_drain(cpu);
	invalidate_bh_lrus_cpu(cpu);
पूर्ण

/**
 * deactivate_file_page - क्रमcefully deactivate a file page
 * @page: page to deactivate
 *
 * This function hपूर्णांकs the VM that @page is a good reclaim candidate,
 * क्रम example अगर its invalidation fails due to the page being dirty
 * or under ग_लिखोback.
 */
व्योम deactivate_file_page(काष्ठा page *page)
अणु
	/*
	 * In a workload with many unevictable page such as mprotect,
	 * unevictable page deactivation क्रम accelerating reclaim is poपूर्णांकless.
	 */
	अगर (PageUnevictable(page))
		वापस;

	अगर (likely(get_page_unless_zero(page))) अणु
		काष्ठा pagevec *pvec;

		local_lock(&lru_pvecs.lock);
		pvec = this_cpu_ptr(&lru_pvecs.lru_deactivate_file);

		अगर (pagevec_add_and_need_flush(pvec, page))
			pagevec_lru_move_fn(pvec, lru_deactivate_file_fn);
		local_unlock(&lru_pvecs.lock);
	पूर्ण
पूर्ण

/*
 * deactivate_page - deactivate a page
 * @page: page to deactivate
 *
 * deactivate_page() moves @page to the inactive list अगर @page was on the active
 * list and was not an unevictable page.  This is करोne to accelerate the reclaim
 * of @page.
 */
व्योम deactivate_page(काष्ठा page *page)
अणु
	अगर (PageLRU(page) && PageActive(page) && !PageUnevictable(page)) अणु
		काष्ठा pagevec *pvec;

		local_lock(&lru_pvecs.lock);
		pvec = this_cpu_ptr(&lru_pvecs.lru_deactivate);
		get_page(page);
		अगर (pagevec_add_and_need_flush(pvec, page))
			pagevec_lru_move_fn(pvec, lru_deactivate_fn);
		local_unlock(&lru_pvecs.lock);
	पूर्ण
पूर्ण

/**
 * mark_page_lazyमुक्त - make an anon page lazyमुक्त
 * @page: page to deactivate
 *
 * mark_page_lazyमुक्त() moves @page to the inactive file list.
 * This is करोne to accelerate the reclaim of @page.
 */
व्योम mark_page_lazyमुक्त(काष्ठा page *page)
अणु
	अगर (PageLRU(page) && PageAnon(page) && PageSwapBacked(page) &&
	    !PageSwapCache(page) && !PageUnevictable(page)) अणु
		काष्ठा pagevec *pvec;

		local_lock(&lru_pvecs.lock);
		pvec = this_cpu_ptr(&lru_pvecs.lru_lazyमुक्त);
		get_page(page);
		अगर (pagevec_add_and_need_flush(pvec, page))
			pagevec_lru_move_fn(pvec, lru_lazyमुक्त_fn);
		local_unlock(&lru_pvecs.lock);
	पूर्ण
पूर्ण

व्योम lru_add_drain(व्योम)
अणु
	local_lock(&lru_pvecs.lock);
	lru_add_drain_cpu(smp_processor_id());
	local_unlock(&lru_pvecs.lock);
पूर्ण

व्योम lru_add_drain_cpu_zone(काष्ठा zone *zone)
अणु
	local_lock(&lru_pvecs.lock);
	lru_add_drain_cpu(smp_processor_id());
	drain_local_pages(zone);
	local_unlock(&lru_pvecs.lock);
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल DEFINE_PER_CPU(काष्ठा work_काष्ठा, lru_add_drain_work);

अटल व्योम lru_add_drain_per_cpu(काष्ठा work_काष्ठा *dummy)
अणु
	lru_add_drain();
पूर्ण

/*
 * Doesn't need any cpu hotplug locking because we करो rely on per-cpu
 * kworkers being shut करोwn beक्रमe our page_alloc_cpu_dead callback is
 * executed on the offlined cpu.
 * Calling this function with cpu hotplug locks held can actually lead
 * to obscure indirect dependencies via WQ context.
 */
अंतरभूत व्योम __lru_add_drain_all(bool क्रमce_all_cpus)
अणु
	/*
	 * lru_drain_gen - Global pages generation number
	 *
	 * (A) Definition: global lru_drain_gen = x implies that all generations
	 *     0 < n <= x are alपढ़ोy *scheduled* क्रम draining.
	 *
	 * This is an optimization क्रम the highly-contended use हाल where a
	 * user space workload keeps स्थिरantly generating a flow of pages क्रम
	 * each CPU.
	 */
	अटल अचिन्हित पूर्णांक lru_drain_gen;
	अटल काष्ठा cpumask has_work;
	अटल DEFINE_MUTEX(lock);
	अचिन्हित cpu, this_gen;

	/*
	 * Make sure nobody triggers this path beक्रमe mm_percpu_wq is fully
	 * initialized.
	 */
	अगर (WARN_ON(!mm_percpu_wq))
		वापस;

	/*
	 * Guarantee pagevec counter stores visible by this CPU are visible to
	 * other CPUs beक्रमe loading the current drain generation.
	 */
	smp_mb();

	/*
	 * (B) Locally cache global LRU draining generation number
	 *
	 * The पढ़ो barrier ensures that the counter is loaded beक्रमe the mutex
	 * is taken. It pairs with smp_mb() inside the mutex critical section
	 * at (D).
	 */
	this_gen = smp_load_acquire(&lru_drain_gen);

	mutex_lock(&lock);

	/*
	 * (C) Exit the draining operation अगर a newer generation, from another
	 * lru_add_drain_all(), was alपढ़ोy scheduled क्रम draining. Check (A).
	 */
	अगर (unlikely(this_gen != lru_drain_gen && !क्रमce_all_cpus))
		जाओ करोne;

	/*
	 * (D) Increment global generation number
	 *
	 * Pairs with smp_load_acquire() at (B), outside of the critical
	 * section. Use a full memory barrier to guarantee that the new global
	 * drain generation number is stored beक्रमe loading pagevec counters.
	 *
	 * This pairing must be करोne here, beक्रमe the क्रम_each_online_cpu loop
	 * below which drains the page vectors.
	 *
	 * Let x, y, and z represent some प्रणाली CPU numbers, where x < y < z.
	 * Assume CPU #z is in the middle of the क्रम_each_online_cpu loop
	 * below and has alपढ़ोy reached CPU #y's per-cpu data. CPU #x comes
	 * aदीर्घ, adds some pages to its per-cpu vectors, then calls
	 * lru_add_drain_all().
	 *
	 * If the paired barrier is करोne at any later step, e.g. after the
	 * loop, CPU #x will just निकास at (C) and miss flushing out all of its
	 * added pages.
	 */
	WRITE_ONCE(lru_drain_gen, lru_drain_gen + 1);
	smp_mb();

	cpumask_clear(&has_work);
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा work_काष्ठा *work = &per_cpu(lru_add_drain_work, cpu);

		अगर (क्रमce_all_cpus ||
		    pagevec_count(&per_cpu(lru_pvecs.lru_add, cpu)) ||
		    data_race(pagevec_count(&per_cpu(lru_rotate.pvec, cpu))) ||
		    pagevec_count(&per_cpu(lru_pvecs.lru_deactivate_file, cpu)) ||
		    pagevec_count(&per_cpu(lru_pvecs.lru_deactivate, cpu)) ||
		    pagevec_count(&per_cpu(lru_pvecs.lru_lazyमुक्त, cpu)) ||
		    need_activate_page_drain(cpu) ||
		    has_bh_in_lru(cpu, शून्य)) अणु
			INIT_WORK(work, lru_add_drain_per_cpu);
			queue_work_on(cpu, mm_percpu_wq, work);
			__cpumask_set_cpu(cpu, &has_work);
		पूर्ण
	पूर्ण

	क्रम_each_cpu(cpu, &has_work)
		flush_work(&per_cpu(lru_add_drain_work, cpu));

करोne:
	mutex_unlock(&lock);
पूर्ण

व्योम lru_add_drain_all(व्योम)
अणु
	__lru_add_drain_all(false);
पूर्ण
#अन्यथा
व्योम lru_add_drain_all(व्योम)
अणु
	lru_add_drain();
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

atomic_t lru_disable_count = ATOMIC_INIT(0);

/*
 * lru_cache_disable() needs to be called beक्रमe we start compiling
 * a list of pages to be migrated using isolate_lru_page().
 * It drains pages on LRU cache and then disable on all cpus until
 * lru_cache_enable is called.
 *
 * Must be paired with a call to lru_cache_enable().
 */
व्योम lru_cache_disable(व्योम)
अणु
	atomic_inc(&lru_disable_count);
#अगर_घोषित CONFIG_SMP
	/*
	 * lru_add_drain_all in the क्रमce mode will schedule draining on
	 * all online CPUs so any calls of lru_cache_disabled wrapped by
	 * local_lock or preemption disabled would be ordered by that.
	 * The atomic operation करोesn't need to have stronger ordering
	 * requirements because that is enक्रमeced by the scheduling
	 * guarantees.
	 */
	__lru_add_drain_all(true);
#अन्यथा
	lru_add_drain();
#पूर्ण_अगर
पूर्ण

/**
 * release_pages - batched put_page()
 * @pages: array of pages to release
 * @nr: number of pages
 *
 * Decrement the reference count on all the pages in @pages.  If it
 * fell to zero, हटाओ the page from the LRU and मुक्त it.
 */
व्योम release_pages(काष्ठा page **pages, पूर्णांक nr)
अणु
	पूर्णांक i;
	LIST_HEAD(pages_to_मुक्त);
	काष्ठा lruvec *lruvec = शून्य;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक lock_batch;

	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा page *page = pages[i];

		/*
		 * Make sure the IRQ-safe lock-holding समय करोes not get
		 * excessive with a continuous string of pages from the
		 * same lruvec. The lock is held only अगर lruvec != शून्य.
		 */
		अगर (lruvec && ++lock_batch == SWAP_CLUSTER_MAX) अणु
			unlock_page_lruvec_irqrestore(lruvec, flags);
			lruvec = शून्य;
		पूर्ण

		page = compound_head(page);
		अगर (is_huge_zero_page(page))
			जारी;

		अगर (is_zone_device_page(page)) अणु
			अगर (lruvec) अणु
				unlock_page_lruvec_irqrestore(lruvec, flags);
				lruvec = शून्य;
			पूर्ण
			/*
			 * ZONE_DEVICE pages that वापस 'false' from
			 * page_is_devmap_managed() करो not require special
			 * processing, and instead, expect a call to
			 * put_page_testzero().
			 */
			अगर (page_is_devmap_managed(page)) अणु
				put_devmap_managed_page(page);
				जारी;
			पूर्ण
			अगर (put_page_testzero(page))
				put_dev_pagemap(page->pgmap);
			जारी;
		पूर्ण

		अगर (!put_page_testzero(page))
			जारी;

		अगर (PageCompound(page)) अणु
			अगर (lruvec) अणु
				unlock_page_lruvec_irqrestore(lruvec, flags);
				lruvec = शून्य;
			पूर्ण
			__put_compound_page(page);
			जारी;
		पूर्ण

		अगर (PageLRU(page)) अणु
			काष्ठा lruvec *prev_lruvec = lruvec;

			lruvec = relock_page_lruvec_irqsave(page, lruvec,
									&flags);
			अगर (prev_lruvec != lruvec)
				lock_batch = 0;

			del_page_from_lru_list(page, lruvec);
			__clear_page_lru_flags(page);
		पूर्ण

		__ClearPageWaiters(page);

		list_add(&page->lru, &pages_to_मुक्त);
	पूर्ण
	अगर (lruvec)
		unlock_page_lruvec_irqrestore(lruvec, flags);

	mem_cgroup_unअक्षरge_list(&pages_to_मुक्त);
	मुक्त_unref_page_list(&pages_to_मुक्त);
पूर्ण
EXPORT_SYMBOL(release_pages);

/*
 * The pages which we're about to release may be in the deferred lru-addition
 * queues.  That would prevent them from really being मुक्तd right now.  That's
 * OK from a correctness poपूर्णांक of view but is inefficient - those pages may be
 * cache-warm and we want to give them back to the page allocator ASAP.
 *
 * So __pagevec_release() will drain those queues here.  __pagevec_lru_add()
 * and __pagevec_lru_add_active() call release_pages() directly to aव्योम
 * mutual recursion.
 */
व्योम __pagevec_release(काष्ठा pagevec *pvec)
अणु
	अगर (!pvec->percpu_pvec_drained) अणु
		lru_add_drain();
		pvec->percpu_pvec_drained = true;
	पूर्ण
	release_pages(pvec->pages, pagevec_count(pvec));
	pagevec_reinit(pvec);
पूर्ण
EXPORT_SYMBOL(__pagevec_release);

अटल व्योम __pagevec_lru_add_fn(काष्ठा page *page, काष्ठा lruvec *lruvec)
अणु
	पूर्णांक was_unevictable = TestClearPageUnevictable(page);
	पूर्णांक nr_pages = thp_nr_pages(page);

	VM_BUG_ON_PAGE(PageLRU(page), page);

	/*
	 * Page becomes evictable in two ways:
	 * 1) Within LRU lock [munlock_vma_page() and __munlock_pagevec()].
	 * 2) Beक्रमe acquiring LRU lock to put the page to correct LRU and then
	 *   a) करो PageLRU check with lock [check_move_unevictable_pages]
	 *   b) करो PageLRU check beक्रमe lock [clear_page_mlock]
	 *
	 * (1) & (2a) are ok as LRU lock will serialize them. For (2b), we need
	 * following strict ordering:
	 *
	 * #0: __pagevec_lru_add_fn		#1: clear_page_mlock
	 *
	 * SetPageLRU()				TestClearPageMlocked()
	 * smp_mb() // explicit ordering	// above provides strict
	 *					// ordering
	 * PageMlocked()			PageLRU()
	 *
	 *
	 * अगर '#1' does not observe setting of PG_lru by '#0' and fails
	 * isolation, the explicit barrier will make sure that page_evictable
	 * check will put the page in correct LRU. Without smp_mb(), SetPageLRU
	 * can be reordered after PageMlocked check and can make '#1' to fail
	 * the isolation of the page whose Mlocked bit is cleared (#0 is also
	 * looking at the same page) and the evictable page will be stअक्रमed
	 * in an unevictable LRU.
	 */
	SetPageLRU(page);
	smp_mb__after_atomic();

	अगर (page_evictable(page)) अणु
		अगर (was_unevictable)
			__count_vm_events(UNEVICTABLE_PGRESCUED, nr_pages);
	पूर्ण अन्यथा अणु
		ClearPageActive(page);
		SetPageUnevictable(page);
		अगर (!was_unevictable)
			__count_vm_events(UNEVICTABLE_PGCULLED, nr_pages);
	पूर्ण

	add_page_to_lru_list(page, lruvec);
	trace_mm_lru_insertion(page);
पूर्ण

/*
 * Add the passed pages to the LRU, then drop the caller's refcount
 * on them.  Reinitialises the caller's pagevec.
 */
व्योम __pagevec_lru_add(काष्ठा pagevec *pvec)
अणु
	पूर्णांक i;
	काष्ठा lruvec *lruvec = शून्य;
	अचिन्हित दीर्घ flags = 0;

	क्रम (i = 0; i < pagevec_count(pvec); i++) अणु
		काष्ठा page *page = pvec->pages[i];

		lruvec = relock_page_lruvec_irqsave(page, lruvec, &flags);
		__pagevec_lru_add_fn(page, lruvec);
	पूर्ण
	अगर (lruvec)
		unlock_page_lruvec_irqrestore(lruvec, flags);
	release_pages(pvec->pages, pvec->nr);
	pagevec_reinit(pvec);
पूर्ण

/**
 * pagevec_हटाओ_exceptionals - pagevec exceptionals pruning
 * @pvec:	The pagevec to prune
 *
 * find_get_entries() fills both pages and XArray value entries (aka
 * exceptional entries) पूर्णांकo the pagevec.  This function prunes all
 * exceptionals from @pvec without leaving holes, so that it can be
 * passed on to page-only pagevec operations.
 */
व्योम pagevec_हटाओ_exceptionals(काष्ठा pagevec *pvec)
अणु
	पूर्णांक i, j;

	क्रम (i = 0, j = 0; i < pagevec_count(pvec); i++) अणु
		काष्ठा page *page = pvec->pages[i];
		अगर (!xa_is_value(page))
			pvec->pages[j++] = page;
	पूर्ण
	pvec->nr = j;
पूर्ण

/**
 * pagevec_lookup_range - gang pagecache lookup
 * @pvec:	Where the resulting pages are placed
 * @mapping:	The address_space to search
 * @start:	The starting page index
 * @end:	The final page index
 *
 * pagevec_lookup_range() will search क्रम & वापस a group of up to PAGEVEC_SIZE
 * pages in the mapping starting from index @start and upto index @end
 * (inclusive).  The pages are placed in @pvec.  pagevec_lookup() takes a
 * reference against the pages in @pvec.
 *
 * The search वापसs a group of mapping-contiguous pages with ascending
 * indexes.  There may be holes in the indices due to not-present pages. We
 * also update @start to index the next page क्रम the traversal.
 *
 * pagevec_lookup_range() वापसs the number of pages which were found. If this
 * number is smaller than PAGEVEC_SIZE, the end of specअगरied range has been
 * reached.
 */
अचिन्हित pagevec_lookup_range(काष्ठा pagevec *pvec,
		काष्ठा address_space *mapping, pgoff_t *start, pgoff_t end)
अणु
	pvec->nr = find_get_pages_range(mapping, start, end, PAGEVEC_SIZE,
					pvec->pages);
	वापस pagevec_count(pvec);
पूर्ण
EXPORT_SYMBOL(pagevec_lookup_range);

अचिन्हित pagevec_lookup_range_tag(काष्ठा pagevec *pvec,
		काष्ठा address_space *mapping, pgoff_t *index, pgoff_t end,
		xa_mark_t tag)
अणु
	pvec->nr = find_get_pages_range_tag(mapping, index, end, tag,
					PAGEVEC_SIZE, pvec->pages);
	वापस pagevec_count(pvec);
पूर्ण
EXPORT_SYMBOL(pagevec_lookup_range_tag);

/*
 * Perक्रमm any setup क्रम the swap प्रणाली
 */
व्योम __init swap_setup(व्योम)
अणु
	अचिन्हित दीर्घ megs = totalram_pages() >> (20 - PAGE_SHIFT);

	/* Use a smaller cluster क्रम small-memory machines */
	अगर (megs < 16)
		page_cluster = 2;
	अन्यथा
		page_cluster = 3;
	/*
	 * Right now other parts of the प्रणाली means that we
	 * _really_ करोn't want to cluster much more
	 */
पूर्ण

#अगर_घोषित CONFIG_DEV_PAGEMAP_OPS
व्योम put_devmap_managed_page(काष्ठा page *page)
अणु
	पूर्णांक count;

	अगर (WARN_ON_ONCE(!page_is_devmap_managed(page)))
		वापस;

	count = page_ref_dec_वापस(page);

	/*
	 * devmap page refcounts are 1-based, rather than 0-based: अगर
	 * refcount is 1, then the page is मुक्त and the refcount is
	 * stable because nobody holds a reference on the page.
	 */
	अगर (count == 1)
		मुक्त_devmap_managed_page(page);
	अन्यथा अगर (!count)
		__put_page(page);
पूर्ण
EXPORT_SYMBOL(put_devmap_managed_page);
#पूर्ण_अगर
