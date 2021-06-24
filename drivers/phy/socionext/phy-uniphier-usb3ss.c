<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * phy-uniphier-usb3ss.c - SS-PHY driver क्रम Socionext UniPhier USB3 controller
 * Copyright 2015-2018 Socionext Inc.
 * Author:
 *      Kunihiko Hayashi <hayashi.kunihiko@socionext.com>
 * Contributors:
 *      Motoya Tanigawa <tanigawa.motoya@socionext.com>
 *      Masami Hiramatsu <masami.hiramatsu@linaro.org>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>

#घोषणा SSPHY_TESTI		0x0
#घोषणा SSPHY_TESTO		0x4
#घोषणा TESTI_DAT_MASK		GENMASK(13, 6)
#घोषणा TESTI_ADR_MASK		GENMASK(5, 1)
#घोषणा TESTI_WR_EN		BIT(0)

#घोषणा PHY_F(regno, msb, lsb) अणु (regno), (msb), (lsb) पूर्ण

#घोषणा CDR_CPD_TRIM	PHY_F(7, 3, 0)	/* RxPLL अक्षरge pump current */
#घोषणा CDR_CPF_TRIM	PHY_F(8, 3, 0)	/* RxPLL अक्षरge pump current 2 */
#घोषणा TX_PLL_TRIM	PHY_F(9, 3, 0)	/* TxPLL अक्षरge pump current */
#घोषणा BGAP_TRIM	PHY_F(11, 3, 0)	/* Bandgap voltage */
#घोषणा CDR_TRIM	PHY_F(13, 6, 5)	/* Clock Data Recovery setting */
#घोषणा VCO_CTRL	PHY_F(26, 7, 4)	/* VCO control */
#घोषणा VCOPLL_CTRL	PHY_F(27, 2, 0)	/* TxPLL VCO tuning */
#घोषणा VCOPLL_CM	PHY_F(28, 1, 0)	/* TxPLL voltage */

#घोषणा MAX_PHY_PARAMS	7

काष्ठा uniphier_u3ssphy_param अणु
	काष्ठा अणु
		पूर्णांक reg_no;
		पूर्णांक msb;
		पूर्णांक lsb;
	पूर्ण field;
	u8 value;
पूर्ण;

काष्ठा uniphier_u3ssphy_priv अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा clk *clk, *clk_ext, *clk_parent, *clk_parent_gio;
	काष्ठा reset_control *rst, *rst_parent, *rst_parent_gio;
	काष्ठा regulator *vbus;
	स्थिर काष्ठा uniphier_u3ssphy_soc_data *data;
पूर्ण;

काष्ठा uniphier_u3ssphy_soc_data अणु
	bool is_legacy;
	पूर्णांक nparams;
	स्थिर काष्ठा uniphier_u3ssphy_param param[MAX_PHY_PARAMS];
पूर्ण;

अटल व्योम uniphier_u3ssphy_testio_ग_लिखो(काष्ठा uniphier_u3ssphy_priv *priv,
					  u32 data)
अणु
	/* need to पढ़ो TESTO twice after accessing TESTI */
	ग_लिखोl(data, priv->base + SSPHY_TESTI);
	पढ़ोl(priv->base + SSPHY_TESTO);
	पढ़ोl(priv->base + SSPHY_TESTO);
पूर्ण

अटल व्योम uniphier_u3ssphy_set_param(काष्ठा uniphier_u3ssphy_priv *priv,
				       स्थिर काष्ठा uniphier_u3ssphy_param *p)
