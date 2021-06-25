<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PARISC_TLBFLUSH_H
#घोषणा _PARISC_TLBFLUSH_H

/* TLB flushing routines.... */

#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/mmu_context.h>

बाह्य व्योम flush_tlb_all(व्योम);
बाह्य व्योम flush_tlb_all_local(व्योम *);

#घोषणा smp_flush_tlb_all()	flush_tlb_all()

पूर्णांक __flush_tlb_range(अचिन्हित दीर्घ sid,
	अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

#घोषणा flush_tlb_range(vma, start, end) \
	__flush_tlb_range((vma)->vm_mm->context, start, end)

#घोषणा flush_tlb_kernel_range(start, end) \
	__flush_tlb_range(0, start, end)

/*
 * flush_tlb_mm()
 *
 * The code to चयन to a new context is NOT valid क्रम processes
 * which play with the space id's.  Thus, we have to preserve the
 * space and just flush the entire tlb.  However, the compilers,
 * dynamic linker, etc, करो not manipulate space id's, so there
 * could be a signअगरicant perक्रमmance benefit in चयनing contexts
 * and not flushing the whole tlb.
 */

अटल अंतरभूत व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	BUG_ON(mm == &init_mm); /* Should never happen */

#अगर 1 || defined(CONFIG_SMP)
	/* Except क्रम very small thपढ़ोs, flushing the whole TLB is
	 * faster than using __flush_tlb_range.  The pdtlb and pitlb
	 * inकाष्ठाions are very slow because of the TLB broadcast.
	 * It might be faster to करो local range flushes on all CPUs
	 * on PA 2.0 प्रणालीs.
	 */
	flush_tlb_all();
#अन्यथा
	/* FIXME: currently broken, causing space id and protection ids
	 * to go out of sync, resulting in faults on userspace accesses.
	 * This approach needs further investigation since running many
	 * small applications (e.g., GCC testsuite) is faster on HP-UX.
	 */
	अगर (mm) अणु
		अगर (mm->context != 0)
			मुक्त_sid(mm->context);
		mm->context = alloc_sid();
		अगर (mm == current->active_mm)
			load_context(mm->context);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ addr)
अणु
	purge_tlb_entries(vma->vm_mm, addr);
पूर्ण
#पूर्ण_अगर
