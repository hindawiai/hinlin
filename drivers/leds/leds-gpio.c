<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LEDs driver क्रम GPIOs
 *
 * Copyright (C) 2007 8D Technologies inc.
 * Raphael Assenat <raph@8d.com>
 * Copyright (C) 2008 Freescale Semiconductor, Inc.
 */
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>

काष्ठा gpio_led_data अणु
	काष्ठा led_classdev cdev;
	काष्ठा gpio_desc *gpiod;
	u8 can_sleep;
	u8 blinking;
	gpio_blink_set_t platक्रमm_gpio_blink_set;
पूर्ण;

अटल अंतरभूत काष्ठा gpio_led_data *
			cdev_to_gpio_led_data(काष्ठा led_classdev *led_cdev)
अणु
	वापस container_of(led_cdev, काष्ठा gpio_led_data, cdev);
पूर्ण

अटल व्योम gpio_led_set(काष्ठा led_classdev *led_cdev,
	क्रमागत led_brightness value)
अणु
	काष्ठा gpio_led_data *led_dat = cdev_to_gpio_led_data(led_cdev);
	पूर्णांक level;

	अगर (value == LED_OFF)
		level = 0;
	अन्यथा
		level = 1;

	अगर (led_dat->blinking) अणु
		led_dat->platक्रमm_gpio_blink_set(led_dat->gpiod, level,
						 शून्य, शून्य);
		led_dat->blinking = 0;
	पूर्ण अन्यथा अणु
		अगर (led_dat->can_sleep)
			gpiod_set_value_cansleep(led_dat->gpiod, level);
		अन्यथा
			gpiod_set_value(led_dat->gpiod, level);
	पूर्ण
पूर्ण

अटल पूर्णांक gpio_led_set_blocking(काष्ठा led_classdev *led_cdev,
	क्रमागत led_brightness value)
अणु
	gpio_led_set(led_cdev, value);
	वापस 0;
पूर्ण

