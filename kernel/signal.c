<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/kernel/संकेत.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  1997-11-02  Modअगरied क्रम POSIX.1b संकेतs by Riअक्षरd Henderson
 *
 *  2003-06-02  Jim Houston - Concurrent Computer Corp.
 *		Changes to use pपुनः_स्मृतिated sigqueue काष्ठाures
 *		to allow संकेतs to be sent reliably.
 */

#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/user.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/tty.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/coredump.h>
#समावेश <linux/security.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/संकेतfd.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/capability.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/uprobes.h>
#समावेश <linux/compat.h>
#समावेश <linux/cn_proc.h>
#समावेश <linux/compiler.h>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/audit.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/संकेत.स>

#समावेश <यंत्र/param.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/siginfo.h>
#समावेश <यंत्र/cacheflush.h>

/*
 * SLAB caches क्रम संकेत bits.
 */

अटल काष्ठा kmem_cache *sigqueue_cachep;

पूर्णांक prपूर्णांक_fatal_संकेतs __पढ़ो_mostly;

अटल व्योम __user *sig_handler(काष्ठा task_काष्ठा *t, पूर्णांक sig)
अणु
	वापस t->sighand->action[sig - 1].sa.sa_handler;
पूर्ण

अटल अंतरभूत bool sig_handler_ignored(व्योम __user *handler, पूर्णांक sig)
अणु
	/* Is it explicitly or implicitly ignored? */
	वापस handler == संक_छोड़ो ||
	       (handler == संक_पूर्व && sig_kernel_ignore(sig));
पूर्ण

अटल bool sig_task_ignored(काष्ठा task_काष्ठा *t, पूर्णांक sig, bool क्रमce)
अणु
	व्योम __user *handler;

	handler = sig_handler(t, sig);

	/* SIGKILL and SIGSTOP may not be sent to the global init */
	अगर (unlikely(is_global_init(t) && sig_kernel_only(sig)))
		वापस true;

	अगर (unlikely(t->संकेत->flags & SIGNAL_UNKILLABLE) &&
	    handler == संक_पूर्व && !(क्रमce && sig_kernel_only(sig)))
		वापस true;

	/* Only allow kernel generated संकेतs to this kthपढ़ो */
	अगर (unlikely((t->flags & PF_KTHREAD) &&
		     (handler == SIG_KTHREAD_KERNEL) && !क्रमce))
		वापस true;

	वापस sig_handler_ignored(handler, sig);
पूर्ण

अटल bool sig_ignored(काष्ठा task_काष्ठा *t, पूर्णांक sig, bool क्रमce)
अणु
	/*
	 * Blocked संकेतs are never ignored, since the
	 * संकेत handler may change by the समय it is
	 * unblocked.
	 */
	अगर (sigismember(&t->blocked, sig) || sigismember(&t->real_blocked, sig))
		वापस false;

	/*
	 * Tracers may want to know about even ignored संकेत unless it
	 * is SIGKILL which can't be reported anyway but can be ignored
	 * by SIGNAL_UNKILLABLE task.
	 */
	अगर (t->ptrace && sig != SIGKILL)
		वापस false;

	वापस sig_task_ignored(t, sig, क्रमce);
पूर्ण

/*
 * Re-calculate pending state from the set of locally pending
 * संकेतs, globally pending संकेतs, and blocked संकेतs.
 */
अटल अंतरभूत bool has_pending_संकेतs(sigset_t *संकेत, sigset_t *blocked)
अणु
	अचिन्हित दीर्घ पढ़ोy;
	दीर्घ i;

	चयन (_NSIG_WORDS) अणु
	शेष:
		क्रम (i = _NSIG_WORDS, पढ़ोy = 0; --i >= 0 ;)
			पढ़ोy |= संकेत->sig[i] &~ blocked->sig[i];
		अवरोध;

	हाल 4: पढ़ोy  = संकेत->sig[3] &~ blocked->sig[3];
		पढ़ोy |= संकेत->sig[2] &~ blocked->sig[2];
		पढ़ोy |= संकेत->sig[1] &~ blocked->sig[1];
		पढ़ोy |= संकेत->sig[0] &~ blocked->sig[0];
		अवरोध;

	हाल 2: पढ़ोy  = संकेत->sig[1] &~ blocked->sig[1];
		पढ़ोy |= संकेत->sig[0] &~ blocked->sig[0];
		अवरोध;

	हाल 1: पढ़ोy  = संकेत->sig[0] &~ blocked->sig[0];
	पूर्ण
	वापस पढ़ोy !=	0;
पूर्ण

#घोषणा PENDING(p,b) has_pending_संकेतs(&(p)->संकेत, (b))

अटल bool recalc_संक_बाकी_tsk(काष्ठा task_काष्ठा *t)
अणु
	अगर ((t->jobctl & (JOBCTL_PENDING_MASK | JOBCTL_TRAP_FREEZE)) ||
	    PENDING(&t->pending, &t->blocked) ||
	    PENDING(&t->संकेत->shared_pending, &t->blocked) ||
	    cgroup_task_frozen(t)) अणु
		set_tsk_thपढ़ो_flag(t, TIF_SIGPENDING);
		वापस true;
	पूर्ण

	/*
	 * We must never clear the flag in another thपढ़ो, or in current
	 * when it's possible the current syscall is वापसing -ERESTART*.
	 * So we करोn't clear it here, and only callers who know they should करो.
	 */
	वापस false;
पूर्ण

/*
 * After recalculating TIF_SIGPENDING, we need to make sure the task wakes up.
 * This is superfluous when called on current, the wakeup is a harmless no-op.
 */
व्योम recalc_संक_बाकी_and_wake(काष्ठा task_काष्ठा *t)
अणु
	अगर (recalc_संक_बाकी_tsk(t))
		संकेत_wake_up(t, 0);
पूर्ण

व्योम recalc_संक_बाकी(व्योम)
अणु
	अगर (!recalc_संक_बाकी_tsk(current) && !मुक्तzing(current))
		clear_thपढ़ो_flag(TIF_SIGPENDING);

पूर्ण
EXPORT_SYMBOL(recalc_संक_बाकी);

व्योम calculate_संक_बाकी(व्योम)
अणु
	/* Have any संकेतs or users of TIF_SIGPENDING been delayed
	 * until after विभाजन?
	 */
	spin_lock_irq(&current->sighand->siglock);
	set_tsk_thपढ़ो_flag(current, TIF_SIGPENDING);
	recalc_संक_बाकी();
	spin_unlock_irq(&current->sighand->siglock);
पूर्ण

/* Given the mask, find the first available संकेत that should be serviced. */

#घोषणा SYNCHRONOUS_MASK \
	(sigmask(संक_अंश) | sigmask(SIGBUS) | sigmask(संक_अवैध) | \
	 sigmask(SIGTRAP) | sigmask(संक_भ_त्रुटि) | sigmask(SIGSYS))

पूर्णांक next_संकेत(काष्ठा संक_बाकी *pending, sigset_t *mask)
अणु
	अचिन्हित दीर्घ i, *s, *m, x;
	पूर्णांक sig = 0;

	s = pending->संकेत.sig;
	m = mask->sig;

	/*
	 * Handle the first word specially: it contains the
	 * synchronous संकेतs that need to be dequeued first.
	 */
	x = *s &~ *m;
	अगर (x) अणु
		अगर (x & SYNCHRONOUS_MASK)
			x &= SYNCHRONOUS_MASK;
		sig = ffz(~x) + 1;
		वापस sig;
	पूर्ण

	चयन (_NSIG_WORDS) अणु
	शेष:
		क्रम (i = 1; i < _NSIG_WORDS; ++i) अणु
			x = *++s &~ *++m;
			अगर (!x)
				जारी;
			sig = ffz(~x) + i*_NSIG_BPW + 1;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 2:
		x = s[1] &~ m[1];
		अगर (!x)
			अवरोध;
		sig = ffz(~x) + _NSIG_BPW + 1;
		अवरोध;

	हाल 1:
		/* Nothing to करो */
		अवरोध;
	पूर्ण

	वापस sig;
पूर्ण

अटल अंतरभूत व्योम prपूर्णांक_dropped_संकेत(पूर्णांक sig)
अणु
	अटल DEFINE_RATELIMIT_STATE(ratelimit_state, 5 * HZ, 10);

	अगर (!prपूर्णांक_fatal_संकेतs)
		वापस;

	अगर (!__ratelimit(&ratelimit_state))
		वापस;

	pr_info("%s/%d: reached RLIMIT_SIGPENDING, dropped signal %d\n",
				current->comm, current->pid, sig);
पूर्ण

/**
 * task_set_jobctl_pending - set jobctl pending bits
 * @task: target task
 * @mask: pending bits to set
 *
 * Clear @mask from @task->jobctl.  @mask must be subset of
 * %JOBCTL_PENDING_MASK | %JOBCTL_STOP_CONSUME | %JOBCTL_STOP_SIGMASK |
 * %JOBCTL_TRAPPING.  If stop signo is being set, the existing signo is
 * cleared.  If @task is alपढ़ोy being समाप्तed or निकासing, this function
 * becomes noop.
 *
 * CONTEXT:
 * Must be called with @task->sighand->siglock held.
 *
 * RETURNS:
 * %true अगर @mask is set, %false अगर made noop because @task was dying.
 */
bool task_set_jobctl_pending(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ mask)
अणु
	BUG_ON(mask & ~(JOBCTL_PENDING_MASK | JOBCTL_STOP_CONSUME |
			JOBCTL_STOP_SIGMASK | JOBCTL_TRAPPING));
	BUG_ON((mask & JOBCTL_TRAPPING) && !(mask & JOBCTL_PENDING_MASK));

	अगर (unlikely(fatal_संकेत_pending(task) || (task->flags & PF_EXITING)))
		वापस false;

	अगर (mask & JOBCTL_STOP_SIGMASK)
		task->jobctl &= ~JOBCTL_STOP_SIGMASK;

	task->jobctl |= mask;
	वापस true;
पूर्ण

/**
 * task_clear_jobctl_trapping - clear jobctl trapping bit
 * @task: target task
 *
 * If JOBCTL_TRAPPING is set, a ptracer is रुकोing क्रम us to enter TRACED.
 * Clear it and wake up the ptracer.  Note that we करोn't need any further
 * locking.  @task->siglock guarantees that @task->parent poपूर्णांकs to the
 * ptracer.
 *
 * CONTEXT:
 * Must be called with @task->sighand->siglock held.
 */
व्योम task_clear_jobctl_trapping(काष्ठा task_काष्ठा *task)
अणु
	अगर (unlikely(task->jobctl & JOBCTL_TRAPPING)) अणु
		task->jobctl &= ~JOBCTL_TRAPPING;
		smp_mb();	/* advised by wake_up_bit() */
		wake_up_bit(&task->jobctl, JOBCTL_TRAPPING_BIT);
	पूर्ण
पूर्ण

/**
 * task_clear_jobctl_pending - clear jobctl pending bits
 * @task: target task
 * @mask: pending bits to clear
 *
 * Clear @mask from @task->jobctl.  @mask must be subset of
 * %JOBCTL_PENDING_MASK.  If %JOBCTL_STOP_PENDING is being cleared, other
 * STOP bits are cleared together.
 *
 * If clearing of @mask leaves no stop or trap pending, this function calls
 * task_clear_jobctl_trapping().
 *
 * CONTEXT:
 * Must be called with @task->sighand->siglock held.
 */
व्योम task_clear_jobctl_pending(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ mask)
अणु
	BUG_ON(mask & ~JOBCTL_PENDING_MASK);

	अगर (mask & JOBCTL_STOP_PENDING)
		mask |= JOBCTL_STOP_CONSUME | JOBCTL_STOP_DEQUEUED;

	task->jobctl &= ~mask;

	अगर (!(task->jobctl & JOBCTL_PENDING_MASK))
		task_clear_jobctl_trapping(task);
पूर्ण

/**
 * task_participate_group_stop - participate in a group stop
 * @task: task participating in a group stop
 *
 * @task has %JOBCTL_STOP_PENDING set and is participating in a group stop.
 * Group stop states are cleared and the group stop count is consumed अगर
 * %JOBCTL_STOP_CONSUME was set.  If the consumption completes the group
 * stop, the appropriate `SIGNAL_*` flags are set.
 *
 * CONTEXT:
 * Must be called with @task->sighand->siglock held.
 *
 * RETURNS:
 * %true अगर group stop completion should be notअगरied to the parent, %false
 * otherwise.
 */
अटल bool task_participate_group_stop(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा संकेत_काष्ठा *sig = task->संकेत;
	bool consume = task->jobctl & JOBCTL_STOP_CONSUME;

	WARN_ON_ONCE(!(task->jobctl & JOBCTL_STOP_PENDING));

	task_clear_jobctl_pending(task, JOBCTL_STOP_PENDING);

	अगर (!consume)
		वापस false;

	अगर (!WARN_ON_ONCE(sig->group_stop_count == 0))
		sig->group_stop_count--;

	/*
	 * Tell the caller to notअगरy completion अगरf we are entering पूर्णांकo a
	 * fresh group stop.  Read comment in करो_संकेत_stop() क्रम details.
	 */
	अगर (!sig->group_stop_count && !(sig->flags & SIGNAL_STOP_STOPPED)) अणु
		संकेत_set_stop_flags(sig, SIGNAL_STOP_STOPPED);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

व्योम task_join_group_stop(काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ mask = current->jobctl & JOBCTL_STOP_SIGMASK;
	काष्ठा संकेत_काष्ठा *sig = current->संकेत;

	अगर (sig->group_stop_count) अणु
		sig->group_stop_count++;
		mask |= JOBCTL_STOP_CONSUME;
	पूर्ण अन्यथा अगर (!(sig->flags & SIGNAL_STOP_STOPPED))
		वापस;

	/* Have the new thपढ़ो join an on-going संकेत group stop */
	task_set_jobctl_pending(task, mask | JOBCTL_STOP_PENDING);
पूर्ण

/*
 * allocate a new संकेत queue record
 * - this may be called without locks अगर and only अगर t == current, otherwise an
 *   appropriate lock must be held to stop the target task from निकासing
 */
अटल काष्ठा sigqueue *
__sigqueue_alloc(पूर्णांक sig, काष्ठा task_काष्ठा *t, gfp_t gfp_flags,
		 पूर्णांक override_rlimit, स्थिर अचिन्हित पूर्णांक sigqueue_flags)
अणु
	काष्ठा sigqueue *q = शून्य;
	काष्ठा user_काष्ठा *user;
	पूर्णांक संक_बाकी;

	/*
	 * Protect access to @t credentials. This can go away when all
	 * callers hold rcu पढ़ो lock.
	 *
	 * NOTE! A pending संकेत will hold on to the user refcount,
	 * and we get/put the refcount only when the संक_बाकी count
	 * changes from/to zero.
	 */
	rcu_पढ़ो_lock();
	user = __task_cred(t)->user;
	संक_बाकी = atomic_inc_वापस(&user->संक_बाकी);
	अगर (संक_बाकी == 1)
		get_uid(user);
	rcu_पढ़ो_unlock();

	अगर (override_rlimit || likely(संक_बाकी <= task_rlimit(t, RLIMIT_SIGPENDING))) अणु
		/*
		 * Pपुनः_स्मृतिation करोes not hold sighand::siglock so it can't
		 * use the cache. The lockless caching requires that only
		 * one consumer and only one producer run at a समय.
		 */
		q = READ_ONCE(t->sigqueue_cache);
		अगर (!q || sigqueue_flags)
			q = kmem_cache_alloc(sigqueue_cachep, gfp_flags);
		अन्यथा
			WRITE_ONCE(t->sigqueue_cache, शून्य);
	पूर्ण अन्यथा अणु
		prपूर्णांक_dropped_संकेत(sig);
	पूर्ण

	अगर (unlikely(q == शून्य)) अणु
		अगर (atomic_dec_and_test(&user->संक_बाकी))
			मुक्त_uid(user);
	पूर्ण अन्यथा अणु
		INIT_LIST_HEAD(&q->list);
		q->flags = sigqueue_flags;
		q->user = user;
	पूर्ण

	वापस q;
पूर्ण

व्योम निकास_task_sigqueue_cache(काष्ठा task_काष्ठा *tsk)
अणु
	/* Race मुक्त because @tsk is mopped up */
	काष्ठा sigqueue *q = tsk->sigqueue_cache;

	अगर (q) अणु
		tsk->sigqueue_cache = शून्य;
		/*
		 * Hand it back to the cache as the task might
		 * be self reaping which would leak the object.
		 */
		 kmem_cache_मुक्त(sigqueue_cachep, q);
	पूर्ण
पूर्ण

अटल व्योम sigqueue_cache_or_मुक्त(काष्ठा sigqueue *q)
अणु
	/*
	 * Cache one sigqueue per task. This pairs with the consumer side
	 * in __sigqueue_alloc() and needs READ/WRITE_ONCE() to prevent the
	 * compiler from store tearing and to tell KCSAN that the data race
	 * is पूर्णांकentional when run without holding current->sighand->siglock,
	 * which is fine as current obviously cannot run __sigqueue_मुक्त()
	 * concurrently.
	 */
	अगर (!READ_ONCE(current->sigqueue_cache))
		WRITE_ONCE(current->sigqueue_cache, q);
	अन्यथा
		kmem_cache_मुक्त(sigqueue_cachep, q);
पूर्ण

अटल व्योम __sigqueue_मुक्त(काष्ठा sigqueue *q)
अणु
	अगर (q->flags & SIGQUEUE_PREALLOC)
		वापस;
	अगर (atomic_dec_and_test(&q->user->संक_बाकी))
		मुक्त_uid(q->user);
	sigqueue_cache_or_मुक्त(q);
पूर्ण

व्योम flush_sigqueue(काष्ठा संक_बाकी *queue)
अणु
	काष्ठा sigqueue *q;

	sigemptyset(&queue->संकेत);
	जबतक (!list_empty(&queue->list)) अणु
		q = list_entry(queue->list.next, काष्ठा sigqueue , list);
		list_del_init(&q->list);
		__sigqueue_मुक्त(q);
	पूर्ण
पूर्ण

/*
 * Flush all pending संकेतs क्रम this kthपढ़ो.
 */
व्योम flush_संकेतs(काष्ठा task_काष्ठा *t)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&t->sighand->siglock, flags);
	clear_tsk_thपढ़ो_flag(t, TIF_SIGPENDING);
	flush_sigqueue(&t->pending);
	flush_sigqueue(&t->संकेत->shared_pending);
	spin_unlock_irqrestore(&t->sighand->siglock, flags);
पूर्ण
EXPORT_SYMBOL(flush_संकेतs);

#अगर_घोषित CONFIG_POSIX_TIMERS
अटल व्योम __flush_iसमयr_संकेतs(काष्ठा संक_बाकी *pending)
अणु
	sigset_t संकेत, retain;
	काष्ठा sigqueue *q, *n;

	संकेत = pending->संकेत;
	sigemptyset(&retain);

	list_क्रम_each_entry_safe(q, n, &pending->list, list) अणु
		पूर्णांक sig = q->info.si_signo;

		अगर (likely(q->info.si_code != SI_TIMER)) अणु
			sigaddset(&retain, sig);
		पूर्ण अन्यथा अणु
			sigdअन्यथाt(&संकेत, sig);
			list_del_init(&q->list);
			__sigqueue_मुक्त(q);
		पूर्ण
	पूर्ण

	sigorsets(&pending->संकेत, &संकेत, &retain);
पूर्ण

व्योम flush_iसमयr_संकेतs(व्योम)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tsk->sighand->siglock, flags);
	__flush_iसमयr_संकेतs(&tsk->pending);
	__flush_iसमयr_संकेतs(&tsk->संकेत->shared_pending);
	spin_unlock_irqrestore(&tsk->sighand->siglock, flags);
पूर्ण
#पूर्ण_अगर

व्योम ignore_संकेतs(काष्ठा task_काष्ठा *t)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < _NSIG; ++i)
		t->sighand->action[i].sa.sa_handler = संक_छोड़ो;

	flush_संकेतs(t);
पूर्ण

/*
 * Flush all handlers क्रम a task.
 */

व्योम
flush_संकेत_handlers(काष्ठा task_काष्ठा *t, पूर्णांक क्रमce_शेष)
अणु
	पूर्णांक i;
	काष्ठा k_sigaction *ka = &t->sighand->action[0];
	क्रम (i = _NSIG ; i != 0 ; i--) अणु
		अगर (क्रमce_शेष || ka->sa.sa_handler != संक_छोड़ो)
			ka->sa.sa_handler = संक_पूर्व;
		ka->sa.sa_flags = 0;
#अगर_घोषित __ARCH_HAS_SA_RESTORER
		ka->sa.sa_restorer = शून्य;
#पूर्ण_अगर
		sigemptyset(&ka->sa.sa_mask);
		ka++;
	पूर्ण
पूर्ण

bool unhandled_संकेत(काष्ठा task_काष्ठा *tsk, पूर्णांक sig)
अणु
	व्योम __user *handler = tsk->sighand->action[sig-1].sa.sa_handler;
	अगर (is_global_init(tsk))
		वापस true;

	अगर (handler != संक_छोड़ो && handler != संक_पूर्व)
		वापस false;

	/* अगर ptraced, let the tracer determine */
	वापस !tsk->ptrace;
पूर्ण

अटल व्योम collect_संकेत(पूर्णांक sig, काष्ठा संक_बाकी *list, kernel_siginfo_t *info,
			   bool *resched_समयr)
अणु
	काष्ठा sigqueue *q, *first = शून्य;

	/*
	 * Collect the siginfo appropriate to this संकेत.  Check अगर
	 * there is another siginfo क्रम the same संकेत.
	*/
	list_क्रम_each_entry(q, &list->list, list) अणु
		अगर (q->info.si_signo == sig) अणु
			अगर (first)
				जाओ still_pending;
			first = q;
		पूर्ण
	पूर्ण

	sigdअन्यथाt(&list->संकेत, sig);

	अगर (first) अणु
