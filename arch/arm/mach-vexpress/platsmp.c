<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-vexpress/platsmp.c
 *
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 */
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/vexpress.h>

#समावेश <यंत्र/mcpm.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <plat/platsmp.h>

#समावेश "core.h"

bool __init vexpress_smp_init_ops(व्योम)
अणु
#अगर_घोषित CONFIG_MCPM
	पूर्णांक cpu;
	काष्ठा device_node *cpu_node, *cci_node;

	/*
	 * The best way to detect a multi-cluster configuration
	 * is to detect अगर the kernel can take over CCI ports
	 * control. Loop over possible CPUs and check अगर CCI
	 * port control is available.
	 * Override the शेष vexpress_smp_ops अगर so.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		bool available;

		cpu_node = of_get_cpu_node(cpu, शून्य);
		अगर (WARN(!cpu_node, "Missing cpu device node!"))
			वापस false;

		cci_node = of_parse_phandle(cpu_node, "cci-control-port", 0);
		available = cci_node && of_device_is_available(cci_node);
		of_node_put(cci_node);
		of_node_put(cpu_node);

		अगर (!available)
			वापस false;
	पूर्ण

	mcpm_smp_set_ops();
	वापस true;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा of_device_id vexpress_smp_dt_scu_match[] __initस्थिर = अणु
	अणु .compatible = "arm,cortex-a5-scu", पूर्ण,
	अणु .compatible = "arm,cortex-a9-scu", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम __init vexpress_smp_dt_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	काष्ठा device_node *scu = of_find_matching_node(शून्य,
			vexpress_smp_dt_scu_match);

	अगर (scu)
		scu_enable(of_iomap(scu, 0));

	/*
	 * Write the address of secondary startup पूर्णांकo the
	 * प्रणाली-wide flags रेजिस्टर. The boot monitor रुकोs
	 * until it receives a soft पूर्णांकerrupt, and then the
	 * secondary CPU branches to this address.
	 */
	vexpress_flags_set(__pa_symbol(versatile_secondary_startup));
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम vexpress_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	versatile_immitation_cpu_die(cpu, 0x40);
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा smp_operations vexpress_smp_dt_ops __initस्थिर = अणु
	.smp_prepare_cpus	= vexpress_smp_dt_prepare_cpus,
	.smp_secondary_init	= versatile_secondary_init,
	.smp_boot_secondary	= versatile_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= vexpress_cpu_die,
#पूर्ण_अगर
पूर्ण;
