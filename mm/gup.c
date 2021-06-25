<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/spinlock.h>

#समावेश <linux/mm.h>
#समावेश <linux/memremap.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/rmap.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/rwsem.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/migrate.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/sched/mm.h>

#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "internal.h"

काष्ठा follow_page_context अणु
	काष्ठा dev_pagemap *pgmap;
	अचिन्हित पूर्णांक page_mask;
पूर्ण;

अटल व्योम hpage_pincount_add(काष्ठा page *page, पूर्णांक refs)
अणु
	VM_BUG_ON_PAGE(!hpage_pincount_available(page), page);
	VM_BUG_ON_PAGE(page != compound_head(page), page);

	atomic_add(refs, compound_pincount_ptr(page));
पूर्ण

अटल व्योम hpage_pincount_sub(काष्ठा page *page, पूर्णांक refs)
अणु
	VM_BUG_ON_PAGE(!hpage_pincount_available(page), page);
	VM_BUG_ON_PAGE(page != compound_head(page), page);

	atomic_sub(refs, compound_pincount_ptr(page));
पूर्ण

/*
 * Return the compound head page with ref appropriately incremented,
 * or शून्य अगर that failed.
 */
अटल अंतरभूत काष्ठा page *try_get_compound_head(काष्ठा page *page, पूर्णांक refs)
अणु
	काष्ठा page *head = compound_head(page);

	अगर (WARN_ON_ONCE(page_ref_count(head) < 0))
		वापस शून्य;
	अगर (unlikely(!page_cache_add_speculative(head, refs)))
		वापस शून्य;
	वापस head;
पूर्ण

/*
 * try_grab_compound_head() - attempt to elevate a page's refcount, by a
 * flags-dependent amount.
 *
 * "grab" names in this file mean, "look at flags to decide whether to use
 * FOLL_PIN or FOLL_GET behavior, when incrementing the page's refcount.
 *
 * Either FOLL_PIN or FOLL_GET (or neither) must be set, but not both at the
 * same समय. (That's true throughout the get_user_pages*() and
 * pin_user_pages*() APIs.) Cases:
 *
 *    FOLL_GET: page's refcount will be incremented by 1.
 *    FOLL_PIN: page's refcount will be incremented by GUP_PIN_COUNTING_BIAS.
 *
 * Return: head page (with refcount appropriately incremented) क्रम success, or
 * शून्य upon failure. If neither FOLL_GET nor FOLL_PIN was set, that's
 * considered failure, and furthermore, a likely bug in the caller, so a warning
 * is also emitted.
 */
__maybe_unused काष्ठा page *try_grab_compound_head(काष्ठा page *page,
						   पूर्णांक refs, अचिन्हित पूर्णांक flags)
अणु
	अगर (flags & FOLL_GET)
		वापस try_get_compound_head(page, refs);
	अन्यथा अगर (flags & FOLL_PIN) अणु
		पूर्णांक orig_refs = refs;

		/*
		 * Can't करो FOLL_LONGTERM + FOLL_PIN gup fast path अगर not in a
		 * right zone, so fail and let the caller fall back to the slow
		 * path.
		 */
		अगर (unlikely((flags & FOLL_LONGTERM) &&
			     !is_pinnable_page(page)))
			वापस शून्य;

		/*
		 * When pinning a compound page of order > 1 (which is what
		 * hpage_pincount_available() checks क्रम), use an exact count to
		 * track it, via hpage_pincount_add/_sub().
		 *
		 * However, be sure to *also* increment the normal page refcount
		 * field at least once, so that the page really is pinned.
		 */
		अगर (!hpage_pincount_available(page))
			refs *= GUP_PIN_COUNTING_BIAS;

		page = try_get_compound_head(page, refs);
		अगर (!page)
			वापस शून्य;

		अगर (hpage_pincount_available(page))
			hpage_pincount_add(page, refs);

		mod_node_page_state(page_pgdat(page), NR_FOLL_PIN_ACQUIRED,
				    orig_refs);

		वापस page;
	पूर्ण

	WARN_ON_ONCE(1);
	वापस शून्य;
पूर्ण

अटल व्योम put_compound_head(काष्ठा page *page, पूर्णांक refs, अचिन्हित पूर्णांक flags)
अणु
	अगर (flags & FOLL_PIN) अणु
		mod_node_page_state(page_pgdat(page), NR_FOLL_PIN_RELEASED,
				    refs);

		अगर (hpage_pincount_available(page))
			hpage_pincount_sub(page, refs);
		अन्यथा
			refs *= GUP_PIN_COUNTING_BIAS;
	पूर्ण

	VM_BUG_ON_PAGE(page_ref_count(page) < refs, page);
	/*
	 * Calling put_page() क्रम each ref is unnecessarily slow. Only the last
	 * ref needs a put_page().
	 */
	अगर (refs > 1)
		page_ref_sub(page, refs - 1);
	put_page(page);
पूर्ण

/**
 * try_grab_page() - elevate a page's refcount by a flag-dependent amount
 *
 * This might not करो anything at all, depending on the flags argument.
 *
 * "grab" names in this file mean, "look at flags to decide whether to use
 * FOLL_PIN or FOLL_GET behavior, when incrementing the page's refcount.
 *
 * @page:    poपूर्णांकer to page to be grabbed
 * @flags:   gup flags: these are the FOLL_* flag values.
 *
 * Either FOLL_PIN or FOLL_GET (or neither) may be set, but not both at the same
 * समय. Cases:
 *
 *    FOLL_GET: page's refcount will be incremented by 1.
 *    FOLL_PIN: page's refcount will be incremented by GUP_PIN_COUNTING_BIAS.
 *
 * Return: true क्रम success, or अगर no action was required (अगर neither FOLL_PIN
 * nor FOLL_GET was set, nothing is करोne). False क्रम failure: FOLL_GET or
 * FOLL_PIN was set, but the page could not be grabbed.
 */
bool __must_check try_grab_page(काष्ठा page *page, अचिन्हित पूर्णांक flags)
अणु
	WARN_ON_ONCE((flags & (FOLL_GET | FOLL_PIN)) == (FOLL_GET | FOLL_PIN));

	अगर (flags & FOLL_GET)
		वापस try_get_page(page);
	अन्यथा अगर (flags & FOLL_PIN) अणु
		पूर्णांक refs = 1;

		page = compound_head(page);

		अगर (WARN_ON_ONCE(page_ref_count(page) <= 0))
			वापस false;

		अगर (hpage_pincount_available(page))
			hpage_pincount_add(page, 1);
		अन्यथा
			refs = GUP_PIN_COUNTING_BIAS;

		/*
		 * Similar to try_grab_compound_head(): even अगर using the
		 * hpage_pincount_add/_sub() routines, be sure to
		 * *also* increment the normal page refcount field at least
		 * once, so that the page really is pinned.
		 */
		page_ref_add(page, refs);

		mod_node_page_state(page_pgdat(page), NR_FOLL_PIN_ACQUIRED, 1);
	पूर्ण

	वापस true;
पूर्ण

/**
 * unpin_user_page() - release a dma-pinned page
 * @page:            poपूर्णांकer to page to be released
 *
 * Pages that were pinned via pin_user_pages*() must be released via either
 * unpin_user_page(), or one of the unpin_user_pages*() routines. This is so
 * that such pages can be separately tracked and uniquely handled. In
 * particular, पूर्णांकeractions with RDMA and fileप्रणालीs need special handling.
 */
व्योम unpin_user_page(काष्ठा page *page)
अणु
	put_compound_head(compound_head(page), 1, FOLL_PIN);
पूर्ण
EXPORT_SYMBOL(unpin_user_page);

अटल अंतरभूत व्योम compound_range_next(अचिन्हित दीर्घ i, अचिन्हित दीर्घ npages,
				       काष्ठा page **list, काष्ठा page **head,
				       अचिन्हित पूर्णांक *ntails)
अणु
	काष्ठा page *next, *page;
	अचिन्हित पूर्णांक nr = 1;

	अगर (i >= npages)
		वापस;

	next = *list + i;
	page = compound_head(next);
	अगर (PageCompound(page) && compound_order(page) >= 1)
		nr = min_t(अचिन्हित पूर्णांक,
			   page + compound_nr(page) - next, npages - i);

	*head = page;
	*ntails = nr;
पूर्ण

#घोषणा क्रम_each_compound_range(__i, __list, __npages, __head, __ntails) \
	क्रम (__i = 0, \
	     compound_range_next(__i, __npages, __list, &(__head), &(__ntails)); \
	     __i < __npages; __i += __ntails, \
	     compound_range_next(__i, __npages, __list, &(__head), &(__ntails)))

अटल अंतरभूत व्योम compound_next(अचिन्हित दीर्घ i, अचिन्हित दीर्घ npages,
				 काष्ठा page **list, काष्ठा page **head,
				 अचिन्हित पूर्णांक *ntails)
अणु
	काष्ठा page *page;
	अचिन्हित पूर्णांक nr;

	अगर (i >= npages)
		वापस;

	page = compound_head(list[i]);
	क्रम (nr = i + 1; nr < npages; nr++) अणु
		अगर (compound_head(list[nr]) != page)
			अवरोध;
	पूर्ण

	*head = page;
	*ntails = nr - i;
पूर्ण

#घोषणा क्रम_each_compound_head(__i, __list, __npages, __head, __ntails) \
	क्रम (__i = 0, \
	     compound_next(__i, __npages, __list, &(__head), &(__ntails)); \
	     __i < __npages; __i += __ntails, \
	     compound_next(__i, __npages, __list, &(__head), &(__ntails)))

/**
 * unpin_user_pages_dirty_lock() - release and optionally dirty gup-pinned pages
 * @pages:  array of pages to be maybe marked dirty, and definitely released.
 * @npages: number of pages in the @pages array.
 * @make_dirty: whether to mark the pages dirty
 *
 * "gup-pinned page" refers to a page that has had one of the get_user_pages()
 * variants called on that page.
 *
 * For each page in the @pages array, make that page (or its head page, अगर a
 * compound page) dirty, अगर @make_dirty is true, and अगर the page was previously
 * listed as clean. In any हाल, releases all pages using unpin_user_page(),
 * possibly via unpin_user_pages(), क्रम the non-dirty हाल.
 *
 * Please see the unpin_user_page() करोcumentation क्रम details.
 *
 * set_page_dirty_lock() is used पूर्णांकernally. If instead, set_page_dirty() is
 * required, then the caller should a) verअगरy that this is really correct,
 * because _lock() is usually required, and b) hand code it:
 * set_page_dirty_lock(), unpin_user_page().
 *
 */
व्योम unpin_user_pages_dirty_lock(काष्ठा page **pages, अचिन्हित दीर्घ npages,
				 bool make_dirty)
अणु
	अचिन्हित दीर्घ index;
	काष्ठा page *head;
	अचिन्हित पूर्णांक ntails;

	अगर (!make_dirty) अणु
		unpin_user_pages(pages, npages);
		वापस;
	पूर्ण

	क्रम_each_compound_head(index, pages, npages, head, ntails) अणु
		/*
		 * Checking PageDirty at this poपूर्णांक may race with
		 * clear_page_dirty_क्रम_io(), but that's OK. Two key
		 * हालs:
		 *
		 * 1) This code sees the page as alपढ़ोy dirty, so it
		 * skips the call to set_page_dirty(). That could happen
		 * because clear_page_dirty_क्रम_io() called
		 * page_mkclean(), followed by set_page_dirty().
		 * However, now the page is going to get written back,
		 * which meets the original पूर्णांकention of setting it
		 * dirty, so all is well: clear_page_dirty_क्रम_io() goes
		 * on to call TestClearPageDirty(), and ग_लिखो the page
		 * back.
		 *
		 * 2) This code sees the page as clean, so it calls
		 * set_page_dirty(). The page stays dirty, despite being
		 * written back, so it माला_लो written back again in the
		 * next ग_लिखोback cycle. This is harmless.
		 */
		अगर (!PageDirty(head))
			set_page_dirty_lock(head);
		put_compound_head(head, ntails, FOLL_PIN);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(unpin_user_pages_dirty_lock);

/**
 * unpin_user_page_range_dirty_lock() - release and optionally dirty
 * gup-pinned page range
 *
 * @page:  the starting page of a range maybe marked dirty, and definitely released.
 * @npages: number of consecutive pages to release.
 * @make_dirty: whether to mark the pages dirty
 *
 * "gup-pinned page range" refers to a range of pages that has had one of the
 * pin_user_pages() variants called on that page.
 *
 * For the page ranges defined by [page .. page+npages], make that range (or
 * its head pages, अगर a compound page) dirty, अगर @make_dirty is true, and अगर the
 * page range was previously listed as clean.
 *
 * set_page_dirty_lock() is used पूर्णांकernally. If instead, set_page_dirty() is
 * required, then the caller should a) verअगरy that this is really correct,
 * because _lock() is usually required, and b) hand code it:
 * set_page_dirty_lock(), unpin_user_page().
 *
 */
व्योम unpin_user_page_range_dirty_lock(काष्ठा page *page, अचिन्हित दीर्घ npages,
				      bool make_dirty)
अणु
	अचिन्हित दीर्घ index;
	काष्ठा page *head;
	अचिन्हित पूर्णांक ntails;

	क्रम_each_compound_range(index, &page, npages, head, ntails) अणु
		अगर (make_dirty && !PageDirty(head))
			set_page_dirty_lock(head);
		put_compound_head(head, ntails, FOLL_PIN);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(unpin_user_page_range_dirty_lock);

/**
 * unpin_user_pages() - release an array of gup-pinned pages.
 * @pages:  array of pages to be marked dirty and released.
 * @npages: number of pages in the @pages array.
 *
 * For each page in the @pages array, release the page using unpin_user_page().
 *
 * Please see the unpin_user_page() करोcumentation क्रम details.
 */
