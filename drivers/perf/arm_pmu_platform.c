<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * platक्रमm_device probing code क्रम ARM perक्रमmance counters.
 *
 * Copyright (C) 2009 picoChip Designs, Ltd., Jamie Iles
 * Copyright (C) 2010 ARM Ltd., Will Deacon <will.deacon@arm.com>
 */
#घोषणा pr_fmt(fmt) "hw perfevents: " fmt
#घोषणा dev_fmt pr_fmt

#समावेश <linux/bug.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqdesc.h>
#समावेश <linux/kconfig.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/percpu.h>
#समावेश <linux/perf/arm_pmu.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/smp.h>

अटल पूर्णांक probe_current_pmu(काष्ठा arm_pmu *pmu,
			     स्थिर काष्ठा pmu_probe_info *info)
अणु
	पूर्णांक cpu = get_cpu();
	अचिन्हित पूर्णांक cpuid = पढ़ो_cpuid_id();
	पूर्णांक ret = -ENODEV;

	pr_info("probing PMU on CPU %d\n", cpu);

	क्रम (; info->init != शून्य; info++) अणु
		अगर ((cpuid & info->mask) != info->cpuid)
			जारी;
		ret = info->init(pmu);
		अवरोध;
	पूर्ण

	put_cpu();
	वापस ret;
पूर्ण

अटल पूर्णांक pmu_parse_percpu_irq(काष्ठा arm_pmu *pmu, पूर्णांक irq)
अणु
	पूर्णांक cpu, ret;
	काष्ठा pmu_hw_events __percpu *hw_events = pmu->hw_events;

	ret = irq_get_percpu_devid_partition(irq, &pmu->supported_cpus);
	अगर (ret)
		वापस ret;

	क्रम_each_cpu(cpu, &pmu->supported_cpus)
		per_cpu(hw_events->irq, cpu) = irq;

	वापस 0;
पूर्ण

अटल bool pmu_has_irq_affinity(काष्ठा device_node *node)
अणु
	वापस !!of_find_property(node, "interrupt-affinity", शून्य);
पूर्ण

अटल पूर्णांक pmu_parse_irq_affinity(काष्ठा device *dev, पूर्णांक i)
अणु
	काष्ठा device_node *dn;
	पूर्णांक cpu;

	/*
	 * If we करोn't have an पूर्णांकerrupt-affinity property, we guess irq
	 * affinity matches our logical CPU order, as we used to assume.
	 * This is fragile, so we'll warn in pmu_parse_irqs().
	 */
	अगर (!pmu_has_irq_affinity(dev->of_node))
		वापस i;

	dn = of_parse_phandle(dev->of_node, "interrupt-affinity", i);
	अगर (!dn) अणु
		dev_warn(dev, "failed to parse interrupt-affinity[%d]\n", i);
		वापस -EINVAL;
	पूर्ण

	cpu = of_cpu_node_to_id(dn);
	अगर (cpu < 0) अणु
		dev_warn(dev, "failed to find logical CPU for %pOFn\n", dn);
		cpu = nr_cpu_ids;
	पूर्ण

	of_node_put(dn);

	वापस cpu;
पूर्ण

