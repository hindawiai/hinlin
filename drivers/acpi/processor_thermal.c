<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * processor_thermal.c - Passive cooling submodule of the ACPI processor driver
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 *  Copyright (C) 2004       Dominik Broकरोwski <linux@broकरो.de>
 *  Copyright (C) 2004  Anil S Keshavamurthy <anil.s.keshavamurthy@पूर्णांकel.com>
 *  			- Added processor hotplug support
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/acpi.h>
#समावेश <acpi/processor.h>
#समावेश <linux/uaccess.h>

#घोषणा PREFIX "ACPI: "

#अगर_घोषित CONFIG_CPU_FREQ

/* If a passive cooling situation is detected, primarily CPUfreq is used, as it
 * offers (in most हालs) voltage scaling in addition to frequency scaling, and
 * thus a cubic (instead of linear) reduction of energy. Also, we allow क्रम
 * _any_ cpufreq driver and not only the acpi-cpufreq driver.
 */

#घोषणा CPUFREQ_THERMAL_MIN_STEP 0
#घोषणा CPUFREQ_THERMAL_MAX_STEP 3

अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, cpufreq_thermal_reduction_pctg);

#घोषणा reduction_pctg(cpu) \
	per_cpu(cpufreq_thermal_reduction_pctg, phys_package_first_cpu(cpu))

/*
 * Emulate "per package data" using per cpu data (which should really be
 * provided अन्यथाwhere)
 *
 * Note we can lose a CPU on cpu hotunplug, in this हाल we क्रमget the state
 * temporarily. Fortunately that's not a big issue here (I hope)
 */
अटल पूर्णांक phys_package_first_cpu(पूर्णांक cpu)
अणु
	पूर्णांक i;
	पूर्णांक id = topology_physical_package_id(cpu);

	क्रम_each_online_cpu(i)
		अगर (topology_physical_package_id(i) == id)
			वापस i;
	वापस 0;
पूर्ण

अटल पूर्णांक cpu_has_cpufreq(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy policy;
	अगर (!acpi_processor_cpufreq_init || cpufreq_get_policy(&policy, cpu))
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक cpufreq_get_max_state(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!cpu_has_cpufreq(cpu))
		वापस 0;

	वापस CPUFREQ_THERMAL_MAX_STEP;
पूर्ण

अटल पूर्णांक cpufreq_get_cur_state(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!cpu_has_cpufreq(cpu))
		वापस 0;

	वापस reduction_pctg(cpu);
पूर्ण

अटल पूर्णांक cpufreq_set_cur_state(अचिन्हित पूर्णांक cpu, पूर्णांक state)
अणु
	काष्ठा cpufreq_policy *policy;
	काष्ठा acpi_processor *pr;
	अचिन्हित दीर्घ max_freq;
	पूर्णांक i, ret;

	अगर (!cpu_has_cpufreq(cpu))
		वापस 0;

	reduction_pctg(cpu) = state;

	/*
	 * Update all the CPUs in the same package because they all
	 * contribute to the temperature and often share the same
	 * frequency.
	 */
	क्रम_each_online_cpu(i) अणु
		अगर (topology_physical_package_id(i) !=
		    topology_physical_package_id(cpu))
			जारी;

		pr = per_cpu(processors, i);

		अगर (unlikely(!freq_qos_request_active(&pr->thermal_req)))
			जारी;

		policy = cpufreq_cpu_get(i);
		अगर (!policy)
			वापस -EINVAL;

		max_freq = (policy->cpuinfo.max_freq * (100 - reduction_pctg(i) * 20)) / 100;

		cpufreq_cpu_put(policy);

		ret = freq_qos_update_request(&pr->thermal_req, max_freq);
		अगर (ret < 0) अणु
			pr_warn("Failed to update thermal freq constraint: CPU%d (%d)\n",
				pr->id, ret);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम acpi_thermal_cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, policy->related_cpus) अणु
		काष्ठा acpi_processor *pr = per_cpu(processors, cpu);
		पूर्णांक ret;

		अगर (!pr)
			जारी;

		ret = freq_qos_add_request(&policy->स्थिरraपूर्णांकs,
					   &pr->thermal_req,
					   FREQ_QOS_MAX, पूर्णांक_उच्च);
		अगर (ret < 0)
			pr_err("Failed to add freq constraint for CPU%d (%d)\n",
			       cpu, ret);
	पूर्ण
