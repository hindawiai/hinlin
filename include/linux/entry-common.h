<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_ENTRYCOMMON_H
#घोषणा __LINUX_ENTRYCOMMON_H

#समावेश <linux/अटल_call_types.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/entry-common.h>

/*
 * Define dummy _TIF work flags अगर not defined by the architecture or क्रम
 * disabled functionality.
 */
#अगर_अघोषित _TIF_PATCH_PENDING
# define _TIF_PATCH_PENDING		(0)
#पूर्ण_अगर

#अगर_अघोषित _TIF_UPROBE
# define _TIF_UPROBE			(0)
#पूर्ण_अगर

/*
 * SYSCALL_WORK flags handled in syscall_enter_from_user_mode()
 */
#अगर_अघोषित ARCH_SYSCALL_WORK_ENTER
# define ARCH_SYSCALL_WORK_ENTER	(0)
#पूर्ण_अगर

/*
 * SYSCALL_WORK flags handled in syscall_निकास_to_user_mode()
 */
#अगर_अघोषित ARCH_SYSCALL_WORK_EXIT
# define ARCH_SYSCALL_WORK_EXIT		(0)
#पूर्ण_अगर

#घोषणा SYSCALL_WORK_ENTER	(SYSCALL_WORK_SECCOMP |			\
				 SYSCALL_WORK_SYSCALL_TRACEPOINT |	\
				 SYSCALL_WORK_SYSCALL_TRACE |		\
				 SYSCALL_WORK_SYSCALL_EMU |		\
				 SYSCALL_WORK_SYSCALL_AUDIT |		\
				 SYSCALL_WORK_SYSCALL_USER_DISPATCH |	\
				 ARCH_SYSCALL_WORK_ENTER)
#घोषणा SYSCALL_WORK_EXIT	(SYSCALL_WORK_SYSCALL_TRACEPOINT |	\
				 SYSCALL_WORK_SYSCALL_TRACE |		\
				 SYSCALL_WORK_SYSCALL_AUDIT |		\
				 SYSCALL_WORK_SYSCALL_USER_DISPATCH |	\
				 SYSCALL_WORK_SYSCALL_EXIT_TRAP	|	\
				 ARCH_SYSCALL_WORK_EXIT)

/*
 * TIF flags handled in निकास_to_user_mode_loop()
 */
#अगर_अघोषित ARCH_EXIT_TO_USER_MODE_WORK
# define ARCH_EXIT_TO_USER_MODE_WORK		(0)
#पूर्ण_अगर

#घोषणा EXIT_TO_USER_MODE_WORK						\
	(_TIF_SIGPENDING | _TIF_NOTIFY_RESUME | _TIF_UPROBE |		\
	 _TIF_NEED_RESCHED | _TIF_PATCH_PENDING | _TIF_NOTIFY_SIGNAL |	\
	 ARCH_EXIT_TO_USER_MODE_WORK)

/**
 * arch_check_user_regs - Architecture specअगरic sanity check क्रम user mode regs
 * @regs:	Poपूर्णांकer to currents pt_regs
 *
 * Defaults to an empty implementation. Can be replaced by architecture
 * specअगरic code.
 *
 * Invoked from syscall_enter_from_user_mode() in the non-instrumentable
 * section. Use __always_अंतरभूत so the compiler cannot push it out of line
 * and make it instrumentable.
 */
अटल __always_अंतरभूत व्योम arch_check_user_regs(काष्ठा pt_regs *regs);

#अगर_अघोषित arch_check_user_regs
अटल __always_अंतरभूत व्योम arch_check_user_regs(काष्ठा pt_regs *regs) अणुपूर्ण
#पूर्ण_अगर

/**
 * arch_syscall_enter_tracehook - Wrapper around tracehook_report_syscall_entry()
 * @regs:	Poपूर्णांकer to currents pt_regs
 *
 * Returns: 0 on success or an error code to skip the syscall.
 *
 * Defaults to tracehook_report_syscall_entry(). Can be replaced by
 * architecture specअगरic code.
 *
 * Invoked from syscall_enter_from_user_mode()
 */
अटल अंतरभूत __must_check पूर्णांक arch_syscall_enter_tracehook(काष्ठा pt_regs *regs);

#अगर_अघोषित arch_syscall_enter_tracehook
अटल अंतरभूत __must_check पूर्णांक arch_syscall_enter_tracehook(काष्ठा pt_regs *regs)
अणु
	वापस tracehook_report_syscall_entry(regs);
पूर्ण
#पूर्ण_अगर

