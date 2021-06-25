<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_H
#घोषणा _LINUX_SCHED_H

/*
 * Define 'struct task_struct' and provide the मुख्य scheduler
 * APIs (schedule(), wakeup variants, etc.)
 */

#समावेश <uapi/linux/sched.h>

#समावेश <यंत्र/current.h>

#समावेश <linux/pid.h>
#समावेश <linux/sem.h>
#समावेश <linux/shm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/plist.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/refcount.h>
#समावेश <linux/resource.h>
#समावेश <linux/latencytop.h>
#समावेश <linux/sched/prपन.स>
#समावेश <linux/sched/types.h>
#समावेश <linux/संकेत_types.h>
#समावेश <linux/syscall_user_dispatch.h>
#समावेश <linux/mm_types_task.h>
#समावेश <linux/task_io_accounting.h>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/rseq.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/kcsan.h>
#समावेश <यंत्र/kmap_size.h>

/* task_काष्ठा member predeclarations (sorted alphabetically): */
काष्ठा audit_context;
काष्ठा backing_dev_info;
काष्ठा bio_list;
काष्ठा blk_plug;
काष्ठा bpf_local_storage;
काष्ठा capture_control;
काष्ठा cfs_rq;
काष्ठा fs_काष्ठा;
काष्ठा futex_pi_state;
काष्ठा io_context;
काष्ठा io_uring_task;
काष्ठा mempolicy;
काष्ठा nameidata;
काष्ठा nsproxy;
काष्ठा perf_event_context;
काष्ठा pid_namespace;
काष्ठा pipe_inode_info;
काष्ठा rcu_node;
काष्ठा reclaim_state;
काष्ठा robust_list_head;
काष्ठा root_करोमुख्य;
काष्ठा rq;
काष्ठा sched_attr;
काष्ठा sched_param;
काष्ठा seq_file;
काष्ठा sighand_काष्ठा;
काष्ठा संकेत_काष्ठा;
काष्ठा task_delay_info;
काष्ठा task_group;

/*
 * Task state biपंचांगask. NOTE! These bits are also
 * encoded in fs/proc/array.c: get_task_state().
 *
 * We have two separate sets of flags: task->state
 * is about runnability, जबतक task->निकास_state are
 * about the task निकासing. Confusing, but this way
 * modअगरying one set can't modअगरy the other one by
 * mistake.
 */

/* Used in tsk->state: */
#घोषणा TASK_RUNNING			0x0000
#घोषणा TASK_INTERRUPTIBLE		0x0001
#घोषणा TASK_UNINTERRUPTIBLE		0x0002
#घोषणा __TASK_STOPPED			0x0004
#घोषणा __TASK_TRACED			0x0008
/* Used in tsk->निकास_state: */
#घोषणा EXIT_DEAD			0x0010
#घोषणा EXIT_ZOMBIE			0x0020
#घोषणा EXIT_TRACE			(EXIT_ZOMBIE | EXIT_DEAD)
/* Used in tsk->state again: */
#घोषणा TASK_PARKED			0x0040
#घोषणा TASK_DEAD			0x0080
#घोषणा TASK_WAKEKILL			0x0100
#घोषणा TASK_WAKING			0x0200
#घोषणा TASK_NOLOAD			0x0400
#घोषणा TASK_NEW			0x0800
#घोषणा TASK_STATE_MAX			0x1000

/* Convenience macros क्रम the sake of set_current_state: */
#घोषणा TASK_KILLABLE			(TASK_WAKEKILL | TASK_UNINTERRUPTIBLE)
#घोषणा TASK_STOPPED			(TASK_WAKEKILL | __TASK_STOPPED)
#घोषणा TASK_TRACED			(TASK_WAKEKILL | __TASK_TRACED)

#घोषणा TASK_IDLE			(TASK_UNINTERRUPTIBLE | TASK_NOLOAD)

/* Convenience macros क्रम the sake of wake_up(): */
#घोषणा TASK_NORMAL			(TASK_INTERRUPTIBLE | TASK_UNINTERRUPTIBLE)

/* get_task_state(): */
#घोषणा TASK_REPORT			(TASK_RUNNING | TASK_INTERRUPTIBLE | \
					 TASK_UNINTERRUPTIBLE | __TASK_STOPPED | \
					 __TASK_TRACED | EXIT_DEAD | EXIT_ZOMBIE | \
					 TASK_PARKED)

#घोषणा task_is_traced(task)		((task->state & __TASK_TRACED) != 0)

#घोषणा task_is_stopped(task)		((task->state & __TASK_STOPPED) != 0)

#घोषणा task_is_stopped_or_traced(task)	((task->state & (__TASK_STOPPED | __TASK_TRACED)) != 0)

#अगर_घोषित CONFIG_DEBUG_ATOMIC_SLEEP

/*
 * Special states are those that करो not use the normal रुको-loop pattern. See
 * the comment with set_special_state().
 */
#घोषणा is_special_task_state(state)				\
	((state) & (__TASK_STOPPED | __TASK_TRACED | TASK_PARKED | TASK_DEAD))

#घोषणा __set_current_state(state_value)			\
	करो अणु							\
		WARN_ON_ONCE(is_special_task_state(state_value));\
		current->task_state_change = _THIS_IP_;		\
		current->state = (state_value);			\
	पूर्ण जबतक (0)

#घोषणा set_current_state(state_value)				\
	करो अणु							\
		WARN_ON_ONCE(is_special_task_state(state_value));\
		current->task_state_change = _THIS_IP_;		\
		smp_store_mb(current->state, (state_value));	\
	पूर्ण जबतक (0)

#घोषणा set_special_state(state_value)					\
	करो अणु								\
		अचिन्हित दीर्घ flags; /* may shaकरोw */			\
		WARN_ON_ONCE(!is_special_task_state(state_value));	\
		raw_spin_lock_irqsave(&current->pi_lock, flags);	\
		current->task_state_change = _THIS_IP_;			\
		current->state = (state_value);				\
		raw_spin_unlock_irqrestore(&current->pi_lock, flags);	\
	पूर्ण जबतक (0)
#अन्यथा
/*
 * set_current_state() includes a barrier so that the ग_लिखो of current->state
 * is correctly serialised wrt the caller's subsequent test of whether to
 * actually sleep:
 *
 *   क्रम (;;) अणु
 *	set_current_state(TASK_UNINTERRUPTIBLE);
 *	अगर (CONDITION)
 *	   अवरोध;
 *
 *	schedule();
 *   पूर्ण
 *   __set_current_state(TASK_RUNNING);
 *
 * If the caller करोes not need such serialisation (because, क्रम instance, the
 * CONDITION test and condition change and wakeup are under the same lock) then
 * use __set_current_state().
 *
 * The above is typically ordered against the wakeup, which करोes:
 *
 *   CONDITION = 1;
 *   wake_up_state(p, TASK_UNINTERRUPTIBLE);
 *
 * where wake_up_state()/try_to_wake_up() executes a full memory barrier beक्रमe
 * accessing p->state.
 *
 * Wakeup will करो: अगर (@state & p->state) p->state = TASK_RUNNING, that is,
 * once it observes the TASK_UNINTERRUPTIBLE store the waking CPU can issue a
 * TASK_RUNNING store which can collide with __set_current_state(TASK_RUNNING).
 *
 * However, with slightly dअगरferent timing the wakeup TASK_RUNNING store can
 * also collide with the TASK_UNINTERRUPTIBLE store. Losing that store is not
 * a problem either because that will result in one extra go around the loop
 * and our @cond test will save the day.
 *
 * Also see the comments of try_to_wake_up().
 */
#घोषणा __set_current_state(state_value)				\
	current->state = (state_value)

#घोषणा set_current_state(state_value)					\
	smp_store_mb(current->state, (state_value))

/*
 * set_special_state() should be used क्रम those states when the blocking task
 * can not use the regular condition based रुको-loop. In that हाल we must
 * serialize against wakeups such that any possible in-flight TASK_RUNNING stores
 * will not collide with our state change.
 */
#घोषणा set_special_state(state_value)					\
	करो अणु								\
		अचिन्हित दीर्घ flags; /* may shaकरोw */			\
		raw_spin_lock_irqsave(&current->pi_lock, flags);	\
		current->state = (state_value);				\
		raw_spin_unlock_irqrestore(&current->pi_lock, flags);	\
	पूर्ण जबतक (0)

#पूर्ण_अगर

/* Task command name length: */
#घोषणा TASK_COMM_LEN			16

बाह्य व्योम scheduler_tick(व्योम);

#घोषणा	MAX_SCHEDULE_TIMEOUT		दीर्घ_उच्च

बाह्य दीर्घ schedule_समयout(दीर्घ समयout);
बाह्य दीर्घ schedule_समयout_पूर्णांकerruptible(दीर्घ समयout);
बाह्य दीर्घ schedule_समयout_समाप्तable(दीर्घ समयout);
बाह्य दीर्घ schedule_समयout_unपूर्णांकerruptible(दीर्घ समयout);
बाह्य दीर्घ schedule_समयout_idle(दीर्घ समयout);
यंत्रlinkage व्योम schedule(व्योम);
बाह्य व्योम schedule_preempt_disabled(व्योम);
यंत्रlinkage व्योम preempt_schedule_irq(व्योम);

बाह्य पूर्णांक __must_check io_schedule_prepare(व्योम);
बाह्य व्योम io_schedule_finish(पूर्णांक token);
बाह्य दीर्घ io_schedule_समयout(दीर्घ समयout);
बाह्य व्योम io_schedule(व्योम);

/**
 * काष्ठा prev_cpuसमय - snapshot of प्रणाली and user cpuसमय
 * @uसमय: समय spent in user mode
 * @sसमय: समय spent in प्रणाली mode
 * @lock: protects the above two fields
 *
 * Stores previous user/प्रणाली समय values such that we can guarantee
 * monotonicity.
 */
काष्ठा prev_cpuसमय अणु
#अगर_अघोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
	u64				uसमय;
	u64				sसमय;
	raw_spinlock_t			lock;
#पूर्ण_अगर
पूर्ण;

क्रमागत vसमय_state अणु
	/* Task is sleeping or running in a CPU with VTIME inactive: */
	VTIME_INACTIVE = 0,
	/* Task is idle */
	VTIME_IDLE,
	/* Task runs in kernelspace in a CPU with VTIME active: */
	VTIME_SYS,
	/* Task runs in userspace in a CPU with VTIME active: */
	VTIME_USER,
	/* Task runs as guests in a CPU with VTIME active: */
	VTIME_GUEST,
पूर्ण;

काष्ठा vसमय अणु
	seqcount_t		seqcount;
	अचिन्हित दीर्घ दीर्घ	startसमय;
	क्रमागत vसमय_state	state;
	अचिन्हित पूर्णांक		cpu;
	u64			uसमय;
	u64			sसमय;
	u64			gसमय;
पूर्ण;

/*
 * Utilization clamp स्थिरraपूर्णांकs.
 * @UCLAMP_MIN:	Minimum utilization
 * @UCLAMP_MAX:	Maximum utilization
 * @UCLAMP_CNT:	Utilization clamp स्थिरraपूर्णांकs count
 */
क्रमागत uclamp_id अणु
	UCLAMP_MIN = 0,
	UCLAMP_MAX,
	UCLAMP_CNT
पूर्ण;

#अगर_घोषित CONFIG_SMP
बाह्य काष्ठा root_करोमुख्य def_root_करोमुख्य;
बाह्य काष्ठा mutex sched_करोमुख्यs_mutex;
#पूर्ण_अगर

