<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012-2014,2017 The Linux Foundation. All rights reserved.
 * Copyright (c) 2018-2020, Linaro Limited
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#घोषणा PHY_CTRL0			0x6C
#घोषणा PHY_CTRL1			0x70
#घोषणा PHY_CTRL2			0x74
#घोषणा PHY_CTRL4			0x7C

/* PHY_CTRL bits */
#घोषणा REF_PHY_EN			BIT(0)
#घोषणा LANE0_PWR_ON			BIT(2)
#घोषणा SWI_PCS_CLK_SEL			BIT(4)
#घोषणा TST_PWR_DOWN			BIT(4)
#घोषणा PHY_RESET			BIT(7)

#घोषणा NUM_BULK_CLKS			3
#घोषणा NUM_BULK_REGS			2

काष्ठा ssphy_priv अणु
	व्योम __iomem *base;
	काष्ठा device *dev;
	काष्ठा reset_control *reset_com;
	काष्ठा reset_control *reset_phy;
	काष्ठा regulator_bulk_data regs[NUM_BULK_REGS];
	काष्ठा clk_bulk_data clks[NUM_BULK_CLKS];
	क्रमागत phy_mode mode;
पूर्ण;

अटल अंतरभूत व्योम qcom_ssphy_updatel(व्योम __iomem *addr, u32 mask, u32 val)
अणु
	ग_लिखोl((पढ़ोl(addr) & ~mask) | val, addr);
पूर्ण

अटल पूर्णांक qcom_ssphy_करो_reset(काष्ठा ssphy_priv *priv)
अणु
	पूर्णांक ret;

	अगर (!priv->reset_com) अणु
		qcom_ssphy_updatel(priv->base + PHY_CTRL1, PHY_RESET,
				   PHY_RESET);
		usleep_range(10, 20);
		qcom_ssphy_updatel(priv->base + PHY_CTRL1, PHY_RESET, 0);
	पूर्ण अन्यथा अणु
		ret = reset_control_निश्चित(priv->reset_com);
		अगर (ret) अणु
			dev_err(priv->dev, "Failed to assert reset com\n");
			वापस ret;
		पूर्ण

		ret = reset_control_निश्चित(priv->reset_phy);
		अगर (ret) अणु
			dev_err(priv->dev, "Failed to assert reset phy\n");
			वापस ret;
		पूर्ण

		usleep_range(10, 20);

		ret = reset_control_deनिश्चित(priv->reset_com);
		अगर (ret) अणु
			dev_err(priv->dev, "Failed to deassert reset com\n");
			वापस ret;
		पूर्ण

		ret = reset_control_deनिश्चित(priv->reset_phy);
		अगर (ret) अणु
			dev_err(priv->dev, "Failed to deassert reset phy\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_ssphy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा ssphy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = regulator_bulk_enable(NUM_BULK_REGS, priv->regs);
	अगर (ret)
		वापस ret;

	ret = clk_bulk_prepare_enable(NUM_BULK_CLKS, priv->clks);
	अगर (ret)
		जाओ err_disable_regulator;

	ret = qcom_ssphy_करो_reset(priv);
	अगर (ret)
		जाओ err_disable_घड़ी;

	ग_लिखोb(SWI_PCS_CLK_SEL, priv->base + PHY_CTRL0);
	qcom_ssphy_updatel(priv->base + PHY_CTRL4, LANE0_PWR_ON, LANE0_PWR_ON);
	qcom_ssphy_updatel(priv->base + PHY_CTRL2, REF_PHY_EN, REF_PHY_EN);
	qcom_ssphy_updatel(priv->base + PHY_CTRL4, TST_PWR_DOWN, 0);

	वापस 0;
err_disable_घड़ी:
	clk_bulk_disable_unprepare(NUM_BULK_CLKS, priv->clks);
err_disable_regulator:
	regulator_bulk_disable(NUM_BULK_REGS, priv->regs);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_ssphy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा ssphy_priv *priv = phy_get_drvdata(phy);

	qcom_ssphy_updatel(priv->base + PHY_CTRL4, LANE0_PWR_ON, 0);
	qcom_ssphy_updatel(priv->base + PHY_CTRL2, REF_PHY_EN, 0);
	qcom_ssphy_updatel(priv->base + PHY_CTRL4, TST_PWR_DOWN, TST_PWR_DOWN);

	clk_bulk_disable_unprepare(NUM_BULK_CLKS, priv->clks);
	regulator_bulk_disable(NUM_BULK_REGS, priv->regs);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_ssphy_init_घड़ी(काष्ठा ssphy_priv *priv)
अणु
	priv->clks[0].id = "ref";
	priv->clks[1].id = "ahb";
	priv->clks[2].id = "pipe";

	वापस devm_clk_bulk_get(priv->dev, NUM_BULK_CLKS, priv->clks);
पूर्ण

अटल पूर्णांक qcom_ssphy_init_regulator(काष्ठा ssphy_priv *priv)
अणु
	पूर्णांक ret;

	priv->regs[0].supply = "vdd";
	priv->regs[1].supply = "vdda1p8";
	ret = devm_regulator_bulk_get(priv->dev, NUM_BULK_REGS, priv->regs);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(priv->dev, "Failed to get regulators\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_ssphy_init_reset(काष्ठा ssphy_priv *priv)
अणु
	priv->reset_com = devm_reset_control_get_optional_exclusive(priv->dev, "com");
	अगर (IS_ERR(priv->reset_com)) अणु
		dev_err(priv->dev, "Failed to get reset control com\n");
		वापस PTR_ERR(priv->reset_com);
	पूर्ण

	अगर (priv->reset_com) अणु
		/* अगर reset_com is present, reset_phy is no दीर्घer optional */
		priv->reset_phy = devm_reset_control_get_exclusive(priv->dev, "phy");
		अगर (IS_ERR(priv->reset_phy)) अणु
			dev_err(priv->dev, "Failed to get reset control phy\n");
			वापस PTR_ERR(priv->reset_phy);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops qcom_ssphy_ops = अणु
	.घातer_off = qcom_ssphy_घातer_off,
	.घातer_on = qcom_ssphy_घातer_on,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक qcom_ssphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_provider *provider;
	काष्ठा ssphy_priv *priv;
	काष्ठा phy *phy;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(काष्ठा ssphy_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	priv->mode = PHY_MODE_INVALID;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	ret = qcom_ssphy_init_घड़ी(priv);
	अगर (ret)
		वापस ret;

	ret = qcom_ssphy_init_reset(priv);
	अगर (ret)
		वापस ret;

	ret = qcom_ssphy_init_regulator(priv);
	अगर (ret)
		वापस ret;

	phy = devm_phy_create(dev, dev->of_node, &qcom_ssphy_ops);
	अगर (IS_ERR(phy)) अणु
		dev_err(dev, "Failed to create the SS phy\n");
		वापस PTR_ERR(phy);
	पूर्ण

	phy_set_drvdata(phy, priv);

	provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_ssphy_match[] = अणु
	अणु .compatible = "qcom,usb-ss-28nm-phy", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_ssphy_match);

अटल काष्ठा platक्रमm_driver qcom_ssphy_driver = अणु
	.probe		= qcom_ssphy_probe,
	.driver = अणु
		.name	= "qcom-usb-ssphy",
		.of_match_table = qcom_ssphy_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_ssphy_driver);

MODULE_DESCRIPTION("Qualcomm SuperSpeed USB PHY driver");
MODULE_LICENSE("GPL v2");
