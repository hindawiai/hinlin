<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/mm/mlock.c
 *
 *  (C) Copyright 1995 Linus Torvalds
 *  (C) Copyright 2002 Christoph Hellwig
 */

#समावेश <linux/capability.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/user.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/sched.h>
#समावेश <linux/export.h>
#समावेश <linux/rmap.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/mm_अंतरभूत.h>

#समावेश "internal.h"

bool can_करो_mlock(व्योम)
अणु
	अगर (rlimit(RLIMIT_MEMLOCK) != 0)
		वापस true;
	अगर (capable(CAP_IPC_LOCK))
		वापस true;
	वापस false;
पूर्ण
EXPORT_SYMBOL(can_करो_mlock);

/*
 * Mlocked pages are marked with PageMlocked() flag क्रम efficient testing
 * in vmscan and, possibly, the fault path; and to support semi-accurate
 * statistics.
 *
 * An mlocked page [PageMlocked(page)] is unevictable.  As such, it will
 * be placed on the LRU "unevictable" list, rather than the [in]active lists.
 * The unevictable list is an LRU sibling list to the [in]active lists.
 * PageUnevictable is set to indicate the unevictable state.
 *
 * When lazy mlocking via vmscan, it is important to ensure that the
 * vma's VM_LOCKED status is not concurrently being modअगरied, otherwise we
 * may have mlocked a page that is being munlocked. So lazy mlock must take
 * the mmap_lock क्रम पढ़ो, and verअगरy that the vma really is locked
 * (see mm/rmap.c).
 */

/*
 *  LRU accounting क्रम clear_page_mlock()
 */
व्योम clear_page_mlock(काष्ठा page *page)
अणु
	पूर्णांक nr_pages;

	अगर (!TestClearPageMlocked(page))
		वापस;

	nr_pages = thp_nr_pages(page);
	mod_zone_page_state(page_zone(page), NR_MLOCK, -nr_pages);
	count_vm_events(UNEVICTABLE_PGCLEARED, nr_pages);
	/*
	 * The previous TestClearPageMlocked() corresponds to the smp_mb()
	 * in __pagevec_lru_add_fn().
	 *
	 * See __pagevec_lru_add_fn क्रम more explanation.
	 */
	अगर (!isolate_lru_page(page)) अणु
		putback_lru_page(page);
	पूर्ण अन्यथा अणु
		/*
		 * We lost the race. the page alपढ़ोy moved to evictable list.
		 */
		अगर (PageUnevictable(page))
			count_vm_events(UNEVICTABLE_PGSTRANDED, nr_pages);
	पूर्ण
पूर्ण

/*
 * Mark page as mlocked अगर not alपढ़ोy.
 * If page on LRU, isolate and putback to move to unevictable list.
 */
व्योम mlock_vma_page(काष्ठा page *page)
अणु
	/* Serialize with page migration */
	BUG_ON(!PageLocked(page));

	VM_BUG_ON_PAGE(PageTail(page), page);
	VM_BUG_ON_PAGE(PageCompound(page) && PageDoubleMap(page), page);

	अगर (!TestSetPageMlocked(page)) अणु
		पूर्णांक nr_pages = thp_nr_pages(page);

		mod_zone_page_state(page_zone(page), NR_MLOCK, nr_pages);
		count_vm_events(UNEVICTABLE_PGMLOCKED, nr_pages);
		अगर (!isolate_lru_page(page))
			putback_lru_page(page);
	पूर्ण
पूर्ण

/*
 * Finish munlock after successful page isolation
 *
 * Page must be locked. This is a wrapper क्रम try_to_munlock()
 * and putback_lru_page() with munlock accounting.
 */
अटल व्योम __munlock_isolated_page(काष्ठा page *page)
अणु
	/*
	 * Optimization: अगर the page was mapped just once, that's our mapping
	 * and we करोn't need to check all the other vmas.
	 */
	अगर (page_mapcount(page) > 1)
		try_to_munlock(page);

	/* Did try_to_unlock() succeed or punt? */
	अगर (!PageMlocked(page))
		count_vm_events(UNEVICTABLE_PGMUNLOCKED, thp_nr_pages(page));

	putback_lru_page(page);
पूर्ण

