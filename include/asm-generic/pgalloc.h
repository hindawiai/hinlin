<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_PGALLOC_H
#घोषणा __ASM_GENERIC_PGALLOC_H

#अगर_घोषित CONFIG_MMU

#घोषणा GFP_PGTABLE_KERNEL	(GFP_KERNEL | __GFP_ZERO)
#घोषणा GFP_PGTABLE_USER	(GFP_PGTABLE_KERNEL | __GFP_ACCOUNT)

/**
 * __pte_alloc_one_kernel - allocate a page क्रम PTE-level kernel page table
 * @mm: the mm_काष्ठा of the current context
 *
 * This function is पूर्णांकended क्रम architectures that need
 * anything beyond simple page allocation.
 *
 * Return: poपूर्णांकer to the allocated memory or %शून्य on error
 */
अटल अंतरभूत pte_t *__pte_alloc_one_kernel(काष्ठा mm_काष्ठा *mm)
अणु
	वापस (pte_t *)__get_मुक्त_page(GFP_PGTABLE_KERNEL);
पूर्ण

#अगर_अघोषित __HAVE_ARCH_PTE_ALLOC_ONE_KERNEL
/**
 * pte_alloc_one_kernel - allocate a page क्रम PTE-level kernel page table
 * @mm: the mm_काष्ठा of the current context
 *
 * Return: poपूर्णांकer to the allocated memory or %शून्य on error
 */
अटल अंतरभूत pte_t *pte_alloc_one_kernel(काष्ठा mm_काष्ठा *mm)
अणु
	वापस __pte_alloc_one_kernel(mm);
पूर्ण
#पूर्ण_अगर

/**
 * pte_मुक्त_kernel - मुक्त PTE-level kernel page table page
 * @mm: the mm_काष्ठा of the current context
 * @pte: poपूर्णांकer to the memory containing the page table
 */
अटल अंतरभूत व्योम pte_मुक्त_kernel(काष्ठा mm_काष्ठा *mm, pte_t *pte)
अणु
	मुक्त_page((अचिन्हित दीर्घ)pte);
पूर्ण

/**
 * __pte_alloc_one - allocate a page क्रम PTE-level user page table
 * @mm: the mm_काष्ठा of the current context
 * @gfp: GFP flags to use क्रम the allocation
 *
 * Allocates a page and runs the pgtable_pte_page_ctor().
 *
 * This function is पूर्णांकended क्रम architectures that need
 * anything beyond simple page allocation or must have custom GFP flags.
 *
 * Return: `काष्ठा page` initialized as page table or %शून्य on error
 */
अटल अंतरभूत pgtable_t __pte_alloc_one(काष्ठा mm_काष्ठा *mm, gfp_t gfp)
अणु
	काष्ठा page *pte;

	pte = alloc_page(gfp);
	अगर (!pte)
		वापस शून्य;
	अगर (!pgtable_pte_page_ctor(pte)) अणु
		__मुक्त_page(pte);
		वापस शून्य;
	पूर्ण

	वापस pte;
पूर्ण

#अगर_अघोषित __HAVE_ARCH_PTE_ALLOC_ONE
/**
 * pte_alloc_one - allocate a page क्रम PTE-level user page table
 * @mm: the mm_काष्ठा of the current context
 *
 * Allocates a page and runs the pgtable_pte_page_ctor().
 *
 * Return: `काष्ठा page` initialized as page table or %शून्य on error
 */
अटल अंतरभूत pgtable_t pte_alloc_one(काष्ठा mm_काष्ठा *mm)
अणु
	वापस __pte_alloc_one(mm, GFP_PGTABLE_USER);
पूर्ण
#पूर्ण_अगर

/*
 * Should really implement gc क्रम मुक्त page table pages. This could be
 * करोne with a reference count in काष्ठा page.
 */

/**
 * pte_मुक्त - मुक्त PTE-level user page table page
 * @mm: the mm_काष्ठा of the current context
 * @pte_page: the `काष्ठा page` representing the page table
 */
अटल अंतरभूत व्योम pte_मुक्त(काष्ठा mm_काष्ठा *mm, काष्ठा page *pte_page)
अणु
	pgtable_pte_page_dtor(pte_page);
	__मुक्त_page(pte_page);
पूर्ण


#अगर CONFIG_PGTABLE_LEVELS > 2

#अगर_अघोषित __HAVE_ARCH_PMD_ALLOC_ONE
/**
 * pmd_alloc_one - allocate a page क्रम PMD-level page table
 * @mm: the mm_काष्ठा of the current context
 *
 * Allocates a page and runs the pgtable_pmd_page_ctor().
 * Allocations use %GFP_PGTABLE_USER in user context and
 * %GFP_PGTABLE_KERNEL in kernel context.
 *
 * Return: poपूर्णांकer to the allocated memory or %शून्य on error
 */
अटल अंतरभूत pmd_t *pmd_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	काष्ठा page *page;
	gfp_t gfp = GFP_PGTABLE_USER;

	अगर (mm == &init_mm)
		gfp = GFP_PGTABLE_KERNEL;
	page = alloc_pages(gfp, 0);
	अगर (!page)
		वापस शून्य;
	अगर (!pgtable_pmd_page_ctor(page)) अणु
		__मुक्त_pages(page, 0);
		वापस शून्य;
	पूर्ण
	वापस (pmd_t *)page_address(page);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PMD_FREE
अटल अंतरभूत व्योम pmd_मुक्त(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
	BUG_ON((अचिन्हित दीर्घ)pmd & (PAGE_SIZE-1));
	pgtable_pmd_page_dtor(virt_to_page(pmd));
	मुक्त_page((अचिन्हित दीर्घ)pmd);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_PGTABLE_LEVELS > 2 */

#अगर CONFIG_PGTABLE_LEVELS > 3

#अगर_अघोषित __HAVE_ARCH_PUD_ALLOC_ONE
/**
 * pud_alloc_one - allocate a page क्रम PUD-level page table
 * @mm: the mm_काष्ठा of the current context
 *
 * Allocates a page using %GFP_PGTABLE_USER क्रम user context and
 * %GFP_PGTABLE_KERNEL क्रम kernel context.
 *
 * Return: poपूर्णांकer to the allocated memory or %शून्य on error
 */
अटल अंतरभूत pud_t *pud_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	gfp_t gfp = GFP_PGTABLE_USER;

	अगर (mm == &init_mm)
		gfp = GFP_PGTABLE_KERNEL;
	वापस (pud_t *)get_zeroed_page(gfp);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम pud_मुक्त(काष्ठा mm_काष्ठा *mm, pud_t *pud)
अणु
	BUG_ON((अचिन्हित दीर्घ)pud & (PAGE_SIZE-1));
	मुक्त_page((अचिन्हित दीर्घ)pud);
पूर्ण

#पूर्ण_अगर /* CONFIG_PGTABLE_LEVELS > 3 */

#अगर_अघोषित __HAVE_ARCH_PGD_FREE
अटल अंतरभूत व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	मुक्त_page((अचिन्हित दीर्घ)pgd);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_MMU */

#पूर्ण_अगर /* __ASM_GENERIC_PGALLOC_H */
