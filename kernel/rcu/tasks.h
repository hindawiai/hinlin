<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Task-based RCU implementations.
 *
 * Copyright (C) 2020 Paul E. McKenney
 */

#अगर_घोषित CONFIG_TASKS_RCU_GENERIC

////////////////////////////////////////////////////////////////////////
//
// Generic data काष्ठाures.

काष्ठा rcu_tasks;
प्रकार व्योम (*rcu_tasks_gp_func_t)(काष्ठा rcu_tasks *rtp);
प्रकार व्योम (*pregp_func_t)(व्योम);
प्रकार व्योम (*pertask_func_t)(काष्ठा task_काष्ठा *t, काष्ठा list_head *hop);
प्रकार व्योम (*postscan_func_t)(काष्ठा list_head *hop);
प्रकार व्योम (*holकरोuts_func_t)(काष्ठा list_head *hop, bool ndrpt, bool *frptp);
प्रकार व्योम (*postgp_func_t)(काष्ठा rcu_tasks *rtp);

/**
 * काष्ठा rcu_tasks - Definition क्रम a Tasks-RCU-like mechanism.
 * @cbs_head: Head of callback list.
 * @cbs_tail: Tail poपूर्णांकer क्रम callback list.
 * @cbs_wq: Wait queue allowning new callback to get kthपढ़ो's attention.
 * @cbs_lock: Lock protecting callback list.
 * @kthपढ़ो_ptr: This flavor's grace-period/callback-invocation kthपढ़ो.
 * @gp_func: This flavor's grace-period-रुको function.
 * @gp_state: Grace period's most recent state transition (debugging).
 * @gp_sleep: Per-grace-period sleep to prevent CPU-bound looping.
 * @init_fract: Initial backoff sleep पूर्णांकerval.
 * @gp_jअगरfies: Time of last @gp_state transition.
 * @gp_start: Most recent grace-period start in jअगरfies.
 * @n_gps: Number of grace periods completed since boot.
 * @n_ipis: Number of IPIs sent to encourage grace periods to end.
 * @n_ipis_fails: Number of IPI-send failures.
 * @pregp_func: This flavor's pre-grace-period function (optional).
 * @pertask_func: This flavor's per-task scan function (optional).
 * @postscan_func: This flavor's post-task scan function (optional).
 * @holकरोuts_func: This flavor's holकरोut-list scan function (optional).
 * @postgp_func: This flavor's post-grace-period function (optional).
 * @call_func: This flavor's call_rcu()-equivalent function.
 * @name: This flavor's textual name.
 * @kname: This flavor's kthपढ़ो name.
 */
काष्ठा rcu_tasks अणु
	काष्ठा rcu_head *cbs_head;
	काष्ठा rcu_head **cbs_tail;
	काष्ठा रुको_queue_head cbs_wq;
	raw_spinlock_t cbs_lock;
	पूर्णांक gp_state;
	पूर्णांक gp_sleep;
	पूर्णांक init_fract;
	अचिन्हित दीर्घ gp_jअगरfies;
	अचिन्हित दीर्घ gp_start;
	अचिन्हित दीर्घ n_gps;
	अचिन्हित दीर्घ n_ipis;
	अचिन्हित दीर्घ n_ipis_fails;
	काष्ठा task_काष्ठा *kthपढ़ो_ptr;
	rcu_tasks_gp_func_t gp_func;
	pregp_func_t pregp_func;
	pertask_func_t pertask_func;
	postscan_func_t postscan_func;
	holकरोuts_func_t holकरोuts_func;
	postgp_func_t postgp_func;
	call_rcu_func_t call_func;
	अक्षर *name;
	अक्षर *kname;
पूर्ण;

#घोषणा DEFINE_RCU_TASKS(rt_name, gp, call, n)				\
अटल काष्ठा rcu_tasks rt_name =					\
अणु									\
	.cbs_tail = &rt_name.cbs_head,					\
	.cbs_wq = __WAIT_QUEUE_HEAD_INITIALIZER(rt_name.cbs_wq),	\
	.cbs_lock = __RAW_SPIN_LOCK_UNLOCKED(rt_name.cbs_lock),		\
	.gp_func = gp,							\
	.call_func = call,						\
	.name = n,							\
	.kname = #rt_name,						\
पूर्ण

/* Track निकासing tasks in order to allow them to be रुकोed क्रम. */
DEFINE_STATIC_SRCU(tasks_rcu_निकास_srcu);

/* Aव्योम IPIing CPUs early in the grace period. */
#घोषणा RCU_TASK_IPI_DELAY (IS_ENABLED(CONFIG_TASKS_TRACE_RCU_READ_MB) ? HZ / 2 : 0)
अटल पूर्णांक rcu_task_ipi_delay __पढ़ो_mostly = RCU_TASK_IPI_DELAY;
module_param(rcu_task_ipi_delay, पूर्णांक, 0644);

/* Control stall समयouts.  Disable with <= 0, otherwise jअगरfies till stall. */
#घोषणा RCU_TASK_STALL_TIMEOUT (HZ * 60 * 10)
अटल पूर्णांक rcu_task_stall_समयout __पढ़ो_mostly = RCU_TASK_STALL_TIMEOUT;
module_param(rcu_task_stall_समयout, पूर्णांक, 0644);

/* RCU tasks grace-period state क्रम debugging. */
#घोषणा RTGS_INIT		 0
#घोषणा RTGS_WAIT_WAIT_CBS	 1
#घोषणा RTGS_WAIT_GP		 2
#घोषणा RTGS_PRE_WAIT_GP	 3
#घोषणा RTGS_SCAN_TASKLIST	 4
#घोषणा RTGS_POST_SCAN_TASKLIST	 5
#घोषणा RTGS_WAIT_SCAN_HOLDOUTS	 6
#घोषणा RTGS_SCAN_HOLDOUTS	 7
#घोषणा RTGS_POST_GP		 8
#घोषणा RTGS_WAIT_READERS	 9
#घोषणा RTGS_INVOKE_CBS		10
#घोषणा RTGS_WAIT_CBS		11
#अगर_अघोषित CONFIG_TINY_RCU
अटल स्थिर अक्षर * स्थिर rcu_tasks_gp_state_names[] = अणु
	"RTGS_INIT",
	"RTGS_WAIT_WAIT_CBS",
	"RTGS_WAIT_GP",
	"RTGS_PRE_WAIT_GP",
	"RTGS_SCAN_TASKLIST",
	"RTGS_POST_SCAN_TASKLIST",
	"RTGS_WAIT_SCAN_HOLDOUTS",
	"RTGS_SCAN_HOLDOUTS",
	"RTGS_POST_GP",
	"RTGS_WAIT_READERS",
	"RTGS_INVOKE_CBS",
	"RTGS_WAIT_CBS",
पूर्ण;
#पूर्ण_अगर /* #अगर_अघोषित CONFIG_TINY_RCU */

////////////////////////////////////////////////////////////////////////
//
// Generic code.

/* Record grace-period phase and समय. */
अटल व्योम set_tasks_gp_state(काष्ठा rcu_tasks *rtp, पूर्णांक newstate)
अणु
	rtp->gp_state = newstate;
	rtp->gp_jअगरfies = jअगरfies;
पूर्ण

#अगर_अघोषित CONFIG_TINY_RCU
/* Return state name. */
अटल स्थिर अक्षर *tasks_gp_state_getname(काष्ठा rcu_tasks *rtp)
अणु
	पूर्णांक i = data_race(rtp->gp_state); // Let KCSAN detect update races
	पूर्णांक j = READ_ONCE(i); // Prevent the compiler from पढ़ोing twice

	अगर (j >= ARRAY_SIZE(rcu_tasks_gp_state_names))
		वापस "???";
	वापस rcu_tasks_gp_state_names[j];
पूर्ण
#पूर्ण_अगर /* #अगर_अघोषित CONFIG_TINY_RCU */

// Enqueue a callback क्रम the specअगरied flavor of Tasks RCU.
अटल व्योम call_rcu_tasks_generic(काष्ठा rcu_head *rhp, rcu_callback_t func,
				   काष्ठा rcu_tasks *rtp)
