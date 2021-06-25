<शैली गुरु>
// SPDX-License-Identअगरier: BSD-2-Clause OR GPL-2.0-or-later
/*
 * Dell Wyse 3020 a.k.a. "Ariel" Embedded Controller LED Driver
 *
 * Copyright (C) 2020 Lubomir Rपूर्णांकel
 */

#समावेश <linux/module.h>
#समावेश <linux/leds.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of_platक्रमm.h>

क्रमागत ec_index अणु
	EC_BLUE_LED	= 0x01,
	EC_AMBER_LED	= 0x02,
	EC_GREEN_LED	= 0x03,
पूर्ण;

क्रमागत अणु
	EC_LED_OFF	= 0x00,
	EC_LED_STILL	= 0x01,
	EC_LED_FADE	= 0x02,
	EC_LED_BLINK	= 0x03,
पूर्ण;

काष्ठा ariel_led अणु
	काष्ठा regmap *ec_ram;
	क्रमागत ec_index ec_index;
	काष्ठा led_classdev led_cdev;
पूर्ण;

#घोषणा led_cdev_to_ariel_led(c) container_of(c, काष्ठा ariel_led, led_cdev)

अटल क्रमागत led_brightness ariel_led_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा ariel_led *led = led_cdev_to_ariel_led(led_cdev);
	अचिन्हित पूर्णांक led_status = 0;

	अगर (regmap_पढ़ो(led->ec_ram, led->ec_index, &led_status))
		वापस LED_OFF;

	अगर (led_status == EC_LED_STILL)
		वापस LED_FULL;
	अन्यथा
		वापस LED_OFF;
पूर्ण

अटल व्योम ariel_led_set(काष्ठा led_classdev *led_cdev,
			  क्रमागत led_brightness brightness)
अणु
	काष्ठा ariel_led *led = led_cdev_to_ariel_led(led_cdev);

	अगर (brightness == LED_OFF)
		regmap_ग_लिखो(led->ec_ram, led->ec_index, EC_LED_OFF);
	अन्यथा
		regmap_ग_लिखो(led->ec_ram, led->ec_index, EC_LED_STILL);
पूर्ण

अटल पूर्णांक ariel_blink_set(काष्ठा led_classdev *led_cdev,
			   अचिन्हित दीर्घ *delay_on, अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा ariel_led *led = led_cdev_to_ariel_led(led_cdev);

	अगर (*delay_on == 0 && *delay_off == 0)
		वापस -EINVAL;

	अगर (*delay_on == 0) अणु
		regmap_ग_लिखो(led->ec_ram, led->ec_index, EC_LED_OFF);
	पूर्ण अन्यथा अगर (*delay_off == 0) अणु
		regmap_ग_लिखो(led->ec_ram, led->ec_index, EC_LED_STILL);
	पूर्ण अन्यथा अणु
		*delay_on = 500;
		*delay_off = 500;
		regmap_ग_लिखो(led->ec_ram, led->ec_index, EC_LED_BLINK);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा NLEDS 3

अटल पूर्णांक ariel_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ariel_led *leds;
	काष्ठा regmap *ec_ram;
	पूर्णांक ret;
	पूर्णांक i;

	ec_ram = dev_get_regmap(dev->parent, "ec_ram");
	अगर (!ec_ram)
		वापस -ENODEV;

	leds = devm_kसुस्मृति(dev, NLEDS, माप(*leds), GFP_KERNEL);
	अगर (!leds)
		वापस -ENOMEM;

	leds[0].ec_index = EC_BLUE_LED;
	leds[0].led_cdev.name = "blue:power";
	leds[0].led_cdev.शेष_trigger = "default-on";

	leds[1].ec_index = EC_AMBER_LED;
	leds[1].led_cdev.name = "amber:status";

	leds[2].ec_index = EC_GREEN_LED;
	leds[2].led_cdev.name = "green:status";
	leds[2].led_cdev.शेष_trigger = "default-on";

	क्रम (i = 0; i < NLEDS; i++) अणु
		leds[i].ec_ram = ec_ram;
		leds[i].led_cdev.brightness_get = ariel_led_get;
		leds[i].led_cdev.brightness_set = ariel_led_set;
		leds[i].led_cdev.blink_set = ariel_blink_set;

		ret = devm_led_classdev_रेजिस्टर(dev, &leds[i].led_cdev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ariel_led_driver = अणु
	.probe = ariel_led_probe,
	.driver = अणु
		.name = "dell-wyse-ariel-led",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ariel_led_driver);

MODULE_AUTHOR("Lubomir Rintel <lkundrak@v3.sk>");
MODULE_DESCRIPTION("Dell Wyse 3020 Status LEDs Driver");
MODULE_LICENSE("Dual BSD/GPL");
