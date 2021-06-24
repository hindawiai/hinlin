<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#अगर_घोषित CONFIG_BLK_DEV_INITRD
#समावेश <linux/initrd.h>
#पूर्ण_अगर
#समावेश <linux/of_fdt.h>
#समावेश <linux/swap.h>
#समावेश <linux/module.h>
#समावेश <linux/highस्मृति.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/arcregs.h>

pgd_t swapper_pg_dir[PTRS_PER_PGD] __aligned(PAGE_SIZE);
अक्षर empty_zero_page[PAGE_SIZE] __aligned(PAGE_SIZE);
EXPORT_SYMBOL(empty_zero_page);

अटल स्थिर अचिन्हित दीर्घ low_mem_start = CONFIG_LINUX_RAM_BASE;
अटल अचिन्हित दीर्घ low_mem_sz;

#अगर_घोषित CONFIG_HIGHMEM
अटल अचिन्हित दीर्घ min_high_pfn, max_high_pfn;
अटल phys_addr_t high_mem_start;
अटल phys_addr_t high_mem_sz;
अचिन्हित दीर्घ arch_pfn_offset;
EXPORT_SYMBOL(arch_pfn_offset);
#पूर्ण_अगर

#अगर_घोषित CONFIG_DISCONTIGMEM
काष्ठा pglist_data node_data[MAX_NUMNODES] __पढ़ो_mostly;
EXPORT_SYMBOL(node_data);
#पूर्ण_अगर

दीर्घ __init arc_get_mem_sz(व्योम)
अणु
	वापस low_mem_sz;
पूर्ण

/* User can over-ride above with "mem=nnn[KkMm]" in cmdline */
अटल पूर्णांक __init setup_mem_sz(अक्षर *str)
अणु
	low_mem_sz = memparse(str, शून्य) & PAGE_MASK;

	/* early console might not be setup yet - it will show up later */
	pr_info("\"mem=%s\": mem sz set to %ldM\n", str, TO_MB(low_mem_sz));

	वापस 0;
पूर्ण
early_param("mem", setup_mem_sz);

व्योम __init early_init_dt_add_memory_arch(u64 base, u64 size)
अणु
	पूर्णांक in_use = 0;

	अगर (!low_mem_sz) अणु
		अगर (base != low_mem_start)
			panic("CONFIG_LINUX_RAM_BASE != DT memory { }");

		low_mem_sz = size;
		in_use = 1;
		memblock_add_node(base, size, 0);
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_HIGHMEM
		high_mem_start = base;
		high_mem_sz = size;
		in_use = 1;
		memblock_add_node(base, size, 1);
		memblock_reserve(base, size);
#पूर्ण_अगर
	पूर्ण

	pr_info("Memory @ %llx [%lldM] %s\n",
		base, TO_MB(size), !in_use ? "Not used":"");
पूर्ण

bool arch_has_descending_max_zone_pfns(व्योम)
अणु
	वापस !IS_ENABLED(CONFIG_ARC_HAS_PAE40);
पूर्ण

/*
 * First memory setup routine called from setup_arch()
 * 1. setup swapper's mm @init_mm
 * 2. Count the pages we have and setup booपंचांगem allocator
 * 3. zone setup
 */
व्योम __init setup_arch_memory(व्योम)
अणु
	अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु 0 पूर्ण;

	init_mm.start_code = (अचिन्हित दीर्घ)_text;
	init_mm.end_code = (अचिन्हित दीर्घ)_etext;
	init_mm.end_data = (अचिन्हित दीर्घ)_edata;
	init_mm.brk = (अचिन्हित दीर्घ)_end;

	/* first page of प्रणाली - kernel .vector starts here */
	min_low_pfn = virt_to_pfn(CONFIG_LINUX_RAM_BASE);

	/* Last usable page of low mem */
	max_low_pfn = max_pfn = PFN_DOWN(low_mem_start + low_mem_sz);

	/*------------- booपंचांगem allocator setup -----------------------*/

	/*
	 * seed the booपंचांगem allocator after any DT memory node parsing or
	 * "mem=xxx" cmdline overrides have potentially updated @arc_mem_sz
	 *
	 * Only low mem is added, otherwise we have crashes when allocating
	 * mem_map[] itself. NO_BOOTMEM allocates mem_map[] at the end of
	 * avail memory, ending in highmem with a > 32-bit address. However
	 * it then tries to स_रखो it with a truncaed 32-bit handle, causing
	 * the crash
	 */

	memblock_reserve(CONFIG_LINUX_LINK_BASE,
			 __pa(_end) - CONFIG_LINUX_LINK_BASE);

