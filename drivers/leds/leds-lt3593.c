<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2009,2018 Daniel Mack <daniel@zonque.org>

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>

#घोषणा LED_LT3593_NAME "lt3593"

काष्ठा lt3593_led_data अणु
	काष्ठा led_classdev cdev;
	काष्ठा gpio_desc *gpiod;
पूर्ण;

अटल पूर्णांक lt3593_led_set(काष्ठा led_classdev *led_cdev,
			   क्रमागत led_brightness value)
अणु
	काष्ठा lt3593_led_data *led_dat =
		container_of(led_cdev, काष्ठा lt3593_led_data, cdev);
	पूर्णांक pulses;

	/*
	 * The LT3593 resets its पूर्णांकernal current level रेजिस्टर to the maximum
	 * level on the first falling edge on the control pin. Each following
	 * falling edge decreases the current level by 625uA. Up to 32 pulses
	 * can be sent, so the maximum घातer reduction is 20mA.
	 * After a समयout of 128us, the value is taken from the रेजिस्टर and
	 * applied is to the output driver.
	 */

	अगर (value == 0) अणु
		gpiod_set_value_cansleep(led_dat->gpiod, 0);
		वापस 0;
	पूर्ण

	pulses = 32 - (value * 32) / 255;

	अगर (pulses == 0) अणु
		gpiod_set_value_cansleep(led_dat->gpiod, 0);
		mdelay(1);
		gpiod_set_value_cansleep(led_dat->gpiod, 1);
		वापस 0;
	पूर्ण

	gpiod_set_value_cansleep(led_dat->gpiod, 1);

	जबतक (pulses--) अणु
		gpiod_set_value_cansleep(led_dat->gpiod, 0);
		udelay(1);
		gpiod_set_value_cansleep(led_dat->gpiod, 1);
		udelay(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lt3593_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा lt3593_led_data *led_data;
	काष्ठा fwnode_handle *child;
	पूर्णांक ret, state = LEDS_GPIO_DEFSTATE_OFF;
	काष्ठा led_init_data init_data = अणुपूर्ण;
	स्थिर अक्षर *पंचांगp;

	अगर (!dev_of_node(dev))
		वापस -ENODEV;

	led_data = devm_kzalloc(dev, माप(*led_data), GFP_KERNEL);
	अगर (!led_data)
		वापस -ENOMEM;

	अगर (device_get_child_node_count(dev) != 1) अणु
		dev_err(dev, "Device must have exactly one LED sub-node.");
		वापस -EINVAL;
	पूर्ण

	led_data->gpiod = devm_gpiod_get(dev, "lltc,ctrl", 0);
	अगर (IS_ERR(led_data->gpiod))
		वापस PTR_ERR(led_data->gpiod);

	child = device_get_next_child_node(dev, शून्य);

	अगर (!fwnode_property_पढ़ो_string(child, "default-state", &पंचांगp)) अणु
		अगर (!म_भेद(पंचांगp, "on"))
			state = LEDS_GPIO_DEFSTATE_ON;
	पूर्ण

	led_data->cdev.brightness_set_blocking = lt3593_led_set;
	led_data->cdev.brightness = state ? LED_FULL : LED_OFF;

	init_data.fwnode = child;
	init_data.devicename = LED_LT3593_NAME;
	init_data.शेष_label = ":";

	ret = devm_led_classdev_रेजिस्टर_ext(dev, &led_data->cdev, &init_data);
	अगर (ret < 0) अणु
		fwnode_handle_put(child);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, led_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_lt3593_leds_match[] = अणु
	अणु .compatible = "lltc,lt3593", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_lt3593_leds_match);

अटल काष्ठा platक्रमm_driver lt3593_led_driver = अणु
	.probe		= lt3593_led_probe,
	.driver		= अणु
		.name	= "leds-lt3593",
		.of_match_table = of_match_ptr(of_lt3593_leds_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(lt3593_led_driver);

MODULE_AUTHOR("Daniel Mack <daniel@zonque.org>");
MODULE_DESCRIPTION("LED driver for LT3593 controllers");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:leds-lt3593");
