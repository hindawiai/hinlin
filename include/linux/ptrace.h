<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PTRACE_H
#घोषणा _LINUX_PTRACE_H

#समावेश <linux/compiler.h>		/* For unlikely.  */
#समावेश <linux/sched.h>		/* For काष्ठा task_काष्ठा.  */
#समावेश <linux/sched/संकेत.स>		/* For send_sig(), same_thपढ़ो_group(), etc. */
#समावेश <linux/err.h>			/* क्रम IS_ERR_VALUE */
#समावेश <linux/bug.h>			/* For BUG_ON.  */
#समावेश <linux/pid_namespace.h>	/* For task_active_pid_ns.  */
#समावेश <uapi/linux/ptrace.h>
#समावेश <linux/seccomp.h>

/* Add sp to seccomp_data, as seccomp is user API, we करोn't want to modअगरy it */
काष्ठा syscall_info अणु
	__u64			sp;
	काष्ठा seccomp_data	data;
पूर्ण;

बाह्य पूर्णांक ptrace_access_vm(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ addr,
			    व्योम *buf, पूर्णांक len, अचिन्हित पूर्णांक gup_flags);

/*
 * Ptrace flags
 *
 * The owner ship rules क्रम task->ptrace which holds the ptrace
 * flags is simple.  When a task is running it owns it's task->ptrace
 * flags.  When the a task is stopped the ptracer owns task->ptrace.
 */

#घोषणा PT_SEIZED	0x00010000	/* SEIZE used, enable new behavior */
#घोषणा PT_PTRACED	0x00000001
#घोषणा PT_DTRACE	0x00000002	/* delayed trace (used on m68k, i386) */

#घोषणा PT_OPT_FLAG_SHIFT	3
/* PT_TRACE_* event enable flags */
#घोषणा PT_EVENT_FLAG(event)	(1 << (PT_OPT_FLAG_SHIFT + (event)))
#घोषणा PT_TRACESYSGOOD		PT_EVENT_FLAG(0)
#घोषणा PT_TRACE_FORK		PT_EVENT_FLAG(PTRACE_EVENT_FORK)
#घोषणा PT_TRACE_VFORK		PT_EVENT_FLAG(PTRACE_EVENT_VFORK)
#घोषणा PT_TRACE_CLONE		PT_EVENT_FLAG(PTRACE_EVENT_CLONE)
#घोषणा PT_TRACE_EXEC		PT_EVENT_FLAG(PTRACE_EVENT_EXEC)
#घोषणा PT_TRACE_VFORK_DONE	PT_EVENT_FLAG(PTRACE_EVENT_VFORK_DONE)
#घोषणा PT_TRACE_EXIT		PT_EVENT_FLAG(PTRACE_EVENT_EXIT)
#घोषणा PT_TRACE_SECCOMP	PT_EVENT_FLAG(PTRACE_EVENT_SECCOMP)

#घोषणा PT_EXITKILL		(PTRACE_O_EXITKILL << PT_OPT_FLAG_SHIFT)
#घोषणा PT_SUSPEND_SECCOMP	(PTRACE_O_SUSPEND_SECCOMP << PT_OPT_FLAG_SHIFT)

/* single stepping state bits (used on ARM and PA-RISC) */
#घोषणा PT_SINGLESTEP_BIT	31
#घोषणा PT_SINGLESTEP		(1<<PT_SINGLESTEP_BIT)
#घोषणा PT_BLOCKSTEP_BIT	30
#घोषणा PT_BLOCKSTEP		(1<<PT_BLOCKSTEP_BIT)

बाह्य दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data);
बाह्य पूर्णांक ptrace_पढ़ोdata(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ src, अक्षर __user *dst, पूर्णांक len);
बाह्य पूर्णांक ptrace_ग_लिखोdata(काष्ठा task_काष्ठा *tsk, अक्षर __user *src, अचिन्हित दीर्घ dst, पूर्णांक len);
बाह्य व्योम ptrace_disable(काष्ठा task_काष्ठा *);
बाह्य पूर्णांक ptrace_request(काष्ठा task_काष्ठा *child, दीर्घ request,
			  अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data);
