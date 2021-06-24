<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_PGALLOC_H
#घोषणा _ASM_IA64_PGALLOC_H

/*
 * This file contains the functions and defines necessary to allocate
 * page tables.
 *
 * This hopefully works with any (fixed) ia-64 page-size, as defined
 * in <यंत्र/page.h> (currently 8192).
 *
 * Copyright (C) 1998-2001 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 2000, Goutham Rao <goutham.rao@पूर्णांकel.com>
 */


#समावेश <linux/compiler.h>
#समावेश <linux/mm.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/thपढ़ोs.h>

#समावेश <यंत्र-generic/pgभाग.स>

#समावेश <यंत्र/mmu_context.h>

अटल अंतरभूत pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	वापस (pgd_t *)__get_मुक्त_page(GFP_KERNEL | __GFP_ZERO);
पूर्ण

#अगर CONFIG_PGTABLE_LEVELS == 4
अटल अंतरभूत व्योम
p4d_populate(काष्ठा mm_काष्ठा *mm, p4d_t * p4d_entry, pud_t * pud)
अणु
	p4d_val(*p4d_entry) = __pa(pud);
पूर्ण

#घोषणा __pud_मुक्त_tlb(tlb, pud, address)	pud_मुक्त((tlb)->mm, pud)
#पूर्ण_अगर /* CONFIG_PGTABLE_LEVELS == 4 */

अटल अंतरभूत व्योम
pud_populate(काष्ठा mm_काष्ठा *mm, pud_t * pud_entry, pmd_t * pmd)
अणु
	pud_val(*pud_entry) = __pa(pmd);
पूर्ण

#घोषणा __pmd_मुक्त_tlb(tlb, pmd, address)	pmd_मुक्त((tlb)->mm, pmd)

अटल अंतरभूत व्योम
pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t * pmd_entry, pgtable_t pte)
अणु
	pmd_val(*pmd_entry) = page_to_phys(pte);
पूर्ण
#घोषणा pmd_pgtable(pmd) pmd_page(pmd)

अटल अंतरभूत व्योम
pmd_populate_kernel(काष्ठा mm_काष्ठा *mm, pmd_t * pmd_entry, pte_t * pte)
अणु
	pmd_val(*pmd_entry) = __pa(pte);
पूर्ण

#घोषणा __pte_मुक्त_tlb(tlb, pte, address)	pte_मुक्त((tlb)->mm, pte)

#पूर्ण_अगर				/* _ASM_IA64_PGALLOC_H */
