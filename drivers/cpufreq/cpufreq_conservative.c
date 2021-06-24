<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  drivers/cpufreq/cpufreq_conservative.c
 *
 *  Copyright (C)  2001 Russell King
 *            (C)  2003 Venkatesh Pallipadi <venkatesh.pallipadi@पूर्णांकel.com>.
 *                      Jun Nakajima <jun.nakajima@पूर्णांकel.com>
 *            (C)  2009 Alexander Clouter <alex@digriz.org.uk>
 */

#समावेश <linux/slab.h>
#समावेश "cpufreq_governor.h"

काष्ठा cs_policy_dbs_info अणु
	काष्ठा policy_dbs_info policy_dbs;
	अचिन्हित पूर्णांक करोwn_skip;
	अचिन्हित पूर्णांक requested_freq;
पूर्ण;

अटल अंतरभूत काष्ठा cs_policy_dbs_info *to_dbs_info(काष्ठा policy_dbs_info *policy_dbs)
अणु
	वापस container_of(policy_dbs, काष्ठा cs_policy_dbs_info, policy_dbs);
पूर्ण

काष्ठा cs_dbs_tuners अणु
	अचिन्हित पूर्णांक करोwn_threshold;
	अचिन्हित पूर्णांक freq_step;
पूर्ण;

/* Conservative governor macros */
#घोषणा DEF_FREQUENCY_UP_THRESHOLD		(80)
#घोषणा DEF_FREQUENCY_DOWN_THRESHOLD		(20)
#घोषणा DEF_FREQUENCY_STEP			(5)
#घोषणा DEF_SAMPLING_DOWN_FACTOR		(1)
#घोषणा MAX_SAMPLING_DOWN_FACTOR		(10)

