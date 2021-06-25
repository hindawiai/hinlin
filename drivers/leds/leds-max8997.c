<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * leds-max8997.c - LED class driver क्रम MAX8997 LEDs.
 *
 * Copyright (C) 2011 Samsung Electronics
 * Donggeun Kim <dg77.kim@samsung.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>
#समावेश <linux/mfd/max8997.h>
#समावेश <linux/mfd/max8997-निजी.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा MAX8997_LED_FLASH_SHIFT			3
#घोषणा MAX8997_LED_FLASH_CUR_MASK		0xf8
#घोषणा MAX8997_LED_MOVIE_SHIFT			4
#घोषणा MAX8997_LED_MOVIE_CUR_MASK		0xf0

#घोषणा MAX8997_LED_FLASH_MAX_BRIGHTNESS	0x1f
#घोषणा MAX8997_LED_MOVIE_MAX_BRIGHTNESS	0xf
#घोषणा MAX8997_LED_NONE_MAX_BRIGHTNESS		0

#घोषणा MAX8997_LED0_FLASH_MASK			0x1
#घोषणा MAX8997_LED0_FLASH_PIN_MASK		0x5
#घोषणा MAX8997_LED0_MOVIE_MASK			0x8
#घोषणा MAX8997_LED0_MOVIE_PIN_MASK		0x28

#घोषणा MAX8997_LED1_FLASH_MASK			0x2
#घोषणा MAX8997_LED1_FLASH_PIN_MASK		0x6
#घोषणा MAX8997_LED1_MOVIE_MASK			0x10
#घोषणा MAX8997_LED1_MOVIE_PIN_MASK		0x30

#घोषणा MAX8997_LED_BOOST_ENABLE_MASK		(1 << 6)

काष्ठा max8997_led अणु
	काष्ठा max8997_dev *iodev;
	काष्ठा led_classdev cdev;
	bool enabled;
	पूर्णांक id;
	क्रमागत max8997_led_mode led_mode;
	काष्ठा mutex mutex;
पूर्ण;

अटल व्योम max8997_led_set_mode(काष्ठा max8997_led *led,
			क्रमागत max8997_led_mode mode)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = led->iodev->i2c;
	u8 mask = 0, val;

	चयन (mode) अणु
	हाल MAX8997_FLASH_MODE:
		mask = MAX8997_LED1_FLASH_MASK | MAX8997_LED0_FLASH_MASK;
		val = led->id ?
		      MAX8997_LED1_FLASH_MASK : MAX8997_LED0_FLASH_MASK;
		led->cdev.max_brightness = MAX8997_LED_FLASH_MAX_BRIGHTNESS;
		अवरोध;
	हाल MAX8997_MOVIE_MODE:
		mask = MAX8997_LED1_MOVIE_MASK | MAX8997_LED0_MOVIE_MASK;
		val = led->id ?
		      MAX8997_LED1_MOVIE_MASK : MAX8997_LED0_MOVIE_MASK;
		led->cdev.max_brightness = MAX8997_LED_MOVIE_MAX_BRIGHTNESS;
		अवरोध;
	हाल MAX8997_FLASH_PIN_CONTROL_MODE:
		mask = MAX8997_LED1_FLASH_PIN_MASK |
		       MAX8997_LED0_FLASH_PIN_MASK;
		val = led->id ?
		      MAX8997_LED1_FLASH_PIN_MASK : MAX8997_LED0_FLASH_PIN_MASK;
		led->cdev.max_brightness = MAX8997_LED_FLASH_MAX_BRIGHTNESS;
		अवरोध;
	हाल MAX8997_MOVIE_PIN_CONTROL_MODE:
		mask = MAX8997_LED1_MOVIE_PIN_MASK |
		       MAX8997_LED0_MOVIE_PIN_MASK;
		val = led->id ?
		      MAX8997_LED1_MOVIE_PIN_MASK : MAX8997_LED0_MOVIE_PIN_MASK;
		led->cdev.max_brightness = MAX8997_LED_MOVIE_MAX_BRIGHTNESS;
		अवरोध;
	शेष:
		led->cdev.max_brightness = MAX8997_LED_NONE_MAX_BRIGHTNESS;
		अवरोध;
	पूर्ण

	अगर (mask) अणु
		ret = max8997_update_reg(client, MAX8997_REG_LEN_CNTL, val,
					 mask);
		अगर (ret)
			dev_err(led->iodev->dev,
				"failed to update register(%d)\n", ret);
	पूर्ण

	led->led_mode = mode;
पूर्ण

अटल व्योम max8997_led_enable(काष्ठा max8997_led *led, bool enable)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = led->iodev->i2c;
	u8 val = 0, mask = MAX8997_LED_BOOST_ENABLE_MASK;

	अगर (led->enabled == enable)
		वापस;

	val = enable ? MAX8997_LED_BOOST_ENABLE_MASK : 0;

	ret = max8997_update_reg(client, MAX8997_REG_BOOST_CNTL, val, mask);
	अगर (ret)
		dev_err(led->iodev->dev,
			"failed to update register(%d)\n", ret);

	led->enabled = enable;
पूर्ण

