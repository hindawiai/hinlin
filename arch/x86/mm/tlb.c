<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/init.h>

#समावेश <linux/mm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/export.h>
#समावेश <linux/cpu.h>
#समावेश <linux/debugfs.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/nospec-branch.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/apic.h>

#समावेश "mm_internal.h"

#अगर_घोषित CONFIG_PARAVIRT
# define STATIC_NOPV
#अन्यथा
# define STATIC_NOPV			अटल
# define __flush_tlb_local		native_flush_tlb_local
# define __flush_tlb_global		native_flush_tlb_global
# define __flush_tlb_one_user(addr)	native_flush_tlb_one_user(addr)
# define __flush_tlb_multi(msk, info)	native_flush_tlb_multi(msk, info)
#पूर्ण_अगर

/*
 *	TLB flushing, क्रमmerly SMP-only
 *		c/o Linus Torvalds.
 *
 *	These mean you can really definitely utterly क्रमget about
 *	writing to user space from पूर्णांकerrupts. (Its not allowed anyway).
 *
 *	Optimizations Manfred Spraul <manfred@colorfullअगरe.com>
 *
 *	More scalable flush, from Andi Kleen
 *
 *	Implement flush IPI by CALL_FUNCTION_VECTOR, Alex Shi
 */

/*
 * Use bit 0 to mangle the TIF_SPEC_IB state पूर्णांकo the mm poपूर्णांकer which is
 * stored in cpu_tlb_state.last_user_mm_ibpb.
 */
#घोषणा LAST_USER_MM_IBPB	0x1UL

/*
 * The x86 feature is called PCID (Process Context IDentअगरier). It is similar
 * to what is traditionally called ASID on the RISC processors.
 *
 * We करोn't use the traditional ASID implementation, where each process/mm माला_लो
 * its own ASID and flush/restart when we run out of ASID space.
 *
 * Instead we have a small per-cpu array of ASIDs and cache the last few mm's
 * that came by on this CPU, allowing cheaper चयन_mm between processes on
 * this CPU.
 *
 * We end up with dअगरferent spaces क्रम dअगरferent things. To aव्योम confusion we
 * use dअगरferent names क्रम each of them:
 *
 * ASID  - [0, TLB_NR_DYN_ASIDS-1]
 *         the canonical identअगरier क्रम an mm
 *
 * kPCID - [1, TLB_NR_DYN_ASIDS]
 *         the value we ग_लिखो पूर्णांकo the PCID part of CR3; corresponds to the
 *         ASID+1, because PCID 0 is special.
 *
 * uPCID - [2048 + 1, 2048 + TLB_NR_DYN_ASIDS]
 *         क्रम KPTI each mm has two address spaces and thus needs two
 *         PCID values, but we can still करो with a single ASID denomination
 *         क्रम each mm. Corresponds to kPCID + 2048.
 *
 */

/* There are 12 bits of space क्रम ASIDS in CR3 */
#घोषणा CR3_HW_ASID_BITS		12

/*
 * When enabled, PAGE_TABLE_ISOLATION consumes a single bit क्रम
 * user/kernel चयनes
 */
#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
# define PTI_CONSUMED_PCID_BITS	1
#अन्यथा
# define PTI_CONSUMED_PCID_BITS	0
#पूर्ण_अगर

#घोषणा CR3_AVAIL_PCID_BITS (X86_CR3_PCID_BITS - PTI_CONSUMED_PCID_BITS)

/*
 * ASIDs are zero-based: 0->MAX_AVAIL_ASID are valid.  -1 below to account
 * क्रम them being zero-based.  Another -1 is because PCID 0 is reserved क्रम
 * use by non-PCID-aware users.
 */
#घोषणा MAX_ASID_AVAILABLE ((1 << CR3_AVAIL_PCID_BITS) - 2)

/*
 * Given @asid, compute kPCID
 */
अटल अंतरभूत u16 kern_pcid(u16 asid)
अणु
	VM_WARN_ON_ONCE(asid > MAX_ASID_AVAILABLE);

#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
	/*
	 * Make sure that the dynamic ASID space करोes not conflict with the
	 * bit we are using to चयन between user and kernel ASIDs.
	 */
	BUILD_BUG_ON(TLB_NR_DYN_ASIDS >= (1 << X86_CR3_PTI_PCID_USER_BIT));

	/*
	 * The ASID being passed in here should have respected the
	 * MAX_ASID_AVAILABLE and thus never have the चयन bit set.
	 */
	VM_WARN_ON_ONCE(asid & (1 << X86_CR3_PTI_PCID_USER_BIT));
#पूर्ण_अगर
	/*
	 * The dynamically-asचिन्हित ASIDs that get passed in are small
	 * (<TLB_NR_DYN_ASIDS).  They never have the high चयन bit set,
	 * so करो not bother to clear it.
	 *
	 * If PCID is on, ASID-aware code paths put the ASID+1 पूर्णांकo the
	 * PCID bits.  This serves two purposes.  It prevents a nasty
	 * situation in which PCID-unaware code saves CR3, loads some other
	 * value (with PCID == 0), and then restores CR3, thus corrupting
	 * the TLB क्रम ASID 0 अगर the saved ASID was nonzero.  It also means
	 * that any bugs involving loading a PCID-enabled CR3 with
	 * CR4.PCIDE off will trigger deterministically.
	 */
	वापस asid + 1;
पूर्ण

/*
 * Given @asid, compute uPCID
 */
अटल अंतरभूत u16 user_pcid(u16 asid)
अणु
	u16 ret = kern_pcid(asid);
#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
	ret |= 1 << X86_CR3_PTI_PCID_USER_BIT;
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ build_cr3(pgd_t *pgd, u16 asid)
अणु
	अगर (अटल_cpu_has(X86_FEATURE_PCID)) अणु
		वापस __sme_pa(pgd) | kern_pcid(asid);
	पूर्ण अन्यथा अणु
		VM_WARN_ON_ONCE(asid != 0);
		वापस __sme_pa(pgd);
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ build_cr3_noflush(pgd_t *pgd, u16 asid)
अणु
	VM_WARN_ON_ONCE(asid > MAX_ASID_AVAILABLE);
	/*
	 * Use boot_cpu_has() instead of this_cpu_has() as this function
	 * might be called during early boot. This should work even after
	 * boot because all CPU's the have same capabilities:
	 */
	VM_WARN_ON_ONCE(!boot_cpu_has(X86_FEATURE_PCID));
	वापस __sme_pa(pgd) | kern_pcid(asid) | CR3_NOFLUSH;
