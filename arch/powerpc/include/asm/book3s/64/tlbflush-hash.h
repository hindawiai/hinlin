<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_64_TLBFLUSH_HASH_H
#घोषणा _ASM_POWERPC_BOOK3S_64_TLBFLUSH_HASH_H

/*
 * TLB flushing क्रम 64-bit hash-MMU CPUs
 */

#समावेश <linux/percpu.h>
#समावेश <यंत्र/page.h>

#घोषणा PPC64_TLB_BATCH_NR 192

काष्ठा ppc64_tlb_batch अणु
	पूर्णांक			active;
	अचिन्हित दीर्घ		index;
	काष्ठा mm_काष्ठा	*mm;
	real_pte_t		pte[PPC64_TLB_BATCH_NR];
	अचिन्हित दीर्घ		vpn[PPC64_TLB_BATCH_NR];
	अचिन्हित पूर्णांक		psize;
	पूर्णांक			ssize;
पूर्ण;
DECLARE_PER_CPU(काष्ठा ppc64_tlb_batch, ppc64_tlb_batch);

बाह्य व्योम __flush_tlb_pending(काष्ठा ppc64_tlb_batch *batch);

#घोषणा __HAVE_ARCH_ENTER_LAZY_MMU_MODE

अटल अंतरभूत व्योम arch_enter_lazy_mmu_mode(व्योम)
अणु
	काष्ठा ppc64_tlb_batch *batch;

	अगर (radix_enabled())
		वापस;
	batch = this_cpu_ptr(&ppc64_tlb_batch);
	batch->active = 1;
पूर्ण

अटल अंतरभूत व्योम arch_leave_lazy_mmu_mode(व्योम)
अणु
	काष्ठा ppc64_tlb_batch *batch;

	अगर (radix_enabled())
		वापस;
	batch = this_cpu_ptr(&ppc64_tlb_batch);

	अगर (batch->index)
		__flush_tlb_pending(batch);
	batch->active = 0;
पूर्ण

#घोषणा arch_flush_lazy_mmu_mode()      करो अणुपूर्ण जबतक (0)

बाह्य व्योम hash__tlbiel_all(अचिन्हित पूर्णांक action);

बाह्य व्योम flush_hash_page(अचिन्हित दीर्घ vpn, real_pte_t pte, पूर्णांक psize,
			    पूर्णांक ssize, अचिन्हित दीर्घ flags);
बाह्य व्योम flush_hash_range(अचिन्हित दीर्घ number, पूर्णांक local);
बाह्य व्योम flush_hash_hugepage(अचिन्हित दीर्घ vsid, अचिन्हित दीर्घ addr,
				pmd_t *pmdp, अचिन्हित पूर्णांक psize, पूर्णांक ssize,
				अचिन्हित दीर्घ flags);
अटल अंतरभूत व्योम hash__local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण

अटल अंतरभूत व्योम hash__flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण

अटल अंतरभूत व्योम hash__local_flush_all_mm(काष्ठा mm_काष्ठा *mm)
अणु
	/*
	 * There's no Page Walk Cache क्रम hash, so what is needed is
	 * the same as flush_tlb_mm(), which करोesn't really make sense
	 * with hash. So the only thing we could करो is flush the
	 * entire LPID! Punt क्रम now, as it's not being used.
	 */
	WARN_ON_ONCE(1);
पूर्ण

अटल अंतरभूत व्योम hash__flush_all_mm(काष्ठा mm_काष्ठा *mm)
अणु
	/*
	 * There's no Page Walk Cache क्रम hash, so what is needed is
	 * the same as flush_tlb_mm(), which करोesn't really make sense
	 * with hash. So the only thing we could करो is flush the
	 * entire LPID! Punt क्रम now, as it's not being used.
	 */
	WARN_ON_ONCE(1);
पूर्ण

अटल अंतरभूत व्योम hash__local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
					  अचिन्हित दीर्घ vmaddr)
अणु
पूर्ण

अटल अंतरभूत व्योम hash__flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
				    अचिन्हित दीर्घ vmaddr)
अणु
पूर्ण

अटल अंतरभूत व्योम hash__flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
पूर्ण

अटल अंतरभूत व्योम hash__flush_tlb_kernel_range(अचिन्हित दीर्घ start,
					    अचिन्हित दीर्घ end)
अणु
पूर्ण


काष्ठा mmu_gather;
बाह्य व्योम hash__tlb_flush(काष्ठा mmu_gather *tlb);
/* Private function क्रम use by PCI IO mapping code */
बाह्य व्योम __flush_hash_table_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम flush_tlb_pmd_range(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
				अचिन्हित दीर्घ addr);
#पूर्ण_अगर /*  _ASM_POWERPC_BOOK3S_64_TLBFLUSH_HASH_H */
