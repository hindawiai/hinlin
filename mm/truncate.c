<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mm/truncate.c - code क्रम taking करोwn pages from address_spaces
 *
 * Copyright (C) 2002, Linus Torvalds
 *
 * 10Sep2002	Andrew Morton
 *		Initial version.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/dax.h>
#समावेश <linux/gfp.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/export.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagevec.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/buffer_head.h>	/* grr. try_to_release_page,
				   करो_invalidatepage */
#समावेश <linux/shmem_fs.h>
#समावेश <linux/cleancache.h>
#समावेश <linux/rmap.h>
#समावेश "internal.h"

/*
 * Regular page slots are stabilized by the page lock even without the tree
 * itself locked.  These unlocked entries need verअगरication under the tree
 * lock.
 */
अटल अंतरभूत व्योम __clear_shaकरोw_entry(काष्ठा address_space *mapping,
				pgoff_t index, व्योम *entry)
अणु
	XA_STATE(xas, &mapping->i_pages, index);

	xas_set_update(&xas, workingset_update_node);
	अगर (xas_load(&xas) != entry)
		वापस;
	xas_store(&xas, शून्य);
पूर्ण

अटल व्योम clear_shaकरोw_entry(काष्ठा address_space *mapping, pgoff_t index,
			       व्योम *entry)
अणु
	xa_lock_irq(&mapping->i_pages);
	__clear_shaकरोw_entry(mapping, index, entry);
	xa_unlock_irq(&mapping->i_pages);
पूर्ण

/*
 * Unconditionally हटाओ exceptional entries. Usually called from truncate
 * path. Note that the pagevec may be altered by this function by removing
 * exceptional entries similar to what pagevec_हटाओ_exceptionals करोes.
 */
अटल व्योम truncate_exceptional_pvec_entries(काष्ठा address_space *mapping,
				काष्ठा pagevec *pvec, pgoff_t *indices)
अणु
	पूर्णांक i, j;
	bool dax;

	/* Handled by shmem itself */
	अगर (shmem_mapping(mapping))
		वापस;

	क्रम (j = 0; j < pagevec_count(pvec); j++)
		अगर (xa_is_value(pvec->pages[j]))
			अवरोध;

	अगर (j == pagevec_count(pvec))
		वापस;

	dax = dax_mapping(mapping);
	अगर (!dax)
		xa_lock_irq(&mapping->i_pages);

	क्रम (i = j; i < pagevec_count(pvec); i++) अणु
		काष्ठा page *page = pvec->pages[i];
		pgoff_t index = indices[i];

		अगर (!xa_is_value(page)) अणु
			pvec->pages[j++] = page;
			जारी;
		पूर्ण

		अगर (unlikely(dax)) अणु
			dax_delete_mapping_entry(mapping, index);
			जारी;
		पूर्ण

		__clear_shaकरोw_entry(mapping, index, page);
	पूर्ण

	अगर (!dax)
		xa_unlock_irq(&mapping->i_pages);
	pvec->nr = j;
पूर्ण

/*
 * Invalidate exceptional entry अगर easily possible. This handles exceptional
 * entries क्रम invalidate_inode_pages().
 */
अटल पूर्णांक invalidate_exceptional_entry(काष्ठा address_space *mapping,
					pgoff_t index, व्योम *entry)
अणु
	/* Handled by shmem itself, or क्रम DAX we करो nothing. */
	अगर (shmem_mapping(mapping) || dax_mapping(mapping))
		वापस 1;
	clear_shaकरोw_entry(mapping, index, entry);
	वापस 1;
पूर्ण

/*
 * Invalidate exceptional entry अगर clean. This handles exceptional entries क्रम
 * invalidate_inode_pages2() so क्रम DAX it evicts only clean entries.
 */
अटल पूर्णांक invalidate_exceptional_entry2(काष्ठा address_space *mapping,
					 pgoff_t index, व्योम *entry)
