<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2003 PathScale Inc
 * Derived from include/यंत्र-i386/pgtable.h
 */

#अगर_अघोषित __UM_PGTABLE_3LEVEL_H
#घोषणा __UM_PGTABLE_3LEVEL_H

#समावेश <यंत्र-generic/pgtable-nopud.h>

/* PGसूची_SHIFT determines what a third-level page table entry can map */

#अगर_घोषित CONFIG_64BIT
#घोषणा PGसूची_SHIFT	30
#अन्यथा
#घोषणा PGसूची_SHIFT	31
#पूर्ण_अगर
#घोषणा PGसूची_SIZE	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))

/* PMD_SHIFT determines the size of the area a second-level page table can
 * map
 */

#घोषणा PMD_SHIFT	21
#घोषणा PMD_SIZE	(1UL << PMD_SHIFT)
#घोषणा PMD_MASK	(~(PMD_SIZE-1))

/*
 * entries per page directory level
 */

#घोषणा PTRS_PER_PTE 512
#अगर_घोषित CONFIG_64BIT
#घोषणा PTRS_PER_PMD 512
#घोषणा PTRS_PER_PGD 512
#अन्यथा
#घोषणा PTRS_PER_PMD 1024
#घोषणा PTRS_PER_PGD 1024
#पूर्ण_अगर

#घोषणा USER_PTRS_PER_PGD ((TASK_SIZE + (PGसूची_SIZE - 1)) / PGसूची_SIZE)
#घोषणा FIRST_USER_ADDRESS	0UL

#घोषणा pte_ERROR(e) \
        prपूर्णांकk("%s:%d: bad pte %p(%016lx).\n", __खाता__, __LINE__, &(e), \
	       pte_val(e))
#घोषणा pmd_ERROR(e) \
        prपूर्णांकk("%s:%d: bad pmd %p(%016lx).\n", __खाता__, __LINE__, &(e), \
	       pmd_val(e))
#घोषणा pgd_ERROR(e) \
        prपूर्णांकk("%s:%d: bad pgd %p(%016lx).\n", __खाता__, __LINE__, &(e), \
	       pgd_val(e))

#घोषणा pud_none(x)	(!(pud_val(x) & ~_PAGE_NEWPAGE))
#घोषणा	pud_bad(x)	((pud_val(x) & (~PAGE_MASK & ~_PAGE_USER)) != _KERNPG_TABLE)
#घोषणा pud_present(x)	(pud_val(x) & _PAGE_PRESENT)
#घोषणा pud_populate(mm, pud, pmd) \
	set_pud(pud, __pud(_PAGE_TABLE + __pa(pmd)))

#अगर_घोषित CONFIG_64BIT
#घोषणा set_pud(pudptr, pudval) set_64bit((u64 *) (pudptr), pud_val(pudval))
#अन्यथा
#घोषणा set_pud(pudptr, pudval) (*(pudptr) = (pudval))
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक pgd_newpage(pgd_t pgd)
अणु
	वापस(pgd_val(pgd) & _PAGE_NEWPAGE);
पूर्ण

अटल अंतरभूत व्योम pgd_mkuptodate(pgd_t pgd) अणु pgd_val(pgd) &= ~_PAGE_NEWPAGE; पूर्ण

#अगर_घोषित CONFIG_64BIT
#घोषणा set_pmd(pmdptr, pmdval) set_64bit((u64 *) (pmdptr), pmd_val(pmdval))
#अन्यथा
#घोषणा set_pmd(pmdptr, pmdval) (*(pmdptr) = (pmdval))
#पूर्ण_अगर

अटल अंतरभूत व्योम pud_clear (pud_t *pud)
अणु
	set_pud(pud, __pud(_PAGE_NEWPAGE));
पूर्ण

#घोषणा pud_page(pud) phys_to_page(pud_val(pud) & PAGE_MASK)
#घोषणा pud_page_vaddr(pud) ((अचिन्हित दीर्घ) __va(pud_val(pud) & PAGE_MASK))

अटल अंतरभूत अचिन्हित दीर्घ pte_pfn(pte_t pte)
अणु
	वापस phys_to_pfn(pte_val(pte));
पूर्ण

अटल अंतरभूत pte_t pfn_pte(अचिन्हित दीर्घ page_nr, pgprot_t pgprot)
अणु
	pte_t pte;
	phys_t phys = pfn_to_phys(page_nr);

	pte_set_val(pte, phys, pgprot);
	वापस pte;
पूर्ण

अटल अंतरभूत pmd_t pfn_pmd(अचिन्हित दीर्घ page_nr, pgprot_t pgprot)
अणु
	वापस __pmd((page_nr << PAGE_SHIFT) | pgprot_val(pgprot));
पूर्ण

#पूर्ण_अगर