व्योम unpin_user_pages(काष्ठा page **pages, अचिन्हित दीर्घ npages)
अणु
	अचिन्हित दीर्घ index;
	काष्ठा page *head;
	अचिन्हित पूर्णांक ntails;

	/*
	 * If this WARN_ON() fires, then the प्रणाली *might* be leaking pages (by
	 * leaving them pinned), but probably not. More likely, gup/pup वापसed
	 * a hard -ERRNO error to the caller, who erroneously passed it here.
	 */
	अगर (WARN_ON(IS_ERR_VALUE(npages)))
		वापस;

	क्रम_each_compound_head(index, pages, npages, head, ntails)
		put_compound_head(head, ntails, FOLL_PIN);
पूर्ण
EXPORT_SYMBOL(unpin_user_pages);

#अगर_घोषित CONFIG_MMU
अटल काष्ठा page *no_page_table(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित पूर्णांक flags)
अणु
	/*
	 * When core dumping an enormous anonymous area that nobody
	 * has touched so far, we करोn't want to allocate unnecessary pages or
	 * page tables.  Return error instead of शून्य to skip handle_mm_fault,
	 * then get_dump_page() will वापस शून्य to leave a hole in the dump.
	 * But we can only make this optimization where a hole would surely
	 * be zero-filled अगर handle_mm_fault() actually did handle it.
	 */
	अगर ((flags & FOLL_DUMP) &&
			(vma_is_anonymous(vma) || !vma->vm_ops->fault))
		वापस ERR_PTR(-EFAULT);
	वापस शून्य;
पूर्ण

अटल पूर्णांक follow_pfn_pte(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		pte_t *pte, अचिन्हित पूर्णांक flags)
अणु
	/* No page to get reference */
	अगर (flags & FOLL_GET)
		वापस -EFAULT;

	अगर (flags & FOLL_TOUCH) अणु
		pte_t entry = *pte;

		अगर (flags & FOLL_WRITE)
			entry = pte_सूची_गढ़ोty(entry);
		entry = pte_mkyoung(entry);

		अगर (!pte_same(*pte, entry)) अणु
			set_pte_at(vma->vm_mm, address, pte, entry);
			update_mmu_cache(vma, address, pte);
		पूर्ण
	पूर्ण

	/* Proper page table entry exists, but no corresponding काष्ठा page */
	वापस -EEXIST;
पूर्ण

/*
 * FOLL_FORCE can ग_लिखो to even unwritable pte's, but only
 * after we've gone through a COW cycle and they are dirty.
 */
अटल अंतरभूत bool can_follow_ग_लिखो_pte(pte_t pte, अचिन्हित पूर्णांक flags)
अणु
	वापस pte_ग_लिखो(pte) ||
		((flags & FOLL_FORCE) && (flags & FOLL_COW) && pte_dirty(pte));
पूर्ण

अटल काष्ठा page *follow_page_pte(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ address, pmd_t *pmd, अचिन्हित पूर्णांक flags,
		काष्ठा dev_pagemap **pgmap)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा page *page;
	spinlock_t *ptl;
	pte_t *ptep, pte;
	पूर्णांक ret;

	/* FOLL_GET and FOLL_PIN are mutually exclusive. */
	अगर (WARN_ON_ONCE((flags & (FOLL_PIN | FOLL_GET)) ==
			 (FOLL_PIN | FOLL_GET)))
		वापस ERR_PTR(-EINVAL);
retry:
	अगर (unlikely(pmd_bad(*pmd)))
		वापस no_page_table(vma, flags);

	ptep = pte_offset_map_lock(mm, pmd, address, &ptl);
	pte = *ptep;
	अगर (!pte_present(pte)) अणु
		swp_entry_t entry;
		/*
		 * KSM's अवरोध_ksm() relies upon recognizing a ksm page
		 * even जबतक it is being migrated, so क्रम that हाल we
		 * need migration_entry_रुको().
		 */
		अगर (likely(!(flags & FOLL_MIGRATION)))
			जाओ no_page;
		अगर (pte_none(pte))
			जाओ no_page;
		entry = pte_to_swp_entry(pte);
		अगर (!is_migration_entry(entry))
			जाओ no_page;
		pte_unmap_unlock(ptep, ptl);
		migration_entry_रुको(mm, pmd, address);
		जाओ retry;
	पूर्ण
	अगर ((flags & FOLL_NUMA) && pte_protnone(pte))
		जाओ no_page;
	अगर ((flags & FOLL_WRITE) && !can_follow_ग_लिखो_pte(pte, flags)) अणु
		pte_unmap_unlock(ptep, ptl);
		वापस शून्य;
	पूर्ण

	page = vm_normal_page(vma, address, pte);
	अगर (!page && pte_devmap(pte) && (flags & (FOLL_GET | FOLL_PIN))) अणु
		/*
		 * Only वापस device mapping pages in the FOLL_GET or FOLL_PIN
		 * हाल since they are only valid जबतक holding the pgmap
		 * reference.
		 */
		*pgmap = get_dev_pagemap(pte_pfn(pte), *pgmap);
		अगर (*pgmap)
			page = pte_page(pte);
		अन्यथा
			जाओ no_page;
	पूर्ण अन्यथा अगर (unlikely(!page)) अणु
		अगर (flags & FOLL_DUMP) अणु
			/* Aव्योम special (like zero) pages in core dumps */
			page = ERR_PTR(-EFAULT);
			जाओ out;
		पूर्ण

		अगर (is_zero_pfn(pte_pfn(pte))) अणु
			page = pte_page(pte);
		पूर्ण अन्यथा अणु
			ret = follow_pfn_pte(vma, address, ptep, flags);
			page = ERR_PTR(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/* try_grab_page() करोes nothing unless FOLL_GET or FOLL_PIN is set. */
	अगर (unlikely(!try_grab_page(page, flags))) अणु
		page = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण
	/*
	 * We need to make the page accessible अगर and only अगर we are going
	 * to access its content (the FOLL_PIN हाल).  Please see
	 * Documentation/core-api/pin_user_pages.rst क्रम details.
	 */
	अगर (flags & FOLL_PIN) अणु
		ret = arch_make_page_accessible(page);
		अगर (ret) अणु
			unpin_user_page(page);
			page = ERR_PTR(ret);
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (flags & FOLL_TOUCH) अणु
		अगर ((flags & FOLL_WRITE) &&
		    !pte_dirty(pte) && !PageDirty(page))
			set_page_dirty(page);
		/*
		 * pte_mkyoung() would be more correct here, but atomic care
		 * is needed to aव्योम losing the dirty bit: it is easier to use
		 * mark_page_accessed().
		 */
		mark_page_accessed(page);
	पूर्ण
	अगर ((flags & FOLL_MLOCK) && (vma->vm_flags & VM_LOCKED)) अणु
		/* Do not mlock pte-mapped THP */
		अगर (PageTransCompound(page))
			जाओ out;

		/*
		 * The preliminary mapping check is मुख्यly to aव्योम the
		 * poपूर्णांकless overhead of lock_page on the ZERO_PAGE
		 * which might bounce very badly अगर there is contention.
		 *
		 * If the page is alपढ़ोy locked, we करोn't need to
		 * handle it now - vmscan will handle it later अगर and
		 * when it attempts to reclaim the page.
		 */
		अगर (page->mapping && trylock_page(page)) अणु
			lru_add_drain();  /* push cached pages to LRU */
			/*
			 * Because we lock page here, and migration is
			 * blocked by the pte's page reference, and we
			 * know the page is still mapped, we करोn't even
			 * need to check क्रम file-cache page truncation.
			 */
			mlock_vma_page(page);
			unlock_page(page);
		पूर्ण
	पूर्ण
out:
	pte_unmap_unlock(ptep, ptl);
	वापस page;
no_page:
	pte_unmap_unlock(ptep, ptl);
	अगर (!pte_none(pte))
		वापस शून्य;
	वापस no_page_table(vma, flags);
पूर्ण

अटल काष्ठा page *follow_pmd_mask(काष्ठा vm_area_काष्ठा *vma,
				    अचिन्हित दीर्घ address, pud_t *pudp,
				    अचिन्हित पूर्णांक flags,
				    काष्ठा follow_page_context *ctx)
अणु
	pmd_t *pmd, pmdval;
	spinlock_t *ptl;
	काष्ठा page *page;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	pmd = pmd_offset(pudp, address);
	/*
	 * The READ_ONCE() will stabilize the pmdval in a रेजिस्टर or
	 * on the stack so that it will stop changing under the code.
	 */
	pmdval = READ_ONCE(*pmd);
	अगर (pmd_none(pmdval))
		वापस no_page_table(vma, flags);
	अगर (pmd_huge(pmdval) && is_vm_hugetlb_page(vma)) अणु
		page = follow_huge_pmd(mm, address, pmd, flags);
		अगर (page)
			वापस page;
		वापस no_page_table(vma, flags);
	पूर्ण
	अगर (is_hugepd(__hugepd(pmd_val(pmdval)))) अणु
		page = follow_huge_pd(vma, address,
				      __hugepd(pmd_val(pmdval)), flags,
				      PMD_SHIFT);
		अगर (page)
			वापस page;
		वापस no_page_table(vma, flags);
	पूर्ण
retry:
	अगर (!pmd_present(pmdval)) अणु
		अगर (likely(!(flags & FOLL_MIGRATION)))
			वापस no_page_table(vma, flags);
		VM_BUG_ON(thp_migration_supported() &&
				  !is_pmd_migration_entry(pmdval));
		अगर (is_pmd_migration_entry(pmdval))
			pmd_migration_entry_रुको(mm, pmd);
		pmdval = READ_ONCE(*pmd);
		/*
		 * MADV_DONTNEED may convert the pmd to null because
		 * mmap_lock is held in पढ़ो mode
		 */
		अगर (pmd_none(pmdval))
			वापस no_page_table(vma, flags);
		जाओ retry;
	पूर्ण
	अगर (pmd_devmap(pmdval)) अणु
		ptl = pmd_lock(mm, pmd);
		page = follow_devmap_pmd(vma, address, pmd, flags, &ctx->pgmap);
		spin_unlock(ptl);
		अगर (page)
			वापस page;
	पूर्ण
	अगर (likely(!pmd_trans_huge(pmdval)))
		वापस follow_page_pte(vma, address, pmd, flags, &ctx->pgmap);

	अगर ((flags & FOLL_NUMA) && pmd_protnone(pmdval))
		वापस no_page_table(vma, flags);

retry_locked:
	ptl = pmd_lock(mm, pmd);
	अगर (unlikely(pmd_none(*pmd))) अणु
		spin_unlock(ptl);
		वापस no_page_table(vma, flags);
	पूर्ण
	अगर (unlikely(!pmd_present(*pmd))) अणु
		spin_unlock(ptl);
		अगर (likely(!(flags & FOLL_MIGRATION)))
			वापस no_page_table(vma, flags);
		pmd_migration_entry_रुको(mm, pmd);
		जाओ retry_locked;
	पूर्ण
	अगर (unlikely(!pmd_trans_huge(*pmd))) अणु
		spin_unlock(ptl);
		वापस follow_page_pte(vma, address, pmd, flags, &ctx->pgmap);
	पूर्ण
	अगर (flags & FOLL_SPLIT_PMD) अणु
		पूर्णांक ret;
		page = pmd_page(*pmd);
		अगर (is_huge_zero_page(page)) अणु
			spin_unlock(ptl);
			ret = 0;
			split_huge_pmd(vma, pmd, address);
			अगर (pmd_trans_unstable(pmd))
				ret = -EBUSY;
		पूर्ण अन्यथा अणु
			spin_unlock(ptl);
			split_huge_pmd(vma, pmd, address);
			ret = pte_alloc(mm, pmd) ? -ENOMEM : 0;
		पूर्ण

		वापस ret ? ERR_PTR(ret) :
			follow_page_pte(vma, address, pmd, flags, &ctx->pgmap);
	पूर्ण
	page = follow_trans_huge_pmd(vma, address, pmd, flags);
	spin_unlock(ptl);
	ctx->page_mask = HPAGE_PMD_NR - 1;
	वापस page;
पूर्ण

अटल काष्ठा page *follow_pud_mask(काष्ठा vm_area_काष्ठा *vma,
				    अचिन्हित दीर्घ address, p4d_t *p4dp,
				    अचिन्हित पूर्णांक flags,
				    काष्ठा follow_page_context *ctx)
अणु
	pud_t *pud;
	spinlock_t *ptl;
	काष्ठा page *page;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	pud = pud_offset(p4dp, address);
	अगर (pud_none(*pud))
		वापस no_page_table(vma, flags);
	अगर (pud_huge(*pud) && is_vm_hugetlb_page(vma)) अणु
		page = follow_huge_pud(mm, address, pud, flags);
		अगर (page)
			वापस page;
		वापस no_page_table(vma, flags);
	पूर्ण
	अगर (is_hugepd(__hugepd(pud_val(*pud)))) अणु
		page = follow_huge_pd(vma, address,
				      __hugepd(pud_val(*pud)), flags,
				      PUD_SHIFT);
		अगर (page)
			वापस page;
		वापस no_page_table(vma, flags);
	पूर्ण
	अगर (pud_devmap(*pud)) अणु
		ptl = pud_lock(mm, pud);
		page = follow_devmap_pud(vma, address, pud, flags, &ctx->pgmap);
		spin_unlock(ptl);
		अगर (page)
			वापस page;
	पूर्ण
	अगर (unlikely(pud_bad(*pud)))
		वापस no_page_table(vma, flags);

	वापस follow_pmd_mask(vma, address, pud, flags, ctx);
पूर्ण

अटल काष्ठा page *follow_p4d_mask(काष्ठा vm_area_काष्ठा *vma,
				    अचिन्हित दीर्घ address, pgd_t *pgdp,
				    अचिन्हित पूर्णांक flags,
				    काष्ठा follow_page_context *ctx)
अणु
	p4d_t *p4d;
	काष्ठा page *page;

	p4d = p4d_offset(pgdp, address);
	अगर (p4d_none(*p4d))
		वापस no_page_table(vma, flags);
	BUILD_BUG_ON(p4d_huge(*p4d));
	अगर (unlikely(p4d_bad(*p4d)))
		वापस no_page_table(vma, flags);

	अगर (is_hugepd(__hugepd(p4d_val(*p4d)))) अणु
		page = follow_huge_pd(vma, address,
				      __hugepd(p4d_val(*p4d)), flags,
				      P4D_SHIFT);
		अगर (page)
			वापस page;
		वापस no_page_table(vma, flags);
	पूर्ण
	वापस follow_pud_mask(vma, address, p4d, flags, ctx);
पूर्ण

/**
 * follow_page_mask - look up a page descriptor from a user-भव address
 * @vma: vm_area_काष्ठा mapping @address
 * @address: भव address to look up
 * @flags: flags modअगरying lookup behaviour
 * @ctx: contains dev_pagemap क्रम %ZONE_DEVICE memory pinning and a
 *       poपूर्णांकer to output page_mask
 *
 * @flags can have FOLL_ flags set, defined in <linux/mm.h>
 *
 * When getting pages from ZONE_DEVICE memory, the @ctx->pgmap caches
 * the device's dev_pagemap metadata to aव्योम repeating expensive lookups.
 *
 * On output, the @ctx->page_mask is set according to the size of the page.
 *
 * Return: the mapped (काष्ठा page *), %शून्य अगर no mapping exists, or
 * an error poपूर्णांकer अगर there is a mapping to something not represented
 * by a page descriptor (see also vm_normal_page()).
 */
अटल काष्ठा page *follow_page_mask(काष्ठा vm_area_काष्ठा *vma,
			      अचिन्हित दीर्घ address, अचिन्हित पूर्णांक flags,
			      काष्ठा follow_page_context *ctx)
अणु
	pgd_t *pgd;
	काष्ठा page *page;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	ctx->page_mask = 0;

	/* make this handle hugepd */
	page = follow_huge_addr(mm, address, flags & FOLL_WRITE);
	अगर (!IS_ERR(page)) अणु
		WARN_ON_ONCE(flags & (FOLL_GET | FOLL_PIN));
		वापस page;
	पूर्ण

	pgd = pgd_offset(mm, address);

	अगर (pgd_none(*pgd) || unlikely(pgd_bad(*pgd)))
		वापस no_page_table(vma, flags);

	अगर (pgd_huge(*pgd)) अणु
		page = follow_huge_pgd(mm, address, pgd, flags);
		अगर (page)
			वापस page;
		वापस no_page_table(vma, flags);
	पूर्ण
	अगर (is_hugepd(__hugepd(pgd_val(*pgd)))) अणु
		page = follow_huge_pd(vma, address,
				      __hugepd(pgd_val(*pgd)), flags,
				      PGसूची_SHIFT);
		अगर (page)
			वापस page;
		वापस no_page_table(vma, flags);
	पूर्ण

	वापस follow_p4d_mask(vma, address, pgd, flags, ctx);
पूर्ण

काष्ठा page *follow_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			 अचिन्हित पूर्णांक foll_flags)
अणु
	काष्ठा follow_page_context ctx = अणु शून्य पूर्ण;
	काष्ठा page *page;

	page = follow_page_mask(vma, address, foll_flags, &ctx);
	अगर (ctx.pgmap)
		put_dev_pagemap(ctx.pgmap);
	वापस page;
