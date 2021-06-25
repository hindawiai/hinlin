<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ACPI probing code क्रम ARM perक्रमmance counters.
 *
 * Copyright (C) 2017 ARM Ltd.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqdesc.h>
#समावेश <linux/percpu.h>
#समावेश <linux/perf/arm_pmu.h>

#समावेश <यंत्र/cputype.h>

अटल DEFINE_PER_CPU(काष्ठा arm_pmu *, probed_pmus);
अटल DEFINE_PER_CPU(पूर्णांक, pmu_irqs);

अटल पूर्णांक arm_pmu_acpi_रेजिस्टर_irq(पूर्णांक cpu)
अणु
	काष्ठा acpi_madt_generic_पूर्णांकerrupt *gicc;
	पूर्णांक gsi, trigger;

	gicc = acpi_cpu_get_madt_gicc(cpu);

	gsi = gicc->perक्रमmance_पूर्णांकerrupt;

	/*
	 * Per the ACPI spec, the MADT cannot describe a PMU that करोesn't
	 * have an पूर्णांकerrupt. QEMU advertises this by using a GSI of zero,
	 * which is not known to be valid on any hardware despite being
	 * valid per the spec. Take the pragmatic approach and reject a
	 * GSI of zero क्रम now.
	 */
	अगर (!gsi)
		वापस 0;

	अगर (gicc->flags & ACPI_MADT_PERFORMANCE_IRQ_MODE)
		trigger = ACPI_EDGE_SENSITIVE;
	अन्यथा
		trigger = ACPI_LEVEL_SENSITIVE;

	/*
	 * Helpfully, the MADT GICC करोesn't have a polarity flag क्रम the
	 * "performance interrupt". Luckily, on compliant GICs the polarity is
	 * a fixed value in HW (क्रम both SPIs and PPIs) that we cannot change
	 * from SW.
	 *
	 * Here we pass in ACPI_ACTIVE_HIGH to keep the core code happy. This
	 * may not match the real polarity, but that should not matter.
	 *
	 * Other पूर्णांकerrupt controllers are not supported with ACPI.
	 */
	वापस acpi_रेजिस्टर_gsi(शून्य, gsi, trigger, ACPI_ACTIVE_HIGH);
पूर्ण

अटल व्योम arm_pmu_acpi_unरेजिस्टर_irq(पूर्णांक cpu)
अणु
	काष्ठा acpi_madt_generic_पूर्णांकerrupt *gicc;
	पूर्णांक gsi;

	gicc = acpi_cpu_get_madt_gicc(cpu);

	gsi = gicc->perक्रमmance_पूर्णांकerrupt;
	अगर (gsi)
		acpi_unरेजिस्टर_gsi(gsi);
पूर्ण

#अगर IS_ENABLED(CONFIG_ARM_SPE_PMU)
अटल काष्ठा resource spe_resources[] = अणु
	अणु
		/* irq */
		.flags          = IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device spe_dev = अणु
	.name = ARMV8_SPE_PDEV_NAME,
	.id = -1,
	.resource = spe_resources,
	.num_resources = ARRAY_SIZE(spe_resources)
पूर्ण;

/*
 * For lack of a better place, hook the normal PMU MADT walk
 * and create a SPE device अगर we detect a recent MADT with
 * a homogeneous PPI mapping.
 */
