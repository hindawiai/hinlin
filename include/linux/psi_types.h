<शैली गुरु>
#अगर_अघोषित _LINUX_PSI_TYPES_H
#घोषणा _LINUX_PSI_TYPES_H

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/types.h>
#समावेश <linux/kref.h>
#समावेश <linux/रुको.h>

#अगर_घोषित CONFIG_PSI

/* Tracked task states */
क्रमागत psi_task_count अणु
	NR_IOWAIT,
	NR_MEMSTALL,
	NR_RUNNING,
	/*
	 * This can't have values other than 0 or 1 and could be
	 * implemented as a bit flag. But क्रम now we still have room
	 * in the first cacheline of psi_group_cpu, and this way we
	 * करोn't have to special हाल any state tracking क्रम it.
	 */
	NR_ONCPU,
	NR_PSI_TASK_COUNTS = 4,
पूर्ण;

/* Task state biपंचांगasks */
#घोषणा TSK_IOWAIT	(1 << NR_IOWAIT)
#घोषणा TSK_MEMSTALL	(1 << NR_MEMSTALL)
#घोषणा TSK_RUNNING	(1 << NR_RUNNING)
#घोषणा TSK_ONCPU	(1 << NR_ONCPU)

/* Resources that workloads could be stalled on */
क्रमागत psi_res अणु
	PSI_IO,
	PSI_MEM,
	PSI_CPU,
	NR_PSI_RESOURCES = 3,
पूर्ण;

/*
 * Pressure states क्रम each resource:
 *
 * SOME: Stalled tasks & working tasks
 * FULL: Stalled tasks & no working tasks
 */
क्रमागत psi_states अणु
	PSI_IO_SOME,
	PSI_IO_FULL,
	PSI_MEM_SOME,
	PSI_MEM_FULL,
	PSI_CPU_SOME,
	PSI_CPU_FULL,
	/* Only per-CPU, to weigh the CPU in the global average: */
	PSI_NONIDLE,
	NR_PSI_STATES = 7,
पूर्ण;

क्रमागत psi_aggregators अणु
	PSI_AVGS = 0,
	PSI_POLL,
	NR_PSI_AGGREGATORS,
पूर्ण;

काष्ठा psi_group_cpu अणु
	/* 1st cacheline updated by the scheduler */

	/* Aggregator needs to know of concurrent changes */
	seqcount_t seq ____cacheline_aligned_in_smp;

	/* States of the tasks beदीर्घing to this group */
	अचिन्हित पूर्णांक tasks[NR_PSI_TASK_COUNTS];

	/* Aggregate pressure state derived from the tasks */
	u32 state_mask;

	/* Period समय sampling buckets क्रम each state of पूर्णांकerest (ns) */
	u32 बार[NR_PSI_STATES];

	/* Time of last task change in this group (rq_घड़ी) */
	u64 state_start;

	/* 2nd cacheline updated by the aggregator */

	/* Delta detection against the sampling buckets */
	u32 बार_prev[NR_PSI_AGGREGATORS][NR_PSI_STATES]
			____cacheline_aligned_in_smp;
पूर्ण;

/* PSI growth tracking winकरोw */
काष्ठा psi_winकरोw अणु
	/* Winकरोw size in ns */
	u64 size;

	/* Start समय of the current winकरोw in ns */
	u64 start_समय;

	/* Value at the start of the winकरोw */
	u64 start_value;

	/* Value growth in the previous winकरोw */
	u64 prev_growth;
पूर्ण;

काष्ठा psi_trigger अणु
	/* PSI state being monitored by the trigger */
	क्रमागत psi_states state;

	/* User-spacअगरied threshold in ns */
	u64 threshold;

	/* List node inside triggers list */
	काष्ठा list_head node;

	/* Backpoपूर्णांकer needed during trigger deकाष्ठाion */
	काष्ठा psi_group *group;

	/* Wait queue क्रम polling */
	रुको_queue_head_t event_रुको;

	/* Pending event flag */
	पूर्णांक event;

	/* Tracking winकरोw */
	काष्ठा psi_winकरोw win;

	/*
	 * Time last event was generated. Used क्रम rate-limiting
	 * events to one per winकरोw
	 */
	u64 last_event_समय;

	/* Refcounting to prevent premature deकाष्ठाion */
	काष्ठा kref refcount;
पूर्ण;

काष्ठा psi_group अणु
	/* Protects data used by the aggregator */
	काष्ठा mutex avgs_lock;

	/* Per-cpu task state & समय tracking */
	काष्ठा psi_group_cpu __percpu *pcpu;

	/* Running pressure averages */
	u64 avg_total[NR_PSI_STATES - 1];
	u64 avg_last_update;
	u64 avg_next_update;

	/* Aggregator work control */
	काष्ठा delayed_work avgs_work;

	/* Total stall बार and sampled pressure averages */
	u64 total[NR_PSI_AGGREGATORS][NR_PSI_STATES - 1];
	अचिन्हित दीर्घ avg[NR_PSI_STATES - 1][3];

	/* Monitor work control */
	काष्ठा task_काष्ठा __rcu *poll_task;
	काष्ठा समयr_list poll_समयr;
	रुको_queue_head_t poll_रुको;
	atomic_t poll_wakeup;

	/* Protects data used by the monitor */
	काष्ठा mutex trigger_lock;

	/* Configured polling triggers */
	काष्ठा list_head triggers;
	u32 nr_triggers[NR_PSI_STATES - 1];
	u32 poll_states;
	u64 poll_min_period;

	/* Total stall बार at the start of monitor activation */
	u64 polling_total[NR_PSI_STATES - 1];
	u64 polling_next_update;
	u64 polling_until;
पूर्ण;

#अन्यथा /* CONFIG_PSI */

काष्ठा psi_group अणु पूर्ण;

#पूर्ण_अगर /* CONFIG_PSI */

#पूर्ण_अगर /* _LINUX_PSI_TYPES_H */
