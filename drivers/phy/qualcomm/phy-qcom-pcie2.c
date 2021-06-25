<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014-2017, The Linux Foundation. All rights reserved.
 * Copyright (c) 2019, Linaro Ltd.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/phy/phy.h>

#घोषणा PCIE20_PARF_PHY_STTS         0x3c
#घोषणा PCIE2_PHY_RESET_CTRL         0x44
#घोषणा PCIE20_PARF_PHY_REFCLK_CTRL2 0xa0
#घोषणा PCIE20_PARF_PHY_REFCLK_CTRL3 0xa4
#घोषणा PCIE20_PARF_PCS_SWING_CTRL1  0x88
#घोषणा PCIE20_PARF_PCS_SWING_CTRL2  0x8c
#घोषणा PCIE20_PARF_PCS_DEEMPH1      0x74
#घोषणा PCIE20_PARF_PCS_DEEMPH2      0x78
#घोषणा PCIE20_PARF_PCS_DEEMPH3      0x7c
#घोषणा PCIE20_PARF_CONFIGBITS       0x84
#घोषणा PCIE20_PARF_PHY_CTRL3        0x94
#घोषणा PCIE20_PARF_PCS_CTRL         0x80

#घोषणा TX_AMP_VAL                   120
#घोषणा PHY_RX0_EQ_GEN1_VAL          0
#घोषणा PHY_RX0_EQ_GEN2_VAL          4
#घोषणा TX_DEEMPH_GEN1_VAL           24
#घोषणा TX_DEEMPH_GEN2_3_5DB_VAL     26
#घोषणा TX_DEEMPH_GEN2_6DB_VAL       36
#घोषणा PHY_TX0_TERM_OFFST_VAL       0

काष्ठा qcom_phy अणु
	काष्ठा device *dev;
	व्योम __iomem *base;

	काष्ठा regulator_bulk_data vregs[2];

	काष्ठा reset_control *phy_reset;
	काष्ठा reset_control *pipe_reset;
	काष्ठा clk *pipe_clk;
पूर्ण;

