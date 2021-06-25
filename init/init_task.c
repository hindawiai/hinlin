<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init_task.h>
#समावेश <linux/export.h>
#समावेश <linux/mqueue.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/sysctl.h>
#समावेश <linux/sched/rt.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/audit.h>
#समावेश <linux/numa.h>
#समावेश <linux/scs.h>

#समावेश <linux/uaccess.h>

अटल काष्ठा संकेत_काष्ठा init_संकेतs = अणु
	.nr_thपढ़ोs	= 1,
	.thपढ़ो_head	= LIST_HEAD_INIT(init_task.thपढ़ो_node),
	.रुको_chldनिकास	= __WAIT_QUEUE_HEAD_INITIALIZER(init_संकेतs.रुको_chldनिकास),
	.shared_pending	= अणु
		.list = LIST_HEAD_INIT(init_संकेतs.shared_pending.list),
		.संकेत =  अणुअणु0पूर्णपूर्ण
	पूर्ण,
	.multiprocess	= HLIST_HEAD_INIT,
	.rlim		= INIT_RLIMITS,
	.cred_guard_mutex = __MUTEX_INITIALIZER(init_संकेतs.cred_guard_mutex),
	.exec_update_lock = __RWSEM_INITIALIZER(init_संकेतs.exec_update_lock),
#अगर_घोषित CONFIG_POSIX_TIMERS
	.posix_समयrs = LIST_HEAD_INIT(init_संकेतs.posix_समयrs),
	.cpuसमयr	= अणु
		.cpuसमय_atomic	= INIT_CPUTIME_ATOMIC,
	पूर्ण,
#पूर्ण_अगर
	INIT_CPU_TIMERS(init_संकेतs)
	.pids = अणु
		[PIDTYPE_PID]	= &init_काष्ठा_pid,
		[PIDTYPE_TGID]	= &init_काष्ठा_pid,
		[PIDTYPE_PGID]	= &init_काष्ठा_pid,
		[PIDTYPE_SID]	= &init_काष्ठा_pid,
	पूर्ण,
	INIT_PREV_CPUTIME(init_संकेतs)
पूर्ण;

अटल काष्ठा sighand_काष्ठा init_sighand = अणु
	.count		= REFCOUNT_INIT(1),
	.action		= अणु अणु अणु .sa_handler = संक_पूर्व, पूर्ण पूर्ण, पूर्ण,
	.siglock	= __SPIN_LOCK_UNLOCKED(init_sighand.siglock),
	.संकेतfd_wqh	= __WAIT_QUEUE_HEAD_INITIALIZER(init_sighand.संकेतfd_wqh),
पूर्ण;

#अगर_घोषित CONFIG_SHADOW_CALL_STACK
अचिन्हित दीर्घ init_shaकरोw_call_stack[SCS_SIZE / माप(दीर्घ)]
		__init_task_data = अणु
	[(SCS_SIZE / माप(दीर्घ)) - 1] = SCS_END_MAGIC
पूर्ण;
#पूर्ण_अगर

/*
 * Set up the first task table, touch at your own risk!. Base=0,
 * limit=0x1fffff (=2MB)
 */
काष्ठा task_काष्ठा init_task
#अगर_घोषित CONFIG_ARCH_TASK_STRUCT_ON_STACK
	__init_task_data
#पूर्ण_अगर
	__aligned(L1_CACHE_BYTES)
= अणु
#अगर_घोषित CONFIG_THREAD_INFO_IN_TASK
	.thपढ़ो_info	= INIT_THREAD_INFO(init_task),
	.stack_refcount	= REFCOUNT_INIT(1),
#पूर्ण_अगर
	.state		= 0,
	.stack		= init_stack,
	.usage		= REFCOUNT_INIT(2),
	.flags		= PF_KTHREAD,
	.prio		= MAX_PRIO - 20,
	.अटल_prio	= MAX_PRIO - 20,
	.normal_prio	= MAX_PRIO - 20,
	.policy		= SCHED_NORMAL,
	.cpus_ptr	= &init_task.cpus_mask,
	.cpus_mask	= CPU_MASK_ALL,
	.nr_cpus_allowed= NR_CPUS,
	.mm		= शून्य,
	.active_mm	= &init_mm,
	.restart_block	= अणु
		.fn = करो_no_restart_syscall,
	पूर्ण,
	.se		= अणु
		.group_node 	= LIST_HEAD_INIT(init_task.se.group_node),
	पूर्ण,
	.rt		= अणु
		.run_list	= LIST_HEAD_INIT(init_task.rt.run_list),
		.समय_slice	= RR_TIMESLICE,
	पूर्ण,
	.tasks		= LIST_HEAD_INIT(init_task.tasks),
#अगर_घोषित CONFIG_SMP
	.pushable_tasks	= PLIST_NODE_INIT(init_task.pushable_tasks, MAX_PRIO),
#पूर्ण_अगर
#अगर_घोषित CONFIG_CGROUP_SCHED
	.sched_task_group = &root_task_group,
#पूर्ण_अगर
	.ptraced	= LIST_HEAD_INIT(init_task.ptraced),
	.ptrace_entry	= LIST_HEAD_INIT(init_task.ptrace_entry),
	.real_parent	= &init_task,
	.parent		= &init_task,
	.children	= LIST_HEAD_INIT(init_task.children),
	.sibling	= LIST_HEAD_INIT(init_task.sibling),
	.group_leader	= &init_task,
	RCU_POINTER_INITIALIZER(real_cred, &init_cred),
	RCU_POINTER_INITIALIZER(cred, &init_cred),
	.comm		= INIT_TASK_COMM,
	.thपढ़ो		= INIT_THREAD,
	.fs		= &init_fs,
	.files		= &init_files,
