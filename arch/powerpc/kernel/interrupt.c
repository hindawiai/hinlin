<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/context_tracking.h>
#समावेश <linux/err.h>
#समावेश <linux/compat.h>

#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/kup.h>
#समावेश <यंत्र/cpuसमय.स>
#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/संकेत.स>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/syscall.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/unistd.h>

#अगर defined(CONFIG_PPC_ADV_DEBUG_REGS) && defined(CONFIG_PPC32)
अचिन्हित दीर्घ global_dbcr0[NR_CPUS];
#पूर्ण_अगर

प्रकार दीर्घ (*syscall_fn)(दीर्घ, दीर्घ, दीर्घ, दीर्घ, दीर्घ, दीर्घ);

/* Has to run notrace because it is entered not completely "reconciled" */
notrace दीर्घ प्रणाली_call_exception(दीर्घ r3, दीर्घ r4, दीर्घ r5,
				   दीर्घ r6, दीर्घ r7, दीर्घ r8,
				   अचिन्हित दीर्घ r0, काष्ठा pt_regs *regs)
अणु
	syscall_fn f;

	kuep_lock();

	regs->orig_gpr3 = r3;

	अगर (IS_ENABLED(CONFIG_PPC_IRQ_SOFT_MASK_DEBUG))
		BUG_ON(irq_soft_mask_वापस() != IRQS_ALL_DISABLED);

	trace_hardirqs_off(); /* finish reconciling */

	CT_WARN_ON(ct_state() == CONTEXT_KERNEL);
	user_निकास_irqoff();

	अगर (!IS_ENABLED(CONFIG_BOOKE) && !IS_ENABLED(CONFIG_40x))
		BUG_ON(!(regs->msr & MSR_RI));
	BUG_ON(!(regs->msr & MSR_PR));
	BUG_ON(arch_irq_disabled_regs(regs));

#अगर_घोषित CONFIG_PPC_PKEY
	अगर (mmu_has_feature(MMU_FTR_PKEY)) अणु
		अचिन्हित दीर्घ amr, iamr;
		bool flush_needed = false;
		/*
		 * When entering from userspace we mostly have the AMR/IAMR
		 * dअगरferent from kernel शेष values. Hence करोn't compare.
		 */
		amr = mfspr(SPRN_AMR);
		iamr = mfspr(SPRN_IAMR);
		regs->amr  = amr;
		regs->iamr = iamr;
		अगर (mmu_has_feature(MMU_FTR_BOOK3S_KUAP)) अणु
			mtspr(SPRN_AMR, AMR_KUAP_BLOCKED);
			flush_needed = true;
		पूर्ण
		अगर (mmu_has_feature(MMU_FTR_BOOK3S_KUEP)) अणु
			mtspr(SPRN_IAMR, AMR_KUEP_BLOCKED);
			flush_needed = true;
		पूर्ण
		अगर (flush_needed)
			isync();
	पूर्ण अन्यथा
#पूर्ण_अगर
		kuap_निश्चित_locked();

	booke_restore_dbcr0();

	account_cpu_user_entry();

	account_stolen_समय();

	/*
	 * This is not required क्रम the syscall निकास path, but makes the
	 * stack frame look nicer. If this was initialised in the first stack
	 * frame, or अगर the unwinder was taught the first stack frame always
	 * वापसs to user with IRQS_ENABLED, this store could be aव्योमed!
	 */
	irq_soft_mask_regs_set_state(regs, IRQS_ENABLED);

	local_irq_enable();

	अगर (unlikely(current_thपढ़ो_info()->flags & _TIF_SYSCALL_DOTRACE)) अणु
		अगर (unlikely(trap_is_unsupported_scv(regs))) अणु
			/* Unsupported scv vector */
			_exception(संक_अवैध, regs, ILL_ILLOPC, regs->nip);
			वापस regs->gpr[3];
		पूर्ण
		/*
		 * We use the वापस value of करो_syscall_trace_enter() as the
		 * syscall number. If the syscall was rejected क्रम any reason
		 * करो_syscall_trace_enter() वापसs an invalid syscall number
		 * and the test against NR_syscalls will fail and the वापस
		 * value to be used is in regs->gpr[3].
		 */
		r0 = करो_syscall_trace_enter(regs);
		अगर (unlikely(r0 >= NR_syscalls))
			वापस regs->gpr[3];
		r3 = regs->gpr[3];
		r4 = regs->gpr[4];
		r5 = regs->gpr[5];
		r6 = regs->gpr[6];
		r7 = regs->gpr[7];
		r8 = regs->gpr[8];

	पूर्ण अन्यथा अगर (unlikely(r0 >= NR_syscalls)) अणु
		अगर (unlikely(trap_is_unsupported_scv(regs))) अणु
			/* Unsupported scv vector */
			_exception(संक_अवैध, regs, ILL_ILLOPC, regs->nip);
			वापस regs->gpr[3];
		पूर्ण
		वापस -ENOSYS;
	पूर्ण

	/* May be faster to करो array_index_nospec? */
	barrier_nospec();

	अगर (unlikely(is_compat_task())) अणु
		f = (व्योम *)compat_sys_call_table[r0];

		r3 &= 0x00000000ffffffffULL;
		r4 &= 0x00000000ffffffffULL;
		r5 &= 0x00000000ffffffffULL;
		r6 &= 0x00000000ffffffffULL;
		r7 &= 0x00000000ffffffffULL;
		r8 &= 0x00000000ffffffffULL;

	पूर्ण अन्यथा अणु
		f = (व्योम *)sys_call_table[r0];
	पूर्ण

	वापस f(r3, r4, r5, r6, r7, r8);
पूर्ण

/*
 * local irqs must be disabled. Returns false अगर the caller must re-enable
 * them, check क्रम new work, and try again.
 *
 * This should be called with local irqs disabled, but अगर they were previously
 * enabled when the पूर्णांकerrupt handler वापसs (indicating a process-context /
 * synchronous पूर्णांकerrupt) then irqs_enabled should be true.
 */
अटल notrace __always_अंतरभूत bool __prep_irq_क्रम_enabled_निकास(bool clear_ri)
अणु
	/* This must be करोne with RI=1 because tracing may touch vmaps */
	trace_hardirqs_on();

	/* This pattern matches prep_irq_क्रम_idle */
	अगर (clear_ri)
		__hard_EE_RI_disable();
	अन्यथा
		__hard_irq_disable();
#अगर_घोषित CONFIG_PPC64
	अगर (unlikely(lazy_irq_pending_nocheck())) अणु
		/* Took an पूर्णांकerrupt, may have more निकास work to करो. */
		अगर (clear_ri)
			__hard_RI_enable();
		trace_hardirqs_off();
		local_paca->irq_happened |= PACA_IRQ_HARD_DIS;

		वापस false;
	पूर्ण
	local_paca->irq_happened = 0;
	irq_soft_mask_set(IRQS_ENABLED);
#पूर्ण_अगर
	वापस true;
पूर्ण

अटल notrace अंतरभूत bool prep_irq_क्रम_enabled_निकास(bool clear_ri, bool irqs_enabled)
अणु
	अगर (__prep_irq_क्रम_enabled_निकास(clear_ri))
		वापस true;

	/*
	 * Must replay pending soft-masked पूर्णांकerrupts now. Don't just
	 * local_irq_enabe(); local_irq_disable(); because अगर we are
	 * वापसing from an asynchronous पूर्णांकerrupt here, another one
	 * might hit after irqs are enabled, and it would निकास via this
	 * same path allowing another to fire, and so on unbounded.
	 *
	 * If पूर्णांकerrupts were enabled when this पूर्णांकerrupt निकासed,
	 * indicating a process context (synchronous) पूर्णांकerrupt,
	 * local_irq_enable/disable can be used, which will enable
	 * पूर्णांकerrupts rather than keeping them masked (unclear how
	 * much benefit this is over just replaying क्रम all हालs,
	 * because we immediately disable again, so all we're really
	 * करोing is allowing hard पूर्णांकerrupts to execute directly क्रम
	 * a very small समय, rather than being masked and replayed).
	 */
	अगर (irqs_enabled) अणु
		local_irq_enable();
		local_irq_disable();
	पूर्ण अन्यथा अणु
		replay_soft_पूर्णांकerrupts();
	पूर्ण

	वापस false;
