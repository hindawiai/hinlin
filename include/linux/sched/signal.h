<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_SIGNAL_H
#घोषणा _LINUX_SCHED_SIGNAL_H

#समावेश <linux/rculist.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/jobctl.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/cred.h>
#समावेश <linux/refcount.h>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/mm_types.h>
#समावेश <यंत्र/ptrace.h>

/*
 * Types defining task->संकेत and task->sighand and APIs using them:
 */

काष्ठा sighand_काष्ठा अणु
	spinlock_t		siglock;
	refcount_t		count;
	रुको_queue_head_t	संकेतfd_wqh;
	काष्ठा k_sigaction	action[_NSIG];
पूर्ण;

/*
 * Per-process accounting stats:
 */
काष्ठा pacct_काष्ठा अणु
	पूर्णांक			ac_flag;
	दीर्घ			ac_निकासcode;
	अचिन्हित दीर्घ		ac_mem;
	u64			ac_uसमय, ac_sसमय;
	अचिन्हित दीर्घ		ac_minflt, ac_majflt;
पूर्ण;

काष्ठा cpu_iसमयr अणु
	u64 expires;
	u64 incr;
पूर्ण;

/*
 * This is the atomic variant of task_cpuसमय, which can be used क्रम
 * storing and updating task_cpuसमय statistics without locking.
 */
काष्ठा task_cpuसमय_atomic अणु
	atomic64_t uसमय;
	atomic64_t sसमय;
	atomic64_t sum_exec_runसमय;
पूर्ण;

#घोषणा INIT_CPUTIME_ATOMIC \
	(काष्ठा task_cpuसमय_atomic) अणु				\
		.uसमय = ATOMIC64_INIT(0),			\
		.sसमय = ATOMIC64_INIT(0),			\
		.sum_exec_runसमय = ATOMIC64_INIT(0),		\
	पूर्ण
/**
 * काष्ठा thपढ़ो_group_cpuसमयr - thपढ़ो group पूर्णांकerval समयr counts
 * @cpuसमय_atomic:	atomic thपढ़ो group पूर्णांकerval समयrs.
 *
 * This काष्ठाure contains the version of task_cpuसमय, above, that is
 * used क्रम thपढ़ो group CPU समयr calculations.
 */
काष्ठा thपढ़ो_group_cpuसमयr अणु
	काष्ठा task_cpuसमय_atomic cpuसमय_atomic;
पूर्ण;

काष्ठा multiprocess_संकेतs अणु
	sigset_t संकेत;
	काष्ठा hlist_node node;
पूर्ण;

/*
 * NOTE! "signal_struct" करोes not have its own
 * locking, because a shared संकेत_काष्ठा always
 * implies a shared sighand_काष्ठा, so locking
 * sighand_काष्ठा is always a proper superset of
 * the locking of संकेत_काष्ठा.
 */
काष्ठा संकेत_काष्ठा अणु
	refcount_t		sigcnt;
	atomic_t		live;
	पूर्णांक			nr_thपढ़ोs;
	काष्ठा list_head	thपढ़ो_head;

	रुको_queue_head_t	रुको_chldनिकास;	/* क्रम रुको4() */

	/* current thपढ़ो group संकेत load-balancing target: */
	काष्ठा task_काष्ठा	*curr_target;

	/* shared संकेत handling: */
	काष्ठा संक_बाकी	shared_pending;

	/* For collecting multiprocess संकेतs during विभाजन */
	काष्ठा hlist_head	multiprocess;

	/* thपढ़ो group निकास support */
	पूर्णांक			group_निकास_code;
	/* overloaded:
	 * - notअगरy group_निकास_task when ->count is equal to notअगरy_count
	 * - everyone except group_निकास_task is stopped during संकेत delivery
	 *   of fatal संकेतs, group_निकास_task processes the संकेत.
	 */
	पूर्णांक			notअगरy_count;
	काष्ठा task_काष्ठा	*group_निकास_task;

	/* thपढ़ो group stop support, overloads group_निकास_code too */
	पूर्णांक			group_stop_count;
	अचिन्हित पूर्णांक		flags; /* see SIGNAL_* flags below */

	/*
	 * PR_SET_CHILD_SUBREAPER marks a process, like a service
	 * manager, to re-parent orphan (द्विगुन-विभाजनing) child processes
	 * to this process instead of 'init'. The service manager is
	 * able to receive SIGCHLD संकेतs and is able to investigate
	 * the process until it calls रुको(). All children of this
	 * process will inherit a flag अगर they should look क्रम a
	 * child_subreaper process at निकास.
	 */
	अचिन्हित पूर्णांक		is_child_subreaper:1;
	अचिन्हित पूर्णांक		has_child_subreaper:1;

