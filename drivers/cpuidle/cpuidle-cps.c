<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2014 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#समावेश <linux/cpu_pm.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/pm-cps.h>

/* Enumeration of the various idle states this driver may enter */
क्रमागत cps_idle_state अणु
	STATE_WAIT = 0,		/* MIPS रुको inकाष्ठाion, coherent */
	STATE_NC_WAIT,		/* MIPS रुको inकाष्ठाion, non-coherent */
	STATE_CLOCK_GATED,	/* Core घड़ी gated */
	STATE_POWER_GATED,	/* Core घातer gated */
	STATE_COUNT
पूर्ण;

अटल पूर्णांक cps_nc_enter(काष्ठा cpuidle_device *dev,
			काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	क्रमागत cps_pm_state pm_state;
	पूर्णांक err;

	/*
	 * At least one core must reमुख्य घातered up & घड़ीed in order क्रम the
	 * प्रणाली to have any hope of functioning.
	 *
	 * TODO: करोn't treat core 0 specially, just prevent the final core
	 * TODO: remap पूर्णांकerrupt affinity temporarily
	 */
	अगर (cpus_are_siblings(0, dev->cpu) && (index > STATE_NC_WAIT))
		index = STATE_NC_WAIT;

	/* Select the appropriate cps_pm_state */
	चयन (index) अणु
	हाल STATE_NC_WAIT:
		pm_state = CPS_PM_NC_WAIT;
		अवरोध;
	हाल STATE_CLOCK_GATED:
		pm_state = CPS_PM_CLOCK_GATED;
		अवरोध;
	हाल STATE_POWER_GATED:
		pm_state = CPS_PM_POWER_GATED;
		अवरोध;
	शेष:
		BUG();
		वापस -EINVAL;
	पूर्ण

	/* Notअगरy listeners the CPU is about to घातer करोwn */
	अगर ((pm_state == CPS_PM_POWER_GATED) && cpu_pm_enter())
		वापस -EINTR;

	/* Enter that state */
	err = cps_pm_enter_state(pm_state);

	/* Notअगरy listeners the CPU is back up */
	अगर (pm_state == CPS_PM_POWER_GATED)
		cpu_pm_निकास();

	वापस err ?: index;
पूर्ण

अटल काष्ठा cpuidle_driver cps_driver = अणु
	.name			= "cpc_cpuidle",
	.owner			= THIS_MODULE,
	.states = अणु
		[STATE_WAIT] = MIPS_CPUIDLE_WAIT_STATE,
		[STATE_NC_WAIT] = अणु
			.enter	= cps_nc_enter,
			.निकास_latency		= 200,
			.target_residency	= 450,
			.name	= "nc-wait",
			.desc	= "non-coherent MIPS wait",
		पूर्ण,
		[STATE_CLOCK_GATED] = अणु
			.enter	= cps_nc_enter,
			.निकास_latency		= 300,
			.target_residency	= 700,
			.flags	= CPUIDLE_FLAG_TIMER_STOP,
			.name	= "clock-gated",
			.desc	= "core clock gated",
		पूर्ण,
		[STATE_POWER_GATED] = अणु
			.enter	= cps_nc_enter,
			.निकास_latency		= 600,
			.target_residency	= 1000,
			.flags	= CPUIDLE_FLAG_TIMER_STOP,
			.name	= "power-gated",
			.desc	= "core power gated",
		पूर्ण,
	पूर्ण,
	.state_count		= STATE_COUNT,
	.safe_state_index	= 0,
पूर्ण;

अटल व्योम __init cps_cpuidle_unरेजिस्टर(व्योम)
अणु
	पूर्णांक cpu;
	काष्ठा cpuidle_device *device;

	क्रम_each_possible_cpu(cpu) अणु
		device = &per_cpu(cpuidle_dev, cpu);
		cpuidle_unरेजिस्टर_device(device);
	पूर्ण

	cpuidle_unरेजिस्टर_driver(&cps_driver);
पूर्ण

अटल पूर्णांक __init cps_cpuidle_init(व्योम)
अणु
	पूर्णांक err, cpu, i;
	काष्ठा cpuidle_device *device;

	/* Detect supported states */
	अगर (!cps_pm_support_state(CPS_PM_POWER_GATED))
		cps_driver.state_count = STATE_CLOCK_GATED + 1;
	अगर (!cps_pm_support_state(CPS_PM_CLOCK_GATED))
		cps_driver.state_count = STATE_NC_WAIT + 1;
	अगर (!cps_pm_support_state(CPS_PM_NC_WAIT))
		cps_driver.state_count = STATE_WAIT + 1;

	/* Inक्रमm the user अगर some states are unavailable */
	अगर (cps_driver.state_count < STATE_COUNT) अणु
		pr_info("cpuidle-cps: limited to ");
		चयन (cps_driver.state_count - 1) अणु
		हाल STATE_WAIT:
			pr_cont("coherent wait\n");
			अवरोध;
		हाल STATE_NC_WAIT:
			pr_cont("non-coherent wait\n");
			अवरोध;
		हाल STATE_CLOCK_GATED:
			pr_cont("clock gating\n");
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Set the coupled flag on the appropriate states अगर this प्रणाली
	 * requires it.
	 */
	अगर (coupled_coherence)
		क्रम (i = STATE_NC_WAIT; i < cps_driver.state_count; i++)
			cps_driver.states[i].flags |= CPUIDLE_FLAG_COUPLED;

	err = cpuidle_रेजिस्टर_driver(&cps_driver);
	अगर (err) अणु
		pr_err("Failed to register CPS cpuidle driver\n");
		वापस err;
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		device = &per_cpu(cpuidle_dev, cpu);
		device->cpu = cpu;
#अगर_घोषित CONFIG_ARCH_NEEDS_CPU_IDLE_COUPLED
		cpumask_copy(&device->coupled_cpus, &cpu_sibling_map[cpu]);
#पूर्ण_अगर

		err = cpuidle_रेजिस्टर_device(device);
		अगर (err) अणु
			pr_err("Failed to register CPU%d cpuidle device\n",
			       cpu);
			जाओ err_out;
		पूर्ण
	पूर्ण

	वापस 0;
err_out:
	cps_cpuidle_unरेजिस्टर();
	वापस err;
पूर्ण
device_initcall(cps_cpuidle_init);
