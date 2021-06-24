<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED driver क्रम WM8350 driven LEDS.
 *
 * Copyright(C) 2007, 2008 Wolfson Microelectronics PLC.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <linux/err.h>
#समावेश <linux/mfd/wm8350/pmic.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

/* Microamps */
अटल स्थिर पूर्णांक isink_cur[] = अणु
	4,
	5,
	6,
	7,
	8,
	10,
	11,
	14,
	16,
	19,
	23,
	27,
	32,
	39,
	46,
	54,
	65,
	77,
	92,
	109,
	130,
	154,
	183,
	218,
	259,
	308,
	367,
	436,
	518,
	616,
	733,
	872,
	1037,
	1233,
	1466,
	1744,
	2073,
	2466,
	2933,
	3487,
	4147,
	4932,
	5865,
	6975,
	8294,
	9864,
	11730,
	13949,
	16589,
	19728,
	23460,
	27899,
	33178,
	39455,
	46920,
	55798,
	66355,
	78910,
	93840,
	111596,
	132710,
	157820,
	187681,
	223191
पूर्ण;

#घोषणा to_wm8350_led(led_cdev) \
	container_of(led_cdev, काष्ठा wm8350_led, cdev)

अटल पूर्णांक wm8350_led_enable(काष्ठा wm8350_led *led)
अणु
	पूर्णांक ret = 0;

	अगर (led->enabled)
		वापस ret;

	ret = regulator_enable(led->isink);
	अगर (ret != 0) अणु
		dev_err(led->cdev.dev, "Failed to enable ISINK: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_enable(led->dcdc);
	अगर (ret != 0) अणु
		dev_err(led->cdev.dev, "Failed to enable DCDC: %d\n", ret);
		regulator_disable(led->isink);
		वापस ret;
	पूर्ण

	led->enabled = 1;

	वापस ret;
पूर्ण

अटल पूर्णांक wm8350_led_disable(काष्ठा wm8350_led *led)
अणु
	पूर्णांक ret = 0;

	अगर (!led->enabled)
		वापस ret;

	ret = regulator_disable(led->dcdc);
	अगर (ret != 0) अणु
		dev_err(led->cdev.dev, "Failed to disable DCDC: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_disable(led->isink);
	अगर (ret != 0) अणु
		dev_err(led->cdev.dev, "Failed to disable ISINK: %d\n", ret);
		ret = regulator_enable(led->dcdc);
		अगर (ret != 0)
			dev_err(led->cdev.dev, "Failed to reenable DCDC: %d\n",
				ret);
		वापस ret;
	पूर्ण

	led->enabled = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक wm8350_led_set(काष्ठा led_classdev *led_cdev,
			   क्रमागत led_brightness value)
अणु
	काष्ठा wm8350_led *led = to_wm8350_led(led_cdev);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	पूर्णांक uA;

	led->value = value;

	spin_lock_irqsave(&led->value_lock, flags);

	अगर (led->value == LED_OFF) अणु
		spin_unlock_irqrestore(&led->value_lock, flags);
		वापस wm8350_led_disable(led);
	पूर्ण

	/* This scales linearly पूर्णांकo the index of valid current
	 * settings which results in a linear scaling of perceived
	 * brightness due to the non-linear current settings provided
	 * by the hardware.
	 */
	uA = (led->max_uA_index * led->value) / LED_FULL;
	spin_unlock_irqrestore(&led->value_lock, flags);
	BUG_ON(uA >= ARRAY_SIZE(isink_cur));

	ret = regulator_set_current_limit(led->isink, isink_cur[uA],
					  isink_cur[uA]);
	अगर (ret != 0) अणु
		dev_err(led->cdev.dev, "Failed to set %duA: %d\n",
			isink_cur[uA], ret);
		वापस ret;
	पूर्ण

	वापस wm8350_led_enable(led);
पूर्ण

अटल व्योम wm8350_led_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8350_led *led = platक्रमm_get_drvdata(pdev);

	led->value = LED_OFF;
	wm8350_led_disable(led);
पूर्ण

अटल पूर्णांक wm8350_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regulator *isink, *dcdc;
	काष्ठा wm8350_led *led;
	काष्ठा wm8350_led_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	पूर्णांक i;

	अगर (pdata == शून्य) अणु
		dev_err(&pdev->dev, "no platform data\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pdata->max_uA < isink_cur[0]) अणु
		dev_err(&pdev->dev, "Invalid maximum current %duA\n",
			pdata->max_uA);
		वापस -EINVAL;
	पूर्ण

	isink = devm_regulator_get(&pdev->dev, "led_isink");
	अगर (IS_ERR(isink)) अणु
		dev_err(&pdev->dev, "%s: can't get ISINK\n", __func__);
		वापस PTR_ERR(isink);
	पूर्ण

	dcdc = devm_regulator_get(&pdev->dev, "led_vcc");
	अगर (IS_ERR(dcdc)) अणु
		dev_err(&pdev->dev, "%s: can't get DCDC\n", __func__);
		वापस PTR_ERR(dcdc);
	पूर्ण

	led = devm_kzalloc(&pdev->dev, माप(*led), GFP_KERNEL);
	अगर (led == शून्य)
		वापस -ENOMEM;

	led->cdev.brightness_set_blocking = wm8350_led_set;
	led->cdev.शेष_trigger = pdata->शेष_trigger;
	led->cdev.name = pdata->name;
	led->cdev.flags |= LED_CORE_SUSPENDRESUME;
	led->enabled = regulator_is_enabled(isink);
	led->isink = isink;
	led->dcdc = dcdc;

	क्रम (i = 0; i < ARRAY_SIZE(isink_cur) - 1; i++)
		अगर (isink_cur[i] >= pdata->max_uA)
			अवरोध;
	led->max_uA_index = i;
	अगर (pdata->max_uA != isink_cur[i])
		dev_warn(&pdev->dev,
			 "Maximum current %duA is not directly supported,"
			 " check platform data\n",
			 pdata->max_uA);

	spin_lock_init(&led->value_lock);
	led->value = LED_OFF;
	platक्रमm_set_drvdata(pdev, led);

	वापस led_classdev_रेजिस्टर(&pdev->dev, &led->cdev);
पूर्ण

अटल पूर्णांक wm8350_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8350_led *led = platक्रमm_get_drvdata(pdev);

	led_classdev_unरेजिस्टर(&led->cdev);
	wm8350_led_disable(led);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wm8350_led_driver = अणु
	.driver = अणु
		   .name = "wm8350-led",
		   पूर्ण,
	.probe = wm8350_led_probe,
	.हटाओ = wm8350_led_हटाओ,
	.shutकरोwn = wm8350_led_shutकरोwn,
पूर्ण;

module_platक्रमm_driver(wm8350_led_driver);

MODULE_AUTHOR("Mark Brown");
MODULE_DESCRIPTION("WM8350 LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm8350-led");
