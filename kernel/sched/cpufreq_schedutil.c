<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * CPUFreq governor based on scheduler-provided CPU utilization data.
 *
 * Copyright (C) 2016, Intel Corporation
 * Author: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "sched.h"

#समावेश <linux/sched/cpufreq.h>
#समावेश <trace/events/घातer.h>

#घोषणा IOWAIT_BOOST_MIN	(SCHED_CAPACITY_SCALE / 8)

काष्ठा sugov_tunables अणु
	काष्ठा gov_attr_set	attr_set;
	अचिन्हित पूर्णांक		rate_limit_us;
पूर्ण;

काष्ठा sugov_policy अणु
	काष्ठा cpufreq_policy	*policy;

	काष्ठा sugov_tunables	*tunables;
	काष्ठा list_head	tunables_hook;

	raw_spinlock_t		update_lock;
	u64			last_freq_update_समय;
	s64			freq_update_delay_ns;
	अचिन्हित पूर्णांक		next_freq;
	अचिन्हित पूर्णांक		cached_raw_freq;

	/* The next fields are only needed अगर fast चयन cannot be used: */
	काष्ठा			irq_work irq_work;
	काष्ठा			kthपढ़ो_work work;
	काष्ठा			mutex work_lock;
	काष्ठा			kthपढ़ो_worker worker;
	काष्ठा task_काष्ठा	*thपढ़ो;
	bool			work_in_progress;

	bool			limits_changed;
	bool			need_freq_update;
पूर्ण;

काष्ठा sugov_cpu अणु
	काष्ठा update_util_data	update_util;
	काष्ठा sugov_policy	*sg_policy;
	अचिन्हित पूर्णांक		cpu;

	bool			ioरुको_boost_pending;
	अचिन्हित पूर्णांक		ioरुको_boost;
	u64			last_update;

	अचिन्हित दीर्घ		util;
	अचिन्हित दीर्घ		bw_dl;
	अचिन्हित दीर्घ		max;

	/* The field below is क्रम single-CPU policies only: */
#अगर_घोषित CONFIG_NO_HZ_COMMON
	अचिन्हित दीर्घ		saved_idle_calls;
#पूर्ण_अगर
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा sugov_cpu, sugov_cpu);

/************************ Governor पूर्णांकernals ***********************/

अटल bool sugov_should_update_freq(काष्ठा sugov_policy *sg_policy, u64 समय)
अणु
	s64 delta_ns;

	/*
	 * Since cpufreq_update_util() is called with rq->lock held क्रम
	 * the @target_cpu, our per-CPU data is fully serialized.
	 *
	 * However, drivers cannot in general deal with cross-CPU
	 * requests, so जबतक get_next_freq() will work, our
	 * sugov_update_commit() call may not क्रम the fast चयनing platक्रमms.
	 *
	 * Hence stop here क्रम remote requests अगर they aren't supported
	 * by the hardware, as calculating the frequency is poपूर्णांकless अगर
	 * we cannot in fact act on it.
	 *
	 * This is needed on the slow चयनing platक्रमms too to prevent CPUs
	 * going offline from leaving stale IRQ work items behind.
	 */
	अगर (!cpufreq_this_cpu_can_update(sg_policy->policy))
		वापस false;

	अगर (unlikely(sg_policy->limits_changed)) अणु
		sg_policy->limits_changed = false;
		sg_policy->need_freq_update = true;
		वापस true;
	पूर्ण

	delta_ns = समय - sg_policy->last_freq_update_समय;

	वापस delta_ns >= sg_policy->freq_update_delay_ns;
पूर्ण

अटल bool sugov_update_next_freq(काष्ठा sugov_policy *sg_policy, u64 समय,
				   अचिन्हित पूर्णांक next_freq)
अणु
	अगर (sg_policy->need_freq_update)
		sg_policy->need_freq_update = cpufreq_driver_test_flags(CPUFREQ_NEED_UPDATE_LIMITS);
	अन्यथा अगर (sg_policy->next_freq == next_freq)
		वापस false;

	sg_policy->next_freq = next_freq;
	sg_policy->last_freq_update_समय = समय;

	वापस true;
पूर्ण

