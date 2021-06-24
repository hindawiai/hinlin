<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित M68K_MCF_PGALLOC_H
#घोषणा M68K_MCF_PGALLOC_H

#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>

बाह्य अंतरभूत व्योम pte_मुक्त_kernel(काष्ठा mm_काष्ठा *mm, pte_t *pte)
अणु
	मुक्त_page((अचिन्हित दीर्घ) pte);
पूर्ण

बाह्य स्थिर अक्षर bad_pmd_string[];

बाह्य अंतरभूत pte_t *pte_alloc_one_kernel(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ page = __get_मुक्त_page(GFP_DMA);

	अगर (!page)
		वापस शून्य;

	स_रखो((व्योम *)page, 0, PAGE_SIZE);
	वापस (pte_t *) (page);
पूर्ण

बाह्य अंतरभूत pmd_t *pmd_alloc_kernel(pgd_t *pgd, अचिन्हित दीर्घ address)
अणु
	वापस (pmd_t *) pgd;
पूर्ण

#घोषणा pmd_populate(mm, pmd, pte) (pmd_val(*pmd) = (अचिन्हित दीर्घ)(pte))

#घोषणा pmd_populate_kernel pmd_populate

#घोषणा pmd_pgtable(pmd) pfn_to_virt(pmd_val(pmd) >> PAGE_SHIFT)

अटल अंतरभूत व्योम __pte_मुक्त_tlb(काष्ठा mmu_gather *tlb, pgtable_t pgtable,
				  अचिन्हित दीर्घ address)
अणु
	काष्ठा page *page = virt_to_page(pgtable);

	pgtable_pte_page_dtor(page);
	__मुक्त_page(page);
पूर्ण

अटल अंतरभूत pgtable_t pte_alloc_one(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा page *page = alloc_pages(GFP_DMA, 0);
	pte_t *pte;

	अगर (!page)
		वापस शून्य;
	अगर (!pgtable_pte_page_ctor(page)) अणु
		__मुक्त_page(page);
		वापस शून्य;
	पूर्ण

	pte = page_address(page);
	clear_page(pte);

	वापस pte;
पूर्ण

अटल अंतरभूत व्योम pte_मुक्त(काष्ठा mm_काष्ठा *mm, pgtable_t pgtable)
अणु
	काष्ठा page *page = virt_to_page(pgtable);

	pgtable_pte_page_dtor(page);
	__मुक्त_page(page);
पूर्ण

/*
 * In our implementation, each pgd entry contains 1 pmd that is never allocated
 * or मुक्तd.  pgd_present is always 1, so this should never be called. -NL
 */
#घोषणा pmd_मुक्त(mm, pmd) BUG()

अटल अंतरभूत व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	मुक्त_page((अचिन्हित दीर्घ) pgd);
पूर्ण

अटल अंतरभूत pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *new_pgd;

	new_pgd = (pgd_t *)__get_मुक्त_page(GFP_DMA | __GFP_NOWARN);
	अगर (!new_pgd)
		वापस शून्य;
	स_नकल(new_pgd, swapper_pg_dir, PTRS_PER_PGD * माप(pgd_t));
	स_रखो(new_pgd, 0, PAGE_OFFSET >> PGसूची_SHIFT);
	वापस new_pgd;
पूर्ण

#पूर्ण_अगर /* M68K_MCF_PGALLOC_H */
