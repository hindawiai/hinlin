<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file contains kasan initialization code क्रम ARM.
 *
 * Copyright (c) 2018 Samsung Electronics Co., Ltd.
 * Author: Andrey Ryabinin <ryabinin.a.a@gmail.com>
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */

#घोषणा pr_fmt(fmt) "kasan: " fmt
#समावेश <linux/kasan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/start_kernel.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/highस्मृति.स>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/procinfo.h>
#समावेश <यंत्र/proc-fns.h>

#समावेश "mm.h"

अटल pgd_t पंचांगp_pgd_table[PTRS_PER_PGD] __initdata __aligned(PGD_SIZE);

pmd_t पंचांगp_pmd_table[PTRS_PER_PMD] __page_aligned_bss;

अटल __init व्योम *kasan_alloc_block(माप_प्रकार size)
अणु
	वापस memblock_alloc_try_nid(size, size, __pa(MAX_DMA_ADDRESS),
				      MEMBLOCK_ALLOC_KASAN, NUMA_NO_NODE);
पूर्ण

अटल व्योम __init kasan_pte_populate(pmd_t *pmdp, अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ end, bool early)
अणु
	अचिन्हित दीर्घ next;
	pte_t *ptep = pte_offset_kernel(pmdp, addr);

	करो अणु
		pte_t entry;
		व्योम *p;

		next = addr + PAGE_SIZE;

		अगर (!early) अणु
			अगर (!pte_none(READ_ONCE(*ptep)))
				जारी;

			p = kasan_alloc_block(PAGE_SIZE);
			अगर (!p) अणु
				panic("%s failed to allocate shadow page for address 0x%lx\n",
				      __func__, addr);
				वापस;
			पूर्ण
			स_रखो(p, KASAN_SHADOW_INIT, PAGE_SIZE);
			entry = pfn_pte(virt_to_pfn(p),
					__pgprot(pgprot_val(PAGE_KERNEL)));
		पूर्ण अन्यथा अगर (pte_none(READ_ONCE(*ptep))) अणु
			/*
			 * The early shaकरोw memory is mapping all KASan
			 * operations to one and the same page in memory,
			 * "kasan_early_shadow_page" so that the instrumentation
			 * will work on a scratch area until we can set up the
			 * proper KASan shaकरोw memory.
			 */
			entry = pfn_pte(virt_to_pfn(kasan_early_shaकरोw_page),
					__pgprot(_L_PTE_DEFAULT | L_PTE_सूचीTY | L_PTE_XN));
		पूर्ण अन्यथा अणु
			/*
			 * Early shaकरोw mappings are PMD_SIZE aligned, so अगर the
			 * first entry is alपढ़ोy set, they must all be set.
			 */
			वापस;
		पूर्ण

		set_pte_at(&init_mm, addr, ptep, entry);
	पूर्ण जबतक (ptep++, addr = next, addr != end);
पूर्ण

/*
 * The pmd (page middle directory) is only used on LPAE
 */
अटल व्योम __init kasan_pmd_populate(pud_t *pudp, अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ end, bool early)
अणु
	अचिन्हित दीर्घ next;
	pmd_t *pmdp = pmd_offset(pudp, addr);

	करो अणु
		अगर (pmd_none(*pmdp)) अणु
			/*
			 * We attempt to allocate a shaकरोw block क्रम the PMDs
			 * used by the PTEs क्रम this address अगर it isn't alपढ़ोy
			 * allocated.
			 */
			व्योम *p = early ? kasan_early_shaकरोw_pte :
				kasan_alloc_block(PAGE_SIZE);

			अगर (!p) अणु
				panic("%s failed to allocate shadow block for address 0x%lx\n",
				      __func__, addr);
				वापस;
			पूर्ण
			pmd_populate_kernel(&init_mm, pmdp, p);
			flush_pmd_entry(pmdp);
		पूर्ण

		next = pmd_addr_end(addr, end);
		kasan_pte_populate(pmdp, addr, next, early);
	पूर्ण जबतक (pmdp++, addr = next, addr != end);
पूर्ण

अटल व्योम __init kasan_pgd_populate(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				      bool early)
अणु
	अचिन्हित दीर्घ next;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;

	pgdp = pgd_offset_k(addr);

	करो अणु
		/*
		 * Allocate and populate the shaकरोw block of p4d folded पूर्णांकo
		 * pud folded पूर्णांकo pmd अगर it करोesn't alपढ़ोy exist
		 */
		अगर (!early && pgd_none(*pgdp)) अणु
			व्योम *p = kasan_alloc_block(PAGE_SIZE);

			अगर (!p) अणु
				panic("%s failed to allocate shadow block for address 0x%lx\n",
				      __func__, addr);
				वापस;
			पूर्ण
			pgd_populate(&init_mm, pgdp, p);
		पूर्ण

		next = pgd_addr_end(addr, end);
		/*
		 * We just immediately jump over the p4d and pud page
		 * directories since we believe ARM32 will never gain four
		 * nor five level page tables.
		 */
		p4dp = p4d_offset(pgdp, addr);
		pudp = pud_offset(p4dp, addr);

		kasan_pmd_populate(pudp, addr, next, early);
	पूर्ण जबतक (pgdp++, addr = next, addr != end);
पूर्ण

बाह्य काष्ठा proc_info_list *lookup_processor_type(अचिन्हित पूर्णांक);

व्योम __init kasan_early_init(व्योम)
अणु
	काष्ठा proc_info_list *list;

	/*
	 * locate processor in the list of supported processor
	 * types.  The linker builds this table क्रम us from the
	 * entries in arch/arm/mm/proc-*.S
	 */
	list = lookup_processor_type(पढ़ो_cpuid_id());
	अगर (list) अणु
