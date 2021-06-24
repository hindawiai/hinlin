<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Tracing hooks
 *
 * Copyright (C) 2008-2009 Red Hat, Inc.  All rights reserved.
 *
 * This file defines hook entry poपूर्णांकs called by core code where
 * user tracing/debugging support might need to करो something.  These
 * entry poपूर्णांकs are called tracehook_*().  Each hook declared below
 * has a detailed kernelकरोc comment giving the context (locking et
 * al) from which it is called, and the meaning of its वापस value.
 *
 * Each function here typically has only one call site, so it is ok
 * to have some nontrivial tracehook_*() अंतरभूतs.  In all हालs, the
 * fast path when no tracing is enabled should be very लघु.
 *
 * The purpose of this file and the tracehook_* layer is to consolidate
 * the पूर्णांकerface that the kernel core and arch code uses to enable any
 * user debugging or tracing facility (such as ptrace).  The पूर्णांकerfaces
 * here are carefully करोcumented so that मुख्यtainers of core and arch
 * code करो not need to think about the implementation details of the
 * tracing facilities.  Likewise, मुख्यtainers of the tracing code करो not
 * need to understand all the calling core or arch code in detail, just
 * करोcumented circumstances of each call, such as locking conditions.
 *
 * If the calling core code changes so that locking is dअगरferent, then
 * it is ok to change the पूर्णांकerface करोcumented here.  The मुख्यtainer of
 * core code changing should notअगरy the मुख्यtainers of the tracing code
 * that they need to work out the change.
 *
 * Some tracehook_*() अंतरभूतs take arguments that the current tracing
 * implementations might not necessarily use.  These function signatures
 * are chosen to pass in all the inक्रमmation that is on hand in the
 * caller and might conceivably be relevant to a tracer, so that the
 * core code won't have to be updated when tracing adds more features.
 * If a call site changes so that some of those parameters are no दीर्घer
 * alपढ़ोy on hand without extra work, then the tracehook_* पूर्णांकerface
 * can change so there is no make-work burden on the core code.  The
 * मुख्यtainer of core code changing should notअगरy the मुख्यtainers of the
 * tracing code that they need to work out the change.
 */

#अगर_अघोषित _LINUX_TRACEHOOK_H
#घोषणा _LINUX_TRACEHOOK_H	1

#समावेश <linux/sched.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/security.h>
#समावेश <linux/task_work.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/blk-cgroup.h>
काष्ठा linux_binprm;

/*
 * ptrace report क्रम syscall entry and निकास looks identical.
 */
अटल अंतरभूत पूर्णांक ptrace_report_syscall(काष्ठा pt_regs *regs,
					अचिन्हित दीर्घ message)
अणु
	पूर्णांक ptrace = current->ptrace;

	अगर (!(ptrace & PT_PTRACED))
		वापस 0;

	current->ptrace_message = message;
	ptrace_notअगरy(SIGTRAP | ((ptrace & PT_TRACESYSGOOD) ? 0x80 : 0));

	/*
	 * this isn't the same as continuing with a संकेत, but it will करो
	 * क्रम normal use.  strace only जारीs with a संकेत अगर the
	 * stopping संकेत is not SIGTRAP.  -brl
	 */
	अगर (current->निकास_code) अणु
		send_sig(current->निकास_code, current, 1);
		current->निकास_code = 0;
	पूर्ण

	current->ptrace_message = 0;
	वापस fatal_संकेत_pending(current);
पूर्ण

/**
 * tracehook_report_syscall_entry - task is about to attempt a प्रणाली call
 * @regs:		user रेजिस्टर state of current task
 *
 * This will be called अगर %SYSCALL_WORK_SYSCALL_TRACE or
 * %SYSCALL_WORK_SYSCALL_EMU have been set, when the current task has just
 * entered the kernel क्रम a प्रणाली call.  Full user रेजिस्टर state is
 * available here.  Changing the values in @regs can affect the प्रणाली
 * call number and arguments to be tried.  It is safe to block here,
 * preventing the प्रणाली call from beginning.
 *
 * Returns zero normally, or nonzero अगर the calling arch code should पात
 * the प्रणाली call.  That must prevent normal entry so no प्रणाली call is
 * made.  If @task ever वापसs to user mode after this, its रेजिस्टर state
 * is unspecअगरied, but should be something harmless like an %ENOSYS error
 * वापस.  It should preserve enough inक्रमmation so that syscall_rollback()
 * can work (see यंत्र-generic/syscall.h).
 *
 * Called without locks, just after entering kernel mode.
 */
अटल अंतरभूत __must_check पूर्णांक tracehook_report_syscall_entry(
	काष्ठा pt_regs *regs)
अणु
	वापस ptrace_report_syscall(regs, PTRACE_EVENTMSG_SYSCALL_ENTRY);
पूर्ण

