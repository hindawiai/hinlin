<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  drivers/cpufreq/cpufreq_ondemand.c
 *
 *  Copyright (C)  2001 Russell King
 *            (C)  2003 Venkatesh Pallipadi <venkatesh.pallipadi@पूर्णांकel.com>.
 *                      Jun Nakajima <jun.nakajima@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cpu.h>
#समावेश <linux/percpu-defs.h>
#समावेश <linux/slab.h>
#समावेश <linux/tick.h>
#समावेश <linux/sched/cpufreq.h>

#समावेश "cpufreq_ondemand.h"

/* On-demand governor macros */
#घोषणा DEF_FREQUENCY_UP_THRESHOLD		(80)
#घोषणा DEF_SAMPLING_DOWN_FACTOR		(1)
#घोषणा MAX_SAMPLING_DOWN_FACTOR		(100000)
#घोषणा MICRO_FREQUENCY_UP_THRESHOLD		(95)
#घोषणा MICRO_FREQUENCY_MIN_SAMPLE_RATE		(10000)
#घोषणा MIN_FREQUENCY_UP_THRESHOLD		(1)
#घोषणा MAX_FREQUENCY_UP_THRESHOLD		(100)

अटल काष्ठा od_ops od_ops;

अटल अचिन्हित पूर्णांक शेष_घातersave_bias;

/*
 * Not all CPUs want IO समय to be accounted as busy; this depends on how
 * efficient idling at a higher frequency/voltage is.
 * Pavel Machek says this is not so क्रम various generations of AMD and old
 * Intel प्रणालीs.
 * Mike Chan (android.com) claims this is also not true क्रम ARM.
 * Because of this, whitelist specअगरic known (series) of CPUs by शेष, and
 * leave all others up to the user.
 */
अटल पूर्णांक should_io_be_busy(व्योम)
अणु
#अगर defined(CONFIG_X86)
	/*
	 * For Intel, Core 2 (model 15) and later have an efficient idle.
	 */
	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_INTEL &&
			boot_cpu_data.x86 == 6 &&
			boot_cpu_data.x86_model >= 15)
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * Find right freq to be set now with घातersave_bias on.
 * Returns the freq_hi to be used right now and will set freq_hi_delay_us,
 * freq_lo, and freq_lo_delay_us in percpu area क्रम averaging freqs.
 */
अटल अचिन्हित पूर्णांक generic_घातersave_bias_target(काष्ठा cpufreq_policy *policy,
		अचिन्हित पूर्णांक freq_next, अचिन्हित पूर्णांक relation)
अणु
	अचिन्हित पूर्णांक freq_req, freq_reduc, freq_avg;
	अचिन्हित पूर्णांक freq_hi, freq_lo;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक delay_hi_us;
	काष्ठा policy_dbs_info *policy_dbs = policy->governor_data;
	काष्ठा od_policy_dbs_info *dbs_info = to_dbs_info(policy_dbs);
	काष्ठा dbs_data *dbs_data = policy_dbs->dbs_data;
	काष्ठा od_dbs_tuners *od_tuners = dbs_data->tuners;
	काष्ठा cpufreq_frequency_table *freq_table = policy->freq_table;

	अगर (!freq_table) अणु
		dbs_info->freq_lo = 0;
		dbs_info->freq_lo_delay_us = 0;
		वापस freq_next;
	पूर्ण

	index = cpufreq_frequency_table_target(policy, freq_next, relation);
	freq_req = freq_table[index].frequency;
	freq_reduc = freq_req * od_tuners->घातersave_bias / 1000;
	freq_avg = freq_req - freq_reduc;

	/* Find freq bounds क्रम freq_avg in freq_table */
	index = cpufreq_table_find_index_h(policy, freq_avg);
	freq_lo = freq_table[index].frequency;
	index = cpufreq_table_find_index_l(policy, freq_avg);
	freq_hi = freq_table[index].frequency;

	/* Find out how दीर्घ we have to be in hi and lo freqs */
	अगर (freq_hi == freq_lo) अणु
		dbs_info->freq_lo = 0;
		dbs_info->freq_lo_delay_us = 0;
		वापस freq_lo;
	पूर्ण
	delay_hi_us = (freq_avg - freq_lo) * dbs_data->sampling_rate;
	delay_hi_us += (freq_hi - freq_lo) / 2;
	delay_hi_us /= freq_hi - freq_lo;
	dbs_info->freq_hi_delay_us = delay_hi_us;
	dbs_info->freq_lo = freq_lo;
	dbs_info->freq_lo_delay_us = dbs_data->sampling_rate - delay_hi_us;
	वापस freq_hi;
पूर्ण

अटल व्योम ondemand_घातersave_bias_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा od_policy_dbs_info *dbs_info = to_dbs_info(policy->governor_data);

	dbs_info->freq_lo = 0;
