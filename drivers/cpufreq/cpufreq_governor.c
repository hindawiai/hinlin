<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/cpufreq/cpufreq_governor.c
 *
 * CPUFREQ governors common code
 *
 * Copyright	(C) 2001 Russell King
 *		(C) 2003 Venkatesh Pallipadi <venkatesh.pallipadi@पूर्णांकel.com>.
 *		(C) 2003 Jun Nakajima <jun.nakajima@पूर्णांकel.com>
 *		(C) 2009 Alexander Clouter <alex@digriz.org.uk>
 *		(c) 2012 Viresh Kumar <viresh.kumar@linaro.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/export.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/slab.h>

#समावेश "cpufreq_governor.h"

#घोषणा CPUFREQ_DBS_MIN_SAMPLING_INTERVAL	(2 * TICK_NSEC / NSEC_PER_USEC)

अटल DEFINE_PER_CPU(काष्ठा cpu_dbs_info, cpu_dbs);

अटल DEFINE_MUTEX(gov_dbs_data_mutex);

/* Common sysfs tunables */
/*
 * store_sampling_rate - update sampling rate effective immediately अगर needed.
 *
 * If new rate is smaller than the old, simply updating
 * dbs.sampling_rate might not be appropriate. For example, अगर the
 * original sampling_rate was 1 second and the requested new sampling rate is 10
 * ms because the user needs immediate reaction from ondemand governor, but not
 * sure अगर higher frequency will be required or not, then, the governor may
 * change the sampling rate too late; up to 1 second later. Thus, अगर we are
 * reducing the sampling rate, we need to make the new value effective
 * immediately.
 *
 * This must be called with dbs_data->mutex held, otherwise traversing
 * policy_dbs_list isn't safe.
 */
