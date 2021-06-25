<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Scheduler पूर्णांकernal types and methods:
 */
#समावेश <linux/sched.h>

#समावेश <linux/sched/स्वतःgroup.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/sched/cpufreq.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/sched/deadline.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/sched/idle.h>
#समावेश <linux/sched/init.h>
#समावेश <linux/sched/isolation.h>
#समावेश <linux/sched/jobctl.h>
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/nohz.h>
#समावेश <linux/sched/numa_balancing.h>
#समावेश <linux/sched/prपन.स>
#समावेश <linux/sched/rt.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/smt.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/sched/sysctl.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/sched/topology.h>
#समावेश <linux/sched/user.h>
#समावेश <linux/sched/wake_q.h>
#समावेश <linux/sched/xacct.h>

#समावेश <uapi/linux/sched/types.h>

#समावेश <linux/binfmts.h>
#समावेश <linux/bitops.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/compat.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/delayacct.h>
#समावेश <linux/energy_model.h>
#समावेश <linux/init_task.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/membarrier.h>
#समावेश <linux/migrate.h>
#समावेश <linux/mmu_context.h>
#समावेश <linux/nmi.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/profile.h>
#समावेश <linux/psi.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/rcupdate_रुको.h>
#समावेश <linux/security.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/suspend.h>
#समावेश <linux/sरुको.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/task_work.h>
#समावेश <linux/tsacct_kern.h>

#समावेश <यंत्र/tlb.h>

#अगर_घोषित CONFIG_PARAVIRT
# include <यंत्र/paravirt.h>
#पूर्ण_अगर

#समावेश "cpupri.h"
#समावेश "cpudeadline.h"

#समावेश <trace/events/sched.h>

#अगर_घोषित CONFIG_SCHED_DEBUG
# define SCHED_WARN_ON(x)	WARN_ONCE(x, #x)
#अन्यथा
# define SCHED_WARN_ON(x)	(अणु (व्योम)(x), 0; पूर्ण)
#पूर्ण_अगर

काष्ठा rq;
काष्ठा cpuidle_state;

/* task_काष्ठा::on_rq states: */
#घोषणा TASK_ON_RQ_QUEUED	1
#घोषणा TASK_ON_RQ_MIGRATING	2

बाह्य __पढ़ो_mostly पूर्णांक scheduler_running;

बाह्य अचिन्हित दीर्घ calc_load_update;
बाह्य atomic_दीर्घ_t calc_load_tasks;

बाह्य व्योम calc_global_load_tick(काष्ठा rq *this_rq);
बाह्य दीर्घ calc_load_fold_active(काष्ठा rq *this_rq, दीर्घ adjust);

बाह्य व्योम call_trace_sched_update_nr_running(काष्ठा rq *rq, पूर्णांक count);
/*
 * Helpers क्रम converting nanosecond timing to jअगरfy resolution
 */
#घोषणा NS_TO_JIFFIES(TIME)	((अचिन्हित दीर्घ)(TIME) / (NSEC_PER_SEC / HZ))

/*
 * Increase resolution of nice-level calculations क्रम 64-bit architectures.
 * The extra resolution improves shares distribution and load balancing of
 * low-weight task groups (eg. nice +19 on an स्वतःgroup), deeper taskgroup
 * hierarchies, especially on larger प्रणालीs. This is not a user-visible change
 * and करोes not change the user-पूर्णांकerface क्रम setting shares/weights.
 *
 * We increase resolution only अगर we have enough bits to allow this increased
 * resolution (i.e. 64-bit). The costs क्रम increasing resolution when 32-bit
 * are pretty high and the वापसs करो not justअगरy the increased costs.
 *
 * Really only required when CONFIG_FAIR_GROUP_SCHED=y is also set, but to
 * increase coverage and consistency always enable it on 64-bit platक्रमms.
 */
#अगर_घोषित CONFIG_64BIT
# define NICE_0_LOAD_SHIFT	(SCHED_FIXEDPOINT_SHIFT + SCHED_FIXEDPOINT_SHIFT)
# define scale_load(w)		((w) << SCHED_FIXEDPOINT_SHIFT)
# define scale_load_करोwn(w) \
(अणु \
	अचिन्हित दीर्घ __w = (w); \
	अगर (__w) \
		__w = max(2UL, __w >> SCHED_FIXEDPOINT_SHIFT); \
	__w; \
पूर्ण)
#अन्यथा
# define NICE_0_LOAD_SHIFT	(SCHED_FIXEDPOINT_SHIFT)
# define scale_load(w)		(w)
# define scale_load_करोwn(w)	(w)
#पूर्ण_अगर

/*
 * Task weight (visible to users) and its load (invisible to users) have
 * independent resolution, but they should be well calibrated. We use
 * scale_load() and scale_load_करोwn(w) to convert between them. The
 * following must be true:
 *
 *  scale_load(sched_prio_to_weight[NICE_TO_PRIO(0)-MAX_RT_PRIO]) == NICE_0_LOAD
 *
 */
#घोषणा NICE_0_LOAD		(1L << NICE_0_LOAD_SHIFT)

/*
 * Single value that decides SCHED_DEADLINE पूर्णांकernal math precision.
 * 10 -> just above 1us
 * 9  -> just above 0.5us
 */
#घोषणा DL_SCALE		10

/*
 * Single value that denotes runसमय == period, ie unlimited समय.
 */
#घोषणा RUNTIME_INF		((u64)~0ULL)

अटल अंतरभूत पूर्णांक idle_policy(पूर्णांक policy)
अणु
	वापस policy == SCHED_IDLE;
पूर्ण
अटल अंतरभूत पूर्णांक fair_policy(पूर्णांक policy)
अणु
	वापस policy == SCHED_NORMAL || policy == SCHED_BATCH;
पूर्ण

अटल अंतरभूत पूर्णांक rt_policy(पूर्णांक policy)
अणु
	वापस policy == SCHED_FIFO || policy == SCHED_RR;
पूर्ण

अटल अंतरभूत पूर्णांक dl_policy(पूर्णांक policy)
अणु
	वापस policy == SCHED_DEADLINE;
पूर्ण
अटल अंतरभूत bool valid_policy(पूर्णांक policy)
अणु
	वापस idle_policy(policy) || fair_policy(policy) ||
		rt_policy(policy) || dl_policy(policy);
पूर्ण

अटल अंतरभूत पूर्णांक task_has_idle_policy(काष्ठा task_काष्ठा *p)
अणु
	वापस idle_policy(p->policy);
पूर्ण

अटल अंतरभूत पूर्णांक task_has_rt_policy(काष्ठा task_काष्ठा *p)
अणु
	वापस rt_policy(p->policy);
पूर्ण

अटल अंतरभूत पूर्णांक task_has_dl_policy(काष्ठा task_काष्ठा *p)
अणु
	वापस dl_policy(p->policy);
पूर्ण

#घोषणा cap_scale(v, s) ((v)*(s) >> SCHED_CAPACITY_SHIFT)

अटल अंतरभूत व्योम update_avg(u64 *avg, u64 sample)
अणु
	s64 dअगरf = sample - *avg;
	*avg += dअगरf / 8;
पूर्ण

/*
 * Shअगरting a value by an exponent greater *or equal* to the size of said value
 * is UB; cap at size-1.
 */
#घोषणा shr_bound(val, shअगरt)							\
	(val >> min_t(typeof(shअगरt), shअगरt, BITS_PER_TYPE(typeof(val)) - 1))

/*
 * !! For sched_setattr_nocheck() (kernel) only !!
 *
 * This is actually gross. :(
 *
 * It is used to make schedutil kworker(s) higher priority than SCHED_DEADLINE
 * tasks, but still be able to sleep. We need this on platक्रमms that cannot
 * atomically change घड़ी frequency. Remove once fast चयनing will be
 * available on such platक्रमms.
 *
 * SUGOV stands क्रम SchedUtil GOVernor.
 */
#घोषणा SCHED_FLAG_SUGOV	0x10000000

अटल अंतरभूत bool dl_entity_is_special(काष्ठा sched_dl_entity *dl_se)
अणु
#अगर_घोषित CONFIG_CPU_FREQ_GOV_SCHEDUTIL
	वापस unlikely(dl_se->flags & SCHED_FLAG_SUGOV);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

/*
 * Tells अगर entity @a should preempt entity @b.
 */
अटल अंतरभूत bool
dl_entity_preempt(काष्ठा sched_dl_entity *a, काष्ठा sched_dl_entity *b)
अणु
	वापस dl_entity_is_special(a) ||
	       dl_समय_beक्रमe(a->deadline, b->deadline);
पूर्ण

/*
 * This is the priority-queue data काष्ठाure of the RT scheduling class:
 */
काष्ठा rt_prio_array अणु
	DECLARE_BITMAP(biपंचांगap, MAX_RT_PRIO+1); /* include 1 bit क्रम delimiter */
	काष्ठा list_head queue[MAX_RT_PRIO];
पूर्ण;

काष्ठा rt_bandwidth अणु
	/* nests inside the rq lock: */
	raw_spinlock_t		rt_runसमय_lock;
	kसमय_प्रकार			rt_period;
	u64			rt_runसमय;
	काष्ठा hrसमयr		rt_period_समयr;
	अचिन्हित पूर्णांक		rt_period_active;
पूर्ण;

व्योम __dl_clear_params(काष्ठा task_काष्ठा *p);

काष्ठा dl_bandwidth अणु
	raw_spinlock_t		dl_runसमय_lock;
	u64			dl_runसमय;
	u64			dl_period;
पूर्ण;

अटल अंतरभूत पूर्णांक dl_bandwidth_enabled(व्योम)
अणु
	वापस sysctl_sched_rt_runसमय >= 0;
पूर्ण

/*
 * To keep the bandwidth of -deadline tasks under control
 * we need some place where:
 *  - store the maximum -deadline bandwidth of each cpu;
 *  - cache the fraction of bandwidth that is currently allocated in
 *    each root करोमुख्य;
 *
 * This is all करोne in the data काष्ठाure below. It is similar to the
 * one used क्रम RT-throttling (rt_bandwidth), with the मुख्य dअगरference
 * that, since here we are only पूर्णांकerested in admission control, we
 * करो not decrease any runसमय जबतक the group "executes", neither we
 * need a समयr to replenish it.
 *
 * With respect to SMP, bandwidth is given on a per root करोमुख्य basis,
 * meaning that:
 *  - bw (< 100%) is the deadline bandwidth of each CPU;
 *  - total_bw is the currently allocated bandwidth in each root करोमुख्य;
 */
काष्ठा dl_bw अणु
	raw_spinlock_t		lock;
	u64			bw;
	u64			total_bw;
पूर्ण;

अटल अंतरभूत व्योम __dl_update(काष्ठा dl_bw *dl_b, s64 bw);

अटल अंतरभूत
व्योम __dl_sub(काष्ठा dl_bw *dl_b, u64 tsk_bw, पूर्णांक cpus)
अणु
	dl_b->total_bw -= tsk_bw;
	__dl_update(dl_b, (s32)tsk_bw / cpus);
पूर्ण

अटल अंतरभूत
व्योम __dl_add(काष्ठा dl_bw *dl_b, u64 tsk_bw, पूर्णांक cpus)
अणु
	dl_b->total_bw += tsk_bw;
	__dl_update(dl_b, -((s32)tsk_bw / cpus));
पूर्ण

अटल अंतरभूत bool __dl_overflow(काष्ठा dl_bw *dl_b, अचिन्हित दीर्घ cap,
				 u64 old_bw, u64 new_bw)
अणु
	वापस dl_b->bw != -1 &&
	       cap_scale(dl_b->bw, cap) < dl_b->total_bw - old_bw + new_bw;
पूर्ण

/*
 * Verअगरy the fitness of task @p to run on @cpu taking पूर्णांकo account the
 * CPU original capacity and the runसमय/deadline ratio of the task.
 *
 * The function will वापस true अगर the CPU original capacity of the
 * @cpu scaled by SCHED_CAPACITY_SCALE >= runसमय/deadline ratio of the
 * task and false otherwise.
 */
