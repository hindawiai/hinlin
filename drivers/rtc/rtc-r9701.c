<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Epson RTC-9701JE
 *
 * Copyright (C) 2008 Magnus Damm
 *
 * Based on rtc-max6902.c
 *
 * Copyright (C) 2006 8D Technologies inc.
 * Copyright (C) 2004 Compulab Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/rtc.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/bcd.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>

#घोषणा RSECCNT	0x00	/* Second Counter */
#घोषणा RMINCNT	0x01	/* Minute Counter */
#घोषणा RHRCNT	0x02	/* Hour Counter */
#घोषणा RWKCNT	0x03	/* Week Counter */
#घोषणा RDAYCNT	0x04	/* Day Counter */
#घोषणा RMONCNT	0x05	/* Month Counter */
#घोषणा RYRCNT	0x06	/* Year Counter */
#घोषणा R100CNT	0x07	/* Y100 Counter */
#घोषणा RMINAR	0x08	/* Minute Alarm */
#घोषणा RHRAR	0x09	/* Hour Alarm */
#घोषणा RWKAR	0x0a	/* Week/Day Alarm */
#घोषणा RTIMCNT	0x0c	/* Interval Timer */
#घोषणा REXT	0x0d	/* Extension Register */
#घोषणा RFLAG	0x0e	/* RTC Flag Register */
#घोषणा RCR	0x0f	/* RTC Control Register */

अटल पूर्णांक ग_लिखो_reg(काष्ठा device *dev, पूर्णांक address, अचिन्हित अक्षर data)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	अचिन्हित अक्षर buf[2];

	buf[0] = address & 0x7f;
	buf[1] = data;

	वापस spi_ग_लिखो(spi, buf, ARRAY_SIZE(buf));
पूर्ण

अटल पूर्णांक पढ़ो_regs(काष्ठा device *dev, अचिन्हित अक्षर *regs, पूर्णांक no_regs)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	u8 txbuf[1], rxbuf[1];
	पूर्णांक k, ret;

	ret = 0;

	क्रम (k = 0; ret == 0 && k < no_regs; k++) अणु
		txbuf[0] = 0x80 | regs[k];
		ret = spi_ग_लिखो_then_पढ़ो(spi, txbuf, 1, rxbuf, 1);
		regs[k] = rxbuf[0];
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक r9701_get_dateसमय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर buf[] = अणु RSECCNT, RMINCNT, RHRCNT,
				RDAYCNT, RMONCNT, RYRCNT पूर्ण;

	ret = पढ़ो_regs(dev, buf, ARRAY_SIZE(buf));
	अगर (ret)
		वापस ret;

	dt->पंचांग_sec = bcd2bin(buf[0]); /* RSECCNT */
	dt->पंचांग_min = bcd2bin(buf[1]); /* RMINCNT */
	dt->पंचांग_hour = bcd2bin(buf[2]); /* RHRCNT */

	dt->पंचांग_mday = bcd2bin(buf[3]); /* RDAYCNT */
	dt->पंचांग_mon = bcd2bin(buf[4]) - 1; /* RMONCNT */
	dt->पंचांग_year = bcd2bin(buf[5]) + 100; /* RYRCNT */

	वापस 0;
पूर्ण

अटल पूर्णांक r9701_set_dateसमय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	पूर्णांक ret;

	ret = ग_लिखो_reg(dev, RHRCNT, bin2bcd(dt->पंचांग_hour));
	ret = ret ? ret : ग_लिखो_reg(dev, RMINCNT, bin2bcd(dt->पंचांग_min));
	ret = ret ? ret : ग_लिखो_reg(dev, RSECCNT, bin2bcd(dt->पंचांग_sec));
	ret = ret ? ret : ग_लिखो_reg(dev, RDAYCNT, bin2bcd(dt->पंचांग_mday));
	ret = ret ? ret : ग_लिखो_reg(dev, RMONCNT, bin2bcd(dt->पंचांग_mon + 1));
	ret = ret ? ret : ग_लिखो_reg(dev, RYRCNT, bin2bcd(dt->पंचांग_year - 100));

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops r9701_rtc_ops = अणु
	.पढ़ो_समय	= r9701_get_dateसमय,
	.set_समय	= r9701_set_dateसमय,
पूर्ण;

अटल पूर्णांक r9701_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा rtc_device *rtc;
	अचिन्हित अक्षर पंचांगp;
	पूर्णांक res;

	पंचांगp = R100CNT;
	res = पढ़ो_regs(&spi->dev, &पंचांगp, 1);
	अगर (res || पंचांगp != 0x20) अणु
		dev_err(&spi->dev, "cannot read RTC register\n");
		वापस -ENODEV;
	पूर्ण

	rtc = devm_rtc_allocate_device(&spi->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	spi_set_drvdata(spi, rtc);
	rtc->ops = &r9701_rtc_ops;
	rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rtc->range_max = RTC_TIMESTAMP_END_2099;

	वापस devm_rtc_रेजिस्टर_device(rtc);
पूर्ण

अटल काष्ठा spi_driver r9701_driver = अणु
	.driver = अणु
		.name	= "rtc-r9701",
	पूर्ण,
	.probe	= r9701_probe,
पूर्ण;

module_spi_driver(r9701_driver);

MODULE_DESCRIPTION("r9701 spi RTC driver");
MODULE_AUTHOR("Magnus Damm <damm@opensource.se>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:rtc-r9701");