पूर्ण

/*
 * We get here when we करो something requiring a TLB invalidation
 * but could not go invalidate all of the contexts.  We करो the
 * necessary invalidation by clearing out the 'ctx_id' which
 * क्रमces a TLB flush when the context is loaded.
 */
अटल व्योम clear_asid_other(व्योम)
अणु
	u16 asid;

	/*
	 * This is only expected to be set अगर we have disabled
	 * kernel _PAGE_GLOBAL pages.
	 */
	अगर (!अटल_cpu_has(X86_FEATURE_PTI)) अणु
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	क्रम (asid = 0; asid < TLB_NR_DYN_ASIDS; asid++) अणु
		/* Do not need to flush the current asid */
		अगर (asid == this_cpu_पढ़ो(cpu_tlbstate.loaded_mm_asid))
			जारी;
		/*
		 * Make sure the next समय we go to चयन to
		 * this asid, we करो a flush:
		 */
		this_cpu_ग_लिखो(cpu_tlbstate.ctxs[asid].ctx_id, 0);
	पूर्ण
	this_cpu_ग_लिखो(cpu_tlbstate.invalidate_other, false);
पूर्ण

atomic64_t last_mm_ctx_id = ATOMIC64_INIT(1);


अटल व्योम choose_new_asid(काष्ठा mm_काष्ठा *next, u64 next_tlb_gen,
			    u16 *new_asid, bool *need_flush)
अणु
	u16 asid;

	अगर (!अटल_cpu_has(X86_FEATURE_PCID)) अणु
		*new_asid = 0;
		*need_flush = true;
		वापस;
	पूर्ण

	अगर (this_cpu_पढ़ो(cpu_tlbstate.invalidate_other))
		clear_asid_other();

	क्रम (asid = 0; asid < TLB_NR_DYN_ASIDS; asid++) अणु
		अगर (this_cpu_पढ़ो(cpu_tlbstate.ctxs[asid].ctx_id) !=
		    next->context.ctx_id)
			जारी;

		*new_asid = asid;
		*need_flush = (this_cpu_पढ़ो(cpu_tlbstate.ctxs[asid].tlb_gen) <
			       next_tlb_gen);
		वापस;
	पूर्ण

	/*
	 * We करोn't currently own an ASID slot on this CPU.
	 * Allocate a slot.
	 */
	*new_asid = this_cpu_add_वापस(cpu_tlbstate.next_asid, 1) - 1;
	अगर (*new_asid >= TLB_NR_DYN_ASIDS) अणु
		*new_asid = 0;
		this_cpu_ग_लिखो(cpu_tlbstate.next_asid, 1);
	पूर्ण
	*need_flush = true;
पूर्ण

/*
 * Given an ASID, flush the corresponding user ASID.  We can delay this
 * until the next समय we चयन to it.
 *
 * See SWITCH_TO_USER_CR3.
 */
अटल अंतरभूत व्योम invalidate_user_asid(u16 asid)
अणु
	/* There is no user ASID अगर address space separation is off */
	अगर (!IS_ENABLED(CONFIG_PAGE_TABLE_ISOLATION))
		वापस;

	/*
	 * We only have a single ASID अगर PCID is off and the CR3
	 * ग_लिखो will have flushed it.
	 */
	अगर (!cpu_feature_enabled(X86_FEATURE_PCID))
		वापस;

	अगर (!अटल_cpu_has(X86_FEATURE_PTI))
		वापस;

	__set_bit(kern_pcid(asid),
		  (अचिन्हित दीर्घ *)this_cpu_ptr(&cpu_tlbstate.user_pcid_flush_mask));
पूर्ण

अटल व्योम load_new_mm_cr3(pgd_t *pgdir, u16 new_asid, bool need_flush)
अणु
	अचिन्हित दीर्घ new_mm_cr3;

	अगर (need_flush) अणु
		invalidate_user_asid(new_asid);
		new_mm_cr3 = build_cr3(pgdir, new_asid);
	पूर्ण अन्यथा अणु
		new_mm_cr3 = build_cr3_noflush(pgdir, new_asid);
	पूर्ण

	/*
	 * Caution: many callers of this function expect
	 * that load_cr3() is serializing and orders TLB
	 * fills with respect to the mm_cpumask ग_लिखोs.
	 */
	ग_लिखो_cr3(new_mm_cr3);
पूर्ण

