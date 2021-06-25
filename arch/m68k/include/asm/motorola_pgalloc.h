<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MOTOROLA_PGALLOC_H
#घोषणा _MOTOROLA_PGALLOC_H

#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>

बाह्य व्योम mmu_page_ctor(व्योम *page);
बाह्य व्योम mmu_page_dtor(व्योम *page);

क्रमागत m68k_table_types अणु
	TABLE_PGD = 0,
	TABLE_PMD = 0, /* same size as PGD */
	TABLE_PTE = 1,
पूर्ण;

बाह्य व्योम init_poपूर्णांकer_table(व्योम *table, पूर्णांक type);
बाह्य व्योम *get_poपूर्णांकer_table(पूर्णांक type);
बाह्य पूर्णांक मुक्त_poपूर्णांकer_table(व्योम *table, पूर्णांक type);

/*
 * Allocate and मुक्त page tables. The xxx_kernel() versions are
 * used to allocate a kernel page table - this turns on ASN bits
 * अगर any.
 */

अटल अंतरभूत pte_t *pte_alloc_one_kernel(काष्ठा mm_काष्ठा *mm)
अणु
	वापस get_poपूर्णांकer_table(TABLE_PTE);
पूर्ण

अटल अंतरभूत व्योम pte_मुक्त_kernel(काष्ठा mm_काष्ठा *mm, pte_t *pte)
अणु
	मुक्त_poपूर्णांकer_table(pte, TABLE_PTE);
पूर्ण

अटल अंतरभूत pgtable_t pte_alloc_one(काष्ठा mm_काष्ठा *mm)
अणु
	वापस get_poपूर्णांकer_table(TABLE_PTE);
पूर्ण

अटल अंतरभूत व्योम pte_मुक्त(काष्ठा mm_काष्ठा *mm, pgtable_t pgtable)
अणु
	मुक्त_poपूर्णांकer_table(pgtable, TABLE_PTE);
पूर्ण

अटल अंतरभूत व्योम __pte_मुक्त_tlb(काष्ठा mmu_gather *tlb, pgtable_t pgtable,
				  अचिन्हित दीर्घ address)
अणु
	मुक्त_poपूर्णांकer_table(pgtable, TABLE_PTE);
पूर्ण


अटल अंतरभूत pmd_t *pmd_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address)
अणु
	वापस get_poपूर्णांकer_table(TABLE_PMD);
पूर्ण

अटल अंतरभूत पूर्णांक pmd_मुक्त(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
	वापस मुक्त_poपूर्णांकer_table(pmd, TABLE_PMD);
पूर्ण

अटल अंतरभूत पूर्णांक __pmd_मुक्त_tlb(काष्ठा mmu_gather *tlb, pmd_t *pmd,
				 अचिन्हित दीर्घ address)
अणु
	वापस मुक्त_poपूर्णांकer_table(pmd, TABLE_PMD);
पूर्ण


अटल अंतरभूत व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	मुक्त_poपूर्णांकer_table(pgd, TABLE_PGD);
पूर्ण

अटल अंतरभूत pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	वापस get_poपूर्णांकer_table(TABLE_PGD);
पूर्ण


अटल अंतरभूत व्योम pmd_populate_kernel(काष्ठा mm_काष्ठा *mm, pmd_t *pmd, pte_t *pte)
अणु
	pmd_set(pmd, pte);
पूर्ण

अटल अंतरभूत व्योम pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t *pmd, pgtable_t page)
अणु
	pmd_set(pmd, page);
पूर्ण
#घोषणा pmd_pgtable(pmd) ((pgtable_t)pmd_page_vaddr(pmd))

अटल अंतरभूत व्योम pud_populate(काष्ठा mm_काष्ठा *mm, pud_t *pud, pmd_t *pmd)
अणु
	pud_set(pud, pmd);
पूर्ण

#पूर्ण_अगर /* _MOTOROLA_PGALLOC_H */
