<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/kernel/ptrace.c
 *
 * (C) Copyright 1999 Linus Torvalds
 *
 * Common पूर्णांकerfaces क्रम "ptrace()" which we करो not want
 * to continually duplicate across every architecture.
 */

#समावेश <linux/capability.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/security.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/uपन.स>
#समावेश <linux/audit.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/regset.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/cn_proc.h>
#समावेश <linux/compat.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/minmax.h>

#समावेश <यंत्र/syscall.h>	/* क्रम syscall_get_* */

/*
 * Access another process' address space via ptrace.
 * Source/target buffer must be kernel space,
 * Do not walk the page table directly, use get_user_pages
 */
पूर्णांक ptrace_access_vm(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ addr,
		     व्योम *buf, पूर्णांक len, अचिन्हित पूर्णांक gup_flags)
अणु
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक ret;

	mm = get_task_mm(tsk);
	अगर (!mm)
		वापस 0;

	अगर (!tsk->ptrace ||
	    (current != tsk->parent) ||
	    ((get_dumpable(mm) != SUID_DUMP_USER) &&
	     !ptracer_capable(tsk, mm->user_ns))) अणु
		mmput(mm);
		वापस 0;
	पूर्ण

	ret = __access_remote_vm(mm, addr, buf, len, gup_flags);
	mmput(mm);

	वापस ret;
पूर्ण


व्योम __ptrace_link(काष्ठा task_काष्ठा *child, काष्ठा task_काष्ठा *new_parent,
		   स्थिर काष्ठा cred *ptracer_cred)
अणु
	BUG_ON(!list_empty(&child->ptrace_entry));
	list_add(&child->ptrace_entry, &new_parent->ptraced);
	child->parent = new_parent;
	child->ptracer_cred = get_cred(ptracer_cred);
पूर्ण

/*
 * ptrace a task: make the debugger its new parent and
 * move it to the ptrace list.
 *
 * Must be called with the tasklist lock ग_लिखो-held.
 */
अटल व्योम ptrace_link(काष्ठा task_काष्ठा *child, काष्ठा task_काष्ठा *new_parent)
अणु
	__ptrace_link(child, new_parent, current_cred());
पूर्ण

/**
 * __ptrace_unlink - unlink ptracee and restore its execution state
 * @child: ptracee to be unlinked
 *
 * Remove @child from the ptrace list, move it back to the original parent,
 * and restore the execution state so that it conक्रमms to the group stop
 * state.
 *
 * Unlinking can happen via two paths - explicit PTRACE_DETACH or ptracer
 * निकासing.  For PTRACE_DETACH, unless the ptracee has been समाप्तed between
 * ptrace_check_attach() and here, it's guaranteed to be in TASK_TRACED.
 * If the ptracer is निकासing, the ptracee can be in any state.
 *
 * After detach, the ptracee should be in a state which conक्रमms to the
 * group stop.  If the group is stopped or in the process of stopping, the
 * ptracee should be put पूर्णांकo TASK_STOPPED; otherwise, it should be woken
 * up from TASK_TRACED.
 *
 * If the ptracee is in TASK_TRACED and needs to be moved to TASK_STOPPED,
 * it goes through TRACED -> RUNNING -> STOPPED transition which is similar
 * to but in the opposite direction of what happens जबतक attaching to a
 * stopped task.  However, in this direction, the पूर्णांकermediate RUNNING
 * state is not hidden even from the current ptracer and अगर it immediately
 * re-attaches and perक्रमms a WNOHANG रुको(2), it may fail.
 *
 * CONTEXT:
 * ग_लिखो_lock_irq(tasklist_lock)
 */
व्योम __ptrace_unlink(काष्ठा task_काष्ठा *child)
अणु
	स्थिर काष्ठा cred *old_cred;
	BUG_ON(!child->ptrace);

	clear_task_syscall_work(child, SYSCALL_TRACE);
#अगर defined(CONFIG_GENERIC_ENTRY) || defined(TIF_SYSCALL_EMU)
	clear_task_syscall_work(child, SYSCALL_EMU);
#पूर्ण_अगर

	child->parent = child->real_parent;
	list_del_init(&child->ptrace_entry);
	old_cred = child->ptracer_cred;
	child->ptracer_cred = शून्य;
	put_cred(old_cred);

	spin_lock(&child->sighand->siglock);
	child->ptrace = 0;
	/*
	 * Clear all pending traps and TRAPPING.  TRAPPING should be
	 * cleared regardless of JOBCTL_STOP_PENDING.  Do it explicitly.
	 */
	task_clear_jobctl_pending(child, JOBCTL_TRAP_MASK);
	task_clear_jobctl_trapping(child);

	/*
	 * Reinstate JOBCTL_STOP_PENDING अगर group stop is in effect and
	 * @child isn't dead.
	 */
	अगर (!(child->flags & PF_EXITING) &&
	    (child->संकेत->flags & SIGNAL_STOP_STOPPED ||
	     child->संकेत->group_stop_count)) अणु
		child->jobctl |= JOBCTL_STOP_PENDING;

		/*
		 * This is only possible अगर this thपढ़ो was cloned by the
		 * traced task running in the stopped group, set the संकेत
		 * क्रम the future reports.
		 * FIXME: we should change ptrace_init_task() to handle this
		 * हाल.
		 */
		अगर (!(child->jobctl & JOBCTL_STOP_SIGMASK))
			child->jobctl |= SIGSTOP;
	पूर्ण

	/*
	 * If transition to TASK_STOPPED is pending or in TASK_TRACED, kick
	 * @child in the butt.  Note that @resume should be used अगरf @child
	 * is in TASK_TRACED; otherwise, we might unduly disrupt
	 * TASK_KILLABLE sleeps.
	 */
	अगर (child->jobctl & JOBCTL_STOP_PENDING || task_is_traced(child))
		ptrace_संकेत_wake_up(child, true);

	spin_unlock(&child->sighand->siglock);
पूर्ण

अटल bool looks_like_a_spurious_pid(काष्ठा task_काष्ठा *task)
अणु
	अगर (task->निकास_code != ((PTRACE_EVENT_EXEC << 8) | SIGTRAP))
		वापस false;

	अगर (task_pid_vnr(task) == task->ptrace_message)
		वापस false;
	/*
	 * The tracee changed its pid but the PTRACE_EVENT_EXEC event
	 * was not रुको()'ed, most probably debugger tarमाला_लो the old
	 * leader which was destroyed in de_thपढ़ो().
	 */
	वापस true;
पूर्ण