व्योम leave_mm(पूर्णांक cpu)
अणु
	काष्ठा mm_काष्ठा *loaded_mm = this_cpu_पढ़ो(cpu_tlbstate.loaded_mm);

	/*
	 * It's plausible that we're in lazy TLB mode जबतक our mm is init_mm.
	 * If so, our callers still expect us to flush the TLB, but there
	 * aren't any user TLB entries in init_mm to worry about.
	 *
	 * This needs to happen beक्रमe any other sanity checks due to
	 * पूर्णांकel_idle's shenanigans.
	 */
	अगर (loaded_mm == &init_mm)
		वापस;

	/* Warn अगर we're not lazy. */
	WARN_ON(!this_cpu_पढ़ो(cpu_tlbstate_shared.is_lazy));

	चयन_mm(शून्य, &init_mm, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(leave_mm);

व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
	       काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	चयन_mm_irqs_off(prev, next, tsk);
	local_irq_restore(flags);
पूर्ण

अटल अचिन्हित दीर्घ mm_mangle_tअगर_spec_ib(काष्ठा task_काष्ठा *next)
अणु
	अचिन्हित दीर्घ next_tअगर = task_thपढ़ो_info(next)->flags;
	अचिन्हित दीर्घ ibpb = (next_tअगर >> TIF_SPEC_IB) & LAST_USER_MM_IBPB;

	वापस (अचिन्हित दीर्घ)next->mm | ibpb;
पूर्ण

अटल व्योम cond_ibpb(काष्ठा task_काष्ठा *next)
अणु
	अगर (!next || !next->mm)
		वापस;

	/*
	 * Both, the conditional and the always IBPB mode use the mm
	 * poपूर्णांकer to aव्योम the IBPB when चयनing between tasks of the
	 * same process. Using the mm poपूर्णांकer instead of mm->context.ctx_id
	 * खोलोs a hypothetical hole vs. mm_काष्ठा reuse, which is more or
	 * less impossible to control by an attacker. Aside of that it
	 * would only affect the first schedule so the theoretically
	 * exposed data is not really पूर्णांकeresting.
	 */
	अगर (अटल_branch_likely(&चयन_mm_cond_ibpb)) अणु
		अचिन्हित दीर्घ prev_mm, next_mm;

		/*
		 * This is a bit more complex than the always mode because
		 * it has to handle two हालs:
		 *
		 * 1) Switch from a user space task (potential attacker)
		 *    which has TIF_SPEC_IB set to a user space task
		 *    (potential victim) which has TIF_SPEC_IB not set.
		 *
		 * 2) Switch from a user space task (potential attacker)
		 *    which has TIF_SPEC_IB not set to a user space task
		 *    (potential victim) which has TIF_SPEC_IB set.
		 *
		 * This could be करोne by unconditionally issuing IBPB when
		 * a task which has TIF_SPEC_IB set is either scheduled in
		 * or out. Though that results in two flushes when:
		 *
		 * - the same user space task is scheduled out and later
		 *   scheduled in again and only a kernel thपढ़ो ran in
		 *   between.
		 *
		 * - a user space task beदीर्घing to the same process is
		 *   scheduled in after a kernel thपढ़ो ran in between
		 *
		 * - a user space task beदीर्घing to the same process is
		 *   scheduled in immediately.
		 *
		 * Optimize this with reasonably small overhead क्रम the
		 * above हालs. Mangle the TIF_SPEC_IB bit पूर्णांकo the mm
		 * poपूर्णांकer of the incoming task which is stored in
		 * cpu_tlbstate.last_user_mm_ibpb क्रम comparison.
		 */
		next_mm = mm_mangle_tअगर_spec_ib(next);
		prev_mm = this_cpu_पढ़ो(cpu_tlbstate.last_user_mm_ibpb);

		/*
		 * Issue IBPB only अगर the mm's are dअगरferent and one or
		 * both have the IBPB bit set.
		 */
		अगर (next_mm != prev_mm &&
		    (next_mm | prev_mm) & LAST_USER_MM_IBPB)
			indirect_branch_prediction_barrier();

		this_cpu_ग_लिखो(cpu_tlbstate.last_user_mm_ibpb, next_mm);
	पूर्ण

	अगर (अटल_branch_unlikely(&चयन_mm_always_ibpb)) अणु
		/*
		 * Only flush when चयनing to a user space task with a
		 * dअगरferent context than the user space task which ran
		 * last on this CPU.
		 */
		अगर (this_cpu_पढ़ो(cpu_tlbstate.last_user_mm) != next->mm) अणु
			indirect_branch_prediction_barrier();
			this_cpu_ग_लिखो(cpu_tlbstate.last_user_mm, next->mm);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PERF_EVENTS
अटल अंतरभूत व्योम cr4_update_pce_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (अटल_branch_unlikely(&rdpmc_always_available_key) ||
	    (!अटल_branch_unlikely(&rdpmc_never_available_key) &&
	     atomic_पढ़ो(&mm->context.perf_rdpmc_allowed)))
		cr4_set_bits_irqsoff(X86_CR4_PCE);
	अन्यथा
		cr4_clear_bits_irqsoff(X86_CR4_PCE);
पूर्ण

व्योम cr4_update_pce(व्योम *ignored)
अणु
	cr4_update_pce_mm(this_cpu_पढ़ो(cpu_tlbstate.loaded_mm));
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम cr4_update_pce_mm(काष्ठा mm_काष्ठा *mm) अणु पूर्ण
#पूर्ण_अगर

व्योम चयन_mm_irqs_off(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
			काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा mm_काष्ठा *real_prev = this_cpu_पढ़ो(cpu_tlbstate.loaded_mm);
	u16 prev_asid = this_cpu_पढ़ो(cpu_tlbstate.loaded_mm_asid);
	bool was_lazy = this_cpu_पढ़ो(cpu_tlbstate_shared.is_lazy);
	अचिन्हित cpu = smp_processor_id();
	u64 next_tlb_gen;
	bool need_flush;
	u16 new_asid;

	/*
	 * NB: The scheduler will call us with prev == next when चयनing
	 * from lazy TLB mode to normal mode अगर active_mm isn't changing.
	 * When this happens, we करोn't assume that CR3 (and hence
	 * cpu_tlbstate.loaded_mm) matches next.
	 *
	 * NB: leave_mm() calls us with prev == शून्य and tsk == शून्य.
	 */

	/* We करोn't want flush_tlb_func() to run concurrently with us. */
	अगर (IS_ENABLED(CONFIG_PROVE_LOCKING))
		WARN_ON_ONCE(!irqs_disabled());

	/*
	 * Verअगरy that CR3 is what we think it is.  This will catch
	 * hypothetical buggy code that directly चयनes to swapper_pg_dir
	 * without going through leave_mm() / चयन_mm_irqs_off() or that
	 * करोes something like ग_लिखो_cr3(पढ़ो_cr3_pa()).
	 *
	 * Only करो this check अगर CONFIG_DEBUG_VM=y because __पढ़ो_cr3()
	 * isn't मुक्त.
	 */
#अगर_घोषित CONFIG_DEBUG_VM
	अगर (WARN_ON_ONCE(__पढ़ो_cr3() != build_cr3(real_prev->pgd, prev_asid))) अणु
		/*
		 * If we were to BUG here, we'd be very likely to समाप्त
		 * the प्रणाली so hard that we करोn't see the call trace.
		 * Try to recover instead by ignoring the error and करोing
		 * a global flush to minimize the chance of corruption.
		 *
		 * (This is far from being a fully correct recovery.
		 *  Architecturally, the CPU could prefetch something
		 *  back पूर्णांकo an incorrect ASID slot and leave it there
		 *  to cause trouble करोwn the road.  It's better than
		 *  nothing, though.)
		 */
		__flush_tlb_all();
	पूर्ण
#पूर्ण_अगर
	अगर (was_lazy)
		this_cpu_ग_लिखो(cpu_tlbstate_shared.is_lazy, false);

	/*
	 * The membarrier प्रणाली call requires a full memory barrier and
	 * core serialization beक्रमe वापसing to user-space, after
	 * storing to rq->curr, when changing mm.  This is because
	 * membarrier() sends IPIs to all CPUs that are in the target mm
	 * to make them issue memory barriers.  However, अगर another CPU
	 * चयनes to/from the target mm concurrently with
	 * membarrier(), it can cause that CPU not to receive an IPI
	 * when it really should issue a memory barrier.  Writing to CR3
	 * provides that full memory barrier and core serializing
	 * inकाष्ठाion.
	 */
	अगर (real_prev == next) अणु
		VM_WARN_ON(this_cpu_पढ़ो(cpu_tlbstate.ctxs[prev_asid].ctx_id) !=
			   next->context.ctx_id);

		/*
		 * Even in lazy TLB mode, the CPU should stay set in the
		 * mm_cpumask. The TLB shootकरोwn code can figure out from
		 * cpu_tlbstate_shared.is_lazy whether or not to send an IPI.
		 */
		अगर (WARN_ON_ONCE(real_prev != &init_mm &&
				 !cpumask_test_cpu(cpu, mm_cpumask(next))))
			cpumask_set_cpu(cpu, mm_cpumask(next));

		/*
		 * If the CPU is not in lazy TLB mode, we are just चयनing
		 * from one thपढ़ो in a process to another thपढ़ो in the same
		 * process. No TLB flush required.
		 */
		अगर (!was_lazy)
			वापस;

		/*
		 * Read the tlb_gen to check whether a flush is needed.
		 * If the TLB is up to date, just use it.
		 * The barrier synchronizes with the tlb_gen increment in
		 * the TLB shootकरोwn code.
		 */
		smp_mb();
		next_tlb_gen = atomic64_पढ़ो(&next->context.tlb_gen);
		अगर (this_cpu_पढ़ो(cpu_tlbstate.ctxs[prev_asid].tlb_gen) ==
				next_tlb_gen)
			वापस;

		/*
		 * TLB contents went out of date जबतक we were in lazy
		 * mode. Fall through to the TLB चयनing code below.
		 */
		new_asid = prev_asid;
		need_flush = true;
	पूर्ण अन्यथा अणु
		/*
		 * Aव्योम user/user BTB poisoning by flushing the branch
		 * predictor when चयनing between processes. This stops
		 * one process from करोing Spectre-v2 attacks on another.
		 */
		cond_ibpb(tsk);

		/*
		 * Stop remote flushes क्रम the previous mm.
		 * Skip kernel thपढ़ोs; we never send init_mm TLB flushing IPIs,
		 * but the biपंचांगap manipulation can cause cache line contention.
		 */
		अगर (real_prev != &init_mm) अणु
			VM_WARN_ON_ONCE(!cpumask_test_cpu(cpu,
						mm_cpumask(real_prev)));
			cpumask_clear_cpu(cpu, mm_cpumask(real_prev));
		पूर्ण

		/*
		 * Start remote flushes and then पढ़ो tlb_gen.
		 */
		अगर (next != &init_mm)
			cpumask_set_cpu(cpu, mm_cpumask(next));
		next_tlb_gen = atomic64_पढ़ो(&next->context.tlb_gen);

		choose_new_asid(next, next_tlb_gen, &new_asid, &need_flush);

		/* Let nmi_uaccess_okay() know that we're changing CR3. */
		this_cpu_ग_लिखो(cpu_tlbstate.loaded_mm, LOADED_MM_SWITCHING);
		barrier();
	पूर्ण

	अगर (need_flush) अणु
		this_cpu_ग_लिखो(cpu_tlbstate.ctxs[new_asid].ctx_id, next->context.ctx_id);
		this_cpu_ग_लिखो(cpu_tlbstate.ctxs[new_asid].tlb_gen, next_tlb_gen);
		load_new_mm_cr3(next->pgd, new_asid, true);

		trace_tlb_flush(TLB_FLUSH_ON_TASK_SWITCH, TLB_FLUSH_ALL);
	पूर्ण अन्यथा अणु
		/* The new ASID is alपढ़ोy up to date. */
		load_new_mm_cr3(next->pgd, new_asid, false);

		trace_tlb_flush(TLB_FLUSH_ON_TASK_SWITCH, 0);
	पूर्ण

	/* Make sure we ग_लिखो CR3 beक्रमe loaded_mm. */
	barrier();

	this_cpu_ग_लिखो(cpu_tlbstate.loaded_mm, next);
	this_cpu_ग_लिखो(cpu_tlbstate.loaded_mm_asid, new_asid);

	अगर (next != real_prev) अणु
		cr4_update_pce_mm(next);
		चयन_ldt(real_prev, next);
	पूर्ण
पूर्ण

/*
 * Please ignore the name of this function.  It should be called
 * चयन_to_kernel_thपढ़ो().
 *
 * enter_lazy_tlb() is a hपूर्णांक from the scheduler that we are entering a
 * kernel thपढ़ो or other context without an mm.  Acceptable implementations
 * include करोing nothing whatsoever, चयनing to init_mm, or various clever
 * lazy tricks to try to minimize TLB flushes.
 *
 * The scheduler reserves the right to call enter_lazy_tlb() several बार
 * in a row.  It will notअगरy us that we're going back to a real mm by
 * calling चयन_mm_irqs_off().
 */
व्योम enter_lazy_tlb(काष्ठा mm_काष्ठा *mm, काष्ठा task_काष्ठा *tsk)
अणु
	अगर (this_cpu_पढ़ो(cpu_tlbstate.loaded_mm) == &init_mm)
		वापस;

	this_cpu_ग_लिखो(cpu_tlbstate_shared.is_lazy, true);
पूर्ण

/*
 * Call this when reinitializing a CPU.  It fixes the following potential
 * problems:
 *
 * - The ASID changed from what cpu_tlbstate thinks it is (most likely
 *   because the CPU was taken करोwn and came back up with CR3's PCID
 *   bits clear.  CPU hotplug can करो this.
 *
 * - The TLB contains junk in slots corresponding to inactive ASIDs.
 *
 * - The CPU went so far out to lunch that it may have missed a TLB
 *   flush.
 */
व्योम initialize_tlbstate_and_flush(व्योम)
अणु
	पूर्णांक i;
	काष्ठा mm_काष्ठा *mm = this_cpu_पढ़ो(cpu_tlbstate.loaded_mm);
	u64 tlb_gen = atomic64_पढ़ो(&init_mm.context.tlb_gen);
	अचिन्हित दीर्घ cr3 = __पढ़ो_cr3();

	/* Assert that CR3 alपढ़ोy references the right mm. */
	WARN_ON((cr3 & CR3_ADDR_MASK) != __pa(mm->pgd));

	/*
	 * Assert that CR4.PCIDE is set अगर needed.  (CR4.PCIDE initialization
	 * करोesn't work like other CR4 bits because it can only be set from
	 * दीर्घ mode.)
	 */
	WARN_ON(boot_cpu_has(X86_FEATURE_PCID) &&
		!(cr4_पढ़ो_shaकरोw() & X86_CR4_PCIDE));

	/* Force ASID 0 and क्रमce a TLB flush. */
	ग_लिखो_cr3(build_cr3(mm->pgd, 0));

	/* Reinitialize tlbstate. */
	this_cpu_ग_लिखो(cpu_tlbstate.last_user_mm_ibpb, LAST_USER_MM_IBPB);
	this_cpu_ग_लिखो(cpu_tlbstate.loaded_mm_asid, 0);
	this_cpu_ग_लिखो(cpu_tlbstate.next_asid, 1);
	this_cpu_ग_लिखो(cpu_tlbstate.ctxs[0].ctx_id, mm->context.ctx_id);
	this_cpu_ग_लिखो(cpu_tlbstate.ctxs[0].tlb_gen, tlb_gen);

	क्रम (i = 1; i < TLB_NR_DYN_ASIDS; i++)
		this_cpu_ग_लिखो(cpu_tlbstate.ctxs[i].ctx_id, 0);
पूर्ण

/*
 * flush_tlb_func()'s memory ordering requirement is that any
 * TLB fills that happen after we flush the TLB are ordered after we
 * पढ़ो active_mm's tlb_gen.  We don't need any explicit barriers
 * because all x86 flush operations are serializing and the
 * atomic64_पढ़ो operation won't be reordered by the compiler.
 */
अटल व्योम flush_tlb_func(व्योम *info)
अणु
	/*
	 * We have three dअगरferent tlb_gen values in here.  They are:
	 *
	 * - mm_tlb_gen:     the latest generation.
	 * - local_tlb_gen:  the generation that this CPU has alपढ़ोy caught
	 *                   up to.
	 * - f->new_tlb_gen: the generation that the requester of the flush
	 *                   wants us to catch up to.
	 */
	स्थिर काष्ठा flush_tlb_info *f = info;
	काष्ठा mm_काष्ठा *loaded_mm = this_cpu_पढ़ो(cpu_tlbstate.loaded_mm);
	u32 loaded_mm_asid = this_cpu_पढ़ो(cpu_tlbstate.loaded_mm_asid);
	u64 mm_tlb_gen = atomic64_पढ़ो(&loaded_mm->context.tlb_gen);
	u64 local_tlb_gen = this_cpu_पढ़ो(cpu_tlbstate.ctxs[loaded_mm_asid].tlb_gen);
	bool local = smp_processor_id() == f->initiating_cpu;
	अचिन्हित दीर्घ nr_invalidate = 0;

	/* This code cannot presently handle being reentered. */
	VM_WARN_ON(!irqs_disabled());

	अगर (!local) अणु
		inc_irq_stat(irq_tlb_count);
		count_vm_tlb_event(NR_TLB_REMOTE_FLUSH_RECEIVED);

		/* Can only happen on remote CPUs */
		अगर (f->mm && f->mm != loaded_mm)
			वापस;
	पूर्ण

	अगर (unlikely(loaded_mm == &init_mm))
		वापस;

	VM_WARN_ON(this_cpu_पढ़ो(cpu_tlbstate.ctxs[loaded_mm_asid].ctx_id) !=
		   loaded_mm->context.ctx_id);

	अगर (this_cpu_पढ़ो(cpu_tlbstate_shared.is_lazy)) अणु
		/*
		 * We're in lazy mode.  We need to at least flush our
		 * paging-काष्ठाure cache to aव्योम speculatively पढ़ोing
		 * garbage पूर्णांकo our TLB.  Since चयनing to init_mm is barely
		 * slower than a minimal flush, just चयन to init_mm.
		 *
		 * This should be rare, with native_flush_tlb_multi() skipping
		 * IPIs to lazy TLB mode CPUs.
		 */
		चयन_mm_irqs_off(शून्य, &init_mm, शून्य);
		वापस;
	पूर्ण

	अगर (unlikely(local_tlb_gen == mm_tlb_gen)) अणु
		/*
		 * There's nothing to do: we're alपढ़ोy up to date.  This can
		 * happen अगर two concurrent flushes happen -- the first flush to
		 * be handled can catch us all the way up, leaving no work क्रम
		 * the second flush.
		 */
		जाओ करोne;
	पूर्ण

	WARN_ON_ONCE(local_tlb_gen > mm_tlb_gen);
	WARN_ON_ONCE(f->new_tlb_gen > mm_tlb_gen);

	/*
	 * If we get to this poपूर्णांक, we know that our TLB is out of date.
	 * This करोes not strictly imply that we need to flush (it's
	 * possible that f->new_tlb_gen <= local_tlb_gen), but we're
	 * going to need to flush in the very near future, so we might
	 * as well get it over with.
	 *
	 * The only question is whether to करो a full or partial flush.
	 *
	 * We करो a partial flush अगर requested and two extra conditions
	 * are met:
	 *
	 * 1. f->new_tlb_gen == local_tlb_gen + 1.  We have an invariant that
	 *    we've always करोne all needed flushes to catch up to
	 *    local_tlb_gen.  If, क्रम example, local_tlb_gen == 2 and
	 *    f->new_tlb_gen == 3, then we know that the flush needed to bring
	 *    us up to date क्रम tlb_gen 3 is the partial flush we're
	 *    processing.
	 *
	 *    As an example of why this check is needed, suppose that there
	 *    are two concurrent flushes.  The first is a full flush that
	 *    changes context.tlb_gen from 1 to 2.  The second is a partial
	 *    flush that changes context.tlb_gen from 2 to 3.  If they get
	 *    processed on this CPU in reverse order, we'll see
	 *     local_tlb_gen == 1, mm_tlb_gen == 3, and end != TLB_FLUSH_ALL.
	 *    If we were to use __flush_tlb_one_user() and set local_tlb_gen to
	 *    3, we'd be break the invariant: we'd update local_tlb_gen above
	 *    1 without the full flush that's needed क्रम tlb_gen 2.
	 *
	 * 2. f->new_tlb_gen == mm_tlb_gen.  This is purely an optimization.
	 *    Partial TLB flushes are not all that much cheaper than full TLB
	 *    flushes, so it seems unlikely that it would be a perक्रमmance win
	 *    to करो a partial flush अगर that won't bring our TLB fully up to
	 *    date.  By करोing a full flush instead, we can increase
	 *    local_tlb_gen all the way to mm_tlb_gen and we can probably
	 *    aव्योम another flush in the very near future.
	 */
	अगर (f->end != TLB_FLUSH_ALL &&
	    f->new_tlb_gen == local_tlb_gen + 1 &&
	    f->new_tlb_gen == mm_tlb_gen) अणु
		/* Partial flush */
		अचिन्हित दीर्घ addr = f->start;

		nr_invalidate = (f->end - f->start) >> f->stride_shअगरt;

		जबतक (addr < f->end) अणु
			flush_tlb_one_user(addr);
			addr += 1UL << f->stride_shअगरt;
		पूर्ण
		अगर (local)
			count_vm_tlb_events(NR_TLB_LOCAL_FLUSH_ONE, nr_invalidate);
	पूर्ण अन्यथा अणु
		/* Full flush. */
		nr_invalidate = TLB_FLUSH_ALL;

		flush_tlb_local();
		अगर (local)
			count_vm_tlb_event(NR_TLB_LOCAL_FLUSH_ALL);
	पूर्ण

	/* Both paths above update our state to mm_tlb_gen. */
	this_cpu_ग_लिखो(cpu_tlbstate.ctxs[loaded_mm_asid].tlb_gen, mm_tlb_gen);

	/* Tracing is करोne in a unअगरied manner to reduce the code size */
करोne:
	trace_tlb_flush(!local ? TLB_REMOTE_SHOOTDOWN :
				(f->mm == शून्य) ? TLB_LOCAL_SHOOTDOWN :
						  TLB_LOCAL_MM_SHOOTDOWN,
			nr_invalidate);
पूर्ण

अटल bool tlb_is_not_lazy(पूर्णांक cpu)
अणु
	वापस !per_cpu(cpu_tlbstate_shared.is_lazy, cpu);
पूर्ण

अटल DEFINE_PER_CPU(cpumask_t, flush_tlb_mask);

DEFINE_PER_CPU_SHARED_ALIGNED(काष्ठा tlb_state_shared, cpu_tlbstate_shared);
EXPORT_PER_CPU_SYMBOL(cpu_tlbstate_shared);

STATIC_NOPV व्योम native_flush_tlb_multi(स्थिर काष्ठा cpumask *cpumask,
					 स्थिर काष्ठा flush_tlb_info *info)
अणु
	/*
	 * Do accounting and tracing. Note that there are (and have always been)
	 * हालs in which a remote TLB flush will be traced, but eventually
	 * would not happen.
	 */
	count_vm_tlb_event(NR_TLB_REMOTE_FLUSH);
	अगर (info->end == TLB_FLUSH_ALL)
		trace_tlb_flush(TLB_REMOTE_SEND_IPI, TLB_FLUSH_ALL);
	अन्यथा
		trace_tlb_flush(TLB_REMOTE_SEND_IPI,
				(info->end - info->start) >> PAGE_SHIFT);

	/*
	 * If no page tables were मुक्तd, we can skip sending IPIs to
	 * CPUs in lazy TLB mode. They will flush the CPU themselves
	 * at the next context चयन.
	 *
	 * However, अगर page tables are getting मुक्तd, we need to send the
	 * IPI everywhere, to prevent CPUs in lazy TLB mode from tripping
	 * up on the new contents of what used to be page tables, जबतक
	 * करोing a speculative memory access.
	 */
	अगर (info->मुक्तd_tables) अणु
		on_each_cpu_mask(cpumask, flush_tlb_func, (व्योम *)info, true);
	पूर्ण अन्यथा अणु
		/*
		 * Although we could have used on_each_cpu_cond_mask(),
		 * खोलो-coding it has perक्रमmance advantages, as it eliminates
		 * the need क्रम indirect calls or retpolines. In addition, it
		 * allows to use a designated cpumask क्रम evaluating the
		 * condition, instead of allocating one.
		 *
		 * This code works under the assumption that there are no nested
		 * TLB flushes, an assumption that is alपढ़ोy made in
		 * flush_tlb_mm_range().
		 *
		 * cond_cpumask is logically a stack-local variable, but it is
		 * more efficient to have it off the stack and not to allocate
		 * it on demand. Preemption is disabled and this code is
		 * non-reentrant.
		 */
		काष्ठा cpumask *cond_cpumask = this_cpu_ptr(&flush_tlb_mask);
		पूर्णांक cpu;

		cpumask_clear(cond_cpumask);

		क्रम_each_cpu(cpu, cpumask) अणु
			अगर (tlb_is_not_lazy(cpu))
				__cpumask_set_cpu(cpu, cond_cpumask);
		पूर्ण
		on_each_cpu_mask(cond_cpumask, flush_tlb_func, (व्योम *)info, true);
	पूर्ण
पूर्ण

व्योम flush_tlb_multi(स्थिर काष्ठा cpumask *cpumask,
		      स्थिर काष्ठा flush_tlb_info *info)
अणु
	__flush_tlb_multi(cpumask, info);
पूर्ण

/*
 * See Documentation/x86/tlb.rst क्रम details.  We choose 33
 * because it is large enough to cover the vast majority (at
 * least 95%) of allocations, and is small enough that we are
 * confident it will not cause too much overhead.  Each single
 * flush is about 100 ns, so this caps the maximum overhead at
 * _about_ 3,000 ns.
 *
 * This is in units of pages.
 */
अचिन्हित दीर्घ tlb_single_page_flush_उच्चमानing __पढ़ो_mostly = 33;

अटल DEFINE_PER_CPU_SHARED_ALIGNED(काष्ठा flush_tlb_info, flush_tlb_info);

#अगर_घोषित CONFIG_DEBUG_VM
अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, flush_tlb_info_idx);
#पूर्ण_अगर

अटल काष्ठा flush_tlb_info *get_flush_tlb_info(काष्ठा mm_काष्ठा *mm,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			अचिन्हित पूर्णांक stride_shअगरt, bool मुक्तd_tables,
			u64 new_tlb_gen)
अणु
	काष्ठा flush_tlb_info *info = this_cpu_ptr(&flush_tlb_info);

#अगर_घोषित CONFIG_DEBUG_VM
	/*
	 * Ensure that the following code is non-reentrant and flush_tlb_info
	 * is not overwritten. This means no TLB flushing is initiated by
	 * पूर्णांकerrupt handlers and machine-check exception handlers.
	 */
	BUG_ON(this_cpu_inc_वापस(flush_tlb_info_idx) != 1);
#पूर्ण_अगर

	info->start		= start;
	info->end		= end;
	info->mm		= mm;
	info->stride_shअगरt	= stride_shअगरt;
	info->मुक्तd_tables	= मुक्तd_tables;
	info->new_tlb_gen	= new_tlb_gen;
	info->initiating_cpu	= smp_processor_id();

	वापस info;
पूर्ण

अटल व्योम put_flush_tlb_info(व्योम)
अणु
#अगर_घोषित CONFIG_DEBUG_VM
	/* Complete reentrancy prevention checks */
	barrier();
	this_cpu_dec(flush_tlb_info_idx);
#पूर्ण_अगर
पूर्ण

व्योम flush_tlb_mm_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ end, अचिन्हित पूर्णांक stride_shअगरt,
				bool मुक्तd_tables)
