<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_PGALLOC_H
#घोषणा _ASM_MICROBLAZE_PGALLOC_H

#समावेश <linux/kernel.h>	/* For min/max macros */
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cache.h>

#घोषणा __HAVE_ARCH_PTE_ALLOC_ONE_KERNEL
#समावेश <यंत्र-generic/pgभाग.स>

बाह्य व्योम __bad_pte(pmd_t *pmd);

अटल अंतरभूत pgd_t *get_pgd(व्योम)
अणु
	वापस (pgd_t *)__get_मुक्त_pages(GFP_KERNEL|__GFP_ZERO, 0);
पूर्ण

#घोषणा pgd_alloc(mm)		get_pgd()

#घोषणा pmd_pgtable(pmd)	pmd_page(pmd)

बाह्य pte_t *pte_alloc_one_kernel(काष्ठा mm_काष्ठा *mm);

#घोषणा __pte_मुक्त_tlb(tlb, pte, addr)	pte_मुक्त((tlb)->mm, (pte))

#घोषणा pmd_populate(mm, pmd, pte) \
			(pmd_val(*(pmd)) = (अचिन्हित दीर्घ)page_address(pte))

#घोषणा pmd_populate_kernel(mm, pmd, pte) \
		(pmd_val(*(pmd)) = (अचिन्हित दीर्घ) (pte))

#पूर्ण_अगर /* _ASM_MICROBLAZE_PGALLOC_H */