/*
 * Accounting क्रम page isolation fail during munlock
 *
 * Perक्रमms accounting when page isolation fails in munlock. There is nothing
 * अन्यथा to करो because it means some other task has alपढ़ोy हटाओd the page
 * from the LRU. putback_lru_page() will take care of removing the page from
 * the unevictable list, अगर necessary. vmscan [page_referenced()] will move
 * the page back to the unevictable list अगर some other vma has it mlocked.
 */
अटल व्योम __munlock_isolation_failed(काष्ठा page *page)
अणु
	पूर्णांक nr_pages = thp_nr_pages(page);

	अगर (PageUnevictable(page))
		__count_vm_events(UNEVICTABLE_PGSTRANDED, nr_pages);
	अन्यथा
		__count_vm_events(UNEVICTABLE_PGMUNLOCKED, nr_pages);
पूर्ण

/**
 * munlock_vma_page - munlock a vma page
 * @page: page to be unlocked, either a normal page or THP page head
 *
 * वापसs the size of the page as a page mask (0 क्रम normal page,
 *         HPAGE_PMD_NR - 1 क्रम THP head page)
 *
 * called from munlock()/munmap() path with page supposedly on the LRU.
 * When we munlock a page, because the vma where we found the page is being
 * munlock()ed or munmap()ed, we want to check whether other vmas hold the
 * page locked so that we can leave it on the unevictable lru list and not
 * bother vmscan with it.  However, to walk the page's rmap list in
 * try_to_munlock() we must isolate the page from the LRU.  If some other
 * task has हटाओd the page from the LRU, we won't be able to करो that.
 * So we clear the PageMlocked as we might not get another chance.  If we
 * can't isolate the page, we leave it क्रम putback_lru_page() and vmscan
 * [page_referenced()/try_to_unmap()] to deal with.
 */
अचिन्हित पूर्णांक munlock_vma_page(काष्ठा page *page)
अणु
	पूर्णांक nr_pages;

	/* For try_to_munlock() and to serialize with page migration */
	BUG_ON(!PageLocked(page));
	VM_BUG_ON_PAGE(PageTail(page), page);

	अगर (!TestClearPageMlocked(page)) अणु
		/* Potentially, PTE-mapped THP: करो not skip the rest PTEs */
		वापस 0;
	पूर्ण

	nr_pages = thp_nr_pages(page);
	mod_zone_page_state(page_zone(page), NR_MLOCK, -nr_pages);

	अगर (!isolate_lru_page(page))
		__munlock_isolated_page(page);
	अन्यथा
		__munlock_isolation_failed(page);

	वापस nr_pages - 1;
पूर्ण

/*
 * convert get_user_pages() वापस value to posix mlock() error
 */
अटल पूर्णांक __mlock_posix_error_वापस(दीर्घ retval)
अणु
	अगर (retval == -EFAULT)
		retval = -ENOMEM;
	अन्यथा अगर (retval == -ENOMEM)
		retval = -EAGAIN;
	वापस retval;
पूर्ण

/*
 * Prepare page क्रम fast batched LRU putback via putback_lru_evictable_pagevec()
 *
 * The fast path is available only क्रम evictable pages with single mapping.
 * Then we can bypass the per-cpu pvec and get better perक्रमmance.
 * when mapcount > 1 we need try_to_munlock() which can fail.
 * when !page_evictable(), we need the full reकरो logic of putback_lru_page to
 * aव्योम leaving evictable page in unevictable list.
 *
 * In हाल of success, @page is added to @pvec and @pgrescued is incremented
 * in हाल that the page was previously unevictable. @page is also unlocked.
 */
अटल bool __putback_lru_fast_prepare(काष्ठा page *page, काष्ठा pagevec *pvec,
		पूर्णांक *pgrescued)
अणु
	VM_BUG_ON_PAGE(PageLRU(page), page);
	VM_BUG_ON_PAGE(!PageLocked(page), page);

	अगर (page_mapcount(page) <= 1 && page_evictable(page)) अणु
		pagevec_add(pvec, page);
		अगर (TestClearPageUnevictable(page))
			(*pgrescued)++;
		unlock_page(page);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Putback multiple evictable pages to the LRU
 *
 * Batched putback of evictable pages that bypasses the per-cpu pvec. Some of
 * the pages might have meanजबतक become unevictable but that is OK.
 */
