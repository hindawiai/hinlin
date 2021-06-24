<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 *  Copyright (c) 2010, 2012-2013, NVIDIA Corporation. All rights reserved.
 */

#समावेश <linux/clk/tegra.h>
#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>

#समावेश <soc/tegra/common.h>
#समावेश <soc/tegra/fuse.h>

#समावेश <यंत्र/smp_plat.h>

#समावेश "common.h"
#समावेश "sleep.h"

अटल व्योम (*tegra_hotplug_shutकरोwn)(व्योम);

पूर्णांक tegra_cpu_समाप्त(अचिन्हित cpu)
अणु
	cpu = cpu_logical_map(cpu);

	/* Clock gate the CPU */
	tegra_रुको_cpu_in_reset(cpu);
	tegra_disable_cpu_घड़ी(cpu);

	वापस 1;
पूर्ण

/*
 * platक्रमm-specअगरic code to shutकरोwn a CPU
 *
 * Called with IRQs disabled
 */
व्योम tegra_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!tegra_hotplug_shutकरोwn) अणु
		WARN(1, "hotplug is not yet initialized\n");
		वापस;
	पूर्ण

	/* Clean L1 data cache */
	tegra_disable_clean_inv_dcache(TEGRA_FLUSH_CACHE_LOUIS);

	/* Shut करोwn the current CPU. */
	tegra_hotplug_shutकरोwn();

	/* Should never वापस here. */
	BUG();
पूर्ण

अटल पूर्णांक __init tegra_hotplug_init(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_HOTPLUG_CPU))
		वापस 0;

	अगर (!soc_is_tegra())
		वापस 0;

	अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_2x_SOC) && tegra_get_chip_id() == TEGRA20)
		tegra_hotplug_shutकरोwn = tegra20_hotplug_shutकरोwn;
	अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_3x_SOC) && tegra_get_chip_id() == TEGRA30)
		tegra_hotplug_shutकरोwn = tegra30_hotplug_shutकरोwn;
	अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_114_SOC) && tegra_get_chip_id() == TEGRA114)
		tegra_hotplug_shutकरोwn = tegra30_hotplug_shutकरोwn;
	अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_124_SOC) && tegra_get_chip_id() == TEGRA124)
		tegra_hotplug_shutकरोwn = tegra30_hotplug_shutकरोwn;

	वापस 0;
पूर्ण
pure_initcall(tegra_hotplug_init);
