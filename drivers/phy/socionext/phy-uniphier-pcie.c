<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * phy-uniphier-pcie.c - PHY driver क्रम UniPhier PCIe controller
 * Copyright 2018, Socionext Inc.
 * Author: Kunihiko Hayashi <hayashi.kunihiko@socionext.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/resource.h>

/* PHY */
#घोषणा PCL_PHY_CLKCTRL		0x0000
#घोषणा PORT_SEL_MASK		GENMASK(11, 9)
#घोषणा PORT_SEL_1		FIELD_PREP(PORT_SEL_MASK, 1)

#घोषणा PCL_PHY_TEST_I		0x2000
#घोषणा PCL_PHY_TEST_O		0x2004
#घोषणा TESTI_DAT_MASK		GENMASK(13, 6)
#घोषणा TESTI_ADR_MASK		GENMASK(5, 1)
#घोषणा TESTI_WR_EN		BIT(0)

#घोषणा PCL_PHY_RESET		0x200c
#घोषणा PCL_PHY_RESET_N_MNMODE	BIT(8)	/* =1:manual */
#घोषणा PCL_PHY_RESET_N		BIT(0)	/* =1:deasssert */

/* SG */
#घोषणा SG_USBPCIESEL		0x590
#घोषणा SG_USBPCIESEL_PCIE	BIT(0)

#घोषणा PCL_PHY_R00		0
#घोषणा   RX_EQ_ADJ_EN		BIT(3)		/* enable क्रम EQ adjusपंचांगent */
#घोषणा PCL_PHY_R06		6
#घोषणा   RX_EQ_ADJ		GENMASK(5, 0)	/* EQ adjusपंचांगent value */
#घोषणा   RX_EQ_ADJ_VAL		0
#घोषणा PCL_PHY_R26		26
#घोषणा   VCO_CTRL		GENMASK(7, 4)	/* Tx VCO adjusपंचांगent value */
#घोषणा   VCO_CTRL_INIT_VAL	5

काष्ठा uniphier_pciephy_priv अणु
	व्योम __iomem *base;
	काष्ठा device *dev;
	काष्ठा clk *clk, *clk_gio;
	काष्ठा reset_control *rst, *rst_gio;
	स्थिर काष्ठा uniphier_pciephy_soc_data *data;
पूर्ण;

काष्ठा uniphier_pciephy_soc_data अणु
	bool is_legacy;
	व्योम (*set_phymode)(काष्ठा regmap *regmap);
पूर्ण;

अटल व्योम uniphier_pciephy_testio_ग_लिखो(काष्ठा uniphier_pciephy_priv *priv,
					  u32 data)
अणु
	/* need to पढ़ो TESTO twice after accessing TESTI */
	ग_लिखोl(data, priv->base + PCL_PHY_TEST_I);
	पढ़ोl(priv->base + PCL_PHY_TEST_O);
	पढ़ोl(priv->base + PCL_PHY_TEST_O);
पूर्ण

अटल व्योम uniphier_pciephy_set_param(काष्ठा uniphier_pciephy_priv *priv,
				       u32 reg, u32 mask, u32 param)
अणु
	u32 val;

	/* पढ़ो previous data */
	val  = FIELD_PREP(TESTI_DAT_MASK, 1);
	val |= FIELD_PREP(TESTI_ADR_MASK, reg);
	uniphier_pciephy_testio_ग_लिखो(priv, val);
	val = पढ़ोl(priv->base + PCL_PHY_TEST_O);

	/* update value */
	val &= ~FIELD_PREP(TESTI_DAT_MASK, mask);
	val  = FIELD_PREP(TESTI_DAT_MASK, mask & param);
	val |= FIELD_PREP(TESTI_ADR_MASK, reg);
	uniphier_pciephy_testio_ग_लिखो(priv, val);
	uniphier_pciephy_testio_ग_लिखो(priv, val | TESTI_WR_EN);
	uniphier_pciephy_testio_ग_लिखो(priv, val);

	/* पढ़ो current data as dummy */
	val  = FIELD_PREP(TESTI_DAT_MASK, 1);
	val |= FIELD_PREP(TESTI_ADR_MASK, reg);
	uniphier_pciephy_testio_ग_लिखो(priv, val);
	पढ़ोl(priv->base + PCL_PHY_TEST_O);
पूर्ण

अटल व्योम uniphier_pciephy_निश्चित(काष्ठा uniphier_pciephy_priv *priv)
अणु
	u32 val;

	val = पढ़ोl(priv->base + PCL_PHY_RESET);
	val &= ~PCL_PHY_RESET_N;
	val |= PCL_PHY_RESET_N_MNMODE;
	ग_लिखोl(val, priv->base + PCL_PHY_RESET);
पूर्ण

अटल व्योम uniphier_pciephy_deनिश्चित(काष्ठा uniphier_pciephy_priv *priv)
अणु
	u32 val;

	val = पढ़ोl(priv->base + PCL_PHY_RESET);
	val |= PCL_PHY_RESET_N_MNMODE | PCL_PHY_RESET_N;
	ग_लिखोl(val, priv->base + PCL_PHY_RESET);
पूर्ण