अणु
	/* Handled by shmem itself */
	अगर (shmem_mapping(mapping))
		वापस 1;
	अगर (dax_mapping(mapping))
		वापस dax_invalidate_mapping_entry_sync(mapping, index);
	clear_shaकरोw_entry(mapping, index, entry);
	वापस 1;
पूर्ण

/**
 * करो_invalidatepage - invalidate part or all of a page
 * @page: the page which is affected
 * @offset: start of the range to invalidate
 * @length: length of the range to invalidate
 *
 * करो_invalidatepage() is called when all or part of the page has become
 * invalidated by a truncate operation.
 *
 * करो_invalidatepage() करोes not have to release all buffers, but it must
 * ensure that no dirty buffer is left outside @offset and that no I/O
 * is underway against any of the blocks which are outside the truncation
 * poपूर्णांक.  Because the caller is about to मुक्त (and possibly reuse) those
 * blocks on-disk.
 */
व्योम करो_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
		       अचिन्हित पूर्णांक length)
अणु
	व्योम (*invalidatepage)(काष्ठा page *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);

	invalidatepage = page->mapping->a_ops->invalidatepage;
#अगर_घोषित CONFIG_BLOCK
	अगर (!invalidatepage)
		invalidatepage = block_invalidatepage;
#पूर्ण_अगर
	अगर (invalidatepage)
		(*invalidatepage)(page, offset, length);
पूर्ण

/*
 * If truncate cannot हटाओ the fs-निजी metadata from the page, the page
 * becomes orphaned.  It will be left on the LRU and may even be mapped पूर्णांकo
 * user pagetables अगर we're racing with filemap_fault().
 *
 * We need to bail out अगर page->mapping is no दीर्घer equal to the original
 * mapping.  This happens a) when the VM reclaimed the page जबतक we रुकोed on
 * its lock, b) when a concurrent invalidate_mapping_pages got there first and
 * c) when पंचांगpfs swizzles a page between a पंचांगpfs inode and swapper_space.
 */
अटल व्योम truncate_cleanup_page(काष्ठा page *page)
अणु
	अगर (page_mapped(page))
		unmap_mapping_page(page);

	अगर (page_has_निजी(page))
		करो_invalidatepage(page, 0, thp_size(page));

	/*
	 * Some fileप्रणालीs seem to re-dirty the page even after
	 * the VM has canceled the dirty bit (eg ext3 journaling).
	 * Hence dirty accounting check is placed after invalidation.
	 */
	cancel_dirty_page(page);
	ClearPageMappedToDisk(page);
पूर्ण

/*
 * This is क्रम invalidate_mapping_pages().  That function can be called at
 * any समय, and is not supposed to throw away dirty pages.  But pages can
 * be marked dirty at any समय too, so use हटाओ_mapping which safely
 * discards clean, unused pages.
 *
 * Returns non-zero अगर the page was successfully invalidated.
 */
अटल पूर्णांक
invalidate_complete_page(काष्ठा address_space *mapping, काष्ठा page *page)
अणु
	पूर्णांक ret;

	अगर (page->mapping != mapping)
		वापस 0;

	अगर (page_has_निजी(page) && !try_to_release_page(page, 0))
		वापस 0;

	ret = हटाओ_mapping(mapping, page);

	वापस ret;
पूर्ण

