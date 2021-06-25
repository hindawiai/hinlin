<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_HUGETLB_H
#घोषणा _ASM_IA64_HUGETLB_H

#समावेश <यंत्र/page.h>

#घोषणा __HAVE_ARCH_HUGETLB_FREE_PGD_RANGE
व्योम hugetlb_मुक्त_pgd_range(काष्ठा mmu_gather *tlb, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ end, अचिन्हित दीर्घ न्यूनमान,
			    अचिन्हित दीर्घ उच्चमानing);

#घोषणा __HAVE_ARCH_PREPARE_HUGEPAGE_RANGE
पूर्णांक prepare_hugepage_range(काष्ठा file *file,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len);

अटल अंतरभूत पूर्णांक is_hugepage_only_range(काष्ठा mm_काष्ठा *mm,
					 अचिन्हित दीर्घ addr,
					 अचिन्हित दीर्घ len)
अणु
	वापस (REGION_NUMBER(addr) == RGN_HPAGE ||
		REGION_NUMBER((addr)+(len)-1) == RGN_HPAGE);
पूर्ण
#घोषणा is_hugepage_only_range is_hugepage_only_range

#घोषणा __HAVE_ARCH_HUGE_PTEP_CLEAR_FLUSH
अटल अंतरभूत व्योम huge_ptep_clear_flush(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
पूर्ण

#समावेश <यंत्र-generic/hugetlb.h>

#पूर्ण_अगर /* _ASM_IA64_HUGETLB_H */
