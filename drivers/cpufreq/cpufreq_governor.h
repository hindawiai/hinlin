<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * drivers/cpufreq/cpufreq_governor.h
 *
 * Header file क्रम CPUFreq governors common code
 *
 * Copyright	(C) 2001 Russell King
 *		(C) 2003 Venkatesh Pallipadi <venkatesh.pallipadi@पूर्णांकel.com>.
 *		(C) 2003 Jun Nakajima <jun.nakajima@पूर्णांकel.com>
 *		(C) 2009 Alexander Clouter <alex@digriz.org.uk>
 *		(c) 2012 Viresh Kumar <viresh.kumar@linaro.org>
 */

#अगर_अघोषित _CPUFREQ_GOVERNOR_H
#घोषणा _CPUFREQ_GOVERNOR_H

#समावेश <linux/atomic.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/sched/cpufreq.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

/* Ondemand Sampling types */
क्रमागत अणुOD_NORMAL_SAMPLE, OD_SUB_SAMPLEपूर्ण;

/*
 * Abbreviations:
 * dbs: used as a लघुक्रमm क्रम demand based चयनing It helps to keep variable
 *	names smaller, simpler
 * cdbs: common dbs
 * od_*: On-demand governor
 * cs_*: Conservative governor
 */

/* Governor demand based चयनing data (per-policy or global). */
काष्ठा dbs_data अणु
	काष्ठा gov_attr_set attr_set;
	व्योम *tuners;
	अचिन्हित पूर्णांक ignore_nice_load;
	अचिन्हित पूर्णांक sampling_rate;
	अचिन्हित पूर्णांक sampling_करोwn_factor;
	अचिन्हित पूर्णांक up_threshold;
	अचिन्हित पूर्णांक io_is_busy;
पूर्ण;

अटल अंतरभूत काष्ठा dbs_data *to_dbs_data(काष्ठा gov_attr_set *attr_set)
अणु
	वापस container_of(attr_set, काष्ठा dbs_data, attr_set);
पूर्ण

#घोषणा gov_show_one(_gov, file_name)					\
अटल sमाप_प्रकार show_##file_name						\
(काष्ठा gov_attr_set *attr_set, अक्षर *buf)				\
अणु									\
	काष्ठा dbs_data *dbs_data = to_dbs_data(attr_set);		\
	काष्ठा _gov##_dbs_tuners *tuners = dbs_data->tuners;		\
	वापस प्र_लिखो(buf, "%u\n", tuners->file_name);			\
पूर्ण

#घोषणा gov_show_one_common(file_name)					\
अटल sमाप_प्रकार show_##file_name						\
(काष्ठा gov_attr_set *attr_set, अक्षर *buf)				\
अणु									\
	काष्ठा dbs_data *dbs_data = to_dbs_data(attr_set);		\
	वापस प्र_लिखो(buf, "%u\n", dbs_data->file_name);		\
पूर्ण

