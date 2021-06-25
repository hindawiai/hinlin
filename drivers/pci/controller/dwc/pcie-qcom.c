<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Qualcomm PCIe root complex driver
 *
 * Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 * Copyright 2015 Linaro Limited.
 *
 * Author: Stanimir Varbanov <svarbanov@mm-sol.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/crc8.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "../../pci.h"
#समावेश "pcie-designware.h"

#घोषणा PCIE20_PARF_SYS_CTRL			0x00
#घोषणा MST_WAKEUP_EN				BIT(13)
#घोषणा SLV_WAKEUP_EN				BIT(12)
#घोषणा MSTR_ACLK_CGC_DIS			BIT(10)
#घोषणा SLV_ACLK_CGC_DIS			BIT(9)
#घोषणा CORE_CLK_CGC_DIS			BIT(6)
#घोषणा AUX_PWR_DET				BIT(4)
#घोषणा L23_CLK_RMV_DIS				BIT(2)
#घोषणा L1_CLK_RMV_DIS				BIT(1)

#घोषणा PCIE20_PARF_PHY_CTRL			0x40
#घोषणा PHY_CTRL_PHY_TX0_TERM_OFFSET_MASK	GENMASK(20, 16)
#घोषणा PHY_CTRL_PHY_TX0_TERM_OFFSET(x)		((x) << 16)

#घोषणा PCIE20_PARF_PHY_REFCLK			0x4C
#घोषणा PHY_REFCLK_SSP_EN			BIT(16)
#घोषणा PHY_REFCLK_USE_PAD			BIT(12)

#घोषणा PCIE20_PARF_DBI_BASE_ADDR		0x168
#घोषणा PCIE20_PARF_SLV_ADDR_SPACE_SIZE		0x16C
#घोषणा PCIE20_PARF_MHI_CLOCK_RESET_CTRL	0x174
#घोषणा PCIE20_PARF_AXI_MSTR_WR_ADDR_HALT	0x178
#घोषणा PCIE20_PARF_AXI_MSTR_WR_ADDR_HALT_V2	0x1A8
#घोषणा PCIE20_PARF_LTSSM			0x1B0
#घोषणा PCIE20_PARF_SID_OFFSET			0x234
#घोषणा PCIE20_PARF_BDF_TRANSLATE_CFG		0x24C
#घोषणा PCIE20_PARF_DEVICE_TYPE			0x1000
#घोषणा PCIE20_PARF_BDF_TO_SID_TABLE_N		0x2000

#घोषणा PCIE20_ELBI_SYS_CTRL			0x04
#घोषणा PCIE20_ELBI_SYS_CTRL_LT_ENABLE		BIT(0)

#घोषणा PCIE20_AXI_MSTR_RESP_COMP_CTRL0		0x818
#घोषणा CFG_REMOTE_RD_REQ_BRIDGE_SIZE_2K	0x4
#घोषणा CFG_REMOTE_RD_REQ_BRIDGE_SIZE_4K	0x5
#घोषणा PCIE20_AXI_MSTR_RESP_COMP_CTRL1		0x81c
#घोषणा CFG_BRIDGE_SB_INIT			BIT(0)

#घोषणा PCIE_CAP_LINK1_VAL			0x2FD7F

#घोषणा PCIE20_PARF_Q2A_FLUSH			0x1AC

#घोषणा PCIE20_MISC_CONTROL_1_REG		0x8BC
#घोषणा DBI_RO_WR_EN				1

#घोषणा PERST_DELAY_US				1000
/* PARF रेजिस्टरs */
#घोषणा PCIE20_PARF_PCS_DEEMPH			0x34
#घोषणा PCS_DEEMPH_TX_DEEMPH_GEN1(x)		((x) << 16)
#घोषणा PCS_DEEMPH_TX_DEEMPH_GEN2_3_5DB(x)	((x) << 8)
#घोषणा PCS_DEEMPH_TX_DEEMPH_GEN2_6DB(x)	((x) << 0)

#घोषणा PCIE20_PARF_PCS_SWING			0x38
#घोषणा PCS_SWING_TX_SWING_FULL(x)		((x) << 8)
#घोषणा PCS_SWING_TX_SWING_LOW(x)		((x) << 0)

#घोषणा PCIE20_PARF_CONFIG_BITS		0x50
#घोषणा PHY_RX0_EQ(x)				((x) << 24)

#घोषणा PCIE20_v3_PARF_SLV_ADDR_SPACE_SIZE	0x358
#घोषणा SLV_ADDR_SPACE_SZ			0x10000000

#घोषणा PCIE20_LNK_CONTROL2_LINK_STATUS2	0xa0

#घोषणा DEVICE_TYPE_RC				0x4

#घोषणा QCOM_PCIE_2_1_0_MAX_SUPPLY	3
#घोषणा QCOM_PCIE_2_1_0_MAX_CLOCKS	5

#घोषणा QCOM_PCIE_CRC8_POLYNOMIAL (BIT(2) | BIT(1) | BIT(0))

काष्ठा qcom_pcie_resources_2_1_0 अणु
	काष्ठा clk_bulk_data clks[QCOM_PCIE_2_1_0_MAX_CLOCKS];
	काष्ठा reset_control *pci_reset;
	काष्ठा reset_control *axi_reset;
	काष्ठा reset_control *ahb_reset;
	काष्ठा reset_control *por_reset;
	काष्ठा reset_control *phy_reset;
	काष्ठा reset_control *ext_reset;
	काष्ठा regulator_bulk_data supplies[QCOM_PCIE_2_1_0_MAX_SUPPLY];
पूर्ण;

काष्ठा qcom_pcie_resources_1_0_0 अणु
	काष्ठा clk *अगरace;
	काष्ठा clk *aux;
	काष्ठा clk *master_bus;
	काष्ठा clk *slave_bus;
	काष्ठा reset_control *core;
	काष्ठा regulator *vdda;
पूर्ण;

#घोषणा QCOM_PCIE_2_3_2_MAX_SUPPLY	2
काष्ठा qcom_pcie_resources_2_3_2 अणु
	काष्ठा clk *aux_clk;
	काष्ठा clk *master_clk;
	काष्ठा clk *slave_clk;
	काष्ठा clk *cfg_clk;
	काष्ठा clk *pipe_clk;
	काष्ठा regulator_bulk_data supplies[QCOM_PCIE_2_3_2_MAX_SUPPLY];
पूर्ण;

#घोषणा QCOM_PCIE_2_4_0_MAX_CLOCKS	4
काष्ठा qcom_pcie_resources_2_4_0 अणु
	काष्ठा clk_bulk_data clks[QCOM_PCIE_2_4_0_MAX_CLOCKS];
	पूर्णांक num_clks;
	काष्ठा reset_control *axi_m_reset;
	काष्ठा reset_control *axi_s_reset;
	काष्ठा reset_control *pipe_reset;
	काष्ठा reset_control *axi_m_vmid_reset;
	काष्ठा reset_control *axi_s_xpu_reset;
	काष्ठा reset_control *parf_reset;
	काष्ठा reset_control *phy_reset;
	काष्ठा reset_control *axi_m_sticky_reset;
	काष्ठा reset_control *pipe_sticky_reset;
	काष्ठा reset_control *pwr_reset;
	काष्ठा reset_control *ahb_reset;
	काष्ठा reset_control *phy_ahb_reset;
पूर्ण;

काष्ठा qcom_pcie_resources_2_3_3 अणु
	काष्ठा clk *अगरace;
	काष्ठा clk *axi_m_clk;
	काष्ठा clk *axi_s_clk;
	काष्ठा clk *ahb_clk;
	काष्ठा clk *aux_clk;
	काष्ठा reset_control *rst[7];