#अगर_घोषित CONFIG_POSIX_TIMERS

	/* POSIX.1b Interval Timers */
	पूर्णांक			posix_समयr_id;
	काष्ठा list_head	posix_समयrs;

	/* ITIMER_REAL समयr क्रम the process */
	काष्ठा hrसमयr real_समयr;
	kसमय_प्रकार it_real_incr;

	/*
	 * ITIMER_PROF and ITIMER_VIRTUAL समयrs क्रम the process, we use
	 * CPUCLOCK_PROF and CPUCLOCK_VIRT क्रम indexing array as these
	 * values are defined to 0 and 1 respectively
	 */
	काष्ठा cpu_iसमयr it[2];

	/*
	 * Thपढ़ो group totals क्रम process CPU समयrs.
	 * See thपढ़ो_group_cpuसमयr(), et al, क्रम details.
	 */
	काष्ठा thपढ़ो_group_cpuसमयr cpuसमयr;

#पूर्ण_अगर
	/* Empty अगर CONFIG_POSIX_TIMERS=n */
	काष्ठा posix_cpuसमयrs posix_cpuसमयrs;

	/* PID/PID hash table linkage. */
	काष्ठा pid *pids[PIDTYPE_MAX];

#अगर_घोषित CONFIG_NO_HZ_FULL
	atomic_t tick_dep_mask;
#पूर्ण_अगर

	काष्ठा pid *tty_old_pgrp;

	/* boolean value क्रम session group leader */
	पूर्णांक leader;

	काष्ठा tty_काष्ठा *tty; /* शून्य अगर no tty */

#अगर_घोषित CONFIG_SCHED_AUTOGROUP
	काष्ठा स्वतःgroup *स्वतःgroup;
#पूर्ण_अगर
	/*
	 * Cumulative resource counters क्रम dead thपढ़ोs in the group,
	 * and क्रम reaped dead child processes विभाजनed by this group.
	 * Live thपढ़ोs मुख्यtain their own counters and add to these
	 * in __निकास_संकेत, except क्रम the group leader.
	 */
	seqlock_t stats_lock;
	u64 uसमय, sसमय, cuसमय, csसमय;
	u64 gसमय;
	u64 cgसमय;
	काष्ठा prev_cpuसमय prev_cpuसमय;
	अचिन्हित दीर्घ nvcsw, nivcsw, cnvcsw, cnivcsw;
	अचिन्हित दीर्घ min_flt, maj_flt, cmin_flt, cmaj_flt;
	अचिन्हित दीर्घ inblock, oublock, cinblock, coublock;
	अचिन्हित दीर्घ maxrss, cmaxrss;
	काष्ठा task_io_accounting ioac;

	/*
	 * Cumulative ns of schedule CPU समय fo dead thपढ़ोs in the
	 * group, not including a zombie group leader, (This only dअगरfers
	 * from jअगरfies_to_ns(uसमय + sसमय) अगर sched_घड़ी uses something
	 * other than jअगरfies.)
	 */
	अचिन्हित दीर्घ दीर्घ sum_sched_runसमय;

	/*
	 * We करोn't bother to synchronize most पढ़ोers of this at all,
	 * because there is no पढ़ोer checking a limit that actually needs
	 * to get both rlim_cur and rlim_max atomically, and either one
	 * alone is a single word that can safely be पढ़ो normally.
	 * getrlimit/setrlimit use task_lock(current->group_leader) to
	 * protect this instead of the siglock, because they really
	 * have no need to disable irqs.
	 */
	काष्ठा rlimit rlim[RLIM_NLIMITS];

#अगर_घोषित CONFIG_BSD_PROCESS_ACCT
	काष्ठा pacct_काष्ठा pacct;	/* per-process accounting inक्रमmation */
