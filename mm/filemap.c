<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	linux/mm/filemap.c
 *
 * Copyright (C) 1994-1999  Linus Torvalds
 */

/*
 * This file handles the generic file mmap semantics used by
 * most "normal" fileप्रणालीs (but you करोn't /have/ to use this:
 * the NFS fileप्रणाली used to करो this dअगरferently, क्रम example)
 */
#समावेश <linux/export.h>
#समावेश <linux/compiler.h>
#समावेश <linux/dax.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/capability.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/gfp.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/mman.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/file.h>
#समावेश <linux/uपन.स>
#समावेश <linux/error-injection.h>
#समावेश <linux/hash.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/security.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/cleancache.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/rmap.h>
#समावेश <linux/delayacct.h>
#समावेश <linux/psi.h>
#समावेश <linux/ramfs.h>
#समावेश <linux/page_idle.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlbflush.h>
#समावेश "internal.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/filemap.h>

/*
 * FIXME: हटाओ all knowledge of the buffer layer from the core VM
 */
#समावेश <linux/buffer_head.h> /* क्रम try_to_मुक्त_buffers */

#समावेश <यंत्र/mman.h>

/*
 * Shared mappings implemented 30.11.1994. It's not fully working yet,
 * though.
 *
 * Shared mappings now work. 15.8.1995  Bruno.
 *
 * finished 'unifying' the page and buffer cache and SMP-thपढ़ोed the
 * page-cache, 21.05.1999, Ingo Molnar <mingo@redhat.com>
 *
 * SMP-thपढ़ोed pagemap-LRU 1999, Andrea Arcangeli <andrea@suse.de>
 */

/*
 * Lock ordering:
 *
 *  ->i_mmap_rwsem		(truncate_pagecache)
 *    ->निजी_lock		(__मुक्त_pte->__set_page_dirty_buffers)
 *      ->swap_lock		(exclusive_swap_page, others)
 *        ->i_pages lock
 *
 *  ->i_mutex
 *    ->i_mmap_rwsem		(truncate->unmap_mapping_range)
 *
 *  ->mmap_lock
 *    ->i_mmap_rwsem
 *      ->page_table_lock or pte_lock	(various, मुख्यly in memory.c)
 *        ->i_pages lock	(arch-dependent flush_dcache_mmap_lock)
 *
 *  ->mmap_lock
 *    ->lock_page		(access_process_vm)
 *
 *  ->i_mutex			(generic_perक्रमm_ग_लिखो)
 *    ->mmap_lock		(fault_in_pages_पढ़ोable->करो_page_fault)
 *
 *  bdi->wb.list_lock
 *    sb_lock			(fs/fs-ग_लिखोback.c)
 *    ->i_pages lock		(__sync_single_inode)
 *
 *  ->i_mmap_rwsem
 *    ->anon_vma.lock		(vma_adjust)
 *
 *  ->anon_vma.lock
 *    ->page_table_lock or pte_lock	(anon_vma_prepare and various)
 *
 *  ->page_table_lock or pte_lock
 *    ->swap_lock		(try_to_unmap_one)
 *    ->निजी_lock		(try_to_unmap_one)
 *    ->i_pages lock		(try_to_unmap_one)
 *    ->lruvec->lru_lock	(follow_page->mark_page_accessed)
 *    ->lruvec->lru_lock	(check_pte_range->isolate_lru_page)
 *    ->निजी_lock		(page_हटाओ_rmap->set_page_dirty)
 *    ->i_pages lock		(page_हटाओ_rmap->set_page_dirty)
 *    bdi.wb->list_lock		(page_हटाओ_rmap->set_page_dirty)
 *    ->inode->i_lock		(page_हटाओ_rmap->set_page_dirty)
 *    ->memcg->move_lock	(page_हटाओ_rmap->lock_page_memcg)
 *    bdi.wb->list_lock		(zap_pte_range->set_page_dirty)
 *    ->inode->i_lock		(zap_pte_range->set_page_dirty)
 *    ->निजी_lock		(zap_pte_range->__set_page_dirty_buffers)
 *
 * ->i_mmap_rwsem
 *   ->tasklist_lock            (memory_failure, collect_procs_ao)
 */

अटल व्योम page_cache_delete(काष्ठा address_space *mapping,
				   काष्ठा page *page, व्योम *shaकरोw)
अणु
	XA_STATE(xas, &mapping->i_pages, page->index);
	अचिन्हित पूर्णांक nr = 1;

	mapping_set_update(&xas, mapping);

	/* hugetlb pages are represented by a single entry in the xarray */
	अगर (!PageHuge(page)) अणु
		xas_set_order(&xas, page->index, compound_order(page));
		nr = compound_nr(page);
	पूर्ण

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(PageTail(page), page);
	VM_BUG_ON_PAGE(nr != 1 && shaकरोw, page);

	xas_store(&xas, shaकरोw);
	xas_init_marks(&xas);

	page->mapping = शून्य;
	/* Leave page->index set: truncation lookup relies upon it */
	mapping->nrpages -= nr;
पूर्ण

अटल व्योम unaccount_page_cache_page(काष्ठा address_space *mapping,
				      काष्ठा page *page)
अणु
	पूर्णांक nr;

	/*
	 * अगर we're uptodate, flush out पूर्णांकo the cleancache, otherwise
	 * invalidate any existing cleancache entries.  We can't leave
	 * stale data around in the cleancache once our page is gone
	 */
	अगर (PageUptodate(page) && PageMappedToDisk(page))
		cleancache_put_page(page);
	अन्यथा
		cleancache_invalidate_page(mapping, page);

	VM_BUG_ON_PAGE(PageTail(page), page);
	VM_BUG_ON_PAGE(page_mapped(page), page);
	अगर (!IS_ENABLED(CONFIG_DEBUG_VM) && unlikely(page_mapped(page))) अणु
		पूर्णांक mapcount;

		pr_alert("BUG: Bad page cache in process %s  pfn:%05lx\n",
			 current->comm, page_to_pfn(page));
		dump_page(page, "still mapped when deleted");
		dump_stack();
		add_taपूर्णांक(TAINT_BAD_PAGE, LOCKDEP_NOW_UNRELIABLE);

		mapcount = page_mapcount(page);
		अगर (mapping_निकासing(mapping) &&
		    page_count(page) >= mapcount + 2) अणु
			/*
			 * All vmas have alपढ़ोy been torn करोwn, so it's
			 * a good bet that actually the page is unmapped,
			 * and we'd prefer not to leak it: if we're wrong,
			 * some other bad page check should catch it later.
			 */
			page_mapcount_reset(page);
			page_ref_sub(page, mapcount);
		पूर्ण
	पूर्ण

	/* hugetlb pages करो not participate in page cache accounting. */
	अगर (PageHuge(page))
		वापस;

	nr = thp_nr_pages(page);

	__mod_lruvec_page_state(page, NR_खाता_PAGES, -nr);
	अगर (PageSwapBacked(page)) अणु
		__mod_lruvec_page_state(page, NR_SHMEM, -nr);
		अगर (PageTransHuge(page))
			__mod_lruvec_page_state(page, NR_SHMEM_THPS, -nr);
	पूर्ण अन्यथा अगर (PageTransHuge(page)) अणु
		__mod_lruvec_page_state(page, NR_खाता_THPS, -nr);
		filemap_nr_thps_dec(mapping);
	पूर्ण

	/*
	 * At this poपूर्णांक page must be either written or cleaned by
	 * truncate.  Dirty page here संकेतs a bug and loss of
	 * unwritten data.
	 *
	 * This fixes dirty accounting after removing the page entirely
	 * but leaves PageDirty set: it has no effect क्रम truncated
	 * page and anyway will be cleared beक्रमe वापसing page पूर्णांकo
	 * buddy allocator.
	 */
	अगर (WARN_ON_ONCE(PageDirty(page)))
		account_page_cleaned(page, mapping, inode_to_wb(mapping->host));
पूर्ण

/*
 * Delete a page from the page cache and मुक्त it. Caller has to make
 * sure the page is locked and that nobody अन्यथा uses it - or that usage
 * is safe.  The caller must hold the i_pages lock.
 */
व्योम __delete_from_page_cache(काष्ठा page *page, व्योम *shaकरोw)
अणु
	काष्ठा address_space *mapping = page->mapping;

	trace_mm_filemap_delete_from_page_cache(page);

	unaccount_page_cache_page(mapping, page);
	page_cache_delete(mapping, page, shaकरोw);
पूर्ण

अटल व्योम page_cache_मुक्त_page(काष्ठा address_space *mapping,
				काष्ठा page *page)
अणु
	व्योम (*मुक्तpage)(काष्ठा page *);

	मुक्तpage = mapping->a_ops->मुक्तpage;
	अगर (मुक्तpage)
		मुक्तpage(page);

	अगर (PageTransHuge(page) && !PageHuge(page)) अणु
		page_ref_sub(page, thp_nr_pages(page));
		VM_BUG_ON_PAGE(page_count(page) <= 0, page);
	पूर्ण अन्यथा अणु
		put_page(page);
	पूर्ण
पूर्ण

/**
 * delete_from_page_cache - delete page from page cache
 * @page: the page which the kernel is trying to हटाओ from page cache
 *
 * This must be called only on pages that have been verअगरied to be in the page
 * cache and locked.  It will never put the page पूर्णांकo the मुक्त list, the caller
 * has a reference on the page.
 */
