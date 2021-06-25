<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED driver क्रम Marvell 88PM860x
 *
 * Copyright (C) 2009 Marvell International Ltd.
 *	Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/88pm860x.h>
#समावेश <linux/module.h>

#घोषणा LED_PWM_MASK		(0x1F)
#घोषणा LED_CURRENT_MASK	(0x07 << 5)

#घोषणा LED_BLINK_MASK		(0x7F)

#घोषणा LED_ON_CONTINUOUS	(0x0F << 3)

#घोषणा LED1_BLINK_EN		(1 << 1)
#घोषणा LED2_BLINK_EN		(1 << 2)

काष्ठा pm860x_led अणु
	काष्ठा led_classdev cdev;
	काष्ठा i2c_client *i2c;
	काष्ठा pm860x_chip *chip;
	काष्ठा mutex lock;
	अक्षर name[MFD_NAME_SIZE];

	पूर्णांक port;
	पूर्णांक iset;
	अचिन्हित अक्षर brightness;
	अचिन्हित अक्षर current_brightness;

	पूर्णांक reg_control;
	पूर्णांक reg_blink;
	पूर्णांक blink_mask;
पूर्ण;

अटल पूर्णांक led_घातer_set(काष्ठा pm860x_chip *chip, पूर्णांक port, पूर्णांक on)
अणु
	पूर्णांक ret = -EINVAL;

	चयन (port) अणु
	हाल 0:
	हाल 1:
	हाल 2:
		ret = on ? pm8606_osc_enable(chip, RGB1_ENABLE) :
			pm8606_osc_disable(chip, RGB1_ENABLE);
		अवरोध;
	हाल 3:
	हाल 4:
	हाल 5:
		ret = on ? pm8606_osc_enable(chip, RGB2_ENABLE) :
			pm8606_osc_disable(chip, RGB2_ENABLE);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक pm860x_led_set(काष्ठा led_classdev *cdev,
			   क्रमागत led_brightness value)
अणु
	काष्ठा pm860x_led *led = container_of(cdev, काष्ठा pm860x_led, cdev);
	काष्ठा pm860x_chip *chip;
	अचिन्हित अक्षर buf[3];
	पूर्णांक ret;

	chip = led->chip;
	mutex_lock(&led->lock);
	led->brightness = value >> 3;

	अगर ((led->current_brightness == 0) && led->brightness) अणु
		led_घातer_set(chip, led->port, 1);
		अगर (led->iset) अणु
			pm860x_set_bits(led->i2c, led->reg_control,
					LED_CURRENT_MASK, led->iset);
		पूर्ण
		pm860x_set_bits(led->i2c, led->reg_blink,
				LED_BLINK_MASK, LED_ON_CONTINUOUS);
		pm860x_set_bits(led->i2c, PM8606_WLED3B, led->blink_mask,
				led->blink_mask);
	पूर्ण
	pm860x_set_bits(led->i2c, led->reg_control, LED_PWM_MASK,
			led->brightness);

	अगर (led->brightness == 0) अणु
		pm860x_bulk_पढ़ो(led->i2c, led->reg_control, 3, buf);
		ret = buf[0] & LED_PWM_MASK;
		ret |= buf[1] & LED_PWM_MASK;
		ret |= buf[2] & LED_PWM_MASK;
		अगर (ret == 0) अणु
			/* unset current since no led is lighting */
			pm860x_set_bits(led->i2c, led->reg_control,
					LED_CURRENT_MASK, 0);
			pm860x_set_bits(led->i2c, PM8606_WLED3B,
					led->blink_mask, 0);
			led_घातer_set(chip, led->port, 0);
		पूर्ण
	पूर्ण
	led->current_brightness = led->brightness;
	dev_dbg(chip->dev, "Update LED. (reg:%d, brightness:%d)\n",
		led->reg_control, led->brightness);
	mutex_unlock(&led->lock);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक pm860x_led_dt_init(काष्ठा platक्रमm_device *pdev,
			      काष्ठा pm860x_led *data)
