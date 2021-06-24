<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/mm/swap_state.c
 *
 *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 *  Swap reorganised 29.12.95, Stephen Tweedie
 *
 *  Rewritten to use page cache, (C) 1998 Stephen Tweedie
 */
#समावेश <linux/mm.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/init.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/migrate.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/swap_slots.h>
#समावेश <linux/huge_mm.h>
#समावेश <linux/shmem_fs.h>
#समावेश "internal.h"

/*
 * swapper_space is a fiction, retained to simplअगरy the path through
 * vmscan's shrink_page_list.
 */
अटल स्थिर काष्ठा address_space_operations swap_aops = अणु
	.ग_लिखोpage	= swap_ग_लिखोpage,
	.set_page_dirty	= swap_set_page_dirty,
#अगर_घोषित CONFIG_MIGRATION
	.migratepage	= migrate_page,
#पूर्ण_अगर
पूर्ण;

काष्ठा address_space *swapper_spaces[MAX_SWAPखाताS] __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक nr_swapper_spaces[MAX_SWAPखाताS] __पढ़ो_mostly;
अटल bool enable_vma_पढ़ोahead __पढ़ो_mostly = true;

#घोषणा SWAP_RA_WIN_SHIFT	(PAGE_SHIFT / 2)
#घोषणा SWAP_RA_HITS_MASK	((1UL << SWAP_RA_WIN_SHIFT) - 1)
#घोषणा SWAP_RA_HITS_MAX	SWAP_RA_HITS_MASK
#घोषणा SWAP_RA_WIN_MASK	(~PAGE_MASK & ~SWAP_RA_HITS_MASK)

#घोषणा SWAP_RA_HITS(v)		((v) & SWAP_RA_HITS_MASK)
#घोषणा SWAP_RA_WIN(v)		(((v) & SWAP_RA_WIN_MASK) >> SWAP_RA_WIN_SHIFT)
#घोषणा SWAP_RA_ADDR(v)		((v) & PAGE_MASK)

#घोषणा SWAP_RA_VAL(addr, win, hits)				\
	(((addr) & PAGE_MASK) |					\
	 (((win) << SWAP_RA_WIN_SHIFT) & SWAP_RA_WIN_MASK) |	\
	 ((hits) & SWAP_RA_HITS_MASK))

/* Initial पढ़ोahead hits is 4 to start up with a small winकरोw */
#घोषणा GET_SWAP_RA_VAL(vma)					\
	(atomic_दीर्घ_पढ़ो(&(vma)->swap_पढ़ोahead_info) ? : 4)

#घोषणा INC_CACHE_INFO(x)	data_race(swap_cache_info.x++)
#घोषणा ADD_CACHE_INFO(x, nr)	data_race(swap_cache_info.x += (nr))

अटल काष्ठा अणु
	अचिन्हित दीर्घ add_total;
	अचिन्हित दीर्घ del_total;
	अचिन्हित दीर्घ find_success;
	अचिन्हित दीर्घ find_total;
पूर्ण swap_cache_info;

अटल atomic_t swapin_पढ़ोahead_hits = ATOMIC_INIT(4);

व्योम show_swap_cache_info(व्योम)
अणु
	prपूर्णांकk("%lu pages in swap cache\n", total_swapcache_pages());
	prपूर्णांकk("Swap cache stats: add %lu, delete %lu, find %lu/%lu\n",
		swap_cache_info.add_total, swap_cache_info.del_total,
		swap_cache_info.find_success, swap_cache_info.find_total);
	prपूर्णांकk("Free swap  = %ldkB\n",
		get_nr_swap_pages() << (PAGE_SHIFT - 10));
	prपूर्णांकk("Total swap = %lukB\n", total_swap_pages << (PAGE_SHIFT - 10));
पूर्ण

व्योम *get_shaकरोw_from_swap_cache(swp_entry_t entry)
अणु
	काष्ठा address_space *address_space = swap_address_space(entry);
	pgoff_t idx = swp_offset(entry);
	काष्ठा page *page;

	page = xa_load(&address_space->i_pages, idx);
	अगर (xa_is_value(page))
		वापस page;
	वापस शून्य;
पूर्ण

/*
 * add_to_swap_cache resembles add_to_page_cache_locked on swapper_space,
 * but sets SwapCache flag and निजी instead of mapping and index.
 */
