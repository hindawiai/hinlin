<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PAGEMAP_H
#घोषणा _LINUX_PAGEMAP_H

/*
 * Copyright 1995 Linus Torvalds
 */
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/list.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/compiler.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/gfp.h>
#समावेश <linux/bitops.h>
#समावेश <linux/hardirq.h> /* क्रम in_पूर्णांकerrupt() */
#समावेश <linux/hugetlb_अंतरभूत.h>

काष्ठा pagevec;

अटल अंतरभूत bool mapping_empty(काष्ठा address_space *mapping)
अणु
	वापस xa_empty(&mapping->i_pages);
पूर्ण

/*
 * Bits in mapping->flags.
 */
क्रमागत mapping_flags अणु
	AS_EIO		= 0,	/* IO error on async ग_लिखो */
	AS_ENOSPC	= 1,	/* ENOSPC on async ग_लिखो */
	AS_MM_ALL_LOCKS	= 2,	/* under mm_take_all_locks() */
	AS_UNEVICTABLE	= 3,	/* e.g., ramdisk, SHM_LOCK */
	AS_EXITING	= 4, 	/* final truncate in progress */
	/* ग_लिखोback related tags are not used */
	AS_NO_WRITEBACK_TAGS = 5,
	AS_THP_SUPPORT = 6,	/* THPs supported */
पूर्ण;

/**
 * mapping_set_error - record a ग_लिखोback error in the address_space
 * @mapping: the mapping in which an error should be set
 * @error: the error to set in the mapping
 *
 * When ग_लिखोback fails in some way, we must record that error so that
 * userspace can be inक्रमmed when fsync and the like are called.  We endeavor
 * to report errors on any file that was खोलो at the समय of the error.  Some
 * पूर्णांकernal callers also need to know when ग_लिखोback errors have occurred.
 *
 * When a ग_लिखोback error occurs, most fileप्रणालीs will want to call
 * mapping_set_error to record the error in the mapping so that it can be
 * reported when the application calls fsync(2).
 */
अटल अंतरभूत व्योम mapping_set_error(काष्ठा address_space *mapping, पूर्णांक error)
अणु
	अगर (likely(!error))
		वापस;

	/* Record in wb_err क्रम checkers using errseq_t based tracking */
	__filemap_set_wb_err(mapping, error);

	/* Record it in superblock */
	अगर (mapping->host)
		errseq_set(&mapping->host->i_sb->s_wb_err, error);

	/* Record it in flags क्रम now, क्रम legacy callers */
	अगर (error == -ENOSPC)
		set_bit(AS_ENOSPC, &mapping->flags);
	अन्यथा
		set_bit(AS_EIO, &mapping->flags);
पूर्ण

अटल अंतरभूत व्योम mapping_set_unevictable(काष्ठा address_space *mapping)
अणु
	set_bit(AS_UNEVICTABLE, &mapping->flags);
पूर्ण

अटल अंतरभूत व्योम mapping_clear_unevictable(काष्ठा address_space *mapping)
अणु
	clear_bit(AS_UNEVICTABLE, &mapping->flags);
पूर्ण

अटल अंतरभूत bool mapping_unevictable(काष्ठा address_space *mapping)
अणु
	वापस mapping && test_bit(AS_UNEVICTABLE, &mapping->flags);
पूर्ण

अटल अंतरभूत व्योम mapping_set_निकासing(काष्ठा address_space *mapping)
अणु
	set_bit(AS_EXITING, &mapping->flags);
पूर्ण

अटल अंतरभूत पूर्णांक mapping_निकासing(काष्ठा address_space *mapping)
अणु
	वापस test_bit(AS_EXITING, &mapping->flags);
पूर्ण

अटल अंतरभूत व्योम mapping_set_no_ग_लिखोback_tags(काष्ठा address_space *mapping)
अणु
	set_bit(AS_NO_WRITEBACK_TAGS, &mapping->flags);
पूर्ण

अटल अंतरभूत पूर्णांक mapping_use_ग_लिखोback_tags(काष्ठा address_space *mapping)
अणु
	वापस !test_bit(AS_NO_WRITEBACK_TAGS, &mapping->flags);
पूर्ण

अटल अंतरभूत gfp_t mapping_gfp_mask(काष्ठा address_space * mapping)
अणु
	वापस mapping->gfp_mask;
पूर्ण

/* Restricts the given gfp_mask to what the mapping allows. */
अटल अंतरभूत gfp_t mapping_gfp_स्थिरraपूर्णांक(काष्ठा address_space *mapping,
		gfp_t gfp_mask)
अणु
	वापस mapping_gfp_mask(mapping) & gfp_mask;
पूर्ण

/*
 * This is non-atomic.  Only to be used beक्रमe the mapping is activated.
 * Probably needs a barrier...
 */
अटल अंतरभूत व्योम mapping_set_gfp_mask(काष्ठा address_space *m, gfp_t mask)
अणु
	m->gfp_mask = mask;
पूर्ण

अटल अंतरभूत bool mapping_thp_support(काष्ठा address_space *mapping)
अणु
	वापस test_bit(AS_THP_SUPPORT, &mapping->flags);
पूर्ण

अटल अंतरभूत पूर्णांक filemap_nr_thps(काष्ठा address_space *mapping)
अणु
#अगर_घोषित CONFIG_READ_ONLY_THP_FOR_FS
	वापस atomic_पढ़ो(&mapping->nr_thps);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम filemap_nr_thps_inc(काष्ठा address_space *mapping)