पूर्ण

अटल व्योम dbs_freq_increase(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा policy_dbs_info *policy_dbs = policy->governor_data;
	काष्ठा dbs_data *dbs_data = policy_dbs->dbs_data;
	काष्ठा od_dbs_tuners *od_tuners = dbs_data->tuners;

	अगर (od_tuners->घातersave_bias)
		freq = od_ops.घातersave_bias_target(policy, freq,
				CPUFREQ_RELATION_H);
	अन्यथा अगर (policy->cur == policy->max)
		वापस;

	__cpufreq_driver_target(policy, freq, od_tuners->घातersave_bias ?
			CPUFREQ_RELATION_L : CPUFREQ_RELATION_H);
पूर्ण

/*
 * Every sampling_rate, we check, अगर current idle समय is less than 20%
 * (शेष), then we try to increase frequency. Else, we adjust the frequency
 * proportional to load.
 */
अटल व्योम od_update(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा policy_dbs_info *policy_dbs = policy->governor_data;
	काष्ठा od_policy_dbs_info *dbs_info = to_dbs_info(policy_dbs);
	काष्ठा dbs_data *dbs_data = policy_dbs->dbs_data;
	काष्ठा od_dbs_tuners *od_tuners = dbs_data->tuners;
	अचिन्हित पूर्णांक load = dbs_update(policy);

	dbs_info->freq_lo = 0;

	/* Check क्रम frequency increase */
	अगर (load > dbs_data->up_threshold) अणु
		/* If चयनing to max speed, apply sampling_करोwn_factor */
		अगर (policy->cur < policy->max)
			policy_dbs->rate_mult = dbs_data->sampling_करोwn_factor;
		dbs_freq_increase(policy, policy->max);
	पूर्ण अन्यथा अणु
		/* Calculate the next frequency proportional to load */
		अचिन्हित पूर्णांक freq_next, min_f, max_f;

		min_f = policy->cpuinfo.min_freq;
		max_f = policy->cpuinfo.max_freq;
		freq_next = min_f + load * (max_f - min_f) / 100;

		/* No दीर्घer fully busy, reset rate_mult */
		policy_dbs->rate_mult = 1;

		अगर (od_tuners->घातersave_bias)
			freq_next = od_ops.घातersave_bias_target(policy,
								 freq_next,
								 CPUFREQ_RELATION_L);

		__cpufreq_driver_target(policy, freq_next, CPUFREQ_RELATION_C);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक od_dbs_update(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा policy_dbs_info *policy_dbs = policy->governor_data;
	काष्ठा dbs_data *dbs_data = policy_dbs->dbs_data;
	काष्ठा od_policy_dbs_info *dbs_info = to_dbs_info(policy_dbs);
	पूर्णांक sample_type = dbs_info->sample_type;

	/* Common NORMAL_SAMPLE setup */
	dbs_info->sample_type = OD_NORMAL_SAMPLE;
	/*
	 * OD_SUB_SAMPLE करोesn't make sense अगर sample_delay_ns is 0, so ignore
	 * it then.
	 */
	अगर (sample_type == OD_SUB_SAMPLE && policy_dbs->sample_delay_ns > 0) अणु
		__cpufreq_driver_target(policy, dbs_info->freq_lo,
					CPUFREQ_RELATION_H);
		वापस dbs_info->freq_lo_delay_us;
	पूर्ण

	od_update(policy);

	अगर (dbs_info->freq_lo) अणु
		/* Setup SUB_SAMPLE */
		dbs_info->sample_type = OD_SUB_SAMPLE;
		वापस dbs_info->freq_hi_delay_us;
	पूर्ण

	वापस dbs_data->sampling_rate * policy_dbs->rate_mult;
पूर्ण

/************************** sysfs पूर्णांकerface ************************/
अटल काष्ठा dbs_governor od_dbs_gov;

अटल sमाप_प्रकार store_io_is_busy(काष्ठा gov_attr_set *attr_set, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा dbs_data *dbs_data = to_dbs_data(attr_set);
	अचिन्हित पूर्णांक input;
	पूर्णांक ret;

	ret = माला_पूछो(buf, "%u", &input);
	अगर (ret != 1)
		वापस -EINVAL;
	dbs_data->io_is_busy = !!input;

	/* we need to re-evaluate prev_cpu_idle */
	gov_update_cpu_data(dbs_data);

	वापस count;
पूर्ण

अटल sमाप_प्रकार store_up_threshold(काष्ठा gov_attr_set *attr_set,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dbs_data *dbs_data = to_dbs_data(attr_set);
	अचिन्हित पूर्णांक input;
	पूर्णांक ret;
	ret = माला_पूछो(buf, "%u", &input);

	अगर (ret != 1 || input > MAX_FREQUENCY_UP_THRESHOLD ||
			input < MIN_FREQUENCY_UP_THRESHOLD) अणु
		वापस -EINVAL;
	पूर्ण

	dbs_data->up_threshold = input;
	वापस count;
पूर्ण

अटल sमाप_प्रकार store_sampling_करोwn_factor(काष्ठा gov_attr_set *attr_set,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dbs_data *dbs_data = to_dbs_data(attr_set);
	काष्ठा policy_dbs_info *policy_dbs;
	अचिन्हित पूर्णांक input;
	पूर्णांक ret;
	ret = माला_पूछो(buf, "%u", &input);

	अगर (ret != 1 || input > MAX_SAMPLING_DOWN_FACTOR || input < 1)
		वापस -EINVAL;

	dbs_data->sampling_करोwn_factor = input;

	/* Reset करोwn sampling multiplier in हाल it was active */
	list_क्रम_each_entry(policy_dbs, &attr_set->policy_list, list) अणु
		/*
		 * Doing this without locking might lead to using dअगरferent
		 * rate_mult values in od_update() and od_dbs_update().
		 */
		mutex_lock(&policy_dbs->update_mutex);
		policy_dbs->rate_mult = 1;
		mutex_unlock(&policy_dbs->update_mutex);
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार store_ignore_nice_load(काष्ठा gov_attr_set *attr_set,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dbs_data *dbs_data = to_dbs_data(attr_set);
	अचिन्हित पूर्णांक input;
	पूर्णांक ret;

	ret = माला_पूछो(buf, "%u", &input);
	अगर (ret != 1)
		वापस -EINVAL;

	अगर (input > 1)
		input = 1;

	अगर (input == dbs_data->ignore_nice_load) अणु /* nothing to करो */
		वापस count;
	पूर्ण
	dbs_data->ignore_nice_load = input;

	/* we need to re-evaluate prev_cpu_idle */
	gov_update_cpu_data(dbs_data);

	वापस count;
पूर्ण

अटल sमाप_प्रकार store_घातersave_bias(काष्ठा gov_attr_set *attr_set,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dbs_data *dbs_data = to_dbs_data(attr_set);
	काष्ठा od_dbs_tuners *od_tuners = dbs_data->tuners;
	काष्ठा policy_dbs_info *policy_dbs;
	अचिन्हित पूर्णांक input;
	पूर्णांक ret;
	ret = माला_पूछो(buf, "%u", &input);

	अगर (ret != 1)
		वापस -EINVAL;

	अगर (input > 1000)
		input = 1000;

	od_tuners->घातersave_bias = input;

	list_क्रम_each_entry(policy_dbs, &attr_set->policy_list, list)
		ondemand_घातersave_bias_init(policy_dbs->policy);

	वापस count;
पूर्ण

gov_show_one_common(sampling_rate);
gov_show_one_common(up_threshold);
gov_show_one_common(sampling_करोwn_factor);
gov_show_one_common(ignore_nice_load);
gov_show_one_common(io_is_busy);
gov_show_one(od, घातersave_bias);

gov_attr_rw(sampling_rate);
gov_attr_rw(io_is_busy);
gov_attr_rw(up_threshold);
gov_attr_rw(sampling_करोwn_factor);
gov_attr_rw(ignore_nice_load);
gov_attr_rw(घातersave_bias);

अटल काष्ठा attribute *od_attributes[] = अणु
	&sampling_rate.attr,
	&up_threshold.attr,
	&sampling_करोwn_factor.attr,
	&ignore_nice_load.attr,
	&घातersave_bias.attr,
	&io_is_busy.attr,
	शून्य
पूर्ण;

/************************** sysfs end ************************/

अटल काष्ठा policy_dbs_info *od_alloc(व्योम)
अणु
	काष्ठा od_policy_dbs_info *dbs_info;

	dbs_info = kzalloc(माप(*dbs_info), GFP_KERNEL);
	वापस dbs_info ? &dbs_info->policy_dbs : शून्य;
पूर्ण

अटल व्योम od_मुक्त(काष्ठा policy_dbs_info *policy_dbs)
अणु
	kमुक्त(to_dbs_info(policy_dbs));
पूर्ण

अटल पूर्णांक od_init(काष्ठा dbs_data *dbs_data)
अणु
	काष्ठा od_dbs_tuners *tuners;
	u64 idle_समय;
	पूर्णांक cpu;

	tuners = kzalloc(माप(*tuners), GFP_KERNEL);
	अगर (!tuners)
		वापस -ENOMEM;

	cpu = get_cpu();
	idle_समय = get_cpu_idle_समय_us(cpu, शून्य);
	put_cpu();
	अगर (idle_समय != -1ULL) अणु
		/* Idle micro accounting is supported. Use finer thresholds */
		dbs_data->up_threshold = MICRO_FREQUENCY_UP_THRESHOLD;
	पूर्ण अन्यथा अणु
		dbs_data->up_threshold = DEF_FREQUENCY_UP_THRESHOLD;
	पूर्ण

	dbs_data->sampling_करोwn_factor = DEF_SAMPLING_DOWN_FACTOR;
	dbs_data->ignore_nice_load = 0;
	tuners->घातersave_bias = शेष_घातersave_bias;
	dbs_data->io_is_busy = should_io_be_busy();

	dbs_data->tuners = tuners;
	वापस 0;
पूर्ण

अटल व्योम od_निकास(काष्ठा dbs_data *dbs_data)
अणु
	kमुक्त(dbs_data->tuners);
पूर्ण

अटल व्योम od_start(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा od_policy_dbs_info *dbs_info = to_dbs_info(policy->governor_data);

	dbs_info->sample_type = OD_NORMAL_SAMPLE;
	ondemand_घातersave_bias_init(policy);
पूर्ण

अटल काष्ठा od_ops od_ops = अणु
	.घातersave_bias_target = generic_घातersave_bias_target,
पूर्ण;

अटल काष्ठा dbs_governor od_dbs_gov = अणु
	.gov = CPUFREQ_DBS_GOVERNOR_INITIALIZER("ondemand"),
	.kobj_type = अणु .शेष_attrs = od_attributes पूर्ण,
	.gov_dbs_update = od_dbs_update,
	.alloc = od_alloc,
	.मुक्त = od_मुक्त,
	.init = od_init,
	.निकास = od_निकास,
	.start = od_start,
पूर्ण;

#घोषणा CPU_FREQ_GOV_ONDEMAND	(od_dbs_gov.gov)

अटल व्योम od_set_घातersave_bias(अचिन्हित पूर्णांक घातersave_bias)
अणु
	अचिन्हित पूर्णांक cpu;
	cpumask_t करोne;

	शेष_घातersave_bias = घातersave_bias;
	cpumask_clear(&करोne);

	get_online_cpus();
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा cpufreq_policy *policy;
		काष्ठा policy_dbs_info *policy_dbs;
		काष्ठा dbs_data *dbs_data;
		काष्ठा od_dbs_tuners *od_tuners;

		अगर (cpumask_test_cpu(cpu, &करोne))
			जारी;

		policy = cpufreq_cpu_get_raw(cpu);
		अगर (!policy || policy->governor != &CPU_FREQ_GOV_ONDEMAND)
			जारी;

		policy_dbs = policy->governor_data;
		अगर (!policy_dbs)
			जारी;

		cpumask_or(&करोne, &करोne, policy->cpus);

		dbs_data = policy_dbs->dbs_data;
		od_tuners = dbs_data->tuners;
		od_tuners->घातersave_bias = शेष_घातersave_bias;
	पूर्ण
	put_online_cpus();
पूर्ण

व्योम od_रेजिस्टर_घातersave_bias_handler(अचिन्हित पूर्णांक (*f)
		(काष्ठा cpufreq_policy *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक),
		अचिन्हित पूर्णांक घातersave_bias)
अणु
	od_ops.घातersave_bias_target = f;
	od_set_घातersave_bias(घातersave_bias);
पूर्ण
EXPORT_SYMBOL_GPL(od_रेजिस्टर_घातersave_bias_handler);

व्योम od_unरेजिस्टर_घातersave_bias_handler(व्योम)
अणु
	od_ops.घातersave_bias_target = generic_घातersave_bias_target;
	od_set_घातersave_bias(0);
पूर्ण
EXPORT_SYMBOL_GPL(od_unरेजिस्टर_घातersave_bias_handler);

MODULE_AUTHOR("Venkatesh Pallipadi <venkatesh.pallipadi@intel.com>");
MODULE_AUTHOR("Alexey Starikovskiy <alexey.y.starikovskiy@intel.com>");
MODULE_DESCRIPTION("'cpufreq_ondemand' - A dynamic cpufreq governor for "
	"Low Latency Frequency Transition capable processors");
MODULE_LICENSE("GPL");

#अगर_घोषित CONFIG_CPU_FREQ_DEFAULT_GOV_ONDEMAND
काष्ठा cpufreq_governor *cpufreq_शेष_governor(व्योम)
अणु
	वापस &CPU_FREQ_GOV_ONDEMAND;
पूर्ण
#पूर्ण_अगर

cpufreq_governor_init(CPU_FREQ_GOV_ONDEMAND);
cpufreq_governor_निकास(CPU_FREQ_GOV_ONDEMAND);
