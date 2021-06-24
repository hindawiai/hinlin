<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2017 Impinj, Inc
 * Author: Andrey Smirnov <andrew.smirnov@gmail.com>
 *
 * Based on the code of analogus driver:
 *
 * Copyright 2015-2017 Pengutronix, Lucas Stach <kernel@pengutronix.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/sizes.h>
#समावेश <dt-bindings/घातer/imx7-घातer.h>
#समावेश <dt-bindings/घातer/imx8mq-घातer.h>

#घोषणा GPC_LPCR_A_CORE_BSC			0x000

#घोषणा GPC_PGC_CPU_MAPPING		0x0ec

#घोषणा IMX7_USB_HSIC_PHY_A_CORE_DOMAIN		BIT(6)
#घोषणा IMX7_USB_OTG2_PHY_A_CORE_DOMAIN		BIT(5)
#घोषणा IMX7_USB_OTG1_PHY_A_CORE_DOMAIN		BIT(4)
#घोषणा IMX7_PCIE_PHY_A_CORE_DOMAIN		BIT(3)
#घोषणा IMX7_MIPI_PHY_A_CORE_DOMAIN		BIT(2)

#घोषणा IMX8M_PCIE2_A53_DOMAIN			BIT(15)
#घोषणा IMX8M_MIPI_CSI2_A53_DOMAIN		BIT(14)
#घोषणा IMX8M_MIPI_CSI1_A53_DOMAIN		BIT(13)
#घोषणा IMX8M_DISP_A53_DOMAIN			BIT(12)
#घोषणा IMX8M_HDMI_A53_DOMAIN			BIT(11)
#घोषणा IMX8M_VPU_A53_DOMAIN			BIT(10)
#घोषणा IMX8M_GPU_A53_DOMAIN			BIT(9)
#घोषणा IMX8M_DDR2_A53_DOMAIN			BIT(8)
#घोषणा IMX8M_DDR1_A53_DOMAIN			BIT(7)
#घोषणा IMX8M_OTG2_A53_DOMAIN			BIT(5)
#घोषणा IMX8M_OTG1_A53_DOMAIN			BIT(4)
#घोषणा IMX8M_PCIE1_A53_DOMAIN			BIT(3)
#घोषणा IMX8M_MIPI_A53_DOMAIN			BIT(2)

#घोषणा GPC_PU_PGC_SW_PUP_REQ		0x0f8
#घोषणा GPC_PU_PGC_SW_PDN_REQ		0x104

#घोषणा IMX7_USB_HSIC_PHY_SW_Pxx_REQ		BIT(4)
#घोषणा IMX7_USB_OTG2_PHY_SW_Pxx_REQ		BIT(3)
#घोषणा IMX7_USB_OTG1_PHY_SW_Pxx_REQ		BIT(2)
#घोषणा IMX7_PCIE_PHY_SW_Pxx_REQ		BIT(1)
#घोषणा IMX7_MIPI_PHY_SW_Pxx_REQ		BIT(0)

#घोषणा IMX8M_PCIE2_SW_Pxx_REQ			BIT(13)
#घोषणा IMX8M_MIPI_CSI2_SW_Pxx_REQ		BIT(12)
#घोषणा IMX8M_MIPI_CSI1_SW_Pxx_REQ		BIT(11)
#घोषणा IMX8M_DISP_SW_Pxx_REQ			BIT(10)
#घोषणा IMX8M_HDMI_SW_Pxx_REQ			BIT(9)
#घोषणा IMX8M_VPU_SW_Pxx_REQ			BIT(8)
#घोषणा IMX8M_GPU_SW_Pxx_REQ			BIT(7)
#घोषणा IMX8M_DDR2_SW_Pxx_REQ			BIT(6)
#घोषणा IMX8M_DDR1_SW_Pxx_REQ			BIT(5)
#घोषणा IMX8M_OTG2_SW_Pxx_REQ			BIT(3)
#घोषणा IMX8M_OTG1_SW_Pxx_REQ			BIT(2)
#घोषणा IMX8M_PCIE1_SW_Pxx_REQ			BIT(1)
#घोषणा IMX8M_MIPI_SW_Pxx_REQ			BIT(0)

