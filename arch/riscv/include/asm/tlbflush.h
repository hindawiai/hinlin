<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2009 Chen Liqin <liqin.chen@sunplusct.com>
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_TLBFLUSH_H
#घोषणा _ASM_RISCV_TLBFLUSH_H

#समावेश <linux/mm_types.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/errata_list.h>

#अगर_घोषित CONFIG_MMU
अटल अंतरभूत व्योम local_flush_tlb_all(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("sfence.vma" : : : "memory");
पूर्ण

/* Flush one page from local TLB */
अटल अंतरभूत व्योम local_flush_tlb_page(अचिन्हित दीर्घ addr)
अणु
	ALT_FLUSH_TLB_PAGE(__यंत्र__ __अस्थिर__ ("sfence.vma %0" : : "r" (addr) : "memory"));
पूर्ण
#अन्यथा /* CONFIG_MMU */
#घोषणा local_flush_tlb_all()			करो अणु पूर्ण जबतक (0)
#घोषणा local_flush_tlb_page(addr)		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_MMU */

#अगर defined(CONFIG_SMP) && defined(CONFIG_MMU)
व्योम flush_tlb_all(व्योम);
व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr);
व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
		     अचिन्हित दीर्घ end);
#अन्यथा /* CONFIG_SMP && CONFIG_MMU */

#घोषणा flush_tlb_all() local_flush_tlb_all()
#घोषणा flush_tlb_page(vma, addr) local_flush_tlb_page(addr)

अटल अंतरभूत व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	local_flush_tlb_all();
पूर्ण

#घोषणा flush_tlb_mm(mm) flush_tlb_all()
#पूर्ण_अगर /* !CONFIG_SMP || !CONFIG_MMU */

/* Flush a range of kernel pages */
अटल अंतरभूत व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start,
	अचिन्हित दीर्घ end)
अणु
	flush_tlb_all();
पूर्ण

#पूर्ण_अगर /* _ASM_RISCV_TLBFLUSH_H */
