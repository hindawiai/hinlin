<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Amlogic AXG PCIE PHY driver
 *
 * Copyright (C) 2020 Remi Pommarel <repk@triplefau.lt>
 */
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bitfield.h>
#समावेश <dt-bindings/phy/phy.h>

#घोषणा MESON_PCIE_REG0 0x00
#घोषणा		MESON_PCIE_COMMON_CLK	BIT(4)
#घोषणा		MESON_PCIE_PORT_SEL	GENMASK(3, 2)
#घोषणा		MESON_PCIE_CLK		BIT(1)
#घोषणा		MESON_PCIE_POWERDOWN	BIT(0)

#घोषणा MESON_PCIE_TWO_X1		FIELD_PREP(MESON_PCIE_PORT_SEL, 0x3)
#घोषणा MESON_PCIE_COMMON_REF_CLK	FIELD_PREP(MESON_PCIE_COMMON_CLK, 0x1)
#घोषणा MESON_PCIE_PHY_INIT		(MESON_PCIE_TWO_X1 |		\
					 MESON_PCIE_COMMON_REF_CLK)
#घोषणा MESON_PCIE_RESET_DELAY		500

काष्ठा phy_axg_pcie_priv अणु
	काष्ठा phy *phy;
	काष्ठा phy *analog;
	काष्ठा regmap *regmap;
	काष्ठा reset_control *reset;
पूर्ण;

अटल स्थिर काष्ठा regmap_config phy_axg_pcie_regmap_conf = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = MESON_PCIE_REG0,
पूर्ण;

अटल पूर्णांक phy_axg_pcie_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा phy_axg_pcie_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = phy_घातer_on(priv->analog);
	अगर (ret != 0)
		वापस ret;

	regmap_update_bits(priv->regmap, MESON_PCIE_REG0,
			   MESON_PCIE_POWERDOWN, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक phy_axg_pcie_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा phy_axg_pcie_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = phy_घातer_off(priv->analog);
	अगर (ret != 0)
		वापस ret;

	regmap_update_bits(priv->regmap, MESON_PCIE_REG0,
			   MESON_PCIE_POWERDOWN, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक phy_axg_pcie_init(काष्ठा phy *phy)
अणु
	काष्ठा phy_axg_pcie_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = phy_init(priv->analog);
	अगर (ret != 0)
		वापस ret;

	regmap_ग_लिखो(priv->regmap, MESON_PCIE_REG0, MESON_PCIE_PHY_INIT);
	वापस reset_control_reset(priv->reset);
पूर्ण

अटल पूर्णांक phy_axg_pcie_निकास(काष्ठा phy *phy)
अणु
	काष्ठा phy_axg_pcie_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = phy_निकास(priv->analog);
	अगर (ret != 0)
		वापस ret;

	वापस reset_control_reset(priv->reset);
पूर्ण

अटल पूर्णांक phy_axg_pcie_reset(काष्ठा phy *phy)
अणु
	काष्ठा phy_axg_pcie_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret = 0;

	ret = phy_reset(priv->analog);
	अगर (ret != 0)
		जाओ out;

	ret = reset_control_निश्चित(priv->reset);
	अगर (ret != 0)
		जाओ out;
	udelay(MESON_PCIE_RESET_DELAY);

	ret = reset_control_deनिश्चित(priv->reset);
	अगर (ret != 0)
		जाओ out;
	udelay(MESON_PCIE_RESET_DELAY);

out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा phy_ops phy_axg_pcie_ops = अणु
	.init = phy_axg_pcie_init,
	.निकास = phy_axg_pcie_निकास,
	.घातer_on = phy_axg_pcie_घातer_on,
	.घातer_off = phy_axg_pcie_घातer_off,
	.reset = phy_axg_pcie_reset,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक phy_axg_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *pphy;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_axg_pcie_priv *priv;
	काष्ठा device_node *np = dev->of_node;
	व्योम __iomem *base;
	पूर्णांक ret;

	priv = devm_kदो_स्मृति(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->phy = devm_phy_create(dev, np, &phy_axg_pcie_ops);
	अगर (IS_ERR(priv->phy)) अणु
		ret = PTR_ERR(priv->phy);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to create PHY\n");
		वापस ret;
	पूर्ण

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	priv->regmap = devm_regmap_init_mmio(dev, base,
					     &phy_axg_pcie_regmap_conf);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	priv->reset = devm_reset_control_array_get_exclusive(dev);
	अगर (IS_ERR(priv->reset))
		वापस PTR_ERR(priv->reset);

	priv->analog = devm_phy_get(dev, "analog");
	अगर (IS_ERR(priv->analog))
		वापस PTR_ERR(priv->analog);

	phy_set_drvdata(priv->phy, priv);
	dev_set_drvdata(dev, priv);
	pphy = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(pphy);
पूर्ण

अटल स्थिर काष्ठा of_device_id phy_axg_pcie_of_match[] = अणु
	अणु
		.compatible = "amlogic,axg-pcie-phy",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, phy_axg_pcie_of_match);

अटल काष्ठा platक्रमm_driver phy_axg_pcie_driver = अणु
	.probe = phy_axg_pcie_probe,
	.driver = अणु
		.name = "phy-axg-pcie",
		.of_match_table = phy_axg_pcie_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(phy_axg_pcie_driver);

MODULE_AUTHOR("Remi Pommarel <repk@triplefau.lt>");
MODULE_DESCRIPTION("Amlogic AXG PCIE PHY driver");
MODULE_LICENSE("GPL v2");
