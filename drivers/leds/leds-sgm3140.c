<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2020 Luca Weiss <luca@z3ntu.xyz>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/led-class-flash.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <media/v4l2-flash-led-class.h>

#घोषणा FLASH_TIMEOUT_DEFAULT		250000U /* 250ms */
#घोषणा FLASH_MAX_TIMEOUT_DEFAULT	300000U /* 300ms */

काष्ठा sgm3140 अणु
	काष्ठा led_classdev_flash fled_cdev;
	काष्ठा v4l2_flash *v4l2_flash;

	काष्ठा समयr_list घातerकरोwn_समयr;

	काष्ठा gpio_desc *flash_gpio;
	काष्ठा gpio_desc *enable_gpio;
	काष्ठा regulator *vin_regulator;

	bool enabled;

	/* current समयout in us */
	u32 समयout;
	/* maximum समयout in us */
	u32 max_समयout;
पूर्ण;

अटल काष्ठा sgm3140 *flcdev_to_sgm3140(काष्ठा led_classdev_flash *flcdev)
अणु
	वापस container_of(flcdev, काष्ठा sgm3140, fled_cdev);
पूर्ण

अटल पूर्णांक sgm3140_strobe_set(काष्ठा led_classdev_flash *fled_cdev, bool state)
अणु
	काष्ठा sgm3140 *priv = flcdev_to_sgm3140(fled_cdev);
	पूर्णांक ret;

	अगर (priv->enabled == state)
		वापस 0;

	अगर (state) अणु
		ret = regulator_enable(priv->vin_regulator);
		अगर (ret) अणु
			dev_err(fled_cdev->led_cdev.dev,
				"failed to enable regulator: %d\n", ret);
			वापस ret;
		पूर्ण
		gpiod_set_value_cansleep(priv->flash_gpio, 1);
		gpiod_set_value_cansleep(priv->enable_gpio, 1);
		mod_समयr(&priv->घातerकरोwn_समयr,
			  jअगरfies + usecs_to_jअगरfies(priv->समयout));
	पूर्ण अन्यथा अणु
		del_समयr_sync(&priv->घातerकरोwn_समयr);
		gpiod_set_value_cansleep(priv->enable_gpio, 0);
		gpiod_set_value_cansleep(priv->flash_gpio, 0);
		ret = regulator_disable(priv->vin_regulator);
		अगर (ret) अणु
			dev_err(fled_cdev->led_cdev.dev,
				"failed to disable regulator: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	priv->enabled = state;

	वापस 0;
पूर्ण

अटल पूर्णांक sgm3140_strobe_get(काष्ठा led_classdev_flash *fled_cdev, bool *state)
अणु
	काष्ठा sgm3140 *priv = flcdev_to_sgm3140(fled_cdev);

	*state = समयr_pending(&priv->घातerकरोwn_समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक sgm3140_समयout_set(काष्ठा led_classdev_flash *fled_cdev,
			       u32 समयout)
अणु
	काष्ठा sgm3140 *priv = flcdev_to_sgm3140(fled_cdev);

	priv->समयout = समयout;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा led_flash_ops sgm3140_flash_ops = अणु
	.strobe_set = sgm3140_strobe_set,
	.strobe_get = sgm3140_strobe_get,
	.समयout_set = sgm3140_समयout_set,
पूर्ण;

अटल पूर्णांक sgm3140_brightness_set(काष्ठा led_classdev *led_cdev,
				  क्रमागत led_brightness brightness)
अणु
	काष्ठा led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);
	काष्ठा sgm3140 *priv = flcdev_to_sgm3140(fled_cdev);
	bool enable = brightness == LED_ON;
	पूर्णांक ret;

	अगर (priv->enabled == enable)
		वापस 0;

	अगर (enable) अणु
		ret = regulator_enable(priv->vin_regulator);
		अगर (ret) अणु
			dev_err(led_cdev->dev,
				"failed to enable regulator: %d\n", ret);
			वापस ret;
		पूर्ण
		gpiod_set_value_cansleep(priv->enable_gpio, 1);
	पूर्ण अन्यथा अणु
		gpiod_set_value_cansleep(priv->enable_gpio, 0);
		ret = regulator_disable(priv->vin_regulator);
		अगर (ret) अणु
			dev_err(led_cdev->dev,
				"failed to disable regulator: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	priv->enabled = enable;

	वापस 0;
पूर्ण

अटल व्योम sgm3140_घातerकरोwn_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sgm3140 *priv = from_समयr(priv, t, घातerकरोwn_समयr);

	gpiod_set_value(priv->enable_gpio, 0);
	gpiod_set_value(priv->flash_gpio, 0);
	regulator_disable(priv->vin_regulator);

	priv->enabled = false;
पूर्ण

अटल व्योम sgm3140_init_flash_समयout(काष्ठा sgm3140 *priv)
अणु
	काष्ठा led_classdev_flash *fled_cdev = &priv->fled_cdev;
	काष्ठा led_flash_setting *s;

	/* Init flash समयout setting */
	s = &fled_cdev->समयout;
	s->min = 1;
	s->max = priv->max_समयout;
	s->step = 1;
	s->val = FLASH_TIMEOUT_DEFAULT;
पूर्ण

#अगर IS_ENABLED(CONFIG_V4L2_FLASH_LED_CLASS)
अटल व्योम sgm3140_init_v4l2_flash_config(काष्ठा sgm3140 *priv,
					काष्ठा v4l2_flash_config *v4l2_sd_cfg)
अणु
	काष्ठा led_classdev *led_cdev = &priv->fled_cdev.led_cdev;
	काष्ठा led_flash_setting *s;

	strscpy(v4l2_sd_cfg->dev_name, led_cdev->dev->kobj.name,
		माप(v4l2_sd_cfg->dev_name));

	/* Init flash पूर्णांकensity setting */
	s = &v4l2_sd_cfg->पूर्णांकensity;
	s->min = 0;
	s->max = 1;
	s->step = 1;
	s->val = 1;
पूर्ण

#अन्यथा
अटल व्योम sgm3140_init_v4l2_flash_config(काष्ठा sgm3140 *priv,
					काष्ठा v4l2_flash_config *v4l2_sd_cfg)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sgm3140_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sgm3140 *priv;
	काष्ठा led_classdev *led_cdev;
	काष्ठा led_classdev_flash *fled_cdev;
	काष्ठा led_init_data init_data = अणुपूर्ण;
	काष्ठा fwnode_handle *child_node;
	काष्ठा v4l2_flash_config v4l2_sd_cfg = अणुपूर्ण;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->flash_gpio = devm_gpiod_get(&pdev->dev, "flash", GPIOD_OUT_LOW);
	ret = PTR_ERR_OR_ZERO(priv->flash_gpio);
	अगर (ret)
		वापस dev_err_probe(&pdev->dev, ret,
				     "Failed to request flash gpio\n");

	priv->enable_gpio = devm_gpiod_get(&pdev->dev, "enable", GPIOD_OUT_LOW);
	ret = PTR_ERR_OR_ZERO(priv->enable_gpio);
	अगर (ret)
		वापस dev_err_probe(&pdev->dev, ret,
				     "Failed to request enable gpio\n");

	priv->vin_regulator = devm_regulator_get(&pdev->dev, "vin");
	ret = PTR_ERR_OR_ZERO(priv->vin_regulator);
	अगर (ret)
		वापस dev_err_probe(&pdev->dev, ret,
				     "Failed to request regulator\n");

	child_node = fwnode_get_next_available_child_node(pdev->dev.fwnode,
							  शून्य);
	अगर (!child_node) अणु
		dev_err(&pdev->dev,
			"No fwnode child node found for connected LED.\n");
		वापस -EINVAL;
	पूर्ण

	ret = fwnode_property_पढ़ो_u32(child_node, "flash-max-timeout-us",
				       &priv->max_समयout);
	अगर (ret) अणु
		priv->max_समयout = FLASH_MAX_TIMEOUT_DEFAULT;
		dev_warn(&pdev->dev,
			 "flash-max-timeout-us property missing\n");
	पूर्ण

	/*
	 * Set शेष समयout to FLASH_DEFAULT_TIMEOUT except अगर max_समयout
	 * from DT is lower.
	 */
	priv->समयout = min(priv->max_समयout, FLASH_TIMEOUT_DEFAULT);

	समयr_setup(&priv->घातerकरोwn_समयr, sgm3140_घातerकरोwn_समयr, 0);

	fled_cdev = &priv->fled_cdev;
	led_cdev = &fled_cdev->led_cdev;

	fled_cdev->ops = &sgm3140_flash_ops;

	led_cdev->brightness_set_blocking = sgm3140_brightness_set;
	led_cdev->max_brightness = LED_ON;
	led_cdev->flags |= LED_DEV_CAP_FLASH;

	sgm3140_init_flash_समयout(priv);

	init_data.fwnode = child_node;

	platक्रमm_set_drvdata(pdev, priv);

	/* Register in the LED subप्रणाली */
	ret = devm_led_classdev_flash_रेजिस्टर_ext(&pdev->dev,
						   fled_cdev, &init_data);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register flash device: %d\n",
			ret);
		जाओ err;
	पूर्ण

	sgm3140_init_v4l2_flash_config(priv, &v4l2_sd_cfg);

	/* Create V4L2 Flash subdev */
	priv->v4l2_flash = v4l2_flash_init(&pdev->dev,
					   child_node,
					   fled_cdev, शून्य,
					   &v4l2_sd_cfg);
	अगर (IS_ERR(priv->v4l2_flash)) अणु
		ret = PTR_ERR(priv->v4l2_flash);
		जाओ err;
	पूर्ण

	वापस ret;

err:
	fwnode_handle_put(child_node);
	वापस ret;
पूर्ण

अटल पूर्णांक sgm3140_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sgm3140 *priv = platक्रमm_get_drvdata(pdev);

	del_समयr_sync(&priv->घातerकरोwn_समयr);

	v4l2_flash_release(priv->v4l2_flash);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sgm3140_dt_match[] = अणु
	अणु .compatible = "sgmicro,sgm3140" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sgm3140_dt_match);

अटल काष्ठा platक्रमm_driver sgm3140_driver = अणु
	.probe	= sgm3140_probe,
	.हटाओ	= sgm3140_हटाओ,
	.driver	= अणु
		.name	= "sgm3140",
		.of_match_table = sgm3140_dt_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sgm3140_driver);

MODULE_AUTHOR("Luca Weiss <luca@z3ntu.xyz>");
MODULE_DESCRIPTION("SG Micro SGM3140 charge pump LED driver");
MODULE_LICENSE("GPL v2");
