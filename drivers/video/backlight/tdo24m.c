<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tकरो24m - SPI-based drivers क्रम Toppoly TDO24M series LCD panels
 *
 * Copyright (C) 2008 Marvell International Ltd.
 *	Eric Miao <eric.miao@marvell.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/tकरो24m.h>
#समावेश <linux/fb.h>
#समावेश <linux/lcd.h>
#समावेश <linux/slab.h>

#घोषणा POWER_IS_ON(pwr)	((pwr) <= FB_BLANK_NORMAL)

#घोषणा TDO24M_SPI_BUFF_SIZE	(4)
#घोषणा MODE_QVGA	0
#घोषणा MODE_VGA	1

काष्ठा tकरो24m अणु
	काष्ठा spi_device	*spi_dev;
	काष्ठा lcd_device	*lcd_dev;

	काष्ठा spi_message	msg;
	काष्ठा spi_transfer	xfer;
	uपूर्णांक8_t			*buf;

	पूर्णांक (*adj_mode)(काष्ठा tकरो24m *lcd, पूर्णांक mode);
	पूर्णांक color_invert;

	पूर्णांक			घातer;
	पूर्णांक			mode;
पूर्ण;

/* use bit 30, 31 as the indicator of command parameter number */
#घोषणा CMD0(x)		((0 << 30) | (x))
#घोषणा CMD1(x, x1)	((1 << 30) | ((x) << 9) | 0x100 | (x1))
#घोषणा CMD2(x, x1, x2)	((2 << 30) | ((x) << 18) | 0x20000 |\
			((x1) << 9) | 0x100 | (x2))
#घोषणा CMD_शून्य	(-1)

अटल स्थिर uपूर्णांक32_t lcd_panel_reset[] = अणु
	CMD0(0x1), /* reset */
	CMD0(0x0), /* nop */
	CMD0(0x0), /* nop */
	CMD0(0x0), /* nop */
	CMD_शून्य,
पूर्ण;

अटल स्थिर uपूर्णांक32_t lcd_panel_on[] = अणु
	CMD0(0x29),		/* Display ON */
	CMD2(0xB8, 0xFF, 0xF9),	/* Output Control */
	CMD0(0x11),		/* Sleep out */
	CMD1(0xB0, 0x16),	/* Wake */
	CMD_शून्य,
पूर्ण;

अटल स्थिर uपूर्णांक32_t lcd_panel_off[] = अणु
	CMD0(0x28),		/* Display OFF */
	CMD2(0xB8, 0x80, 0x02),	/* Output Control */
	CMD0(0x10),		/* Sleep in */
	CMD1(0xB0, 0x00),	/* Deep stand by in */
	CMD_शून्य,
पूर्ण;

अटल स्थिर uपूर्णांक32_t lcd_vga_pass_through_tकरो24m[] = अणु
	CMD1(0xB0, 0x16),
	CMD1(0xBC, 0x80),
	CMD1(0xE1, 0x00),
	CMD1(0x36, 0x50),
	CMD1(0x3B, 0x00),
	CMD_शून्य,
पूर्ण;

अटल स्थिर uपूर्णांक32_t lcd_qvga_pass_through_tकरो24m[] = अणु
	CMD1(0xB0, 0x16),
	CMD1(0xBC, 0x81),
	CMD1(0xE1, 0x00),
	CMD1(0x36, 0x50),
	CMD1(0x3B, 0x22),
	CMD_शून्य,
पूर्ण;

अटल स्थिर uपूर्णांक32_t lcd_vga_transfer_tकरो24m[] = अणु
	CMD1(0xcf, 0x02),	/* Blanking period control (1) */
	CMD2(0xd0, 0x08, 0x04),	/* Blanking period control (2) */
	CMD1(0xd1, 0x01),	/* CKV timing control on/off */
	CMD2(0xd2, 0x14, 0x00),	/* CKV 1,2 timing control */
	CMD2(0xd3, 0x1a, 0x0f),	/* OEV timing control */
	CMD2(0xd4, 0x1f, 0xaf),	/* ASW timing control (1) */
	CMD1(0xd5, 0x14),	/* ASW timing control (2) */
	CMD0(0x21),		/* Invert क्रम normally black display */
	CMD0(0x29),		/* Display on */
	CMD_शून्य,
पूर्ण;

