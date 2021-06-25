<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 ARM/Linaro
 *
 * Authors: Daniel Lezcano <daniel.lezcano@linaro.org>
 *          Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
 *          Nicolas Pitre <nicolas.pitre@linaro.org>
 *
 * Maपूर्णांकainer: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
 * Maपूर्णांकainer: Daniel Lezcano <daniel.lezcano@linaro.org>
 */
#समावेश <linux/cpuidle.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/cpuidle.h>
#समावेश <यंत्र/mcpm.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/suspend.h>

#समावेश "dt_idle_states.h"

अटल पूर्णांक bl_enter_घातerकरोwn(काष्ठा cpuidle_device *dev,
			      काष्ठा cpuidle_driver *drv, पूर्णांक idx);

/*
 * NB: Owing to current menu governor behaviour big and LITTLE
 * index 1 states have to define निकास_latency and target_residency क्रम
 * cluster state since, when all CPUs in a cluster hit it, the cluster
 * can be shutकरोwn. This means that when a single CPU enters this state
 * the निकास_latency and target_residency values are somewhat overसमाप्त.
 * There is no notion of cluster states in the menu governor, so CPUs
 * have to define CPU states where possibly the cluster will be shutकरोwn
 * depending on the state of other CPUs. idle states entry and निकास happen
 * at अक्रमom बार; however the cluster state provides target_residency
 * values as अगर all CPUs in a cluster enter the state at once; this is
 * somewhat optimistic and behaviour should be fixed either in the governor
 * or in the MCPM back-ends.
 * To make this driver 100% generic the number of states and the निकास_latency
 * target_residency values must be obtained from device tree bindings.
 *
 * निकास_latency: refers to the TC2 vexpress test chip and depends on the
 * current cluster operating poपूर्णांक. It is the समय it takes to get the CPU
 * up and running when the CPU is घातered up on cluster wake-up from shutकरोwn.
 * Current values क्रम big and LITTLE clusters are provided क्रम clusters
 * running at शेष operating poपूर्णांकs.
 *
 * target_residency: it is the minimum amount of समय the cluster has
 * to be करोwn to अवरोध even in terms of घातer consumption. cluster
 * shutकरोwn has inherent dynamic घातer costs (L2 ग_लिखोbacks to DRAM
 * being the मुख्य factor) that depend on the current operating poपूर्णांकs.
 * The current values क्रम both clusters are provided क्रम a CPU whose half
 * of L2 lines are dirty and require cleaning to DRAM, and takes पूर्णांकo
 * account leakage अटल घातer values related to the vexpress TC2 testchip.
 */
अटल काष्ठा cpuidle_driver bl_idle_little_driver = अणु
	.name = "little_idle",
	.owner = THIS_MODULE,
	.states[0] = ARM_CPUIDLE_WFI_STATE,
	.states[1] = अणु
		.enter			= bl_enter_घातerकरोwn,
		.निकास_latency		= 700,
		.target_residency	= 2500,
		.flags			= CPUIDLE_FLAG_TIMER_STOP,
		.name			= "C1",
		.desc			= "ARM little-cluster power down",
	पूर्ण,
	.state_count = 2,
पूर्ण;

अटल स्थिर काष्ठा of_device_id bl_idle_state_match[] __initस्थिर = अणु
	अणु .compatible = "arm,idle-state",
	  .data = bl_enter_घातerकरोwn पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा cpuidle_driver bl_idle_big_driver = अणु
	.name = "big_idle",
	.owner = THIS_MODULE,
	.states[0] = ARM_CPUIDLE_WFI_STATE,
	.states[1] = अणु
		.enter			= bl_enter_घातerकरोwn,
		.निकास_latency		= 500,
		.target_residency	= 2000,
		.flags			= CPUIDLE_FLAG_TIMER_STOP,
		.name			= "C1",
		.desc			= "ARM big-cluster power down",
	पूर्ण,
	.state_count = 2,
पूर्ण;

/*
 * notrace prevents trace shims from getting inserted where they
 * should not. Global jumps and ldrex/strex must not be inserted
 * in घातer करोwn sequences where caches and MMU may be turned off.
 */