पूर्ण

अटल पूर्णांक get_gate_page(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
		अचिन्हित पूर्णांक gup_flags, काष्ठा vm_area_काष्ठा **vma,
		काष्ठा page **page)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	पूर्णांक ret = -EFAULT;

	/* user gate pages are पढ़ो-only */
	अगर (gup_flags & FOLL_WRITE)
		वापस -EFAULT;
	अगर (address > TASK_SIZE)
		pgd = pgd_offset_k(address);
	अन्यथा
		pgd = pgd_offset_gate(mm, address);
	अगर (pgd_none(*pgd))
		वापस -EFAULT;
	p4d = p4d_offset(pgd, address);
	अगर (p4d_none(*p4d))
		वापस -EFAULT;
	pud = pud_offset(p4d, address);
	अगर (pud_none(*pud))
		वापस -EFAULT;
	pmd = pmd_offset(pud, address);
	अगर (!pmd_present(*pmd))
		वापस -EFAULT;
	VM_BUG_ON(pmd_trans_huge(*pmd));
	pte = pte_offset_map(pmd, address);
	अगर (pte_none(*pte))
		जाओ unmap;
	*vma = get_gate_vma(mm);
	अगर (!page)
		जाओ out;
	*page = vm_normal_page(*vma, address, *pte);
	अगर (!*page) अणु
		अगर ((gup_flags & FOLL_DUMP) || !is_zero_pfn(pte_pfn(*pte)))
			जाओ unmap;
		*page = pte_page(*pte);
	पूर्ण
	अगर (unlikely(!try_grab_page(*page, gup_flags))) अणु
		ret = -ENOMEM;
		जाओ unmap;
	पूर्ण
out:
	ret = 0;
unmap:
	pte_unmap(pte);
	वापस ret;
पूर्ण

/*
 * mmap_lock must be held on entry.  If @locked != शून्य and *@flags
 * करोes not include FOLL_NOWAIT, the mmap_lock may be released.  If it
 * is, *@locked will be set to 0 and -EBUSY वापसed.
 */
अटल पूर्णांक faultin_page(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ address, अचिन्हित पूर्णांक *flags, पूर्णांक *locked)
अणु
	अचिन्हित पूर्णांक fault_flags = 0;
	vm_fault_t ret;

	/* mlock all present pages, but करो not fault in new pages */
	अगर ((*flags & (FOLL_POPULATE | FOLL_MLOCK)) == FOLL_MLOCK)
		वापस -ENOENT;
	अगर (*flags & FOLL_WRITE)
		fault_flags |= FAULT_FLAG_WRITE;
	अगर (*flags & FOLL_REMOTE)
		fault_flags |= FAULT_FLAG_REMOTE;
	अगर (locked)
		fault_flags |= FAULT_FLAG_ALLOW_RETRY | FAULT_FLAG_KILLABLE;
	अगर (*flags & FOLL_NOWAIT)
		fault_flags |= FAULT_FLAG_ALLOW_RETRY | FAULT_FLAG_RETRY_NOWAIT;
	अगर (*flags & FOLL_TRIED) अणु
		/*
		 * Note: FAULT_FLAG_ALLOW_RETRY and FAULT_FLAG_TRIED
		 * can co-exist
		 */
		fault_flags |= FAULT_FLAG_TRIED;
	पूर्ण

	ret = handle_mm_fault(vma, address, fault_flags, शून्य);
	अगर (ret & VM_FAULT_ERROR) अणु
		पूर्णांक err = vm_fault_to_त्रुटि_सं(ret, *flags);

		अगर (err)
			वापस err;
		BUG();
	पूर्ण

	अगर (ret & VM_FAULT_RETRY) अणु
		अगर (locked && !(fault_flags & FAULT_FLAG_RETRY_NOWAIT))
			*locked = 0;
		वापस -EBUSY;
	पूर्ण

	/*
	 * The VM_FAULT_WRITE bit tells us that करो_wp_page has broken COW when
	 * necessary, even अगर maybe_mkग_लिखो decided not to set pte_ग_लिखो. We
	 * can thus safely करो subsequent page lookups as अगर they were पढ़ोs.
	 * But only करो so when looping क्रम pte_ग_लिखो is futile: in some हालs
	 * userspace may also be wanting to ग_लिखो to the gotten user page,
	 * which a पढ़ो fault here might prevent (a पढ़ोonly page might get
	 * reCOWed by userspace ग_लिखो).
	 */
	अगर ((ret & VM_FAULT_WRITE) && !(vma->vm_flags & VM_WRITE))
		*flags |= FOLL_COW;
	वापस 0;
पूर्ण

अटल पूर्णांक check_vma_flags(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ gup_flags)
अणु
	vm_flags_t vm_flags = vma->vm_flags;
	पूर्णांक ग_लिखो = (gup_flags & FOLL_WRITE);
	पूर्णांक क्रमeign = (gup_flags & FOLL_REMOTE);

	अगर (vm_flags & (VM_IO | VM_PFNMAP))
		वापस -EFAULT;

	अगर (gup_flags & FOLL_ANON && !vma_is_anonymous(vma))
		वापस -EFAULT;

	अगर ((gup_flags & FOLL_LONGTERM) && vma_is_fsdax(vma))
		वापस -EOPNOTSUPP;

	अगर (ग_लिखो) अणु
		अगर (!(vm_flags & VM_WRITE)) अणु
			अगर (!(gup_flags & FOLL_FORCE))
				वापस -EFAULT;
			/*
			 * We used to let the ग_लिखो,क्रमce हाल करो COW in a
			 * VM_MAYWRITE VM_SHARED !VM_WRITE vma, so ptrace could
			 * set a अवरोधpoपूर्णांक in a पढ़ो-only mapping of an
			 * executable, without corrupting the file (yet only
			 * when that file had been खोलोed क्रम writing!).
			 * Anon pages in shared mappings are surprising: now
			 * just reject it.
			 */
			अगर (!is_cow_mapping(vm_flags))
				वापस -EFAULT;
		पूर्ण
	पूर्ण अन्यथा अगर (!(vm_flags & VM_READ)) अणु
		अगर (!(gup_flags & FOLL_FORCE))
			वापस -EFAULT;
		/*
		 * Is there actually any vma we can reach here which करोes not
		 * have VM_MAYREAD set?
		 */
		अगर (!(vm_flags & VM_MAYREAD))
			वापस -EFAULT;
	पूर्ण
	/*
	 * gups are always data accesses, not inकाष्ठाion
	 * fetches, so execute=false here
	 */
	अगर (!arch_vma_access_permitted(vma, ग_लिखो, false, क्रमeign))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/**
 * __get_user_pages() - pin user pages in memory
 * @mm:		mm_काष्ठा of target mm
 * @start:	starting user address
 * @nr_pages:	number of pages from start to pin
 * @gup_flags:	flags modअगरying pin behaviour
 * @pages:	array that receives poपूर्णांकers to the pages pinned.
 *		Should be at least nr_pages दीर्घ. Or शून्य, अगर caller
 *		only पूर्णांकends to ensure the pages are faulted in.
 * @vmas:	array of poपूर्णांकers to vmas corresponding to each page.
 *		Or शून्य अगर the caller करोes not require them.
 * @locked:     whether we're still with the mmap_lock held
 *
 * Returns either number of pages pinned (which may be less than the
 * number requested), or an error. Details about the वापस value:
 *
 * -- If nr_pages is 0, वापसs 0.
 * -- If nr_pages is >0, but no pages were pinned, वापसs -त्रुटि_सं.
 * -- If nr_pages is >0, and some pages were pinned, वापसs the number of
 *    pages pinned. Again, this may be less than nr_pages.
 * -- 0 वापस value is possible when the fault would need to be retried.
 *
 * The caller is responsible क्रम releasing वापसed @pages, via put_page().
 *
 * @vmas are valid only as दीर्घ as mmap_lock is held.
 *
 * Must be called with mmap_lock held.  It may be released.  See below.
 *
 * __get_user_pages walks a process's page tables and takes a reference to
 * each काष्ठा page that each user address corresponds to at a given
 * instant. That is, it takes the page that would be accessed अगर a user
 * thपढ़ो accesses the given user भव address at that instant.
 *
 * This करोes not guarantee that the page exists in the user mappings when
 * __get_user_pages वापसs, and there may even be a completely dअगरferent
 * page there in some हालs (eg. अगर mmapped pagecache has been invalidated
 * and subsequently re faulted). However it करोes guarantee that the page
 * won't be मुक्तd completely. And mostly callers simply care that the page
 * contains data that was valid *at some poपूर्णांक in समय*. Typically, an IO
 * or similar operation cannot guarantee anything stronger anyway because
 * locks can't be held over the syscall boundary.
 *
 * If @gup_flags & FOLL_WRITE == 0, the page must not be written to. If
 * the page is written to, set_page_dirty (or set_page_dirty_lock, as
 * appropriate) must be called after the page is finished with, and
 * beक्रमe put_page is called.
 *
 * If @locked != शून्य, *@locked will be set to 0 when mmap_lock is
 * released by an up_पढ़ो().  That can happen अगर @gup_flags करोes not
 * have FOLL_NOWAIT.
 *
 * A caller using such a combination of @locked and @gup_flags
 * must thereक्रमe hold the mmap_lock क्रम पढ़ोing only, and recognize
 * when it's been released.  Otherwise, it must be held क्रम either
 * पढ़ोing or writing and will not be released.
 *
 * In most हालs, get_user_pages or get_user_pages_fast should be used
 * instead of __get_user_pages. __get_user_pages should be used only अगर
 * you need some special @gup_flags.
 */
अटल दीर्घ __get_user_pages(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
		अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages,
		काष्ठा vm_area_काष्ठा **vmas, पूर्णांक *locked)
अणु
	दीर्घ ret = 0, i = 0;
	काष्ठा vm_area_काष्ठा *vma = शून्य;
	काष्ठा follow_page_context ctx = अणु शून्य पूर्ण;

	अगर (!nr_pages)
		वापस 0;

	start = untagged_addr(start);

	VM_BUG_ON(!!pages != !!(gup_flags & (FOLL_GET | FOLL_PIN)));

	/*
	 * If FOLL_FORCE is set then करो not क्रमce a full fault as the hपूर्णांकing
	 * fault inक्रमmation is unrelated to the reference behaviour of a task
	 * using the address space
	 */
	अगर (!(gup_flags & FOLL_FORCE))
		gup_flags |= FOLL_NUMA;

	करो अणु
		काष्ठा page *page;
		अचिन्हित पूर्णांक foll_flags = gup_flags;
		अचिन्हित पूर्णांक page_increm;

		/* first iteration or cross vma bound */
		अगर (!vma || start >= vma->vm_end) अणु
			vma = find_extend_vma(mm, start);
			अगर (!vma && in_gate_area(mm, start)) अणु
				ret = get_gate_page(mm, start & PAGE_MASK,
						gup_flags, &vma,
						pages ? &pages[i] : शून्य);
				अगर (ret)
					जाओ out;
				ctx.page_mask = 0;
				जाओ next_page;
			पूर्ण

			अगर (!vma) अणु
				ret = -EFAULT;
				जाओ out;
			पूर्ण
			ret = check_vma_flags(vma, gup_flags);
			अगर (ret)
				जाओ out;

			अगर (is_vm_hugetlb_page(vma)) अणु
				i = follow_hugetlb_page(mm, vma, pages, vmas,
						&start, &nr_pages, i,
						gup_flags, locked);
				अगर (locked && *locked == 0) अणु
					/*
					 * We've got a VM_FAULT_RETRY
					 * and we've lost mmap_lock.
					 * We must stop here.
					 */
					BUG_ON(gup_flags & FOLL_NOWAIT);
					BUG_ON(ret != 0);
					जाओ out;
				पूर्ण
				जारी;
			पूर्ण
		पूर्ण