व्योम delete_from_page_cache(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page_mapping(page);
	अचिन्हित दीर्घ flags;

	BUG_ON(!PageLocked(page));
	xa_lock_irqsave(&mapping->i_pages, flags);
	__delete_from_page_cache(page, शून्य);
	xa_unlock_irqrestore(&mapping->i_pages, flags);

	page_cache_मुक्त_page(mapping, page);
पूर्ण
EXPORT_SYMBOL(delete_from_page_cache);

/*
 * page_cache_delete_batch - delete several pages from page cache
 * @mapping: the mapping to which pages beदीर्घ
 * @pvec: pagevec with pages to delete
 *
 * The function walks over mapping->i_pages and हटाओs pages passed in @pvec
 * from the mapping. The function expects @pvec to be sorted by page index
 * and is optimised क्रम it to be dense.
 * It tolerates holes in @pvec (mapping entries at those indices are not
 * modअगरied). The function expects only THP head pages to be present in the
 * @pvec.
 *
 * The function expects the i_pages lock to be held.
 */
अटल व्योम page_cache_delete_batch(काष्ठा address_space *mapping,
			     काष्ठा pagevec *pvec)
अणु
	XA_STATE(xas, &mapping->i_pages, pvec->pages[0]->index);
	पूर्णांक total_pages = 0;
	पूर्णांक i = 0;
	काष्ठा page *page;

	mapping_set_update(&xas, mapping);
	xas_क्रम_each(&xas, page, अच_दीर्घ_उच्च) अणु
		अगर (i >= pagevec_count(pvec))
			अवरोध;

		/* A swap/dax/shaकरोw entry got inserted? Skip it. */
		अगर (xa_is_value(page))
			जारी;
		/*
		 * A page got inserted in our range? Skip it. We have our
		 * pages locked so they are रक्षित from being हटाओd.
		 * If we see a page whose index is higher than ours, it
		 * means our page has been हटाओd, which shouldn't be
		 * possible because we're holding the PageLock.
		 */
		अगर (page != pvec->pages[i]) अणु
			VM_BUG_ON_PAGE(page->index > pvec->pages[i]->index,
					page);
			जारी;
		पूर्ण

		WARN_ON_ONCE(!PageLocked(page));

		अगर (page->index == xas.xa_index)
			page->mapping = शून्य;
		/* Leave page->index set: truncation lookup relies on it */

		/*
		 * Move to the next page in the vector अगर this is a regular
		 * page or the index is of the last sub-page of this compound
		 * page.
		 */
		अगर (page->index + compound_nr(page) - 1 == xas.xa_index)
			i++;
		xas_store(&xas, शून्य);
		total_pages++;
	पूर्ण
	mapping->nrpages -= total_pages;
पूर्ण

व्योम delete_from_page_cache_batch(काष्ठा address_space *mapping,
				  काष्ठा pagevec *pvec)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (!pagevec_count(pvec))
		वापस;

	xa_lock_irqsave(&mapping->i_pages, flags);
	क्रम (i = 0; i < pagevec_count(pvec); i++) अणु
		trace_mm_filemap_delete_from_page_cache(pvec->pages[i]);

		unaccount_page_cache_page(mapping, pvec->pages[i]);
	पूर्ण
	page_cache_delete_batch(mapping, pvec);
	xa_unlock_irqrestore(&mapping->i_pages, flags);

	क्रम (i = 0; i < pagevec_count(pvec); i++)
		page_cache_मुक्त_page(mapping, pvec->pages[i]);
पूर्ण

पूर्णांक filemap_check_errors(काष्ठा address_space *mapping)
अणु
	पूर्णांक ret = 0;
	/* Check क्रम outstanding ग_लिखो errors */
	अगर (test_bit(AS_ENOSPC, &mapping->flags) &&
	    test_and_clear_bit(AS_ENOSPC, &mapping->flags))
		ret = -ENOSPC;
	अगर (test_bit(AS_EIO, &mapping->flags) &&
	    test_and_clear_bit(AS_EIO, &mapping->flags))
		ret = -EIO;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(filemap_check_errors);

अटल पूर्णांक filemap_check_and_keep_errors(काष्ठा address_space *mapping)
अणु
	/* Check क्रम outstanding ग_लिखो errors */
	अगर (test_bit(AS_EIO, &mapping->flags))
		वापस -EIO;
	अगर (test_bit(AS_ENOSPC, &mapping->flags))
		वापस -ENOSPC;
	वापस 0;
पूर्ण

/**
 * __filemap_fdataग_लिखो_range - start ग_लिखोback on mapping dirty pages in range
 * @mapping:	address space काष्ठाure to ग_लिखो
 * @start:	offset in bytes where the range starts
 * @end:	offset in bytes where the range ends (inclusive)
 * @sync_mode:	enable synchronous operation
 *
 * Start ग_लिखोback against all of a mapping's dirty pages that lie
 * within the byte offsets <start, end> inclusive.
 *
 * If sync_mode is WB_SYNC_ALL then this is a "data integrity" operation, as
 * opposed to a regular memory cleansing ग_लिखोback.  The dअगरference between
 * these two operations is that अगर a dirty page/buffer is encountered, it must
 * be रुकोed upon, and not just skipped over.
 *
 * Return: %0 on success, negative error code otherwise.
 */
पूर्णांक __filemap_fdataग_लिखो_range(काष्ठा address_space *mapping, loff_t start,
				loff_t end, पूर्णांक sync_mode)
अणु
	पूर्णांक ret;
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode = sync_mode,
		.nr_to_ग_लिखो = दीर्घ_उच्च,
		.range_start = start,
		.range_end = end,
	पूर्ण;

	अगर (!mapping_can_ग_लिखोback(mapping) ||
	    !mapping_tagged(mapping, PAGECACHE_TAG_सूचीTY))
		वापस 0;

	wbc_attach_fdataग_लिखो_inode(&wbc, mapping->host);
	ret = करो_ग_लिखोpages(mapping, &wbc);
	wbc_detach_inode(&wbc);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक __filemap_fdataग_लिखो(काष्ठा address_space *mapping,
	पूर्णांक sync_mode)
अणु
	वापस __filemap_fdataग_लिखो_range(mapping, 0, Lदीर्घ_उच्च, sync_mode);
पूर्ण

पूर्णांक filemap_fdataग_लिखो(काष्ठा address_space *mapping)
अणु
	वापस __filemap_fdataग_लिखो(mapping, WB_SYNC_ALL);
पूर्ण
EXPORT_SYMBOL(filemap_fdataग_लिखो);

पूर्णांक filemap_fdataग_लिखो_range(काष्ठा address_space *mapping, loff_t start,
				loff_t end)
अणु
	वापस __filemap_fdataग_लिखो_range(mapping, start, end, WB_SYNC_ALL);
पूर्ण
EXPORT_SYMBOL(filemap_fdataग_लिखो_range);

/**
 * filemap_flush - mostly a non-blocking flush
 * @mapping:	target address_space
 *
 * This is a mostly non-blocking flush.  Not suitable क्रम data-पूर्णांकegrity
 * purposes - I/O may not be started against all dirty pages.
 *
 * Return: %0 on success, negative error code otherwise.
 */
पूर्णांक filemap_flush(काष्ठा address_space *mapping)
अणु
	वापस __filemap_fdataग_लिखो(mapping, WB_SYNC_NONE);
पूर्ण
EXPORT_SYMBOL(filemap_flush);

/**
 * filemap_range_has_page - check अगर a page exists in range.
 * @mapping:           address space within which to check
 * @start_byte:        offset in bytes where the range starts
 * @end_byte:          offset in bytes where the range ends (inclusive)
 *
 * Find at least one page in the range supplied, usually used to check अगर
 * direct writing in this range will trigger a ग_लिखोback.
 *
 * Return: %true अगर at least one page exists in the specअगरied range,
 * %false otherwise.
 */
bool filemap_range_has_page(काष्ठा address_space *mapping,
			   loff_t start_byte, loff_t end_byte)
अणु
	काष्ठा page *page;
	XA_STATE(xas, &mapping->i_pages, start_byte >> PAGE_SHIFT);
	pgoff_t max = end_byte >> PAGE_SHIFT;

	अगर (end_byte < start_byte)
		वापस false;

	rcu_पढ़ो_lock();
	क्रम (;;) अणु
		page = xas_find(&xas, max);
		अगर (xas_retry(&xas, page))
			जारी;
		/* Shaकरोw entries करोn't count */
		अगर (xa_is_value(page))
			जारी;
		/*
		 * We करोn't need to try to pin this page; we're about to
		 * release the RCU lock anyway.  It is enough to know that
		 * there was a page here recently.
		 */
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस page != शून्य;
पूर्ण
EXPORT_SYMBOL(filemap_range_has_page);

अटल व्योम __filemap_fdataरुको_range(काष्ठा address_space *mapping,
				     loff_t start_byte, loff_t end_byte)
अणु
	pgoff_t index = start_byte >> PAGE_SHIFT;
	pgoff_t end = end_byte >> PAGE_SHIFT;
	काष्ठा pagevec pvec;
	पूर्णांक nr_pages;

	अगर (end_byte < start_byte)
		वापस;

	pagevec_init(&pvec);
	जबतक (index <= end) अणु
		अचिन्हित i;

		nr_pages = pagevec_lookup_range_tag(&pvec, mapping, &index,
				end, PAGECACHE_TAG_WRITEBACK);
		अगर (!nr_pages)
			अवरोध;

		क्रम (i = 0; i < nr_pages; i++) अणु
			काष्ठा page *page = pvec.pages[i];

			रुको_on_page_ग_लिखोback(page);
			ClearPageError(page);
		पूर्ण
		pagevec_release(&pvec);
		cond_resched();
	पूर्ण
पूर्ण

/**
 * filemap_fdataरुको_range - रुको क्रम ग_लिखोback to complete
 * @mapping:		address space काष्ठाure to रुको क्रम
 * @start_byte:		offset in bytes where the range starts
 * @end_byte:		offset in bytes where the range ends (inclusive)
 *
 * Walk the list of under-ग_लिखोback pages of the given address space
 * in the given range and रुको क्रम all of them.  Check error status of
 * the address space and वापस it.
 *
 * Since the error status of the address space is cleared by this function,
 * callers are responsible क्रम checking the वापस value and handling and/or
 * reporting the error.
 *
 * Return: error status of the address space.
 */
पूर्णांक filemap_fdataरुको_range(काष्ठा address_space *mapping, loff_t start_byte,
			    loff_t end_byte)
अणु
	__filemap_fdataरुको_range(mapping, start_byte, end_byte);
	वापस filemap_check_errors(mapping);
पूर्ण
EXPORT_SYMBOL(filemap_fdataरुको_range);

/**
 * filemap_fdataरुको_range_keep_errors - रुको क्रम ग_लिखोback to complete
 * @mapping:		address space काष्ठाure to रुको क्रम
 * @start_byte:		offset in bytes where the range starts
 * @end_byte:		offset in bytes where the range ends (inclusive)
 *
 * Walk the list of under-ग_लिखोback pages of the given address space in the
 * given range and रुको क्रम all of them.  Unlike filemap_fdataरुको_range(),
 * this function करोes not clear error status of the address space.
 *
 * Use this function अगर callers करोn't handle errors themselves.  Expected
 * call sites are प्रणाली-wide / fileप्रणाली-wide data flushers: e.g. sync(2),
 * fsमुक्तze(8)
 */
पूर्णांक filemap_fdataरुको_range_keep_errors(काष्ठा address_space *mapping,
		loff_t start_byte, loff_t end_byte)
अणु
	__filemap_fdataरुको_range(mapping, start_byte, end_byte);
	वापस filemap_check_and_keep_errors(mapping);
पूर्ण
EXPORT_SYMBOL(filemap_fdataरुको_range_keep_errors);

/**
 * file_fdataरुको_range - रुको क्रम ग_लिखोback to complete
 * @file:		file poपूर्णांकing to address space काष्ठाure to रुको क्रम
 * @start_byte:		offset in bytes where the range starts
 * @end_byte:		offset in bytes where the range ends (inclusive)
 *
 * Walk the list of under-ग_लिखोback pages of the address space that file
 * refers to, in the given range and रुको क्रम all of them.  Check error
 * status of the address space vs. the file->f_wb_err cursor and वापस it.
 *
 * Since the error status of the file is advanced by this function,
 * callers are responsible क्रम checking the वापस value and handling and/or
 * reporting the error.
 *
 * Return: error status of the address space vs. the file->f_wb_err cursor.
 */
पूर्णांक file_fdataरुको_range(काष्ठा file *file, loff_t start_byte, loff_t end_byte)
अणु
	काष्ठा address_space *mapping = file->f_mapping;

	__filemap_fdataरुको_range(mapping, start_byte, end_byte);
	वापस file_check_and_advance_wb_err(file);
पूर्ण
EXPORT_SYMBOL(file_fdataरुको_range);

/**
 * filemap_fdataरुको_keep_errors - रुको क्रम ग_लिखोback without clearing errors
 * @mapping: address space काष्ठाure to रुको क्रम
 *
 * Walk the list of under-ग_लिखोback pages of the given address space
 * and रुको क्रम all of them.  Unlike filemap_fdataरुको(), this function
 * करोes not clear error status of the address space.
 *
 * Use this function अगर callers करोn't handle errors themselves.  Expected
 * call sites are प्रणाली-wide / fileप्रणाली-wide data flushers: e.g. sync(2),
 * fsमुक्तze(8)
 *
 * Return: error status of the address space.
 */
पूर्णांक filemap_fdataरुको_keep_errors(काष्ठा address_space *mapping)
अणु
	__filemap_fdataरुको_range(mapping, 0, Lदीर्घ_उच्च);
	वापस filemap_check_and_keep_errors(mapping);
पूर्ण
EXPORT_SYMBOL(filemap_fdataरुको_keep_errors);

/* Returns true अगर ग_लिखोback might be needed or alपढ़ोy in progress. */
अटल bool mapping_needs_ग_लिखोback(काष्ठा address_space *mapping)
अणु
	वापस mapping->nrpages;
पूर्ण

/**
 * filemap_range_needs_ग_लिखोback - check अगर range potentially needs ग_लिखोback
 * @mapping:           address space within which to check
 * @start_byte:        offset in bytes where the range starts
 * @end_byte:          offset in bytes where the range ends (inclusive)
 *
 * Find at least one page in the range supplied, usually used to check अगर
 * direct writing in this range will trigger a ग_लिखोback. Used by O_सूचीECT
 * पढ़ो/ग_लिखो with IOCB_NOWAIT, to see अगर the caller needs to करो
 * filemap_ग_लिखो_and_रुको_range() beक्रमe proceeding.
 *
 * Return: %true अगर the caller should करो filemap_ग_लिखो_and_रुको_range() beक्रमe
 * करोing O_सूचीECT to a page in this range, %false otherwise.
 */
bool filemap_range_needs_ग_लिखोback(काष्ठा address_space *mapping,
				   loff_t start_byte, loff_t end_byte)
अणु
	XA_STATE(xas, &mapping->i_pages, start_byte >> PAGE_SHIFT);
	pgoff_t max = end_byte >> PAGE_SHIFT;
	काष्ठा page *page;

	अगर (!mapping_needs_ग_लिखोback(mapping))
		वापस false;
	अगर (!mapping_tagged(mapping, PAGECACHE_TAG_सूचीTY) &&
	    !mapping_tagged(mapping, PAGECACHE_TAG_WRITEBACK))
		वापस false;
	अगर (end_byte < start_byte)
		वापस false;

	rcu_पढ़ो_lock();
	xas_क्रम_each(&xas, page, max) अणु
		अगर (xas_retry(&xas, page))
			जारी;
		अगर (xa_is_value(page))
			जारी;
		अगर (PageDirty(page) || PageLocked(page) || PageWriteback(page))
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस page != शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(filemap_range_needs_ग_लिखोback);

/**
 * filemap_ग_लिखो_and_रुको_range - ग_लिखो out & रुको on a file range
 * @mapping:	the address_space क्रम the pages
 * @lstart:	offset in bytes where the range starts
 * @lend:	offset in bytes where the range ends (inclusive)
 *
 * Write out and रुको upon file offsets lstart->lend, inclusive.
 *
 * Note that @lend is inclusive (describes the last byte to be written) so
 * that this function can be used to ग_लिखो to the very end-of-file (end = -1).
 *
 * Return: error status of the address space.
 */
पूर्णांक filemap_ग_लिखो_and_रुको_range(काष्ठा address_space *mapping,
				 loff_t lstart, loff_t lend)
अणु
	पूर्णांक err = 0;

	अगर (mapping_needs_ग_लिखोback(mapping)) अणु
		err = __filemap_fdataग_लिखो_range(mapping, lstart, lend,
						 WB_SYNC_ALL);
		/*
		 * Even अगर the above वापसed error, the pages may be
		 * written partially (e.g. -ENOSPC), so we रुको क्रम it.
		 * But the -EIO is special हाल, it may indicate the worst
		 * thing (e.g. bug) happened, so we aव्योम रुकोing क्रम it.
		 */
		अगर (err != -EIO) अणु
			पूर्णांक err2 = filemap_fdataरुको_range(mapping,
						lstart, lend);
			अगर (!err)
				err = err2;
		पूर्ण अन्यथा अणु
			/* Clear any previously stored errors */
			filemap_check_errors(mapping);
		पूर्ण
	पूर्ण अन्यथा अणु
		err = filemap_check_errors(mapping);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL(filemap_ग_लिखो_and_रुको_range);

व्योम __filemap_set_wb_err(काष्ठा address_space *mapping, पूर्णांक err)
अणु
	errseq_t eseq = errseq_set(&mapping->wb_err, err);

	trace_filemap_set_wb_err(mapping, eseq);
पूर्ण
EXPORT_SYMBOL(__filemap_set_wb_err);

/**
 * file_check_and_advance_wb_err - report wb error (अगर any) that was previously
 * 				   and advance wb_err to current one
 * @file: काष्ठा file on which the error is being reported
 *
 * When userland calls fsync (or something like nfsd करोes the equivalent), we
 * want to report any ग_लिखोback errors that occurred since the last fsync (or
 * since the file was खोलोed अगर there haven't been any).
 *
 * Grab the wb_err from the mapping. If it matches what we have in the file,
 * then just quickly वापस 0. The file is all caught up.
 *
 * If it करोesn't match, then take the mapping value, set the "seen" flag in
 * it and try to swap it पूर्णांकo place. If it works, or another task beat us
 * to it with the new value, then update the f_wb_err and वापस the error
 * portion. The error at this poपूर्णांक must be reported via proper channels
 * (a'la fsync, or NFS COMMIT operation, etc.).
 *
 * While we handle mapping->wb_err with atomic operations, the f_wb_err
 * value is रक्षित by the f_lock since we must ensure that it reflects
 * the latest value swapped in क्रम this file descriptor.
 *
 * Return: %0 on success, negative error code otherwise.
 */
पूर्णांक file_check_and_advance_wb_err(काष्ठा file *file)
अणु
	पूर्णांक err = 0;
	errseq_t old = READ_ONCE(file->f_wb_err);
	काष्ठा address_space *mapping = file->f_mapping;

	/* Locklessly handle the common हाल where nothing has changed */
	अगर (errseq_check(&mapping->wb_err, old)) अणु
		/* Something changed, must use slow path */
		spin_lock(&file->f_lock);
		old = file->f_wb_err;
		err = errseq_check_and_advance(&mapping->wb_err,
						&file->f_wb_err);
		trace_file_check_and_advance_wb_err(file, old);
		spin_unlock(&file->f_lock);
	पूर्ण

	/*
	 * We're mostly using this function as a drop in replacement क्रम
	 * filemap_check_errors. Clear AS_EIO/AS_ENOSPC to emulate the effect
	 * that the legacy code would have had on these flags.
	 */
	clear_bit(AS_EIO, &mapping->flags);
	clear_bit(AS_ENOSPC, &mapping->flags);
	वापस err;
पूर्ण
EXPORT_SYMBOL(file_check_and_advance_wb_err);

/**
 * file_ग_लिखो_and_रुको_range - ग_लिखो out & रुको on a file range
 * @file:	file poपूर्णांकing to address_space with pages
 * @lstart:	offset in bytes where the range starts
 * @lend:	offset in bytes where the range ends (inclusive)
 *
 * Write out and रुको upon file offsets lstart->lend, inclusive.
 *
 * Note that @lend is inclusive (describes the last byte to be written) so
 * that this function can be used to ग_लिखो to the very end-of-file (end = -1).
 *
 * After writing out and रुकोing on the data, we check and advance the
 * f_wb_err cursor to the latest value, and वापस any errors detected there.
 *
 * Return: %0 on success, negative error code otherwise.
 */
पूर्णांक file_ग_लिखो_and_रुको_range(काष्ठा file *file, loff_t lstart, loff_t lend)
अणु
	पूर्णांक err = 0, err2;
	काष्ठा address_space *mapping = file->f_mapping;

	अगर (mapping_needs_ग_लिखोback(mapping)) अणु
		err = __filemap_fdataग_लिखो_range(mapping, lstart, lend,
						 WB_SYNC_ALL);
		/* See comment of filemap_ग_लिखो_and_रुको() */
		अगर (err != -EIO)
			__filemap_fdataरुको_range(mapping, lstart, lend);
	पूर्ण
	err2 = file_check_and_advance_wb_err(file);
	अगर (!err)
		err = err2;
	वापस err;
पूर्ण
EXPORT_SYMBOL(file_ग_लिखो_and_रुको_range);

/**
 * replace_page_cache_page - replace a pagecache page with a new one
 * @old:	page to be replaced
 * @new:	page to replace with
 *
 * This function replaces a page in the pagecache with a new one.  On
 * success it acquires the pagecache reference क्रम the new page and
 * drops it क्रम the old page.  Both the old and new pages must be
 * locked.  This function करोes not add the new page to the LRU, the
 * caller must करो that.
 *
 * The हटाओ + add is atomic.  This function cannot fail.
 */
व्योम replace_page_cache_page(काष्ठा page *old, काष्ठा page *new)
अणु
	काष्ठा address_space *mapping = old->mapping;
	व्योम (*मुक्तpage)(काष्ठा page *) = mapping->a_ops->मुक्तpage;
	pgoff_t offset = old->index;
	XA_STATE(xas, &mapping->i_pages, offset);
	अचिन्हित दीर्घ flags;

	VM_BUG_ON_PAGE(!PageLocked(old), old);
	VM_BUG_ON_PAGE(!PageLocked(new), new);
	VM_BUG_ON_PAGE(new->mapping, new);

	get_page(new);
	new->mapping = mapping;
	new->index = offset;

	mem_cgroup_migrate(old, new);

	xas_lock_irqsave(&xas, flags);
	xas_store(&xas, new);

	old->mapping = शून्य;
	/* hugetlb pages करो not participate in page cache accounting. */
	अगर (!PageHuge(old))
		__dec_lruvec_page_state(old, NR_खाता_PAGES);
	अगर (!PageHuge(new))
		__inc_lruvec_page_state(new, NR_खाता_PAGES);
	अगर (PageSwapBacked(old))
		__dec_lruvec_page_state(old, NR_SHMEM);
	अगर (PageSwapBacked(new))
		__inc_lruvec_page_state(new, NR_SHMEM);
	xas_unlock_irqrestore(&xas, flags);
	अगर (मुक्तpage)
		मुक्तpage(old);
	put_page(old);
पूर्ण
EXPORT_SYMBOL_GPL(replace_page_cache_page);

noअंतरभूत पूर्णांक __add_to_page_cache_locked(काष्ठा page *page,
					काष्ठा address_space *mapping,
					pgoff_t offset, gfp_t gfp,
					व्योम **shaकरोwp)
अणु
	XA_STATE(xas, &mapping->i_pages, offset);
	पूर्णांक huge = PageHuge(page);
	पूर्णांक error;
	bool अक्षरged = false;

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(PageSwapBacked(page), page);
	mapping_set_update(&xas, mapping);

	get_page(page);
	page->mapping = mapping;
	page->index = offset;

	अगर (!huge) अणु
		error = mem_cgroup_अक्षरge(page, current->mm, gfp);
		अगर (error)
			जाओ error;
		अक्षरged = true;
	पूर्ण

	gfp &= GFP_RECLAIM_MASK;

	करो अणु
		अचिन्हित पूर्णांक order = xa_get_order(xas.xa, xas.xa_index);
		व्योम *entry, *old = शून्य;

		अगर (order > thp_order(page))
			xas_split_alloc(&xas, xa_load(xas.xa, xas.xa_index),
					order, gfp);
		xas_lock_irq(&xas);
		xas_क्रम_each_conflict(&xas, entry) अणु
			old = entry;
			अगर (!xa_is_value(entry)) अणु
				xas_set_err(&xas, -EEXIST);
				जाओ unlock;
			पूर्ण
		पूर्ण

		अगर (old) अणु
			अगर (shaकरोwp)
				*shaकरोwp = old;
			/* entry may have been split beक्रमe we acquired lock */
			order = xa_get_order(xas.xa, xas.xa_index);
			अगर (order > thp_order(page)) अणु
				xas_split(&xas, old, order);
				xas_reset(&xas);
			पूर्ण
		पूर्ण

		xas_store(&xas, page);
		अगर (xas_error(&xas))
			जाओ unlock;

		mapping->nrpages++;

		/* hugetlb pages करो not participate in page cache accounting */
		अगर (!huge)
			__inc_lruvec_page_state(page, NR_खाता_PAGES);
unlock:
		xas_unlock_irq(&xas);
	पूर्ण जबतक (xas_nomem(&xas, gfp));

	अगर (xas_error(&xas)) अणु
		error = xas_error(&xas);
		अगर (अक्षरged)
			mem_cgroup_unअक्षरge(page);
		जाओ error;
	पूर्ण

	trace_mm_filemap_add_to_page_cache(page);
	वापस 0;
error:
	page->mapping = शून्य;
	/* Leave page->index set: truncation relies upon it */
	put_page(page);
	वापस error;
पूर्ण
ALLOW_ERROR_INJECTION(__add_to_page_cache_locked, ERRNO);

/**
 * add_to_page_cache_locked - add a locked page to the pagecache
 * @page:	page to add
 * @mapping:	the page's address_space
 * @offset:	page index
 * @gfp_mask:	page allocation mode
 *
 * This function is used to add a page to the pagecache. It must be locked.
 * This function करोes not add the page to the LRU.  The caller must करो that.
 *
 * Return: %0 on success, negative error code otherwise.
 */
पूर्णांक add_to_page_cache_locked(काष्ठा page *page, काष्ठा address_space *mapping,
		pgoff_t offset, gfp_t gfp_mask)
अणु
	वापस __add_to_page_cache_locked(page, mapping, offset,
					  gfp_mask, शून्य);
पूर्ण
EXPORT_SYMBOL(add_to_page_cache_locked);

पूर्णांक add_to_page_cache_lru(काष्ठा page *page, काष्ठा address_space *mapping,
				pgoff_t offset, gfp_t gfp_mask)
अणु
	व्योम *shaकरोw = शून्य;
	पूर्णांक ret;

	__SetPageLocked(page);
	ret = __add_to_page_cache_locked(page, mapping, offset,
					 gfp_mask, &shaकरोw);
	अगर (unlikely(ret))
		__ClearPageLocked(page);
	अन्यथा अणु
		/*
		 * The page might have been evicted from cache only
		 * recently, in which हाल it should be activated like
		 * any other repeatedly accessed page.
		 * The exception is pages getting rewritten; evicting other
		 * data from the working set, only to cache data that will
		 * get overwritten with something अन्यथा, is a waste of memory.
		 */
		WARN_ON_ONCE(PageActive(page));
		अगर (!(gfp_mask & __GFP_WRITE) && shaकरोw)
			workingset_refault(page, shaकरोw);
		lru_cache_add(page);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(add_to_page_cache_lru);

#अगर_घोषित CONFIG_NUMA
काष्ठा page *__page_cache_alloc(gfp_t gfp)
अणु
	पूर्णांक n;
	काष्ठा page *page;

	अगर (cpuset_करो_page_mem_spपढ़ो()) अणु
		अचिन्हित पूर्णांक cpuset_mems_cookie;
		करो अणु
			cpuset_mems_cookie = पढ़ो_mems_allowed_begin();
			n = cpuset_mem_spपढ़ो_node();
			page = __alloc_pages_node(n, gfp, 0);
		पूर्ण जबतक (!page && पढ़ो_mems_allowed_retry(cpuset_mems_cookie));

		वापस page;
	पूर्ण
	वापस alloc_pages(gfp, 0);
पूर्ण
EXPORT_SYMBOL(__page_cache_alloc);
#पूर्ण_अगर

/*
 * In order to रुको क्रम pages to become available there must be
 * रुकोqueues associated with pages. By using a hash table of
 * रुकोqueues where the bucket discipline is to मुख्यtain all
 * रुकोers on the same queue and wake all when any of the pages
 * become available, and क्रम the woken contexts to check to be
 * sure the appropriate page became available, this saves space
 * at a cost of "thundering herd" phenomena during rare hash
 * collisions.
 */
#घोषणा PAGE_WAIT_TABLE_BITS 8
#घोषणा PAGE_WAIT_TABLE_SIZE (1 << PAGE_WAIT_TABLE_BITS)
अटल रुको_queue_head_t page_रुको_table[PAGE_WAIT_TABLE_SIZE] __cacheline_aligned;

अटल रुको_queue_head_t *page_रुकोqueue(काष्ठा page *page)
अणु
	वापस &page_रुको_table[hash_ptr(page, PAGE_WAIT_TABLE_BITS)];
पूर्ण

व्योम __init pagecache_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PAGE_WAIT_TABLE_SIZE; i++)
		init_रुकोqueue_head(&page_रुको_table[i]);

	page_ग_लिखोback_init();
