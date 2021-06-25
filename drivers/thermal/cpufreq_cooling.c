<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/drivers/thermal/cpufreq_cooling.c
 *
 *  Copyright (C) 2012	Samsung Electronics Co., Ltd(http://www.samsung.com)
 *
 *  Copyright (C) 2012-2018 Linaro Limited.
 *
 *  Authors:	Amit Daniel <amit.kachhap@linaro.org>
 *		Viresh Kumar <viresh.kumar@linaro.org>
 *
 */
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpu_cooling.h>
#समावेश <linux/device.h>
#समावेश <linux/energy_model.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>

#समावेश <trace/events/thermal.h>

/*
 * Cooling state <-> CPUFreq frequency
 *
 * Cooling states are translated to frequencies throughout this driver and this
 * is the relation between them.
 *
 * Highest cooling state corresponds to lowest possible frequency.
 *
 * i.e.
 *	level 0 --> 1st Max Freq
 *	level 1 --> 2nd Max Freq
 *	...
 */

/**
 * काष्ठा समय_in_idle - Idle समय stats
 * @समय: previous पढ़ोing of the असलolute समय that this cpu was idle
 * @बारtamp: wall समय of the last invocation of get_cpu_idle_समय_us()
 */
काष्ठा समय_in_idle अणु
	u64 समय;
	u64 बारtamp;
पूर्ण;

/**
 * काष्ठा cpufreq_cooling_device - data क्रम cooling device with cpufreq
 * @last_load: load measured by the latest call to cpufreq_get_requested_घातer()
 * @cpufreq_state: पूर्णांकeger value representing the current state of cpufreq
 *	cooling	devices.
 * @max_level: maximum cooling level. One less than total number of valid
 *	cpufreq frequencies.
 * @em: Reference on the Energy Model of the device
 * @cdev: thermal_cooling_device poपूर्णांकer to keep track of the
 *	रेजिस्टरed cooling device.
 * @policy: cpufreq policy.
 * @idle_समय: idle समय stats
 * @qos_req: PM QoS contraपूर्णांक to apply
 *
 * This काष्ठाure is required क्रम keeping inक्रमmation of each रेजिस्टरed
 * cpufreq_cooling_device.
 */
काष्ठा cpufreq_cooling_device अणु
	u32 last_load;
	अचिन्हित पूर्णांक cpufreq_state;
	अचिन्हित पूर्णांक max_level;
	काष्ठा em_perf_करोमुख्य *em;
	काष्ठा cpufreq_policy *policy;
#अगर_अघोषित CONFIG_SMP
	काष्ठा समय_in_idle *idle_समय;
#पूर्ण_अगर
	काष्ठा freq_qos_request qos_req;
पूर्ण;

#अगर_घोषित CONFIG_THERMAL_GOV_POWER_ALLOCATOR
/**
 * get_level: Find the level क्रम a particular frequency
 * @cpufreq_cdev: cpufreq_cdev क्रम which the property is required
 * @freq: Frequency
 *
 * Return: level corresponding to the frequency.
 */
अटल अचिन्हित दीर्घ get_level(काष्ठा cpufreq_cooling_device *cpufreq_cdev,
			       अचिन्हित पूर्णांक freq)
अणु
	पूर्णांक i;

	क्रम (i = cpufreq_cdev->max_level - 1; i >= 0; i--) अणु
		अगर (freq > cpufreq_cdev->em->table[i].frequency)
			अवरोध;
	पूर्ण

	वापस cpufreq_cdev->max_level - i - 1;
पूर्ण

अटल u32 cpu_freq_to_घातer(काष्ठा cpufreq_cooling_device *cpufreq_cdev,
			     u32 freq)
अणु
	पूर्णांक i;

	क्रम (i = cpufreq_cdev->max_level - 1; i >= 0; i--) अणु
		अगर (freq > cpufreq_cdev->em->table[i].frequency)
			अवरोध;
	पूर्ण

	वापस cpufreq_cdev->em->table[i + 1].घातer;
पूर्ण

अटल u32 cpu_घातer_to_freq(काष्ठा cpufreq_cooling_device *cpufreq_cdev,
			     u32 घातer)
अणु
	पूर्णांक i;

	क्रम (i = cpufreq_cdev->max_level; i > 0; i--) अणु
		अगर (घातer >= cpufreq_cdev->em->table[i].घातer)
			अवरोध;
	पूर्ण

	वापस cpufreq_cdev->em->table[i].frequency;
पूर्ण

/**
 * get_load() - get load क्रम a cpu
 * @cpufreq_cdev: काष्ठा cpufreq_cooling_device क्रम the cpu
 * @cpu: cpu number
 * @cpu_idx: index of the cpu in समय_in_idle array
 *
 * Return: The average load of cpu @cpu in percentage since this
 * function was last called.
 */
#अगर_घोषित CONFIG_SMP
अटल u32 get_load(काष्ठा cpufreq_cooling_device *cpufreq_cdev, पूर्णांक cpu,
		    पूर्णांक cpu_idx)
अणु
	अचिन्हित दीर्घ max = arch_scale_cpu_capacity(cpu);
	अचिन्हित दीर्घ util;

	util = sched_cpu_util(cpu, max);
	वापस (util * 100) / max;
पूर्ण
#अन्यथा /* !CONFIG_SMP */
अटल u32 get_load(काष्ठा cpufreq_cooling_device *cpufreq_cdev, पूर्णांक cpu,
		    पूर्णांक cpu_idx)
अणु
	u32 load;
	u64 now, now_idle, delta_समय, delta_idle;
	काष्ठा समय_in_idle *idle_समय = &cpufreq_cdev->idle_समय[cpu_idx];

	now_idle = get_cpu_idle_समय(cpu, &now, 0);
	delta_idle = now_idle - idle_समय->समय;
	delta_समय = now - idle_समय->बारtamp;

	अगर (delta_समय <= delta_idle)
		load = 0;
	अन्यथा
		load = भाग64_u64(100 * (delta_समय - delta_idle), delta_समय);

	idle_समय->समय = now_idle;
	idle_समय->बारtamp = now;

	वापस load;
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

/**
 * get_dynamic_घातer() - calculate the dynamic घातer
 * @cpufreq_cdev:	&cpufreq_cooling_device क्रम this cdev
 * @freq:	current frequency
 *
 * Return: the dynamic घातer consumed by the cpus described by
 * @cpufreq_cdev.
 */
अटल u32 get_dynamic_घातer(काष्ठा cpufreq_cooling_device *cpufreq_cdev,
			     अचिन्हित दीर्घ freq)
अणु
	u32 raw_cpu_घातer;

	raw_cpu_घातer = cpu_freq_to_घातer(cpufreq_cdev, freq);
	वापस (raw_cpu_घातer * cpufreq_cdev->last_load) / 100;
पूर्ण

/**
 * cpufreq_get_requested_घातer() - get the current घातer
 * @cdev:	&thermal_cooling_device poपूर्णांकer
 * @घातer:	poपूर्णांकer in which to store the resulting घातer
 *
 * Calculate the current घातer consumption of the cpus in milliwatts
 * and store it in @घातer.  This function should actually calculate
 * the requested घातer, but it's hard to get the frequency that
 * cpufreq would have asचिन्हित अगर there were no thermal limits.
 * Instead, we calculate the current घातer on the assumption that the
 * immediate future will look like the immediate past.
 *
 * We use the current frequency and the average load since this
 * function was last called.  In reality, there could have been
 * multiple opps since this function was last called and that affects
 * the load calculation.  While it's not perfectly accurate, this
 * simplअगरication is good enough and works.  REVISIT this, as more
 * complex code may be needed अगर experiments show that it's not
 * accurate enough.
 *
 * Return: 0 on success, -E* अगर getting the अटल घातer failed.
 */
अटल पूर्णांक cpufreq_get_requested_घातer(काष्ठा thermal_cooling_device *cdev,
				       u32 *घातer)
अणु
	अचिन्हित दीर्घ freq;
	पूर्णांक i = 0, cpu;
	u32 total_load = 0;
	काष्ठा cpufreq_cooling_device *cpufreq_cdev = cdev->devdata;
	काष्ठा cpufreq_policy *policy = cpufreq_cdev->policy;
	u32 *load_cpu = शून्य;

	freq = cpufreq_quick_get(policy->cpu);

	अगर (trace_thermal_घातer_cpu_get_घातer_enabled()) अणु
		u32 ncpus = cpumask_weight(policy->related_cpus);

		load_cpu = kसुस्मृति(ncpus, माप(*load_cpu), GFP_KERNEL);
	पूर्ण

	क्रम_each_cpu(cpu, policy->related_cpus) अणु
		u32 load;

		अगर (cpu_online(cpu))
			load = get_load(cpufreq_cdev, cpu, i);
		अन्यथा
			load = 0;

		total_load += load;
		अगर (load_cpu)
			load_cpu[i] = load;

		i++;
	पूर्ण

	cpufreq_cdev->last_load = total_load;

	*घातer = get_dynamic_घातer(cpufreq_cdev, freq);

	अगर (load_cpu) अणु
		trace_thermal_घातer_cpu_get_घातer(policy->related_cpus, freq,
						  load_cpu, i, *घातer);

		kमुक्त(load_cpu);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cpufreq_state2घातer() - convert a cpu cdev state to घातer consumed
 * @cdev:	&thermal_cooling_device poपूर्णांकer
 * @state:	cooling device state to be converted
 * @घातer:	poपूर्णांकer in which to store the resulting घातer
 *
 * Convert cooling device state @state पूर्णांकo घातer consumption in
 * milliwatts assuming 100% load.  Store the calculated घातer in
 * @घातer.
 *
 * Return: 0 on success, -EINVAL अगर the cooling device state could not
 * be converted पूर्णांकo a frequency or other -E* अगर there was an error
 * when calculating the अटल घातer.
 */
अटल पूर्णांक cpufreq_state2घातer(काष्ठा thermal_cooling_device *cdev,
			       अचिन्हित दीर्घ state, u32 *घातer)
अणु
	अचिन्हित पूर्णांक freq, num_cpus, idx;
	काष्ठा cpufreq_cooling_device *cpufreq_cdev = cdev->devdata;

	/* Request state should be less than max_level */
	अगर (state > cpufreq_cdev->max_level)
		वापस -EINVAL;

	num_cpus = cpumask_weight(cpufreq_cdev->policy->cpus);

	idx = cpufreq_cdev->max_level - state;
	freq = cpufreq_cdev->em->table[idx].frequency;
	*घातer = cpu_freq_to_घातer(cpufreq_cdev, freq) * num_cpus;

	वापस 0;
पूर्ण

/**
 * cpufreq_घातer2state() - convert घातer to a cooling device state
 * @cdev:	&thermal_cooling_device poपूर्णांकer
 * @घातer:	घातer in milliwatts to be converted
 * @state:	poपूर्णांकer in which to store the resulting state
 *
 * Calculate a cooling device state क्रम the cpus described by @cdev
 * that would allow them to consume at most @घातer mW and store it in
 * @state.  Note that this calculation depends on बाह्यal factors
 * such as the cpu load or the current अटल घातer.  Calling this
 * function with the same घातer as input can yield dअगरferent cooling
 * device states depending on those बाह्यal factors.
 *
 * Return: 0 on success, -ENODEV अगर no cpus are online or -EINVAL अगर
 * the calculated frequency could not be converted to a valid state.
 * The latter should not happen unless the frequencies available to
 * cpufreq have changed since the initialization of the cpu cooling
 * device.
 */
अटल पूर्णांक cpufreq_घातer2state(काष्ठा thermal_cooling_device *cdev,
			       u32 घातer, अचिन्हित दीर्घ *state)
अणु
	अचिन्हित पूर्णांक target_freq;
	u32 last_load, normalised_घातer;
	काष्ठा cpufreq_cooling_device *cpufreq_cdev = cdev->devdata;
	काष्ठा cpufreq_policy *policy = cpufreq_cdev->policy;

	last_load = cpufreq_cdev->last_load ?: 1;
	normalised_घातer = (घातer * 100) / last_load;
	target_freq = cpu_घातer_to_freq(cpufreq_cdev, normalised_घातer);

	*state = get_level(cpufreq_cdev, target_freq);
	trace_thermal_घातer_cpu_limit(policy->related_cpus, target_freq, *state,
				      घातer);
	वापस 0;
पूर्ण

अटल अंतरभूत bool em_is_sane(काष्ठा cpufreq_cooling_device *cpufreq_cdev,
			      काष्ठा em_perf_करोमुख्य *em) अणु
	काष्ठा cpufreq_policy *policy;
	अचिन्हित पूर्णांक nr_levels;

	अगर (!em)
		वापस false;

	policy = cpufreq_cdev->policy;
	अगर (!cpumask_equal(policy->related_cpus, em_span_cpus(em))) अणु
		pr_err("The span of pd %*pbl is misaligned with cpufreq policy %*pbl\n",
			cpumask_pr_args(em_span_cpus(em)),
			cpumask_pr_args(policy->related_cpus));
		वापस false;
	पूर्ण

	nr_levels = cpufreq_cdev->max_level + 1;
	अगर (em_pd_nr_perf_states(em) != nr_levels) अणु
		pr_err("The number of performance states in pd %*pbl (%u) doesn't match the number of cooling levels (%u)\n",
			cpumask_pr_args(em_span_cpus(em)),
			em_pd_nr_perf_states(em), nr_levels);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_THERMAL_GOV_POWER_ALLOCATOR */

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत पूर्णांक allocate_idle_समय(काष्ठा cpufreq_cooling_device *cpufreq_cdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम मुक्त_idle_समय(काष्ठा cpufreq_cooling_device *cpufreq_cdev)
अणु
पूर्ण
#अन्यथा
अटल पूर्णांक allocate_idle_समय(काष्ठा cpufreq_cooling_device *cpufreq_cdev)
अणु
	अचिन्हित पूर्णांक num_cpus = cpumask_weight(cpufreq_cdev->policy->related_cpus);

	cpufreq_cdev->idle_समय = kसुस्मृति(num_cpus,
					  माप(*cpufreq_cdev->idle_समय),
					  GFP_KERNEL);
	अगर (!cpufreq_cdev->idle_समय)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_idle_समय(काष्ठा cpufreq_cooling_device *cpufreq_cdev)
अणु
	kमुक्त(cpufreq_cdev->idle_समय);
	cpufreq_cdev->idle_समय = शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल अचिन्हित पूर्णांक get_state_freq(काष्ठा cpufreq_cooling_device *cpufreq_cdev,
				   अचिन्हित दीर्घ state)
अणु
	काष्ठा cpufreq_policy *policy;
	अचिन्हित दीर्घ idx;

#अगर_घोषित CONFIG_THERMAL_GOV_POWER_ALLOCATOR
	/* Use the Energy Model table अगर available */
	अगर (cpufreq_cdev->em) अणु
		idx = cpufreq_cdev->max_level - state;
		वापस cpufreq_cdev->em->table[idx].frequency;
	पूर्ण
#पूर्ण_अगर

	/* Otherwise, fallback on the CPUFreq table */
	policy = cpufreq_cdev->policy;
	अगर (policy->freq_table_sorted == CPUFREQ_TABLE_SORTED_ASCENDING)
		idx = cpufreq_cdev->max_level - state;
	अन्यथा
		idx = state;

	वापस policy->freq_table[idx].frequency;
पूर्ण

/* cpufreq cooling device callback functions are defined below */

/**
 * cpufreq_get_max_state - callback function to get the max cooling state.
 * @cdev: thermal cooling device poपूर्णांकer.
 * @state: fill this variable with the max cooling state.
 *
 * Callback क्रम the thermal cooling device to वापस the cpufreq
 * max cooling state.
 *
 * Return: 0 on success, an error code otherwise.
 */
अटल पूर्णांक cpufreq_get_max_state(काष्ठा thermal_cooling_device *cdev,
				 अचिन्हित दीर्घ *state)
अणु
	काष्ठा cpufreq_cooling_device *cpufreq_cdev = cdev->devdata;

	*state = cpufreq_cdev->max_level;
	वापस 0;
पूर्ण

/**
 * cpufreq_get_cur_state - callback function to get the current cooling state.
 * @cdev: thermal cooling device poपूर्णांकer.
 * @state: fill this variable with the current cooling state.
 *
 * Callback क्रम the thermal cooling device to वापस the cpufreq
 * current cooling state.
 *
 * Return: 0 on success, an error code otherwise.
 */
अटल पूर्णांक cpufreq_get_cur_state(काष्ठा thermal_cooling_device *cdev,
				 अचिन्हित दीर्घ *state)
अणु
	काष्ठा cpufreq_cooling_device *cpufreq_cdev = cdev->devdata;

	*state = cpufreq_cdev->cpufreq_state;

	वापस 0;
पूर्ण

/**
 * cpufreq_set_cur_state - callback function to set the current cooling state.
 * @cdev: thermal cooling device poपूर्णांकer.
 * @state: set this variable to the current cooling state.
 *
 * Callback क्रम the thermal cooling device to change the cpufreq
 * current cooling state.
 *
 * Return: 0 on success, an error code otherwise.
 */
अटल पूर्णांक cpufreq_set_cur_state(काष्ठा thermal_cooling_device *cdev,
				 अचिन्हित दीर्घ state)
अणु
	काष्ठा cpufreq_cooling_device *cpufreq_cdev = cdev->devdata;
	काष्ठा cpumask *cpus;
	अचिन्हित पूर्णांक frequency;
	अचिन्हित दीर्घ max_capacity, capacity;
	पूर्णांक ret;

	/* Request state should be less than max_level */
	अगर (state > cpufreq_cdev->max_level)
		वापस -EINVAL;

	/* Check अगर the old cooling action is same as new cooling action */
	अगर (cpufreq_cdev->cpufreq_state == state)
		वापस 0;

	frequency = get_state_freq(cpufreq_cdev, state);

	ret = freq_qos_update_request(&cpufreq_cdev->qos_req, frequency);
	अगर (ret >= 0) अणु
		cpufreq_cdev->cpufreq_state = state;
		cpus = cpufreq_cdev->policy->cpus;
		max_capacity = arch_scale_cpu_capacity(cpumask_first(cpus));
		capacity = frequency * max_capacity;
		capacity /= cpufreq_cdev->policy->cpuinfo.max_freq;
		arch_set_thermal_pressure(cpus, max_capacity - capacity);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/* Bind cpufreq callbacks to thermal cooling device ops */

अटल काष्ठा thermal_cooling_device_ops cpufreq_cooling_ops = अणु
	.get_max_state		= cpufreq_get_max_state,
	.get_cur_state		= cpufreq_get_cur_state,
	.set_cur_state		= cpufreq_set_cur_state,
पूर्ण;

/**
 * __cpufreq_cooling_रेजिस्टर - helper function to create cpufreq cooling device
 * @np: a valid काष्ठा device_node to the cooling device device tree node
 * @policy: cpufreq policy
 * Normally this should be same as cpufreq policy->related_cpus.
 * @em: Energy Model of the cpufreq policy
 *
 * This पूर्णांकerface function रेजिस्टरs the cpufreq cooling device with the name
 * "thermal-cpufreq-%x". This api can support multiple instances of cpufreq
 * cooling devices. It also gives the opportunity to link the cooling device
 * with a device tree node, in order to bind it via the thermal DT code.
 *
 * Return: a valid काष्ठा thermal_cooling_device poपूर्णांकer on success,
 * on failure, it वापसs a corresponding ERR_PTR().
 */
अटल काष्ठा thermal_cooling_device *
__cpufreq_cooling_रेजिस्टर(काष्ठा device_node *np,
			काष्ठा cpufreq_policy *policy,
			काष्ठा em_perf_करोमुख्य *em)
अणु
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा cpufreq_cooling_device *cpufreq_cdev;
	अचिन्हित पूर्णांक i;
	काष्ठा device *dev;
	पूर्णांक ret;
	काष्ठा thermal_cooling_device_ops *cooling_ops;
	अक्षर *name;

	dev = get_cpu_device(policy->cpu);
	अगर (unlikely(!dev)) अणु
		pr_warn("No cpu device for cpu %d\n", policy->cpu);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	अगर (IS_ERR_OR_शून्य(policy)) अणु
		pr_err("%s: cpufreq policy isn't valid: %p\n", __func__, policy);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	i = cpufreq_table_count_valid_entries(policy);
	अगर (!i) अणु
		pr_debug("%s: CPUFreq table not found or has no valid entries\n",
			 __func__);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	cpufreq_cdev = kzalloc(माप(*cpufreq_cdev), GFP_KERNEL);
	अगर (!cpufreq_cdev)
		वापस ERR_PTR(-ENOMEM);

	cpufreq_cdev->policy = policy;

	ret = allocate_idle_समय(cpufreq_cdev);
	अगर (ret) अणु
		cdev = ERR_PTR(ret);
		जाओ मुक्त_cdev;
	पूर्ण

	/* max_level is an index, not a counter */
	cpufreq_cdev->max_level = i - 1;

	cooling_ops = &cpufreq_cooling_ops;

#अगर_घोषित CONFIG_THERMAL_GOV_POWER_ALLOCATOR
	अगर (em_is_sane(cpufreq_cdev, em)) अणु
		cpufreq_cdev->em = em;
		cooling_ops->get_requested_घातer = cpufreq_get_requested_घातer;
		cooling_ops->state2घातer = cpufreq_state2घातer;
		cooling_ops->घातer2state = cpufreq_घातer2state;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अगर (policy->freq_table_sorted == CPUFREQ_TABLE_UNSORTED) अणु
		pr_err("%s: unsorted frequency tables are not supported\n",
		       __func__);
		cdev = ERR_PTR(-EINVAL);
		जाओ मुक्त_idle_समय;
	पूर्ण

	ret = freq_qos_add_request(&policy->स्थिरraपूर्णांकs,
				   &cpufreq_cdev->qos_req, FREQ_QOS_MAX,
				   get_state_freq(cpufreq_cdev, 0));
	अगर (ret < 0) अणु
		pr_err("%s: Failed to add freq constraint (%d)\n", __func__,
		       ret);
		cdev = ERR_PTR(ret);
		जाओ मुक्त_idle_समय;
	पूर्ण

	cdev = ERR_PTR(-ENOMEM);
	name = kaप्र_लिखो(GFP_KERNEL, "cpufreq-%s", dev_name(dev));
	अगर (!name)
		जाओ हटाओ_qos_req;

	cdev = thermal_of_cooling_device_रेजिस्टर(np, name, cpufreq_cdev,
						  cooling_ops);
	kमुक्त(name);

	अगर (IS_ERR(cdev))
		जाओ हटाओ_qos_req;

	वापस cdev;

हटाओ_qos_req:
	freq_qos_हटाओ_request(&cpufreq_cdev->qos_req);
मुक्त_idle_समय:
	मुक्त_idle_समय(cpufreq_cdev);
मुक्त_cdev:
	kमुक्त(cpufreq_cdev);
	वापस cdev;
पूर्ण

/**
 * cpufreq_cooling_रेजिस्टर - function to create cpufreq cooling device.
 * @policy: cpufreq policy
 *
 * This पूर्णांकerface function रेजिस्टरs the cpufreq cooling device with the name
 * "thermal-cpufreq-%x". This api can support multiple instances of cpufreq
 * cooling devices.
 *
 * Return: a valid काष्ठा thermal_cooling_device poपूर्णांकer on success,
 * on failure, it वापसs a corresponding ERR_PTR().
 */
काष्ठा thermal_cooling_device *
cpufreq_cooling_रेजिस्टर(काष्ठा cpufreq_policy *policy)
अणु
	वापस __cpufreq_cooling_रेजिस्टर(शून्य, policy, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_cooling_रेजिस्टर);

/**
 * of_cpufreq_cooling_रेजिस्टर - function to create cpufreq cooling device.
 * @policy: cpufreq policy
 *
 * This पूर्णांकerface function रेजिस्टरs the cpufreq cooling device with the name
 * "thermal-cpufreq-%x". This api can support multiple instances of cpufreq
 * cooling devices. Using this API, the cpufreq cooling device will be
 * linked to the device tree node provided.
 *
 * Using this function, the cooling device will implement the घातer
 * extensions by using a simple cpu घातer model.  The cpus must have
 * रेजिस्टरed their OPPs using the OPP library.
 *
 * It also takes पूर्णांकo account, अगर property present in policy CPU node, the
 * अटल घातer consumed by the cpu.
 *
 * Return: a valid काष्ठा thermal_cooling_device poपूर्णांकer on success,
 * and शून्य on failure.
 */
काष्ठा thermal_cooling_device *
of_cpufreq_cooling_रेजिस्टर(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा device_node *np = of_get_cpu_node(policy->cpu, शून्य);
	काष्ठा thermal_cooling_device *cdev = शून्य;

	अगर (!np) अणु
		pr_err("cpufreq_cooling: OF node not available for cpu%d\n",
		       policy->cpu);
		वापस शून्य;
	पूर्ण

	अगर (of_find_property(np, "#cooling-cells", शून्य)) अणु
		काष्ठा em_perf_करोमुख्य *em = em_cpu_get(policy->cpu);

		cdev = __cpufreq_cooling_रेजिस्टर(np, policy, em);
		अगर (IS_ERR(cdev)) अणु
			pr_err("cpufreq_cooling: cpu%d failed to register as cooling device: %ld\n",
			       policy->cpu, PTR_ERR(cdev));
			cdev = शून्य;
		पूर्ण
	पूर्ण

	of_node_put(np);
	वापस cdev;
पूर्ण
EXPORT_SYMBOL_GPL(of_cpufreq_cooling_रेजिस्टर);

/**
 * cpufreq_cooling_unरेजिस्टर - function to हटाओ cpufreq cooling device.
 * @cdev: thermal cooling device poपूर्णांकer.
 *
 * This पूर्णांकerface function unरेजिस्टरs the "thermal-cpufreq-%x" cooling device.
 */
व्योम cpufreq_cooling_unरेजिस्टर(काष्ठा thermal_cooling_device *cdev)
अणु
	काष्ठा cpufreq_cooling_device *cpufreq_cdev;

	अगर (!cdev)
		वापस;

	cpufreq_cdev = cdev->devdata;

	thermal_cooling_device_unरेजिस्टर(cdev);
	freq_qos_हटाओ_request(&cpufreq_cdev->qos_req);
	मुक्त_idle_समय(cpufreq_cdev);
	kमुक्त(cpufreq_cdev);
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_cooling_unरेजिस्टर);