अणु
	अचिन्हित दीर्घ flags;
	bool needwake;

	rhp->next = शून्य;
	rhp->func = func;
	raw_spin_lock_irqsave(&rtp->cbs_lock, flags);
	needwake = !rtp->cbs_head;
	WRITE_ONCE(*rtp->cbs_tail, rhp);
	rtp->cbs_tail = &rhp->next;
	raw_spin_unlock_irqrestore(&rtp->cbs_lock, flags);
	/* We can't create the thपढ़ो unless पूर्णांकerrupts are enabled. */
	अगर (needwake && READ_ONCE(rtp->kthपढ़ो_ptr))
		wake_up(&rtp->cbs_wq);
पूर्ण

// Wait क्रम a grace period क्रम the specअगरied flavor of Tasks RCU.
अटल व्योम synchronize_rcu_tasks_generic(काष्ठा rcu_tasks *rtp)
अणु
	/* Complain अगर the scheduler has not started.  */
	RCU_LOCKDEP_WARN(rcu_scheduler_active == RCU_SCHEDULER_INACTIVE,
			 "synchronize_rcu_tasks called too soon");

	/* Wait क्रम the grace period. */
	रुको_rcu_gp(rtp->call_func);
पूर्ण

/* RCU-tasks kthपढ़ो that detects grace periods and invokes callbacks. */
अटल पूर्णांक __noवापस rcu_tasks_kthपढ़ो(व्योम *arg)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rcu_head *list;
	काष्ठा rcu_head *next;
	काष्ठा rcu_tasks *rtp = arg;

	/* Run on housekeeping CPUs by शेष.  Sysadm can move अगर desired. */
	housekeeping_affine(current, HK_FLAG_RCU);
	WRITE_ONCE(rtp->kthपढ़ो_ptr, current); // Let GPs start!

	/*
	 * Each pass through the following loop makes one check क्रम
	 * newly arrived callbacks, and, अगर there are some, रुकोs क्रम
	 * one RCU-tasks grace period and then invokes the callbacks.
	 * This loop is terminated by the प्रणाली going करोwn.  ;-)
	 */
	क्रम (;;) अणु

		/* Pick up any new callbacks. */
		raw_spin_lock_irqsave(&rtp->cbs_lock, flags);
		smp_mb__after_spinlock(); // Order updates vs. GP.
		list = rtp->cbs_head;
		rtp->cbs_head = शून्य;
		rtp->cbs_tail = &rtp->cbs_head;
		raw_spin_unlock_irqrestore(&rtp->cbs_lock, flags);

		/* If there were none, रुको a bit and start over. */
		अगर (!list) अणु
			रुको_event_पूर्णांकerruptible(rtp->cbs_wq,
						 READ_ONCE(rtp->cbs_head));
			अगर (!rtp->cbs_head) अणु
				WARN_ON(संकेत_pending(current));
				set_tasks_gp_state(rtp, RTGS_WAIT_WAIT_CBS);
				schedule_समयout_idle(HZ/10);
			पूर्ण
			जारी;
		पूर्ण

		// Wait क्रम one grace period.
		set_tasks_gp_state(rtp, RTGS_WAIT_GP);
		rtp->gp_start = jअगरfies;
		rtp->gp_func(rtp);
		rtp->n_gps++;

		/* Invoke the callbacks. */
		set_tasks_gp_state(rtp, RTGS_INVOKE_CBS);
		जबतक (list) अणु
			next = list->next;
			local_bh_disable();
			list->func(list);
			local_bh_enable();
			list = next;
			cond_resched();
		पूर्ण
		/* Paranoid sleep to keep this from entering a tight loop */
		schedule_समयout_idle(rtp->gp_sleep);

		set_tasks_gp_state(rtp, RTGS_WAIT_CBS);
	पूर्ण
पूर्ण

/* Spawn RCU-tasks grace-period kthपढ़ो. */
अटल व्योम __init rcu_spawn_tasks_kthपढ़ो_generic(काष्ठा rcu_tasks *rtp)
अणु
	काष्ठा task_काष्ठा *t;

	t = kthपढ़ो_run(rcu_tasks_kthपढ़ो, rtp, "%s_kthread", rtp->kname);
	अगर (WARN_ONCE(IS_ERR(t), "%s: Could not start %s grace-period kthread, OOM is now expected behavior\n", __func__, rtp->name))
		वापस;
	smp_mb(); /* Ensure others see full kthपढ़ो. */
पूर्ण

#अगर_अघोषित CONFIG_TINY_RCU

/*
 * Prपूर्णांक any non-शेष Tasks RCU settings.
 */
अटल व्योम __init rcu_tasks_bootup_oddness(व्योम)
अणु
#अगर defined(CONFIG_TASKS_RCU) || defined(CONFIG_TASKS_TRACE_RCU)
	अगर (rcu_task_stall_समयout != RCU_TASK_STALL_TIMEOUT)
		pr_info("\tTasks-RCU CPU stall warnings timeout set to %d (rcu_task_stall_timeout).\n", rcu_task_stall_समयout);
#पूर्ण_अगर /* #अगर_घोषित CONFIG_TASKS_RCU */
#अगर_घोषित CONFIG_TASKS_RCU
	pr_info("\tTrampoline variant of Tasks RCU enabled.\n");
#पूर्ण_अगर /* #अगर_घोषित CONFIG_TASKS_RCU */
#अगर_घोषित CONFIG_TASKS_RUDE_RCU
	pr_info("\tRude variant of Tasks RCU enabled.\n");
#पूर्ण_अगर /* #अगर_घोषित CONFIG_TASKS_RUDE_RCU */
#अगर_घोषित CONFIG_TASKS_TRACE_RCU
	pr_info("\tTracing variant of Tasks RCU enabled.\n");
#पूर्ण_अगर /* #अगर_घोषित CONFIG_TASKS_TRACE_RCU */
पूर्ण

#पूर्ण_अगर /* #अगर_अघोषित CONFIG_TINY_RCU */

#अगर_अघोषित CONFIG_TINY_RCU
/* Dump out rcutorture-relevant state common to all RCU-tasks flavors. */
अटल व्योम show_rcu_tasks_generic_gp_kthपढ़ो(काष्ठा rcu_tasks *rtp, अक्षर *s)
अणु
	pr_info("%s: %s(%d) since %lu g:%lu i:%lu/%lu %c%c %s\n",
		rtp->kname,
		tasks_gp_state_getname(rtp), data_race(rtp->gp_state),
		jअगरfies - data_race(rtp->gp_jअगरfies),
		data_race(rtp->n_gps),
		data_race(rtp->n_ipis_fails), data_race(rtp->n_ipis),
		".k"[!!data_race(rtp->kthपढ़ो_ptr)],
		".C"[!!data_race(rtp->cbs_head)],
		s);
पूर्ण
#पूर्ण_अगर // #अगर_अघोषित CONFIG_TINY_RCU

अटल व्योम निकास_tasks_rcu_finish_trace(काष्ठा task_काष्ठा *t);

#अगर defined(CONFIG_TASKS_RCU) || defined(CONFIG_TASKS_TRACE_RCU)

////////////////////////////////////////////////////////////////////////
//
// Shared code between task-list-scanning variants of Tasks RCU.

