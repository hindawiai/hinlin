<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  MEN 14F021P00 Board Management Controller (BMC) LEDs Driver.
 *
 *  This is the core LED driver of the MEN 14F021P00 BMC.
 *  There are four LEDs available which can be चयनed on and off.
 *  STATUS LED, HOT SWAP LED, USER LED 1, USER LED 2
 *
 *  Copyright (C) 2014 MEN Mikro Elektronik Nuernberg GmbH
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <linux/i2c.h>

#घोषणा BMC_CMD_LED_GET_SET	0xA0
#घोषणा BMC_BIT_LED_STATUS	BIT(0)
#घोषणा BMC_BIT_LED_HOTSWAP	BIT(1)
#घोषणा BMC_BIT_LED_USER1	BIT(2)
#घोषणा BMC_BIT_LED_USER2	BIT(3)

काष्ठा menf21bmc_led अणु
	काष्ठा led_classdev cdev;
	u8 led_bit;
	स्थिर अक्षर *name;
	काष्ठा i2c_client *i2c_client;
पूर्ण;

अटल काष्ठा menf21bmc_led leds[] = अणु
	अणु
		.name = "menf21bmc:led_status",
		.led_bit = BMC_BIT_LED_STATUS,
	पूर्ण,
	अणु
		.name = "menf21bmc:led_hotswap",
		.led_bit = BMC_BIT_LED_HOTSWAP,
	पूर्ण,
	अणु
		.name = "menf21bmc:led_user1",
		.led_bit = BMC_BIT_LED_USER1,
	पूर्ण,
	अणु
		.name = "menf21bmc:led_user2",
		.led_bit = BMC_BIT_LED_USER2,
	पूर्ण
पूर्ण;

अटल DEFINE_MUTEX(led_lock);

अटल व्योम
menf21bmc_led_set(काष्ठा led_classdev *led_cdev, क्रमागत led_brightness value)
अणु
	पूर्णांक led_val;
	काष्ठा menf21bmc_led *led = container_of(led_cdev,
					काष्ठा menf21bmc_led, cdev);

	mutex_lock(&led_lock);
	led_val = i2c_smbus_पढ़ो_byte_data(led->i2c_client,
					   BMC_CMD_LED_GET_SET);
	अगर (led_val < 0)
		जाओ err_out;

	अगर (value == LED_OFF)
		led_val &= ~led->led_bit;
	अन्यथा
		led_val |= led->led_bit;

	i2c_smbus_ग_लिखो_byte_data(led->i2c_client,
				  BMC_CMD_LED_GET_SET, led_val);
err_out:
	mutex_unlock(&led_lock);
पूर्ण

अटल पूर्णांक menf21bmc_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	काष्ठा i2c_client *i2c_client = to_i2c_client(pdev->dev.parent);

	क्रम (i = 0; i < ARRAY_SIZE(leds); i++) अणु
		leds[i].cdev.name = leds[i].name;
		leds[i].cdev.brightness_set = menf21bmc_led_set;
		leds[i].i2c_client = i2c_client;
		ret = devm_led_classdev_रेजिस्टर(&pdev->dev, &leds[i].cdev);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "failed to register LED device\n");
			वापस ret;
		पूर्ण
	पूर्ण
	dev_info(&pdev->dev, "MEN 140F21P00 BMC LED device enabled\n");

	वापस 0;

पूर्ण

अटल काष्ठा platक्रमm_driver menf21bmc_led = अणु
	.probe		= menf21bmc_led_probe,
	.driver		= अणु
		.name		= "menf21bmc_led",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(menf21bmc_led);

MODULE_AUTHOR("Andreas Werner <andreas.werner@men.de>");
MODULE_DESCRIPTION("MEN 14F021P00 BMC led driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:menf21bmc_led");