अटल अंतरभूत अचिन्हित पूर्णांक get_freq_step(काष्ठा cs_dbs_tuners *cs_tuners,
					 काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक freq_step = (cs_tuners->freq_step * policy->max) / 100;

	/* max freq cannot be less than 100. But who knows... */
	अगर (unlikely(freq_step == 0))
		freq_step = DEF_FREQUENCY_STEP;

	वापस freq_step;
पूर्ण

/*
 * Every sampling_rate, we check, अगर current idle समय is less than 20%
 * (शेष), then we try to increase frequency. Every sampling_rate *
 * sampling_करोwn_factor, we check, अगर current idle समय is more than 80%
 * (शेष), then we try to decrease frequency
 *
 * Frequency updates happen at minimum steps of 5% (शेष) of maximum
 * frequency
 */
अटल अचिन्हित पूर्णांक cs_dbs_update(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा policy_dbs_info *policy_dbs = policy->governor_data;
	काष्ठा cs_policy_dbs_info *dbs_info = to_dbs_info(policy_dbs);
	अचिन्हित पूर्णांक requested_freq = dbs_info->requested_freq;
	काष्ठा dbs_data *dbs_data = policy_dbs->dbs_data;
	काष्ठा cs_dbs_tuners *cs_tuners = dbs_data->tuners;
	अचिन्हित पूर्णांक load = dbs_update(policy);
	अचिन्हित पूर्णांक freq_step;

	/*
	 * अवरोध out अगर we 'cannot' reduce the speed as the user might
	 * want freq_step to be zero
	 */
	अगर (cs_tuners->freq_step == 0)
		जाओ out;

	/*
	 * If requested_freq is out of range, it is likely that the limits
	 * changed in the meanसमय, so fall back to current frequency in that
	 * हाल.
	 */
	अगर (requested_freq > policy->max || requested_freq < policy->min) अणु
		requested_freq = policy->cur;
		dbs_info->requested_freq = requested_freq;
	पूर्ण

	freq_step = get_freq_step(cs_tuners, policy);

	/*
	 * Decrease requested_freq one freq_step क्रम each idle period that
	 * we didn't update the frequency.
	 */
	अगर (policy_dbs->idle_periods < अच_पूर्णांक_उच्च) अणु
		अचिन्हित पूर्णांक freq_steps = policy_dbs->idle_periods * freq_step;

		अगर (requested_freq > policy->min + freq_steps)
			requested_freq -= freq_steps;
		अन्यथा
			requested_freq = policy->min;

		policy_dbs->idle_periods = अच_पूर्णांक_उच्च;
	पूर्ण

	/* Check क्रम frequency increase */
	अगर (load > dbs_data->up_threshold) अणु
		dbs_info->करोwn_skip = 0;

		/* अगर we are alपढ़ोy at full speed then अवरोध out early */
		अगर (requested_freq == policy->max)
			जाओ out;

		requested_freq += freq_step;
		अगर (requested_freq > policy->max)
			requested_freq = policy->max;

		__cpufreq_driver_target(policy, requested_freq, CPUFREQ_RELATION_H);
		dbs_info->requested_freq = requested_freq;
		जाओ out;
	पूर्ण

	/* अगर sampling_करोwn_factor is active अवरोध out early */
	अगर (++dbs_info->करोwn_skip < dbs_data->sampling_करोwn_factor)
		जाओ out;
	dbs_info->करोwn_skip = 0;

	/* Check क्रम frequency decrease */
	अगर (load < cs_tuners->करोwn_threshold) अणु
		/*
		 * अगर we cannot reduce the frequency anymore, अवरोध out early
		 */
		अगर (requested_freq == policy->min)
			जाओ out;

		अगर (requested_freq > freq_step)
			requested_freq -= freq_step;
		अन्यथा
			requested_freq = policy->min;

		__cpufreq_driver_target(policy, requested_freq, CPUFREQ_RELATION_L);
		dbs_info->requested_freq = requested_freq;
	पूर्ण

 out:
	वापस dbs_data->sampling_rate;
पूर्ण

/************************** sysfs पूर्णांकerface ************************/

अटल sमाप_प्रकार store_sampling_करोwn_factor(काष्ठा gov_attr_set *attr_set,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dbs_data *dbs_data = to_dbs_data(attr_set);
	अचिन्हित पूर्णांक input;
	पूर्णांक ret;
	ret = माला_पूछो(buf, "%u", &input);

	अगर (ret != 1 || input > MAX_SAMPLING_DOWN_FACTOR || input < 1)
		वापस -EINVAL;

	dbs_data->sampling_करोwn_factor = input;
	वापस count;
पूर्ण

अटल sमाप_प्रकार store_up_threshold(काष्ठा gov_attr_set *attr_set,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dbs_data *dbs_data = to_dbs_data(attr_set);
	काष्ठा cs_dbs_tuners *cs_tuners = dbs_data->tuners;
	अचिन्हित पूर्णांक input;
	पूर्णांक ret;
	ret = माला_पूछो(buf, "%u", &input);

	अगर (ret != 1 || input > 100 || input <= cs_tuners->करोwn_threshold)
		वापस -EINVAL;

	dbs_data->up_threshold = input;
	वापस count;
पूर्ण

अटल sमाप_प्रकार store_करोwn_threshold(काष्ठा gov_attr_set *attr_set,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dbs_data *dbs_data = to_dbs_data(attr_set);
	काष्ठा cs_dbs_tuners *cs_tuners = dbs_data->tuners;
	अचिन्हित पूर्णांक input;
	पूर्णांक ret;
	ret = माला_पूछो(buf, "%u", &input);

	/* cannot be lower than 1 otherwise freq will not fall */
	अगर (ret != 1 || input < 1 || input > 100 ||
			input >= dbs_data->up_threshold)
		वापस -EINVAL;

	cs_tuners->करोwn_threshold = input;
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

	अगर (input == dbs_data->ignore_nice_load) /* nothing to करो */
		वापस count;

	dbs_data->ignore_nice_load = input;

	/* we need to re-evaluate prev_cpu_idle */
	gov_update_cpu_data(dbs_data);

	वापस count;
पूर्ण

अटल sमाप_प्रकार store_freq_step(काष्ठा gov_attr_set *attr_set, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा dbs_data *dbs_data = to_dbs_data(attr_set);
	काष्ठा cs_dbs_tuners *cs_tuners = dbs_data->tuners;
	अचिन्हित पूर्णांक input;
	पूर्णांक ret;
	ret = माला_पूछो(buf, "%u", &input);

	अगर (ret != 1)
		वापस -EINVAL;

	अगर (input > 100)
		input = 100;

	/*
	 * no need to test here अगर freq_step is zero as the user might actually
	 * want this, they would be crazy though :)
	 */
	cs_tuners->freq_step = input;
	वापस count;
पूर्ण

gov_show_one_common(sampling_rate);
gov_show_one_common(sampling_करोwn_factor);
gov_show_one_common(up_threshold);
gov_show_one_common(ignore_nice_load);
gov_show_one(cs, करोwn_threshold);
gov_show_one(cs, freq_step);

gov_attr_rw(sampling_rate);
gov_attr_rw(sampling_करोwn_factor);
gov_attr_rw(up_threshold);
gov_attr_rw(ignore_nice_load);
gov_attr_rw(करोwn_threshold);
gov_attr_rw(freq_step);

अटल काष्ठा attribute *cs_attributes[] = अणु
	&sampling_rate.attr,
	&sampling_करोwn_factor.attr,
	&up_threshold.attr,
	&करोwn_threshold.attr,
	&ignore_nice_load.attr,
	&freq_step.attr,
	शून्य
पूर्ण;

/************************** sysfs end ************************/

अटल काष्ठा policy_dbs_info *cs_alloc(व्योम)
अणु
	काष्ठा cs_policy_dbs_info *dbs_info;

	dbs_info = kzalloc(माप(*dbs_info), GFP_KERNEL);
	वापस dbs_info ? &dbs_info->policy_dbs : शून्य;
पूर्ण

अटल व्योम cs_मुक्त(काष्ठा policy_dbs_info *policy_dbs)
अणु
	kमुक्त(to_dbs_info(policy_dbs));
पूर्ण

अटल पूर्णांक cs_init(काष्ठा dbs_data *dbs_data)
अणु
	काष्ठा cs_dbs_tuners *tuners;

	tuners = kzalloc(माप(*tuners), GFP_KERNEL);
	अगर (!tuners)
		वापस -ENOMEM;

	tuners->करोwn_threshold = DEF_FREQUENCY_DOWN_THRESHOLD;
	tuners->freq_step = DEF_FREQUENCY_STEP;
	dbs_data->up_threshold = DEF_FREQUENCY_UP_THRESHOLD;
	dbs_data->sampling_करोwn_factor = DEF_SAMPLING_DOWN_FACTOR;
	dbs_data->ignore_nice_load = 0;
	dbs_data->tuners = tuners;

	वापस 0;
पूर्ण

अटल व्योम cs_निकास(काष्ठा dbs_data *dbs_data)
अणु
	kमुक्त(dbs_data->tuners);
पूर्ण

अटल व्योम cs_start(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cs_policy_dbs_info *dbs_info = to_dbs_info(policy->governor_data);

	dbs_info->करोwn_skip = 0;
	dbs_info->requested_freq = policy->cur;
पूर्ण

अटल काष्ठा dbs_governor cs_governor = अणु
	.gov = CPUFREQ_DBS_GOVERNOR_INITIALIZER("conservative"),
	.kobj_type = अणु .शेष_attrs = cs_attributes पूर्ण,
	.gov_dbs_update = cs_dbs_update,
	.alloc = cs_alloc,
	.मुक्त = cs_मुक्त,
	.init = cs_init,
	.निकास = cs_निकास,
	.start = cs_start,
पूर्ण;

#घोषणा CPU_FREQ_GOV_CONSERVATIVE	(cs_governor.gov)

MODULE_AUTHOR("Alexander Clouter <alex@digriz.org.uk>");
MODULE_DESCRIPTION("'cpufreq_conservative' - A dynamic cpufreq governor for "
		"Low Latency Frequency Transition capable processors "
		"optimised for use in a battery environment");
MODULE_LICENSE("GPL");

#अगर_घोषित CONFIG_CPU_FREQ_DEFAULT_GOV_CONSERVATIVE
काष्ठा cpufreq_governor *cpufreq_शेष_governor(व्योम)
अणु
	वापस &CPU_FREQ_GOV_CONSERVATIVE;
पूर्ण
#पूर्ण_अगर

cpufreq_governor_init(CPU_FREQ_GOV_CONSERVATIVE);
cpufreq_governor_निकास(CPU_FREQ_GOV_CONSERVATIVE);