/* Wait क्रम one RCU-tasks grace period. */
अटल व्योम rcu_tasks_रुको_gp(काष्ठा rcu_tasks *rtp)
अणु
	काष्ठा task_काष्ठा *g, *t;
	अचिन्हित दीर्घ lastreport;
	LIST_HEAD(holकरोuts);
	पूर्णांक fract;

	set_tasks_gp_state(rtp, RTGS_PRE_WAIT_GP);
	rtp->pregp_func();

	/*
	 * There were callbacks, so we need to रुको क्रम an RCU-tasks
	 * grace period.  Start off by scanning the task list क्रम tasks
	 * that are not alपढ़ोy voluntarily blocked.  Mark these tasks
	 * and make a list of them in holकरोuts.
	 */
	set_tasks_gp_state(rtp, RTGS_SCAN_TASKLIST);
	rcu_पढ़ो_lock();
	क्रम_each_process_thपढ़ो(g, t)
		rtp->pertask_func(t, &holकरोuts);
	rcu_पढ़ो_unlock();

	set_tasks_gp_state(rtp, RTGS_POST_SCAN_TASKLIST);
	rtp->postscan_func(&holकरोuts);

	/*
	 * Each pass through the following loop scans the list of holकरोut
	 * tasks, removing any that are no दीर्घer holकरोuts.  When the list
	 * is empty, we are करोne.
	 */
	lastreport = jअगरfies;

	// Start off with initial रुको and slowly back off to 1 HZ रुको.
	fract = rtp->init_fract;

	जबतक (!list_empty(&holकरोuts)) अणु
		bool firstreport;
		bool needreport;
		पूर्णांक rtst;

		/* Slowly back off रुकोing क्रम holकरोuts */
		set_tasks_gp_state(rtp, RTGS_WAIT_SCAN_HOLDOUTS);
		schedule_समयout_idle(fract);

		अगर (fract < HZ)
			fract++;

		rtst = READ_ONCE(rcu_task_stall_समयout);
		needreport = rtst > 0 && समय_after(jअगरfies, lastreport + rtst);
		अगर (needreport)
			lastreport = jअगरfies;
		firstreport = true;
		WARN_ON(संकेत_pending(current));
		set_tasks_gp_state(rtp, RTGS_SCAN_HOLDOUTS);
		rtp->holकरोuts_func(&holकरोuts, needreport, &firstreport);
	पूर्ण

	set_tasks_gp_state(rtp, RTGS_POST_GP);
	rtp->postgp_func(rtp);
पूर्ण

#पूर्ण_अगर /* #अगर defined(CONFIG_TASKS_RCU) || defined(CONFIG_TASKS_TRACE_RCU) */

#अगर_घोषित CONFIG_TASKS_RCU

////////////////////////////////////////////////////////////////////////
//
// Simple variant of RCU whose quiescent states are voluntary context
// चयन, cond_resched_rcu_qs(), user-space execution, and idle.
// As such, grace periods can take one good दीर्घ समय.  There are no
// पढ़ो-side primitives similar to rcu_पढ़ो_lock() and rcu_पढ़ो_unlock()
// because this implementation is पूर्णांकended to get the प्रणाली पूर्णांकo a safe
// state क्रम some of the manipulations involved in tracing and the like.
// Finally, this implementation करोes not support high call_rcu_tasks()
// rates from multiple CPUs.  If this is required, per-CPU callback lists
// will be needed.

/* Pre-grace-period preparation. */
अटल व्योम rcu_tasks_pregp_step(व्योम)
अणु
	/*
	 * Wait क्रम all pre-existing t->on_rq and t->nvcsw transitions
	 * to complete.  Invoking synchronize_rcu() suffices because all
	 * these transitions occur with पूर्णांकerrupts disabled.  Without this
	 * synchronize_rcu(), a पढ़ो-side critical section that started
	 * beक्रमe the grace period might be incorrectly seen as having
	 * started after the grace period.
	 *
	 * This synchronize_rcu() also dispenses with the need क्रम a
	 * memory barrier on the first store to t->rcu_tasks_holकरोut,
	 * as it क्रमces the store to happen after the beginning of the
	 * grace period.
	 */
	synchronize_rcu();
पूर्ण

/* Per-task initial processing. */
अटल व्योम rcu_tasks_pertask(काष्ठा task_काष्ठा *t, काष्ठा list_head *hop)
अणु
	अगर (t != current && READ_ONCE(t->on_rq) && !is_idle_task(t)) अणु
		get_task_काष्ठा(t);
		t->rcu_tasks_nvcsw = READ_ONCE(t->nvcsw);
		WRITE_ONCE(t->rcu_tasks_holकरोut, true);
		list_add(&t->rcu_tasks_holकरोut_list, hop);
	पूर्ण
पूर्ण

/* Processing between scanning taskslist and draining the holकरोut list. */
अटल व्योम rcu_tasks_postscan(काष्ठा list_head *hop)
अणु
	/*
	 * Wait क्रम tasks that are in the process of निकासing.  This
	 * करोes only part of the job, ensuring that all tasks that were
	 * previously निकासing reach the poपूर्णांक where they have disabled
	 * preemption, allowing the later synchronize_rcu() to finish
	 * the job.
	 */
	synchronize_srcu(&tasks_rcu_निकास_srcu);
पूर्ण

/* See अगर tasks are still holding out, complain अगर so. */
अटल व्योम check_holकरोut_task(काष्ठा task_काष्ठा *t,
			       bool needreport, bool *firstreport)
अणु
	पूर्णांक cpu;

	अगर (!READ_ONCE(t->rcu_tasks_holकरोut) ||
	    t->rcu_tasks_nvcsw != READ_ONCE(t->nvcsw) ||
	    !READ_ONCE(t->on_rq) ||
	    (IS_ENABLED(CONFIG_NO_HZ_FULL) &&
	     !is_idle_task(t) && t->rcu_tasks_idle_cpu >= 0)) अणु
		WRITE_ONCE(t->rcu_tasks_holकरोut, false);
		list_del_init(&t->rcu_tasks_holकरोut_list);
		put_task_काष्ठा(t);
		वापस;
	पूर्ण
	rcu_request_urgent_qs_task(t);
	अगर (!needreport)
		वापस;
	अगर (*firstreport) अणु
		pr_err("INFO: rcu_tasks detected stalls on tasks:\n");
		*firstreport = false;
	पूर्ण
	cpu = task_cpu(t);
	pr_alert("%p: %c%c nvcsw: %lu/%lu holdout: %d idle_cpu: %d/%d\n",
		 t, ".I"[is_idle_task(t)],
		 "N."[cpu < 0 || !tick_nohz_full_cpu(cpu)],
		 t->rcu_tasks_nvcsw, t->nvcsw, t->rcu_tasks_holकरोut,
		 t->rcu_tasks_idle_cpu, cpu);
	sched_show_task(t);
पूर्ण

/* Scan the holकरोut lists क्रम tasks no दीर्घer holding out. */
अटल व्योम check_all_holकरोut_tasks(काष्ठा list_head *hop,
				    bool needreport, bool *firstreport)
अणु
	काष्ठा task_काष्ठा *t, *t1;

	list_क्रम_each_entry_safe(t, t1, hop, rcu_tasks_holकरोut_list) अणु
		check_holकरोut_task(t, needreport, firstreport);
		cond_resched();
	पूर्ण
पूर्ण

/* Finish off the Tasks-RCU grace period. */
अटल व्योम rcu_tasks_postgp(काष्ठा rcu_tasks *rtp)
अणु
	/*
	 * Because ->on_rq and ->nvcsw are not guaranteed to have a full
	 * memory barriers prior to them in the schedule() path, memory
	 * reordering on other CPUs could cause their RCU-tasks पढ़ो-side
	 * critical sections to extend past the end of the grace period.
	 * However, because these ->nvcsw updates are carried out with
	 * पूर्णांकerrupts disabled, we can use synchronize_rcu() to क्रमce the
	 * needed ordering on all such CPUs.
	 *
	 * This synchronize_rcu() also confines all ->rcu_tasks_holकरोut
	 * accesses to be within the grace period, aव्योमing the need क्रम
	 * memory barriers क्रम ->rcu_tasks_holकरोut accesses.
	 *
	 * In addition, this synchronize_rcu() रुकोs क्रम निकासing tasks
	 * to complete their final preempt_disable() region of execution,
	 * cleaning up after the synchronize_srcu() above.
	 */
	synchronize_rcu();
पूर्ण

व्योम call_rcu_tasks(काष्ठा rcu_head *rhp, rcu_callback_t func);
DEFINE_RCU_TASKS(rcu_tasks, rcu_tasks_रुको_gp, call_rcu_tasks, "RCU Tasks");

/**
 * call_rcu_tasks() - Queue an RCU क्रम invocation task-based grace period
 * @rhp: काष्ठाure to be used क्रम queueing the RCU updates.
 * @func: actual callback function to be invoked after the grace period
 *
 * The callback function will be invoked some समय after a full grace
 * period elapses, in other words after all currently executing RCU
 * पढ़ो-side critical sections have completed. call_rcu_tasks() assumes
 * that the पढ़ो-side critical sections end at a voluntary context
 * चयन (not a preemption!), cond_resched_rcu_qs(), entry पूर्णांकo idle,
 * or transition to usermode execution.  As such, there are no पढ़ो-side
 * primitives analogous to rcu_पढ़ो_lock() and rcu_पढ़ो_unlock() because
 * this primitive is पूर्णांकended to determine that all tasks have passed
 * through a safe state, not so much क्रम data-strcuture synchronization.
 *
 * See the description of call_rcu() क्रम more detailed inक्रमmation on
 * memory ordering guarantees.
 */
