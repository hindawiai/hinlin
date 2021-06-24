<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_TLBFLUSH_H
#घोषणा _ASM_MICROBLAZE_TLBFLUSH_H

#समावेश <linux/sched.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/processor.h>	/* For TASK_SIZE */
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/page.h>

बाह्य व्योम _tlbie(अचिन्हित दीर्घ address);
बाह्य व्योम _tlbia(व्योम);

#घोषणा __tlbia()	अणु preempt_disable(); _tlbia(); preempt_enable(); पूर्ण
#घोषणा __tlbie(x)	अणु _tlbie(x); पूर्ण

अटल अंतरभूत व्योम local_flush_tlb_all(व्योम)
	अणु __tlbia(); पूर्ण
अटल अंतरभूत व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
	अणु __tlbia(); पूर्ण
अटल अंतरभूत व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ vmaddr)
	अणु __tlbie(vmaddr); पूर्ण
अटल अंतरभूत व्योम local_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
	अणु __tlbia(); पूर्ण

#घोषणा flush_tlb_kernel_range(start, end)	करो अणु पूर्ण जबतक (0)

#घोषणा update_mmu_cache(vma, addr, ptep)	करो अणु पूर्ण जबतक (0)

#घोषणा flush_tlb_all local_flush_tlb_all
#घोषणा flush_tlb_mm local_flush_tlb_mm
#घोषणा flush_tlb_page local_flush_tlb_page
#घोषणा flush_tlb_range local_flush_tlb_range

/*
 * This is called in munmap when we have मुक्तd up some page-table
 * pages.  We करोn't need to do anything here, there's nothing special
 * about our page-table pages.  -- paulus
 */
अटल अंतरभूत व्योम flush_tlb_pgtables(काष्ठा mm_काष्ठा *mm,
	अचिन्हित दीर्घ start, अचिन्हित दीर्घ end) अणु पूर्ण

#पूर्ण_अगर /* _ASM_MICROBLAZE_TLBFLUSH_H */
