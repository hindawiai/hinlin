<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Exception handling code
 *
 * Copyright (C) 2019 ARM Ltd.
 */

#समावेश <linux/context_tracking.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/thपढ़ो_info.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/daअगरflags.h>
#समावेश <यंत्र/esr.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/sysreg.h>

/*
 * This is पूर्णांकended to match the logic in irqentry_enter(), handling the kernel
 * mode transitions only.
 */
अटल व्योम noinstr enter_from_kernel_mode(काष्ठा pt_regs *regs)
अणु
	regs->निकास_rcu = false;

	अगर (!IS_ENABLED(CONFIG_TINY_RCU) && is_idle_task(current)) अणु
		lockdep_hardirqs_off(CALLER_ADDR0);
		rcu_irq_enter();
		trace_hardirqs_off_finish();

		regs->निकास_rcu = true;
		वापस;
	पूर्ण

	lockdep_hardirqs_off(CALLER_ADDR0);
	rcu_irq_enter_check_tick();
	trace_hardirqs_off_finish();

	mte_check_tfsr_entry();
पूर्ण

/*
 * This is पूर्णांकended to match the logic in irqentry_निकास(), handling the kernel
 * mode transitions only, and with preemption handled अन्यथाwhere.
 */
अटल व्योम noinstr निकास_to_kernel_mode(काष्ठा pt_regs *regs)
अणु
	lockdep_निश्चित_irqs_disabled();

	mte_check_tfsr_निकास();

	अगर (पूर्णांकerrupts_enabled(regs)) अणु
		अगर (regs->निकास_rcu) अणु
			trace_hardirqs_on_prepare();
			lockdep_hardirqs_on_prepare(CALLER_ADDR0);
			rcu_irq_निकास();
			lockdep_hardirqs_on(CALLER_ADDR0);
			वापस;
		पूर्ण

		trace_hardirqs_on();
	पूर्ण अन्यथा अणु
		अगर (regs->निकास_rcu)
			rcu_irq_निकास();
	पूर्ण
पूर्ण

व्योम noinstr arm64_enter_nmi(काष्ठा pt_regs *regs)
अणु
	regs->lockdep_hardirqs = lockdep_hardirqs_enabled();

	__nmi_enter();
	lockdep_hardirqs_off(CALLER_ADDR0);
	lockdep_hardirq_enter();
	rcu_nmi_enter();

	trace_hardirqs_off_finish();
	ftrace_nmi_enter();
पूर्ण

व्योम noinstr arm64_निकास_nmi(काष्ठा pt_regs *regs)
अणु
	bool restore = regs->lockdep_hardirqs;

	ftrace_nmi_निकास();
	अगर (restore) अणु
		trace_hardirqs_on_prepare();
		lockdep_hardirqs_on_prepare(CALLER_ADDR0);
	पूर्ण

	rcu_nmi_निकास();
	lockdep_hardirq_निकास();
	अगर (restore)
		lockdep_hardirqs_on(CALLER_ADDR0);
	__nmi_निकास();
पूर्ण

यंत्रlinkage व्योम noinstr enter_el1_irq_or_nmi(काष्ठा pt_regs *regs)
अणु
	अगर (IS_ENABLED(CONFIG_ARM64_PSEUDO_NMI) && !पूर्णांकerrupts_enabled(regs))
		arm64_enter_nmi(regs);
	अन्यथा
		enter_from_kernel_mode(regs);
पूर्ण

यंत्रlinkage व्योम noinstr निकास_el1_irq_or_nmi(काष्ठा pt_regs *regs)
अणु
	अगर (IS_ENABLED(CONFIG_ARM64_PSEUDO_NMI) && !पूर्णांकerrupts_enabled(regs))
		arm64_निकास_nmi(regs);
	अन्यथा
		निकास_to_kernel_mode(regs);
पूर्ण

#अगर_घोषित CONFIG_ARM64_ERRATUM_1463225
अटल DEFINE_PER_CPU(पूर्णांक, __in_cortex_a76_erratum_1463225_wa);

