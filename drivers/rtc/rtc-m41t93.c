<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Driver क्रम ST M41T93 SPI RTC
 *
 * (c) 2010 Nikolaus Voss, Weinmann Medical GmbH
 */

#समावेश <linux/bcd.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/spi/spi.h>

#घोषणा M41T93_REG_SSEC			0
#घोषणा M41T93_REG_ST_SEC		1
#घोषणा M41T93_REG_MIN			2
#घोषणा M41T93_REG_CENT_HOUR		3
#घोषणा M41T93_REG_WDAY			4
#घोषणा M41T93_REG_DAY			5
#घोषणा M41T93_REG_MON			6
#घोषणा M41T93_REG_YEAR			7


#घोषणा M41T93_REG_ALM_HOUR_HT		0xc
#घोषणा M41T93_REG_FLAGS		0xf

#घोषणा M41T93_FLAG_ST			(1 << 7)
#घोषणा M41T93_FLAG_OF			(1 << 2)
#घोषणा M41T93_FLAG_BL			(1 << 4)
#घोषणा M41T93_FLAG_HT			(1 << 6)

अटल अंतरभूत पूर्णांक m41t93_set_reg(काष्ठा spi_device *spi, u8 addr, u8 data)
अणु
	u8 buf[2];

	/* MSB must be '1' to ग_लिखो */
	buf[0] = addr | 0x80;
	buf[1] = data;

	वापस spi_ग_लिखो(spi, buf, माप(buf));
पूर्ण

अटल पूर्णांक m41t93_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	पूर्णांक पंचांगp;
	u8 buf[9] = अणु0x80पूर्ण;        /* ग_लिखो cmd + 8 data bytes */
	u8 * स्थिर data = &buf[1]; /* ptr to first data byte */

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"write", पंचांग->पंचांग_sec, पंचांग->पंचांग_min,
		पंचांग->पंचांग_hour, पंचांग->पंचांग_mday,
		पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	अगर (पंचांग->पंचांग_year < 100) अणु
		dev_warn(&spi->dev, "unsupported date (before 2000-01-01).\n");
		वापस -EINVAL;
	पूर्ण

	पंचांगp = spi_w8r8(spi, M41T93_REG_FLAGS);
	अगर (पंचांगp < 0)
		वापस पंचांगp;

	अगर (पंचांगp & M41T93_FLAG_OF) अणु
		dev_warn(&spi->dev, "OF bit is set, resetting.\n");
		m41t93_set_reg(spi, M41T93_REG_FLAGS, पंचांगp & ~M41T93_FLAG_OF);

		पंचांगp = spi_w8r8(spi, M41T93_REG_FLAGS);
		अगर (पंचांगp < 0) अणु
			वापस पंचांगp;
		पूर्ण अन्यथा अगर (पंचांगp & M41T93_FLAG_OF) अणु
			/* OF cannot be immediately reset: oscillator has to be
			 * restarted. */
			u8 reset_osc = buf[M41T93_REG_ST_SEC] | M41T93_FLAG_ST;

			dev_warn(&spi->dev,
				 "OF bit is still set, kickstarting clock.\n");
			m41t93_set_reg(spi, M41T93_REG_ST_SEC, reset_osc);
			reset_osc &= ~M41T93_FLAG_ST;
			m41t93_set_reg(spi, M41T93_REG_ST_SEC, reset_osc);
		पूर्ण
	पूर्ण

	data[M41T93_REG_SSEC]		= 0;
	data[M41T93_REG_ST_SEC]		= bin2bcd(पंचांग->पंचांग_sec);
	data[M41T93_REG_MIN]		= bin2bcd(पंचांग->पंचांग_min);
	data[M41T93_REG_CENT_HOUR]	= bin2bcd(पंचांग->पंचांग_hour) |
						((पंचांग->पंचांग_year/100-1) << 6);
	data[M41T93_REG_DAY]		= bin2bcd(पंचांग->पंचांग_mday);
	data[M41T93_REG_WDAY]		= bin2bcd(पंचांग->पंचांग_wday + 1);
	data[M41T93_REG_MON]		= bin2bcd(पंचांग->पंचांग_mon + 1);
	data[M41T93_REG_YEAR]		= bin2bcd(पंचांग->पंचांग_year % 100);

	वापस spi_ग_लिखो(spi, buf, माप(buf));
