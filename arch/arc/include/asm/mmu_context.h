<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * vineetg: May 2011
 *  -Refactored get_new_mmu_context( ) to only handle live-mm.
 *   retiring-mm handled in other hooks
 *
 * Vineetg: March 25th, 2008: Bug #92690
 *  -Major reग_लिखो of Core ASID allocation routine get_new_mmu_context
 *
 * Amit Bhor, Sameer Dhavale: Codito Technologies 2004
 */

#अगर_अघोषित _ASM_ARC_MMU_CONTEXT_H
#घोषणा _ASM_ARC_MMU_CONTEXT_H

#समावेश <यंत्र/arcregs.h>
#समावेश <यंत्र/tlb.h>
#समावेश <linux/sched/mm.h>

#समावेश <यंत्र-generic/mm_hooks.h>

/*		ARC700 ASID Management
 *
 * ARC MMU provides 8-bit ASID (0..255) to TAG TLB entries, allowing entries
 * with same vaddr (dअगरferent tasks) to co-निकास. This provides क्रम
 * "Fast Context Switch" i.e. no TLB flush on ctxt-चयन
 *
 * Linux assigns each task a unique ASID. A simple round-robin allocation
 * of H/w ASID is करोne using software tracker @asid_cpu.
 * When it reaches max 255, the allocation cycle starts afresh by flushing
 * the entire TLB and wrapping ASID back to zero.
 *
 * A new allocation cycle, post rollover, could potentially reassign an ASID
 * to a dअगरferent task. Thus the rule is to refresh the ASID in a new cycle.
 * The 32 bit @asid_cpu (and mm->asid) have 8 bits MMU PID and rest 24 bits
 * serve as cycle/generation indicator and natural 32 bit अचिन्हित math
 * स्वतःmagically increments the generation when lower 8 bits rollover.
 */

#घोषणा MM_CTXT_ASID_MASK	0x000000ff /* MMU PID reg :8 bit PID */
#घोषणा MM_CTXT_CYCLE_MASK	(~MM_CTXT_ASID_MASK)

#घोषणा MM_CTXT_FIRST_CYCLE	(MM_CTXT_ASID_MASK + 1)
#घोषणा MM_CTXT_NO_ASID		0UL

#घोषणा asid_mm(mm, cpu)	mm->context.asid[cpu]
#घोषणा hw_pid(mm, cpu)		(asid_mm(mm, cpu) & MM_CTXT_ASID_MASK)

DECLARE_PER_CPU(अचिन्हित पूर्णांक, asid_cache);
#घोषणा asid_cpu(cpu)		per_cpu(asid_cache, cpu)

/*
 * Get a new ASID अगर task करोesn't have a valid one (unalloc or from prev cycle)
 * Also set the MMU PID रेजिस्टर to existing/updated ASID
 */
अटल अंतरभूत व्योम get_new_mmu_context(काष्ठा mm_काष्ठा *mm)
अणु
	स्थिर अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/*
	 * Move to new ASID अगर it was not from current alloc-cycle/generation.
	 * This is करोne by ensuring that the generation bits in both mm->ASID
	 * and cpu's ASID counter are exactly same.
	 *
	 * Note: Callers needing new ASID unconditionally, independent of
	 * 	 generation, e.g. local_flush_tlb_mm() क्रम विभाजनing  parent,
	 * 	 first need to destroy the context, setting it to invalid
	 * 	 value.
	 */
	अगर (!((asid_mm(mm, cpu) ^ asid_cpu(cpu)) & MM_CTXT_CYCLE_MASK))
		जाओ set_hw;

	/* move to new ASID and handle rollover */
	अगर (unlikely(!(++asid_cpu(cpu) & MM_CTXT_ASID_MASK))) अणु

		local_flush_tlb_all();

		/*
		 * Above check क्रम rollover of 8 bit ASID in 32 bit container.
		 * If the container itself wrapped around, set it to a non zero
		 * "generation" to distinguish from no context
		 */
		अगर (!asid_cpu(cpu))
			asid_cpu(cpu) = MM_CTXT_FIRST_CYCLE;
	पूर्ण

	/* Assign new ASID to tsk */
	asid_mm(mm, cpu) = asid_cpu(cpu);

set_hw:
	ग_लिखो_aux_reg(ARC_REG_PID, hw_pid(mm, cpu) | MMU_ENABLE);

	local_irq_restore(flags);
पूर्ण

/*
 * Initialize the context related info क्रम a new mm_काष्ठा
 * instance.
 */
#घोषणा init_new_context init_new_context
अटल अंतरभूत पूर्णांक
init_new_context(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i)
		asid_mm(mm, i) = MM_CTXT_NO_ASID;

	वापस 0;
पूर्ण

#घोषणा destroy_context destroy_context
अटल अंतरभूत व्योम destroy_context(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ flags;

	/* Needed to elide CONFIG_DEBUG_PREEMPT warning */
	local_irq_save(flags);
	asid_mm(mm, smp_processor_id()) = MM_CTXT_NO_ASID;
	local_irq_restore(flags);
पूर्ण

/* Prepare the MMU क्रम task: setup PID reg with allocated ASID
    If task करोesn't have an ASID (never alloc or stolen, get a new ASID)
*/
अटल अंतरभूत व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
			     काष्ठा task_काष्ठा *tsk)
अणु
	स्थिर पूर्णांक cpu = smp_processor_id();

	/*
	 * Note that the mm_cpumask is "aggregating" only, we करोn't clear it
	 * क्रम the चयनed-out task, unlike some other arches.
	 * It is used to enlist cpus क्रम sending TLB flush IPIs and not sending
	 * it to CPUs where a task once ran-on, could cause stale TLB entry
	 * re-use, specially क्रम a multi-thपढ़ोed task.
	 * e.g. T1 runs on C1, migrates to C3. T2 running on C2 munmaps.
	 *      For a non-aggregating mm_cpumask, IPI not sent C1, and अगर T1
	 *      were to re-migrate to C1, it could access the unmapped region
	 *      via any existing stale TLB entries.
	 */
	cpumask_set_cpu(cpu, mm_cpumask(next));

#अगर_घोषित ARC_USE_SCRATCH_REG
	/* PGD cached in MMU reg to aव्योम 3 mem lookups: task->mm->pgd */
	ग_लिखो_aux_reg(ARC_REG_SCRATCH_DATA0, next->pgd);
#पूर्ण_अगर

	get_new_mmu_context(next);
पूर्ण

/*
 * activate_mm शेषs (in यंत्र-generic) to चयन_mm and is called at the
 * समय of execve() to get a new ASID Note the subtlety here:
 * get_new_mmu_context() behaves dअगरferently here vs. in चयन_mm(). Here
 * it always वापसs a new ASID, because mm has an unallocated "initial"
 * value, जबतक in latter, it moves to a new ASID, only अगर it was
 * unallocated
 */

/* it seemed that deactivate_mm( ) is a reasonable place to करो book-keeping
 * क्रम retiring-mm. However destroy_context( ) still needs to करो that because
 * between mm_release( ) = >deactive_mm( ) and
 * mmput => .. => __mmdrop( ) => destroy_context( )
 * there is a good chance that task माला_लो sched-out/in, making it's ASID valid
 * again (this teased me क्रम a whole day).
 */

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर /* __ASM_ARC_MMU_CONTEXT_H */
