<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */

#अगर_अघोषित __ASM_OPENRISC_TLBFLUSH_H
#घोषणा __ASM_OPENRISC_TLBFLUSH_H

#समावेश <linux/mm.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/current.h>
#समावेश <linux/sched.h>

/*
 *  - flush_tlb() flushes the current mm काष्ठा TLBs
 *  - flush_tlb_all() flushes all processes TLBs
 *  - flush_tlb_mm(mm) flushes the specअगरied mm context TLB's
 *  - flush_tlb_page(vma, vmaddr) flushes one page
 *  - flush_tlb_range(mm, start, end) flushes a range of pages
 */
बाह्य व्योम local_flush_tlb_all(व्योम);
बाह्य व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ addr);
बाह्य व्योम local_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ start,
				  अचिन्हित दीर्घ end);

#अगर_अघोषित CONFIG_SMP
#घोषणा flush_tlb_all	local_flush_tlb_all
#घोषणा flush_tlb_mm	local_flush_tlb_mm
#घोषणा flush_tlb_page	local_flush_tlb_page
#घोषणा flush_tlb_range	local_flush_tlb_range
#अन्यथा
बाह्य व्योम flush_tlb_all(व्योम);
बाह्य व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr);
बाह्य व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			    अचिन्हित दीर्घ end);
#पूर्ण_अगर

अटल अंतरभूत व्योम flush_tlb(व्योम)
अणु
	flush_tlb_mm(current->mm);
पूर्ण

अटल अंतरभूत व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start,
					  अचिन्हित दीर्घ end)
अणु
	flush_tlb_range(शून्य, start, end);
पूर्ण

#पूर्ण_अगर /* __ASM_OPENRISC_TLBFLUSH_H */
