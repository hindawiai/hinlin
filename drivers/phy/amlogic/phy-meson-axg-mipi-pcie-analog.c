<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Amlogic AXG MIPI + PCIE analog PHY driver
 *
 * Copyright (C) 2019 Remi Pommarel <repk@triplefau.lt>
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regmap.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <dt-bindings/phy/phy.h>

#घोषणा HHI_MIPI_CNTL0 0x00
#घोषणा		HHI_MIPI_CNTL0_COMMON_BLOCK	GENMASK(31, 28)
#घोषणा		HHI_MIPI_CNTL0_ENABLE		BIT(29)
#घोषणा		HHI_MIPI_CNTL0_BANDGAP		BIT(26)
#घोषणा		HHI_MIPI_CNTL0_DIF_REF_CTL1	GENMASK(25, 16)
#घोषणा		HHI_MIPI_CNTL0_DIF_REF_CTL0	GENMASK(15, 0)

#घोषणा HHI_MIPI_CNTL1 0x04
#घोषणा		HHI_MIPI_CNTL1_CH0_CML_PDR_EN	BIT(12)
#घोषणा		HHI_MIPI_CNTL1_LP_ABILITY	GENMASK(5, 4)
#घोषणा		HHI_MIPI_CNTL1_LP_RESISTER	BIT(3)
#घोषणा		HHI_MIPI_CNTL1_INPUT_SETTING	BIT(2)
#घोषणा		HHI_MIPI_CNTL1_INPUT_SEL	BIT(1)
#घोषणा		HHI_MIPI_CNTL1_PRBS7_EN		BIT(0)

#घोषणा HHI_MIPI_CNTL2 0x08
#घोषणा		HHI_MIPI_CNTL2_CH_PU		GENMASK(31, 25)
#घोषणा		HHI_MIPI_CNTL2_CH_CTL		GENMASK(24, 19)
#घोषणा		HHI_MIPI_CNTL2_CH0_DIGDR_EN	BIT(18)
#घोषणा		HHI_MIPI_CNTL2_CH_DIGDR_EN	BIT(17)
#घोषणा		HHI_MIPI_CNTL2_LPULPS_EN	BIT(16)
#घोषणा		HHI_MIPI_CNTL2_CH_EN		GENMASK(15, 11)
#घोषणा		HHI_MIPI_CNTL2_CH0_LP_CTL	GENMASK(10, 1)

#घोषणा DSI_LANE_0              BIT(4)
#घोषणा DSI_LANE_1              BIT(3)
#घोषणा DSI_LANE_CLK            BIT(2)
#घोषणा DSI_LANE_2              BIT(1)
#घोषणा DSI_LANE_3              BIT(0)

काष्ठा phy_axg_mipi_pcie_analog_priv अणु
	काष्ठा phy *phy;
	काष्ठा regmap *regmap;
	bool dsi_configured;
	bool dsi_enabled;
	bool घातered;
	काष्ठा phy_configure_opts_mipi_dphy config;
पूर्ण;

अटल व्योम phy_bandgap_enable(काष्ठा phy_axg_mipi_pcie_analog_priv *priv)
अणु
	regmap_update_bits(priv->regmap, HHI_MIPI_CNTL0,
			HHI_MIPI_CNTL0_BANDGAP, HHI_MIPI_CNTL0_BANDGAP);

	regmap_update_bits(priv->regmap, HHI_MIPI_CNTL0,
			HHI_MIPI_CNTL0_ENABLE, HHI_MIPI_CNTL0_ENABLE);
पूर्ण

अटल व्योम phy_bandgap_disable(काष्ठा phy_axg_mipi_pcie_analog_priv *priv)
अणु
	regmap_update_bits(priv->regmap, HHI_MIPI_CNTL0,
			HHI_MIPI_CNTL0_BANDGAP, 0);
	regmap_update_bits(priv->regmap, HHI_MIPI_CNTL0,
			HHI_MIPI_CNTL0_ENABLE, 0);
पूर्ण

अटल व्योम phy_dsi_analog_enable(काष्ठा phy_axg_mipi_pcie_analog_priv *priv)
अणु
	u32 reg;

	regmap_update_bits(priv->regmap, HHI_MIPI_CNTL0,
			   HHI_MIPI_CNTL0_DIF_REF_CTL1,
			   FIELD_PREP(HHI_MIPI_CNTL0_DIF_REF_CTL1, 0x1b8));
	regmap_update_bits(priv->regmap, HHI_MIPI_CNTL0,
			   BIT(31), BIT(31));
	regmap_update_bits(priv->regmap, HHI_MIPI_CNTL0,
			   HHI_MIPI_CNTL0_DIF_REF_CTL0,
			   FIELD_PREP(HHI_MIPI_CNTL0_DIF_REF_CTL0, 0x8));

	regmap_ग_लिखो(priv->regmap, HHI_MIPI_CNTL1, 0x001e);

	regmap_ग_लिखो(priv->regmap, HHI_MIPI_CNTL2,
		     (0x26e0 << 16) | (0x459 << 0));

	reg = DSI_LANE_CLK;
	चयन (priv->config.lanes) अणु
	हाल 4:
		reg |= DSI_LANE_3;
		fallthrough;
	हाल 3:
		reg |= DSI_LANE_2;
		fallthrough;
	हाल 2:
		reg |= DSI_LANE_1;
		fallthrough;
	हाल 1:
		reg |= DSI_LANE_0;
		अवरोध;
	शेष:
		reg = 0;
	पूर्ण

	regmap_update_bits(priv->regmap, HHI_MIPI_CNTL2,
			   HHI_MIPI_CNTL2_CH_EN,
			   FIELD_PREP(HHI_MIPI_CNTL2_CH_EN, reg));

	priv->dsi_enabled = true;
