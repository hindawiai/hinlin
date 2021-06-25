<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017-2018 NXP
 *   Author: Dong Aisheng <aisheng.करोng@nxp.com>
 */

#समावेश <linux/irqchip.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "common.h"
#समावेश "cpuidle.h"
#समावेश "hardware.h"

#घोषणा SIM_JTAG_ID_REG		0x8c

अटल व्योम __init imx7ulp_set_revision(व्योम)
अणु
	काष्ठा regmap *sim;
	u32 revision;

	sim = syscon_regmap_lookup_by_compatible("fsl,imx7ulp-sim");
	अगर (IS_ERR(sim)) अणु
		pr_warn("failed to find fsl,imx7ulp-sim regmap!\n");
		वापस;
	पूर्ण

	अगर (regmap_पढ़ो(sim, SIM_JTAG_ID_REG, &revision)) अणु
		pr_warn("failed to read sim regmap!\n");
		वापस;
	पूर्ण

	/*
	 * bit[31:28] of JTAG_ID रेजिस्टर defines revision as below from B0:
	 * 0001        B0
	 * 0010        B1
	 * 0011        B2
	 */
	चयन (revision >> 28) अणु
	हाल 1:
		imx_set_soc_revision(IMX_CHIP_REVISION_2_0);
		अवरोध;
	हाल 2:
		imx_set_soc_revision(IMX_CHIP_REVISION_2_1);
		अवरोध;
	हाल 3:
		imx_set_soc_revision(IMX_CHIP_REVISION_2_2);
		अवरोध;
	शेष:
		imx_set_soc_revision(IMX_CHIP_REVISION_1_0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __init imx7ulp_init_machine(व्योम)
अणु
	imx7ulp_pm_init();

	mxc_set_cpu_type(MXC_CPU_IMX7ULP);
	imx7ulp_set_revision();
	of_platक्रमm_शेष_populate(शून्य, शून्य, शून्य);
पूर्ण

अटल स्थिर अक्षर *स्थिर imx7ulp_dt_compat[] __initस्थिर = अणु
	"fsl,imx7ulp",
	शून्य,
पूर्ण;

अटल व्योम __init imx7ulp_init_late(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_ARM_IMX_CPUFREQ_DT))
		platक्रमm_device_रेजिस्टर_simple("imx-cpufreq-dt", -1, शून्य, 0);

	imx7ulp_cpuidle_init();
पूर्ण

DT_MACHINE_START(IMX7ulp, "Freescale i.MX7ULP (Device Tree)")
	.init_machine	= imx7ulp_init_machine,
	.dt_compat	= imx7ulp_dt_compat,
	.init_late	= imx7ulp_init_late,
MACHINE_END