अटल अंतरभूत bool dl_task_fits_capacity(काष्ठा task_काष्ठा *p, पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ cap = arch_scale_cpu_capacity(cpu);

	वापस cap_scale(p->dl.dl_deadline, cap) >= p->dl.dl_runसमय;
पूर्ण

बाह्य व्योम init_dl_bw(काष्ठा dl_bw *dl_b);
बाह्य पूर्णांक  sched_dl_global_validate(व्योम);
बाह्य व्योम sched_dl_करो_global(व्योम);
बाह्य पूर्णांक  sched_dl_overflow(काष्ठा task_काष्ठा *p, पूर्णांक policy, स्थिर काष्ठा sched_attr *attr);
बाह्य व्योम __setparam_dl(काष्ठा task_काष्ठा *p, स्थिर काष्ठा sched_attr *attr);
बाह्य व्योम __getparam_dl(काष्ठा task_काष्ठा *p, काष्ठा sched_attr *attr);
बाह्य bool __checkparam_dl(स्थिर काष्ठा sched_attr *attr);
बाह्य bool dl_param_changed(काष्ठा task_काष्ठा *p, स्थिर काष्ठा sched_attr *attr);
बाह्य पूर्णांक  dl_task_can_attach(काष्ठा task_काष्ठा *p, स्थिर काष्ठा cpumask *cs_cpus_allowed);
बाह्य पूर्णांक  dl_cpuset_cpumask_can_shrink(स्थिर काष्ठा cpumask *cur, स्थिर काष्ठा cpumask *trial);
बाह्य bool dl_cpu_busy(अचिन्हित पूर्णांक cpu);

#अगर_घोषित CONFIG_CGROUP_SCHED

#समावेश <linux/cgroup.h>
#समावेश <linux/psi.h>

काष्ठा cfs_rq;
काष्ठा rt_rq;

बाह्य काष्ठा list_head task_groups;

काष्ठा cfs_bandwidth अणु
#अगर_घोषित CONFIG_CFS_BANDWIDTH
	raw_spinlock_t		lock;
	kसमय_प्रकार			period;
	u64			quota;
	u64			runसमय;
	s64			hierarchical_quota;

	u8			idle;
	u8			period_active;
	u8			slack_started;
	काष्ठा hrसमयr		period_समयr;
	काष्ठा hrसमयr		slack_समयr;
	काष्ठा list_head	throttled_cfs_rq;

	/* Statistics: */
	पूर्णांक			nr_periods;
	पूर्णांक			nr_throttled;
	u64			throttled_समय;
#पूर्ण_अगर
पूर्ण;

/* Task group related inक्रमmation */
काष्ठा task_group अणु
	काष्ठा cgroup_subsys_state css;

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	/* schedulable entities of this group on each CPU */
	काष्ठा sched_entity	**se;
	/* runqueue "owned" by this group on each CPU */
	काष्ठा cfs_rq		**cfs_rq;
	अचिन्हित दीर्घ		shares;

#अगर_घोषित	CONFIG_SMP
	/*
	 * load_avg can be heavily contended at घड़ी tick समय, so put
	 * it in its own cacheline separated from the fields above which
	 * will also be accessed at each tick.
	 */
	atomic_दीर्घ_t		load_avg ____cacheline_aligned;
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_RT_GROUP_SCHED
	काष्ठा sched_rt_entity	**rt_se;
	काष्ठा rt_rq		**rt_rq;

	काष्ठा rt_bandwidth	rt_bandwidth;
#पूर्ण_अगर

	काष्ठा rcu_head		rcu;
	काष्ठा list_head	list;

	काष्ठा task_group	*parent;
	काष्ठा list_head	siblings;
	काष्ठा list_head	children;

#अगर_घोषित CONFIG_SCHED_AUTOGROUP
	काष्ठा स्वतःgroup	*स्वतःgroup;
#पूर्ण_अगर

	काष्ठा cfs_bandwidth	cfs_bandwidth;

#अगर_घोषित CONFIG_UCLAMP_TASK_GROUP
	/* The two decimal precision [%] value requested from user-space */
	अचिन्हित पूर्णांक		uclamp_pct[UCLAMP_CNT];
	/* Clamp values requested क्रम a task group */
	काष्ठा uclamp_se	uclamp_req[UCLAMP_CNT];
	/* Effective clamp values used क्रम a task group */
	काष्ठा uclamp_se	uclamp[UCLAMP_CNT];
#पूर्ण_अगर

पूर्ण;

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
#घोषणा ROOT_TASK_GROUP_LOAD	NICE_0_LOAD

/*
 * A weight of 0 or 1 can cause arithmetics problems.
 * A weight of a cfs_rq is the sum of weights of which entities
 * are queued on this cfs_rq, so a weight of a entity should not be
 * too large, so as the shares value of a task group.
 * (The शेष weight is 1024 - so there's no practical
 *  limitation from this.)
 */
#घोषणा MIN_SHARES		(1UL <<  1)
#घोषणा MAX_SHARES		(1UL << 18)
#पूर्ण_अगर

प्रकार पूर्णांक (*tg_visitor)(काष्ठा task_group *, व्योम *);

बाह्य पूर्णांक walk_tg_tree_from(काष्ठा task_group *from,
			     tg_visitor करोwn, tg_visitor up, व्योम *data);

/*
 * Iterate the full tree, calling @करोwn when first entering a node and @up when
 * leaving it क्रम the final समय.
 *
 * Caller must hold rcu_lock or sufficient equivalent.
 */
अटल अंतरभूत पूर्णांक walk_tg_tree(tg_visitor करोwn, tg_visitor up, व्योम *data)
अणु
	वापस walk_tg_tree_from(&root_task_group, करोwn, up, data);
पूर्ण

बाह्य पूर्णांक tg_nop(काष्ठा task_group *tg, व्योम *data);

बाह्य व्योम मुक्त_fair_sched_group(काष्ठा task_group *tg);
बाह्य पूर्णांक alloc_fair_sched_group(काष्ठा task_group *tg, काष्ठा task_group *parent);
बाह्य व्योम online_fair_sched_group(काष्ठा task_group *tg);
बाह्य व्योम unरेजिस्टर_fair_sched_group(काष्ठा task_group *tg);
बाह्य व्योम init_tg_cfs_entry(काष्ठा task_group *tg, काष्ठा cfs_rq *cfs_rq,
			काष्ठा sched_entity *se, पूर्णांक cpu,
			काष्ठा sched_entity *parent);
बाह्य व्योम init_cfs_bandwidth(काष्ठा cfs_bandwidth *cfs_b);

बाह्य व्योम __refill_cfs_bandwidth_runसमय(काष्ठा cfs_bandwidth *cfs_b);
बाह्य व्योम start_cfs_bandwidth(काष्ठा cfs_bandwidth *cfs_b);
बाह्य व्योम unthrottle_cfs_rq(काष्ठा cfs_rq *cfs_rq);

बाह्य व्योम मुक्त_rt_sched_group(काष्ठा task_group *tg);
बाह्य पूर्णांक alloc_rt_sched_group(काष्ठा task_group *tg, काष्ठा task_group *parent);
बाह्य व्योम init_tg_rt_entry(काष्ठा task_group *tg, काष्ठा rt_rq *rt_rq,
		काष्ठा sched_rt_entity *rt_se, पूर्णांक cpu,
		काष्ठा sched_rt_entity *parent);
बाह्य पूर्णांक sched_group_set_rt_runसमय(काष्ठा task_group *tg, दीर्घ rt_runसमय_us);
बाह्य पूर्णांक sched_group_set_rt_period(काष्ठा task_group *tg, u64 rt_period_us);
बाह्य दीर्घ sched_group_rt_runसमय(काष्ठा task_group *tg);
बाह्य दीर्घ sched_group_rt_period(काष्ठा task_group *tg);
बाह्य पूर्णांक sched_rt_can_attach(काष्ठा task_group *tg, काष्ठा task_काष्ठा *tsk);

बाह्य काष्ठा task_group *sched_create_group(काष्ठा task_group *parent);
बाह्य व्योम sched_online_group(काष्ठा task_group *tg,
			       काष्ठा task_group *parent);
बाह्य व्योम sched_destroy_group(काष्ठा task_group *tg);
बाह्य व्योम sched_offline_group(काष्ठा task_group *tg);

बाह्य व्योम sched_move_task(काष्ठा task_काष्ठा *tsk);

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
बाह्य पूर्णांक sched_group_set_shares(काष्ठा task_group *tg, अचिन्हित दीर्घ shares);

#अगर_घोषित CONFIG_SMP
बाह्य व्योम set_task_rq_fair(काष्ठा sched_entity *se,
			     काष्ठा cfs_rq *prev, काष्ठा cfs_rq *next);
#अन्यथा /* !CONFIG_SMP */
अटल अंतरभूत व्योम set_task_rq_fair(काष्ठा sched_entity *se,
			     काष्ठा cfs_rq *prev, काष्ठा cfs_rq *next) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */
#पूर्ण_अगर /* CONFIG_FAIR_GROUP_SCHED */

#अन्यथा /* CONFIG_CGROUP_SCHED */

काष्ठा cfs_bandwidth अणु पूर्ण;

#पूर्ण_अगर	/* CONFIG_CGROUP_SCHED */

/* CFS-related fields in a runqueue */
काष्ठा cfs_rq अणु
	काष्ठा load_weight	load;
	अचिन्हित पूर्णांक		nr_running;
	अचिन्हित पूर्णांक		h_nr_running;      /* SCHED_अणुNORMAL,BATCH,IDLEपूर्ण */
	अचिन्हित पूर्णांक		idle_h_nr_running; /* SCHED_IDLE */

	u64			exec_घड़ी;
	u64			min_vrunसमय;
#अगर_अघोषित CONFIG_64BIT
	u64			min_vrunसमय_copy;
#पूर्ण_अगर

	काष्ठा rb_root_cached	tasks_समयline;

	/*
	 * 'curr' poपूर्णांकs to currently running entity on this cfs_rq.
	 * It is set to शून्य otherwise (i.e when none are currently running).
	 */
	काष्ठा sched_entity	*curr;
	काष्ठा sched_entity	*next;
	काष्ठा sched_entity	*last;
	काष्ठा sched_entity	*skip;

#अगर_घोषित	CONFIG_SCHED_DEBUG
	अचिन्हित पूर्णांक		nr_spपढ़ो_over;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
	/*
	 * CFS load tracking
	 */
	काष्ठा sched_avg	avg;
#अगर_अघोषित CONFIG_64BIT
	u64			load_last_update_समय_copy;
#पूर्ण_अगर
	काष्ठा अणु
		raw_spinlock_t	lock ____cacheline_aligned;
		पूर्णांक		nr;
		अचिन्हित दीर्घ	load_avg;
		अचिन्हित दीर्घ	util_avg;
		अचिन्हित दीर्घ	runnable_avg;
	पूर्ण हटाओd;

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	अचिन्हित दीर्घ		tg_load_avg_contrib;
	दीर्घ			propagate;
	दीर्घ			prop_runnable_sum;

	/*
	 *   h_load = weight * f(tg)
	 *
	 * Where f(tg) is the recursive weight fraction asचिन्हित to
	 * this group.
	 */
	अचिन्हित दीर्घ		h_load;
	u64			last_h_load_update;
	काष्ठा sched_entity	*h_load_next;
#पूर्ण_अगर /* CONFIG_FAIR_GROUP_SCHED */
#पूर्ण_अगर /* CONFIG_SMP */

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	काष्ठा rq		*rq;	/* CPU runqueue to which this cfs_rq is attached */

	/*
	 * leaf cfs_rqs are those that hold tasks (lowest schedulable entity in
	 * a hierarchy). Non-leaf lrqs hold other higher schedulable entities
	 * (like users, containers etc.)
	 *
	 * leaf_cfs_rq_list ties together list of leaf cfs_rq's in a CPU.
	 * This list is used during load balance.
	 */
	पूर्णांक			on_list;
	काष्ठा list_head	leaf_cfs_rq_list;
	काष्ठा task_group	*tg;	/* group that "owns" this runqueue */

#अगर_घोषित CONFIG_CFS_BANDWIDTH
	पूर्णांक			runसमय_enabled;
	s64			runसमय_reमुख्यing;

	u64			throttled_घड़ी;
	u64			throttled_घड़ी_प्रकारask;
	u64			throttled_घड़ी_प्रकारask_समय;
	पूर्णांक			throttled;
	पूर्णांक			throttle_count;
	काष्ठा list_head	throttled_list;
#पूर्ण_अगर /* CONFIG_CFS_BANDWIDTH */
#पूर्ण_अगर /* CONFIG_FAIR_GROUP_SCHED */
पूर्ण;

अटल अंतरभूत पूर्णांक rt_bandwidth_enabled(व्योम)
अणु
	वापस sysctl_sched_rt_runसमय >= 0;
पूर्ण

/* RT IPI pull logic requires IRQ_WORK */
#अगर defined(CONFIG_IRQ_WORK) && defined(CONFIG_SMP)
# define HAVE_RT_PUSH_IPI
#पूर्ण_अगर

/* Real-Time classes' related field in a runqueue: */
काष्ठा rt_rq अणु
	काष्ठा rt_prio_array	active;
	अचिन्हित पूर्णांक		rt_nr_running;
	अचिन्हित पूर्णांक		rr_nr_running;
#अगर defined CONFIG_SMP || defined CONFIG_RT_GROUP_SCHED
	काष्ठा अणु
		पूर्णांक		curr; /* highest queued rt task prio */
#अगर_घोषित CONFIG_SMP
		पूर्णांक		next; /* next highest */
#पूर्ण_अगर
	पूर्ण highest_prio;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
	अचिन्हित दीर्घ		rt_nr_migratory;
	अचिन्हित दीर्घ		rt_nr_total;
	पूर्णांक			overloaded;
	काष्ठा plist_head	pushable_tasks;

#पूर्ण_अगर /* CONFIG_SMP */
	पूर्णांक			rt_queued;

	पूर्णांक			rt_throttled;
	u64			rt_समय;
	u64			rt_runसमय;
	/* Nests inside the rq lock: */
	raw_spinlock_t		rt_runसमय_lock;

#अगर_घोषित CONFIG_RT_GROUP_SCHED
	अचिन्हित दीर्घ		rt_nr_boosted;

	काष्ठा rq		*rq;
	काष्ठा task_group	*tg;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत bool rt_rq_is_runnable(काष्ठा rt_rq *rt_rq)
अणु
	वापस rt_rq->rt_queued && rt_rq->rt_nr_running;
पूर्ण

/* Deadline class' related fields in a runqueue */
काष्ठा dl_rq अणु
	/* runqueue is an rbtree, ordered by deadline */
	काष्ठा rb_root_cached	root;

	अचिन्हित दीर्घ		dl_nr_running;

#अगर_घोषित CONFIG_SMP
	/*
	 * Deadline values of the currently executing and the
	 * earliest पढ़ोy task on this rq. Caching these facilitates
	 * the decision whether or not a पढ़ोy but not running task
	 * should migrate somewhere अन्यथा.
	 */
	काष्ठा अणु
		u64		curr;
		u64		next;
	पूर्ण earliest_dl;

	अचिन्हित दीर्घ		dl_nr_migratory;
	पूर्णांक			overloaded;

	/*
	 * Tasks on this rq that can be pushed away. They are kept in
	 * an rb-tree, ordered by tasks' deadlines, with caching
	 * of the lefपंचांगost (earliest deadline) element.
	 */
	काष्ठा rb_root_cached	pushable_dl_tasks_root;
#अन्यथा
	काष्ठा dl_bw		dl_bw;
#पूर्ण_अगर
	/*
	 * "Active utilization" क्रम this runqueue: increased when a
	 * task wakes up (becomes TASK_RUNNING) and decreased when a
	 * task blocks
	 */
	u64			running_bw;

	/*
	 * Utilization of the tasks "assigned" to this runqueue (including
	 * the tasks that are in runqueue and the tasks that executed on this
	 * CPU and blocked). Increased when a task moves to this runqueue, and
	 * decreased when the task moves away (migrates, changes scheduling
	 * policy, or terminates).
	 * This is needed to compute the "inactive utilization" क्रम the
	 * runqueue (inactive utilization = this_bw - running_bw).
	 */
	u64			this_bw;
	u64			extra_bw;

	/*
	 * Inverse of the fraction of CPU utilization that can be reclaimed
	 * by the GRUB algorithm.
	 */
	u64			bw_ratio;
पूर्ण;

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
/* An entity is a task अगर it करोesn't "own" a runqueue */
#घोषणा entity_is_task(se)	(!se->my_q)

अटल अंतरभूत व्योम se_update_runnable(काष्ठा sched_entity *se)
अणु
	अगर (!entity_is_task(se))
		se->runnable_weight = se->my_q->h_nr_running;
पूर्ण

अटल अंतरभूत दीर्घ se_runnable(काष्ठा sched_entity *se)
अणु
	अगर (entity_is_task(se))
		वापस !!se->on_rq;
	अन्यथा
		वापस se->runnable_weight;
पूर्ण

#अन्यथा
#घोषणा entity_is_task(se)	1

अटल अंतरभूत व्योम se_update_runnable(काष्ठा sched_entity *se) अणुपूर्ण

अटल अंतरभूत दीर्घ se_runnable(काष्ठा sched_entity *se)
अणु
	वापस !!se->on_rq;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
/*
 * XXX we want to get rid of these helpers and use the full load resolution.
 */
अटल अंतरभूत दीर्घ se_weight(काष्ठा sched_entity *se)
अणु
	वापस scale_load_करोwn(se->load.weight);
पूर्ण


अटल अंतरभूत bool sched_asym_prefer(पूर्णांक a, पूर्णांक b)
अणु
	वापस arch_asym_cpu_priority(a) > arch_asym_cpu_priority(b);
पूर्ण

काष्ठा perf_करोमुख्य अणु
	काष्ठा em_perf_करोमुख्य *em_pd;
	काष्ठा perf_करोमुख्य *next;
	काष्ठा rcu_head rcu;
पूर्ण;

/* Scheduling group status flags */
#घोषणा SG_OVERLOAD		0x1 /* More than one runnable task on a CPU. */
#घोषणा SG_OVERUTILIZED		0x2 /* One or more CPUs are over-utilized. */

/*
 * We add the notion of a root-करोमुख्य which will be used to define per-करोमुख्य
 * variables. Each exclusive cpuset essentially defines an island करोमुख्य by
 * fully partitioning the member CPUs from any other cpuset. Whenever a new
 * exclusive cpuset is created, we also create and attach a new root-करोमुख्य
 * object.
 *
 */
काष्ठा root_करोमुख्य अणु
	atomic_t		refcount;
	atomic_t		rto_count;
	काष्ठा rcu_head		rcu;
	cpumask_var_t		span;
	cpumask_var_t		online;

	/*
	 * Indicate pullable load on at least one CPU, e.g:
	 * - More than one runnable task
	 * - Running task is misfit
	 */
	पूर्णांक			overload;

	/* Indicate one or more cpus over-utilized (tipping poपूर्णांक) */
	पूर्णांक			overutilized;

	/*
	 * The bit corresponding to a CPU माला_लो set here अगर such CPU has more
	 * than one runnable -deadline task (as it is below क्रम RT tasks).
	 */
	cpumask_var_t		dlo_mask;
	atomic_t		dlo_count;
	काष्ठा dl_bw		dl_bw;
	काष्ठा cpudl		cpudl;

	/*
	 * Indicate whether a root_करोमुख्य's dl_bw has been checked or
	 * updated. It's monotonously increasing value.
	 *
	 * Also, some corner हालs, like 'wrap around' is dangerous, but given
	 * that u64 is 'big enough'. So that shouldn't be a concern.
	 */
	u64 visit_gen;

#अगर_घोषित HAVE_RT_PUSH_IPI
	/*
	 * For IPI pull requests, loop across the rto_mask.
	 */
	काष्ठा irq_work		rto_push_work;
	raw_spinlock_t		rto_lock;
	/* These are only updated and पढ़ो within rto_lock */
	पूर्णांक			rto_loop;
	पूर्णांक			rto_cpu;
	/* These atomics are updated outside of a lock */
	atomic_t		rto_loop_next;
	atomic_t		rto_loop_start;
#पूर्ण_अगर
	/*
	 * The "RT overload" flag: it माला_लो set अगर a CPU has more than
	 * one runnable RT task.
	 */
	cpumask_var_t		rto_mask;
	काष्ठा cpupri		cpupri;

	अचिन्हित दीर्घ		max_cpu_capacity;

	/*
	 * शून्य-terminated list of perक्रमmance करोमुख्यs पूर्णांकersecting with the
	 * CPUs of the rd. Protected by RCU.
	 */
	काष्ठा perf_करोमुख्य __rcu *pd;
पूर्ण;

बाह्य व्योम init_defrootकरोमुख्य(व्योम);
बाह्य पूर्णांक sched_init_करोमुख्यs(स्थिर काष्ठा cpumask *cpu_map);
बाह्य व्योम rq_attach_root(काष्ठा rq *rq, काष्ठा root_करोमुख्य *rd);
बाह्य व्योम sched_get_rd(काष्ठा root_करोमुख्य *rd);
बाह्य व्योम sched_put_rd(काष्ठा root_करोमुख्य *rd);

#अगर_घोषित HAVE_RT_PUSH_IPI
बाह्य व्योम rto_push_irq_work_func(काष्ठा irq_work *work);
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_SMP */

#अगर_घोषित CONFIG_UCLAMP_TASK
/*
 * काष्ठा uclamp_bucket - Utilization clamp bucket
 * @value: utilization clamp value क्रम tasks on this clamp bucket
 * @tasks: number of RUNNABLE tasks on this clamp bucket
 *
 * Keep track of how many tasks are RUNNABLE क्रम a given utilization
 * clamp value.
 */
काष्ठा uclamp_bucket अणु
	अचिन्हित दीर्घ value : bits_per(SCHED_CAPACITY_SCALE);
	अचिन्हित दीर्घ tasks : BITS_PER_LONG - bits_per(SCHED_CAPACITY_SCALE);
पूर्ण;

/*
 * काष्ठा uclamp_rq - rq's utilization clamp
 * @value: currently active clamp values क्रम a rq
 * @bucket: utilization clamp buckets affecting a rq
 *
 * Keep track of RUNNABLE tasks on a rq to aggregate their clamp values.
 * A clamp value is affecting a rq when there is at least one task RUNNABLE
 * (or actually running) with that value.
 *
 * There are up to UCLAMP_CNT possible dअगरferent clamp values, currently there
 * are only two: minimum utilization and maximum utilization.
 *
 * All utilization clamping values are MAX aggregated, since:
 * - क्रम util_min: we want to run the CPU at least at the max of the minimum
 *   utilization required by its currently RUNNABLE tasks.
 * - क्रम util_max: we want to allow the CPU to run up to the max of the
 *   maximum utilization allowed by its currently RUNNABLE tasks.
 *
 * Since on each प्रणाली we expect only a limited number of dअगरferent
 * utilization clamp values (UCLAMP_BUCKETS), use a simple array to track
 * the metrics required to compute all the per-rq utilization clamp values.
 */
काष्ठा uclamp_rq अणु
	अचिन्हित पूर्णांक value;
	काष्ठा uclamp_bucket bucket[UCLAMP_BUCKETS];
पूर्ण;

DECLARE_STATIC_KEY_FALSE(sched_uclamp_used);
#पूर्ण_अगर /* CONFIG_UCLAMP_TASK */

/*
 * This is the मुख्य, per-CPU runqueue data काष्ठाure.
 *
 * Locking rule: those places that want to lock multiple runqueues
 * (such as the load balancing or the thपढ़ो migration code), lock
 * acquire operations must be ordered by ascending &runqueue.
 */
काष्ठा rq अणु
	/* runqueue lock: */
	raw_spinlock_t		lock;

	/*
	 * nr_running and cpu_load should be in the same cacheline because
	 * remote CPUs use both these fields when करोing load calculation.
	 */
	अचिन्हित पूर्णांक		nr_running;
#अगर_घोषित CONFIG_NUMA_BALANCING
	अचिन्हित पूर्णांक		nr_numa_running;
	अचिन्हित पूर्णांक		nr_preferred_running;
	अचिन्हित पूर्णांक		numa_migrate_on;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NO_HZ_COMMON
#अगर_घोषित CONFIG_SMP
	अचिन्हित दीर्घ		last_blocked_load_update_tick;
	अचिन्हित पूर्णांक		has_blocked_load;
	call_single_data_t	nohz_csd;
#पूर्ण_अगर /* CONFIG_SMP */
	अचिन्हित पूर्णांक		nohz_tick_stopped;
	atomic_t		nohz_flags;
#पूर्ण_अगर /* CONFIG_NO_HZ_COMMON */

#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक		ttwu_pending;
#पूर्ण_अगर
	u64			nr_चयनes;

#अगर_घोषित CONFIG_UCLAMP_TASK
	/* Utilization clamp values based on CPU's RUNNABLE tasks */
	काष्ठा uclamp_rq	uclamp[UCLAMP_CNT] ____cacheline_aligned;
	अचिन्हित पूर्णांक		uclamp_flags;
#घोषणा UCLAMP_FLAG_IDLE 0x01
#पूर्ण_अगर

	काष्ठा cfs_rq		cfs;
	काष्ठा rt_rq		rt;
	काष्ठा dl_rq		dl;

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	/* list of leaf cfs_rq on this CPU: */
	काष्ठा list_head	leaf_cfs_rq_list;
	काष्ठा list_head	*पंचांगp_alone_branch;
#पूर्ण_अगर /* CONFIG_FAIR_GROUP_SCHED */

	/*
	 * This is part of a global counter where only the total sum
	 * over all CPUs matters. A task can increase this counter on
	 * one CPU and अगर it got migrated afterwards it may decrease
	 * it on another CPU. Always updated under the runqueue lock:
	 */
	अचिन्हित दीर्घ		nr_unपूर्णांकerruptible;

	काष्ठा task_काष्ठा __rcu	*curr;
	काष्ठा task_काष्ठा	*idle;
	काष्ठा task_काष्ठा	*stop;
	अचिन्हित दीर्घ		next_balance;
	काष्ठा mm_काष्ठा	*prev_mm;

	अचिन्हित पूर्णांक		घड़ी_update_flags;
	u64			घड़ी;
	/* Ensure that all घड़ीs are in the same cache line */
	u64			घड़ी_प्रकारask ____cacheline_aligned;
	u64			घड़ी_pelt;
	अचिन्हित दीर्घ		lost_idle_समय;

	atomic_t		nr_ioरुको;

#अगर_घोषित CONFIG_SCHED_DEBUG
	u64 last_seen_need_resched_ns;
	पूर्णांक ticks_without_resched;
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEMBARRIER
	पूर्णांक membarrier_state;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
	काष्ठा root_करोमुख्य		*rd;
	काष्ठा sched_करोमुख्य __rcu	*sd;

	अचिन्हित दीर्घ		cpu_capacity;
	अचिन्हित दीर्घ		cpu_capacity_orig;

	काष्ठा callback_head	*balance_callback;

	अचिन्हित अक्षर		nohz_idle_balance;
	अचिन्हित अक्षर		idle_balance;

	अचिन्हित दीर्घ		misfit_task_load;

	/* For active balancing */
	पूर्णांक			active_balance;
	पूर्णांक			push_cpu;
	काष्ठा cpu_stop_work	active_balance_work;

	/* CPU of this runqueue: */
	पूर्णांक			cpu;
	पूर्णांक			online;

	काष्ठा list_head cfs_tasks;

	काष्ठा sched_avg	avg_rt;
	काष्ठा sched_avg	avg_dl;
#अगर_घोषित CONFIG_HAVE_SCHED_AVG_IRQ
	काष्ठा sched_avg	avg_irq;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SCHED_THERMAL_PRESSURE
	काष्ठा sched_avg	avg_thermal;
#पूर्ण_अगर
	u64			idle_stamp;
	u64			avg_idle;

	/* This is used to determine avg_idle's max value */
	u64			max_idle_balance_cost;

#अगर_घोषित CONFIG_HOTPLUG_CPU
	काष्ठा rcuरुको		hotplug_रुको;
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_SMP */

#अगर_घोषित CONFIG_IRQ_TIME_ACCOUNTING
	u64			prev_irq_समय;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PARAVIRT
	u64			prev_steal_समय;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PARAVIRT_TIME_ACCOUNTING
	u64			prev_steal_समय_rq;
#पूर्ण_अगर

	/* calc_load related fields */
	अचिन्हित दीर्घ		calc_load_update;
	दीर्घ			calc_load_active;

#अगर_घोषित CONFIG_SCHED_HRTICK
#अगर_घोषित CONFIG_SMP
	call_single_data_t	hrtick_csd;
#पूर्ण_अगर
	काष्ठा hrसमयr		hrtick_समयr;
	kसमय_प्रकार 		hrtick_समय;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SCHEDSTATS
	/* latency stats */
	काष्ठा sched_info	rq_sched_info;
	अचिन्हित दीर्घ दीर्घ	rq_cpu_समय;
	/* could above be rq->cfs_rq.exec_घड़ी + rq->rt_rq.rt_runसमय ? */

	/* sys_sched_yield() stats */
	अचिन्हित पूर्णांक		yld_count;

	/* schedule() stats */
	अचिन्हित पूर्णांक		sched_count;
	अचिन्हित पूर्णांक		sched_goidle;

	/* try_to_wake_up() stats */
	अचिन्हित पूर्णांक		ttwu_count;
	अचिन्हित पूर्णांक		ttwu_local;
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_IDLE
	/* Must be inspected within a rcu lock section */
	काष्ठा cpuidle_state	*idle_state;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक		nr_pinned;
#पूर्ण_अगर
	अचिन्हित पूर्णांक		push_busy;
	काष्ठा cpu_stop_work	push_work;
पूर्ण;

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED

/* CPU runqueue to which this cfs_rq is attached */
अटल अंतरभूत काष्ठा rq *rq_of(काष्ठा cfs_rq *cfs_rq)
अणु
	वापस cfs_rq->rq;
पूर्ण

#अन्यथा

अटल अंतरभूत काष्ठा rq *rq_of(काष्ठा cfs_rq *cfs_rq)
अणु
	वापस container_of(cfs_rq, काष्ठा rq, cfs);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक cpu_of(काष्ठा rq *rq)
अणु
#अगर_घोषित CONFIG_SMP
	वापस rq->cpu;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

#घोषणा MDF_PUSH	0x01

अटल अंतरभूत bool is_migration_disabled(काष्ठा task_काष्ठा *p)
अणु
#अगर_घोषित CONFIG_SMP
	वापस p->migration_disabled;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_SCHED_SMT
बाह्य व्योम __update_idle_core(काष्ठा rq *rq);

अटल अंतरभूत व्योम update_idle_core(काष्ठा rq *rq)
अणु
	अगर (अटल_branch_unlikely(&sched_smt_present))
		__update_idle_core(rq);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम update_idle_core(काष्ठा rq *rq) अणु पूर्ण
#पूर्ण_अगर

DECLARE_PER_CPU_SHARED_ALIGNED(काष्ठा rq, runqueues);

#घोषणा cpu_rq(cpu)		(&per_cpu(runqueues, (cpu)))
#घोषणा this_rq()		this_cpu_ptr(&runqueues)
#घोषणा task_rq(p)		cpu_rq(task_cpu(p))
#घोषणा cpu_curr(cpu)		(cpu_rq(cpu)->curr)
#घोषणा raw_rq()		raw_cpu_ptr(&runqueues)

बाह्य व्योम update_rq_घड़ी(काष्ठा rq *rq);

अटल अंतरभूत u64 __rq_घड़ी_broken(काष्ठा rq *rq)
अणु
	वापस READ_ONCE(rq->घड़ी);
पूर्ण

/*
 * rq::घड़ी_update_flags bits
 *
 * %RQCF_REQ_SKIP - will request skipping of घड़ी update on the next
 *  call to __schedule(). This is an optimisation to aव्योम
 *  neighbouring rq घड़ी updates.
 *
 * %RQCF_ACT_SKIP - is set from inside of __schedule() when skipping is
 *  in effect and calls to update_rq_घड़ी() are being ignored.
 *
 * %RQCF_UPDATED - is a debug flag that indicates whether a call has been
 *  made to update_rq_घड़ी() since the last समय rq::lock was pinned.
 *
 * If inside of __schedule(), घड़ी_update_flags will have been
 * shअगरted left (a left shअगरt is a cheap operation क्रम the fast path
 * to promote %RQCF_REQ_SKIP to %RQCF_ACT_SKIP), so you must use,
 *
 *	अगर (rq-घड़ी_update_flags >= RQCF_UPDATED)
 *
 * to check अगर %RQCF_UPDATED is set. It'll never be shअगरted more than
 * one position though, because the next rq_unpin_lock() will shअगरt it
 * back.
 */
#घोषणा RQCF_REQ_SKIP		0x01
#घोषणा RQCF_ACT_SKIP		0x02
#घोषणा RQCF_UPDATED		0x04

अटल अंतरभूत व्योम निश्चित_घड़ी_updated(काष्ठा rq *rq)
अणु
	/*
	 * The only reason क्रम not seeing a घड़ी update since the
	 * last rq_pin_lock() is अगर we're currently skipping updates.
	 */
	SCHED_WARN_ON(rq->घड़ी_update_flags < RQCF_ACT_SKIP);
पूर्ण

अटल अंतरभूत u64 rq_घड़ी(काष्ठा rq *rq)
अणु
	lockdep_निश्चित_held(&rq->lock);
	निश्चित_घड़ी_updated(rq);

	वापस rq->घड़ी;
पूर्ण

अटल अंतरभूत u64 rq_घड़ी_प्रकारask(काष्ठा rq *rq)
अणु
	lockdep_निश्चित_held(&rq->lock);
	निश्चित_घड़ी_updated(rq);

	वापस rq->घड़ी_प्रकारask;
पूर्ण

/**
 * By शेष the decay is the शेष pelt decay period.
 * The decay shअगरt can change the decay period in
 * multiples of 32.
 *  Decay shअगरt		Decay period(ms)
 *	0			32
 *	1			64
 *	2			128
 *	3			256
 *	4			512
 */
बाह्य पूर्णांक sched_thermal_decay_shअगरt;

अटल अंतरभूत u64 rq_घड़ी_प्रकारhermal(काष्ठा rq *rq)
अणु
	वापस rq_घड़ी_प्रकारask(rq) >> sched_thermal_decay_shअगरt;
पूर्ण

अटल अंतरभूत व्योम rq_घड़ी_skip_update(काष्ठा rq *rq)
अणु
	lockdep_निश्चित_held(&rq->lock);
	rq->घड़ी_update_flags |= RQCF_REQ_SKIP;
पूर्ण

/*
 * See rt task throttling, which is the only समय a skip
 * request is canceled.
 */
अटल अंतरभूत व्योम rq_घड़ी_cancel_skipupdate(काष्ठा rq *rq)
अणु
	lockdep_निश्चित_held(&rq->lock);
	rq->घड़ी_update_flags &= ~RQCF_REQ_SKIP;
पूर्ण

काष्ठा rq_flags अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pin_cookie cookie;
#अगर_घोषित CONFIG_SCHED_DEBUG
	/*
	 * A copy of (rq::घड़ी_update_flags & RQCF_UPDATED) क्रम the
	 * current pin context is stashed here in हाल it needs to be
	 * restored in rq_repin_lock().
	 */
	अचिन्हित पूर्णांक घड़ी_update_flags;
#पूर्ण_अगर
पूर्ण;

बाह्य काष्ठा callback_head balance_push_callback;

/*
 * Lockdep annotation that aव्योमs accidental unlocks; it's like a
 * sticky/continuous lockdep_निश्चित_held().
 *
 * This aव्योमs code that has access to 'struct rq *rq' (basically everything in
 * the scheduler) from accidentally unlocking the rq अगर they करो not also have a
 * copy of the (on-stack) 'struct rq_flags rf'.
 *
 * Also see Documentation/locking/lockdep-design.rst.
 */
अटल अंतरभूत व्योम rq_pin_lock(काष्ठा rq *rq, काष्ठा rq_flags *rf)
अणु
	rf->cookie = lockdep_pin_lock(&rq->lock);

#अगर_घोषित CONFIG_SCHED_DEBUG
	rq->घड़ी_update_flags &= (RQCF_REQ_SKIP|RQCF_ACT_SKIP);
	rf->घड़ी_update_flags = 0;
#अगर_घोषित CONFIG_SMP
	SCHED_WARN_ON(rq->balance_callback && rq->balance_callback != &balance_push_callback);
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम rq_unpin_lock(काष्ठा rq *rq, काष्ठा rq_flags *rf)
अणु
#अगर_घोषित CONFIG_SCHED_DEBUG
	अगर (rq->घड़ी_update_flags > RQCF_ACT_SKIP)
		rf->घड़ी_update_flags = RQCF_UPDATED;
#पूर्ण_अगर

	lockdep_unpin_lock(&rq->lock, rf->cookie);
पूर्ण

अटल अंतरभूत व्योम rq_repin_lock(काष्ठा rq *rq, काष्ठा rq_flags *rf)
अणु
	lockdep_repin_lock(&rq->lock, rf->cookie);

#अगर_घोषित CONFIG_SCHED_DEBUG
	/*
	 * Restore the value we stashed in @rf क्रम this pin context.
	 */
	rq->घड़ी_update_flags |= rf->घड़ी_update_flags;
#पूर्ण_अगर
पूर्ण

काष्ठा rq *__task_rq_lock(काष्ठा task_काष्ठा *p, काष्ठा rq_flags *rf)
	__acquires(rq->lock);

काष्ठा rq *task_rq_lock(काष्ठा task_काष्ठा *p, काष्ठा rq_flags *rf)
	__acquires(p->pi_lock)
	__acquires(rq->lock);

अटल अंतरभूत व्योम __task_rq_unlock(काष्ठा rq *rq, काष्ठा rq_flags *rf)
	__releases(rq->lock)
अणु
	rq_unpin_lock(rq, rf);
	raw_spin_unlock(&rq->lock);
पूर्ण

अटल अंतरभूत व्योम
task_rq_unlock(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, काष्ठा rq_flags *rf)
	__releases(rq->lock)
	__releases(p->pi_lock)
अणु
	rq_unpin_lock(rq, rf);
	raw_spin_unlock(&rq->lock);
	raw_spin_unlock_irqrestore(&p->pi_lock, rf->flags);
पूर्ण

अटल अंतरभूत व्योम
rq_lock_irqsave(काष्ठा rq *rq, काष्ठा rq_flags *rf)
	__acquires(rq->lock)
अणु
	raw_spin_lock_irqsave(&rq->lock, rf->flags);
	rq_pin_lock(rq, rf);
पूर्ण

अटल अंतरभूत व्योम
rq_lock_irq(काष्ठा rq *rq, काष्ठा rq_flags *rf)
	__acquires(rq->lock)
अणु
	raw_spin_lock_irq(&rq->lock);
	rq_pin_lock(rq, rf);
पूर्ण

अटल अंतरभूत व्योम
rq_lock(काष्ठा rq *rq, काष्ठा rq_flags *rf)
	__acquires(rq->lock)
अणु
	raw_spin_lock(&rq->lock);
	rq_pin_lock(rq, rf);
पूर्ण

अटल अंतरभूत व्योम
rq_relock(काष्ठा rq *rq, काष्ठा rq_flags *rf)
	__acquires(rq->lock)
अणु
	raw_spin_lock(&rq->lock);
	rq_repin_lock(rq, rf);
पूर्ण

अटल अंतरभूत व्योम
rq_unlock_irqrestore(काष्ठा rq *rq, काष्ठा rq_flags *rf)
	__releases(rq->lock)
अणु
	rq_unpin_lock(rq, rf);
	raw_spin_unlock_irqrestore(&rq->lock, rf->flags);
पूर्ण

अटल अंतरभूत व्योम
rq_unlock_irq(काष्ठा rq *rq, काष्ठा rq_flags *rf)
	__releases(rq->lock)
अणु
	rq_unpin_lock(rq, rf);
	raw_spin_unlock_irq(&rq->lock);
पूर्ण

अटल अंतरभूत व्योम
rq_unlock(काष्ठा rq *rq, काष्ठा rq_flags *rf)
	__releases(rq->lock)
अणु
	rq_unpin_lock(rq, rf);
	raw_spin_unlock(&rq->lock);
पूर्ण

अटल अंतरभूत काष्ठा rq *
this_rq_lock_irq(काष्ठा rq_flags *rf)
	__acquires(rq->lock)
अणु
	काष्ठा rq *rq;

	local_irq_disable();
	rq = this_rq();
	rq_lock(rq, rf);
	वापस rq;
पूर्ण

#अगर_घोषित CONFIG_NUMA
क्रमागत numa_topology_type अणु
	NUMA_सूचीECT,
	NUMA_GLUELESS_MESH,
	NUMA_BACKPLANE,
पूर्ण;
बाह्य क्रमागत numa_topology_type sched_numa_topology_type;
बाह्य पूर्णांक sched_max_numa_distance;
बाह्य bool find_numa_distance(पूर्णांक distance);
बाह्य व्योम sched_init_numa(व्योम);
बाह्य व्योम sched_करोमुख्यs_numa_masks_set(अचिन्हित पूर्णांक cpu);
बाह्य व्योम sched_करोमुख्यs_numa_masks_clear(अचिन्हित पूर्णांक cpu);
बाह्य पूर्णांक sched_numa_find_बंदst(स्थिर काष्ठा cpumask *cpus, पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत व्योम sched_init_numa(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम sched_करोमुख्यs_numa_masks_set(अचिन्हित पूर्णांक cpu) अणु पूर्ण
अटल अंतरभूत व्योम sched_करोमुख्यs_numa_masks_clear(अचिन्हित पूर्णांक cpu) अणु पूर्ण
अटल अंतरभूत पूर्णांक sched_numa_find_बंदst(स्थिर काष्ठा cpumask *cpus, पूर्णांक cpu)
अणु
	वापस nr_cpu_ids;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NUMA_BALANCING
/* The regions in numa_faults array from task_काष्ठा */
क्रमागत numa_faults_stats अणु
	NUMA_MEM = 0,
	NUMA_CPU,
	NUMA_MEMBUF,
	NUMA_CPUBUF
पूर्ण;
बाह्य व्योम sched_setnuma(काष्ठा task_काष्ठा *p, पूर्णांक node);
बाह्य पूर्णांक migrate_task_to(काष्ठा task_काष्ठा *p, पूर्णांक cpu);
बाह्य पूर्णांक migrate_swap(काष्ठा task_काष्ठा *p, काष्ठा task_काष्ठा *t,
			पूर्णांक cpu, पूर्णांक scpu);
बाह्य व्योम init_numa_balancing(अचिन्हित दीर्घ clone_flags, काष्ठा task_काष्ठा *p);
#अन्यथा
अटल अंतरभूत व्योम
init_numa_balancing(अचिन्हित दीर्घ clone_flags, काष्ठा task_काष्ठा *p)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

#अगर_घोषित CONFIG_SMP

अटल अंतरभूत व्योम
queue_balance_callback(काष्ठा rq *rq,
		       काष्ठा callback_head *head,
		       व्योम (*func)(काष्ठा rq *rq))
अणु
	lockdep_निश्चित_held(&rq->lock);

	अगर (unlikely(head->next || rq->balance_callback == &balance_push_callback))
		वापस;

	head->func = (व्योम (*)(काष्ठा callback_head *))func;
	head->next = rq->balance_callback;
	rq->balance_callback = head;
पूर्ण

#घोषणा rcu_dereference_check_sched_करोमुख्य(p) \
	rcu_dereference_check((p), \
			      lockdep_is_held(&sched_करोमुख्यs_mutex))

/*
 * The करोमुख्य tree (rq->sd) is रक्षित by RCU's quiescent state transition.
 * See destroy_sched_करोमुख्यs: call_rcu क्रम details.
 *
 * The करोमुख्य tree of any CPU may only be accessed from within
 * preempt-disabled sections.
 */
#घोषणा क्रम_each_करोमुख्य(cpu, __sd) \
	क्रम (__sd = rcu_dereference_check_sched_करोमुख्य(cpu_rq(cpu)->sd); \
			__sd; __sd = __sd->parent)

/**
 * highest_flag_करोमुख्य - Return highest sched_करोमुख्य containing flag.
 * @cpu:	The CPU whose highest level of sched करोमुख्य is to
 *		be वापसed.
 * @flag:	The flag to check क्रम the highest sched_करोमुख्य
 *		क्रम the given CPU.
 *
 * Returns the highest sched_करोमुख्य of a CPU which contains the given flag.
 */
अटल अंतरभूत काष्ठा sched_करोमुख्य *highest_flag_करोमुख्य(पूर्णांक cpu, पूर्णांक flag)
अणु
	काष्ठा sched_करोमुख्य *sd, *hsd = शून्य;

	क्रम_each_करोमुख्य(cpu, sd) अणु
		अगर (!(sd->flags & flag))
			अवरोध;
		hsd = sd;
	पूर्ण

	वापस hsd;
पूर्ण

अटल अंतरभूत काष्ठा sched_करोमुख्य *lowest_flag_करोमुख्य(पूर्णांक cpu, पूर्णांक flag)
अणु
	काष्ठा sched_करोमुख्य *sd;

	क्रम_each_करोमुख्य(cpu, sd) अणु
		अगर (sd->flags & flag)
			अवरोध;
	पूर्ण

	वापस sd;
पूर्ण

DECLARE_PER_CPU(काष्ठा sched_करोमुख्य __rcu *, sd_llc);
DECLARE_PER_CPU(पूर्णांक, sd_llc_size);
DECLARE_PER_CPU(पूर्णांक, sd_llc_id);
DECLARE_PER_CPU(काष्ठा sched_करोमुख्य_shared __rcu *, sd_llc_shared);
DECLARE_PER_CPU(काष्ठा sched_करोमुख्य __rcu *, sd_numa);
DECLARE_PER_CPU(काष्ठा sched_करोमुख्य __rcu *, sd_asym_packing);
DECLARE_PER_CPU(काष्ठा sched_करोमुख्य __rcu *, sd_asym_cpucapacity);
बाह्य काष्ठा अटल_key_false sched_asym_cpucapacity;

काष्ठा sched_group_capacity अणु
	atomic_t		ref;
	/*
	 * CPU capacity of this group, SCHED_CAPACITY_SCALE being max capacity
	 * क्रम a single CPU.
	 */
	अचिन्हित दीर्घ		capacity;
	अचिन्हित दीर्घ		min_capacity;		/* Min per-CPU capacity in group */
	अचिन्हित दीर्घ		max_capacity;		/* Max per-CPU capacity in group */
	अचिन्हित दीर्घ		next_update;
	पूर्णांक			imbalance;		/* XXX unrelated to capacity but shared group state */

#अगर_घोषित CONFIG_SCHED_DEBUG
	पूर्णांक			id;
#पूर्ण_अगर

	अचिन्हित दीर्घ		cpumask[];		/* Balance mask */
पूर्ण;

काष्ठा sched_group अणु
	काष्ठा sched_group	*next;			/* Must be a circular list */
	atomic_t		ref;

	अचिन्हित पूर्णांक		group_weight;
	काष्ठा sched_group_capacity *sgc;
	पूर्णांक			asym_prefer_cpu;	/* CPU of highest priority in group */

	/*
	 * The CPUs this group covers.
	 *
	 * NOTE: this field is variable length. (Allocated dynamically
	 * by attaching extra space to the end of the काष्ठाure,
	 * depending on how many CPUs the kernel has booted up with)
	 */
	अचिन्हित दीर्घ		cpumask[];
पूर्ण;

अटल अंतरभूत काष्ठा cpumask *sched_group_span(काष्ठा sched_group *sg)
अणु
	वापस to_cpumask(sg->cpumask);
पूर्ण

/*
 * See build_balance_mask().
 */
अटल अंतरभूत काष्ठा cpumask *group_balance_mask(काष्ठा sched_group *sg)
अणु
	वापस to_cpumask(sg->sgc->cpumask);
पूर्ण

/**
 * group_first_cpu - Returns the first CPU in the cpumask of a sched_group.
 * @group: The group whose first CPU is to be वापसed.
 */
अटल अंतरभूत अचिन्हित पूर्णांक group_first_cpu(काष्ठा sched_group *group)
अणु
	वापस cpumask_first(sched_group_span(group));
पूर्ण

बाह्य पूर्णांक group_balance_cpu(काष्ठा sched_group *sg);

#अगर_घोषित CONFIG_SCHED_DEBUG
व्योम update_sched_करोमुख्य_debugfs(व्योम);
व्योम dirty_sched_करोमुख्य_sysctl(पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत व्योम update_sched_करोमुख्य_debugfs(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम dirty_sched_करोमुख्य_sysctl(पूर्णांक cpu)
अणु
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक sched_update_scaling(व्योम);

बाह्य व्योम flush_smp_call_function_from_idle(व्योम);

#अन्यथा /* !CONFIG_SMP: */
अटल अंतरभूत व्योम flush_smp_call_function_from_idle(व्योम) अणु पूर्ण
#पूर्ण_अगर

#समावेश "stats.h"
#समावेश "autogroup.h"

#अगर_घोषित CONFIG_CGROUP_SCHED

/*
 * Return the group to which this tasks beदीर्घs.
 *
 * We cannot use task_css() and मित्रs because the cgroup subप्रणाली
 * changes that value beक्रमe the cgroup_subsys::attach() method is called,
 * thereक्रमe we cannot pin it and might observe the wrong value.
 *
 * The same is true क्रम स्वतःgroup's p->संकेत->स्वतःgroup->tg, the स्वतःgroup
 * core changes this beक्रमe calling sched_move_task().
 *
 * Instead we use a 'copy' which is updated from sched_move_task() जबतक
 * holding both task_काष्ठा::pi_lock and rq::lock.
 */
अटल अंतरभूत काष्ठा task_group *task_group(काष्ठा task_काष्ठा *p)
अणु
	वापस p->sched_task_group;
पूर्ण

/* Change a task's cfs_rq and parent entity अगर it moves across CPUs/groups */
अटल अंतरभूत व्योम set_task_rq(काष्ठा task_काष्ठा *p, अचिन्हित पूर्णांक cpu)
अणु
#अगर defined(CONFIG_FAIR_GROUP_SCHED) || defined(CONFIG_RT_GROUP_SCHED)
	काष्ठा task_group *tg = task_group(p);
#पूर्ण_अगर

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	set_task_rq_fair(&p->se, p->se.cfs_rq, tg->cfs_rq[cpu]);
	p->se.cfs_rq = tg->cfs_rq[cpu];
	p->se.parent = tg->se[cpu];
#पूर्ण_अगर

#अगर_घोषित CONFIG_RT_GROUP_SCHED
	p->rt.rt_rq  = tg->rt_rq[cpu];
	p->rt.parent = tg->rt_se[cpu];
#पूर्ण_अगर
पूर्ण

#अन्यथा /* CONFIG_CGROUP_SCHED */

अटल अंतरभूत व्योम set_task_rq(काष्ठा task_काष्ठा *p, अचिन्हित पूर्णांक cpu) अणु पूर्ण
अटल अंतरभूत काष्ठा task_group *task_group(काष्ठा task_काष्ठा *p)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_CGROUP_SCHED */

अटल अंतरभूत व्योम __set_task_cpu(काष्ठा task_काष्ठा *p, अचिन्हित पूर्णांक cpu)
अणु
	set_task_rq(p, cpu);
#अगर_घोषित CONFIG_SMP
	/*
	 * After ->cpu is set up to a new value, task_rq_lock(p, ...) can be
	 * successfully executed on another CPU. We must ensure that updates of
	 * per-task data have been completed by this moment.
	 */
	smp_wmb();
#अगर_घोषित CONFIG_THREAD_INFO_IN_TASK
	WRITE_ONCE(p->cpu, cpu);
#अन्यथा
	WRITE_ONCE(task_thपढ़ो_info(p)->cpu, cpu);
#पूर्ण_अगर
	p->wake_cpu = cpu;
#पूर्ण_अगर
पूर्ण

/*
 * Tunables that become स्थिरants when CONFIG_SCHED_DEBUG is off:
 */
#अगर_घोषित CONFIG_SCHED_DEBUG
# include <linux/अटल_key.h>
# define स्थिर_debug __पढ़ो_mostly
#अन्यथा
# define स्थिर_debug स्थिर
#पूर्ण_अगर

#घोषणा SCHED_FEAT(name, enabled)	\
	__SCHED_FEAT_##name ,

क्रमागत अणु
#समावेश "features.h"
	__SCHED_FEAT_NR,
पूर्ण;

#अघोषित SCHED_FEAT

#अगर_घोषित CONFIG_SCHED_DEBUG

/*
 * To support run-समय toggling of sched features, all the translation units
 * (but core.c) reference the sysctl_sched_features defined in core.c.
 */
बाह्य स्थिर_debug अचिन्हित पूर्णांक sysctl_sched_features;

#अगर_घोषित CONFIG_JUMP_LABEL
#घोषणा SCHED_FEAT(name, enabled)					\
अटल __always_अंतरभूत bool अटल_branch_##name(काष्ठा अटल_key *key) \
अणु									\
	वापस अटल_key_##enabled(key);				\
पूर्ण

#समावेश "features.h"
#अघोषित SCHED_FEAT

बाह्य काष्ठा अटल_key sched_feat_keys[__SCHED_FEAT_NR];
#घोषणा sched_feat(x) (अटल_branch_##x(&sched_feat_keys[__SCHED_FEAT_##x]))

#अन्यथा /* !CONFIG_JUMP_LABEL */

#घोषणा sched_feat(x) (sysctl_sched_features & (1UL << __SCHED_FEAT_##x))

#पूर्ण_अगर /* CONFIG_JUMP_LABEL */

#अन्यथा /* !SCHED_DEBUG */

/*
 * Each translation unit has its own copy of sysctl_sched_features to allow
 * स्थिरants propagation at compile समय and compiler optimization based on
 * features शेष.
 */
#घोषणा SCHED_FEAT(name, enabled)	\
	(1UL << __SCHED_FEAT_##name) * enabled |
अटल स्थिर_debug __maybe_unused अचिन्हित पूर्णांक sysctl_sched_features =
#समावेश "features.h"
	0;
#अघोषित SCHED_FEAT

#घोषणा sched_feat(x) !!(sysctl_sched_features & (1UL << __SCHED_FEAT_##x))

#पूर्ण_अगर /* SCHED_DEBUG */

बाह्य काष्ठा अटल_key_false sched_numa_balancing;
बाह्य काष्ठा अटल_key_false sched_schedstats;

अटल अंतरभूत u64 global_rt_period(व्योम)
अणु
	वापस (u64)sysctl_sched_rt_period * NSEC_PER_USEC;
पूर्ण

अटल अंतरभूत u64 global_rt_runसमय(व्योम)
अणु
	अगर (sysctl_sched_rt_runसमय < 0)
		वापस RUNTIME_INF;

	वापस (u64)sysctl_sched_rt_runसमय * NSEC_PER_USEC;
पूर्ण

अटल अंतरभूत पूर्णांक task_current(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	वापस rq->curr == p;
पूर्ण

अटल अंतरभूत पूर्णांक task_running(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
#अगर_घोषित CONFIG_SMP
	वापस p->on_cpu;
#अन्यथा
	वापस task_current(rq, p);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक task_on_rq_queued(काष्ठा task_काष्ठा *p)
अणु
	वापस p->on_rq == TASK_ON_RQ_QUEUED;
पूर्ण

अटल अंतरभूत पूर्णांक task_on_rq_migrating(काष्ठा task_काष्ठा *p)
अणु
	वापस READ_ONCE(p->on_rq) == TASK_ON_RQ_MIGRATING;
पूर्ण

/* Wake flags. The first three directly map to some SD flag value */
#घोषणा WF_EXEC     0x02 /* Wakeup after exec; maps to SD_BALANCE_EXEC */
#घोषणा WF_FORK     0x04 /* Wakeup after विभाजन; maps to SD_BALANCE_FORK */
#घोषणा WF_TTWU     0x08 /* Wakeup;            maps to SD_BALANCE_WAKE */

#घोषणा WF_SYNC     0x10 /* Waker goes to sleep after wakeup */
#घोषणा WF_MIGRATED 0x20 /* Internal use, task got migrated */
#घोषणा WF_ON_CPU   0x40 /* Wakee is on_cpu */

#अगर_घोषित CONFIG_SMP
अटल_निश्चित(WF_EXEC == SD_BALANCE_EXEC);
अटल_निश्चित(WF_FORK == SD_BALANCE_FORK);
अटल_निश्चित(WF_TTWU == SD_BALANCE_WAKE);
#पूर्ण_अगर

/*
 * To aid in aव्योमing the subversion of "niceness" due to uneven distribution
 * of tasks with abnormal "nice" values across CPUs the contribution that
 * each task makes to its run queue's load is weighted according to its
 * scheduling class and "nice" value. For SCHED_NORMAL tasks this is just a
 * scaled version of the new समय slice allocation that they receive on समय
 * slice expiry etc.
 */

#घोषणा WEIGHT_IDLEPRIO		3
#घोषणा WMULT_IDLEPRIO		1431655765

बाह्य स्थिर पूर्णांक		sched_prio_to_weight[40];
बाह्य स्थिर u32		sched_prio_to_wmult[40];

/*
 * अणुde,enपूर्णqueue flags:
 *
 * DEQUEUE_SLEEP  - task is no दीर्घer runnable
 * ENQUEUE_WAKEUP - task just became runnable
 *
 * SAVE/RESTORE - an otherwise spurious dequeue/enqueue, करोne to ensure tasks
 *                are in a known state which allows modअगरication. Such pairs
 *                should preserve as much state as possible.
 *
 * MOVE - paired with SAVE/RESTORE, explicitly करोes not preserve the location
 *        in the runqueue.
 *
 * ENQUEUE_HEAD      - place at front of runqueue (tail अगर not specअगरied)
 * ENQUEUE_REPLENISH - CBS (replenish runसमय and postpone deadline)
 * ENQUEUE_MIGRATED  - the task was migrated during wakeup
 *
 */

#घोषणा DEQUEUE_SLEEP		0x01
#घोषणा DEQUEUE_SAVE		0x02 /* Matches ENQUEUE_RESTORE */
#घोषणा DEQUEUE_MOVE		0x04 /* Matches ENQUEUE_MOVE */
#घोषणा DEQUEUE_NOCLOCK		0x08 /* Matches ENQUEUE_NOCLOCK */

#घोषणा ENQUEUE_WAKEUP		0x01
#घोषणा ENQUEUE_RESTORE		0x02
#घोषणा ENQUEUE_MOVE		0x04
#घोषणा ENQUEUE_NOCLOCK		0x08

#घोषणा ENQUEUE_HEAD		0x10
#घोषणा ENQUEUE_REPLENISH	0x20
#अगर_घोषित CONFIG_SMP
#घोषणा ENQUEUE_MIGRATED	0x40
#अन्यथा
#घोषणा ENQUEUE_MIGRATED	0x00
#पूर्ण_अगर

#घोषणा RETRY_TASK		((व्योम *)-1UL)

काष्ठा sched_class अणु

#अगर_घोषित CONFIG_UCLAMP_TASK
	पूर्णांक uclamp_enabled;
#पूर्ण_अगर

	व्योम (*enqueue_task) (काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags);
	व्योम (*dequeue_task) (काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags);
	व्योम (*yield_task)   (काष्ठा rq *rq);
	bool (*yield_to_task)(काष्ठा rq *rq, काष्ठा task_काष्ठा *p);

	व्योम (*check_preempt_curr)(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags);

	काष्ठा task_काष्ठा *(*pick_next_task)(काष्ठा rq *rq);

	व्योम (*put_prev_task)(काष्ठा rq *rq, काष्ठा task_काष्ठा *p);
	व्योम (*set_next_task)(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, bool first);

#अगर_घोषित CONFIG_SMP
	पूर्णांक (*balance)(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev, काष्ठा rq_flags *rf);
	पूर्णांक  (*select_task_rq)(काष्ठा task_काष्ठा *p, पूर्णांक task_cpu, पूर्णांक flags);
	व्योम (*migrate_task_rq)(काष्ठा task_काष्ठा *p, पूर्णांक new_cpu);

	व्योम (*task_woken)(काष्ठा rq *this_rq, काष्ठा task_काष्ठा *task);

	व्योम (*set_cpus_allowed)(काष्ठा task_काष्ठा *p,
				 स्थिर काष्ठा cpumask *newmask,
				 u32 flags);

	व्योम (*rq_online)(काष्ठा rq *rq);
	व्योम (*rq_offline)(काष्ठा rq *rq);

	काष्ठा rq *(*find_lock_rq)(काष्ठा task_काष्ठा *p, काष्ठा rq *rq);
#पूर्ण_अगर

	व्योम (*task_tick)(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक queued);
	व्योम (*task_विभाजन)(काष्ठा task_काष्ठा *p);
	व्योम (*task_dead)(काष्ठा task_काष्ठा *p);

	/*
	 * The चयनed_from() call is allowed to drop rq->lock, thereक्रमe we
	 * cannot assume the चयनed_from/चयनed_to pair is serialized by
	 * rq->lock. They are however serialized by p->pi_lock.
	 */
	व्योम (*चयनed_from)(काष्ठा rq *this_rq, काष्ठा task_काष्ठा *task);
	व्योम (*चयनed_to)  (काष्ठा rq *this_rq, काष्ठा task_काष्ठा *task);
	व्योम (*prio_changed) (काष्ठा rq *this_rq, काष्ठा task_काष्ठा *task,
			      पूर्णांक oldprio);

	अचिन्हित पूर्णांक (*get_rr_पूर्णांकerval)(काष्ठा rq *rq,
					काष्ठा task_काष्ठा *task);

	व्योम (*update_curr)(काष्ठा rq *rq);

#घोषणा TASK_SET_GROUP		0
#घोषणा TASK_MOVE_GROUP		1

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	व्योम (*task_change_group)(काष्ठा task_काष्ठा *p, पूर्णांक type);
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत व्योम put_prev_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev)
अणु
	WARN_ON_ONCE(rq->curr != prev);
	prev->sched_class->put_prev_task(rq, prev);
पूर्ण

अटल अंतरभूत व्योम set_next_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *next)
अणु
	WARN_ON_ONCE(rq->curr != next);
	next->sched_class->set_next_task(rq, next, false);
पूर्ण


/*
 * Helper to define a sched_class instance; each one is placed in a separate
 * section which is ordered by the linker script:
 *
 *   include/यंत्र-generic/vmlinux.lds.h
 *
 * Also enक्रमce alignment on the instance, not the type, to guarantee layout.
 */
#घोषणा DEFINE_SCHED_CLASS(name) \
स्थिर काष्ठा sched_class name##_sched_class \
	__aligned(__alignof__(काष्ठा sched_class)) \
	__section("__" #name "_sched_class")

/* Defined in include/यंत्र-generic/vmlinux.lds.h */
बाह्य काष्ठा sched_class __begin_sched_classes[];
बाह्य काष्ठा sched_class __end_sched_classes[];

#घोषणा sched_class_highest (__end_sched_classes - 1)
#घोषणा sched_class_lowest  (__begin_sched_classes - 1)

#घोषणा क्रम_class_range(class, _from, _to) \
	क्रम (class = (_from); class != (_to); class--)

#घोषणा क्रम_each_class(class) \
	क्रम_class_range(class, sched_class_highest, sched_class_lowest)

बाह्य स्थिर काष्ठा sched_class stop_sched_class;
बाह्य स्थिर काष्ठा sched_class dl_sched_class;
बाह्य स्थिर काष्ठा sched_class rt_sched_class;
बाह्य स्थिर काष्ठा sched_class fair_sched_class;
बाह्य स्थिर काष्ठा sched_class idle_sched_class;

अटल अंतरभूत bool sched_stop_runnable(काष्ठा rq *rq)
अणु
	वापस rq->stop && task_on_rq_queued(rq->stop);
पूर्ण

अटल अंतरभूत bool sched_dl_runnable(काष्ठा rq *rq)
अणु
	वापस rq->dl.dl_nr_running > 0;
पूर्ण

अटल अंतरभूत bool sched_rt_runnable(काष्ठा rq *rq)
अणु
	वापस rq->rt.rt_queued > 0;
पूर्ण

अटल अंतरभूत bool sched_fair_runnable(काष्ठा rq *rq)
अणु
	वापस rq->cfs.nr_running > 0;
पूर्ण

बाह्य काष्ठा task_काष्ठा *pick_next_task_fair(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev, काष्ठा rq_flags *rf);
बाह्य काष्ठा task_काष्ठा *pick_next_task_idle(काष्ठा rq *rq);

#घोषणा SCA_CHECK		0x01
#घोषणा SCA_MIGRATE_DISABLE	0x02
#घोषणा SCA_MIGRATE_ENABLE	0x04

#अगर_घोषित CONFIG_SMP

बाह्य व्योम update_group_capacity(काष्ठा sched_करोमुख्य *sd, पूर्णांक cpu);

बाह्य व्योम trigger_load_balance(काष्ठा rq *rq);

बाह्य व्योम set_cpus_allowed_common(काष्ठा task_काष्ठा *p, स्थिर काष्ठा cpumask *new_mask, u32 flags);

अटल अंतरभूत काष्ठा task_काष्ठा *get_push_task(काष्ठा rq *rq)
अणु
	काष्ठा task_काष्ठा *p = rq->curr;

	lockdep_निश्चित_held(&rq->lock);

	अगर (rq->push_busy)
		वापस शून्य;

	अगर (p->nr_cpus_allowed == 1)
		वापस शून्य;

	rq->push_busy = true;
	वापस get_task_काष्ठा(p);
पूर्ण

बाह्य पूर्णांक push_cpu_stop(व्योम *arg);

#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_IDLE
अटल अंतरभूत व्योम idle_set_state(काष्ठा rq *rq,
				  काष्ठा cpuidle_state *idle_state)
अणु
	rq->idle_state = idle_state;
पूर्ण

अटल अंतरभूत काष्ठा cpuidle_state *idle_get_state(काष्ठा rq *rq)
अणु
	SCHED_WARN_ON(!rcu_पढ़ो_lock_held());

	वापस rq->idle_state;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम idle_set_state(काष्ठा rq *rq,
				  काष्ठा cpuidle_state *idle_state)
अणु
पूर्ण

अटल अंतरभूत काष्ठा cpuidle_state *idle_get_state(काष्ठा rq *rq)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

बाह्य व्योम schedule_idle(व्योम);

बाह्य व्योम sysrq_sched_debug_show(व्योम);
बाह्य व्योम sched_init_granularity(व्योम);
बाह्य व्योम update_max_पूर्णांकerval(व्योम);

बाह्य व्योम init_sched_dl_class(व्योम);
बाह्य व्योम init_sched_rt_class(व्योम);
बाह्य व्योम init_sched_fair_class(व्योम);

बाह्य व्योम reweight_task(काष्ठा task_काष्ठा *p, पूर्णांक prio);

बाह्य व्योम resched_curr(काष्ठा rq *rq);
बाह्य व्योम resched_cpu(पूर्णांक cpu);

बाह्य काष्ठा rt_bandwidth def_rt_bandwidth;
बाह्य व्योम init_rt_bandwidth(काष्ठा rt_bandwidth *rt_b, u64 period, u64 runसमय);

बाह्य काष्ठा dl_bandwidth def_dl_bandwidth;
बाह्य व्योम init_dl_bandwidth(काष्ठा dl_bandwidth *dl_b, u64 period, u64 runसमय);
बाह्य व्योम init_dl_task_समयr(काष्ठा sched_dl_entity *dl_se);
बाह्य व्योम init_dl_inactive_task_समयr(काष्ठा sched_dl_entity *dl_se);

#घोषणा BW_SHIFT		20
#घोषणा BW_UNIT			(1 << BW_SHIFT)
#घोषणा RATIO_SHIFT		8
#घोषणा MAX_BW_BITS		(64 - BW_SHIFT)
#घोषणा MAX_BW			((1ULL << MAX_BW_BITS) - 1)
अचिन्हित दीर्घ to_ratio(u64 period, u64 runसमय);

बाह्य व्योम init_entity_runnable_average(काष्ठा sched_entity *se);
बाह्य व्योम post_init_entity_util_avg(काष्ठा task_काष्ठा *p);

#अगर_घोषित CONFIG_NO_HZ_FULL
बाह्य bool sched_can_stop_tick(काष्ठा rq *rq);
बाह्य पूर्णांक __init sched_tick_offload_init(व्योम);

/*
 * Tick may be needed by tasks in the runqueue depending on their policy and
 * requirements. If tick is needed, lets send the target an IPI to kick it out of
 * nohz mode अगर necessary.
 */
अटल अंतरभूत व्योम sched_update_tick_dependency(काष्ठा rq *rq)
अणु
	पूर्णांक cpu = cpu_of(rq);

	अगर (!tick_nohz_full_cpu(cpu))
		वापस;

	अगर (sched_can_stop_tick(rq))
		tick_nohz_dep_clear_cpu(cpu, TICK_DEP_BIT_SCHED);
	अन्यथा
		tick_nohz_dep_set_cpu(cpu, TICK_DEP_BIT_SCHED);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक sched_tick_offload_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम sched_update_tick_dependency(काष्ठा rq *rq) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम add_nr_running(काष्ठा rq *rq, अचिन्हित count)
अणु
	अचिन्हित prev_nr = rq->nr_running;

	rq->nr_running = prev_nr + count;
	अगर (trace_sched_update_nr_running_tp_enabled()) अणु
		call_trace_sched_update_nr_running(rq, count);
	पूर्ण

#अगर_घोषित CONFIG_SMP
	अगर (prev_nr < 2 && rq->nr_running >= 2) अणु
		अगर (!READ_ONCE(rq->rd->overload))
			WRITE_ONCE(rq->rd->overload, 1);
	पूर्ण
#पूर्ण_अगर

	sched_update_tick_dependency(rq);
पूर्ण

अटल अंतरभूत व्योम sub_nr_running(काष्ठा rq *rq, अचिन्हित count)
अणु
	rq->nr_running -= count;
	अगर (trace_sched_update_nr_running_tp_enabled()) अणु
		call_trace_sched_update_nr_running(rq, -count);
	पूर्ण

	/* Check अगर we still need preemption */
	sched_update_tick_dependency(rq);
पूर्ण

बाह्य व्योम activate_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags);
बाह्य व्योम deactivate_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags);

बाह्य व्योम check_preempt_curr(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags);

बाह्य स्थिर_debug अचिन्हित पूर्णांक sysctl_sched_nr_migrate;
बाह्य स्थिर_debug अचिन्हित पूर्णांक sysctl_sched_migration_cost;

#अगर_घोषित CONFIG_SCHED_HRTICK

/*
 * Use hrtick when:
 *  - enabled by features
 *  - hrसमयr is actually high res
 */
अटल अंतरभूत पूर्णांक hrtick_enabled(काष्ठा rq *rq)
अणु
	अगर (!cpu_active(cpu_of(rq)))
		वापस 0;
	वापस hrसमयr_is_hres_active(&rq->hrtick_समयr);
पूर्ण

अटल अंतरभूत पूर्णांक hrtick_enabled_fair(काष्ठा rq *rq)
अणु
	अगर (!sched_feat(HRTICK))
		वापस 0;
	वापस hrtick_enabled(rq);
पूर्ण

अटल अंतरभूत पूर्णांक hrtick_enabled_dl(काष्ठा rq *rq)
अणु
	अगर (!sched_feat(HRTICK_DL))
		वापस 0;
	वापस hrtick_enabled(rq);
पूर्ण

व्योम hrtick_start(काष्ठा rq *rq, u64 delay);

#अन्यथा

अटल अंतरभूत पूर्णांक hrtick_enabled_fair(काष्ठा rq *rq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hrtick_enabled_dl(काष्ठा rq *rq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hrtick_enabled(काष्ठा rq *rq)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_SCHED_HRTICK */

#अगर_अघोषित arch_scale_freq_tick
अटल __always_अंतरभूत
व्योम arch_scale_freq_tick(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित arch_scale_freq_capacity
/**
 * arch_scale_freq_capacity - get the frequency scale factor of a given CPU.
 * @cpu: the CPU in question.
 *
 * Return: the frequency scale factor normalized against SCHED_CAPACITY_SCALE, i.e.
 *
 *     f_curr
 *     ------ * SCHED_CAPACITY_SCALE
 *     f_max
 */
अटल __always_अंतरभूत
अचिन्हित दीर्घ arch_scale_freq_capacity(पूर्णांक cpu)
अणु
	वापस SCHED_CAPACITY_SCALE;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
#अगर_घोषित CONFIG_PREEMPTION

अटल अंतरभूत व्योम द्विगुन_rq_lock(काष्ठा rq *rq1, काष्ठा rq *rq2);

/*
 * fair द्विगुन_lock_balance: Safely acquires both rq->locks in a fair
 * way at the expense of क्रमcing extra atomic operations in all
 * invocations.  This assures that the द्विगुन_lock is acquired using the
 * same underlying policy as the spinlock_t on this architecture, which
 * reduces latency compared to the unfair variant below.  However, it
 * also adds more overhead and thereक्रमe may reduce throughput.
 */
अटल अंतरभूत पूर्णांक _द्विगुन_lock_balance(काष्ठा rq *this_rq, काष्ठा rq *busiest)
	__releases(this_rq->lock)
	__acquires(busiest->lock)
	__acquires(this_rq->lock)
अणु
	raw_spin_unlock(&this_rq->lock);
	द्विगुन_rq_lock(this_rq, busiest);

	वापस 1;
पूर्ण

#अन्यथा
/*
 * Unfair द्विगुन_lock_balance: Optimizes throughput at the expense of
 * latency by eliminating extra atomic operations when the locks are
 * alपढ़ोy in proper order on entry.  This favors lower CPU-ids and will
 * grant the द्विगुन lock to lower CPUs over higher ids under contention,
 * regardless of entry order पूर्णांकo the function.
 */
अटल अंतरभूत पूर्णांक _द्विगुन_lock_balance(काष्ठा rq *this_rq, काष्ठा rq *busiest)
	__releases(this_rq->lock)
	__acquires(busiest->lock)
	__acquires(this_rq->lock)
अणु
	पूर्णांक ret = 0;

	अगर (unlikely(!raw_spin_trylock(&busiest->lock))) अणु
		अगर (busiest < this_rq) अणु
			raw_spin_unlock(&this_rq->lock);
			raw_spin_lock(&busiest->lock);
			raw_spin_lock_nested(&this_rq->lock,
					      SINGLE_DEPTH_NESTING);
			ret = 1;
		पूर्ण अन्यथा
			raw_spin_lock_nested(&busiest->lock,
					      SINGLE_DEPTH_NESTING);
	पूर्ण
	वापस ret;
पूर्ण

#पूर्ण_अगर /* CONFIG_PREEMPTION */

/*
 * द्विगुन_lock_balance - lock the busiest runqueue, this_rq is locked alपढ़ोy.
 */
अटल अंतरभूत पूर्णांक द्विगुन_lock_balance(काष्ठा rq *this_rq, काष्ठा rq *busiest)
अणु
	अगर (unlikely(!irqs_disabled())) अणु
		/* prपूर्णांकk() करोesn't work well under rq->lock */
		raw_spin_unlock(&this_rq->lock);
		BUG_ON(1);
	पूर्ण

	वापस _द्विगुन_lock_balance(this_rq, busiest);
पूर्ण

अटल अंतरभूत व्योम द्विगुन_unlock_balance(काष्ठा rq *this_rq, काष्ठा rq *busiest)
	__releases(busiest->lock)
अणु
	raw_spin_unlock(&busiest->lock);
	lock_set_subclass(&this_rq->lock.dep_map, 0, _RET_IP_);
पूर्ण

अटल अंतरभूत व्योम द्विगुन_lock(spinlock_t *l1, spinlock_t *l2)
अणु
	अगर (l1 > l2)
		swap(l1, l2);

	spin_lock(l1);
	spin_lock_nested(l2, SINGLE_DEPTH_NESTING);
पूर्ण

अटल अंतरभूत व्योम द्विगुन_lock_irq(spinlock_t *l1, spinlock_t *l2)
अणु
	अगर (l1 > l2)
		swap(l1, l2);

	spin_lock_irq(l1);
	spin_lock_nested(l2, SINGLE_DEPTH_NESTING);
पूर्ण

अटल अंतरभूत व्योम द्विगुन_raw_lock(raw_spinlock_t *l1, raw_spinlock_t *l2)
अणु
	अगर (l1 > l2)
		swap(l1, l2);

	raw_spin_lock(l1);
	raw_spin_lock_nested(l2, SINGLE_DEPTH_NESTING);
पूर्ण

/*
 * द्विगुन_rq_lock - safely lock two runqueues
 *
 * Note this करोes not disable पूर्णांकerrupts like task_rq_lock,
 * you need to करो so manually beक्रमe calling.
 */
अटल अंतरभूत व्योम द्विगुन_rq_lock(काष्ठा rq *rq1, काष्ठा rq *rq2)
	__acquires(rq1->lock)
	__acquires(rq2->lock)
अणु
	BUG_ON(!irqs_disabled());
	अगर (rq1 == rq2) अणु
		raw_spin_lock(&rq1->lock);
		__acquire(rq2->lock);	/* Fake it out ;) */
	पूर्ण अन्यथा अणु
		अगर (rq1 < rq2) अणु
			raw_spin_lock(&rq1->lock);
			raw_spin_lock_nested(&rq2->lock, SINGLE_DEPTH_NESTING);
		पूर्ण अन्यथा अणु
			raw_spin_lock(&rq2->lock);
			raw_spin_lock_nested(&rq1->lock, SINGLE_DEPTH_NESTING);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * द्विगुन_rq_unlock - safely unlock two runqueues
 *
 * Note this करोes not restore पूर्णांकerrupts like task_rq_unlock,
 * you need to करो so manually after calling.
 */
अटल अंतरभूत व्योम द्विगुन_rq_unlock(काष्ठा rq *rq1, काष्ठा rq *rq2)
	__releases(rq1->lock)
	__releases(rq2->lock)
अणु
	raw_spin_unlock(&rq1->lock);
	अगर (rq1 != rq2)
		raw_spin_unlock(&rq2->lock);
	अन्यथा
		__release(rq2->lock);
पूर्ण

बाह्य व्योम set_rq_online (काष्ठा rq *rq);
बाह्य व्योम set_rq_offline(काष्ठा rq *rq);
बाह्य bool sched_smp_initialized;

#अन्यथा /* CONFIG_SMP */

/*
 * द्विगुन_rq_lock - safely lock two runqueues
 *
 * Note this करोes not disable पूर्णांकerrupts like task_rq_lock,
 * you need to करो so manually beक्रमe calling.
 */
अटल अंतरभूत व्योम द्विगुन_rq_lock(काष्ठा rq *rq1, काष्ठा rq *rq2)
	__acquires(rq1->lock)
	__acquires(rq2->lock)
अणु
	BUG_ON(!irqs_disabled());
	BUG_ON(rq1 != rq2);
	raw_spin_lock(&rq1->lock);
	__acquire(rq2->lock);	/* Fake it out ;) */
पूर्ण

/*
 * द्विगुन_rq_unlock - safely unlock two runqueues
 *
 * Note this करोes not restore पूर्णांकerrupts like task_rq_unlock,
 * you need to करो so manually after calling.
 */
अटल अंतरभूत व्योम द्विगुन_rq_unlock(काष्ठा rq *rq1, काष्ठा rq *rq2)
	__releases(rq1->lock)
	__releases(rq2->lock)
अणु
	BUG_ON(rq1 != rq2);
	raw_spin_unlock(&rq1->lock);
	__release(rq2->lock);
पूर्ण

#पूर्ण_अगर

बाह्य काष्ठा sched_entity *__pick_first_entity(काष्ठा cfs_rq *cfs_rq);
बाह्य काष्ठा sched_entity *__pick_last_entity(काष्ठा cfs_rq *cfs_rq);

#अगर_घोषित	CONFIG_SCHED_DEBUG
बाह्य bool sched_debug_verbose;

बाह्य व्योम prपूर्णांक_cfs_stats(काष्ठा seq_file *m, पूर्णांक cpu);
बाह्य व्योम prपूर्णांक_rt_stats(काष्ठा seq_file *m, पूर्णांक cpu);
बाह्य व्योम prपूर्णांक_dl_stats(काष्ठा seq_file *m, पूर्णांक cpu);
बाह्य व्योम prपूर्णांक_cfs_rq(काष्ठा seq_file *m, पूर्णांक cpu, काष्ठा cfs_rq *cfs_rq);
बाह्य व्योम prपूर्णांक_rt_rq(काष्ठा seq_file *m, पूर्णांक cpu, काष्ठा rt_rq *rt_rq);
बाह्य व्योम prपूर्णांक_dl_rq(काष्ठा seq_file *m, पूर्णांक cpu, काष्ठा dl_rq *dl_rq);

बाह्य व्योम resched_latency_warn(पूर्णांक cpu, u64 latency);
#अगर_घोषित CONFIG_NUMA_BALANCING
बाह्य व्योम
show_numa_stats(काष्ठा task_काष्ठा *p, काष्ठा seq_file *m);
बाह्य व्योम
prपूर्णांक_numa_stats(काष्ठा seq_file *m, पूर्णांक node, अचिन्हित दीर्घ tsf,
	अचिन्हित दीर्घ tpf, अचिन्हित दीर्घ gsf, अचिन्हित दीर्घ gpf);
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */
#अन्यथा
अटल अंतरभूत व्योम resched_latency_warn(पूर्णांक cpu, u64 latency) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_SCHED_DEBUG */

बाह्य व्योम init_cfs_rq(काष्ठा cfs_rq *cfs_rq);
बाह्य व्योम init_rt_rq(काष्ठा rt_rq *rt_rq);
बाह्य व्योम init_dl_rq(काष्ठा dl_rq *dl_rq);

बाह्य व्योम cfs_bandwidth_usage_inc(व्योम);
बाह्य व्योम cfs_bandwidth_usage_dec(व्योम);

#अगर_घोषित CONFIG_NO_HZ_COMMON
#घोषणा NOHZ_BALANCE_KICK_BIT	0
#घोषणा NOHZ_STATS_KICK_BIT	1
#घोषणा NOHZ_NEWILB_KICK_BIT	2

#घोषणा NOHZ_BALANCE_KICK	BIT(NOHZ_BALANCE_KICK_BIT)
#घोषणा NOHZ_STATS_KICK		BIT(NOHZ_STATS_KICK_BIT)
#घोषणा NOHZ_NEWILB_KICK	BIT(NOHZ_NEWILB_KICK_BIT)

#घोषणा NOHZ_KICK_MASK	(NOHZ_BALANCE_KICK | NOHZ_STATS_KICK)

#घोषणा nohz_flags(cpu)	(&cpu_rq(cpu)->nohz_flags)

बाह्य व्योम nohz_balance_निकास_idle(काष्ठा rq *rq);
#अन्यथा
अटल अंतरभूत व्योम nohz_balance_निकास_idle(काष्ठा rq *rq) अणु पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SMP) && defined(CONFIG_NO_HZ_COMMON)
बाह्य व्योम nohz_run_idle_balance(पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत व्योम nohz_run_idle_balance(पूर्णांक cpu) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत
व्योम __dl_update(काष्ठा dl_bw *dl_b, s64 bw)
अणु
	काष्ठा root_करोमुख्य *rd = container_of(dl_b, काष्ठा root_करोमुख्य, dl_bw);
	पूर्णांक i;

	RCU_LOCKDEP_WARN(!rcu_पढ़ो_lock_sched_held(),
			 "sched RCU must be held");
	क्रम_each_cpu_and(i, rd->span, cpu_active_mask) अणु
		काष्ठा rq *rq = cpu_rq(i);

		rq->dl.extra_bw += bw;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत
व्योम __dl_update(काष्ठा dl_bw *dl_b, s64 bw)
अणु
	काष्ठा dl_rq *dl = container_of(dl_b, काष्ठा dl_rq, dl_bw);

	dl->extra_bw += bw;
पूर्ण
#पूर्ण_अगर


#अगर_घोषित CONFIG_IRQ_TIME_ACCOUNTING
काष्ठा irqसमय अणु
	u64			total;
	u64			tick_delta;
	u64			irq_start_समय;
	काष्ठा u64_stats_sync	sync;
पूर्ण;

DECLARE_PER_CPU(काष्ठा irqसमय, cpu_irqसमय);

/*
 * Returns the irqसमय minus the softirq समय computed by ksoftirqd.
 * Otherwise ksoftirqd's sum_exec_runसमय is subtracted its own runसमय
 * and never move क्रमward.
 */
अटल अंतरभूत u64 irq_समय_पढ़ो(पूर्णांक cpu)
अणु
	काष्ठा irqसमय *irqसमय = &per_cpu(cpu_irqसमय, cpu);
	अचिन्हित पूर्णांक seq;
	u64 total;

	करो अणु
		seq = __u64_stats_fetch_begin(&irqसमय->sync);
		total = irqसमय->total;
	पूर्ण जबतक (__u64_stats_fetch_retry(&irqसमय->sync, seq));

	वापस total;
पूर्ण
#पूर्ण_अगर /* CONFIG_IRQ_TIME_ACCOUNTING */

#अगर_घोषित CONFIG_CPU_FREQ
DECLARE_PER_CPU(काष्ठा update_util_data __rcu *, cpufreq_update_util_data);

/**
 * cpufreq_update_util - Take a note about CPU utilization changes.
 * @rq: Runqueue to carry out the update क्रम.
 * @flags: Update reason flags.
 *
 * This function is called by the scheduler on the CPU whose utilization is
 * being updated.
 *
 * It can only be called from RCU-sched पढ़ो-side critical sections.
 *
 * The way cpufreq is currently arranged requires it to evaluate the CPU
 * perक्रमmance state (frequency/voltage) on a regular basis to prevent it from
 * being stuck in a completely inadequate perक्रमmance level क्रम too दीर्घ.
 * That is not guaranteed to happen अगर the updates are only triggered from CFS
 * and DL, though, because they may not be coming in अगर only RT tasks are
 * active all the समय (or there are RT tasks only).
 *
 * As a workaround क्रम that issue, this function is called periodically by the
 * RT sched class to trigger extra cpufreq updates to prevent it from stalling,
 * but that really is a band-aid.  Going क्रमward it should be replaced with
 * solutions targeted more specअगरically at RT tasks.
 */
अटल अंतरभूत व्योम cpufreq_update_util(काष्ठा rq *rq, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा update_util_data *data;

	data = rcu_dereference_sched(*per_cpu_ptr(&cpufreq_update_util_data,
						  cpu_of(rq)));
	अगर (data)
		data->func(data, rq_घड़ी(rq), flags);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cpufreq_update_util(काष्ठा rq *rq, अचिन्हित पूर्णांक flags) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_CPU_FREQ */

#अगर_घोषित CONFIG_UCLAMP_TASK
अचिन्हित दीर्घ uclamp_eff_value(काष्ठा task_काष्ठा *p, क्रमागत uclamp_id clamp_id);

/**
 * uclamp_rq_util_with - clamp @util with @rq and @p effective uclamp values.
 * @rq:		The rq to clamp against. Must not be शून्य.
 * @util:	The util value to clamp.
 * @p:		The task to clamp against. Can be शून्य अगर you want to clamp
 *		against @rq only.
 *
 * Clamps the passed @util to the max(@rq, @p) effective uclamp values.
 *
 * If sched_uclamp_used अटल key is disabled, then just वापस the util
 * without any clamping since uclamp aggregation at the rq level in the fast
 * path is disabled, rendering this operation a NOP.
 *
 * Use uclamp_eff_value() अगर you करोn't care about uclamp values at rq level. It
 * will वापस the correct effective uclamp value of the task even अगर the
 * अटल key is disabled.
 */
अटल __always_अंतरभूत
अचिन्हित दीर्घ uclamp_rq_util_with(काष्ठा rq *rq, अचिन्हित दीर्घ util,
				  काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ min_util;
	अचिन्हित दीर्घ max_util;

	अगर (!अटल_branch_likely(&sched_uclamp_used))
		वापस util;

	min_util = READ_ONCE(rq->uclamp[UCLAMP_MIN].value);
	max_util = READ_ONCE(rq->uclamp[UCLAMP_MAX].value);

	अगर (p) अणु
		min_util = max(min_util, uclamp_eff_value(p, UCLAMP_MIN));
		max_util = max(max_util, uclamp_eff_value(p, UCLAMP_MAX));
	पूर्ण

	/*
	 * Since CPU's अणुmin,maxपूर्ण_util clamps are MAX aggregated considering
	 * RUNNABLE tasks with _dअगरferent_ clamps, we can end up with an
	 * inversion. Fix it now when the clamps are applied.
	 */
	अगर (unlikely(min_util >= max_util))
		वापस min_util;

	वापस clamp(util, min_util, max_util);
पूर्ण

/*
 * When uclamp is compiled in, the aggregation at rq level is 'turned off'
 * by शेष in the fast path and only माला_लो turned on once userspace perक्रमms
 * an operation that requires it.
 *
 * Returns true अगर userspace opted-in to use uclamp and aggregation at rq level
 * hence is active.
 */
अटल अंतरभूत bool uclamp_is_used(व्योम)
अणु
	वापस अटल_branch_likely(&sched_uclamp_used);
पूर्ण
#अन्यथा /* CONFIG_UCLAMP_TASK */
अटल अंतरभूत
अचिन्हित दीर्घ uclamp_rq_util_with(काष्ठा rq *rq, अचिन्हित दीर्घ util,
				  काष्ठा task_काष्ठा *p)
अणु
	वापस util;
पूर्ण

अटल अंतरभूत bool uclamp_is_used(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_UCLAMP_TASK */

#अगर_घोषित arch_scale_freq_capacity
# अगरndef arch_scale_freq_invariant
#  define arch_scale_freq_invariant()	true
# endअगर
#अन्यथा
# define arch_scale_freq_invariant()	false
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत अचिन्हित दीर्घ capacity_orig_of(पूर्णांक cpu)
अणु
	वापस cpu_rq(cpu)->cpu_capacity_orig;
पूर्ण

/**
 * क्रमागत cpu_util_type - CPU utilization type
 * @FREQUENCY_UTIL:	Utilization used to select frequency
 * @ENERGY_UTIL:	Utilization used during energy calculation
 *
 * The utilization संकेतs of all scheduling classes (CFS/RT/DL) and IRQ समय
 * need to be aggregated dअगरferently depending on the usage made of them. This
 * क्रमागत is used within effective_cpu_util() to dअगरferentiate the types of
 * utilization expected by the callers, and adjust the aggregation accordingly.
 */
क्रमागत cpu_util_type अणु
	FREQUENCY_UTIL,
	ENERGY_UTIL,
पूर्ण;

अचिन्हित दीर्घ effective_cpu_util(पूर्णांक cpu, अचिन्हित दीर्घ util_cfs,
				 अचिन्हित दीर्घ max, क्रमागत cpu_util_type type,
				 काष्ठा task_काष्ठा *p);

अटल अंतरभूत अचिन्हित दीर्घ cpu_bw_dl(काष्ठा rq *rq)
अणु
	वापस (rq->dl.running_bw * SCHED_CAPACITY_SCALE) >> BW_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cpu_util_dl(काष्ठा rq *rq)
अणु
	वापस READ_ONCE(rq->avg_dl.util_avg);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cpu_util_cfs(काष्ठा rq *rq)
अणु
	अचिन्हित दीर्घ util = READ_ONCE(rq->cfs.avg.util_avg);

	अगर (sched_feat(UTIL_EST)) अणु
		util = max_t(अचिन्हित दीर्घ, util,
			     READ_ONCE(rq->cfs.avg.util_est.enqueued));
	पूर्ण

	वापस util;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cpu_util_rt(काष्ठा rq *rq)
अणु
	वापस READ_ONCE(rq->avg_rt.util_avg);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_SCHED_AVG_IRQ
अटल अंतरभूत अचिन्हित दीर्घ cpu_util_irq(काष्ठा rq *rq)
अणु
	वापस rq->avg_irq.util_avg;
पूर्ण

अटल अंतरभूत
अचिन्हित दीर्घ scale_irq_capacity(अचिन्हित दीर्घ util, अचिन्हित दीर्घ irq, अचिन्हित दीर्घ max)
अणु
	util *= (max - irq);
	util /= max;

	वापस util;

पूर्ण
#अन्यथा
अटल अंतरभूत अचिन्हित दीर्घ cpu_util_irq(काष्ठा rq *rq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
अचिन्हित दीर्घ scale_irq_capacity(अचिन्हित दीर्घ util, अचिन्हित दीर्घ irq, अचिन्हित दीर्घ max)
अणु
	वापस util;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ENERGY_MODEL) && defined(CONFIG_CPU_FREQ_GOV_SCHEDUTIL)

#घोषणा perf_करोमुख्य_span(pd) (to_cpumask(((pd)->em_pd->cpus)))

DECLARE_STATIC_KEY_FALSE(sched_energy_present);

अटल अंतरभूत bool sched_energy_enabled(व्योम)
अणु
	वापस अटल_branch_unlikely(&sched_energy_present);
पूर्ण

#अन्यथा /* ! (CONFIG_ENERGY_MODEL && CONFIG_CPU_FREQ_GOV_SCHEDUTIL) */

#घोषणा perf_करोमुख्य_span(pd) शून्य
अटल अंतरभूत bool sched_energy_enabled(व्योम) अणु वापस false; पूर्ण

#पूर्ण_अगर /* CONFIG_ENERGY_MODEL && CONFIG_CPU_FREQ_GOV_SCHEDUTIL */

#अगर_घोषित CONFIG_MEMBARRIER
/*
 * The scheduler provides memory barriers required by membarrier between:
 * - prior user-space memory accesses and store to rq->membarrier_state,
 * - store to rq->membarrier_state and following user-space memory accesses.
 * In the same way it provides those guarantees around store to rq->curr.
 */
अटल अंतरभूत व्योम membarrier_चयन_mm(काष्ठा rq *rq,
					काष्ठा mm_काष्ठा *prev_mm,
					काष्ठा mm_काष्ठा *next_mm)
अणु
	पूर्णांक membarrier_state;

	अगर (prev_mm == next_mm)
		वापस;

	membarrier_state = atomic_पढ़ो(&next_mm->membarrier_state);
	अगर (READ_ONCE(rq->membarrier_state) == membarrier_state)
		वापस;

	WRITE_ONCE(rq->membarrier_state, membarrier_state);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम membarrier_चयन_mm(काष्ठा rq *rq,
					काष्ठा mm_काष्ठा *prev_mm,
					काष्ठा mm_काष्ठा *next_mm)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत bool is_per_cpu_kthपढ़ो(काष्ठा task_काष्ठा *p)
अणु
	अगर (!(p->flags & PF_KTHREAD))
		वापस false;

	अगर (p->nr_cpus_allowed != 1)
		वापस false;

	वापस true;
पूर्ण
#पूर्ण_अगर

बाह्य व्योम swake_up_all_locked(काष्ठा sरुको_queue_head *q);
बाह्य व्योम __prepare_to_sरुको(काष्ठा sरुको_queue_head *q, काष्ठा sरुको_queue *रुको);

#अगर_घोषित CONFIG_PREEMPT_DYNAMIC
बाह्य पूर्णांक preempt_dynamic_mode;
बाह्य पूर्णांक sched_dynamic_mode(स्थिर अक्षर *str);
बाह्य व्योम sched_dynamic_update(पूर्णांक mode);
#पूर्ण_अगर

