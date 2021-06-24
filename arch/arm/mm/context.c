<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mm/context.c
 *
 *  Copyright (C) 2002-2003 Deep Blue Solutions Ltd, all rights reserved.
 *  Copyright (C) 2012 ARM Limited
 *
 *  Author: Will Deacon <will.deacon@arm.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/percpu.h>

#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/thपढ़ो_notअगरy.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/proc-fns.h>

/*
 * On ARMv6, we have the following काष्ठाure in the Context ID:
 *
 * 31                         7          0
 * +-------------------------+-----------+
 * |      process ID         |   ASID    |
 * +-------------------------+-----------+
 * |              context ID             |
 * +-------------------------------------+
 *
 * The ASID is used to tag entries in the CPU caches and TLBs.
 * The context ID is used by debuggers and trace logic, and
 * should be unique within all running processes.
 *
 * In big endian operation, the two 32 bit words are swapped अगर accessed
 * by non-64-bit operations.
 */
#घोषणा ASID_FIRST_VERSION	(1ULL << ASID_BITS)
#घोषणा NUM_USER_ASIDS		ASID_FIRST_VERSION

अटल DEFINE_RAW_SPINLOCK(cpu_asid_lock);
अटल atomic64_t asid_generation = ATOMIC64_INIT(ASID_FIRST_VERSION);
अटल DECLARE_BITMAP(asid_map, NUM_USER_ASIDS);

अटल DEFINE_PER_CPU(atomic64_t, active_asids);
अटल DEFINE_PER_CPU(u64, reserved_asids);
अटल cpumask_t tlb_flush_pending;

#अगर_घोषित CONFIG_ARM_ERRATA_798181
व्योम a15_erratum_get_cpumask(पूर्णांक this_cpu, काष्ठा mm_काष्ठा *mm,
			     cpumask_t *mask)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags;
	u64 context_id, asid;

	raw_spin_lock_irqsave(&cpu_asid_lock, flags);
	context_id = mm->context.id.counter;
	क्रम_each_online_cpu(cpu) अणु
		अगर (cpu == this_cpu)
			जारी;
		/*
		 * We only need to send an IPI अगर the other CPUs are
		 * running the same ASID as the one being invalidated.
		 */
		asid = per_cpu(active_asids, cpu).counter;
		अगर (asid == 0)
			asid = per_cpu(reserved_asids, cpu);
		अगर (context_id == asid)
			cpumask_set_cpu(cpu, mask);
	पूर्ण
	raw_spin_unlock_irqrestore(&cpu_asid_lock, flags);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM_LPAE
/*
 * With LPAE, the ASID and page tables are updated atomicly, so there is
 * no need क्रम a reserved set of tables (the active ASID tracking prevents
 * any issues across a rollover).
 */
#घोषणा cpu_set_reserved_ttbr0()
#अन्यथा
अटल व्योम cpu_set_reserved_ttbr0(व्योम)
अणु
	u32 ttb;
	/*
	 * Copy TTBR1 पूर्णांकo TTBR0.
	 * This poपूर्णांकs at swapper_pg_dir, which contains only global
	 * entries so any speculative walks are perfectly safe.
	 */
	यंत्र अस्थिर(
	"	mrc	p15, 0, %0, c2, c0, 1		@ read TTBR1\n"
	"	mcr	p15, 0, %0, c2, c0, 0		@ set TTBR0\n"
	: "=r" (ttb));
	isb();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PID_IN_CONTEXTIDR
अटल पूर्णांक contextidr_notअगरier(काष्ठा notअगरier_block *unused, अचिन्हित दीर्घ cmd,
			       व्योम *t)
अणु
	u32 contextidr;
	pid_t pid;
	काष्ठा thपढ़ो_info *thपढ़ो = t;

	अगर (cmd != THREAD_NOTIFY_SWITCH)
		वापस NOTIFY_DONE;

	pid = task_pid_nr(thपढ़ो->task) << ASID_BITS;
	यंत्र अस्थिर(
	"	mrc	p15, 0, %0, c13, c0, 1\n"
	"	and	%0, %0, %2\n"
	"	orr	%0, %0, %1\n"
	"	mcr	p15, 0, %0, c13, c0, 1\n"
	: "=r" (contextidr), "+r" (pid)
	: "I" (~ASID_MASK));
	isb();

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block contextidr_notअगरier_block = अणु
	.notअगरier_call = contextidr_notअगरier,
पूर्ण;

अटल पूर्णांक __init contextidr_notअगरier_init(व्योम)
अणु
	वापस thपढ़ो_रेजिस्टर_notअगरier(&contextidr_notअगरier_block);
पूर्ण
arch_initcall(contextidr_notअगरier_init);
#पूर्ण_अगर