/**
 * enter_from_user_mode - Establish state when coming from user mode
 *
 * Syscall/पूर्णांकerrupt entry disables पूर्णांकerrupts, but user mode is traced as
 * पूर्णांकerrupts enabled. Also with NO_HZ_FULL RCU might be idle.
 *
 * 1) Tell lockdep that पूर्णांकerrupts are disabled
 * 2) Invoke context tracking अगर enabled to reactivate RCU
 * 3) Trace पूर्णांकerrupts off state
 *
 * Invoked from architecture specअगरic syscall entry code with पूर्णांकerrupts
 * disabled. The calling code has to be non-instrumentable. When the
 * function वापसs all state is correct and पूर्णांकerrupts are still
 * disabled. The subsequent functions can be instrumented.
 *
 * This is invoked when there is architecture specअगरic functionality to be
 * करोne between establishing state and enabling पूर्णांकerrupts. The caller must
 * enable पूर्णांकerrupts beक्रमe invoking syscall_enter_from_user_mode_work().
 */
व्योम enter_from_user_mode(काष्ठा pt_regs *regs);

/**
 * syscall_enter_from_user_mode_prepare - Establish state and enable पूर्णांकerrupts
 * @regs:	Poपूर्णांकer to currents pt_regs
 *
 * Invoked from architecture specअगरic syscall entry code with पूर्णांकerrupts
 * disabled. The calling code has to be non-instrumentable. When the
 * function वापसs all state is correct, पूर्णांकerrupts are enabled and the
 * subsequent functions can be instrumented.
 *
 * This handles lockdep, RCU (context tracking) and tracing state, i.e.
 * the functionality provided by enter_from_user_mode().
 *
 * This is invoked when there is extra architecture specअगरic functionality
 * to be करोne between establishing state and handling user mode entry work.
 */
व्योम syscall_enter_from_user_mode_prepare(काष्ठा pt_regs *regs);

/**
 * syscall_enter_from_user_mode_work - Check and handle work beक्रमe invoking
 *				       a syscall
 * @regs:	Poपूर्णांकer to currents pt_regs
 * @syscall:	The syscall number
 *
 * Invoked from architecture specअगरic syscall entry code with पूर्णांकerrupts
 * enabled after invoking syscall_enter_from_user_mode_prepare() and extra
 * architecture specअगरic work.
 *
 * Returns: The original or a modअगरied syscall number
 *
 * If the वापसed syscall number is -1 then the syscall should be
 * skipped. In this हाल the caller may invoke syscall_set_error() or
 * syscall_set_वापस_value() first.  If neither of those are called and -1
 * is वापसed, then the syscall will fail with ENOSYS.
 *
 * It handles the following work items:
 *
 *  1) syscall_work flag dependent invocations of
 *     arch_syscall_enter_tracehook(), __secure_computing(), trace_sys_enter()
 *  2) Invocation of audit_syscall_entry()
 */
दीर्घ syscall_enter_from_user_mode_work(काष्ठा pt_regs *regs, दीर्घ syscall);

/**
 * syscall_enter_from_user_mode - Establish state and check and handle work
 *				  beक्रमe invoking a syscall
 * @regs:	Poपूर्णांकer to currents pt_regs
 * @syscall:	The syscall number
 *
 * Invoked from architecture specअगरic syscall entry code with पूर्णांकerrupts
 * disabled. The calling code has to be non-instrumentable. When the
 * function वापसs all state is correct, पूर्णांकerrupts are enabled and the
 * subsequent functions can be instrumented.
 *
 * This is combination of syscall_enter_from_user_mode_prepare() and
 * syscall_enter_from_user_mode_work().
 *
 * Returns: The original or a modअगरied syscall number. See
 * syscall_enter_from_user_mode_work() क्रम further explanation.
 */
दीर्घ syscall_enter_from_user_mode(काष्ठा pt_regs *regs, दीर्घ syscall);

/**
 * local_irq_enable_निकास_to_user - Exit to user variant of local_irq_enable()
 * @ti_work:	Cached TIF flags gathered with पूर्णांकerrupts disabled
 *
 * Defaults to local_irq_enable(). Can be supplied by architecture specअगरic
 * code.
 */
अटल अंतरभूत व्योम local_irq_enable_निकास_to_user(अचिन्हित दीर्घ ti_work);

#अगर_अघोषित local_irq_enable_निकास_to_user
अटल अंतरभूत व्योम local_irq_enable_निकास_to_user(अचिन्हित दीर्घ ti_work)
अणु
	local_irq_enable();
पूर्ण
#पूर्ण_अगर