/* Ensure that nothing can wake it up, even SIGKILL */
अटल bool ptrace_मुक्तze_traced(काष्ठा task_काष्ठा *task)
अणु
	bool ret = false;

	/* Lockless, nobody but us can set this flag */
	अगर (task->jobctl & JOBCTL_LISTENING)
		वापस ret;

	spin_lock_irq(&task->sighand->siglock);
	अगर (task_is_traced(task) && !looks_like_a_spurious_pid(task) &&
	    !__fatal_संकेत_pending(task)) अणु
		task->state = __TASK_TRACED;
		ret = true;
	पूर्ण
	spin_unlock_irq(&task->sighand->siglock);

	वापस ret;
पूर्ण

अटल व्योम ptrace_unमुक्तze_traced(काष्ठा task_काष्ठा *task)
अणु
	अगर (task->state != __TASK_TRACED)
		वापस;

	WARN_ON(!task->ptrace || task->parent != current);

	/*
	 * PTRACE_LISTEN can allow ptrace_trap_notअगरy to wake us up remotely.
	 * Recheck state under the lock to बंद this race.
	 */
	spin_lock_irq(&task->sighand->siglock);
	अगर (task->state == __TASK_TRACED) अणु
		अगर (__fatal_संकेत_pending(task))
			wake_up_state(task, __TASK_TRACED);
		अन्यथा
			task->state = TASK_TRACED;
	पूर्ण
	spin_unlock_irq(&task->sighand->siglock);
पूर्ण

/**
 * ptrace_check_attach - check whether ptracee is पढ़ोy क्रम ptrace operation
 * @child: ptracee to check क्रम
 * @ignore_state: करोn't check whether @child is currently %TASK_TRACED
 *
 * Check whether @child is being ptraced by %current and पढ़ोy क्रम further
 * ptrace operations.  If @ignore_state is %false, @child also should be in
 * %TASK_TRACED state and on वापस the child is guaranteed to be traced
 * and not executing.  If @ignore_state is %true, @child can be in any
 * state.
 *
 * CONTEXT:
 * Grअसल and releases tasklist_lock and @child->sighand->siglock.
 *
 * RETURNS:
 * 0 on success, -ESRCH अगर %child is not पढ़ोy.
 */
अटल पूर्णांक ptrace_check_attach(काष्ठा task_काष्ठा *child, bool ignore_state)
अणु
	पूर्णांक ret = -ESRCH;

	/*
	 * We take the पढ़ो lock around करोing both checks to बंद a
	 * possible race where someone अन्यथा was tracing our child and
	 * detached between these two checks.  After this locked check,
	 * we are sure that this is our traced child and that can only
	 * be changed by us so it's not changing right after this.
	 */
	पढ़ो_lock(&tasklist_lock);
	अगर (child->ptrace && child->parent == current) अणु
		WARN_ON(child->state == __TASK_TRACED);
		/*
		 * child->sighand can't be शून्य, release_task()
		 * करोes ptrace_unlink() beक्रमe __निकास_संकेत().
		 */
		अगर (ignore_state || ptrace_मुक्तze_traced(child))
			ret = 0;
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);

	अगर (!ret && !ignore_state) अणु
		अगर (!रुको_task_inactive(child, __TASK_TRACED)) अणु
			/*
			 * This can only happen अगर may_ptrace_stop() fails and
			 * ptrace_stop() changes ->state back to TASK_RUNNING,
			 * so we should not worry about leaking __TASK_TRACED.
			 */
			WARN_ON(child->state == __TASK_TRACED);
			ret = -ESRCH;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल bool ptrace_has_cap(काष्ठा user_namespace *ns, अचिन्हित पूर्णांक mode)
अणु
	अगर (mode & PTRACE_MODE_NOAUDIT)
		वापस ns_capable_noaudit(ns, CAP_SYS_PTRACE);
	वापस ns_capable(ns, CAP_SYS_PTRACE);
पूर्ण

/* Returns 0 on success, -त्रुटि_सं on denial. */
अटल पूर्णांक __ptrace_may_access(काष्ठा task_काष्ठा *task, अचिन्हित पूर्णांक mode)
अणु
	स्थिर काष्ठा cred *cred = current_cred(), *tcred;
	काष्ठा mm_काष्ठा *mm;
	kuid_t caller_uid;
	kgid_t caller_gid;

	अगर (!(mode & PTRACE_MODE_FSCREDS) == !(mode & PTRACE_MODE_REALCREDS)) अणु
		WARN(1, "denying ptrace access check without PTRACE_MODE_*CREDS\n");
		वापस -EPERM;
	पूर्ण

	/* May we inspect the given task?
	 * This check is used both क्रम attaching with ptrace
	 * and क्रम allowing access to sensitive inक्रमmation in /proc.
	 *
	 * ptrace_attach denies several हालs that /proc allows
	 * because setting up the necessary parent/child relationship
	 * or halting the specअगरied task is impossible.
	 */

	/* Don't let security modules deny पूर्णांकrospection */
	अगर (same_thपढ़ो_group(task, current))
		वापस 0;
	rcu_पढ़ो_lock();
	अगर (mode & PTRACE_MODE_FSCREDS) अणु
		caller_uid = cred->fsuid;
		caller_gid = cred->fsgid;
	पूर्ण अन्यथा अणु
		/*
		 * Using the euid would make more sense here, but something
		 * in userland might rely on the old behavior, and this
		 * shouldn't be a security problem since
		 * PTRACE_MODE_REALCREDS implies that the caller explicitly
		 * used a syscall that requests access to another process
		 * (and not a fileप्रणाली syscall to procfs).
		 */
		caller_uid = cred->uid;
		caller_gid = cred->gid;
	पूर्ण
	tcred = __task_cred(task);
	अगर (uid_eq(caller_uid, tcred->euid) &&
	    uid_eq(caller_uid, tcred->suid) &&
	    uid_eq(caller_uid, tcred->uid)  &&
	    gid_eq(caller_gid, tcred->egid) &&
	    gid_eq(caller_gid, tcred->sgid) &&
	    gid_eq(caller_gid, tcred->gid))
		जाओ ok;
	अगर (ptrace_has_cap(tcred->user_ns, mode))
		जाओ ok;
	rcu_पढ़ो_unlock();
	वापस -EPERM;
ok:
	rcu_पढ़ो_unlock();
	/*
	 * If a task drops privileges and becomes nondumpable (through a syscall
	 * like setresuid()) जबतक we are trying to access it, we must ensure
	 * that the dumpability is पढ़ो after the credentials; otherwise,
	 * we may be able to attach to a task that we shouldn't be able to
	 * attach to (as अगर the task had dropped privileges without becoming
	 * nondumpable).
	 * Pairs with a ग_लिखो barrier in commit_creds().
	 */
	smp_rmb();
	mm = task->mm;
	अगर (mm &&
	    ((get_dumpable(mm) != SUID_DUMP_USER) &&
	     !ptrace_has_cap(mm->user_ns, mode)))
	    वापस -EPERM;

	वापस security_ptrace_access_check(task, mode);
