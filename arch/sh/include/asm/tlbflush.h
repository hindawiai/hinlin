<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_TLBFLUSH_H
#घोषणा __ASM_SH_TLBFLUSH_H

/*
 * TLB flushing:
 *
 *  - flush_tlb_all() flushes all processes TLBs
 *  - flush_tlb_mm(mm) flushes the specअगरied mm context TLB's
 *  - flush_tlb_page(vma, vmaddr) flushes one page
 *  - flush_tlb_range(vma, start, end) flushes a range of pages
 *  - flush_tlb_kernel_range(start, end) flushes a range of kernel pages
 */
बाह्य व्योम local_flush_tlb_all(व्योम);
बाह्य व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम local_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ start,
				  अचिन्हित दीर्घ end);
बाह्य व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ page);
बाह्य व्योम local_flush_tlb_kernel_range(अचिन्हित दीर्घ start,
					 अचिन्हित दीर्घ end);
बाह्य व्योम local_flush_tlb_one(अचिन्हित दीर्घ asid, अचिन्हित दीर्घ page);

बाह्य व्योम __flush_tlb_global(व्योम);

#अगर_घोषित CONFIG_SMP

बाह्य व्योम flush_tlb_all(व्योम);
बाह्य व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			    अचिन्हित दीर्घ end);
बाह्य व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page);
बाह्य व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम flush_tlb_one(अचिन्हित दीर्घ asid, अचिन्हित दीर्घ page);

#अन्यथा

#घोषणा flush_tlb_all()			local_flush_tlb_all()
#घोषणा flush_tlb_mm(mm)		local_flush_tlb_mm(mm)
#घोषणा flush_tlb_page(vma, page)	local_flush_tlb_page(vma, page)
#घोषणा flush_tlb_one(asid, page)	local_flush_tlb_one(asid, page)

#घोषणा flush_tlb_range(vma, start, end)	\
	local_flush_tlb_range(vma, start, end)

#घोषणा flush_tlb_kernel_range(start, end)	\
	local_flush_tlb_kernel_range(start, end)

#पूर्ण_अगर /* CONFIG_SMP */

#पूर्ण_अगर /* __ASM_SH_TLBFLUSH_H */