#पूर्ण_अगर
#अगर_घोषित CONFIG_TASKSTATS
	काष्ठा taskstats *stats;
#पूर्ण_अगर
#अगर_घोषित CONFIG_AUDIT
	अचिन्हित audit_tty;
	काष्ठा tty_audit_buf *tty_audit_buf;
#पूर्ण_अगर

	/*
	 * Thपढ़ो is the potential origin of an oom condition; समाप्त first on
	 * oom
	 */
	bool oom_flag_origin;
	लघु oom_score_adj;		/* OOM समाप्त score adjusपंचांगent */
	लघु oom_score_adj_min;	/* OOM समाप्त score adjusपंचांगent min value.
					 * Only settable by CAP_SYS_RESOURCE. */
	काष्ठा mm_काष्ठा *oom_mm;	/* recorded mm when the thपढ़ो group got
					 * समाप्तed by the oom समाप्तer */

	काष्ठा mutex cred_guard_mutex;	/* guard against क्रमeign influences on
					 * credential calculations
					 * (notably. ptrace)
					 * Deprecated करो not use in new code.
					 * Use exec_update_lock instead.
					 */
	काष्ठा rw_semaphore exec_update_lock;	/* Held जबतक task_काष्ठा is
						 * being updated during exec,
						 * and may have inconsistent
						 * permissions.
						 */
पूर्ण __अक्रमomize_layout;

/*
 * Bits in flags field of संकेत_काष्ठा.
 */
#घोषणा SIGNAL_STOP_STOPPED	0x00000001 /* job control stop in effect */
#घोषणा SIGNAL_STOP_CONTINUED	0x00000002 /* SIGCONT since WCONTINUED reap */
#घोषणा SIGNAL_GROUP_EXIT	0x00000004 /* group निकास in progress */
#घोषणा SIGNAL_GROUP_COREDUMP	0x00000008 /* coredump in progress */
/*
 * Pending notअगरications to parent.
 */
#घोषणा SIGNAL_CLD_STOPPED	0x00000010
#घोषणा SIGNAL_CLD_CONTINUED	0x00000020
#घोषणा SIGNAL_CLD_MASK		(SIGNAL_CLD_STOPPED|SIGNAL_CLD_CONTINUED)

#घोषणा SIGNAL_UNKILLABLE	0x00000040 /* क्रम init: ignore fatal संकेतs */

#घोषणा SIGNAL_STOP_MASK (SIGNAL_CLD_MASK | SIGNAL_STOP_STOPPED | \
			  SIGNAL_STOP_CONTINUED)

अटल अंतरभूत व्योम संकेत_set_stop_flags(काष्ठा संकेत_काष्ठा *sig,
					 अचिन्हित पूर्णांक flags)
अणु
	WARN_ON(sig->flags & (SIGNAL_GROUP_EXIT|SIGNAL_GROUP_COREDUMP));
	sig->flags = (sig->flags & ~SIGNAL_STOP_MASK) | flags;
पूर्ण

/* If true, all thपढ़ोs except ->group_निकास_task have pending SIGKILL */
अटल अंतरभूत पूर्णांक संकेत_group_निकास(स्थिर काष्ठा संकेत_काष्ठा *sig)
अणु
	वापस	(sig->flags & SIGNAL_GROUP_EXIT) ||
		(sig->group_निकास_task != शून्य);
पूर्ण

बाह्य व्योम flush_संकेतs(काष्ठा task_काष्ठा *);
बाह्य व्योम ignore_संकेतs(काष्ठा task_काष्ठा *);
बाह्य व्योम flush_संकेत_handlers(काष्ठा task_काष्ठा *, पूर्णांक क्रमce_शेष);
बाह्य पूर्णांक dequeue_संकेत(काष्ठा task_काष्ठा *task,
			  sigset_t *mask, kernel_siginfo_t *info);

अटल अंतरभूत पूर्णांक kernel_dequeue_संकेत(व्योम)
अणु
	काष्ठा task_काष्ठा *task = current;
	kernel_siginfo_t __info;
	पूर्णांक ret;

	spin_lock_irq(&task->sighand->siglock);
	ret = dequeue_संकेत(task, &task->blocked, &__info);
	spin_unlock_irq(&task->sighand->siglock);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम kernel_संकेत_stop(व्योम)
