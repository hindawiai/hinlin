<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SMP support क्रम SoCs with APMU
 *
 * Copyright (C) 2014  Renesas Electronics Corporation
 * Copyright (C) 2013  Magnus Damm
 */
#समावेश <linux/cpu_pm.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/of_address.h>
#समावेश <linux/smp.h>
#समावेश <linux/suspend.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/suspend.h>
#समावेश "common.h"
#समावेश "rcar-gen2.h"

अटल काष्ठा अणु
	व्योम __iomem *iomem;
	पूर्णांक bit;
पूर्ण apmu_cpus[NR_CPUS];

#घोषणा WUPCR_OFFS	 0x10		/* Wake Up Control Register */
#घोषणा PSTR_OFFS	 0x40		/* Power Status Register */
#घोषणा CPUNCR_OFFS(n)	(0x100 + (0x10 * (n)))
					/* CPUn Power Status Control Register */
#घोषणा DBGRCR_OFFS	0x180		/* Debug Resource Reset Control Reg. */

/* Power Status Register */
#घोषणा CPUNST(r, n)	(((r) >> (n * 4)) & 3)	/* CPUn Status Bit */
#घोषणा CPUST_RUN	0		/* Run Mode */
#घोषणा CPUST_STANDBY	3		/* CoreStandby Mode */

/* Debug Resource Reset Control Register */
#घोषणा DBGCPUREN	BIT(24)		/* CPU Other Reset Request Enable */
#घोषणा DBGCPUNREN(n)	BIT((n) + 20)	/* CPUn Reset Request Enable */
#घोषणा DBGCPUPREN	BIT(19)		/* CPU Peripheral Reset Req. Enable */

अटल पूर्णांक __maybe_unused apmu_घातer_on(व्योम __iomem *p, पूर्णांक bit)
अणु
	/* request घातer on */
	ग_लिखोl_relaxed(BIT(bit), p + WUPCR_OFFS);

	/* रुको क्रम APMU to finish */
	जबतक (पढ़ोl_relaxed(p + WUPCR_OFFS) != 0)
		;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused apmu_घातer_off(व्योम __iomem *p, पूर्णांक bit)
अणु
	/* request Core Standby क्रम next WFI */
	ग_लिखोl_relaxed(3, p + CPUNCR_OFFS(bit));
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused apmu_घातer_off_poll(व्योम __iomem *p, पूर्णांक bit)
अणु
	पूर्णांक k;

	क्रम (k = 0; k < 1000; k++) अणु
		अगर (CPUNST(पढ़ोl_relaxed(p + PSTR_OFFS), bit) == CPUST_STANDBY)
			वापस 1;

		mdelay(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused apmu_wrap(पूर्णांक cpu, पूर्णांक (*fn)(व्योम __iomem *p, पूर्णांक cpu))
अणु
	व्योम __iomem *p = apmu_cpus[cpu].iomem;

	वापस p ? fn(p, apmu_cpus[cpu].bit) : -EINVAL;
पूर्ण

#अगर defined(CONFIG_HOTPLUG_CPU) || defined(CONFIG_SUSPEND)
/* nicked from arch/arm/mach-exynos/hotplug.c */
अटल अंतरभूत व्योम cpu_enter_lowघातer_a15(व्योम)
अणु
	अचिन्हित पूर्णांक v;

	यंत्र अस्थिर(
	"       mrc     p15, 0, %0, c1, c0, 0\n"
	"       bic     %0, %0, %1\n"
	"       mcr     p15, 0, %0, c1, c0, 0\n"
		: "=&r" (v)
		: "Ir" (CR_C)
		: "cc");

	flush_cache_louis();

	यंत्र अस्थिर(
	/*
	 * Turn off coherency
	 */
	"       mrc     p15, 0, %0, c1, c0, 1\n"
	"       bic     %0, %0, %1\n"
	"       mcr     p15, 0, %0, c1, c0, 1\n"
		: "=&r" (v)
		: "Ir" (0x40)
		: "cc");

	isb();
	dsb();
पूर्ण

अटल व्योम shmobile_smp_apmu_cpu_shutकरोwn(अचिन्हित पूर्णांक cpu)
अणु

	/* Select next sleep mode using the APMU */
	apmu_wrap(cpu, apmu_घातer_off);

	/* Do ARM specअगरic CPU shutकरोwn */
	cpu_enter_lowघातer_a15();
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_HOTPLUG_CPU)
अटल व्योम shmobile_smp_apmu_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	/* For this particular CPU deरेजिस्टर boot vector */
	shmobile_smp_hook(cpu, 0, 0);

	/* Shutकरोwn CPU core */
	shmobile_smp_apmu_cpu_shutकरोwn(cpu);

	/* jump to shared mach-shmobile sleep / reset code */
	shmobile_smp_sleep();
पूर्ण

अटल पूर्णांक shmobile_smp_apmu_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	वापस apmu_wrap(cpu, apmu_घातer_off_poll);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SUSPEND)
अटल पूर्णांक shmobile_smp_apmu_करो_suspend(अचिन्हित दीर्घ cpu)
अणु
	shmobile_smp_hook(cpu, __pa_symbol(cpu_resume), 0);
	shmobile_smp_apmu_cpu_shutकरोwn(cpu);
	cpu_करो_idle(); /* WFI selects Core Standby */
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम cpu_leave_lowघातer(व्योम)
अणु
	अचिन्हित पूर्णांक v;

	यंत्र अस्थिर("mrc    p15, 0, %0, c1, c0, 0\n"
		     "       orr     %0, %0, %1\n"
		     "       mcr     p15, 0, %0, c1, c0, 0\n"
		     "       mrc     p15, 0, %0, c1, c0, 1\n"
		     "       orr     %0, %0, %2\n"
		     "       mcr     p15, 0, %0, c1, c0, 1\n"
		     : "=&r" (v)
		     : "Ir" (CR_C), "Ir" (0x40)
		     : "cc");