पूर्ण;

/* 6 घड़ीs typically, 7 क्रम sm8250 */
काष्ठा qcom_pcie_resources_2_7_0 अणु
	काष्ठा clk_bulk_data clks[7];
	पूर्णांक num_clks;
	काष्ठा regulator_bulk_data supplies[2];
	काष्ठा reset_control *pci_reset;
	काष्ठा clk *pipe_clk;
पूर्ण;

जोड़ qcom_pcie_resources अणु
	काष्ठा qcom_pcie_resources_1_0_0 v1_0_0;
	काष्ठा qcom_pcie_resources_2_1_0 v2_1_0;
	काष्ठा qcom_pcie_resources_2_3_2 v2_3_2;
	काष्ठा qcom_pcie_resources_2_3_3 v2_3_3;
	काष्ठा qcom_pcie_resources_2_4_0 v2_4_0;
	काष्ठा qcom_pcie_resources_2_7_0 v2_7_0;
पूर्ण;

काष्ठा qcom_pcie;

काष्ठा qcom_pcie_ops अणु
	पूर्णांक (*get_resources)(काष्ठा qcom_pcie *pcie);
	पूर्णांक (*init)(काष्ठा qcom_pcie *pcie);
	पूर्णांक (*post_init)(काष्ठा qcom_pcie *pcie);
	व्योम (*deinit)(काष्ठा qcom_pcie *pcie);
	व्योम (*post_deinit)(काष्ठा qcom_pcie *pcie);
	व्योम (*ltssm_enable)(काष्ठा qcom_pcie *pcie);
	पूर्णांक (*config_sid)(काष्ठा qcom_pcie *pcie);
पूर्ण;

काष्ठा qcom_pcie अणु
	काष्ठा dw_pcie *pci;
	व्योम __iomem *parf;			/* DT parf */
	व्योम __iomem *elbi;			/* DT elbi */
	जोड़ qcom_pcie_resources res;
	काष्ठा phy *phy;
	काष्ठा gpio_desc *reset;
	स्थिर काष्ठा qcom_pcie_ops *ops;
पूर्ण;

#घोषणा to_qcom_pcie(x)		dev_get_drvdata((x)->dev)

अटल व्योम qcom_ep_reset_निश्चित(काष्ठा qcom_pcie *pcie)
अणु
	gpiod_set_value_cansleep(pcie->reset, 1);
	usleep_range(PERST_DELAY_US, PERST_DELAY_US + 500);
पूर्ण

अटल व्योम qcom_ep_reset_deनिश्चित(काष्ठा qcom_pcie *pcie)
अणु
	/* Ensure that PERST has been निश्चितed क्रम at least 100 ms */
	msleep(100);
	gpiod_set_value_cansleep(pcie->reset, 0);
	usleep_range(PERST_DELAY_US, PERST_DELAY_US + 500);
पूर्ण

अटल पूर्णांक qcom_pcie_start_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा qcom_pcie *pcie = to_qcom_pcie(pci);

	/* Enable Link Training state machine */
	अगर (pcie->ops->ltssm_enable)
		pcie->ops->ltssm_enable(pcie);

	वापस 0;
पूर्ण

अटल व्योम qcom_pcie_2_1_0_ltssm_enable(काष्ठा qcom_pcie *pcie)
अणु
	u32 val;

	/* enable link training */
	val = पढ़ोl(pcie->elbi + PCIE20_ELBI_SYS_CTRL);
	val |= PCIE20_ELBI_SYS_CTRL_LT_ENABLE;
	ग_लिखोl(val, pcie->elbi + PCIE20_ELBI_SYS_CTRL);
पूर्ण

अटल पूर्णांक qcom_pcie_get_resources_2_1_0(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_1_0 *res = &pcie->res.v2_1_0;
	काष्ठा dw_pcie *pci = pcie->pci;
	काष्ठा device *dev = pci->dev;
	पूर्णांक ret;

	res->supplies[0].supply = "vdda";
	res->supplies[1].supply = "vdda_phy";
	res->supplies[2].supply = "vdda_refclk";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(res->supplies),
				      res->supplies);
	अगर (ret)
		वापस ret;

	res->clks[0].id = "iface";
	res->clks[1].id = "core";
	res->clks[2].id = "phy";
	res->clks[3].id = "aux";
	res->clks[4].id = "ref";

	/* अगरace, core, phy are required */
	ret = devm_clk_bulk_get(dev, 3, res->clks);
	अगर (ret < 0)
		वापस ret;

	/* aux, ref are optional */
	ret = devm_clk_bulk_get_optional(dev, 2, res->clks + 3);
	अगर (ret < 0)
		वापस ret;

	res->pci_reset = devm_reset_control_get_exclusive(dev, "pci");
	अगर (IS_ERR(res->pci_reset))
		वापस PTR_ERR(res->pci_reset);

	res->axi_reset = devm_reset_control_get_exclusive(dev, "axi");
	अगर (IS_ERR(res->axi_reset))
		वापस PTR_ERR(res->axi_reset);

	res->ahb_reset = devm_reset_control_get_exclusive(dev, "ahb");
	अगर (IS_ERR(res->ahb_reset))
		वापस PTR_ERR(res->ahb_reset);

	res->por_reset = devm_reset_control_get_exclusive(dev, "por");
	अगर (IS_ERR(res->por_reset))
		वापस PTR_ERR(res->por_reset);

	res->ext_reset = devm_reset_control_get_optional_exclusive(dev, "ext");
	अगर (IS_ERR(res->ext_reset))
		वापस PTR_ERR(res->ext_reset);

	res->phy_reset = devm_reset_control_get_exclusive(dev, "phy");
	वापस PTR_ERR_OR_ZERO(res->phy_reset);
पूर्ण

