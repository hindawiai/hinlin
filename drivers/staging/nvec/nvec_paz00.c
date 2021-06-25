<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * nvec_paz00: OEM specअगरic driver क्रम Compal PAZ00 based devices
 *
 * Copyright (C) 2011 The AC100 Kernel Team <ac100@lists.launchpad.net>
 *
 * Authors:  Ilya Petrov <ilya.muromec@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "nvec.h"

#घोषणा to_nvec_led(led_cdev) \
	container_of(led_cdev, काष्ठा nvec_led, cdev)

#घोषणा NVEC_LED_REQ अणु'\x0d', '\x10', '\x45', '\x10', '\x00'पूर्ण

#घोषणा NVEC_LED_MAX 8

काष्ठा nvec_led अणु
	काष्ठा led_classdev cdev;
	काष्ठा nvec_chip *nvec;
पूर्ण;

अटल व्योम nvec_led_brightness_set(काष्ठा led_classdev *led_cdev,
				    क्रमागत led_brightness value)
अणु
	काष्ठा nvec_led *led = to_nvec_led(led_cdev);
	अचिन्हित अक्षर buf[] = NVEC_LED_REQ;

	buf[4] = value;

	nvec_ग_लिखो_async(led->nvec, buf, माप(buf));

	led->cdev.brightness = value;
पूर्ण

अटल पूर्णांक nvec_paz00_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nvec_chip *nvec = dev_get_drvdata(pdev->dev.parent);
	काष्ठा nvec_led *led;
	पूर्णांक ret = 0;

	led = devm_kzalloc(&pdev->dev, माप(*led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	led->cdev.max_brightness = NVEC_LED_MAX;

	led->cdev.brightness_set = nvec_led_brightness_set;
	led->cdev.name = "paz00-led";
	led->cdev.flags |= LED_CORE_SUSPENDRESUME;
	led->nvec = nvec;

	platक्रमm_set_drvdata(pdev, led);

	ret = devm_led_classdev_रेजिस्टर(&pdev->dev, &led->cdev);
	अगर (ret < 0)
		वापस ret;

	/* to expose the शेष value to userspace */
	led->cdev.brightness = 0;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver nvec_paz00_driver = अणु
	.probe  = nvec_paz00_probe,
	.driver = अणु
		.name  = "nvec-paz00",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(nvec_paz00_driver);

MODULE_AUTHOR("Ilya Petrov <ilya.muromec@gmail.com>");
MODULE_DESCRIPTION("Tegra NVEC PAZ00 driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:nvec-paz00");
