<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* sun3_pgभाग.स --
 * reorganization around 2.3.39, routines moved from sun3_pgtable.h
 *
 *
 * 02/27/2002 -- Modअगरied to support "highpte" implementation in 2.5.5 (Sam)
 *
 * moved 1/26/2000 Sam Creasey
 */

#अगर_अघोषित _SUN3_PGALLOC_H
#घोषणा _SUN3_PGALLOC_H

#समावेश <यंत्र/tlb.h>

#समावेश <यंत्र-generic/pgभाग.स>

बाह्य स्थिर अक्षर bad_pmd_string[];

#घोषणा __pte_मुक्त_tlb(tlb,pte,addr)			\
करो अणु							\
	pgtable_pte_page_dtor(pte);			\
	tlb_हटाओ_page((tlb), pte);			\
पूर्ण जबतक (0)

अटल अंतरभूत व्योम pmd_populate_kernel(काष्ठा mm_काष्ठा *mm, pmd_t *pmd, pte_t *pte)
अणु
	pmd_val(*pmd) = __pa((अचिन्हित दीर्घ)pte);
पूर्ण

अटल अंतरभूत व्योम pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t *pmd, pgtable_t page)
अणु
	pmd_val(*pmd) = __pa((अचिन्हित दीर्घ)page_address(page));
पूर्ण
#घोषणा pmd_pgtable(pmd) pmd_page(pmd)

/*
 * allocating and मुक्तing a pmd is trivial: the 1-entry pmd is
 * inside the pgd, so has no extra memory associated with it.
 */
#घोषणा pmd_मुक्त(mm, x)			करो अणु पूर्ण जबतक (0)

अटल अंतरभूत pgd_t * pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
     pgd_t *new_pgd;

     new_pgd = (pgd_t *)get_zeroed_page(GFP_KERNEL);
     स_नकल(new_pgd, swapper_pg_dir, PAGE_SIZE);
     स_रखो(new_pgd, 0, (PAGE_OFFSET >> PGसूची_SHIFT));
     वापस new_pgd;
पूर्ण

#पूर्ण_अगर /* SUN3_PGALLOC_H */