काष्ठा sched_info अणु
#अगर_घोषित CONFIG_SCHED_INFO
	/* Cumulative counters: */

	/* # of बार we have run on this CPU: */
	अचिन्हित दीर्घ			pcount;

	/* Time spent रुकोing on a runqueue: */
	अचिन्हित दीर्घ दीर्घ		run_delay;

	/* Timestamps: */

	/* When did we last run on a CPU? */
	अचिन्हित दीर्घ दीर्घ		last_arrival;

	/* When were we last queued to run? */
	अचिन्हित दीर्घ दीर्घ		last_queued;

#पूर्ण_अगर /* CONFIG_SCHED_INFO */
पूर्ण;

/*
 * Integer metrics need fixed poपूर्णांक arithmetic, e.g., sched/fair
 * has a few: load, load_avg, util_avg, freq, and capacity.
 *
 * We define a basic fixed poपूर्णांक arithmetic range, and then क्रमmalize
 * all these metrics based on that basic range.
 */
# define SCHED_FIXEDPOINT_SHIFT		10
# define SCHED_FIXEDPOINT_SCALE		(1L << SCHED_FIXEDPOINT_SHIFT)

/* Increase resolution of cpu_capacity calculations */
# define SCHED_CAPACITY_SHIFT		SCHED_FIXEDPOINT_SHIFT
# define SCHED_CAPACITY_SCALE		(1L << SCHED_CAPACITY_SHIFT)

काष्ठा load_weight अणु
	अचिन्हित दीर्घ			weight;
	u32				inv_weight;
पूर्ण;

/**
 * काष्ठा util_est - Estimation utilization of FAIR tasks
 * @enqueued: instantaneous estimated utilization of a task/cpu
 * @ewma:     the Exponential Weighted Moving Average (EWMA)
 *            utilization of a task
 *
 * Support data काष्ठाure to track an Exponential Weighted Moving Average
 * (EWMA) of a FAIR task's utilization. New samples are added to the moving
 * average each समय a task completes an activation. Sample's weight is chosen
 * so that the EWMA will be relatively insensitive to transient changes to the
 * task's workload.
 *
 * The enqueued attribute has a slightly dअगरferent meaning क्रम tasks and cpus:
 * - task:   the task's util_avg at last task dequeue समय
 * - cfs_rq: the sum of util_est.enqueued क्रम each RUNNABLE task on that CPU
 * Thus, the util_est.enqueued of a task represents the contribution on the
 * estimated utilization of the CPU where that task is currently enqueued.
 *
 * Only क्रम tasks we track a moving average of the past instantaneous
 * estimated utilization. This allows to असलorb sporadic drops in utilization
 * of an otherwise almost periodic task.
 *
 * The UTIL_AVG_UNCHANGED flag is used to synchronize util_est with util_avg
 * updates. When a task is dequeued, its util_est should not be updated अगर its
 * util_avg has not been updated in the meanसमय.
 * This inक्रमmation is mapped पूर्णांकo the MSB bit of util_est.enqueued at dequeue
 * समय. Since max value of util_est.enqueued क्रम a task is 1024 (PELT util_avg
 * क्रम a task) it is safe to use MSB.
 */
काष्ठा util_est अणु
	अचिन्हित पूर्णांक			enqueued;
	अचिन्हित पूर्णांक			ewma;
#घोषणा UTIL_EST_WEIGHT_SHIFT		2
#घोषणा UTIL_AVG_UNCHANGED		0x80000000
पूर्ण __attribute__((__aligned__(माप(u64))));

/*
 * The load/runnable/util_avg accumulates an infinite geometric series
 * (see __update_load_avg_cfs_rq() in kernel/sched/pelt.c).
 *
 * [load_avg definition]
 *
 *   load_avg = runnable% * scale_load_करोwn(load)
 *
 * [runnable_avg definition]
 *
 *   runnable_avg = runnable% * SCHED_CAPACITY_SCALE
 *
 * [util_avg definition]
 *
 *   util_avg = running% * SCHED_CAPACITY_SCALE
 *
 * where runnable% is the समय ratio that a sched_entity is runnable and
 * running% the समय ratio that a sched_entity is running.
 *
 * For cfs_rq, they are the aggregated values of all runnable and blocked
 * sched_entities.
 *
 * The load/runnable/util_avg करोesn't directly factor frequency scaling and CPU
 * capacity scaling. The scaling is करोne through the rq_घड़ी_pelt that is used
 * क्रम computing those संकेतs (see update_rq_घड़ी_pelt())
 *
 * N.B., the above ratios (runnable% and running%) themselves are in the
 * range of [0, 1]. To करो fixed poपूर्णांक arithmetics, we thereक्रमe scale them
 * to as large a range as necessary. This is क्रम example reflected by
 * util_avg's SCHED_CAPACITY_SCALE.
 *
 * [Overflow issue]
 *
 * The 64-bit load_sum can have 4353082796 (=2^64/47742/88761) entities
 * with the highest load (=88761), always runnable on a single cfs_rq,
 * and should not overflow as the number alपढ़ोy hits PID_MAX_LIMIT.
 *
 * For all other हालs (including 32-bit kernels), काष्ठा load_weight's
 * weight will overflow first beक्रमe we करो, because:
 *
 *    Max(load_avg) <= Max(load.weight)
 *
 * Then it is the load_weight's responsibility to consider overflow
 * issues.
 */
काष्ठा sched_avg अणु
	u64				last_update_समय;
	u64				load_sum;
	u64				runnable_sum;
	u32				util_sum;
	u32				period_contrib;
	अचिन्हित दीर्घ			load_avg;
	अचिन्हित दीर्घ			runnable_avg;
	अचिन्हित दीर्घ			util_avg;
	काष्ठा util_est			util_est;
पूर्ण ____cacheline_aligned;

काष्ठा sched_statistics अणु
#अगर_घोषित CONFIG_SCHEDSTATS
	u64				रुको_start;
	u64				रुको_max;
	u64				रुको_count;
	u64				रुको_sum;
	u64				ioरुको_count;
	u64				ioरुको_sum;

	u64				sleep_start;
	u64				sleep_max;
	s64				sum_sleep_runसमय;

	u64				block_start;
	u64				block_max;
	u64				exec_max;
	u64				slice_max;

	u64				nr_migrations_cold;
	u64				nr_failed_migrations_affine;
	u64				nr_failed_migrations_running;
	u64				nr_failed_migrations_hot;
	u64				nr_क्रमced_migrations;

	u64				nr_wakeups;
	u64				nr_wakeups_sync;
	u64				nr_wakeups_migrate;
	u64				nr_wakeups_local;
	u64				nr_wakeups_remote;
	u64				nr_wakeups_affine;
	u64				nr_wakeups_affine_attempts;
	u64				nr_wakeups_passive;
	u64				nr_wakeups_idle;
#पूर्ण_अगर
पूर्ण;

काष्ठा sched_entity अणु
	/* For load-balancing: */
	काष्ठा load_weight		load;
	काष्ठा rb_node			run_node;
	काष्ठा list_head		group_node;
	अचिन्हित पूर्णांक			on_rq;

	u64				exec_start;
	u64				sum_exec_runसमय;
	u64				vrunसमय;
	u64				prev_sum_exec_runसमय;

	u64				nr_migrations;

	काष्ठा sched_statistics		statistics;

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	पूर्णांक				depth;
	काष्ठा sched_entity		*parent;
	/* rq on which this entity is (to be) queued: */
	काष्ठा cfs_rq			*cfs_rq;
	/* rq "owned" by this entity/group: */
	काष्ठा cfs_rq			*my_q;
	/* cached value of my_q->h_nr_running */
	अचिन्हित दीर्घ			runnable_weight;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
	/*
	 * Per entity load average tracking.
	 *
	 * Put पूर्णांकo separate cache line so it करोes not
	 * collide with पढ़ो-mostly values above.
	 */
	काष्ठा sched_avg		avg;
#पूर्ण_अगर
पूर्ण;

काष्ठा sched_rt_entity अणु
	काष्ठा list_head		run_list;
	अचिन्हित दीर्घ			समयout;
	अचिन्हित दीर्घ			watchकरोg_stamp;
	अचिन्हित पूर्णांक			समय_slice;
	अचिन्हित लघु			on_rq;
	अचिन्हित लघु			on_list;

	काष्ठा sched_rt_entity		*back;
#अगर_घोषित CONFIG_RT_GROUP_SCHED
	काष्ठा sched_rt_entity		*parent;
	/* rq on which this entity is (to be) queued: */
	काष्ठा rt_rq			*rt_rq;
	/* rq "owned" by this entity/group: */
	काष्ठा rt_rq			*my_q;
#पूर्ण_अगर
पूर्ण __अक्रमomize_layout;

काष्ठा sched_dl_entity अणु
	काष्ठा rb_node			rb_node;

	/*
	 * Original scheduling parameters. Copied here from sched_attr
	 * during sched_setattr(), they will reमुख्य the same until
	 * the next sched_setattr().
	 */
	u64				dl_runसमय;	/* Maximum runसमय क्रम each instance	*/
	u64				dl_deadline;	/* Relative deadline of each instance	*/
	u64				dl_period;	/* Separation of two instances (period) */
	u64				dl_bw;		/* dl_runसमय / dl_period		*/
	u64				dl_density;	/* dl_runसमय / dl_deadline		*/

	/*
	 * Actual scheduling parameters. Initialized with the values above,
	 * they are continuously updated during task execution. Note that
	 * the reमुख्यing runसमय could be < 0 in हाल we are in overrun.
	 */
	s64				runसमय;	/* Reमुख्यing runसमय क्रम this instance	*/
	u64				deadline;	/* Absolute deadline क्रम this instance	*/
	अचिन्हित पूर्णांक			flags;		/* Specअगरying the scheduler behaviour	*/

	/*
	 * Some bool flags:
	 *
	 * @dl_throttled tells अगर we exhausted the runसमय. If so, the
	 * task has to रुको क्रम a replenishment to be perक्रमmed at the
	 * next firing of dl_समयr.
	 *
	 * @dl_boosted tells अगर we are boosted due to DI. If so we are
	 * outside bandwidth enक्रमcement mechanism (but only until we
	 * निकास the critical section);
	 *
	 * @dl_yielded tells अगर task gave up the CPU beक्रमe consuming
	 * all its available runसमय during the last job.
	 *
	 * @dl_non_contending tells अगर the task is inactive जबतक still
	 * contributing to the active utilization. In other words, it
	 * indicates अगर the inactive समयr has been armed and its handler
	 * has not been executed yet. This flag is useful to aव्योम race
	 * conditions between the inactive समयr handler and the wakeup
	 * code.
	 *
	 * @dl_overrun tells अगर the task asked to be inक्रमmed about runसमय
	 * overruns.
	 */
	अचिन्हित पूर्णांक			dl_throttled      : 1;
	अचिन्हित पूर्णांक			dl_yielded        : 1;
	अचिन्हित पूर्णांक			dl_non_contending : 1;
	अचिन्हित पूर्णांक			dl_overrun	  : 1;

	/*
	 * Bandwidth enक्रमcement समयr. Each -deadline task has its
	 * own bandwidth to be enक्रमced, thus we need one समयr per task.
	 */
	काष्ठा hrसमयr			dl_समयr;

	/*
	 * Inactive समयr, responsible क्रम decreasing the active utilization
	 * at the "0-lag time". When a -deadline task blocks, it contributes
	 * to GRUB's active utilization until the "0-lag time", hence a
	 * समयr is needed to decrease the active utilization at the correct
	 * समय.
	 */
	काष्ठा hrसमयr inactive_समयr;