पूर्ण

bool ptrace_may_access(काष्ठा task_काष्ठा *task, अचिन्हित पूर्णांक mode)
अणु
	पूर्णांक err;
	task_lock(task);
	err = __ptrace_may_access(task, mode);
	task_unlock(task);
	वापस !err;
पूर्ण

अटल पूर्णांक ptrace_attach(काष्ठा task_काष्ठा *task, दीर्घ request,
			 अचिन्हित दीर्घ addr,
			 अचिन्हित दीर्घ flags)
अणु
	bool seize = (request == PTRACE_SEIZE);
	पूर्णांक retval;

	retval = -EIO;
	अगर (seize) अणु
		अगर (addr != 0)
			जाओ out;
		अगर (flags & ~(अचिन्हित दीर्घ)PTRACE_O_MASK)
			जाओ out;
		flags = PT_PTRACED | PT_SEIZED | (flags << PT_OPT_FLAG_SHIFT);
	पूर्ण अन्यथा अणु
		flags = PT_PTRACED;
	पूर्ण

	audit_ptrace(task);

	retval = -EPERM;
	अगर (unlikely(task->flags & PF_KTHREAD))
		जाओ out;
	अगर (same_thपढ़ो_group(task, current))
		जाओ out;

	/*
	 * Protect exec's credential calculations against our पूर्णांकerference;
	 * SUID, SGID and LSM creds get determined dअगरferently
	 * under ptrace.
	 */
	retval = -ERESTARTNOINTR;
	अगर (mutex_lock_पूर्णांकerruptible(&task->संकेत->cred_guard_mutex))
		जाओ out;

	task_lock(task);
	retval = __ptrace_may_access(task, PTRACE_MODE_ATTACH_REALCREDS);
	task_unlock(task);
	अगर (retval)
		जाओ unlock_creds;

	ग_लिखो_lock_irq(&tasklist_lock);
	retval = -EPERM;
	अगर (unlikely(task->निकास_state))
		जाओ unlock_tasklist;
	अगर (task->ptrace)
		जाओ unlock_tasklist;

	अगर (seize)
		flags |= PT_SEIZED;
	task->ptrace = flags;

	ptrace_link(task, current);

	/* SEIZE करोesn't trap tracee on attach */
	अगर (!seize)
		send_sig_info(SIGSTOP, SEND_SIG_PRIV, task);

	spin_lock(&task->sighand->siglock);

	/*
	 * If the task is alपढ़ोy STOPPED, set JOBCTL_TRAP_STOP and
	 * TRAPPING, and kick it so that it transits to TRACED.  TRAPPING
	 * will be cleared अगर the child completes the transition or any
	 * event which clears the group stop states happens.  We'll रुको
	 * क्रम the transition to complete beक्रमe वापसing from this
	 * function.
	 *
	 * This hides STOPPED -> RUNNING -> TRACED transition from the
	 * attaching thपढ़ो but a dअगरferent thपढ़ो in the same group can
	 * still observe the transient RUNNING state.  IOW, अगर another
	 * thपढ़ो's WNOHANG रुको(2) on the stopped tracee races against
	 * ATTACH, the रुको(2) may fail due to the transient RUNNING.
	 *
	 * The following task_is_stopped() test is safe as both transitions
	 * in and out of STOPPED are रक्षित by siglock.
	 */
	अगर (task_is_stopped(task) &&
	    task_set_jobctl_pending(task, JOBCTL_TRAP_STOP | JOBCTL_TRAPPING))
		संकेत_wake_up_state(task, __TASK_STOPPED);

	spin_unlock(&task->sighand->siglock);

	retval = 0;
unlock_tasklist:
	ग_लिखो_unlock_irq(&tasklist_lock);
unlock_creds:
	mutex_unlock(&task->संकेत->cred_guard_mutex);
out:
	अगर (!retval) अणु
		/*
		 * We करो not bother to change retval or clear JOBCTL_TRAPPING
		 * अगर रुको_on_bit() was पूर्णांकerrupted by SIGKILL. The tracer will
		 * not वापस to user-mode, it will निकास and clear this bit in
		 * __ptrace_unlink() अगर it wasn't alपढ़ोy cleared by the tracee;
		 * and until then nobody can ptrace this task.
		 */
		रुको_on_bit(&task->jobctl, JOBCTL_TRAPPING_BIT, TASK_KILLABLE);
		proc_ptrace_connector(task, PTRACE_ATTACH);
	पूर्ण

	वापस retval;
पूर्ण

/**
 * ptrace_traceme  --  helper क्रम PTRACE_TRACEME
 *
 * Perक्रमms checks and sets PT_PTRACED.
 * Should be used by all ptrace implementations क्रम PTRACE_TRACEME.
 */
अटल पूर्णांक ptrace_traceme(व्योम)
अणु
	पूर्णांक ret = -EPERM;

	ग_लिखो_lock_irq(&tasklist_lock);
	/* Are we alपढ़ोy being traced? */
	अगर (!current->ptrace) अणु
		ret = security_ptrace_traceme(current->parent);
		/*
		 * Check PF_EXITING to ensure ->real_parent has not passed
		 * निकास_ptrace(). Otherwise we करोn't report the error but
		 * pretend ->real_parent untraces us right after वापस.
		 */
		अगर (!ret && !(current->real_parent->flags & PF_EXITING)) अणु
			current->ptrace = PT_PTRACED;
			ptrace_link(current, current->real_parent);
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_irq(&tasklist_lock);

	वापस ret;
पूर्ण

/*
 * Called with irqs disabled, वापसs true अगर childs should reap themselves.
 */
अटल पूर्णांक ignoring_children(काष्ठा sighand_काष्ठा *sigh)
अणु
	पूर्णांक ret;
	spin_lock(&sigh->siglock);
	ret = (sigh->action[SIGCHLD-1].sa.sa_handler == संक_छोड़ो) ||
	      (sigh->action[SIGCHLD-1].sa.sa_flags & SA_NOCLDWAIT);
	spin_unlock(&sigh->siglock);
	वापस ret;
पूर्ण

/*
 * Called with tasklist_lock held क्रम writing.
 * Unlink a traced task, and clean it up अगर it was a traced zombie.
 * Return true अगर it needs to be reaped with release_task().
 * (We can't call release_task() here because we alपढ़ोy hold tasklist_lock.)
 *
 * If it's a zombie, our attachedness prevented normal parent notअगरication
 * or self-reaping.  Do notअगरication now अगर it would have happened earlier.
 * If it should reap itself, वापस true.
 *
 * If it's our own child, there is no notअगरication to करो. But अगर our normal
 * children self-reap, then this child was prevented by ptrace and we must
 * reap it now, in that हाल we must also wake up sub-thपढ़ोs sleeping in
 * करो_रुको().
 */