पूर्ण

/*
 * The page रुको code treats the "wait->flags" somewhat unusually, because
 * we have multiple dअगरferent kinds of रुकोs, not just the usual "exclusive"
 * one.
 *
 * We have:
 *
 *  (a) no special bits set:
 *
 *	We're just रुकोing क्रम the bit to be released, and when a waker
 *	calls the wakeup function, we set WQ_FLAG_WOKEN and wake it up,
 *	and हटाओ it from the रुको queue.
 *
 *	Simple and straightक्रमward.
 *
 *  (b) WQ_FLAG_EXCLUSIVE:
 *
 *	The रुकोer is रुकोing to get the lock, and only one रुकोer should
 *	be woken up to aव्योम any thundering herd behavior. We'll set the
 *	WQ_FLAG_WOKEN bit, wake it up, and हटाओ it from the रुको queue.
 *
 *	This is the traditional exclusive रुको.
 *
 *  (c) WQ_FLAG_EXCLUSIVE | WQ_FLAG_CUSTOM:
 *
 *	The रुकोer is रुकोing to get the bit, and additionally wants the
 *	lock to be transferred to it क्रम fair lock behavior. If the lock
 *	cannot be taken, we stop walking the रुको queue without waking
 *	the रुकोer.
 *
 *	This is the "fair lock handoff" हाल, and in addition to setting
 *	WQ_FLAG_WOKEN, we set WQ_FLAG_DONE to let the रुकोer easily see
 *	that it now has the lock.
 */
अटल पूर्णांक wake_page_function(रुको_queue_entry_t *रुको, अचिन्हित mode, पूर्णांक sync, व्योम *arg)
अणु
	अचिन्हित पूर्णांक flags;
	काष्ठा रुको_page_key *key = arg;
	काष्ठा रुको_page_queue *रुको_page
		= container_of(रुको, काष्ठा रुको_page_queue, रुको);

	अगर (!wake_page_match(रुको_page, key))
		वापस 0;

	/*
	 * If it's a lock hanकरोff रुको, we get the bit क्रम it, and
	 * stop walking (and करो not wake it up) अगर we can't.
	 */
	flags = रुको->flags;
	अगर (flags & WQ_FLAG_EXCLUSIVE) अणु
		अगर (test_bit(key->bit_nr, &key->page->flags))
			वापस -1;
		अगर (flags & WQ_FLAG_CUSTOM) अणु
			अगर (test_and_set_bit(key->bit_nr, &key->page->flags))
				वापस -1;
			flags |= WQ_FLAG_DONE;
		पूर्ण
	पूर्ण

	/*
	 * We are holding the रुको-queue lock, but the रुकोer that
	 * is रुकोing क्रम this will be checking the flags without
	 * any locking.
	 *
	 * So update the flags atomically, and wake up the रुकोer
	 * afterwards to aव्योम any races. This store-release pairs
	 * with the load-acquire in रुको_on_page_bit_common().
	 */
	smp_store_release(&रुको->flags, flags | WQ_FLAG_WOKEN);
	wake_up_state(रुको->निजी, mode);

	/*
	 * Ok, we have successfully करोne what we're रुकोing क्रम,
	 * and we can unconditionally हटाओ the रुको entry.
	 *
	 * Note that this pairs with the "finish_wait()" in the
	 * रुकोer, and has to be the असलolute last thing we करो.
	 * After this list_del_init(&रुको->entry) the रुको entry
	 * might be de-allocated and the process might even have
	 * निकासed.
	 */
	list_del_init_careful(&रुको->entry);
	वापस (flags & WQ_FLAG_EXCLUSIVE) != 0;
पूर्ण

अटल व्योम wake_up_page_bit(काष्ठा page *page, पूर्णांक bit_nr)
अणु
	रुको_queue_head_t *q = page_रुकोqueue(page);
	काष्ठा रुको_page_key key;
	अचिन्हित दीर्घ flags;
	रुको_queue_entry_t bookmark;

	key.page = page;
	key.bit_nr = bit_nr;
	key.page_match = 0;

	bookmark.flags = 0;
	bookmark.निजी = शून्य;
	bookmark.func = शून्य;
	INIT_LIST_HEAD(&bookmark.entry);

	spin_lock_irqsave(&q->lock, flags);
	__wake_up_locked_key_bookmark(q, TASK_NORMAL, &key, &bookmark);

	जबतक (bookmark.flags & WQ_FLAG_BOOKMARK) अणु
		/*
		 * Take a breather from holding the lock,
		 * allow pages that finish wake up asynchronously
		 * to acquire the lock and हटाओ themselves
		 * from रुको queue
		 */
		spin_unlock_irqrestore(&q->lock, flags);
		cpu_relax();
		spin_lock_irqsave(&q->lock, flags);
		__wake_up_locked_key_bookmark(q, TASK_NORMAL, &key, &bookmark);
	पूर्ण

	/*
	 * It is possible क्रम other pages to have collided on the रुकोqueue
	 * hash, so in that हाल check क्रम a page match. That prevents a दीर्घ-
	 * term रुकोer
	 *
	 * It is still possible to miss a हाल here, when we woke page रुकोers
	 * and हटाओd them from the रुकोqueue, but there are still other
	 * page रुकोers.
	 */
	अगर (!रुकोqueue_active(q) || !key.page_match) अणु
		ClearPageWaiters(page);
		/*
		 * It's possible to miss clearing Waiters here, when we woke
		 * our page रुकोers, but the hashed रुकोqueue has रुकोers क्रम
		 * other pages on it.
		 *
		 * That's okay, it's a rare हाल. The next waker will clear it.
		 */
	पूर्ण
	spin_unlock_irqrestore(&q->lock, flags);
पूर्ण

अटल व्योम wake_up_page(काष्ठा page *page, पूर्णांक bit)
अणु
	अगर (!PageWaiters(page))
		वापस;
	wake_up_page_bit(page, bit);
पूर्ण

/*
 * A choice of three behaviors क्रम रुको_on_page_bit_common():
 */
क्रमागत behavior अणु
	EXCLUSIVE,	/* Hold ref to page and take the bit when woken, like
			 * __lock_page() रुकोing on then setting PG_locked.
			 */
	SHARED,		/* Hold ref to page and check the bit when woken, like
			 * रुको_on_page_ग_लिखोback() रुकोing on PG_ग_लिखोback.
			 */
	DROP,		/* Drop ref to page beक्रमe रुको, no check when woken,
			 * like put_and_रुको_on_page_locked() on PG_locked.
			 */
पूर्ण;

/*
 * Attempt to check (or get) the page bit, and mark us करोne
 * अगर successful.
 */
अटल अंतरभूत bool trylock_page_bit_common(काष्ठा page *page, पूर्णांक bit_nr,
					काष्ठा रुको_queue_entry *रुको)
अणु
	अगर (रुको->flags & WQ_FLAG_EXCLUSIVE) अणु
		अगर (test_and_set_bit(bit_nr, &page->flags))
			वापस false;
	पूर्ण अन्यथा अगर (test_bit(bit_nr, &page->flags))
		वापस false;

	रुको->flags |= WQ_FLAG_WOKEN | WQ_FLAG_DONE;
	वापस true;
पूर्ण

/* How many बार करो we accept lock stealing from under a रुकोer? */
पूर्णांक sysctl_page_lock_unfairness = 5;

अटल अंतरभूत पूर्णांक रुको_on_page_bit_common(रुको_queue_head_t *q,
	काष्ठा page *page, पूर्णांक bit_nr, पूर्णांक state, क्रमागत behavior behavior)
अणु
	पूर्णांक unfairness = sysctl_page_lock_unfairness;
	काष्ठा रुको_page_queue रुको_page;
	रुको_queue_entry_t *रुको = &रुको_page.रुको;
	bool thrashing = false;
	bool delayacct = false;
	अचिन्हित दीर्घ pflags;

	अगर (bit_nr == PG_locked &&
	    !PageUptodate(page) && PageWorkingset(page)) अणु
		अगर (!PageSwapBacked(page)) अणु
			delayacct_thrashing_start();
			delayacct = true;
		पूर्ण
		psi_memstall_enter(&pflags);
		thrashing = true;
	पूर्ण

	init_रुको(रुको);
	रुको->func = wake_page_function;
	रुको_page.page = page;
	रुको_page.bit_nr = bit_nr;

repeat:
	रुको->flags = 0;
	अगर (behavior == EXCLUSIVE) अणु
		रुको->flags = WQ_FLAG_EXCLUSIVE;
		अगर (--unfairness < 0)
			रुको->flags |= WQ_FLAG_CUSTOM;
	पूर्ण

	/*
	 * Do one last check whether we can get the
	 * page bit synchronously.
	 *
	 * Do the SetPageWaiters() marking beक्रमe that
	 * to let any waker we _just_ missed know they
	 * need to wake us up (otherwise they'll never
	 * even go to the slow हाल that looks at the
	 * page queue), and add ourselves to the रुको
	 * queue अगर we need to sleep.
	 *
	 * This part needs to be करोne under the queue
	 * lock to aव्योम races.
	 */
	spin_lock_irq(&q->lock);
	SetPageWaiters(page);
	अगर (!trylock_page_bit_common(page, bit_nr, रुको))
		__add_रुको_queue_entry_tail(q, रुको);
	spin_unlock_irq(&q->lock);

	/*
	 * From now on, all the logic will be based on
	 * the WQ_FLAG_WOKEN and WQ_FLAG_DONE flag, to
	 * see whether the page bit testing has alपढ़ोy
	 * been करोne by the wake function.
	 *
	 * We can drop our reference to the page.
	 */
	अगर (behavior == DROP)
		put_page(page);

	/*
	 * Note that until the "finish_wait()", or until
	 * we see the WQ_FLAG_WOKEN flag, we need to
	 * be very careful with the 'wait->flags', because
	 * we may race with a waker that sets them.
	 */
	क्रम (;;) अणु
		अचिन्हित पूर्णांक flags;

		set_current_state(state);

		/* Loop until we've been woken or पूर्णांकerrupted */
		flags = smp_load_acquire(&रुको->flags);
		अगर (!(flags & WQ_FLAG_WOKEN)) अणु
			अगर (संकेत_pending_state(state, current))
				अवरोध;

			io_schedule();
			जारी;
		पूर्ण

		/* If we were non-exclusive, we're करोne */
		अगर (behavior != EXCLUSIVE)
			अवरोध;

		/* If the waker got the lock क्रम us, we're करोne */
		अगर (flags & WQ_FLAG_DONE)
			अवरोध;

		/*
		 * Otherwise, अगर we're getting the lock, we need to
		 * try to get it ourselves.
		 *
		 * And अगर that fails, we'll have to retry this all.
		 */
		अगर (unlikely(test_and_set_bit(bit_nr, &page->flags)))
			जाओ repeat;

		रुको->flags |= WQ_FLAG_DONE;
		अवरोध;
	पूर्ण

	/*
	 * If a संकेत happened, this 'finish_wait()' may हटाओ the last
	 * रुकोer from the रुको-queues, but the PageWaiters bit will reमुख्य
	 * set. That's ok. The next wakeup will take care of it, and trying
	 * to करो it here would be dअगरficult and prone to races.
	 */
	finish_रुको(q, रुको);

	अगर (thrashing) अणु
		अगर (delayacct)
			delayacct_thrashing_end();
		psi_memstall_leave(&pflags);
	पूर्ण

	/*
	 * NOTE! The रुको->flags weren't stable until we've करोne the
	 * 'finish_wait()', and we could have निकासed the loop above due
	 * to a संकेत, and had a wakeup event happen after the संकेत
	 * test but beक्रमe the 'finish_wait()'.
	 *
	 * So only after the finish_रुको() can we reliably determine
	 * अगर we got woken up or not, so we can now figure out the final
	 * वापस value based on that state without races.
	 *
	 * Also note that WQ_FLAG_WOKEN is sufficient क्रम a non-exclusive
	 * रुकोer, but an exclusive one requires WQ_FLAG_DONE.
	 */
	अगर (behavior == EXCLUSIVE)
		वापस रुको->flags & WQ_FLAG_DONE ? 0 : -EINTR;

	वापस रुको->flags & WQ_FLAG_WOKEN ? 0 : -EINTR;
पूर्ण

व्योम रुको_on_page_bit(काष्ठा page *page, पूर्णांक bit_nr)
अणु
	रुको_queue_head_t *q = page_रुकोqueue(page);
	रुको_on_page_bit_common(q, page, bit_nr, TASK_UNINTERRUPTIBLE, SHARED);
पूर्ण
EXPORT_SYMBOL(रुको_on_page_bit);

पूर्णांक रुको_on_page_bit_समाप्तable(काष्ठा page *page, पूर्णांक bit_nr)
अणु
	रुको_queue_head_t *q = page_रुकोqueue(page);
	वापस रुको_on_page_bit_common(q, page, bit_nr, TASK_KILLABLE, SHARED);
पूर्ण
EXPORT_SYMBOL(रुको_on_page_bit_समाप्तable);

/**
 * put_and_रुको_on_page_locked - Drop a reference and रुको क्रम it to be unlocked
 * @page: The page to रुको क्रम.
 * @state: The sleep state (TASK_KILLABLE, TASK_UNINTERRUPTIBLE, etc).
 *
 * The caller should hold a reference on @page.  They expect the page to
 * become unlocked relatively soon, but करो not wish to hold up migration
 * (क्रम example) by holding the reference जबतक रुकोing क्रम the page to
 * come unlocked.  After this function वापसs, the caller should not
 * dereference @page.
 *
 * Return: 0 अगर the page was unlocked or -EINTR अगर पूर्णांकerrupted by a संकेत.
 */
पूर्णांक put_and_रुको_on_page_locked(काष्ठा page *page, पूर्णांक state)
अणु
	रुको_queue_head_t *q;

	page = compound_head(page);
	q = page_रुकोqueue(page);
	वापस रुको_on_page_bit_common(q, page, PG_locked, state, DROP);
पूर्ण

/**
 * add_page_रुको_queue - Add an arbitrary रुकोer to a page's रुको queue
 * @page: Page defining the रुको queue of पूर्णांकerest
 * @रुकोer: Waiter to add to the queue
 *
 * Add an arbitrary @रुकोer to the रुको queue क्रम the nominated @page.
 */
