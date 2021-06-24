<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains KASAN shaकरोw initialization code.
 *
 * Copyright (c) 2015 Samsung Electronics Co., Ltd.
 * Author: Andrey Ryabinin <ryabinin.a.a@gmail.com>
 */

#समावेश <linux/memblock.h>
#समावेश <linux/init.h>
#समावेश <linux/kasan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/pfn.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgभाग.स>

#समावेश "kasan.h"

/*
 * This page serves two purposes:
 *   - It used as early shaकरोw memory. The entire shaकरोw region populated
 *     with this page, beक्रमe we will be able to setup normal shaकरोw memory.
 *   - Latter it reused it as zero shaकरोw to cover large ranges of memory
 *     that allowed to access, but not handled by kasan (vदो_स्मृति/vmemmap ...).
 */
अचिन्हित अक्षर kasan_early_shaकरोw_page[PAGE_SIZE] __page_aligned_bss;

#अगर CONFIG_PGTABLE_LEVELS > 4
p4d_t kasan_early_shaकरोw_p4d[MAX_PTRS_PER_P4D] __page_aligned_bss;
अटल अंतरभूत bool kasan_p4d_table(pgd_t pgd)
अणु
	वापस pgd_page(pgd) == virt_to_page(lm_alias(kasan_early_shaकरोw_p4d));
पूर्ण
#अन्यथा
अटल अंतरभूत bool kasan_p4d_table(pgd_t pgd)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर
#अगर CONFIG_PGTABLE_LEVELS > 3
pud_t kasan_early_shaकरोw_pud[PTRS_PER_PUD] __page_aligned_bss;
अटल अंतरभूत bool kasan_pud_table(p4d_t p4d)
अणु
	वापस p4d_page(p4d) == virt_to_page(lm_alias(kasan_early_shaकरोw_pud));
पूर्ण
#अन्यथा
अटल अंतरभूत bool kasan_pud_table(p4d_t p4d)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर
#अगर CONFIG_PGTABLE_LEVELS > 2
pmd_t kasan_early_shaकरोw_pmd[PTRS_PER_PMD] __page_aligned_bss;
अटल अंतरभूत bool kasan_pmd_table(pud_t pud)
अणु
	वापस pud_page(pud) == virt_to_page(lm_alias(kasan_early_shaकरोw_pmd));
पूर्ण
#अन्यथा
अटल अंतरभूत bool kasan_pmd_table(pud_t pud)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर
pte_t kasan_early_shaकरोw_pte[PTRS_PER_PTE + PTE_HWTABLE_PTRS]
	__page_aligned_bss;

अटल अंतरभूत bool kasan_pte_table(pmd_t pmd)
अणु
	वापस pmd_page(pmd) == virt_to_page(lm_alias(kasan_early_shaकरोw_pte));
पूर्ण

अटल अंतरभूत bool kasan_early_shaकरोw_page_entry(pte_t pte)
अणु
	वापस pte_page(pte) == virt_to_page(lm_alias(kasan_early_shaकरोw_page));
पूर्ण

अटल __init व्योम *early_alloc(माप_प्रकार size, पूर्णांक node)
अणु
	व्योम *ptr = memblock_alloc_try_nid(size, size, __pa(MAX_DMA_ADDRESS),
					   MEMBLOCK_ALLOC_ACCESSIBLE, node);

	अगर (!ptr)
		panic("%s: Failed to allocate %zu bytes align=%zx nid=%d from=%llx\n",
		      __func__, size, size, node, (u64)__pa(MAX_DMA_ADDRESS));

	वापस ptr;
पूर्ण

अटल व्योम __ref zero_pte_populate(pmd_t *pmd, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ end)
अणु
	pte_t *pte = pte_offset_kernel(pmd, addr);
	pte_t zero_pte;

	zero_pte = pfn_pte(PFN_DOWN(__pa_symbol(kasan_early_shaकरोw_page)),
				PAGE_KERNEL);
	zero_pte = pte_wrprotect(zero_pte);

	जबतक (addr + PAGE_SIZE <= end) अणु
		set_pte_at(&init_mm, addr, pte, zero_pte);
		addr += PAGE_SIZE;
		pte = pte_offset_kernel(pmd, addr);
	पूर्ण
पूर्ण

