<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_SPARC64_HUGETLB_H
#घोषणा _ASM_SPARC64_HUGETLB_H

#समावेश <यंत्र/page.h>

#अगर_घोषित CONFIG_HUGETLB_PAGE
काष्ठा pud_huge_patch_entry अणु
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक insn;
पूर्ण;
बाह्य काष्ठा pud_huge_patch_entry __pud_huge_patch, __pud_huge_patch_end;
#पूर्ण_अगर

#घोषणा __HAVE_ARCH_HUGE_SET_HUGE_PTE_AT
व्योम set_huge_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		     pte_t *ptep, pte_t pte);

#घोषणा __HAVE_ARCH_HUGE_PTEP_GET_AND_CLEAR
pte_t huge_ptep_get_and_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pte_t *ptep);

#घोषणा __HAVE_ARCH_HUGE_PTEP_CLEAR_FLUSH
अटल अंतरभूत व्योम huge_ptep_clear_flush(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
पूर्ण

#घोषणा __HAVE_ARCH_HUGE_PTEP_SET_WRPROTECT
अटल अंतरभूत व्योम huge_ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm,
					   अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_t old_pte = *ptep;
	set_huge_pte_at(mm, addr, ptep, pte_wrprotect(old_pte));
पूर्ण

#घोषणा __HAVE_ARCH_HUGE_PTEP_SET_ACCESS_FLAGS
अटल अंतरभूत पूर्णांक huge_ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
					     अचिन्हित दीर्घ addr, pte_t *ptep,
					     pte_t pte, पूर्णांक dirty)
अणु
	पूर्णांक changed = !pte_same(*ptep, pte);
	अगर (changed) अणु
		set_huge_pte_at(vma->vm_mm, addr, ptep, pte);
		flush_tlb_page(vma, addr);
	पूर्ण
	वापस changed;
पूर्ण

#घोषणा __HAVE_ARCH_HUGETLB_FREE_PGD_RANGE
व्योम hugetlb_मुक्त_pgd_range(काष्ठा mmu_gather *tlb, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ end, अचिन्हित दीर्घ न्यूनमान,
			    अचिन्हित दीर्घ उच्चमानing);

#समावेश <यंत्र-generic/hugetlb.h>

#पूर्ण_अगर /* _ASM_SPARC64_HUGETLB_H */
