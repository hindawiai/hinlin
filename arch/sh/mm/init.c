<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/sh/mm/init.c
 *
 *  Copyright (C) 1999  Niibe Yutaka
 *  Copyright (C) 2002 - 2011  Paul Mundt
 *
 *  Based on linux/arch/i386/mm/init.c:
 *   Copyright (C) 1995  Linus Torvalds
 */
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/init.h>
#समावेश <linux/gfp.h>
#समावेश <linux/memblock.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/percpu.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mmzone.h>
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <linux/sizes.h>
#समावेश "ioremap.h"

pgd_t swapper_pg_dir[PTRS_PER_PGD];

व्योम __init generic_mem_init(व्योम)
अणु
	memblock_add(__MEMORY_START, __MEMORY_SIZE);
पूर्ण

व्योम __init __weak plat_mem_setup(व्योम)
अणु
	/* Nothing to see here, move aदीर्घ. */
पूर्ण

#अगर_घोषित CONFIG_MMU
अटल pte_t *__get_pte_phys(अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd = pgd_offset_k(addr);
	अगर (pgd_none(*pgd)) अणु
		pgd_ERROR(*pgd);
		वापस शून्य;
	पूर्ण

	p4d = p4d_alloc(शून्य, pgd, addr);
	अगर (unlikely(!p4d)) अणु
		p4d_ERROR(*p4d);
		वापस शून्य;
	पूर्ण

	pud = pud_alloc(शून्य, p4d, addr);
	अगर (unlikely(!pud)) अणु
		pud_ERROR(*pud);
		वापस शून्य;
	पूर्ण

	pmd = pmd_alloc(शून्य, pud, addr);
	अगर (unlikely(!pmd)) अणु
		pmd_ERROR(*pmd);
		वापस शून्य;
	पूर्ण

	वापस pte_offset_kernel(pmd, addr);
पूर्ण

अटल व्योम set_pte_phys(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ phys, pgprot_t prot)
अणु
	pte_t *pte;

	pte = __get_pte_phys(addr);
	अगर (!pte_none(*pte)) अणु
		pte_ERROR(*pte);
		वापस;
	पूर्ण

	set_pte(pte, pfn_pte(phys >> PAGE_SHIFT, prot));
	local_flush_tlb_one(get_asid(), addr);

	अगर (pgprot_val(prot) & _PAGE_WIRED)
		tlb_wire_entry(शून्य, addr, *pte);
पूर्ण

अटल व्योम clear_pte_phys(अचिन्हित दीर्घ addr, pgprot_t prot)
अणु
	pte_t *pte;

	pte = __get_pte_phys(addr);

	अगर (pgprot_val(prot) & _PAGE_WIRED)
		tlb_unwire_entry();

	set_pte(pte, pfn_pte(0, __pgprot(0)));
	local_flush_tlb_one(get_asid(), addr);
पूर्ण

व्योम __set_fixmap(क्रमागत fixed_addresses idx, अचिन्हित दीर्घ phys, pgprot_t prot)
अणु
	अचिन्हित दीर्घ address = __fix_to_virt(idx);

	अगर (idx >= __end_of_fixed_addresses) अणु
		BUG();
		वापस;
	पूर्ण

	set_pte_phys(address, phys, prot);
पूर्ण

व्योम __clear_fixmap(क्रमागत fixed_addresses idx, pgprot_t prot)
अणु
	अचिन्हित दीर्घ address = __fix_to_virt(idx);

	अगर (idx >= __end_of_fixed_addresses) अणु
		BUG();
		वापस;
	पूर्ण

	clear_pte_phys(address, prot);
पूर्ण

अटल pmd_t * __init one_md_table_init(pud_t *pud)
अणु
	अगर (pud_none(*pud)) अणु
		pmd_t *pmd;

		pmd = memblock_alloc(PAGE_SIZE, PAGE_SIZE);
		अगर (!pmd)
			panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
			      __func__, PAGE_SIZE, PAGE_SIZE);
		pud_populate(&init_mm, pud, pmd);
		BUG_ON(pmd != pmd_offset(pud, 0));
	पूर्ण

	वापस pmd_offset(pud, 0);
पूर्ण

अटल pte_t * __init one_page_table_init(pmd_t *pmd)
अणु
	अगर (pmd_none(*pmd)) अणु
		pte_t *pte;

		pte = memblock_alloc(PAGE_SIZE, PAGE_SIZE);
		अगर (!pte)
			panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
			      __func__, PAGE_SIZE, PAGE_SIZE);
		pmd_populate_kernel(&init_mm, pmd, pte);
		BUG_ON(pte != pte_offset_kernel(pmd, 0));
	पूर्ण

	वापस pte_offset_kernel(pmd, 0);
पूर्ण

अटल pte_t * __init page_table_kmap_check(pte_t *pte, pmd_t *pmd,
					    अचिन्हित दीर्घ vaddr, pte_t *lastpte)
अणु
	वापस pte;
पूर्ण

व्योम __init page_table_range_init(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
					 pgd_t *pgd_base)