पूर्णांक truncate_inode_page(काष्ठा address_space *mapping, काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(PageTail(page), page);

	अगर (page->mapping != mapping)
		वापस -EIO;

	truncate_cleanup_page(page);
	delete_from_page_cache(page);
	वापस 0;
पूर्ण

/*
 * Used to get rid of pages on hardware memory corruption.
 */
पूर्णांक generic_error_हटाओ_page(काष्ठा address_space *mapping, काष्ठा page *page)
अणु
	अगर (!mapping)
		वापस -EINVAL;
	/*
	 * Only punch क्रम normal data pages क्रम now.
	 * Handling other types like directories would need more auditing.
	 */
	अगर (!S_ISREG(mapping->host->i_mode))
		वापस -EIO;
	वापस truncate_inode_page(mapping, page);
पूर्ण
EXPORT_SYMBOL(generic_error_हटाओ_page);

/*
 * Safely invalidate one page from its pagecache mapping.
 * It only drops clean, unused pages. The page must be locked.
 *
 * Returns 1 अगर the page is successfully invalidated, otherwise 0.
 */
पूर्णांक invalidate_inode_page(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page_mapping(page);
	अगर (!mapping)
		वापस 0;
	अगर (PageDirty(page) || PageWriteback(page))
		वापस 0;
	अगर (page_mapped(page))
		वापस 0;
	वापस invalidate_complete_page(mapping, page);
पूर्ण

/**
 * truncate_inode_pages_range - truncate range of pages specअगरied by start & end byte offsets
 * @mapping: mapping to truncate
 * @lstart: offset from which to truncate
 * @lend: offset to which to truncate (inclusive)
 *
 * Truncate the page cache, removing the pages that are between
 * specअगरied offsets (and zeroing out partial pages
 * अगर lstart or lend + 1 is not page aligned).
 *
 * Truncate takes two passes - the first pass is nonblocking.  It will not
 * block on page locks and it will not block on ग_लिखोback.  The second pass
 * will रुको.  This is to prevent as much IO as possible in the affected region.
 * The first pass will हटाओ most pages, so the search cost of the second pass
 * is low.
 *
 * We pass करोwn the cache-hot hपूर्णांक to the page मुक्तing code.  Even अगर the
 * mapping is large, it is probably the हाल that the final pages are the most
 * recently touched, and मुक्तing happens in ascending file offset order.
 *
 * Note that since ->invalidatepage() accepts range to invalidate
 * truncate_inode_pages_range is able to handle हालs where lend + 1 is not
 * page aligned properly.
 */
व्योम truncate_inode_pages_range(काष्ठा address_space *mapping,
				loff_t lstart, loff_t lend)
अणु
	pgoff_t		start;		/* inclusive */
	pgoff_t		end;		/* exclusive */
	अचिन्हित पूर्णांक	partial_start;	/* inclusive */
	अचिन्हित पूर्णांक	partial_end;	/* exclusive */
	काष्ठा pagevec	pvec;
	pgoff_t		indices[PAGEVEC_SIZE];
	pgoff_t		index;
	पूर्णांक		i;

	अगर (mapping_empty(mapping))
		जाओ out;

	/* Offsets within partial pages */
	partial_start = lstart & (PAGE_SIZE - 1);
	partial_end = (lend + 1) & (PAGE_SIZE - 1);

	/*
	 * 'start' and 'end' always covers the range of pages to be fully
	 * truncated. Partial pages are covered with 'partial_start' at the
	 * start of the range and 'partial_end' at the end of the range.
	 * Note that 'end' is exclusive while 'lend' is inclusive.
	 */
	start = (lstart + PAGE_SIZE - 1) >> PAGE_SHIFT;
	अगर (lend == -1)
		/*
		 * lend == -1 indicates end-of-file so we have to set 'end'
		 * to the highest possible pgoff_t and since the type is
		 * अचिन्हित we're using -1.
		 */
		end = -1;
	अन्यथा
		end = (lend + 1) >> PAGE_SHIFT;

	pagevec_init(&pvec);
	index = start;
	जबतक (index < end && find_lock_entries(mapping, index, end - 1,
			&pvec, indices)) अणु
		index = indices[pagevec_count(&pvec) - 1] + 1;
		truncate_exceptional_pvec_entries(mapping, &pvec, indices);
		क्रम (i = 0; i < pagevec_count(&pvec); i++)
			truncate_cleanup_page(pvec.pages[i]);
		delete_from_page_cache_batch(mapping, &pvec);
		क्रम (i = 0; i < pagevec_count(&pvec); i++)
			unlock_page(pvec.pages[i]);
		pagevec_release(&pvec);
		cond_resched();
	पूर्ण

	अगर (partial_start) अणु
		काष्ठा page *page = find_lock_page(mapping, start - 1);
		अगर (page) अणु
			अचिन्हित पूर्णांक top = PAGE_SIZE;
			अगर (start > end) अणु
				/* Truncation within a single page */
				top = partial_end;
				partial_end = 0;
			पूर्ण
			रुको_on_page_ग_लिखोback(page);
			zero_user_segment(page, partial_start, top);
			cleancache_invalidate_page(mapping, page);
			अगर (page_has_निजी(page))
				करो_invalidatepage(page, partial_start,
						  top - partial_start);
			unlock_page(page);
			put_page(page);
		पूर्ण
	पूर्ण
	अगर (partial_end) अणु
		काष्ठा page *page = find_lock_page(mapping, end);
		अगर (page) अणु
			रुको_on_page_ग_लिखोback(page);
			zero_user_segment(page, 0, partial_end);
			cleancache_invalidate_page(mapping, page);
			अगर (page_has_निजी(page))
				करो_invalidatepage(page, 0,
						  partial_end);
			unlock_page(page);
			put_page(page);
		पूर्ण
	पूर्ण
	/*
	 * If the truncation happened within a single page no pages
	 * will be released, just zeroed, so we can bail out now.
	 */
	अगर (start >= end)
		जाओ out;

	index = start;
	क्रम ( ; ; ) अणु
		cond_resched();
		अगर (!find_get_entries(mapping, index, end - 1, &pvec,
				indices)) अणु
			/* If all gone from start onwards, we're करोne */
			अगर (index == start)
				अवरोध;
			/* Otherwise restart to make sure all gone */
			index = start;
			जारी;
		पूर्ण

		क्रम (i = 0; i < pagevec_count(&pvec); i++) अणु
			काष्ठा page *page = pvec.pages[i];

			/* We rely upon deletion not changing page->index */
			index = indices[i];

			अगर (xa_is_value(page))
				जारी;

			lock_page(page);
			WARN_ON(page_to_index(page) != index);
			रुको_on_page_ग_लिखोback(page);
			truncate_inode_page(mapping, page);
			unlock_page(page);
		पूर्ण
		truncate_exceptional_pvec_entries(mapping, &pvec, indices);
		pagevec_release(&pvec);
		index++;
	पूर्ण

out:
	cleancache_invalidate_inode(mapping);
पूर्ण
EXPORT_SYMBOL(truncate_inode_pages_range);

/**
 * truncate_inode_pages - truncate *all* the pages from an offset
 * @mapping: mapping to truncate
 * @lstart: offset from which to truncate
 *
 * Called under (and serialised by) inode->i_mutex.
 *
 * Note: When this function वापसs, there can be a page in the process of
 * deletion (inside __delete_from_page_cache()) in the specअगरied range.  Thus
 * mapping->nrpages can be non-zero when this function वापसs even after
 * truncation of the whole mapping.
 */
व्योम truncate_inode_pages(काष्ठा address_space *mapping, loff_t lstart)
अणु
	truncate_inode_pages_range(mapping, lstart, (loff_t)-1);
पूर्ण
EXPORT_SYMBOL(truncate_inode_pages);

/**
 * truncate_inode_pages_final - truncate *all* pages beक्रमe inode dies
 * @mapping: mapping to truncate
 *
 * Called under (and serialized by) inode->i_mutex.
 *
 * Fileप्रणालीs have to use this in the .evict_inode path to inक्रमm the
 * VM that this is the final truncate and the inode is going away.
 */
व्योम truncate_inode_pages_final(काष्ठा address_space *mapping)
अणु
	/*
	 * Page reclaim can not participate in regular inode lअगरeसमय
	 * management (can't call iput()) and thus can race with the
	 * inode tearकरोwn.  Tell it when the address space is निकासing,
	 * so that it करोes not install eviction inक्रमmation after the
	 * final truncate has begun.
	 */
	mapping_set_निकासing(mapping);

	अगर (!mapping_empty(mapping)) अणु
		/*
		 * As truncation uses a lockless tree lookup, cycle
		 * the tree lock to make sure any ongoing tree
		 * modअगरication that करोes not see AS_EXITING is
		 * completed beक्रमe starting the final truncate.
		 */
		xa_lock_irq(&mapping->i_pages);
		xa_unlock_irq(&mapping->i_pages);
	पूर्ण

	/*
	 * Cleancache needs notअगरication even अगर there are no pages or shaकरोw
	 * entries.
	 */
	truncate_inode_pages(mapping, 0);
पूर्ण
EXPORT_SYMBOL(truncate_inode_pages_final);

अटल अचिन्हित दीर्घ __invalidate_mapping_pages(काष्ठा address_space *mapping,
		pgoff_t start, pgoff_t end, अचिन्हित दीर्घ *nr_pagevec)
अणु
	pgoff_t indices[PAGEVEC_SIZE];
	काष्ठा pagevec pvec;
	pgoff_t index = start;
	अचिन्हित दीर्घ ret;
	अचिन्हित दीर्घ count = 0;
	पूर्णांक i;

	pagevec_init(&pvec);
	जबतक (find_lock_entries(mapping, index, end, &pvec, indices)) अणु
		क्रम (i = 0; i < pagevec_count(&pvec); i++) अणु
			काष्ठा page *page = pvec.pages[i];

			/* We rely upon deletion not changing page->index */
			index = indices[i];

			अगर (xa_is_value(page)) अणु
				invalidate_exceptional_entry(mapping, index,
							     page);
				जारी;
			पूर्ण
			index += thp_nr_pages(page) - 1;

			ret = invalidate_inode_page(page);
			unlock_page(page);
			/*
			 * Invalidation is a hपूर्णांक that the page is no दीर्घer
			 * of पूर्णांकerest and try to speed up its reclaim.
			 */
			अगर (!ret) अणु
				deactivate_file_page(page);
				/* It is likely on the pagevec of a remote CPU */
				अगर (nr_pagevec)
					(*nr_pagevec)++;
			पूर्ण
			count += ret;
		पूर्ण
		pagevec_हटाओ_exceptionals(&pvec);
		pagevec_release(&pvec);
		cond_resched();
		index++;
	पूर्ण
	वापस count;
पूर्ण

/**
 * invalidate_mapping_pages - Invalidate all the unlocked pages of one inode
 * @mapping: the address_space which holds the pages to invalidate
 * @start: the offset 'from' which to invalidate
 * @end: the offset 'to' which to invalidate (inclusive)
 *
 * This function only हटाओs the unlocked pages, अगर you want to
 * हटाओ all the pages of one inode, you must call truncate_inode_pages.
 *
 * invalidate_mapping_pages() will not block on IO activity. It will not
 * invalidate pages which are dirty, locked, under ग_लिखोback or mapped पूर्णांकo
 * pagetables.
 *
 * Return: the number of the pages that were invalidated
 */
अचिन्हित दीर्घ invalidate_mapping_pages(काष्ठा address_space *mapping,
		pgoff_t start, pgoff_t end)
अणु
	वापस __invalidate_mapping_pages(mapping, start, end, शून्य);
पूर्ण
EXPORT_SYMBOL(invalidate_mapping_pages);

/**
 * invalidate_mapping_pagevec - Invalidate all the unlocked pages of one inode
 * @mapping: the address_space which holds the pages to invalidate
 * @start: the offset 'from' which to invalidate
 * @end: the offset 'to' which to invalidate (inclusive)
 * @nr_pagevec: invalidate failed page number क्रम caller
 *
 * This helper is similar to invalidate_mapping_pages(), except that it accounts
 * क्रम pages that are likely on a pagevec and counts them in @nr_pagevec, which
 * will be used by the caller.
 */
व्योम invalidate_mapping_pagevec(काष्ठा address_space *mapping,
		pgoff_t start, pgoff_t end, अचिन्हित दीर्घ *nr_pagevec)
अणु
	__invalidate_mapping_pages(mapping, start, end, nr_pagevec);
पूर्ण

/*
 * This is like invalidate_complete_page(), except it ignores the page's
 * refcount.  We करो this because invalidate_inode_pages2() needs stronger
 * invalidation guarantees, and cannot afक्रमd to leave pages behind because
 * shrink_page_list() has a temp ref on them, or because they're transiently
 * sitting in the lru_cache_add() pagevecs.
 */
अटल पूर्णांक
invalidate_complete_page2(काष्ठा address_space *mapping, काष्ठा page *page)
अणु
	अचिन्हित दीर्घ flags;

	अगर (page->mapping != mapping)
		वापस 0;

	अगर (page_has_निजी(page) && !try_to_release_page(page, GFP_KERNEL))
		वापस 0;

	xa_lock_irqsave(&mapping->i_pages, flags);
	अगर (PageDirty(page))
		जाओ failed;

	BUG_ON(page_has_निजी(page));
	__delete_from_page_cache(page, शून्य);
	xa_unlock_irqrestore(&mapping->i_pages, flags);

	अगर (mapping->a_ops->मुक्तpage)
		mapping->a_ops->मुक्तpage(page);

	put_page(page);	/* pagecache ref */
	वापस 1;
failed:
	xa_unlock_irqrestore(&mapping->i_pages, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_launder_page(काष्ठा address_space *mapping, काष्ठा page *page)
अणु
	अगर (!PageDirty(page))
		वापस 0;
	अगर (page->mapping != mapping || mapping->a_ops->launder_page == शून्य)
		वापस 0;
	वापस mapping->a_ops->launder_page(page);
पूर्ण

/**
 * invalidate_inode_pages2_range - हटाओ range of pages from an address_space
 * @mapping: the address_space
 * @start: the page offset 'from' which to invalidate
 * @end: the page offset 'to' which to invalidate (inclusive)
 *
 * Any pages which are found to be mapped पूर्णांकo pagetables are unmapped prior to
 * invalidation.
 *
 * Return: -EBUSY अगर any pages could not be invalidated.
 */
पूर्णांक invalidate_inode_pages2_range(काष्ठा address_space *mapping,
				  pgoff_t start, pgoff_t end)
अणु
	pgoff_t indices[PAGEVEC_SIZE];
	काष्ठा pagevec pvec;
	pgoff_t index;
	पूर्णांक i;
	पूर्णांक ret = 0;
	पूर्णांक ret2 = 0;
	पूर्णांक did_range_unmap = 0;

	अगर (mapping_empty(mapping))
		जाओ out;

	pagevec_init(&pvec);
	index = start;
	जबतक (find_get_entries(mapping, index, end, &pvec, indices)) अणु
		क्रम (i = 0; i < pagevec_count(&pvec); i++) अणु
			काष्ठा page *page = pvec.pages[i];

			/* We rely upon deletion not changing page->index */
			index = indices[i];

			अगर (xa_is_value(page)) अणु
				अगर (!invalidate_exceptional_entry2(mapping,
								   index, page))
					ret = -EBUSY;
				जारी;
			पूर्ण

			अगर (!did_range_unmap && page_mapped(page)) अणु
				/*
				 * If page is mapped, beक्रमe taking its lock,
				 * zap the rest of the file in one hit.
				 */
				unmap_mapping_pages(mapping, index,
						(1 + end - index), false);
				did_range_unmap = 1;
			पूर्ण

			lock_page(page);
			WARN_ON(page_to_index(page) != index);
			अगर (page->mapping != mapping) अणु
				unlock_page(page);
				जारी;
			पूर्ण
			रुको_on_page_ग_लिखोback(page);

			अगर (page_mapped(page))
				unmap_mapping_page(page);
			BUG_ON(page_mapped(page));

			ret2 = करो_launder_page(mapping, page);
			अगर (ret2 == 0) अणु
				अगर (!invalidate_complete_page2(mapping, page))
					ret2 = -EBUSY;
			पूर्ण
			अगर (ret2 < 0)
				ret = ret2;
			unlock_page(page);
		पूर्ण
		pagevec_हटाओ_exceptionals(&pvec);
		pagevec_release(&pvec);
		cond_resched();
		index++;
	पूर्ण
	/*
	 * For DAX we invalidate page tables after invalidating page cache.  We
	 * could invalidate page tables जबतक invalidating each entry however
	 * that would be expensive. And करोing range unmapping beक्रमe करोesn't
	 * work as we have no cheap way to find whether page cache entry didn't
	 * get remapped later.
	 */
	अगर (dax_mapping(mapping)) अणु
		unmap_mapping_pages(mapping, start, end - start + 1, false);
	पूर्ण
out:
	cleancache_invalidate_inode(mapping);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(invalidate_inode_pages2_range);

/**
 * invalidate_inode_pages2 - हटाओ all pages from an address_space
 * @mapping: the address_space
 *
 * Any pages which are found to be mapped पूर्णांकo pagetables are unmapped prior to
 * invalidation.
 *
 * Return: -EBUSY अगर any pages could not be invalidated.
 */
पूर्णांक invalidate_inode_pages2(काष्ठा address_space *mapping)
अणु
	वापस invalidate_inode_pages2_range(mapping, 0, -1);
पूर्ण
EXPORT_SYMBOL_GPL(invalidate_inode_pages2);

/**
 * truncate_pagecache - unmap and हटाओ pagecache that has been truncated
 * @inode: inode
 * @newsize: new file size
 *
 * inode's new i_size must alपढ़ोy be written beक्रमe truncate_pagecache
 * is called.
 *
 * This function should typically be called beक्रमe the fileप्रणाली
 * releases resources associated with the मुक्तd range (eg. deallocates
 * blocks). This way, pagecache will always stay logically coherent
 * with on-disk क्रमmat, and the fileप्रणाली would not have to deal with
 * situations such as ग_लिखोpage being called क्रम a page that has alपढ़ोy
 * had its underlying blocks deallocated.
 */
व्योम truncate_pagecache(काष्ठा inode *inode, loff_t newsize)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	loff_t holebegin = round_up(newsize, PAGE_SIZE);

	/*
	 * unmap_mapping_range is called twice, first simply क्रम
	 * efficiency so that truncate_inode_pages करोes fewer
	 * single-page unmaps.  However after this first call, and
	 * beक्रमe truncate_inode_pages finishes, it is possible क्रम
	 * निजी pages to be COWed, which reमुख्य after
	 * truncate_inode_pages finishes, hence the second
	 * unmap_mapping_range call must be made क्रम correctness.
	 */
	unmap_mapping_range(mapping, holebegin, 0, 1);
	truncate_inode_pages(mapping, newsize);
	unmap_mapping_range(mapping, holebegin, 0, 1);
पूर्ण
EXPORT_SYMBOL(truncate_pagecache);

/**
 * truncate_setsize - update inode and pagecache क्रम a new file size
 * @inode: inode
 * @newsize: new file size
 *
 * truncate_setsize updates i_size and perक्रमms pagecache truncation (अगर
 * necessary) to @newsize. It will be typically be called from the fileप्रणाली's
 * setattr function when ATTR_SIZE is passed in.
 *
 * Must be called with a lock serializing truncates and ग_लिखोs (generally
 * i_mutex but e.g. xfs uses a dअगरferent lock) and beक्रमe all fileप्रणाली
 * specअगरic block truncation has been perक्रमmed.
 */
व्योम truncate_setsize(काष्ठा inode *inode, loff_t newsize)
अणु
	loff_t oldsize = inode->i_size;

	i_size_ग_लिखो(inode, newsize);
	अगर (newsize > oldsize)
		pagecache_isize_extended(inode, oldsize, newsize);
	truncate_pagecache(inode, newsize);
पूर्ण
EXPORT_SYMBOL(truncate_setsize);

/**
 * pagecache_isize_extended - update pagecache after extension of i_size
 * @inode:	inode क्रम which i_size was extended
 * @from:	original inode size
 * @to:		new inode size
 *
 * Handle extension of inode size either caused by extending truncate or by
 * ग_लिखो starting after current i_size. We mark the page straddling current
 * i_size RO so that page_mkग_लिखो() is called on the nearest ग_लिखो access to
 * the page.  This way fileप्रणाली can be sure that page_mkग_लिखो() is called on
 * the page beक्रमe user ग_लिखोs to the page via mmap after the i_size has been
 * changed.
 *
 * The function must be called after i_size is updated so that page fault
 * coming after we unlock the page will alपढ़ोy see the new i_size.
 * The function must be called जबतक we still hold i_mutex - this not only
 * makes sure i_size is stable but also that userspace cannot observe new
 * i_size value beक्रमe we are prepared to store mmap ग_लिखोs at new inode size.
 */
व्योम pagecache_isize_extended(काष्ठा inode *inode, loff_t from, loff_t to)
अणु
	पूर्णांक bsize = i_blocksize(inode);
	loff_t rounded_from;
	काष्ठा page *page;
	pgoff_t index;

	WARN_ON(to > inode->i_size);

	अगर (from >= to || bsize == PAGE_SIZE)
		वापस;
	/* Page straddling @from will not have any hole block created? */
	rounded_from = round_up(from, bsize);
	अगर (to <= rounded_from || !(rounded_from & (PAGE_SIZE - 1)))
		वापस;

	index = from >> PAGE_SHIFT;
	page = find_lock_page(inode->i_mapping, index);
	/* Page not cached? Nothing to करो */
	अगर (!page)
		वापस;
	/*
	 * See clear_page_dirty_क्रम_io() क्रम details why set_page_dirty()
	 * is needed.
	 */
	अगर (page_mkclean(page))
		set_page_dirty(page);
	unlock_page(page);
	put_page(page);
पूर्ण
EXPORT_SYMBOL(pagecache_isize_extended);

/**
 * truncate_pagecache_range - unmap and हटाओ pagecache that is hole-punched
 * @inode: inode
 * @lstart: offset of beginning of hole
 * @lend: offset of last byte of hole
 *
 * This function should typically be called beक्रमe the fileप्रणाली
 * releases resources associated with the मुक्तd range (eg. deallocates
 * blocks). This way, pagecache will always stay logically coherent
 * with on-disk क्रमmat, and the fileप्रणाली would not have to deal with
 * situations such as ग_लिखोpage being called क्रम a page that has alपढ़ोy
 * had its underlying blocks deallocated.
 */
व्योम truncate_pagecache_range(काष्ठा inode *inode, loff_t lstart, loff_t lend)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	loff_t unmap_start = round_up(lstart, PAGE_SIZE);
	loff_t unmap_end = round_करोwn(1 + lend, PAGE_SIZE) - 1;
	/*
	 * This rounding is currently just क्रम example: unmap_mapping_range
	 * expands its hole outwards, whereas we want it to contract the hole
	 * inwards.  However, existing callers of truncate_pagecache_range are
	 * करोing their own page rounding first.  Note that unmap_mapping_range
	 * allows holelen 0 क्रम all, and we allow lend -1 क्रम end of file.
	 */

	/*
	 * Unlike in truncate_pagecache, unmap_mapping_range is called only
	 * once (beक्रमe truncating pagecache), and without "even_cows" flag:
	 * hole-punching should not हटाओ निजी COWed pages from the hole.
	 */
	अगर ((u64)unmap_end > (u64)unmap_start)
		unmap_mapping_range(mapping, unmap_start,
				    1 + unmap_end - unmap_start, 0);
	truncate_inode_pages_range(mapping, lstart, lend);
पूर्ण
EXPORT_SYMBOL(truncate_pagecache_range);