#अगर_घोषित CONFIG_RT_MUTEXES
	/*
	 * Priority Inheritance. When a DEADLINE scheduling entity is boosted
	 * pi_se poपूर्णांकs to the करोnor, otherwise poपूर्णांकs to the dl_se it beदीर्घs
	 * to (the original one/itself).
	 */
	काष्ठा sched_dl_entity *pi_se;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_UCLAMP_TASK
/* Number of utilization clamp buckets (लघुer alias) */
#घोषणा UCLAMP_BUCKETS CONFIG_UCLAMP_BUCKETS_COUNT

/*
 * Utilization clamp क्रम a scheduling entity
 * @value:		clamp value "assigned" to a se
 * @bucket_id:		bucket index corresponding to the "assigned" value
 * @active:		the se is currently refcounted in a rq's bucket
 * @user_defined:	the requested clamp value comes from user-space
 *
 * The bucket_id is the index of the clamp bucket matching the clamp value
 * which is pre-computed and stored to aव्योम expensive पूर्णांकeger भागisions from
 * the fast path.
 *
 * The active bit is set whenever a task has got an "effective" value asचिन्हित,
 * which can be dअगरferent from the clamp value "requested" from user-space.
 * This allows to know a task is refcounted in the rq's bucket corresponding
 * to the "effective" bucket_id.
 *
 * The user_defined bit is set whenever a task has got a task-specअगरic clamp
 * value requested from userspace, i.e. the प्रणाली शेषs apply to this task
 * just as a restriction. This allows to relax शेष clamps when a less
 * restrictive task-specअगरic value has been requested, thus allowing to
 * implement a "nice" semantic. For example, a task running with a 20%
 * शेष boost can still drop its own boosting to 0%.
 */
काष्ठा uclamp_se अणु
	अचिन्हित पूर्णांक value		: bits_per(SCHED_CAPACITY_SCALE);
	अचिन्हित पूर्णांक bucket_id		: bits_per(UCLAMP_BUCKETS);
	अचिन्हित पूर्णांक active		: 1;
	अचिन्हित पूर्णांक user_defined	: 1;
पूर्ण;
#पूर्ण_अगर /* CONFIG_UCLAMP_TASK */

जोड़ rcu_special अणु
	काष्ठा अणु
		u8			blocked;
		u8			need_qs;
		u8			exp_hपूर्णांक; /* Hपूर्णांक क्रम perक्रमmance. */
		u8			need_mb; /* Readers need smp_mb(). */
	पूर्ण b; /* Bits. */
	u32 s; /* Set of bits. */
पूर्ण;

क्रमागत perf_event_task_context अणु
	perf_invalid_context = -1,
	perf_hw_context = 0,
	perf_sw_context,
	perf_nr_task_contexts,
पूर्ण;

काष्ठा wake_q_node अणु
	काष्ठा wake_q_node *next;
पूर्ण;

काष्ठा kmap_ctrl अणु
#अगर_घोषित CONFIG_KMAP_LOCAL
	पूर्णांक				idx;
	pte_t				pteval[KM_MAX_IDX];
#पूर्ण_अगर
पूर्ण;

काष्ठा task_काष्ठा अणु
#अगर_घोषित CONFIG_THREAD_INFO_IN_TASK
	/*
	 * For reasons of header soup (see current_thपढ़ो_info()), this
	 * must be the first element of task_काष्ठा.
	 */
	काष्ठा thपढ़ो_info		thपढ़ो_info;
#पूर्ण_अगर
	/* -1 unrunnable, 0 runnable, >0 stopped: */
	अस्थिर दीर्घ			state;

	/*
	 * This begins the अक्रमomizable portion of task_काष्ठा. Only
	 * scheduling-critical items should be added above here.
	 */
	अक्रमomized_काष्ठा_fields_start

	व्योम				*stack;
	refcount_t			usage;
	/* Per task flags (PF_*), defined further below: */
	अचिन्हित पूर्णांक			flags;
	अचिन्हित पूर्णांक			ptrace;

#अगर_घोषित CONFIG_SMP
	पूर्णांक				on_cpu;
	काष्ठा __call_single_node	wake_entry;
#अगर_घोषित CONFIG_THREAD_INFO_IN_TASK
	/* Current CPU: */
	अचिन्हित पूर्णांक			cpu;
#पूर्ण_अगर
	अचिन्हित पूर्णांक			wakee_flips;
	अचिन्हित दीर्घ			wakee_flip_decay_ts;
	काष्ठा task_काष्ठा		*last_wakee;

	/*
	 * recent_used_cpu is initially set as the last CPU used by a task
	 * that wakes affine another task. Waker/wakee relationships can
	 * push tasks around a CPU where each wakeup moves to the next one.
	 * Tracking a recently used CPU allows a quick search क्रम a recently
	 * used CPU that may be idle.
	 */
	पूर्णांक				recent_used_cpu;
	पूर्णांक				wake_cpu;
#पूर्ण_अगर
	पूर्णांक				on_rq;

	पूर्णांक				prio;
	पूर्णांक				अटल_prio;
	पूर्णांक				normal_prio;
	अचिन्हित पूर्णांक			rt_priority;

	स्थिर काष्ठा sched_class	*sched_class;
	काष्ठा sched_entity		se;
	काष्ठा sched_rt_entity		rt;
#अगर_घोषित CONFIG_CGROUP_SCHED
	काष्ठा task_group		*sched_task_group;
#पूर्ण_अगर
	काष्ठा sched_dl_entity		dl;

#अगर_घोषित CONFIG_UCLAMP_TASK
	/*
	 * Clamp values requested क्रम a scheduling entity.
	 * Must be updated with task_rq_lock() held.
	 */
	काष्ठा uclamp_se		uclamp_req[UCLAMP_CNT];
	/*
	 * Effective clamp values used क्रम a scheduling entity.
	 * Must be updated with task_rq_lock() held.
	 */
	काष्ठा uclamp_se		uclamp[UCLAMP_CNT];
#पूर्ण_अगर

#अगर_घोषित CONFIG_PREEMPT_NOTIFIERS
	/* List of काष्ठा preempt_notअगरier: */
	काष्ठा hlist_head		preempt_notअगरiers;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BLK_DEV_IO_TRACE
	अचिन्हित पूर्णांक			btrace_seq;
#पूर्ण_अगर

	अचिन्हित पूर्णांक			policy;
	पूर्णांक				nr_cpus_allowed;
	स्थिर cpumask_t			*cpus_ptr;
	cpumask_t			cpus_mask;
	व्योम				*migration_pending;
#अगर_घोषित CONFIG_SMP
	अचिन्हित लघु			migration_disabled;
#पूर्ण_अगर
	अचिन्हित लघु			migration_flags;

#अगर_घोषित CONFIG_PREEMPT_RCU
	पूर्णांक				rcu_पढ़ो_lock_nesting;
	जोड़ rcu_special		rcu_पढ़ो_unlock_special;
	काष्ठा list_head		rcu_node_entry;
	काष्ठा rcu_node			*rcu_blocked_node;
#पूर्ण_अगर /* #अगर_घोषित CONFIG_PREEMPT_RCU */

#अगर_घोषित CONFIG_TASKS_RCU
	अचिन्हित दीर्घ			rcu_tasks_nvcsw;
	u8				rcu_tasks_holकरोut;
	u8				rcu_tasks_idx;
	पूर्णांक				rcu_tasks_idle_cpu;
	काष्ठा list_head		rcu_tasks_holकरोut_list;
#पूर्ण_अगर /* #अगर_घोषित CONFIG_TASKS_RCU */

#अगर_घोषित CONFIG_TASKS_TRACE_RCU
	पूर्णांक				trc_पढ़ोer_nesting;
	पूर्णांक				trc_ipi_to_cpu;
	जोड़ rcu_special		trc_पढ़ोer_special;
	bool				trc_पढ़ोer_checked;
	काष्ठा list_head		trc_holकरोut_list;
#पूर्ण_अगर /* #अगर_घोषित CONFIG_TASKS_TRACE_RCU */

	काष्ठा sched_info		sched_info;

	काष्ठा list_head		tasks;
#अगर_घोषित CONFIG_SMP
	काष्ठा plist_node		pushable_tasks;
	काष्ठा rb_node			pushable_dl_tasks;
#पूर्ण_अगर

	काष्ठा mm_काष्ठा		*mm;
	काष्ठा mm_काष्ठा		*active_mm;

	/* Per-thपढ़ो vma caching: */
	काष्ठा vmacache			vmacache;

#अगर_घोषित SPLIT_RSS_COUNTING
	काष्ठा task_rss_stat		rss_stat;
#पूर्ण_अगर
	पूर्णांक				निकास_state;
	पूर्णांक				निकास_code;
	पूर्णांक				निकास_संकेत;
	/* The संकेत sent when the parent dies: */
	पूर्णांक				pdeath_संकेत;
	/* JOBCTL_*, siglock रक्षित: */
	अचिन्हित दीर्घ			jobctl;

	/* Used क्रम emulating ABI behavior of previous Linux versions: */
	अचिन्हित पूर्णांक			personality;

	/* Scheduler bits, serialized by scheduler locks: */
	अचिन्हित			sched_reset_on_विभाजन:1;
	अचिन्हित			sched_contributes_to_load:1;
	अचिन्हित			sched_migrated:1;
#अगर_घोषित CONFIG_PSI
	अचिन्हित			sched_psi_wake_requeue:1;
#पूर्ण_अगर

	/* Force alignment to the next boundary: */
	अचिन्हित			:0;

	/* Unserialized, strictly 'current' */

	/*
	 * This field must not be in the scheduler word above due to wakelist
	 * queueing no दीर्घer being serialized by p->on_cpu. However:
	 *
	 * p->XXX = X;			ttwu()
	 * schedule()			  अगर (p->on_rq && ..) // false
	 *   smp_mb__after_spinlock();	  अगर (smp_load_acquire(&p->on_cpu) && //true
	 *   deactivate_task()		      ttwu_queue_wakelist())
	 *     p->on_rq = 0;			p->sched_remote_wakeup = Y;
	 *
	 * guarantees all stores of 'current' are visible beक्रमe
	 * ->sched_remote_wakeup माला_लो used, so it can be in this word.
	 */
	अचिन्हित			sched_remote_wakeup:1;

	/* Bit to tell LSMs we're in execve(): */
	अचिन्हित			in_execve:1;
	अचिन्हित			in_ioरुको:1;
#अगर_अघोषित TIF_RESTORE_SIGMASK
	अचिन्हित			restore_sigmask:1;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEMCG
	अचिन्हित			in_user_fault:1;
#पूर्ण_अगर
#अगर_घोषित CONFIG_COMPAT_BRK
	अचिन्हित			brk_अक्रमomized:1;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CGROUPS
	/* disallow userland-initiated cgroup migration */
	अचिन्हित			no_cgroup_migration:1;
	/* task is frozen/stopped (used by the cgroup मुक्तzer) */
	अचिन्हित			frozen:1;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BLK_CGROUP
	अचिन्हित			use_memdelay:1;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PSI
	/* Stalled due to lack of memory */
	अचिन्हित			in_memstall:1;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PAGE_OWNER
	/* Used by page_owner=on to detect recursion in page tracking. */
	अचिन्हित			in_page_owner:1;
#पूर्ण_अगर

	अचिन्हित दीर्घ			atomic_flags; /* Flags requiring atomic access. */

	काष्ठा restart_block		restart_block;

	pid_t				pid;
	pid_t				tgid;

