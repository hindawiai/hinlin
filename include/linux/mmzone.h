<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MMZONE_H
#घोषणा _LINUX_MMZONE_H

#अगर_अघोषित __ASSEMBLY__
#अगर_अघोषित __GENERATING_BOUNDS_H

#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/bitops.h>
#समावेश <linux/cache.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/numa.h>
#समावेश <linux/init.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/pageblock-flags.h>
#समावेश <linux/page-flags-layout.h>
#समावेश <linux/atomic.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/page-flags.h>
#समावेश <यंत्र/page.h>

/* Free memory management - zoned buddy allocator.  */
#अगर_अघोषित CONFIG_FORCE_MAX_ZONEORDER
#घोषणा MAX_ORDER 11
#अन्यथा
#घोषणा MAX_ORDER CONFIG_FORCE_MAX_ZONEORDER
#पूर्ण_अगर
#घोषणा MAX_ORDER_NR_PAGES (1 << (MAX_ORDER - 1))

/*
 * PAGE_ALLOC_COSTLY_ORDER is the order at which allocations are deemed
 * costly to service.  That is between allocation orders which should
 * coalesce naturally under reasonable reclaim pressure and those which
 * will not.
 */
#घोषणा PAGE_ALLOC_COSTLY_ORDER 3

क्रमागत migratetype अणु
	MIGRATE_UNMOVABLE,
	MIGRATE_MOVABLE,
	MIGRATE_RECLAIMABLE,
	MIGRATE_PCPTYPES,	/* the number of types on the pcp lists */
	MIGRATE_HIGHATOMIC = MIGRATE_PCPTYPES,
#अगर_घोषित CONFIG_CMA
	/*
	 * MIGRATE_CMA migration type is deचिन्हित to mimic the way
	 * ZONE_MOVABLE works.  Only movable pages can be allocated
	 * from MIGRATE_CMA pageblocks and page allocator never
	 * implicitly change migration type of MIGRATE_CMA pageblock.
	 *
	 * The way to use it is to change migratetype of a range of
	 * pageblocks to MIGRATE_CMA which can be करोne by
	 * __मुक्त_pageblock_cma() function.  What is important though
	 * is that a range of pageblocks must be aligned to
	 * MAX_ORDER_NR_PAGES should biggest page be bigger than
	 * a single pageblock.
	 */
	MIGRATE_CMA,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEMORY_ISOLATION
	MIGRATE_ISOLATE,	/* can't allocate from here */
#पूर्ण_अगर
	MIGRATE_TYPES
पूर्ण;

/* In mm/page_alloc.c; keep in sync also with show_migration_types() there */
बाह्य स्थिर अक्षर * स्थिर migratetype_names[MIGRATE_TYPES];

#अगर_घोषित CONFIG_CMA
#  define is_migrate_cma(migratetype) unlikely((migratetype) == MIGRATE_CMA)
#  define is_migrate_cma_page(_page) (get_pageblock_migratetype(_page) == MIGRATE_CMA)
#अन्यथा
#  define is_migrate_cma(migratetype) false
#  define is_migrate_cma_page(_page) false
#पूर्ण_अगर

अटल अंतरभूत bool is_migrate_movable(पूर्णांक mt)
अणु
	वापस is_migrate_cma(mt) || mt == MIGRATE_MOVABLE;
पूर्ण

#घोषणा क्रम_each_migratetype_order(order, type) \
	क्रम (order = 0; order < MAX_ORDER; order++) \
		क्रम (type = 0; type < MIGRATE_TYPES; type++)

बाह्य पूर्णांक page_group_by_mobility_disabled;

#घोषणा MIGRATETYPE_MASK ((1UL << PB_migratetype_bits) - 1)

#घोषणा get_pageblock_migratetype(page)					\
	get_pfnblock_flags_mask(page, page_to_pfn(page), MIGRATETYPE_MASK)

काष्ठा मुक्त_area अणु
	काष्ठा list_head	मुक्त_list[MIGRATE_TYPES];
	अचिन्हित दीर्घ		nr_मुक्त;
पूर्ण;

अटल अंतरभूत काष्ठा page *get_page_from_मुक्त_area(काष्ठा मुक्त_area *area,
					    पूर्णांक migratetype)
अणु
	वापस list_first_entry_or_null(&area->मुक्त_list[migratetype],
					काष्ठा page, lru);
पूर्ण

अटल अंतरभूत bool मुक्त_area_empty(काष्ठा मुक्त_area *area, पूर्णांक migratetype)
अणु
	वापस list_empty(&area->मुक्त_list[migratetype]);
पूर्ण

काष्ठा pglist_data;

/*
 * Add a wild amount of padding here to ensure datas fall पूर्णांकo separate
 * cachelines.  There are very few zone काष्ठाures in the machine, so space
 * consumption is not a concern here.
 */
#अगर defined(CONFIG_SMP)
काष्ठा zone_padding अणु
	अक्षर x[0];
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;
#घोषणा ZONE_PADDING(name)	काष्ठा zone_padding name;
#अन्यथा
#घोषणा ZONE_PADDING(name)
#पूर्ण_अगर

#अगर_घोषित CONFIG_NUMA
क्रमागत numa_stat_item अणु
	NUMA_HIT,		/* allocated in पूर्णांकended node */
	NUMA_MISS,		/* allocated in non पूर्णांकended node */
	NUMA_FOREIGN,		/* was पूर्णांकended here, hit अन्यथाwhere */
	NUMA_INTERLEAVE_HIT,	/* पूर्णांकerleaver preferred this zone */
	NUMA_LOCAL,		/* allocation from local node */
	NUMA_OTHER,		/* allocation from other node */
	NR_VM_NUMA_STAT_ITEMS
पूर्ण;
#अन्यथा
#घोषणा NR_VM_NUMA_STAT_ITEMS 0
#पूर्ण_अगर

क्रमागत zone_stat_item अणु
	/* First 128 byte cacheline (assuming 64 bit words) */
	NR_FREE_PAGES,
	NR_ZONE_LRU_BASE, /* Used only क्रम compaction and reclaim retry */
	NR_ZONE_INACTIVE_ANON = NR_ZONE_LRU_BASE,
	NR_ZONE_ACTIVE_ANON,
	NR_ZONE_INACTIVE_खाता,
	NR_ZONE_ACTIVE_खाता,
	NR_ZONE_UNEVICTABLE,
	NR_ZONE_WRITE_PENDING,	/* Count of dirty, ग_लिखोback and unstable pages */
	NR_MLOCK,		/* mlock()ed pages found and moved off LRU */
	/* Second 128 byte cacheline */
	NR_BOUNCE,
#अगर IS_ENABLED(CONFIG_ZSMALLOC)
	NR_ZSPAGES,		/* allocated in zsदो_स्मृति */
#पूर्ण_अगर
	NR_FREE_CMA_PAGES,
	NR_VM_ZONE_STAT_ITEMS पूर्ण;

