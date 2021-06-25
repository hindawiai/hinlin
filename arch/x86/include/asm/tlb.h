<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_TLB_H
#घोषणा _ASM_X86_TLB_H

#घोषणा tlb_start_vma(tlb, vma) करो अणु पूर्ण जबतक (0)
#घोषणा tlb_end_vma(tlb, vma) करो अणु पूर्ण जबतक (0)

#घोषणा tlb_flush tlb_flush
अटल अंतरभूत व्योम tlb_flush(काष्ठा mmu_gather *tlb);

#समावेश <यंत्र-generic/tlb.h>

अटल अंतरभूत व्योम tlb_flush(काष्ठा mmu_gather *tlb)
अणु
	अचिन्हित दीर्घ start = 0UL, end = TLB_FLUSH_ALL;
	अचिन्हित पूर्णांक stride_shअगरt = tlb_get_unmap_shअगरt(tlb);

	अगर (!tlb->fullmm && !tlb->need_flush_all) अणु
		start = tlb->start;
		end = tlb->end;
	पूर्ण

	flush_tlb_mm_range(tlb->mm, start, end, stride_shअगरt, tlb->मुक्तd_tables);
पूर्ण

/*
 * While x86 architecture in general requires an IPI to perक्रमm TLB
 * shootकरोwn, enablement code क्रम several hypervisors overrides
 * .flush_tlb_others hook in pv_mmu_ops and implements it by issuing
 * a hypercall. To keep software pagetable walkers safe in this हाल we
 * चयन to RCU based table मुक्त (MMU_GATHER_RCU_TABLE_FREE). See the comment
 * below 'ifdef CONFIG_MMU_GATHER_RCU_TABLE_FREE' in include/यंत्र-generic/tlb.h
 * क्रम more details.
 */
अटल अंतरभूत व्योम __tlb_हटाओ_table(व्योम *table)
अणु
	मुक्त_page_and_swap_cache(table);
पूर्ण

#पूर्ण_अगर /* _ASM_X86_TLB_H */
