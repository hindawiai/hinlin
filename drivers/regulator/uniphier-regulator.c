<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Regulator controller driver क्रम UniPhier SoC
// Copyright 2018 Socionext Inc.
// Author: Kunihiko Hayashi <hayashi.kunihiko@socionext.com>

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/reset.h>

#घोषणा MAX_CLKS	2
#घोषणा MAX_RSTS	2

काष्ठा uniphier_regulator_soc_data अणु
	पूर्णांक nclks;
	स्थिर अक्षर * स्थिर *घड़ी_names;
	पूर्णांक nrsts;
	स्थिर अक्षर * स्थिर *reset_names;
	स्थिर काष्ठा regulator_desc *desc;
	स्थिर काष्ठा regmap_config *regconf;
पूर्ण;

काष्ठा uniphier_regulator_priv अणु
	काष्ठा clk_bulk_data clk[MAX_CLKS];
	काष्ठा reset_control *rst[MAX_RSTS];
	स्थिर काष्ठा uniphier_regulator_soc_data *data;
पूर्ण;

अटल स्थिर काष्ठा regulator_ops uniphier_regulator_ops = अणु
	.enable     = regulator_enable_regmap,
	.disable    = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

अटल पूर्णांक uniphier_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uniphier_regulator_priv *priv;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा regmap *regmap;
	व्योम __iomem *base;
	स्थिर अक्षर *name;
	पूर्णांक i, ret, nr;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->data = of_device_get_match_data(dev);
	अगर (WARN_ON(!priv->data))
		वापस -EINVAL;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	क्रम (i = 0; i < priv->data->nclks; i++)
		priv->clk[i].id = priv->data->घड़ी_names[i];
	ret = devm_clk_bulk_get(dev, priv->data->nclks, priv->clk);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < priv->data->nrsts; i++) अणु
		name = priv->data->reset_names[i];
		priv->rst[i] = devm_reset_control_get_shared(dev, name);
		अगर (IS_ERR(priv->rst[i]))
			वापस PTR_ERR(priv->rst[i]);
	पूर्ण

	ret = clk_bulk_prepare_enable(priv->data->nclks, priv->clk);
	अगर (ret)
		वापस ret;

	क्रम (nr = 0; nr < priv->data->nrsts; nr++) अणु
		ret = reset_control_deनिश्चित(priv->rst[nr]);
		अगर (ret)
			जाओ out_rst_निश्चित;
	पूर्ण

	regmap = devm_regmap_init_mmio(dev, base, priv->data->regconf);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		जाओ out_rst_निश्चित;
	पूर्ण

	config.dev = dev;
	config.driver_data = priv;
	config.of_node = dev->of_node;
	config.regmap = regmap;
	config.init_data = of_get_regulator_init_data(dev, dev->of_node,
						      priv->data->desc);
	rdev = devm_regulator_रेजिस्टर(dev, priv->data->desc, &config);
	अगर (IS_ERR(rdev)) अणु
		ret = PTR_ERR(rdev);
		जाओ out_rst_निश्चित;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	वापस 0;

out_rst_निश्चित:
	जबतक (nr--)
		reset_control_निश्चित(priv->rst[nr]);

	clk_bulk_disable_unprepare(priv->data->nclks, priv->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_regulator_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uniphier_regulator_priv *priv = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < priv->data->nrsts; i++)
		reset_control_निश्चित(priv->rst[i]);

	clk_bulk_disable_unprepare(priv->data->nclks, priv->clk);

	वापस 0;
पूर्ण

/* USB3 controller data */
#घोषणा USB3VBUS_OFFSET		0x0
#घोषणा USB3VBUS_REG		BIT(4)
#घोषणा USB3VBUS_REG_EN		BIT(3)
अटल स्थिर काष्ठा regulator_desc uniphier_usb3_regulator_desc = अणु
	.name = "vbus",
	.of_match = of_match_ptr("vbus"),
	.ops = &uniphier_regulator_ops,
	.type = REGULATOR_VOLTAGE,
	.owner = THIS_MODULE,
	.enable_reg  = USB3VBUS_OFFSET,
	.enable_mask = USB3VBUS_REG_EN | USB3VBUS_REG,
	.enable_val  = USB3VBUS_REG_EN | USB3VBUS_REG,
	.disable_val = USB3VBUS_REG_EN,
पूर्ण;

अटल स्थिर काष्ठा regmap_config uniphier_usb3_regulator_regconf = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = 1,
पूर्ण;

अटल स्थिर अक्षर * स्थिर uniphier_pro4_घड़ी_reset_names[] = अणु
	"gio", "link",
पूर्ण;

अटल स्थिर काष्ठा uniphier_regulator_soc_data uniphier_pro4_usb3_data = अणु
	.nclks = ARRAY_SIZE(uniphier_pro4_घड़ी_reset_names),
	.घड़ी_names = uniphier_pro4_घड़ी_reset_names,
	.nrsts = ARRAY_SIZE(uniphier_pro4_घड़ी_reset_names),
	.reset_names = uniphier_pro4_घड़ी_reset_names,
	.desc = &uniphier_usb3_regulator_desc,
	.regconf = &uniphier_usb3_regulator_regconf,
पूर्ण;

अटल स्थिर अक्षर * स्थिर uniphier_pxs2_घड़ी_reset_names[] = अणु
	"link",
पूर्ण;

अटल स्थिर काष्ठा uniphier_regulator_soc_data uniphier_pxs2_usb3_data = अणु
	.nclks = ARRAY_SIZE(uniphier_pxs2_घड़ी_reset_names),
	.घड़ी_names = uniphier_pxs2_घड़ी_reset_names,
	.nrsts = ARRAY_SIZE(uniphier_pxs2_घड़ी_reset_names),
	.reset_names = uniphier_pxs2_घड़ी_reset_names,
	.desc = &uniphier_usb3_regulator_desc,
	.regconf = &uniphier_usb3_regulator_regconf,
पूर्ण;

अटल स्थिर काष्ठा of_device_id uniphier_regulator_match[] = अणु
	/* USB VBUS */
	अणु
		.compatible = "socionext,uniphier-pro4-usb3-regulator",
		.data = &uniphier_pro4_usb3_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pro5-usb3-regulator",
		.data = &uniphier_pro4_usb3_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs2-usb3-regulator",
		.data = &uniphier_pxs2_usb3_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld20-usb3-regulator",
		.data = &uniphier_pxs2_usb3_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs3-usb3-regulator",
		.data = &uniphier_pxs2_usb3_data,
	पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver uniphier_regulator_driver = अणु
	.probe = uniphier_regulator_probe,
	.हटाओ = uniphier_regulator_हटाओ,
	.driver = अणु
		.name  = "uniphier-regulator",
		.of_match_table = uniphier_regulator_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_regulator_driver);

MODULE_AUTHOR("Kunihiko Hayashi <hayashi.kunihiko@socionext.com>");
MODULE_DESCRIPTION("UniPhier Regulator Controller Driver");
MODULE_LICENSE("GPL");
