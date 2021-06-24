<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008, 2009 Cavium Networks, Inc.
 */

#अगर_अघोषित __ASM_HUGETLB_H
#घोषणा __ASM_HUGETLB_H

#समावेश <यंत्र/page.h>

#घोषणा __HAVE_ARCH_PREPARE_HUGEPAGE_RANGE
अटल अंतरभूत पूर्णांक prepare_hugepage_range(काष्ठा file *file,
					 अचिन्हित दीर्घ addr,
					 अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ task_size = STACK_TOP;
	काष्ठा hstate *h = hstate_file(file);

	अगर (len & ~huge_page_mask(h))
		वापस -EINVAL;
	अगर (addr & ~huge_page_mask(h))
		वापस -EINVAL;
	अगर (len > task_size)
		वापस -ENOMEM;
	अगर (task_size - len < addr)
		वापस -EINVAL;
	वापस 0;
पूर्ण

#घोषणा __HAVE_ARCH_HUGE_PTEP_GET_AND_CLEAR
अटल अंतरभूत pte_t huge_ptep_get_and_clear(काष्ठा mm_काष्ठा *mm,
					    अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_t clear;
	pte_t pte = *ptep;

	pte_val(clear) = (अचिन्हित दीर्घ)invalid_pte_table;
	set_pte_at(mm, addr, ptep, clear);
	वापस pte;
पूर्ण

#घोषणा __HAVE_ARCH_HUGE_PTEP_CLEAR_FLUSH
अटल अंतरभूत व्योम huge_ptep_clear_flush(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	flush_tlb_page(vma, addr & huge_page_mask(hstate_vma(vma)));
पूर्ण

#घोषणा __HAVE_ARCH_HUGE_PTE_NONE
अटल अंतरभूत पूर्णांक huge_pte_none(pte_t pte)
अणु
	अचिन्हित दीर्घ val = pte_val(pte) & ~_PAGE_GLOBAL;
	वापस !val || (val == (अचिन्हित दीर्घ)invalid_pte_table);
पूर्ण

#घोषणा __HAVE_ARCH_HUGE_PTEP_SET_ACCESS_FLAGS
अटल अंतरभूत पूर्णांक huge_ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
					     अचिन्हित दीर्घ addr,
					     pte_t *ptep, pte_t pte,
					     पूर्णांक dirty)
अणु
	पूर्णांक changed = !pte_same(*ptep, pte);

	अगर (changed) अणु
		set_pte_at(vma->vm_mm, addr, ptep, pte);
		/*
		 * There could be some standard sized pages in there,
		 * get them all.
		 */
		flush_tlb_range(vma, addr, addr + HPAGE_SIZE);
	पूर्ण
	वापस changed;
पूर्ण

#समावेश <यंत्र-generic/hugetlb.h>

#पूर्ण_अगर /* __ASM_HUGETLB_H */
