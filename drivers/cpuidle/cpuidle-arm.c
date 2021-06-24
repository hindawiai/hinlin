<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARM/ARM64 generic CPU idle driver.
 *
 * Copyright (C) 2014 ARM Ltd.
 * Author: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
 */

#घोषणा pr_fmt(fmt) "CPUidle arm: " fmt

#समावेश <linux/cpu_cooling.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/cpuidle.h>

#समावेश "dt_idle_states.h"

/*
 * arm_enter_idle_state - Programs CPU to enter the specअगरied state
 *
 * dev: cpuidle device
 * drv: cpuidle driver
 * idx: state index
 *
 * Called from the CPUidle framework to program the device to the
 * specअगरied target state selected by the governor.
 */
अटल पूर्णांक arm_enter_idle_state(काष्ठा cpuidle_device *dev,
				काष्ठा cpuidle_driver *drv, पूर्णांक idx)
अणु
	/*
	 * Pass idle state index to arm_cpuidle_suspend which in turn
	 * will call the CPU ops suspend protocol with idle index as a
	 * parameter.
	 */
	वापस CPU_PM_CPU_IDLE_ENTER(arm_cpuidle_suspend, idx);
पूर्ण

अटल काष्ठा cpuidle_driver arm_idle_driver __initdata = अणु
	.name = "arm_idle",
	.owner = THIS_MODULE,
	/*
	 * State at index 0 is standby wfi and considered standard
	 * on all ARM platक्रमms. If in some platक्रमms simple wfi
	 * can't be used as "state 0", DT bindings must be implemented
	 * to work around this issue and allow installing a special
	 * handler क्रम idle state index 0.
	 */
	.states[0] = अणु
		.enter                  = arm_enter_idle_state,
		.निकास_latency           = 1,
		.target_residency       = 1,
		.घातer_usage		= अच_पूर्णांक_उच्च,
		.name                   = "WFI",
		.desc                   = "ARM WFI",
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id arm_idle_state_match[] __initस्थिर = अणु
	अणु .compatible = "arm,idle-state",
	  .data = arm_enter_idle_state पूर्ण,
	अणु पूर्ण,
पूर्ण;

/*
 * arm_idle_init_cpu
 *
 * Registers the arm specअगरic cpuidle driver with the cpuidle
 * framework. It relies on core code to parse the idle states
 * and initialize them using driver data काष्ठाures accordingly.
 */
अटल पूर्णांक __init arm_idle_init_cpu(पूर्णांक cpu)
अणु
	पूर्णांक ret;
	काष्ठा cpuidle_driver *drv;

	drv = kmemdup(&arm_idle_driver, माप(*drv), GFP_KERNEL);
	अगर (!drv)
		वापस -ENOMEM;

	drv->cpumask = (काष्ठा cpumask *)cpumask_of(cpu);

	/*
	 * Initialize idle states data, starting at index 1.  This
	 * driver is DT only, अगर no DT idle states are detected (ret
	 * == 0) let the driver initialization fail accordingly since
	 * there is no reason to initialize the idle driver अगर only
	 * wfi is supported.
	 */
	ret = dt_init_idle_driver(drv, arm_idle_state_match, 1);
	अगर (ret <= 0) अणु
		ret = ret ? : -ENODEV;
		जाओ out_kमुक्त_drv;
	पूर्ण

	/*
	 * Call arch CPU operations in order to initialize
	 * idle states suspend back-end specअगरic data
	 */
	ret = arm_cpuidle_init(cpu);

	/*
	 * Allow the initialization to जारी क्रम other CPUs, अगर the
	 * reported failure is a HW misconfiguration/अवरोधage (-ENXIO).
	 *
	 * Some platक्रमms करो not support idle operations
	 * (arm_cpuidle_init() वापसing -EOPNOTSUPP), we should
	 * not flag this हाल as an error, it is a valid
	 * configuration.
	 */
	अगर (ret) अणु
		अगर (ret != -EOPNOTSUPP)
			pr_err("CPU %d failed to init idle CPU ops\n", cpu);
		ret = ret == -ENXIO ? 0 : ret;
		जाओ out_kमुक्त_drv;
	पूर्ण

	ret = cpuidle_रेजिस्टर(drv, शून्य);
	अगर (ret)
		जाओ out_kमुक्त_drv;

	cpuidle_cooling_रेजिस्टर(drv);

	वापस 0;

out_kमुक्त_drv:
	kमुक्त(drv);
	वापस ret;
पूर्ण

/*
 * arm_idle_init - Initializes arm cpuidle driver
 *
 * Initializes arm cpuidle driver क्रम all CPUs, अगर any CPU fails
 * to रेजिस्टर cpuidle driver then rollback to cancel all CPUs
 * रेजिस्टरation.
 */
अटल पूर्णांक __init arm_idle_init(व्योम)
अणु
	पूर्णांक cpu, ret;
	काष्ठा cpuidle_driver *drv;
	काष्ठा cpuidle_device *dev;

	क्रम_each_possible_cpu(cpu) अणु
		ret = arm_idle_init_cpu(cpu);
		अगर (ret)
			जाओ out_fail;
	पूर्ण

	वापस 0;

out_fail:
	जबतक (--cpu >= 0) अणु
		dev = per_cpu(cpuidle_devices, cpu);
		drv = cpuidle_get_cpu_driver(dev);
		cpuidle_unरेजिस्टर(drv);
		kमुक्त(drv);
	पूर्ण

	वापस ret;
पूर्ण
device_initcall(arm_idle_init);
