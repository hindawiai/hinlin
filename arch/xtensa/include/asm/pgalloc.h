<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/यंत्र-xtensa/pgभाग.स
 *
 * Copyright (C) 2001-2007 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_PGALLOC_H
#घोषणा _XTENSA_PGALLOC_H

#अगर_घोषित CONFIG_MMU
#समावेश <linux/highस्मृति.स>
#समावेश <linux/slab.h>

#घोषणा __HAVE_ARCH_PTE_ALLOC_ONE_KERNEL
#घोषणा __HAVE_ARCH_PTE_ALLOC_ONE
#समावेश <यंत्र-generic/pgभाग.स>

/*
 * Allocating and मुक्तing a pmd is trivial: the 1-entry pmd is
 * inside the pgd, so has no extra memory associated with it.
 */

#घोषणा pmd_populate_kernel(mm, pmdp, ptep)				     \
	(pmd_val(*(pmdp)) = ((अचिन्हित दीर्घ)ptep))
#घोषणा pmd_populate(mm, pmdp, page)					     \
	(pmd_val(*(pmdp)) = ((अचिन्हित दीर्घ)page_to_virt(page)))
#घोषणा pmd_pgtable(pmd) pmd_page(pmd)

अटल अंतरभूत pgd_t*
pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	वापस (pgd_t*) __get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO, PGD_ORDER);
पूर्ण

अटल अंतरभूत व्योम ptes_clear(pte_t *ptep)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PTE; i++)
		pte_clear(शून्य, 0, ptep + i);
पूर्ण

अटल अंतरभूत pte_t *pte_alloc_one_kernel(काष्ठा mm_काष्ठा *mm)
अणु
	pte_t *ptep;

	ptep = (pte_t *)__pte_alloc_one_kernel(mm);
	अगर (!ptep)
		वापस शून्य;
	ptes_clear(ptep);
	वापस ptep;
पूर्ण

अटल अंतरभूत pgtable_t pte_alloc_one(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा page *page;

	page = __pte_alloc_one(mm, GFP_PGTABLE_USER);
	अगर (!page)
		वापस शून्य;
	ptes_clear(page_address(page));
	वापस page;
पूर्ण

#घोषणा pmd_pgtable(pmd) pmd_page(pmd)
#पूर्ण_अगर /* CONFIG_MMU */

#पूर्ण_अगर /* _XTENSA_PGALLOC_H */
