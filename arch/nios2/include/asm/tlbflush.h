<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2010 Tobias Klauser <tklauser@distanz.ch>
 */

#अगर_अघोषित _ASM_NIOS2_TLBFLUSH_H
#घोषणा _ASM_NIOS2_TLBFLUSH_H

काष्ठा mm_काष्ठा;

/*
 * TLB flushing:
 *
 *  - flush_tlb_all() flushes all processes TLB entries
 *  - flush_tlb_mm(mm) flushes the specअगरied mm context TLB entries
 *  - flush_tlb_range(vma, start, end) flushes a range of pages
 *  - flush_tlb_page(vma, address) flushes a page
 *  - flush_tlb_kernel_range(start, end) flushes a range of kernel pages
 *  - flush_tlb_kernel_page(address) flushes a kernel page
 *
 *  - reload_tlb_page(vma, address, pte) flushes the TLB क्रम address like
 *    flush_tlb_page, then replaces it with a TLB क्रम pte.
 */
बाह्य व्योम flush_tlb_all(व्योम);
बाह्य व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			    अचिन्हित दीर्घ end);
बाह्य व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

अटल अंतरभूत व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ address)
अणु
	flush_tlb_range(vma, address, address + PAGE_SIZE);
पूर्ण

अटल अंतरभूत व्योम flush_tlb_kernel_page(अचिन्हित दीर्घ address)
अणु
	flush_tlb_kernel_range(address, address + PAGE_SIZE);
पूर्ण

बाह्य व्योम reload_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			    pte_t pte);

#पूर्ण_अगर /* _ASM_NIOS2_TLBFLUSH_H */
