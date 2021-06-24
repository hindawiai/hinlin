<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2013 Freescale Semiconductor, Inc.
 */

#समावेश <linux/irqchip.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/imx6q-iomuxc-gpr.h>
#समावेश <linux/regmap.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "common.h"
#समावेश "cpuidle.h"
#समावेश "hardware.h"

अटल व्योम __init imx6sl_fec_init(व्योम)
अणु
	काष्ठा regmap *gpr;

	/* set FEC घड़ी from पूर्णांकernal PLL घड़ी source */
	gpr = syscon_regmap_lookup_by_compatible("fsl,imx6sl-iomuxc-gpr");
	अगर (!IS_ERR(gpr)) अणु
		regmap_update_bits(gpr, IOMUXC_GPR1,
			IMX6SL_GPR1_FEC_CLOCK_MUX2_SEL_MASK, 0);
		regmap_update_bits(gpr, IOMUXC_GPR1,
			IMX6SL_GPR1_FEC_CLOCK_MUX1_SEL_MASK, 0);
	पूर्ण अन्यथा अणु
		pr_err("failed to find fsl,imx6sl-iomux-gpr regmap\n");
	पूर्ण
पूर्ण

अटल व्योम __init imx6sl_init_late(व्योम)
अणु
	/* imx6sl reuses imx6q cpufreq driver */
	अगर (IS_ENABLED(CONFIG_ARM_IMX6Q_CPUFREQ))
		platक्रमm_device_रेजिस्टर_simple("imx6q-cpufreq", -1, शून्य, 0);

	अगर (IS_ENABLED(CONFIG_SOC_IMX6SL) && cpu_is_imx6sl())
		imx6sl_cpuidle_init();
	अन्यथा अगर (IS_ENABLED(CONFIG_SOC_IMX6SLL))
		imx6sx_cpuidle_init();
पूर्ण

अटल व्योम __init imx6sl_init_machine(व्योम)
अणु
	of_platक्रमm_शेष_populate(शून्य, शून्य, शून्य);

	अगर (cpu_is_imx6sl())
		imx6sl_fec_init();
	imx_anatop_init();
	imx6sl_pm_init();
पूर्ण

अटल व्योम __init imx6sl_init_irq(व्योम)
अणु
	imx_gpc_check_dt();
	imx_init_revision_from_anatop();
	imx_init_l2cache();
	imx_src_init();
	irqchip_init();
	अगर (cpu_is_imx6sl())
		imx6_pm_ccm_init("fsl,imx6sl-ccm");
	अन्यथा
		imx6_pm_ccm_init("fsl,imx6sll-ccm");
पूर्ण

अटल स्थिर अक्षर * स्थिर imx6sl_dt_compat[] __initस्थिर = अणु
	"fsl,imx6sl",
	"fsl,imx6sll",
	शून्य,
पूर्ण;

DT_MACHINE_START(IMX6SL, "Freescale i.MX6 SoloLite (Device Tree)")
	.l2c_aux_val 	= 0,
	.l2c_aux_mask	= ~0,
	.init_irq	= imx6sl_init_irq,
	.init_machine	= imx6sl_init_machine,
	.init_late      = imx6sl_init_late,
	.dt_compat	= imx6sl_dt_compat,
MACHINE_END
