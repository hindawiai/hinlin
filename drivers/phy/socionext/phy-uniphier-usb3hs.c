<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * phy-uniphier-usb3hs.c - HS-PHY driver क्रम Socionext UniPhier USB3 controller
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
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#घोषणा HSPHY_CFG0		0x0
#घोषणा HSPHY_CFG0_HS_I_MASK	GENMASK(31, 28)
#घोषणा HSPHY_CFG0_HSDISC_MASK	GENMASK(27, 26)
#घोषणा HSPHY_CFG0_SWING_MASK	GENMASK(17, 16)
#घोषणा HSPHY_CFG0_SEL_T_MASK	GENMASK(15, 12)
#घोषणा HSPHY_CFG0_RTERM_MASK	GENMASK(7, 6)
#घोषणा HSPHY_CFG0_TRIMMASK	(HSPHY_CFG0_HS_I_MASK \
				 | HSPHY_CFG0_SEL_T_MASK \
				 | HSPHY_CFG0_RTERM_MASK)

#घोषणा HSPHY_CFG1		0x4
#घोषणा HSPHY_CFG1_DAT_EN	BIT(29)
#घोषणा HSPHY_CFG1_ADR_EN	BIT(28)
#घोषणा HSPHY_CFG1_ADR_MASK	GENMASK(27, 16)
#घोषणा HSPHY_CFG1_DAT_MASK	GENMASK(23, 16)

#घोषणा PHY_F(regno, msb, lsb) अणु (regno), (msb), (lsb) पूर्ण

#घोषणा RX_CHK_SYNC	PHY_F(0, 5, 5)	/* RX sync mode */
#घोषणा RX_SYNC_SEL	PHY_F(1, 1, 0)	/* RX sync length */
#घोषणा LS_SLEW		PHY_F(10, 6, 6)	/* LS mode slew rate */
#घोषणा FS_LS_DRV	PHY_F(10, 5, 5)	/* FS/LS slew rate */

#घोषणा MAX_PHY_PARAMS	4

काष्ठा uniphier_u3hsphy_param अणु
	काष्ठा अणु
		पूर्णांक reg_no;
		पूर्णांक msb;
		पूर्णांक lsb;
	पूर्ण field;
	u8 value;
पूर्ण;

काष्ठा uniphier_u3hsphy_trim_param अणु
	अचिन्हित पूर्णांक rterm;
	अचिन्हित पूर्णांक sel_t;
	अचिन्हित पूर्णांक hs_i;
पूर्ण;

#घोषणा trim_param_is_valid(p)	((p)->rterm || (p)->sel_t || (p)->hs_i)

काष्ठा uniphier_u3hsphy_priv अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा clk *clk, *clk_parent, *clk_ext, *clk_parent_gio;
	काष्ठा reset_control *rst, *rst_parent, *rst_parent_gio;
	काष्ठा regulator *vbus;
	स्थिर काष्ठा uniphier_u3hsphy_soc_data *data;
पूर्ण;

काष्ठा uniphier_u3hsphy_soc_data अणु
	bool is_legacy;
	पूर्णांक nparams;
	स्थिर काष्ठा uniphier_u3hsphy_param param[MAX_PHY_PARAMS];
	u32 config0;
	u32 config1;
	व्योम (*trim_func)(काष्ठा uniphier_u3hsphy_priv *priv, u32 *pconfig,
			  काष्ठा uniphier_u3hsphy_trim_param *pt);
पूर्ण;

अटल व्योम uniphier_u3hsphy_trim_ld20(काष्ठा uniphier_u3hsphy_priv *priv,
				       u32 *pconfig,
				       काष्ठा uniphier_u3hsphy_trim_param *pt)
अणु
	*pconfig &= ~HSPHY_CFG0_RTERM_MASK;
	*pconfig |= FIELD_PREP(HSPHY_CFG0_RTERM_MASK, pt->rterm);

	*pconfig &= ~HSPHY_CFG0_SEL_T_MASK;
	*pconfig |= FIELD_PREP(HSPHY_CFG0_SEL_T_MASK, pt->sel_t);

	*pconfig &= ~HSPHY_CFG0_HS_I_MASK;
	*pconfig |= FIELD_PREP(HSPHY_CFG0_HS_I_MASK,  pt->hs_i);
पूर्ण