#अगर_घोषित MULTI_CPU
		processor = *list->proc;
#पूर्ण_अगर
	पूर्ण

	BUILD_BUG_ON((KASAN_SHADOW_END - (1UL << 29)) != KASAN_SHADOW_OFFSET);
	/*
	 * We walk the page table and set all of the shaकरोw memory to poपूर्णांक
	 * to the scratch page.
	 */
	kasan_pgd_populate(KASAN_SHADOW_START, KASAN_SHADOW_END, true);
पूर्ण

अटल व्योम __init clear_pgds(अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ end)
अणु
	क्रम (; start && start < end; start += PMD_SIZE)
		pmd_clear(pmd_off_k(start));
पूर्ण

अटल पूर्णांक __init create_mapping(व्योम *start, व्योम *end)
अणु
	व्योम *shaकरोw_start, *shaकरोw_end;

	shaकरोw_start = kasan_mem_to_shaकरोw(start);
	shaकरोw_end = kasan_mem_to_shaकरोw(end);

	pr_info("Mapping kernel virtual memory block: %px-%px at shadow: %px-%px\n",
		start, end, shaकरोw_start, shaकरोw_end);

	kasan_pgd_populate((अचिन्हित दीर्घ)shaकरोw_start & PAGE_MASK,
			   PAGE_ALIGN((अचिन्हित दीर्घ)shaकरोw_end), false);
	वापस 0;
पूर्ण

व्योम __init kasan_init(व्योम)
अणु
	phys_addr_t pa_start, pa_end;
	u64 i;

	/*
	 * We are going to perक्रमm proper setup of shaकरोw memory.
	 *
	 * At first we should unmap early shaकरोw (clear_pgds() call bellow).
	 * However, instrumented code can't execute without shaकरोw memory.
	 *
	 * To keep the early shaकरोw memory MMU tables around जबतक setting up
	 * the proper shaकरोw memory, we copy swapper_pg_dir (the initial page
	 * table) to पंचांगp_pgd_table and use that to keep the early shaकरोw memory
	 * mapped until the full shaकरोw setup is finished. Then we swap back
	 * to the proper swapper_pg_dir.
	 */

	स_नकल(पंचांगp_pgd_table, swapper_pg_dir, माप(पंचांगp_pgd_table));
#अगर_घोषित CONFIG_ARM_LPAE
	/* We need to be in the same PGD or this won't work */
	BUILD_BUG_ON(pgd_index(KASAN_SHADOW_START) !=
		     pgd_index(KASAN_SHADOW_END));
	स_नकल(पंचांगp_pmd_table,
	       pgd_page_vaddr(*pgd_offset_k(KASAN_SHADOW_START)),
	       माप(पंचांगp_pmd_table));
	set_pgd(&पंचांगp_pgd_table[pgd_index(KASAN_SHADOW_START)],
		__pgd(__pa(पंचांगp_pmd_table) | PMD_TYPE_TABLE | L_PGD_SWAPPER));
#पूर्ण_अगर
	cpu_चयन_mm(पंचांगp_pgd_table, &init_mm);
	local_flush_tlb_all();

	clear_pgds(KASAN_SHADOW_START, KASAN_SHADOW_END);

	kasan_populate_early_shaकरोw(kasan_mem_to_shaकरोw((व्योम *)VMALLOC_START),
				    kasan_mem_to_shaकरोw((व्योम *)-1UL) + 1);

	क्रम_each_mem_range(i, &pa_start, &pa_end) अणु
		व्योम *start = __va(pa_start);
		व्योम *end = __va(pa_end);

		/* Do not attempt to shaकरोw highmem */
		अगर (pa_start >= arm_lowmem_limit) अणु
			pr_info("Skip highmem block at %pa-%pa\n", &pa_start, &pa_end);
			जारी;
		पूर्ण
		अगर (pa_end > arm_lowmem_limit) अणु
			pr_info("Truncating shadow for memory block at %pa-%pa to lowmem region at %pa\n",
				&pa_start, &pa_end, &arm_lowmem_limit);
			end = __va(arm_lowmem_limit);
		पूर्ण
		अगर (start >= end) अणु
			pr_info("Skipping invalid memory block %pa-%pa (virtual %p-%p)\n",
				&pa_start, &pa_end, start, end);
			जारी;
		पूर्ण

		create_mapping(start, end);
	पूर्ण

	/*
	 * 1. The module global variables are in MODULES_VADDR ~ MODULES_END,
	 *    so we need to map this area.
	 * 2. PKMAP_BASE ~ PKMAP_BASE+PMD_SIZE's shaकरोw and MODULES_VADDR
	 *    ~ MODULES_END's shadow is in the same PMD_SIZE, so we can't
	 *    use kasan_populate_zero_shaकरोw.
	 */
	create_mapping((व्योम *)MODULES_VADDR, (व्योम *)(PKMAP_BASE + PMD_SIZE));

	/*
	 * KAsan may reuse the contents of kasan_early_shaकरोw_pte directly, so
	 * we should make sure that it maps the zero page पढ़ो-only.
	 */
	क्रम (i = 0; i < PTRS_PER_PTE; i++)
		set_pte_at(&init_mm, KASAN_SHADOW_START + i*PAGE_SIZE,
			   &kasan_early_shaकरोw_pte[i],
			   pfn_pte(virt_to_pfn(kasan_early_shaकरोw_page),
				__pgprot(pgprot_val(PAGE_KERNEL)
					 | L_PTE_RDONLY)));

	cpu_चयन_mm(swapper_pg_dir, &init_mm);
	local_flush_tlb_all();

	स_रखो(kasan_early_shaकरोw_page, 0, PAGE_SIZE);
	pr_info("Kernel address sanitizer initialized\n");
	init_task.kasan_depth = 0;
पूर्ण
