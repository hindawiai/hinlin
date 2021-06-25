<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/tlb.h
 *
 * Copyright (C) 2002 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_TLB_H
#घोषणा __ASM_TLB_H

#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>

अटल अंतरभूत व्योम __tlb_हटाओ_table(व्योम *_table)
अणु
	मुक्त_page_and_swap_cache((काष्ठा page *)_table);
पूर्ण

#घोषणा tlb_flush tlb_flush
अटल व्योम tlb_flush(काष्ठा mmu_gather *tlb);

#समावेश <यंत्र-generic/tlb.h>

/*
 * get the tlbi levels in arm64.  Default value is 0 अगर more than one
 * of cleared_* is set or neither is set.
 * Arm64 करोesn't support p4ds now.
 */
अटल अंतरभूत पूर्णांक tlb_get_level(काष्ठा mmu_gather *tlb)
अणु
	अगर (tlb->cleared_ptes && !(tlb->cleared_pmds ||
				   tlb->cleared_puds ||
				   tlb->cleared_p4ds))
		वापस 3;

	अगर (tlb->cleared_pmds && !(tlb->cleared_ptes ||
				   tlb->cleared_puds ||
				   tlb->cleared_p4ds))
		वापस 2;

	अगर (tlb->cleared_puds && !(tlb->cleared_ptes ||
				   tlb->cleared_pmds ||
				   tlb->cleared_p4ds))
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम tlb_flush(काष्ठा mmu_gather *tlb)
अणु
	काष्ठा vm_area_काष्ठा vma = TLB_FLUSH_VMA(tlb->mm, 0);
	bool last_level = !tlb->मुक्तd_tables;
	अचिन्हित दीर्घ stride = tlb_get_unmap_size(tlb);
	पूर्णांक tlb_level = tlb_get_level(tlb);

	/*
	 * If we're tearing करोwn the address space then we only care about
	 * invalidating the walk-cache, since the ASID allocator won't
	 * पुनः_स्मृतिate our ASID without invalidating the entire TLB.
	 */
	अगर (tlb->fullmm) अणु
		अगर (!last_level)
			flush_tlb_mm(tlb->mm);
		वापस;
	पूर्ण

	__flush_tlb_range(&vma, tlb->start, tlb->end, stride,
			  last_level, tlb_level);
पूर्ण

अटल अंतरभूत व्योम __pte_मुक्त_tlb(काष्ठा mmu_gather *tlb, pgtable_t pte,
				  अचिन्हित दीर्घ addr)
अणु
	pgtable_pte_page_dtor(pte);
	tlb_हटाओ_table(tlb, pte);
पूर्ण

#अगर CONFIG_PGTABLE_LEVELS > 2
अटल अंतरभूत व्योम __pmd_मुक्त_tlb(काष्ठा mmu_gather *tlb, pmd_t *pmdp,
				  अचिन्हित दीर्घ addr)
अणु
	काष्ठा page *page = virt_to_page(pmdp);

	pgtable_pmd_page_dtor(page);
	tlb_हटाओ_table(tlb, page);
पूर्ण
#पूर्ण_अगर

#अगर CONFIG_PGTABLE_LEVELS > 3
अटल अंतरभूत व्योम __pud_मुक्त_tlb(काष्ठा mmu_gather *tlb, pud_t *pudp,
				  अचिन्हित दीर्घ addr)
अणु
	tlb_हटाओ_table(tlb, virt_to_page(pudp));
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
