<शैली गुरु>
/*
 * arch/xtensa/mm/init.c
 *
 * Derived from MIPS, PPC.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 * Copyright (C) 2014 - 2016 Cadence Design Systems Inc.
 *
 * Chris Zankel	<chris@zankel.net>
 * Joe Taylor	<joe@tensilica.com, joetylr@yahoo.com>
 * Marc Gauthier
 * Kevin Chea
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/memblock.h>
#समावेश <linux/gfp.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/swap.h>
#समावेश <linux/mman.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/mm.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/dma-map-ops.h>

#समावेश <यंत्र/bootparam.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/sysस्मृति.स>

/*
 * Initialize the booपंचांगem प्रणाली and give it all low memory we have available.
 */

व्योम __init booपंचांगem_init(व्योम)
अणु
	/* Reserve all memory below PHYS_OFFSET, as memory
	 * accounting करोesn't work क्रम pages below that address.
	 *
	 * If PHYS_OFFSET is zero reserve page at address 0:
	 * successfull allocations should never वापस शून्य.
	 */
	memblock_reserve(0, PHYS_OFFSET ? PHYS_OFFSET : 1);

	early_init_fdt_scan_reserved_mem();

	अगर (!memblock_phys_mem_size())
		panic("No memory found!\n");

	min_low_pfn = PFN_UP(memblock_start_of_DRAM());
	min_low_pfn = max(min_low_pfn, PFN_UP(PHYS_OFFSET));
	max_pfn = PFN_DOWN(memblock_end_of_DRAM());
	max_low_pfn = min(max_pfn, MAX_LOW_PFN);

	early_memtest((phys_addr_t)min_low_pfn << PAGE_SHIFT,
		      (phys_addr_t)max_low_pfn << PAGE_SHIFT);

	memblock_set_current_limit(PFN_PHYS(max_low_pfn));
	dma_contiguous_reserve(PFN_PHYS(max_low_pfn));

	memblock_dump_all();
पूर्ण


व्योम __init zones_init(व्योम)
अणु
	/* All pages are DMA-able, so we put them all in the DMA zone. */
	अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु
		[ZONE_NORMAL] = max_low_pfn,
#अगर_घोषित CONFIG_HIGHMEM
		[ZONE_HIGHMEM] = max_pfn,
#पूर्ण_अगर
	पूर्ण;
	मुक्त_area_init(max_zone_pfn);
पूर्ण

अटल व्योम __init मुक्त_highpages(व्योम)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	अचिन्हित दीर्घ max_low = max_low_pfn;
	phys_addr_t range_start, range_end;
	u64 i;

	/* set highmem page मुक्त */
	क्रम_each_मुक्त_mem_range(i, NUMA_NO_NODE, MEMBLOCK_NONE,
				&range_start, &range_end, शून्य) अणु
		अचिन्हित दीर्घ start = PFN_UP(range_start);
		अचिन्हित दीर्घ end = PFN_DOWN(range_end);

		/* Ignore complete lowmem entries */
		अगर (end <= max_low)
			जारी;

		/* Truncate partial highmem entries */
		अगर (start < max_low)
			start = max_low;

		क्रम (; start < end; start++)
			मुक्त_highmem_page(pfn_to_page(start));
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Initialize memory pages.
 */