अटल bool __ptrace_detach(काष्ठा task_काष्ठा *tracer, काष्ठा task_काष्ठा *p)
अणु
	bool dead;

	__ptrace_unlink(p);

	अगर (p->निकास_state != EXIT_ZOMBIE)
		वापस false;

	dead = !thपढ़ो_group_leader(p);

	अगर (!dead && thपढ़ो_group_empty(p)) अणु
		अगर (!same_thपढ़ो_group(p->real_parent, tracer))
			dead = करो_notअगरy_parent(p, p->निकास_संकेत);
		अन्यथा अगर (ignoring_children(tracer->sighand)) अणु
			__wake_up_parent(p, tracer);
			dead = true;
		पूर्ण
	पूर्ण
	/* Mark it as in the process of being reaped. */
	अगर (dead)
		p->निकास_state = EXIT_DEAD;
	वापस dead;
पूर्ण

अटल पूर्णांक ptrace_detach(काष्ठा task_काष्ठा *child, अचिन्हित पूर्णांक data)
अणु
	अगर (!valid_संकेत(data))
		वापस -EIO;

	/* Architecture-specअगरic hardware disable .. */
	ptrace_disable(child);

	ग_लिखो_lock_irq(&tasklist_lock);
	/*
	 * We rely on ptrace_मुक्तze_traced(). It can't be समाप्तed and
	 * untraced by another thपढ़ो, it can't be a zombie.
	 */
	WARN_ON(!child->ptrace || child->निकास_state);
	/*
	 * tasklist_lock aव्योमs the race with रुको_task_stopped(), see
	 * the comment in ptrace_resume().
	 */
	child->निकास_code = data;
	__ptrace_detach(current, child);
	ग_लिखो_unlock_irq(&tasklist_lock);

	proc_ptrace_connector(child, PTRACE_DETACH);

	वापस 0;
पूर्ण

/*
 * Detach all tasks we were using ptrace on. Called with tasklist held
 * क्रम writing.
 */
व्योम निकास_ptrace(काष्ठा task_काष्ठा *tracer, काष्ठा list_head *dead)
अणु
	काष्ठा task_काष्ठा *p, *n;

	list_क्रम_each_entry_safe(p, n, &tracer->ptraced, ptrace_entry) अणु
		अगर (unlikely(p->ptrace & PT_EXITKILL))
			send_sig_info(SIGKILL, SEND_SIG_PRIV, p);

		अगर (__ptrace_detach(tracer, p))
			list_add(&p->ptrace_entry, dead);
	पूर्ण
पूर्ण

पूर्णांक ptrace_पढ़ोdata(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ src, अक्षर __user *dst, पूर्णांक len)
अणु
	पूर्णांक copied = 0;

	जबतक (len > 0) अणु
		अक्षर buf[128];
		पूर्णांक this_len, retval;

		this_len = (len > माप(buf)) ? माप(buf) : len;
		retval = ptrace_access_vm(tsk, src, buf, this_len, FOLL_FORCE);

		अगर (!retval) अणु
			अगर (copied)
				अवरोध;
			वापस -EIO;
		पूर्ण
		अगर (copy_to_user(dst, buf, retval))
			वापस -EFAULT;
		copied += retval;
		src += retval;
		dst += retval;
		len -= retval;
	पूर्ण
	वापस copied;
पूर्ण

पूर्णांक ptrace_ग_लिखोdata(काष्ठा task_काष्ठा *tsk, अक्षर __user *src, अचिन्हित दीर्घ dst, पूर्णांक len)
अणु
	पूर्णांक copied = 0;

	जबतक (len > 0) अणु
		अक्षर buf[128];
		पूर्णांक this_len, retval;

		this_len = (len > माप(buf)) ? माप(buf) : len;
		अगर (copy_from_user(buf, src, this_len))
			वापस -EFAULT;
		retval = ptrace_access_vm(tsk, dst, buf, this_len,
				FOLL_FORCE | FOLL_WRITE);
		अगर (!retval) अणु
			अगर (copied)
				अवरोध;
			वापस -EIO;
		पूर्ण
		copied += retval;
		src += retval;
		dst += retval;
		len -= retval;
	पूर्ण
	वापस copied;
पूर्ण

अटल पूर्णांक ptrace_setoptions(काष्ठा task_काष्ठा *child, अचिन्हित दीर्घ data)
अणु
	अचिन्हित flags;

	अगर (data & ~(अचिन्हित दीर्घ)PTRACE_O_MASK)
		वापस -EINVAL;

	अगर (unlikely(data & PTRACE_O_SUSPEND_SECCOMP)) अणु
		अगर (!IS_ENABLED(CONFIG_CHECKPOINT_RESTORE) ||
		    !IS_ENABLED(CONFIG_SECCOMP))
			वापस -EINVAL;

		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		अगर (seccomp_mode(&current->seccomp) != SECCOMP_MODE_DISABLED ||
		    current->ptrace & PT_SUSPEND_SECCOMP)
			वापस -EPERM;
	पूर्ण

	/* Aव्योम पूर्णांकermediate state when all opts are cleared */
	flags = child->ptrace;
	flags &= ~(PTRACE_O_MASK << PT_OPT_FLAG_SHIFT);
	flags |= (data << PT_OPT_FLAG_SHIFT);
	child->ptrace = flags;

	वापस 0;
पूर्ण

अटल पूर्णांक ptrace_माला_लोiginfo(काष्ठा task_काष्ठा *child, kernel_siginfo_t *info)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक error = -ESRCH;

	अगर (lock_task_sighand(child, &flags)) अणु
		error = -EINVAL;
		अगर (likely(child->last_siginfo != शून्य)) अणु
			copy_siginfo(info, child->last_siginfo);
			error = 0;
		पूर्ण
		unlock_task_sighand(child, &flags);
	पूर्ण
	वापस error;
पूर्ण

अटल पूर्णांक ptrace_setsiginfo(काष्ठा task_काष्ठा *child, स्थिर kernel_siginfo_t *info)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक error = -ESRCH;

	अगर (lock_task_sighand(child, &flags)) अणु
		error = -EINVAL;
		अगर (likely(child->last_siginfo != शून्य)) अणु
			copy_siginfo(child->last_siginfo, info);
			error = 0;
		पूर्ण
		unlock_task_sighand(child, &flags);
	पूर्ण
	वापस error;
पूर्ण

अटल पूर्णांक ptrace_peek_siginfo(काष्ठा task_काष्ठा *child,
				अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ data)
