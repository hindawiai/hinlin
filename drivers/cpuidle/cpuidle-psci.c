<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PSCI CPU idle driver.
 *
 * Copyright (C) 2019 ARM Ltd.
 * Author: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
 */

#घोषणा pr_fmt(fmt) "CPUidle PSCI: " fmt

#समावेश <linux/cpuhotplug.h>
#समावेश <linux/cpu_cooling.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/psci.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/cpuidle.h>

#समावेश "cpuidle-psci.h"
#समावेश "dt_idle_states.h"

काष्ठा psci_cpuidle_data अणु
	u32 *psci_states;
	काष्ठा device *dev;
पूर्ण;

अटल DEFINE_PER_CPU_READ_MOSTLY(काष्ठा psci_cpuidle_data, psci_cpuidle_data);
अटल DEFINE_PER_CPU(u32, करोमुख्य_state);
अटल bool psci_cpuidle_use_cpuhp;

व्योम psci_set_करोमुख्य_state(u32 state)
अणु
	__this_cpu_ग_लिखो(करोमुख्य_state, state);
पूर्ण

अटल अंतरभूत u32 psci_get_करोमुख्य_state(व्योम)
अणु
	वापस __this_cpu_पढ़ो(करोमुख्य_state);
पूर्ण

अटल अंतरभूत पूर्णांक psci_enter_state(पूर्णांक idx, u32 state)
अणु
	वापस CPU_PM_CPU_IDLE_ENTER_PARAM(psci_cpu_suspend_enter, idx, state);
पूर्ण

अटल पूर्णांक __psci_enter_करोमुख्य_idle_state(काष्ठा cpuidle_device *dev,
					  काष्ठा cpuidle_driver *drv, पूर्णांक idx,
					  bool s2idle)
अणु
	काष्ठा psci_cpuidle_data *data = this_cpu_ptr(&psci_cpuidle_data);
	u32 *states = data->psci_states;
	काष्ठा device *pd_dev = data->dev;
	u32 state;
	पूर्णांक ret;

	ret = cpu_pm_enter();
	अगर (ret)
		वापस -1;

	/* Do runसमय PM to manage a hierarchical CPU toplogy. */
	rcu_irq_enter_irqson();
	अगर (s2idle)
		dev_pm_genpd_suspend(pd_dev);
	अन्यथा
		pm_runसमय_put_sync_suspend(pd_dev);
	rcu_irq_निकास_irqson();

	state = psci_get_करोमुख्य_state();
	अगर (!state)
		state = states[idx];

	ret = psci_cpu_suspend_enter(state) ? -1 : idx;

	rcu_irq_enter_irqson();
	अगर (s2idle)
		dev_pm_genpd_resume(pd_dev);
	अन्यथा
		pm_runसमय_get_sync(pd_dev);
	rcu_irq_निकास_irqson();

	cpu_pm_निकास();

	/* Clear the करोमुख्य state to start fresh when back from idle. */
	psci_set_करोमुख्य_state(0);
	वापस ret;
पूर्ण

अटल पूर्णांक psci_enter_करोमुख्य_idle_state(काष्ठा cpuidle_device *dev,
					काष्ठा cpuidle_driver *drv, पूर्णांक idx)
अणु
	वापस __psci_enter_करोमुख्य_idle_state(dev, drv, idx, false);
पूर्ण

अटल पूर्णांक psci_enter_s2idle_करोमुख्य_idle_state(काष्ठा cpuidle_device *dev,
					       काष्ठा cpuidle_driver *drv,
					       पूर्णांक idx)
अणु
	वापस __psci_enter_करोमुख्य_idle_state(dev, drv, idx, true);
पूर्ण