पूर्णांक add_to_swap_cache(काष्ठा page *page, swp_entry_t entry,
			gfp_t gfp, व्योम **shaकरोwp)
अणु
	काष्ठा address_space *address_space = swap_address_space(entry);
	pgoff_t idx = swp_offset(entry);
	XA_STATE_ORDER(xas, &address_space->i_pages, idx, compound_order(page));
	अचिन्हित दीर्घ i, nr = thp_nr_pages(page);
	व्योम *old;

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(PageSwapCache(page), page);
	VM_BUG_ON_PAGE(!PageSwapBacked(page), page);

	page_ref_add(page, nr);
	SetPageSwapCache(page);

	करो अणु
		अचिन्हित दीर्घ nr_shaकरोws = 0;

		xas_lock_irq(&xas);
		xas_create_range(&xas);
		अगर (xas_error(&xas))
			जाओ unlock;
		क्रम (i = 0; i < nr; i++) अणु
			VM_BUG_ON_PAGE(xas.xa_index != idx + i, page);
			old = xas_load(&xas);
			अगर (xa_is_value(old)) अणु
				nr_shaकरोws++;
				अगर (shaकरोwp)
					*shaकरोwp = old;
			पूर्ण
			set_page_निजी(page + i, entry.val + i);
			xas_store(&xas, page);
			xas_next(&xas);
		पूर्ण
		address_space->nrpages += nr;
		__mod_node_page_state(page_pgdat(page), NR_खाता_PAGES, nr);
		__mod_lruvec_page_state(page, NR_SWAPCACHE, nr);
		ADD_CACHE_INFO(add_total, nr);
unlock:
		xas_unlock_irq(&xas);
	पूर्ण जबतक (xas_nomem(&xas, gfp));

	अगर (!xas_error(&xas))
		वापस 0;

	ClearPageSwapCache(page);
	page_ref_sub(page, nr);
	वापस xas_error(&xas);
पूर्ण

/*
 * This must be called only on pages that have
 * been verअगरied to be in the swap cache.
 */
व्योम __delete_from_swap_cache(काष्ठा page *page,
			swp_entry_t entry, व्योम *shaकरोw)
अणु
	काष्ठा address_space *address_space = swap_address_space(entry);
	पूर्णांक i, nr = thp_nr_pages(page);
	pgoff_t idx = swp_offset(entry);
	XA_STATE(xas, &address_space->i_pages, idx);

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(!PageSwapCache(page), page);
	VM_BUG_ON_PAGE(PageWriteback(page), page);

	क्रम (i = 0; i < nr; i++) अणु
		व्योम *entry = xas_store(&xas, shaकरोw);
		VM_BUG_ON_PAGE(entry != page, entry);
		set_page_निजी(page + i, 0);
		xas_next(&xas);
	पूर्ण
	ClearPageSwapCache(page);
	address_space->nrpages -= nr;
	__mod_node_page_state(page_pgdat(page), NR_खाता_PAGES, -nr);
	__mod_lruvec_page_state(page, NR_SWAPCACHE, -nr);
	ADD_CACHE_INFO(del_total, nr);
पूर्ण

/**
 * add_to_swap - allocate swap space क्रम a page
 * @page: page we want to move to swap
 *
 * Allocate swap space क्रम the page and add the page to the
 * swap cache.  Caller needs to hold the page lock. 
 */
पूर्णांक add_to_swap(काष्ठा page *page)
अणु
	swp_entry_t entry;
	पूर्णांक err;

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(!PageUptodate(page), page);

	entry = get_swap_page(page);
	अगर (!entry.val)
		वापस 0;

	/*
	 * XArray node allocations from PF_MEMALLOC contexts could
	 * completely exhaust the page allocator. __GFP_NOMEMALLOC
	 * stops emergency reserves from being allocated.
	 *
	 * TODO: this could cause a theoretical memory reclaim
	 * deadlock in the swap out path.
	 */
	/*
	 * Add it to the swap cache.
	 */
	err = add_to_swap_cache(page, entry,
			__GFP_HIGH|__GFP_NOMEMALLOC|__GFP_NOWARN, शून्य);
	अगर (err)
		/*
		 * add_to_swap_cache() करोesn't वापस -EEXIST, so we can safely
		 * clear SWAP_HAS_CACHE flag.
		 */
		जाओ fail;
	/*
	 * Normally the page will be dirtied in unmap because its pte should be
	 * dirty. A special हाल is MADV_FREE page. The page's pte could have
	 * dirty bit cleared but the page's SwapBacked bit is still set because
	 * clearing the dirty bit and SwapBacked bit has no lock रक्षित. For
	 * such page, unmap will not set dirty bit क्रम it, so page reclaim will
	 * not ग_लिखो the page out. This can cause data corruption when the page
	 * is swap in later. Always setting the dirty bit क्रम the page solves
	 * the problem.
	 */
	set_page_dirty(page);

	वापस 1;

