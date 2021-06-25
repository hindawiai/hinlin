<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _S390_TLBFLUSH_H
#घोषणा _S390_TLBFLUSH_H

#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/processor.h>

/*
 * Flush all TLB entries on the local CPU.
 */
अटल अंतरभूत व्योम __tlb_flush_local(व्योम)
अणु
	यंत्र अस्थिर("ptlb" : : : "memory");
पूर्ण

/*
 * Flush TLB entries क्रम a specअगरic ASCE on all CPUs
 */
अटल अंतरभूत व्योम __tlb_flush_idte(अचिन्हित दीर्घ asce)
अणु
	अचिन्हित दीर्घ opt;

	opt = IDTE_PTOA;
	अगर (MACHINE_HAS_TLB_GUEST)
		opt |= IDTE_GUEST_ASCE;
	/* Global TLB flush क्रम the mm */
	यंत्र अस्थिर(
		"	.insn	rrf,0xb98e0000,0,%0,%1,0"
		: : "a" (opt), "a" (asce) : "cc");
पूर्ण

/*
 * Flush all TLB entries on all CPUs.
 */
अटल अंतरभूत व्योम __tlb_flush_global(व्योम)
अणु
	अचिन्हित पूर्णांक dummy = 0;

	csp(&dummy, 0, 0);
पूर्ण

/*
 * Flush TLB entries क्रम a specअगरic mm on all CPUs (in हाल gmap is used
 * this implicates multiple ASCEs!).
 */
अटल अंतरभूत व्योम __tlb_flush_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ gmap_asce;

	/*
	 * If the machine has IDTE we prefer to करो a per mm flush
	 * on all cpus instead of करोing a local flush अगर the mm
	 * only ran on the local cpu.
	 */
	preempt_disable();
	atomic_inc(&mm->context.flush_count);
	/* Reset TLB flush mask */
	cpumask_copy(mm_cpumask(mm), &mm->context.cpu_attach_mask);
	barrier();
	gmap_asce = READ_ONCE(mm->context.gmap_asce);
	अगर (MACHINE_HAS_IDTE && gmap_asce != -1UL) अणु
		अगर (gmap_asce)
			__tlb_flush_idte(gmap_asce);
		__tlb_flush_idte(mm->context.asce);
	पूर्ण अन्यथा अणु
		/* Global TLB flush */
		__tlb_flush_global();
	पूर्ण
	atomic_dec(&mm->context.flush_count);
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम __tlb_flush_kernel(व्योम)
अणु
	अगर (MACHINE_HAS_IDTE)
		__tlb_flush_idte(init_mm.context.asce);
	अन्यथा
		__tlb_flush_global();
पूर्ण

अटल अंतरभूत व्योम __tlb_flush_mm_lazy(काष्ठा mm_काष्ठा * mm)
अणु
	spin_lock(&mm->context.lock);
	अगर (mm->context.flush_mm) अणु
		mm->context.flush_mm = 0;
		__tlb_flush_mm(mm);
	पूर्ण
	spin_unlock(&mm->context.lock);
पूर्ण

/*
 * TLB flushing:
 *  flush_tlb() - flushes the current mm काष्ठा TLBs
 *  flush_tlb_all() - flushes all processes TLBs
 *  flush_tlb_mm(mm) - flushes the specअगरied mm context TLB's
 *  flush_tlb_page(vma, vmaddr) - flushes one page
 *  flush_tlb_range(vma, start, end) - flushes a range of pages
 *  flush_tlb_kernel_range(start, end) - flushes a range of kernel pages
 */

/*
 * flush_tlb_mm goes together with ptep_set_wrprotect क्रम the
 * copy_page_range operation and flush_tlb_range is related to
 * ptep_get_and_clear क्रम change_protection. ptep_set_wrprotect and
 * ptep_get_and_clear करो not flush the TLBs directly अगर the mm has
 * only one user. At the end of the update the flush_tlb_mm and
 * flush_tlb_range functions need to करो the flush.
 */
#घोषणा flush_tlb()				करो अणु पूर्ण जबतक (0)
#घोषणा flush_tlb_all()				करो अणु पूर्ण जबतक (0)
#घोषणा flush_tlb_page(vma, addr)		करो अणु पूर्ण जबतक (0)

अटल अंतरभूत व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	__tlb_flush_mm_lazy(mm);
पूर्ण

अटल अंतरभूत व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	__tlb_flush_mm_lazy(vma->vm_mm);
पूर्ण

अटल अंतरभूत व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start,
					  अचिन्हित दीर्घ end)
अणु
	__tlb_flush_kernel();
पूर्ण

#पूर्ण_अगर /* _S390_TLBFLUSH_H */
