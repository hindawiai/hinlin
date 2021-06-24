<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_32_TLBFLUSH_H
#घोषणा _ASM_POWERPC_BOOK3S_32_TLBFLUSH_H

#घोषणा MMU_NO_CONTEXT      (0)
/*
 * TLB flushing क्रम "classic" hash-MMU 32-bit CPUs, 6xx, 7xx, 7xxx
 */
व्योम hash__flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
व्योम hash__flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr);
व्योम hash__flush_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

#अगर_घोषित CONFIG_SMP
व्योम _tlbie(अचिन्हित दीर्घ address);
#अन्यथा
अटल अंतरभूत व्योम _tlbie(अचिन्हित दीर्घ address)
अणु
	यंत्र अस्थिर ("tlbie %0; sync" : : "r" (address) : "memory");
पूर्ण
#पूर्ण_अगर
व्योम _tlbia(व्योम);

/*
 * Called at the end of a mmu_gather operation to make sure the
 * TLB flush is completely करोne.
 */
अटल अंतरभूत व्योम tlb_flush(काष्ठा mmu_gather *tlb)
अणु
	/* 603 needs to flush the whole TLB here since it करोesn't use a hash table. */
	अगर (!mmu_has_feature(MMU_FTR_HPTE_TABLE))
		_tlbia();
पूर्ण

अटल अंतरभूत व्योम flush_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	start &= PAGE_MASK;
	अगर (mmu_has_feature(MMU_FTR_HPTE_TABLE))
		hash__flush_range(mm, start, end);
	अन्यथा अगर (end - start <= PAGE_SIZE)
		_tlbie(start);
	अन्यथा
		_tlbia();
पूर्ण

अटल अंतरभूत व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mmu_has_feature(MMU_FTR_HPTE_TABLE))
		hash__flush_tlb_mm(mm);
	अन्यथा
		_tlbia();
पूर्ण

अटल अंतरभूत व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr)
अणु
	अगर (mmu_has_feature(MMU_FTR_HPTE_TABLE))
		hash__flush_tlb_page(vma, vmaddr);
	अन्यथा
		_tlbie(vmaddr);
पूर्ण

अटल अंतरभूत व्योम
flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	flush_range(vma->vm_mm, start, end);
पूर्ण

अटल अंतरभूत व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	flush_range(&init_mm, start, end);
पूर्ण

अटल अंतरभूत व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ vmaddr)
अणु
	flush_tlb_page(vma, vmaddr);
पूर्ण
अटल अंतरभूत व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	flush_tlb_mm(mm);
पूर्ण

#पूर्ण_अगर /* _ASM_POWERPC_BOOK3S_32_TLBFLUSH_H */
