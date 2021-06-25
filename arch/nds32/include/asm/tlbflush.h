<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित _ASMNDS32_TLBFLUSH_H
#घोषणा _ASMNDS32_TLBFLUSH_H

#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <nds32_पूर्णांकrinsic.h>

अटल अंतरभूत व्योम local_flush_tlb_all(व्योम)
अणु
	__nds32__tlbop_flua();
	__nds32__isb();
पूर्ण

अटल अंतरभूत व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	__nds32__tlbop_flua();
	__nds32__isb();
पूर्ण

अटल अंतरभूत व्योम local_flush_tlb_kernel_range(अचिन्हित दीर्घ start,
						अचिन्हित दीर्घ end)
अणु
	जबतक (start < end) अणु
		__nds32__tlbop_inv(start);
		__nds32__isb();
		start += PAGE_SIZE;
	पूर्ण
पूर्ण

व्योम local_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
			   अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr);

#घोषणा flush_tlb_all		local_flush_tlb_all
#घोषणा flush_tlb_mm		local_flush_tlb_mm
#घोषणा flush_tlb_range		local_flush_tlb_range
#घोषणा flush_tlb_page		local_flush_tlb_page
#घोषणा flush_tlb_kernel_range	local_flush_tlb_kernel_range

व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma,
		      अचिन्हित दीर्घ address, pte_t * pte);

#पूर्ण_अगर