अटल व्योम sugov_deferred_update(काष्ठा sugov_policy *sg_policy)
अणु
	अगर (!sg_policy->work_in_progress) अणु
		sg_policy->work_in_progress = true;
		irq_work_queue(&sg_policy->irq_work);
	पूर्ण
पूर्ण

/**
 * get_next_freq - Compute a new frequency क्रम a given cpufreq policy.
 * @sg_policy: schedutil policy object to compute the new frequency क्रम.
 * @util: Current CPU utilization.
 * @max: CPU capacity.
 *
 * If the utilization is frequency-invariant, choose the new frequency to be
 * proportional to it, that is
 *
 * next_freq = C * max_freq * util / max
 *
 * Otherwise, approximate the would-be frequency-invariant utilization by
 * util_raw * (curr_freq / max_freq) which leads to
 *
 * next_freq = C * curr_freq * util_raw / max
 *
 * Take C = 1.25 क्रम the frequency tipping poपूर्णांक at (util / max) = 0.8.
 *
 * The lowest driver-supported frequency which is equal or greater than the raw
 * next_freq (as calculated above) is वापसed, subject to policy min/max and
 * cpufreq driver limitations.
 */
अटल अचिन्हित पूर्णांक get_next_freq(काष्ठा sugov_policy *sg_policy,
				  अचिन्हित दीर्घ util, अचिन्हित दीर्घ max)
अणु
	काष्ठा cpufreq_policy *policy = sg_policy->policy;
	अचिन्हित पूर्णांक freq = arch_scale_freq_invariant() ?
				policy->cpuinfo.max_freq : policy->cur;

	freq = map_util_freq(util, freq, max);

	अगर (freq == sg_policy->cached_raw_freq && !sg_policy->need_freq_update)
		वापस sg_policy->next_freq;

	sg_policy->cached_raw_freq = freq;
	वापस cpufreq_driver_resolve_freq(policy, freq);
पूर्ण

अटल व्योम sugov_get_util(काष्ठा sugov_cpu *sg_cpu)
अणु
	काष्ठा rq *rq = cpu_rq(sg_cpu->cpu);
	अचिन्हित दीर्घ max = arch_scale_cpu_capacity(sg_cpu->cpu);

	sg_cpu->max = max;
	sg_cpu->bw_dl = cpu_bw_dl(rq);
	sg_cpu->util = effective_cpu_util(sg_cpu->cpu, cpu_util_cfs(rq), max,
					  FREQUENCY_UTIL, शून्य);
पूर्ण

/**
 * sugov_ioरुको_reset() - Reset the IO boost status of a CPU.
 * @sg_cpu: the sugov data क्रम the CPU to boost
 * @समय: the update समय from the caller
 * @set_ioरुको_boost: true अगर an IO boost has been requested
 *
 * The IO रुको boost of a task is disabled after a tick since the last update
 * of a CPU. If a new IO रुको boost is requested after more then a tick, then
 * we enable the boost starting from IOWAIT_BOOST_MIN, which improves energy
 * efficiency by ignoring sporadic wakeups from IO.
 */
अटल bool sugov_ioरुको_reset(काष्ठा sugov_cpu *sg_cpu, u64 समय,
			       bool set_ioरुको_boost)
अणु
	s64 delta_ns = समय - sg_cpu->last_update;

	/* Reset boost only अगर a tick has elapsed since last request */
	अगर (delta_ns <= TICK_NSEC)
		वापस false;

	sg_cpu->ioरुको_boost = set_ioरुको_boost ? IOWAIT_BOOST_MIN : 0;
	sg_cpu->ioरुको_boost_pending = set_ioरुको_boost;

	वापस true;
पूर्ण

/**
 * sugov_ioरुको_boost() - Updates the IO boost status of a CPU.
 * @sg_cpu: the sugov data क्रम the CPU to boost
 * @समय: the update समय from the caller
 * @flags: SCHED_CPUFREQ_IOWAIT अगर the task is waking up after an IO रुको
 *
 * Each समय a task wakes up after an IO operation, the CPU utilization can be
 * boosted to a certain utilization which द्विगुनs at each "frequent and
 * successive" wakeup from IO, ranging from IOWAIT_BOOST_MIN to the utilization
 * of the maximum OPP.
 *
 * To keep करोubling, an IO boost has to be requested at least once per tick,
 * otherwise we restart from the utilization of the minimum OPP.
 */