अटल पूर्णांक pmu_parse_irqs(काष्ठा arm_pmu *pmu)
अणु
	पूर्णांक i = 0, num_irqs;
	काष्ठा platक्रमm_device *pdev = pmu->plat_device;
	काष्ठा pmu_hw_events __percpu *hw_events = pmu->hw_events;
	काष्ठा device *dev = &pdev->dev;

	num_irqs = platक्रमm_irq_count(pdev);
	अगर (num_irqs < 0)
		वापस dev_err_probe(dev, num_irqs, "unable to count PMU IRQs\n");

	/*
	 * In this हाल we have no idea which CPUs are covered by the PMU.
	 * To match our prior behaviour, we assume all CPUs in this हाल.
	 */
	अगर (num_irqs == 0) अणु
		dev_warn(dev, "no irqs for PMU, sampling events not supported\n");
		pmu->pmu.capabilities |= PERF_PMU_CAP_NO_INTERRUPT;
		cpumask_setall(&pmu->supported_cpus);
		वापस 0;
	पूर्ण

	अगर (num_irqs == 1) अणु
		पूर्णांक irq = platक्रमm_get_irq(pdev, 0);
		अगर (irq && irq_is_percpu_devid(irq))
			वापस pmu_parse_percpu_irq(pmu, irq);
	पूर्ण

	अगर (nr_cpu_ids != 1 && !pmu_has_irq_affinity(dev->of_node))
		dev_warn(dev, "no interrupt-affinity property, guessing.\n");

	क्रम (i = 0; i < num_irqs; i++) अणु
		पूर्णांक cpu, irq;

		irq = platक्रमm_get_irq(pdev, i);
		अगर (WARN_ON(irq <= 0))
			जारी;

		अगर (irq_is_percpu_devid(irq)) अणु
			dev_warn(dev, "multiple PPIs or mismatched SPI/PPI detected\n");
			वापस -EINVAL;
		पूर्ण

		cpu = pmu_parse_irq_affinity(dev, i);
		अगर (cpu < 0)
			वापस cpu;
		अगर (cpu >= nr_cpu_ids)
			जारी;

		अगर (per_cpu(hw_events->irq, cpu)) अणु
			dev_warn(dev, "multiple PMU IRQs for the same CPU detected\n");
			वापस -EINVAL;
		पूर्ण

		per_cpu(hw_events->irq, cpu) = irq;
		cpumask_set_cpu(cpu, &pmu->supported_cpus);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक armpmu_request_irqs(काष्ठा arm_pmu *armpmu)
अणु
	काष्ठा pmu_hw_events __percpu *hw_events = armpmu->hw_events;
	पूर्णांक cpu, err = 0;

	क्रम_each_cpu(cpu, &armpmu->supported_cpus) अणु
		पूर्णांक irq = per_cpu(hw_events->irq, cpu);
		अगर (!irq)
			जारी;

		err = armpmu_request_irq(irq, cpu);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम armpmu_मुक्त_irqs(काष्ठा arm_pmu *armpmu)
अणु
	पूर्णांक cpu;
	काष्ठा pmu_hw_events __percpu *hw_events = armpmu->hw_events;

	क्रम_each_cpu(cpu, &armpmu->supported_cpus) अणु
		पूर्णांक irq = per_cpu(hw_events->irq, cpu);

		armpmu_मुक्त_irq(irq, cpu);
	पूर्ण
पूर्ण

पूर्णांक arm_pmu_device_probe(काष्ठा platक्रमm_device *pdev,
			 स्थिर काष्ठा of_device_id *of_table,
			 स्थिर काष्ठा pmu_probe_info *probe_table)
अणु
	armpmu_init_fn init_fn;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा arm_pmu *pmu;
	पूर्णांक ret = -ENODEV;

	pmu = armpmu_alloc();
	अगर (!pmu)
		वापस -ENOMEM;

	pmu->plat_device = pdev;

	ret = pmu_parse_irqs(pmu);
	अगर (ret)
		जाओ out_मुक्त;

	init_fn = of_device_get_match_data(dev);
	अगर (init_fn) अणु
		pmu->secure_access = of_property_पढ़ो_bool(dev->of_node,
							   "secure-reg-access");

		/* arm64 प्रणालीs boot only as non-secure */
		अगर (IS_ENABLED(CONFIG_ARM64) && pmu->secure_access) अणु
			dev_warn(dev, "ignoring \"secure-reg-access\" property for arm64\n");
			pmu->secure_access = false;
		पूर्ण

		ret = init_fn(pmu);
	पूर्ण अन्यथा अगर (probe_table) अणु
		cpumask_setall(&pmu->supported_cpus);
		ret = probe_current_pmu(pmu, probe_table);
	पूर्ण

	अगर (ret) अणु
		dev_err(dev, "failed to probe PMU!\n");
		जाओ out_मुक्त;
	पूर्ण

	ret = armpmu_request_irqs(pmu);
	अगर (ret)
		जाओ out_मुक्त_irqs;

	ret = armpmu_रेजिस्टर(pmu);
	अगर (ret) अणु
		dev_err(dev, "failed to register PMU devices!\n");
		जाओ out_मुक्त_irqs;
	पूर्ण

	वापस 0;

out_मुक्त_irqs:
	armpmu_मुक्त_irqs(pmu);
out_मुक्त:
	armpmu_मुक्त(pmu);
	वापस ret;
पूर्ण
