<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा DISABLE_BRANCH_PROFILING

#समावेश <linux/kasan.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/memblock.h>
#समावेश <linux/sched/task.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/code-patching.h>
#समावेश <mm/mmu_decl.h>

अटल pgprot_t __init kasan_prot_ro(व्योम)
अणु
	अगर (early_mmu_has_feature(MMU_FTR_HPTE_TABLE))
		वापस PAGE_READONLY;

	वापस PAGE_KERNEL_RO;
पूर्ण

अटल व्योम __init kasan_populate_pte(pte_t *ptep, pgprot_t prot)
अणु
	अचिन्हित दीर्घ va = (अचिन्हित दीर्घ)kasan_early_shaकरोw_page;
	phys_addr_t pa = __pa(kasan_early_shaकरोw_page);
	पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PTE; i++, ptep++)
		__set_pte_at(&init_mm, va, ptep, pfn_pte(PHYS_PFN(pa), prot), 0);
पूर्ण

पूर्णांक __init kasan_init_shaकरोw_page_tables(अचिन्हित दीर्घ k_start, अचिन्हित दीर्घ k_end)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ k_cur, k_next;

	pmd = pmd_off_k(k_start);

	क्रम (k_cur = k_start; k_cur != k_end; k_cur = k_next, pmd++) अणु
		pte_t *new;

		k_next = pgd_addr_end(k_cur, k_end);
		अगर ((व्योम *)pmd_page_vaddr(*pmd) != kasan_early_shaकरोw_pte)
			जारी;

		new = memblock_alloc(PTE_FRAG_SIZE, PTE_FRAG_SIZE);

		अगर (!new)
			वापस -ENOMEM;
		kasan_populate_pte(new, PAGE_KERNEL);
		pmd_populate_kernel(&init_mm, pmd, new);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक __init __weak kasan_init_region(व्योम *start, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ k_start = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw(start);
	अचिन्हित दीर्घ k_end = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw(start + size);
	अचिन्हित दीर्घ k_cur;
	पूर्णांक ret;
	व्योम *block;

	ret = kasan_init_shaकरोw_page_tables(k_start, k_end);
	अगर (ret)
		वापस ret;

	block = memblock_alloc(k_end - k_start, PAGE_SIZE);
	अगर (!block)
		वापस -ENOMEM;

	क्रम (k_cur = k_start & PAGE_MASK; k_cur < k_end; k_cur += PAGE_SIZE) अणु
		pmd_t *pmd = pmd_off_k(k_cur);
		व्योम *va = block + k_cur - k_start;
		pte_t pte = pfn_pte(PHYS_PFN(__pa(va)), PAGE_KERNEL);

		__set_pte_at(&init_mm, k_cur, pte_offset_kernel(pmd, k_cur), pte, 0);
	पूर्ण
	flush_tlb_kernel_range(k_start, k_end);
	वापस 0;
पूर्ण

व्योम __init
kasan_update_early_region(अचिन्हित दीर्घ k_start, अचिन्हित दीर्घ k_end, pte_t pte)
अणु
	अचिन्हित दीर्घ k_cur;
	phys_addr_t pa = __pa(kasan_early_shaकरोw_page);

	क्रम (k_cur = k_start; k_cur != k_end; k_cur += PAGE_SIZE) अणु
		pmd_t *pmd = pmd_off_k(k_cur);
		pte_t *ptep = pte_offset_kernel(pmd, k_cur);

		अगर ((pte_val(*ptep) & PTE_RPN_MASK) != pa)
			जारी;

		__set_pte_at(&init_mm, k_cur, ptep, pte, 0);
	पूर्ण

	flush_tlb_kernel_range(k_start, k_end);
पूर्ण

अटल व्योम __init kasan_remap_early_shaकरोw_ro(व्योम)
अणु
	pgprot_t prot = kasan_prot_ro();
	phys_addr_t pa = __pa(kasan_early_shaकरोw_page);

	kasan_populate_pte(kasan_early_shaकरोw_pte, prot);

	kasan_update_early_region(KASAN_SHADOW_START, KASAN_SHADOW_END,
				  pfn_pte(PHYS_PFN(pa), prot));
पूर्ण

अटल व्योम __init kasan_unmap_early_shaकरोw_vदो_स्मृति(व्योम)
अणु
	अचिन्हित दीर्घ k_start = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw((व्योम *)VMALLOC_START);
	अचिन्हित दीर्घ k_end = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw((व्योम *)VMALLOC_END);

	kasan_update_early_region(k_start, k_end, __pte(0));

#अगर_घोषित MODULES_VADDR
	k_start = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw((व्योम *)MODULES_VADDR);
	k_end = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw((व्योम *)MODULES_END);
	kasan_update_early_region(k_start, k_end, __pte(0));
#पूर्ण_अगर
पूर्ण

व्योम __init kasan_mmu_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (early_mmu_has_feature(MMU_FTR_HPTE_TABLE)) अणु
		ret = kasan_init_shaकरोw_page_tables(KASAN_SHADOW_START, KASAN_SHADOW_END);

		अगर (ret)
			panic("kasan: kasan_init_shadow_page_tables() failed");
	पूर्ण
पूर्ण

व्योम __init kasan_init(व्योम)
अणु
	phys_addr_t base, end;
	u64 i;
	पूर्णांक ret;

	क्रम_each_mem_range(i, &base, &end) अणु
		phys_addr_t top = min(end, total_lowmem);

		अगर (base >= top)
			जारी;

		ret = kasan_init_region(__va(base), top - base);
		अगर (ret)
			panic("kasan: kasan_init_region() failed");
	पूर्ण

	अगर (IS_ENABLED(CONFIG_KASAN_VMALLOC)) अणु
		ret = kasan_init_shaकरोw_page_tables(KASAN_SHADOW_START, KASAN_SHADOW_END);

		अगर (ret)
			panic("kasan: kasan_init_shadow_page_tables() failed");
	पूर्ण

	kasan_remap_early_shaकरोw_ro();

	clear_page(kasan_early_shaकरोw_page);

	/* At this poपूर्णांक kasan is fully initialized. Enable error messages */
	init_task.kasan_depth = 0;
	pr_info("KASAN init done\n");
पूर्ण

व्योम __init kasan_late_init(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_KASAN_VMALLOC))
		kasan_unmap_early_shaकरोw_vदो_स्मृति();
पूर्ण

व्योम __init kasan_early_init(व्योम)
अणु
	अचिन्हित दीर्घ addr = KASAN_SHADOW_START;
	अचिन्हित दीर्घ end = KASAN_SHADOW_END;
	अचिन्हित दीर्घ next;
	pmd_t *pmd = pmd_off_k(addr);

	BUILD_BUG_ON(KASAN_SHADOW_START & ~PGसूची_MASK);

	kasan_populate_pte(kasan_early_shaकरोw_pte, PAGE_KERNEL);

	करो अणु
		next = pgd_addr_end(addr, end);
		pmd_populate_kernel(&init_mm, pmd, kasan_early_shaकरोw_pte);
	पूर्ण जबतक (pmd++, addr = next, addr != end);
पूर्ण
