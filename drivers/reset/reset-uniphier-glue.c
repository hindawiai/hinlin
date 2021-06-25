<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// reset-uniphier-glue.c - Glue layer reset driver क्रम UniPhier
// Copyright 2018 Socionext Inc.
// Author: Kunihiko Hayashi <hayashi.kunihiko@socionext.com>

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/reset/reset-simple.h>

#घोषणा MAX_CLKS	2
#घोषणा MAX_RSTS	2

काष्ठा uniphier_glue_reset_soc_data अणु
	पूर्णांक nclks;
	स्थिर अक्षर * स्थिर *घड़ी_names;
	पूर्णांक nrsts;
	स्थिर अक्षर * स्थिर *reset_names;
पूर्ण;

काष्ठा uniphier_glue_reset_priv अणु
	काष्ठा clk_bulk_data clk[MAX_CLKS];
	काष्ठा reset_control *rst[MAX_RSTS];
	काष्ठा reset_simple_data rdata;
	स्थिर काष्ठा uniphier_glue_reset_soc_data *data;
पूर्ण;

अटल पूर्णांक uniphier_glue_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uniphier_glue_reset_priv *priv;
	काष्ठा resource *res;
	resource_माप_प्रकार size;
	स्थिर अक्षर *name;
	पूर्णांक i, ret, nr;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->data = of_device_get_match_data(dev);
	अगर (WARN_ON(!priv->data || priv->data->nclks > MAX_CLKS ||
		    priv->data->nrsts > MAX_RSTS))
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	size = resource_size(res);
	priv->rdata.membase = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->rdata.membase))
		वापस PTR_ERR(priv->rdata.membase);

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

	spin_lock_init(&priv->rdata.lock);
	priv->rdata.rcdev.owner = THIS_MODULE;
	priv->rdata.rcdev.nr_resets = size * BITS_PER_BYTE;
	priv->rdata.rcdev.ops = &reset_simple_ops;
	priv->rdata.rcdev.of_node = dev->of_node;
	priv->rdata.active_low = true;

	platक्रमm_set_drvdata(pdev, priv);

	ret = devm_reset_controller_रेजिस्टर(dev, &priv->rdata.rcdev);
	अगर (ret)
		जाओ out_rst_निश्चित;

	वापस 0;

out_rst_निश्चित:
	जबतक (nr--)
		reset_control_निश्चित(priv->rst[nr]);

	clk_bulk_disable_unprepare(priv->data->nclks, priv->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_glue_reset_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uniphier_glue_reset_priv *priv = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < priv->data->nrsts; i++)
		reset_control_निश्चित(priv->rst[i]);

	clk_bulk_disable_unprepare(priv->data->nclks, priv->clk);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर uniphier_pro4_घड़ी_reset_names[] = अणु
	"gio", "link",
पूर्ण;

अटल स्थिर काष्ठा uniphier_glue_reset_soc_data uniphier_pro4_data = अणु
	.nclks = ARRAY_SIZE(uniphier_pro4_घड़ी_reset_names),
	.घड़ी_names = uniphier_pro4_घड़ी_reset_names,
	.nrsts = ARRAY_SIZE(uniphier_pro4_घड़ी_reset_names),
	.reset_names = uniphier_pro4_घड़ी_reset_names,
पूर्ण;

अटल स्थिर अक्षर * स्थिर uniphier_pxs2_घड़ी_reset_names[] = अणु
	"link",
पूर्ण;

अटल स्थिर काष्ठा uniphier_glue_reset_soc_data uniphier_pxs2_data = अणु
	.nclks = ARRAY_SIZE(uniphier_pxs2_घड़ी_reset_names),
	.घड़ी_names = uniphier_pxs2_घड़ी_reset_names,
	.nrsts = ARRAY_SIZE(uniphier_pxs2_घड़ी_reset_names),
	.reset_names = uniphier_pxs2_घड़ी_reset_names,
पूर्ण;

अटल स्थिर काष्ठा of_device_id uniphier_glue_reset_match[] = अणु
	अणु
		.compatible = "socionext,uniphier-pro4-usb3-reset",
		.data = &uniphier_pro4_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pro5-usb3-reset",
		.data = &uniphier_pro4_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs2-usb3-reset",
		.data = &uniphier_pxs2_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld20-usb3-reset",
		.data = &uniphier_pxs2_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs3-usb3-reset",
		.data = &uniphier_pxs2_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pro4-ahci-reset",
		.data = &uniphier_pro4_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs2-ahci-reset",
		.data = &uniphier_pxs2_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs3-ahci-reset",
		.data = &uniphier_pxs2_data,
	पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_glue_reset_match);

अटल काष्ठा platक्रमm_driver uniphier_glue_reset_driver = अणु
	.probe = uniphier_glue_reset_probe,
	.हटाओ = uniphier_glue_reset_हटाओ,
	.driver = अणु
		.name = "uniphier-glue-reset",
		.of_match_table = uniphier_glue_reset_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_glue_reset_driver);

MODULE_AUTHOR("Kunihiko Hayashi <hayashi.kunihiko@socionext.com>");
MODULE_DESCRIPTION("UniPhier Glue layer reset driver");
MODULE_LICENSE("GPL");
