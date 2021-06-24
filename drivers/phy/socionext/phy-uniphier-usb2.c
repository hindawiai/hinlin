<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * phy-uniphier-usb2.c - PHY driver क्रम UniPhier USB2 controller
 * Copyright 2015-2018 Socionext Inc.
 * Author:
 *      Kunihiko Hayashi <hayashi.kunihiko@socionext.com>
 */

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा SG_USBPHY1CTRL		0x500
#घोषणा SG_USBPHY1CTRL2		0x504
#घोषणा SG_USBPHY2CTRL		0x508
#घोषणा SG_USBPHY2CTRL2		0x50c	/* LD11 */
#घोषणा SG_USBPHY12PLL		0x50c	/* Pro4 */
#घोषणा SG_USBPHY3CTRL		0x510
#घोषणा SG_USBPHY3CTRL2		0x514
#घोषणा SG_USBPHY4CTRL		0x518	/* Pro4 */
#घोषणा SG_USBPHY4CTRL2		0x51c	/* Pro4 */
#घोषणा SG_USBPHY34PLL		0x51c	/* Pro4 */

काष्ठा uniphier_u2phy_param अणु
	u32 offset;
	u32 value;
पूर्ण;

काष्ठा uniphier_u2phy_soc_data अणु
	काष्ठा uniphier_u2phy_param config0;
	काष्ठा uniphier_u2phy_param config1;
पूर्ण;

काष्ठा uniphier_u2phy_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा phy *phy;
	काष्ठा regulator *vbus;
	स्थिर काष्ठा uniphier_u2phy_soc_data *data;
	काष्ठा uniphier_u2phy_priv *next;
पूर्ण;

अटल पूर्णांक uniphier_u2phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_u2phy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret = 0;

	अगर (priv->vbus)
		ret = regulator_enable(priv->vbus);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_u2phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_u2phy_priv *priv = phy_get_drvdata(phy);

	अगर (priv->vbus)
		regulator_disable(priv->vbus);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_u2phy_init(काष्ठा phy *phy)
अणु
	काष्ठा uniphier_u2phy_priv *priv = phy_get_drvdata(phy);

	अगर (!priv->data)
		वापस 0;

	regmap_ग_लिखो(priv->regmap, priv->data->config0.offset,
		     priv->data->config0.value);
	regmap_ग_लिखो(priv->regmap, priv->data->config1.offset,
		     priv->data->config1.value);

	वापस 0;
पूर्ण

अटल काष्ठा phy *uniphier_u2phy_xlate(काष्ठा device *dev,
					काष्ठा of_phandle_args *args)