अणु
#अगर_घोषित CONFIG_READ_ONLY_THP_FOR_FS
	अगर (!mapping_thp_support(mapping))
		atomic_inc(&mapping->nr_thps);
#अन्यथा
	WARN_ON_ONCE(1);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम filemap_nr_thps_dec(काष्ठा address_space *mapping)
अणु
#अगर_घोषित CONFIG_READ_ONLY_THP_FOR_FS
	अगर (!mapping_thp_support(mapping))
		atomic_dec(&mapping->nr_thps);
#अन्यथा
	WARN_ON_ONCE(1);
#पूर्ण_अगर
पूर्ण

व्योम release_pages(काष्ठा page **pages, पूर्णांक nr);

/*
 * For file cache pages, वापस the address_space, otherwise वापस शून्य
 */
अटल अंतरभूत काष्ठा address_space *page_mapping_file(काष्ठा page *page)
अणु
	अगर (unlikely(PageSwapCache(page)))
		वापस शून्य;
	वापस page_mapping(page);
पूर्ण

/*
 * speculatively take a reference to a page.
 * If the page is मुक्त (_refcount == 0), then _refcount is untouched, and 0
 * is वापसed. Otherwise, _refcount is incremented by 1 and 1 is वापसed.
 *
 * This function must be called inside the same rcu_पढ़ो_lock() section as has
 * been used to lookup the page in the pagecache radix-tree (or page table):
 * this allows allocators to use a synchronize_rcu() to stabilize _refcount.
 *
 * Unless an RCU grace period has passed, the count of all pages coming out
 * of the allocator must be considered unstable. page_count may वापस higher
 * than expected, and put_page must be able to करो the right thing when the
 * page has been finished with, no matter what it is subsequently allocated
 * क्रम (because put_page is what is used here to drop an invalid speculative
 * reference).
 *
 * This is the पूर्णांकeresting part of the lockless pagecache (and lockless
 * get_user_pages) locking protocol, where the lookup-side (eg. find_get_page)
 * has the following pattern:
 * 1. find page in radix tree
 * 2. conditionally increment refcount
 * 3. check the page is still in pagecache (अगर no, जाओ 1)
 *
 * Remove-side that cares about stability of _refcount (eg. reclaim) has the
 * following (with the i_pages lock held):
 * A. atomically check refcount is correct and set it to 0 (atomic_cmpxchg)
 * B. हटाओ page from pagecache
 * C. मुक्त the page
 *
 * There are 2 critical पूर्णांकerleavings that matter:
 * - 2 runs beक्रमe A: in this हाल, A sees elevated refcount and bails out
 * - A runs beक्रमe 2: in this हाल, 2 sees zero refcount and retries;
 *   subsequently, B will complete and 1 will find no page, causing the
 *   lookup to वापस शून्य.
 *
 * It is possible that between 1 and 2, the page is हटाओd then the exact same
 * page is inserted पूर्णांकo the same position in pagecache. That's OK: the
 * old find_get_page using a lock could equally have run beक्रमe or after
 * such a re-insertion, depending on order that locks are granted.
 *
 * Lookups racing against pagecache insertion isn't a big problem: either 1
 * will find the page or it will not. Likewise, the old find_get_page could run
 * either beक्रमe the insertion or afterwards, depending on timing.
 */
अटल अंतरभूत पूर्णांक __page_cache_add_speculative(काष्ठा page *page, पूर्णांक count)
अणु
#अगर_घोषित CONFIG_TINY_RCU
# अगरdef CONFIG_PREEMPT_COUNT
	VM_BUG_ON(!in_atomic() && !irqs_disabled());
# endअगर
	/*
	 * Preempt must be disabled here - we rely on rcu_पढ़ो_lock करोing
	 * this क्रम us.
	 *
	 * Pagecache won't be truncated from पूर्णांकerrupt context, so अगर we have
	 * found a page in the radix tree here, we have pinned its refcount by
	 * disabling preempt, and hence no need क्रम the "speculative get" that
	 * SMP requires.
	 */
	VM_BUG_ON_PAGE(page_count(page) == 0, page);
	page_ref_add(page, count);

#अन्यथा
	अगर (unlikely(!page_ref_add_unless(page, count, 0))) अणु
		/*
		 * Either the page has been मुक्तd, or will be मुक्तd.
		 * In either हाल, retry here and the caller should
		 * करो the right thing (see comments above).
		 */
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	VM_BUG_ON_PAGE(PageTail(page), page);

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक page_cache_get_speculative(काष्ठा page *page)
अणु
	वापस __page_cache_add_speculative(page, 1);
पूर्ण

अटल अंतरभूत पूर्णांक page_cache_add_speculative(काष्ठा page *page, पूर्णांक count)
अणु
	वापस __page_cache_add_speculative(page, count);
पूर्ण

/**
 * attach_page_निजी - Attach निजी data to a page.
 * @page: Page to attach data to.
 * @data: Data to attach to page.
 *
 * Attaching निजी data to a page increments the page's reference count.
 * The data must be detached beक्रमe the page will be मुक्तd.
 */
अटल अंतरभूत व्योम attach_page_निजी(काष्ठा page *page, व्योम *data)
अणु
	get_page(page);
	set_page_निजी(page, (अचिन्हित दीर्घ)data);
	SetPagePrivate(page);
पूर्ण

