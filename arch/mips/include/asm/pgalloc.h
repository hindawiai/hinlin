<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994 - 2001, 2003 by Ralf Baechle
 * Copyright (C) 1999, 2000, 2001 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_PGALLOC_H
#घोषणा _ASM_PGALLOC_H

#समावेश <linux/highस्मृति.स>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>

#घोषणा __HAVE_ARCH_PMD_ALLOC_ONE
#घोषणा __HAVE_ARCH_PUD_ALLOC_ONE
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

#अगर_अघोषित __PAGETABLE_PMD_FOLDED

अटल अंतरभूत व्योम pud_populate(काष्ठा mm_काष्ठा *mm, pud_t *pud, pmd_t *pmd)
अणु
	set_pud(pud, __pud((अचिन्हित दीर्घ)pmd));
पूर्ण
#पूर्ण_अगर

/*
 * Initialize a new pgd / pmd table with invalid poपूर्णांकers.
 */
बाह्य व्योम pgd_init(अचिन्हित दीर्घ page);
बाह्य pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm);

#घोषणा __pte_मुक्त_tlb(tlb,pte,address)			\
करो अणु							\
	pgtable_pte_page_dtor(pte);			\
	tlb_हटाओ_page((tlb), pte);			\
पूर्ण जबतक (0)

#अगर_अघोषित __PAGETABLE_PMD_FOLDED

अटल अंतरभूत pmd_t *pmd_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address)
अणु
	pmd_t *pmd;

	pmd = (pmd_t *) __get_मुक्त_pages(GFP_KERNEL, PMD_ORDER);
	अगर (pmd)
		pmd_init((अचिन्हित दीर्घ)pmd, (अचिन्हित दीर्घ)invalid_pte_table);
	वापस pmd;
पूर्ण

#घोषणा __pmd_मुक्त_tlb(tlb, x, addr)	pmd_मुक्त((tlb)->mm, x)

#पूर्ण_अगर

#अगर_अघोषित __PAGETABLE_PUD_FOLDED

अटल अंतरभूत pud_t *pud_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address)
अणु
	pud_t *pud;

	pud = (pud_t *) __get_मुक्त_pages(GFP_KERNEL, PUD_ORDER);
	अगर (pud)
		pud_init((अचिन्हित दीर्घ)pud, (अचिन्हित दीर्घ)invalid_pmd_table);
	वापस pud;
पूर्ण

अटल अंतरभूत व्योम p4d_populate(काष्ठा mm_काष्ठा *mm, p4d_t *p4d, pud_t *pud)
अणु
	set_p4d(p4d, __p4d((अचिन्हित दीर्घ)pud));
पूर्ण

#घोषणा __pud_मुक्त_tlb(tlb, x, addr)	pud_मुक्त((tlb)->mm, x)

#पूर्ण_अगर /* __PAGETABLE_PUD_FOLDED */

बाह्य व्योम pagetable_init(व्योम);

#पूर्ण_अगर /* _ASM_PGALLOC_H */
