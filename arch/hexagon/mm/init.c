<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Memory subप्रणाली initialization क्रम Hexagon
 *
 * Copyright (c) 2010-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/atomic.h>
#समावेश <linux/highस्मृति.स>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/vm_mmu.h>

/*
 * Define a startpg just past the end of the kernel image and a lastpg
 * that corresponds to the end of real or simulated platक्रमm memory.
 */
#घोषणा booपंचांगem_startpg (PFN_UP(((अचिन्हित दीर्घ) _end) - PAGE_OFFSET + PHYS_OFFSET))

अचिन्हित दीर्घ booपंचांगem_lastpg;	/*  Should be set by platक्रमm code  */
अचिन्हित दीर्घ __phys_offset;	/*  physical kernel offset >> 12  */

/*  Set as variable to limit PMD copies  */
पूर्णांक max_kernel_seg = 0x303;

/*  indicate pfn's of high memory  */
अचिन्हित दीर्घ highstart_pfn, highend_pfn;

DEFINE_PER_CPU(काष्ठा mmu_gather, mmu_gathers);

/* Default cache attribute क्रम newly created page tables */
अचिन्हित दीर्घ _dflt_cache_att = CACHEDEF;

/*
 * The current "generation" of kernel map, which should not roll
 * over until Hell मुक्तzes over.  Actual bound in years needs to be
 * calculated to confirm.
 */
DEFINE_SPINLOCK(kmap_gen_lock);

/*  checkpatch says करोn't init this to 0.  */
अचिन्हित दीर्घ दीर्घ kmap_generation;

/*
 * mem_init - initializes memory
 *
 * Frees up booपंचांगem
 * Fixes up more stuff क्रम HIGHMEM
 * Calculates and displays memory available/used
 */
व्योम __init mem_init(व्योम)
अणु
	/*  No idea where this is actually declared.  Seems to evade LXR.  */
	memblock_मुक्त_all();

	/*
	 *  To-Do:  someone somewhere should wipe out the booपंचांगem map
	 *  after we're करोne?
	 */

	/*
	 * This can be moved to some more भव-memory-specअगरic
	 * initialization hook at some poपूर्णांक.  Set the init_mm
	 * descriptors "context" value to poपूर्णांक to the initial
	 * kernel segment table's physical address.
	 */
	init_mm.context.ptbase = __pa(init_mm.pgd);
पूर्ण

व्योम sync_icache_dcache(pte_t pte)
अणु
	अचिन्हित दीर्घ addr;
	काष्ठा page *page;

	page = pte_page(pte);
	addr = (अचिन्हित दीर्घ) page_address(page);

	__vmcache_idsync(addr, PAGE_SIZE);
पूर्ण

/*
 * In order to set up page allocator "nodes",
 * somebody has to call मुक्त_area_init() क्रम UMA.
 *
 * In this mode, we only have one pg_data_t
 * काष्ठाure: contig_mem_data.
 */
व्योम __init paging_init(व्योम)
अणु
	अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु0, पूर्ण;

	/*
	 *  This is not particularly well करोcumented anywhere, but
	 *  give ZONE_NORMAL all the memory, including the big holes
	 *  left by the kernel+booपंचांगem_map which are alपढ़ोy left as reserved
	 *  in the booपंचांगem_map; मुक्त_area_init should see those bits and
	 *  adjust accordingly.
	 */

	max_zone_pfn[ZONE_NORMAL] = max_low_pfn;

	मुक्त_area_init(max_zone_pfn);  /*  sets up the zonelists and mem_map  */

	/*
	 * Start of high memory area.  Will probably need something more
	 * fancy अगर we...  get more fancy.
	 */
	high_memory = (व्योम *)((booपंचांगem_lastpg + 1) << PAGE_SHIFT);
पूर्ण

#अगर_अघोषित DMA_RESERVE
#घोषणा DMA_RESERVE		(4)
#पूर्ण_अगर

#घोषणा DMA_CHUNKSIZE		(1<<22)
#घोषणा DMA_RESERVED_BYTES	(DMA_RESERVE * DMA_CHUNKSIZE)

/*
 * Pick out the memory size.  We look क्रम mem=size,
 * where size is "size[KkMm]"
 */
अटल पूर्णांक __init early_mem(अक्षर *p)
अणु
	अचिन्हित दीर्घ size;
	अक्षर *endp;

	size = memparse(p, &endp);

	booपंचांगem_lastpg = PFN_DOWN(size);

	वापस 0;
पूर्ण
early_param("mem", early_mem);

माप_प्रकार hexagon_coherent_pool_size = (माप_प्रकार) (DMA_RESERVE << 22);

