<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994 - 2001, 2003 by Ralf Baechle
 * Copyright (C) 1999, 2000, 2001 Silicon Graphics, Inc.
 */

#अगर_अघोषित _ASM_NIOS2_PGALLOC_H
#घोषणा _ASM_NIOS2_PGALLOC_H

#समावेश <linux/mm.h>

#समावेश <यंत्र-generic/pgभाग.स>

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

/*
 * Initialize a new pmd table with invalid poपूर्णांकers.
 */
बाह्य व्योम pmd_init(अचिन्हित दीर्घ page, अचिन्हित दीर्घ pagetable);

बाह्य pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm);

#घोषणा __pte_मुक्त_tlb(tlb, pte, addr)				\
	करो अणु							\
		pgtable_pte_page_dtor(pte);			\
		tlb_हटाओ_page((tlb), (pte));			\
	पूर्ण जबतक (0)

#पूर्ण_अगर /* _ASM_NIOS2_PGALLOC_H */