अणु
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte = शून्य;
	पूर्णांक i, j, k;
	अचिन्हित दीर्घ vaddr;

	vaddr = start;
	i = pgd_index(vaddr);
	j = pud_index(vaddr);
	k = pmd_index(vaddr);
	pgd = pgd_base + i;

	क्रम ( ; (i < PTRS_PER_PGD) && (vaddr != end); pgd++, i++) अणु
		pud = (pud_t *)pgd;
		क्रम ( ; (j < PTRS_PER_PUD) && (vaddr != end); pud++, j++) अणु
			pmd = one_md_table_init(pud);
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
			pmd += k;
#पूर्ण_अगर
			क्रम (; (k < PTRS_PER_PMD) && (vaddr != end); pmd++, k++) अणु
				pte = page_table_kmap_check(one_page_table_init(pmd),
							    pmd, vaddr, pte);
				vaddr += PMD_SIZE;
			पूर्ण
			k = 0;
		पूर्ण
		j = 0;
	पूर्ण
पूर्ण
#पूर्ण_अगर	/* CONFIG_MMU */

व्योम __init allocate_pgdat(अचिन्हित पूर्णांक nid)
अणु
	अचिन्हित दीर्घ start_pfn, end_pfn;

	get_pfn_range_क्रम_nid(nid, &start_pfn, &end_pfn);

#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
	NODE_DATA(nid) = memblock_alloc_try_nid(
				माप(काष्ठा pglist_data),
				SMP_CACHE_BYTES, MEMBLOCK_LOW_LIMIT,
				MEMBLOCK_ALLOC_ACCESSIBLE, nid);
	अगर (!NODE_DATA(nid))
		panic("Can't allocate pgdat for node %d\n", nid);
#पूर्ण_अगर

	NODE_DATA(nid)->node_start_pfn = start_pfn;
	NODE_DATA(nid)->node_spanned_pages = end_pfn - start_pfn;
पूर्ण

अटल व्योम __init करो_init_booपंचांगem(व्योम)
अणु
	अचिन्हित दीर्घ start_pfn, end_pfn;
	पूर्णांक i;

	/* Add active regions with valid PFNs. */
	क्रम_each_mem_pfn_range(i, MAX_NUMNODES, &start_pfn, &end_pfn, शून्य)
		__add_active_range(0, start_pfn, end_pfn);

	/* All of प्रणाली RAM sits in node 0 क्रम the non-NUMA हाल */
	allocate_pgdat(0);
	node_set_online(0);

	plat_mem_setup();

	sparse_init();
पूर्ण

अटल व्योम __init early_reserve_mem(व्योम)
अणु
	अचिन्हित दीर्घ start_pfn;
	u32 zero_base = (u32)__MEMORY_START + (u32)PHYSICAL_OFFSET;
	u32 start = zero_base + (u32)CONFIG_ZERO_PAGE_OFFSET;

	/*
	 * Partially used pages are not usable - thus
	 * we are rounding upwards:
	 */
	start_pfn = PFN_UP(__pa(_end));

	/*
	 * Reserve the kernel text and Reserve the booपंचांगem biपंचांगap. We करो
	 * this in two steps (first step was init_booपंचांगem()), because
	 * this catches the (definitely buggy) हाल of us accidentally
	 * initializing the booपंचांगem allocator with an invalid RAM area.
	 */
	memblock_reserve(start, (PFN_PHYS(start_pfn) + PAGE_SIZE - 1) - start);

	/*
	 * Reserve physical pages below CONFIG_ZERO_PAGE_OFFSET.
	 */
	अगर (CONFIG_ZERO_PAGE_OFFSET != 0)
		memblock_reserve(zero_base, CONFIG_ZERO_PAGE_OFFSET);

	/*
	 * Handle additional early reservations
	 */
	check_क्रम_initrd();
	reserve_crashkernel();
पूर्ण

व्योम __init paging_init(व्योम)
अणु
	अचिन्हित दीर्घ max_zone_pfns[MAX_NR_ZONES];
	अचिन्हित दीर्घ vaddr, end;

	sh_mv.mv_mem_init();

	early_reserve_mem();

	/*
	 * Once the early reservations are out of the way, give the
	 * platक्रमms a chance to kick out some memory.
	 */
	अगर (sh_mv.mv_mem_reserve)
		sh_mv.mv_mem_reserve();

	memblock_enक्रमce_memory_limit(memory_limit);
	memblock_allow_resize();

	memblock_dump_all();

	/*
	 * Determine low and high memory ranges:
	 */
	max_low_pfn = max_pfn = memblock_end_of_DRAM() >> PAGE_SHIFT;
	min_low_pfn = __MEMORY_START >> PAGE_SHIFT;

	nodes_clear(node_online_map);

	memory_start = (अचिन्हित दीर्घ)__va(__MEMORY_START);
	memory_end = memory_start + (memory_limit ?: memblock_phys_mem_size());

	uncached_init();
	pmb_init();
	करो_init_booपंचांगem();
	ioremap_fixed_init();

	/* We करोn't need to map the kernel through the TLB, as
	 * it is permanatly mapped using P1. So clear the
	 * entire pgd. */
	स_रखो(swapper_pg_dir, 0, माप(swapper_pg_dir));

	/* Set an initial value क्रम the MMU.TTB so we करोn't have to
	 * check क्रम a null value. */
	set_TTB(swapper_pg_dir);

	/*
	 * Populate the relevant portions of swapper_pg_dir so that
	 * we can use the fixmap entries without calling kदो_स्मृति.
	 * pte's will be filled in by __set_fixmap().
	 */
	vaddr = __fix_to_virt(__end_of_fixed_addresses - 1) & PMD_MASK;
	end = (FIXADDR_TOP + PMD_SIZE - 1) & PMD_MASK;
	page_table_range_init(vaddr, end, swapper_pg_dir);

	kmap_coherent_init();

	स_रखो(max_zone_pfns, 0, माप(max_zone_pfns));
	max_zone_pfns[ZONE_NORMAL] = max_low_pfn;
	मुक्त_area_init(max_zone_pfns);