#अगर_घोषित CONFIG_IO_URING
	.io_uring	= शून्य,
#पूर्ण_अगर
	.संकेत		= &init_संकेतs,
	.sighand	= &init_sighand,
	.nsproxy	= &init_nsproxy,
	.pending	= अणु
		.list = LIST_HEAD_INIT(init_task.pending.list),
		.संकेत = अणुअणु0पूर्णपूर्ण
	पूर्ण,
	.blocked	= अणुअणु0पूर्णपूर्ण,
	.alloc_lock	= __SPIN_LOCK_UNLOCKED(init_task.alloc_lock),
	.journal_info	= शून्य,
	INIT_CPU_TIMERS(init_task)
	.pi_lock	= __RAW_SPIN_LOCK_UNLOCKED(init_task.pi_lock),
	.समयr_slack_ns = 50000, /* 50 usec शेष slack */
	.thपढ़ो_pid	= &init_काष्ठा_pid,
	.thपढ़ो_group	= LIST_HEAD_INIT(init_task.thपढ़ो_group),
	.thपढ़ो_node	= LIST_HEAD_INIT(init_संकेतs.thपढ़ो_head),
#अगर_घोषित CONFIG_AUDIT
	.loginuid	= INVALID_UID,
	.sessionid	= AUDIT_SID_UNSET,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PERF_EVENTS
	.perf_event_mutex = __MUTEX_INITIALIZER(init_task.perf_event_mutex),
	.perf_event_list = LIST_HEAD_INIT(init_task.perf_event_list),
#पूर्ण_अगर
#अगर_घोषित CONFIG_PREEMPT_RCU
	.rcu_पढ़ो_lock_nesting = 0,
	.rcu_पढ़ो_unlock_special.s = 0,
	.rcu_node_entry = LIST_HEAD_INIT(init_task.rcu_node_entry),
	.rcu_blocked_node = शून्य,
#पूर्ण_अगर
#अगर_घोषित CONFIG_TASKS_RCU
	.rcu_tasks_holकरोut = false,
	.rcu_tasks_holकरोut_list = LIST_HEAD_INIT(init_task.rcu_tasks_holकरोut_list),
	.rcu_tasks_idle_cpu = -1,
#पूर्ण_अगर
#अगर_घोषित CONFIG_TASKS_TRACE_RCU
	.trc_पढ़ोer_nesting = 0,
	.trc_पढ़ोer_special.s = 0,
	.trc_holकरोut_list = LIST_HEAD_INIT(init_task.trc_holकरोut_list),
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPUSETS
	.mems_allowed_seq = SEQCNT_SPINLOCK_ZERO(init_task.mems_allowed_seq,
						 &init_task.alloc_lock),
#पूर्ण_अगर
#अगर_घोषित CONFIG_RT_MUTEXES
	.pi_रुकोers	= RB_ROOT_CACHED,
	.pi_top_task	= शून्य,
#पूर्ण_अगर
	INIT_PREV_CPUTIME(init_task)
#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_GEN
	.vसमय.seqcount	= SEQCNT_ZERO(init_task.vसमय_seqcount),
	.vसमय.startसमय = 0,
	.vसमय.state	= VTIME_SYS,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NUMA_BALANCING
	.numa_preferred_nid = NUMA_NO_NODE,
	.numa_group	= शून्य,
	.numa_faults	= शून्य,
#पूर्ण_अगर
#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)
	.kasan_depth	= 1,
#पूर्ण_अगर
#अगर_घोषित CONFIG_KCSAN
	.kcsan_ctx = अणु
		.disable_count		= 0,
		.atomic_next		= 0,
		.atomic_nest_count	= 0,
		.in_flat_atomic		= false,
		.access_mask		= 0,
		.scoped_accesses	= अणुLIST_POISON1, शून्यपूर्ण,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_TRACE_IRQFLAGS
	.softirqs_enabled = 1,
#पूर्ण_अगर
#अगर_घोषित CONFIG_LOCKDEP
	.lockdep_depth = 0, /* no locks held yet */
	.curr_chain_key = INITIAL_CHAIN_KEY,
	.lockdep_recursion = 0,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	.ret_stack		= शून्य,
	.tracing_graph_छोड़ो	= ATOMIC_INIT(0),
#पूर्ण_अगर
#अगर defined(CONFIG_TRACING) && defined(CONFIG_PREEMPTION)
	.trace_recursion = 0,
#पूर्ण_अगर
#अगर_घोषित CONFIG_LIVEPATCH
	.patch_state	= KLP_UNDEFINED,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECURITY
	.security	= शून्य,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECCOMP_FILTER
	.seccomp	= अणु .filter_count = ATOMIC_INIT(0) पूर्ण,
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL(init_task);

/*
 * Initial thपढ़ो काष्ठाure. Alignment of this is handled by a special
 * linker map entry.
 */
#अगर_अघोषित CONFIG_THREAD_INFO_IN_TASK
काष्ठा thपढ़ो_info init_thपढ़ो_info __init_thपढ़ो_info = INIT_THREAD_INFO(init_task);
#पूर्ण_अगर
