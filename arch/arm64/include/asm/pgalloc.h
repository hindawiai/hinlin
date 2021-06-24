<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/pgभाग.स
 *
 * Copyright (C) 2000-2001 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_PGALLOC_H
#घोषणा __ASM_PGALLOC_H

#समावेश <यंत्र/pgtable-hwdef.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>

#घोषणा __HAVE_ARCH_PGD_FREE
#समावेश <यंत्र-generic/pgभाग.स>

#घोषणा PGD_SIZE	(PTRS_PER_PGD * माप(pgd_t))

#अगर CONFIG_PGTABLE_LEVELS > 2

अटल अंतरभूत व्योम __pud_populate(pud_t *pudp, phys_addr_t pmdp, pudval_t prot)
अणु
	set_pud(pudp, __pud(__phys_to_pud_val(pmdp) | prot));
पूर्ण

अटल अंतरभूत व्योम pud_populate(काष्ठा mm_काष्ठा *mm, pud_t *pudp, pmd_t *pmdp)
अणु
	pudval_t pudval = PUD_TYPE_TABLE;

	pudval |= (mm == &init_mm) ? PUD_TABLE_UXN : PUD_TABLE_PXN;
	__pud_populate(pudp, __pa(pmdp), pudval);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम __pud_populate(pud_t *pudp, phys_addr_t pmdp, pudval_t prot)
अणु
	BUILD_BUG();
पूर्ण
#पूर्ण_अगर	/* CONFIG_PGTABLE_LEVELS > 2 */

#अगर CONFIG_PGTABLE_LEVELS > 3

अटल अंतरभूत व्योम __p4d_populate(p4d_t *p4dp, phys_addr_t pudp, p4dval_t prot)
अणु
	set_p4d(p4dp, __p4d(__phys_to_p4d_val(pudp) | prot));
पूर्ण

अटल अंतरभूत व्योम p4d_populate(काष्ठा mm_काष्ठा *mm, p4d_t *p4dp, pud_t *pudp)
अणु
	p4dval_t p4dval = P4D_TYPE_TABLE;

	p4dval |= (mm == &init_mm) ? P4D_TABLE_UXN : P4D_TABLE_PXN;
	__p4d_populate(p4dp, __pa(pudp), p4dval);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम __p4d_populate(p4d_t *p4dp, phys_addr_t pudp, p4dval_t prot)
अणु
	BUILD_BUG();
पूर्ण
#पूर्ण_अगर	/* CONFIG_PGTABLE_LEVELS > 3 */

बाह्य pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgdp);

अटल अंतरभूत व्योम __pmd_populate(pmd_t *pmdp, phys_addr_t ptep,
				  pmdval_t prot)
अणु
	set_pmd(pmdp, __pmd(__phys_to_pmd_val(ptep) | prot));
पूर्ण

/*
 * Populate the pmdp entry with a poपूर्णांकer to the pte.  This pmd is part
 * of the mm address space.
 */
अटल अंतरभूत व्योम
pmd_populate_kernel(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp, pte_t *ptep)
अणु
	VM_BUG_ON(mm != &init_mm);
	__pmd_populate(pmdp, __pa(ptep), PMD_TYPE_TABLE | PMD_TABLE_UXN);
पूर्ण

अटल अंतरभूत व्योम
pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp, pgtable_t ptep)
अणु
	VM_BUG_ON(mm == &init_mm);
	__pmd_populate(pmdp, page_to_phys(ptep), PMD_TYPE_TABLE | PMD_TABLE_PXN);
पूर्ण
#घोषणा pmd_pgtable(pmd) pmd_page(pmd)

#पूर्ण_अगर
