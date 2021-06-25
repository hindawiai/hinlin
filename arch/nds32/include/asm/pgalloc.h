<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित _ASMNDS32_PGALLOC_H
#घोषणा _ASMNDS32_PGALLOC_H

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/proc-fns.h>

#घोषणा __HAVE_ARCH_PTE_ALLOC_ONE
#समावेश <यंत्र-generic/pgभाग.स>	/* क्रम pte_अणुalloc,मुक्तपूर्ण_one */

/*
 * Since we have only two-level page tables, these are trivial
 */
#घोषणा pmd_pgtable(pmd) pmd_page(pmd)

बाह्य pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t * pgd);

अटल अंतरभूत pgtable_t pte_alloc_one(काष्ठा mm_काष्ठा *mm)
अणु
	pgtable_t pte;

	pte = __pte_alloc_one(mm, GFP_PGTABLE_USER);
	अगर (pte)
		cpu_dcache_wb_page((अचिन्हित दीर्घ)page_address(pte));

	वापस pte;
पूर्ण

/*
 * Populate the pmdp entry with a poपूर्णांकer to the pte.  This pmd is part
 * of the mm address space.
 *
 * Ensure that we always set both PMD entries.
 */
अटल अंतरभूत व्योम
pmd_populate_kernel(काष्ठा mm_काष्ठा *mm, pmd_t * pmdp, pte_t * ptep)
अणु
	अचिन्हित दीर्घ pte_ptr = (अचिन्हित दीर्घ)ptep;
	अचिन्हित दीर्घ pmdval;

	BUG_ON(mm != &init_mm);

	/*
	 * The pmd must be loaded with the physical
	 * address of the PTE table
	 */
	pmdval = __pa(pte_ptr) | _PAGE_KERNEL_TABLE;
	set_pmd(pmdp, __pmd(pmdval));
पूर्ण

अटल अंतरभूत व्योम
pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t * pmdp, pgtable_t ptep)
अणु
	अचिन्हित दीर्घ pmdval;

	BUG_ON(mm == &init_mm);

	pmdval = page_to_pfn(ptep) << PAGE_SHIFT | _PAGE_USER_TABLE;
	set_pmd(pmdp, __pmd(pmdval));
पूर्ण

#पूर्ण_अगर
