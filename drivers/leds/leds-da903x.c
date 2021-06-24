<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LEDs driver क्रम Dialog Semiconductor DA9030/DA9034
 *
 * Copyright (C) 2008 Compulab, Ltd.
 *	Mike Rapoport <mike@compulab.co.il>
 *
 * Copyright (C) 2006-2008 Marvell International Ltd.
 *	Eric Miao <eric.miao@marvell.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <linux/mfd/da903x.h>
#समावेश <linux/slab.h>

#घोषणा DA9030_LED1_CONTROL	0x20
#घोषणा DA9030_LED2_CONTROL	0x21
#घोषणा DA9030_LED3_CONTROL	0x22
#घोषणा DA9030_LED4_CONTROL	0x23
#घोषणा DA9030_LEDPC_CONTROL	0x24
#घोषणा DA9030_MISC_CONTROL_A	0x26	/* Vibrator Control */

#घोषणा DA9034_LED1_CONTROL	0x35
#घोषणा DA9034_LED2_CONTROL	0x36
#घोषणा DA9034_VIBRA		0x40

काष्ठा da903x_led अणु
	काष्ठा led_classdev	cdev;
	काष्ठा device		*master;
	पूर्णांक			id;
	पूर्णांक			flags;
पूर्ण;

#घोषणा DA9030_LED_OFFSET(id)	((id) - DA9030_ID_LED_1)
#घोषणा DA9034_LED_OFFSET(id)	((id) - DA9034_ID_LED_1)

अटल पूर्णांक da903x_led_set(काष्ठा led_classdev *led_cdev,
			   क्रमागत led_brightness value)
अणु
	काष्ठा da903x_led *led =
			container_of(led_cdev, काष्ठा da903x_led, cdev);
	uपूर्णांक8_t val;
	पूर्णांक offset, ret = -EINVAL;

	चयन (led->id) अणु
	हाल DA9030_ID_LED_1:
	हाल DA9030_ID_LED_2:
	हाल DA9030_ID_LED_3:
	हाल DA9030_ID_LED_4:
	हाल DA9030_ID_LED_PC:
		offset = DA9030_LED_OFFSET(led->id);
		val = led->flags & ~0x87;
		val |= value ? 0x80 : 0; /* EN bit */
		val |= (0x7 - (value >> 5)) & 0x7; /* PWM<2:0> */
		ret = da903x_ग_लिखो(led->master, DA9030_LED1_CONTROL + offset,
				   val);
		अवरोध;
	हाल DA9030_ID_VIBRA:
		val = led->flags & ~0x80;
		val |= value ? 0x80 : 0; /* EN bit */
		ret = da903x_ग_लिखो(led->master, DA9030_MISC_CONTROL_A, val);
		अवरोध;
	हाल DA9034_ID_LED_1:
	हाल DA9034_ID_LED_2:
		offset = DA9034_LED_OFFSET(led->id);
		val = (value * 0x5f / LED_FULL) & 0x7f;
		val |= (led->flags & DA9034_LED_RAMP) ? 0x80 : 0;
		ret = da903x_ग_लिखो(led->master, DA9034_LED1_CONTROL + offset,
				   val);
		अवरोध;
	हाल DA9034_ID_VIBRA:
		val = value & 0xfe;
		ret = da903x_ग_लिखो(led->master, DA9034_VIBRA, val);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक da903x_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा led_info *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा da903x_led *led;
	पूर्णांक id, ret;

	अगर (pdata == शून्य)
		वापस 0;

	id = pdev->id;

	अगर (!((id >= DA9030_ID_LED_1 && id <= DA9030_ID_VIBRA) ||
	      (id >= DA9034_ID_LED_1 && id <= DA9034_ID_VIBRA))) अणु
		dev_err(&pdev->dev, "invalid LED ID (%d) specified\n", id);
		वापस -EINVAL;
	पूर्ण

	led = devm_kzalloc(&pdev->dev, माप(काष्ठा da903x_led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	led->cdev.name = pdata->name;
	led->cdev.शेष_trigger = pdata->शेष_trigger;
	led->cdev.brightness_set_blocking = da903x_led_set;
	led->cdev.brightness = LED_OFF;

	led->id = id;
	led->flags = pdata->flags;
	led->master = pdev->dev.parent;

	ret = led_classdev_रेजिस्टर(led->master, &led->cdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register LED %d\n", id);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, led);

	वापस 0;
पूर्ण

अटल पूर्णांक da903x_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da903x_led *led = platक्रमm_get_drvdata(pdev);

	led_classdev_unरेजिस्टर(&led->cdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da903x_led_driver = अणु
	.driver	= अणु
		.name	= "da903x-led",
	पूर्ण,
	.probe		= da903x_led_probe,
	.हटाओ		= da903x_led_हटाओ,
पूर्ण;

module_platक्रमm_driver(da903x_led_driver);

MODULE_DESCRIPTION("LEDs driver for Dialog Semiconductor DA9030/DA9034");
MODULE_AUTHOR("Eric Miao <eric.miao@marvell.com>");
MODULE_AUTHOR("Mike Rapoport <mike@compulab.co.il>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da903x-led");