अणु
	काष्ठा flush_tlb_info *info;
	u64 new_tlb_gen;
	पूर्णांक cpu;

	cpu = get_cpu();

	/* Should we flush just the requested range? */
	अगर ((end == TLB_FLUSH_ALL) ||
	    ((end - start) >> stride_shअगरt) > tlb_single_page_flush_उच्चमानing) अणु
		start = 0;
		end = TLB_FLUSH_ALL;
	पूर्ण

	/* This is also a barrier that synchronizes with चयन_mm(). */
	new_tlb_gen = inc_mm_tlb_gen(mm);

	info = get_flush_tlb_info(mm, start, end, stride_shअगरt, मुक्तd_tables,
				  new_tlb_gen);

	/*
	 * flush_tlb_multi() is not optimized क्रम the common हाल in which only
	 * a local TLB flush is needed. Optimize this use-हाल by calling
	 * flush_tlb_func_local() directly in this हाल.
	 */
	अगर (cpumask_any_but(mm_cpumask(mm), cpu) < nr_cpu_ids) अणु
		flush_tlb_multi(mm_cpumask(mm), info);
	पूर्ण अन्यथा अगर (mm == this_cpu_पढ़ो(cpu_tlbstate.loaded_mm)) अणु
		lockdep_निश्चित_irqs_enabled();
		local_irq_disable();
		flush_tlb_func(info);
		local_irq_enable();
	पूर्ण

	put_flush_tlb_info();
	put_cpu();
