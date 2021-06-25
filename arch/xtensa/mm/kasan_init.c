<शैली गुरु>
/*
 * Xtensa KASAN shaकरोw map initialization
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2017 Cadence Design Systems Inc.
 */

#समावेश <linux/memblock.h>
#समावेश <linux/init_task.h>
#समावेश <linux/kasan.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/initialize_mmu.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/traps.h>

व्योम __init kasan_early_init(व्योम)
अणु
	अचिन्हित दीर्घ vaddr = KASAN_SHADOW_START;
	pmd_t *pmd = pmd_off_k(vaddr);
	पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PTE; ++i)
		set_pte(kasan_early_shaकरोw_pte + i,
			mk_pte(virt_to_page(kasan_early_shaकरोw_page),
				PAGE_KERNEL));

	क्रम (vaddr = 0; vaddr < KASAN_SHADOW_SIZE; vaddr += PMD_SIZE, ++pmd) अणु
		BUG_ON(!pmd_none(*pmd));
		set_pmd(pmd, __pmd((अचिन्हित दीर्घ)kasan_early_shaकरोw_pte));
	पूर्ण
	early_trap_init();
पूर्ण

अटल व्योम __init populate(व्योम *start, व्योम *end)
अणु
	अचिन्हित दीर्घ n_pages = (end - start) / PAGE_SIZE;
	अचिन्हित दीर्घ n_pmds = n_pages / PTRS_PER_PTE;
	अचिन्हित दीर्घ i, j;
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ)start;
	pmd_t *pmd = pmd_off_k(vaddr);
	pte_t *pte = memblock_alloc(n_pages * माप(pte_t), PAGE_SIZE);

	अगर (!pte)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, n_pages * माप(pte_t), PAGE_SIZE);

	pr_debug("%s: %p - %p\n", __func__, start, end);

	क्रम (i = j = 0; i < n_pmds; ++i) अणु
		पूर्णांक k;

		क्रम (k = 0; k < PTRS_PER_PTE; ++k, ++j) अणु
			phys_addr_t phys =
				memblock_phys_alloc_range(PAGE_SIZE, PAGE_SIZE,
							  0,
							  MEMBLOCK_ALLOC_ANYWHERE);

			अगर (!phys)
				panic("Failed to allocate page table page\n");

			set_pte(pte + j, pfn_pte(PHYS_PFN(phys), PAGE_KERNEL));
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < n_pmds ; ++i, pte += PTRS_PER_PTE)
		set_pmd(pmd + i, __pmd((अचिन्हित दीर्घ)pte));

	local_flush_tlb_all();
	स_रखो(start, 0, end - start);
पूर्ण

व्योम __init kasan_init(व्योम)
अणु
	पूर्णांक i;

	BUILD_BUG_ON(KASAN_SHADOW_OFFSET != KASAN_SHADOW_START -
		     (KASAN_START_VADDR >> KASAN_SHADOW_SCALE_SHIFT));
	BUILD_BUG_ON(VMALLOC_START < KASAN_START_VADDR);

	/*
	 * Replace shaकरोw map pages that cover addresses from VMALLOC area
	 * start to the end of KSEG with clean writable pages.
	 */
	populate(kasan_mem_to_shaकरोw((व्योम *)VMALLOC_START),
		 kasan_mem_to_shaकरोw((व्योम *)XCHAL_KSEG_BYPASS_VADDR));

	/*
	 * Write protect kasan_early_shaकरोw_page and zero-initialize it again.
	 */
	क्रम (i = 0; i < PTRS_PER_PTE; ++i)
		set_pte(kasan_early_shaकरोw_pte + i,
			mk_pte(virt_to_page(kasan_early_shaकरोw_page),
				PAGE_KERNEL_RO));

	local_flush_tlb_all();
	स_रखो(kasan_early_shaकरोw_page, 0, PAGE_SIZE);

	/* At this poपूर्णांक kasan is fully initialized. Enable error messages. */
	current->kasan_depth = 0;
	pr_info("KernelAddressSanitizer initialized\n");
पूर्ण
