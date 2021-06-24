<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LEDs driver क्रम Analog Devices ADP5520/ADP5501 MFD PMICs
 *
 * Copyright 2009 Analog Devices Inc.
 *
 * Loosely derived from leds-da903x:
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
#समावेश <linux/mfd/adp5520.h>
#समावेश <linux/slab.h>

काष्ठा adp5520_led अणु
	काष्ठा led_classdev	cdev;
	काष्ठा device		*master;
	पूर्णांक			id;
	पूर्णांक			flags;
पूर्ण;

अटल पूर्णांक adp5520_led_set(काष्ठा led_classdev *led_cdev,
			   क्रमागत led_brightness value)
अणु
	काष्ठा adp5520_led *led;

	led = container_of(led_cdev, काष्ठा adp5520_led, cdev);
	वापस adp5520_ग_लिखो(led->master, ADP5520_LED1_CURRENT + led->id - 1,
			 value >> 2);
पूर्ण

अटल पूर्णांक adp5520_led_setup(काष्ठा adp5520_led *led)
अणु
	काष्ठा device *dev = led->master;
	पूर्णांक flags = led->flags;
	पूर्णांक ret = 0;

	चयन (led->id) अणु
	हाल FLAG_ID_ADP5520_LED1_ADP5501_LED0:
		ret |= adp5520_set_bits(dev, ADP5520_LED_TIME,
					(flags >> ADP5520_FLAG_OFFT_SHIFT) &
					ADP5520_FLAG_OFFT_MASK);
		ret |= adp5520_set_bits(dev, ADP5520_LED_CONTROL,
					ADP5520_LED1_EN);
		अवरोध;
	हाल FLAG_ID_ADP5520_LED2_ADP5501_LED1:
		ret |= adp5520_set_bits(dev,  ADP5520_LED_TIME,
					((flags >> ADP5520_FLAG_OFFT_SHIFT) &
					ADP5520_FLAG_OFFT_MASK) << 2);
		ret |= adp5520_clr_bits(dev, ADP5520_LED_CONTROL,
					 ADP5520_R3_MODE);
		ret |= adp5520_set_bits(dev, ADP5520_LED_CONTROL,
					ADP5520_LED2_EN);
		अवरोध;
	हाल FLAG_ID_ADP5520_LED3_ADP5501_LED2:
		ret |= adp5520_set_bits(dev,  ADP5520_LED_TIME,
					((flags >> ADP5520_FLAG_OFFT_SHIFT) &
					ADP5520_FLAG_OFFT_MASK) << 4);
		ret |= adp5520_clr_bits(dev, ADP5520_LED_CONTROL,
					ADP5520_C3_MODE);
		ret |= adp5520_set_bits(dev, ADP5520_LED_CONTROL,
					ADP5520_LED3_EN);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक adp5520_led_prepare(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा adp5520_leds_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device *dev = pdev->dev.parent;
	पूर्णांक ret = 0;

	ret |= adp5520_ग_लिखो(dev, ADP5520_LED1_CURRENT, 0);
	ret |= adp5520_ग_लिखो(dev, ADP5520_LED2_CURRENT, 0);
	ret |= adp5520_ग_लिखो(dev, ADP5520_LED3_CURRENT, 0);
	ret |= adp5520_ग_लिखो(dev, ADP5520_LED_TIME, pdata->led_on_समय << 6);
	ret |= adp5520_ग_लिखो(dev, ADP5520_LED_FADE, FADE_VAL(pdata->fade_in,
		 pdata->fade_out));

	वापस ret;
पूर्ण

अटल पूर्णांक adp5520_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा adp5520_leds_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा adp5520_led *led, *led_dat;
	काष्ठा led_info *cur_led;
	पूर्णांक ret, i;

	अगर (pdata == शून्य) अणु
		dev_err(&pdev->dev, "missing platform data\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pdata->num_leds > ADP5520_01_MAXLEDS) अणु
		dev_err(&pdev->dev, "can't handle more than %d LEDS\n",
				 ADP5520_01_MAXLEDS);
		वापस -EFAULT;
	पूर्ण

	led = devm_kसुस्मृति(&pdev->dev, pdata->num_leds, माप(*led),
				GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	ret = adp5520_led_prepare(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to write\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < pdata->num_leds; ++i) अणु
		cur_led = &pdata->leds[i];
		led_dat = &led[i];

		led_dat->cdev.name = cur_led->name;
		led_dat->cdev.शेष_trigger = cur_led->शेष_trigger;
		led_dat->cdev.brightness_set_blocking = adp5520_led_set;
		led_dat->cdev.brightness = LED_OFF;

		अगर (cur_led->flags & ADP5520_FLAG_LED_MASK)
			led_dat->flags = cur_led->flags;
		अन्यथा
			led_dat->flags = i + 1;

		led_dat->id = led_dat->flags & ADP5520_FLAG_LED_MASK;

		led_dat->master = pdev->dev.parent;

		ret = led_classdev_रेजिस्टर(led_dat->master, &led_dat->cdev);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to register LED %d\n",
				led_dat->id);
			जाओ err;
		पूर्ण

		ret = adp5520_led_setup(led_dat);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to write\n");
			i++;
			जाओ err;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, led);
	वापस 0;

err:
	अगर (i > 0) अणु
		क्रम (i = i - 1; i >= 0; i--)
			led_classdev_unरेजिस्टर(&led[i].cdev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक adp5520_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा adp5520_leds_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा adp5520_led *led;
	पूर्णांक i;

	led = platक्रमm_get_drvdata(pdev);

	adp5520_clr_bits(led->master, ADP5520_LED_CONTROL,
		 ADP5520_LED1_EN | ADP5520_LED2_EN | ADP5520_LED3_EN);

	क्रम (i = 0; i < pdata->num_leds; i++) अणु
		led_classdev_unरेजिस्टर(&led[i].cdev);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver adp5520_led_driver = अणु
	.driver	= अणु
		.name	= "adp5520-led",
	पूर्ण,
	.probe		= adp5520_led_probe,
	.हटाओ		= adp5520_led_हटाओ,
पूर्ण;

module_platक्रमm_driver(adp5520_led_driver);

MODULE_AUTHOR("Michael Hennerich <hennerich@blackfin.uclinux.org>");
MODULE_DESCRIPTION("LEDS ADP5520(01) Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:adp5520-led");