#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (phys_initrd_size) अणु
		memblock_reserve(phys_initrd_start, phys_initrd_size);
		initrd_start = (अचिन्हित दीर्घ)__va(phys_initrd_start);
		initrd_end = initrd_start + phys_initrd_size;
	पूर्ण
#पूर्ण_अगर

	early_init_fdt_reserve_self();
	early_init_fdt_scan_reserved_mem();

	memblock_dump_all();

	/*----------------- node/zones setup --------------------------*/
	max_zone_pfn[ZONE_NORMAL] = max_low_pfn;

#अगर_घोषित CONFIG_HIGHMEM
	/*
	 * Populate a new node with highmem
	 *
	 * On ARC (w/o PAE) HIGHMEM addresses are actually smaller (0 based)
	 * than addresses in normal ala low memory (0x8000_0000 based).
	 * Even with PAE, the huge peripheral space hole would waste a lot of
	 * mem with single mem_map[]. This warrants a mem_map per region design.
	 * Thus HIGHMEM on ARC is imlemented with DISCONTIGMEM.
	 *
	 * DISCONTIGMEM in turns requires multiple nodes. node 0 above is
	 * populated with normal memory zone जबतक node 1 only has highmem
	 */
#अगर_घोषित CONFIG_DISCONTIGMEM
	node_set_online(1);
#पूर्ण_अगर

	min_high_pfn = PFN_DOWN(high_mem_start);
	max_high_pfn = PFN_DOWN(high_mem_start + high_mem_sz);

	/*
	 * max_high_pfn should be ok here क्रम both HIGHMEM and HIGHMEM+PAE.
	 * For HIGHMEM without PAE max_high_pfn should be less than
	 * min_low_pfn to guarantee that these two regions करोn't overlap.
	 * For PAE हाल highmem is greater than lowmem, so it is natural
	 * to use max_high_pfn.
	 *
	 * In both हालs, holes should be handled by pfn_valid().
	 */
	max_zone_pfn[ZONE_HIGHMEM] = max_high_pfn;

	high_memory = (व्योम *)(min_high_pfn << PAGE_SHIFT);

	arch_pfn_offset = min(min_low_pfn, min_high_pfn);
	kmap_init();

#अन्यथा /* CONFIG_HIGHMEM */
	/* pfn_valid() uses this when FLATMEM=y and HIGHMEM=n */
	max_mapnr = max_low_pfn - min_low_pfn;

#पूर्ण_अगर /* CONFIG_HIGHMEM */

	मुक्त_area_init(max_zone_pfn);
पूर्ण

अटल व्योम __init highmem_init(व्योम)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	अचिन्हित दीर्घ पंचांगp;

	memblock_मुक्त(high_mem_start, high_mem_sz);
	क्रम (पंचांगp = min_high_pfn; पंचांगp < max_high_pfn; पंचांगp++)
		मुक्त_highmem_page(pfn_to_page(पंचांगp));
#पूर्ण_अगर
पूर्ण

/*
 * mem_init - initializes memory
 *
 * Frees up booपंचांगem
 * Calculates and displays memory available/used
 */
व्योम __init mem_init(व्योम)
अणु
	memblock_मुक्त_all();
	highmem_init();
पूर्ण

#अगर_घोषित CONFIG_HIGHMEM
पूर्णांक pfn_valid(अचिन्हित दीर्घ pfn)
अणु
	वापस (pfn >= min_high_pfn && pfn <= max_high_pfn) ||
		(pfn >= min_low_pfn && pfn <= max_low_pfn);
पूर्ण
EXPORT_SYMBOL(pfn_valid);
#पूर्ण_अगर
