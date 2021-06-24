<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Based on drivers/video/omap/lcd_inn1510.c
 *
 * LCD panel support क्रम the Amstrad E3 (Delta) videophone.
 *
 * Copyright (C) 2006 Jonathan McDowell <noodles@earth.li>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/lcd.h>

#समावेश <mach/hardware.h>

#समावेश "omapfb.h"

#घोषणा AMS_DELTA_DEFAULT_CONTRAST	112

#घोषणा AMS_DELTA_MAX_CONTRAST		0x00FF
#घोषणा AMS_DELTA_LCD_POWER		0x0100


/* LCD class device section */

अटल पूर्णांक ams_delta_lcd;
अटल काष्ठा gpio_desc *gpiod_vblen;
अटल काष्ठा gpio_desc *gpiod_ndisp;

अटल पूर्णांक ams_delta_lcd_set_घातer(काष्ठा lcd_device *dev, पूर्णांक घातer)
अणु
	अगर (घातer == FB_BLANK_UNBLANK) अणु
		अगर (!(ams_delta_lcd & AMS_DELTA_LCD_POWER)) अणु
			omap_ग_लिखोb(ams_delta_lcd & AMS_DELTA_MAX_CONTRAST,
					OMAP_PWL_ENABLE);
			omap_ग_लिखोb(1, OMAP_PWL_CLK_ENABLE);
			ams_delta_lcd |= AMS_DELTA_LCD_POWER;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ams_delta_lcd & AMS_DELTA_LCD_POWER) अणु
			omap_ग_लिखोb(0, OMAP_PWL_ENABLE);
			omap_ग_लिखोb(0, OMAP_PWL_CLK_ENABLE);
			ams_delta_lcd &= ~AMS_DELTA_LCD_POWER;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ams_delta_lcd_set_contrast(काष्ठा lcd_device *dev, पूर्णांक value)
अणु
	अगर ((value >= 0) && (value <= AMS_DELTA_MAX_CONTRAST)) अणु
		omap_ग_लिखोb(value, OMAP_PWL_ENABLE);
		ams_delta_lcd &= ~AMS_DELTA_MAX_CONTRAST;
		ams_delta_lcd |= value;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_LCD_CLASS_DEVICE
अटल पूर्णांक ams_delta_lcd_get_घातer(काष्ठा lcd_device *dev)
अणु
	अगर (ams_delta_lcd & AMS_DELTA_LCD_POWER)
		वापस FB_BLANK_UNBLANK;
	अन्यथा
		वापस FB_BLANK_POWERDOWN;
पूर्ण

अटल पूर्णांक ams_delta_lcd_get_contrast(काष्ठा lcd_device *dev)
अणु
	अगर (!(ams_delta_lcd & AMS_DELTA_LCD_POWER))
		वापस 0;

	वापस ams_delta_lcd & AMS_DELTA_MAX_CONTRAST;
पूर्ण

अटल काष्ठा lcd_ops ams_delta_lcd_ops = अणु
	.get_घातer = ams_delta_lcd_get_घातer,
	.set_घातer = ams_delta_lcd_set_घातer,
	.get_contrast = ams_delta_lcd_get_contrast,
	.set_contrast = ams_delta_lcd_set_contrast,
पूर्ण;
#पूर्ण_अगर


/* omapfb panel section */

अटल पूर्णांक ams_delta_panel_enable(काष्ठा lcd_panel *panel)
अणु
	gpiod_set_value(gpiod_ndisp, 1);
	gpiod_set_value(gpiod_vblen, 1);
	वापस 0;
पूर्ण

अटल व्योम ams_delta_panel_disable(काष्ठा lcd_panel *panel)
अणु
	gpiod_set_value(gpiod_vblen, 0);
	gpiod_set_value(gpiod_ndisp, 0);
पूर्ण

अटल काष्ठा lcd_panel ams_delta_panel = अणु
	.name		= "ams-delta",
	.config		= 0,

	.bpp		= 12,
	.data_lines	= 16,
	.x_res		= 480,
	.y_res		= 320,
	.pixel_घड़ी	= 4687,
	.hsw		= 3,
	.hfp		= 1,
	.hbp		= 1,
	.vsw		= 1,
	.vfp		= 0,
	.vbp		= 0,
	.pcd		= 0,
	.acb		= 37,

	.enable		= ams_delta_panel_enable,
	.disable	= ams_delta_panel_disable,
पूर्ण;


/* platक्रमm driver section */

अटल पूर्णांक ams_delta_panel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lcd_device *lcd_device = शून्य;
	पूर्णांक ret;

	gpiod_vblen = devm_gpiod_get(&pdev->dev, "vblen", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpiod_vblen)) अणु
		ret = PTR_ERR(gpiod_vblen);
		dev_err(&pdev->dev, "VBLEN GPIO request failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	gpiod_ndisp = devm_gpiod_get(&pdev->dev, "ndisp", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpiod_ndisp)) अणु
		ret = PTR_ERR(gpiod_ndisp);
		dev_err(&pdev->dev, "NDISP GPIO request failed (%d)\n", ret);
		वापस ret;
	पूर्ण

#अगर_घोषित CONFIG_LCD_CLASS_DEVICE
	lcd_device = lcd_device_रेजिस्टर("omapfb", &pdev->dev, शून्य,
						&ams_delta_lcd_ops);

	अगर (IS_ERR(lcd_device)) अणु
		ret = PTR_ERR(lcd_device);
		dev_err(&pdev->dev, "failed to register device\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, lcd_device);
	lcd_device->props.max_contrast = AMS_DELTA_MAX_CONTRAST;
#पूर्ण_अगर

	ams_delta_lcd_set_contrast(lcd_device, AMS_DELTA_DEFAULT_CONTRAST);
	ams_delta_lcd_set_घातer(lcd_device, FB_BLANK_UNBLANK);

	omapfb_रेजिस्टर_panel(&ams_delta_panel);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ams_delta_panel_driver = अणु
	.probe		= ams_delta_panel_probe,
	.driver		= अणु
		.name	= "lcd_ams_delta",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ams_delta_panel_driver);

MODULE_AUTHOR("Jonathan McDowell <noodles@earth.li>");
MODULE_DESCRIPTION("LCD panel support for the Amstrad E3 (Delta) videophone");
MODULE_LICENSE("GPL");
