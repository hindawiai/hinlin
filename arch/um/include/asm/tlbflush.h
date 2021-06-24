<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __UM_TLBFLUSH_H
#घोषणा __UM_TLBFLUSH_H

#समावेश <linux/mm.h>

/*
 * TLB flushing:
 *
 *  - flush_tlb() flushes the current mm काष्ठा TLBs
 *  - flush_tlb_all() flushes all processes TLBs
 *  - flush_tlb_mm(mm) flushes the specअगरied mm context TLB's
 *  - flush_tlb_page(vma, vmaddr) flushes one page
 *  - flush_tlb_kernel_vm() flushes the kernel vm area
 *  - flush_tlb_range(vma, start, end) flushes a range of pages
 */

बाह्य व्योम flush_tlb_all(व्योम);
बाह्य व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, 
			    अचिन्हित दीर्घ end);
बाह्य व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address);
बाह्य व्योम flush_tlb_kernel_vm(व्योम);
बाह्य व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम __flush_tlb_one(अचिन्हित दीर्घ addr);

#पूर्ण_अगर
