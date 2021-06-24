<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 *  linux/drivers/cpufreq/cpufreq_userspace.c
 *
 *  Copyright (C)  2001 Russell King
 *            (C)  2002 - 2004 Dominik Broकरोwski <linux@broकरो.de>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cpufreq.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, cpu_is_managed);
अटल DEFINE_MUTEX(userspace_mutex);

/**
 * cpufreq_set - set the CPU frequency
 * @policy: poपूर्णांकer to policy काष्ठा where freq is being set
 * @freq: target frequency in kHz
 *
 * Sets the CPU frequency to freq.
 */
अटल पूर्णांक cpufreq_set(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक freq)
अणु
	पूर्णांक ret = -EINVAL;
	अचिन्हित पूर्णांक *setspeed = policy->governor_data;

	pr_debug("cpufreq_set for cpu %u, freq %u kHz\n", policy->cpu, freq);

	mutex_lock(&userspace_mutex);
	अगर (!per_cpu(cpu_is_managed, policy->cpu))
		जाओ err;

	*setspeed = freq;

	ret = __cpufreq_driver_target(policy, freq, CPUFREQ_RELATION_L);
 err:
	mutex_unlock(&userspace_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_speed(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", policy->cur);
पूर्ण

अटल पूर्णांक cpufreq_userspace_policy_init(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक *setspeed;

	setspeed = kzalloc(माप(*setspeed), GFP_KERNEL);
	अगर (!setspeed)
		वापस -ENOMEM;

	policy->governor_data = setspeed;
	वापस 0;
पूर्ण

अटल व्योम cpufreq_userspace_policy_निकास(काष्ठा cpufreq_policy *policy)
अणु
	mutex_lock(&userspace_mutex);
	kमुक्त(policy->governor_data);
	policy->governor_data = शून्य;
	mutex_unlock(&userspace_mutex);
पूर्ण

अटल पूर्णांक cpufreq_userspace_policy_start(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक *setspeed = policy->governor_data;

	BUG_ON(!policy->cur);
	pr_debug("started managing cpu %u\n", policy->cpu);

	mutex_lock(&userspace_mutex);
	per_cpu(cpu_is_managed, policy->cpu) = 1;
	*setspeed = policy->cur;
	mutex_unlock(&userspace_mutex);
	वापस 0;
पूर्ण

अटल व्योम cpufreq_userspace_policy_stop(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक *setspeed = policy->governor_data;

	pr_debug("managing cpu %u stopped\n", policy->cpu);

	mutex_lock(&userspace_mutex);
	per_cpu(cpu_is_managed, policy->cpu) = 0;
	*setspeed = 0;
	mutex_unlock(&userspace_mutex);
पूर्ण

अटल व्योम cpufreq_userspace_policy_limits(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक *setspeed = policy->governor_data;

	mutex_lock(&userspace_mutex);

	pr_debug("limit event for cpu %u: %u - %u kHz, currently %u kHz, last set to %u kHz\n",
		 policy->cpu, policy->min, policy->max, policy->cur, *setspeed);

	अगर (policy->max < *setspeed)
		__cpufreq_driver_target(policy, policy->max, CPUFREQ_RELATION_H);
	अन्यथा अगर (policy->min > *setspeed)
		__cpufreq_driver_target(policy, policy->min, CPUFREQ_RELATION_L);
	अन्यथा
		__cpufreq_driver_target(policy, *setspeed, CPUFREQ_RELATION_L);

	mutex_unlock(&userspace_mutex);
पूर्ण

अटल काष्ठा cpufreq_governor cpufreq_gov_userspace = अणु
	.name		= "userspace",
	.init		= cpufreq_userspace_policy_init,
	.निकास		= cpufreq_userspace_policy_निकास,
	.start		= cpufreq_userspace_policy_start,
	.stop		= cpufreq_userspace_policy_stop,
	.limits		= cpufreq_userspace_policy_limits,
	.store_setspeed	= cpufreq_set,
	.show_setspeed	= show_speed,
	.owner		= THIS_MODULE,
पूर्ण;

MODULE_AUTHOR("Dominik Brodowski <linux@brodo.de>, "
		"Russell King <rmk@arm.linux.org.uk>");
MODULE_DESCRIPTION("CPUfreq policy governor 'userspace'");
MODULE_LICENSE("GPL");

#अगर_घोषित CONFIG_CPU_FREQ_DEFAULT_GOV_USERSPACE
काष्ठा cpufreq_governor *cpufreq_शेष_governor(व्योम)
अणु
	वापस &cpufreq_gov_userspace;
पूर्ण
#पूर्ण_अगर

cpufreq_governor_init(cpufreq_gov_userspace);
cpufreq_governor_निकास(cpufreq_gov_userspace);