पूर्ण

अटल व्योम phy_dsi_analog_disable(काष्ठा phy_axg_mipi_pcie_analog_priv *priv)
अणु
	regmap_update_bits(priv->regmap, HHI_MIPI_CNTL0,
			HHI_MIPI_CNTL0_DIF_REF_CTL1,
			FIELD_PREP(HHI_MIPI_CNTL0_DIF_REF_CTL1, 0));
	regmap_update_bits(priv->regmap, HHI_MIPI_CNTL0, BIT(31), 0);
	regmap_update_bits(priv->regmap, HHI_MIPI_CNTL0,
			HHI_MIPI_CNTL0_DIF_REF_CTL1, 0);

	regmap_ग_लिखो(priv->regmap, HHI_MIPI_CNTL1, 0x6);

	regmap_ग_लिखो(priv->regmap, HHI_MIPI_CNTL2, 0x00200000);

	priv->dsi_enabled = false;
पूर्ण

अटल पूर्णांक phy_axg_mipi_pcie_analog_configure(काष्ठा phy *phy,
					      जोड़ phy_configure_opts *opts)
अणु
	काष्ठा phy_axg_mipi_pcie_analog_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = phy_mipi_dphy_config_validate(&opts->mipi_dphy);
	अगर (ret)
		वापस ret;

	स_नकल(&priv->config, opts, माप(priv->config));

	priv->dsi_configured = true;

	/* If PHY was alपढ़ोy घातered on, setup the DSI analog part */
	अगर (priv->घातered) अणु
		/* If reconfiguring, disable & reconfigure */
		अगर (priv->dsi_enabled)
			phy_dsi_analog_disable(priv);

		usleep_range(100, 200);

		phy_dsi_analog_enable(priv);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक phy_axg_mipi_pcie_analog_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा phy_axg_mipi_pcie_analog_priv *priv = phy_get_drvdata(phy);

	phy_bandgap_enable(priv);

	अगर (priv->dsi_configured)
		phy_dsi_analog_enable(priv);

	priv->घातered = true;

	वापस 0;
पूर्ण

अटल पूर्णांक phy_axg_mipi_pcie_analog_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा phy_axg_mipi_pcie_analog_priv *priv = phy_get_drvdata(phy);

	phy_bandgap_disable(priv);

	अगर (priv->dsi_enabled)
		phy_dsi_analog_disable(priv);

	priv->घातered = false;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops phy_axg_mipi_pcie_analog_ops = अणु
	.configure = phy_axg_mipi_pcie_analog_configure,
	.घातer_on = phy_axg_mipi_pcie_analog_घातer_on,
	.घातer_off = phy_axg_mipi_pcie_analog_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक phy_axg_mipi_pcie_analog_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_axg_mipi_pcie_analog_priv *priv;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा regmap *map;
	पूर्णांक ret;

	priv = devm_kदो_स्मृति(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* Get the hhi प्रणाली controller node */
	map = syscon_node_to_regmap(of_get_parent(dev->of_node));
	अगर (IS_ERR(map)) अणु
		dev_err(dev,
			"failed to get HHI regmap\n");
		वापस PTR_ERR(map);
	पूर्ण

	priv->regmap = map;

	priv->phy = devm_phy_create(dev, np, &phy_axg_mipi_pcie_analog_ops);
	अगर (IS_ERR(priv->phy)) अणु
		ret = PTR_ERR(priv->phy);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to create PHY\n");
		वापस ret;
	पूर्ण

	phy_set_drvdata(priv->phy, priv);
	dev_set_drvdata(dev, priv);

	phy = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy);
पूर्ण

अटल स्थिर काष्ठा of_device_id phy_axg_mipi_pcie_analog_of_match[] = अणु
	अणु
		.compatible = "amlogic,axg-mipi-pcie-analog-phy",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, phy_axg_mipi_pcie_analog_of_match);

अटल काष्ठा platक्रमm_driver phy_axg_mipi_pcie_analog_driver = अणु
	.probe = phy_axg_mipi_pcie_analog_probe,
	.driver = अणु
		.name = "phy-axg-mipi-pcie-analog",
		.of_match_table = phy_axg_mipi_pcie_analog_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(phy_axg_mipi_pcie_analog_driver);

MODULE_AUTHOR("Remi Pommarel <repk@triplefau.lt>");
MODULE_DESCRIPTION("Amlogic AXG MIPI + PCIE analog PHY driver");
MODULE_LICENSE("GPL v2");