पूर्ण


अटल पूर्णांक m41t93_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	स्थिर u8 start_addr = 0;
	u8 buf[8];
	पूर्णांक century_after_1900;
	पूर्णांक पंचांगp;
	पूर्णांक ret = 0;

	/* Check status of घड़ी. Two states must be considered:
	   1. halt bit (HT) is set: the घड़ी is running but update of पढ़ोout
	      रेजिस्टरs has been disabled due to घातer failure. This is normal
	      हाल after घातeron. Time is valid after resetting HT bit.
	   2. oscillator fail bit (OF) is set: समय is invalid.
	*/
	पंचांगp = spi_w8r8(spi, M41T93_REG_ALM_HOUR_HT);
	अगर (पंचांगp < 0)
		वापस पंचांगp;

	अगर (पंचांगp & M41T93_FLAG_HT) अणु
		dev_dbg(&spi->dev, "HT bit is set, reenable clock update.\n");
		m41t93_set_reg(spi, M41T93_REG_ALM_HOUR_HT,
			       पंचांगp & ~M41T93_FLAG_HT);
	पूर्ण

	पंचांगp = spi_w8r8(spi, M41T93_REG_FLAGS);
	अगर (पंचांगp < 0)
		वापस पंचांगp;

	अगर (पंचांगp & M41T93_FLAG_OF) अणु
		ret = -EINVAL;
		dev_warn(&spi->dev, "OF bit is set, write time to restart.\n");
	पूर्ण

	अगर (पंचांगp & M41T93_FLAG_BL)
		dev_warn(&spi->dev, "BL bit is set, replace battery.\n");

	/* पढ़ो actual समय/date */
	पंचांगp = spi_ग_लिखो_then_पढ़ो(spi, &start_addr, 1, buf, माप(buf));
	अगर (पंचांगp < 0)
		वापस पंचांगp;

	पंचांग->पंचांग_sec	= bcd2bin(buf[M41T93_REG_ST_SEC]);
	पंचांग->पंचांग_min	= bcd2bin(buf[M41T93_REG_MIN]);
	पंचांग->पंचांग_hour	= bcd2bin(buf[M41T93_REG_CENT_HOUR] & 0x3f);
	पंचांग->पंचांग_mday	= bcd2bin(buf[M41T93_REG_DAY]);
	पंचांग->पंचांग_mon	= bcd2bin(buf[M41T93_REG_MON]) - 1;
	पंचांग->पंचांग_wday	= bcd2bin(buf[M41T93_REG_WDAY] & 0x0f) - 1;

	century_after_1900 = (buf[M41T93_REG_CENT_HOUR] >> 6) + 1;
	पंचांग->पंचांग_year = bcd2bin(buf[M41T93_REG_YEAR]) + century_after_1900 * 100;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"read", पंचांग->पंचांग_sec, पंचांग->पंचांग_min,
		पंचांग->पंचांग_hour, पंचांग->पंचांग_mday,
		पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	वापस ret;
पूर्ण


अटल स्थिर काष्ठा rtc_class_ops m41t93_rtc_ops = अणु
	.पढ़ो_समय	= m41t93_get_समय,
	.set_समय	= m41t93_set_समय,
पूर्ण;

अटल काष्ठा spi_driver m41t93_driver;

अटल पूर्णांक m41t93_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा rtc_device *rtc;
	पूर्णांक res;

	spi->bits_per_word = 8;
	spi_setup(spi);

	res = spi_w8r8(spi, M41T93_REG_WDAY);
	अगर (res < 0 || (res & 0xf8) != 0) अणु
		dev_err(&spi->dev, "not found 0x%x.\n", res);
		वापस -ENODEV;
	पूर्ण

	rtc = devm_rtc_device_रेजिस्टर(&spi->dev, m41t93_driver.driver.name,
					&m41t93_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	spi_set_drvdata(spi, rtc);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver m41t93_driver = अणु
	.driver = अणु
		.name	= "rtc-m41t93",
	पूर्ण,
	.probe	= m41t93_probe,
पूर्ण;

module_spi_driver(m41t93_driver);

MODULE_AUTHOR("Nikolaus Voss <n.voss@weinmann.de>");
MODULE_DESCRIPTION("Driver for ST M41T93 SPI RTC");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:rtc-m41t93");