अणु
	u32 val;
	u8 field_mask = GENMASK(p->field.msb, p->field.lsb);
	u8 data;

	/* पढ़ो previous data */
	val  = FIELD_PREP(TESTI_DAT_MASK, 1);
	val |= FIELD_PREP(TESTI_ADR_MASK, p->field.reg_no);
	uniphier_u3ssphy_testio_ग_लिखो(priv, val);
	val = पढ़ोl(priv->base + SSPHY_TESTO);

	/* update value */
	val &= ~FIELD_PREP(TESTI_DAT_MASK, field_mask);
	data = field_mask & (p->value << p->field.lsb);
	val  = FIELD_PREP(TESTI_DAT_MASK, data);
	val |= FIELD_PREP(TESTI_ADR_MASK, p->field.reg_no);
	uniphier_u3ssphy_testio_ग_लिखो(priv, val);
	uniphier_u3ssphy_testio_ग_लिखो(priv, val | TESTI_WR_EN);
	uniphier_u3ssphy_testio_ग_लिखो(priv, val);

	/* पढ़ो current data as dummy */
	val  = FIELD_PREP(TESTI_DAT_MASK, 1);
	val |= FIELD_PREP(TESTI_ADR_MASK, p->field.reg_no);
	uniphier_u3ssphy_testio_ग_लिखो(priv, val);
	पढ़ोl(priv->base + SSPHY_TESTO);
पूर्ण

अटल पूर्णांक uniphier_u3ssphy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_u3ssphy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->clk_ext);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		जाओ out_clk_ext_disable;

	ret = reset_control_deनिश्चित(priv->rst);
	अगर (ret)
		जाओ out_clk_disable;

	अगर (priv->vbus) अणु
		ret = regulator_enable(priv->vbus);
		अगर (ret)
			जाओ out_rst_निश्चित;
	पूर्ण

	वापस 0;

out_rst_निश्चित:
	reset_control_निश्चित(priv->rst);
out_clk_disable:
	clk_disable_unprepare(priv->clk);
