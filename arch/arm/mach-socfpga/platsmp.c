<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2010-2011 Calxeda, Inc.
 * Copyright 2012 Pavel Machek <pavel@denx.de>
 * Based on platsmp.c, Copyright (C) 2002 ARM Ltd.
 * Copyright (C) 2012 Altera Corporation
 */
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/smp_plat.h>

#समावेश "core.h"

अटल पूर्णांक socfpga_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक trampoline_size = &secondary_trampoline_end - &secondary_trampoline;

	अगर (socfpga_cpu1start_addr) अणु
		/* This will put CPU #1 पूर्णांकo reset. */
		ग_लिखोl(RSTMGR_MPUMODRST_CPU1,
		       rst_manager_base_addr + SOCFPGA_RSTMGR_MODMPURST);

		स_नकल(phys_to_virt(0), &secondary_trampoline, trampoline_size);

		ग_लिखोl(__pa_symbol(secondary_startup),
		       sys_manager_base_addr + (socfpga_cpu1start_addr & 0x000000ff));

		flush_cache_all();
		smp_wmb();
		outer_clean_range(0, trampoline_size);

		/* This will release CPU #1 out of reset. */
		ग_लिखोl(0, rst_manager_base_addr + SOCFPGA_RSTMGR_MODMPURST);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक socfpga_a10_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक trampoline_size = &secondary_trampoline_end - &secondary_trampoline;

	अगर (socfpga_cpu1start_addr) अणु
		ग_लिखोl(RSTMGR_MPUMODRST_CPU1, rst_manager_base_addr +
		       SOCFPGA_A10_RSTMGR_MODMPURST);
		स_नकल(phys_to_virt(0), &secondary_trampoline, trampoline_size);

		ग_लिखोl(__pa_symbol(secondary_startup),
		       sys_manager_base_addr + (socfpga_cpu1start_addr & 0x00000fff));

		flush_cache_all();
		smp_wmb();
		outer_clean_range(0, trampoline_size);

		/* This will release CPU #1 out of reset. */
		ग_लिखोl(0, rst_manager_base_addr + SOCFPGA_A10_RSTMGR_MODMPURST);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init socfpga_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *socfpga_scu_base_addr;

	np = of_find_compatible_node(शून्य, शून्य, "arm,cortex-a9-scu");
	अगर (!np) अणु
		pr_err("%s: missing scu\n", __func__);
		वापस;
	पूर्ण

	socfpga_scu_base_addr = of_iomap(np, 0);
	अगर (!socfpga_scu_base_addr)
		वापस;
	scu_enable(socfpga_scu_base_addr);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
/*
 * platक्रमm-specअगरic code to shutकरोwn a CPU
 *
 * Called with IRQs disabled
 */
अटल व्योम socfpga_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	/* Do WFI. If we wake up early, go back पूर्णांकo WFI */
	जबतक (1)
		cpu_करो_idle();
पूर्ण

/*
 * We need a dummy function so that platक्रमm_can_cpu_hotplug() knows
 * we support CPU hotplug. However, the function करोes not need to करो
 * anything, because CPUs going offline just करो WFI. We could reset
 * the CPUs but it would increase घातer consumption.
 */
अटल पूर्णांक socfpga_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा smp_operations socfpga_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= socfpga_smp_prepare_cpus,
	.smp_boot_secondary	= socfpga_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= socfpga_cpu_die,
	.cpu_समाप्त		= socfpga_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा smp_operations socfpga_a10_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= socfpga_smp_prepare_cpus,
	.smp_boot_secondary	= socfpga_a10_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= socfpga_cpu_die,
	.cpu_समाप्त		= socfpga_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;

CPU_METHOD_OF_DECLARE(socfpga_smp, "altr,socfpga-smp", &socfpga_smp_ops);
CPU_METHOD_OF_DECLARE(socfpga_a10_smp, "altr,socfpga-a10-smp", &socfpga_a10_smp_ops);
