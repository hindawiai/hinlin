<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PGALLOC_H
#घोषणा _ASM_PGALLOC_H

#समावेश <linux/gfp.h>
#समावेश <linux/mm.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/fixmap.h>

#समावेश <यंत्र/cache.h>

#घोषणा __HAVE_ARCH_PMD_ALLOC_ONE
#घोषणा __HAVE_ARCH_PMD_FREE
#घोषणा __HAVE_ARCH_PGD_FREE
#समावेश <यंत्र-generic/pgभाग.स>

/* Allocate the top level pgd (page directory) */
अटल अंतरभूत pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *pgd;

	pgd = (pgd_t *) __get_मुक्त_pages(GFP_KERNEL, PGD_ORDER);
	अगर (unlikely(pgd == शून्य))
		वापस शून्य;

	स_रखो(pgd, 0, PAGE_SIZE << PGD_ORDER);

	वापस pgd;
पूर्ण

अटल अंतरभूत व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	मुक्त_pages((अचिन्हित दीर्घ)pgd, PGD_ORDER);
पूर्ण

#अगर CONFIG_PGTABLE_LEVELS == 3

/* Three Level Page Table Support क्रम pmd's */

अटल अंतरभूत व्योम pud_populate(काष्ठा mm_काष्ठा *mm, pud_t *pud, pmd_t *pmd)
अणु
	set_pud(pud, __pud((PxD_FLAG_PRESENT | PxD_FLAG_VALID) +
			(__u32)(__pa((अचिन्हित दीर्घ)pmd) >> PxD_VALUE_SHIFT)));
पूर्ण

अटल अंतरभूत pmd_t *pmd_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address)
अणु
	pmd_t *pmd;

	pmd = (pmd_t *)__get_मुक्त_pages(GFP_PGTABLE_KERNEL, PMD_ORDER);
	अगर (likely(pmd))
		स_रखो ((व्योम *)pmd, 0, PAGE_SIZE << PMD_ORDER);
	वापस pmd;
पूर्ण

अटल अंतरभूत व्योम pmd_मुक्त(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
	मुक्त_pages((अचिन्हित दीर्घ)pmd, PMD_ORDER);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम
pmd_populate_kernel(काष्ठा mm_काष्ठा *mm, pmd_t *pmd, pte_t *pte)
अणु
	set_pmd(pmd, __pmd((PxD_FLAG_PRESENT | PxD_FLAG_VALID)
		+ (__u32)(__pa((अचिन्हित दीर्घ)pte) >> PxD_VALUE_SHIFT)));
पूर्ण

#घोषणा pmd_populate(mm, pmd, pte_page) \
	pmd_populate_kernel(mm, pmd, page_address(pte_page))
#घोषणा pmd_pgtable(pmd) pmd_page(pmd)

#पूर्ण_अगर
