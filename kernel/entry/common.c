<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/context_tracking.h>
#समावेश <linux/entry-common.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/livepatch.h>
#समावेश <linux/audit.h>
#समावेश <linux/tick.h>

#समावेश "common.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/syscalls.h>

/* See comment क्रम enter_from_user_mode() in entry-common.h */
अटल __always_अंतरभूत व्योम __enter_from_user_mode(काष्ठा pt_regs *regs)
अणु
	arch_check_user_regs(regs);
	lockdep_hardirqs_off(CALLER_ADDR0);

	CT_WARN_ON(ct_state() != CONTEXT_USER);
	user_निकास_irqoff();

	instrumentation_begin();
	trace_hardirqs_off_finish();
	instrumentation_end();
पूर्ण

व्योम noinstr enter_from_user_mode(काष्ठा pt_regs *regs)
अणु
	__enter_from_user_mode(regs);
पूर्ण

अटल अंतरभूत व्योम syscall_enter_audit(काष्ठा pt_regs *regs, दीर्घ syscall)
अणु
	अगर (unlikely(audit_context())) अणु
		अचिन्हित दीर्घ args[6];

		syscall_get_arguments(current, regs, args);
		audit_syscall_entry(syscall, args[0], args[1], args[2], args[3]);
	पूर्ण
पूर्ण

अटल दीर्घ syscall_trace_enter(काष्ठा pt_regs *regs, दीर्घ syscall,
				अचिन्हित दीर्घ work)
अणु
	दीर्घ ret = 0;

	/*
	 * Handle Syscall User Dispatch.  This must comes first, since
	 * the ABI here can be something that करोesn't make sense क्रम
	 * other syscall_work features.
	 */
	अगर (work & SYSCALL_WORK_SYSCALL_USER_DISPATCH) अणु
		अगर (syscall_user_dispatch(regs))
			वापस -1L;
	पूर्ण

	/* Handle ptrace */
	अगर (work & (SYSCALL_WORK_SYSCALL_TRACE | SYSCALL_WORK_SYSCALL_EMU)) अणु
		ret = arch_syscall_enter_tracehook(regs);
		अगर (ret || (work & SYSCALL_WORK_SYSCALL_EMU))
			वापस -1L;
	पूर्ण

	/* Do seccomp after ptrace, to catch any tracer changes. */
	अगर (work & SYSCALL_WORK_SECCOMP) अणु
		ret = __secure_computing(शून्य);
		अगर (ret == -1L)
			वापस ret;
	पूर्ण

	/* Either of the above might have changed the syscall number */
	syscall = syscall_get_nr(current, regs);

	अगर (unlikely(work & SYSCALL_WORK_SYSCALL_TRACEPOINT))
		trace_sys_enter(regs, syscall);

	syscall_enter_audit(regs, syscall);

	वापस ret ? : syscall;
पूर्ण

अटल __always_अंतरभूत दीर्घ
__syscall_enter_from_user_work(काष्ठा pt_regs *regs, दीर्घ syscall)
अणु
	अचिन्हित दीर्घ work = READ_ONCE(current_thपढ़ो_info()->syscall_work);

	अगर (work & SYSCALL_WORK_ENTER)
		syscall = syscall_trace_enter(regs, syscall, work);

	वापस syscall;
पूर्ण

दीर्घ syscall_enter_from_user_mode_work(काष्ठा pt_regs *regs, दीर्घ syscall)
अणु
	वापस __syscall_enter_from_user_work(regs, syscall);
पूर्ण

noinstr दीर्घ syscall_enter_from_user_mode(काष्ठा pt_regs *regs, दीर्घ syscall)
अणु
	दीर्घ ret;

	__enter_from_user_mode(regs);

	instrumentation_begin();
	local_irq_enable();
	ret = __syscall_enter_from_user_work(regs, syscall);
	instrumentation_end();

	वापस ret;
पूर्ण

noinstr व्योम syscall_enter_from_user_mode_prepare(काष्ठा pt_regs *regs)
अणु
	__enter_from_user_mode(regs);
	instrumentation_begin();
	local_irq_enable();
	instrumentation_end();
पूर्ण

/* See comment क्रम निकास_to_user_mode() in entry-common.h */
अटल __always_अंतरभूत व्योम __निकास_to_user_mode(व्योम)
अणु
	instrumentation_begin();
	trace_hardirqs_on_prepare();
	lockdep_hardirqs_on_prepare(CALLER_ADDR0);
	instrumentation_end();

	user_enter_irqoff();
	arch_निकास_to_user_mode();
	lockdep_hardirqs_on(CALLER_ADDR0);