#अगर_घोषित CONFIG_STACKPROTECTOR
	/* Canary value क्रम the -fstack-protector GCC feature: */
	अचिन्हित दीर्घ			stack_canary;
#पूर्ण_अगर
	/*
	 * Poपूर्णांकers to the (original) parent process, youngest child, younger sibling,
	 * older sibling, respectively.  (p->father can be replaced with
	 * p->real_parent->pid)
	 */

	/* Real parent process: */
	काष्ठा task_काष्ठा __rcu	*real_parent;

	/* Recipient of SIGCHLD, रुको4() reports: */
	काष्ठा task_काष्ठा __rcu	*parent;

	/*
	 * Children/sibling क्रमm the list of natural children:
	 */
	काष्ठा list_head		children;
	काष्ठा list_head		sibling;
	काष्ठा task_काष्ठा		*group_leader;

	/*
	 * 'ptraced' is the list of tasks this task is using ptrace() on.
	 *
	 * This includes both natural children and PTRACE_ATTACH tarमाला_लो.
	 * 'ptrace_entry' is this task's link on the p->parent->ptraced list.
	 */
	काष्ठा list_head		ptraced;
	काष्ठा list_head		ptrace_entry;

	/* PID/PID hash table linkage. */
	काष्ठा pid			*thपढ़ो_pid;
	काष्ठा hlist_node		pid_links[PIDTYPE_MAX];
	काष्ठा list_head		thपढ़ो_group;
	काष्ठा list_head		thपढ़ो_node;

	काष्ठा completion		*vविभाजन_करोne;

	/* CLONE_CHILD_SETTID: */
	पूर्णांक __user			*set_child_tid;

	/* CLONE_CHILD_CLEARTID: */
	पूर्णांक __user			*clear_child_tid;

	/* PF_IO_WORKER */
	व्योम				*pf_io_worker;

	u64				uसमय;
	u64				sसमय;
#अगर_घोषित CONFIG_ARCH_HAS_SCALED_CPUTIME
	u64				uबारcaled;
	u64				sबारcaled;
#पूर्ण_अगर
	u64				gसमय;
	काष्ठा prev_cpuसमय		prev_cpuसमय;
#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_GEN
	काष्ठा vसमय			vसमय;
#पूर्ण_अगर

#अगर_घोषित CONFIG_NO_HZ_FULL
	atomic_t			tick_dep_mask;
#पूर्ण_अगर
	/* Context चयन counts: */
	अचिन्हित दीर्घ			nvcsw;
	अचिन्हित दीर्घ			nivcsw;

	/* Monotonic समय in nsecs: */
	u64				start_समय;

	/* Boot based समय in nsecs: */
	u64				start_bootसमय;

	/* MM fault and swap info: this can arguably be seen as either mm-specअगरic or thपढ़ो-specअगरic: */
	अचिन्हित दीर्घ			min_flt;
	अचिन्हित दीर्घ			maj_flt;

	/* Empty अगर CONFIG_POSIX_CPUTIMERS=n */
	काष्ठा posix_cpuसमयrs		posix_cpuसमयrs;

#अगर_घोषित CONFIG_POSIX_CPU_TIMERS_TASK_WORK
	काष्ठा posix_cpuसमयrs_work	posix_cpuसमयrs_work;
#पूर्ण_अगर

	/* Process credentials: */

	/* Tracer's credentials at attach: */
	स्थिर काष्ठा cred __rcu		*ptracer_cred;

	/* Objective and real subjective task credentials (COW): */
	स्थिर काष्ठा cred __rcu		*real_cred;

	/* Effective (overridable) subjective task credentials (COW): */
	स्थिर काष्ठा cred __rcu		*cred;

#अगर_घोषित CONFIG_KEYS
	/* Cached requested key. */
	काष्ठा key			*cached_requested_key;
#पूर्ण_अगर

	/*
	 * executable name, excluding path.
	 *
	 * - normally initialized setup_new_exec()
	 * - access it with [gs]et_task_comm()
	 * - lock it with task_lock()
	 */
	अक्षर				comm[TASK_COMM_LEN];

	काष्ठा nameidata		*nameidata;

#अगर_घोषित CONFIG_SYSVIPC
	काष्ठा sysv_sem			sysvsem;
	काष्ठा sysv_shm			sysvshm;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DETECT_HUNG_TASK
	अचिन्हित दीर्घ			last_चयन_count;
	अचिन्हित दीर्घ			last_चयन_समय;
#पूर्ण_अगर
	/* Fileप्रणाली inक्रमmation: */
	काष्ठा fs_काष्ठा		*fs;

	/* Open file inक्रमmation: */
	काष्ठा files_काष्ठा		*files;

#अगर_घोषित CONFIG_IO_URING
	काष्ठा io_uring_task		*io_uring;
#पूर्ण_अगर

	/* Namespaces: */
	काष्ठा nsproxy			*nsproxy;

	/* Signal handlers: */
	काष्ठा संकेत_काष्ठा		*संकेत;
	काष्ठा sighand_काष्ठा __rcu		*sighand;
	काष्ठा sigqueue			*sigqueue_cache;
	sigset_t			blocked;
	sigset_t			real_blocked;
	/* Restored अगर set_restore_sigmask() was used: */
	sigset_t			saved_sigmask;
	काष्ठा संक_बाकी		pending;
	अचिन्हित दीर्घ			sas_ss_sp;
	माप_प्रकार				sas_ss_size;
	अचिन्हित पूर्णांक			sas_ss_flags;

	काष्ठा callback_head		*task_works;

#अगर_घोषित CONFIG_AUDIT
#अगर_घोषित CONFIG_AUDITSYSCALL
	काष्ठा audit_context		*audit_context;
#पूर्ण_अगर
	kuid_t				loginuid;
	अचिन्हित पूर्णांक			sessionid;
#पूर्ण_अगर
	काष्ठा seccomp			seccomp;
	काष्ठा syscall_user_dispatch	syscall_dispatch;

	/* Thपढ़ो group tracking: */
	u64				parent_exec_id;
	u64				self_exec_id;

	/* Protection against (de-)allocation: mm, files, fs, tty, keyrings, mems_allowed, mempolicy: */
	spinlock_t			alloc_lock;

	/* Protection of the PI data काष्ठाures: */
	raw_spinlock_t			pi_lock;

	काष्ठा wake_q_node		wake_q;

#अगर_घोषित CONFIG_RT_MUTEXES
	/* PI रुकोers blocked on a rt_mutex held by this task: */
	काष्ठा rb_root_cached		pi_रुकोers;
	/* Updated under owner's pi_lock and rq lock */
	काष्ठा task_काष्ठा		*pi_top_task;
	/* Deadlock detection and priority inheritance handling: */
	काष्ठा rt_mutex_रुकोer		*pi_blocked_on;
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_MUTEXES
	/* Mutex deadlock detection: */
	काष्ठा mutex_रुकोer		*blocked_on;
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_ATOMIC_SLEEP
	पूर्णांक				non_block_count;
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRACE_IRQFLAGS
	काष्ठा irqtrace_events		irqtrace;
	अचिन्हित पूर्णांक			hardirq_thपढ़ोed;
	u64				hardirq_chain_key;
	पूर्णांक				softirqs_enabled;
	पूर्णांक				softirq_context;
	पूर्णांक				irq_config;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PREEMPT_RT
	पूर्णांक				softirq_disable_cnt;
#पूर्ण_अगर

#अगर_घोषित CONFIG_LOCKDEP
# define MAX_LOCK_DEPTH			48UL
	u64				curr_chain_key;
	पूर्णांक				lockdep_depth;
	अचिन्हित पूर्णांक			lockdep_recursion;
	काष्ठा held_lock		held_locks[MAX_LOCK_DEPTH];
#पूर्ण_अगर

#अगर defined(CONFIG_UBSAN) && !defined(CONFIG_UBSAN_TRAP)
	अचिन्हित पूर्णांक			in_ubsan;
#पूर्ण_अगर

	/* Journalling fileप्रणाली info: */
	व्योम				*journal_info;

	/* Stacked block device info: */
	काष्ठा bio_list			*bio_list;

#अगर_घोषित CONFIG_BLOCK
	/* Stack plugging: */
	काष्ठा blk_plug			*plug;
#पूर्ण_अगर

	/* VM state: */
	काष्ठा reclaim_state		*reclaim_state;

	काष्ठा backing_dev_info		*backing_dev_info;

	काष्ठा io_context		*io_context;

#अगर_घोषित CONFIG_COMPACTION
	काष्ठा capture_control		*capture_control;
#पूर्ण_अगर
	/* Ptrace state: */
	अचिन्हित दीर्घ			ptrace_message;
	kernel_siginfo_t		*last_siginfo;

	काष्ठा task_io_accounting	ioac;
#अगर_घोषित CONFIG_PSI
	/* Pressure stall state */
	अचिन्हित पूर्णांक			psi_flags;
#पूर्ण_अगर
#अगर_घोषित CONFIG_TASK_XACCT
	/* Accumulated RSS usage: */
	u64				acct_rss_mem1;
	/* Accumulated भव memory usage: */
	u64				acct_vm_mem1;
	/* sसमय + uसमय since last update: */
	u64				acct_समयxpd;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPUSETS
	/* Protected by ->alloc_lock: */
	nodemask_t			mems_allowed;
	/* Sequence number to catch updates: */
	seqcount_spinlock_t		mems_allowed_seq;
	पूर्णांक				cpuset_mem_spपढ़ो_rotor;
	पूर्णांक				cpuset_slab_spपढ़ो_rotor;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CGROUPS
	/* Control Group info रक्षित by css_set_lock: */
	काष्ठा css_set __rcu		*cgroups;
	/* cg_list रक्षित by css_set_lock and tsk->alloc_lock: */
	काष्ठा list_head		cg_list;
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_CPU_RESCTRL
	u32				closid;
	u32				rmid;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FUTEX
	काष्ठा robust_list_head __user	*robust_list;
#अगर_घोषित CONFIG_COMPAT
	काष्ठा compat_robust_list_head __user *compat_robust_list;
#पूर्ण_अगर
	काष्ठा list_head		pi_state_list;
	काष्ठा futex_pi_state		*pi_state_cache;
	काष्ठा mutex			futex_निकास_mutex;
	अचिन्हित पूर्णांक			futex_state;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PERF_EVENTS
	काष्ठा perf_event_context	*perf_event_ctxp[perf_nr_task_contexts];
	काष्ठा mutex			perf_event_mutex;
	काष्ठा list_head		perf_event_list;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_PREEMPT
	अचिन्हित दीर्घ			preempt_disable_ip;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NUMA
	/* Protected by alloc_lock: */
	काष्ठा mempolicy		*mempolicy;
	लघु				il_prev;
	लघु				pref_node_विभाजन;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NUMA_BALANCING
	पूर्णांक				numa_scan_seq;
	अचिन्हित पूर्णांक			numa_scan_period;
	अचिन्हित पूर्णांक			numa_scan_period_max;
	पूर्णांक				numa_preferred_nid;
	अचिन्हित दीर्घ			numa_migrate_retry;
	/* Migration stamp: */
	u64				node_stamp;
	u64				last_task_numa_placement;
	u64				last_sum_exec_runसमय;
	काष्ठा callback_head		numa_work;

	/*
	 * This poपूर्णांकer is only modअगरied क्रम current in syscall and
	 * pagefault context (and क्रम tasks being destroyed), so it can be पढ़ो
	 * from any of the following contexts:
	 *  - RCU पढ़ो-side critical section
	 *  - current->numa_group from everywhere
	 *  - task's runqueue locked, task not running
	 */
	काष्ठा numa_group __rcu		*numa_group;

	/*
	 * numa_faults is an array split पूर्णांकo four regions:
	 * faults_memory, faults_cpu, faults_memory_buffer, faults_cpu_buffer
	 * in this precise order.
	 *
	 * faults_memory: Exponential decaying average of faults on a per-node
	 * basis. Scheduling placement decisions are made based on these
	 * counts. The values reमुख्य अटल क्रम the duration of a PTE scan.
	 * faults_cpu: Track the nodes the process was running on when a NUMA
	 * hपूर्णांकing fault was incurred.
	 * faults_memory_buffer and faults_cpu_buffer: Record faults per node
	 * during the current scan winकरोw. When the scan completes, the counts
	 * in faults_memory and faults_cpu decay and these values are copied.
	 */
	अचिन्हित दीर्घ			*numa_faults;
	अचिन्हित दीर्घ			total_numa_faults;

	/*
	 * numa_faults_locality tracks अगर faults recorded during the last
	 * scan winकरोw were remote/local or failed to migrate. The task scan
	 * period is adapted based on the locality of the faults with dअगरferent
	 * weights depending on whether they were shared or निजी faults
	 */
	अचिन्हित दीर्घ			numa_faults_locality[3];

	अचिन्हित दीर्घ			numa_pages_migrated;
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

