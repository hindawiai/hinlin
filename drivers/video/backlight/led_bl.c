<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Texas Instruments Incorporated -  http://www.ti.com/
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 *
 * Based on pwm_bl.c
 */

#समावेश <linux/backlight.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा led_bl_data अणु
	काष्ठा device		*dev;
	काष्ठा backlight_device	*bl_dev;
	काष्ठा led_classdev	**leds;
	bool			enabled;
	पूर्णांक			nb_leds;
	अचिन्हित पूर्णांक		*levels;
	अचिन्हित पूर्णांक		शेष_brightness;
	अचिन्हित पूर्णांक		max_brightness;
पूर्ण;

अटल व्योम led_bl_set_brightness(काष्ठा led_bl_data *priv, पूर्णांक level)
अणु
	पूर्णांक i;
	पूर्णांक bkl_brightness;

	अगर (priv->levels)
		bkl_brightness = priv->levels[level];
	अन्यथा
		bkl_brightness = level;

	क्रम (i = 0; i < priv->nb_leds; i++)
		led_set_brightness(priv->leds[i], bkl_brightness);

	priv->enabled = true;
पूर्ण

अटल व्योम led_bl_घातer_off(काष्ठा led_bl_data *priv)
अणु
	पूर्णांक i;

	अगर (!priv->enabled)
		वापस;

	क्रम (i = 0; i < priv->nb_leds; i++)
		led_set_brightness(priv->leds[i], LED_OFF);

	priv->enabled = false;
पूर्ण

अटल पूर्णांक led_bl_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा led_bl_data *priv = bl_get_data(bl);
	पूर्णांक brightness = backlight_get_brightness(bl);

	अगर (brightness > 0)
		led_bl_set_brightness(priv, brightness);
	अन्यथा
		led_bl_घातer_off(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops led_bl_ops = अणु
	.update_status	= led_bl_update_status,
पूर्ण;

अटल पूर्णांक led_bl_get_leds(काष्ठा device *dev,
			   काष्ठा led_bl_data *priv)
अणु
	पूर्णांक i, nb_leds, ret;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा led_classdev **leds;
	अचिन्हित पूर्णांक max_brightness;
	अचिन्हित पूर्णांक शेष_brightness;

	ret = of_count_phandle_with_args(node, "leds", शून्य);
	अगर (ret < 0) अणु
		dev_err(dev, "Unable to get led count\n");
		वापस -EINVAL;
	पूर्ण

	nb_leds = ret;
	अगर (nb_leds < 1) अणु
		dev_err(dev, "At least one LED must be specified!\n");
		वापस -EINVAL;
	पूर्ण

	leds = devm_kzalloc(dev, माप(काष्ठा led_classdev *) * nb_leds,
			    GFP_KERNEL);
	अगर (!leds)
		वापस -ENOMEM;

	क्रम (i = 0; i < nb_leds; i++) अणु
		leds[i] = devm_of_led_get(dev, i);
		अगर (IS_ERR(leds[i]))
			वापस PTR_ERR(leds[i]);
	पूर्ण

	/* check that the LEDs all have the same brightness range */
	max_brightness = leds[0]->max_brightness;
	क्रम (i = 1; i < nb_leds; i++) अणु
		अगर (max_brightness != leds[i]->max_brightness) अणु
			dev_err(dev, "LEDs must have identical ranges\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* get the शेष brightness from the first LED from the list */
	शेष_brightness = leds[0]->brightness;

	priv->nb_leds = nb_leds;
	priv->leds = leds;
	priv->max_brightness = max_brightness;
	priv->शेष_brightness = शेष_brightness;

	वापस 0;
पूर्ण

अटल पूर्णांक led_bl_parse_levels(काष्ठा device *dev,
			   काष्ठा led_bl_data *priv)
अणु
	काष्ठा device_node *node = dev->of_node;
	पूर्णांक num_levels;
	u32 value;
	पूर्णांक ret;

	अगर (!node)
		वापस -ENODEV;

	num_levels = of_property_count_u32_elems(node, "brightness-levels");
	अगर (num_levels > 1) अणु
		पूर्णांक i;
		अचिन्हित पूर्णांक db;
		u32 *levels = शून्य;

		levels = devm_kzalloc(dev, माप(u32) * num_levels,
				      GFP_KERNEL);
		अगर (!levels)
			वापस -ENOMEM;

		ret = of_property_पढ़ो_u32_array(node, "brightness-levels",
						levels,
						num_levels);
		अगर (ret < 0)
			वापस ret;

		/*
		 * Try to map actual LED brightness to backlight brightness
		 * level
		 */
		db = priv->शेष_brightness;
		क्रम (i = 0 ; i < num_levels; i++) अणु
			अगर ((i && db > levels[i-1]) && db <= levels[i])
				अवरोध;
		पूर्ण
		priv->शेष_brightness = i;
		priv->max_brightness = num_levels - 1;
		priv->levels = levels;
	पूर्ण अन्यथा अगर (num_levels >= 0)
		dev_warn(dev, "Not enough levels defined\n");

	ret = of_property_पढ़ो_u32(node, "default-brightness-level", &value);
	अगर (!ret && value <= priv->max_brightness)
		priv->शेष_brightness = value;
	अन्यथा अगर (!ret  && value > priv->max_brightness)
		dev_warn(dev, "Invalid default brightness. Ignoring it\n");

	वापस 0;
पूर्ण

अटल पूर्णांक led_bl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_properties props;
	काष्ठा led_bl_data *priv;
	पूर्णांक ret, i;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	priv->dev = &pdev->dev;

	ret = led_bl_get_leds(&pdev->dev, priv);
	अगर (ret)
		वापस ret;

	ret = led_bl_parse_levels(&pdev->dev, priv);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to parse DT data\n");
		वापस ret;
	पूर्ण

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = priv->max_brightness;
	props.brightness = priv->शेष_brightness;
	props.घातer = (priv->शेष_brightness > 0) ? FB_BLANK_POWERDOWN :
		      FB_BLANK_UNBLANK;
	priv->bl_dev = backlight_device_रेजिस्टर(dev_name(&pdev->dev),
			&pdev->dev, priv, &led_bl_ops, &props);
	अगर (IS_ERR(priv->bl_dev)) अणु
		dev_err(&pdev->dev, "Failed to register backlight\n");
		वापस PTR_ERR(priv->bl_dev);
	पूर्ण

	क्रम (i = 0; i < priv->nb_leds; i++)
		led_sysfs_disable(priv->leds[i]);

	backlight_update_status(priv->bl_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक led_bl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा led_bl_data *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा backlight_device *bl = priv->bl_dev;
	पूर्णांक i;

	backlight_device_unरेजिस्टर(bl);

	led_bl_घातer_off(priv);
	क्रम (i = 0; i < priv->nb_leds; i++)
		led_sysfs_enable(priv->leds[i]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id led_bl_of_match[] = अणु
	अणु .compatible = "led-backlight" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, led_bl_of_match);

अटल काष्ठा platक्रमm_driver led_bl_driver = अणु
	.driver		= अणु
		.name		= "led-backlight",
		.of_match_table	= of_match_ptr(led_bl_of_match),
	पूर्ण,
	.probe		= led_bl_probe,
	.हटाओ		= led_bl_हटाओ,
पूर्ण;

module_platक्रमm_driver(led_bl_driver);

MODULE_DESCRIPTION("LED based Backlight Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:led-backlight");