पूर्ण


अटल व्योम करो_flush_tlb_all(व्योम *info)
अणु
	count_vm_tlb_event(NR_TLB_REMOTE_FLUSH_RECEIVED);
	__flush_tlb_all();
पूर्ण

व्योम flush_tlb_all(व्योम)
अणु
	count_vm_tlb_event(NR_TLB_REMOTE_FLUSH);
	on_each_cpu(करो_flush_tlb_all, शून्य, 1);
पूर्ण

अटल व्योम करो_kernel_range_flush(व्योम *info)
अणु
	काष्ठा flush_tlb_info *f = info;
	अचिन्हित दीर्घ addr;

	/* flush range by one by one 'invlpg' */
	क्रम (addr = f->start; addr < f->end; addr += PAGE_SIZE)
		flush_tlb_one_kernel(addr);
पूर्ण

व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	/* Balance as user space task's flush, a bit conservative */
	अगर (end == TLB_FLUSH_ALL ||
	    (end - start) > tlb_single_page_flush_उच्चमानing << PAGE_SHIFT) अणु
		on_each_cpu(करो_flush_tlb_all, शून्य, 1);
	पूर्ण अन्यथा अणु
		काष्ठा flush_tlb_info *info;

		preempt_disable();
		info = get_flush_tlb_info(शून्य, start, end, 0, false, 0);

		on_each_cpu(करो_kernel_range_flush, info, 1);

		put_flush_tlb_info();
		preempt_enable();
	पूर्ण