#अगर_घोषित CONFIG_RSEQ
	काष्ठा rseq __user *rseq;
	u32 rseq_sig;
	/*
	 * RmW on rseq_event_mask must be perक्रमmed atomically
	 * with respect to preemption.
	 */
	अचिन्हित दीर्घ rseq_event_mask;
#पूर्ण_अगर

	काष्ठा tlbflush_unmap_batch	tlb_ubc;

	जोड़ अणु
		refcount_t		rcu_users;
		काष्ठा rcu_head		rcu;
	पूर्ण;

	/* Cache last used pipe क्रम splice(): */
	काष्ठा pipe_inode_info		*splice_pipe;

	काष्ठा page_frag		task_frag;

#अगर_घोषित CONFIG_TASK_DELAY_ACCT
	काष्ठा task_delay_info		*delays;
#पूर्ण_अगर

#अगर_घोषित CONFIG_FAULT_INJECTION
	पूर्णांक				make_it_fail;
	अचिन्हित पूर्णांक			fail_nth;
#पूर्ण_अगर
	/*
	 * When (nr_dirtied >= nr_dirtied_छोड़ो), it's समय to call
	 * balance_dirty_pages() क्रम a dirty throttling छोड़ो:
	 */
	पूर्णांक				nr_dirtied;
	पूर्णांक				nr_dirtied_छोड़ो;
	/* Start of a ग_लिखो-and-छोड़ो period: */
	अचिन्हित दीर्घ			dirty_छोड़ोd_when;

#अगर_घोषित CONFIG_LATENCYTOP
	पूर्णांक				latency_record_count;
	काष्ठा latency_record		latency_record[LT_SAVECOUNT];
#पूर्ण_अगर
	/*
	 * Time slack values; these are used to round up poll() and
	 * select() etc समयout values. These are in nanoseconds.
	 */
	u64				समयr_slack_ns;
	u64				शेष_समयr_slack_ns;

#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)
	अचिन्हित पूर्णांक			kasan_depth;
#पूर्ण_अगर

#अगर_घोषित CONFIG_KCSAN
	काष्ठा kcsan_ctx		kcsan_ctx;
#अगर_घोषित CONFIG_TRACE_IRQFLAGS
	काष्ठा irqtrace_events		kcsan_save_irqtrace;
#पूर्ण_अगर
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_KUNIT)
	काष्ठा kunit			*kunit_test;
#पूर्ण_अगर

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	/* Index of current stored address in ret_stack: */
	पूर्णांक				curr_ret_stack;
	पूर्णांक				curr_ret_depth;

	/* Stack of वापस addresses क्रम वापस function tracing: */
	काष्ठा ftrace_ret_stack		*ret_stack;

	/* Timestamp क्रम last schedule: */
	अचिन्हित दीर्घ दीर्घ		ftrace_बारtamp;

	/*
	 * Number of functions that haven't been traced
	 * because of depth overrun:
	 */
	atomic_t			trace_overrun;

	/* Pause tracing: */
	atomic_t			tracing_graph_छोड़ो;
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRACING
	/* State flags क्रम use by tracers: */
	अचिन्हित दीर्घ			trace;

	/* Biपंचांगask and counter of trace recursion: */
	अचिन्हित दीर्घ			trace_recursion;
#पूर्ण_अगर /* CONFIG_TRACING */

#अगर_घोषित CONFIG_KCOV
	/* See kernel/kcov.c क्रम more details. */

	/* Coverage collection mode enabled क्रम this task (0 अगर disabled): */
	अचिन्हित पूर्णांक			kcov_mode;

	/* Size of the kcov_area: */
	अचिन्हित पूर्णांक			kcov_size;

	/* Buffer क्रम coverage collection: */
	व्योम				*kcov_area;

	/* KCOV descriptor wired with this task or शून्य: */
	काष्ठा kcov			*kcov;

	/* KCOV common handle क्रम remote coverage collection: */
	u64				kcov_handle;

	/* KCOV sequence number: */
	पूर्णांक				kcov_sequence;

	/* Collect coverage from softirq context: */
	अचिन्हित पूर्णांक			kcov_softirq;
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEMCG
	काष्ठा mem_cgroup		*memcg_in_oom;
	gfp_t				memcg_oom_gfp_mask;
	पूर्णांक				memcg_oom_order;

	/* Number of pages to reclaim on वापसing to userland: */
	अचिन्हित पूर्णांक			memcg_nr_pages_over_high;

	/* Used by memcontrol क्रम targeted memcg अक्षरge: */
	काष्ठा mem_cgroup		*active_memcg;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BLK_CGROUP
	काष्ठा request_queue		*throttle_queue;
#पूर्ण_अगर

#अगर_घोषित CONFIG_UPROBES
	काष्ठा uprobe_task		*utask;
#पूर्ण_अगर
#अगर defined(CONFIG_BCACHE) || defined(CONFIG_BCACHE_MODULE)
	अचिन्हित पूर्णांक			sequential_io;
	अचिन्हित पूर्णांक			sequential_io_avg;
#पूर्ण_अगर
	काष्ठा kmap_ctrl		kmap_ctrl;
#अगर_घोषित CONFIG_DEBUG_ATOMIC_SLEEP
	अचिन्हित दीर्घ			task_state_change;
#पूर्ण_अगर
	पूर्णांक				pagefault_disabled;
#अगर_घोषित CONFIG_MMU
	काष्ठा task_काष्ठा		*oom_reaper_list;
#पूर्ण_अगर
#अगर_घोषित CONFIG_VMAP_STACK
	काष्ठा vm_काष्ठा		*stack_vm_area;
#पूर्ण_अगर
#अगर_घोषित CONFIG_THREAD_INFO_IN_TASK
	/* A live task holds one reference: */
	refcount_t			stack_refcount;
#पूर्ण_अगर
#अगर_घोषित CONFIG_LIVEPATCH
	पूर्णांक patch_state;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECURITY
	/* Used by LSM modules क्रम access restriction: */
	व्योम				*security;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BPF_SYSCALL
	/* Used by BPF task local storage */
	काष्ठा bpf_local_storage __rcu	*bpf_storage;
#पूर्ण_अगर

#अगर_घोषित CONFIG_GCC_PLUGIN_STACKLEAK
	अचिन्हित दीर्घ			lowest_stack;
	अचिन्हित दीर्घ			prev_lowest_stack;
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_MCE
	व्योम __user			*mce_vaddr;
	__u64				mce_kflags;
	u64				mce_addr;
	__u64				mce_ripv : 1,
					mce_whole_page : 1,
					__mce_reserved : 62;
	काष्ठा callback_head		mce_समाप्त_me;
#पूर्ण_अगर

#अगर_घोषित CONFIG_KRETPROBES
	काष्ठा llist_head               kretprobe_instances;
#पूर्ण_अगर

	/*
	 * New fields क्रम task_काष्ठा should be added above here, so that
	 * they are included in the अक्रमomized portion of task_काष्ठा.
	 */
	अक्रमomized_काष्ठा_fields_end

	/* CPU-specअगरic state of this task: */
	काष्ठा thपढ़ो_काष्ठा		thपढ़ो;

	/*
	 * WARNING: on x86, 'thread_struct' contains a variable-sized
	 * काष्ठाure.  It *MUST* be at the end of 'task_struct'.
	 *
	 * Do not put anything below here!
	 */
पूर्ण;

अटल अंतरभूत काष्ठा pid *task_pid(काष्ठा task_काष्ठा *task)
अणु
	वापस task->thपढ़ो_pid;
पूर्ण

/*
 * the helpers to get the task's dअगरferent pids as they are seen
 * from various namespaces
 *
 * task_xid_nr()     : global id, i.e. the id seen from the init namespace;
 * task_xid_vnr()    : भव id, i.e. the id seen from the pid namespace of
 *                     current.
 * task_xid_nr_ns()  : id seen from the ns specअगरied;
 *
 * see also pid_nr() etc in include/linux/pid.h
 */
pid_t __task_pid_nr_ns(काष्ठा task_काष्ठा *task, क्रमागत pid_type type, काष्ठा pid_namespace *ns);

अटल अंतरभूत pid_t task_pid_nr(काष्ठा task_काष्ठा *tsk)
अणु
	वापस tsk->pid;
पूर्ण

अटल अंतरभूत pid_t task_pid_nr_ns(काष्ठा task_काष्ठा *tsk, काष्ठा pid_namespace *ns)
अणु
	वापस __task_pid_nr_ns(tsk, PIDTYPE_PID, ns);
पूर्ण

अटल अंतरभूत pid_t task_pid_vnr(काष्ठा task_काष्ठा *tsk)
अणु
	वापस __task_pid_nr_ns(tsk, PIDTYPE_PID, शून्य);
पूर्ण


अटल अंतरभूत pid_t task_tgid_nr(काष्ठा task_काष्ठा *tsk)
अणु
	वापस tsk->tgid;
पूर्ण

/**
 * pid_alive - check that a task काष्ठाure is not stale
 * @p: Task काष्ठाure to be checked.
 *
 * Test अगर a process is not yet dead (at most zombie state)
 * If pid_alive fails, then poपूर्णांकers within the task काष्ठाure
 * can be stale and must not be dereferenced.
 *
 * Return: 1 अगर the process is alive. 0 otherwise.
 */
अटल अंतरभूत पूर्णांक pid_alive(स्थिर काष्ठा task_काष्ठा *p)
अणु
	वापस p->thपढ़ो_pid != शून्य;
पूर्ण

अटल अंतरभूत pid_t task_pgrp_nr_ns(काष्ठा task_काष्ठा *tsk, काष्ठा pid_namespace *ns)
अणु
	वापस __task_pid_nr_ns(tsk, PIDTYPE_PGID, ns);
पूर्ण

अटल अंतरभूत pid_t task_pgrp_vnr(काष्ठा task_काष्ठा *tsk)
अणु
	वापस __task_pid_nr_ns(tsk, PIDTYPE_PGID, शून्य);
पूर्ण


अटल अंतरभूत pid_t task_session_nr_ns(काष्ठा task_काष्ठा *tsk, काष्ठा pid_namespace *ns)
अणु
	वापस __task_pid_nr_ns(tsk, PIDTYPE_SID, ns);