व्योम __init mem_init(व्योम)
अणु
	मुक्त_highpages();

	max_mapnr = max_pfn - ARCH_PFN_OFFSET;
	high_memory = (व्योम *)__va(max_low_pfn << PAGE_SHIFT);

	memblock_मुक्त_all();

	pr_info("virtual kernel memory layout:\n"
#अगर_घोषित CONFIG_KASAN
		"    kasan   : 0x%08lx - 0x%08lx  (%5lu MB)\n"
#पूर्ण_अगर
#अगर_घोषित CONFIG_MMU
		"    vmalloc : 0x%08lx - 0x%08lx  (%5lu MB)\n"
#पूर्ण_अगर
#अगर_घोषित CONFIG_HIGHMEM
		"    pkmap   : 0x%08lx - 0x%08lx  (%5lu kB)\n"
		"    fixmap  : 0x%08lx - 0x%08lx  (%5lu kB)\n"
#पूर्ण_अगर
		"    lowmem  : 0x%08lx - 0x%08lx  (%5lu MB)\n"
		"    .text   : 0x%08lx - 0x%08lx  (%5lu kB)\n"
		"    .rodata : 0x%08lx - 0x%08lx  (%5lu kB)\n"
		"    .data   : 0x%08lx - 0x%08lx  (%5lu kB)\n"
		"    .init   : 0x%08lx - 0x%08lx  (%5lu kB)\n"
		"    .bss    : 0x%08lx - 0x%08lx  (%5lu kB)\n",
#अगर_घोषित CONFIG_KASAN
		KASAN_SHADOW_START, KASAN_SHADOW_START + KASAN_SHADOW_SIZE,
		KASAN_SHADOW_SIZE >> 20,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MMU
		VMALLOC_START, VMALLOC_END,
		(VMALLOC_END - VMALLOC_START) >> 20,
#अगर_घोषित CONFIG_HIGHMEM
		PKMAP_BASE, PKMAP_BASE + LAST_PKMAP * PAGE_SIZE,
		(LAST_PKMAP*PAGE_SIZE) >> 10,
		FIXADDR_START, FIXADDR_END,
		(FIXADDR_END - FIXADDR_START) >> 10,
#पूर्ण_अगर
		PAGE_OFFSET, PAGE_OFFSET +
		(max_low_pfn - min_low_pfn) * PAGE_SIZE,
#अन्यथा
		min_low_pfn * PAGE_SIZE, max_low_pfn * PAGE_SIZE,
#पूर्ण_अगर
		((max_low_pfn - min_low_pfn) * PAGE_SIZE) >> 20,
		(अचिन्हित दीर्घ)_text, (अचिन्हित दीर्घ)_etext,
		(अचिन्हित दीर्घ)(_etext - _text) >> 10,
		(अचिन्हित दीर्घ)__start_rodata, (अचिन्हित दीर्घ)__end_rodata,
		(अचिन्हित दीर्घ)(__end_rodata - __start_rodata) >> 10,
		(अचिन्हित दीर्घ)_sdata, (अचिन्हित दीर्घ)_edata,
		(अचिन्हित दीर्घ)(_edata - _sdata) >> 10,
		(अचिन्हित दीर्घ)__init_begin, (अचिन्हित दीर्घ)__init_end,
		(अचिन्हित दीर्घ)(__init_end - __init_begin) >> 10,
		(अचिन्हित दीर्घ)__bss_start, (अचिन्हित दीर्घ)__bss_stop,
		(अचिन्हित दीर्घ)(__bss_stop - __bss_start) >> 10);
पूर्ण

अटल व्योम __init parse_memmap_one(अक्षर *p)
अणु
	अक्षर *oldp;
	अचिन्हित दीर्घ start_at, mem_size;

	अगर (!p)
		वापस;

	oldp = p;
	mem_size = memparse(p, &p);
	अगर (p == oldp)
		वापस;

	चयन (*p) अणु
	हाल '@':
		start_at = memparse(p + 1, &p);
		memblock_add(start_at, mem_size);
		अवरोध;

	हाल '$':
		start_at = memparse(p + 1, &p);
		memblock_reserve(start_at, mem_size);
		अवरोध;

	हाल 0:
		memblock_reserve(mem_size, -mem_size);
		अवरोध;

	शेष:
		pr_warn("Unrecognized memmap syntax: %s\n", p);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक __init parse_memmap_opt(अक्षर *str)
अणु
	जबतक (str) अणु
		अक्षर *k = म_अक्षर(str, ',');

		अगर (k)
			*k++ = 0;

		parse_memmap_one(str);
		str = k;
	पूर्ण

	वापस 0;
पूर्ण
early_param("memmap", parse_memmap_opt);