अटल पूर्णांक __ref zero_pmd_populate(pud_t *pud, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ end)
अणु
	pmd_t *pmd = pmd_offset(pud, addr);
	अचिन्हित दीर्घ next;

	करो अणु
		next = pmd_addr_end(addr, end);

		अगर (IS_ALIGNED(addr, PMD_SIZE) && end - addr >= PMD_SIZE) अणु
			pmd_populate_kernel(&init_mm, pmd,
					lm_alias(kasan_early_shaकरोw_pte));
			जारी;
		पूर्ण

		अगर (pmd_none(*pmd)) अणु
			pte_t *p;

			अगर (slab_is_available())
				p = pte_alloc_one_kernel(&init_mm);
			अन्यथा
				p = early_alloc(PAGE_SIZE, NUMA_NO_NODE);
			अगर (!p)
				वापस -ENOMEM;

			pmd_populate_kernel(&init_mm, pmd, p);
		पूर्ण
		zero_pte_populate(pmd, addr, next);
	पूर्ण जबतक (pmd++, addr = next, addr != end);

	वापस 0;
पूर्ण

अटल पूर्णांक __ref zero_pud_populate(p4d_t *p4d, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ end)
अणु
	pud_t *pud = pud_offset(p4d, addr);
	अचिन्हित दीर्घ next;

	करो अणु
		next = pud_addr_end(addr, end);
		अगर (IS_ALIGNED(addr, PUD_SIZE) && end - addr >= PUD_SIZE) अणु
			pmd_t *pmd;

			pud_populate(&init_mm, pud,
					lm_alias(kasan_early_shaकरोw_pmd));
			pmd = pmd_offset(pud, addr);
			pmd_populate_kernel(&init_mm, pmd,
					lm_alias(kasan_early_shaकरोw_pte));
			जारी;
		पूर्ण

		अगर (pud_none(*pud)) अणु
			pmd_t *p;

			अगर (slab_is_available()) अणु
				p = pmd_alloc(&init_mm, pud, addr);
				अगर (!p)
					वापस -ENOMEM;
			पूर्ण अन्यथा अणु
				pud_populate(&init_mm, pud,
					early_alloc(PAGE_SIZE, NUMA_NO_NODE));
			पूर्ण
		पूर्ण
		zero_pmd_populate(pud, addr, next);
	पूर्ण जबतक (pud++, addr = next, addr != end);

	वापस 0;
पूर्ण

अटल पूर्णांक __ref zero_p4d_populate(pgd_t *pgd, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ end)
अणु
	p4d_t *p4d = p4d_offset(pgd, addr);
	अचिन्हित दीर्घ next;

	करो अणु
		next = p4d_addr_end(addr, end);
		अगर (IS_ALIGNED(addr, P4D_SIZE) && end - addr >= P4D_SIZE) अणु
			pud_t *pud;
			pmd_t *pmd;

			p4d_populate(&init_mm, p4d,
					lm_alias(kasan_early_shaकरोw_pud));
			pud = pud_offset(p4d, addr);
			pud_populate(&init_mm, pud,
					lm_alias(kasan_early_shaकरोw_pmd));
			pmd = pmd_offset(pud, addr);
			pmd_populate_kernel(&init_mm, pmd,
					lm_alias(kasan_early_shaकरोw_pte));
			जारी;
		पूर्ण

		अगर (p4d_none(*p4d)) अणु
			pud_t *p;

			अगर (slab_is_available()) अणु
				p = pud_alloc(&init_mm, p4d, addr);
				अगर (!p)
					वापस -ENOMEM;
			पूर्ण अन्यथा अणु
				p4d_populate(&init_mm, p4d,
					early_alloc(PAGE_SIZE, NUMA_NO_NODE));
			पूर्ण
		पूर्ण
		zero_pud_populate(p4d, addr, next);
	पूर्ण जबतक (p4d++, addr = next, addr != end);

	वापस 0;
पूर्ण

/**
 * kasan_populate_early_shaकरोw - populate shaकरोw memory region with
 *                               kasan_early_shaकरोw_page
 * @shaकरोw_start: start of the memory range to populate
 * @shaकरोw_end: end of the memory range to populate
 */