व्योम __init setup_arch_memory(व्योम)
अणु
	/*  XXX Toकरो: this probably should be cleaned up  */
	u32 *segtable = (u32 *) &swapper_pg_dir[0];
	u32 *segtable_end;

	/*
	 * Set up boot memory allocator
	 *
	 * The Gorman book also talks about these functions.
	 * This needs to change क्रम highmem setups.
	 */

	/*  Prior to this, booपंचांगem_lastpg is actually mem size  */
	booपंचांगem_lastpg += ARCH_PFN_OFFSET;

	/* Memory size needs to be a multiple of 16M */
	booपंचांगem_lastpg = PFN_DOWN((booपंचांगem_lastpg << PAGE_SHIFT) &
		~((BIG_KERNEL_PAGE_SIZE) - 1));

	memblock_add(PHYS_OFFSET,
		     (booपंचांगem_lastpg - ARCH_PFN_OFFSET) << PAGE_SHIFT);

	/* Reserve kernel text/data/bss */
	memblock_reserve(PHYS_OFFSET,
			 (booपंचांगem_startpg - ARCH_PFN_OFFSET) << PAGE_SHIFT);
	/*
	 * Reserve the top DMA_RESERVE bytes of RAM क्रम DMA (uncached)
	 * memory allocation
	 */
	max_low_pfn = booपंचांगem_lastpg - PFN_DOWN(DMA_RESERVED_BYTES);
	min_low_pfn = ARCH_PFN_OFFSET;
	memblock_reserve(PFN_PHYS(max_low_pfn), DMA_RESERVED_BYTES);

	prपूर्णांकk(KERN_INFO "bootmem_startpg:  0x%08lx\n", booपंचांगem_startpg);
	prपूर्णांकk(KERN_INFO "bootmem_lastpg:  0x%08lx\n", booपंचांगem_lastpg);
	prपूर्णांकk(KERN_INFO "min_low_pfn:  0x%08lx\n", min_low_pfn);
	prपूर्णांकk(KERN_INFO "max_low_pfn:  0x%08lx\n", max_low_pfn);

	/*
	 * The शेष VM page tables (will be) populated with
	 * VA=PA+PAGE_OFFSET mapping.  We go in and invalidate entries
	 * higher than what we have memory क्रम.
	 */

	/*  this is poपूर्णांकer arithmetic; each entry covers 4MB  */
	segtable = segtable + (PAGE_OFFSET >> 22);

	/*  this actually only goes to the end of the first gig  */
	segtable_end = segtable + (1<<(30-22));

	/*
	 * Move क्रमward to the start of empty pages; take पूर्णांकo account
	 * phys_offset shअगरt.
	 */

	segtable += (booपंचांगem_lastpg-ARCH_PFN_OFFSET)>>(22-PAGE_SHIFT);
	अणु
		पूर्णांक i;

		क्रम (i = 1 ; i <= DMA_RESERVE ; i++)
			segtable[-i] = ((segtable[-i] & __HVM_PTE_PGMASK_4MB)
				| __HVM_PTE_R | __HVM_PTE_W | __HVM_PTE_X
				| __HEXAGON_C_UNC << 6
				| __HVM_PDE_S_4MB);
	पूर्ण

	prपूर्णांकk(KERN_INFO "clearing segtable from %p to %p\n", segtable,
		segtable_end);
	जबतक (segtable < (segtable_end-8))
		*(segtable++) = __HVM_PDE_S_INVALID;
	/* stop the poपूर्णांकer at the device I/O 4MB page  */

	prपूर्णांकk(KERN_INFO "segtable = %p (should be equal to _K_io_map)\n",
		segtable);

#अगर 0
	/*  Other half of the early device table from vm_init_segtable. */
	prपूर्णांकk(KERN_INFO "&_K_init_devicetable = 0x%08x\n",
		(अचिन्हित दीर्घ) _K_init_devicetable-PAGE_OFFSET);
	*segtable = ((u32) (अचिन्हित दीर्घ) _K_init_devicetable-PAGE_OFFSET) |
		__HVM_PDE_S_4KB;
	prपूर्णांकk(KERN_INFO "*segtable = 0x%08x\n", *segtable);
#पूर्ण_अगर

	/*
	 *  The booपंचांगem allocator seemingly just lives to feed memory
	 *  to the paging प्रणाली
	 */
	prपूर्णांकk(KERN_INFO "PAGE_SIZE=%lu\n", PAGE_SIZE);
	paging_init();  /*  See Gorman Book, 2.3  */

	/*
	 *  At this poपूर्णांक, the page allocator is kind of initialized, but
	 *  apparently no pages are available (just like with the booपंचांगem
	 *  allocator), and need to be मुक्तd themselves via mem_init(),
	 *  which is called by start_kernel() later on in the process
	 */
पूर्ण
