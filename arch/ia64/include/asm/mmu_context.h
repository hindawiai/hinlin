<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_MMU_CONTEXT_H
#घोषणा _ASM_IA64_MMU_CONTEXT_H

/*
 * Copyright (C) 1998-2002 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */

/*
 * Routines to manage the allocation of task context numbers.  Task context
 * numbers are used to reduce or eliminate the need to perक्रमm TLB flushes
 * due to context चयनes.  Context numbers are implemented using ia-64
 * region ids.  Since the IA-64 TLB करोes not consider the region number when
 * perक्रमming a TLB lookup, we need to assign a unique region id to each
 * region in a process.  We use the least signअगरicant three bits in aregion
 * id क्रम this purpose.
 */

#घोषणा IA64_REGION_ID_KERNEL	0 /* the kernel's region id (tlb.c depends on this being 0) */

#घोषणा ia64_rid(ctx,addr)	(((ctx) << 3) | (addr >> 61))

# include <यंत्र/page.h>
# अगरndef __ASSEMBLY__

#समावेश <linux/compiler.h>
#समावेश <linux/percpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र-generic/mm_hooks.h>

काष्ठा ia64_ctx अणु
	spinlock_t lock;
	अचिन्हित पूर्णांक next;	/* next context number to use */
	अचिन्हित पूर्णांक limit;     /* available मुक्त range */
	अचिन्हित पूर्णांक max_ctx;   /* max. context value supported by all CPUs */
				/* call wrap_mmu_context when next >= max */
	अचिन्हित दीर्घ *biपंचांगap;  /* biपंचांगap size is max_ctx+1 */
	अचिन्हित दीर्घ *flushmap;/* pending rid to be flushed */
पूर्ण;

बाह्य काष्ठा ia64_ctx ia64_ctx;
DECLARE_PER_CPU(u8, ia64_need_tlb_flush);

बाह्य व्योम mmu_context_init (व्योम);
बाह्य व्योम wrap_mmu_context (काष्ठा mm_काष्ठा *mm);

/*
 * When the context counter wraps around all TLBs need to be flushed because
 * an old context number might have been reused. This is संकेतled by the
 * ia64_need_tlb_flush per-CPU variable, which is checked in the routine
 * below. Called by activate_mm(). <efocht@ess.nec.de>
 */
अटल अंतरभूत व्योम
delayed_tlb_flush (व्योम)
अणु
	बाह्य व्योम local_flush_tlb_all (व्योम);
	अचिन्हित दीर्घ flags;

	अगर (unlikely(__ia64_per_cpu_var(ia64_need_tlb_flush))) अणु
		spin_lock_irqsave(&ia64_ctx.lock, flags);
		अगर (__ia64_per_cpu_var(ia64_need_tlb_flush)) अणु
			local_flush_tlb_all();
			__ia64_per_cpu_var(ia64_need_tlb_flush) = 0;
		पूर्ण
		spin_unlock_irqrestore(&ia64_ctx.lock, flags);
	पूर्ण
पूर्ण

अटल अंतरभूत nv_mm_context_t
get_mmu_context (काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ flags;
	nv_mm_context_t context = mm->context;

	अगर (likely(context))
		जाओ out;

	spin_lock_irqsave(&ia64_ctx.lock, flags);
	/* re-check, now that we've got the lock: */
	context = mm->context;
	अगर (context == 0) अणु
		cpumask_clear(mm_cpumask(mm));
		अगर (ia64_ctx.next >= ia64_ctx.limit) अणु
			ia64_ctx.next = find_next_zero_bit(ia64_ctx.biपंचांगap,
					ia64_ctx.max_ctx, ia64_ctx.next);
			ia64_ctx.limit = find_next_bit(ia64_ctx.biपंचांगap,
					ia64_ctx.max_ctx, ia64_ctx.next);
			अगर (ia64_ctx.next >= ia64_ctx.max_ctx)
				wrap_mmu_context(mm);
		पूर्ण
		mm->context = context = ia64_ctx.next++;
		__set_bit(context, ia64_ctx.biपंचांगap);
	पूर्ण
	spin_unlock_irqrestore(&ia64_ctx.lock, flags);
out:
	/*
	 * Ensure we're not starting to use "context" beक्रमe any old
	 * uses of it are gone from our TLB.
	 */
	delayed_tlb_flush();

	वापस context;
पूर्ण

/*
 * Initialize context number to some sane value.  MM is guaranteed to be a
 * bअक्रम-new address-space, so no TLB flushing is needed, ever.
 */
#घोषणा init_new_context init_new_context
अटल अंतरभूत पूर्णांक
init_new_context (काष्ठा task_काष्ठा *p, काष्ठा mm_काष्ठा *mm)
अणु
	mm->context = 0;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
reload_context (nv_mm_context_t context)
अणु
	अचिन्हित दीर्घ rid;
	अचिन्हित दीर्घ rid_incr = 0;
	अचिन्हित दीर्घ rr0, rr1, rr2, rr3, rr4, old_rr4;

	old_rr4 = ia64_get_rr(RGN_BASE(RGN_HPAGE));
	rid = context << 3;	/* make space क्रम encoding the region number */
	rid_incr = 1 << 8;

	/* encode the region id, preferred page size, and VHPT enable bit: */
	rr0 = (rid << 8) | (PAGE_SHIFT << 2) | 1;
	rr1 = rr0 + 1*rid_incr;
	rr2 = rr0 + 2*rid_incr;
	rr3 = rr0 + 3*rid_incr;
	rr4 = rr0 + 4*rid_incr;
#अगर_घोषित  CONFIG_HUGETLB_PAGE
	rr4 = (rr4 & (~(0xfcUL))) | (old_rr4 & 0xfc);

#  अगर RGN_HPAGE != 4
#    error "reload_context assumes RGN_HPAGE is 4"
#  endअगर
#पूर्ण_अगर

	ia64_set_rr0_to_rr4(rr0, rr1, rr2, rr3, rr4);
	ia64_srlz_i();			/* srlz.i implies srlz.d */
पूर्ण

/*
 * Must be called with preemption off
 */
अटल अंतरभूत व्योम
activate_context (काष्ठा mm_काष्ठा *mm)
अणु
	nv_mm_context_t context;

	करो अणु
		context = get_mmu_context(mm);
		अगर (!cpumask_test_cpu(smp_processor_id(), mm_cpumask(mm)))
			cpumask_set_cpu(smp_processor_id(), mm_cpumask(mm));
		reload_context(context);
		/*
		 * in the unlikely event of a TLB-flush by another thपढ़ो,
		 * reकरो the load.
		 */
	पूर्ण जबतक (unlikely(context != mm->context));
पूर्ण

/*
 * Switch from address space PREV to address space NEXT.
 */
#घोषणा activate_mm activate_mm
अटल अंतरभूत व्योम
activate_mm (काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next)
अणु
	/*
	 * We may get पूर्णांकerrupts here, but that's OK because पूर्णांकerrupt
	 * handlers cannot touch user-space.
	 */
	ia64_set_kr(IA64_KR_PT_BASE, __pa(next->pgd));
	activate_context(next);
पूर्ण

#घोषणा चयन_mm(prev_mm,next_mm,next_task)	activate_mm(prev_mm, next_mm)

#समावेश <यंत्र-generic/mmu_context.h>

# endअगर /* ! __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_IA64_MMU_CONTEXT_H */