/**
 * local_irq_disable_निकास_to_user - Exit to user variant of local_irq_disable()
 *
 * Defaults to local_irq_disable(). Can be supplied by architecture specअगरic
 * code.
 */
अटल अंतरभूत व्योम local_irq_disable_निकास_to_user(व्योम);

#अगर_अघोषित local_irq_disable_निकास_to_user
अटल अंतरभूत व्योम local_irq_disable_निकास_to_user(व्योम)
अणु
	local_irq_disable();
पूर्ण
#पूर्ण_अगर

/**
 * arch_निकास_to_user_mode_work - Architecture specअगरic TIF work क्रम निकास
 *				 to user mode.
 * @regs:	Poपूर्णांकer to currents pt_regs
 * @ti_work:	Cached TIF flags gathered with पूर्णांकerrupts disabled
 *
 * Invoked from निकास_to_user_mode_loop() with पूर्णांकerrupt enabled
 *
 * Defaults to NOOP. Can be supplied by architecture specअगरic code.
 */
अटल अंतरभूत व्योम arch_निकास_to_user_mode_work(काष्ठा pt_regs *regs,
					       अचिन्हित दीर्घ ti_work);

#अगर_अघोषित arch_निकास_to_user_mode_work
अटल अंतरभूत व्योम arch_निकास_to_user_mode_work(काष्ठा pt_regs *regs,
					       अचिन्हित दीर्घ ti_work)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * arch_निकास_to_user_mode_prepare - Architecture specअगरic preparation क्रम
 *				    निकास to user mode.
 * @regs:	Poपूर्णांकer to currents pt_regs
 * @ti_work:	Cached TIF flags gathered with पूर्णांकerrupts disabled
 *
 * Invoked from निकास_to_user_mode_prepare() with पूर्णांकerrupt disabled as the last
 * function beक्रमe वापस. Defaults to NOOP.
 */
अटल अंतरभूत व्योम arch_निकास_to_user_mode_prepare(काष्ठा pt_regs *regs,
						  अचिन्हित दीर्घ ti_work);

#अगर_अघोषित arch_निकास_to_user_mode_prepare
अटल अंतरभूत व्योम arch_निकास_to_user_mode_prepare(काष्ठा pt_regs *regs,
						  अचिन्हित दीर्घ ti_work)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * arch_निकास_to_user_mode - Architecture specअगरic final work beक्रमe
 *			    निकास to user mode.
 *
 * Invoked from निकास_to_user_mode() with पूर्णांकerrupt disabled as the last
 * function beक्रमe वापस. Defaults to NOOP.
 *
 * This needs to be __always_अंतरभूत because it is non-instrumentable code
 * invoked after context tracking चयनed to user mode.
 *
 * An architecture implementation must not करो anything complex, no locking
 * etc. The मुख्य purpose is क्रम speculation mitigations.
 */
अटल __always_अंतरभूत व्योम arch_निकास_to_user_mode(व्योम);

#अगर_अघोषित arch_निकास_to_user_mode
अटल __always_अंतरभूत व्योम arch_निकास_to_user_mode(व्योम) अणु पूर्ण
#पूर्ण_अगर

/**
 * arch_करो_संकेत_or_restart -  Architecture specअगरic संकेत delivery function
 * @regs:	Poपूर्णांकer to currents pt_regs
 * @has_संकेत:	actual संकेत to handle
 *
 * Invoked from निकास_to_user_mode_loop().
 */
व्योम arch_करो_संकेत_or_restart(काष्ठा pt_regs *regs, bool has_संकेत);

/**
 * arch_syscall_निकास_tracehook - Wrapper around tracehook_report_syscall_निकास()
 * @regs:	Poपूर्णांकer to currents pt_regs
 * @step:	Indicator क्रम single step
 *
 * Defaults to tracehook_report_syscall_निकास(). Can be replaced by
 * architecture specअगरic code.
 *
 * Invoked from syscall_निकास_to_user_mode()
 */
अटल अंतरभूत व्योम arch_syscall_निकास_tracehook(काष्ठा pt_regs *regs, bool step);

#अगर_अघोषित arch_syscall_निकास_tracehook
अटल अंतरभूत व्योम arch_syscall_निकास_tracehook(काष्ठा pt_regs *regs, bool step)
अणु
	tracehook_report_syscall_निकास(regs, step);
पूर्ण
#पूर्ण_अगर

