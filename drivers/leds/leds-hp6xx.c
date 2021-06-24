<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED Triggers Core
 * For the HP Jornada 620/660/680/690 handhelds
 *
 * Copyright 2008 Kristoffer Ericson <kristoffer.ericson@gmail.com>
 *     this driver is based on leds-spitz.c by Riअक्षरd Purdie.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <यंत्र/hd64461.h>
#समावेश <mach/hp6xx.h>

अटल व्योम hp6xxled_green_set(काष्ठा led_classdev *led_cdev,
			       क्रमागत led_brightness value)
अणु
	u8 v8;

	v8 = inb(PKDR);
	अगर (value)
		outb(v8 & (~PKDR_LED_GREEN), PKDR);
	अन्यथा
		outb(v8 | PKDR_LED_GREEN, PKDR);
पूर्ण

अटल व्योम hp6xxled_red_set(काष्ठा led_classdev *led_cdev,
			     क्रमागत led_brightness value)
अणु
	u16 v16;

	v16 = inw(HD64461_GPBDR);
	अगर (value)
		outw(v16 & (~HD64461_GPBDR_LED_RED), HD64461_GPBDR);
	अन्यथा
		outw(v16 | HD64461_GPBDR_LED_RED, HD64461_GPBDR);
पूर्ण

अटल काष्ठा led_classdev hp6xx_red_led = अणु
	.name			= "hp6xx:red",
	.शेष_trigger	= "hp6xx-charge",
	.brightness_set		= hp6xxled_red_set,
	.flags			= LED_CORE_SUSPENDRESUME,
पूर्ण;

अटल काष्ठा led_classdev hp6xx_green_led = अणु
	.name			= "hp6xx:green",
	.शेष_trigger	= "disk-activity",
	.brightness_set		= hp6xxled_green_set,
	.flags			= LED_CORE_SUSPENDRESUME,
पूर्ण;

अटल पूर्णांक hp6xxled_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = devm_led_classdev_रेजिस्टर(&pdev->dev, &hp6xx_red_led);
	अगर (ret < 0)
		वापस ret;

	वापस devm_led_classdev_रेजिस्टर(&pdev->dev, &hp6xx_green_led);
पूर्ण

अटल काष्ठा platक्रमm_driver hp6xxled_driver = अणु
	.probe		= hp6xxled_probe,
	.driver		= अणु
		.name		= "hp6xx-led",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(hp6xxled_driver);

MODULE_AUTHOR("Kristoffer Ericson <kristoffer.ericson@gmail.com>");
MODULE_DESCRIPTION("HP Jornada 6xx LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hp6xx-led");
