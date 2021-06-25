<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_PGALLOC_H
#घोषणा _ALPHA_PGALLOC_H

#समावेश <linux/mm.h>
#समावेश <linux/mmzone.h>

#समावेश <यंत्र-generic/pgभाग.स>

/*      
 * Allocate and मुक्त page tables. The xxx_kernel() versions are
 * used to allocate a kernel page table - this turns on ASN bits
 * अगर any.
 */

अटल अंतरभूत व्योम
pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t *pmd, pgtable_t pte)
अणु
	pmd_set(pmd, (pte_t *)(page_to_pa(pte) + PAGE_OFFSET));
पूर्ण
#घोषणा pmd_pgtable(pmd) pmd_page(pmd)

अटल अंतरभूत व्योम
pmd_populate_kernel(काष्ठा mm_काष्ठा *mm, pmd_t *pmd, pte_t *pte)
अणु
	pmd_set(pmd, pte);
पूर्ण

अटल अंतरभूत व्योम
pud_populate(काष्ठा mm_काष्ठा *mm, pud_t *pud, pmd_t *pmd)
अणु
	pud_set(pud, pmd);
पूर्ण

बाह्य pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm);

#पूर्ण_अगर /* _ALPHA_PGALLOC_H */
