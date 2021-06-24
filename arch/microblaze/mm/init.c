<शैली गुरु>
/*
 * Copyright (C) 2007-2008 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/dma-map-ops.h>
#समावेश <linux/memblock.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h> /* mem_init */
#समावेश <linux/initrd.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pfn.h>
#समावेश <linux/slab.h>
#समावेश <linux/swap.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/fixmap.h>

/* Use क्रम MMU and noMMU because of PCI generic code */
पूर्णांक mem_init_करोne;

अक्षर *klimit = _end;

/*
 * Initialize the booपंचांगem प्रणाली and give it all the memory we
 * have available.
 */
अचिन्हित दीर्घ memory_start;
EXPORT_SYMBOL(memory_start);
अचिन्हित दीर्घ memory_size;
EXPORT_SYMBOL(memory_size);
अचिन्हित दीर्घ lowmem_size;

EXPORT_SYMBOL(min_low_pfn);
EXPORT_SYMBOL(max_low_pfn);

#अगर_घोषित CONFIG_HIGHMEM
अटल व्योम __init highmem_init(व्योम)
अणु
	pr_debug("%x\n", (u32)PKMAP_BASE);
	map_page(PKMAP_BASE, 0, 0);	/* XXX gross */
	pkmap_page_table = virt_to_kpte(PKMAP_BASE);
पूर्ण

अटल व्योम __meminit highmem_setup(व्योम)
अणु
	अचिन्हित दीर्घ pfn;

	क्रम (pfn = max_low_pfn; pfn < max_pfn; ++pfn) अणु
		काष्ठा page *page = pfn_to_page(pfn);

		/* FIXME not sure about */
		अगर (!memblock_is_reserved(pfn << PAGE_SHIFT))
			मुक्त_highmem_page(page);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_HIGHMEM */

/*
 * paging_init() sets up the page tables - in fact we've alपढ़ोy करोne this.
 */
अटल व्योम __init paging_init(व्योम)
अणु
	अचिन्हित दीर्घ zones_size[MAX_NR_ZONES];
	पूर्णांक idx;

	/* Setup fixmaps */
	क्रम (idx = 0; idx < __end_of_fixed_addresses; idx++)
		clear_fixmap(idx);

	/* Clean every zones */
	स_रखो(zones_size, 0, माप(zones_size));

#अगर_घोषित CONFIG_HIGHMEM
	highmem_init();

	zones_size[ZONE_DMA] = max_low_pfn;
	zones_size[ZONE_HIGHMEM] = max_pfn;
#अन्यथा
	zones_size[ZONE_DMA] = max_pfn;
#पूर्ण_अगर

	/* We करोn't have holes in memory map */
	मुक्त_area_init(zones_size);
पूर्ण

व्योम __init setup_memory(व्योम)
अणु
	/*
	 * Kernel:
	 * start: base phys address of kernel - page align
	 * end: base phys address of kernel - page align
	 *
	 * min_low_pfn - the first page (mm/booपंचांगem.c - node_boot_start)
	 * max_low_pfn
	 * max_mapnr - the first unused page (mm/booपंचांगem.c - node_low_pfn)
	 */

	/* memory start is from the kernel end (aligned) to higher addr */
	min_low_pfn = memory_start >> PAGE_SHIFT; /* minimum क्रम allocation */
	/* RAM is assumed contiguous */
	max_mapnr = memory_size >> PAGE_SHIFT;
	max_low_pfn = ((u64)memory_start + (u64)lowmem_size) >> PAGE_SHIFT;
	max_pfn = ((u64)memory_start + (u64)memory_size) >> PAGE_SHIFT;

	pr_info("%s: max_mapnr: %#lx\n", __func__, max_mapnr);
	pr_info("%s: min_low_pfn: %#lx\n", __func__, min_low_pfn);
	pr_info("%s: max_low_pfn: %#lx\n", __func__, max_low_pfn);
	pr_info("%s: max_pfn: %#lx\n", __func__, max_pfn);

	paging_init();
पूर्ण

व्योम __init mem_init(व्योम)
अणु
	high_memory = (व्योम *)__va(memory_start + lowmem_size - 1);

	/* this will put all memory onto the मुक्तlists */
	memblock_मुक्त_all();
#अगर_घोषित CONFIG_HIGHMEM
	highmem_setup();
#पूर्ण_अगर

	mem_init_करोne = 1;
पूर्ण

पूर्णांक page_is_ram(अचिन्हित दीर्घ pfn)
अणु
	वापस pfn < max_low_pfn;
पूर्ण

/*
 * Check क्रम command-line options that affect what MMU_init will करो.
 */
अटल व्योम mm_cmdline_setup(व्योम)
अणु
	अचिन्हित दीर्घ maxmem = 0;
	अक्षर *p = cmd_line;

	/* Look क्रम mem= option on command line */
	p = म_माला(cmd_line, "mem=");
	अगर (p) अणु
		p += 4;
		maxmem = memparse(p, &p);
		अगर (maxmem && memory_size > maxmem) अणु
			memory_size = maxmem;
			memblock.memory.regions[0].size = memory_size;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * MMU_init_hw करोes the chip-specअगरic initialization of the MMU hardware.
 */