/**
 * detach_page_निजी - Detach निजी data from a page.
 * @page: Page to detach data from.
 *
 * Removes the data that was previously attached to the page and decrements
 * the refcount on the page.
 *
 * Return: Data that was attached to the page.
 */
अटल अंतरभूत व्योम *detach_page_निजी(काष्ठा page *page)
अणु
	व्योम *data = (व्योम *)page_निजी(page);

	अगर (!PagePrivate(page))
		वापस शून्य;
	ClearPagePrivate(page);
	set_page_निजी(page, 0);
	put_page(page);

	वापस data;
पूर्ण

#अगर_घोषित CONFIG_NUMA
बाह्य काष्ठा page *__page_cache_alloc(gfp_t gfp);
#अन्यथा
अटल अंतरभूत काष्ठा page *__page_cache_alloc(gfp_t gfp)
अणु
	वापस alloc_pages(gfp, 0);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा page *page_cache_alloc(काष्ठा address_space *x)
अणु
	वापस __page_cache_alloc(mapping_gfp_mask(x));
पूर्ण

अटल अंतरभूत gfp_t पढ़ोahead_gfp_mask(काष्ठा address_space *x)
अणु
	वापस mapping_gfp_mask(x) | __GFP_NORETRY | __GFP_NOWARN;
पूर्ण

प्रकार पूर्णांक filler_t(व्योम *, काष्ठा page *);

pgoff_t page_cache_next_miss(काष्ठा address_space *mapping,
			     pgoff_t index, अचिन्हित दीर्घ max_scan);
pgoff_t page_cache_prev_miss(काष्ठा address_space *mapping,
			     pgoff_t index, अचिन्हित दीर्घ max_scan);

#घोषणा FGP_ACCESSED		0x00000001
#घोषणा FGP_LOCK		0x00000002
#घोषणा FGP_CREAT		0x00000004
#घोषणा FGP_WRITE		0x00000008
#घोषणा FGP_NOFS		0x00000010
#घोषणा FGP_NOWAIT		0x00000020
#घोषणा FGP_FOR_MMAP		0x00000040
#घोषणा FGP_HEAD		0x00000080
#घोषणा FGP_ENTRY		0x00000100

काष्ठा page *pagecache_get_page(काष्ठा address_space *mapping, pgoff_t offset,
		पूर्णांक fgp_flags, gfp_t cache_gfp_mask);

/**
 * find_get_page - find and get a page reference
 * @mapping: the address_space to search
 * @offset: the page index
 *
 * Looks up the page cache slot at @mapping & @offset.  If there is a
 * page cache page, it is वापसed with an increased refcount.
 *
 * Otherwise, %शून्य is वापसed.
 */
अटल अंतरभूत काष्ठा page *find_get_page(काष्ठा address_space *mapping,
					pgoff_t offset)
अणु
	वापस pagecache_get_page(mapping, offset, 0, 0);
पूर्ण

अटल अंतरभूत काष्ठा page *find_get_page_flags(काष्ठा address_space *mapping,
					pgoff_t offset, पूर्णांक fgp_flags)
अणु
	वापस pagecache_get_page(mapping, offset, fgp_flags, 0);
पूर्ण

/**
 * find_lock_page - locate, pin and lock a pagecache page
 * @mapping: the address_space to search
 * @index: the page index
 *
 * Looks up the page cache entry at @mapping & @index.  If there is a
 * page cache page, it is वापसed locked and with an increased
 * refcount.
 *
 * Context: May sleep.
 * Return: A काष्ठा page or %शून्य अगर there is no page in the cache क्रम this
 * index.
 */
अटल अंतरभूत काष्ठा page *find_lock_page(काष्ठा address_space *mapping,
					pgoff_t index)
अणु
	वापस pagecache_get_page(mapping, index, FGP_LOCK, 0);
पूर्ण

/**
 * find_lock_head - Locate, pin and lock a pagecache page.
 * @mapping: The address_space to search.
 * @index: The page index.
 *
 * Looks up the page cache entry at @mapping & @index.  If there is a
 * page cache page, its head page is वापसed locked and with an increased
 * refcount.
 *
 * Context: May sleep.
 * Return: A काष्ठा page which is !PageTail, or %शून्य अगर there is no page
 * in the cache क्रम this index.
 */
अटल अंतरभूत काष्ठा page *find_lock_head(काष्ठा address_space *mapping,
					pgoff_t index)
अणु
	वापस pagecache_get_page(mapping, index, FGP_LOCK | FGP_HEAD, 0);
पूर्ण

/**
 * find_or_create_page - locate or add a pagecache page
 * @mapping: the page's address_space
 * @index: the page's index पूर्णांकo the mapping
 * @gfp_mask: page allocation mode
 *
 * Looks up the page cache slot at @mapping & @offset.  If there is a
 * page cache page, it is वापसed locked and with an increased
 * refcount.
 *
 * If the page is not present, a new page is allocated using @gfp_mask
 * and added to the page cache and the VM's LRU list.  The page is
 * वापसed locked and with an increased refcount.
 *
 * On memory exhaustion, %शून्य is वापसed.
 *
 * find_or_create_page() may sleep, even अगर @gfp_flags specअगरies an
 * atomic allocation!
 */
अटल अंतरभूत काष्ठा page *find_or_create_page(काष्ठा address_space *mapping,
					pgoff_t index, gfp_t gfp_mask)
अणु
	वापस pagecache_get_page(mapping, index,
					FGP_LOCK|FGP_ACCESSED|FGP_CREAT,
					gfp_mask);
पूर्ण

/**
 * grab_cache_page_noरुको - वापसs locked page at given index in given cache
 * @mapping: target address_space
 * @index: the page index
 *
 * Same as grab_cache_page(), but करो not रुको अगर the page is unavailable.
 * This is पूर्णांकended क्रम speculative data generators, where the data can
 * be regenerated अगर the page couldn't be grabbed.  This routine should
 * be safe to call जबतक holding the lock क्रम another page.
 *
 * Clear __GFP_FS when allocating the page to aव्योम recursion पूर्णांकo the fs
 * and deadlock against the caller's locked page.
 */
अटल अंतरभूत काष्ठा page *grab_cache_page_noरुको(काष्ठा address_space *mapping,
				pgoff_t index)
अणु
	वापस pagecache_get_page(mapping, index,
			FGP_LOCK|FGP_CREAT|FGP_NOFS|FGP_NOWAIT,
			mapping_gfp_mask(mapping));
पूर्ण

/* Does this page contain this index? */
अटल अंतरभूत bool thp_contains(काष्ठा page *head, pgoff_t index)
अणु
	/* HugeTLBfs indexes the page cache in units of hpage_size */
	अगर (PageHuge(head))
		वापस head->index == index;
	वापस page_index(head) == (index & ~(thp_nr_pages(head) - 1UL));
पूर्ण

/*
 * Given the page we found in the page cache, वापस the page corresponding
 * to this index in the file
 */
अटल अंतरभूत काष्ठा page *find_subpage(काष्ठा page *head, pgoff_t index)
अणु
	/* HugeTLBfs wants the head page regardless */
	अगर (PageHuge(head))
		वापस head;

	वापस head + (index & (thp_nr_pages(head) - 1));
पूर्ण

अचिन्हित find_get_entries(काष्ठा address_space *mapping, pgoff_t start,
		pgoff_t end, काष्ठा pagevec *pvec, pgoff_t *indices);
अचिन्हित find_get_pages_range(काष्ठा address_space *mapping, pgoff_t *start,
			pgoff_t end, अचिन्हित पूर्णांक nr_pages,
			काष्ठा page **pages);
अटल अंतरभूत अचिन्हित find_get_pages(काष्ठा address_space *mapping,
			pgoff_t *start, अचिन्हित पूर्णांक nr_pages,
			काष्ठा page **pages)
अणु
	वापस find_get_pages_range(mapping, start, (pgoff_t)-1, nr_pages,
				    pages);
पूर्ण
अचिन्हित find_get_pages_contig(काष्ठा address_space *mapping, pgoff_t start,
			       अचिन्हित पूर्णांक nr_pages, काष्ठा page **pages);
अचिन्हित find_get_pages_range_tag(काष्ठा address_space *mapping, pgoff_t *index,
			pgoff_t end, xa_mark_t tag, अचिन्हित पूर्णांक nr_pages,
			काष्ठा page **pages);
अटल अंतरभूत अचिन्हित find_get_pages_tag(काष्ठा address_space *mapping,
			pgoff_t *index, xa_mark_t tag, अचिन्हित पूर्णांक nr_pages,
			काष्ठा page **pages)
अणु
	वापस find_get_pages_range_tag(mapping, index, (pgoff_t)-1, tag,
					nr_pages, pages);
पूर्ण

काष्ठा page *grab_cache_page_ग_लिखो_begin(काष्ठा address_space *mapping,
			pgoff_t index, अचिन्हित flags);

/*
 * Returns locked page at given index in given cache, creating it अगर needed.
 */
अटल अंतरभूत काष्ठा page *grab_cache_page(काष्ठा address_space *mapping,
								pgoff_t index)
अणु
	वापस find_or_create_page(mapping, index, mapping_gfp_mask(mapping));
पूर्ण

बाह्य काष्ठा page * पढ़ो_cache_page(काष्ठा address_space *mapping,
				pgoff_t index, filler_t *filler, व्योम *data);
बाह्य काष्ठा page * पढ़ो_cache_page_gfp(काष्ठा address_space *mapping,
				pgoff_t index, gfp_t gfp_mask);
बाह्य पूर्णांक पढ़ो_cache_pages(काष्ठा address_space *mapping,
		काष्ठा list_head *pages, filler_t *filler, व्योम *data);

अटल अंतरभूत काष्ठा page *पढ़ो_mapping_page(काष्ठा address_space *mapping,
				pgoff_t index, व्योम *data)
अणु
	वापस पढ़ो_cache_page(mapping, index, शून्य, data);
पूर्ण

/*
 * Get index of the page with in radix-tree
 * (TODO: हटाओ once hugetlb pages will have ->index in PAGE_SIZE)
 */
अटल अंतरभूत pgoff_t page_to_index(काष्ठा page *page)
अणु
	pgoff_t pgoff;

	अगर (likely(!PageTransTail(page)))
		वापस page->index;

	/*
	 *  We करोn't initialize ->index क्रम tail pages: calculate based on
	 *  head page
	 */
	pgoff = compound_head(page)->index;
	pgoff += page - compound_head(page);
	वापस pgoff;
पूर्ण

/*
 * Get the offset in PAGE_SIZE.
 * (TODO: hugepage should have ->index in PAGE_SIZE)
 */
अटल अंतरभूत pgoff_t page_to_pgoff(काष्ठा page *page)
अणु
	अगर (unlikely(PageHeadHuge(page)))
		वापस page->index << compound_order(page);

	वापस page_to_index(page);
