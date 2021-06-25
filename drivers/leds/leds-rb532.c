<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LEDs driver क्रम the "User LED" on Routerboard532
 *
 * Copyright (C) 2009 Phil Sutter <n0-1@मुक्तwrt.org>
 *
 * Based on leds-cobalt-qube.c by Florian Fainelly and
 * rb-diag.c (my own standalone driver क्रम both LED and
 * button of Routerboard532).
 */

#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/mach-rc32434/gpपन.स>
#समावेश <यंत्र/mach-rc32434/rb.h>

अटल व्योम rb532_led_set(काष्ठा led_classdev *cdev,
			  क्रमागत led_brightness brightness)
अणु
	अगर (brightness)
		set_latch_u5(LO_ULED, 0);
	अन्यथा
		set_latch_u5(0, LO_ULED);
पूर्ण

अटल क्रमागत led_brightness rb532_led_get(काष्ठा led_classdev *cdev)
अणु
	वापस (get_latch_u5() & LO_ULED) ? LED_FULL : LED_OFF;
पूर्ण

अटल काष्ठा led_classdev rb532_uled = अणु
	.name = "uled",
	.brightness_set = rb532_led_set,
	.brightness_get = rb532_led_get,
	.शेष_trigger = "nand-disk",
पूर्ण;

अटल पूर्णांक rb532_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस led_classdev_रेजिस्टर(&pdev->dev, &rb532_uled);
पूर्ण

अटल पूर्णांक rb532_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	led_classdev_unरेजिस्टर(&rb532_uled);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rb532_led_driver = अणु
	.probe = rb532_led_probe,
	.हटाओ = rb532_led_हटाओ,
	.driver = अणु
		.name = "rb532-led",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rb532_led_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("User LED support for Routerboard532");
MODULE_AUTHOR("Phil Sutter <n0-1@freewrt.org>");
MODULE_ALIAS("platform:rb532-led");
