<शैली गुरु>
/*
 * Pressure stall inक्रमmation क्रम CPU, memory and IO
 *
 * Copyright (c) 2018 Facebook, Inc.
 * Author: Johannes Weiner <hannes@cmpxchg.org>
 *
 * Polling support by Suren Baghdasaryan <surenb@google.com>
 * Copyright (c) 2018 Google, Inc.
 *
 * When CPU, memory and IO are contended, tasks experience delays that
 * reduce throughput and पूर्णांकroduce latencies पूर्णांकo the workload. Memory
 * and IO contention, in addition, can cause a full loss of क्रमward
 * progress in which the CPU goes idle.
 *
 * This code aggregates inभागidual task delays पूर्णांकo resource pressure
 * metrics that indicate problems with both workload health and
 * resource utilization.
 *
 *			Model
 *
 * The समय in which a task can execute on a CPU is our baseline क्रम
 * productivity. Pressure expresses the amount of समय in which this
 * potential cannot be realized due to resource contention.
 *
 * This concept of productivity has two components: the workload and
 * the CPU. To measure the impact of pressure on both, we define two
 * contention states क्रम a resource: SOME and FULL.
 *
 * In the SOME state of a given resource, one or more tasks are
 * delayed on that resource. This affects the workload's ability to
 * perक्रमm work, but the CPU may still be executing other tasks.
 *
 * In the FULL state of a given resource, all non-idle tasks are
 * delayed on that resource such that nobody is advancing and the CPU
 * goes idle. This leaves both workload and CPU unproductive.
 *
 * Naturally, the FULL state करोesn't exist क्रम the CPU resource at the
 * प्रणाली level, but exist at the cgroup level, means all non-idle tasks
 * in a cgroup are delayed on the CPU resource which used by others outside
 * of the cgroup or throttled by the cgroup cpu.max configuration.
 *
 *	SOME = nr_delayed_tasks != 0
 *	FULL = nr_delayed_tasks != 0 && nr_running_tasks == 0
 *
 * The percentage of wallघड़ी समय spent in those compound stall
 * states gives pressure numbers between 0 and 100 क्रम each resource,
 * where the SOME percentage indicates workload slowकरोwns and the FULL
 * percentage indicates reduced CPU utilization:
 *
 *	%SOME = समय(SOME) / period
 *	%FULL = समय(FULL) / period
 *
 *			Multiple CPUs
 *
 * The more tasks and available CPUs there are, the more work can be
 * perक्रमmed concurrently. This means that the potential that can go
 * unrealized due to resource contention *also* scales with non-idle
 * tasks and CPUs.
 *
 * Consider a scenario where 257 number crunching tasks are trying to
 * run concurrently on 256 CPUs. If we simply aggregated the task
 * states, we would have to conclude a CPU SOME pressure number of
 * 100%, since *somebody* is रुकोing on a runqueue at all
 * बार. However, that is clearly not the amount of contention the
 * workload is experiencing: only one out of 256 possible execution
 * thपढ़ोs will be contended at any given समय, or about 0.4%.
 *
 * Conversely, consider a scenario of 4 tasks and 4 CPUs where at any
 * given समय *one* of the tasks is delayed due to a lack of memory.
 * Again, looking purely at the task state would yield a memory FULL
 * pressure number of 0%, since *somebody* is always making क्रमward
 * progress. But again this wouldn't capture the amount of execution
 * potential lost, which is 1 out of 4 CPUs, or 25%.
 *
 * To calculate wasted potential (pressure) with multiple processors,
 * we have to base our calculation on the number of non-idle tasks in
 * conjunction with the number of available CPUs, which is the number
 * of potential execution thपढ़ोs. SOME becomes then the proportion of
 * delayed tasks to possible thपढ़ोs, and FULL is the share of possible
 * thपढ़ोs that are unproductive due to delays:
 *
 *	thपढ़ोs = min(nr_nonidle_tasks, nr_cpus)
 *	   SOME = min(nr_delayed_tasks / thपढ़ोs, 1)
 *	   FULL = (thपढ़ोs - min(nr_running_tasks, thपढ़ोs)) / thपढ़ोs
 *
 * For the 257 number crunchers on 256 CPUs, this yields:
 *
 *	thपढ़ोs = min(257, 256)
 *	   SOME = min(1 / 256, 1)             = 0.4%
 *	   FULL = (256 - min(257, 256)) / 256 = 0%
 *
 * For the 1 out of 4 memory-delayed tasks, this yields:
 *
 *	thपढ़ोs = min(4, 4)
 *	   SOME = min(1 / 4, 1)               = 25%
 *	   FULL = (4 - min(3, 4)) / 4         = 25%
 *
 * [ Substitute nr_cpus with 1, and you can see that it's a natural
 *   extension of the single-CPU model. ]
 *
 *			Implementation
 *
 * To assess the precise समय spent in each such state, we would have
 * to मुक्तze the प्रणाली on task changes and start/stop the state
 * घड़ीs accordingly. Obviously that करोesn't scale in practice.
 *
 * Because the scheduler aims to distribute the compute load evenly
 * among the available CPUs, we can track task state locally to each
 * CPU and, at much lower frequency, extrapolate the global state क्रम
 * the cumulative stall बार and the running averages.
 *
 * For each runqueue, we track:
 *
 *	   tSOME[cpu] = समय(nr_delayed_tasks[cpu] != 0)
 *	   tFULL[cpu] = समय(nr_delayed_tasks[cpu] && !nr_running_tasks[cpu])
 *	tNONIDLE[cpu] = समय(nr_nonidle_tasks[cpu] != 0)
 *
 * and then periodically aggregate:
 *
 *	tNONIDLE = sum(tNONIDLE[i])
 *
 *	   tSOME = sum(tSOME[i] * tNONIDLE[i]) / tNONIDLE
 *	   tFULL = sum(tFULL[i] * tNONIDLE[i]) / tNONIDLE
 *
 *	   %SOME = tSOME / period
 *	   %FULL = tFULL / period
 *
 * This gives us an approximation of pressure that is practical
 * cost-wise, yet way more sensitive and accurate than periodic
 * sampling of the aggregate task states would be.
 */

#समावेश "../workqueue_internal.h"
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/file.h>
#समावेश <linux/poll.h>
#समावेश <linux/psi.h>
#समावेश "sched.h"

अटल पूर्णांक psi_bug __पढ़ो_mostly;