retry:
		/*
		 * If we have a pending SIGKILL, करोn't keep faulting pages and
		 * potentially allocating memory.
		 */
		अगर (fatal_संकेत_pending(current)) अणु
			ret = -EINTR;
			जाओ out;
		पूर्ण
		cond_resched();

		page = follow_page_mask(vma, start, foll_flags, &ctx);
		अगर (!page) अणु
			ret = faultin_page(vma, start, &foll_flags, locked);
			चयन (ret) अणु
			हाल 0:
				जाओ retry;
			हाल -EBUSY:
				ret = 0;
				fallthrough;
			हाल -EFAULT:
			हाल -ENOMEM:
			हाल -EHWPOISON:
				जाओ out;
			हाल -ENOENT:
				जाओ next_page;
			पूर्ण
			BUG();
		पूर्ण अन्यथा अगर (PTR_ERR(page) == -EEXIST) अणु
			/*
			 * Proper page table entry exists, but no corresponding
			 * काष्ठा page.
			 */
			जाओ next_page;
		पूर्ण अन्यथा अगर (IS_ERR(page)) अणु
			ret = PTR_ERR(page);
			जाओ out;
		पूर्ण
		अगर (pages) अणु
			pages[i] = page;
			flush_anon_page(vma, page, start);
			flush_dcache_page(page);
			ctx.page_mask = 0;
		पूर्ण
next_page:
		अगर (vmas) अणु
			vmas[i] = vma;
			ctx.page_mask = 0;
		पूर्ण
		page_increm = 1 + (~(start >> PAGE_SHIFT) & ctx.page_mask);
		अगर (page_increm > nr_pages)
			page_increm = nr_pages;
		i += page_increm;
		start += page_increm * PAGE_SIZE;
		nr_pages -= page_increm;
	पूर्ण जबतक (nr_pages);
out:
	अगर (ctx.pgmap)
		put_dev_pagemap(ctx.pgmap);
	वापस i ? i : ret;
पूर्ण

अटल bool vma_permits_fault(काष्ठा vm_area_काष्ठा *vma,
			      अचिन्हित पूर्णांक fault_flags)
अणु
	bool ग_लिखो   = !!(fault_flags & FAULT_FLAG_WRITE);
	bool क्रमeign = !!(fault_flags & FAULT_FLAG_REMOTE);
	vm_flags_t vm_flags = ग_लिखो ? VM_WRITE : VM_READ;

	अगर (!(vm_flags & vma->vm_flags))
		वापस false;

	/*
	 * The architecture might have a hardware protection
	 * mechanism other than पढ़ो/ग_लिखो that can deny access.
	 *
	 * gup always represents data access, not inकाष्ठाion
	 * fetches, so execute=false here:
	 */
	अगर (!arch_vma_access_permitted(vma, ग_लिखो, false, क्रमeign))
		वापस false;

	वापस true;
पूर्ण

/**
 * fixup_user_fault() - manually resolve a user page fault
 * @mm:		mm_काष्ठा of target mm
 * @address:	user address
 * @fault_flags:flags to pass करोwn to handle_mm_fault()
 * @unlocked:	did we unlock the mmap_lock जबतक retrying, maybe शून्य अगर caller
 *		करोes not allow retry. If शून्य, the caller must guarantee
 *		that fault_flags करोes not contain FAULT_FLAG_ALLOW_RETRY.
 *
 * This is meant to be called in the specअगरic scenario where क्रम locking reasons
 * we try to access user memory in atomic context (within a pagefault_disable()
 * section), this वापसs -EFAULT, and we want to resolve the user fault beक्रमe
 * trying again.
 *
 * Typically this is meant to be used by the futex code.
 *
 * The मुख्य dअगरference with get_user_pages() is that this function will
 * unconditionally call handle_mm_fault() which will in turn perक्रमm all the
 * necessary SW fixup of the dirty and young bits in the PTE, जबतक
 * get_user_pages() only guarantees to update these in the काष्ठा page.
 *
 * This is important क्रम some architectures where those bits also gate the
 * access permission to the page because they are मुख्यtained in software.  On
 * such architectures, gup() will not be enough to make a subsequent access
 * succeed.
 *
 * This function will not वापस with an unlocked mmap_lock. So it has not the
 * same semantics wrt the @mm->mmap_lock as करोes filemap_fault().
 */
पूर्णांक fixup_user_fault(काष्ठा mm_काष्ठा *mm,
		     अचिन्हित दीर्घ address, अचिन्हित पूर्णांक fault_flags,
		     bool *unlocked)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	vm_fault_t ret, major = 0;

	address = untagged_addr(address);

	अगर (unlocked)
		fault_flags |= FAULT_FLAG_ALLOW_RETRY | FAULT_FLAG_KILLABLE;

retry:
	vma = find_extend_vma(mm, address);
	अगर (!vma || address < vma->vm_start)
		वापस -EFAULT;

	अगर (!vma_permits_fault(vma, fault_flags))
		वापस -EFAULT;

	अगर ((fault_flags & FAULT_FLAG_KILLABLE) &&
	    fatal_संकेत_pending(current))
		वापस -EINTR;

	ret = handle_mm_fault(vma, address, fault_flags, शून्य);
	major |= ret & VM_FAULT_MAJOR;
	अगर (ret & VM_FAULT_ERROR) अणु
		पूर्णांक err = vm_fault_to_त्रुटि_सं(ret, 0);

		अगर (err)
			वापस err;
		BUG();
	पूर्ण

	अगर (ret & VM_FAULT_RETRY) अणु
		mmap_पढ़ो_lock(mm);
		*unlocked = true;
		fault_flags |= FAULT_FLAG_TRIED;
		जाओ retry;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fixup_user_fault);

/*
 * Please note that this function, unlike __get_user_pages will not
 * वापस 0 क्रम nr_pages > 0 without FOLL_NOWAIT
 */
अटल __always_अंतरभूत दीर्घ __get_user_pages_locked(काष्ठा mm_काष्ठा *mm,
						अचिन्हित दीर्घ start,
						अचिन्हित दीर्घ nr_pages,
						काष्ठा page **pages,
						काष्ठा vm_area_काष्ठा **vmas,
						पूर्णांक *locked,
						अचिन्हित पूर्णांक flags)
अणु
	दीर्घ ret, pages_करोne;
	bool lock_dropped;

	अगर (locked) अणु
		/* अगर VM_FAULT_RETRY can be वापसed, vmas become invalid */
		BUG_ON(vmas);
		/* check caller initialized locked */
		BUG_ON(*locked != 1);
	पूर्ण

	अगर (flags & FOLL_PIN)
		atomic_set(&mm->has_pinned, 1);

	/*
	 * FOLL_PIN and FOLL_GET are mutually exclusive. Traditional behavior
	 * is to set FOLL_GET अगर the caller wants pages[] filled in (but has
	 * carelessly failed to specअगरy FOLL_GET), so keep करोing that, but only
	 * क्रम FOLL_GET, not क्रम the newer FOLL_PIN.
	 *
	 * FOLL_PIN always expects pages to be non-null, but no need to निश्चित
	 * that here, as any failures will be obvious enough.
	 */
	अगर (pages && !(flags & FOLL_PIN))
		flags |= FOLL_GET;

	pages_करोne = 0;
	lock_dropped = false;
	क्रम (;;) अणु
		ret = __get_user_pages(mm, start, nr_pages, flags, pages,
				       vmas, locked);
		अगर (!locked)
			/* VM_FAULT_RETRY couldn't trigger, bypass */
			वापस ret;

		/* VM_FAULT_RETRY cannot वापस errors */
		अगर (!*locked) अणु
			BUG_ON(ret < 0);
			BUG_ON(ret >= nr_pages);
		पूर्ण

		अगर (ret > 0) अणु
			nr_pages -= ret;
			pages_करोne += ret;
			अगर (!nr_pages)
				अवरोध;
		पूर्ण
		अगर (*locked) अणु
			/*
			 * VM_FAULT_RETRY didn't trigger or it was a
			 * FOLL_NOWAIT.
			 */
			अगर (!pages_करोne)
				pages_करोne = ret;
			अवरोध;
		पूर्ण
		/*
		 * VM_FAULT_RETRY triggered, so seek to the faulting offset.
		 * For the prefault हाल (!pages) we only update counts.
		 */
		अगर (likely(pages))
			pages += ret;
		start += ret << PAGE_SHIFT;
		lock_dropped = true;

retry:
		/*
		 * Repeat on the address that fired VM_FAULT_RETRY
		 * with both FAULT_FLAG_ALLOW_RETRY and
		 * FAULT_FLAG_TRIED.  Note that GUP can be पूर्णांकerrupted
		 * by fatal संकेतs, so we need to check it beक्रमe we
		 * start trying again otherwise it can loop क्रमever.
		 */

		अगर (fatal_संकेत_pending(current)) अणु
			अगर (!pages_करोne)
				pages_करोne = -EINTR;
			अवरोध;
		पूर्ण

		ret = mmap_पढ़ो_lock_समाप्तable(mm);
		अगर (ret) अणु
			BUG_ON(ret > 0);
			अगर (!pages_करोne)
				pages_करोne = ret;
			अवरोध;
		पूर्ण

		*locked = 1;
		ret = __get_user_pages(mm, start, 1, flags | FOLL_TRIED,
				       pages, शून्य, locked);
		अगर (!*locked) अणु
			/* Continue to retry until we succeeded */
			BUG_ON(ret != 0);
			जाओ retry;
		पूर्ण
		अगर (ret != 1) अणु
			BUG_ON(ret > 1);
			अगर (!pages_करोne)
				pages_करोne = ret;
			अवरोध;
		पूर्ण
		nr_pages--;
		pages_करोne++;
		अगर (!nr_pages)
			अवरोध;
		अगर (likely(pages))
			pages++;
		start += PAGE_SIZE;
	पूर्ण
	अगर (lock_dropped && *locked) अणु
		/*
		 * We must let the caller know we temporarily dropped the lock
		 * and so the critical section रक्षित by it was lost.
		 */
		mmap_पढ़ो_unlock(mm);
		*locked = 0;
	पूर्ण
	वापस pages_करोne;
पूर्ण

/**
 * populate_vma_page_range() -  populate a range of pages in the vma.
 * @vma:   target vma
 * @start: start address
 * @end:   end address
 * @locked: whether the mmap_lock is still held
 *
 * This takes care of mlocking the pages too अगर VM_LOCKED is set.
 *
 * Return either number of pages pinned in the vma, or a negative error
 * code on error.
 *
 * vma->vm_mm->mmap_lock must be held.
 *
 * If @locked is शून्य, it may be held क्रम पढ़ो or ग_लिखो and will
 * be unperturbed.
 *
 * If @locked is non-शून्य, it must held क्रम पढ़ो only and may be
 * released.  If it's released, *@locked will be set to 0.
 */
दीर्घ populate_vma_page_range(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक *locked)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित दीर्घ nr_pages = (end - start) / PAGE_SIZE;
	पूर्णांक gup_flags;

	VM_BUG_ON(start & ~PAGE_MASK);
	VM_BUG_ON(end   & ~PAGE_MASK);
	VM_BUG_ON_VMA(start < vma->vm_start, vma);
	VM_BUG_ON_VMA(end   > vma->vm_end, vma);
	mmap_निश्चित_locked(mm);

	gup_flags = FOLL_TOUCH | FOLL_POPULATE | FOLL_MLOCK;
	अगर (vma->vm_flags & VM_LOCKONFAULT)
		gup_flags &= ~FOLL_POPULATE;
	/*
	 * We want to touch writable mappings with a ग_लिखो fault in order
	 * to अवरोध COW, except क्रम shared mappings because these करोn't COW
	 * and we would not want to dirty them क्रम nothing.
	 */
	अगर ((vma->vm_flags & (VM_WRITE | VM_SHARED)) == VM_WRITE)
		gup_flags |= FOLL_WRITE;

	/*
	 * We want mlock to succeed क्रम regions that have any permissions
	 * other than PROT_NONE.
	 */
	अगर (vma_is_accessible(vma))
		gup_flags |= FOLL_FORCE;

	/*
	 * We made sure addr is within a VMA, so the following will
	 * not result in a stack expansion that recurses back here.
	 */
	वापस __get_user_pages(mm, start, nr_pages, gup_flags,
				शून्य, शून्य, locked);
पूर्ण

/*
 * __mm_populate - populate and/or mlock pages within a range of address space.
 *
 * This is used to implement mlock() and the MAP_POPULATE / MAP_LOCKED mmap
 * flags. VMAs must be alपढ़ोy marked with the desired vm_flags, and
 * mmap_lock must not be held.
 */