व्योम add_page_रुको_queue(काष्ठा page *page, रुको_queue_entry_t *रुकोer)
अणु
	रुको_queue_head_t *q = page_रुकोqueue(page);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q->lock, flags);
	__add_रुको_queue_entry_tail(q, रुकोer);
	SetPageWaiters(page);
	spin_unlock_irqrestore(&q->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(add_page_रुको_queue);

#अगर_अघोषित clear_bit_unlock_is_negative_byte

/*
 * PG_रुकोers is the high bit in the same byte as PG_lock.
 *
 * On x86 (and on many other architectures), we can clear PG_lock and
 * test the sign bit at the same समय. But अगर the architecture करोes
 * not support that special operation, we just करो this all by hand
 * instead.
 *
 * The पढ़ो of PG_रुकोers has to be after (or concurrently with) PG_locked
 * being cleared, but a memory barrier should be unnecessary since it is
 * in the same byte as PG_locked.
 */
अटल अंतरभूत bool clear_bit_unlock_is_negative_byte(दीर्घ nr, अस्थिर व्योम *mem)
अणु
	clear_bit_unlock(nr, mem);
	/* smp_mb__after_atomic(); */
	वापस test_bit(PG_रुकोers, mem);
पूर्ण

#पूर्ण_अगर

/**
 * unlock_page - unlock a locked page
 * @page: the page
 *
 * Unlocks the page and wakes up sleepers in रुको_on_page_locked().
 * Also wakes sleepers in रुको_on_page_ग_लिखोback() because the wakeup
 * mechanism between PageLocked pages and PageWriteback pages is shared.
 * But that's OK - sleepers in रुको_on_page_ग_लिखोback() just go back to sleep.
 *
 * Note that this depends on PG_रुकोers being the sign bit in the byte
 * that contains PG_locked - thus the BUILD_BUG_ON(). That allows us to
 * clear the PG_locked bit and test PG_रुकोers at the same समय fairly
 * portably (architectures that करो LL/SC can test any bit, जबतक x86 can
 * test the sign bit).
 */
व्योम unlock_page(काष्ठा page *page)
अणु
	BUILD_BUG_ON(PG_रुकोers != 7);
	page = compound_head(page);
	VM_BUG_ON_PAGE(!PageLocked(page), page);
	अगर (clear_bit_unlock_is_negative_byte(PG_locked, &page->flags))
		wake_up_page_bit(page, PG_locked);
पूर्ण
EXPORT_SYMBOL(unlock_page);

/**
 * end_page_निजी_2 - Clear PG_निजी_2 and release any रुकोers
 * @page: The page
 *
 * Clear the PG_निजी_2 bit on a page and wake up any sleepers रुकोing क्रम
 * this.  The page ref held क्रम PG_निजी_2 being set is released.
 *
 * This is, क्रम example, used when a netfs page is being written to a local
 * disk cache, thereby allowing ग_लिखोs to the cache क्रम the same page to be
 * serialised.
 */
व्योम end_page_निजी_2(काष्ठा page *page)
अणु
	page = compound_head(page);
	VM_BUG_ON_PAGE(!PagePrivate2(page), page);
	clear_bit_unlock(PG_निजी_2, &page->flags);
	wake_up_page_bit(page, PG_निजी_2);
	put_page(page);
पूर्ण
EXPORT_SYMBOL(end_page_निजी_2);

/**
 * रुको_on_page_निजी_2 - Wait क्रम PG_निजी_2 to be cleared on a page
 * @page: The page to रुको on
 *
 * Wait क्रम PG_निजी_2 (aka PG_fscache) to be cleared on a page.
 */
व्योम रुको_on_page_निजी_2(काष्ठा page *page)
अणु
	page = compound_head(page);
	जबतक (PagePrivate2(page))
		रुको_on_page_bit(page, PG_निजी_2);
पूर्ण
EXPORT_SYMBOL(रुको_on_page_निजी_2);

/**
 * रुको_on_page_निजी_2_समाप्तable - Wait क्रम PG_निजी_2 to be cleared on a page
 * @page: The page to रुको on
 *
 * Wait क्रम PG_निजी_2 (aka PG_fscache) to be cleared on a page or until a
 * fatal संकेत is received by the calling task.
 *
 * Return:
 * - 0 अगर successful.
 * - -EINTR अगर a fatal संकेत was encountered.
 */
पूर्णांक रुको_on_page_निजी_2_समाप्तable(काष्ठा page *page)
अणु
	पूर्णांक ret = 0;

	page = compound_head(page);
	जबतक (PagePrivate2(page)) अणु
		ret = रुको_on_page_bit_समाप्तable(page, PG_निजी_2);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(रुको_on_page_निजी_2_समाप्तable);

/**
 * end_page_ग_लिखोback - end ग_लिखोback against a page
 * @page: the page
 */
व्योम end_page_ग_लिखोback(काष्ठा page *page)
अणु
	/*
	 * TestClearPageReclaim could be used here but it is an atomic
	 * operation and overसमाप्त in this particular हाल. Failing to
	 * shuffle a page marked क्रम immediate reclaim is too mild to
	 * justअगरy taking an atomic operation penalty at the end of
	 * ever page ग_लिखोback.
	 */
	अगर (PageReclaim(page)) अणु
		ClearPageReclaim(page);
		rotate_reclaimable_page(page);
	पूर्ण

	/*
	 * Writeback करोes not hold a page reference of its own, relying
	 * on truncation to रुको क्रम the clearing of PG_ग_लिखोback.
	 * But here we must make sure that the page is not मुक्तd and
	 * reused beक्रमe the wake_up_page().
	 */
	get_page(page);
	अगर (!test_clear_page_ग_लिखोback(page))
		BUG();

	smp_mb__after_atomic();
	wake_up_page(page, PG_ग_लिखोback);
	put_page(page);
पूर्ण
EXPORT_SYMBOL(end_page_ग_लिखोback);

/*
 * After completing I/O on a page, call this routine to update the page
 * flags appropriately
 */
व्योम page_endio(काष्ठा page *page, bool is_ग_लिखो, पूर्णांक err)
अणु
	अगर (!is_ग_लिखो) अणु
		अगर (!err) अणु
			SetPageUptodate(page);
		पूर्ण अन्यथा अणु
			ClearPageUptodate(page);
			SetPageError(page);
		पूर्ण
		unlock_page(page);
	पूर्ण अन्यथा अणु
		अगर (err) अणु
			काष्ठा address_space *mapping;

			SetPageError(page);
			mapping = page_mapping(page);
			अगर (mapping)
				mapping_set_error(mapping, err);
		पूर्ण
		end_page_ग_लिखोback(page);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(page_endio);

/**
 * __lock_page - get a lock on the page, assuming we need to sleep to get it
 * @__page: the page to lock
 */
व्योम __lock_page(काष्ठा page *__page)
अणु
	काष्ठा page *page = compound_head(__page);
	रुको_queue_head_t *q = page_रुकोqueue(page);
	रुको_on_page_bit_common(q, page, PG_locked, TASK_UNINTERRUPTIBLE,
				EXCLUSIVE);
पूर्ण
EXPORT_SYMBOL(__lock_page);

पूर्णांक __lock_page_समाप्तable(काष्ठा page *__page)
अणु
	काष्ठा page *page = compound_head(__page);
	रुको_queue_head_t *q = page_रुकोqueue(page);
	वापस रुको_on_page_bit_common(q, page, PG_locked, TASK_KILLABLE,
					EXCLUSIVE);
पूर्ण
EXPORT_SYMBOL_GPL(__lock_page_समाप्तable);

पूर्णांक __lock_page_async(काष्ठा page *page, काष्ठा रुको_page_queue *रुको)
अणु
	काष्ठा रुको_queue_head *q = page_रुकोqueue(page);
	पूर्णांक ret = 0;

	रुको->page = page;
	रुको->bit_nr = PG_locked;

	spin_lock_irq(&q->lock);
	__add_रुको_queue_entry_tail(q, &रुको->रुको);
	SetPageWaiters(page);
	ret = !trylock_page(page);
	/*
	 * If we were successful now, we know we're still on the
	 * रुकोqueue as we're still under the lock. This means it's
	 * safe to हटाओ and वापस success, we know the callback
	 * isn't going to trigger.
	 */
	अगर (!ret)
		__हटाओ_रुको_queue(q, &रुको->रुको);
	अन्यथा
		ret = -EIOCBQUEUED;
	spin_unlock_irq(&q->lock);
	वापस ret;
पूर्ण

/*
 * Return values:
 * 1 - page is locked; mmap_lock is still held.
 * 0 - page is not locked.
 *     mmap_lock has been released (mmap_पढ़ो_unlock(), unless flags had both
 *     FAULT_FLAG_ALLOW_RETRY and FAULT_FLAG_RETRY_NOWAIT set, in
 *     which हाल mmap_lock is still held.
 *
 * If neither ALLOW_RETRY nor KILLABLE are set, will always वापस 1
 * with the page locked and the mmap_lock unperturbed.
 */
पूर्णांक __lock_page_or_retry(काष्ठा page *page, काष्ठा mm_काष्ठा *mm,
			 अचिन्हित पूर्णांक flags)
अणु
	अगर (fault_flag_allow_retry_first(flags)) अणु
		/*
		 * CAUTION! In this हाल, mmap_lock is not released
		 * even though वापस 0.
		 */
		अगर (flags & FAULT_FLAG_RETRY_NOWAIT)
			वापस 0;

		mmap_पढ़ो_unlock(mm);
		अगर (flags & FAULT_FLAG_KILLABLE)
			रुको_on_page_locked_समाप्तable(page);
		अन्यथा
			रुको_on_page_locked(page);
		वापस 0;
	पूर्ण
	अगर (flags & FAULT_FLAG_KILLABLE) अणु
		पूर्णांक ret;

		ret = __lock_page_समाप्तable(page);
		अगर (ret) अणु
			mmap_पढ़ो_unlock(mm);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		__lock_page(page);
	पूर्ण
	वापस 1;

पूर्ण

/**
 * page_cache_next_miss() - Find the next gap in the page cache.
 * @mapping: Mapping.
 * @index: Index.
 * @max_scan: Maximum range to search.
 *
 * Search the range [index, min(index + max_scan - 1, अच_दीर्घ_उच्च)] क्रम the
 * gap with the lowest index.
 *
 * This function may be called under the rcu_पढ़ो_lock.  However, this will
 * not atomically search a snapshot of the cache at a single poपूर्णांक in समय.
 * For example, अगर a gap is created at index 5, then subsequently a gap is
 * created at index 10, page_cache_next_miss covering both indices may
 * वापस 10 अगर called under the rcu_पढ़ो_lock.
 *
 * Return: The index of the gap अगर found, otherwise an index outside the
 * range specअगरied (in which हाल 'return - index >= max_scan' will be true).
 * In the rare हाल of index wrap-around, 0 will be वापसed.
 */
pgoff_t page_cache_next_miss(काष्ठा address_space *mapping,
			     pgoff_t index, अचिन्हित दीर्घ max_scan)
अणु
	XA_STATE(xas, &mapping->i_pages, index);

	जबतक (max_scan--) अणु
		व्योम *entry = xas_next(&xas);
		अगर (!entry || xa_is_value(entry))
			अवरोध;
		अगर (xas.xa_index == 0)
			अवरोध;
	पूर्ण

	वापस xas.xa_index;
पूर्ण
EXPORT_SYMBOL(page_cache_next_miss);

/**
 * page_cache_prev_miss() - Find the previous gap in the page cache.
 * @mapping: Mapping.
 * @index: Index.
 * @max_scan: Maximum range to search.
 *
 * Search the range [max(index - max_scan + 1, 0), index] क्रम the
 * gap with the highest index.
 *
 * This function may be called under the rcu_पढ़ो_lock.  However, this will
 * not atomically search a snapshot of the cache at a single poपूर्णांक in समय.
 * For example, अगर a gap is created at index 10, then subsequently a gap is
 * created at index 5, page_cache_prev_miss() covering both indices may
 * वापस 5 अगर called under the rcu_पढ़ो_lock.
 *
 * Return: The index of the gap अगर found, otherwise an index outside the
 * range specअगरied (in which हाल 'index - return >= max_scan' will be true).
 * In the rare हाल of wrap-around, अच_दीर्घ_उच्च will be वापसed.
 */
pgoff_t page_cache_prev_miss(काष्ठा address_space *mapping,
			     pgoff_t index, अचिन्हित दीर्घ max_scan)
अणु
	XA_STATE(xas, &mapping->i_pages, index);

	जबतक (max_scan--) अणु
		व्योम *entry = xas_prev(&xas);
		अगर (!entry || xa_is_value(entry))
			अवरोध;
		अगर (xas.xa_index == अच_दीर्घ_उच्च)
			अवरोध;
	पूर्ण

	वापस xas.xa_index;
पूर्ण
EXPORT_SYMBOL(page_cache_prev_miss);

/*
 * mapping_get_entry - Get a page cache entry.
 * @mapping: the address_space to search
 * @index: The page cache index.
 *
 * Looks up the page cache slot at @mapping & @index.  If there is a
 * page cache page, the head page is वापसed with an increased refcount.
 *
 * If the slot holds a shaकरोw entry of a previously evicted page, or a
 * swap entry from shmem/पंचांगpfs, it is वापसed.
 *
 * Return: The head page or shaकरोw entry, %शून्य अगर nothing is found.
 */
अटल काष्ठा page *mapping_get_entry(काष्ठा address_space *mapping,
		pgoff_t index)
अणु
	XA_STATE(xas, &mapping->i_pages, index);
	काष्ठा page *page;

	rcu_पढ़ो_lock();
repeat:
	xas_reset(&xas);
	page = xas_load(&xas);
	अगर (xas_retry(&xas, page))
		जाओ repeat;
	/*
	 * A shaकरोw entry of a recently evicted page, or a swap entry from
	 * shmem/पंचांगpfs.  Return it without attempting to उठाओ page count.
	 */
	अगर (!page || xa_is_value(page))
		जाओ out;

	अगर (!page_cache_get_speculative(page))
		जाओ repeat;

	/*
	 * Has the page moved or been split?
	 * This is part of the lockless pagecache protocol. See
	 * include/linux/pagemap.h क्रम details.
	 */
	अगर (unlikely(page != xas_reload(&xas))) अणु
		put_page(page);
		जाओ repeat;
	पूर्ण
out:
	rcu_पढ़ो_unlock();

	वापस page;
पूर्ण

/**
 * pagecache_get_page - Find and get a reference to a page.
 * @mapping: The address_space to search.
 * @index: The page index.
 * @fgp_flags: %FGP flags modअगरy how the page is वापसed.
 * @gfp_mask: Memory allocation flags to use अगर %FGP_CREAT is specअगरied.
 *
 * Looks up the page cache entry at @mapping & @index.
 *
 * @fgp_flags can be zero or more of these flags:
 *
 * * %FGP_ACCESSED - The page will be marked accessed.
 * * %FGP_LOCK - The page is वापसed locked.
 * * %FGP_HEAD - If the page is present and a THP, वापस the head page
 *   rather than the exact page specअगरied by the index.
 * * %FGP_ENTRY - If there is a shaकरोw / swap / DAX entry, वापस it
 *   instead of allocating a new page to replace it.
 * * %FGP_CREAT - If no page is present then a new page is allocated using
 *   @gfp_mask and added to the page cache and the VM's LRU list.
 *   The page is वापसed locked and with an increased refcount.
 * * %FGP_FOR_MMAP - The caller wants to करो its own locking dance अगर the
 *   page is alपढ़ोy in cache.  If the page was allocated, unlock it beक्रमe
 *   वापसing so the caller can करो the same dance.
 * * %FGP_WRITE - The page will be written
 * * %FGP_NOFS - __GFP_FS will get cleared in gfp mask
 * * %FGP_NOWAIT - Don't get blocked by page lock
 *
 * If %FGP_LOCK or %FGP_CREAT are specअगरied then the function may sleep even
 * अगर the %GFP flags specअगरied क्रम %FGP_CREAT are atomic.
 *
 * If there is a page cache page, it is वापसed with an increased refcount.
 *
 * Return: The found page or %शून्य otherwise.
 */
काष्ठा page *pagecache_get_page(काष्ठा address_space *mapping, pgoff_t index,
		पूर्णांक fgp_flags, gfp_t gfp_mask)
अणु
	काष्ठा page *page;

repeat:
	page = mapping_get_entry(mapping, index);
	अगर (xa_is_value(page)) अणु
		अगर (fgp_flags & FGP_ENTRY)
			वापस page;
		page = शून्य;
	पूर्ण
	अगर (!page)
		जाओ no_page;

	अगर (fgp_flags & FGP_LOCK) अणु
		अगर (fgp_flags & FGP_NOWAIT) अणु
			अगर (!trylock_page(page)) अणु
				put_page(page);
				वापस शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			lock_page(page);
		पूर्ण

		/* Has the page been truncated? */
		अगर (unlikely(page->mapping != mapping)) अणु
			unlock_page(page);
			put_page(page);
			जाओ repeat;
		पूर्ण
		VM_BUG_ON_PAGE(!thp_contains(page, index), page);
	पूर्ण

	अगर (fgp_flags & FGP_ACCESSED)
		mark_page_accessed(page);
	अन्यथा अगर (fgp_flags & FGP_WRITE) अणु
		/* Clear idle flag क्रम buffer ग_लिखो */
		अगर (page_is_idle(page))
			clear_page_idle(page);
	पूर्ण
	अगर (!(fgp_flags & FGP_HEAD))
		page = find_subpage(page, index);

no_page:
	अगर (!page && (fgp_flags & FGP_CREAT)) अणु
		पूर्णांक err;
		अगर ((fgp_flags & FGP_WRITE) && mapping_can_ग_लिखोback(mapping))
			gfp_mask |= __GFP_WRITE;
		अगर (fgp_flags & FGP_NOFS)
			gfp_mask &= ~__GFP_FS;

		page = __page_cache_alloc(gfp_mask);
		अगर (!page)
			वापस शून्य;

		अगर (WARN_ON_ONCE(!(fgp_flags & (FGP_LOCK | FGP_FOR_MMAP))))
			fgp_flags |= FGP_LOCK;

		/* Init accessed so aव्योम atomic mark_page_accessed later */
		अगर (fgp_flags & FGP_ACCESSED)
			__SetPageReferenced(page);

		err = add_to_page_cache_lru(page, mapping, index, gfp_mask);
		अगर (unlikely(err)) अणु
			put_page(page);
			page = शून्य;
			अगर (err == -EEXIST)
				जाओ repeat;
		पूर्ण

		/*
		 * add_to_page_cache_lru locks the page, and क्रम mmap we expect
		 * an unlocked page.
		 */
		अगर (page && (fgp_flags & FGP_FOR_MMAP))
			unlock_page(page);
	पूर्ण

	वापस page;
पूर्ण
EXPORT_SYMBOL(pagecache_get_page);

अटल अंतरभूत काष्ठा page *find_get_entry(काष्ठा xa_state *xas, pgoff_t max,
		xa_mark_t mark)
अणु
	काष्ठा page *page;

retry:
	अगर (mark == XA_PRESENT)
		page = xas_find(xas, max);
	अन्यथा
		page = xas_find_marked(xas, max, mark);

	अगर (xas_retry(xas, page))
		जाओ retry;
	/*
	 * A shaकरोw entry of a recently evicted page, a swap
	 * entry from shmem/पंचांगpfs or a DAX entry.  Return it
	 * without attempting to उठाओ page count.
	 */
	अगर (!page || xa_is_value(page))
		वापस page;

	अगर (!page_cache_get_speculative(page))
		जाओ reset;

	/* Has the page moved or been split? */
	अगर (unlikely(page != xas_reload(xas))) अणु
		put_page(page);
		जाओ reset;
	पूर्ण

	वापस page;
reset:
	xas_reset(xas);
	जाओ retry;
पूर्ण

/**
 * find_get_entries - gang pagecache lookup
 * @mapping:	The address_space to search
 * @start:	The starting page cache index
 * @end:	The final page index (inclusive).
 * @pvec:	Where the resulting entries are placed.
 * @indices:	The cache indices corresponding to the entries in @entries
 *
 * find_get_entries() will search क्रम and वापस a batch of entries in
 * the mapping.  The entries are placed in @pvec.  find_get_entries()
 * takes a reference on any actual pages it वापसs.
 *
 * The search वापसs a group of mapping-contiguous page cache entries
 * with ascending indexes.  There may be holes in the indices due to
 * not-present pages.
 *
 * Any shaकरोw entries of evicted pages, or swap entries from
 * shmem/पंचांगpfs, are included in the वापसed array.
 *
 * If it finds a Transparent Huge Page, head or tail, find_get_entries()
 * stops at that page: the caller is likely to have a better way to handle
 * the compound page as a whole, and then skip its extent, than repeatedly
 * calling find_get_entries() to वापस all its tails.
 *
 * Return: the number of pages and shaकरोw entries which were found.
 */
अचिन्हित find_get_entries(काष्ठा address_space *mapping, pgoff_t start,
		pgoff_t end, काष्ठा pagevec *pvec, pgoff_t *indices)
अणु
	XA_STATE(xas, &mapping->i_pages, start);
	काष्ठा page *page;
	अचिन्हित पूर्णांक ret = 0;
	अचिन्हित nr_entries = PAGEVEC_SIZE;

	rcu_पढ़ो_lock();
	जबतक ((page = find_get_entry(&xas, end, XA_PRESENT))) अणु
		/*
		 * Terminate early on finding a THP, to allow the caller to
		 * handle it all at once; but जारी अगर this is hugetlbfs.
		 */
		अगर (!xa_is_value(page) && PageTransHuge(page) &&
				!PageHuge(page)) अणु
			page = find_subpage(page, xas.xa_index);
			nr_entries = ret + 1;
		पूर्ण

		indices[ret] = xas.xa_index;
		pvec->pages[ret] = page;
		अगर (++ret == nr_entries)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	pvec->nr = ret;
	वापस ret;
पूर्ण

/**
 * find_lock_entries - Find a batch of pagecache entries.
 * @mapping:	The address_space to search.
 * @start:	The starting page cache index.
 * @end:	The final page index (inclusive).
 * @pvec:	Where the resulting entries are placed.
 * @indices:	The cache indices of the entries in @pvec.
 *
 * find_lock_entries() will वापस a batch of entries from @mapping.
 * Swap, shaकरोw and DAX entries are included.  Pages are वापसed
 * locked and with an incremented refcount.  Pages which are locked by
 * somebody अन्यथा or under ग_लिखोback are skipped.  Only the head page of
 * a THP is वापसed.  Pages which are partially outside the range are
 * not वापसed.
 *
 * The entries have ascending indexes.  The indices may not be consecutive
 * due to not-present entries, THP pages, pages which could not be locked
 * or pages under ग_लिखोback.
 *
 * Return: The number of entries which were found.
 */
अचिन्हित find_lock_entries(काष्ठा address_space *mapping, pgoff_t start,
		pgoff_t end, काष्ठा pagevec *pvec, pgoff_t *indices)
अणु
	XA_STATE(xas, &mapping->i_pages, start);
	काष्ठा page *page;

	rcu_पढ़ो_lock();
	जबतक ((page = find_get_entry(&xas, end, XA_PRESENT))) अणु
		अगर (!xa_is_value(page)) अणु
			अगर (page->index < start)
				जाओ put;
			VM_BUG_ON_PAGE(page->index != xas.xa_index, page);
			अगर (page->index + thp_nr_pages(page) - 1 > end)
				जाओ put;
			अगर (!trylock_page(page))
				जाओ put;
			अगर (page->mapping != mapping || PageWriteback(page))
				जाओ unlock;
			VM_BUG_ON_PAGE(!thp_contains(page, xas.xa_index),
					page);
		पूर्ण
		indices[pvec->nr] = xas.xa_index;
		अगर (!pagevec_add(pvec, page))
			अवरोध;
		जाओ next;
unlock:
		unlock_page(page);
put:
		put_page(page);
next:
		अगर (!xa_is_value(page) && PageTransHuge(page)) अणु
			अचिन्हित पूर्णांक nr_pages = thp_nr_pages(page);

			/* Final THP may cross MAX_LFS_खाताSIZE on 32-bit */
			xas_set(&xas, page->index + nr_pages);
			अगर (xas.xa_index < nr_pages)
				अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस pagevec_count(pvec);
पूर्ण

/**
 * find_get_pages_range - gang pagecache lookup
 * @mapping:	The address_space to search
 * @start:	The starting page index
 * @end:	The final page index (inclusive)
 * @nr_pages:	The maximum number of pages
 * @pages:	Where the resulting pages are placed
 *
 * find_get_pages_range() will search क्रम and वापस a group of up to @nr_pages
 * pages in the mapping starting at index @start and up to index @end
 * (inclusive).  The pages are placed at @pages.  find_get_pages_range() takes
 * a reference against the वापसed pages.
 *
 * The search वापसs a group of mapping-contiguous pages with ascending
 * indexes.  There may be holes in the indices due to not-present pages.
 * We also update @start to index the next page क्रम the traversal.
 *
 * Return: the number of pages which were found. If this number is
 * smaller than @nr_pages, the end of specअगरied range has been
 * reached.
 */
अचिन्हित find_get_pages_range(काष्ठा address_space *mapping, pgoff_t *start,
			      pgoff_t end, अचिन्हित पूर्णांक nr_pages,
			      काष्ठा page **pages)
अणु
	XA_STATE(xas, &mapping->i_pages, *start);
	काष्ठा page *page;
	अचिन्हित ret = 0;

	अगर (unlikely(!nr_pages))
		वापस 0;

	rcu_पढ़ो_lock();
	जबतक ((page = find_get_entry(&xas, end, XA_PRESENT))) अणु
		/* Skip over shaकरोw, swap and DAX entries */
		अगर (xa_is_value(page))
			जारी;

		pages[ret] = find_subpage(page, xas.xa_index);
		अगर (++ret == nr_pages) अणु
			*start = xas.xa_index + 1;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * We come here when there is no page beyond @end. We take care to not
	 * overflow the index @start as it confuses some of the callers. This
	 * अवरोधs the iteration when there is a page at index -1 but that is
	 * alपढ़ोy broken anyway.
	 */
	अगर (end == (pgoff_t)-1)
		*start = (pgoff_t)-1;
	अन्यथा
		*start = end + 1;
out:
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/**
 * find_get_pages_contig - gang contiguous pagecache lookup
 * @mapping:	The address_space to search
 * @index:	The starting page index
 * @nr_pages:	The maximum number of pages
 * @pages:	Where the resulting pages are placed
 *
 * find_get_pages_contig() works exactly like find_get_pages(), except
 * that the वापसed number of pages are guaranteed to be contiguous.
 *
 * Return: the number of pages which were found.
 */
अचिन्हित find_get_pages_contig(काष्ठा address_space *mapping, pgoff_t index,
			       अचिन्हित पूर्णांक nr_pages, काष्ठा page **pages)
अणु
	XA_STATE(xas, &mapping->i_pages, index);
	काष्ठा page *page;
	अचिन्हित पूर्णांक ret = 0;

	अगर (unlikely(!nr_pages))
		वापस 0;

	rcu_पढ़ो_lock();
	क्रम (page = xas_load(&xas); page; page = xas_next(&xas)) अणु
		अगर (xas_retry(&xas, page))
			जारी;
		/*
		 * If the entry has been swapped out, we can stop looking.
		 * No current caller is looking क्रम DAX entries.
		 */
		अगर (xa_is_value(page))
			अवरोध;

		अगर (!page_cache_get_speculative(page))
			जाओ retry;

		/* Has the page moved or been split? */
		अगर (unlikely(page != xas_reload(&xas)))
			जाओ put_page;

		pages[ret] = find_subpage(page, xas.xa_index);
		अगर (++ret == nr_pages)
			अवरोध;
		जारी;
put_page:
		put_page(page);
retry:
		xas_reset(&xas);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL(find_get_pages_contig);

/**
 * find_get_pages_range_tag - Find and वापस head pages matching @tag.
 * @mapping:	the address_space to search
 * @index:	the starting page index
 * @end:	The final page index (inclusive)
 * @tag:	the tag index
 * @nr_pages:	the maximum number of pages
 * @pages:	where the resulting pages are placed
 *
 * Like find_get_pages(), except we only वापस head pages which are tagged
 * with @tag.  @index is updated to the index immediately after the last
 * page we वापस, पढ़ोy क्रम the next iteration.
 *
 * Return: the number of pages which were found.
 */
अचिन्हित find_get_pages_range_tag(काष्ठा address_space *mapping, pgoff_t *index,
			pgoff_t end, xa_mark_t tag, अचिन्हित पूर्णांक nr_pages,
			काष्ठा page **pages)
अणु
	XA_STATE(xas, &mapping->i_pages, *index);
	काष्ठा page *page;
	अचिन्हित ret = 0;

	अगर (unlikely(!nr_pages))
		वापस 0;

	rcu_पढ़ो_lock();
	जबतक ((page = find_get_entry(&xas, end, tag))) अणु
		/*
		 * Shaकरोw entries should never be tagged, but this iteration
		 * is lockless so there is a winकरोw क्रम page reclaim to evict
		 * a page we saw tagged.  Skip over it.
		 */
		अगर (xa_is_value(page))
			जारी;

		pages[ret] = page;
		अगर (++ret == nr_pages) अणु
			*index = page->index + thp_nr_pages(page);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * We come here when we got to @end. We take care to not overflow the
	 * index @index as it confuses some of the callers. This अवरोधs the
	 * iteration when there is a page at index -1 but that is alपढ़ोy
	 * broken anyway.
	 */
	अगर (end == (pgoff_t)-1)
		*index = (pgoff_t)-1;
	अन्यथा
		*index = end + 1;
out:
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(find_get_pages_range_tag);

/*
 * CD/DVDs are error prone. When a medium error occurs, the driver may fail
 * a _large_ part of the i/o request. Imagine the worst scenario:
 *
 *      ---R__________________________________________B__________
 *         ^ पढ़ोing here                             ^ bad block(assume 4k)
 *
 * पढ़ो(R) => miss => पढ़ोahead(R...B) => media error => frustrating retries
 * => failing the whole request => पढ़ो(R) => पढ़ो(R+1) =>
 * पढ़ोahead(R+1...B+1) => bang => पढ़ो(R+2) => पढ़ो(R+3) =>
 * पढ़ोahead(R+3...B+2) => bang => पढ़ो(R+3) => पढ़ो(R+4) =>
 * पढ़ोahead(R+4...B+3) => bang => पढ़ो(R+4) => पढ़ो(R+5) => ......
 *
 * It is going insane. Fix it by quickly scaling करोwn the पढ़ोahead size.
 */
अटल व्योम shrink_पढ़ोahead_size_eio(काष्ठा file_ra_state *ra)
अणु
	ra->ra_pages /= 4;
पूर्ण

/*
 * filemap_get_पढ़ो_batch - Get a batch of pages क्रम पढ़ो
 *
 * Get a batch of pages which represent a contiguous range of bytes
 * in the file.  No tail pages will be वापसed.  If @index is in the
 * middle of a THP, the entire THP will be वापसed.  The last page in
 * the batch may have Readahead set or be not Uptodate so that the
 * caller can take the appropriate action.
 */
अटल व्योम filemap_get_पढ़ो_batch(काष्ठा address_space *mapping,
		pgoff_t index, pgoff_t max, काष्ठा pagevec *pvec)
अणु
	XA_STATE(xas, &mapping->i_pages, index);
	काष्ठा page *head;

	rcu_पढ़ो_lock();
	क्रम (head = xas_load(&xas); head; head = xas_next(&xas)) अणु
		अगर (xas_retry(&xas, head))
			जारी;
		अगर (xas.xa_index > max || xa_is_value(head))
			अवरोध;
		अगर (!page_cache_get_speculative(head))
			जाओ retry;

		/* Has the page moved or been split? */
		अगर (unlikely(head != xas_reload(&xas)))
			जाओ put_page;

		अगर (!pagevec_add(pvec, head))
			अवरोध;
		अगर (!PageUptodate(head))
			अवरोध;
		अगर (PageReadahead(head))
			अवरोध;
		xas.xa_index = head->index + thp_nr_pages(head) - 1;
		xas.xa_offset = (xas.xa_index >> xas.xa_shअगरt) & XA_CHUNK_MASK;
		जारी;
put_page:
		put_page(head);
retry:
		xas_reset(&xas);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक filemap_पढ़ो_page(काष्ठा file *file, काष्ठा address_space *mapping,
		काष्ठा page *page)
अणु
	पूर्णांक error;

	/*
	 * A previous I/O error may have been due to temporary failures,
	 * eg. multipath errors.  PG_error will be set again अगर पढ़ोpage
	 * fails.
	 */
	ClearPageError(page);
	/* Start the actual पढ़ो. The पढ़ो will unlock the page. */
	error = mapping->a_ops->पढ़ोpage(file, page);
	अगर (error)
		वापस error;

	error = रुको_on_page_locked_समाप्तable(page);
	अगर (error)
		वापस error;
	अगर (PageUptodate(page))
		वापस 0;
	shrink_पढ़ोahead_size_eio(&file->f_ra);
	वापस -EIO;
पूर्ण

अटल bool filemap_range_uptodate(काष्ठा address_space *mapping,
		loff_t pos, काष्ठा iov_iter *iter, काष्ठा page *page)
अणु
	पूर्णांक count;

	अगर (PageUptodate(page))
		वापस true;
	/* pipes can't handle partially uptodate pages */
	अगर (iov_iter_is_pipe(iter))
		वापस false;
	अगर (!mapping->a_ops->is_partially_uptodate)
		वापस false;
	अगर (mapping->host->i_blkbits >= (PAGE_SHIFT + thp_order(page)))
		वापस false;

	count = iter->count;
	अगर (page_offset(page) > pos) अणु
		count -= page_offset(page) - pos;
		pos = 0;
	पूर्ण अन्यथा अणु
		pos -= page_offset(page);
	पूर्ण

	वापस mapping->a_ops->is_partially_uptodate(page, pos, count);
पूर्ण

अटल पूर्णांक filemap_update_page(काष्ठा kiocb *iocb,
		काष्ठा address_space *mapping, काष्ठा iov_iter *iter,
		काष्ठा page *page)
अणु
	पूर्णांक error;

	अगर (!trylock_page(page)) अणु
		अगर (iocb->ki_flags & (IOCB_NOWAIT | IOCB_NOIO))
			वापस -EAGAIN;
		अगर (!(iocb->ki_flags & IOCB_WAITQ)) अणु
			put_and_रुको_on_page_locked(page, TASK_KILLABLE);
			वापस AOP_TRUNCATED_PAGE;
		पूर्ण
		error = __lock_page_async(page, iocb->ki_रुकोq);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (!page->mapping)
		जाओ truncated;

	error = 0;
	अगर (filemap_range_uptodate(mapping, iocb->ki_pos, iter, page))
		जाओ unlock;

	error = -EAGAIN;
	अगर (iocb->ki_flags & (IOCB_NOIO | IOCB_NOWAIT | IOCB_WAITQ))
		जाओ unlock;

	error = filemap_पढ़ो_page(iocb->ki_filp, mapping, page);
	अगर (error == AOP_TRUNCATED_PAGE)
		put_page(page);
	वापस error;
truncated:
	unlock_page(page);
	put_page(page);
	वापस AOP_TRUNCATED_PAGE;
unlock:
	unlock_page(page);
	वापस error;
पूर्ण

अटल पूर्णांक filemap_create_page(काष्ठा file *file,
		काष्ठा address_space *mapping, pgoff_t index,
		काष्ठा pagevec *pvec)
अणु
	काष्ठा page *page;
	पूर्णांक error;

	page = page_cache_alloc(mapping);
	अगर (!page)
		वापस -ENOMEM;

	error = add_to_page_cache_lru(page, mapping, index,
			mapping_gfp_स्थिरraपूर्णांक(mapping, GFP_KERNEL));
	अगर (error == -EEXIST)
		error = AOP_TRUNCATED_PAGE;
	अगर (error)
		जाओ error;

	error = filemap_पढ़ो_page(file, mapping, page);
	अगर (error)
		जाओ error;

	pagevec_add(pvec, page);
	वापस 0;
error:
	put_page(page);
	वापस error;
पूर्ण

अटल पूर्णांक filemap_पढ़ोahead(काष्ठा kiocb *iocb, काष्ठा file *file,
		काष्ठा address_space *mapping, काष्ठा page *page,
		pgoff_t last_index)
अणु
	अगर (iocb->ki_flags & IOCB_NOIO)
		वापस -EAGAIN;
	page_cache_async_पढ़ोahead(mapping, &file->f_ra, file, page,
			page->index, last_index - page->index);
	वापस 0;
पूर्ण

अटल पूर्णांक filemap_get_pages(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter,
		काष्ठा pagevec *pvec)
अणु
	काष्ठा file *filp = iocb->ki_filp;
	काष्ठा address_space *mapping = filp->f_mapping;
	काष्ठा file_ra_state *ra = &filp->f_ra;
	pgoff_t index = iocb->ki_pos >> PAGE_SHIFT;
	pgoff_t last_index;
	काष्ठा page *page;
	पूर्णांक err = 0;

	last_index = DIV_ROUND_UP(iocb->ki_pos + iter->count, PAGE_SIZE);
retry:
	अगर (fatal_संकेत_pending(current))
		वापस -EINTR;

	filemap_get_पढ़ो_batch(mapping, index, last_index, pvec);
	अगर (!pagevec_count(pvec)) अणु
		अगर (iocb->ki_flags & IOCB_NOIO)
			वापस -EAGAIN;
		page_cache_sync_पढ़ोahead(mapping, ra, filp, index,
				last_index - index);
		filemap_get_पढ़ो_batch(mapping, index, last_index, pvec);
	पूर्ण
	अगर (!pagevec_count(pvec)) अणु
		अगर (iocb->ki_flags & (IOCB_NOWAIT | IOCB_WAITQ))
			वापस -EAGAIN;
		err = filemap_create_page(filp, mapping,
				iocb->ki_pos >> PAGE_SHIFT, pvec);
		अगर (err == AOP_TRUNCATED_PAGE)
			जाओ retry;
		वापस err;
	पूर्ण

	page = pvec->pages[pagevec_count(pvec) - 1];
	अगर (PageReadahead(page)) अणु
		err = filemap_पढ़ोahead(iocb, filp, mapping, page, last_index);
		अगर (err)
			जाओ err;
	पूर्ण
	अगर (!PageUptodate(page)) अणु
		अगर ((iocb->ki_flags & IOCB_WAITQ) && pagevec_count(pvec) > 1)
			iocb->ki_flags |= IOCB_NOWAIT;
		err = filemap_update_page(iocb, mapping, iter, page);
		अगर (err)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	अगर (err < 0)
		put_page(page);
	अगर (likely(--pvec->nr))
		वापस 0;
	अगर (err == AOP_TRUNCATED_PAGE)
		जाओ retry;
	वापस err;
पूर्ण

/**
 * filemap_पढ़ो - Read data from the page cache.
 * @iocb: The iocb to पढ़ो.
 * @iter: Destination क्रम the data.
 * @alपढ़ोy_पढ़ो: Number of bytes alपढ़ोy पढ़ो by the caller.
 *
 * Copies data from the page cache.  If the data is not currently present,
 * uses the पढ़ोahead and पढ़ोpage address_space operations to fetch it.
 *
 * Return: Total number of bytes copied, including those alपढ़ोy पढ़ो by
 * the caller.  If an error happens beक्रमe any bytes are copied, वापसs
 * a negative error number.
 */
sमाप_प्रकार filemap_पढ़ो(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter,
		sमाप_प्रकार alपढ़ोy_पढ़ो)
अणु
	काष्ठा file *filp = iocb->ki_filp;
	काष्ठा file_ra_state *ra = &filp->f_ra;
	काष्ठा address_space *mapping = filp->f_mapping;
	काष्ठा inode *inode = mapping->host;
	काष्ठा pagevec pvec;
	पूर्णांक i, error = 0;
	bool writably_mapped;
	loff_t isize, end_offset;

	अगर (unlikely(iocb->ki_pos >= inode->i_sb->s_maxbytes))
		वापस 0;
	अगर (unlikely(!iov_iter_count(iter)))
		वापस 0;

	iov_iter_truncate(iter, inode->i_sb->s_maxbytes);
	pagevec_init(&pvec);

	करो अणु
		cond_resched();

		/*
		 * If we've alपढ़ोy successfully copied some data, then we
		 * can no दीर्घer safely वापस -EIOCBQUEUED. Hence mark
		 * an async पढ़ो NOWAIT at that poपूर्णांक.
		 */
		अगर ((iocb->ki_flags & IOCB_WAITQ) && alपढ़ोy_पढ़ो)
			iocb->ki_flags |= IOCB_NOWAIT;

		error = filemap_get_pages(iocb, iter, &pvec);
		अगर (error < 0)
			अवरोध;

		/*
		 * i_size must be checked after we know the pages are Uptodate.
		 *
		 * Checking i_size after the check allows us to calculate
		 * the correct value क्रम "nr", which means the zero-filled
		 * part of the page is not copied back to userspace (unless
		 * another truncate extends the file - this is desired though).
		 */
		isize = i_size_पढ़ो(inode);
		अगर (unlikely(iocb->ki_pos >= isize))
			जाओ put_pages;
		end_offset = min_t(loff_t, isize, iocb->ki_pos + iter->count);

		/*
		 * Once we start copying data, we करोn't want to be touching any
		 * cachelines that might be contended:
		 */
		writably_mapped = mapping_writably_mapped(mapping);

		/*
		 * When a sequential पढ़ो accesses a page several बार, only
		 * mark it as accessed the first समय.
		 */
		अगर (iocb->ki_pos >> PAGE_SHIFT !=
		    ra->prev_pos >> PAGE_SHIFT)
			mark_page_accessed(pvec.pages[0]);

		क्रम (i = 0; i < pagevec_count(&pvec); i++) अणु
			काष्ठा page *page = pvec.pages[i];
			माप_प्रकार page_size = thp_size(page);
			माप_प्रकार offset = iocb->ki_pos & (page_size - 1);
			माप_प्रकार bytes = min_t(loff_t, end_offset - iocb->ki_pos,
					     page_size - offset);
			माप_प्रकार copied;

			अगर (end_offset < page_offset(page))
				अवरोध;
			अगर (i > 0)
				mark_page_accessed(page);
			/*
			 * If users can be writing to this page using arbitrary
			 * भव addresses, take care about potential aliasing
			 * beक्रमe पढ़ोing the page on the kernel side.
			 */
			अगर (writably_mapped) अणु
				पूर्णांक j;

				क्रम (j = 0; j < thp_nr_pages(page); j++)
					flush_dcache_page(page + j);
			पूर्ण

			copied = copy_page_to_iter(page, offset, bytes, iter);

			alपढ़ोy_पढ़ो += copied;
			iocb->ki_pos += copied;
			ra->prev_pos = iocb->ki_pos;

			अगर (copied < bytes) अणु
				error = -EFAULT;
				अवरोध;
			पूर्ण
		पूर्ण
put_pages:
		क्रम (i = 0; i < pagevec_count(&pvec); i++)
			put_page(pvec.pages[i]);
		pagevec_reinit(&pvec);
	पूर्ण जबतक (iov_iter_count(iter) && iocb->ki_pos < isize && !error);

	file_accessed(filp);

	वापस alपढ़ोy_पढ़ो ? alपढ़ोy_पढ़ो : error;
पूर्ण
EXPORT_SYMBOL_GPL(filemap_पढ़ो);

/**
 * generic_file_पढ़ो_iter - generic fileप्रणाली पढ़ो routine
 * @iocb:	kernel I/O control block
 * @iter:	destination क्रम the data पढ़ो
 *
 * This is the "read_iter()" routine क्रम all fileप्रणालीs
 * that can use the page cache directly.
 *
 * The IOCB_NOWAIT flag in iocb->ki_flags indicates that -EAGAIN shall
 * be वापसed when no data can be पढ़ो without रुकोing क्रम I/O requests
 * to complete; it करोesn't prevent पढ़ोahead.
 *
 * The IOCB_NOIO flag in iocb->ki_flags indicates that no new I/O
 * requests shall be made क्रम the पढ़ो or क्रम पढ़ोahead.  When no data
 * can be पढ़ो, -EAGAIN shall be वापसed.  When पढ़ोahead would be
 * triggered, a partial, possibly empty पढ़ो shall be वापसed.
 *
 * Return:
 * * number of bytes copied, even क्रम partial पढ़ोs
 * * negative error code (or 0 अगर IOCB_NOIO) अगर nothing was पढ़ो
 */
sमाप_प्रकार
generic_file_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	माप_प्रकार count = iov_iter_count(iter);
	sमाप_प्रकार retval = 0;

	अगर (!count)
		वापस 0; /* skip aसमय */

	अगर (iocb->ki_flags & IOCB_सूचीECT) अणु
		काष्ठा file *file = iocb->ki_filp;
		काष्ठा address_space *mapping = file->f_mapping;
		काष्ठा inode *inode = mapping->host;
		loff_t size;

		size = i_size_पढ़ो(inode);
		अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
			अगर (filemap_range_needs_ग_लिखोback(mapping, iocb->ki_pos,
						iocb->ki_pos + count - 1))
				वापस -EAGAIN;
		पूर्ण अन्यथा अणु
			retval = filemap_ग_लिखो_and_रुको_range(mapping,
						iocb->ki_pos,
					        iocb->ki_pos + count - 1);
			अगर (retval < 0)
				वापस retval;
		पूर्ण

		file_accessed(file);

		retval = mapping->a_ops->direct_IO(iocb, iter);
		अगर (retval >= 0) अणु
			iocb->ki_pos += retval;
			count -= retval;
		पूर्ण
		अगर (retval != -EIOCBQUEUED)
			iov_iter_revert(iter, count - iov_iter_count(iter));

		/*
		 * Btrfs can have a लघु DIO पढ़ो अगर we encounter
		 * compressed extents, so अगर there was an error, or अगर
		 * we've alपढ़ोy पढ़ो everything we wanted to, or अगर
		 * there was a लघु पढ़ो because we hit खातापूर्ण, go ahead
		 * and वापस.  Otherwise fallthrough to buffered io क्रम
		 * the rest of the पढ़ो.  Buffered पढ़ोs will not work क्रम
		 * DAX files, so करोn't bother trying.
		 */
		अगर (retval < 0 || !count || iocb->ki_pos >= size ||
		    IS_DAX(inode))
			वापस retval;
	पूर्ण

	वापस filemap_पढ़ो(iocb, iter, retval);
पूर्ण
EXPORT_SYMBOL(generic_file_पढ़ो_iter);

अटल अंतरभूत loff_t page_seek_hole_data(काष्ठा xa_state *xas,
		काष्ठा address_space *mapping, काष्ठा page *page,
		loff_t start, loff_t end, bool seek_data)
अणु
	स्थिर काष्ठा address_space_operations *ops = mapping->a_ops;
	माप_प्रकार offset, bsz = i_blocksize(mapping->host);

	अगर (xa_is_value(page) || PageUptodate(page))
		वापस seek_data ? start : end;
	अगर (!ops->is_partially_uptodate)
		वापस seek_data ? end : start;

	xas_छोड़ो(xas);
	rcu_पढ़ो_unlock();
	lock_page(page);
	अगर (unlikely(page->mapping != mapping))
		जाओ unlock;

	offset = offset_in_thp(page, start) & ~(bsz - 1);

	करो अणु
		अगर (ops->is_partially_uptodate(page, offset, bsz) == seek_data)
			अवरोध;
		start = (start + bsz) & ~(bsz - 1);
		offset += bsz;
	पूर्ण जबतक (offset < thp_size(page));
unlock:
	unlock_page(page);
	rcu_पढ़ो_lock();
	वापस start;
पूर्ण

अटल अंतरभूत
अचिन्हित पूर्णांक seek_page_size(काष्ठा xa_state *xas, काष्ठा page *page)
अणु
	अगर (xa_is_value(page))
		वापस PAGE_SIZE << xa_get_order(xas->xa, xas->xa_index);
	वापस thp_size(page);
पूर्ण

/**
 * mapping_seek_hole_data - Seek क्रम SEEK_DATA / SEEK_HOLE in the page cache.
 * @mapping: Address space to search.
 * @start: First byte to consider.
 * @end: Limit of search (exclusive).
 * @whence: Either SEEK_HOLE or SEEK_DATA.
 *
 * If the page cache knows which blocks contain holes and which blocks
 * contain data, your fileप्रणाली can use this function to implement
 * SEEK_HOLE and SEEK_DATA.  This is useful क्रम fileप्रणालीs which are
 * entirely memory-based such as पंचांगpfs, and fileप्रणालीs which support
 * unwritten extents.
 *
 * Return: The requested offset on success, or -ENXIO अगर @whence specअगरies
 * SEEK_DATA and there is no data after @start.  There is an implicit hole
 * after @end - 1, so SEEK_HOLE वापसs @end अगर all the bytes between @start
 * and @end contain data.
 */
loff_t mapping_seek_hole_data(काष्ठा address_space *mapping, loff_t start,
		loff_t end, पूर्णांक whence)
अणु
	XA_STATE(xas, &mapping->i_pages, start >> PAGE_SHIFT);
	pgoff_t max = (end - 1) >> PAGE_SHIFT;
	bool seek_data = (whence == SEEK_DATA);
	काष्ठा page *page;

	अगर (end <= start)
		वापस -ENXIO;

	rcu_पढ़ो_lock();
	जबतक ((page = find_get_entry(&xas, max, XA_PRESENT))) अणु
		loff_t pos = (u64)xas.xa_index << PAGE_SHIFT;
		अचिन्हित पूर्णांक seek_size;

		अगर (start < pos) अणु
			अगर (!seek_data)
				जाओ unlock;
			start = pos;
		पूर्ण

		seek_size = seek_page_size(&xas, page);
		pos = round_up(pos + 1, seek_size);
		start = page_seek_hole_data(&xas, mapping, page, start, pos,
				seek_data);
		अगर (start < pos)
			जाओ unlock;
		अगर (start >= end)
			अवरोध;
		अगर (seek_size > PAGE_SIZE)
			xas_set(&xas, pos >> PAGE_SHIFT);
		अगर (!xa_is_value(page))
			put_page(page);
	पूर्ण
	अगर (seek_data)
		start = -ENXIO;
unlock:
	rcu_पढ़ो_unlock();
	अगर (page && !xa_is_value(page))
		put_page(page);
	अगर (start > end)
		वापस end;
	वापस start;
पूर्ण

#अगर_घोषित CONFIG_MMU
#घोषणा MMAP_LOTSAMISS  (100)
/*
 * lock_page_maybe_drop_mmap - lock the page, possibly dropping the mmap_lock
 * @vmf - the vm_fault क्रम this fault.
 * @page - the page to lock.
 * @fpin - the poपूर्णांकer to the file we may pin (or is alपढ़ोy pinned).
 *
 * This works similar to lock_page_or_retry in that it can drop the mmap_lock.
 * It dअगरfers in that it actually वापसs the page locked अगर it वापसs 1 and 0
 * अगर it couldn't lock the page.  If we did have to drop the mmap_lock then fpin
 * will poपूर्णांक to the pinned file and needs to be fput()'ed at a later poपूर्णांक.
 */
अटल पूर्णांक lock_page_maybe_drop_mmap(काष्ठा vm_fault *vmf, काष्ठा page *page,
				     काष्ठा file **fpin)
अणु
	अगर (trylock_page(page))
		वापस 1;

	/*
	 * NOTE! This will make us वापस with VM_FAULT_RETRY, but with
	 * the mmap_lock still held. That's how FAULT_FLAG_RETRY_NOWAIT
	 * is supposed to work. We have way too many special हालs..
	 */
	अगर (vmf->flags & FAULT_FLAG_RETRY_NOWAIT)
		वापस 0;

	*fpin = maybe_unlock_mmap_क्रम_io(vmf, *fpin);
	अगर (vmf->flags & FAULT_FLAG_KILLABLE) अणु
		अगर (__lock_page_समाप्तable(page)) अणु
			/*
			 * We didn't have the right flags to drop the mmap_lock,
			 * but all fault_handlers only check क्रम fatal संकेतs
			 * अगर we वापस VM_FAULT_RETRY, so we need to drop the
			 * mmap_lock here and वापस 0 अगर we करोn't have a fpin.
			 */
			अगर (*fpin == शून्य)
				mmap_पढ़ो_unlock(vmf->vma->vm_mm);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा
		__lock_page(page);
	वापस 1;
पूर्ण


/*
 * Synchronous पढ़ोahead happens when we करोn't even find a page in the page
 * cache at all.  We करोn't want to perक्रमm IO under the mmap sem, so अगर we have
 * to drop the mmap sem we वापस the file that was pinned in order क्रम us to करो
 * that.  If we didn't pin a file then we वापस शून्य.  The file that is
 * वापसed needs to be fput()'ed when we're करोne with it.
 */
अटल काष्ठा file *करो_sync_mmap_पढ़ोahead(काष्ठा vm_fault *vmf)
अणु
	काष्ठा file *file = vmf->vma->vm_file;
	काष्ठा file_ra_state *ra = &file->f_ra;
	काष्ठा address_space *mapping = file->f_mapping;
	DEFINE_READAHEAD(ractl, file, ra, mapping, vmf->pgoff);
	काष्ठा file *fpin = शून्य;
	अचिन्हित पूर्णांक mmap_miss;

	/* If we करोn't want any read-ahead, don't bother */
	अगर (vmf->vma->vm_flags & VM_RAND_READ)
		वापस fpin;
	अगर (!ra->ra_pages)
		वापस fpin;

	अगर (vmf->vma->vm_flags & VM_SEQ_READ) अणु
		fpin = maybe_unlock_mmap_क्रम_io(vmf, fpin);
		page_cache_sync_ra(&ractl, ra->ra_pages);
		वापस fpin;
	पूर्ण

	/* Aव्योम banging the cache line अगर not needed */
	mmap_miss = READ_ONCE(ra->mmap_miss);
	अगर (mmap_miss < MMAP_LOTSAMISS * 10)
		WRITE_ONCE(ra->mmap_miss, ++mmap_miss);

	/*
	 * Do we miss much more than hit in this file? If so,
	 * stop bothering with पढ़ो-ahead. It will only hurt.
	 */
	अगर (mmap_miss > MMAP_LOTSAMISS)
		वापस fpin;

	/*
	 * mmap पढ़ो-around
	 */
	fpin = maybe_unlock_mmap_क्रम_io(vmf, fpin);
	ra->start = max_t(दीर्घ, 0, vmf->pgoff - ra->ra_pages / 2);
	ra->size = ra->ra_pages;
	ra->async_size = ra->ra_pages / 4;
	ractl._index = ra->start;
	करो_page_cache_ra(&ractl, ra->size, ra->async_size);
	वापस fpin;
पूर्ण

/*
 * Asynchronous पढ़ोahead happens when we find the page and PG_पढ़ोahead,
 * so we want to possibly extend the पढ़ोahead further.  We वापस the file that
 * was pinned अगर we have to drop the mmap_lock in order to करो IO.
 */
अटल काष्ठा file *करो_async_mmap_पढ़ोahead(काष्ठा vm_fault *vmf,
					    काष्ठा page *page)
अणु
	काष्ठा file *file = vmf->vma->vm_file;
	काष्ठा file_ra_state *ra = &file->f_ra;
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा file *fpin = शून्य;
	अचिन्हित पूर्णांक mmap_miss;
	pgoff_t offset = vmf->pgoff;

	/* If we करोn't want any read-ahead, don't bother */
	अगर (vmf->vma->vm_flags & VM_RAND_READ || !ra->ra_pages)
		वापस fpin;
	mmap_miss = READ_ONCE(ra->mmap_miss);
	अगर (mmap_miss)
		WRITE_ONCE(ra->mmap_miss, --mmap_miss);
	अगर (PageReadahead(page)) अणु
		fpin = maybe_unlock_mmap_क्रम_io(vmf, fpin);
		page_cache_async_पढ़ोahead(mapping, ra, file,
					   page, offset, ra->ra_pages);
	पूर्ण
	वापस fpin;
पूर्ण

/**
 * filemap_fault - पढ़ो in file data क्रम page fault handling
 * @vmf:	काष्ठा vm_fault containing details of the fault
 *
 * filemap_fault() is invoked via the vma operations vector क्रम a
 * mapped memory region to पढ़ो in file data during a page fault.
 *
 * The जाओ's are kind of ugly, but this streamlines the normal हाल of having
 * it in the page cache, and handles the special हालs reasonably without
 * having a lot of duplicated code.
 *
 * vma->vm_mm->mmap_lock must be held on entry.
 *
 * If our वापस value has VM_FAULT_RETRY set, it's because the mmap_lock
 * may be dropped beक्रमe करोing I/O or by lock_page_maybe_drop_mmap().
 *
 * If our वापस value करोes not have VM_FAULT_RETRY set, the mmap_lock
 * has not been released.
 *
 * We never वापस with VM_FAULT_RETRY and a bit from VM_FAULT_ERROR set.
 *
 * Return: bitwise-OR of %VM_FAULT_ codes.
 */
vm_fault_t filemap_fault(काष्ठा vm_fault *vmf)
अणु
	पूर्णांक error;
	काष्ठा file *file = vmf->vma->vm_file;
	काष्ठा file *fpin = शून्य;
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	pgoff_t offset = vmf->pgoff;
	pgoff_t max_off;
	काष्ठा page *page;
	vm_fault_t ret = 0;

	max_off = DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE);
	अगर (unlikely(offset >= max_off))
		वापस VM_FAULT_SIGBUS;

	/*
	 * Do we have something in the page cache alपढ़ोy?
	 */
	page = find_get_page(mapping, offset);
	अगर (likely(page) && !(vmf->flags & FAULT_FLAG_TRIED)) अणु
		/*
		 * We found the page, so try async पढ़ोahead beक्रमe
		 * रुकोing क्रम the lock.
		 */
		fpin = करो_async_mmap_पढ़ोahead(vmf, page);
	पूर्ण अन्यथा अगर (!page) अणु
		/* No page in the page cache at all */
		count_vm_event(PGMAJFAULT);
		count_memcg_event_mm(vmf->vma->vm_mm, PGMAJFAULT);
		ret = VM_FAULT_MAJOR;
		fpin = करो_sync_mmap_पढ़ोahead(vmf);