अटल व्योम max8997_led_set_current(काष्ठा max8997_led *led,
				क्रमागत led_brightness value)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = led->iodev->i2c;
	u8 val = 0, mask = 0, reg = 0;

	चयन (led->led_mode) अणु
	हाल MAX8997_FLASH_MODE:
	हाल MAX8997_FLASH_PIN_CONTROL_MODE:
		val = value << MAX8997_LED_FLASH_SHIFT;
		mask = MAX8997_LED_FLASH_CUR_MASK;
		reg = led->id ? MAX8997_REG_FLASH2_CUR : MAX8997_REG_FLASH1_CUR;
		अवरोध;
	हाल MAX8997_MOVIE_MODE:
	हाल MAX8997_MOVIE_PIN_CONTROL_MODE:
		val = value << MAX8997_LED_MOVIE_SHIFT;
		mask = MAX8997_LED_MOVIE_CUR_MASK;
		reg = MAX8997_REG_MOVIE_CUR;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (mask) अणु
		ret = max8997_update_reg(client, reg, val, mask);
		अगर (ret)
			dev_err(led->iodev->dev,
				"failed to update register(%d)\n", ret);
	पूर्ण
पूर्ण

अटल व्योम max8997_led_brightness_set(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness value)
अणु
	काष्ठा max8997_led *led =
			container_of(led_cdev, काष्ठा max8997_led, cdev);

	अगर (value) अणु
		max8997_led_set_current(led, value);
		max8997_led_enable(led, true);
	पूर्ण अन्यथा अणु
		max8997_led_set_current(led, value);
		max8997_led_enable(led, false);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार mode_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा max8997_led *led =
			container_of(led_cdev, काष्ठा max8997_led, cdev);
	sमाप_प्रकार ret = 0;

	mutex_lock(&led->mutex);

	चयन (led->led_mode) अणु
	हाल MAX8997_FLASH_MODE:
		ret += प्र_लिखो(buf, "FLASH\n");
		अवरोध;
	हाल MAX8997_MOVIE_MODE:
		ret += प्र_लिखो(buf, "MOVIE\n");
		अवरोध;
	हाल MAX8997_FLASH_PIN_CONTROL_MODE:
		ret += प्र_लिखो(buf, "FLASH_PIN_CONTROL\n");
		अवरोध;
	हाल MAX8997_MOVIE_PIN_CONTROL_MODE:
		ret += प्र_लिखो(buf, "MOVIE_PIN_CONTROL\n");
		अवरोध;
	शेष:
		ret += प्र_लिखो(buf, "NONE\n");
		अवरोध;
	पूर्ण

	mutex_unlock(&led->mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार mode_store(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा max8997_led *led =
			container_of(led_cdev, काष्ठा max8997_led, cdev);
	क्रमागत max8997_led_mode mode;

	mutex_lock(&led->mutex);

	अगर (!म_भेदन(buf, "FLASH_PIN_CONTROL", 17))
		mode = MAX8997_FLASH_PIN_CONTROL_MODE;
	अन्यथा अगर (!म_भेदन(buf, "MOVIE_PIN_CONTROL", 17))
		mode = MAX8997_MOVIE_PIN_CONTROL_MODE;
	अन्यथा अगर (!म_भेदन(buf, "FLASH", 5))
		mode = MAX8997_FLASH_MODE;
	अन्यथा अगर (!म_भेदन(buf, "MOVIE", 5))
		mode = MAX8997_MOVIE_MODE;
	अन्यथा
		mode = MAX8997_NONE;

	max8997_led_set_mode(led, mode);

	mutex_unlock(&led->mutex);

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(mode);

अटल काष्ठा attribute *max8997_attrs[] = अणु
	&dev_attr_mode.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(max8997);

अटल पूर्णांक max8997_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8997_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max8997_platक्रमm_data *pdata = dev_get_platdata(iodev->dev);
	काष्ठा max8997_led *led;
	अक्षर name[20];
	पूर्णांक ret = 0;

	अगर (pdata == शून्य) अणु
		dev_err(&pdev->dev, "no platform data\n");
		वापस -ENODEV;
	पूर्ण

	led = devm_kzalloc(&pdev->dev, माप(*led), GFP_KERNEL);
	अगर (led == शून्य)
		वापस -ENOMEM;

	led->id = pdev->id;
	snम_लिखो(name, माप(name), "max8997-led%d", pdev->id);

	led->cdev.name = name;
	led->cdev.brightness_set = max8997_led_brightness_set;
	led->cdev.flags |= LED_CORE_SUSPENDRESUME;
	led->cdev.brightness = 0;
	led->cdev.groups = max8997_groups;
	led->iodev = iodev;

	/* initialize mode and brightness according to platक्रमm_data */
	अगर (pdata->led_pdata) अणु
		u8 mode = 0, brightness = 0;

		mode = pdata->led_pdata->mode[led->id];
		brightness = pdata->led_pdata->brightness[led->id];

		max8997_led_set_mode(led, mode);

		अगर (brightness > led->cdev.max_brightness)
			brightness = led->cdev.max_brightness;
		max8997_led_set_current(led, brightness);
		led->cdev.brightness = brightness;
	पूर्ण अन्यथा अणु
		max8997_led_set_mode(led, MAX8997_NONE);
		max8997_led_set_current(led, 0);
	पूर्ण

	mutex_init(&led->mutex);

	ret = devm_led_classdev_रेजिस्टर(&pdev->dev, &led->cdev);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver max8997_led_driver = अणु
	.driver = अणु
		.name  = "max8997-led",
	पूर्ण,
	.probe  = max8997_led_probe,
पूर्ण;

module_platक्रमm_driver(max8997_led_driver);

MODULE_AUTHOR("Donggeun Kim <dg77.kim@samsung.com>");
MODULE_DESCRIPTION("MAX8997 LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:max8997-led");