पूर्णांक __mm_populate(अचिन्हित दीर्घ start, अचिन्हित दीर्घ len, पूर्णांक ignore_errors)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ end, nstart, nend;
	काष्ठा vm_area_काष्ठा *vma = शून्य;
	पूर्णांक locked = 0;
	दीर्घ ret = 0;

	end = start + len;

	क्रम (nstart = start; nstart < end; nstart = nend) अणु
		/*
		 * We want to fault in pages क्रम [nstart; end) address range.
		 * Find first corresponding VMA.
		 */
		अगर (!locked) अणु
			locked = 1;
			mmap_पढ़ो_lock(mm);
			vma = find_vma(mm, nstart);
		पूर्ण अन्यथा अगर (nstart >= vma->vm_end)
			vma = vma->vm_next;
		अगर (!vma || vma->vm_start >= end)
			अवरोध;
		/*
		 * Set [nstart; nend) to पूर्णांकersection of desired address
		 * range with the first VMA. Also, skip undesirable VMA types.
		 */
		nend = min(end, vma->vm_end);
		अगर (vma->vm_flags & (VM_IO | VM_PFNMAP))
			जारी;
		अगर (nstart < vma->vm_start)
			nstart = vma->vm_start;
		/*
		 * Now fault in a range of pages. populate_vma_page_range()
		 * द्विगुन checks the vma flags, so that it won't mlock pages
		 * अगर the vma was alपढ़ोy munlocked.
		 */
		ret = populate_vma_page_range(vma, nstart, nend, &locked);
		अगर (ret < 0) अणु
			अगर (ignore_errors) अणु
				ret = 0;
				जारी;	/* जारी at next VMA */
			पूर्ण
			अवरोध;
		पूर्ण
		nend = nstart + ret * PAGE_SIZE;
		ret = 0;
	पूर्ण
	अगर (locked)
		mmap_पढ़ो_unlock(mm);
	वापस ret;	/* 0 or negative error code */
पूर्ण
#अन्यथा /* CONFIG_MMU */
अटल दीर्घ __get_user_pages_locked(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ nr_pages, काष्ठा page **pages,
		काष्ठा vm_area_काष्ठा **vmas, पूर्णांक *locked,
		अचिन्हित पूर्णांक foll_flags)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ vm_flags;
	दीर्घ i;

	/* calculate required पढ़ो or ग_लिखो permissions.
	 * If FOLL_FORCE is set, we only require the "MAY" flags.
	 */
	vm_flags  = (foll_flags & FOLL_WRITE) ?
			(VM_WRITE | VM_MAYWRITE) : (VM_READ | VM_MAYREAD);
	vm_flags &= (foll_flags & FOLL_FORCE) ?
			(VM_MAYREAD | VM_MAYWRITE) : (VM_READ | VM_WRITE);

	क्रम (i = 0; i < nr_pages; i++) अणु
		vma = find_vma(mm, start);
		अगर (!vma)
			जाओ finish_or_fault;

		/* protect what we can, including अक्षरdevs */
		अगर ((vma->vm_flags & (VM_IO | VM_PFNMAP)) ||
		    !(vm_flags & vma->vm_flags))
			जाओ finish_or_fault;

		अगर (pages) अणु
			pages[i] = virt_to_page(start);
			अगर (pages[i])
				get_page(pages[i]);
		पूर्ण
		अगर (vmas)
			vmas[i] = vma;
		start = (start + PAGE_SIZE) & PAGE_MASK;
	पूर्ण

	वापस i;

finish_or_fault:
	वापस i ? : -EFAULT;
पूर्ण
#पूर्ण_अगर /* !CONFIG_MMU */

/**
 * get_dump_page() - pin user page in memory जबतक writing it to core dump
 * @addr: user address
 *
 * Returns काष्ठा page poपूर्णांकer of user page pinned क्रम dump,
 * to be मुक्तd afterwards by put_page().
 *
 * Returns शून्य on any kind of failure - a hole must then be inserted पूर्णांकo
 * the corefile, to preserve alignment with its headers; and also वापसs
 * शून्य wherever the ZERO_PAGE, or an anonymous pte_none, has been found -
 * allowing a hole to be left in the corefile to save disk space.
 *
 * Called without mmap_lock (takes and releases the mmap_lock by itself).
 */
#अगर_घोषित CONFIG_ELF_CORE
काष्ठा page *get_dump_page(अचिन्हित दीर्घ addr)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा page *page;
	पूर्णांक locked = 1;
	पूर्णांक ret;

	अगर (mmap_पढ़ो_lock_समाप्तable(mm))
		वापस शून्य;
	ret = __get_user_pages_locked(mm, addr, 1, &page, शून्य, &locked,
				      FOLL_FORCE | FOLL_DUMP | FOLL_GET);
	अगर (locked)
		mmap_पढ़ो_unlock(mm);
	वापस (ret == 1) ? page : शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_ELF_CORE */

#अगर_घोषित CONFIG_MIGRATION
/*
 * Check whether all pages are pinnable, अगर so वापस number of pages.  If some
 * pages are not pinnable, migrate them, and unpin all pages. Return zero अगर
 * pages were migrated, or अगर some pages were not successfully isolated.
 * Return negative error अगर migration fails.
 */
अटल दीर्घ check_and_migrate_movable_pages(अचिन्हित दीर्घ nr_pages,
					    काष्ठा page **pages,
					    अचिन्हित पूर्णांक gup_flags)
अणु
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ isolation_error_count = 0;
	bool drain_allow = true;
	LIST_HEAD(movable_page_list);
	दीर्घ ret = 0;
	काष्ठा page *prev_head = शून्य;
	काष्ठा page *head;
	काष्ठा migration_target_control mtc = अणु
		.nid = NUMA_NO_NODE,
		.gfp_mask = GFP_USER | __GFP_NOWARN,
	पूर्ण;

	क्रम (i = 0; i < nr_pages; i++) अणु
		head = compound_head(pages[i]);
		अगर (head == prev_head)
			जारी;
		prev_head = head;
		/*
		 * If we get a movable page, since we are going to be pinning
		 * these entries, try to move them out अगर possible.
		 */
		अगर (!is_pinnable_page(head)) अणु
			अगर (PageHuge(head)) अणु
				अगर (!isolate_huge_page(head, &movable_page_list))
					isolation_error_count++;
			पूर्ण अन्यथा अणु
				अगर (!PageLRU(head) && drain_allow) अणु
					lru_add_drain_all();
					drain_allow = false;
				पूर्ण

				अगर (isolate_lru_page(head)) अणु
					isolation_error_count++;
					जारी;
				पूर्ण
				list_add_tail(&head->lru, &movable_page_list);
				mod_node_page_state(page_pgdat(head),
						    NR_ISOLATED_ANON +
						    page_is_file_lru(head),
						    thp_nr_pages(head));
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * If list is empty, and no isolation errors, means that all pages are
	 * in the correct zone.
	 */
	अगर (list_empty(&movable_page_list) && !isolation_error_count)
		वापस nr_pages;

	अगर (gup_flags & FOLL_PIN) अणु
		unpin_user_pages(pages, nr_pages);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < nr_pages; i++)
			put_page(pages[i]);
	पूर्ण
	अगर (!list_empty(&movable_page_list)) अणु
		ret = migrate_pages(&movable_page_list, alloc_migration_target,
				    शून्य, (अचिन्हित दीर्घ)&mtc, MIGRATE_SYNC,
				    MR_LONGTERM_PIN);
		अगर (ret && !list_empty(&movable_page_list))
			putback_movable_pages(&movable_page_list);
	पूर्ण

	वापस ret > 0 ? -ENOMEM : ret;
पूर्ण
#अन्यथा
अटल दीर्घ check_and_migrate_movable_pages(अचिन्हित दीर्घ nr_pages,
					    काष्ठा page **pages,
					    अचिन्हित पूर्णांक gup_flags)
अणु
	वापस nr_pages;
पूर्ण
#पूर्ण_अगर /* CONFIG_MIGRATION */

/*
 * __gup_दीर्घterm_locked() is a wrapper क्रम __get_user_pages_locked which
 * allows us to process the FOLL_LONGTERM flag.
 */
अटल दीर्घ __gup_दीर्घterm_locked(काष्ठा mm_काष्ठा *mm,
				  अचिन्हित दीर्घ start,
				  अचिन्हित दीर्घ nr_pages,
				  काष्ठा page **pages,
				  काष्ठा vm_area_काष्ठा **vmas,
				  अचिन्हित पूर्णांक gup_flags)
अणु
	अचिन्हित पूर्णांक flags;
	दीर्घ rc;

	अगर (!(gup_flags & FOLL_LONGTERM))
		वापस __get_user_pages_locked(mm, start, nr_pages, pages, vmas,
					       शून्य, gup_flags);
	flags = meदो_स्मृति_pin_save();
	करो अणु
		rc = __get_user_pages_locked(mm, start, nr_pages, pages, vmas,
					     शून्य, gup_flags);
		अगर (rc <= 0)
			अवरोध;
		rc = check_and_migrate_movable_pages(rc, pages, gup_flags);
	पूर्ण जबतक (!rc);
	meदो_स्मृति_pin_restore(flags);

	वापस rc;
पूर्ण

अटल bool is_valid_gup_flags(अचिन्हित पूर्णांक gup_flags)
अणु
	/*
	 * FOLL_PIN must only be set पूर्णांकernally by the pin_user_pages*() APIs,
	 * never directly by the caller, so enक्रमce that with an निश्चितion:
	 */
	अगर (WARN_ON_ONCE(gup_flags & FOLL_PIN))
		वापस false;
	/*
	 * FOLL_PIN is a prerequisite to FOLL_LONGTERM. Another way of saying
	 * that is, FOLL_LONGTERM is a specअगरic हाल, more restrictive हाल of
	 * FOLL_PIN.
	 */
	अगर (WARN_ON_ONCE(gup_flags & FOLL_LONGTERM))
		वापस false;

	वापस true;
पूर्ण

#अगर_घोषित CONFIG_MMU
अटल दीर्घ __get_user_pages_remote(काष्ठा mm_काष्ठा *mm,
				    अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
				    अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages,
				    काष्ठा vm_area_काष्ठा **vmas, पूर्णांक *locked)
अणु
	/*
	 * Parts of FOLL_LONGTERM behavior are incompatible with
	 * FAULT_FLAG_ALLOW_RETRY because of the FS DAX check requirement on
	 * vmas. However, this only comes up अगर locked is set, and there are
	 * callers that करो request FOLL_LONGTERM, but करो not set locked. So,
	 * allow what we can.
	 */
	अगर (gup_flags & FOLL_LONGTERM) अणु
		अगर (WARN_ON_ONCE(locked))
			वापस -EINVAL;
		/*
		 * This will check the vmas (even अगर our vmas arg is शून्य)
		 * and वापस -ENOTSUPP अगर DAX isn't allowed in this हाल:
		 */
		वापस __gup_दीर्घterm_locked(mm, start, nr_pages, pages,
					     vmas, gup_flags | FOLL_TOUCH |
					     FOLL_REMOTE);
	पूर्ण

	वापस __get_user_pages_locked(mm, start, nr_pages, pages, vmas,
				       locked,
				       gup_flags | FOLL_TOUCH | FOLL_REMOTE);
पूर्ण

/**
 * get_user_pages_remote() - pin user pages in memory
 * @mm:		mm_काष्ठा of target mm
 * @start:	starting user address
 * @nr_pages:	number of pages from start to pin
 * @gup_flags:	flags modअगरying lookup behaviour
 * @pages:	array that receives poपूर्णांकers to the pages pinned.
 *		Should be at least nr_pages दीर्घ. Or शून्य, अगर caller
 *		only पूर्णांकends to ensure the pages are faulted in.
 * @vmas:	array of poपूर्णांकers to vmas corresponding to each page.
 *		Or शून्य अगर the caller करोes not require them.
 * @locked:	poपूर्णांकer to lock flag indicating whether lock is held and
 *		subsequently whether VM_FAULT_RETRY functionality can be
 *		utilised. Lock must initially be held.
 *
 * Returns either number of pages pinned (which may be less than the
 * number requested), or an error. Details about the वापस value:
 *
 * -- If nr_pages is 0, वापसs 0.
 * -- If nr_pages is >0, but no pages were pinned, वापसs -त्रुटि_सं.
 * -- If nr_pages is >0, and some pages were pinned, वापसs the number of
 *    pages pinned. Again, this may be less than nr_pages.
 *
 * The caller is responsible क्रम releasing वापसed @pages, via put_page().
 *
 * @vmas are valid only as दीर्घ as mmap_lock is held.
 *
 * Must be called with mmap_lock held क्रम पढ़ो or ग_लिखो.
 *
 * get_user_pages_remote walks a process's page tables and takes a reference
 * to each काष्ठा page that each user address corresponds to at a given
 * instant. That is, it takes the page that would be accessed अगर a user
 * thपढ़ो accesses the given user भव address at that instant.
 *
 * This करोes not guarantee that the page exists in the user mappings when
 * get_user_pages_remote वापसs, and there may even be a completely dअगरferent
 * page there in some हालs (eg. अगर mmapped pagecache has been invalidated
 * and subsequently re faulted). However it करोes guarantee that the page
 * won't be मुक्तd completely. And mostly callers simply care that the page
 * contains data that was valid *at some poपूर्णांक in समय*. Typically, an IO
 * or similar operation cannot guarantee anything stronger anyway because
 * locks can't be held over the syscall boundary.
 *
 * If gup_flags & FOLL_WRITE == 0, the page must not be written to. If the page
 * is written to, set_page_dirty (or set_page_dirty_lock, as appropriate) must
 * be called after the page is finished with, and beक्रमe put_page is called.
 *
 * get_user_pages_remote is typically used क्रम fewer-copy IO operations,
 * to get a handle on the memory by some means other than accesses
 * via the user भव addresses. The pages may be submitted क्रम
 * DMA to devices or accessed via their kernel linear mapping (via the
 * kmap APIs). Care should be taken to use the correct cache flushing APIs.
 *
 * See also get_user_pages_fast, क्रम perक्रमmance critical applications.
 *
 * get_user_pages_remote should be phased out in favor of
 * get_user_pages_locked|unlocked or get_user_pages_fast. Nothing
 * should use get_user_pages_remote because it cannot pass
 * FAULT_FLAG_ALLOW_RETRY to handle_mm_fault.
 */
दीर्घ get_user_pages_remote(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
		अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages,
		काष्ठा vm_area_काष्ठा **vmas, पूर्णांक *locked)
अणु
	अगर (!is_valid_gup_flags(gup_flags))
		वापस -EINVAL;

	वापस __get_user_pages_remote(mm, start, nr_pages, gup_flags,
				       pages, vmas, locked);
पूर्ण
EXPORT_SYMBOL(get_user_pages_remote);