क्रमागत node_stat_item अणु
	NR_LRU_BASE,
	NR_INACTIVE_ANON = NR_LRU_BASE, /* must match order of LRU_[IN]ACTIVE */
	NR_ACTIVE_ANON,		/*  "     "     "   "       "         */
	NR_INACTIVE_खाता,	/*  "     "     "   "       "         */
	NR_ACTIVE_खाता,		/*  "     "     "   "       "         */
	NR_UNEVICTABLE,		/*  "     "     "   "       "         */
	NR_SLAB_RECLAIMABLE_B,
	NR_SLAB_UNRECLAIMABLE_B,
	NR_ISOLATED_ANON,	/* Temporary isolated pages from anon lru */
	NR_ISOLATED_खाता,	/* Temporary isolated pages from file lru */
	WORKINGSET_NODES,
	WORKINGSET_REFAULT_BASE,
	WORKINGSET_REFAULT_ANON = WORKINGSET_REFAULT_BASE,
	WORKINGSET_REFAULT_खाता,
	WORKINGSET_ACTIVATE_BASE,
	WORKINGSET_ACTIVATE_ANON = WORKINGSET_ACTIVATE_BASE,
	WORKINGSET_ACTIVATE_खाता,
	WORKINGSET_RESTORE_BASE,
	WORKINGSET_RESTORE_ANON = WORKINGSET_RESTORE_BASE,
	WORKINGSET_RESTORE_खाता,
	WORKINGSET_NODERECLAIM,
	NR_ANON_MAPPED,	/* Mapped anonymous pages */
	NR_खाता_MAPPED,	/* pagecache pages mapped पूर्णांकo pagetables.
			   only modअगरied from process context */
	NR_खाता_PAGES,
	NR_खाता_सूचीTY,
	NR_WRITEBACK,
	NR_WRITEBACK_TEMP,	/* Writeback using temporary buffers */
	NR_SHMEM,		/* shmem pages (included पंचांगpfs/GEM pages) */
	NR_SHMEM_THPS,
	NR_SHMEM_PMDMAPPED,
	NR_खाता_THPS,
	NR_खाता_PMDMAPPED,
	NR_ANON_THPS,
	NR_VMSCAN_WRITE,
	NR_VMSCAN_IMMEDIATE,	/* Prioritise क्रम reclaim when ग_लिखोback ends */
	NR_सूचीTIED,		/* page dirtyings since bootup */
	NR_WRITTEN,		/* page writings since bootup */
	NR_KERNEL_MISC_RECLAIMABLE,	/* reclaimable non-slab kernel pages */
	NR_FOLL_PIN_ACQUIRED,	/* via: pin_user_page(), gup flag: FOLL_PIN */
	NR_FOLL_PIN_RELEASED,	/* pages वापसed via unpin_user_page() */
	NR_KERNEL_STACK_KB,	/* measured in KiB */
#अगर IS_ENABLED(CONFIG_SHADOW_CALL_STACK)
	NR_KERNEL_SCS_KB,	/* measured in KiB */
#पूर्ण_अगर
	NR_PAGETABLE,		/* used क्रम pagetables */
#अगर_घोषित CONFIG_SWAP
	NR_SWAPCACHE,
#पूर्ण_अगर
	NR_VM_NODE_STAT_ITEMS
पूर्ण;

/*
 * Returns true अगर the item should be prपूर्णांकed in THPs (/proc/vmstat
 * currently prपूर्णांकs number of anon, file and shmem THPs. But the item
 * is अक्षरged in pages).
 */
अटल __always_अंतरभूत bool vmstat_item_prपूर्णांक_in_thp(क्रमागत node_stat_item item)
अणु
	अगर (!IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE))
		वापस false;

	वापस item == NR_ANON_THPS ||
	       item == NR_खाता_THPS ||
	       item == NR_SHMEM_THPS ||
	       item == NR_SHMEM_PMDMAPPED ||
	       item == NR_खाता_PMDMAPPED;
पूर्ण

/*
 * Returns true अगर the value is measured in bytes (most vmstat values are
 * measured in pages). This defines the API part, the पूर्णांकernal representation
 * might be dअगरferent.
 */
अटल __always_अंतरभूत bool vmstat_item_in_bytes(पूर्णांक idx)
अणु
	/*
	 * Global and per-node slab counters track slab pages.
	 * It's expected that changes are multiples of PAGE_SIZE.
	 * Internally values are stored in pages.
	 *
	 * Per-memcg and per-lruvec counters track memory, consumed
	 * by inभागidual slab objects. These counters are actually
	 * byte-precise.
	 */
	वापस (idx == NR_SLAB_RECLAIMABLE_B ||
		idx == NR_SLAB_UNRECLAIMABLE_B);
पूर्ण

/*
 * We करो arithmetic on the LRU lists in various places in the code,
 * so it is important to keep the active lists LRU_ACTIVE higher in
 * the array than the corresponding inactive lists, and to keep
 * the *_खाता lists LRU_खाता higher than the corresponding _ANON lists.
 *
 * This has to be kept in sync with the statistics in zone_stat_item
 * above and the descriptions in vmstat_text in mm/vmstat.c
 */
#घोषणा LRU_BASE 0
#घोषणा LRU_ACTIVE 1
#घोषणा LRU_खाता 2

क्रमागत lru_list अणु
	LRU_INACTIVE_ANON = LRU_BASE,
	LRU_ACTIVE_ANON = LRU_BASE + LRU_ACTIVE,
	LRU_INACTIVE_खाता = LRU_BASE + LRU_खाता,
	LRU_ACTIVE_खाता = LRU_BASE + LRU_खाता + LRU_ACTIVE,
	LRU_UNEVICTABLE,
	NR_LRU_LISTS
पूर्ण;

#घोषणा क्रम_each_lru(lru) क्रम (lru = 0; lru < NR_LRU_LISTS; lru++)

#घोषणा क्रम_each_evictable_lru(lru) क्रम (lru = 0; lru <= LRU_ACTIVE_खाता; lru++)

अटल अंतरभूत bool is_file_lru(क्रमागत lru_list lru)
अणु
	वापस (lru == LRU_INACTIVE_खाता || lru == LRU_ACTIVE_खाता);
पूर्ण

अटल अंतरभूत bool is_active_lru(क्रमागत lru_list lru)
अणु
	वापस (lru == LRU_ACTIVE_ANON || lru == LRU_ACTIVE_खाता);
पूर्ण

#घोषणा ANON_AND_खाता 2

क्रमागत lruvec_flags अणु
	LRUVEC_CONGESTED,		/* lruvec has many dirty pages
					 * backed by a congested BDI
					 */
पूर्ण;

काष्ठा lruvec अणु
	काष्ठा list_head		lists[NR_LRU_LISTS];
	/* per lruvec lru_lock क्रम memcg */
	spinlock_t			lru_lock;
	/*
	 * These track the cost of reclaiming one LRU - file or anon -
	 * over the other. As the observed cost of reclaiming one LRU
	 * increases, the reclaim scan balance tips toward the other.
	 */
	अचिन्हित दीर्घ			anon_cost;
	अचिन्हित दीर्घ			file_cost;
	/* Non-resident age, driven by LRU movement */
	atomic_दीर्घ_t			nonresident_age;
	/* Refaults at the समय of last reclaim cycle */
	अचिन्हित दीर्घ			refaults[ANON_AND_खाता];
	/* Various lruvec state flags (क्रमागत lruvec_flags) */
	अचिन्हित दीर्घ			flags;
#अगर_घोषित CONFIG_MEMCG
	काष्ठा pglist_data *pgdat;
#पूर्ण_अगर
पूर्ण;

/* Isolate unmapped pages */
#घोषणा ISOLATE_UNMAPPED	((__क्रमce isolate_mode_t)0x2)
/* Isolate क्रम asynchronous migration */
#घोषणा ISOLATE_ASYNC_MIGRATE	((__क्रमce isolate_mode_t)0x4)
/* Isolate unevictable pages */
#घोषणा ISOLATE_UNEVICTABLE	((__क्रमce isolate_mode_t)0x8)

/* LRU Isolation modes. */
प्रकार अचिन्हित __bitwise isolate_mode_t;

क्रमागत zone_watermarks अणु
	WMARK_MIN,
	WMARK_LOW,
	WMARK_HIGH,
	NR_WMARK
पूर्ण;

#घोषणा min_wmark_pages(z) (z->_watermark[WMARK_MIN] + z->watermark_boost)
#घोषणा low_wmark_pages(z) (z->_watermark[WMARK_LOW] + z->watermark_boost)
#घोषणा high_wmark_pages(z) (z->_watermark[WMARK_HIGH] + z->watermark_boost)
#घोषणा wmark_pages(z, i) (z->_watermark[i] + z->watermark_boost)

काष्ठा per_cpu_pages अणु
	पूर्णांक count;		/* number of pages in the list */
	पूर्णांक high;		/* high watermark, emptying needed */
	पूर्णांक batch;		/* chunk size क्रम buddy add/हटाओ */

	/* Lists of pages, one per migrate type stored on the pcp-lists */
	काष्ठा list_head lists[MIGRATE_PCPTYPES];
पूर्ण;

काष्ठा per_cpu_pageset अणु
	काष्ठा per_cpu_pages pcp;
#अगर_घोषित CONFIG_NUMA
	s8 expire;
	u16 vm_numa_stat_dअगरf[NR_VM_NUMA_STAT_ITEMS];
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
	s8 stat_threshold;
	s8 vm_stat_dअगरf[NR_VM_ZONE_STAT_ITEMS];