अटल पूर्णांक notrace bl_घातerकरोwn_finisher(अचिन्हित दीर्घ arg)
अणु
	/* MCPM works with HW CPU identअगरiers */
	अचिन्हित पूर्णांक mpidr = पढ़ो_cpuid_mpidr();
	अचिन्हित पूर्णांक cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);
	अचिन्हित पूर्णांक cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);

	mcpm_set_entry_vector(cpu, cluster, cpu_resume);
	mcpm_cpu_suspend();

	/* वापस value != 0 means failure */
	वापस 1;
पूर्ण

/**
 * bl_enter_घातerकरोwn - Programs CPU to enter the specअगरied state
 * @dev: cpuidle device
 * @drv: The target state to be programmed
 * @idx: state index
 *
 * Called from the CPUidle framework to program the device to the
 * specअगरied target state selected by the governor.
 */
अटल पूर्णांक bl_enter_घातerकरोwn(काष्ठा cpuidle_device *dev,
				काष्ठा cpuidle_driver *drv, पूर्णांक idx)
अणु
	cpu_pm_enter();

	cpu_suspend(0, bl_घातerकरोwn_finisher);

	/* संकेतs the MCPM core that CPU is out of low घातer state */
	mcpm_cpu_घातered_up();

	cpu_pm_निकास();

	वापस idx;
पूर्ण

अटल पूर्णांक __init bl_idle_driver_init(काष्ठा cpuidle_driver *drv, पूर्णांक part_id)
अणु
	काष्ठा cpumask *cpumask;
	पूर्णांक cpu;

	cpumask = kzalloc(cpumask_size(), GFP_KERNEL);
	अगर (!cpumask)
		वापस -ENOMEM;

	क्रम_each_possible_cpu(cpu)
		अगर (smp_cpuid_part(cpu) == part_id)
			cpumask_set_cpu(cpu, cpumask);

	drv->cpumask = cpumask;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id compatible_machine_match[] = अणु
	अणु .compatible = "arm,vexpress,v2p-ca15_a7" पूर्ण,
	अणु .compatible = "google,peach" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init bl_idle_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा device_node *root = of_find_node_by_path("/");
	स्थिर काष्ठा of_device_id *match_id;

	अगर (!root)
		वापस -ENODEV;

	/*
	 * Initialize the driver just क्रम a compliant set of machines
	 */
	match_id = of_match_node(compatible_machine_match, root);

	of_node_put(root);

	अगर (!match_id)
		वापस -ENODEV;

	अगर (!mcpm_is_available())
		वापस -EUNATCH;

	/*
	 * For now the dअगरferentiation between little and big cores
	 * is based on the part number. A7 cores are considered little
	 * cores, A15 are considered big cores. This distinction may
	 * evolve in the future with a more generic matching approach.
	 */
	ret = bl_idle_driver_init(&bl_idle_little_driver,
				  ARM_CPU_PART_CORTEX_A7);
	अगर (ret)
		वापस ret;

	ret = bl_idle_driver_init(&bl_idle_big_driver, ARM_CPU_PART_CORTEX_A15);
	अगर (ret)
		जाओ out_uninit_little;

	/* Start at index 1, index 0 standard WFI */
	ret = dt_init_idle_driver(&bl_idle_big_driver, bl_idle_state_match, 1);
	अगर (ret < 0)
		जाओ out_uninit_big;

	/* Start at index 1, index 0 standard WFI */
	ret = dt_init_idle_driver(&bl_idle_little_driver,
				  bl_idle_state_match, 1);
	अगर (ret < 0)
		जाओ out_uninit_big;

	ret = cpuidle_रेजिस्टर(&bl_idle_little_driver, शून्य);
	अगर (ret)
		जाओ out_uninit_big;

	ret = cpuidle_रेजिस्टर(&bl_idle_big_driver, शून्य);
	अगर (ret)
		जाओ out_unरेजिस्टर_little;

	वापस 0;

out_unरेजिस्टर_little:
	cpuidle_unरेजिस्टर(&bl_idle_little_driver);
out_uninit_big:
	kमुक्त(bl_idle_big_driver.cpumask);
out_uninit_little:
	kमुक्त(bl_idle_little_driver.cpumask);

	वापस ret;
पूर्ण
device_initcall(bl_idle_init);
