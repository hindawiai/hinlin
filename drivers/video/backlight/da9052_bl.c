<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Backlight Driver क्रम Dialog DA9052 PMICs
 *
 * Copyright(c) 2012 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mfd/da9052/da9052.h>
#समावेश <linux/mfd/da9052/reg.h>

#घोषणा DA9052_MAX_BRIGHTNESS		0xFF

क्रमागत अणु
	DA9052_WLEDS_OFF,
	DA9052_WLEDS_ON,
पूर्ण;

क्रमागत अणु
	DA9052_TYPE_WLED1,
	DA9052_TYPE_WLED2,
	DA9052_TYPE_WLED3,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर wled_bank[] = अणु
	DA9052_LED1_CONF_REG,
	DA9052_LED2_CONF_REG,
	DA9052_LED3_CONF_REG,
पूर्ण;

काष्ठा da9052_bl अणु
	काष्ठा da9052 *da9052;
	uपूर्णांक brightness;
	uपूर्णांक state;
	uपूर्णांक led_reg;
पूर्ण;

अटल पूर्णांक da9052_adjust_wled_brightness(काष्ठा da9052_bl *wleds)
अणु
	अचिन्हित अक्षर boost_en;
	अचिन्हित अक्षर i_sink;
	पूर्णांक ret;

	boost_en = 0x3F;
	i_sink = 0xFF;
	अगर (wleds->state == DA9052_WLEDS_OFF) अणु
		boost_en = 0x00;
		i_sink = 0x00;
	पूर्ण

	ret = da9052_reg_ग_लिखो(wleds->da9052, DA9052_BOOST_REG, boost_en);
	अगर (ret < 0)
		वापस ret;

	ret = da9052_reg_ग_लिखो(wleds->da9052, DA9052_LED_CONT_REG, i_sink);
	अगर (ret < 0)
		वापस ret;

	ret = da9052_reg_ग_लिखो(wleds->da9052, wled_bank[wleds->led_reg], 0x0);
	अगर (ret < 0)
		वापस ret;

	usleep_range(10000, 11000);

	अगर (wleds->brightness) अणु
		ret = da9052_reg_ग_लिखो(wleds->da9052, wled_bank[wleds->led_reg],
				       wleds->brightness);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da9052_backlight_update_status(काष्ठा backlight_device *bl)
अणु
	पूर्णांक brightness = bl->props.brightness;
	काष्ठा da9052_bl *wleds = bl_get_data(bl);

	wleds->brightness = brightness;
	wleds->state = DA9052_WLEDS_ON;

	वापस da9052_adjust_wled_brightness(wleds);
पूर्ण

अटल पूर्णांक da9052_backlight_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा da9052_bl *wleds = bl_get_data(bl);

	वापस wleds->brightness;
पूर्ण

अटल स्थिर काष्ठा backlight_ops da9052_backlight_ops = अणु
	.update_status = da9052_backlight_update_status,
	.get_brightness = da9052_backlight_get_brightness,
पूर्ण;

अटल पूर्णांक da9052_backlight_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_device *bl;
	काष्ठा backlight_properties props;
	काष्ठा da9052_bl *wleds;

	wleds = devm_kzalloc(&pdev->dev, माप(काष्ठा da9052_bl), GFP_KERNEL);
	अगर (!wleds)
		वापस -ENOMEM;

	wleds->da9052 = dev_get_drvdata(pdev->dev.parent);
	wleds->brightness = 0;
	wleds->led_reg = platक्रमm_get_device_id(pdev)->driver_data;
	wleds->state = DA9052_WLEDS_OFF;

	props.type = BACKLIGHT_RAW;
	props.max_brightness = DA9052_MAX_BRIGHTNESS;

	bl = devm_backlight_device_रेजिस्टर(&pdev->dev, pdev->name,
					wleds->da9052->dev, wleds,
					&da9052_backlight_ops, &props);
	अगर (IS_ERR(bl)) अणु
		dev_err(&pdev->dev, "Failed to register backlight\n");
		वापस PTR_ERR(bl);
	पूर्ण

	bl->props.max_brightness = DA9052_MAX_BRIGHTNESS;
	bl->props.brightness = 0;
	platक्रमm_set_drvdata(pdev, bl);

	वापस da9052_adjust_wled_brightness(wleds);
पूर्ण

अटल पूर्णांक da9052_backlight_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_device *bl = platक्रमm_get_drvdata(pdev);
	काष्ठा da9052_bl *wleds = bl_get_data(bl);

	wleds->brightness = 0;
	wleds->state = DA9052_WLEDS_OFF;
	da9052_adjust_wled_brightness(wleds);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id da9052_wled_ids[] = अणु
	अणु
		.name		= "da9052-wled1",
		.driver_data	= DA9052_TYPE_WLED1,
	पूर्ण,
	अणु
		.name		= "da9052-wled2",
		.driver_data	= DA9052_TYPE_WLED2,
	पूर्ण,
	अणु
		.name		= "da9052-wled3",
		.driver_data	= DA9052_TYPE_WLED3,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, da9052_wled_ids);

अटल काष्ठा platक्रमm_driver da9052_wled_driver = अणु
	.probe		= da9052_backlight_probe,
	.हटाओ		= da9052_backlight_हटाओ,
	.id_table	= da9052_wled_ids,
	.driver	= अणु
		.name	= "da9052-wled",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(da9052_wled_driver);

MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
MODULE_DESCRIPTION("Backlight driver for DA9052 PMIC");
MODULE_LICENSE("GPL");
