<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Backlight driver क्रम Marvell Semiconductor 88PM8606
 *
 * Copyright (C) 2009 Marvell International Ltd.
 *	Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/fb.h>
#समावेश <linux/i2c.h>
#समावेश <linux/backlight.h>
#समावेश <linux/mfd/88pm860x.h>
#समावेश <linux/module.h>

#घोषणा MAX_BRIGHTNESS		(0xFF)
#घोषणा MIN_BRIGHTNESS		(0)

#घोषणा CURRENT_BITMASK		(0x1F << 1)

काष्ठा pm860x_backlight_data अणु
	काष्ठा pm860x_chip *chip;
	काष्ठा i2c_client *i2c;
	पूर्णांक	current_brightness;
	पूर्णांक	port;
	पूर्णांक	pwm;
	पूर्णांक	iset;
	पूर्णांक	reg_duty_cycle;
	पूर्णांक	reg_always_on;
	पूर्णांक	reg_current;
पूर्ण;

अटल पूर्णांक backlight_घातer_set(काष्ठा pm860x_chip *chip, पूर्णांक port,
		पूर्णांक on)
अणु
	पूर्णांक ret = -EINVAL;

	चयन (port) अणु
	हाल 0:
		ret = on ? pm8606_osc_enable(chip, WLED1_DUTY) :
			pm8606_osc_disable(chip, WLED1_DUTY);
		अवरोध;
	हाल 1:
		ret = on ? pm8606_osc_enable(chip, WLED2_DUTY) :
			pm8606_osc_disable(chip, WLED2_DUTY);
		अवरोध;
	हाल 2:
		ret = on ? pm8606_osc_enable(chip, WLED3_DUTY) :
			pm8606_osc_disable(chip, WLED3_DUTY);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक pm860x_backlight_set(काष्ठा backlight_device *bl, पूर्णांक brightness)
अणु
	काष्ठा pm860x_backlight_data *data = bl_get_data(bl);
	काष्ठा pm860x_chip *chip = data->chip;
	अचिन्हित अक्षर value;
	पूर्णांक ret;

	अगर (brightness > MAX_BRIGHTNESS)
		value = MAX_BRIGHTNESS;
	अन्यथा
		value = brightness;

	अगर (brightness)
		backlight_घातer_set(chip, data->port, 1);

	ret = pm860x_reg_ग_लिखो(data->i2c, data->reg_duty_cycle, value);
	अगर (ret < 0)
		जाओ out;

	अगर ((data->current_brightness == 0) && brightness) अणु
		अगर (data->iset) अणु
			ret = pm860x_set_bits(data->i2c, data->reg_current,
					      CURRENT_BITMASK, data->iset);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
		अगर (data->pwm) अणु
			ret = pm860x_set_bits(data->i2c, PM8606_PWM,
					      PM8606_PWM_FREQ_MASK, data->pwm);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
		अगर (brightness == MAX_BRIGHTNESS) अणु
			/* set WLED_ON bit as 100% */
			ret = pm860x_set_bits(data->i2c, data->reg_always_on,
					      PM8606_WLED_ON, PM8606_WLED_ON);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (brightness == MAX_BRIGHTNESS) अणु
			/* set WLED_ON bit as 100% */
			ret = pm860x_set_bits(data->i2c, data->reg_always_on,
					      PM8606_WLED_ON, PM8606_WLED_ON);
		पूर्ण अन्यथा अणु
			/* clear WLED_ON bit since it's not 100% */
			ret = pm860x_set_bits(data->i2c, data->reg_always_on,
					      PM8606_WLED_ON, 0);
		पूर्ण
	पूर्ण
	अगर (ret < 0)
		जाओ out;

	अगर (brightness == 0)
		backlight_घातer_set(chip, data->port, 0);

	dev_dbg(chip->dev, "set brightness %d\n", value);
	data->current_brightness = value;
	वापस 0;