DEFINE_STATIC_KEY_FALSE(psi_disabled);

#अगर_घोषित CONFIG_PSI_DEFAULT_DISABLED
अटल bool psi_enable;
#अन्यथा
अटल bool psi_enable = true;
#पूर्ण_अगर
अटल पूर्णांक __init setup_psi(अक्षर *str)
अणु
	वापस kstrtobool(str, &psi_enable) == 0;
पूर्ण
__setup("psi=", setup_psi);

/* Running averages - we need to be higher-res than loadavg */
#घोषणा PSI_FREQ	(2*HZ+1)	/* 2 sec पूर्णांकervals */
#घोषणा EXP_10s		1677		/* 1/exp(2s/10s) as fixed-poपूर्णांक */
#घोषणा EXP_60s		1981		/* 1/exp(2s/60s) */
#घोषणा EXP_300s	2034		/* 1/exp(2s/300s) */

/* PSI trigger definitions */
#घोषणा WINDOW_MIN_US 500000	/* Min winकरोw size is 500ms */
#घोषणा WINDOW_MAX_US 10000000	/* Max winकरोw size is 10s */
#घोषणा UPDATES_PER_WINDOW 10	/* 10 updates per winकरोw */

/* Sampling frequency in nanoseconds */
अटल u64 psi_period __पढ़ो_mostly;

/* System-level pressure and stall tracking */
अटल DEFINE_PER_CPU(काष्ठा psi_group_cpu, प्रणाली_group_pcpu);
काष्ठा psi_group psi_प्रणाली = अणु
	.pcpu = &प्रणाली_group_pcpu,
पूर्ण;

अटल व्योम psi_avgs_work(काष्ठा work_काष्ठा *work);

अटल व्योम group_init(काष्ठा psi_group *group)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		seqcount_init(&per_cpu_ptr(group->pcpu, cpu)->seq);
	group->avg_last_update = sched_घड़ी();
	group->avg_next_update = group->avg_last_update + psi_period;
	INIT_DELAYED_WORK(&group->avgs_work, psi_avgs_work);
	mutex_init(&group->avgs_lock);
	/* Init trigger-related members */
	mutex_init(&group->trigger_lock);
	INIT_LIST_HEAD(&group->triggers);
	स_रखो(group->nr_triggers, 0, माप(group->nr_triggers));
	group->poll_states = 0;
	group->poll_min_period = U32_MAX;
	स_रखो(group->polling_total, 0, माप(group->polling_total));
	group->polling_next_update = ULदीर्घ_उच्च;
	group->polling_until = 0;
	rcu_assign_poपूर्णांकer(group->poll_task, शून्य);
पूर्ण

व्योम __init psi_init(व्योम)
अणु
	अगर (!psi_enable) अणु
		अटल_branch_enable(&psi_disabled);
		वापस;
	पूर्ण

	psi_period = jअगरfies_to_nsecs(PSI_FREQ);
	group_init(&psi_प्रणाली);
पूर्ण

अटल bool test_state(अचिन्हित पूर्णांक *tasks, क्रमागत psi_states state)
अणु
	चयन (state) अणु
	हाल PSI_IO_SOME:
		वापस unlikely(tasks[NR_IOWAIT]);
	हाल PSI_IO_FULL:
		वापस unlikely(tasks[NR_IOWAIT] && !tasks[NR_RUNNING]);
	हाल PSI_MEM_SOME:
		वापस unlikely(tasks[NR_MEMSTALL]);
	हाल PSI_MEM_FULL:
		वापस unlikely(tasks[NR_MEMSTALL] && !tasks[NR_RUNNING]);
	हाल PSI_CPU_SOME:
		वापस unlikely(tasks[NR_RUNNING] > tasks[NR_ONCPU]);
	हाल PSI_CPU_FULL:
		वापस unlikely(tasks[NR_RUNNING] && !tasks[NR_ONCPU]);
	हाल PSI_NONIDLE:
		वापस tasks[NR_IOWAIT] || tasks[NR_MEMSTALL] ||
			tasks[NR_RUNNING];
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम get_recent_बार(काष्ठा psi_group *group, पूर्णांक cpu,
			     क्रमागत psi_aggregators aggregator, u32 *बार,
			     u32 *pchanged_states)
अणु
	काष्ठा psi_group_cpu *groupc = per_cpu_ptr(group->pcpu, cpu);
	u64 now, state_start;
	क्रमागत psi_states s;
	अचिन्हित पूर्णांक seq;
	u32 state_mask;

	*pchanged_states = 0;

	/* Snapshot a coherent view of the CPU state */
	करो अणु
		seq = पढ़ो_seqcount_begin(&groupc->seq);
		now = cpu_घड़ी(cpu);
		स_नकल(बार, groupc->बार, माप(groupc->बार));
		state_mask = groupc->state_mask;
		state_start = groupc->state_start;
	पूर्ण जबतक (पढ़ो_seqcount_retry(&groupc->seq, seq));

	/* Calculate state समय deltas against the previous snapshot */
	क्रम (s = 0; s < NR_PSI_STATES; s++) अणु
		u32 delta;
		/*
		 * In addition to alपढ़ोy concluded states, we also
		 * incorporate currently active states on the CPU,
		 * since states may last क्रम many sampling periods.
		 *
		 * This way we keep our delta sampling buckets small
		 * (u32) and our reported pressure बंद to what's
		 * actually happening.
		 */
		अगर (state_mask & (1 << s))
			बार[s] += now - state_start;

		delta = बार[s] - groupc->बार_prev[aggregator][s];
		groupc->बार_prev[aggregator][s] = बार[s];

		बार[s] = delta;
		अगर (delta)
			*pchanged_states |= (1 << s);
	पूर्ण
पूर्ण

अटल व्योम calc_avgs(अचिन्हित दीर्घ avg[3], पूर्णांक missed_periods,
		      u64 समय, u64 period)
अणु
	अचिन्हित दीर्घ pct;

	/* Fill in zeroes क्रम periods of no activity */
	अगर (missed_periods) अणु
		avg[0] = calc_load_n(avg[0], EXP_10s, 0, missed_periods);
		avg[1] = calc_load_n(avg[1], EXP_60s, 0, missed_periods);
		avg[2] = calc_load_n(avg[2], EXP_300s, 0, missed_periods);
	पूर्ण

	/* Sample the most recent active period */
	pct = भाग_u64(समय * 100, period);
	pct *= FIXED_1;
	avg[0] = calc_load(avg[0], EXP_10s, pct);
	avg[1] = calc_load(avg[1], EXP_60s, pct);
	avg[2] = calc_load(avg[2], EXP_300s, pct);
