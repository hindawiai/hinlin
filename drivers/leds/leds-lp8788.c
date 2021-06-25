<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI LP8788 MFD - keyled driver
 *
 * Copyright 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mfd/lp8788.h>
#समावेश <linux/mfd/lp8788-isink.h>

#घोषणा MAX_BRIGHTNESS			LP8788_ISINK_MAX_PWM
#घोषणा DEFAULT_LED_NAME		"keyboard-backlight"

काष्ठा lp8788_led अणु
	काष्ठा lp8788 *lp;
	काष्ठा mutex lock;
	काष्ठा led_classdev led_dev;
	क्रमागत lp8788_isink_number isink_num;
	पूर्णांक on;
पूर्ण;

काष्ठा lp8788_led_config अणु
	क्रमागत lp8788_isink_scale scale;
	क्रमागत lp8788_isink_number num;
	पूर्णांक iout;
पूर्ण;

अटल काष्ठा lp8788_led_config शेष_led_config = अणु
	.scale = LP8788_ISINK_SCALE_100mA,
	.num   = LP8788_ISINK_3,
	.iout  = 0,
पूर्ण;

अटल पूर्णांक lp8788_led_init_device(काष्ठा lp8788_led *led,
				काष्ठा lp8788_led_platक्रमm_data *pdata)
अणु
	काष्ठा lp8788_led_config *cfg = &शेष_led_config;
	u8 addr, mask, val;
	पूर्णांक ret;

	अगर (pdata) अणु
		cfg->scale = pdata->scale;
		cfg->num = pdata->num;
		cfg->iout = pdata->iout_code;
	पूर्ण

	led->isink_num = cfg->num;

	/* scale configuration */
	addr = LP8788_ISINK_CTRL;
	mask = 1 << (cfg->num + LP8788_ISINK_SCALE_OFFSET);
	val = cfg->scale << (cfg->num + LP8788_ISINK_SCALE_OFFSET);
	ret = lp8788_update_bits(led->lp, addr, mask, val);
	अगर (ret)
		वापस ret;

	/* current configuration */
	addr = lp8788_iout_addr[cfg->num];
	mask = lp8788_iout_mask[cfg->num];
	val = cfg->iout;

	वापस lp8788_update_bits(led->lp, addr, mask, val);
पूर्ण

अटल पूर्णांक lp8788_led_enable(काष्ठा lp8788_led *led,
			क्रमागत lp8788_isink_number num, पूर्णांक on)
अणु
	पूर्णांक ret;

	u8 mask = 1 << num;
	u8 val = on << num;

	ret = lp8788_update_bits(led->lp, LP8788_ISINK_CTRL, mask, val);
	अगर (ret == 0)
		led->on = on;

	वापस ret;
पूर्ण

अटल पूर्णांक lp8788_brightness_set(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness val)
अणु
	काष्ठा lp8788_led *led =
			container_of(led_cdev, काष्ठा lp8788_led, led_dev);

	क्रमागत lp8788_isink_number num = led->isink_num;
	पूर्णांक enable, ret;

	mutex_lock(&led->lock);

	चयन (num) अणु
	हाल LP8788_ISINK_1:
	हाल LP8788_ISINK_2:
	हाल LP8788_ISINK_3:
		ret = lp8788_ग_लिखो_byte(led->lp, lp8788_pwm_addr[num], val);
		अगर (ret < 0)
			जाओ unlock;
		अवरोध;
	शेष:
		mutex_unlock(&led->lock);
		वापस -EINVAL;
	पूर्ण

	enable = (val > 0) ? 1 : 0;
	अगर (enable != led->on)
		ret = lp8788_led_enable(led, num, enable);
unlock:
	mutex_unlock(&led->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक lp8788_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp8788 *lp = dev_get_drvdata(pdev->dev.parent);
	काष्ठा lp8788_led_platक्रमm_data *led_pdata;
	काष्ठा lp8788_led *led;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	led = devm_kzalloc(dev, माप(काष्ठा lp8788_led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	led->lp = lp;
	led->led_dev.max_brightness = MAX_BRIGHTNESS;
	led->led_dev.brightness_set_blocking = lp8788_brightness_set;

	led_pdata = lp->pdata ? lp->pdata->led_pdata : शून्य;

	अगर (!led_pdata || !led_pdata->name)
		led->led_dev.name = DEFAULT_LED_NAME;
	अन्यथा
		led->led_dev.name = led_pdata->name;

	mutex_init(&led->lock);

	ret = lp8788_led_init_device(led, led_pdata);
	अगर (ret) अणु
		dev_err(dev, "led init device err: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_led_classdev_रेजिस्टर(dev, &led->led_dev);
	अगर (ret) अणु
		dev_err(dev, "led register err: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver lp8788_led_driver = अणु
	.probe = lp8788_led_probe,
	.driver = अणु
		.name = LP8788_DEV_KEYLED,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lp8788_led_driver);

MODULE_DESCRIPTION("Texas Instruments LP8788 Keyboard LED Driver");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lp8788-keyled");
