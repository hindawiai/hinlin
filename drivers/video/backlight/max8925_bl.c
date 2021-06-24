<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Backlight driver क्रम Maxim MAX8925
 *
 * Copyright (C) 2009 Marvell International Ltd.
 *      Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fb.h>
#समावेश <linux/i2c.h>
#समावेश <linux/backlight.h>
#समावेश <linux/mfd/max8925.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#घोषणा MAX_BRIGHTNESS		(0xff)
#घोषणा MIN_BRIGHTNESS		(0)

#घोषणा LWX_FREQ(x)		(((x - 601) / 100) & 0x7)

काष्ठा max8925_backlight_data अणु
	काष्ठा max8925_chip	*chip;

	पूर्णांक	current_brightness;
	पूर्णांक	reg_mode_cntl;
	पूर्णांक	reg_cntl;
पूर्ण;

अटल पूर्णांक max8925_backlight_set(काष्ठा backlight_device *bl, पूर्णांक brightness)
अणु
	काष्ठा max8925_backlight_data *data = bl_get_data(bl);
	काष्ठा max8925_chip *chip = data->chip;
	अचिन्हित अक्षर value;
	पूर्णांक ret;

	अगर (brightness > MAX_BRIGHTNESS)
		value = MAX_BRIGHTNESS;
	अन्यथा
		value = brightness;

	ret = max8925_reg_ग_लिखो(chip->i2c, data->reg_cntl, value);
	अगर (ret < 0)
		जाओ out;

	अगर (!data->current_brightness && brightness)
		/* enable WLED output */
		ret = max8925_set_bits(chip->i2c, data->reg_mode_cntl, 1, 1);
	अन्यथा अगर (!brightness)
		/* disable WLED output */
		ret = max8925_set_bits(chip->i2c, data->reg_mode_cntl, 1, 0);
	अगर (ret < 0)
		जाओ out;
	dev_dbg(chip->dev, "set brightness %d\n", value);
	data->current_brightness = value;
	वापस 0;
out:
	dev_dbg(chip->dev, "set brightness %d failure with return value:%d\n",
		value, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक max8925_backlight_update_status(काष्ठा backlight_device *bl)
अणु
	वापस max8925_backlight_set(bl, backlight_get_brightness(bl));
पूर्ण

अटल पूर्णांक max8925_backlight_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा max8925_backlight_data *data = bl_get_data(bl);
	काष्ठा max8925_chip *chip = data->chip;
	पूर्णांक ret;

	ret = max8925_reg_पढ़ो(chip->i2c, data->reg_cntl);
	अगर (ret < 0)
		वापस -EINVAL;
	data->current_brightness = ret;
	dev_dbg(chip->dev, "get brightness %d\n", data->current_brightness);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा backlight_ops max8925_backlight_ops = अणु
	.options	= BL_CORE_SUSPENDRESUME,
	.update_status	= max8925_backlight_update_status,
	.get_brightness	= max8925_backlight_get_brightness,
पूर्ण;

अटल व्योम max8925_backlight_dt_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *nproot = pdev->dev.parent->of_node, *np;
	काष्ठा max8925_backlight_pdata *pdata;
	u32 val;

	अगर (!nproot || !IS_ENABLED(CONFIG_OF))
		वापस;

	pdata = devm_kzalloc(&pdev->dev,
			     माप(काष्ठा max8925_backlight_pdata),
			     GFP_KERNEL);
	अगर (!pdata)
		वापस;

	np = of_get_child_by_name(nproot, "backlight");
	अगर (!np) अणु
		dev_err(&pdev->dev, "failed to find backlight node\n");
		वापस;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "maxim,max8925-dual-string", &val))
		pdata->dual_string = val;

	of_node_put(np);

	pdev->dev.platक्रमm_data = pdata;
पूर्ण

अटल पूर्णांक max8925_backlight_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max8925_backlight_pdata *pdata;
	काष्ठा max8925_backlight_data *data;
	काष्ठा backlight_device *bl;
	काष्ठा backlight_properties props;
	काष्ठा resource *res;
	अचिन्हित अक्षर value;
	पूर्णांक ret = 0;

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा max8925_backlight_data),
			    GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_REG, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "No REG resource for mode control!\n");
		वापस -ENXIO;
	पूर्ण
	data->reg_mode_cntl = res->start;
	res = platक्रमm_get_resource(pdev, IORESOURCE_REG, 1);
	अगर (!res) अणु
		dev_err(&pdev->dev, "No REG resource for control!\n");
		वापस -ENXIO;
	पूर्ण
	data->reg_cntl = res->start;

	data->chip = chip;
	data->current_brightness = 0;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = MAX_BRIGHTNESS;
	bl = devm_backlight_device_रेजिस्टर(&pdev->dev, "max8925-backlight",
					&pdev->dev, data,
					&max8925_backlight_ops, &props);
	अगर (IS_ERR(bl)) अणु
		dev_err(&pdev->dev, "failed to register backlight\n");
		वापस PTR_ERR(bl);
	पूर्ण
	bl->props.brightness = MAX_BRIGHTNESS;

	platक्रमm_set_drvdata(pdev, bl);

	value = 0;
	अगर (!pdev->dev.platक्रमm_data)
		max8925_backlight_dt_init(pdev);

	pdata = pdev->dev.platक्रमm_data;
	अगर (pdata) अणु
		अगर (pdata->lxw_scl)
			value |= (1 << 7);
		अगर (pdata->lxw_freq)
			value |= (LWX_FREQ(pdata->lxw_freq) << 4);
		अगर (pdata->dual_string)
			value |= (1 << 1);
	पूर्ण
	ret = max8925_set_bits(chip->i2c, data->reg_mode_cntl, 0xfe, value);
	अगर (ret < 0)
		वापस ret;
	backlight_update_status(bl);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver max8925_backlight_driver = अणु
	.driver		= अणु
		.name	= "max8925-backlight",
	पूर्ण,
	.probe		= max8925_backlight_probe,
पूर्ण;

module_platक्रमm_driver(max8925_backlight_driver);

MODULE_DESCRIPTION("Backlight Driver for Maxim MAX8925");
MODULE_AUTHOR("Haojian Zhuang <haojian.zhuang@marvell.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:max8925-backlight");
