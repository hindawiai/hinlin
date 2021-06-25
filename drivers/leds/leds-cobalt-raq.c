<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  LEDs driver क्रम the Cobalt Raq series.
 *
 *  Copyright (C) 2007  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/export.h>

#घोषणा LED_WEB		0x04
#घोषणा LED_POWER_OFF	0x08

अटल व्योम __iomem *led_port;
अटल u8 led_value;
अटल DEFINE_SPINLOCK(led_value_lock);

अटल व्योम raq_web_led_set(काष्ठा led_classdev *led_cdev,
			    क्रमागत led_brightness brightness)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&led_value_lock, flags);

	अगर (brightness)
		led_value |= LED_WEB;
	अन्यथा
		led_value &= ~LED_WEB;
	ग_लिखोb(led_value, led_port);

	spin_unlock_irqrestore(&led_value_lock, flags);
पूर्ण

अटल काष्ठा led_classdev raq_web_led = अणु
	.name		= "raq::web",
	.brightness_set	= raq_web_led_set,
पूर्ण;

अटल व्योम raq_घातer_off_led_set(काष्ठा led_classdev *led_cdev,
				  क्रमागत led_brightness brightness)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&led_value_lock, flags);

	अगर (brightness)
		led_value |= LED_POWER_OFF;
	अन्यथा
		led_value &= ~LED_POWER_OFF;
	ग_लिखोb(led_value, led_port);

	spin_unlock_irqrestore(&led_value_lock, flags);
पूर्ण

अटल काष्ठा led_classdev raq_घातer_off_led = अणु
	.name			= "raq::power-off",
	.brightness_set		= raq_घातer_off_led_set,
	.शेष_trigger	= "power-off",
पूर्ण;

अटल पूर्णांक cobalt_raq_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	पूर्णांक retval;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EBUSY;

	led_port = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (!led_port)
		वापस -ENOMEM;

	retval = led_classdev_रेजिस्टर(&pdev->dev, &raq_घातer_off_led);
	अगर (retval)
		जाओ err_null;

	retval = led_classdev_रेजिस्टर(&pdev->dev, &raq_web_led);
	अगर (retval)
		जाओ err_unरेजिस्टर;

	वापस 0;

err_unरेजिस्टर:
	led_classdev_unरेजिस्टर(&raq_घातer_off_led);

err_null:
	led_port = शून्य;

	वापस retval;
पूर्ण

अटल काष्ठा platक्रमm_driver cobalt_raq_led_driver = अणु
	.probe	= cobalt_raq_led_probe,
	.driver = अणु
		.name	= "cobalt-raq-leds",
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(cobalt_raq_led_driver);
