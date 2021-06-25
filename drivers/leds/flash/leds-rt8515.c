<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LED driver क्रम Richtek RT8515 flash/torch white LEDs
 * found on some Samsung mobile phones.
 *
 * This is a 1.5A Boost dual channel driver produced around 2011.
 *
 * The component lacks a datasheet, but in the schematic picture
 * from the LG P970 service manual you can see the connections
 * from the RT8515 to the LED, with two resistors connected
 * from the pins "RFS" and "RTS" to ground.
 *
 * On the LG P970:
 * RFS (resistance flash setting?) is 20 kOhm
 * RTS (resistance torch setting?) is 39 kOhm
 *
 * Some sleuthing finds us the RT9387A which we have a datasheet क्रम:
 * https://अटल5.arrow.com/pdfs/2014/7/27/8/21/12/794/rtt_/manual/94करोwnload_ds.jspprt9387a.jspprt9387a.pdf
 * This apparently works the same way so in theory this driver
 * should cover RT9387A as well. This has not been tested, please
 * update the compatibles अगर you add RT9387A support.
 *
 * Linus Walleij <linus.walleij@linaro.org>
 */
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/led-class-flash.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <media/v4l2-flash-led-class.h>

/* We can provide 15-700 mA out to the LED */
#घोषणा RT8515_MIN_IOUT_MA	15
#घोषणा RT8515_MAX_IOUT_MA	700
/* The maximum पूर्णांकensity is 1-16 क्रम flash and 1-100 क्रम torch */
#घोषणा RT8515_FLASH_MAX	16
#घोषणा RT8515_TORCH_MAX	100

#घोषणा RT8515_TIMEOUT_US	250000U
#घोषणा RT8515_MAX_TIMEOUT_US	300000U

काष्ठा rt8515 अणु
	काष्ठा led_classdev_flash fled;
	काष्ठा device *dev;
	काष्ठा v4l2_flash *v4l2_flash;
	काष्ठा mutex lock;
	काष्ठा regulator *reg;
	काष्ठा gpio_desc *enable_torch;
	काष्ठा gpio_desc *enable_flash;
	काष्ठा समयr_list घातerकरोwn_समयr;
	u32 max_समयout; /* Flash max समयout */
	पूर्णांक flash_max_पूर्णांकensity;
	पूर्णांक torch_max_पूर्णांकensity;
पूर्ण;

अटल काष्ठा rt8515 *to_rt8515(काष्ठा led_classdev_flash *fled)
अणु
	वापस container_of(fled, काष्ठा rt8515, fled);
पूर्ण

अटल व्योम rt8515_gpio_led_off(काष्ठा rt8515 *rt)
अणु
	gpiod_set_value(rt->enable_flash, 0);
	gpiod_set_value(rt->enable_torch, 0);
पूर्ण

अटल व्योम rt8515_gpio_brightness_commit(काष्ठा gpio_desc *gpiod,
					  पूर्णांक brightness)
अणु
	पूर्णांक i;

	/*
	 * Toggling a GPIO line with a small delay increases the
	 * brightness one step at a समय.
	 */
	क्रम (i = 0; i < brightness; i++) अणु
		gpiod_set_value(gpiod, 0);
		udelay(1);
		gpiod_set_value(gpiod, 1);
		udelay(1);
	पूर्ण
पूर्ण

/* This is setting the torch light level */
अटल पूर्णांक rt8515_led_brightness_set(काष्ठा led_classdev *led,
				     क्रमागत led_brightness brightness)
