<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/kernel/निकास.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/स्वतःgroup.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/capability.h>
#समावेश <linux/completion.h>
#समावेश <linux/personality.h>
#समावेश <linux/tty.h>
#समावेश <linux/iocontext.h>
#समावेश <linux/key.h>
#समावेश <linux/cpu.h>
#समावेश <linux/acct.h>
#समावेश <linux/tsacct_kern.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/profile.h>
#समावेश <linux/mount.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/taskstats_kern.h>
#समावेश <linux/delayacct.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/cn_proc.h>
#समावेश <linux/mutex.h>
#समावेश <linux/futex.h>
#समावेश <linux/pipe_fs_i.h>
#समावेश <linux/audit.h> /* क्रम audit_मुक्त() */
#समावेश <linux/resource.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/init_task.h>
#समावेश <linux/perf_event.h>
#समावेश <trace/events/sched.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/oom.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/shm.h>
#समावेश <linux/kcov.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rcuरुको.h>
#समावेश <linux/compat.h>
#समावेश <linux/io_uring.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/mmu_context.h>

अटल व्योम __unhash_process(काष्ठा task_काष्ठा *p, bool group_dead)
अणु
	nr_thपढ़ोs--;
	detach_pid(p, PIDTYPE_PID);
	अगर (group_dead) अणु
		detach_pid(p, PIDTYPE_TGID);
		detach_pid(p, PIDTYPE_PGID);
		detach_pid(p, PIDTYPE_SID);

		list_del_rcu(&p->tasks);
		list_del_init(&p->sibling);
		__this_cpu_dec(process_counts);
	पूर्ण
	list_del_rcu(&p->thपढ़ो_group);
	list_del_rcu(&p->thपढ़ो_node);
पूर्ण

/*
 * This function expects the tasklist_lock ग_लिखो-locked.
 */
