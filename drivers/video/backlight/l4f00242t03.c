<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * l4f00242t03.c -- support क्रम Epson L4F00242T03 LCD
 *
 * Copyright 2007-2009 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * Copyright (c) 2009 Alberto Panizzo <maramaopercheseimorto@gmail.com>
 *	Inspired by Marek Vasut work in l4f00242t03.c
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/lcd.h>
#समावेश <linux/slab.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

काष्ठा l4f00242t03_priv अणु
	काष्ठा spi_device	*spi;
	काष्ठा lcd_device	*ld;
	पूर्णांक lcd_state;
	काष्ठा regulator *io_reg;
	काष्ठा regulator *core_reg;
	काष्ठा gpio_desc *reset;
	काष्ठा gpio_desc *enable;
पूर्ण;

अटल व्योम l4f00242t03_reset(काष्ठा gpio_desc *gpiod)
अणु
	pr_debug("l4f00242t03_reset.\n");
	gpiod_set_value(gpiod, 1);
	mdelay(100);
	gpiod_set_value(gpiod, 0);
	mdelay(10);	/* tRES >= 100us */
	gpiod_set_value(gpiod, 1);
	mdelay(20);
पूर्ण

#घोषणा param(x) ((x) | 0x100)

अटल व्योम l4f00242t03_lcd_init(काष्ठा spi_device *spi)
अणु
	काष्ठा l4f00242t03_priv *priv = spi_get_drvdata(spi);
	स्थिर u16 cmd[] = अणु 0x36, param(0), 0x3A, param(0x60) पूर्ण;
	पूर्णांक ret;

	dev_dbg(&spi->dev, "initializing LCD\n");

	ret = regulator_set_voltage(priv->io_reg, 1800000, 1800000);
	अगर (ret) अणु
		dev_err(&spi->dev, "failed to set the IO regulator voltage.\n");
		वापस;
	पूर्ण
	ret = regulator_enable(priv->io_reg);
	अगर (ret) अणु
		dev_err(&spi->dev, "failed to enable the IO regulator.\n");
		वापस;
	पूर्ण

	ret = regulator_set_voltage(priv->core_reg, 2800000, 2800000);
	अगर (ret) अणु
		dev_err(&spi->dev, "failed to set the core regulator voltage.\n");
		regulator_disable(priv->io_reg);
		वापस;
	पूर्ण
	ret = regulator_enable(priv->core_reg);
	अगर (ret) अणु
		dev_err(&spi->dev, "failed to enable the core regulator.\n");
		regulator_disable(priv->io_reg);
		वापस;
	पूर्ण

	l4f00242t03_reset(priv->reset);

	gpiod_set_value(priv->enable, 1);
	msleep(60);
	spi_ग_लिखो(spi, (स्थिर u8 *)cmd, ARRAY_SIZE(cmd) * माप(u16));
पूर्ण

अटल व्योम l4f00242t03_lcd_घातerकरोwn(काष्ठा spi_device *spi)
अणु
	काष्ठा l4f00242t03_priv *priv = spi_get_drvdata(spi);

	dev_dbg(&spi->dev, "Powering down LCD\n");

	gpiod_set_value(priv->enable, 0);

	regulator_disable(priv->io_reg);
	regulator_disable(priv->core_reg);
पूर्ण

अटल पूर्णांक l4f00242t03_lcd_घातer_get(काष्ठा lcd_device *ld)
अणु
	काष्ठा l4f00242t03_priv *priv = lcd_get_data(ld);

	वापस priv->lcd_state;
पूर्ण

अटल पूर्णांक l4f00242t03_lcd_घातer_set(काष्ठा lcd_device *ld, पूर्णांक घातer)
अणु
	काष्ठा l4f00242t03_priv *priv = lcd_get_data(ld);
	काष्ठा spi_device *spi = priv->spi;

	स्थिर u16 slpout = 0x11;
	स्थिर u16 dison = 0x29;

	स्थिर u16 slpin = 0x10;
	स्थिर u16 disoff = 0x28;

	अगर (घातer <= FB_BLANK_NORMAL) अणु
		अगर (priv->lcd_state <= FB_BLANK_NORMAL) अणु
			/* Do nothing, the LCD is running */
		पूर्ण अन्यथा अगर (priv->lcd_state < FB_BLANK_POWERDOWN) अणु
			dev_dbg(&spi->dev, "Resuming LCD\n");

			spi_ग_लिखो(spi, (स्थिर u8 *)&slpout, माप(u16));
			msleep(60);
			spi_ग_लिखो(spi, (स्थिर u8 *)&dison, माप(u16));
		पूर्ण अन्यथा अणु
			/* priv->lcd_state == FB_BLANK_POWERDOWN */
			l4f00242t03_lcd_init(spi);
			priv->lcd_state = FB_BLANK_VSYNC_SUSPEND;
			l4f00242t03_lcd_घातer_set(priv->ld, घातer);
		पूर्ण
	पूर्ण अन्यथा अगर (घातer < FB_BLANK_POWERDOWN) अणु
		अगर (priv->lcd_state <= FB_BLANK_NORMAL) अणु
			/* Send the display in standby */
			dev_dbg(&spi->dev, "Standby the LCD\n");

			spi_ग_लिखो(spi, (स्थिर u8 *)&disoff, माप(u16));
			msleep(60);
			spi_ग_लिखो(spi, (स्थिर u8 *)&slpin, माप(u16));
		पूर्ण अन्यथा अगर (priv->lcd_state < FB_BLANK_POWERDOWN) अणु
			/* Do nothing, the LCD is alपढ़ोy in standby */
		पूर्ण अन्यथा अणु
			/* priv->lcd_state == FB_BLANK_POWERDOWN */
			l4f00242t03_lcd_init(spi);
			priv->lcd_state = FB_BLANK_UNBLANK;
			l4f00242t03_lcd_घातer_set(ld, घातer);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* घातer == FB_BLANK_POWERDOWN */
		अगर (priv->lcd_state != FB_BLANK_POWERDOWN) अणु
			/* Clear the screen beक्रमe shutting करोwn */
			spi_ग_लिखो(spi, (स्थिर u8 *)&disoff, माप(u16));
			msleep(60);
			l4f00242t03_lcd_घातerकरोwn(spi);
		पूर्ण
	पूर्ण

	priv->lcd_state = घातer;

	वापस 0;