अणु
	spin_lock_irq(&current->sighand->siglock);
	अगर (current->jobctl & JOBCTL_STOP_DEQUEUED)
		set_special_state(TASK_STOPPED);
	spin_unlock_irq(&current->sighand->siglock);

	schedule();
पूर्ण
#अगर_घोषित __ARCH_SI_TRAPNO
# define ___ARCH_SI_TRAPNO(_a1) , _a1
#अन्यथा
# define ___ARCH_SI_TRAPNO(_a1)
#पूर्ण_अगर
#अगर_घोषित __ia64__
# define ___ARCH_SI_IA64(_a1, _a2, _a3) , _a1, _a2, _a3
#अन्यथा
# define ___ARCH_SI_IA64(_a1, _a2, _a3)
#पूर्ण_अगर

पूर्णांक क्रमce_sig_fault_to_task(पूर्णांक sig, पूर्णांक code, व्योम __user *addr
	___ARCH_SI_TRAPNO(पूर्णांक trapno)
	___ARCH_SI_IA64(पूर्णांक imm, अचिन्हित पूर्णांक flags, अचिन्हित दीर्घ isr)
	, काष्ठा task_काष्ठा *t);
पूर्णांक क्रमce_sig_fault(पूर्णांक sig, पूर्णांक code, व्योम __user *addr
	___ARCH_SI_TRAPNO(पूर्णांक trapno)
	___ARCH_SI_IA64(पूर्णांक imm, अचिन्हित पूर्णांक flags, अचिन्हित दीर्घ isr));
पूर्णांक send_sig_fault(पूर्णांक sig, पूर्णांक code, व्योम __user *addr
	___ARCH_SI_TRAPNO(पूर्णांक trapno)
	___ARCH_SI_IA64(पूर्णांक imm, अचिन्हित पूर्णांक flags, अचिन्हित दीर्घ isr)
	, काष्ठा task_काष्ठा *t);

पूर्णांक क्रमce_sig_mceerr(पूर्णांक code, व्योम __user *, लघु);
पूर्णांक send_sig_mceerr(पूर्णांक code, व्योम __user *, लघु, काष्ठा task_काष्ठा *);

पूर्णांक क्रमce_sig_bnderr(व्योम __user *addr, व्योम __user *lower, व्योम __user *upper);
पूर्णांक क्रमce_sig_pkuerr(व्योम __user *addr, u32 pkey);
पूर्णांक क्रमce_sig_perf(व्योम __user *addr, u32 type, u64 sig_data);

पूर्णांक क्रमce_sig_ptrace_त्रुटि_सं_trap(पूर्णांक त्रुटि_सं, व्योम __user *addr);

बाह्य पूर्णांक send_sig_info(पूर्णांक, काष्ठा kernel_siginfo *, काष्ठा task_काष्ठा *);
बाह्य व्योम क्रमce_sigsegv(पूर्णांक sig);
बाह्य पूर्णांक क्रमce_sig_info(काष्ठा kernel_siginfo *);
बाह्य पूर्णांक __समाप्त_pgrp_info(पूर्णांक sig, काष्ठा kernel_siginfo *info, काष्ठा pid *pgrp);
बाह्य पूर्णांक समाप्त_pid_info(पूर्णांक sig, काष्ठा kernel_siginfo *info, काष्ठा pid *pid);
बाह्य पूर्णांक समाप्त_pid_usb_asyncio(पूर्णांक sig, पूर्णांक त्रुटि_सं, sigval_t addr, काष्ठा pid *,
				स्थिर काष्ठा cred *);
बाह्य पूर्णांक समाप्त_pgrp(काष्ठा pid *pid, पूर्णांक sig, पूर्णांक priv);
बाह्य पूर्णांक समाप्त_pid(काष्ठा pid *pid, पूर्णांक sig, पूर्णांक priv);
बाह्य __must_check bool करो_notअगरy_parent(काष्ठा task_काष्ठा *, पूर्णांक);
बाह्य व्योम __wake_up_parent(काष्ठा task_काष्ठा *p, काष्ठा task_काष्ठा *parent);
बाह्य व्योम क्रमce_sig(पूर्णांक);
बाह्य पूर्णांक send_sig(पूर्णांक, काष्ठा task_काष्ठा *, पूर्णांक);
बाह्य पूर्णांक zap_other_thपढ़ोs(काष्ठा task_काष्ठा *p);
बाह्य काष्ठा sigqueue *sigqueue_alloc(व्योम);
बाह्य व्योम sigqueue_मुक्त(काष्ठा sigqueue *);
बाह्य पूर्णांक send_sigqueue(काष्ठा sigqueue *, काष्ठा pid *, क्रमागत pid_type);
बाह्य पूर्णांक करो_sigaction(पूर्णांक, काष्ठा k_sigaction *, काष्ठा k_sigaction *);

