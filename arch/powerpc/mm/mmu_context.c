<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Common implementation of चयन_mm_irqs_off
 *
 *  Copyright IBM Corp. 2017
 */

#समावेश <linux/mm.h>
#समावेश <linux/cpu.h>
#समावेश <linux/sched/mm.h>

#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/pgभाग.स>

#अगर defined(CONFIG_PPC32)
अटल अंतरभूत व्योम चयन_mm_pgdir(काष्ठा task_काष्ठा *tsk,
				   काष्ठा mm_काष्ठा *mm)
अणु
	/* 32-bit keeps track of the current PGसूची in the thपढ़ो काष्ठा */
	tsk->thपढ़ो.pgdir = mm->pgd;
पूर्ण
#या_अगर defined(CONFIG_PPC_BOOK3E_64)
अटल अंतरभूत व्योम चयन_mm_pgdir(काष्ठा task_काष्ठा *tsk,
				   काष्ठा mm_काष्ठा *mm)
अणु
	/* 64-bit Book3E keeps track of current PGD in the PACA */
	get_paca()->pgd = mm->pgd;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम चयन_mm_pgdir(काष्ठा task_काष्ठा *tsk,
				   काष्ठा mm_काष्ठा *mm) अणु पूर्ण
#पूर्ण_अगर

व्योम चयन_mm_irqs_off(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
			काष्ठा task_काष्ठा *tsk)
अणु
	bool new_on_cpu = false;

	/* Mark this context has been used on the new CPU */
	अगर (!cpumask_test_cpu(smp_processor_id(), mm_cpumask(next))) अणु
		cpumask_set_cpu(smp_processor_id(), mm_cpumask(next));
		inc_mm_active_cpus(next);

		/*
		 * This full barrier orders the store to the cpumask above vs
		 * a subsequent load which allows this CPU/MMU to begin loading
		 * translations क्रम 'next' from page table PTEs पूर्णांकo the TLB.
		 *
		 * When using the radix MMU, that operation is the load of the
		 * MMU context id, which is then moved to SPRN_PID.
		 *
		 * For the hash MMU it is either the first load from slb_cache
		 * in चयन_slb() to preload the SLBs, or the load of
		 * get_user_context which loads the context क्रम the VSID hash
		 * to insert a new SLB, in the SLB fault handler.
		 *
		 * On the other side, the barrier is in mm/tlb-radix.c क्रम
		 * radix which orders earlier stores to clear the PTEs beक्रमe
		 * the load of mm_cpumask to check which CPU TLBs should be
		 * flushed. For hash, pte_xchg to clear the PTE includes the
		 * barrier.
		 *
		 * This full barrier is also needed by membarrier when
		 * चयनing between processes after store to rq->curr, beक्रमe
		 * user-space memory accesses.
		 */
		smp_mb();

		new_on_cpu = true;
	पूर्ण

	/* Some subarchs need to track the PGD अन्यथाwhere */
	चयन_mm_pgdir(tsk, next);

	/* Nothing अन्यथा to करो अगर we aren't actually चयनing */
	अगर (prev == next)
		वापस;

	/*
	 * We must stop all altivec streams beक्रमe changing the HW
	 * context
	 */
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		यंत्र अस्थिर ("dssall");

	अगर (new_on_cpu)
		radix_kvm_prefetch_workaround(next);
	अन्यथा
		membarrier_arch_चयन_mm(prev, next, tsk);

	/*
	 * The actual HW चयनing method dअगरfers between the various
	 * sub architectures. Out of line क्रम now
	 */
	चयन_mmu_context(prev, next, tsk);
पूर्ण

#अगर_अघोषित CONFIG_PPC_BOOK3S_64
व्योम arch_निकास_mmap(काष्ठा mm_काष्ठा *mm)
अणु
	व्योम *frag = pte_frag_get(&mm->context);

	अगर (frag)
		pte_frag_destroy(frag);
पूर्ण
#पूर्ण_अगर