पूर्ण

अटल notrace व्योम booke_load_dbcr0(व्योम)
अणु
#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
	अचिन्हित दीर्घ dbcr0 = current->thपढ़ो.debug.dbcr0;

	अगर (likely(!(dbcr0 & DBCR0_IDM)))
		वापस;

	/*
	 * Check to see अगर the dbcr0 रेजिस्टर is set up to debug.
	 * Use the पूर्णांकernal debug mode bit to करो this.
	 */
	mपंचांगsr(mfmsr() & ~MSR_DE);
	अगर (IS_ENABLED(CONFIG_PPC32)) अणु
		isync();
		global_dbcr0[smp_processor_id()] = mfspr(SPRN_DBCR0);
	पूर्ण
	mtspr(SPRN_DBCR0, dbcr0);
	mtspr(SPRN_DBSR, -1);
#पूर्ण_अगर
पूर्ण

/*
 * This should be called after a syscall वापसs, with r3 the वापस value
 * from the syscall. If this function वापसs non-zero, the प्रणाली call
 * निकास assembly should additionally load all GPR रेजिस्टरs and CTR and XER
 * from the पूर्णांकerrupt frame.
 *
 * The function graph tracer can not trace the वापस side of this function,
 * because RI=0 and soft mask state is "unreconciled", so it is marked notrace.
 */
notrace अचिन्हित दीर्घ syscall_निकास_prepare(अचिन्हित दीर्घ r3,
					   काष्ठा pt_regs *regs,
					   दीर्घ scv)
अणु
	अचिन्हित दीर्घ ti_flags;
	अचिन्हित दीर्घ ret = 0;
	bool is_not_scv = !IS_ENABLED(CONFIG_PPC_BOOK3S_64) || !scv;

	CT_WARN_ON(ct_state() == CONTEXT_USER);

	kuap_निश्चित_locked();

	regs->result = r3;

	/* Check whether the syscall is issued inside a restartable sequence */
	rseq_syscall(regs);

	ti_flags = current_thपढ़ो_info()->flags;

	अगर (unlikely(r3 >= (अचिन्हित दीर्घ)-MAX_ERRNO) && is_not_scv) अणु
		अगर (likely(!(ti_flags & (_TIF_NOERROR | _TIF_RESTOREALL)))) अणु
			r3 = -r3;
			regs->ccr |= 0x10000000; /* Set SO bit in CR */
		पूर्ण
	पूर्ण

	अगर (unlikely(ti_flags & _TIF_PERSYSCALL_MASK)) अणु
		अगर (ti_flags & _TIF_RESTOREALL)
			ret = _TIF_RESTOREALL;
		अन्यथा
			regs->gpr[3] = r3;
		clear_bits(_TIF_PERSYSCALL_MASK, &current_thपढ़ो_info()->flags);
	पूर्ण अन्यथा अणु
		regs->gpr[3] = r3;
	पूर्ण

	अगर (unlikely(ti_flags & _TIF_SYSCALL_DOTRACE)) अणु
		करो_syscall_trace_leave(regs);
		ret |= _TIF_RESTOREALL;
	पूर्ण

	local_irq_disable();