व्योम call_rcu_tasks(काष्ठा rcu_head *rhp, rcu_callback_t func)
अणु
	call_rcu_tasks_generic(rhp, func, &rcu_tasks);
पूर्ण
EXPORT_SYMBOL_GPL(call_rcu_tasks);

/**
 * synchronize_rcu_tasks - रुको until an rcu-tasks grace period has elapsed.
 *
 * Control will वापस to the caller some समय after a full rcu-tasks
 * grace period has elapsed, in other words after all currently
 * executing rcu-tasks पढ़ो-side critical sections have elapsed.  These
 * पढ़ो-side critical sections are delimited by calls to schedule(),
 * cond_resched_tasks_rcu_qs(), idle execution, userspace execution, calls
 * to synchronize_rcu_tasks(), and (in theory, anyway) cond_resched().
 *
 * This is a very specialized primitive, पूर्णांकended only क्रम a few uses in
 * tracing and other situations requiring manipulation of function
 * preambles and profiling hooks.  The synchronize_rcu_tasks() function
 * is not (yet) पूर्णांकended क्रम heavy use from multiple CPUs.
 *
 * See the description of synchronize_rcu() क्रम more detailed inक्रमmation
 * on memory ordering guarantees.
 */
व्योम synchronize_rcu_tasks(व्योम)
अणु
	synchronize_rcu_tasks_generic(&rcu_tasks);
पूर्ण
EXPORT_SYMBOL_GPL(synchronize_rcu_tasks);

/**
 * rcu_barrier_tasks - Wait क्रम in-flight call_rcu_tasks() callbacks.
 *
 * Although the current implementation is guaranteed to रुको, it is not
 * obligated to, क्रम example, अगर there are no pending callbacks.
 */
व्योम rcu_barrier_tasks(व्योम)
अणु
	/* There is only one callback queue, so this is easy.  ;-) */
	synchronize_rcu_tasks();
पूर्ण
EXPORT_SYMBOL_GPL(rcu_barrier_tasks);

अटल पूर्णांक __init rcu_spawn_tasks_kthपढ़ो(व्योम)
अणु
	rcu_tasks.gp_sleep = HZ / 10;
	rcu_tasks.init_fract = HZ / 10;
	rcu_tasks.pregp_func = rcu_tasks_pregp_step;
	rcu_tasks.pertask_func = rcu_tasks_pertask;
	rcu_tasks.postscan_func = rcu_tasks_postscan;
	rcu_tasks.holकरोuts_func = check_all_holकरोut_tasks;
	rcu_tasks.postgp_func = rcu_tasks_postgp;
	rcu_spawn_tasks_kthपढ़ो_generic(&rcu_tasks);
	वापस 0;
पूर्ण

#अगर !defined(CONFIG_TINY_RCU)
व्योम show_rcu_tasks_classic_gp_kthपढ़ो(व्योम)
अणु
	show_rcu_tasks_generic_gp_kthपढ़ो(&rcu_tasks, "");
पूर्ण
EXPORT_SYMBOL_GPL(show_rcu_tasks_classic_gp_kthपढ़ो);
#पूर्ण_अगर // !defined(CONFIG_TINY_RCU)

/* Do the srcu_पढ़ो_lock() क्रम the above synchronize_srcu().  */
व्योम निकास_tasks_rcu_start(व्योम) __acquires(&tasks_rcu_निकास_srcu)
अणु
	preempt_disable();
	current->rcu_tasks_idx = __srcu_पढ़ो_lock(&tasks_rcu_निकास_srcu);
	preempt_enable();
पूर्ण

/* Do the srcu_पढ़ो_unlock() क्रम the above synchronize_srcu().  */
व्योम निकास_tasks_rcu_finish(व्योम) __releases(&tasks_rcu_निकास_srcu)
अणु
	काष्ठा task_काष्ठा *t = current;

	preempt_disable();
	__srcu_पढ़ो_unlock(&tasks_rcu_निकास_srcu, t->rcu_tasks_idx);
	preempt_enable();
	निकास_tasks_rcu_finish_trace(t);
पूर्ण

#अन्यथा /* #अगर_घोषित CONFIG_TASKS_RCU */
व्योम निकास_tasks_rcu_start(व्योम) अणु पूर्ण
व्योम निकास_tasks_rcu_finish(व्योम) अणु निकास_tasks_rcu_finish_trace(current); पूर्ण
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_TASKS_RCU */

#अगर_घोषित CONFIG_TASKS_RUDE_RCU

////////////////////////////////////////////////////////////////////////
//
// "Rude" variant of Tasks RCU, inspired by Steve Rostedt's trick of
// passing an empty function to schedule_on_each_cpu().  This approach
// provides an asynchronous call_rcu_tasks_rude() API and batching
// of concurrent calls to the synchronous synchronize_rcu_rude() API.
// This sends IPIs far and wide and induces otherwise unnecessary context
// चयनes on all online CPUs, whether idle or not.

// Empty function to allow workqueues to क्रमce a context चयन.
अटल व्योम rcu_tasks_be_rude(काष्ठा work_काष्ठा *work)
अणु
पूर्ण

// Wait क्रम one rude RCU-tasks grace period.
अटल व्योम rcu_tasks_rude_रुको_gp(काष्ठा rcu_tasks *rtp)
अणु
	rtp->n_ipis += cpumask_weight(cpu_online_mask);
	schedule_on_each_cpu(rcu_tasks_be_rude);
पूर्ण

व्योम call_rcu_tasks_rude(काष्ठा rcu_head *rhp, rcu_callback_t func);
DEFINE_RCU_TASKS(rcu_tasks_rude, rcu_tasks_rude_रुको_gp, call_rcu_tasks_rude,
		 "RCU Tasks Rude");

/**
 * call_rcu_tasks_rude() - Queue a callback rude task-based grace period
 * @rhp: काष्ठाure to be used क्रम queueing the RCU updates.
 * @func: actual callback function to be invoked after the grace period
 *
 * The callback function will be invoked some समय after a full grace
 * period elapses, in other words after all currently executing RCU
 * पढ़ो-side critical sections have completed. call_rcu_tasks_rude()
 * assumes that the पढ़ो-side critical sections end at context चयन,
 * cond_resched_rcu_qs(), or transition to usermode execution.  As such,
 * there are no पढ़ो-side primitives analogous to rcu_पढ़ो_lock() and
 * rcu_पढ़ो_unlock() because this primitive is पूर्णांकended to determine
 * that all tasks have passed through a safe state, not so much क्रम
 * data-strcuture synchronization.
 *
 * See the description of call_rcu() क्रम more detailed inक्रमmation on
 * memory ordering guarantees.
 */
व्योम call_rcu_tasks_rude(काष्ठा rcu_head *rhp, rcu_callback_t func)
अणु
	call_rcu_tasks_generic(rhp, func, &rcu_tasks_rude);
पूर्ण
EXPORT_SYMBOL_GPL(call_rcu_tasks_rude);

/**
 * synchronize_rcu_tasks_rude - रुको क्रम a rude rcu-tasks grace period
 *
 * Control will वापस to the caller some समय after a rude rcu-tasks
 * grace period has elapsed, in other words after all currently
 * executing rcu-tasks पढ़ो-side critical sections have elapsed.  These
 * पढ़ो-side critical sections are delimited by calls to schedule(),
 * cond_resched_tasks_rcu_qs(), userspace execution, and (in theory,
 * anyway) cond_resched().
 *
 * This is a very specialized primitive, पूर्णांकended only क्रम a few uses in
 * tracing and other situations requiring manipulation of function preambles
 * and profiling hooks.  The synchronize_rcu_tasks_rude() function is not
 * (yet) पूर्णांकended क्रम heavy use from multiple CPUs.
 *
 * See the description of synchronize_rcu() क्रम more detailed inक्रमmation
 * on memory ordering guarantees.
 */
व्योम synchronize_rcu_tasks_rude(व्योम)
अणु
	synchronize_rcu_tasks_generic(&rcu_tasks_rude);
