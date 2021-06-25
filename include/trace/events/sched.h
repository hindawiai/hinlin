<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM sched

#अगर !defined(_TRACE_SCHED_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_SCHED_H

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched/numa_balancing.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/binfmts.h>

/*
 * Tracepoपूर्णांक क्रम calling kthपढ़ो_stop, perक्रमmed to end a kthपढ़ो:
 */
TRACE_EVENT(sched_kthपढ़ो_stop,

	TP_PROTO(काष्ठा task_काष्ठा *t),

	TP_ARGS(t),

	TP_STRUCT__entry(
		__array(	अक्षर,	comm,	TASK_COMM_LEN	)
		__field(	pid_t,	pid			)
	),

	TP_fast_assign(
		स_नकल(__entry->comm, t->comm, TASK_COMM_LEN);
		__entry->pid	= t->pid;
	),

	TP_prपूर्णांकk("comm=%s pid=%d", __entry->comm, __entry->pid)
);

/*
 * Tracepoपूर्णांक क्रम the वापस value of the kthपढ़ो stopping:
 */
TRACE_EVENT(sched_kthपढ़ो_stop_ret,

	TP_PROTO(पूर्णांक ret),

	TP_ARGS(ret),

	TP_STRUCT__entry(
		__field(	पूर्णांक,	ret	)
	),

	TP_fast_assign(
		__entry->ret	= ret;
	),

	TP_prपूर्णांकk("ret=%d", __entry->ret)
);

/**
 * sched_kthपढ़ो_work_queue_work - called when a work माला_लो queued
 * @worker:	poपूर्णांकer to the kthपढ़ो_worker
 * @work:	poपूर्णांकer to काष्ठा kthपढ़ो_work
 *
 * This event occurs when a work is queued immediately or once a
 * delayed work is actually queued (ie: once the delay has been
 * reached).
 */
TRACE_EVENT(sched_kthपढ़ो_work_queue_work,

	TP_PROTO(काष्ठा kthपढ़ो_worker *worker,
		 काष्ठा kthपढ़ो_work *work),

	TP_ARGS(worker, work),

	TP_STRUCT__entry(
		__field( व्योम *,	work	)
		__field( व्योम *,	function)
		__field( व्योम *,	worker)
	),

	TP_fast_assign(
		__entry->work		= work;
		__entry->function	= work->func;
		__entry->worker		= worker;
	),

	TP_prपूर्णांकk("work struct=%p function=%ps worker=%p",
		  __entry->work, __entry->function, __entry->worker)
);

/**
 * sched_kthपढ़ो_work_execute_start - called immediately beक्रमe the work callback
 * @work:	poपूर्णांकer to काष्ठा kthपढ़ो_work
 *
 * Allows to track kthपढ़ो work execution.
 */
TRACE_EVENT(sched_kthपढ़ो_work_execute_start,

	TP_PROTO(काष्ठा kthपढ़ो_work *work),

	TP_ARGS(work),

	TP_STRUCT__entry(
		__field( व्योम *,	work	)
		__field( व्योम *,	function)
	),

	TP_fast_assign(
		__entry->work		= work;
		__entry->function	= work->func;
	),

	TP_prपूर्णांकk("work struct %p: function %ps", __entry->work, __entry->function)
);

/**
 * sched_kthपढ़ो_work_execute_end - called immediately after the work callback
 * @work:	poपूर्णांकer to काष्ठा work_काष्ठा
 * @function:   poपूर्णांकer to worker function
 *
 * Allows to track workqueue execution.
 */
TRACE_EVENT(sched_kthपढ़ो_work_execute_end,

	TP_PROTO(काष्ठा kthपढ़ो_work *work, kthपढ़ो_work_func_t function),

	TP_ARGS(work, function),

	TP_STRUCT__entry(
		__field( व्योम *,	work	)
		__field( व्योम *,	function)
	),

	TP_fast_assign(
		__entry->work		= work;
		__entry->function	= function;
	),

	TP_prपूर्णांकk("work struct %p: function %ps", __entry->work, __entry->function)
);

/*
 * Tracepoपूर्णांक क्रम waking up a task:
 */
