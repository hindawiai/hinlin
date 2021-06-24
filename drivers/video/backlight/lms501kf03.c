<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lms501kf03 TFT LCD panel driver.
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 * Author: Jingoo Han  <jg1.han@samsung.com>
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/lcd.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/रुको.h>

#घोषणा COMMAND_ONLY		0x00
#घोषणा DATA_ONLY		0x01

काष्ठा lms501kf03 अणु
	काष्ठा device			*dev;
	काष्ठा spi_device		*spi;
	अचिन्हित पूर्णांक			घातer;
	काष्ठा lcd_device		*ld;
	काष्ठा lcd_platक्रमm_data	*lcd_pd;
पूर्ण;

अटल स्थिर अचिन्हित अक्षर seq_password[] = अणु
	0xb9, 0xff, 0x83, 0x69,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर seq_घातer[] = अणु
	0xb1, 0x01, 0x00, 0x34, 0x06, 0x00, 0x14, 0x14, 0x20, 0x28,
	0x12, 0x12, 0x17, 0x0a, 0x01, 0xe6, 0xe6, 0xe6, 0xe6, 0xe6,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर seq_display[] = अणु
	0xb2, 0x00, 0x2b, 0x03, 0x03, 0x70, 0x00, 0xff, 0x00, 0x00,
	0x00, 0x00, 0x03, 0x03, 0x00, 0x01,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर seq_rgb_अगर[] = अणु
	0xb3, 0x09,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर seq_display_inv[] = अणु
	0xb4, 0x01, 0x08, 0x77, 0x0e, 0x06,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर seq_vcom[] = अणु
	0xb6, 0x4c, 0x2e,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर seq_gate[] = अणु
	0xd5, 0x00, 0x05, 0x03, 0x29, 0x01, 0x07, 0x17, 0x68, 0x13,
	0x37, 0x20, 0x31, 0x8a, 0x46, 0x9b, 0x57, 0x13, 0x02, 0x75,
	0xb9, 0x64, 0xa8, 0x07, 0x0f, 0x04, 0x07,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर seq_panel[] = अणु
	0xcc, 0x02,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर seq_col_mod[] = अणु
	0x3a, 0x77,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर seq_w_gamma[] = अणु
	0xe0, 0x00, 0x04, 0x09, 0x0f, 0x1f, 0x3f, 0x1f, 0x2f, 0x0a,
	0x0f, 0x10, 0x16, 0x18, 0x16, 0x17, 0x0d, 0x15, 0x00, 0x04,
	0x09, 0x0f, 0x38, 0x3f, 0x20, 0x39, 0x0a, 0x0f, 0x10, 0x16,
	0x18, 0x16, 0x17, 0x0d, 0x15,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर seq_rgb_gamma[] = अणु
	0xc1, 0x01, 0x03, 0x07, 0x0f, 0x1a, 0x22, 0x2c, 0x33, 0x3c,
	0x46, 0x4f, 0x58, 0x60, 0x69, 0x71, 0x79, 0x82, 0x89, 0x92,
	0x9a, 0xa1, 0xa9, 0xb1, 0xb9, 0xc1, 0xc9, 0xcf, 0xd6, 0xde,
	0xe5, 0xec, 0xf3, 0xf9, 0xff, 0xdd, 0x39, 0x07, 0x1c, 0xcb,
	0xab, 0x5f, 0x49, 0x80, 0x03, 0x07, 0x0f, 0x19, 0x20, 0x2a,
	0x31, 0x39, 0x42, 0x4b, 0x53, 0x5b, 0x63, 0x6b, 0x73, 0x7b,
	0x83, 0x8a, 0x92, 0x9b, 0xa2, 0xaa, 0xb2, 0xba, 0xc2, 0xca,
	0xd0, 0xd8, 0xe1, 0xe8, 0xf0, 0xf8, 0xff, 0xf7, 0xd8, 0xbe,
	0xa7, 0x39, 0x40, 0x85, 0x8c, 0xc0, 0x04, 0x07, 0x0c, 0x17,
	0x1c, 0x23, 0x2b, 0x34, 0x3b, 0x43, 0x4c, 0x54, 0x5b, 0x63,
	0x6a, 0x73, 0x7a, 0x82, 0x8a, 0x91, 0x98, 0xa1, 0xa8, 0xb0,
	0xb7, 0xc1, 0xc9, 0xcf, 0xd9, 0xe3, 0xea, 0xf4, 0xff, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर seq_sleep_out[] = अणु
	0x11,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर seq_display_on[] = अणु
	0x29,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर seq_display_off[] = अणु
	0x10,
पूर्ण;

अटल पूर्णांक lms501kf03_spi_ग_लिखो_byte(काष्ठा lms501kf03 *lcd, पूर्णांक addr, पूर्णांक data)
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

अटल पूर्णांक lms501kf03_spi_ग_लिखो(काष्ठा lms501kf03 *lcd, अचिन्हित अक्षर address,
				अचिन्हित अक्षर command)
