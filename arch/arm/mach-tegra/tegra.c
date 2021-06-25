<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NVIDIA Tegra SoC device tree board support
 *
 * Copyright (C) 2011, 2013, NVIDIA Corporation
 * Copyright (C) 2010 Secret Lab Technologies, Ltd.
 * Copyright (C) 2010 Google, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk/tegra.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pda_घातer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/usb/tegra_usb_phy.h>

#समावेश <linux/firmware/trusted_foundations.h>

#समावेश <soc/tegra/fuse.h>
#समावेश <soc/tegra/pmc.h>

#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/psci.h>
#समावेश <यंत्र/setup.h>

#समावेश "board.h"
#समावेश "common.h"
#समावेश "iomap.h"
#समावेश "pm.h"
#समावेश "reset.h"
#समावेश "sleep.h"

/*
 * Storage क्रम debug-macro.S's state.
 *
 * This must be in .data not .bss so that it माला_लो initialized each समय the
 * kernel is loaded. The data is declared here rather than debug-macro.S so
 * that multiple inclusions of debug-macro.S poपूर्णांक at the same data.
 */
u32 tegra_uart_config[3] = अणु
	/* Debug UART initialization required */
	1,
	/* Debug UART physical address */
	0,
	/* Debug UART भव address */
	0,
पूर्ण;

अटल व्योम __init tegra_init_early(व्योम)
अणु
	of_रेजिस्टर_trusted_foundations();
	tegra_cpu_reset_handler_init();
	call_firmware_op(l2x0_init);
पूर्ण

अटल व्योम __init tegra_dt_init_irq(व्योम)
अणु
	tegra_init_irq();
	irqchip_init();
पूर्ण

अटल व्योम __init tegra_dt_init(व्योम)
अणु
	काष्ठा device *parent = tegra_soc_device_रेजिस्टर();

	of_platक्रमm_शेष_populate(शून्य, शून्य, parent);
पूर्ण

अटल व्योम __init tegra_dt_init_late(व्योम)
अणु
	tegra_init_suspend();

	अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_2x_SOC) &&
	    of_machine_is_compatible("compal,paz00"))
		tegra_paz00_wअगरiसमाप्त_init();

	अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_2x_SOC) &&
	    of_machine_is_compatible("nvidia,tegra20"))
		platक्रमm_device_रेजिस्टर_simple("tegra20-cpufreq", -1, शून्य, 0);

	अगर (IS_ENABLED(CONFIG_ARM_TEGRA_CPUIDLE) && !psci_smp_available())
		platक्रमm_device_रेजिस्टर_simple("tegra-cpuidle", -1, शून्य, 0);

	अगर (IS_ENABLED(CONFIG_ARCH_TEGRA_3x_SOC) &&
	    of_machine_is_compatible("nvidia,tegra30"))
		platक्रमm_device_रेजिस्टर_simple("tegra20-cpufreq", -1, शून्य, 0);
पूर्ण

अटल स्थिर अक्षर * स्थिर tegra_dt_board_compat[] = अणु
	"nvidia,tegra124",
	"nvidia,tegra114",
	"nvidia,tegra30",
	"nvidia,tegra20",
	शून्य
पूर्ण;

DT_MACHINE_START(TEGRA_DT, "NVIDIA Tegra SoC (Flattened Device Tree)")
	.l2c_aux_val	= 0x3c400000,
	.l2c_aux_mask	= 0xc20fc3ff,
	.smp		= smp_ops(tegra_smp_ops),
	.map_io		= tegra_map_common_io,
	.init_early	= tegra_init_early,
	.init_irq	= tegra_dt_init_irq,
	.init_machine	= tegra_dt_init,
	.init_late	= tegra_dt_init_late,
	.dt_compat	= tegra_dt_board_compat,
MACHINE_END