अणु
	काष्ठा led_classdev_flash *fled = lcdev_to_flcdev(led);
	काष्ठा rt8515 *rt = to_rt8515(fled);

	mutex_lock(&rt->lock);

	अगर (brightness == LED_OFF) अणु
		/* Off */
		rt8515_gpio_led_off(rt);
	पूर्ण अन्यथा अगर (brightness < RT8515_TORCH_MAX) अणु
		/* Step it up to movie mode brightness using the flash pin */
		rt8515_gpio_brightness_commit(rt->enable_torch, brightness);
	पूर्ण अन्यथा अणु
		/* Max torch brightness requested */
		gpiod_set_value(rt->enable_torch, 1);
	पूर्ण

	mutex_unlock(&rt->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक rt8515_led_flash_strobe_set(काष्ठा led_classdev_flash *fled,
				       bool state)
अणु
	काष्ठा rt8515 *rt = to_rt8515(fled);
	काष्ठा led_flash_setting *समयout = &fled->समयout;
	पूर्णांक brightness = rt->flash_max_पूर्णांकensity;

	mutex_lock(&rt->lock);

	अगर (state) अणु
		/* Enable LED flash mode and set brightness */
		rt8515_gpio_brightness_commit(rt->enable_flash, brightness);
		/* Set समयout */
		mod_समयr(&rt->घातerकरोwn_समयr,
			  jअगरfies + usecs_to_jअगरfies(समयout->val));
	पूर्ण अन्यथा अणु
		del_समयr_sync(&rt->घातerकरोwn_समयr);
		/* Turn the LED off */
		rt8515_gpio_led_off(rt);
	पूर्ण

	fled->led_cdev.brightness = LED_OFF;
	/* After this the torch LED will be disabled */

	mutex_unlock(&rt->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक rt8515_led_flash_strobe_get(काष्ठा led_classdev_flash *fled,
				       bool *state)
अणु
	काष्ठा rt8515 *rt = to_rt8515(fled);

	*state = समयr_pending(&rt->घातerकरोwn_समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक rt8515_led_flash_समयout_set(काष्ठा led_classdev_flash *fled,
					u32 समयout)
अणु
	/* The समयout is stored in the led-class-flash core */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा led_flash_ops rt8515_flash_ops = अणु
	.strobe_set = rt8515_led_flash_strobe_set,
	.strobe_get = rt8515_led_flash_strobe_get,
	.समयout_set = rt8515_led_flash_समयout_set,
पूर्ण;

अटल व्योम rt8515_घातerकरोwn_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा rt8515 *rt = from_समयr(rt, t, घातerकरोwn_समयr);

	/* Turn the LED off */
	rt8515_gpio_led_off(rt);
पूर्ण

अटल व्योम rt8515_init_flash_समयout(काष्ठा rt8515 *rt)
अणु
	काष्ठा led_classdev_flash *fled = &rt->fled;
	काष्ठा led_flash_setting *s;

	/* Init flash समयout setting */
	s = &fled->समयout;
	s->min = 1;
	s->max = rt->max_समयout;
	s->step = 1;
	/*
	 * Set शेष समयout to RT8515_TIMEOUT_US except अगर
	 * max_समयout from DT is lower.
	 */
	s->val = min(rt->max_समयout, RT8515_TIMEOUT_US);
पूर्ण

#अगर IS_ENABLED(CONFIG_V4L2_FLASH_LED_CLASS)
/* Configure the V2L2 flash subdevice */
अटल व्योम rt8515_init_v4l2_flash_config(काष्ठा rt8515 *rt,
					  काष्ठा v4l2_flash_config *v4l2_sd_cfg)
अणु
	काष्ठा led_classdev *led = &rt->fled.led_cdev;
	काष्ठा led_flash_setting *s;

	strscpy(v4l2_sd_cfg->dev_name, led->dev->kobj.name,
		माप(v4l2_sd_cfg->dev_name));

	/*
	 * Init flash पूर्णांकensity setting: this is a linear scale
	 * capped from the device tree max पूर्णांकensity setting
	 * 1..flash_max_पूर्णांकensity
	 */
	s = &v4l2_sd_cfg->पूर्णांकensity;
	s->min = 1;
	s->max = rt->flash_max_पूर्णांकensity;
	s->step = 1;
	s->val = s->max;
पूर्ण

अटल व्योम rt8515_v4l2_flash_release(काष्ठा rt8515 *rt)
अणु
	v4l2_flash_release(rt->v4l2_flash);
पूर्ण

#अन्यथा
अटल व्योम rt8515_init_v4l2_flash_config(काष्ठा rt8515 *rt,
					  काष्ठा v4l2_flash_config *v4l2_sd_cfg)
अणु
पूर्ण

अटल व्योम rt8515_v4l2_flash_release(काष्ठा rt8515 *rt)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम rt8515_determine_max_पूर्णांकensity(काष्ठा rt8515 *rt,
					   काष्ठा fwnode_handle *led,
					   स्थिर अक्षर *resistance,
					   स्थिर अक्षर *max_ua_prop, पूर्णांक hw_max,
					   पूर्णांक *max_पूर्णांकensity_setting)
अणु
	u32 res = 0; /* Can't be 0 so 0 is undefined */
	u32 ua;
	u32 max_ma;
	पूर्णांक max_पूर्णांकensity;
	पूर्णांक ret;

	fwnode_property_पढ़ो_u32(rt->dev->fwnode, resistance, &res);
	ret = fwnode_property_पढ़ो_u32(led, max_ua_prop, &ua);

	/* Missing info in DT, OK go with hardware maxima */
	अगर (ret || res == 0) अणु
		dev_err(rt->dev,
			"either %s or %s missing from DT, using HW max\n",
			resistance, max_ua_prop);
		max_ma = RT8515_MAX_IOUT_MA;
		max_पूर्णांकensity = hw_max;
		जाओ out_assign_max;
	पूर्ण

	/*
	 * Formula from the datasheet, this is the maximum current
	 * defined by the hardware.
	 */
	max_ma = (5500 * 1000) / res;
	/*
	 * Calculate max पूर्णांकensity (linear scaling)
	 * Formula is ((ua / 1000) / max_ma) * 100, then simplअगरied
	 */
	max_पूर्णांकensity = (ua / 10) / max_ma;

	dev_info(rt->dev,
		 "current restricted from %u to %u mA, max intensity %d/100\n",
		 max_ma, (ua / 1000), max_पूर्णांकensity);

out_assign_max:
	dev_info(rt->dev, "max intensity %d/%d = %d mA\n",
		 max_पूर्णांकensity, hw_max, max_ma);
	*max_पूर्णांकensity_setting = max_पूर्णांकensity;
पूर्ण

अटल पूर्णांक rt8515_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fwnode_handle *child;
	काष्ठा rt8515 *rt;
	काष्ठा led_classdev *led;
	काष्ठा led_classdev_flash *fled;
	काष्ठा led_init_data init_data = अणुपूर्ण;
	काष्ठा v4l2_flash_config v4l2_sd_cfg = अणुपूर्ण;
	पूर्णांक ret;

	rt = devm_kzalloc(dev, माप(*rt), GFP_KERNEL);
	अगर (!rt)
		वापस -ENOMEM;

	rt->dev = dev;
	fled = &rt->fled;
	led = &fled->led_cdev;

	/* ENF - Enable Flash line */
	rt->enable_flash = devm_gpiod_get(dev, "enf", GPIOD_OUT_LOW);
	अगर (IS_ERR(rt->enable_flash))
		वापस dev_err_probe(dev, PTR_ERR(rt->enable_flash),
				     "cannot get ENF (enable flash) GPIO\n");

	/* ENT - Enable Torch line */
	rt->enable_torch = devm_gpiod_get(dev, "ent", GPIOD_OUT_LOW);
	अगर (IS_ERR(rt->enable_torch))
		वापस dev_err_probe(dev, PTR_ERR(rt->enable_torch),
				     "cannot get ENT (enable torch) GPIO\n");

	child = fwnode_get_next_available_child_node(dev->fwnode, शून्य);
	अगर (!child) अणु
		dev_err(dev,
			"No fwnode child node found for connected LED.\n");
		वापस -EINVAL;
	पूर्ण
	init_data.fwnode = child;

	rt8515_determine_max_पूर्णांकensity(rt, child, "richtek,rfs-ohms",
				       "flash-max-microamp",
				       RT8515_FLASH_MAX,
				       &rt->flash_max_पूर्णांकensity);
	rt8515_determine_max_पूर्णांकensity(rt, child, "richtek,rts-ohms",
				       "led-max-microamp",
				       RT8515_TORCH_MAX,
				       &rt->torch_max_पूर्णांकensity);

	ret = fwnode_property_पढ़ो_u32(child, "flash-max-timeout-us",
				       &rt->max_समयout);
	अगर (ret) अणु
		rt->max_समयout = RT8515_MAX_TIMEOUT_US;
		dev_warn(dev,
			 "flash-max-timeout-us property missing\n");
	पूर्ण
	समयr_setup(&rt->घातerकरोwn_समयr, rt8515_घातerकरोwn_समयr, 0);
	rt8515_init_flash_समयout(rt);

	fled->ops = &rt8515_flash_ops;

	led->max_brightness = rt->torch_max_पूर्णांकensity;
	led->brightness_set_blocking = rt8515_led_brightness_set;
	led->flags |= LED_CORE_SUSPENDRESUME | LED_DEV_CAP_FLASH;

	mutex_init(&rt->lock);

	platक्रमm_set_drvdata(pdev, rt);

	ret = devm_led_classdev_flash_रेजिस्टर_ext(dev, fled, &init_data);
	अगर (ret) अणु
		dev_err(dev, "can't register LED %s\n", led->name);
		mutex_destroy(&rt->lock);
		वापस ret;
	पूर्ण

	rt8515_init_v4l2_flash_config(rt, &v4l2_sd_cfg);

	/* Create a V4L2 Flash device अगर V4L2 flash is enabled */
	rt->v4l2_flash = v4l2_flash_init(dev, child, fled, शून्य, &v4l2_sd_cfg);
	अगर (IS_ERR(rt->v4l2_flash)) अणु
		ret = PTR_ERR(rt->v4l2_flash);
		dev_err(dev, "failed to register V4L2 flash device (%d)\n",
			ret);
		/*
		 * Continue without the V4L2 flash
		 * (we still have the classdev)
		 */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt8515_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rt8515 *rt = platक्रमm_get_drvdata(pdev);

	rt8515_v4l2_flash_release(rt);
	del_समयr_sync(&rt->घातerकरोwn_समयr);
	mutex_destroy(&rt->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rt8515_match[] = अणु
	अणु .compatible = "richtek,rt8515", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rt8515_match);

अटल काष्ठा platक्रमm_driver rt8515_driver = अणु
	.driver = अणु
		.name  = "rt8515",
		.of_match_table = rt8515_match,
	पूर्ण,
	.probe  = rt8515_probe,
	.हटाओ = rt8515_हटाओ,
पूर्ण;
module_platक्रमm_driver(rt8515_driver);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("Richtek RT8515 LED driver");
MODULE_LICENSE("GPL");