पूर्ण

अटल व्योम collect_percpu_बार(काष्ठा psi_group *group,
				 क्रमागत psi_aggregators aggregator,
				 u32 *pchanged_states)
अणु
	u64 deltas[NR_PSI_STATES - 1] = अणु 0, पूर्ण;
	अचिन्हित दीर्घ nonidle_total = 0;
	u32 changed_states = 0;
	पूर्णांक cpu;
	पूर्णांक s;

	/*
	 * Collect the per-cpu समय buckets and average them पूर्णांकo a
	 * single समय sample that is normalized to wallघड़ी समय.
	 *
	 * For averaging, each CPU is weighted by its non-idle समय in
	 * the sampling period. This eliminates artअगरacts from uneven
	 * loading, or even entirely idle CPUs.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		u32 बार[NR_PSI_STATES];
		u32 nonidle;
		u32 cpu_changed_states;

		get_recent_बार(group, cpu, aggregator, बार,
				&cpu_changed_states);
		changed_states |= cpu_changed_states;

		nonidle = nsecs_to_jअगरfies(बार[PSI_NONIDLE]);
		nonidle_total += nonidle;

		क्रम (s = 0; s < PSI_NONIDLE; s++)
			deltas[s] += (u64)बार[s] * nonidle;
	पूर्ण

	/*
	 * Integrate the sample पूर्णांकo the running statistics that are
	 * reported to userspace: the cumulative stall बार and the
	 * decaying averages.
	 *
	 * Pressure percentages are sampled at PSI_FREQ. We might be
	 * called more often when the user polls more frequently than
	 * that; we might be called less often when there is no task
	 * activity, thus no data, and घड़ी ticks are sporadic. The
	 * below handles both.
	 */

	/* total= */
	क्रम (s = 0; s < NR_PSI_STATES - 1; s++)
		group->total[aggregator][s] +=
				भाग_u64(deltas[s], max(nonidle_total, 1UL));

	अगर (pchanged_states)
		*pchanged_states = changed_states;
पूर्ण

अटल u64 update_averages(काष्ठा psi_group *group, u64 now)
अणु
	अचिन्हित दीर्घ missed_periods = 0;
	u64 expires, period;
	u64 avg_next_update;
	पूर्णांक s;

	/* avgX= */
	expires = group->avg_next_update;
	अगर (now - expires >= psi_period)
		missed_periods = भाग_u64(now - expires, psi_period);

	/*
	 * The periodic घड़ी tick can get delayed क्रम various
	 * reasons, especially on loaded प्रणालीs. To aव्योम घड़ी
	 * drअगरt, we schedule the घड़ी in fixed psi_period पूर्णांकervals.
	 * But the deltas we sample out of the per-cpu buckets above
	 * are based on the actual समय elapsing between घड़ी ticks.
	 */
	avg_next_update = expires + ((1 + missed_periods) * psi_period);
	period = now - (group->avg_last_update + (missed_periods * psi_period));
	group->avg_last_update = now;

	क्रम (s = 0; s < NR_PSI_STATES - 1; s++) अणु
		u32 sample;

		sample = group->total[PSI_AVGS][s] - group->avg_total[s];
		/*
		 * Due to the lockless sampling of the समय buckets,
		 * recorded समय deltas can slip पूर्णांकo the next period,
		 * which under full pressure can result in samples in
		 * excess of the period length.
		 *
		 * We करोn't want to report non-sensical pressures in
		 * excess of 100%, nor करो we want to drop such events
		 * on the न्यूनमान. Instead we punt any overage पूर्णांकo the
		 * future until pressure subsides. By करोing this we
		 * करोn't underreport the occurring pressure curve, we
		 * just report it delayed by one period length.
		 *
		 * The error isn't cumulative. As soon as another
		 * delta slips from a period P to P+1, by definition
		 * it मुक्तs up its समय T in P.
		 */
		अगर (sample > period)
			sample = period;
		group->avg_total[s] += sample;
		calc_avgs(group->avg[s], missed_periods, sample, period);
	पूर्ण

	वापस avg_next_update;
पूर्ण

अटल व्योम psi_avgs_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork;
	काष्ठा psi_group *group;
	u32 changed_states;
	bool nonidle;
	u64 now;

	dwork = to_delayed_work(work);
	group = container_of(dwork, काष्ठा psi_group, avgs_work);

	mutex_lock(&group->avgs_lock);

	now = sched_घड़ी();

	collect_percpu_बार(group, PSI_AVGS, &changed_states);
	nonidle = changed_states & (1 << PSI_NONIDLE);
	/*
	 * If there is task activity, periodically fold the per-cpu
	 * बार and feed samples पूर्णांकo the running averages. If things
	 * are idle and there is no data to process, stop the घड़ी.
	 * Once restarted, we'll catch up the running averages in one
	 * go - see calc_avgs() and missed_periods.
	 */
	अगर (now >= group->avg_next_update)
		group->avg_next_update = update_averages(group, now);

	अगर (nonidle) अणु
		schedule_delayed_work(dwork, nsecs_to_jअगरfies(
				group->avg_next_update - now) + 1);
	पूर्ण

	mutex_unlock(&group->avgs_lock);
पूर्ण

/* Trigger tracking winकरोw manipulations */
अटल व्योम winकरोw_reset(काष्ठा psi_winकरोw *win, u64 now, u64 value,
			 u64 prev_growth)
अणु
	win->start_समय = now;
	win->start_value = value;
	win->prev_growth = prev_growth;
पूर्ण

/*
 * PSI growth tracking winकरोw update and growth calculation routine.
 *
 * This approximates a sliding tracking winकरोw by पूर्णांकerpolating
 * partially elapsed winकरोws using historical growth data from the
 * previous पूर्णांकervals. This minimizes memory requirements (by not storing
 * all the पूर्णांकermediate values in the previous winकरोw) and simplअगरies
 * the calculations. It works well because PSI संकेत changes only in
 * positive direction and over relatively small winकरोw sizes the growth
 * is बंद to linear.
 */