पूर्ण

अटल पूर्णांक shmobile_smp_apmu_enter_suspend(suspend_state_t state)
अणु
	cpu_suspend(smp_processor_id(), shmobile_smp_apmu_करो_suspend);
	cpu_leave_lowघातer();
	वापस 0;
पूर्ण

व्योम __init shmobile_smp_apmu_suspend_init(व्योम)
अणु
	shmobile_suspend_ops.enter = shmobile_smp_apmu_enter_suspend;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
अटल व्योम apmu_init_cpu(काष्ठा resource *res, पूर्णांक cpu, पूर्णांक bit)
अणु
	u32 x;

	अगर ((cpu >= ARRAY_SIZE(apmu_cpus)) || apmu_cpus[cpu].iomem)
		वापस;

	apmu_cpus[cpu].iomem = ioremap(res->start, resource_size(res));
	apmu_cpus[cpu].bit = bit;

	pr_debug("apmu ioremap %d %d %pr\n", cpu, bit, res);

	/* Setup क्रम debug mode */
	x = पढ़ोl(apmu_cpus[cpu].iomem + DBGRCR_OFFS);
	x |= DBGCPUREN | DBGCPUNREN(bit) | DBGCPUPREN;
	ग_लिखोl(x, apmu_cpus[cpu].iomem + DBGRCR_OFFS);
पूर्ण

अटल स्थिर काष्ठा of_device_id apmu_ids[] = अणु
	अणु .compatible = "renesas,apmu" पूर्ण,
	अणु /*sentinel*/ पूर्ण
पूर्ण;

अटल व्योम apmu_parse_dt(व्योम (*fn)(काष्ठा resource *res, पूर्णांक cpu, पूर्णांक bit))
अणु
	काष्ठा device_node *np_apmu, *np_cpu;
	काष्ठा resource res;
	पूर्णांक bit, index;
	u32 id;

	क्रम_each_matching_node(np_apmu, apmu_ids) अणु
		/* only enable the cluster that includes the boot CPU */
		bool is_allowed = false;

		क्रम (bit = 0; bit < CONFIG_NR_CPUS; bit++) अणु
			np_cpu = of_parse_phandle(np_apmu, "cpus", bit);
			अगर (np_cpu) अणु
				अगर (!of_property_पढ़ो_u32(np_cpu, "reg", &id)) अणु
					अगर (id == cpu_logical_map(0)) अणु
						is_allowed = true;
						of_node_put(np_cpu);
						अवरोध;
					पूर्ण

				पूर्ण
				of_node_put(np_cpu);
			पूर्ण
		पूर्ण
		अगर (!is_allowed)
			जारी;

		क्रम (bit = 0; bit < CONFIG_NR_CPUS; bit++) अणु
			np_cpu = of_parse_phandle(np_apmu, "cpus", bit);
			अगर (np_cpu) अणु
				अगर (!of_property_पढ़ो_u32(np_cpu, "reg", &id)) अणु
					index = get_logical_index(id);
					अगर ((index >= 0) &&
					    !of_address_to_resource(np_apmu,
								    0, &res))
						fn(&res, index, bit);
				पूर्ण
				of_node_put(np_cpu);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init shmobile_smp_apmu_setup_boot(व्योम)
अणु
	/* install boot code shared by all CPUs */
	shmobile_boot_fn = __pa_symbol(shmobile_smp_boot);
	shmobile_boot_fn_gen2 = shmobile_boot_fn;
पूर्ण

अटल पूर्णांक shmobile_smp_apmu_boot_secondary(अचिन्हित पूर्णांक cpu,
					    काष्ठा task_काष्ठा *idle)
अणु
	/* For this particular CPU रेजिस्टर boot vector */
	shmobile_smp_hook(cpu, __pa_symbol(shmobile_boot_apmu), 0);

	वापस apmu_wrap(cpu, apmu_घातer_on);
पूर्ण

अटल व्योम __init shmobile_smp_apmu_prepare_cpus_dt(अचिन्हित पूर्णांक max_cpus)
अणु
	shmobile_smp_apmu_setup_boot();
	apmu_parse_dt(apmu_init_cpu);
	rcar_gen2_pm_init();
पूर्ण

अटल काष्ठा smp_operations apmu_smp_ops __initdata = अणु
	.smp_prepare_cpus	= shmobile_smp_apmu_prepare_cpus_dt,
	.smp_boot_secondary	= shmobile_smp_apmu_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_can_disable	= shmobile_smp_cpu_can_disable,
	.cpu_die		= shmobile_smp_apmu_cpu_die,
	.cpu_समाप्त		= shmobile_smp_apmu_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;

CPU_METHOD_OF_DECLARE(shmobile_smp_apmu, "renesas,apmu", &apmu_smp_ops);
#पूर्ण_अगर /* CONFIG_SMP */