पूर्ण

अटल अंतरभूत pid_t task_session_vnr(काष्ठा task_काष्ठा *tsk)
अणु
	वापस __task_pid_nr_ns(tsk, PIDTYPE_SID, शून्य);
पूर्ण

अटल अंतरभूत pid_t task_tgid_nr_ns(काष्ठा task_काष्ठा *tsk, काष्ठा pid_namespace *ns)
अणु
	वापस __task_pid_nr_ns(tsk, PIDTYPE_TGID, ns);
पूर्ण

अटल अंतरभूत pid_t task_tgid_vnr(काष्ठा task_काष्ठा *tsk)
अणु
	वापस __task_pid_nr_ns(tsk, PIDTYPE_TGID, शून्य);
पूर्ण

अटल अंतरभूत pid_t task_ppid_nr_ns(स्थिर काष्ठा task_काष्ठा *tsk, काष्ठा pid_namespace *ns)
अणु
	pid_t pid = 0;

	rcu_पढ़ो_lock();
	अगर (pid_alive(tsk))
		pid = task_tgid_nr_ns(rcu_dereference(tsk->real_parent), ns);
	rcu_पढ़ो_unlock();

	वापस pid;
पूर्ण

अटल अंतरभूत pid_t task_ppid_nr(स्थिर काष्ठा task_काष्ठा *tsk)
अणु
	वापस task_ppid_nr_ns(tsk, &init_pid_ns);
पूर्ण

/* Obsolete, करो not use: */
अटल अंतरभूत pid_t task_pgrp_nr(काष्ठा task_काष्ठा *tsk)
अणु
	वापस task_pgrp_nr_ns(tsk, &init_pid_ns);
पूर्ण

#घोषणा TASK_REPORT_IDLE	(TASK_REPORT + 1)
#घोषणा TASK_REPORT_MAX		(TASK_REPORT_IDLE << 1)

