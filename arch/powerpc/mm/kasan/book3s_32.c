<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा DISABLE_BRANCH_PROFILING

#समावेश <linux/kasan.h>
#समावेश <linux/memblock.h>
#समावेश <mm/mmu_decl.h>

पूर्णांक __init kasan_init_region(व्योम *start, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ k_start = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw(start);
	अचिन्हित दीर्घ k_end = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw(start + size);
	अचिन्हित दीर्घ k_cur = k_start;
	पूर्णांक k_size = k_end - k_start;
	पूर्णांक k_size_base = 1 << (ffs(k_size) - 1);
	पूर्णांक ret;
	व्योम *block;

	block = memblock_alloc(k_size, k_size_base);

	अगर (block && k_size_base >= SZ_128K && k_start == ALIGN(k_start, k_size_base)) अणु
		पूर्णांक k_size_more = 1 << (ffs(k_size - k_size_base) - 1);

		setbat(-1, k_start, __pa(block), k_size_base, PAGE_KERNEL);
		अगर (k_size_more >= SZ_128K)
			setbat(-1, k_start + k_size_base, __pa(block) + k_size_base,
			       k_size_more, PAGE_KERNEL);
		अगर (v_block_mapped(k_start))
			k_cur = k_start + k_size_base;
		अगर (v_block_mapped(k_start + k_size_base))
			k_cur = k_start + k_size_base + k_size_more;

		update_bats();
	पूर्ण

	अगर (!block)
		block = memblock_alloc(k_size, PAGE_SIZE);
	अगर (!block)
		वापस -ENOMEM;

	ret = kasan_init_shaकरोw_page_tables(k_start, k_end);
	अगर (ret)
		वापस ret;

	kasan_update_early_region(k_start, k_cur, __pte(0));

	क्रम (; k_cur < k_end; k_cur += PAGE_SIZE) अणु
		pmd_t *pmd = pmd_off_k(k_cur);
		व्योम *va = block + k_cur - k_start;
		pte_t pte = pfn_pte(PHYS_PFN(__pa(va)), PAGE_KERNEL);

		__set_pte_at(&init_mm, k_cur, pte_offset_kernel(pmd, k_cur), pte, 0);
	पूर्ण
	flush_tlb_kernel_range(k_start, k_end);
	वापस 0;
पूर्ण