/**
 * निकास_to_user_mode - Fixup state when निकासing to user mode
 *
 * Syscall/पूर्णांकerrupt निकास enables पूर्णांकerrupts, but the kernel state is
 * पूर्णांकerrupts disabled when this is invoked. Also tell RCU about it.
 *
 * 1) Trace पूर्णांकerrupts on state
 * 2) Invoke context tracking अगर enabled to adjust RCU state
 * 3) Invoke architecture specअगरic last minute निकास code, e.g. speculation
 *    mitigations, etc.: arch_निकास_to_user_mode()
 * 4) Tell lockdep that पूर्णांकerrupts are enabled
 *
 * Invoked from architecture specअगरic code when syscall_निकास_to_user_mode()
 * is not suitable as the last step beक्रमe वापसing to userspace. Must be
 * invoked with पूर्णांकerrupts disabled and the caller must be
 * non-instrumentable.
 * The caller has to invoke syscall_निकास_to_user_mode_work() beक्रमe this.
 */
व्योम निकास_to_user_mode(व्योम);

/**
 * syscall_निकास_to_user_mode_work - Handle work beक्रमe वापसing to user mode
 * @regs:	Poपूर्णांकer to currents pt_regs
 *
 * Same as step 1 and 2 of syscall_निकास_to_user_mode() but without calling
 * निकास_to_user_mode() to perक्रमm the final transition to user mode.
 *
 * Calling convention is the same as क्रम syscall_निकास_to_user_mode() and it
 * वापसs with all work handled and पूर्णांकerrupts disabled. The caller must
 * invoke निकास_to_user_mode() beक्रमe actually चयनing to user mode to
 * make the final state transitions. Interrupts must stay disabled between
 * वापस from this function and the invocation of निकास_to_user_mode().
 */
व्योम syscall_निकास_to_user_mode_work(काष्ठा pt_regs *regs);

/**
 * syscall_निकास_to_user_mode - Handle work beक्रमe वापसing to user mode
 * @regs:	Poपूर्णांकer to currents pt_regs
 *
 * Invoked with पूर्णांकerrupts enabled and fully valid regs. Returns with all
 * work handled, पूर्णांकerrupts disabled such that the caller can immediately
 * चयन to user mode. Called from architecture specअगरic syscall and ret
 * from विभाजन code.
 *
 * The call order is:
 *  1) One-समय syscall निकास work:
 *	- rseq syscall निकास
 *      - audit
 *	- syscall tracing
 *	- tracehook (single stepping)
 *
 *  2) Preparatory work
 *	- Exit to user mode loop (common TIF handling). Invokes
 *	  arch_निकास_to_user_mode_work() क्रम architecture specअगरic TIF work
 *	- Architecture specअगरic one समय work arch_निकास_to_user_mode_prepare()
 *	- Address limit and lockdep checks
 *
 *  3) Final transition (lockdep, tracing, context tracking, RCU), i.e. the
 *     functionality in निकास_to_user_mode().
 *
 * This is a combination of syscall_निकास_to_user_mode_work() (1,2) and
 * निकास_to_user_mode(). This function is preferred unless there is a
 * compelling architectural reason to use the separate functions.
 */
व्योम syscall_निकास_to_user_mode(काष्ठा pt_regs *regs);

/**
 * irqentry_enter_from_user_mode - Establish state beक्रमe invoking the irq handler
 * @regs:	Poपूर्णांकer to currents pt_regs
 *
 * Invoked from architecture specअगरic entry code with पूर्णांकerrupts disabled.
 * Can only be called when the पूर्णांकerrupt entry came from user mode. The
 * calling code must be non-instrumentable.  When the function वापसs all
 * state is correct and the subsequent functions can be instrumented.
 *
 * The function establishes state (lockdep, RCU (context tracking), tracing)
 */
व्योम irqentry_enter_from_user_mode(काष्ठा pt_regs *regs);

/**
 * irqentry_निकास_to_user_mode - Interrupt निकास work
 * @regs:	Poपूर्णांकer to current's pt_regs
 *
 * Invoked with पूर्णांकerrupts disabled and fully valid regs. Returns with all
 * work handled, पूर्णांकerrupts disabled such that the caller can immediately
 * चयन to user mode. Called from architecture specअगरic पूर्णांकerrupt
 * handling code.
 *
 * The call order is #2 and #3 as described in syscall_निकास_to_user_mode().
 * Interrupt निकास is not invoking #1 which is the syscall specअगरic one समय
 * work.
 */
व्योम irqentry_निकास_to_user_mode(काष्ठा pt_regs *regs);

