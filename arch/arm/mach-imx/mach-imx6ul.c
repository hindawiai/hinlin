<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Freescale Semiconductor, Inc.
 */
#समावेश <linux/irqchip.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/imx6q-iomuxc-gpr.h>
#समावेश <linux/micrel_phy.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy.h>
#समावेश <linux/regmap.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "common.h"
#समावेश "cpuidle.h"
#समावेश "hardware.h"

अटल व्योम __init imx6ul_enet_clk_init(व्योम)
अणु
	काष्ठा regmap *gpr;

	gpr = syscon_regmap_lookup_by_compatible("fsl,imx6ul-iomuxc-gpr");
	अगर (!IS_ERR(gpr))
		regmap_update_bits(gpr, IOMUXC_GPR1, IMX6UL_GPR1_ENET_CLK_सूची,
				   IMX6UL_GPR1_ENET_CLK_OUTPUT);
	अन्यथा
		pr_err("failed to find fsl,imx6ul-iomux-gpr regmap\n");
पूर्ण

अटल अंतरभूत व्योम imx6ul_enet_init(व्योम)
अणु
	imx6ul_enet_clk_init();
पूर्ण

अटल व्योम __init imx6ul_init_machine(व्योम)
अणु
	imx_prपूर्णांक_silicon_rev(cpu_is_imx6ull() ? "i.MX6ULL" : "i.MX6UL",
		imx_get_soc_revision());

	of_platक्रमm_शेष_populate(शून्य, शून्य, शून्य);
	imx6ul_enet_init();
	imx_anatop_init();
	imx6ul_pm_init();
पूर्ण

अटल व्योम __init imx6ul_init_irq(व्योम)
अणु
	imx_init_revision_from_anatop();
	imx_src_init();
	irqchip_init();
	imx6_pm_ccm_init("fsl,imx6ul-ccm");
पूर्ण

अटल व्योम __init imx6ul_init_late(व्योम)
अणु
	imx6sx_cpuidle_init();

	अगर (IS_ENABLED(CONFIG_ARM_IMX6Q_CPUFREQ))
		platक्रमm_device_रेजिस्टर_simple("imx6q-cpufreq", -1, शून्य, 0);
पूर्ण

अटल स्थिर अक्षर * स्थिर imx6ul_dt_compat[] __initस्थिर = अणु
	"fsl,imx6ul",
	"fsl,imx6ull",
	शून्य,
पूर्ण;

DT_MACHINE_START(IMX6UL, "Freescale i.MX6 Ultralite (Device Tree)")
	.init_irq	= imx6ul_init_irq,
	.init_machine	= imx6ul_init_machine,
	.init_late	= imx6ul_init_late,
	.dt_compat	= imx6ul_dt_compat,
MACHINE_END
