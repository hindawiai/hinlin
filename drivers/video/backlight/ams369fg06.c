<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ams369fg06 AMOLED LCD panel driver.
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Author: Jingoo Han  <jg1.han@samsung.com>
 *
 * Derived from drivers/video/s6e63m0.c
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/lcd.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/रुको.h>

#घोषणा SLEEPMSEC		0x1000
#घोषणा ENDDEF			0x2000
#घोषणा	DEFMASK			0xFF00
#घोषणा COMMAND_ONLY		0xFE
#घोषणा DATA_ONLY		0xFF

#घोषणा MAX_GAMMA_LEVEL		5
#घोषणा GAMMA_TABLE_COUNT	21

#घोषणा MIN_BRIGHTNESS		0
#घोषणा MAX_BRIGHTNESS		255
#घोषणा DEFAULT_BRIGHTNESS	150

काष्ठा ams369fg06 अणु
	काष्ठा device			*dev;
	काष्ठा spi_device		*spi;
	अचिन्हित पूर्णांक			घातer;
	काष्ठा lcd_device		*ld;
	काष्ठा backlight_device		*bd;
	काष्ठा lcd_platक्रमm_data	*lcd_pd;
पूर्ण;

अटल स्थिर अचिन्हित लघु seq_display_on[] = अणु
	0x14, 0x03,
	ENDDEF, 0x0000
पूर्ण;

अटल स्थिर अचिन्हित लघु seq_display_off[] = अणु
	0x14, 0x00,
	ENDDEF, 0x0000
पूर्ण;

अटल स्थिर अचिन्हित लघु seq_stand_by_on[] = अणु
	0x1D, 0xA1,
	SLEEPMSEC, 200,
	ENDDEF, 0x0000
पूर्ण;

अटल स्थिर अचिन्हित लघु seq_stand_by_off[] = अणु
	0x1D, 0xA0,
	SLEEPMSEC, 250,
	ENDDEF, 0x0000
पूर्ण;

अटल स्थिर अचिन्हित लघु seq_setting[] = अणु
	0x31, 0x08,
	0x32, 0x14,
	0x30, 0x02,
	0x27, 0x01,
	0x12, 0x08,
	0x13, 0x08,
	0x15, 0x00,
	0x16, 0x00,

	0xef, 0xd0,
	DATA_ONLY, 0xe8,

	0x39, 0x44,
	0x40, 0x00,
	0x41, 0x3f,
	0x42, 0x2a,
	0x43, 0x27,
	0x44, 0x27,
	0x45, 0x1f,
	0x46, 0x44,
	0x50, 0x00,
	0x51, 0x00,
	0x52, 0x17,
	0x53, 0x24,
	0x54, 0x26,
	0x55, 0x1f,
	0x56, 0x43,
	0x60, 0x00,
	0x61, 0x3f,
	0x62, 0x2a,
	0x63, 0x25,
	0x64, 0x24,
	0x65, 0x1b,
	0x66, 0x5c,

	0x17, 0x22,
	0x18, 0x33,
	0x19, 0x03,
	0x1a, 0x01,
	0x22, 0xa4,
	0x23, 0x00,
	0x26, 0xa0,

	0x1d, 0xa0,
	SLEEPMSEC, 300,

	0x14, 0x03,

	ENDDEF, 0x0000
पूर्ण;