अटल स्थिर uपूर्णांक32_t lcd_qvga_transfer[] = अणु
	CMD1(0xd6, 0x02),	/* Blanking period control (1) */
	CMD2(0xd7, 0x08, 0x04),	/* Blanking period control (2) */
	CMD1(0xd8, 0x01),	/* CKV timing control on/off */
	CMD2(0xd9, 0x00, 0x08),	/* CKV 1,2 timing control */
	CMD2(0xde, 0x05, 0x0a),	/* OEV timing control */
	CMD2(0xdf, 0x0a, 0x19),	/* ASW timing control (1) */
	CMD1(0xe0, 0x0a),	/* ASW timing control (2) */
	CMD0(0x21),		/* Invert क्रम normally black display */
	CMD0(0x29),		/* Display on */
	CMD_शून्य,
पूर्ण;

अटल स्थिर uपूर्णांक32_t lcd_vga_pass_through_tकरो35s[] = अणु
	CMD1(0xB0, 0x16),
	CMD1(0xBC, 0x80),
	CMD1(0xE1, 0x00),
	CMD1(0x3B, 0x00),
	CMD_शून्य,
पूर्ण;

अटल स्थिर uपूर्णांक32_t lcd_qvga_pass_through_tकरो35s[] = अणु
	CMD1(0xB0, 0x16),
	CMD1(0xBC, 0x81),
	CMD1(0xE1, 0x00),
	CMD1(0x3B, 0x22),
	CMD_शून्य,
पूर्ण;

अटल स्थिर uपूर्णांक32_t lcd_vga_transfer_tकरो35s[] = अणु
	CMD1(0xcf, 0x02),	/* Blanking period control (1) */
	CMD2(0xd0, 0x08, 0x04),	/* Blanking period control (2) */
	CMD1(0xd1, 0x01),	/* CKV timing control on/off */
	CMD2(0xd2, 0x00, 0x1e),	/* CKV 1,2 timing control */
	CMD2(0xd3, 0x14, 0x28),	/* OEV timing control */
	CMD2(0xd4, 0x28, 0x64),	/* ASW timing control (1) */
	CMD1(0xd5, 0x28),	/* ASW timing control (2) */
	CMD0(0x21),		/* Invert क्रम normally black display */
	CMD0(0x29),		/* Display on */
	CMD_शून्य,
पूर्ण;

अटल स्थिर uपूर्णांक32_t lcd_panel_config[] = अणु
	CMD2(0xb8, 0xff, 0xf9),	/* Output control */
	CMD0(0x11),		/* sleep out */
	CMD1(0xba, 0x01),	/* Display mode (1) */
	CMD1(0xbb, 0x00),	/* Display mode (2) */
	CMD1(0x3a, 0x60),	/* Display mode 18-bit RGB */
	CMD1(0xbf, 0x10),	/* Drive प्रणाली change control */
	CMD1(0xb1, 0x56),	/* Booster operation setup */
	CMD1(0xb2, 0x33),	/* Booster mode setup */
	CMD1(0xb3, 0x11),	/* Booster frequency setup */
	CMD1(0xb4, 0x02),	/* Op amp/प्रणाली घड़ी */
	CMD1(0xb5, 0x35),	/* VCS voltage */
	CMD1(0xb6, 0x40),	/* VCOM voltage */
	CMD1(0xb7, 0x03),	/* External display संकेत */
	CMD1(0xbd, 0x00),	/* ASW slew rate */
	CMD1(0xbe, 0x00),	/* Dummy data क्रम QuadData operation */
	CMD1(0xc0, 0x11),	/* Sleep out FR count (A) */
	CMD1(0xc1, 0x11),	/* Sleep out FR count (B) */
	CMD1(0xc2, 0x11),	/* Sleep out FR count (C) */
	CMD2(0xc3, 0x20, 0x40),	/* Sleep out FR count (D) */
	CMD2(0xc4, 0x60, 0xc0),	/* Sleep out FR count (E) */
	CMD2(0xc5, 0x10, 0x20),	/* Sleep out FR count (F) */
	CMD1(0xc6, 0xc0),	/* Sleep out FR count (G) */
	CMD2(0xc7, 0x33, 0x43),	/* Gamma 1 fine tuning (1) */
	CMD1(0xc8, 0x44),	/* Gamma 1 fine tuning (2) */
	CMD1(0xc9, 0x33),	/* Gamma 1 inclination adjusपंचांगent */
	CMD1(0xca, 0x00),	/* Gamma 1 blue offset adjusपंचांगent */
	CMD2(0xec, 0x01, 0xf0),	/* Horizontal घड़ी cycles */
	CMD_शून्य,
पूर्ण;