अटल व्योम sugov_ioरुको_boost(काष्ठा sugov_cpu *sg_cpu, u64 समय,
			       अचिन्हित पूर्णांक flags)
अणु
	bool set_ioरुको_boost = flags & SCHED_CPUFREQ_IOWAIT;

	/* Reset boost अगर the CPU appears to have been idle enough */
	अगर (sg_cpu->ioरुको_boost &&
	    sugov_ioरुको_reset(sg_cpu, समय, set_ioरुको_boost))
		वापस;

	/* Boost only tasks waking up after IO */
	अगर (!set_ioरुको_boost)
		वापस;

	/* Ensure boost द्विगुनs only one समय at each request */
	अगर (sg_cpu->ioरुको_boost_pending)
		वापस;
	sg_cpu->ioरुको_boost_pending = true;

	/* Double the boost at each request */
	अगर (sg_cpu->ioरुको_boost) अणु
		sg_cpu->ioरुको_boost =
			min_t(अचिन्हित पूर्णांक, sg_cpu->ioरुको_boost << 1, SCHED_CAPACITY_SCALE);
		वापस;
	पूर्ण

	/* First wakeup after IO: start with minimum boost */
	sg_cpu->ioरुको_boost = IOWAIT_BOOST_MIN;
पूर्ण

/**
 * sugov_ioरुको_apply() - Apply the IO boost to a CPU.
 * @sg_cpu: the sugov data क्रम the cpu to boost
 * @समय: the update समय from the caller
 *
 * A CPU running a task which woken up after an IO operation can have its
 * utilization boosted to speed up the completion of those IO operations.
 * The IO boost value is increased each समय a task wakes up from IO, in
 * sugov_ioरुको_apply(), and it's instead decreased by this function,
 * each समय an increase has not been requested (!ioरुको_boost_pending).
 *
 * A CPU which also appears to have been idle क्रम at least one tick has also
 * its IO boost utilization reset.
 *
 * This mechanism is deचिन्हित to boost high frequently IO रुकोing tasks, जबतक
 * being more conservative on tasks which करोes sporadic IO operations.
 */
अटल व्योम sugov_ioरुको_apply(काष्ठा sugov_cpu *sg_cpu, u64 समय)
अणु
	अचिन्हित दीर्घ boost;

	/* No boost currently required */
	अगर (!sg_cpu->ioरुको_boost)
		वापस;

	/* Reset boost अगर the CPU appears to have been idle enough */
	अगर (sugov_ioरुको_reset(sg_cpu, समय, false))
		वापस;

	अगर (!sg_cpu->ioरुको_boost_pending) अणु
		/*
		 * No boost pending; reduce the boost value.
		 */
		sg_cpu->ioरुको_boost >>= 1;
		अगर (sg_cpu->ioरुको_boost < IOWAIT_BOOST_MIN) अणु
			sg_cpu->ioरुको_boost = 0;
			वापस;
		पूर्ण
	पूर्ण

	sg_cpu->ioरुको_boost_pending = false;

	/*
	 * sg_cpu->util is alपढ़ोy in capacity scale; convert ioरुको_boost
	 * पूर्णांकo the same scale so we can compare.
	 */
	boost = (sg_cpu->ioरुको_boost * sg_cpu->max) >> SCHED_CAPACITY_SHIFT;
	अगर (sg_cpu->util < boost)
		sg_cpu->util = boost;
पूर्ण

#अगर_घोषित CONFIG_NO_HZ_COMMON
अटल bool sugov_cpu_is_busy(काष्ठा sugov_cpu *sg_cpu)
अणु
	अचिन्हित दीर्घ idle_calls = tick_nohz_get_idle_calls_cpu(sg_cpu->cpu);
	bool ret = idle_calls == sg_cpu->saved_idle_calls;

	sg_cpu->saved_idle_calls = idle_calls;
	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत bool sugov_cpu_is_busy(काष्ठा sugov_cpu *sg_cpu) अणु वापस false; पूर्ण
#पूर्ण_अगर /* CONFIG_NO_HZ_COMMON */

/*
 * Make sugov_should_update_freq() ignore the rate limit when DL
 * has increased the utilization.
 */