again:
	ti_flags = READ_ONCE(current_thपढ़ो_info()->flags);
	जबतक (unlikely(ti_flags & (_TIF_USER_WORK_MASK & ~_TIF_RESTORE_TM))) अणु
		local_irq_enable();
		अगर (ti_flags & _TIF_NEED_RESCHED) अणु
			schedule();
		पूर्ण अन्यथा अणु
			/*
			 * SIGPENDING must restore संकेत handler function
			 * argument GPRs, and some non-अस्थिरs (e.g., r1).
			 * Restore all क्रम now. This could be made lighter.
			 */
			अगर (ti_flags & _TIF_SIGPENDING)
				ret |= _TIF_RESTOREALL;
			करो_notअगरy_resume(regs, ti_flags);
		पूर्ण
		local_irq_disable();
		ti_flags = READ_ONCE(current_thपढ़ो_info()->flags);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_PPC_BOOK3S) && IS_ENABLED(CONFIG_PPC_FPU)) अणु
		अगर (IS_ENABLED(CONFIG_PPC_TRANSACTIONAL_MEM) &&
				unlikely((ti_flags & _TIF_RESTORE_TM))) अणु
			restore_पंचांग_state(regs);
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ mathflags = MSR_FP;

			अगर (cpu_has_feature(CPU_FTR_VSX))
				mathflags |= MSR_VEC | MSR_VSX;
			अन्यथा अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
				mathflags |= MSR_VEC;

			/*
			 * If userspace MSR has all available FP bits set,
			 * then they are live and no need to restore. If not,
			 * it means the regs were given up and restore_math
			 * may decide to restore them (to aव्योम taking an FP
			 * fault).
			 */
			अगर ((regs->msr & mathflags) != mathflags)
				restore_math(regs);
		पूर्ण
	पूर्ण

	user_enter_irqoff();

	/* scv need not set RI=0 because SRRs are not used */
	अगर (unlikely(!__prep_irq_क्रम_enabled_निकास(is_not_scv))) अणु
		user_निकास_irqoff();
		local_irq_enable();
		local_irq_disable();
		जाओ again;
	पूर्ण

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	local_paca->पंचांग_scratch = regs->msr;
#पूर्ण_अगर

	booke_load_dbcr0();

	account_cpu_user_निकास();

	/* Restore user access locks last */
	kuap_user_restore(regs);
	kuep_unlock();

	वापस ret;
पूर्ण

notrace अचिन्हित दीर्घ पूर्णांकerrupt_निकास_user_prepare(काष्ठा pt_regs *regs, अचिन्हित दीर्घ msr)
अणु
	अचिन्हित दीर्घ ti_flags;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ ret = 0;

	अगर (!IS_ENABLED(CONFIG_BOOKE) && !IS_ENABLED(CONFIG_40x))
		BUG_ON(!(regs->msr & MSR_RI));
	BUG_ON(!(regs->msr & MSR_PR));
	BUG_ON(arch_irq_disabled_regs(regs));
	CT_WARN_ON(ct_state() == CONTEXT_USER);

	/*
	 * We करोn't need to restore AMR on the way back to userspace क्रम KUAP.
	 * AMR can only have been unlocked अगर we पूर्णांकerrupted the kernel.
	 */
	kuap_निश्चित_locked();

	local_irq_save(flags);