पूर्ण

अचिन्हित पूर्णांक mem_init_करोne = 0;

व्योम __init mem_init(व्योम)
अणु
	pg_data_t *pgdat;

	high_memory = शून्य;
	क्रम_each_online_pgdat(pgdat)
		high_memory = max_t(व्योम *, high_memory,
				    __va(pgdat_end_pfn(pgdat) << PAGE_SHIFT));

	memblock_मुक्त_all();

	/* Set this up early, so we can take care of the zero page */
	cpu_cache_init();

	/* clear the zero-page */
	स_रखो(empty_zero_page, 0, PAGE_SIZE);
	__flush_wback_region(empty_zero_page, PAGE_SIZE);

	vsyscall_init();

	pr_info("virtual kernel memory layout:\n"
		"    fixmap  : 0x%08lx - 0x%08lx   (%4ld kB)\n"
		"    vmalloc : 0x%08lx - 0x%08lx   (%4ld MB)\n"
		"    lowmem  : 0x%08lx - 0x%08lx   (%4ld MB) (cached)\n"
#अगर_घोषित CONFIG_UNCACHED_MAPPING
		"            : 0x%08lx - 0x%08lx   (%4ld MB) (uncached)\n"
#पूर्ण_अगर
		"      .init : 0x%08lx - 0x%08lx   (%4ld kB)\n"
		"      .data : 0x%08lx - 0x%08lx   (%4ld kB)\n"
		"      .text : 0x%08lx - 0x%08lx   (%4ld kB)\n",
		FIXADDR_START, FIXADDR_TOP,
		(FIXADDR_TOP - FIXADDR_START) >> 10,

		(अचिन्हित दीर्घ)VMALLOC_START, VMALLOC_END,
		(VMALLOC_END - VMALLOC_START) >> 20,

		(अचिन्हित दीर्घ)memory_start, (अचिन्हित दीर्घ)high_memory,
		((अचिन्हित दीर्घ)high_memory - (अचिन्हित दीर्घ)memory_start) >> 20,

#अगर_घोषित CONFIG_UNCACHED_MAPPING
		uncached_start, uncached_end, uncached_size >> 20,
#पूर्ण_अगर

		(अचिन्हित दीर्घ)&__init_begin, (अचिन्हित दीर्घ)&__init_end,
		((अचिन्हित दीर्घ)&__init_end -
		 (अचिन्हित दीर्घ)&__init_begin) >> 10,

		(अचिन्हित दीर्घ)&_etext, (अचिन्हित दीर्घ)&_edata,
		((अचिन्हित दीर्घ)&_edata - (अचिन्हित दीर्घ)&_etext) >> 10,

		(अचिन्हित दीर्घ)&_text, (अचिन्हित दीर्घ)&_etext,
		((अचिन्हित दीर्घ)&_etext - (अचिन्हित दीर्घ)&_text) >> 10);

	mem_init_करोne = 1;
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
पूर्णांक arch_add_memory(पूर्णांक nid, u64 start, u64 size,
		    काष्ठा mhp_params *params)
अणु
	अचिन्हित दीर्घ start_pfn = PFN_DOWN(start);
	अचिन्हित दीर्घ nr_pages = size >> PAGE_SHIFT;
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(params->pgprot.pgprot != PAGE_KERNEL.pgprot))
		वापस -EINVAL;

	/* We only have ZONE_NORMAL, so this is easy.. */
	ret = __add_pages(nid, start_pfn, nr_pages, params);
	अगर (unlikely(ret))
		prपूर्णांकk("%s: Failed, __add_pages() == %d\n", __func__, ret);

	वापस ret;
पूर्ण

व्योम arch_हटाओ_memory(पूर्णांक nid, u64 start, u64 size,
			काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ start_pfn = PFN_DOWN(start);
	अचिन्हित दीर्घ nr_pages = size >> PAGE_SHIFT;

	__हटाओ_pages(start_pfn, nr_pages, alपंचांगap);
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG */
