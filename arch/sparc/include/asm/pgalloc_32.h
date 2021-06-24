<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC_PGALLOC_H
#घोषणा _SPARC_PGALLOC_H

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/pgtsrmmu.h>
#समावेश <यंत्र/vaddrs.h>
#समावेश <यंत्र/page.h>

काष्ठा page;

व्योम *srmmu_get_nocache(पूर्णांक size, पूर्णांक align);
व्योम srmmu_मुक्त_nocache(व्योम *addr, पूर्णांक size);

बाह्य काष्ठा resource sparc_iomap;

pgd_t *get_pgd_fast(व्योम);
अटल अंतरभूत व्योम मुक्त_pgd_fast(pgd_t *pgd)
अणु
	srmmu_मुक्त_nocache(pgd, SRMMU_PGD_TABLE_SIZE);
पूर्ण

#घोषणा pgd_मुक्त(mm, pgd)	मुक्त_pgd_fast(pgd)
#घोषणा pgd_alloc(mm)	get_pgd_fast()

अटल अंतरभूत व्योम pud_set(pud_t * pudp, pmd_t * pmdp)
अणु
	अचिन्हित दीर्घ pa = __nocache_pa(pmdp);

	set_pte((pte_t *)pudp, __pte((SRMMU_ET_PTD | (pa >> 4))));
पूर्ण

#घोषणा pud_populate(MM, PGD, PMD)      pud_set(PGD, PMD)

अटल अंतरभूत pmd_t *pmd_alloc_one(काष्ठा mm_काष्ठा *mm,
				   अचिन्हित दीर्घ address)
अणु
	वापस srmmu_get_nocache(SRMMU_PMD_TABLE_SIZE,
				 SRMMU_PMD_TABLE_SIZE);
पूर्ण

अटल अंतरभूत व्योम मुक्त_pmd_fast(pmd_t * pmd)
अणु
	srmmu_मुक्त_nocache(pmd, SRMMU_PMD_TABLE_SIZE);
पूर्ण

#घोषणा pmd_मुक्त(mm, pmd)		मुक्त_pmd_fast(pmd)
#घोषणा __pmd_मुक्त_tlb(tlb, pmd, addr)	pmd_मुक्त((tlb)->mm, pmd)

#घोषणा pmd_populate(mm, pmd, pte)	pmd_set(pmd, pte)
#घोषणा pmd_pgtable(pmd)		(pgtable_t)__pmd_page(pmd)

व्योम pmd_set(pmd_t *pmdp, pte_t *ptep);
#घोषणा pmd_populate_kernel		pmd_populate

pgtable_t pte_alloc_one(काष्ठा mm_काष्ठा *mm);

अटल अंतरभूत pte_t *pte_alloc_one_kernel(काष्ठा mm_काष्ठा *mm)
अणु
	वापस srmmu_get_nocache(SRMMU_PTE_TABLE_SIZE,
				 SRMMU_PTE_TABLE_SIZE);
पूर्ण


अटल अंतरभूत व्योम मुक्त_pte_fast(pte_t *pte)
अणु
	srmmu_मुक्त_nocache(pte, SRMMU_PTE_TABLE_SIZE);
पूर्ण

#घोषणा pte_मुक्त_kernel(mm, pte)	मुक्त_pte_fast(pte)

व्योम pte_मुक्त(काष्ठा mm_काष्ठा * mm, pgtable_t pte);
#घोषणा __pte_मुक्त_tlb(tlb, pte, addr)	pte_मुक्त((tlb)->mm, pte)

#पूर्ण_अगर /* _SPARC_PGALLOC_H */