अटल u64 winकरोw_update(काष्ठा psi_winकरोw *win, u64 now, u64 value)
अणु
	u64 elapsed;
	u64 growth;

	elapsed = now - win->start_समय;
	growth = value - win->start_value;
	/*
	 * After each tracking winकरोw passes win->start_value and
	 * win->start_समय get reset and win->prev_growth stores
	 * the average per-winकरोw growth of the previous winकरोw.
	 * win->prev_growth is then used to पूर्णांकerpolate additional
	 * growth from the previous winकरोw assuming it was linear.
	 */
	अगर (elapsed > win->size)
		winकरोw_reset(win, now, value, growth);
	अन्यथा अणु
		u32 reमुख्यing;

		reमुख्यing = win->size - elapsed;
		growth += भाग64_u64(win->prev_growth * reमुख्यing, win->size);
	पूर्ण

	वापस growth;
पूर्ण

अटल व्योम init_triggers(काष्ठा psi_group *group, u64 now)
अणु
	काष्ठा psi_trigger *t;

	list_क्रम_each_entry(t, &group->triggers, node)
		winकरोw_reset(&t->win, now,
				group->total[PSI_POLL][t->state], 0);
	स_नकल(group->polling_total, group->total[PSI_POLL],
		   माप(group->polling_total));
	group->polling_next_update = now + group->poll_min_period;
पूर्ण

अटल u64 update_triggers(काष्ठा psi_group *group, u64 now)
अणु
	काष्ठा psi_trigger *t;
	bool new_stall = false;
	u64 *total = group->total[PSI_POLL];

	/*
	 * On subsequent updates, calculate growth deltas and let
	 * watchers know when their specअगरied thresholds are exceeded.
	 */
	list_क्रम_each_entry(t, &group->triggers, node) अणु
		u64 growth;

		/* Check क्रम stall activity */
		अगर (group->polling_total[t->state] == total[t->state])
			जारी;

		/*
		 * Multiple triggers might be looking at the same state,
		 * remember to update group->polling_total[] once we've
		 * been through all of them. Also remember to extend the
		 * polling समय अगर we see new stall activity.
		 */
		new_stall = true;

		/* Calculate growth since last update */
		growth = winकरोw_update(&t->win, now, total[t->state]);
		अगर (growth < t->threshold)
			जारी;

		/* Limit event संकेतing to once per winकरोw */
		अगर (now < t->last_event_समय + t->win.size)
			जारी;

		/* Generate an event */
		अगर (cmpxchg(&t->event, 0, 1) == 0)
			wake_up_पूर्णांकerruptible(&t->event_रुको);
		t->last_event_समय = now;
	पूर्ण

	अगर (new_stall)
		स_नकल(group->polling_total, total,
				माप(group->polling_total));

	वापस now + group->poll_min_period;
पूर्ण

/* Schedule polling अगर it's not alपढ़ोy scheduled. */
अटल व्योम psi_schedule_poll_work(काष्ठा psi_group *group, अचिन्हित दीर्घ delay)
अणु
	काष्ठा task_काष्ठा *task;

	/*
	 * Do not reschedule अगर alपढ़ोy scheduled.
	 * Possible race with a समयr scheduled after this check but beक्रमe
	 * mod_समयr below can be tolerated because group->polling_next_update
	 * will keep updates on schedule.
	 */
	अगर (समयr_pending(&group->poll_समयr))
		वापस;

	rcu_पढ़ो_lock();

	task = rcu_dereference(group->poll_task);
	/*
	 * kworker might be शून्य in हाल psi_trigger_destroy races with
	 * psi_task_change (hotpath) which can't use locks
	 */
	अगर (likely(task))
		mod_समयr(&group->poll_समयr, jअगरfies + delay);

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम psi_poll_work(काष्ठा psi_group *group)
अणु
	u32 changed_states;
	u64 now;

	mutex_lock(&group->trigger_lock);

	now = sched_घड़ी();

	collect_percpu_बार(group, PSI_POLL, &changed_states);

	अगर (changed_states & group->poll_states) अणु
		/* Initialize trigger winकरोws when entering polling mode */
		अगर (now > group->polling_until)
			init_triggers(group, now);

		/*
		 * Keep the monitor active क्रम at least the duration of the
		 * minimum tracking winकरोw as दीर्घ as monitor states are
		 * changing.
		 */
		group->polling_until = now +
			group->poll_min_period * UPDATES_PER_WINDOW;
	पूर्ण

	अगर (now > group->polling_until) अणु
		group->polling_next_update = ULदीर्घ_उच्च;
		जाओ out;
	पूर्ण

	अगर (now >= group->polling_next_update)
		group->polling_next_update = update_triggers(group, now);

	psi_schedule_poll_work(group,
		nsecs_to_jअगरfies(group->polling_next_update - now) + 1);

out:
	mutex_unlock(&group->trigger_lock);
पूर्ण

अटल पूर्णांक psi_poll_worker(व्योम *data)
अणु
	काष्ठा psi_group *group = (काष्ठा psi_group *)data;

	sched_set_fअगरo_low(current);

	जबतक (true) अणु
		रुको_event_पूर्णांकerruptible(group->poll_रुको,
				atomic_cmpxchg(&group->poll_wakeup, 1, 0) ||
				kthपढ़ो_should_stop());
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		psi_poll_work(group);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम poll_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा psi_group *group = from_समयr(group, t, poll_समयr);

	atomic_set(&group->poll_wakeup, 1);
	wake_up_पूर्णांकerruptible(&group->poll_रुको);
पूर्ण

अटल व्योम record_बार(काष्ठा psi_group_cpu *groupc, u64 now)
अणु
	u32 delta;

	delta = now - groupc->state_start;
	groupc->state_start = now;

	अगर (groupc->state_mask & (1 << PSI_IO_SOME)) अणु
		groupc->बार[PSI_IO_SOME] += delta;
		अगर (groupc->state_mask & (1 << PSI_IO_FULL))
			groupc->बार[PSI_IO_FULL] += delta;
	पूर्ण

	अगर (groupc->state_mask & (1 << PSI_MEM_SOME)) अणु
		groupc->बार[PSI_MEM_SOME] += delta;
		अगर (groupc->state_mask & (1 << PSI_MEM_FULL))
			groupc->बार[PSI_MEM_FULL] += delta;
	पूर्ण

	अगर (groupc->state_mask & (1 << PSI_CPU_SOME)) अणु
		groupc->बार[PSI_CPU_SOME] += delta;
		अगर (groupc->state_mask & (1 << PSI_CPU_FULL))
			groupc->बार[PSI_CPU_FULL] += delta;
	पूर्ण

	अगर (groupc->state_mask & (1 << PSI_NONIDLE))
		groupc->बार[PSI_NONIDLE] += delta;