अटल व्योम __putback_lru_fast(काष्ठा pagevec *pvec, पूर्णांक pgrescued)
अणु
	count_vm_events(UNEVICTABLE_PGMUNLOCKED, pagevec_count(pvec));
	/*
	 *__pagevec_lru_add() calls release_pages() so we करोn't call
	 * put_page() explicitly
	 */
	__pagevec_lru_add(pvec);
	count_vm_events(UNEVICTABLE_PGRESCUED, pgrescued);
पूर्ण

/*
 * Munlock a batch of pages from the same zone
 *
 * The work is split to two मुख्य phases. First phase clears the Mlocked flag
 * and attempts to isolate the pages, all under a single zone lru lock.
 * The second phase finishes the munlock only क्रम pages where isolation
 * succeeded.
 *
 * Note that the pagevec may be modअगरied during the process.
 */
अटल व्योम __munlock_pagevec(काष्ठा pagevec *pvec, काष्ठा zone *zone)
अणु
	पूर्णांक i;
	पूर्णांक nr = pagevec_count(pvec);
	पूर्णांक delta_munlocked = -nr;
	काष्ठा pagevec pvec_putback;
	काष्ठा lruvec *lruvec = शून्य;
	पूर्णांक pgrescued = 0;

	pagevec_init(&pvec_putback);

	/* Phase 1: page isolation */
	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा page *page = pvec->pages[i];

		अगर (TestClearPageMlocked(page)) अणु
			/*
			 * We alपढ़ोy have pin from follow_page_mask()
			 * so we can spare the get_page() here.
			 */
			अगर (TestClearPageLRU(page)) अणु
				lruvec = relock_page_lruvec_irq(page, lruvec);
				del_page_from_lru_list(page, lruvec);
				जारी;
			पूर्ण अन्यथा
				__munlock_isolation_failed(page);
		पूर्ण अन्यथा अणु
			delta_munlocked++;
		पूर्ण

		/*
		 * We won't be munlocking this page in the next phase
		 * but we still need to release the follow_page_mask()
		 * pin. We cannot करो it under lru_lock however. If it's
		 * the last pin, __page_cache_release() would deadlock.
		 */
		pagevec_add(&pvec_putback, pvec->pages[i]);
		pvec->pages[i] = शून्य;
	पूर्ण
	अगर (lruvec) अणु
		__mod_zone_page_state(zone, NR_MLOCK, delta_munlocked);
		unlock_page_lruvec_irq(lruvec);
	पूर्ण अन्यथा अगर (delta_munlocked) अणु
		mod_zone_page_state(zone, NR_MLOCK, delta_munlocked);
	पूर्ण

	/* Now we can release pins of pages that we are not munlocking */
	pagevec_release(&pvec_putback);

	/* Phase 2: page munlock */
	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा page *page = pvec->pages[i];

		अगर (page) अणु
			lock_page(page);
			अगर (!__putback_lru_fast_prepare(page, &pvec_putback,
					&pgrescued)) अणु
				/*
				 * Slow path. We करोn't want to lose the last
				 * pin beक्रमe unlock_page()
				 */
				get_page(page); /* क्रम putback_lru_page() */
				__munlock_isolated_page(page);
				unlock_page(page);
				put_page(page); /* from follow_page_mask() */
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Phase 3: page putback क्रम pages that qualअगरied क्रम the fast path
	 * This will also call put_page() to वापस pin from follow_page_mask()
	 */
	अगर (pagevec_count(&pvec_putback))
		__putback_lru_fast(&pvec_putback, pgrescued);
पूर्ण

/*
 * Fill up pagevec क्रम __munlock_pagevec using pte walk
 *
 * The function expects that the काष्ठा page corresponding to @start address is
 * a non-TPH page alपढ़ोy pinned and in the @pvec, and that it beदीर्घs to @zone.
 *
 * The rest of @pvec is filled by subsequent pages within the same pmd and same
 * zone, as दीर्घ as the pte's are present and vm_normal_page() succeeds. These
 * pages also get pinned.
 *
 * Returns the address of the next page that should be scanned. This equals
 * @start + PAGE_SIZE when no page could be added by the pte walk.
 */
