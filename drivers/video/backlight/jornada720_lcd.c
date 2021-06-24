<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * LCD driver क्रम HP Jornada 700 series (710/720/728)
 * Copyright (C) 2006-2009 Kristoffer Ericson <kristoffer.ericson@gmail.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/fb.h>
#समावेश <linux/kernel.h>
#समावेश <linux/lcd.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>

#समावेश <mach/jornada720.h>
#समावेश <mach/hardware.h>

#समावेश <video/s1d13xxxfb.h>

#घोषणा LCD_MAX_CONTRAST	0xff
#घोषणा LCD_DEF_CONTRAST	0x80

अटल पूर्णांक jornada_lcd_get_घातer(काष्ठा lcd_device *ld)
अणु
	वापस PPSR & PPC_LDD2 ? FB_BLANK_UNBLANK : FB_BLANK_POWERDOWN;
पूर्ण

अटल पूर्णांक jornada_lcd_get_contrast(काष्ठा lcd_device *ld)
अणु
	पूर्णांक ret;

	अगर (jornada_lcd_get_घातer(ld) != FB_BLANK_UNBLANK)
		वापस 0;

	jornada_ssp_start();

	अगर (jornada_ssp_byte(GETCONTRAST) == TXDUMMY) अणु
		ret = jornada_ssp_byte(TXDUMMY);
		जाओ success;
	पूर्ण

	dev_err(&ld->dev, "failed to set contrast\n");
	ret = -ETIMEDOUT;

success:
	jornada_ssp_end();
	वापस ret;
पूर्ण

अटल पूर्णांक jornada_lcd_set_contrast(काष्ठा lcd_device *ld, पूर्णांक value)
अणु
	पूर्णांक ret = 0;

	jornada_ssp_start();

	/* start by sending our set contrast cmd to mcu */
	अगर (jornada_ssp_byte(SETCONTRAST) == TXDUMMY) अणु
		/* अगर successful push the new value */
		अगर (jornada_ssp_byte(value) == TXDUMMY)
			जाओ success;
	पूर्ण

	dev_err(&ld->dev, "failed to set contrast\n");
	ret = -ETIMEDOUT;

success:
	jornada_ssp_end();
	वापस ret;
पूर्ण

अटल पूर्णांक jornada_lcd_set_घातer(काष्ठा lcd_device *ld, पूर्णांक घातer)
अणु
	अगर (घातer != FB_BLANK_UNBLANK) अणु
		PPSR &= ~PPC_LDD2;
		PPDR |= PPC_LDD2;
	पूर्ण अन्यथा अणु
		PPSR |= PPC_LDD2;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा lcd_ops jornada_lcd_props = अणु
	.get_contrast = jornada_lcd_get_contrast,
	.set_contrast = jornada_lcd_set_contrast,
	.get_घातer = jornada_lcd_get_घातer,
	.set_घातer = jornada_lcd_set_घातer,
पूर्ण;

अटल पूर्णांक jornada_lcd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lcd_device *lcd_device;
	पूर्णांक ret;

	lcd_device = devm_lcd_device_रेजिस्टर(&pdev->dev, S1D_DEVICENAME,
					&pdev->dev, शून्य, &jornada_lcd_props);

	अगर (IS_ERR(lcd_device)) अणु
		ret = PTR_ERR(lcd_device);
		dev_err(&pdev->dev, "failed to register device\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, lcd_device);

	/* lets set our शेष values */
	jornada_lcd_set_contrast(lcd_device, LCD_DEF_CONTRAST);
	jornada_lcd_set_घातer(lcd_device, FB_BLANK_UNBLANK);
	/* give it some समय to startup */
	msleep(100);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver jornada_lcd_driver = अणु
	.probe	= jornada_lcd_probe,
	.driver	= अणु
		.name	= "jornada_lcd",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(jornada_lcd_driver);

MODULE_AUTHOR("Kristoffer Ericson <kristoffer.ericson@gmail.com>");
MODULE_DESCRIPTION("HP Jornada 710/720/728 LCD driver");
MODULE_LICENSE("GPL");