अटल पूर्णांक psci_idle_cpuhp_up(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *pd_dev = __this_cpu_पढ़ो(psci_cpuidle_data.dev);

	अगर (pd_dev)
		pm_runसमय_get_sync(pd_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक psci_idle_cpuhp_करोwn(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *pd_dev = __this_cpu_पढ़ो(psci_cpuidle_data.dev);

	अगर (pd_dev) अणु
		pm_runसमय_put_sync(pd_dev);
		/* Clear करोमुख्य state to start fresh at next online. */
		psci_set_करोमुख्य_state(0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम psci_idle_init_cpuhp(व्योम)
अणु
	पूर्णांक err;

	अगर (!psci_cpuidle_use_cpuhp)
		वापस;

	err = cpuhp_setup_state_nocalls(CPUHP_AP_CPU_PM_STARTING,
					"cpuidle/psci:online",
					psci_idle_cpuhp_up,
					psci_idle_cpuhp_करोwn);
	अगर (err)
		pr_warn("Failed %d while setup cpuhp state\n", err);
पूर्ण

अटल पूर्णांक psci_enter_idle_state(काष्ठा cpuidle_device *dev,
				काष्ठा cpuidle_driver *drv, पूर्णांक idx)
अणु
	u32 *state = __this_cpu_पढ़ो(psci_cpuidle_data.psci_states);

	वापस psci_enter_state(idx, state[idx]);
पूर्ण

अटल स्थिर काष्ठा of_device_id psci_idle_state_match[] = अणु
	अणु .compatible = "arm,idle-state",
	  .data = psci_enter_idle_state पूर्ण,
	अणु पूर्ण,
पूर्ण;

पूर्णांक psci_dt_parse_state_node(काष्ठा device_node *np, u32 *state)
अणु
	पूर्णांक err = of_property_पढ़ो_u32(np, "arm,psci-suspend-param", state);

	अगर (err) अणु
		pr_warn("%pOF missing arm,psci-suspend-param property\n", np);
		वापस err;
	पूर्ण

	अगर (!psci_घातer_state_is_valid(*state)) अणु
		pr_warn("Invalid PSCI power state %#x\n", *state);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक psci_dt_cpu_init_topology(काष्ठा cpuidle_driver *drv,
				     काष्ठा psci_cpuidle_data *data,
				     अचिन्हित पूर्णांक state_count, पूर्णांक cpu)
अणु
	/* Currently limit the hierarchical topology to be used in OSI mode. */
	अगर (!psci_has_osi_support())
		वापस 0;

	data->dev = psci_dt_attach_cpu(cpu);
	अगर (IS_ERR_OR_शून्य(data->dev))
		वापस PTR_ERR_OR_ZERO(data->dev);

	/*
	 * Using the deepest state क्रम the CPU to trigger a potential selection
	 * of a shared state क्रम the करोमुख्य, assumes the करोमुख्य states are all
	 * deeper states.
	 */
	drv->states[state_count - 1].enter = psci_enter_करोमुख्य_idle_state;
	drv->states[state_count - 1].enter_s2idle = psci_enter_s2idle_करोमुख्य_idle_state;
	psci_cpuidle_use_cpuhp = true;

	वापस 0;
पूर्ण

अटल पूर्णांक psci_dt_cpu_init_idle(काष्ठा device *dev, काष्ठा cpuidle_driver *drv,
				 काष्ठा device_node *cpu_node,
				 अचिन्हित पूर्णांक state_count, पूर्णांक cpu)
अणु
	पूर्णांक i, ret = 0;
	u32 *psci_states;
	काष्ठा device_node *state_node;
	काष्ठा psci_cpuidle_data *data = per_cpu_ptr(&psci_cpuidle_data, cpu);

	state_count++; /* Add WFI state too */
	psci_states = devm_kसुस्मृति(dev, state_count, माप(*psci_states),
				   GFP_KERNEL);
	अगर (!psci_states)
		वापस -ENOMEM;

	क्रम (i = 1; i < state_count; i++) अणु
		state_node = of_get_cpu_state_node(cpu_node, i - 1);
		अगर (!state_node)
			अवरोध;

		ret = psci_dt_parse_state_node(state_node, &psci_states[i]);
		of_node_put(state_node);

		अगर (ret)
			वापस ret;

		pr_debug("psci-power-state %#x index %d\n", psci_states[i], i);
	पूर्ण

	अगर (i != state_count)
		वापस -ENODEV;

	/* Initialize optional data, used क्रम the hierarchical topology. */
	ret = psci_dt_cpu_init_topology(drv, data, state_count, cpu);
	अगर (ret < 0)
		वापस ret;

	/* Idle states parsed correctly, store them in the per-cpu काष्ठा. */
	data->psci_states = psci_states;
	वापस 0;
पूर्ण

अटल पूर्णांक psci_cpu_init_idle(काष्ठा device *dev, काष्ठा cpuidle_driver *drv,
			      अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक state_count)
अणु
	काष्ठा device_node *cpu_node;
	पूर्णांक ret;

	/*
	 * If the PSCI cpu_suspend function hook has not been initialized
	 * idle states must not be enabled, so bail out
	 */
	अगर (!psci_ops.cpu_suspend)
		वापस -EOPNOTSUPP;

	cpu_node = of_cpu_device_node_get(cpu);
	अगर (!cpu_node)
		वापस -ENODEV;

	ret = psci_dt_cpu_init_idle(dev, drv, cpu_node, state_count, cpu);

	of_node_put(cpu_node);

	वापस ret;
पूर्ण

अटल व्योम psci_cpu_deinit_idle(पूर्णांक cpu)
अणु
	काष्ठा psci_cpuidle_data *data = per_cpu_ptr(&psci_cpuidle_data, cpu);

	psci_dt_detach_cpu(data->dev);
	psci_cpuidle_use_cpuhp = false;
पूर्ण

अटल पूर्णांक psci_idle_init_cpu(काष्ठा device *dev, पूर्णांक cpu)
अणु
	काष्ठा cpuidle_driver *drv;
	काष्ठा device_node *cpu_node;
	स्थिर अक्षर *enable_method;
	पूर्णांक ret = 0;

	cpu_node = of_cpu_device_node_get(cpu);
	अगर (!cpu_node)
		वापस -ENODEV;

	/*
	 * Check whether the enable-method क्रम the cpu is PSCI, fail
	 * अगर it is not.
	 */
	enable_method = of_get_property(cpu_node, "enable-method", शून्य);
	अगर (!enable_method || (म_भेद(enable_method, "psci")))
		ret = -ENODEV;

	of_node_put(cpu_node);
	अगर (ret)
		वापस ret;

	drv = devm_kzalloc(dev, माप(*drv), GFP_KERNEL);
	अगर (!drv)
		वापस -ENOMEM;

	drv->name = "psci_idle";
	drv->owner = THIS_MODULE;
	drv->cpumask = (काष्ठा cpumask *)cpumask_of(cpu);

	/*
	 * PSCI idle states relies on architectural WFI to be represented as
	 * state index 0.
	 */
	drv->states[0].enter = psci_enter_idle_state;
	drv->states[0].निकास_latency = 1;
	drv->states[0].target_residency = 1;
	drv->states[0].घातer_usage = अच_पूर्णांक_उच्च;
	म_नकल(drv->states[0].name, "WFI");
	म_नकल(drv->states[0].desc, "ARM WFI");

	/*
	 * If no DT idle states are detected (ret == 0) let the driver
	 * initialization fail accordingly since there is no reason to
	 * initialize the idle driver अगर only wfi is supported, the
	 * शेष archictectural back-end alपढ़ोy executes wfi
	 * on idle entry.
	 */
	ret = dt_init_idle_driver(drv, psci_idle_state_match, 1);
	अगर (ret <= 0)
		वापस ret ? : -ENODEV;

	/*
	 * Initialize PSCI idle states.
	 */
	ret = psci_cpu_init_idle(dev, drv, cpu, ret);
	अगर (ret) अणु
		pr_err("CPU %d failed to PSCI idle\n", cpu);
		वापस ret;
	पूर्ण

	ret = cpuidle_रेजिस्टर(drv, शून्य);
	अगर (ret)
		जाओ deinit;

	cpuidle_cooling_रेजिस्टर(drv);

	वापस 0;
deinit:
	psci_cpu_deinit_idle(cpu);
	वापस ret;
पूर्ण

/*
 * psci_idle_probe - Initializes PSCI cpuidle driver
 *
 * Initializes PSCI cpuidle driver क्रम all CPUs, अगर any CPU fails
 * to रेजिस्टर cpuidle driver then rollback to cancel all CPUs
 * registration.
 */
अटल पूर्णांक psci_cpuidle_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक cpu, ret;
	काष्ठा cpuidle_driver *drv;
	काष्ठा cpuidle_device *dev;

	क्रम_each_possible_cpu(cpu) अणु
		ret = psci_idle_init_cpu(&pdev->dev, cpu);
		अगर (ret)
			जाओ out_fail;
	पूर्ण

	psci_idle_init_cpuhp();
	वापस 0;

out_fail:
	जबतक (--cpu >= 0) अणु
		dev = per_cpu(cpuidle_devices, cpu);
		drv = cpuidle_get_cpu_driver(dev);
		cpuidle_unरेजिस्टर(drv);
		psci_cpu_deinit_idle(cpu);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver psci_cpuidle_driver = अणु
	.probe = psci_cpuidle_probe,
	.driver = अणु
		.name = "psci-cpuidle",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init psci_idle_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&psci_cpuidle_driver);
	अगर (ret)
		वापस ret;

	pdev = platक्रमm_device_रेजिस्टर_simple("psci-cpuidle", -1, शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		platक्रमm_driver_unरेजिस्टर(&psci_cpuidle_driver);
		वापस PTR_ERR(pdev);
	पूर्ण

	वापस 0;
पूर्ण
device_initcall(psci_idle_init);
