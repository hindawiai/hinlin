<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Dallas DS1302 RTC Support
 *
 *  Copyright (C) 2002 David McCullough
 *  Copyright (C) 2003 - 2007 Paul Mundt
 */

#समावेश <linux/bcd.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/rtc.h>
#समावेश <linux/spi/spi.h>

#घोषणा	RTC_CMD_READ	0x81		/* Read command */
#घोषणा	RTC_CMD_WRITE	0x80		/* Write command */

#घोषणा	RTC_CMD_WRITE_ENABLE	0x00		/* Write enable */
#घोषणा	RTC_CMD_WRITE_DISABLE	0x80		/* Write disable */

#घोषणा RTC_ADDR_RAM0	0x20		/* Address of RAM0 */
#घोषणा RTC_ADDR_TCR	0x08		/* Address of trickle अक्षरge रेजिस्टर */
#घोषणा RTC_CLCK_BURST	0x1F		/* Address of घड़ी burst */
#घोषणा	RTC_CLCK_LEN	0x08		/* Size of घड़ी burst */
#घोषणा	RTC_ADDR_CTRL	0x07		/* Address of control रेजिस्टर */
#घोषणा	RTC_ADDR_YEAR	0x06		/* Address of year रेजिस्टर */
#घोषणा	RTC_ADDR_DAY	0x05		/* Address of day of week रेजिस्टर */
#घोषणा	RTC_ADDR_MON	0x04		/* Address of month रेजिस्टर */
#घोषणा	RTC_ADDR_DATE	0x03		/* Address of day of month रेजिस्टर */
#घोषणा	RTC_ADDR_HOUR	0x02		/* Address of hour रेजिस्टर */
#घोषणा	RTC_ADDR_MIN	0x01		/* Address of minute रेजिस्टर */
#घोषणा	RTC_ADDR_SEC	0x00		/* Address of second रेजिस्टर */

अटल पूर्णांक ds1302_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *समय)
अणु
	काष्ठा spi_device	*spi = dev_get_drvdata(dev);
	u8		buf[1 + RTC_CLCK_LEN];
	u8		*bp;
	पूर्णांक		status;

	/* Enable writing */
	bp = buf;
	*bp++ = RTC_ADDR_CTRL << 1 | RTC_CMD_WRITE;
	*bp++ = RTC_CMD_WRITE_ENABLE;

	status = spi_ग_लिखो_then_पढ़ो(spi, buf, 2,
			शून्य, 0);
	अगर (status)
		वापस status;

	/* Write रेजिस्टरs starting at the first समय/date address. */
	bp = buf;
	*bp++ = RTC_CLCK_BURST << 1 | RTC_CMD_WRITE;

	*bp++ = bin2bcd(समय->पंचांग_sec);
	*bp++ = bin2bcd(समय->पंचांग_min);
	*bp++ = bin2bcd(समय->पंचांग_hour);
	*bp++ = bin2bcd(समय->पंचांग_mday);
	*bp++ = bin2bcd(समय->पंचांग_mon + 1);
	*bp++ = समय->पंचांग_wday + 1;
	*bp++ = bin2bcd(समय->पंचांग_year % 100);
	*bp++ = RTC_CMD_WRITE_DISABLE;

	/* use ग_लिखो-then-पढ़ो since dma from stack is nonportable */
	वापस spi_ग_लिखो_then_पढ़ो(spi, buf, माप(buf),
			शून्य, 0);
पूर्ण

अटल पूर्णांक ds1302_rtc_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *समय)
अणु
	काष्ठा spi_device	*spi = dev_get_drvdata(dev);
	u8		addr = RTC_CLCK_BURST << 1 | RTC_CMD_READ;
	u8		buf[RTC_CLCK_LEN - 1];
	पूर्णांक		status;

	/* Use ग_लिखो-then-पढ़ो to get all the date/समय रेजिस्टरs
	 * since dma from stack is nonportable
	 */
	status = spi_ग_लिखो_then_पढ़ो(spi, &addr, माप(addr),
			buf, माप(buf));
	अगर (status < 0)
		वापस status;

	/* Decode the रेजिस्टरs */
	समय->पंचांग_sec = bcd2bin(buf[RTC_ADDR_SEC]);
	समय->पंचांग_min = bcd2bin(buf[RTC_ADDR_MIN]);
	समय->पंचांग_hour = bcd2bin(buf[RTC_ADDR_HOUR]);
	समय->पंचांग_wday = buf[RTC_ADDR_DAY] - 1;
	समय->पंचांग_mday = bcd2bin(buf[RTC_ADDR_DATE]);
	समय->पंचांग_mon = bcd2bin(buf[RTC_ADDR_MON]) - 1;
	समय->पंचांग_year = bcd2bin(buf[RTC_ADDR_YEAR]) + 100;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ds1302_rtc_ops = अणु
	.पढ़ो_समय	= ds1302_rtc_get_समय,
	.set_समय	= ds1302_rtc_set_समय,
