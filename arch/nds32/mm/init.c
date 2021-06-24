<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 1995-2005 Russell King
// Copyright (C) 2012 ARM Ltd.
// Copyright (C) 2013-2017 Andes Technology Corporation

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/swap.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mman.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/initrd.h>
#समावेश <linux/highस्मृति.स>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/page.h>

DEFINE_PER_CPU(काष्ठा mmu_gather, mmu_gathers);
DEFINE_SPINLOCK(anon_alias_lock);
बाह्य pgd_t swapper_pg_dir[PTRS_PER_PGD];

/*
 * empty_zero_page is a special page that is used क्रम
 * zero-initialized data and COW.
 */
काष्ठा page *empty_zero_page;
EXPORT_SYMBOL(empty_zero_page);

अटल व्योम __init zone_sizes_init(व्योम)
अणु
	अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु 0 पूर्ण;

	max_zone_pfn[ZONE_NORMAL] = max_low_pfn;
#अगर_घोषित CONFIG_HIGHMEM
	max_zone_pfn[ZONE_HIGHMEM] = max_pfn;
#पूर्ण_अगर
	मुक्त_area_init(max_zone_pfn);

पूर्ण

/*
 * Map all physical memory under high_memory पूर्णांकo kernel's address space.
 *
 * This is explicitly coded क्रम two-level page tables, so अगर you need
 * something अन्यथा then this needs to change.
 */
अटल व्योम __init map_ram(व्योम)
अणु
	अचिन्हित दीर्घ v, p, e;
	pgd_t *pge;
	p4d_t *p4e;
	pud_t *pue;
	pmd_t *pme;
	pte_t *pte;
	/* These mark extents of पढ़ो-only kernel pages...
	 * ...from vmlinux.lds.S
	 */

	p = (u32) memblock_start_of_DRAM() & PAGE_MASK;
	e = min((u32) memblock_end_of_DRAM(), (u32) __pa(high_memory));

	v = (u32) __va(p);
	pge = pgd_offset_k(v);

	जबतक (p < e) अणु
		पूर्णांक j;
		p4e = p4d_offset(pge, v);
		pue = pud_offset(p4e, v);
		pme = pmd_offset(pue, v);

		अगर ((u32) pue != (u32) pge || (u32) pme != (u32) pge) अणु
			panic("%s: Kernel hardcoded for "
			      "two-level page tables", __func__);
		पूर्ण

		/* Alloc one page क्रम holding PTE's... */
		pte = memblock_alloc(PAGE_SIZE, PAGE_SIZE);
		अगर (!pte)
			panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
			      __func__, PAGE_SIZE, PAGE_SIZE);
		set_pmd(pme, __pmd(__pa(pte) + _PAGE_KERNEL_TABLE));

		/* Fill the newly allocated page with PTE'S */
		क्रम (j = 0; p < e && j < PTRS_PER_PTE;
		     v += PAGE_SIZE, p += PAGE_SIZE, j++, pte++) अणु
			/* Create mapping between p and v. */
			/* TODO: more fine grant क्रम page access permission */
			set_pte(pte, __pte(p + pgprot_val(PAGE_KERNEL)));
		पूर्ण

		pge++;
	पूर्ण
पूर्ण
अटल pmd_t *fixmap_pmd_p;
अटल व्योम __init fixedrange_init(व्योम)
अणु
	अचिन्हित दीर्घ vaddr;
	pmd_t *pmd;
#अगर_घोषित CONFIG_HIGHMEM
	pte_t *pte;
#पूर्ण_अगर /* CONFIG_HIGHMEM */

	/*
	 * Fixed mappings:
	 */
	vaddr = __fix_to_virt(__end_of_fixed_addresses - 1);
	pmd = pmd_off_k(vaddr);
	fixmap_pmd_p = memblock_alloc(PAGE_SIZE, PAGE_SIZE);
	अगर (!fixmap_pmd_p)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);
	set_pmd(pmd, __pmd(__pa(fixmap_pmd_p) + _PAGE_KERNEL_TABLE));

#अगर_घोषित CONFIG_HIGHMEM
	/*
	 * Permanent kmaps:
	 */
	vaddr = PKMAP_BASE;

	pmd = pmd_off_k(vaddr);
	pte = memblock_alloc(PAGE_SIZE, PAGE_SIZE);
	अगर (!pte)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);
	set_pmd(pmd, __pmd(__pa(pte) + _PAGE_KERNEL_TABLE));
	pkmap_page_table = pte;
#पूर्ण_अगर /* CONFIG_HIGHMEM */
पूर्ण

/*
 * paging_init() sets up the page tables, initialises the zone memory
 * maps, and sets up the zero page, bad page and bad page tables.
 */
व्योम __init paging_init(व्योम)
अणु
	पूर्णांक i;
	व्योम *zero_page;

	pr_info("Setting up paging and PTEs.\n");
	/* clear out the init_mm.pgd that will contain the kernel's mappings */
	क्रम (i = 0; i < PTRS_PER_PGD; i++)
		swapper_pg_dir[i] = __pgd(1);

	map_ram();

	fixedrange_init();

	/* allocate space क्रम empty_zero_page */
	zero_page = memblock_alloc(PAGE_SIZE, PAGE_SIZE);
	अगर (!zero_page)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);
	zone_sizes_init();

	empty_zero_page = virt_to_page(zero_page);
	flush_dcache_page(empty_zero_page);
पूर्ण