बाह्य व्योम ptrace_notअगरy(पूर्णांक निकास_code);
बाह्य व्योम __ptrace_link(काष्ठा task_काष्ठा *child,
			  काष्ठा task_काष्ठा *new_parent,
			  स्थिर काष्ठा cred *ptracer_cred);
बाह्य व्योम __ptrace_unlink(काष्ठा task_काष्ठा *child);
बाह्य व्योम निकास_ptrace(काष्ठा task_काष्ठा *tracer, काष्ठा list_head *dead);
#घोषणा PTRACE_MODE_READ	0x01
#घोषणा PTRACE_MODE_ATTACH	0x02
#घोषणा PTRACE_MODE_NOAUDIT	0x04
#घोषणा PTRACE_MODE_FSCREDS	0x08
#घोषणा PTRACE_MODE_REALCREDS	0x10

/* लघुhands क्रम READ/ATTACH and FSCREDS/REALCREDS combinations */
#घोषणा PTRACE_MODE_READ_FSCREDS (PTRACE_MODE_READ | PTRACE_MODE_FSCREDS)
#घोषणा PTRACE_MODE_READ_REALCREDS (PTRACE_MODE_READ | PTRACE_MODE_REALCREDS)
#घोषणा PTRACE_MODE_ATTACH_FSCREDS (PTRACE_MODE_ATTACH | PTRACE_MODE_FSCREDS)
#घोषणा PTRACE_MODE_ATTACH_REALCREDS (PTRACE_MODE_ATTACH | PTRACE_MODE_REALCREDS)

/**
 * ptrace_may_access - check whether the caller is permitted to access
 * a target task.
 * @task: target task
 * @mode: selects type of access and caller credentials
 *
 * Returns true on success, false on denial.
 *
 * One of the flags PTRACE_MODE_FSCREDS and PTRACE_MODE_REALCREDS must
 * be set in @mode to specअगरy whether the access was requested through
 * a fileप्रणाली syscall (should use effective capabilities and fsuid
 * of the caller) or through an explicit syscall such as
 * process_vm_ग_लिखोv or ptrace (and should use the real credentials).
 */
बाह्य bool ptrace_may_access(काष्ठा task_काष्ठा *task, अचिन्हित पूर्णांक mode);

अटल अंतरभूत पूर्णांक ptrace_reparented(काष्ठा task_काष्ठा *child)
अणु
	वापस !same_thपढ़ो_group(child->real_parent, child->parent);
पूर्ण

अटल अंतरभूत व्योम ptrace_unlink(काष्ठा task_काष्ठा *child)
अणु
	अगर (unlikely(child->ptrace))
		__ptrace_unlink(child);
पूर्ण

पूर्णांक generic_ptrace_peekdata(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ data);
पूर्णांक generic_ptrace_pokedata(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ data);

/**
 * ptrace_parent - वापस the task that is tracing the given task
 * @task: task to consider
 *
 * Returns %शून्य अगर no one is tracing @task, or the &काष्ठा task_काष्ठा
 * poपूर्णांकer to its tracer.
 *
 * Must called under rcu_पढ़ो_lock().  The poपूर्णांकer वापसed might be kept
 * live only by RCU.  During exec, this may be called with task_lock() held
 * on @task, still held from when check_unsafe_exec() was called.
 */
अटल अंतरभूत काष्ठा task_काष्ठा *ptrace_parent(काष्ठा task_काष्ठा *task)
अणु
	अगर (unlikely(task->ptrace))
		वापस rcu_dereference(task->parent);
	वापस शून्य;
पूर्ण

/**
 * ptrace_event_enabled - test whether a ptrace event is enabled
 * @task: ptracee of पूर्णांकerest
 * @event: %PTRACE_EVENT_* to test
 *
 * Test whether @event is enabled क्रम ptracee @task.
 *
 * Returns %true अगर @event is enabled, %false otherwise.
 */
अटल अंतरभूत bool ptrace_event_enabled(काष्ठा task_काष्ठा *task, पूर्णांक event)
अणु
	वापस task->ptrace & PT_EVENT_FLAG(event);
