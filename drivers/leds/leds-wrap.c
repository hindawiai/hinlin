<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LEDs driver क्रम PCEngines WRAP
 *
 * Copyright (C) 2006 Kristian Kielhofner <kris@krisk.org>
 *
 * Based on leds-net48xx.c
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/scx200_gpपन.स>
#समावेश <linux/module.h>

#घोषणा DRVNAME "wrap-led"
#घोषणा WRAP_POWER_LED_GPIO	2
#घोषणा WRAP_ERROR_LED_GPIO	3
#घोषणा WRAP_EXTRA_LED_GPIO	18

अटल काष्ठा platक्रमm_device *pdev;

अटल व्योम wrap_घातer_led_set(काष्ठा led_classdev *led_cdev,
		क्रमागत led_brightness value)
अणु
	अगर (value)
		scx200_gpio_set_low(WRAP_POWER_LED_GPIO);
	अन्यथा
		scx200_gpio_set_high(WRAP_POWER_LED_GPIO);
पूर्ण

अटल व्योम wrap_error_led_set(काष्ठा led_classdev *led_cdev,
		क्रमागत led_brightness value)
अणु
	अगर (value)
		scx200_gpio_set_low(WRAP_ERROR_LED_GPIO);
	अन्यथा
		scx200_gpio_set_high(WRAP_ERROR_LED_GPIO);
पूर्ण

अटल व्योम wrap_extra_led_set(काष्ठा led_classdev *led_cdev,
		क्रमागत led_brightness value)
अणु
	अगर (value)
		scx200_gpio_set_low(WRAP_EXTRA_LED_GPIO);
	अन्यथा
		scx200_gpio_set_high(WRAP_EXTRA_LED_GPIO);
पूर्ण

अटल काष्ठा led_classdev wrap_घातer_led = अणु
	.name			= "wrap::power",
	.brightness_set		= wrap_घातer_led_set,
	.शेष_trigger	= "default-on",
	.flags			= LED_CORE_SUSPENDRESUME,
पूर्ण;

अटल काष्ठा led_classdev wrap_error_led = अणु
	.name		= "wrap::error",
	.brightness_set	= wrap_error_led_set,
	.flags			= LED_CORE_SUSPENDRESUME,
पूर्ण;

अटल काष्ठा led_classdev wrap_extra_led = अणु
	.name           = "wrap::extra",
	.brightness_set = wrap_extra_led_set,
	.flags			= LED_CORE_SUSPENDRESUME,
पूर्ण;

अटल पूर्णांक wrap_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = devm_led_classdev_रेजिस्टर(&pdev->dev, &wrap_घातer_led);
	अगर (ret < 0)
		वापस ret;

	ret = devm_led_classdev_रेजिस्टर(&pdev->dev, &wrap_error_led);
	अगर (ret < 0)
		वापस ret;

	वापस  devm_led_classdev_रेजिस्टर(&pdev->dev, &wrap_extra_led);
पूर्ण

अटल काष्ठा platक्रमm_driver wrap_led_driver = अणु
	.probe		= wrap_led_probe,
	.driver		= अणु
		.name		= DRVNAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init wrap_led_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!scx200_gpio_present()) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&wrap_led_driver);
	अगर (ret < 0)
		जाओ out;

	pdev = platक्रमm_device_रेजिस्टर_simple(DRVNAME, -1, शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		ret = PTR_ERR(pdev);
		platक्रमm_driver_unरेजिस्टर(&wrap_led_driver);
		जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम __निकास wrap_led_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(pdev);
	platक्रमm_driver_unरेजिस्टर(&wrap_led_driver);
पूर्ण

module_init(wrap_led_init);
module_निकास(wrap_led_निकास);

MODULE_AUTHOR("Kristian Kielhofner <kris@krisk.org>");
MODULE_DESCRIPTION("PCEngines WRAP LED driver");
MODULE_LICENSE("GPL");