sमाप_प्रकार store_sampling_rate(काष्ठा gov_attr_set *attr_set, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	काष्ठा dbs_data *dbs_data = to_dbs_data(attr_set);
	काष्ठा policy_dbs_info *policy_dbs;
	अचिन्हित पूर्णांक sampling_पूर्णांकerval;
	पूर्णांक ret;

	ret = माला_पूछो(buf, "%u", &sampling_पूर्णांकerval);
	अगर (ret != 1 || sampling_पूर्णांकerval < CPUFREQ_DBS_MIN_SAMPLING_INTERVAL)
		वापस -EINVAL;

	dbs_data->sampling_rate = sampling_पूर्णांकerval;

	/*
	 * We are operating under dbs_data->mutex and so the list and its
	 * entries can't be मुक्तd concurrently.
	 */
	list_क्रम_each_entry(policy_dbs, &attr_set->policy_list, list) अणु
		mutex_lock(&policy_dbs->update_mutex);
		/*
		 * On 32-bit architectures this may race with the
		 * sample_delay_ns पढ़ो in dbs_update_util_handler(), but that
		 * really करोesn't matter.  If the read returns a value that's
		 * too big, the sample will be skipped, but the next invocation
		 * of dbs_update_util_handler() (when the update has been
		 * completed) will take a sample.
		 *
		 * If this runs in parallel with dbs_work_handler(), we may end
		 * up overwriting the sample_delay_ns value that it has just
		 * written, but it will be corrected next समय a sample is
		 * taken, so it shouldn't be signअगरicant.
		 */
		gov_update_sample_delay(policy_dbs, 0);
		mutex_unlock(&policy_dbs->update_mutex);
	पूर्ण

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(store_sampling_rate);

/**
 * gov_update_cpu_data - Update CPU load data.
 * @dbs_data: Top-level governor data poपूर्णांकer.
 *
 * Update CPU load data क्रम all CPUs in the करोमुख्य governed by @dbs_data
 * (that may be a single policy or a bunch of them अगर governor tunables are
 * प्रणाली-wide).
 *
 * Call under the @dbs_data mutex.
 */
व्योम gov_update_cpu_data(काष्ठा dbs_data *dbs_data)
अणु
	काष्ठा policy_dbs_info *policy_dbs;

	list_क्रम_each_entry(policy_dbs, &dbs_data->attr_set.policy_list, list) अणु
		अचिन्हित पूर्णांक j;

		क्रम_each_cpu(j, policy_dbs->policy->cpus) अणु
			काष्ठा cpu_dbs_info *j_cdbs = &per_cpu(cpu_dbs, j);

			j_cdbs->prev_cpu_idle = get_cpu_idle_समय(j, &j_cdbs->prev_update_समय,
								  dbs_data->io_is_busy);
			अगर (dbs_data->ignore_nice_load)
				j_cdbs->prev_cpu_nice = kcpustat_field(&kcpustat_cpu(j), CPUTIME_NICE, j);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(gov_update_cpu_data);

अचिन्हित पूर्णांक dbs_update(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा policy_dbs_info *policy_dbs = policy->governor_data;
	काष्ठा dbs_data *dbs_data = policy_dbs->dbs_data;
	अचिन्हित पूर्णांक ignore_nice = dbs_data->ignore_nice_load;
	अचिन्हित पूर्णांक max_load = 0, idle_periods = अच_पूर्णांक_उच्च;
	अचिन्हित पूर्णांक sampling_rate, io_busy, j;

	/*
	 * Someबार governors may use an additional multiplier to increase
	 * sample delays temporarily.  Apply that multiplier to sampling_rate
	 * so as to keep the wake-up-from-idle detection logic a bit
	 * conservative.
	 */
	sampling_rate = dbs_data->sampling_rate * policy_dbs->rate_mult;
	/*
	 * For the purpose of ondemand, रुकोing क्रम disk IO is an indication
	 * that you're perक्रमmance critical, and not that the प्रणाली is actually
	 * idle, so करो not add the ioरुको समय to the CPU idle समय then.
	 */
	io_busy = dbs_data->io_is_busy;

	/* Get Absolute Load */
	क्रम_each_cpu(j, policy->cpus) अणु
		काष्ठा cpu_dbs_info *j_cdbs = &per_cpu(cpu_dbs, j);
		u64 update_समय, cur_idle_समय;
		अचिन्हित पूर्णांक idle_समय, समय_elapsed;
		अचिन्हित पूर्णांक load;

		cur_idle_समय = get_cpu_idle_समय(j, &update_समय, io_busy);

		समय_elapsed = update_समय - j_cdbs->prev_update_समय;
		j_cdbs->prev_update_समय = update_समय;

		idle_समय = cur_idle_समय - j_cdbs->prev_cpu_idle;
		j_cdbs->prev_cpu_idle = cur_idle_समय;

		अगर (ignore_nice) अणु
			u64 cur_nice = kcpustat_field(&kcpustat_cpu(j), CPUTIME_NICE, j);

			idle_समय += भाग_u64(cur_nice - j_cdbs->prev_cpu_nice, NSEC_PER_USEC);
			j_cdbs->prev_cpu_nice = cur_nice;
		पूर्ण

		अगर (unlikely(!समय_elapsed)) अणु
			/*
			 * That can only happen when this function is called
			 * twice in a row with a very लघु पूर्णांकerval between the
			 * calls, so the previous load value can be used then.
			 */
			load = j_cdbs->prev_load;
		पूर्ण अन्यथा अगर (unlikely((पूर्णांक)idle_समय > 2 * sampling_rate &&
				    j_cdbs->prev_load)) अणु
			/*
			 * If the CPU had gone completely idle and a task has
			 * just woken up on this CPU now, it would be unfair to
			 * calculate 'load' the usual way क्रम this elapsed
			 * समय-winकरोw, because it would show near-zero load,
			 * irrespective of how CPU पूर्णांकensive that task actually
			 * was. This is undesirable क्रम latency-sensitive bursty
			 * workloads.
			 *
			 * To aव्योम this, reuse the 'load' from the previous
			 * समय-winकरोw and give this task a chance to start with
			 * a reasonably high CPU frequency. However, that
			 * shouldn't be over-करोne, lest we get stuck at a high
			 * load (high frequency) क्रम too दीर्घ, even when the
			 * current प्रणाली load has actually dropped करोwn, so
			 * clear prev_load to guarantee that the load will be
			 * computed again next समय.
			 *
			 * Detecting this situation is easy: an unusually large
			 * 'idle_time' (as compared to the sampling rate)
			 * indicates this scenario.
			 */
			load = j_cdbs->prev_load;
			j_cdbs->prev_load = 0;
		पूर्ण अन्यथा अणु
			अगर (समय_elapsed >= idle_समय) अणु
				load = 100 * (समय_elapsed - idle_समय) / समय_elapsed;
			पूर्ण अन्यथा अणु
				/*
				 * That can happen अगर idle_समय is वापसed by
				 * get_cpu_idle_समय_jअगरfy().  In that हाल
				 * idle_समय is roughly equal to the dअगरference
				 * between समय_elapsed and "busy time" obtained
				 * from CPU statistics.  Then, the "busy time"
				 * can end up being greater than समय_elapsed
				 * (क्रम example, अगर jअगरfies_64 and the CPU
				 * statistics are updated by dअगरferent CPUs),
				 * so idle_समय may in fact be negative.  That
				 * means, though, that the CPU was busy all
				 * the समय (on the rough average) during the
				 * last sampling पूर्णांकerval and 100 can be
				 * वापसed as the load.
				 */
				load = (पूर्णांक)idle_समय < 0 ? 100 : 0;
			पूर्ण
			j_cdbs->prev_load = load;
		पूर्ण

		अगर (unlikely((पूर्णांक)idle_समय > 2 * sampling_rate)) अणु
			अचिन्हित पूर्णांक periods = idle_समय / sampling_rate;

			अगर (periods < idle_periods)
				idle_periods = periods;
		पूर्ण

		अगर (load > max_load)
			max_load = load;
	पूर्ण

	policy_dbs->idle_periods = idle_periods;

	वापस max_load;
पूर्ण
EXPORT_SYMBOL_GPL(dbs_update);

अटल व्योम dbs_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा policy_dbs_info *policy_dbs;
	काष्ठा cpufreq_policy *policy;
	काष्ठा dbs_governor *gov;

	policy_dbs = container_of(work, काष्ठा policy_dbs_info, work);
	policy = policy_dbs->policy;
	gov = dbs_governor_of(policy);

	/*
	 * Make sure cpufreq_governor_limits() isn't evaluating load or the
	 * ondemand governor isn't updating the sampling rate in parallel.
	 */
	mutex_lock(&policy_dbs->update_mutex);
	gov_update_sample_delay(policy_dbs, gov->gov_dbs_update(policy));
	mutex_unlock(&policy_dbs->update_mutex);

	/* Allow the utilization update handler to queue up more work. */
	atomic_set(&policy_dbs->work_count, 0);
	/*
	 * If the update below is reordered with respect to the sample delay
	 * modअगरication, the utilization update handler may end up using a stale
	 * sample delay value.
	 */
	smp_wmb();
	policy_dbs->work_in_progress = false;
पूर्ण

अटल व्योम dbs_irq_work(काष्ठा irq_work *irq_work)
अणु
	काष्ठा policy_dbs_info *policy_dbs;

	policy_dbs = container_of(irq_work, काष्ठा policy_dbs_info, irq_work);
	schedule_work_on(smp_processor_id(), &policy_dbs->work);
पूर्ण

अटल व्योम dbs_update_util_handler(काष्ठा update_util_data *data, u64 समय,
				    अचिन्हित पूर्णांक flags)
अणु
	काष्ठा cpu_dbs_info *cdbs = container_of(data, काष्ठा cpu_dbs_info, update_util);
	काष्ठा policy_dbs_info *policy_dbs = cdbs->policy_dbs;
	u64 delta_ns, lst;

	अगर (!cpufreq_this_cpu_can_update(policy_dbs->policy))
		वापस;

	/*
	 * The work may not be allowed to be queued up right now.
	 * Possible reasons:
	 * - Work has alपढ़ोy been queued up or is in progress.
	 * - It is too early (too little समय from the previous sample).
	 */
	अगर (policy_dbs->work_in_progress)
		वापस;

	/*
	 * If the पढ़ोs below are reordered beक्रमe the check above, the value
	 * of sample_delay_ns used in the computation may be stale.
	 */
	smp_rmb();
	lst = READ_ONCE(policy_dbs->last_sample_समय);
	delta_ns = समय - lst;
	अगर ((s64)delta_ns < policy_dbs->sample_delay_ns)
		वापस;

	/*
	 * If the policy is not shared, the irq_work may be queued up right away
	 * at this poपूर्णांक.  Otherwise, we need to ensure that only one of the
	 * CPUs sharing the policy will करो that.
	 */
	अगर (policy_dbs->is_shared) अणु
		अगर (!atomic_add_unless(&policy_dbs->work_count, 1, 1))
			वापस;

		/*
		 * If another CPU updated last_sample_समय in the meanसमय, we
		 * shouldn't be here, so clear the work counter and bail out.
		 */
		अगर (unlikely(lst != READ_ONCE(policy_dbs->last_sample_समय))) अणु
			atomic_set(&policy_dbs->work_count, 0);
			वापस;
		पूर्ण
	पूर्ण

	policy_dbs->last_sample_समय = समय;
	policy_dbs->work_in_progress = true;
	irq_work_queue(&policy_dbs->irq_work);
पूर्ण

अटल व्योम gov_set_update_util(काष्ठा policy_dbs_info *policy_dbs,
				अचिन्हित पूर्णांक delay_us)
अणु
	काष्ठा cpufreq_policy *policy = policy_dbs->policy;
	पूर्णांक cpu;

	gov_update_sample_delay(policy_dbs, delay_us);
	policy_dbs->last_sample_समय = 0;

	क्रम_each_cpu(cpu, policy->cpus) अणु
		काष्ठा cpu_dbs_info *cdbs = &per_cpu(cpu_dbs, cpu);

		cpufreq_add_update_util_hook(cpu, &cdbs->update_util,
					     dbs_update_util_handler);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम gov_clear_update_util(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक i;

	क्रम_each_cpu(i, policy->cpus)
		cpufreq_हटाओ_update_util_hook(i);

	synchronize_rcu();
पूर्ण

अटल काष्ठा policy_dbs_info *alloc_policy_dbs_info(काष्ठा cpufreq_policy *policy,
						     काष्ठा dbs_governor *gov)
अणु
	काष्ठा policy_dbs_info *policy_dbs;
	पूर्णांक j;

	/* Allocate memory क्रम per-policy governor data. */
	policy_dbs = gov->alloc();
	अगर (!policy_dbs)
		वापस शून्य;

	policy_dbs->policy = policy;
	mutex_init(&policy_dbs->update_mutex);
	atomic_set(&policy_dbs->work_count, 0);
	init_irq_work(&policy_dbs->irq_work, dbs_irq_work);
	INIT_WORK(&policy_dbs->work, dbs_work_handler);

	/* Set policy_dbs क्रम all CPUs, online+offline */
	क्रम_each_cpu(j, policy->related_cpus) अणु
		काष्ठा cpu_dbs_info *j_cdbs = &per_cpu(cpu_dbs, j);

		j_cdbs->policy_dbs = policy_dbs;
	पूर्ण
	वापस policy_dbs;
पूर्ण

अटल व्योम मुक्त_policy_dbs_info(काष्ठा policy_dbs_info *policy_dbs,
				 काष्ठा dbs_governor *gov)
अणु
	पूर्णांक j;

	mutex_destroy(&policy_dbs->update_mutex);

	क्रम_each_cpu(j, policy_dbs->policy->related_cpus) अणु
		काष्ठा cpu_dbs_info *j_cdbs = &per_cpu(cpu_dbs, j);

		j_cdbs->policy_dbs = शून्य;
		j_cdbs->update_util.func = शून्य;
	पूर्ण
	gov->मुक्त(policy_dbs);
पूर्ण

पूर्णांक cpufreq_dbs_governor_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा dbs_governor *gov = dbs_governor_of(policy);
	काष्ठा dbs_data *dbs_data;
	काष्ठा policy_dbs_info *policy_dbs;
	पूर्णांक ret = 0;

	/* State should be equivalent to EXIT */
	अगर (policy->governor_data)
		वापस -EBUSY;

	policy_dbs = alloc_policy_dbs_info(policy, gov);
	अगर (!policy_dbs)
		वापस -ENOMEM;

	/* Protect gov->gdbs_data against concurrent updates. */
	mutex_lock(&gov_dbs_data_mutex);

	dbs_data = gov->gdbs_data;
	अगर (dbs_data) अणु
		अगर (WARN_ON(have_governor_per_policy())) अणु
			ret = -EINVAL;
			जाओ मुक्त_policy_dbs_info;
		पूर्ण
		policy_dbs->dbs_data = dbs_data;
		policy->governor_data = policy_dbs;

		gov_attr_set_get(&dbs_data->attr_set, &policy_dbs->list);
		जाओ out;
	पूर्ण

	dbs_data = kzalloc(माप(*dbs_data), GFP_KERNEL);
	अगर (!dbs_data) अणु
		ret = -ENOMEM;
		जाओ मुक्त_policy_dbs_info;
	पूर्ण

	gov_attr_set_init(&dbs_data->attr_set, &policy_dbs->list);

	ret = gov->init(dbs_data);
	अगर (ret)
		जाओ मुक्त_policy_dbs_info;

	/*
	 * The sampling पूर्णांकerval should not be less than the transition latency
	 * of the CPU and it also cannot be too small क्रम dbs_update() to work
	 * correctly.
	 */
	dbs_data->sampling_rate = max_t(अचिन्हित पूर्णांक,
					CPUFREQ_DBS_MIN_SAMPLING_INTERVAL,
					cpufreq_policy_transition_delay_us(policy));

	अगर (!have_governor_per_policy())
		gov->gdbs_data = dbs_data;

	policy_dbs->dbs_data = dbs_data;
	policy->governor_data = policy_dbs;

	gov->kobj_type.sysfs_ops = &governor_sysfs_ops;
	ret = kobject_init_and_add(&dbs_data->attr_set.kobj, &gov->kobj_type,
				   get_governor_parent_kobj(policy),
				   "%s", gov->gov.name);
	अगर (!ret)
		जाओ out;

	/* Failure, so roll back. */
	pr_err("initialization failed (dbs_data kobject init error %d)\n", ret);

	kobject_put(&dbs_data->attr_set.kobj);

	policy->governor_data = शून्य;

	अगर (!have_governor_per_policy())
		gov->gdbs_data = शून्य;
	gov->निकास(dbs_data);
	kमुक्त(dbs_data);

मुक्त_policy_dbs_info:
	मुक्त_policy_dbs_info(policy_dbs, gov);

out:
	mutex_unlock(&gov_dbs_data_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_dbs_governor_init);

व्योम cpufreq_dbs_governor_निकास(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा dbs_governor *gov = dbs_governor_of(policy);
	काष्ठा policy_dbs_info *policy_dbs = policy->governor_data;
	काष्ठा dbs_data *dbs_data = policy_dbs->dbs_data;
	अचिन्हित पूर्णांक count;

	/* Protect gov->gdbs_data against concurrent updates. */
	mutex_lock(&gov_dbs_data_mutex);

	count = gov_attr_set_put(&dbs_data->attr_set, &policy_dbs->list);

	policy->governor_data = शून्य;

	अगर (!count) अणु
		अगर (!have_governor_per_policy())
			gov->gdbs_data = शून्य;

		gov->निकास(dbs_data);
		kमुक्त(dbs_data);
	पूर्ण

	मुक्त_policy_dbs_info(policy_dbs, gov);

	mutex_unlock(&gov_dbs_data_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_dbs_governor_निकास);

पूर्णांक cpufreq_dbs_governor_start(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा dbs_governor *gov = dbs_governor_of(policy);
	काष्ठा policy_dbs_info *policy_dbs = policy->governor_data;
	काष्ठा dbs_data *dbs_data = policy_dbs->dbs_data;
	अचिन्हित पूर्णांक sampling_rate, ignore_nice, j;
	अचिन्हित पूर्णांक io_busy;

	अगर (!policy->cur)
		वापस -EINVAL;

	policy_dbs->is_shared = policy_is_shared(policy);
	policy_dbs->rate_mult = 1;

	sampling_rate = dbs_data->sampling_rate;
	ignore_nice = dbs_data->ignore_nice_load;
	io_busy = dbs_data->io_is_busy;

	क्रम_each_cpu(j, policy->cpus) अणु
		काष्ठा cpu_dbs_info *j_cdbs = &per_cpu(cpu_dbs, j);

		j_cdbs->prev_cpu_idle = get_cpu_idle_समय(j, &j_cdbs->prev_update_समय, io_busy);
		/*
		 * Make the first invocation of dbs_update() compute the load.
		 */
		j_cdbs->prev_load = 0;

		अगर (ignore_nice)
			j_cdbs->prev_cpu_nice = kcpustat_field(&kcpustat_cpu(j), CPUTIME_NICE, j);
	पूर्ण

	gov->start(policy);

	gov_set_update_util(policy_dbs, sampling_rate);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_dbs_governor_start);

व्योम cpufreq_dbs_governor_stop(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा policy_dbs_info *policy_dbs = policy->governor_data;

	gov_clear_update_util(policy_dbs->policy);
	irq_work_sync(&policy_dbs->irq_work);
	cancel_work_sync(&policy_dbs->work);
	atomic_set(&policy_dbs->work_count, 0);
	policy_dbs->work_in_progress = false;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_dbs_governor_stop);

व्योम cpufreq_dbs_governor_limits(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा policy_dbs_info *policy_dbs;

	/* Protect gov->gdbs_data against cpufreq_dbs_governor_निकास() */
	mutex_lock(&gov_dbs_data_mutex);
	policy_dbs = policy->governor_data;
	अगर (!policy_dbs)
		जाओ out;

	mutex_lock(&policy_dbs->update_mutex);
	cpufreq_policy_apply_limits(policy);
	gov_update_sample_delay(policy_dbs, 0);
	mutex_unlock(&policy_dbs->update_mutex);

out:
	mutex_unlock(&gov_dbs_data_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_dbs_governor_limits);