retry_find:
		page = pagecache_get_page(mapping, offset,
					  FGP_CREAT|FGP_FOR_MMAP,
					  vmf->gfp_mask);
		अगर (!page) अणु
			अगर (fpin)
				जाओ out_retry;
			वापस VM_FAULT_OOM;
		पूर्ण
	पूर्ण

	अगर (!lock_page_maybe_drop_mmap(vmf, page, &fpin))
		जाओ out_retry;

	/* Did it get truncated? */
	अगर (unlikely(compound_head(page)->mapping != mapping)) अणु
		unlock_page(page);
		put_page(page);
		जाओ retry_find;
	पूर्ण
	VM_BUG_ON_PAGE(page_to_pgoff(page) != offset, page);

	/*
	 * We have a locked page in the page cache, now we need to check
	 * that it's up-to-date. If not, it is going to be due to an error.
	 */
	अगर (unlikely(!PageUptodate(page)))
		जाओ page_not_uptodate;

	/*
	 * We've made it this far and we had to drop our mmap_lock, now is the
	 * समय to वापस to the upper layer and have it re-find the vma and
	 * reकरो the fault.
	 */
	अगर (fpin) अणु
		unlock_page(page);
		जाओ out_retry;
	पूर्ण

	/*
	 * Found the page and have a reference on it.
	 * We must recheck i_size under page lock.
	 */
	max_off = DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE);
	अगर (unlikely(offset >= max_off)) अणु
		unlock_page(page);
		put_page(page);
		वापस VM_FAULT_SIGBUS;
	पूर्ण

	vmf->page = page;
	वापस ret | VM_FAULT_LOCKED;