/* gamma value: 2.2 */
अटल स्थिर अचिन्हित पूर्णांक ams369fg06_22_250[] = अणु
	0x00, 0x3f, 0x2a, 0x27, 0x27, 0x1f, 0x44,
	0x00, 0x00, 0x17, 0x24, 0x26, 0x1f, 0x43,
	0x00, 0x3f, 0x2a, 0x25, 0x24, 0x1b, 0x5c,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ams369fg06_22_200[] = अणु
	0x00, 0x3f, 0x28, 0x29, 0x27, 0x21, 0x3e,
	0x00, 0x00, 0x10, 0x25, 0x27, 0x20, 0x3d,
	0x00, 0x3f, 0x28, 0x27, 0x25, 0x1d, 0x53,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ams369fg06_22_150[] = अणु
	0x00, 0x3f, 0x2d, 0x29, 0x28, 0x23, 0x37,
	0x00, 0x00, 0x0b, 0x25, 0x28, 0x22, 0x36,
	0x00, 0x3f, 0x2b, 0x28, 0x26, 0x1f, 0x4a,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ams369fg06_22_100[] = अणु
	0x00, 0x3f, 0x30, 0x2a, 0x2b, 0x24, 0x2f,
	0x00, 0x00, 0x00, 0x25, 0x29, 0x24, 0x2e,
	0x00, 0x3f, 0x2f, 0x29, 0x29, 0x21, 0x3f,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ams369fg06_22_50[] = अणु
	0x00, 0x3f, 0x3c, 0x2c, 0x2d, 0x27, 0x24,
	0x00, 0x00, 0x00, 0x22, 0x2a, 0x27, 0x23,
	0x00, 0x3f, 0x3b, 0x2c, 0x2b, 0x24, 0x31,
पूर्ण;

काष्ठा ams369fg06_gamma अणु
	अचिन्हित पूर्णांक *gamma_22_table[MAX_GAMMA_LEVEL];
पूर्ण;

अटल काष्ठा ams369fg06_gamma gamma_table = अणु
	.gamma_22_table[0] = (अचिन्हित पूर्णांक *)&ams369fg06_22_50,
	.gamma_22_table[1] = (अचिन्हित पूर्णांक *)&ams369fg06_22_100,
	.gamma_22_table[2] = (अचिन्हित पूर्णांक *)&ams369fg06_22_150,
	.gamma_22_table[3] = (अचिन्हित पूर्णांक *)&ams369fg06_22_200,
	.gamma_22_table[4] = (अचिन्हित पूर्णांक *)&ams369fg06_22_250,
पूर्ण;

अटल पूर्णांक ams369fg06_spi_ग_लिखो_byte(काष्ठा ams369fg06 *lcd, पूर्णांक addr, पूर्णांक data)
अणु
	u16 buf[1];
	काष्ठा spi_message msg;

	काष्ठा spi_transfer xfer = अणु
		.len		= 2,
		.tx_buf		= buf,
	पूर्ण;

	buf[0] = (addr << 8) | data;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	वापस spi_sync(lcd->spi, &msg);
पूर्ण

अटल पूर्णांक ams369fg06_spi_ग_लिखो(काष्ठा ams369fg06 *lcd, अचिन्हित अक्षर address,
	अचिन्हित अक्षर command)
अणु
	पूर्णांक ret = 0;

	अगर (address != DATA_ONLY)
		ret = ams369fg06_spi_ग_लिखो_byte(lcd, 0x70, address);
	अगर (command != COMMAND_ONLY)
		ret = ams369fg06_spi_ग_लिखो_byte(lcd, 0x72, command);

	वापस ret;
पूर्ण

अटल पूर्णांक ams369fg06_panel_send_sequence(काष्ठा ams369fg06 *lcd,
	स्थिर अचिन्हित लघु *wbuf)
अणु
	पूर्णांक ret = 0, i = 0;

	जबतक ((wbuf[i] & DEFMASK) != ENDDEF) अणु
		अगर ((wbuf[i] & DEFMASK) != SLEEPMSEC) अणु
			ret = ams369fg06_spi_ग_लिखो(lcd, wbuf[i], wbuf[i+1]);
			अगर (ret)
				अवरोध;
		पूर्ण अन्यथा अणु
			msleep(wbuf[i+1]);
		पूर्ण
		i += 2;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक _ams369fg06_gamma_ctl(काष्ठा ams369fg06 *lcd,
	स्थिर अचिन्हित पूर्णांक *gamma)