पूर्ण
EXPORT_SYMBOL_GPL(synchronize_rcu_tasks_rude);

/**
 * rcu_barrier_tasks_rude - Wait क्रम in-flight call_rcu_tasks_rude() callbacks.
 *
 * Although the current implementation is guaranteed to रुको, it is not
 * obligated to, क्रम example, अगर there are no pending callbacks.
 */
व्योम rcu_barrier_tasks_rude(व्योम)
अणु
	/* There is only one callback queue, so this is easy.  ;-) */
	synchronize_rcu_tasks_rude();
पूर्ण
EXPORT_SYMBOL_GPL(rcu_barrier_tasks_rude);

अटल पूर्णांक __init rcu_spawn_tasks_rude_kthपढ़ो(व्योम)
अणु
	rcu_tasks_rude.gp_sleep = HZ / 10;
	rcu_spawn_tasks_kthपढ़ो_generic(&rcu_tasks_rude);
	वापस 0;
पूर्ण

#अगर !defined(CONFIG_TINY_RCU)
व्योम show_rcu_tasks_rude_gp_kthपढ़ो(व्योम)
अणु
	show_rcu_tasks_generic_gp_kthपढ़ो(&rcu_tasks_rude, "");
पूर्ण
EXPORT_SYMBOL_GPL(show_rcu_tasks_rude_gp_kthपढ़ो);
#पूर्ण_अगर // !defined(CONFIG_TINY_RCU)
#पूर्ण_अगर /* #अगर_घोषित CONFIG_TASKS_RUDE_RCU */

////////////////////////////////////////////////////////////////////////
//
// Tracing variant of Tasks RCU.  This variant is deचिन्हित to be used
// to protect tracing hooks, including those of BPF.  This variant
// thereक्रमe:
//
// 1.	Has explicit पढ़ो-side markers to allow finite grace periods
//	in the face of in-kernel loops क्रम PREEMPT=n builds.
//
// 2.	Protects code in the idle loop, exception entry/निकास, and
//	CPU-hotplug code paths, similar to the capabilities of SRCU.
//
// 3.	Aव्योमs expensive पढ़ो-side inकाष्ठाion, having overhead similar
//	to that of Preemptible RCU.
//
// There are of course करोwnsides.  The grace-period code can send IPIs to
// CPUs, even when those CPUs are in the idle loop or in nohz_full userspace.
// It is necessary to scan the full tasklist, much as क्रम Tasks RCU.  There
// is a single callback queue guarded by a single lock, again, much as क्रम
// Tasks RCU.  If needed, these करोwnsides can be at least partially remedied.
//
// Perhaps most important, this variant of RCU करोes not affect the vanilla
// flavors, rcu_preempt and rcu_sched.  The fact that RCU Tasks Trace
// पढ़ोers can operate from idle, offline, and exception entry/निकास in no
// way allows rcu_preempt and rcu_sched पढ़ोers to also करो so.
//
// The implementation uses rcu_tasks_रुको_gp(), which relies on function
// poपूर्णांकers in the rcu_tasks काष्ठाure.  The rcu_spawn_tasks_trace_kthपढ़ो()
// function sets these function poपूर्णांकers up so that rcu_tasks_रुको_gp()
// invokes these functions in this order:
//
// rcu_tasks_trace_pregp_step():
//	Initialize the count of पढ़ोers and block CPU-hotplug operations.
// rcu_tasks_trace_pertask(), invoked on every non-idle task:
//	Initialize per-task state and attempt to identअगरy an immediate
//	quiescent state क्रम that task, or, failing that, attempt to
//	set that task's .need_qs flag so that task's next outermost
//	rcu_पढ़ो_unlock_trace() will report the quiescent state (in which
//	हाल the count of पढ़ोers is incremented).  If both attempts fail,
//	the task is added to a "holdout" list.
// rcu_tasks_trace_postscan():
//	Initialize state and attempt to identअगरy an immediate quiescent
//	state as above (but only क्रम idle tasks), unblock CPU-hotplug
//	operations, and रुको क्रम an RCU grace period to aव्योम races with
//	tasks that are in the process of निकासing.
// check_all_holकरोut_tasks_trace(), repeatedly until holकरोut list is empty:
//	Scans the holकरोut list, attempting to identअगरy a quiescent state
//	क्रम each task on the list.  If there is a quiescent state, the
//	corresponding task is हटाओd from the holकरोut list.
// rcu_tasks_trace_postgp():
//	Wait क्रम the count of पढ़ोers करो drop to zero, reporting any stalls.
//	Also execute full memory barriers to मुख्यtain ordering with code
//	executing after the grace period.
//
// The निकास_tasks_rcu_finish_trace() synchronizes with निकासing tasks.
//
// Pre-grace-period update-side code is ordered beक्रमe the grace
// period via the ->cbs_lock and barriers in rcu_tasks_kthपढ़ो().
// Pre-grace-period पढ़ो-side code is ordered beक्रमe the grace period by
// atomic_dec_and_test() of the count of पढ़ोers (क्रम IPIed पढ़ोers) and by
// scheduler context-चयन ordering (क्रम locked-करोwn non-running पढ़ोers).

// The lockdep state must be outside of #अगर_घोषित to be useful.
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
अटल काष्ठा lock_class_key rcu_lock_trace_key;
काष्ठा lockdep_map rcu_trace_lock_map =
	STATIC_LOCKDEP_MAP_INIT("rcu_read_lock_trace", &rcu_lock_trace_key);
EXPORT_SYMBOL_GPL(rcu_trace_lock_map);
#पूर्ण_अगर /* #अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC */

#अगर_घोषित CONFIG_TASKS_TRACE_RCU

अटल atomic_t trc_n_पढ़ोers_need_end;		// Number of रुकोed-क्रम पढ़ोers.
अटल DECLARE_WAIT_QUEUE_HEAD(trc_रुको);	// List of holकरोut tasks.

// Record outstanding IPIs to each CPU.  No poपूर्णांक in sending two...
अटल DEFINE_PER_CPU(bool, trc_ipi_to_cpu);

// The number of detections of task quiescent state relying on
// heavyweight पढ़ोers executing explicit memory barriers.
अटल अचिन्हित दीर्घ n_heavy_पढ़ोer_attempts;
अटल अचिन्हित दीर्घ n_heavy_पढ़ोer_updates;
अटल अचिन्हित दीर्घ n_heavy_पढ़ोer_ofl_updates;

व्योम call_rcu_tasks_trace(काष्ठा rcu_head *rhp, rcu_callback_t func);
DEFINE_RCU_TASKS(rcu_tasks_trace, rcu_tasks_रुको_gp, call_rcu_tasks_trace,
		 "RCU Tasks Trace");

/*
 * This irq_work handler allows rcu_पढ़ो_unlock_trace() to be invoked
 * जबतक the scheduler locks are held.
 */
अटल व्योम rcu_पढ़ो_unlock_iw(काष्ठा irq_work *iwp)
अणु
	wake_up(&trc_रुको);
पूर्ण
अटल DEFINE_IRQ_WORK(rcu_tasks_trace_iw, rcu_पढ़ो_unlock_iw);

/* If we are the last पढ़ोer, wake up the grace-period kthपढ़ो. */
व्योम rcu_पढ़ो_unlock_trace_special(काष्ठा task_काष्ठा *t, पूर्णांक nesting)
अणु
	पूर्णांक nq = t->trc_पढ़ोer_special.b.need_qs;

	अगर (IS_ENABLED(CONFIG_TASKS_TRACE_RCU_READ_MB) &&
	    t->trc_पढ़ोer_special.b.need_mb)
		smp_mb(); // Pairs with update-side barriers.
	// Update .need_qs beक्रमe ->trc_पढ़ोer_nesting क्रम irq/NMI handlers.
	अगर (nq)
		WRITE_ONCE(t->trc_पढ़ोer_special.b.need_qs, false);
	WRITE_ONCE(t->trc_पढ़ोer_nesting, nesting);
	अगर (nq && atomic_dec_and_test(&trc_n_पढ़ोers_need_end))
		irq_work_queue(&rcu_tasks_trace_iw);
पूर्ण
EXPORT_SYMBOL_GPL(rcu_पढ़ो_unlock_trace_special);

