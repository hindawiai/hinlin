<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2017 Sebastian Reichel <sre@kernel.org>
 */

#समावेश <linux/leds.h>
#समावेश <linux/mfd/motorola-cpcap.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा CPCAP_LED_NO_CURRENT 0x0001

काष्ठा cpcap_led_info अणु
	u16 reg;
	u16 mask;
	u16 limit;
	u16 init_mask;
	u16 init_val;
पूर्ण;

अटल स्थिर काष्ठा cpcap_led_info cpcap_led_red = अणु
	.reg	= CPCAP_REG_REDC,
	.mask	= 0x03FF,
	.limit	= 31,
पूर्ण;

अटल स्थिर काष्ठा cpcap_led_info cpcap_led_green = अणु
	.reg	= CPCAP_REG_GREENC,
	.mask	= 0x03FF,
	.limit	= 31,
पूर्ण;

अटल स्थिर काष्ठा cpcap_led_info cpcap_led_blue = अणु
	.reg	= CPCAP_REG_BLUEC,
	.mask	= 0x03FF,
	.limit	= 31,
पूर्ण;

/* aux display light */
अटल स्थिर काष्ठा cpcap_led_info cpcap_led_adl = अणु
	.reg		= CPCAP_REG_ADLC,
	.mask		= 0x000F,
	.limit		= 1,
	.init_mask	= 0x7FFF,
	.init_val	= 0x5FF0,
पूर्ण;

/* camera privacy led */
अटल स्थिर काष्ठा cpcap_led_info cpcap_led_cp = अणु
	.reg		= CPCAP_REG_CLEDC,
	.mask		= 0x0007,
	.limit		= 1,
	.init_mask	= 0x03FF,
	.init_val	= 0x0008,
पूर्ण;

काष्ठा cpcap_led अणु
	काष्ठा led_classdev led;
	स्थिर काष्ठा cpcap_led_info *info;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा mutex update_lock;
	काष्ठा regulator *vdd;
	bool घातered;

	u32 current_limit;
पूर्ण;

अटल u16 cpcap_led_val(u8 current_limit, u8 duty_cycle)
अणु
	current_limit &= 0x1f; /* 5 bit */
	duty_cycle &= 0x0f; /* 4 bit */

	वापस current_limit << 4 | duty_cycle;
पूर्ण

अटल पूर्णांक cpcap_led_set_घातer(काष्ठा cpcap_led *led, bool status)
अणु
	पूर्णांक err;

	अगर (status == led->घातered)
		वापस 0;

	अगर (status)
		err = regulator_enable(led->vdd);
	अन्यथा
		err = regulator_disable(led->vdd);

	अगर (err) अणु
		dev_err(led->dev, "regulator failure: %d", err);
		वापस err;
	पूर्ण

	led->घातered = status;

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_led_set(काष्ठा led_classdev *ledc, क्रमागत led_brightness value)
अणु
	काष्ठा cpcap_led *led = container_of(ledc, काष्ठा cpcap_led, led);
	पूर्णांक brightness;
	पूर्णांक err;

	mutex_lock(&led->update_lock);

	अगर (value > LED_OFF) अणु
		err = cpcap_led_set_घातer(led, true);
		अगर (err)
			जाओ निकास;
	पूर्ण

	अगर (value == LED_OFF) अणु
		/* Aव्योम HW issue by turning off current beक्रमe duty cycle */
		err = regmap_update_bits(led->regmap,
			led->info->reg, led->info->mask, CPCAP_LED_NO_CURRENT);
		अगर (err) अणु
			dev_err(led->dev, "regmap failed: %d", err);
			जाओ निकास;
		पूर्ण

		brightness = cpcap_led_val(value, LED_OFF);
	पूर्ण अन्यथा अणु
		brightness = cpcap_led_val(value, LED_ON);
	पूर्ण

	err = regmap_update_bits(led->regmap, led->info->reg, led->info->mask,
		brightness);
	अगर (err) अणु
		dev_err(led->dev, "regmap failed: %d", err);
		जाओ निकास;
	पूर्ण

	अगर (value == LED_OFF) अणु
		err = cpcap_led_set_घातer(led, false);
		अगर (err)
			जाओ निकास;
	पूर्ण

निकास:
	mutex_unlock(&led->update_lock);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id cpcap_led_of_match[] = अणु
	अणु .compatible = "motorola,cpcap-led-red", .data = &cpcap_led_red पूर्ण,
	अणु .compatible = "motorola,cpcap-led-green", .data = &cpcap_led_green पूर्ण,
	अणु .compatible = "motorola,cpcap-led-blue",  .data = &cpcap_led_blue पूर्ण,
	अणु .compatible = "motorola,cpcap-led-adl", .data = &cpcap_led_adl पूर्ण,
	अणु .compatible = "motorola,cpcap-led-cp", .data = &cpcap_led_cp पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cpcap_led_of_match);

अटल पूर्णांक cpcap_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cpcap_led *led;
	पूर्णांक err;

	led = devm_kzalloc(&pdev->dev, माप(*led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, led);
	led->info = device_get_match_data(&pdev->dev);
	led->dev = &pdev->dev;

	अगर (led->info->reg == 0x0000) अणु
		dev_err(led->dev, "Unsupported LED");
		वापस -ENODEV;
	पूर्ण

	led->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!led->regmap)
		वापस -ENODEV;

	led->vdd = devm_regulator_get(&pdev->dev, "vdd");
	अगर (IS_ERR(led->vdd)) अणु
		err = PTR_ERR(led->vdd);
		dev_err(led->dev, "Couldn't get regulator: %d", err);
		वापस err;
	पूर्ण

	err = device_property_पढ़ो_string(&pdev->dev, "label", &led->led.name);
	अगर (err) अणु
		dev_err(led->dev, "Couldn't read LED label: %d", err);
		वापस err;
	पूर्ण

	अगर (led->info->init_mask) अणु
		err = regmap_update_bits(led->regmap, led->info->reg,
			led->info->init_mask, led->info->init_val);
		अगर (err) अणु
			dev_err(led->dev, "regmap failed: %d", err);
			वापस err;
		पूर्ण
	पूर्ण

	mutex_init(&led->update_lock);

	led->led.max_brightness = led->info->limit;
	led->led.brightness_set_blocking = cpcap_led_set;
	err = devm_led_classdev_रेजिस्टर(&pdev->dev, &led->led);
	अगर (err) अणु
		dev_err(led->dev, "Couldn't register LED: %d", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cpcap_led_driver = अणु
	.probe = cpcap_led_probe,
	.driver = अणु
		.name = "cpcap-led",
		.of_match_table = cpcap_led_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(cpcap_led_driver);

MODULE_DESCRIPTION("CPCAP LED driver");
MODULE_AUTHOR("Sebastian Reichel <sre@kernel.org>");
MODULE_LICENSE("GPL");
