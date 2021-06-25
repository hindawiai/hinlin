<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2009 Chen Liqin <liqin.chen@sunplusct.com>
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_PGALLOC_H
#घोषणा _ASM_RISCV_PGALLOC_H

#समावेश <linux/mm.h>
#समावेश <यंत्र/tlb.h>

#अगर_घोषित CONFIG_MMU
#समावेश <यंत्र-generic/pgभाग.स>

अटल अंतरभूत व्योम pmd_populate_kernel(काष्ठा mm_काष्ठा *mm,
	pmd_t *pmd, pte_t *pte)
अणु
	अचिन्हित दीर्घ pfn = virt_to_pfn(pte);

	set_pmd(pmd, __pmd((pfn << _PAGE_PFN_SHIFT) | _PAGE_TABLE));
पूर्ण

अटल अंतरभूत व्योम pmd_populate(काष्ठा mm_काष्ठा *mm,
	pmd_t *pmd, pgtable_t pte)
अणु
	अचिन्हित दीर्घ pfn = virt_to_pfn(page_address(pte));

	set_pmd(pmd, __pmd((pfn << _PAGE_PFN_SHIFT) | _PAGE_TABLE));
पूर्ण

#अगर_अघोषित __PAGETABLE_PMD_FOLDED
अटल अंतरभूत व्योम pud_populate(काष्ठा mm_काष्ठा *mm, pud_t *pud, pmd_t *pmd)
अणु
	अचिन्हित दीर्घ pfn = virt_to_pfn(pmd);

	set_pud(pud, __pud((pfn << _PAGE_PFN_SHIFT) | _PAGE_TABLE));
पूर्ण
#पूर्ण_अगर /* __PAGETABLE_PMD_FOLDED */

#घोषणा pmd_pgtable(pmd)	pmd_page(pmd)

अटल अंतरभूत pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *pgd;

	pgd = (pgd_t *)__get_मुक्त_page(GFP_KERNEL);
	अगर (likely(pgd != शून्य)) अणु
		स_रखो(pgd, 0, USER_PTRS_PER_PGD * माप(pgd_t));
		/* Copy kernel mappings */
		स_नकल(pgd + USER_PTRS_PER_PGD,
			init_mm.pgd + USER_PTRS_PER_PGD,
			(PTRS_PER_PGD - USER_PTRS_PER_PGD) * माप(pgd_t));
	पूर्ण
	वापस pgd;
पूर्ण

#अगर_अघोषित __PAGETABLE_PMD_FOLDED

#घोषणा __pmd_मुक्त_tlb(tlb, pmd, addr)  pmd_मुक्त((tlb)->mm, pmd)

#पूर्ण_अगर /* __PAGETABLE_PMD_FOLDED */

#घोषणा __pte_मुक्त_tlb(tlb, pte, buf)   \
करो अणु                                    \
	pgtable_pte_page_dtor(pte);     \
	tlb_हटाओ_page((tlb), pte);    \
पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_MMU */

#पूर्ण_अगर /* _ASM_RISCV_PGALLOC_H */