DECLARE_EVENT_CLASS(sched_wakeup_ढाँचा,

	TP_PROTO(काष्ठा task_काष्ठा *p),

	TP_ARGS(__perf_task(p)),

	TP_STRUCT__entry(
		__array(	अक्षर,	comm,	TASK_COMM_LEN	)
		__field(	pid_t,	pid			)
		__field(	पूर्णांक,	prio			)
		__field(	पूर्णांक,	success			)
		__field(	पूर्णांक,	target_cpu		)
	),

	TP_fast_assign(
		स_नकल(__entry->comm, p->comm, TASK_COMM_LEN);
		__entry->pid		= p->pid;
		__entry->prio		= p->prio; /* XXX SCHED_DEADLINE */
		__entry->success	= 1; /* rudiment, समाप्त when possible */
		__entry->target_cpu	= task_cpu(p);
	),

	TP_prपूर्णांकk("comm=%s pid=%d prio=%d target_cpu=%03d",
		  __entry->comm, __entry->pid, __entry->prio,
		  __entry->target_cpu)
);

/*
 * Tracepoपूर्णांक called when waking a task; this tracepoपूर्णांक is guaranteed to be
 * called from the waking context.
 */
DEFINE_EVENT(sched_wakeup_ढाँचा, sched_waking,
	     TP_PROTO(काष्ठा task_काष्ठा *p),
	     TP_ARGS(p));

/*
 * Tracepoपूर्णांक called when the task is actually woken; p->state == TASK_RUNNING.
 * It is not always called from the waking context.
 */
DEFINE_EVENT(sched_wakeup_ढाँचा, sched_wakeup,
	     TP_PROTO(काष्ठा task_काष्ठा *p),
	     TP_ARGS(p));

/*
 * Tracepoपूर्णांक क्रम waking up a new task:
 */
DEFINE_EVENT(sched_wakeup_ढाँचा, sched_wakeup_new,
	     TP_PROTO(काष्ठा task_काष्ठा *p),
	     TP_ARGS(p));