पूर्ण;

अटल पूर्णांक ds1302_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा rtc_device	*rtc;
	u8		addr;
	u8		buf[4];
	u8		*bp;
	पूर्णांक		status;

	/* Sanity check board setup data.  This may be hooked up
	 * in 3wire mode, but we करोn't care.  Note that unless
	 * there's an inverter in place, this needs SPI_CS_HIGH!
	 */
	अगर (spi->bits_per_word && (spi->bits_per_word != 8)) अणु
		dev_err(&spi->dev, "bad word length\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (spi->max_speed_hz > 2000000) अणु
		dev_err(&spi->dev, "speed is too high\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (spi->mode & SPI_CPHA) अणु
		dev_err(&spi->dev, "bad mode\n");
		वापस -EINVAL;
	पूर्ण

	addr = RTC_ADDR_CTRL << 1 | RTC_CMD_READ;
	status = spi_ग_लिखो_then_पढ़ो(spi, &addr, माप(addr), buf, 1);
	अगर (status < 0) अणु
		dev_err(&spi->dev, "control register read error %d\n",
				status);
		वापस status;
	पूर्ण

	अगर ((buf[0] & ~RTC_CMD_WRITE_DISABLE) != 0) अणु
		status = spi_ग_लिखो_then_पढ़ो(spi, &addr, माप(addr), buf, 1);
		अगर (status < 0) अणु
			dev_err(&spi->dev, "control register read error %d\n",
					status);
			वापस status;
		पूर्ण

		अगर ((buf[0] & ~RTC_CMD_WRITE_DISABLE) != 0) अणु
			dev_err(&spi->dev, "junk in control register\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	अगर (buf[0] == 0) अणु
		bp = buf;
		*bp++ = RTC_ADDR_CTRL << 1 | RTC_CMD_WRITE;
		*bp++ = RTC_CMD_WRITE_DISABLE;

		status = spi_ग_लिखो_then_पढ़ो(spi, buf, 2, शून्य, 0);
		अगर (status < 0) अणु
			dev_err(&spi->dev, "control register write error %d\n",
					status);
			वापस status;
		पूर्ण

		addr = RTC_ADDR_CTRL << 1 | RTC_CMD_READ;
		status = spi_ग_लिखो_then_पढ़ो(spi, &addr, माप(addr), buf, 1);
		अगर (status < 0) अणु
			dev_err(&spi->dev,
					"error %d reading control register\n",
					status);
			वापस status;
		पूर्ण

		अगर (buf[0] != RTC_CMD_WRITE_DISABLE) अणु
			dev_err(&spi->dev, "failed to detect chip\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	spi_set_drvdata(spi, spi);

	rtc = devm_rtc_device_रेजिस्टर(&spi->dev, "ds1302",
			&ds1302_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc)) अणु
		status = PTR_ERR(rtc);
		dev_err(&spi->dev, "error %d registering rtc\n", status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ds1302_हटाओ(काष्ठा spi_device *spi)
अणु
	spi_set_drvdata(spi, शून्य);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ds1302_dt_ids[] = अणु
	अणु .compatible = "maxim,ds1302", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ds1302_dt_ids);
#पूर्ण_अगर

अटल काष्ठा spi_driver ds1302_driver = अणु
	.driver.name	= "rtc-ds1302",
	.driver.of_match_table = of_match_ptr(ds1302_dt_ids),
	.probe		= ds1302_probe,
	.हटाओ		= ds1302_हटाओ,
पूर्ण;

module_spi_driver(ds1302_driver);

MODULE_DESCRIPTION("Dallas DS1302 RTC driver");
MODULE_AUTHOR("Paul Mundt, David McCullough");
MODULE_LICENSE("GPL v2");
