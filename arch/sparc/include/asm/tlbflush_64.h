<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_TLBFLUSH_H
#घोषणा _SPARC64_TLBFLUSH_H

#समावेश <यंत्र/mmu_context.h>

/* TSB flush operations. */

#घोषणा TLB_BATCH_NR	192

काष्ठा tlb_batch अणु
	अचिन्हित पूर्णांक hugepage_shअगरt;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ tlb_nr;
	अचिन्हित दीर्घ active;
	अचिन्हित दीर्घ vaddrs[TLB_BATCH_NR];
पूर्ण;

व्योम flush_tsb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम flush_tsb_user(काष्ठा tlb_batch *tb);
व्योम flush_tsb_user_page(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr,
			 अचिन्हित पूर्णांक hugepage_shअगरt);

/* TLB flush operations. */

अटल अंतरभूत व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण

अटल अंतरभूत व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ vmaddr)
अणु
पूर्ण

अटल अंतरभूत व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
पूर्ण

व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

#घोषणा __HAVE_ARCH_ENTER_LAZY_MMU_MODE

व्योम flush_tlb_pending(व्योम);
व्योम arch_enter_lazy_mmu_mode(व्योम);
व्योम arch_leave_lazy_mmu_mode(व्योम);
#घोषणा arch_flush_lazy_mmu_mode()      करो अणुपूर्ण जबतक (0)

/* Local cpu only.  */
व्योम __flush_tlb_all(व्योम);
व्योम __flush_tlb_page(अचिन्हित दीर्घ context, अचिन्हित दीर्घ vaddr);
व्योम __flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

#अगर_अघोषित CONFIG_SMP

अटल अंतरभूत व्योम global_flush_tlb_page(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr)
अणु
	__flush_tlb_page(CTX_HWBITS(mm->context), vaddr);
पूर्ण

#अन्यथा /* CONFIG_SMP */

व्योम smp_flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम smp_flush_tlb_page(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr);

#घोषणा global_flush_tlb_page(mm, vaddr) \
	smp_flush_tlb_page(mm, vaddr)

#पूर्ण_अगर /* ! CONFIG_SMP */

#पूर्ण_अगर /* _SPARC64_TLBFLUSH_H */
