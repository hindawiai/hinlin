<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/mm/page_alloc.c
 *
 *  Manages the मुक्त list, the प्रणाली allocates मुक्त pages here.
 *  Note that kदो_स्मृति() lives in slab.c
 *
 *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 *  Swap reorganised 29.12.95, Stephen Tweedie
 *  Support of BIGMEM added by Gerhard Wichert, Siemens AG, July 1999
 *  Reshaped it to be a zoned allocator, Ingo Molnar, Red Hat, 1999
 *  Discontiguous memory support, Kanoj Sarcar, SGI, Nov 1999
 *  Zone balancing, Kanoj Sarcar, SGI, Jan 2000
 *  Per cpu hot/cold page lists, bulk allocation, Martin J. Bligh, Sept 2002
 *          (lots of bits borrowed from Ingo Molnar & Andrew Morton)
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/swap.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/memblock.h>
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kasan.h>
#समावेश <linux/module.h>
#समावेश <linux/suspend.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/oom.h>
#समावेश <linux/topology.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/memory_hotplug.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/vmस्थिति.स>
#समावेश <linux/mempolicy.h>
#समावेश <linux/memremap.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sort.h>
#समावेश <linux/pfn.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/fault-inject.h>
#समावेश <linux/page-isolation.h>
#समावेश <linux/debugobjects.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/compaction.h>
#समावेश <trace/events/kस्मृति.स>
#समावेश <trace/events/oom.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/migrate.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/sched/rt.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/page_owner.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/nmi.h>
#समावेश <linux/psi.h>
#समावेश <linux/padata.h>
#समावेश <linux/khugepaged.h>
#समावेश <linux/buffer_head.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/भाग64.h>
#समावेश "internal.h"
#समावेश "shuffle.h"
#समावेश "page_reporting.h"

/* Free Page Internal flags: क्रम पूर्णांकernal, non-pcp variants of मुक्त_pages(). */
प्रकार पूर्णांक __bitwise fpi_t;

/* No special request */
#घोषणा FPI_NONE		((__क्रमce fpi_t)0)

/*
 * Skip मुक्त page reporting notअगरication क्रम the (possibly merged) page.
 * This करोes not hinder मुक्त page reporting from grabbing the page,
 * reporting it and marking it "reported" -  it only skips notअगरying
 * the मुक्त page reporting infraकाष्ठाure about a newly मुक्तd page. For
 * example, used when temporarily pulling a page from a मुक्तlist and
 * putting it back unmodअगरied.
 */
#घोषणा FPI_SKIP_REPORT_NOTIFY	((__क्रमce fpi_t)BIT(0))

/*
 * Place the (possibly merged) page to the tail of the मुक्तlist. Will ignore
 * page shuffling (relevant code - e.g., memory onlining - is expected to
 * shuffle the whole zone).
 *
 * Note: No code should rely on this flag क्रम correctness - it's purely
 *       to allow क्रम optimizations when handing back either fresh pages
 *       (memory onlining) or untouched pages (page isolation, मुक्त page
 *       reporting).
 */
#घोषणा FPI_TO_TAIL		((__क्रमce fpi_t)BIT(1))

/*
 * Don't poison memory with KASAN (only क्रम the tag-based modes).
 * During boot, all non-reserved memblock memory is exposed to page_alloc.
 * Poisoning all that memory lengthens boot समय, especially on प्रणालीs with
 * large amount of RAM. This flag is used to skip that poisoning.
 * This is only करोne क्रम the tag-based KASAN modes, as those are able to
 * detect memory corruptions with the memory tags asचिन्हित by शेष.
 * All memory allocated normally after boot माला_लो poisoned as usual.
 */
#घोषणा FPI_SKIP_KASAN_POISON	((__क्रमce fpi_t)BIT(2))

/* prevent >1 _updater_ of zone percpu pageset ->high and ->batch fields */
अटल DEFINE_MUTEX(pcp_batch_high_lock);
#घोषणा MIN_PERCPU_PAGELIST_FRACTION	(8)

#अगर_घोषित CONFIG_USE_PERCPU_NUMA_NODE_ID
DEFINE_PER_CPU(पूर्णांक, numa_node);
EXPORT_PER_CPU_SYMBOL(numa_node);
#पूर्ण_अगर

DEFINE_STATIC_KEY_TRUE(vm_numa_stat_key);

#अगर_घोषित CONFIG_HAVE_MEMORYLESS_NODES
/*
 * N.B., Do NOT reference the '_numa_mem_' per cpu variable directly.
 * It will not be defined when CONFIG_HAVE_MEMORYLESS_NODES is not defined.
 * Use the accessor functions set_numa_mem(), numa_mem_id() and cpu_to_mem()
 * defined in <linux/topology.h>.
 */
DEFINE_PER_CPU(पूर्णांक, _numa_mem_);		/* Kernel "local memory" node */
EXPORT_PER_CPU_SYMBOL(_numa_mem_);
#पूर्ण_अगर

/* work_काष्ठाs क्रम global per-cpu drains */
काष्ठा pcpu_drain अणु
	काष्ठा zone *zone;
	काष्ठा work_काष्ठा work;
पूर्ण;
अटल DEFINE_MUTEX(pcpu_drain_mutex);
अटल DEFINE_PER_CPU(काष्ठा pcpu_drain, pcpu_drain);

#अगर_घोषित CONFIG_GCC_PLUGIN_LATENT_ENTROPY
अस्थिर अचिन्हित दीर्घ latent_entropy __latent_entropy;
EXPORT_SYMBOL(latent_entropy);
#पूर्ण_अगर

/*
 * Array of node states.
 */
nodemask_t node_states[NR_NODE_STATES] __पढ़ो_mostly = अणु
	[N_POSSIBLE] = NODE_MASK_ALL,
	[N_ONLINE] = अणु अणु [0] = 1UL पूर्ण पूर्ण,
#अगर_अघोषित CONFIG_NUMA
	[N_NORMAL_MEMORY] = अणु अणु [0] = 1UL पूर्ण पूर्ण,
#अगर_घोषित CONFIG_HIGHMEM
	[N_HIGH_MEMORY] = अणु अणु [0] = 1UL पूर्ण पूर्ण,
#पूर्ण_अगर
	[N_MEMORY] = अणु अणु [0] = 1UL पूर्ण पूर्ण,
	[N_CPU] = अणु अणु [0] = 1UL पूर्ण पूर्ण,
#पूर्ण_अगर	/* NUMA */
पूर्ण;
EXPORT_SYMBOL(node_states);

atomic_दीर्घ_t _totalram_pages __पढ़ो_mostly;
EXPORT_SYMBOL(_totalram_pages);
अचिन्हित दीर्घ totalreserve_pages __पढ़ो_mostly;
अचिन्हित दीर्घ totalcma_pages __पढ़ो_mostly;

पूर्णांक percpu_pagelist_fraction;
gfp_t gfp_allowed_mask __पढ़ो_mostly = GFP_BOOT_MASK;
DEFINE_STATIC_KEY_MAYBE(CONFIG_INIT_ON_ALLOC_DEFAULT_ON, init_on_alloc);
EXPORT_SYMBOL(init_on_alloc);

DEFINE_STATIC_KEY_MAYBE(CONFIG_INIT_ON_FREE_DEFAULT_ON, init_on_मुक्त);
EXPORT_SYMBOL(init_on_मुक्त);

अटल bool _init_on_alloc_enabled_early __पढ़ो_mostly
				= IS_ENABLED(CONFIG_INIT_ON_ALLOC_DEFAULT_ON);
अटल पूर्णांक __init early_init_on_alloc(अक्षर *buf)
अणु

	वापस kstrtobool(buf, &_init_on_alloc_enabled_early);
पूर्ण
early_param("init_on_alloc", early_init_on_alloc);

अटल bool _init_on_मुक्त_enabled_early __पढ़ो_mostly
				= IS_ENABLED(CONFIG_INIT_ON_FREE_DEFAULT_ON);
अटल पूर्णांक __init early_init_on_मुक्त(अक्षर *buf)
अणु
	वापस kstrtobool(buf, &_init_on_मुक्त_enabled_early);
पूर्ण
early_param("init_on_free", early_init_on_मुक्त);

/*
 * A cached value of the page's pageblock's migratetype, used when the page is
 * put on a pcplist. Used to aव्योम the pageblock migratetype lookup when
 * मुक्तing from pcplists in most हालs, at the cost of possibly becoming stale.
 * Also the migratetype set in the page करोes not necessarily match the pcplist
 * index, e.g. page might have MIGRATE_CMA set but be on a pcplist with any
 * other index - this ensures that it will be put on the correct CMA मुक्तlist.
 */
अटल अंतरभूत पूर्णांक get_pcppage_migratetype(काष्ठा page *page)
अणु
	वापस page->index;
पूर्ण

अटल अंतरभूत व्योम set_pcppage_migratetype(काष्ठा page *page, पूर्णांक migratetype)
अणु
	page->index = migratetype;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * The following functions are used by the suspend/hibernate code to temporarily
 * change gfp_allowed_mask in order to aव्योम using I/O during memory allocations
 * जबतक devices are suspended.  To aव्योम races with the suspend/hibernate code,
 * they should always be called with प्रणाली_transition_mutex held
 * (gfp_allowed_mask also should only be modअगरied with प्रणाली_transition_mutex
 * held, unless the suspend/hibernate code is guaranteed not to run in parallel
 * with that modअगरication).
 */

अटल gfp_t saved_gfp_mask;

व्योम pm_restore_gfp_mask(व्योम)
अणु
	WARN_ON(!mutex_is_locked(&प्रणाली_transition_mutex));
	अगर (saved_gfp_mask) अणु
		gfp_allowed_mask = saved_gfp_mask;
		saved_gfp_mask = 0;
	पूर्ण
पूर्ण

व्योम pm_restrict_gfp_mask(व्योम)
अणु
	WARN_ON(!mutex_is_locked(&प्रणाली_transition_mutex));
	WARN_ON(saved_gfp_mask);
	saved_gfp_mask = gfp_allowed_mask;
	gfp_allowed_mask &= ~(__GFP_IO | __GFP_FS);
पूर्ण

bool pm_suspended_storage(व्योम)
अणु
	अगर ((gfp_allowed_mask & (__GFP_IO | __GFP_FS)) == (__GFP_IO | __GFP_FS))
		वापस false;
	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_HUGETLB_PAGE_SIZE_VARIABLE
अचिन्हित पूर्णांक pageblock_order __पढ़ो_mostly;
#पूर्ण_अगर

अटल व्योम __मुक्त_pages_ok(काष्ठा page *page, अचिन्हित पूर्णांक order,
			    fpi_t fpi_flags);

/*
 * results with 256, 32 in the lowmem_reserve sysctl:
 *	1G machine -> (16M dma, 800M-16M normal, 1G-800M high)
 *	1G machine -> (16M dma, 784M normal, 224M high)
 *	NORMAL allocation will leave 784M/256 of ram reserved in the ZONE_DMA
 *	HIGHMEM allocation will leave 224M/32 of ram reserved in ZONE_NORMAL
 *	HIGHMEM allocation will leave (224M+784M)/256 of ram reserved in ZONE_DMA
 *
 * TBD: should special हाल ZONE_DMA32 machines here - in those we normally
 * करोn't need any ZONE_NORMAL reservation
 */
पूर्णांक sysctl_lowmem_reserve_ratio[MAX_NR_ZONES] = अणु
#अगर_घोषित CONFIG_ZONE_DMA
	[ZONE_DMA] = 256,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ZONE_DMA32
	[ZONE_DMA32] = 256,
#पूर्ण_अगर
	[ZONE_NORMAL] = 32,
#अगर_घोषित CONFIG_HIGHMEM
	[ZONE_HIGHMEM] = 0,
#पूर्ण_अगर
	[ZONE_MOVABLE] = 0,
पूर्ण;

अटल अक्षर * स्थिर zone_names[MAX_NR_ZONES] = अणु
#अगर_घोषित CONFIG_ZONE_DMA
	 "DMA",
#पूर्ण_अगर
#अगर_घोषित CONFIG_ZONE_DMA32
	 "DMA32",
#पूर्ण_अगर
	 "Normal",
#अगर_घोषित CONFIG_HIGHMEM
	 "HighMem",
#पूर्ण_अगर
	 "Movable",
#अगर_घोषित CONFIG_ZONE_DEVICE
	 "Device",
#पूर्ण_अगर
पूर्ण;

स्थिर अक्षर * स्थिर migratetype_names[MIGRATE_TYPES] = अणु
	"Unmovable",
	"Movable",
	"Reclaimable",
	"HighAtomic",
#अगर_घोषित CONFIG_CMA
	"CMA",
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEMORY_ISOLATION
	"Isolate",
#पूर्ण_अगर
पूर्ण;

compound_page_dtor * स्थिर compound_page_dtors[NR_COMPOUND_DTORS] = अणु
	[शून्य_COMPOUND_DTOR] = शून्य,
	[COMPOUND_PAGE_DTOR] = मुक्त_compound_page,
#अगर_घोषित CONFIG_HUGETLB_PAGE
	[HUGETLB_PAGE_DTOR] = मुक्त_huge_page,
#पूर्ण_अगर
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	[TRANSHUGE_PAGE_DTOR] = मुक्त_transhuge_page,
#पूर्ण_अगर
पूर्ण;

पूर्णांक min_मुक्त_kbytes = 1024;
पूर्णांक user_min_मुक्त_kbytes = -1;
#अगर_घोषित CONFIG_DISCONTIGMEM
/*
 * DiscontigMem defines memory ranges as separate pg_data_t even अगर the ranges
 * are not on separate NUMA nodes. Functionally this works but with
 * watermark_boost_factor, it can reclaim prematurely as the ranges can be
 * quite small. By शेष, करो not boost watermarks on discontigmem as in
 * many हालs very high-order allocations like THP are likely to be
 * unsupported and the premature reclaim offsets the advantage of दीर्घ-term
 * fragmentation aव्योमance.
 */
पूर्णांक watermark_boost_factor __पढ़ो_mostly;
#अन्यथा
पूर्णांक watermark_boost_factor __पढ़ो_mostly = 15000;
#पूर्ण_अगर
पूर्णांक watermark_scale_factor = 10;

अटल अचिन्हित दीर्घ nr_kernel_pages __initdata;
अटल अचिन्हित दीर्घ nr_all_pages __initdata;
अटल अचिन्हित दीर्घ dma_reserve __initdata;

अटल अचिन्हित दीर्घ arch_zone_lowest_possible_pfn[MAX_NR_ZONES] __initdata;
अटल अचिन्हित दीर्घ arch_zone_highest_possible_pfn[MAX_NR_ZONES] __initdata;
अटल अचिन्हित दीर्घ required_kernelcore __initdata;
अटल अचिन्हित दीर्घ required_kernelcore_percent __initdata;
अटल अचिन्हित दीर्घ required_movablecore __initdata;
अटल अचिन्हित दीर्घ required_movablecore_percent __initdata;
अटल अचिन्हित दीर्घ zone_movable_pfn[MAX_NUMNODES] __initdata;
अटल bool mirrored_kernelcore __meminitdata;

/* movable_zone is the "real" zone pages in ZONE_MOVABLE are taken from */
पूर्णांक movable_zone;
EXPORT_SYMBOL(movable_zone);

#अगर MAX_NUMNODES > 1
अचिन्हित पूर्णांक nr_node_ids __पढ़ो_mostly = MAX_NUMNODES;
अचिन्हित पूर्णांक nr_online_nodes __पढ़ो_mostly = 1;
EXPORT_SYMBOL(nr_node_ids);
EXPORT_SYMBOL(nr_online_nodes);
#पूर्ण_अगर

पूर्णांक page_group_by_mobility_disabled __पढ़ो_mostly;

#अगर_घोषित CONFIG_DEFERRED_STRUCT_PAGE_INIT
/*
 * During boot we initialize deferred pages on-demand, as needed, but once
 * page_alloc_init_late() has finished, the deferred pages are all initialized,
 * and we can permanently disable that path.
 */
अटल DEFINE_STATIC_KEY_TRUE(deferred_pages);

/*
 * Calling kasan_मुक्त_pages() only after deferred memory initialization
 * has completed. Poisoning pages during deferred memory init will greatly
 * lengthen the process and cause problem in large memory प्रणालीs as the
 * deferred pages initialization is करोne with पूर्णांकerrupt disabled.
 *
 * Assuming that there will be no reference to those newly initialized
 * pages beक्रमe they are ever allocated, this should have no effect on
 * KASAN memory tracking as the poison will be properly inserted at page
 * allocation समय. The only corner हाल is when pages are allocated by
 * on-demand allocation and then मुक्तd again beक्रमe the deferred pages
 * initialization is करोne, but this is not likely to happen.
 */
अटल अंतरभूत व्योम kasan_मुक्त_nondeferred_pages(काष्ठा page *page, पूर्णांक order,
						bool init, fpi_t fpi_flags)
अणु
	अगर (अटल_branch_unlikely(&deferred_pages))
		वापस;
	अगर (!IS_ENABLED(CONFIG_KASAN_GENERIC) &&
			(fpi_flags & FPI_SKIP_KASAN_POISON))
		वापस;
	kasan_मुक्त_pages(page, order, init);
पूर्ण

/* Returns true अगर the काष्ठा page क्रम the pfn is uninitialised */
अटल अंतरभूत bool __meminit early_page_uninitialised(अचिन्हित दीर्घ pfn)
अणु
	पूर्णांक nid = early_pfn_to_nid(pfn);

	अगर (node_online(nid) && pfn >= NODE_DATA(nid)->first_deferred_pfn)
		वापस true;

	वापस false;
पूर्ण

/*
 * Returns true when the reमुख्यing initialisation should be deferred until
 * later in the boot cycle when it can be parallelised.
 */
अटल bool __meminit
defer_init(पूर्णांक nid, अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ end_pfn)
अणु
	अटल अचिन्हित दीर्घ prev_end_pfn, nr_initialised;

	/*
	 * prev_end_pfn अटल that contains the end of previous zone
	 * No need to protect because called very early in boot beक्रमe smp_init.
	 */
	अगर (prev_end_pfn != end_pfn) अणु
		prev_end_pfn = end_pfn;
		nr_initialised = 0;
	पूर्ण

	/* Always populate low zones क्रम address-स्थिरrained allocations */
	अगर (end_pfn < pgdat_end_pfn(NODE_DATA(nid)))
		वापस false;

	अगर (NODE_DATA(nid)->first_deferred_pfn != अच_दीर्घ_उच्च)
		वापस true;
	/*
	 * We start only with one section of pages, more pages are added as
	 * needed until the rest of deferred pages are initialized.
	 */
	nr_initialised++;
	अगर ((nr_initialised > PAGES_PER_SECTION) &&
	    (pfn & (PAGES_PER_SECTION - 1)) == 0) अणु
		NODE_DATA(nid)->first_deferred_pfn = pfn;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम kasan_मुक्त_nondeferred_pages(काष्ठा page *page, पूर्णांक order,
						bool init, fpi_t fpi_flags)
अणु
	अगर (!IS_ENABLED(CONFIG_KASAN_GENERIC) &&
			(fpi_flags & FPI_SKIP_KASAN_POISON))
		वापस;
	kasan_मुक्त_pages(page, order, init);
पूर्ण

अटल अंतरभूत bool early_page_uninitialised(अचिन्हित दीर्घ pfn)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool defer_init(पूर्णांक nid, अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ end_pfn)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/* Return a poपूर्णांकer to the biपंचांगap storing bits affecting a block of pages */
अटल अंतरभूत अचिन्हित दीर्घ *get_pageblock_biपंचांगap(काष्ठा page *page,
							अचिन्हित दीर्घ pfn)
अणु
#अगर_घोषित CONFIG_SPARSEMEM
	वापस section_to_usemap(__pfn_to_section(pfn));
#अन्यथा
	वापस page_zone(page)->pageblock_flags;
#पूर्ण_अगर /* CONFIG_SPARSEMEM */
पूर्ण

अटल अंतरभूत पूर्णांक pfn_to_bitidx(काष्ठा page *page, अचिन्हित दीर्घ pfn)
अणु
#अगर_घोषित CONFIG_SPARSEMEM
	pfn &= (PAGES_PER_SECTION-1);
#अन्यथा
	pfn = pfn - round_करोwn(page_zone(page)->zone_start_pfn, pageblock_nr_pages);
#पूर्ण_अगर /* CONFIG_SPARSEMEM */
	वापस (pfn >> pageblock_order) * NR_PAGEBLOCK_BITS;
पूर्ण

अटल __always_अंतरभूत
अचिन्हित दीर्घ __get_pfnblock_flags_mask(काष्ठा page *page,
					अचिन्हित दीर्घ pfn,
					अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ *biपंचांगap;
	अचिन्हित दीर्घ bitidx, word_bitidx;
	अचिन्हित दीर्घ word;

	biपंचांगap = get_pageblock_biपंचांगap(page, pfn);
	bitidx = pfn_to_bitidx(page, pfn);
	word_bitidx = bitidx / BITS_PER_LONG;
	bitidx &= (BITS_PER_LONG-1);

	word = biपंचांगap[word_bitidx];
	वापस (word >> bitidx) & mask;
पूर्ण

/**
 * get_pfnblock_flags_mask - Return the requested group of flags क्रम the pageblock_nr_pages block of pages
 * @page: The page within the block of पूर्णांकerest
 * @pfn: The target page frame number
 * @mask: mask of bits that the caller is पूर्णांकerested in
 *
 * Return: pageblock_bits flags
 */
अचिन्हित दीर्घ get_pfnblock_flags_mask(काष्ठा page *page, अचिन्हित दीर्घ pfn,
					अचिन्हित दीर्घ mask)
अणु
	वापस __get_pfnblock_flags_mask(page, pfn, mask);
पूर्ण

अटल __always_अंतरभूत पूर्णांक get_pfnblock_migratetype(काष्ठा page *page, अचिन्हित दीर्घ pfn)
अणु
	वापस __get_pfnblock_flags_mask(page, pfn, MIGRATETYPE_MASK);
पूर्ण

/**
 * set_pfnblock_flags_mask - Set the requested group of flags क्रम a pageblock_nr_pages block of pages
 * @page: The page within the block of पूर्णांकerest
 * @flags: The flags to set
 * @pfn: The target page frame number
 * @mask: mask of bits that the caller is पूर्णांकerested in
 */
व्योम set_pfnblock_flags_mask(काष्ठा page *page, अचिन्हित दीर्घ flags,
					अचिन्हित दीर्घ pfn,
					अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ *biपंचांगap;
	अचिन्हित दीर्घ bitidx, word_bitidx;
	अचिन्हित दीर्घ old_word, word;

	BUILD_BUG_ON(NR_PAGEBLOCK_BITS != 4);
	BUILD_BUG_ON(MIGRATE_TYPES > (1 << PB_migratetype_bits));

	biपंचांगap = get_pageblock_biपंचांगap(page, pfn);
	bitidx = pfn_to_bitidx(page, pfn);
	word_bitidx = bitidx / BITS_PER_LONG;
	bitidx &= (BITS_PER_LONG-1);

	VM_BUG_ON_PAGE(!zone_spans_pfn(page_zone(page), pfn), page);

	mask <<= bitidx;
	flags <<= bitidx;

	word = READ_ONCE(biपंचांगap[word_bitidx]);
	क्रम (;;) अणु
		old_word = cmpxchg(&biपंचांगap[word_bitidx], word, (word & ~mask) | flags);
		अगर (word == old_word)
			अवरोध;
		word = old_word;
	पूर्ण
पूर्ण

व्योम set_pageblock_migratetype(काष्ठा page *page, पूर्णांक migratetype)
अणु
	अगर (unlikely(page_group_by_mobility_disabled &&
		     migratetype < MIGRATE_PCPTYPES))
		migratetype = MIGRATE_UNMOVABLE;

	set_pfnblock_flags_mask(page, (अचिन्हित दीर्घ)migratetype,
				page_to_pfn(page), MIGRATETYPE_MASK);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_VM
अटल पूर्णांक page_outside_zone_boundaries(काष्ठा zone *zone, काष्ठा page *page)
अणु
	पूर्णांक ret = 0;
	अचिन्हित seq;
	अचिन्हित दीर्घ pfn = page_to_pfn(page);
	अचिन्हित दीर्घ sp, start_pfn;

	करो अणु
		seq = zone_span_seqbegin(zone);
		start_pfn = zone->zone_start_pfn;
		sp = zone->spanned_pages;
		अगर (!zone_spans_pfn(zone, pfn))
			ret = 1;
	पूर्ण जबतक (zone_span_seqretry(zone, seq));

	अगर (ret)
		pr_err("page 0x%lx outside node %d zone %s [ 0x%lx - 0x%lx ]\n",
			pfn, zone_to_nid(zone), zone->name,
			start_pfn, start_pfn + sp);

	वापस ret;
पूर्ण

अटल पूर्णांक page_is_consistent(काष्ठा zone *zone, काष्ठा page *page)
अणु
	अगर (!pfn_valid_within(page_to_pfn(page)))
		वापस 0;
	अगर (zone != page_zone(page))
		वापस 0;

	वापस 1;
पूर्ण
/*
 * Temporary debugging check क्रम pages not lying within a given zone.
 */
अटल पूर्णांक __maybe_unused bad_range(काष्ठा zone *zone, काष्ठा page *page)
अणु
	अगर (page_outside_zone_boundaries(zone, page))
		वापस 1;
	अगर (!page_is_consistent(zone, page))
		वापस 1;

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक __maybe_unused bad_range(काष्ठा zone *zone, काष्ठा page *page)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम bad_page(काष्ठा page *page, स्थिर अक्षर *reason)
अणु
	अटल अचिन्हित दीर्घ resume;
	अटल अचिन्हित दीर्घ nr_shown;
	अटल अचिन्हित दीर्घ nr_unshown;

	/*
	 * Allow a burst of 60 reports, then keep quiet क्रम that minute;
	 * or allow a steady drip of one report per second.
	 */
	अगर (nr_shown == 60) अणु
		अगर (समय_beक्रमe(jअगरfies, resume)) अणु
			nr_unshown++;
			जाओ out;
		पूर्ण
		अगर (nr_unshown) अणु
			pr_alert(
			      "BUG: Bad page state: %lu messages suppressed\n",
				nr_unshown);
			nr_unshown = 0;
		पूर्ण
		nr_shown = 0;
	पूर्ण
	अगर (nr_shown++ == 0)
		resume = jअगरfies + 60 * HZ;

	pr_alert("BUG: Bad page state in process %s  pfn:%05lx\n",
		current->comm, page_to_pfn(page));
	__dump_page(page, reason);
	dump_page_owner(page);

	prपूर्णांक_modules();
	dump_stack();
out:
	/* Leave bad fields क्रम debug, except PageBuddy could make trouble */
	page_mapcount_reset(page); /* हटाओ PageBuddy */
	add_taपूर्णांक(TAINT_BAD_PAGE, LOCKDEP_NOW_UNRELIABLE);
पूर्ण

/*
 * Higher-order pages are called "compound pages".  They are काष्ठाured thusly:
 *
 * The first PAGE_SIZE page is called the "head page" and have PG_head set.
 *
 * The reमुख्यing PAGE_SIZE pages are called "tail pages". PageTail() is encoded
 * in bit 0 of page->compound_head. The rest of bits is poपूर्णांकer to head page.
 *
 * The first tail page's ->compound_dtor holds the offset in array of compound
 * page deकाष्ठाors. See compound_page_dtors.
 *
 * The first tail page's ->compound_order holds the order of allocation.
 * This usage means that zero-order pages may not be compound.
 */

व्योम मुक्त_compound_page(काष्ठा page *page)
अणु
	mem_cgroup_unअक्षरge(page);
	__मुक्त_pages_ok(page, compound_order(page), FPI_NONE);
पूर्ण

व्योम prep_compound_page(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	पूर्णांक i;
	पूर्णांक nr_pages = 1 << order;

	__SetPageHead(page);
	क्रम (i = 1; i < nr_pages; i++) अणु
		काष्ठा page *p = page + i;
		set_page_count(p, 0);
		p->mapping = TAIL_MAPPING;
		set_compound_head(p, page);
	पूर्ण

	set_compound_page_dtor(page, COMPOUND_PAGE_DTOR);
	set_compound_order(page, order);
	atomic_set(compound_mapcount_ptr(page), -1);
	अगर (hpage_pincount_available(page))
		atomic_set(compound_pincount_ptr(page), 0);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
अचिन्हित पूर्णांक _debug_guardpage_minorder;

bool _debug_pagealloc_enabled_early __पढ़ो_mostly
			= IS_ENABLED(CONFIG_DEBUG_PAGEALLOC_ENABLE_DEFAULT);
EXPORT_SYMBOL(_debug_pagealloc_enabled_early);
DEFINE_STATIC_KEY_FALSE(_debug_pagealloc_enabled);
EXPORT_SYMBOL(_debug_pagealloc_enabled);

DEFINE_STATIC_KEY_FALSE(_debug_guardpage_enabled);

अटल पूर्णांक __init early_debug_pagealloc(अक्षर *buf)
अणु
	वापस kstrtobool(buf, &_debug_pagealloc_enabled_early);
पूर्ण
early_param("debug_pagealloc", early_debug_pagealloc);

अटल पूर्णांक __init debug_guardpage_minorder_setup(अक्षर *buf)
अणु
	अचिन्हित दीर्घ res;

	अगर (kम_से_अदीर्घ(buf, 10, &res) < 0 ||  res > MAX_ORDER / 2) अणु
		pr_err("Bad debug_guardpage_minorder value\n");
		वापस 0;
	पूर्ण
	_debug_guardpage_minorder = res;
	pr_info("Setting debug_guardpage_minorder to %lu\n", res);
	वापस 0;
पूर्ण
early_param("debug_guardpage_minorder", debug_guardpage_minorder_setup);

अटल अंतरभूत bool set_page_guard(काष्ठा zone *zone, काष्ठा page *page,
				अचिन्हित पूर्णांक order, पूर्णांक migratetype)
अणु
	अगर (!debug_guardpage_enabled())
		वापस false;

	अगर (order >= debug_guardpage_minorder())
		वापस false;

	__SetPageGuard(page);
	INIT_LIST_HEAD(&page->lru);
	set_page_निजी(page, order);
	/* Guard pages are not available क्रम any usage */
	__mod_zone_मुक्तpage_state(zone, -(1 << order), migratetype);

	वापस true;
पूर्ण

अटल अंतरभूत व्योम clear_page_guard(काष्ठा zone *zone, काष्ठा page *page,
				अचिन्हित पूर्णांक order, पूर्णांक migratetype)
अणु
	अगर (!debug_guardpage_enabled())
		वापस;

	__ClearPageGuard(page);

	set_page_निजी(page, 0);
	अगर (!is_migrate_isolate(migratetype))
		__mod_zone_मुक्तpage_state(zone, (1 << order), migratetype);
पूर्ण
#अन्यथा
अटल अंतरभूत bool set_page_guard(काष्ठा zone *zone, काष्ठा page *page,
			अचिन्हित पूर्णांक order, पूर्णांक migratetype) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम clear_page_guard(काष्ठा zone *zone, काष्ठा page *page,
				अचिन्हित पूर्णांक order, पूर्णांक migratetype) अणुपूर्ण
#पूर्ण_अगर

/*
 * Enable अटल keys related to various memory debugging and hardening options.
 * Some override others, and depend on early params that are evaluated in the
 * order of appearance. So we need to first gather the full picture of what was
 * enabled, and then make decisions.
 */
व्योम init_mem_debugging_and_hardening(व्योम)
अणु
	bool page_poisoning_requested = false;

#अगर_घोषित CONFIG_PAGE_POISONING
	/*
	 * Page poisoning is debug page alloc क्रम some arches. If
	 * either of those options are enabled, enable poisoning.
	 */
	अगर (page_poisoning_enabled() ||
	     (!IS_ENABLED(CONFIG_ARCH_SUPPORTS_DEBUG_PAGEALLOC) &&
	      debug_pagealloc_enabled())) अणु
		अटल_branch_enable(&_page_poisoning_enabled);
		page_poisoning_requested = true;
	पूर्ण
#पूर्ण_अगर

	अगर (_init_on_alloc_enabled_early) अणु
		अगर (page_poisoning_requested)
			pr_info("mem auto-init: CONFIG_PAGE_POISONING is on, "
				"will take precedence over init_on_alloc\n");
		अन्यथा
			अटल_branch_enable(&init_on_alloc);
	पूर्ण
	अगर (_init_on_मुक्त_enabled_early) अणु
		अगर (page_poisoning_requested)
			pr_info("mem auto-init: CONFIG_PAGE_POISONING is on, "
				"will take precedence over init_on_free\n");
		अन्यथा
			अटल_branch_enable(&init_on_मुक्त);
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
	अगर (!debug_pagealloc_enabled())
		वापस;

	अटल_branch_enable(&_debug_pagealloc_enabled);

	अगर (!debug_guardpage_minorder())
		वापस;

	अटल_branch_enable(&_debug_guardpage_enabled);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम set_buddy_order(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	set_page_निजी(page, order);
	__SetPageBuddy(page);
पूर्ण

/*
 * This function checks whether a page is मुक्त && is the buddy
 * we can coalesce a page and its buddy अगर
 * (a) the buddy is not in a hole (check beक्रमe calling!) &&
 * (b) the buddy is in the buddy प्रणाली &&
 * (c) a page and its buddy have the same order &&
 * (d) a page and its buddy are in the same zone.
 *
 * For recording whether a page is in the buddy प्रणाली, we set PageBuddy.
 * Setting, clearing, and testing PageBuddy is serialized by zone->lock.
 *
 * For recording page's order, we use page_निजी(page).
 */
अटल अंतरभूत bool page_is_buddy(काष्ठा page *page, काष्ठा page *buddy,
							अचिन्हित पूर्णांक order)
अणु
	अगर (!page_is_guard(buddy) && !PageBuddy(buddy))
		वापस false;

	अगर (buddy_order(buddy) != order)
		वापस false;

	/*
	 * zone check is करोne late to aव्योम uselessly calculating
	 * zone/node ids क्रम pages that could never merge.
	 */
	अगर (page_zone_id(page) != page_zone_id(buddy))
		वापस false;

	VM_BUG_ON_PAGE(page_count(buddy) != 0, buddy);

	वापस true;
पूर्ण

#अगर_घोषित CONFIG_COMPACTION
अटल अंतरभूत काष्ठा capture_control *task_capc(काष्ठा zone *zone)
अणु
	काष्ठा capture_control *capc = current->capture_control;

	वापस unlikely(capc) &&
		!(current->flags & PF_KTHREAD) &&
		!capc->page &&
		capc->cc->zone == zone ? capc : शून्य;
पूर्ण

अटल अंतरभूत bool
compaction_capture(काष्ठा capture_control *capc, काष्ठा page *page,
		   पूर्णांक order, पूर्णांक migratetype)
अणु
	अगर (!capc || order != capc->cc->order)
		वापस false;

	/* Do not accidentally pollute CMA or isolated regions*/
	अगर (is_migrate_cma(migratetype) ||
	    is_migrate_isolate(migratetype))
		वापस false;

	/*
	 * Do not let lower order allocations pollute a movable pageblock.
	 * This might let an unmovable request use a reclaimable pageblock
	 * and vice-versa but no more than normal fallback logic which can
	 * have trouble finding a high-order मुक्त page.
	 */
	अगर (order < pageblock_order && migratetype == MIGRATE_MOVABLE)
		वापस false;

	capc->page = page;
	वापस true;
पूर्ण

#अन्यथा
अटल अंतरभूत काष्ठा capture_control *task_capc(काष्ठा zone *zone)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool
compaction_capture(काष्ठा capture_control *capc, काष्ठा page *page,
		   पूर्णांक order, पूर्णांक migratetype)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPACTION */

/* Used क्रम pages not on another list */
अटल अंतरभूत व्योम add_to_मुक्त_list(काष्ठा page *page, काष्ठा zone *zone,
				    अचिन्हित पूर्णांक order, पूर्णांक migratetype)
अणु
	काष्ठा मुक्त_area *area = &zone->मुक्त_area[order];

	list_add(&page->lru, &area->मुक्त_list[migratetype]);
	area->nr_मुक्त++;
पूर्ण

/* Used क्रम pages not on another list */
अटल अंतरभूत व्योम add_to_मुक्त_list_tail(काष्ठा page *page, काष्ठा zone *zone,
					 अचिन्हित पूर्णांक order, पूर्णांक migratetype)
अणु
	काष्ठा मुक्त_area *area = &zone->मुक्त_area[order];

	list_add_tail(&page->lru, &area->मुक्त_list[migratetype]);
	area->nr_मुक्त++;
पूर्ण

/*
 * Used क्रम pages which are on another list. Move the pages to the tail
 * of the list - so the moved pages won't immediately be considered क्रम
 * allocation again (e.g., optimization क्रम memory onlining).
 */
अटल अंतरभूत व्योम move_to_मुक्त_list(काष्ठा page *page, काष्ठा zone *zone,
				     अचिन्हित पूर्णांक order, पूर्णांक migratetype)
अणु
	काष्ठा मुक्त_area *area = &zone->मुक्त_area[order];

	list_move_tail(&page->lru, &area->मुक्त_list[migratetype]);
पूर्ण

अटल अंतरभूत व्योम del_page_from_मुक्त_list(काष्ठा page *page, काष्ठा zone *zone,
					   अचिन्हित पूर्णांक order)
अणु
	/* clear reported state and update reported page count */
	अगर (page_reported(page))
		__ClearPageReported(page);

	list_del(&page->lru);
	__ClearPageBuddy(page);
	set_page_निजी(page, 0);
	zone->मुक्त_area[order].nr_मुक्त--;
पूर्ण

/*
 * If this is not the largest possible page, check अगर the buddy
 * of the next-highest order is मुक्त. If it is, it's possible
 * that pages are being मुक्तd that will coalesce soon. In हाल,
 * that is happening, add the मुक्त page to the tail of the list
 * so it's less likely to be used soon and more likely to be merged
 * as a higher order page
 */
अटल अंतरभूत bool
buddy_merge_likely(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ buddy_pfn,
		   काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	काष्ठा page *higher_page, *higher_buddy;
	अचिन्हित दीर्घ combined_pfn;

	अगर (order >= MAX_ORDER - 2)
		वापस false;

	अगर (!pfn_valid_within(buddy_pfn))
		वापस false;

	combined_pfn = buddy_pfn & pfn;
	higher_page = page + (combined_pfn - pfn);
	buddy_pfn = __find_buddy_pfn(combined_pfn, order + 1);
	higher_buddy = higher_page + (buddy_pfn - combined_pfn);

	वापस pfn_valid_within(buddy_pfn) &&
	       page_is_buddy(higher_page, higher_buddy, order + 1);
पूर्ण

/*
 * Freeing function क्रम a buddy प्रणाली allocator.
 *
 * The concept of a buddy प्रणाली is to मुख्यtain direct-mapped table
 * (containing bit values) क्रम memory blocks of various "orders".
 * The bottom level table contains the map क्रम the smallest allocatable
 * units of memory (here, pages), and each level above it describes
 * pairs of units from the levels below, hence, "buddies".
 * At a high level, all that happens here is marking the table entry
 * at the bottom level available, and propagating the changes upward
 * as necessary, plus some accounting needed to play nicely with other
 * parts of the VM प्रणाली.
 * At each level, we keep a list of pages, which are heads of continuous
 * मुक्त pages of length of (1 << order) and marked with PageBuddy.
 * Page's order is recorded in page_निजी(page) field.
 * So when we are allocating or मुक्तing one, we can derive the state of the
 * other.  That is, अगर we allocate a small block, and both were
 * मुक्त, the reमुख्यder of the region must be split पूर्णांकo blocks.
 * If a block is मुक्तd, and its buddy is also मुक्त, then this
 * triggers coalescing पूर्णांकo a block of larger size.
 *
 * -- nyc
 */

अटल अंतरभूत व्योम __मुक्त_one_page(काष्ठा page *page,
		अचिन्हित दीर्घ pfn,
		काष्ठा zone *zone, अचिन्हित पूर्णांक order,
		पूर्णांक migratetype, fpi_t fpi_flags)
अणु
	काष्ठा capture_control *capc = task_capc(zone);
	अचिन्हित दीर्घ buddy_pfn;
	अचिन्हित दीर्घ combined_pfn;
	अचिन्हित पूर्णांक max_order;
	काष्ठा page *buddy;
	bool to_tail;

	max_order = min_t(अचिन्हित पूर्णांक, MAX_ORDER - 1, pageblock_order);

	VM_BUG_ON(!zone_is_initialized(zone));
	VM_BUG_ON_PAGE(page->flags & PAGE_FLAGS_CHECK_AT_PREP, page);

	VM_BUG_ON(migratetype == -1);
	अगर (likely(!is_migrate_isolate(migratetype)))
		__mod_zone_मुक्तpage_state(zone, 1 << order, migratetype);

	VM_BUG_ON_PAGE(pfn & ((1 << order) - 1), page);
	VM_BUG_ON_PAGE(bad_range(zone, page), page);

जारी_merging:
	जबतक (order < max_order) अणु
		अगर (compaction_capture(capc, page, order, migratetype)) अणु
			__mod_zone_मुक्तpage_state(zone, -(1 << order),
								migratetype);
			वापस;
		पूर्ण
		buddy_pfn = __find_buddy_pfn(pfn, order);
		buddy = page + (buddy_pfn - pfn);

		अगर (!pfn_valid_within(buddy_pfn))
			जाओ करोne_merging;
		अगर (!page_is_buddy(page, buddy, order))
			जाओ करोne_merging;
		/*
		 * Our buddy is मुक्त or it is CONFIG_DEBUG_PAGEALLOC guard page,
		 * merge with it and move up one order.
		 */
		अगर (page_is_guard(buddy))
			clear_page_guard(zone, buddy, order, migratetype);
		अन्यथा
			del_page_from_मुक्त_list(buddy, zone, order);
		combined_pfn = buddy_pfn & pfn;
		page = page + (combined_pfn - pfn);
		pfn = combined_pfn;
		order++;
	पूर्ण
	अगर (order < MAX_ORDER - 1) अणु
		/* If we are here, it means order is >= pageblock_order.
		 * We want to prevent merge between मुक्तpages on isolate
		 * pageblock and normal pageblock. Without this, pageblock
		 * isolation could cause incorrect मुक्तpage or CMA accounting.
		 *
		 * We करोn't want to hit this code क्रम the more frequent
		 * low-order merging.
		 */
		अगर (unlikely(has_isolate_pageblock(zone))) अणु
			पूर्णांक buddy_mt;

			buddy_pfn = __find_buddy_pfn(pfn, order);
			buddy = page + (buddy_pfn - pfn);
			buddy_mt = get_pageblock_migratetype(buddy);

			अगर (migratetype != buddy_mt
					&& (is_migrate_isolate(migratetype) ||
						is_migrate_isolate(buddy_mt)))
				जाओ करोne_merging;
		पूर्ण
		max_order = order + 1;
		जाओ जारी_merging;
	पूर्ण

करोne_merging:
	set_buddy_order(page, order);

	अगर (fpi_flags & FPI_TO_TAIL)
		to_tail = true;
	अन्यथा अगर (is_shuffle_order(order))
		to_tail = shuffle_pick_tail();
	अन्यथा
		to_tail = buddy_merge_likely(pfn, buddy_pfn, page, order);

	अगर (to_tail)
		add_to_मुक्त_list_tail(page, zone, order, migratetype);
	अन्यथा
		add_to_मुक्त_list(page, zone, order, migratetype);

	/* Notअगरy page reporting subप्रणाली of मुक्तd page */
	अगर (!(fpi_flags & FPI_SKIP_REPORT_NOTIFY))
		page_reporting_notअगरy_मुक्त(order);
पूर्ण

/*
 * A bad page could be due to a number of fields. Instead of multiple branches,
 * try and check multiple fields with one check. The caller must करो a detailed
 * check अगर necessary.
 */
अटल अंतरभूत bool page_expected_state(काष्ठा page *page,
					अचिन्हित दीर्घ check_flags)
अणु
	अगर (unlikely(atomic_पढ़ो(&page->_mapcount) != -1))
		वापस false;

	अगर (unlikely((अचिन्हित दीर्घ)page->mapping |
			page_ref_count(page) |
#अगर_घोषित CONFIG_MEMCG
			page->memcg_data |
#पूर्ण_अगर
			(page->flags & check_flags)))
		वापस false;

	वापस true;
पूर्ण

अटल स्थिर अक्षर *page_bad_reason(काष्ठा page *page, अचिन्हित दीर्घ flags)
अणु
	स्थिर अक्षर *bad_reason = शून्य;

	अगर (unlikely(atomic_पढ़ो(&page->_mapcount) != -1))
		bad_reason = "nonzero mapcount";
	अगर (unlikely(page->mapping != शून्य))
		bad_reason = "non-NULL mapping";
	अगर (unlikely(page_ref_count(page) != 0))
		bad_reason = "nonzero _refcount";
	अगर (unlikely(page->flags & flags)) अणु
		अगर (flags == PAGE_FLAGS_CHECK_AT_PREP)
			bad_reason = "PAGE_FLAGS_CHECK_AT_PREP flag(s) set";
		अन्यथा
			bad_reason = "PAGE_FLAGS_CHECK_AT_FREE flag(s) set";
	पूर्ण
#अगर_घोषित CONFIG_MEMCG
	अगर (unlikely(page->memcg_data))
		bad_reason = "page still charged to cgroup";
#पूर्ण_अगर
	वापस bad_reason;
पूर्ण

अटल व्योम check_मुक्त_page_bad(काष्ठा page *page)
अणु
	bad_page(page,
		 page_bad_reason(page, PAGE_FLAGS_CHECK_AT_FREE));
पूर्ण

अटल अंतरभूत पूर्णांक check_मुक्त_page(काष्ठा page *page)
अणु
	अगर (likely(page_expected_state(page, PAGE_FLAGS_CHECK_AT_FREE)))
		वापस 0;

	/* Something has gone sideways, find it */
	check_मुक्त_page_bad(page);
	वापस 1;
पूर्ण

अटल पूर्णांक मुक्त_tail_pages_check(काष्ठा page *head_page, काष्ठा page *page)
अणु
	पूर्णांक ret = 1;

	/*
	 * We rely page->lru.next never has bit 0 set, unless the page
	 * is PageTail(). Let's make sure that's true even क्रम poisoned ->lru.
	 */
	BUILD_BUG_ON((अचिन्हित दीर्घ)LIST_POISON1 & 1);

	अगर (!IS_ENABLED(CONFIG_DEBUG_VM)) अणु
		ret = 0;
		जाओ out;
	पूर्ण
	चयन (page - head_page) अणु
	हाल 1:
		/* the first tail page: ->mapping may be compound_mapcount() */
		अगर (unlikely(compound_mapcount(page))) अणु
			bad_page(page, "nonzero compound_mapcount");
			जाओ out;
		पूर्ण
		अवरोध;
	हाल 2:
		/*
		 * the second tail page: ->mapping is
		 * deferred_list.next -- ignore value.
		 */
		अवरोध;
	शेष:
		अगर (page->mapping != TAIL_MAPPING) अणु
			bad_page(page, "corrupted mapping in tail page");
			जाओ out;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (unlikely(!PageTail(page))) अणु
		bad_page(page, "PageTail not set");
		जाओ out;
	पूर्ण
	अगर (unlikely(compound_head(page) != head_page)) अणु
		bad_page(page, "compound_head not consistent");
		जाओ out;
	पूर्ण
	ret = 0;
out:
	page->mapping = शून्य;
	clear_compound_head(page);
	वापस ret;
पूर्ण

अटल व्योम kernel_init_मुक्त_pages(काष्ठा page *page, पूर्णांक numpages)
अणु
	पूर्णांक i;

	/* s390's use of स_रखो() could override KASAN redzones. */
	kasan_disable_current();
	क्रम (i = 0; i < numpages; i++) अणु
		u8 tag = page_kasan_tag(page + i);
		page_kasan_tag_reset(page + i);
		clear_highpage(page + i);
		page_kasan_tag_set(page + i, tag);
	पूर्ण
	kasan_enable_current();
पूर्ण

अटल __always_अंतरभूत bool मुक्त_pages_prepare(काष्ठा page *page,
			अचिन्हित पूर्णांक order, bool check_मुक्त, fpi_t fpi_flags)
अणु
	पूर्णांक bad = 0;
	bool init;

	VM_BUG_ON_PAGE(PageTail(page), page);

	trace_mm_page_मुक्त(page, order);

	अगर (unlikely(PageHWPoison(page)) && !order) अणु
		/*
		 * Do not let hwpoison pages hit pcplists/buddy
		 * Untie memcg state and reset page's owner
		 */
		अगर (memcg_kmem_enabled() && PageMemcgKmem(page))
			__memcg_kmem_unअक्षरge_page(page, order);
		reset_page_owner(page, order);
		वापस false;
	पूर्ण

	/*
	 * Check tail pages beक्रमe head page inक्रमmation is cleared to
	 * aव्योम checking PageCompound क्रम order-0 pages.
	 */
	अगर (unlikely(order)) अणु
		bool compound = PageCompound(page);
		पूर्णांक i;

		VM_BUG_ON_PAGE(compound && compound_order(page) != order, page);

		अगर (compound)
			ClearPageDoubleMap(page);
		क्रम (i = 1; i < (1 << order); i++) अणु
			अगर (compound)
				bad += मुक्त_tail_pages_check(page, page + i);
			अगर (unlikely(check_मुक्त_page(page + i))) अणु
				bad++;
				जारी;
			पूर्ण
			(page + i)->flags &= ~PAGE_FLAGS_CHECK_AT_PREP;
		पूर्ण
	पूर्ण
	अगर (PageMappingFlags(page))
		page->mapping = शून्य;
	अगर (memcg_kmem_enabled() && PageMemcgKmem(page))
		__memcg_kmem_unअक्षरge_page(page, order);
	अगर (check_मुक्त)
		bad += check_मुक्त_page(page);
	अगर (bad)
		वापस false;

	page_cpupid_reset_last(page);
	page->flags &= ~PAGE_FLAGS_CHECK_AT_PREP;
	reset_page_owner(page, order);

	अगर (!PageHighMem(page)) अणु
		debug_check_no_locks_मुक्तd(page_address(page),
					   PAGE_SIZE << order);
		debug_check_no_obj_मुक्तd(page_address(page),
					   PAGE_SIZE << order);
	पूर्ण

	kernel_poison_pages(page, 1 << order);

	/*
	 * As memory initialization might be पूर्णांकegrated पूर्णांकo KASAN,
	 * kasan_मुक्त_pages and kernel_init_मुक्त_pages must be
	 * kept together to aव्योम discrepancies in behavior.
	 *
	 * With hardware tag-based KASAN, memory tags must be set beक्रमe the
	 * page becomes unavailable via debug_pagealloc or arch_मुक्त_page.
	 */
	init = want_init_on_मुक्त();
	अगर (init && !kasan_has_पूर्णांकegrated_init())
		kernel_init_मुक्त_pages(page, 1 << order);
	kasan_मुक्त_nondeferred_pages(page, order, init, fpi_flags);

	/*
	 * arch_मुक्त_page() can make the page's contents inaccessible.  s390
	 * करोes this.  So nothing which can access the page's contents should
	 * happen after this.
	 */
	arch_मुक्त_page(page, order);

	debug_pagealloc_unmap_pages(page, 1 << order);

	वापस true;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_VM
/*
 * With DEBUG_VM enabled, order-0 pages are checked immediately when being मुक्तd
 * to pcp lists. With debug_pagealloc also enabled, they are also rechecked when
 * moved from pcp lists to मुक्त lists.
 */
अटल bool मुक्त_pcp_prepare(काष्ठा page *page)
अणु
	वापस मुक्त_pages_prepare(page, 0, true, FPI_NONE);
पूर्ण

अटल bool bulkमुक्त_pcp_prepare(काष्ठा page *page)
अणु
	अगर (debug_pagealloc_enabled_अटल())
		वापस check_मुक्त_page(page);
	अन्यथा
		वापस false;
पूर्ण
#अन्यथा
/*
 * With DEBUG_VM disabled, order-0 pages being मुक्तd are checked only when
 * moving from pcp lists to मुक्त list in order to reduce overhead. With
 * debug_pagealloc enabled, they are checked also immediately when being मुक्तd
 * to the pcp lists.
 */
अटल bool मुक्त_pcp_prepare(काष्ठा page *page)
अणु
	अगर (debug_pagealloc_enabled_अटल())
		वापस मुक्त_pages_prepare(page, 0, true, FPI_NONE);
	अन्यथा
		वापस मुक्त_pages_prepare(page, 0, false, FPI_NONE);
पूर्ण

अटल bool bulkमुक्त_pcp_prepare(काष्ठा page *page)
अणु
	वापस check_मुक्त_page(page);
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_VM */

अटल अंतरभूत व्योम prefetch_buddy(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ pfn = page_to_pfn(page);
	अचिन्हित दीर्घ buddy_pfn = __find_buddy_pfn(pfn, 0);
	काष्ठा page *buddy = page + (buddy_pfn - pfn);

	prefetch(buddy);
पूर्ण

/*
 * Frees a number of pages from the PCP lists
 * Assumes all pages on list are in same zone, and of same order.
 * count is the number of pages to मुक्त.
 *
 * If the zone was previously in an "all pages pinned" state then look to
 * see अगर this मुक्तing clears that state.
 *
 * And clear the zone's pages_scanned counter, to hold off the "all pages are
 * pinned" detection logic.
 */
अटल व्योम मुक्त_pcppages_bulk(काष्ठा zone *zone, पूर्णांक count,
					काष्ठा per_cpu_pages *pcp)
अणु
	पूर्णांक migratetype = 0;
	पूर्णांक batch_मुक्त = 0;
	पूर्णांक prefetch_nr = READ_ONCE(pcp->batch);
	bool isolated_pageblocks;
	काष्ठा page *page, *पंचांगp;
	LIST_HEAD(head);

	/*
	 * Ensure proper count is passed which otherwise would stuck in the
	 * below जबतक (list_empty(list)) loop.
	 */
	count = min(pcp->count, count);
	जबतक (count) अणु
		काष्ठा list_head *list;

		/*
		 * Remove pages from lists in a round-robin fashion. A
		 * batch_मुक्त count is मुख्यtained that is incremented when an
		 * empty list is encountered.  This is so more pages are मुक्तd
		 * off fuller lists instead of spinning excessively around empty
		 * lists
		 */
		करो अणु
			batch_मुक्त++;
			अगर (++migratetype == MIGRATE_PCPTYPES)
				migratetype = 0;
			list = &pcp->lists[migratetype];
		पूर्ण जबतक (list_empty(list));

		/* This is the only non-empty list. Free them all. */
		अगर (batch_मुक्त == MIGRATE_PCPTYPES)
			batch_मुक्त = count;

		करो अणु
			page = list_last_entry(list, काष्ठा page, lru);
			/* must delete to aव्योम corrupting pcp list */
			list_del(&page->lru);
			pcp->count--;

			अगर (bulkमुक्त_pcp_prepare(page))
				जारी;

			list_add_tail(&page->lru, &head);

			/*
			 * We are going to put the page back to the global
			 * pool, prefetch its buddy to speed up later access
			 * under zone->lock. It is believed the overhead of
			 * an additional test and calculating buddy_pfn here
			 * can be offset by reduced memory latency later. To
			 * aव्योम excessive prefetching due to large count, only
			 * prefetch buddy क्रम the first pcp->batch nr of pages.
			 */
			अगर (prefetch_nr) अणु
				prefetch_buddy(page);
				prefetch_nr--;
			पूर्ण
		पूर्ण जबतक (--count && --batch_मुक्त && !list_empty(list));
	पूर्ण

	spin_lock(&zone->lock);
	isolated_pageblocks = has_isolate_pageblock(zone);

	/*
	 * Use safe version since after __मुक्त_one_page(),
	 * page->lru.next will not poपूर्णांक to original list.
	 */
	list_क्रम_each_entry_safe(page, पंचांगp, &head, lru) अणु
		पूर्णांक mt = get_pcppage_migratetype(page);
		/* MIGRATE_ISOLATE page should not go to pcplists */
		VM_BUG_ON_PAGE(is_migrate_isolate(mt), page);
		/* Pageblock could have been isolated meanजबतक */
		अगर (unlikely(isolated_pageblocks))
			mt = get_pageblock_migratetype(page);

		__मुक्त_one_page(page, page_to_pfn(page), zone, 0, mt, FPI_NONE);
		trace_mm_page_pcpu_drain(page, 0, mt);
	पूर्ण
	spin_unlock(&zone->lock);
पूर्ण

अटल व्योम मुक्त_one_page(काष्ठा zone *zone,
				काष्ठा page *page, अचिन्हित दीर्घ pfn,
				अचिन्हित पूर्णांक order,
				पूर्णांक migratetype, fpi_t fpi_flags)
अणु
	spin_lock(&zone->lock);
	अगर (unlikely(has_isolate_pageblock(zone) ||
		is_migrate_isolate(migratetype))) अणु
		migratetype = get_pfnblock_migratetype(page, pfn);
	पूर्ण
	__मुक्त_one_page(page, pfn, zone, order, migratetype, fpi_flags);
	spin_unlock(&zone->lock);
पूर्ण

अटल व्योम __meminit __init_single_page(काष्ठा page *page, अचिन्हित दीर्घ pfn,
				अचिन्हित दीर्घ zone, पूर्णांक nid)
अणु
	mm_zero_काष्ठा_page(page);
	set_page_links(page, zone, nid, pfn);
	init_page_count(page);
	page_mapcount_reset(page);
	page_cpupid_reset_last(page);
	page_kasan_tag_reset(page);

	INIT_LIST_HEAD(&page->lru);
#अगर_घोषित WANT_PAGE_VIRTUAL
	/* The shअगरt won't overflow because ZONE_NORMAL is below 4G. */
	अगर (!is_highmem_idx(zone))
		set_page_address(page, __va(pfn << PAGE_SHIFT));
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_DEFERRED_STRUCT_PAGE_INIT
अटल व्योम __meminit init_reserved_page(अचिन्हित दीर्घ pfn)
अणु
	pg_data_t *pgdat;
	पूर्णांक nid, zid;

	अगर (!early_page_uninitialised(pfn))
		वापस;

	nid = early_pfn_to_nid(pfn);
	pgdat = NODE_DATA(nid);

	क्रम (zid = 0; zid < MAX_NR_ZONES; zid++) अणु
		काष्ठा zone *zone = &pgdat->node_zones[zid];

		अगर (pfn >= zone->zone_start_pfn && pfn < zone_end_pfn(zone))
			अवरोध;
	पूर्ण
	__init_single_page(pfn_to_page(pfn), pfn, zid, nid);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम init_reserved_page(अचिन्हित दीर्घ pfn)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DEFERRED_STRUCT_PAGE_INIT */

/*
 * Initialised pages करो not have PageReserved set. This function is
 * called क्रम each range allocated by the booपंचांगem allocator and
 * marks the pages PageReserved. The reमुख्यing valid pages are later
 * sent to the buddy page allocator.
 */
व्योम __meminit reserve_booपंचांगem_region(phys_addr_t start, phys_addr_t end)
अणु
	अचिन्हित दीर्घ start_pfn = PFN_DOWN(start);
	अचिन्हित दीर्घ end_pfn = PFN_UP(end);

	क्रम (; start_pfn < end_pfn; start_pfn++) अणु
		अगर (pfn_valid(start_pfn)) अणु
			काष्ठा page *page = pfn_to_page(start_pfn);

			init_reserved_page(start_pfn);

			/* Aव्योम false-positive PageTail() */
			INIT_LIST_HEAD(&page->lru);

			/*
			 * no need क्रम atomic set_bit because the काष्ठा
			 * page is not visible yet so nobody should
			 * access it yet.
			 */
			__SetPageReserved(page);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __मुक्त_pages_ok(काष्ठा page *page, अचिन्हित पूर्णांक order,
			    fpi_t fpi_flags)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक migratetype;
	अचिन्हित दीर्घ pfn = page_to_pfn(page);

	अगर (!मुक्त_pages_prepare(page, order, true, fpi_flags))
		वापस;

	migratetype = get_pfnblock_migratetype(page, pfn);
	local_irq_save(flags);
	__count_vm_events(PGFREE, 1 << order);
	मुक्त_one_page(page_zone(page), page, pfn, order, migratetype,
		      fpi_flags);
	local_irq_restore(flags);
पूर्ण

व्योम __मुक्त_pages_core(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	अचिन्हित पूर्णांक nr_pages = 1 << order;
	काष्ठा page *p = page;
	अचिन्हित पूर्णांक loop;

	/*
	 * When initializing the memmap, __init_single_page() sets the refcount
	 * of all pages to 1 ("allocated"/"not free"). We have to set the
	 * refcount of all involved pages to 0.
	 */
	prefetchw(p);
	क्रम (loop = 0; loop < (nr_pages - 1); loop++, p++) अणु
		prefetchw(p + 1);
		__ClearPageReserved(p);
		set_page_count(p, 0);
	पूर्ण
	__ClearPageReserved(p);
	set_page_count(p, 0);

	atomic_दीर्घ_add(nr_pages, &page_zone(page)->managed_pages);

	/*
	 * Bypass PCP and place fresh pages right to the tail, primarily
	 * relevant क्रम memory onlining.
	 */
	__मुक्त_pages_ok(page, order, FPI_TO_TAIL | FPI_SKIP_KASAN_POISON);
पूर्ण

#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES

/*
 * During memory init memblocks map pfns to nids. The search is expensive and
 * this caches recent lookups. The implementation of __early_pfn_to_nid
 * treats start/end as pfns.
 */
काष्ठा mminit_pfnnid_cache अणु
	अचिन्हित दीर्घ last_start;
	अचिन्हित दीर्घ last_end;
	पूर्णांक last_nid;
पूर्ण;

अटल काष्ठा mminit_pfnnid_cache early_pfnnid_cache __meminitdata;

/*
 * Required by SPARSEMEM. Given a PFN, वापस what node the PFN is on.
 */
अटल पूर्णांक __meminit __early_pfn_to_nid(अचिन्हित दीर्घ pfn,
					काष्ठा mminit_pfnnid_cache *state)
अणु
	अचिन्हित दीर्घ start_pfn, end_pfn;
	पूर्णांक nid;

	अगर (state->last_start <= pfn && pfn < state->last_end)
		वापस state->last_nid;

	nid = memblock_search_pfn_nid(pfn, &start_pfn, &end_pfn);
	अगर (nid != NUMA_NO_NODE) अणु
		state->last_start = start_pfn;
		state->last_end = end_pfn;
		state->last_nid = nid;
	पूर्ण

	वापस nid;
पूर्ण

पूर्णांक __meminit early_pfn_to_nid(अचिन्हित दीर्घ pfn)
अणु
	अटल DEFINE_SPINLOCK(early_pfn_lock);
	पूर्णांक nid;

	spin_lock(&early_pfn_lock);
	nid = __early_pfn_to_nid(pfn, &early_pfnnid_cache);
	अगर (nid < 0)
		nid = first_online_node;
	spin_unlock(&early_pfn_lock);

	वापस nid;
पूर्ण
#पूर्ण_अगर /* CONFIG_NEED_MULTIPLE_NODES */

व्योम __init memblock_मुक्त_pages(काष्ठा page *page, अचिन्हित दीर्घ pfn,
							अचिन्हित पूर्णांक order)
अणु
	अगर (early_page_uninitialised(pfn))
		वापस;
	__मुक्त_pages_core(page, order);
पूर्ण

/*
 * Check that the whole (or subset of) a pageblock given by the पूर्णांकerval of
 * [start_pfn, end_pfn) is valid and within the same zone, beक्रमe scanning it
 * with the migration of मुक्त compaction scanner. The scanners then need to
 * use only pfn_valid_within() check क्रम arches that allow holes within
 * pageblocks.
 *
 * Return काष्ठा page poपूर्णांकer of start_pfn, or शून्य अगर checks were not passed.
 *
 * It's possible on some configurations to have a setup like node0 node1 node0
 * i.e. it's possible that all pages within a zones range of pages करो not
 * beदीर्घ to a single zone. We assume that a border between node0 and node1
 * can occur within a single pageblock, but not a node0 node1 node0
 * पूर्णांकerleaving within a single pageblock. It is thereक्रमe sufficient to check
 * the first and last page of a pageblock and aव्योम checking each inभागidual
 * page in a pageblock.
 */
काष्ठा page *__pageblock_pfn_to_page(अचिन्हित दीर्घ start_pfn,
				     अचिन्हित दीर्घ end_pfn, काष्ठा zone *zone)
अणु
	काष्ठा page *start_page;
	काष्ठा page *end_page;

	/* end_pfn is one past the range we are checking */
	end_pfn--;

	अगर (!pfn_valid(start_pfn) || !pfn_valid(end_pfn))
		वापस शून्य;

	start_page = pfn_to_online_page(start_pfn);
	अगर (!start_page)
		वापस शून्य;

	अगर (page_zone(start_page) != zone)
		वापस शून्य;

	end_page = pfn_to_page(end_pfn);

	/* This gives a लघुer code than deriving page_zone(end_page) */
	अगर (page_zone_id(start_page) != page_zone_id(end_page))
		वापस शून्य;

	वापस start_page;
पूर्ण

व्योम set_zone_contiguous(काष्ठा zone *zone)
अणु
	अचिन्हित दीर्घ block_start_pfn = zone->zone_start_pfn;
	अचिन्हित दीर्घ block_end_pfn;

	block_end_pfn = ALIGN(block_start_pfn + 1, pageblock_nr_pages);
	क्रम (; block_start_pfn < zone_end_pfn(zone);
			block_start_pfn = block_end_pfn,
			 block_end_pfn += pageblock_nr_pages) अणु

		block_end_pfn = min(block_end_pfn, zone_end_pfn(zone));

		अगर (!__pageblock_pfn_to_page(block_start_pfn,
					     block_end_pfn, zone))
			वापस;
		cond_resched();
	पूर्ण

	/* We confirm that there is no hole */
	zone->contiguous = true;
पूर्ण

व्योम clear_zone_contiguous(काष्ठा zone *zone)
अणु
	zone->contiguous = false;
पूर्ण

#अगर_घोषित CONFIG_DEFERRED_STRUCT_PAGE_INIT
अटल व्योम __init deferred_मुक्त_range(अचिन्हित दीर्घ pfn,
				       अचिन्हित दीर्घ nr_pages)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ i;

	अगर (!nr_pages)
		वापस;

	page = pfn_to_page(pfn);

	/* Free a large naturally-aligned chunk अगर possible */
	अगर (nr_pages == pageblock_nr_pages &&
	    (pfn & (pageblock_nr_pages - 1)) == 0) अणु
		set_pageblock_migratetype(page, MIGRATE_MOVABLE);
		__मुक्त_pages_core(page, pageblock_order);
		वापस;
	पूर्ण

	क्रम (i = 0; i < nr_pages; i++, page++, pfn++) अणु
		अगर ((pfn & (pageblock_nr_pages - 1)) == 0)
			set_pageblock_migratetype(page, MIGRATE_MOVABLE);
		__मुक्त_pages_core(page, 0);
	पूर्ण
पूर्ण

/* Completion tracking क्रम deferred_init_memmap() thपढ़ोs */
अटल atomic_t pgdat_init_n_unकरोne __initdata;
अटल __initdata DECLARE_COMPLETION(pgdat_init_all_करोne_comp);

अटल अंतरभूत व्योम __init pgdat_init_report_one_करोne(व्योम)
अणु
	अगर (atomic_dec_and_test(&pgdat_init_n_unकरोne))
		complete(&pgdat_init_all_करोne_comp);
पूर्ण

/*
 * Returns true अगर page needs to be initialized or मुक्तd to buddy allocator.
 *
 * First we check अगर pfn is valid on architectures where it is possible to have
 * holes within pageblock_nr_pages. On प्रणालीs where it is not possible, this
 * function is optimized out.
 *
 * Then, we check अगर a current large page is valid by only checking the validity
 * of the head pfn.
 */
अटल अंतरभूत bool __init deferred_pfn_valid(अचिन्हित दीर्घ pfn)
अणु
	अगर (!pfn_valid_within(pfn))
		वापस false;
	अगर (!(pfn & (pageblock_nr_pages - 1)) && !pfn_valid(pfn))
		वापस false;
	वापस true;
पूर्ण

/*
 * Free pages to buddy allocator. Try to मुक्त aligned pages in
 * pageblock_nr_pages sizes.
 */
अटल व्योम __init deferred_मुक्त_pages(अचिन्हित दीर्घ pfn,
				       अचिन्हित दीर्घ end_pfn)
अणु
	अचिन्हित दीर्घ nr_pgmask = pageblock_nr_pages - 1;
	अचिन्हित दीर्घ nr_मुक्त = 0;

	क्रम (; pfn < end_pfn; pfn++) अणु
		अगर (!deferred_pfn_valid(pfn)) अणु
			deferred_मुक्त_range(pfn - nr_मुक्त, nr_मुक्त);
			nr_मुक्त = 0;
		पूर्ण अन्यथा अगर (!(pfn & nr_pgmask)) अणु
			deferred_मुक्त_range(pfn - nr_मुक्त, nr_मुक्त);
			nr_मुक्त = 1;
		पूर्ण अन्यथा अणु
			nr_मुक्त++;
		पूर्ण
	पूर्ण
	/* Free the last block of pages to allocator */
	deferred_मुक्त_range(pfn - nr_मुक्त, nr_मुक्त);
पूर्ण

/*
 * Initialize काष्ठा pages.  We minimize pfn page lookups and scheduler checks
 * by perक्रमming it only once every pageblock_nr_pages.
 * Return number of pages initialized.
 */
अटल अचिन्हित दीर्घ  __init deferred_init_pages(काष्ठा zone *zone,
						 अचिन्हित दीर्घ pfn,
						 अचिन्हित दीर्घ end_pfn)
अणु
	अचिन्हित दीर्घ nr_pgmask = pageblock_nr_pages - 1;
	पूर्णांक nid = zone_to_nid(zone);
	अचिन्हित दीर्घ nr_pages = 0;
	पूर्णांक zid = zone_idx(zone);
	काष्ठा page *page = शून्य;

	क्रम (; pfn < end_pfn; pfn++) अणु
		अगर (!deferred_pfn_valid(pfn)) अणु
			page = शून्य;
			जारी;
		पूर्ण अन्यथा अगर (!page || !(pfn & nr_pgmask)) अणु
			page = pfn_to_page(pfn);
		पूर्ण अन्यथा अणु
			page++;
		पूर्ण
		__init_single_page(page, pfn, zid, nid);
		nr_pages++;
	पूर्ण
	वापस (nr_pages);
पूर्ण

/*
 * This function is meant to pre-load the iterator क्रम the zone init.
 * Specअगरically it walks through the ranges until we are caught up to the
 * first_init_pfn value and निकासs there. If we never encounter the value we
 * वापस false indicating there are no valid ranges left.
 */
अटल bool __init
deferred_init_mem_pfn_range_in_zone(u64 *i, काष्ठा zone *zone,
				    अचिन्हित दीर्घ *spfn, अचिन्हित दीर्घ *epfn,
				    अचिन्हित दीर्घ first_init_pfn)
अणु
	u64 j;

	/*
	 * Start out by walking through the ranges in this zone that have
	 * alपढ़ोy been initialized. We करोn't need to करो anything with them
	 * so we just need to flush them out of the प्रणाली.
	 */
	क्रम_each_मुक्त_mem_pfn_range_in_zone(j, zone, spfn, epfn) अणु
		अगर (*epfn <= first_init_pfn)
			जारी;
		अगर (*spfn < first_init_pfn)
			*spfn = first_init_pfn;
		*i = j;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Initialize and मुक्त pages. We करो it in two loops: first we initialize
 * काष्ठा page, then मुक्त to buddy allocator, because जबतक we are
 * मुक्तing pages we can access pages that are ahead (computing buddy
 * page in __मुक्त_one_page()).
 *
 * In order to try and keep some memory in the cache we have the loop
 * broken aदीर्घ max page order boundaries. This way we will not cause
 * any issues with the buddy page computation.
 */
अटल अचिन्हित दीर्घ __init
deferred_init_maxorder(u64 *i, काष्ठा zone *zone, अचिन्हित दीर्घ *start_pfn,
		       अचिन्हित दीर्घ *end_pfn)
अणु
	अचिन्हित दीर्घ mo_pfn = ALIGN(*start_pfn + 1, MAX_ORDER_NR_PAGES);
	अचिन्हित दीर्घ spfn = *start_pfn, epfn = *end_pfn;
	अचिन्हित दीर्घ nr_pages = 0;
	u64 j = *i;

	/* First we loop through and initialize the page values */
	क्रम_each_मुक्त_mem_pfn_range_in_zone_from(j, zone, start_pfn, end_pfn) अणु
		अचिन्हित दीर्घ t;

		अगर (mo_pfn <= *start_pfn)
			अवरोध;

		t = min(mo_pfn, *end_pfn);
		nr_pages += deferred_init_pages(zone, *start_pfn, t);

		अगर (mo_pfn < *end_pfn) अणु
			*start_pfn = mo_pfn;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Reset values and now loop through मुक्तing pages as needed */
	swap(j, *i);

	क्रम_each_मुक्त_mem_pfn_range_in_zone_from(j, zone, &spfn, &epfn) अणु
		अचिन्हित दीर्घ t;

		अगर (mo_pfn <= spfn)
			अवरोध;

		t = min(mo_pfn, epfn);
		deferred_मुक्त_pages(spfn, t);

		अगर (mo_pfn <= epfn)
			अवरोध;
	पूर्ण

	वापस nr_pages;
पूर्ण

अटल व्योम __init
deferred_init_memmap_chunk(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn,
			   व्योम *arg)
अणु
	अचिन्हित दीर्घ spfn, epfn;
	काष्ठा zone *zone = arg;
	u64 i;

	deferred_init_mem_pfn_range_in_zone(&i, zone, &spfn, &epfn, start_pfn);

	/*
	 * Initialize and मुक्त pages in MAX_ORDER sized increments so that we
	 * can aव्योम पूर्णांकroducing any issues with the buddy allocator.
	 */
	जबतक (spfn < end_pfn) अणु
		deferred_init_maxorder(&i, zone, &spfn, &epfn);
		cond_resched();
	पूर्ण
पूर्ण

/* An arch may override क्रम more concurrency. */
__weak पूर्णांक __init
deferred_page_init_max_thपढ़ोs(स्थिर काष्ठा cpumask *node_cpumask)
अणु
	वापस 1;
पूर्ण

/* Initialise reमुख्यing memory on a node */
अटल पूर्णांक __init deferred_init_memmap(व्योम *data)
अणु
	pg_data_t *pgdat = data;
	स्थिर काष्ठा cpumask *cpumask = cpumask_of_node(pgdat->node_id);
	अचिन्हित दीर्घ spfn = 0, epfn = 0;
	अचिन्हित दीर्घ first_init_pfn, flags;
	अचिन्हित दीर्घ start = jअगरfies;
	काष्ठा zone *zone;
	पूर्णांक zid, max_thपढ़ोs;
	u64 i;

	/* Bind memory initialisation thपढ़ो to a local node अगर possible */
	अगर (!cpumask_empty(cpumask))
		set_cpus_allowed_ptr(current, cpumask);

	pgdat_resize_lock(pgdat, &flags);
	first_init_pfn = pgdat->first_deferred_pfn;
	अगर (first_init_pfn == अच_दीर्घ_उच्च) अणु
		pgdat_resize_unlock(pgdat, &flags);
		pgdat_init_report_one_करोne();
		वापस 0;
	पूर्ण

	/* Sanity check boundaries */
	BUG_ON(pgdat->first_deferred_pfn < pgdat->node_start_pfn);
	BUG_ON(pgdat->first_deferred_pfn > pgdat_end_pfn(pgdat));
	pgdat->first_deferred_pfn = अच_दीर्घ_उच्च;

	/*
	 * Once we unlock here, the zone cannot be grown anymore, thus अगर an
	 * पूर्णांकerrupt thपढ़ो must allocate this early in boot, zone must be
	 * pre-grown prior to start of deferred page initialization.
	 */
	pgdat_resize_unlock(pgdat, &flags);

	/* Only the highest zone is deferred so find it */
	क्रम (zid = 0; zid < MAX_NR_ZONES; zid++) अणु
		zone = pgdat->node_zones + zid;
		अगर (first_init_pfn < zone_end_pfn(zone))
			अवरोध;
	पूर्ण

	/* If the zone is empty somebody अन्यथा may have cleared out the zone */
	अगर (!deferred_init_mem_pfn_range_in_zone(&i, zone, &spfn, &epfn,
						 first_init_pfn))
		जाओ zone_empty;

	max_thपढ़ोs = deferred_page_init_max_thपढ़ोs(cpumask);

	जबतक (spfn < epfn) अणु
		अचिन्हित दीर्घ epfn_align = ALIGN(epfn, PAGES_PER_SECTION);
		काष्ठा padata_mt_job job = अणु
			.thपढ़ो_fn   = deferred_init_memmap_chunk,
			.fn_arg      = zone,
			.start       = spfn,
			.size        = epfn_align - spfn,
			.align       = PAGES_PER_SECTION,
			.min_chunk   = PAGES_PER_SECTION,
			.max_thपढ़ोs = max_thपढ़ोs,
		पूर्ण;

		padata_करो_multithपढ़ोed(&job);
		deferred_init_mem_pfn_range_in_zone(&i, zone, &spfn, &epfn,
						    epfn_align);
	पूर्ण
zone_empty:
	/* Sanity check that the next zone really is unpopulated */
	WARN_ON(++zid < MAX_NR_ZONES && populated_zone(++zone));

	pr_info("node %d deferred pages initialised in %ums\n",
		pgdat->node_id, jअगरfies_to_msecs(jअगरfies - start));

	pgdat_init_report_one_करोne();
	वापस 0;
पूर्ण

/*
 * If this zone has deferred pages, try to grow it by initializing enough
 * deferred pages to satisfy the allocation specअगरied by order, rounded up to
 * the nearest PAGES_PER_SECTION boundary.  So we're adding memory in increments
 * of SECTION_SIZE bytes by initializing काष्ठा pages in increments of
 * PAGES_PER_SECTION * माप(काष्ठा page) bytes.
 *
 * Return true when zone was grown, otherwise वापस false. We वापस true even
 * when we grow less than requested, to let the caller decide अगर there are
 * enough pages to satisfy the allocation.
 *
 * Note: We use noअंतरभूत because this function is needed only during boot, and
 * it is called from a __ref function _deferred_grow_zone. This way we are
 * making sure that it is not अंतरभूतd पूर्णांकo permanent text section.
 */
अटल noअंतरभूत bool __init
deferred_grow_zone(काष्ठा zone *zone, अचिन्हित पूर्णांक order)
अणु
	अचिन्हित दीर्घ nr_pages_needed = ALIGN(1 << order, PAGES_PER_SECTION);
	pg_data_t *pgdat = zone->zone_pgdat;
	अचिन्हित दीर्घ first_deferred_pfn = pgdat->first_deferred_pfn;
	अचिन्हित दीर्घ spfn, epfn, flags;
	अचिन्हित दीर्घ nr_pages = 0;
	u64 i;

	/* Only the last zone may have deferred pages */
	अगर (zone_end_pfn(zone) != pgdat_end_pfn(pgdat))
		वापस false;

	pgdat_resize_lock(pgdat, &flags);

	/*
	 * If someone grew this zone जबतक we were रुकोing क्रम spinlock, वापस
	 * true, as there might be enough pages alपढ़ोy.
	 */
	अगर (first_deferred_pfn != pgdat->first_deferred_pfn) अणु
		pgdat_resize_unlock(pgdat, &flags);
		वापस true;
	पूर्ण

	/* If the zone is empty somebody अन्यथा may have cleared out the zone */
	अगर (!deferred_init_mem_pfn_range_in_zone(&i, zone, &spfn, &epfn,
						 first_deferred_pfn)) अणु
		pgdat->first_deferred_pfn = अच_दीर्घ_उच्च;
		pgdat_resize_unlock(pgdat, &flags);
		/* Retry only once. */
		वापस first_deferred_pfn != अच_दीर्घ_उच्च;
	पूर्ण

	/*
	 * Initialize and मुक्त pages in MAX_ORDER sized increments so
	 * that we can aव्योम पूर्णांकroducing any issues with the buddy
	 * allocator.
	 */
	जबतक (spfn < epfn) अणु
		/* update our first deferred PFN क्रम this section */
		first_deferred_pfn = spfn;

		nr_pages += deferred_init_maxorder(&i, zone, &spfn, &epfn);
		touch_nmi_watchकरोg();

		/* We should only stop aदीर्घ section boundaries */
		अगर ((first_deferred_pfn ^ spfn) < PAGES_PER_SECTION)
			जारी;

		/* If our quota has been met we can stop here */
		अगर (nr_pages >= nr_pages_needed)
			अवरोध;
	पूर्ण

	pgdat->first_deferred_pfn = spfn;
	pgdat_resize_unlock(pgdat, &flags);

	वापस nr_pages > 0;
पूर्ण

/*
 * deferred_grow_zone() is __init, but it is called from
 * get_page_from_मुक्तlist() during early boot until deferred_pages permanently
 * disables this call. This is why we have refdata wrapper to aव्योम warning,
 * and to ensure that the function body माला_लो unloaded.
 */
अटल bool __ref
_deferred_grow_zone(काष्ठा zone *zone, अचिन्हित पूर्णांक order)
अणु
	वापस deferred_grow_zone(zone, order);
पूर्ण

#पूर्ण_अगर /* CONFIG_DEFERRED_STRUCT_PAGE_INIT */

व्योम __init page_alloc_init_late(व्योम)
अणु
	काष्ठा zone *zone;
	पूर्णांक nid;

#अगर_घोषित CONFIG_DEFERRED_STRUCT_PAGE_INIT

	/* There will be num_node_state(N_MEMORY) thपढ़ोs */
	atomic_set(&pgdat_init_n_unकरोne, num_node_state(N_MEMORY));
	क्रम_each_node_state(nid, N_MEMORY) अणु
		kthपढ़ो_run(deferred_init_memmap, NODE_DATA(nid), "pgdatinit%d", nid);
	पूर्ण

	/* Block until all are initialised */
	रुको_क्रम_completion(&pgdat_init_all_करोne_comp);

	/*
	 * The number of managed pages has changed due to the initialisation
	 * so the pcpu batch and high limits needs to be updated or the limits
	 * will be artअगरicially small.
	 */
	क्रम_each_populated_zone(zone)
		zone_pcp_update(zone);

	/*
	 * We initialized the rest of the deferred pages.  Permanently disable
	 * on-demand काष्ठा page initialization.
	 */
	अटल_branch_disable(&deferred_pages);

	/* Reinit limits that are based on मुक्त pages after the kernel is up */
	files_maxfiles_init();
#पूर्ण_अगर

	buffer_init();

	/* Discard memblock निजी memory */
	memblock_discard();

	क्रम_each_node_state(nid, N_MEMORY)
		shuffle_मुक्त_memory(NODE_DATA(nid));

	क्रम_each_populated_zone(zone)
		set_zone_contiguous(zone);
पूर्ण

#अगर_घोषित CONFIG_CMA
/* Free whole pageblock and set its migration type to MIGRATE_CMA. */
व्योम __init init_cma_reserved_pageblock(काष्ठा page *page)
अणु
	अचिन्हित i = pageblock_nr_pages;
	काष्ठा page *p = page;

	करो अणु
		__ClearPageReserved(p);
		set_page_count(p, 0);
	पूर्ण जबतक (++p, --i);

	set_pageblock_migratetype(page, MIGRATE_CMA);

	अगर (pageblock_order >= MAX_ORDER) अणु
		i = pageblock_nr_pages;
		p = page;
		करो अणु
			set_page_refcounted(p);
			__मुक्त_pages(p, MAX_ORDER - 1);
			p += MAX_ORDER_NR_PAGES;
		पूर्ण जबतक (i -= MAX_ORDER_NR_PAGES);
	पूर्ण अन्यथा अणु
		set_page_refcounted(page);
		__मुक्त_pages(page, pageblock_order);
	पूर्ण

	adjust_managed_page_count(page, pageblock_nr_pages);
	page_zone(page)->cma_pages += pageblock_nr_pages;
पूर्ण
#पूर्ण_अगर

/*
 * The order of subभागision here is critical क्रम the IO subप्रणाली.
 * Please करो not alter this order without good reasons and regression
 * testing. Specअगरically, as large blocks of memory are subभागided,
 * the order in which smaller blocks are delivered depends on the order
 * they're subभागided in this function. This is the primary factor
 * influencing the order in which pages are delivered to the IO
 * subप्रणाली according to empirical testing, and this is also justअगरied
 * by considering the behavior of a buddy प्रणाली containing a single
 * large block of memory acted on by a series of small allocations.
 * This behavior is a critical factor in sglist merging's success.
 *
 * -- nyc
 */
अटल अंतरभूत व्योम expand(काष्ठा zone *zone, काष्ठा page *page,
	पूर्णांक low, पूर्णांक high, पूर्णांक migratetype)
अणु
	अचिन्हित दीर्घ size = 1 << high;

	जबतक (high > low) अणु
		high--;
		size >>= 1;
		VM_BUG_ON_PAGE(bad_range(zone, &page[size]), &page[size]);

		/*
		 * Mark as guard pages (or page), that will allow to
		 * merge back to allocator when buddy will be मुक्तd.
		 * Corresponding page table entries will not be touched,
		 * pages will stay not present in भव address space
		 */
		अगर (set_page_guard(zone, &page[size], high, migratetype))
			जारी;

		add_to_मुक्त_list(&page[size], zone, high, migratetype);
		set_buddy_order(&page[size], high);
	पूर्ण
पूर्ण

अटल व्योम check_new_page_bad(काष्ठा page *page)
अणु
	अगर (unlikely(page->flags & __PG_HWPOISON)) अणु
		/* Don't complain about hwpoisoned pages */
		page_mapcount_reset(page); /* हटाओ PageBuddy */
		वापस;
	पूर्ण

	bad_page(page,
		 page_bad_reason(page, PAGE_FLAGS_CHECK_AT_PREP));
पूर्ण

/*
 * This page is about to be वापसed from the page allocator
 */
अटल अंतरभूत पूर्णांक check_new_page(काष्ठा page *page)
अणु
	अगर (likely(page_expected_state(page,
				PAGE_FLAGS_CHECK_AT_PREP|__PG_HWPOISON)))
		वापस 0;

	check_new_page_bad(page);
	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_VM
/*
 * With DEBUG_VM enabled, order-0 pages are checked क्रम expected state when
 * being allocated from pcp lists. With debug_pagealloc also enabled, they are
 * also checked when pcp lists are refilled from the मुक्त lists.
 */
अटल अंतरभूत bool check_pcp_refill(काष्ठा page *page)
अणु
	अगर (debug_pagealloc_enabled_अटल())
		वापस check_new_page(page);
	अन्यथा
		वापस false;
पूर्ण

अटल अंतरभूत bool check_new_pcp(काष्ठा page *page)
अणु
	वापस check_new_page(page);
पूर्ण
#अन्यथा
/*
 * With DEBUG_VM disabled, मुक्त order-0 pages are checked क्रम expected state
 * when pcp lists are being refilled from the मुक्त lists. With debug_pagealloc
 * enabled, they are also checked when being allocated from the pcp lists.
 */
अटल अंतरभूत bool check_pcp_refill(काष्ठा page *page)
अणु
	वापस check_new_page(page);
पूर्ण
अटल अंतरभूत bool check_new_pcp(काष्ठा page *page)
अणु
	अगर (debug_pagealloc_enabled_अटल())
		वापस check_new_page(page);
	अन्यथा
		वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_VM */

अटल bool check_new_pages(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < (1 << order); i++) अणु
		काष्ठा page *p = page + i;

		अगर (unlikely(check_new_page(p)))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अंतरभूत व्योम post_alloc_hook(काष्ठा page *page, अचिन्हित पूर्णांक order,
				gfp_t gfp_flags)
अणु
	bool init;

	set_page_निजी(page, 0);
	set_page_refcounted(page);

	arch_alloc_page(page, order);
	debug_pagealloc_map_pages(page, 1 << order);

	/*
	 * Page unpoisoning must happen beक्रमe memory initialization.
	 * Otherwise, the poison pattern will be overwritten क्रम __GFP_ZERO
	 * allocations and the page unpoisoning code will complain.
	 */
	kernel_unpoison_pages(page, 1 << order);

	/*
	 * As memory initialization might be पूर्णांकegrated पूर्णांकo KASAN,
	 * kasan_alloc_pages and kernel_init_मुक्त_pages must be
	 * kept together to aव्योम discrepancies in behavior.
	 */
	init = !want_init_on_मुक्त() && want_init_on_alloc(gfp_flags);
	kasan_alloc_pages(page, order, init);
	अगर (init && !kasan_has_पूर्णांकegrated_init())
		kernel_init_मुक्त_pages(page, 1 << order);

	set_page_owner(page, order, gfp_flags);
पूर्ण

अटल व्योम prep_new_page(काष्ठा page *page, अचिन्हित पूर्णांक order, gfp_t gfp_flags,
							अचिन्हित पूर्णांक alloc_flags)
अणु
	post_alloc_hook(page, order, gfp_flags);

	अगर (order && (gfp_flags & __GFP_COMP))
		prep_compound_page(page, order);

	/*
	 * page is set pfmeदो_स्मृति when ALLOC_NO_WATERMARKS was necessary to
	 * allocate the page. The expectation is that the caller is taking
	 * steps that will मुक्त more memory. The caller should aव्योम the page
	 * being used क्रम !PFMEMALLOC purposes.
	 */
	अगर (alloc_flags & ALLOC_NO_WATERMARKS)
		set_page_pfmeदो_स्मृति(page);
	अन्यथा
		clear_page_pfmeदो_स्मृति(page);
पूर्ण

/*
 * Go through the मुक्त lists क्रम the given migratetype and हटाओ
 * the smallest available page from the मुक्तlists
 */
अटल __always_अंतरभूत
काष्ठा page *__rmqueue_smallest(काष्ठा zone *zone, अचिन्हित पूर्णांक order,
						पूर्णांक migratetype)
अणु
	अचिन्हित पूर्णांक current_order;
	काष्ठा मुक्त_area *area;
	काष्ठा page *page;

	/* Find a page of the appropriate size in the preferred list */
	क्रम (current_order = order; current_order < MAX_ORDER; ++current_order) अणु
		area = &(zone->मुक्त_area[current_order]);
		page = get_page_from_मुक्त_area(area, migratetype);
		अगर (!page)
			जारी;
		del_page_from_मुक्त_list(page, zone, current_order);
		expand(zone, page, order, current_order, migratetype);
		set_pcppage_migratetype(page, migratetype);
		वापस page;
	पूर्ण

	वापस शून्य;
पूर्ण


/*
 * This array describes the order lists are fallen back to when
 * the मुक्त lists क्रम the desirable migrate type are depleted
 */
अटल पूर्णांक fallbacks[MIGRATE_TYPES][3] = अणु
	[MIGRATE_UNMOVABLE]   = अणु MIGRATE_RECLAIMABLE, MIGRATE_MOVABLE,   MIGRATE_TYPES पूर्ण,
	[MIGRATE_MOVABLE]     = अणु MIGRATE_RECLAIMABLE, MIGRATE_UNMOVABLE, MIGRATE_TYPES पूर्ण,
	[MIGRATE_RECLAIMABLE] = अणु MIGRATE_UNMOVABLE,   MIGRATE_MOVABLE,   MIGRATE_TYPES पूर्ण,
#अगर_घोषित CONFIG_CMA
	[MIGRATE_CMA]         = अणु MIGRATE_TYPES पूर्ण, /* Never used */
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEMORY_ISOLATION
	[MIGRATE_ISOLATE]     = अणु MIGRATE_TYPES पूर्ण, /* Never used */
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_CMA
अटल __always_अंतरभूत काष्ठा page *__rmqueue_cma_fallback(काष्ठा zone *zone,
					अचिन्हित पूर्णांक order)
अणु
	वापस __rmqueue_smallest(zone, order, MIGRATE_CMA);
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा page *__rmqueue_cma_fallback(काष्ठा zone *zone,
					अचिन्हित पूर्णांक order) अणु वापस शून्य; पूर्ण
#पूर्ण_अगर

/*
 * Move the मुक्त pages in a range to the मुक्तlist tail of the requested type.
 * Note that start_page and end_pages are not aligned on a pageblock
 * boundary. If alignment is required, use move_मुक्तpages_block()
 */
अटल पूर्णांक move_मुक्तpages(काष्ठा zone *zone,
			  अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn,
			  पूर्णांक migratetype, पूर्णांक *num_movable)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ pfn;
	अचिन्हित पूर्णांक order;
	पूर्णांक pages_moved = 0;

	क्रम (pfn = start_pfn; pfn <= end_pfn;) अणु
		अगर (!pfn_valid_within(pfn)) अणु
			pfn++;
			जारी;
		पूर्ण

		page = pfn_to_page(pfn);
		अगर (!PageBuddy(page)) अणु
			/*
			 * We assume that pages that could be isolated क्रम
			 * migration are movable. But we करोn't actually try
			 * isolating, as that would be expensive.
			 */
			अगर (num_movable &&
					(PageLRU(page) || __PageMovable(page)))
				(*num_movable)++;
			pfn++;
			जारी;
		पूर्ण

		/* Make sure we are not inadvertently changing nodes */
		VM_BUG_ON_PAGE(page_to_nid(page) != zone_to_nid(zone), page);
		VM_BUG_ON_PAGE(page_zone(page) != zone, page);

		order = buddy_order(page);
		move_to_मुक्त_list(page, zone, order, migratetype);
		pfn += 1 << order;
		pages_moved += 1 << order;
	पूर्ण

	वापस pages_moved;
पूर्ण

पूर्णांक move_मुक्तpages_block(काष्ठा zone *zone, काष्ठा page *page,
				पूर्णांक migratetype, पूर्णांक *num_movable)
अणु
	अचिन्हित दीर्घ start_pfn, end_pfn, pfn;

	अगर (num_movable)
		*num_movable = 0;

	pfn = page_to_pfn(page);
	start_pfn = pfn & ~(pageblock_nr_pages - 1);
	end_pfn = start_pfn + pageblock_nr_pages - 1;

	/* Do not cross zone boundaries */
	अगर (!zone_spans_pfn(zone, start_pfn))
		start_pfn = pfn;
	अगर (!zone_spans_pfn(zone, end_pfn))
		वापस 0;

	वापस move_मुक्तpages(zone, start_pfn, end_pfn, migratetype,
								num_movable);
पूर्ण

अटल व्योम change_pageblock_range(काष्ठा page *pageblock_page,
					पूर्णांक start_order, पूर्णांक migratetype)
अणु
	पूर्णांक nr_pageblocks = 1 << (start_order - pageblock_order);

	जबतक (nr_pageblocks--) अणु
		set_pageblock_migratetype(pageblock_page, migratetype);
		pageblock_page += pageblock_nr_pages;
	पूर्ण
पूर्ण

/*
 * When we are falling back to another migratetype during allocation, try to
 * steal extra मुक्त pages from the same pageblocks to satisfy further
 * allocations, instead of polluting multiple pageblocks.
 *
 * If we are stealing a relatively large buddy page, it is likely there will
 * be more मुक्त pages in the pageblock, so try to steal them all. For
 * reclaimable and unmovable allocations, we steal regardless of page size,
 * as fragmentation caused by those allocations polluting movable pageblocks
 * is worse than movable allocations stealing from unmovable and reclaimable
 * pageblocks.
 */
अटल bool can_steal_fallback(अचिन्हित पूर्णांक order, पूर्णांक start_mt)
अणु
	/*
	 * Leaving this order check is पूर्णांकended, although there is
	 * relaxed order check in next check. The reason is that
	 * we can actually steal whole pageblock अगर this condition met,
	 * but, below check करोesn't guarantee it and that is just heuristic
	 * so could be changed anyसमय.
	 */
	अगर (order >= pageblock_order)
		वापस true;

	अगर (order >= pageblock_order / 2 ||
		start_mt == MIGRATE_RECLAIMABLE ||
		start_mt == MIGRATE_UNMOVABLE ||
		page_group_by_mobility_disabled)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool boost_watermark(काष्ठा zone *zone)
अणु
	अचिन्हित दीर्घ max_boost;

	अगर (!watermark_boost_factor)
		वापस false;
	/*
	 * Don't bother in zones that are unlikely to produce results.
	 * On small machines, including kdump capture kernels running
	 * in a small area, boosting the watermark can cause an out of
	 * memory situation immediately.
	 */
	अगर ((pageblock_nr_pages * 4) > zone_managed_pages(zone))
		वापस false;

	max_boost = mult_frac(zone->_watermark[WMARK_HIGH],
			watermark_boost_factor, 10000);

	/*
	 * high watermark may be uninitialised अगर fragmentation occurs
	 * very early in boot so करो not boost. We करो not fall
	 * through and boost by pageblock_nr_pages as failing
	 * allocations that early means that reclaim is not going
	 * to help and it may even be impossible to reclaim the
	 * boosted watermark resulting in a hang.
	 */
	अगर (!max_boost)
		वापस false;

	max_boost = max(pageblock_nr_pages, max_boost);

	zone->watermark_boost = min(zone->watermark_boost + pageblock_nr_pages,
		max_boost);

	वापस true;
पूर्ण

/*
 * This function implements actual steal behaviour. If order is large enough,
 * we can steal whole pageblock. If not, we first move मुक्तpages in this
 * pageblock to our migratetype and determine how many alपढ़ोy-allocated pages
 * are there in the pageblock with a compatible migratetype. If at least half
 * of pages are मुक्त or compatible, we can change migratetype of the pageblock
 * itself, so pages मुक्तd in the future will be put on the correct मुक्त list.
 */
अटल व्योम steal_suitable_fallback(काष्ठा zone *zone, काष्ठा page *page,
		अचिन्हित पूर्णांक alloc_flags, पूर्णांक start_type, bool whole_block)
अणु
	अचिन्हित पूर्णांक current_order = buddy_order(page);
	पूर्णांक मुक्त_pages, movable_pages, alike_pages;
	पूर्णांक old_block_type;

	old_block_type = get_pageblock_migratetype(page);

	/*
	 * This can happen due to races and we want to prevent broken
	 * highatomic accounting.
	 */
	अगर (is_migrate_highatomic(old_block_type))
		जाओ single_page;

	/* Take ownership क्रम orders >= pageblock_order */
	अगर (current_order >= pageblock_order) अणु
		change_pageblock_range(page, current_order, start_type);
		जाओ single_page;
	पूर्ण

	/*
	 * Boost watermarks to increase reclaim pressure to reduce the
	 * likelihood of future fallbacks. Wake kswapd now as the node
	 * may be balanced overall and kswapd will not wake naturally.
	 */
	अगर (boost_watermark(zone) && (alloc_flags & ALLOC_KSWAPD))
		set_bit(ZONE_BOOSTED_WATERMARK, &zone->flags);

	/* We are not allowed to try stealing from the whole block */
	अगर (!whole_block)
		जाओ single_page;

	मुक्त_pages = move_मुक्तpages_block(zone, page, start_type,
						&movable_pages);
	/*
	 * Determine how many pages are compatible with our allocation.
	 * For movable allocation, it's the number of movable pages which
	 * we just obtained. For other types it's a bit more tricky.
	 */
	अगर (start_type == MIGRATE_MOVABLE) अणु
		alike_pages = movable_pages;
	पूर्ण अन्यथा अणु
		/*
		 * If we are falling back a RECLAIMABLE or UNMOVABLE allocation
		 * to MOVABLE pageblock, consider all non-movable pages as
		 * compatible. If it's UNMOVABLE falling back to RECLAIMABLE or
		 * vice versa, be conservative since we can't distinguish the
		 * exact migratetype of non-movable pages.
		 */
		अगर (old_block_type == MIGRATE_MOVABLE)
			alike_pages = pageblock_nr_pages
						- (मुक्त_pages + movable_pages);
		अन्यथा
			alike_pages = 0;
	पूर्ण

	/* moving whole block can fail due to zone boundary conditions */
	अगर (!मुक्त_pages)
		जाओ single_page;

	/*
	 * If a sufficient number of pages in the block are either मुक्त or of
	 * comparable migratability as our allocation, claim the whole block.
	 */
	अगर (मुक्त_pages + alike_pages >= (1 << (pageblock_order-1)) ||
			page_group_by_mobility_disabled)
		set_pageblock_migratetype(page, start_type);

	वापस;

single_page:
	move_to_मुक्त_list(page, zone, current_order, start_type);
पूर्ण

/*
 * Check whether there is a suitable fallback मुक्तpage with requested order.
 * If only_stealable is true, this function वापसs fallback_mt only अगर
 * we can steal other मुक्तpages all together. This would help to reduce
 * fragmentation due to mixed migratetype pages in one pageblock.
 */
पूर्णांक find_suitable_fallback(काष्ठा मुक्त_area *area, अचिन्हित पूर्णांक order,
			पूर्णांक migratetype, bool only_stealable, bool *can_steal)
अणु
	पूर्णांक i;
	पूर्णांक fallback_mt;

	अगर (area->nr_मुक्त == 0)
		वापस -1;

	*can_steal = false;
	क्रम (i = 0;; i++) अणु
		fallback_mt = fallbacks[migratetype][i];
		अगर (fallback_mt == MIGRATE_TYPES)
			अवरोध;

		अगर (मुक्त_area_empty(area, fallback_mt))
			जारी;

		अगर (can_steal_fallback(order, migratetype))
			*can_steal = true;

		अगर (!only_stealable)
			वापस fallback_mt;

		अगर (*can_steal)
			वापस fallback_mt;
	पूर्ण

	वापस -1;
पूर्ण

/*
 * Reserve a pageblock क्रम exclusive use of high-order atomic allocations अगर
 * there are no empty page blocks that contain a page with a suitable order
 */
अटल व्योम reserve_highatomic_pageblock(काष्ठा page *page, काष्ठा zone *zone,
				अचिन्हित पूर्णांक alloc_order)
अणु
	पूर्णांक mt;
	अचिन्हित दीर्घ max_managed, flags;

	/*
	 * Limit the number reserved to 1 pageblock or roughly 1% of a zone.
	 * Check is race-prone but harmless.
	 */
	max_managed = (zone_managed_pages(zone) / 100) + pageblock_nr_pages;
	अगर (zone->nr_reserved_highatomic >= max_managed)
		वापस;

	spin_lock_irqsave(&zone->lock, flags);

	/* Recheck the nr_reserved_highatomic limit under the lock */
	अगर (zone->nr_reserved_highatomic >= max_managed)
		जाओ out_unlock;

	/* Yoink! */
	mt = get_pageblock_migratetype(page);
	अगर (!is_migrate_highatomic(mt) && !is_migrate_isolate(mt)
	    && !is_migrate_cma(mt)) अणु
		zone->nr_reserved_highatomic += pageblock_nr_pages;
		set_pageblock_migratetype(page, MIGRATE_HIGHATOMIC);
		move_मुक्तpages_block(zone, page, MIGRATE_HIGHATOMIC, शून्य);
	पूर्ण

out_unlock:
	spin_unlock_irqrestore(&zone->lock, flags);
पूर्ण

/*
 * Used when an allocation is about to fail under memory pressure. This
 * potentially hurts the reliability of high-order allocations when under
 * पूर्णांकense memory pressure but failed atomic allocations should be easier
 * to recover from than an OOM.
 *
 * If @क्रमce is true, try to unreserve a pageblock even though highatomic
 * pageblock is exhausted.
 */
अटल bool unreserve_highatomic_pageblock(स्थिर काष्ठा alloc_context *ac,
						bool क्रमce)
अणु
	काष्ठा zonelist *zonelist = ac->zonelist;
	अचिन्हित दीर्घ flags;
	काष्ठा zoneref *z;
	काष्ठा zone *zone;
	काष्ठा page *page;
	पूर्णांक order;
	bool ret;

	क्रम_each_zone_zonelist_nodemask(zone, z, zonelist, ac->highest_zoneidx,
								ac->nodemask) अणु
		/*
		 * Preserve at least one pageblock unless memory pressure
		 * is really high.
		 */
		अगर (!क्रमce && zone->nr_reserved_highatomic <=
					pageblock_nr_pages)
			जारी;

		spin_lock_irqsave(&zone->lock, flags);
		क्रम (order = 0; order < MAX_ORDER; order++) अणु
			काष्ठा मुक्त_area *area = &(zone->मुक्त_area[order]);

			page = get_page_from_मुक्त_area(area, MIGRATE_HIGHATOMIC);
			अगर (!page)
				जारी;

			/*
			 * In page मुक्तing path, migratetype change is racy so
			 * we can counter several मुक्त pages in a pageblock
			 * in this loop although we changed the pageblock type
			 * from highatomic to ac->migratetype. So we should
			 * adjust the count once.
			 */
			अगर (is_migrate_highatomic_page(page)) अणु
				/*
				 * It should never happen but changes to
				 * locking could inadvertently allow a per-cpu
				 * drain to add pages to MIGRATE_HIGHATOMIC
				 * जबतक unreserving so be safe and watch क्रम
				 * underflows.
				 */
				zone->nr_reserved_highatomic -= min(
						pageblock_nr_pages,
						zone->nr_reserved_highatomic);
			पूर्ण

			/*
			 * Convert to ac->migratetype and aव्योम the normal
			 * pageblock stealing heuristics. Minimally, the caller
			 * is करोing the work and needs the pages. More
			 * importantly, अगर the block was always converted to
			 * MIGRATE_UNMOVABLE or another type then the number
			 * of pageblocks that cannot be completely मुक्तd
			 * may increase.
			 */
			set_pageblock_migratetype(page, ac->migratetype);
			ret = move_मुक्तpages_block(zone, page, ac->migratetype,
									शून्य);
			अगर (ret) अणु
				spin_unlock_irqrestore(&zone->lock, flags);
				वापस ret;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&zone->lock, flags);
	पूर्ण

	वापस false;
पूर्ण

/*
 * Try finding a मुक्त buddy page on the fallback list and put it on the मुक्त
 * list of requested migratetype, possibly aदीर्घ with other pages from the same
 * block, depending on fragmentation aव्योमance heuristics. Returns true अगर
 * fallback was found so that __rmqueue_smallest() can grab it.
 *
 * The use of चिन्हित पूर्णांकs क्रम order and current_order is a deliberate
 * deviation from the rest of this file, to make the क्रम loop
 * condition simpler.
 */
अटल __always_अंतरभूत bool
__rmqueue_fallback(काष्ठा zone *zone, पूर्णांक order, पूर्णांक start_migratetype,
						अचिन्हित पूर्णांक alloc_flags)
अणु
	काष्ठा मुक्त_area *area;
	पूर्णांक current_order;
	पूर्णांक min_order = order;
	काष्ठा page *page;
	पूर्णांक fallback_mt;
	bool can_steal;

	/*
	 * Do not steal pages from मुक्तlists beदीर्घing to other pageblocks
	 * i.e. orders < pageblock_order. If there are no local zones मुक्त,
	 * the zonelists will be reiterated without ALLOC_NOFRAGMENT.
	 */
	अगर (alloc_flags & ALLOC_NOFRAGMENT)
		min_order = pageblock_order;

	/*
	 * Find the largest available मुक्त page in the other list. This roughly
	 * approximates finding the pageblock with the most मुक्त pages, which
	 * would be too costly to करो exactly.
	 */
	क्रम (current_order = MAX_ORDER - 1; current_order >= min_order;
				--current_order) अणु
		area = &(zone->मुक्त_area[current_order]);
		fallback_mt = find_suitable_fallback(area, current_order,
				start_migratetype, false, &can_steal);
		अगर (fallback_mt == -1)
			जारी;

		/*
		 * We cannot steal all मुक्त pages from the pageblock and the
		 * requested migratetype is movable. In that हाल it's better to
		 * steal and split the smallest available page instead of the
		 * largest available page, because even अगर the next movable
		 * allocation falls back पूर्णांकo a dअगरferent pageblock than this
		 * one, it won't cause permanent fragmentation.
		 */
		अगर (!can_steal && start_migratetype == MIGRATE_MOVABLE
					&& current_order > order)
			जाओ find_smallest;

		जाओ करो_steal;
	पूर्ण

	वापस false;

find_smallest:
	क्रम (current_order = order; current_order < MAX_ORDER;
							current_order++) अणु
		area = &(zone->मुक्त_area[current_order]);
		fallback_mt = find_suitable_fallback(area, current_order,
				start_migratetype, false, &can_steal);
		अगर (fallback_mt != -1)
			अवरोध;
	पूर्ण

	/*
	 * This should not happen - we alपढ़ोy found a suitable fallback
	 * when looking क्रम the largest page.
	 */
	VM_BUG_ON(current_order == MAX_ORDER);

करो_steal:
	page = get_page_from_मुक्त_area(area, fallback_mt);

	steal_suitable_fallback(zone, page, alloc_flags, start_migratetype,
								can_steal);

	trace_mm_page_alloc_extfrag(page, order, current_order,
		start_migratetype, fallback_mt);

	वापस true;

पूर्ण

/*
 * Do the hard work of removing an element from the buddy allocator.
 * Call me with the zone->lock alपढ़ोy held.
 */
अटल __always_अंतरभूत काष्ठा page *
__rmqueue(काष्ठा zone *zone, अचिन्हित पूर्णांक order, पूर्णांक migratetype,
						अचिन्हित पूर्णांक alloc_flags)
अणु
	काष्ठा page *page;

	अगर (IS_ENABLED(CONFIG_CMA)) अणु
		/*
		 * Balance movable allocations between regular and CMA areas by
		 * allocating from CMA when over half of the zone's मुक्त memory
		 * is in the CMA area.
		 */
		अगर (alloc_flags & ALLOC_CMA &&
		    zone_page_state(zone, NR_FREE_CMA_PAGES) >
		    zone_page_state(zone, NR_FREE_PAGES) / 2) अणु
			page = __rmqueue_cma_fallback(zone, order);
			अगर (page)
				जाओ out;
		पूर्ण
	पूर्ण
retry:
	page = __rmqueue_smallest(zone, order, migratetype);
	अगर (unlikely(!page)) अणु
		अगर (alloc_flags & ALLOC_CMA)
			page = __rmqueue_cma_fallback(zone, order);

		अगर (!page && __rmqueue_fallback(zone, order, migratetype,
								alloc_flags))
			जाओ retry;
	पूर्ण
out:
	अगर (page)
		trace_mm_page_alloc_zone_locked(page, order, migratetype);
	वापस page;
पूर्ण

/*
 * Obtain a specअगरied number of elements from the buddy allocator, all under
 * a single hold of the lock, क्रम efficiency.  Add them to the supplied list.
 * Returns the number of new pages which were placed at *list.
 */
अटल पूर्णांक rmqueue_bulk(काष्ठा zone *zone, अचिन्हित पूर्णांक order,
			अचिन्हित दीर्घ count, काष्ठा list_head *list,
			पूर्णांक migratetype, अचिन्हित पूर्णांक alloc_flags)
अणु
	पूर्णांक i, allocated = 0;

	spin_lock(&zone->lock);
	क्रम (i = 0; i < count; ++i) अणु
		काष्ठा page *page = __rmqueue(zone, order, migratetype,
								alloc_flags);
		अगर (unlikely(page == शून्य))
			अवरोध;

		अगर (unlikely(check_pcp_refill(page)))
			जारी;

		/*
		 * Split buddy pages वापसed by expand() are received here in
		 * physical page order. The page is added to the tail of
		 * caller's list. From the callers perspective, the linked list
		 * is ordered by page number under some conditions. This is
		 * useful क्रम IO devices that can क्रमward direction from the
		 * head, thus also in the physical page order. This is useful
		 * क्रम IO devices that can merge IO requests अगर the physical
		 * pages are ordered properly.
		 */
		list_add_tail(&page->lru, list);
		allocated++;
		अगर (is_migrate_cma(get_pcppage_migratetype(page)))
			__mod_zone_page_state(zone, NR_FREE_CMA_PAGES,
					      -(1 << order));
	पूर्ण

	/*
	 * i pages were हटाओd from the buddy list even अगर some leak due
	 * to check_pcp_refill failing so adjust NR_FREE_PAGES based
	 * on i. Do not confuse with 'allocated' which is the number of
	 * pages added to the pcp list.
	 */
	__mod_zone_page_state(zone, NR_FREE_PAGES, -(i << order));
	spin_unlock(&zone->lock);
	वापस allocated;
पूर्ण

#अगर_घोषित CONFIG_NUMA
/*
 * Called from the vmstat counter updater to drain pagesets of this
 * currently executing processor on remote nodes after they have
 * expired.
 *
 * Note that this function must be called with the thपढ़ो pinned to
 * a single processor.
 */
व्योम drain_zone_pages(काष्ठा zone *zone, काष्ठा per_cpu_pages *pcp)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक to_drain, batch;

	local_irq_save(flags);
	batch = READ_ONCE(pcp->batch);
	to_drain = min(pcp->count, batch);
	अगर (to_drain > 0)
		मुक्त_pcppages_bulk(zone, to_drain, pcp);
	local_irq_restore(flags);
पूर्ण
#पूर्ण_अगर

/*
 * Drain pcplists of the indicated processor and zone.
 *
 * The processor must either be the current processor and the
 * thपढ़ो pinned to the current processor or a processor that
 * is not online.
 */
अटल व्योम drain_pages_zone(अचिन्हित पूर्णांक cpu, काष्ठा zone *zone)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा per_cpu_pageset *pset;
	काष्ठा per_cpu_pages *pcp;

	local_irq_save(flags);
	pset = per_cpu_ptr(zone->pageset, cpu);

	pcp = &pset->pcp;
	अगर (pcp->count)
		मुक्त_pcppages_bulk(zone, pcp->count, pcp);
	local_irq_restore(flags);
पूर्ण

/*
 * Drain pcplists of all zones on the indicated processor.
 *
 * The processor must either be the current processor and the
 * thपढ़ो pinned to the current processor or a processor that
 * is not online.
 */
अटल व्योम drain_pages(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा zone *zone;

	क्रम_each_populated_zone(zone) अणु
		drain_pages_zone(cpu, zone);
	पूर्ण
पूर्ण

/*
 * Spill all of this CPU's per-cpu pages back पूर्णांकo the buddy allocator.
 *
 * The CPU has to be pinned. When zone parameter is non-शून्य, spill just
 * the single zone's pages.
 */
व्योम drain_local_pages(काष्ठा zone *zone)
अणु
	पूर्णांक cpu = smp_processor_id();

	अगर (zone)
		drain_pages_zone(cpu, zone);
	अन्यथा
		drain_pages(cpu);
पूर्ण

अटल व्योम drain_local_pages_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pcpu_drain *drain;

	drain = container_of(work, काष्ठा pcpu_drain, work);

	/*
	 * drain_all_pages करोesn't use proper cpu hotplug protection so
	 * we can race with cpu offline when the WQ can move this from
	 * a cpu pinned worker to an unbound one. We can operate on a dअगरferent
	 * cpu which is alright but we also have to make sure to not move to
	 * a dअगरferent one.
	 */
	preempt_disable();
	drain_local_pages(drain->zone);
	preempt_enable();
पूर्ण

/*
 * The implementation of drain_all_pages(), exposing an extra parameter to
 * drain on all cpus.
 *
 * drain_all_pages() is optimized to only execute on cpus where pcplists are
 * not empty. The check क्रम non-emptiness can however race with a मुक्त to
 * pcplist that has not yet increased the pcp->count from 0 to 1. Callers
 * that need the guarantee that every CPU has drained can disable the
 * optimizing racy check.
 */
अटल व्योम __drain_all_pages(काष्ठा zone *zone, bool क्रमce_all_cpus)
अणु
	पूर्णांक cpu;

	/*
	 * Allocate in the BSS so we wont require allocation in
	 * direct reclaim path क्रम CONFIG_CPUMASK_OFFSTACK=y
	 */
	अटल cpumask_t cpus_with_pcps;

	/*
	 * Make sure nobody triggers this path beक्रमe mm_percpu_wq is fully
	 * initialized.
	 */
	अगर (WARN_ON_ONCE(!mm_percpu_wq))
		वापस;

	/*
	 * Do not drain अगर one is alपढ़ोy in progress unless it's specअगरic to
	 * a zone. Such callers are primarily CMA and memory hotplug and need
	 * the drain to be complete when the call वापसs.
	 */
	अगर (unlikely(!mutex_trylock(&pcpu_drain_mutex))) अणु
		अगर (!zone)
			वापस;
		mutex_lock(&pcpu_drain_mutex);
	पूर्ण

	/*
	 * We करोn't care about racing with CPU hotplug event
	 * as offline notअगरication will cause the notअगरied
	 * cpu to drain that CPU pcps and on_each_cpu_mask
	 * disables preemption as part of its processing
	 */
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा per_cpu_pageset *pcp;
		काष्ठा zone *z;
		bool has_pcps = false;

		अगर (क्रमce_all_cpus) अणु
			/*
			 * The pcp.count check is racy, some callers need a
			 * guarantee that no cpu is missed.
			 */
			has_pcps = true;
		पूर्ण अन्यथा अगर (zone) अणु
			pcp = per_cpu_ptr(zone->pageset, cpu);
			अगर (pcp->pcp.count)
				has_pcps = true;
		पूर्ण अन्यथा अणु
			क्रम_each_populated_zone(z) अणु
				pcp = per_cpu_ptr(z->pageset, cpu);
				अगर (pcp->pcp.count) अणु
					has_pcps = true;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (has_pcps)
			cpumask_set_cpu(cpu, &cpus_with_pcps);
		अन्यथा
			cpumask_clear_cpu(cpu, &cpus_with_pcps);
	पूर्ण

	क्रम_each_cpu(cpu, &cpus_with_pcps) अणु
		काष्ठा pcpu_drain *drain = per_cpu_ptr(&pcpu_drain, cpu);

		drain->zone = zone;
		INIT_WORK(&drain->work, drain_local_pages_wq);
		queue_work_on(cpu, mm_percpu_wq, &drain->work);
	पूर्ण
	क्रम_each_cpu(cpu, &cpus_with_pcps)
		flush_work(&per_cpu_ptr(&pcpu_drain, cpu)->work);

	mutex_unlock(&pcpu_drain_mutex);
पूर्ण

/*
 * Spill all the per-cpu pages from all CPUs back पूर्णांकo the buddy allocator.
 *
 * When zone parameter is non-शून्य, spill just the single zone's pages.
 *
 * Note that this can be extremely slow as the draining happens in a workqueue.
 */
व्योम drain_all_pages(काष्ठा zone *zone)
अणु
	__drain_all_pages(zone, false);
पूर्ण

#अगर_घोषित CONFIG_HIBERNATION

/*
 * Touch the watchकरोg क्रम every WD_PAGE_COUNT pages.
 */
#घोषणा WD_PAGE_COUNT	(128*1024)

व्योम mark_मुक्त_pages(काष्ठा zone *zone)
अणु
	अचिन्हित दीर्घ pfn, max_zone_pfn, page_count = WD_PAGE_COUNT;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक order, t;
	काष्ठा page *page;

	अगर (zone_is_empty(zone))
		वापस;

	spin_lock_irqsave(&zone->lock, flags);

	max_zone_pfn = zone_end_pfn(zone);
	क्रम (pfn = zone->zone_start_pfn; pfn < max_zone_pfn; pfn++)
		अगर (pfn_valid(pfn)) अणु
			page = pfn_to_page(pfn);

			अगर (!--page_count) अणु
				touch_nmi_watchकरोg();
				page_count = WD_PAGE_COUNT;
			पूर्ण

			अगर (page_zone(page) != zone)
				जारी;

			अगर (!swsusp_page_is_क्रमbidden(page))
				swsusp_unset_page_मुक्त(page);
		पूर्ण

	क्रम_each_migratetype_order(order, t) अणु
		list_क्रम_each_entry(page,
				&zone->मुक्त_area[order].मुक्त_list[t], lru) अणु
			अचिन्हित दीर्घ i;

			pfn = page_to_pfn(page);
			क्रम (i = 0; i < (1UL << order); i++) अणु
				अगर (!--page_count) अणु
					touch_nmi_watchकरोg();
					page_count = WD_PAGE_COUNT;
				पूर्ण
				swsusp_set_page_मुक्त(pfn_to_page(pfn + i));
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&zone->lock, flags);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल bool मुक्त_unref_page_prepare(काष्ठा page *page, अचिन्हित दीर्घ pfn)
अणु
	पूर्णांक migratetype;

	अगर (!मुक्त_pcp_prepare(page))
		वापस false;

	migratetype = get_pfnblock_migratetype(page, pfn);
	set_pcppage_migratetype(page, migratetype);
	वापस true;
पूर्ण

अटल व्योम मुक्त_unref_page_commit(काष्ठा page *page, अचिन्हित दीर्घ pfn)
अणु
	काष्ठा zone *zone = page_zone(page);
	काष्ठा per_cpu_pages *pcp;
	पूर्णांक migratetype;

	migratetype = get_pcppage_migratetype(page);
	__count_vm_event(PGFREE);

	/*
	 * We only track unmovable, reclaimable and movable on pcp lists.
	 * Free ISOLATE pages back to the allocator because they are being
	 * offlined but treat HIGHATOMIC as movable pages so we can get those
	 * areas back अगर necessary. Otherwise, we may have to मुक्त
	 * excessively पूर्णांकo the page allocator
	 */
	अगर (migratetype >= MIGRATE_PCPTYPES) अणु
		अगर (unlikely(is_migrate_isolate(migratetype))) अणु
			मुक्त_one_page(zone, page, pfn, 0, migratetype,
				      FPI_NONE);
			वापस;
		पूर्ण
		migratetype = MIGRATE_MOVABLE;
	पूर्ण

	pcp = &this_cpu_ptr(zone->pageset)->pcp;
	list_add(&page->lru, &pcp->lists[migratetype]);
	pcp->count++;
	अगर (pcp->count >= READ_ONCE(pcp->high))
		मुक्त_pcppages_bulk(zone, READ_ONCE(pcp->batch), pcp);
पूर्ण

/*
 * Free a 0-order page
 */
व्योम मुक्त_unref_page(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ pfn = page_to_pfn(page);

	अगर (!मुक्त_unref_page_prepare(page, pfn))
		वापस;

	local_irq_save(flags);
	मुक्त_unref_page_commit(page, pfn);
	local_irq_restore(flags);
पूर्ण

/*
 * Free a list of 0-order pages
 */
व्योम मुक्त_unref_page_list(काष्ठा list_head *list)
अणु
	काष्ठा page *page, *next;
	अचिन्हित दीर्घ flags, pfn;
	पूर्णांक batch_count = 0;

	/* Prepare pages क्रम मुक्तing */
	list_क्रम_each_entry_safe(page, next, list, lru) अणु
		pfn = page_to_pfn(page);
		अगर (!मुक्त_unref_page_prepare(page, pfn))
			list_del(&page->lru);
		set_page_निजी(page, pfn);
	पूर्ण

	local_irq_save(flags);
	list_क्रम_each_entry_safe(page, next, list, lru) अणु
		अचिन्हित दीर्घ pfn = page_निजी(page);

		set_page_निजी(page, 0);
		trace_mm_page_मुक्त_batched(page);
		मुक्त_unref_page_commit(page, pfn);

		/*
		 * Guard against excessive IRQ disabled बार when we get
		 * a large list of pages to मुक्त.
		 */
		अगर (++batch_count == SWAP_CLUSTER_MAX) अणु
			local_irq_restore(flags);
			batch_count = 0;
			local_irq_save(flags);
		पूर्ण
	पूर्ण
	local_irq_restore(flags);
पूर्ण

/*
 * split_page takes a non-compound higher-order page, and splits it पूर्णांकo
 * n (1<<order) sub-pages: page[0..n]
 * Each sub-page must be मुक्तd inभागidually.
 *
 * Note: this is probably too low level an operation क्रम use in drivers.
 * Please consult with lkml beक्रमe using this in your driver.
 */
व्योम split_page(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	पूर्णांक i;

	VM_BUG_ON_PAGE(PageCompound(page), page);
	VM_BUG_ON_PAGE(!page_count(page), page);

	क्रम (i = 1; i < (1 << order); i++)
		set_page_refcounted(page + i);
	split_page_owner(page, 1 << order);
	split_page_memcg(page, 1 << order);
पूर्ण
EXPORT_SYMBOL_GPL(split_page);

पूर्णांक __isolate_मुक्त_page(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	अचिन्हित दीर्घ watermark;
	काष्ठा zone *zone;
	पूर्णांक mt;

	BUG_ON(!PageBuddy(page));

	zone = page_zone(page);
	mt = get_pageblock_migratetype(page);

	अगर (!is_migrate_isolate(mt)) अणु
		/*
		 * Obey watermarks as अगर the page was being allocated. We can
		 * emulate a high-order watermark check with a उठाओd order-0
		 * watermark, because we alपढ़ोy know our high-order page
		 * exists.
		 */
		watermark = zone->_watermark[WMARK_MIN] + (1UL << order);
		अगर (!zone_watermark_ok(zone, 0, watermark, 0, ALLOC_CMA))
			वापस 0;

		__mod_zone_मुक्तpage_state(zone, -(1UL << order), mt);
	पूर्ण

	/* Remove page from मुक्त list */

	del_page_from_मुक्त_list(page, zone, order);

	/*
	 * Set the pageblock अगर the isolated page is at least half of a
	 * pageblock
	 */
	अगर (order >= pageblock_order - 1) अणु
		काष्ठा page *endpage = page + (1 << order) - 1;
		क्रम (; page < endpage; page += pageblock_nr_pages) अणु
			पूर्णांक mt = get_pageblock_migratetype(page);
			अगर (!is_migrate_isolate(mt) && !is_migrate_cma(mt)
			    && !is_migrate_highatomic(mt))
				set_pageblock_migratetype(page,
							  MIGRATE_MOVABLE);
		पूर्ण
	पूर्ण


	वापस 1UL << order;
पूर्ण

/**
 * __putback_isolated_page - Return a now-isolated page back where we got it
 * @page: Page that was isolated
 * @order: Order of the isolated page
 * @mt: The page's pageblock's migratetype
 *
 * This function is meant to वापस a page pulled from the मुक्त lists via
 * __isolate_मुक्त_page back to the मुक्त lists they were pulled from.
 */
व्योम __putback_isolated_page(काष्ठा page *page, अचिन्हित पूर्णांक order, पूर्णांक mt)
अणु
	काष्ठा zone *zone = page_zone(page);

	/* zone lock should be held when this function is called */
	lockdep_निश्चित_held(&zone->lock);

	/* Return isolated page to tail of मुक्तlist. */
	__मुक्त_one_page(page, page_to_pfn(page), zone, order, mt,
			FPI_SKIP_REPORT_NOTIFY | FPI_TO_TAIL);
पूर्ण

/*
 * Update NUMA hit/miss statistics
 *
 * Must be called with पूर्णांकerrupts disabled.
 */
अटल अंतरभूत व्योम zone_statistics(काष्ठा zone *preferred_zone, काष्ठा zone *z)
अणु
#अगर_घोषित CONFIG_NUMA
	क्रमागत numa_stat_item local_stat = NUMA_LOCAL;

	/* skip numa counters update अगर numa stats is disabled */
	अगर (!अटल_branch_likely(&vm_numa_stat_key))
		वापस;

	अगर (zone_to_nid(z) != numa_node_id())
		local_stat = NUMA_OTHER;

	अगर (zone_to_nid(z) == zone_to_nid(preferred_zone))
		__inc_numa_state(z, NUMA_HIT);
	अन्यथा अणु
		__inc_numa_state(z, NUMA_MISS);
		__inc_numa_state(preferred_zone, NUMA_FOREIGN);
	पूर्ण
	__inc_numa_state(z, local_stat);
#पूर्ण_अगर
पूर्ण

/* Remove page from the per-cpu list, caller must protect the list */
अटल अंतरभूत
काष्ठा page *__rmqueue_pcplist(काष्ठा zone *zone, पूर्णांक migratetype,
			अचिन्हित पूर्णांक alloc_flags,
			काष्ठा per_cpu_pages *pcp,
			काष्ठा list_head *list)
अणु
	काष्ठा page *page;

	करो अणु
		अगर (list_empty(list)) अणु
			pcp->count += rmqueue_bulk(zone, 0,
					READ_ONCE(pcp->batch), list,
					migratetype, alloc_flags);
			अगर (unlikely(list_empty(list)))
				वापस शून्य;
		पूर्ण

		page = list_first_entry(list, काष्ठा page, lru);
		list_del(&page->lru);
		pcp->count--;
	पूर्ण जबतक (check_new_pcp(page));

	वापस page;
पूर्ण

/* Lock and हटाओ page from the per-cpu list */
अटल काष्ठा page *rmqueue_pcplist(काष्ठा zone *preferred_zone,
			काष्ठा zone *zone, gfp_t gfp_flags,
			पूर्णांक migratetype, अचिन्हित पूर्णांक alloc_flags)
अणु
	काष्ठा per_cpu_pages *pcp;
	काष्ठा list_head *list;
	काष्ठा page *page;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	pcp = &this_cpu_ptr(zone->pageset)->pcp;
	list = &pcp->lists[migratetype];
	page = __rmqueue_pcplist(zone,  migratetype, alloc_flags, pcp, list);
	अगर (page) अणु
		__count_zid_vm_events(PGALLOC, page_zonक्रमागत(page), 1);
		zone_statistics(preferred_zone, zone);
	पूर्ण
	local_irq_restore(flags);
	वापस page;
पूर्ण

/*
 * Allocate a page from the given zone. Use pcplists क्रम order-0 allocations.
 */
अटल अंतरभूत
काष्ठा page *rmqueue(काष्ठा zone *preferred_zone,
			काष्ठा zone *zone, अचिन्हित पूर्णांक order,
			gfp_t gfp_flags, अचिन्हित पूर्णांक alloc_flags,
			पूर्णांक migratetype)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा page *page;

	अगर (likely(order == 0)) अणु
		/*
		 * MIGRATE_MOVABLE pcplist could have the pages on CMA area and
		 * we need to skip it when CMA area isn't allowed.
		 */
		अगर (!IS_ENABLED(CONFIG_CMA) || alloc_flags & ALLOC_CMA ||
				migratetype != MIGRATE_MOVABLE) अणु
			page = rmqueue_pcplist(preferred_zone, zone, gfp_flags,
					migratetype, alloc_flags);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * We most definitely करोn't want callers attempting to
	 * allocate greater than order-1 page units with __GFP_NOFAIL.
	 */
	WARN_ON_ONCE((gfp_flags & __GFP_NOFAIL) && (order > 1));
	spin_lock_irqsave(&zone->lock, flags);

	करो अणु
		page = शून्य;
		/*
		 * order-0 request can reach here when the pcplist is skipped
		 * due to non-CMA allocation context. HIGHATOMIC area is
		 * reserved क्रम high-order atomic allocation, so order-0
		 * request should skip it.
		 */
		अगर (order > 0 && alloc_flags & ALLOC_HARDER) अणु
			page = __rmqueue_smallest(zone, order, MIGRATE_HIGHATOMIC);
			अगर (page)
				trace_mm_page_alloc_zone_locked(page, order, migratetype);
		पूर्ण
		अगर (!page)
			page = __rmqueue(zone, order, migratetype, alloc_flags);
	पूर्ण जबतक (page && check_new_pages(page, order));
	spin_unlock(&zone->lock);
	अगर (!page)
		जाओ failed;
	__mod_zone_मुक्तpage_state(zone, -(1 << order),
				  get_pcppage_migratetype(page));

	__count_zid_vm_events(PGALLOC, page_zonक्रमागत(page), 1 << order);
	zone_statistics(preferred_zone, zone);
	local_irq_restore(flags);

out:
	/* Separate test+clear to aव्योम unnecessary atomics */
	अगर (test_bit(ZONE_BOOSTED_WATERMARK, &zone->flags)) अणु
		clear_bit(ZONE_BOOSTED_WATERMARK, &zone->flags);
		wakeup_kswapd(zone, 0, 0, zone_idx(zone));
	पूर्ण

	VM_BUG_ON_PAGE(page && bad_range(zone, page), page);
	वापस page;

failed:
	local_irq_restore(flags);
	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_FAIL_PAGE_ALLOC

अटल काष्ठा अणु
	काष्ठा fault_attr attr;

	bool ignore_gfp_highmem;
	bool ignore_gfp_reclaim;
	u32 min_order;
पूर्ण fail_page_alloc = अणु
	.attr = FAULT_ATTR_INITIALIZER,
	.ignore_gfp_reclaim = true,
	.ignore_gfp_highmem = true,
	.min_order = 1,
पूर्ण;

अटल पूर्णांक __init setup_fail_page_alloc(अक्षर *str)
अणु
	वापस setup_fault_attr(&fail_page_alloc.attr, str);
पूर्ण
__setup("fail_page_alloc=", setup_fail_page_alloc);

अटल bool __should_fail_alloc_page(gfp_t gfp_mask, अचिन्हित पूर्णांक order)
अणु
	अगर (order < fail_page_alloc.min_order)
		वापस false;
	अगर (gfp_mask & __GFP_NOFAIL)
		वापस false;
	अगर (fail_page_alloc.ignore_gfp_highmem && (gfp_mask & __GFP_HIGHMEM))
		वापस false;
	अगर (fail_page_alloc.ignore_gfp_reclaim &&
			(gfp_mask & __GFP_सूचीECT_RECLAIM))
		वापस false;

	वापस should_fail(&fail_page_alloc.attr, 1 << order);
पूर्ण

#अगर_घोषित CONFIG_FAULT_INJECTION_DEBUG_FS

अटल पूर्णांक __init fail_page_alloc_debugfs(व्योम)
अणु
	umode_t mode = S_IFREG | 0600;
	काष्ठा dentry *dir;

	dir = fault_create_debugfs_attr("fail_page_alloc", शून्य,
					&fail_page_alloc.attr);

	debugfs_create_bool("ignore-gfp-wait", mode, dir,
			    &fail_page_alloc.ignore_gfp_reclaim);
	debugfs_create_bool("ignore-gfp-highmem", mode, dir,
			    &fail_page_alloc.ignore_gfp_highmem);
	debugfs_create_u32("min-order", mode, dir, &fail_page_alloc.min_order);

	वापस 0;
पूर्ण

late_initcall(fail_page_alloc_debugfs);

#पूर्ण_अगर /* CONFIG_FAULT_INJECTION_DEBUG_FS */

#अन्यथा /* CONFIG_FAIL_PAGE_ALLOC */

अटल अंतरभूत bool __should_fail_alloc_page(gfp_t gfp_mask, अचिन्हित पूर्णांक order)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_FAIL_PAGE_ALLOC */

noअंतरभूत bool should_fail_alloc_page(gfp_t gfp_mask, अचिन्हित पूर्णांक order)
अणु
	वापस __should_fail_alloc_page(gfp_mask, order);
पूर्ण
ALLOW_ERROR_INJECTION(should_fail_alloc_page, TRUE);

अटल अंतरभूत दीर्घ __zone_watermark_unusable_मुक्त(काष्ठा zone *z,
				अचिन्हित पूर्णांक order, अचिन्हित पूर्णांक alloc_flags)
अणु
	स्थिर bool alloc_harder = (alloc_flags & (ALLOC_HARDER|ALLOC_OOM));
	दीर्घ unusable_मुक्त = (1 << order) - 1;

	/*
	 * If the caller करोes not have rights to ALLOC_HARDER then subtract
	 * the high-atomic reserves. This will over-estimate the size of the
	 * atomic reserve but it aव्योमs a search.
	 */
	अगर (likely(!alloc_harder))
		unusable_मुक्त += z->nr_reserved_highatomic;

#अगर_घोषित CONFIG_CMA
	/* If allocation can't use CMA areas don't use मुक्त CMA pages */
	अगर (!(alloc_flags & ALLOC_CMA))
		unusable_मुक्त += zone_page_state(z, NR_FREE_CMA_PAGES);
#पूर्ण_अगर

	वापस unusable_मुक्त;
पूर्ण

/*
 * Return true अगर मुक्त base pages are above 'mark'. For high-order checks it
 * will वापस true of the order-0 watermark is reached and there is at least
 * one मुक्त page of a suitable size. Checking now aव्योमs taking the zone lock
 * to check in the allocation paths अगर no pages are मुक्त.
 */
bool __zone_watermark_ok(काष्ठा zone *z, अचिन्हित पूर्णांक order, अचिन्हित दीर्घ mark,
			 पूर्णांक highest_zoneidx, अचिन्हित पूर्णांक alloc_flags,
			 दीर्घ मुक्त_pages)
अणु
	दीर्घ min = mark;
	पूर्णांक o;
	स्थिर bool alloc_harder = (alloc_flags & (ALLOC_HARDER|ALLOC_OOM));

	/* मुक्त_pages may go negative - that's OK */
	मुक्त_pages -= __zone_watermark_unusable_मुक्त(z, order, alloc_flags);

	अगर (alloc_flags & ALLOC_HIGH)
		min -= min / 2;

	अगर (unlikely(alloc_harder)) अणु
		/*
		 * OOM victims can try even harder than normal ALLOC_HARDER
		 * users on the grounds that it's definitely going to be in
		 * the निकास path लघुly and मुक्त memory. Any allocation it
		 * makes during the मुक्त path will be small and लघु-lived.
		 */
		अगर (alloc_flags & ALLOC_OOM)
			min -= min / 2;
		अन्यथा
			min -= min / 4;
	पूर्ण

	/*
	 * Check watermarks क्रम an order-0 allocation request. If these
	 * are not met, then a high-order request also cannot go ahead
	 * even अगर a suitable page happened to be मुक्त.
	 */
	अगर (मुक्त_pages <= min + z->lowmem_reserve[highest_zoneidx])
		वापस false;

	/* If this is an order-0 request then the watermark is fine */
	अगर (!order)
		वापस true;

	/* For a high-order request, check at least one suitable page is मुक्त */
	क्रम (o = order; o < MAX_ORDER; o++) अणु
		काष्ठा मुक्त_area *area = &z->मुक्त_area[o];
		पूर्णांक mt;

		अगर (!area->nr_मुक्त)
			जारी;

		क्रम (mt = 0; mt < MIGRATE_PCPTYPES; mt++) अणु
			अगर (!मुक्त_area_empty(area, mt))
				वापस true;
		पूर्ण

#अगर_घोषित CONFIG_CMA
		अगर ((alloc_flags & ALLOC_CMA) &&
		    !मुक्त_area_empty(area, MIGRATE_CMA)) अणु
			वापस true;
		पूर्ण
#पूर्ण_अगर
		अगर (alloc_harder && !मुक्त_area_empty(area, MIGRATE_HIGHATOMIC))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool zone_watermark_ok(काष्ठा zone *z, अचिन्हित पूर्णांक order, अचिन्हित दीर्घ mark,
		      पूर्णांक highest_zoneidx, अचिन्हित पूर्णांक alloc_flags)
अणु
	वापस __zone_watermark_ok(z, order, mark, highest_zoneidx, alloc_flags,
					zone_page_state(z, NR_FREE_PAGES));
पूर्ण

अटल अंतरभूत bool zone_watermark_fast(काष्ठा zone *z, अचिन्हित पूर्णांक order,
				अचिन्हित दीर्घ mark, पूर्णांक highest_zoneidx,
				अचिन्हित पूर्णांक alloc_flags, gfp_t gfp_mask)
अणु
	दीर्घ मुक्त_pages;

	मुक्त_pages = zone_page_state(z, NR_FREE_PAGES);

	/*
	 * Fast check क्रम order-0 only. If this fails then the reserves
	 * need to be calculated.
	 */
	अगर (!order) अणु
		दीर्घ fast_मुक्त;

		fast_मुक्त = मुक्त_pages;
		fast_मुक्त -= __zone_watermark_unusable_मुक्त(z, 0, alloc_flags);
		अगर (fast_मुक्त > mark + z->lowmem_reserve[highest_zoneidx])
			वापस true;
	पूर्ण

	अगर (__zone_watermark_ok(z, order, mark, highest_zoneidx, alloc_flags,
					मुक्त_pages))
		वापस true;
	/*
	 * Ignore watermark boosting क्रम GFP_ATOMIC order-0 allocations
	 * when checking the min watermark. The min watermark is the
	 * poपूर्णांक where boosting is ignored so that kswapd is woken up
	 * when below the low watermark.
	 */
	अगर (unlikely(!order && (gfp_mask & __GFP_ATOMIC) && z->watermark_boost
		&& ((alloc_flags & ALLOC_WMARK_MASK) == WMARK_MIN))) अणु
		mark = z->_watermark[WMARK_MIN];
		वापस __zone_watermark_ok(z, order, mark, highest_zoneidx,
					alloc_flags, मुक्त_pages);
	पूर्ण

	वापस false;
पूर्ण

bool zone_watermark_ok_safe(काष्ठा zone *z, अचिन्हित पूर्णांक order,
			अचिन्हित दीर्घ mark, पूर्णांक highest_zoneidx)
अणु
	दीर्घ मुक्त_pages = zone_page_state(z, NR_FREE_PAGES);

	अगर (z->percpu_drअगरt_mark && मुक्त_pages < z->percpu_drअगरt_mark)
		मुक्त_pages = zone_page_state_snapshot(z, NR_FREE_PAGES);

	वापस __zone_watermark_ok(z, order, mark, highest_zoneidx, 0,
								मुक्त_pages);
पूर्ण

#अगर_घोषित CONFIG_NUMA
अटल bool zone_allows_reclaim(काष्ठा zone *local_zone, काष्ठा zone *zone)
अणु
	वापस node_distance(zone_to_nid(local_zone), zone_to_nid(zone)) <=
				node_reclaim_distance;
पूर्ण
#अन्यथा	/* CONFIG_NUMA */
अटल bool zone_allows_reclaim(काष्ठा zone *local_zone, काष्ठा zone *zone)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर	/* CONFIG_NUMA */

/*
 * The restriction on ZONE_DMA32 as being a suitable zone to use to aव्योम
 * fragmentation is subtle. If the preferred zone was HIGHMEM then
 * premature use of a lower zone may cause lowmem pressure problems that
 * are worse than fragmentation. If the next zone is ZONE_DMA then it is
 * probably too small. It only makes sense to spपढ़ो allocations to aव्योम
 * fragmentation between the Normal and DMA32 zones.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
alloc_flags_nofragment(काष्ठा zone *zone, gfp_t gfp_mask)
अणु
	अचिन्हित पूर्णांक alloc_flags;

	/*
	 * __GFP_KSWAPD_RECLAIM is assumed to be the same as ALLOC_KSWAPD
	 * to save a branch.
	 */
	alloc_flags = (__क्रमce पूर्णांक) (gfp_mask & __GFP_KSWAPD_RECLAIM);

#अगर_घोषित CONFIG_ZONE_DMA32
	अगर (!zone)
		वापस alloc_flags;

	अगर (zone_idx(zone) != ZONE_NORMAL)
		वापस alloc_flags;

	/*
	 * If ZONE_DMA32 exists, assume it is the one after ZONE_NORMAL and
	 * the poपूर्णांकer is within zone->zone_pgdat->node_zones[]. Also assume
	 * on UMA that अगर Normal is populated then so is DMA32.
	 */
	BUILD_BUG_ON(ZONE_NORMAL - ZONE_DMA32 != 1);
	अगर (nr_online_nodes > 1 && !populated_zone(--zone))
		वापस alloc_flags;

	alloc_flags |= ALLOC_NOFRAGMENT;
#पूर्ण_अगर /* CONFIG_ZONE_DMA32 */
	वापस alloc_flags;
पूर्ण

/* Must be called after current_gfp_context() which can change gfp_mask */
अटल अंतरभूत अचिन्हित पूर्णांक gfp_to_alloc_flags_cma(gfp_t gfp_mask,
						  अचिन्हित पूर्णांक alloc_flags)
अणु
#अगर_घोषित CONFIG_CMA
	अगर (gfp_migratetype(gfp_mask) == MIGRATE_MOVABLE)
		alloc_flags |= ALLOC_CMA;
#पूर्ण_अगर
	वापस alloc_flags;
पूर्ण

/*
 * get_page_from_मुक्तlist goes through the zonelist trying to allocate
 * a page.
 */
अटल काष्ठा page *
get_page_from_मुक्तlist(gfp_t gfp_mask, अचिन्हित पूर्णांक order, पूर्णांक alloc_flags,
						स्थिर काष्ठा alloc_context *ac)
अणु
	काष्ठा zoneref *z;
	काष्ठा zone *zone;
	काष्ठा pglist_data *last_pgdat_dirty_limit = शून्य;
	bool no_fallback;

retry:
	/*
	 * Scan zonelist, looking क्रम a zone with enough मुक्त.
	 * See also __cpuset_node_allowed() comment in kernel/cpuset.c.
	 */
	no_fallback = alloc_flags & ALLOC_NOFRAGMENT;
	z = ac->preferred_zoneref;
	क्रम_next_zone_zonelist_nodemask(zone, z, ac->highest_zoneidx,
					ac->nodemask) अणु
		काष्ठा page *page;
		अचिन्हित दीर्घ mark;

		अगर (cpusets_enabled() &&
			(alloc_flags & ALLOC_CPUSET) &&
			!__cpuset_zone_allowed(zone, gfp_mask))
				जारी;
		/*
		 * When allocating a page cache page क्रम writing, we
		 * want to get it from a node that is within its dirty
		 * limit, such that no single node holds more than its
		 * proportional share of globally allowed dirty pages.
		 * The dirty limits take पूर्णांकo account the node's
		 * lowmem reserves and high watermark so that kswapd
		 * should be able to balance it without having to
		 * ग_लिखो pages from its LRU list.
		 *
		 * XXX: For now, allow allocations to potentially
		 * exceed the per-node dirty limit in the slowpath
		 * (spपढ़ो_dirty_pages unset) beक्रमe going पूर्णांकo reclaim,
		 * which is important when on a NUMA setup the allowed
		 * nodes are together not big enough to reach the
		 * global limit.  The proper fix क्रम these situations
		 * will require awareness of nodes in the
		 * dirty-throttling and the flusher thपढ़ोs.
		 */
		अगर (ac->spपढ़ो_dirty_pages) अणु
			अगर (last_pgdat_dirty_limit == zone->zone_pgdat)
				जारी;

			अगर (!node_dirty_ok(zone->zone_pgdat)) अणु
				last_pgdat_dirty_limit = zone->zone_pgdat;
				जारी;
			पूर्ण
		पूर्ण

		अगर (no_fallback && nr_online_nodes > 1 &&
		    zone != ac->preferred_zoneref->zone) अणु
			पूर्णांक local_nid;

			/*
			 * If moving to a remote node, retry but allow
			 * fragmenting fallbacks. Locality is more important
			 * than fragmentation aव्योमance.
			 */
			local_nid = zone_to_nid(ac->preferred_zoneref->zone);
			अगर (zone_to_nid(zone) != local_nid) अणु
				alloc_flags &= ~ALLOC_NOFRAGMENT;
				जाओ retry;
			पूर्ण
		पूर्ण

		mark = wmark_pages(zone, alloc_flags & ALLOC_WMARK_MASK);
		अगर (!zone_watermark_fast(zone, order, mark,
				       ac->highest_zoneidx, alloc_flags,
				       gfp_mask)) अणु
			पूर्णांक ret;

#अगर_घोषित CONFIG_DEFERRED_STRUCT_PAGE_INIT
			/*
			 * Watermark failed क्रम this zone, but see अगर we can
			 * grow this zone अगर it contains deferred pages.
			 */
			अगर (अटल_branch_unlikely(&deferred_pages)) अणु
				अगर (_deferred_grow_zone(zone, order))
					जाओ try_this_zone;
			पूर्ण
#पूर्ण_अगर
			/* Checked here to keep the fast path fast */
			BUILD_BUG_ON(ALLOC_NO_WATERMARKS < NR_WMARK);
			अगर (alloc_flags & ALLOC_NO_WATERMARKS)
				जाओ try_this_zone;

			अगर (!node_reclaim_enabled() ||
			    !zone_allows_reclaim(ac->preferred_zoneref->zone, zone))
				जारी;

			ret = node_reclaim(zone->zone_pgdat, gfp_mask, order);
			चयन (ret) अणु
			हाल NODE_RECLAIM_NOSCAN:
				/* did not scan */
				जारी;
			हाल NODE_RECLAIM_FULL:
				/* scanned but unreclaimable */
				जारी;
			शेष:
				/* did we reclaim enough */
				अगर (zone_watermark_ok(zone, order, mark,
					ac->highest_zoneidx, alloc_flags))
					जाओ try_this_zone;

				जारी;
			पूर्ण
		पूर्ण

try_this_zone:
		page = rmqueue(ac->preferred_zoneref->zone, zone, order,
				gfp_mask, alloc_flags, ac->migratetype);
		अगर (page) अणु
			prep_new_page(page, order, gfp_mask, alloc_flags);

			/*
			 * If this is a high-order atomic allocation then check
			 * अगर the pageblock should be reserved क्रम the future
			 */
			अगर (unlikely(order && (alloc_flags & ALLOC_HARDER)))
				reserve_highatomic_pageblock(page, zone, order);

			वापस page;
		पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_DEFERRED_STRUCT_PAGE_INIT
			/* Try again अगर zone has deferred pages */
			अगर (अटल_branch_unlikely(&deferred_pages)) अणु
				अगर (_deferred_grow_zone(zone, order))
					जाओ try_this_zone;
			पूर्ण
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	/*
	 * It's possible on a UMA machine to get through all zones that are
	 * fragmented. If aव्योमing fragmentation, reset and try again.
	 */
	अगर (no_fallback) अणु
		alloc_flags &= ~ALLOC_NOFRAGMENT;
		जाओ retry;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम warn_alloc_show_mem(gfp_t gfp_mask, nodemask_t *nodemask)
अणु
	अचिन्हित पूर्णांक filter = SHOW_MEM_FILTER_NODES;

	/*
	 * This करोcuments exceptions given to allocations in certain
	 * contexts that are allowed to allocate outside current's set
	 * of allowed nodes.
	 */
	अगर (!(gfp_mask & __GFP_NOMEMALLOC))
		अगर (tsk_is_oom_victim(current) ||
		    (current->flags & (PF_MEMALLOC | PF_EXITING)))
			filter &= ~SHOW_MEM_FILTER_NODES;
	अगर (in_पूर्णांकerrupt() || !(gfp_mask & __GFP_सूचीECT_RECLAIM))
		filter &= ~SHOW_MEM_FILTER_NODES;

	show_mem(filter, nodemask);
पूर्ण

व्योम warn_alloc(gfp_t gfp_mask, nodemask_t *nodemask, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	अटल DEFINE_RATELIMIT_STATE(nopage_rs, 10*HZ, 1);

	अगर ((gfp_mask & __GFP_NOWARN) || !__ratelimit(&nopage_rs))
		वापस;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	pr_warn("%s: %pV, mode:%#x(%pGg), nodemask=%*pbl",
			current->comm, &vaf, gfp_mask, &gfp_mask,
			nodemask_pr_args(nodemask));
	बहु_पूर्ण(args);

	cpuset_prपूर्णांक_current_mems_allowed();
	pr_cont("\n");
	dump_stack();
	warn_alloc_show_mem(gfp_mask, nodemask);
पूर्ण

अटल अंतरभूत काष्ठा page *
__alloc_pages_cpuset_fallback(gfp_t gfp_mask, अचिन्हित पूर्णांक order,
			      अचिन्हित पूर्णांक alloc_flags,
			      स्थिर काष्ठा alloc_context *ac)
अणु
	काष्ठा page *page;

	page = get_page_from_मुक्तlist(gfp_mask, order,
			alloc_flags|ALLOC_CPUSET, ac);
	/*
	 * fallback to ignore cpuset restriction अगर our nodes
	 * are depleted
	 */
	अगर (!page)
		page = get_page_from_मुक्तlist(gfp_mask, order,
				alloc_flags, ac);

	वापस page;
पूर्ण

अटल अंतरभूत काष्ठा page *
__alloc_pages_may_oom(gfp_t gfp_mask, अचिन्हित पूर्णांक order,
	स्थिर काष्ठा alloc_context *ac, अचिन्हित दीर्घ *did_some_progress)
अणु
	काष्ठा oom_control oc = अणु
		.zonelist = ac->zonelist,
		.nodemask = ac->nodemask,
		.memcg = शून्य,
		.gfp_mask = gfp_mask,
		.order = order,
	पूर्ण;
	काष्ठा page *page;

	*did_some_progress = 0;

	/*
	 * Acquire the oom lock.  If that fails, somebody अन्यथा is
	 * making progress क्रम us.
	 */
	अगर (!mutex_trylock(&oom_lock)) अणु
		*did_some_progress = 1;
		schedule_समयout_unपूर्णांकerruptible(1);
		वापस शून्य;
	पूर्ण

	/*
	 * Go through the zonelist yet one more समय, keep very high watermark
	 * here, this is only to catch a parallel oom समाप्तing, we must fail अगर
	 * we're still under heavy pressure. But make sure that this reclaim
	 * attempt shall not depend on __GFP_सूचीECT_RECLAIM && !__GFP_NORETRY
	 * allocation which will never fail due to oom_lock alपढ़ोy held.
	 */
	page = get_page_from_मुक्तlist((gfp_mask | __GFP_HARDWALL) &
				      ~__GFP_सूचीECT_RECLAIM, order,
				      ALLOC_WMARK_HIGH|ALLOC_CPUSET, ac);
	अगर (page)
		जाओ out;

	/* Coredumps can quickly deplete all memory reserves */
	अगर (current->flags & PF_DUMPCORE)
		जाओ out;
	/* The OOM समाप्तer will not help higher order allocs */
	अगर (order > PAGE_ALLOC_COSTLY_ORDER)
		जाओ out;
	/*
	 * We have alपढ़ोy exhausted all our reclaim opportunities without any
	 * success so it is समय to admit defeat. We will skip the OOM समाप्तer
	 * because it is very likely that the caller has a more reasonable
	 * fallback than shooting a अक्रमom task.
	 *
	 * The OOM समाप्तer may not मुक्त memory on a specअगरic node.
	 */
	अगर (gfp_mask & (__GFP_RETRY_MAYFAIL | __GFP_THISNODE))
		जाओ out;
	/* The OOM समाप्तer करोes not needlessly समाप्त tasks क्रम lowmem */
	अगर (ac->highest_zoneidx < ZONE_NORMAL)
		जाओ out;
	अगर (pm_suspended_storage())
		जाओ out;
	/*
	 * XXX: GFP_NOFS allocations should rather fail than rely on
	 * other request to make a क्रमward progress.
	 * We are in an unक्रमtunate situation where out_of_memory cannot
	 * करो much क्रम this context but let's try it to at least get
	 * access to memory reserved अगर the current task is समाप्तed (see
	 * out_of_memory). Once fileप्रणालीs are पढ़ोy to handle allocation
	 * failures more gracefully we should just bail out here.
	 */

	/* Exhausted what can be करोne so it's blame समय */
	अगर (out_of_memory(&oc) || WARN_ON_ONCE(gfp_mask & __GFP_NOFAIL)) अणु
		*did_some_progress = 1;

		/*
		 * Help non-failing allocations by giving them access to memory
		 * reserves
		 */
		अगर (gfp_mask & __GFP_NOFAIL)
			page = __alloc_pages_cpuset_fallback(gfp_mask, order,
					ALLOC_NO_WATERMARKS, ac);
	पूर्ण
out:
	mutex_unlock(&oom_lock);
	वापस page;
पूर्ण

/*
 * Maximum number of compaction retries with a progress beक्रमe OOM
 * समाप्तer is consider as the only way to move क्रमward.
 */
#घोषणा MAX_COMPACT_RETRIES 16

#अगर_घोषित CONFIG_COMPACTION
/* Try memory compaction क्रम high-order allocations beक्रमe reclaim */
अटल काष्ठा page *
__alloc_pages_direct_compact(gfp_t gfp_mask, अचिन्हित पूर्णांक order,
		अचिन्हित पूर्णांक alloc_flags, स्थिर काष्ठा alloc_context *ac,
		क्रमागत compact_priority prio, क्रमागत compact_result *compact_result)
अणु
	काष्ठा page *page = शून्य;
	अचिन्हित दीर्घ pflags;
	अचिन्हित पूर्णांक noreclaim_flag;

	अगर (!order)
		वापस शून्य;

	psi_memstall_enter(&pflags);
	noreclaim_flag = meदो_स्मृति_noreclaim_save();

	*compact_result = try_to_compact_pages(gfp_mask, order, alloc_flags, ac,
								prio, &page);

	meदो_स्मृति_noreclaim_restore(noreclaim_flag);
	psi_memstall_leave(&pflags);

	अगर (*compact_result == COMPACT_SKIPPED)
		वापस शून्य;
	/*
	 * At least in one zone compaction wasn't deferred or skipped, so let's
	 * count a compaction stall
	 */
	count_vm_event(COMPACTSTALL);

	/* Prep a captured page अगर available */
	अगर (page)
		prep_new_page(page, order, gfp_mask, alloc_flags);

	/* Try get a page from the मुक्तlist अगर available */
	अगर (!page)
		page = get_page_from_मुक्तlist(gfp_mask, order, alloc_flags, ac);

	अगर (page) अणु
		काष्ठा zone *zone = page_zone(page);

		zone->compact_blockskip_flush = false;
		compaction_defer_reset(zone, order, true);
		count_vm_event(COMPACTSUCCESS);
		वापस page;
	पूर्ण

	/*
	 * It's bad अगर compaction run occurs and fails. The most likely reason
	 * is that pages exist, but not enough to satisfy watermarks.
	 */
	count_vm_event(COMPACTFAIL);

	cond_resched();

	वापस शून्य;
पूर्ण

अटल अंतरभूत bool
should_compact_retry(काष्ठा alloc_context *ac, पूर्णांक order, पूर्णांक alloc_flags,
		     क्रमागत compact_result compact_result,
		     क्रमागत compact_priority *compact_priority,
		     पूर्णांक *compaction_retries)
अणु
	पूर्णांक max_retries = MAX_COMPACT_RETRIES;
	पूर्णांक min_priority;
	bool ret = false;
	पूर्णांक retries = *compaction_retries;
	क्रमागत compact_priority priority = *compact_priority;

	अगर (!order)
		वापस false;

	अगर (compaction_made_progress(compact_result))
		(*compaction_retries)++;

	/*
	 * compaction considers all the zone as desperately out of memory
	 * so it करोesn't really make much sense to retry except when the
	 * failure could be caused by insufficient priority
	 */
	अगर (compaction_failed(compact_result))
		जाओ check_priority;

	/*
	 * compaction was skipped because there are not enough order-0 pages
	 * to work with, so we retry only अगर it looks like reclaim can help.
	 */
	अगर (compaction_needs_reclaim(compact_result)) अणु
		ret = compaction_zonelist_suitable(ac, order, alloc_flags);
		जाओ out;
	पूर्ण

	/*
	 * make sure the compaction wasn't deferred or didn't bail out early
	 * due to locks contention beक्रमe we declare that we should give up.
	 * But the next retry should use a higher priority अगर allowed, so
	 * we करोn't just keep bailing out endlessly.
	 */
	अगर (compaction_withdrawn(compact_result)) अणु
		जाओ check_priority;
	पूर्ण

	/*
	 * !costly requests are much more important than __GFP_RETRY_MAYFAIL
	 * costly ones because they are de facto nofail and invoke OOM
	 * समाप्तer to move on जबतक costly can fail and users are पढ़ोy
	 * to cope with that. 1/4 retries is rather arbitrary but we
	 * would need much more detailed feedback from compaction to
	 * make a better decision.
	 */
	अगर (order > PAGE_ALLOC_COSTLY_ORDER)
		max_retries /= 4;
	अगर (*compaction_retries <= max_retries) अणु
		ret = true;
		जाओ out;
	पूर्ण

	/*
	 * Make sure there are attempts at the highest priority अगर we exhausted
	 * all retries or failed at the lower priorities.
	 */
check_priority:
	min_priority = (order > PAGE_ALLOC_COSTLY_ORDER) ?
			MIN_COMPACT_COSTLY_PRIORITY : MIN_COMPACT_PRIORITY;

	अगर (*compact_priority > min_priority) अणु
		(*compact_priority)--;
		*compaction_retries = 0;
		ret = true;
	पूर्ण
out:
	trace_compact_retry(order, priority, compact_result, retries, max_retries, ret);
	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा page *
__alloc_pages_direct_compact(gfp_t gfp_mask, अचिन्हित पूर्णांक order,
		अचिन्हित पूर्णांक alloc_flags, स्थिर काष्ठा alloc_context *ac,
		क्रमागत compact_priority prio, क्रमागत compact_result *compact_result)
अणु
	*compact_result = COMPACT_SKIPPED;
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool
should_compact_retry(काष्ठा alloc_context *ac, अचिन्हित पूर्णांक order, पूर्णांक alloc_flags,
		     क्रमागत compact_result compact_result,
		     क्रमागत compact_priority *compact_priority,
		     पूर्णांक *compaction_retries)
अणु
	काष्ठा zone *zone;
	काष्ठा zoneref *z;

	अगर (!order || order > PAGE_ALLOC_COSTLY_ORDER)
		वापस false;

	/*
	 * There are setups with compaction disabled which would prefer to loop
	 * inside the allocator rather than hit the oom समाप्तer prematurely.
	 * Let's give them a good hope and keep retrying जबतक the order-0
	 * watermarks are OK.
	 */
	क्रम_each_zone_zonelist_nodemask(zone, z, ac->zonelist,
				ac->highest_zoneidx, ac->nodemask) अणु
		अगर (zone_watermark_ok(zone, 0, min_wmark_pages(zone),
					ac->highest_zoneidx, alloc_flags))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPACTION */

#अगर_घोषित CONFIG_LOCKDEP
अटल काष्ठा lockdep_map __fs_reclaim_map =
	STATIC_LOCKDEP_MAP_INIT("fs_reclaim", &__fs_reclaim_map);

अटल bool __need_reclaim(gfp_t gfp_mask)
अणु
	/* no reclaim without रुकोing on it */
	अगर (!(gfp_mask & __GFP_सूचीECT_RECLAIM))
		वापस false;

	/* this guy won't enter reclaim */
	अगर (current->flags & PF_MEMALLOC)
		वापस false;

	अगर (gfp_mask & __GFP_NOLOCKDEP)
		वापस false;

	वापस true;
पूर्ण

व्योम __fs_reclaim_acquire(व्योम)
अणु
	lock_map_acquire(&__fs_reclaim_map);
पूर्ण

व्योम __fs_reclaim_release(व्योम)
अणु
	lock_map_release(&__fs_reclaim_map);
पूर्ण

व्योम fs_reclaim_acquire(gfp_t gfp_mask)
अणु
	gfp_mask = current_gfp_context(gfp_mask);

	अगर (__need_reclaim(gfp_mask)) अणु
		अगर (gfp_mask & __GFP_FS)
			__fs_reclaim_acquire();

#अगर_घोषित CONFIG_MMU_NOTIFIER
		lock_map_acquire(&__mmu_notअगरier_invalidate_range_start_map);
		lock_map_release(&__mmu_notअगरier_invalidate_range_start_map);
#पूर्ण_अगर

	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(fs_reclaim_acquire);

व्योम fs_reclaim_release(gfp_t gfp_mask)
अणु
	gfp_mask = current_gfp_context(gfp_mask);

	अगर (__need_reclaim(gfp_mask)) अणु
		अगर (gfp_mask & __GFP_FS)
			__fs_reclaim_release();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(fs_reclaim_release);
#पूर्ण_अगर

/* Perक्रमm direct synchronous page reclaim */
अटल अचिन्हित दीर्घ
__perक्रमm_reclaim(gfp_t gfp_mask, अचिन्हित पूर्णांक order,
					स्थिर काष्ठा alloc_context *ac)
अणु
	अचिन्हित पूर्णांक noreclaim_flag;
	अचिन्हित दीर्घ pflags, progress;

	cond_resched();

	/* We now go पूर्णांकo synchronous reclaim */
	cpuset_memory_pressure_bump();
	psi_memstall_enter(&pflags);
	fs_reclaim_acquire(gfp_mask);
	noreclaim_flag = meदो_स्मृति_noreclaim_save();

	progress = try_to_मुक्त_pages(ac->zonelist, order, gfp_mask,
								ac->nodemask);

	meदो_स्मृति_noreclaim_restore(noreclaim_flag);
	fs_reclaim_release(gfp_mask);
	psi_memstall_leave(&pflags);

	cond_resched();

	वापस progress;
पूर्ण

/* The really slow allocator path where we enter direct reclaim */
अटल अंतरभूत काष्ठा page *
__alloc_pages_direct_reclaim(gfp_t gfp_mask, अचिन्हित पूर्णांक order,
		अचिन्हित पूर्णांक alloc_flags, स्थिर काष्ठा alloc_context *ac,
		अचिन्हित दीर्घ *did_some_progress)
अणु
	काष्ठा page *page = शून्य;
	bool drained = false;

	*did_some_progress = __perक्रमm_reclaim(gfp_mask, order, ac);
	अगर (unlikely(!(*did_some_progress)))
		वापस शून्य;

retry:
	page = get_page_from_मुक्तlist(gfp_mask, order, alloc_flags, ac);

	/*
	 * If an allocation failed after direct reclaim, it could be because
	 * pages are pinned on the per-cpu lists or in high alloc reserves.
	 * Shrink them and try again
	 */
	अगर (!page && !drained) अणु
		unreserve_highatomic_pageblock(ac, false);
		drain_all_pages(शून्य);
		drained = true;
		जाओ retry;
	पूर्ण

	वापस page;
पूर्ण

अटल व्योम wake_all_kswapds(अचिन्हित पूर्णांक order, gfp_t gfp_mask,
			     स्थिर काष्ठा alloc_context *ac)
अणु
	काष्ठा zoneref *z;
	काष्ठा zone *zone;
	pg_data_t *last_pgdat = शून्य;
	क्रमागत zone_type highest_zoneidx = ac->highest_zoneidx;

	क्रम_each_zone_zonelist_nodemask(zone, z, ac->zonelist, highest_zoneidx,
					ac->nodemask) अणु
		अगर (last_pgdat != zone->zone_pgdat)
			wakeup_kswapd(zone, gfp_mask, order, highest_zoneidx);
		last_pgdat = zone->zone_pgdat;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
gfp_to_alloc_flags(gfp_t gfp_mask)
अणु
	अचिन्हित पूर्णांक alloc_flags = ALLOC_WMARK_MIN | ALLOC_CPUSET;

	/*
	 * __GFP_HIGH is assumed to be the same as ALLOC_HIGH
	 * and __GFP_KSWAPD_RECLAIM is assumed to be the same as ALLOC_KSWAPD
	 * to save two branches.
	 */
	BUILD_BUG_ON(__GFP_HIGH != (__क्रमce gfp_t) ALLOC_HIGH);
	BUILD_BUG_ON(__GFP_KSWAPD_RECLAIM != (__क्रमce gfp_t) ALLOC_KSWAPD);

	/*
	 * The caller may dip पूर्णांकo page reserves a bit more अगर the caller
	 * cannot run direct reclaim, or अगर the caller has realसमय scheduling
	 * policy or is asking क्रम __GFP_HIGH memory.  GFP_ATOMIC requests will
	 * set both ALLOC_HARDER (__GFP_ATOMIC) and ALLOC_HIGH (__GFP_HIGH).
	 */
	alloc_flags |= (__क्रमce पूर्णांक)
		(gfp_mask & (__GFP_HIGH | __GFP_KSWAPD_RECLAIM));

	अगर (gfp_mask & __GFP_ATOMIC) अणु
		/*
		 * Not worth trying to allocate harder क्रम __GFP_NOMEMALLOC even
		 * अगर it can't schedule.
		 */
		अगर (!(gfp_mask & __GFP_NOMEMALLOC))
			alloc_flags |= ALLOC_HARDER;
		/*
		 * Ignore cpuset mems क्रम GFP_ATOMIC rather than fail, see the
		 * comment क्रम __cpuset_node_allowed().
		 */
		alloc_flags &= ~ALLOC_CPUSET;
	पूर्ण अन्यथा अगर (unlikely(rt_task(current)) && !in_पूर्णांकerrupt())
		alloc_flags |= ALLOC_HARDER;

	alloc_flags = gfp_to_alloc_flags_cma(gfp_mask, alloc_flags);

	वापस alloc_flags;
पूर्ण

अटल bool oom_reserves_allowed(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (!tsk_is_oom_victim(tsk))
		वापस false;

	/*
	 * !MMU करोesn't have oom reaper so give access to memory reserves
	 * only to the thपढ़ो with TIF_MEMDIE set
	 */
	अगर (!IS_ENABLED(CONFIG_MMU) && !test_thपढ़ो_flag(TIF_MEMDIE))
		वापस false;

	वापस true;
पूर्ण

/*
 * Distinguish requests which really need access to full memory
 * reserves from oom victims which can live with a portion of it
 */
अटल अंतरभूत पूर्णांक __gfp_pfmeदो_स्मृति_flags(gfp_t gfp_mask)
अणु
	अगर (unlikely(gfp_mask & __GFP_NOMEMALLOC))
		वापस 0;
	अगर (gfp_mask & __GFP_MEMALLOC)
		वापस ALLOC_NO_WATERMARKS;
	अगर (in_serving_softirq() && (current->flags & PF_MEMALLOC))
		वापस ALLOC_NO_WATERMARKS;
	अगर (!in_पूर्णांकerrupt()) अणु
		अगर (current->flags & PF_MEMALLOC)
			वापस ALLOC_NO_WATERMARKS;
		अन्यथा अगर (oom_reserves_allowed(current))
			वापस ALLOC_OOM;
	पूर्ण

	वापस 0;
पूर्ण

bool gfp_pfmeदो_स्मृति_allowed(gfp_t gfp_mask)
अणु
	वापस !!__gfp_pfmeदो_स्मृति_flags(gfp_mask);
पूर्ण

/*
 * Checks whether it makes sense to retry the reclaim to make a क्रमward progress
 * क्रम the given allocation request.
 *
 * We give up when we either have tried MAX_RECLAIM_RETRIES in a row
 * without success, or when we couldn't even meet the watermark अगर we
 * reclaimed all reमुख्यing pages on the LRU lists.
 *
 * Returns true अगर a retry is viable or false to enter the oom path.
 */
अटल अंतरभूत bool
should_reclaim_retry(gfp_t gfp_mask, अचिन्हित order,
		     काष्ठा alloc_context *ac, पूर्णांक alloc_flags,
		     bool did_some_progress, पूर्णांक *no_progress_loops)
अणु
	काष्ठा zone *zone;
	काष्ठा zoneref *z;
	bool ret = false;

	/*
	 * Costly allocations might have made a progress but this करोesn't mean
	 * their order will become available due to high fragmentation so
	 * always increment the no progress counter क्रम them
	 */
	अगर (did_some_progress && order <= PAGE_ALLOC_COSTLY_ORDER)
		*no_progress_loops = 0;
	अन्यथा
		(*no_progress_loops)++;

	/*
	 * Make sure we converge to OOM अगर we cannot make any progress
	 * several बार in the row.
	 */
	अगर (*no_progress_loops > MAX_RECLAIM_RETRIES) अणु
		/* Beक्रमe OOM, exhaust highatomic_reserve */
		वापस unreserve_highatomic_pageblock(ac, true);
	पूर्ण

	/*
	 * Keep reclaiming pages जबतक there is a chance this will lead
	 * somewhere.  If none of the target zones can satisfy our allocation
	 * request even अगर all reclaimable pages are considered then we are
	 * screwed and have to go OOM.
	 */
	क्रम_each_zone_zonelist_nodemask(zone, z, ac->zonelist,
				ac->highest_zoneidx, ac->nodemask) अणु
		अचिन्हित दीर्घ available;
		अचिन्हित दीर्घ reclaimable;
		अचिन्हित दीर्घ min_wmark = min_wmark_pages(zone);
		bool wmark;

		available = reclaimable = zone_reclaimable_pages(zone);
		available += zone_page_state_snapshot(zone, NR_FREE_PAGES);

		/*
		 * Would the allocation succeed अगर we reclaimed all
		 * reclaimable pages?
		 */
		wmark = __zone_watermark_ok(zone, order, min_wmark,
				ac->highest_zoneidx, alloc_flags, available);
		trace_reclaim_retry_zone(z, order, reclaimable,
				available, min_wmark, *no_progress_loops, wmark);
		अगर (wmark) अणु
			/*
			 * If we didn't make any progress and have a lot of
			 * dirty + ग_लिखोback pages then we should रुको क्रम
			 * an IO to complete to slow करोwn the reclaim and
			 * prevent from pre mature OOM
			 */
			अगर (!did_some_progress) अणु
				अचिन्हित दीर्घ ग_लिखो_pending;

				ग_लिखो_pending = zone_page_state_snapshot(zone,
							NR_ZONE_WRITE_PENDING);

				अगर (2 * ग_लिखो_pending > reclaimable) अणु
					congestion_रुको(BLK_RW_ASYNC, HZ/10);
					वापस true;
				पूर्ण
			पूर्ण

			ret = true;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	/*
	 * Memory allocation/reclaim might be called from a WQ context and the
	 * current implementation of the WQ concurrency control करोesn't
	 * recognize that a particular WQ is congested अगर the worker thपढ़ो is
	 * looping without ever sleeping. Thereक्रमe we have to करो a लघु sleep
	 * here rather than calling cond_resched().
	 */
	अगर (current->flags & PF_WQ_WORKER)
		schedule_समयout_unपूर्णांकerruptible(1);
	अन्यथा
		cond_resched();
	वापस ret;
पूर्ण

अटल अंतरभूत bool
check_retry_cpuset(पूर्णांक cpuset_mems_cookie, काष्ठा alloc_context *ac)
अणु
	/*
	 * It's possible that cpuset's mems_allowed and the nodemask from
	 * mempolicy करोn't पूर्णांकersect. This should be normally dealt with by
	 * policy_nodemask(), but it's possible to race with cpuset update in
	 * such a way the check therein was true, and then it became false
	 * beक्रमe we got our cpuset_mems_cookie here.
	 * This assumes that क्रम all allocations, ac->nodemask can come only
	 * from MPOL_BIND mempolicy (whose करोcumented semantics is to be ignored
	 * when it करोes not पूर्णांकersect with the cpuset restrictions) or the
	 * caller can deal with a violated nodemask.
	 */
	अगर (cpusets_enabled() && ac->nodemask &&
			!cpuset_nodemask_valid_mems_allowed(ac->nodemask)) अणु
		ac->nodemask = शून्य;
		वापस true;
	पूर्ण

	/*
	 * When updating a task's mems_allowed or mempolicy nodemask, it is
	 * possible to race with parallel thपढ़ोs in such a way that our
	 * allocation can fail जबतक the mask is being updated. If we are about
	 * to fail, check अगर the cpuset changed during allocation and अगर so,
	 * retry.
	 */
	अगर (पढ़ो_mems_allowed_retry(cpuset_mems_cookie))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा page *
__alloc_pages_slowpath(gfp_t gfp_mask, अचिन्हित पूर्णांक order,
						काष्ठा alloc_context *ac)
अणु
	bool can_direct_reclaim = gfp_mask & __GFP_सूचीECT_RECLAIM;
	स्थिर bool costly_order = order > PAGE_ALLOC_COSTLY_ORDER;
	काष्ठा page *page = शून्य;
	अचिन्हित पूर्णांक alloc_flags;
	अचिन्हित दीर्घ did_some_progress;
	क्रमागत compact_priority compact_priority;
	क्रमागत compact_result compact_result;
	पूर्णांक compaction_retries;
	पूर्णांक no_progress_loops;
	अचिन्हित पूर्णांक cpuset_mems_cookie;
	पूर्णांक reserve_flags;

	/*
	 * We also sanity check to catch abuse of atomic reserves being used by
	 * callers that are not in atomic context.
	 */
	अगर (WARN_ON_ONCE((gfp_mask & (__GFP_ATOMIC|__GFP_सूचीECT_RECLAIM)) ==
				(__GFP_ATOMIC|__GFP_सूचीECT_RECLAIM)))
		gfp_mask &= ~__GFP_ATOMIC;

retry_cpuset:
	compaction_retries = 0;
	no_progress_loops = 0;
	compact_priority = DEF_COMPACT_PRIORITY;
	cpuset_mems_cookie = पढ़ो_mems_allowed_begin();

	/*
	 * The fast path uses conservative alloc_flags to succeed only until
	 * kswapd needs to be woken up, and to aव्योम the cost of setting up
	 * alloc_flags precisely. So we करो that now.
	 */
	alloc_flags = gfp_to_alloc_flags(gfp_mask);

	/*
	 * We need to recalculate the starting poपूर्णांक क्रम the zonelist iterator
	 * because we might have used dअगरferent nodemask in the fast path, or
	 * there was a cpuset modअगरication and we are retrying - otherwise we
	 * could end up iterating over non-eligible zones endlessly.
	 */
	ac->preferred_zoneref = first_zones_zonelist(ac->zonelist,
					ac->highest_zoneidx, ac->nodemask);
	अगर (!ac->preferred_zoneref->zone)
		जाओ nopage;

	अगर (alloc_flags & ALLOC_KSWAPD)
		wake_all_kswapds(order, gfp_mask, ac);

	/*
	 * The adjusted alloc_flags might result in immediate success, so try
	 * that first
	 */
	page = get_page_from_मुक्तlist(gfp_mask, order, alloc_flags, ac);
	अगर (page)
		जाओ got_pg;

	/*
	 * For costly allocations, try direct compaction first, as it's likely
	 * that we have enough base pages and करोn't need to reclaim. For non-
	 * movable high-order allocations, करो that as well, as compaction will
	 * try prevent permanent fragmentation by migrating from blocks of the
	 * same migratetype.
	 * Don't try this क्रम allocations that are allowed to ignore
	 * watermarks, as the ALLOC_NO_WATERMARKS attempt didn't yet happen.
	 */
	अगर (can_direct_reclaim &&
			(costly_order ||
			   (order > 0 && ac->migratetype != MIGRATE_MOVABLE))
			&& !gfp_pfmeदो_स्मृति_allowed(gfp_mask)) अणु
		page = __alloc_pages_direct_compact(gfp_mask, order,
						alloc_flags, ac,
						INIT_COMPACT_PRIORITY,
						&compact_result);
		अगर (page)
			जाओ got_pg;

		/*
		 * Checks क्रम costly allocations with __GFP_NORETRY, which
		 * includes some THP page fault allocations
		 */
		अगर (costly_order && (gfp_mask & __GFP_NORETRY)) अणु
			/*
			 * If allocating entire pageblock(s) and compaction
			 * failed because all zones are below low watermarks
			 * or is prohibited because it recently failed at this
			 * order, fail immediately unless the allocator has
			 * requested compaction and reclaim retry.
			 *
			 * Reclaim is
			 *  - potentially very expensive because zones are far
			 *    below their low watermarks or this is part of very
			 *    bursty high order allocations,
			 *  - not guaranteed to help because isolate_मुक्तpages()
			 *    may not iterate over मुक्तd pages as part of its
			 *    linear scan, and
			 *  - unlikely to make entire pageblocks मुक्त on its
			 *    own.
			 */
			अगर (compact_result == COMPACT_SKIPPED ||
			    compact_result == COMPACT_DEFERRED)
				जाओ nopage;

			/*
			 * Looks like reclaim/compaction is worth trying, but
			 * sync compaction could be very expensive, so keep
			 * using async compaction.
			 */
			compact_priority = INIT_COMPACT_PRIORITY;
		पूर्ण
	पूर्ण

retry:
	/* Ensure kswapd करोesn't accidentally go to sleep as दीर्घ as we loop */
	अगर (alloc_flags & ALLOC_KSWAPD)
		wake_all_kswapds(order, gfp_mask, ac);

	reserve_flags = __gfp_pfmeदो_स्मृति_flags(gfp_mask);
	अगर (reserve_flags)
		alloc_flags = gfp_to_alloc_flags_cma(gfp_mask, reserve_flags);

	/*
	 * Reset the nodemask and zonelist iterators अगर memory policies can be
	 * ignored. These allocations are high priority and प्रणाली rather than
	 * user oriented.
	 */
	अगर (!(alloc_flags & ALLOC_CPUSET) || reserve_flags) अणु
		ac->nodemask = शून्य;
		ac->preferred_zoneref = first_zones_zonelist(ac->zonelist,
					ac->highest_zoneidx, ac->nodemask);
	पूर्ण

	/* Attempt with potentially adjusted zonelist and alloc_flags */
	page = get_page_from_मुक्तlist(gfp_mask, order, alloc_flags, ac);
	अगर (page)
		जाओ got_pg;

	/* Caller is not willing to reclaim, we can't balance anything */
	अगर (!can_direct_reclaim)
		जाओ nopage;

	/* Aव्योम recursion of direct reclaim */
	अगर (current->flags & PF_MEMALLOC)
		जाओ nopage;

	/* Try direct reclaim and then allocating */
	page = __alloc_pages_direct_reclaim(gfp_mask, order, alloc_flags, ac,
							&did_some_progress);
	अगर (page)
		जाओ got_pg;

	/* Try direct compaction and then allocating */
	page = __alloc_pages_direct_compact(gfp_mask, order, alloc_flags, ac,
					compact_priority, &compact_result);
	अगर (page)
		जाओ got_pg;

	/* Do not loop अगर specअगरically requested */
	अगर (gfp_mask & __GFP_NORETRY)
		जाओ nopage;

	/*
	 * Do not retry costly high order allocations unless they are
	 * __GFP_RETRY_MAYFAIL
	 */
	अगर (costly_order && !(gfp_mask & __GFP_RETRY_MAYFAIL))
		जाओ nopage;

	अगर (should_reclaim_retry(gfp_mask, order, ac, alloc_flags,
				 did_some_progress > 0, &no_progress_loops))
		जाओ retry;

	/*
	 * It करोesn't make any sense to retry क्रम the compaction अगर the order-0
	 * reclaim is not able to make any progress because the current
	 * implementation of the compaction depends on the sufficient amount
	 * of मुक्त memory (see __compaction_suitable)
	 */
	अगर (did_some_progress > 0 &&
			should_compact_retry(ac, order, alloc_flags,
				compact_result, &compact_priority,
				&compaction_retries))
		जाओ retry;


	/* Deal with possible cpuset update races beक्रमe we start OOM समाप्तing */
	अगर (check_retry_cpuset(cpuset_mems_cookie, ac))
		जाओ retry_cpuset;

	/* Reclaim has failed us, start समाप्तing things */
	page = __alloc_pages_may_oom(gfp_mask, order, ac, &did_some_progress);
	अगर (page)
		जाओ got_pg;

	/* Aव्योम allocations with no watermarks from looping endlessly */
	अगर (tsk_is_oom_victim(current) &&
	    (alloc_flags & ALLOC_OOM ||
	     (gfp_mask & __GFP_NOMEMALLOC)))
		जाओ nopage;

	/* Retry as दीर्घ as the OOM समाप्तer is making progress */
	अगर (did_some_progress) अणु
		no_progress_loops = 0;
		जाओ retry;
	पूर्ण

nopage:
	/* Deal with possible cpuset update races beक्रमe we fail */
	अगर (check_retry_cpuset(cpuset_mems_cookie, ac))
		जाओ retry_cpuset;

	/*
	 * Make sure that __GFP_NOFAIL request करोesn't leak out and make sure
	 * we always retry
	 */
	अगर (gfp_mask & __GFP_NOFAIL) अणु
		/*
		 * All existing users of the __GFP_NOFAIL are blockable, so warn
		 * of any new users that actually require GFP_NOWAIT
		 */
		अगर (WARN_ON_ONCE(!can_direct_reclaim))
			जाओ fail;

		/*
		 * PF_MEMALLOC request from this context is rather bizarre
		 * because we cannot reclaim anything and only can loop रुकोing
		 * क्रम somebody to करो a work क्रम us
		 */
		WARN_ON_ONCE(current->flags & PF_MEMALLOC);

		/*
		 * non failing costly orders are a hard requirement which we
		 * are not prepared क्रम much so let's warn about these users
		 * so that we can identअगरy them and convert them to something
		 * अन्यथा.
		 */
		WARN_ON_ONCE(order > PAGE_ALLOC_COSTLY_ORDER);

		/*
		 * Help non-failing allocations by giving them access to memory
		 * reserves but करो not use ALLOC_NO_WATERMARKS because this
		 * could deplete whole memory reserves which would just make
		 * the situation worse
		 */
		page = __alloc_pages_cpuset_fallback(gfp_mask, order, ALLOC_HARDER, ac);
		अगर (page)
			जाओ got_pg;

		cond_resched();
		जाओ retry;
	पूर्ण
fail:
	warn_alloc(gfp_mask, ac->nodemask,
			"page allocation failure: order:%u", order);
got_pg:
	वापस page;
पूर्ण

अटल अंतरभूत bool prepare_alloc_pages(gfp_t gfp_mask, अचिन्हित पूर्णांक order,
		पूर्णांक preferred_nid, nodemask_t *nodemask,
		काष्ठा alloc_context *ac, gfp_t *alloc_gfp,
		अचिन्हित पूर्णांक *alloc_flags)
अणु
	ac->highest_zoneidx = gfp_zone(gfp_mask);
	ac->zonelist = node_zonelist(preferred_nid, gfp_mask);
	ac->nodemask = nodemask;
	ac->migratetype = gfp_migratetype(gfp_mask);

	अगर (cpusets_enabled()) अणु
		*alloc_gfp |= __GFP_HARDWALL;
		/*
		 * When we are in the पूर्णांकerrupt context, it is irrelevant
		 * to the current task context. It means that any node ok.
		 */
		अगर (!in_पूर्णांकerrupt() && !ac->nodemask)
			ac->nodemask = &cpuset_current_mems_allowed;
		अन्यथा
			*alloc_flags |= ALLOC_CPUSET;
	पूर्ण

	fs_reclaim_acquire(gfp_mask);
	fs_reclaim_release(gfp_mask);

	might_sleep_अगर(gfp_mask & __GFP_सूचीECT_RECLAIM);

	अगर (should_fail_alloc_page(gfp_mask, order))
		वापस false;

	*alloc_flags = gfp_to_alloc_flags_cma(gfp_mask, *alloc_flags);

	/* Dirty zone balancing only करोne in the fast path */
	ac->spपढ़ो_dirty_pages = (gfp_mask & __GFP_WRITE);

	/*
	 * The preferred zone is used क्रम statistics but crucially it is
	 * also used as the starting poपूर्णांक क्रम the zonelist iterator. It
	 * may get reset क्रम allocations that ignore memory policies.
	 */
	ac->preferred_zoneref = first_zones_zonelist(ac->zonelist,
					ac->highest_zoneidx, ac->nodemask);

	वापस true;
पूर्ण

/*
 * __alloc_pages_bulk - Allocate a number of order-0 pages to a list or array
 * @gfp: GFP flags क्रम the allocation
 * @preferred_nid: The preferred NUMA node ID to allocate from
 * @nodemask: Set of nodes to allocate from, may be शून्य
 * @nr_pages: The number of pages desired on the list or array
 * @page_list: Optional list to store the allocated pages
 * @page_array: Optional array to store the pages
 *
 * This is a batched version of the page allocator that attempts to
 * allocate nr_pages quickly. Pages are added to page_list अगर page_list
 * is not शून्य, otherwise it is assumed that the page_array is valid.
 *
 * For lists, nr_pages is the number of pages that should be allocated.
 *
 * For arrays, only शून्य elements are populated with pages and nr_pages
 * is the maximum number of pages that will be stored in the array.
 *
 * Returns the number of pages on the list or array.
 */
अचिन्हित दीर्घ __alloc_pages_bulk(gfp_t gfp, पूर्णांक preferred_nid,
			nodemask_t *nodemask, पूर्णांक nr_pages,
			काष्ठा list_head *page_list,
			काष्ठा page **page_array)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ flags;
	काष्ठा zone *zone;
	काष्ठा zoneref *z;
	काष्ठा per_cpu_pages *pcp;
	काष्ठा list_head *pcp_list;
	काष्ठा alloc_context ac;
	gfp_t alloc_gfp;
	अचिन्हित पूर्णांक alloc_flags = ALLOC_WMARK_LOW;
	पूर्णांक nr_populated = 0;

	अगर (unlikely(nr_pages <= 0))
		वापस 0;

	/*
	 * Skip populated array elements to determine अगर any pages need
	 * to be allocated beक्रमe disabling IRQs.
	 */
	जबतक (page_array && page_array[nr_populated] && nr_populated < nr_pages)
		nr_populated++;

	/* Use the single page allocator क्रम one page. */
	अगर (nr_pages - nr_populated == 1)
		जाओ failed;

	/* May set ALLOC_NOFRAGMENT, fragmentation will वापस 1 page. */
	gfp &= gfp_allowed_mask;
	alloc_gfp = gfp;
	अगर (!prepare_alloc_pages(gfp, 0, preferred_nid, nodemask, &ac, &alloc_gfp, &alloc_flags))
		वापस 0;
	gfp = alloc_gfp;

	/* Find an allowed local zone that meets the low watermark. */
	क्रम_each_zone_zonelist_nodemask(zone, z, ac.zonelist, ac.highest_zoneidx, ac.nodemask) अणु
		अचिन्हित दीर्घ mark;

		अगर (cpusets_enabled() && (alloc_flags & ALLOC_CPUSET) &&
		    !__cpuset_zone_allowed(zone, gfp)) अणु
			जारी;
		पूर्ण

		अगर (nr_online_nodes > 1 && zone != ac.preferred_zoneref->zone &&
		    zone_to_nid(zone) != zone_to_nid(ac.preferred_zoneref->zone)) अणु
			जाओ failed;
		पूर्ण

		mark = wmark_pages(zone, alloc_flags & ALLOC_WMARK_MASK) + nr_pages;
		अगर (zone_watermark_fast(zone, 0,  mark,
				zonelist_zone_idx(ac.preferred_zoneref),
				alloc_flags, gfp)) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If there are no allowed local zones that meets the watermarks then
	 * try to allocate a single page and reclaim अगर necessary.
	 */
	अगर (unlikely(!zone))
		जाओ failed;

	/* Attempt the batch allocation */
	local_irq_save(flags);
	pcp = &this_cpu_ptr(zone->pageset)->pcp;
	pcp_list = &pcp->lists[ac.migratetype];

	जबतक (nr_populated < nr_pages) अणु

		/* Skip existing pages */
		अगर (page_array && page_array[nr_populated]) अणु
			nr_populated++;
			जारी;
		पूर्ण

		page = __rmqueue_pcplist(zone, ac.migratetype, alloc_flags,
								pcp, pcp_list);
		अगर (unlikely(!page)) अणु
			/* Try and get at least one page */
			अगर (!nr_populated)
				जाओ failed_irq;
			अवरोध;
		पूर्ण

		/*
		 * Ideally this would be batched but the best way to करो
		 * that cheaply is to first convert zone_statistics to
		 * be inaccurate per-cpu counter like vm_events to aव्योम
		 * a RMW cycle then करो the accounting with IRQs enabled.
		 */
		__count_zid_vm_events(PGALLOC, zone_idx(zone), 1);
		zone_statistics(ac.preferred_zoneref->zone, zone);

		prep_new_page(page, 0, gfp, 0);
		अगर (page_list)
			list_add(&page->lru, page_list);
		अन्यथा
			page_array[nr_populated] = page;
		nr_populated++;
	पूर्ण

	local_irq_restore(flags);

	वापस nr_populated;

failed_irq:
	local_irq_restore(flags);

failed:
	page = __alloc_pages(gfp, 0, preferred_nid, nodemask);
	अगर (page) अणु
		अगर (page_list)
			list_add(&page->lru, page_list);
		अन्यथा
			page_array[nr_populated] = page;
		nr_populated++;
	पूर्ण

	वापस nr_populated;
पूर्ण
EXPORT_SYMBOL_GPL(__alloc_pages_bulk);

/*
 * This is the 'heart' of the zoned buddy allocator.
 */
काष्ठा page *__alloc_pages(gfp_t gfp, अचिन्हित पूर्णांक order, पूर्णांक preferred_nid,
							nodemask_t *nodemask)
अणु
	काष्ठा page *page;
	अचिन्हित पूर्णांक alloc_flags = ALLOC_WMARK_LOW;
	gfp_t alloc_gfp; /* The gfp_t that was actually used क्रम allocation */
	काष्ठा alloc_context ac = अणु पूर्ण;

	/*
	 * There are several places where we assume that the order value is sane
	 * so bail out early अगर the request is out of bound.
	 */
	अगर (unlikely(order >= MAX_ORDER)) अणु
		WARN_ON_ONCE(!(gfp & __GFP_NOWARN));
		वापस शून्य;
	पूर्ण

	gfp &= gfp_allowed_mask;
	/*
	 * Apply scoped allocation स्थिरraपूर्णांकs. This is मुख्यly about GFP_NOFS
	 * resp. GFP_NOIO which has to be inherited क्रम all allocation requests
	 * from a particular context which has been marked by
	 * meदो_स्मृति_noअणुfs,ioपूर्ण_अणुsave,restoreपूर्ण. And PF_MEMALLOC_PIN which ensures
	 * movable zones are not used during allocation.
	 */
	gfp = current_gfp_context(gfp);
	alloc_gfp = gfp;
	अगर (!prepare_alloc_pages(gfp, order, preferred_nid, nodemask, &ac,
			&alloc_gfp, &alloc_flags))
		वापस शून्य;

	/*
	 * Forbid the first pass from falling back to types that fragment
	 * memory until all local zones are considered.
	 */
	alloc_flags |= alloc_flags_nofragment(ac.preferred_zoneref->zone, gfp);

	/* First allocation attempt */
	page = get_page_from_मुक्तlist(alloc_gfp, order, alloc_flags, &ac);
	अगर (likely(page))
		जाओ out;

	alloc_gfp = gfp;
	ac.spपढ़ो_dirty_pages = false;

	/*
	 * Restore the original nodemask अगर it was potentially replaced with
	 * &cpuset_current_mems_allowed to optimize the fast-path attempt.
	 */
	ac.nodemask = nodemask;

	page = __alloc_pages_slowpath(alloc_gfp, order, &ac);

out:
	अगर (memcg_kmem_enabled() && (gfp & __GFP_ACCOUNT) && page &&
	    unlikely(__memcg_kmem_अक्षरge_page(page, gfp, order) != 0)) अणु
		__मुक्त_pages(page, order);
		page = शून्य;
	पूर्ण

	trace_mm_page_alloc(page, order, alloc_gfp, ac.migratetype);

	वापस page;
पूर्ण
EXPORT_SYMBOL(__alloc_pages);

/*
 * Common helper functions. Never use with __GFP_HIGHMEM because the वापसed
 * address cannot represent highmem pages. Use alloc_pages and then kmap अगर
 * you need to access high mem.
 */
अचिन्हित दीर्घ __get_मुक्त_pages(gfp_t gfp_mask, अचिन्हित पूर्णांक order)
अणु
	काष्ठा page *page;

	page = alloc_pages(gfp_mask & ~__GFP_HIGHMEM, order);
	अगर (!page)
		वापस 0;
	वापस (अचिन्हित दीर्घ) page_address(page);
पूर्ण
EXPORT_SYMBOL(__get_मुक्त_pages);

अचिन्हित दीर्घ get_zeroed_page(gfp_t gfp_mask)
अणु
	वापस __get_मुक्त_pages(gfp_mask | __GFP_ZERO, 0);
पूर्ण
EXPORT_SYMBOL(get_zeroed_page);

अटल अंतरभूत व्योम मुक्त_the_page(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	अगर (order == 0)		/* Via pcp? */
		मुक्त_unref_page(page);
	अन्यथा
		__मुक्त_pages_ok(page, order, FPI_NONE);
पूर्ण

/**
 * __मुक्त_pages - Free pages allocated with alloc_pages().
 * @page: The page poपूर्णांकer वापसed from alloc_pages().
 * @order: The order of the allocation.
 *
 * This function can मुक्त multi-page allocations that are not compound
 * pages.  It करोes not check that the @order passed in matches that of
 * the allocation, so it is easy to leak memory.  Freeing more memory
 * than was allocated will probably emit a warning.
 *
 * If the last reference to this page is speculative, it will be released
 * by put_page() which only मुक्तs the first page of a non-compound
 * allocation.  To prevent the reमुख्यing pages from being leaked, we मुक्त
 * the subsequent pages here.  If you want to use the page's reference
 * count to decide when to मुक्त the allocation, you should allocate a
 * compound page, and use put_page() instead of __मुक्त_pages().
 *
 * Context: May be called in पूर्णांकerrupt context or जबतक holding a normal
 * spinlock, but not in NMI context or जबतक holding a raw spinlock.
 */
व्योम __मुक्त_pages(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	अगर (put_page_testzero(page))
		मुक्त_the_page(page, order);
	अन्यथा अगर (!PageHead(page))
		जबतक (order-- > 0)
			मुक्त_the_page(page + (1 << order), order);
पूर्ण
EXPORT_SYMBOL(__मुक्त_pages);

व्योम मुक्त_pages(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक order)
अणु
	अगर (addr != 0) अणु
		VM_BUG_ON(!virt_addr_valid((व्योम *)addr));
		__मुक्त_pages(virt_to_page((व्योम *)addr), order);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(मुक्त_pages);

/*
 * Page Fragment:
 *  An arbitrary-length arbitrary-offset area of memory which resides
 *  within a 0 or higher order page.  Multiple fragments within that page
 *  are inभागidually refcounted, in the page's reference counter.
 *
 * The page_frag functions below provide a simple allocation framework क्रम
 * page fragments.  This is used by the network stack and network device
 * drivers to provide a backing region of memory क्रम use as either an
 * sk_buff->head, or to be used in the "frags" portion of skb_shared_info.
 */
अटल काष्ठा page *__page_frag_cache_refill(काष्ठा page_frag_cache *nc,
					     gfp_t gfp_mask)
अणु
	काष्ठा page *page = शून्य;
	gfp_t gfp = gfp_mask;

#अगर (PAGE_SIZE < PAGE_FRAG_CACHE_MAX_SIZE)
	gfp_mask |= __GFP_COMP | __GFP_NOWARN | __GFP_NORETRY |
		    __GFP_NOMEMALLOC;
	page = alloc_pages_node(NUMA_NO_NODE, gfp_mask,
				PAGE_FRAG_CACHE_MAX_ORDER);
	nc->size = page ? PAGE_FRAG_CACHE_MAX_SIZE : PAGE_SIZE;
#पूर्ण_अगर
	अगर (unlikely(!page))
		page = alloc_pages_node(NUMA_NO_NODE, gfp, 0);

	nc->va = page ? page_address(page) : शून्य;

	वापस page;
पूर्ण

व्योम __page_frag_cache_drain(काष्ठा page *page, अचिन्हित पूर्णांक count)
अणु
	VM_BUG_ON_PAGE(page_ref_count(page) == 0, page);

	अगर (page_ref_sub_and_test(page, count))
		मुक्त_the_page(page, compound_order(page));
पूर्ण
EXPORT_SYMBOL(__page_frag_cache_drain);

व्योम *page_frag_alloc_align(काष्ठा page_frag_cache *nc,
		      अचिन्हित पूर्णांक fragsz, gfp_t gfp_mask,
		      अचिन्हित पूर्णांक align_mask)
अणु
	अचिन्हित पूर्णांक size = PAGE_SIZE;
	काष्ठा page *page;
	पूर्णांक offset;

	अगर (unlikely(!nc->va)) अणु
refill:
		page = __page_frag_cache_refill(nc, gfp_mask);
		अगर (!page)
			वापस शून्य;

#अगर (PAGE_SIZE < PAGE_FRAG_CACHE_MAX_SIZE)
		/* अगर size can vary use size अन्यथा just use PAGE_SIZE */
		size = nc->size;
#पूर्ण_अगर
		/* Even अगर we own the page, we करो not use atomic_set().
		 * This would अवरोध get_page_unless_zero() users.
		 */
		page_ref_add(page, PAGE_FRAG_CACHE_MAX_SIZE);

		/* reset page count bias and offset to start of new frag */
		nc->pfmeदो_स्मृति = page_is_pfmeदो_स्मृति(page);
		nc->pagecnt_bias = PAGE_FRAG_CACHE_MAX_SIZE + 1;
		nc->offset = size;
	पूर्ण

	offset = nc->offset - fragsz;
	अगर (unlikely(offset < 0)) अणु
		page = virt_to_page(nc->va);

		अगर (!page_ref_sub_and_test(page, nc->pagecnt_bias))
			जाओ refill;

		अगर (unlikely(nc->pfmeदो_स्मृति)) अणु
			मुक्त_the_page(page, compound_order(page));
			जाओ refill;
		पूर्ण

#अगर (PAGE_SIZE < PAGE_FRAG_CACHE_MAX_SIZE)
		/* अगर size can vary use size अन्यथा just use PAGE_SIZE */
		size = nc->size;
#पूर्ण_अगर
		/* OK, page count is 0, we can safely set it */
		set_page_count(page, PAGE_FRAG_CACHE_MAX_SIZE + 1);

		/* reset page count bias and offset to start of new frag */
		nc->pagecnt_bias = PAGE_FRAG_CACHE_MAX_SIZE + 1;
		offset = size - fragsz;
	पूर्ण

	nc->pagecnt_bias--;
	offset &= align_mask;
	nc->offset = offset;

	वापस nc->va + offset;
पूर्ण
EXPORT_SYMBOL(page_frag_alloc_align);

/*
 * Frees a page fragment allocated out of either a compound or order 0 page.
 */
व्योम page_frag_मुक्त(व्योम *addr)
अणु
	काष्ठा page *page = virt_to_head_page(addr);

	अगर (unlikely(put_page_testzero(page)))
		मुक्त_the_page(page, compound_order(page));
पूर्ण
EXPORT_SYMBOL(page_frag_मुक्त);

अटल व्योम *make_alloc_exact(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक order,
		माप_प्रकार size)
अणु
	अगर (addr) अणु
		अचिन्हित दीर्घ alloc_end = addr + (PAGE_SIZE << order);
		अचिन्हित दीर्घ used = addr + PAGE_ALIGN(size);

		split_page(virt_to_page((व्योम *)addr), order);
		जबतक (used < alloc_end) अणु
			मुक्त_page(used);
			used += PAGE_SIZE;
		पूर्ण
	पूर्ण
	वापस (व्योम *)addr;
पूर्ण

/**
 * alloc_pages_exact - allocate an exact number physically-contiguous pages.
 * @size: the number of bytes to allocate
 * @gfp_mask: GFP flags क्रम the allocation, must not contain __GFP_COMP
 *
 * This function is similar to alloc_pages(), except that it allocates the
 * minimum number of pages to satisfy the request.  alloc_pages() can only
 * allocate memory in घातer-of-two pages.
 *
 * This function is also limited by MAX_ORDER.
 *
 * Memory allocated by this function must be released by मुक्त_pages_exact().
 *
 * Return: poपूर्णांकer to the allocated area or %शून्य in हाल of error.
 */
व्योम *alloc_pages_exact(माप_प्रकार size, gfp_t gfp_mask)
अणु
	अचिन्हित पूर्णांक order = get_order(size);
	अचिन्हित दीर्घ addr;

	अगर (WARN_ON_ONCE(gfp_mask & __GFP_COMP))
		gfp_mask &= ~__GFP_COMP;

	addr = __get_मुक्त_pages(gfp_mask, order);
	वापस make_alloc_exact(addr, order, size);
पूर्ण
EXPORT_SYMBOL(alloc_pages_exact);

/**
 * alloc_pages_exact_nid - allocate an exact number of physically-contiguous
 *			   pages on a node.
 * @nid: the preferred node ID where memory should be allocated
 * @size: the number of bytes to allocate
 * @gfp_mask: GFP flags क्रम the allocation, must not contain __GFP_COMP
 *
 * Like alloc_pages_exact(), but try to allocate on node nid first beक्रमe falling
 * back.
 *
 * Return: poपूर्णांकer to the allocated area or %शून्य in हाल of error.
 */
व्योम * __meminit alloc_pages_exact_nid(पूर्णांक nid, माप_प्रकार size, gfp_t gfp_mask)
अणु
	अचिन्हित पूर्णांक order = get_order(size);
	काष्ठा page *p;

	अगर (WARN_ON_ONCE(gfp_mask & __GFP_COMP))
		gfp_mask &= ~__GFP_COMP;

	p = alloc_pages_node(nid, gfp_mask, order);
	अगर (!p)
		वापस शून्य;
	वापस make_alloc_exact((अचिन्हित दीर्घ)page_address(p), order, size);
पूर्ण

/**
 * मुक्त_pages_exact - release memory allocated via alloc_pages_exact()
 * @virt: the value वापसed by alloc_pages_exact.
 * @size: size of allocation, same value as passed to alloc_pages_exact().
 *
 * Release the memory allocated by a previous call to alloc_pages_exact.
 */
व्योम मुक्त_pages_exact(व्योम *virt, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)virt;
	अचिन्हित दीर्घ end = addr + PAGE_ALIGN(size);

	जबतक (addr < end) अणु
		मुक्त_page(addr);
		addr += PAGE_SIZE;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(मुक्त_pages_exact);

/**
 * nr_मुक्त_zone_pages - count number of pages beyond high watermark
 * @offset: The zone index of the highest zone
 *
 * nr_मुक्त_zone_pages() counts the number of pages which are beyond the
 * high watermark within all zones at or below a given zone index.  For each
 * zone, the number of pages is calculated as:
 *
 *     nr_मुक्त_zone_pages = managed_pages - high_pages
 *
 * Return: number of pages beyond high watermark.
 */
अटल अचिन्हित दीर्घ nr_मुक्त_zone_pages(पूर्णांक offset)
अणु
	काष्ठा zoneref *z;
	काष्ठा zone *zone;

	/* Just pick one node, since fallback list is circular */
	अचिन्हित दीर्घ sum = 0;

	काष्ठा zonelist *zonelist = node_zonelist(numa_node_id(), GFP_KERNEL);

	क्रम_each_zone_zonelist(zone, z, zonelist, offset) अणु
		अचिन्हित दीर्घ size = zone_managed_pages(zone);
		अचिन्हित दीर्घ high = high_wmark_pages(zone);
		अगर (size > high)
			sum += size - high;
	पूर्ण

	वापस sum;
पूर्ण

/**
 * nr_मुक्त_buffer_pages - count number of pages beyond high watermark
 *
 * nr_मुक्त_buffer_pages() counts the number of pages which are beyond the high
 * watermark within ZONE_DMA and ZONE_NORMAL.
 *
 * Return: number of pages beyond high watermark within ZONE_DMA and
 * ZONE_NORMAL.
 */
अचिन्हित दीर्घ nr_मुक्त_buffer_pages(व्योम)
अणु
	वापस nr_मुक्त_zone_pages(gfp_zone(GFP_USER));
पूर्ण
EXPORT_SYMBOL_GPL(nr_मुक्त_buffer_pages);

अटल अंतरभूत व्योम show_node(काष्ठा zone *zone)
अणु
	अगर (IS_ENABLED(CONFIG_NUMA))
		prपूर्णांकk("Node %d ", zone_to_nid(zone));
पूर्ण

दीर्घ si_mem_available(व्योम)
अणु
	दीर्घ available;
	अचिन्हित दीर्घ pagecache;
	अचिन्हित दीर्घ wmark_low = 0;
	अचिन्हित दीर्घ pages[NR_LRU_LISTS];
	अचिन्हित दीर्घ reclaimable;
	काष्ठा zone *zone;
	पूर्णांक lru;

	क्रम (lru = LRU_BASE; lru < NR_LRU_LISTS; lru++)
		pages[lru] = global_node_page_state(NR_LRU_BASE + lru);

	क्रम_each_zone(zone)
		wmark_low += low_wmark_pages(zone);

	/*
	 * Estimate the amount of memory available क्रम userspace allocations,
	 * without causing swapping.
	 */
	available = global_zone_page_state(NR_FREE_PAGES) - totalreserve_pages;

	/*
	 * Not all the page cache can be मुक्तd, otherwise the प्रणाली will
	 * start swapping. Assume at least half of the page cache, or the
	 * low watermark worth of cache, needs to stay.
	 */
	pagecache = pages[LRU_ACTIVE_खाता] + pages[LRU_INACTIVE_खाता];
	pagecache -= min(pagecache / 2, wmark_low);
	available += pagecache;

	/*
	 * Part of the reclaimable slab and other kernel memory consists of
	 * items that are in use, and cannot be मुक्तd. Cap this estimate at the
	 * low watermark.
	 */
	reclaimable = global_node_page_state_pages(NR_SLAB_RECLAIMABLE_B) +
		global_node_page_state(NR_KERNEL_MISC_RECLAIMABLE);
	available += reclaimable - min(reclaimable / 2, wmark_low);

	अगर (available < 0)
		available = 0;
	वापस available;
पूर्ण
EXPORT_SYMBOL_GPL(si_mem_available);

व्योम si_meminfo(काष्ठा sysinfo *val)
अणु
	val->totalram = totalram_pages();
	val->sharedram = global_node_page_state(NR_SHMEM);
	val->मुक्तram = global_zone_page_state(NR_FREE_PAGES);
	val->bufferram = nr_blockdev_pages();
	val->totalhigh = totalhigh_pages();
	val->मुक्तhigh = nr_मुक्त_highpages();
	val->mem_unit = PAGE_SIZE;
पूर्ण

EXPORT_SYMBOL(si_meminfo);

#अगर_घोषित CONFIG_NUMA
व्योम si_meminfo_node(काष्ठा sysinfo *val, पूर्णांक nid)
अणु
	पूर्णांक zone_type;		/* needs to be चिन्हित */
	अचिन्हित दीर्घ managed_pages = 0;
	अचिन्हित दीर्घ managed_highpages = 0;
	अचिन्हित दीर्घ मुक्त_highpages = 0;
	pg_data_t *pgdat = NODE_DATA(nid);

	क्रम (zone_type = 0; zone_type < MAX_NR_ZONES; zone_type++)
		managed_pages += zone_managed_pages(&pgdat->node_zones[zone_type]);
	val->totalram = managed_pages;
	val->sharedram = node_page_state(pgdat, NR_SHMEM);
	val->मुक्तram = sum_zone_node_page_state(nid, NR_FREE_PAGES);
#अगर_घोषित CONFIG_HIGHMEM
	क्रम (zone_type = 0; zone_type < MAX_NR_ZONES; zone_type++) अणु
		काष्ठा zone *zone = &pgdat->node_zones[zone_type];

		अगर (is_highmem(zone)) अणु
			managed_highpages += zone_managed_pages(zone);
			मुक्त_highpages += zone_page_state(zone, NR_FREE_PAGES);
		पूर्ण
	पूर्ण
	val->totalhigh = managed_highpages;
	val->मुक्तhigh = मुक्त_highpages;
#अन्यथा
	val->totalhigh = managed_highpages;
	val->मुक्तhigh = मुक्त_highpages;
#पूर्ण_अगर
	val->mem_unit = PAGE_SIZE;
पूर्ण
#पूर्ण_अगर

/*
 * Determine whether the node should be displayed or not, depending on whether
 * SHOW_MEM_FILTER_NODES was passed to show_मुक्त_areas().
 */
अटल bool show_mem_node_skip(अचिन्हित पूर्णांक flags, पूर्णांक nid, nodemask_t *nodemask)
अणु
	अगर (!(flags & SHOW_MEM_FILTER_NODES))
		वापस false;

	/*
	 * no node mask - aka implicit memory numa policy. Do not bother with
	 * the synchronization - पढ़ो_mems_allowed_begin - because we करो not
	 * have to be precise here.
	 */
	अगर (!nodemask)
		nodemask = &cpuset_current_mems_allowed;

	वापस !node_isset(nid, *nodemask);
पूर्ण

#घोषणा K(x) ((x) << (PAGE_SHIFT-10))

अटल व्योम show_migration_types(अचिन्हित अक्षर type)
अणु
	अटल स्थिर अक्षर types[MIGRATE_TYPES] = अणु
		[MIGRATE_UNMOVABLE]	= 'U',
		[MIGRATE_MOVABLE]	= 'M',
		[MIGRATE_RECLAIMABLE]	= 'E',
		[MIGRATE_HIGHATOMIC]	= 'H',
#अगर_घोषित CONFIG_CMA
		[MIGRATE_CMA]		= 'C',
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEMORY_ISOLATION
		[MIGRATE_ISOLATE]	= 'I',
#पूर्ण_अगर
	पूर्ण;
	अक्षर पंचांगp[MIGRATE_TYPES + 1];
	अक्षर *p = पंचांगp;
	पूर्णांक i;

	क्रम (i = 0; i < MIGRATE_TYPES; i++) अणु
		अगर (type & (1 << i))
			*p++ = types[i];
	पूर्ण

	*p = '\0';
	prपूर्णांकk(KERN_CONT "(%s) ", पंचांगp);
पूर्ण

/*
 * Show मुक्त area list (used inside shअगरt_scroll-lock stuff)
 * We also calculate the percentage fragmentation. We करो this by counting the
 * memory on each मुक्त list with the exception of the first item on the list.
 *
 * Bits in @filter:
 * SHOW_MEM_FILTER_NODES: suppress nodes that are not allowed by current's
 *   cpuset.
 */
व्योम show_मुक्त_areas(अचिन्हित पूर्णांक filter, nodemask_t *nodemask)
अणु
	अचिन्हित दीर्घ मुक्त_pcp = 0;
	पूर्णांक cpu;
	काष्ठा zone *zone;
	pg_data_t *pgdat;

	क्रम_each_populated_zone(zone) अणु
		अगर (show_mem_node_skip(filter, zone_to_nid(zone), nodemask))
			जारी;

		क्रम_each_online_cpu(cpu)
			मुक्त_pcp += per_cpu_ptr(zone->pageset, cpu)->pcp.count;
	पूर्ण

	prपूर्णांकk("active_anon:%lu inactive_anon:%lu isolated_anon:%lu\n"
		" active_file:%lu inactive_file:%lu isolated_file:%lu\n"
		" unevictable:%lu dirty:%lu writeback:%lu\n"
		" slab_reclaimable:%lu slab_unreclaimable:%lu\n"
		" mapped:%lu shmem:%lu pagetables:%lu bounce:%lu\n"
		" free:%lu free_pcp:%lu free_cma:%lu\n",
		global_node_page_state(NR_ACTIVE_ANON),
		global_node_page_state(NR_INACTIVE_ANON),
		global_node_page_state(NR_ISOLATED_ANON),
		global_node_page_state(NR_ACTIVE_खाता),
		global_node_page_state(NR_INACTIVE_खाता),
		global_node_page_state(NR_ISOLATED_खाता),
		global_node_page_state(NR_UNEVICTABLE),
		global_node_page_state(NR_खाता_सूचीTY),
		global_node_page_state(NR_WRITEBACK),
		global_node_page_state_pages(NR_SLAB_RECLAIMABLE_B),
		global_node_page_state_pages(NR_SLAB_UNRECLAIMABLE_B),
		global_node_page_state(NR_खाता_MAPPED),
		global_node_page_state(NR_SHMEM),
		global_node_page_state(NR_PAGETABLE),
		global_zone_page_state(NR_BOUNCE),
		global_zone_page_state(NR_FREE_PAGES),
		मुक्त_pcp,
		global_zone_page_state(NR_FREE_CMA_PAGES));

	क्रम_each_online_pgdat(pgdat) अणु
		अगर (show_mem_node_skip(filter, pgdat->node_id, nodemask))
			जारी;

		prपूर्णांकk("Node %d"
			" active_anon:%lukB"
			" inactive_anon:%lukB"
			" active_file:%lukB"
			" inactive_file:%lukB"
			" unevictable:%lukB"
			" isolated(anon):%lukB"
			" isolated(file):%lukB"
			" mapped:%lukB"
			" dirty:%lukB"
			" writeback:%lukB"
			" shmem:%lukB"
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
			" shmem_thp: %lukB"
			" shmem_pmdmapped: %lukB"
			" anon_thp: %lukB"
#पूर्ण_अगर
			" writeback_tmp:%lukB"
			" kernel_stack:%lukB"
#अगर_घोषित CONFIG_SHADOW_CALL_STACK
			" shadow_call_stack:%lukB"
#पूर्ण_अगर
			" pagetables:%lukB"
			" all_unreclaimable? %s"
			"\n",
			pgdat->node_id,
			K(node_page_state(pgdat, NR_ACTIVE_ANON)),
			K(node_page_state(pgdat, NR_INACTIVE_ANON)),
			K(node_page_state(pgdat, NR_ACTIVE_खाता)),
			K(node_page_state(pgdat, NR_INACTIVE_खाता)),
			K(node_page_state(pgdat, NR_UNEVICTABLE)),
			K(node_page_state(pgdat, NR_ISOLATED_ANON)),
			K(node_page_state(pgdat, NR_ISOLATED_खाता)),
			K(node_page_state(pgdat, NR_खाता_MAPPED)),
			K(node_page_state(pgdat, NR_खाता_सूचीTY)),
			K(node_page_state(pgdat, NR_WRITEBACK)),
			K(node_page_state(pgdat, NR_SHMEM)),
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
			K(node_page_state(pgdat, NR_SHMEM_THPS)),
			K(node_page_state(pgdat, NR_SHMEM_PMDMAPPED)),
			K(node_page_state(pgdat, NR_ANON_THPS)),
#पूर्ण_अगर
			K(node_page_state(pgdat, NR_WRITEBACK_TEMP)),
			node_page_state(pgdat, NR_KERNEL_STACK_KB),
#अगर_घोषित CONFIG_SHADOW_CALL_STACK
			node_page_state(pgdat, NR_KERNEL_SCS_KB),
#पूर्ण_अगर
			K(node_page_state(pgdat, NR_PAGETABLE)),
			pgdat->kswapd_failures >= MAX_RECLAIM_RETRIES ?
				"yes" : "no");
	पूर्ण

	क्रम_each_populated_zone(zone) अणु
		पूर्णांक i;

		अगर (show_mem_node_skip(filter, zone_to_nid(zone), nodemask))
			जारी;

		मुक्त_pcp = 0;
		क्रम_each_online_cpu(cpu)
			मुक्त_pcp += per_cpu_ptr(zone->pageset, cpu)->pcp.count;

		show_node(zone);
		prपूर्णांकk(KERN_CONT
			"%s"
			" free:%lukB"
			" min:%lukB"
			" low:%lukB"
			" high:%lukB"
			" reserved_highatomic:%luKB"
			" active_anon:%lukB"
			" inactive_anon:%lukB"
			" active_file:%lukB"
			" inactive_file:%lukB"
			" unevictable:%lukB"
			" writepending:%lukB"
			" present:%lukB"
			" managed:%lukB"
			" mlocked:%lukB"
			" bounce:%lukB"
			" free_pcp:%lukB"
			" local_pcp:%ukB"
			" free_cma:%lukB"
			"\n",
			zone->name,
			K(zone_page_state(zone, NR_FREE_PAGES)),
			K(min_wmark_pages(zone)),
			K(low_wmark_pages(zone)),
			K(high_wmark_pages(zone)),
			K(zone->nr_reserved_highatomic),
			K(zone_page_state(zone, NR_ZONE_ACTIVE_ANON)),
			K(zone_page_state(zone, NR_ZONE_INACTIVE_ANON)),
			K(zone_page_state(zone, NR_ZONE_ACTIVE_खाता)),
			K(zone_page_state(zone, NR_ZONE_INACTIVE_खाता)),
			K(zone_page_state(zone, NR_ZONE_UNEVICTABLE)),
			K(zone_page_state(zone, NR_ZONE_WRITE_PENDING)),
			K(zone->present_pages),
			K(zone_managed_pages(zone)),
			K(zone_page_state(zone, NR_MLOCK)),
			K(zone_page_state(zone, NR_BOUNCE)),
			K(मुक्त_pcp),
			K(this_cpu_पढ़ो(zone->pageset->pcp.count)),
			K(zone_page_state(zone, NR_FREE_CMA_PAGES)));
		prपूर्णांकk("lowmem_reserve[]:");
		क्रम (i = 0; i < MAX_NR_ZONES; i++)
			prपूर्णांकk(KERN_CONT " %ld", zone->lowmem_reserve[i]);
		prपूर्णांकk(KERN_CONT "\n");
	पूर्ण

	क्रम_each_populated_zone(zone) अणु
		अचिन्हित पूर्णांक order;
		अचिन्हित दीर्घ nr[MAX_ORDER], flags, total = 0;
		अचिन्हित अक्षर types[MAX_ORDER];

		अगर (show_mem_node_skip(filter, zone_to_nid(zone), nodemask))
			जारी;
		show_node(zone);
		prपूर्णांकk(KERN_CONT "%s: ", zone->name);

		spin_lock_irqsave(&zone->lock, flags);
		क्रम (order = 0; order < MAX_ORDER; order++) अणु
			काष्ठा मुक्त_area *area = &zone->मुक्त_area[order];
			पूर्णांक type;

			nr[order] = area->nr_मुक्त;
			total += nr[order] << order;

			types[order] = 0;
			क्रम (type = 0; type < MIGRATE_TYPES; type++) अणु
				अगर (!मुक्त_area_empty(area, type))
					types[order] |= 1 << type;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&zone->lock, flags);
		क्रम (order = 0; order < MAX_ORDER; order++) अणु
			prपूर्णांकk(KERN_CONT "%lu*%lukB ",
			       nr[order], K(1UL) << order);
			अगर (nr[order])
				show_migration_types(types[order]);
		पूर्ण
		prपूर्णांकk(KERN_CONT "= %lukB\n", K(total));
	पूर्ण

	hugetlb_show_meminfo();

	prपूर्णांकk("%ld total pagecache pages\n", global_node_page_state(NR_खाता_PAGES));

	show_swap_cache_info();
पूर्ण

अटल व्योम zoneref_set_zone(काष्ठा zone *zone, काष्ठा zoneref *zoneref)
अणु
	zoneref->zone = zone;
	zoneref->zone_idx = zone_idx(zone);
पूर्ण

/*
 * Builds allocation fallback zone lists.
 *
 * Add all populated zones of a node to the zonelist.
 */
अटल पूर्णांक build_zonerefs_node(pg_data_t *pgdat, काष्ठा zoneref *zonerefs)
अणु
	काष्ठा zone *zone;
	क्रमागत zone_type zone_type = MAX_NR_ZONES;
	पूर्णांक nr_zones = 0;

	करो अणु
		zone_type--;
		zone = pgdat->node_zones + zone_type;
		अगर (managed_zone(zone)) अणु
			zoneref_set_zone(zone, &zonerefs[nr_zones++]);
			check_highest_zone(zone_type);
		पूर्ण
	पूर्ण जबतक (zone_type);

	वापस nr_zones;
पूर्ण

#अगर_घोषित CONFIG_NUMA

अटल पूर्णांक __parse_numa_zonelist_order(अक्षर *s)
अणु
	/*
	 * We used to support dअगरferent zonelists modes but they turned
	 * out to be just not useful. Let's keep the warning in place
	 * अगर somebody still use the cmd line parameter so that we करो
	 * not fail it silently
	 */
	अगर (!(*s == 'd' || *s == 'D' || *s == 'n' || *s == 'N')) अणु
		pr_warn("Ignoring unsupported numa_zonelist_order value:  %s\n", s);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अक्षर numa_zonelist_order[] = "Node";

/*
 * sysctl handler क्रम numa_zonelist_order
 */
पूर्णांक numa_zonelist_order_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *length, loff_t *ppos)
अणु
	अगर (ग_लिखो)
		वापस __parse_numa_zonelist_order(buffer);
	वापस proc_करोstring(table, ग_लिखो, buffer, length, ppos);
पूर्ण


#घोषणा MAX_NODE_LOAD (nr_online_nodes)
अटल पूर्णांक node_load[MAX_NUMNODES];

/**
 * find_next_best_node - find the next node that should appear in a given node's fallback list
 * @node: node whose fallback list we're appending
 * @used_node_mask: nodemask_t of alपढ़ोy used nodes
 *
 * We use a number of factors to determine which is the next node that should
 * appear on a given node's fallback list.  The node should not have appeared
 * alपढ़ोy in @node's fallback list, and it should be the next बंदst node
 * according to the distance array (which contains arbitrary distance values
 * from each node to each node in the प्रणाली), and should also prefer nodes
 * with no CPUs, since presumably they'll have very little allocation pressure
 * on them otherwise.
 *
 * Return: node id of the found node or %NUMA_NO_NODE अगर no node is found.
 */
अटल पूर्णांक find_next_best_node(पूर्णांक node, nodemask_t *used_node_mask)
अणु
	पूर्णांक n, val;
	पूर्णांक min_val = पूर्णांक_उच्च;
	पूर्णांक best_node = NUMA_NO_NODE;

	/* Use the local node अगर we haven't alपढ़ोy */
	अगर (!node_isset(node, *used_node_mask)) अणु
		node_set(node, *used_node_mask);
		वापस node;
	पूर्ण

	क्रम_each_node_state(n, N_MEMORY) अणु

		/* Don't want a node to appear more than once */
		अगर (node_isset(n, *used_node_mask))
			जारी;

		/* Use the distance array to find the distance */
		val = node_distance(node, n);

		/* Penalize nodes under us ("prefer the next node") */
		val += (n < node);

		/* Give preference to headless and unused nodes */
		अगर (!cpumask_empty(cpumask_of_node(n)))
			val += PENALTY_FOR_NODE_WITH_CPUS;

		/* Slight preference क्रम less loaded node */
		val *= (MAX_NODE_LOAD*MAX_NUMNODES);
		val += node_load[n];

		अगर (val < min_val) अणु
			min_val = val;
			best_node = n;
		पूर्ण
	पूर्ण

	अगर (best_node >= 0)
		node_set(best_node, *used_node_mask);

	वापस best_node;
पूर्ण


/*
 * Build zonelists ordered by node and zones within node.
 * This results in maximum locality--normal zone overflows पूर्णांकo local
 * DMA zone, अगर any--but risks exhausting DMA zone.
 */
अटल व्योम build_zonelists_in_node_order(pg_data_t *pgdat, पूर्णांक *node_order,
		अचिन्हित nr_nodes)
अणु
	काष्ठा zoneref *zonerefs;
	पूर्णांक i;

	zonerefs = pgdat->node_zonelists[ZONELIST_FALLBACK]._zonerefs;

	क्रम (i = 0; i < nr_nodes; i++) अणु
		पूर्णांक nr_zones;

		pg_data_t *node = NODE_DATA(node_order[i]);

		nr_zones = build_zonerefs_node(node, zonerefs);
		zonerefs += nr_zones;
	पूर्ण
	zonerefs->zone = शून्य;
	zonerefs->zone_idx = 0;
पूर्ण

/*
 * Build gfp_thisnode zonelists
 */
अटल व्योम build_thisnode_zonelists(pg_data_t *pgdat)
अणु
	काष्ठा zoneref *zonerefs;
	पूर्णांक nr_zones;

	zonerefs = pgdat->node_zonelists[ZONELIST_NOFALLBACK]._zonerefs;
	nr_zones = build_zonerefs_node(pgdat, zonerefs);
	zonerefs += nr_zones;
	zonerefs->zone = शून्य;
	zonerefs->zone_idx = 0;
पूर्ण

/*
 * Build zonelists ordered by zone and nodes within zones.
 * This results in conserving DMA zone[s] until all Normal memory is
 * exhausted, but results in overflowing to remote node जबतक memory
 * may still exist in local DMA zone.
 */

अटल व्योम build_zonelists(pg_data_t *pgdat)
अणु
	अटल पूर्णांक node_order[MAX_NUMNODES];
	पूर्णांक node, load, nr_nodes = 0;
	nodemask_t used_mask = NODE_MASK_NONE;
	पूर्णांक local_node, prev_node;

	/* NUMA-aware ordering of nodes */
	local_node = pgdat->node_id;
	load = nr_online_nodes;
	prev_node = local_node;

	स_रखो(node_order, 0, माप(node_order));
	जबतक ((node = find_next_best_node(local_node, &used_mask)) >= 0) अणु
		/*
		 * We करोn't want to pressure a particular node.
		 * So adding penalty to the first node in same
		 * distance group to make it round-robin.
		 */
		अगर (node_distance(local_node, node) !=
		    node_distance(local_node, prev_node))
			node_load[node] = load;

		node_order[nr_nodes++] = node;
		prev_node = node;
		load--;
	पूर्ण

	build_zonelists_in_node_order(pgdat, node_order, nr_nodes);
	build_thisnode_zonelists(pgdat);
पूर्ण

#अगर_घोषित CONFIG_HAVE_MEMORYLESS_NODES
/*
 * Return node id of node used क्रम "local" allocations.
 * I.e., first node id of first zone in arg node's generic zonelist.
 * Used क्रम initializing percpu 'numa_mem', which is used primarily
 * क्रम kernel allocations, so use GFP_KERNEL flags to locate zonelist.
 */
पूर्णांक local_memory_node(पूर्णांक node)
अणु
	काष्ठा zoneref *z;

	z = first_zones_zonelist(node_zonelist(node, GFP_KERNEL),
				   gfp_zone(GFP_KERNEL),
				   शून्य);
	वापस zone_to_nid(z->zone);
पूर्ण
#पूर्ण_अगर

अटल व्योम setup_min_unmapped_ratio(व्योम);
अटल व्योम setup_min_slab_ratio(व्योम);
#अन्यथा	/* CONFIG_NUMA */

अटल व्योम build_zonelists(pg_data_t *pgdat)
अणु
	पूर्णांक node, local_node;
	काष्ठा zoneref *zonerefs;
	पूर्णांक nr_zones;

	local_node = pgdat->node_id;

	zonerefs = pgdat->node_zonelists[ZONELIST_FALLBACK]._zonerefs;
	nr_zones = build_zonerefs_node(pgdat, zonerefs);
	zonerefs += nr_zones;

	/*
	 * Now we build the zonelist so that it contains the zones
	 * of all the other nodes.
	 * We करोn't want to pressure a particular node, so when
	 * building the zones क्रम node N, we make sure that the
	 * zones coming right after the local ones are those from
	 * node N+1 (modulo N)
	 */
	क्रम (node = local_node + 1; node < MAX_NUMNODES; node++) अणु
		अगर (!node_online(node))
			जारी;
		nr_zones = build_zonerefs_node(NODE_DATA(node), zonerefs);
		zonerefs += nr_zones;
	पूर्ण
	क्रम (node = 0; node < local_node; node++) अणु
		अगर (!node_online(node))
			जारी;
		nr_zones = build_zonerefs_node(NODE_DATA(node), zonerefs);
		zonerefs += nr_zones;
	पूर्ण

	zonerefs->zone = शून्य;
	zonerefs->zone_idx = 0;
पूर्ण

#पूर्ण_अगर	/* CONFIG_NUMA */

/*
 * Boot pageset table. One per cpu which is going to be used क्रम all
 * zones and all nodes. The parameters will be set in such a way
 * that an item put on a list will immediately be handed over to
 * the buddy list. This is safe since pageset manipulation is करोne
 * with पूर्णांकerrupts disabled.
 *
 * The boot_pagesets must be kept even after bootup is complete क्रम
 * unused processors and/or zones. They करो play a role क्रम bootstrapping
 * hotplugged processors.
 *
 * zoneinfo_show() and maybe other functions करो
 * not check अगर the processor is online beक्रमe following the pageset poपूर्णांकer.
 * Other parts of the kernel may not check अगर the zone is available.
 */
अटल व्योम pageset_init(काष्ठा per_cpu_pageset *p);
/* These effectively disable the pcplists in the boot pageset completely */
#घोषणा BOOT_PAGESET_HIGH	0
#घोषणा BOOT_PAGESET_BATCH	1
अटल DEFINE_PER_CPU(काष्ठा per_cpu_pageset, boot_pageset);
अटल DEFINE_PER_CPU(काष्ठा per_cpu_nodestat, boot_nodestats);

अटल व्योम __build_all_zonelists(व्योम *data)
अणु
	पूर्णांक nid;
	पूर्णांक __maybe_unused cpu;
	pg_data_t *self = data;
	अटल DEFINE_SPINLOCK(lock);

	spin_lock(&lock);

#अगर_घोषित CONFIG_NUMA
	स_रखो(node_load, 0, माप(node_load));
#पूर्ण_अगर

	/*
	 * This node is hotadded and no memory is yet present.   So just
	 * building zonelists is fine - no need to touch other nodes.
	 */
	अगर (self && !node_online(self->node_id)) अणु
		build_zonelists(self);
	पूर्ण अन्यथा अणु
		क्रम_each_online_node(nid) अणु
			pg_data_t *pgdat = NODE_DATA(nid);

			build_zonelists(pgdat);
		पूर्ण

#अगर_घोषित CONFIG_HAVE_MEMORYLESS_NODES
		/*
		 * We now know the "local memory node" क्रम each node--
		 * i.e., the node of the first zone in the generic zonelist.
		 * Set up numa_mem percpu variable क्रम on-line cpus.  During
		 * boot, only the boot cpu should be on-line;  we'll init the
		 * secondary cpus' numa_mem as they come on-line.  During
		 * node/memory hotplug, we'll fixup all on-line cpus.
		 */
		क्रम_each_online_cpu(cpu)
			set_cpu_numa_mem(cpu, local_memory_node(cpu_to_node(cpu)));
#पूर्ण_अगर
	पूर्ण

	spin_unlock(&lock);
पूर्ण

अटल noअंतरभूत व्योम __init
build_all_zonelists_init(व्योम)
अणु
	पूर्णांक cpu;

	__build_all_zonelists(शून्य);

	/*
	 * Initialize the boot_pagesets that are going to be used
	 * क्रम bootstrapping processors. The real pagesets क्रम
	 * each zone will be allocated later when the per cpu
	 * allocator is available.
	 *
	 * boot_pagesets are used also क्रम bootstrapping offline
	 * cpus अगर the प्रणाली is alपढ़ोy booted because the pagesets
	 * are needed to initialize allocators on a specअगरic cpu too.
	 * F.e. the percpu allocator needs the page allocator which
	 * needs the percpu allocator in order to allocate its pagesets
	 * (a chicken-egg dilemma).
	 */
	क्रम_each_possible_cpu(cpu)
		pageset_init(&per_cpu(boot_pageset, cpu));

	mminit_verअगरy_zonelist();
	cpuset_init_current_mems_allowed();
पूर्ण

/*
 * unless प्रणाली_state == SYSTEM_BOOTING.
 *
 * __ref due to call of __init annotated helper build_all_zonelists_init
 * [रक्षित by SYSTEM_BOOTING].
 */
व्योम __ref build_all_zonelists(pg_data_t *pgdat)
अणु
	अचिन्हित दीर्घ vm_total_pages;

	अगर (प्रणाली_state == SYSTEM_BOOTING) अणु
		build_all_zonelists_init();
	पूर्ण अन्यथा अणु
		__build_all_zonelists(pgdat);
		/* cpuset refresh routine should be here */
	पूर्ण
	/* Get the number of मुक्त pages beyond high watermark in all zones. */
	vm_total_pages = nr_मुक्त_zone_pages(gfp_zone(GFP_HIGHUSER_MOVABLE));
	/*
	 * Disable grouping by mobility अगर the number of pages in the
	 * प्रणाली is too low to allow the mechanism to work. It would be
	 * more accurate, but expensive to check per-zone. This check is
	 * made on memory-hotadd so a प्रणाली can start with mobility
	 * disabled and enable it later
	 */
	अगर (vm_total_pages < (pageblock_nr_pages * MIGRATE_TYPES))
		page_group_by_mobility_disabled = 1;
	अन्यथा
		page_group_by_mobility_disabled = 0;

	pr_info("Built %u zonelists, mobility grouping %s.  Total pages: %ld\n",
		nr_online_nodes,
		page_group_by_mobility_disabled ? "off" : "on",
		vm_total_pages);
#अगर_घोषित CONFIG_NUMA
	pr_info("Policy zone: %s\n", zone_names[policy_zone]);
#पूर्ण_अगर
पूर्ण

/* If zone is ZONE_MOVABLE but memory is mirrored, it is an overlapped init */
अटल bool __meminit
overlap_memmap_init(अचिन्हित दीर्घ zone, अचिन्हित दीर्घ *pfn)
अणु
	अटल काष्ठा memblock_region *r;

	अगर (mirrored_kernelcore && zone == ZONE_MOVABLE) अणु
		अगर (!r || *pfn >= memblock_region_memory_end_pfn(r)) अणु
			क्रम_each_mem_region(r) अणु
				अगर (*pfn < memblock_region_memory_end_pfn(r))
					अवरोध;
			पूर्ण
		पूर्ण
		अगर (*pfn >= memblock_region_memory_base_pfn(r) &&
		    memblock_is_mirror(r)) अणु
			*pfn = memblock_region_memory_end_pfn(r);
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

/*
 * Initially all pages are reserved - मुक्त ones are मुक्तd
 * up by memblock_मुक्त_all() once the early boot process is
 * करोne. Non-atomic initialization, single-pass.
 *
 * All aligned pageblocks are initialized to the specअगरied migratetype
 * (usually MIGRATE_MOVABLE). Besides setting the migratetype, no related
 * zone stats (e.g., nr_isolate_pageblock) are touched.
 */
व्योम __meminit memmap_init_range(अचिन्हित दीर्घ size, पूर्णांक nid, अचिन्हित दीर्घ zone,
		अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ zone_end_pfn,
		क्रमागत meminit_context context,
		काष्ठा vmem_alपंचांगap *alपंचांगap, पूर्णांक migratetype)
अणु
	अचिन्हित दीर्घ pfn, end_pfn = start_pfn + size;
	काष्ठा page *page;

	अगर (highest_memmap_pfn < end_pfn - 1)
		highest_memmap_pfn = end_pfn - 1;

#अगर_घोषित CONFIG_ZONE_DEVICE
	/*
	 * Honor reservation requested by the driver क्रम this ZONE_DEVICE
	 * memory. We limit the total number of pages to initialize to just
	 * those that might contain the memory mapping. We will defer the
	 * ZONE_DEVICE page initialization until after we have released
	 * the hotplug lock.
	 */
	अगर (zone == ZONE_DEVICE) अणु
		अगर (!alपंचांगap)
			वापस;

		अगर (start_pfn == alपंचांगap->base_pfn)
			start_pfn += alपंचांगap->reserve;
		end_pfn = alपंचांगap->base_pfn + vmem_alपंचांगap_offset(alपंचांगap);
	पूर्ण
#पूर्ण_अगर

	क्रम (pfn = start_pfn; pfn < end_pfn; ) अणु
		/*
		 * There can be holes in boot-समय mem_map[]s handed to this
		 * function.  They करो not exist on hotplugged memory.
		 */
		अगर (context == MEMINIT_EARLY) अणु
			अगर (overlap_memmap_init(zone, &pfn))
				जारी;
			अगर (defer_init(nid, pfn, zone_end_pfn))
				अवरोध;
		पूर्ण

		page = pfn_to_page(pfn);
		__init_single_page(page, pfn, zone, nid);
		अगर (context == MEMINIT_HOTPLUG)
			__SetPageReserved(page);

		/*
		 * Usually, we want to mark the pageblock MIGRATE_MOVABLE,
		 * such that unmovable allocations won't be scattered all
		 * over the place during प्रणाली boot.
		 */
		अगर (IS_ALIGNED(pfn, pageblock_nr_pages)) अणु
			set_pageblock_migratetype(page, migratetype);
			cond_resched();
		पूर्ण
		pfn++;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ZONE_DEVICE
व्योम __ref memmap_init_zone_device(काष्ठा zone *zone,
				   अचिन्हित दीर्घ start_pfn,
				   अचिन्हित दीर्घ nr_pages,
				   काष्ठा dev_pagemap *pgmap)
अणु
	अचिन्हित दीर्घ pfn, end_pfn = start_pfn + nr_pages;
	काष्ठा pglist_data *pgdat = zone->zone_pgdat;
	काष्ठा vmem_alपंचांगap *alपंचांगap = pgmap_alपंचांगap(pgmap);
	अचिन्हित दीर्घ zone_idx = zone_idx(zone);
	अचिन्हित दीर्घ start = jअगरfies;
	पूर्णांक nid = pgdat->node_id;

	अगर (WARN_ON_ONCE(!pgmap || zone_idx(zone) != ZONE_DEVICE))
		वापस;

	/*
	 * The call to memmap_init_zone should have alपढ़ोy taken care
	 * of the pages reserved क्रम the memmap, so we can just jump to
	 * the end of that region and start processing the device pages.
	 */
	अगर (alपंचांगap) अणु
		start_pfn = alपंचांगap->base_pfn + vmem_alपंचांगap_offset(alपंचांगap);
		nr_pages = end_pfn - start_pfn;
	पूर्ण

	क्रम (pfn = start_pfn; pfn < end_pfn; pfn++) अणु
		काष्ठा page *page = pfn_to_page(pfn);

		__init_single_page(page, pfn, zone_idx, nid);

		/*
		 * Mark page reserved as it will need to रुको क्रम onlining
		 * phase क्रम it to be fully associated with a zone.
		 *
		 * We can use the non-atomic __set_bit operation क्रम setting
		 * the flag as we are still initializing the pages.
		 */
		__SetPageReserved(page);

		/*
		 * ZONE_DEVICE pages जोड़ ->lru with a ->pgmap back poपूर्णांकer
		 * and zone_device_data.  It is a bug अगर a ZONE_DEVICE page is
		 * ever मुक्तd or placed on a driver-निजी list.
		 */
		page->pgmap = pgmap;
		page->zone_device_data = शून्य;

		/*
		 * Mark the block movable so that blocks are reserved क्रम
		 * movable at startup. This will क्रमce kernel allocations
		 * to reserve their blocks rather than leaking throughout
		 * the address space during boot when many दीर्घ-lived
		 * kernel allocations are made.
		 *
		 * Please note that MEMINIT_HOTPLUG path करोesn't clear memmap
		 * because this is करोne early in section_activate()
		 */
		अगर (IS_ALIGNED(pfn, pageblock_nr_pages)) अणु
			set_pageblock_migratetype(page, MIGRATE_MOVABLE);
			cond_resched();
		पूर्ण
	पूर्ण

	pr_info("%s initialised %lu pages in %ums\n", __func__,
		nr_pages, jअगरfies_to_msecs(jअगरfies - start));
पूर्ण

#पूर्ण_अगर
अटल व्योम __meminit zone_init_मुक्त_lists(काष्ठा zone *zone)
अणु
	अचिन्हित पूर्णांक order, t;
	क्रम_each_migratetype_order(order, t) अणु
		INIT_LIST_HEAD(&zone->मुक्त_area[order].मुक्त_list[t]);
		zone->मुक्त_area[order].nr_मुक्त = 0;
	पूर्ण
पूर्ण

#अगर !defined(CONFIG_FLAT_NODE_MEM_MAP)
/*
 * Only काष्ठा pages that correspond to ranges defined by memblock.memory
 * are zeroed and initialized by going through __init_single_page() during
 * memmap_init_zone().
 *
 * But, there could be काष्ठा pages that correspond to holes in
 * memblock.memory. This can happen because of the following reasons:
 * - physical memory bank size is not necessarily the exact multiple of the
 *   arbitrary section size
 * - early reserved memory may not be listed in memblock.memory
 * - memory layouts defined with memmap= kernel parameter may not align
 *   nicely with memmap sections
 *
 * Explicitly initialize those काष्ठा pages so that:
 * - PG_Reserved is set
 * - zone and node links poपूर्णांक to zone and node that span the page अगर the
 *   hole is in the middle of a zone
 * - zone and node links poपूर्णांक to adjacent zone/node अगर the hole falls on
 *   the zone boundary; the pages in such holes will be prepended to the
 *   zone/node above the hole except क्रम the trailing pages in the last
 *   section that will be appended to the zone/node below.
 */
अटल u64 __meminit init_unavailable_range(अचिन्हित दीर्घ spfn,
					    अचिन्हित दीर्घ epfn,
					    पूर्णांक zone, पूर्णांक node)
अणु
	अचिन्हित दीर्घ pfn;
	u64 pgcnt = 0;

	क्रम (pfn = spfn; pfn < epfn; pfn++) अणु
		अगर (!pfn_valid(ALIGN_DOWN(pfn, pageblock_nr_pages))) अणु
			pfn = ALIGN_DOWN(pfn, pageblock_nr_pages)
				+ pageblock_nr_pages - 1;
			जारी;
		पूर्ण
		__init_single_page(pfn_to_page(pfn), pfn, zone, node);
		__SetPageReserved(pfn_to_page(pfn));
		pgcnt++;
	पूर्ण

	वापस pgcnt;
पूर्ण
#अन्यथा
अटल अंतरभूत u64 init_unavailable_range(अचिन्हित दीर्घ spfn, अचिन्हित दीर्घ epfn,
					 पूर्णांक zone, पूर्णांक node)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम __meminit __weak memmap_init_zone(काष्ठा zone *zone)
अणु
	अचिन्हित दीर्घ zone_start_pfn = zone->zone_start_pfn;
	अचिन्हित दीर्घ zone_end_pfn = zone_start_pfn + zone->spanned_pages;
	पूर्णांक i, nid = zone_to_nid(zone), zone_id = zone_idx(zone);
	अटल अचिन्हित दीर्घ hole_pfn;
	अचिन्हित दीर्घ start_pfn, end_pfn;
	u64 pgcnt = 0;

	क्रम_each_mem_pfn_range(i, nid, &start_pfn, &end_pfn, शून्य) अणु
		start_pfn = clamp(start_pfn, zone_start_pfn, zone_end_pfn);
		end_pfn = clamp(end_pfn, zone_start_pfn, zone_end_pfn);

		अगर (end_pfn > start_pfn)
			memmap_init_range(end_pfn - start_pfn, nid,
					zone_id, start_pfn, zone_end_pfn,
					MEMINIT_EARLY, शून्य, MIGRATE_MOVABLE);

		अगर (hole_pfn < start_pfn)
			pgcnt += init_unavailable_range(hole_pfn, start_pfn,
							zone_id, nid);
		hole_pfn = end_pfn;
	पूर्ण

#अगर_घोषित CONFIG_SPARSEMEM
	/*
	 * Initialize the hole in the range [zone_end_pfn, section_end].
	 * If zone boundary falls in the middle of a section, this hole
	 * will be re-initialized during the call to this function क्रम the
	 * higher zone.
	 */
	end_pfn = round_up(zone_end_pfn, PAGES_PER_SECTION);
	अगर (hole_pfn < end_pfn)
		pgcnt += init_unavailable_range(hole_pfn, end_pfn,
						zone_id, nid);
#पूर्ण_अगर

	अगर (pgcnt)
		pr_info("  %s zone: %llu pages in unavailable ranges\n",
			zone->name, pgcnt);
पूर्ण

अटल पूर्णांक zone_batchsize(काष्ठा zone *zone)
अणु
#अगर_घोषित CONFIG_MMU
	पूर्णांक batch;

	/*
	 * The per-cpu-pages pools are set to around 1000th of the
	 * size of the zone.
	 */
	batch = zone_managed_pages(zone) / 1024;
	/* But no more than a meg. */
	अगर (batch * PAGE_SIZE > 1024 * 1024)
		batch = (1024 * 1024) / PAGE_SIZE;
	batch /= 4;		/* We effectively *= 4 below */
	अगर (batch < 1)
		batch = 1;

	/*
	 * Clamp the batch to a 2^n - 1 value. Having a घातer
	 * of 2 value was found to be more likely to have
	 * suboptimal cache aliasing properties in some हालs.
	 *
	 * For example अगर 2 tasks are alternately allocating
	 * batches of pages, one task can end up with a lot
	 * of pages of one half of the possible page colors
	 * and the other with pages of the other colors.
	 */
	batch = roundकरोwn_घात_of_two(batch + batch/2) - 1;

	वापस batch;

#अन्यथा
	/* The deferral and batching of मुक्तs should be suppressed under NOMMU
	 * conditions.
	 *
	 * The problem is that NOMMU needs to be able to allocate large chunks
	 * of contiguous memory as there's no hardware page translation to
	 * assemble apparent contiguous memory from discontiguous pages.
	 *
	 * Queueing large contiguous runs of pages क्रम batching, however,
	 * causes the pages to actually be मुक्तd in smaller chunks.  As there
	 * can be a signअगरicant delay between the inभागidual batches being
	 * recycled, this leads to the once large chunks of space being
	 * fragmented and becoming unavailable क्रम high-order allocations.
	 */
	वापस 0;
#पूर्ण_अगर
पूर्ण

/*
 * pcp->high and pcp->batch values are related and generally batch is lower
 * than high. They are also related to pcp->count such that count is lower
 * than high, and as soon as it reaches high, the pcplist is flushed.
 *
 * However, guaranteeing these relations at all बार would require e.g. ग_लिखो
 * barriers here but also careful usage of पढ़ो barriers at the पढ़ो side, and
 * thus be prone to error and bad क्रम perक्रमmance. Thus the update only prevents
 * store tearing. Any new users of pcp->batch and pcp->high should ensure they
 * can cope with those fields changing asynchronously, and fully trust only the
 * pcp->count field on the local CPU with पूर्णांकerrupts disabled.
 *
 * mutex_is_locked(&pcp_batch_high_lock) required when calling this function
 * outside of boot समय (or some other assurance that no concurrent updaters
 * exist).
 */
अटल व्योम pageset_update(काष्ठा per_cpu_pages *pcp, अचिन्हित दीर्घ high,
		अचिन्हित दीर्घ batch)
अणु
	WRITE_ONCE(pcp->batch, batch);
	WRITE_ONCE(pcp->high, high);
पूर्ण

अटल व्योम pageset_init(काष्ठा per_cpu_pageset *p)
अणु
	काष्ठा per_cpu_pages *pcp;
	पूर्णांक migratetype;

	स_रखो(p, 0, माप(*p));

	pcp = &p->pcp;
	क्रम (migratetype = 0; migratetype < MIGRATE_PCPTYPES; migratetype++)
		INIT_LIST_HEAD(&pcp->lists[migratetype]);

	/*
	 * Set batch and high values safe क्रम a boot pageset. A true percpu
	 * pageset's initialization will update them subsequently. Here we don't
	 * need to be as careful as pageset_update() as nobody can access the
	 * pageset yet.
	 */
	pcp->high = BOOT_PAGESET_HIGH;
	pcp->batch = BOOT_PAGESET_BATCH;
पूर्ण

अटल व्योम __zone_set_pageset_high_and_batch(काष्ठा zone *zone, अचिन्हित दीर्घ high,
		अचिन्हित दीर्घ batch)
अणु
	काष्ठा per_cpu_pageset *p;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		p = per_cpu_ptr(zone->pageset, cpu);
		pageset_update(&p->pcp, high, batch);
	पूर्ण
पूर्ण

/*
 * Calculate and set new high and batch values क्रम all per-cpu pagesets of a
 * zone, based on the zone's size and the percpu_pagelist_fraction sysctl.
 */
अटल व्योम zone_set_pageset_high_and_batch(काष्ठा zone *zone)
अणु
	अचिन्हित दीर्घ new_high, new_batch;

	अगर (percpu_pagelist_fraction) अणु
		new_high = zone_managed_pages(zone) / percpu_pagelist_fraction;
		new_batch = max(1UL, new_high / 4);
		अगर ((new_high / 4) > (PAGE_SHIFT * 8))
			new_batch = PAGE_SHIFT * 8;
	पूर्ण अन्यथा अणु
		new_batch = zone_batchsize(zone);
		new_high = 6 * new_batch;
		new_batch = max(1UL, 1 * new_batch);
	पूर्ण

	अगर (zone->pageset_high == new_high &&
	    zone->pageset_batch == new_batch)
		वापस;

	zone->pageset_high = new_high;
	zone->pageset_batch = new_batch;

	__zone_set_pageset_high_and_batch(zone, new_high, new_batch);
पूर्ण

व्योम __meminit setup_zone_pageset(काष्ठा zone *zone)
अणु
	काष्ठा per_cpu_pageset *p;
	पूर्णांक cpu;

	zone->pageset = alloc_percpu(काष्ठा per_cpu_pageset);
	क्रम_each_possible_cpu(cpu) अणु
		p = per_cpu_ptr(zone->pageset, cpu);
		pageset_init(p);
	पूर्ण

	zone_set_pageset_high_and_batch(zone);
पूर्ण

/*
 * Allocate per cpu pagesets and initialize them.
 * Beक्रमe this call only boot pagesets were available.
 */
व्योम __init setup_per_cpu_pageset(व्योम)
अणु
	काष्ठा pglist_data *pgdat;
	काष्ठा zone *zone;
	पूर्णांक __maybe_unused cpu;

	क्रम_each_populated_zone(zone)
		setup_zone_pageset(zone);

#अगर_घोषित CONFIG_NUMA
	/*
	 * Unpopulated zones जारी using the boot pagesets.
	 * The numa stats क्रम these pagesets need to be reset.
	 * Otherwise, they will end up skewing the stats of
	 * the nodes these zones are associated with.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा per_cpu_pageset *pcp = &per_cpu(boot_pageset, cpu);
		स_रखो(pcp->vm_numa_stat_dअगरf, 0,
		       माप(pcp->vm_numa_stat_dअगरf));
	पूर्ण
#पूर्ण_अगर

	क्रम_each_online_pgdat(pgdat)
		pgdat->per_cpu_nodestats =
			alloc_percpu(काष्ठा per_cpu_nodestat);
पूर्ण

अटल __meminit व्योम zone_pcp_init(काष्ठा zone *zone)
अणु
	/*
	 * per cpu subप्रणाली is not up at this poपूर्णांक. The following code
	 * relies on the ability of the linker to provide the
	 * offset of a (अटल) per cpu variable पूर्णांकo the per cpu area.
	 */
	zone->pageset = &boot_pageset;
	zone->pageset_high = BOOT_PAGESET_HIGH;
	zone->pageset_batch = BOOT_PAGESET_BATCH;

	अगर (populated_zone(zone))
		prपूर्णांकk(KERN_DEBUG "  %s zone: %lu pages, LIFO batch:%u\n",
			zone->name, zone->present_pages,
					 zone_batchsize(zone));
पूर्ण

व्योम __meminit init_currently_empty_zone(काष्ठा zone *zone,
					अचिन्हित दीर्घ zone_start_pfn,
					अचिन्हित दीर्घ size)
अणु
	काष्ठा pglist_data *pgdat = zone->zone_pgdat;
	पूर्णांक zone_idx = zone_idx(zone) + 1;

	अगर (zone_idx > pgdat->nr_zones)
		pgdat->nr_zones = zone_idx;

	zone->zone_start_pfn = zone_start_pfn;

	mminit_dprपूर्णांकk(MMINIT_TRACE, "memmap_init",
			"Initialising map node %d zone %lu pfns %lu -> %lu\n",
			pgdat->node_id,
			(अचिन्हित दीर्घ)zone_idx(zone),
			zone_start_pfn, (zone_start_pfn + size));

	zone_init_मुक्त_lists(zone);
	zone->initialized = 1;
पूर्ण

/**
 * get_pfn_range_क्रम_nid - Return the start and end page frames क्रम a node
 * @nid: The nid to वापस the range क्रम. If MAX_NUMNODES, the min and max PFN are वापसed.
 * @start_pfn: Passed by reference. On वापस, it will have the node start_pfn.
 * @end_pfn: Passed by reference. On वापस, it will have the node end_pfn.
 *
 * It वापसs the start and end page frame of a node based on inक्रमmation
 * provided by memblock_set_node(). If called क्रम a node
 * with no available memory, a warning is prपूर्णांकed and the start and end
 * PFNs will be 0.
 */
व्योम __init get_pfn_range_क्रम_nid(अचिन्हित पूर्णांक nid,
			अचिन्हित दीर्घ *start_pfn, अचिन्हित दीर्घ *end_pfn)
अणु
	अचिन्हित दीर्घ this_start_pfn, this_end_pfn;
	पूर्णांक i;

	*start_pfn = -1UL;
	*end_pfn = 0;

	क्रम_each_mem_pfn_range(i, nid, &this_start_pfn, &this_end_pfn, शून्य) अणु
		*start_pfn = min(*start_pfn, this_start_pfn);
		*end_pfn = max(*end_pfn, this_end_pfn);
	पूर्ण

	अगर (*start_pfn == -1UL)
		*start_pfn = 0;
पूर्ण

/*
 * This finds a zone that can be used क्रम ZONE_MOVABLE pages. The
 * assumption is made that zones within a node are ordered in monotonic
 * increasing memory addresses so that the "highest" populated zone is used
 */
अटल व्योम __init find_usable_zone_क्रम_movable(व्योम)
अणु
	पूर्णांक zone_index;
	क्रम (zone_index = MAX_NR_ZONES - 1; zone_index >= 0; zone_index--) अणु
		अगर (zone_index == ZONE_MOVABLE)
			जारी;

		अगर (arch_zone_highest_possible_pfn[zone_index] >
				arch_zone_lowest_possible_pfn[zone_index])
			अवरोध;
	पूर्ण

	VM_BUG_ON(zone_index == -1);
	movable_zone = zone_index;
पूर्ण

/*
 * The zone ranges provided by the architecture करो not include ZONE_MOVABLE
 * because it is sized independent of architecture. Unlike the other zones,
 * the starting poपूर्णांक क्रम ZONE_MOVABLE is not fixed. It may be dअगरferent
 * in each node depending on the size of each node and how evenly kernelcore
 * is distributed. This helper function adjusts the zone ranges
 * provided by the architecture क्रम a given node by using the end of the
 * highest usable zone क्रम ZONE_MOVABLE. This preserves the assumption that
 * zones within a node are in order of monotonic increases memory addresses
 */
अटल व्योम __init adjust_zone_range_क्रम_zone_movable(पूर्णांक nid,
					अचिन्हित दीर्घ zone_type,
					अचिन्हित दीर्घ node_start_pfn,
					अचिन्हित दीर्घ node_end_pfn,
					अचिन्हित दीर्घ *zone_start_pfn,
					अचिन्हित दीर्घ *zone_end_pfn)
अणु
	/* Only adjust अगर ZONE_MOVABLE is on this node */
	अगर (zone_movable_pfn[nid]) अणु
		/* Size ZONE_MOVABLE */
		अगर (zone_type == ZONE_MOVABLE) अणु
			*zone_start_pfn = zone_movable_pfn[nid];
			*zone_end_pfn = min(node_end_pfn,
				arch_zone_highest_possible_pfn[movable_zone]);

		/* Adjust क्रम ZONE_MOVABLE starting within this range */
		पूर्ण अन्यथा अगर (!mirrored_kernelcore &&
			*zone_start_pfn < zone_movable_pfn[nid] &&
			*zone_end_pfn > zone_movable_pfn[nid]) अणु
			*zone_end_pfn = zone_movable_pfn[nid];

		/* Check अगर this whole range is within ZONE_MOVABLE */
		पूर्ण अन्यथा अगर (*zone_start_pfn >= zone_movable_pfn[nid])
			*zone_start_pfn = *zone_end_pfn;
	पूर्ण
पूर्ण

/*
 * Return the number of pages a zone spans in a node, including holes
 * present_pages = zone_spanned_pages_in_node() - zone_असलent_pages_in_node()
 */
अटल अचिन्हित दीर्घ __init zone_spanned_pages_in_node(पूर्णांक nid,
					अचिन्हित दीर्घ zone_type,
					अचिन्हित दीर्घ node_start_pfn,
					अचिन्हित दीर्घ node_end_pfn,
					अचिन्हित दीर्घ *zone_start_pfn,
					अचिन्हित दीर्घ *zone_end_pfn)
अणु
	अचिन्हित दीर्घ zone_low = arch_zone_lowest_possible_pfn[zone_type];
	अचिन्हित दीर्घ zone_high = arch_zone_highest_possible_pfn[zone_type];
	/* When hotadd a new node from cpu_up(), the node should be empty */
	अगर (!node_start_pfn && !node_end_pfn)
		वापस 0;

	/* Get the start and end of the zone */
	*zone_start_pfn = clamp(node_start_pfn, zone_low, zone_high);
	*zone_end_pfn = clamp(node_end_pfn, zone_low, zone_high);
	adjust_zone_range_क्रम_zone_movable(nid, zone_type,
				node_start_pfn, node_end_pfn,
				zone_start_pfn, zone_end_pfn);

	/* Check that this node has pages within the zone's required range */
	अगर (*zone_end_pfn < node_start_pfn || *zone_start_pfn > node_end_pfn)
		वापस 0;

	/* Move the zone boundaries inside the node अगर necessary */
	*zone_end_pfn = min(*zone_end_pfn, node_end_pfn);
	*zone_start_pfn = max(*zone_start_pfn, node_start_pfn);

	/* Return the spanned pages */
	वापस *zone_end_pfn - *zone_start_pfn;
पूर्ण

/*
 * Return the number of holes in a range on a node. If nid is MAX_NUMNODES,
 * then all holes in the requested range will be accounted क्रम.
 */
अचिन्हित दीर्घ __init __असलent_pages_in_range(पूर्णांक nid,
				अचिन्हित दीर्घ range_start_pfn,
				अचिन्हित दीर्घ range_end_pfn)
अणु
	अचिन्हित दीर्घ nr_असलent = range_end_pfn - range_start_pfn;
	अचिन्हित दीर्घ start_pfn, end_pfn;
	पूर्णांक i;

	क्रम_each_mem_pfn_range(i, nid, &start_pfn, &end_pfn, शून्य) अणु
		start_pfn = clamp(start_pfn, range_start_pfn, range_end_pfn);
		end_pfn = clamp(end_pfn, range_start_pfn, range_end_pfn);
		nr_असलent -= end_pfn - start_pfn;
	पूर्ण
	वापस nr_असलent;
पूर्ण

/**
 * असलent_pages_in_range - Return number of page frames in holes within a range
 * @start_pfn: The start PFN to start searching क्रम holes
 * @end_pfn: The end PFN to stop searching क्रम holes
 *
 * Return: the number of pages frames in memory holes within a range.
 */
अचिन्हित दीर्घ __init असलent_pages_in_range(अचिन्हित दीर्घ start_pfn,
							अचिन्हित दीर्घ end_pfn)
अणु
	वापस __असलent_pages_in_range(MAX_NUMNODES, start_pfn, end_pfn);
पूर्ण

/* Return the number of page frames in holes in a zone on a node */
अटल अचिन्हित दीर्घ __init zone_असलent_pages_in_node(पूर्णांक nid,
					अचिन्हित दीर्घ zone_type,
					अचिन्हित दीर्घ node_start_pfn,
					अचिन्हित दीर्घ node_end_pfn)
अणु
	अचिन्हित दीर्घ zone_low = arch_zone_lowest_possible_pfn[zone_type];
	अचिन्हित दीर्घ zone_high = arch_zone_highest_possible_pfn[zone_type];
	अचिन्हित दीर्घ zone_start_pfn, zone_end_pfn;
	अचिन्हित दीर्घ nr_असलent;

	/* When hotadd a new node from cpu_up(), the node should be empty */
	अगर (!node_start_pfn && !node_end_pfn)
		वापस 0;

	zone_start_pfn = clamp(node_start_pfn, zone_low, zone_high);
	zone_end_pfn = clamp(node_end_pfn, zone_low, zone_high);

	adjust_zone_range_क्रम_zone_movable(nid, zone_type,
			node_start_pfn, node_end_pfn,
			&zone_start_pfn, &zone_end_pfn);
	nr_असलent = __असलent_pages_in_range(nid, zone_start_pfn, zone_end_pfn);

	/*
	 * ZONE_MOVABLE handling.
	 * Treat pages to be ZONE_MOVABLE in ZONE_NORMAL as असलent pages
	 * and vice versa.
	 */
	अगर (mirrored_kernelcore && zone_movable_pfn[nid]) अणु
		अचिन्हित दीर्घ start_pfn, end_pfn;
		काष्ठा memblock_region *r;

		क्रम_each_mem_region(r) अणु
			start_pfn = clamp(memblock_region_memory_base_pfn(r),
					  zone_start_pfn, zone_end_pfn);
			end_pfn = clamp(memblock_region_memory_end_pfn(r),
					zone_start_pfn, zone_end_pfn);

			अगर (zone_type == ZONE_MOVABLE &&
			    memblock_is_mirror(r))
				nr_असलent += end_pfn - start_pfn;

			अगर (zone_type == ZONE_NORMAL &&
			    !memblock_is_mirror(r))
				nr_असलent += end_pfn - start_pfn;
		पूर्ण
	पूर्ण

	वापस nr_असलent;
पूर्ण

अटल व्योम __init calculate_node_totalpages(काष्ठा pglist_data *pgdat,
						अचिन्हित दीर्घ node_start_pfn,
						अचिन्हित दीर्घ node_end_pfn)
अणु
	अचिन्हित दीर्घ realtotalpages = 0, totalpages = 0;
	क्रमागत zone_type i;

	क्रम (i = 0; i < MAX_NR_ZONES; i++) अणु
		काष्ठा zone *zone = pgdat->node_zones + i;
		अचिन्हित दीर्घ zone_start_pfn, zone_end_pfn;
		अचिन्हित दीर्घ spanned, असलent;
		अचिन्हित दीर्घ size, real_size;

		spanned = zone_spanned_pages_in_node(pgdat->node_id, i,
						     node_start_pfn,
						     node_end_pfn,
						     &zone_start_pfn,
						     &zone_end_pfn);
		असलent = zone_असलent_pages_in_node(pgdat->node_id, i,
						   node_start_pfn,
						   node_end_pfn);

		size = spanned;
		real_size = size - असलent;

		अगर (size)
			zone->zone_start_pfn = zone_start_pfn;
		अन्यथा
			zone->zone_start_pfn = 0;
		zone->spanned_pages = size;
		zone->present_pages = real_size;

		totalpages += size;
		realtotalpages += real_size;
	पूर्ण

	pgdat->node_spanned_pages = totalpages;
	pgdat->node_present_pages = realtotalpages;
	prपूर्णांकk(KERN_DEBUG "On node %d totalpages: %lu\n", pgdat->node_id,
							realtotalpages);
पूर्ण

#अगर_अघोषित CONFIG_SPARSEMEM
/*
 * Calculate the size of the zone->blockflags rounded to an अचिन्हित दीर्घ
 * Start by making sure zonesize is a multiple of pageblock_order by rounding
 * up. Then use 1 NR_PAGEBLOCK_BITS worth of bits per pageblock, finally
 * round what is now in bits to nearest दीर्घ in bits, then वापस it in
 * bytes.
 */
अटल अचिन्हित दीर्घ __init usemap_size(अचिन्हित दीर्घ zone_start_pfn, अचिन्हित दीर्घ zonesize)
अणु
	अचिन्हित दीर्घ usemapsize;

	zonesize += zone_start_pfn & (pageblock_nr_pages-1);
	usemapsize = roundup(zonesize, pageblock_nr_pages);
	usemapsize = usemapsize >> pageblock_order;
	usemapsize *= NR_PAGEBLOCK_BITS;
	usemapsize = roundup(usemapsize, 8 * माप(अचिन्हित दीर्घ));

	वापस usemapsize / 8;
पूर्ण

अटल व्योम __ref setup_usemap(काष्ठा zone *zone)
अणु
	अचिन्हित दीर्घ usemapsize = usemap_size(zone->zone_start_pfn,
					       zone->spanned_pages);
	zone->pageblock_flags = शून्य;
	अगर (usemapsize) अणु
		zone->pageblock_flags =
			memblock_alloc_node(usemapsize, SMP_CACHE_BYTES,
					    zone_to_nid(zone));
		अगर (!zone->pageblock_flags)
			panic("Failed to allocate %ld bytes for zone %s pageblock flags on node %d\n",
			      usemapsize, zone->name, zone_to_nid(zone));
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम setup_usemap(काष्ठा zone *zone) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_SPARSEMEM */

#अगर_घोषित CONFIG_HUGETLB_PAGE_SIZE_VARIABLE

/* Initialise the number of pages represented by NR_PAGEBLOCK_BITS */
व्योम __init set_pageblock_order(व्योम)
अणु
	अचिन्हित पूर्णांक order;

	/* Check that pageblock_nr_pages has not alपढ़ोy been setup */
	अगर (pageblock_order)
		वापस;

	अगर (HPAGE_SHIFT > PAGE_SHIFT)
		order = HUGETLB_PAGE_ORDER;
	अन्यथा
		order = MAX_ORDER - 1;

	/*
	 * Assume the largest contiguous order of पूर्णांकerest is a huge page.
	 * This value may be variable depending on boot parameters on IA64 and
	 * घातerpc.
	 */
	pageblock_order = order;
पूर्ण
#अन्यथा /* CONFIG_HUGETLB_PAGE_SIZE_VARIABLE */

/*
 * When CONFIG_HUGETLB_PAGE_SIZE_VARIABLE is not set, set_pageblock_order()
 * is unused as pageblock_order is set at compile-समय. See
 * include/linux/pageblock-flags.h क्रम the values of pageblock_order based on
 * the kernel config
 */
व्योम __init set_pageblock_order(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE_SIZE_VARIABLE */

अटल अचिन्हित दीर्घ __init calc_memmap_size(अचिन्हित दीर्घ spanned_pages,
						अचिन्हित दीर्घ present_pages)
अणु
	अचिन्हित दीर्घ pages = spanned_pages;

	/*
	 * Provide a more accurate estimation अगर there are holes within
	 * the zone and SPARSEMEM is in use. If there are holes within the
	 * zone, each populated memory region may cost us one or two extra
	 * memmap pages due to alignment because memmap pages क्रम each
	 * populated regions may not be naturally aligned on page boundary.
	 * So the (present_pages >> 4) heuristic is a tradeoff क्रम that.
	 */
	अगर (spanned_pages > present_pages + (present_pages >> 4) &&
	    IS_ENABLED(CONFIG_SPARSEMEM))
		pages = present_pages;

	वापस PAGE_ALIGN(pages * माप(काष्ठा page)) >> PAGE_SHIFT;
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल व्योम pgdat_init_split_queue(काष्ठा pglist_data *pgdat)
अणु
	काष्ठा deferred_split *ds_queue = &pgdat->deferred_split_queue;

	spin_lock_init(&ds_queue->split_queue_lock);
	INIT_LIST_HEAD(&ds_queue->split_queue);
	ds_queue->split_queue_len = 0;
पूर्ण
#अन्यथा
अटल व्योम pgdat_init_split_queue(काष्ठा pglist_data *pgdat) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPACTION
अटल व्योम pgdat_init_kcompactd(काष्ठा pglist_data *pgdat)
अणु
	init_रुकोqueue_head(&pgdat->kcompactd_रुको);
पूर्ण
#अन्यथा
अटल व्योम pgdat_init_kcompactd(काष्ठा pglist_data *pgdat) अणुपूर्ण
#पूर्ण_अगर

अटल व्योम __meminit pgdat_init_पूर्णांकernals(काष्ठा pglist_data *pgdat)
अणु
	pgdat_resize_init(pgdat);

	pgdat_init_split_queue(pgdat);
	pgdat_init_kcompactd(pgdat);

	init_रुकोqueue_head(&pgdat->kswapd_रुको);
	init_रुकोqueue_head(&pgdat->pfmeदो_स्मृति_रुको);

	pgdat_page_ext_init(pgdat);
	lruvec_init(&pgdat->__lruvec);
पूर्ण

अटल व्योम __meminit zone_init_पूर्णांकernals(काष्ठा zone *zone, क्रमागत zone_type idx, पूर्णांक nid,
							अचिन्हित दीर्घ reमुख्यing_pages)
अणु
	atomic_दीर्घ_set(&zone->managed_pages, reमुख्यing_pages);
	zone_set_nid(zone, nid);
	zone->name = zone_names[idx];
	zone->zone_pgdat = NODE_DATA(nid);
	spin_lock_init(&zone->lock);
	zone_seqlock_init(zone);
	zone_pcp_init(zone);
पूर्ण

/*
 * Set up the zone data काष्ठाures
 * - init pgdat पूर्णांकernals
 * - init all zones beदीर्घing to this node
 *
 * NOTE: this function is only called during memory hotplug
 */
#अगर_घोषित CONFIG_MEMORY_HOTPLUG
व्योम __ref मुक्त_area_init_core_hotplug(पूर्णांक nid)
अणु
	क्रमागत zone_type z;
	pg_data_t *pgdat = NODE_DATA(nid);

	pgdat_init_पूर्णांकernals(pgdat);
	क्रम (z = 0; z < MAX_NR_ZONES; z++)
		zone_init_पूर्णांकernals(&pgdat->node_zones[z], z, nid, 0);
पूर्ण
#पूर्ण_अगर

/*
 * Set up the zone data काष्ठाures:
 *   - mark all pages reserved
 *   - mark all memory queues empty
 *   - clear the memory biपंचांगaps
 *
 * NOTE: pgdat should get zeroed by caller.
 * NOTE: this function is only called during early init.
 */
अटल व्योम __init मुक्त_area_init_core(काष्ठा pglist_data *pgdat)
अणु
	क्रमागत zone_type j;
	पूर्णांक nid = pgdat->node_id;

	pgdat_init_पूर्णांकernals(pgdat);
	pgdat->per_cpu_nodestats = &boot_nodestats;

	क्रम (j = 0; j < MAX_NR_ZONES; j++) अणु
		काष्ठा zone *zone = pgdat->node_zones + j;
		अचिन्हित दीर्घ size, मुक्तsize, memmap_pages;

		size = zone->spanned_pages;
		मुक्तsize = zone->present_pages;

		/*
		 * Adjust मुक्तsize so that it accounts क्रम how much memory
		 * is used by this zone क्रम memmap. This affects the watermark
		 * and per-cpu initialisations
		 */
		memmap_pages = calc_memmap_size(size, मुक्तsize);
		अगर (!is_highmem_idx(j)) अणु
			अगर (मुक्तsize >= memmap_pages) अणु
				मुक्तsize -= memmap_pages;
				अगर (memmap_pages)
					prपूर्णांकk(KERN_DEBUG
					       "  %s zone: %lu pages used for memmap\n",
					       zone_names[j], memmap_pages);
			पूर्ण अन्यथा
				pr_warn("  %s zone: %lu pages exceeds freesize %lu\n",
					zone_names[j], memmap_pages, मुक्तsize);
		पूर्ण

		/* Account क्रम reserved pages */
		अगर (j == 0 && मुक्तsize > dma_reserve) अणु
			मुक्तsize -= dma_reserve;
			prपूर्णांकk(KERN_DEBUG "  %s zone: %lu pages reserved\n",
					zone_names[0], dma_reserve);
		पूर्ण

		अगर (!is_highmem_idx(j))
			nr_kernel_pages += मुक्तsize;
		/* Charge क्रम highmem memmap अगर there are enough kernel pages */
		अन्यथा अगर (nr_kernel_pages > memmap_pages * 2)
			nr_kernel_pages -= memmap_pages;
		nr_all_pages += मुक्तsize;

		/*
		 * Set an approximate value क्रम lowmem here, it will be adjusted
		 * when the booपंचांगem allocator मुक्तs pages पूर्णांकo the buddy प्रणाली.
		 * And all highmem pages will be managed by the buddy प्रणाली.
		 */
		zone_init_पूर्णांकernals(zone, j, nid, मुक्तsize);

		अगर (!size)
			जारी;

		set_pageblock_order();
		setup_usemap(zone);
		init_currently_empty_zone(zone, zone->zone_start_pfn, size);
		memmap_init_zone(zone);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_FLAT_NODE_MEM_MAP
अटल व्योम __ref alloc_node_mem_map(काष्ठा pglist_data *pgdat)
अणु
	अचिन्हित दीर्घ __maybe_unused start = 0;
	अचिन्हित दीर्घ __maybe_unused offset = 0;

	/* Skip empty nodes */
	अगर (!pgdat->node_spanned_pages)
		वापस;

	start = pgdat->node_start_pfn & ~(MAX_ORDER_NR_PAGES - 1);
	offset = pgdat->node_start_pfn - start;
	/* ia64 माला_लो its own node_mem_map, beक्रमe this, without booपंचांगem */
	अगर (!pgdat->node_mem_map) अणु
		अचिन्हित दीर्घ size, end;
		काष्ठा page *map;

		/*
		 * The zone's endpoints aren't required to be MAX_ORDER
		 * aligned but the node_mem_map endpoपूर्णांकs must be in order
		 * क्रम the buddy allocator to function correctly.
		 */
		end = pgdat_end_pfn(pgdat);
		end = ALIGN(end, MAX_ORDER_NR_PAGES);
		size =  (end - start) * माप(काष्ठा page);
		map = memblock_alloc_node(size, SMP_CACHE_BYTES,
					  pgdat->node_id);
		अगर (!map)
			panic("Failed to allocate %ld bytes for node %d memory map\n",
			      size, pgdat->node_id);
		pgdat->node_mem_map = map + offset;
	पूर्ण
	pr_debug("%s: node %d, pgdat %08lx, node_mem_map %08lx\n",
				__func__, pgdat->node_id, (अचिन्हित दीर्घ)pgdat,
				(अचिन्हित दीर्घ)pgdat->node_mem_map);
#अगर_अघोषित CONFIG_NEED_MULTIPLE_NODES
	/*
	 * With no DISCONTIG, the global mem_map is just set as node 0's
	 */
	अगर (pgdat == NODE_DATA(0)) अणु
		mem_map = NODE_DATA(0)->node_mem_map;
		अगर (page_to_pfn(mem_map) != pgdat->node_start_pfn)
			mem_map -= offset;
	पूर्ण
#पूर्ण_अगर
पूर्ण
#अन्यथा
अटल व्योम __ref alloc_node_mem_map(काष्ठा pglist_data *pgdat) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_FLAT_NODE_MEM_MAP */

#अगर_घोषित CONFIG_DEFERRED_STRUCT_PAGE_INIT
अटल अंतरभूत व्योम pgdat_set_deferred_range(pg_data_t *pgdat)
अणु
	pgdat->first_deferred_pfn = अच_दीर्घ_उच्च;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pgdat_set_deferred_range(pg_data_t *pgdat) अणुपूर्ण
#पूर्ण_अगर

अटल व्योम __init मुक्त_area_init_node(पूर्णांक nid)
अणु
	pg_data_t *pgdat = NODE_DATA(nid);
	अचिन्हित दीर्घ start_pfn = 0;
	अचिन्हित दीर्घ end_pfn = 0;

	/* pg_data_t should be reset to zero when it's allocated */
	WARN_ON(pgdat->nr_zones || pgdat->kswapd_highest_zoneidx);

	get_pfn_range_क्रम_nid(nid, &start_pfn, &end_pfn);

	pgdat->node_id = nid;
	pgdat->node_start_pfn = start_pfn;
	pgdat->per_cpu_nodestats = शून्य;

	pr_info("Initmem setup node %d [mem %#018Lx-%#018Lx]\n", nid,
		(u64)start_pfn << PAGE_SHIFT,
		end_pfn ? ((u64)end_pfn << PAGE_SHIFT) - 1 : 0);
	calculate_node_totalpages(pgdat, start_pfn, end_pfn);

	alloc_node_mem_map(pgdat);
	pgdat_set_deferred_range(pgdat);

	मुक्त_area_init_core(pgdat);
पूर्ण

व्योम __init मुक्त_area_init_memoryless_node(पूर्णांक nid)
अणु
	मुक्त_area_init_node(nid);
पूर्ण

#अगर MAX_NUMNODES > 1
/*
 * Figure out the number of possible node ids.
 */
व्योम __init setup_nr_node_ids(व्योम)
अणु
	अचिन्हित पूर्णांक highest;

	highest = find_last_bit(node_possible_map.bits, MAX_NUMNODES);
	nr_node_ids = highest + 1;
पूर्ण
#पूर्ण_अगर

/**
 * node_map_pfn_alignment - determine the maximum पूर्णांकernode alignment
 *
 * This function should be called after node map is populated and sorted.
 * It calculates the maximum घातer of two alignment which can distinguish
 * all the nodes.
 *
 * For example, अगर all nodes are 1GiB and aligned to 1GiB, the वापस value
 * would indicate 1GiB alignment with (1 << (30 - PAGE_SHIFT)).  If the
 * nodes are shअगरted by 256MiB, 256MiB.  Note that अगर only the last node is
 * shअगरted, 1GiB is enough and this function will indicate so.
 *
 * This is used to test whether pfn -> nid mapping of the chosen memory
 * model has fine enough granularity to aव्योम incorrect mapping क्रम the
 * populated node map.
 *
 * Return: the determined alignment in pfn's.  0 अगर there is no alignment
 * requirement (single node).
 */
अचिन्हित दीर्घ __init node_map_pfn_alignment(व्योम)
अणु
	अचिन्हित दीर्घ accl_mask = 0, last_end = 0;
	अचिन्हित दीर्घ start, end, mask;
	पूर्णांक last_nid = NUMA_NO_NODE;
	पूर्णांक i, nid;

	क्रम_each_mem_pfn_range(i, MAX_NUMNODES, &start, &end, &nid) अणु
		अगर (!start || last_nid < 0 || last_nid == nid) अणु
			last_nid = nid;
			last_end = end;
			जारी;
		पूर्ण

		/*
		 * Start with a mask granular enough to pin-poपूर्णांक to the
		 * start pfn and tick off bits one-by-one until it becomes
		 * too coarse to separate the current node from the last.
		 */
		mask = ~((1 << __ffs(start)) - 1);
		जबतक (mask && last_end <= (start & (mask << 1)))
			mask <<= 1;

		/* accumulate all पूर्णांकernode masks */
		accl_mask |= mask;
	पूर्ण

	/* convert mask to number of pages */
	वापस ~accl_mask + 1;
पूर्ण

/**
 * find_min_pfn_with_active_regions - Find the minimum PFN रेजिस्टरed
 *
 * Return: the minimum PFN based on inक्रमmation provided via
 * memblock_set_node().
 */
अचिन्हित दीर्घ __init find_min_pfn_with_active_regions(व्योम)
अणु
	वापस PHYS_PFN(memblock_start_of_DRAM());
पूर्ण

/*
 * early_calculate_totalpages()
 * Sum pages in active regions क्रम movable zone.
 * Populate N_MEMORY क्रम calculating usable_nodes.
 */
अटल अचिन्हित दीर्घ __init early_calculate_totalpages(व्योम)
अणु
	अचिन्हित दीर्घ totalpages = 0;
	अचिन्हित दीर्घ start_pfn, end_pfn;
	पूर्णांक i, nid;

	क्रम_each_mem_pfn_range(i, MAX_NUMNODES, &start_pfn, &end_pfn, &nid) अणु
		अचिन्हित दीर्घ pages = end_pfn - start_pfn;

		totalpages += pages;
		अगर (pages)
			node_set_state(nid, N_MEMORY);
	पूर्ण
	वापस totalpages;
पूर्ण

/*
 * Find the PFN the Movable zone begins in each node. Kernel memory
 * is spपढ़ो evenly between nodes as दीर्घ as the nodes have enough
 * memory. When they करोn't, some nodes will have more kernelcore than
 * others
 */
अटल व्योम __init find_zone_movable_pfns_क्रम_nodes(व्योम)
अणु
	पूर्णांक i, nid;
	अचिन्हित दीर्घ usable_startpfn;
	अचिन्हित दीर्घ kernelcore_node, kernelcore_reमुख्यing;
	/* save the state beक्रमe borrow the nodemask */
	nodemask_t saved_node_state = node_states[N_MEMORY];
	अचिन्हित दीर्घ totalpages = early_calculate_totalpages();
	पूर्णांक usable_nodes = nodes_weight(node_states[N_MEMORY]);
	काष्ठा memblock_region *r;

	/* Need to find movable_zone earlier when movable_node is specअगरied. */
	find_usable_zone_क्रम_movable();

	/*
	 * If movable_node is specअगरied, ignore kernelcore and movablecore
	 * options.
	 */
	अगर (movable_node_is_enabled()) अणु
		क्रम_each_mem_region(r) अणु
			अगर (!memblock_is_hotpluggable(r))
				जारी;

			nid = memblock_get_region_node(r);

			usable_startpfn = PFN_DOWN(r->base);
			zone_movable_pfn[nid] = zone_movable_pfn[nid] ?
				min(usable_startpfn, zone_movable_pfn[nid]) :
				usable_startpfn;
		पूर्ण

		जाओ out2;
	पूर्ण

	/*
	 * If kernelcore=mirror is specअगरied, ignore movablecore option
	 */
	अगर (mirrored_kernelcore) अणु
		bool mem_below_4gb_not_mirrored = false;

		क्रम_each_mem_region(r) अणु
			अगर (memblock_is_mirror(r))
				जारी;

			nid = memblock_get_region_node(r);

			usable_startpfn = memblock_region_memory_base_pfn(r);

			अगर (usable_startpfn < 0x100000) अणु
				mem_below_4gb_not_mirrored = true;
				जारी;
			पूर्ण

			zone_movable_pfn[nid] = zone_movable_pfn[nid] ?
				min(usable_startpfn, zone_movable_pfn[nid]) :
				usable_startpfn;
		पूर्ण

		अगर (mem_below_4gb_not_mirrored)
			pr_warn("This configuration results in unmirrored kernel memory.\n");

		जाओ out2;
	पूर्ण

	/*
	 * If kernelcore=nn% or movablecore=nn% was specअगरied, calculate the
	 * amount of necessary memory.
	 */
	अगर (required_kernelcore_percent)
		required_kernelcore = (totalpages * 100 * required_kernelcore_percent) /
				       10000UL;
	अगर (required_movablecore_percent)
		required_movablecore = (totalpages * 100 * required_movablecore_percent) /
					10000UL;

	/*
	 * If movablecore= was specअगरied, calculate what size of
	 * kernelcore that corresponds so that memory usable क्रम
	 * any allocation type is evenly spपढ़ो. If both kernelcore
	 * and movablecore are specअगरied, then the value of kernelcore
	 * will be used क्रम required_kernelcore अगर it's greater than
	 * what movablecore would have allowed.
	 */
	अगर (required_movablecore) अणु
		अचिन्हित दीर्घ corepages;

		/*
		 * Round-up so that ZONE_MOVABLE is at least as large as what
		 * was requested by the user
		 */
		required_movablecore =
			roundup(required_movablecore, MAX_ORDER_NR_PAGES);
		required_movablecore = min(totalpages, required_movablecore);
		corepages = totalpages - required_movablecore;

		required_kernelcore = max(required_kernelcore, corepages);
	पूर्ण

	/*
	 * If kernelcore was not specअगरied or kernelcore size is larger
	 * than totalpages, there is no ZONE_MOVABLE.
	 */
	अगर (!required_kernelcore || required_kernelcore >= totalpages)
		जाओ out;

	/* usable_startpfn is the lowest possible pfn ZONE_MOVABLE can be at */
	usable_startpfn = arch_zone_lowest_possible_pfn[movable_zone];

restart:
	/* Spपढ़ो kernelcore memory as evenly as possible throughout nodes */
	kernelcore_node = required_kernelcore / usable_nodes;
	क्रम_each_node_state(nid, N_MEMORY) अणु
		अचिन्हित दीर्घ start_pfn, end_pfn;

		/*
		 * Recalculate kernelcore_node अगर the भागision per node
		 * now exceeds what is necessary to satisfy the requested
		 * amount of memory क्रम the kernel
		 */
		अगर (required_kernelcore < kernelcore_node)
			kernelcore_node = required_kernelcore / usable_nodes;

		/*
		 * As the map is walked, we track how much memory is usable
		 * by the kernel using kernelcore_reमुख्यing. When it is
		 * 0, the rest of the node is usable by ZONE_MOVABLE
		 */
		kernelcore_reमुख्यing = kernelcore_node;

		/* Go through each range of PFNs within this node */
		क्रम_each_mem_pfn_range(i, nid, &start_pfn, &end_pfn, शून्य) अणु
			अचिन्हित दीर्घ size_pages;

			start_pfn = max(start_pfn, zone_movable_pfn[nid]);
			अगर (start_pfn >= end_pfn)
				जारी;

			/* Account क्रम what is only usable क्रम kernelcore */
			अगर (start_pfn < usable_startpfn) अणु
				अचिन्हित दीर्घ kernel_pages;
				kernel_pages = min(end_pfn, usable_startpfn)
								- start_pfn;

				kernelcore_reमुख्यing -= min(kernel_pages,
							kernelcore_reमुख्यing);
				required_kernelcore -= min(kernel_pages,
							required_kernelcore);

				/* Continue अगर range is now fully accounted */
				अगर (end_pfn <= usable_startpfn) अणु

					/*
					 * Push zone_movable_pfn to the end so
					 * that अगर we have to rebalance
					 * kernelcore across nodes, we will
					 * not द्विगुन account here
					 */
					zone_movable_pfn[nid] = end_pfn;
					जारी;
				पूर्ण
				start_pfn = usable_startpfn;
			पूर्ण

			/*
			 * The usable PFN range क्रम ZONE_MOVABLE is from
			 * start_pfn->end_pfn. Calculate size_pages as the
			 * number of pages used as kernelcore
			 */
			size_pages = end_pfn - start_pfn;
			अगर (size_pages > kernelcore_reमुख्यing)
				size_pages = kernelcore_reमुख्यing;
			zone_movable_pfn[nid] = start_pfn + size_pages;

			/*
			 * Some kernelcore has been met, update counts and
			 * अवरोध अगर the kernelcore क्रम this node has been
			 * satisfied
			 */
			required_kernelcore -= min(required_kernelcore,
								size_pages);
			kernelcore_reमुख्यing -= size_pages;
			अगर (!kernelcore_reमुख्यing)
				अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If there is still required_kernelcore, we करो another pass with one
	 * less node in the count. This will push zone_movable_pfn[nid] further
	 * aदीर्घ on the nodes that still have memory until kernelcore is
	 * satisfied
	 */
	usable_nodes--;
	अगर (usable_nodes && required_kernelcore > usable_nodes)
		जाओ restart;

out2:
	/* Align start of ZONE_MOVABLE on all nids to MAX_ORDER_NR_PAGES */
	क्रम (nid = 0; nid < MAX_NUMNODES; nid++)
		zone_movable_pfn[nid] =
			roundup(zone_movable_pfn[nid], MAX_ORDER_NR_PAGES);

out:
	/* restore the node_state */
	node_states[N_MEMORY] = saved_node_state;
पूर्ण

/* Any regular or high memory on that node ? */
अटल व्योम check_क्रम_memory(pg_data_t *pgdat, पूर्णांक nid)
अणु
	क्रमागत zone_type zone_type;

	क्रम (zone_type = 0; zone_type <= ZONE_MOVABLE - 1; zone_type++) अणु
		काष्ठा zone *zone = &pgdat->node_zones[zone_type];
		अगर (populated_zone(zone)) अणु
			अगर (IS_ENABLED(CONFIG_HIGHMEM))
				node_set_state(nid, N_HIGH_MEMORY);
			अगर (zone_type <= ZONE_NORMAL)
				node_set_state(nid, N_NORMAL_MEMORY);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Some architectures, e.g. ARC may have ZONE_HIGHMEM below ZONE_NORMAL. For
 * such हालs we allow max_zone_pfn sorted in the descending order
 */
bool __weak arch_has_descending_max_zone_pfns(व्योम)
अणु
	वापस false;
पूर्ण

/**
 * मुक्त_area_init - Initialise all pg_data_t and zone data
 * @max_zone_pfn: an array of max PFNs क्रम each zone
 *
 * This will call मुक्त_area_init_node() क्रम each active node in the प्रणाली.
 * Using the page ranges provided by memblock_set_node(), the size of each
 * zone in each node and their holes is calculated. If the maximum PFN
 * between two adjacent zones match, it is assumed that the zone is empty.
 * For example, अगर arch_max_dma_pfn == arch_max_dma32_pfn, it is assumed
 * that arch_max_dma32_pfn has no pages. It is also assumed that a zone
 * starts where the previous one ended. For example, ZONE_DMA32 starts
 * at arch_max_dma_pfn.
 */
व्योम __init मुक्त_area_init(अचिन्हित दीर्घ *max_zone_pfn)
अणु
	अचिन्हित दीर्घ start_pfn, end_pfn;
	पूर्णांक i, nid, zone;
	bool descending;

	/* Record where the zone boundaries are */
	स_रखो(arch_zone_lowest_possible_pfn, 0,
				माप(arch_zone_lowest_possible_pfn));
	स_रखो(arch_zone_highest_possible_pfn, 0,
				माप(arch_zone_highest_possible_pfn));

	start_pfn = find_min_pfn_with_active_regions();
	descending = arch_has_descending_max_zone_pfns();

	क्रम (i = 0; i < MAX_NR_ZONES; i++) अणु
		अगर (descending)
			zone = MAX_NR_ZONES - i - 1;
		अन्यथा
			zone = i;

		अगर (zone == ZONE_MOVABLE)
			जारी;

		end_pfn = max(max_zone_pfn[zone], start_pfn);
		arch_zone_lowest_possible_pfn[zone] = start_pfn;
		arch_zone_highest_possible_pfn[zone] = end_pfn;

		start_pfn = end_pfn;
	पूर्ण

	/* Find the PFNs that ZONE_MOVABLE begins at in each node */
	स_रखो(zone_movable_pfn, 0, माप(zone_movable_pfn));
	find_zone_movable_pfns_क्रम_nodes();

	/* Prपूर्णांक out the zone ranges */
	pr_info("Zone ranges:\n");
	क्रम (i = 0; i < MAX_NR_ZONES; i++) अणु
		अगर (i == ZONE_MOVABLE)
			जारी;
		pr_info("  %-8s ", zone_names[i]);
		अगर (arch_zone_lowest_possible_pfn[i] ==
				arch_zone_highest_possible_pfn[i])
			pr_cont("empty\n");
		अन्यथा
			pr_cont("[mem %#018Lx-%#018Lx]\n",
				(u64)arch_zone_lowest_possible_pfn[i]
					<< PAGE_SHIFT,
				((u64)arch_zone_highest_possible_pfn[i]
					<< PAGE_SHIFT) - 1);
	पूर्ण

	/* Prपूर्णांक out the PFNs ZONE_MOVABLE begins at in each node */
	pr_info("Movable zone start for each node\n");
	क्रम (i = 0; i < MAX_NUMNODES; i++) अणु
		अगर (zone_movable_pfn[i])
			pr_info("  Node %d: %#018Lx\n", i,
			       (u64)zone_movable_pfn[i] << PAGE_SHIFT);
	पूर्ण

	/*
	 * Prपूर्णांक out the early node map, and initialize the
	 * subsection-map relative to active online memory ranges to
	 * enable future "sub-section" extensions of the memory map.
	 */
	pr_info("Early memory node ranges\n");
	क्रम_each_mem_pfn_range(i, MAX_NUMNODES, &start_pfn, &end_pfn, &nid) अणु
		pr_info("  node %3d: [mem %#018Lx-%#018Lx]\n", nid,
			(u64)start_pfn << PAGE_SHIFT,
			((u64)end_pfn << PAGE_SHIFT) - 1);
		subsection_map_init(start_pfn, end_pfn - start_pfn);
	पूर्ण

	/* Initialise every node */
	mminit_verअगरy_pageflags_layout();
	setup_nr_node_ids();
	क्रम_each_online_node(nid) अणु
		pg_data_t *pgdat = NODE_DATA(nid);
		मुक्त_area_init_node(nid);

		/* Any memory on that node */
		अगर (pgdat->node_present_pages)
			node_set_state(nid, N_MEMORY);
		check_क्रम_memory(pgdat, nid);
	पूर्ण
पूर्ण

अटल पूर्णांक __init cmdline_parse_core(अक्षर *p, अचिन्हित दीर्घ *core,
				     अचिन्हित दीर्घ *percent)
अणु
	अचिन्हित दीर्घ दीर्घ coremem;
	अक्षर *endptr;

	अगर (!p)
		वापस -EINVAL;

	/* Value may be a percentage of total memory, otherwise bytes */
	coremem = simple_म_से_अदीर्घl(p, &endptr, 0);
	अगर (*endptr == '%') अणु
		/* Paranoid check क्रम percent values greater than 100 */
		WARN_ON(coremem > 100);

		*percent = coremem;
	पूर्ण अन्यथा अणु
		coremem = memparse(p, &p);
		/* Paranoid check that UL is enough क्रम the coremem value */
		WARN_ON((coremem >> PAGE_SHIFT) > अच_दीर्घ_उच्च);

		*core = coremem >> PAGE_SHIFT;
		*percent = 0UL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * kernelcore=size sets the amount of memory क्रम use क्रम allocations that
 * cannot be reclaimed or migrated.
 */
अटल पूर्णांक __init cmdline_parse_kernelcore(अक्षर *p)
अणु
	/* parse kernelcore=mirror */
	अगर (parse_option_str(p, "mirror")) अणु
		mirrored_kernelcore = true;
		वापस 0;
	पूर्ण

	वापस cmdline_parse_core(p, &required_kernelcore,
				  &required_kernelcore_percent);
पूर्ण

/*
 * movablecore=size sets the amount of memory क्रम use क्रम allocations that
 * can be reclaimed or migrated.
 */
अटल पूर्णांक __init cmdline_parse_movablecore(अक्षर *p)
अणु
	वापस cmdline_parse_core(p, &required_movablecore,
				  &required_movablecore_percent);
पूर्ण

early_param("kernelcore", cmdline_parse_kernelcore);
early_param("movablecore", cmdline_parse_movablecore);

व्योम adjust_managed_page_count(काष्ठा page *page, दीर्घ count)
अणु
	atomic_दीर्घ_add(count, &page_zone(page)->managed_pages);
	totalram_pages_add(count);
#अगर_घोषित CONFIG_HIGHMEM
	अगर (PageHighMem(page))
		totalhigh_pages_add(count);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(adjust_managed_page_count);

अचिन्हित दीर्घ मुक्त_reserved_area(व्योम *start, व्योम *end, पूर्णांक poison, स्थिर अक्षर *s)
अणु
	व्योम *pos;
	अचिन्हित दीर्घ pages = 0;

	start = (व्योम *)PAGE_ALIGN((अचिन्हित दीर्घ)start);
	end = (व्योम *)((अचिन्हित दीर्घ)end & PAGE_MASK);
	क्रम (pos = start; pos < end; pos += PAGE_SIZE, pages++) अणु
		काष्ठा page *page = virt_to_page(pos);
		व्योम *direct_map_addr;

		/*
		 * 'direct_map_addr' might be different from 'pos'
		 * because some architectures' virt_to_page()
		 * work with aliases.  Getting the direct map
		 * address ensures that we get a _ग_लिखोable_
		 * alias क्रम the स_रखो().
		 */
		direct_map_addr = page_address(page);
		/*
		 * Perक्रमm a kasan-unchecked स_रखो() since this memory
		 * has not been initialized.
		 */
		direct_map_addr = kasan_reset_tag(direct_map_addr);
		अगर ((अचिन्हित पूर्णांक)poison <= 0xFF)
			स_रखो(direct_map_addr, poison, PAGE_SIZE);

		मुक्त_reserved_page(page);
	पूर्ण

	अगर (pages && s)
		pr_info("Freeing %s memory: %ldK\n",
			s, pages << (PAGE_SHIFT - 10));

	वापस pages;
पूर्ण

व्योम __init mem_init_prपूर्णांक_info(व्योम)
अणु
	अचिन्हित दीर्घ physpages, codesize, datasize, rosize, bss_size;
	अचिन्हित दीर्घ init_code_size, init_data_size;

	physpages = get_num_physpages();
	codesize = _etext - _stext;
	datasize = _edata - _sdata;
	rosize = __end_rodata - __start_rodata;
	bss_size = __bss_stop - __bss_start;
	init_data_size = __init_end - __init_begin;
	init_code_size = _einittext - _sinittext;

	/*
	 * Detect special हालs and adjust section sizes accordingly:
	 * 1) .init.* may be embedded पूर्णांकo .data sections
	 * 2) .init.text.* may be out of [__init_begin, __init_end],
	 *    please refer to arch/tile/kernel/vmlinux.lds.S.
	 * 3) .rodata.* may be embedded पूर्णांकo .text or .data sections.
	 */
#घोषणा adj_init_size(start, end, size, pos, adj) \
	करो अणु \
		अगर (start <= pos && pos < end && size > adj) \
			size -= adj; \
	पूर्ण जबतक (0)

	adj_init_size(__init_begin, __init_end, init_data_size,
		     _sinittext, init_code_size);
	adj_init_size(_stext, _etext, codesize, _sinittext, init_code_size);
	adj_init_size(_sdata, _edata, datasize, __init_begin, init_data_size);
	adj_init_size(_stext, _etext, codesize, __start_rodata, rosize);
	adj_init_size(_sdata, _edata, datasize, __start_rodata, rosize);

#अघोषित	adj_init_size

	pr_info("Memory: %luK/%luK available (%luK kernel code, %luK rwdata, %luK rodata, %luK init, %luK bss, %luK reserved, %luK cma-reserved"
#अगर_घोषित	CONFIG_HIGHMEM
		", %luK highmem"
#पूर्ण_अगर
		")\n",
		nr_मुक्त_pages() << (PAGE_SHIFT - 10),
		physpages << (PAGE_SHIFT - 10),
		codesize >> 10, datasize >> 10, rosize >> 10,
		(init_data_size + init_code_size) >> 10, bss_size >> 10,
		(physpages - totalram_pages() - totalcma_pages) << (PAGE_SHIFT - 10),
		totalcma_pages << (PAGE_SHIFT - 10)
#अगर_घोषित	CONFIG_HIGHMEM
		, totalhigh_pages() << (PAGE_SHIFT - 10)
#पूर्ण_अगर
		);
पूर्ण

/**
 * set_dma_reserve - set the specअगरied number of pages reserved in the first zone
 * @new_dma_reserve: The number of pages to mark reserved
 *
 * The per-cpu batchsize and zone watermarks are determined by managed_pages.
 * In the DMA zone, a signअगरicant percentage may be consumed by kernel image
 * and other unमुक्तable allocations which can skew the watermarks badly. This
 * function may optionally be used to account क्रम unमुक्तable pages in the
 * first zone (e.g., ZONE_DMA). The effect will be lower watermarks and
 * smaller per-cpu batchsize.
 */
व्योम __init set_dma_reserve(अचिन्हित दीर्घ new_dma_reserve)
अणु
	dma_reserve = new_dma_reserve;
पूर्ण

अटल पूर्णांक page_alloc_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु

	lru_add_drain_cpu(cpu);
	drain_pages(cpu);

	/*
	 * Spill the event counters of the dead processor
	 * पूर्णांकo the current processors event counters.
	 * This artअगरicially elevates the count of the current
	 * processor.
	 */
	vm_events_fold_cpu(cpu);

	/*
	 * Zero the dअगरferential counters of the dead processor
	 * so that the vm statistics are consistent.
	 *
	 * This is only okay since the processor is dead and cannot
	 * race with what we are करोing.
	 */
	cpu_vm_stats_fold(cpu);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NUMA
पूर्णांक hashdist = HASHDIST_DEFAULT;

अटल पूर्णांक __init set_hashdist(अक्षर *str)
अणु
	अगर (!str)
		वापस 0;
	hashdist = simple_म_से_अदीर्घ(str, &str, 0);
	वापस 1;
पूर्ण
__setup("hashdist=", set_hashdist);
#पूर्ण_अगर

व्योम __init page_alloc_init(व्योम)
अणु
	पूर्णांक ret;

#अगर_घोषित CONFIG_NUMA
	अगर (num_node_state(N_MEMORY) == 1)
		hashdist = 0;
#पूर्ण_अगर

	ret = cpuhp_setup_state_nocalls(CPUHP_PAGE_ALLOC_DEAD,
					"mm/page_alloc:dead", शून्य,
					page_alloc_cpu_dead);
	WARN_ON(ret < 0);
पूर्ण

/*
 * calculate_totalreserve_pages - called when sysctl_lowmem_reserve_ratio
 *	or min_मुक्त_kbytes changes.
 */
अटल व्योम calculate_totalreserve_pages(व्योम)
अणु
	काष्ठा pglist_data *pgdat;
	अचिन्हित दीर्घ reserve_pages = 0;
	क्रमागत zone_type i, j;

	क्रम_each_online_pgdat(pgdat) अणु

		pgdat->totalreserve_pages = 0;

		क्रम (i = 0; i < MAX_NR_ZONES; i++) अणु
			काष्ठा zone *zone = pgdat->node_zones + i;
			दीर्घ max = 0;
			अचिन्हित दीर्घ managed_pages = zone_managed_pages(zone);

			/* Find valid and maximum lowmem_reserve in the zone */
			क्रम (j = i; j < MAX_NR_ZONES; j++) अणु
				अगर (zone->lowmem_reserve[j] > max)
					max = zone->lowmem_reserve[j];
			पूर्ण

			/* we treat the high watermark as reserved pages. */
			max += high_wmark_pages(zone);

			अगर (max > managed_pages)
				max = managed_pages;

			pgdat->totalreserve_pages += max;

			reserve_pages += max;
		पूर्ण
	पूर्ण
	totalreserve_pages = reserve_pages;
पूर्ण

/*
 * setup_per_zone_lowmem_reserve - called whenever
 *	sysctl_lowmem_reserve_ratio changes.  Ensures that each zone
 *	has a correct pages reserved value, so an adequate number of
 *	pages are left in the zone after a successful __alloc_pages().
 */
अटल व्योम setup_per_zone_lowmem_reserve(व्योम)
अणु
	काष्ठा pglist_data *pgdat;
	क्रमागत zone_type i, j;

	क्रम_each_online_pgdat(pgdat) अणु
		क्रम (i = 0; i < MAX_NR_ZONES - 1; i++) अणु
			काष्ठा zone *zone = &pgdat->node_zones[i];
			पूर्णांक ratio = sysctl_lowmem_reserve_ratio[i];
			bool clear = !ratio || !zone_managed_pages(zone);
			अचिन्हित दीर्घ managed_pages = 0;

			क्रम (j = i + 1; j < MAX_NR_ZONES; j++) अणु
				अगर (clear) अणु
					zone->lowmem_reserve[j] = 0;
				पूर्ण अन्यथा अणु
					काष्ठा zone *upper_zone = &pgdat->node_zones[j];

					managed_pages += zone_managed_pages(upper_zone);
					zone->lowmem_reserve[j] = managed_pages / ratio;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* update totalreserve_pages */
	calculate_totalreserve_pages();
पूर्ण

अटल व्योम __setup_per_zone_wmarks(व्योम)
अणु
	अचिन्हित दीर्घ pages_min = min_मुक्त_kbytes >> (PAGE_SHIFT - 10);
	अचिन्हित दीर्घ lowmem_pages = 0;
	काष्ठा zone *zone;
	अचिन्हित दीर्घ flags;

	/* Calculate total number of !ZONE_HIGHMEM pages */
	क्रम_each_zone(zone) अणु
		अगर (!is_highmem(zone))
			lowmem_pages += zone_managed_pages(zone);
	पूर्ण

	क्रम_each_zone(zone) अणु
		u64 पंचांगp;

		spin_lock_irqsave(&zone->lock, flags);
		पंचांगp = (u64)pages_min * zone_managed_pages(zone);
		करो_भाग(पंचांगp, lowmem_pages);
		अगर (is_highmem(zone)) अणु
			/*
			 * __GFP_HIGH and PF_MEMALLOC allocations usually करोn't
			 * need highmem pages, so cap pages_min to a small
			 * value here.
			 *
			 * The WMARK_HIGH-WMARK_LOW and (WMARK_LOW-WMARK_MIN)
			 * deltas control async page reclaim, and so should
			 * not be capped क्रम highmem.
			 */
			अचिन्हित दीर्घ min_pages;

			min_pages = zone_managed_pages(zone) / 1024;
			min_pages = clamp(min_pages, SWAP_CLUSTER_MAX, 128UL);
			zone->_watermark[WMARK_MIN] = min_pages;
		पूर्ण अन्यथा अणु
			/*
			 * If it's a lowmem zone, reserve a number of pages
			 * proportionate to the zone's size.
			 */
			zone->_watermark[WMARK_MIN] = पंचांगp;
		पूर्ण

		/*
		 * Set the kswapd watermarks distance according to the
		 * scale factor in proportion to available memory, but
		 * ensure a minimum size on small प्रणालीs.
		 */
		पंचांगp = max_t(u64, पंचांगp >> 2,
			    mult_frac(zone_managed_pages(zone),
				      watermark_scale_factor, 10000));

		zone->watermark_boost = 0;
		zone->_watermark[WMARK_LOW]  = min_wmark_pages(zone) + पंचांगp;
		zone->_watermark[WMARK_HIGH] = min_wmark_pages(zone) + पंचांगp * 2;

		spin_unlock_irqrestore(&zone->lock, flags);
	पूर्ण

	/* update totalreserve_pages */
	calculate_totalreserve_pages();
पूर्ण

/**
 * setup_per_zone_wmarks - called when min_मुक्त_kbytes changes
 * or when memory is hot-अणुadded|हटाओdपूर्ण
 *
 * Ensures that the watermark[min,low,high] values क्रम each zone are set
 * correctly with respect to min_मुक्त_kbytes.
 */
व्योम setup_per_zone_wmarks(व्योम)
अणु
	अटल DEFINE_SPINLOCK(lock);

	spin_lock(&lock);
	__setup_per_zone_wmarks();
	spin_unlock(&lock);
पूर्ण

/*
 * Initialise min_मुक्त_kbytes.
 *
 * For small machines we want it small (128k min).  For large machines
 * we want it large (256MB max).  But it is not linear, because network
 * bandwidth करोes not increase linearly with machine size.  We use
 *
 *	min_मुक्त_kbytes = 4 * वर्ग_मूल(lowmem_kbytes), क्रम better accuracy:
 *	min_मुक्त_kbytes = वर्ग_मूल(lowmem_kbytes * 16)
 *
 * which yields
 *
 * 16MB:	512k
 * 32MB:	724k
 * 64MB:	1024k
 * 128MB:	1448k
 * 256MB:	2048k
 * 512MB:	2896k
 * 1024MB:	4096k
 * 2048MB:	5792k
 * 4096MB:	8192k
 * 8192MB:	11584k
 * 16384MB:	16384k
 */
पूर्णांक __meminit init_per_zone_wmark_min(व्योम)
अणु
	अचिन्हित दीर्घ lowmem_kbytes;
	पूर्णांक new_min_मुक्त_kbytes;

	lowmem_kbytes = nr_मुक्त_buffer_pages() * (PAGE_SIZE >> 10);
	new_min_मुक्त_kbytes = पूर्णांक_वर्ग_मूल(lowmem_kbytes * 16);

	अगर (new_min_मुक्त_kbytes > user_min_मुक्त_kbytes) अणु
		min_मुक्त_kbytes = new_min_मुक्त_kbytes;
		अगर (min_मुक्त_kbytes < 128)
			min_मुक्त_kbytes = 128;
		अगर (min_मुक्त_kbytes > 262144)
			min_मुक्त_kbytes = 262144;
	पूर्ण अन्यथा अणु
		pr_warn("min_free_kbytes is not updated to %d because user defined value %d is preferred\n",
				new_min_मुक्त_kbytes, user_min_मुक्त_kbytes);
	पूर्ण
	setup_per_zone_wmarks();
	refresh_zone_stat_thresholds();
	setup_per_zone_lowmem_reserve();

#अगर_घोषित CONFIG_NUMA
	setup_min_unmapped_ratio();
	setup_min_slab_ratio();
#पूर्ण_अगर

	khugepaged_min_मुक्त_kbytes_update();

	वापस 0;
पूर्ण
postcore_initcall(init_per_zone_wmark_min)

/*
 * min_मुक्त_kbytes_sysctl_handler - just a wrapper around proc_करोपूर्णांकvec() so
 *	that we can call two helper functions whenever min_मुक्त_kbytes
 *	changes.
 */
पूर्णांक min_मुक्त_kbytes_sysctl_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *length, loff_t *ppos)
अणु
	पूर्णांक rc;

	rc = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, length, ppos);
	अगर (rc)
		वापस rc;

	अगर (ग_लिखो) अणु
		user_min_मुक्त_kbytes = min_मुक्त_kbytes;
		setup_per_zone_wmarks();
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक watermark_scale_factor_sysctl_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *length, loff_t *ppos)
अणु
	पूर्णांक rc;

	rc = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, length, ppos);
	अगर (rc)
		वापस rc;

	अगर (ग_लिखो)
		setup_per_zone_wmarks();

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NUMA
अटल व्योम setup_min_unmapped_ratio(व्योम)
अणु
	pg_data_t *pgdat;
	काष्ठा zone *zone;

	क्रम_each_online_pgdat(pgdat)
		pgdat->min_unmapped_pages = 0;

	क्रम_each_zone(zone)
		zone->zone_pgdat->min_unmapped_pages += (zone_managed_pages(zone) *
						         sysctl_min_unmapped_ratio) / 100;
पूर्ण


पूर्णांक sysctl_min_unmapped_ratio_sysctl_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *length, loff_t *ppos)
अणु
	पूर्णांक rc;

	rc = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, length, ppos);
	अगर (rc)
		वापस rc;

	setup_min_unmapped_ratio();

	वापस 0;
पूर्ण

अटल व्योम setup_min_slab_ratio(व्योम)
अणु
	pg_data_t *pgdat;
	काष्ठा zone *zone;

	क्रम_each_online_pgdat(pgdat)
		pgdat->min_slab_pages = 0;

	क्रम_each_zone(zone)
		zone->zone_pgdat->min_slab_pages += (zone_managed_pages(zone) *
						     sysctl_min_slab_ratio) / 100;
पूर्ण

पूर्णांक sysctl_min_slab_ratio_sysctl_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *length, loff_t *ppos)
अणु
	पूर्णांक rc;

	rc = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, length, ppos);
	अगर (rc)
		वापस rc;

	setup_min_slab_ratio();

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * lowmem_reserve_ratio_sysctl_handler - just a wrapper around
 *	proc_करोपूर्णांकvec() so that we can call setup_per_zone_lowmem_reserve()
 *	whenever sysctl_lowmem_reserve_ratio changes.
 *
 * The reserve ratio obviously has असलolutely no relation with the
 * minimum watermarks. The lowmem reserve ratio can only make sense
 * अगर in function of the boot समय zone sizes.
 */
पूर्णांक lowmem_reserve_ratio_sysctl_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *length, loff_t *ppos)
अणु
	पूर्णांक i;

	proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, length, ppos);

	क्रम (i = 0; i < MAX_NR_ZONES; i++) अणु
		अगर (sysctl_lowmem_reserve_ratio[i] < 1)
			sysctl_lowmem_reserve_ratio[i] = 0;
	पूर्ण

	setup_per_zone_lowmem_reserve();
	वापस 0;
पूर्ण

/*
 * percpu_pagelist_fraction - changes the pcp->high क्रम each zone on each
 * cpu.  It is the fraction of total pages in each zone that a hot per cpu
 * pagelist can have beक्रमe it माला_लो flushed back to buddy allocator.
 */
पूर्णांक percpu_pagelist_fraction_sysctl_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *length, loff_t *ppos)
अणु
	काष्ठा zone *zone;
	पूर्णांक old_percpu_pagelist_fraction;
	पूर्णांक ret;

	mutex_lock(&pcp_batch_high_lock);
	old_percpu_pagelist_fraction = percpu_pagelist_fraction;

	ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, length, ppos);
	अगर (!ग_लिखो || ret < 0)
		जाओ out;

	/* Sanity checking to aव्योम pcp imbalance */
	अगर (percpu_pagelist_fraction &&
	    percpu_pagelist_fraction < MIN_PERCPU_PAGELIST_FRACTION) अणु
		percpu_pagelist_fraction = old_percpu_pagelist_fraction;
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* No change? */
	अगर (percpu_pagelist_fraction == old_percpu_pagelist_fraction)
		जाओ out;

	क्रम_each_populated_zone(zone)
		zone_set_pageset_high_and_batch(zone);
out:
	mutex_unlock(&pcp_batch_high_lock);
	वापस ret;
पूर्ण

#अगर_अघोषित __HAVE_ARCH_RESERVED_KERNEL_PAGES
/*
 * Returns the number of pages that arch has reserved but
 * is not known to alloc_large_प्रणाली_hash().
 */
अटल अचिन्हित दीर्घ __init arch_reserved_kernel_pages(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Adaptive scale is meant to reduce sizes of hash tables on large memory
 * machines. As memory size is increased the scale is also increased but at
 * slower pace.  Starting from ADAPT_SCALE_BASE (64G), every समय memory
 * quadruples the scale is increased by one, which means the size of hash table
 * only द्विगुनs, instead of quadrupling as well.
 * Because 32-bit प्रणालीs cannot have large physical memory, where this scaling
 * makes sense, it is disabled on such platक्रमms.
 */
#अगर __BITS_PER_LONG > 32
#घोषणा ADAPT_SCALE_BASE	(64ul << 30)
#घोषणा ADAPT_SCALE_SHIFT	2
#घोषणा ADAPT_SCALE_NPAGES	(ADAPT_SCALE_BASE >> PAGE_SHIFT)
#पूर्ण_अगर

/*
 * allocate a large प्रणाली hash table from booपंचांगem
 * - it is assumed that the hash table must contain an exact घातer-of-2
 *   quantity of entries
 * - limit is the number of hash buckets, not the total allocation size
 */
व्योम *__init alloc_large_प्रणाली_hash(स्थिर अक्षर *tablename,
				     अचिन्हित दीर्घ bucketsize,
				     अचिन्हित दीर्घ numentries,
				     पूर्णांक scale,
				     पूर्णांक flags,
				     अचिन्हित पूर्णांक *_hash_shअगरt,
				     अचिन्हित पूर्णांक *_hash_mask,
				     अचिन्हित दीर्घ low_limit,
				     अचिन्हित दीर्घ high_limit)
अणु
	अचिन्हित दीर्घ दीर्घ max = high_limit;
	अचिन्हित दीर्घ log2qty, size;
	व्योम *table = शून्य;
	gfp_t gfp_flags;
	bool virt;
	bool huge;

	/* allow the kernel cmdline to have a say */
	अगर (!numentries) अणु
		/* round applicable memory size up to nearest megabyte */
		numentries = nr_kernel_pages;
		numentries -= arch_reserved_kernel_pages();

		/* It isn't necessary when PAGE_SIZE >= 1MB */
		अगर (PAGE_SHIFT < 20)
			numentries = round_up(numentries, (1<<20)/PAGE_SIZE);

#अगर __BITS_PER_LONG > 32
		अगर (!high_limit) अणु
			अचिन्हित दीर्घ adapt;

			क्रम (adapt = ADAPT_SCALE_NPAGES; adapt < numentries;
			     adapt <<= ADAPT_SCALE_SHIFT)
				scale++;
		पूर्ण
#पूर्ण_अगर

		/* limit to 1 bucket per 2^scale bytes of low memory */
		अगर (scale > PAGE_SHIFT)
			numentries >>= (scale - PAGE_SHIFT);
		अन्यथा
			numentries <<= (PAGE_SHIFT - scale);

		/* Make sure we've got at least a 0-order allocation.. */
		अगर (unlikely(flags & HASH_SMALL)) अणु
			/* Makes no sense without HASH_EARLY */
			WARN_ON(!(flags & HASH_EARLY));
			अगर (!(numentries >> *_hash_shअगरt)) अणु
				numentries = 1UL << *_hash_shअगरt;
				BUG_ON(!numentries);
			पूर्ण
		पूर्ण अन्यथा अगर (unlikely((numentries * bucketsize) < PAGE_SIZE))
			numentries = PAGE_SIZE / bucketsize;
	पूर्ण
	numentries = roundup_घात_of_two(numentries);

	/* limit allocation size to 1/16 total memory by शेष */
	अगर (max == 0) अणु
		max = ((अचिन्हित दीर्घ दीर्घ)nr_all_pages << PAGE_SHIFT) >> 4;
		करो_भाग(max, bucketsize);
	पूर्ण
	max = min(max, 0x80000000ULL);

	अगर (numentries < low_limit)
		numentries = low_limit;
	अगर (numentries > max)
		numentries = max;

	log2qty = ilog2(numentries);

	gfp_flags = (flags & HASH_ZERO) ? GFP_ATOMIC | __GFP_ZERO : GFP_ATOMIC;
	करो अणु
		virt = false;
		size = bucketsize << log2qty;
		अगर (flags & HASH_EARLY) अणु
			अगर (flags & HASH_ZERO)
				table = memblock_alloc(size, SMP_CACHE_BYTES);
			अन्यथा
				table = memblock_alloc_raw(size,
							   SMP_CACHE_BYTES);
		पूर्ण अन्यथा अगर (get_order(size) >= MAX_ORDER || hashdist) अणु
			table = __vदो_स्मृति(size, gfp_flags);
			virt = true;
			huge = is_vm_area_hugepages(table);
		पूर्ण अन्यथा अणु
			/*
			 * If bucketsize is not a घातer-of-two, we may मुक्त
			 * some pages at the end of hash table which
			 * alloc_pages_exact() स्वतःmatically करोes
			 */
			table = alloc_pages_exact(size, gfp_flags);
			kmemleak_alloc(table, size, 1, gfp_flags);
		पूर्ण
	पूर्ण जबतक (!table && size > PAGE_SIZE && --log2qty);

	अगर (!table)
		panic("Failed to allocate %s hash table\n", tablename);

	pr_info("%s hash table entries: %ld (order: %d, %lu bytes, %s)\n",
		tablename, 1UL << log2qty, ilog2(size) - PAGE_SHIFT, size,
		virt ? (huge ? "vmalloc hugepage" : "vmalloc") : "linear");

	अगर (_hash_shअगरt)
		*_hash_shअगरt = log2qty;
	अगर (_hash_mask)
		*_hash_mask = (1 << log2qty) - 1;

	वापस table;
पूर्ण

/*
 * This function checks whether pageblock includes unmovable pages or not.
 *
 * PageLRU check without isolation or lru_lock could race so that
 * MIGRATE_MOVABLE block might include unmovable pages. And __PageMovable
 * check without lock_page also may miss some movable non-lru pages at
 * race condition. So you can't expect this function should be exact.
 *
 * Returns a page without holding a reference. If the caller wants to
 * dereference that page (e.g., dumping), it has to make sure that it
 * cannot get हटाओd (e.g., via memory unplug) concurrently.
 *
 */
काष्ठा page *has_unmovable_pages(काष्ठा zone *zone, काष्ठा page *page,
				 पूर्णांक migratetype, पूर्णांक flags)
अणु
	अचिन्हित दीर्घ iter = 0;
	अचिन्हित दीर्घ pfn = page_to_pfn(page);
	अचिन्हित दीर्घ offset = pfn % pageblock_nr_pages;

	अगर (is_migrate_cma_page(page)) अणु
		/*
		 * CMA allocations (alloc_contig_range) really need to mark
		 * isolate CMA pageblocks even when they are not movable in fact
		 * so consider them movable here.
		 */
		अगर (is_migrate_cma(migratetype))
			वापस शून्य;

		वापस page;
	पूर्ण

	क्रम (; iter < pageblock_nr_pages - offset; iter++) अणु
		अगर (!pfn_valid_within(pfn + iter))
			जारी;

		page = pfn_to_page(pfn + iter);

		/*
		 * Both, booपंचांगem allocations and memory holes are marked
		 * PG_reserved and are unmovable. We can even have unmovable
		 * allocations inside ZONE_MOVABLE, क्रम example when
		 * specअगरying "movablecore".
		 */
		अगर (PageReserved(page))
			वापस page;

		/*
		 * If the zone is movable and we have ruled out all reserved
		 * pages then it should be reasonably safe to assume the rest
		 * is movable.
		 */
		अगर (zone_idx(zone) == ZONE_MOVABLE)
			जारी;

		/*
		 * Hugepages are not in LRU lists, but they're movable.
		 * THPs are on the LRU, but need to be counted as #small pages.
		 * We need not scan over tail pages because we करोn't
		 * handle each tail page inभागidually in migration.
		 */
		अगर (PageHuge(page) || PageTransCompound(page)) अणु
			काष्ठा page *head = compound_head(page);
			अचिन्हित पूर्णांक skip_pages;

			अगर (PageHuge(page)) अणु
				अगर (!hugepage_migration_supported(page_hstate(head)))
					वापस page;
			पूर्ण अन्यथा अगर (!PageLRU(head) && !__PageMovable(head)) अणु
				वापस page;
			पूर्ण

			skip_pages = compound_nr(head) - (page - head);
			iter += skip_pages - 1;
			जारी;
		पूर्ण

		/*
		 * We can't use page_count without pin a page
		 * because another CPU can मुक्त compound page.
		 * This check alपढ़ोy skips compound tails of THP
		 * because their page->_refcount is zero at all समय.
		 */
		अगर (!page_ref_count(page)) अणु
			अगर (PageBuddy(page))
				iter += (1 << buddy_order(page)) - 1;
			जारी;
		पूर्ण

		/*
		 * The HWPoisoned page may be not in buddy प्रणाली, and
		 * page_count() is not 0.
		 */
		अगर ((flags & MEMORY_OFFLINE) && PageHWPoison(page))
			जारी;

		/*
		 * We treat all PageOffline() pages as movable when offlining
		 * to give drivers a chance to decrement their reference count
		 * in MEM_GOING_OFFLINE in order to indicate that these pages
		 * can be offlined as there are no direct references anymore.
		 * For actually unmovable PageOffline() where the driver करोes
		 * not support this, we will fail later when trying to actually
		 * move these pages that still have a reference count > 0.
		 * (false negatives in this function only)
		 */
		अगर ((flags & MEMORY_OFFLINE) && PageOffline(page))
			जारी;

		अगर (__PageMovable(page) || PageLRU(page))
			जारी;

		/*
		 * If there are RECLAIMABLE pages, we need to check
		 * it.  But now, memory offline itself करोesn't call
		 * shrink_node_sद_असल() and it still to be fixed.
		 */
		वापस page;
	पूर्ण
	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_CONTIG_ALLOC
अटल अचिन्हित दीर्घ pfn_max_align_करोwn(अचिन्हित दीर्घ pfn)
अणु
	वापस pfn & ~(max_t(अचिन्हित दीर्घ, MAX_ORDER_NR_PAGES,
			     pageblock_nr_pages) - 1);
पूर्ण

अटल अचिन्हित दीर्घ pfn_max_align_up(अचिन्हित दीर्घ pfn)
अणु
	वापस ALIGN(pfn, max_t(अचिन्हित दीर्घ, MAX_ORDER_NR_PAGES,
				pageblock_nr_pages));
पूर्ण

#अगर defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_CORE) && defined(DYNAMIC_DEBUG_MODULE))
/* Usage: See admin-guide/dynamic-debug-howto.rst */
अटल व्योम alloc_contig_dump_pages(काष्ठा list_head *page_list)
अणु
	DEFINE_DYNAMIC_DEBUG_METADATA(descriptor, "migrate failure");

	अगर (DYNAMIC_DEBUG_BRANCH(descriptor)) अणु
		काष्ठा page *page;

		dump_stack();
		list_क्रम_each_entry(page, page_list, lru)
			dump_page(page, "migration failure");
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम alloc_contig_dump_pages(काष्ठा list_head *page_list)
अणु
पूर्ण
#पूर्ण_अगर

/* [start, end) must beदीर्घ to a single zone. */
अटल पूर्णांक __alloc_contig_migrate_range(काष्ठा compact_control *cc,
					अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	/* This function is based on compact_zone() from compaction.c. */
	अचिन्हित पूर्णांक nr_reclaimed;
	अचिन्हित दीर्घ pfn = start;
	अचिन्हित पूर्णांक tries = 0;
	पूर्णांक ret = 0;
	काष्ठा migration_target_control mtc = अणु
		.nid = zone_to_nid(cc->zone),
		.gfp_mask = GFP_USER | __GFP_MOVABLE | __GFP_RETRY_MAYFAIL,
	पूर्ण;

	lru_cache_disable();

	जबतक (pfn < end || !list_empty(&cc->migratepages)) अणु
		अगर (fatal_संकेत_pending(current)) अणु
			ret = -EINTR;
			अवरोध;
		पूर्ण

		अगर (list_empty(&cc->migratepages)) अणु
			cc->nr_migratepages = 0;
			ret = isolate_migratepages_range(cc, pfn, end);
			अगर (ret && ret != -EAGAIN)
				अवरोध;
			pfn = cc->migrate_pfn;
			tries = 0;
		पूर्ण अन्यथा अगर (++tries == 5) अणु
			ret = -EBUSY;
			अवरोध;
		पूर्ण

		nr_reclaimed = reclaim_clean_pages_from_list(cc->zone,
							&cc->migratepages);
		cc->nr_migratepages -= nr_reclaimed;

		ret = migrate_pages(&cc->migratepages, alloc_migration_target,
				शून्य, (अचिन्हित दीर्घ)&mtc, cc->mode, MR_CONTIG_RANGE);

		/*
		 * On -ENOMEM, migrate_pages() bails out right away. It is poपूर्णांकless
		 * to retry again over this error, so करो the same here.
		 */
		अगर (ret == -ENOMEM)
			अवरोध;
	पूर्ण

	lru_cache_enable();
	अगर (ret < 0) अणु
		alloc_contig_dump_pages(&cc->migratepages);
		putback_movable_pages(&cc->migratepages);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * alloc_contig_range() -- tries to allocate given range of pages
 * @start:	start PFN to allocate
 * @end:	one-past-the-last PFN to allocate
 * @migratetype:	migratetype of the underlying pageblocks (either
 *			#MIGRATE_MOVABLE or #MIGRATE_CMA).  All pageblocks
 *			in range must have the same migratetype and it must
 *			be either of the two.
 * @gfp_mask:	GFP mask to use during compaction
 *
 * The PFN range करोes not have to be pageblock or MAX_ORDER_NR_PAGES
 * aligned.  The PFN range must beदीर्घ to a single zone.
 *
 * The first thing this routine करोes is attempt to MIGRATE_ISOLATE all
 * pageblocks in the range.  Once isolated, the pageblocks should not
 * be modअगरied by others.
 *
 * Return: zero on success or negative error code.  On success all
 * pages which PFN is in [start, end) are allocated क्रम the caller and
 * need to be मुक्तd with मुक्त_contig_range().
 */
पूर्णांक alloc_contig_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
		       अचिन्हित migratetype, gfp_t gfp_mask)
अणु
	अचिन्हित दीर्घ outer_start, outer_end;
	अचिन्हित पूर्णांक order;
	पूर्णांक ret = 0;

	काष्ठा compact_control cc = अणु
		.nr_migratepages = 0,
		.order = -1,
		.zone = page_zone(pfn_to_page(start)),
		.mode = MIGRATE_SYNC,
		.ignore_skip_hपूर्णांक = true,
		.no_set_skip_hपूर्णांक = true,
		.gfp_mask = current_gfp_context(gfp_mask),
		.alloc_contig = true,
	पूर्ण;
	INIT_LIST_HEAD(&cc.migratepages);

	/*
	 * What we करो here is we mark all pageblocks in range as
	 * MIGRATE_ISOLATE.  Because pageblock and max order pages may
	 * have dअगरferent sizes, and due to the way page allocator
	 * work, we align the range to biggest of the two pages so
	 * that page allocator won't try to merge buddies from
	 * dअगरferent pageblocks and change MIGRATE_ISOLATE to some
	 * other migration type.
	 *
	 * Once the pageblocks are marked as MIGRATE_ISOLATE, we
	 * migrate the pages from an unaligned range (ie. pages that
	 * we are पूर्णांकerested in).  This will put all the pages in
	 * range back to page allocator as MIGRATE_ISOLATE.
	 *
	 * When this is करोne, we take the pages in range from page
	 * allocator removing them from the buddy प्रणाली.  This way
	 * page allocator will never consider using them.
	 *
	 * This lets us mark the pageblocks back as
	 * MIGRATE_CMA/MIGRATE_MOVABLE so that मुक्त pages in the
	 * aligned range but not in the unaligned, original range are
	 * put back to page allocator so that buddy can use them.
	 */

	ret = start_isolate_page_range(pfn_max_align_करोwn(start),
				       pfn_max_align_up(end), migratetype, 0);
	अगर (ret)
		वापस ret;

	drain_all_pages(cc.zone);

	/*
	 * In हाल of -EBUSY, we'd like to know which page causes problem.
	 * So, just fall through. test_pages_isolated() has a tracepoपूर्णांक
	 * which will report the busy page.
	 *
	 * It is possible that busy pages could become available beक्रमe
	 * the call to test_pages_isolated, and the range will actually be
	 * allocated.  So, अगर we fall through be sure to clear ret so that
	 * -EBUSY is not accidentally used or वापसed to caller.
	 */
	ret = __alloc_contig_migrate_range(&cc, start, end);
	अगर (ret && ret != -EBUSY)
		जाओ करोne;
	ret = 0;

	/*
	 * Pages from [start, end) are within a MAX_ORDER_NR_PAGES
	 * aligned blocks that are marked as MIGRATE_ISOLATE.  What's
	 * more, all pages in [start, end) are मुक्त in page allocator.
	 * What we are going to करो is to allocate all pages from
	 * [start, end) (that is हटाओ them from page allocator).
	 *
	 * The only problem is that pages at the beginning and at the
	 * end of पूर्णांकeresting range may be not aligned with pages that
	 * page allocator holds, ie. they can be part of higher order
	 * pages.  Because of this, we reserve the bigger range and
	 * once this is करोne मुक्त the pages we are not पूर्णांकerested in.
	 *
	 * We करोn't have to hold zone->lock here because the pages are
	 * isolated thus they won't get हटाओd from buddy.
	 */

	order = 0;
	outer_start = start;
	जबतक (!PageBuddy(pfn_to_page(outer_start))) अणु
		अगर (++order >= MAX_ORDER) अणु
			outer_start = start;
			अवरोध;
		पूर्ण
		outer_start &= ~0UL << order;
	पूर्ण

	अगर (outer_start != start) अणु
		order = buddy_order(pfn_to_page(outer_start));

		/*
		 * outer_start page could be small order buddy page and
		 * it करोesn't include start page. Adjust outer_start
		 * in this हाल to report failed page properly
		 * on tracepoपूर्णांक in test_pages_isolated()
		 */
		अगर (outer_start + (1UL << order) <= start)
			outer_start = start;
	पूर्ण

	/* Make sure the range is really isolated. */
	अगर (test_pages_isolated(outer_start, end, 0)) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	/* Grab isolated pages from मुक्तlists. */
	outer_end = isolate_मुक्तpages_range(&cc, outer_start, end);
	अगर (!outer_end) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	/* Free head and tail (अगर any) */
	अगर (start != outer_start)
		मुक्त_contig_range(outer_start, start - outer_start);
	अगर (end != outer_end)
		मुक्त_contig_range(end, outer_end - end);

करोne:
	unकरो_isolate_page_range(pfn_max_align_करोwn(start),
				pfn_max_align_up(end), migratetype);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(alloc_contig_range);

अटल पूर्णांक __alloc_contig_pages(अचिन्हित दीर्घ start_pfn,
				अचिन्हित दीर्घ nr_pages, gfp_t gfp_mask)
अणु
	अचिन्हित दीर्घ end_pfn = start_pfn + nr_pages;

	वापस alloc_contig_range(start_pfn, end_pfn, MIGRATE_MOVABLE,
				  gfp_mask);
पूर्ण

अटल bool pfn_range_valid_contig(काष्ठा zone *z, अचिन्हित दीर्घ start_pfn,
				   अचिन्हित दीर्घ nr_pages)
अणु
	अचिन्हित दीर्घ i, end_pfn = start_pfn + nr_pages;
	काष्ठा page *page;

	क्रम (i = start_pfn; i < end_pfn; i++) अणु
		page = pfn_to_online_page(i);
		अगर (!page)
			वापस false;

		अगर (page_zone(page) != z)
			वापस false;

		अगर (PageReserved(page))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool zone_spans_last_pfn(स्थिर काष्ठा zone *zone,
				अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ nr_pages)
अणु
	अचिन्हित दीर्घ last_pfn = start_pfn + nr_pages - 1;

	वापस zone_spans_pfn(zone, last_pfn);
पूर्ण

/**
 * alloc_contig_pages() -- tries to find and allocate contiguous range of pages
 * @nr_pages:	Number of contiguous pages to allocate
 * @gfp_mask:	GFP mask to limit search and used during compaction
 * @nid:	Target node
 * @nodemask:	Mask क्रम other possible nodes
 *
 * This routine is a wrapper around alloc_contig_range(). It scans over zones
 * on an applicable zonelist to find a contiguous pfn range which can then be
 * tried क्रम allocation with alloc_contig_range(). This routine is पूर्णांकended
 * क्रम allocation requests which can not be fulfilled with the buddy allocator.
 *
 * The allocated memory is always aligned to a page boundary. If nr_pages is a
 * घातer of two then the alignment is guaranteed to be to the given nr_pages
 * (e.g. 1GB request would be aligned to 1GB).
 *
 * Allocated pages can be मुक्तd with मुक्त_contig_range() or by manually calling
 * __मुक्त_page() on each allocated page.
 *
 * Return: poपूर्णांकer to contiguous pages on success, or शून्य अगर not successful.
 */
काष्ठा page *alloc_contig_pages(अचिन्हित दीर्घ nr_pages, gfp_t gfp_mask,
				पूर्णांक nid, nodemask_t *nodemask)
अणु
	अचिन्हित दीर्घ ret, pfn, flags;
	काष्ठा zonelist *zonelist;
	काष्ठा zone *zone;
	काष्ठा zoneref *z;

	zonelist = node_zonelist(nid, gfp_mask);
	क्रम_each_zone_zonelist_nodemask(zone, z, zonelist,
					gfp_zone(gfp_mask), nodemask) अणु
		spin_lock_irqsave(&zone->lock, flags);

		pfn = ALIGN(zone->zone_start_pfn, nr_pages);
		जबतक (zone_spans_last_pfn(zone, pfn, nr_pages)) अणु
			अगर (pfn_range_valid_contig(zone, pfn, nr_pages)) अणु
				/*
				 * We release the zone lock here because
				 * alloc_contig_range() will also lock the zone
				 * at some poपूर्णांक. If there's an allocation
				 * spinning on this lock, it may win the race
				 * and cause alloc_contig_range() to fail...
				 */
				spin_unlock_irqrestore(&zone->lock, flags);
				ret = __alloc_contig_pages(pfn, nr_pages,
							gfp_mask);
				अगर (!ret)
					वापस pfn_to_page(pfn);
				spin_lock_irqsave(&zone->lock, flags);
			पूर्ण
			pfn += nr_pages;
		पूर्ण
		spin_unlock_irqrestore(&zone->lock, flags);
	पूर्ण
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_CONTIG_ALLOC */

व्योम मुक्त_contig_range(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages)
अणु
	अचिन्हित दीर्घ count = 0;

	क्रम (; nr_pages--; pfn++) अणु
		काष्ठा page *page = pfn_to_page(pfn);

		count += page_count(page) != 1;
		__मुक्त_page(page);
	पूर्ण
	WARN(count != 0, "%lu pages are still in use!\n", count);
पूर्ण
EXPORT_SYMBOL(मुक्त_contig_range);

/*
 * The zone indicated has a new number of managed_pages; batch sizes and percpu
 * page high values need to be recalculated.
 */
व्योम __meminit zone_pcp_update(काष्ठा zone *zone)
अणु
	mutex_lock(&pcp_batch_high_lock);
	zone_set_pageset_high_and_batch(zone);
	mutex_unlock(&pcp_batch_high_lock);
पूर्ण

/*
 * Effectively disable pcplists क्रम the zone by setting the high limit to 0
 * and draining all cpus. A concurrent page मुक्तing on another CPU that's about
 * to put the page on pcplist will either finish beक्रमe the drain and the page
 * will be drained, or observe the new high limit and skip the pcplist.
 *
 * Must be paired with a call to zone_pcp_enable().
 */
व्योम zone_pcp_disable(काष्ठा zone *zone)
अणु
	mutex_lock(&pcp_batch_high_lock);
	__zone_set_pageset_high_and_batch(zone, 0, 1);
	__drain_all_pages(zone, true);
पूर्ण

व्योम zone_pcp_enable(काष्ठा zone *zone)
अणु
	__zone_set_pageset_high_and_batch(zone, zone->pageset_high, zone->pageset_batch);
	mutex_unlock(&pcp_batch_high_lock);
पूर्ण

व्योम zone_pcp_reset(काष्ठा zone *zone)
अणु
	पूर्णांक cpu;
	काष्ठा per_cpu_pageset *pset;

	अगर (zone->pageset != &boot_pageset) अणु
		क्रम_each_online_cpu(cpu) अणु
			pset = per_cpu_ptr(zone->pageset, cpu);
			drain_zonestat(zone, pset);
		पूर्ण
		मुक्त_percpu(zone->pageset);
		zone->pageset = &boot_pageset;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTREMOVE
/*
 * All pages in the range must be in a single zone, must not contain holes,
 * must span full sections, and must be isolated beक्रमe calling this function.
 */
व्योम __offline_isolated_pages(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn)
अणु
	अचिन्हित दीर्घ pfn = start_pfn;
	काष्ठा page *page;
	काष्ठा zone *zone;
	अचिन्हित पूर्णांक order;
	अचिन्हित दीर्घ flags;

	offline_mem_sections(pfn, end_pfn);
	zone = page_zone(pfn_to_page(pfn));
	spin_lock_irqsave(&zone->lock, flags);
	जबतक (pfn < end_pfn) अणु
		page = pfn_to_page(pfn);
		/*
		 * The HWPoisoned page may be not in buddy प्रणाली, and
		 * page_count() is not 0.
		 */
		अगर (unlikely(!PageBuddy(page) && PageHWPoison(page))) अणु
			pfn++;
			जारी;
		पूर्ण
		/*
		 * At this poपूर्णांक all reमुख्यing PageOffline() pages have a
		 * reference count of 0 and can simply be skipped.
		 */
		अगर (PageOffline(page)) अणु
			BUG_ON(page_count(page));
			BUG_ON(PageBuddy(page));
			pfn++;
			जारी;
		पूर्ण

		BUG_ON(page_count(page));
		BUG_ON(!PageBuddy(page));
		order = buddy_order(page);
		del_page_from_मुक्त_list(page, zone, order);
		pfn += (1 << order);
	पूर्ण
	spin_unlock_irqrestore(&zone->lock, flags);
पूर्ण
#पूर्ण_अगर

bool is_मुक्त_buddy_page(काष्ठा page *page)
अणु
	काष्ठा zone *zone = page_zone(page);
	अचिन्हित दीर्घ pfn = page_to_pfn(page);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक order;

	spin_lock_irqsave(&zone->lock, flags);
	क्रम (order = 0; order < MAX_ORDER; order++) अणु
		काष्ठा page *page_head = page - (pfn & ((1 << order) - 1));

		अगर (PageBuddy(page_head) && buddy_order(page_head) >= order)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&zone->lock, flags);

	वापस order < MAX_ORDER;
पूर्ण

#अगर_घोषित CONFIG_MEMORY_FAILURE
/*
 * Break करोwn a higher-order page in sub-pages, and keep our target out of
 * buddy allocator.
 */
अटल व्योम अवरोध_करोwn_buddy_pages(काष्ठा zone *zone, काष्ठा page *page,
				   काष्ठा page *target, पूर्णांक low, पूर्णांक high,
				   पूर्णांक migratetype)
अणु
	अचिन्हित दीर्घ size = 1 << high;
	काष्ठा page *current_buddy, *next_page;

	जबतक (high > low) अणु
		high--;
		size >>= 1;

		अगर (target >= &page[size]) अणु
			next_page = page + size;
			current_buddy = page;
		पूर्ण अन्यथा अणु
			next_page = page;
			current_buddy = page + size;
		पूर्ण

		अगर (set_page_guard(zone, current_buddy, high, migratetype))
			जारी;

		अगर (current_buddy != target) अणु
			add_to_मुक्त_list(current_buddy, zone, high, migratetype);
			set_buddy_order(current_buddy, high);
			page = next_page;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Take a page that will be marked as poisoned off the buddy allocator.
 */
bool take_page_off_buddy(काष्ठा page *page)
अणु
	काष्ठा zone *zone = page_zone(page);
	अचिन्हित दीर्घ pfn = page_to_pfn(page);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक order;
	bool ret = false;

	spin_lock_irqsave(&zone->lock, flags);
	क्रम (order = 0; order < MAX_ORDER; order++) अणु
		काष्ठा page *page_head = page - (pfn & ((1 << order) - 1));
		पूर्णांक page_order = buddy_order(page_head);

		अगर (PageBuddy(page_head) && page_order >= order) अणु
			अचिन्हित दीर्घ pfn_head = page_to_pfn(page_head);
			पूर्णांक migratetype = get_pfnblock_migratetype(page_head,
								   pfn_head);

			del_page_from_मुक्त_list(page_head, zone, page_order);
			अवरोध_करोwn_buddy_pages(zone, page_head, page, 0,
						page_order, migratetype);
			अगर (!is_migrate_isolate(migratetype))
				__mod_zone_मुक्तpage_state(zone, -1, migratetype);
			ret = true;
			अवरोध;
		पूर्ण
		अगर (page_count(page_head) > 0)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&zone->lock, flags);
	वापस ret;
पूर्ण
#पूर्ण_अगर