अटल पूर्णांक uniphier_u3hsphy_get_nvparam(काष्ठा uniphier_u3hsphy_priv *priv,
					स्थिर अक्षर *name, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा nvmem_cell *cell;
	u8 *buf;

	cell = devm_nvmem_cell_get(priv->dev, name);
	अगर (IS_ERR(cell))
		वापस PTR_ERR(cell);

	buf = nvmem_cell_पढ़ो(cell, शून्य);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	*val = *buf;

	kमुक्त(buf);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_u3hsphy_get_nvparams(काष्ठा uniphier_u3hsphy_priv *priv,
					 काष्ठा uniphier_u3hsphy_trim_param *pt)
अणु
	पूर्णांक ret;

	ret = uniphier_u3hsphy_get_nvparam(priv, "rterm", &pt->rterm);
	अगर (ret)
		वापस ret;

	ret = uniphier_u3hsphy_get_nvparam(priv, "sel_t", &pt->sel_t);
	अगर (ret)
		वापस ret;

	ret = uniphier_u3hsphy_get_nvparam(priv, "hs_i", &pt->hs_i);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_u3hsphy_update_config(काष्ठा uniphier_u3hsphy_priv *priv,
					  u32 *pconfig)
अणु
	काष्ठा uniphier_u3hsphy_trim_param trim;
	पूर्णांक ret, trimmed = 0;

	अगर (priv->data->trim_func) अणु
		ret = uniphier_u3hsphy_get_nvparams(priv, &trim);
		अगर (ret == -EPROBE_DEFER)
			वापस ret;

		/*
		 * call trim_func only when trimming parameters that aren't
		 * all-zero can be acquired. All-zero parameters mean nothing
		 * has been written to nvmem.
		 */
		अगर (!ret && trim_param_is_valid(&trim)) अणु
			priv->data->trim_func(priv, pconfig, &trim);
			trimmed = 1;
		पूर्ण अन्यथा अणु
			dev_dbg(priv->dev, "can't get parameter from nvmem\n");
		पूर्ण
	पूर्ण

	/* use शेष parameters without trimming values */
	अगर (!trimmed) अणु
		*pconfig &= ~HSPHY_CFG0_HSDISC_MASK;
		*pconfig |= FIELD_PREP(HSPHY_CFG0_HSDISC_MASK, 3);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम uniphier_u3hsphy_set_param(काष्ठा uniphier_u3hsphy_priv *priv,
				       स्थिर काष्ठा uniphier_u3hsphy_param *p)
अणु
	u32 val;
	u32 field_mask = GENMASK(p->field.msb, p->field.lsb);
	u8 data;

	val = पढ़ोl(priv->base + HSPHY_CFG1);
	val &= ~HSPHY_CFG1_ADR_MASK;
	val |= FIELD_PREP(HSPHY_CFG1_ADR_MASK, p->field.reg_no)
		| HSPHY_CFG1_ADR_EN;
	ग_लिखोl(val, priv->base + HSPHY_CFG1);

	val = पढ़ोl(priv->base + HSPHY_CFG1);
	val &= ~HSPHY_CFG1_ADR_EN;
	ग_लिखोl(val, priv->base + HSPHY_CFG1);

	val = पढ़ोl(priv->base + HSPHY_CFG1);
	val &= ~FIELD_PREP(HSPHY_CFG1_DAT_MASK, field_mask);
	data = field_mask & (p->value << p->field.lsb);
	val |=  FIELD_PREP(HSPHY_CFG1_DAT_MASK, data) | HSPHY_CFG1_DAT_EN;
	ग_लिखोl(val, priv->base + HSPHY_CFG1);

	val = पढ़ोl(priv->base + HSPHY_CFG1);
	val &= ~HSPHY_CFG1_DAT_EN;
	ग_लिखोl(val, priv->base + HSPHY_CFG1);
पूर्ण

अटल पूर्णांक uniphier_u3hsphy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_u3hsphy_priv *priv = phy_get_drvdata(phy);
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

अटल पूर्णांक uniphier_u3hsphy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_u3hsphy_priv *priv = phy_get_drvdata(phy);

	अगर (priv->vbus)
		regulator_disable(priv->vbus);

	reset_control_निश्चित(priv->rst);
	clk_disable_unprepare(priv->clk);
	clk_disable_unprepare(priv->clk_ext);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_u3hsphy_init(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_u3hsphy_priv *priv = phy_get_drvdata(phy);
	u32 config0, config1;
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

	अगर ((priv->data->is_legacy)
	    || (!priv->data->config0 && !priv->data->config1))
		वापस 0;

	config0 = priv->data->config0;
	config1 = priv->data->config1;

	ret = uniphier_u3hsphy_update_config(priv, &config0);
	अगर (ret)
		जाओ out_rst_निश्चित;

	ग_लिखोl(config0, priv->base + HSPHY_CFG0);
	ग_लिखोl(config1, priv->base + HSPHY_CFG1);

	क्रम (i = 0; i < priv->data->nparams; i++)
		uniphier_u3hsphy_set_param(priv, &priv->data->param[i]);

	वापस 0;

out_rst_निश्चित:
	reset_control_निश्चित(priv->rst_parent);
out_clk_gio_disable:
	clk_disable_unprepare(priv->clk_parent_gio);
out_clk_disable:
	clk_disable_unprepare(priv->clk_parent);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_u3hsphy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_u3hsphy_priv *priv = phy_get_drvdata(phy);

	reset_control_निश्चित(priv->rst_parent_gio);
	reset_control_निश्चित(priv->rst_parent);
	clk_disable_unprepare(priv->clk_parent_gio);
	clk_disable_unprepare(priv->clk_parent);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops uniphier_u3hsphy_ops = अणु
	.init           = uniphier_u3hsphy_init,
	.निकास           = uniphier_u3hsphy_निकास,
	.घातer_on       = uniphier_u3hsphy_घातer_on,
	.घातer_off      = uniphier_u3hsphy_घातer_off,
	.owner          = THIS_MODULE,
पूर्ण;

अटल पूर्णांक uniphier_u3hsphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uniphier_u3hsphy_priv *priv;
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

	phy = devm_phy_create(dev, dev->of_node, &uniphier_u3hsphy_ops);
	अगर (IS_ERR(phy))
		वापस PTR_ERR(phy);

	phy_set_drvdata(phy, priv);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा uniphier_u3hsphy_soc_data uniphier_pro5_data = अणु
	.is_legacy = true,
	.nparams = 0,
पूर्ण;

अटल स्थिर काष्ठा uniphier_u3hsphy_soc_data uniphier_pxs2_data = अणु
	.is_legacy = false,
	.nparams = 2,
	.param = अणु
		अणु RX_CHK_SYNC, 1 पूर्ण,
		अणु RX_SYNC_SEL, 1 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा uniphier_u3hsphy_soc_data uniphier_ld20_data = अणु
	.is_legacy = false,
	.nparams = 4,
	.param = अणु
		अणु RX_CHK_SYNC, 1 पूर्ण,
		अणु RX_SYNC_SEL, 1 पूर्ण,
		अणु LS_SLEW, 1 पूर्ण,
		अणु FS_LS_DRV, 1 पूर्ण,
	पूर्ण,
	.trim_func = uniphier_u3hsphy_trim_ld20,
	.config0 = 0x92316680,
	.config1 = 0x00000106,
पूर्ण;

अटल स्थिर काष्ठा uniphier_u3hsphy_soc_data uniphier_pxs3_data = अणु
	.is_legacy = false,
	.nparams = 2,
	.param = अणु
		अणु RX_CHK_SYNC, 1 पूर्ण,
		अणु RX_SYNC_SEL, 1 पूर्ण,
	पूर्ण,
	.trim_func = uniphier_u3hsphy_trim_ld20,
	.config0 = 0x92316680,
	.config1 = 0x00000106,
पूर्ण;

अटल स्थिर काष्ठा of_device_id uniphier_u3hsphy_match[] = अणु
	अणु
		.compatible = "socionext,uniphier-pro5-usb3-hsphy",
		.data = &uniphier_pro5_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs2-usb3-hsphy",
		.data = &uniphier_pxs2_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld20-usb3-hsphy",
		.data = &uniphier_ld20_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs3-usb3-hsphy",
		.data = &uniphier_pxs3_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_u3hsphy_match);

अटल काष्ठा platक्रमm_driver uniphier_u3hsphy_driver = अणु
	.probe = uniphier_u3hsphy_probe,
	.driver	= अणु
		.name = "uniphier-usb3-hsphy",
		.of_match_table	= uniphier_u3hsphy_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(uniphier_u3hsphy_driver);

MODULE_AUTHOR("Kunihiko Hayashi <hayashi.kunihiko@socionext.com>");
MODULE_DESCRIPTION("UniPhier HS-PHY driver for USB3 controller");
MODULE_LICENSE("GPL v2");
