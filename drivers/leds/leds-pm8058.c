<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2010, 2011, 2016 The Linux Foundation. All rights reserved.
 */
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>

#घोषणा PM8058_LED_TYPE_COMMON	0x00
#घोषणा PM8058_LED_TYPE_KEYPAD	0x01
#घोषणा PM8058_LED_TYPE_FLASH	0x02

#घोषणा PM8058_LED_TYPE_COMMON_MASK	0xf8
#घोषणा PM8058_LED_TYPE_KEYPAD_MASK	0xf0
#घोषणा PM8058_LED_TYPE_COMMON_SHIFT	3
#घोषणा PM8058_LED_TYPE_KEYPAD_SHIFT	4

काष्ठा pm8058_led अणु
	काष्ठा regmap *map;
	u32 reg;
	u32 ledtype;
	काष्ठा led_classdev cdev;
पूर्ण;

अटल व्योम pm8058_led_set(काष्ठा led_classdev *cled,
	क्रमागत led_brightness value)
अणु
	काष्ठा pm8058_led *led;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक mask = 0;
	अचिन्हित पूर्णांक val = 0;

	led = container_of(cled, काष्ठा pm8058_led, cdev);
	चयन (led->ledtype) अणु
	हाल PM8058_LED_TYPE_COMMON:
		mask = PM8058_LED_TYPE_COMMON_MASK;
		val = value << PM8058_LED_TYPE_COMMON_SHIFT;
		अवरोध;
	हाल PM8058_LED_TYPE_KEYPAD:
	हाल PM8058_LED_TYPE_FLASH:
		mask = PM8058_LED_TYPE_KEYPAD_MASK;
		val = value << PM8058_LED_TYPE_KEYPAD_SHIFT;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ret = regmap_update_bits(led->map, led->reg, mask, val);
	अगर (ret)
		pr_err("Failed to set LED brightness\n");
पूर्ण

अटल क्रमागत led_brightness pm8058_led_get(काष्ठा led_classdev *cled)
अणु
	काष्ठा pm8058_led *led;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	led = container_of(cled, काष्ठा pm8058_led, cdev);

	ret = regmap_पढ़ो(led->map, led->reg, &val);
	अगर (ret) अणु
		pr_err("Failed to get LED brightness\n");
		वापस LED_OFF;
	पूर्ण

	चयन (led->ledtype) अणु
	हाल PM8058_LED_TYPE_COMMON:
		val &= PM8058_LED_TYPE_COMMON_MASK;
		val >>= PM8058_LED_TYPE_COMMON_SHIFT;
		अवरोध;
	हाल PM8058_LED_TYPE_KEYPAD:
	हाल PM8058_LED_TYPE_FLASH:
		val &= PM8058_LED_TYPE_KEYPAD_MASK;
		val >>= PM8058_LED_TYPE_KEYPAD_SHIFT;
		अवरोध;
	शेष:
		val = LED_OFF;
		अवरोध;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक pm8058_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा led_init_data init_data = अणुपूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pm8058_led *led;
	काष्ठा device_node *np;
	पूर्णांक ret;
	काष्ठा regmap *map;
	स्थिर अक्षर *state;
	क्रमागत led_brightness maxbright;

	led = devm_kzalloc(dev, माप(*led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	led->ledtype = (u32)(अचिन्हित दीर्घ)of_device_get_match_data(dev);

	map = dev_get_regmap(dev->parent, शून्य);
	अगर (!map) अणु
		dev_err(dev, "Parent regmap unavailable.\n");
		वापस -ENXIO;
	पूर्ण
	led->map = map;

	np = dev_of_node(dev);

	ret = of_property_पढ़ो_u32(np, "reg", &led->reg);
	अगर (ret) अणु
		dev_err(dev, "no register offset specified\n");
		वापस -EINVAL;
	पूर्ण

	led->cdev.brightness_set = pm8058_led_set;
	led->cdev.brightness_get = pm8058_led_get;
	अगर (led->ledtype == PM8058_LED_TYPE_COMMON)
		maxbright = 31; /* 5 bits */
	अन्यथा
		maxbright = 15; /* 4 bits */
	led->cdev.max_brightness = maxbright;

	state = of_get_property(np, "default-state", शून्य);
	अगर (state) अणु
		अगर (!म_भेद(state, "keep")) अणु
			led->cdev.brightness = pm8058_led_get(&led->cdev);
		पूर्ण अन्यथा अगर (!म_भेद(state, "on")) अणु
			led->cdev.brightness = maxbright;
			pm8058_led_set(&led->cdev, maxbright);
		पूर्ण अन्यथा अणु
			led->cdev.brightness = LED_OFF;
			pm8058_led_set(&led->cdev, LED_OFF);
		पूर्ण
	पूर्ण

	अगर (led->ledtype == PM8058_LED_TYPE_KEYPAD ||
	    led->ledtype == PM8058_LED_TYPE_FLASH)
		led->cdev.flags	= LED_CORE_SUSPENDRESUME;

	init_data.fwnode = of_fwnode_handle(np);

	ret = devm_led_classdev_रेजिस्टर_ext(dev, &led->cdev, &init_data);
	अगर (ret)
		dev_err(dev, "Failed to register LED for %pOF\n", np);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id pm8058_leds_id_table[] = अणु
	अणु
		.compatible = "qcom,pm8058-led",
		.data = (व्योम *)PM8058_LED_TYPE_COMMON
	पूर्ण,
	अणु
		.compatible = "qcom,pm8058-keypad-led",
		.data = (व्योम *)PM8058_LED_TYPE_KEYPAD
	पूर्ण,
	अणु
		.compatible = "qcom,pm8058-flash-led",
		.data = (व्योम *)PM8058_LED_TYPE_FLASH
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pm8058_leds_id_table);

अटल काष्ठा platक्रमm_driver pm8058_led_driver = अणु
	.probe		= pm8058_led_probe,
	.driver		= अणु
		.name	= "pm8058-leds",
		.of_match_table = pm8058_leds_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pm8058_led_driver);

MODULE_DESCRIPTION("PM8058 LEDs driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:pm8058-leds");
