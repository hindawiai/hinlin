<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * phy-uniphier-ahci.c - PHY driver क्रम UniPhier AHCI controller
 * Copyright 2016-2020, Socionext Inc.
 * Author: Kunihiko Hayashi <hayashi.kunihiko@socionext.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

काष्ठा uniphier_ahciphy_priv अणु
	काष्ठा device *dev;
	व्योम __iomem  *base;
	काष्ठा clk *clk, *clk_parent;
	काष्ठा reset_control *rst, *rst_parent;
	स्थिर काष्ठा uniphier_ahciphy_soc_data *data;
पूर्ण;

काष्ठा uniphier_ahciphy_soc_data अणु
	पूर्णांक (*init)(काष्ठा uniphier_ahciphy_priv *priv);
	पूर्णांक (*घातer_on)(काष्ठा uniphier_ahciphy_priv *priv);
	पूर्णांक (*घातer_off)(काष्ठा uniphier_ahciphy_priv *priv);
	bool is_पढ़ोy_high;
	bool is_phy_clk;
पूर्ण;

/* क्रम PXs2/PXs3 */
#घोषणा CKCTRL				0x0
#घोषणा CKCTRL_P0_READY			BIT(15)
#घोषणा CKCTRL_P0_RESET			BIT(10)
#घोषणा CKCTRL_REF_SSP_EN		BIT(9)
#घोषणा TXCTRL0				0x4
#घोषणा TXCTRL0_AMP_G3_MASK		GENMASK(22, 16)
#घोषणा TXCTRL0_AMP_G2_MASK		GENMASK(14, 8)
#घोषणा TXCTRL0_AMP_G1_MASK		GENMASK(6, 0)
#घोषणा TXCTRL1				0x8
#घोषणा TXCTRL1_DEEMPH_G3_MASK		GENMASK(21, 16)
#घोषणा TXCTRL1_DEEMPH_G2_MASK		GENMASK(13, 8)
#घोषणा TXCTRL1_DEEMPH_G1_MASK		GENMASK(5, 0)
#घोषणा RXCTRL				0xc
#घोषणा RXCTRL_LOS_LVL_MASK		GENMASK(20, 16)
#घोषणा RXCTRL_LOS_BIAS_MASK		GENMASK(10, 8)
#घोषणा RXCTRL_RX_EQ_MASK		GENMASK(2, 0)

अटल व्योम uniphier_ahciphy_pxs2_enable(काष्ठा uniphier_ahciphy_priv *priv,
					 bool enable)
अणु
	u32 val;

	val = पढ़ोl(priv->base + CKCTRL);

	अगर (enable) अणु
		val |= CKCTRL_REF_SSP_EN;
		ग_लिखोl(val, priv->base + CKCTRL);
		val &= ~CKCTRL_P0_RESET;
		ग_लिखोl(val, priv->base + CKCTRL);
	पूर्ण अन्यथा अणु
		val |= CKCTRL_P0_RESET;
		ग_लिखोl(val, priv->base + CKCTRL);
		val &= ~CKCTRL_REF_SSP_EN;
		ग_लिखोl(val, priv->base + CKCTRL);
	पूर्ण
पूर्ण

अटल पूर्णांक uniphier_ahciphy_pxs2_घातer_on(काष्ठा uniphier_ahciphy_priv *priv)
अणु
	पूर्णांक ret;
	u32 val;

	uniphier_ahciphy_pxs2_enable(priv, true);

	/* रुको until PLL is पढ़ोy */
	अगर (priv->data->is_पढ़ोy_high)
		ret = पढ़ोl_poll_समयout(priv->base + CKCTRL, val,
					 (val & CKCTRL_P0_READY), 200, 400);
	अन्यथा
		ret = पढ़ोl_poll_समयout(priv->base + CKCTRL, val,
					 !(val & CKCTRL_P0_READY), 200, 400);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to check whether PHY PLL is ready\n");
		uniphier_ahciphy_pxs2_enable(priv, false);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_ahciphy_pxs2_घातer_off(काष्ठा uniphier_ahciphy_priv *priv)
अणु
	uniphier_ahciphy_pxs2_enable(priv, false);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_ahciphy_pxs3_init(काष्ठा uniphier_ahciphy_priv *priv)