अटल व्योम __init mmu_init_hw(व्योम)
अणु
	/*
	 * The Zone Protection Register (ZPR) defines how protection will
	 * be applied to every page which is a member of a given zone. At
	 * present, we utilize only two of the zones.
	 * The zone index bits (of ZSEL) in the PTE are used क्रम software
	 * indicators, except the LSB.  For user access, zone 1 is used,
	 * क्रम kernel access, zone 0 is used.  We set all but zone 1
	 * to zero, allowing only kernel access as indicated in the PTE.
	 * For zone 1, we set a 01 binary (a value of 10 will not work)
	 * to allow user access as indicated in the PTE.  This also allows
	 * kernel access as indicated in the PTE.
	 */
	__यंत्र__ __अस्थिर__ ("ori r11, r0, 0x10000000;" \
			"mts rzpr, r11;"
			: : : "r11");
पूर्ण

/*
 * MMU_init sets up the basic memory mappings क्रम the kernel,
 * including both RAM and possibly some I/O regions,
 * and sets up the page tables and the MMU hardware पढ़ोy to go.
 */

/* called from head.S */
यंत्रlinkage व्योम __init mmu_init(व्योम)
अणु
	अचिन्हित पूर्णांक kstart, ksize;

	अगर (!memblock.reserved.cnt) अणु
		pr_emerg("Error memory count\n");
		machine_restart(शून्य);
	पूर्ण

	अगर ((u32) memblock.memory.regions[0].size < 0x400000) अणु
		pr_emerg("Memory must be greater than 4MB\n");
		machine_restart(शून्य);
	पूर्ण

	अगर ((u32) memblock.memory.regions[0].size < kernel_tlb) अणु
		pr_emerg("Kernel size is greater than memory node\n");
		machine_restart(शून्य);
	पूर्ण

	/* Find मुख्य memory where the kernel is */
	memory_start = (u32) memblock.memory.regions[0].base;
	lowmem_size = memory_size = (u32) memblock.memory.regions[0].size;

	अगर (lowmem_size > CONFIG_LOWMEM_SIZE) अणु
		lowmem_size = CONFIG_LOWMEM_SIZE;
#अगर_अघोषित CONFIG_HIGHMEM
		memory_size = lowmem_size;
#पूर्ण_अगर
	पूर्ण

	mm_cmdline_setup(); /* FIXME parse args from command line - not used */

	/*
	 * Map out the kernel text/data/bss from the available physical
	 * memory.
	 */
	kstart = __pa(CONFIG_KERNEL_START); /* kernel start */
	/* kernel size */
	ksize = PAGE_ALIGN(((u32)_end - (u32)CONFIG_KERNEL_START));
	memblock_reserve(kstart, ksize);

#अगर defined(CONFIG_BLK_DEV_INITRD)
	/* Remove the init RAM disk from the available memory. */
	अगर (initrd_start) अणु
		अचिन्हित दीर्घ size;
		size = initrd_end - initrd_start;
		memblock_reserve(__virt_to_phys(initrd_start), size);
	पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_INITRD */

	/* Initialize the MMU hardware */
	mmu_init_hw();

	/* Map in all of RAM starting at CONFIG_KERNEL_START */
	mapin_ram();

	/* Extend vदो_स्मृति and ioremap area as big as possible */
#अगर_घोषित CONFIG_HIGHMEM
	ioremap_base = ioremap_bot = PKMAP_BASE;
#अन्यथा
	ioremap_base = ioremap_bot = FIXADDR_START;
#पूर्ण_अगर

	/* Initialize the context management stuff */
	mmu_context_init();

	/* Shortly after that, the entire linear mapping will be available */
	/* This will also cause that unflatten device tree will be allocated
	 * inside 768MB limit */
	memblock_set_current_limit(memory_start + lowmem_size - 1);

	parse_early_param();

	/* CMA initialization */
	dma_contiguous_reserve(memory_start + lowmem_size - 1);
पूर्ण

/* This is only called until mem_init is करोne. */
व्योम __init *early_get_page(व्योम)
अणु
	/*
	 * Mem start + kernel_tlb -> here is limit
	 * because of mem mapping from head.S
	 */
	वापस memblock_alloc_try_nid_raw(PAGE_SIZE, PAGE_SIZE,
				MEMBLOCK_LOW_LIMIT, memory_start + kernel_tlb,
				NUMA_NO_NODE);
पूर्ण

व्योम * __ref zalloc_maybe_booपंचांगem(माप_प्रकार size, gfp_t mask)
अणु
	व्योम *p;

	अगर (mem_init_करोne) अणु
		p = kzalloc(size, mask);
	पूर्ण अन्यथा अणु
		p = memblock_alloc(size, SMP_CACHE_BYTES);
		अगर (!p)
			panic("%s: Failed to allocate %zu bytes\n",
			      __func__, size);
	पूर्ण

	वापस p;
पूर्ण