पूर्ण

/*
 * This can be used from process context to figure out what the value of
 * CR3 is without needing to करो a (slow) __पढ़ो_cr3().
 *
 * It's पूर्णांकended to be used क्रम code like KVM that sneakily changes CR3
 * and needs to restore it.  It needs to be used very carefully.
 */
अचिन्हित दीर्घ __get_current_cr3_fast(व्योम)
अणु
	अचिन्हित दीर्घ cr3 = build_cr3(this_cpu_पढ़ो(cpu_tlbstate.loaded_mm)->pgd,
		this_cpu_पढ़ो(cpu_tlbstate.loaded_mm_asid));

	/* For now, be very restrictive about when this can be called. */
	VM_WARN_ON(in_nmi() || preemptible());

	VM_BUG_ON(cr3 != __पढ़ो_cr3());
	वापस cr3;
पूर्ण
EXPORT_SYMBOL_GPL(__get_current_cr3_fast);

/*
 * Flush one page in the kernel mapping
 */
व्योम flush_tlb_one_kernel(अचिन्हित दीर्घ addr)
अणु
	count_vm_tlb_event(NR_TLB_LOCAL_FLUSH_ONE);

	/*
	 * If PTI is off, then __flush_tlb_one_user() is just INVLPG or its
	 * paravirt equivalent.  Even with PCID, this is sufficient: we only
	 * use PCID अगर we also use global PTEs क्रम the kernel mapping, and
	 * INVLPG flushes global translations across all address spaces.
	 *
	 * If PTI is on, then the kernel is mapped with non-global PTEs, and
	 * __flush_tlb_one_user() will flush the given address क्रम the current
	 * kernel address space and क्रम its usermode counterpart, but it करोes
	 * not flush it क्रम other address spaces.
	 */
	flush_tlb_one_user(addr);

	अगर (!अटल_cpu_has(X86_FEATURE_PTI))
		वापस;

	/*
	 * See above.  We need to propagate the flush to all other address
	 * spaces.  In principle, we only need to propagate it to kernelmode
	 * address spaces, but the extra bookkeeping we would need is not
	 * worth it.
	 */
	this_cpu_ग_लिखो(cpu_tlbstate.invalidate_other, true);