अटल व्योम arm_spe_acpi_रेजिस्टर_device(व्योम)
अणु
	पूर्णांक cpu, hetid, irq, ret;
	bool first = true;
	u16 gsi = 0;

	/*
	 * Sanity check all the GICC tables क्रम the same पूर्णांकerrupt number.
	 * For now, we only support homogeneous ACPI/SPE machines.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा acpi_madt_generic_पूर्णांकerrupt *gicc;

		gicc = acpi_cpu_get_madt_gicc(cpu);
		अगर (gicc->header.length < ACPI_MADT_GICC_SPE)
			वापस;

		अगर (first) अणु
			gsi = gicc->spe_पूर्णांकerrupt;
			अगर (!gsi)
				वापस;
			hetid = find_acpi_cpu_topology_hetero_id(cpu);
			first = false;
		पूर्ण अन्यथा अगर ((gsi != gicc->spe_पूर्णांकerrupt) ||
			   (hetid != find_acpi_cpu_topology_hetero_id(cpu))) अणु
			pr_warn("ACPI: SPE must be homogeneous\n");
			वापस;
		पूर्ण
	पूर्ण

	irq = acpi_रेजिस्टर_gsi(शून्य, gsi, ACPI_LEVEL_SENSITIVE,
				ACPI_ACTIVE_HIGH);
	अगर (irq < 0) अणु
		pr_warn("ACPI: SPE Unable to register interrupt: %d\n", gsi);
		वापस;
	पूर्ण

	spe_resources[0].start = irq;
	ret = platक्रमm_device_रेजिस्टर(&spe_dev);
	अगर (ret < 0) अणु
		pr_warn("ACPI: SPE: Unable to register device\n");
		acpi_unरेजिस्टर_gsi(gsi);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम arm_spe_acpi_रेजिस्टर_device(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ARM_SPE_PMU */

अटल पूर्णांक arm_pmu_acpi_parse_irqs(व्योम)
अणु
	पूर्णांक irq, cpu, irq_cpu, err;

	क्रम_each_possible_cpu(cpu) अणु
		irq = arm_pmu_acpi_रेजिस्टर_irq(cpu);
		अगर (irq < 0) अणु
			err = irq;
			pr_warn("Unable to parse ACPI PMU IRQ for CPU%d: %d\n",
				cpu, err);
			जाओ out_err;
		पूर्ण अन्यथा अगर (irq == 0) अणु
			pr_warn("No ACPI PMU IRQ for CPU%d\n", cpu);
		पूर्ण

		/*
		 * Log and request the IRQ so the core arm_pmu code can manage
		 * it. We'll have to sanity-check IRQs later when we associate
		 * them with their PMUs.
		 */
		per_cpu(pmu_irqs, cpu) = irq;
		armpmu_request_irq(irq, cpu);
	पूर्ण

	वापस 0;

out_err:
	क्रम_each_possible_cpu(cpu) अणु
		irq = per_cpu(pmu_irqs, cpu);
		अगर (!irq)
			जारी;

		arm_pmu_acpi_unरेजिस्टर_irq(cpu);

		/*
		 * Blat all copies of the IRQ so that we only unरेजिस्टर the
		 * corresponding GSI once (e.g. when we have PPIs).
		 */
		क्रम_each_possible_cpu(irq_cpu) अणु
			अगर (per_cpu(pmu_irqs, irq_cpu) == irq)
				per_cpu(pmu_irqs, irq_cpu) = 0;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा arm_pmu *arm_pmu_acpi_find_alloc_pmu(व्योम)
अणु
	अचिन्हित दीर्घ cpuid = पढ़ो_cpuid_id();
	काष्ठा arm_pmu *pmu;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		pmu = per_cpu(probed_pmus, cpu);
		अगर (!pmu || pmu->acpi_cpuid != cpuid)
			जारी;

		वापस pmu;
	पूर्ण

	pmu = armpmu_alloc_atomic();
	अगर (!pmu) अणु
		pr_warn("Unable to allocate PMU for CPU%d\n",
			smp_processor_id());
		वापस शून्य;
	पूर्ण

	pmu->acpi_cpuid = cpuid;

	वापस pmu;
पूर्ण

/*
 * Check whether the new IRQ is compatible with those alपढ़ोy associated with
 * the PMU (e.g. we करोn't have mismatched PPIs).
 */