पूर्ण

व्योम noinstr निकास_to_user_mode(व्योम)
अणु
	__निकास_to_user_mode();
पूर्ण

/* Workaround to allow gradual conversion of architecture code */
व्योम __weak arch_करो_संकेत_or_restart(काष्ठा pt_regs *regs, bool has_संकेत) अणु पूर्ण

अटल व्योम handle_संकेत_work(काष्ठा pt_regs *regs, अचिन्हित दीर्घ ti_work)
अणु
	अगर (ti_work & _TIF_NOTIFY_SIGNAL)
		tracehook_notअगरy_संकेत();

	arch_करो_संकेत_or_restart(regs, ti_work & _TIF_SIGPENDING);
पूर्ण

अटल अचिन्हित दीर्घ निकास_to_user_mode_loop(काष्ठा pt_regs *regs,
					    अचिन्हित दीर्घ ti_work)
अणु
	/*
	 * Beक्रमe वापसing to user space ensure that all pending work
	 * items have been completed.
	 */
	जबतक (ti_work & EXIT_TO_USER_MODE_WORK) अणु

		local_irq_enable_निकास_to_user(ti_work);

		अगर (ti_work & _TIF_NEED_RESCHED)
			schedule();

		अगर (ti_work & _TIF_UPROBE)
			uprobe_notअगरy_resume(regs);

		अगर (ti_work & _TIF_PATCH_PENDING)
			klp_update_patch_state(current);

		अगर (ti_work & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAL))
			handle_संकेत_work(regs, ti_work);

		अगर (ti_work & _TIF_NOTIFY_RESUME) अणु
			tracehook_notअगरy_resume(regs);
			rseq_handle_notअगरy_resume(शून्य, regs);
		पूर्ण

		/* Architecture specअगरic TIF work */
		arch_निकास_to_user_mode_work(regs, ti_work);

		/*
		 * Disable पूर्णांकerrupts and reevaluate the work flags as they
		 * might have changed जबतक पूर्णांकerrupts and preemption was
		 * enabled above.
		 */
		local_irq_disable_निकास_to_user();

		/* Check अगर any of the above work has queued a deferred wakeup */
		tick_nohz_user_enter_prepare();

		ti_work = READ_ONCE(current_thपढ़ो_info()->flags);
	पूर्ण

	/* Return the latest work state क्रम arch_निकास_to_user_mode() */
	वापस ti_work;
पूर्ण

