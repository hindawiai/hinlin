<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* पूर्णांकernal.h: mm/ पूर्णांकernal definitions
 *
 * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#अगर_अघोषित __MM_INTERNAL_H
#घोषणा __MM_INTERNAL_H

#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/tracepoपूर्णांक-defs.h>

/*
 * The set of flags that only affect watermark checking and reclaim
 * behaviour. This is used by the MM to obey the caller स्थिरraपूर्णांकs
 * about IO, FS and watermark checking जबतक ignoring placement
 * hपूर्णांकs such as HIGHMEM usage.
 */
#घोषणा GFP_RECLAIM_MASK (__GFP_RECLAIM|__GFP_HIGH|__GFP_IO|__GFP_FS|\
			__GFP_NOWARN|__GFP_RETRY_MAYFAIL|__GFP_NOFAIL|\
			__GFP_NORETRY|__GFP_MEMALLOC|__GFP_NOMEMALLOC|\
			__GFP_ATOMIC)

/* The GFP flags allowed during early boot */
#घोषणा GFP_BOOT_MASK (__GFP_BITS_MASK & ~(__GFP_RECLAIM|__GFP_IO|__GFP_FS))

/* Control allocation cpuset and node placement स्थिरraपूर्णांकs */
#घोषणा GFP_CONSTRAINT_MASK (__GFP_HARDWALL|__GFP_THISNODE)

/* Do not use these with a slab allocator */
#घोषणा GFP_SLAB_BUG_MASK (__GFP_DMA32|__GFP_HIGHMEM|~__GFP_BITS_MASK)

व्योम page_ग_लिखोback_init(व्योम);

vm_fault_t करो_swap_page(काष्ठा vm_fault *vmf);

व्योम मुक्त_pgtables(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *start_vma,
		अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing);

