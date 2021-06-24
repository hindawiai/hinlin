<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/cpufreq/cpufreq.c
 *
 *  Copyright (C) 2001 Russell King
 *            (C) 2002 - 2003 Dominik Broकरोwski <linux@broकरो.de>
 *            (C) 2013 Viresh Kumar <viresh.kumar@linaro.org>
 *
 *  Oct 2005 - Ashok Raj <ashok.raj@पूर्णांकel.com>
 *	Added handling क्रम CPU hotplug
 *  Feb 2006 - Jacob Shin <jacob.shin@amd.com>
 *	Fix handling क्रम CPU hotplug -- affected CPUs
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpu_cooling.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/tick.h>
#समावेश <trace/events/घातer.h>

अटल LIST_HEAD(cpufreq_policy_list);

/* Macros to iterate over CPU policies */
#घोषणा क्रम_each_suitable_policy(__policy, __active)			 \
	list_क्रम_each_entry(__policy, &cpufreq_policy_list, policy_list) \
		अगर ((__active) == !policy_is_inactive(__policy))

#घोषणा क्रम_each_active_policy(__policy)		\
	क्रम_each_suitable_policy(__policy, true)
#घोषणा क्रम_each_inactive_policy(__policy)		\
	क्रम_each_suitable_policy(__policy, false)

/* Iterate over governors */
अटल LIST_HEAD(cpufreq_governor_list);
#घोषणा क्रम_each_governor(__governor)				\
	list_क्रम_each_entry(__governor, &cpufreq_governor_list, governor_list)

अटल अक्षर शेष_governor[CPUFREQ_NAME_LEN];

/*
 * The "cpufreq driver" - the arch- or hardware-dependent low
 * level driver of CPUFreq support, and its spinlock. This lock
 * also protects the cpufreq_cpu_data array.
 */
अटल काष्ठा cpufreq_driver *cpufreq_driver;
अटल DEFINE_PER_CPU(काष्ठा cpufreq_policy *, cpufreq_cpu_data);
अटल DEFINE_RWLOCK(cpufreq_driver_lock);

अटल DEFINE_STATIC_KEY_FALSE(cpufreq_freq_invariance);
bool cpufreq_supports_freq_invariance(व्योम)
अणु
	वापस अटल_branch_likely(&cpufreq_freq_invariance);
पूर्ण

/* Flag to suspend/resume CPUFreq governors */
अटल bool cpufreq_suspended;

अटल अंतरभूत bool has_target(व्योम)
अणु
	वापस cpufreq_driver->target_index || cpufreq_driver->target;
पूर्ण

/* पूर्णांकernal prototypes */
अटल अचिन्हित पूर्णांक __cpufreq_get(काष्ठा cpufreq_policy *policy);
अटल पूर्णांक cpufreq_init_governor(काष्ठा cpufreq_policy *policy);
अटल व्योम cpufreq_निकास_governor(काष्ठा cpufreq_policy *policy);
अटल व्योम cpufreq_governor_limits(काष्ठा cpufreq_policy *policy);
अटल पूर्णांक cpufreq_set_policy(काष्ठा cpufreq_policy *policy,
			      काष्ठा cpufreq_governor *new_gov,
			      अचिन्हित पूर्णांक new_pol);

/*
 * Two notअगरier lists: the "policy" list is involved in the
 * validation process क्रम a new CPU frequency policy; the
 * "transition" list क्रम kernel code that needs to handle
 * changes to devices when the CPU घड़ी speed changes.
 * The mutex locks both lists.
 */
अटल BLOCKING_NOTIFIER_HEAD(cpufreq_policy_notअगरier_list);
SRCU_NOTIFIER_HEAD_STATIC(cpufreq_transition_notअगरier_list);

अटल पूर्णांक off __पढ़ो_mostly;
अटल पूर्णांक cpufreq_disabled(व्योम)
अणु
	वापस off;
पूर्ण
व्योम disable_cpufreq(व्योम)
अणु
	off = 1;
पूर्ण
अटल DEFINE_MUTEX(cpufreq_governor_mutex);

bool have_governor_per_policy(व्योम)
अणु
	वापस !!(cpufreq_driver->flags & CPUFREQ_HAVE_GOVERNOR_PER_POLICY);
पूर्ण
EXPORT_SYMBOL_GPL(have_governor_per_policy);

अटल काष्ठा kobject *cpufreq_global_kobject;

काष्ठा kobject *get_governor_parent_kobj(काष्ठा cpufreq_policy *policy)
अणु
	अगर (have_governor_per_policy())
		वापस &policy->kobj;
	अन्यथा
		वापस cpufreq_global_kobject;
पूर्ण
EXPORT_SYMBOL_GPL(get_governor_parent_kobj);

अटल अंतरभूत u64 get_cpu_idle_समय_jअगरfy(अचिन्हित पूर्णांक cpu, u64 *wall)
अणु
	काष्ठा kernel_cpustat kcpustat;
	u64 cur_wall_समय;
	u64 idle_समय;
	u64 busy_समय;

	cur_wall_समय = jअगरfies64_to_nsecs(get_jअगरfies_64());

	kcpustat_cpu_fetch(&kcpustat, cpu);

	busy_समय = kcpustat.cpustat[CPUTIME_USER];
	busy_समय += kcpustat.cpustat[CPUTIME_SYSTEM];
	busy_समय += kcpustat.cpustat[CPUTIME_IRQ];
	busy_समय += kcpustat.cpustat[CPUTIME_SOFTIRQ];
	busy_समय += kcpustat.cpustat[CPUTIME_STEAL];
	busy_समय += kcpustat.cpustat[CPUTIME_NICE];

	idle_समय = cur_wall_समय - busy_समय;
	अगर (wall)
		*wall = भाग_u64(cur_wall_समय, NSEC_PER_USEC);

	वापस भाग_u64(idle_समय, NSEC_PER_USEC);
पूर्ण

u64 get_cpu_idle_समय(अचिन्हित पूर्णांक cpu, u64 *wall, पूर्णांक io_busy)
अणु
	u64 idle_समय = get_cpu_idle_समय_us(cpu, io_busy ? wall : शून्य);

	अगर (idle_समय == -1ULL)
		वापस get_cpu_idle_समय_jअगरfy(cpu, wall);
	अन्यथा अगर (!io_busy)
		idle_समय += get_cpu_ioरुको_समय_us(cpu, wall);

	वापस idle_समय;
पूर्ण
EXPORT_SYMBOL_GPL(get_cpu_idle_समय);

/*
 * This is a generic cpufreq init() routine which can be used by cpufreq
 * drivers of SMP प्रणालीs. It will करो following:
 * - validate & show freq table passed
 * - set policies transition latency
 * - policy->cpus with all possible CPUs
 */
व्योम cpufreq_generic_init(काष्ठा cpufreq_policy *policy,
		काष्ठा cpufreq_frequency_table *table,
		अचिन्हित पूर्णांक transition_latency)
अणु
	policy->freq_table = table;
	policy->cpuinfo.transition_latency = transition_latency;

	/*
	 * The driver only supports the SMP configuration where all processors
	 * share the घड़ी and voltage and घड़ी.
	 */
	cpumask_setall(policy->cpus);
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_generic_init);

काष्ठा cpufreq_policy *cpufreq_cpu_get_raw(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy = per_cpu(cpufreq_cpu_data, cpu);

	वापस policy && cpumask_test_cpu(cpu, policy->cpus) ? policy : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_cpu_get_raw);

अचिन्हित पूर्णांक cpufreq_generic_get(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy = cpufreq_cpu_get_raw(cpu);

	अगर (!policy || IS_ERR(policy->clk)) अणु
		pr_err("%s: No %s associated to cpu: %d\n",
		       __func__, policy ? "clk" : "policy", cpu);
		वापस 0;
	पूर्ण

	वापस clk_get_rate(policy->clk) / 1000;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_generic_get);

/**
 * cpufreq_cpu_get - Return policy क्रम a CPU and mark it as busy.
 * @cpu: CPU to find the policy क्रम.
 *
 * Call cpufreq_cpu_get_raw() to obtain a cpufreq policy क्रम @cpu and increment
 * the kobject reference counter of that policy.  Return a valid policy on
 * success or शून्य on failure.
 *
 * The policy वापसed by this function has to be released with the help of
 * cpufreq_cpu_put() to balance its kobject reference counter properly.
 */
काष्ठा cpufreq_policy *cpufreq_cpu_get(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy = शून्य;
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(cpu >= nr_cpu_ids))
		वापस शून्य;

	/* get the cpufreq driver */
	पढ़ो_lock_irqsave(&cpufreq_driver_lock, flags);

	अगर (cpufreq_driver) अणु
		/* get the CPU */
		policy = cpufreq_cpu_get_raw(cpu);
		अगर (policy)
			kobject_get(&policy->kobj);
	पूर्ण

	पढ़ो_unlock_irqrestore(&cpufreq_driver_lock, flags);

	वापस policy;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_cpu_get);

/**
 * cpufreq_cpu_put - Decrement kobject usage counter क्रम cpufreq policy.
 * @policy: cpufreq policy वापसed by cpufreq_cpu_get().
 */
व्योम cpufreq_cpu_put(काष्ठा cpufreq_policy *policy)
अणु
	kobject_put(&policy->kobj);
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_cpu_put);

/**
 * cpufreq_cpu_release - Unlock a policy and decrement its usage counter.
 * @policy: cpufreq policy वापसed by cpufreq_cpu_acquire().
 */
व्योम cpufreq_cpu_release(काष्ठा cpufreq_policy *policy)
अणु
	अगर (WARN_ON(!policy))
		वापस;

	lockdep_निश्चित_held(&policy->rwsem);

	up_ग_लिखो(&policy->rwsem);

	cpufreq_cpu_put(policy);
पूर्ण

/**
 * cpufreq_cpu_acquire - Find policy क्रम a CPU, mark it as busy and lock it.
 * @cpu: CPU to find the policy क्रम.
 *
 * Call cpufreq_cpu_get() to get a reference on the cpufreq policy क्रम @cpu and
 * अगर the policy वापसed by it is not शून्य, acquire its rwsem क्रम writing.
 * Return the policy अगर it is active or release it and वापस शून्य otherwise.
 *
 * The policy वापसed by this function has to be released with the help of
 * cpufreq_cpu_release() in order to release its rwsem and balance its usage
 * counter properly.
 */
