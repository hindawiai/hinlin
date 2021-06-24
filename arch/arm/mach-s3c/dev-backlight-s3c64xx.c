<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2011 Samsung Electronics Co., Ltd.
//              http://www.samsung.com
//
// Common infraकाष्ठाure क्रम PWM Backlight क्रम Samsung boards

#समावेश <linux/gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/pwm_backlight.h>

#समावेश "devs.h"
#समावेश "gpio-cfg.h"

#समावेश "backlight-s3c64xx.h"

काष्ठा samsung_bl_drvdata अणु
	काष्ठा platक्रमm_pwm_backlight_data plat_data;
	काष्ठा samsung_bl_gpio_info *gpio_info;
पूर्ण;

अटल पूर्णांक samsung_bl_init(काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा platक्रमm_pwm_backlight_data *pdata = dev->platक्रमm_data;
	काष्ठा samsung_bl_drvdata *drvdata = container_of(pdata,
					काष्ठा samsung_bl_drvdata, plat_data);
	काष्ठा samsung_bl_gpio_info *bl_gpio_info = drvdata->gpio_info;

	ret = gpio_request(bl_gpio_info->no, "Backlight");
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "failed to request GPIO for LCD Backlight\n");
		वापस ret;
	पूर्ण

	/* Configure GPIO pin with specअगरic GPIO function क्रम PWM समयr */
	s3c_gpio_cfgpin(bl_gpio_info->no, bl_gpio_info->func);

	वापस 0;
पूर्ण

अटल व्योम samsung_bl_निकास(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_pwm_backlight_data *pdata = dev->platक्रमm_data;
	काष्ठा samsung_bl_drvdata *drvdata = container_of(pdata,
					काष्ठा samsung_bl_drvdata, plat_data);
	काष्ठा samsung_bl_gpio_info *bl_gpio_info = drvdata->gpio_info;

	s3c_gpio_cfgpin(bl_gpio_info->no, S3C_GPIO_OUTPUT);
	gpio_मुक्त(bl_gpio_info->no);
पूर्ण

/* Initialize few important fields of platक्रमm_pwm_backlight_data
 * काष्ठाure with शेष values. These fields can be overridden by
 * board-specअगरic values sent from machine file.
 * For ease of operation, these fields are initialized with values
 * used by most samsung boards.
 * Users has the option of sending info about other parameters
 * क्रम their specअगरic boards
 */

अटल काष्ठा samsung_bl_drvdata samsung_dfl_bl_data __initdata = अणु
	.plat_data = अणु
		.max_brightness = 255,
		.dft_brightness = 255,
		.init           = samsung_bl_init,
		.निकास           = samsung_bl_निकास,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device samsung_dfl_bl_device __initdata = अणु
	.name		= "pwm-backlight",
पूर्ण;

/* samsung_bl_set - Set board specअगरic data (अगर any) provided by user क्रम
 * PWM Backlight control and रेजिस्टर specअगरic PWM and backlight device.
 * @gpio_info:	काष्ठाure containing GPIO info क्रम PWM समयr
 * @bl_data:	काष्ठाure containing Backlight control data
 */
व्योम __init samsung_bl_set(काष्ठा samsung_bl_gpio_info *gpio_info,
	काष्ठा platक्रमm_pwm_backlight_data *bl_data)
अणु
	पूर्णांक ret = 0;
	काष्ठा platक्रमm_device *samsung_bl_device;
	काष्ठा samsung_bl_drvdata *samsung_bl_drvdata;
	काष्ठा platक्रमm_pwm_backlight_data *samsung_bl_data;

	samsung_bl_device = kmemdup(&samsung_dfl_bl_device,
			माप(काष्ठा platक्रमm_device), GFP_KERNEL);
	अगर (!samsung_bl_device)
		वापस;

	samsung_bl_drvdata = kmemdup(&samsung_dfl_bl_data,
				माप(samsung_dfl_bl_data), GFP_KERNEL);
	अगर (!samsung_bl_drvdata)
		जाओ err_data;

	samsung_bl_device->dev.platक्रमm_data = &samsung_bl_drvdata->plat_data;
	samsung_bl_drvdata->gpio_info = gpio_info;
	samsung_bl_data = &samsung_bl_drvdata->plat_data;

	/* Copy board specअगरic data provided by user */
	samsung_bl_device->dev.parent = &samsung_device_pwm.dev;

	अगर (bl_data->max_brightness)
		samsung_bl_data->max_brightness = bl_data->max_brightness;
	अगर (bl_data->dft_brightness)
		samsung_bl_data->dft_brightness = bl_data->dft_brightness;
	अगर (bl_data->lth_brightness)
		samsung_bl_data->lth_brightness = bl_data->lth_brightness;
	अगर (bl_data->init)
		samsung_bl_data->init = bl_data->init;
	अगर (bl_data->notअगरy)
		samsung_bl_data->notअगरy = bl_data->notअगरy;
	अगर (bl_data->notअगरy_after)
		samsung_bl_data->notअगरy_after = bl_data->notअगरy_after;
	अगर (bl_data->निकास)
		samsung_bl_data->निकास = bl_data->निकास;
	अगर (bl_data->check_fb)
		samsung_bl_data->check_fb = bl_data->check_fb;

	/* Register the Backlight dev */
	ret = platक्रमm_device_रेजिस्टर(samsung_bl_device);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "failed to register backlight device: %d\n", ret);
		जाओ err_plat_reg2;
	पूर्ण

	वापस;

err_plat_reg2:
	kमुक्त(samsung_bl_data);
err_data:
	kमुक्त(samsung_bl_device);
पूर्ण