#पूर्ण_अगर
पूर्ण;

काष्ठा per_cpu_nodestat अणु
	s8 stat_threshold;
	s8 vm_node_stat_dअगरf[NR_VM_NODE_STAT_ITEMS];
पूर्ण;

#पूर्ण_अगर /* !__GENERATING_BOUNDS.H */

क्रमागत zone_type अणु
	/*
	 * ZONE_DMA and ZONE_DMA32 are used when there are peripherals not able
	 * to DMA to all of the addressable memory (ZONE_NORMAL).
	 * On architectures where this area covers the whole 32 bit address
	 * space ZONE_DMA32 is used. ZONE_DMA is left क्रम the ones with smaller
	 * DMA addressing स्थिरraपूर्णांकs. This distinction is important as a 32bit
	 * DMA mask is assumed when ZONE_DMA32 is defined. Some 64-bit
	 * platक्रमms may need both zones as they support peripherals with
	 * dअगरferent DMA addressing limitations.
	 */
#अगर_घोषित CONFIG_ZONE_DMA
	ZONE_DMA,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ZONE_DMA32
	ZONE_DMA32,
#पूर्ण_अगर
	/*
	 * Normal addressable memory is in ZONE_NORMAL. DMA operations can be
	 * perक्रमmed on pages in ZONE_NORMAL अगर the DMA devices support
	 * transfers to all addressable memory.
	 */
	ZONE_NORMAL,
#अगर_घोषित CONFIG_HIGHMEM
	/*
	 * A memory area that is only addressable by the kernel through
	 * mapping portions पूर्णांकo its own address space. This is क्रम example
	 * used by i386 to allow the kernel to address the memory beyond
	 * 900MB. The kernel will set up special mappings (page
	 * table entries on i386) क्रम each page that the kernel needs to
	 * access.
	 */
	ZONE_HIGHMEM,
#पूर्ण_अगर
	/*
	 * ZONE_MOVABLE is similar to ZONE_NORMAL, except that it contains
	 * movable pages with few exceptional हालs described below. Main use
	 * हालs क्रम ZONE_MOVABLE are to make memory offlining/unplug more
	 * likely to succeed, and to locally limit unmovable allocations - e.g.,
	 * to increase the number of THP/huge pages. Notable special हालs are:
	 *
	 * 1. Pinned pages: (दीर्घ-term) pinning of movable pages might
	 *    essentially turn such pages unmovable. Thereक्रमe, we करो not allow
	 *    pinning दीर्घ-term pages in ZONE_MOVABLE. When pages are pinned and
	 *    faulted, they come from the right zone right away. However, it is
	 *    still possible that address space alपढ़ोy has pages in
	 *    ZONE_MOVABLE at the समय when pages are pinned (i.e. user has
	 *    touches that memory beक्रमe pinning). In such हाल we migrate them
	 *    to a dअगरferent zone. When migration fails - pinning fails.
	 * 2. memblock allocations: kernelcore/movablecore setups might create
	 *    situations where ZONE_MOVABLE contains unmovable allocations
	 *    after boot. Memory offlining and allocations fail early.
	 * 3. Memory holes: kernelcore/movablecore setups might create very rare
	 *    situations where ZONE_MOVABLE contains memory holes after boot,
	 *    क्रम example, अगर we have sections that are only partially
	 *    populated. Memory offlining and allocations fail early.
	 * 4. PG_hwpoison pages: जबतक poisoned pages can be skipped during
	 *    memory offlining, such pages cannot be allocated.
	 * 5. Unmovable PG_offline pages: in paraभवized environments,
	 *    hotplugged memory blocks might only partially be managed by the
	 *    buddy (e.g., via XEN-balloon, Hyper-V balloon, virtio-mem). The
	 *    parts not manged by the buddy are unmovable PG_offline pages. In
	 *    some हालs (virtio-mem), such pages can be skipped during
	 *    memory offlining, however, cannot be moved/allocated. These
	 *    techniques might use alloc_contig_range() to hide previously
	 *    exposed pages from the buddy again (e.g., to implement some sort
	 *    of memory unplug in virtio-mem).
	 * 6. ZERO_PAGE(0), kernelcore/movablecore setups might create
	 *    situations where ZERO_PAGE(0) which is allocated dअगरferently
	 *    on dअगरferent platक्रमms may end up in a movable zone. ZERO_PAGE(0)
	 *    cannot be migrated.
	 * 7. Memory-hotplug: when using memmap_on_memory and onlining the
	 *    memory to the MOVABLE zone, the vmemmap pages are also placed in
	 *    such zone. Such pages cannot be really moved around as they are
	 *    self-stored in the range, but they are treated as movable when
	 *    the range they describe is about to be offlined.
	 *
	 * In general, no unmovable allocations that degrade memory offlining
	 * should end up in ZONE_MOVABLE. Allocators (like alloc_contig_range())
	 * have to expect that migrating pages in ZONE_MOVABLE can fail (even
	 * अगर has_unmovable_pages() states that there are no unmovable pages,
	 * there can be false negatives).
	 */
	ZONE_MOVABLE,
#अगर_घोषित CONFIG_ZONE_DEVICE
	ZONE_DEVICE,
#पूर्ण_अगर
	__MAX_NR_ZONES

पूर्ण;

#अगर_अघोषित __GENERATING_BOUNDS_H

#घोषणा ASYNC_AND_SYNC 2

काष्ठा zone अणु
	/* Read-mostly fields */

	/* zone watermarks, access with *_wmark_pages(zone) macros */
	अचिन्हित दीर्घ _watermark[NR_WMARK];
	अचिन्हित दीर्घ watermark_boost;

	अचिन्हित दीर्घ nr_reserved_highatomic;

	/*
	 * We करोn't know if the memory that we're going to allocate will be
	 * मुक्तable or/and it will be released eventually, so to aव्योम totally
	 * wasting several GB of ram we must reserve some of the lower zone
	 * memory (otherwise we risk to run OOM on the lower zones despite
	 * there being tons of मुक्तable ram on the higher zones).  This array is
	 * recalculated at runसमय अगर the sysctl_lowmem_reserve_ratio sysctl
	 * changes.
	 */
	दीर्घ lowmem_reserve[MAX_NR_ZONES];

#अगर_घोषित CONFIG_NUMA
	पूर्णांक node;
#पूर्ण_अगर
	काष्ठा pglist_data	*zone_pgdat;
	काष्ठा per_cpu_pageset __percpu *pageset;
	/*
	 * the high and batch values are copied to inभागidual pagesets क्रम
	 * faster access
	 */
	पूर्णांक pageset_high;
	पूर्णांक pageset_batch;

#अगर_अघोषित CONFIG_SPARSEMEM
	/*
	 * Flags क्रम a pageblock_nr_pages block. See pageblock-flags.h.
	 * In SPARSEMEM, this map is stored in काष्ठा mem_section
	 */
	अचिन्हित दीर्घ		*pageblock_flags;
#पूर्ण_अगर /* CONFIG_SPARSEMEM */

	/* zone_start_pfn == zone_start_paddr >> PAGE_SHIFT */
	अचिन्हित दीर्घ		zone_start_pfn;

	/*
	 * spanned_pages is the total pages spanned by the zone, including
	 * holes, which is calculated as:
	 * 	spanned_pages = zone_end_pfn - zone_start_pfn;
	 *
	 * present_pages is physical pages existing within the zone, which
	 * is calculated as:
	 *	present_pages = spanned_pages - असलent_pages(pages in holes);
	 *
	 * managed_pages is present pages managed by the buddy प्रणाली, which
	 * is calculated as (reserved_pages includes pages allocated by the
	 * booपंचांगem allocator):
	 *	managed_pages = present_pages - reserved_pages;
	 *
	 * cma pages is present pages that are asचिन्हित क्रम CMA use
	 * (MIGRATE_CMA).
	 *
	 * So present_pages may be used by memory hotplug or memory घातer
	 * management logic to figure out unmanaged pages by checking
	 * (present_pages - managed_pages). And managed_pages should be used
	 * by page allocator and vm scanner to calculate all kinds of watermarks
	 * and thresholds.
	 *
	 * Locking rules:
	 *
	 * zone_start_pfn and spanned_pages are रक्षित by span_seqlock.
	 * It is a seqlock because it has to be पढ़ो outside of zone->lock,
	 * and it is करोne in the मुख्य allocator path.  But, it is written
	 * quite infrequently.
	 *
	 * The span_seq lock is declared aदीर्घ with zone->lock because it is
	 * frequently पढ़ो in proximity to zone->lock.  It's good to
	 * give them a chance of being in the same cacheline.
	 *
	 * Write access to present_pages at runसमय should be रक्षित by
	 * mem_hotplug_begin/end(). Any पढ़ोer who can't tolerant drअगरt of
	 * present_pages should get_online_mems() to get a stable value.
	 */
	atomic_दीर्घ_t		managed_pages;
	अचिन्हित दीर्घ		spanned_pages;
	अचिन्हित दीर्घ		present_pages;
