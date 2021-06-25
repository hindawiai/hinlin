<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/leds/leds-locomo.c
 *
 * Copyright (C) 2005 John Lenz <lenz@cs.wisc.edu>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/leds.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/hardware/locomo.h>

अटल व्योम locomoled_brightness_set(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness value, पूर्णांक offset)
अणु
	काष्ठा locomo_dev *locomo_dev = LOCOMO_DEV(led_cdev->dev->parent);
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (value)
		locomo_ग_लिखोl(LOCOMO_LPT_TOFH, locomo_dev->mapbase + offset);
	अन्यथा
		locomo_ग_लिखोl(LOCOMO_LPT_TOFL, locomo_dev->mapbase + offset);
	local_irq_restore(flags);
पूर्ण

अटल व्योम locomoled_brightness_set0(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness value)
अणु
	locomoled_brightness_set(led_cdev, value, LOCOMO_LPT0);
पूर्ण

अटल व्योम locomoled_brightness_set1(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness value)
अणु
	locomoled_brightness_set(led_cdev, value, LOCOMO_LPT1);
पूर्ण

अटल काष्ठा led_classdev locomo_led0 = अणु
	.name			= "locomo:amber:charge",
	.शेष_trigger	= "main-battery-charging",
	.brightness_set		= locomoled_brightness_set0,
पूर्ण;

अटल काष्ठा led_classdev locomo_led1 = अणु
	.name			= "locomo:green:mail",
	.शेष_trigger	= "nand-disk",
	.brightness_set		= locomoled_brightness_set1,
पूर्ण;

अटल पूर्णांक locomoled_probe(काष्ठा locomo_dev *ldev)
अणु
	पूर्णांक ret;

	ret = devm_led_classdev_रेजिस्टर(&ldev->dev, &locomo_led0);
	अगर (ret < 0)
		वापस ret;

	वापस  devm_led_classdev_रेजिस्टर(&ldev->dev, &locomo_led1);
पूर्ण


अटल काष्ठा locomo_driver locomoled_driver = अणु
	.drv = अणु
		.name = "locomoled"
	पूर्ण,
	.devid	= LOCOMO_DEVID_LED,
	.probe	= locomoled_probe,
पूर्ण;

अटल पूर्णांक __init locomoled_init(व्योम)
अणु
	वापस locomo_driver_रेजिस्टर(&locomoled_driver);
पूर्ण
module_init(locomoled_init);

MODULE_AUTHOR("John Lenz <lenz@cs.wisc.edu>");
MODULE_DESCRIPTION("Locomo LED driver");
MODULE_LICENSE("GPL");