still_pending:
		list_del_init(&first->list);
		copy_siginfo(info, &first->info);

		*resched_समयr =
			(first->flags & SIGQUEUE_PREALLOC) &&
			(info->si_code == SI_TIMER) &&
			(info->si_sys_निजी);

		__sigqueue_मुक्त(first);
	पूर्ण अन्यथा अणु
		/*
		 * Ok, it wasn't in the queue.  This must be
		 * a fast-pathed संकेत or we must have been
		 * out of queue space.  So zero out the info.
		 */
		clear_siginfo(info);
		info->si_signo = sig;
		info->si_त्रुटि_सं = 0;
		info->si_code = SI_USER;
		info->si_pid = 0;
		info->si_uid = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक __dequeue_संकेत(काष्ठा संक_बाकी *pending, sigset_t *mask,
			kernel_siginfo_t *info, bool *resched_समयr)
अणु
	पूर्णांक sig = next_संकेत(pending, mask);

	अगर (sig)
		collect_संकेत(sig, pending, info, resched_समयr);
	वापस sig;
पूर्ण

/*
 * Dequeue a संकेत and वापस the element to the caller, which is
 * expected to मुक्त it.
 *
 * All callers have to hold the siglock.
 */
पूर्णांक dequeue_संकेत(काष्ठा task_काष्ठा *tsk, sigset_t *mask, kernel_siginfo_t *info)
अणु
	bool resched_समयr = false;
	पूर्णांक signr;

	/* We only dequeue निजी संकेतs from ourselves, we करोn't let
	 * संकेतfd steal them
	 */
	signr = __dequeue_संकेत(&tsk->pending, mask, info, &resched_समयr);
	अगर (!signr) अणु
		signr = __dequeue_संकेत(&tsk->संकेत->shared_pending,
					 mask, info, &resched_समयr);
#अगर_घोषित CONFIG_POSIX_TIMERS
		/*
		 * iसमयr संकेत ?
		 *
		 * iसमयrs are process shared and we restart periodic
		 * iसमयrs in the संकेत delivery path to prevent DoS
		 * attacks in the high resolution समयr हाल. This is
		 * compliant with the old way of self-restarting
		 * iसमयrs, as the SIGALRM is a legacy संकेत and only
		 * queued once. Changing the restart behaviour to
		 * restart the समयr in the संकेत dequeue path is
		 * reducing the समयr noise on heavy loaded !highres
		 * प्रणालीs too.
		 */
		अगर (unlikely(signr == SIGALRM)) अणु
			काष्ठा hrसमयr *पंचांगr = &tsk->संकेत->real_समयr;

			अगर (!hrसमयr_is_queued(पंचांगr) &&
			    tsk->संकेत->it_real_incr != 0) अणु
				hrसमयr_क्रमward(पंचांगr, पंचांगr->base->get_समय(),
						tsk->संकेत->it_real_incr);
				hrसमयr_restart(पंचांगr);
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	recalc_संक_बाकी();
	अगर (!signr)
		वापस 0;

	अगर (unlikely(sig_kernel_stop(signr))) अणु
		/*
		 * Set a marker that we have dequeued a stop संकेत.  Our
		 * caller might release the siglock and then the pending
		 * stop संकेत it is about to process is no दीर्घer in the
		 * pending biपंचांगasks, but must still be cleared by a SIGCONT
		 * (and overruled by a SIGKILL).  So those हालs clear this
		 * shared flag after we've set it.  Note that this flag may
		 * reमुख्य set after the संकेत we वापस is ignored or
		 * handled.  That करोesn't matter because its only purpose
		 * is to alert stop-संकेत processing code when another
		 * processor has come aदीर्घ and cleared the flag.
		 */
		current->jobctl |= JOBCTL_STOP_DEQUEUED;
	पूर्ण
#अगर_घोषित CONFIG_POSIX_TIMERS
	अगर (resched_समयr) अणु
		/*
		 * Release the siglock to ensure proper locking order
		 * of समयr locks outside of siglocks.  Note, we leave
		 * irqs disabled here, since the posix-समयrs code is
		 * about to disable them again anyway.
		 */
		spin_unlock(&tsk->sighand->siglock);
		posixसमयr_rearm(info);
		spin_lock(&tsk->sighand->siglock);

		/* Don't expose the si_sys_निजी value to userspace */
		info->si_sys_निजी = 0;
	पूर्ण
#पूर्ण_अगर
	वापस signr;
पूर्ण
EXPORT_SYMBOL_GPL(dequeue_संकेत);

अटल पूर्णांक dequeue_synchronous_संकेत(kernel_siginfo_t *info)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा संक_बाकी *pending = &tsk->pending;
	काष्ठा sigqueue *q, *sync = शून्य;

	/*
	 * Might a synchronous संकेत be in the queue?
	 */
	अगर (!((pending->संकेत.sig[0] & ~tsk->blocked.sig[0]) & SYNCHRONOUS_MASK))
		वापस 0;

	/*
	 * Return the first synchronous संकेत in the queue.
	 */
	list_क्रम_each_entry(q, &pending->list, list) अणु
		/* Synchronous संकेतs have a positive si_code */
		अगर ((q->info.si_code > SI_USER) &&
		    (sigmask(q->info.si_signo) & SYNCHRONOUS_MASK)) अणु
			sync = q;
			जाओ next;
		पूर्ण
	पूर्ण
	वापस 0;
next:
	/*
	 * Check अगर there is another siginfo क्रम the same संकेत.
	 */
	list_क्रम_each_entry_जारी(q, &pending->list, list) अणु
		अगर (q->info.si_signo == sync->info.si_signo)
			जाओ still_pending;
	पूर्ण

	sigdअन्यथाt(&pending->संकेत, sync->info.si_signo);
	recalc_संक_बाकी();
still_pending:
	list_del_init(&sync->list);
	copy_siginfo(info, &sync->info);
	__sigqueue_मुक्त(sync);
	वापस info->si_signo;
पूर्ण

/*
 * Tell a process that it has a new active संकेत..
 *
 * NOTE! we rely on the previous spin_lock to
 * lock पूर्णांकerrupts क्रम us! We can only be called with
 * "siglock" held, and the local पूर्णांकerrupt must
 * have been disabled when that got acquired!
 *
 * No need to set need_resched since संकेत event passing
 * goes through ->blocked
 */
व्योम संकेत_wake_up_state(काष्ठा task_काष्ठा *t, अचिन्हित पूर्णांक state)
अणु
	set_tsk_thपढ़ो_flag(t, TIF_SIGPENDING);
	/*
	 * TASK_WAKEKILL also means wake it up in the stopped/traced/समाप्तable
	 * हाल. We करोn't check t->state here because there is a race with it
	 * executing another processor and just now entering stopped state.
	 * By using wake_up_state, we ensure the process will wake up and
	 * handle its death संकेत.
	 */
	अगर (!wake_up_state(t, state | TASK_INTERRUPTIBLE))
		kick_process(t);
पूर्ण

/*
 * Remove संकेतs in mask from the pending set and queue.
 * Returns 1 अगर any संकेतs were found.
 *
 * All callers must be holding the siglock.
 */
अटल व्योम flush_sigqueue_mask(sigset_t *mask, काष्ठा संक_बाकी *s)
अणु
	काष्ठा sigqueue *q, *n;
	sigset_t m;

	sigandsets(&m, mask, &s->संकेत);
	अगर (sigisemptyset(&m))
		वापस;

	sigandnsets(&s->संकेत, &s->संकेत, mask);
	list_क्रम_each_entry_safe(q, n, &s->list, list) अणु
		अगर (sigismember(mask, q->info.si_signo)) अणु
			list_del_init(&q->list);
			__sigqueue_मुक्त(q);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक is_si_special(स्थिर काष्ठा kernel_siginfo *info)
अणु
	वापस info <= SEND_SIG_PRIV;
पूर्ण

अटल अंतरभूत bool si_fromuser(स्थिर काष्ठा kernel_siginfo *info)
अणु
	वापस info == SEND_SIG_NOINFO ||
		(!is_si_special(info) && SI_FROMUSER(info));
पूर्ण

/*
 * called with RCU पढ़ो lock from check_समाप्त_permission()
 */
अटल bool समाप्त_ok_by_cred(काष्ठा task_काष्ठा *t)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	स्थिर काष्ठा cred *tcred = __task_cred(t);

	वापस uid_eq(cred->euid, tcred->suid) ||
	       uid_eq(cred->euid, tcred->uid) ||
	       uid_eq(cred->uid, tcred->suid) ||
	       uid_eq(cred->uid, tcred->uid) ||
	       ns_capable(tcred->user_ns, CAP_KILL);
पूर्ण

/*
 * Bad permissions क्रम sending the संकेत
 * - the caller must hold the RCU पढ़ो lock
 */
अटल पूर्णांक check_समाप्त_permission(पूर्णांक sig, काष्ठा kernel_siginfo *info,
				 काष्ठा task_काष्ठा *t)
अणु
	काष्ठा pid *sid;
	पूर्णांक error;

	अगर (!valid_संकेत(sig))
		वापस -EINVAL;

	अगर (!si_fromuser(info))
		वापस 0;

	error = audit_संकेत_info(sig, t); /* Let audit प्रणाली see the संकेत */
	अगर (error)
		वापस error;

	अगर (!same_thपढ़ो_group(current, t) &&
	    !समाप्त_ok_by_cred(t)) अणु
		चयन (sig) अणु
		हाल SIGCONT:
			sid = task_session(t);
			/*
			 * We करोn't वापस the error अगर sid == शून्य. The
			 * task was unhashed, the caller must notice this.
			 */
			अगर (!sid || sid == task_session(current))
				अवरोध;
			fallthrough;
		शेष:
			वापस -EPERM;
		पूर्ण
	पूर्ण

	वापस security_task_समाप्त(t, info, sig, शून्य);
पूर्ण

/**
 * ptrace_trap_notअगरy - schedule trap to notअगरy ptracer
 * @t: tracee wanting to notअगरy tracer
 *
 * This function schedules sticky ptrace trap which is cleared on the next
 * TRAP_STOP to notअगरy ptracer of an event.  @t must have been seized by
 * ptracer.
 *
 * If @t is running, STOP trap will be taken.  If trapped क्रम STOP and
 * ptracer is listening क्रम events, tracee is woken up so that it can
 * re-trap क्रम the new event.  If trapped otherwise, STOP trap will be
 * eventually taken without वापसing to userland after the existing traps
 * are finished by PTRACE_CONT.
 *
 * CONTEXT:
 * Must be called with @task->sighand->siglock held.
 */
अटल व्योम ptrace_trap_notअगरy(काष्ठा task_काष्ठा *t)
अणु
	WARN_ON_ONCE(!(t->ptrace & PT_SEIZED));
	निश्चित_spin_locked(&t->sighand->siglock);

	task_set_jobctl_pending(t, JOBCTL_TRAP_NOTIFY);
	ptrace_संकेत_wake_up(t, t->jobctl & JOBCTL_LISTENING);
पूर्ण

/*
 * Handle magic process-wide effects of stop/जारी संकेतs. Unlike
 * the संकेत actions, these happen immediately at संकेत-generation
 * समय regardless of blocking, ignoring, or handling.  This करोes the
 * actual continuing क्रम SIGCONT, but not the actual stopping क्रम stop
 * संकेतs. The process stop is करोne as a संकेत action क्रम संक_पूर्व.
 *
 * Returns true अगर the संकेत should be actually delivered, otherwise
 * it should be dropped.
 */
अटल bool prepare_संकेत(पूर्णांक sig, काष्ठा task_काष्ठा *p, bool क्रमce)
अणु
	काष्ठा संकेत_काष्ठा *संकेत = p->संकेत;
	काष्ठा task_काष्ठा *t;
	sigset_t flush;

	अगर (संकेत->flags & (SIGNAL_GROUP_EXIT | SIGNAL_GROUP_COREDUMP)) अणु
		अगर (!(संकेत->flags & SIGNAL_GROUP_EXIT))
			वापस sig == SIGKILL;
		/*
		 * The process is in the middle of dying, nothing to करो.
		 */
	पूर्ण अन्यथा अगर (sig_kernel_stop(sig)) अणु
		/*
		 * This is a stop संकेत.  Remove SIGCONT from all queues.
		 */
		siginitset(&flush, sigmask(SIGCONT));
		flush_sigqueue_mask(&flush, &संकेत->shared_pending);
		क्रम_each_thपढ़ो(p, t)
			flush_sigqueue_mask(&flush, &t->pending);
	पूर्ण अन्यथा अगर (sig == SIGCONT) अणु
		अचिन्हित पूर्णांक why;
		/*
		 * Remove all stop संकेतs from all queues, wake all thपढ़ोs.
		 */
		siginitset(&flush, SIG_KERNEL_STOP_MASK);
		flush_sigqueue_mask(&flush, &संकेत->shared_pending);
		क्रम_each_thपढ़ो(p, t) अणु
			flush_sigqueue_mask(&flush, &t->pending);
			task_clear_jobctl_pending(t, JOBCTL_STOP_PENDING);
			अगर (likely(!(t->ptrace & PT_SEIZED)))
				wake_up_state(t, __TASK_STOPPED);
			अन्यथा
				ptrace_trap_notअगरy(t);
		पूर्ण

		/*
		 * Notअगरy the parent with CLD_CONTINUED अगर we were stopped.
		 *
		 * If we were in the middle of a group stop, we pretend it
		 * was alपढ़ोy finished, and then जारीd. Since SIGCHLD
		 * करोesn't queue we report only CLD_STOPPED, as अगर the next
		 * CLD_CONTINUED was dropped.
		 */
		why = 0;
		अगर (संकेत->flags & SIGNAL_STOP_STOPPED)
			why |= SIGNAL_CLD_CONTINUED;
		अन्यथा अगर (संकेत->group_stop_count)
			why |= SIGNAL_CLD_STOPPED;

		अगर (why) अणु
			/*
			 * The first thपढ़ो which वापसs from करो_संकेत_stop()
			 * will take ->siglock, notice SIGNAL_CLD_MASK, and
			 * notअगरy its parent. See get_संकेत().
			 */
			संकेत_set_stop_flags(संकेत, why | SIGNAL_STOP_CONTINUED);
			संकेत->group_stop_count = 0;
			संकेत->group_निकास_code = 0;
		पूर्ण
	पूर्ण

	वापस !sig_ignored(p, sig, क्रमce);
पूर्ण

/*
 * Test अगर P wants to take SIG.  After we've checked all thपढ़ोs with this,
 * it's equivalent to finding no thपढ़ोs not blocking SIG.  Any thपढ़ोs not
 * blocking SIG were ruled out because they are not running and alपढ़ोy
 * have pending संकेतs.  Such thपढ़ोs will dequeue from the shared queue
 * as soon as they're available, so putting the संकेत on the shared queue
 * will be equivalent to sending it to one such thपढ़ो.
 */
अटल अंतरभूत bool wants_संकेत(पूर्णांक sig, काष्ठा task_काष्ठा *p)
अणु
	अगर (sigismember(&p->blocked, sig))
		वापस false;

	अगर (p->flags & PF_EXITING)
		वापस false;

	अगर (sig == SIGKILL)
		वापस true;

	अगर (task_is_stopped_or_traced(p))
		वापस false;

	वापस task_curr(p) || !task_संक_बाकी(p);
पूर्ण

अटल व्योम complete_संकेत(पूर्णांक sig, काष्ठा task_काष्ठा *p, क्रमागत pid_type type)
अणु
	काष्ठा संकेत_काष्ठा *संकेत = p->संकेत;
	काष्ठा task_काष्ठा *t;

	/*
	 * Now find a thपढ़ो we can wake up to take the संकेत off the queue.
	 *
	 * If the मुख्य thपढ़ो wants the संकेत, it माला_लो first crack.
	 * Probably the least surprising to the average bear.
	 */
	अगर (wants_संकेत(sig, p))
		t = p;
	अन्यथा अगर ((type == PIDTYPE_PID) || thपढ़ो_group_empty(p))
		/*
		 * There is just one thपढ़ो and it करोes not need to be woken.
		 * It will dequeue unblocked संकेतs beक्रमe it runs again.
		 */
		वापस;
	अन्यथा अणु
		/*
		 * Otherwise try to find a suitable thपढ़ो.
		 */
		t = संकेत->curr_target;
		जबतक (!wants_संकेत(sig, t)) अणु
			t = next_thपढ़ो(t);
			अगर (t == संकेत->curr_target)
				/*
				 * No thपढ़ो needs to be woken.
				 * Any eligible thपढ़ोs will see
				 * the संकेत in the queue soon.
				 */
				वापस;
		पूर्ण
		संकेत->curr_target = t;
	पूर्ण

	/*
	 * Found a समाप्तable thपढ़ो.  If the संकेत will be fatal,
	 * then start taking the whole group करोwn immediately.
	 */
	अगर (sig_fatal(p, sig) &&
	    !(संकेत->flags & SIGNAL_GROUP_EXIT) &&
	    !sigismember(&t->real_blocked, sig) &&
	    (sig == SIGKILL || !p->ptrace)) अणु
		/*
		 * This संकेत will be fatal to the whole group.
		 */
		अगर (!sig_kernel_coredump(sig)) अणु
			/*
			 * Start a group निकास and wake everybody up.
			 * This way we करोn't have other thपढ़ोs
			 * running and करोing things after a slower
			 * thपढ़ो has the fatal संकेत pending.
			 */
			संकेत->flags = SIGNAL_GROUP_EXIT;
			संकेत->group_निकास_code = sig;
			संकेत->group_stop_count = 0;
			t = p;
			करो अणु
				task_clear_jobctl_pending(t, JOBCTL_PENDING_MASK);
				sigaddset(&t->pending.संकेत, SIGKILL);
				संकेत_wake_up(t, 1);
			पूर्ण जबतक_each_thपढ़ो(p, t);
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * The संकेत is alपढ़ोy in the shared-pending queue.
	 * Tell the chosen thपढ़ो to wake up and dequeue it.
	 */
	संकेत_wake_up(t, sig == SIGKILL);
	वापस;
पूर्ण

अटल अंतरभूत bool legacy_queue(काष्ठा संक_बाकी *संकेतs, पूर्णांक sig)
अणु
	वापस (sig < SIGRTMIN) && sigismember(&संकेतs->संकेत, sig);
पूर्ण

अटल पूर्णांक __send_संकेत(पूर्णांक sig, काष्ठा kernel_siginfo *info, काष्ठा task_काष्ठा *t,
			क्रमागत pid_type type, bool क्रमce)
अणु
	काष्ठा संक_बाकी *pending;
	काष्ठा sigqueue *q;
	पूर्णांक override_rlimit;
	पूर्णांक ret = 0, result;

	निश्चित_spin_locked(&t->sighand->siglock);

	result = TRACE_SIGNAL_IGNORED;
	अगर (!prepare_संकेत(sig, t, क्रमce))
		जाओ ret;

	pending = (type != PIDTYPE_PID) ? &t->संकेत->shared_pending : &t->pending;
	/*
	 * Short-circuit ignored संकेतs and support queuing
	 * exactly one non-rt संकेत, so that we can get more
	 * detailed inक्रमmation about the cause of the संकेत.
	 */
	result = TRACE_SIGNAL_ALREADY_PENDING;
	अगर (legacy_queue(pending, sig))
		जाओ ret;

	result = TRACE_SIGNAL_DELIVERED;
	/*
	 * Skip useless siginfo allocation क्रम SIGKILL and kernel thपढ़ोs.
	 */
	अगर ((sig == SIGKILL) || (t->flags & PF_KTHREAD))
		जाओ out_set;

	/*
	 * Real-समय संकेतs must be queued अगर sent by sigqueue, or
	 * some other real-समय mechanism.  It is implementation
	 * defined whether समाप्त() करोes so.  We attempt to करो so, on
	 * the principle of least surprise, but since समाप्त is not
	 * allowed to fail with EAGAIN when low on memory we just
	 * make sure at least one संकेत माला_लो delivered and करोn't
	 * pass on the info काष्ठा.
	 */
	अगर (sig < SIGRTMIN)
		override_rlimit = (is_si_special(info) || info->si_code >= 0);
	अन्यथा
		override_rlimit = 0;

	q = __sigqueue_alloc(sig, t, GFP_ATOMIC, override_rlimit, 0);

	अगर (q) अणु
		list_add_tail(&q->list, &pending->list);
		चयन ((अचिन्हित दीर्घ) info) अणु
		हाल (अचिन्हित दीर्घ) SEND_SIG_NOINFO:
			clear_siginfo(&q->info);
			q->info.si_signo = sig;
			q->info.si_त्रुटि_सं = 0;
			q->info.si_code = SI_USER;
			q->info.si_pid = task_tgid_nr_ns(current,
							task_active_pid_ns(t));
			rcu_पढ़ो_lock();
			q->info.si_uid =
				from_kuid_munged(task_cred_xxx(t, user_ns),
						 current_uid());
			rcu_पढ़ो_unlock();
			अवरोध;
		हाल (अचिन्हित दीर्घ) SEND_SIG_PRIV:
			clear_siginfo(&q->info);
			q->info.si_signo = sig;
			q->info.si_त्रुटि_सं = 0;
			q->info.si_code = SI_KERNEL;
			q->info.si_pid = 0;
			q->info.si_uid = 0;
			अवरोध;
		शेष:
			copy_siginfo(&q->info, info);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (!is_si_special(info) &&
		   sig >= SIGRTMIN && info->si_code != SI_USER) अणु
		/*
		 * Queue overflow, पात.  We may पात अगर the
		 * संकेत was rt and sent by user using something
		 * other than समाप्त().
		 */
		result = TRACE_SIGNAL_OVERFLOW_FAIL;
		ret = -EAGAIN;
		जाओ ret;
	पूर्ण अन्यथा अणु
		/*
		 * This is a silent loss of inक्रमmation.  We still
		 * send the संकेत, but the *info bits are lost.
		 */
		result = TRACE_SIGNAL_LOSE_INFO;
	पूर्ण

