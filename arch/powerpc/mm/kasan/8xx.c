<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा DISABLE_BRANCH_PROFILING

#समावेश <linux/kasan.h>
#समावेश <linux/memblock.h>
#समावेश <linux/hugetlb.h>

अटल पूर्णांक __init
kasan_init_shaकरोw_8M(अचिन्हित दीर्घ k_start, अचिन्हित दीर्घ k_end, व्योम *block)
अणु
	pmd_t *pmd = pmd_off_k(k_start);
	अचिन्हित दीर्घ k_cur, k_next;

	क्रम (k_cur = k_start; k_cur != k_end; k_cur = k_next, pmd += 2, block += SZ_8M) अणु
		pte_basic_t *new;

		k_next = pgd_addr_end(k_cur, k_end);
		k_next = pgd_addr_end(k_next, k_end);
		अगर ((व्योम *)pmd_page_vaddr(*pmd) != kasan_early_shaकरोw_pte)
			जारी;

		new = memblock_alloc(माप(pte_basic_t), SZ_4K);
		अगर (!new)
			वापस -ENOMEM;

		*new = pte_val(pte_mkhuge(pfn_pte(PHYS_PFN(__pa(block)), PAGE_KERNEL)));

		hugepd_populate_kernel((hugepd_t *)pmd, (pte_t *)new, PAGE_SHIFT_8M);
		hugepd_populate_kernel((hugepd_t *)pmd + 1, (pte_t *)new, PAGE_SHIFT_8M);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक __init kasan_init_region(व्योम *start, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ k_start = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw(start);
	अचिन्हित दीर्घ k_end = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw(start + size);
	अचिन्हित दीर्घ k_cur;
	पूर्णांक ret;
	व्योम *block;

	block = memblock_alloc(k_end - k_start, SZ_8M);
	अगर (!block)
		वापस -ENOMEM;

	अगर (IS_ALIGNED(k_start, SZ_8M)) अणु
		kasan_init_shaकरोw_8M(k_start, ALIGN_DOWN(k_end, SZ_8M), block);
		k_cur = ALIGN_DOWN(k_end, SZ_8M);
		अगर (k_cur == k_end)
			जाओ finish;
	पूर्ण अन्यथा अणु
		k_cur = k_start;
	पूर्ण

	ret = kasan_init_shaकरोw_page_tables(k_start, k_end);
	अगर (ret)
		वापस ret;

	क्रम (; k_cur < k_end; k_cur += PAGE_SIZE) अणु
		pmd_t *pmd = pmd_off_k(k_cur);
		व्योम *va = block + k_cur - k_start;
		pte_t pte = pfn_pte(PHYS_PFN(__pa(va)), PAGE_KERNEL);

		अगर (k_cur < ALIGN_DOWN(k_end, SZ_512K))
			pte = pte_mkhuge(pte);

		__set_pte_at(&init_mm, k_cur, pte_offset_kernel(pmd, k_cur), pte, 0);
	पूर्ण
finish:
	flush_tlb_kernel_range(k_start, k_end);
	वापस 0;
पूर्ण