अटल व्योम qcom_pcie_deinit_2_1_0(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_1_0 *res = &pcie->res.v2_1_0;

	clk_bulk_disable_unprepare(ARRAY_SIZE(res->clks), res->clks);
	reset_control_निश्चित(res->pci_reset);
	reset_control_निश्चित(res->axi_reset);
	reset_control_निश्चित(res->ahb_reset);
	reset_control_निश्चित(res->por_reset);
	reset_control_निश्चित(res->ext_reset);
	reset_control_निश्चित(res->phy_reset);

	ग_लिखोl(1, pcie->parf + PCIE20_PARF_PHY_CTRL);

	regulator_bulk_disable(ARRAY_SIZE(res->supplies), res->supplies);
पूर्ण

अटल पूर्णांक qcom_pcie_init_2_1_0(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_1_0 *res = &pcie->res.v2_1_0;
	काष्ठा dw_pcie *pci = pcie->pci;
	काष्ठा device *dev = pci->dev;
	काष्ठा device_node *node = dev->of_node;
	u32 val;
	पूर्णांक ret;

	/* reset the PCIe पूर्णांकerface as uboot can leave it undefined state */
	reset_control_निश्चित(res->pci_reset);
	reset_control_निश्चित(res->axi_reset);
	reset_control_निश्चित(res->ahb_reset);
	reset_control_निश्चित(res->por_reset);
	reset_control_निश्चित(res->ext_reset);
	reset_control_निश्चित(res->phy_reset);

	ग_लिखोl(1, pcie->parf + PCIE20_PARF_PHY_CTRL);

	ret = regulator_bulk_enable(ARRAY_SIZE(res->supplies), res->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot enable regulators\n");
		वापस ret;
	पूर्ण

	ret = reset_control_deनिश्चित(res->ahb_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot deassert ahb reset\n");
		जाओ err_deनिश्चित_ahb;
	पूर्ण

	ret = reset_control_deनिश्चित(res->ext_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot deassert ext reset\n");
		जाओ err_deनिश्चित_ext;
	पूर्ण

	ret = reset_control_deनिश्चित(res->phy_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot deassert phy reset\n");
		जाओ err_deनिश्चित_phy;
	पूर्ण

	ret = reset_control_deनिश्चित(res->pci_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot deassert pci reset\n");
		जाओ err_deनिश्चित_pci;
	पूर्ण

	ret = reset_control_deनिश्चित(res->por_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot deassert por reset\n");
		जाओ err_deनिश्चित_por;
	पूर्ण

	ret = reset_control_deनिश्चित(res->axi_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot deassert axi reset\n");
		जाओ err_deनिश्चित_axi;
	पूर्ण

	ret = clk_bulk_prepare_enable(ARRAY_SIZE(res->clks), res->clks);
	अगर (ret)
		जाओ err_clks;

	/* enable PCIe घड़ीs and resets */
	val = पढ़ोl(pcie->parf + PCIE20_PARF_PHY_CTRL);
	val &= ~BIT(0);
	ग_लिखोl(val, pcie->parf + PCIE20_PARF_PHY_CTRL);

	अगर (of_device_is_compatible(node, "qcom,pcie-ipq8064") ||
	    of_device_is_compatible(node, "qcom,pcie-ipq8064-v2")) अणु
		ग_लिखोl(PCS_DEEMPH_TX_DEEMPH_GEN1(24) |
			       PCS_DEEMPH_TX_DEEMPH_GEN2_3_5DB(24) |
			       PCS_DEEMPH_TX_DEEMPH_GEN2_6DB(34),
		       pcie->parf + PCIE20_PARF_PCS_DEEMPH);
		ग_लिखोl(PCS_SWING_TX_SWING_FULL(120) |
			       PCS_SWING_TX_SWING_LOW(120),
		       pcie->parf + PCIE20_PARF_PCS_SWING);
		ग_लिखोl(PHY_RX0_EQ(4), pcie->parf + PCIE20_PARF_CONFIG_BITS);
	पूर्ण

	अगर (of_device_is_compatible(node, "qcom,pcie-ipq8064")) अणु
		/* set TX termination offset */
		val = पढ़ोl(pcie->parf + PCIE20_PARF_PHY_CTRL);
		val &= ~PHY_CTRL_PHY_TX0_TERM_OFFSET_MASK;
		val |= PHY_CTRL_PHY_TX0_TERM_OFFSET(7);
		ग_लिखोl(val, pcie->parf + PCIE20_PARF_PHY_CTRL);
	पूर्ण

	/* enable बाह्यal reference घड़ी */
	val = पढ़ोl(pcie->parf + PCIE20_PARF_PHY_REFCLK);
	/* USE_PAD is required only क्रम ipq806x */
	अगर (!of_device_is_compatible(node, "qcom,pcie-apq8064"))
		val &= ~PHY_REFCLK_USE_PAD;
	val |= PHY_REFCLK_SSP_EN;
	ग_लिखोl(val, pcie->parf + PCIE20_PARF_PHY_REFCLK);

	/* रुको क्रम घड़ी acquisition */
	usleep_range(1000, 1500);

	/* Set the Max TLP size to 2K, instead of using शेष of 4K */
	ग_लिखोl(CFG_REMOTE_RD_REQ_BRIDGE_SIZE_2K,
	       pci->dbi_base + PCIE20_AXI_MSTR_RESP_COMP_CTRL0);
	ग_लिखोl(CFG_BRIDGE_SB_INIT,
	       pci->dbi_base + PCIE20_AXI_MSTR_RESP_COMP_CTRL1);

	वापस 0;

err_clks:
	reset_control_निश्चित(res->axi_reset);
err_deनिश्चित_axi:
	reset_control_निश्चित(res->por_reset);
err_deनिश्चित_por:
	reset_control_निश्चित(res->pci_reset);
err_deनिश्चित_pci:
	reset_control_निश्चित(res->phy_reset);
err_deनिश्चित_phy:
	reset_control_निश्चित(res->ext_reset);
err_deनिश्चित_ext:
	reset_control_निश्चित(res->ahb_reset);
err_deनिश्चित_ahb:
	regulator_bulk_disable(ARRAY_SIZE(res->supplies), res->supplies);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_pcie_get_resources_1_0_0(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_1_0_0 *res = &pcie->res.v1_0_0;
	काष्ठा dw_pcie *pci = pcie->pci;
	काष्ठा device *dev = pci->dev;

	res->vdda = devm_regulator_get(dev, "vdda");
	अगर (IS_ERR(res->vdda))
		वापस PTR_ERR(res->vdda);

	res->अगरace = devm_clk_get(dev, "iface");
	अगर (IS_ERR(res->अगरace))
		वापस PTR_ERR(res->अगरace);

	res->aux = devm_clk_get(dev, "aux");
	अगर (IS_ERR(res->aux))
		वापस PTR_ERR(res->aux);

	res->master_bus = devm_clk_get(dev, "master_bus");
	अगर (IS_ERR(res->master_bus))
		वापस PTR_ERR(res->master_bus);

	res->slave_bus = devm_clk_get(dev, "slave_bus");
	अगर (IS_ERR(res->slave_bus))
		वापस PTR_ERR(res->slave_bus);

	res->core = devm_reset_control_get_exclusive(dev, "core");
	वापस PTR_ERR_OR_ZERO(res->core);
पूर्ण

अटल व्योम qcom_pcie_deinit_1_0_0(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_1_0_0 *res = &pcie->res.v1_0_0;

	reset_control_निश्चित(res->core);
	clk_disable_unprepare(res->slave_bus);
	clk_disable_unprepare(res->master_bus);
	clk_disable_unprepare(res->अगरace);
	clk_disable_unprepare(res->aux);
	regulator_disable(res->vdda);
पूर्ण

अटल पूर्णांक qcom_pcie_init_1_0_0(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_1_0_0 *res = &pcie->res.v1_0_0;
	काष्ठा dw_pcie *pci = pcie->pci;
	काष्ठा device *dev = pci->dev;
	पूर्णांक ret;

	ret = reset_control_deनिश्चित(res->core);
	अगर (ret) अणु
		dev_err(dev, "cannot deassert core reset\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(res->aux);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable aux clock\n");
		जाओ err_res;
	पूर्ण

	ret = clk_prepare_enable(res->अगरace);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable iface clock\n");
		जाओ err_aux;
	पूर्ण

	ret = clk_prepare_enable(res->master_bus);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable master_bus clock\n");
		जाओ err_अगरace;
	पूर्ण

	ret = clk_prepare_enable(res->slave_bus);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable slave_bus clock\n");
		जाओ err_master;
	पूर्ण

	ret = regulator_enable(res->vdda);
	अगर (ret) अणु
		dev_err(dev, "cannot enable vdda regulator\n");
		जाओ err_slave;
	पूर्ण

	/* change DBI base address */
	ग_लिखोl(0, pcie->parf + PCIE20_PARF_DBI_BASE_ADDR);

	अगर (IS_ENABLED(CONFIG_PCI_MSI)) अणु
		u32 val = पढ़ोl(pcie->parf + PCIE20_PARF_AXI_MSTR_WR_ADDR_HALT);

		val |= BIT(31);
		ग_लिखोl(val, pcie->parf + PCIE20_PARF_AXI_MSTR_WR_ADDR_HALT);
	पूर्ण

	वापस 0;
err_slave:
	clk_disable_unprepare(res->slave_bus);
err_master:
	clk_disable_unprepare(res->master_bus);
err_अगरace:
	clk_disable_unprepare(res->अगरace);
err_aux:
	clk_disable_unprepare(res->aux);
err_res:
	reset_control_निश्चित(res->core);

	वापस ret;
पूर्ण

अटल व्योम qcom_pcie_2_3_2_ltssm_enable(काष्ठा qcom_pcie *pcie)
अणु
	u32 val;

	/* enable link training */
	val = पढ़ोl(pcie->parf + PCIE20_PARF_LTSSM);
	val |= BIT(8);
	ग_लिखोl(val, pcie->parf + PCIE20_PARF_LTSSM);
पूर्ण

अटल पूर्णांक qcom_pcie_get_resources_2_3_2(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_3_2 *res = &pcie->res.v2_3_2;
	काष्ठा dw_pcie *pci = pcie->pci;
	काष्ठा device *dev = pci->dev;
	पूर्णांक ret;

	res->supplies[0].supply = "vdda";
	res->supplies[1].supply = "vddpe-3v3";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(res->supplies),
				      res->supplies);
	अगर (ret)
		वापस ret;

	res->aux_clk = devm_clk_get(dev, "aux");
	अगर (IS_ERR(res->aux_clk))
		वापस PTR_ERR(res->aux_clk);

	res->cfg_clk = devm_clk_get(dev, "cfg");
	अगर (IS_ERR(res->cfg_clk))
		वापस PTR_ERR(res->cfg_clk);

	res->master_clk = devm_clk_get(dev, "bus_master");
	अगर (IS_ERR(res->master_clk))
		वापस PTR_ERR(res->master_clk);

	res->slave_clk = devm_clk_get(dev, "bus_slave");
	अगर (IS_ERR(res->slave_clk))
		वापस PTR_ERR(res->slave_clk);

	res->pipe_clk = devm_clk_get(dev, "pipe");
	वापस PTR_ERR_OR_ZERO(res->pipe_clk);
पूर्ण

अटल व्योम qcom_pcie_deinit_2_3_2(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_3_2 *res = &pcie->res.v2_3_2;

	clk_disable_unprepare(res->slave_clk);
	clk_disable_unprepare(res->master_clk);
	clk_disable_unprepare(res->cfg_clk);
	clk_disable_unprepare(res->aux_clk);

	regulator_bulk_disable(ARRAY_SIZE(res->supplies), res->supplies);
पूर्ण

अटल व्योम qcom_pcie_post_deinit_2_3_2(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_3_2 *res = &pcie->res.v2_3_2;

	clk_disable_unprepare(res->pipe_clk);
पूर्ण

अटल पूर्णांक qcom_pcie_init_2_3_2(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_3_2 *res = &pcie->res.v2_3_2;
	काष्ठा dw_pcie *pci = pcie->pci;
	काष्ठा device *dev = pci->dev;
	u32 val;
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(res->supplies), res->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot enable regulators\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(res->aux_clk);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable aux clock\n");
		जाओ err_aux_clk;
	पूर्ण

	ret = clk_prepare_enable(res->cfg_clk);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable cfg clock\n");
		जाओ err_cfg_clk;
	पूर्ण

	ret = clk_prepare_enable(res->master_clk);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable master clock\n");
		जाओ err_master_clk;
	पूर्ण

	ret = clk_prepare_enable(res->slave_clk);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable slave clock\n");
		जाओ err_slave_clk;
	पूर्ण

	/* enable PCIe घड़ीs and resets */
	val = पढ़ोl(pcie->parf + PCIE20_PARF_PHY_CTRL);
	val &= ~BIT(0);
	ग_लिखोl(val, pcie->parf + PCIE20_PARF_PHY_CTRL);

	/* change DBI base address */
	ग_लिखोl(0, pcie->parf + PCIE20_PARF_DBI_BASE_ADDR);

	/* MAC PHY_POWERDOWN MUX DISABLE  */
	val = पढ़ोl(pcie->parf + PCIE20_PARF_SYS_CTRL);
	val &= ~BIT(29);
	ग_लिखोl(val, pcie->parf + PCIE20_PARF_SYS_CTRL);

	val = पढ़ोl(pcie->parf + PCIE20_PARF_MHI_CLOCK_RESET_CTRL);
	val |= BIT(4);
	ग_लिखोl(val, pcie->parf + PCIE20_PARF_MHI_CLOCK_RESET_CTRL);

	val = पढ़ोl(pcie->parf + PCIE20_PARF_AXI_MSTR_WR_ADDR_HALT_V2);
	val |= BIT(31);
	ग_लिखोl(val, pcie->parf + PCIE20_PARF_AXI_MSTR_WR_ADDR_HALT_V2);

	वापस 0;

err_slave_clk:
	clk_disable_unprepare(res->master_clk);
err_master_clk:
	clk_disable_unprepare(res->cfg_clk);
err_cfg_clk:
	clk_disable_unprepare(res->aux_clk);

err_aux_clk:
	regulator_bulk_disable(ARRAY_SIZE(res->supplies), res->supplies);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_pcie_post_init_2_3_2(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_3_2 *res = &pcie->res.v2_3_2;
	काष्ठा dw_pcie *pci = pcie->pci;
	काष्ठा device *dev = pci->dev;
	पूर्णांक ret;

	ret = clk_prepare_enable(res->pipe_clk);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable pipe clock\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_pcie_get_resources_2_4_0(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_4_0 *res = &pcie->res.v2_4_0;
	काष्ठा dw_pcie *pci = pcie->pci;
	काष्ठा device *dev = pci->dev;
	bool is_ipq = of_device_is_compatible(dev->of_node, "qcom,pcie-ipq4019");
	पूर्णांक ret;

	res->clks[0].id = "aux";
	res->clks[1].id = "master_bus";
	res->clks[2].id = "slave_bus";
	res->clks[3].id = "iface";

	/* qcom,pcie-ipq4019 is defined without "iface" */
	res->num_clks = is_ipq ? 3 : 4;

	ret = devm_clk_bulk_get(dev, res->num_clks, res->clks);
	अगर (ret < 0)
		वापस ret;

	res->axi_m_reset = devm_reset_control_get_exclusive(dev, "axi_m");
	अगर (IS_ERR(res->axi_m_reset))
		वापस PTR_ERR(res->axi_m_reset);

	res->axi_s_reset = devm_reset_control_get_exclusive(dev, "axi_s");
	अगर (IS_ERR(res->axi_s_reset))
		वापस PTR_ERR(res->axi_s_reset);

	अगर (is_ipq) अणु
		/*
		 * These resources relates to the PHY or are secure घड़ीs, but
		 * are controlled here क्रम IPQ4019
		 */
		res->pipe_reset = devm_reset_control_get_exclusive(dev, "pipe");
		अगर (IS_ERR(res->pipe_reset))
			वापस PTR_ERR(res->pipe_reset);

		res->axi_m_vmid_reset = devm_reset_control_get_exclusive(dev,
									 "axi_m_vmid");
		अगर (IS_ERR(res->axi_m_vmid_reset))
			वापस PTR_ERR(res->axi_m_vmid_reset);

		res->axi_s_xpu_reset = devm_reset_control_get_exclusive(dev,
									"axi_s_xpu");
		अगर (IS_ERR(res->axi_s_xpu_reset))
			वापस PTR_ERR(res->axi_s_xpu_reset);

		res->parf_reset = devm_reset_control_get_exclusive(dev, "parf");
		अगर (IS_ERR(res->parf_reset))
			वापस PTR_ERR(res->parf_reset);

		res->phy_reset = devm_reset_control_get_exclusive(dev, "phy");
		अगर (IS_ERR(res->phy_reset))
			वापस PTR_ERR(res->phy_reset);
	पूर्ण

	res->axi_m_sticky_reset = devm_reset_control_get_exclusive(dev,
								   "axi_m_sticky");
	अगर (IS_ERR(res->axi_m_sticky_reset))
		वापस PTR_ERR(res->axi_m_sticky_reset);

	res->pipe_sticky_reset = devm_reset_control_get_exclusive(dev,
								  "pipe_sticky");
	अगर (IS_ERR(res->pipe_sticky_reset))
		वापस PTR_ERR(res->pipe_sticky_reset);

	res->pwr_reset = devm_reset_control_get_exclusive(dev, "pwr");
	अगर (IS_ERR(res->pwr_reset))
		वापस PTR_ERR(res->pwr_reset);

	res->ahb_reset = devm_reset_control_get_exclusive(dev, "ahb");
	अगर (IS_ERR(res->ahb_reset))
		वापस PTR_ERR(res->ahb_reset);

	अगर (is_ipq) अणु
		res->phy_ahb_reset = devm_reset_control_get_exclusive(dev, "phy_ahb");
		अगर (IS_ERR(res->phy_ahb_reset))
			वापस PTR_ERR(res->phy_ahb_reset);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qcom_pcie_deinit_2_4_0(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_4_0 *res = &pcie->res.v2_4_0;

	reset_control_निश्चित(res->axi_m_reset);
	reset_control_निश्चित(res->axi_s_reset);
	reset_control_निश्चित(res->pipe_reset);
	reset_control_निश्चित(res->pipe_sticky_reset);
	reset_control_निश्चित(res->phy_reset);
	reset_control_निश्चित(res->phy_ahb_reset);
	reset_control_निश्चित(res->axi_m_sticky_reset);
	reset_control_निश्चित(res->pwr_reset);
	reset_control_निश्चित(res->ahb_reset);
	clk_bulk_disable_unprepare(res->num_clks, res->clks);
पूर्ण

अटल पूर्णांक qcom_pcie_init_2_4_0(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_4_0 *res = &pcie->res.v2_4_0;
	काष्ठा dw_pcie *pci = pcie->pci;
	काष्ठा device *dev = pci->dev;
	u32 val;
	पूर्णांक ret;

	ret = reset_control_निश्चित(res->axi_m_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot assert axi master reset\n");
		वापस ret;
	पूर्ण

	ret = reset_control_निश्चित(res->axi_s_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot assert axi slave reset\n");
		वापस ret;
	पूर्ण

	usleep_range(10000, 12000);

	ret = reset_control_निश्चित(res->pipe_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot assert pipe reset\n");
		वापस ret;
	पूर्ण

	ret = reset_control_निश्चित(res->pipe_sticky_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot assert pipe sticky reset\n");
		वापस ret;
	पूर्ण

	ret = reset_control_निश्चित(res->phy_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot assert phy reset\n");
		वापस ret;
	पूर्ण

	ret = reset_control_निश्चित(res->phy_ahb_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot assert phy ahb reset\n");
		वापस ret;
	पूर्ण

	usleep_range(10000, 12000);

	ret = reset_control_निश्चित(res->axi_m_sticky_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot assert axi master sticky reset\n");
		वापस ret;
	पूर्ण

	ret = reset_control_निश्चित(res->pwr_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot assert power reset\n");
		वापस ret;
	पूर्ण

	ret = reset_control_निश्चित(res->ahb_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot assert ahb reset\n");
		वापस ret;
	पूर्ण

	usleep_range(10000, 12000);

	ret = reset_control_deनिश्चित(res->phy_ahb_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot deassert phy ahb reset\n");
		वापस ret;
	पूर्ण

	ret = reset_control_deनिश्चित(res->phy_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot deassert phy reset\n");
		जाओ err_rst_phy;
	पूर्ण

	ret = reset_control_deनिश्चित(res->pipe_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot deassert pipe reset\n");
		जाओ err_rst_pipe;
	पूर्ण

	ret = reset_control_deनिश्चित(res->pipe_sticky_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot deassert pipe sticky reset\n");
		जाओ err_rst_pipe_sticky;
	पूर्ण

	usleep_range(10000, 12000);

	ret = reset_control_deनिश्चित(res->axi_m_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot deassert axi master reset\n");
		जाओ err_rst_axi_m;
	पूर्ण

	ret = reset_control_deनिश्चित(res->axi_m_sticky_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot deassert axi master sticky reset\n");
		जाओ err_rst_axi_m_sticky;
	पूर्ण

	ret = reset_control_deनिश्चित(res->axi_s_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot deassert axi slave reset\n");
		जाओ err_rst_axi_s;
	पूर्ण

	ret = reset_control_deनिश्चित(res->pwr_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot deassert power reset\n");
		जाओ err_rst_pwr;
	पूर्ण

	ret = reset_control_deनिश्चित(res->ahb_reset);
	अगर (ret) अणु
		dev_err(dev, "cannot deassert ahb reset\n");
		जाओ err_rst_ahb;
	पूर्ण

	usleep_range(10000, 12000);

	ret = clk_bulk_prepare_enable(res->num_clks, res->clks);
	अगर (ret)
		जाओ err_clks;

	/* enable PCIe घड़ीs and resets */
	val = पढ़ोl(pcie->parf + PCIE20_PARF_PHY_CTRL);
	val &= ~BIT(0);
	ग_लिखोl(val, pcie->parf + PCIE20_PARF_PHY_CTRL);

	/* change DBI base address */
	ग_लिखोl(0, pcie->parf + PCIE20_PARF_DBI_BASE_ADDR);

	/* MAC PHY_POWERDOWN MUX DISABLE  */
	val = पढ़ोl(pcie->parf + PCIE20_PARF_SYS_CTRL);
	val &= ~BIT(29);
	ग_लिखोl(val, pcie->parf + PCIE20_PARF_SYS_CTRL);

	val = पढ़ोl(pcie->parf + PCIE20_PARF_MHI_CLOCK_RESET_CTRL);
	val |= BIT(4);
	ग_लिखोl(val, pcie->parf + PCIE20_PARF_MHI_CLOCK_RESET_CTRL);

	val = पढ़ोl(pcie->parf + PCIE20_PARF_AXI_MSTR_WR_ADDR_HALT_V2);
	val |= BIT(31);
	ग_लिखोl(val, pcie->parf + PCIE20_PARF_AXI_MSTR_WR_ADDR_HALT_V2);

	वापस 0;

err_clks:
	reset_control_निश्चित(res->ahb_reset);
err_rst_ahb:
	reset_control_निश्चित(res->pwr_reset);
err_rst_pwr:
	reset_control_निश्चित(res->axi_s_reset);
err_rst_axi_s:
	reset_control_निश्चित(res->axi_m_sticky_reset);
err_rst_axi_m_sticky:
	reset_control_निश्चित(res->axi_m_reset);
err_rst_axi_m:
	reset_control_निश्चित(res->pipe_sticky_reset);
err_rst_pipe_sticky:
	reset_control_निश्चित(res->pipe_reset);
err_rst_pipe:
	reset_control_निश्चित(res->phy_reset);
err_rst_phy:
	reset_control_निश्चित(res->phy_ahb_reset);
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_pcie_get_resources_2_3_3(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_3_3 *res = &pcie->res.v2_3_3;
	काष्ठा dw_pcie *pci = pcie->pci;
	काष्ठा device *dev = pci->dev;
	पूर्णांक i;
	स्थिर अक्षर *rst_names[] = अणु "axi_m", "axi_s", "pipe",
				    "axi_m_sticky", "sticky",
				    "ahb", "sleep", पूर्ण;

	res->अगरace = devm_clk_get(dev, "iface");
	अगर (IS_ERR(res->अगरace))
		वापस PTR_ERR(res->अगरace);

	res->axi_m_clk = devm_clk_get(dev, "axi_m");
	अगर (IS_ERR(res->axi_m_clk))
		वापस PTR_ERR(res->axi_m_clk);

	res->axi_s_clk = devm_clk_get(dev, "axi_s");
	अगर (IS_ERR(res->axi_s_clk))
		वापस PTR_ERR(res->axi_s_clk);

	res->ahb_clk = devm_clk_get(dev, "ahb");
	अगर (IS_ERR(res->ahb_clk))
		वापस PTR_ERR(res->ahb_clk);

	res->aux_clk = devm_clk_get(dev, "aux");
	अगर (IS_ERR(res->aux_clk))
		वापस PTR_ERR(res->aux_clk);

	क्रम (i = 0; i < ARRAY_SIZE(rst_names); i++) अणु
		res->rst[i] = devm_reset_control_get(dev, rst_names[i]);
		अगर (IS_ERR(res->rst[i]))
			वापस PTR_ERR(res->rst[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qcom_pcie_deinit_2_3_3(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_3_3 *res = &pcie->res.v2_3_3;

	clk_disable_unprepare(res->अगरace);
	clk_disable_unprepare(res->axi_m_clk);
	clk_disable_unprepare(res->axi_s_clk);
	clk_disable_unprepare(res->ahb_clk);
	clk_disable_unprepare(res->aux_clk);
पूर्ण

अटल पूर्णांक qcom_pcie_init_2_3_3(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_3_3 *res = &pcie->res.v2_3_3;
	काष्ठा dw_pcie *pci = pcie->pci;
	काष्ठा device *dev = pci->dev;
	u16 offset = dw_pcie_find_capability(pci, PCI_CAP_ID_EXP);
	पूर्णांक i, ret;
	u32 val;

	क्रम (i = 0; i < ARRAY_SIZE(res->rst); i++) अणु
		ret = reset_control_निश्चित(res->rst[i]);
		अगर (ret) अणु
			dev_err(dev, "reset #%d assert failed (%d)\n", i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	usleep_range(2000, 2500);

	क्रम (i = 0; i < ARRAY_SIZE(res->rst); i++) अणु
		ret = reset_control_deनिश्चित(res->rst[i]);
		अगर (ret) अणु
			dev_err(dev, "reset #%d deassert failed (%d)\n", i,
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Don't have a way to see अगर the reset has completed.
	 * Wait क्रम some समय.
	 */
	usleep_range(2000, 2500);

	ret = clk_prepare_enable(res->अगरace);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable core clock\n");
		जाओ err_clk_अगरace;
	पूर्ण

	ret = clk_prepare_enable(res->axi_m_clk);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable core clock\n");
		जाओ err_clk_axi_m;
	पूर्ण

	ret = clk_prepare_enable(res->axi_s_clk);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable axi slave clock\n");
		जाओ err_clk_axi_s;
	पूर्ण

	ret = clk_prepare_enable(res->ahb_clk);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable ahb clock\n");
		जाओ err_clk_ahb;
	पूर्ण

	ret = clk_prepare_enable(res->aux_clk);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable aux clock\n");
		जाओ err_clk_aux;
	पूर्ण

	ग_लिखोl(SLV_ADDR_SPACE_SZ,
		pcie->parf + PCIE20_v3_PARF_SLV_ADDR_SPACE_SIZE);

	val = पढ़ोl(pcie->parf + PCIE20_PARF_PHY_CTRL);
	val &= ~BIT(0);
	ग_लिखोl(val, pcie->parf + PCIE20_PARF_PHY_CTRL);

	ग_लिखोl(0, pcie->parf + PCIE20_PARF_DBI_BASE_ADDR);

	ग_लिखोl(MST_WAKEUP_EN | SLV_WAKEUP_EN | MSTR_ACLK_CGC_DIS
		| SLV_ACLK_CGC_DIS | CORE_CLK_CGC_DIS |
		AUX_PWR_DET | L23_CLK_RMV_DIS | L1_CLK_RMV_DIS,
		pcie->parf + PCIE20_PARF_SYS_CTRL);
	ग_लिखोl(0, pcie->parf + PCIE20_PARF_Q2A_FLUSH);

	ग_लिखोl(PCI_COMMAND_MASTER, pci->dbi_base + PCI_COMMAND);
	ग_लिखोl(DBI_RO_WR_EN, pci->dbi_base + PCIE20_MISC_CONTROL_1_REG);
	ग_लिखोl(PCIE_CAP_LINK1_VAL, pci->dbi_base + offset + PCI_EXP_SLTCAP);

	val = पढ़ोl(pci->dbi_base + offset + PCI_EXP_LNKCAP);
	val &= ~PCI_EXP_LNKCAP_ASPMS;
	ग_लिखोl(val, pci->dbi_base + offset + PCI_EXP_LNKCAP);

	ग_लिखोl(PCI_EXP_DEVCTL2_COMP_TMOUT_DIS, pci->dbi_base + offset +
		PCI_EXP_DEVCTL2);

	वापस 0;

err_clk_aux:
	clk_disable_unprepare(res->ahb_clk);
err_clk_ahb:
	clk_disable_unprepare(res->axi_s_clk);
err_clk_axi_s:
	clk_disable_unprepare(res->axi_m_clk);
err_clk_axi_m:
	clk_disable_unprepare(res->अगरace);
err_clk_अगरace:
	/*
	 * Not checking क्रम failure, will anyway वापस
	 * the original failure in 'ret'.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(res->rst); i++)
		reset_control_निश्चित(res->rst[i]);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_pcie_get_resources_2_7_0(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_7_0 *res = &pcie->res.v2_7_0;
	काष्ठा dw_pcie *pci = pcie->pci;
	काष्ठा device *dev = pci->dev;
	पूर्णांक ret;

	res->pci_reset = devm_reset_control_get_exclusive(dev, "pci");
	अगर (IS_ERR(res->pci_reset))
		वापस PTR_ERR(res->pci_reset);

	res->supplies[0].supply = "vdda";
	res->supplies[1].supply = "vddpe-3v3";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(res->supplies),
				      res->supplies);
	अगर (ret)
		वापस ret;

	res->clks[0].id = "aux";
	res->clks[1].id = "cfg";
	res->clks[2].id = "bus_master";
	res->clks[3].id = "bus_slave";
	res->clks[4].id = "slave_q2a";
	res->clks[5].id = "tbu";
	अगर (of_device_is_compatible(dev->of_node, "qcom,pcie-sm8250")) अणु
		res->clks[6].id = "ddrss_sf_tbu";
		res->num_clks = 7;
	पूर्ण अन्यथा अणु
		res->num_clks = 6;
	पूर्ण

	ret = devm_clk_bulk_get(dev, res->num_clks, res->clks);
	अगर (ret < 0)
		वापस ret;

	res->pipe_clk = devm_clk_get(dev, "pipe");
	वापस PTR_ERR_OR_ZERO(res->pipe_clk);
पूर्ण

अटल पूर्णांक qcom_pcie_init_2_7_0(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_7_0 *res = &pcie->res.v2_7_0;
	काष्ठा dw_pcie *pci = pcie->pci;
	काष्ठा device *dev = pci->dev;
	u32 val;
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(res->supplies), res->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot enable regulators\n");
		वापस ret;
	पूर्ण

	ret = clk_bulk_prepare_enable(res->num_clks, res->clks);
	अगर (ret < 0)
		जाओ err_disable_regulators;

	ret = reset_control_निश्चित(res->pci_reset);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot deassert pci reset\n");
		जाओ err_disable_घड़ीs;
	पूर्ण

	usleep_range(1000, 1500);

	ret = reset_control_deनिश्चित(res->pci_reset);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot deassert pci reset\n");
		जाओ err_disable_घड़ीs;
	पूर्ण

	ret = clk_prepare_enable(res->pipe_clk);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable pipe clock\n");
		जाओ err_disable_घड़ीs;
	पूर्ण

	/* configure PCIe to RC mode */
	ग_लिखोl(DEVICE_TYPE_RC, pcie->parf + PCIE20_PARF_DEVICE_TYPE);

	/* enable PCIe घड़ीs and resets */
	val = पढ़ोl(pcie->parf + PCIE20_PARF_PHY_CTRL);
	val &= ~BIT(0);
	ग_लिखोl(val, pcie->parf + PCIE20_PARF_PHY_CTRL);

	/* change DBI base address */
	ग_लिखोl(0, pcie->parf + PCIE20_PARF_DBI_BASE_ADDR);

	/* MAC PHY_POWERDOWN MUX DISABLE  */
	val = पढ़ोl(pcie->parf + PCIE20_PARF_SYS_CTRL);
	val &= ~BIT(29);
	ग_लिखोl(val, pcie->parf + PCIE20_PARF_SYS_CTRL);

	val = पढ़ोl(pcie->parf + PCIE20_PARF_MHI_CLOCK_RESET_CTRL);
	val |= BIT(4);
	ग_लिखोl(val, pcie->parf + PCIE20_PARF_MHI_CLOCK_RESET_CTRL);

	अगर (IS_ENABLED(CONFIG_PCI_MSI)) अणु
		val = पढ़ोl(pcie->parf + PCIE20_PARF_AXI_MSTR_WR_ADDR_HALT);
		val |= BIT(31);
		ग_लिखोl(val, pcie->parf + PCIE20_PARF_AXI_MSTR_WR_ADDR_HALT);
	पूर्ण

	वापस 0;
err_disable_घड़ीs:
	clk_bulk_disable_unprepare(res->num_clks, res->clks);
err_disable_regulators:
	regulator_bulk_disable(ARRAY_SIZE(res->supplies), res->supplies);

	वापस ret;
पूर्ण

अटल व्योम qcom_pcie_deinit_2_7_0(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_7_0 *res = &pcie->res.v2_7_0;

	clk_bulk_disable_unprepare(res->num_clks, res->clks);
	regulator_bulk_disable(ARRAY_SIZE(res->supplies), res->supplies);
पूर्ण

अटल पूर्णांक qcom_pcie_post_init_2_7_0(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_7_0 *res = &pcie->res.v2_7_0;

	वापस clk_prepare_enable(res->pipe_clk);
पूर्ण

अटल व्योम qcom_pcie_post_deinit_2_7_0(काष्ठा qcom_pcie *pcie)
अणु
	काष्ठा qcom_pcie_resources_2_7_0 *res = &pcie->res.v2_7_0;

	clk_disable_unprepare(res->pipe_clk);
पूर्ण

अटल पूर्णांक qcom_pcie_link_up(काष्ठा dw_pcie *pci)
अणु
	u16 offset = dw_pcie_find_capability(pci, PCI_CAP_ID_EXP);
	u16 val = पढ़ोw(pci->dbi_base + offset + PCI_EXP_LNKSTA);

	वापस !!(val & PCI_EXP_LNKSTA_DLLLA);
पूर्ण

अटल पूर्णांक qcom_pcie_config_sid_sm8250(काष्ठा qcom_pcie *pcie)
अणु
	/* iommu map काष्ठाure */
	काष्ठा अणु
		u32 bdf;
		u32 phandle;
		u32 smmu_sid;
		u32 smmu_sid_len;
	पूर्ण *map;
	व्योम __iomem *bdf_to_sid_base = pcie->parf + PCIE20_PARF_BDF_TO_SID_TABLE_N;
	काष्ठा device *dev = pcie->pci->dev;
	u8 qcom_pcie_crc8_table[CRC8_TABLE_SIZE];
	पूर्णांक i, nr_map, size = 0;
	u32 smmu_sid_base;

	of_get_property(dev->of_node, "iommu-map", &size);
	अगर (!size)
		वापस 0;

	map = kzalloc(size, GFP_KERNEL);
	अगर (!map)
		वापस -ENOMEM;

	of_property_पढ़ो_u32_array(dev->of_node,
		"iommu-map", (u32 *)map, size / माप(u32));

	nr_map = size / (माप(*map));

	crc8_populate_msb(qcom_pcie_crc8_table, QCOM_PCIE_CRC8_POLYNOMIAL);

	/* Registers need to be zero out first */
	स_रखो_io(bdf_to_sid_base, 0, CRC8_TABLE_SIZE * माप(u32));

	/* Extract the SMMU SID base from the first entry of iommu-map */
	smmu_sid_base = map[0].smmu_sid;

	/* Look क्रम an available entry to hold the mapping */
	क्रम (i = 0; i < nr_map; i++) अणु
		u16 bdf_be = cpu_to_be16(map[i].bdf);
		u32 val;
		u8 hash;

		hash = crc8(qcom_pcie_crc8_table, (u8 *)&bdf_be, माप(bdf_be),
			0);

		val = पढ़ोl(bdf_to_sid_base + hash * माप(u32));

		/* If the रेजिस्टर is alपढ़ोy populated, look क्रम next available entry */
		जबतक (val) अणु
			u8 current_hash = hash++;
			u8 next_mask = 0xff;

			/* If NEXT field is शून्य then update it with next hash */
			अगर (!(val & next_mask)) अणु
				val |= (u32)hash;
				ग_लिखोl(val, bdf_to_sid_base + current_hash * माप(u32));
			पूर्ण

			val = पढ़ोl(bdf_to_sid_base + hash * माप(u32));
		पूर्ण

		/* BDF [31:16] | SID [15:8] | NEXT [7:0] */
		val = map[i].bdf << 16 | (map[i].smmu_sid - smmu_sid_base) << 8 | 0;
		ग_लिखोl(val, bdf_to_sid_base + hash * माप(u32));
	पूर्ण

	kमुक्त(map);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा qcom_pcie *pcie = to_qcom_pcie(pci);
	पूर्णांक ret;

	qcom_ep_reset_निश्चित(pcie);

	ret = pcie->ops->init(pcie);
	अगर (ret)
		वापस ret;

	ret = phy_घातer_on(pcie->phy);
	अगर (ret)
		जाओ err_deinit;

	अगर (pcie->ops->post_init) अणु
		ret = pcie->ops->post_init(pcie);
		अगर (ret)
			जाओ err_disable_phy;
	पूर्ण

	qcom_ep_reset_deनिश्चित(pcie);

	अगर (pcie->ops->config_sid) अणु
		ret = pcie->ops->config_sid(pcie);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	qcom_ep_reset_निश्चित(pcie);
	अगर (pcie->ops->post_deinit)
		pcie->ops->post_deinit(pcie);
err_disable_phy:
	phy_घातer_off(pcie->phy);
err_deinit:
	pcie->ops->deinit(pcie);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_host_ops qcom_pcie_dw_ops = अणु
	.host_init = qcom_pcie_host_init,
पूर्ण;

/* Qcom IP rev.: 2.1.0	Synopsys IP rev.: 4.01a */
अटल स्थिर काष्ठा qcom_pcie_ops ops_2_1_0 = अणु
	.get_resources = qcom_pcie_get_resources_2_1_0,
	.init = qcom_pcie_init_2_1_0,
	.deinit = qcom_pcie_deinit_2_1_0,
	.ltssm_enable = qcom_pcie_2_1_0_ltssm_enable,
पूर्ण;

/* Qcom IP rev.: 1.0.0	Synopsys IP rev.: 4.11a */
अटल स्थिर काष्ठा qcom_pcie_ops ops_1_0_0 = अणु
	.get_resources = qcom_pcie_get_resources_1_0_0,
	.init = qcom_pcie_init_1_0_0,
	.deinit = qcom_pcie_deinit_1_0_0,
	.ltssm_enable = qcom_pcie_2_1_0_ltssm_enable,
पूर्ण;

/* Qcom IP rev.: 2.3.2	Synopsys IP rev.: 4.21a */
अटल स्थिर काष्ठा qcom_pcie_ops ops_2_3_2 = अणु
	.get_resources = qcom_pcie_get_resources_2_3_2,
	.init = qcom_pcie_init_2_3_2,
	.post_init = qcom_pcie_post_init_2_3_2,
	.deinit = qcom_pcie_deinit_2_3_2,
	.post_deinit = qcom_pcie_post_deinit_2_3_2,
	.ltssm_enable = qcom_pcie_2_3_2_ltssm_enable,
पूर्ण;

/* Qcom IP rev.: 2.4.0	Synopsys IP rev.: 4.20a */
अटल स्थिर काष्ठा qcom_pcie_ops ops_2_4_0 = अणु
	.get_resources = qcom_pcie_get_resources_2_4_0,
	.init = qcom_pcie_init_2_4_0,
	.deinit = qcom_pcie_deinit_2_4_0,
	.ltssm_enable = qcom_pcie_2_3_2_ltssm_enable,
पूर्ण;

/* Qcom IP rev.: 2.3.3	Synopsys IP rev.: 4.30a */
अटल स्थिर काष्ठा qcom_pcie_ops ops_2_3_3 = अणु
	.get_resources = qcom_pcie_get_resources_2_3_3,
	.init = qcom_pcie_init_2_3_3,
	.deinit = qcom_pcie_deinit_2_3_3,
	.ltssm_enable = qcom_pcie_2_3_2_ltssm_enable,
पूर्ण;

/* Qcom IP rev.: 2.7.0	Synopsys IP rev.: 4.30a */
अटल स्थिर काष्ठा qcom_pcie_ops ops_2_7_0 = अणु
	.get_resources = qcom_pcie_get_resources_2_7_0,
	.init = qcom_pcie_init_2_7_0,
	.deinit = qcom_pcie_deinit_2_7_0,
	.ltssm_enable = qcom_pcie_2_3_2_ltssm_enable,
	.post_init = qcom_pcie_post_init_2_7_0,
	.post_deinit = qcom_pcie_post_deinit_2_7_0,
पूर्ण;

/* Qcom IP rev.: 1.9.0 */
अटल स्थिर काष्ठा qcom_pcie_ops ops_1_9_0 = अणु
	.get_resources = qcom_pcie_get_resources_2_7_0,
	.init = qcom_pcie_init_2_7_0,
	.deinit = qcom_pcie_deinit_2_7_0,
	.ltssm_enable = qcom_pcie_2_3_2_ltssm_enable,
	.post_init = qcom_pcie_post_init_2_7_0,
	.post_deinit = qcom_pcie_post_deinit_2_7_0,
	.config_sid = qcom_pcie_config_sid_sm8250,
पूर्ण;

अटल स्थिर काष्ठा dw_pcie_ops dw_pcie_ops = अणु
	.link_up = qcom_pcie_link_up,
	.start_link = qcom_pcie_start_link,
पूर्ण;

अटल पूर्णांक qcom_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pcie_port *pp;
	काष्ठा dw_pcie *pci;
	काष्ठा qcom_pcie *pcie;
	पूर्णांक ret;

	pcie = devm_kzalloc(dev, माप(*pcie), GFP_KERNEL);
	अगर (!pcie)
		वापस -ENOMEM;

	pci = devm_kzalloc(dev, माप(*pci), GFP_KERNEL);
	अगर (!pci)
		वापस -ENOMEM;

	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0)
		जाओ err_pm_runसमय_put;

	pci->dev = dev;
	pci->ops = &dw_pcie_ops;
	pp = &pci->pp;

	pcie->pci = pci;

	pcie->ops = of_device_get_match_data(dev);

	pcie->reset = devm_gpiod_get_optional(dev, "perst", GPIOD_OUT_HIGH);
	अगर (IS_ERR(pcie->reset)) अणु
		ret = PTR_ERR(pcie->reset);
		जाओ err_pm_runसमय_put;
	पूर्ण

	pcie->parf = devm_platक्रमm_ioremap_resource_byname(pdev, "parf");
	अगर (IS_ERR(pcie->parf)) अणु
		ret = PTR_ERR(pcie->parf);
		जाओ err_pm_runसमय_put;
	पूर्ण

	pcie->elbi = devm_platक्रमm_ioremap_resource_byname(pdev, "elbi");
	अगर (IS_ERR(pcie->elbi)) अणु
		ret = PTR_ERR(pcie->elbi);
		जाओ err_pm_runसमय_put;
	पूर्ण

	pcie->phy = devm_phy_optional_get(dev, "pciephy");
	अगर (IS_ERR(pcie->phy)) अणु
		ret = PTR_ERR(pcie->phy);
		जाओ err_pm_runसमय_put;
	पूर्ण

	ret = pcie->ops->get_resources(pcie);
	अगर (ret)
		जाओ err_pm_runसमय_put;

	pp->ops = &qcom_pcie_dw_ops;

	ret = phy_init(pcie->phy);
	अगर (ret) अणु
		pm_runसमय_disable(&pdev->dev);
		जाओ err_pm_runसमय_put;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pcie);

	ret = dw_pcie_host_init(pp);
	अगर (ret) अणु
		dev_err(dev, "cannot initialize host\n");
		pm_runसमय_disable(&pdev->dev);
		जाओ err_pm_runसमय_put;
	पूर्ण

	वापस 0;

err_pm_runसमय_put:
	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_pcie_match[] = अणु
	अणु .compatible = "qcom,pcie-apq8084", .data = &ops_1_0_0 पूर्ण,
	अणु .compatible = "qcom,pcie-ipq8064", .data = &ops_2_1_0 पूर्ण,
	अणु .compatible = "qcom,pcie-ipq8064-v2", .data = &ops_2_1_0 पूर्ण,
	अणु .compatible = "qcom,pcie-apq8064", .data = &ops_2_1_0 पूर्ण,
	अणु .compatible = "qcom,pcie-msm8996", .data = &ops_2_3_2 पूर्ण,
	अणु .compatible = "qcom,pcie-ipq8074", .data = &ops_2_3_3 पूर्ण,
	अणु .compatible = "qcom,pcie-ipq4019", .data = &ops_2_4_0 पूर्ण,
	अणु .compatible = "qcom,pcie-qcs404", .data = &ops_2_4_0 पूर्ण,
	अणु .compatible = "qcom,pcie-sdm845", .data = &ops_2_7_0 पूर्ण,
	अणु .compatible = "qcom,pcie-sm8250", .data = &ops_1_9_0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम qcom_fixup_class(काष्ठा pci_dev *dev)
अणु
	dev->class = PCI_CLASS_BRIDGE_PCI << 8;
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_QCOM, 0x0101, qcom_fixup_class);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_QCOM, 0x0104, qcom_fixup_class);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_QCOM, 0x0106, qcom_fixup_class);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_QCOM, 0x0107, qcom_fixup_class);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_QCOM, 0x0302, qcom_fixup_class);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_QCOM, 0x1000, qcom_fixup_class);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_QCOM, 0x1001, qcom_fixup_class);

अटल काष्ठा platक्रमm_driver qcom_pcie_driver = अणु
	.probe = qcom_pcie_probe,
	.driver = अणु
		.name = "qcom-pcie",
		.suppress_bind_attrs = true,
		.of_match_table = qcom_pcie_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(qcom_pcie_driver);
