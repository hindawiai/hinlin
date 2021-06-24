<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_PGALLOC_H
#घोषणा __ASM_SH_PGALLOC_H

#समावेश <यंत्र/page.h>

#घोषणा __HAVE_ARCH_PMD_ALLOC_ONE
#घोषणा __HAVE_ARCH_PMD_FREE
#घोषणा __HAVE_ARCH_PGD_FREE
#समावेश <यंत्र-generic/pgभाग.स>

बाह्य pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *);
बाह्य व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd);

#अगर PAGETABLE_LEVELS > 2
बाह्य व्योम pud_populate(काष्ठा mm_काष्ठा *mm, pud_t *pudp, pmd_t *pmd);
बाह्य pmd_t *pmd_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address);
बाह्य व्योम pmd_मुक्त(काष्ठा mm_काष्ठा *mm, pmd_t *pmd);
#घोषणा __pmd_मुक्त_tlb(tlb, pmdp, addr)		pmd_मुक्त((tlb)->mm, (pmdp))
#पूर्ण_अगर

अटल अंतरभूत व्योम pmd_populate_kernel(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
				       pte_t *pte)
अणु
	set_pmd(pmd, __pmd((अचिन्हित दीर्घ)pte));
पूर्ण

अटल अंतरभूत व्योम pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
				pgtable_t pte)
अणु
	set_pmd(pmd, __pmd((अचिन्हित दीर्घ)page_address(pte)));
पूर्ण
#घोषणा pmd_pgtable(pmd) pmd_page(pmd)

#घोषणा __pte_मुक्त_tlb(tlb,pte,addr)			\
करो अणु							\
	pgtable_pte_page_dtor(pte);			\
	tlb_हटाओ_page((tlb), (pte));			\
पूर्ण जबतक (0)

#पूर्ण_अगर /* __ASM_SH_PGALLOC_H */