अटल अंतरभूत अचिन्हित पूर्णांक task_state_index(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित पूर्णांक tsk_state = READ_ONCE(tsk->state);
	अचिन्हित पूर्णांक state = (tsk_state | tsk->निकास_state) & TASK_REPORT;

	BUILD_BUG_ON_NOT_POWER_OF_2(TASK_REPORT_MAX);

	अगर (tsk_state == TASK_IDLE)
		state = TASK_REPORT_IDLE;

	वापस fls(state);
पूर्ण

अटल अंतरभूत अक्षर task_index_to_अक्षर(अचिन्हित पूर्णांक state)
अणु
	अटल स्थिर अक्षर state_अक्षर[] = "RSDTtXZPI";

	BUILD_BUG_ON(1 + ilog2(TASK_REPORT_MAX) != माप(state_अक्षर) - 1);

	वापस state_अक्षर[state];
पूर्ण

अटल अंतरभूत अक्षर task_state_to_अक्षर(काष्ठा task_काष्ठा *tsk)
अणु
	वापस task_index_to_अक्षर(task_state_index(tsk));
पूर्ण

/**
 * is_global_init - check अगर a task काष्ठाure is init. Since init
 * is मुक्त to have sub-thपढ़ोs we need to check tgid.
 * @tsk: Task काष्ठाure to be checked.
 *
 * Check अगर a task काष्ठाure is the first user space task the kernel created.
 *
 * Return: 1 अगर the task काष्ठाure is init. 0 otherwise.
 */
अटल अंतरभूत पूर्णांक is_global_init(काष्ठा task_काष्ठा *tsk)
अणु
	वापस task_tgid_nr(tsk) == 1;
पूर्ण

बाह्य काष्ठा pid *cad_pid;

/*
 * Per process flags
 */
#घोषणा PF_VCPU			0x00000001	/* I'm a भव CPU */
#घोषणा PF_IDLE			0x00000002	/* I am an IDLE thपढ़ो */
#घोषणा PF_EXITING		0x00000004	/* Getting shut करोwn */
#घोषणा PF_IO_WORKER		0x00000010	/* Task is an IO worker */
#घोषणा PF_WQ_WORKER		0x00000020	/* I'm a workqueue worker */
#घोषणा PF_FORKNOEXEC		0x00000040	/* Forked but didn't exec */
#घोषणा PF_MCE_PROCESS		0x00000080      /* Process policy on mce errors */
#घोषणा PF_SUPERPRIV		0x00000100	/* Used super-user privileges */
#घोषणा PF_DUMPCORE		0x00000200	/* Dumped core */
#घोषणा PF_SIGNALED		0x00000400	/* Killed by a संकेत */
#घोषणा PF_MEMALLOC		0x00000800	/* Allocating memory */
#घोषणा PF_NPROC_EXCEEDED	0x00001000	/* set_user() noticed that RLIMIT_NPROC was exceeded */
#घोषणा PF_USED_MATH		0x00002000	/* If unset the fpu must be initialized beक्रमe use */
#घोषणा PF_USED_ASYNC		0x00004000	/* Used async_schedule*(), used by module init */
#घोषणा PF_NOFREEZE		0x00008000	/* This thपढ़ो should not be frozen */
#घोषणा PF_FROZEN		0x00010000	/* Frozen क्रम प्रणाली suspend */
#घोषणा PF_KSWAPD		0x00020000	/* I am kswapd */
#घोषणा PF_MEMALLOC_NOFS	0x00040000	/* All allocation requests will inherit GFP_NOFS */
#घोषणा PF_MEMALLOC_NOIO	0x00080000	/* All allocation requests will inherit GFP_NOIO */
#घोषणा PF_LOCAL_THROTTLE	0x00100000	/* Throttle ग_लिखोs only against the bdi I ग_लिखो to,
						 * I am cleaning dirty pages from some other bdi. */
#घोषणा PF_KTHREAD		0x00200000	/* I am a kernel thपढ़ो */
#घोषणा PF_RANDOMIZE		0x00400000	/* Ranकरोmize भव address space */
#घोषणा PF_SWAPWRITE		0x00800000	/* Allowed to ग_लिखो to swap */
#घोषणा PF_NO_SETAFFINITY	0x04000000	/* Userland is not allowed to meddle with cpus_mask */
#घोषणा PF_MCE_EARLY		0x08000000      /* Early समाप्त क्रम mce process policy */
#घोषणा PF_MEMALLOC_PIN		0x10000000	/* Allocation context स्थिरrained to zones which allow दीर्घ term pinning. */
#घोषणा PF_FREEZER_SKIP		0x40000000	/* Freezer should not count it as मुक्तzable */
#घोषणा PF_SUSPEND_TASK		0x80000000      /* This thपढ़ो called मुक्तze_processes() and should not be frozen */

/*
 * Only the _current_ task can पढ़ो/ग_लिखो to tsk->flags, but other
 * tasks can access tsk->flags in पढ़ोonly mode क्रम example
 * with tsk_used_math (like during thपढ़ोed core dumping).
 * There is however an exception to this rule during ptrace
 * or during विभाजन: the ptracer task is allowed to ग_लिखो to the
 * child->flags of its traced child (same goes क्रम विभाजन, the parent
 * can ग_लिखो to the child->flags), because we're guaranteed the
 * child is not running and in turn not changing child->flags
 * at the same समय the parent करोes it.
 */
#घोषणा clear_stopped_child_used_math(child)	करो अणु (child)->flags &= ~PF_USED_MATH; पूर्ण जबतक (0)
#घोषणा set_stopped_child_used_math(child)	करो अणु (child)->flags |= PF_USED_MATH; पूर्ण जबतक (0)
#घोषणा clear_used_math()			clear_stopped_child_used_math(current)
#घोषणा set_used_math()				set_stopped_child_used_math(current)

#घोषणा conditional_stopped_child_used_math(condition, child) \
	करो अणु (child)->flags &= ~PF_USED_MATH, (child)->flags |= (condition) ? PF_USED_MATH : 0; पूर्ण जबतक (0)

#घोषणा conditional_used_math(condition)	conditional_stopped_child_used_math(condition, current)

#घोषणा copy_to_stopped_child_used_math(child) \
	करो अणु (child)->flags &= ~PF_USED_MATH, (child)->flags |= current->flags & PF_USED_MATH; पूर्ण जबतक (0)

/* NOTE: this will वापस 0 or PF_USED_MATH, it will never वापस 1 */
#घोषणा tsk_used_math(p)			((p)->flags & PF_USED_MATH)
#घोषणा used_math()				tsk_used_math(current)

अटल अंतरभूत bool is_percpu_thपढ़ो(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	वापस (current->flags & PF_NO_SETAFFINITY) &&
		(current->nr_cpus_allowed  == 1);
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

/* Per-process atomic flags. */
#घोषणा PFA_NO_NEW_PRIVS		0	/* May not gain new privileges. */
#घोषणा PFA_SPREAD_PAGE			1	/* Spपढ़ो page cache over cpuset */
#घोषणा PFA_SPREAD_SLAB			2	/* Spपढ़ो some slab caches over cpuset */
#घोषणा PFA_SPEC_SSB_DISABLE		3	/* Speculative Store Bypass disabled */
#घोषणा PFA_SPEC_SSB_FORCE_DISABLE	4	/* Speculative Store Bypass क्रमce disabled*/
#घोषणा PFA_SPEC_IB_DISABLE		5	/* Indirect branch speculation restricted */
#घोषणा PFA_SPEC_IB_FORCE_DISABLE	6	/* Indirect branch speculation permanently restricted */
#घोषणा PFA_SPEC_SSB_NOEXEC		7	/* Speculative Store Bypass clear on execve() */

#घोषणा TASK_PFA_TEST(name, func)					\
	अटल अंतरभूत bool task_##func(काष्ठा task_काष्ठा *p)		\
	अणु वापस test_bit(PFA_##name, &p->atomic_flags); पूर्ण

#घोषणा TASK_PFA_SET(name, func)					\
	अटल अंतरभूत व्योम task_set_##func(काष्ठा task_काष्ठा *p)	\
	अणु set_bit(PFA_##name, &p->atomic_flags); पूर्ण

#घोषणा TASK_PFA_CLEAR(name, func)					\
	अटल अंतरभूत व्योम task_clear_##func(काष्ठा task_काष्ठा *p)	\
	अणु clear_bit(PFA_##name, &p->atomic_flags); पूर्ण

TASK_PFA_TEST(NO_NEW_PRIVS, no_new_privs)
TASK_PFA_SET(NO_NEW_PRIVS, no_new_privs)

TASK_PFA_TEST(SPREAD_PAGE, spपढ़ो_page)
TASK_PFA_SET(SPREAD_PAGE, spपढ़ो_page)
TASK_PFA_CLEAR(SPREAD_PAGE, spपढ़ो_page)

TASK_PFA_TEST(SPREAD_SLAB, spपढ़ो_slab)
TASK_PFA_SET(SPREAD_SLAB, spपढ़ो_slab)
TASK_PFA_CLEAR(SPREAD_SLAB, spपढ़ो_slab)

TASK_PFA_TEST(SPEC_SSB_DISABLE, spec_ssb_disable)
TASK_PFA_SET(SPEC_SSB_DISABLE, spec_ssb_disable)
TASK_PFA_CLEAR(SPEC_SSB_DISABLE, spec_ssb_disable)

TASK_PFA_TEST(SPEC_SSB_NOEXEC, spec_ssb_noexec)
TASK_PFA_SET(SPEC_SSB_NOEXEC, spec_ssb_noexec)
TASK_PFA_CLEAR(SPEC_SSB_NOEXEC, spec_ssb_noexec)

TASK_PFA_TEST(SPEC_SSB_FORCE_DISABLE, spec_ssb_क्रमce_disable)
TASK_PFA_SET(SPEC_SSB_FORCE_DISABLE, spec_ssb_क्रमce_disable)

TASK_PFA_TEST(SPEC_IB_DISABLE, spec_ib_disable)
TASK_PFA_SET(SPEC_IB_DISABLE, spec_ib_disable)
TASK_PFA_CLEAR(SPEC_IB_DISABLE, spec_ib_disable)

TASK_PFA_TEST(SPEC_IB_FORCE_DISABLE, spec_ib_क्रमce_disable)
TASK_PFA_SET(SPEC_IB_FORCE_DISABLE, spec_ib_क्रमce_disable)

अटल अंतरभूत व्योम
current_restore_flags(अचिन्हित दीर्घ orig_flags, अचिन्हित दीर्घ flags)
अणु
	current->flags &= ~flags;
	current->flags |= orig_flags & flags;
पूर्ण

बाह्य पूर्णांक cpuset_cpumask_can_shrink(स्थिर काष्ठा cpumask *cur, स्थिर काष्ठा cpumask *trial);
बाह्य पूर्णांक task_can_attach(काष्ठा task_काष्ठा *p, स्थिर काष्ठा cpumask *cs_cpus_allowed);
#अगर_घोषित CONFIG_SMP
बाह्य व्योम करो_set_cpus_allowed(काष्ठा task_काष्ठा *p, स्थिर काष्ठा cpumask *new_mask);
बाह्य पूर्णांक set_cpus_allowed_ptr(काष्ठा task_काष्ठा *p, स्थिर काष्ठा cpumask *new_mask);
#अन्यथा
अटल अंतरभूत व्योम करो_set_cpus_allowed(काष्ठा task_काष्ठा *p, स्थिर काष्ठा cpumask *new_mask)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक set_cpus_allowed_ptr(काष्ठा task_काष्ठा *p, स्थिर काष्ठा cpumask *new_mask)
अणु
	अगर (!cpumask_test_cpu(0, new_mask))
		वापस -EINVAL;
	वापस 0;
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक yield_to(काष्ठा task_काष्ठा *p, bool preempt);
बाह्य व्योम set_user_nice(काष्ठा task_काष्ठा *p, दीर्घ nice);
बाह्य पूर्णांक task_prio(स्थिर काष्ठा task_काष्ठा *p);

/**
 * task_nice - वापस the nice value of a given task.
 * @p: the task in question.
 *
 * Return: The nice value [ -20 ... 0 ... 19 ].
 */
अटल अंतरभूत पूर्णांक task_nice(स्थिर काष्ठा task_काष्ठा *p)
अणु
	वापस PRIO_TO_NICE((p)->अटल_prio);
पूर्ण

बाह्य पूर्णांक can_nice(स्थिर काष्ठा task_काष्ठा *p, स्थिर पूर्णांक nice);
बाह्य पूर्णांक task_curr(स्थिर काष्ठा task_काष्ठा *p);
बाह्य पूर्णांक idle_cpu(पूर्णांक cpu);
बाह्य पूर्णांक available_idle_cpu(पूर्णांक cpu);
बाह्य पूर्णांक sched_setscheduler(काष्ठा task_काष्ठा *, पूर्णांक, स्थिर काष्ठा sched_param *);
बाह्य पूर्णांक sched_setscheduler_nocheck(काष्ठा task_काष्ठा *, पूर्णांक, स्थिर काष्ठा sched_param *);
बाह्य व्योम sched_set_fअगरo(काष्ठा task_काष्ठा *p);
बाह्य व्योम sched_set_fअगरo_low(काष्ठा task_काष्ठा *p);
बाह्य व्योम sched_set_normal(काष्ठा task_काष्ठा *p, पूर्णांक nice);
बाह्य पूर्णांक sched_setattr(काष्ठा task_काष्ठा *, स्थिर काष्ठा sched_attr *);
बाह्य पूर्णांक sched_setattr_nocheck(काष्ठा task_काष्ठा *, स्थिर काष्ठा sched_attr *);
बाह्य काष्ठा task_काष्ठा *idle_task(पूर्णांक cpu);

/**
 * is_idle_task - is the specअगरied task an idle task?
 * @p: the task in question.
 *
 * Return: 1 अगर @p is an idle task. 0 otherwise.
 */
अटल __always_अंतरभूत bool is_idle_task(स्थिर काष्ठा task_काष्ठा *p)
अणु
	वापस !!(p->flags & PF_IDLE);
पूर्ण

बाह्य काष्ठा task_काष्ठा *curr_task(पूर्णांक cpu);
बाह्य व्योम ia64_set_curr_task(पूर्णांक cpu, काष्ठा task_काष्ठा *p);

व्योम yield(व्योम);

जोड़ thपढ़ो_जोड़ अणु
#अगर_अघोषित CONFIG_ARCH_TASK_STRUCT_ON_STACK
	काष्ठा task_काष्ठा task;
#पूर्ण_अगर
#अगर_अघोषित CONFIG_THREAD_INFO_IN_TASK
	काष्ठा thपढ़ो_info thपढ़ो_info;
#पूर्ण_अगर
	अचिन्हित दीर्घ stack[THREAD_SIZE/माप(दीर्घ)];
पूर्ण;

#अगर_अघोषित CONFIG_THREAD_INFO_IN_TASK
बाह्य काष्ठा thपढ़ो_info init_thपढ़ो_info;
#पूर्ण_अगर

बाह्य अचिन्हित दीर्घ init_stack[THREAD_SIZE / माप(अचिन्हित दीर्घ)];

#अगर_घोषित CONFIG_THREAD_INFO_IN_TASK
अटल अंतरभूत काष्ठा thपढ़ो_info *task_thपढ़ो_info(काष्ठा task_काष्ठा *task)
अणु
	वापस &task->thपढ़ो_info;
पूर्ण
#या_अगर !defined(__HAVE_THREAD_FUNCTIONS)
# define task_thपढ़ो_info(task)	((काष्ठा thपढ़ो_info *)(task)->stack)
#पूर्ण_अगर

/*
 * find a task by one of its numerical ids
 *
 * find_task_by_pid_ns():
 *      finds a task by its pid in the specअगरied namespace
 * find_task_by_vpid():
 *      finds a task by its भव pid
 *
 * see also find_vpid() etc in include/linux/pid.h
 */

बाह्य काष्ठा task_काष्ठा *find_task_by_vpid(pid_t nr);
बाह्य काष्ठा task_काष्ठा *find_task_by_pid_ns(pid_t nr, काष्ठा pid_namespace *ns);

/*
 * find a task by its भव pid and get the task काष्ठा
 */
बाह्य काष्ठा task_काष्ठा *find_get_task_by_vpid(pid_t nr);

बाह्य पूर्णांक wake_up_state(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक state);
बाह्य पूर्णांक wake_up_process(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम wake_up_new_task(काष्ठा task_काष्ठा *tsk);

#अगर_घोषित CONFIG_SMP
बाह्य व्योम kick_process(काष्ठा task_काष्ठा *tsk);
#अन्यथा
अटल अंतरभूत व्योम kick_process(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
#पूर्ण_अगर

बाह्य व्योम __set_task_comm(काष्ठा task_काष्ठा *tsk, स्थिर अक्षर *from, bool exec);

अटल अंतरभूत व्योम set_task_comm(काष्ठा task_काष्ठा *tsk, स्थिर अक्षर *from)
अणु
	__set_task_comm(tsk, from, false);
पूर्ण

बाह्य अक्षर *__get_task_comm(अक्षर *to, माप_प्रकार len, काष्ठा task_काष्ठा *tsk);
#घोषणा get_task_comm(buf, tsk) (अणु			\
	BUILD_BUG_ON(माप(buf) != TASK_COMM_LEN);	\
	__get_task_comm(buf, माप(buf), tsk);		\
पूर्ण)

#अगर_घोषित CONFIG_SMP
अटल __always_अंतरभूत व्योम scheduler_ipi(व्योम)
अणु
	/*
	 * Fold TIF_NEED_RESCHED पूर्णांकo the preempt_count; anybody setting
	 * TIF_NEED_RESCHED remotely (क्रम the first समय) will also send
	 * this IPI.
	 */
	preempt_fold_need_resched();
पूर्ण
बाह्य अचिन्हित दीर्घ रुको_task_inactive(काष्ठा task_काष्ठा *, दीर्घ match_state);
#अन्यथा
अटल अंतरभूत व्योम scheduler_ipi(व्योम) अणु पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ रुको_task_inactive(काष्ठा task_काष्ठा *p, दीर्घ match_state)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर

/*
 * Set thपढ़ो flags in other task's काष्ठाures.
 * See यंत्र/thपढ़ो_info.h क्रम TIF_xxxx flags available:
 */
अटल अंतरभूत व्योम set_tsk_thपढ़ो_flag(काष्ठा task_काष्ठा *tsk, पूर्णांक flag)
अणु
	set_ti_thपढ़ो_flag(task_thपढ़ो_info(tsk), flag);
पूर्ण

अटल अंतरभूत व्योम clear_tsk_thपढ़ो_flag(काष्ठा task_काष्ठा *tsk, पूर्णांक flag)
अणु
	clear_ti_thपढ़ो_flag(task_thपढ़ो_info(tsk), flag);
पूर्ण

अटल अंतरभूत व्योम update_tsk_thपढ़ो_flag(काष्ठा task_काष्ठा *tsk, पूर्णांक flag,
					  bool value)
अणु
	update_ti_thपढ़ो_flag(task_thपढ़ो_info(tsk), flag, value);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_set_tsk_thपढ़ो_flag(काष्ठा task_काष्ठा *tsk, पूर्णांक flag)
अणु
	वापस test_and_set_ti_thपढ़ो_flag(task_thपढ़ो_info(tsk), flag);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_clear_tsk_thपढ़ो_flag(काष्ठा task_काष्ठा *tsk, पूर्णांक flag)
अणु
	वापस test_and_clear_ti_thपढ़ो_flag(task_thपढ़ो_info(tsk), flag);
पूर्ण

अटल अंतरभूत पूर्णांक test_tsk_thपढ़ो_flag(काष्ठा task_काष्ठा *tsk, पूर्णांक flag)
अणु
	वापस test_ti_thपढ़ो_flag(task_thपढ़ो_info(tsk), flag);
पूर्ण

अटल अंतरभूत व्योम set_tsk_need_resched(काष्ठा task_काष्ठा *tsk)
अणु
	set_tsk_thपढ़ो_flag(tsk,TIF_NEED_RESCHED);
पूर्ण

अटल अंतरभूत व्योम clear_tsk_need_resched(काष्ठा task_काष्ठा *tsk)
अणु
	clear_tsk_thपढ़ो_flag(tsk,TIF_NEED_RESCHED);
पूर्ण

अटल अंतरभूत पूर्णांक test_tsk_need_resched(काष्ठा task_काष्ठा *tsk)
अणु
	वापस unlikely(test_tsk_thपढ़ो_flag(tsk,TIF_NEED_RESCHED));
पूर्ण

/*
 * cond_resched() and cond_resched_lock(): latency reduction via
 * explicit rescheduling in places that are safe. The वापस
 * value indicates whether a reschedule was करोne in fact.
 * cond_resched_lock() will drop the spinlock beक्रमe scheduling,
 */
#अगर !defined(CONFIG_PREEMPTION) || defined(CONFIG_PREEMPT_DYNAMIC)
बाह्य पूर्णांक __cond_resched(व्योम);

#अगर_घोषित CONFIG_PREEMPT_DYNAMIC

DECLARE_STATIC_CALL(cond_resched, __cond_resched);

अटल __always_अंतरभूत पूर्णांक _cond_resched(व्योम)
अणु
	वापस अटल_call_mod(cond_resched)();
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक _cond_resched(व्योम)
अणु
	वापस __cond_resched();
पूर्ण

#पूर्ण_अगर /* CONFIG_PREEMPT_DYNAMIC */

#अन्यथा

अटल अंतरभूत पूर्णांक _cond_resched(व्योम) अणु वापस 0; पूर्ण

#पूर्ण_अगर /* !defined(CONFIG_PREEMPTION) || defined(CONFIG_PREEMPT_DYNAMIC) */

#घोषणा cond_resched() (अणु			\
	___might_sleep(__खाता__, __LINE__, 0);	\
	_cond_resched();			\
पूर्ण)

बाह्य पूर्णांक __cond_resched_lock(spinlock_t *lock);
बाह्य पूर्णांक __cond_resched_rwlock_पढ़ो(rwlock_t *lock);
बाह्य पूर्णांक __cond_resched_rwlock_ग_लिखो(rwlock_t *lock);

#घोषणा cond_resched_lock(lock) (अणु				\
	___might_sleep(__खाता__, __LINE__, PREEMPT_LOCK_OFFSET);\
	__cond_resched_lock(lock);				\
पूर्ण)

#घोषणा cond_resched_rwlock_पढ़ो(lock) (अणु			\
	__might_sleep(__खाता__, __LINE__, PREEMPT_LOCK_OFFSET);	\
	__cond_resched_rwlock_पढ़ो(lock);			\
पूर्ण)

#घोषणा cond_resched_rwlock_ग_लिखो(lock) (अणु			\
	__might_sleep(__खाता__, __LINE__, PREEMPT_LOCK_OFFSET);	\
	__cond_resched_rwlock_ग_लिखो(lock);			\
पूर्ण)

अटल अंतरभूत व्योम cond_resched_rcu(व्योम)
अणु
#अगर defined(CONFIG_DEBUG_ATOMIC_SLEEP) || !defined(CONFIG_PREEMPT_RCU)
	rcu_पढ़ो_unlock();
	cond_resched();
	rcu_पढ़ो_lock();
#पूर्ण_अगर
पूर्ण

/*
 * Does a critical section need to be broken due to another
 * task रुकोing?: (technically करोes not depend on CONFIG_PREEMPTION,
 * but a general need क्रम low latency)
 */
अटल अंतरभूत पूर्णांक spin_needअवरोध(spinlock_t *lock)
अणु
#अगर_घोषित CONFIG_PREEMPTION
	वापस spin_is_contended(lock);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/*
 * Check अगर a rwlock is contended.
 * Returns non-zero अगर there is another task रुकोing on the rwlock.
 * Returns zero अगर the lock is not contended or the प्रणाली / underlying
 * rwlock implementation करोes not support contention detection.
 * Technically करोes not depend on CONFIG_PREEMPTION, but a general need
 * क्रम low latency.
 */
अटल अंतरभूत पूर्णांक rwlock_needअवरोध(rwlock_t *lock)
अणु
#अगर_घोषित CONFIG_PREEMPTION
	वापस rwlock_is_contended(lock);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल __always_अंतरभूत bool need_resched(व्योम)
अणु
	वापस unlikely(tअगर_need_resched());
पूर्ण

/*
 * Wrappers क्रम p->thपढ़ो_info->cpu access. No-op on UP.
 */
#अगर_घोषित CONFIG_SMP

अटल अंतरभूत अचिन्हित पूर्णांक task_cpu(स्थिर काष्ठा task_काष्ठा *p)
अणु
#अगर_घोषित CONFIG_THREAD_INFO_IN_TASK
	वापस READ_ONCE(p->cpu);
#अन्यथा
	वापस READ_ONCE(task_thपढ़ो_info(p)->cpu);
#पूर्ण_अगर
पूर्ण

बाह्य व्योम set_task_cpu(काष्ठा task_काष्ठा *p, अचिन्हित पूर्णांक cpu);

#अन्यथा

अटल अंतरभूत अचिन्हित पूर्णांक task_cpu(स्थिर काष्ठा task_काष्ठा *p)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम set_task_cpu(काष्ठा task_काष्ठा *p, अचिन्हित पूर्णांक cpu)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

/*
 * In order to reduce various lock holder preemption latencies provide an
 * पूर्णांकerface to see अगर a vCPU is currently running or not.
 *
 * This allows us to terminate optimistic spin loops and block, analogous to
 * the native optimistic spin heuristic of testing अगर the lock owner task is
 * running or not.
 */
#अगर_अघोषित vcpu_is_preempted
अटल अंतरभूत bool vcpu_is_preempted(पूर्णांक cpu)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

बाह्य दीर्घ sched_setaffinity(pid_t pid, स्थिर काष्ठा cpumask *new_mask);
बाह्य दीर्घ sched_getaffinity(pid_t pid, काष्ठा cpumask *mask);

#अगर_अघोषित TASK_SIZE_OF
#घोषणा TASK_SIZE_OF(tsk)	TASK_SIZE
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
/* Returns effective CPU energy utilization, as seen by the scheduler */
अचिन्हित दीर्घ sched_cpu_util(पूर्णांक cpu, अचिन्हित दीर्घ max);
#पूर्ण_अगर /* CONFIG_SMP */

#अगर_घोषित CONFIG_RSEQ

/*
 * Map the event mask on the user-space ABI क्रमागत rseq_cs_flags
 * क्रम direct mask checks.
 */
क्रमागत rseq_event_mask_bits अणु
	RSEQ_EVENT_PREEMPT_BIT	= RSEQ_CS_FLAG_NO_RESTART_ON_PREEMPT_BIT,
	RSEQ_EVENT_SIGNAL_BIT	= RSEQ_CS_FLAG_NO_RESTART_ON_SIGNAL_BIT,
	RSEQ_EVENT_MIGRATE_BIT	= RSEQ_CS_FLAG_NO_RESTART_ON_MIGRATE_BIT,
पूर्ण;

क्रमागत rseq_event_mask अणु
	RSEQ_EVENT_PREEMPT	= (1U << RSEQ_EVENT_PREEMPT_BIT),
	RSEQ_EVENT_SIGNAL	= (1U << RSEQ_EVENT_SIGNAL_BIT),
	RSEQ_EVENT_MIGRATE	= (1U << RSEQ_EVENT_MIGRATE_BIT),
पूर्ण;

अटल अंतरभूत व्योम rseq_set_notअगरy_resume(काष्ठा task_काष्ठा *t)
अणु
	अगर (t->rseq)
		set_tsk_thपढ़ो_flag(t, TIF_NOTIFY_RESUME);
पूर्ण

व्योम __rseq_handle_notअगरy_resume(काष्ठा kसंकेत *sig, काष्ठा pt_regs *regs);

अटल अंतरभूत व्योम rseq_handle_notअगरy_resume(काष्ठा kसंकेत *ksig,
					     काष्ठा pt_regs *regs)
अणु
	अगर (current->rseq)
		__rseq_handle_notअगरy_resume(ksig, regs);
पूर्ण

अटल अंतरभूत व्योम rseq_संकेत_deliver(काष्ठा kसंकेत *ksig,
				       काष्ठा pt_regs *regs)
अणु
	preempt_disable();
	__set_bit(RSEQ_EVENT_SIGNAL_BIT, &current->rseq_event_mask);
	preempt_enable();
	rseq_handle_notअगरy_resume(ksig, regs);
पूर्ण

/* rseq_preempt() requires preemption to be disabled. */
अटल अंतरभूत व्योम rseq_preempt(काष्ठा task_काष्ठा *t)
अणु
	__set_bit(RSEQ_EVENT_PREEMPT_BIT, &t->rseq_event_mask);
	rseq_set_notअगरy_resume(t);
पूर्ण

/* rseq_migrate() requires preemption to be disabled. */
अटल अंतरभूत व्योम rseq_migrate(काष्ठा task_काष्ठा *t)
अणु
	__set_bit(RSEQ_EVENT_MIGRATE_BIT, &t->rseq_event_mask);
	rseq_set_notअगरy_resume(t);
पूर्ण

/*
 * If parent process has a रेजिस्टरed restartable sequences area, the
 * child inherits. Unरेजिस्टर rseq क्रम a clone with CLONE_VM set.
 */
अटल अंतरभूत व्योम rseq_विभाजन(काष्ठा task_काष्ठा *t, अचिन्हित दीर्घ clone_flags)
अणु
	अगर (clone_flags & CLONE_VM) अणु
		t->rseq = शून्य;
		t->rseq_sig = 0;
		t->rseq_event_mask = 0;
	पूर्ण अन्यथा अणु
		t->rseq = current->rseq;
		t->rseq_sig = current->rseq_sig;
		t->rseq_event_mask = current->rseq_event_mask;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम rseq_execve(काष्ठा task_काष्ठा *t)
अणु
	t->rseq = शून्य;
	t->rseq_sig = 0;
	t->rseq_event_mask = 0;
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम rseq_set_notअगरy_resume(काष्ठा task_काष्ठा *t)
अणु
पूर्ण
अटल अंतरभूत व्योम rseq_handle_notअगरy_resume(काष्ठा kसंकेत *ksig,
					     काष्ठा pt_regs *regs)
अणु
पूर्ण
अटल अंतरभूत व्योम rseq_संकेत_deliver(काष्ठा kसंकेत *ksig,
				       काष्ठा pt_regs *regs)
अणु
पूर्ण
अटल अंतरभूत व्योम rseq_preempt(काष्ठा task_काष्ठा *t)
अणु
पूर्ण
अटल अंतरभूत व्योम rseq_migrate(काष्ठा task_काष्ठा *t)
अणु
पूर्ण
अटल अंतरभूत व्योम rseq_विभाजन(काष्ठा task_काष्ठा *t, अचिन्हित दीर्घ clone_flags)
अणु
पूर्ण
अटल अंतरभूत व्योम rseq_execve(काष्ठा task_काष्ठा *t)
अणु
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_RSEQ

व्योम rseq_syscall(काष्ठा pt_regs *regs);

#अन्यथा

अटल अंतरभूत व्योम rseq_syscall(काष्ठा pt_regs *regs)
अणु
पूर्ण

#पूर्ण_अगर

स्थिर काष्ठा sched_avg *sched_trace_cfs_rq_avg(काष्ठा cfs_rq *cfs_rq);
अक्षर *sched_trace_cfs_rq_path(काष्ठा cfs_rq *cfs_rq, अक्षर *str, पूर्णांक len);
पूर्णांक sched_trace_cfs_rq_cpu(काष्ठा cfs_rq *cfs_rq);

स्थिर काष्ठा sched_avg *sched_trace_rq_avg_rt(काष्ठा rq *rq);
स्थिर काष्ठा sched_avg *sched_trace_rq_avg_dl(काष्ठा rq *rq);
स्थिर काष्ठा sched_avg *sched_trace_rq_avg_irq(काष्ठा rq *rq);

पूर्णांक sched_trace_rq_cpu(काष्ठा rq *rq);
पूर्णांक sched_trace_rq_cpu_capacity(काष्ठा rq *rq);
पूर्णांक sched_trace_rq_nr_running(काष्ठा rq *rq);

स्थिर काष्ठा cpumask *sched_trace_rd_span(काष्ठा root_करोमुख्य *rd);

#पूर्ण_अगर