#घोषणा GPC_M4_PU_PDN_FLG		0x1bc

#घोषणा GPC_PU_PWRHSK			0x1fc

#घोषणा IMX8M_GPU_HSK_PWRDNREQN			BIT(6)
#घोषणा IMX8M_VPU_HSK_PWRDNREQN			BIT(5)
#घोषणा IMX8M_DISP_HSK_PWRDNREQN		BIT(4)

/*
 * The PGC offset values in Reference Manual
 * (Rev. 1, 01/2018 and the older ones) GPC chapter's
 * GPC_PGC memory map are incorrect, below offset
 * values are from design RTL.
 */
#घोषणा IMX7_PGC_MIPI			16
#घोषणा IMX7_PGC_PCIE			17
#घोषणा IMX7_PGC_USB_HSIC		20

#घोषणा IMX8M_PGC_MIPI			16
#घोषणा IMX8M_PGC_PCIE1			17
#घोषणा IMX8M_PGC_OTG1			18
#घोषणा IMX8M_PGC_OTG2			19
#घोषणा IMX8M_PGC_DDR1			21
#घोषणा IMX8M_PGC_GPU			23
#घोषणा IMX8M_PGC_VPU			24
#घोषणा IMX8M_PGC_DISP			26
#घोषणा IMX8M_PGC_MIPI_CSI1		27
#घोषणा IMX8M_PGC_MIPI_CSI2		28
#घोषणा IMX8M_PGC_PCIE2			29

#घोषणा GPC_PGC_CTRL(n)			(0x800 + (n) * 0x40)
#घोषणा GPC_PGC_SR(n)			(GPC_PGC_CTRL(n) + 0xc)

#घोषणा GPC_PGC_CTRL_PCR		BIT(0)

#घोषणा GPC_CLK_MAX		6

काष्ठा imx_pgc_करोमुख्य अणु
	काष्ठा generic_pm_करोमुख्य genpd;
	काष्ठा regmap *regmap;
	काष्ठा regulator *regulator;
	काष्ठा clk *clk[GPC_CLK_MAX];
	पूर्णांक num_clks;

	अचिन्हित पूर्णांक pgc;

	स्थिर काष्ठा अणु
		u32 pxx;
		u32 map;
		u32 hsk;
	पूर्ण bits;

	स्थिर पूर्णांक voltage;
	काष्ठा device *dev;
पूर्ण;

काष्ठा imx_pgc_करोमुख्य_data अणु
	स्थिर काष्ठा imx_pgc_करोमुख्य *करोमुख्यs;
	माप_प्रकार करोमुख्यs_num;
	स्थिर काष्ठा regmap_access_table *reg_access_table;
पूर्ण;

अटल पूर्णांक imx_gpc_pu_pgc_sw_pxx_req(काष्ठा generic_pm_करोमुख्य *genpd,
				      bool on)
