<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Lantiq XWAY SoC RCU module based USB 1.1/2.0 PHY driver
 *
 * Copyright (C) 2016 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 * Copyright (C) 2017 Hauke Mehrtens <hauke@hauke-m.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

/* Transmitter HS Pre-Emphasis Enable */
#घोषणा RCU_CFG1_TX_PEE		BIT(0)
/* Disconnect Threshold */
#घोषणा RCU_CFG1_DIS_THR_MASK	0x00038000
#घोषणा RCU_CFG1_DIS_THR_SHIFT	15

काष्ठा ltq_rcu_usb2_bits अणु
	u8 hosपंचांगode;
	u8 slave_endianness;
	u8 host_endianness;
	bool have_ana_cfg;
पूर्ण;

काष्ठा ltq_rcu_usb2_priv अणु
	काष्ठा regmap			*regmap;
	अचिन्हित पूर्णांक			phy_reg_offset;
	अचिन्हित पूर्णांक			ana_cfg1_reg_offset;
	स्थिर काष्ठा ltq_rcu_usb2_bits	*reg_bits;
	काष्ठा device			*dev;
	काष्ठा phy			*phy;
	काष्ठा clk			*phy_gate_clk;
	काष्ठा reset_control		*ctrl_reset;
	काष्ठा reset_control		*phy_reset;
पूर्ण;

अटल स्थिर काष्ठा ltq_rcu_usb2_bits xway_rcu_usb2_reg_bits = अणु
	.hosपंचांगode = 11,
	.slave_endianness = 9,
	.host_endianness = 10,
	.have_ana_cfg = false,
पूर्ण;

अटल स्थिर काष्ठा ltq_rcu_usb2_bits xrx100_rcu_usb2_reg_bits = अणु
	.hosपंचांगode = 11,
	.slave_endianness = 17,
	.host_endianness = 10,
	.have_ana_cfg = false,
पूर्ण;

अटल स्थिर काष्ठा ltq_rcu_usb2_bits xrx200_rcu_usb2_reg_bits = अणु
	.hosपंचांगode = 11,
	.slave_endianness = 9,
	.host_endianness = 10,
	.have_ana_cfg = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ltq_rcu_usb2_phy_of_match[] = अणु
	अणु
		.compatible = "lantiq,ase-usb2-phy",
		.data = &xway_rcu_usb2_reg_bits,
	पूर्ण,
	अणु
		.compatible = "lantiq,danube-usb2-phy",
		.data = &xway_rcu_usb2_reg_bits,
	पूर्ण,
	अणु
		.compatible = "lantiq,xrx100-usb2-phy",
		.data = &xrx100_rcu_usb2_reg_bits,
	पूर्ण,
	अणु
		.compatible = "lantiq,xrx200-usb2-phy",
		.data = &xrx200_rcu_usb2_reg_bits,
	पूर्ण,
	अणु
		.compatible = "lantiq,xrx300-usb2-phy",
		.data = &xrx200_rcu_usb2_reg_bits,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ltq_rcu_usb2_phy_of_match);

अटल पूर्णांक ltq_rcu_usb2_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा ltq_rcu_usb2_priv *priv = phy_get_drvdata(phy);

	अगर (priv->reg_bits->have_ana_cfg) अणु
		regmap_update_bits(priv->regmap, priv->ana_cfg1_reg_offset,
			RCU_CFG1_TX_PEE, RCU_CFG1_TX_PEE);
		regmap_update_bits(priv->regmap, priv->ana_cfg1_reg_offset,
			RCU_CFG1_DIS_THR_MASK, 7 << RCU_CFG1_DIS_THR_SHIFT);
	पूर्ण

	/* Configure core to host mode */
	regmap_update_bits(priv->regmap, priv->phy_reg_offset,
			   BIT(priv->reg_bits->hosपंचांगode), 0);

	/* Select DMA endianness (Host-endian: big-endian) */
	regmap_update_bits(priv->regmap, priv->phy_reg_offset,
		BIT(priv->reg_bits->slave_endianness), 0);
	regmap_update_bits(priv->regmap, priv->phy_reg_offset,
		BIT(priv->reg_bits->host_endianness),
		BIT(priv->reg_bits->host_endianness));

	वापस 0;
पूर्ण