पूर्णांक __ref kasan_populate_early_shaकरोw(स्थिर व्योम *shaकरोw_start,
					स्थिर व्योम *shaकरोw_end)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)shaकरोw_start;
	अचिन्हित दीर्घ end = (अचिन्हित दीर्घ)shaकरोw_end;
	pgd_t *pgd = pgd_offset_k(addr);
	अचिन्हित दीर्घ next;

	करो अणु
		next = pgd_addr_end(addr, end);

		अगर (IS_ALIGNED(addr, PGसूची_SIZE) && end - addr >= PGसूची_SIZE) अणु
			p4d_t *p4d;
			pud_t *pud;
			pmd_t *pmd;

			/*
			 * kasan_early_shaकरोw_pud should be populated with pmds
			 * at this moment.
			 * [pud,pmd]_populate*() below needed only क्रम
			 * 3,2 - level page tables where we करोn't have
			 * puds,pmds, so pgd_populate(), pud_populate()
			 * is noops.
			 */
			pgd_populate(&init_mm, pgd,
					lm_alias(kasan_early_shaकरोw_p4d));
			p4d = p4d_offset(pgd, addr);
			p4d_populate(&init_mm, p4d,
					lm_alias(kasan_early_shaकरोw_pud));
			pud = pud_offset(p4d, addr);
			pud_populate(&init_mm, pud,
					lm_alias(kasan_early_shaकरोw_pmd));
			pmd = pmd_offset(pud, addr);
			pmd_populate_kernel(&init_mm, pmd,
					lm_alias(kasan_early_shaकरोw_pte));
			जारी;
		पूर्ण

		अगर (pgd_none(*pgd)) अणु
			p4d_t *p;

			अगर (slab_is_available()) अणु
				p = p4d_alloc(&init_mm, pgd, addr);
				अगर (!p)
					वापस -ENOMEM;
			पूर्ण अन्यथा अणु
				pgd_populate(&init_mm, pgd,
					early_alloc(PAGE_SIZE, NUMA_NO_NODE));
			पूर्ण
		पूर्ण
		zero_p4d_populate(pgd, addr, next);
	पूर्ण जबतक (pgd++, addr = next, addr != end);

	वापस 0;
पूर्ण

अटल व्योम kasan_मुक्त_pte(pte_t *pte_start, pmd_t *pmd)
अणु
	pte_t *pte;
	पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PTE; i++) अणु
		pte = pte_start + i;
		अगर (!pte_none(*pte))
			वापस;
	पूर्ण

	pte_मुक्त_kernel(&init_mm, (pte_t *)page_to_virt(pmd_page(*pmd)));
	pmd_clear(pmd);
पूर्ण

अटल व्योम kasan_मुक्त_pmd(pmd_t *pmd_start, pud_t *pud)
अणु
	pmd_t *pmd;
	पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PMD; i++) अणु
		pmd = pmd_start + i;
		अगर (!pmd_none(*pmd))
			वापस;
	पूर्ण

	pmd_मुक्त(&init_mm, (pmd_t *)page_to_virt(pud_page(*pud)));
	pud_clear(pud);
पूर्ण

अटल व्योम kasan_मुक्त_pud(pud_t *pud_start, p4d_t *p4d)
अणु
	pud_t *pud;
	पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PUD; i++) अणु
		pud = pud_start + i;
		अगर (!pud_none(*pud))
			वापस;
	पूर्ण

	pud_मुक्त(&init_mm, (pud_t *)page_to_virt(p4d_page(*p4d)));
	p4d_clear(p4d);
पूर्ण

अटल व्योम kasan_मुक्त_p4d(p4d_t *p4d_start, pgd_t *pgd)
अणु
	p4d_t *p4d;
	पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_P4D; i++) अणु
		p4d = p4d_start + i;
		अगर (!p4d_none(*p4d))
			वापस;
	पूर्ण

	p4d_मुक्त(&init_mm, (p4d_t *)page_to_virt(pgd_page(*pgd)));
	pgd_clear(pgd);
पूर्ण