अटल bool pmu_irq_matches(काष्ठा arm_pmu *pmu, पूर्णांक irq)
अणु
	काष्ठा pmu_hw_events __percpu *hw_events = pmu->hw_events;
	पूर्णांक cpu;

	अगर (!irq)
		वापस true;

	क्रम_each_cpu(cpu, &pmu->supported_cpus) अणु
		पूर्णांक other_irq = per_cpu(hw_events->irq, cpu);
		अगर (!other_irq)
			जारी;

		अगर (irq == other_irq)
			जारी;
		अगर (!irq_is_percpu_devid(irq) && !irq_is_percpu_devid(other_irq))
			जारी;

		pr_warn("mismatched PPIs detected\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * This must run beक्रमe the common arm_pmu hotplug logic, so that we can
 * associate a CPU and its पूर्णांकerrupt beक्रमe the common code tries to manage the
 * affinity and so on.
 *
 * Note that hotplug events are serialized, so we cannot race with another CPU
 * coming up. The perf core won't खोलो events जबतक a hotplug event is in
 * progress.
 */
अटल पूर्णांक arm_pmu_acpi_cpu_starting(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा arm_pmu *pmu;
	काष्ठा pmu_hw_events __percpu *hw_events;
	पूर्णांक irq;

	/* If we've alपढ़ोy probed this CPU, we have nothing to करो */
	अगर (per_cpu(probed_pmus, cpu))
		वापस 0;

	irq = per_cpu(pmu_irqs, cpu);

	pmu = arm_pmu_acpi_find_alloc_pmu();
	अगर (!pmu)
		वापस -ENOMEM;

	per_cpu(probed_pmus, cpu) = pmu;

	अगर (pmu_irq_matches(pmu, irq)) अणु
		hw_events = pmu->hw_events;
		per_cpu(hw_events->irq, cpu) = irq;
	पूर्ण

	cpumask_set_cpu(cpu, &pmu->supported_cpus);

	/*
	 * Ideally, we'd probe the PMU here when we find the first matching
	 * CPU. We can't करो that क्रम several reasons; see the comment in
	 * arm_pmu_acpi_init().
	 *
	 * So क्रम the समय being, we're करोne.
	 */
	वापस 0;
पूर्ण

पूर्णांक arm_pmu_acpi_probe(armpmu_init_fn init_fn)
अणु
	पूर्णांक pmu_idx = 0;
	पूर्णांक cpu, ret;

	/*
	 * Initialise and रेजिस्टर the set of PMUs which we know about right
	 * now. Ideally we'd करो this in arm_pmu_acpi_cpu_starting() so that we
	 * could handle late hotplug, but this may lead to deadlock since we
	 * might try to रेजिस्टर a hotplug notअगरier instance from within a
	 * hotplug notअगरier.
	 *
	 * There's also the problem of having access to the right init_fn,
	 * without tying this too deeply पूर्णांकo the "real" PMU driver.
	 *
	 * For the moment, as with the platक्रमm/DT हाल, we need at least one
	 * of a PMU's CPUs to be online at probe समय.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा arm_pmu *pmu = per_cpu(probed_pmus, cpu);
		अक्षर *base_name;

		अगर (!pmu || pmu->name)
			जारी;

		ret = init_fn(pmu);
		अगर (ret == -ENODEV) अणु
			/* PMU not handled by this driver, or not present */
			जारी;
		पूर्ण अन्यथा अगर (ret) अणु
			pr_warn("Unable to initialise PMU for CPU%d\n", cpu);
			वापस ret;
		पूर्ण

		base_name = pmu->name;
		pmu->name = kaप्र_लिखो(GFP_KERNEL, "%s_%d", base_name, pmu_idx++);
		अगर (!pmu->name) अणु
			pr_warn("Unable to allocate PMU name for CPU%d\n", cpu);
			वापस -ENOMEM;
		पूर्ण

		ret = armpmu_रेजिस्टर(pmu);
		अगर (ret) अणु
			pr_warn("Failed to register PMU for CPU%d\n", cpu);
			kमुक्त(pmu->name);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arm_pmu_acpi_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (acpi_disabled)
		वापस 0;

	arm_spe_acpi_रेजिस्टर_device();

	ret = arm_pmu_acpi_parse_irqs();
	अगर (ret)
		वापस ret;

	ret = cpuhp_setup_state(CPUHP_AP_PERF_ARM_ACPI_STARTING,
				"perf/arm/pmu_acpi:starting",
				arm_pmu_acpi_cpu_starting, शून्य);

	वापस ret;
पूर्ण
subsys_initcall(arm_pmu_acpi_init)