अटल अंतरभूत पूर्णांक restart_syscall(व्योम)
अणु
	set_tsk_thपढ़ो_flag(current, TIF_SIGPENDING);
	वापस -ERESTARTNOINTR;
पूर्ण

अटल अंतरभूत पूर्णांक task_संक_बाकी(काष्ठा task_काष्ठा *p)
अणु
	वापस unlikely(test_tsk_thपढ़ो_flag(p,TIF_SIGPENDING));
पूर्ण

अटल अंतरभूत पूर्णांक संकेत_pending(काष्ठा task_काष्ठा *p)
अणु
	/*
	 * TIF_NOTIFY_SIGNAL isn't really a संकेत, but it requires the same
	 * behavior in terms of ensuring that we अवरोध out of रुको loops
	 * so that notअगरy संकेत callbacks can be processed.
	 */
	अगर (unlikely(test_tsk_thपढ़ो_flag(p, TIF_NOTIFY_SIGNAL)))
		वापस 1;
	वापस task_संक_बाकी(p);
पूर्ण

अटल अंतरभूत पूर्णांक __fatal_संकेत_pending(काष्ठा task_काष्ठा *p)
अणु
	वापस unlikely(sigismember(&p->pending.संकेत, SIGKILL));
पूर्ण

अटल अंतरभूत पूर्णांक fatal_संकेत_pending(काष्ठा task_काष्ठा *p)
अणु
	वापस task_संक_बाकी(p) && __fatal_संकेत_pending(p);
पूर्ण

अटल अंतरभूत पूर्णांक संकेत_pending_state(दीर्घ state, काष्ठा task_काष्ठा *p)
अणु
	अगर (!(state & (TASK_INTERRUPTIBLE | TASK_WAKEKILL)))
		वापस 0;
	अगर (!संकेत_pending(p))
		वापस 0;

	वापस (state & TASK_INTERRUPTIBLE) || __fatal_संकेत_pending(p);
पूर्ण

/*
 * This should only be used in fault handlers to decide whether we
 * should stop the current fault routine to handle the संकेतs
 * instead, especially with the हाल where we've got पूर्णांकerrupted with
 * a VM_FAULT_RETRY.
 */
अटल अंतरभूत bool fault_संकेत_pending(vm_fault_t fault_flags,
					काष्ठा pt_regs *regs)
अणु
	वापस unlikely((fault_flags & VM_FAULT_RETRY) &&
			(fatal_संकेत_pending(current) ||
			 (user_mode(regs) && संकेत_pending(current))));
पूर्ण

/*
 * Reevaluate whether the task has संकेतs pending delivery.
 * Wake the task अगर so.
 * This is required every समय the blocked sigset_t changes.
 * callers must hold sighand->siglock.
 */
बाह्य व्योम recalc_संक_बाकी_and_wake(काष्ठा task_काष्ठा *t);
बाह्य व्योम recalc_संक_बाकी(व्योम);
बाह्य व्योम calculate_संक_बाकी(व्योम);

बाह्य व्योम संकेत_wake_up_state(काष्ठा task_काष्ठा *t, अचिन्हित पूर्णांक state);

अटल अंतरभूत व्योम संकेत_wake_up(काष्ठा task_काष्ठा *t, bool resume)
अणु
	संकेत_wake_up_state(t, resume ? TASK_WAKEKILL : 0);
पूर्ण
अटल अंतरभूत व्योम ptrace_संकेत_wake_up(काष्ठा task_काष्ठा *t, bool resume)
अणु
	संकेत_wake_up_state(t, resume ? __TASK_TRACED : 0);
पूर्ण