#अन्यथा /* CONFIG_MMU */
दीर्घ get_user_pages_remote(काष्ठा mm_काष्ठा *mm,
			   अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
			   अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages,
			   काष्ठा vm_area_काष्ठा **vmas, पूर्णांक *locked)
अणु
	वापस 0;
पूर्ण

अटल दीर्घ __get_user_pages_remote(काष्ठा mm_काष्ठा *mm,
				    अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
				    अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages,
				    काष्ठा vm_area_काष्ठा **vmas, पूर्णांक *locked)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* !CONFIG_MMU */

/**
 * get_user_pages() - pin user pages in memory
 * @start:      starting user address
 * @nr_pages:   number of pages from start to pin
 * @gup_flags:  flags modअगरying lookup behaviour
 * @pages:      array that receives poपूर्णांकers to the pages pinned.
 *              Should be at least nr_pages दीर्घ. Or शून्य, अगर caller
 *              only पूर्णांकends to ensure the pages are faulted in.
 * @vmas:       array of poपूर्णांकers to vmas corresponding to each page.
 *              Or शून्य अगर the caller करोes not require them.
 *
 * This is the same as get_user_pages_remote(), just with a less-flexible
 * calling convention where we assume that the mm being operated on beदीर्घs to
 * the current task, and करोesn't allow passing of a locked parameter.  We also
 * obviously करोn't pass FOLL_REMOTE in here.
 */
दीर्घ get_user_pages(अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
		अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages,
		काष्ठा vm_area_काष्ठा **vmas)
अणु
	अगर (!is_valid_gup_flags(gup_flags))
		वापस -EINVAL;

	वापस __gup_दीर्घterm_locked(current->mm, start, nr_pages,
				     pages, vmas, gup_flags | FOLL_TOUCH);
पूर्ण
EXPORT_SYMBOL(get_user_pages);

/**
 * get_user_pages_locked() - variant of get_user_pages()
 *
 * @start:      starting user address
 * @nr_pages:   number of pages from start to pin
 * @gup_flags:  flags modअगरying lookup behaviour
 * @pages:      array that receives poपूर्णांकers to the pages pinned.
 *              Should be at least nr_pages दीर्घ. Or शून्य, अगर caller
 *              only पूर्णांकends to ensure the pages are faulted in.
 * @locked:     poपूर्णांकer to lock flag indicating whether lock is held and
 *              subsequently whether VM_FAULT_RETRY functionality can be
 *              utilised. Lock must initially be held.
 *
 * It is suitable to replace the क्रमm:
 *
 *      mmap_पढ़ो_lock(mm);
 *      करो_something()
 *      get_user_pages(mm, ..., pages, शून्य);
 *      mmap_पढ़ो_unlock(mm);
 *
 *  to:
 *
 *      पूर्णांक locked = 1;
 *      mmap_पढ़ो_lock(mm);
 *      करो_something()
 *      get_user_pages_locked(mm, ..., pages, &locked);
 *      अगर (locked)
 *          mmap_पढ़ो_unlock(mm);
 *
 * We can leverage the VM_FAULT_RETRY functionality in the page fault
 * paths better by using either get_user_pages_locked() or
 * get_user_pages_unlocked().
 *
 */
दीर्घ get_user_pages_locked(अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
			   अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages,
			   पूर्णांक *locked)
अणु
	/*
	 * FIXME: Current FOLL_LONGTERM behavior is incompatible with
	 * FAULT_FLAG_ALLOW_RETRY because of the FS DAX check requirement on
	 * vmas.  As there are no users of this flag in this call we simply
	 * disallow this option क्रम now.
	 */
	अगर (WARN_ON_ONCE(gup_flags & FOLL_LONGTERM))
		वापस -EINVAL;
	/*
	 * FOLL_PIN must only be set पूर्णांकernally by the pin_user_pages*() APIs,
	 * never directly by the caller, so enक्रमce that:
	 */
	अगर (WARN_ON_ONCE(gup_flags & FOLL_PIN))
		वापस -EINVAL;

	वापस __get_user_pages_locked(current->mm, start, nr_pages,
				       pages, शून्य, locked,
				       gup_flags | FOLL_TOUCH);
पूर्ण
EXPORT_SYMBOL(get_user_pages_locked);

/*
 * get_user_pages_unlocked() is suitable to replace the क्रमm:
 *
 *      mmap_पढ़ो_lock(mm);
 *      get_user_pages(mm, ..., pages, शून्य);
 *      mmap_पढ़ो_unlock(mm);
 *
 *  with:
 *
 *      get_user_pages_unlocked(mm, ..., pages);
 *
 * It is functionally equivalent to get_user_pages_fast so
 * get_user_pages_fast should be used instead अगर specअगरic gup_flags
 * (e.g. FOLL_FORCE) are not required.
 */
दीर्घ get_user_pages_unlocked(अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
			     काष्ठा page **pages, अचिन्हित पूर्णांक gup_flags)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	पूर्णांक locked = 1;
	दीर्घ ret;

	/*
	 * FIXME: Current FOLL_LONGTERM behavior is incompatible with
	 * FAULT_FLAG_ALLOW_RETRY because of the FS DAX check requirement on
	 * vmas.  As there are no users of this flag in this call we simply
	 * disallow this option क्रम now.
	 */
	अगर (WARN_ON_ONCE(gup_flags & FOLL_LONGTERM))
		वापस -EINVAL;

	mmap_पढ़ो_lock(mm);
	ret = __get_user_pages_locked(mm, start, nr_pages, pages, शून्य,
				      &locked, gup_flags | FOLL_TOUCH);
	अगर (locked)
		mmap_पढ़ो_unlock(mm);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(get_user_pages_unlocked);

/*
 * Fast GUP
 *
 * get_user_pages_fast attempts to pin user pages by walking the page
 * tables directly and aव्योमs taking locks. Thus the walker needs to be
 * रक्षित from page table pages being मुक्तd from under it, and should
 * block any THP splits.
 *
 * One way to achieve this is to have the walker disable पूर्णांकerrupts, and
 * rely on IPIs from the TLB flushing code blocking beक्रमe the page table
 * pages are मुक्तd. This is unsuitable क्रम architectures that करो not need
 * to broadcast an IPI when invalidating TLBs.
 *
 * Another way to achieve this is to batch up page table containing pages
 * beदीर्घing to more than one mm_user, then rcu_sched a callback to मुक्त those
 * pages. Disabling पूर्णांकerrupts will allow the fast_gup walker to both block
 * the rcu_sched callback, and an IPI that we broadcast क्रम splitting THPs
 * (which is a relatively rare event). The code below aकरोpts this strategy.
 *
 * Beक्रमe activating this code, please be aware that the following assumptions
 * are currently made:
 *
 *  *) Either MMU_GATHER_RCU_TABLE_FREE is enabled, and tlb_हटाओ_table() is used to
 *  मुक्त pages containing page tables or TLB flushing requires IPI broadcast.
 *
 *  *) ptes can be पढ़ो atomically by the architecture.
 *
 *  *) access_ok is sufficient to validate userspace address ranges.
 *
 * The last two assumptions can be relaxed by the addition of helper functions.
 *
 * This code is based heavily on the PowerPC implementation by Nick Piggin.
 */
#अगर_घोषित CONFIG_HAVE_FAST_GUP

अटल व्योम __maybe_unused unकरो_dev_pagemap(पूर्णांक *nr, पूर्णांक nr_start,
					    अचिन्हित पूर्णांक flags,
					    काष्ठा page **pages)
अणु
	जबतक ((*nr) - nr_start) अणु
		काष्ठा page *page = pages[--(*nr)];

		ClearPageReferenced(page);
		अगर (flags & FOLL_PIN)
			unpin_user_page(page);
		अन्यथा
			put_page(page);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ARCH_HAS_PTE_SPECIAL
अटल पूर्णांक gup_pte_range(pmd_t pmd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			 अचिन्हित पूर्णांक flags, काष्ठा page **pages, पूर्णांक *nr)
अणु
	काष्ठा dev_pagemap *pgmap = शून्य;
	पूर्णांक nr_start = *nr, ret = 0;
	pte_t *ptep, *ptem;

	ptem = ptep = pte_offset_map(&pmd, addr);
	करो अणु
		pte_t pte = ptep_get_lockless(ptep);
		काष्ठा page *head, *page;

		/*
		 * Similar to the PMD हाल below, NUMA hपूर्णांकing must take slow
		 * path using the pte_protnone check.
		 */
		अगर (pte_protnone(pte))
			जाओ pte_unmap;

		अगर (!pte_access_permitted(pte, flags & FOLL_WRITE))
			जाओ pte_unmap;

		अगर (pte_devmap(pte)) अणु
			अगर (unlikely(flags & FOLL_LONGTERM))
				जाओ pte_unmap;

			pgmap = get_dev_pagemap(pte_pfn(pte), pgmap);
			अगर (unlikely(!pgmap)) अणु
				unकरो_dev_pagemap(nr, nr_start, flags, pages);
				जाओ pte_unmap;
			पूर्ण
		पूर्ण अन्यथा अगर (pte_special(pte))
			जाओ pte_unmap;

		VM_BUG_ON(!pfn_valid(pte_pfn(pte)));
		page = pte_page(pte);

		head = try_grab_compound_head(page, 1, flags);
		अगर (!head)
			जाओ pte_unmap;

		अगर (unlikely(pte_val(pte) != pte_val(*ptep))) अणु
			put_compound_head(head, 1, flags);
			जाओ pte_unmap;
		पूर्ण

		VM_BUG_ON_PAGE(compound_head(page) != head, page);

		/*
		 * We need to make the page accessible अगर and only अगर we are
		 * going to access its content (the FOLL_PIN हाल).  Please
		 * see Documentation/core-api/pin_user_pages.rst क्रम
		 * details.
		 */
		अगर (flags & FOLL_PIN) अणु
			ret = arch_make_page_accessible(page);
			अगर (ret) अणु
				unpin_user_page(page);
				जाओ pte_unmap;
			पूर्ण
		पूर्ण
		SetPageReferenced(page);
		pages[*nr] = page;
		(*nr)++;

	पूर्ण जबतक (ptep++, addr += PAGE_SIZE, addr != end);

	ret = 1;

pte_unmap:
	अगर (pgmap)
		put_dev_pagemap(pgmap);
	pte_unmap(ptem);
	वापस ret;
पूर्ण
#अन्यथा

/*
 * If we can't determine whether or not a pte is special, then fail immediately
 * क्रम ptes. Note, we can still pin HugeTLB and THP as these are guaranteed not
 * to be special.
 *
 * For a futex to be placed on a THP tail page, get_futex_key requires a
 * get_user_pages_fast_only implementation that can pin pages. Thus it's still
 * useful to have gup_huge_pmd even अगर we can't operate on ptes.
 */