अणु
	काष्ठा uniphier_u2phy_priv *priv = dev_get_drvdata(dev);

	जबतक (priv && args->np != priv->phy->dev.of_node)
		priv = priv->next;

	अगर (!priv) अणु
		dev_err(dev, "Failed to find appropriate phy\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस priv->phy;
पूर्ण

अटल स्थिर काष्ठा phy_ops uniphier_u2phy_ops = अणु
	.init      = uniphier_u2phy_init,
	.घातer_on  = uniphier_u2phy_घातer_on,
	.घातer_off = uniphier_u2phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक uniphier_u2phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *parent, *child;
	काष्ठा uniphier_u2phy_priv *priv = शून्य, *next = शून्य;
	काष्ठा phy_provider *phy_provider;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा uniphier_u2phy_soc_data *data;
	पूर्णांक ret, data_idx, ndatas;

	data = of_device_get_match_data(dev);
	अगर (WARN_ON(!data))
		वापस -EINVAL;

	/* get number of data */
	क्रम (ndatas = 0; data[ndatas].config0.offset; ndatas++)
		;

	parent = of_get_parent(dev->of_node);
	regmap = syscon_node_to_regmap(parent);
	of_node_put(parent);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Failed to get regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	क्रम_each_child_of_node(dev->of_node, child) अणु
		priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
		अगर (!priv) अणु
			ret = -ENOMEM;
			जाओ out_put_child;
		पूर्ण
		priv->regmap = regmap;

		priv->vbus = devm_regulator_get_optional(dev, "vbus");
		अगर (IS_ERR(priv->vbus)) अणु
			अगर (PTR_ERR(priv->vbus) == -EPROBE_DEFER) अणु
				ret = PTR_ERR(priv->vbus);
				जाओ out_put_child;
			पूर्ण
			priv->vbus = शून्य;
		पूर्ण

		priv->phy = devm_phy_create(dev, child, &uniphier_u2phy_ops);
		अगर (IS_ERR(priv->phy)) अणु
			dev_err(dev, "Failed to create phy\n");
			ret = PTR_ERR(priv->phy);
			जाओ out_put_child;
		पूर्ण

		ret = of_property_पढ़ो_u32(child, "reg", &data_idx);
		अगर (ret) अणु
			dev_err(dev, "Failed to get reg property\n");
			जाओ out_put_child;
		पूर्ण

		अगर (data_idx < ndatas)
			priv->data = &data[data_idx];
		अन्यथा
			dev_warn(dev, "No phy configuration: %s\n",
				 child->full_name);

		phy_set_drvdata(priv->phy, priv);
		priv->next = next;
		next = priv;
	पूर्ण

	dev_set_drvdata(dev, priv);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev,
						     uniphier_u2phy_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);

out_put_child:
	of_node_put(child);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा uniphier_u2phy_soc_data uniphier_pro4_data[] = अणु
	अणु
		.config0 = अणु SG_USBPHY1CTRL, 0x05142400 पूर्ण,
		.config1 = अणु SG_USBPHY12PLL, 0x00010010 पूर्ण,
	पूर्ण,
	अणु
		.config0 = अणु SG_USBPHY2CTRL, 0x05142400 पूर्ण,
		.config1 = अणु SG_USBPHY12PLL, 0x00010010 पूर्ण,
	पूर्ण,
	अणु
		.config0 = अणु SG_USBPHY3CTRL, 0x05142400 पूर्ण,
		.config1 = अणु SG_USBPHY34PLL, 0x00010010 पूर्ण,
	पूर्ण,
	अणु
		.config0 = अणु SG_USBPHY4CTRL, 0x05142400 पूर्ण,
		.config1 = अणु SG_USBPHY34PLL, 0x00010010 पूर्ण,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा uniphier_u2phy_soc_data uniphier_ld11_data[] = अणु
	अणु
		.config0 = अणु SG_USBPHY1CTRL,  0x82280000 पूर्ण,
		.config1 = अणु SG_USBPHY1CTRL2, 0x00000106 पूर्ण,
	पूर्ण,
	अणु
		.config0 = अणु SG_USBPHY2CTRL,  0x82280000 पूर्ण,
		.config1 = अणु SG_USBPHY2CTRL2, 0x00000106 पूर्ण,
	पूर्ण,
	अणु
		.config0 = अणु SG_USBPHY3CTRL,  0x82280000 पूर्ण,
		.config1 = अणु SG_USBPHY3CTRL2, 0x00000106 पूर्ण,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id uniphier_u2phy_match[] = अणु
	अणु
		.compatible = "socionext,uniphier-pro4-usb2-phy",
		.data = &uniphier_pro4_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld11-usb2-phy",
		.data = &uniphier_ld11_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_u2phy_match);

अटल काष्ठा platक्रमm_driver uniphier_u2phy_driver = अणु
	.probe = uniphier_u2phy_probe,
	.driver = अणु
		.name = "uniphier-usb2-phy",
		.of_match_table = uniphier_u2phy_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_u2phy_driver);

MODULE_AUTHOR("Kunihiko Hayashi <hayashi.kunihiko@socionext.com>");
MODULE_DESCRIPTION("UniPhier PHY driver for USB2 controller");
MODULE_LICENSE("GPL v2");