अटल व्योम flush_context(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक i;
	u64 asid;

	/* Update the list of reserved ASIDs and the ASID biपंचांगap. */
	biपंचांगap_clear(asid_map, 0, NUM_USER_ASIDS);
	क्रम_each_possible_cpu(i) अणु
		asid = atomic64_xchg(&per_cpu(active_asids, i), 0);
		/*
		 * If this CPU has alपढ़ोy been through a
		 * rollover, but hasn't run another task in
		 * the meanसमय, we must preserve its reserved
		 * ASID, as this is the only trace we have of
		 * the process it is still running.
		 */
		अगर (asid == 0)
			asid = per_cpu(reserved_asids, i);
		__set_bit(asid & ~ASID_MASK, asid_map);
		per_cpu(reserved_asids, i) = asid;
	पूर्ण

	/* Queue a TLB invalidate and flush the I-cache अगर necessary. */
	cpumask_setall(&tlb_flush_pending);

	अगर (icache_is_vivt_asid_tagged())
		__flush_icache_all();
पूर्ण

अटल bool check_update_reserved_asid(u64 asid, u64 newasid)
अणु
	पूर्णांक cpu;
	bool hit = false;

	/*
	 * Iterate over the set of reserved ASIDs looking क्रम a match.
	 * If we find one, then we can update our mm to use newasid
	 * (i.e. the same ASID in the current generation) but we can't
	 * निकास the loop early, since we need to ensure that all copies
	 * of the old ASID are updated to reflect the mm. Failure to करो
	 * so could result in us missing the reserved ASID in a future
	 * generation.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		अगर (per_cpu(reserved_asids, cpu) == asid) अणु
			hit = true;
			per_cpu(reserved_asids, cpu) = newasid;
		पूर्ण
	पूर्ण

	वापस hit;
पूर्ण

अटल u64 new_context(काष्ठा mm_काष्ठा *mm, अचिन्हित पूर्णांक cpu)
अणु
	अटल u32 cur_idx = 1;
	u64 asid = atomic64_पढ़ो(&mm->context.id);
	u64 generation = atomic64_पढ़ो(&asid_generation);

	अगर (asid != 0) अणु
		u64 newasid = generation | (asid & ~ASID_MASK);

		/*
		 * If our current ASID was active during a rollover, we
		 * can जारी to use it and this was just a false alarm.
		 */
		अगर (check_update_reserved_asid(asid, newasid))
			वापस newasid;

		/*
		 * We had a valid ASID in a previous lअगरe, so try to re-use
		 * it अगर possible.,
		 */
		asid &= ~ASID_MASK;
		अगर (!__test_and_set_bit(asid, asid_map))
			वापस newasid;
	पूर्ण

	/*
	 * Allocate a मुक्त ASID. If we can't find one, take a note of the
	 * currently active ASIDs and mark the TLBs as requiring flushes.
	 * We always count from ASID #1, as we reserve ASID #0 to चयन
	 * via TTBR0 and to aव्योम speculative page table walks from hitting
	 * in any partial walk caches, which could be populated from
	 * overlapping level-1 descriptors used to map both the module
	 * area and the userspace stack.
	 */
	asid = find_next_zero_bit(asid_map, NUM_USER_ASIDS, cur_idx);
	अगर (asid == NUM_USER_ASIDS) अणु
		generation = atomic64_add_वापस(ASID_FIRST_VERSION,
						 &asid_generation);
		flush_context(cpu);
		asid = find_next_zero_bit(asid_map, NUM_USER_ASIDS, 1);
	पूर्ण

	__set_bit(asid, asid_map);
	cur_idx = asid;
	cpumask_clear(mm_cpumask(mm));
	वापस asid | generation;
पूर्ण

व्योम check_and_चयन_context(काष्ठा mm_काष्ठा *mm, काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	u64 asid;

	अगर (unlikely(mm->context.vदो_स्मृति_seq != init_mm.context.vदो_स्मृति_seq))
		__check_vदो_स्मृति_seq(mm);

	/*
	 * We cannot update the pgd and the ASID atomicly with classic
	 * MMU, so चयन exclusively to global mappings to aव्योम
	 * speculative page table walking with the wrong TTBR.
	 */
	cpu_set_reserved_ttbr0();

	asid = atomic64_पढ़ो(&mm->context.id);
	अगर (!((asid ^ atomic64_पढ़ो(&asid_generation)) >> ASID_BITS)
	    && atomic64_xchg(&per_cpu(active_asids, cpu), asid))
		जाओ चयन_mm_fastpath;

	raw_spin_lock_irqsave(&cpu_asid_lock, flags);
	/* Check that our ASID beदीर्घs to the current generation. */
	asid = atomic64_पढ़ो(&mm->context.id);
	अगर ((asid ^ atomic64_पढ़ो(&asid_generation)) >> ASID_BITS) अणु
		asid = new_context(mm, cpu);
		atomic64_set(&mm->context.id, asid);
	पूर्ण

	अगर (cpumask_test_and_clear_cpu(cpu, &tlb_flush_pending)) अणु
		local_flush_bp_all();
		local_flush_tlb_all();
	पूर्ण

	atomic64_set(&per_cpu(active_asids, cpu), asid);
	cpumask_set_cpu(cpu, mm_cpumask(mm));
	raw_spin_unlock_irqrestore(&cpu_asid_lock, flags);

चयन_mm_fastpath:
	cpu_चयन_mm(mm->pgd, mm);
पूर्ण
