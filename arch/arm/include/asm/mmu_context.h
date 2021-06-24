<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/mmu_context.h
 *
 *  Copyright (C) 1996 Russell King.
 *
 *  Changelog:
 *   27-06-1996	RMK	Created
 */
#अगर_अघोषित __ASM_ARM_MMU_CONTEXT_H
#घोषणा __ASM_ARM_MMU_CONTEXT_H

#समावेश <linux/compiler.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/preempt.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cachetype.h>
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र-generic/mm_hooks.h>

व्योम __check_vदो_स्मृति_seq(काष्ठा mm_काष्ठा *mm);

#अगर_घोषित CONFIG_CPU_HAS_ASID

व्योम check_and_चयन_context(काष्ठा mm_काष्ठा *mm, काष्ठा task_काष्ठा *tsk);

#घोषणा init_new_context init_new_context
अटल अंतरभूत पूर्णांक
init_new_context(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm)
अणु
	atomic64_set(&mm->context.id, 0);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ARM_ERRATA_798181
व्योम a15_erratum_get_cpumask(पूर्णांक this_cpu, काष्ठा mm_काष्ठा *mm,
			     cpumask_t *mask);
#अन्यथा  /* !CONFIG_ARM_ERRATA_798181 */
अटल अंतरभूत व्योम a15_erratum_get_cpumask(पूर्णांक this_cpu, काष्ठा mm_काष्ठा *mm,
					   cpumask_t *mask)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ARM_ERRATA_798181 */

#अन्यथा	/* !CONFIG_CPU_HAS_ASID */

#अगर_घोषित CONFIG_MMU

अटल अंतरभूत व्योम check_and_चयन_context(काष्ठा mm_काष्ठा *mm,
					    काष्ठा task_काष्ठा *tsk)
अणु
	अगर (unlikely(mm->context.vदो_स्मृति_seq != init_mm.context.vदो_स्मृति_seq))
		__check_vदो_स्मृति_seq(mm);

	अगर (irqs_disabled())
		/*
		 * cpu_चयन_mm() needs to flush the VIVT caches. To aव्योम
		 * high पूर्णांकerrupt latencies, defer the call and जारी
		 * running with the old mm. Since we only support UP प्रणालीs
		 * on non-ASID CPUs, the old mm will reमुख्य valid until the
		 * finish_arch_post_lock_चयन() call.
		 */
		mm->context.चयन_pending = 1;
	अन्यथा
		cpu_चयन_mm(mm->pgd, mm);
पूर्ण

#अगर_अघोषित MODULE
#घोषणा finish_arch_post_lock_चयन \
	finish_arch_post_lock_चयन
अटल अंतरभूत व्योम finish_arch_post_lock_चयन(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;

	अगर (mm && mm->context.चयन_pending) अणु
		/*
		 * Preemption must be disabled during cpu_चयन_mm() as we
		 * have some stateful cache flush implementations. Check
		 * चयन_pending again in हाल we were preempted and the
		 * चयन to this mm was alपढ़ोy करोne.
		 */
		preempt_disable();
		अगर (mm->context.चयन_pending) अणु
			mm->context.चयन_pending = 0;
			cpu_चयन_mm(mm->pgd, mm);
		पूर्ण
		preempt_enable_no_resched();
	पूर्ण
पूर्ण
#पूर्ण_अगर /* !MODULE */

#पूर्ण_अगर	/* CONFIG_MMU */

#पूर्ण_अगर	/* CONFIG_CPU_HAS_ASID */

#घोषणा activate_mm(prev,next)		चयन_mm(prev, next, शून्य)

/*
 * This is the actual mm चयन as far as the scheduler
 * is concerned.  No रेजिस्टरs are touched.  We aव्योम
 * calling the CPU specअगरic function when the mm hasn't
 * actually changed.
 */
अटल अंतरभूत व्योम
चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
	  काष्ठा task_काष्ठा *tsk)
अणु
#अगर_घोषित CONFIG_MMU
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	/*
	 * __sync_icache_dcache करोesn't broadcast the I-cache invalidation,
	 * so check क्रम possible thपढ़ो migration and invalidate the I-cache
	 * अगर we're new to this CPU.
	 */
	अगर (cache_ops_need_broadcast() &&
	    !cpumask_empty(mm_cpumask(next)) &&
	    !cpumask_test_cpu(cpu, mm_cpumask(next)))
		__flush_icache_all();

	अगर (!cpumask_test_and_set_cpu(cpu, mm_cpumask(next)) || prev != next) अणु
		check_and_चयन_context(next, tsk);
		अगर (cache_is_vivt())
			cpumask_clear_cpu(cpu, mm_cpumask(prev));
	पूर्ण
#पूर्ण_अगर
पूर्ण

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर
