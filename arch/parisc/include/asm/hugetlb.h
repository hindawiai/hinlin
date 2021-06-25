<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PARISC64_HUGETLB_H
#घोषणा _ASM_PARISC64_HUGETLB_H

#समावेश <यंत्र/page.h>

#घोषणा __HAVE_ARCH_HUGE_SET_HUGE_PTE_AT
व्योम set_huge_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		     pte_t *ptep, pte_t pte);

#घोषणा __HAVE_ARCH_HUGE_PTEP_GET_AND_CLEAR
pte_t huge_ptep_get_and_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pte_t *ptep);

/*
 * If the arch करोesn't supply something अन्यथा, assume that hugepage
 * size aligned regions are ok without further preparation.
 */
#घोषणा __HAVE_ARCH_PREPARE_HUGEPAGE_RANGE
अटल अंतरभूत पूर्णांक prepare_hugepage_range(काष्ठा file *file,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	अगर (len & ~HPAGE_MASK)
		वापस -EINVAL;
	अगर (addr & ~HPAGE_MASK)
		वापस -EINVAL;
	वापस 0;
पूर्ण

#घोषणा __HAVE_ARCH_HUGE_PTEP_CLEAR_FLUSH
अटल अंतरभूत व्योम huge_ptep_clear_flush(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
पूर्ण

#घोषणा __HAVE_ARCH_HUGE_PTEP_SET_WRPROTECT
व्योम huge_ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm,
					   अचिन्हित दीर्घ addr, pte_t *ptep);

#घोषणा __HAVE_ARCH_HUGE_PTEP_SET_ACCESS_FLAGS
पूर्णांक huge_ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
					     अचिन्हित दीर्घ addr, pte_t *ptep,
					     pte_t pte, पूर्णांक dirty);

#समावेश <यंत्र-generic/hugetlb.h>

#पूर्ण_अगर /* _ASM_PARISC64_HUGETLB_H */