अटल पूर्णांक ltq_rcu_usb2_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा ltq_rcu_usb2_priv *priv = phy_get_drvdata(phy);
	काष्ठा device *dev = priv->dev;
	पूर्णांक ret;

	reset_control_deनिश्चित(priv->phy_reset);

	ret = clk_prepare_enable(priv->phy_gate_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable PHY gate\n");
		वापस ret;
	पूर्ण

	/*
	 * at least the xrx200 usb2 phy requires some extra समय to be
	 * operational after enabling the घड़ी
	 */
	usleep_range(100, 200);

	वापस ret;
पूर्ण

अटल पूर्णांक ltq_rcu_usb2_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा ltq_rcu_usb2_priv *priv = phy_get_drvdata(phy);

	reset_control_निश्चित(priv->phy_reset);

	clk_disable_unprepare(priv->phy_gate_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops ltq_rcu_usb2_phy_ops = अणु
	.init		= ltq_rcu_usb2_phy_init,
	.घातer_on	= ltq_rcu_usb2_phy_घातer_on,
	.घातer_off	= ltq_rcu_usb2_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक ltq_rcu_usb2_of_parse(काष्ठा ltq_rcu_usb2_priv *priv,
				 काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = priv->dev;
	स्थिर __be32 *offset;

	priv->reg_bits = of_device_get_match_data(dev);

	priv->regmap = syscon_node_to_regmap(dev->of_node->parent);
	अगर (IS_ERR(priv->regmap)) अणु
		dev_err(dev, "Failed to lookup RCU regmap\n");
		वापस PTR_ERR(priv->regmap);
	पूर्ण

	offset = of_get_address(dev->of_node, 0, शून्य, शून्य);
	अगर (!offset) अणु
		dev_err(dev, "Failed to get RCU PHY reg offset\n");
		वापस -ENOENT;
	पूर्ण
	priv->phy_reg_offset = __be32_to_cpu(*offset);

	अगर (priv->reg_bits->have_ana_cfg) अणु
		offset = of_get_address(dev->of_node, 1, शून्य, शून्य);
		अगर (!offset) अणु
			dev_err(dev, "Failed to get RCU ANA CFG1 reg offset\n");
			वापस -ENOENT;
		पूर्ण
		priv->ana_cfg1_reg_offset = __be32_to_cpu(*offset);
	पूर्ण

	priv->phy_gate_clk = devm_clk_get(dev, "phy");
	अगर (IS_ERR(priv->phy_gate_clk)) अणु
		dev_err(dev, "Unable to get USB phy gate clk\n");
		वापस PTR_ERR(priv->phy_gate_clk);
	पूर्ण

	priv->ctrl_reset = devm_reset_control_get_shared(dev, "ctrl");
	अगर (IS_ERR(priv->ctrl_reset)) अणु
		अगर (PTR_ERR(priv->ctrl_reset) != -EPROBE_DEFER)
			dev_err(dev, "failed to get 'ctrl' reset\n");
		वापस PTR_ERR(priv->ctrl_reset);
	पूर्ण

	priv->phy_reset = devm_reset_control_get_optional(dev, "phy");

	वापस PTR_ERR_OR_ZERO(priv->phy_reset);
पूर्ण

अटल पूर्णांक ltq_rcu_usb2_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ltq_rcu_usb2_priv *priv;
	काष्ठा phy_provider *provider;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;

	ret = ltq_rcu_usb2_of_parse(priv, pdev);
	अगर (ret)
		वापस ret;

	/* Reset USB core through reset controller */
	reset_control_deनिश्चित(priv->ctrl_reset);

	reset_control_निश्चित(priv->phy_reset);

	priv->phy = devm_phy_create(dev, dev->of_node, &ltq_rcu_usb2_phy_ops);
	अगर (IS_ERR(priv->phy)) अणु
		dev_err(dev, "failed to create PHY\n");
		वापस PTR_ERR(priv->phy);
	पूर्ण

	phy_set_drvdata(priv->phy, priv);

	provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(provider))
		वापस PTR_ERR(provider);

	dev_set_drvdata(priv->dev, priv);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ltq_rcu_usb2_phy_driver = अणु
	.probe	= ltq_rcu_usb2_phy_probe,
	.driver = अणु
		.name	= "lantiq-rcu-usb2-phy",
		.of_match_table	= ltq_rcu_usb2_phy_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(ltq_rcu_usb2_phy_driver);

MODULE_AUTHOR("Martin Blumenstingl <martin.blumenstingl@googlemail.com>");
MODULE_DESCRIPTION("Lantiq XWAY USB2 PHY driver");
MODULE_LICENSE("GPL v2");
