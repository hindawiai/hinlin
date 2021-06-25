<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright:	(C) 2018 Socionext Inc.
 * Copyright:	(C) 2015 Linaro Ltd.
 */

#समावेश <linux/cpu_pm.h>
#समावेश <linux/irqchip/arm-gic.h>
#समावेश <linux/of_address.h>
#समावेश <linux/suspend.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/idmap.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/suspend.h>

#घोषणा M10V_MAX_CPU	4
#घोषणा KERNEL_UNBOOT_FLAG	0x12345678

अटल व्योम __iomem *m10v_smp_base;

अटल पूर्णांक m10v_boot_secondary(अचिन्हित पूर्णांक l_cpu, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित पूर्णांक mpidr, cpu, cluster;

	अगर (!m10v_smp_base)
		वापस -ENXIO;

	mpidr = cpu_logical_map(l_cpu);
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);

	अगर (cpu >= M10V_MAX_CPU)
		वापस -EINVAL;

	pr_info("%s: cpu %u l_cpu %u cluster %u\n",
			__func__, cpu, l_cpu, cluster);

	ग_लिखोl(__pa_symbol(secondary_startup), m10v_smp_base + cpu * 4);
	arch_send_wakeup_ipi_mask(cpumask_of(l_cpu));

	वापस 0;
पूर्ण

अटल व्योम m10v_smp_init(अचिन्हित पूर्णांक max_cpus)
अणु
	अचिन्हित पूर्णांक mpidr, cpu, cluster;
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "socionext,milbeaut-smp-sram");
	अगर (!np)
		वापस;

	m10v_smp_base = of_iomap(np, 0);
	अगर (!m10v_smp_base)
		वापस;

	mpidr = पढ़ो_cpuid_mpidr();
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);
	pr_info("MCPM boot on cpu_%u cluster_%u\n", cpu, cluster);

	क्रम (cpu = 0; cpu < M10V_MAX_CPU; cpu++)
		ग_लिखोl(KERNEL_UNBOOT_FLAG, m10v_smp_base + cpu * 4);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम m10v_cpu_die(अचिन्हित पूर्णांक l_cpu)
अणु
	gic_cpu_अगर_करोwn(0);
	v7_निकास_coherency_flush(louis);
	wfi();
पूर्ण

अटल पूर्णांक m10v_cpu_समाप्त(अचिन्हित पूर्णांक l_cpu)
अणु
	अचिन्हित पूर्णांक mpidr, cpu;

	mpidr = cpu_logical_map(l_cpu);
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);

	ग_लिखोl(KERNEL_UNBOOT_FLAG, m10v_smp_base + cpu * 4);

	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा smp_operations m10v_smp_ops __initdata = अणु
	.smp_prepare_cpus	= m10v_smp_init,
	.smp_boot_secondary	= m10v_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= m10v_cpu_die,
	.cpu_समाप्त		= m10v_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;
CPU_METHOD_OF_DECLARE(m10v_smp, "socionext,milbeaut-m10v-smp", &m10v_smp_ops);

अटल पूर्णांक m10v_pm_valid(suspend_state_t state)
अणु
	वापस (state == PM_SUSPEND_STANDBY) || (state == PM_SUSPEND_MEM);
पूर्ण

प्रकार व्योम (*phys_reset_t)(अचिन्हित दीर्घ);
अटल phys_reset_t phys_reset;

अटल पूर्णांक m10v_die(अचिन्हित दीर्घ arg)
अणु
	setup_mm_क्रम_reboot();
	यंत्र("wfi");
	/* Boot just like a secondary */
	phys_reset = (phys_reset_t)(अचिन्हित दीर्घ)virt_to_phys(cpu_reset);
	phys_reset(virt_to_phys(cpu_resume));

	वापस 0;
पूर्ण

अटल पूर्णांक m10v_pm_enter(suspend_state_t state)
अणु
	चयन (state) अणु
	हाल PM_SUSPEND_STANDBY:
		यंत्र("wfi");
		अवरोध;
	हाल PM_SUSPEND_MEM:
		cpu_pm_enter();
		cpu_suspend(0, m10v_die);
		cpu_pm_निकास();
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops m10v_pm_ops = अणु
	.valid		= m10v_pm_valid,
	.enter		= m10v_pm_enter,
पूर्ण;

काष्ठा clk *m10v_clclk_रेजिस्टर(काष्ठा device *cpu_dev);

अटल पूर्णांक __init m10v_pm_init(व्योम)
अणु
	अगर (of_machine_is_compatible("socionext,milbeaut-evb"))
		suspend_set_ops(&m10v_pm_ops);

	वापस 0;
पूर्ण
late_initcall(m10v_pm_init);