अटल पूर्णांक tकरो24m_ग_लिखोs(काष्ठा tकरो24m *lcd, स्थिर uपूर्णांक32_t *array)
अणु
	काष्ठा spi_transfer *x = &lcd->xfer;
	स्थिर uपूर्णांक32_t *p = array;
	uपूर्णांक32_t data;
	पूर्णांक nparams, err = 0;

	क्रम (; *p != CMD_शून्य; p++) अणु
		अगर (!lcd->color_invert && *p == CMD0(0x21))
			जारी;

		nparams = (*p >> 30) & 0x3;

		data = *p << (7 - nparams);
		चयन (nparams) अणु
		हाल 0:
			lcd->buf[0] = (data >> 8) & 0xff;
			lcd->buf[1] = data & 0xff;
			अवरोध;
		हाल 1:
			lcd->buf[0] = (data >> 16) & 0xff;
			lcd->buf[1] = (data >> 8) & 0xff;
			lcd->buf[2] = data & 0xff;
			अवरोध;
		हाल 2:
			lcd->buf[0] = (data >> 24) & 0xff;
			lcd->buf[1] = (data >> 16) & 0xff;
			lcd->buf[2] = (data >> 8) & 0xff;
			lcd->buf[3] = data & 0xff;
			अवरोध;
		शेष:
			जारी;
		पूर्ण
		x->len = nparams + 2;
		err = spi_sync(lcd->spi_dev, &lcd->msg);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक tकरो24m_adj_mode(काष्ठा tकरो24m *lcd, पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल MODE_VGA:
		tकरो24m_ग_लिखोs(lcd, lcd_vga_pass_through_tकरो24m);
		tकरो24m_ग_लिखोs(lcd, lcd_panel_config);
		tकरो24m_ग_लिखोs(lcd, lcd_vga_transfer_tकरो24m);
		अवरोध;
	हाल MODE_QVGA:
		tकरो24m_ग_लिखोs(lcd, lcd_qvga_pass_through_tकरो24m);
		tकरो24m_ग_लिखोs(lcd, lcd_panel_config);
		tकरो24m_ग_लिखोs(lcd, lcd_qvga_transfer);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	lcd->mode = mode;
	वापस 0;
पूर्ण

अटल पूर्णांक tकरो35s_adj_mode(काष्ठा tकरो24m *lcd, पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल MODE_VGA:
		tकरो24m_ग_लिखोs(lcd, lcd_vga_pass_through_tकरो35s);
		tकरो24m_ग_लिखोs(lcd, lcd_panel_config);
		tकरो24m_ग_लिखोs(lcd, lcd_vga_transfer_tकरो35s);
		अवरोध;
	हाल MODE_QVGA:
		tकरो24m_ग_लिखोs(lcd, lcd_qvga_pass_through_tकरो35s);
		tकरो24m_ग_लिखोs(lcd, lcd_panel_config);
		tकरो24m_ग_लिखोs(lcd, lcd_qvga_transfer);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	lcd->mode = mode;
	वापस 0;
पूर्ण

अटल पूर्णांक tकरो24m_घातer_on(काष्ठा tकरो24m *lcd)
अणु
	पूर्णांक err;

	err = tकरो24m_ग_लिखोs(lcd, lcd_panel_on);
	अगर (err)
		जाओ out;

	err = tकरो24m_ग_लिखोs(lcd, lcd_panel_reset);
	अगर (err)
		जाओ out;

	err = lcd->adj_mode(lcd, lcd->mode);
out:
	वापस err;
पूर्ण

अटल पूर्णांक tकरो24m_घातer_off(काष्ठा tकरो24m *lcd)
अणु
	वापस tकरो24m_ग_लिखोs(lcd, lcd_panel_off);
पूर्ण

अटल पूर्णांक tकरो24m_घातer(काष्ठा tकरो24m *lcd, पूर्णांक घातer)
अणु
	पूर्णांक ret = 0;

	अगर (POWER_IS_ON(घातer) && !POWER_IS_ON(lcd->घातer))
		ret = tकरो24m_घातer_on(lcd);
	अन्यथा अगर (!POWER_IS_ON(घातer) && POWER_IS_ON(lcd->घातer))
		ret = tकरो24m_घातer_off(lcd);

	अगर (!ret)
		lcd->घातer = घातer;

	वापस ret;
पूर्ण


अटल पूर्णांक tकरो24m_set_घातer(काष्ठा lcd_device *ld, पूर्णांक घातer)
अणु
	काष्ठा tकरो24m *lcd = lcd_get_data(ld);

	वापस tकरो24m_घातer(lcd, घातer);
पूर्ण

अटल पूर्णांक tकरो24m_get_घातer(काष्ठा lcd_device *ld)
अणु
	काष्ठा tकरो24m *lcd = lcd_get_data(ld);

	वापस lcd->घातer;
पूर्ण

अटल पूर्णांक tकरो24m_set_mode(काष्ठा lcd_device *ld, काष्ठा fb_videomode *m)
अणु
	काष्ठा tकरो24m *lcd = lcd_get_data(ld);
	पूर्णांक mode = MODE_QVGA;

	अगर (m->xres == 640 || m->xres == 480)
		mode = MODE_VGA;

	अगर (lcd->mode == mode)
		वापस 0;

	वापस lcd->adj_mode(lcd, mode);
पूर्ण

अटल काष्ठा lcd_ops tकरो24m_ops = अणु
	.get_घातer	= tकरो24m_get_घातer,
	.set_घातer	= tकरो24m_set_घातer,
	.set_mode	= tकरो24m_set_mode,
पूर्ण;

अटल पूर्णांक tकरो24m_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा tकरो24m *lcd;
	काष्ठा spi_message *m;
	काष्ठा spi_transfer *x;
	काष्ठा tकरो24m_platक्रमm_data *pdata;
	क्रमागत tकरो24m_model model;
	पूर्णांक err;

	pdata = dev_get_platdata(&spi->dev);
	अगर (pdata)
		model = pdata->model;
	अन्यथा
		model = TDO24M;

	spi->bits_per_word = 8;
	spi->mode = SPI_MODE_3;
	err = spi_setup(spi);
	अगर (err)
		वापस err;

	lcd = devm_kzalloc(&spi->dev, माप(काष्ठा tकरो24m), GFP_KERNEL);
	अगर (!lcd)
		वापस -ENOMEM;

	lcd->spi_dev = spi;
	lcd->घातer = FB_BLANK_POWERDOWN;
	lcd->mode = MODE_VGA;	/* शेष to VGA */

	lcd->buf = devm_kzalloc(&spi->dev, TDO24M_SPI_BUFF_SIZE, GFP_KERNEL);
	अगर (lcd->buf == शून्य)
		वापस -ENOMEM;

	m = &lcd->msg;
	x = &lcd->xfer;

	spi_message_init(m);

	x->cs_change = 0;
	x->tx_buf = &lcd->buf[0];
	spi_message_add_tail(x, m);

	चयन (model) अणु
	हाल TDO24M:
		lcd->color_invert = 1;
		lcd->adj_mode = tकरो24m_adj_mode;
		अवरोध;
	हाल TDO35S:
		lcd->adj_mode = tकरो35s_adj_mode;
		lcd->color_invert = 0;
		अवरोध;
	शेष:
		dev_err(&spi->dev, "Unsupported model");
		वापस -EINVAL;
	पूर्ण

	lcd->lcd_dev = devm_lcd_device_रेजिस्टर(&spi->dev, "tdo24m", &spi->dev,
						lcd, &tकरो24m_ops);
	अगर (IS_ERR(lcd->lcd_dev))
		वापस PTR_ERR(lcd->lcd_dev);

	spi_set_drvdata(spi, lcd);
	err = tकरो24m_घातer(lcd, FB_BLANK_UNBLANK);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक tकरो24m_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा tकरो24m *lcd = spi_get_drvdata(spi);

	tकरो24m_घातer(lcd, FB_BLANK_POWERDOWN);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tकरो24m_suspend(काष्ठा device *dev)
अणु
	काष्ठा tकरो24m *lcd = dev_get_drvdata(dev);

	वापस tकरो24m_घातer(lcd, FB_BLANK_POWERDOWN);
पूर्ण

अटल पूर्णांक tकरो24m_resume(काष्ठा device *dev)
अणु
	काष्ठा tकरो24m *lcd = dev_get_drvdata(dev);

	वापस tकरो24m_घातer(lcd, FB_BLANK_UNBLANK);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tकरो24m_pm_ops, tकरो24m_suspend, tकरो24m_resume);

/* Power करोwn all displays on reboot, घातeroff or halt */
अटल व्योम tकरो24m_shutकरोwn(काष्ठा spi_device *spi)
अणु
	काष्ठा tकरो24m *lcd = spi_get_drvdata(spi);

	tकरो24m_घातer(lcd, FB_BLANK_POWERDOWN);
पूर्ण

अटल काष्ठा spi_driver tकरो24m_driver = अणु
	.driver = अणु
		.name		= "tdo24m",
		.pm		= &tकरो24m_pm_ops,
	पूर्ण,
	.probe		= tकरो24m_probe,
	.हटाओ		= tकरो24m_हटाओ,
	.shutकरोwn	= tकरो24m_shutकरोwn,
पूर्ण;

module_spi_driver(tकरो24m_driver);

MODULE_AUTHOR("Eric Miao <eric.miao@marvell.com>");
MODULE_DESCRIPTION("Driver for Toppoly TDO24M LCD Panel");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:tdo24m");
