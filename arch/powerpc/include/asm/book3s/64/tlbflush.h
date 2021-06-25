<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_64_TLBFLUSH_H
#घोषणा _ASM_POWERPC_BOOK3S_64_TLBFLUSH_H

#घोषणा MMU_NO_CONTEXT	~0UL

#समावेश <linux/mm_types.h>
#समावेश <यंत्र/book3s/64/tlbflush-hash.h>
#समावेश <यंत्र/book3s/64/tlbflush-radix.h>

/* TLB flush actions. Used as argument to tlbiel_all() */
क्रमागत अणु
	TLB_INVAL_SCOPE_GLOBAL = 0,	/* invalidate all TLBs */
	TLB_INVAL_SCOPE_LPID = 1,	/* invalidate TLBs क्रम current LPID */
पूर्ण;

#अगर_घोषित CONFIG_PPC_NATIVE
अटल अंतरभूत व्योम tlbiel_all(व्योम)
अणु
	/*
	 * This is used क्रम host machine check and bootup.
	 *
	 * This uses early_radix_enabled and implementations use
	 * early_cpu_has_feature etc because that works early in boot
	 * and this is the machine check path which is not perक्रमmance
	 * critical.
	 */
	अगर (early_radix_enabled())
		radix__tlbiel_all(TLB_INVAL_SCOPE_GLOBAL);
	अन्यथा
		hash__tlbiel_all(TLB_INVAL_SCOPE_GLOBAL);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम tlbiel_all(व्योम) अणु BUG(); पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम tlbiel_all_lpid(bool radix)
अणु
	/*
	 * This is used क्रम guest machine check.
	 */
	अगर (radix)
		radix__tlbiel_all(TLB_INVAL_SCOPE_LPID);
	अन्यथा
		hash__tlbiel_all(TLB_INVAL_SCOPE_LPID);
पूर्ण


#घोषणा __HAVE_ARCH_FLUSH_PMD_TLB_RANGE
अटल अंतरभूत व्योम flush_pmd_tlb_range(काष्ठा vm_area_काष्ठा *vma,
				       अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (radix_enabled())
		वापस radix__flush_pmd_tlb_range(vma, start, end);
	वापस hash__flush_tlb_range(vma, start, end);
पूर्ण

#घोषणा __HAVE_ARCH_FLUSH_HUGETLB_TLB_RANGE
अटल अंतरभूत व्योम flush_hugetlb_tlb_range(काष्ठा vm_area_काष्ठा *vma,
					   अचिन्हित दीर्घ start,
					   अचिन्हित दीर्घ end)
अणु
	अगर (radix_enabled())
		वापस radix__flush_hugetlb_tlb_range(vma, start, end);
	वापस hash__flush_tlb_range(vma, start, end);
पूर्ण

अटल अंतरभूत व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (radix_enabled())
		वापस radix__flush_tlb_range(vma, start, end);
	वापस hash__flush_tlb_range(vma, start, end);
पूर्ण

अटल अंतरभूत व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start,
					  अचिन्हित दीर्घ end)
अणु
	अगर (radix_enabled())
		वापस radix__flush_tlb_kernel_range(start, end);
	वापस hash__flush_tlb_kernel_range(start, end);
पूर्ण

अटल अंतरभूत व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (radix_enabled())
		वापस radix__local_flush_tlb_mm(mm);
	वापस hash__local_flush_tlb_mm(mm);
पूर्ण

अटल अंतरभूत व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ vmaddr)
अणु
	अगर (radix_enabled())
		वापस radix__local_flush_tlb_page(vma, vmaddr);
	वापस hash__local_flush_tlb_page(vma, vmaddr);
पूर्ण

अटल अंतरभूत व्योम local_flush_all_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (radix_enabled())
		वापस radix__local_flush_all_mm(mm);
	वापस hash__local_flush_all_mm(mm);
पूर्ण

अटल अंतरभूत व्योम tlb_flush(काष्ठा mmu_gather *tlb)
अणु
	अगर (radix_enabled())
		वापस radix__tlb_flush(tlb);
	वापस hash__tlb_flush(tlb);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (radix_enabled())
		वापस radix__flush_tlb_mm(mm);
	वापस hash__flush_tlb_mm(mm);
पूर्ण

अटल अंतरभूत व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ vmaddr)
अणु
	अगर (radix_enabled())
		वापस radix__flush_tlb_page(vma, vmaddr);
	वापस hash__flush_tlb_page(vma, vmaddr);
पूर्ण

अटल अंतरभूत व्योम flush_all_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (radix_enabled())
		वापस radix__flush_all_mm(mm);
	वापस hash__flush_all_mm(mm);
पूर्ण
#अन्यथा
#घोषणा flush_tlb_mm(mm)		local_flush_tlb_mm(mm)
#घोषणा flush_tlb_page(vma, addr)	local_flush_tlb_page(vma, addr)
#घोषणा flush_all_mm(mm)		local_flush_all_mm(mm)
#पूर्ण_अगर /* CONFIG_SMP */

#घोषणा flush_tlb_fix_spurious_fault flush_tlb_fix_spurious_fault
अटल अंतरभूत व्योम flush_tlb_fix_spurious_fault(काष्ठा vm_area_काष्ठा *vma,
						अचिन्हित दीर्घ address)
अणु
	/* See ptep_set_access_flags comment */
	अगर (atomic_पढ़ो(&vma->vm_mm->context.copros) > 0)
		flush_tlb_page(vma, address);
पूर्ण

बाह्य bool tlbie_capable;
बाह्य bool tlbie_enabled;

अटल अंतरभूत bool cputlb_use_tlbie(व्योम)
अणु
	वापस tlbie_enabled;
पूर्ण

#पूर्ण_अगर /*  _ASM_POWERPC_BOOK3S_64_TLBFLUSH_H */