/* Add a task to the holकरोut list, अगर it is not alपढ़ोy on the list. */
अटल व्योम trc_add_holकरोut(काष्ठा task_काष्ठा *t, काष्ठा list_head *bhp)
अणु
	अगर (list_empty(&t->trc_holकरोut_list)) अणु
		get_task_काष्ठा(t);
		list_add(&t->trc_holकरोut_list, bhp);
	पूर्ण
पूर्ण

/* Remove a task from the holकरोut list, अगर it is in fact present. */
अटल व्योम trc_del_holकरोut(काष्ठा task_काष्ठा *t)
अणु
	अगर (!list_empty(&t->trc_holकरोut_list)) अणु
		list_del_init(&t->trc_holकरोut_list);
		put_task_काष्ठा(t);
	पूर्ण
पूर्ण

/* IPI handler to check task state. */
अटल व्योम trc_पढ़ो_check_handler(व्योम *t_in)
अणु
	काष्ठा task_काष्ठा *t = current;
	काष्ठा task_काष्ठा *texp = t_in;

	// If the task is no दीर्घer running on this CPU, leave.
	अगर (unlikely(texp != t)) अणु
		अगर (WARN_ON_ONCE(atomic_dec_and_test(&trc_n_पढ़ोers_need_end)))
			wake_up(&trc_रुको);
		जाओ reset_ipi; // Alपढ़ोy on holकरोut list, so will check later.
	पूर्ण

	// If the task is not in a पढ़ो-side critical section, and
	// अगर this is the last पढ़ोer, awaken the grace-period kthपढ़ो.
	अगर (likely(!t->trc_पढ़ोer_nesting)) अणु
		अगर (WARN_ON_ONCE(atomic_dec_and_test(&trc_n_पढ़ोers_need_end)))
			wake_up(&trc_रुको);
		// Mark as checked after decrement to aव्योम false
		// positives on the above WARN_ON_ONCE().
		WRITE_ONCE(t->trc_पढ़ोer_checked, true);
		जाओ reset_ipi;
	पूर्ण
	// If we are racing with an rcu_पढ़ो_unlock_trace(), try again later.
	अगर (unlikely(t->trc_पढ़ोer_nesting < 0)) अणु
		अगर (WARN_ON_ONCE(atomic_dec_and_test(&trc_n_पढ़ोers_need_end)))
			wake_up(&trc_रुको);
		जाओ reset_ipi;
	पूर्ण
	WRITE_ONCE(t->trc_पढ़ोer_checked, true);

	// Get here अगर the task is in a पढ़ो-side critical section.  Set
	// its state so that it will awaken the grace-period kthपढ़ो upon
	// निकास from that critical section.
	WARN_ON_ONCE(t->trc_पढ़ोer_special.b.need_qs);
	WRITE_ONCE(t->trc_पढ़ोer_special.b.need_qs, true);

reset_ipi:
	// Allow future IPIs to be sent on CPU and क्रम task.
	// Also order this IPI handler against any later manipulations of
	// the पूर्णांकended task.
	smp_store_release(&per_cpu(trc_ipi_to_cpu, smp_processor_id()), false); // ^^^
	smp_store_release(&texp->trc_ipi_to_cpu, -1); // ^^^
पूर्ण

/* Callback function क्रम scheduler to check locked-करोwn task.  */
अटल bool trc_inspect_पढ़ोer(काष्ठा task_काष्ठा *t, व्योम *arg)
अणु
	पूर्णांक cpu = task_cpu(t);
	bool in_qs = false;
	bool ofl = cpu_is_offline(cpu);

	अगर (task_curr(t)) अणु
		WARN_ON_ONCE(ofl && !is_idle_task(t));

		// If no chance of heavyweight पढ़ोers, करो it the hard way.
		अगर (!ofl && !IS_ENABLED(CONFIG_TASKS_TRACE_RCU_READ_MB))
			वापस false;

		// If heavyweight पढ़ोers are enabled on the remote task,
		// we can inspect its state despite its currently running.
		// However, we cannot safely change its state.
		n_heavy_पढ़ोer_attempts++;
		अगर (!ofl && // Check क्रम "running" idle tasks on offline CPUs.
		    !rcu_dynticks_zero_in_eqs(cpu, &t->trc_पढ़ोer_nesting))
			वापस false; // No quiescent state, करो it the hard way.
		n_heavy_पढ़ोer_updates++;
		अगर (ofl)
			n_heavy_पढ़ोer_ofl_updates++;
		in_qs = true;
	पूर्ण अन्यथा अणु
		in_qs = likely(!t->trc_पढ़ोer_nesting);
	पूर्ण

	// Mark as checked.  Because this is called from the grace-period
	// kthपढ़ो, also हटाओ the task from the holकरोut list.
	t->trc_पढ़ोer_checked = true;
	trc_del_holकरोut(t);

	अगर (in_qs)
		वापस true;  // Alपढ़ोy in quiescent state, करोne!!!

	// The task is in a पढ़ो-side critical section, so set up its
	// state so that it will awaken the grace-period kthपढ़ो upon निकास
	// from that critical section.
	atomic_inc(&trc_n_पढ़ोers_need_end); // One more to रुको on.
	WARN_ON_ONCE(t->trc_पढ़ोer_special.b.need_qs);
	WRITE_ONCE(t->trc_पढ़ोer_special.b.need_qs, true);
	वापस true;
पूर्ण

/* Attempt to extract the state क्रम the specअगरied task. */
अटल व्योम trc_रुको_क्रम_one_पढ़ोer(काष्ठा task_काष्ठा *t,
				    काष्ठा list_head *bhp)
अणु
	पूर्णांक cpu;

	// If a previous IPI is still in flight, let it complete.
	अगर (smp_load_acquire(&t->trc_ipi_to_cpu) != -1) // Order IPI
		वापस;

	// The current task had better be in a quiescent state.
	अगर (t == current) अणु
		t->trc_पढ़ोer_checked = true;
		trc_del_holकरोut(t);
		WARN_ON_ONCE(t->trc_पढ़ोer_nesting);
		वापस;
	पूर्ण

	// Attempt to nail करोwn the task क्रम inspection.
	get_task_काष्ठा(t);
	अगर (try_invoke_on_locked_करोwn_task(t, trc_inspect_पढ़ोer, शून्य)) अणु
		put_task_काष्ठा(t);
		वापस;
	पूर्ण
	put_task_काष्ठा(t);

	// If currently running, send an IPI, either way, add to list.
	trc_add_holकरोut(t, bhp);
	अगर (task_curr(t) &&
	    समय_after(jअगरfies + 1, rcu_tasks_trace.gp_start + rcu_task_ipi_delay)) अणु
		// The task is currently running, so try IPIing it.
		cpu = task_cpu(t);

		// If there is alपढ़ोy an IPI outstanding, let it happen.
		अगर (per_cpu(trc_ipi_to_cpu, cpu) || t->trc_ipi_to_cpu >= 0)
			वापस;

		atomic_inc(&trc_n_पढ़ोers_need_end);
		per_cpu(trc_ipi_to_cpu, cpu) = true;
		t->trc_ipi_to_cpu = cpu;
		rcu_tasks_trace.n_ipis++;
		अगर (smp_call_function_single(cpu,
					     trc_पढ़ो_check_handler, t, 0)) अणु
			// Just in हाल there is some other reason क्रम
			// failure than the target CPU being offline.
			rcu_tasks_trace.n_ipis_fails++;
			per_cpu(trc_ipi_to_cpu, cpu) = false;
			t->trc_ipi_to_cpu = cpu;
			अगर (atomic_dec_and_test(&trc_n_पढ़ोers_need_end)) अणु
				WARN_ON_ONCE(1);
				wake_up(&trc_रुको);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Initialize क्रम a new RCU-tasks-trace grace period. */
अटल व्योम rcu_tasks_trace_pregp_step(व्योम)
अणु
	पूर्णांक cpu;

	// Allow क्रम fast-acting IPIs.
	atomic_set(&trc_n_पढ़ोers_need_end, 1);

	// There shouldn't be any old IPIs, but...
	क्रम_each_possible_cpu(cpu)
		WARN_ON_ONCE(per_cpu(trc_ipi_to_cpu, cpu));

	// Disable CPU hotplug across the tasklist scan.
	// This also रुकोs क्रम all पढ़ोers in CPU-hotplug code paths.
	cpus_पढ़ो_lock();