अटल अंतरभूत bool can_madv_lru_vma(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस !(vma->vm_flags & (VM_LOCKED|VM_HUGETLB|VM_PFNMAP));
पूर्ण

व्योम unmap_page_range(काष्ठा mmu_gather *tlb,
			     काष्ठा vm_area_काष्ठा *vma,
			     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			     काष्ठा zap_details *details);

व्योम करो_page_cache_ra(काष्ठा पढ़ोahead_control *, अचिन्हित दीर्घ nr_to_पढ़ो,
		अचिन्हित दीर्घ lookahead_size);
व्योम क्रमce_page_cache_ra(काष्ठा पढ़ोahead_control *, अचिन्हित दीर्घ nr);
अटल अंतरभूत व्योम क्रमce_page_cache_पढ़ोahead(काष्ठा address_space *mapping,
		काष्ठा file *file, pgoff_t index, अचिन्हित दीर्घ nr_to_पढ़ो)
अणु
	DEFINE_READAHEAD(ractl, file, &file->f_ra, mapping, index);
	क्रमce_page_cache_ra(&ractl, nr_to_पढ़ो);
पूर्ण

अचिन्हित find_lock_entries(काष्ठा address_space *mapping, pgoff_t start,
		pgoff_t end, काष्ठा pagevec *pvec, pgoff_t *indices);

/**
 * page_evictable - test whether a page is evictable
 * @page: the page to test
 *
 * Test whether page is evictable--i.e., should be placed on active/inactive
 * lists vs unevictable list.
 *
 * Reasons page might not be evictable:
 * (1) page's mapping marked unevictable
 * (2) page is part of an mlocked VMA
 *
 */
अटल अंतरभूत bool page_evictable(काष्ठा page *page)
अणु
	bool ret;

	/* Prevent address_space of inode and swap cache from being मुक्तd */
	rcu_पढ़ो_lock();
	ret = !mapping_unevictable(page_mapping(page)) && !PageMlocked(page);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/*
 * Turn a non-refcounted page (->_refcount == 0) पूर्णांकo refcounted with
 * a count of one.
 */
अटल अंतरभूत व्योम set_page_refcounted(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(PageTail(page), page);
	VM_BUG_ON_PAGE(page_ref_count(page), page);
	set_page_count(page, 1);
पूर्ण

बाह्य अचिन्हित दीर्घ highest_memmap_pfn;

/*
 * Maximum number of reclaim retries without progress beक्रमe the OOM
 * समाप्तer is consider the only way क्रमward.
 */
#घोषणा MAX_RECLAIM_RETRIES 16

/*
 * in mm/vmscan.c:
 */
बाह्य पूर्णांक isolate_lru_page(काष्ठा page *page);
बाह्य व्योम putback_lru_page(काष्ठा page *page);

/*
 * in mm/rmap.c:
 */
बाह्य pmd_t *mm_find_pmd(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address);

/*
 * in mm/page_alloc.c
 */

/*
 * Structure क्रम holding the mostly immutable allocation parameters passed
 * between functions involved in allocations, including the alloc_pages*
 * family of functions.
 *
 * nodemask, migratetype and highest_zoneidx are initialized only once in
 * __alloc_pages() and then never change.
 *
 * zonelist, preferred_zone and highest_zoneidx are set first in
 * __alloc_pages() क्रम the fast path, and might be later changed
 * in __alloc_pages_slowpath(). All other functions pass the whole काष्ठाure
 * by a स्थिर poपूर्णांकer.
 */
काष्ठा alloc_context अणु
	काष्ठा zonelist *zonelist;
	nodemask_t *nodemask;
	काष्ठा zoneref *preferred_zoneref;
	पूर्णांक migratetype;

	/*
	 * highest_zoneidx represents highest usable zone index of
	 * the allocation request. Due to the nature of the zone,
	 * memory on lower zone than the highest_zoneidx will be
	 * रक्षित by lowmem_reserve[highest_zoneidx].
	 *
	 * highest_zoneidx is also used by reclaim/compaction to limit
	 * the target zone since higher zone than this index cannot be
	 * usable क्रम this allocation request.
	 */
	क्रमागत zone_type highest_zoneidx;
	bool spपढ़ो_dirty_pages;
पूर्ण;

/*
 * Locate the काष्ठा page क्रम both the matching buddy in our
 * pair (buddy1) and the combined O(n+1) page they क्रमm (page).
 *
 * 1) Any buddy B1 will have an order O twin B2 which satisfies
 * the following equation:
 *     B2 = B1 ^ (1 << O)
 * For example, अगर the starting buddy (buddy2) is #8 its order
 * 1 buddy is #10:
 *     B2 = 8 ^ (1 << 1) = 8 ^ 2 = 10
 *
 * 2) Any buddy B will have an order O+1 parent P which
 * satisfies the following equation:
 *     P = B & ~(1 << O)
 *
 * Assumption: *_mem_map is contiguous at least up to MAX_ORDER
 */
अटल अंतरभूत अचिन्हित दीर्घ
__find_buddy_pfn(अचिन्हित दीर्घ page_pfn, अचिन्हित पूर्णांक order)
अणु
	वापस page_pfn ^ (1 << order);
पूर्ण

बाह्य काष्ठा page *__pageblock_pfn_to_page(अचिन्हित दीर्घ start_pfn,
				अचिन्हित दीर्घ end_pfn, काष्ठा zone *zone);

अटल अंतरभूत काष्ठा page *pageblock_pfn_to_page(अचिन्हित दीर्घ start_pfn,
				अचिन्हित दीर्घ end_pfn, काष्ठा zone *zone)
अणु
	अगर (zone->contiguous)
		वापस pfn_to_page(start_pfn);

	वापस __pageblock_pfn_to_page(start_pfn, end_pfn, zone);
पूर्ण

बाह्य पूर्णांक __isolate_मुक्त_page(काष्ठा page *page, अचिन्हित पूर्णांक order);
बाह्य व्योम __putback_isolated_page(काष्ठा page *page, अचिन्हित पूर्णांक order,
				    पूर्णांक mt);
बाह्य व्योम memblock_मुक्त_pages(काष्ठा page *page, अचिन्हित दीर्घ pfn,
					अचिन्हित पूर्णांक order);
बाह्य व्योम __मुक्त_pages_core(काष्ठा page *page, अचिन्हित पूर्णांक order);
बाह्य व्योम prep_compound_page(काष्ठा page *page, अचिन्हित पूर्णांक order);
बाह्य व्योम post_alloc_hook(काष्ठा page *page, अचिन्हित पूर्णांक order,
					gfp_t gfp_flags);
बाह्य पूर्णांक user_min_मुक्त_kbytes;

बाह्य व्योम मुक्त_unref_page(काष्ठा page *page);
बाह्य व्योम मुक्त_unref_page_list(काष्ठा list_head *list);

बाह्य व्योम zone_pcp_update(काष्ठा zone *zone);
बाह्य व्योम zone_pcp_reset(काष्ठा zone *zone);
बाह्य व्योम zone_pcp_disable(काष्ठा zone *zone);
बाह्य व्योम zone_pcp_enable(काष्ठा zone *zone);

#अगर defined CONFIG_COMPACTION || defined CONFIG_CMA

/*
 * in mm/compaction.c
 */
/*
 * compact_control is used to track pages being migrated and the मुक्त pages
 * they are being migrated to during memory compaction. The मुक्त_pfn starts
 * at the end of a zone and migrate_pfn begins at the start. Movable pages
 * are moved to the end of a zone during a compaction run and the run
 * completes when मुक्त_pfn <= migrate_pfn
 */
काष्ठा compact_control अणु
	काष्ठा list_head मुक्तpages;	/* List of मुक्त pages to migrate to */
	काष्ठा list_head migratepages;	/* List of pages being migrated */
	अचिन्हित पूर्णांक nr_मुक्तpages;	/* Number of isolated मुक्त pages */
	अचिन्हित पूर्णांक nr_migratepages;	/* Number of pages to migrate */
	अचिन्हित दीर्घ मुक्त_pfn;		/* isolate_मुक्तpages search base */
	/*
	 * Acts as an in/out parameter to page isolation क्रम migration.
	 * isolate_migratepages uses it as a search base.
	 * isolate_migratepages_block will update the value to the next pfn
	 * after the last isolated one.
	 */
	अचिन्हित दीर्घ migrate_pfn;
	अचिन्हित दीर्घ fast_start_pfn;	/* a pfn to start linear scan from */
	काष्ठा zone *zone;
	अचिन्हित दीर्घ total_migrate_scanned;
	अचिन्हित दीर्घ total_मुक्त_scanned;
	अचिन्हित लघु fast_search_fail;/* failures to use मुक्त list searches */
	लघु search_order;		/* order to start a fast search at */
	स्थिर gfp_t gfp_mask;		/* gfp mask of a direct compactor */
	पूर्णांक order;			/* order a direct compactor needs */
	पूर्णांक migratetype;		/* migratetype of direct compactor */
	स्थिर अचिन्हित पूर्णांक alloc_flags;	/* alloc flags of a direct compactor */
	स्थिर पूर्णांक highest_zoneidx;	/* zone index of a direct compactor */
	क्रमागत migrate_mode mode;		/* Async or sync migration mode */
	bool ignore_skip_hपूर्णांक;		/* Scan blocks even अगर marked skip */
	bool no_set_skip_hपूर्णांक;		/* Don't mark blocks क्रम skipping */
	bool ignore_block_suitable;	/* Scan blocks considered unsuitable */
	bool direct_compaction;		/* False from kcompactd or /proc/... */
	bool proactive_compaction;	/* kcompactd proactive compaction */
	bool whole_zone;		/* Whole zone should/has been scanned */
	bool contended;			/* Signal lock or sched contention */
	bool rescan;			/* Rescanning the same pageblock */
	bool alloc_contig;		/* alloc_contig_range allocation */
पूर्ण;

/*
 * Used in direct compaction when a page should be taken from the मुक्तlists
 * immediately when one is created during the मुक्त path.
 */
काष्ठा capture_control अणु
	काष्ठा compact_control *cc;
	काष्ठा page *page;
पूर्ण;

अचिन्हित दीर्घ
isolate_मुक्तpages_range(काष्ठा compact_control *cc,
			अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn);
पूर्णांक
isolate_migratepages_range(काष्ठा compact_control *cc,
			   अचिन्हित दीर्घ low_pfn, अचिन्हित दीर्घ end_pfn);
पूर्णांक find_suitable_fallback(काष्ठा मुक्त_area *area, अचिन्हित पूर्णांक order,
			पूर्णांक migratetype, bool only_stealable, bool *can_steal);

#पूर्ण_अगर

/*
 * This function वापसs the order of a मुक्त page in the buddy प्रणाली. In
 * general, page_zone(page)->lock must be held by the caller to prevent the
 * page from being allocated in parallel and वापसing garbage as the order.
 * If a caller करोes not hold page_zone(page)->lock, it must guarantee that the
 * page cannot be allocated or merged in parallel. Alternatively, it must
 * handle invalid values gracefully, and use buddy_order_unsafe() below.
 */
अटल अंतरभूत अचिन्हित पूर्णांक buddy_order(काष्ठा page *page)
अणु
	/* PageBuddy() must be checked by the caller */
	वापस page_निजी(page);
पूर्ण

/*
 * Like buddy_order(), but क्रम callers who cannot afक्रमd to hold the zone lock.
 * PageBuddy() should be checked first by the caller to minimize race winकरोw,
 * and invalid values must be handled gracefully.
 *
 * READ_ONCE is used so that अगर the caller assigns the result पूर्णांकo a local
 * variable and e.g. tests it क्रम valid range beक्रमe using, the compiler cannot
 * decide to हटाओ the variable and अंतरभूत the page_निजी(page) multiple
 * बार, potentially observing dअगरferent values in the tests and the actual
 * use of the result.
 */
#घोषणा buddy_order_unsafe(page)	READ_ONCE(page_निजी(page))

/*
 * These three helpers classअगरies VMAs क्रम भव memory accounting.
 */

/*
 * Executable code area - executable, not writable, not stack
 */
अटल अंतरभूत bool is_exec_mapping(vm_flags_t flags)
अणु
	वापस (flags & (VM_EXEC | VM_WRITE | VM_STACK)) == VM_EXEC;
पूर्ण

/*
 * Stack area - स्वतःmatically grows in one direction
 *
 * VM_GROWSUP / VM_GROWSDOWN VMAs are always निजी anonymous:
 * करो_mmap() क्रमbids all other combinations.
 */
अटल अंतरभूत bool is_stack_mapping(vm_flags_t flags)
अणु
	वापस (flags & VM_STACK) == VM_STACK;
पूर्ण

/*
 * Data area - निजी, writable, not stack
 */
अटल अंतरभूत bool is_data_mapping(vm_flags_t flags)
अणु
	वापस (flags & (VM_WRITE | VM_SHARED | VM_STACK)) == VM_WRITE;
पूर्ण

/* mm/util.c */
व्योम __vma_link_list(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
		काष्ठा vm_area_काष्ठा *prev);
व्योम __vma_unlink_list(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma);

#अगर_घोषित CONFIG_MMU
बाह्य दीर्घ populate_vma_page_range(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक *nonblocking);
बाह्य व्योम munlock_vma_pages_range(काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
अटल अंतरभूत व्योम munlock_vma_pages_all(काष्ठा vm_area_काष्ठा *vma)
अणु
	munlock_vma_pages_range(vma, vma->vm_start, vma->vm_end);
पूर्ण

/*
 * must be called with vma's mmap_lock held क्रम पढ़ो or ग_लिखो, and page locked.
 */
बाह्य व्योम mlock_vma_page(काष्ठा page *page);
बाह्य अचिन्हित पूर्णांक munlock_vma_page(काष्ठा page *page);

/*
 * Clear the page's PageMlocked().  This can be useful in a situation where
 * we want to unconditionally हटाओ a page from the pagecache -- e.g.,
 * on truncation or मुक्तing.
 *
 * It is legal to call this function क्रम any page, mlocked or not.
 * If called क्रम a page that is still mapped by mlocked vmas, all we करो
 * is revert to lazy LRU behaviour -- semantics are not broken.
 */
बाह्य व्योम clear_page_mlock(काष्ठा page *page);

/*
 * mlock_migrate_page - called only from migrate_misplaced_transhuge_page()
 * (because that करोes not go through the full procedure of migration ptes):
 * to migrate the Mlocked page flag; update statistics.
 */
अटल अंतरभूत व्योम mlock_migrate_page(काष्ठा page *newpage, काष्ठा page *page)
अणु
	अगर (TestClearPageMlocked(page)) अणु
		पूर्णांक nr_pages = thp_nr_pages(page);

		/* Holding pmd lock, no change in irq context: __mod is safe */
		__mod_zone_page_state(page_zone(page), NR_MLOCK, -nr_pages);
		SetPageMlocked(newpage);
		__mod_zone_page_state(page_zone(newpage), NR_MLOCK, nr_pages);
	पूर्ण
पूर्ण

बाह्य pmd_t maybe_pmd_mkग_लिखो(pmd_t pmd, काष्ठा vm_area_काष्ठा *vma);

/*
 * At what user भव address is page expected in vma?
 * Returns -EFAULT अगर all of the page is outside the range of vma.
 * If page is a compound head, the entire compound page is considered.
 */
अटल अंतरभूत अचिन्हित दीर्घ
vma_address(काष्ठा page *page, काष्ठा vm_area_काष्ठा *vma)
अणु
	pgoff_t pgoff;
	अचिन्हित दीर्घ address;

	VM_BUG_ON_PAGE(PageKsm(page), page);	/* KSM page->index unusable */
	pgoff = page_to_pgoff(page);
	अगर (pgoff >= vma->vm_pgoff) अणु
		address = vma->vm_start +
			((pgoff - vma->vm_pgoff) << PAGE_SHIFT);
		/* Check क्रम address beyond vma (or wrapped through 0?) */
		अगर (address < vma->vm_start || address >= vma->vm_end)
			address = -EFAULT;
	पूर्ण अन्यथा अगर (PageHead(page) &&
		   pgoff + compound_nr(page) - 1 >= vma->vm_pgoff) अणु
		/* Test above aव्योमs possibility of wrap to 0 on 32-bit */
		address = vma->vm_start;
	पूर्ण अन्यथा अणु
		address = -EFAULT;
	पूर्ण
	वापस address;
पूर्ण

/*
 * Then at what user भव address will none of the page be found in vma?
 * Assumes that vma_address() alपढ़ोy वापसed a good starting address.
 * If page is a compound head, the entire compound page is considered.
 */
अटल अंतरभूत अचिन्हित दीर्घ
vma_address_end(काष्ठा page *page, काष्ठा vm_area_काष्ठा *vma)
अणु
	pgoff_t pgoff;
	अचिन्हित दीर्घ address;

	VM_BUG_ON_PAGE(PageKsm(page), page);	/* KSM page->index unusable */
	pgoff = page_to_pgoff(page) + compound_nr(page);
	address = vma->vm_start + ((pgoff - vma->vm_pgoff) << PAGE_SHIFT);
	/* Check क्रम address beyond vma (or wrapped through 0?) */
	अगर (address < vma->vm_start || address > vma->vm_end)
		address = vma->vm_end;
	वापस address;
पूर्ण

अटल अंतरभूत काष्ठा file *maybe_unlock_mmap_क्रम_io(काष्ठा vm_fault *vmf,
						    काष्ठा file *fpin)
अणु
	पूर्णांक flags = vmf->flags;

	अगर (fpin)
		वापस fpin;

	/*
	 * FAULT_FLAG_RETRY_NOWAIT means we करोn't want to रुको on page locks or
	 * anything, so we only pin the file and drop the mmap_lock अगर only
	 * FAULT_FLAG_ALLOW_RETRY is set, जबतक this is the first attempt.
	 */
	अगर (fault_flag_allow_retry_first(flags) &&
	    !(flags & FAULT_FLAG_RETRY_NOWAIT)) अणु
		fpin = get_file(vmf->vma->vm_file);
		mmap_पढ़ो_unlock(vmf->vma->vm_mm);
	पूर्ण
	वापस fpin;
पूर्ण

#अन्यथा /* !CONFIG_MMU */
अटल अंतरभूत व्योम clear_page_mlock(काष्ठा page *page) अणु पूर्ण
अटल अंतरभूत व्योम mlock_vma_page(काष्ठा page *page) अणु पूर्ण
अटल अंतरभूत व्योम mlock_migrate_page(काष्ठा page *new, काष्ठा page *old) अणु पूर्ण
अटल अंतरभूत व्योम vunmap_range_noflush(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
पूर्ण
#पूर्ण_अगर /* !CONFIG_MMU */

/*
 * Return the mem_map entry representing the 'offset' subpage within
 * the maximally aligned gigantic page 'base'.  Handle any discontiguity
 * in the mem_map at MAX_ORDER_NR_PAGES boundaries.
 */
अटल अंतरभूत काष्ठा page *mem_map_offset(काष्ठा page *base, पूर्णांक offset)
अणु
	अगर (unlikely(offset >= MAX_ORDER_NR_PAGES))
		वापस nth_page(base, offset);
	वापस base + offset;
पूर्ण

/*
 * Iterator over all subpages within the maximally aligned gigantic
 * page 'base'.  Handle any discontiguity in the mem_map.
 */
अटल अंतरभूत काष्ठा page *mem_map_next(काष्ठा page *iter,
						काष्ठा page *base, पूर्णांक offset)
अणु
	अगर (unlikely((offset & (MAX_ORDER_NR_PAGES - 1)) == 0)) अणु
		अचिन्हित दीर्घ pfn = page_to_pfn(base) + offset;
		अगर (!pfn_valid(pfn))
			वापस शून्य;
		वापस pfn_to_page(pfn);
	पूर्ण
	वापस iter + 1;
पूर्ण

/* Memory initialisation debug and verअगरication */
क्रमागत mminit_level अणु
	MMINIT_WARNING,
	MMINIT_VERIFY,
	MMINIT_TRACE
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_MEMORY_INIT

बाह्य पूर्णांक mminit_loglevel;

#घोषणा mminit_dprपूर्णांकk(level, prefix, fmt, arg...) \
करो अणु \
	अगर (level < mminit_loglevel) अणु \
		अगर (level <= MMINIT_WARNING) \
			pr_warn("mminit::" prefix " " fmt, ##arg);	\
		अन्यथा \
			prपूर्णांकk(KERN_DEBUG "mminit::" prefix " " fmt, ##arg); \
	पूर्ण \
पूर्ण जबतक (0)

बाह्य व्योम mminit_verअगरy_pageflags_layout(व्योम);
बाह्य व्योम mminit_verअगरy_zonelist(व्योम);
#अन्यथा

अटल अंतरभूत व्योम mminit_dprपूर्णांकk(क्रमागत mminit_level level,
				स्थिर अक्षर *prefix, स्थिर अक्षर *fmt, ...)
अणु
पूर्ण

अटल अंतरभूत व्योम mminit_verअगरy_pageflags_layout(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम mminit_verअगरy_zonelist(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_MEMORY_INIT */

/* mminit_validate_memmodel_limits is independent of CONFIG_DEBUG_MEMORY_INIT */
#अगर defined(CONFIG_SPARSEMEM)
बाह्य व्योम mminit_validate_memmodel_limits(अचिन्हित दीर्घ *start_pfn,
				अचिन्हित दीर्घ *end_pfn);
#अन्यथा
अटल अंतरभूत व्योम mminit_validate_memmodel_limits(अचिन्हित दीर्घ *start_pfn,
				अचिन्हित दीर्घ *end_pfn)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SPARSEMEM */

#घोषणा NODE_RECLAIM_NOSCAN	-2
#घोषणा NODE_RECLAIM_FULL	-1
#घोषणा NODE_RECLAIM_SOME	0
#घोषणा NODE_RECLAIM_SUCCESS	1

#अगर_घोषित CONFIG_NUMA
बाह्य पूर्णांक node_reclaim(काष्ठा pglist_data *, gfp_t, अचिन्हित पूर्णांक);
#अन्यथा
अटल अंतरभूत पूर्णांक node_reclaim(काष्ठा pglist_data *pgdat, gfp_t mask,
				अचिन्हित पूर्णांक order)
अणु
	वापस NODE_RECLAIM_NOSCAN;
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक hwpoison_filter(काष्ठा page *p);

बाह्य u32 hwpoison_filter_dev_major;
बाह्य u32 hwpoison_filter_dev_minor;
बाह्य u64 hwpoison_filter_flags_mask;
बाह्य u64 hwpoison_filter_flags_value;
बाह्य u64 hwpoison_filter_memcg;
बाह्य u32 hwpoison_filter_enable;

बाह्य अचिन्हित दीर्घ  __must_check vm_mmap_pgoff(काष्ठा file *, अचिन्हित दीर्घ,
        अचिन्हित दीर्घ, अचिन्हित दीर्घ,
        अचिन्हित दीर्घ, अचिन्हित दीर्घ);

बाह्य व्योम set_pageblock_order(व्योम);
अचिन्हित पूर्णांक reclaim_clean_pages_from_list(काष्ठा zone *zone,
					    काष्ठा list_head *page_list);
/* The ALLOC_WMARK bits are used as an index to zone->watermark */
#घोषणा ALLOC_WMARK_MIN		WMARK_MIN
#घोषणा ALLOC_WMARK_LOW		WMARK_LOW
#घोषणा ALLOC_WMARK_HIGH	WMARK_HIGH
#घोषणा ALLOC_NO_WATERMARKS	0x04 /* करोn't check watermarks at all */

/* Mask to get the watermark bits */
#घोषणा ALLOC_WMARK_MASK	(ALLOC_NO_WATERMARKS-1)

/*
 * Only MMU archs have async oom victim reclaim - aka oom_reaper so we
 * cannot assume a reduced access to memory reserves is sufficient क्रम
 * !MMU
 */
#अगर_घोषित CONFIG_MMU
#घोषणा ALLOC_OOM		0x08
#अन्यथा
#घोषणा ALLOC_OOM		ALLOC_NO_WATERMARKS
#पूर्ण_अगर

#घोषणा ALLOC_HARDER		 0x10 /* try to alloc harder */
#घोषणा ALLOC_HIGH		 0x20 /* __GFP_HIGH set */
#घोषणा ALLOC_CPUSET		 0x40 /* check क्रम correct cpuset */
#घोषणा ALLOC_CMA		 0x80 /* allow allocations from CMA areas */
#अगर_घोषित CONFIG_ZONE_DMA32
#घोषणा ALLOC_NOFRAGMENT	0x100 /* aव्योम mixing pageblock types */
#अन्यथा
#घोषणा ALLOC_NOFRAGMENT	  0x0
#पूर्ण_अगर
#घोषणा ALLOC_KSWAPD		0x800 /* allow waking of kswapd, __GFP_KSWAPD_RECLAIM set */

क्रमागत ttu_flags;
काष्ठा tlbflush_unmap_batch;


/*
 * only क्रम MM पूर्णांकernal work items which करो not depend on
 * any allocations or locks which might depend on allocations
 */
बाह्य काष्ठा workqueue_काष्ठा *mm_percpu_wq;

#अगर_घोषित CONFIG_ARCH_WANT_BATCHED_UNMAP_TLB_FLUSH
व्योम try_to_unmap_flush(व्योम);
व्योम try_to_unmap_flush_dirty(व्योम);
व्योम flush_tlb_batched_pending(काष्ठा mm_काष्ठा *mm);
#अन्यथा
अटल अंतरभूत व्योम try_to_unmap_flush(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम try_to_unmap_flush_dirty(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम flush_tlb_batched_pending(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_WANT_BATCHED_UNMAP_TLB_FLUSH */

बाह्य स्थिर काष्ठा trace_prपूर्णांक_flags pageflag_names[];
बाह्य स्थिर काष्ठा trace_prपूर्णांक_flags vmaflag_names[];
बाह्य स्थिर काष्ठा trace_prपूर्णांक_flags gfpflag_names[];

अटल अंतरभूत bool is_migrate_highatomic(क्रमागत migratetype migratetype)
अणु
	वापस migratetype == MIGRATE_HIGHATOMIC;
पूर्ण

अटल अंतरभूत bool is_migrate_highatomic_page(काष्ठा page *page)
अणु
	वापस get_pageblock_migratetype(page) == MIGRATE_HIGHATOMIC;
पूर्ण

व्योम setup_zone_pageset(काष्ठा zone *zone);

काष्ठा migration_target_control अणु
	पूर्णांक nid;		/* preferred node id */
	nodemask_t *nmask;
	gfp_t gfp_mask;
पूर्ण;

/*
 * mm/vदो_स्मृति.c
 */
#अगर_घोषित CONFIG_MMU
पूर्णांक vmap_pages_range_noflush(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
                pgprot_t prot, काष्ठा page **pages, अचिन्हित पूर्णांक page_shअगरt);
#अन्यथा
अटल अंतरभूत
पूर्णांक vmap_pages_range_noflush(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
                pgprot_t prot, काष्ठा page **pages, अचिन्हित पूर्णांक page_shअगरt)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

व्योम vunmap_range_noflush(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

#पूर्ण_अगर	/* __MM_INTERNAL_H */