out_set:
	संकेतfd_notअगरy(t, sig);
	sigaddset(&pending->संकेत, sig);

	/* Let multiprocess संकेतs appear after on-going विभाजनs */
	अगर (type > PIDTYPE_TGID) अणु
		काष्ठा multiprocess_संकेतs *delayed;
		hlist_क्रम_each_entry(delayed, &t->संकेत->multiprocess, node) अणु
			sigset_t *संकेत = &delayed->संकेत;
			/* Can't queue both a stop and a जारी संकेत */
			अगर (sig == SIGCONT)
				sigdअन्यथापंचांगask(संकेत, SIG_KERNEL_STOP_MASK);
			अन्यथा अगर (sig_kernel_stop(sig))
				sigdअन्यथाt(संकेत, SIGCONT);
			sigaddset(संकेत, sig);
		पूर्ण
	पूर्ण

	complete_संकेत(sig, t, type);
ret:
	trace_संकेत_generate(sig, info, t, type != PIDTYPE_PID, result);
	वापस ret;
पूर्ण

अटल अंतरभूत bool has_si_pid_and_uid(काष्ठा kernel_siginfo *info)
अणु
	bool ret = false;
	चयन (siginfo_layout(info->si_signo, info->si_code)) अणु
	हाल SIL_KILL:
	हाल SIL_CHLD:
	हाल SIL_RT:
		ret = true;
		अवरोध;
	हाल SIL_TIMER:
	हाल SIL_POLL:
	हाल SIL_FAULT:
	हाल SIL_FAULT_TRAPNO:
	हाल SIL_FAULT_MCEERR:
	हाल SIL_FAULT_BNDERR:
	हाल SIL_FAULT_PKUERR:
	हाल SIL_PERF_EVENT:
	हाल SIL_SYS:
		ret = false;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक send_संकेत(पूर्णांक sig, काष्ठा kernel_siginfo *info, काष्ठा task_काष्ठा *t,
			क्रमागत pid_type type)
अणु
	/* Should SIGKILL or SIGSTOP be received by a pid namespace init? */
	bool क्रमce = false;

	अगर (info == SEND_SIG_NOINFO) अणु
		/* Force अगर sent from an ancestor pid namespace */
		क्रमce = !task_pid_nr_ns(current, task_active_pid_ns(t));
	पूर्ण अन्यथा अगर (info == SEND_SIG_PRIV) अणु
		/* Don't ignore kernel generated संकेतs */
		क्रमce = true;
	पूर्ण अन्यथा अगर (has_si_pid_and_uid(info)) अणु
		/* SIGKILL and SIGSTOP is special or has ids */
		काष्ठा user_namespace *t_user_ns;

		rcu_पढ़ो_lock();
		t_user_ns = task_cred_xxx(t, user_ns);
		अगर (current_user_ns() != t_user_ns) अणु
			kuid_t uid = make_kuid(current_user_ns(), info->si_uid);
			info->si_uid = from_kuid_munged(t_user_ns, uid);
		पूर्ण
		rcu_पढ़ो_unlock();

		/* A kernel generated संकेत? */
		क्रमce = (info->si_code == SI_KERNEL);

		/* From an ancestor pid namespace? */
		अगर (!task_pid_nr_ns(current, task_active_pid_ns(t))) अणु
			info->si_pid = 0;
			क्रमce = true;
		पूर्ण
	पूर्ण
	वापस __send_संकेत(sig, info, t, type, क्रमce);
पूर्ण

अटल व्योम prपूर्णांक_fatal_संकेत(पूर्णांक signr)
अणु
	काष्ठा pt_regs *regs = संकेत_pt_regs();
	pr_info("potentially unexpected fatal signal %d.\n", signr);

#अगर defined(__i386__) && !defined(__arch_um__)
	pr_info("code at %08lx: ", regs->ip);
	अणु
		पूर्णांक i;
		क्रम (i = 0; i < 16; i++) अणु
			अचिन्हित अक्षर insn;

			अगर (get_user(insn, (अचिन्हित अक्षर *)(regs->ip + i)))
				अवरोध;
			pr_cont("%02x ", insn);
		पूर्ण
	पूर्ण
	pr_cont("\n");
#पूर्ण_अगर
	preempt_disable();
	show_regs(regs);
	preempt_enable();
पूर्ण

अटल पूर्णांक __init setup_prपूर्णांक_fatal_संकेतs(अक्षर *str)
अणु
	get_option (&str, &prपूर्णांक_fatal_संकेतs);

	वापस 1;
पूर्ण

__setup("print-fatal-signals=", setup_prपूर्णांक_fatal_संकेतs);

पूर्णांक
__group_send_sig_info(पूर्णांक sig, काष्ठा kernel_siginfo *info, काष्ठा task_काष्ठा *p)
अणु
	वापस send_संकेत(sig, info, p, PIDTYPE_TGID);
पूर्ण

पूर्णांक करो_send_sig_info(पूर्णांक sig, काष्ठा kernel_siginfo *info, काष्ठा task_काष्ठा *p,
			क्रमागत pid_type type)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -ESRCH;

	अगर (lock_task_sighand(p, &flags)) अणु
		ret = send_संकेत(sig, info, p, type);
		unlock_task_sighand(p, &flags);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Force a संकेत that the process can't ignore: अगर necessary
 * we unblock the संकेत and change any संक_छोड़ो to संक_पूर्व.
 *
 * Note: If we unblock the संकेत, we always reset it to संक_पूर्व,
 * since we करो not want to have a संकेत handler that was blocked
 * be invoked when user space had explicitly blocked it.
 *
 * We करोn't want to have recursive SIGSEGV's etc, क्रम example,
 * that is why we also clear SIGNAL_UNKILLABLE.
 */
अटल पूर्णांक
क्रमce_sig_info_to_task(काष्ठा kernel_siginfo *info, काष्ठा task_काष्ठा *t)
अणु
	अचिन्हित दीर्घ पूर्णांक flags;
	पूर्णांक ret, blocked, ignored;
	काष्ठा k_sigaction *action;
	पूर्णांक sig = info->si_signo;

	spin_lock_irqsave(&t->sighand->siglock, flags);
	action = &t->sighand->action[sig-1];
	ignored = action->sa.sa_handler == संक_छोड़ो;
	blocked = sigismember(&t->blocked, sig);
	अगर (blocked || ignored) अणु
		action->sa.sa_handler = संक_पूर्व;
		अगर (blocked) अणु
			sigdअन्यथाt(&t->blocked, sig);
			recalc_संक_बाकी_and_wake(t);
		पूर्ण
	पूर्ण
	/*
	 * Don't clear SIGNAL_UNKILLABLE for traced tasks, users won't expect
	 * debugging to leave init समाप्तable.
	 */
	अगर (action->sa.sa_handler == संक_पूर्व && !t->ptrace)
		t->संकेत->flags &= ~SIGNAL_UNKILLABLE;
	ret = send_संकेत(sig, info, t, PIDTYPE_PID);
	spin_unlock_irqrestore(&t->sighand->siglock, flags);

	वापस ret;
पूर्ण

पूर्णांक क्रमce_sig_info(काष्ठा kernel_siginfo *info)
अणु
	वापस क्रमce_sig_info_to_task(info, current);
पूर्ण

/*
 * Nuke all other thपढ़ोs in the group.
 */