काष्ठा cpufreq_policy *cpufreq_cpu_acquire(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy = cpufreq_cpu_get(cpu);

	अगर (!policy)
		वापस शून्य;

	करोwn_ग_लिखो(&policy->rwsem);

	अगर (policy_is_inactive(policy)) अणु
		cpufreq_cpu_release(policy);
		वापस शून्य;
	पूर्ण

	वापस policy;
पूर्ण

/*********************************************************************
 *            EXTERNALLY AFFECTING FREQUENCY CHANGES                 *
 *********************************************************************/

/**
 * adjust_jअगरfies - Adjust the प्रणाली "loops_per_jiffy".
 * @val: CPUFREQ_PRECHANGE or CPUFREQ_POSTCHANGE.
 * @ci: Frequency change inक्रमmation.
 *
 * This function alters the प्रणाली "loops_per_jiffy" क्रम the घड़ी
 * speed change. Note that loops_per_jअगरfy cannot be updated on SMP
 * प्रणालीs as each CPU might be scaled dअगरferently. So, use the arch
 * per-CPU loops_per_jअगरfy value wherever possible.
 */
अटल व्योम adjust_jअगरfies(अचिन्हित दीर्घ val, काष्ठा cpufreq_freqs *ci)
अणु
#अगर_अघोषित CONFIG_SMP
	अटल अचिन्हित दीर्घ l_p_j_ref;
	अटल अचिन्हित पूर्णांक l_p_j_ref_freq;

	अगर (ci->flags & CPUFREQ_CONST_LOOPS)
		वापस;

	अगर (!l_p_j_ref_freq) अणु
		l_p_j_ref = loops_per_jअगरfy;
		l_p_j_ref_freq = ci->old;
		pr_debug("saving %lu as reference value for loops_per_jiffy; freq is %u kHz\n",
			 l_p_j_ref, l_p_j_ref_freq);
	पूर्ण
	अगर (val == CPUFREQ_POSTCHANGE && ci->old != ci->new) अणु
		loops_per_jअगरfy = cpufreq_scale(l_p_j_ref, l_p_j_ref_freq,
								ci->new);
		pr_debug("scaling loops_per_jiffy to %lu for frequency %u kHz\n",
			 loops_per_jअगरfy, ci->new);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/**
 * cpufreq_notअगरy_transition - Notअगरy frequency transition and adjust jअगरfies.
 * @policy: cpufreq policy to enable fast frequency चयनing क्रम.
 * @freqs: contain details of the frequency update.
 * @state: set to CPUFREQ_PRECHANGE or CPUFREQ_POSTCHANGE.
 *
 * This function calls the transition notअगरiers and adjust_jअगरfies().
 *
 * It is called twice on all CPU frequency changes that have बाह्यal effects.
 */
अटल व्योम cpufreq_notअगरy_transition(काष्ठा cpufreq_policy *policy,
				      काष्ठा cpufreq_freqs *freqs,
				      अचिन्हित पूर्णांक state)
अणु
	पूर्णांक cpu;

	BUG_ON(irqs_disabled());

	अगर (cpufreq_disabled())
		वापस;

	freqs->policy = policy;
	freqs->flags = cpufreq_driver->flags;
	pr_debug("notification %u of frequency transition to %u kHz\n",
		 state, freqs->new);

	चयन (state) अणु
	हाल CPUFREQ_PRECHANGE:
		/*
		 * Detect अगर the driver reported a value as "old frequency"
		 * which is not equal to what the cpufreq core thinks is
		 * "old frequency".
		 */
		अगर (policy->cur && policy->cur != freqs->old) अणु
			pr_debug("Warning: CPU frequency is %u, cpufreq assumed %u kHz\n",
				 freqs->old, policy->cur);
			freqs->old = policy->cur;
		पूर्ण

		srcu_notअगरier_call_chain(&cpufreq_transition_notअगरier_list,
					 CPUFREQ_PRECHANGE, freqs);

		adjust_jअगरfies(CPUFREQ_PRECHANGE, freqs);
		अवरोध;

	हाल CPUFREQ_POSTCHANGE:
		adjust_jअगरfies(CPUFREQ_POSTCHANGE, freqs);
		pr_debug("FREQ: %u - CPUs: %*pbl\n", freqs->new,
			 cpumask_pr_args(policy->cpus));

		क्रम_each_cpu(cpu, policy->cpus)
			trace_cpu_frequency(freqs->new, cpu);

		srcu_notअगरier_call_chain(&cpufreq_transition_notअगरier_list,
					 CPUFREQ_POSTCHANGE, freqs);

		cpufreq_stats_record_transition(policy, freqs->new);
		policy->cur = freqs->new;
	पूर्ण
पूर्ण

/* Do post notअगरications when there are chances that transition has failed */
अटल व्योम cpufreq_notअगरy_post_transition(काष्ठा cpufreq_policy *policy,
		काष्ठा cpufreq_freqs *freqs, पूर्णांक transition_failed)
अणु
	cpufreq_notअगरy_transition(policy, freqs, CPUFREQ_POSTCHANGE);
	अगर (!transition_failed)
		वापस;

	swap(freqs->old, freqs->new);
	cpufreq_notअगरy_transition(policy, freqs, CPUFREQ_PRECHANGE);
	cpufreq_notअगरy_transition(policy, freqs, CPUFREQ_POSTCHANGE);
पूर्ण

व्योम cpufreq_freq_transition_begin(काष्ठा cpufreq_policy *policy,
		काष्ठा cpufreq_freqs *freqs)
अणु

	/*
	 * Catch द्विगुन invocations of _begin() which lead to self-deadlock.
	 * ASYNC_NOTIFICATION drivers are left out because the cpufreq core
	 * करोesn't invoke _begin() on their behalf, and hence the chances of
	 * द्विगुन invocations are very low. Moreover, there are scenarios
	 * where these checks can emit false-positive warnings in these
	 * drivers; so we aव्योम that by skipping them altogether.
	 */
	WARN_ON(!(cpufreq_driver->flags & CPUFREQ_ASYNC_NOTIFICATION)
				&& current == policy->transition_task);

रुको:
	रुको_event(policy->transition_रुको, !policy->transition_ongoing);

	spin_lock(&policy->transition_lock);

	अगर (unlikely(policy->transition_ongoing)) अणु
		spin_unlock(&policy->transition_lock);
		जाओ रुको;
	पूर्ण

	policy->transition_ongoing = true;
	policy->transition_task = current;

	spin_unlock(&policy->transition_lock);

	cpufreq_notअगरy_transition(policy, freqs, CPUFREQ_PRECHANGE);
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_freq_transition_begin);

व्योम cpufreq_freq_transition_end(काष्ठा cpufreq_policy *policy,
		काष्ठा cpufreq_freqs *freqs, पूर्णांक transition_failed)
अणु
	अगर (WARN_ON(!policy->transition_ongoing))
		वापस;

	cpufreq_notअगरy_post_transition(policy, freqs, transition_failed);

	arch_set_freq_scale(policy->related_cpus,
			    policy->cur,
			    policy->cpuinfo.max_freq);

	policy->transition_ongoing = false;
	policy->transition_task = शून्य;

	wake_up(&policy->transition_रुको);
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_freq_transition_end);

/*
 * Fast frequency चयनing status count.  Positive means "enabled", negative
 * means "disabled" and 0 means "not decided yet".
 */
अटल पूर्णांक cpufreq_fast_चयन_count;
अटल DEFINE_MUTEX(cpufreq_fast_चयन_lock);

अटल व्योम cpufreq_list_transition_notअगरiers(व्योम)
अणु
	काष्ठा notअगरier_block *nb;

	pr_info("Registered transition notifiers:\n");

	mutex_lock(&cpufreq_transition_notअगरier_list.mutex);

	क्रम (nb = cpufreq_transition_notअगरier_list.head; nb; nb = nb->next)
		pr_info("%pS\n", nb->notअगरier_call);

	mutex_unlock(&cpufreq_transition_notअगरier_list.mutex);
पूर्ण

/**
 * cpufreq_enable_fast_चयन - Enable fast frequency चयनing क्रम policy.
 * @policy: cpufreq policy to enable fast frequency चयनing क्रम.
 *
 * Try to enable fast frequency चयनing क्रम @policy.
 *
 * The attempt will fail अगर there is at least one transition notअगरier रेजिस्टरed
 * at this poपूर्णांक, as fast frequency चयनing is quite fundamentally at odds
 * with transition notअगरiers.  Thus अगर successful, it will make registration of
 * transition notअगरiers fail going क्रमward.
 */
व्योम cpufreq_enable_fast_चयन(काष्ठा cpufreq_policy *policy)
अणु
	lockdep_निश्चित_held(&policy->rwsem);

	अगर (!policy->fast_चयन_possible)
		वापस;

	mutex_lock(&cpufreq_fast_चयन_lock);
	अगर (cpufreq_fast_चयन_count >= 0) अणु
		cpufreq_fast_चयन_count++;
		policy->fast_चयन_enabled = true;
	पूर्ण अन्यथा अणु
		pr_warn("CPU%u: Fast frequency switching not enabled\n",
			policy->cpu);
		cpufreq_list_transition_notअगरiers();
	पूर्ण
	mutex_unlock(&cpufreq_fast_चयन_lock);
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_enable_fast_चयन);

/**
 * cpufreq_disable_fast_चयन - Disable fast frequency चयनing क्रम policy.
 * @policy: cpufreq policy to disable fast frequency चयनing क्रम.
 */
व्योम cpufreq_disable_fast_चयन(काष्ठा cpufreq_policy *policy)
अणु
	mutex_lock(&cpufreq_fast_चयन_lock);
	अगर (policy->fast_चयन_enabled) अणु
		policy->fast_चयन_enabled = false;
		अगर (!WARN_ON(cpufreq_fast_चयन_count <= 0))
			cpufreq_fast_चयन_count--;
	पूर्ण
	mutex_unlock(&cpufreq_fast_चयन_lock);
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_disable_fast_चयन);

/**
 * cpufreq_driver_resolve_freq - Map a target frequency to a driver-supported
 * one.
 * @policy: associated policy to पूर्णांकerrogate
 * @target_freq: target frequency to resolve.
 *
 * The target to driver frequency mapping is cached in the policy.
 *
 * Return: Lowest driver-supported frequency greater than or equal to the
 * given target_freq, subject to policy (min/max) and driver limitations.
 */
अचिन्हित पूर्णांक cpufreq_driver_resolve_freq(काष्ठा cpufreq_policy *policy,
					 अचिन्हित पूर्णांक target_freq)
अणु
	target_freq = clamp_val(target_freq, policy->min, policy->max);
	policy->cached_target_freq = target_freq;

	अगर (cpufreq_driver->target_index) अणु
		अचिन्हित पूर्णांक idx;

		idx = cpufreq_frequency_table_target(policy, target_freq,
						     CPUFREQ_RELATION_L);
		policy->cached_resolved_idx = idx;
		वापस policy->freq_table[idx].frequency;
	पूर्ण

	अगर (cpufreq_driver->resolve_freq)
		वापस cpufreq_driver->resolve_freq(policy, target_freq);

	वापस target_freq;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_driver_resolve_freq);

अचिन्हित पूर्णांक cpufreq_policy_transition_delay_us(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक latency;

	अगर (policy->transition_delay_us)
		वापस policy->transition_delay_us;

	latency = policy->cpuinfo.transition_latency / NSEC_PER_USEC;
	अगर (latency) अणु
		/*
		 * For platक्रमms that can change the frequency very fast (< 10
		 * us), the above क्रमmula gives a decent transition delay. But
		 * क्रम platक्रमms where transition_latency is in milliseconds, it
		 * ends up giving unrealistic values.
		 *
		 * Cap the शेष transition delay to 10 ms, which seems to be
		 * a reasonable amount of समय after which we should reevaluate
		 * the frequency.
		 */
		वापस min(latency * LATENCY_MULTIPLIER, (अचिन्हित पूर्णांक)10000);
	पूर्ण

	वापस LATENCY_MULTIPLIER;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_policy_transition_delay_us);

/*********************************************************************
 *                          SYSFS INTERFACE                          *
 *********************************************************************/
