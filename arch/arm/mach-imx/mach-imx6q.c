<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011-2013 Freescale Semiconductor, Inc.
 * Copyright 2011 Linaro Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pci.h>
#समावेश <linux/phy.h>
#समावेश <linux/regmap.h>
#समावेश <linux/micrel_phy.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/imx6q-iomuxc-gpr.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "common.h"
#समावेश "cpuidle.h"
#समावेश "hardware.h"

/* For imx6q sabrelite board: set KSZ9021RN RGMII pad skew */
अटल पूर्णांक ksz9021rn_phy_fixup(काष्ठा phy_device *phydev)
अणु
	अगर (IS_BUILTIN(CONFIG_PHYLIB)) अणु
		/* min rx data delay */
		phy_ग_लिखो(phydev, MICREL_KSZ9021_EXTREG_CTRL,
			0x8000 | MICREL_KSZ9021_RGMII_RX_DATA_PAD_SCEW);
		phy_ग_लिखो(phydev, MICREL_KSZ9021_EXTREG_DATA_WRITE, 0x0000);

		/* max rx/tx घड़ी delay, min rx/tx control delay */
		phy_ग_लिखो(phydev, MICREL_KSZ9021_EXTREG_CTRL,
			0x8000 | MICREL_KSZ9021_RGMII_CLK_CTRL_PAD_SCEW);
		phy_ग_लिखो(phydev, MICREL_KSZ9021_EXTREG_DATA_WRITE, 0xf0f0);
		phy_ग_लिखो(phydev, MICREL_KSZ9021_EXTREG_CTRL,
			MICREL_KSZ9021_RGMII_CLK_CTRL_PAD_SCEW);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mmd_ग_लिखो_reg(काष्ठा phy_device *dev, पूर्णांक device, पूर्णांक reg, पूर्णांक val)
अणु
	phy_ग_लिखो(dev, 0x0d, device);
	phy_ग_लिखो(dev, 0x0e, reg);
	phy_ग_लिखो(dev, 0x0d, (1 << 14) | device);
	phy_ग_लिखो(dev, 0x0e, val);
पूर्ण

अटल पूर्णांक ksz9031rn_phy_fixup(काष्ठा phy_device *dev)
अणु
	/*
	 * min rx data delay, max rx/tx घड़ी delay,
	 * min rx/tx control delay
	 */
	mmd_ग_लिखो_reg(dev, 2, 4, 0);
	mmd_ग_लिखो_reg(dev, 2, 5, 0);
	mmd_ग_लिखो_reg(dev, 2, 8, 0x003ff);

	वापस 0;
पूर्ण

/*
 * fixup क्रम PLX PEX8909 bridge to configure GPIO1-7 as output High
 * as they are used क्रम slots1-7 PERST#
 */
अटल व्योम ventana_pciesw_early_fixup(काष्ठा pci_dev *dev)
अणु
	u32 dw;

	अगर (!of_machine_is_compatible("gw,ventana"))
		वापस;

	अगर (dev->devfn != 0)
		वापस;

	pci_पढ़ो_config_dword(dev, 0x62c, &dw);
	dw |= 0xaaa8; // GPIO1-7 outमाला_दो
	pci_ग_लिखो_config_dword(dev, 0x62c, dw);

	pci_पढ़ो_config_dword(dev, 0x644, &dw);
	dw |= 0xfe;   // GPIO1-7 output high
	pci_ग_लिखो_config_dword(dev, 0x644, dw);

	msleep(100);
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_PLX, 0x8609, ventana_pciesw_early_fixup);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_PLX, 0x8606, ventana_pciesw_early_fixup);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_PLX, 0x8604, ventana_pciesw_early_fixup);

अटल पूर्णांक ar8031_phy_fixup(काष्ठा phy_device *dev)
अणु
	u16 val;

	/* To enable AR8031 output a 125MHz clk from CLK_25M */
	phy_ग_लिखो(dev, 0xd, 0x7);
	phy_ग_लिखो(dev, 0xe, 0x8016);
	phy_ग_लिखो(dev, 0xd, 0x4007);

	val = phy_पढ़ो(dev, 0xe);
	val &= 0xffe3;
	val |= 0x18;
	phy_ग_लिखो(dev, 0xe, val);

	/* पूर्णांकroduce tx घड़ी delay */
	phy_ग_लिखो(dev, 0x1d, 0x5);
	val = phy_पढ़ो(dev, 0x1e);
	val |= 0x0100;
	phy_ग_लिखो(dev, 0x1e, val);

	वापस 0;
पूर्ण