अणु
	वापस lms501kf03_spi_ग_लिखो_byte(lcd, address, command);
पूर्ण

अटल पूर्णांक lms501kf03_panel_send_sequence(काष्ठा lms501kf03 *lcd,
					स्थिर अचिन्हित अक्षर *wbuf,
					अचिन्हित पूर्णांक len)
अणु
	पूर्णांक ret = 0, i = 0;

	जबतक (i < len) अणु
		अगर (i == 0)
			ret = lms501kf03_spi_ग_लिखो(lcd, COMMAND_ONLY, wbuf[i]);
		अन्यथा
			ret = lms501kf03_spi_ग_लिखो(lcd, DATA_ONLY, wbuf[i]);
		अगर (ret)
			अवरोध;
		i += 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक lms501kf03_ldi_init(काष्ठा lms501kf03 *lcd)
अणु
	पूर्णांक ret, i;
	अटल स्थिर अचिन्हित अक्षर *init_seq[] = अणु
		seq_password,
		seq_घातer,
		seq_display,
		seq_rgb_अगर,
		seq_display_inv,
		seq_vcom,
		seq_gate,
		seq_panel,
		seq_col_mod,
		seq_w_gamma,
		seq_rgb_gamma,
		seq_sleep_out,
	पूर्ण;

	अटल स्थिर अचिन्हित पूर्णांक size_seq[] = अणु
		ARRAY_SIZE(seq_password),
		ARRAY_SIZE(seq_घातer),
		ARRAY_SIZE(seq_display),
		ARRAY_SIZE(seq_rgb_अगर),
		ARRAY_SIZE(seq_display_inv),
		ARRAY_SIZE(seq_vcom),
		ARRAY_SIZE(seq_gate),
		ARRAY_SIZE(seq_panel),
		ARRAY_SIZE(seq_col_mod),
		ARRAY_SIZE(seq_w_gamma),
		ARRAY_SIZE(seq_rgb_gamma),
		ARRAY_SIZE(seq_sleep_out),
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(init_seq); i++) अणु
		ret = lms501kf03_panel_send_sequence(lcd, init_seq[i],
						size_seq[i]);
		अगर (ret)
			अवरोध;
	पूर्ण
	/*
	 * According to the datasheet, 120ms delay समय is required.
	 * After sleep out sequence, command is blocked क्रम 120ms.
	 * Thus, LDI should रुको क्रम 120ms.
	 */
	msleep(120);

	वापस ret;
पूर्ण

अटल पूर्णांक lms501kf03_ldi_enable(काष्ठा lms501kf03 *lcd)
अणु
	वापस lms501kf03_panel_send_sequence(lcd, seq_display_on,
					ARRAY_SIZE(seq_display_on));
पूर्ण

अटल पूर्णांक lms501kf03_ldi_disable(काष्ठा lms501kf03 *lcd)
अणु
	वापस lms501kf03_panel_send_sequence(lcd, seq_display_off,
					ARRAY_SIZE(seq_display_off));
पूर्ण

अटल पूर्णांक lms501kf03_घातer_is_on(पूर्णांक घातer)
अणु
	वापस (घातer) <= FB_BLANK_NORMAL;
पूर्ण