अटल अचिन्हित दीर्घ __munlock_pagevec_fill(काष्ठा pagevec *pvec,
			काष्ठा vm_area_काष्ठा *vma, काष्ठा zone *zone,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	pte_t *pte;
	spinlock_t *ptl;

	/*
	 * Initialize pte walk starting at the alपढ़ोy pinned page where we
	 * are sure that there is a pte, as it was pinned under the same
	 * mmap_lock ग_लिखो op.
	 */
	pte = get_locked_pte(vma->vm_mm, start,	&ptl);
	/* Make sure we करो not cross the page table boundary */
	end = pgd_addr_end(start, end);
	end = p4d_addr_end(start, end);
	end = pud_addr_end(start, end);
	end = pmd_addr_end(start, end);

	/* The page next to the pinned page is the first we will try to get */
	start += PAGE_SIZE;
	जबतक (start < end) अणु
		काष्ठा page *page = शून्य;
		pte++;
		अगर (pte_present(*pte))
			page = vm_normal_page(vma, start, *pte);
		/*
		 * Break अगर page could not be obtained or the page's node+zone करोes not
		 * match
		 */
		अगर (!page || page_zone(page) != zone)
			अवरोध;

		/*
		 * Do not use pagevec क्रम PTE-mapped THP,
		 * munlock_vma_pages_range() will handle them.
		 */
		अगर (PageTransCompound(page))
			अवरोध;

		get_page(page);
		/*
		 * Increase the address that will be वापसed *beक्रमe* the
		 * eventual अवरोध due to pvec becoming full by adding the page
		 */
		start += PAGE_SIZE;
		अगर (pagevec_add(pvec, page) == 0)
			अवरोध;
	पूर्ण
	pte_unmap_unlock(pte, ptl);
	वापस start;
पूर्ण

/*
 * munlock_vma_pages_range() - munlock all pages in the vma range.'
 * @vma - vma containing range to be munlock()ed.
 * @start - start address in @vma of the range
 * @end - end of range in @vma.
 *
 *  For mremap(), munmap() and निकास().
 *
 * Called with @vma VM_LOCKED.
 *
 * Returns with VM_LOCKED cleared.  Callers must be prepared to
 * deal with this.
 *
 * We करोn't save and restore VM_LOCKED here because pages are
 * still on lru.  In unmap path, pages might be scanned by reclaim
 * and re-mlocked by try_to_अणुmunlock|unmapपूर्ण beक्रमe we unmap and
 * मुक्त them.  This will result in मुक्तing mlocked pages.
 */
व्योम munlock_vma_pages_range(काष्ठा vm_area_काष्ठा *vma,
			     अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	vma->vm_flags &= VM_LOCKED_CLEAR_MASK;

	जबतक (start < end) अणु
		काष्ठा page *page;
		अचिन्हित पूर्णांक page_mask = 0;
		अचिन्हित दीर्घ page_increm;
		काष्ठा pagevec pvec;
		काष्ठा zone *zone;

		pagevec_init(&pvec);
		/*
		 * Although FOLL_DUMP is पूर्णांकended क्रम get_dump_page(),
		 * it just so happens that its special treaपंचांगent of the
		 * ZERO_PAGE (वापसing an error instead of करोing get_page)
		 * suits munlock very well (and अगर somehow an abnormal page
		 * has sneaked पूर्णांकo the range, we won't oops here: great).
		 */
		page = follow_page(vma, start, FOLL_GET | FOLL_DUMP);

		अगर (page && !IS_ERR(page)) अणु
			अगर (PageTransTail(page)) अणु
				VM_BUG_ON_PAGE(PageMlocked(page), page);
				put_page(page); /* follow_page_mask() */
			पूर्ण अन्यथा अगर (PageTransHuge(page)) अणु
				lock_page(page);
				/*
				 * Any THP page found by follow_page_mask() may
				 * have gotten split beक्रमe reaching
				 * munlock_vma_page(), so we need to compute
				 * the page_mask here instead.
				 */
				page_mask = munlock_vma_page(page);
				unlock_page(page);
				put_page(page); /* follow_page_mask() */
			पूर्ण अन्यथा अणु
				/*
				 * Non-huge pages are handled in batches via
				 * pagevec. The pin from follow_page_mask()
				 * prevents them from collapsing by THP.
				 */
				pagevec_add(&pvec, page);
				zone = page_zone(page);

				/*
				 * Try to fill the rest of pagevec using fast
				 * pte walk. This will also update start to
				 * the next page to process. Then munlock the
				 * pagevec.
				 */
				start = __munlock_pagevec_fill(&pvec, vma,
						zone, start, end);
				__munlock_pagevec(&pvec, zone);
				जाओ next;
			पूर्ण
		पूर्ण
		page_increm = 1 + page_mask;
		start += page_increm * PAGE_SIZE;
next:
		cond_resched();
	पूर्ण
पूर्ण

/*
 * mlock_fixup  - handle mlock[all]/munlock[all] requests.
 *
 * Filters out "special" vmas -- VM_LOCKED never माला_लो set क्रम these, and
 * munlock is a no-op.  However, क्रम some special vmas, we go ahead and
 * populate the ptes.
 *
 * For vmas that pass the filters, merge/split as appropriate.
 */
अटल पूर्णांक mlock_fixup(काष्ठा vm_area_काष्ठा *vma, काष्ठा vm_area_काष्ठा **prev,
	अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, vm_flags_t newflags)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	pgoff_t pgoff;
	पूर्णांक nr_pages;
	पूर्णांक ret = 0;
	पूर्णांक lock = !!(newflags & VM_LOCKED);
	vm_flags_t old_flags = vma->vm_flags;

	अगर (newflags == vma->vm_flags || (vma->vm_flags & VM_SPECIAL) ||
	    is_vm_hugetlb_page(vma) || vma == get_gate_vma(current->mm) ||
	    vma_is_dax(vma))
		/* करोn't set VM_LOCKED or VM_LOCKONFAULT and don't count */
		जाओ out;

	pgoff = vma->vm_pgoff + ((start - vma->vm_start) >> PAGE_SHIFT);
	*prev = vma_merge(mm, *prev, start, end, newflags, vma->anon_vma,
			  vma->vm_file, pgoff, vma_policy(vma),
			  vma->vm_userfaultfd_ctx);
	अगर (*prev) अणु
		vma = *prev;
		जाओ success;
	पूर्ण

	अगर (start != vma->vm_start) अणु
		ret = split_vma(mm, vma, start, 1);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (end != vma->vm_end) अणु
		ret = split_vma(mm, vma, end, 0);
		अगर (ret)
			जाओ out;
	पूर्ण

success:
	/*
	 * Keep track of amount of locked VM.
	 */
	nr_pages = (end - start) >> PAGE_SHIFT;
	अगर (!lock)
		nr_pages = -nr_pages;
	अन्यथा अगर (old_flags & VM_LOCKED)
		nr_pages = 0;
	mm->locked_vm += nr_pages;

	/*
	 * vm_flags is रक्षित by the mmap_lock held in ग_लिखो mode.
	 * It's okay अगर try_to_unmap_one unmaps a page just after we
	 * set VM_LOCKED, populate_vma_page_range will bring it back.
	 */

	अगर (lock)
		vma->vm_flags = newflags;
	अन्यथा
		munlock_vma_pages_range(vma, start, end);

out:
	*prev = vma;
	वापस ret;
पूर्ण

अटल पूर्णांक apply_vma_lock_flags(अचिन्हित दीर्घ start, माप_प्रकार len,
				vm_flags_t flags)
अणु
	अचिन्हित दीर्घ nstart, end, पंचांगp;
	काष्ठा vm_area_काष्ठा *vma, *prev;
	पूर्णांक error;

	VM_BUG_ON(offset_in_page(start));
	VM_BUG_ON(len != PAGE_ALIGN(len));
	end = start + len;
	अगर (end < start)
		वापस -EINVAL;
	अगर (end == start)
		वापस 0;
	vma = find_vma(current->mm, start);
	अगर (!vma || vma->vm_start > start)
		वापस -ENOMEM;

	prev = vma->vm_prev;
	अगर (start > vma->vm_start)
		prev = vma;

	क्रम (nstart = start ; ; ) अणु
		vm_flags_t newflags = vma->vm_flags & VM_LOCKED_CLEAR_MASK;

		newflags |= flags;

		/* Here we know that  vma->vm_start <= nstart < vma->vm_end. */
		पंचांगp = vma->vm_end;
		अगर (पंचांगp > end)
			पंचांगp = end;
		error = mlock_fixup(vma, &prev, nstart, पंचांगp, newflags);
		अगर (error)
			अवरोध;
		nstart = पंचांगp;
		अगर (nstart < prev->vm_end)
			nstart = prev->vm_end;
		अगर (nstart >= end)
			अवरोध;

		vma = prev->vm_next;
		अगर (!vma || vma->vm_start != nstart) अणु
			error = -ENOMEM;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस error;
पूर्ण

/*
 * Go through vma areas and sum size of mlocked
 * vma pages, as वापस value.
 * Note deferred memory locking हाल(mlock2(,,MLOCK_ONFAULT)
 * is also counted.
 * Return value: previously mlocked page counts
 */
अटल अचिन्हित दीर्घ count_mm_mlocked_page_nr(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ start, माप_प्रकार len)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ count = 0;

	अगर (mm == शून्य)
		mm = current->mm;

	vma = find_vma(mm, start);
	अगर (vma == शून्य)
		वापस 0;

	क्रम (; vma ; vma = vma->vm_next) अणु
		अगर (start >= vma->vm_end)
			जारी;
		अगर (start + len <=  vma->vm_start)
			अवरोध;
		अगर (vma->vm_flags & VM_LOCKED) अणु
			अगर (start > vma->vm_start)
				count -= (start - vma->vm_start);
			अगर (start + len < vma->vm_end) अणु
				count += start + len - vma->vm_start;
				अवरोध;
			पूर्ण
			count += vma->vm_end - vma->vm_start;
		पूर्ण
	पूर्ण

	वापस count >> PAGE_SHIFT;
पूर्ण

अटल __must_check पूर्णांक करो_mlock(अचिन्हित दीर्घ start, माप_प्रकार len, vm_flags_t flags)
अणु
	अचिन्हित दीर्घ locked;
	अचिन्हित दीर्घ lock_limit;
	पूर्णांक error = -ENOMEM;

	start = untagged_addr(start);

	अगर (!can_करो_mlock())
		वापस -EPERM;

	len = PAGE_ALIGN(len + (offset_in_page(start)));
	start &= PAGE_MASK;

	lock_limit = rlimit(RLIMIT_MEMLOCK);
	lock_limit >>= PAGE_SHIFT;
	locked = len >> PAGE_SHIFT;

	अगर (mmap_ग_लिखो_lock_समाप्तable(current->mm))
		वापस -EINTR;

	locked += current->mm->locked_vm;
	अगर ((locked > lock_limit) && (!capable(CAP_IPC_LOCK))) अणु
		/*
		 * It is possible that the regions requested पूर्णांकersect with
		 * previously mlocked areas, that part area in "mm->locked_vm"
		 * should not be counted to new mlock increment count. So check
		 * and adjust locked count अगर necessary.
		 */
		locked -= count_mm_mlocked_page_nr(current->mm,
				start, len);
	पूर्ण

	/* check against resource limits */
	अगर ((locked <= lock_limit) || capable(CAP_IPC_LOCK))
		error = apply_vma_lock_flags(start, len, flags);

	mmap_ग_लिखो_unlock(current->mm);
	अगर (error)
		वापस error;

	error = __mm_populate(start, len, 0);
	अगर (error)
		वापस __mlock_posix_error_वापस(error);
	वापस 0;
पूर्ण

SYSCALL_DEFINE2(mlock, अचिन्हित दीर्घ, start, माप_प्रकार, len)
अणु
	वापस करो_mlock(start, len, VM_LOCKED);
पूर्ण

SYSCALL_DEFINE3(mlock2, अचिन्हित दीर्घ, start, माप_प्रकार, len, पूर्णांक, flags)
अणु
	vm_flags_t vm_flags = VM_LOCKED;

	अगर (flags & ~MLOCK_ONFAULT)
		वापस -EINVAL;

	अगर (flags & MLOCK_ONFAULT)
		vm_flags |= VM_LOCKONFAULT;

	वापस करो_mlock(start, len, vm_flags);
पूर्ण

SYSCALL_DEFINE2(munlock, अचिन्हित दीर्घ, start, माप_प्रकार, len)
अणु
	पूर्णांक ret;

	start = untagged_addr(start);

	len = PAGE_ALIGN(len + (offset_in_page(start)));
	start &= PAGE_MASK;

	अगर (mmap_ग_लिखो_lock_समाप्तable(current->mm))
		वापस -EINTR;
	ret = apply_vma_lock_flags(start, len, 0);
	mmap_ग_लिखो_unlock(current->mm);

	वापस ret;
पूर्ण

/*
 * Take the MCL_* flags passed पूर्णांकo mlockall (or 0 अगर called from munlockall)
 * and translate पूर्णांकo the appropriate modअगरications to mm->def_flags and/or the
 * flags क्रम all current VMAs.
 *
 * There are a couple of subtleties with this.  If mlockall() is called multiple
 * बार with dअगरferent flags, the values करो not necessarily stack.  If mlockall
 * is called once including the MCL_FUTURE flag and then a second समय without
 * it, VM_LOCKED and VM_LOCKONFAULT will be cleared from mm->def_flags.
 */
अटल पूर्णांक apply_mlockall_flags(पूर्णांक flags)
अणु
	काष्ठा vm_area_काष्ठा *vma, *prev = शून्य;
	vm_flags_t to_add = 0;

	current->mm->def_flags &= VM_LOCKED_CLEAR_MASK;
	अगर (flags & MCL_FUTURE) अणु
		current->mm->def_flags |= VM_LOCKED;

		अगर (flags & MCL_ONFAULT)
			current->mm->def_flags |= VM_LOCKONFAULT;

		अगर (!(flags & MCL_CURRENT))
			जाओ out;
	पूर्ण

	अगर (flags & MCL_CURRENT) अणु
		to_add |= VM_LOCKED;
		अगर (flags & MCL_ONFAULT)
			to_add |= VM_LOCKONFAULT;
	पूर्ण

	क्रम (vma = current->mm->mmap; vma ; vma = prev->vm_next) अणु
		vm_flags_t newflags;

		newflags = vma->vm_flags & VM_LOCKED_CLEAR_MASK;
		newflags |= to_add;

		/* Ignore errors */
		mlock_fixup(vma, &prev, vma->vm_start, vma->vm_end, newflags);
		cond_resched();
	पूर्ण
out:
	वापस 0;
पूर्ण

SYSCALL_DEFINE1(mlockall, पूर्णांक, flags)
अणु
	अचिन्हित दीर्घ lock_limit;
	पूर्णांक ret;

	अगर (!flags || (flags & ~(MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT)) ||
	    flags == MCL_ONFAULT)
		वापस -EINVAL;

	अगर (!can_करो_mlock())
		वापस -EPERM;

	lock_limit = rlimit(RLIMIT_MEMLOCK);
	lock_limit >>= PAGE_SHIFT;

	अगर (mmap_ग_लिखो_lock_समाप्तable(current->mm))
		वापस -EINTR;

	ret = -ENOMEM;
	अगर (!(flags & MCL_CURRENT) || (current->mm->total_vm <= lock_limit) ||
	    capable(CAP_IPC_LOCK))
		ret = apply_mlockall_flags(flags);
	mmap_ग_लिखो_unlock(current->mm);
	अगर (!ret && (flags & MCL_CURRENT))
		mm_populate(0, TASK_SIZE);

	वापस ret;
पूर्ण

SYSCALL_DEFINE0(munlockall)
अणु
	पूर्णांक ret;

	अगर (mmap_ग_लिखो_lock_समाप्तable(current->mm))
		वापस -EINTR;
	ret = apply_mlockall_flags(0);
	mmap_ग_लिखो_unlock(current->mm);
	वापस ret;
पूर्ण

/*
 * Objects with dअगरferent lअगरeसमय than processes (SHM_LOCK and SHM_HUGETLB
 * shm segments) get accounted against the user_काष्ठा instead.
 */
अटल DEFINE_SPINLOCK(shmlock_user_lock);

पूर्णांक user_shm_lock(माप_प्रकार size, काष्ठा user_काष्ठा *user)
अणु
	अचिन्हित दीर्घ lock_limit, locked;
	पूर्णांक allowed = 0;

	locked = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	lock_limit = rlimit(RLIMIT_MEMLOCK);
	अगर (lock_limit == RLIM_अनन्त)
		allowed = 1;
	lock_limit >>= PAGE_SHIFT;
	spin_lock(&shmlock_user_lock);
	अगर (!allowed &&
	    locked + user->locked_shm > lock_limit && !capable(CAP_IPC_LOCK))
		जाओ out;
	get_uid(user);
	user->locked_shm += locked;
	allowed = 1;
out:
	spin_unlock(&shmlock_user_lock);
	वापस allowed;
पूर्ण

व्योम user_shm_unlock(माप_प्रकार size, काष्ठा user_काष्ठा *user)
अणु
	spin_lock(&shmlock_user_lock);
	user->locked_shm -= (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	spin_unlock(&shmlock_user_lock);
	मुक्त_uid(user);
पूर्ण