अणु
	पूर्णांक i;
	u32 val;

	/* setup port parameter */
	val = पढ़ोl(priv->base + TXCTRL0);
	val &= ~TXCTRL0_AMP_G3_MASK;
	val |= FIELD_PREP(TXCTRL0_AMP_G3_MASK, 0x73);
	val &= ~TXCTRL0_AMP_G2_MASK;
	val |= FIELD_PREP(TXCTRL0_AMP_G2_MASK, 0x46);
	val &= ~TXCTRL0_AMP_G1_MASK;
	val |= FIELD_PREP(TXCTRL0_AMP_G1_MASK, 0x42);
	ग_लिखोl(val, priv->base + TXCTRL0);

	val = पढ़ोl(priv->base + TXCTRL1);
	val &= ~TXCTRL1_DEEMPH_G3_MASK;
	val |= FIELD_PREP(TXCTRL1_DEEMPH_G3_MASK, 0x23);
	val &= ~TXCTRL1_DEEMPH_G2_MASK;
	val |= FIELD_PREP(TXCTRL1_DEEMPH_G2_MASK, 0x05);
	val &= ~TXCTRL1_DEEMPH_G1_MASK;
	val |= FIELD_PREP(TXCTRL1_DEEMPH_G1_MASK, 0x05);

	val = पढ़ोl(priv->base + RXCTRL);
	val &= ~RXCTRL_LOS_LVL_MASK;
	val |= FIELD_PREP(RXCTRL_LOS_LVL_MASK, 0x9);
	val &= ~RXCTRL_LOS_BIAS_MASK;
	val |= FIELD_PREP(RXCTRL_LOS_BIAS_MASK, 0x2);
	val &= ~RXCTRL_RX_EQ_MASK;
	val |= FIELD_PREP(RXCTRL_RX_EQ_MASK, 0x1);

	/* dummy पढ़ो 25 बार to make a रुको समय क्रम the phy to stabilize */
	क्रम (i = 0; i < 25; i++)
		पढ़ोl(priv->base + CKCTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_ahciphy_init(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_ahciphy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->clk_parent);
	अगर (ret)
		वापस ret;

	ret = reset_control_deनिश्चित(priv->rst_parent);
	अगर (ret)
		जाओ out_clk_disable;

	अगर (priv->data->init) अणु
		ret = priv->data->init(priv);
		अगर (ret)
			जाओ out_rst_निश्चित;
	पूर्ण

	वापस 0;

out_rst_निश्चित:
	reset_control_निश्चित(priv->rst_parent);
out_clk_disable:
	clk_disable_unprepare(priv->clk_parent);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_ahciphy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_ahciphy_priv *priv = phy_get_drvdata(phy);

	reset_control_निश्चित(priv->rst_parent);
	clk_disable_unprepare(priv->clk_parent);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_ahciphy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_ahciphy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret = 0;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	ret = reset_control_deनिश्चित(priv->rst);
	अगर (ret)
		जाओ out_clk_disable;

	अगर (priv->data->घातer_on) अणु
		ret = priv->data->घातer_on(priv);
		अगर (ret)
			जाओ out_reset_निश्चित;
	पूर्ण

	वापस 0;

out_reset_निश्चित:
	reset_control_निश्चित(priv->rst);
out_clk_disable:
	clk_disable_unprepare(priv->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_ahciphy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_ahciphy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret = 0;

	अगर (priv->data->घातer_off)
		ret = priv->data->घातer_off(priv);

	reset_control_निश्चित(priv->rst);
	clk_disable_unprepare(priv->clk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा phy_ops uniphier_ahciphy_ops = अणु
	.init  = uniphier_ahciphy_init,
	.निकास  = uniphier_ahciphy_निकास,
	.घातer_on  = uniphier_ahciphy_घातer_on,
	.घातer_off = uniphier_ahciphy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक uniphier_ahciphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uniphier_ahciphy_priv *priv;
	काष्ठा phy *phy;
	काष्ठा phy_provider *phy_provider;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	priv->data = of_device_get_match_data(dev);
	अगर (WARN_ON(!priv->data))
		वापस -EINVAL;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->clk_parent = devm_clk_get(dev, "link");
	अगर (IS_ERR(priv->clk_parent))
		वापस PTR_ERR(priv->clk_parent);

	अगर (priv->data->is_phy_clk) अणु
		priv->clk = devm_clk_get(dev, "phy");
		अगर (IS_ERR(priv->clk))
			वापस PTR_ERR(priv->clk);
	पूर्ण

	priv->rst_parent = devm_reset_control_get_shared(dev, "link");
	अगर (IS_ERR(priv->rst_parent))
		वापस PTR_ERR(priv->rst_parent);

	priv->rst = devm_reset_control_get_shared(dev, "phy");
	अगर (IS_ERR(priv->rst))
		वापस PTR_ERR(priv->rst);

	phy = devm_phy_create(dev, dev->of_node, &uniphier_ahciphy_ops);
	अगर (IS_ERR(phy)) अणु
		dev_err(dev, "failed to create phy\n");
		वापस PTR_ERR(phy);
	पूर्ण

	phy_set_drvdata(phy, priv);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider))
		वापस PTR_ERR(phy_provider);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uniphier_ahciphy_soc_data uniphier_pxs2_data = अणु
	.घातer_on  = uniphier_ahciphy_pxs2_घातer_on,
	.घातer_off = uniphier_ahciphy_pxs2_घातer_off,
	.is_पढ़ोy_high = false,
	.is_phy_clk = false,
पूर्ण;

अटल स्थिर काष्ठा uniphier_ahciphy_soc_data uniphier_pxs3_data = अणु
	.init      = uniphier_ahciphy_pxs3_init,
	.घातer_on  = uniphier_ahciphy_pxs2_घातer_on,
	.घातer_off = uniphier_ahciphy_pxs2_घातer_off,
	.is_पढ़ोy_high = true,
	.is_phy_clk = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id uniphier_ahciphy_match[] = अणु
	अणु
		.compatible = "socionext,uniphier-pxs2-ahci-phy",
		.data = &uniphier_pxs2_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs3-ahci-phy",
		.data = &uniphier_pxs3_data,
	पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_ahciphy_match);

अटल काष्ठा platक्रमm_driver uniphier_ahciphy_driver = अणु
	.probe = uniphier_ahciphy_probe,
	.driver = अणु
		.name = "uniphier-ahci-phy",
		.of_match_table = uniphier_ahciphy_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_ahciphy_driver);

MODULE_AUTHOR("Kunihiko Hayashi <hayashi.kunihiko@socionext.com>");
MODULE_DESCRIPTION("UniPhier PHY driver for AHCI controller");
MODULE_LICENSE("GPL v2");