पूर्ण

अटल व्योम psi_group_change(काष्ठा psi_group *group, पूर्णांक cpu,
			     अचिन्हित पूर्णांक clear, अचिन्हित पूर्णांक set, u64 now,
			     bool wake_घड़ी)
अणु
	काष्ठा psi_group_cpu *groupc;
	u32 state_mask = 0;
	अचिन्हित पूर्णांक t, m;
	क्रमागत psi_states s;

	groupc = per_cpu_ptr(group->pcpu, cpu);

	/*
	 * First we assess the aggregate resource states this CPU's
	 * tasks have been in since the last change, and account any
	 * SOME and FULL समय these may have resulted in.
	 *
	 * Then we update the task counts according to the state
	 * change requested through the @clear and @set bits.
	 */
	ग_लिखो_seqcount_begin(&groupc->seq);

	record_बार(groupc, now);

	क्रम (t = 0, m = clear; m; m &= ~(1 << t), t++) अणु
		अगर (!(m & (1 << t)))
			जारी;
		अगर (groupc->tasks[t]) अणु
			groupc->tasks[t]--;
		पूर्ण अन्यथा अगर (!psi_bug) अणु
			prपूर्णांकk_deferred(KERN_ERR "psi: task underflow! cpu=%d t=%d tasks=[%u %u %u %u] clear=%x set=%x\n",
					cpu, t, groupc->tasks[0],
					groupc->tasks[1], groupc->tasks[2],
					groupc->tasks[3], clear, set);
			psi_bug = 1;
		पूर्ण
	पूर्ण

	क्रम (t = 0; set; set &= ~(1 << t), t++)
		अगर (set & (1 << t))
			groupc->tasks[t]++;

	/* Calculate state mask representing active states */
	क्रम (s = 0; s < NR_PSI_STATES; s++) अणु
		अगर (test_state(groupc->tasks, s))
			state_mask |= (1 << s);
	पूर्ण

	/*
	 * Since we care about lost potential, a memstall is FULL
	 * when there are no other working tasks, but also when
	 * the CPU is actively reclaiming and nothing productive
	 * could run even अगर it were runnable. So when the current
	 * task in a cgroup is in_memstall, the corresponding groupc
	 * on that cpu is in PSI_MEM_FULL state.
	 */
	अगर (unlikely(groupc->tasks[NR_ONCPU] && cpu_curr(cpu)->in_memstall))
		state_mask |= (1 << PSI_MEM_FULL);

	groupc->state_mask = state_mask;

	ग_लिखो_seqcount_end(&groupc->seq);

	अगर (state_mask & group->poll_states)
		psi_schedule_poll_work(group, 1);

	अगर (wake_घड़ी && !delayed_work_pending(&group->avgs_work))
		schedule_delayed_work(&group->avgs_work, PSI_FREQ);
पूर्ण

अटल काष्ठा psi_group *iterate_groups(काष्ठा task_काष्ठा *task, व्योम **iter)
अणु
#अगर_घोषित CONFIG_CGROUPS
	काष्ठा cgroup *cgroup = शून्य;

	अगर (!*iter)
		cgroup = task->cgroups->dfl_cgrp;
	अन्यथा अगर (*iter == &psi_प्रणाली)
		वापस शून्य;
	अन्यथा
		cgroup = cgroup_parent(*iter);

	अगर (cgroup && cgroup_parent(cgroup)) अणु
		*iter = cgroup;
		वापस cgroup_psi(cgroup);
	पूर्ण
#अन्यथा
	अगर (*iter)
		वापस शून्य;
#पूर्ण_अगर
	*iter = &psi_प्रणाली;
	वापस &psi_प्रणाली;
पूर्ण

अटल व्योम psi_flags_change(काष्ठा task_काष्ठा *task, पूर्णांक clear, पूर्णांक set)
अणु
	अगर (((task->psi_flags & set) ||
	     (task->psi_flags & clear) != clear) &&
	    !psi_bug) अणु
		prपूर्णांकk_deferred(KERN_ERR "psi: inconsistent task state! task=%d:%s cpu=%d psi_flags=%x clear=%x set=%x\n",
				task->pid, task->comm, task_cpu(task),
				task->psi_flags, clear, set);
		psi_bug = 1;
	पूर्ण

	task->psi_flags &= ~clear;
	task->psi_flags |= set;
पूर्ण

व्योम psi_task_change(काष्ठा task_काष्ठा *task, पूर्णांक clear, पूर्णांक set)
अणु
	पूर्णांक cpu = task_cpu(task);
	काष्ठा psi_group *group;
	bool wake_घड़ी = true;
	व्योम *iter = शून्य;
	u64 now;

	अगर (!task->pid)
		वापस;

	psi_flags_change(task, clear, set);

	now = cpu_घड़ी(cpu);
	/*
	 * Periodic aggregation shuts off अगर there is a period of no
	 * task changes, so we wake it back up अगर necessary. However,
	 * करोn't करो this अगर the task change is the aggregation worker
	 * itself going to sleep, or we'll ping-pong क्रमever.
	 */
	अगर (unlikely((clear & TSK_RUNNING) &&
		     (task->flags & PF_WQ_WORKER) &&
		     wq_worker_last_func(task) == psi_avgs_work))
		wake_घड़ी = false;

	जबतक ((group = iterate_groups(task, &iter)))
		psi_group_change(group, cpu, clear, set, now, wake_घड़ी);
पूर्ण

व्योम psi_task_चयन(काष्ठा task_काष्ठा *prev, काष्ठा task_काष्ठा *next,
		     bool sleep)