अणु
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक ret = 0;

	क्रम (i = 0 ; i < GAMMA_TABLE_COUNT / 3; i++) अणु
		ret = ams369fg06_spi_ग_लिखो(lcd, 0x40 + i, gamma[i]);
		ret = ams369fg06_spi_ग_लिखो(lcd, 0x50 + i, gamma[i+7*1]);
		ret = ams369fg06_spi_ग_लिखो(lcd, 0x60 + i, gamma[i+7*2]);
		अगर (ret) अणु
			dev_err(lcd->dev, "failed to set gamma table.\n");
			जाओ gamma_err;
		पूर्ण
	पूर्ण

gamma_err:
	वापस ret;
पूर्ण

अटल पूर्णांक ams369fg06_gamma_ctl(काष्ठा ams369fg06 *lcd, पूर्णांक brightness)
अणु
	पूर्णांक ret = 0;
	पूर्णांक gamma = 0;

	अगर ((brightness >= 0) && (brightness <= 50))
		gamma = 0;
	अन्यथा अगर ((brightness > 50) && (brightness <= 100))
		gamma = 1;
	अन्यथा अगर ((brightness > 100) && (brightness <= 150))
		gamma = 2;
	अन्यथा अगर ((brightness > 150) && (brightness <= 200))
		gamma = 3;
	अन्यथा अगर ((brightness > 200) && (brightness <= 255))
		gamma = 4;

	ret = _ams369fg06_gamma_ctl(lcd, gamma_table.gamma_22_table[gamma]);

	वापस ret;
पूर्ण