व्योम task_join_group_stop(काष्ठा task_काष्ठा *task);

#अगर_घोषित TIF_RESTORE_SIGMASK
/*
 * Legacy restore_sigmask accessors.  These are inefficient on
 * SMP architectures because they require atomic operations.
 */

/**
 * set_restore_sigmask() - make sure saved_sigmask processing माला_लो करोne
 *
 * This sets TIF_RESTORE_SIGMASK and ensures that the arch संकेत code
 * will run beक्रमe वापसing to user mode, to process the flag.  For
 * all callers, TIF_SIGPENDING is alपढ़ोy set or it's no harm to set
 * it.  TIF_RESTORE_SIGMASK need not be in the set of bits that the
 * arch code will notice on वापस to user mode, in हाल those bits
 * are scarce.  We set TIF_SIGPENDING here to ensure that the arch
 * संकेत code always माला_लो run when TIF_RESTORE_SIGMASK is set.
 */
अटल अंतरभूत व्योम set_restore_sigmask(व्योम)
अणु
	set_thपढ़ो_flag(TIF_RESTORE_SIGMASK);
पूर्ण

अटल अंतरभूत व्योम clear_tsk_restore_sigmask(काष्ठा task_काष्ठा *task)
अणु
	clear_tsk_thपढ़ो_flag(task, TIF_RESTORE_SIGMASK);
पूर्ण

अटल अंतरभूत व्योम clear_restore_sigmask(व्योम)
अणु
	clear_thपढ़ो_flag(TIF_RESTORE_SIGMASK);
पूर्ण
अटल अंतरभूत bool test_tsk_restore_sigmask(काष्ठा task_काष्ठा *task)
अणु
	वापस test_tsk_thपढ़ो_flag(task, TIF_RESTORE_SIGMASK);
पूर्ण
अटल अंतरभूत bool test_restore_sigmask(व्योम)
अणु
	वापस test_thपढ़ो_flag(TIF_RESTORE_SIGMASK);
पूर्ण
अटल अंतरभूत bool test_and_clear_restore_sigmask(व्योम)
अणु
	वापस test_and_clear_thपढ़ो_flag(TIF_RESTORE_SIGMASK);
पूर्ण

#अन्यथा	/* TIF_RESTORE_SIGMASK */

/* Higher-quality implementation, used अगर TIF_RESTORE_SIGMASK करोesn't exist. */
अटल अंतरभूत व्योम set_restore_sigmask(व्योम)
अणु
	current->restore_sigmask = true;
पूर्ण
अटल अंतरभूत व्योम clear_tsk_restore_sigmask(काष्ठा task_काष्ठा *task)
अणु
	task->restore_sigmask = false;
पूर्ण
अटल अंतरभूत व्योम clear_restore_sigmask(व्योम)
अणु
	current->restore_sigmask = false;
पूर्ण
अटल अंतरभूत bool test_restore_sigmask(व्योम)
अणु
	वापस current->restore_sigmask;
पूर्ण
अटल अंतरभूत bool test_tsk_restore_sigmask(काष्ठा task_काष्ठा *task)
अणु
	वापस task->restore_sigmask;
पूर्ण
अटल अंतरभूत bool test_and_clear_restore_sigmask(व्योम)
अणु
	अगर (!current->restore_sigmask)
		वापस false;
	current->restore_sigmask = false;
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम restore_saved_sigmask(व्योम)
अणु
	अगर (test_and_clear_restore_sigmask())
		__set_current_blocked(&current->saved_sigmask);
पूर्ण

बाह्य पूर्णांक set_user_sigmask(स्थिर sigset_t __user *umask, माप_प्रकार sigsetsize);

अटल अंतरभूत व्योम restore_saved_sigmask_unless(bool पूर्णांकerrupted)
अणु
	अगर (पूर्णांकerrupted)
		WARN_ON(!संकेत_pending(current));
	अन्यथा
		restore_saved_sigmask();
पूर्ण

अटल अंतरभूत sigset_t *sigmask_to_save(व्योम)
अणु
	sigset_t *res = &current->blocked;
	अगर (unlikely(test_restore_sigmask()))
		res = &current->saved_sigmask;
	वापस res;
पूर्ण

