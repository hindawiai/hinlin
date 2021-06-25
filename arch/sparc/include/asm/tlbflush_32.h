<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC_TLBFLUSH_H
#घोषणा _SPARC_TLBFLUSH_H

#समावेश <यंत्र/cachetlb_32.h>

#घोषणा flush_tlb_all() \
	sparc32_cachetlb_ops->tlb_all()
#घोषणा flush_tlb_mm(mm) \
	sparc32_cachetlb_ops->tlb_mm(mm)
#घोषणा flush_tlb_range(vma, start, end) \
	sparc32_cachetlb_ops->tlb_range(vma, start, end)
#घोषणा flush_tlb_page(vma, addr) \
	sparc32_cachetlb_ops->tlb_page(vma, addr)

/*
 * This is a kludge, until I know better. --zaitcev XXX
 */
अटल अंतरभूत व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start,
					  अचिन्हित दीर्घ end)
अणु
	flush_tlb_all();
पूर्ण

#पूर्ण_अगर /* _SPARC_TLBFLUSH_H */
