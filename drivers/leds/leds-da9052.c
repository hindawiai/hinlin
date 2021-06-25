<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LED Driver क्रम Dialog DA9052 PMICs.
 *
 * Copyright(c) 2012 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <linux/slab.h>

#समावेश <linux/mfd/da9052/reg.h>
#समावेश <linux/mfd/da9052/da9052.h>
#समावेश <linux/mfd/da9052/pdata.h>

#घोषणा DA9052_OPENDRAIN_OUTPUT	2
#घोषणा DA9052_SET_HIGH_LVL_OUTPUT	(1 << 3)
#घोषणा DA9052_MASK_UPPER_NIBBLE	0xF0
#घोषणा DA9052_MASK_LOWER_NIBBLE	0x0F
#घोषणा DA9052_NIBBLE_SHIFT		4
#घोषणा DA9052_MAX_BRIGHTNESS		0x5f

काष्ठा da9052_led अणु
	काष्ठा led_classdev cdev;
	काष्ठा da9052 *da9052;
	अचिन्हित अक्षर led_index;
	अचिन्हित अक्षर id;
पूर्ण;

अटल अचिन्हित अक्षर led_reg[] = अणु
	DA9052_LED_CONT_4_REG,
	DA9052_LED_CONT_5_REG,
पूर्ण;

अटल पूर्णांक da9052_set_led_brightness(काष्ठा da9052_led *led,
				     क्रमागत led_brightness brightness)
अणु
	u8 val;
	पूर्णांक error;

	val = (brightness & 0x7f) | DA9052_LED_CONT_DIM;

	error = da9052_reg_ग_लिखो(led->da9052, led_reg[led->led_index], val);
	अगर (error < 0)
		dev_err(led->da9052->dev, "Failed to set led brightness, %d\n",
			error);
	वापस error;
पूर्ण

अटल पूर्णांक da9052_led_set(काष्ठा led_classdev *led_cdev,
			   क्रमागत led_brightness value)
अणु
	काष्ठा da9052_led *led =
			container_of(led_cdev, काष्ठा da9052_led, cdev);

	वापस da9052_set_led_brightness(led, value);
पूर्ण

अटल पूर्णांक da9052_configure_leds(काष्ठा da9052 *da9052)
अणु
	पूर्णांक error;
	अचिन्हित अक्षर रेजिस्टर_value = DA9052_OPENDRAIN_OUTPUT
				       | DA9052_SET_HIGH_LVL_OUTPUT;

	error = da9052_reg_update(da9052, DA9052_GPIO_14_15_REG,
				  DA9052_MASK_LOWER_NIBBLE,
				  रेजिस्टर_value);

	अगर (error < 0) अणु
		dev_err(da9052->dev, "Failed to write GPIO 14-15 reg, %d\n",
			error);
		वापस error;
	पूर्ण

	error = da9052_reg_update(da9052, DA9052_GPIO_14_15_REG,
				  DA9052_MASK_UPPER_NIBBLE,
				  रेजिस्टर_value << DA9052_NIBBLE_SHIFT);
	अगर (error < 0)
		dev_err(da9052->dev, "Failed to write GPIO 14-15 reg, %d\n",
			error);

	वापस error;
पूर्ण

अटल पूर्णांक da9052_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9052_pdata *pdata;
	काष्ठा da9052 *da9052;
	काष्ठा led_platक्रमm_data *pled;
	काष्ठा da9052_led *led = शून्य;
	पूर्णांक error = -ENODEV;
	पूर्णांक i;

	da9052 = dev_get_drvdata(pdev->dev.parent);
	pdata = dev_get_platdata(da9052->dev);
	अगर (pdata == शून्य) अणु
		dev_err(&pdev->dev, "No platform data\n");
		जाओ err;
	पूर्ण

	pled = pdata->pled;
	अगर (pled == शून्य) अणु
		dev_err(&pdev->dev, "No platform data for LED\n");
		जाओ err;
	पूर्ण

	led = devm_kसुस्मृति(&pdev->dev,
			   pled->num_leds, माप(काष्ठा da9052_led),
			   GFP_KERNEL);
	अगर (!led) अणु
		error = -ENOMEM;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < pled->num_leds; i++) अणु
		led[i].cdev.name = pled->leds[i].name;
		led[i].cdev.brightness_set_blocking = da9052_led_set;
		led[i].cdev.brightness = LED_OFF;
		led[i].cdev.max_brightness = DA9052_MAX_BRIGHTNESS;
		led[i].led_index = pled->leds[i].flags;
		led[i].da9052 = dev_get_drvdata(pdev->dev.parent);

		error = led_classdev_रेजिस्टर(pdev->dev.parent, &led[i].cdev);
		अगर (error) अणु
			dev_err(&pdev->dev, "Failed to register led %d\n",
				led[i].led_index);
			जाओ err_रेजिस्टर;
		पूर्ण

		error = da9052_set_led_brightness(&led[i],
						  led[i].cdev.brightness);
		अगर (error) अणु
			dev_err(&pdev->dev, "Unable to init led %d\n",
				led[i].led_index);
			जारी;
		पूर्ण
	पूर्ण
	error = da9052_configure_leds(led->da9052);
	अगर (error) अणु
		dev_err(&pdev->dev, "Failed to configure GPIO LED%d\n", error);
		जाओ err_रेजिस्टर;
	पूर्ण

	platक्रमm_set_drvdata(pdev, led);

	वापस 0;

err_रेजिस्टर:
	क्रम (i = i - 1; i >= 0; i--)
		led_classdev_unरेजिस्टर(&led[i].cdev);
err:
	वापस error;
पूर्ण

अटल पूर्णांक da9052_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9052_led *led = platक्रमm_get_drvdata(pdev);
	काष्ठा da9052_pdata *pdata;
	काष्ठा da9052 *da9052;
	काष्ठा led_platक्रमm_data *pled;
	पूर्णांक i;

	da9052 = dev_get_drvdata(pdev->dev.parent);
	pdata = dev_get_platdata(da9052->dev);
	pled = pdata->pled;

	क्रम (i = 0; i < pled->num_leds; i++) अणु
		da9052_set_led_brightness(&led[i], LED_OFF);
		led_classdev_unरेजिस्टर(&led[i].cdev);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9052_led_driver = अणु
	.driver		= अणु
		.name	= "da9052-leds",
	पूर्ण,
	.probe		= da9052_led_probe,
	.हटाओ		= da9052_led_हटाओ,
पूर्ण;

module_platक्रमm_driver(da9052_led_driver);

MODULE_AUTHOR("Dialog Semiconductor Ltd <dchen@diasemi.com>");
MODULE_DESCRIPTION("LED driver for Dialog DA9052 PMIC");
MODULE_LICENSE("GPL");