पूर्ण

/*
 * Return byte-offset पूर्णांकo fileप्रणाली object क्रम page.
 */
अटल अंतरभूत loff_t page_offset(काष्ठा page *page)
अणु
	वापस ((loff_t)page->index) << PAGE_SHIFT;
पूर्ण

अटल अंतरभूत loff_t page_file_offset(काष्ठा page *page)
अणु
	वापस ((loff_t)page_index(page)) << PAGE_SHIFT;
पूर्ण

बाह्य pgoff_t linear_hugepage_index(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ address);

अटल अंतरभूत pgoff_t linear_page_index(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ address)
अणु
	pgoff_t pgoff;
	अगर (unlikely(is_vm_hugetlb_page(vma)))
		वापस linear_hugepage_index(vma, address);
	pgoff = (address - vma->vm_start) >> PAGE_SHIFT;
	pgoff += vma->vm_pgoff;
	वापस pgoff;
पूर्ण

काष्ठा रुको_page_key अणु
	काष्ठा page *page;
	पूर्णांक bit_nr;
	पूर्णांक page_match;
पूर्ण;

काष्ठा रुको_page_queue अणु
	काष्ठा page *page;
	पूर्णांक bit_nr;
	रुको_queue_entry_t रुको;
पूर्ण;

अटल अंतरभूत bool wake_page_match(काष्ठा रुको_page_queue *रुको_page,
				  काष्ठा रुको_page_key *key)
अणु
	अगर (रुको_page->page != key->page)
	       वापस false;
	key->page_match = 1;

	अगर (रुको_page->bit_nr != key->bit_nr)
		वापस false;

	वापस true;
पूर्ण

बाह्य व्योम __lock_page(काष्ठा page *page);
बाह्य पूर्णांक __lock_page_समाप्तable(काष्ठा page *page);
बाह्य पूर्णांक __lock_page_async(काष्ठा page *page, काष्ठा रुको_page_queue *रुको);
बाह्य पूर्णांक __lock_page_or_retry(काष्ठा page *page, काष्ठा mm_काष्ठा *mm,
				अचिन्हित पूर्णांक flags);
बाह्य व्योम unlock_page(काष्ठा page *page);

/*
 * Return true अगर the page was successfully locked
 */
अटल अंतरभूत पूर्णांक trylock_page(काष्ठा page *page)
अणु
	page = compound_head(page);
	वापस (likely(!test_and_set_bit_lock(PG_locked, &page->flags)));
पूर्ण

/*
 * lock_page may only be called अगर we have the page's inode pinned.
 */
अटल अंतरभूत व्योम lock_page(काष्ठा page *page)
अणु
	might_sleep();
	अगर (!trylock_page(page))
		__lock_page(page);
पूर्ण

/*
 * lock_page_समाप्तable is like lock_page but can be पूर्णांकerrupted by fatal
 * संकेतs.  It वापसs 0 अगर it locked the page and -EINTR अगर it was
 * समाप्तed जबतक रुकोing.
 */
अटल अंतरभूत पूर्णांक lock_page_समाप्तable(काष्ठा page *page)
अणु
	might_sleep();
	अगर (!trylock_page(page))
		वापस __lock_page_समाप्तable(page);
	वापस 0;
पूर्ण

/*
 * lock_page_async - Lock the page, unless this would block. If the page
 * is alपढ़ोy locked, then queue a callback when the page becomes unlocked.
 * This callback can then retry the operation.
 *
 * Returns 0 अगर the page is locked successfully, or -EIOCBQUEUED अगर the page
 * was alपढ़ोy locked and the callback defined in 'wait' was queued.
 */
अटल अंतरभूत पूर्णांक lock_page_async(काष्ठा page *page,
				  काष्ठा रुको_page_queue *रुको)
अणु
	अगर (!trylock_page(page))
		वापस __lock_page_async(page, रुको);
	वापस 0;
पूर्ण

/*
 * lock_page_or_retry - Lock the page, unless this would block and the
 * caller indicated that it can handle a retry.
 *
 * Return value and mmap_lock implications depend on flags; see
 * __lock_page_or_retry().
 */
अटल अंतरभूत पूर्णांक lock_page_or_retry(काष्ठा page *page, काष्ठा mm_काष्ठा *mm,
				     अचिन्हित पूर्णांक flags)
अणु
	might_sleep();
	वापस trylock_page(page) || __lock_page_or_retry(page, mm, flags);
पूर्ण

/*
 * This is exported only क्रम रुको_on_page_locked/रुको_on_page_ग_लिखोback, etc.,
 * and should not be used directly.
 */
बाह्य व्योम रुको_on_page_bit(काष्ठा page *page, पूर्णांक bit_nr);
बाह्य पूर्णांक रुको_on_page_bit_समाप्तable(काष्ठा page *page, पूर्णांक bit_nr);

/* 
 * Wait क्रम a page to be unlocked.
 *
 * This must be called with the caller "holding" the page,
 * ie with increased "page->count" so that the page won't
 * go away during the रुको..
 */
अटल अंतरभूत व्योम रुको_on_page_locked(काष्ठा page *page)
अणु
	अगर (PageLocked(page))
		रुको_on_page_bit(compound_head(page), PG_locked);
पूर्ण