अटल व्योम निकास_to_user_mode_prepare(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ ti_work = READ_ONCE(current_thपढ़ो_info()->flags);

	lockdep_निश्चित_irqs_disabled();

	/* Flush pending rcuog wakeup beक्रमe the last need_resched() check */
	tick_nohz_user_enter_prepare();

	अगर (unlikely(ti_work & EXIT_TO_USER_MODE_WORK))
		ti_work = निकास_to_user_mode_loop(regs, ti_work);

	arch_निकास_to_user_mode_prepare(regs, ti_work);

	/* Ensure that the address limit is पूर्णांकact and no locks are held */
	addr_limit_user_check();
	kmap_निश्चित_nomap();
	lockdep_निश्चित_irqs_disabled();
	lockdep_sys_निकास();
पूर्ण

/*
 * If SYSCALL_EMU is set, then the only reason to report is when
 * SINGLESTEP is set (i.e. PTRACE_SYSEMU_SINGLESTEP).  This syscall
 * inकाष्ठाion has been alपढ़ोy reported in syscall_enter_from_user_mode().
 */
अटल अंतरभूत bool report_single_step(अचिन्हित दीर्घ work)
अणु
	अगर (work & SYSCALL_WORK_SYSCALL_EMU)
		वापस false;

	वापस work & SYSCALL_WORK_SYSCALL_EXIT_TRAP;
पूर्ण

अटल व्योम syscall_निकास_work(काष्ठा pt_regs *regs, अचिन्हित दीर्घ work)
अणु
	bool step;

	/*
	 * If the syscall was rolled back due to syscall user dispatching,
	 * then the tracers below are not invoked क्रम the same reason as
	 * the entry side was not invoked in syscall_trace_enter(): The ABI
	 * of these syscalls is unknown.
	 */
	अगर (work & SYSCALL_WORK_SYSCALL_USER_DISPATCH) अणु
		अगर (unlikely(current->syscall_dispatch.on_dispatch)) अणु
			current->syscall_dispatch.on_dispatch = false;
			वापस;
		पूर्ण
	पूर्ण

	audit_syscall_निकास(regs);

	अगर (work & SYSCALL_WORK_SYSCALL_TRACEPOINT)
		trace_sys_निकास(regs, syscall_get_वापस_value(current, regs));

	step = report_single_step(work);
	अगर (step || work & SYSCALL_WORK_SYSCALL_TRACE)
		arch_syscall_निकास_tracehook(regs, step);
पूर्ण

/*
 * Syscall specअगरic निकास to user mode preparation. Runs with पूर्णांकerrupts
 * enabled.
 */
अटल व्योम syscall_निकास_to_user_mode_prepare(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ work = READ_ONCE(current_thपढ़ो_info()->syscall_work);
	अचिन्हित दीर्घ nr = syscall_get_nr(current, regs);

	CT_WARN_ON(ct_state() != CONTEXT_KERNEL);

	अगर (IS_ENABLED(CONFIG_PROVE_LOCKING)) अणु
		अगर (WARN(irqs_disabled(), "syscall %lu left IRQs disabled", nr))
			local_irq_enable();
	पूर्ण

	rseq_syscall(regs);

	/*
	 * Do one-समय syscall specअगरic work. If these work items are
	 * enabled, we want to run them exactly once per syscall निकास with
	 * पूर्णांकerrupts enabled.
	 */
	अगर (unlikely(work & SYSCALL_WORK_EXIT))
		syscall_निकास_work(regs, work);
पूर्ण

अटल __always_अंतरभूत व्योम __syscall_निकास_to_user_mode_work(काष्ठा pt_regs *regs)
अणु
	syscall_निकास_to_user_mode_prepare(regs);
	local_irq_disable_निकास_to_user();
	निकास_to_user_mode_prepare(regs);
पूर्ण

व्योम syscall_निकास_to_user_mode_work(काष्ठा pt_regs *regs)
अणु
	__syscall_निकास_to_user_mode_work(regs);
पूर्ण

__visible noinstr व्योम syscall_निकास_to_user_mode(काष्ठा pt_regs *regs)
अणु
	instrumentation_begin();
	__syscall_निकास_to_user_mode_work(regs);
	instrumentation_end();
	__निकास_to_user_mode();
पूर्ण

noinstr व्योम irqentry_enter_from_user_mode(काष्ठा pt_regs *regs)
अणु
	__enter_from_user_mode(regs);
पूर्ण

noinstr व्योम irqentry_निकास_to_user_mode(काष्ठा pt_regs *regs)
अणु
	instrumentation_begin();
	निकास_to_user_mode_prepare(regs);
	instrumentation_end();
	__निकास_to_user_mode();
पूर्ण

noinstr irqentry_state_t irqentry_enter(काष्ठा pt_regs *regs)
अणु
	irqentry_state_t ret = अणु
		.निकास_rcu = false,
	पूर्ण;

	अगर (user_mode(regs)) अणु
		irqentry_enter_from_user_mode(regs);
		वापस ret;
	पूर्ण

	/*
	 * If this entry hit the idle task invoke rcu_irq_enter() whether
	 * RCU is watching or not.
	 *
	 * Interrupts can nest when the first पूर्णांकerrupt invokes softirq
	 * processing on वापस which enables पूर्णांकerrupts.
	 *
	 * Scheduler ticks in the idle task can mark quiescent state and
	 * terminate a grace period, अगर and only अगर the समयr पूर्णांकerrupt is
	 * not nested पूर्णांकo another पूर्णांकerrupt.
	 *
	 * Checking क्रम rcu_is_watching() here would prevent the nesting
	 * पूर्णांकerrupt to invoke rcu_irq_enter(). If that nested पूर्णांकerrupt is
	 * the tick then rcu_flavor_sched_घड़ी_irq() would wrongfully
	 * assume that it is the first पूर्णांकerrupt and eventually claim
	 * quiescent state and end grace periods prematurely.
	 *
	 * Unconditionally invoke rcu_irq_enter() so RCU state stays
	 * consistent.
	 *
	 * TINY_RCU करोes not support EQS, so let the compiler eliminate
	 * this part when enabled.
	 */
	अगर (!IS_ENABLED(CONFIG_TINY_RCU) && is_idle_task(current)) अणु
		/*
		 * If RCU is not watching then the same careful
		 * sequence vs. lockdep and tracing is required
		 * as in irqentry_enter_from_user_mode().
		 */
		lockdep_hardirqs_off(CALLER_ADDR0);
		rcu_irq_enter();
		instrumentation_begin();
		trace_hardirqs_off_finish();
		instrumentation_end();

		ret.निकास_rcu = true;
		वापस ret;
	पूर्ण

	/*
	 * If RCU is watching then RCU only wants to check whether it needs
	 * to restart the tick in NOHZ mode. rcu_irq_enter_check_tick()
	 * alपढ़ोy contains a warning when RCU is not watching, so no poपूर्णांक
	 * in having another one here.
	 */
	lockdep_hardirqs_off(CALLER_ADDR0);
	instrumentation_begin();
	rcu_irq_enter_check_tick();
	trace_hardirqs_off_finish();
	instrumentation_end();

	वापस ret;
पूर्ण

व्योम irqentry_निकास_cond_resched(व्योम)
अणु
	अगर (!preempt_count()) अणु
		/* Sanity check RCU and thपढ़ो stack */
		rcu_irq_निकास_check_preempt();
		अगर (IS_ENABLED(CONFIG_DEBUG_ENTRY))
			WARN_ON_ONCE(!on_thपढ़ो_stack());
		अगर (need_resched())
			preempt_schedule_irq();
	पूर्ण
पूर्ण
#अगर_घोषित CONFIG_PREEMPT_DYNAMIC
DEFINE_STATIC_CALL(irqentry_निकास_cond_resched, irqentry_निकास_cond_resched);
#पूर्ण_अगर

noinstr व्योम irqentry_निकास(काष्ठा pt_regs *regs, irqentry_state_t state)
अणु
	lockdep_निश्चित_irqs_disabled();

	/* Check whether this वापसs to user mode */
	अगर (user_mode(regs)) अणु
		irqentry_निकास_to_user_mode(regs);
	पूर्ण अन्यथा अगर (!regs_irqs_disabled(regs)) अणु
		/*
		 * If RCU was not watching on entry this needs to be करोne
		 * carefully and needs the same ordering of lockdep/tracing
		 * and RCU as the वापस to user mode path.
		 */
		अगर (state.निकास_rcu) अणु
			instrumentation_begin();
			/* Tell the tracer that IRET will enable पूर्णांकerrupts */
			trace_hardirqs_on_prepare();
			lockdep_hardirqs_on_prepare(CALLER_ADDR0);
			instrumentation_end();
			rcu_irq_निकास();
			lockdep_hardirqs_on(CALLER_ADDR0);
			वापस;
		पूर्ण

		instrumentation_begin();
		अगर (IS_ENABLED(CONFIG_PREEMPTION)) अणु
#अगर_घोषित CONFIG_PREEMPT_DYNAMIC
			अटल_call(irqentry_निकास_cond_resched)();
#अन्यथा
			irqentry_निकास_cond_resched();
#पूर्ण_अगर
		पूर्ण
		/* Covers both tracing and lockdep */
		trace_hardirqs_on();
		instrumentation_end();
	पूर्ण अन्यथा अणु
		/*
		 * IRQ flags state is correct alपढ़ोy. Just tell RCU अगर it
		 * was not watching on entry.
		 */
		अगर (state.निकास_rcu)
			rcu_irq_निकास();
	पूर्ण
पूर्ण

irqentry_state_t noinstr irqentry_nmi_enter(काष्ठा pt_regs *regs)
अणु
	irqentry_state_t irq_state;

	irq_state.lockdep = lockdep_hardirqs_enabled();

	__nmi_enter();
	lockdep_hardirqs_off(CALLER_ADDR0);
	lockdep_hardirq_enter();
	rcu_nmi_enter();

	instrumentation_begin();
	trace_hardirqs_off_finish();
	ftrace_nmi_enter();
	instrumentation_end();

	वापस irq_state;
पूर्ण

व्योम noinstr irqentry_nmi_निकास(काष्ठा pt_regs *regs, irqentry_state_t irq_state)
अणु
	instrumentation_begin();
	ftrace_nmi_निकास();
	अगर (irq_state.lockdep) अणु
		trace_hardirqs_on_prepare();
		lockdep_hardirqs_on_prepare(CALLER_ADDR0);
	पूर्ण
	instrumentation_end();

	rcu_nmi_निकास();
	lockdep_hardirq_निकास();
	अगर (irq_state.lockdep)
		lockdep_hardirqs_on(CALLER_ADDR0);
	__nmi_निकास();
पूर्ण
