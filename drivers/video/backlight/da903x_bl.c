<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Backlight driver क्रम Dialog Semiconductor DA9030/DA9034
 *
 * Copyright (C) 2008 Compulab, Ltd.
 *	Mike Rapoport <mike@compulab.co.il>
 *
 * Copyright (C) 2006-2008 Marvell International Ltd.
 *	Eric Miao <eric.miao@marvell.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>
#समावेश <linux/mfd/da903x.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#घोषणा DA9030_WLED_CONTROL	0x25
#घोषणा DA9030_WLED_CP_EN	(1 << 6)
#घोषणा DA9030_WLED_TRIM(x)	((x) & 0x7)

#घोषणा DA9034_WLED_CONTROL1	0x3C
#घोषणा DA9034_WLED_CONTROL2	0x3D
#घोषणा DA9034_WLED_ISET(x)	((x) & 0x1f)

#घोषणा DA9034_WLED_BOOST_EN	(1 << 5)

#घोषणा DA9030_MAX_BRIGHTNESS	7
#घोषणा DA9034_MAX_BRIGHTNESS	0x7f

काष्ठा da903x_backlight_data अणु
	काष्ठा device *da903x_dev;
	पूर्णांक id;
	पूर्णांक current_brightness;
पूर्ण;

अटल पूर्णांक da903x_backlight_set(काष्ठा backlight_device *bl, पूर्णांक brightness)
अणु
	काष्ठा da903x_backlight_data *data = bl_get_data(bl);
	काष्ठा device *dev = data->da903x_dev;
	uपूर्णांक8_t val;
	पूर्णांक ret = 0;

	चयन (data->id) अणु
	हाल DA9034_ID_WLED:
		ret = da903x_update(dev, DA9034_WLED_CONTROL1,
				brightness, 0x7f);
		अगर (ret)
			वापस ret;

		अगर (data->current_brightness && brightness == 0)
			ret = da903x_clr_bits(dev,
					DA9034_WLED_CONTROL2,
					DA9034_WLED_BOOST_EN);

		अगर (data->current_brightness == 0 && brightness)
			ret = da903x_set_bits(dev,
					DA9034_WLED_CONTROL2,
					DA9034_WLED_BOOST_EN);
		अवरोध;
	हाल DA9030_ID_WLED:
		val = DA9030_WLED_TRIM(brightness);
		val |= brightness ? DA9030_WLED_CP_EN : 0;
		ret = da903x_ग_लिखो(dev, DA9030_WLED_CONTROL, val);
		अवरोध;
	पूर्ण

	अगर (ret)
		वापस ret;

	data->current_brightness = brightness;
	वापस 0;
पूर्ण

अटल पूर्णांक da903x_backlight_update_status(काष्ठा backlight_device *bl)
अणु
	वापस da903x_backlight_set(bl, backlight_get_brightness(bl));
पूर्ण

अटल पूर्णांक da903x_backlight_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा da903x_backlight_data *data = bl_get_data(bl);

	वापस data->current_brightness;
पूर्ण

अटल स्थिर काष्ठा backlight_ops da903x_backlight_ops = अणु
	.options	= BL_CORE_SUSPENDRESUME,
	.update_status	= da903x_backlight_update_status,
	.get_brightness	= da903x_backlight_get_brightness,
पूर्ण;

अटल पूर्णांक da903x_backlight_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9034_backlight_pdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा da903x_backlight_data *data;
	काष्ठा backlight_device *bl;
	काष्ठा backlight_properties props;
	पूर्णांक max_brightness;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	चयन (pdev->id) अणु
	हाल DA9030_ID_WLED:
		max_brightness = DA9030_MAX_BRIGHTNESS;
		अवरोध;
	हाल DA9034_ID_WLED:
		max_brightness = DA9034_MAX_BRIGHTNESS;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "invalid backlight device ID(%d)\n",
				pdev->id);
		वापस -EINVAL;
	पूर्ण

	data->id = pdev->id;
	data->da903x_dev = pdev->dev.parent;
	data->current_brightness = 0;

	/* adjust the WLED output current */
	अगर (pdata)
		da903x_ग_लिखो(data->da903x_dev, DA9034_WLED_CONTROL2,
				DA9034_WLED_ISET(pdata->output_current));

	स_रखो(&props, 0, माप(props));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = max_brightness;
	bl = devm_backlight_device_रेजिस्टर(&pdev->dev, pdev->name,
					data->da903x_dev, data,
					&da903x_backlight_ops, &props);
	अगर (IS_ERR(bl)) अणु
		dev_err(&pdev->dev, "failed to register backlight\n");
		वापस PTR_ERR(bl);
	पूर्ण

	bl->props.brightness = max_brightness;

	platक्रमm_set_drvdata(pdev, bl);
	backlight_update_status(bl);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da903x_backlight_driver = अणु
	.driver		= अणु
		.name	= "da903x-backlight",
	पूर्ण,
	.probe		= da903x_backlight_probe,
पूर्ण;

module_platक्रमm_driver(da903x_backlight_driver);

MODULE_DESCRIPTION("Backlight Driver for Dialog Semiconductor DA9030/DA9034");
MODULE_AUTHOR("Eric Miao <eric.miao@marvell.com>");
MODULE_AUTHOR("Mike Rapoport <mike@compulab.co.il>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da903x-backlight");