अटल व्योम cortex_a76_erratum_1463225_svc_handler(व्योम)
अणु
	u32 reg, val;

	अगर (!unlikely(test_thपढ़ो_flag(TIF_SINGLESTEP)))
		वापस;

	अगर (!unlikely(this_cpu_has_cap(ARM64_WORKAROUND_1463225)))
		वापस;

	__this_cpu_ग_लिखो(__in_cortex_a76_erratum_1463225_wa, 1);
	reg = पढ़ो_sysreg(mdscr_el1);
	val = reg | DBG_MDSCR_SS | DBG_MDSCR_KDE;
	ग_लिखो_sysreg(val, mdscr_el1);
	यंत्र अस्थिर("msr daifclr, #8");
	isb();

	/* We will have taken a single-step exception by this poपूर्णांक */

	ग_लिखो_sysreg(reg, mdscr_el1);
	__this_cpu_ग_लिखो(__in_cortex_a76_erratum_1463225_wa, 0);
पूर्ण

अटल bool cortex_a76_erratum_1463225_debug_handler(काष्ठा pt_regs *regs)
अणु
	अगर (!__this_cpu_पढ़ो(__in_cortex_a76_erratum_1463225_wa))
		वापस false;

	/*
	 * We've taken a dummy step exception from the kernel to ensure
	 * that पूर्णांकerrupts are re-enabled on the syscall path. Return back
	 * to cortex_a76_erratum_1463225_svc_handler() with debug exceptions
	 * masked so that we can safely restore the mdscr and get on with
	 * handling the syscall.
	 */
	regs->pstate |= PSR_D_BIT;
	वापस true;
पूर्ण
#अन्यथा /* CONFIG_ARM64_ERRATUM_1463225 */
अटल व्योम cortex_a76_erratum_1463225_svc_handler(व्योम) अणु पूर्ण
अटल bool cortex_a76_erratum_1463225_debug_handler(काष्ठा pt_regs *regs)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARM64_ERRATUM_1463225 */