अटल अंतरभूत पूर्णांक समाप्त_cad_pid(पूर्णांक sig, पूर्णांक priv)
अणु
	वापस समाप्त_pid(cad_pid, sig, priv);
पूर्ण

/* These can be the second arg to send_sig_info/send_group_sig_info.  */
#घोषणा SEND_SIG_NOINFO ((काष्ठा kernel_siginfo *) 0)
#घोषणा SEND_SIG_PRIV	((काष्ठा kernel_siginfo *) 1)

/*
 * True अगर we are on the alternate संकेत stack.
 */
अटल अंतरभूत पूर्णांक on_sig_stack(अचिन्हित दीर्घ sp)
अणु
	/*
	 * If the संकेत stack is SS_AUTODISARM then, by स्थिरruction, we
	 * can't be on the संकेत stack unless user code deliberately set
	 * SS_AUTODISARM when we were alपढ़ोy on it.
	 *
	 * This improves reliability: अगर user state माला_लो corrupted such that
	 * the stack poपूर्णांकer poपूर्णांकs very बंद to the end of the संकेत stack,
	 * then this check will enable the संकेत to be handled anyway.
	 */
	अगर (current->sas_ss_flags & SS_AUTODISARM)
		वापस 0;

#अगर_घोषित CONFIG_STACK_GROWSUP
	वापस sp >= current->sas_ss_sp &&
		sp - current->sas_ss_sp < current->sas_ss_size;
#अन्यथा
	वापस sp > current->sas_ss_sp &&
		sp - current->sas_ss_sp <= current->sas_ss_size;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक sas_ss_flags(अचिन्हित दीर्घ sp)
अणु
	अगर (!current->sas_ss_size)
		वापस SS_DISABLE;

	वापस on_sig_stack(sp) ? SS_ONSTACK : 0;
पूर्ण

अटल अंतरभूत व्योम sas_ss_reset(काष्ठा task_काष्ठा *p)
अणु
	p->sas_ss_sp = 0;
	p->sas_ss_size = 0;
	p->sas_ss_flags = SS_DISABLE;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ sigsp(अचिन्हित दीर्घ sp, काष्ठा kसंकेत *ksig)
अणु
	अगर (unlikely((ksig->ka.sa.sa_flags & SA_ONSTACK)) && ! sas_ss_flags(sp))
#अगर_घोषित CONFIG_STACK_GROWSUP
		वापस current->sas_ss_sp;
#अन्यथा
		वापस current->sas_ss_sp + current->sas_ss_size;
#पूर्ण_अगर
	वापस sp;
पूर्ण

बाह्य व्योम __cleanup_sighand(काष्ठा sighand_काष्ठा *);
बाह्य व्योम flush_iसमयr_संकेतs(व्योम);

#घोषणा tasklist_empty() \
	list_empty(&init_task.tasks)

#घोषणा next_task(p) \
	list_entry_rcu((p)->tasks.next, काष्ठा task_काष्ठा, tasks)

#घोषणा क्रम_each_process(p) \
	क्रम (p = &init_task ; (p = next_task(p)) != &init_task ; )

बाह्य bool current_is_single_thपढ़ोed(व्योम);

/*
 * Careful: करो_each_thपढ़ो/जबतक_each_thपढ़ो is a द्विगुन loop so
 *          'break' will not work as expected - use जाओ instead.
 */
#घोषणा करो_each_thपढ़ो(g, t) \
	क्रम (g = t = &init_task ; (g = t = next_task(g)) != &init_task ; ) करो

#घोषणा जबतक_each_thपढ़ो(g, t) \
	जबतक ((t = next_thपढ़ो(t)) != g)

#घोषणा __क्रम_each_thपढ़ो(संकेत, t)	\
	list_क्रम_each_entry_rcu(t, &(संकेत)->thपढ़ो_head, thपढ़ो_node)

#घोषणा क्रम_each_thपढ़ो(p, t)		\
	__क्रम_each_thपढ़ो((p)->संकेत, t)

/* Careful: this is a द्विगुन loop, 'break' won't work as expected. */
#घोषणा क्रम_each_process_thपढ़ो(p, t)	\
	क्रम_each_process(p) क्रम_each_thपढ़ो(p, t)