page_not_uptodate:
	/*
	 * Umm, take care of errors अगर the page isn't up-to-date.
	 * Try to re-पढ़ो it _once_. We करो this synchronously,
	 * because there really aren't any perक्रमmance issues here
	 * and we need to check क्रम errors.
	 */
	fpin = maybe_unlock_mmap_क्रम_io(vmf, fpin);
	error = filemap_पढ़ो_page(file, mapping, page);
	अगर (fpin)
		जाओ out_retry;
	put_page(page);

	अगर (!error || error == AOP_TRUNCATED_PAGE)
		जाओ retry_find;

	वापस VM_FAULT_SIGBUS;

out_retry:
	/*
	 * We dropped the mmap_lock, we need to वापस to the fault handler to
	 * re-find the vma and come back and find our hopefully still populated
	 * page.
	 */
	अगर (page)
		put_page(page);
	अगर (fpin)
		fput(fpin);
	वापस ret | VM_FAULT_RETRY;
पूर्ण
EXPORT_SYMBOL(filemap_fault);

अटल bool filemap_map_pmd(काष्ठा vm_fault *vmf, काष्ठा page *page)
अणु
	काष्ठा mm_काष्ठा *mm = vmf->vma->vm_mm;

	/* Huge page is mapped? No need to proceed. */
	अगर (pmd_trans_huge(*vmf->pmd)) अणु
		unlock_page(page);
		put_page(page);
		वापस true;
	पूर्ण

	अगर (pmd_none(*vmf->pmd) && PageTransHuge(page)) अणु
	    vm_fault_t ret = करो_set_pmd(vmf, page);
	    अगर (!ret) अणु
		    /* The page is mapped successfully, reference consumed. */
		    unlock_page(page);
		    वापस true;
	    पूर्ण
	पूर्ण

	अगर (pmd_none(*vmf->pmd)) अणु
		vmf->ptl = pmd_lock(mm, vmf->pmd);
		अगर (likely(pmd_none(*vmf->pmd))) अणु
			mm_inc_nr_ptes(mm);
			pmd_populate(mm, vmf->pmd, vmf->pपुनः_स्मृति_pte);
			vmf->pपुनः_स्मृति_pte = शून्य;
		पूर्ण
		spin_unlock(vmf->ptl);
	पूर्ण

	/* See comment in handle_pte_fault() */
	अगर (pmd_devmap_trans_unstable(vmf->pmd)) अणु
		unlock_page(page);
		put_page(page);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा page *next_uptodate_page(काष्ठा page *page,
				       काष्ठा address_space *mapping,
				       काष्ठा xa_state *xas, pgoff_t end_pgoff)