पूर्ण

/**
 * ptrace_event - possibly stop क्रम a ptrace event notअगरication
 * @event:	%PTRACE_EVENT_* value to report
 * @message:	value क्रम %PTRACE_GETEVENTMSG to वापस
 *
 * Check whether @event is enabled and, अगर so, report @event and @message
 * to the ptrace parent.
 *
 * Called without locks.
 */
अटल अंतरभूत व्योम ptrace_event(पूर्णांक event, अचिन्हित दीर्घ message)
अणु
	अगर (unlikely(ptrace_event_enabled(current, event))) अणु
		current->ptrace_message = message;
		ptrace_notअगरy((event << 8) | SIGTRAP);
	पूर्ण अन्यथा अगर (event == PTRACE_EVENT_EXEC) अणु
		/* legacy EXEC report via SIGTRAP */
		अगर ((current->ptrace & (PT_PTRACED|PT_SEIZED)) == PT_PTRACED)
			send_sig(SIGTRAP, current, 0);
	पूर्ण
पूर्ण

/**
 * ptrace_event_pid - possibly stop क्रम a ptrace event notअगरication
 * @event:	%PTRACE_EVENT_* value to report
 * @pid:	process identअगरier क्रम %PTRACE_GETEVENTMSG to वापस
 *
 * Check whether @event is enabled and, अगर so, report @event and @pid
 * to the ptrace parent.  @pid is reported as the pid_t seen from the
 * ptrace parent's pid namespace.
 *
 * Called without locks.
 */
अटल अंतरभूत व्योम ptrace_event_pid(पूर्णांक event, काष्ठा pid *pid)
अणु
	/*
	 * FIXME: There's a potential race अगर a ptracer in a dअगरferent pid
	 * namespace than parent attaches between computing message below and
	 * when we acquire tasklist_lock in ptrace_stop().  If this happens,
	 * the ptracer will get a bogus pid from PTRACE_GETEVENTMSG.
	 */
	अचिन्हित दीर्घ message = 0;
	काष्ठा pid_namespace *ns;

	rcu_पढ़ो_lock();
	ns = task_active_pid_ns(rcu_dereference(current->parent));
	अगर (ns)
		message = pid_nr_ns(pid, ns);
	rcu_पढ़ो_unlock();

	ptrace_event(event, message);
पूर्ण

/**
 * ptrace_init_task - initialize ptrace state क्रम a new child
 * @child:		new child task
 * @ptrace:		true अगर child should be ptrace'd by parent's tracer
 *
 * This is called immediately after adding @child to its parent's children
 * list.  @ptrace is false in the normal हाल, and true to ptrace @child.
 *
 * Called with current's siglock and ग_लिखो_lock_irq(&tasklist_lock) held.
 */
अटल अंतरभूत व्योम ptrace_init_task(काष्ठा task_काष्ठा *child, bool ptrace)
अणु
	INIT_LIST_HEAD(&child->ptrace_entry);
	INIT_LIST_HEAD(&child->ptraced);
	child->jobctl = 0;
	child->ptrace = 0;
	child->parent = child->real_parent;

	अगर (unlikely(ptrace) && current->ptrace) अणु
		child->ptrace = current->ptrace;
		__ptrace_link(child, current->parent, current->ptracer_cred);

		अगर (child->ptrace & PT_SEIZED)
			task_set_jobctl_pending(child, JOBCTL_TRAP_STOP);
		अन्यथा
			sigaddset(&child->pending.संकेत, SIGSTOP);
	पूर्ण
	अन्यथा
		child->ptracer_cred = शून्य;
पूर्ण

/**
 * ptrace_release_task - final ptrace-related cleanup of a zombie being reaped
 * @task:	task in %EXIT_DEAD state
 *
 * Called with ग_लिखो_lock(&tasklist_lock) held.
 */
अटल अंतरभूत व्योम ptrace_release_task(काष्ठा task_काष्ठा *task)
अणु
	BUG_ON(!list_empty(&task->ptraced));
	ptrace_unlink(task);
	BUG_ON(!list_empty(&task->ptrace_entry));
पूर्ण