पूर्ण

/* Do first-round processing क्रम the specअगरied task. */
अटल व्योम rcu_tasks_trace_pertask(काष्ठा task_काष्ठा *t,
				    काष्ठा list_head *hop)
अणु
	// During early boot when there is only the one boot CPU, there
	// is no idle task क्रम the other CPUs. Just वापस.
	अगर (unlikely(t == शून्य))
		वापस;

	WRITE_ONCE(t->trc_पढ़ोer_special.b.need_qs, false);
	WRITE_ONCE(t->trc_पढ़ोer_checked, false);
	t->trc_ipi_to_cpu = -1;
	trc_रुको_क्रम_one_पढ़ोer(t, hop);
पूर्ण

/*
 * Do पूर्णांकermediate processing between task and holकरोut scans and
 * pick up the idle tasks.
 */
अटल व्योम rcu_tasks_trace_postscan(काष्ठा list_head *hop)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		rcu_tasks_trace_pertask(idle_task(cpu), hop);

	// Re-enable CPU hotplug now that the tasklist scan has completed.
	cpus_पढ़ो_unlock();

	// Wait क्रम late-stage निकासing tasks to finish निकासing.
	// These might have passed the call to निकास_tasks_rcu_finish().
	synchronize_rcu();
	// Any tasks that निकास after this poपूर्णांक will set ->trc_पढ़ोer_checked.
पूर्ण

/* Show the state of a task stalling the current RCU tasks trace GP. */
अटल व्योम show_stalled_task_trace(काष्ठा task_काष्ठा *t, bool *firstreport)
अणु
	पूर्णांक cpu;

	अगर (*firstreport) अणु
		pr_err("INFO: rcu_tasks_trace detected stalls on tasks:\n");
		*firstreport = false;
	पूर्ण
	// FIXME: This should attempt to use try_invoke_on_nonrunning_task().
	cpu = task_cpu(t);
	pr_alert("P%d: %c%c%c nesting: %d%c cpu: %d\n",
		 t->pid,
		 ".I"[READ_ONCE(t->trc_ipi_to_cpu) > 0],
		 ".i"[is_idle_task(t)],
		 ".N"[cpu > 0 && tick_nohz_full_cpu(cpu)],
		 t->trc_पढ़ोer_nesting,
		 " N"[!!t->trc_पढ़ोer_special.b.need_qs],
		 cpu);
	sched_show_task(t);
पूर्ण

/* List stalled IPIs क्रम RCU tasks trace. */
अटल व्योम show_stalled_ipi_trace(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		अगर (per_cpu(trc_ipi_to_cpu, cpu))
			pr_alert("\tIPI outstanding to CPU %d\n", cpu);
पूर्ण

/* Do one scan of the holकरोut list. */
अटल व्योम check_all_holकरोut_tasks_trace(काष्ठा list_head *hop,
					  bool needreport, bool *firstreport)
अणु
	काष्ठा task_काष्ठा *g, *t;

	// Disable CPU hotplug across the holकरोut list scan.
	cpus_पढ़ो_lock();

	list_क्रम_each_entry_safe(t, g, hop, trc_holकरोut_list) अणु
		// If safe and needed, try to check the current task.
		अगर (READ_ONCE(t->trc_ipi_to_cpu) == -1 &&
		    !READ_ONCE(t->trc_पढ़ोer_checked))
			trc_रुको_क्रम_one_पढ़ोer(t, hop);

		// If check succeeded, हटाओ this task from the list.
		अगर (READ_ONCE(t->trc_पढ़ोer_checked))
			trc_del_holकरोut(t);
		अन्यथा अगर (needreport)
			show_stalled_task_trace(t, firstreport);
	पूर्ण

	// Re-enable CPU hotplug now that the holकरोut list scan has completed.
	cpus_पढ़ो_unlock();

	अगर (needreport) अणु
		अगर (firstreport)
			pr_err("INFO: rcu_tasks_trace detected stalls? (Late IPI?)\n");
		show_stalled_ipi_trace();
	पूर्ण
पूर्ण

/* Wait क्रम grace period to complete and provide ordering. */
अटल व्योम rcu_tasks_trace_postgp(काष्ठा rcu_tasks *rtp)
अणु
	bool firstreport;
	काष्ठा task_काष्ठा *g, *t;
	LIST_HEAD(holकरोuts);
	दीर्घ ret;

	// Remove the safety count.
	smp_mb__beक्रमe_atomic();  // Order vs. earlier atomics
	atomic_dec(&trc_n_पढ़ोers_need_end);
	smp_mb__after_atomic();  // Order vs. later atomics

	// Wait क्रम पढ़ोers.
	set_tasks_gp_state(rtp, RTGS_WAIT_READERS);
	क्रम (;;) अणु
		ret = रुको_event_idle_exclusive_समयout(
				trc_रुको,
				atomic_पढ़ो(&trc_n_पढ़ोers_need_end) == 0,
				READ_ONCE(rcu_task_stall_समयout));
		अगर (ret)
			अवरोध;  // Count reached zero.
		// Stall warning समय, so make a list of the offenders.
		rcu_पढ़ो_lock();
		क्रम_each_process_thपढ़ो(g, t)
			अगर (READ_ONCE(t->trc_पढ़ोer_special.b.need_qs))
				trc_add_holकरोut(t, &holकरोuts);
		rcu_पढ़ो_unlock();
		firstreport = true;
		list_क्रम_each_entry_safe(t, g, &holकरोuts, trc_holकरोut_list) अणु
			अगर (READ_ONCE(t->trc_पढ़ोer_special.b.need_qs))
				show_stalled_task_trace(t, &firstreport);
			trc_del_holकरोut(t); // Release task_काष्ठा reference.
		पूर्ण
		अगर (firstreport)
			pr_err("INFO: rcu_tasks_trace detected stalls? (Counter/taskslist mismatch?)\n");
		show_stalled_ipi_trace();
		pr_err("\t%d holdouts\n", atomic_पढ़ो(&trc_n_पढ़ोers_need_end));
	पूर्ण
	smp_mb(); // Caller's code must be ordered after wakeup.
		  // Pairs with pretty much every ordering primitive.
पूर्ण

/* Report any needed quiescent state क्रम this निकासing task. */
अटल व्योम निकास_tasks_rcu_finish_trace(काष्ठा task_काष्ठा *t)
अणु
	WRITE_ONCE(t->trc_पढ़ोer_checked, true);
	WARN_ON_ONCE(t->trc_पढ़ोer_nesting);
	WRITE_ONCE(t->trc_पढ़ोer_nesting, 0);
	अगर (WARN_ON_ONCE(READ_ONCE(t->trc_पढ़ोer_special.b.need_qs)))
		rcu_पढ़ो_unlock_trace_special(t, 0);
पूर्ण

/**
 * call_rcu_tasks_trace() - Queue a callback trace task-based grace period
 * @rhp: काष्ठाure to be used क्रम queueing the RCU updates.
 * @func: actual callback function to be invoked after the grace period
 *
 * The callback function will be invoked some समय after a full grace
 * period elapses, in other words after all currently executing RCU
 * पढ़ो-side critical sections have completed. call_rcu_tasks_trace()
 * assumes that the पढ़ो-side critical sections end at context चयन,
 * cond_resched_rcu_qs(), or transition to usermode execution.  As such,
 * there are no पढ़ो-side primitives analogous to rcu_पढ़ो_lock() and
 * rcu_पढ़ो_unlock() because this primitive is पूर्णांकended to determine
 * that all tasks have passed through a safe state, not so much क्रम
 * data-strcuture synchronization.
 *
 * See the description of call_rcu() क्रम more detailed inक्रमmation on
 * memory ordering guarantees.
 */
व्योम call_rcu_tasks_trace(काष्ठा rcu_head *rhp, rcu_callback_t func)
अणु
	call_rcu_tasks_generic(rhp, func, &rcu_tasks_trace);
पूर्ण
EXPORT_SYMBOL_GPL(call_rcu_tasks_trace);

/**
 * synchronize_rcu_tasks_trace - रुको क्रम a trace rcu-tasks grace period
 *
 * Control will वापस to the caller some समय after a trace rcu-tasks
 * grace period has elapsed, in other words after all currently executing
 * rcu-tasks पढ़ो-side critical sections have elapsed.  These पढ़ो-side
 * critical sections are delimited by calls to rcu_पढ़ो_lock_trace()
 * and rcu_पढ़ो_unlock_trace().
 *
 * This is a very specialized primitive, पूर्णांकended only क्रम a few uses in
 * tracing and other situations requiring manipulation of function preambles
 * and profiling hooks.  The synchronize_rcu_tasks_trace() function is not
 * (yet) पूर्णांकended क्रम heavy use from multiple CPUs.
 *
 * See the description of synchronize_rcu() क्रम more detailed inक्रमmation
 * on memory ordering guarantees.
 */
व्योम synchronize_rcu_tasks_trace(व्योम)
अणु
	RCU_LOCKDEP_WARN(lock_is_held(&rcu_trace_lock_map), "Illegal synchronize_rcu_tasks_trace() in RCU Tasks Trace read-side critical section");
	synchronize_rcu_tasks_generic(&rcu_tasks_trace);
पूर्ण
EXPORT_SYMBOL_GPL(synchronize_rcu_tasks_trace);

/**
 * rcu_barrier_tasks_trace - Wait क्रम in-flight call_rcu_tasks_trace() callbacks.
 *
 * Although the current implementation is guaranteed to रुको, it is not
 * obligated to, क्रम example, अगर there are no pending callbacks.
 */
व्योम rcu_barrier_tasks_trace(व्योम)
अणु
	/* There is only one callback queue, so this is easy.  ;-) */
	synchronize_rcu_tasks_trace();
पूर्ण
EXPORT_SYMBOL_GPL(rcu_barrier_tasks_trace);

अटल पूर्णांक __init rcu_spawn_tasks_trace_kthपढ़ो(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_TASKS_TRACE_RCU_READ_MB)) अणु
		rcu_tasks_trace.gp_sleep = HZ / 10;
		rcu_tasks_trace.init_fract = HZ / 10;
	पूर्ण अन्यथा अणु
		rcu_tasks_trace.gp_sleep = HZ / 200;
		अगर (rcu_tasks_trace.gp_sleep <= 0)
			rcu_tasks_trace.gp_sleep = 1;
		rcu_tasks_trace.init_fract = HZ / 200;
		अगर (rcu_tasks_trace.init_fract <= 0)
			rcu_tasks_trace.init_fract = 1;
	पूर्ण
	rcu_tasks_trace.pregp_func = rcu_tasks_trace_pregp_step;
	rcu_tasks_trace.pertask_func = rcu_tasks_trace_pertask;
	rcu_tasks_trace.postscan_func = rcu_tasks_trace_postscan;
	rcu_tasks_trace.holकरोuts_func = check_all_holकरोut_tasks_trace;
	rcu_tasks_trace.postgp_func = rcu_tasks_trace_postgp;
	rcu_spawn_tasks_kthपढ़ो_generic(&rcu_tasks_trace);
	वापस 0;