अटल पूर्णांक ams369fg06_ldi_init(काष्ठा ams369fg06 *lcd)
अणु
	पूर्णांक ret, i;
	अटल स्थिर अचिन्हित लघु *init_seq[] = अणु
		seq_setting,
		seq_stand_by_off,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(init_seq); i++) अणु
		ret = ams369fg06_panel_send_sequence(lcd, init_seq[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ams369fg06_ldi_enable(काष्ठा ams369fg06 *lcd)
अणु
	पूर्णांक ret, i;
	अटल स्थिर अचिन्हित लघु *init_seq[] = अणु
		seq_stand_by_off,
		seq_display_on,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(init_seq); i++) अणु
		ret = ams369fg06_panel_send_sequence(lcd, init_seq[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ams369fg06_ldi_disable(काष्ठा ams369fg06 *lcd)
अणु
	पूर्णांक ret, i;

	अटल स्थिर अचिन्हित लघु *init_seq[] = अणु
		seq_display_off,
		seq_stand_by_on,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(init_seq); i++) अणु
		ret = ams369fg06_panel_send_sequence(lcd, init_seq[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ams369fg06_घातer_is_on(पूर्णांक घातer)
अणु
	वापस घातer <= FB_BLANK_NORMAL;
पूर्ण

अटल पूर्णांक ams369fg06_घातer_on(काष्ठा ams369fg06 *lcd)
अणु
	पूर्णांक ret = 0;
	काष्ठा lcd_platक्रमm_data *pd;
	काष्ठा backlight_device *bd;

	pd = lcd->lcd_pd;
	bd = lcd->bd;

	अगर (pd->घातer_on) अणु
		pd->घातer_on(lcd->ld, 1);
		msleep(pd->घातer_on_delay);
	पूर्ण

	अगर (!pd->reset) अणु
		dev_err(lcd->dev, "reset is NULL.\n");
		वापस -EINVAL;
	पूर्ण

	pd->reset(lcd->ld);
	msleep(pd->reset_delay);

	ret = ams369fg06_ldi_init(lcd);
	अगर (ret) अणु
		dev_err(lcd->dev, "failed to initialize ldi.\n");
		वापस ret;
	पूर्ण

	ret = ams369fg06_ldi_enable(lcd);
	अगर (ret) अणु
		dev_err(lcd->dev, "failed to enable ldi.\n");
		वापस ret;
	पूर्ण

	/* set brightness to current value after घातer on or resume. */
	ret = ams369fg06_gamma_ctl(lcd, bd->props.brightness);
	अगर (ret) अणु
		dev_err(lcd->dev, "lcd gamma setting failed.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ams369fg06_घातer_off(काष्ठा ams369fg06 *lcd)
अणु
	पूर्णांक ret;
	काष्ठा lcd_platक्रमm_data *pd;

	pd = lcd->lcd_pd;

	ret = ams369fg06_ldi_disable(lcd);
	अगर (ret) अणु
		dev_err(lcd->dev, "lcd setting failed.\n");
		वापस -EIO;
	पूर्ण

	msleep(pd->घातer_off_delay);

	अगर (pd->घातer_on)
		pd->घातer_on(lcd->ld, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ams369fg06_घातer(काष्ठा ams369fg06 *lcd, पूर्णांक घातer)
अणु
	पूर्णांक ret = 0;

	अगर (ams369fg06_घातer_is_on(घातer) &&
		!ams369fg06_घातer_is_on(lcd->घातer))
		ret = ams369fg06_घातer_on(lcd);
	अन्यथा अगर (!ams369fg06_घातer_is_on(घातer) &&
		ams369fg06_घातer_is_on(lcd->घातer))
		ret = ams369fg06_घातer_off(lcd);

	अगर (!ret)
		lcd->घातer = घातer;

	वापस ret;
पूर्ण

अटल पूर्णांक ams369fg06_get_घातer(काष्ठा lcd_device *ld)
अणु
	काष्ठा ams369fg06 *lcd = lcd_get_data(ld);

	वापस lcd->घातer;
पूर्ण

अटल पूर्णांक ams369fg06_set_घातer(काष्ठा lcd_device *ld, पूर्णांक घातer)
अणु
	काष्ठा ams369fg06 *lcd = lcd_get_data(ld);

	अगर (घातer != FB_BLANK_UNBLANK && घातer != FB_BLANK_POWERDOWN &&
		घातer != FB_BLANK_NORMAL) अणु
		dev_err(lcd->dev, "power value should be 0, 1 or 4.\n");
		वापस -EINVAL;
	पूर्ण

	वापस ams369fg06_घातer(lcd, घातer);
पूर्ण

अटल पूर्णांक ams369fg06_set_brightness(काष्ठा backlight_device *bd)
अणु
	पूर्णांक ret = 0;
	पूर्णांक brightness = bd->props.brightness;
	काष्ठा ams369fg06 *lcd = bl_get_data(bd);

	अगर (brightness < MIN_BRIGHTNESS ||
		brightness > bd->props.max_brightness) अणु
		dev_err(&bd->dev, "lcd brightness should be %d to %d.\n",
			MIN_BRIGHTNESS, MAX_BRIGHTNESS);
		वापस -EINVAL;
	पूर्ण

	ret = ams369fg06_gamma_ctl(lcd, bd->props.brightness);
	अगर (ret) अणु
		dev_err(&bd->dev, "lcd brightness setting failed.\n");
		वापस -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा lcd_ops ams369fg06_lcd_ops = अणु
	.get_घातer = ams369fg06_get_घातer,
	.set_घातer = ams369fg06_set_घातer,
पूर्ण;

अटल स्थिर काष्ठा backlight_ops ams369fg06_backlight_ops = अणु
	.update_status = ams369fg06_set_brightness,
पूर्ण;

अटल पूर्णांक ams369fg06_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret = 0;
	काष्ठा ams369fg06 *lcd = शून्य;
	काष्ठा lcd_device *ld = शून्य;
	काष्ठा backlight_device *bd = शून्य;
	काष्ठा backlight_properties props;

	lcd = devm_kzalloc(&spi->dev, माप(काष्ठा ams369fg06), GFP_KERNEL);
	अगर (!lcd)
		वापस -ENOMEM;

	/* ams369fg06 lcd panel uses 3-wire 16bits SPI Mode. */
	spi->bits_per_word = 16;

	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "spi setup failed.\n");
		वापस ret;
	पूर्ण

	lcd->spi = spi;
	lcd->dev = &spi->dev;

	lcd->lcd_pd = dev_get_platdata(&spi->dev);
	अगर (!lcd->lcd_pd) अणु
		dev_err(&spi->dev, "platform data is NULL\n");
		वापस -EINVAL;
	पूर्ण

	ld = devm_lcd_device_रेजिस्टर(&spi->dev, "ams369fg06", &spi->dev, lcd,
					&ams369fg06_lcd_ops);
	अगर (IS_ERR(ld))
		वापस PTR_ERR(ld);

	lcd->ld = ld;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = MAX_BRIGHTNESS;

	bd = devm_backlight_device_रेजिस्टर(&spi->dev, "ams369fg06-bl",
					&spi->dev, lcd,
					&ams369fg06_backlight_ops, &props);
	अगर (IS_ERR(bd))
		वापस PTR_ERR(bd);

	bd->props.brightness = DEFAULT_BRIGHTNESS;
	lcd->bd = bd;

	अगर (!lcd->lcd_pd->lcd_enabled) अणु
		/*
		 * अगर lcd panel was off from bootloader then
		 * current lcd status is घातerकरोwn and then
		 * it enables lcd panel.
		 */
		lcd->घातer = FB_BLANK_POWERDOWN;

		ams369fg06_घातer(lcd, FB_BLANK_UNBLANK);
	पूर्ण अन्यथा अणु
		lcd->घातer = FB_BLANK_UNBLANK;
	पूर्ण

	spi_set_drvdata(spi, lcd);

	dev_info(&spi->dev, "ams369fg06 panel driver has been probed.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ams369fg06_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा ams369fg06 *lcd = spi_get_drvdata(spi);

	ams369fg06_घातer(lcd, FB_BLANK_POWERDOWN);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ams369fg06_suspend(काष्ठा device *dev)
अणु
	काष्ठा ams369fg06 *lcd = dev_get_drvdata(dev);

	dev_dbg(dev, "lcd->power = %d\n", lcd->घातer);

	/*
	 * when lcd panel is suspend, lcd panel becomes off
	 * regardless of status.
	 */
	वापस ams369fg06_घातer(lcd, FB_BLANK_POWERDOWN);
पूर्ण

अटल पूर्णांक ams369fg06_resume(काष्ठा device *dev)
अणु
	काष्ठा ams369fg06 *lcd = dev_get_drvdata(dev);

	lcd->घातer = FB_BLANK_POWERDOWN;

	वापस ams369fg06_घातer(lcd, FB_BLANK_UNBLANK);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ams369fg06_pm_ops, ams369fg06_suspend,
			ams369fg06_resume);

अटल व्योम ams369fg06_shutकरोwn(काष्ठा spi_device *spi)
अणु
	काष्ठा ams369fg06 *lcd = spi_get_drvdata(spi);

	ams369fg06_घातer(lcd, FB_BLANK_POWERDOWN);
पूर्ण

अटल काष्ठा spi_driver ams369fg06_driver = अणु
	.driver = अणु
		.name	= "ams369fg06",
		.pm	= &ams369fg06_pm_ops,
	पूर्ण,
	.probe		= ams369fg06_probe,
	.हटाओ		= ams369fg06_हटाओ,
	.shutकरोwn	= ams369fg06_shutकरोwn,
पूर्ण;

module_spi_driver(ams369fg06_driver);

MODULE_AUTHOR("Jingoo Han <jg1.han@samsung.com>");
MODULE_DESCRIPTION("ams369fg06 LCD Driver");
MODULE_LICENSE("GPL");