#अगर_अघोषित irqentry_state
/**
 * काष्ठा irqentry_state - Opaque object क्रम exception state storage
 * @निकास_rcu: Used exclusively in the irqentry_*() calls; संकेतs whether the
 *            निकास path has to invoke rcu_irq_निकास().
 * @lockdep: Used exclusively in the irqentry_nmi_*() calls; ensures that
 *           lockdep state is restored correctly on निकास from nmi.
 *
 * This opaque object is filled in by the irqentry_*_enter() functions and
 * must be passed back पूर्णांकo the corresponding irqentry_*_निकास() functions
 * when the exception is complete.
 *
 * Callers of irqentry_*_[enter|निकास]() must consider this काष्ठाure opaque
 * and all members निजी.  Descriptions of the members are provided to aid in
 * the मुख्यtenance of the irqentry_*() functions.
 */
प्रकार काष्ठा irqentry_state अणु
	जोड़ अणु
		bool	निकास_rcu;
		bool	lockdep;
	पूर्ण;
पूर्ण irqentry_state_t;
#पूर्ण_अगर

/**
 * irqentry_enter - Handle state tracking on ordinary पूर्णांकerrupt entries
 * @regs:	Poपूर्णांकer to pt_regs of पूर्णांकerrupted context
 *
 * Invokes:
 *  - lockdep irqflag state tracking as low level ASM entry disabled
 *    पूर्णांकerrupts.
 *
 *  - Context tracking अगर the exception hit user mode.
 *
 *  - The hardirq tracer to keep the state consistent as low level ASM
 *    entry disabled पूर्णांकerrupts.
 *
 * As a precondition, this requires that the entry came from user mode,
 * idle, or a kernel context in which RCU is watching.
 *
 * For kernel mode entries RCU handling is करोne conditional. If RCU is
 * watching then the only RCU requirement is to check whether the tick has
 * to be restarted. If RCU is not watching then rcu_irq_enter() has to be
 * invoked on entry and rcu_irq_निकास() on निकास.
 *
 * Aव्योमing the rcu_irq_enter/निकास() calls is an optimization but also
 * solves the problem of kernel mode pagefaults which can schedule, which
 * is not possible after invoking rcu_irq_enter() without unकरोing it.
 *
 * For user mode entries irqentry_enter_from_user_mode() is invoked to
 * establish the proper context क्रम NOHZ_FULL. Otherwise scheduling on निकास
 * would not be possible.
 *
 * Returns: An opaque object that must be passed to idtentry_निकास()
 */
irqentry_state_t noinstr irqentry_enter(काष्ठा pt_regs *regs);

/**
 * irqentry_निकास_cond_resched - Conditionally reschedule on वापस from पूर्णांकerrupt
 *
 * Conditional reschedule with additional sanity checks.
 */
व्योम irqentry_निकास_cond_resched(व्योम);
#अगर_घोषित CONFIG_PREEMPT_DYNAMIC
DECLARE_STATIC_CALL(irqentry_निकास_cond_resched, irqentry_निकास_cond_resched);
#पूर्ण_अगर

/**
 * irqentry_निकास - Handle वापस from exception that used irqentry_enter()
 * @regs:	Poपूर्णांकer to pt_regs (exception entry regs)
 * @state:	Return value from matching call to irqentry_enter()
 *
 * Depending on the वापस target (kernel/user) this runs the necessary
 * preemption and work checks अगर possible and required and वापसs to
 * the caller with पूर्णांकerrupts disabled and no further work pending.
 *
 * This is the last action beक्रमe वापसing to the low level ASM code which
 * just needs to वापस to the appropriate context.
 *
 * Counterpart to irqentry_enter().
 */
व्योम noinstr irqentry_निकास(काष्ठा pt_regs *regs, irqentry_state_t state);

/**
 * irqentry_nmi_enter - Handle NMI entry
 * @regs:	Poपूर्णांकer to currents pt_regs
 *
 * Similar to irqentry_enter() but taking care of the NMI स्थिरraपूर्णांकs.
 */
irqentry_state_t noinstr irqentry_nmi_enter(काष्ठा pt_regs *regs);

/**
 * irqentry_nmi_निकास - Handle वापस from NMI handling
 * @regs:	Poपूर्णांकer to pt_regs (NMI entry regs)
 * @irq_state:	Return value from matching call to irqentry_nmi_enter()
 *
 * Last action beक्रमe वापसing to the low level assembly code.
 *
 * Counterpart to irqentry_nmi_enter().
 */
व्योम noinstr irqentry_nmi_निकास(काष्ठा pt_regs *regs, irqentry_state_t irq_state);

#पूर्ण_अगर
