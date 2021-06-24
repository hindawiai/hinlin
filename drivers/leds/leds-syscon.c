<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Generic Syscon LEDs Driver
 *
 * Copyright (c) 2014, Linaro Limited
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/leds.h>

/**
 * काष्ठा syscon_led - state container क्रम syscon based LEDs
 * @cdev: LED class device क्रम this LED
 * @map: regmap to access the syscon device backing this LED
 * @offset: the offset पूर्णांकo the syscon regmap क्रम the LED रेजिस्टर
 * @mask: the bit in the रेजिस्टर corresponding to the LED
 * @state: current state of the LED
 */
काष्ठा syscon_led अणु
	काष्ठा led_classdev cdev;
	काष्ठा regmap *map;
	u32 offset;
	u32 mask;
	bool state;
पूर्ण;

अटल व्योम syscon_led_set(काष्ठा led_classdev *led_cdev,
	क्रमागत led_brightness value)
अणु
	काष्ठा syscon_led *sled =
		container_of(led_cdev, काष्ठा syscon_led, cdev);
	u32 val;
	पूर्णांक ret;

	अगर (value == LED_OFF) अणु
		val = 0;
		sled->state = false;
	पूर्ण अन्यथा अणु
		val = sled->mask;
		sled->state = true;
	पूर्ण

	ret = regmap_update_bits(sled->map, sled->offset, sled->mask, val);
	अगर (ret < 0)
		dev_err(sled->cdev.dev, "error updating LED status\n");
पूर्ण

अटल पूर्णांक syscon_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा led_init_data init_data = अणुपूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev_of_node(dev);
	काष्ठा device *parent;
	काष्ठा regmap *map;
	काष्ठा syscon_led *sled;
	स्थिर अक्षर *state;
	पूर्णांक ret;

	parent = dev->parent;
	अगर (!parent) अणु
		dev_err(dev, "no parent for syscon LED\n");
		वापस -ENODEV;
	पूर्ण
	map = syscon_node_to_regmap(dev_of_node(parent));
	अगर (IS_ERR(map)) अणु
		dev_err(dev, "no regmap for syscon LED parent\n");
		वापस PTR_ERR(map);
	पूर्ण

	sled = devm_kzalloc(dev, माप(*sled), GFP_KERNEL);
	अगर (!sled)
		वापस -ENOMEM;

	sled->map = map;

	अगर (of_property_पढ़ो_u32(np, "offset", &sled->offset))
		वापस -EINVAL;
	अगर (of_property_पढ़ो_u32(np, "mask", &sled->mask))
		वापस -EINVAL;

	state = of_get_property(np, "default-state", शून्य);
	अगर (state) अणु
		अगर (!म_भेद(state, "keep")) अणु
			u32 val;

			ret = regmap_पढ़ो(map, sled->offset, &val);
			अगर (ret < 0)
				वापस ret;
			sled->state = !!(val & sled->mask);
		पूर्ण अन्यथा अगर (!म_भेद(state, "on")) अणु
			sled->state = true;
			ret = regmap_update_bits(map, sled->offset,
						 sled->mask,
						 sled->mask);
			अगर (ret < 0)
				वापस ret;
		पूर्ण अन्यथा अणु
			sled->state = false;
			ret = regmap_update_bits(map, sled->offset,
						 sled->mask, 0);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण
	sled->cdev.brightness_set = syscon_led_set;

	init_data.fwnode = of_fwnode_handle(np);

	ret = devm_led_classdev_रेजिस्टर_ext(dev, &sled->cdev, &init_data);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, sled);
	dev_info(dev, "registered LED %s\n", sled->cdev.name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_syscon_leds_match[] = अणु
	अणु .compatible = "register-bit-led", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver syscon_led_driver = अणु
	.probe		= syscon_led_probe,
	.driver		= अणु
		.name	= "leds-syscon",
		.of_match_table = of_syscon_leds_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(syscon_led_driver);
