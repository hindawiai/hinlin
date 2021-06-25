<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/tlb.h
 *
 *  Copyright (C) 2002 Russell King
 *
 *  Experimentation shows that on a StrongARM, it appears to be faster
 *  to use the "invalidate whole tlb" rather than "invalidate single
 *  tlb" क्रम this.
 *
 *  This appears true क्रम both the process विभाजन+निकास हाल, as well as
 *  the munmap-large-area हाल.
 */
#अगर_अघोषित __ASMARM_TLB_H
#घोषणा __ASMARM_TLB_H

#समावेश <यंत्र/cacheflush.h>

#अगर_अघोषित CONFIG_MMU

#समावेश <linux/pagemap.h>

#घोषणा tlb_flush(tlb)	((व्योम) tlb)

#समावेश <यंत्र-generic/tlb.h>

#अन्यथा /* !CONFIG_MMU */

#समावेश <linux/swap.h>
#समावेश <यंत्र/tlbflush.h>

अटल अंतरभूत व्योम __tlb_हटाओ_table(व्योम *_table)
अणु
	मुक्त_page_and_swap_cache((काष्ठा page *)_table);
पूर्ण

#समावेश <यंत्र-generic/tlb.h>

अटल अंतरभूत व्योम
__pte_मुक्त_tlb(काष्ठा mmu_gather *tlb, pgtable_t pte, अचिन्हित दीर्घ addr)
अणु
	pgtable_pte_page_dtor(pte);

#अगर_अघोषित CONFIG_ARM_LPAE
	/*
	 * With the classic ARM MMU, a pte page has two corresponding pmd
	 * entries, each covering 1MB.
	 */
	addr = (addr & PMD_MASK) + SZ_1M;
	__tlb_adjust_range(tlb, addr - PAGE_SIZE, 2 * PAGE_SIZE);
#पूर्ण_अगर

	tlb_हटाओ_table(tlb, pte);
पूर्ण

अटल अंतरभूत व्योम
__pmd_मुक्त_tlb(काष्ठा mmu_gather *tlb, pmd_t *pmdp, अचिन्हित दीर्घ addr)
अणु
#अगर_घोषित CONFIG_ARM_LPAE
	काष्ठा page *page = virt_to_page(pmdp);

	pgtable_pmd_page_dtor(page);
	tlb_हटाओ_table(tlb, page);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* CONFIG_MMU */
#पूर्ण_अगर