अटल व्योम kasan_हटाओ_pte_table(pte_t *pte, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ next;

	क्रम (; addr < end; addr = next, pte++) अणु
		next = (addr + PAGE_SIZE) & PAGE_MASK;
		अगर (next > end)
			next = end;

		अगर (!pte_present(*pte))
			जारी;

		अगर (WARN_ON(!kasan_early_shaकरोw_page_entry(*pte)))
			जारी;
		pte_clear(&init_mm, addr, pte);
	पूर्ण
पूर्ण

अटल व्योम kasan_हटाओ_pmd_table(pmd_t *pmd, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ next;

	क्रम (; addr < end; addr = next, pmd++) अणु
		pte_t *pte;

		next = pmd_addr_end(addr, end);

		अगर (!pmd_present(*pmd))
			जारी;

		अगर (kasan_pte_table(*pmd)) अणु
			अगर (IS_ALIGNED(addr, PMD_SIZE) &&
			    IS_ALIGNED(next, PMD_SIZE)) अणु
				pmd_clear(pmd);
				जारी;
			पूर्ण
		पूर्ण
		pte = pte_offset_kernel(pmd, addr);
		kasan_हटाओ_pte_table(pte, addr, next);
		kasan_मुक्त_pte(pte_offset_kernel(pmd, 0), pmd);
	पूर्ण
पूर्ण

अटल व्योम kasan_हटाओ_pud_table(pud_t *pud, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ next;

	क्रम (; addr < end; addr = next, pud++) अणु
		pmd_t *pmd, *pmd_base;

		next = pud_addr_end(addr, end);

		अगर (!pud_present(*pud))
			जारी;

		अगर (kasan_pmd_table(*pud)) अणु
			अगर (IS_ALIGNED(addr, PUD_SIZE) &&
			    IS_ALIGNED(next, PUD_SIZE)) अणु
				pud_clear(pud);
				जारी;
			पूर्ण
		पूर्ण
		pmd = pmd_offset(pud, addr);
		pmd_base = pmd_offset(pud, 0);
		kasan_हटाओ_pmd_table(pmd, addr, next);
		kasan_मुक्त_pmd(pmd_base, pud);
	पूर्ण
पूर्ण

अटल व्योम kasan_हटाओ_p4d_table(p4d_t *p4d, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ next;

	क्रम (; addr < end; addr = next, p4d++) अणु
		pud_t *pud;

		next = p4d_addr_end(addr, end);

		अगर (!p4d_present(*p4d))
			जारी;

		अगर (kasan_pud_table(*p4d)) अणु
			अगर (IS_ALIGNED(addr, P4D_SIZE) &&
			    IS_ALIGNED(next, P4D_SIZE)) अणु
				p4d_clear(p4d);
				जारी;
			पूर्ण
		पूर्ण
		pud = pud_offset(p4d, addr);
		kasan_हटाओ_pud_table(pud, addr, next);
		kasan_मुक्त_pud(pud_offset(p4d, 0), p4d);
	पूर्ण
पूर्ण

व्योम kasan_हटाओ_zero_shaकरोw(व्योम *start, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ addr, end, next;
	pgd_t *pgd;

	addr = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw(start);
	end = addr + (size >> KASAN_SHADOW_SCALE_SHIFT);

	अगर (WARN_ON((अचिन्हित दीर्घ)start % KASAN_MEMORY_PER_SHADOW_PAGE) ||
	    WARN_ON(size % KASAN_MEMORY_PER_SHADOW_PAGE))
		वापस;

	क्रम (; addr < end; addr = next) अणु
		p4d_t *p4d;

		next = pgd_addr_end(addr, end);

		pgd = pgd_offset_k(addr);
		अगर (!pgd_present(*pgd))
			जारी;

		अगर (kasan_p4d_table(*pgd)) अणु
			अगर (IS_ALIGNED(addr, PGसूची_SIZE) &&
			    IS_ALIGNED(next, PGसूची_SIZE)) अणु
				pgd_clear(pgd);
				जारी;
			पूर्ण
		पूर्ण

		p4d = p4d_offset(pgd, addr);
		kasan_हटाओ_p4d_table(p4d, addr, next);
		kasan_मुक्त_p4d(p4d_offset(pgd, 0), pgd);
	पूर्ण
पूर्ण

पूर्णांक kasan_add_zero_shaकरोw(व्योम *start, अचिन्हित दीर्घ size)
अणु
	पूर्णांक ret;
	व्योम *shaकरोw_start, *shaकरोw_end;

	shaकरोw_start = kasan_mem_to_shaकरोw(start);
	shaकरोw_end = shaकरोw_start + (size >> KASAN_SHADOW_SCALE_SHIFT);

	अगर (WARN_ON((अचिन्हित दीर्घ)start % KASAN_MEMORY_PER_SHADOW_PAGE) ||
	    WARN_ON(size % KASAN_MEMORY_PER_SHADOW_PAGE))
		वापस -EINVAL;

	ret = kasan_populate_early_shaकरोw(shaकरोw_start, shaकरोw_end);
	अगर (ret)
		kasan_हटाओ_zero_shaकरोw(start, size);
	वापस ret;
पूर्ण
