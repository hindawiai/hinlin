<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2006 - Florian Fainelli <florian@खोलोwrt.org>
 *
 * Control the Cobalt Qube/RaQ front LED
 */
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

#घोषणा LED_FRONT_LEFT	0x01
#घोषणा LED_FRONT_RIGHT	0x02

अटल व्योम __iomem *led_port;
अटल u8 led_value;

अटल व्योम qube_front_led_set(काष्ठा led_classdev *led_cdev,
			       क्रमागत led_brightness brightness)
अणु
	अगर (brightness)
		led_value = LED_FRONT_LEFT | LED_FRONT_RIGHT;
	अन्यथा
		led_value = ~(LED_FRONT_LEFT | LED_FRONT_RIGHT);
	ग_लिखोb(led_value, led_port);
पूर्ण

अटल काष्ठा led_classdev qube_front_led = अणु
	.name			= "qube::front",
	.brightness		= LED_FULL,
	.brightness_set		= qube_front_led_set,
	.शेष_trigger	= "default-on",
पूर्ण;

अटल पूर्णांक cobalt_qube_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EBUSY;

	led_port = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (!led_port)
		वापस -ENOMEM;

	led_value = LED_FRONT_LEFT | LED_FRONT_RIGHT;
	ग_लिखोb(led_value, led_port);

	वापस devm_led_classdev_रेजिस्टर(&pdev->dev, &qube_front_led);
पूर्ण

अटल काष्ठा platक्रमm_driver cobalt_qube_led_driver = अणु
	.probe	= cobalt_qube_led_probe,
	.driver	= अणु
		.name	= "cobalt-qube-leds",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cobalt_qube_led_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Front LED support for Cobalt Server");
MODULE_AUTHOR("Florian Fainelli <florian@openwrt.org>");
MODULE_ALIAS("platform:cobalt-qube-leds");