अणु
	काष्ठा psi_group *group, *common = शून्य;
	पूर्णांक cpu = task_cpu(prev);
	व्योम *iter;
	u64 now = cpu_घड़ी(cpu);

	अगर (next->pid) अणु
		bool identical_state;

		psi_flags_change(next, 0, TSK_ONCPU);
		/*
		 * When चयनing between tasks that have an identical
		 * runसमय state, the cgroup that contains both tasks
		 * runसमय state, the cgroup that contains both tasks
		 * we reach the first common ancestor. Iterate @next's
		 * ancestors only until we encounter @prev's ONCPU.
		 */
		identical_state = prev->psi_flags == next->psi_flags;
		iter = शून्य;
		जबतक ((group = iterate_groups(next, &iter))) अणु
			अगर (identical_state &&
			    per_cpu_ptr(group->pcpu, cpu)->tasks[NR_ONCPU]) अणु
				common = group;
				अवरोध;
			पूर्ण

			psi_group_change(group, cpu, 0, TSK_ONCPU, now, true);
		पूर्ण
	पूर्ण

	अगर (prev->pid) अणु
		पूर्णांक clear = TSK_ONCPU, set = 0;

		/*
		 * When we're going to sleep, psi_dequeue() lets us handle
		 * TSK_RUNNING and TSK_IOWAIT here, where we can combine it
		 * with TSK_ONCPU and save walking common ancestors twice.
		 */
		अगर (sleep) अणु
			clear |= TSK_RUNNING;
			अगर (prev->in_ioरुको)
				set |= TSK_IOWAIT;
		पूर्ण

		psi_flags_change(prev, clear, set);

		iter = शून्य;
		जबतक ((group = iterate_groups(prev, &iter)) && group != common)
			psi_group_change(group, cpu, clear, set, now, true);

		/*
		 * TSK_ONCPU is handled up to the common ancestor. If we're tasked
		 * with dequeuing too, finish that क्रम the rest of the hierarchy.
		 */
		अगर (sleep) अणु
			clear &= ~TSK_ONCPU;
			क्रम (; group; group = iterate_groups(prev, &iter))
				psi_group_change(group, cpu, clear, set, now, true);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * psi_memstall_enter - mark the beginning of a memory stall section
 * @flags: flags to handle nested sections
 *
 * Marks the calling task as being stalled due to a lack of memory,
 * such as रुकोing क्रम a refault or perक्रमming reclaim.
 */
व्योम psi_memstall_enter(अचिन्हित दीर्घ *flags)
अणु
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;

	अगर (अटल_branch_likely(&psi_disabled))
		वापस;

	*flags = current->in_memstall;
	अगर (*flags)
		वापस;
	/*
	 * in_memstall setting & accounting needs to be atomic wrt
	 * changes to the task's scheduling state, otherwise we can
	 * race with CPU migration.
	 */
	rq = this_rq_lock_irq(&rf);

	current->in_memstall = 1;
	psi_task_change(current, 0, TSK_MEMSTALL);

	rq_unlock_irq(rq, &rf);
पूर्ण

/**
 * psi_memstall_leave - mark the end of an memory stall section
 * @flags: flags to handle nested memdelay sections
 *
 * Marks the calling task as no दीर्घer stalled due to lack of memory.
 */
व्योम psi_memstall_leave(अचिन्हित दीर्घ *flags)
अणु
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;

	अगर (अटल_branch_likely(&psi_disabled))
		वापस;

	अगर (*flags)
		वापस;
	/*
	 * in_memstall clearing & accounting needs to be atomic wrt
	 * changes to the task's scheduling state, otherwise we could
	 * race with CPU migration.
	 */
	rq = this_rq_lock_irq(&rf);

	current->in_memstall = 0;
	psi_task_change(current, TSK_MEMSTALL, 0);

	rq_unlock_irq(rq, &rf);
पूर्ण

#अगर_घोषित CONFIG_CGROUPS
पूर्णांक psi_cgroup_alloc(काष्ठा cgroup *cgroup)
अणु
	अगर (अटल_branch_likely(&psi_disabled))
		वापस 0;

	cgroup->psi.pcpu = alloc_percpu(काष्ठा psi_group_cpu);
	अगर (!cgroup->psi.pcpu)
		वापस -ENOMEM;
	group_init(&cgroup->psi);
	वापस 0;
पूर्ण

व्योम psi_cgroup_मुक्त(काष्ठा cgroup *cgroup)
अणु
	अगर (अटल_branch_likely(&psi_disabled))
		वापस;

	cancel_delayed_work_sync(&cgroup->psi.avgs_work);
	मुक्त_percpu(cgroup->psi.pcpu);
	/* All triggers must be हटाओd by now */
	WARN_ONCE(cgroup->psi.poll_states, "psi: trigger leak\n");
पूर्ण

/**
 * cgroup_move_task - move task to a dअगरferent cgroup
 * @task: the task
 * @to: the target css_set
 *
 * Move task to a new cgroup and safely migrate its associated stall
 * state between the dअगरferent groups.
 *
 * This function acquires the task's rq lock to lock out concurrent
 * changes to the task's scheduling state and - in हाल the task is
 * running - concurrent changes to its stall state.
 */
व्योम cgroup_move_task(काष्ठा task_काष्ठा *task, काष्ठा css_set *to)
अणु
	अचिन्हित पूर्णांक task_flags;
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;

	अगर (अटल_branch_likely(&psi_disabled)) अणु
		/*
		 * Lame to करो this here, but the scheduler cannot be locked
		 * from the outside, so we move cgroups from inside sched/.
		 */
		rcu_assign_poपूर्णांकer(task->cgroups, to);
		वापस;
	पूर्ण

	rq = task_rq_lock(task, &rf);

	/*
	 * We may race with schedule() dropping the rq lock between
	 * deactivating prev and चयनing to next. Because the psi
	 * updates from the deactivation are deferred to the चयन
	 * callback to save cgroup tree updates, the task's scheduling
	 * state here is not coherent with its psi state:
	 *
	 * schedule()                   cgroup_move_task()
	 *   rq_lock()
	 *   deactivate_task()
	 *     p->on_rq = 0
	 *     psi_dequeue() // defers TSK_RUNNING & TSK_IOWAIT updates
	 *   pick_next_task()
	 *     rq_unlock()
	 *                                rq_lock()
	 *                                psi_task_change() // old cgroup
	 *                                task->cgroups = to
	 *                                psi_task_change() // new cgroup
	 *                                rq_unlock()
	 *     rq_lock()
	 *   psi_sched_चयन() // करोes deferred updates in new cgroup
	 *
	 * Don't rely on the scheduling state. Use psi_flags instead.
	 */
	task_flags = task->psi_flags;

	अगर (task_flags)
		psi_task_change(task, task_flags, 0);

	/* See comment above */
	rcu_assign_poपूर्णांकer(task->cgroups, to);

	अगर (task_flags)
		psi_task_change(task, 0, task_flags);

	task_rq_unlock(rq, task, &rf);
पूर्ण
#पूर्ण_अगर /* CONFIG_CGROUPS */

