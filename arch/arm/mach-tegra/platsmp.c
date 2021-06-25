<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-tegra/platsmp.c
 *
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 *
 *  Copyright (C) 2009 Palm
 *  All Rights Reserved
 */

#समावेश <linux/clk/tegra.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/smp.h>

#समावेश <soc/tegra/flowctrl.h>
#समावेश <soc/tegra/fuse.h>
#समावेश <soc/tegra/pmc.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>

#समावेश "common.h"
#समावेश "iomap.h"
#समावेश "reset.h"

अटल cpumask_t tegra_cpu_init_mask;

अटल व्योम tegra_secondary_init(अचिन्हित पूर्णांक cpu)
अणु
	cpumask_set_cpu(cpu, &tegra_cpu_init_mask);
पूर्ण


अटल पूर्णांक tegra20_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	cpu = cpu_logical_map(cpu);

	/*
	 * Force the CPU पूर्णांकo reset. The CPU must reमुख्य in reset when
	 * the flow controller state is cleared (which will cause the
	 * flow controller to stop driving reset अगर the CPU has been
	 * घातer-gated via the flow controller). This will have no
	 * effect on first boot of the CPU since it should alपढ़ोy be
	 * in reset.
	 */
	tegra_put_cpu_in_reset(cpu);

	/*
	 * Unhalt the CPU. If the flow controller was used to
	 * घातer-gate the CPU this will cause the flow controller to
	 * stop driving reset. The CPU will reमुख्य in reset because the
	 * घड़ी and reset block is now driving reset.
	 */
	flowctrl_ग_लिखो_cpu_halt(cpu, 0);

	tegra_enable_cpu_घड़ी(cpu);
	flowctrl_ग_लिखो_cpu_csr(cpu, 0); /* Clear flow controller CSR. */
	tegra_cpu_out_of_reset(cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra30_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;

	cpu = cpu_logical_map(cpu);
	tegra_put_cpu_in_reset(cpu);
	flowctrl_ग_लिखो_cpu_halt(cpu, 0);

	/*
	 * The घातer up sequence of cold boot CPU and warm boot CPU
	 * was dअगरferent.
	 *
	 * For warm boot CPU that was resumed from CPU hotplug, the
	 * घातer will be resumed स्वतःmatically after un-halting the
	 * flow controller of the warm boot CPU. We need to रुको क्रम
	 * the confirmaiton that the CPU is घातered then removing
	 * the IO clamps.
	 * For cold boot CPU, करो not रुको. After the cold boot CPU be
	 * booted, it will run to tegra_secondary_init() and set
	 * tegra_cpu_init_mask which influences what tegra30_boot_secondary()
	 * next समय around.
	 */
	अगर (cpumask_test_cpu(cpu, &tegra_cpu_init_mask)) अणु
		समयout = jअगरfies + msecs_to_jअगरfies(50);
		करो अणु
			अगर (tegra_pmc_cpu_is_घातered(cpu))
				जाओ हटाओ_clamps;
			udelay(10);
		पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));
	पूर्ण

	/*
	 * The घातer status of the cold boot CPU is घातer gated as
	 * शेष. To घातer up the cold boot CPU, the घातer should
	 * be un-gated by un-toggling the घातer gate रेजिस्टर
	 * manually.
	 */
	ret = tegra_pmc_cpu_घातer_on(cpu);
	अगर (ret)
		वापस ret;

हटाओ_clamps:
	/* CPU partition is घातered. Enable the CPU घड़ी. */
	tegra_enable_cpu_घड़ी(cpu);
	udelay(10);

	/* Remove I/O clamps. */
	ret = tegra_pmc_cpu_हटाओ_clamping(cpu);
	अगर (ret)
		वापस ret;

	udelay(10);

	flowctrl_ग_लिखो_cpu_csr(cpu, 0); /* Clear flow controller CSR. */
	tegra_cpu_out_of_reset(cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra114_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक ret = 0;

	cpu = cpu_logical_map(cpu);

	अगर (cpumask_test_cpu(cpu, &tegra_cpu_init_mask)) अणु
		/*
		 * Warm boot flow
		 * The flow controller in अक्षरge of the घातer state and
		 * control क्रम each CPU.
		 */
		/* set SCLK as event trigger क्रम flow controller */
		flowctrl_ग_लिखो_cpu_csr(cpu, 1);
		flowctrl_ग_लिखो_cpu_halt(cpu,
				FLOW_CTRL_WAITEVENT | FLOW_CTRL_SCLK_RESUME);
	पूर्ण अन्यथा अणु
		/*
		 * Cold boot flow
		 * The CPU is घातered up by toggling PMC directly. It will
		 * also initial घातer state in flow controller. After that,
		 * the CPU's घातer state is मुख्यtained by flow controller.
		 */
		ret = tegra_pmc_cpu_घातer_on(cpu);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_boot_secondary(अचिन्हित पूर्णांक cpu,
					  काष्ठा task_काष्ठा *idle)
अणु
	अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_2x_SOC) && tegra_get_chip_id() == TEGRA20)
		वापस tegra20_boot_secondary(cpu, idle);
	अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_3x_SOC) && tegra_get_chip_id() == TEGRA30)
		वापस tegra30_boot_secondary(cpu, idle);
	अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_114_SOC) && tegra_get_chip_id() == TEGRA114)
		वापस tegra114_boot_secondary(cpu, idle);
	अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_124_SOC) && tegra_get_chip_id() == TEGRA124)
		वापस tegra114_boot_secondary(cpu, idle);

	वापस -EINVAL;
पूर्ण

अटल व्योम __init tegra_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	/* Always mark the boot CPU (CPU0) as initialized. */
	cpumask_set_cpu(0, &tegra_cpu_init_mask);

	अगर (scu_a9_has_base())
		scu_enable(IO_ADDRESS(scu_a9_get_base()));
पूर्ण

स्थिर काष्ठा smp_operations tegra_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= tegra_smp_prepare_cpus,
	.smp_secondary_init	= tegra_secondary_init,
	.smp_boot_secondary	= tegra_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_समाप्त		= tegra_cpu_समाप्त,
	.cpu_die		= tegra_cpu_die,
#पूर्ण_अगर
पूर्ण;
