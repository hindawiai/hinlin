<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/rtc/rtc-max6902.c
 *
 * Copyright (C) 2006 8D Technologies inc.
 * Copyright (C) 2004 Compulab Ltd.
 *
 * Driver क्रम MAX6902 spi RTC
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/rtc.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/bcd.h>

#घोषणा MAX6902_REG_SECONDS		0x01
#घोषणा MAX6902_REG_MINUTES		0x03
#घोषणा MAX6902_REG_HOURS		0x05
#घोषणा MAX6902_REG_DATE		0x07
#घोषणा MAX6902_REG_MONTH		0x09
#घोषणा MAX6902_REG_DAY			0x0B
#घोषणा MAX6902_REG_YEAR		0x0D
#घोषणा MAX6902_REG_CONTROL		0x0F
#घोषणा MAX6902_REG_CENTURY		0x13

अटल पूर्णांक max6902_set_reg(काष्ठा device *dev, अचिन्हित अक्षर address,
				अचिन्हित अक्षर data)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	अचिन्हित अक्षर buf[2];

	/* MSB must be '0' to ग_लिखो */
	buf[0] = address & 0x7f;
	buf[1] = data;

	वापस spi_ग_लिखो_then_पढ़ो(spi, buf, 2, शून्य, 0);
पूर्ण

अटल पूर्णांक max6902_get_reg(काष्ठा device *dev, अचिन्हित अक्षर address,
				अचिन्हित अक्षर *data)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);

	/* Set MSB to indicate पढ़ो */
	*data = address | 0x80;

	वापस spi_ग_लिखो_then_पढ़ो(spi, data, 1, data, 1);
पूर्ण

अटल पूर्णांक max6902_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	पूर्णांक err, century;
	काष्ठा spi_device *spi = to_spi_device(dev);
	अचिन्हित अक्षर buf[8];

	buf[0] = 0xbf;	/* Burst पढ़ो */

	err = spi_ग_लिखो_then_पढ़ो(spi, buf, 1, buf, 8);
	अगर (err != 0)
		वापस err;

	/* The chip sends data in this order:
	 * Seconds, Minutes, Hours, Date, Month, Day, Year */
	dt->पंचांग_sec	= bcd2bin(buf[0]);
	dt->पंचांग_min	= bcd2bin(buf[1]);
	dt->पंचांग_hour	= bcd2bin(buf[2]);
	dt->पंचांग_mday	= bcd2bin(buf[3]);
	dt->पंचांग_mon	= bcd2bin(buf[4]) - 1;
	dt->पंचांग_wday	= bcd2bin(buf[5]);
	dt->पंचांग_year	= bcd2bin(buf[6]);

	/* Read century */
	err = max6902_get_reg(dev, MAX6902_REG_CENTURY, &buf[0]);
	अगर (err != 0)
		वापस err;

	century = bcd2bin(buf[0]) * 100;

	dt->पंचांग_year += century;
	dt->पंचांग_year -= 1900;

	वापस 0;
पूर्ण

अटल पूर्णांक max6902_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	dt->पंचांग_year = dt->पंचांग_year + 1900;

	/* Remove ग_लिखो protection */
	max6902_set_reg(dev, MAX6902_REG_CONTROL, 0);

	max6902_set_reg(dev, MAX6902_REG_SECONDS, bin2bcd(dt->पंचांग_sec));
	max6902_set_reg(dev, MAX6902_REG_MINUTES, bin2bcd(dt->पंचांग_min));
	max6902_set_reg(dev, MAX6902_REG_HOURS, bin2bcd(dt->पंचांग_hour));

	max6902_set_reg(dev, MAX6902_REG_DATE, bin2bcd(dt->पंचांग_mday));
	max6902_set_reg(dev, MAX6902_REG_MONTH, bin2bcd(dt->पंचांग_mon + 1));
	max6902_set_reg(dev, MAX6902_REG_DAY, bin2bcd(dt->पंचांग_wday));
	max6902_set_reg(dev, MAX6902_REG_YEAR, bin2bcd(dt->पंचांग_year % 100));
	max6902_set_reg(dev, MAX6902_REG_CENTURY, bin2bcd(dt->पंचांग_year / 100));

	/* Compulab used a delay here. However, the datasheet
	 * करोes not mention a delay being required anywhere... */
	/* delay(2000); */

	/* Write protect */
	max6902_set_reg(dev, MAX6902_REG_CONTROL, 0x80);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops max6902_rtc_ops = अणु
	.पढ़ो_समय	= max6902_पढ़ो_समय,
	.set_समय	= max6902_set_समय,
पूर्ण;

अटल पूर्णांक max6902_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा rtc_device *rtc;
	अचिन्हित अक्षर पंचांगp;
	पूर्णांक res;

	spi->mode = SPI_MODE_3;
	spi->bits_per_word = 8;
	spi_setup(spi);

	res = max6902_get_reg(&spi->dev, MAX6902_REG_SECONDS, &पंचांगp);
	अगर (res != 0)
		वापस res;

	rtc = devm_rtc_device_रेजिस्टर(&spi->dev, "max6902",
				&max6902_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	spi_set_drvdata(spi, rtc);
	वापस 0;
पूर्ण

अटल काष्ठा spi_driver max6902_driver = अणु
	.driver = अणु
		.name	= "rtc-max6902",
	पूर्ण,
	.probe	= max6902_probe,
पूर्ण;

module_spi_driver(max6902_driver);

MODULE_DESCRIPTION("max6902 spi RTC driver");
MODULE_AUTHOR("Raphael Assenat");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:rtc-max6902");