पूर्ण

व्योम acpi_thermal_cpufreq_निकास(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, policy->related_cpus) अणु
		काष्ठा acpi_processor *pr = per_cpu(processors, policy->cpu);

		अगर (pr)
			freq_qos_हटाओ_request(&pr->thermal_req);
	पूर्ण
पूर्ण
#अन्यथा				/* ! CONFIG_CPU_FREQ */
अटल पूर्णांक cpufreq_get_max_state(अचिन्हित पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक cpufreq_get_cur_state(अचिन्हित पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक cpufreq_set_cur_state(अचिन्हित पूर्णांक cpu, पूर्णांक state)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

/* thermal cooling device callbacks */
अटल पूर्णांक acpi_processor_max_state(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक max_state = 0;

	/*
	 * There exists four states according to
	 * cpufreq_thermal_reduction_pctg. 0, 1, 2, 3
	 */
	max_state += cpufreq_get_max_state(pr->id);
	अगर (pr->flags.throttling)
		max_state += (pr->throttling.state_count -1);

	वापस max_state;
पूर्ण
अटल पूर्णांक
processor_get_max_state(काष्ठा thermal_cooling_device *cdev,
			अचिन्हित दीर्घ *state)
अणु
	काष्ठा acpi_device *device = cdev->devdata;
	काष्ठा acpi_processor *pr;

	अगर (!device)
		वापस -EINVAL;

	pr = acpi_driver_data(device);
	अगर (!pr)
		वापस -EINVAL;

	*state = acpi_processor_max_state(pr);
	वापस 0;
पूर्ण

अटल पूर्णांक
processor_get_cur_state(काष्ठा thermal_cooling_device *cdev,
			अचिन्हित दीर्घ *cur_state)
अणु
	काष्ठा acpi_device *device = cdev->devdata;
	काष्ठा acpi_processor *pr;

	अगर (!device)
		वापस -EINVAL;

	pr = acpi_driver_data(device);
	अगर (!pr)
		वापस -EINVAL;

	*cur_state = cpufreq_get_cur_state(pr->id);
	अगर (pr->flags.throttling)
		*cur_state += pr->throttling.state;
	वापस 0;
पूर्ण

अटल पूर्णांक
processor_set_cur_state(काष्ठा thermal_cooling_device *cdev,
			अचिन्हित दीर्घ state)
अणु
	काष्ठा acpi_device *device = cdev->devdata;
	काष्ठा acpi_processor *pr;
	पूर्णांक result = 0;
	पूर्णांक max_pstate;

	अगर (!device)
		वापस -EINVAL;

	pr = acpi_driver_data(device);
	अगर (!pr)
		वापस -EINVAL;

	max_pstate = cpufreq_get_max_state(pr->id);

	अगर (state > acpi_processor_max_state(pr))
		वापस -EINVAL;

	अगर (state <= max_pstate) अणु
		अगर (pr->flags.throttling && pr->throttling.state)
			result = acpi_processor_set_throttling(pr, 0, false);
		cpufreq_set_cur_state(pr->id, state);
	पूर्ण अन्यथा अणु
		cpufreq_set_cur_state(pr->id, max_pstate);
		result = acpi_processor_set_throttling(pr,
				state - max_pstate, false);
	पूर्ण
	वापस result;
पूर्ण

स्थिर काष्ठा thermal_cooling_device_ops processor_cooling_ops = अणु
	.get_max_state = processor_get_max_state,
	.get_cur_state = processor_get_cur_state,
	.set_cur_state = processor_set_cur_state,
पूर्ण;