पूर्ण

/*
 * Flush one page in the user mapping
 */
STATIC_NOPV व्योम native_flush_tlb_one_user(अचिन्हित दीर्घ addr)
अणु
	u32 loaded_mm_asid = this_cpu_पढ़ो(cpu_tlbstate.loaded_mm_asid);

	यंत्र अस्थिर("invlpg (%0)" ::"r" (addr) : "memory");

	अगर (!अटल_cpu_has(X86_FEATURE_PTI))
		वापस;

	/*
	 * Some platक्रमms #GP अगर we call invpcid(type=1/2) beक्रमe CR4.PCIDE=1.
	 * Just use invalidate_user_asid() in हाल we are called early.
	 */
	अगर (!this_cpu_has(X86_FEATURE_INVPCID_SINGLE))
		invalidate_user_asid(loaded_mm_asid);
	अन्यथा
		invpcid_flush_one(user_pcid(loaded_mm_asid), addr);
पूर्ण

व्योम flush_tlb_one_user(अचिन्हित दीर्घ addr)
अणु
	__flush_tlb_one_user(addr);
पूर्ण

/*
 * Flush everything
 */
STATIC_NOPV व्योम native_flush_tlb_global(व्योम)
अणु
	अचिन्हित दीर्घ cr4, flags;

	अगर (अटल_cpu_has(X86_FEATURE_INVPCID)) अणु
		/*
		 * Using INVPCID is considerably faster than a pair of ग_लिखोs
		 * to CR4 sandwiched inside an IRQ flag save/restore.
		 *
		 * Note, this works with CR4.PCIDE=0 or 1.
		 */
		invpcid_flush_all();
		वापस;
	पूर्ण

	/*
	 * Read-modअगरy-ग_लिखो to CR4 - protect it from preemption and
	 * from पूर्णांकerrupts. (Use the raw variant because this code can
	 * be called from deep inside debugging code.)
	 */
	raw_local_irq_save(flags);

	cr4 = this_cpu_पढ़ो(cpu_tlbstate.cr4);
	/* toggle PGE */
	native_ग_लिखो_cr4(cr4 ^ X86_CR4_PGE);
	/* ग_लिखो old PGE again and flush TLBs */
	native_ग_लिखो_cr4(cr4);

	raw_local_irq_restore(flags);