out_clk_ext_disable:
	clk_disable_unprepare(priv->clk_ext);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_u3ssphy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_u3ssphy_priv *priv = phy_get_drvdata(phy);

	अगर (priv->vbus)
		regulator_disable(priv->vbus);

	reset_control_निश्चित(priv->rst);
	clk_disable_unprepare(priv->clk);
	clk_disable_unprepare(priv->clk_ext);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_u3ssphy_init(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_u3ssphy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक i, ret;

	ret = clk_prepare_enable(priv->clk_parent);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(priv->clk_parent_gio);
	अगर (ret)
		जाओ out_clk_disable;

	ret = reset_control_deनिश्चित(priv->rst_parent);
	अगर (ret)
		जाओ out_clk_gio_disable;

	ret = reset_control_deनिश्चित(priv->rst_parent_gio);
	अगर (ret)
		जाओ out_rst_निश्चित;

	अगर (priv->data->is_legacy)
		वापस 0;

	क्रम (i = 0; i < priv->data->nparams; i++)
		uniphier_u3ssphy_set_param(priv, &priv->data->param[i]);

	वापस 0;

out_rst_निश्चित:
	reset_control_निश्चित(priv->rst_parent);
out_clk_gio_disable:
	clk_disable_unprepare(priv->clk_parent_gio);
out_clk_disable:
	clk_disable_unprepare(priv->clk_parent);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_u3ssphy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_u3ssphy_priv *priv = phy_get_drvdata(phy);

	reset_control_निश्चित(priv->rst_parent_gio);
	reset_control_निश्चित(priv->rst_parent);
	clk_disable_unprepare(priv->clk_parent_gio);
	clk_disable_unprepare(priv->clk_parent);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops uniphier_u3ssphy_ops = अणु
	.init           = uniphier_u3ssphy_init,
	.निकास           = uniphier_u3ssphy_निकास,
	.घातer_on       = uniphier_u3ssphy_घातer_on,
	.घातer_off      = uniphier_u3ssphy_घातer_off,
	.owner          = THIS_MODULE,
पूर्ण;

अटल पूर्णांक uniphier_u3ssphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uniphier_u3ssphy_priv *priv;
	काष्ठा phy_provider *phy_provider;
	काष्ठा phy *phy;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	priv->data = of_device_get_match_data(dev);
	अगर (WARN_ON(!priv->data ||
		    priv->data->nparams > MAX_PHY_PARAMS))
		वापस -EINVAL;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	अगर (!priv->data->is_legacy) अणु
		priv->clk = devm_clk_get(dev, "phy");
		अगर (IS_ERR(priv->clk))
			वापस PTR_ERR(priv->clk);

		priv->clk_ext = devm_clk_get_optional(dev, "phy-ext");
		अगर (IS_ERR(priv->clk_ext))
			वापस PTR_ERR(priv->clk_ext);

		priv->rst = devm_reset_control_get_shared(dev, "phy");
		अगर (IS_ERR(priv->rst))
			वापस PTR_ERR(priv->rst);
	पूर्ण अन्यथा अणु
		priv->clk_parent_gio = devm_clk_get(dev, "gio");
		अगर (IS_ERR(priv->clk_parent_gio))
			वापस PTR_ERR(priv->clk_parent_gio);

		priv->rst_parent_gio =
			devm_reset_control_get_shared(dev, "gio");
		अगर (IS_ERR(priv->rst_parent_gio))
			वापस PTR_ERR(priv->rst_parent_gio);
	पूर्ण

	priv->clk_parent = devm_clk_get(dev, "link");
	अगर (IS_ERR(priv->clk_parent))
		वापस PTR_ERR(priv->clk_parent);

	priv->rst_parent = devm_reset_control_get_shared(dev, "link");
	अगर (IS_ERR(priv->rst_parent))
		वापस PTR_ERR(priv->rst_parent);

	priv->vbus = devm_regulator_get_optional(dev, "vbus");
	अगर (IS_ERR(priv->vbus)) अणु
		अगर (PTR_ERR(priv->vbus) == -EPROBE_DEFER)
			वापस PTR_ERR(priv->vbus);
		priv->vbus = शून्य;
	पूर्ण

	phy = devm_phy_create(dev, dev->of_node, &uniphier_u3ssphy_ops);
	अगर (IS_ERR(phy))
		वापस PTR_ERR(phy);

	phy_set_drvdata(phy, priv);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा uniphier_u3ssphy_soc_data uniphier_pro4_data = अणु
	.is_legacy = true,
पूर्ण;

अटल स्थिर काष्ठा uniphier_u3ssphy_soc_data uniphier_pxs2_data = अणु
	.is_legacy = false,
	.nparams = 7,
	.param = अणु
		अणु CDR_CPD_TRIM, 10 पूर्ण,
		अणु CDR_CPF_TRIM, 3 पूर्ण,
		अणु TX_PLL_TRIM, 5 पूर्ण,
		अणु BGAP_TRIM, 9 पूर्ण,
		अणु CDR_TRIM, 2 पूर्ण,
		अणु VCOPLL_CTRL, 7 पूर्ण,
		अणु VCOPLL_CM, 1 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा uniphier_u3ssphy_soc_data uniphier_ld20_data = अणु
	.is_legacy = false,
	.nparams = 3,
	.param = अणु
		अणु CDR_CPD_TRIM, 6 पूर्ण,
		अणु CDR_TRIM, 2 पूर्ण,
		अणु VCO_CTRL, 5 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id uniphier_u3ssphy_match[] = अणु
	अणु
		.compatible = "socionext,uniphier-pro4-usb3-ssphy",
		.data = &uniphier_pro4_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pro5-usb3-ssphy",
		.data = &uniphier_pro4_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs2-usb3-ssphy",
		.data = &uniphier_pxs2_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld20-usb3-ssphy",
		.data = &uniphier_ld20_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs3-usb3-ssphy",
		.data = &uniphier_ld20_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_u3ssphy_match);

अटल काष्ठा platक्रमm_driver uniphier_u3ssphy_driver = अणु
	.probe = uniphier_u3ssphy_probe,
	.driver	= अणु
		.name = "uniphier-usb3-ssphy",
		.of_match_table	= uniphier_u3ssphy_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(uniphier_u3ssphy_driver);

MODULE_AUTHOR("Kunihiko Hayashi <hayashi.kunihiko@socionext.com>");
MODULE_DESCRIPTION("UniPhier SS-PHY driver for USB3 controller");
MODULE_LICENSE("GPL v2");