अटल पूर्णांक gup_pte_range(pmd_t pmd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			 अचिन्हित पूर्णांक flags, काष्ठा page **pages, पूर्णांक *nr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HAS_PTE_SPECIAL */

#अगर defined(CONFIG_ARCH_HAS_PTE_DEVMAP) && defined(CONFIG_TRANSPARENT_HUGEPAGE)
अटल पूर्णांक __gup_device_huge(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ addr,
			     अचिन्हित दीर्घ end, अचिन्हित पूर्णांक flags,
			     काष्ठा page **pages, पूर्णांक *nr)
अणु
	पूर्णांक nr_start = *nr;
	काष्ठा dev_pagemap *pgmap = शून्य;

	करो अणु
		काष्ठा page *page = pfn_to_page(pfn);

		pgmap = get_dev_pagemap(pfn, pgmap);
		अगर (unlikely(!pgmap)) अणु
			unकरो_dev_pagemap(nr, nr_start, flags, pages);
			वापस 0;
		पूर्ण
		SetPageReferenced(page);
		pages[*nr] = page;
		अगर (unlikely(!try_grab_page(page, flags))) अणु
			unकरो_dev_pagemap(nr, nr_start, flags, pages);
			वापस 0;
		पूर्ण
		(*nr)++;
		pfn++;
	पूर्ण जबतक (addr += PAGE_SIZE, addr != end);

	अगर (pgmap)
		put_dev_pagemap(pgmap);
	वापस 1;
पूर्ण

अटल पूर्णांक __gup_device_huge_pmd(pmd_t orig, pmd_t *pmdp, अचिन्हित दीर्घ addr,
				 अचिन्हित दीर्घ end, अचिन्हित पूर्णांक flags,
				 काष्ठा page **pages, पूर्णांक *nr)
अणु
	अचिन्हित दीर्घ fault_pfn;
	पूर्णांक nr_start = *nr;

	fault_pfn = pmd_pfn(orig) + ((addr & ~PMD_MASK) >> PAGE_SHIFT);
	अगर (!__gup_device_huge(fault_pfn, addr, end, flags, pages, nr))
		वापस 0;

	अगर (unlikely(pmd_val(orig) != pmd_val(*pmdp))) अणु
		unकरो_dev_pagemap(nr, nr_start, flags, pages);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक __gup_device_huge_pud(pud_t orig, pud_t *pudp, अचिन्हित दीर्घ addr,
				 अचिन्हित दीर्घ end, अचिन्हित पूर्णांक flags,
				 काष्ठा page **pages, पूर्णांक *nr)
अणु
	अचिन्हित दीर्घ fault_pfn;
	पूर्णांक nr_start = *nr;

	fault_pfn = pud_pfn(orig) + ((addr & ~PUD_MASK) >> PAGE_SHIFT);
	अगर (!__gup_device_huge(fault_pfn, addr, end, flags, pages, nr))
		वापस 0;

	अगर (unlikely(pud_val(orig) != pud_val(*pudp))) अणु
		unकरो_dev_pagemap(nr, nr_start, flags, pages);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण
#अन्यथा
अटल पूर्णांक __gup_device_huge_pmd(pmd_t orig, pmd_t *pmdp, अचिन्हित दीर्घ addr,
				 अचिन्हित दीर्घ end, अचिन्हित पूर्णांक flags,
				 काष्ठा page **pages, पूर्णांक *nr)
अणु
	BUILD_BUG();
	वापस 0;
पूर्ण

अटल पूर्णांक __gup_device_huge_pud(pud_t pud, pud_t *pudp, अचिन्हित दीर्घ addr,
				 अचिन्हित दीर्घ end, अचिन्हित पूर्णांक flags,
				 काष्ठा page **pages, पूर्णांक *nr)
अणु
	BUILD_BUG();
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक record_subpages(काष्ठा page *page, अचिन्हित दीर्घ addr,
			   अचिन्हित दीर्घ end, काष्ठा page **pages)
अणु
	पूर्णांक nr;

	क्रम (nr = 0; addr != end; addr += PAGE_SIZE)
		pages[nr++] = page++;

	वापस nr;
पूर्ण

#अगर_घोषित CONFIG_ARCH_HAS_HUGEPD
अटल अचिन्हित दीर्घ hugepte_addr_end(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				      अचिन्हित दीर्घ sz)
अणु
	अचिन्हित दीर्घ __boundary = (addr + sz) & ~(sz-1);
	वापस (__boundary - 1 < end - 1) ? __boundary : end;
पूर्ण

अटल पूर्णांक gup_hugepte(pte_t *ptep, अचिन्हित दीर्घ sz, अचिन्हित दीर्घ addr,
		       अचिन्हित दीर्घ end, अचिन्हित पूर्णांक flags,
		       काष्ठा page **pages, पूर्णांक *nr)
अणु
	अचिन्हित दीर्घ pte_end;
	काष्ठा page *head, *page;
	pte_t pte;
	पूर्णांक refs;

	pte_end = (addr + sz) & ~(sz-1);
	अगर (pte_end < end)
		end = pte_end;

	pte = huge_ptep_get(ptep);

	अगर (!pte_access_permitted(pte, flags & FOLL_WRITE))
		वापस 0;

	/* hugepages are never "special" */
	VM_BUG_ON(!pfn_valid(pte_pfn(pte)));

	head = pte_page(pte);
	page = head + ((addr & (sz-1)) >> PAGE_SHIFT);
	refs = record_subpages(page, addr, end, pages + *nr);

	head = try_grab_compound_head(head, refs, flags);
	अगर (!head)
		वापस 0;

	अगर (unlikely(pte_val(pte) != pte_val(*ptep))) अणु
		put_compound_head(head, refs, flags);
		वापस 0;
	पूर्ण

	*nr += refs;
	SetPageReferenced(head);
	वापस 1;
पूर्ण

अटल पूर्णांक gup_huge_pd(hugepd_t hugepd, अचिन्हित दीर्घ addr,
		अचिन्हित पूर्णांक pdshअगरt, अचिन्हित दीर्घ end, अचिन्हित पूर्णांक flags,
		काष्ठा page **pages, पूर्णांक *nr)
अणु
	pte_t *ptep;
	अचिन्हित दीर्घ sz = 1UL << hugepd_shअगरt(hugepd);
	अचिन्हित दीर्घ next;

	ptep = hugepte_offset(hugepd, addr, pdshअगरt);
	करो अणु
		next = hugepte_addr_end(addr, end, sz);
		अगर (!gup_hugepte(ptep, sz, addr, end, flags, pages, nr))
			वापस 0;
	पूर्ण जबतक (ptep++, addr = next, addr != end);

	वापस 1;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक gup_huge_pd(hugepd_t hugepd, अचिन्हित दीर्घ addr,
		अचिन्हित पूर्णांक pdshअगरt, अचिन्हित दीर्घ end, अचिन्हित पूर्णांक flags,
		काष्ठा page **pages, पूर्णांक *nr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HAS_HUGEPD */

अटल पूर्णांक gup_huge_pmd(pmd_t orig, pmd_t *pmdp, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ end, अचिन्हित पूर्णांक flags,
			काष्ठा page **pages, पूर्णांक *nr)
अणु
	काष्ठा page *head, *page;
	पूर्णांक refs;

	अगर (!pmd_access_permitted(orig, flags & FOLL_WRITE))
		वापस 0;

	अगर (pmd_devmap(orig)) अणु
		अगर (unlikely(flags & FOLL_LONGTERM))
			वापस 0;
		वापस __gup_device_huge_pmd(orig, pmdp, addr, end, flags,
					     pages, nr);
	पूर्ण

	page = pmd_page(orig) + ((addr & ~PMD_MASK) >> PAGE_SHIFT);
	refs = record_subpages(page, addr, end, pages + *nr);

	head = try_grab_compound_head(pmd_page(orig), refs, flags);
	अगर (!head)
		वापस 0;

	अगर (unlikely(pmd_val(orig) != pmd_val(*pmdp))) अणु
		put_compound_head(head, refs, flags);
		वापस 0;
	पूर्ण

	*nr += refs;
	SetPageReferenced(head);
	वापस 1;
पूर्ण

अटल पूर्णांक gup_huge_pud(pud_t orig, pud_t *pudp, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ end, अचिन्हित पूर्णांक flags,
			काष्ठा page **pages, पूर्णांक *nr)
अणु
	काष्ठा page *head, *page;
	पूर्णांक refs;

	अगर (!pud_access_permitted(orig, flags & FOLL_WRITE))
		वापस 0;

	अगर (pud_devmap(orig)) अणु
		अगर (unlikely(flags & FOLL_LONGTERM))
			वापस 0;
		वापस __gup_device_huge_pud(orig, pudp, addr, end, flags,
					     pages, nr);
	पूर्ण

	page = pud_page(orig) + ((addr & ~PUD_MASK) >> PAGE_SHIFT);
	refs = record_subpages(page, addr, end, pages + *nr);

	head = try_grab_compound_head(pud_page(orig), refs, flags);
	अगर (!head)
		वापस 0;

	अगर (unlikely(pud_val(orig) != pud_val(*pudp))) अणु
		put_compound_head(head, refs, flags);
		वापस 0;
	पूर्ण

	*nr += refs;
	SetPageReferenced(head);
	वापस 1;
पूर्ण

अटल पूर्णांक gup_huge_pgd(pgd_t orig, pgd_t *pgdp, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ end, अचिन्हित पूर्णांक flags,
			काष्ठा page **pages, पूर्णांक *nr)
अणु
	पूर्णांक refs;
	काष्ठा page *head, *page;

	अगर (!pgd_access_permitted(orig, flags & FOLL_WRITE))
		वापस 0;

	BUILD_BUG_ON(pgd_devmap(orig));

	page = pgd_page(orig) + ((addr & ~PGसूची_MASK) >> PAGE_SHIFT);
	refs = record_subpages(page, addr, end, pages + *nr);

	head = try_grab_compound_head(pgd_page(orig), refs, flags);
	अगर (!head)
		वापस 0;

	अगर (unlikely(pgd_val(orig) != pgd_val(*pgdp))) अणु
		put_compound_head(head, refs, flags);
		वापस 0;
	पूर्ण

	*nr += refs;
	SetPageReferenced(head);
	वापस 1;
पूर्ण

अटल पूर्णांक gup_pmd_range(pud_t *pudp, pud_t pud, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		अचिन्हित पूर्णांक flags, काष्ठा page **pages, पूर्णांक *nr)
अणु
	अचिन्हित दीर्घ next;
	pmd_t *pmdp;

	pmdp = pmd_offset_lockless(pudp, pud, addr);
	करो अणु
		pmd_t pmd = READ_ONCE(*pmdp);

		next = pmd_addr_end(addr, end);
		अगर (!pmd_present(pmd))
			वापस 0;

		अगर (unlikely(pmd_trans_huge(pmd) || pmd_huge(pmd) ||
			     pmd_devmap(pmd))) अणु
			/*
			 * NUMA hपूर्णांकing faults need to be handled in the GUP
			 * slowpath क्रम accounting purposes and so that they
			 * can be serialised against THP migration.
			 */
			अगर (pmd_protnone(pmd))
				वापस 0;

			अगर (!gup_huge_pmd(pmd, pmdp, addr, next, flags,
				pages, nr))
				वापस 0;

		पूर्ण अन्यथा अगर (unlikely(is_hugepd(__hugepd(pmd_val(pmd))))) अणु
			/*
			 * architecture have dअगरferent क्रमmat क्रम hugetlbfs
			 * pmd क्रमmat and THP pmd क्रमmat
			 */
			अगर (!gup_huge_pd(__hugepd(pmd_val(pmd)), addr,
					 PMD_SHIFT, next, flags, pages, nr))
				वापस 0;
		पूर्ण अन्यथा अगर (!gup_pte_range(pmd, addr, next, flags, pages, nr))
			वापस 0;
	पूर्ण जबतक (pmdp++, addr = next, addr != end);

	वापस 1;
पूर्ण

अटल पूर्णांक gup_pud_range(p4d_t *p4dp, p4d_t p4d, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			 अचिन्हित पूर्णांक flags, काष्ठा page **pages, पूर्णांक *nr)
अणु
	अचिन्हित दीर्घ next;
	pud_t *pudp;

	pudp = pud_offset_lockless(p4dp, p4d, addr);
	करो अणु
		pud_t pud = READ_ONCE(*pudp);

		next = pud_addr_end(addr, end);
		अगर (unlikely(!pud_present(pud)))
			वापस 0;
		अगर (unlikely(pud_huge(pud))) अणु
			अगर (!gup_huge_pud(pud, pudp, addr, next, flags,
					  pages, nr))
				वापस 0;
		पूर्ण अन्यथा अगर (unlikely(is_hugepd(__hugepd(pud_val(pud))))) अणु
			अगर (!gup_huge_pd(__hugepd(pud_val(pud)), addr,
					 PUD_SHIFT, next, flags, pages, nr))
				वापस 0;
		पूर्ण अन्यथा अगर (!gup_pmd_range(pudp, pud, addr, next, flags, pages, nr))
			वापस 0;
	पूर्ण जबतक (pudp++, addr = next, addr != end);

	वापस 1;
पूर्ण

अटल पूर्णांक gup_p4d_range(pgd_t *pgdp, pgd_t pgd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			 अचिन्हित पूर्णांक flags, काष्ठा page **pages, पूर्णांक *nr)
अणु
	अचिन्हित दीर्घ next;
	p4d_t *p4dp;

	p4dp = p4d_offset_lockless(pgdp, pgd, addr);
	करो अणु
		p4d_t p4d = READ_ONCE(*p4dp);

		next = p4d_addr_end(addr, end);
		अगर (p4d_none(p4d))
			वापस 0;
		BUILD_BUG_ON(p4d_huge(p4d));
		अगर (unlikely(is_hugepd(__hugepd(p4d_val(p4d))))) अणु
			अगर (!gup_huge_pd(__hugepd(p4d_val(p4d)), addr,
					 P4D_SHIFT, next, flags, pages, nr))
				वापस 0;
		पूर्ण अन्यथा अगर (!gup_pud_range(p4dp, p4d, addr, next, flags, pages, nr))
			वापस 0;
	पूर्ण जबतक (p4dp++, addr = next, addr != end);

	वापस 1;
पूर्ण

अटल व्योम gup_pgd_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		अचिन्हित पूर्णांक flags, काष्ठा page **pages, पूर्णांक *nr)
अणु
	अचिन्हित दीर्घ next;
	pgd_t *pgdp;

	pgdp = pgd_offset(current->mm, addr);
	करो अणु
		pgd_t pgd = READ_ONCE(*pgdp);

		next = pgd_addr_end(addr, end);
		अगर (pgd_none(pgd))
			वापस;
		अगर (unlikely(pgd_huge(pgd))) अणु
			अगर (!gup_huge_pgd(pgd, pgdp, addr, next, flags,
					  pages, nr))
				वापस;
		पूर्ण अन्यथा अगर (unlikely(is_hugepd(__hugepd(pgd_val(pgd))))) अणु
			अगर (!gup_huge_pd(__hugepd(pgd_val(pgd)), addr,
					 PGसूची_SHIFT, next, flags, pages, nr))
				वापस;
		पूर्ण अन्यथा अगर (!gup_p4d_range(pgdp, pgd, addr, next, flags, pages, nr))
			वापस;
	पूर्ण जबतक (pgdp++, addr = next, addr != end);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम gup_pgd_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		अचिन्हित पूर्णांक flags, काष्ठा page **pages, पूर्णांक *nr)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_FAST_GUP */

#अगर_अघोषित gup_fast_permitted
/*
 * Check अगर it's allowed to use get_user_pages_fast_only() क्रम the range, or
 * we need to fall back to the slow version:
 */