पूर्ण

/*
 * Flush the entire current user mapping
 */
STATIC_NOPV व्योम native_flush_tlb_local(व्योम)
अणु
	/*
	 * Preemption or पूर्णांकerrupts must be disabled to protect the access
	 * to the per CPU variable and to prevent being preempted between
	 * पढ़ो_cr3() and ग_लिखो_cr3().
	 */
	WARN_ON_ONCE(preemptible());

	invalidate_user_asid(this_cpu_पढ़ो(cpu_tlbstate.loaded_mm_asid));

	/* If current->mm == शून्य then the पढ़ो_cr3() "borrows" an mm */
	native_ग_लिखो_cr3(__native_पढ़ो_cr3());
पूर्ण

व्योम flush_tlb_local(व्योम)
अणु
	__flush_tlb_local();
पूर्ण

/*
 * Flush everything
 */
व्योम __flush_tlb_all(व्योम)
अणु
	/*
	 * This is to catch users with enabled preemption and the PGE feature
	 * and करोn't trigger the warning in __native_flush_tlb().
	 */
	VM_WARN_ON_ONCE(preemptible());

	अगर (boot_cpu_has(X86_FEATURE_PGE)) अणु
		__flush_tlb_global();
	पूर्ण अन्यथा अणु
		/*
		 * !PGE -> !PCID (setup_pcid()), thus every flush is total.
		 */
		flush_tlb_local();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__flush_tlb_all);

व्योम arch_tlbbatch_flush(काष्ठा arch_tlbflush_unmap_batch *batch)
अणु
	काष्ठा flush_tlb_info *info;

	पूर्णांक cpu = get_cpu();

	info = get_flush_tlb_info(शून्य, 0, TLB_FLUSH_ALL, 0, false, 0);
	/*
	 * flush_tlb_multi() is not optimized क्रम the common हाल in which only
	 * a local TLB flush is needed. Optimize this use-हाल by calling
	 * flush_tlb_func_local() directly in this हाल.
	 */
	अगर (cpumask_any_but(&batch->cpumask, cpu) < nr_cpu_ids) अणु
		flush_tlb_multi(&batch->cpumask, info);
	पूर्ण अन्यथा अगर (cpumask_test_cpu(cpu, &batch->cpumask)) अणु
		lockdep_निश्चित_irqs_enabled();
		local_irq_disable();
		flush_tlb_func(info);
		local_irq_enable();
	पूर्ण

	cpumask_clear(&batch->cpumask);

	put_flush_tlb_info();
	put_cpu();
पूर्ण

/*
 * Blindly accessing user memory from NMI context can be dangerous
 * अगर we're in the middle of चयनing the current user task or
 * चयनing the loaded mm.  It can also be dangerous अगर we
 * पूर्णांकerrupted some kernel code that was temporarily using a
 * dअगरferent mm.
 */
bool nmi_uaccess_okay(व्योम)
अणु
	काष्ठा mm_काष्ठा *loaded_mm = this_cpu_पढ़ो(cpu_tlbstate.loaded_mm);
	काष्ठा mm_काष्ठा *current_mm = current->mm;

	VM_WARN_ON_ONCE(!loaded_mm);

	/*
	 * The condition we want to check is
	 * current_mm->pgd == __va(पढ़ो_cr3_pa()).  This may be slow, though,
	 * अगर we're running in a VM with shaकरोw paging, and nmi_uaccess_okay()
	 * is supposed to be reasonably fast.
	 *
	 * Instead, we check the almost equivalent but somewhat conservative
	 * condition below, and we rely on the fact that चयन_mm_irqs_off()
	 * sets loaded_mm to LOADED_MM_SWITCHING beक्रमe writing to CR3.
	 */
	अगर (loaded_mm != current_mm)
		वापस false;

	VM_WARN_ON_ONCE(current_mm->pgd != __va(पढ़ो_cr3_pa()));

	वापस true;
पूर्ण

अटल sमाप_प्रकार tlbflush_पढ़ो_file(काष्ठा file *file, अक्षर __user *user_buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[32];
	अचिन्हित पूर्णांक len;

	len = प्र_लिखो(buf, "%ld\n", tlb_single_page_flush_उच्चमानing);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार tlbflush_ग_लिखो_file(काष्ठा file *file,
		 स्थिर अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[32];
	sमाप_प्रकार len;
	पूर्णांक उच्चमानing;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kstrtoपूर्णांक(buf, 0, &उच्चमानing))
		वापस -EINVAL;

	अगर (उच्चमानing < 0)
		वापस -EINVAL;

	tlb_single_page_flush_उच्चमानing = उच्चमानing;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_tlbflush = अणु
	.पढ़ो = tlbflush_पढ़ो_file,
	.ग_लिखो = tlbflush_ग_लिखो_file,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक __init create_tlb_single_page_flush_उच्चमानing(व्योम)
अणु
	debugfs_create_file("tlb_single_page_flush_ceiling", S_IRUSR | S_IWUSR,
			    arch_debugfs_dir, शून्य, &fops_tlbflush);
	वापस 0;
पूर्ण
late_initcall(create_tlb_single_page_flush_उच्चमानing);