पूर्णांक psi_show(काष्ठा seq_file *m, काष्ठा psi_group *group, क्रमागत psi_res res)
अणु
	पूर्णांक full;
	u64 now;

	अगर (अटल_branch_likely(&psi_disabled))
		वापस -EOPNOTSUPP;

	/* Update averages beक्रमe reporting them */
	mutex_lock(&group->avgs_lock);
	now = sched_घड़ी();
	collect_percpu_बार(group, PSI_AVGS, शून्य);
	अगर (now >= group->avg_next_update)
		group->avg_next_update = update_averages(group, now);
	mutex_unlock(&group->avgs_lock);

	क्रम (full = 0; full < 2; full++) अणु
		अचिन्हित दीर्घ avg[3];
		u64 total;
		पूर्णांक w;

		क्रम (w = 0; w < 3; w++)
			avg[w] = group->avg[res * 2 + full][w];
		total = भाग_u64(group->total[PSI_AVGS][res * 2 + full],
				NSEC_PER_USEC);

		seq_म_लिखो(m, "%s avg10=%lu.%02lu avg60=%lu.%02lu avg300=%lu.%02lu total=%llu\n",
			   full ? "full" : "some",
			   LOAD_INT(avg[0]), LOAD_FRAC(avg[0]),
			   LOAD_INT(avg[1]), LOAD_FRAC(avg[1]),
			   LOAD_INT(avg[2]), LOAD_FRAC(avg[2]),
			   total);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक psi_io_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस psi_show(m, &psi_प्रणाली, PSI_IO);
पूर्ण

अटल पूर्णांक psi_memory_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस psi_show(m, &psi_प्रणाली, PSI_MEM);
पूर्ण

अटल पूर्णांक psi_cpu_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस psi_show(m, &psi_प्रणाली, PSI_CPU);
पूर्ण

अटल पूर्णांक psi_खोलो(काष्ठा file *file, पूर्णांक (*psi_show)(काष्ठा seq_file *, व्योम *))
अणु
	अगर (file->f_mode & FMODE_WRITE && !capable(CAP_SYS_RESOURCE))
		वापस -EPERM;

	वापस single_खोलो(file, psi_show, शून्य);
पूर्ण

अटल पूर्णांक psi_io_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस psi_खोलो(file, psi_io_show);
पूर्ण

अटल पूर्णांक psi_memory_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस psi_खोलो(file, psi_memory_show);
पूर्ण

अटल पूर्णांक psi_cpu_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस psi_खोलो(file, psi_cpu_show);
पूर्ण

काष्ठा psi_trigger *psi_trigger_create(काष्ठा psi_group *group,
			अक्षर *buf, माप_प्रकार nbytes, क्रमागत psi_res res)
अणु
	काष्ठा psi_trigger *t;
	क्रमागत psi_states state;
	u32 threshold_us;
	u32 winकरोw_us;

	अगर (अटल_branch_likely(&psi_disabled))
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (माला_पूछो(buf, "some %u %u", &threshold_us, &winकरोw_us) == 2)
		state = PSI_IO_SOME + res * 2;
	अन्यथा अगर (माला_पूछो(buf, "full %u %u", &threshold_us, &winकरोw_us) == 2)
		state = PSI_IO_FULL + res * 2;
	अन्यथा
		वापस ERR_PTR(-EINVAL);

	अगर (state >= PSI_NONIDLE)
		वापस ERR_PTR(-EINVAL);

	अगर (winकरोw_us < WINDOW_MIN_US ||
		winकरोw_us > WINDOW_MAX_US)
		वापस ERR_PTR(-EINVAL);

	/* Check threshold */
	अगर (threshold_us == 0 || threshold_us > winकरोw_us)
		वापस ERR_PTR(-EINVAL);

	t = kदो_स्मृति(माप(*t), GFP_KERNEL);
	अगर (!t)
		वापस ERR_PTR(-ENOMEM);

	t->group = group;
	t->state = state;
	t->threshold = threshold_us * NSEC_PER_USEC;
	t->win.size = winकरोw_us * NSEC_PER_USEC;
	winकरोw_reset(&t->win, 0, 0, 0);

	t->event = 0;
	t->last_event_समय = 0;
	init_रुकोqueue_head(&t->event_रुको);
	kref_init(&t->refcount);

	mutex_lock(&group->trigger_lock);

	अगर (!rcu_access_poपूर्णांकer(group->poll_task)) अणु
		काष्ठा task_काष्ठा *task;

		task = kthपढ़ो_create(psi_poll_worker, group, "psimon");
		अगर (IS_ERR(task)) अणु
			kमुक्त(t);
			mutex_unlock(&group->trigger_lock);
			वापस ERR_CAST(task);
		पूर्ण
		atomic_set(&group->poll_wakeup, 0);
		init_रुकोqueue_head(&group->poll_रुको);
		wake_up_process(task);
		समयr_setup(&group->poll_समयr, poll_समयr_fn, 0);
		rcu_assign_poपूर्णांकer(group->poll_task, task);
	पूर्ण

	list_add(&t->node, &group->triggers);
	group->poll_min_period = min(group->poll_min_period,
		भाग_u64(t->win.size, UPDATES_PER_WINDOW));
	group->nr_triggers[t->state]++;
	group->poll_states |= (1 << t->state);

	mutex_unlock(&group->trigger_lock);

	वापस t;
पूर्ण