पूर्णांक zap_other_thपढ़ोs(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा task_काष्ठा *t = p;
	पूर्णांक count = 0;

	p->संकेत->group_stop_count = 0;

	जबतक_each_thपढ़ो(p, t) अणु
		task_clear_jobctl_pending(t, JOBCTL_PENDING_MASK);
		count++;

		/* Don't bother with alपढ़ोy dead thपढ़ोs */
		अगर (t->निकास_state)
			जारी;
		sigaddset(&t->pending.संकेत, SIGKILL);
		संकेत_wake_up(t, 1);
	पूर्ण

	वापस count;
पूर्ण

काष्ठा sighand_काष्ठा *__lock_task_sighand(काष्ठा task_काष्ठा *tsk,
					   अचिन्हित दीर्घ *flags)
अणु
	काष्ठा sighand_काष्ठा *sighand;

	rcu_पढ़ो_lock();
	क्रम (;;) अणु
		sighand = rcu_dereference(tsk->sighand);
		अगर (unlikely(sighand == शून्य))
			अवरोध;

		/*
		 * This sighand can be alपढ़ोy मुक्तd and even reused, but
		 * we rely on SLAB_TYPESAFE_BY_RCU and sighand_ctor() which
		 * initializes ->siglock: this slab can't go away, it has
		 * the same object type, ->siglock can't be reinitialized.
		 *
		 * We need to ensure that tsk->sighand is still the same
		 * after we take the lock, we can race with de_thपढ़ो() or
		 * __निकास_संकेत(). In the latter हाल the next iteration
		 * must see ->sighand == शून्य.
		 */
		spin_lock_irqsave(&sighand->siglock, *flags);
		अगर (likely(sighand == rcu_access_poपूर्णांकer(tsk->sighand)))
			अवरोध;
		spin_unlock_irqrestore(&sighand->siglock, *flags);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस sighand;
पूर्ण

/*
 * send संकेत info to all the members of a group
 */
पूर्णांक group_send_sig_info(पूर्णांक sig, काष्ठा kernel_siginfo *info,
			काष्ठा task_काष्ठा *p, क्रमागत pid_type type)
अणु
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	ret = check_समाप्त_permission(sig, info, p);
	rcu_पढ़ो_unlock();

	अगर (!ret && sig)
		ret = करो_send_sig_info(sig, info, p, type);

	वापस ret;
पूर्ण

/*
 * __समाप्त_pgrp_info() sends a संकेत to a process group: this is what the tty
 * control अक्षरacters करो (^C, ^Z etc)
 * - the caller must hold at least a पढ़ोlock on tasklist_lock
 */
पूर्णांक __समाप्त_pgrp_info(पूर्णांक sig, काष्ठा kernel_siginfo *info, काष्ठा pid *pgrp)
अणु
	काष्ठा task_काष्ठा *p = शून्य;
	पूर्णांक retval, success;

	success = 0;
	retval = -ESRCH;
	करो_each_pid_task(pgrp, PIDTYPE_PGID, p) अणु
		पूर्णांक err = group_send_sig_info(sig, info, p, PIDTYPE_PGID);
		success |= !err;
		retval = err;
	पूर्ण जबतक_each_pid_task(pgrp, PIDTYPE_PGID, p);
	वापस success ? 0 : retval;
पूर्ण

पूर्णांक समाप्त_pid_info(पूर्णांक sig, काष्ठा kernel_siginfo *info, काष्ठा pid *pid)
अणु
	पूर्णांक error = -ESRCH;
	काष्ठा task_काष्ठा *p;

	क्रम (;;) अणु
		rcu_पढ़ो_lock();
		p = pid_task(pid, PIDTYPE_PID);
		अगर (p)
			error = group_send_sig_info(sig, info, p, PIDTYPE_TGID);
		rcu_पढ़ो_unlock();
		अगर (likely(!p || error != -ESRCH))
			वापस error;

		/*
		 * The task was unhashed in between, try again.  If it
		 * is dead, pid_task() will वापस शून्य, अगर we race with
		 * de_thपढ़ो() it will find the new leader.
		 */
	पूर्ण
पूर्ण

अटल पूर्णांक समाप्त_proc_info(पूर्णांक sig, काष्ठा kernel_siginfo *info, pid_t pid)
अणु
	पूर्णांक error;
	rcu_पढ़ो_lock();
	error = समाप्त_pid_info(sig, info, find_vpid(pid));
	rcu_पढ़ो_unlock();
	वापस error;
पूर्ण

अटल अंतरभूत bool समाप्त_as_cred_perm(स्थिर काष्ठा cred *cred,
				     काष्ठा task_काष्ठा *target)
अणु
	स्थिर काष्ठा cred *pcred = __task_cred(target);

	वापस uid_eq(cred->euid, pcred->suid) ||
	       uid_eq(cred->euid, pcred->uid) ||
	       uid_eq(cred->uid, pcred->suid) ||
	       uid_eq(cred->uid, pcred->uid);
पूर्ण

/*
 * The usb asyncio usage of siginfo is wrong.  The glibc support
 * क्रम asyncio which uses SI_ASYNCIO assumes the layout is SIL_RT.
 * AKA after the generic fields:
 *	kernel_pid_t	si_pid;
 *	kernel_uid32_t	si_uid;
 *	sigval_t	si_value;
 *
 * Unक्रमtunately when usb generates SI_ASYNCIO it assumes the layout
 * after the generic fields is:
 *	व्योम __user 	*si_addr;
 *
 * This is a practical problem when there is a 64bit big endian kernel
 * and a 32bit userspace.  As the 32bit address will encoded in the low
 * 32bits of the poपूर्णांकer.  Those low 32bits will be stored at higher
 * address than appear in a 32 bit poपूर्णांकer.  So userspace will not
 * see the address it was expecting क्रम it's completions.
 *
 * There is nothing in the encoding that can allow
 * copy_siginfo_to_user32 to detect this confusion of क्रमmats, so
 * handle this by requiring the caller of समाप्त_pid_usb_asyncio to
 * notice when this situration takes place and to store the 32bit
 * poपूर्णांकer in sival_पूर्णांक, instead of sival_addr of the sigval_t addr
 * parameter.
 */
पूर्णांक समाप्त_pid_usb_asyncio(पूर्णांक sig, पूर्णांक त्रुटि_सं, sigval_t addr,
			 काष्ठा pid *pid, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा kernel_siginfo info;
	काष्ठा task_काष्ठा *p;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;

	अगर (!valid_संकेत(sig))
		वापस ret;

	clear_siginfo(&info);
	info.si_signo = sig;
	info.si_त्रुटि_सं = त्रुटि_सं;
	info.si_code = SI_ASYNCIO;
	*((sigval_t *)&info.si_pid) = addr;

	rcu_पढ़ो_lock();
	p = pid_task(pid, PIDTYPE_PID);
	अगर (!p) अणु
		ret = -ESRCH;
		जाओ out_unlock;
	पूर्ण
	अगर (!समाप्त_as_cred_perm(cred, p)) अणु
		ret = -EPERM;
		जाओ out_unlock;
	पूर्ण
	ret = security_task_समाप्त(p, &info, sig, cred);
	अगर (ret)
		जाओ out_unlock;

	अगर (sig) अणु
		अगर (lock_task_sighand(p, &flags)) अणु
			ret = __send_संकेत(sig, &info, p, PIDTYPE_TGID, false);
			unlock_task_sighand(p, &flags);
		पूर्ण अन्यथा
			ret = -ESRCH;
	पूर्ण
out_unlock:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(समाप्त_pid_usb_asyncio);

/*
 * समाप्त_something_info() पूर्णांकerprets pid in पूर्णांकeresting ways just like समाप्त(2).
 *
 * POSIX specअगरies that समाप्त(-1,sig) is unspecअगरied, but what we have
 * is probably wrong.  Should make it like BSD or SYSV.
 */

अटल पूर्णांक समाप्त_something_info(पूर्णांक sig, काष्ठा kernel_siginfo *info, pid_t pid)
अणु
	पूर्णांक ret;

	अगर (pid > 0)
		वापस समाप्त_proc_info(sig, info, pid);

	/* -पूर्णांक_न्यून is undefined.  Exclude this हाल to aव्योम a UBSAN warning */
	अगर (pid == पूर्णांक_न्यून)
		वापस -ESRCH;

	पढ़ो_lock(&tasklist_lock);
	अगर (pid != -1) अणु
		ret = __समाप्त_pgrp_info(sig, info,
				pid ? find_vpid(-pid) : task_pgrp(current));
	पूर्ण अन्यथा अणु
		पूर्णांक retval = 0, count = 0;
		काष्ठा task_काष्ठा * p;

		क्रम_each_process(p) अणु
			अगर (task_pid_vnr(p) > 1 &&
					!same_thपढ़ो_group(p, current)) अणु
				पूर्णांक err = group_send_sig_info(sig, info, p,
							      PIDTYPE_MAX);
				++count;
				अगर (err != -EPERM)
					retval = err;
			पूर्ण
		पूर्ण
		ret = count ? retval : -ESRCH;
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);

	वापस ret;
पूर्ण

/*
 * These are क्रम backward compatibility with the rest of the kernel source.
 */

पूर्णांक send_sig_info(पूर्णांक sig, काष्ठा kernel_siginfo *info, काष्ठा task_काष्ठा *p)
अणु
	/*
	 * Make sure legacy kernel users करोn't send in bad values
	 * (normal paths check this in check_समाप्त_permission).
	 */
	अगर (!valid_संकेत(sig))
		वापस -EINVAL;

	वापस करो_send_sig_info(sig, info, p, PIDTYPE_PID);
पूर्ण
EXPORT_SYMBOL(send_sig_info);

#घोषणा __si_special(priv) \
	((priv) ? SEND_SIG_PRIV : SEND_SIG_NOINFO)

पूर्णांक
send_sig(पूर्णांक sig, काष्ठा task_काष्ठा *p, पूर्णांक priv)
अणु
	वापस send_sig_info(sig, __si_special(priv), p);
पूर्ण
EXPORT_SYMBOL(send_sig);

व्योम क्रमce_sig(पूर्णांक sig)
अणु
	काष्ठा kernel_siginfo info;

	clear_siginfo(&info);
	info.si_signo = sig;
	info.si_त्रुटि_सं = 0;
	info.si_code = SI_KERNEL;
	info.si_pid = 0;
	info.si_uid = 0;
	क्रमce_sig_info(&info);
पूर्ण
EXPORT_SYMBOL(क्रमce_sig);

/*
 * When things go south during संकेत handling, we
 * will क्रमce a संक_अंश. And अगर the संकेत that caused
 * the problem was alपढ़ोy a संक_अंश, we'll want to
 * make sure we करोn't even try to deliver the संकेत..
 */
व्योम क्रमce_sigsegv(पूर्णांक sig)
अणु
	काष्ठा task_काष्ठा *p = current;

	अगर (sig == संक_अंश) अणु
		अचिन्हित दीर्घ flags;
		spin_lock_irqsave(&p->sighand->siglock, flags);
		p->sighand->action[sig - 1].sa.sa_handler = संक_पूर्व;
		spin_unlock_irqrestore(&p->sighand->siglock, flags);
	पूर्ण
	क्रमce_sig(संक_अंश);
पूर्ण

पूर्णांक क्रमce_sig_fault_to_task(पूर्णांक sig, पूर्णांक code, व्योम __user *addr
	___ARCH_SI_TRAPNO(पूर्णांक trapno)
	___ARCH_SI_IA64(पूर्णांक imm, अचिन्हित पूर्णांक flags, अचिन्हित दीर्घ isr)
	, काष्ठा task_काष्ठा *t)
अणु
	काष्ठा kernel_siginfo info;

	clear_siginfo(&info);
	info.si_signo = sig;
	info.si_त्रुटि_सं = 0;
	info.si_code  = code;
	info.si_addr  = addr;
#अगर_घोषित __ARCH_SI_TRAPNO
	info.si_trapno = trapno;
#पूर्ण_अगर
#अगर_घोषित __ia64__
	info.si_imm = imm;
	info.si_flags = flags;
	info.si_isr = isr;
#पूर्ण_अगर
	वापस क्रमce_sig_info_to_task(&info, t);
पूर्ण

पूर्णांक क्रमce_sig_fault(पूर्णांक sig, पूर्णांक code, व्योम __user *addr
	___ARCH_SI_TRAPNO(पूर्णांक trapno)
	___ARCH_SI_IA64(पूर्णांक imm, अचिन्हित पूर्णांक flags, अचिन्हित दीर्घ isr))
अणु
	वापस क्रमce_sig_fault_to_task(sig, code, addr
				       ___ARCH_SI_TRAPNO(trapno)
				       ___ARCH_SI_IA64(imm, flags, isr), current);
पूर्ण

पूर्णांक send_sig_fault(पूर्णांक sig, पूर्णांक code, व्योम __user *addr
	___ARCH_SI_TRAPNO(पूर्णांक trapno)
	___ARCH_SI_IA64(पूर्णांक imm, अचिन्हित पूर्णांक flags, अचिन्हित दीर्घ isr)
	, काष्ठा task_काष्ठा *t)
अणु
	काष्ठा kernel_siginfo info;

	clear_siginfo(&info);
	info.si_signo = sig;
	info.si_त्रुटि_सं = 0;
	info.si_code  = code;
	info.si_addr  = addr;
#अगर_घोषित __ARCH_SI_TRAPNO
	info.si_trapno = trapno;
#पूर्ण_अगर
#अगर_घोषित __ia64__
	info.si_imm = imm;
	info.si_flags = flags;
	info.si_isr = isr;
#पूर्ण_अगर
	वापस send_sig_info(info.si_signo, &info, t);
पूर्ण

पूर्णांक क्रमce_sig_mceerr(पूर्णांक code, व्योम __user *addr, लघु lsb)
अणु
	काष्ठा kernel_siginfo info;

	WARN_ON((code != BUS_MCEERR_AO) && (code != BUS_MCEERR_AR));
	clear_siginfo(&info);
	info.si_signo = SIGBUS;
	info.si_त्रुटि_सं = 0;
	info.si_code = code;
	info.si_addr = addr;
	info.si_addr_lsb = lsb;
	वापस क्रमce_sig_info(&info);
पूर्ण

पूर्णांक send_sig_mceerr(पूर्णांक code, व्योम __user *addr, लघु lsb, काष्ठा task_काष्ठा *t)
अणु
	काष्ठा kernel_siginfo info;

	WARN_ON((code != BUS_MCEERR_AO) && (code != BUS_MCEERR_AR));
	clear_siginfo(&info);
	info.si_signo = SIGBUS;
	info.si_त्रुटि_सं = 0;
	info.si_code = code;
	info.si_addr = addr;
	info.si_addr_lsb = lsb;
	वापस send_sig_info(info.si_signo, &info, t);
पूर्ण
EXPORT_SYMBOL(send_sig_mceerr);

पूर्णांक क्रमce_sig_bnderr(व्योम __user *addr, व्योम __user *lower, व्योम __user *upper)
अणु
	काष्ठा kernel_siginfo info;

	clear_siginfo(&info);
	info.si_signo = संक_अंश;
	info.si_त्रुटि_सं = 0;
	info.si_code  = SEGV_BNDERR;
	info.si_addr  = addr;
	info.si_lower = lower;
	info.si_upper = upper;
	वापस क्रमce_sig_info(&info);
पूर्ण

#अगर_घोषित SEGV_PKUERR
पूर्णांक क्रमce_sig_pkuerr(व्योम __user *addr, u32 pkey)
अणु
	काष्ठा kernel_siginfo info;

	clear_siginfo(&info);
	info.si_signo = संक_अंश;
	info.si_त्रुटि_सं = 0;
	info.si_code  = SEGV_PKUERR;
	info.si_addr  = addr;
	info.si_pkey  = pkey;
	वापस क्रमce_sig_info(&info);
पूर्ण
#पूर्ण_अगर

पूर्णांक क्रमce_sig_perf(व्योम __user *addr, u32 type, u64 sig_data)
अणु
	काष्ठा kernel_siginfo info;

	clear_siginfo(&info);
	info.si_signo     = SIGTRAP;
	info.si_त्रुटि_सं     = 0;
	info.si_code      = TRAP_PERF;
	info.si_addr      = addr;
	info.si_perf_data = sig_data;
	info.si_perf_type = type;

	वापस क्रमce_sig_info(&info);
पूर्ण

/* For the crazy architectures that include trap inक्रमmation in
 * the त्रुटि_सं field, instead of an actual त्रुटि_सं value.
 */
पूर्णांक क्रमce_sig_ptrace_त्रुटि_सं_trap(पूर्णांक त्रुटि_सं, व्योम __user *addr)
अणु
	काष्ठा kernel_siginfo info;

	clear_siginfo(&info);
	info.si_signo = SIGTRAP;
	info.si_त्रुटि_सं = त्रुटि_सं;
	info.si_code  = TRAP_HWBKPT;
	info.si_addr  = addr;
	वापस क्रमce_sig_info(&info);
पूर्ण

पूर्णांक समाप्त_pgrp(काष्ठा pid *pid, पूर्णांक sig, पूर्णांक priv)
अणु
	पूर्णांक ret;

	पढ़ो_lock(&tasklist_lock);
	ret = __समाप्त_pgrp_info(sig, __si_special(priv), pid);
	पढ़ो_unlock(&tasklist_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(समाप्त_pgrp);

पूर्णांक समाप्त_pid(काष्ठा pid *pid, पूर्णांक sig, पूर्णांक priv)
अणु
	वापस समाप्त_pid_info(sig, __si_special(priv), pid);
पूर्ण
EXPORT_SYMBOL(समाप्त_pid);

/*
 * These functions support sending संकेतs using pपुनः_स्मृतिated sigqueue
 * काष्ठाures.  This is needed "because realसमय applications cannot
 * afक्रमd to lose notअगरications of asynchronous events, like समयr
 * expirations or I/O completions".  In the हाल of POSIX Timers
 * we allocate the sigqueue काष्ठाure from the समयr_create.  If this
 * allocation fails we are able to report the failure to the application
 * with an EAGAIN error.
 */
काष्ठा sigqueue *sigqueue_alloc(व्योम)
अणु
	वापस __sigqueue_alloc(-1, current, GFP_KERNEL, 0, SIGQUEUE_PREALLOC);
पूर्ण

व्योम sigqueue_मुक्त(काष्ठा sigqueue *q)
अणु
	अचिन्हित दीर्घ flags;
	spinlock_t *lock = &current->sighand->siglock;

	BUG_ON(!(q->flags & SIGQUEUE_PREALLOC));
	/*
	 * We must hold ->siglock जबतक testing q->list
	 * to serialize with collect_संकेत() or with
	 * __निकास_संकेत()->flush_sigqueue().
	 */
	spin_lock_irqsave(lock, flags);
	q->flags &= ~SIGQUEUE_PREALLOC;
	/*
	 * If it is queued it will be मुक्तd when dequeued,
	 * like the "regular" sigqueue.
	 */
	अगर (!list_empty(&q->list))
		q = शून्य;
	spin_unlock_irqrestore(lock, flags);

	अगर (q)
		__sigqueue_मुक्त(q);
पूर्ण

पूर्णांक send_sigqueue(काष्ठा sigqueue *q, काष्ठा pid *pid, क्रमागत pid_type type)
अणु
	पूर्णांक sig = q->info.si_signo;
	काष्ठा संक_बाकी *pending;
	काष्ठा task_काष्ठा *t;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, result;

	BUG_ON(!(q->flags & SIGQUEUE_PREALLOC));

	ret = -1;
	rcu_पढ़ो_lock();
	t = pid_task(pid, type);
	अगर (!t || !likely(lock_task_sighand(t, &flags)))
		जाओ ret;

	ret = 1; /* the संकेत is ignored */
	result = TRACE_SIGNAL_IGNORED;
	अगर (!prepare_संकेत(sig, t, false))
		जाओ out;

	ret = 0;
	अगर (unlikely(!list_empty(&q->list))) अणु
		/*
		 * If an SI_TIMER entry is alपढ़ोy queue just increment
		 * the overrun count.
		 */
		BUG_ON(q->info.si_code != SI_TIMER);
		q->info.si_overrun++;
		result = TRACE_SIGNAL_ALREADY_PENDING;
		जाओ out;
	पूर्ण
	q->info.si_overrun = 0;

	संकेतfd_notअगरy(t, sig);
	pending = (type != PIDTYPE_PID) ? &t->संकेत->shared_pending : &t->pending;
	list_add_tail(&q->list, &pending->list);
	sigaddset(&pending->संकेत, sig);
	complete_संकेत(sig, t, type);
	result = TRACE_SIGNAL_DELIVERED;
out:
	trace_संकेत_generate(sig, &q->info, t, type != PIDTYPE_PID, result);
	unlock_task_sighand(t, &flags);
ret:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल व्योम करो_notअगरy_pidfd(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा pid *pid;

	WARN_ON(task->निकास_state == 0);
	pid = task_pid(task);
	wake_up_all(&pid->रुको_pidfd);
पूर्ण

/*
 * Let a parent know about the death of a child.
 * For a stopped/जारीd status change, use करो_notअगरy_parent_cldstop instead.
 *
 * Returns true अगर our parent ignored us and so we've चयनed to
 * self-reaping.
 */
bool करो_notअगरy_parent(काष्ठा task_काष्ठा *tsk, पूर्णांक sig)
अणु
	काष्ठा kernel_siginfo info;
	अचिन्हित दीर्घ flags;
	काष्ठा sighand_काष्ठा *psig;
	bool स्वतःreap = false;
	u64 uसमय, sसमय;

	BUG_ON(sig == -1);

 	/* करो_notअगरy_parent_cldstop should have been called instead.  */
 	BUG_ON(task_is_stopped_or_traced(tsk));

	BUG_ON(!tsk->ptrace &&
	       (tsk->group_leader != tsk || !thपढ़ो_group_empty(tsk)));

	/* Wake up all pidfd रुकोers */
	करो_notअगरy_pidfd(tsk);

	अगर (sig != SIGCHLD) अणु
		/*
		 * This is only possible अगर parent == real_parent.
		 * Check अगर it has changed security करोमुख्य.
		 */
		अगर (tsk->parent_exec_id != READ_ONCE(tsk->parent->self_exec_id))
			sig = SIGCHLD;
	पूर्ण

	clear_siginfo(&info);
	info.si_signo = sig;
	info.si_त्रुटि_सं = 0;
	/*
	 * We are under tasklist_lock here so our parent is tied to
	 * us and cannot change.
	 *
	 * task_active_pid_ns will always वापस the same pid namespace
	 * until a task passes through release_task.
	 *
	 * ग_लिखो_lock() currently calls preempt_disable() which is the
	 * same as rcu_पढ़ो_lock(), but according to Oleg, this is not
	 * correct to rely on this
	 */
	rcu_पढ़ो_lock();
	info.si_pid = task_pid_nr_ns(tsk, task_active_pid_ns(tsk->parent));
	info.si_uid = from_kuid_munged(task_cred_xxx(tsk->parent, user_ns),
				       task_uid(tsk));
	rcu_पढ़ो_unlock();

	task_cpuसमय(tsk, &uसमय, &sसमय);
	info.si_uसमय = nsec_to_घड़ी_प्रकार(uसमय + tsk->संकेत->uसमय);
	info.si_sसमय = nsec_to_घड़ी_प्रकार(sसमय + tsk->संकेत->sसमय);

	info.si_status = tsk->निकास_code & 0x7f;
	अगर (tsk->निकास_code & 0x80)
		info.si_code = CLD_DUMPED;
	अन्यथा अगर (tsk->निकास_code & 0x7f)
		info.si_code = CLD_KILLED;
	अन्यथा अणु
		info.si_code = CLD_EXITED;
		info.si_status = tsk->निकास_code >> 8;
	पूर्ण

	psig = tsk->parent->sighand;
	spin_lock_irqsave(&psig->siglock, flags);
	अगर (!tsk->ptrace && sig == SIGCHLD &&
	    (psig->action[SIGCHLD-1].sa.sa_handler == संक_छोड़ो ||
	     (psig->action[SIGCHLD-1].sa.sa_flags & SA_NOCLDWAIT))) अणु
		/*
		 * We are निकासing and our parent करोesn't care.  POSIX.1
		 * defines special semantics क्रम setting SIGCHLD to संक_छोड़ो
		 * or setting the SA_NOCLDWAIT flag: we should be reaped
		 * स्वतःmatically and not left क्रम our parent's रुको4 call.
		 * Rather than having the parent करो it as a magic kind of
		 * संकेत handler, we just set this to tell करो_निकास that we
		 * can be cleaned up without becoming a zombie.  Note that
		 * we still call __wake_up_parent in this हाल, because a
		 * blocked sys_रुको4 might now वापस -ECHILD.
		 *
		 * Whether we send SIGCHLD or not क्रम SA_NOCLDWAIT
		 * is implementation-defined: we करो (अगर you करोn't want
		 * it, just use संक_छोड़ो instead).
		 */
		स्वतःreap = true;
		अगर (psig->action[SIGCHLD-1].sa.sa_handler == संक_छोड़ो)
			sig = 0;
	पूर्ण
	/*
	 * Send with __send_संकेत as si_pid and si_uid are in the
	 * parent's namespaces.
	 */
	अगर (valid_संकेत(sig) && sig)
		__send_संकेत(sig, &info, tsk->parent, PIDTYPE_TGID, false);
	__wake_up_parent(tsk, tsk->parent);
	spin_unlock_irqrestore(&psig->siglock, flags);

	वापस स्वतःreap;
पूर्ण

/**
 * करो_notअगरy_parent_cldstop - notअगरy parent of stopped/जारीd state change
 * @tsk: task reporting the state change
 * @क्रम_ptracer: the notअगरication is क्रम ptracer
 * @why: CLD_अणुCONTINUED|STOPPED|TRAPPEDपूर्ण to report
 *
 * Notअगरy @tsk's parent that the stopped/जारीd state has changed.  If
 * @क्रम_ptracer is %false, @tsk's group leader notअगरies to its real parent.
 * If %true, @tsk reports to @tsk->parent which should be the ptracer.
 *
 * CONTEXT:
 * Must be called with tasklist_lock at least पढ़ो locked.
 */
अटल व्योम करो_notअगरy_parent_cldstop(काष्ठा task_काष्ठा *tsk,
				     bool क्रम_ptracer, पूर्णांक why)
अणु
	काष्ठा kernel_siginfo info;
	अचिन्हित दीर्घ flags;
	काष्ठा task_काष्ठा *parent;
	काष्ठा sighand_काष्ठा *sighand;
	u64 uसमय, sसमय;

	अगर (क्रम_ptracer) अणु
		parent = tsk->parent;
	पूर्ण अन्यथा अणु
		tsk = tsk->group_leader;
		parent = tsk->real_parent;
	पूर्ण

	clear_siginfo(&info);
	info.si_signo = SIGCHLD;
	info.si_त्रुटि_सं = 0;
	/*
	 * see comment in करो_notअगरy_parent() about the following 4 lines
	 */
	rcu_पढ़ो_lock();
	info.si_pid = task_pid_nr_ns(tsk, task_active_pid_ns(parent));
	info.si_uid = from_kuid_munged(task_cred_xxx(parent, user_ns), task_uid(tsk));
	rcu_पढ़ो_unlock();

	task_cpuसमय(tsk, &uसमय, &sसमय);
	info.si_uसमय = nsec_to_घड़ी_प्रकार(uसमय);
	info.si_sसमय = nsec_to_घड़ी_प्रकार(sसमय);

 	info.si_code = why;
 	चयन (why) अणु
 	हाल CLD_CONTINUED:
 		info.si_status = SIGCONT;
 		अवरोध;
 	हाल CLD_STOPPED:
 		info.si_status = tsk->संकेत->group_निकास_code & 0x7f;
 		अवरोध;
 	हाल CLD_TRAPPED:
 		info.si_status = tsk->निकास_code & 0x7f;
 		अवरोध;
 	शेष:
 		BUG();
 	पूर्ण

	sighand = parent->sighand;
	spin_lock_irqsave(&sighand->siglock, flags);
	अगर (sighand->action[SIGCHLD-1].sa.sa_handler != संक_छोड़ो &&
	    !(sighand->action[SIGCHLD-1].sa.sa_flags & SA_NOCLDSTOP))
		__group_send_sig_info(SIGCHLD, &info, parent);
	/*
	 * Even अगर SIGCHLD is not generated, we must wake up रुको4 calls.
	 */
	__wake_up_parent(tsk, parent);
	spin_unlock_irqrestore(&sighand->siglock, flags);
पूर्ण

अटल अंतरभूत bool may_ptrace_stop(व्योम)
अणु
	अगर (!likely(current->ptrace))
		वापस false;
	/*
	 * Are we in the middle of करो_coredump?
	 * If so and our tracer is also part of the coredump stopping
	 * is a deadlock situation, and poपूर्णांकless because our tracer
	 * is dead so करोn't allow us to stop.
	 * If SIGKILL was alपढ़ोy sent beक्रमe the caller unlocked
	 * ->siglock we must see ->core_state != शून्य. Otherwise it
	 * is safe to enter schedule().
	 *
	 * This is almost outdated, a task with the pending SIGKILL can't
	 * block in TASK_TRACED. But PTRACE_EVENT_EXIT can be reported
	 * after SIGKILL was alपढ़ोy dequeued.
	 */
	अगर (unlikely(current->mm->core_state) &&
	    unlikely(current->mm == current->parent->mm))
		वापस false;

	वापस true;
पूर्ण

/*
 * Return non-zero अगर there is a SIGKILL that should be waking us up.
 * Called with the siglock held.
 */
अटल bool sigसमाप्त_pending(काष्ठा task_काष्ठा *tsk)
अणु
	वापस sigismember(&tsk->pending.संकेत, SIGKILL) ||
	       sigismember(&tsk->संकेत->shared_pending.संकेत, SIGKILL);
पूर्ण

/*
 * This must be called with current->sighand->siglock held.
 *
 * This should be the path क्रम all ptrace stops.
 * We always set current->last_siginfo जबतक stopped here.
 * That makes it a way to test a stopped process क्रम
 * being ptrace-stopped vs being job-control-stopped.
 *
 * If we actually decide not to stop at all because the tracer
 * is gone, we keep current->निकास_code unless clear_code.
 */
अटल व्योम ptrace_stop(पूर्णांक निकास_code, पूर्णांक why, पूर्णांक clear_code, kernel_siginfo_t *info)
	__releases(&current->sighand->siglock)
	__acquires(&current->sighand->siglock)
अणु
	bool gstop_करोne = false;

	अगर (arch_ptrace_stop_needed(निकास_code, info)) अणु
		/*
		 * The arch code has something special to करो beक्रमe a
		 * ptrace stop.  This is allowed to block, e.g. क्रम faults
		 * on user stack pages.  We can't keep the siglock जबतक
		 * calling arch_ptrace_stop, so we must release it now.
		 * To preserve proper semantics, we must करो this beक्रमe
		 * any संकेत bookkeeping like checking group_stop_count.
		 * Meanजबतक, a SIGKILL could come in beक्रमe we retake the
		 * siglock.  That must prevent us from sleeping in TASK_TRACED.
		 * So after regaining the lock, we must check क्रम SIGKILL.
		 */
		spin_unlock_irq(&current->sighand->siglock);
		arch_ptrace_stop(निकास_code, info);
		spin_lock_irq(&current->sighand->siglock);
		अगर (sigसमाप्त_pending(current))
			वापस;
	पूर्ण

	set_special_state(TASK_TRACED);

	/*
	 * We're committing to trapping.  TRACED should be visible beक्रमe
	 * TRAPPING is cleared; otherwise, the tracer might fail करो_रुको().
	 * Also, transition to TRACED and updates to ->jobctl should be
	 * atomic with respect to siglock and should be करोne after the arch
	 * hook as siglock is released and regrabbed across it.
	 *
	 *     TRACER				    TRACEE
	 *
	 *     ptrace_attach()
	 * [L]   रुको_on_bit(JOBCTL_TRAPPING)	[S] set_special_state(TRACED)
	 *     करो_रुको()
	 *       set_current_state()                smp_wmb();
	 *       ptrace_करो_रुको()
	 *         रुको_task_stopped()
	 *           task_stopped_code()
	 * [L]         task_is_traced()		[S] task_clear_jobctl_trapping();
	 */
	smp_wmb();

	current->last_siginfo = info;
	current->निकास_code = निकास_code;

	/*
	 * If @why is CLD_STOPPED, we're trapping to participate in a group
	 * stop.  Do the bookkeeping.  Note that अगर SIGCONT was delievered
	 * across siglock relocks since INTERRUPT was scheduled, PENDING
	 * could be clear now.  We act as अगर SIGCONT is received after
	 * TASK_TRACED is entered - ignore it.
	 */
	अगर (why == CLD_STOPPED && (current->jobctl & JOBCTL_STOP_PENDING))
		gstop_करोne = task_participate_group_stop(current);

	/* any trap clears pending STOP trap, STOP trap clears NOTIFY */
	task_clear_jobctl_pending(current, JOBCTL_TRAP_STOP);
	अगर (info && info->si_code >> 8 == PTRACE_EVENT_STOP)
		task_clear_jobctl_pending(current, JOBCTL_TRAP_NOTIFY);

	/* entering a trap, clear TRAPPING */
	task_clear_jobctl_trapping(current);

	spin_unlock_irq(&current->sighand->siglock);
	पढ़ो_lock(&tasklist_lock);
	अगर (may_ptrace_stop()) अणु
		/*
		 * Notअगरy parents of the stop.
		 *
		 * While ptraced, there are two parents - the ptracer and
		 * the real_parent of the group_leader.  The ptracer should
		 * know about every stop जबतक the real parent is only
		 * पूर्णांकerested in the completion of group stop.  The states
		 * क्रम the two करोn't पूर्णांकeract with each other.  Notअगरy
		 * separately unless they're gonna be duplicates.
		 */
		करो_notअगरy_parent_cldstop(current, true, why);
		अगर (gstop_करोne && ptrace_reparented(current))
			करो_notअगरy_parent_cldstop(current, false, why);

		/*
		 * Don't want to allow preemption here, because
		 * sys_ptrace() needs this task to be inactive.
		 *
		 * XXX: implement पढ़ो_unlock_no_resched().
		 */
		preempt_disable();
		पढ़ो_unlock(&tasklist_lock);
		cgroup_enter_frozen();
		preempt_enable_no_resched();
		मुक्तzable_schedule();
		cgroup_leave_frozen(true);
	पूर्ण अन्यथा अणु
		/*
		 * By the समय we got the lock, our tracer went away.
		 * Don't drop the lock yet, another tracer may come.
		 *
		 * If @gstop_करोne, the ptracer went away between group stop
		 * completion and here.  During detach, it would have set
		 * JOBCTL_STOP_PENDING on us and we'll re-enter
		 * TASK_STOPPED in करो_संकेत_stop() on वापस, so notअगरying
		 * the real parent of the group stop completion is enough.
		 */
		अगर (gstop_करोne)
			करो_notअगरy_parent_cldstop(current, false, why);

		/* tasklist protects us from ptrace_मुक्तze_traced() */
		__set_current_state(TASK_RUNNING);
		अगर (clear_code)
			current->निकास_code = 0;
		पढ़ो_unlock(&tasklist_lock);
	पूर्ण

	/*
	 * We are back.  Now reacquire the siglock beक्रमe touching
	 * last_siginfo, so that we are sure to have synchronized with
	 * any संकेत-sending on another CPU that wants to examine it.
	 */
	spin_lock_irq(&current->sighand->siglock);
	current->last_siginfo = शून्य;

	/* LISTENING can be set only during STOP traps, clear it */
	current->jobctl &= ~JOBCTL_LISTENING;

	/*
	 * Queued संकेतs ignored us जबतक we were stopped क्रम tracing.
	 * So check क्रम any that we should take beक्रमe resuming user mode.
	 * This sets TIF_SIGPENDING, but never clears it.
	 */
	recalc_संक_बाकी_tsk(current);
पूर्ण

अटल व्योम ptrace_करो_notअगरy(पूर्णांक signr, पूर्णांक निकास_code, पूर्णांक why)
अणु
	kernel_siginfo_t info;

	clear_siginfo(&info);
	info.si_signo = signr;
	info.si_code = निकास_code;
	info.si_pid = task_pid_vnr(current);
	info.si_uid = from_kuid_munged(current_user_ns(), current_uid());

	/* Let the debugger run.  */
	ptrace_stop(निकास_code, why, 1, &info);
पूर्ण

व्योम ptrace_notअगरy(पूर्णांक निकास_code)
अणु
	BUG_ON((निकास_code & (0x7f | ~0xffff)) != SIGTRAP);
	अगर (unlikely(current->task_works))
		task_work_run();

	spin_lock_irq(&current->sighand->siglock);
	ptrace_करो_notअगरy(SIGTRAP, निकास_code, CLD_TRAPPED);
	spin_unlock_irq(&current->sighand->siglock);
पूर्ण

/**
 * करो_संकेत_stop - handle group stop क्रम SIGSTOP and other stop संकेतs
 * @signr: signr causing group stop अगर initiating
 *
 * If %JOBCTL_STOP_PENDING is not set yet, initiate group stop with @signr
 * and participate in it.  If alपढ़ोy set, participate in the existing
 * group stop.  If participated in a group stop (and thus slept), %true is
 * वापसed with siglock released.
 *
 * If ptraced, this function करोesn't handle stop itself.  Instead,
 * %JOBCTL_TRAP_STOP is scheduled and %false is वापसed with siglock
 * untouched.  The caller must ensure that INTERRUPT trap handling takes
 * places afterwards.
 *
 * CONTEXT:
 * Must be called with @current->sighand->siglock held, which is released
 * on %true वापस.
 *
 * RETURNS:
 * %false अगर group stop is alपढ़ोy cancelled or ptrace trap is scheduled.
 * %true अगर participated in group stop.
 */
अटल bool करो_संकेत_stop(पूर्णांक signr)
	__releases(&current->sighand->siglock)
अणु
	काष्ठा संकेत_काष्ठा *sig = current->संकेत;

	अगर (!(current->jobctl & JOBCTL_STOP_PENDING)) अणु
		अचिन्हित दीर्घ gstop = JOBCTL_STOP_PENDING | JOBCTL_STOP_CONSUME;
		काष्ठा task_काष्ठा *t;

		/* signr will be recorded in task->jobctl क्रम retries */
		WARN_ON_ONCE(signr & ~JOBCTL_STOP_SIGMASK);

		अगर (!likely(current->jobctl & JOBCTL_STOP_DEQUEUED) ||
		    unlikely(संकेत_group_निकास(sig)))
			वापस false;
		/*
		 * There is no group stop alपढ़ोy in progress.  We must
		 * initiate one now.
		 *
		 * While ptraced, a task may be resumed जबतक group stop is
		 * still in effect and then receive a stop संकेत and
		 * initiate another group stop.  This deviates from the
		 * usual behavior as two consecutive stop संकेतs can't
		 * cause two group stops when !ptraced.  That is why we
		 * also check !task_is_stopped(t) below.
		 *
		 * The condition can be distinguished by testing whether
		 * SIGNAL_STOP_STOPPED is alपढ़ोy set.  Don't generate
		 * group_निकास_code in such हाल.
		 *
		 * This is not necessary क्रम SIGNAL_STOP_CONTINUED because
		 * an पूर्णांकervening stop संकेत is required to cause two
		 * जारीd events regardless of ptrace.
		 */
		अगर (!(sig->flags & SIGNAL_STOP_STOPPED))
			sig->group_निकास_code = signr;

		sig->group_stop_count = 0;

		अगर (task_set_jobctl_pending(current, signr | gstop))
			sig->group_stop_count++;

		t = current;
		जबतक_each_thपढ़ो(current, t) अणु
			/*
			 * Setting state to TASK_STOPPED क्रम a group
			 * stop is always करोne with the siglock held,
			 * so this check has no races.
			 */
			अगर (!task_is_stopped(t) &&
			    task_set_jobctl_pending(t, signr | gstop)) अणु
				sig->group_stop_count++;
				अगर (likely(!(t->ptrace & PT_SEIZED)))
					संकेत_wake_up(t, 0);
				अन्यथा
					ptrace_trap_notअगरy(t);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (likely(!current->ptrace)) अणु
		पूर्णांक notअगरy = 0;

		/*
		 * If there are no other thपढ़ोs in the group, or अगर there
		 * is a group stop in progress and we are the last to stop,
		 * report to the parent.
		 */
		अगर (task_participate_group_stop(current))
			notअगरy = CLD_STOPPED;

		set_special_state(TASK_STOPPED);
		spin_unlock_irq(&current->sighand->siglock);

		/*
		 * Notअगरy the parent of the group stop completion.  Because
		 * we're not holding either the siglock or tasklist_lock
		 * here, ptracer may attach inbetween; however, this is क्रम
		 * group stop and should always be delivered to the real
		 * parent of the group leader.  The new ptracer will get
		 * its notअगरication when this task transitions पूर्णांकo
		 * TASK_TRACED.
		 */
		अगर (notअगरy) अणु
			पढ़ो_lock(&tasklist_lock);
			करो_notअगरy_parent_cldstop(current, false, notअगरy);
			पढ़ो_unlock(&tasklist_lock);
		पूर्ण

		/* Now we करोn't run again until woken by SIGCONT or SIGKILL */
		cgroup_enter_frozen();
		मुक्तzable_schedule();
		वापस true;
	पूर्ण अन्यथा अणु
		/*
		 * While ptraced, group stop is handled by STOP trap.
		 * Schedule it and let the caller deal with it.
		 */
		task_set_jobctl_pending(current, JOBCTL_TRAP_STOP);
		वापस false;
	पूर्ण
पूर्ण

/**
 * करो_jobctl_trap - take care of ptrace jobctl traps
 *
 * When PT_SEIZED, it's used क्रम both group stop and explicit
 * SEIZE/INTERRUPT traps.  Both generate PTRACE_EVENT_STOP trap with
 * accompanying siginfo.  If stopped, lower eight bits of निकास_code contain
 * the stop संकेत; otherwise, %SIGTRAP.
 *
 * When !PT_SEIZED, it's used only क्रम group stop trap with stop संकेत
 * number as निकास_code and no siginfo.
 *
 * CONTEXT:
 * Must be called with @current->sighand->siglock held, which may be
 * released and re-acquired beक्रमe वापसing with पूर्णांकervening sleep.
 */
अटल व्योम करो_jobctl_trap(व्योम)
अणु
	काष्ठा संकेत_काष्ठा *संकेत = current->संकेत;
	पूर्णांक signr = current->jobctl & JOBCTL_STOP_SIGMASK;

	अगर (current->ptrace & PT_SEIZED) अणु
		अगर (!संकेत->group_stop_count &&
		    !(संकेत->flags & SIGNAL_STOP_STOPPED))
			signr = SIGTRAP;
		WARN_ON_ONCE(!signr);
		ptrace_करो_notअगरy(signr, signr | (PTRACE_EVENT_STOP << 8),
				 CLD_STOPPED);
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(!signr);
		ptrace_stop(signr, CLD_STOPPED, 0, शून्य);
		current->निकास_code = 0;
	पूर्ण
पूर्ण

/**
 * करो_मुक्तzer_trap - handle the मुक्तzer jobctl trap
 *
 * Puts the task पूर्णांकo frozen state, अगर only the task is not about to quit.
 * In this हाल it drops JOBCTL_TRAP_FREEZE.
 *
 * CONTEXT:
 * Must be called with @current->sighand->siglock held,
 * which is always released beक्रमe वापसing.
 */
अटल व्योम करो_मुक्तzer_trap(व्योम)
	__releases(&current->sighand->siglock)
अणु
	/*
	 * If there are other trap bits pending except JOBCTL_TRAP_FREEZE,
	 * let's make another loop to give it a chance to be handled.
	 * In any हाल, we'll वापस back.
	 */
	अगर ((current->jobctl & (JOBCTL_PENDING_MASK | JOBCTL_TRAP_FREEZE)) !=
	     JOBCTL_TRAP_FREEZE) अणु
		spin_unlock_irq(&current->sighand->siglock);
		वापस;
	पूर्ण

	/*
	 * Now we're sure that there is no pending fatal संकेत and no
	 * pending traps. Clear TIF_SIGPENDING to not get out of schedule()
	 * immediately (अगर there is a non-fatal संकेत pending), and
	 * put the task पूर्णांकo sleep.
	 */
	__set_current_state(TASK_INTERRUPTIBLE);
	clear_thपढ़ो_flag(TIF_SIGPENDING);
	spin_unlock_irq(&current->sighand->siglock);
	cgroup_enter_frozen();
	मुक्तzable_schedule();
पूर्ण

अटल पूर्णांक ptrace_संकेत(पूर्णांक signr, kernel_siginfo_t *info)
अणु
	/*
	 * We करो not check sig_kernel_stop(signr) but set this marker
	 * unconditionally because we करो not know whether debugger will
	 * change signr. This flag has no meaning unless we are going
	 * to stop after वापस from ptrace_stop(). In this हाल it will
	 * be checked in करो_संकेत_stop(), we should only stop अगर it was
	 * not cleared by SIGCONT जबतक we were sleeping. See also the
	 * comment in dequeue_संकेत().
	 */
	current->jobctl |= JOBCTL_STOP_DEQUEUED;
	ptrace_stop(signr, CLD_TRAPPED, 0, info);

	/* We're back.  Did the debugger cancel the sig?  */
	signr = current->निकास_code;
	अगर (signr == 0)
		वापस signr;

	current->निकास_code = 0;

	/*
	 * Update the siginfo काष्ठाure अगर the संकेत has
	 * changed.  If the debugger wanted something
	 * specअगरic in the siginfo काष्ठाure then it should
	 * have updated *info via PTRACE_SETSIGINFO.
	 */
	अगर (signr != info->si_signo) अणु
		clear_siginfo(info);
		info->si_signo = signr;
		info->si_त्रुटि_सं = 0;
		info->si_code = SI_USER;
		rcu_पढ़ो_lock();
		info->si_pid = task_pid_vnr(current->parent);
		info->si_uid = from_kuid_munged(current_user_ns(),
						task_uid(current->parent));
		rcu_पढ़ो_unlock();
	पूर्ण

	/* If the (new) संकेत is now blocked, requeue it.  */
	अगर (sigismember(&current->blocked, signr)) अणु
		send_संकेत(signr, info, current, PIDTYPE_PID);
		signr = 0;
	पूर्ण

	वापस signr;
पूर्ण

अटल व्योम hide_si_addr_tag_bits(काष्ठा kसंकेत *ksig)
अणु
	चयन (siginfo_layout(ksig->sig, ksig->info.si_code)) अणु
	हाल SIL_FAULT:
	हाल SIL_FAULT_TRAPNO:
	हाल SIL_FAULT_MCEERR:
	हाल SIL_FAULT_BNDERR:
	हाल SIL_FAULT_PKUERR:
	हाल SIL_PERF_EVENT:
		ksig->info.si_addr = arch_untagged_si_addr(
			ksig->info.si_addr, ksig->sig, ksig->info.si_code);
		अवरोध;
	हाल SIL_KILL:
	हाल SIL_TIMER:
	हाल SIL_POLL:
	हाल SIL_CHLD:
	हाल SIL_RT:
	हाल SIL_SYS:
		अवरोध;
	पूर्ण
पूर्ण

bool get_संकेत(काष्ठा kसंकेत *ksig)
अणु
	काष्ठा sighand_काष्ठा *sighand = current->sighand;
	काष्ठा संकेत_काष्ठा *संकेत = current->संकेत;
	पूर्णांक signr;

	अगर (unlikely(current->task_works))
		task_work_run();

	/*
	 * For non-generic architectures, check क्रम TIF_NOTIFY_SIGNAL so
	 * that the arch handlers करोn't all have to करो it. If we get here
	 * without TIF_SIGPENDING, just निकास after running संकेत work.
	 */
	अगर (!IS_ENABLED(CONFIG_GENERIC_ENTRY)) अणु
		अगर (test_thपढ़ो_flag(TIF_NOTIFY_SIGNAL))
			tracehook_notअगरy_संकेत();
		अगर (!task_संक_बाकी(current))
			वापस false;
	पूर्ण

	अगर (unlikely(uprobe_deny_संकेत()))
		वापस false;

	/*
	 * Do this once, we can't वापस to user-mode अगर मुक्तzing() == T.
	 * करो_संकेत_stop() and ptrace_stop() करो मुक्तzable_schedule() and
	 * thus करो not need another check after वापस.
	 */
	try_to_मुक्तze();

relock:
	spin_lock_irq(&sighand->siglock);

	/*
	 * Every stopped thपढ़ो goes here after wakeup. Check to see अगर
	 * we should notअगरy the parent, prepare_संकेत(SIGCONT) encodes
	 * the CLD_ si_code पूर्णांकo SIGNAL_CLD_MASK bits.
	 */
	अगर (unlikely(संकेत->flags & SIGNAL_CLD_MASK)) अणु
		पूर्णांक why;

		अगर (संकेत->flags & SIGNAL_CLD_CONTINUED)
			why = CLD_CONTINUED;
		अन्यथा
			why = CLD_STOPPED;

		संकेत->flags &= ~SIGNAL_CLD_MASK;

		spin_unlock_irq(&sighand->siglock);

		/*
		 * Notअगरy the parent that we're continuing.  This event is
		 * always per-process and करोesn't make whole lot of sense
		 * क्रम ptracers, who shouldn't consume the state via
		 * रुको(2) either, but, क्रम backward compatibility, notअगरy
		 * the ptracer of the group leader too unless it's gonna be
		 * a duplicate.
		 */
		पढ़ो_lock(&tasklist_lock);
		करो_notअगरy_parent_cldstop(current, false, why);

		अगर (ptrace_reparented(current->group_leader))
			करो_notअगरy_parent_cldstop(current->group_leader,
						true, why);
		पढ़ो_unlock(&tasklist_lock);

		जाओ relock;
	पूर्ण

	/* Has this task alपढ़ोy been marked क्रम death? */
	अगर (संकेत_group_निकास(संकेत)) अणु
		ksig->info.si_signo = signr = SIGKILL;
		sigdअन्यथाt(&current->pending.संकेत, SIGKILL);
		trace_संकेत_deliver(SIGKILL, SEND_SIG_NOINFO,
				&sighand->action[SIGKILL - 1]);
		recalc_संक_बाकी();
		जाओ fatal;
	पूर्ण

	क्रम (;;) अणु
		काष्ठा k_sigaction *ka;

		अगर (unlikely(current->jobctl & JOBCTL_STOP_PENDING) &&
		    करो_संकेत_stop(0))
			जाओ relock;

		अगर (unlikely(current->jobctl &
			     (JOBCTL_TRAP_MASK | JOBCTL_TRAP_FREEZE))) अणु
			अगर (current->jobctl & JOBCTL_TRAP_MASK) अणु
				करो_jobctl_trap();
				spin_unlock_irq(&sighand->siglock);
			पूर्ण अन्यथा अगर (current->jobctl & JOBCTL_TRAP_FREEZE)
				करो_मुक्तzer_trap();

			जाओ relock;
		पूर्ण

		/*
		 * If the task is leaving the frozen state, let's update
		 * cgroup counters and reset the frozen bit.
		 */
		अगर (unlikely(cgroup_task_frozen(current))) अणु
			spin_unlock_irq(&sighand->siglock);
			cgroup_leave_frozen(false);
			जाओ relock;
		पूर्ण

		/*
		 * Signals generated by the execution of an inकाष्ठाion
		 * need to be delivered beक्रमe any other pending संकेतs
		 * so that the inकाष्ठाion poपूर्णांकer in the संकेत stack
		 * frame poपूर्णांकs to the faulting inकाष्ठाion.
		 */
		signr = dequeue_synchronous_संकेत(&ksig->info);
		अगर (!signr)
			signr = dequeue_संकेत(current, &current->blocked, &ksig->info);

		अगर (!signr)
			अवरोध; /* will वापस 0 */

		अगर (unlikely(current->ptrace) && signr != SIGKILL) अणु
			signr = ptrace_संकेत(signr, &ksig->info);
			अगर (!signr)
				जारी;
		पूर्ण

		ka = &sighand->action[signr-1];

		/* Trace actually delivered संकेतs. */
		trace_संकेत_deliver(signr, &ksig->info, ka);

		अगर (ka->sa.sa_handler == संक_छोड़ो) /* Do nothing.  */
			जारी;
		अगर (ka->sa.sa_handler != संक_पूर्व) अणु
			/* Run the handler.  */
			ksig->ka = *ka;

			अगर (ka->sa.sa_flags & SA_ONESHOT)
				ka->sa.sa_handler = संक_पूर्व;

			अवरोध; /* will वापस non-zero "signr" value */
		पूर्ण

		/*
		 * Now we are करोing the शेष action क्रम this संकेत.
		 */
		अगर (sig_kernel_ignore(signr)) /* Default is nothing. */
			जारी;

		/*
		 * Global init माला_लो no संकेतs it करोesn't want.
		 * Container-init माला_लो no संकेतs it करोesn't want from same
		 * container.
		 *
		 * Note that अगर global/container-init sees a sig_kernel_only()
		 * संकेत here, the संकेत must have been generated पूर्णांकernally
		 * or must have come from an ancestor namespace. In either
		 * हाल, the संकेत cannot be dropped.
		 */
		अगर (unlikely(संकेत->flags & SIGNAL_UNKILLABLE) &&
				!sig_kernel_only(signr))
			जारी;

		अगर (sig_kernel_stop(signr)) अणु
			/*
			 * The शेष action is to stop all thपढ़ोs in
			 * the thपढ़ो group.  The job control संकेतs
			 * करो nothing in an orphaned pgrp, but SIGSTOP
			 * always works.  Note that siglock needs to be
			 * dropped during the call to is_orphaned_pgrp()
			 * because of lock ordering with tasklist_lock.
			 * This allows an पूर्णांकervening SIGCONT to be posted.
			 * We need to check क्रम that and bail out अगर necessary.
			 */
			अगर (signr != SIGSTOP) अणु
				spin_unlock_irq(&sighand->siglock);

				/* संकेतs can be posted during this winकरोw */

				अगर (is_current_pgrp_orphaned())
					जाओ relock;

				spin_lock_irq(&sighand->siglock);
			पूर्ण

			अगर (likely(करो_संकेत_stop(ksig->info.si_signo))) अणु
				/* It released the siglock.  */
				जाओ relock;
			पूर्ण

			/*
			 * We didn't actually stop, due to a race
			 * with SIGCONT or something like that.
			 */
			जारी;
		पूर्ण

	fatal:
		spin_unlock_irq(&sighand->siglock);
		अगर (unlikely(cgroup_task_frozen(current)))
			cgroup_leave_frozen(true);

		/*
		 * Anything अन्यथा is fatal, maybe with a core dump.
		 */
		current->flags |= PF_SIGNALED;

		अगर (sig_kernel_coredump(signr)) अणु
			अगर (prपूर्णांक_fatal_संकेतs)
				prपूर्णांक_fatal_संकेत(ksig->info.si_signo);
			proc_coredump_connector(current);
			/*
			 * If it was able to dump core, this समाप्तs all
			 * other thपढ़ोs in the group and synchronizes with
			 * their demise.  If we lost the race with another
			 * thपढ़ो getting here, it set group_निकास_code
			 * first and our करो_group_निकास call below will use
			 * that value and ignore the one we pass it.
			 */
			करो_coredump(&ksig->info);
		पूर्ण

		/*
		 * PF_IO_WORKER thपढ़ोs will catch and निकास on fatal संकेतs
		 * themselves. They have cleanup that must be perक्रमmed, so
		 * we cannot call करो_निकास() on their behalf.
		 */
		अगर (current->flags & PF_IO_WORKER)
			जाओ out;

		/*
		 * Death संकेतs, no core dump.
		 */
		करो_group_निकास(ksig->info.si_signo);
		/* NOTREACHED */
	पूर्ण
	spin_unlock_irq(&sighand->siglock);
out:
	ksig->sig = signr;

	अगर (!(ksig->ka.sa.sa_flags & SA_EXPOSE_TAGBITS))
		hide_si_addr_tag_bits(ksig);

	वापस ksig->sig > 0;
पूर्ण

/**
 * संकेत_delivered - 
 * @ksig:		kernel संकेत काष्ठा
 * @stepping:		nonzero अगर debugger single-step or block-step in use
 *
 * This function should be called when a संकेत has successfully been
 * delivered. It updates the blocked संकेतs accordingly (@ksig->ka.sa.sa_mask
 * is always blocked, and the संकेत itself is blocked unless %SA_NODEFER
 * is set in @ksig->ka.sa.sa_flags.  Tracing is notअगरied.
 */
अटल व्योम संकेत_delivered(काष्ठा kसंकेत *ksig, पूर्णांक stepping)
अणु
	sigset_t blocked;

	/* A संकेत was successfully delivered, and the
	   saved sigmask was stored on the संकेत frame,
	   and will be restored by sigवापस.  So we can
	   simply clear the restore sigmask flag.  */
	clear_restore_sigmask();

	sigorsets(&blocked, &current->blocked, &ksig->ka.sa.sa_mask);
	अगर (!(ksig->ka.sa.sa_flags & SA_NODEFER))
		sigaddset(&blocked, ksig->sig);
	set_current_blocked(&blocked);
	tracehook_संकेत_handler(stepping);
पूर्ण

व्योम संकेत_setup_करोne(पूर्णांक failed, काष्ठा kसंकेत *ksig, पूर्णांक stepping)
अणु
	अगर (failed)
		क्रमce_sigsegv(ksig->sig);
	अन्यथा
		संकेत_delivered(ksig, stepping);
पूर्ण

/*
 * It could be that complete_संकेत() picked us to notअगरy about the
 * group-wide संकेत. Other thपढ़ोs should be notअगरied now to take
 * the shared संकेतs in @which since we will not.
 */
अटल व्योम retarget_shared_pending(काष्ठा task_काष्ठा *tsk, sigset_t *which)
अणु
	sigset_t retarget;
	काष्ठा task_काष्ठा *t;

	sigandsets(&retarget, &tsk->संकेत->shared_pending.संकेत, which);
	अगर (sigisemptyset(&retarget))
		वापस;

	t = tsk;
	जबतक_each_thपढ़ो(tsk, t) अणु
		अगर (t->flags & PF_EXITING)
			जारी;

		अगर (!has_pending_संकेतs(&retarget, &t->blocked))
			जारी;
		/* Remove the संकेतs this thपढ़ो can handle. */
		sigandsets(&retarget, &retarget, &t->blocked);

		अगर (!task_संक_बाकी(t))
			संकेत_wake_up(t, 0);

		अगर (sigisemptyset(&retarget))
			अवरोध;
	पूर्ण
पूर्ण

व्योम निकास_संकेतs(काष्ठा task_काष्ठा *tsk)
अणु
	पूर्णांक group_stop = 0;
	sigset_t unblocked;

	/*
	 * @tsk is about to have PF_EXITING set - lock out users which
	 * expect stable thपढ़ोgroup.
	 */
	cgroup_thपढ़ोgroup_change_begin(tsk);

	अगर (thपढ़ो_group_empty(tsk) || संकेत_group_निकास(tsk->संकेत)) अणु
		tsk->flags |= PF_EXITING;
		cgroup_thपढ़ोgroup_change_end(tsk);
		वापस;
	पूर्ण

	spin_lock_irq(&tsk->sighand->siglock);
	/*
	 * From now this task is not visible क्रम group-wide संकेतs,
	 * see wants_संकेत(), करो_संकेत_stop().
	 */
	tsk->flags |= PF_EXITING;

	cgroup_thपढ़ोgroup_change_end(tsk);

	अगर (!task_संक_बाकी(tsk))
		जाओ out;

	unblocked = tsk->blocked;
	signotset(&unblocked);
	retarget_shared_pending(tsk, &unblocked);

	अगर (unlikely(tsk->jobctl & JOBCTL_STOP_PENDING) &&
	    task_participate_group_stop(tsk))
		group_stop = CLD_STOPPED;
out:
	spin_unlock_irq(&tsk->sighand->siglock);

	/*
	 * If group stop has completed, deliver the notअगरication.  This
	 * should always go to the real parent of the group leader.
	 */
	अगर (unlikely(group_stop)) अणु
		पढ़ो_lock(&tasklist_lock);
		करो_notअगरy_parent_cldstop(tsk, false, group_stop);
		पढ़ो_unlock(&tasklist_lock);
	पूर्ण
पूर्ण

/*
 * System call entry poपूर्णांकs.
 */

/**
 *  sys_restart_syscall - restart a प्रणाली call
 */
SYSCALL_DEFINE0(restart_syscall)
अणु
	काष्ठा restart_block *restart = &current->restart_block;
	वापस restart->fn(restart);
पूर्ण

दीर्घ करो_no_restart_syscall(काष्ठा restart_block *param)
अणु
	वापस -EINTR;
पूर्ण

अटल व्योम __set_task_blocked(काष्ठा task_काष्ठा *tsk, स्थिर sigset_t *newset)
अणु
	अगर (task_संक_बाकी(tsk) && !thपढ़ो_group_empty(tsk)) अणु
		sigset_t newblocked;
		/* A set of now blocked but previously unblocked संकेतs. */
		sigandnsets(&newblocked, newset, &current->blocked);
		retarget_shared_pending(tsk, &newblocked);
	पूर्ण
	tsk->blocked = *newset;
	recalc_संक_बाकी();
पूर्ण

/**
 * set_current_blocked - change current->blocked mask
 * @newset: new mask
 *
 * It is wrong to change ->blocked directly, this helper should be used
 * to ensure the process can't miss a shared संकेत we are going to block.
 */
व्योम set_current_blocked(sigset_t *newset)
अणु
	sigdअन्यथापंचांगask(newset, sigmask(SIGKILL) | sigmask(SIGSTOP));
	__set_current_blocked(newset);
पूर्ण

व्योम __set_current_blocked(स्थिर sigset_t *newset)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	/*
	 * In हाल the संकेत mask hasn't changed, there is nothing we need
	 * to करो. The current->blocked shouldn't be modअगरied by other task.
	 */
	अगर (sigequalsets(&tsk->blocked, newset))
		वापस;

	spin_lock_irq(&tsk->sighand->siglock);
	__set_task_blocked(tsk, newset);
	spin_unlock_irq(&tsk->sighand->siglock);
पूर्ण

/*
 * This is also useful क्रम kernel thपढ़ोs that want to temporarily
 * (or permanently) block certain संकेतs.
 *
 * NOTE! Unlike the user-mode sys_sigprocmask(), the kernel
 * पूर्णांकerface happily blocks "unblockable" संकेतs like SIGKILL
 * and मित्रs.
 */
पूर्णांक sigprocmask(पूर्णांक how, sigset_t *set, sigset_t *oldset)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	sigset_t newset;

	/* Lockless, only current can change ->blocked, never from irq */
	अगर (oldset)
		*oldset = tsk->blocked;

	चयन (how) अणु
	हाल SIG_BLOCK:
		sigorsets(&newset, &tsk->blocked, set);
		अवरोध;
	हाल SIG_UNBLOCK:
		sigandnsets(&newset, &tsk->blocked, set);
		अवरोध;
	हाल SIG_SETMASK:
		newset = *set;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	__set_current_blocked(&newset);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(sigprocmask);

/*
 * The api helps set app-provided sigmasks.
 *
 * This is useful क्रम syscalls such as ppoll, pselect, io_pgetevents and
 * epoll_pरुको where a new sigmask is passed from userland क्रम the syscalls.
 *
 * Note that it करोes set_restore_sigmask() in advance, so it must be always
 * paired with restore_saved_sigmask_unless() beक्रमe वापस from syscall.
 */
पूर्णांक set_user_sigmask(स्थिर sigset_t __user *umask, माप_प्रकार sigsetsize)
अणु
	sigset_t kmask;

	अगर (!umask)
		वापस 0;
	अगर (sigsetsize != माप(sigset_t))
		वापस -EINVAL;
	अगर (copy_from_user(&kmask, umask, माप(sigset_t)))
		वापस -EFAULT;

	set_restore_sigmask();
	current->saved_sigmask = current->blocked;
	set_current_blocked(&kmask);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
पूर्णांक set_compat_user_sigmask(स्थिर compat_sigset_t __user *umask,
			    माप_प्रकार sigsetsize)
अणु
	sigset_t kmask;

	अगर (!umask)
		वापस 0;
	अगर (sigsetsize != माप(compat_sigset_t))
		वापस -EINVAL;
	अगर (get_compat_sigset(&kmask, umask))
		वापस -EFAULT;

	set_restore_sigmask();
	current->saved_sigmask = current->blocked;
	set_current_blocked(&kmask);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/**
 *  sys_rt_sigprocmask - change the list of currently blocked संकेतs
 *  @how: whether to add, हटाओ, or set संकेतs
 *  @nset: stores pending संकेतs
 *  @oset: previous value of संकेत mask अगर non-null
 *  @sigsetsize: size of sigset_t type
 */
SYSCALL_DEFINE4(rt_sigprocmask, पूर्णांक, how, sigset_t __user *, nset,
		sigset_t __user *, oset, माप_प्रकार, sigsetsize)
अणु
	sigset_t old_set, new_set;
	पूर्णांक error;

	/* XXX: Don't preclude handling different sized sigset_t's.  */
	अगर (sigsetsize != माप(sigset_t))
		वापस -EINVAL;

	old_set = current->blocked;

	अगर (nset) अणु
		अगर (copy_from_user(&new_set, nset, माप(sigset_t)))
			वापस -EFAULT;
		sigdअन्यथापंचांगask(&new_set, sigmask(SIGKILL)|sigmask(SIGSTOP));

		error = sigprocmask(how, &new_set, शून्य);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (oset) अणु
		अगर (copy_to_user(oset, &old_set, माप(sigset_t)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE4(rt_sigprocmask, पूर्णांक, how, compat_sigset_t __user *, nset,
		compat_sigset_t __user *, oset, compat_माप_प्रकार, sigsetsize)
अणु
	sigset_t old_set = current->blocked;

	/* XXX: Don't preclude handling different sized sigset_t's.  */
	अगर (sigsetsize != माप(sigset_t))
		वापस -EINVAL;

	अगर (nset) अणु
		sigset_t new_set;
		पूर्णांक error;
		अगर (get_compat_sigset(&new_set, nset))
			वापस -EFAULT;
		sigdअन्यथापंचांगask(&new_set, sigmask(SIGKILL)|sigmask(SIGSTOP));

		error = sigprocmask(how, &new_set, शून्य);
		अगर (error)
			वापस error;
	पूर्ण
	वापस oset ? put_compat_sigset(oset, &old_set, माप(*oset)) : 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम करो_संक_बाकी(sigset_t *set)
अणु
	spin_lock_irq(&current->sighand->siglock);
	sigorsets(set, &current->pending.संकेत,
		  &current->संकेत->shared_pending.संकेत);
	spin_unlock_irq(&current->sighand->siglock);

	/* Outside the lock because only this thपढ़ो touches it.  */
	sigandsets(set, &current->blocked, set);
पूर्ण

/**
 *  sys_rt_संक_बाकी - examine a pending संकेत that has been उठाओd
 *			जबतक blocked
 *  @uset: stores pending संकेतs
 *  @sigsetsize: size of sigset_t type or larger
 */
SYSCALL_DEFINE2(rt_संक_बाकी, sigset_t __user *, uset, माप_प्रकार, sigsetsize)
अणु
	sigset_t set;

	अगर (sigsetsize > माप(*uset))
		वापस -EINVAL;

	करो_संक_बाकी(&set);

	अगर (copy_to_user(uset, &set, sigsetsize))
		वापस -EFAULT;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE2(rt_संक_बाकी, compat_sigset_t __user *, uset,
		compat_माप_प्रकार, sigsetsize)
अणु
	sigset_t set;

	अगर (sigsetsize > माप(*uset))
		वापस -EINVAL;

	करो_संक_बाकी(&set);

	वापस put_compat_sigset(uset, &set, sigsetsize);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा अणु
	अचिन्हित अक्षर limit, layout;
पूर्ण sig_sicodes[] = अणु
	[संक_अवैध]  = अणु Nसंक_अवैध,  SIL_FAULT पूर्ण,
	[संक_भ_त्रुटि]  = अणु Nसंक_भ_त्रुटि,  SIL_FAULT पूर्ण,
	[संक_अंश] = अणु Nसंक_अंश, SIL_FAULT पूर्ण,
	[SIGBUS]  = अणु NSIGBUS,  SIL_FAULT पूर्ण,
	[SIGTRAP] = अणु NSIGTRAP, SIL_FAULT पूर्ण,
#अगर defined(SIGEMT)
	[SIGEMT]  = अणु NSIGEMT,  SIL_FAULT पूर्ण,
#पूर्ण_अगर
	[SIGCHLD] = अणु NSIGCHLD, SIL_CHLD पूर्ण,
	[SIGPOLL] = अणु NSIGPOLL, SIL_POLL पूर्ण,
	[SIGSYS]  = अणु NSIGSYS,  SIL_SYS पूर्ण,
पूर्ण;

अटल bool known_siginfo_layout(अचिन्हित sig, पूर्णांक si_code)
अणु
	अगर (si_code == SI_KERNEL)
		वापस true;
	अन्यथा अगर ((si_code > SI_USER)) अणु
		अगर (sig_specअगरic_sicodes(sig)) अणु
			अगर (si_code <= sig_sicodes[sig].limit)
				वापस true;
		पूर्ण
		अन्यथा अगर (si_code <= NSIGPOLL)
			वापस true;
	पूर्ण
	अन्यथा अगर (si_code >= SI_DETHREAD)
		वापस true;
	अन्यथा अगर (si_code == SI_ASYNCNL)
		वापस true;
	वापस false;
पूर्ण

क्रमागत siginfo_layout siginfo_layout(अचिन्हित sig, पूर्णांक si_code)
अणु
	क्रमागत siginfo_layout layout = SIL_KILL;
	अगर ((si_code > SI_USER) && (si_code < SI_KERNEL)) अणु
		अगर ((sig < ARRAY_SIZE(sig_sicodes)) &&
		    (si_code <= sig_sicodes[sig].limit)) अणु
			layout = sig_sicodes[sig].layout;
			/* Handle the exceptions */
			अगर ((sig == SIGBUS) &&
			    (si_code >= BUS_MCEERR_AR) && (si_code <= BUS_MCEERR_AO))
				layout = SIL_FAULT_MCEERR;
			अन्यथा अगर ((sig == संक_अंश) && (si_code == SEGV_BNDERR))
				layout = SIL_FAULT_BNDERR;
#अगर_घोषित SEGV_PKUERR
			अन्यथा अगर ((sig == संक_अंश) && (si_code == SEGV_PKUERR))
				layout = SIL_FAULT_PKUERR;
#पूर्ण_अगर
			अन्यथा अगर ((sig == SIGTRAP) && (si_code == TRAP_PERF))
				layout = SIL_PERF_EVENT;
#अगर_घोषित __ARCH_SI_TRAPNO
			अन्यथा अगर (layout == SIL_FAULT)
				layout = SIL_FAULT_TRAPNO;
#पूर्ण_अगर
		पूर्ण
		अन्यथा अगर (si_code <= NSIGPOLL)
			layout = SIL_POLL;
	पूर्ण अन्यथा अणु
		अगर (si_code == SI_TIMER)
			layout = SIL_TIMER;
		अन्यथा अगर (si_code == SI_SIGIO)
			layout = SIL_POLL;
		अन्यथा अगर (si_code < 0)
			layout = SIL_RT;
	पूर्ण
	वापस layout;
पूर्ण

अटल अंतरभूत अक्षर __user *si_expansion(स्थिर siginfo_t __user *info)
अणु
	वापस ((अक्षर __user *)info) + माप(काष्ठा kernel_siginfo);
पूर्ण

पूर्णांक copy_siginfo_to_user(siginfo_t __user *to, स्थिर kernel_siginfo_t *from)
अणु
	अक्षर __user *expansion = si_expansion(to);
	अगर (copy_to_user(to, from , माप(काष्ठा kernel_siginfo)))
		वापस -EFAULT;
	अगर (clear_user(expansion, SI_EXPANSION_SIZE))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक post_copy_siginfo_from_user(kernel_siginfo_t *info,
				       स्थिर siginfo_t __user *from)
अणु
	अगर (unlikely(!known_siginfo_layout(info->si_signo, info->si_code))) अणु
		अक्षर __user *expansion = si_expansion(from);
		अक्षर buf[SI_EXPANSION_SIZE];
		पूर्णांक i;
		/*
		 * An unknown si_code might need more than
		 * माप(काष्ठा kernel_siginfo) bytes.  Verअगरy all of the
		 * extra bytes are 0.  This guarantees copy_siginfo_to_user
		 * will वापस this data to userspace exactly.
		 */
		अगर (copy_from_user(&buf, expansion, SI_EXPANSION_SIZE))
			वापस -EFAULT;
		क्रम (i = 0; i < SI_EXPANSION_SIZE; i++) अणु
			अगर (buf[i] != 0)
				वापस -E2BIG;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __copy_siginfo_from_user(पूर्णांक signo, kernel_siginfo_t *to,
				    स्थिर siginfo_t __user *from)
अणु
	अगर (copy_from_user(to, from, माप(काष्ठा kernel_siginfo)))
		वापस -EFAULT;
	to->si_signo = signo;
	वापस post_copy_siginfo_from_user(to, from);
पूर्ण

पूर्णांक copy_siginfo_from_user(kernel_siginfo_t *to, स्थिर siginfo_t __user *from)
अणु
	अगर (copy_from_user(to, from, माप(काष्ठा kernel_siginfo)))
		वापस -EFAULT;
	वापस post_copy_siginfo_from_user(to, from);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
/**
 * copy_siginfo_to_बाह्यal32 - copy a kernel siginfo पूर्णांकo a compat user siginfo
 * @to: compat siginfo destination
 * @from: kernel siginfo source
 *
 * Note: This function करोes not work properly क्रम the SIGCHLD on x32, but
 * क्रमtunately it करोesn't have to.  The only valid callers क्रम this function are
 * copy_siginfo_to_user32, which is overriden क्रम x32 and the coredump code.
 * The latter करोes not care because SIGCHLD will never cause a coredump.
 */
व्योम copy_siginfo_to_बाह्यal32(काष्ठा compat_siginfo *to,
		स्थिर काष्ठा kernel_siginfo *from)
अणु
	स_रखो(to, 0, माप(*to));

	to->si_signo = from->si_signo;
	to->si_त्रुटि_सं = from->si_त्रुटि_सं;
	to->si_code  = from->si_code;
	चयन(siginfo_layout(from->si_signo, from->si_code)) अणु
	हाल SIL_KILL:
		to->si_pid = from->si_pid;
		to->si_uid = from->si_uid;
		अवरोध;
	हाल SIL_TIMER:
		to->si_tid     = from->si_tid;
		to->si_overrun = from->si_overrun;
		to->si_पूर्णांक     = from->si_पूर्णांक;
		अवरोध;
	हाल SIL_POLL:
		to->si_band = from->si_band;
		to->si_fd   = from->si_fd;
		अवरोध;
	हाल SIL_FAULT:
		to->si_addr = ptr_to_compat(from->si_addr);
		अवरोध;
	हाल SIL_FAULT_TRAPNO:
		to->si_addr = ptr_to_compat(from->si_addr);
		to->si_trapno = from->si_trapno;
		अवरोध;
	हाल SIL_FAULT_MCEERR:
		to->si_addr = ptr_to_compat(from->si_addr);
		to->si_addr_lsb = from->si_addr_lsb;
		अवरोध;
	हाल SIL_FAULT_BNDERR:
		to->si_addr = ptr_to_compat(from->si_addr);
		to->si_lower = ptr_to_compat(from->si_lower);
		to->si_upper = ptr_to_compat(from->si_upper);
		अवरोध;
	हाल SIL_FAULT_PKUERR:
		to->si_addr = ptr_to_compat(from->si_addr);
		to->si_pkey = from->si_pkey;
		अवरोध;
	हाल SIL_PERF_EVENT:
		to->si_addr = ptr_to_compat(from->si_addr);
		to->si_perf_data = from->si_perf_data;
		to->si_perf_type = from->si_perf_type;
		अवरोध;
	हाल SIL_CHLD:
		to->si_pid = from->si_pid;
		to->si_uid = from->si_uid;
		to->si_status = from->si_status;
		to->si_uसमय = from->si_uसमय;
		to->si_sसमय = from->si_sसमय;
		अवरोध;
	हाल SIL_RT:
		to->si_pid = from->si_pid;
		to->si_uid = from->si_uid;
		to->si_पूर्णांक = from->si_पूर्णांक;
		अवरोध;
	हाल SIL_SYS:
		to->si_call_addr = ptr_to_compat(from->si_call_addr);
		to->si_syscall   = from->si_syscall;
		to->si_arch      = from->si_arch;
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक __copy_siginfo_to_user32(काष्ठा compat_siginfo __user *to,
			   स्थिर काष्ठा kernel_siginfo *from)
अणु
	काष्ठा compat_siginfo new;

	copy_siginfo_to_बाह्यal32(&new, from);
	अगर (copy_to_user(to, &new, माप(काष्ठा compat_siginfo)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक post_copy_siginfo_from_user32(kernel_siginfo_t *to,
					 स्थिर काष्ठा compat_siginfo *from)
अणु
	clear_siginfo(to);
	to->si_signo = from->si_signo;
	to->si_त्रुटि_सं = from->si_त्रुटि_सं;
	to->si_code  = from->si_code;
	चयन(siginfo_layout(from->si_signo, from->si_code)) अणु
	हाल SIL_KILL:
		to->si_pid = from->si_pid;
		to->si_uid = from->si_uid;
		अवरोध;
	हाल SIL_TIMER:
		to->si_tid     = from->si_tid;
		to->si_overrun = from->si_overrun;
		to->si_पूर्णांक     = from->si_पूर्णांक;
		अवरोध;
	हाल SIL_POLL:
		to->si_band = from->si_band;
		to->si_fd   = from->si_fd;
		अवरोध;
	हाल SIL_FAULT:
		to->si_addr = compat_ptr(from->si_addr);
		अवरोध;
	हाल SIL_FAULT_TRAPNO:
		to->si_addr = compat_ptr(from->si_addr);
		to->si_trapno = from->si_trapno;
		अवरोध;
	हाल SIL_FAULT_MCEERR:
		to->si_addr = compat_ptr(from->si_addr);
		to->si_addr_lsb = from->si_addr_lsb;
		अवरोध;
	हाल SIL_FAULT_BNDERR:
		to->si_addr = compat_ptr(from->si_addr);
		to->si_lower = compat_ptr(from->si_lower);
		to->si_upper = compat_ptr(from->si_upper);
		अवरोध;
	हाल SIL_FAULT_PKUERR:
		to->si_addr = compat_ptr(from->si_addr);
		to->si_pkey = from->si_pkey;
		अवरोध;
	हाल SIL_PERF_EVENT:
		to->si_addr = compat_ptr(from->si_addr);
		to->si_perf_data = from->si_perf_data;
		to->si_perf_type = from->si_perf_type;
		अवरोध;
	हाल SIL_CHLD:
		to->si_pid    = from->si_pid;
		to->si_uid    = from->si_uid;
		to->si_status = from->si_status;
#अगर_घोषित CONFIG_X86_X32_ABI
		अगर (in_x32_syscall()) अणु
			to->si_uसमय = from->_sअगरields._sigchld_x32._uसमय;
			to->si_sसमय = from->_sअगरields._sigchld_x32._sसमय;
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			to->si_uसमय = from->si_uसमय;
			to->si_sसमय = from->si_sसमय;
		पूर्ण
		अवरोध;
	हाल SIL_RT:
		to->si_pid = from->si_pid;
		to->si_uid = from->si_uid;
		to->si_पूर्णांक = from->si_पूर्णांक;
		अवरोध;
	हाल SIL_SYS:
		to->si_call_addr = compat_ptr(from->si_call_addr);
		to->si_syscall   = from->si_syscall;
		to->si_arch      = from->si_arch;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __copy_siginfo_from_user32(पूर्णांक signo, काष्ठा kernel_siginfo *to,
				      स्थिर काष्ठा compat_siginfo __user *ufrom)
अणु
	काष्ठा compat_siginfo from;

	अगर (copy_from_user(&from, ufrom, माप(काष्ठा compat_siginfo)))
		वापस -EFAULT;

	from.si_signo = signo;
	वापस post_copy_siginfo_from_user32(to, &from);
पूर्ण

पूर्णांक copy_siginfo_from_user32(काष्ठा kernel_siginfo *to,
			     स्थिर काष्ठा compat_siginfo __user *ufrom)
अणु
	काष्ठा compat_siginfo from;

	अगर (copy_from_user(&from, ufrom, माप(काष्ठा compat_siginfo)))
		वापस -EFAULT;

	वापस post_copy_siginfo_from_user32(to, &from);
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

/**
 *  करो_sigसमयdरुको - रुको क्रम queued संकेतs specअगरied in @which
 *  @which: queued संकेतs to रुको क्रम
 *  @info: अगर non-null, the संकेत's siginfo is वापसed here
 *  @ts: upper bound on process समय suspension
 */
अटल पूर्णांक करो_sigसमयdरुको(स्थिर sigset_t *which, kernel_siginfo_t *info,
		    स्थिर काष्ठा बारpec64 *ts)
अणु
	kसमय_प्रकार *to = शून्य, समयout = KTIME_MAX;
	काष्ठा task_काष्ठा *tsk = current;
	sigset_t mask = *which;
	पूर्णांक sig, ret = 0;

	अगर (ts) अणु
		अगर (!बारpec64_valid(ts))
			वापस -EINVAL;
		समयout = बारpec64_to_kसमय(*ts);
		to = &समयout;
	पूर्ण

	/*
	 * Invert the set of allowed संकेतs to get those we want to block.
	 */
	sigdअन्यथापंचांगask(&mask, sigmask(SIGKILL) | sigmask(SIGSTOP));
	signotset(&mask);

	spin_lock_irq(&tsk->sighand->siglock);
	sig = dequeue_संकेत(tsk, &mask, info);
	अगर (!sig && समयout) अणु
		/*
		 * None पढ़ोy, temporarily unblock those we're पूर्णांकerested
		 * जबतक we are sleeping in so that we'll be awakened when
		 * they arrive. Unblocking is always fine, we can aव्योम
		 * set_current_blocked().
		 */
		tsk->real_blocked = tsk->blocked;
		sigandsets(&tsk->blocked, &tsk->blocked, &mask);
		recalc_संक_बाकी();
		spin_unlock_irq(&tsk->sighand->siglock);

		__set_current_state(TASK_INTERRUPTIBLE);
		ret = मुक्तzable_schedule_hrसमयout_range(to, tsk->समयr_slack_ns,
							 HRTIMER_MODE_REL);
		spin_lock_irq(&tsk->sighand->siglock);
		__set_task_blocked(tsk, &tsk->real_blocked);
		sigemptyset(&tsk->real_blocked);
		sig = dequeue_संकेत(tsk, &mask, info);
	पूर्ण
	spin_unlock_irq(&tsk->sighand->siglock);

	अगर (sig)
		वापस sig;
	वापस ret ? -EINTR : -EAGAIN;
पूर्ण

/**
 *  sys_rt_sigसमयdरुको - synchronously रुको क्रम queued संकेतs specअगरied
 *			in @uthese
 *  @uthese: queued संकेतs to रुको क्रम
 *  @uinfo: अगर non-null, the संकेत's siginfo is वापसed here
 *  @uts: upper bound on process समय suspension
 *  @sigsetsize: size of sigset_t type
 */
SYSCALL_DEFINE4(rt_sigसमयdरुको, स्थिर sigset_t __user *, uthese,
		siginfo_t __user *, uinfo,
		स्थिर काष्ठा __kernel_बारpec __user *, uts,
		माप_प्रकार, sigsetsize)
अणु
	sigset_t these;
	काष्ठा बारpec64 ts;
	kernel_siginfo_t info;
	पूर्णांक ret;

	/* XXX: Don't preclude handling different sized sigset_t's.  */
	अगर (sigsetsize != माप(sigset_t))
		वापस -EINVAL;

	अगर (copy_from_user(&these, uthese, माप(these)))
		वापस -EFAULT;

	अगर (uts) अणु
		अगर (get_बारpec64(&ts, uts))
			वापस -EFAULT;
	पूर्ण

	ret = करो_sigसमयdरुको(&these, &info, uts ? &ts : शून्य);

	अगर (ret > 0 && uinfo) अणु
		अगर (copy_siginfo_to_user(uinfo, &info))
			ret = -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
SYSCALL_DEFINE4(rt_sigसमयdरुको_समय32, स्थिर sigset_t __user *, uthese,
		siginfo_t __user *, uinfo,
		स्थिर काष्ठा old_बारpec32 __user *, uts,
		माप_प्रकार, sigsetsize)
अणु
	sigset_t these;
	काष्ठा बारpec64 ts;
	kernel_siginfo_t info;
	पूर्णांक ret;

	अगर (sigsetsize != माप(sigset_t))
		वापस -EINVAL;

	अगर (copy_from_user(&these, uthese, माप(these)))
		वापस -EFAULT;

	अगर (uts) अणु
		अगर (get_old_बारpec32(&ts, uts))
			वापस -EFAULT;
	पूर्ण

	ret = करो_sigसमयdरुको(&these, &info, uts ? &ts : शून्य);

	अगर (ret > 0 && uinfo) अणु
		अगर (copy_siginfo_to_user(uinfo, &info))
			ret = -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE4(rt_sigसमयdरुको_समय64, compat_sigset_t __user *, uthese,
		काष्ठा compat_siginfo __user *, uinfo,
		काष्ठा __kernel_बारpec __user *, uts, compat_माप_प्रकार, sigsetsize)
अणु
	sigset_t s;
	काष्ठा बारpec64 t;
	kernel_siginfo_t info;
	दीर्घ ret;

	अगर (sigsetsize != माप(sigset_t))
		वापस -EINVAL;

	अगर (get_compat_sigset(&s, uthese))
		वापस -EFAULT;

	अगर (uts) अणु
		अगर (get_बारpec64(&t, uts))
			वापस -EFAULT;
	पूर्ण

	ret = करो_sigसमयdरुको(&s, &info, uts ? &t : शून्य);

	अगर (ret > 0 && uinfo) अणु
		अगर (copy_siginfo_to_user32(uinfo, &info))
			ret = -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
COMPAT_SYSCALL_DEFINE4(rt_sigसमयdरुको_समय32, compat_sigset_t __user *, uthese,
		काष्ठा compat_siginfo __user *, uinfo,
		काष्ठा old_बारpec32 __user *, uts, compat_माप_प्रकार, sigsetsize)
अणु
	sigset_t s;
	काष्ठा बारpec64 t;
	kernel_siginfo_t info;
	दीर्घ ret;

	अगर (sigsetsize != माप(sigset_t))
		वापस -EINVAL;

	अगर (get_compat_sigset(&s, uthese))
		वापस -EFAULT;

	अगर (uts) अणु
		अगर (get_old_बारpec32(&t, uts))
			वापस -EFAULT;
	पूर्ण

	ret = करो_sigसमयdरुको(&s, &info, uts ? &t : शून्य);

	अगर (ret > 0 && uinfo) अणु
		अगर (copy_siginfo_to_user32(uinfo, &info))
			ret = -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

अटल अंतरभूत व्योम prepare_समाप्त_siginfo(पूर्णांक sig, काष्ठा kernel_siginfo *info)
अणु
	clear_siginfo(info);
	info->si_signo = sig;
	info->si_त्रुटि_सं = 0;
	info->si_code = SI_USER;
	info->si_pid = task_tgid_vnr(current);
	info->si_uid = from_kuid_munged(current_user_ns(), current_uid());
पूर्ण

/**
 *  sys_समाप्त - send a संकेत to a process
 *  @pid: the PID of the process
 *  @sig: संकेत to be sent
 */
SYSCALL_DEFINE2(समाप्त, pid_t, pid, पूर्णांक, sig)
अणु
	काष्ठा kernel_siginfo info;

	prepare_समाप्त_siginfo(sig, &info);

	वापस समाप्त_something_info(sig, &info, pid);
पूर्ण

/*
 * Verअगरy that the संकेतer and संकेतee either are in the same pid namespace
 * or that the संकेतer's pid namespace is an ancestor of the signalee's pid
 * namespace.
 */
अटल bool access_pidfd_pidns(काष्ठा pid *pid)
अणु
	काष्ठा pid_namespace *active = task_active_pid_ns(current);
	काष्ठा pid_namespace *p = ns_of_pid(pid);

	क्रम (;;) अणु
		अगर (!p)
			वापस false;
		अगर (p == active)
			अवरोध;
		p = p->parent;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक copy_siginfo_from_user_any(kernel_siginfo_t *kinfo,
		siginfo_t __user *info)
अणु
#अगर_घोषित CONFIG_COMPAT
	/*
	 * Aव्योम hooking up compat syscalls and instead handle necessary
	 * conversions here. Note, this is a stop-gap measure and should not be
	 * considered a generic solution.
	 */
	अगर (in_compat_syscall())
		वापस copy_siginfo_from_user32(
			kinfo, (काष्ठा compat_siginfo __user *)info);
#पूर्ण_अगर
	वापस copy_siginfo_from_user(kinfo, info);
पूर्ण

अटल काष्ठा pid *pidfd_to_pid(स्थिर काष्ठा file *file)
अणु
	काष्ठा pid *pid;

	pid = pidfd_pid(file);
	अगर (!IS_ERR(pid))
		वापस pid;

	वापस tgid_pidfd_to_pid(file);
पूर्ण

/**
 * sys_pidfd_send_संकेत - Signal a process through a pidfd
 * @pidfd:  file descriptor of the process
 * @sig:    संकेत to send
 * @info:   संकेत info
 * @flags:  future flags
 *
 * The syscall currently only संकेतs via PIDTYPE_PID which covers
 * समाप्त(<positive-pid>, <संकेत>. It करोes not संकेत thपढ़ोs or process
 * groups.
 * In order to extend the syscall to thपढ़ोs and process groups the @flags
 * argument should be used. In essence, the @flags argument will determine
 * what is संकेतed and not the file descriptor itself. Put in other words,
 * grouping is a property of the flags argument not a property of the file
 * descriptor.
 *
 * Return: 0 on success, negative त्रुटि_सं on failure
 */
SYSCALL_DEFINE4(pidfd_send_संकेत, पूर्णांक, pidfd, पूर्णांक, sig,
		siginfo_t __user *, info, अचिन्हित पूर्णांक, flags)
अणु
	पूर्णांक ret;
	काष्ठा fd f;
	काष्ठा pid *pid;
	kernel_siginfo_t kinfo;

	/* Enक्रमce flags be set to 0 until we add an extension. */
	अगर (flags)
		वापस -EINVAL;

	f = fdget(pidfd);
	अगर (!f.file)
		वापस -EBADF;

	/* Is this a pidfd? */
	pid = pidfd_to_pid(f.file);
	अगर (IS_ERR(pid)) अणु
		ret = PTR_ERR(pid);
		जाओ err;
	पूर्ण

	ret = -EINVAL;
	अगर (!access_pidfd_pidns(pid))
		जाओ err;

	अगर (info) अणु
		ret = copy_siginfo_from_user_any(&kinfo, info);
		अगर (unlikely(ret))
			जाओ err;

		ret = -EINVAL;
		अगर (unlikely(sig != kinfo.si_signo))
			जाओ err;

		/* Only allow sending arbitrary संकेतs to yourself. */
		ret = -EPERM;
		अगर ((task_pid(current) != pid) &&
		    (kinfo.si_code >= 0 || kinfo.si_code == SI_TKILL))
			जाओ err;
	पूर्ण अन्यथा अणु
		prepare_समाप्त_siginfo(sig, &kinfo);
	पूर्ण

	ret = समाप्त_pid_info(sig, &kinfo, pid);

err:
	fdput(f);
	वापस ret;
पूर्ण

अटल पूर्णांक
करो_send_specअगरic(pid_t tgid, pid_t pid, पूर्णांक sig, काष्ठा kernel_siginfo *info)
अणु
	काष्ठा task_काष्ठा *p;
	पूर्णांक error = -ESRCH;

	rcu_पढ़ो_lock();
	p = find_task_by_vpid(pid);
	अगर (p && (tgid <= 0 || task_tgid_vnr(p) == tgid)) अणु
		error = check_समाप्त_permission(sig, info, p);
		/*
		 * The null संकेत is a permissions and process existence
		 * probe.  No संकेत is actually delivered.
		 */
		अगर (!error && sig) अणु
			error = करो_send_sig_info(sig, info, p, PIDTYPE_PID);
			/*
			 * If lock_task_sighand() failed we pretend the task
			 * dies after receiving the संकेत. The winकरोw is tiny,
			 * and the संकेत is निजी anyway.
			 */
			अगर (unlikely(error == -ESRCH))
				error = 0;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस error;
पूर्ण

अटल पूर्णांक करो_tसमाप्त(pid_t tgid, pid_t pid, पूर्णांक sig)
अणु
	काष्ठा kernel_siginfo info;

	clear_siginfo(&info);
	info.si_signo = sig;
	info.si_त्रुटि_सं = 0;
	info.si_code = SI_TKILL;
	info.si_pid = task_tgid_vnr(current);
	info.si_uid = from_kuid_munged(current_user_ns(), current_uid());

	वापस करो_send_specअगरic(tgid, pid, sig, &info);
पूर्ण

/**
 *  sys_tgसमाप्त - send संकेत to one specअगरic thपढ़ो
 *  @tgid: the thपढ़ो group ID of the thपढ़ो
 *  @pid: the PID of the thपढ़ो
 *  @sig: संकेत to be sent
 *
 *  This syscall also checks the @tgid and वापसs -ESRCH even अगर the PID
 *  exists but it's not beदीर्घing to the target process anymore. This
 *  method solves the problem of thपढ़ोs निकासing and PIDs getting reused.
 */
SYSCALL_DEFINE3(tgसमाप्त, pid_t, tgid, pid_t, pid, पूर्णांक, sig)
अणु
	/* This is only valid क्रम single tasks */
	अगर (pid <= 0 || tgid <= 0)
		वापस -EINVAL;

	वापस करो_tसमाप्त(tgid, pid, sig);
पूर्ण

/**
 *  sys_tसमाप्त - send संकेत to one specअगरic task
 *  @pid: the PID of the task
 *  @sig: संकेत to be sent
 *
 *  Send a संकेत to only one task, even अगर it's a CLONE_THREAD task.
 */
SYSCALL_DEFINE2(tसमाप्त, pid_t, pid, पूर्णांक, sig)
अणु
	/* This is only valid क्रम single tasks */
	अगर (pid <= 0)
		वापस -EINVAL;

	वापस करो_tसमाप्त(0, pid, sig);
पूर्ण

अटल पूर्णांक करो_rt_sigqueueinfo(pid_t pid, पूर्णांक sig, kernel_siginfo_t *info)
अणु
	/* Not even root can pretend to send संकेतs from the kernel.
	 * Nor can they impersonate a समाप्त()/tgसमाप्त(), which adds source info.
	 */
	अगर ((info->si_code >= 0 || info->si_code == SI_TKILL) &&
	    (task_pid_vnr(current) != pid))
		वापस -EPERM;

	/* POSIX.1b करोesn't mention process groups.  */
	वापस समाप्त_proc_info(sig, info, pid);
पूर्ण

/**
 *  sys_rt_sigqueueinfo - send संकेत inक्रमmation to a संकेत
 *  @pid: the PID of the thपढ़ो
 *  @sig: संकेत to be sent
 *  @uinfo: संकेत info to be sent
 */
SYSCALL_DEFINE3(rt_sigqueueinfo, pid_t, pid, पूर्णांक, sig,
		siginfo_t __user *, uinfo)
अणु
	kernel_siginfo_t info;
	पूर्णांक ret = __copy_siginfo_from_user(sig, &info, uinfo);
	अगर (unlikely(ret))
		वापस ret;
	वापस करो_rt_sigqueueinfo(pid, sig, &info);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE3(rt_sigqueueinfo,
			compat_pid_t, pid,
			पूर्णांक, sig,
			काष्ठा compat_siginfo __user *, uinfo)
अणु
	kernel_siginfo_t info;
	पूर्णांक ret = __copy_siginfo_from_user32(sig, &info, uinfo);
	अगर (unlikely(ret))
		वापस ret;
	वापस करो_rt_sigqueueinfo(pid, sig, &info);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक करो_rt_tgsigqueueinfo(pid_t tgid, pid_t pid, पूर्णांक sig, kernel_siginfo_t *info)
अणु
	/* This is only valid क्रम single tasks */
	अगर (pid <= 0 || tgid <= 0)
		वापस -EINVAL;

	/* Not even root can pretend to send संकेतs from the kernel.
	 * Nor can they impersonate a समाप्त()/tgसमाप्त(), which adds source info.
	 */
	अगर ((info->si_code >= 0 || info->si_code == SI_TKILL) &&
	    (task_pid_vnr(current) != pid))
		वापस -EPERM;

	वापस करो_send_specअगरic(tgid, pid, sig, info);
पूर्ण

SYSCALL_DEFINE4(rt_tgsigqueueinfo, pid_t, tgid, pid_t, pid, पूर्णांक, sig,
		siginfo_t __user *, uinfo)
अणु
	kernel_siginfo_t info;
	पूर्णांक ret = __copy_siginfo_from_user(sig, &info, uinfo);
	अगर (unlikely(ret))
		वापस ret;
	वापस करो_rt_tgsigqueueinfo(tgid, pid, sig, &info);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE4(rt_tgsigqueueinfo,
			compat_pid_t, tgid,
			compat_pid_t, pid,
			पूर्णांक, sig,
			काष्ठा compat_siginfo __user *, uinfo)
अणु
	kernel_siginfo_t info;
	पूर्णांक ret = __copy_siginfo_from_user32(sig, &info, uinfo);
	अगर (unlikely(ret))
		वापस ret;
	वापस करो_rt_tgsigqueueinfo(tgid, pid, sig, &info);
पूर्ण
#पूर्ण_अगर

/*
 * For kthपढ़ोs only, must not be used अगर cloned with CLONE_SIGHAND
 */
व्योम kernel_sigaction(पूर्णांक sig, __sighandler_t action)
अणु
	spin_lock_irq(&current->sighand->siglock);
	current->sighand->action[sig - 1].sa.sa_handler = action;
	अगर (action == संक_छोड़ो) अणु
		sigset_t mask;

		sigemptyset(&mask);
		sigaddset(&mask, sig);

		flush_sigqueue_mask(&mask, &current->संकेत->shared_pending);
		flush_sigqueue_mask(&mask, &current->pending);
		recalc_संक_बाकी();
	पूर्ण
	spin_unlock_irq(&current->sighand->siglock);
पूर्ण
EXPORT_SYMBOL(kernel_sigaction);

व्योम __weak sigaction_compat_abi(काष्ठा k_sigaction *act,
		काष्ठा k_sigaction *oact)
अणु
पूर्ण

पूर्णांक करो_sigaction(पूर्णांक sig, काष्ठा k_sigaction *act, काष्ठा k_sigaction *oact)
अणु
	काष्ठा task_काष्ठा *p = current, *t;
	काष्ठा k_sigaction *k;
	sigset_t mask;

	अगर (!valid_संकेत(sig) || sig < 1 || (act && sig_kernel_only(sig)))
		वापस -EINVAL;

	k = &p->sighand->action[sig-1];

	spin_lock_irq(&p->sighand->siglock);
	अगर (oact)
		*oact = *k;

	/*
	 * Make sure that we never accidentally claim to support SA_UNSUPPORTED,
	 * e.g. by having an architecture use the bit in their uapi.
	 */
	BUILD_BUG_ON(UAPI_SA_FLAGS & SA_UNSUPPORTED);

	/*
	 * Clear unknown flag bits in order to allow userspace to detect missing
	 * support क्रम flag bits and to allow the kernel to use non-uapi bits
	 * पूर्णांकernally.
	 */
	अगर (act)
		act->sa.sa_flags &= UAPI_SA_FLAGS;
	अगर (oact)
		oact->sa.sa_flags &= UAPI_SA_FLAGS;

	sigaction_compat_abi(act, oact);

	अगर (act) अणु
		sigdअन्यथापंचांगask(&act->sa.sa_mask,
			      sigmask(SIGKILL) | sigmask(SIGSTOP));
		*k = *act;
		/*
		 * POSIX 3.3.1.3:
		 *  "Setting a संकेत action to संक_छोड़ो क्रम a संकेत that is
		 *   pending shall cause the pending संकेत to be discarded,
		 *   whether or not it is blocked."
		 *
		 *  "Setting a संकेत action to संक_पूर्व क्रम a संकेत that is
		 *   pending and whose शेष action is to ignore the संकेत
		 *   (क्रम example, SIGCHLD), shall cause the pending संकेत to
		 *   be discarded, whether or not it is blocked"
		 */
		अगर (sig_handler_ignored(sig_handler(p, sig), sig)) अणु
			sigemptyset(&mask);
			sigaddset(&mask, sig);
			flush_sigqueue_mask(&mask, &p->संकेत->shared_pending);
			क्रम_each_thपढ़ो(p, t)
				flush_sigqueue_mask(&mask, &t->pending);
		पूर्ण
	पूर्ण

	spin_unlock_irq(&p->sighand->siglock);
	वापस 0;
पूर्ण

अटल पूर्णांक
करो_sigaltstack (स्थिर stack_t *ss, stack_t *oss, अचिन्हित दीर्घ sp,
		माप_प्रकार min_ss_size)
अणु
	काष्ठा task_काष्ठा *t = current;

	अगर (oss) अणु
		स_रखो(oss, 0, माप(stack_t));
		oss->ss_sp = (व्योम __user *) t->sas_ss_sp;
		oss->ss_size = t->sas_ss_size;
		oss->ss_flags = sas_ss_flags(sp) |
			(current->sas_ss_flags & SS_FLAG_BITS);
	पूर्ण

	अगर (ss) अणु
		व्योम __user *ss_sp = ss->ss_sp;
		माप_प्रकार ss_size = ss->ss_size;
		अचिन्हित ss_flags = ss->ss_flags;
		पूर्णांक ss_mode;

		अगर (unlikely(on_sig_stack(sp)))
			वापस -EPERM;

		ss_mode = ss_flags & ~SS_FLAG_BITS;
		अगर (unlikely(ss_mode != SS_DISABLE && ss_mode != SS_ONSTACK &&
				ss_mode != 0))
			वापस -EINVAL;

		अगर (ss_mode == SS_DISABLE) अणु
			ss_size = 0;
			ss_sp = शून्य;
		पूर्ण अन्यथा अणु
			अगर (unlikely(ss_size < min_ss_size))
				वापस -ENOMEM;
		पूर्ण

		t->sas_ss_sp = (अचिन्हित दीर्घ) ss_sp;
		t->sas_ss_size = ss_size;
		t->sas_ss_flags = ss_flags;
	पूर्ण
	वापस 0;
पूर्ण

SYSCALL_DEFINE2(sigaltstack,स्थिर stack_t __user *,uss, stack_t __user *,uoss)
अणु
	stack_t new, old;
	पूर्णांक err;
	अगर (uss && copy_from_user(&new, uss, माप(stack_t)))
		वापस -EFAULT;
	err = करो_sigaltstack(uss ? &new : शून्य, uoss ? &old : शून्य,
			      current_user_stack_poपूर्णांकer(),
			      MINSIGSTKSZ);
	अगर (!err && uoss && copy_to_user(uoss, &old, माप(stack_t)))
		err = -EFAULT;
	वापस err;
पूर्ण

पूर्णांक restore_altstack(स्थिर stack_t __user *uss)
अणु
	stack_t new;
	अगर (copy_from_user(&new, uss, माप(stack_t)))
		वापस -EFAULT;
	(व्योम)करो_sigaltstack(&new, शून्य, current_user_stack_poपूर्णांकer(),
			     MINSIGSTKSZ);
	/* squash all but EFAULT क्रम now */
	वापस 0;
पूर्ण

पूर्णांक __save_altstack(stack_t __user *uss, अचिन्हित दीर्घ sp)
अणु
	काष्ठा task_काष्ठा *t = current;
	पूर्णांक err = __put_user((व्योम __user *)t->sas_ss_sp, &uss->ss_sp) |
		__put_user(t->sas_ss_flags, &uss->ss_flags) |
		__put_user(t->sas_ss_size, &uss->ss_size);
	अगर (err)
		वापस err;
	अगर (t->sas_ss_flags & SS_AUTODISARM)
		sas_ss_reset(t);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक करो_compat_sigaltstack(स्थिर compat_stack_t __user *uss_ptr,
				 compat_stack_t __user *uoss_ptr)
अणु
	stack_t uss, uoss;
	पूर्णांक ret;

	अगर (uss_ptr) अणु
		compat_stack_t uss32;
		अगर (copy_from_user(&uss32, uss_ptr, माप(compat_stack_t)))
			वापस -EFAULT;
		uss.ss_sp = compat_ptr(uss32.ss_sp);
		uss.ss_flags = uss32.ss_flags;
		uss.ss_size = uss32.ss_size;
	पूर्ण
	ret = करो_sigaltstack(uss_ptr ? &uss : शून्य, &uoss,
			     compat_user_stack_poपूर्णांकer(),
			     COMPAT_MINSIGSTKSZ);
	अगर (ret >= 0 && uoss_ptr)  अणु
		compat_stack_t old;
		स_रखो(&old, 0, माप(old));
		old.ss_sp = ptr_to_compat(uoss.ss_sp);
		old.ss_flags = uoss.ss_flags;
		old.ss_size = uoss.ss_size;
		अगर (copy_to_user(uoss_ptr, &old, माप(compat_stack_t)))
			ret = -EFAULT;
	पूर्ण
	वापस ret;
पूर्ण

COMPAT_SYSCALL_DEFINE2(sigaltstack,
			स्थिर compat_stack_t __user *, uss_ptr,
			compat_stack_t __user *, uoss_ptr)
अणु
	वापस करो_compat_sigaltstack(uss_ptr, uoss_ptr);
पूर्ण

पूर्णांक compat_restore_altstack(स्थिर compat_stack_t __user *uss)
अणु
	पूर्णांक err = करो_compat_sigaltstack(uss, शून्य);
	/* squash all but -EFAULT क्रम now */
	वापस err == -EFAULT ? err : 0;
पूर्ण

पूर्णांक __compat_save_altstack(compat_stack_t __user *uss, अचिन्हित दीर्घ sp)
अणु
	पूर्णांक err;
	काष्ठा task_काष्ठा *t = current;
	err = __put_user(ptr_to_compat((व्योम __user *)t->sas_ss_sp),
			 &uss->ss_sp) |
		__put_user(t->sas_ss_flags, &uss->ss_flags) |
		__put_user(t->sas_ss_size, &uss->ss_size);
	अगर (err)
		वापस err;
	अगर (t->sas_ss_flags & SS_AUTODISARM)
		sas_ss_reset(t);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित __ARCH_WANT_SYS_SIGPENDING

/**
 *  sys_संक_बाकी - examine pending संकेतs
 *  @uset: where mask of pending संकेत is वापसed
 */
SYSCALL_DEFINE1(संक_बाकी, old_sigset_t __user *, uset)
अणु
	sigset_t set;

	अगर (माप(old_sigset_t) > माप(*uset))
		वापस -EINVAL;

	करो_संक_बाकी(&set);

	अगर (copy_to_user(uset, &set, माप(old_sigset_t)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE1(संक_बाकी, compat_old_sigset_t __user *, set32)
अणु
	sigset_t set;

	करो_संक_बाकी(&set);

	वापस put_user(set.sig[0], set32);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर

#अगर_घोषित __ARCH_WANT_SYS_SIGPROCMASK
/**
 *  sys_sigprocmask - examine and change blocked संकेतs
 *  @how: whether to add, हटाओ, or set संकेतs
 *  @nset: संकेतs to add or हटाओ (अगर non-null)
 *  @oset: previous value of संकेत mask अगर non-null
 *
 * Some platक्रमms have their own version with special arguments;
 * others support only sys_rt_sigprocmask.
 */

SYSCALL_DEFINE3(sigprocmask, पूर्णांक, how, old_sigset_t __user *, nset,
		old_sigset_t __user *, oset)
अणु
	old_sigset_t old_set, new_set;
	sigset_t new_blocked;

	old_set = current->blocked.sig[0];

	अगर (nset) अणु
		अगर (copy_from_user(&new_set, nset, माप(*nset)))
			वापस -EFAULT;

		new_blocked = current->blocked;

		चयन (how) अणु
		हाल SIG_BLOCK:
			sigaddseपंचांगask(&new_blocked, new_set);
			अवरोध;
		हाल SIG_UNBLOCK:
			sigdअन्यथापंचांगask(&new_blocked, new_set);
			अवरोध;
		हाल SIG_SETMASK:
			new_blocked.sig[0] = new_set;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		set_current_blocked(&new_blocked);
	पूर्ण

	अगर (oset) अणु
		अगर (copy_to_user(oset, &old_set, माप(*oset)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* __ARCH_WANT_SYS_SIGPROCMASK */

#अगर_अघोषित CONFIG_ODD_RT_SIGACTION
/**
 *  sys_rt_sigaction - alter an action taken by a process
 *  @sig: संकेत to be sent
 *  @act: new sigaction
 *  @oact: used to save the previous sigaction
 *  @sigsetsize: size of sigset_t type
 */
SYSCALL_DEFINE4(rt_sigaction, पूर्णांक, sig,
		स्थिर काष्ठा sigaction __user *, act,
		काष्ठा sigaction __user *, oact,
		माप_प्रकार, sigsetsize)
अणु
	काष्ठा k_sigaction new_sa, old_sa;
	पूर्णांक ret;

	/* XXX: Don't preclude handling different sized sigset_t's.  */
	अगर (sigsetsize != माप(sigset_t))
		वापस -EINVAL;

	अगर (act && copy_from_user(&new_sa.sa, act, माप(new_sa.sa)))
		वापस -EFAULT;

	ret = करो_sigaction(sig, act ? &new_sa : शून्य, oact ? &old_sa : शून्य);
	अगर (ret)
		वापस ret;

	अगर (oact && copy_to_user(oact, &old_sa.sa, माप(old_sa.sa)))
		वापस -EFAULT;

	वापस 0;
पूर्ण
#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE4(rt_sigaction, पूर्णांक, sig,
		स्थिर काष्ठा compat_sigaction __user *, act,
		काष्ठा compat_sigaction __user *, oact,
		compat_माप_प्रकार, sigsetsize)
अणु
	काष्ठा k_sigaction new_ka, old_ka;
#अगर_घोषित __ARCH_HAS_SA_RESTORER
	compat_uptr_t restorer;
#पूर्ण_अगर
	पूर्णांक ret;

	/* XXX: Don't preclude handling different sized sigset_t's.  */
	अगर (sigsetsize != माप(compat_sigset_t))
		वापस -EINVAL;

	अगर (act) अणु
		compat_uptr_t handler;
		ret = get_user(handler, &act->sa_handler);
		new_ka.sa.sa_handler = compat_ptr(handler);
#अगर_घोषित __ARCH_HAS_SA_RESTORER
		ret |= get_user(restorer, &act->sa_restorer);
		new_ka.sa.sa_restorer = compat_ptr(restorer);
#पूर्ण_अगर
		ret |= get_compat_sigset(&new_ka.sa.sa_mask, &act->sa_mask);
		ret |= get_user(new_ka.sa.sa_flags, &act->sa_flags);
		अगर (ret)
			वापस -EFAULT;
	पूर्ण

	ret = करो_sigaction(sig, act ? &new_ka : शून्य, oact ? &old_ka : शून्य);
	अगर (!ret && oact) अणु
		ret = put_user(ptr_to_compat(old_ka.sa.sa_handler), 
			       &oact->sa_handler);
		ret |= put_compat_sigset(&oact->sa_mask, &old_ka.sa.sa_mask,
					 माप(oact->sa_mask));
		ret |= put_user(old_ka.sa.sa_flags, &oact->sa_flags);
#अगर_घोषित __ARCH_HAS_SA_RESTORER
		ret |= put_user(ptr_to_compat(old_ka.sa.sa_restorer),
				&oact->sa_restorer);
#पूर्ण_अगर
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* !CONFIG_ODD_RT_SIGACTION */

#अगर_घोषित CONFIG_OLD_SIGACTION
SYSCALL_DEFINE3(sigaction, पूर्णांक, sig,
		स्थिर काष्ठा old_sigaction __user *, act,
	        काष्ठा old_sigaction __user *, oact)
अणु
	काष्ठा k_sigaction new_ka, old_ka;
	पूर्णांक ret;

	अगर (act) अणु
		old_sigset_t mask;
		अगर (!access_ok(act, माप(*act)) ||
		    __get_user(new_ka.sa.sa_handler, &act->sa_handler) ||
		    __get_user(new_ka.sa.sa_restorer, &act->sa_restorer) ||
		    __get_user(new_ka.sa.sa_flags, &act->sa_flags) ||
		    __get_user(mask, &act->sa_mask))
			वापस -EFAULT;
#अगर_घोषित __ARCH_HAS_KA_RESTORER
		new_ka.ka_restorer = शून्य;
#पूर्ण_अगर
		siginitset(&new_ka.sa.sa_mask, mask);
	पूर्ण

	ret = करो_sigaction(sig, act ? &new_ka : शून्य, oact ? &old_ka : शून्य);

	अगर (!ret && oact) अणु
		अगर (!access_ok(oact, माप(*oact)) ||
		    __put_user(old_ka.sa.sa_handler, &oact->sa_handler) ||
		    __put_user(old_ka.sa.sa_restorer, &oact->sa_restorer) ||
		    __put_user(old_ka.sa.sa_flags, &oact->sa_flags) ||
		    __put_user(old_ka.sa.sa_mask.sig[0], &oact->sa_mask))
			वापस -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_COMPAT_OLD_SIGACTION
COMPAT_SYSCALL_DEFINE3(sigaction, पूर्णांक, sig,
		स्थिर काष्ठा compat_old_sigaction __user *, act,
	        काष्ठा compat_old_sigaction __user *, oact)
अणु
	काष्ठा k_sigaction new_ka, old_ka;
	पूर्णांक ret;
	compat_old_sigset_t mask;
	compat_uptr_t handler, restorer;

	अगर (act) अणु
		अगर (!access_ok(act, माप(*act)) ||
		    __get_user(handler, &act->sa_handler) ||
		    __get_user(restorer, &act->sa_restorer) ||
		    __get_user(new_ka.sa.sa_flags, &act->sa_flags) ||
		    __get_user(mask, &act->sa_mask))
			वापस -EFAULT;

#अगर_घोषित __ARCH_HAS_KA_RESTORER
		new_ka.ka_restorer = शून्य;
#पूर्ण_अगर
		new_ka.sa.sa_handler = compat_ptr(handler);
		new_ka.sa.sa_restorer = compat_ptr(restorer);
		siginitset(&new_ka.sa.sa_mask, mask);
	पूर्ण

	ret = करो_sigaction(sig, act ? &new_ka : शून्य, oact ? &old_ka : शून्य);

	अगर (!ret && oact) अणु
		अगर (!access_ok(oact, माप(*oact)) ||
		    __put_user(ptr_to_compat(old_ka.sa.sa_handler),
			       &oact->sa_handler) ||
		    __put_user(ptr_to_compat(old_ka.sa.sa_restorer),
			       &oact->sa_restorer) ||
		    __put_user(old_ka.sa.sa_flags, &oact->sa_flags) ||
		    __put_user(old_ka.sa.sa_mask.sig[0], &oact->sa_mask))
			वापस -EFAULT;
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SGETMASK_SYSCALL

/*
 * For backwards compatibility.  Functionality superseded by sigprocmask.
 */
SYSCALL_DEFINE0(sgeपंचांगask)
अणु
	/* SMP safe */
	वापस current->blocked.sig[0];
पूर्ण

SYSCALL_DEFINE1(sseपंचांगask, पूर्णांक, newmask)
अणु
	पूर्णांक old = current->blocked.sig[0];
	sigset_t newset;

	siginitset(&newset, newmask);
	set_current_blocked(&newset);

	वापस old;
पूर्ण
#पूर्ण_अगर /* CONFIG_SGETMASK_SYSCALL */

#अगर_घोषित __ARCH_WANT_SYS_SIGNAL
/*
 * For backwards compatibility.  Functionality superseded by sigaction.
 */
SYSCALL_DEFINE2(संकेत, पूर्णांक, sig, __sighandler_t, handler)
अणु
	काष्ठा k_sigaction new_sa, old_sa;
	पूर्णांक ret;

	new_sa.sa.sa_handler = handler;
	new_sa.sa.sa_flags = SA_ONESHOT | SA_NOMASK;
	sigemptyset(&new_sa.sa.sa_mask);

	ret = करो_sigaction(sig, &new_sa, &old_sa);

	वापस ret ? ret : (अचिन्हित दीर्घ)old_sa.sa.sa_handler;
पूर्ण
#पूर्ण_अगर /* __ARCH_WANT_SYS_SIGNAL */

#अगर_घोषित __ARCH_WANT_SYS_PAUSE

SYSCALL_DEFINE0(छोड़ो)
अणु
	जबतक (!संकेत_pending(current)) अणु
		__set_current_state(TASK_INTERRUPTIBLE);
		schedule();
	पूर्ण
	वापस -ERESTARTNOHAND;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक संक_रोको(sigset_t *set)
अणु
	current->saved_sigmask = current->blocked;
	set_current_blocked(set);

	जबतक (!संकेत_pending(current)) अणु
		__set_current_state(TASK_INTERRUPTIBLE);
		schedule();
	पूर्ण
	set_restore_sigmask();
	वापस -ERESTARTNOHAND;
पूर्ण

/**
 *  sys_rt_संक_रोको - replace the संकेत mask क्रम a value with the
 *	@unewset value until a संकेत is received
 *  @unewset: new संकेत mask value
 *  @sigsetsize: size of sigset_t type
 */
SYSCALL_DEFINE2(rt_संक_रोको, sigset_t __user *, unewset, माप_प्रकार, sigsetsize)
अणु
	sigset_t newset;

	/* XXX: Don't preclude handling different sized sigset_t's.  */
	अगर (sigsetsize != माप(sigset_t))
		वापस -EINVAL;

	अगर (copy_from_user(&newset, unewset, माप(newset)))
		वापस -EFAULT;
	वापस संक_रोको(&newset);
पूर्ण
 
#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE2(rt_संक_रोको, compat_sigset_t __user *, unewset, compat_माप_प्रकार, sigsetsize)
अणु
	sigset_t newset;

	/* XXX: Don't preclude handling different sized sigset_t's.  */
	अगर (sigsetsize != माप(sigset_t))
		वापस -EINVAL;

	अगर (get_compat_sigset(&newset, unewset))
		वापस -EFAULT;
	वापस संक_रोको(&newset);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_OLD_SIGSUSPEND
SYSCALL_DEFINE1(संक_रोको, old_sigset_t, mask)
अणु
	sigset_t blocked;
	siginitset(&blocked, mask);
	वापस संक_रोको(&blocked);
पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_OLD_SIGSUSPEND3
SYSCALL_DEFINE3(संक_रोको, पूर्णांक, unused1, पूर्णांक, unused2, old_sigset_t, mask)
अणु
	sigset_t blocked;
	siginitset(&blocked, mask);
	वापस संक_रोको(&blocked);
पूर्ण
#पूर्ण_अगर

__weak स्थिर अक्षर *arch_vma_name(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम siginfo_buildसमय_checks(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा siginfo) != SI_MAX_SIZE);

	/* Verअगरy the offsets in the two siginfos match */
#घोषणा CHECK_OFFSET(field) \
	BUILD_BUG_ON(दुरत्व(siginfo_t, field) != दुरत्व(kernel_siginfo_t, field))

	/* समाप्त */
	CHECK_OFFSET(si_pid);
	CHECK_OFFSET(si_uid);

	/* समयr */
	CHECK_OFFSET(si_tid);
	CHECK_OFFSET(si_overrun);
	CHECK_OFFSET(si_value);

	/* rt */
	CHECK_OFFSET(si_pid);
	CHECK_OFFSET(si_uid);
	CHECK_OFFSET(si_value);

	/* sigchld */
	CHECK_OFFSET(si_pid);
	CHECK_OFFSET(si_uid);
	CHECK_OFFSET(si_status);
	CHECK_OFFSET(si_uसमय);
	CHECK_OFFSET(si_sसमय);

	/* sigfault */
	CHECK_OFFSET(si_addr);
	CHECK_OFFSET(si_trapno);
	CHECK_OFFSET(si_addr_lsb);
	CHECK_OFFSET(si_lower);
	CHECK_OFFSET(si_upper);
	CHECK_OFFSET(si_pkey);
	CHECK_OFFSET(si_perf_data);
	CHECK_OFFSET(si_perf_type);

	/* sigpoll */
	CHECK_OFFSET(si_band);
	CHECK_OFFSET(si_fd);

	/* sigsys */
	CHECK_OFFSET(si_call_addr);
	CHECK_OFFSET(si_syscall);
	CHECK_OFFSET(si_arch);
#अघोषित CHECK_OFFSET

	/* usb asyncio */
	BUILD_BUG_ON(दुरत्व(काष्ठा siginfo, si_pid) !=
		     दुरत्व(काष्ठा siginfo, si_addr));
	अगर (माप(पूर्णांक) == माप(व्योम __user *)) अणु
		BUILD_BUG_ON(माप_field(काष्ठा siginfo, si_pid) !=
			     माप(व्योम __user *));
	पूर्ण अन्यथा अणु
		BUILD_BUG_ON((माप_field(काष्ठा siginfo, si_pid) +
			      माप_field(काष्ठा siginfo, si_uid)) !=
			     माप(व्योम __user *));
		BUILD_BUG_ON(दुरत्वend(काष्ठा siginfo, si_pid) !=
			     दुरत्व(काष्ठा siginfo, si_uid));
	पूर्ण
#अगर_घोषित CONFIG_COMPAT
	BUILD_BUG_ON(दुरत्व(काष्ठा compat_siginfo, si_pid) !=
		     दुरत्व(काष्ठा compat_siginfo, si_addr));
	BUILD_BUG_ON(माप_field(काष्ठा compat_siginfo, si_pid) !=
		     माप(compat_uptr_t));
	BUILD_BUG_ON(माप_field(काष्ठा compat_siginfo, si_pid) !=
		     माप_field(काष्ठा siginfo, si_pid));
#पूर्ण_अगर
पूर्ण

व्योम __init संकेतs_init(व्योम)
अणु
	siginfo_buildसमय_checks();

	sigqueue_cachep = KMEM_CACHE(sigqueue, SLAB_PANIC);
पूर्ण

#अगर_घोषित CONFIG_KGDB_KDB
#समावेश <linux/kdb.h>
/*
 * kdb_send_sig - Allows kdb to send संकेतs without exposing
 * संकेत पूर्णांकernals.  This function checks अगर the required locks are
 * available beक्रमe calling the मुख्य संकेत code, to aव्योम kdb
 * deadlocks.
 */
व्योम kdb_send_sig(काष्ठा task_काष्ठा *t, पूर्णांक sig)
अणु
	अटल काष्ठा task_काष्ठा *kdb_prev_t;
	पूर्णांक new_t, ret;
	अगर (!spin_trylock(&t->sighand->siglock)) अणु
		kdb_म_लिखो("Can't do kill command now.\n"
			   "The sigmask lock is held somewhere else in "
			   "kernel, try again later\n");
		वापस;
	पूर्ण
	new_t = kdb_prev_t != t;
	kdb_prev_t = t;
	अगर (t->state != TASK_RUNNING && new_t) अणु
		spin_unlock(&t->sighand->siglock);
		kdb_म_लिखो("Process is not RUNNING, sending a signal from "
			   "kdb risks deadlock\n"
			   "on the run queue locks. "
			   "The signal has _not_ been sent.\n"
			   "Reissue the kill command if you want to risk "
			   "the deadlock.\n");
		वापस;
	पूर्ण
	ret = send_संकेत(sig, SEND_SIG_PRIV, t, PIDTYPE_PID);
	spin_unlock(&t->sighand->siglock);
	अगर (ret)
		kdb_म_लिखो("Fail to deliver Signal %d to process %d.\n",
			   sig, t->pid);
	अन्यथा
		kdb_म_लिखो("Signal %d is sent to process %d.\n", sig, t->pid);
पूर्ण
#पूर्ण_अगर	/* CONFIG_KGDB_KDB */
