<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PGALLOC_H
#घोषणा _ASM_X86_PGALLOC_H

#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/mm.h>		/* क्रम काष्ठा page */
#समावेश <linux/pagemap.h>

#घोषणा __HAVE_ARCH_PTE_ALLOC_ONE
#घोषणा __HAVE_ARCH_PGD_FREE
#समावेश <यंत्र-generic/pgभाग.स>

अटल अंतरभूत पूर्णांक  __paravirt_pgd_alloc(काष्ठा mm_काष्ठा *mm) अणु वापस 0; पूर्ण

#अगर_घोषित CONFIG_PARAVIRT_XXL
#समावेश <यंत्र/paravirt.h>
#अन्यथा
#घोषणा paravirt_pgd_alloc(mm)	__paravirt_pgd_alloc(mm)
अटल अंतरभूत व्योम paravirt_pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd) अणुपूर्ण
अटल अंतरभूत व्योम paravirt_alloc_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn)	अणुपूर्ण
अटल अंतरभूत व्योम paravirt_alloc_pmd(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn)	अणुपूर्ण
अटल अंतरभूत व्योम paravirt_alloc_pmd_clone(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ clonepfn,
					    अचिन्हित दीर्घ start, अचिन्हित दीर्घ count) अणुपूर्ण
अटल अंतरभूत व्योम paravirt_alloc_pud(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn)	अणुपूर्ण
अटल अंतरभूत व्योम paravirt_alloc_p4d(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn)	अणुपूर्ण
अटल अंतरभूत व्योम paravirt_release_pte(अचिन्हित दीर्घ pfn) अणुपूर्ण
अटल अंतरभूत व्योम paravirt_release_pmd(अचिन्हित दीर्घ pfn) अणुपूर्ण
अटल अंतरभूत व्योम paravirt_release_pud(अचिन्हित दीर्घ pfn) अणुपूर्ण
अटल अंतरभूत व्योम paravirt_release_p4d(अचिन्हित दीर्घ pfn) अणुपूर्ण
#पूर्ण_अगर

/*
 * Flags to use when allocating a user page table page.
 */
बाह्य gfp_t __userpte_alloc_gfp;

#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
/*
 * Instead of one PGD, we acquire two PGDs.  Being order-1, it is
 * both 8k in size and 8k-aligned.  That lets us just flip bit 12
 * in a poपूर्णांकer to swap between the two 4k halves.
 */
#घोषणा PGD_ALLOCATION_ORDER 1
#अन्यथा
#घोषणा PGD_ALLOCATION_ORDER 0
#पूर्ण_अगर

/*
 * Allocate and मुक्त page tables.
 */
बाह्य pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *);
बाह्य व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd);

बाह्य pgtable_t pte_alloc_one(काष्ठा mm_काष्ठा *);

बाह्य व्योम ___pte_मुक्त_tlb(काष्ठा mmu_gather *tlb, काष्ठा page *pte);

अटल अंतरभूत व्योम __pte_मुक्त_tlb(काष्ठा mmu_gather *tlb, काष्ठा page *pte,
				  अचिन्हित दीर्घ address)
अणु
	___pte_मुक्त_tlb(tlb, pte);
पूर्ण

अटल अंतरभूत व्योम pmd_populate_kernel(काष्ठा mm_काष्ठा *mm,
				       pmd_t *pmd, pte_t *pte)
अणु
	paravirt_alloc_pte(mm, __pa(pte) >> PAGE_SHIFT);
	set_pmd(pmd, __pmd(__pa(pte) | _PAGE_TABLE));
पूर्ण

अटल अंतरभूत व्योम pmd_populate_kernel_safe(काष्ठा mm_काष्ठा *mm,
				       pmd_t *pmd, pte_t *pte)
अणु
	paravirt_alloc_pte(mm, __pa(pte) >> PAGE_SHIFT);
	set_pmd_safe(pmd, __pmd(__pa(pte) | _PAGE_TABLE));
पूर्ण

अटल अंतरभूत व्योम pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
				काष्ठा page *pte)
अणु
	अचिन्हित दीर्घ pfn = page_to_pfn(pte);

	paravirt_alloc_pte(mm, pfn);
	set_pmd(pmd, __pmd(((pteval_t)pfn << PAGE_SHIFT) | _PAGE_TABLE));
पूर्ण

#घोषणा pmd_pgtable(pmd) pmd_page(pmd)

#अगर CONFIG_PGTABLE_LEVELS > 2
बाह्य व्योम ___pmd_मुक्त_tlb(काष्ठा mmu_gather *tlb, pmd_t *pmd);

अटल अंतरभूत व्योम __pmd_मुक्त_tlb(काष्ठा mmu_gather *tlb, pmd_t *pmd,
				  अचिन्हित दीर्घ address)