#अगर_घोषित CONFIG_CMA
	अचिन्हित दीर्घ		cma_pages;
#पूर्ण_अगर

	स्थिर अक्षर		*name;

#अगर_घोषित CONFIG_MEMORY_ISOLATION
	/*
	 * Number of isolated pageblock. It is used to solve incorrect
	 * मुक्तpage counting problem due to racy retrieving migratetype
	 * of pageblock. Protected by zone->lock.
	 */
	अचिन्हित दीर्घ		nr_isolate_pageblock;
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
	/* see spanned/present_pages क्रम more description */
	seqlock_t		span_seqlock;
#पूर्ण_अगर

	पूर्णांक initialized;

	/* Write-पूर्णांकensive fields used from the page allocator */
	ZONE_PADDING(_pad1_)

	/* मुक्त areas of dअगरferent sizes */
	काष्ठा मुक्त_area	मुक्त_area[MAX_ORDER];

	/* zone flags, see below */
	अचिन्हित दीर्घ		flags;

	/* Primarily protects मुक्त_area */
	spinlock_t		lock;

	/* Write-पूर्णांकensive fields used by compaction and vmstats. */
	ZONE_PADDING(_pad2_)

	/*
	 * When मुक्त pages are below this poपूर्णांक, additional steps are taken
	 * when पढ़ोing the number of मुक्त pages to aव्योम per-cpu counter
	 * drअगरt allowing watermarks to be breached
	 */
	अचिन्हित दीर्घ percpu_drअगरt_mark;

#अगर defined CONFIG_COMPACTION || defined CONFIG_CMA
	/* pfn where compaction मुक्त scanner should start */
	अचिन्हित दीर्घ		compact_cached_मुक्त_pfn;
	/* pfn where compaction migration scanner should start */
	अचिन्हित दीर्घ		compact_cached_migrate_pfn[ASYNC_AND_SYNC];
	अचिन्हित दीर्घ		compact_init_migrate_pfn;
	अचिन्हित दीर्घ		compact_init_मुक्त_pfn;
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPACTION
	/*
	 * On compaction failure, 1<<compact_defer_shअगरt compactions
	 * are skipped beक्रमe trying again. The number attempted since
	 * last failure is tracked with compact_considered.
	 * compact_order_failed is the minimum compaction failed order.
	 */
	अचिन्हित पूर्णांक		compact_considered;
	अचिन्हित पूर्णांक		compact_defer_shअगरt;
	पूर्णांक			compact_order_failed;
#पूर्ण_अगर

#अगर defined CONFIG_COMPACTION || defined CONFIG_CMA
	/* Set to true when the PG_migrate_skip bits should be cleared */
	bool			compact_blockskip_flush;
#पूर्ण_अगर

	bool			contiguous;

	ZONE_PADDING(_pad3_)
	/* Zone statistics */
	atomic_दीर्घ_t		vm_stat[NR_VM_ZONE_STAT_ITEMS];
	atomic_दीर्घ_t		vm_numa_stat[NR_VM_NUMA_STAT_ITEMS];
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

क्रमागत pgdat_flags अणु
	PGDAT_सूचीTY,			/* reclaim scanning has recently found
					 * many dirty file pages at the tail
					 * of the LRU.
					 */
	PGDAT_WRITEBACK,		/* reclaim scanning has recently found
					 * many pages under ग_लिखोback
					 */
	PGDAT_RECLAIM_LOCKED,		/* prevents concurrent reclaim */
पूर्ण;

क्रमागत zone_flags अणु
	ZONE_BOOSTED_WATERMARK,		/* zone recently boosted watermarks.
					 * Cleared when kswapd is woken.
					 */
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ zone_managed_pages(काष्ठा zone *zone)
अणु
	वापस (अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&zone->managed_pages);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ zone_cma_pages(काष्ठा zone *zone)
अणु
#अगर_घोषित CONFIG_CMA
	वापस zone->cma_pages;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ zone_end_pfn(स्थिर काष्ठा zone *zone)
अणु
	वापस zone->zone_start_pfn + zone->spanned_pages;
पूर्ण

अटल अंतरभूत bool zone_spans_pfn(स्थिर काष्ठा zone *zone, अचिन्हित दीर्घ pfn)
अणु
	वापस zone->zone_start_pfn <= pfn && pfn < zone_end_pfn(zone);
पूर्ण

अटल अंतरभूत bool zone_is_initialized(काष्ठा zone *zone)
अणु
	वापस zone->initialized;
पूर्ण

अटल अंतरभूत bool zone_is_empty(काष्ठा zone *zone)
अणु
	वापस zone->spanned_pages == 0;
पूर्ण

/*
 * Return true अगर [start_pfn, start_pfn + nr_pages) range has a non-empty
 * पूर्णांकersection with the given zone
 */
अटल अंतरभूत bool zone_पूर्णांकersects(काष्ठा zone *zone,
		अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ nr_pages)
अणु
	अगर (zone_is_empty(zone))
		वापस false;
	अगर (start_pfn >= zone_end_pfn(zone) ||
	    start_pfn + nr_pages <= zone->zone_start_pfn)
		वापस false;

	वापस true;
पूर्ण

/*
 * The "priority" of VM scanning is how much of the queues we will scan in one
 * go. A value of 12 क्रम DEF_PRIORITY implies that we will scan 1/4096th of the
 * queues ("queue_length >> 12") during an aging round.
 */
#घोषणा DEF_PRIORITY 12

/* Maximum number of zones on a zonelist */
#घोषणा MAX_ZONES_PER_ZONELIST (MAX_NUMNODES * MAX_NR_ZONES)

क्रमागत अणु
	ZONELIST_FALLBACK,	/* zonelist with fallback */
#अगर_घोषित CONFIG_NUMA
	/*
	 * The NUMA zonelists are द्विगुनd because we need zonelists that
	 * restrict the allocations to a single node क्रम __GFP_THISNODE.
	 */
	ZONELIST_NOFALLBACK,	/* zonelist without fallback (__GFP_THISNODE) */
#पूर्ण_अगर
	MAX_ZONELISTS
पूर्ण;

/*
 * This काष्ठा contains inक्रमmation about a zone in a zonelist. It is stored
 * here to aव्योम dereferences पूर्णांकo large काष्ठाures and lookups of tables
 */
काष्ठा zoneref अणु
	काष्ठा zone *zone;	/* Poपूर्णांकer to actual zone */
	पूर्णांक zone_idx;		/* zone_idx(zoneref->zone) */
पूर्ण;

/*
 * One allocation request operates on a zonelist. A zonelist
 * is a list of zones, the first one is the 'goal' of the
 * allocation, the other zones are fallback zones, in decreasing
 * priority.
 *
 * To speed the पढ़ोing of the zonelist, the zonerefs contain the zone index
 * of the entry being पढ़ो. Helper functions to access inक्रमmation given
 * a काष्ठा zoneref are
 *
 * zonelist_zone()	- Return the काष्ठा zone * क्रम an entry in _zonerefs
 * zonelist_zone_idx()	- Return the index of the zone क्रम an entry
 * zonelist_node_idx()	- Return the index of the node क्रम an entry
 */
काष्ठा zonelist अणु
	काष्ठा zoneref _zonerefs[MAX_ZONES_PER_ZONELIST + 1];
पूर्ण;

#अगर_अघोषित CONFIG_DISCONTIGMEM
/* The array of काष्ठा pages - क्रम discontigmem use pgdat->lmem_map */
बाह्य काष्ठा page *mem_map;
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
काष्ठा deferred_split अणु
	spinlock_t split_queue_lock;
	काष्ठा list_head split_queue;
	अचिन्हित दीर्घ split_queue_len;