पूर्ण

#अगर !defined(CONFIG_TINY_RCU)
व्योम show_rcu_tasks_trace_gp_kthपढ़ो(व्योम)
अणु
	अक्षर buf[64];

	प्र_लिखो(buf, "N%d h:%lu/%lu/%lu", atomic_पढ़ो(&trc_n_पढ़ोers_need_end),
		data_race(n_heavy_पढ़ोer_ofl_updates),
		data_race(n_heavy_पढ़ोer_updates),
		data_race(n_heavy_पढ़ोer_attempts));
	show_rcu_tasks_generic_gp_kthपढ़ो(&rcu_tasks_trace, buf);
पूर्ण
EXPORT_SYMBOL_GPL(show_rcu_tasks_trace_gp_kthपढ़ो);
#पूर्ण_अगर // !defined(CONFIG_TINY_RCU)

#अन्यथा /* #अगर_घोषित CONFIG_TASKS_TRACE_RCU */
अटल व्योम निकास_tasks_rcu_finish_trace(काष्ठा task_काष्ठा *t) अणु पूर्ण
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_TASKS_TRACE_RCU */

#अगर_अघोषित CONFIG_TINY_RCU
व्योम show_rcu_tasks_gp_kthपढ़ोs(व्योम)
अणु
	show_rcu_tasks_classic_gp_kthपढ़ो();
	show_rcu_tasks_rude_gp_kthपढ़ो();
	show_rcu_tasks_trace_gp_kthपढ़ो();
पूर्ण
#पूर्ण_अगर /* #अगर_अघोषित CONFIG_TINY_RCU */

#अगर_घोषित CONFIG_PROVE_RCU
काष्ठा rcu_tasks_test_desc अणु
	काष्ठा rcu_head rh;
	स्थिर अक्षर *name;
	bool notrun;
पूर्ण;

अटल काष्ठा rcu_tasks_test_desc tests[] = अणु
	अणु
		.name = "call_rcu_tasks()",
		/* If not defined, the test is skipped. */
		.notrun = !IS_ENABLED(CONFIG_TASKS_RCU),
	पूर्ण,
	अणु
		.name = "call_rcu_tasks_rude()",
		/* If not defined, the test is skipped. */
		.notrun = !IS_ENABLED(CONFIG_TASKS_RUDE_RCU),
	पूर्ण,
	अणु
		.name = "call_rcu_tasks_trace()",
		/* If not defined, the test is skipped. */
		.notrun = !IS_ENABLED(CONFIG_TASKS_TRACE_RCU)
	पूर्ण
पूर्ण;

अटल व्योम test_rcu_tasks_callback(काष्ठा rcu_head *rhp)
अणु
	काष्ठा rcu_tasks_test_desc *rttd =
		container_of(rhp, काष्ठा rcu_tasks_test_desc, rh);

	pr_info("Callback from %s invoked.\n", rttd->name);

	rttd->notrun = true;
पूर्ण

अटल व्योम rcu_tasks_initiate_self_tests(व्योम)
अणु
	pr_info("Running RCU-tasks wait API self tests\n");
#अगर_घोषित CONFIG_TASKS_RCU
	synchronize_rcu_tasks();
	call_rcu_tasks(&tests[0].rh, test_rcu_tasks_callback);
#पूर्ण_अगर

#अगर_घोषित CONFIG_TASKS_RUDE_RCU
	synchronize_rcu_tasks_rude();
	call_rcu_tasks_rude(&tests[1].rh, test_rcu_tasks_callback);
#पूर्ण_अगर

#अगर_घोषित CONFIG_TASKS_TRACE_RCU
	synchronize_rcu_tasks_trace();
	call_rcu_tasks_trace(&tests[2].rh, test_rcu_tasks_callback);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक rcu_tasks_verअगरy_self_tests(व्योम)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		अगर (!tests[i].notrun) अणु		// still hanging.
			pr_err("%s has been failed.\n", tests[i].name);
			ret = -1;
		पूर्ण
	पूर्ण

	अगर (ret)
		WARN_ON(1);

	वापस ret;
पूर्ण
late_initcall(rcu_tasks_verअगरy_self_tests);
#अन्यथा /* #अगर_घोषित CONFIG_PROVE_RCU */
अटल व्योम rcu_tasks_initiate_self_tests(व्योम) अणु पूर्ण
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_PROVE_RCU */

व्योम __init rcu_init_tasks_generic(व्योम)
अणु
#अगर_घोषित CONFIG_TASKS_RCU
	rcu_spawn_tasks_kthपढ़ो();
#पूर्ण_अगर

#अगर_घोषित CONFIG_TASKS_RUDE_RCU
	rcu_spawn_tasks_rude_kthपढ़ो();
#पूर्ण_अगर

#अगर_घोषित CONFIG_TASKS_TRACE_RCU
	rcu_spawn_tasks_trace_kthपढ़ो();
#पूर्ण_अगर

	// Run the self-tests.
	rcu_tasks_initiate_self_tests();
पूर्ण

#अन्यथा /* #अगर_घोषित CONFIG_TASKS_RCU_GENERIC */
अटल अंतरभूत व्योम rcu_tasks_bootup_oddness(व्योम) अणुपूर्ण
व्योम show_rcu_tasks_gp_kthपढ़ोs(व्योम) अणुपूर्ण
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_TASKS_RCU_GENERIC */