पूर्ण

अटल काष्ठा lcd_ops l4f_ops = अणु
	.set_घातer	= l4f00242t03_lcd_घातer_set,
	.get_घातer	= l4f00242t03_lcd_घातer_get,
पूर्ण;

अटल पूर्णांक l4f00242t03_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा l4f00242t03_priv *priv;

	priv = devm_kzalloc(&spi->dev, माप(काष्ठा l4f00242t03_priv),
				GFP_KERNEL);
	अगर (priv == शून्य)
		वापस -ENOMEM;

	spi_set_drvdata(spi, priv);
	spi->bits_per_word = 9;
	spi_setup(spi);

	priv->spi = spi;

	priv->reset = devm_gpiod_get(&spi->dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->reset)) अणु
		dev_err(&spi->dev,
			"Unable to get the lcd l4f00242t03 reset gpio.\n");
		वापस PTR_ERR(priv->reset);
	पूर्ण
	gpiod_set_consumer_name(priv->reset, "lcd l4f00242t03 reset");

	priv->enable = devm_gpiod_get(&spi->dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->enable)) अणु
		dev_err(&spi->dev,
			"Unable to get the lcd l4f00242t03 data en gpio.\n");
		वापस PTR_ERR(priv->enable);
	पूर्ण
	gpiod_set_consumer_name(priv->enable, "lcd l4f00242t03 data enable");

	priv->io_reg = devm_regulator_get(&spi->dev, "vdd");
	अगर (IS_ERR(priv->io_reg)) अणु
		dev_err(&spi->dev, "%s: Unable to get the IO regulator\n",
		       __func__);
		वापस PTR_ERR(priv->io_reg);
	पूर्ण

	priv->core_reg = devm_regulator_get(&spi->dev, "vcore");
	अगर (IS_ERR(priv->core_reg)) अणु
		dev_err(&spi->dev, "%s: Unable to get the core regulator\n",
		       __func__);
		वापस PTR_ERR(priv->core_reg);
	पूर्ण

	priv->ld = devm_lcd_device_रेजिस्टर(&spi->dev, "l4f00242t03", &spi->dev,
					priv, &l4f_ops);
	अगर (IS_ERR(priv->ld))
		वापस PTR_ERR(priv->ld);

	/* Init the LCD */
	l4f00242t03_lcd_init(spi);
	priv->lcd_state = FB_BLANK_VSYNC_SUSPEND;
	l4f00242t03_lcd_घातer_set(priv->ld, FB_BLANK_UNBLANK);

	dev_info(&spi->dev, "Epson l4f00242t03 lcd probed.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक l4f00242t03_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा l4f00242t03_priv *priv = spi_get_drvdata(spi);

	l4f00242t03_lcd_घातer_set(priv->ld, FB_BLANK_POWERDOWN);
	वापस 0;
पूर्ण

अटल व्योम l4f00242t03_shutकरोwn(काष्ठा spi_device *spi)
अणु
	काष्ठा l4f00242t03_priv *priv = spi_get_drvdata(spi);

	अगर (priv)
		l4f00242t03_lcd_घातer_set(priv->ld, FB_BLANK_POWERDOWN);

पूर्ण

अटल काष्ठा spi_driver l4f00242t03_driver = अणु
	.driver = अणु
		.name	= "l4f00242t03",
	पूर्ण,
	.probe		= l4f00242t03_probe,
	.हटाओ		= l4f00242t03_हटाओ,
	.shutकरोwn	= l4f00242t03_shutकरोwn,
पूर्ण;

module_spi_driver(l4f00242t03_driver);

MODULE_AUTHOR("Alberto Panizzo <maramaopercheseimorto@gmail.com>");
MODULE_DESCRIPTION("EPSON L4F00242T03 LCD");
MODULE_LICENSE("GPL v2");
