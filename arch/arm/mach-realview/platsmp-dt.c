<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Linus Walleij
 */
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>

#समावेश <plat/platsmp.h>

#घोषणा REALVIEW_SYS_FLAGSSET_OFFSET	0x30

अटल स्थिर काष्ठा of_device_id realview_scu_match[] = अणु
	अणु .compatible = "arm,arm11mp-scu", पूर्ण,
	अणु .compatible = "arm,cortex-a9-scu", पूर्ण,
	अणु .compatible = "arm,cortex-a5-scu", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id realview_syscon_match[] = अणु
        अणु .compatible = "arm,core-module-integrator", पूर्ण,
        अणु .compatible = "arm,realview-eb-syscon", पूर्ण,
        अणु .compatible = "arm,realview-pb11mp-syscon", पूर्ण,
        अणु .compatible = "arm,realview-pbx-syscon", पूर्ण,
        अणु पूर्ण,
पूर्ण;

अटल व्योम __init realview_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *scu_base;
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक ncores;
	पूर्णांक i;

	np = of_find_matching_node(शून्य, realview_scu_match);
	अगर (!np) अणु
		pr_err("PLATSMP: No SCU base address\n");
		वापस;
	पूर्ण
	scu_base = of_iomap(np, 0);
	of_node_put(np);
	अगर (!scu_base) अणु
		pr_err("PLATSMP: No SCU remap\n");
		वापस;
	पूर्ण

	scu_enable(scu_base);
	ncores = scu_get_core_count(scu_base);
	pr_info("SCU: %d cores detected\n", ncores);
	क्रम (i = 0; i < ncores; i++)
		set_cpu_possible(i, true);
	iounmap(scu_base);

	/* The syscon contains the magic SMP start address रेजिस्टरs */
	np = of_find_matching_node(शून्य, realview_syscon_match);
	अगर (!np) अणु
		pr_err("PLATSMP: No syscon match\n");
		वापस;
	पूर्ण
	map = syscon_node_to_regmap(np);
	अगर (IS_ERR(map)) अणु
		pr_err("PLATSMP: No syscon regmap\n");
		वापस;
	पूर्ण
	/* Put the boot address in this magic रेजिस्टर */
	regmap_ग_लिखो(map, REALVIEW_SYS_FLAGSSET_OFFSET,
		     __pa_symbol(versatile_secondary_startup));
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम realview_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	वापस versatile_immitation_cpu_die(cpu, 0x20);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा smp_operations realview_dt_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= realview_smp_prepare_cpus,
	.smp_secondary_init	= versatile_secondary_init,
	.smp_boot_secondary	= versatile_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= realview_cpu_die,
#पूर्ण_अगर
पूर्ण;
CPU_METHOD_OF_DECLARE(realview_smp, "arm,realview-smp", &realview_dt_smp_ops);