अटल व्योम psi_trigger_destroy(काष्ठा kref *ref)
अणु
	काष्ठा psi_trigger *t = container_of(ref, काष्ठा psi_trigger, refcount);
	काष्ठा psi_group *group = t->group;
	काष्ठा task_काष्ठा *task_to_destroy = शून्य;

	अगर (अटल_branch_likely(&psi_disabled))
		वापस;

	/*
	 * Wakeup रुकोers to stop polling. Can happen अगर cgroup is deleted
	 * from under a polling process.
	 */
	wake_up_पूर्णांकerruptible(&t->event_रुको);

	mutex_lock(&group->trigger_lock);

	अगर (!list_empty(&t->node)) अणु
		काष्ठा psi_trigger *पंचांगp;
		u64 period = ULदीर्घ_उच्च;

		list_del(&t->node);
		group->nr_triggers[t->state]--;
		अगर (!group->nr_triggers[t->state])
			group->poll_states &= ~(1 << t->state);
		/* reset min update period क्रम the reमुख्यing triggers */
		list_क्रम_each_entry(पंचांगp, &group->triggers, node)
			period = min(period, भाग_u64(पंचांगp->win.size,
					UPDATES_PER_WINDOW));
		group->poll_min_period = period;
		/* Destroy poll_task when the last trigger is destroyed */
		अगर (group->poll_states == 0) अणु
			group->polling_until = 0;
			task_to_destroy = rcu_dereference_रक्षित(
					group->poll_task,
					lockdep_is_held(&group->trigger_lock));
			rcu_assign_poपूर्णांकer(group->poll_task, शून्य);
		पूर्ण
	पूर्ण

	mutex_unlock(&group->trigger_lock);

	/*
	 * Wait क्रम both *trigger_ptr from psi_trigger_replace and
	 * poll_task RCUs to complete their पढ़ो-side critical sections
	 * beक्रमe destroying the trigger and optionally the poll_task
	 */
	synchronize_rcu();
	/*
	 * Destroy the kworker after releasing trigger_lock to prevent a
	 * deadlock जबतक रुकोing क्रम psi_poll_work to acquire trigger_lock
	 */
	अगर (task_to_destroy) अणु
		/*
		 * After the RCU grace period has expired, the worker
		 * can no दीर्घer be found through group->poll_task.
		 * But it might have been alपढ़ोy scheduled beक्रमe
		 * that - deschedule it cleanly beक्रमe destroying it.
		 */
		del_समयr_sync(&group->poll_समयr);
		kthपढ़ो_stop(task_to_destroy);
	पूर्ण
	kमुक्त(t);
पूर्ण

व्योम psi_trigger_replace(व्योम **trigger_ptr, काष्ठा psi_trigger *new)
अणु
	काष्ठा psi_trigger *old = *trigger_ptr;

	अगर (अटल_branch_likely(&psi_disabled))
		वापस;

	rcu_assign_poपूर्णांकer(*trigger_ptr, new);
	अगर (old)
		kref_put(&old->refcount, psi_trigger_destroy);
पूर्ण

__poll_t psi_trigger_poll(व्योम **trigger_ptr,
				काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t ret = DEFAULT_POLLMASK;
	काष्ठा psi_trigger *t;

	अगर (अटल_branch_likely(&psi_disabled))
		वापस DEFAULT_POLLMASK | EPOLLERR | EPOLLPRI;

	rcu_पढ़ो_lock();

	t = rcu_dereference(*(व्योम __rcu __क्रमce **)trigger_ptr);
	अगर (!t) अणु
		rcu_पढ़ो_unlock();
		वापस DEFAULT_POLLMASK | EPOLLERR | EPOLLPRI;
	पूर्ण
	kref_get(&t->refcount);

	rcu_पढ़ो_unlock();

	poll_रुको(file, &t->event_रुको, रुको);

	अगर (cmpxchg(&t->event, 1, 0) == 1)
		ret |= EPOLLPRI;

	kref_put(&t->refcount, psi_trigger_destroy);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार psi_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			 माप_प्रकार nbytes, क्रमागत psi_res res)
अणु
	अक्षर buf[32];
	माप_प्रकार buf_size;
	काष्ठा seq_file *seq;
	काष्ठा psi_trigger *new;

	अगर (अटल_branch_likely(&psi_disabled))
		वापस -EOPNOTSUPP;

	अगर (!nbytes)
		वापस -EINVAL;

	buf_size = min(nbytes, माप(buf));
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;

	buf[buf_size - 1] = '\0';

	new = psi_trigger_create(&psi_प्रणाली, buf, nbytes, res);
	अगर (IS_ERR(new))
		वापस PTR_ERR(new);

	seq = file->निजी_data;
	/* Take seq->lock to protect seq->निजी from concurrent ग_लिखोs */
	mutex_lock(&seq->lock);
	psi_trigger_replace(&seq->निजी, new);
	mutex_unlock(&seq->lock);

	वापस nbytes;
पूर्ण

अटल sमाप_प्रकार psi_io_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			    माप_प्रकार nbytes, loff_t *ppos)
अणु
	वापस psi_ग_लिखो(file, user_buf, nbytes, PSI_IO);
पूर्ण

अटल sमाप_प्रकार psi_memory_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				माप_प्रकार nbytes, loff_t *ppos)
अणु
	वापस psi_ग_लिखो(file, user_buf, nbytes, PSI_MEM);
पूर्ण

अटल sमाप_प्रकार psi_cpu_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			     माप_प्रकार nbytes, loff_t *ppos)
अणु
	वापस psi_ग_लिखो(file, user_buf, nbytes, PSI_CPU);
पूर्ण

अटल __poll_t psi_fop_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा seq_file *seq = file->निजी_data;

	वापस psi_trigger_poll(&seq->निजी, file, रुको);
पूर्ण

अटल पूर्णांक psi_fop_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = file->निजी_data;

	psi_trigger_replace(&seq->निजी, शून्य);
	वापस single_release(inode, file);
पूर्ण

अटल स्थिर काष्ठा proc_ops psi_io_proc_ops = अणु
	.proc_खोलो	= psi_io_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_ग_लिखो	= psi_io_ग_लिखो,
	.proc_poll	= psi_fop_poll,
	.proc_release	= psi_fop_release,
पूर्ण;

अटल स्थिर काष्ठा proc_ops psi_memory_proc_ops = अणु
	.proc_खोलो	= psi_memory_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_ग_लिखो	= psi_memory_ग_लिखो,
	.proc_poll	= psi_fop_poll,
	.proc_release	= psi_fop_release,
पूर्ण;

अटल स्थिर काष्ठा proc_ops psi_cpu_proc_ops = अणु
	.proc_खोलो	= psi_cpu_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_ग_लिखो	= psi_cpu_ग_लिखो,
	.proc_poll	= psi_fop_poll,
	.proc_release	= psi_fop_release,
पूर्ण;

अटल पूर्णांक __init psi_proc_init(व्योम)
अणु
	अगर (psi_enable) अणु
		proc_सूची_गढ़ो("pressure", शून्य);
		proc_create("pressure/io", 0666, शून्य, &psi_io_proc_ops);
		proc_create("pressure/memory", 0666, शून्य, &psi_memory_proc_ops);
		proc_create("pressure/cpu", 0666, शून्य, &psi_cpu_proc_ops);
	पूर्ण
	वापस 0;
पूर्ण
module_init(psi_proc_init);