again:
	ti_flags = READ_ONCE(current_thपढ़ो_info()->flags);
	जबतक (unlikely(ti_flags & (_TIF_USER_WORK_MASK & ~_TIF_RESTORE_TM))) अणु
		local_irq_enable(); /* वापसing to user: may enable */
		अगर (ti_flags & _TIF_NEED_RESCHED) अणु
			schedule();
		पूर्ण अन्यथा अणु
			अगर (ti_flags & _TIF_SIGPENDING)
				ret |= _TIF_RESTOREALL;
			करो_notअगरy_resume(regs, ti_flags);
		पूर्ण
		local_irq_disable();
		ti_flags = READ_ONCE(current_thपढ़ो_info()->flags);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_PPC_BOOK3S_64) && IS_ENABLED(CONFIG_PPC_FPU)) अणु
		अगर (IS_ENABLED(CONFIG_PPC_TRANSACTIONAL_MEM) &&
				unlikely((ti_flags & _TIF_RESTORE_TM))) अणु
			restore_पंचांग_state(regs);
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ mathflags = MSR_FP;

			अगर (cpu_has_feature(CPU_FTR_VSX))
				mathflags |= MSR_VEC | MSR_VSX;
			अन्यथा अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
				mathflags |= MSR_VEC;

			/* See above restore_math comment */
			अगर ((regs->msr & mathflags) != mathflags)
				restore_math(regs);
		पूर्ण
	पूर्ण

	user_enter_irqoff();

	अगर (unlikely(!__prep_irq_क्रम_enabled_निकास(true))) अणु
		user_निकास_irqoff();
		local_irq_enable();
		local_irq_disable();
		जाओ again;
	पूर्ण

	booke_load_dbcr0();

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	local_paca->पंचांग_scratch = regs->msr;
#पूर्ण_अगर

	account_cpu_user_निकास();

	/* Restore user access locks last */
	kuap_user_restore(regs);
	kuep_unlock();

	वापस ret;
पूर्ण

व्योम preempt_schedule_irq(व्योम);

notrace अचिन्हित दीर्घ पूर्णांकerrupt_निकास_kernel_prepare(काष्ठा pt_regs *regs, अचिन्हित दीर्घ msr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ ret = 0;
	अचिन्हित दीर्घ kuap;

	अगर (!IS_ENABLED(CONFIG_BOOKE) && !IS_ENABLED(CONFIG_40x) &&
	    unlikely(!(regs->msr & MSR_RI)))
		unrecoverable_exception(regs);
	BUG_ON(regs->msr & MSR_PR);
	/*
	 * CT_WARN_ON comes here via program_check_exception,
	 * so aव्योम recursion.
	 */
	अगर (TRAP(regs) != INTERRUPT_PROGRAM)
		CT_WARN_ON(ct_state() == CONTEXT_USER);

	kuap = kuap_get_and_निश्चित_locked();

	अगर (unlikely(current_thपढ़ो_info()->flags & _TIF_EMULATE_STACK_STORE)) अणु
		clear_bits(_TIF_EMULATE_STACK_STORE, &current_thपढ़ो_info()->flags);
		ret = 1;
	पूर्ण

	local_irq_save(flags);

	अगर (!arch_irq_disabled_regs(regs)) अणु
		/* Returning to a kernel context with local irqs enabled. */
		WARN_ON_ONCE(!(regs->msr & MSR_EE));
again:
		अगर (IS_ENABLED(CONFIG_PREEMPT)) अणु
			/* Return to preemptible kernel context */
			अगर (unlikely(current_thपढ़ो_info()->flags & _TIF_NEED_RESCHED)) अणु
				अगर (preempt_count() == 0)
					preempt_schedule_irq();
			पूर्ण
		पूर्ण

		अगर (unlikely(!prep_irq_क्रम_enabled_निकास(true, !irqs_disabled_flags(flags))))
			जाओ again;
	पूर्ण अन्यथा अणु
		/* Returning to a kernel context with local irqs disabled. */
		__hard_EE_RI_disable();
#अगर_घोषित CONFIG_PPC64
		अगर (regs->msr & MSR_EE)
			local_paca->irq_happened &= ~PACA_IRQ_HARD_DIS;
#पूर्ण_अगर
	पूर्ण


#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	local_paca->पंचांग_scratch = regs->msr;
#पूर्ण_अगर

	/*
	 * 64s करोes not want to mfspr(SPRN_AMR) here, because this comes after
	 * mपंचांगsr, which would cause Read-After-Write stalls. Hence, take the
	 * AMR value from the check above.
	 */
	kuap_kernel_restore(regs, kuap);

	वापस ret;
पूर्ण