अणु
	काष्ठा ptrace_peeksiginfo_args arg;
	काष्ठा संक_बाकी *pending;
	काष्ठा sigqueue *q;
	पूर्णांक ret, i;

	ret = copy_from_user(&arg, (व्योम __user *) addr,
				माप(काष्ठा ptrace_peeksiginfo_args));
	अगर (ret)
		वापस -EFAULT;

	अगर (arg.flags & ~PTRACE_PEEKSIGINFO_SHARED)
		वापस -EINVAL; /* unknown flags */

	अगर (arg.nr < 0)
		वापस -EINVAL;

	/* Ensure arg.off fits in an अचिन्हित दीर्घ */
	अगर (arg.off > अच_दीर्घ_उच्च)
		वापस 0;

	अगर (arg.flags & PTRACE_PEEKSIGINFO_SHARED)
		pending = &child->संकेत->shared_pending;
	अन्यथा
		pending = &child->pending;

	क्रम (i = 0; i < arg.nr; ) अणु
		kernel_siginfo_t info;
		अचिन्हित दीर्घ off = arg.off + i;
		bool found = false;

		spin_lock_irq(&child->sighand->siglock);
		list_क्रम_each_entry(q, &pending->list, list) अणु
			अगर (!off--) अणु
				found = true;
				copy_siginfo(&info, &q->info);
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_irq(&child->sighand->siglock);

		अगर (!found) /* beyond the end of the list */
			अवरोध;

#अगर_घोषित CONFIG_COMPAT
		अगर (unlikely(in_compat_syscall())) अणु
			compat_siginfo_t __user *uinfo = compat_ptr(data);

			अगर (copy_siginfo_to_user32(uinfo, &info)) अणु
				ret = -EFAULT;
				अवरोध;
			पूर्ण

		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			siginfo_t __user *uinfo = (siginfo_t __user *) data;

			अगर (copy_siginfo_to_user(uinfo, &info)) अणु
				ret = -EFAULT;
				अवरोध;
			पूर्ण
		पूर्ण

		data += माप(siginfo_t);
		i++;

		अगर (संकेत_pending(current))
			अवरोध;

		cond_resched();
	पूर्ण

	अगर (i > 0)
		वापस i;

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_RSEQ
अटल दीर्घ ptrace_get_rseq_configuration(काष्ठा task_काष्ठा *task,
					  अचिन्हित दीर्घ size, व्योम __user *data)
अणु
	काष्ठा ptrace_rseq_configuration conf = अणु
		.rseq_abi_poपूर्णांकer = (u64)(uपूर्णांकptr_t)task->rseq,
		.rseq_abi_size = माप(*task->rseq),
		.signature = task->rseq_sig,
		.flags = 0,
	पूर्ण;

	size = min_t(अचिन्हित दीर्घ, size, माप(conf));
	अगर (copy_to_user(data, &conf, size))
		वापस -EFAULT;
	वापस माप(conf);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित PTRACE_SINGLESTEP
#घोषणा is_singlestep(request)		((request) == PTRACE_SINGLESTEP)
#अन्यथा
#घोषणा is_singlestep(request)		0
#पूर्ण_अगर

#अगर_घोषित PTRACE_SINGLEBLOCK
#घोषणा is_singleblock(request)		((request) == PTRACE_SINGLEBLOCK)
#अन्यथा
#घोषणा is_singleblock(request)		0
#पूर्ण_अगर

#अगर_घोषित PTRACE_SYSEMU
#घोषणा is_sysemu_singlestep(request)	((request) == PTRACE_SYSEMU_SINGLESTEP)
#अन्यथा
#घोषणा is_sysemu_singlestep(request)	0
#पूर्ण_अगर

अटल पूर्णांक ptrace_resume(काष्ठा task_काष्ठा *child, दीर्घ request,
			 अचिन्हित दीर्घ data)
अणु
	bool need_siglock;

	अगर (!valid_संकेत(data))
		वापस -EIO;

	अगर (request == PTRACE_SYSCALL)
		set_task_syscall_work(child, SYSCALL_TRACE);
	अन्यथा
		clear_task_syscall_work(child, SYSCALL_TRACE);

#अगर defined(CONFIG_GENERIC_ENTRY) || defined(TIF_SYSCALL_EMU)
	अगर (request == PTRACE_SYSEMU || request == PTRACE_SYSEMU_SINGLESTEP)
		set_task_syscall_work(child, SYSCALL_EMU);
	अन्यथा
		clear_task_syscall_work(child, SYSCALL_EMU);
#पूर्ण_अगर

	अगर (is_singleblock(request)) अणु
		अगर (unlikely(!arch_has_block_step()))
			वापस -EIO;
		user_enable_block_step(child);
	पूर्ण अन्यथा अगर (is_singlestep(request) || is_sysemu_singlestep(request)) अणु
		अगर (unlikely(!arch_has_single_step()))
			वापस -EIO;
		user_enable_single_step(child);
	पूर्ण अन्यथा अणु
		user_disable_single_step(child);
	पूर्ण

	/*
	 * Change ->निकास_code and ->state under siglock to aव्योम the race
	 * with रुको_task_stopped() in between; a non-zero ->निकास_code will
	 * wrongly look like another report from tracee.
	 *
	 * Note that we need siglock even अगर ->निकास_code == data and/or this
	 * status was not reported yet, the new status must not be cleared by
	 * रुको_task_stopped() after resume.
	 *
	 * If data == 0 we करो not care अगर रुको_task_stopped() reports the old
	 * status and clears the code too; this can't race with the tracee, it
	 * takes siglock after resume.
	 */
	need_siglock = data && !thपढ़ो_group_empty(current);
	अगर (need_siglock)
		spin_lock_irq(&child->sighand->siglock);
	child->निकास_code = data;
	wake_up_state(child, __TASK_TRACED);
	अगर (need_siglock)
		spin_unlock_irq(&child->sighand->siglock);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_TRACEHOOK

अटल स्थिर काष्ठा user_regset *
find_regset(स्थिर काष्ठा user_regset_view *view, अचिन्हित पूर्णांक type)
अणु
	स्थिर काष्ठा user_regset *regset;
	पूर्णांक n;

	क्रम (n = 0; n < view->n; ++n) अणु
		regset = view->regsets + n;
		अगर (regset->core_note_type == type)
			वापस regset;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक ptrace_regset(काष्ठा task_काष्ठा *task, पूर्णांक req, अचिन्हित पूर्णांक type,
			 काष्ठा iovec *kiov)