अटल व्योम __निकास_संकेत(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा संकेत_काष्ठा *sig = tsk->संकेत;
	bool group_dead = thपढ़ो_group_leader(tsk);
	काष्ठा sighand_काष्ठा *sighand;
	काष्ठा tty_काष्ठा *tty;
	u64 uसमय, sसमय;

	sighand = rcu_dereference_check(tsk->sighand,
					lockdep_tasklist_lock_is_held());
	spin_lock(&sighand->siglock);

#अगर_घोषित CONFIG_POSIX_TIMERS
	posix_cpu_समयrs_निकास(tsk);
	अगर (group_dead)
		posix_cpu_समयrs_निकास_group(tsk);
#पूर्ण_अगर

	अगर (group_dead) अणु
		tty = sig->tty;
		sig->tty = शून्य;
	पूर्ण अन्यथा अणु
		/*
		 * If there is any task रुकोing क्रम the group निकास
		 * then notअगरy it:
		 */
		अगर (sig->notअगरy_count > 0 && !--sig->notअगरy_count)
			wake_up_process(sig->group_निकास_task);

		अगर (tsk == sig->curr_target)
			sig->curr_target = next_thपढ़ो(tsk);
	पूर्ण

	add_device_अक्रमomness((स्थिर व्योम*) &tsk->se.sum_exec_runसमय,
			      माप(अचिन्हित दीर्घ दीर्घ));

	/*
	 * Accumulate here the counters क्रम all thपढ़ोs as they die. We could
	 * skip the group leader because it is the last user of संकेत_काष्ठा,
	 * but we want to aव्योम the race with thपढ़ो_group_cpuसमय() which can
	 * see the empty ->thपढ़ो_head list.
	 */
	task_cpuसमय(tsk, &uसमय, &sसमय);
	ग_लिखो_seqlock(&sig->stats_lock);
	sig->uसमय += uसमय;
	sig->sसमय += sसमय;
	sig->gसमय += task_gसमय(tsk);
	sig->min_flt += tsk->min_flt;
	sig->maj_flt += tsk->maj_flt;
	sig->nvcsw += tsk->nvcsw;
	sig->nivcsw += tsk->nivcsw;
	sig->inblock += task_io_get_inblock(tsk);
	sig->oublock += task_io_get_oublock(tsk);
	task_io_accounting_add(&sig->ioac, &tsk->ioac);
	sig->sum_sched_runसमय += tsk->se.sum_exec_runसमय;
	sig->nr_thपढ़ोs--;
	__unhash_process(tsk, group_dead);
	ग_लिखो_sequnlock(&sig->stats_lock);

	/*
	 * Do this under ->siglock, we can race with another thपढ़ो
	 * करोing sigqueue_मुक्त() अगर we have SIGQUEUE_PREALLOC संकेतs.
	 */
	flush_sigqueue(&tsk->pending);
	tsk->sighand = शून्य;
	spin_unlock(&sighand->siglock);

	__cleanup_sighand(sighand);
	clear_tsk_thपढ़ो_flag(tsk, TIF_SIGPENDING);
	अगर (group_dead) अणु
		flush_sigqueue(&sig->shared_pending);
		tty_kref_put(tty);
	पूर्ण
	निकास_task_sigqueue_cache(tsk);
पूर्ण

अटल व्योम delayed_put_task_काष्ठा(काष्ठा rcu_head *rhp)
अणु
	काष्ठा task_काष्ठा *tsk = container_of(rhp, काष्ठा task_काष्ठा, rcu);

	perf_event_delayed_put(tsk);
	trace_sched_process_मुक्त(tsk);
	put_task_काष्ठा(tsk);
पूर्ण

व्योम put_task_काष्ठा_rcu_user(काष्ठा task_काष्ठा *task)
अणु
	अगर (refcount_dec_and_test(&task->rcu_users))
		call_rcu(&task->rcu, delayed_put_task_काष्ठा);
पूर्ण

व्योम release_task(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा task_काष्ठा *leader;
	काष्ठा pid *thपढ़ो_pid;
	पूर्णांक zap_leader;
repeat:
	/* करोn't need to get the RCU पढ़ोlock here - the process is dead and
	 * can't be modअगरying its own credentials. But shut RCU-lockdep up */
	rcu_पढ़ो_lock();
	atomic_dec(&__task_cred(p)->user->processes);
	rcu_पढ़ो_unlock();

	cgroup_release(p);

	ग_लिखो_lock_irq(&tasklist_lock);
	ptrace_release_task(p);
	thपढ़ो_pid = get_pid(p->thपढ़ो_pid);
	__निकास_संकेत(p);

	/*
	 * If we are the last non-leader member of the thपढ़ो
	 * group, and the leader is zombie, then notअगरy the
	 * group leader's parent process. (अगर it wants notअगरication.)
	 */
	zap_leader = 0;
	leader = p->group_leader;
	अगर (leader != p && thपढ़ो_group_empty(leader)
			&& leader->निकास_state == EXIT_ZOMBIE) अणु
		/*
		 * If we were the last child thपढ़ो and the leader has
		 * निकासed alपढ़ोy, and the leader's parent ignores SIGCHLD,
		 * then we are the one who should release the leader.
		 */
		zap_leader = करो_notअगरy_parent(leader, leader->निकास_संकेत);
		अगर (zap_leader)
			leader->निकास_state = EXIT_DEAD;
	पूर्ण

	ग_लिखो_unlock_irq(&tasklist_lock);
	seccomp_filter_release(p);
	proc_flush_pid(thपढ़ो_pid);
	put_pid(thपढ़ो_pid);
	release_thपढ़ो(p);
	put_task_काष्ठा_rcu_user(p);

	p = leader;
	अगर (unlikely(zap_leader))
		जाओ repeat;
पूर्ण

पूर्णांक rcuरुको_wake_up(काष्ठा rcuरुको *w)
अणु
	पूर्णांक ret = 0;
	काष्ठा task_काष्ठा *task;

	rcu_पढ़ो_lock();

	/*
	 * Order condition vs @task, such that everything prior to the load
	 * of @task is visible. This is the condition as to why the user called
	 * rcuरुको_wake() in the first place. Pairs with set_current_state()
	 * barrier (A) in rcuरुको_रुको_event().
	 *
	 *    WAIT                WAKE
	 *    [S] tsk = current	  [S] cond = true
	 *        MB (A)	      MB (B)
	 *    [L] cond		  [L] tsk
	 */
	smp_mb(); /* (B) */

	task = rcu_dereference(w->task);
	अगर (task)
		ret = wake_up_process(task);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rcuरुको_wake_up);

/*
 * Determine अगर a process group is "orphaned", according to the POSIX
 * definition in 2.2.2.52.  Orphaned process groups are not to be affected
 * by terminal-generated stop संकेतs.  Newly orphaned process groups are
 * to receive a SIGHUP and a SIGCONT.
 *
 * "I ask you, have you ever known what it is to be an orphan?"
 */
अटल पूर्णांक will_become_orphaned_pgrp(काष्ठा pid *pgrp,
					काष्ठा task_काष्ठा *ignored_task)
अणु
	काष्ठा task_काष्ठा *p;

	करो_each_pid_task(pgrp, PIDTYPE_PGID, p) अणु
		अगर ((p == ignored_task) ||
		    (p->निकास_state && thपढ़ो_group_empty(p)) ||
		    is_global_init(p->real_parent))
			जारी;

		अगर (task_pgrp(p->real_parent) != pgrp &&
		    task_session(p->real_parent) == task_session(p))
			वापस 0;
	पूर्ण जबतक_each_pid_task(pgrp, PIDTYPE_PGID, p);

	वापस 1;
पूर्ण

पूर्णांक is_current_pgrp_orphaned(व्योम)
अणु
	पूर्णांक retval;

	पढ़ो_lock(&tasklist_lock);
	retval = will_become_orphaned_pgrp(task_pgrp(current), शून्य);
	पढ़ो_unlock(&tasklist_lock);

	वापस retval;
पूर्ण

अटल bool has_stopped_jobs(काष्ठा pid *pgrp)
अणु
	काष्ठा task_काष्ठा *p;

	करो_each_pid_task(pgrp, PIDTYPE_PGID, p) अणु
		अगर (p->संकेत->flags & SIGNAL_STOP_STOPPED)
			वापस true;
	पूर्ण जबतक_each_pid_task(pgrp, PIDTYPE_PGID, p);

	वापस false;
पूर्ण

/*
 * Check to see अगर any process groups have become orphaned as
 * a result of our निकासing, and अगर they have any stopped jobs,
 * send them a SIGHUP and then a SIGCONT. (POSIX 3.2.2.2)
 */
अटल व्योम
समाप्त_orphaned_pgrp(काष्ठा task_काष्ठा *tsk, काष्ठा task_काष्ठा *parent)
अणु
	काष्ठा pid *pgrp = task_pgrp(tsk);
	काष्ठा task_काष्ठा *ignored_task = tsk;

	अगर (!parent)
		/* निकास: our father is in a dअगरferent pgrp than
		 * we are and we were the only connection outside.
		 */
		parent = tsk->real_parent;
	अन्यथा
		/* reparent: our child is in a dअगरferent pgrp than
		 * we are, and it was the only connection outside.
		 */
		ignored_task = शून्य;

	अगर (task_pgrp(parent) != pgrp &&
	    task_session(parent) == task_session(tsk) &&
	    will_become_orphaned_pgrp(pgrp, ignored_task) &&
	    has_stopped_jobs(pgrp)) अणु
		__समाप्त_pgrp_info(SIGHUP, SEND_SIG_PRIV, pgrp);
		__समाप्त_pgrp_info(SIGCONT, SEND_SIG_PRIV, pgrp);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_MEMCG
/*
 * A task is निकासing.   If it owned this mm, find a new owner क्रम the mm.
 */
व्योम mm_update_next_owner(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा task_काष्ठा *c, *g, *p = current;

retry:
	/*
	 * If the निकासing or execing task is not the owner, it's
	 * someone अन्यथा's problem.
	 */
	अगर (mm->owner != p)
		वापस;
	/*
	 * The current owner is निकासing/execing and there are no other
	 * candidates.  Do not leave the mm poपूर्णांकing to a possibly
	 * मुक्तd task काष्ठाure.
	 */
	अगर (atomic_पढ़ो(&mm->mm_users) <= 1) अणु
		WRITE_ONCE(mm->owner, शून्य);
		वापस;
	पूर्ण

	पढ़ो_lock(&tasklist_lock);
	/*
	 * Search in the children
	 */
	list_क्रम_each_entry(c, &p->children, sibling) अणु
		अगर (c->mm == mm)
			जाओ assign_new_owner;
	पूर्ण

	/*
	 * Search in the siblings
	 */
	list_क्रम_each_entry(c, &p->real_parent->children, sibling) अणु
		अगर (c->mm == mm)
			जाओ assign_new_owner;
	पूर्ण

	/*
	 * Search through everything अन्यथा, we should not get here often.
	 */
	क्रम_each_process(g) अणु
		अगर (g->flags & PF_KTHREAD)
			जारी;
		क्रम_each_thपढ़ो(g, c) अणु
			अगर (c->mm == mm)
				जाओ assign_new_owner;
			अगर (c->mm)
				अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);
	/*
	 * We found no owner yet mm_users > 1: this implies that we are
	 * most likely racing with swapoff (try_to_unuse()) or /proc or
	 * ptrace or page migration (get_task_mm()).  Mark owner as शून्य.
	 */
	WRITE_ONCE(mm->owner, शून्य);
	वापस;

assign_new_owner:
	BUG_ON(c == p);
	get_task_काष्ठा(c);
	/*
	 * The task_lock protects c->mm from changing.
	 * We always want mm->owner->mm == mm
	 */
	task_lock(c);
	/*
	 * Delay पढ़ो_unlock() till we have the task_lock()
	 * to ensure that c करोes not slip away underneath us
	 */
	पढ़ो_unlock(&tasklist_lock);
	अगर (c->mm != mm) अणु
		task_unlock(c);
		put_task_काष्ठा(c);
		जाओ retry;
	पूर्ण
	WRITE_ONCE(mm->owner, c);
	task_unlock(c);
	put_task_काष्ठा(c);
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMCG */

/*
 * Turn us पूर्णांकo a lazy TLB process अगर we
 * aren't alपढ़ोy..
 */
अटल व्योम निकास_mm(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा core_state *core_state;

	निकास_mm_release(current, mm);
	अगर (!mm)
		वापस;
	sync_mm_rss(mm);
	/*
	 * Serialize with any possible pending coredump.
	 * We must hold mmap_lock around checking core_state
	 * and clearing tsk->mm.  The core-inducing thपढ़ो
	 * will increment ->nr_thपढ़ोs क्रम each thपढ़ो in the
	 * group with ->mm != शून्य.
	 */
	mmap_पढ़ो_lock(mm);
	core_state = mm->core_state;
	अगर (core_state) अणु
		काष्ठा core_thपढ़ो self;

		mmap_पढ़ो_unlock(mm);

		self.task = current;
		अगर (self.task->flags & PF_SIGNALED)
			self.next = xchg(&core_state->dumper.next, &self);
		अन्यथा
			self.task = शून्य;
		/*
		 * Implies mb(), the result of xchg() must be visible
		 * to core_state->dumper.
		 */
		अगर (atomic_dec_and_test(&core_state->nr_thपढ़ोs))
			complete(&core_state->startup);

		क्रम (;;) अणु
			set_current_state(TASK_UNINTERRUPTIBLE);
			अगर (!self.task) /* see coredump_finish() */
				अवरोध;
			मुक्तzable_schedule();
		पूर्ण
		__set_current_state(TASK_RUNNING);
		mmap_पढ़ो_lock(mm);
	पूर्ण
	mmgrab(mm);
	BUG_ON(mm != current->active_mm);
	/* more a memory barrier than a real lock */
	task_lock(current);
	/*
	 * When a thपढ़ो stops operating on an address space, the loop
	 * in membarrier_निजी_expedited() may not observe that
	 * tsk->mm, and the loop in membarrier_global_expedited() may
	 * not observe a MEMBARRIER_STATE_GLOBAL_EXPEDITED
	 * rq->membarrier_state, so those would not issue an IPI.
	 * Membarrier requires a memory barrier after accessing
	 * user-space memory, beक्रमe clearing tsk->mm or the
	 * rq->membarrier_state.
	 */
	smp_mb__after_spinlock();
	local_irq_disable();
	current->mm = शून्य;
	membarrier_update_current_mm(शून्य);
	enter_lazy_tlb(mm, current);
	local_irq_enable();
	task_unlock(current);
	mmap_पढ़ो_unlock(mm);
	mm_update_next_owner(mm);
	mmput(mm);
	अगर (test_thपढ़ो_flag(TIF_MEMDIE))
		निकास_oom_victim();
पूर्ण

अटल काष्ठा task_काष्ठा *find_alive_thपढ़ो(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा task_काष्ठा *t;

	क्रम_each_thपढ़ो(p, t) अणु
		अगर (!(t->flags & PF_EXITING))
			वापस t;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा task_काष्ठा *find_child_reaper(काष्ठा task_काष्ठा *father,
						काष्ठा list_head *dead)
	__releases(&tasklist_lock)
	__acquires(&tasklist_lock)
अणु
	काष्ठा pid_namespace *pid_ns = task_active_pid_ns(father);
	काष्ठा task_काष्ठा *reaper = pid_ns->child_reaper;
	काष्ठा task_काष्ठा *p, *n;

	अगर (likely(reaper != father))
		वापस reaper;

	reaper = find_alive_thपढ़ो(father);
	अगर (reaper) अणु
		pid_ns->child_reaper = reaper;
		वापस reaper;
	पूर्ण

	ग_लिखो_unlock_irq(&tasklist_lock);

	list_क्रम_each_entry_safe(p, n, dead, ptrace_entry) अणु
		list_del_init(&p->ptrace_entry);
		release_task(p);
	पूर्ण

	zap_pid_ns_processes(pid_ns);
	ग_लिखो_lock_irq(&tasklist_lock);

	वापस father;
पूर्ण

/*
 * When we die, we re-parent all our children, and try to:
 * 1. give them to another thपढ़ो in our thपढ़ो group, अगर such a member exists
 * 2. give it to the first ancestor process which prctl'd itself as a
 *    child_subreaper क्रम its children (like a service manager)
 * 3. give it to the init process (PID 1) in our pid namespace
 */
अटल काष्ठा task_काष्ठा *find_new_reaper(काष्ठा task_काष्ठा *father,
					   काष्ठा task_काष्ठा *child_reaper)
अणु
	काष्ठा task_काष्ठा *thपढ़ो, *reaper;

	thपढ़ो = find_alive_thपढ़ो(father);
	अगर (thपढ़ो)
		वापस thपढ़ो;

	अगर (father->संकेत->has_child_subreaper) अणु
		अचिन्हित पूर्णांक ns_level = task_pid(father)->level;
		/*
		 * Find the first ->is_child_subreaper ancestor in our pid_ns.
		 * We can't check reaper != child_reaper to ensure we करो not
		 * cross the namespaces, the निकासing parent could be injected
		 * by setns() + विभाजन().
		 * We check pid->level, this is slightly more efficient than
		 * task_active_pid_ns(reaper) != task_active_pid_ns(father).
		 */
		क्रम (reaper = father->real_parent;
		     task_pid(reaper)->level == ns_level;
		     reaper = reaper->real_parent) अणु
			अगर (reaper == &init_task)
				अवरोध;
			अगर (!reaper->संकेत->is_child_subreaper)
				जारी;
			thपढ़ो = find_alive_thपढ़ो(reaper);
			अगर (thपढ़ो)
				वापस thपढ़ो;
		पूर्ण
	पूर्ण

	वापस child_reaper;
पूर्ण

/*
* Any that need to be release_task'd are put on the @dead list.
 */
अटल व्योम reparent_leader(काष्ठा task_काष्ठा *father, काष्ठा task_काष्ठा *p,
				काष्ठा list_head *dead)
अणु
	अगर (unlikely(p->निकास_state == EXIT_DEAD))
		वापस;

	/* We करोn't want people slaying init. */
	p->निकास_संकेत = SIGCHLD;

	/* If it has निकासed notअगरy the new parent about this child's death. */
	अगर (!p->ptrace &&
	    p->निकास_state == EXIT_ZOMBIE && thपढ़ो_group_empty(p)) अणु
		अगर (करो_notअगरy_parent(p, p->निकास_संकेत)) अणु
			p->निकास_state = EXIT_DEAD;
			list_add(&p->ptrace_entry, dead);
		पूर्ण
	पूर्ण

	समाप्त_orphaned_pgrp(p, father);
पूर्ण

/*
 * This करोes two things:
 *
 * A.  Make init inherit all the child processes
 * B.  Check to see अगर any process groups have become orphaned
 *	as a result of our निकासing, and अगर they have any stopped
 *	jobs, send them a SIGHUP and then a SIGCONT.  (POSIX 3.2.2.2)
 */
अटल व्योम क्रमget_original_parent(काष्ठा task_काष्ठा *father,
					काष्ठा list_head *dead)
अणु
	काष्ठा task_काष्ठा *p, *t, *reaper;

	अगर (unlikely(!list_empty(&father->ptraced)))
		निकास_ptrace(father, dead);

	/* Can drop and reacquire tasklist_lock */
	reaper = find_child_reaper(father, dead);
	अगर (list_empty(&father->children))
		वापस;

	reaper = find_new_reaper(father, reaper);
	list_क्रम_each_entry(p, &father->children, sibling) अणु
		क्रम_each_thपढ़ो(p, t) अणु
			RCU_INIT_POINTER(t->real_parent, reaper);
			BUG_ON((!t->ptrace) != (rcu_access_poपूर्णांकer(t->parent) == father));
			अगर (likely(!t->ptrace))
				t->parent = t->real_parent;
			अगर (t->pdeath_संकेत)
				group_send_sig_info(t->pdeath_संकेत,
						    SEND_SIG_NOINFO, t,
						    PIDTYPE_TGID);
		पूर्ण
		/*
		 * If this is a thपढ़ोed reparent there is no need to
		 * notअगरy anyone anything has happened.
		 */
		अगर (!same_thपढ़ो_group(reaper, father))
			reparent_leader(father, p, dead);
	पूर्ण
	list_splice_tail_init(&father->children, &reaper->children);
पूर्ण

/*
 * Send संकेतs to all our बंदst relatives so that they know
 * to properly mourn us..
 */
अटल व्योम निकास_notअगरy(काष्ठा task_काष्ठा *tsk, पूर्णांक group_dead)
अणु
	bool स्वतःreap;
	काष्ठा task_काष्ठा *p, *n;
	LIST_HEAD(dead);

	ग_लिखो_lock_irq(&tasklist_lock);
	क्रमget_original_parent(tsk, &dead);

	अगर (group_dead)
		समाप्त_orphaned_pgrp(tsk->group_leader, शून्य);

	tsk->निकास_state = EXIT_ZOMBIE;
	अगर (unlikely(tsk->ptrace)) अणु
		पूर्णांक sig = thपढ़ो_group_leader(tsk) &&
				thपढ़ो_group_empty(tsk) &&
				!ptrace_reparented(tsk) ?
			tsk->निकास_संकेत : SIGCHLD;
		स्वतःreap = करो_notअगरy_parent(tsk, sig);
	पूर्ण अन्यथा अगर (thपढ़ो_group_leader(tsk)) अणु
		स्वतःreap = thपढ़ो_group_empty(tsk) &&
			करो_notअगरy_parent(tsk, tsk->निकास_संकेत);
	पूर्ण अन्यथा अणु
		स्वतःreap = true;
	पूर्ण

	अगर (स्वतःreap) अणु
		tsk->निकास_state = EXIT_DEAD;
		list_add(&tsk->ptrace_entry, &dead);
	पूर्ण

	/* mt-exec, de_thपढ़ो() is रुकोing क्रम group leader */
	अगर (unlikely(tsk->संकेत->notअगरy_count < 0))
		wake_up_process(tsk->संकेत->group_निकास_task);
	ग_लिखो_unlock_irq(&tasklist_lock);

	list_क्रम_each_entry_safe(p, n, &dead, ptrace_entry) अणु
		list_del_init(&p->ptrace_entry);
		release_task(p);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DEBUG_STACK_USAGE
अटल व्योम check_stack_usage(व्योम)
अणु
	अटल DEFINE_SPINLOCK(low_water_lock);
	अटल पूर्णांक lowest_to_date = THREAD_SIZE;
	अचिन्हित दीर्घ मुक्त;

	मुक्त = stack_not_used(current);

	अगर (मुक्त >= lowest_to_date)
		वापस;

	spin_lock(&low_water_lock);
	अगर (मुक्त < lowest_to_date) अणु
		pr_info("%s (%d) used greatest stack depth: %lu bytes left\n",
			current->comm, task_pid_nr(current), मुक्त);
		lowest_to_date = मुक्त;
	पूर्ण
	spin_unlock(&low_water_lock);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम check_stack_usage(व्योम) अणुपूर्ण
#पूर्ण_अगर

व्योम __noवापस करो_निकास(दीर्घ code)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	पूर्णांक group_dead;

	/*
	 * We can get here from a kernel oops, someबार with preemption off.
	 * Start by checking क्रम critical errors.
	 * Then fix up important state like USER_DS and preemption.
	 * Then करो everything अन्यथा.
	 */

	WARN_ON(blk_needs_flush_plug(tsk));

	अगर (unlikely(in_पूर्णांकerrupt()))
		panic("Aiee, killing interrupt handler!");
	अगर (unlikely(!tsk->pid))
		panic("Attempted to kill the idle task!");

	/*
	 * If करो_निकास is called because this processes oopsed, it's possible
	 * that get_fs() was left as KERNEL_DS, so reset it to USER_DS beक्रमe
	 * continuing. Amongst other possible reasons, this is to prevent
	 * mm_release()->clear_child_tid() from writing to a user-controlled
	 * kernel address.
	 */
	क्रमce_uaccess_begin();

	अगर (unlikely(in_atomic())) अणु
		pr_info("note: %s[%d] exited with preempt_count %d\n",
			current->comm, task_pid_nr(current),
			preempt_count());
		preempt_count_set(PREEMPT_ENABLED);
	पूर्ण

	profile_task_निकास(tsk);
	kcov_task_निकास(tsk);

	ptrace_event(PTRACE_EVENT_EXIT, code);

	validate_creds_क्रम_करो_निकास(tsk);

	/*
	 * We're taking recursive faults here in करो_निकास. Safest is to just
	 * leave this task alone and रुको क्रम reboot.
	 */
	अगर (unlikely(tsk->flags & PF_EXITING)) अणु
		pr_alert("Fixing recursive fault but reboot is needed!\n");
		futex_निकास_recursive(tsk);
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule();
	पूर्ण

	io_uring_files_cancel(tsk->files);
	निकास_संकेतs(tsk);  /* sets PF_EXITING */

	/* sync mm's RSS info beक्रमe statistics gathering */
	अगर (tsk->mm)
		sync_mm_rss(tsk->mm);
	acct_update_पूर्णांकegrals(tsk);
	group_dead = atomic_dec_and_test(&tsk->संकेत->live);
	अगर (group_dead) अणु
		/*
		 * If the last thपढ़ो of global init has निकासed, panic
		 * immediately to get a useable coredump.
		 */
		अगर (unlikely(is_global_init(tsk)))
			panic("Attempted to kill init! exitcode=0x%08x\n",
				tsk->संकेत->group_निकास_code ?: (पूर्णांक)code);

#अगर_घोषित CONFIG_POSIX_TIMERS
		hrसमयr_cancel(&tsk->संकेत->real_समयr);
		निकास_iसमयrs(tsk->संकेत);
#पूर्ण_अगर
		अगर (tsk->mm)
			seपंचांगax_mm_hiwater_rss(&tsk->संकेत->maxrss, tsk->mm);
	पूर्ण
	acct_collect(code, group_dead);
	अगर (group_dead)
		tty_audit_निकास();
	audit_मुक्त(tsk);

	tsk->निकास_code = code;
	taskstats_निकास(tsk, group_dead);

	निकास_mm();

	अगर (group_dead)
		acct_process();
	trace_sched_process_निकास(tsk);

	निकास_sem(tsk);
	निकास_shm(tsk);
	निकास_files(tsk);
	निकास_fs(tsk);
	अगर (group_dead)
		disassociate_ctty(1);
	निकास_task_namespaces(tsk);
	निकास_task_work(tsk);
	निकास_thपढ़ो(tsk);

	/*
	 * Flush inherited counters to the parent - beक्रमe the parent
	 * माला_लो woken up by child-निकास notअगरications.
	 *
	 * because of cgroup mode, must be called beक्रमe cgroup_निकास()
	 */
	perf_event_निकास_task(tsk);

	sched_स्वतःgroup_निकास_task(tsk);
	cgroup_निकास(tsk);

	/*
	 * FIXME: करो that only when needed, using sched_निकास tracepoपूर्णांक
	 */
	flush_ptrace_hw_अवरोधpoपूर्णांक(tsk);

	निकास_tasks_rcu_start();
	निकास_notअगरy(tsk, group_dead);
	proc_निकास_connector(tsk);
	mpol_put_task_policy(tsk);
#अगर_घोषित CONFIG_FUTEX
	अगर (unlikely(current->pi_state_cache))
		kमुक्त(current->pi_state_cache);
#पूर्ण_अगर
	/*
	 * Make sure we are holding no locks:
	 */
	debug_check_no_locks_held();

	अगर (tsk->io_context)
		निकास_io_context(tsk);

	अगर (tsk->splice_pipe)
		मुक्त_pipe_info(tsk->splice_pipe);

	अगर (tsk->task_frag.page)
		put_page(tsk->task_frag.page);

	validate_creds_क्रम_करो_निकास(tsk);

	check_stack_usage();
	preempt_disable();
	अगर (tsk->nr_dirtied)
		__this_cpu_add(dirty_throttle_leaks, tsk->nr_dirtied);
	निकास_rcu();
	निकास_tasks_rcu_finish();

	lockdep_मुक्त_task(tsk);
	करो_task_dead();
पूर्ण
EXPORT_SYMBOL_GPL(करो_निकास);

व्योम complete_and_निकास(काष्ठा completion *comp, दीर्घ code)
अणु
	अगर (comp)
		complete(comp);

	करो_निकास(code);
पूर्ण
EXPORT_SYMBOL(complete_and_निकास);

SYSCALL_DEFINE1(निकास, पूर्णांक, error_code)
अणु
	करो_निकास((error_code&0xff)<<8);
पूर्ण

/*
 * Take करोwn every thपढ़ो in the group.  This is called by fatal संकेतs
 * as well as by sys_निकास_group (below).
 */
व्योम
करो_group_निकास(पूर्णांक निकास_code)
अणु
	काष्ठा संकेत_काष्ठा *sig = current->संकेत;

	BUG_ON(निकास_code & 0x80); /* core dumps करोn't get here */

	अगर (संकेत_group_निकास(sig))
		निकास_code = sig->group_निकास_code;
	अन्यथा अगर (!thपढ़ो_group_empty(current)) अणु
		काष्ठा sighand_काष्ठा *स्थिर sighand = current->sighand;

		spin_lock_irq(&sighand->siglock);
		अगर (संकेत_group_निकास(sig))
			/* Another thपढ़ो got here beक्रमe we took the lock.  */
			निकास_code = sig->group_निकास_code;
		अन्यथा अणु
			sig->group_निकास_code = निकास_code;
			sig->flags = SIGNAL_GROUP_EXIT;
			zap_other_thपढ़ोs(current);
		पूर्ण
		spin_unlock_irq(&sighand->siglock);
	पूर्ण

	करो_निकास(निकास_code);
	/* NOTREACHED */
पूर्ण

/*
 * this समाप्तs every thपढ़ो in the thपढ़ो group. Note that any बाह्यally
 * रुको4()-ing process will get the correct निकास code - even अगर this
 * thपढ़ो is not the thपढ़ो group leader.
 */
SYSCALL_DEFINE1(निकास_group, पूर्णांक, error_code)
अणु
	करो_group_निकास((error_code & 0xff) << 8);
	/* NOTREACHED */
	वापस 0;
पूर्ण

काष्ठा रुकोid_info अणु
	pid_t pid;
	uid_t uid;
	पूर्णांक status;
	पूर्णांक cause;
पूर्ण;

काष्ठा रुको_opts अणु
	क्रमागत pid_type		wo_type;
	पूर्णांक			wo_flags;
	काष्ठा pid		*wo_pid;

	काष्ठा रुकोid_info	*wo_info;
	पूर्णांक			wo_stat;
	काष्ठा rusage		*wo_rusage;

	रुको_queue_entry_t		child_रुको;
	पूर्णांक			notask_error;
पूर्ण;

अटल पूर्णांक eligible_pid(काष्ठा रुको_opts *wo, काष्ठा task_काष्ठा *p)
अणु
	वापस	wo->wo_type == PIDTYPE_MAX ||
		task_pid_type(p, wo->wo_type) == wo->wo_pid;
पूर्ण

अटल पूर्णांक
eligible_child(काष्ठा रुको_opts *wo, bool ptrace, काष्ठा task_काष्ठा *p)
अणु
	अगर (!eligible_pid(wo, p))
		वापस 0;

	/*
	 * Wait क्रम all children (clone and not) अगर __WALL is set or
	 * अगर it is traced by us.
	 */
	अगर (ptrace || (wo->wo_flags & __WALL))
		वापस 1;

	/*
	 * Otherwise, रुको क्रम clone children *only* अगर __WCLONE is set;
	 * otherwise, रुको क्रम non-clone children *only*.
	 *
	 * Note: a "clone" child here is one that reports to its parent
	 * using a संकेत other than SIGCHLD, or a non-leader thपढ़ो which
	 * we can only see अगर it is traced by us.
	 */
	अगर ((p->निकास_संकेत != SIGCHLD) ^ !!(wo->wo_flags & __WCLONE))
		वापस 0;

	वापस 1;
पूर्ण

/*
 * Handle sys_रुको4 work क्रम one task in state EXIT_ZOMBIE.  We hold
 * पढ़ो_lock(&tasklist_lock) on entry.  If we वापस zero, we still hold
 * the lock and this task is unपूर्णांकeresting.  If we वापस nonzero, we have
 * released the lock and the प्रणाली call should वापस.
 */
अटल पूर्णांक रुको_task_zombie(काष्ठा रुको_opts *wo, काष्ठा task_काष्ठा *p)
अणु
	पूर्णांक state, status;
	pid_t pid = task_pid_vnr(p);
	uid_t uid = from_kuid_munged(current_user_ns(), task_uid(p));
	काष्ठा रुकोid_info *infop;

	अगर (!likely(wo->wo_flags & WEXITED))
		वापस 0;

	अगर (unlikely(wo->wo_flags & WNOWAIT)) अणु
		status = p->निकास_code;
		get_task_काष्ठा(p);
		पढ़ो_unlock(&tasklist_lock);
		sched_annotate_sleep();
		अगर (wo->wo_rusage)
			getrusage(p, RUSAGE_BOTH, wo->wo_rusage);
		put_task_काष्ठा(p);
		जाओ out_info;
	पूर्ण
	/*
	 * Move the task's state to DEAD/TRACE, only one thपढ़ो can करो this.
	 */
	state = (ptrace_reparented(p) && thपढ़ो_group_leader(p)) ?
		EXIT_TRACE : EXIT_DEAD;
	अगर (cmpxchg(&p->निकास_state, EXIT_ZOMBIE, state) != EXIT_ZOMBIE)
		वापस 0;
	/*
	 * We own this thपढ़ो, nobody अन्यथा can reap it.
	 */
	पढ़ो_unlock(&tasklist_lock);
	sched_annotate_sleep();

	/*
	 * Check thपढ़ो_group_leader() to exclude the traced sub-thपढ़ोs.
	 */
	अगर (state == EXIT_DEAD && thपढ़ो_group_leader(p)) अणु
		काष्ठा संकेत_काष्ठा *sig = p->संकेत;
		काष्ठा संकेत_काष्ठा *psig = current->संकेत;
		अचिन्हित दीर्घ maxrss;
		u64 tguसमय, tgsसमय;

		/*
		 * The resource counters क्रम the group leader are in its
		 * own task_काष्ठा.  Those क्रम dead thपढ़ोs in the group
		 * are in its संकेत_काष्ठा, as are those क्रम the child
		 * processes it has previously reaped.  All these
		 * accumulate in the parent's संकेत_काष्ठा c* fields.
		 *
		 * We करोn't bother to take a lock here to protect these
		 * p->संकेत fields because the whole thपढ़ो group is dead
		 * and nobody can change them.
		 *
		 * psig->stats_lock also protects us from our sub-theads
		 * which can reap other children at the same समय. Until
		 * we change k_getrusage()-like users to rely on this lock
		 * we have to take ->siglock as well.
		 *
		 * We use thपढ़ो_group_cpuसमय_adjusted() to get बार क्रम
		 * the thपढ़ो group, which consolidates बार क्रम all thपढ़ोs
		 * in the group including the group leader.
		 */
		thपढ़ो_group_cpuसमय_adjusted(p, &tguसमय, &tgsसमय);
		spin_lock_irq(&current->sighand->siglock);
		ग_लिखो_seqlock(&psig->stats_lock);
		psig->cuसमय += tguसमय + sig->cuसमय;
		psig->csसमय += tgsसमय + sig->csसमय;
		psig->cgसमय += task_gसमय(p) + sig->gसमय + sig->cgसमय;
		psig->cmin_flt +=
			p->min_flt + sig->min_flt + sig->cmin_flt;
		psig->cmaj_flt +=
			p->maj_flt + sig->maj_flt + sig->cmaj_flt;
		psig->cnvcsw +=
			p->nvcsw + sig->nvcsw + sig->cnvcsw;
		psig->cnivcsw +=
			p->nivcsw + sig->nivcsw + sig->cnivcsw;
		psig->cinblock +=
			task_io_get_inblock(p) +
			sig->inblock + sig->cinblock;
		psig->coublock +=
			task_io_get_oublock(p) +
			sig->oublock + sig->coublock;
		maxrss = max(sig->maxrss, sig->cmaxrss);
		अगर (psig->cmaxrss < maxrss)
			psig->cmaxrss = maxrss;
		task_io_accounting_add(&psig->ioac, &p->ioac);
		task_io_accounting_add(&psig->ioac, &sig->ioac);
		ग_लिखो_sequnlock(&psig->stats_lock);
		spin_unlock_irq(&current->sighand->siglock);
	पूर्ण

	अगर (wo->wo_rusage)
		getrusage(p, RUSAGE_BOTH, wo->wo_rusage);
	status = (p->संकेत->flags & SIGNAL_GROUP_EXIT)
		? p->संकेत->group_निकास_code : p->निकास_code;
	wo->wo_stat = status;

	अगर (state == EXIT_TRACE) अणु
		ग_लिखो_lock_irq(&tasklist_lock);
		/* We dropped tasklist, ptracer could die and untrace */
		ptrace_unlink(p);

		/* If parent wants a zombie, करोn't release it now */
		state = EXIT_ZOMBIE;
		अगर (करो_notअगरy_parent(p, p->निकास_संकेत))
			state = EXIT_DEAD;
		p->निकास_state = state;
		ग_लिखो_unlock_irq(&tasklist_lock);
	पूर्ण
	अगर (state == EXIT_DEAD)
		release_task(p);

out_info:
	infop = wo->wo_info;
	अगर (infop) अणु
		अगर ((status & 0x7f) == 0) अणु
			infop->cause = CLD_EXITED;
			infop->status = status >> 8;
		पूर्ण अन्यथा अणु
			infop->cause = (status & 0x80) ? CLD_DUMPED : CLD_KILLED;
			infop->status = status & 0x7f;
		पूर्ण
		infop->pid = pid;
		infop->uid = uid;
	पूर्ण

	वापस pid;
पूर्ण

अटल पूर्णांक *task_stopped_code(काष्ठा task_काष्ठा *p, bool ptrace)
अणु
	अगर (ptrace) अणु
		अगर (task_is_traced(p) && !(p->jobctl & JOBCTL_LISTENING))
			वापस &p->निकास_code;
	पूर्ण अन्यथा अणु
		अगर (p->संकेत->flags & SIGNAL_STOP_STOPPED)
			वापस &p->संकेत->group_निकास_code;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * रुको_task_stopped - Wait क्रम %TASK_STOPPED or %TASK_TRACED
 * @wo: रुको options
 * @ptrace: is the रुको क्रम ptrace
 * @p: task to रुको क्रम
 *
 * Handle sys_रुको4() work क्रम %p in state %TASK_STOPPED or %TASK_TRACED.
 *
 * CONTEXT:
 * पढ़ो_lock(&tasklist_lock), which is released अगर वापस value is
 * non-zero.  Also, grअसल and releases @p->sighand->siglock.
 *
 * RETURNS:
 * 0 अगर रुको condition didn't exist and search क्रम other रुको conditions
 * should जारी.  Non-zero वापस, -त्रुटि_सं on failure and @p's pid on
 * success, implies that tasklist_lock is released and रुको condition
 * search should terminate.
 */
अटल पूर्णांक रुको_task_stopped(काष्ठा रुको_opts *wo,
				पूर्णांक ptrace, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा रुकोid_info *infop;
	पूर्णांक निकास_code, *p_code, why;
	uid_t uid = 0; /* unneeded, required by compiler */
	pid_t pid;

	/*
	 * Traditionally we see ptrace'd stopped tasks regardless of options.
	 */
	अगर (!ptrace && !(wo->wo_flags & WUNTRACED))
		वापस 0;

	अगर (!task_stopped_code(p, ptrace))
		वापस 0;

	निकास_code = 0;
	spin_lock_irq(&p->sighand->siglock);

	p_code = task_stopped_code(p, ptrace);
	अगर (unlikely(!p_code))
		जाओ unlock_sig;

	निकास_code = *p_code;
	अगर (!निकास_code)
		जाओ unlock_sig;

	अगर (!unlikely(wo->wo_flags & WNOWAIT))
		*p_code = 0;

	uid = from_kuid_munged(current_user_ns(), task_uid(p));
unlock_sig:
	spin_unlock_irq(&p->sighand->siglock);
	अगर (!निकास_code)
		वापस 0;

	/*
	 * Now we are pretty sure this task is पूर्णांकeresting.
	 * Make sure it करोesn't get reaped out from under us जबतक we
	 * give up the lock and then examine it below.  We करोn't want to
	 * keep holding onto the tasklist_lock जबतक we call getrusage and
	 * possibly take page faults क्रम user memory.
	 */
	get_task_काष्ठा(p);
	pid = task_pid_vnr(p);
	why = ptrace ? CLD_TRAPPED : CLD_STOPPED;
	पढ़ो_unlock(&tasklist_lock);
	sched_annotate_sleep();
	अगर (wo->wo_rusage)
		getrusage(p, RUSAGE_BOTH, wo->wo_rusage);
	put_task_काष्ठा(p);

	अगर (likely(!(wo->wo_flags & WNOWAIT)))
		wo->wo_stat = (निकास_code << 8) | 0x7f;

	infop = wo->wo_info;
	अगर (infop) अणु
		infop->cause = why;
		infop->status = निकास_code;
		infop->pid = pid;
		infop->uid = uid;
	पूर्ण
	वापस pid;
पूर्ण

/*
 * Handle करो_रुको work क्रम one task in a live, non-stopped state.
 * पढ़ो_lock(&tasklist_lock) on entry.  If we वापस zero, we still hold
 * the lock and this task is unपूर्णांकeresting.  If we वापस nonzero, we have
 * released the lock and the प्रणाली call should वापस.
 */
अटल पूर्णांक रुको_task_जारीd(काष्ठा रुको_opts *wo, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा रुकोid_info *infop;
	pid_t pid;
	uid_t uid;

	अगर (!unlikely(wo->wo_flags & WCONTINUED))
		वापस 0;

	अगर (!(p->संकेत->flags & SIGNAL_STOP_CONTINUED))
		वापस 0;

	spin_lock_irq(&p->sighand->siglock);
	/* Re-check with the lock held.  */
	अगर (!(p->संकेत->flags & SIGNAL_STOP_CONTINUED)) अणु
		spin_unlock_irq(&p->sighand->siglock);
		वापस 0;
	पूर्ण
	अगर (!unlikely(wo->wo_flags & WNOWAIT))
		p->संकेत->flags &= ~SIGNAL_STOP_CONTINUED;
	uid = from_kuid_munged(current_user_ns(), task_uid(p));
	spin_unlock_irq(&p->sighand->siglock);

	pid = task_pid_vnr(p);
	get_task_काष्ठा(p);
	पढ़ो_unlock(&tasklist_lock);
	sched_annotate_sleep();
	अगर (wo->wo_rusage)
		getrusage(p, RUSAGE_BOTH, wo->wo_rusage);
	put_task_काष्ठा(p);

	infop = wo->wo_info;
	अगर (!infop) अणु
		wo->wo_stat = 0xffff;
	पूर्ण अन्यथा अणु
		infop->cause = CLD_CONTINUED;
		infop->pid = pid;
		infop->uid = uid;
		infop->status = SIGCONT;
	पूर्ण
	वापस pid;
पूर्ण

/*
 * Consider @p क्रम a रुको by @parent.
 *
 * -ECHILD should be in ->notask_error beक्रमe the first call.
 * Returns nonzero क्रम a final वापस, when we have unlocked tasklist_lock.
 * Returns zero अगर the search क्रम a child should जारी;
 * then ->notask_error is 0 अगर @p is an eligible child,
 * or still -ECHILD.
 */
अटल पूर्णांक रुको_consider_task(काष्ठा रुको_opts *wo, पूर्णांक ptrace,
				काष्ठा task_काष्ठा *p)
अणु
	/*
	 * We can race with रुको_task_zombie() from another thपढ़ो.
	 * Ensure that EXIT_ZOMBIE -> EXIT_DEAD/EXIT_TRACE transition
	 * can't confuse the checks below.
	 */
	पूर्णांक निकास_state = READ_ONCE(p->निकास_state);
	पूर्णांक ret;

	अगर (unlikely(निकास_state == EXIT_DEAD))
		वापस 0;

	ret = eligible_child(wo, ptrace, p);
	अगर (!ret)
		वापस ret;

	अगर (unlikely(निकास_state == EXIT_TRACE)) अणु
		/*
		 * ptrace == 0 means we are the natural parent. In this हाल
		 * we should clear notask_error, debugger will notअगरy us.
		 */
		अगर (likely(!ptrace))
			wo->notask_error = 0;
		वापस 0;
	पूर्ण

	अगर (likely(!ptrace) && unlikely(p->ptrace)) अणु
		/*
		 * If it is traced by its real parent's group, just pretend
		 * the caller is ptrace_करो_रुको() and reap this child अगर it
		 * is zombie.
		 *
		 * This also hides group stop state from real parent; otherwise
		 * a single stop can be reported twice as group and ptrace stop.
		 * If a ptracer wants to distinguish these two events क्रम its
		 * own children it should create a separate process which takes
		 * the role of real parent.
		 */
		अगर (!ptrace_reparented(p))
			ptrace = 1;
	पूर्ण

	/* slay zombie? */
	अगर (निकास_state == EXIT_ZOMBIE) अणु
		/* we करोn't reap group leaders with subthपढ़ोs */
		अगर (!delay_group_leader(p)) अणु
			/*
			 * A zombie ptracee is only visible to its ptracer.
			 * Notअगरication and reaping will be cascaded to the
			 * real parent when the ptracer detaches.
			 */
			अगर (unlikely(ptrace) || likely(!p->ptrace))
				वापस रुको_task_zombie(wo, p);
		पूर्ण

		/*
		 * Allow access to stopped/जारीd state via zombie by
		 * falling through.  Clearing of notask_error is complex.
		 *
		 * When !@ptrace:
		 *
		 * If WEXITED is set, notask_error should naturally be
		 * cleared.  If not, subset of WSTOPPED|WCONTINUED is set,
		 * so, अगर there are live subthपढ़ोs, there are events to
		 * रुको क्रम.  If all subthपढ़ोs are dead, it's still safe
		 * to clear - this function will be called again in finite
		 * amount समय once all the subthपढ़ोs are released and
		 * will then वापस without clearing.
		 *
		 * When @ptrace:
		 *
		 * Stopped state is per-task and thus can't change once the
		 * target task dies.  Only जारीd and निकासed can happen.
		 * Clear notask_error अगर WCONTINUED | WEXITED.
		 */
		अगर (likely(!ptrace) || (wo->wo_flags & (WCONTINUED | WEXITED)))
			wo->notask_error = 0;
	पूर्ण अन्यथा अणु
		/*
		 * @p is alive and it's gonna stop, जारी or निकास, so
		 * there always is something to रुको क्रम.
		 */
		wo->notask_error = 0;
	पूर्ण

	/*
	 * Wait क्रम stopped.  Depending on @ptrace, dअगरferent stopped state
	 * is used and the two करोn't पूर्णांकeract with each other.
	 */
	ret = रुको_task_stopped(wo, ptrace, p);
	अगर (ret)
		वापस ret;

	/*
	 * Wait क्रम जारीd.  There's only one जारीd state and the
	 * ptracer can consume it which can confuse the real parent.  Don't
	 * use WCONTINUED from ptracer.  You करोn't need or want it.
	 */
	वापस रुको_task_जारीd(wo, p);
पूर्ण

/*
 * Do the work of करो_रुको() क्रम one thपढ़ो in the group, @tsk.
 *
 * -ECHILD should be in ->notask_error beक्रमe the first call.
 * Returns nonzero क्रम a final वापस, when we have unlocked tasklist_lock.
 * Returns zero अगर the search क्रम a child should जारी; then
 * ->notask_error is 0 अगर there were any eligible children,
 * or still -ECHILD.
 */
अटल पूर्णांक करो_रुको_thपढ़ो(काष्ठा रुको_opts *wo, काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा task_काष्ठा *p;

	list_क्रम_each_entry(p, &tsk->children, sibling) अणु
		पूर्णांक ret = रुको_consider_task(wo, 0, p);

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ptrace_करो_रुको(काष्ठा रुको_opts *wo, काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा task_काष्ठा *p;

	list_क्रम_each_entry(p, &tsk->ptraced, ptrace_entry) अणु
		पूर्णांक ret = रुको_consider_task(wo, 1, p);

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक child_रुको_callback(रुको_queue_entry_t *रुको, अचिन्हित mode,
				पूर्णांक sync, व्योम *key)
अणु
	काष्ठा रुको_opts *wo = container_of(रुको, काष्ठा रुको_opts,
						child_रुको);
	काष्ठा task_काष्ठा *p = key;

	अगर (!eligible_pid(wo, p))
		वापस 0;

	अगर ((wo->wo_flags & __WNOTHREAD) && रुको->निजी != p->parent)
		वापस 0;

	वापस शेष_wake_function(रुको, mode, sync, key);
पूर्ण

व्योम __wake_up_parent(काष्ठा task_काष्ठा *p, काष्ठा task_काष्ठा *parent)
अणु
	__wake_up_sync_key(&parent->संकेत->रुको_chldनिकास,
			   TASK_INTERRUPTIBLE, p);
पूर्ण

अटल bool is_effectively_child(काष्ठा रुको_opts *wo, bool ptrace,
				 काष्ठा task_काष्ठा *target)
अणु
	काष्ठा task_काष्ठा *parent =
		!ptrace ? target->real_parent : target->parent;

	वापस current == parent || (!(wo->wo_flags & __WNOTHREAD) &&
				     same_thपढ़ो_group(current, parent));
पूर्ण

/*
 * Optimization क्रम रुकोing on PIDTYPE_PID. No need to iterate through child
 * and tracee lists to find the target task.
 */
अटल पूर्णांक करो_रुको_pid(काष्ठा रुको_opts *wo)
अणु
	bool ptrace;
	काष्ठा task_काष्ठा *target;
	पूर्णांक retval;

	ptrace = false;
	target = pid_task(wo->wo_pid, PIDTYPE_TGID);
	अगर (target && is_effectively_child(wo, ptrace, target)) अणु
		retval = रुको_consider_task(wo, ptrace, target);
		अगर (retval)
			वापस retval;
	पूर्ण

	ptrace = true;
	target = pid_task(wo->wo_pid, PIDTYPE_PID);
	अगर (target && target->ptrace &&
	    is_effectively_child(wo, ptrace, target)) अणु
		retval = रुको_consider_task(wo, ptrace, target);
		अगर (retval)
			वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ करो_रुको(काष्ठा रुको_opts *wo)
अणु
	पूर्णांक retval;

	trace_sched_process_रुको(wo->wo_pid);

	init_रुकोqueue_func_entry(&wo->child_रुको, child_रुको_callback);
	wo->child_रुको.निजी = current;
	add_रुको_queue(&current->संकेत->रुको_chldनिकास, &wo->child_रुको);
repeat:
	/*
	 * If there is nothing that can match our criteria, just get out.
	 * We will clear ->notask_error to zero अगर we see any child that
	 * might later match our criteria, even अगर we are not able to reap
	 * it yet.
	 */
	wo->notask_error = -ECHILD;
	अगर ((wo->wo_type < PIDTYPE_MAX) &&
	   (!wo->wo_pid || !pid_has_task(wo->wo_pid, wo->wo_type)))
		जाओ notask;

	set_current_state(TASK_INTERRUPTIBLE);
	पढ़ो_lock(&tasklist_lock);

	अगर (wo->wo_type == PIDTYPE_PID) अणु
		retval = करो_रुको_pid(wo);
		अगर (retval)
			जाओ end;
	पूर्ण अन्यथा अणु
		काष्ठा task_काष्ठा *tsk = current;

		करो अणु
			retval = करो_रुको_thपढ़ो(wo, tsk);
			अगर (retval)
				जाओ end;

			retval = ptrace_करो_रुको(wo, tsk);
			अगर (retval)
				जाओ end;

			अगर (wo->wo_flags & __WNOTHREAD)
				अवरोध;
		पूर्ण जबतक_each_thपढ़ो(current, tsk);
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);

notask:
	retval = wo->notask_error;
	अगर (!retval && !(wo->wo_flags & WNOHANG)) अणु
		retval = -ERESTARTSYS;
		अगर (!संकेत_pending(current)) अणु
			schedule();
			जाओ repeat;
		पूर्ण
	पूर्ण
end:
	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&current->संकेत->रुको_chldनिकास, &wo->child_रुको);
	वापस retval;
पूर्ण

अटल दीर्घ kernel_रुकोid(पूर्णांक which, pid_t upid, काष्ठा रुकोid_info *infop,
			  पूर्णांक options, काष्ठा rusage *ru)
अणु
	काष्ठा रुको_opts wo;
	काष्ठा pid *pid = शून्य;
	क्रमागत pid_type type;
	दीर्घ ret;
	अचिन्हित पूर्णांक f_flags = 0;

	अगर (options & ~(WNOHANG|WNOWAIT|WEXITED|WSTOPPED|WCONTINUED|
			__WNOTHREAD|__WCLONE|__WALL))
		वापस -EINVAL;
	अगर (!(options & (WEXITED|WSTOPPED|WCONTINUED)))
		वापस -EINVAL;

	चयन (which) अणु
	हाल P_ALL:
		type = PIDTYPE_MAX;
		अवरोध;
	हाल P_PID:
		type = PIDTYPE_PID;
		अगर (upid <= 0)
			वापस -EINVAL;

		pid = find_get_pid(upid);
		अवरोध;
	हाल P_PGID:
		type = PIDTYPE_PGID;
		अगर (upid < 0)
			वापस -EINVAL;

		अगर (upid)
			pid = find_get_pid(upid);
		अन्यथा
			pid = get_task_pid(current, PIDTYPE_PGID);
		अवरोध;
	हाल P_PIDFD:
		type = PIDTYPE_PID;
		अगर (upid < 0)
			वापस -EINVAL;

		pid = pidfd_get_pid(upid, &f_flags);
		अगर (IS_ERR(pid))
			वापस PTR_ERR(pid);

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	wo.wo_type	= type;
	wo.wo_pid	= pid;
	wo.wo_flags	= options;
	wo.wo_info	= infop;
	wo.wo_rusage	= ru;
	अगर (f_flags & O_NONBLOCK)
		wo.wo_flags |= WNOHANG;

	ret = करो_रुको(&wo);
	अगर (!ret && !(options & WNOHANG) && (f_flags & O_NONBLOCK))
		ret = -EAGAIN;

	put_pid(pid);
	वापस ret;
पूर्ण

SYSCALL_DEFINE5(रुकोid, पूर्णांक, which, pid_t, upid, काष्ठा siginfo __user *,
		infop, पूर्णांक, options, काष्ठा rusage __user *, ru)
अणु
	काष्ठा rusage r;
	काष्ठा रुकोid_info info = अणु.status = 0पूर्ण;
	दीर्घ err = kernel_रुकोid(which, upid, &info, options, ru ? &r : शून्य);
	पूर्णांक signo = 0;

	अगर (err > 0) अणु
		signo = SIGCHLD;
		err = 0;
		अगर (ru && copy_to_user(ru, &r, माप(काष्ठा rusage)))
			वापस -EFAULT;
	पूर्ण
	अगर (!infop)
		वापस err;

	अगर (!user_ग_लिखो_access_begin(infop, माप(*infop)))
		वापस -EFAULT;

	unsafe_put_user(signo, &infop->si_signo, Efault);
	unsafe_put_user(0, &infop->si_त्रुटि_सं, Efault);
	unsafe_put_user(info.cause, &infop->si_code, Efault);
	unsafe_put_user(info.pid, &infop->si_pid, Efault);
	unsafe_put_user(info.uid, &infop->si_uid, Efault);
	unsafe_put_user(info.status, &infop->si_status, Efault);
	user_ग_लिखो_access_end();
	वापस err;
Efault:
	user_ग_लिखो_access_end();
	वापस -EFAULT;
पूर्ण

दीर्घ kernel_रुको4(pid_t upid, पूर्णांक __user *stat_addr, पूर्णांक options,
		  काष्ठा rusage *ru)
अणु
	काष्ठा रुको_opts wo;
	काष्ठा pid *pid = शून्य;
	क्रमागत pid_type type;
	दीर्घ ret;

	अगर (options & ~(WNOHANG|WUNTRACED|WCONTINUED|
			__WNOTHREAD|__WCLONE|__WALL))
		वापस -EINVAL;

	/* -पूर्णांक_न्यून is not defined */
	अगर (upid == पूर्णांक_न्यून)
		वापस -ESRCH;

	अगर (upid == -1)
		type = PIDTYPE_MAX;
	अन्यथा अगर (upid < 0) अणु
		type = PIDTYPE_PGID;
		pid = find_get_pid(-upid);
	पूर्ण अन्यथा अगर (upid == 0) अणु
		type = PIDTYPE_PGID;
		pid = get_task_pid(current, PIDTYPE_PGID);
	पूर्ण अन्यथा /* upid > 0 */ अणु
		type = PIDTYPE_PID;
		pid = find_get_pid(upid);
	पूर्ण

	wo.wo_type	= type;
	wo.wo_pid	= pid;
	wo.wo_flags	= options | WEXITED;
	wo.wo_info	= शून्य;
	wo.wo_stat	= 0;
	wo.wo_rusage	= ru;
	ret = करो_रुको(&wo);
	put_pid(pid);
	अगर (ret > 0 && stat_addr && put_user(wo.wo_stat, stat_addr))
		ret = -EFAULT;

	वापस ret;
पूर्ण

पूर्णांक kernel_रुको(pid_t pid, पूर्णांक *stat)
अणु
	काष्ठा रुको_opts wo = अणु
		.wo_type	= PIDTYPE_PID,
		.wo_pid		= find_get_pid(pid),
		.wo_flags	= WEXITED,
	पूर्ण;
	पूर्णांक ret;

	ret = करो_रुको(&wo);
	अगर (ret > 0 && wo.wo_stat)
		*stat = wo.wo_stat;
	put_pid(wo.wo_pid);
	वापस ret;
पूर्ण

SYSCALL_DEFINE4(रुको4, pid_t, upid, पूर्णांक __user *, stat_addr,
		पूर्णांक, options, काष्ठा rusage __user *, ru)
अणु
	काष्ठा rusage r;
	दीर्घ err = kernel_रुको4(upid, stat_addr, options, ru ? &r : शून्य);

	अगर (err > 0) अणु
		अगर (ru && copy_to_user(ru, &r, माप(काष्ठा rusage)))
			वापस -EFAULT;
	पूर्ण
	वापस err;
पूर्ण

#अगर_घोषित __ARCH_WANT_SYS_WAITPID

/*
 * sys_रुकोpid() reमुख्यs क्रम compatibility. रुकोpid() should be
 * implemented by calling sys_रुको4() from libc.a.
 */
SYSCALL_DEFINE3(रुकोpid, pid_t, pid, पूर्णांक __user *, stat_addr, पूर्णांक, options)
अणु
	वापस kernel_रुको4(pid, stat_addr, options, शून्य);
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE4(रुको4,
	compat_pid_t, pid,
	compat_uपूर्णांक_t __user *, stat_addr,
	पूर्णांक, options,
	काष्ठा compat_rusage __user *, ru)
अणु
	काष्ठा rusage r;
	दीर्घ err = kernel_रुको4(pid, stat_addr, options, ru ? &r : शून्य);
	अगर (err > 0) अणु
		अगर (ru && put_compat_rusage(&r, ru))
			वापस -EFAULT;
	पूर्ण
	वापस err;
पूर्ण

COMPAT_SYSCALL_DEFINE5(रुकोid,
		पूर्णांक, which, compat_pid_t, pid,
		काष्ठा compat_siginfo __user *, infop, पूर्णांक, options,
		काष्ठा compat_rusage __user *, uru)
अणु
	काष्ठा rusage ru;
	काष्ठा रुकोid_info info = अणु.status = 0पूर्ण;
	दीर्घ err = kernel_रुकोid(which, pid, &info, options, uru ? &ru : शून्य);
	पूर्णांक signo = 0;
	अगर (err > 0) अणु
		signo = SIGCHLD;
		err = 0;
		अगर (uru) अणु
			/* kernel_रुकोid() overग_लिखोs everything in ru */
			अगर (COMPAT_USE_64BIT_TIME)
				err = copy_to_user(uru, &ru, माप(ru));
			अन्यथा
				err = put_compat_rusage(&ru, uru);
			अगर (err)
				वापस -EFAULT;
		पूर्ण
	पूर्ण

	अगर (!infop)
		वापस err;

	अगर (!user_ग_लिखो_access_begin(infop, माप(*infop)))
		वापस -EFAULT;

	unsafe_put_user(signo, &infop->si_signo, Efault);
	unsafe_put_user(0, &infop->si_त्रुटि_सं, Efault);
	unsafe_put_user(info.cause, &infop->si_code, Efault);
	unsafe_put_user(info.pid, &infop->si_pid, Efault);
	unsafe_put_user(info.uid, &infop->si_uid, Efault);
	unsafe_put_user(info.status, &infop->si_status, Efault);
	user_ग_लिखो_access_end();
	वापस err;
Efault:
	user_ग_लिखो_access_end();
	वापस -EFAULT;
पूर्ण
#पूर्ण_अगर

/**
 * thपढ़ो_group_निकासed - check that a thपढ़ो group has निकासed
 * @pid: tgid of thपढ़ो group to be checked.
 *
 * Test अगर the thपढ़ो group represented by tgid has निकासed (all
 * thपढ़ोs are zombies, dead or completely gone).
 *
 * Return: true अगर the thपढ़ो group has निकासed. false otherwise.
 */
bool thपढ़ो_group_निकासed(काष्ठा pid *pid)
अणु
	काष्ठा task_काष्ठा *task;
	bool निकासed;

	rcu_पढ़ो_lock();
	task = pid_task(pid, PIDTYPE_PID);
	निकासed = !task ||
		(READ_ONCE(task->निकास_state) && thपढ़ो_group_empty(task));
	rcu_पढ़ो_unlock();

	वापस निकासed;
पूर्ण
EXPORT_SYMBOL(thपढ़ो_group_निकासed);

__weak व्योम पात(व्योम)
अणु
	BUG();

	/* अगर that करोesn't समाप्त us, halt */
	panic("Oops failed to kill thread");
पूर्ण
EXPORT_SYMBOL(पात);
