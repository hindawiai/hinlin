<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * lms283gf05.c -- support क्रम Samsung LMS283GF05 LCD
 *
 * Copyright (c) 2009 Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/lcd.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>

काष्ठा lms283gf05_state अणु
	काष्ठा spi_device	*spi;
	काष्ठा lcd_device	*ld;
	काष्ठा gpio_desc	*reset;
पूर्ण;

काष्ठा lms283gf05_seq अणु
	अचिन्हित अक्षर		reg;
	अचिन्हित लघु		value;
	अचिन्हित अक्षर		delay;
पूर्ण;

/* Magic sequences supplied by manufacturer, क्रम details refer to datasheet */
अटल स्थिर काष्ठा lms283gf05_seq disp_initseq[] = अणु
	/* REG, VALUE, DELAY */
	अणु 0x07, 0x0000, 0 पूर्ण,
	अणु 0x13, 0x0000, 10 पूर्ण,

	अणु 0x11, 0x3004, 0 पूर्ण,
	अणु 0x14, 0x200F, 0 पूर्ण,
	अणु 0x10, 0x1a20, 0 पूर्ण,
	अणु 0x13, 0x0040, 50 पूर्ण,

	अणु 0x13, 0x0060, 0 पूर्ण,
	अणु 0x13, 0x0070, 200 पूर्ण,

	अणु 0x01, 0x0127, 0 पूर्ण,
	अणु 0x02,	0x0700, 0 पूर्ण,
	अणु 0x03, 0x1030, 0 पूर्ण,
	अणु 0x08, 0x0208, 0 पूर्ण,
	अणु 0x0B, 0x0620, 0 पूर्ण,
	अणु 0x0C, 0x0110, 0 पूर्ण,
	अणु 0x30, 0x0120, 0 पूर्ण,
	अणु 0x31, 0x0127, 0 पूर्ण,
	अणु 0x32, 0x0000, 0 पूर्ण,
	अणु 0x33, 0x0503, 0 पूर्ण,
	अणु 0x34, 0x0727, 0 पूर्ण,
	अणु 0x35, 0x0124, 0 पूर्ण,
	अणु 0x36, 0x0706, 0 पूर्ण,
	अणु 0x37, 0x0701, 0 पूर्ण,
	अणु 0x38, 0x0F00, 0 पूर्ण,
	अणु 0x39, 0x0F00, 0 पूर्ण,
	अणु 0x40, 0x0000, 0 पूर्ण,
	अणु 0x41, 0x0000, 0 पूर्ण,
	अणु 0x42, 0x013f, 0 पूर्ण,
	अणु 0x43, 0x0000, 0 पूर्ण,
	अणु 0x44, 0x013f, 0 पूर्ण,
	अणु 0x45, 0x0000, 0 पूर्ण,
	अणु 0x46, 0xef00, 0 पूर्ण,
	अणु 0x47, 0x013f, 0 पूर्ण,
	अणु 0x48, 0x0000, 0 पूर्ण,
	अणु 0x07, 0x0015, 30 पूर्ण,

	अणु 0x07, 0x0017, 0 पूर्ण,

	अणु 0x20, 0x0000, 0 पूर्ण,
	अणु 0x21, 0x0000, 0 पूर्ण,
	अणु 0x22, 0x0000, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा lms283gf05_seq disp_pdwnseq[] = अणु
	अणु 0x07, 0x0016, 30 पूर्ण,

	अणु 0x07, 0x0004, 0 पूर्ण,
	अणु 0x10, 0x0220, 20 पूर्ण,

	अणु 0x13, 0x0060, 50 पूर्ण,

	अणु 0x13, 0x0040, 50 पूर्ण,

	अणु 0x13, 0x0000, 0 पूर्ण,
	अणु 0x10, 0x0000, 0 पूर्ण
पूर्ण;


अटल व्योम lms283gf05_reset(काष्ठा gpio_desc *gpiod)
अणु
	gpiod_set_value(gpiod, 0); /* De-निश्चितed */
	mdelay(100);
	gpiod_set_value(gpiod, 1); /* Asserted */
	mdelay(20);
	gpiod_set_value(gpiod, 0); /* De-निश्चितed */
	mdelay(20);
पूर्ण

अटल व्योम lms283gf05_toggle(काष्ठा spi_device *spi,
				स्थिर काष्ठा lms283gf05_seq *seq, पूर्णांक sz)
अणु
	अक्षर buf[3];
	पूर्णांक i;

	क्रम (i = 0; i < sz; i++) अणु
		buf[0] = 0x74;
		buf[1] = 0x00;
		buf[2] = seq[i].reg;
		spi_ग_लिखो(spi, buf, 3);

		buf[0] = 0x76;
		buf[1] = seq[i].value >> 8;
		buf[2] = seq[i].value & 0xff;
		spi_ग_लिखो(spi, buf, 3);

		mdelay(seq[i].delay);
	पूर्ण
पूर्ण

अटल पूर्णांक lms283gf05_घातer_set(काष्ठा lcd_device *ld, पूर्णांक घातer)
अणु
	काष्ठा lms283gf05_state *st = lcd_get_data(ld);
	काष्ठा spi_device *spi = st->spi;

	अगर (घातer <= FB_BLANK_NORMAL) अणु
		अगर (st->reset)
			lms283gf05_reset(st->reset);
		lms283gf05_toggle(spi, disp_initseq, ARRAY_SIZE(disp_initseq));
	पूर्ण अन्यथा अणु
		lms283gf05_toggle(spi, disp_pdwnseq, ARRAY_SIZE(disp_pdwnseq));
		अगर (st->reset)
			gpiod_set_value(st->reset, 1); /* Asserted */
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा lcd_ops lms_ops = अणु
	.set_घातer	= lms283gf05_घातer_set,
	.get_घातer	= शून्य,
पूर्ण;

अटल पूर्णांक lms283gf05_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा lms283gf05_state *st;
	काष्ठा lcd_device *ld;

	st = devm_kzalloc(&spi->dev, माप(काष्ठा lms283gf05_state),
				GFP_KERNEL);
	अगर (st == शून्य)
		वापस -ENOMEM;

	st->reset = gpiod_get_optional(&spi->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(st->reset))
		वापस PTR_ERR(st->reset);
	gpiod_set_consumer_name(st->reset, "LMS283GF05 RESET");

	ld = devm_lcd_device_रेजिस्टर(&spi->dev, "lms283gf05", &spi->dev, st,
					&lms_ops);
	अगर (IS_ERR(ld))
		वापस PTR_ERR(ld);

	st->spi = spi;
	st->ld = ld;

	spi_set_drvdata(spi, st);

	/* kick in the LCD */
	अगर (st->reset)
		lms283gf05_reset(st->reset);
	lms283gf05_toggle(spi, disp_initseq, ARRAY_SIZE(disp_initseq));

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver lms283gf05_driver = अणु
	.driver = अणु
		.name	= "lms283gf05",
	पूर्ण,
	.probe		= lms283gf05_probe,
पूर्ण;

module_spi_driver(lms283gf05_driver);

MODULE_AUTHOR("Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("LCD283GF05 LCD");
MODULE_LICENSE("GPL v2");