अटल अंतरभूत व्योम __init मुक्त_highmem(व्योम)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	अचिन्हित दीर्घ pfn;
	क्रम (pfn = PFN_UP(__pa(high_memory)); pfn < max_pfn; pfn++) अणु
		phys_addr_t paddr = (phys_addr_t) pfn << PAGE_SHIFT;
		अगर (!memblock_is_reserved(paddr))
			मुक्त_highmem_page(pfn_to_page(pfn));
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __init set_max_mapnr_init(व्योम)
अणु
	max_mapnr = max_pfn;
पूर्ण

/*
 * mem_init() marks the मुक्त areas in the mem_map and tells us how much
 * memory is मुक्त.  This is करोne after various parts of the प्रणाली have
 * claimed their memory after the kernel image.
 */
व्योम __init mem_init(व्योम)
अणु
	phys_addr_t memory_start = memblock_start_of_DRAM();
	BUG_ON(!mem_map);
	set_max_mapnr_init();

	मुक्त_highmem();

	/* this will put all low memory onto the मुक्तlists */
	memblock_मुक्त_all();

	pr_info("virtual kernel memory layout:\n"
		"    fixmap  : 0x%08lx - 0x%08lx   (%4ld kB)\n"
#अगर_घोषित CONFIG_HIGHMEM
		"    pkmap   : 0x%08lx - 0x%08lx   (%4ld kB)\n"
#पूर्ण_अगर
		"    consist : 0x%08lx - 0x%08lx   (%4ld MB)\n"
		"    vmalloc : 0x%08lx - 0x%08lx   (%4ld MB)\n"
		"    lowmem  : 0x%08lx - 0x%08lx   (%4ld MB)\n"
		"      .init : 0x%08lx - 0x%08lx   (%4ld kB)\n"
		"      .data : 0x%08lx - 0x%08lx   (%4ld kB)\n"
		"      .text : 0x%08lx - 0x%08lx   (%4ld kB)\n",
		FIXADDR_START, FIXADDR_TOP, (FIXADDR_TOP - FIXADDR_START) >> 10,
#अगर_घोषित CONFIG_HIGHMEM
		PKMAP_BASE, PKMAP_BASE + LAST_PKMAP * PAGE_SIZE,
		(LAST_PKMAP * PAGE_SIZE) >> 10,
#पूर्ण_अगर
		CONSISTENT_BASE, CONSISTENT_END,
		((CONSISTENT_END) - (CONSISTENT_BASE)) >> 20, VMALLOC_START,
		(अचिन्हित दीर्घ)VMALLOC_END, (VMALLOC_END - VMALLOC_START) >> 20,
		(अचिन्हित दीर्घ)__va(memory_start), (अचिन्हित दीर्घ)high_memory,
		((अचिन्हित दीर्घ)high_memory -
		 (अचिन्हित दीर्घ)__va(memory_start)) >> 20,
		(अचिन्हित दीर्घ)&__init_begin, (अचिन्हित दीर्घ)&__init_end,
		((अचिन्हित दीर्घ)&__init_end -
		 (अचिन्हित दीर्घ)&__init_begin) >> 10, (अचिन्हित दीर्घ)&_etext,
		(अचिन्हित दीर्घ)&_edata,
		((अचिन्हित दीर्घ)&_edata - (अचिन्हित दीर्घ)&_etext) >> 10,
		(अचिन्हित दीर्घ)&_text, (अचिन्हित दीर्घ)&_etext,
		((अचिन्हित दीर्घ)&_etext - (अचिन्हित दीर्घ)&_text) >> 10);

	/*
	 * Check boundaries twice: Some fundamental inconsistencies can
	 * be detected at build समय alपढ़ोy.
	 */
#अगर_घोषित CONFIG_HIGHMEM
	BUILD_BUG_ON(PKMAP_BASE + LAST_PKMAP * PAGE_SIZE > FIXADDR_START);
	BUILD_BUG_ON((CONSISTENT_END) > PKMAP_BASE);
#पूर्ण_अगर
	BUILD_BUG_ON(VMALLOC_END > CONSISTENT_BASE);
	BUILD_BUG_ON(VMALLOC_START >= VMALLOC_END);

#अगर_घोषित CONFIG_HIGHMEM
	BUG_ON(PKMAP_BASE + LAST_PKMAP * PAGE_SIZE > FIXADDR_START);
	BUG_ON(CONSISTENT_END > PKMAP_BASE);
#पूर्ण_अगर
	BUG_ON(VMALLOC_END > CONSISTENT_BASE);
	BUG_ON(VMALLOC_START >= VMALLOC_END);
	BUG_ON((अचिन्हित दीर्घ)high_memory > VMALLOC_START);

	वापस;
पूर्ण

व्योम __set_fixmap(क्रमागत fixed_addresses idx,
			       phys_addr_t phys, pgprot_t flags)
अणु
	अचिन्हित दीर्घ addr = __fix_to_virt(idx);
	pte_t *pte;

	BUG_ON(idx <= FIX_HOLE || idx >= __end_of_fixed_addresses);

	pte = (pte_t *)&fixmap_pmd_p[pte_index(addr)];

	अगर (pgprot_val(flags)) अणु
		set_pte(pte, pfn_pte(phys >> PAGE_SHIFT, flags));
	पूर्ण अन्यथा अणु
		pte_clear(&init_mm, addr, pte);
		flush_tlb_kernel_range(addr, addr + PAGE_SIZE);
	पूर्ण
पूर्ण