fail:
	put_swap_page(page, entry);
	वापस 0;
पूर्ण

/*
 * This must be called only on pages that have
 * been verअगरied to be in the swap cache and locked.
 * It will never put the page पूर्णांकo the मुक्त list,
 * the caller has a reference on the page.
 */
व्योम delete_from_swap_cache(काष्ठा page *page)
अणु
	swp_entry_t entry = अणु .val = page_निजी(page) पूर्ण;
	काष्ठा address_space *address_space = swap_address_space(entry);

	xa_lock_irq(&address_space->i_pages);
	__delete_from_swap_cache(page, entry, शून्य);
	xa_unlock_irq(&address_space->i_pages);

	put_swap_page(page, entry);
	page_ref_sub(page, thp_nr_pages(page));
पूर्ण

व्योम clear_shaकरोw_from_swap_cache(पूर्णांक type, अचिन्हित दीर्घ begin,
				अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ curr = begin;
	व्योम *old;

	क्रम (;;) अणु
		अचिन्हित दीर्घ nr_shaकरोws = 0;
		swp_entry_t entry = swp_entry(type, curr);
		काष्ठा address_space *address_space = swap_address_space(entry);
		XA_STATE(xas, &address_space->i_pages, curr);

		xa_lock_irq(&address_space->i_pages);
		xas_क्रम_each(&xas, old, end) अणु
			अगर (!xa_is_value(old))
				जारी;
			xas_store(&xas, शून्य);
			nr_shaकरोws++;
		पूर्ण
		xa_unlock_irq(&address_space->i_pages);

		/* search the next swapcache until we meet end */
		curr >>= SWAP_ADDRESS_SPACE_SHIFT;
		curr++;
		curr <<= SWAP_ADDRESS_SPACE_SHIFT;
		अगर (curr > end)
			अवरोध;
	पूर्ण
पूर्ण

/* 
 * If we are the only user, then try to मुक्त up the swap cache. 
 * 
 * Its ok to check क्रम PageSwapCache without the page lock
 * here because we are going to recheck again inside
 * try_to_मुक्त_swap() _with_ the lock.
 * 					- Marcelo
 */
अटल अंतरभूत व्योम मुक्त_swap_cache(काष्ठा page *page)
अणु
	अगर (PageSwapCache(page) && !page_mapped(page) && trylock_page(page)) अणु
		try_to_मुक्त_swap(page);
		unlock_page(page);
	पूर्ण
पूर्ण

/* 
 * Perक्रमm a मुक्त_page(), also मुक्तing any swap cache associated with
 * this page अगर it is the last user of the page.
 */
व्योम मुक्त_page_and_swap_cache(काष्ठा page *page)
अणु
	मुक्त_swap_cache(page);
	अगर (!is_huge_zero_page(page))
		put_page(page);
पूर्ण

/*
 * Passed an array of pages, drop them all from swapcache and then release
 * them.  They are हटाओd from the LRU and मुक्तd अगर this is their last use.
 */
व्योम मुक्त_pages_and_swap_cache(काष्ठा page **pages, पूर्णांक nr)
अणु
	काष्ठा page **pagep = pages;
	पूर्णांक i;

	lru_add_drain();
	क्रम (i = 0; i < nr; i++)
		मुक्त_swap_cache(pagep[i]);
	release_pages(pagep, nr);
पूर्ण

अटल अंतरभूत bool swap_use_vma_पढ़ोahead(व्योम)
अणु
	वापस READ_ONCE(enable_vma_पढ़ोahead) && !atomic_पढ़ो(&nr_rotate_swap);
पूर्ण

/*
 * Lookup a swap entry in the swap cache. A found page will be वापसed
 * unlocked and with its refcount incremented - we rely on the kernel
 * lock getting page table operations atomic even अगर we drop the page
 * lock beक्रमe वापसing.
 */
काष्ठा page *lookup_swap_cache(swp_entry_t entry, काष्ठा vm_area_काष्ठा *vma,
			       अचिन्हित दीर्घ addr)
अणु
	काष्ठा page *page;
	काष्ठा swap_info_काष्ठा *si;

	si = get_swap_device(entry);
	अगर (!si)
		वापस शून्य;
	page = find_get_page(swap_address_space(entry), swp_offset(entry));
	put_swap_device(si);

	INC_CACHE_INFO(find_total);
	अगर (page) अणु
		bool vma_ra = swap_use_vma_पढ़ोahead();
		bool पढ़ोahead;

		INC_CACHE_INFO(find_success);
		/*
		 * At the moment, we करोn't support PG_पढ़ोahead क्रम anon THP
		 * so let's bail out rather than confusing the पढ़ोahead stat.
		 */
		अगर (unlikely(PageTransCompound(page)))
			वापस page;

		पढ़ोahead = TestClearPageReadahead(page);
		अगर (vma && vma_ra) अणु
			अचिन्हित दीर्घ ra_val;
			पूर्णांक win, hits;

			ra_val = GET_SWAP_RA_VAL(vma);
			win = SWAP_RA_WIN(ra_val);
			hits = SWAP_RA_HITS(ra_val);
			अगर (पढ़ोahead)
				hits = min_t(पूर्णांक, hits + 1, SWAP_RA_HITS_MAX);
			atomic_दीर्घ_set(&vma->swap_पढ़ोahead_info,
					SWAP_RA_VAL(addr, win, hits));
		पूर्ण

		अगर (पढ़ोahead) अणु
			count_vm_event(SWAP_RA_HIT);
			अगर (!vma || !vma_ra)
				atomic_inc(&swapin_पढ़ोahead_hits);
		पूर्ण
	पूर्ण

	वापस page;
पूर्ण

/**
 * find_get_incore_page - Find and get a page from the page or swap caches.
 * @mapping: The address_space to search.
 * @index: The page cache index.
 *
 * This dअगरfers from find_get_page() in that it will also look क्रम the
 * page in the swap cache.
 *
 * Return: The found page or %शून्य.
 */
काष्ठा page *find_get_incore_page(काष्ठा address_space *mapping, pgoff_t index)
अणु
	swp_entry_t swp;
	काष्ठा swap_info_काष्ठा *si;
	काष्ठा page *page = pagecache_get_page(mapping, index,
						FGP_ENTRY | FGP_HEAD, 0);

	अगर (!page)
		वापस page;
	अगर (!xa_is_value(page))
		वापस find_subpage(page, index);
	अगर (!shmem_mapping(mapping))
		वापस शून्य;

	swp = radix_to_swp_entry(page);
	/* Prevent swapoff from happening to us */
	si = get_swap_device(swp);
	अगर (!si)
		वापस शून्य;
	page = find_get_page(swap_address_space(swp), swp_offset(swp));
	put_swap_device(si);
	वापस page;
पूर्ण

काष्ठा page *__पढ़ो_swap_cache_async(swp_entry_t entry, gfp_t gfp_mask,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			bool *new_page_allocated)
अणु
	काष्ठा swap_info_काष्ठा *si;
	काष्ठा page *page;
	व्योम *shaकरोw = शून्य;

	*new_page_allocated = false;

	क्रम (;;) अणु
		पूर्णांक err;
		/*
		 * First check the swap cache.  Since this is normally
		 * called after lookup_swap_cache() failed, re-calling
		 * that would confuse statistics.
		 */
		si = get_swap_device(entry);
		अगर (!si)
			वापस शून्य;
		page = find_get_page(swap_address_space(entry),
				     swp_offset(entry));
		put_swap_device(si);
		अगर (page)
			वापस page;

		/*
		 * Just skip पढ़ो ahead क्रम unused swap slot.
		 * During swap_off when swap_slot_cache is disabled,
		 * we have to handle the race between putting
		 * swap entry in swap cache and marking swap slot
		 * as SWAP_HAS_CACHE.  That's करोne in later part of code or
		 * अन्यथा swap_off will be पातed अगर we वापस शून्य.
		 */
		अगर (!__swp_swapcount(entry) && swap_slot_cache_enabled)
			वापस शून्य;

		/*
		 * Get a new page to पढ़ो पूर्णांकo from swap.  Allocate it now,
		 * beक्रमe marking swap_map SWAP_HAS_CACHE, when -EEXIST will
		 * cause any racers to loop around until we add it to cache.
		 */
		page = alloc_page_vma(gfp_mask, vma, addr);
		अगर (!page)
			वापस शून्य;

		/*
		 * Swap entry may have been मुक्तd since our caller observed it.
		 */
		err = swapcache_prepare(entry);
		अगर (!err)
			अवरोध;

		put_page(page);
		अगर (err != -EEXIST)
			वापस शून्य;

		/*
		 * We might race against __delete_from_swap_cache(), and
		 * stumble across a swap_map entry whose SWAP_HAS_CACHE
		 * has not yet been cleared.  Or race against another
		 * __पढ़ो_swap_cache_async(), which has set SWAP_HAS_CACHE
		 * in swap_map, but not yet added its page to swap cache.
		 */
		cond_resched();
	पूर्ण

	/*
	 * The swap entry is ours to swap in. Prepare the new page.
	 */

	__SetPageLocked(page);
	__SetPageSwapBacked(page);

	अगर (mem_cgroup_swapin_अक्षरge_page(page, शून्य, gfp_mask, entry))
		जाओ fail_unlock;

	/* May fail (-ENOMEM) अगर XArray node allocation failed. */
	अगर (add_to_swap_cache(page, entry, gfp_mask & GFP_RECLAIM_MASK, &shaकरोw))
		जाओ fail_unlock;

	mem_cgroup_swapin_unअक्षरge_swap(entry);

	अगर (shaकरोw)
		workingset_refault(page, shaकरोw);

	/* Caller will initiate पढ़ो पूर्णांकo locked page */
	lru_cache_add(page);
	*new_page_allocated = true;
	वापस page;

fail_unlock:
	put_swap_page(page, entry);
	unlock_page(page);
	put_page(page);
	वापस शून्य;
पूर्ण

/*
 * Locate a page of swap in physical memory, reserving swap cache space
 * and पढ़ोing the disk अगर it is not alपढ़ोy cached.
 * A failure वापस means that either the page allocation failed or that
 * the swap entry is no दीर्घer in use.
 */
काष्ठा page *पढ़ो_swap_cache_async(swp_entry_t entry, gfp_t gfp_mask,
		काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr, bool करो_poll)
अणु
	bool page_was_allocated;
	काष्ठा page *retpage = __पढ़ो_swap_cache_async(entry, gfp_mask,
			vma, addr, &page_was_allocated);

	अगर (page_was_allocated)
		swap_पढ़ोpage(retpage, करो_poll);

	वापस retpage;
पूर्ण

अटल अचिन्हित पूर्णांक __swapin_nr_pages(अचिन्हित दीर्घ prev_offset,
				      अचिन्हित दीर्घ offset,
				      पूर्णांक hits,
				      पूर्णांक max_pages,
				      पूर्णांक prev_win)
अणु
	अचिन्हित पूर्णांक pages, last_ra;

	/*
	 * This heuristic has been found to work well on both sequential and
	 * अक्रमom loads, swapping to hard disk or to SSD: please करोn't ask
	 * what the "+ 2" means, it just happens to work well, that's all.
	 */
	pages = hits + 2;
	अगर (pages == 2) अणु
		/*
		 * We can have no पढ़ोahead hits to judge by: but must not get
		 * stuck here क्रमever, so check क्रम an adjacent offset instead
		 * (and करोn't even bother to check whether swap type is same).
		 */
		अगर (offset != prev_offset + 1 && offset != prev_offset - 1)
			pages = 1;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक roundup = 4;
		जबतक (roundup < pages)
			roundup <<= 1;
		pages = roundup;
	पूर्ण

	अगर (pages > max_pages)
		pages = max_pages;

	/* Don't shrink पढ़ोahead too fast */
	last_ra = prev_win / 2;
	अगर (pages < last_ra)
		pages = last_ra;

	वापस pages;
पूर्ण

अटल अचिन्हित दीर्घ swapin_nr_pages(अचिन्हित दीर्घ offset)
अणु
	अटल अचिन्हित दीर्घ prev_offset;
	अचिन्हित पूर्णांक hits, pages, max_pages;
	अटल atomic_t last_पढ़ोahead_pages;

	max_pages = 1 << READ_ONCE(page_cluster);
	अगर (max_pages <= 1)
		वापस 1;

	hits = atomic_xchg(&swapin_पढ़ोahead_hits, 0);
	pages = __swapin_nr_pages(READ_ONCE(prev_offset), offset, hits,
				  max_pages,
				  atomic_पढ़ो(&last_पढ़ोahead_pages));
	अगर (!hits)
		WRITE_ONCE(prev_offset, offset);
	atomic_set(&last_पढ़ोahead_pages, pages);

	वापस pages;
पूर्ण

/**
 * swap_cluster_पढ़ोahead - swap in pages in hope we need them soon
 * @entry: swap entry of this memory
 * @gfp_mask: memory allocation flags
 * @vmf: fault inक्रमmation
 *
 * Returns the काष्ठा page क्रम entry and addr, after queueing swapin.
 *
 * Primitive swap पढ़ोahead code. We simply पढ़ो an aligned block of
 * (1 << page_cluster) entries in the swap area. This method is chosen
 * because it करोesn't cost us any seek समय.  We also make sure to queue
 * the 'original' request together with the पढ़ोahead ones...
 *
 * This has been extended to use the NUMA policies from the mm triggering
 * the पढ़ोahead.
 *
 * Caller must hold पढ़ो mmap_lock अगर vmf->vma is not शून्य.
 */
काष्ठा page *swap_cluster_पढ़ोahead(swp_entry_t entry, gfp_t gfp_mask,
				काष्ठा vm_fault *vmf)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ entry_offset = swp_offset(entry);
	अचिन्हित दीर्घ offset = entry_offset;
	अचिन्हित दीर्घ start_offset, end_offset;
	अचिन्हित दीर्घ mask;
	काष्ठा swap_info_काष्ठा *si = swp_swap_info(entry);
	काष्ठा blk_plug plug;
	bool करो_poll = true, page_allocated;
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	अचिन्हित दीर्घ addr = vmf->address;

	mask = swapin_nr_pages(offset) - 1;
	अगर (!mask)
		जाओ skip;

	/* Test swap type to make sure the dereference is safe */
	अगर (likely(si->flags & (SWP_BLKDEV | SWP_FS_OPS))) अणु
		काष्ठा inode *inode = si->swap_file->f_mapping->host;
		अगर (inode_पढ़ो_congested(inode))
			जाओ skip;
	पूर्ण

	करो_poll = false;
	/* Read a page_cluster sized and aligned cluster around offset. */
	start_offset = offset & ~mask;
	end_offset = offset | mask;
	अगर (!start_offset)	/* First page is swap header. */
		start_offset++;
	अगर (end_offset >= si->max)
		end_offset = si->max - 1;

	blk_start_plug(&plug);
	क्रम (offset = start_offset; offset <= end_offset ; offset++) अणु
		/* Ok, करो the async पढ़ो-ahead now */
		page = __पढ़ो_swap_cache_async(
			swp_entry(swp_type(entry), offset),
			gfp_mask, vma, addr, &page_allocated);
		अगर (!page)
			जारी;
		अगर (page_allocated) अणु
			swap_पढ़ोpage(page, false);
			अगर (offset != entry_offset) अणु
				SetPageReadahead(page);
				count_vm_event(SWAP_RA);
			पूर्ण
		पूर्ण
		put_page(page);
	पूर्ण
	blk_finish_plug(&plug);

	lru_add_drain();	/* Push any new pages onto the LRU now */
skip:
	वापस पढ़ो_swap_cache_async(entry, gfp_mask, vma, addr, करो_poll);
पूर्ण

पूर्णांक init_swap_address_space(अचिन्हित पूर्णांक type, अचिन्हित दीर्घ nr_pages)
अणु
	काष्ठा address_space *spaces, *space;
	अचिन्हित पूर्णांक i, nr;

	nr = DIV_ROUND_UP(nr_pages, SWAP_ADDRESS_SPACE_PAGES);
	spaces = kvसुस्मृति(nr, माप(काष्ठा address_space), GFP_KERNEL);
	अगर (!spaces)
		वापस -ENOMEM;
	क्रम (i = 0; i < nr; i++) अणु
		space = spaces + i;
		xa_init_flags(&space->i_pages, XA_FLAGS_LOCK_IRQ);
		atomic_set(&space->i_mmap_writable, 0);
		space->a_ops = &swap_aops;
		/* swap cache करोesn't use ग_लिखोback related tags */
		mapping_set_no_ग_लिखोback_tags(space);
	पूर्ण
	nr_swapper_spaces[type] = nr;
	swapper_spaces[type] = spaces;

	वापस 0;
पूर्ण

व्योम निकास_swap_address_space(अचिन्हित पूर्णांक type)
अणु
	kvमुक्त(swapper_spaces[type]);
	nr_swapper_spaces[type] = 0;
	swapper_spaces[type] = शून्य;
पूर्ण

अटल अंतरभूत व्योम swap_ra_clamp_pfn(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ faddr,
				     अचिन्हित दीर्घ lpfn,
				     अचिन्हित दीर्घ rpfn,
				     अचिन्हित दीर्घ *start,
				     अचिन्हित दीर्घ *end)
अणु
	*start = max3(lpfn, PFN_DOWN(vma->vm_start),
		      PFN_DOWN(faddr & PMD_MASK));
	*end = min3(rpfn, PFN_DOWN(vma->vm_end),
		    PFN_DOWN((faddr & PMD_MASK) + PMD_SIZE));
पूर्ण

अटल व्योम swap_ra_info(काष्ठा vm_fault *vmf,
			काष्ठा vma_swap_पढ़ोahead *ra_info)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	अचिन्हित दीर्घ ra_val;
	swp_entry_t entry;
	अचिन्हित दीर्घ faddr, pfn, fpfn;
	अचिन्हित दीर्घ start, end;
	pte_t *pte, *orig_pte;
	अचिन्हित पूर्णांक max_win, hits, prev_win, win, left;
#अगर_अघोषित CONFIG_64BIT
	pte_t *tpte;
#पूर्ण_अगर

	max_win = 1 << min_t(अचिन्हित पूर्णांक, READ_ONCE(page_cluster),
			     SWAP_RA_ORDER_CEILING);
	अगर (max_win == 1) अणु
		ra_info->win = 1;
		वापस;
	पूर्ण

	faddr = vmf->address;
	orig_pte = pte = pte_offset_map(vmf->pmd, faddr);
	entry = pte_to_swp_entry(*pte);
	अगर ((unlikely(non_swap_entry(entry)))) अणु
		pte_unmap(orig_pte);
		वापस;
	पूर्ण

	fpfn = PFN_DOWN(faddr);
	ra_val = GET_SWAP_RA_VAL(vma);
	pfn = PFN_DOWN(SWAP_RA_ADDR(ra_val));
	prev_win = SWAP_RA_WIN(ra_val);
	hits = SWAP_RA_HITS(ra_val);
	ra_info->win = win = __swapin_nr_pages(pfn, fpfn, hits,
					       max_win, prev_win);
	atomic_दीर्घ_set(&vma->swap_पढ़ोahead_info,
			SWAP_RA_VAL(faddr, win, 0));

	अगर (win == 1) अणु
		pte_unmap(orig_pte);
		वापस;
	पूर्ण

	/* Copy the PTEs because the page table may be unmapped */
	अगर (fpfn == pfn + 1)
		swap_ra_clamp_pfn(vma, faddr, fpfn, fpfn + win, &start, &end);
	अन्यथा अगर (pfn == fpfn + 1)
		swap_ra_clamp_pfn(vma, faddr, fpfn - win + 1, fpfn + 1,
				  &start, &end);
	अन्यथा अणु
		left = (win - 1) / 2;
		swap_ra_clamp_pfn(vma, faddr, fpfn - left, fpfn + win - left,
				  &start, &end);
	पूर्ण
	ra_info->nr_pte = end - start;
	ra_info->offset = fpfn - start;
	pte -= ra_info->offset;
#अगर_घोषित CONFIG_64BIT
	ra_info->ptes = pte;
#अन्यथा
	tpte = ra_info->ptes;
	क्रम (pfn = start; pfn != end; pfn++)
		*tpte++ = *pte++;
#पूर्ण_अगर
	pte_unmap(orig_pte);
पूर्ण

/**
 * swap_vma_पढ़ोahead - swap in pages in hope we need them soon
 * @fentry: swap entry of this memory
 * @gfp_mask: memory allocation flags
 * @vmf: fault inक्रमmation
 *
 * Returns the काष्ठा page क्रम entry and addr, after queueing swapin.
 *
 * Primitive swap पढ़ोahead code. We simply पढ़ो in a few pages whose
 * भव addresses are around the fault address in the same vma.
 *
 * Caller must hold पढ़ो mmap_lock अगर vmf->vma is not शून्य.
 *
 */
अटल काष्ठा page *swap_vma_पढ़ोahead(swp_entry_t fentry, gfp_t gfp_mask,
				       काष्ठा vm_fault *vmf)
अणु
	काष्ठा blk_plug plug;
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा page *page;
	pte_t *pte, pentry;
	swp_entry_t entry;
	अचिन्हित पूर्णांक i;
	bool page_allocated;
	काष्ठा vma_swap_पढ़ोahead ra_info = अणु
		.win = 1,
	पूर्ण;

	swap_ra_info(vmf, &ra_info);
	अगर (ra_info.win == 1)
		जाओ skip;

	blk_start_plug(&plug);
	क्रम (i = 0, pte = ra_info.ptes; i < ra_info.nr_pte;
	     i++, pte++) अणु
		pentry = *pte;
		अगर (pte_none(pentry))
			जारी;
		अगर (pte_present(pentry))
			जारी;
		entry = pte_to_swp_entry(pentry);
		अगर (unlikely(non_swap_entry(entry)))
			जारी;
		page = __पढ़ो_swap_cache_async(entry, gfp_mask, vma,
					       vmf->address, &page_allocated);
		अगर (!page)
			जारी;
		अगर (page_allocated) अणु
			swap_पढ़ोpage(page, false);
			अगर (i != ra_info.offset) अणु
				SetPageReadahead(page);
				count_vm_event(SWAP_RA);
			पूर्ण
		पूर्ण
		put_page(page);
	पूर्ण
	blk_finish_plug(&plug);
	lru_add_drain();
skip:
	वापस पढ़ो_swap_cache_async(fentry, gfp_mask, vma, vmf->address,
				     ra_info.win == 1);
पूर्ण

/**
 * swapin_पढ़ोahead - swap in pages in hope we need them soon
 * @entry: swap entry of this memory
 * @gfp_mask: memory allocation flags
 * @vmf: fault inक्रमmation
 *
 * Returns the काष्ठा page क्रम entry and addr, after queueing swapin.
 *
 * It's a मुख्य entry function क्रम swap पढ़ोahead. By the configuration,
 * it will पढ़ो ahead blocks by cluster-based(ie, physical disk based)
 * or vma-based(ie, भव address based on faulty address) पढ़ोahead.
 */
काष्ठा page *swapin_पढ़ोahead(swp_entry_t entry, gfp_t gfp_mask,
				काष्ठा vm_fault *vmf)
अणु
	वापस swap_use_vma_पढ़ोahead() ?
			swap_vma_पढ़ोahead(entry, gfp_mask, vmf) :
			swap_cluster_पढ़ोahead(entry, gfp_mask, vmf);
पूर्ण

#अगर_घोषित CONFIG_SYSFS
अटल sमाप_प्रकार vma_ra_enabled_show(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%s\n",
			  enable_vma_पढ़ोahead ? "true" : "false");
पूर्ण
अटल sमाप_प्रकार vma_ra_enabled_store(काष्ठा kobject *kobj,
				      काष्ठा kobj_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (!म_भेदन(buf, "true", 4) || !म_भेदन(buf, "1", 1))
		enable_vma_पढ़ोahead = true;
	अन्यथा अगर (!म_भेदन(buf, "false", 5) || !म_भेदन(buf, "0", 1))
		enable_vma_पढ़ोahead = false;
	अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण
अटल काष्ठा kobj_attribute vma_ra_enabled_attr =
	__ATTR(vma_ra_enabled, 0644, vma_ra_enabled_show,
	       vma_ra_enabled_store);

अटल काष्ठा attribute *swap_attrs[] = अणु
	&vma_ra_enabled_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group swap_attr_group = अणु
	.attrs = swap_attrs,
पूर्ण;

अटल पूर्णांक __init swap_init_sysfs(व्योम)
अणु
	पूर्णांक err;
	काष्ठा kobject *swap_kobj;

	swap_kobj = kobject_create_and_add("swap", mm_kobj);
	अगर (!swap_kobj) अणु
		pr_err("failed to create swap kobject\n");
		वापस -ENOMEM;
	पूर्ण
	err = sysfs_create_group(swap_kobj, &swap_attr_group);
	अगर (err) अणु
		pr_err("failed to register swap group\n");
		जाओ delete_obj;
	पूर्ण
	वापस 0;

delete_obj:
	kobject_put(swap_kobj);
	वापस err;
पूर्ण
subsys_initcall(swap_init_sysfs);
#पूर्ण_अगर