#घोषणा PHY_ID_AR8031	0x004dd074

अटल पूर्णांक ar8035_phy_fixup(काष्ठा phy_device *dev)
अणु
	u16 val;

	/* Ar803x phy SmartEEE feature cause link status generates glitch,
	 * which cause ethernet link करोwn/up issue, so disable SmartEEE
	 */
	phy_ग_लिखो(dev, 0xd, 0x3);
	phy_ग_लिखो(dev, 0xe, 0x805d);
	phy_ग_लिखो(dev, 0xd, 0x4003);

	val = phy_पढ़ो(dev, 0xe);
	phy_ग_लिखो(dev, 0xe, val & ~(1 << 8));

	/*
	 * Enable 125MHz घड़ी from CLK_25M on the AR8031.  This
	 * is fed in to the IMX6 on the ENET_REF_CLK (V22) pad.
	 * Also, पूर्णांकroduce a tx घड़ी delay.
	 *
	 * This is the same as is the AR8031 fixup.
	 */
	ar8031_phy_fixup(dev);

	/*check phy घातer*/
	val = phy_पढ़ो(dev, 0x0);
	अगर (val & BMCR_PDOWN)
		phy_ग_लिखो(dev, 0x0, val & ~BMCR_PDOWN);

	वापस 0;
पूर्ण

#घोषणा PHY_ID_AR8035 0x004dd072

अटल व्योम __init imx6q_enet_phy_init(व्योम)
अणु
	अगर (IS_BUILTIN(CONFIG_PHYLIB)) अणु
		phy_रेजिस्टर_fixup_क्रम_uid(PHY_ID_KSZ9021, MICREL_PHY_ID_MASK,
				ksz9021rn_phy_fixup);
		phy_रेजिस्टर_fixup_क्रम_uid(PHY_ID_KSZ9031, MICREL_PHY_ID_MASK,
				ksz9031rn_phy_fixup);
		phy_रेजिस्टर_fixup_क्रम_uid(PHY_ID_AR8031, 0xffffffef,
				ar8031_phy_fixup);
		phy_रेजिस्टर_fixup_क्रम_uid(PHY_ID_AR8035, 0xffffffef,
				ar8035_phy_fixup);
	पूर्ण
पूर्ण

अटल व्योम __init imx6q_1588_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा clk *ptp_clk;
	काष्ठा clk *enet_ref;
	काष्ठा regmap *gpr;
	u32 clksel;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx6q-fec");
	अगर (!np) अणु
		pr_warn("%s: failed to find fec node\n", __func__);
		वापस;
	पूर्ण

	ptp_clk = of_clk_get(np, 2);
	अगर (IS_ERR(ptp_clk)) अणु
		pr_warn("%s: failed to get ptp clock\n", __func__);
		जाओ put_node;
	पूर्ण

	enet_ref = clk_get_sys(शून्य, "enet_ref");
	अगर (IS_ERR(enet_ref)) अणु
		pr_warn("%s: failed to get enet clock\n", __func__);
		जाओ put_ptp_clk;
	पूर्ण

	/*
	 * If enet_ref from ANATOP/CCM is the PTP घड़ी source, we need to
	 * set bit IOMUXC_GPR1[21].  Or the PTP घड़ी must be from pad
	 * (बाह्यal OSC), and we need to clear the bit.
	 */
	clksel = clk_is_match(ptp_clk, enet_ref) ?
				IMX6Q_GPR1_ENET_CLK_SEL_ANATOP :
				IMX6Q_GPR1_ENET_CLK_SEL_PAD;
	gpr = syscon_regmap_lookup_by_compatible("fsl,imx6q-iomuxc-gpr");
	अगर (!IS_ERR(gpr))
		regmap_update_bits(gpr, IOMUXC_GPR1,
				IMX6Q_GPR1_ENET_CLK_SEL_MASK,
				clksel);
	अन्यथा
		pr_err("failed to find fsl,imx6q-iomuxc-gpr regmap\n");

	clk_put(enet_ref);
put_ptp_clk:
	clk_put(ptp_clk);
put_node:
	of_node_put(np);
पूर्ण

