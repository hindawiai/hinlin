<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/pgभाग.स
 *
 *  Copyright (C) 2000-2001 Russell King
 */
#अगर_अघोषित _ASMARM_PGALLOC_H
#घोषणा _ASMARM_PGALLOC_H

#समावेश <linux/pagemap.h>

#समावेश <यंत्र/करोमुख्य.h>
#समावेश <यंत्र/pgtable-hwdef.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>

#अगर_घोषित CONFIG_MMU

#घोषणा _PAGE_USER_TABLE	(PMD_TYPE_TABLE | PMD_BIT4 | PMD_DOMAIN(DOMAIN_USER))
#घोषणा _PAGE_KERNEL_TABLE	(PMD_TYPE_TABLE | PMD_BIT4 | PMD_DOMAIN(DOMAIN_KERNEL))

#अगर_घोषित CONFIG_ARM_LPAE
#घोषणा PGD_SIZE		(PTRS_PER_PGD * माप(pgd_t))

अटल अंतरभूत व्योम pud_populate(काष्ठा mm_काष्ठा *mm, pud_t *pud, pmd_t *pmd)
अणु
	set_pud(pud, __pud(__pa(pmd) | PMD_TYPE_TABLE));
पूर्ण

#अन्यथा	/* !CONFIG_ARM_LPAE */
#घोषणा PGD_SIZE		(PAGE_SIZE << 2)

/*
 * Since we have only two-level page tables, these are trivial
 */
#घोषणा pmd_alloc_one(mm,addr)		(अणु BUG(); ((pmd_t *)2); पूर्ण)
#घोषणा pmd_मुक्त(mm, pmd)		करो अणु पूर्ण जबतक (0)
#अगर_घोषित CONFIG_KASAN
/* The KASan core unconditionally calls pud_populate() on all architectures */
#घोषणा pud_populate(mm,pmd,pte)	करो अणु पूर्ण जबतक (0)
#अन्यथा
#घोषणा pud_populate(mm,pmd,pte)	BUG()
#पूर्ण_अगर
#पूर्ण_अगर	/* CONFIG_ARM_LPAE */

बाह्य pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd);

अटल अंतरभूत व्योम clean_pte_table(pte_t *pte)
अणु
	clean_dcache_area(pte + PTE_HWTABLE_PTRS, PTE_HWTABLE_SIZE);
पूर्ण

/*
 * Allocate one PTE table.
 *
 * This actually allocates two hardware PTE tables, but we wrap this up
 * पूर्णांकo one table thus:
 *
 *  +------------+
 *  | Linux pt 0 |
 *  +------------+
 *  | Linux pt 1 |
 *  +------------+
 *  |  h/w pt 0  |
 *  +------------+
 *  |  h/w pt 1  |
 *  +------------+
 */

#घोषणा __HAVE_ARCH_PTE_ALLOC_ONE_KERNEL
#घोषणा __HAVE_ARCH_PTE_ALLOC_ONE
#घोषणा __HAVE_ARCH_PGD_FREE
#समावेश <यंत्र-generic/pgभाग.स>

अटल अंतरभूत pte_t *
pte_alloc_one_kernel(काष्ठा mm_काष्ठा *mm)
अणु
	pte_t *pte = __pte_alloc_one_kernel(mm);

	अगर (pte)
		clean_pte_table(pte);

	वापस pte;
पूर्ण

#अगर_घोषित CONFIG_HIGHPTE
#घोषणा PGTABLE_HIGHMEM __GFP_HIGHMEM
#अन्यथा
#घोषणा PGTABLE_HIGHMEM 0
#पूर्ण_अगर

अटल अंतरभूत pgtable_t
pte_alloc_one(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा page *pte;

	pte = __pte_alloc_one(mm, GFP_PGTABLE_USER | PGTABLE_HIGHMEM);
	अगर (!pte)
		वापस शून्य;
	अगर (!PageHighMem(pte))
		clean_pte_table(page_address(pte));
	वापस pte;
पूर्ण

अटल अंतरभूत व्योम __pmd_populate(pmd_t *pmdp, phys_addr_t pte,
				  pmdval_t prot)
अणु
	pmdval_t pmdval = (pte + PTE_HWTABLE_OFF) | prot;
	pmdp[0] = __pmd(pmdval);
#अगर_अघोषित CONFIG_ARM_LPAE
	pmdp[1] = __pmd(pmdval + 256 * माप(pte_t));
#पूर्ण_अगर
	flush_pmd_entry(pmdp);
पूर्ण

/*
 * Populate the pmdp entry with a poपूर्णांकer to the pte.  This pmd is part
 * of the mm address space.
 *
 * Ensure that we always set both PMD entries.
 */
अटल अंतरभूत व्योम
pmd_populate_kernel(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp, pte_t *ptep)
अणु
	/*
	 * The pmd must be loaded with the physical address of the PTE table
	 */
	__pmd_populate(pmdp, __pa(ptep), _PAGE_KERNEL_TABLE);
पूर्ण

अटल अंतरभूत व्योम
pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp, pgtable_t ptep)
अणु
	बाह्य pmdval_t user_pmd_table;
	pmdval_t prot;

	अगर (__LINUX_ARM_ARCH__ >= 6 && !IS_ENABLED(CONFIG_ARM_LPAE))
		prot = user_pmd_table;
	अन्यथा
		prot = _PAGE_USER_TABLE;

	__pmd_populate(pmdp, page_to_phys(ptep), prot);
पूर्ण
#घोषणा pmd_pgtable(pmd) pmd_page(pmd)

#पूर्ण_अगर /* CONFIG_MMU */

#पूर्ण_अगर