अटल अंतरभूत पूर्णांक रुको_on_page_locked_समाप्तable(काष्ठा page *page)
अणु
	अगर (!PageLocked(page))
		वापस 0;
	वापस रुको_on_page_bit_समाप्तable(compound_head(page), PG_locked);
पूर्ण

पूर्णांक put_and_रुको_on_page_locked(काष्ठा page *page, पूर्णांक state);
व्योम रुको_on_page_ग_लिखोback(काष्ठा page *page);
पूर्णांक रुको_on_page_ग_लिखोback_समाप्तable(काष्ठा page *page);
बाह्य व्योम end_page_ग_लिखोback(काष्ठा page *page);
व्योम रुको_क्रम_stable_page(काष्ठा page *page);

व्योम page_endio(काष्ठा page *page, bool is_ग_लिखो, पूर्णांक err);

/**
 * set_page_निजी_2 - Set PG_निजी_2 on a page and take a ref
 * @page: The page.
 *
 * Set the PG_निजी_2 flag on a page and take the reference needed क्रम the VM
 * to handle its lअगरeसमय correctly.  This sets the flag and takes the
 * reference unconditionally, so care must be taken not to set the flag again
 * अगर it's alपढ़ोy set.
 */
अटल अंतरभूत व्योम set_page_निजी_2(काष्ठा page *page)
अणु
	page = compound_head(page);
	get_page(page);
	SetPagePrivate2(page);
पूर्ण

व्योम end_page_निजी_2(काष्ठा page *page);
व्योम रुको_on_page_निजी_2(काष्ठा page *page);
पूर्णांक रुको_on_page_निजी_2_समाप्तable(काष्ठा page *page);

/*
 * Add an arbitrary रुकोer to a page's रुको queue
 */
बाह्य व्योम add_page_रुको_queue(काष्ठा page *page, रुको_queue_entry_t *रुकोer);

/*
 * Fault everything in given userspace address range in.
 */
अटल अंतरभूत पूर्णांक fault_in_pages_ग_लिखोable(अक्षर __user *uaddr, पूर्णांक size)
अणु
	अक्षर __user *end = uaddr + size - 1;

	अगर (unlikely(size == 0))
		वापस 0;

	अगर (unlikely(uaddr > end))
		वापस -EFAULT;
	/*
	 * Writing zeroes पूर्णांकo userspace here is OK, because we know that अगर
	 * the zero माला_लो there, we'll be overwriting it.
	 */
	करो अणु
		अगर (unlikely(__put_user(0, uaddr) != 0))
			वापस -EFAULT;
		uaddr += PAGE_SIZE;
	पूर्ण जबतक (uaddr <= end);

	/* Check whether the range spilled पूर्णांकo the next page. */
	अगर (((अचिन्हित दीर्घ)uaddr & PAGE_MASK) ==
			((अचिन्हित दीर्घ)end & PAGE_MASK))
		वापस __put_user(0, end);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक fault_in_pages_पढ़ोable(स्थिर अक्षर __user *uaddr, पूर्णांक size)
अणु
	अस्थिर अक्षर c;
	स्थिर अक्षर __user *end = uaddr + size - 1;

	अगर (unlikely(size == 0))
		वापस 0;

	अगर (unlikely(uaddr > end))
		वापस -EFAULT;

	करो अणु
		अगर (unlikely(__get_user(c, uaddr) != 0))
			वापस -EFAULT;
		uaddr += PAGE_SIZE;
	पूर्ण जबतक (uaddr <= end);

	/* Check whether the range spilled पूर्णांकo the next page. */
	अगर (((अचिन्हित दीर्घ)uaddr & PAGE_MASK) ==
			((अचिन्हित दीर्घ)end & PAGE_MASK)) अणु
		वापस __get_user(c, end);
	पूर्ण

	(व्योम)c;
	वापस 0;
पूर्ण

पूर्णांक add_to_page_cache_locked(काष्ठा page *page, काष्ठा address_space *mapping,
				pgoff_t index, gfp_t gfp_mask);
पूर्णांक add_to_page_cache_lru(काष्ठा page *page, काष्ठा address_space *mapping,
				pgoff_t index, gfp_t gfp_mask);
बाह्य व्योम delete_from_page_cache(काष्ठा page *page);
बाह्य व्योम __delete_from_page_cache(काष्ठा page *page, व्योम *shaकरोw);
व्योम replace_page_cache_page(काष्ठा page *old, काष्ठा page *new);
व्योम delete_from_page_cache_batch(काष्ठा address_space *mapping,
				  काष्ठा pagevec *pvec);
loff_t mapping_seek_hole_data(काष्ठा address_space *, loff_t start, loff_t end,
		पूर्णांक whence);

/*
 * Like add_to_page_cache_locked, but used to add newly allocated pages:
 * the page is new, so we can just run __SetPageLocked() against it.
 */
अटल अंतरभूत पूर्णांक add_to_page_cache(काष्ठा page *page,
		काष्ठा address_space *mapping, pgoff_t offset, gfp_t gfp_mask)
अणु
	पूर्णांक error;

	__SetPageLocked(page);
	error = add_to_page_cache_locked(page, mapping, offset, gfp_mask);
	अगर (unlikely(error))
		__ClearPageLocked(page);
	वापस error;
पूर्ण

