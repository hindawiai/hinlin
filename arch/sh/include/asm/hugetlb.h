<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_SH_HUGETLB_H
#घोषणा _ASM_SH_HUGETLB_H

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/page.h>

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

अटल अंतरभूत व्योम arch_clear_hugepage_flags(काष्ठा page *page)
अणु
	clear_bit(PG_dcache_clean, &page->flags);
पूर्ण
#घोषणा arch_clear_hugepage_flags arch_clear_hugepage_flags

#समावेश <यंत्र-generic/hugetlb.h>

#पूर्ण_अगर /* _ASM_SH_HUGETLB_H */