/**
 * tracehook_report_syscall_निकास - task has just finished a प्रणाली call
 * @regs:		user रेजिस्टर state of current task
 * @step:		nonzero अगर simulating single-step or block-step
 *
 * This will be called अगर %SYSCALL_WORK_SYSCALL_TRACE has been set, when
 * the current task has just finished an attempted प्रणाली call.  Full
 * user रेजिस्टर state is available here.  It is safe to block here,
 * preventing संकेतs from being processed.
 *
 * If @step is nonzero, this report is also in lieu of the normal
 * trap that would follow the प्रणाली call inकाष्ठाion because
 * user_enable_block_step() or user_enable_single_step() was used.
 * In this हाल, %SYSCALL_WORK_SYSCALL_TRACE might not be set.
 *
 * Called without locks, just beक्रमe checking क्रम pending संकेतs.
 */
अटल अंतरभूत व्योम tracehook_report_syscall_निकास(काष्ठा pt_regs *regs, पूर्णांक step)
अणु
	अगर (step)
		user_single_step_report(regs);
	अन्यथा
		ptrace_report_syscall(regs, PTRACE_EVENTMSG_SYSCALL_EXIT);
पूर्ण

/**
 * tracehook_संकेत_handler - संकेत handler setup is complete
 * @stepping:		nonzero अगर debugger single-step or block-step in use
 *
 * Called by the arch code after a संकेत handler has been set up.
 * Register and stack state reflects the user handler about to run.
 * Signal mask changes have alपढ़ोy been made.
 *
 * Called without locks, लघुly beक्रमe वापसing to user mode
 * (or handling more संकेतs).
 */
अटल अंतरभूत व्योम tracehook_संकेत_handler(पूर्णांक stepping)
अणु
	अगर (stepping)
		ptrace_notअगरy(SIGTRAP);
पूर्ण

/**
 * set_notअगरy_resume - cause tracehook_notअगरy_resume() to be called
 * @task:		task that will call tracehook_notअगरy_resume()
 *
 * Calling this arranges that @task will call tracehook_notअगरy_resume()
 * beक्रमe वापसing to user mode.  If it's alपढ़ोy running in user mode,
 * it will enter the kernel and call tracehook_notअगरy_resume() soon.
 * If it's blocked, it will not be woken.
 */
अटल अंतरभूत व्योम set_notअगरy_resume(काष्ठा task_काष्ठा *task)
अणु
#अगर_घोषित TIF_NOTIFY_RESUME
	अगर (!test_and_set_tsk_thपढ़ो_flag(task, TIF_NOTIFY_RESUME))
		kick_process(task);
#पूर्ण_अगर
पूर्ण

/**
 * tracehook_notअगरy_resume - report when about to वापस to user mode
 * @regs:		user-mode रेजिस्टरs of @current task
 *
 * This is called when %TIF_NOTIFY_RESUME has been set.  Now we are
 * about to वापस to user mode, and the user state in @regs can be
 * inspected or adjusted.  The caller in arch code has cleared
 * %TIF_NOTIFY_RESUME beक्रमe the call.  If the flag माला_लो set again
 * asynchronously, this will be called again beक्रमe we वापस to
 * user mode.
 *
 * Called without locks.
 */
अटल अंतरभूत व्योम tracehook_notअगरy_resume(काष्ठा pt_regs *regs)
अणु
	clear_thपढ़ो_flag(TIF_NOTIFY_RESUME);
	/*
	 * This barrier pairs with task_work_add()->set_notअगरy_resume() after
	 * hlist_add_head(task->task_works);
	 */
	smp_mb__after_atomic();
	अगर (unlikely(current->task_works))
		task_work_run();

#अगर_घोषित CONFIG_KEYS_REQUEST_CACHE
	अगर (unlikely(current->cached_requested_key)) अणु
		key_put(current->cached_requested_key);
		current->cached_requested_key = शून्य;
	पूर्ण
#पूर्ण_अगर

	mem_cgroup_handle_over_high();
	blkcg_maybe_throttle_current();
पूर्ण

/*
 * called by निकास_to_user_mode_loop() अगर ti_work & _TIF_NOTIFY_SIGNAL. This
 * is currently used by TWA_SIGNAL based task_work, which requires अवरोधing
 * रुको loops to ensure that task_work is noticed and run.
 */
अटल अंतरभूत व्योम tracehook_notअगरy_संकेत(व्योम)
अणु
	clear_thपढ़ो_flag(TIF_NOTIFY_SIGNAL);
	smp_mb__after_atomic();
	अगर (current->task_works)
		task_work_run();
पूर्ण

/*
 * Called when we have work to process from निकास_to_user_mode_loop()
 */
अटल अंतरभूत व्योम set_notअगरy_संकेत(काष्ठा task_काष्ठा *task)
अणु
	अगर (!test_and_set_tsk_thपढ़ो_flag(task, TIF_NOTIFY_SIGNAL) &&
	    !wake_up_state(task, TASK_INTERRUPTIBLE))
		kick_process(task);
पूर्ण

#पूर्ण_अगर	/* <linux/tracehook.h> */