पूर्ण;
#पूर्ण_अगर

/*
 * On NUMA machines, each NUMA node would have a pg_data_t to describe
 * it's memory layout. On UMA machines there is a single pglist_data which
 * describes the whole memory.
 *
 * Memory statistics and page replacement data काष्ठाures are मुख्यtained on a
 * per-zone basis.
 */
प्रकार काष्ठा pglist_data अणु
	/*
	 * node_zones contains just the zones क्रम THIS node. Not all of the
	 * zones may be populated, but it is the full list. It is referenced by
	 * this node's node_zonelists as well as other node's node_zonelists.
	 */
	काष्ठा zone node_zones[MAX_NR_ZONES];

	/*
	 * node_zonelists contains references to all zones in all nodes.
	 * Generally the first zones will be references to this node's
	 * node_zones.
	 */
	काष्ठा zonelist node_zonelists[MAX_ZONELISTS];

	पूर्णांक nr_zones; /* number of populated zones in this node */
#अगर_घोषित CONFIG_FLAT_NODE_MEM_MAP	/* means !SPARSEMEM */
	काष्ठा page *node_mem_map;
#अगर_घोषित CONFIG_PAGE_EXTENSION
	काष्ठा page_ext *node_page_ext;
#पूर्ण_अगर
#पूर्ण_अगर
#अगर defined(CONFIG_MEMORY_HOTPLUG) || defined(CONFIG_DEFERRED_STRUCT_PAGE_INIT)
	/*
	 * Must be held any समय you expect node_start_pfn,
	 * node_present_pages, node_spanned_pages or nr_zones to stay स्थिरant.
	 * Also synchronizes pgdat->first_deferred_pfn during deferred page
	 * init.
	 *
	 * pgdat_resize_lock() and pgdat_resize_unlock() are provided to
	 * manipulate node_size_lock without checking क्रम CONFIG_MEMORY_HOTPLUG
	 * or CONFIG_DEFERRED_STRUCT_PAGE_INIT.
	 *
	 * Nests above zone->lock and zone->span_seqlock
	 */
	spinlock_t node_size_lock;
#पूर्ण_अगर
	अचिन्हित दीर्घ node_start_pfn;
	अचिन्हित दीर्घ node_present_pages; /* total number of physical pages */
	अचिन्हित दीर्घ node_spanned_pages; /* total size of physical page
					     range, including holes */
	पूर्णांक node_id;
	रुको_queue_head_t kswapd_रुको;
	रुको_queue_head_t pfmeदो_स्मृति_रुको;
	काष्ठा task_काष्ठा *kswapd;	/* Protected by
					   mem_hotplug_begin/end() */
	पूर्णांक kswapd_order;
	क्रमागत zone_type kswapd_highest_zoneidx;

	पूर्णांक kswapd_failures;		/* Number of 'reclaimed == 0' runs */

#अगर_घोषित CONFIG_COMPACTION
	पूर्णांक kcompactd_max_order;
	क्रमागत zone_type kcompactd_highest_zoneidx;
	रुको_queue_head_t kcompactd_रुको;
	काष्ठा task_काष्ठा *kcompactd;
#पूर्ण_अगर
	/*
	 * This is a per-node reserve of pages that are not available
	 * to userspace allocations.
	 */
	अचिन्हित दीर्घ		totalreserve_pages;

#अगर_घोषित CONFIG_NUMA
	/*
	 * node reclaim becomes active अगर more unmapped pages exist.
	 */
	अचिन्हित दीर्घ		min_unmapped_pages;
	अचिन्हित दीर्घ		min_slab_pages;
#पूर्ण_अगर /* CONFIG_NUMA */

	/* Write-पूर्णांकensive fields used by page reclaim */
	ZONE_PADDING(_pad1_)

#अगर_घोषित CONFIG_DEFERRED_STRUCT_PAGE_INIT
	/*
	 * If memory initialisation on large machines is deferred then this
	 * is the first PFN that needs to be initialised.
	 */
	अचिन्हित दीर्घ first_deferred_pfn;
#पूर्ण_अगर /* CONFIG_DEFERRED_STRUCT_PAGE_INIT */

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	काष्ठा deferred_split deferred_split_queue;
#पूर्ण_अगर

	/* Fields commonly accessed by the page reclaim scanner */

	/*
	 * NOTE: THIS IS UNUSED IF MEMCG IS ENABLED.
	 *
	 * Use mem_cgroup_lruvec() to look up lruvecs.
	 */
	काष्ठा lruvec		__lruvec;

	अचिन्हित दीर्घ		flags;

	ZONE_PADDING(_pad2_)

	/* Per-node vmstats */
	काष्ठा per_cpu_nodestat __percpu *per_cpu_nodestats;
	atomic_दीर्घ_t		vm_stat[NR_VM_NODE_STAT_ITEMS];
पूर्ण pg_data_t;

#घोषणा node_present_pages(nid)	(NODE_DATA(nid)->node_present_pages)
#घोषणा node_spanned_pages(nid)	(NODE_DATA(nid)->node_spanned_pages)
#अगर_घोषित CONFIG_FLAT_NODE_MEM_MAP
#घोषणा pgdat_page_nr(pgdat, pagenr)	((pgdat)->node_mem_map + (pagenr))
#अन्यथा
#घोषणा pgdat_page_nr(pgdat, pagenr)	pfn_to_page((pgdat)->node_start_pfn + (pagenr))
#पूर्ण_अगर
#घोषणा nid_page_nr(nid, pagenr) 	pgdat_page_nr(NODE_DATA(nid),(pagenr))

#घोषणा node_start_pfn(nid)	(NODE_DATA(nid)->node_start_pfn)
#घोषणा node_end_pfn(nid) pgdat_end_pfn(NODE_DATA(nid))

अटल अंतरभूत अचिन्हित दीर्घ pgdat_end_pfn(pg_data_t *pgdat)
अणु
	वापस pgdat->node_start_pfn + pgdat->node_spanned_pages;
पूर्ण

अटल अंतरभूत bool pgdat_is_empty(pg_data_t *pgdat)
अणु
	वापस !pgdat->node_start_pfn && !pgdat->node_spanned_pages;
पूर्ण

#समावेश <linux/memory_hotplug.h>

व्योम build_all_zonelists(pg_data_t *pgdat);
व्योम wakeup_kswapd(काष्ठा zone *zone, gfp_t gfp_mask, पूर्णांक order,
		   क्रमागत zone_type highest_zoneidx);
bool __zone_watermark_ok(काष्ठा zone *z, अचिन्हित पूर्णांक order, अचिन्हित दीर्घ mark,
			 पूर्णांक highest_zoneidx, अचिन्हित पूर्णांक alloc_flags,
			 दीर्घ मुक्त_pages);
bool zone_watermark_ok(काष्ठा zone *z, अचिन्हित पूर्णांक order,
		अचिन्हित दीर्घ mark, पूर्णांक highest_zoneidx,
		अचिन्हित पूर्णांक alloc_flags);
bool zone_watermark_ok_safe(काष्ठा zone *z, अचिन्हित पूर्णांक order,
		अचिन्हित दीर्घ mark, पूर्णांक highest_zoneidx);
/*
 * Memory initialization context, use to dअगरferentiate memory added by
 * the platक्रमm अटलally or via memory hotplug पूर्णांकerface.
 */
क्रमागत meminit_context अणु
	MEMINIT_EARLY,
	MEMINIT_HOTPLUG,
पूर्ण;

बाह्य व्योम init_currently_empty_zone(काष्ठा zone *zone, अचिन्हित दीर्घ start_pfn,
				     अचिन्हित दीर्घ size);

बाह्य व्योम lruvec_init(काष्ठा lruvec *lruvec);

अटल अंतरभूत काष्ठा pglist_data *lruvec_pgdat(काष्ठा lruvec *lruvec)
अणु
#अगर_घोषित CONFIG_MEMCG
	वापस lruvec->pgdat;
#अन्यथा
	वापस container_of(lruvec, काष्ठा pglist_data, __lruvec);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_HAVE_MEMORYLESS_NODES