अणु
	काष्ठा imx_pgc_करोमुख्य *करोमुख्य = container_of(genpd,
						      काष्ठा imx_pgc_करोमुख्य,
						      genpd);
	अचिन्हित पूर्णांक offset = on ?
		GPC_PU_PGC_SW_PUP_REQ : GPC_PU_PGC_SW_PDN_REQ;
	स्थिर bool enable_घातer_control = !on;
	स्थिर bool has_regulator = !IS_ERR(करोमुख्य->regulator);
	पूर्णांक i, ret = 0;
	u32 pxx_req;

	regmap_update_bits(करोमुख्य->regmap, GPC_PGC_CPU_MAPPING,
			   करोमुख्य->bits.map, करोमुख्य->bits.map);

	अगर (has_regulator && on) अणु
		ret = regulator_enable(करोमुख्य->regulator);
		अगर (ret) अणु
			dev_err(करोमुख्य->dev, "failed to enable regulator\n");
			जाओ unmap;
		पूर्ण
	पूर्ण

	/* Enable reset घड़ीs क्रम all devices in the करोमुख्य */
	क्रम (i = 0; i < करोमुख्य->num_clks; i++)
		clk_prepare_enable(करोमुख्य->clk[i]);

	अगर (enable_घातer_control)
		regmap_update_bits(करोमुख्य->regmap, GPC_PGC_CTRL(करोमुख्य->pgc),
				   GPC_PGC_CTRL_PCR, GPC_PGC_CTRL_PCR);

	अगर (करोमुख्य->bits.hsk)
		regmap_update_bits(करोमुख्य->regmap, GPC_PU_PWRHSK,
				   करोमुख्य->bits.hsk, on ? करोमुख्य->bits.hsk : 0);

	regmap_update_bits(करोमुख्य->regmap, offset,
			   करोमुख्य->bits.pxx, करोमुख्य->bits.pxx);

	/*
	 * As per "5.5.9.4 Example Code 4" in IMX7DRM.pdf रुको
	 * क्रम PUP_REQ/PDN_REQ bit to be cleared
	 */
	ret = regmap_पढ़ो_poll_समयout(करोमुख्य->regmap, offset, pxx_req,
				       !(pxx_req & करोमुख्य->bits.pxx),
				       0, USEC_PER_MSEC);
	अगर (ret) अणु
		dev_err(करोमुख्य->dev, "failed to command PGC\n");
		/*
		 * If we were in a process of enabling a
		 * करोमुख्य and failed we might as well disable
		 * the regulator we just enabled. And अगर it
		 * was the opposite situation and we failed to
		 * घातer करोwn -- keep the regulator on
		 */
		on = !on;
	पूर्ण

	अगर (enable_घातer_control)
		regmap_update_bits(करोमुख्य->regmap, GPC_PGC_CTRL(करोमुख्य->pgc),
				   GPC_PGC_CTRL_PCR, 0);

	/* Disable reset घड़ीs क्रम all devices in the करोमुख्य */
	क्रम (i = 0; i < करोमुख्य->num_clks; i++)
		clk_disable_unprepare(करोमुख्य->clk[i]);

	अगर (has_regulator && !on) अणु
		पूर्णांक err;

		err = regulator_disable(करोमुख्य->regulator);
		अगर (err)
			dev_err(करोमुख्य->dev,
				"failed to disable regulator: %d\n", err);
		/* Preserve earlier error code */
		ret = ret ?: err;
	पूर्ण