अटल पूर्णांक qcom_pcie2_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा qcom_phy *qphy = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = reset_control_deनिश्चित(qphy->phy_reset);
	अगर (ret) अणु
		dev_err(qphy->dev, "cannot deassert pipe reset\n");
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(qphy->vregs), qphy->vregs);
	अगर (ret)
		reset_control_निश्चित(qphy->phy_reset);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_pcie2_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा qcom_phy *qphy = phy_get_drvdata(phy);
	पूर्णांक ret;
	u32 val;

	/* Program REF_CLK source */
	val = पढ़ोl(qphy->base + PCIE20_PARF_PHY_REFCLK_CTRL2);
	val &= ~BIT(1);
	ग_लिखोl(val, qphy->base + PCIE20_PARF_PHY_REFCLK_CTRL2);

	usleep_range(1000, 2000);

	/* Don't use PAD क्रम refघड़ी */
	val = पढ़ोl(qphy->base + PCIE20_PARF_PHY_REFCLK_CTRL2);
	val &= ~BIT(0);
	ग_लिखोl(val, qphy->base + PCIE20_PARF_PHY_REFCLK_CTRL2);

	/* Program SSP ENABLE */
	val = पढ़ोl(qphy->base + PCIE20_PARF_PHY_REFCLK_CTRL3);
	val |= BIT(0);
	ग_लिखोl(val, qphy->base + PCIE20_PARF_PHY_REFCLK_CTRL3);

	usleep_range(1000, 2000);

	/* Assert Phy SW Reset */
	val = पढ़ोl(qphy->base + PCIE2_PHY_RESET_CTRL);
	val |= BIT(0);
	ग_लिखोl(val, qphy->base + PCIE2_PHY_RESET_CTRL);

	/* Program Tx Amplitude */
	val = पढ़ोl(qphy->base + PCIE20_PARF_PCS_SWING_CTRL1);
	val &= ~0x7f;
	val |= TX_AMP_VAL;
	ग_लिखोl(val, qphy->base + PCIE20_PARF_PCS_SWING_CTRL1);

	val = पढ़ोl(qphy->base + PCIE20_PARF_PCS_SWING_CTRL2);
	val &= ~0x7f;
	val |= TX_AMP_VAL;
	ग_लिखोl(val, qphy->base + PCIE20_PARF_PCS_SWING_CTRL2);

	/* Program De-Emphasis */
	val = पढ़ोl(qphy->base + PCIE20_PARF_PCS_DEEMPH1);
	val &= ~0x3f;
	val |= TX_DEEMPH_GEN2_6DB_VAL;
	ग_लिखोl(val, qphy->base + PCIE20_PARF_PCS_DEEMPH1);

	val = पढ़ोl(qphy->base + PCIE20_PARF_PCS_DEEMPH2);
	val &= ~0x3f;
	val |= TX_DEEMPH_GEN2_3_5DB_VAL;
	ग_लिखोl(val, qphy->base + PCIE20_PARF_PCS_DEEMPH2);

	val = पढ़ोl(qphy->base + PCIE20_PARF_PCS_DEEMPH3);
	val &= ~0x3f;
	val |= TX_DEEMPH_GEN1_VAL;
	ग_लिखोl(val, qphy->base + PCIE20_PARF_PCS_DEEMPH3);

	/* Program Rx_Eq */
	val = पढ़ोl(qphy->base + PCIE20_PARF_CONFIGBITS);
	val &= ~0x7;
	val |= PHY_RX0_EQ_GEN2_VAL;
	ग_लिखोl(val, qphy->base + PCIE20_PARF_CONFIGBITS);

	/* Program Tx0_term_offset */
	val = पढ़ोl(qphy->base + PCIE20_PARF_PHY_CTRL3);
	val &= ~0x1f;
	val |= PHY_TX0_TERM_OFFST_VAL;
	ग_लिखोl(val, qphy->base + PCIE20_PARF_PHY_CTRL3);

	/* disable Tx2Rx Loopback */
	val = पढ़ोl(qphy->base + PCIE20_PARF_PCS_CTRL);
	val &= ~BIT(1);
	ग_लिखोl(val, qphy->base + PCIE20_PARF_PCS_CTRL);

	/* De-निश्चित Phy SW Reset */
	val = पढ़ोl(qphy->base + PCIE2_PHY_RESET_CTRL);
	val &= ~BIT(0);
	ग_लिखोl(val, qphy->base + PCIE2_PHY_RESET_CTRL);

	usleep_range(1000, 2000);

	ret = reset_control_deनिश्चित(qphy->pipe_reset);
	अगर (ret) अणु
		dev_err(qphy->dev, "cannot deassert pipe reset\n");
		जाओ out;
	पूर्ण

	clk_set_rate(qphy->pipe_clk, 250000000);

	ret = clk_prepare_enable(qphy->pipe_clk);
	अगर (ret) अणु
		dev_err(qphy->dev, "failed to enable pipe clock\n");
		जाओ out;
	पूर्ण

	ret = पढ़ोl_poll_समयout(qphy->base + PCIE20_PARF_PHY_STTS, val,
				 !(val & BIT(0)), 1000, 10);
	अगर (ret)
		dev_err(qphy->dev, "phy initialization failed\n");

out:
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_pcie2_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा qcom_phy *qphy = phy_get_drvdata(phy);
	u32 val;

	val = पढ़ोl(qphy->base + PCIE2_PHY_RESET_CTRL);
	val |= BIT(0);
	ग_लिखोl(val, qphy->base + PCIE2_PHY_RESET_CTRL);

	clk_disable_unprepare(qphy->pipe_clk);
	reset_control_निश्चित(qphy->pipe_reset);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_pcie2_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा qcom_phy *qphy = phy_get_drvdata(phy);

	regulator_bulk_disable(ARRAY_SIZE(qphy->vregs), qphy->vregs);
	reset_control_निश्चित(qphy->phy_reset);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops qcom_pcie2_ops = अणु
	.init = qcom_pcie2_phy_init,
	.घातer_on = qcom_pcie2_phy_घातer_on,
	.घातer_off = qcom_pcie2_phy_घातer_off,
	.निकास = qcom_pcie2_phy_निकास,
	.owner = THIS_MODULE,
पूर्ण;