पूर्णांक local_memory_node(पूर्णांक node_id);
#अन्यथा
अटल अंतरभूत पूर्णांक local_memory_node(पूर्णांक node_id) अणु वापस node_id; पूर्ण;
#पूर्ण_अगर

/*
 * zone_idx() वापसs 0 क्रम the ZONE_DMA zone, 1 क्रम the ZONE_NORMAL zone, etc.
 */
#घोषणा zone_idx(zone)		((zone) - (zone)->zone_pgdat->node_zones)

#अगर_घोषित CONFIG_ZONE_DEVICE
अटल अंतरभूत bool zone_is_zone_device(काष्ठा zone *zone)
अणु
	वापस zone_idx(zone) == ZONE_DEVICE;
पूर्ण
#अन्यथा
अटल अंतरभूत bool zone_is_zone_device(काष्ठा zone *zone)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/*
 * Returns true अगर a zone has pages managed by the buddy allocator.
 * All the reclaim decisions have to use this function rather than
 * populated_zone(). If the whole zone is reserved then we can easily
 * end up with populated_zone() && !managed_zone().
 */
अटल अंतरभूत bool managed_zone(काष्ठा zone *zone)
अणु
	वापस zone_managed_pages(zone);
पूर्ण

/* Returns true अगर a zone has memory */
अटल अंतरभूत bool populated_zone(काष्ठा zone *zone)
अणु
	वापस zone->present_pages;
पूर्ण

#अगर_घोषित CONFIG_NUMA
अटल अंतरभूत पूर्णांक zone_to_nid(काष्ठा zone *zone)
अणु
	वापस zone->node;
पूर्ण

अटल अंतरभूत व्योम zone_set_nid(काष्ठा zone *zone, पूर्णांक nid)
अणु
	zone->node = nid;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक zone_to_nid(काष्ठा zone *zone)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम zone_set_nid(काष्ठा zone *zone, पूर्णांक nid) अणुपूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक movable_zone;

#अगर_घोषित CONFIG_HIGHMEM
अटल अंतरभूत पूर्णांक zone_movable_is_highmem(व्योम)
अणु
#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
	वापस movable_zone == ZONE_HIGHMEM;
#अन्यथा
	वापस (ZONE_MOVABLE - 1) == ZONE_HIGHMEM;
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक is_highmem_idx(क्रमागत zone_type idx)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	वापस (idx == ZONE_HIGHMEM ||
		(idx == ZONE_MOVABLE && zone_movable_is_highmem()));
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/**
 * is_highmem - helper function to quickly check अगर a काष्ठा zone is a
 *              highmem zone or not.  This is an attempt to keep references
 *              to ZONE_अणुDMA/NORMAL/HIGHMEM/etcपूर्ण in general code to a minimum.
 * @zone: poपूर्णांकer to काष्ठा zone variable
 * Return: 1 क्रम a highmem zone, 0 otherwise
 */
अटल अंतरभूत पूर्णांक is_highmem(काष्ठा zone *zone)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	वापस is_highmem_idx(zone_idx(zone));
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/* These two functions are used to setup the per zone pages min values */
काष्ठा ctl_table;

पूर्णांक min_मुक्त_kbytes_sysctl_handler(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *,
		loff_t *);
पूर्णांक watermark_scale_factor_sysctl_handler(काष्ठा ctl_table *, पूर्णांक, व्योम *,
		माप_प्रकार *, loff_t *);
बाह्य पूर्णांक sysctl_lowmem_reserve_ratio[MAX_NR_ZONES];
पूर्णांक lowmem_reserve_ratio_sysctl_handler(काष्ठा ctl_table *, पूर्णांक, व्योम *,
		माप_प्रकार *, loff_t *);
पूर्णांक percpu_pagelist_fraction_sysctl_handler(काष्ठा ctl_table *, पूर्णांक,
		व्योम *, माप_प्रकार *, loff_t *);
पूर्णांक sysctl_min_unmapped_ratio_sysctl_handler(काष्ठा ctl_table *, पूर्णांक,
		व्योम *, माप_प्रकार *, loff_t *);
पूर्णांक sysctl_min_slab_ratio_sysctl_handler(काष्ठा ctl_table *, पूर्णांक,
		व्योम *, माप_प्रकार *, loff_t *);
पूर्णांक numa_zonelist_order_handler(काष्ठा ctl_table *, पूर्णांक,
		व्योम *, माप_प्रकार *, loff_t *);
बाह्य पूर्णांक percpu_pagelist_fraction;
बाह्य अक्षर numa_zonelist_order[];
#घोषणा NUMA_ZONELIST_ORDER_LEN	16

#अगर_अघोषित CONFIG_NEED_MULTIPLE_NODES

बाह्य काष्ठा pglist_data contig_page_data;
#घोषणा NODE_DATA(nid)		(&contig_page_data)
#घोषणा NODE_MEM_MAP(nid)	mem_map

#अन्यथा /* CONFIG_NEED_MULTIPLE_NODES */

#समावेश <यंत्र/mmzone.h>

#पूर्ण_अगर /* !CONFIG_NEED_MULTIPLE_NODES */

बाह्य काष्ठा pglist_data *first_online_pgdat(व्योम);
बाह्य काष्ठा pglist_data *next_online_pgdat(काष्ठा pglist_data *pgdat);
बाह्य काष्ठा zone *next_zone(काष्ठा zone *zone);

/**
 * क्रम_each_online_pgdat - helper macro to iterate over all online nodes
 * @pgdat: poपूर्णांकer to a pg_data_t variable
 */
#घोषणा क्रम_each_online_pgdat(pgdat)			\
	क्रम (pgdat = first_online_pgdat();		\
	     pgdat;					\
	     pgdat = next_online_pgdat(pgdat))
/**
 * क्रम_each_zone - helper macro to iterate over all memory zones
 * @zone: poपूर्णांकer to काष्ठा zone variable
 *
 * The user only needs to declare the zone variable, क्रम_each_zone
 * fills it in.
 */
#घोषणा क्रम_each_zone(zone)			        \
	क्रम (zone = (first_online_pgdat())->node_zones; \
	     zone;					\
	     zone = next_zone(zone))

#घोषणा क्रम_each_populated_zone(zone)		        \
	क्रम (zone = (first_online_pgdat())->node_zones; \
	     zone;					\
	     zone = next_zone(zone))			\
		अगर (!populated_zone(zone))		\
			; /* करो nothing */		\
		अन्यथा

अटल अंतरभूत काष्ठा zone *zonelist_zone(काष्ठा zoneref *zoneref)
अणु
	वापस zoneref->zone;
पूर्ण

अटल अंतरभूत पूर्णांक zonelist_zone_idx(काष्ठा zoneref *zoneref)
अणु
	वापस zoneref->zone_idx;
पूर्ण

अटल अंतरभूत पूर्णांक zonelist_node_idx(काष्ठा zoneref *zoneref)
अणु
	वापस zone_to_nid(zoneref->zone);
पूर्ण

काष्ठा zoneref *__next_zones_zonelist(काष्ठा zoneref *z,
					क्रमागत zone_type highest_zoneidx,
					nodemask_t *nodes);

/**
 * next_zones_zonelist - Returns the next zone at or below highest_zoneidx within the allowed nodemask using a cursor within a zonelist as a starting poपूर्णांक
 * @z: The cursor used as a starting poपूर्णांक क्रम the search
 * @highest_zoneidx: The zone index of the highest zone to वापस
 * @nodes: An optional nodemask to filter the zonelist with
 *
 * This function वापसs the next zone at or below a given zone index that is
 * within the allowed nodemask using a cursor as the starting poपूर्णांक क्रम the
 * search. The zoneref वापसed is a cursor that represents the current zone
 * being examined. It should be advanced by one beक्रमe calling
 * next_zones_zonelist again.
 *
 * Return: the next zone at or below highest_zoneidx within the allowed
 * nodemask using a cursor within a zonelist as a starting poपूर्णांक
 */
अटल __always_अंतरभूत काष्ठा zoneref *next_zones_zonelist(काष्ठा zoneref *z,
					क्रमागत zone_type highest_zoneidx,
					nodemask_t *nodes)
अणु
	अगर (likely(!nodes && zonelist_zone_idx(z) <= highest_zoneidx))
		वापस z;
	वापस __next_zones_zonelist(z, highest_zoneidx, nodes);
