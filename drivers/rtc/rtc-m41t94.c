<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम ST M41T94 SPI RTC
 *
 * Copyright (C) 2008 Kim B. Heino
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/bcd.h>

#घोषणा M41T94_REG_SECONDS	0x01
#घोषणा M41T94_REG_MINUTES	0x02
#घोषणा M41T94_REG_HOURS	0x03
#घोषणा M41T94_REG_WDAY		0x04
#घोषणा M41T94_REG_DAY		0x05
#घोषणा M41T94_REG_MONTH	0x06
#घोषणा M41T94_REG_YEAR		0x07
#घोषणा M41T94_REG_HT		0x0c

#घोषणा M41T94_BIT_HALT		0x40
#घोषणा M41T94_BIT_STOP		0x80
#घोषणा M41T94_BIT_CB		0x40
#घोषणा M41T94_BIT_CEB		0x80

अटल पूर्णांक m41t94_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	u8 buf[8]; /* ग_लिखो cmd + 7 रेजिस्टरs */

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"write", पंचांग->पंचांग_sec, पंचांग->पंचांग_min,
		पंचांग->पंचांग_hour, पंचांग->पंचांग_mday,
		पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	buf[0] = 0x80 | M41T94_REG_SECONDS; /* ग_लिखो समय + date */
	buf[M41T94_REG_SECONDS] = bin2bcd(पंचांग->पंचांग_sec);
	buf[M41T94_REG_MINUTES] = bin2bcd(पंचांग->पंचांग_min);
	buf[M41T94_REG_HOURS]   = bin2bcd(पंचांग->पंचांग_hour);
	buf[M41T94_REG_WDAY]    = bin2bcd(पंचांग->पंचांग_wday + 1);
	buf[M41T94_REG_DAY]     = bin2bcd(पंचांग->पंचांग_mday);
	buf[M41T94_REG_MONTH]   = bin2bcd(पंचांग->पंचांग_mon + 1);

	buf[M41T94_REG_HOURS] |= M41T94_BIT_CEB;
	अगर (पंचांग->पंचांग_year >= 100)
		buf[M41T94_REG_HOURS] |= M41T94_BIT_CB;
	buf[M41T94_REG_YEAR] = bin2bcd(पंचांग->पंचांग_year % 100);

	वापस spi_ग_लिखो(spi, buf, 8);
पूर्ण

अटल पूर्णांक m41t94_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	u8 buf[2];
	पूर्णांक ret, hour;

	/* clear halt update bit */
	ret = spi_w8r8(spi, M41T94_REG_HT);
	अगर (ret < 0)
		वापस ret;
	अगर (ret & M41T94_BIT_HALT) अणु
		buf[0] = 0x80 | M41T94_REG_HT;
		buf[1] = ret & ~M41T94_BIT_HALT;
		spi_ग_लिखो(spi, buf, 2);
	पूर्ण

	/* clear stop bit */
	ret = spi_w8r8(spi, M41T94_REG_SECONDS);
	अगर (ret < 0)
		वापस ret;
	अगर (ret & M41T94_BIT_STOP) अणु
		buf[0] = 0x80 | M41T94_REG_SECONDS;
		buf[1] = ret & ~M41T94_BIT_STOP;
		spi_ग_लिखो(spi, buf, 2);
	पूर्ण

	पंचांग->पंचांग_sec  = bcd2bin(spi_w8r8(spi, M41T94_REG_SECONDS));
	पंचांग->पंचांग_min  = bcd2bin(spi_w8r8(spi, M41T94_REG_MINUTES));
	hour = spi_w8r8(spi, M41T94_REG_HOURS);
	पंचांग->पंचांग_hour = bcd2bin(hour & 0x3f);
	पंचांग->पंचांग_wday = bcd2bin(spi_w8r8(spi, M41T94_REG_WDAY)) - 1;
	पंचांग->पंचांग_mday = bcd2bin(spi_w8r8(spi, M41T94_REG_DAY));
	पंचांग->पंचांग_mon  = bcd2bin(spi_w8r8(spi, M41T94_REG_MONTH)) - 1;
	पंचांग->पंचांग_year = bcd2bin(spi_w8r8(spi, M41T94_REG_YEAR));
	अगर ((hour & M41T94_BIT_CB) || !(hour & M41T94_BIT_CEB))
		पंचांग->पंचांग_year += 100;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"read", पंचांग->पंचांग_sec, पंचांग->पंचांग_min,
		पंचांग->पंचांग_hour, पंचांग->पंचांग_mday,
		पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops m41t94_rtc_ops = अणु
	.पढ़ो_समय	= m41t94_पढ़ो_समय,
	.set_समय	= m41t94_set_समय,
पूर्ण;

अटल काष्ठा spi_driver m41t94_driver;

अटल पूर्णांक m41t94_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा rtc_device *rtc;
	पूर्णांक res;

	spi->bits_per_word = 8;
	spi_setup(spi);

	res = spi_w8r8(spi, M41T94_REG_SECONDS);
	अगर (res < 0) अणु
		dev_err(&spi->dev, "not found.\n");
		वापस res;
	पूर्ण

	rtc = devm_rtc_device_रेजिस्टर(&spi->dev, m41t94_driver.driver.name,
					&m41t94_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	spi_set_drvdata(spi, rtc);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver m41t94_driver = अणु
	.driver = अणु
		.name	= "rtc-m41t94",
	पूर्ण,
	.probe	= m41t94_probe,
पूर्ण;

module_spi_driver(m41t94_driver);

MODULE_AUTHOR("Kim B. Heino <Kim.Heino@bluegiga.com>");
MODULE_DESCRIPTION("Driver for ST M41T94 SPI RTC");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:rtc-m41t94");