अटल अंतरभूत व्योम ignore_dl_rate_limit(काष्ठा sugov_cpu *sg_cpu)
अणु
	अगर (cpu_bw_dl(cpu_rq(sg_cpu->cpu)) > sg_cpu->bw_dl)
		sg_cpu->sg_policy->limits_changed = true;
पूर्ण

अटल अंतरभूत bool sugov_update_single_common(काष्ठा sugov_cpu *sg_cpu,
					      u64 समय, अचिन्हित पूर्णांक flags)
अणु
	sugov_ioरुको_boost(sg_cpu, समय, flags);
	sg_cpu->last_update = समय;

	ignore_dl_rate_limit(sg_cpu);

	अगर (!sugov_should_update_freq(sg_cpu->sg_policy, समय))
		वापस false;

	sugov_get_util(sg_cpu);
	sugov_ioरुको_apply(sg_cpu, समय);

	वापस true;
पूर्ण

अटल व्योम sugov_update_single_freq(काष्ठा update_util_data *hook, u64 समय,
				     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sugov_cpu *sg_cpu = container_of(hook, काष्ठा sugov_cpu, update_util);
	काष्ठा sugov_policy *sg_policy = sg_cpu->sg_policy;
	अचिन्हित पूर्णांक cached_freq = sg_policy->cached_raw_freq;
	अचिन्हित पूर्णांक next_f;

	अगर (!sugov_update_single_common(sg_cpu, समय, flags))
		वापस;

	next_f = get_next_freq(sg_policy, sg_cpu->util, sg_cpu->max);
	/*
	 * Do not reduce the frequency अगर the CPU has not been idle
	 * recently, as the reduction is likely to be premature then.
	 */
	अगर (sugov_cpu_is_busy(sg_cpu) && next_f < sg_policy->next_freq) अणु
		next_f = sg_policy->next_freq;

		/* Restore cached freq as next_freq has changed */
		sg_policy->cached_raw_freq = cached_freq;
	पूर्ण

	अगर (!sugov_update_next_freq(sg_policy, समय, next_f))
		वापस;

	/*
	 * This code runs under rq->lock क्रम the target CPU, so it won't run
	 * concurrently on two dअगरferent CPUs क्रम the same target and it is not
	 * necessary to acquire the lock in the fast चयन हाल.
	 */
	अगर (sg_policy->policy->fast_चयन_enabled) अणु
		cpufreq_driver_fast_चयन(sg_policy->policy, next_f);
	पूर्ण अन्यथा अणु
		raw_spin_lock(&sg_policy->update_lock);
		sugov_deferred_update(sg_policy);
		raw_spin_unlock(&sg_policy->update_lock);
	पूर्ण
पूर्ण

अटल व्योम sugov_update_single_perf(काष्ठा update_util_data *hook, u64 समय,
				     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sugov_cpu *sg_cpu = container_of(hook, काष्ठा sugov_cpu, update_util);
	अचिन्हित दीर्घ prev_util = sg_cpu->util;

	/*
	 * Fall back to the "frequency" path अगर frequency invariance is not
	 * supported, because the direct mapping between the utilization and
	 * the perक्रमmance levels depends on the frequency invariance.
	 */
	अगर (!arch_scale_freq_invariant()) अणु
		sugov_update_single_freq(hook, समय, flags);
		वापस;
	पूर्ण

	अगर (!sugov_update_single_common(sg_cpu, समय, flags))
		वापस;

	/*
	 * Do not reduce the target perक्रमmance level अगर the CPU has not been
	 * idle recently, as the reduction is likely to be premature then.
	 */
	अगर (sugov_cpu_is_busy(sg_cpu) && sg_cpu->util < prev_util)
		sg_cpu->util = prev_util;

	cpufreq_driver_adjust_perf(sg_cpu->cpu, map_util_perf(sg_cpu->bw_dl),
				   map_util_perf(sg_cpu->util), sg_cpu->max);

	sg_cpu->sg_policy->last_freq_update_समय = समय;
पूर्ण

अटल अचिन्हित पूर्णांक sugov_next_freq_shared(काष्ठा sugov_cpu *sg_cpu, u64 समय)
अणु
	काष्ठा sugov_policy *sg_policy = sg_cpu->sg_policy;
	काष्ठा cpufreq_policy *policy = sg_policy->policy;
	अचिन्हित दीर्घ util = 0, max = 1;
	अचिन्हित पूर्णांक j;

	क्रम_each_cpu(j, policy->cpus) अणु
		काष्ठा sugov_cpu *j_sg_cpu = &per_cpu(sugov_cpu, j);
		अचिन्हित दीर्घ j_util, j_max;

		sugov_get_util(j_sg_cpu);
		sugov_ioरुको_apply(j_sg_cpu, समय);
		j_util = j_sg_cpu->util;
		j_max = j_sg_cpu->max;

		अगर (j_util * max > j_max * util) अणु
			util = j_util;
			max = j_max;
		पूर्ण
	पूर्ण

	वापस get_next_freq(sg_policy, util, max);
पूर्ण

अटल व्योम
sugov_update_shared(काष्ठा update_util_data *hook, u64 समय, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sugov_cpu *sg_cpu = container_of(hook, काष्ठा sugov_cpu, update_util);
	काष्ठा sugov_policy *sg_policy = sg_cpu->sg_policy;
	अचिन्हित पूर्णांक next_f;

	raw_spin_lock(&sg_policy->update_lock);

	sugov_ioरुको_boost(sg_cpu, समय, flags);
	sg_cpu->last_update = समय;

	ignore_dl_rate_limit(sg_cpu);

	अगर (sugov_should_update_freq(sg_policy, समय)) अणु
		next_f = sugov_next_freq_shared(sg_cpu, समय);

		अगर (!sugov_update_next_freq(sg_policy, समय, next_f))
			जाओ unlock;

		अगर (sg_policy->policy->fast_चयन_enabled)
			cpufreq_driver_fast_चयन(sg_policy->policy, next_f);
		अन्यथा
			sugov_deferred_update(sg_policy);
	पूर्ण
unlock:
	raw_spin_unlock(&sg_policy->update_lock);
पूर्ण

अटल व्योम sugov_work(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा sugov_policy *sg_policy = container_of(work, काष्ठा sugov_policy, work);
	अचिन्हित पूर्णांक freq;
	अचिन्हित दीर्घ flags;

	/*
	 * Hold sg_policy->update_lock लघुly to handle the हाल where:
	 * in हाल sg_policy->next_freq is पढ़ो here, and then updated by
	 * sugov_deferred_update() just beक्रमe work_in_progress is set to false
	 * here, we may miss queueing the new update.
	 *
	 * Note: If a work was queued after the update_lock is released,
	 * sugov_work() will just be called again by kthपढ़ो_work code; and the
	 * request will be proceed beक्रमe the sugov thपढ़ो sleeps.
	 */
	raw_spin_lock_irqsave(&sg_policy->update_lock, flags);
	freq = sg_policy->next_freq;
	sg_policy->work_in_progress = false;
	raw_spin_unlock_irqrestore(&sg_policy->update_lock, flags);

	mutex_lock(&sg_policy->work_lock);
	__cpufreq_driver_target(sg_policy->policy, freq, CPUFREQ_RELATION_L);
	mutex_unlock(&sg_policy->work_lock);
पूर्ण

अटल व्योम sugov_irq_work(काष्ठा irq_work *irq_work)
अणु
	काष्ठा sugov_policy *sg_policy;

	sg_policy = container_of(irq_work, काष्ठा sugov_policy, irq_work);

	kthपढ़ो_queue_work(&sg_policy->worker, &sg_policy->work);
पूर्ण

/************************** sysfs पूर्णांकerface ************************/

अटल काष्ठा sugov_tunables *global_tunables;
अटल DEFINE_MUTEX(global_tunables_lock);

अटल अंतरभूत काष्ठा sugov_tunables *to_sugov_tunables(काष्ठा gov_attr_set *attr_set)
अणु
	वापस container_of(attr_set, काष्ठा sugov_tunables, attr_set);
पूर्ण

अटल sमाप_प्रकार rate_limit_us_show(काष्ठा gov_attr_set *attr_set, अक्षर *buf)
अणु
	काष्ठा sugov_tunables *tunables = to_sugov_tunables(attr_set);

	वापस प्र_लिखो(buf, "%u\n", tunables->rate_limit_us);
पूर्ण

अटल sमाप_प्रकार
rate_limit_us_store(काष्ठा gov_attr_set *attr_set, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sugov_tunables *tunables = to_sugov_tunables(attr_set);
	काष्ठा sugov_policy *sg_policy;
	अचिन्हित पूर्णांक rate_limit_us;

	अगर (kstrtouपूर्णांक(buf, 10, &rate_limit_us))
		वापस -EINVAL;

	tunables->rate_limit_us = rate_limit_us;

	list_क्रम_each_entry(sg_policy, &attr_set->policy_list, tunables_hook)
		sg_policy->freq_update_delay_ns = rate_limit_us * NSEC_PER_USEC;

	वापस count;
पूर्ण

अटल काष्ठा governor_attr rate_limit_us = __ATTR_RW(rate_limit_us);

अटल काष्ठा attribute *sugov_attrs[] = अणु
	&rate_limit_us.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(sugov);

अटल काष्ठा kobj_type sugov_tunables_ktype = अणु
	.शेष_groups = sugov_groups,
	.sysfs_ops = &governor_sysfs_ops,
पूर्ण;

/********************** cpufreq governor पूर्णांकerface *********************/

काष्ठा cpufreq_governor schedutil_gov;

अटल काष्ठा sugov_policy *sugov_policy_alloc(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा sugov_policy *sg_policy;

	sg_policy = kzalloc(माप(*sg_policy), GFP_KERNEL);
	अगर (!sg_policy)
		वापस शून्य;

	sg_policy->policy = policy;
	raw_spin_lock_init(&sg_policy->update_lock);
	वापस sg_policy;
पूर्ण

अटल व्योम sugov_policy_मुक्त(काष्ठा sugov_policy *sg_policy)
अणु
	kमुक्त(sg_policy);
पूर्ण

अटल पूर्णांक sugov_kthपढ़ो_create(काष्ठा sugov_policy *sg_policy)
अणु
	काष्ठा task_काष्ठा *thपढ़ो;
	काष्ठा sched_attr attr = अणु
		.size		= माप(काष्ठा sched_attr),
		.sched_policy	= SCHED_DEADLINE,
		.sched_flags	= SCHED_FLAG_SUGOV,
		.sched_nice	= 0,
		.sched_priority	= 0,
		/*
		 * Fake (unused) bandwidth; workaround to "fix"
		 * priority inheritance.
		 */
		.sched_runसमय	=  1000000,
		.sched_deadline = 10000000,
		.sched_period	= 10000000,
	पूर्ण;
	काष्ठा cpufreq_policy *policy = sg_policy->policy;
	पूर्णांक ret;

	/* kthपढ़ो only required क्रम slow path */
	अगर (policy->fast_चयन_enabled)
		वापस 0;

	kthपढ़ो_init_work(&sg_policy->work, sugov_work);
	kthपढ़ो_init_worker(&sg_policy->worker);
	thपढ़ो = kthपढ़ो_create(kthपढ़ो_worker_fn, &sg_policy->worker,
				"sugov:%d",
				cpumask_first(policy->related_cpus));
	अगर (IS_ERR(thपढ़ो)) अणु
		pr_err("failed to create sugov thread: %ld\n", PTR_ERR(thपढ़ो));
		वापस PTR_ERR(thपढ़ो);
	पूर्ण

	ret = sched_setattr_nocheck(thपढ़ो, &attr);
	अगर (ret) अणु
		kthपढ़ो_stop(thपढ़ो);
		pr_warn("%s: failed to set SCHED_DEADLINE\n", __func__);
		वापस ret;
	पूर्ण

	sg_policy->thपढ़ो = thपढ़ो;
	kthपढ़ो_bind_mask(thपढ़ो, policy->related_cpus);
	init_irq_work(&sg_policy->irq_work, sugov_irq_work);
	mutex_init(&sg_policy->work_lock);

	wake_up_process(thपढ़ो);

	वापस 0;
पूर्ण

अटल व्योम sugov_kthपढ़ो_stop(काष्ठा sugov_policy *sg_policy)
अणु
	/* kthपढ़ो only required क्रम slow path */
	अगर (sg_policy->policy->fast_चयन_enabled)
		वापस;

	kthपढ़ो_flush_worker(&sg_policy->worker);
	kthपढ़ो_stop(sg_policy->thपढ़ो);
	mutex_destroy(&sg_policy->work_lock);
पूर्ण

अटल काष्ठा sugov_tunables *sugov_tunables_alloc(काष्ठा sugov_policy *sg_policy)
अणु
	काष्ठा sugov_tunables *tunables;

	tunables = kzalloc(माप(*tunables), GFP_KERNEL);
	अगर (tunables) अणु
		gov_attr_set_init(&tunables->attr_set, &sg_policy->tunables_hook);
		अगर (!have_governor_per_policy())
			global_tunables = tunables;
	पूर्ण
	वापस tunables;
पूर्ण

अटल व्योम sugov_tunables_मुक्त(काष्ठा sugov_tunables *tunables)
अणु
	अगर (!have_governor_per_policy())
		global_tunables = शून्य;

	kमुक्त(tunables);
पूर्ण

अटल पूर्णांक sugov_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा sugov_policy *sg_policy;
	काष्ठा sugov_tunables *tunables;
	पूर्णांक ret = 0;

	/* State should be equivalent to EXIT */
	अगर (policy->governor_data)
		वापस -EBUSY;

	cpufreq_enable_fast_चयन(policy);

	sg_policy = sugov_policy_alloc(policy);
	अगर (!sg_policy) अणु
		ret = -ENOMEM;
		जाओ disable_fast_चयन;
	पूर्ण

	ret = sugov_kthपढ़ो_create(sg_policy);
	अगर (ret)
		जाओ मुक्त_sg_policy;

	mutex_lock(&global_tunables_lock);

	अगर (global_tunables) अणु
		अगर (WARN_ON(have_governor_per_policy())) अणु
			ret = -EINVAL;
			जाओ stop_kthपढ़ो;
		पूर्ण
		policy->governor_data = sg_policy;
		sg_policy->tunables = global_tunables;

		gov_attr_set_get(&global_tunables->attr_set, &sg_policy->tunables_hook);
		जाओ out;
	पूर्ण

	tunables = sugov_tunables_alloc(sg_policy);
	अगर (!tunables) अणु
		ret = -ENOMEM;
		जाओ stop_kthपढ़ो;
	पूर्ण

	tunables->rate_limit_us = cpufreq_policy_transition_delay_us(policy);

	policy->governor_data = sg_policy;
	sg_policy->tunables = tunables;

	ret = kobject_init_and_add(&tunables->attr_set.kobj, &sugov_tunables_ktype,
				   get_governor_parent_kobj(policy), "%s",
				   schedutil_gov.name);
	अगर (ret)
		जाओ fail;

out:
	mutex_unlock(&global_tunables_lock);
	वापस 0;

fail:
	kobject_put(&tunables->attr_set.kobj);
	policy->governor_data = शून्य;
	sugov_tunables_मुक्त(tunables);

stop_kthपढ़ो:
	sugov_kthपढ़ो_stop(sg_policy);
	mutex_unlock(&global_tunables_lock);

मुक्त_sg_policy:
	sugov_policy_मुक्त(sg_policy);

disable_fast_चयन:
	cpufreq_disable_fast_चयन(policy);

	pr_err("initialization failed (error %d)\n", ret);
	वापस ret;
पूर्ण

अटल व्योम sugov_निकास(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा sugov_policy *sg_policy = policy->governor_data;
	काष्ठा sugov_tunables *tunables = sg_policy->tunables;
	अचिन्हित पूर्णांक count;

	mutex_lock(&global_tunables_lock);

	count = gov_attr_set_put(&tunables->attr_set, &sg_policy->tunables_hook);
	policy->governor_data = शून्य;
	अगर (!count)
		sugov_tunables_मुक्त(tunables);

	mutex_unlock(&global_tunables_lock);

	sugov_kthपढ़ो_stop(sg_policy);
	sugov_policy_मुक्त(sg_policy);
	cpufreq_disable_fast_चयन(policy);
पूर्ण

अटल पूर्णांक sugov_start(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा sugov_policy *sg_policy = policy->governor_data;
	व्योम (*uu)(काष्ठा update_util_data *data, u64 समय, अचिन्हित पूर्णांक flags);
	अचिन्हित पूर्णांक cpu;

	sg_policy->freq_update_delay_ns	= sg_policy->tunables->rate_limit_us * NSEC_PER_USEC;
	sg_policy->last_freq_update_समय	= 0;
	sg_policy->next_freq			= 0;
	sg_policy->work_in_progress		= false;
	sg_policy->limits_changed		= false;
	sg_policy->cached_raw_freq		= 0;

	sg_policy->need_freq_update = cpufreq_driver_test_flags(CPUFREQ_NEED_UPDATE_LIMITS);

	क्रम_each_cpu(cpu, policy->cpus) अणु
		काष्ठा sugov_cpu *sg_cpu = &per_cpu(sugov_cpu, cpu);

		स_रखो(sg_cpu, 0, माप(*sg_cpu));
		sg_cpu->cpu			= cpu;
		sg_cpu->sg_policy		= sg_policy;
	पूर्ण

	अगर (policy_is_shared(policy))
		uu = sugov_update_shared;
	अन्यथा अगर (policy->fast_चयन_enabled && cpufreq_driver_has_adjust_perf())
		uu = sugov_update_single_perf;
	अन्यथा
		uu = sugov_update_single_freq;

	क्रम_each_cpu(cpu, policy->cpus) अणु
		काष्ठा sugov_cpu *sg_cpu = &per_cpu(sugov_cpu, cpu);

		cpufreq_add_update_util_hook(cpu, &sg_cpu->update_util, uu);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sugov_stop(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा sugov_policy *sg_policy = policy->governor_data;
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, policy->cpus)
		cpufreq_हटाओ_update_util_hook(cpu);

	synchronize_rcu();

	अगर (!policy->fast_चयन_enabled) अणु
		irq_work_sync(&sg_policy->irq_work);
		kthपढ़ो_cancel_work_sync(&sg_policy->work);
	पूर्ण
पूर्ण

अटल व्योम sugov_limits(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा sugov_policy *sg_policy = policy->governor_data;

	अगर (!policy->fast_चयन_enabled) अणु
		mutex_lock(&sg_policy->work_lock);
		cpufreq_policy_apply_limits(policy);
		mutex_unlock(&sg_policy->work_lock);
	पूर्ण

	sg_policy->limits_changed = true;
पूर्ण

काष्ठा cpufreq_governor schedutil_gov = अणु
	.name			= "schedutil",
	.owner			= THIS_MODULE,
	.flags			= CPUFREQ_GOV_DYNAMIC_SWITCHING,
	.init			= sugov_init,
	.निकास			= sugov_निकास,
	.start			= sugov_start,
	.stop			= sugov_stop,
	.limits			= sugov_limits,
पूर्ण;

#अगर_घोषित CONFIG_CPU_FREQ_DEFAULT_GOV_SCHEDUTIL
काष्ठा cpufreq_governor *cpufreq_शेष_governor(व्योम)
अणु
	वापस &schedutil_gov;
पूर्ण
#पूर्ण_अगर

cpufreq_governor_init(schedutil_gov);

#अगर_घोषित CONFIG_ENERGY_MODEL
अटल व्योम rebuild_sd_workfn(काष्ठा work_काष्ठा *work)
अणु
	rebuild_sched_करोमुख्यs_energy();
पूर्ण
अटल DECLARE_WORK(rebuild_sd_work, rebuild_sd_workfn);

/*
 * EAS shouldn't be attempted without sugov, so rebuild the sched_करोमुख्यs
 * on governor changes to make sure the scheduler knows about it.
 */
व्योम sched_cpufreq_governor_change(काष्ठा cpufreq_policy *policy,
				  काष्ठा cpufreq_governor *old_gov)
अणु
	अगर (old_gov == &schedutil_gov || policy->governor == &schedutil_gov) अणु
		/*
		 * When called from the cpufreq_रेजिस्टर_driver() path, the
		 * cpu_hotplug_lock is alपढ़ोy held, so use a work item to
		 * aव्योम nested locking in rebuild_sched_करोमुख्यs().
		 */
		schedule_work(&rebuild_sd_work);
	पूर्ण

पूर्ण
#पूर्ण_अगर