अणु
	अचिन्हित दीर्घ max_idx;

	करो अणु
		अगर (!page)
			वापस शून्य;
		अगर (xas_retry(xas, page))
			जारी;
		अगर (xa_is_value(page))
			जारी;
		अगर (PageLocked(page))
			जारी;
		अगर (!page_cache_get_speculative(page))
			जारी;
		/* Has the page moved or been split? */
		अगर (unlikely(page != xas_reload(xas)))
			जाओ skip;
		अगर (!PageUptodate(page) || PageReadahead(page))
			जाओ skip;
		अगर (PageHWPoison(page))
			जाओ skip;
		अगर (!trylock_page(page))
			जाओ skip;
		अगर (page->mapping != mapping)
			जाओ unlock;
		अगर (!PageUptodate(page))
			जाओ unlock;
		max_idx = DIV_ROUND_UP(i_size_पढ़ो(mapping->host), PAGE_SIZE);
		अगर (xas->xa_index >= max_idx)
			जाओ unlock;
		वापस page;
unlock:
		unlock_page(page);
skip:
		put_page(page);
	पूर्ण जबतक ((page = xas_next_entry(xas, end_pgoff)) != शून्य);

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा page *first_map_page(काष्ठा address_space *mapping,
					  काष्ठा xa_state *xas,
					  pgoff_t end_pgoff)
अणु
	वापस next_uptodate_page(xas_find(xas, end_pgoff),
				  mapping, xas, end_pgoff);
पूर्ण

अटल अंतरभूत काष्ठा page *next_map_page(काष्ठा address_space *mapping,
					 काष्ठा xa_state *xas,
					 pgoff_t end_pgoff)
अणु
	वापस next_uptodate_page(xas_next_entry(xas, end_pgoff),
				  mapping, xas, end_pgoff);
पूर्ण

vm_fault_t filemap_map_pages(काष्ठा vm_fault *vmf,
			     pgoff_t start_pgoff, pgoff_t end_pgoff)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा file *file = vma->vm_file;
	काष्ठा address_space *mapping = file->f_mapping;
	pgoff_t last_pgoff = start_pgoff;
	अचिन्हित दीर्घ addr;
	XA_STATE(xas, &mapping->i_pages, start_pgoff);
	काष्ठा page *head, *page;
	अचिन्हित पूर्णांक mmap_miss = READ_ONCE(file->f_ra.mmap_miss);
	vm_fault_t ret = 0;

	rcu_पढ़ो_lock();
	head = first_map_page(mapping, &xas, end_pgoff);
	अगर (!head)
		जाओ out;

	अगर (filemap_map_pmd(vmf, head)) अणु
		ret = VM_FAULT_NOPAGE;
		जाओ out;
	पूर्ण

	addr = vma->vm_start + ((start_pgoff - vma->vm_pgoff) << PAGE_SHIFT);
	vmf->pte = pte_offset_map_lock(vma->vm_mm, vmf->pmd, addr, &vmf->ptl);
	करो अणु
		page = find_subpage(head, xas.xa_index);
		अगर (PageHWPoison(page))
			जाओ unlock;

		अगर (mmap_miss > 0)
			mmap_miss--;

		addr += (xas.xa_index - last_pgoff) << PAGE_SHIFT;
		vmf->pte += xas.xa_index - last_pgoff;
		last_pgoff = xas.xa_index;

		अगर (!pte_none(*vmf->pte))
			जाओ unlock;

		/* We're about to handle the fault */
		अगर (vmf->address == addr)
			ret = VM_FAULT_NOPAGE;

		करो_set_pte(vmf, page, addr);
		/* no need to invalidate: a not-present page won't be cached */
		update_mmu_cache(vma, addr, vmf->pte);
		unlock_page(head);
		जारी;
unlock:
		unlock_page(head);
		put_page(head);
	पूर्ण जबतक ((head = next_map_page(mapping, &xas, end_pgoff)) != शून्य);
	pte_unmap_unlock(vmf->pte, vmf->ptl);
out:
	rcu_पढ़ो_unlock();
	WRITE_ONCE(file->f_ra.mmap_miss, mmap_miss);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(filemap_map_pages);

vm_fault_t filemap_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा address_space *mapping = vmf->vma->vm_file->f_mapping;
	काष्ठा page *page = vmf->page;
	vm_fault_t ret = VM_FAULT_LOCKED;

	sb_start_pagefault(mapping->host->i_sb);
	file_update_समय(vmf->vma->vm_file);
	lock_page(page);
	अगर (page->mapping != mapping) अणु
		unlock_page(page);
		ret = VM_FAULT_NOPAGE;
		जाओ out;
	पूर्ण
	/*
	 * We mark the page dirty alपढ़ोy here so that when मुक्तze is in
	 * progress, we are guaranteed that ग_लिखोback during मुक्तzing will
	 * see the dirty page and ग_लिखोprotect it again.
	 */
	set_page_dirty(page);
	रुको_क्रम_stable_page(page);
out:
	sb_end_pagefault(mapping->host->i_sb);
	वापस ret;
पूर्ण

स्थिर काष्ठा vm_operations_काष्ठा generic_file_vm_ops = अणु
	.fault		= filemap_fault,
	.map_pages	= filemap_map_pages,
	.page_mkग_लिखो	= filemap_page_mkग_लिखो,
पूर्ण;

/* This is used क्रम a general mmap of a disk file */

पूर्णांक generic_file_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा address_space *mapping = file->f_mapping;

	अगर (!mapping->a_ops->पढ़ोpage)
		वापस -ENOEXEC;
	file_accessed(file);
	vma->vm_ops = &generic_file_vm_ops;
	वापस 0;
पूर्ण

/*
 * This is क्रम fileप्रणालीs which करो not implement ->ग_लिखोpage.
 */
पूर्णांक generic_file_पढ़ोonly_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर ((vma->vm_flags & VM_SHARED) && (vma->vm_flags & VM_MAYWRITE))
		वापस -EINVAL;
	वापस generic_file_mmap(file, vma);
पूर्ण
#अन्यथा
vm_fault_t filemap_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	वापस VM_FAULT_SIGBUS;
पूर्ण
पूर्णांक generic_file_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस -ENOSYS;
पूर्ण
पूर्णांक generic_file_पढ़ोonly_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर /* CONFIG_MMU */

EXPORT_SYMBOL(filemap_page_mkग_लिखो);
EXPORT_SYMBOL(generic_file_mmap);
EXPORT_SYMBOL(generic_file_पढ़ोonly_mmap);

अटल काष्ठा page *रुको_on_page_पढ़ो(काष्ठा page *page)
अणु
	अगर (!IS_ERR(page)) अणु
		रुको_on_page_locked(page);
		अगर (!PageUptodate(page)) अणु
			put_page(page);
			page = ERR_PTR(-EIO);
		पूर्ण
	पूर्ण
	वापस page;
पूर्ण

अटल काष्ठा page *करो_पढ़ो_cache_page(काष्ठा address_space *mapping,
				pgoff_t index,
				पूर्णांक (*filler)(व्योम *, काष्ठा page *),
				व्योम *data,
				gfp_t gfp)
अणु
	काष्ठा page *page;
	पूर्णांक err;
repeat:
	page = find_get_page(mapping, index);
	अगर (!page) अणु
		page = __page_cache_alloc(gfp);
		अगर (!page)
			वापस ERR_PTR(-ENOMEM);
		err = add_to_page_cache_lru(page, mapping, index, gfp);
		अगर (unlikely(err)) अणु
			put_page(page);
			अगर (err == -EEXIST)
				जाओ repeat;
			/* Presumably ENOMEM क्रम xarray node */
			वापस ERR_PTR(err);
		पूर्ण

