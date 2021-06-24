<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Scheduler code and data काष्ठाures related to cpufreq.
 *
 * Copyright (C) 2016, Intel Corporation
 * Author: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */
#समावेश <linux/cpufreq.h>

#समावेश "sched.h"

DEFINE_PER_CPU(काष्ठा update_util_data __rcu *, cpufreq_update_util_data);

/**
 * cpufreq_add_update_util_hook - Populate the CPU's update_util_data poपूर्णांकer.
 * @cpu: The CPU to set the poपूर्णांकer क्रम.
 * @data: New poपूर्णांकer value.
 * @func: Callback function to set क्रम the CPU.
 *
 * Set and publish the update_util_data poपूर्णांकer क्रम the given CPU.
 *
 * The update_util_data poपूर्णांकer of @cpu is set to @data and the callback
 * function poपूर्णांकer in the target काष्ठा update_util_data is set to @func.
 * That function will be called by cpufreq_update_util() from RCU-sched
 * पढ़ो-side critical sections, so it must not sleep.  @data will always be
 * passed to it as the first argument which allows the function to get to the
 * target update_util_data काष्ठाure and its container.
 *
 * The update_util_data poपूर्णांकer of @cpu must be शून्य when this function is
 * called or it will WARN() and वापस with no effect.
 */
व्योम cpufreq_add_update_util_hook(पूर्णांक cpu, काष्ठा update_util_data *data,
			व्योम (*func)(काष्ठा update_util_data *data, u64 समय,
				     अचिन्हित पूर्णांक flags))
अणु
	अगर (WARN_ON(!data || !func))
		वापस;

	अगर (WARN_ON(per_cpu(cpufreq_update_util_data, cpu)))
		वापस;

	data->func = func;
	rcu_assign_poपूर्णांकer(per_cpu(cpufreq_update_util_data, cpu), data);
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_add_update_util_hook);

/**
 * cpufreq_हटाओ_update_util_hook - Clear the CPU's update_util_data poपूर्णांकer.
 * @cpu: The CPU to clear the poपूर्णांकer क्रम.
 *
 * Clear the update_util_data poपूर्णांकer क्रम the given CPU.
 *
 * Callers must use RCU callbacks to मुक्त any memory that might be
 * accessed via the old update_util_data poपूर्णांकer or invoke synchronize_rcu()
 * right after this function to aव्योम use-after-मुक्त.
 */
व्योम cpufreq_हटाओ_update_util_hook(पूर्णांक cpu)
अणु
	rcu_assign_poपूर्णांकer(per_cpu(cpufreq_update_util_data, cpu), शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_हटाओ_update_util_hook);

/**
 * cpufreq_this_cpu_can_update - Check अगर cpufreq policy can be updated.
 * @policy: cpufreq policy to check.
 *
 * Return 'true' अगर:
 * - the local and remote CPUs share @policy,
 * - dvfs_possible_from_any_cpu is set in @policy and the local CPU is not going
 *   offline (in which हाल it is not expected to run cpufreq updates any more).
 */
bool cpufreq_this_cpu_can_update(काष्ठा cpufreq_policy *policy)
अणु
	वापस cpumask_test_cpu(smp_processor_id(), policy->cpus) ||
		(policy->dvfs_possible_from_any_cpu &&
		 rcu_dereference_sched(*this_cpu_ptr(&cpufreq_update_util_data)));
पूर्ण