अणु
	स्थिर काष्ठा user_regset_view *view = task_user_regset_view(task);
	स्थिर काष्ठा user_regset *regset = find_regset(view, type);
	पूर्णांक regset_no;

	अगर (!regset || (kiov->iov_len % regset->size) != 0)
		वापस -EINVAL;

	regset_no = regset - view->regsets;
	kiov->iov_len = min(kiov->iov_len,
			    (__kernel_माप_प्रकार) (regset->n * regset->size));

	अगर (req == PTRACE_GETREGSET)
		वापस copy_regset_to_user(task, view, regset_no, 0,
					   kiov->iov_len, kiov->iov_base);
	अन्यथा
		वापस copy_regset_from_user(task, view, regset_no, 0,
					     kiov->iov_len, kiov->iov_base);
पूर्ण

/*
 * This is declared in linux/regset.h and defined in machine-dependent
 * code.  We put the export here, near the primary machine-neutral use,
 * to ensure no machine क्रममाला_लो it.
 */
EXPORT_SYMBOL_GPL(task_user_regset_view);

अटल अचिन्हित दीर्घ
ptrace_get_syscall_info_entry(काष्ठा task_काष्ठा *child, काष्ठा pt_regs *regs,
			      काष्ठा ptrace_syscall_info *info)
अणु
	अचिन्हित दीर्घ args[ARRAY_SIZE(info->entry.args)];
	पूर्णांक i;

	info->op = PTRACE_SYSCALL_INFO_ENTRY;
	info->entry.nr = syscall_get_nr(child, regs);
	syscall_get_arguments(child, regs, args);
	क्रम (i = 0; i < ARRAY_SIZE(args); i++)
		info->entry.args[i] = args[i];

	/* args is the last field in काष्ठा ptrace_syscall_info.entry */
	वापस दुरत्वend(काष्ठा ptrace_syscall_info, entry.args);
पूर्ण

अटल अचिन्हित दीर्घ
ptrace_get_syscall_info_seccomp(काष्ठा task_काष्ठा *child, काष्ठा pt_regs *regs,
				काष्ठा ptrace_syscall_info *info)
अणु
	/*
	 * As काष्ठा ptrace_syscall_info.entry is currently a subset
	 * of काष्ठा ptrace_syscall_info.seccomp, it makes sense to
	 * initialize that subset using ptrace_get_syscall_info_entry().
	 * This can be reconsidered in the future अगर these काष्ठाures
	 * भागerge signअगरicantly enough.
	 */
	ptrace_get_syscall_info_entry(child, regs, info);
	info->op = PTRACE_SYSCALL_INFO_SECCOMP;
	info->seccomp.ret_data = child->ptrace_message;

	/* ret_data is the last field in काष्ठा ptrace_syscall_info.seccomp */
	वापस दुरत्वend(काष्ठा ptrace_syscall_info, seccomp.ret_data);
पूर्ण

अटल अचिन्हित दीर्घ
ptrace_get_syscall_info_निकास(काष्ठा task_काष्ठा *child, काष्ठा pt_regs *regs,
			     काष्ठा ptrace_syscall_info *info)
अणु
	info->op = PTRACE_SYSCALL_INFO_EXIT;
	info->निकास.rval = syscall_get_error(child, regs);
	info->निकास.is_error = !!info->निकास.rval;
	अगर (!info->निकास.is_error)
		info->निकास.rval = syscall_get_वापस_value(child, regs);

	/* is_error is the last field in काष्ठा ptrace_syscall_info.निकास */
	वापस दुरत्वend(काष्ठा ptrace_syscall_info, निकास.is_error);
पूर्ण

अटल पूर्णांक
ptrace_get_syscall_info(काष्ठा task_काष्ठा *child, अचिन्हित दीर्घ user_size,
			व्योम __user *datavp)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(child);
	काष्ठा ptrace_syscall_info info = अणु
		.op = PTRACE_SYSCALL_INFO_NONE,
		.arch = syscall_get_arch(child),
		.inकाष्ठाion_poपूर्णांकer = inकाष्ठाion_poपूर्णांकer(regs),
		.stack_poपूर्णांकer = user_stack_poपूर्णांकer(regs),
	पूर्ण;
	अचिन्हित दीर्घ actual_size = दुरत्व(काष्ठा ptrace_syscall_info, entry);
	अचिन्हित दीर्घ ग_लिखो_size;

	/*
	 * This करोes not need lock_task_sighand() to access
	 * child->last_siginfo because ptrace_मुक्तze_traced()
	 * called earlier by ptrace_check_attach() ensures that
	 * the tracee cannot go away and clear its last_siginfo.
	 */
	चयन (child->last_siginfo ? child->last_siginfo->si_code : 0) अणु
	हाल SIGTRAP | 0x80:
		चयन (child->ptrace_message) अणु
		हाल PTRACE_EVENTMSG_SYSCALL_ENTRY:
			actual_size = ptrace_get_syscall_info_entry(child, regs,
								    &info);
			अवरोध;
		हाल PTRACE_EVENTMSG_SYSCALL_EXIT:
			actual_size = ptrace_get_syscall_info_निकास(child, regs,
								   &info);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SIGTRAP | (PTRACE_EVENT_SECCOMP << 8):
		actual_size = ptrace_get_syscall_info_seccomp(child, regs,
							      &info);
		अवरोध;
	पूर्ण

	ग_लिखो_size = min(actual_size, user_size);
	वापस copy_to_user(datavp, &info, ग_लिखो_size) ? -EFAULT : actual_size;
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_TRACEHOOK */