अटल sमाप_प्रकार show_boost(काष्ठा kobject *kobj,
			  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", cpufreq_driver->boost_enabled);
पूर्ण

अटल sमाप_प्रकार store_boost(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret, enable;

	ret = माला_पूछो(buf, "%d", &enable);
	अगर (ret != 1 || enable < 0 || enable > 1)
		वापस -EINVAL;

	अगर (cpufreq_boost_trigger_state(enable)) अणु
		pr_err("%s: Cannot %s BOOST!\n",
		       __func__, enable ? "enable" : "disable");
		वापस -EINVAL;
	पूर्ण

	pr_debug("%s: cpufreq BOOST %s\n",
		 __func__, enable ? "enabled" : "disabled");

	वापस count;
पूर्ण
define_one_global_rw(boost);

अटल काष्ठा cpufreq_governor *find_governor(स्थिर अक्षर *str_governor)
अणु
	काष्ठा cpufreq_governor *t;

	क्रम_each_governor(t)
		अगर (!strnहालcmp(str_governor, t->name, CPUFREQ_NAME_LEN))
			वापस t;

	वापस शून्य;
पूर्ण

अटल काष्ठा cpufreq_governor *get_governor(स्थिर अक्षर *str_governor)
अणु
	काष्ठा cpufreq_governor *t;

	mutex_lock(&cpufreq_governor_mutex);
	t = find_governor(str_governor);
	अगर (!t)
		जाओ unlock;

	अगर (!try_module_get(t->owner))
		t = शून्य;

unlock:
	mutex_unlock(&cpufreq_governor_mutex);

	वापस t;
पूर्ण

अटल अचिन्हित पूर्णांक cpufreq_parse_policy(अक्षर *str_governor)
अणु
	अगर (!strnहालcmp(str_governor, "performance", CPUFREQ_NAME_LEN))
		वापस CPUFREQ_POLICY_PERFORMANCE;

	अगर (!strnहालcmp(str_governor, "powersave", CPUFREQ_NAME_LEN))
		वापस CPUFREQ_POLICY_POWERSAVE;

	वापस CPUFREQ_POLICY_UNKNOWN;
पूर्ण

/**
 * cpufreq_parse_governor - parse a governor string only क्रम has_target()
 * @str_governor: Governor name.
 */
अटल काष्ठा cpufreq_governor *cpufreq_parse_governor(अक्षर *str_governor)
अणु
	काष्ठा cpufreq_governor *t;

	t = get_governor(str_governor);
	अगर (t)
		वापस t;

	अगर (request_module("cpufreq_%s", str_governor))
		वापस शून्य;

	वापस get_governor(str_governor);
पूर्ण

/*
 * cpufreq_per_cpu_attr_पढ़ो() / show_##file_name() -
 * prपूर्णांक out cpufreq inक्रमmation
 *
 * Write out inक्रमmation from cpufreq_driver->policy[cpu]; object must be
 * "unsigned int".
 */

#घोषणा show_one(file_name, object)			\
अटल sमाप_प्रकार show_##file_name				\
(काष्ठा cpufreq_policy *policy, अक्षर *buf)		\
अणु							\
	वापस प्र_लिखो(buf, "%u\n", policy->object);	\
पूर्ण

show_one(cpuinfo_min_freq, cpuinfo.min_freq);
show_one(cpuinfo_max_freq, cpuinfo.max_freq);
show_one(cpuinfo_transition_latency, cpuinfo.transition_latency);
show_one(scaling_min_freq, min);
show_one(scaling_max_freq, max);

__weak अचिन्हित पूर्णांक arch_freq_get_on_cpu(पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_scaling_cur_freq(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	sमाप_प्रकार ret;
	अचिन्हित पूर्णांक freq;

	freq = arch_freq_get_on_cpu(policy->cpu);
	अगर (freq)
		ret = प्र_लिखो(buf, "%u\n", freq);
	अन्यथा अगर (cpufreq_driver->setpolicy && cpufreq_driver->get)
		ret = प्र_लिखो(buf, "%u\n", cpufreq_driver->get(policy->cpu));
	अन्यथा
		ret = प्र_लिखो(buf, "%u\n", policy->cur);
	वापस ret;
पूर्ण

/*
 * cpufreq_per_cpu_attr_ग_लिखो() / store_##file_name() - sysfs ग_लिखो access
 */
#घोषणा store_one(file_name, object)			\
अटल sमाप_प्रकार store_##file_name					\
(काष्ठा cpufreq_policy *policy, स्थिर अक्षर *buf, माप_प्रकार count)		\
अणु									\
	अचिन्हित दीर्घ val;						\
	पूर्णांक ret;							\
									\
	ret = माला_पूछो(buf, "%lu", &val);					\
	अगर (ret != 1)							\
		वापस -EINVAL;						\
									\
	ret = freq_qos_update_request(policy->object##_freq_req, val);\
	वापस ret >= 0 ? count : ret;					\
पूर्ण

store_one(scaling_min_freq, min);
store_one(scaling_max_freq, max);

/*
 * show_cpuinfo_cur_freq - current CPU frequency as detected by hardware
 */
अटल sमाप_प्रकार show_cpuinfo_cur_freq(काष्ठा cpufreq_policy *policy,
					अक्षर *buf)
अणु
	अचिन्हित पूर्णांक cur_freq = __cpufreq_get(policy);

	अगर (cur_freq)
		वापस प्र_लिखो(buf, "%u\n", cur_freq);

	वापस प्र_लिखो(buf, "<unknown>\n");
पूर्ण

/*
 * show_scaling_governor - show the current policy क्रम the specअगरied CPU
 */
अटल sमाप_प्रकार show_scaling_governor(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	अगर (policy->policy == CPUFREQ_POLICY_POWERSAVE)
		वापस प्र_लिखो(buf, "powersave\n");
	अन्यथा अगर (policy->policy == CPUFREQ_POLICY_PERFORMANCE)
		वापस प्र_लिखो(buf, "performance\n");
	अन्यथा अगर (policy->governor)
		वापस scnम_लिखो(buf, CPUFREQ_NAME_PLEN, "%s\n",
				policy->governor->name);
	वापस -EINVAL;
पूर्ण

/*
 * store_scaling_governor - store policy क्रम the specअगरied CPU
 */
अटल sमाप_प्रकार store_scaling_governor(काष्ठा cpufreq_policy *policy,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अक्षर str_governor[16];
	पूर्णांक ret;

	ret = माला_पूछो(buf, "%15s", str_governor);
	अगर (ret != 1)
		वापस -EINVAL;

	अगर (cpufreq_driver->setpolicy) अणु
		अचिन्हित पूर्णांक new_pol;

		new_pol = cpufreq_parse_policy(str_governor);
		अगर (!new_pol)
			वापस -EINVAL;

		ret = cpufreq_set_policy(policy, शून्य, new_pol);
	पूर्ण अन्यथा अणु
		काष्ठा cpufreq_governor *new_gov;

		new_gov = cpufreq_parse_governor(str_governor);
		अगर (!new_gov)
			वापस -EINVAL;

		ret = cpufreq_set_policy(policy, new_gov,
					 CPUFREQ_POLICY_UNKNOWN);

		module_put(new_gov->owner);
	पूर्ण

	वापस ret ? ret : count;
पूर्ण

/*
 * show_scaling_driver - show the cpufreq driver currently loaded
 */
अटल sमाप_प्रकार show_scaling_driver(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, CPUFREQ_NAME_PLEN, "%s\n", cpufreq_driver->name);
पूर्ण

/*
 * show_scaling_available_governors - show the available CPUfreq governors
 */
अटल sमाप_प्रकार show_scaling_available_governors(काष्ठा cpufreq_policy *policy,
						अक्षर *buf)
अणु
	sमाप_प्रकार i = 0;
	काष्ठा cpufreq_governor *t;

	अगर (!has_target()) अणु
		i += प्र_लिखो(buf, "performance powersave");
		जाओ out;
	पूर्ण

	mutex_lock(&cpufreq_governor_mutex);
	क्रम_each_governor(t) अणु
		अगर (i >= (sमाप_प्रकार) ((PAGE_SIZE / माप(अक्षर))
		    - (CPUFREQ_NAME_LEN + 2)))
			अवरोध;
		i += scnम_लिखो(&buf[i], CPUFREQ_NAME_PLEN, "%s ", t->name);
	पूर्ण
	mutex_unlock(&cpufreq_governor_mutex);
out:
	i += प्र_लिखो(&buf[i], "\n");
	वापस i;
पूर्ण

sमाप_प्रकार cpufreq_show_cpus(स्थिर काष्ठा cpumask *mask, अक्षर *buf)
अणु
	sमाप_प्रकार i = 0;
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask) अणु
		अगर (i)
			i += scnम_लिखो(&buf[i], (PAGE_SIZE - i - 2), " ");
		i += scnम_लिखो(&buf[i], (PAGE_SIZE - i - 2), "%u", cpu);
		अगर (i >= (PAGE_SIZE - 5))
			अवरोध;
	पूर्ण
	i += प्र_लिखो(&buf[i], "\n");
	वापस i;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_show_cpus);

/*
 * show_related_cpus - show the CPUs affected by each transition even अगर
 * hw coordination is in use
 */
अटल sमाप_प्रकार show_related_cpus(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	वापस cpufreq_show_cpus(policy->related_cpus, buf);
पूर्ण

/*
 * show_affected_cpus - show the CPUs affected by each transition
 */
अटल sमाप_प्रकार show_affected_cpus(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	वापस cpufreq_show_cpus(policy->cpus, buf);
पूर्ण

अटल sमाप_प्रकार store_scaling_setspeed(काष्ठा cpufreq_policy *policy,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक freq = 0;
	अचिन्हित पूर्णांक ret;

	अगर (!policy->governor || !policy->governor->store_setspeed)
		वापस -EINVAL;

	ret = माला_पूछो(buf, "%u", &freq);
	अगर (ret != 1)
		वापस -EINVAL;

	policy->governor->store_setspeed(policy, freq);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_scaling_setspeed(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	अगर (!policy->governor || !policy->governor->show_setspeed)
		वापस प्र_लिखो(buf, "<unsupported>\n");

	वापस policy->governor->show_setspeed(policy, buf);
पूर्ण

/*
 * show_bios_limit - show the current cpufreq HW/BIOS limitation
 */
अटल sमाप_प्रकार show_bios_limit(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक limit;
	पूर्णांक ret;
	ret = cpufreq_driver->bios_limit(policy->cpu, &limit);
	अगर (!ret)
		वापस प्र_लिखो(buf, "%u\n", limit);
	वापस प्र_लिखो(buf, "%u\n", policy->cpuinfo.max_freq);
पूर्ण

cpufreq_freq_attr_ro_perm(cpuinfo_cur_freq, 0400);
cpufreq_freq_attr_ro(cpuinfo_min_freq);
cpufreq_freq_attr_ro(cpuinfo_max_freq);
cpufreq_freq_attr_ro(cpuinfo_transition_latency);
cpufreq_freq_attr_ro(scaling_available_governors);
cpufreq_freq_attr_ro(scaling_driver);
cpufreq_freq_attr_ro(scaling_cur_freq);
cpufreq_freq_attr_ro(bios_limit);
cpufreq_freq_attr_ro(related_cpus);
cpufreq_freq_attr_ro(affected_cpus);
cpufreq_freq_attr_rw(scaling_min_freq);
cpufreq_freq_attr_rw(scaling_max_freq);
cpufreq_freq_attr_rw(scaling_governor);
cpufreq_freq_attr_rw(scaling_setspeed);

अटल काष्ठा attribute *शेष_attrs[] = अणु
	&cpuinfo_min_freq.attr,
	&cpuinfo_max_freq.attr,
	&cpuinfo_transition_latency.attr,
	&scaling_min_freq.attr,
	&scaling_max_freq.attr,
	&affected_cpus.attr,
	&related_cpus.attr,
	&scaling_governor.attr,
	&scaling_driver.attr,
	&scaling_available_governors.attr,
	&scaling_setspeed.attr,
	शून्य
पूर्ण;

#घोषणा to_policy(k) container_of(k, काष्ठा cpufreq_policy, kobj)
#घोषणा to_attr(a) container_of(a, काष्ठा freq_attr, attr)

अटल sमाप_प्रकार show(काष्ठा kobject *kobj, काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा cpufreq_policy *policy = to_policy(kobj);
	काष्ठा freq_attr *fattr = to_attr(attr);
	sमाप_प्रकार ret;

	अगर (!fattr->show)
		वापस -EIO;

	करोwn_पढ़ो(&policy->rwsem);
	ret = fattr->show(policy, buf);
	up_पढ़ो(&policy->rwsem);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
		     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cpufreq_policy *policy = to_policy(kobj);
	काष्ठा freq_attr *fattr = to_attr(attr);
	sमाप_प्रकार ret = -EINVAL;

	अगर (!fattr->store)
		वापस -EIO;

	/*
	 * cpus_पढ़ो_trylock() is used here to work around a circular lock
	 * dependency problem with respect to the cpufreq_रेजिस्टर_driver().
	 */
	अगर (!cpus_पढ़ो_trylock())
		वापस -EBUSY;

	अगर (cpu_online(policy->cpu)) अणु
		करोwn_ग_लिखो(&policy->rwsem);
		ret = fattr->store(policy, buf, count);
		up_ग_लिखो(&policy->rwsem);
	पूर्ण

	cpus_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल व्योम cpufreq_sysfs_release(काष्ठा kobject *kobj)
अणु
	काष्ठा cpufreq_policy *policy = to_policy(kobj);
	pr_debug("last reference is dropped\n");
	complete(&policy->kobj_unरेजिस्टर);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops sysfs_ops = अणु
	.show	= show,
	.store	= store,
पूर्ण;

अटल काष्ठा kobj_type ktype_cpufreq = अणु
	.sysfs_ops	= &sysfs_ops,
	.शेष_attrs	= शेष_attrs,
	.release	= cpufreq_sysfs_release,
पूर्ण;

अटल व्योम add_cpu_dev_symlink(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *dev = get_cpu_device(cpu);

	अगर (unlikely(!dev))
		वापस;

	अगर (cpumask_test_and_set_cpu(cpu, policy->real_cpus))
		वापस;

	dev_dbg(dev, "%s: Adding symlink\n", __func__);
	अगर (sysfs_create_link(&dev->kobj, &policy->kobj, "cpufreq"))
		dev_err(dev, "cpufreq symlink creation failed\n");
पूर्ण

अटल व्योम हटाओ_cpu_dev_symlink(काष्ठा cpufreq_policy *policy,
				   काष्ठा device *dev)
अणु
	dev_dbg(dev, "%s: Removing symlink\n", __func__);
	sysfs_हटाओ_link(&dev->kobj, "cpufreq");
पूर्ण

अटल पूर्णांक cpufreq_add_dev_पूर्णांकerface(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा freq_attr **drv_attr;
	पूर्णांक ret = 0;

	/* set up files क्रम this cpu device */
	drv_attr = cpufreq_driver->attr;
	जबतक (drv_attr && *drv_attr) अणु
		ret = sysfs_create_file(&policy->kobj, &((*drv_attr)->attr));
		अगर (ret)
			वापस ret;
		drv_attr++;
	पूर्ण
	अगर (cpufreq_driver->get) अणु
		ret = sysfs_create_file(&policy->kobj, &cpuinfo_cur_freq.attr);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = sysfs_create_file(&policy->kobj, &scaling_cur_freq.attr);
	अगर (ret)
		वापस ret;

	अगर (cpufreq_driver->bios_limit) अणु
		ret = sysfs_create_file(&policy->kobj, &bios_limit.attr);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpufreq_init_policy(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpufreq_governor *gov = शून्य;
	अचिन्हित पूर्णांक pol = CPUFREQ_POLICY_UNKNOWN;
	पूर्णांक ret;

	अगर (has_target()) अणु
		/* Update policy governor to the one used beक्रमe hotplug. */
		gov = get_governor(policy->last_governor);
		अगर (gov) अणु
			pr_debug("Restoring governor %s for cpu %d\n",
				 gov->name, policy->cpu);
		पूर्ण अन्यथा अणु
			gov = get_governor(शेष_governor);
		पूर्ण

		अगर (!gov) अणु
			gov = cpufreq_शेष_governor();
			__module_get(gov->owner);
		पूर्ण

	पूर्ण अन्यथा अणु

		/* Use the शेष policy अगर there is no last_policy. */
		अगर (policy->last_policy) अणु
			pol = policy->last_policy;
		पूर्ण अन्यथा अणु
			pol = cpufreq_parse_policy(शेष_governor);
			/*
			 * In हाल the शेष governor is neither "performance"
			 * nor "powersave", fall back to the initial policy
			 * value set by the driver.
			 */
			अगर (pol == CPUFREQ_POLICY_UNKNOWN)
				pol = policy->policy;
		पूर्ण
		अगर (pol != CPUFREQ_POLICY_PERFORMANCE &&
		    pol != CPUFREQ_POLICY_POWERSAVE)
			वापस -ENODATA;
	पूर्ण

	ret = cpufreq_set_policy(policy, gov, pol);
	अगर (gov)
		module_put(gov->owner);

	वापस ret;
पूर्ण

अटल पूर्णांक cpufreq_add_policy_cpu(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक ret = 0;

	/* Has this CPU been taken care of alपढ़ोy? */
	अगर (cpumask_test_cpu(cpu, policy->cpus))
		वापस 0;

	करोwn_ग_लिखो(&policy->rwsem);
	अगर (has_target())
		cpufreq_stop_governor(policy);

	cpumask_set_cpu(cpu, policy->cpus);

	अगर (has_target()) अणु
		ret = cpufreq_start_governor(policy);
		अगर (ret)
			pr_err("%s: Failed to start governor\n", __func__);
	पूर्ण
	up_ग_लिखो(&policy->rwsem);
	वापस ret;
पूर्ण

व्योम refresh_frequency_limits(काष्ठा cpufreq_policy *policy)
अणु
	अगर (!policy_is_inactive(policy)) अणु
		pr_debug("updating policy for CPU %u\n", policy->cpu);

		cpufreq_set_policy(policy, policy->governor, policy->policy);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(refresh_frequency_limits);

अटल व्योम handle_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cpufreq_policy *policy =
		container_of(work, काष्ठा cpufreq_policy, update);

	pr_debug("handle_update for cpu %u called\n", policy->cpu);
	करोwn_ग_लिखो(&policy->rwsem);
	refresh_frequency_limits(policy);
	up_ग_लिखो(&policy->rwsem);
पूर्ण

अटल पूर्णांक cpufreq_notअगरier_min(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ freq,
				व्योम *data)
अणु
	काष्ठा cpufreq_policy *policy = container_of(nb, काष्ठा cpufreq_policy, nb_min);

	schedule_work(&policy->update);
	वापस 0;
पूर्ण

अटल पूर्णांक cpufreq_notअगरier_max(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ freq,
				व्योम *data)
अणु
	काष्ठा cpufreq_policy *policy = container_of(nb, काष्ठा cpufreq_policy, nb_max);

	schedule_work(&policy->update);
	वापस 0;
पूर्ण

अटल व्योम cpufreq_policy_put_kobj(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा kobject *kobj;
	काष्ठा completion *cmp;

	करोwn_ग_लिखो(&policy->rwsem);
	cpufreq_stats_मुक्त_table(policy);
	kobj = &policy->kobj;
	cmp = &policy->kobj_unरेजिस्टर;
	up_ग_लिखो(&policy->rwsem);
	kobject_put(kobj);

	/*
	 * We need to make sure that the underlying kobj is
	 * actually not referenced anymore by anybody beक्रमe we
	 * proceed with unloading.
	 */
	pr_debug("waiting for dropping of refcount\n");
	रुको_क्रम_completion(cmp);
	pr_debug("wait complete\n");
पूर्ण

अटल काष्ठा cpufreq_policy *cpufreq_policy_alloc(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy;
	काष्ठा device *dev = get_cpu_device(cpu);
	पूर्णांक ret;

	अगर (!dev)
		वापस शून्य;

	policy = kzalloc(माप(*policy), GFP_KERNEL);
	अगर (!policy)
		वापस शून्य;

	अगर (!alloc_cpumask_var(&policy->cpus, GFP_KERNEL))
		जाओ err_मुक्त_policy;

	अगर (!zalloc_cpumask_var(&policy->related_cpus, GFP_KERNEL))
		जाओ err_मुक्त_cpumask;

	अगर (!zalloc_cpumask_var(&policy->real_cpus, GFP_KERNEL))
		जाओ err_मुक्त_rcpumask;

	ret = kobject_init_and_add(&policy->kobj, &ktype_cpufreq,
				   cpufreq_global_kobject, "policy%u", cpu);
	अगर (ret) अणु
		dev_err(dev, "%s: failed to init policy->kobj: %d\n", __func__, ret);
		/*
		 * The entire policy object will be मुक्तd below, but the extra
		 * memory allocated क्रम the kobject name needs to be मुक्तd by
		 * releasing the kobject.
		 */
		kobject_put(&policy->kobj);
		जाओ err_मुक्त_real_cpus;
	पूर्ण

	freq_स्थिरraपूर्णांकs_init(&policy->स्थिरraपूर्णांकs);

	policy->nb_min.notअगरier_call = cpufreq_notअगरier_min;
	policy->nb_max.notअगरier_call = cpufreq_notअगरier_max;

	ret = freq_qos_add_notअगरier(&policy->स्थिरraपूर्णांकs, FREQ_QOS_MIN,
				    &policy->nb_min);
	अगर (ret) अणु
		dev_err(dev, "Failed to register MIN QoS notifier: %d (%*pbl)\n",
			ret, cpumask_pr_args(policy->cpus));
		जाओ err_kobj_हटाओ;
	पूर्ण

	ret = freq_qos_add_notअगरier(&policy->स्थिरraपूर्णांकs, FREQ_QOS_MAX,
				    &policy->nb_max);
	अगर (ret) अणु
		dev_err(dev, "Failed to register MAX QoS notifier: %d (%*pbl)\n",
			ret, cpumask_pr_args(policy->cpus));
		जाओ err_min_qos_notअगरier;
	पूर्ण

	INIT_LIST_HEAD(&policy->policy_list);
	init_rwsem(&policy->rwsem);
	spin_lock_init(&policy->transition_lock);
	init_रुकोqueue_head(&policy->transition_रुको);
	init_completion(&policy->kobj_unरेजिस्टर);
	INIT_WORK(&policy->update, handle_update);

	policy->cpu = cpu;
	वापस policy;

err_min_qos_notअगरier:
	freq_qos_हटाओ_notअगरier(&policy->स्थिरraपूर्णांकs, FREQ_QOS_MIN,
				 &policy->nb_min);
err_kobj_हटाओ:
	cpufreq_policy_put_kobj(policy);
err_मुक्त_real_cpus:
	मुक्त_cpumask_var(policy->real_cpus);
err_मुक्त_rcpumask:
	मुक्त_cpumask_var(policy->related_cpus);
err_मुक्त_cpumask:
	मुक्त_cpumask_var(policy->cpus);
err_मुक्त_policy:
	kमुक्त(policy);

	वापस शून्य;
पूर्ण

अटल व्योम cpufreq_policy_मुक्त(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक cpu;

	/* Remove policy from list */
	ग_लिखो_lock_irqsave(&cpufreq_driver_lock, flags);
	list_del(&policy->policy_list);

	क्रम_each_cpu(cpu, policy->related_cpus)
		per_cpu(cpufreq_cpu_data, cpu) = शून्य;
	ग_लिखो_unlock_irqrestore(&cpufreq_driver_lock, flags);

	freq_qos_हटाओ_notअगरier(&policy->स्थिरraपूर्णांकs, FREQ_QOS_MAX,
				 &policy->nb_max);
	freq_qos_हटाओ_notअगरier(&policy->स्थिरraपूर्णांकs, FREQ_QOS_MIN,
				 &policy->nb_min);

	/* Cancel any pending policy->update work beक्रमe मुक्तing the policy. */
	cancel_work_sync(&policy->update);

	अगर (policy->max_freq_req) अणु
		/*
		 * CPUFREQ_CREATE_POLICY notअगरication is sent only after
		 * successfully adding max_freq_req request.
		 */
		blocking_notअगरier_call_chain(&cpufreq_policy_notअगरier_list,
					     CPUFREQ_REMOVE_POLICY, policy);
		freq_qos_हटाओ_request(policy->max_freq_req);
	पूर्ण

	freq_qos_हटाओ_request(policy->min_freq_req);
	kमुक्त(policy->min_freq_req);

	cpufreq_policy_put_kobj(policy);
	मुक्त_cpumask_var(policy->real_cpus);
	मुक्त_cpumask_var(policy->related_cpus);
	मुक्त_cpumask_var(policy->cpus);
	kमुक्त(policy);
पूर्ण

अटल पूर्णांक cpufreq_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy;
	bool new_policy;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक j;
	पूर्णांक ret;

	pr_debug("%s: bringing CPU%u online\n", __func__, cpu);

	/* Check अगर this CPU alपढ़ोy has a policy to manage it */
	policy = per_cpu(cpufreq_cpu_data, cpu);
	अगर (policy) अणु
		WARN_ON(!cpumask_test_cpu(cpu, policy->related_cpus));
		अगर (!policy_is_inactive(policy))
			वापस cpufreq_add_policy_cpu(policy, cpu);

		/* This is the only online CPU क्रम the policy.  Start over. */
		new_policy = false;
		करोwn_ग_लिखो(&policy->rwsem);
		policy->cpu = cpu;
		policy->governor = शून्य;
		up_ग_लिखो(&policy->rwsem);
	पूर्ण अन्यथा अणु
		new_policy = true;
		policy = cpufreq_policy_alloc(cpu);
		अगर (!policy)
			वापस -ENOMEM;
	पूर्ण

	अगर (!new_policy && cpufreq_driver->online) अणु
		ret = cpufreq_driver->online(policy);
		अगर (ret) अणु
			pr_debug("%s: %d: initialization failed\n", __func__,
				 __LINE__);
			जाओ out_निकास_policy;
		पूर्ण

		/* Recover policy->cpus using related_cpus */
		cpumask_copy(policy->cpus, policy->related_cpus);
	पूर्ण अन्यथा अणु
		cpumask_copy(policy->cpus, cpumask_of(cpu));

		/*
		 * Call driver. From then on the cpufreq must be able
		 * to accept all calls to ->verअगरy and ->setpolicy क्रम this CPU.
		 */
		ret = cpufreq_driver->init(policy);
		अगर (ret) अणु
			pr_debug("%s: %d: initialization failed\n", __func__,
				 __LINE__);
			जाओ out_मुक्त_policy;
		पूर्ण

		ret = cpufreq_table_validate_and_sort(policy);
		अगर (ret)
			जाओ out_निकास_policy;

		/* related_cpus should at least include policy->cpus. */
		cpumask_copy(policy->related_cpus, policy->cpus);
	पूर्ण

	करोwn_ग_लिखो(&policy->rwsem);
	/*
	 * affected cpus must always be the one, which are online. We aren't
	 * managing offline cpus here.
	 */
	cpumask_and(policy->cpus, policy->cpus, cpu_online_mask);

	अगर (new_policy) अणु
		क्रम_each_cpu(j, policy->related_cpus) अणु
			per_cpu(cpufreq_cpu_data, j) = policy;
			add_cpu_dev_symlink(policy, j);
		पूर्ण

		policy->min_freq_req = kzalloc(2 * माप(*policy->min_freq_req),
					       GFP_KERNEL);
		अगर (!policy->min_freq_req) अणु
			ret = -ENOMEM;
			जाओ out_destroy_policy;
		पूर्ण

		ret = freq_qos_add_request(&policy->स्थिरraपूर्णांकs,
					   policy->min_freq_req, FREQ_QOS_MIN,
					   policy->min);
		अगर (ret < 0) अणु
			/*
			 * So we करोn't call freq_qos_हटाओ_request() क्रम an
			 * uninitialized request.
			 */
			kमुक्त(policy->min_freq_req);
			policy->min_freq_req = शून्य;
			जाओ out_destroy_policy;
		पूर्ण

		/*
		 * This must be initialized right here to aव्योम calling
		 * freq_qos_हटाओ_request() on uninitialized request in हाल
		 * of errors.
		 */
		policy->max_freq_req = policy->min_freq_req + 1;

		ret = freq_qos_add_request(&policy->स्थिरraपूर्णांकs,
					   policy->max_freq_req, FREQ_QOS_MAX,
					   policy->max);
		अगर (ret < 0) अणु
			policy->max_freq_req = शून्य;
			जाओ out_destroy_policy;
		पूर्ण

		blocking_notअगरier_call_chain(&cpufreq_policy_notअगरier_list,
				CPUFREQ_CREATE_POLICY, policy);
	पूर्ण

	अगर (cpufreq_driver->get && has_target()) अणु
		policy->cur = cpufreq_driver->get(policy->cpu);
		अगर (!policy->cur) अणु
			ret = -EIO;
			pr_err("%s: ->get() failed\n", __func__);
			जाओ out_destroy_policy;
		पूर्ण
	पूर्ण

	/*
	 * Someबार boot loaders set CPU frequency to a value outside of
	 * frequency table present with cpufreq core. In such हालs CPU might be
	 * unstable अगर it has to run on that frequency क्रम दीर्घ duration of समय
	 * and so its better to set it to a frequency which is specअगरied in
	 * freq-table. This also makes cpufreq stats inconsistent as
	 * cpufreq-stats would fail to रेजिस्टर because current frequency of CPU
	 * isn't found in freq-table.
	 *
	 * Because we करोn't want this change to effect boot process badly, we go
	 * क्रम the next freq which is >= policy->cur ('cur' must be set by now,
	 * otherwise we will end up setting freq to lowest of the table as 'cur'
	 * is initialized to zero).
	 *
	 * We are passing target-freq as "policy->cur - 1" otherwise
	 * __cpufreq_driver_target() would simply fail, as policy->cur will be
	 * equal to target-freq.
	 */
	अगर ((cpufreq_driver->flags & CPUFREQ_NEED_INITIAL_FREQ_CHECK)
	    && has_target()) अणु
		अचिन्हित पूर्णांक old_freq = policy->cur;

		/* Are we running at unknown frequency ? */
		ret = cpufreq_frequency_table_get_index(policy, old_freq);
		अगर (ret == -EINVAL) अणु
			ret = __cpufreq_driver_target(policy, old_freq - 1,
						      CPUFREQ_RELATION_L);

			/*
			 * Reaching here after boot in a few seconds may not
			 * mean that प्रणाली will reमुख्य stable at "unknown"
			 * frequency क्रम दीर्घer duration. Hence, a BUG_ON().
			 */
			BUG_ON(ret);
			pr_info("%s: CPU%d: Running at unlisted initial frequency: %u KHz, changing to: %u KHz\n",
				__func__, policy->cpu, old_freq, policy->cur);
		पूर्ण
	पूर्ण

	अगर (new_policy) अणु
		ret = cpufreq_add_dev_पूर्णांकerface(policy);
		अगर (ret)
			जाओ out_destroy_policy;

		cpufreq_stats_create_table(policy);

		ग_लिखो_lock_irqsave(&cpufreq_driver_lock, flags);
		list_add(&policy->policy_list, &cpufreq_policy_list);
		ग_लिखो_unlock_irqrestore(&cpufreq_driver_lock, flags);
	पूर्ण

	ret = cpufreq_init_policy(policy);
	अगर (ret) अणु
		pr_err("%s: Failed to initialize policy for cpu: %d (%d)\n",
		       __func__, cpu, ret);
		जाओ out_destroy_policy;
	पूर्ण

	up_ग_लिखो(&policy->rwsem);

	kobject_uevent(&policy->kobj, KOBJ_ADD);

	/* Callback क्रम handling stuff after policy is पढ़ोy */
	अगर (cpufreq_driver->पढ़ोy)
		cpufreq_driver->पढ़ोy(policy);

	अगर (cpufreq_thermal_control_enabled(cpufreq_driver))
		policy->cdev = of_cpufreq_cooling_रेजिस्टर(policy);

	pr_debug("initialization complete\n");

	वापस 0;

out_destroy_policy:
	क्रम_each_cpu(j, policy->real_cpus)
		हटाओ_cpu_dev_symlink(policy, get_cpu_device(j));

	up_ग_लिखो(&policy->rwsem);

out_निकास_policy:
	अगर (cpufreq_driver->निकास)
		cpufreq_driver->निकास(policy);

out_मुक्त_policy:
	cpufreq_policy_मुक्त(policy);
	वापस ret;
पूर्ण

/**
 * cpufreq_add_dev - the cpufreq पूर्णांकerface क्रम a CPU device.
 * @dev: CPU device.
 * @sअगर: Subप्रणाली पूर्णांकerface काष्ठाure poपूर्णांकer (not used)
 */
अटल पूर्णांक cpufreq_add_dev(काष्ठा device *dev, काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	काष्ठा cpufreq_policy *policy;
	अचिन्हित cpu = dev->id;
	पूर्णांक ret;

	dev_dbg(dev, "%s: adding CPU%u\n", __func__, cpu);

	अगर (cpu_online(cpu)) अणु
		ret = cpufreq_online(cpu);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Create sysfs link on CPU registration */
	policy = per_cpu(cpufreq_cpu_data, cpu);
	अगर (policy)
		add_cpu_dev_symlink(policy, cpu);

	वापस 0;
पूर्ण

अटल पूर्णांक cpufreq_offline(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy;
	पूर्णांक ret;

	pr_debug("%s: unregistering CPU %u\n", __func__, cpu);

	policy = cpufreq_cpu_get_raw(cpu);
	अगर (!policy) अणु
		pr_debug("%s: No cpu_data found\n", __func__);
		वापस 0;
	पूर्ण

	करोwn_ग_लिखो(&policy->rwsem);
	अगर (has_target())
		cpufreq_stop_governor(policy);

	cpumask_clear_cpu(cpu, policy->cpus);

	अगर (policy_is_inactive(policy)) अणु
		अगर (has_target())
			म_नकलन(policy->last_governor, policy->governor->name,
				CPUFREQ_NAME_LEN);
		अन्यथा
			policy->last_policy = policy->policy;
	पूर्ण अन्यथा अगर (cpu == policy->cpu) अणु
		/* Nominate new CPU */
		policy->cpu = cpumask_any(policy->cpus);
	पूर्ण

	/* Start governor again क्रम active policy */
	अगर (!policy_is_inactive(policy)) अणु
		अगर (has_target()) अणु
			ret = cpufreq_start_governor(policy);
			अगर (ret)
				pr_err("%s: Failed to start governor\n", __func__);
		पूर्ण

		जाओ unlock;
	पूर्ण

	अगर (cpufreq_thermal_control_enabled(cpufreq_driver)) अणु
		cpufreq_cooling_unरेजिस्टर(policy->cdev);
		policy->cdev = शून्य;
	पूर्ण

	अगर (cpufreq_driver->stop_cpu)
		cpufreq_driver->stop_cpu(policy);

	अगर (has_target())
		cpufreq_निकास_governor(policy);

	/*
	 * Perक्रमm the ->offline() during light-weight tear-करोwn, as
	 * that allows fast recovery when the CPU comes back.
	 */
	अगर (cpufreq_driver->offline) अणु
		cpufreq_driver->offline(policy);
	पूर्ण अन्यथा अगर (cpufreq_driver->निकास) अणु
		cpufreq_driver->निकास(policy);
		policy->freq_table = शून्य;
	पूर्ण

unlock:
	up_ग_लिखो(&policy->rwsem);
	वापस 0;
पूर्ण

/*
 * cpufreq_हटाओ_dev - हटाओ a CPU device
 *
 * Removes the cpufreq पूर्णांकerface क्रम a CPU device.
 */
अटल व्योम cpufreq_हटाओ_dev(काष्ठा device *dev, काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	अचिन्हित पूर्णांक cpu = dev->id;
	काष्ठा cpufreq_policy *policy = per_cpu(cpufreq_cpu_data, cpu);

	अगर (!policy)
		वापस;

	अगर (cpu_online(cpu))
		cpufreq_offline(cpu);

	cpumask_clear_cpu(cpu, policy->real_cpus);
	हटाओ_cpu_dev_symlink(policy, dev);

	अगर (cpumask_empty(policy->real_cpus)) अणु
		/* We did light-weight निकास earlier, करो full tear करोwn now */
		अगर (cpufreq_driver->offline)
			cpufreq_driver->निकास(policy);

		cpufreq_policy_मुक्त(policy);
	पूर्ण
पूर्ण

/**
 * cpufreq_out_of_sync - Fix up actual and saved CPU frequency dअगरference.
 * @policy: Policy managing CPUs.
 * @new_freq: New CPU frequency.
 *
 * Adjust to the current frequency first and clean up later by either calling
 * cpufreq_update_policy(), or scheduling handle_update().
 */
अटल व्योम cpufreq_out_of_sync(काष्ठा cpufreq_policy *policy,
				अचिन्हित पूर्णांक new_freq)
अणु
	काष्ठा cpufreq_freqs freqs;

	pr_debug("Warning: CPU frequency out of sync: cpufreq and timing core thinks of %u, is %u kHz\n",
		 policy->cur, new_freq);

	freqs.old = policy->cur;
	freqs.new = new_freq;

	cpufreq_freq_transition_begin(policy, &freqs);
	cpufreq_freq_transition_end(policy, &freqs, 0);
पूर्ण

अटल अचिन्हित पूर्णांक cpufreq_verअगरy_current_freq(काष्ठा cpufreq_policy *policy, bool update)
अणु
	अचिन्हित पूर्णांक new_freq;

	new_freq = cpufreq_driver->get(policy->cpu);
	अगर (!new_freq)
		वापस 0;

	/*
	 * If fast frequency चयनing is used with the given policy, the check
	 * against policy->cur is poपूर्णांकless, so skip it in that हाल.
	 */
	अगर (policy->fast_चयन_enabled || !has_target())
		वापस new_freq;

	अगर (policy->cur != new_freq) अणु
		cpufreq_out_of_sync(policy, new_freq);
		अगर (update)
			schedule_work(&policy->update);
	पूर्ण

	वापस new_freq;
पूर्ण

/**
 * cpufreq_quick_get - get the CPU frequency (in kHz) from policy->cur
 * @cpu: CPU number
 *
 * This is the last known freq, without actually getting it from the driver.
 * Return value will be same as what is shown in scaling_cur_freq in sysfs.
 */
अचिन्हित पूर्णांक cpufreq_quick_get(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy;
	अचिन्हित पूर्णांक ret_freq = 0;
	अचिन्हित दीर्घ flags;

	पढ़ो_lock_irqsave(&cpufreq_driver_lock, flags);

	अगर (cpufreq_driver && cpufreq_driver->setpolicy && cpufreq_driver->get) अणु
		ret_freq = cpufreq_driver->get(cpu);
		पढ़ो_unlock_irqrestore(&cpufreq_driver_lock, flags);
		वापस ret_freq;
	पूर्ण

	पढ़ो_unlock_irqrestore(&cpufreq_driver_lock, flags);

	policy = cpufreq_cpu_get(cpu);
	अगर (policy) अणु
		ret_freq = policy->cur;
		cpufreq_cpu_put(policy);
	पूर्ण

	वापस ret_freq;
पूर्ण
EXPORT_SYMBOL(cpufreq_quick_get);

/**
 * cpufreq_quick_get_max - get the max reported CPU frequency क्रम this CPU
 * @cpu: CPU number
 *
 * Just वापस the max possible frequency क्रम a given CPU.
 */
अचिन्हित पूर्णांक cpufreq_quick_get_max(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy = cpufreq_cpu_get(cpu);
	अचिन्हित पूर्णांक ret_freq = 0;

	अगर (policy) अणु
		ret_freq = policy->max;
		cpufreq_cpu_put(policy);
	पूर्ण

	वापस ret_freq;
पूर्ण
EXPORT_SYMBOL(cpufreq_quick_get_max);

/**
 * cpufreq_get_hw_max_freq - get the max hardware frequency of the CPU
 * @cpu: CPU number
 *
 * The शेष वापस value is the max_freq field of cpuinfo.
 */
__weak अचिन्हित पूर्णांक cpufreq_get_hw_max_freq(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy = cpufreq_cpu_get(cpu);
	अचिन्हित पूर्णांक ret_freq = 0;

	अगर (policy) अणु
		ret_freq = policy->cpuinfo.max_freq;
		cpufreq_cpu_put(policy);
	पूर्ण

	वापस ret_freq;
पूर्ण
EXPORT_SYMBOL(cpufreq_get_hw_max_freq);

अटल अचिन्हित पूर्णांक __cpufreq_get(काष्ठा cpufreq_policy *policy)
अणु
	अगर (unlikely(policy_is_inactive(policy)))
		वापस 0;

	वापस cpufreq_verअगरy_current_freq(policy, true);
पूर्ण

/**
 * cpufreq_get - get the current CPU frequency (in kHz)
 * @cpu: CPU number
 *
 * Get the CPU current (अटल) CPU frequency
 */
अचिन्हित पूर्णांक cpufreq_get(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy = cpufreq_cpu_get(cpu);
	अचिन्हित पूर्णांक ret_freq = 0;

	अगर (policy) अणु
		करोwn_पढ़ो(&policy->rwsem);
		अगर (cpufreq_driver->get)
			ret_freq = __cpufreq_get(policy);
		up_पढ़ो(&policy->rwsem);

		cpufreq_cpu_put(policy);
	पूर्ण

	वापस ret_freq;
पूर्ण
EXPORT_SYMBOL(cpufreq_get);

अटल काष्ठा subsys_पूर्णांकerface cpufreq_पूर्णांकerface = अणु
	.name		= "cpufreq",
	.subsys		= &cpu_subsys,
	.add_dev	= cpufreq_add_dev,
	.हटाओ_dev	= cpufreq_हटाओ_dev,
पूर्ण;

/*
 * In हाल platक्रमm wants some specअगरic frequency to be configured
 * during suspend..
 */
पूर्णांक cpufreq_generic_suspend(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक ret;

	अगर (!policy->suspend_freq) अणु
		pr_debug("%s: suspend_freq not defined\n", __func__);
		वापस 0;
	पूर्ण

	pr_debug("%s: Setting suspend-freq: %u\n", __func__,
			policy->suspend_freq);

	ret = __cpufreq_driver_target(policy, policy->suspend_freq,
			CPUFREQ_RELATION_H);
	अगर (ret)
		pr_err("%s: unable to set suspend-freq: %u. err: %d\n",
				__func__, policy->suspend_freq, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(cpufreq_generic_suspend);

/**
 * cpufreq_suspend() - Suspend CPUFreq governors.
 *
 * Called during प्रणाली wide Suspend/Hibernate cycles क्रम suspending governors
 * as some platक्रमms can't change frequency after this poपूर्णांक in suspend cycle.
 * Because some of the devices (like: i2c, regulators, etc) they use क्रम
 * changing frequency are suspended quickly after this poपूर्णांक.
 */
व्योम cpufreq_suspend(व्योम)
अणु
	काष्ठा cpufreq_policy *policy;

	अगर (!cpufreq_driver)
		वापस;

	अगर (!has_target() && !cpufreq_driver->suspend)
		जाओ suspend;

	pr_debug("%s: Suspending Governors\n", __func__);

	क्रम_each_active_policy(policy) अणु
		अगर (has_target()) अणु
			करोwn_ग_लिखो(&policy->rwsem);
			cpufreq_stop_governor(policy);
			up_ग_लिखो(&policy->rwsem);
		पूर्ण

		अगर (cpufreq_driver->suspend && cpufreq_driver->suspend(policy))
			pr_err("%s: Failed to suspend driver: %s\n", __func__,
				cpufreq_driver->name);
	पूर्ण

suspend:
	cpufreq_suspended = true;
पूर्ण

/**
 * cpufreq_resume() - Resume CPUFreq governors.
 *
 * Called during प्रणाली wide Suspend/Hibernate cycle क्रम resuming governors that
 * are suspended with cpufreq_suspend().
 */
व्योम cpufreq_resume(व्योम)
अणु
	काष्ठा cpufreq_policy *policy;
	पूर्णांक ret;

	अगर (!cpufreq_driver)
		वापस;

	अगर (unlikely(!cpufreq_suspended))
		वापस;

	cpufreq_suspended = false;

	अगर (!has_target() && !cpufreq_driver->resume)
		वापस;

	pr_debug("%s: Resuming Governors\n", __func__);

	क्रम_each_active_policy(policy) अणु
		अगर (cpufreq_driver->resume && cpufreq_driver->resume(policy)) अणु
			pr_err("%s: Failed to resume driver: %p\n", __func__,
				policy);
		पूर्ण अन्यथा अगर (has_target()) अणु
			करोwn_ग_लिखो(&policy->rwsem);
			ret = cpufreq_start_governor(policy);
			up_ग_लिखो(&policy->rwsem);

			अगर (ret)
				pr_err("%s: Failed to start governor for policy: %p\n",
				       __func__, policy);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * cpufreq_driver_test_flags - Test cpufreq driver's flags against given ones.
 * @flags: Flags to test against the current cpufreq driver's flags.
 *
 * Assumes that the driver is there, so callers must ensure that this is the
 * हाल.
 */
bool cpufreq_driver_test_flags(u16 flags)
अणु
	वापस !!(cpufreq_driver->flags & flags);
पूर्ण

/**
 * cpufreq_get_current_driver - Return the current driver's name.
 *
 * Return the name string of the currently रेजिस्टरed cpufreq driver or शून्य अगर
 * none.
 */
स्थिर अक्षर *cpufreq_get_current_driver(व्योम)
अणु
	अगर (cpufreq_driver)
		वापस cpufreq_driver->name;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_get_current_driver);

/**
 * cpufreq_get_driver_data - Return current driver data.
 *
 * Return the निजी data of the currently रेजिस्टरed cpufreq driver, or शून्य
 * अगर no cpufreq driver has been रेजिस्टरed.
 */
व्योम *cpufreq_get_driver_data(व्योम)
अणु
	अगर (cpufreq_driver)
		वापस cpufreq_driver->driver_data;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_get_driver_data);

/*********************************************************************
 *                     NOTIFIER LISTS INTERFACE                      *
 *********************************************************************/

/**
 * cpufreq_रेजिस्टर_notअगरier - Register a notअगरier with cpufreq.
 * @nb: notअगरier function to रेजिस्टर.
 * @list: CPUFREQ_TRANSITION_NOTIFIER or CPUFREQ_POLICY_NOTIFIER.
 *
 * Add a notअगरier to one of two lists: either a list of notअगरiers that run on
 * घड़ी rate changes (once beक्रमe and once after every transition), or a list
 * of notअगरiers that ron on cpufreq policy changes.
 *
 * This function may sleep and it has the same वापस values as
 * blocking_notअगरier_chain_रेजिस्टर().
 */
पूर्णांक cpufreq_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित पूर्णांक list)
अणु
	पूर्णांक ret;

	अगर (cpufreq_disabled())
		वापस -EINVAL;

	चयन (list) अणु
	हाल CPUFREQ_TRANSITION_NOTIFIER:
		mutex_lock(&cpufreq_fast_चयन_lock);

		अगर (cpufreq_fast_चयन_count > 0) अणु
			mutex_unlock(&cpufreq_fast_चयन_lock);
			वापस -EBUSY;
		पूर्ण
		ret = srcu_notअगरier_chain_रेजिस्टर(
				&cpufreq_transition_notअगरier_list, nb);
		अगर (!ret)
			cpufreq_fast_चयन_count--;

		mutex_unlock(&cpufreq_fast_चयन_lock);
		अवरोध;
	हाल CPUFREQ_POLICY_NOTIFIER:
		ret = blocking_notअगरier_chain_रेजिस्टर(
				&cpufreq_policy_notअगरier_list, nb);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(cpufreq_रेजिस्टर_notअगरier);

/**
 * cpufreq_unरेजिस्टर_notअगरier - Unरेजिस्टर a notअगरier from cpufreq.
 * @nb: notअगरier block to be unरेजिस्टरed.
 * @list: CPUFREQ_TRANSITION_NOTIFIER or CPUFREQ_POLICY_NOTIFIER.
 *
 * Remove a notअगरier from one of the cpufreq notअगरier lists.
 *
 * This function may sleep and it has the same वापस values as
 * blocking_notअगरier_chain_unरेजिस्टर().
 */
पूर्णांक cpufreq_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित पूर्णांक list)
अणु
	पूर्णांक ret;

	अगर (cpufreq_disabled())
		वापस -EINVAL;

	चयन (list) अणु
	हाल CPUFREQ_TRANSITION_NOTIFIER:
		mutex_lock(&cpufreq_fast_चयन_lock);

		ret = srcu_notअगरier_chain_unरेजिस्टर(
				&cpufreq_transition_notअगरier_list, nb);
		अगर (!ret && !WARN_ON(cpufreq_fast_चयन_count >= 0))
			cpufreq_fast_चयन_count++;

		mutex_unlock(&cpufreq_fast_चयन_lock);
		अवरोध;
	हाल CPUFREQ_POLICY_NOTIFIER:
		ret = blocking_notअगरier_chain_unरेजिस्टर(
				&cpufreq_policy_notअगरier_list, nb);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(cpufreq_unरेजिस्टर_notअगरier);


/*********************************************************************
 *                              GOVERNORS                            *
 *********************************************************************/

/**
 * cpufreq_driver_fast_चयन - Carry out a fast CPU frequency चयन.
 * @policy: cpufreq policy to चयन the frequency क्रम.
 * @target_freq: New frequency to set (may be approximate).
 *
 * Carry out a fast frequency चयन without sleeping.
 *
 * The driver's ->fast_चयन() callback invoked by this function must be
 * suitable क्रम being called from within RCU-sched पढ़ो-side critical sections
 * and it is expected to select the minimum available frequency greater than or
 * equal to @target_freq (CPUFREQ_RELATION_L).
 *
 * This function must not be called अगर policy->fast_चयन_enabled is unset.
 *
 * Governors calling this function must guarantee that it will never be invoked
 * twice in parallel क्रम the same policy and that it will never be called in
 * parallel with either ->target() or ->target_index() क्रम the same policy.
 *
 * Returns the actual frequency set क्रम the CPU.
 *
 * If 0 is वापसed by the driver's ->fast_चयन() callback to indicate an
 * error condition, the hardware configuration must be preserved.
 */
अचिन्हित पूर्णांक cpufreq_driver_fast_चयन(काष्ठा cpufreq_policy *policy,
					अचिन्हित पूर्णांक target_freq)
अणु
	अचिन्हित पूर्णांक freq;
	पूर्णांक cpu;

	target_freq = clamp_val(target_freq, policy->min, policy->max);
	freq = cpufreq_driver->fast_चयन(policy, target_freq);

	अगर (!freq)
		वापस 0;

	policy->cur = freq;
	arch_set_freq_scale(policy->related_cpus, freq,
			    policy->cpuinfo.max_freq);
	cpufreq_stats_record_transition(policy, freq);

	अगर (trace_cpu_frequency_enabled()) अणु
		क्रम_each_cpu(cpu, policy->cpus)
			trace_cpu_frequency(freq, cpu);
	पूर्ण

	वापस freq;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_driver_fast_चयन);

/**
 * cpufreq_driver_adjust_perf - Adjust CPU perक्रमmance level in one go.
 * @cpu: Target CPU.
 * @min_perf: Minimum (required) perक्रमmance level (units of @capacity).
 * @target_perf: Target (desired) perक्रमmance level (units of @capacity).
 * @capacity: Capacity of the target CPU.
 *
 * Carry out a fast perक्रमmance level चयन of @cpu without sleeping.
 *
 * The driver's ->adjust_perf() callback invoked by this function must be
 * suitable क्रम being called from within RCU-sched पढ़ो-side critical sections
 * and it is expected to select a suitable perक्रमmance level equal to or above
 * @min_perf and preferably equal to or below @target_perf.
 *
 * This function must not be called अगर policy->fast_चयन_enabled is unset.
 *
 * Governors calling this function must guarantee that it will never be invoked
 * twice in parallel क्रम the same CPU and that it will never be called in
 * parallel with either ->target() or ->target_index() or ->fast_चयन() क्रम
 * the same CPU.
 */
व्योम cpufreq_driver_adjust_perf(अचिन्हित पूर्णांक cpu,
				 अचिन्हित दीर्घ min_perf,
				 अचिन्हित दीर्घ target_perf,
				 अचिन्हित दीर्घ capacity)
अणु
	cpufreq_driver->adjust_perf(cpu, min_perf, target_perf, capacity);
पूर्ण

/**
 * cpufreq_driver_has_adjust_perf - Check "direct fast switch" callback.
 *
 * Return 'true' अगर the ->adjust_perf callback is present क्रम the
 * current driver or 'false' otherwise.
 */
bool cpufreq_driver_has_adjust_perf(व्योम)
अणु
	वापस !!cpufreq_driver->adjust_perf;
पूर्ण

/* Must set freqs->new to पूर्णांकermediate frequency */
अटल पूर्णांक __target_पूर्णांकermediate(काष्ठा cpufreq_policy *policy,
				 काष्ठा cpufreq_freqs *freqs, पूर्णांक index)
अणु
	पूर्णांक ret;

	freqs->new = cpufreq_driver->get_पूर्णांकermediate(policy, index);

	/* We करोn't need to चयन to पूर्णांकermediate freq */
	अगर (!freqs->new)
		वापस 0;

	pr_debug("%s: cpu: %d, switching to intermediate freq: oldfreq: %u, intermediate freq: %u\n",
		 __func__, policy->cpu, freqs->old, freqs->new);

	cpufreq_freq_transition_begin(policy, freqs);
	ret = cpufreq_driver->target_पूर्णांकermediate(policy, index);
	cpufreq_freq_transition_end(policy, freqs, ret);

	अगर (ret)
		pr_err("%s: Failed to change to intermediate frequency: %d\n",
		       __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक __target_index(काष्ठा cpufreq_policy *policy, पूर्णांक index)
अणु
	काष्ठा cpufreq_freqs freqs = अणु.old = policy->cur, .flags = 0पूर्ण;
	अचिन्हित पूर्णांक restore_freq, पूर्णांकermediate_freq = 0;
	अचिन्हित पूर्णांक newfreq = policy->freq_table[index].frequency;
	पूर्णांक retval = -EINVAL;
	bool notअगरy;

	अगर (newfreq == policy->cur)
		वापस 0;

	/* Save last value to restore later on errors */
	restore_freq = policy->cur;

	notअगरy = !(cpufreq_driver->flags & CPUFREQ_ASYNC_NOTIFICATION);
	अगर (notअगरy) अणु
		/* Handle चयनing to पूर्णांकermediate frequency */
		अगर (cpufreq_driver->get_पूर्णांकermediate) अणु
			retval = __target_पूर्णांकermediate(policy, &freqs, index);
			अगर (retval)
				वापस retval;

			पूर्णांकermediate_freq = freqs.new;
			/* Set old freq to पूर्णांकermediate */
			अगर (पूर्णांकermediate_freq)
				freqs.old = freqs.new;
		पूर्ण

		freqs.new = newfreq;
		pr_debug("%s: cpu: %d, oldfreq: %u, new freq: %u\n",
			 __func__, policy->cpu, freqs.old, freqs.new);

		cpufreq_freq_transition_begin(policy, &freqs);
	पूर्ण

	retval = cpufreq_driver->target_index(policy, index);
	अगर (retval)
		pr_err("%s: Failed to change cpu frequency: %d\n", __func__,
		       retval);

	अगर (notअगरy) अणु
		cpufreq_freq_transition_end(policy, &freqs, retval);

		/*
		 * Failed after setting to पूर्णांकermediate freq? Driver should have
		 * reverted back to initial frequency and so should we. Check
		 * here क्रम पूर्णांकermediate_freq instead of get_पूर्णांकermediate, in
		 * हाल we haven't चयनed to पूर्णांकermediate freq at all.
		 */
		अगर (unlikely(retval && पूर्णांकermediate_freq)) अणु
			freqs.old = पूर्णांकermediate_freq;
			freqs.new = restore_freq;
			cpufreq_freq_transition_begin(policy, &freqs);
			cpufreq_freq_transition_end(policy, &freqs, 0);
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

पूर्णांक __cpufreq_driver_target(काष्ठा cpufreq_policy *policy,
			    अचिन्हित पूर्णांक target_freq,
			    अचिन्हित पूर्णांक relation)
अणु
	अचिन्हित पूर्णांक old_target_freq = target_freq;
	पूर्णांक index;

	अगर (cpufreq_disabled())
		वापस -ENODEV;

	/* Make sure that target_freq is within supported range */
	target_freq = clamp_val(target_freq, policy->min, policy->max);

	pr_debug("target for CPU %u: %u kHz, relation %u, requested %u kHz\n",
		 policy->cpu, target_freq, relation, old_target_freq);

	/*
	 * This might look like a redundant call as we are checking it again
	 * after finding index. But it is left पूर्णांकentionally क्रम हालs where
	 * exactly same freq is called again and so we can save on few function
	 * calls.
	 */
	अगर (target_freq == policy->cur &&
	    !(cpufreq_driver->flags & CPUFREQ_NEED_UPDATE_LIMITS))
		वापस 0;

	अगर (cpufreq_driver->target)
		वापस cpufreq_driver->target(policy, target_freq, relation);

	अगर (!cpufreq_driver->target_index)
		वापस -EINVAL;

	index = cpufreq_frequency_table_target(policy, target_freq, relation);

	वापस __target_index(policy, index);
पूर्ण
EXPORT_SYMBOL_GPL(__cpufreq_driver_target);

पूर्णांक cpufreq_driver_target(काष्ठा cpufreq_policy *policy,
			  अचिन्हित पूर्णांक target_freq,
			  अचिन्हित पूर्णांक relation)
अणु
	पूर्णांक ret;

	करोwn_ग_लिखो(&policy->rwsem);

	ret = __cpufreq_driver_target(policy, target_freq, relation);

	up_ग_लिखो(&policy->rwsem);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_driver_target);

__weak काष्ठा cpufreq_governor *cpufreq_fallback_governor(व्योम)
अणु
	वापस शून्य;
पूर्ण

अटल पूर्णांक cpufreq_init_governor(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक ret;

	/* Don't start any governor operations अगर we are entering suspend */
	अगर (cpufreq_suspended)
		वापस 0;
	/*
	 * Governor might not be initiated here अगर ACPI _PPC changed
	 * notअगरication happened, so check it.
	 */
	अगर (!policy->governor)
		वापस -EINVAL;

	/* Platक्रमm करोesn't want dynamic frequency चयनing ? */
	अगर (policy->governor->flags & CPUFREQ_GOV_DYNAMIC_SWITCHING &&
	    cpufreq_driver->flags & CPUFREQ_NO_AUTO_DYNAMIC_SWITCHING) अणु
		काष्ठा cpufreq_governor *gov = cpufreq_fallback_governor();

		अगर (gov) अणु
			pr_warn("Can't use %s governor as dynamic switching is disallowed. Fallback to %s governor\n",
				policy->governor->name, gov->name);
			policy->governor = gov;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!try_module_get(policy->governor->owner))
		वापस -EINVAL;

	pr_debug("%s: for CPU %u\n", __func__, policy->cpu);

	अगर (policy->governor->init) अणु
		ret = policy->governor->init(policy);
		अगर (ret) अणु
			module_put(policy->governor->owner);
			वापस ret;
		पूर्ण
	पूर्ण

	policy->strict_target = !!(policy->governor->flags & CPUFREQ_GOV_STRICT_TARGET);

	वापस 0;
पूर्ण

अटल व्योम cpufreq_निकास_governor(काष्ठा cpufreq_policy *policy)
अणु
	अगर (cpufreq_suspended || !policy->governor)
		वापस;

	pr_debug("%s: for CPU %u\n", __func__, policy->cpu);

	अगर (policy->governor->निकास)
		policy->governor->निकास(policy);

	module_put(policy->governor->owner);
पूर्ण

पूर्णांक cpufreq_start_governor(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक ret;

	अगर (cpufreq_suspended)
		वापस 0;

	अगर (!policy->governor)
		वापस -EINVAL;

	pr_debug("%s: for CPU %u\n", __func__, policy->cpu);

	अगर (cpufreq_driver->get)
		cpufreq_verअगरy_current_freq(policy, false);

	अगर (policy->governor->start) अणु
		ret = policy->governor->start(policy);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (policy->governor->limits)
		policy->governor->limits(policy);

	वापस 0;
पूर्ण

व्योम cpufreq_stop_governor(काष्ठा cpufreq_policy *policy)
अणु
	अगर (cpufreq_suspended || !policy->governor)
		वापस;

	pr_debug("%s: for CPU %u\n", __func__, policy->cpu);

	अगर (policy->governor->stop)
		policy->governor->stop(policy);
पूर्ण

अटल व्योम cpufreq_governor_limits(काष्ठा cpufreq_policy *policy)
अणु
	अगर (cpufreq_suspended || !policy->governor)
		वापस;

	pr_debug("%s: for CPU %u\n", __func__, policy->cpu);

	अगर (policy->governor->limits)
		policy->governor->limits(policy);
पूर्ण

पूर्णांक cpufreq_रेजिस्टर_governor(काष्ठा cpufreq_governor *governor)
अणु
	पूर्णांक err;

	अगर (!governor)
		वापस -EINVAL;

	अगर (cpufreq_disabled())
		वापस -ENODEV;

	mutex_lock(&cpufreq_governor_mutex);

	err = -EBUSY;
	अगर (!find_governor(governor->name)) अणु
		err = 0;
		list_add(&governor->governor_list, &cpufreq_governor_list);
	पूर्ण

	mutex_unlock(&cpufreq_governor_mutex);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_रेजिस्टर_governor);

व्योम cpufreq_unरेजिस्टर_governor(काष्ठा cpufreq_governor *governor)
अणु
	काष्ठा cpufreq_policy *policy;
	अचिन्हित दीर्घ flags;

	अगर (!governor)
		वापस;

	अगर (cpufreq_disabled())
		वापस;

	/* clear last_governor क्रम all inactive policies */
	पढ़ो_lock_irqsave(&cpufreq_driver_lock, flags);
	क्रम_each_inactive_policy(policy) अणु
		अगर (!म_भेद(policy->last_governor, governor->name)) अणु
			policy->governor = शून्य;
			म_नकल(policy->last_governor, "\0");
		पूर्ण
	पूर्ण
	पढ़ो_unlock_irqrestore(&cpufreq_driver_lock, flags);

	mutex_lock(&cpufreq_governor_mutex);
	list_del(&governor->governor_list);
	mutex_unlock(&cpufreq_governor_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_unरेजिस्टर_governor);


/*********************************************************************
 *                          POLICY INTERFACE                         *
 *********************************************************************/

/**
 * cpufreq_get_policy - get the current cpufreq_policy
 * @policy: काष्ठा cpufreq_policy पूर्णांकo which the current cpufreq_policy
 *	is written
 * @cpu: CPU to find the policy क्रम
 *
 * Reads the current cpufreq policy.
 */
पूर्णांक cpufreq_get_policy(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *cpu_policy;
	अगर (!policy)
		वापस -EINVAL;

	cpu_policy = cpufreq_cpu_get(cpu);
	अगर (!cpu_policy)
		वापस -EINVAL;

	स_नकल(policy, cpu_policy, माप(*policy));

	cpufreq_cpu_put(cpu_policy);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cpufreq_get_policy);

/**
 * cpufreq_set_policy - Modअगरy cpufreq policy parameters.
 * @policy: Policy object to modअगरy.
 * @new_gov: Policy governor poपूर्णांकer.
 * @new_pol: Policy value (क्रम drivers with built-in governors).
 *
 * Invoke the cpufreq driver's ->verअगरy() callback to sanity-check the frequency
 * limits to be set क्रम the policy, update @policy with the verअगरied limits
 * values and either invoke the driver's ->setpolicy() callback (अगर present) or
 * carry out a governor update क्रम @policy.  That is, run the current governor's
 * ->limits() callback (अगर @new_gov poपूर्णांकs to the same object as the one in
 * @policy) or replace the governor क्रम @policy with @new_gov.
 *
 * The cpuinfo part of @policy is not updated by this function.
 */
अटल पूर्णांक cpufreq_set_policy(काष्ठा cpufreq_policy *policy,
			      काष्ठा cpufreq_governor *new_gov,
			      अचिन्हित पूर्णांक new_pol)
अणु
	काष्ठा cpufreq_policy_data new_data;
	काष्ठा cpufreq_governor *old_gov;
	पूर्णांक ret;

	स_नकल(&new_data.cpuinfo, &policy->cpuinfo, माप(policy->cpuinfo));
	new_data.freq_table = policy->freq_table;
	new_data.cpu = policy->cpu;
	/*
	 * PM QoS framework collects all the requests from users and provide us
	 * the final aggregated value here.
	 */
	new_data.min = freq_qos_पढ़ो_value(&policy->स्थिरraपूर्णांकs, FREQ_QOS_MIN);
	new_data.max = freq_qos_पढ़ो_value(&policy->स्थिरraपूर्णांकs, FREQ_QOS_MAX);

	pr_debug("setting new policy for CPU %u: %u - %u kHz\n",
		 new_data.cpu, new_data.min, new_data.max);

	/*
	 * Verअगरy that the CPU speed can be set within these limits and make sure
	 * that min <= max.
	 */
	ret = cpufreq_driver->verअगरy(&new_data);
	अगर (ret)
		वापस ret;

	policy->min = new_data.min;
	policy->max = new_data.max;
	trace_cpu_frequency_limits(policy);

	policy->cached_target_freq = अच_पूर्णांक_उच्च;

	pr_debug("new min and max freqs are %u - %u kHz\n",
		 policy->min, policy->max);

	अगर (cpufreq_driver->setpolicy) अणु
		policy->policy = new_pol;
		pr_debug("setting range\n");
		वापस cpufreq_driver->setpolicy(policy);
	पूर्ण

	अगर (new_gov == policy->governor) अणु
		pr_debug("governor limits update\n");
		cpufreq_governor_limits(policy);
		वापस 0;
	पूर्ण

	pr_debug("governor switch\n");

	/* save old, working values */
	old_gov = policy->governor;
	/* end old governor */
	अगर (old_gov) अणु
		cpufreq_stop_governor(policy);
		cpufreq_निकास_governor(policy);
	पूर्ण

	/* start new governor */
	policy->governor = new_gov;
	ret = cpufreq_init_governor(policy);
	अगर (!ret) अणु
		ret = cpufreq_start_governor(policy);
		अगर (!ret) अणु
			pr_debug("governor change\n");
			sched_cpufreq_governor_change(policy, old_gov);
			वापस 0;
		पूर्ण
		cpufreq_निकास_governor(policy);
	पूर्ण

	/* new governor failed, so re-start old one */
	pr_debug("starting governor %s failed\n", policy->governor->name);
	अगर (old_gov) अणु
		policy->governor = old_gov;
		अगर (cpufreq_init_governor(policy))
			policy->governor = शून्य;
		अन्यथा
			cpufreq_start_governor(policy);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * cpufreq_update_policy - Re-evaluate an existing cpufreq policy.
 * @cpu: CPU to re-evaluate the policy क्रम.
 *
 * Update the current frequency क्रम the cpufreq policy of @cpu and use
 * cpufreq_set_policy() to re-apply the min and max limits, which triggers the
 * evaluation of policy notअगरiers and the cpufreq driver's ->verअगरy() callback
 * क्रम the policy in question, among other things.
 */
व्योम cpufreq_update_policy(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy = cpufreq_cpu_acquire(cpu);

	अगर (!policy)
		वापस;

	/*
	 * BIOS might change freq behind our back
	 * -> ask driver क्रम current freq and notअगरy governors about a change
	 */
	अगर (cpufreq_driver->get && has_target() &&
	    (cpufreq_suspended || WARN_ON(!cpufreq_verअगरy_current_freq(policy, false))))
		जाओ unlock;

	refresh_frequency_limits(policy);

unlock:
	cpufreq_cpu_release(policy);
पूर्ण
EXPORT_SYMBOL(cpufreq_update_policy);

/**
 * cpufreq_update_limits - Update policy limits क्रम a given CPU.
 * @cpu: CPU to update the policy limits क्रम.
 *
 * Invoke the driver's ->update_limits callback अगर present or call
 * cpufreq_update_policy() क्रम @cpu.
 */
व्योम cpufreq_update_limits(अचिन्हित पूर्णांक cpu)
अणु
	अगर (cpufreq_driver->update_limits)
		cpufreq_driver->update_limits(cpu);
	अन्यथा
		cpufreq_update_policy(cpu);
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_update_limits);

/*********************************************************************
 *               BOOST						     *
 *********************************************************************/
अटल पूर्णांक cpufreq_boost_set_sw(काष्ठा cpufreq_policy *policy, पूर्णांक state)
अणु
	पूर्णांक ret;

	अगर (!policy->freq_table)
		वापस -ENXIO;

	ret = cpufreq_frequency_table_cpuinfo(policy, policy->freq_table);
	अगर (ret) अणु
		pr_err("%s: Policy frequency update failed\n", __func__);
		वापस ret;
	पूर्ण

	ret = freq_qos_update_request(policy->max_freq_req, policy->max);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक cpufreq_boost_trigger_state(पूर्णांक state)
अणु
	काष्ठा cpufreq_policy *policy;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (cpufreq_driver->boost_enabled == state)
		वापस 0;

	ग_लिखो_lock_irqsave(&cpufreq_driver_lock, flags);
	cpufreq_driver->boost_enabled = state;
	ग_लिखो_unlock_irqrestore(&cpufreq_driver_lock, flags);

	get_online_cpus();
	क्रम_each_active_policy(policy) अणु
		ret = cpufreq_driver->set_boost(policy, state);
		अगर (ret)
			जाओ err_reset_state;
	पूर्ण
	put_online_cpus();

	वापस 0;

err_reset_state:
	put_online_cpus();

	ग_लिखो_lock_irqsave(&cpufreq_driver_lock, flags);
	cpufreq_driver->boost_enabled = !state;
	ग_लिखो_unlock_irqrestore(&cpufreq_driver_lock, flags);

	pr_err("%s: Cannot %s BOOST\n",
	       __func__, state ? "enable" : "disable");

	वापस ret;
पूर्ण

अटल bool cpufreq_boost_supported(व्योम)
अणु
	वापस cpufreq_driver->set_boost;
पूर्ण

अटल पूर्णांक create_boost_sysfs_file(व्योम)
अणु
	पूर्णांक ret;

	ret = sysfs_create_file(cpufreq_global_kobject, &boost.attr);
	अगर (ret)
		pr_err("%s: cannot register global BOOST sysfs file\n",
		       __func__);

	वापस ret;
पूर्ण

अटल व्योम हटाओ_boost_sysfs_file(व्योम)
अणु
	अगर (cpufreq_boost_supported())
		sysfs_हटाओ_file(cpufreq_global_kobject, &boost.attr);
पूर्ण

पूर्णांक cpufreq_enable_boost_support(व्योम)
अणु
	अगर (!cpufreq_driver)
		वापस -EINVAL;

	अगर (cpufreq_boost_supported())
		वापस 0;

	cpufreq_driver->set_boost = cpufreq_boost_set_sw;

	/* This will get हटाओd on driver unरेजिस्टर */
	वापस create_boost_sysfs_file();
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_enable_boost_support);

पूर्णांक cpufreq_boost_enabled(व्योम)
अणु
	वापस cpufreq_driver->boost_enabled;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_boost_enabled);

/*********************************************************************
 *               REGISTER / UNREGISTER CPUFREQ DRIVER                *
 *********************************************************************/
अटल क्रमागत cpuhp_state hp_online;

अटल पूर्णांक cpuhp_cpufreq_online(अचिन्हित पूर्णांक cpu)
अणु
	cpufreq_online(cpu);

	वापस 0;
पूर्ण

अटल पूर्णांक cpuhp_cpufreq_offline(अचिन्हित पूर्णांक cpu)
अणु
	cpufreq_offline(cpu);

	वापस 0;
पूर्ण

/**
 * cpufreq_रेजिस्टर_driver - रेजिस्टर a CPU Frequency driver
 * @driver_data: A काष्ठा cpufreq_driver containing the values#
 * submitted by the CPU Frequency driver.
 *
 * Registers a CPU Frequency driver to this core code. This code
 * वापसs zero on success, -EEXIST when another driver got here first
 * (and isn't unरेजिस्टरed in the meanसमय).
 *
 */
पूर्णांक cpufreq_रेजिस्टर_driver(काष्ठा cpufreq_driver *driver_data)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (cpufreq_disabled())
		वापस -ENODEV;

	/*
	 * The cpufreq core depends heavily on the availability of device
	 * काष्ठाure, make sure they are available beक्रमe proceeding further.
	 */
	अगर (!get_cpu_device(0))
		वापस -EPROBE_DEFER;

	अगर (!driver_data || !driver_data->verअगरy || !driver_data->init ||
	    !(driver_data->setpolicy || driver_data->target_index ||
		    driver_data->target) ||
	     (driver_data->setpolicy && (driver_data->target_index ||
		    driver_data->target)) ||
	     (!driver_data->get_पूर्णांकermediate != !driver_data->target_पूर्णांकermediate) ||
	     (!driver_data->online != !driver_data->offline))
		वापस -EINVAL;

	pr_debug("trying to register driver %s\n", driver_data->name);

	/* Protect against concurrent CPU online/offline. */
	cpus_पढ़ो_lock();

	ग_लिखो_lock_irqsave(&cpufreq_driver_lock, flags);
	अगर (cpufreq_driver) अणु
		ग_लिखो_unlock_irqrestore(&cpufreq_driver_lock, flags);
		ret = -EEXIST;
		जाओ out;
	पूर्ण
	cpufreq_driver = driver_data;
	ग_लिखो_unlock_irqrestore(&cpufreq_driver_lock, flags);

	/*
	 * Mark support क्रम the scheduler's frequency invariance engine क्रम
	 * drivers that implement target(), target_index() or fast_चयन().
	 */
	अगर (!cpufreq_driver->setpolicy) अणु
		अटल_branch_enable_cpuslocked(&cpufreq_freq_invariance);
		pr_debug("supports frequency invariance");
	पूर्ण

	अगर (driver_data->setpolicy)
		driver_data->flags |= CPUFREQ_CONST_LOOPS;

	अगर (cpufreq_boost_supported()) अणु
		ret = create_boost_sysfs_file();
		अगर (ret)
			जाओ err_null_driver;
	पूर्ण

	ret = subsys_पूर्णांकerface_रेजिस्टर(&cpufreq_पूर्णांकerface);
	अगर (ret)
		जाओ err_boost_unreg;

	अगर (unlikely(list_empty(&cpufreq_policy_list))) अणु
		/* अगर all ->init() calls failed, unरेजिस्टर */
		ret = -ENODEV;
		pr_debug("%s: No CPU initialized for driver %s\n", __func__,
			 driver_data->name);
		जाओ err_अगर_unreg;
	पूर्ण

	ret = cpuhp_setup_state_nocalls_cpuslocked(CPUHP_AP_ONLINE_DYN,
						   "cpufreq:online",
						   cpuhp_cpufreq_online,
						   cpuhp_cpufreq_offline);
	अगर (ret < 0)
		जाओ err_अगर_unreg;
	hp_online = ret;
	ret = 0;

	pr_debug("driver %s up and running\n", driver_data->name);
	जाओ out;

err_अगर_unreg:
	subsys_पूर्णांकerface_unरेजिस्टर(&cpufreq_पूर्णांकerface);
err_boost_unreg:
	हटाओ_boost_sysfs_file();
err_null_driver:
	ग_लिखो_lock_irqsave(&cpufreq_driver_lock, flags);
	cpufreq_driver = शून्य;
	ग_लिखो_unlock_irqrestore(&cpufreq_driver_lock, flags);
out:
	cpus_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_रेजिस्टर_driver);

/*
 * cpufreq_unरेजिस्टर_driver - unरेजिस्टर the current CPUFreq driver
 *
 * Unरेजिस्टर the current CPUFreq driver. Only call this अगर you have
 * the right to करो so, i.e. अगर you have succeeded in initialising beक्रमe!
 * Returns zero अगर successful, and -EINVAL अगर the cpufreq_driver is
 * currently not initialised.
 */
पूर्णांक cpufreq_unरेजिस्टर_driver(काष्ठा cpufreq_driver *driver)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!cpufreq_driver || (driver != cpufreq_driver))
		वापस -EINVAL;

	pr_debug("unregistering driver %s\n", driver->name);

	/* Protect against concurrent cpu hotplug */
	cpus_पढ़ो_lock();
	subsys_पूर्णांकerface_unरेजिस्टर(&cpufreq_पूर्णांकerface);
	हटाओ_boost_sysfs_file();
	अटल_branch_disable_cpuslocked(&cpufreq_freq_invariance);
	cpuhp_हटाओ_state_nocalls_cpuslocked(hp_online);

	ग_लिखो_lock_irqsave(&cpufreq_driver_lock, flags);

	cpufreq_driver = शून्य;

	ग_लिखो_unlock_irqrestore(&cpufreq_driver_lock, flags);
	cpus_पढ़ो_unlock();

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_unरेजिस्टर_driver);

अटल पूर्णांक __init cpufreq_core_init(व्योम)
अणु
	काष्ठा cpufreq_governor *gov = cpufreq_शेष_governor();

	अगर (cpufreq_disabled())
		वापस -ENODEV;

	cpufreq_global_kobject = kobject_create_and_add("cpufreq", &cpu_subsys.dev_root->kobj);
	BUG_ON(!cpufreq_global_kobject);

	अगर (!म_माप(शेष_governor))
		म_नकलन(शेष_governor, gov->name, CPUFREQ_NAME_LEN);

	वापस 0;
पूर्ण
module_param(off, पूर्णांक, 0444);
module_param_string(शेष_governor, शेष_governor, CPUFREQ_NAME_LEN, 0444);
core_initcall(cpufreq_core_init);
