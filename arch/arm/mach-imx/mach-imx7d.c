<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Freescale Semiconductor, Inc.
 */
#समावेश <linux/irqchip.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/imx7-iomuxc-gpr.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy.h>
#समावेश <linux/regmap.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "common.h"

अटल पूर्णांक ar8031_phy_fixup(काष्ठा phy_device *dev)
अणु
	u16 val;

	/* Set RGMII IO voltage to 1.8V */
	phy_ग_लिखो(dev, 0x1d, 0x1f);
	phy_ग_लिखो(dev, 0x1e, 0x8);

	/* disable phy AR8031 SmartEEE function. */
	phy_ग_लिखो(dev, 0xd, 0x3);
	phy_ग_लिखो(dev, 0xe, 0x805d);
	phy_ग_लिखो(dev, 0xd, 0x4003);
	val = phy_पढ़ो(dev, 0xe);
	val &= ~(0x1 << 8);
	phy_ग_लिखो(dev, 0xe, val);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm54220_phy_fixup(काष्ठा phy_device *dev)
अणु
	/* enable RXC skew select RGMII copper mode */
	phy_ग_लिखो(dev, 0x1e, 0x21);
	phy_ग_लिखो(dev, 0x1f, 0x7ea8);
	phy_ग_लिखो(dev, 0x1e, 0x2f);
	phy_ग_लिखो(dev, 0x1f, 0x71b7);

	वापस 0;
पूर्ण

#घोषणा PHY_ID_AR8031	0x004dd074
#घोषणा PHY_ID_BCM54220	0x600d8589

अटल व्योम __init imx7d_enet_phy_init(व्योम)
अणु
	अगर (IS_BUILTIN(CONFIG_PHYLIB)) अणु
		phy_रेजिस्टर_fixup_क्रम_uid(PHY_ID_AR8031, 0xffffffff,
					   ar8031_phy_fixup);
		phy_रेजिस्टर_fixup_क्रम_uid(PHY_ID_BCM54220, 0xffffffff,
					   bcm54220_phy_fixup);
	पूर्ण
पूर्ण

अटल व्योम __init imx7d_enet_clk_sel(व्योम)
अणु
	काष्ठा regmap *gpr;

	gpr = syscon_regmap_lookup_by_compatible("fsl,imx7d-iomuxc-gpr");
	अगर (!IS_ERR(gpr)) अणु
		regmap_update_bits(gpr, IOMUXC_GPR1, IMX7D_GPR1_ENET_TX_CLK_SEL_MASK, 0);
		regmap_update_bits(gpr, IOMUXC_GPR1, IMX7D_GPR1_ENET_CLK_सूची_MASK, 0);
	पूर्ण अन्यथा अणु
		pr_err("failed to find fsl,imx7d-iomux-gpr regmap\n");
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम imx7d_enet_init(व्योम)
अणु
	imx7d_enet_phy_init();
	imx7d_enet_clk_sel();
पूर्ण

अटल व्योम __init imx7d_init_machine(व्योम)
अणु
	imx_anatop_init();
	imx7d_enet_init();
पूर्ण

अटल व्योम __init imx7d_init_late(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_ARM_IMX_CPUFREQ_DT))
		platक्रमm_device_रेजिस्टर_simple("imx-cpufreq-dt", -1, शून्य, 0);
पूर्ण

अटल व्योम __init imx7d_init_irq(व्योम)
अणु
	imx_init_revision_from_anatop();
	imx_src_init();
	irqchip_init();
पूर्ण

अटल स्थिर अक्षर *स्थिर imx7d_dt_compat[] __initस्थिर = अणु
	"fsl,imx7d",
	"fsl,imx7s",
	शून्य,
पूर्ण;

DT_MACHINE_START(IMX7D, "Freescale i.MX7 Dual (Device Tree)")
	.init_irq	= imx7d_init_irq,
	.init_machine	= imx7d_init_machine,
	.init_late      = imx7d_init_late,
	.dt_compat	= imx7d_dt_compat,
MACHINE_END