पूर्ण

/**
 * first_zones_zonelist - Returns the first zone at or below highest_zoneidx within the allowed nodemask in a zonelist
 * @zonelist: The zonelist to search क्रम a suitable zone
 * @highest_zoneidx: The zone index of the highest zone to वापस
 * @nodes: An optional nodemask to filter the zonelist with
 *
 * This function वापसs the first zone at or below a given zone index that is
 * within the allowed nodemask. The zoneref वापसed is a cursor that can be
 * used to iterate the zonelist with next_zones_zonelist by advancing it by
 * one beक्रमe calling.
 *
 * When no eligible zone is found, zoneref->zone is शून्य (zoneref itself is
 * never शून्य). This may happen either genuinely, or due to concurrent nodemask
 * update due to cpuset modअगरication.
 *
 * Return: Zoneref poपूर्णांकer क्रम the first suitable zone found
 */
अटल अंतरभूत काष्ठा zoneref *first_zones_zonelist(काष्ठा zonelist *zonelist,
					क्रमागत zone_type highest_zoneidx,
					nodemask_t *nodes)
अणु
	वापस next_zones_zonelist(zonelist->_zonerefs,
							highest_zoneidx, nodes);
पूर्ण

/**
 * क्रम_each_zone_zonelist_nodemask - helper macro to iterate over valid zones in a zonelist at or below a given zone index and within a nodemask
 * @zone: The current zone in the iterator
 * @z: The current poपूर्णांकer within zonelist->_zonerefs being iterated
 * @zlist: The zonelist being iterated
 * @highidx: The zone index of the highest zone to वापस
 * @nodemask: Nodemask allowed by the allocator
 *
 * This iterator iterates though all zones at or below a given zone index and
 * within a given nodemask
 */
#घोषणा क्रम_each_zone_zonelist_nodemask(zone, z, zlist, highidx, nodemask) \
	क्रम (z = first_zones_zonelist(zlist, highidx, nodemask), zone = zonelist_zone(z);	\
		zone;							\
		z = next_zones_zonelist(++z, highidx, nodemask),	\
			zone = zonelist_zone(z))

#घोषणा क्रम_next_zone_zonelist_nodemask(zone, z, highidx, nodemask) \
	क्रम (zone = z->zone;	\
		zone;							\
		z = next_zones_zonelist(++z, highidx, nodemask),	\
			zone = zonelist_zone(z))


/**
 * क्रम_each_zone_zonelist - helper macro to iterate over valid zones in a zonelist at or below a given zone index
 * @zone: The current zone in the iterator
 * @z: The current poपूर्णांकer within zonelist->zones being iterated
 * @zlist: The zonelist being iterated
 * @highidx: The zone index of the highest zone to वापस
 *
 * This iterator iterates though all zones at or below a given zone index.
 */
#घोषणा क्रम_each_zone_zonelist(zone, z, zlist, highidx) \
	क्रम_each_zone_zonelist_nodemask(zone, z, zlist, highidx, शून्य)

#अगर_घोषित CONFIG_SPARSEMEM
#समावेश <यंत्र/sparseस्मृति.स>
#पूर्ण_अगर

#अगर_घोषित CONFIG_FLATMEM
#घोषणा pfn_to_nid(pfn)		(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SPARSEMEM

/*
 * SECTION_SHIFT    		#bits space required to store a section #
 *
 * PA_SECTION_SHIFT		physical address to/from section number
 * PFN_SECTION_SHIFT		pfn to/from section number
 */
#घोषणा PA_SECTION_SHIFT	(SECTION_SIZE_BITS)
#घोषणा PFN_SECTION_SHIFT	(SECTION_SIZE_BITS - PAGE_SHIFT)

#घोषणा NR_MEM_SECTIONS		(1UL << SECTIONS_SHIFT)

#घोषणा PAGES_PER_SECTION       (1UL << PFN_SECTION_SHIFT)
#घोषणा PAGE_SECTION_MASK	(~(PAGES_PER_SECTION-1))

#घोषणा SECTION_BLOCKFLAGS_BITS \
	((1UL << (PFN_SECTION_SHIFT - pageblock_order)) * NR_PAGEBLOCK_BITS)

#अगर (MAX_ORDER - 1 + PAGE_SHIFT) > SECTION_SIZE_BITS
#त्रुटि Allocator MAX_ORDER exceeds SECTION_SIZE
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ pfn_to_section_nr(अचिन्हित दीर्घ pfn)
अणु
	वापस pfn >> PFN_SECTION_SHIFT;
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ section_nr_to_pfn(अचिन्हित दीर्घ sec)
अणु
	वापस sec << PFN_SECTION_SHIFT;
पूर्ण

#घोषणा SECTION_ALIGN_UP(pfn)	(((pfn) + PAGES_PER_SECTION - 1) & PAGE_SECTION_MASK)
#घोषणा SECTION_ALIGN_DOWN(pfn)	((pfn) & PAGE_SECTION_MASK)

#घोषणा SUBSECTION_SHIFT 21
#घोषणा SUBSECTION_SIZE (1UL << SUBSECTION_SHIFT)

#घोषणा PFN_SUBSECTION_SHIFT (SUBSECTION_SHIFT - PAGE_SHIFT)
#घोषणा PAGES_PER_SUBSECTION (1UL << PFN_SUBSECTION_SHIFT)
#घोषणा PAGE_SUBSECTION_MASK (~(PAGES_PER_SUBSECTION-1))

#अगर SUBSECTION_SHIFT > SECTION_SIZE_BITS
#त्रुटि Subsection size exceeds section size
#अन्यथा
#घोषणा SUBSECTIONS_PER_SECTION (1UL << (SECTION_SIZE_BITS - SUBSECTION_SHIFT))
#पूर्ण_अगर

#घोषणा SUBSECTION_ALIGN_UP(pfn) ALIGN((pfn), PAGES_PER_SUBSECTION)
#घोषणा SUBSECTION_ALIGN_DOWN(pfn) ((pfn) & PAGE_SUBSECTION_MASK)

काष्ठा mem_section_usage अणु
#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
	DECLARE_BITMAP(subsection_map, SUBSECTIONS_PER_SECTION);
#पूर्ण_अगर
	/* See declaration of similar field in काष्ठा zone */
	अचिन्हित दीर्घ pageblock_flags[0];
पूर्ण;

व्योम subsection_map_init(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages);

काष्ठा page;
काष्ठा page_ext;
काष्ठा mem_section अणु
	/*
	 * This is, logically, a poपूर्णांकer to an array of काष्ठा
	 * pages.  However, it is stored with some other magic.
	 * (see sparse.c::sparse_init_one_section())
	 *
	 * Additionally during early boot we encode node id of
	 * the location of the section here to guide allocation.
	 * (see sparse.c::memory_present())
	 *
	 * Making it a UL at least makes someone करो a cast
	 * beक्रमe using it wrong.
	 */
	अचिन्हित दीर्घ section_mem_map;

	काष्ठा mem_section_usage *usage;
#अगर_घोषित CONFIG_PAGE_EXTENSION
	/*
	 * If SPARSEMEM, pgdat करोesn't have page_ext poपूर्णांकer. We use
	 * section. (see page_ext.h about this.)
	 */
	काष्ठा page_ext *page_ext;
	अचिन्हित दीर्घ pad;
#पूर्ण_अगर
	/*
	 * WARNING: mem_section must be a घातer-of-2 in size क्रम the
	 * calculation and use of SECTION_ROOT_MASK to make sense.
	 */
पूर्ण;

#अगर_घोषित CONFIG_SPARSEMEM_EXTREME
#घोषणा SECTIONS_PER_ROOT       (PAGE_SIZE / माप (काष्ठा mem_section))
#अन्यथा
#घोषणा SECTIONS_PER_ROOT	1
#पूर्ण_अगर

#घोषणा SECTION_NR_TO_ROOT(sec)	((sec) / SECTIONS_PER_ROOT)
#घोषणा NR_SECTION_ROOTS	DIV_ROUND_UP(NR_MEM_SECTIONS, SECTIONS_PER_ROOT)
#घोषणा SECTION_ROOT_MASK	(SECTIONS_PER_ROOT - 1)