#घोषणा gov_attr_ro(_name)						\
अटल काष्ठा governor_attr _name =					\
__ATTR(_name, 0444, show_##_name, शून्य)

#घोषणा gov_attr_rw(_name)						\
अटल काष्ठा governor_attr _name =					\
__ATTR(_name, 0644, show_##_name, store_##_name)

/* Common to all CPUs of a policy */
काष्ठा policy_dbs_info अणु
	काष्ठा cpufreq_policy *policy;
	/*
	 * Per policy mutex that serializes load evaluation from limit-change
	 * and work-handler.
	 */
	काष्ठा mutex update_mutex;

	u64 last_sample_समय;
	s64 sample_delay_ns;
	atomic_t work_count;
	काष्ठा irq_work irq_work;
	काष्ठा work_काष्ठा work;
	/* dbs_data may be shared between multiple policy objects */
	काष्ठा dbs_data *dbs_data;
	काष्ठा list_head list;
	/* Multiplier क्रम increasing sample delay temporarily. */
	अचिन्हित पूर्णांक rate_mult;
	अचिन्हित पूर्णांक idle_periods;	/* For conservative */
	/* Status indicators */
	bool is_shared;		/* This object is used by multiple CPUs */
	bool work_in_progress;	/* Work is being queued up or in progress */
पूर्ण;

अटल अंतरभूत व्योम gov_update_sample_delay(काष्ठा policy_dbs_info *policy_dbs,
					   अचिन्हित पूर्णांक delay_us)
अणु
	policy_dbs->sample_delay_ns = delay_us * NSEC_PER_USEC;
पूर्ण

/* Per cpu काष्ठाures */
काष्ठा cpu_dbs_info अणु
	u64 prev_cpu_idle;
	u64 prev_update_समय;
	u64 prev_cpu_nice;
	/*
	 * Used to keep track of load in the previous पूर्णांकerval. However, when
	 * explicitly set to zero, it is used as a flag to ensure that we copy
	 * the previous load to the current पूर्णांकerval only once, upon the first
	 * wake-up from idle.
	 */
	अचिन्हित पूर्णांक prev_load;
	काष्ठा update_util_data update_util;
	काष्ठा policy_dbs_info *policy_dbs;
पूर्ण;

/* Common Governor data across policies */
काष्ठा dbs_governor अणु
	काष्ठा cpufreq_governor gov;
	काष्ठा kobj_type kobj_type;

	/*
	 * Common data क्रम platक्रमms that करोn't set
	 * CPUFREQ_HAVE_GOVERNOR_PER_POLICY
	 */
	काष्ठा dbs_data *gdbs_data;

	अचिन्हित पूर्णांक (*gov_dbs_update)(काष्ठा cpufreq_policy *policy);
	काष्ठा policy_dbs_info *(*alloc)(व्योम);
	व्योम (*मुक्त)(काष्ठा policy_dbs_info *policy_dbs);
	पूर्णांक (*init)(काष्ठा dbs_data *dbs_data);
	व्योम (*निकास)(काष्ठा dbs_data *dbs_data);
	व्योम (*start)(काष्ठा cpufreq_policy *policy);
पूर्ण;

अटल अंतरभूत काष्ठा dbs_governor *dbs_governor_of(काष्ठा cpufreq_policy *policy)
अणु
	वापस container_of(policy->governor, काष्ठा dbs_governor, gov);
पूर्ण

/* Governor callback routines */
पूर्णांक cpufreq_dbs_governor_init(काष्ठा cpufreq_policy *policy);
व्योम cpufreq_dbs_governor_निकास(काष्ठा cpufreq_policy *policy);
पूर्णांक cpufreq_dbs_governor_start(काष्ठा cpufreq_policy *policy);
व्योम cpufreq_dbs_governor_stop(काष्ठा cpufreq_policy *policy);
व्योम cpufreq_dbs_governor_limits(काष्ठा cpufreq_policy *policy);

#घोषणा CPUFREQ_DBS_GOVERNOR_INITIALIZER(_name_)			\
	अणु								\
		.name = _name_,						\
		.flags = CPUFREQ_GOV_DYNAMIC_SWITCHING,			\
		.owner = THIS_MODULE,					\
		.init = cpufreq_dbs_governor_init,			\
		.निकास = cpufreq_dbs_governor_निकास,			\
		.start = cpufreq_dbs_governor_start,			\
		.stop = cpufreq_dbs_governor_stop,			\
		.limits = cpufreq_dbs_governor_limits,			\
	पूर्ण

/* Governor specअगरic operations */
काष्ठा od_ops अणु
	अचिन्हित पूर्णांक (*घातersave_bias_target)(काष्ठा cpufreq_policy *policy,
			अचिन्हित पूर्णांक freq_next, अचिन्हित पूर्णांक relation);
पूर्ण;

अचिन्हित पूर्णांक dbs_update(काष्ठा cpufreq_policy *policy);
व्योम od_रेजिस्टर_घातersave_bias_handler(अचिन्हित पूर्णांक (*f)
		(काष्ठा cpufreq_policy *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक),
		अचिन्हित पूर्णांक घातersave_bias);
व्योम od_unरेजिस्टर_घातersave_bias_handler(व्योम);
sमाप_प्रकार store_sampling_rate(काष्ठा gov_attr_set *attr_set, स्थिर अक्षर *buf,
			    माप_प्रकार count);
व्योम gov_update_cpu_data(काष्ठा dbs_data *dbs_data);
#पूर्ण_अगर /* _CPUFREQ_GOVERNOR_H */
