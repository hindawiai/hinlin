<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm64/include/यंत्र/hugetlb.h
 *
 * Copyright (C) 2013 Linaro Ltd.
 *
 * Based on arch/x86/include/यंत्र/hugetlb.h
 */

#अगर_अघोषित __ASM_HUGETLB_H
#घोषणा __ASM_HUGETLB_H

#समावेश <यंत्र/page.h>

#अगर_घोषित CONFIG_ARCH_ENABLE_HUGEPAGE_MIGRATION
#घोषणा arch_hugetlb_migration_supported arch_hugetlb_migration_supported
बाह्य bool arch_hugetlb_migration_supported(काष्ठा hstate *h);
#पूर्ण_अगर

अटल अंतरभूत व्योम arch_clear_hugepage_flags(काष्ठा page *page)
अणु
	clear_bit(PG_dcache_clean, &page->flags);
पूर्ण
#घोषणा arch_clear_hugepage_flags arch_clear_hugepage_flags

बाह्य pte_t arch_make_huge_pte(pte_t entry, काष्ठा vm_area_काष्ठा *vma,
				काष्ठा page *page, पूर्णांक writable);
#घोषणा arch_make_huge_pte arch_make_huge_pte
#घोषणा __HAVE_ARCH_HUGE_SET_HUGE_PTE_AT
बाह्य व्योम set_huge_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			    pte_t *ptep, pte_t pte);
#घोषणा __HAVE_ARCH_HUGE_PTEP_SET_ACCESS_FLAGS
बाह्य पूर्णांक huge_ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
				      अचिन्हित दीर्घ addr, pte_t *ptep,
				      pte_t pte, पूर्णांक dirty);
#घोषणा __HAVE_ARCH_HUGE_PTEP_GET_AND_CLEAR
बाह्य pte_t huge_ptep_get_and_clear(काष्ठा mm_काष्ठा *mm,
				     अचिन्हित दीर्घ addr, pte_t *ptep);
#घोषणा __HAVE_ARCH_HUGE_PTEP_SET_WRPROTECT
बाह्य व्योम huge_ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm,
				    अचिन्हित दीर्घ addr, pte_t *ptep);
#घोषणा __HAVE_ARCH_HUGE_PTEP_CLEAR_FLUSH
बाह्य व्योम huge_ptep_clear_flush(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ addr, pte_t *ptep);
#घोषणा __HAVE_ARCH_HUGE_PTE_CLEAR
बाह्य व्योम huge_pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			   pte_t *ptep, अचिन्हित दीर्घ sz);
बाह्य व्योम set_huge_swap_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				 pte_t *ptep, pte_t pte, अचिन्हित दीर्घ sz);
#घोषणा set_huge_swap_pte_at set_huge_swap_pte_at

व्योम __init arm64_hugetlb_cma_reserve(व्योम);

#समावेश <यंत्र-generic/hugetlb.h>

#पूर्ण_अगर /* __ASM_HUGETLB_H */