#अगर_अघोषित क्रमce_successful_syscall_वापस
/*
 * System call handlers that, upon successful completion, need to वापस a
 * negative value should call क्रमce_successful_syscall_वापस() right beक्रमe
 * वापसing.  On architectures where the syscall convention provides क्रम a
 * separate error flag (e.g., alpha, ia64, ppcअणु,64पूर्ण, sparcअणु,64पूर्ण, possibly
 * others), this macro can be used to ensure that the error flag will not get
 * set.  On architectures which करो not support a separate error flag, the macro
 * is a no-op and the spurious error condition needs to be filtered out by some
 * other means (e.g., in user-level, by passing an extra argument to the
 * syscall handler, or something aदीर्घ those lines).
 */
#घोषणा क्रमce_successful_syscall_वापस() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित is_syscall_success
/*
 * On most प्रणालीs we can tell अगर a syscall is a success based on अगर the retval
 * is an error value.  On some प्रणालीs like ia64 and घातerpc they have dअगरferent
 * indicators of success/failure and must define their own.
 */
#घोषणा is_syscall_success(regs) (!IS_ERR_VALUE((अचिन्हित दीर्घ)(regs_वापस_value(regs))))
#पूर्ण_अगर

/*
 * <यंत्र/ptrace.h> should define the following things inside #अगर_घोषित __KERNEL__.
 *
 * These करो-nothing अंतरभूतs are used when the arch करोes not
 * implement single-step.  The kernelकरोc comments are here
 * to करोcument the पूर्णांकerface क्रम all arch definitions.
 */

#अगर_अघोषित arch_has_single_step
/**
 * arch_has_single_step - करोes this CPU support user-mode single-step?
 *
 * If this is defined, then there must be function declarations or
 * अंतरभूतs क्रम user_enable_single_step() and user_disable_single_step().
 * arch_has_single_step() should evaluate to nonzero अगरf the machine
 * supports inकाष्ठाion single-step क्रम user mode.
 * It can be a स्थिरant or it can test a CPU feature bit.
 */
#घोषणा arch_has_single_step()		(0)

/**
 * user_enable_single_step - single-step in user-mode task
 * @task: either current or a task stopped in %TASK_TRACED
 *
 * This can only be called when arch_has_single_step() has वापसed nonzero.
 * Set @task so that when it वापसs to user mode, it will trap after the
 * next single inकाष्ठाion executes.  If arch_has_block_step() is defined,
 * this must clear the effects of user_enable_block_step() too.
 */
अटल अंतरभूत व्योम user_enable_single_step(काष्ठा task_काष्ठा *task)
अणु
	BUG();			/* This can never be called.  */
पूर्ण

/**
 * user_disable_single_step - cancel user-mode single-step
 * @task: either current or a task stopped in %TASK_TRACED
 *
 * Clear @task of the effects of user_enable_single_step() and
 * user_enable_block_step().  This can be called whether or not either
 * of those was ever called on @task, and even अगर arch_has_single_step()
 * वापसed zero.
 */
अटल अंतरभूत व्योम user_disable_single_step(काष्ठा task_काष्ठा *task)
अणु
पूर्ण
#अन्यथा
बाह्य व्योम user_enable_single_step(काष्ठा task_काष्ठा *);
बाह्य व्योम user_disable_single_step(काष्ठा task_काष्ठा *);
#पूर्ण_अगर	/* arch_has_single_step */

#अगर_अघोषित arch_has_block_step
/**
 * arch_has_block_step - करोes this CPU support user-mode block-step?
 *
 * If this is defined, then there must be a function declaration or अंतरभूत
 * क्रम user_enable_block_step(), and arch_has_single_step() must be defined
 * too.  arch_has_block_step() should evaluate to nonzero अगरf the machine
 * supports step-until-branch क्रम user mode.  It can be a स्थिरant or it
 * can test a CPU feature bit.
 */
#घोषणा arch_has_block_step()		(0)

/**
 * user_enable_block_step - step until branch in user-mode task
 * @task: either current or a task stopped in %TASK_TRACED
 *
 * This can only be called when arch_has_block_step() has वापसed nonzero,
 * and will never be called when single-inकाष्ठाion stepping is being used.
 * Set @task so that when it वापसs to user mode, it will trap after the
 * next branch or trap taken.
 */