/**
 * काष्ठा पढ़ोahead_control - Describes a पढ़ोahead request.
 *
 * A पढ़ोahead request is क्रम consecutive pages.  Fileप्रणालीs which
 * implement the ->पढ़ोahead method should call पढ़ोahead_page() or
 * पढ़ोahead_page_batch() in a loop and attempt to start I/O against
 * each page in the request.
 *
 * Most of the fields in this काष्ठा are निजी and should be accessed
 * by the functions below.
 *
 * @file: The file, used primarily by network fileप्रणालीs क्रम authentication.
 *	  May be शून्य अगर invoked पूर्णांकernally by the fileप्रणाली.
 * @mapping: Readahead this fileप्रणाली object.
 * @ra: File पढ़ोahead state.  May be शून्य.
 */
काष्ठा पढ़ोahead_control अणु
	काष्ठा file *file;
	काष्ठा address_space *mapping;
	काष्ठा file_ra_state *ra;
/* निजी: use the पढ़ोahead_* accessors instead */
	pgoff_t _index;
	अचिन्हित पूर्णांक _nr_pages;
	अचिन्हित पूर्णांक _batch_count;
पूर्ण;

#घोषणा DEFINE_READAHEAD(ractl, f, r, m, i)				\
	काष्ठा पढ़ोahead_control ractl = अणु				\
		.file = f,						\
		.mapping = m,						\
		.ra = r,						\
		._index = i,						\
	पूर्ण

#घोषणा VM_READAHEAD_PAGES	(SZ_128K / PAGE_SIZE)

व्योम page_cache_ra_unbounded(काष्ठा पढ़ोahead_control *,
		अचिन्हित दीर्घ nr_to_पढ़ो, अचिन्हित दीर्घ lookahead_count);
व्योम page_cache_sync_ra(काष्ठा पढ़ोahead_control *, अचिन्हित दीर्घ req_count);
व्योम page_cache_async_ra(काष्ठा पढ़ोahead_control *, काष्ठा page *,
		अचिन्हित दीर्घ req_count);
व्योम पढ़ोahead_expand(काष्ठा पढ़ोahead_control *ractl,
		      loff_t new_start, माप_प्रकार new_len);

/**
 * page_cache_sync_पढ़ोahead - generic file पढ़ोahead
 * @mapping: address_space which holds the pagecache and I/O vectors
 * @ra: file_ra_state which holds the पढ़ोahead state
 * @file: Used by the fileप्रणाली क्रम authentication.
 * @index: Index of first page to be पढ़ो.
 * @req_count: Total number of pages being पढ़ो by the caller.
 *
 * page_cache_sync_पढ़ोahead() should be called when a cache miss happened:
 * it will submit the पढ़ो.  The पढ़ोahead logic may decide to piggyback more
 * pages onto the पढ़ो request अगर access patterns suggest it will improve
 * perक्रमmance.
 */
अटल अंतरभूत
व्योम page_cache_sync_पढ़ोahead(काष्ठा address_space *mapping,
		काष्ठा file_ra_state *ra, काष्ठा file *file, pgoff_t index,
		अचिन्हित दीर्घ req_count)
अणु
	DEFINE_READAHEAD(ractl, file, ra, mapping, index);
	page_cache_sync_ra(&ractl, req_count);
पूर्ण

/**
 * page_cache_async_पढ़ोahead - file पढ़ोahead क्रम marked pages
 * @mapping: address_space which holds the pagecache and I/O vectors
 * @ra: file_ra_state which holds the पढ़ोahead state
 * @file: Used by the fileप्रणाली क्रम authentication.
 * @page: The page at @index which triggered the पढ़ोahead call.
 * @index: Index of first page to be पढ़ो.
 * @req_count: Total number of pages being पढ़ो by the caller.
 *
 * page_cache_async_पढ़ोahead() should be called when a page is used which
 * is marked as PageReadahead; this is a marker to suggest that the application
 * has used up enough of the पढ़ोahead winकरोw that we should start pulling in
 * more pages.
 */
अटल अंतरभूत
व्योम page_cache_async_पढ़ोahead(काष्ठा address_space *mapping,
		काष्ठा file_ra_state *ra, काष्ठा file *file,
		काष्ठा page *page, pgoff_t index, अचिन्हित दीर्घ req_count)
अणु
	DEFINE_READAHEAD(ractl, file, ra, mapping, index);
	page_cache_async_ra(&ractl, page, req_count);
पूर्ण

/**
 * पढ़ोahead_page - Get the next page to पढ़ो.
 * @rac: The current पढ़ोahead request.
 *
 * Context: The page is locked and has an elevated refcount.  The caller
 * should decreases the refcount once the page has been submitted क्रम I/O
 * and unlock the page once all I/O to that page has completed.
 * Return: A poपूर्णांकer to the next page, or %शून्य अगर we are करोne.
 */
अटल अंतरभूत काष्ठा page *पढ़ोahead_page(काष्ठा पढ़ोahead_control *rac)
अणु
	काष्ठा page *page;

	BUG_ON(rac->_batch_count > rac->_nr_pages);
	rac->_nr_pages -= rac->_batch_count;
	rac->_index += rac->_batch_count;

	अगर (!rac->_nr_pages) अणु
		rac->_batch_count = 0;
		वापस शून्य;
	पूर्ण

	page = xa_load(&rac->mapping->i_pages, rac->_index);
	VM_BUG_ON_PAGE(!PageLocked(page), page);
	rac->_batch_count = thp_nr_pages(page);

	वापस page;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __पढ़ोahead_batch(काष्ठा पढ़ोahead_control *rac,
		काष्ठा page **array, अचिन्हित पूर्णांक array_sz)
