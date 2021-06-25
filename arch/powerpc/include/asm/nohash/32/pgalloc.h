<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_PGALLOC_32_H
#घोषणा _ASM_POWERPC_PGALLOC_32_H

#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/slab.h>

/*
 * We करोn't have any real pmd's, and this code never triggers because
 * the pgd will always be present..
 */
/* #घोषणा pmd_alloc_one(mm,address)       (अणु BUG(); ((pmd_t *)2); पूर्ण) */
#घोषणा pmd_मुक्त(mm, x) 		करो अणु पूर्ण जबतक (0)
#घोषणा __pmd_मुक्त_tlb(tlb,x,a)		करो अणु पूर्ण जबतक (0)
/* #घोषणा pgd_populate(mm, pmd, pte)      BUG() */

अटल अंतरभूत व्योम pmd_populate_kernel(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
				       pte_t *pte)
अणु
	अगर (IS_ENABLED(CONFIG_BOOKE))
		*pmdp = __pmd((अचिन्हित दीर्घ)pte | _PMD_PRESENT);
	अन्यथा
		*pmdp = __pmd(__pa(pte) | _PMD_PRESENT);
पूर्ण

अटल अंतरभूत व्योम pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
				pgtable_t pte_page)
अणु
	अगर (IS_ENABLED(CONFIG_BOOKE))
		*pmdp = __pmd((अचिन्हित दीर्घ)pte_page | _PMD_PRESENT);
	अन्यथा
		*pmdp = __pmd(__pa(pte_page) | _PMD_USER | _PMD_PRESENT);
पूर्ण

#पूर्ण_अगर /* _ASM_POWERPC_PGALLOC_32_H */
