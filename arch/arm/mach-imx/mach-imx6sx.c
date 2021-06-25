<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014 Freescale Semiconductor, Inc.
 */

#समावेश <linux/irqchip.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/imx6q-iomuxc-gpr.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "common.h"
#समावेश "cpuidle.h"

अटल पूर्णांक ar8031_phy_fixup(काष्ठा phy_device *dev)
अणु
	u16 val;

	/* Set RGMII IO voltage to 1.8V */
	phy_ग_लिखो(dev, 0x1d, 0x1f);
	phy_ग_लिखो(dev, 0x1e, 0x8);

	/* पूर्णांकroduce tx घड़ी delay */
	phy_ग_लिखो(dev, 0x1d, 0x5);
	val = phy_पढ़ो(dev, 0x1e);
	val |= 0x0100;
	phy_ग_लिखो(dev, 0x1e, val);

	वापस 0;
पूर्ण

#घोषणा PHY_ID_AR8031   0x004dd074
अटल व्योम __init imx6sx_enet_phy_init(व्योम)
अणु
	अगर (IS_BUILTIN(CONFIG_PHYLIB))
		phy_रेजिस्टर_fixup_क्रम_uid(PHY_ID_AR8031, 0xffffffff,
					   ar8031_phy_fixup);
पूर्ण

अटल व्योम __init imx6sx_enet_clk_sel(व्योम)
अणु
	काष्ठा regmap *gpr;

	gpr = syscon_regmap_lookup_by_compatible("fsl,imx6sx-iomuxc-gpr");
	अगर (!IS_ERR(gpr)) अणु
		regmap_update_bits(gpr, IOMUXC_GPR1,
				   IMX6SX_GPR1_FEC_CLOCK_MUX_SEL_MASK, 0);
		regmap_update_bits(gpr, IOMUXC_GPR1,
				   IMX6SX_GPR1_FEC_CLOCK_PAD_सूची_MASK, 0);
	पूर्ण अन्यथा अणु
		pr_err("failed to find fsl,imx6sx-iomux-gpr regmap\n");
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम imx6sx_enet_init(व्योम)
अणु
	imx6sx_enet_phy_init();
	imx6sx_enet_clk_sel();
पूर्ण

अटल व्योम __init imx6sx_init_machine(व्योम)
अणु
	of_platक्रमm_शेष_populate(शून्य, शून्य, शून्य);

	imx6sx_enet_init();
	imx_anatop_init();
	imx6sx_pm_init();
पूर्ण

अटल व्योम __init imx6sx_init_irq(व्योम)
अणु
	imx_gpc_check_dt();
	imx_init_revision_from_anatop();
	imx_init_l2cache();
	imx_src_init();
	irqchip_init();
	imx6_pm_ccm_init("fsl,imx6sx-ccm");
पूर्ण

अटल व्योम __init imx6sx_init_late(व्योम)
अणु
	imx6sx_cpuidle_init();

	अगर (IS_ENABLED(CONFIG_ARM_IMX6Q_CPUFREQ))
		platक्रमm_device_रेजिस्टर_simple("imx6q-cpufreq", -1, शून्य, 0);
पूर्ण

अटल स्थिर अक्षर * स्थिर imx6sx_dt_compat[] __initस्थिर = अणु
	"fsl,imx6sx",
	शून्य,
पूर्ण;

DT_MACHINE_START(IMX6SX, "Freescale i.MX6 SoloX (Device Tree)")
	.l2c_aux_val 	= 0,
	.l2c_aux_mask	= ~0,
	.init_irq	= imx6sx_init_irq,
	.init_machine	= imx6sx_init_machine,
	.dt_compat	= imx6sx_dt_compat,
	.init_late	= imx6sx_init_late,
MACHINE_END
