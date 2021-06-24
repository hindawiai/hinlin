<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_TLBFLUSH_H
#घोषणा __ASM_TLBFLUSH_H

#समावेश <linux/mm.h>

/*
 * TLB flushing:
 *
 *  - flush_tlb_all() flushes all processes TLB entries
 *  - flush_tlb_mm(mm) flushes the specअगरied mm context TLB entries
 *  - flush_tlb_page(vma, vmaddr) flushes one page
 *  - flush_tlb_range(vma, start, end) flushes a range of pages
 *  - flush_tlb_kernel_range(start, end) flushes a range of kernel pages
 */
बाह्य व्योम local_flush_tlb_all(व्योम);
बाह्य व्योम local_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम local_flush_tlb_kernel_range(अचिन्हित दीर्घ start,
	अचिन्हित दीर्घ end);
बाह्य व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ page);
बाह्य व्योम local_flush_tlb_one(अचिन्हित दीर्घ vaddr);

#समावेश <यंत्र/mmu_context.h>

#अगर_घोषित CONFIG_SMP

बाह्य व्योम flush_tlb_all(व्योम);
बाह्य व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *);
बाह्य व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ,
	अचिन्हित दीर्घ);
बाह्य व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ);
बाह्य व्योम flush_tlb_one(अचिन्हित दीर्घ vaddr);

#अन्यथा /* CONFIG_SMP */

#घोषणा flush_tlb_all()			local_flush_tlb_all()
#घोषणा flush_tlb_mm(mm)		drop_mmu_context(mm)
#घोषणा flush_tlb_range(vma, vmaddr, end)	local_flush_tlb_range(vma, vmaddr, end)
#घोषणा flush_tlb_kernel_range(vmaddr,end) \
	local_flush_tlb_kernel_range(vmaddr, end)
#घोषणा flush_tlb_page(vma, page)	local_flush_tlb_page(vma, page)
#घोषणा flush_tlb_one(vaddr)		local_flush_tlb_one(vaddr)

#पूर्ण_अगर /* CONFIG_SMP */

#पूर्ण_अगर /* __ASM_TLBFLUSH_H */