अटल पूर्णांक gpio_blink_set(काष्ठा led_classdev *led_cdev,
	अचिन्हित दीर्घ *delay_on, अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा gpio_led_data *led_dat = cdev_to_gpio_led_data(led_cdev);

	led_dat->blinking = 1;
	वापस led_dat->platक्रमm_gpio_blink_set(led_dat->gpiod, GPIO_LED_BLINK,
						delay_on, delay_off);
पूर्ण

अटल पूर्णांक create_gpio_led(स्थिर काष्ठा gpio_led *ढाँचा,
	काष्ठा gpio_led_data *led_dat, काष्ठा device *parent,
	काष्ठा fwnode_handle *fwnode, gpio_blink_set_t blink_set)
अणु
	काष्ठा led_init_data init_data = अणुपूर्ण;
	पूर्णांक ret, state;

	led_dat->cdev.शेष_trigger = ढाँचा->शेष_trigger;
	led_dat->can_sleep = gpiod_cansleep(led_dat->gpiod);
	अगर (!led_dat->can_sleep)
		led_dat->cdev.brightness_set = gpio_led_set;
	अन्यथा
		led_dat->cdev.brightness_set_blocking = gpio_led_set_blocking;
	led_dat->blinking = 0;
	अगर (blink_set) अणु
		led_dat->platक्रमm_gpio_blink_set = blink_set;
		led_dat->cdev.blink_set = gpio_blink_set;
	पूर्ण
	अगर (ढाँचा->शेष_state == LEDS_GPIO_DEFSTATE_KEEP) अणु
		state = gpiod_get_value_cansleep(led_dat->gpiod);
		अगर (state < 0)
			वापस state;
	पूर्ण अन्यथा अणु
		state = (ढाँचा->शेष_state == LEDS_GPIO_DEFSTATE_ON);
	पूर्ण
	led_dat->cdev.brightness = state;
	led_dat->cdev.max_brightness = 1;
	अगर (!ढाँचा->retain_state_suspended)
		led_dat->cdev.flags |= LED_CORE_SUSPENDRESUME;
	अगर (ढाँचा->panic_indicator)
		led_dat->cdev.flags |= LED_PANIC_INDICATOR;
	अगर (ढाँचा->retain_state_shutकरोwn)
		led_dat->cdev.flags |= LED_RETAIN_AT_SHUTDOWN;

	ret = gpiod_direction_output(led_dat->gpiod, state);
	अगर (ret < 0)
		वापस ret;

	अगर (ढाँचा->name) अणु
		led_dat->cdev.name = ढाँचा->name;
		ret = devm_led_classdev_रेजिस्टर(parent, &led_dat->cdev);
	पूर्ण अन्यथा अणु
		init_data.fwnode = fwnode;
		ret = devm_led_classdev_रेजिस्टर_ext(parent, &led_dat->cdev,
						     &init_data);
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा gpio_leds_priv अणु
	पूर्णांक num_leds;
	काष्ठा gpio_led_data leds[];
पूर्ण;

अटल काष्ठा gpio_leds_priv *gpio_leds_create(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fwnode_handle *child;
	काष्ठा gpio_leds_priv *priv;
	पूर्णांक count, ret;

	count = device_get_child_node_count(dev);
	अगर (!count)
		वापस ERR_PTR(-ENODEV);

	priv = devm_kzalloc(dev, काष्ठा_size(priv, leds, count), GFP_KERNEL);
	अगर (!priv)
		वापस ERR_PTR(-ENOMEM);

	device_क्रम_each_child_node(dev, child) अणु
		काष्ठा gpio_led_data *led_dat = &priv->leds[priv->num_leds];
		काष्ठा gpio_led led = अणुपूर्ण;
		स्थिर अक्षर *state = शून्य;

		/*
		 * Acquire gpiod from DT with uninitialized label, which
		 * will be updated after LED class device is रेजिस्टरed,
		 * Only then the final LED name is known.
		 */
		led.gpiod = devm_fwnode_get_gpiod_from_child(dev, शून्य, child,
							     GPIOD_ASIS,
							     शून्य);
		अगर (IS_ERR(led.gpiod)) अणु
			fwnode_handle_put(child);
			वापस ERR_CAST(led.gpiod);
		पूर्ण

		led_dat->gpiod = led.gpiod;

		अगर (!fwnode_property_पढ़ो_string(child, "default-state",
						 &state)) अणु
			अगर (!म_भेद(state, "keep"))
				led.शेष_state = LEDS_GPIO_DEFSTATE_KEEP;
			अन्यथा अगर (!म_भेद(state, "on"))
				led.शेष_state = LEDS_GPIO_DEFSTATE_ON;
			अन्यथा
				led.शेष_state = LEDS_GPIO_DEFSTATE_OFF;
		पूर्ण

		अगर (fwnode_property_present(child, "retain-state-suspended"))
			led.retain_state_suspended = 1;
		अगर (fwnode_property_present(child, "retain-state-shutdown"))
			led.retain_state_shutकरोwn = 1;
		अगर (fwnode_property_present(child, "panic-indicator"))
			led.panic_indicator = 1;

		ret = create_gpio_led(&led, led_dat, dev, child, शून्य);
		अगर (ret < 0) अणु
			fwnode_handle_put(child);
			वापस ERR_PTR(ret);
		पूर्ण
		/* Set gpiod label to match the corresponding LED name. */
		gpiod_set_consumer_name(led_dat->gpiod,
					led_dat->cdev.dev->kobj.name);
		priv->num_leds++;
	पूर्ण

	वापस priv;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_gpio_leds_match[] = अणु
	अणु .compatible = "gpio-leds", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_gpio_leds_match);

अटल काष्ठा gpio_desc *gpio_led_get_gpiod(काष्ठा device *dev, पूर्णांक idx,
					    स्थिर काष्ठा gpio_led *ढाँचा)
अणु
	काष्ठा gpio_desc *gpiod;
	अचिन्हित दीर्घ flags = GPIOF_OUT_INIT_LOW;
	पूर्णांक ret;

	/*
	 * This means the LED करोes not come from the device tree
	 * or ACPI, so let's try just getting it by index from the
	 * device, this will hit the board file, अगर any and get
	 * the GPIO from there.
	 */
	gpiod = devm_gpiod_get_index(dev, शून्य, idx, GPIOD_OUT_LOW);
	अगर (!IS_ERR(gpiod)) अणु
		gpiod_set_consumer_name(gpiod, ढाँचा->name);
		वापस gpiod;
	पूर्ण
	अगर (PTR_ERR(gpiod) != -ENOENT)
		वापस gpiod;

	/*
	 * This is the legacy code path क्रम platक्रमm code that
	 * still uses GPIO numbers. Ultimately we would like to get
	 * rid of this block completely.
	 */

	/* skip leds that aren't available */
	अगर (!gpio_is_valid(ढाँचा->gpio))
		वापस ERR_PTR(-ENOENT);

	अगर (ढाँचा->active_low)
		flags |= GPIOF_ACTIVE_LOW;

	ret = devm_gpio_request_one(dev, ढाँचा->gpio, flags,
				    ढाँचा->name);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	gpiod = gpio_to_desc(ढाँचा->gpio);
	अगर (!gpiod)
		वापस ERR_PTR(-EINVAL);

	वापस gpiod;
पूर्ण

अटल पूर्णांक gpio_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_led_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा gpio_leds_priv *priv;
	पूर्णांक i, ret = 0;

	अगर (pdata && pdata->num_leds) अणु
		priv = devm_kzalloc(&pdev->dev, काष्ठा_size(priv, leds, pdata->num_leds),
				    GFP_KERNEL);
		अगर (!priv)
			वापस -ENOMEM;

		priv->num_leds = pdata->num_leds;
		क्रम (i = 0; i < priv->num_leds; i++) अणु
			स्थिर काष्ठा gpio_led *ढाँचा = &pdata->leds[i];
			काष्ठा gpio_led_data *led_dat = &priv->leds[i];

			अगर (ढाँचा->gpiod)
				led_dat->gpiod = ढाँचा->gpiod;
			अन्यथा
				led_dat->gpiod =
					gpio_led_get_gpiod(&pdev->dev,
							   i, ढाँचा);
			अगर (IS_ERR(led_dat->gpiod)) अणु
				dev_info(&pdev->dev, "Skipping unavailable LED gpio %d (%s)\n",
					 ढाँचा->gpio, ढाँचा->name);
				जारी;
			पूर्ण

			ret = create_gpio_led(ढाँचा, led_dat,
					      &pdev->dev, शून्य,
					      pdata->gpio_blink_set);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		priv = gpio_leds_create(pdev);
		अगर (IS_ERR(priv))
			वापस PTR_ERR(priv);
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	वापस 0;
पूर्ण

अटल व्योम gpio_led_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_leds_priv *priv = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_leds; i++) अणु
		काष्ठा gpio_led_data *led = &priv->leds[i];

		अगर (!(led->cdev.flags & LED_RETAIN_AT_SHUTDOWN))
			gpio_led_set(&led->cdev, LED_OFF);
	पूर्ण
पूर्ण

अटल काष्ठा platक्रमm_driver gpio_led_driver = अणु
	.probe		= gpio_led_probe,
	.shutकरोwn	= gpio_led_shutकरोwn,
	.driver		= अणु
		.name	= "leds-gpio",
		.of_match_table = of_gpio_leds_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(gpio_led_driver);

MODULE_AUTHOR("Raphael Assenat <raph@8d.com>, Trent Piepho <tpiepho@freescale.com>");
MODULE_DESCRIPTION("GPIO LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:leds-gpio");