filler:
		अगर (filler)
			err = filler(data, page);
		अन्यथा
			err = mapping->a_ops->पढ़ोpage(data, page);

		अगर (err < 0) अणु
			put_page(page);
			वापस ERR_PTR(err);
		पूर्ण

		page = रुको_on_page_पढ़ो(page);
		अगर (IS_ERR(page))
			वापस page;
		जाओ out;
	पूर्ण
	अगर (PageUptodate(page))
		जाओ out;

	/*
	 * Page is not up to date and may be locked due to one of the following
	 * हाल a: Page is being filled and the page lock is held
	 * हाल b: Read/ग_लिखो error clearing the page uptodate status
	 * हाल c: Truncation in progress (page locked)
	 * हाल d: Reclaim in progress
	 *
	 * Case a, the page will be up to date when the page is unlocked.
	 *    There is no need to serialise on the page lock here as the page
	 *    is pinned so the lock gives no additional protection. Even अगर the
	 *    page is truncated, the data is still valid अगर PageUptodate as
	 *    it's a race vs truncate race.
	 * Case b, the page will not be up to date
	 * Case c, the page may be truncated but in itself, the data may still
	 *    be valid after IO completes as it's a पढ़ो vs truncate race. The
	 *    operation must restart अगर the page is not uptodate on unlock but
	 *    otherwise serialising on page lock to stabilise the mapping gives
	 *    no additional guarantees to the caller as the page lock is
	 *    released beक्रमe वापस.
	 * Case d, similar to truncation. If reclaim holds the page lock, it
	 *    will be a race with हटाओ_mapping that determines अगर the mapping
	 *    is valid on unlock but otherwise the data is valid and there is
	 *    no need to serialise with page lock.
	 *
	 * As the page lock gives no additional guarantee, we optimistically
	 * रुको on the page to be unlocked and check अगर it's up to date and
	 * use the page अगर it is. Otherwise, the page lock is required to
	 * distinguish between the dअगरferent हालs. The motivation is that we
	 * aव्योम spurious serialisations and wakeups when multiple processes
	 * रुको on the same page क्रम IO to complete.
	 */
	रुको_on_page_locked(page);
	अगर (PageUptodate(page))
		जाओ out;

	/* Distinguish between all the हालs under the safety of the lock */
	lock_page(page);

	/* Case c or d, restart the operation */
	अगर (!page->mapping) अणु
		unlock_page(page);
		put_page(page);
		जाओ repeat;
	पूर्ण

	/* Someone अन्यथा locked and filled the page in a very small winकरोw */
	अगर (PageUptodate(page)) अणु
		unlock_page(page);
		जाओ out;
	पूर्ण

	/*
	 * A previous I/O error may have been due to temporary
	 * failures.
	 * Clear page error beक्रमe actual पढ़ो, PG_error will be
	 * set again अगर पढ़ो page fails.
	 */
	ClearPageError(page);
	जाओ filler;

out:
	mark_page_accessed(page);
	वापस page;
पूर्ण

/**
 * पढ़ो_cache_page - पढ़ो पूर्णांकo page cache, fill it अगर needed
 * @mapping:	the page's address_space
 * @index:	the page index
 * @filler:	function to perक्रमm the पढ़ो
 * @data:	first arg to filler(data, page) function, often left as शून्य
 *
 * Read पूर्णांकo the page cache. If a page alपढ़ोy exists, and PageUptodate() is
 * not set, try to fill the page and रुको क्रम it to become unlocked.
 *
 * If the page करोes not get brought uptodate, वापस -EIO.
 *
 * Return: up to date page on success, ERR_PTR() on failure.
 */
काष्ठा page *पढ़ो_cache_page(काष्ठा address_space *mapping,
				pgoff_t index,
				पूर्णांक (*filler)(व्योम *, काष्ठा page *),
				व्योम *data)
अणु
	वापस करो_पढ़ो_cache_page(mapping, index, filler, data,
			mapping_gfp_mask(mapping));
पूर्ण
EXPORT_SYMBOL(पढ़ो_cache_page);

/**
 * पढ़ो_cache_page_gfp - पढ़ो पूर्णांकo page cache, using specअगरied page allocation flags.
 * @mapping:	the page's address_space
 * @index:	the page index
 * @gfp:	the page allocator flags to use अगर allocating
 *
 * This is the same as "read_mapping_page(mapping, index, NULL)", but with
 * any new page allocations करोne using the specअगरied allocation flags.
 *
 * If the page करोes not get brought uptodate, वापस -EIO.
 *
 * Return: up to date page on success, ERR_PTR() on failure.
 */
काष्ठा page *पढ़ो_cache_page_gfp(काष्ठा address_space *mapping,
				pgoff_t index,
				gfp_t gfp)
अणु
	वापस करो_पढ़ो_cache_page(mapping, index, शून्य, शून्य, gfp);
पूर्ण
EXPORT_SYMBOL(पढ़ो_cache_page_gfp);

पूर्णांक pagecache_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
				loff_t pos, अचिन्हित len, अचिन्हित flags,
				काष्ठा page **pagep, व्योम **fsdata)
अणु
	स्थिर काष्ठा address_space_operations *aops = mapping->a_ops;

	वापस aops->ग_लिखो_begin(file, mapping, pos, len, flags,
							pagep, fsdata);
पूर्ण
EXPORT_SYMBOL(pagecache_ग_लिखो_begin);

पूर्णांक pagecache_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
				loff_t pos, अचिन्हित len, अचिन्हित copied,
				काष्ठा page *page, व्योम *fsdata)
अणु
	स्थिर काष्ठा address_space_operations *aops = mapping->a_ops;

	वापस aops->ग_लिखो_end(file, mapping, pos, len, copied, page, fsdata);
पूर्ण
EXPORT_SYMBOL(pagecache_ग_लिखो_end);

/*
 * Warn about a page cache invalidation failure during a direct I/O ग_लिखो.
 */
व्योम dio_warn_stale_pagecache(काष्ठा file *filp)
अणु
	अटल DEFINE_RATELIMIT_STATE(_rs, 86400 * HZ, DEFAULT_RATELIMIT_BURST);
	अक्षर pathname[128];
	अक्षर *path;

	errseq_set(&filp->f_mapping->wb_err, -EIO);
	अगर (__ratelimit(&_rs)) अणु
		path = file_path(filp, pathname, माप(pathname));
		अगर (IS_ERR(path))
			path = "(unknown)";
		pr_crit("Page cache invalidation failure on direct I/O.  Possible data corruption due to collision with buffered I/O!\n");
		pr_crit("File: %s PID: %d Comm: %.20s\n", path, current->pid,
			current->comm);
	पूर्ण
पूर्ण

sमाप_प्रकार
generic_file_direct_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file	*file = iocb->ki_filp;
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode	*inode = mapping->host;
	loff_t		pos = iocb->ki_pos;
	sमाप_प्रकार		written;
	माप_प्रकार		ग_लिखो_len;
	pgoff_t		end;

	ग_लिखो_len = iov_iter_count(from);
	end = (pos + ग_लिखो_len - 1) >> PAGE_SHIFT;

	अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
		/* If there are pages to ग_लिखोback, वापस */
		अगर (filemap_range_has_page(file->f_mapping, pos,
					   pos + ग_लिखो_len - 1))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		written = filemap_ग_लिखो_and_रुको_range(mapping, pos,
							pos + ग_लिखो_len - 1);
		अगर (written)
			जाओ out;
	पूर्ण

	/*
	 * After a ग_लिखो we want buffered पढ़ोs to be sure to go to disk to get
	 * the new data.  We invalidate clean cached page from the region we're
	 * about to ग_लिखो.  We करो this *beक्रमe* the ग_लिखो so that we can वापस
	 * without clobbering -EIOCBQUEUED from ->direct_IO().
	 */
	written = invalidate_inode_pages2_range(mapping,
					pos >> PAGE_SHIFT, end);
	/*
	 * If a page can not be invalidated, वापस 0 to fall back
	 * to buffered ग_लिखो.
	 */
	अगर (written) अणु
		अगर (written == -EBUSY)
			वापस 0;
		जाओ out;
	पूर्ण

	written = mapping->a_ops->direct_IO(iocb, from);

	/*
	 * Finally, try again to invalidate clean pages which might have been
	 * cached by non-direct पढ़ोahead, or faulted in by get_user_pages()
	 * अगर the source of the ग_लिखो was an mmap'ed region of the file
	 * we're writing.  Either one is a pretty crazy thing to करो,
	 * so we करोn't support it 100%.  If this invalidation
	 * fails, tough, the ग_लिखो still worked...
	 *
	 * Most of the समय we करो not need this since dio_complete() will करो
	 * the invalidation क्रम us. However there are some file प्रणालीs that
	 * करो not end up with dio_complete() being called, so let's not अवरोध
	 * them by removing it completely.
	 *
	 * Noticeable example is a blkdev_direct_IO().
	 *
	 * Skip invalidation क्रम async ग_लिखोs or अगर mapping has no pages.
	 */
	अगर (written > 0 && mapping->nrpages &&
	    invalidate_inode_pages2_range(mapping, pos >> PAGE_SHIFT, end))
		dio_warn_stale_pagecache(file);

	अगर (written > 0) अणु
		pos += written;
		ग_लिखो_len -= written;
		अगर (pos > i_size_पढ़ो(inode) && !S_ISBLK(inode->i_mode)) अणु
			i_size_ग_लिखो(inode, pos);
			mark_inode_dirty(inode);
		पूर्ण
		iocb->ki_pos = pos;
	पूर्ण
	अगर (written != -EIOCBQUEUED)
		iov_iter_revert(from, ग_लिखो_len - iov_iter_count(from));
out:
	वापस written;
पूर्ण
EXPORT_SYMBOL(generic_file_direct_ग_लिखो);

/*
 * Find or create a page at the given pagecache position. Return the locked
 * page. This function is specअगरically क्रम buffered ग_लिखोs.
 */
काष्ठा page *grab_cache_page_ग_लिखो_begin(काष्ठा address_space *mapping,
					pgoff_t index, अचिन्हित flags)
अणु
	काष्ठा page *page;
	पूर्णांक fgp_flags = FGP_LOCK|FGP_WRITE|FGP_CREAT;

	अगर (flags & AOP_FLAG_NOFS)
		fgp_flags |= FGP_NOFS;

	page = pagecache_get_page(mapping, index, fgp_flags,
			mapping_gfp_mask(mapping));
	अगर (page)
		रुको_क्रम_stable_page(page);

	वापस page;
पूर्ण
EXPORT_SYMBOL(grab_cache_page_ग_लिखो_begin);

sमाप_प्रकार generic_perक्रमm_ग_लिखो(काष्ठा file *file,
				काष्ठा iov_iter *i, loff_t pos)
अणु
	काष्ठा address_space *mapping = file->f_mapping;
	स्थिर काष्ठा address_space_operations *a_ops = mapping->a_ops;
	दीर्घ status = 0;
	sमाप_प्रकार written = 0;
	अचिन्हित पूर्णांक flags = 0;

	करो अणु
		काष्ठा page *page;
		अचिन्हित दीर्घ offset;	/* Offset पूर्णांकo pagecache page */
		अचिन्हित दीर्घ bytes;	/* Bytes to ग_लिखो to page */
		माप_प्रकार copied;		/* Bytes copied from user */
		व्योम *fsdata;

		offset = (pos & (PAGE_SIZE - 1));
		bytes = min_t(अचिन्हित दीर्घ, PAGE_SIZE - offset,
						iov_iter_count(i));

again:
		/*
		 * Bring in the user page that we will copy from _first_.
		 * Otherwise there's a nasty deadlock on copying from the
		 * same page as we're writing to, without it being marked
		 * up-to-date.
		 *
		 * Not only is this an optimisation, but it is also required
		 * to check that the address is actually valid, when atomic
		 * usercopies are used, below.
		 */
		अगर (unlikely(iov_iter_fault_in_पढ़ोable(i, bytes))) अणु
			status = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (fatal_संकेत_pending(current)) अणु
			status = -EINTR;
			अवरोध;
		पूर्ण

		status = a_ops->ग_लिखो_begin(file, mapping, pos, bytes, flags,
						&page, &fsdata);
		अगर (unlikely(status < 0))
			अवरोध;

		अगर (mapping_writably_mapped(mapping))
			flush_dcache_page(page);

		copied = iov_iter_copy_from_user_atomic(page, i, offset, bytes);
		flush_dcache_page(page);

		status = a_ops->ग_लिखो_end(file, mapping, pos, bytes, copied,
						page, fsdata);
		अगर (unlikely(status < 0))
			अवरोध;
		copied = status;

		cond_resched();

		iov_iter_advance(i, copied);
		अगर (unlikely(copied == 0)) अणु
			/*
			 * If we were unable to copy any data at all, we must
			 * fall back to a single segment length ग_लिखो.
			 *
			 * If we didn't fallback here, we could livelock
			 * because not all segments in the iov can be copied at
			 * once without a pagefault.
			 */
			bytes = min_t(अचिन्हित दीर्घ, PAGE_SIZE - offset,
						iov_iter_single_seg_count(i));
			जाओ again;
		पूर्ण
		pos += copied;
		written += copied;

		balance_dirty_pages_ratelimited(mapping);
	पूर्ण जबतक (iov_iter_count(i));

	वापस written ? written : status;
पूर्ण
EXPORT_SYMBOL(generic_perक्रमm_ग_लिखो);

/**
 * __generic_file_ग_लिखो_iter - ग_लिखो data to a file
 * @iocb:	IO state काष्ठाure (file, offset, etc.)
 * @from:	iov_iter with data to ग_लिखो
 *
 * This function करोes all the work needed क्रम actually writing data to a
 * file. It करोes all basic checks, हटाओs SUID from the file, updates
 * modअगरication बार and calls proper subroutines depending on whether we
 * करो direct IO or a standard buffered ग_लिखो.
 *
 * It expects i_mutex to be grabbed unless we work on a block device or similar
 * object which करोes not need locking at all.
 *
 * This function करोes *not* take care of syncing data in हाल of O_SYNC ग_लिखो.
 * A caller has to handle it. This is मुख्यly due to the fact that we want to
 * aव्योम syncing under i_mutex.
 *
 * Return:
 * * number of bytes written, even क्रम truncated ग_लिखोs
 * * negative error code अगर no data has been written at all
 */
sमाप_प्रकार __generic_file_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode 	*inode = mapping->host;
	sमाप_प्रकार		written = 0;
	sमाप_प्रकार		err;
	sमाप_प्रकार		status;

	/* We can ग_लिखो back this queue in page reclaim */
	current->backing_dev_info = inode_to_bdi(inode);
	err = file_हटाओ_privs(file);
	अगर (err)
		जाओ out;

	err = file_update_समय(file);
	अगर (err)
		जाओ out;

	अगर (iocb->ki_flags & IOCB_सूचीECT) अणु
		loff_t pos, endbyte;

		written = generic_file_direct_ग_लिखो(iocb, from);
		/*
		 * If the ग_लिखो stopped लघु of completing, fall back to
		 * buffered ग_लिखोs.  Some fileप्रणालीs करो this क्रम ग_लिखोs to
		 * holes, क्रम example.  For DAX files, a buffered ग_लिखो will
		 * not succeed (even अगर it did, DAX करोes not handle dirty
		 * page-cache pages correctly).
		 */
		अगर (written < 0 || !iov_iter_count(from) || IS_DAX(inode))
			जाओ out;

		status = generic_perक्रमm_ग_लिखो(file, from, pos = iocb->ki_pos);
		/*
		 * If generic_perक्रमm_ग_लिखो() वापसed a synchronous error
		 * then we want to वापस the number of bytes which were
		 * direct-written, or the error code अगर that was zero.  Note
		 * that this dअगरfers from normal direct-io semantics, which
		 * will वापस -EFOO even अगर some bytes were written.
		 */
		अगर (unlikely(status < 0)) अणु
			err = status;
			जाओ out;
		पूर्ण
		/*
		 * We need to ensure that the page cache pages are written to
		 * disk and invalidated to preserve the expected O_सूचीECT
		 * semantics.
		 */
		endbyte = pos + status - 1;
		err = filemap_ग_लिखो_and_रुको_range(mapping, pos, endbyte);
		अगर (err == 0) अणु
			iocb->ki_pos = endbyte + 1;
			written += status;
			invalidate_mapping_pages(mapping,
						 pos >> PAGE_SHIFT,
						 endbyte >> PAGE_SHIFT);
		पूर्ण अन्यथा अणु
			/*
			 * We करोn't know how much we wrote, so just वापस
			 * the number of bytes which were direct-written
			 */
		पूर्ण
	पूर्ण अन्यथा अणु
		written = generic_perक्रमm_ग_लिखो(file, from, iocb->ki_pos);
		अगर (likely(written > 0))
			iocb->ki_pos += written;
	पूर्ण
out:
	current->backing_dev_info = शून्य;
	वापस written ? written : err;
पूर्ण
EXPORT_SYMBOL(__generic_file_ग_लिखो_iter);

/**
 * generic_file_ग_लिखो_iter - ग_लिखो data to a file
 * @iocb:	IO state काष्ठाure
 * @from:	iov_iter with data to ग_लिखो
 *
 * This is a wrapper around __generic_file_ग_लिखो_iter() to be used by most
 * fileप्रणालीs. It takes care of syncing the file in हाल of O_SYNC file
 * and acquires i_mutex as needed.
 * Return:
 * * negative error code अगर no data has been written at all of
 *   vfs_fsync_range() failed क्रम a synchronous ग_लिखो
 * * number of bytes written, even क्रम truncated ग_लिखोs
 */
sमाप_प्रकार generic_file_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file->f_mapping->host;
	sमाप_प्रकार ret;

	inode_lock(inode);
	ret = generic_ग_लिखो_checks(iocb, from);
	अगर (ret > 0)
		ret = __generic_file_ग_लिखो_iter(iocb, from);
	inode_unlock(inode);

	अगर (ret > 0)
		ret = generic_ग_लिखो_sync(iocb, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(generic_file_ग_लिखो_iter);

/**
 * try_to_release_page() - release old fs-specअगरic metadata on a page
 *
 * @page: the page which the kernel is trying to मुक्त
 * @gfp_mask: memory allocation flags (and I/O mode)
 *
 * The address_space is to try to release any data against the page
 * (presumably at page->निजी).
 *
 * This may also be called अगर PG_fscache is set on a page, indicating that the
 * page is known to the local caching routines.
 *
 * The @gfp_mask argument specअगरies whether I/O may be perक्रमmed to release
 * this page (__GFP_IO), and whether the call may block (__GFP_RECLAIM & __GFP_FS).
 *
 * Return: %1 अगर the release was successful, otherwise वापस zero.
 */
पूर्णांक try_to_release_page(काष्ठा page *page, gfp_t gfp_mask)
अणु
	काष्ठा address_space * स्थिर mapping = page->mapping;

	BUG_ON(!PageLocked(page));
	अगर (PageWriteback(page))
		वापस 0;

	अगर (mapping && mapping->a_ops->releasepage)
		वापस mapping->a_ops->releasepage(page, gfp_mask);
	वापस try_to_मुक्त_buffers(page);
पूर्ण

EXPORT_SYMBOL(try_to_release_page);
