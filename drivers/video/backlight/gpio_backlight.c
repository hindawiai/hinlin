<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * gpio_backlight.c - Simple GPIO-controlled backlight
 */

#समावेश <linux/backlight.h>
#समावेश <linux/err.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/gpio_backlight.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>

काष्ठा gpio_backlight अणु
	काष्ठा device *fbdev;
	काष्ठा gpio_desc *gpiod;
पूर्ण;

अटल पूर्णांक gpio_backlight_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा gpio_backlight *gbl = bl_get_data(bl);

	gpiod_set_value_cansleep(gbl->gpiod, backlight_get_brightness(bl));

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_backlight_check_fb(काष्ठा backlight_device *bl,
				   काष्ठा fb_info *info)
अणु
	काष्ठा gpio_backlight *gbl = bl_get_data(bl);

	वापस gbl->fbdev == शून्य || gbl->fbdev == info->dev;
पूर्ण

अटल स्थिर काष्ठा backlight_ops gpio_backlight_ops = अणु
	.options	= BL_CORE_SUSPENDRESUME,
	.update_status	= gpio_backlight_update_status,
	.check_fb	= gpio_backlight_check_fb,
पूर्ण;

अटल पूर्णांक gpio_backlight_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gpio_backlight_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा device_node *of_node = dev->of_node;
	काष्ठा backlight_properties props;
	काष्ठा backlight_device *bl;
	काष्ठा gpio_backlight *gbl;
	पूर्णांक ret, init_brightness, def_value;

	gbl = devm_kzalloc(dev, माप(*gbl), GFP_KERNEL);
	अगर (gbl == शून्य)
		वापस -ENOMEM;

	अगर (pdata)
		gbl->fbdev = pdata->fbdev;

	def_value = device_property_पढ़ो_bool(dev, "default-on");

	gbl->gpiod = devm_gpiod_get(dev, शून्य, GPIOD_ASIS);
	अगर (IS_ERR(gbl->gpiod)) अणु
		ret = PTR_ERR(gbl->gpiod);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev,
				"Error: The gpios parameter is missing or invalid.\n");
		वापस ret;
	पूर्ण

	स_रखो(&props, 0, माप(props));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = 1;
	bl = devm_backlight_device_रेजिस्टर(dev, dev_name(dev), dev, gbl,
					    &gpio_backlight_ops, &props);
	अगर (IS_ERR(bl)) अणु
		dev_err(dev, "failed to register backlight\n");
		वापस PTR_ERR(bl);
	पूर्ण

	/* Set the initial घातer state */
	अगर (!of_node || !of_node->phandle)
		/* Not booted with device tree or no phandle link to the node */
		bl->props.घातer = def_value ? FB_BLANK_UNBLANK
					    : FB_BLANK_POWERDOWN;
	अन्यथा अगर (gpiod_get_direction(gbl->gpiod) == 0 &&
		 gpiod_get_value_cansleep(gbl->gpiod) == 0)
		bl->props.घातer = FB_BLANK_POWERDOWN;
	अन्यथा
		bl->props.घातer = FB_BLANK_UNBLANK;

	bl->props.brightness = 1;

	init_brightness = backlight_get_brightness(bl);
	ret = gpiod_direction_output(gbl->gpiod, init_brightness);
	अगर (ret) अणु
		dev_err(dev, "failed to set initial brightness\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, bl);
	वापस 0;
पूर्ण

अटल काष्ठा of_device_id gpio_backlight_of_match[] = अणु
	अणु .compatible = "gpio-backlight" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, gpio_backlight_of_match);

अटल काष्ठा platक्रमm_driver gpio_backlight_driver = अणु
	.driver		= अणु
		.name		= "gpio-backlight",
		.of_match_table = gpio_backlight_of_match,
	पूर्ण,
	.probe		= gpio_backlight_probe,
पूर्ण;

module_platक्रमm_driver(gpio_backlight_driver);

MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_DESCRIPTION("GPIO-based Backlight Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:gpio-backlight");
