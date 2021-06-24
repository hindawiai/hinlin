<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Backlight driver क्रम Wolfson Microelectronics WM831x PMICs
 *
 * Copyright 2009 Wolfson Microelectonics plc
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>
#समावेश <linux/slab.h>

#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/pdata.h>
#समावेश <linux/mfd/wm831x/regulator.h>

काष्ठा wm831x_backlight_data अणु
	काष्ठा wm831x *wm831x;
	पूर्णांक isink_reg;
	पूर्णांक current_brightness;
पूर्ण;

अटल पूर्णांक wm831x_backlight_set(काष्ठा backlight_device *bl, पूर्णांक brightness)
अणु
	काष्ठा wm831x_backlight_data *data = bl_get_data(bl);
	काष्ठा wm831x *wm831x = data->wm831x;
	पूर्णांक घातer_up = !data->current_brightness && brightness;
	पूर्णांक घातer_करोwn = data->current_brightness && !brightness;
	पूर्णांक ret;

	अगर (घातer_up) अणु
		/* Enable the ISINK */
		ret = wm831x_set_bits(wm831x, data->isink_reg,
				      WM831X_CS1_ENA, WM831X_CS1_ENA);
		अगर (ret < 0)
			जाओ err;

		/* Enable the DC-DC */
		ret = wm831x_set_bits(wm831x, WM831X_DCDC_ENABLE,
				      WM831X_DC4_ENA, WM831X_DC4_ENA);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	अगर (घातer_करोwn) अणु
		/* DCDC first */
		ret = wm831x_set_bits(wm831x, WM831X_DCDC_ENABLE,
				      WM831X_DC4_ENA, 0);
		अगर (ret < 0)
			जाओ err;

		/* ISINK */
		ret = wm831x_set_bits(wm831x, data->isink_reg,
				      WM831X_CS1_DRIVE | WM831X_CS1_ENA, 0);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	/* Set the new brightness */
	ret = wm831x_set_bits(wm831x, data->isink_reg,
			      WM831X_CS1_ISEL_MASK, brightness);
	अगर (ret < 0)
		जाओ err;

	अगर (घातer_up) अणु
		/* Drive current through the ISINK */
		ret = wm831x_set_bits(wm831x, data->isink_reg,
				      WM831X_CS1_DRIVE, WM831X_CS1_DRIVE);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	data->current_brightness = brightness;

	वापस 0;

err:
	/* If we were in the middle of a घातer transition always shut करोwn
	 * क्रम safety.
	 */
	अगर (घातer_up || घातer_करोwn) अणु
		wm831x_set_bits(wm831x, WM831X_DCDC_ENABLE, WM831X_DC4_ENA, 0);
		wm831x_set_bits(wm831x, data->isink_reg, WM831X_CS1_ENA, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक wm831x_backlight_update_status(काष्ठा backlight_device *bl)
अणु
	वापस wm831x_backlight_set(bl, backlight_get_brightness(bl));
पूर्ण

अटल पूर्णांक wm831x_backlight_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा wm831x_backlight_data *data = bl_get_data(bl);

	वापस data->current_brightness;
पूर्ण

अटल स्थिर काष्ठा backlight_ops wm831x_backlight_ops = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.update_status	= wm831x_backlight_update_status,
	.get_brightness	= wm831x_backlight_get_brightness,
पूर्ण;

अटल पूर्णांक wm831x_backlight_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_pdata *wm831x_pdata = dev_get_platdata(pdev->dev.parent);
	काष्ठा wm831x_backlight_pdata *pdata;
	काष्ठा wm831x_backlight_data *data;
	काष्ठा backlight_device *bl;
	काष्ठा backlight_properties props;
	पूर्णांक ret, i, max_isel, isink_reg, dcdc_cfg;

	/* We need platक्रमm data */
	अगर (wm831x_pdata)
		pdata = wm831x_pdata->backlight;
	अन्यथा
		pdata = शून्य;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "No platform data supplied\n");
		वापस -EINVAL;
	पूर्ण

	/* Figure out the maximum current we can use */
	क्रम (i = 0; i < WM831X_ISINK_MAX_ISEL; i++) अणु
		अगर (wm831x_isinkv_values[i] > pdata->max_uA)
			अवरोध;
	पूर्ण

	अगर (i == 0) अणु
		dev_err(&pdev->dev, "Invalid max_uA: %duA\n", pdata->max_uA);
		वापस -EINVAL;
	पूर्ण
	max_isel = i - 1;

	अगर (pdata->max_uA != wm831x_isinkv_values[max_isel])
		dev_warn(&pdev->dev,
			 "Maximum current is %duA not %duA as requested\n",
			 wm831x_isinkv_values[max_isel], pdata->max_uA);

	चयन (pdata->isink) अणु
	हाल 1:
		isink_reg = WM831X_CURRENT_SINK_1;
		dcdc_cfg = 0;
		अवरोध;
	हाल 2:
		isink_reg = WM831X_CURRENT_SINK_2;
		dcdc_cfg = WM831X_DC4_FBSRC;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Invalid ISINK %d\n", pdata->isink);
		वापस -EINVAL;
	पूर्ण

	/* Configure the ISINK to use क्रम feedback */
	ret = wm831x_reg_unlock(wm831x);
	अगर (ret < 0)
		वापस ret;

	ret = wm831x_set_bits(wm831x, WM831X_DC4_CONTROL, WM831X_DC4_FBSRC,
			      dcdc_cfg);

	wm831x_reg_lock(wm831x);
	अगर (ret < 0)
		वापस ret;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	data->wm831x = wm831x;
	data->current_brightness = 0;
	data->isink_reg = isink_reg;

	स_रखो(&props, 0, माप(props));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = max_isel;
	bl = devm_backlight_device_रेजिस्टर(&pdev->dev, "wm831x", &pdev->dev,
					data, &wm831x_backlight_ops, &props);
	अगर (IS_ERR(bl)) अणु
		dev_err(&pdev->dev, "failed to register backlight\n");
		वापस PTR_ERR(bl);
	पूर्ण

	bl->props.brightness = max_isel;

	platक्रमm_set_drvdata(pdev, bl);

	/* Disable the DCDC अगर it was started so we can bootstrap */
	wm831x_set_bits(wm831x, WM831X_DCDC_ENABLE, WM831X_DC4_ENA, 0);

	backlight_update_status(bl);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_backlight_driver = अणु
	.driver		= अणु
		.name	= "wm831x-backlight",
	पूर्ण,
	.probe		= wm831x_backlight_probe,
पूर्ण;

module_platक्रमm_driver(wm831x_backlight_driver);

MODULE_DESCRIPTION("Backlight Driver for WM831x PMICs");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm831x-backlight");