#अगर_घोषित CREATE_TRACE_POINTS
अटल अंतरभूत दीर्घ __trace_sched_चयन_state(bool preempt, काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित पूर्णांक state;

#अगर_घोषित CONFIG_SCHED_DEBUG
	BUG_ON(p != current);
#पूर्ण_अगर /* CONFIG_SCHED_DEBUG */

	/*
	 * Preemption ignores task state, thereक्रमe preempted tasks are always
	 * RUNNING (we will not have dequeued अगर state != RUNNING).
	 */
	अगर (preempt)
		वापस TASK_REPORT_MAX;

	/*
	 * task_state_index() uses fls() and वापसs a value from 0-8 range.
	 * Decrement it by 1 (except TASK_RUNNING state i.e 0) beक्रमe using
	 * it क्रम left shअगरt operation to get the correct task->state
	 * mapping.
	 */
	state = task_state_index(p);

	वापस state ? (1 << (state - 1)) : state;
पूर्ण
#पूर्ण_अगर /* CREATE_TRACE_POINTS */

/*
 * Tracepoपूर्णांक क्रम task चयनes, perक्रमmed by the scheduler:
 */
TRACE_EVENT(sched_चयन,

	TP_PROTO(bool preempt,
		 काष्ठा task_काष्ठा *prev,
		 काष्ठा task_काष्ठा *next),

	TP_ARGS(preempt, prev, next),

	TP_STRUCT__entry(
		__array(	अक्षर,	prev_comm,	TASK_COMM_LEN	)
		__field(	pid_t,	prev_pid			)
		__field(	पूर्णांक,	prev_prio			)
		__field(	दीर्घ,	prev_state			)
		__array(	अक्षर,	next_comm,	TASK_COMM_LEN	)
		__field(	pid_t,	next_pid			)
		__field(	पूर्णांक,	next_prio			)
	),

	TP_fast_assign(
		स_नकल(__entry->next_comm, next->comm, TASK_COMM_LEN);
		__entry->prev_pid	= prev->pid;
		__entry->prev_prio	= prev->prio;
		__entry->prev_state	= __trace_sched_चयन_state(preempt, prev);
		स_नकल(__entry->prev_comm, prev->comm, TASK_COMM_LEN);
		__entry->next_pid	= next->pid;
		__entry->next_prio	= next->prio;
		/* XXX SCHED_DEADLINE */
	),

	TP_prपूर्णांकk("prev_comm=%s prev_pid=%d prev_prio=%d prev_state=%s%s ==> next_comm=%s next_pid=%d next_prio=%d",
		__entry->prev_comm, __entry->prev_pid, __entry->prev_prio,

		(__entry->prev_state & (TASK_REPORT_MAX - 1)) ?
		  __prपूर्णांक_flags(__entry->prev_state & (TASK_REPORT_MAX - 1), "|",
				अणु TASK_INTERRUPTIBLE, "S" पूर्ण,
				अणु TASK_UNINTERRUPTIBLE, "D" पूर्ण,
				अणु __TASK_STOPPED, "T" पूर्ण,
				अणु __TASK_TRACED, "t" पूर्ण,
				अणु EXIT_DEAD, "X" पूर्ण,
				अणु EXIT_ZOMBIE, "Z" पूर्ण,
				अणु TASK_PARKED, "P" पूर्ण,
				अणु TASK_DEAD, "I" पूर्ण) :
		  "R",

		__entry->prev_state & TASK_REPORT_MAX ? "+" : "",
		__entry->next_comm, __entry->next_pid, __entry->next_prio)
);

/*
 * Tracepoपूर्णांक क्रम a task being migrated:
 */
TRACE_EVENT(sched_migrate_task,

	TP_PROTO(काष्ठा task_काष्ठा *p, पूर्णांक dest_cpu),

	TP_ARGS(p, dest_cpu),

	TP_STRUCT__entry(
		__array(	अक्षर,	comm,	TASK_COMM_LEN	)
		__field(	pid_t,	pid			)
		__field(	पूर्णांक,	prio			)
		__field(	पूर्णांक,	orig_cpu		)
		__field(	पूर्णांक,	dest_cpu		)
	),

	TP_fast_assign(
		स_नकल(__entry->comm, p->comm, TASK_COMM_LEN);
		__entry->pid		= p->pid;
		__entry->prio		= p->prio; /* XXX SCHED_DEADLINE */
		__entry->orig_cpu	= task_cpu(p);
		__entry->dest_cpu	= dest_cpu;
	),

	TP_prपूर्णांकk("comm=%s pid=%d prio=%d orig_cpu=%d dest_cpu=%d",
		  __entry->comm, __entry->pid, __entry->prio,
		  __entry->orig_cpu, __entry->dest_cpu)
);

DECLARE_EVENT_CLASS(sched_process_ढाँचा,

	TP_PROTO(काष्ठा task_काष्ठा *p),

	TP_ARGS(p),

	TP_STRUCT__entry(
		__array(	अक्षर,	comm,	TASK_COMM_LEN	)
		__field(	pid_t,	pid			)
		__field(	पूर्णांक,	prio			)
	),

	TP_fast_assign(
		स_नकल(__entry->comm, p->comm, TASK_COMM_LEN);
		__entry->pid		= p->pid;
		__entry->prio		= p->prio; /* XXX SCHED_DEADLINE */
	),

	TP_prपूर्णांकk("comm=%s pid=%d prio=%d",
		  __entry->comm, __entry->pid, __entry->prio)
);

/*
 * Tracepoपूर्णांक क्रम मुक्तing a task:
 */
DEFINE_EVENT(sched_process_ढाँचा, sched_process_मुक्त,
	     TP_PROTO(काष्ठा task_काष्ठा *p),
	     TP_ARGS(p));

/*
 * Tracepoपूर्णांक क्रम a task निकासing:
 */
DEFINE_EVENT(sched_process_ढाँचा, sched_process_निकास,
	     TP_PROTO(काष्ठा task_काष्ठा *p),
	     TP_ARGS(p));

/*
 * Tracepoपूर्णांक क्रम रुकोing on task to unschedule:
 */
DEFINE_EVENT(sched_process_ढाँचा, sched_रुको_task,
	TP_PROTO(काष्ठा task_काष्ठा *p),
	TP_ARGS(p));

/*
 * Tracepoपूर्णांक क्रम a रुकोing task:
 */
TRACE_EVENT(sched_process_रुको,

	TP_PROTO(काष्ठा pid *pid),

	TP_ARGS(pid),

	TP_STRUCT__entry(
		__array(	अक्षर,	comm,	TASK_COMM_LEN	)
		__field(	pid_t,	pid			)
		__field(	पूर्णांक,	prio			)
	),

	TP_fast_assign(
		स_नकल(__entry->comm, current->comm, TASK_COMM_LEN);
		__entry->pid		= pid_nr(pid);
		__entry->prio		= current->prio; /* XXX SCHED_DEADLINE */
	),

	TP_prपूर्णांकk("comm=%s pid=%d prio=%d",
		  __entry->comm, __entry->pid, __entry->prio)
);

/*
 * Tracepoपूर्णांक क्रम kernel_clone:
 */
TRACE_EVENT(sched_process_विभाजन,

	TP_PROTO(काष्ठा task_काष्ठा *parent, काष्ठा task_काष्ठा *child),

	TP_ARGS(parent, child),

	TP_STRUCT__entry(
		__array(	अक्षर,	parent_comm,	TASK_COMM_LEN	)
		__field(	pid_t,	parent_pid			)
		__array(	अक्षर,	child_comm,	TASK_COMM_LEN	)
		__field(	pid_t,	child_pid			)
	),

	TP_fast_assign(
		स_नकल(__entry->parent_comm, parent->comm, TASK_COMM_LEN);
		__entry->parent_pid	= parent->pid;
		स_नकल(__entry->child_comm, child->comm, TASK_COMM_LEN);
		__entry->child_pid	= child->pid;
	),

	TP_prपूर्णांकk("comm=%s pid=%d child_comm=%s child_pid=%d",
		__entry->parent_comm, __entry->parent_pid,
		__entry->child_comm, __entry->child_pid)
);

/*
 * Tracepoपूर्णांक क्रम exec:
 */
TRACE_EVENT(sched_process_exec,

	TP_PROTO(काष्ठा task_काष्ठा *p, pid_t old_pid,
		 काष्ठा linux_binprm *bprm),

	TP_ARGS(p, old_pid, bprm),

	TP_STRUCT__entry(
		__string(	filename,	bprm->filename	)
		__field(	pid_t,		pid		)
		__field(	pid_t,		old_pid		)
	),

	TP_fast_assign(
		__assign_str(filename, bprm->filename);
		__entry->pid		= p->pid;
		__entry->old_pid	= old_pid;
	),

	TP_prपूर्णांकk("filename=%s pid=%d old_pid=%d", __get_str(filename),
		  __entry->pid, __entry->old_pid)
);


#अगर_घोषित CONFIG_SCHEDSTATS
#घोषणा DEFINE_EVENT_SCHEDSTAT DEFINE_EVENT
#घोषणा DECLARE_EVENT_CLASS_SCHEDSTAT DECLARE_EVENT_CLASS
#अन्यथा
#घोषणा DEFINE_EVENT_SCHEDSTAT DEFINE_EVENT_NOP
#घोषणा DECLARE_EVENT_CLASS_SCHEDSTAT DECLARE_EVENT_CLASS_NOP
#पूर्ण_अगर

/*
 * XXX the below sched_stat tracepoपूर्णांकs only apply to SCHED_OTHER/BATCH/IDLE
 *     adding sched_stat support to SCHED_FIFO/RR would be welcome.
 */
DECLARE_EVENT_CLASS_SCHEDSTAT(sched_stat_ढाँचा,

	TP_PROTO(काष्ठा task_काष्ठा *tsk, u64 delay),

	TP_ARGS(__perf_task(tsk), __perf_count(delay)),

	TP_STRUCT__entry(
		__array( अक्षर,	comm,	TASK_COMM_LEN	)
		__field( pid_t,	pid			)
		__field( u64,	delay			)
	),

	TP_fast_assign(
		स_नकल(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid	= tsk->pid;
		__entry->delay	= delay;
	),

	TP_prपूर्णांकk("comm=%s pid=%d delay=%Lu [ns]",
			__entry->comm, __entry->pid,
			(अचिन्हित दीर्घ दीर्घ)__entry->delay)
);

/*
 * Tracepoपूर्णांक क्रम accounting रुको समय (समय the task is runnable
 * but not actually running due to scheduler contention).
 */
DEFINE_EVENT_SCHEDSTAT(sched_stat_ढाँचा, sched_stat_रुको,
	     TP_PROTO(काष्ठा task_काष्ठा *tsk, u64 delay),
	     TP_ARGS(tsk, delay));

/*
 * Tracepoपूर्णांक क्रम accounting sleep समय (समय the task is not runnable,
 * including ioरुको, see below).
 */
DEFINE_EVENT_SCHEDSTAT(sched_stat_ढाँचा, sched_stat_sleep,
	     TP_PROTO(काष्ठा task_काष्ठा *tsk, u64 delay),
	     TP_ARGS(tsk, delay));

/*
 * Tracepoपूर्णांक क्रम accounting ioरुको समय (समय the task is not runnable
 * due to रुकोing on IO to complete).
 */
DEFINE_EVENT_SCHEDSTAT(sched_stat_ढाँचा, sched_stat_ioरुको,
	     TP_PROTO(काष्ठा task_काष्ठा *tsk, u64 delay),
	     TP_ARGS(tsk, delay));

/*
 * Tracepoपूर्णांक क्रम accounting blocked समय (समय the task is in unपूर्णांकerruptible).
 */
DEFINE_EVENT_SCHEDSTAT(sched_stat_ढाँचा, sched_stat_blocked,
	     TP_PROTO(काष्ठा task_काष्ठा *tsk, u64 delay),
	     TP_ARGS(tsk, delay));

/*
 * Tracepoपूर्णांक क्रम accounting runसमय (समय the task is executing
 * on a CPU).
 */
DECLARE_EVENT_CLASS(sched_stat_runसमय,

	TP_PROTO(काष्ठा task_काष्ठा *tsk, u64 runसमय, u64 vrunसमय),

	TP_ARGS(tsk, __perf_count(runसमय), vrunसमय),

	TP_STRUCT__entry(
		__array( अक्षर,	comm,	TASK_COMM_LEN	)
		__field( pid_t,	pid			)
		__field( u64,	runसमय			)
		__field( u64,	vrunसमय			)
	),

	TP_fast_assign(
		स_नकल(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid		= tsk->pid;
		__entry->runसमय	= runसमय;
		__entry->vrunसमय	= vrunसमय;
	),

	TP_prपूर्णांकk("comm=%s pid=%d runtime=%Lu [ns] vruntime=%Lu [ns]",
			__entry->comm, __entry->pid,
			(अचिन्हित दीर्घ दीर्घ)__entry->runसमय,
			(अचिन्हित दीर्घ दीर्घ)__entry->vrunसमय)
);

DEFINE_EVENT(sched_stat_runसमय, sched_stat_runसमय,
	     TP_PROTO(काष्ठा task_काष्ठा *tsk, u64 runसमय, u64 vrunसमय),
	     TP_ARGS(tsk, runसमय, vrunसमय));

/*
 * Tracepoपूर्णांक क्रम showing priority inheritance modअगरying a tasks
 * priority.
 */
TRACE_EVENT(sched_pi_setprio,

	TP_PROTO(काष्ठा task_काष्ठा *tsk, काष्ठा task_काष्ठा *pi_task),

	TP_ARGS(tsk, pi_task),

	TP_STRUCT__entry(
		__array( अक्षर,	comm,	TASK_COMM_LEN	)
		__field( pid_t,	pid			)
		__field( पूर्णांक,	oldprio			)
		__field( पूर्णांक,	newprio			)
	),

	TP_fast_assign(
		स_नकल(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid		= tsk->pid;
		__entry->oldprio	= tsk->prio;
		__entry->newprio	= pi_task ?
				min(tsk->normal_prio, pi_task->prio) :
				tsk->normal_prio;
		/* XXX SCHED_DEADLINE bits missing */
	),

	TP_prपूर्णांकk("comm=%s pid=%d oldprio=%d newprio=%d",
			__entry->comm, __entry->pid,
			__entry->oldprio, __entry->newprio)
);

#अगर_घोषित CONFIG_DETECT_HUNG_TASK
TRACE_EVENT(sched_process_hang,
	TP_PROTO(काष्ठा task_काष्ठा *tsk),
	TP_ARGS(tsk),

	TP_STRUCT__entry(
		__array( अक्षर,	comm,	TASK_COMM_LEN	)
		__field( pid_t,	pid			)
	),

	TP_fast_assign(
		स_नकल(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid = tsk->pid;
	),

	TP_prपूर्णांकk("comm=%s pid=%d", __entry->comm, __entry->pid)
);
#पूर्ण_अगर /* CONFIG_DETECT_HUNG_TASK */

/*
 * Tracks migration of tasks from one runqueue to another. Can be used to
 * detect अगर स्वतःmatic NUMA balancing is bouncing between nodes.
 */
TRACE_EVENT(sched_move_numa,

	TP_PROTO(काष्ठा task_काष्ठा *tsk, पूर्णांक src_cpu, पूर्णांक dst_cpu),

	TP_ARGS(tsk, src_cpu, dst_cpu),

	TP_STRUCT__entry(
		__field( pid_t,	pid			)
		__field( pid_t,	tgid			)
		__field( pid_t,	ngid			)
		__field( पूर्णांक,	src_cpu			)
		__field( पूर्णांक,	src_nid			)
		__field( पूर्णांक,	dst_cpu			)
		__field( पूर्णांक,	dst_nid			)
	),

	TP_fast_assign(
		__entry->pid		= task_pid_nr(tsk);
		__entry->tgid		= task_tgid_nr(tsk);
		__entry->ngid		= task_numa_group_id(tsk);
		__entry->src_cpu	= src_cpu;
		__entry->src_nid	= cpu_to_node(src_cpu);
		__entry->dst_cpu	= dst_cpu;
		__entry->dst_nid	= cpu_to_node(dst_cpu);
	),

	TP_prपूर्णांकk("pid=%d tgid=%d ngid=%d src_cpu=%d src_nid=%d dst_cpu=%d dst_nid=%d",
			__entry->pid, __entry->tgid, __entry->ngid,
			__entry->src_cpu, __entry->src_nid,
			__entry->dst_cpu, __entry->dst_nid)
);

DECLARE_EVENT_CLASS(sched_numa_pair_ढाँचा,

	TP_PROTO(काष्ठा task_काष्ठा *src_tsk, पूर्णांक src_cpu,
		 काष्ठा task_काष्ठा *dst_tsk, पूर्णांक dst_cpu),

	TP_ARGS(src_tsk, src_cpu, dst_tsk, dst_cpu),

	TP_STRUCT__entry(
		__field( pid_t,	src_pid			)
		__field( pid_t,	src_tgid		)
		__field( pid_t,	src_ngid		)
		__field( पूर्णांक,	src_cpu			)
		__field( पूर्णांक,	src_nid			)
		__field( pid_t,	dst_pid			)
		__field( pid_t,	dst_tgid		)
		__field( pid_t,	dst_ngid		)
		__field( पूर्णांक,	dst_cpu			)
		__field( पूर्णांक,	dst_nid			)
	),

	TP_fast_assign(
		__entry->src_pid	= task_pid_nr(src_tsk);
		__entry->src_tgid	= task_tgid_nr(src_tsk);
		__entry->src_ngid	= task_numa_group_id(src_tsk);
		__entry->src_cpu	= src_cpu;
		__entry->src_nid	= cpu_to_node(src_cpu);
		__entry->dst_pid	= dst_tsk ? task_pid_nr(dst_tsk) : 0;
		__entry->dst_tgid	= dst_tsk ? task_tgid_nr(dst_tsk) : 0;
		__entry->dst_ngid	= dst_tsk ? task_numa_group_id(dst_tsk) : 0;
		__entry->dst_cpu	= dst_cpu;
		__entry->dst_nid	= dst_cpu >= 0 ? cpu_to_node(dst_cpu) : -1;
	),

	TP_prपूर्णांकk("src_pid=%d src_tgid=%d src_ngid=%d src_cpu=%d src_nid=%d dst_pid=%d dst_tgid=%d dst_ngid=%d dst_cpu=%d dst_nid=%d",
			__entry->src_pid, __entry->src_tgid, __entry->src_ngid,
			__entry->src_cpu, __entry->src_nid,
			__entry->dst_pid, __entry->dst_tgid, __entry->dst_ngid,
			__entry->dst_cpu, __entry->dst_nid)
);

DEFINE_EVENT(sched_numa_pair_ढाँचा, sched_stick_numa,

	TP_PROTO(काष्ठा task_काष्ठा *src_tsk, पूर्णांक src_cpu,
		 काष्ठा task_काष्ठा *dst_tsk, पूर्णांक dst_cpu),

	TP_ARGS(src_tsk, src_cpu, dst_tsk, dst_cpu)
);

DEFINE_EVENT(sched_numa_pair_ढाँचा, sched_swap_numa,

	TP_PROTO(काष्ठा task_काष्ठा *src_tsk, पूर्णांक src_cpu,
		 काष्ठा task_काष्ठा *dst_tsk, पूर्णांक dst_cpu),

	TP_ARGS(src_tsk, src_cpu, dst_tsk, dst_cpu)
);


/*
 * Tracepoपूर्णांक क्रम waking a polling cpu without an IPI.
 */
TRACE_EVENT(sched_wake_idle_without_ipi,

	TP_PROTO(पूर्णांक cpu),

	TP_ARGS(cpu),

	TP_STRUCT__entry(
		__field(	पूर्णांक,	cpu	)
	),

	TP_fast_assign(
		__entry->cpu	= cpu;
	),

	TP_prपूर्णांकk("cpu=%d", __entry->cpu)
);

/*
 * Following tracepoपूर्णांकs are not exported in tracefs and provide hooking
 * mechanisms only क्रम testing and debugging purposes.
 *
 * Postfixed with _tp to make them easily identअगरiable in the code.
 */
DECLARE_TRACE(pelt_cfs_tp,
	TP_PROTO(काष्ठा cfs_rq *cfs_rq),
	TP_ARGS(cfs_rq));

DECLARE_TRACE(pelt_rt_tp,
	TP_PROTO(काष्ठा rq *rq),
	TP_ARGS(rq));

DECLARE_TRACE(pelt_dl_tp,
	TP_PROTO(काष्ठा rq *rq),
	TP_ARGS(rq));

DECLARE_TRACE(pelt_thermal_tp,
	TP_PROTO(काष्ठा rq *rq),
	TP_ARGS(rq));

DECLARE_TRACE(pelt_irq_tp,
	TP_PROTO(काष्ठा rq *rq),
	TP_ARGS(rq));

DECLARE_TRACE(pelt_se_tp,
	TP_PROTO(काष्ठा sched_entity *se),
	TP_ARGS(se));

DECLARE_TRACE(sched_cpu_capacity_tp,
	TP_PROTO(काष्ठा rq *rq),
	TP_ARGS(rq));

DECLARE_TRACE(sched_overutilized_tp,
	TP_PROTO(काष्ठा root_करोमुख्य *rd, bool overutilized),
	TP_ARGS(rd, overutilized));

DECLARE_TRACE(sched_util_est_cfs_tp,
	TP_PROTO(काष्ठा cfs_rq *cfs_rq),
	TP_ARGS(cfs_rq));

DECLARE_TRACE(sched_util_est_se_tp,
	TP_PROTO(काष्ठा sched_entity *se),
	TP_ARGS(se));

DECLARE_TRACE(sched_update_nr_running_tp,
	TP_PROTO(काष्ठा rq *rq, पूर्णांक change),
	TP_ARGS(rq, change));

#पूर्ण_अगर /* _TRACE_SCHED_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