#अगर_घोषित CONFIG_SPARSEMEM_EXTREME
बाह्य काष्ठा mem_section **mem_section;
#अन्यथा
बाह्य काष्ठा mem_section mem_section[NR_SECTION_ROOTS][SECTIONS_PER_ROOT];
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ *section_to_usemap(काष्ठा mem_section *ms)
अणु
	वापस ms->usage->pageblock_flags;
पूर्ण

अटल अंतरभूत काष्ठा mem_section *__nr_to_section(अचिन्हित दीर्घ nr)
अणु
#अगर_घोषित CONFIG_SPARSEMEM_EXTREME
	अगर (!mem_section)
		वापस शून्य;
#पूर्ण_अगर
	अगर (!mem_section[SECTION_NR_TO_ROOT(nr)])
		वापस शून्य;
	वापस &mem_section[SECTION_NR_TO_ROOT(nr)][nr & SECTION_ROOT_MASK];
पूर्ण
बाह्य अचिन्हित दीर्घ __section_nr(काष्ठा mem_section *ms);
बाह्य माप_प्रकार mem_section_usage_size(व्योम);

/*
 * We use the lower bits of the mem_map poपूर्णांकer to store
 * a little bit of inक्रमmation.  The poपूर्णांकer is calculated
 * as mem_map - section_nr_to_pfn(pnum).  The result is
 * aligned to the minimum alignment of the two values:
 *   1. All mem_map arrays are page-aligned.
 *   2. section_nr_to_pfn() always clears PFN_SECTION_SHIFT
 *      lowest bits.  PFN_SECTION_SHIFT is arch-specअगरic
 *      (equal SECTION_SIZE_BITS - PAGE_SHIFT), and the
 *      worst combination is घातerpc with 256k pages,
 *      which results in PFN_SECTION_SHIFT equal 6.
 * To sum it up, at least 6 bits are available.
 */
#घोषणा SECTION_MARKED_PRESENT		(1UL<<0)
#घोषणा SECTION_HAS_MEM_MAP		(1UL<<1)
#घोषणा SECTION_IS_ONLINE		(1UL<<2)
#घोषणा SECTION_IS_EARLY		(1UL<<3)
#घोषणा SECTION_TAINT_ZONE_DEVICE	(1UL<<4)
#घोषणा SECTION_MAP_LAST_BIT		(1UL<<5)
#घोषणा SECTION_MAP_MASK		(~(SECTION_MAP_LAST_BIT-1))
#घोषणा SECTION_NID_SHIFT		3

अटल अंतरभूत काष्ठा page *__section_mem_map_addr(काष्ठा mem_section *section)
अणु
	अचिन्हित दीर्घ map = section->section_mem_map;
	map &= SECTION_MAP_MASK;
	वापस (काष्ठा page *)map;
पूर्ण

अटल अंतरभूत पूर्णांक present_section(काष्ठा mem_section *section)
अणु
	वापस (section && (section->section_mem_map & SECTION_MARKED_PRESENT));
पूर्ण

अटल अंतरभूत पूर्णांक present_section_nr(अचिन्हित दीर्घ nr)
अणु
	वापस present_section(__nr_to_section(nr));
पूर्ण

अटल अंतरभूत पूर्णांक valid_section(काष्ठा mem_section *section)
अणु
	वापस (section && (section->section_mem_map & SECTION_HAS_MEM_MAP));
पूर्ण

अटल अंतरभूत पूर्णांक early_section(काष्ठा mem_section *section)
अणु
	वापस (section && (section->section_mem_map & SECTION_IS_EARLY));
पूर्ण

अटल अंतरभूत पूर्णांक valid_section_nr(अचिन्हित दीर्घ nr)
अणु
	वापस valid_section(__nr_to_section(nr));
पूर्ण

अटल अंतरभूत पूर्णांक online_section(काष्ठा mem_section *section)
अणु
	वापस (section && (section->section_mem_map & SECTION_IS_ONLINE));
पूर्ण

अटल अंतरभूत पूर्णांक online_device_section(काष्ठा mem_section *section)
अणु
	अचिन्हित दीर्घ flags = SECTION_IS_ONLINE | SECTION_TAINT_ZONE_DEVICE;

	वापस section && ((section->section_mem_map & flags) == flags);
पूर्ण

अटल अंतरभूत पूर्णांक online_section_nr(अचिन्हित दीर्घ nr)
अणु
	वापस online_section(__nr_to_section(nr));
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
व्योम online_mem_sections(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn);
व्योम offline_mem_sections(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn);
#पूर्ण_अगर

अटल अंतरभूत काष्ठा mem_section *__pfn_to_section(अचिन्हित दीर्घ pfn)
अणु
	वापस __nr_to_section(pfn_to_section_nr(pfn));
पूर्ण

बाह्य अचिन्हित दीर्घ __highest_present_section_nr;

अटल अंतरभूत पूर्णांक subsection_map_index(अचिन्हित दीर्घ pfn)
अणु
	वापस (pfn & ~(PAGE_SECTION_MASK)) / PAGES_PER_SUBSECTION;
पूर्ण

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
अटल अंतरभूत पूर्णांक pfn_section_valid(काष्ठा mem_section *ms, अचिन्हित दीर्घ pfn)
अणु
	पूर्णांक idx = subsection_map_index(pfn);

	वापस test_bit(idx, ms->usage->subsection_map);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक pfn_section_valid(काष्ठा mem_section *ms, अचिन्हित दीर्घ pfn)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_HAVE_ARCH_PFN_VALID
अटल अंतरभूत पूर्णांक pfn_valid(अचिन्हित दीर्घ pfn)
अणु
	काष्ठा mem_section *ms;

	अगर (pfn_to_section_nr(pfn) >= NR_MEM_SECTIONS)
		वापस 0;
	ms = __nr_to_section(pfn_to_section_nr(pfn));
	अगर (!valid_section(ms))
		वापस 0;
	/*
	 * Traditionally early sections always वापसed pfn_valid() क्रम
	 * the entire section-sized span.
	 */
	वापस early_section(ms) || pfn_section_valid(ms, pfn);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक pfn_in_present_section(अचिन्हित दीर्घ pfn)
अणु
	अगर (pfn_to_section_nr(pfn) >= NR_MEM_SECTIONS)
		वापस 0;
	वापस present_section(__nr_to_section(pfn_to_section_nr(pfn)));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ next_present_section_nr(अचिन्हित दीर्घ section_nr)
अणु
	जबतक (++section_nr <= __highest_present_section_nr) अणु
		अगर (present_section_nr(section_nr))
			वापस section_nr;
	पूर्ण

	वापस -1;
पूर्ण

/*
 * These are _only_ used during initialisation, thereक्रमe they
 * can use __initdata ...  They could have names to indicate
 * this restriction.
 */
#अगर_घोषित CONFIG_NUMA
#घोषणा pfn_to_nid(pfn)							\
(अणु									\
	अचिन्हित दीर्घ __pfn_to_nid_pfn = (pfn);				\
	page_to_nid(pfn_to_page(__pfn_to_nid_pfn));			\
पूर्ण)
#अन्यथा
#घोषणा pfn_to_nid(pfn)		(0)
#पूर्ण_अगर

व्योम sparse_init(व्योम);
#अन्यथा
#घोषणा sparse_init()	करो अणुपूर्ण जबतक (0)
#घोषणा sparse_index_init(_sec, _nid)  करो अणुपूर्ण जबतक (0)
#घोषणा pfn_in_present_section pfn_valid
#घोषणा subsection_map_init(_pfn, _nr_pages) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_SPARSEMEM */

/*
 * If it is possible to have holes within a MAX_ORDER_NR_PAGES, then we
 * need to check pfn validity within that MAX_ORDER_NR_PAGES block.
 * pfn_valid_within() should be used in this हाल; we optimise this away
 * when we have no holes within a MAX_ORDER_NR_PAGES block.
 */
#अगर_घोषित CONFIG_HOLES_IN_ZONE
#घोषणा pfn_valid_within(pfn) pfn_valid(pfn)
#अन्यथा
#घोषणा pfn_valid_within(pfn) (1)
#पूर्ण_अगर

#पूर्ण_अगर /* !__GENERATING_BOUNDS.H */
#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* _LINUX_MMZONE_H */