अटल पूर्णांक uniphier_pciephy_init(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_pciephy_priv *priv = phy_get_drvdata(phy);
	u32 val;
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(priv->clk_gio);
	अगर (ret)
		जाओ out_clk_disable;

	ret = reset_control_deनिश्चित(priv->rst);
	अगर (ret)
		जाओ out_clk_gio_disable;

	ret = reset_control_deनिश्चित(priv->rst_gio);
	अगर (ret)
		जाओ out_rst_निश्चित;

	/* support only 1 port */
	val = पढ़ोl(priv->base + PCL_PHY_CLKCTRL);
	val &= ~PORT_SEL_MASK;
	val |= PORT_SEL_1;
	ग_लिखोl(val, priv->base + PCL_PHY_CLKCTRL);

	/* legacy controller करोesn't have phy_reset and parameters */
	अगर (priv->data->is_legacy)
		वापस 0;

	uniphier_pciephy_set_param(priv, PCL_PHY_R00,
				   RX_EQ_ADJ_EN, RX_EQ_ADJ_EN);
	uniphier_pciephy_set_param(priv, PCL_PHY_R06, RX_EQ_ADJ,
				   FIELD_PREP(RX_EQ_ADJ, RX_EQ_ADJ_VAL));
	uniphier_pciephy_set_param(priv, PCL_PHY_R26, VCO_CTRL,
				   FIELD_PREP(VCO_CTRL, VCO_CTRL_INIT_VAL));
	usleep_range(1, 10);

	uniphier_pciephy_deनिश्चित(priv);
	usleep_range(1, 10);

	वापस 0;

out_rst_निश्चित:
	reset_control_निश्चित(priv->rst);
out_clk_gio_disable:
	clk_disable_unprepare(priv->clk_gio);
out_clk_disable:
	clk_disable_unprepare(priv->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_pciephy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_pciephy_priv *priv = phy_get_drvdata(phy);

	अगर (!priv->data->is_legacy)
		uniphier_pciephy_निश्चित(priv);
	reset_control_निश्चित(priv->rst_gio);
	reset_control_निश्चित(priv->rst);
	clk_disable_unprepare(priv->clk_gio);
	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops uniphier_pciephy_ops = अणु
	.init  = uniphier_pciephy_init,
	.निकास  = uniphier_pciephy_निकास,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक uniphier_pciephy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uniphier_pciephy_priv *priv;
	काष्ठा phy_provider *phy_provider;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regmap *regmap;
	काष्ठा phy *phy;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->data = of_device_get_match_data(dev);
	अगर (WARN_ON(!priv->data))
		वापस -EINVAL;

	priv->dev = dev;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	अगर (priv->data->is_legacy) अणु
		priv->clk_gio = devm_clk_get(dev, "gio");
		अगर (IS_ERR(priv->clk_gio))
			वापस PTR_ERR(priv->clk_gio);

		priv->rst_gio =
			devm_reset_control_get_shared(dev, "gio");
		अगर (IS_ERR(priv->rst_gio))
			वापस PTR_ERR(priv->rst_gio);

		priv->clk = devm_clk_get(dev, "link");
		अगर (IS_ERR(priv->clk))
			वापस PTR_ERR(priv->clk);

		priv->rst = devm_reset_control_get_shared(dev, "link");
		अगर (IS_ERR(priv->rst))
			वापस PTR_ERR(priv->rst);
	पूर्ण अन्यथा अणु
		priv->clk = devm_clk_get(dev, शून्य);
		अगर (IS_ERR(priv->clk))
			वापस PTR_ERR(priv->clk);

		priv->rst = devm_reset_control_get_shared(dev, शून्य);
		अगर (IS_ERR(priv->rst))
			वापस PTR_ERR(priv->rst);
	पूर्ण

	phy = devm_phy_create(dev, dev->of_node, &uniphier_pciephy_ops);
	अगर (IS_ERR(phy))
		वापस PTR_ERR(phy);

	regmap = syscon_regmap_lookup_by_phandle(dev->of_node,
						 "socionext,syscon");
	अगर (!IS_ERR(regmap) && priv->data->set_phymode)
		priv->data->set_phymode(regmap);

	phy_set_drvdata(phy, priv);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल व्योम uniphier_pciephy_ld20_seपंचांगode(काष्ठा regmap *regmap)
अणु
	regmap_update_bits(regmap, SG_USBPCIESEL,
			   SG_USBPCIESEL_PCIE, SG_USBPCIESEL_PCIE);
पूर्ण

अटल स्थिर काष्ठा uniphier_pciephy_soc_data uniphier_pro5_data = अणु
	.is_legacy = true,
पूर्ण;

अटल स्थिर काष्ठा uniphier_pciephy_soc_data uniphier_ld20_data = अणु
	.is_legacy = false,
	.set_phymode = uniphier_pciephy_ld20_seपंचांगode,
पूर्ण;

अटल स्थिर काष्ठा uniphier_pciephy_soc_data uniphier_pxs3_data = अणु
	.is_legacy = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id uniphier_pciephy_match[] = अणु
	अणु
		.compatible = "socionext,uniphier-pro5-pcie-phy",
		.data = &uniphier_pro5_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld20-pcie-phy",
		.data = &uniphier_ld20_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs3-pcie-phy",
		.data = &uniphier_pxs3_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_pciephy_match);

अटल काष्ठा platक्रमm_driver uniphier_pciephy_driver = अणु
	.probe = uniphier_pciephy_probe,
	.driver = अणु
		.name = "uniphier-pcie-phy",
		.of_match_table = uniphier_pciephy_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_pciephy_driver);

MODULE_AUTHOR("Kunihiko Hayashi <hayashi.kunihiko@socionext.com>");
MODULE_DESCRIPTION("UniPhier PHY driver for PCIe controller");
MODULE_LICENSE("GPL v2");