अटल पूर्णांक lms501kf03_घातer_on(काष्ठा lms501kf03 *lcd)
अणु
	पूर्णांक ret = 0;
	काष्ठा lcd_platक्रमm_data *pd;

	pd = lcd->lcd_pd;

	अगर (!pd->घातer_on) अणु
		dev_err(lcd->dev, "power_on is NULL.\n");
		वापस -EINVAL;
	पूर्ण

	pd->घातer_on(lcd->ld, 1);
	msleep(pd->घातer_on_delay);

	अगर (!pd->reset) अणु
		dev_err(lcd->dev, "reset is NULL.\n");
		वापस -EINVAL;
	पूर्ण

	pd->reset(lcd->ld);
	msleep(pd->reset_delay);

	ret = lms501kf03_ldi_init(lcd);
	अगर (ret) अणु
		dev_err(lcd->dev, "failed to initialize ldi.\n");
		वापस ret;
	पूर्ण

	ret = lms501kf03_ldi_enable(lcd);
	अगर (ret) अणु
		dev_err(lcd->dev, "failed to enable ldi.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lms501kf03_घातer_off(काष्ठा lms501kf03 *lcd)
अणु
	पूर्णांक ret = 0;
	काष्ठा lcd_platक्रमm_data *pd;

	pd = lcd->lcd_pd;

	ret = lms501kf03_ldi_disable(lcd);
	अगर (ret) अणु
		dev_err(lcd->dev, "lcd setting failed.\n");
		वापस -EIO;
	पूर्ण

	msleep(pd->घातer_off_delay);

	pd->घातer_on(lcd->ld, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक lms501kf03_घातer(काष्ठा lms501kf03 *lcd, पूर्णांक घातer)
अणु
	पूर्णांक ret = 0;

	अगर (lms501kf03_घातer_is_on(घातer) &&
		!lms501kf03_घातer_is_on(lcd->घातer))
		ret = lms501kf03_घातer_on(lcd);
	अन्यथा अगर (!lms501kf03_घातer_is_on(घातer) &&
		lms501kf03_घातer_is_on(lcd->घातer))
		ret = lms501kf03_घातer_off(lcd);

	अगर (!ret)
		lcd->घातer = घातer;

	वापस ret;
पूर्ण

अटल पूर्णांक lms501kf03_get_घातer(काष्ठा lcd_device *ld)
अणु
	काष्ठा lms501kf03 *lcd = lcd_get_data(ld);

	वापस lcd->घातer;
पूर्ण

अटल पूर्णांक lms501kf03_set_घातer(काष्ठा lcd_device *ld, पूर्णांक घातer)
अणु
	काष्ठा lms501kf03 *lcd = lcd_get_data(ld);

	अगर (घातer != FB_BLANK_UNBLANK && घातer != FB_BLANK_POWERDOWN &&
		घातer != FB_BLANK_NORMAL) अणु
		dev_err(lcd->dev, "power value should be 0, 1 or 4.\n");
		वापस -EINVAL;
	पूर्ण

	वापस lms501kf03_घातer(lcd, घातer);
पूर्ण

अटल काष्ठा lcd_ops lms501kf03_lcd_ops = अणु
	.get_घातer = lms501kf03_get_घातer,
	.set_घातer = lms501kf03_set_घातer,
पूर्ण;

अटल पूर्णांक lms501kf03_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा lms501kf03 *lcd = शून्य;
	काष्ठा lcd_device *ld = शून्य;
	पूर्णांक ret = 0;

	lcd = devm_kzalloc(&spi->dev, माप(काष्ठा lms501kf03), GFP_KERNEL);
	अगर (!lcd)
		वापस -ENOMEM;

	/* lms501kf03 lcd panel uses 3-wire 9-bit SPI Mode. */
	spi->bits_per_word = 9;

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

	ld = devm_lcd_device_रेजिस्टर(&spi->dev, "lms501kf03", &spi->dev, lcd,
					&lms501kf03_lcd_ops);
	अगर (IS_ERR(ld))
		वापस PTR_ERR(ld);

	lcd->ld = ld;

	अगर (!lcd->lcd_pd->lcd_enabled) अणु
		/*
		 * अगर lcd panel was off from bootloader then
		 * current lcd status is घातerकरोwn and then
		 * it enables lcd panel.
		 */
		lcd->घातer = FB_BLANK_POWERDOWN;

		lms501kf03_घातer(lcd, FB_BLANK_UNBLANK);
	पूर्ण अन्यथा अणु
		lcd->घातer = FB_BLANK_UNBLANK;
	पूर्ण

	spi_set_drvdata(spi, lcd);

	dev_info(&spi->dev, "lms501kf03 panel driver has been probed.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक lms501kf03_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा lms501kf03 *lcd = spi_get_drvdata(spi);

	lms501kf03_घातer(lcd, FB_BLANK_POWERDOWN);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक lms501kf03_suspend(काष्ठा device *dev)
अणु
	काष्ठा lms501kf03 *lcd = dev_get_drvdata(dev);

	dev_dbg(dev, "lcd->power = %d\n", lcd->घातer);

	/*
	 * when lcd panel is suspend, lcd panel becomes off
	 * regardless of status.
	 */
	वापस lms501kf03_घातer(lcd, FB_BLANK_POWERDOWN);
पूर्ण

अटल पूर्णांक lms501kf03_resume(काष्ठा device *dev)
अणु
	काष्ठा lms501kf03 *lcd = dev_get_drvdata(dev);

	lcd->घातer = FB_BLANK_POWERDOWN;

	वापस lms501kf03_घातer(lcd, FB_BLANK_UNBLANK);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(lms501kf03_pm_ops, lms501kf03_suspend,
			lms501kf03_resume);

अटल व्योम lms501kf03_shutकरोwn(काष्ठा spi_device *spi)
अणु
	काष्ठा lms501kf03 *lcd = spi_get_drvdata(spi);

	lms501kf03_घातer(lcd, FB_BLANK_POWERDOWN);
पूर्ण

अटल काष्ठा spi_driver lms501kf03_driver = अणु
	.driver = अणु
		.name	= "lms501kf03",
		.pm	= &lms501kf03_pm_ops,
	पूर्ण,
	.probe		= lms501kf03_probe,
	.हटाओ		= lms501kf03_हटाओ,
	.shutकरोwn	= lms501kf03_shutकरोwn,
पूर्ण;

module_spi_driver(lms501kf03_driver);

MODULE_AUTHOR("Jingoo Han <jg1.han@samsung.com>");
MODULE_DESCRIPTION("lms501kf03 LCD Driver");
MODULE_LICENSE("GPL");
