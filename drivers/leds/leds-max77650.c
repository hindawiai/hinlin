<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2018 BayLibre SAS
// Author: Bartosz Golaszewski <bgolaszewski@baylibre.com>
//
// LED driver क्रम MAXIM 77650/77651 अक्षरger/घातer-supply.

#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/mfd/max77650.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा MAX77650_LED_NUM_LEDS		3

#घोषणा MAX77650_LED_A_BASE		0x40
#घोषणा MAX77650_LED_B_BASE		0x43

#घोषणा MAX77650_LED_BR_MASK		GENMASK(4, 0)
#घोषणा MAX77650_LED_EN_MASK		GENMASK(7, 6)

#घोषणा MAX77650_LED_MAX_BRIGHTNESS	MAX77650_LED_BR_MASK

/* Enable EN_LED_MSTR. */
#घोषणा MAX77650_LED_TOP_DEFAULT	BIT(0)

#घोषणा MAX77650_LED_ENABLE		GENMASK(7, 6)
#घोषणा MAX77650_LED_DISABLE		0x00

#घोषणा MAX77650_LED_A_DEFAULT		MAX77650_LED_DISABLE
/* 100% on duty */
#घोषणा MAX77650_LED_B_DEFAULT		GENMASK(3, 0)

काष्ठा max77650_led अणु
	काष्ठा led_classdev cdev;
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक regA;
	अचिन्हित पूर्णांक regB;
पूर्ण;

अटल काष्ठा max77650_led *max77650_to_led(काष्ठा led_classdev *cdev)
अणु
	वापस container_of(cdev, काष्ठा max77650_led, cdev);
पूर्ण

अटल पूर्णांक max77650_led_brightness_set(काष्ठा led_classdev *cdev,
				       क्रमागत led_brightness brightness)
अणु
	काष्ठा max77650_led *led = max77650_to_led(cdev);
	पूर्णांक val, mask;

	mask = MAX77650_LED_BR_MASK | MAX77650_LED_EN_MASK;

	अगर (brightness == LED_OFF)
		val = MAX77650_LED_DISABLE;
	अन्यथा
		val = MAX77650_LED_ENABLE | brightness;

	वापस regmap_update_bits(led->map, led->regA, mask, val);
पूर्ण

अटल पूर्णांक max77650_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fwnode_handle *child;
	काष्ठा max77650_led *leds, *led;
	काष्ठा device *dev;
	काष्ठा regmap *map;
	पूर्णांक rv, num_leds;
	u32 reg;

	dev = &pdev->dev;

	leds = devm_kसुस्मृति(dev, माप(*leds),
			    MAX77650_LED_NUM_LEDS, GFP_KERNEL);
	अगर (!leds)
		वापस -ENOMEM;

	map = dev_get_regmap(dev->parent, शून्य);
	अगर (!map)
		वापस -ENODEV;

	num_leds = device_get_child_node_count(dev);
	अगर (!num_leds || num_leds > MAX77650_LED_NUM_LEDS)
		वापस -ENODEV;

	device_क्रम_each_child_node(dev, child) अणु
		काष्ठा led_init_data init_data = अणुपूर्ण;

		rv = fwnode_property_पढ़ो_u32(child, "reg", &reg);
		अगर (rv || reg >= MAX77650_LED_NUM_LEDS) अणु
			rv = -EINVAL;
			जाओ err_node_put;
		पूर्ण

		led = &leds[reg];
		led->map = map;
		led->regA = MAX77650_LED_A_BASE + reg;
		led->regB = MAX77650_LED_B_BASE + reg;
		led->cdev.brightness_set_blocking = max77650_led_brightness_set;
		led->cdev.max_brightness = MAX77650_LED_MAX_BRIGHTNESS;

		init_data.fwnode = child;
		init_data.devicename = "max77650";
		/* क्रम backwards compatibility अगर `label` is not present */
		init_data.शेष_label = ":";

		rv = devm_led_classdev_रेजिस्टर_ext(dev, &led->cdev,
						    &init_data);
		अगर (rv)
			जाओ err_node_put;

		rv = regmap_ग_लिखो(map, led->regA, MAX77650_LED_A_DEFAULT);
		अगर (rv)
			जाओ err_node_put;

		rv = regmap_ग_लिखो(map, led->regB, MAX77650_LED_B_DEFAULT);
		अगर (rv)
			जाओ err_node_put;
	पूर्ण

	वापस regmap_ग_लिखो(map,
			    MAX77650_REG_CNFG_LED_TOP,
			    MAX77650_LED_TOP_DEFAULT);
err_node_put:
	fwnode_handle_put(child);
	वापस rv;
पूर्ण

अटल स्थिर काष्ठा of_device_id max77650_led_of_match[] = अणु
	अणु .compatible = "maxim,max77650-led" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max77650_led_of_match);

अटल काष्ठा platक्रमm_driver max77650_led_driver = अणु
	.driver = अणु
		.name = "max77650-led",
		.of_match_table = max77650_led_of_match,
	पूर्ण,
	.probe = max77650_led_probe,
पूर्ण;
module_platक्रमm_driver(max77650_led_driver);

MODULE_DESCRIPTION("MAXIM 77650/77651 LED driver");
MODULE_AUTHOR("Bartosz Golaszewski <bgolaszewski@baylibre.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:max77650-led");