प्रकार पूर्णांक (*proc_visitor)(काष्ठा task_काष्ठा *p, व्योम *data);
व्योम walk_process_tree(काष्ठा task_काष्ठा *top, proc_visitor, व्योम *);

अटल अंतरभूत
काष्ठा pid *task_pid_type(काष्ठा task_काष्ठा *task, क्रमागत pid_type type)
अणु
	काष्ठा pid *pid;
	अगर (type == PIDTYPE_PID)
		pid = task_pid(task);
	अन्यथा
		pid = task->संकेत->pids[type];
	वापस pid;
पूर्ण

अटल अंतरभूत काष्ठा pid *task_tgid(काष्ठा task_काष्ठा *task)
अणु
	वापस task->संकेत->pids[PIDTYPE_TGID];
पूर्ण

/*
 * Without tasklist or RCU lock it is not safe to dereference
 * the result of task_pgrp/task_session even अगर task == current,
 * we can race with another thपढ़ो करोing sys_setsid/sys_setpgid.
 */
अटल अंतरभूत काष्ठा pid *task_pgrp(काष्ठा task_काष्ठा *task)
अणु
	वापस task->संकेत->pids[PIDTYPE_PGID];
पूर्ण

अटल अंतरभूत काष्ठा pid *task_session(काष्ठा task_काष्ठा *task)
अणु
	वापस task->संकेत->pids[PIDTYPE_SID];
पूर्ण

अटल अंतरभूत पूर्णांक get_nr_thपढ़ोs(काष्ठा task_काष्ठा *task)
अणु
	वापस task->संकेत->nr_thपढ़ोs;
पूर्ण

अटल अंतरभूत bool thपढ़ो_group_leader(काष्ठा task_काष्ठा *p)
अणु
	वापस p->निकास_संकेत >= 0;
पूर्ण

अटल अंतरभूत
bool same_thपढ़ो_group(काष्ठा task_काष्ठा *p1, काष्ठा task_काष्ठा *p2)
अणु
	वापस p1->संकेत == p2->संकेत;
पूर्ण

अटल अंतरभूत काष्ठा task_काष्ठा *next_thपढ़ो(स्थिर काष्ठा task_काष्ठा *p)
अणु
	वापस list_entry_rcu(p->thपढ़ो_group.next,
			      काष्ठा task_काष्ठा, thपढ़ो_group);
पूर्ण

अटल अंतरभूत पूर्णांक thपढ़ो_group_empty(काष्ठा task_काष्ठा *p)
अणु
	वापस list_empty(&p->thपढ़ो_group);
पूर्ण

#घोषणा delay_group_leader(p) \
		(thपढ़ो_group_leader(p) && !thपढ़ो_group_empty(p))

बाह्य bool thपढ़ो_group_निकासed(काष्ठा pid *pid);

बाह्य काष्ठा sighand_काष्ठा *__lock_task_sighand(काष्ठा task_काष्ठा *task,
							अचिन्हित दीर्घ *flags);

अटल अंतरभूत काष्ठा sighand_काष्ठा *lock_task_sighand(काष्ठा task_काष्ठा *task,
						       अचिन्हित दीर्घ *flags)
अणु
	काष्ठा sighand_काष्ठा *ret;

	ret = __lock_task_sighand(task, flags);
	(व्योम)__cond_lock(&task->sighand->siglock, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम unlock_task_sighand(काष्ठा task_काष्ठा *task,
						अचिन्हित दीर्घ *flags)
अणु
	spin_unlock_irqrestore(&task->sighand->siglock, *flags);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ task_rlimit(स्थिर काष्ठा task_काष्ठा *task,
		अचिन्हित पूर्णांक limit)
अणु
	वापस READ_ONCE(task->संकेत->rlim[limit].rlim_cur);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ task_rlimit_max(स्थिर काष्ठा task_काष्ठा *task,
		अचिन्हित पूर्णांक limit)
अणु
	वापस READ_ONCE(task->संकेत->rlim[limit].rlim_max);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ rlimit(अचिन्हित पूर्णांक limit)
अणु
	वापस task_rlimit(current, limit);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ rlimit_max(अचिन्हित पूर्णांक limit)
अणु
	वापस task_rlimit_max(current, limit);
पूर्ण

#पूर्ण_अगर /* _LINUX_SCHED_SIGNAL_H */