out:
	dev_dbg(chip->dev, "set brightness %d failure with return value: %d\n",
		value, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक pm860x_backlight_update_status(काष्ठा backlight_device *bl)
अणु
	वापस pm860x_backlight_set(bl, backlight_get_brightness(bl));
पूर्ण

अटल पूर्णांक pm860x_backlight_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा pm860x_backlight_data *data = bl_get_data(bl);
	काष्ठा pm860x_chip *chip = data->chip;
	पूर्णांक ret;

	ret = pm860x_reg_पढ़ो(data->i2c, data->reg_duty_cycle);
	अगर (ret < 0)
		जाओ out;
	data->current_brightness = ret;
	dev_dbg(chip->dev, "get brightness %d\n", data->current_brightness);
	वापस data->current_brightness;
out:
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा backlight_ops pm860x_backlight_ops = अणु
	.options	= BL_CORE_SUSPENDRESUME,
	.update_status	= pm860x_backlight_update_status,
	.get_brightness	= pm860x_backlight_get_brightness,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल पूर्णांक pm860x_backlight_dt_init(काष्ठा platक्रमm_device *pdev,
				    काष्ठा pm860x_backlight_data *data,
				    अक्षर *name)
अणु
	काष्ठा device_node *nproot, *np;
	पूर्णांक iset = 0;

	nproot = of_get_child_by_name(pdev->dev.parent->of_node, "backlights");
	अगर (!nproot) अणु
		dev_err(&pdev->dev, "failed to find backlights node\n");
		वापस -ENODEV;
	पूर्ण
	क्रम_each_child_of_node(nproot, np) अणु
		अगर (of_node_name_eq(np, name)) अणु
			of_property_पढ़ो_u32(np, "marvell,88pm860x-iset",
					     &iset);
			data->iset = PM8606_WLED_CURRENT(iset);
			of_property_पढ़ो_u32(np, "marvell,88pm860x-pwm",
					     &data->pwm);
			of_node_put(np);
			अवरोध;
		पूर्ण
	पूर्ण
	of_node_put(nproot);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा pm860x_backlight_dt_init(x, y, z)	(-1)
#पूर्ण_अगर

अटल पूर्णांक pm860x_backlight_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा pm860x_backlight_pdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा pm860x_backlight_data *data;
	काष्ठा backlight_device *bl;
	काष्ठा resource *res;
	काष्ठा backlight_properties props;
	अक्षर name[MFD_NAME_SIZE];
	पूर्णांक ret = 0;

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा pm860x_backlight_data),
			    GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_REG, "duty cycle");
	अगर (!res) अणु
		dev_err(&pdev->dev, "No REG resource for duty cycle\n");
		वापस -ENXIO;
	पूर्ण
	data->reg_duty_cycle = res->start;
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_REG, "always on");
	अगर (!res) अणु
		dev_err(&pdev->dev, "No REG resource for always on\n");
		वापस -ENXIO;
	पूर्ण
	data->reg_always_on = res->start;
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_REG, "current");
	अगर (!res) अणु
		dev_err(&pdev->dev, "No REG resource for current\n");
		वापस -ENXIO;
	पूर्ण
	data->reg_current = res->start;

	स_रखो(name, 0, MFD_NAME_SIZE);
	प्र_लिखो(name, "backlight-%d", pdev->id);
	data->port = pdev->id;
	data->chip = chip;
	data->i2c = (chip->id == CHIP_PM8606) ? chip->client : chip->companion;
	data->current_brightness = MAX_BRIGHTNESS;
	अगर (pm860x_backlight_dt_init(pdev, data, name)) अणु
		अगर (pdata) अणु
			data->pwm = pdata->pwm;
			data->iset = pdata->iset;
		पूर्ण
	पूर्ण

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = MAX_BRIGHTNESS;
	bl = devm_backlight_device_रेजिस्टर(&pdev->dev, name, &pdev->dev, data,
					&pm860x_backlight_ops, &props);
	अगर (IS_ERR(bl)) अणु
		dev_err(&pdev->dev, "failed to register backlight\n");
		वापस PTR_ERR(bl);
	पूर्ण
	bl->props.brightness = MAX_BRIGHTNESS;

	platक्रमm_set_drvdata(pdev, bl);

	/* पढ़ो current backlight */
	ret = pm860x_backlight_get_brightness(bl);
	अगर (ret < 0)
		वापस ret;

	backlight_update_status(bl);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pm860x_backlight_driver = अणु
	.driver		= अणु
		.name	= "88pm860x-backlight",
	पूर्ण,
	.probe		= pm860x_backlight_probe,
पूर्ण;

module_platक्रमm_driver(pm860x_backlight_driver);

MODULE_DESCRIPTION("Backlight Driver for Marvell Semiconductor 88PM8606");
MODULE_AUTHOR("Haojian Zhuang <haojian.zhuang@marvell.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:88pm860x-backlight");