अणु
	अचिन्हित पूर्णांक i = 0;
	XA_STATE(xas, &rac->mapping->i_pages, 0);
	काष्ठा page *page;

	BUG_ON(rac->_batch_count > rac->_nr_pages);
	rac->_nr_pages -= rac->_batch_count;
	rac->_index += rac->_batch_count;
	rac->_batch_count = 0;

	xas_set(&xas, rac->_index);
	rcu_पढ़ो_lock();
	xas_क्रम_each(&xas, page, rac->_index + rac->_nr_pages - 1) अणु
		अगर (xas_retry(&xas, page))
			जारी;
		VM_BUG_ON_PAGE(!PageLocked(page), page);
		VM_BUG_ON_PAGE(PageTail(page), page);
		array[i++] = page;
		rac->_batch_count += thp_nr_pages(page);

		/*
		 * The page cache isn't using multi-index entries yet,
		 * so the xas cursor needs to be manually moved to the
		 * next index.  This can be हटाओd once the page cache
		 * is converted.
		 */
		अगर (PageHead(page))
			xas_set(&xas, rac->_index + rac->_batch_count);

		अगर (i == array_sz)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस i;
पूर्ण

/**
 * पढ़ोahead_page_batch - Get a batch of pages to पढ़ो.
 * @rac: The current पढ़ोahead request.
 * @array: An array of poपूर्णांकers to काष्ठा page.
 *
 * Context: The pages are locked and have an elevated refcount.  The caller
 * should decreases the refcount once the page has been submitted क्रम I/O
 * and unlock the page once all I/O to that page has completed.
 * Return: The number of pages placed in the array.  0 indicates the request
 * is complete.
 */
#घोषणा पढ़ोahead_page_batch(rac, array)				\
	__पढ़ोahead_batch(rac, array, ARRAY_SIZE(array))

/**
 * पढ़ोahead_pos - The byte offset पूर्णांकo the file of this पढ़ोahead request.
 * @rac: The पढ़ोahead request.
 */
अटल अंतरभूत loff_t पढ़ोahead_pos(काष्ठा पढ़ोahead_control *rac)
अणु
	वापस (loff_t)rac->_index * PAGE_SIZE;
पूर्ण

/**
 * पढ़ोahead_length - The number of bytes in this पढ़ोahead request.
 * @rac: The पढ़ोahead request.
 */
अटल अंतरभूत माप_प्रकार पढ़ोahead_length(काष्ठा पढ़ोahead_control *rac)
अणु
	वापस rac->_nr_pages * PAGE_SIZE;
पूर्ण

/**
 * पढ़ोahead_index - The index of the first page in this पढ़ोahead request.
 * @rac: The पढ़ोahead request.
 */
अटल अंतरभूत pgoff_t पढ़ोahead_index(काष्ठा पढ़ोahead_control *rac)
अणु
	वापस rac->_index;
पूर्ण

/**
 * पढ़ोahead_count - The number of pages in this पढ़ोahead request.
 * @rac: The पढ़ोahead request.
 */
अटल अंतरभूत अचिन्हित पूर्णांक पढ़ोahead_count(काष्ठा पढ़ोahead_control *rac)
अणु
	वापस rac->_nr_pages;
पूर्ण

/**
 * पढ़ोahead_batch_length - The number of bytes in the current batch.
 * @rac: The पढ़ोahead request.
 */
अटल अंतरभूत माप_प्रकार पढ़ोahead_batch_length(काष्ठा पढ़ोahead_control *rac)
अणु
	वापस rac->_batch_count * PAGE_SIZE;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ dir_pages(काष्ठा inode *inode)
अणु
	वापस (अचिन्हित दीर्घ)(inode->i_size + PAGE_SIZE - 1) >>
			       PAGE_SHIFT;
पूर्ण

/**
 * page_mkग_लिखो_check_truncate - check अगर page was truncated
 * @page: the page to check
 * @inode: the inode to check the page against
 *
 * Returns the number of bytes in the page up to खातापूर्ण,
 * or -EFAULT अगर the page was truncated.
 */
अटल अंतरभूत पूर्णांक page_mkग_लिखो_check_truncate(काष्ठा page *page,
					      काष्ठा inode *inode)
अणु
	loff_t size = i_size_पढ़ो(inode);
	pgoff_t index = size >> PAGE_SHIFT;
	पूर्णांक offset = offset_in_page(size);

	अगर (page->mapping != inode->i_mapping)
		वापस -EFAULT;

	/* page is wholly inside खातापूर्ण */
	अगर (page->index < index)
		वापस PAGE_SIZE;
	/* page is wholly past खातापूर्ण */
	अगर (page->index > index || !offset)
		वापस -EFAULT;
	/* page is partially inside खातापूर्ण */
	वापस offset;
पूर्ण

/**
 * i_blocks_per_page - How many blocks fit in this page.
 * @inode: The inode which contains the blocks.
 * @page: The page (head page अगर the page is a THP).
 *
 * If the block size is larger than the size of this page, वापस zero.
 *
 * Context: The caller should hold a refcount on the page to prevent it
 * from being split.
 * Return: The number of fileप्रणाली blocks covered by this page.
 */
अटल अंतरभूत
अचिन्हित पूर्णांक i_blocks_per_page(काष्ठा inode *inode, काष्ठा page *page)
अणु
	वापस thp_size(page) >> inode->i_blkbits;
पूर्ण
#पूर्ण_अगर /* _LINUX_PAGEMAP_H */