अटल व्योम noinstr el1_पात(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	अचिन्हित दीर्घ far = पढ़ो_sysreg(far_el1);

	enter_from_kernel_mode(regs);
	local_daअगर_inherit(regs);
	करो_mem_पात(far, esr, regs);
	local_daअगर_mask();
	निकास_to_kernel_mode(regs);
पूर्ण

अटल व्योम noinstr el1_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	अचिन्हित दीर्घ far = पढ़ो_sysreg(far_el1);

	enter_from_kernel_mode(regs);
	local_daअगर_inherit(regs);
	करो_sp_pc_पात(far, esr, regs);
	local_daअगर_mask();
	निकास_to_kernel_mode(regs);
पूर्ण

अटल व्योम noinstr el1_undef(काष्ठा pt_regs *regs)
अणु
	enter_from_kernel_mode(regs);
	local_daअगर_inherit(regs);
	करो_undefinstr(regs);
	local_daअगर_mask();
	निकास_to_kernel_mode(regs);
पूर्ण

अटल व्योम noinstr el1_inv(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	enter_from_kernel_mode(regs);
	local_daअगर_inherit(regs);
	bad_mode(regs, 0, esr);
	local_daअगर_mask();
	निकास_to_kernel_mode(regs);
पूर्ण

अटल व्योम noinstr arm64_enter_el1_dbg(काष्ठा pt_regs *regs)
अणु
	regs->lockdep_hardirqs = lockdep_hardirqs_enabled();

	lockdep_hardirqs_off(CALLER_ADDR0);
	rcu_nmi_enter();

	trace_hardirqs_off_finish();
पूर्ण

अटल व्योम noinstr arm64_निकास_el1_dbg(काष्ठा pt_regs *regs)
अणु
	bool restore = regs->lockdep_hardirqs;

	अगर (restore) अणु
		trace_hardirqs_on_prepare();
		lockdep_hardirqs_on_prepare(CALLER_ADDR0);
	पूर्ण

	rcu_nmi_निकास();
	अगर (restore)
		lockdep_hardirqs_on(CALLER_ADDR0);
पूर्ण

अटल व्योम noinstr el1_dbg(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	अचिन्हित दीर्घ far = पढ़ो_sysreg(far_el1);

	arm64_enter_el1_dbg(regs);
	अगर (!cortex_a76_erratum_1463225_debug_handler(regs))
		करो_debug_exception(far, esr, regs);
	arm64_निकास_el1_dbg(regs);
पूर्ण

अटल व्योम noinstr el1_fpac(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	enter_from_kernel_mode(regs);
	local_daअगर_inherit(regs);
	करो_ptrauth_fault(regs, esr);
	local_daअगर_mask();
	निकास_to_kernel_mode(regs);
पूर्ण

यंत्रlinkage व्योम noinstr el1_sync_handler(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ esr = पढ़ो_sysreg(esr_el1);

	चयन (ESR_ELx_EC(esr)) अणु
	हाल ESR_ELx_EC_DABT_CUR:
	हाल ESR_ELx_EC_IABT_CUR:
		el1_पात(regs, esr);
		अवरोध;
	/*
	 * We करोn't handle ESR_ELx_EC_SP_ALIGN, since we will have hit a
	 * recursive exception when trying to push the initial pt_regs.
	 */
	हाल ESR_ELx_EC_PC_ALIGN:
		el1_pc(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_SYS64:
	हाल ESR_ELx_EC_UNKNOWN:
		el1_undef(regs);
		अवरोध;
	हाल ESR_ELx_EC_BREAKPT_CUR:
	हाल ESR_ELx_EC_SOFTSTP_CUR:
	हाल ESR_ELx_EC_WATCHPT_CUR:
	हाल ESR_ELx_EC_BRK64:
		el1_dbg(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_FPAC:
		el1_fpac(regs, esr);
		अवरोध;
	शेष:
		el1_inv(regs, esr);
	पूर्ण
पूर्ण

यंत्रlinkage व्योम noinstr enter_from_user_mode(व्योम)
अणु
	lockdep_hardirqs_off(CALLER_ADDR0);
	CT_WARN_ON(ct_state() != CONTEXT_USER);
	user_निकास_irqoff();
	trace_hardirqs_off_finish();
पूर्ण

यंत्रlinkage व्योम noinstr निकास_to_user_mode(व्योम)
अणु
	mte_check_tfsr_निकास();

	trace_hardirqs_on_prepare();
	lockdep_hardirqs_on_prepare(CALLER_ADDR0);
	user_enter_irqoff();
	lockdep_hardirqs_on(CALLER_ADDR0);
पूर्ण

अटल व्योम noinstr el0_da(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	अचिन्हित दीर्घ far = पढ़ो_sysreg(far_el1);

	enter_from_user_mode();
	local_daअगर_restore(DAIF_PROCCTX);
	करो_mem_पात(far, esr, regs);
पूर्ण

अटल व्योम noinstr el0_ia(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	अचिन्हित दीर्घ far = पढ़ो_sysreg(far_el1);

	/*
	 * We've taken an inकाष्ठाion पात from userspace and not yet
	 * re-enabled IRQs. If the address is a kernel address, apply
	 * BP hardening prior to enabling IRQs and pre-emption.
	 */
	अगर (!is_ttbr0_addr(far))
		arm64_apply_bp_hardening();

	enter_from_user_mode();
	local_daअगर_restore(DAIF_PROCCTX);
	करो_mem_पात(far, esr, regs);
पूर्ण

अटल व्योम noinstr el0_fpsimd_acc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	enter_from_user_mode();
	local_daअगर_restore(DAIF_PROCCTX);
	करो_fpsimd_acc(esr, regs);
पूर्ण

अटल व्योम noinstr el0_sve_acc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	enter_from_user_mode();
	local_daअगर_restore(DAIF_PROCCTX);
	करो_sve_acc(esr, regs);
पूर्ण

अटल व्योम noinstr el0_fpsimd_exc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	enter_from_user_mode();
	local_daअगर_restore(DAIF_PROCCTX);
	करो_fpsimd_exc(esr, regs);
पूर्ण

अटल व्योम noinstr el0_sys(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	enter_from_user_mode();
	local_daअगर_restore(DAIF_PROCCTX);
	करो_sysinstr(esr, regs);
पूर्ण

अटल व्योम noinstr el0_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	अचिन्हित दीर्घ far = पढ़ो_sysreg(far_el1);

	अगर (!is_ttbr0_addr(inकाष्ठाion_poपूर्णांकer(regs)))
		arm64_apply_bp_hardening();

	enter_from_user_mode();
	local_daअगर_restore(DAIF_PROCCTX);
	करो_sp_pc_पात(far, esr, regs);
पूर्ण

अटल व्योम noinstr el0_sp(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	enter_from_user_mode();
	local_daअगर_restore(DAIF_PROCCTX);
	करो_sp_pc_पात(regs->sp, esr, regs);
पूर्ण

अटल व्योम noinstr el0_undef(काष्ठा pt_regs *regs)
अणु
	enter_from_user_mode();
	local_daअगर_restore(DAIF_PROCCTX);
	करो_undefinstr(regs);
पूर्ण

अटल व्योम noinstr el0_bti(काष्ठा pt_regs *regs)
अणु
	enter_from_user_mode();
	local_daअगर_restore(DAIF_PROCCTX);
	करो_bti(regs);
पूर्ण

अटल व्योम noinstr el0_inv(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	enter_from_user_mode();
	local_daअगर_restore(DAIF_PROCCTX);
	bad_el0_sync(regs, 0, esr);
पूर्ण

अटल व्योम noinstr el0_dbg(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	/* Only watchpoपूर्णांकs ग_लिखो FAR_EL1, otherwise its UNKNOWN */
	अचिन्हित दीर्घ far = पढ़ो_sysreg(far_el1);

	enter_from_user_mode();
	करो_debug_exception(far, esr, regs);
	local_daअगर_restore(DAIF_PROCCTX_NOIRQ);
पूर्ण

अटल व्योम noinstr el0_svc(काष्ठा pt_regs *regs)
अणु
	enter_from_user_mode();
	cortex_a76_erratum_1463225_svc_handler();
	करो_el0_svc(regs);
पूर्ण

अटल व्योम noinstr el0_fpac(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	enter_from_user_mode();
	local_daअगर_restore(DAIF_PROCCTX);
	करो_ptrauth_fault(regs, esr);
पूर्ण

यंत्रlinkage व्योम noinstr el0_sync_handler(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ esr = पढ़ो_sysreg(esr_el1);

	चयन (ESR_ELx_EC(esr)) अणु
	हाल ESR_ELx_EC_SVC64:
		el0_svc(regs);
		अवरोध;
	हाल ESR_ELx_EC_DABT_LOW:
		el0_da(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_IABT_LOW:
		el0_ia(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_FP_ASIMD:
		el0_fpsimd_acc(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_SVE:
		el0_sve_acc(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_FP_EXC64:
		el0_fpsimd_exc(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_SYS64:
	हाल ESR_ELx_EC_WFx:
		el0_sys(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_SP_ALIGN:
		el0_sp(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_PC_ALIGN:
		el0_pc(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_UNKNOWN:
		el0_undef(regs);
		अवरोध;
	हाल ESR_ELx_EC_BTI:
		el0_bti(regs);
		अवरोध;
	हाल ESR_ELx_EC_BREAKPT_LOW:
	हाल ESR_ELx_EC_SOFTSTP_LOW:
	हाल ESR_ELx_EC_WATCHPT_LOW:
	हाल ESR_ELx_EC_BRK64:
		el0_dbg(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_FPAC:
		el0_fpac(regs, esr);
		अवरोध;
	शेष:
		el0_inv(regs, esr);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल व्योम noinstr el0_cp15(काष्ठा pt_regs *regs, अचिन्हित दीर्घ esr)
अणु
	enter_from_user_mode();
	local_daअगर_restore(DAIF_PROCCTX);
	करो_cp15instr(esr, regs);
पूर्ण

अटल व्योम noinstr el0_svc_compat(काष्ठा pt_regs *regs)
अणु
	enter_from_user_mode();
	cortex_a76_erratum_1463225_svc_handler();
	करो_el0_svc_compat(regs);
पूर्ण

यंत्रlinkage व्योम noinstr el0_sync_compat_handler(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ esr = पढ़ो_sysreg(esr_el1);

	चयन (ESR_ELx_EC(esr)) अणु
	हाल ESR_ELx_EC_SVC32:
		el0_svc_compat(regs);
		अवरोध;
	हाल ESR_ELx_EC_DABT_LOW:
		el0_da(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_IABT_LOW:
		el0_ia(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_FP_ASIMD:
		el0_fpsimd_acc(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_FP_EXC32:
		el0_fpsimd_exc(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_PC_ALIGN:
		el0_pc(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_UNKNOWN:
	हाल ESR_ELx_EC_CP14_MR:
	हाल ESR_ELx_EC_CP14_LS:
	हाल ESR_ELx_EC_CP14_64:
		el0_undef(regs);
		अवरोध;
	हाल ESR_ELx_EC_CP15_32:
	हाल ESR_ELx_EC_CP15_64:
		el0_cp15(regs, esr);
		अवरोध;
	हाल ESR_ELx_EC_BREAKPT_LOW:
	हाल ESR_ELx_EC_SOFTSTP_LOW:
	हाल ESR_ELx_EC_WATCHPT_LOW:
	हाल ESR_ELx_EC_BKPT32:
		el0_dbg(regs, esr);
		अवरोध;
	शेष:
		el0_inv(regs, esr);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */
