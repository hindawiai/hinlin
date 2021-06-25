<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * leds-regulator.c - LED class driver क्रम regulator driven LEDs.
 *
 * Copyright (C) 2009 Antonio Ospite <ospite@studenti.unina.it>
 *
 * Inspired by leds-wm8350 driver.
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>
#समावेश <linux/leds-regulator.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा to_regulator_led(led_cdev) \
	container_of(led_cdev, काष्ठा regulator_led, cdev)

काष्ठा regulator_led अणु
	काष्ठा led_classdev cdev;
	पूर्णांक enabled;
	काष्ठा mutex mutex;

	काष्ठा regulator *vcc;
पूर्ण;

अटल अंतरभूत पूर्णांक led_regulator_get_max_brightness(काष्ठा regulator *supply)
अणु
	पूर्णांक ret;
	पूर्णांक voltage = regulator_list_voltage(supply, 0);

	अगर (voltage <= 0)
		वापस 1;

	/* even अगर regulator can't change voltages,
	 * we still assume it can change status
	 * and the LED can be turned on and off.
	 */
	ret = regulator_set_voltage(supply, voltage, voltage);
	अगर (ret < 0)
		वापस 1;

	वापस regulator_count_voltages(supply);
पूर्ण

अटल पूर्णांक led_regulator_get_voltage(काष्ठा regulator *supply,
		क्रमागत led_brightness brightness)
अणु
	अगर (brightness == 0)
		वापस -EINVAL;

	वापस regulator_list_voltage(supply, brightness - 1);
पूर्ण


अटल व्योम regulator_led_enable(काष्ठा regulator_led *led)
अणु
	पूर्णांक ret;

	अगर (led->enabled)
		वापस;

	ret = regulator_enable(led->vcc);
	अगर (ret != 0) अणु
		dev_err(led->cdev.dev, "Failed to enable vcc: %d\n", ret);
		वापस;
	पूर्ण

	led->enabled = 1;
पूर्ण

अटल व्योम regulator_led_disable(काष्ठा regulator_led *led)
अणु
	पूर्णांक ret;

	अगर (!led->enabled)
		वापस;

	ret = regulator_disable(led->vcc);
	अगर (ret != 0) अणु
		dev_err(led->cdev.dev, "Failed to disable vcc: %d\n", ret);
		वापस;
	पूर्ण

	led->enabled = 0;
पूर्ण

अटल पूर्णांक regulator_led_brightness_set(काष्ठा led_classdev *led_cdev,
					 क्रमागत led_brightness value)
अणु
	काष्ठा regulator_led *led = to_regulator_led(led_cdev);
	पूर्णांक voltage;
	पूर्णांक ret = 0;

	mutex_lock(&led->mutex);

	अगर (value == LED_OFF) अणु
		regulator_led_disable(led);
		जाओ out;
	पूर्ण

	अगर (led->cdev.max_brightness > 1) अणु
		voltage = led_regulator_get_voltage(led->vcc, value);
		dev_dbg(led->cdev.dev, "brightness: %d voltage: %d\n",
				value, voltage);

		ret = regulator_set_voltage(led->vcc, voltage, voltage);
		अगर (ret != 0)
			dev_err(led->cdev.dev, "Failed to set voltage %d: %d\n",
				voltage, ret);
	पूर्ण

	regulator_led_enable(led);

out:
	mutex_unlock(&led->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक regulator_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा led_regulator_platक्रमm_data *pdata =
			dev_get_platdata(&pdev->dev);
	काष्ठा regulator_led *led;
	काष्ठा regulator *vcc;
	पूर्णांक ret = 0;

	अगर (pdata == शून्य) अणु
		dev_err(&pdev->dev, "no platform data\n");
		वापस -ENODEV;
	पूर्ण

	vcc = devm_regulator_get_exclusive(&pdev->dev, "vled");
	अगर (IS_ERR(vcc)) अणु
		dev_err(&pdev->dev, "Cannot get vcc for %s\n", pdata->name);
		वापस PTR_ERR(vcc);
	पूर्ण

	led = devm_kzalloc(&pdev->dev, माप(*led), GFP_KERNEL);
	अगर (led == शून्य)
		वापस -ENOMEM;

	led->cdev.max_brightness = led_regulator_get_max_brightness(vcc);
	अगर (pdata->brightness > led->cdev.max_brightness) अणु
		dev_err(&pdev->dev, "Invalid default brightness %d\n",
				pdata->brightness);
		वापस -EINVAL;
	पूर्ण

	led->cdev.brightness_set_blocking = regulator_led_brightness_set;
	led->cdev.name = pdata->name;
	led->cdev.flags |= LED_CORE_SUSPENDRESUME;
	led->vcc = vcc;

	/* to handle correctly an alपढ़ोy enabled regulator */
	अगर (regulator_is_enabled(led->vcc))
		led->enabled = 1;

	mutex_init(&led->mutex);

	platक्रमm_set_drvdata(pdev, led);

	ret = led_classdev_रेजिस्टर(&pdev->dev, &led->cdev);
	अगर (ret < 0)
		वापस ret;

	/* to expose the शेष value to userspace */
	led->cdev.brightness = pdata->brightness;

	/* Set the शेष led status */
	regulator_led_brightness_set(&led->cdev, led->cdev.brightness);

	वापस 0;
पूर्ण

अटल पूर्णांक regulator_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regulator_led *led = platक्रमm_get_drvdata(pdev);

	led_classdev_unरेजिस्टर(&led->cdev);
	regulator_led_disable(led);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver regulator_led_driver = अणु
	.driver = अणु
		   .name  = "leds-regulator",
		   पूर्ण,
	.probe  = regulator_led_probe,
	.हटाओ = regulator_led_हटाओ,
पूर्ण;

module_platक्रमm_driver(regulator_led_driver);

MODULE_AUTHOR("Antonio Ospite <ospite@studenti.unina.it>");
MODULE_DESCRIPTION("Regulator driven LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:leds-regulator");