पूर्णांक ptrace_request(काष्ठा task_काष्ठा *child, दीर्घ request,
		   अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	bool seized = child->ptrace & PT_SEIZED;
	पूर्णांक ret = -EIO;
	kernel_siginfo_t siginfo, *si;
	व्योम __user *datavp = (व्योम __user *) data;
	अचिन्हित दीर्घ __user *datalp = datavp;
	अचिन्हित दीर्घ flags;

	चयन (request) अणु
	हाल PTRACE_PEEKTEXT:
	हाल PTRACE_PEEKDATA:
		वापस generic_ptrace_peekdata(child, addr, data);
	हाल PTRACE_POKETEXT:
	हाल PTRACE_POKEDATA:
		वापस generic_ptrace_pokedata(child, addr, data);

#अगर_घोषित PTRACE_OLDSETOPTIONS
	हाल PTRACE_OLDSETOPTIONS:
#पूर्ण_अगर
	हाल PTRACE_SETOPTIONS:
		ret = ptrace_setoptions(child, data);
		अवरोध;
	हाल PTRACE_GETEVENTMSG:
		ret = put_user(child->ptrace_message, datalp);
		अवरोध;

	हाल PTRACE_PEEKSIGINFO:
		ret = ptrace_peek_siginfo(child, addr, data);
		अवरोध;

	हाल PTRACE_GETSIGINFO:
		ret = ptrace_माला_लोiginfo(child, &siginfo);
		अगर (!ret)
			ret = copy_siginfo_to_user(datavp, &siginfo);
		अवरोध;

	हाल PTRACE_SETSIGINFO:
		ret = copy_siginfo_from_user(&siginfo, datavp);
		अगर (!ret)
			ret = ptrace_setsiginfo(child, &siginfo);
		अवरोध;

	हाल PTRACE_GETSIGMASK: अणु
		sigset_t *mask;

		अगर (addr != माप(sigset_t)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (test_tsk_restore_sigmask(child))
			mask = &child->saved_sigmask;
		अन्यथा
			mask = &child->blocked;

		अगर (copy_to_user(datavp, mask, माप(sigset_t)))
			ret = -EFAULT;
		अन्यथा
			ret = 0;

		अवरोध;
	पूर्ण

	हाल PTRACE_SETSIGMASK: अणु
		sigset_t new_set;

		अगर (addr != माप(sigset_t)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (copy_from_user(&new_set, datavp, माप(sigset_t))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		sigdअन्यथापंचांगask(&new_set, sigmask(SIGKILL)|sigmask(SIGSTOP));

		/*
		 * Every thपढ़ो करोes recalc_संक_बाकी() after resume, so
		 * retarget_shared_pending() and recalc_संक_बाकी() are not
		 * called here.
		 */
		spin_lock_irq(&child->sighand->siglock);
		child->blocked = new_set;
		spin_unlock_irq(&child->sighand->siglock);

		clear_tsk_restore_sigmask(child);

		ret = 0;
		अवरोध;
	पूर्ण

	हाल PTRACE_INTERRUPT:
		/*
		 * Stop tracee without any side-effect on संकेत or job
		 * control.  At least one trap is guaranteed to happen
		 * after this request.  If @child is alपढ़ोy trapped, the
		 * current trap is not disturbed and another trap will
		 * happen after the current trap is ended with PTRACE_CONT.
		 *
		 * The actual trap might not be PTRACE_EVENT_STOP trap but
		 * the pending condition is cleared regardless.
		 */
		अगर (unlikely(!seized || !lock_task_sighand(child, &flags)))
			अवरोध;

		/*
		 * INTERRUPT करोesn't disturb existing trap sans one
		 * exception.  If ptracer issued LISTEN क्रम the current
		 * STOP, this INTERRUPT should clear LISTEN and re-trap
		 * tracee पूर्णांकo STOP.
		 */
		अगर (likely(task_set_jobctl_pending(child, JOBCTL_TRAP_STOP)))
			ptrace_संकेत_wake_up(child, child->jobctl & JOBCTL_LISTENING);

		unlock_task_sighand(child, &flags);
		ret = 0;
		अवरोध;

	हाल PTRACE_LISTEN:
		/*
		 * Listen क्रम events.  Tracee must be in STOP.  It's not
		 * resumed per-se but is not considered to be in TRACED by
		 * रुको(2) or ptrace(2).  If an async event (e.g. group
		 * stop state change) happens, tracee will enter STOP trap
		 * again.  Alternatively, ptracer can issue INTERRUPT to
		 * finish listening and re-trap tracee पूर्णांकo STOP.
		 */
		अगर (unlikely(!seized || !lock_task_sighand(child, &flags)))
			अवरोध;

		si = child->last_siginfo;
		अगर (likely(si && (si->si_code >> 8) == PTRACE_EVENT_STOP)) अणु
			child->jobctl |= JOBCTL_LISTENING;
			/*
			 * If NOTIFY is set, it means event happened between
			 * start of this trap and now.  Trigger re-trap.
			 */
			अगर (child->jobctl & JOBCTL_TRAP_NOTIFY)
				ptrace_संकेत_wake_up(child, true);
			ret = 0;
		पूर्ण
		unlock_task_sighand(child, &flags);
		अवरोध;

	हाल PTRACE_DETACH:	 /* detach a process that was attached. */
		ret = ptrace_detach(child, data);
		अवरोध;

#अगर_घोषित CONFIG_BINFMT_ELF_FDPIC
	हाल PTRACE_GETFDPIC: अणु
		काष्ठा mm_काष्ठा *mm = get_task_mm(child);
		अचिन्हित दीर्घ पंचांगp = 0;

		ret = -ESRCH;
		अगर (!mm)
			अवरोध;

		चयन (addr) अणु
		हाल PTRACE_GETFDPIC_EXEC:
			पंचांगp = mm->context.exec_fdpic_loadmap;
			अवरोध;
		हाल PTRACE_GETFDPIC_INTERP:
			पंचांगp = mm->context.पूर्णांकerp_fdpic_loadmap;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		mmput(mm);

		ret = put_user(पंचांगp, datalp);
		अवरोध;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित PTRACE_SINGLESTEP
	हाल PTRACE_SINGLESTEP:
#पूर्ण_अगर
#अगर_घोषित PTRACE_SINGLEBLOCK
	हाल PTRACE_SINGLEBLOCK:
#पूर्ण_अगर
#अगर_घोषित PTRACE_SYSEMU
	हाल PTRACE_SYSEMU:
	हाल PTRACE_SYSEMU_SINGLESTEP:
#पूर्ण_अगर
	हाल PTRACE_SYSCALL:
	हाल PTRACE_CONT:
		वापस ptrace_resume(child, request, data);

	हाल PTRACE_KILL:
		अगर (child->निकास_state)	/* alपढ़ोy dead */
			वापस 0;
		वापस ptrace_resume(child, request, SIGKILL);

#अगर_घोषित CONFIG_HAVE_ARCH_TRACEHOOK
	हाल PTRACE_GETREGSET:
	हाल PTRACE_SETREGSET: अणु
		काष्ठा iovec kiov;
		काष्ठा iovec __user *uiov = datavp;

		अगर (!access_ok(uiov, माप(*uiov)))
			वापस -EFAULT;

		अगर (__get_user(kiov.iov_base, &uiov->iov_base) ||
		    __get_user(kiov.iov_len, &uiov->iov_len))
			वापस -EFAULT;

		ret = ptrace_regset(child, request, addr, &kiov);
		अगर (!ret)
			ret = __put_user(kiov.iov_len, &uiov->iov_len);
		अवरोध;
	पूर्ण

	हाल PTRACE_GET_SYSCALL_INFO:
		ret = ptrace_get_syscall_info(child, addr, datavp);
		अवरोध;
#पूर्ण_अगर

	हाल PTRACE_SECCOMP_GET_FILTER:
		ret = seccomp_get_filter(child, addr, datavp);
		अवरोध;

	हाल PTRACE_SECCOMP_GET_METADATA:
		ret = seccomp_get_metadata(child, addr, datavp);
		अवरोध;

#अगर_घोषित CONFIG_RSEQ
	हाल PTRACE_GET_RSEQ_CONFIGURATION:
		ret = ptrace_get_rseq_configuration(child, addr, datavp);
		अवरोध;
#पूर्ण_अगर

	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

#अगर_अघोषित arch_ptrace_attach
#घोषणा arch_ptrace_attach(child)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

SYSCALL_DEFINE4(ptrace, दीर्घ, request, दीर्घ, pid, अचिन्हित दीर्घ, addr,
		अचिन्हित दीर्घ, data)
अणु
	काष्ठा task_काष्ठा *child;
	दीर्घ ret;

	अगर (request == PTRACE_TRACEME) अणु
		ret = ptrace_traceme();
		अगर (!ret)
			arch_ptrace_attach(current);
		जाओ out;
	पूर्ण

	child = find_get_task_by_vpid(pid);
	अगर (!child) अणु
		ret = -ESRCH;
		जाओ out;
	पूर्ण

	अगर (request == PTRACE_ATTACH || request == PTRACE_SEIZE) अणु
		ret = ptrace_attach(child, request, addr, data);
		/*
		 * Some architectures need to करो book-keeping after
		 * a ptrace attach.
		 */
		अगर (!ret)
			arch_ptrace_attach(child);
		जाओ out_put_task_काष्ठा;
	पूर्ण

	ret = ptrace_check_attach(child, request == PTRACE_KILL ||
				  request == PTRACE_INTERRUPT);
	अगर (ret < 0)
		जाओ out_put_task_काष्ठा;

	ret = arch_ptrace(child, request, addr, data);
	अगर (ret || request != PTRACE_DETACH)
		ptrace_unमुक्तze_traced(child);

 out_put_task_काष्ठा:
	put_task_काष्ठा(child);
 out:
	वापस ret;
पूर्ण

पूर्णांक generic_ptrace_peekdata(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ data)
अणु
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक copied;

	copied = ptrace_access_vm(tsk, addr, &पंचांगp, माप(पंचांगp), FOLL_FORCE);
	अगर (copied != माप(पंचांगp))
		वापस -EIO;
	वापस put_user(पंचांगp, (अचिन्हित दीर्घ __user *)data);
पूर्ण

पूर्णांक generic_ptrace_pokedata(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ data)
अणु
	पूर्णांक copied;

	copied = ptrace_access_vm(tsk, addr, &data, माप(data),
			FOLL_FORCE | FOLL_WRITE);
	वापस (copied == माप(data)) ? 0 : -EIO;
पूर्ण

#अगर defined CONFIG_COMPAT

पूर्णांक compat_ptrace_request(काष्ठा task_काष्ठा *child, compat_दीर्घ_t request,
			  compat_uदीर्घ_t addr, compat_uदीर्घ_t data)
अणु
	compat_uदीर्घ_t __user *datap = compat_ptr(data);
	compat_uदीर्घ_t word;
	kernel_siginfo_t siginfo;
	पूर्णांक ret;

	चयन (request) अणु
	हाल PTRACE_PEEKTEXT:
	हाल PTRACE_PEEKDATA:
		ret = ptrace_access_vm(child, addr, &word, माप(word),
				FOLL_FORCE);
		अगर (ret != माप(word))
			ret = -EIO;
		अन्यथा
			ret = put_user(word, datap);
		अवरोध;

	हाल PTRACE_POKETEXT:
	हाल PTRACE_POKEDATA:
		ret = ptrace_access_vm(child, addr, &data, माप(data),
				FOLL_FORCE | FOLL_WRITE);
		ret = (ret != माप(data) ? -EIO : 0);
		अवरोध;

	हाल PTRACE_GETEVENTMSG:
		ret = put_user((compat_uदीर्घ_t) child->ptrace_message, datap);
		अवरोध;

	हाल PTRACE_GETSIGINFO:
		ret = ptrace_माला_लोiginfo(child, &siginfo);
		अगर (!ret)
			ret = copy_siginfo_to_user32(
				(काष्ठा compat_siginfo __user *) datap,
				&siginfo);
		अवरोध;

	हाल PTRACE_SETSIGINFO:
		ret = copy_siginfo_from_user32(
			&siginfo, (काष्ठा compat_siginfo __user *) datap);
		अगर (!ret)
			ret = ptrace_setsiginfo(child, &siginfo);
		अवरोध;
#अगर_घोषित CONFIG_HAVE_ARCH_TRACEHOOK
	हाल PTRACE_GETREGSET:
	हाल PTRACE_SETREGSET:
	अणु
		काष्ठा iovec kiov;
		काष्ठा compat_iovec __user *uiov =
			(काष्ठा compat_iovec __user *) datap;
		compat_uptr_t ptr;
		compat_माप_प्रकार len;

		अगर (!access_ok(uiov, माप(*uiov)))
			वापस -EFAULT;

		अगर (__get_user(ptr, &uiov->iov_base) ||
		    __get_user(len, &uiov->iov_len))
			वापस -EFAULT;

		kiov.iov_base = compat_ptr(ptr);
		kiov.iov_len = len;

		ret = ptrace_regset(child, request, addr, &kiov);
		अगर (!ret)
			ret = __put_user(kiov.iov_len, &uiov->iov_len);
		अवरोध;
	पूर्ण
#पूर्ण_अगर

	शेष:
		ret = ptrace_request(child, request, addr, data);
	पूर्ण

	वापस ret;
पूर्ण

COMPAT_SYSCALL_DEFINE4(ptrace, compat_दीर्घ_t, request, compat_दीर्घ_t, pid,
		       compat_दीर्घ_t, addr, compat_दीर्घ_t, data)
अणु
	काष्ठा task_काष्ठा *child;
	दीर्घ ret;

	अगर (request == PTRACE_TRACEME) अणु
		ret = ptrace_traceme();
		जाओ out;
	पूर्ण

	child = find_get_task_by_vpid(pid);
	अगर (!child) अणु
		ret = -ESRCH;
		जाओ out;
	पूर्ण

	अगर (request == PTRACE_ATTACH || request == PTRACE_SEIZE) अणु
		ret = ptrace_attach(child, request, addr, data);
		/*
		 * Some architectures need to करो book-keeping after
		 * a ptrace attach.
		 */
		अगर (!ret)
			arch_ptrace_attach(child);
		जाओ out_put_task_काष्ठा;
	पूर्ण

	ret = ptrace_check_attach(child, request == PTRACE_KILL ||
				  request == PTRACE_INTERRUPT);
	अगर (!ret) अणु
		ret = compat_arch_ptrace(child, request, addr, data);
		अगर (ret || request != PTRACE_DETACH)
			ptrace_unमुक्तze_traced(child);
	पूर्ण

 out_put_task_काष्ठा:
	put_task_काष्ठा(child);
 out:
	वापस ret;
पूर्ण
#पूर्ण_अगर	/* CONFIG_COMPAT */
