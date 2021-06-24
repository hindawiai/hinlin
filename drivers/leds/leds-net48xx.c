<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LEDs driver क्रम Soekris net48xx
 *
 * Copyright (C) 2006 Chris Boot <bootc@bootc.net>
 *
 * Based on leds-ams-delta.c
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/nsc_gpपन.स>
#समावेश <linux/scx200_gpपन.स>
#समावेश <linux/module.h>

#घोषणा DRVNAME "net48xx-led"
#घोषणा NET48XX_ERROR_LED_GPIO	20

अटल काष्ठा platक्रमm_device *pdev;

अटल व्योम net48xx_error_led_set(काष्ठा led_classdev *led_cdev,
		क्रमागत led_brightness value)
अणु
	scx200_gpio_ops.gpio_set(NET48XX_ERROR_LED_GPIO, value ? 1 : 0);
पूर्ण

अटल काष्ठा led_classdev net48xx_error_led = अणु
	.name		= "net48xx::error",
	.brightness_set	= net48xx_error_led_set,
	.flags		= LED_CORE_SUSPENDRESUME,
पूर्ण;

अटल पूर्णांक net48xx_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_led_classdev_रेजिस्टर(&pdev->dev, &net48xx_error_led);
पूर्ण

अटल काष्ठा platक्रमm_driver net48xx_led_driver = अणु
	.probe		= net48xx_led_probe,
	.driver		= अणु
		.name		= DRVNAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init net48xx_led_init(व्योम)
अणु
	पूर्णांक ret;

	/* small hack, but scx200_gpio करोesn't set .dev अगर the probe fails */
	अगर (!scx200_gpio_ops.dev) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&net48xx_led_driver);
	अगर (ret < 0)
		जाओ out;

	pdev = platक्रमm_device_रेजिस्टर_simple(DRVNAME, -1, शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		ret = PTR_ERR(pdev);
		platक्रमm_driver_unरेजिस्टर(&net48xx_led_driver);
		जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम __निकास net48xx_led_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(pdev);
	platक्रमm_driver_unरेजिस्टर(&net48xx_led_driver);
पूर्ण

module_init(net48xx_led_init);
module_निकास(net48xx_led_निकास);

MODULE_AUTHOR("Chris Boot <bootc@bootc.net>");
MODULE_DESCRIPTION("Soekris net48xx LED driver");
MODULE_LICENSE("GPL");