अटल व्योम __init imx6q_axi_init(व्योम)
अणु
	काष्ठा regmap *gpr;
	अचिन्हित पूर्णांक mask;

	gpr = syscon_regmap_lookup_by_compatible("fsl,imx6q-iomuxc-gpr");
	अगर (!IS_ERR(gpr)) अणु
		/*
		 * Enable the cacheable attribute of VPU and IPU
		 * AXI transactions.
		 */
		mask = IMX6Q_GPR4_VPU_WR_CACHE_SEL |
			IMX6Q_GPR4_VPU_RD_CACHE_SEL |
			IMX6Q_GPR4_VPU_P_WR_CACHE_VAL |
			IMX6Q_GPR4_VPU_P_RD_CACHE_VAL_MASK |
			IMX6Q_GPR4_IPU_WR_CACHE_CTL |
			IMX6Q_GPR4_IPU_RD_CACHE_CTL;
		regmap_update_bits(gpr, IOMUXC_GPR4, mask, mask);

		/* Increase IPU पढ़ो QoS priority */
		regmap_update_bits(gpr, IOMUXC_GPR6,
				IMX6Q_GPR6_IPU1_ID00_RD_QOS_MASK |
				IMX6Q_GPR6_IPU1_ID01_RD_QOS_MASK,
				(0xf << 16) | (0x7 << 20));
		regmap_update_bits(gpr, IOMUXC_GPR7,
				IMX6Q_GPR7_IPU2_ID00_RD_QOS_MASK |
				IMX6Q_GPR7_IPU2_ID01_RD_QOS_MASK,
				(0xf << 16) | (0x7 << 20));
	पूर्ण अन्यथा अणु
		pr_warn("failed to find fsl,imx6q-iomuxc-gpr regmap\n");
	पूर्ण
पूर्ण

अटल व्योम __init imx6q_init_machine(व्योम)
अणु
	अगर (cpu_is_imx6q() && imx_get_soc_revision() >= IMX_CHIP_REVISION_2_0)
		/*
		 * SoCs that identअगरy as i.MX6Q >= rev 2.0 are really i.MX6QP.
		 * Quirk: i.MX6QP revision = i.MX6Q revision - (1, 0),
		 * e.g. i.MX6QP rev 1.1 identअगरies as i.MX6Q rev 2.1.
		 */
		imx_prपूर्णांक_silicon_rev("i.MX6QP", imx_get_soc_revision() - 0x10);
	अन्यथा
		imx_prपूर्णांक_silicon_rev(cpu_is_imx6dl() ? "i.MX6DL" : "i.MX6Q",
				imx_get_soc_revision());

	imx6q_enet_phy_init();

	of_platक्रमm_शेष_populate(शून्य, शून्य, शून्य);

	imx_anatop_init();
	cpu_is_imx6q() ?  imx6q_pm_init() : imx6dl_pm_init();
	imx6q_1588_init();
	imx6q_axi_init();
पूर्ण

अटल व्योम __init imx6q_init_late(व्योम)
अणु
	/*
	 * WAIT mode is broken on imx6 Dual/Quad revision 1.0 and 1.1 so
	 * there is no poपूर्णांक to run cpuidle on them.
	 *
	 * It करोes work on imx6 Solo/DualLite starting from 1.1
	 */
	अगर ((cpu_is_imx6q() && imx_get_soc_revision() > IMX_CHIP_REVISION_1_1) ||
	    (cpu_is_imx6dl() && imx_get_soc_revision() > IMX_CHIP_REVISION_1_0))
		imx6q_cpuidle_init();

	अगर (IS_ENABLED(CONFIG_ARM_IMX6Q_CPUFREQ))
		platक्रमm_device_रेजिस्टर_simple("imx6q-cpufreq", -1, शून्य, 0);
पूर्ण

अटल व्योम __init imx6q_map_io(व्योम)
अणु
	debug_ll_io_init();
	imx_scu_map_io();
पूर्ण

अटल व्योम __init imx6q_init_irq(व्योम)
अणु
	imx_gpc_check_dt();
	imx_init_revision_from_anatop();
	imx_init_l2cache();
	imx_src_init();
	irqchip_init();
	imx6_pm_ccm_init("fsl,imx6q-ccm");
पूर्ण

अटल स्थिर अक्षर * स्थिर imx6q_dt_compat[] __initस्थिर = अणु
	"fsl,imx6dl",
	"fsl,imx6q",
	"fsl,imx6qp",
	शून्य,
पूर्ण;

DT_MACHINE_START(IMX6Q, "Freescale i.MX6 Quad/DualLite (Device Tree)")
	.l2c_aux_val 	= 0,
	.l2c_aux_mask	= ~0,
	.smp		= smp_ops(imx_smp_ops),
	.map_io		= imx6q_map_io,
	.init_irq	= imx6q_init_irq,
	.init_machine	= imx6q_init_machine,
	.init_late      = imx6q_init_late,
	.dt_compat	= imx6q_dt_compat,
MACHINE_END