अणु
	काष्ठा device_node *nproot, *np;
	पूर्णांक iset = 0;

	अगर (!dev_of_node(pdev->dev.parent))
		वापस -ENODEV;
	nproot = of_get_child_by_name(dev_of_node(pdev->dev.parent), "leds");
	अगर (!nproot) अणु
		dev_err(&pdev->dev, "failed to find leds node\n");
		वापस -ENODEV;
	पूर्ण
	क्रम_each_available_child_of_node(nproot, np) अणु
		अगर (of_node_name_eq(np, data->name)) अणु
			of_property_पढ़ो_u32(np, "marvell,88pm860x-iset",
					     &iset);
			data->iset = PM8606_LED_CURRENT(iset);
			of_node_put(np);
			अवरोध;
		पूर्ण
	पूर्ण
	of_node_put(nproot);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा pm860x_led_dt_init(x, y)	(-1)
#पूर्ण_अगर

अटल पूर्णांक pm860x_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा pm860x_led_pdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा pm860x_led *data;
	काष्ठा resource *res;
	पूर्णांक ret = 0;

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा pm860x_led), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_REG, "control");
	अगर (!res) अणु
		dev_err(&pdev->dev, "No REG resource for control\n");
		वापस -ENXIO;
	पूर्ण
	data->reg_control = res->start;
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_REG, "blink");
	अगर (!res) अणु
		dev_err(&pdev->dev, "No REG resource for blink\n");
		वापस -ENXIO;
	पूर्ण
	data->reg_blink = res->start;
	स_रखो(data->name, 0, MFD_NAME_SIZE);
	चयन (pdev->id) अणु
	हाल 0:
		data->blink_mask = LED1_BLINK_EN;
		प्र_लिखो(data->name, "led0-red");
		अवरोध;
	हाल 1:
		data->blink_mask = LED1_BLINK_EN;
		प्र_लिखो(data->name, "led0-green");
		अवरोध;
	हाल 2:
		data->blink_mask = LED1_BLINK_EN;
		प्र_लिखो(data->name, "led0-blue");
		अवरोध;
	हाल 3:
		data->blink_mask = LED2_BLINK_EN;
		प्र_लिखो(data->name, "led1-red");
		अवरोध;
	हाल 4:
		data->blink_mask = LED2_BLINK_EN;
		प्र_लिखो(data->name, "led1-green");
		अवरोध;
	हाल 5:
		data->blink_mask = LED2_BLINK_EN;
		प्र_लिखो(data->name, "led1-blue");
		अवरोध;
	पूर्ण
	data->chip = chip;
	data->i2c = (chip->id == CHIP_PM8606) ? chip->client : chip->companion;
	data->port = pdev->id;
	अगर (pm860x_led_dt_init(pdev, data))
		अगर (pdata)
			data->iset = pdata->iset;

	data->current_brightness = 0;
	data->cdev.name = data->name;
	data->cdev.brightness_set_blocking = pm860x_led_set;
	mutex_init(&data->lock);

	ret = led_classdev_रेजिस्टर(chip->dev, &data->cdev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register LED: %d\n", ret);
		वापस ret;
	पूर्ण
	pm860x_led_set(&data->cdev, 0);

	platक्रमm_set_drvdata(pdev, data);

	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm860x_led *data = platक्रमm_get_drvdata(pdev);

	led_classdev_unरेजिस्टर(&data->cdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pm860x_led_driver = अणु
	.driver	= अणु
		.name	= "88pm860x-led",
	पूर्ण,
	.probe	= pm860x_led_probe,
	.हटाओ	= pm860x_led_हटाओ,
पूर्ण;

module_platक्रमm_driver(pm860x_led_driver);

MODULE_DESCRIPTION("LED driver for Marvell PM860x");
MODULE_AUTHOR("Haojian Zhuang <haojian.zhuang@marvell.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:88pm860x-led");
