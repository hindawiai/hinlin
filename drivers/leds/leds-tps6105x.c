<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2019 Sven Van Asbroeck
 */

#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/tps6105x.h>
#समावेश <linux/regmap.h>

काष्ठा tps6105x_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा led_classdev cdev;
	काष्ठा fwnode_handle *fwnode;
पूर्ण;

अटल व्योम tps6105x_handle_put(व्योम *data)
अणु
	काष्ठा tps6105x_priv *priv = data;

	fwnode_handle_put(priv->fwnode);
पूर्ण

अटल पूर्णांक tps6105x_brightness_set(काष्ठा led_classdev *cdev,
				  क्रमागत led_brightness brightness)
अणु
	काष्ठा tps6105x_priv *priv = container_of(cdev, काष्ठा tps6105x_priv,
							cdev);

	वापस regmap_update_bits(priv->regmap, TPS6105X_REG_0,
				  TPS6105X_REG0_TORCHC_MASK,
				  brightness << TPS6105X_REG0_TORCHC_SHIFT);
पूर्ण

अटल पूर्णांक tps6105x_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps6105x *tps6105x = dev_get_platdata(&pdev->dev);
	काष्ठा tps6105x_platक्रमm_data *pdata = tps6105x->pdata;
	काष्ठा led_init_data init_data = अणु पूर्ण;
	काष्ठा tps6105x_priv *priv;
	पूर्णांक ret;

	/* This instance is not set क्रम torch mode so bail out */
	अगर (pdata->mode != TPS6105X_MODE_TORCH) अणु
		dev_info(&pdev->dev,
			"chip not in torch mode, exit probe");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	/* fwnode/devicetree is optional. शून्य is allowed क्रम priv->fwnode */
	priv->fwnode = device_get_next_child_node(pdev->dev.parent, शून्य);
	ret = devm_add_action_or_reset(&pdev->dev, tps6105x_handle_put, priv);
	अगर (ret)
		वापस ret;
	priv->regmap = tps6105x->regmap;
	priv->cdev.brightness_set_blocking = tps6105x_brightness_set;
	priv->cdev.max_brightness = 7;
	init_data.devicename = "tps6105x";
	init_data.शेष_label = ":torch";
	init_data.fwnode = priv->fwnode;

	ret = regmap_update_bits(tps6105x->regmap, TPS6105X_REG_0,
				 TPS6105X_REG0_MODE_MASK |
					TPS6105X_REG0_TORCHC_MASK,
				 TPS6105X_REG0_MODE_TORCH <<
					TPS6105X_REG0_MODE_SHIFT);
	अगर (ret)
		वापस ret;

	वापस devm_led_classdev_रेजिस्टर_ext(&pdev->dev, &priv->cdev,
					      &init_data);
पूर्ण

अटल काष्ठा platक्रमm_driver led_driver = अणु
	.probe = tps6105x_led_probe,
	.driver = अणु
		.name = "tps6105x-leds",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(led_driver);

MODULE_DESCRIPTION("TPS6105x LED driver");
MODULE_AUTHOR("Sven Van Asbroeck <TheSven73@gmail.com>");
MODULE_LICENSE("GPL v2");