/*
 * Register a fixed rate pipe घड़ी.
 *
 * The <s>_pipe_clksrc generated by PHY goes to the GCC that gate
 * controls it. The <s>_pipe_clk coming out of the GCC is requested
 * by the PHY driver क्रम its operations.
 * We रेजिस्टर the <s>_pipe_clksrc here. The gcc driver takes care
 * of assigning this <s>_pipe_clksrc as parent to <s>_pipe_clk.
 * Below picture shows this relationship.
 *
 *         +---------------+
 *         |   PHY block   |<<---------------------------------------+
 *         |               |                                         |
 *         |   +-------+   |                   +-----+               |
 *   I/P---^-->|  PLL  |---^--->pipe_clksrc--->| GCC |--->pipe_clk---+
 *    clk  |   +-------+   |                   +-----+
 *         +---------------+
 */
अटल पूर्णांक phy_pipe_clksrc_रेजिस्टर(काष्ठा qcom_phy *qphy)
अणु
	काष्ठा device_node *np = qphy->dev->of_node;
	काष्ठा clk_fixed_rate *fixed;
	काष्ठा clk_init_data init = अणु पूर्ण;
	पूर्णांक ret;

	ret = of_property_पढ़ो_string(np, "clock-output-names", &init.name);
	अगर (ret) अणु
		dev_err(qphy->dev, "%s: No clock-output-names\n", np->name);
		वापस ret;
	पूर्ण

	fixed = devm_kzalloc(qphy->dev, माप(*fixed), GFP_KERNEL);
	अगर (!fixed)
		वापस -ENOMEM;

	init.ops = &clk_fixed_rate_ops;

	/* controllers using QMP phys use 250MHz pipe घड़ी पूर्णांकerface */
	fixed->fixed_rate = 250000000;
	fixed->hw.init = &init;

	वापस devm_clk_hw_रेजिस्टर(qphy->dev, &fixed->hw);
पूर्ण

अटल पूर्णांक qcom_pcie2_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा qcom_phy *qphy;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy *phy;
	पूर्णांक ret;

	qphy = devm_kzalloc(dev, माप(*qphy), GFP_KERNEL);
	अगर (!qphy)
		वापस -ENOMEM;

	qphy->dev = dev;
	qphy->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(qphy->base))
		वापस PTR_ERR(qphy->base);

	ret = phy_pipe_clksrc_रेजिस्टर(qphy);
	अगर (ret) अणु
		dev_err(dev, "failed to register pipe_clk\n");
		वापस ret;
	पूर्ण

	qphy->vregs[0].supply = "vdda-vp";
	qphy->vregs[1].supply = "vdda-vph";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(qphy->vregs), qphy->vregs);
	अगर (ret < 0)
		वापस ret;

	qphy->pipe_clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(qphy->pipe_clk)) अणु
		dev_err(dev, "failed to acquire pipe clock\n");
		वापस PTR_ERR(qphy->pipe_clk);
	पूर्ण

	qphy->phy_reset = devm_reset_control_get_exclusive(dev, "phy");
	अगर (IS_ERR(qphy->phy_reset)) अणु
		dev_err(dev, "failed to acquire phy reset\n");
		वापस PTR_ERR(qphy->phy_reset);
	पूर्ण

	qphy->pipe_reset = devm_reset_control_get_exclusive(dev, "pipe");
	अगर (IS_ERR(qphy->pipe_reset)) अणु
		dev_err(dev, "failed to acquire pipe reset\n");
		वापस PTR_ERR(qphy->pipe_reset);
	पूर्ण

	phy = devm_phy_create(dev, dev->of_node, &qcom_pcie2_ops);
	अगर (IS_ERR(phy)) अणु
		dev_err(dev, "failed to create phy\n");
		वापस PTR_ERR(phy);
	पूर्ण

	phy_set_drvdata(phy, qphy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider))
		dev_err(dev, "failed to register phy provider\n");

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_pcie2_phy_match_table[] = अणु
	अणु .compatible = "qcom,pcie2-phy" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_pcie2_phy_match_table);

अटल काष्ठा platक्रमm_driver qcom_pcie2_phy_driver = अणु
	.probe = qcom_pcie2_phy_probe,
	.driver = अणु
		.name = "phy-qcom-pcie2",
		.of_match_table = qcom_pcie2_phy_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(qcom_pcie2_phy_driver);

MODULE_DESCRIPTION("Qualcomm PCIe PHY driver");
MODULE_LICENSE("GPL v2");