अणु
	___pmd_मुक्त_tlb(tlb, pmd);
पूर्ण

#अगर_घोषित CONFIG_X86_PAE
बाह्य व्योम pud_populate(काष्ठा mm_काष्ठा *mm, pud_t *pudp, pmd_t *pmd);
#अन्यथा	/* !CONFIG_X86_PAE */
अटल अंतरभूत व्योम pud_populate(काष्ठा mm_काष्ठा *mm, pud_t *pud, pmd_t *pmd)
अणु
	paravirt_alloc_pmd(mm, __pa(pmd) >> PAGE_SHIFT);
	set_pud(pud, __pud(_PAGE_TABLE | __pa(pmd)));
पूर्ण

अटल अंतरभूत व्योम pud_populate_safe(काष्ठा mm_काष्ठा *mm, pud_t *pud, pmd_t *pmd)
अणु
	paravirt_alloc_pmd(mm, __pa(pmd) >> PAGE_SHIFT);
	set_pud_safe(pud, __pud(_PAGE_TABLE | __pa(pmd)));
पूर्ण
#पूर्ण_अगर	/* CONFIG_X86_PAE */

#अगर CONFIG_PGTABLE_LEVELS > 3
अटल अंतरभूत व्योम p4d_populate(काष्ठा mm_काष्ठा *mm, p4d_t *p4d, pud_t *pud)
अणु
	paravirt_alloc_pud(mm, __pa(pud) >> PAGE_SHIFT);
	set_p4d(p4d, __p4d(_PAGE_TABLE | __pa(pud)));
पूर्ण

अटल अंतरभूत व्योम p4d_populate_safe(काष्ठा mm_काष्ठा *mm, p4d_t *p4d, pud_t *pud)
अणु
	paravirt_alloc_pud(mm, __pa(pud) >> PAGE_SHIFT);
	set_p4d_safe(p4d, __p4d(_PAGE_TABLE | __pa(pud)));
पूर्ण

बाह्य व्योम ___pud_मुक्त_tlb(काष्ठा mmu_gather *tlb, pud_t *pud);

अटल अंतरभूत व्योम __pud_मुक्त_tlb(काष्ठा mmu_gather *tlb, pud_t *pud,
				  अचिन्हित दीर्घ address)
अणु
	___pud_मुक्त_tlb(tlb, pud);
पूर्ण

#अगर CONFIG_PGTABLE_LEVELS > 4
अटल अंतरभूत व्योम pgd_populate(काष्ठा mm_काष्ठा *mm, pgd_t *pgd, p4d_t *p4d)
अणु
	अगर (!pgtable_l5_enabled())
		वापस;
	paravirt_alloc_p4d(mm, __pa(p4d) >> PAGE_SHIFT);
	set_pgd(pgd, __pgd(_PAGE_TABLE | __pa(p4d)));
पूर्ण

अटल अंतरभूत व्योम pgd_populate_safe(काष्ठा mm_काष्ठा *mm, pgd_t *pgd, p4d_t *p4d)
अणु
	अगर (!pgtable_l5_enabled())
		वापस;
	paravirt_alloc_p4d(mm, __pa(p4d) >> PAGE_SHIFT);
	set_pgd_safe(pgd, __pgd(_PAGE_TABLE | __pa(p4d)));
पूर्ण

अटल अंतरभूत p4d_t *p4d_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	gfp_t gfp = GFP_KERNEL_ACCOUNT;

	अगर (mm == &init_mm)
		gfp &= ~__GFP_ACCOUNT;
	वापस (p4d_t *)get_zeroed_page(gfp);
पूर्ण

अटल अंतरभूत व्योम p4d_मुक्त(काष्ठा mm_काष्ठा *mm, p4d_t *p4d)
अणु
	अगर (!pgtable_l5_enabled())
		वापस;

	BUG_ON((अचिन्हित दीर्घ)p4d & (PAGE_SIZE-1));
	मुक्त_page((अचिन्हित दीर्घ)p4d);
पूर्ण

बाह्य व्योम ___p4d_मुक्त_tlb(काष्ठा mmu_gather *tlb, p4d_t *p4d);

अटल अंतरभूत व्योम __p4d_मुक्त_tlb(काष्ठा mmu_gather *tlb, p4d_t *p4d,
				  अचिन्हित दीर्घ address)
अणु
	अगर (pgtable_l5_enabled())
		___p4d_मुक्त_tlb(tlb, p4d);
पूर्ण

#पूर्ण_अगर	/* CONFIG_PGTABLE_LEVELS > 4 */
#पूर्ण_अगर	/* CONFIG_PGTABLE_LEVELS > 3 */
#पूर्ण_अगर	/* CONFIG_PGTABLE_LEVELS > 2 */

#पूर्ण_अगर /* _ASM_X86_PGALLOC_H */