अटल अंतरभूत व्योम user_enable_block_step(काष्ठा task_काष्ठा *task)
अणु
	BUG();			/* This can never be called.  */
पूर्ण
#अन्यथा
बाह्य व्योम user_enable_block_step(काष्ठा task_काष्ठा *);
#पूर्ण_अगर	/* arch_has_block_step */

#अगर_घोषित ARCH_HAS_USER_SINGLE_STEP_REPORT
बाह्य व्योम user_single_step_report(काष्ठा pt_regs *regs);
#अन्यथा
अटल अंतरभूत व्योम user_single_step_report(काष्ठा pt_regs *regs)
अणु
	kernel_siginfo_t info;
	clear_siginfo(&info);
	info.si_signo = SIGTRAP;
	info.si_त्रुटि_सं = 0;
	info.si_code = SI_USER;
	info.si_pid = 0;
	info.si_uid = 0;
	क्रमce_sig_info(&info);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित arch_ptrace_stop_needed
/**
 * arch_ptrace_stop_needed - Decide whether arch_ptrace_stop() should be called
 * @code:	current->निकास_code value ptrace will stop with
 * @info:	siginfo_t poपूर्णांकer (or %शून्य) क्रम संकेत ptrace will stop with
 *
 * This is called with the siglock held, to decide whether or not it's
 * necessary to release the siglock and call arch_ptrace_stop() with the
 * same @code and @info arguments.  It can be defined to a स्थिरant अगर
 * arch_ptrace_stop() is never required, or always is.  On machines where
 * this makes sense, it should be defined to a quick test to optimize out
 * calling arch_ptrace_stop() when it would be superfluous.  For example,
 * अगर the thपढ़ो has not been back to user mode since the last stop, the
 * thपढ़ो state might indicate that nothing needs to be करोne.
 *
 * This is guaranteed to be invoked once beक्रमe a task stops क्रम ptrace and
 * may include arch-specअगरic operations necessary prior to a ptrace stop.
 */
#घोषणा arch_ptrace_stop_needed(code, info)	(0)
#पूर्ण_अगर

#अगर_अघोषित arch_ptrace_stop
/**
 * arch_ptrace_stop - Do machine-specअगरic work beक्रमe stopping क्रम ptrace
 * @code:	current->निकास_code value ptrace will stop with
 * @info:	siginfo_t poपूर्णांकer (or %शून्य) क्रम संकेत ptrace will stop with
 *
 * This is called with no locks held when arch_ptrace_stop_needed() has
 * just वापसed nonzero.  It is allowed to block, e.g. क्रम user memory
 * access.  The arch can have machine-specअगरic work to be करोne beक्रमe
 * ptrace stops.  On ia64, रेजिस्टर backing store माला_लो written back to user
 * memory here.  Since this can be costly (requires dropping the siglock),
 * we only करो it when the arch requires it क्रम this particular stop, as
 * indicated by arch_ptrace_stop_needed().
 */
#घोषणा arch_ptrace_stop(code, info)		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित current_pt_regs
#घोषणा current_pt_regs() task_pt_regs(current)
#पूर्ण_अगर

/*
 * unlike current_pt_regs(), this one is equal to task_pt_regs(current)
 * on *all* architectures; the only reason to have a per-arch definition
 * is optimisation.
 */
#अगर_अघोषित संकेत_pt_regs
#घोषणा संकेत_pt_regs() task_pt_regs(current)
#पूर्ण_अगर

#अगर_अघोषित current_user_stack_poपूर्णांकer
#घोषणा current_user_stack_poपूर्णांकer() user_stack_poपूर्णांकer(current_pt_regs())
#पूर्ण_अगर

बाह्य पूर्णांक task_current_syscall(काष्ठा task_काष्ठा *target, काष्ठा syscall_info *info);

बाह्य व्योम sigaction_compat_abi(काष्ठा k_sigaction *act, काष्ठा k_sigaction *oact);
#पूर्ण_अगर