unmap:
	regmap_update_bits(करोमुख्य->regmap, GPC_PGC_CPU_MAPPING,
			   करोमुख्य->bits.map, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक imx_gpc_pu_pgc_sw_pup_req(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	वापस imx_gpc_pu_pgc_sw_pxx_req(genpd, true);
पूर्ण

अटल पूर्णांक imx_gpc_pu_pgc_sw_pdn_req(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	वापस imx_gpc_pu_pgc_sw_pxx_req(genpd, false);
पूर्ण

अटल स्थिर काष्ठा imx_pgc_करोमुख्य imx7_pgc_करोमुख्यs[] = अणु
	[IMX7_POWER_DOMAIN_MIPI_PHY] = अणु
		.genpd = अणु
			.name      = "mipi-phy",
		पूर्ण,
		.bits  = अणु
			.pxx = IMX7_MIPI_PHY_SW_Pxx_REQ,
			.map = IMX7_MIPI_PHY_A_CORE_DOMAIN,
		पूर्ण,
		.voltage   = 1000000,
		.pgc	   = IMX7_PGC_MIPI,
	पूर्ण,

	[IMX7_POWER_DOMAIN_PCIE_PHY] = अणु
		.genpd = अणु
			.name      = "pcie-phy",
		पूर्ण,
		.bits  = अणु
			.pxx = IMX7_PCIE_PHY_SW_Pxx_REQ,
			.map = IMX7_PCIE_PHY_A_CORE_DOMAIN,
		पूर्ण,
		.voltage   = 1000000,
		.pgc	   = IMX7_PGC_PCIE,
	पूर्ण,

	[IMX7_POWER_DOMAIN_USB_HSIC_PHY] = अणु
		.genpd = अणु
			.name      = "usb-hsic-phy",
		पूर्ण,
		.bits  = अणु
			.pxx = IMX7_USB_HSIC_PHY_SW_Pxx_REQ,
			.map = IMX7_USB_HSIC_PHY_A_CORE_DOMAIN,
		पूर्ण,
		.voltage   = 1200000,
		.pgc	   = IMX7_PGC_USB_HSIC,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range imx7_yes_ranges[] = अणु
		regmap_reg_range(GPC_LPCR_A_CORE_BSC,
				 GPC_M4_PU_PDN_FLG),
		regmap_reg_range(GPC_PGC_CTRL(IMX7_PGC_MIPI),
				 GPC_PGC_SR(IMX7_PGC_MIPI)),
		regmap_reg_range(GPC_PGC_CTRL(IMX7_PGC_PCIE),
				 GPC_PGC_SR(IMX7_PGC_PCIE)),
		regmap_reg_range(GPC_PGC_CTRL(IMX7_PGC_USB_HSIC),
				 GPC_PGC_SR(IMX7_PGC_USB_HSIC)),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table imx7_access_table = अणु
	.yes_ranges	= imx7_yes_ranges,
	.n_yes_ranges	= ARRAY_SIZE(imx7_yes_ranges),
पूर्ण;

अटल स्थिर काष्ठा imx_pgc_करोमुख्य_data imx7_pgc_करोमुख्य_data = अणु
	.करोमुख्यs = imx7_pgc_करोमुख्यs,
	.करोमुख्यs_num = ARRAY_SIZE(imx7_pgc_करोमुख्यs),
	.reg_access_table = &imx7_access_table,
पूर्ण;

अटल स्थिर काष्ठा imx_pgc_करोमुख्य imx8m_pgc_करोमुख्यs[] = अणु
	[IMX8M_POWER_DOMAIN_MIPI] = अणु
		.genpd = अणु
			.name      = "mipi",
		पूर्ण,
		.bits  = अणु
			.pxx = IMX8M_MIPI_SW_Pxx_REQ,
			.map = IMX8M_MIPI_A53_DOMAIN,
		पूर्ण,
		.pgc	   = IMX8M_PGC_MIPI,
	पूर्ण,

	[IMX8M_POWER_DOMAIN_PCIE1] = अणु
		.genpd = अणु
			.name = "pcie1",
		पूर्ण,
		.bits  = अणु
			.pxx = IMX8M_PCIE1_SW_Pxx_REQ,
			.map = IMX8M_PCIE1_A53_DOMAIN,
		पूर्ण,
		.pgc   = IMX8M_PGC_PCIE1,
	पूर्ण,

	[IMX8M_POWER_DOMAIN_USB_OTG1] = अणु
		.genpd = अणु
			.name = "usb-otg1",
		पूर्ण,
		.bits  = अणु
			.pxx = IMX8M_OTG1_SW_Pxx_REQ,
			.map = IMX8M_OTG1_A53_DOMAIN,
		पूर्ण,
		.pgc   = IMX8M_PGC_OTG1,
	पूर्ण,

	[IMX8M_POWER_DOMAIN_USB_OTG2] = अणु
		.genpd = अणु
			.name = "usb-otg2",
		पूर्ण,
		.bits  = अणु
			.pxx = IMX8M_OTG2_SW_Pxx_REQ,
			.map = IMX8M_OTG2_A53_DOMAIN,
		पूर्ण,
		.pgc   = IMX8M_PGC_OTG2,
	पूर्ण,

	[IMX8M_POWER_DOMAIN_DDR1] = अणु
		.genpd = अणु
			.name = "ddr1",
		पूर्ण,
		.bits  = अणु
			.pxx = IMX8M_DDR1_SW_Pxx_REQ,
			.map = IMX8M_DDR2_A53_DOMAIN,
		पूर्ण,
		.pgc   = IMX8M_PGC_DDR1,
	पूर्ण,

	[IMX8M_POWER_DOMAIN_GPU] = अणु
		.genpd = अणु
			.name = "gpu",
		पूर्ण,
		.bits  = अणु
			.pxx = IMX8M_GPU_SW_Pxx_REQ,
			.map = IMX8M_GPU_A53_DOMAIN,
			.hsk = IMX8M_GPU_HSK_PWRDNREQN,
		पूर्ण,
		.pgc   = IMX8M_PGC_GPU,
	पूर्ण,

	[IMX8M_POWER_DOMAIN_VPU] = अणु
		.genpd = अणु
			.name = "vpu",
		पूर्ण,
		.bits  = अणु
			.pxx = IMX8M_VPU_SW_Pxx_REQ,
			.map = IMX8M_VPU_A53_DOMAIN,
			.hsk = IMX8M_VPU_HSK_PWRDNREQN,
		पूर्ण,
		.pgc   = IMX8M_PGC_VPU,
	पूर्ण,

	[IMX8M_POWER_DOMAIN_DISP] = अणु
		.genpd = अणु
			.name = "disp",
		पूर्ण,
		.bits  = अणु
			.pxx = IMX8M_DISP_SW_Pxx_REQ,
			.map = IMX8M_DISP_A53_DOMAIN,
			.hsk = IMX8M_DISP_HSK_PWRDNREQN,
		पूर्ण,
		.pgc   = IMX8M_PGC_DISP,
	पूर्ण,

	[IMX8M_POWER_DOMAIN_MIPI_CSI1] = अणु
		.genpd = अणु
			.name = "mipi-csi1",
		पूर्ण,
		.bits  = अणु
			.pxx = IMX8M_MIPI_CSI1_SW_Pxx_REQ,
			.map = IMX8M_MIPI_CSI1_A53_DOMAIN,
		पूर्ण,
		.pgc   = IMX8M_PGC_MIPI_CSI1,
	पूर्ण,

	[IMX8M_POWER_DOMAIN_MIPI_CSI2] = अणु
		.genpd = अणु
			.name = "mipi-csi2",
		पूर्ण,
		.bits  = अणु
			.pxx = IMX8M_MIPI_CSI2_SW_Pxx_REQ,
			.map = IMX8M_MIPI_CSI2_A53_DOMAIN,
		पूर्ण,
		.pgc   = IMX8M_PGC_MIPI_CSI2,
	पूर्ण,

	[IMX8M_POWER_DOMAIN_PCIE2] = अणु
		.genpd = अणु
			.name = "pcie2",
		पूर्ण,
		.bits  = अणु
			.pxx = IMX8M_PCIE2_SW_Pxx_REQ,
			.map = IMX8M_PCIE2_A53_DOMAIN,
		पूर्ण,
		.pgc   = IMX8M_PGC_PCIE2,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range imx8m_yes_ranges[] = अणु
		regmap_reg_range(GPC_LPCR_A_CORE_BSC,
				 GPC_PU_PWRHSK),
		regmap_reg_range(GPC_PGC_CTRL(IMX8M_PGC_MIPI),
				 GPC_PGC_SR(IMX8M_PGC_MIPI)),
		regmap_reg_range(GPC_PGC_CTRL(IMX8M_PGC_PCIE1),
				 GPC_PGC_SR(IMX8M_PGC_PCIE1)),
		regmap_reg_range(GPC_PGC_CTRL(IMX8M_PGC_OTG1),
				 GPC_PGC_SR(IMX8M_PGC_OTG1)),
		regmap_reg_range(GPC_PGC_CTRL(IMX8M_PGC_OTG2),
				 GPC_PGC_SR(IMX8M_PGC_OTG2)),
		regmap_reg_range(GPC_PGC_CTRL(IMX8M_PGC_DDR1),
				 GPC_PGC_SR(IMX8M_PGC_DDR1)),
		regmap_reg_range(GPC_PGC_CTRL(IMX8M_PGC_GPU),
				 GPC_PGC_SR(IMX8M_PGC_GPU)),
		regmap_reg_range(GPC_PGC_CTRL(IMX8M_PGC_VPU),
				 GPC_PGC_SR(IMX8M_PGC_VPU)),
		regmap_reg_range(GPC_PGC_CTRL(IMX8M_PGC_DISP),
				 GPC_PGC_SR(IMX8M_PGC_DISP)),
		regmap_reg_range(GPC_PGC_CTRL(IMX8M_PGC_MIPI_CSI1),
				 GPC_PGC_SR(IMX8M_PGC_MIPI_CSI1)),
		regmap_reg_range(GPC_PGC_CTRL(IMX8M_PGC_MIPI_CSI2),
				 GPC_PGC_SR(IMX8M_PGC_MIPI_CSI2)),
		regmap_reg_range(GPC_PGC_CTRL(IMX8M_PGC_PCIE2),
				 GPC_PGC_SR(IMX8M_PGC_PCIE2)),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table imx8m_access_table = अणु
	.yes_ranges	= imx8m_yes_ranges,
	.n_yes_ranges	= ARRAY_SIZE(imx8m_yes_ranges),
पूर्ण;

अटल स्थिर काष्ठा imx_pgc_करोमुख्य_data imx8m_pgc_करोमुख्य_data = अणु
	.करोमुख्यs = imx8m_pgc_करोमुख्यs,
	.करोमुख्यs_num = ARRAY_SIZE(imx8m_pgc_करोमुख्यs),
	.reg_access_table = &imx8m_access_table,
पूर्ण;

अटल पूर्णांक imx_pgc_get_घड़ीs(काष्ठा imx_pgc_करोमुख्य *करोमुख्य)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; ; i++) अणु
		काष्ठा clk *clk = of_clk_get(करोमुख्य->dev->of_node, i);
		अगर (IS_ERR(clk))
			अवरोध;
		अगर (i >= GPC_CLK_MAX) अणु
			dev_err(करोमुख्य->dev, "more than %d clocks\n",
				GPC_CLK_MAX);
			ret = -EINVAL;
			जाओ clk_err;
		पूर्ण
		करोमुख्य->clk[i] = clk;
	पूर्ण
	करोमुख्य->num_clks = i;

	वापस 0;

clk_err:
	जबतक (i--)
		clk_put(करोमुख्य->clk[i]);

	वापस ret;
पूर्ण

अटल व्योम imx_pgc_put_घड़ीs(काष्ठा imx_pgc_करोमुख्य *करोमुख्य)
अणु
	पूर्णांक i;

	क्रम (i = करोमुख्य->num_clks - 1; i >= 0; i--)
		clk_put(करोमुख्य->clk[i]);
पूर्ण

अटल पूर्णांक imx_pgc_करोमुख्य_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_pgc_करोमुख्य *करोमुख्य = pdev->dev.platक्रमm_data;
	पूर्णांक ret;

	करोमुख्य->dev = &pdev->dev;

	करोमुख्य->regulator = devm_regulator_get_optional(करोमुख्य->dev, "power");
	अगर (IS_ERR(करोमुख्य->regulator)) अणु
		अगर (PTR_ERR(करोमुख्य->regulator) != -ENODEV)
			वापस dev_err_probe(करोमुख्य->dev, PTR_ERR(करोमुख्य->regulator),
					     "Failed to get domain's regulator\n");
	पूर्ण अन्यथा अगर (करोमुख्य->voltage) अणु
		regulator_set_voltage(करोमुख्य->regulator,
				      करोमुख्य->voltage, करोमुख्य->voltage);
	पूर्ण

	ret = imx_pgc_get_घड़ीs(करोमुख्य);
	अगर (ret)
		वापस dev_err_probe(करोमुख्य->dev, ret, "Failed to get domain's clocks\n");

	ret = pm_genpd_init(&करोमुख्य->genpd, शून्य, true);
	अगर (ret) अणु
		dev_err(करोमुख्य->dev, "Failed to init power domain\n");
		imx_pgc_put_घड़ीs(करोमुख्य);
		वापस ret;
	पूर्ण

	ret = of_genpd_add_provider_simple(करोमुख्य->dev->of_node,
					   &करोमुख्य->genpd);
	अगर (ret) अणु
		dev_err(करोमुख्य->dev, "Failed to add genpd provider\n");
		pm_genpd_हटाओ(&करोमुख्य->genpd);
		imx_pgc_put_घड़ीs(करोमुख्य);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक imx_pgc_करोमुख्य_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_pgc_करोमुख्य *करोमुख्य = pdev->dev.platक्रमm_data;

	of_genpd_del_provider(करोमुख्य->dev->of_node);
	pm_genpd_हटाओ(&करोमुख्य->genpd);
	imx_pgc_put_घड़ीs(करोमुख्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id imx_pgc_करोमुख्य_id[] = अणु
	अणु "imx-pgc-domain", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver imx_pgc_करोमुख्य_driver = अणु
	.driver = अणु
		.name = "imx-pgc",
	पूर्ण,
	.probe    = imx_pgc_करोमुख्य_probe,
	.हटाओ   = imx_pgc_करोमुख्य_हटाओ,
	.id_table = imx_pgc_करोमुख्य_id,
पूर्ण;
builtin_platक्रमm_driver(imx_pgc_करोमुख्य_driver)

अटल पूर्णांक imx_gpcv2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा imx_pgc_करोमुख्य_data *करोमुख्य_data =
			of_device_get_match_data(&pdev->dev);

	काष्ठा regmap_config regmap_config = अणु
		.reg_bits	= 32,
		.val_bits	= 32,
		.reg_stride	= 4,
		.rd_table	= करोमुख्य_data->reg_access_table,
		.wr_table	= करोमुख्य_data->reg_access_table,
		.max_रेजिस्टर   = SZ_4K,
	पूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *pgc_np, *np;
	काष्ठा regmap *regmap;
	व्योम __iomem *base;
	पूर्णांक ret;

	pgc_np = of_get_child_by_name(dev->of_node, "pgc");
	अगर (!pgc_np) अणु
		dev_err(dev, "No power domains specified in DT\n");
		वापस -EINVAL;
	पूर्ण

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(dev, base, &regmap_config);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(dev, "failed to init regmap (%d)\n", ret);
		वापस ret;
	पूर्ण

	क्रम_each_child_of_node(pgc_np, np) अणु
		काष्ठा platक्रमm_device *pd_pdev;
		काष्ठा imx_pgc_करोमुख्य *करोमुख्य;
		u32 करोमुख्य_index;

		ret = of_property_पढ़ो_u32(np, "reg", &करोमुख्य_index);
		अगर (ret) अणु
			dev_err(dev, "Failed to read 'reg' property\n");
			of_node_put(np);
			वापस ret;
		पूर्ण

		अगर (करोमुख्य_index >= करोमुख्य_data->करोमुख्यs_num) अणु
			dev_warn(dev,
				 "Domain index %d is out of bounds\n",
				 करोमुख्य_index);
			जारी;
		पूर्ण

		pd_pdev = platक्रमm_device_alloc("imx-pgc-domain",
						करोमुख्य_index);
		अगर (!pd_pdev) अणु
			dev_err(dev, "Failed to allocate platform device\n");
			of_node_put(np);
			वापस -ENOMEM;
		पूर्ण

		ret = platक्रमm_device_add_data(pd_pdev,
					       &करोमुख्य_data->करोमुख्यs[करोमुख्य_index],
					       माप(करोमुख्य_data->करोमुख्यs[करोमुख्य_index]));
		अगर (ret) अणु
			platक्रमm_device_put(pd_pdev);
			of_node_put(np);
			वापस ret;
		पूर्ण

		करोमुख्य = pd_pdev->dev.platक्रमm_data;
		करोमुख्य->regmap = regmap;
		करोमुख्य->genpd.घातer_on  = imx_gpc_pu_pgc_sw_pup_req;
		करोमुख्य->genpd.घातer_off = imx_gpc_pu_pgc_sw_pdn_req;

		pd_pdev->dev.parent = dev;
		pd_pdev->dev.of_node = np;

		ret = platक्रमm_device_add(pd_pdev);
		अगर (ret) अणु
			platक्रमm_device_put(pd_pdev);
			of_node_put(np);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_gpcv2_dt_ids[] = अणु
	अणु .compatible = "fsl,imx7d-gpc", .data = &imx7_pgc_करोमुख्य_data, पूर्ण,
	अणु .compatible = "fsl,imx8mq-gpc", .data = &imx8m_pgc_करोमुख्य_data, पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver imx_gpc_driver = अणु
	.driver = अणु
		.name = "imx-gpcv2",
		.of_match_table = imx_gpcv2_dt_ids,
	पूर्ण,
	.probe = imx_gpcv2_probe,
पूर्ण;
builtin_platक्रमm_driver(imx_gpc_driver)
