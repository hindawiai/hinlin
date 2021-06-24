<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_HUGETLB_H
#घोषणा _ASM_POWERPC_HUGETLB_H

#अगर_घोषित CONFIG_HUGETLB_PAGE
#समावेश <यंत्र/page.h>

#अगर_घोषित CONFIG_PPC_BOOK3S_64
#समावेश <यंत्र/book3s/64/hugetlb.h>
#या_अगर defined(CONFIG_PPC_FSL_BOOK3E)
#समावेश <यंत्र/nohash/hugetlb-book3e.h>
#या_अगर defined(CONFIG_PPC_8xx)
#समावेश <यंत्र/nohash/32/hugetlb-8xx.h>
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */

बाह्य bool hugetlb_disabled;

व्योम hugetlbpage_init_शेष(व्योम);

पूर्णांक slice_is_hugepage_only_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			   अचिन्हित दीर्घ len);

अटल अंतरभूत पूर्णांक is_hugepage_only_range(काष्ठा mm_काष्ठा *mm,
					 अचिन्हित दीर्घ addr,
					 अचिन्हित दीर्घ len)
अणु
	अगर (IS_ENABLED(CONFIG_PPC_MM_SLICES) && !radix_enabled())
		वापस slice_is_hugepage_only_range(mm, addr, len);
	वापस 0;
पूर्ण
#घोषणा is_hugepage_only_range is_hugepage_only_range

#घोषणा __HAVE_ARCH_HUGETLB_FREE_PGD_RANGE
व्योम hugetlb_मुक्त_pgd_range(काष्ठा mmu_gather *tlb, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ end, अचिन्हित दीर्घ न्यूनमान,
			    अचिन्हित दीर्घ उच्चमानing);

#घोषणा __HAVE_ARCH_HUGE_PTEP_GET_AND_CLEAR
अटल अंतरभूत pte_t huge_ptep_get_and_clear(काष्ठा mm_काष्ठा *mm,
					    अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	वापस __pte(pte_update(mm, addr, ptep, ~0UL, 0, 1));
पूर्ण

#घोषणा __HAVE_ARCH_HUGE_PTEP_CLEAR_FLUSH
अटल अंतरभूत व्योम huge_ptep_clear_flush(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	huge_ptep_get_and_clear(vma->vm_mm, addr, ptep);
	flush_hugetlb_page(vma, addr);
पूर्ण

#घोषणा __HAVE_ARCH_HUGE_PTEP_SET_ACCESS_FLAGS
पूर्णांक huge_ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
			       अचिन्हित दीर्घ addr, pte_t *ptep,
			       pte_t pte, पूर्णांक dirty);

व्योम gigantic_hugetlb_cma_reserve(व्योम) __init;
#समावेश <यंत्र-generic/hugetlb.h>

#अन्यथा /* ! CONFIG_HUGETLB_PAGE */
अटल अंतरभूत व्योम flush_hugetlb_page(काष्ठा vm_area_काष्ठा *vma,
				      अचिन्हित दीर्घ vmaddr)
अणु
पूर्ण

#घोषणा hugepd_shअगरt(x) 0
अटल अंतरभूत pte_t *hugepte_offset(hugepd_t hpd, अचिन्हित दीर्घ addr,
				    अचिन्हित pdshअगरt)
अणु
	वापस शून्य;
पूर्ण


अटल अंतरभूत व्योम __init gigantic_hugetlb_cma_reserve(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */

#पूर्ण_अगर /* _ASM_POWERPC_HUGETLB_H */