अटल bool gup_fast_permitted(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __gup_दीर्घterm_unlocked(अचिन्हित दीर्घ start, पूर्णांक nr_pages,
				   अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages)
अणु
	पूर्णांक ret;

	/*
	 * FIXME: FOLL_LONGTERM करोes not work with
	 * get_user_pages_unlocked() (see comments in that function)
	 */
	अगर (gup_flags & FOLL_LONGTERM) अणु
		mmap_पढ़ो_lock(current->mm);
		ret = __gup_दीर्घterm_locked(current->mm,
					    start, nr_pages,
					    pages, शून्य, gup_flags);
		mmap_पढ़ो_unlock(current->mm);
	पूर्ण अन्यथा अणु
		ret = get_user_pages_unlocked(start, nr_pages,
					      pages, gup_flags);
	पूर्ण

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ lockless_pages_from_mm(अचिन्हित दीर्घ start,
					    अचिन्हित दीर्घ end,
					    अचिन्हित पूर्णांक gup_flags,
					    काष्ठा page **pages)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक nr_pinned = 0;
	अचिन्हित seq;

	अगर (!IS_ENABLED(CONFIG_HAVE_FAST_GUP) ||
	    !gup_fast_permitted(start, end))
		वापस 0;

	अगर (gup_flags & FOLL_PIN) अणु
		seq = raw_पढ़ो_seqcount(&current->mm->ग_लिखो_protect_seq);
		अगर (seq & 1)
			वापस 0;
	पूर्ण

	/*
	 * Disable पूर्णांकerrupts. The nested क्रमm is used, in order to allow full,
	 * general purpose use of this routine.
	 *
	 * With पूर्णांकerrupts disabled, we block page table pages from being मुक्तd
	 * from under us. See काष्ठा mmu_table_batch comments in
	 * include/यंत्र-generic/tlb.h क्रम more details.
	 *
	 * We करो not aकरोpt an rcu_पढ़ो_lock() here as we also want to block IPIs
	 * that come from THPs splitting.
	 */
	local_irq_save(flags);
	gup_pgd_range(start, end, gup_flags, pages, &nr_pinned);
	local_irq_restore(flags);

	/*
	 * When pinning pages क्रम DMA there could be a concurrent ग_लिखो protect
	 * from विभाजन() via copy_page_range(), in this हाल always fail fast GUP.
	 */
	अगर (gup_flags & FOLL_PIN) अणु
		अगर (पढ़ो_seqcount_retry(&current->mm->ग_लिखो_protect_seq, seq)) अणु
			unpin_user_pages(pages, nr_pinned);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस nr_pinned;
पूर्ण

अटल पूर्णांक पूर्णांकernal_get_user_pages_fast(अचिन्हित दीर्घ start,
					अचिन्हित दीर्घ nr_pages,
					अचिन्हित पूर्णांक gup_flags,
					काष्ठा page **pages)
अणु
	अचिन्हित दीर्घ len, end;
	अचिन्हित दीर्घ nr_pinned;
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(gup_flags & ~(FOLL_WRITE | FOLL_LONGTERM |
				       FOLL_FORCE | FOLL_PIN | FOLL_GET |
				       FOLL_FAST_ONLY)))
		वापस -EINVAL;

	अगर (gup_flags & FOLL_PIN)
		atomic_set(&current->mm->has_pinned, 1);

	अगर (!(gup_flags & FOLL_FAST_ONLY))
		might_lock_पढ़ो(&current->mm->mmap_lock);

	start = untagged_addr(start) & PAGE_MASK;
	len = nr_pages << PAGE_SHIFT;
	अगर (check_add_overflow(start, len, &end))
		वापस 0;
	अगर (unlikely(!access_ok((व्योम __user *)start, len)))
		वापस -EFAULT;

	nr_pinned = lockless_pages_from_mm(start, end, gup_flags, pages);
	अगर (nr_pinned == nr_pages || gup_flags & FOLL_FAST_ONLY)
		वापस nr_pinned;

	/* Slow path: try to get the reमुख्यing pages with get_user_pages */
	start += nr_pinned << PAGE_SHIFT;
	pages += nr_pinned;
	ret = __gup_दीर्घterm_unlocked(start, nr_pages - nr_pinned, gup_flags,
				      pages);
	अगर (ret < 0) अणु
		/*
		 * The caller has to unpin the pages we alपढ़ोy pinned so
		 * वापसing -त्रुटि_सं is not an option
		 */
		अगर (nr_pinned)
			वापस nr_pinned;
		वापस ret;
	पूर्ण
	वापस ret + nr_pinned;
पूर्ण

/**
 * get_user_pages_fast_only() - pin user pages in memory
 * @start:      starting user address
 * @nr_pages:   number of pages from start to pin
 * @gup_flags:  flags modअगरying pin behaviour
 * @pages:      array that receives poपूर्णांकers to the pages pinned.
 *              Should be at least nr_pages दीर्घ.
 *
 * Like get_user_pages_fast() except it's IRQ-safe in that it won't fall back to
 * the regular GUP.
 * Note a dअगरference with get_user_pages_fast: this always वापसs the
 * number of pages pinned, 0 अगर no pages were pinned.
 *
 * If the architecture करोes not support this function, simply वापस with no
 * pages pinned.
 *
 * Careful, careful! COW अवरोधing can go either way, so a non-ग_लिखो
 * access can get ambiguous page results. If you call this function without
 * 'write' set, you'd better be sure that you're ok with that ambiguity.
 */
पूर्णांक get_user_pages_fast_only(अचिन्हित दीर्घ start, पूर्णांक nr_pages,
			     अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages)
अणु
	पूर्णांक nr_pinned;
	/*
	 * Internally (within mm/gup.c), gup fast variants must set FOLL_GET,
	 * because gup fast is always a "pin with a +1 page refcount" request.
	 *
	 * FOLL_FAST_ONLY is required in order to match the API description of
	 * this routine: no fall back to regular ("slow") GUP.
	 */
	gup_flags |= FOLL_GET | FOLL_FAST_ONLY;

	nr_pinned = पूर्णांकernal_get_user_pages_fast(start, nr_pages, gup_flags,
						 pages);

	/*
	 * As specअगरied in the API description above, this routine is not
	 * allowed to वापस negative values. However, the common core
	 * routine पूर्णांकernal_get_user_pages_fast() *can* वापस -त्रुटि_सं.
	 * Thereक्रमe, correct क्रम that here:
	 */
	अगर (nr_pinned < 0)
		nr_pinned = 0;

	वापस nr_pinned;
पूर्ण
EXPORT_SYMBOL_GPL(get_user_pages_fast_only);

/**
 * get_user_pages_fast() - pin user pages in memory
 * @start:      starting user address
 * @nr_pages:   number of pages from start to pin
 * @gup_flags:  flags modअगरying pin behaviour
 * @pages:      array that receives poपूर्णांकers to the pages pinned.
 *              Should be at least nr_pages दीर्घ.
 *
 * Attempt to pin user pages in memory without taking mm->mmap_lock.
 * If not successful, it will fall back to taking the lock and
 * calling get_user_pages().
 *
 * Returns number of pages pinned. This may be fewer than the number requested.
 * If nr_pages is 0 or negative, वापसs 0. If no pages were pinned, वापसs
 * -त्रुटि_सं.
 */
पूर्णांक get_user_pages_fast(अचिन्हित दीर्घ start, पूर्णांक nr_pages,
			अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages)
अणु
	अगर (!is_valid_gup_flags(gup_flags))
		वापस -EINVAL;

	/*
	 * The caller may or may not have explicitly set FOLL_GET; either way is
	 * OK. However, पूर्णांकernally (within mm/gup.c), gup fast variants must set
	 * FOLL_GET, because gup fast is always a "pin with a +1 page refcount"
	 * request.
	 */
	gup_flags |= FOLL_GET;
	वापस पूर्णांकernal_get_user_pages_fast(start, nr_pages, gup_flags, pages);
पूर्ण
EXPORT_SYMBOL_GPL(get_user_pages_fast);

/**
 * pin_user_pages_fast() - pin user pages in memory without taking locks
 *
 * @start:      starting user address
 * @nr_pages:   number of pages from start to pin
 * @gup_flags:  flags modअगरying pin behaviour
 * @pages:      array that receives poपूर्णांकers to the pages pinned.
 *              Should be at least nr_pages दीर्घ.
 *
 * Nearly the same as get_user_pages_fast(), except that FOLL_PIN is set. See
 * get_user_pages_fast() क्रम करोcumentation on the function arguments, because
 * the arguments here are identical.
 *
 * FOLL_PIN means that the pages must be released via unpin_user_page(). Please
 * see Documentation/core-api/pin_user_pages.rst क्रम further details.
 */
पूर्णांक pin_user_pages_fast(अचिन्हित दीर्घ start, पूर्णांक nr_pages,
			अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages)
अणु
	/* FOLL_GET and FOLL_PIN are mutually exclusive. */
	अगर (WARN_ON_ONCE(gup_flags & FOLL_GET))
		वापस -EINVAL;

	gup_flags |= FOLL_PIN;
	वापस पूर्णांकernal_get_user_pages_fast(start, nr_pages, gup_flags, pages);
पूर्ण
EXPORT_SYMBOL_GPL(pin_user_pages_fast);

/*
 * This is the FOLL_PIN equivalent of get_user_pages_fast_only(). Behavior
 * is the same, except that this one sets FOLL_PIN instead of FOLL_GET.
 *
 * The API rules are the same, too: no negative values may be वापसed.
 */
पूर्णांक pin_user_pages_fast_only(अचिन्हित दीर्घ start, पूर्णांक nr_pages,
			     अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages)
अणु
	पूर्णांक nr_pinned;

	/*
	 * FOLL_GET and FOLL_PIN are mutually exclusive. Note that the API
	 * rules require वापसing 0, rather than -त्रुटि_सं:
	 */
	अगर (WARN_ON_ONCE(gup_flags & FOLL_GET))
		वापस 0;
	/*
	 * FOLL_FAST_ONLY is required in order to match the API description of
	 * this routine: no fall back to regular ("slow") GUP.
	 */
	gup_flags |= (FOLL_PIN | FOLL_FAST_ONLY);
	nr_pinned = पूर्णांकernal_get_user_pages_fast(start, nr_pages, gup_flags,
						 pages);
	/*
	 * This routine is not allowed to वापस negative values. However,
	 * पूर्णांकernal_get_user_pages_fast() *can* वापस -त्रुटि_सं. Thereक्रमe,
	 * correct क्रम that here:
	 */
	अगर (nr_pinned < 0)
		nr_pinned = 0;

	वापस nr_pinned;
पूर्ण
EXPORT_SYMBOL_GPL(pin_user_pages_fast_only);

/**
 * pin_user_pages_remote() - pin pages of a remote process
 *
 * @mm:		mm_काष्ठा of target mm
 * @start:	starting user address
 * @nr_pages:	number of pages from start to pin
 * @gup_flags:	flags modअगरying lookup behaviour
 * @pages:	array that receives poपूर्णांकers to the pages pinned.
 *		Should be at least nr_pages दीर्घ. Or शून्य, अगर caller
 *		only पूर्णांकends to ensure the pages are faulted in.
 * @vmas:	array of poपूर्णांकers to vmas corresponding to each page.
 *		Or शून्य अगर the caller करोes not require them.
 * @locked:	poपूर्णांकer to lock flag indicating whether lock is held and
 *		subsequently whether VM_FAULT_RETRY functionality can be
 *		utilised. Lock must initially be held.
 *
 * Nearly the same as get_user_pages_remote(), except that FOLL_PIN is set. See
 * get_user_pages_remote() क्रम करोcumentation on the function arguments, because
 * the arguments here are identical.
 *
 * FOLL_PIN means that the pages must be released via unpin_user_page(). Please
 * see Documentation/core-api/pin_user_pages.rst क्रम details.
 */
दीर्घ pin_user_pages_remote(काष्ठा mm_काष्ठा *mm,
			   अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
			   अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages,
			   काष्ठा vm_area_काष्ठा **vmas, पूर्णांक *locked)
अणु
	/* FOLL_GET and FOLL_PIN are mutually exclusive. */
	अगर (WARN_ON_ONCE(gup_flags & FOLL_GET))
		वापस -EINVAL;

	gup_flags |= FOLL_PIN;
	वापस __get_user_pages_remote(mm, start, nr_pages, gup_flags,
				       pages, vmas, locked);
पूर्ण
EXPORT_SYMBOL(pin_user_pages_remote);

/**
 * pin_user_pages() - pin user pages in memory क्रम use by other devices
 *
 * @start:	starting user address
 * @nr_pages:	number of pages from start to pin
 * @gup_flags:	flags modअगरying lookup behaviour
 * @pages:	array that receives poपूर्णांकers to the pages pinned.
 *		Should be at least nr_pages दीर्घ. Or शून्य, अगर caller
 *		only पूर्णांकends to ensure the pages are faulted in.
 * @vmas:	array of poपूर्णांकers to vmas corresponding to each page.
 *		Or शून्य अगर the caller करोes not require them.
 *
 * Nearly the same as get_user_pages(), except that FOLL_TOUCH is not set, and
 * FOLL_PIN is set.
 *
 * FOLL_PIN means that the pages must be released via unpin_user_page(). Please
 * see Documentation/core-api/pin_user_pages.rst क्रम details.
 */
दीर्घ pin_user_pages(अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
		    अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages,
		    काष्ठा vm_area_काष्ठा **vmas)
अणु
	/* FOLL_GET and FOLL_PIN are mutually exclusive. */
	अगर (WARN_ON_ONCE(gup_flags & FOLL_GET))
		वापस -EINVAL;

	gup_flags |= FOLL_PIN;
	वापस __gup_दीर्घterm_locked(current->mm, start, nr_pages,
				     pages, vmas, gup_flags);
पूर्ण
EXPORT_SYMBOL(pin_user_pages);

/*
 * pin_user_pages_unlocked() is the FOLL_PIN variant of
 * get_user_pages_unlocked(). Behavior is the same, except that this one sets
 * FOLL_PIN and rejects FOLL_GET.
 */
दीर्घ pin_user_pages_unlocked(अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
			     काष्ठा page **pages, अचिन्हित पूर्णांक gup_flags)
अणु
	/* FOLL_GET and FOLL_PIN are mutually exclusive. */
	अगर (WARN_ON_ONCE(gup_flags & FOLL_GET))
		वापस -EINVAL;

	gup_flags |= FOLL_PIN;
	वापस get_user_pages_unlocked(start, nr_pages, pages, gup_flags);
पूर्ण
EXPORT_SYMBOL(pin_user_pages_unlocked);

/*
 * pin_user_pages_locked() is the FOLL_PIN variant of get_user_pages_locked().
 * Behavior is the same, except that this one sets FOLL_PIN and rejects
 * FOLL_GET.
 */
दीर्घ pin_user_pages_locked(अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
			   अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages,
			   पूर्णांक *locked)
अणु
	/*
	 * FIXME: Current FOLL_LONGTERM behavior is incompatible with
	 * FAULT_FLAG_ALLOW_RETRY because of the FS DAX check requirement on
	 * vmas.  As there are no users of this flag in this call we simply
	 * disallow this option क्रम now.
	 */
	अगर (WARN_ON_ONCE(gup_flags & FOLL_LONGTERM))
		वापस -EINVAL;

	/* FOLL_GET and FOLL_PIN are mutually exclusive. */
	अगर (WARN_ON_ONCE(gup_flags & FOLL_GET))
		वापस -EINVAL;

	gup_flags |= FOLL_PIN;
	वापस __get_user_pages_locked(current->mm, start, nr_pages,
				       pages, शून्य, locked,
				       gup_flags | FOLL_TOUCH);
पूर्ण
EXPORT_SYMBOL(pin_user_pages_locked);
