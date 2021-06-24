<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_NOHASH_TLBFLUSH_H
#घोषणा _ASM_POWERPC_NOHASH_TLBFLUSH_H

/*
 * TLB flushing:
 *
 *  - flush_tlb_mm(mm) flushes the specअगरied mm context TLB's
 *  - flush_tlb_page(vma, vmaddr) flushes one page
 *  - local_flush_tlb_mm(mm, full) flushes the specअगरied mm context on
 *                           the local processor
 *  - local_flush_tlb_page(vma, vmaddr) flushes one page on the local processor
 *  - flush_tlb_range(vma, start, end) flushes a range of pages
 *  - flush_tlb_kernel_range(start, end) flushes a range of kernel pages
 *
 */

/*
 * TLB flushing क्रम software loaded TLB chips
 *
 * TODO: (CONFIG_FSL_BOOKE) determine अगर flush_tlb_range &
 * flush_tlb_kernel_range are best implemented as tlbia vs
 * specअगरic tlbie's
 */

काष्ठा vm_area_काष्ठा;
काष्ठा mm_काष्ठा;

#घोषणा MMU_NO_CONTEXT      	((अचिन्हित पूर्णांक)-1)

बाह्य व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			    अचिन्हित दीर्घ end);
बाह्य व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

बाह्य व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr);

बाह्य व्योम __local_flush_tlb_page(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr,
				   पूर्णांक tsize, पूर्णांक ind);

#अगर_घोषित CONFIG_SMP
बाह्य व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr);
बाह्य व्योम __flush_tlb_page(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr,
			     पूर्णांक tsize, पूर्णांक ind);
#अन्यथा
#घोषणा flush_tlb_mm(mm)		local_flush_tlb_mm(mm)
#घोषणा flush_tlb_page(vma,addr)	local_flush_tlb_page(vma,addr)
#घोषणा __flush_tlb_page(mm,addr,p,i)	__local_flush_tlb_page(mm,addr,p,i)
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_POWERPC_NOHASH_TLBFLUSH_H */
