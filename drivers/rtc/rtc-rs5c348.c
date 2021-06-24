<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * A SPI driver क्रम the Ricoh RS5C348 RTC
 *
 * Copyright (C) 2006 Atsushi Nemoto <anemo@mba.ocn.ne.jp>
 *
 * The board specअगरic init code should provide अक्षरacteristics of this
 * device:
 *     Mode 1 (High-Active, Shअगरt-Then-Sample), High Avtive CS
 */

#समावेश <linux/bcd.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/rtc.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>

#घोषणा RS5C348_REG_SECS	0
#घोषणा RS5C348_REG_MINS	1
#घोषणा RS5C348_REG_HOURS	2
#घोषणा RS5C348_REG_WDAY	3
#घोषणा RS5C348_REG_DAY	4
#घोषणा RS5C348_REG_MONTH	5
#घोषणा RS5C348_REG_YEAR	6
#घोषणा RS5C348_REG_CTL1	14
#घोषणा RS5C348_REG_CTL2	15

#घोषणा RS5C348_SECS_MASK	0x7f
#घोषणा RS5C348_MINS_MASK	0x7f
#घोषणा RS5C348_HOURS_MASK	0x3f
#घोषणा RS5C348_WDAY_MASK	0x03
#घोषणा RS5C348_DAY_MASK	0x3f
#घोषणा RS5C348_MONTH_MASK	0x1f

#घोषणा RS5C348_BIT_PM	0x20	/* REG_HOURS */
#घोषणा RS5C348_BIT_Y2K	0x80	/* REG_MONTH */
#घोषणा RS5C348_BIT_24H	0x20	/* REG_CTL1 */
#घोषणा RS5C348_BIT_XSTP	0x10	/* REG_CTL2 */
#घोषणा RS5C348_BIT_VDET	0x40	/* REG_CTL2 */

#घोषणा RS5C348_CMD_W(addr)	(((addr) << 4) | 0x08)	/* single ग_लिखो */
#घोषणा RS5C348_CMD_R(addr)	(((addr) << 4) | 0x0c)	/* single पढ़ो */
#घोषणा RS5C348_CMD_MW(addr)	(((addr) << 4) | 0x00)	/* burst ग_लिखो */
#घोषणा RS5C348_CMD_MR(addr)	(((addr) << 4) | 0x04)	/* burst पढ़ो */

काष्ठा rs5c348_plat_data अणु
	काष्ठा rtc_device *rtc;
	पूर्णांक rtc_24h;
पूर्ण;

अटल पूर्णांक
rs5c348_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा rs5c348_plat_data *pdata = dev_get_platdata(&spi->dev);
	u8 txbuf[5+7], *txp;
	पूर्णांक ret;

	ret = spi_w8r8(spi, RS5C348_CMD_R(RS5C348_REG_CTL2));
	अगर (ret < 0)
		वापस ret;
	अगर (ret & RS5C348_BIT_XSTP) अणु
		txbuf[0] = RS5C348_CMD_W(RS5C348_REG_CTL2);
		txbuf[1] = 0;
		ret = spi_ग_लिखो_then_पढ़ो(spi, txbuf, 2, शून्य, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Transfer 5 bytes beक्रमe writing SEC.  This gives 31us क्रम carry. */
	txp = txbuf;
	txbuf[0] = RS5C348_CMD_R(RS5C348_REG_CTL2); /* cmd, ctl2 */
	txbuf[1] = 0;	/* dummy */
	txbuf[2] = RS5C348_CMD_R(RS5C348_REG_CTL2); /* cmd, ctl2 */
	txbuf[3] = 0;	/* dummy */
	txbuf[4] = RS5C348_CMD_MW(RS5C348_REG_SECS); /* cmd, sec, ... */
	txp = &txbuf[5];
	txp[RS5C348_REG_SECS] = bin2bcd(पंचांग->पंचांग_sec);
	txp[RS5C348_REG_MINS] = bin2bcd(पंचांग->पंचांग_min);
	अगर (pdata->rtc_24h) अणु
		txp[RS5C348_REG_HOURS] = bin2bcd(पंचांग->पंचांग_hour);
	पूर्ण अन्यथा अणु
		/* hour 0 is AM12, noon is PM12 */
		txp[RS5C348_REG_HOURS] = bin2bcd((पंचांग->पंचांग_hour + 11) % 12 + 1) |
			(पंचांग->पंचांग_hour >= 12 ? RS5C348_BIT_PM : 0);
	पूर्ण
	txp[RS5C348_REG_WDAY] = bin2bcd(पंचांग->पंचांग_wday);
	txp[RS5C348_REG_DAY] = bin2bcd(पंचांग->पंचांग_mday);
	txp[RS5C348_REG_MONTH] = bin2bcd(पंचांग->पंचांग_mon + 1) |
		(पंचांग->पंचांग_year >= 100 ? RS5C348_BIT_Y2K : 0);
	txp[RS5C348_REG_YEAR] = bin2bcd(पंचांग->पंचांग_year % 100);
	/* ग_लिखो in one transfer to aव्योम data inconsistency */
	ret = spi_ग_लिखो_then_पढ़ो(spi, txbuf, माप(txbuf), शून्य, 0);
	udelay(62);	/* Tcsr 62us */
	वापस ret;
पूर्ण

अटल पूर्णांक
rs5c348_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा rs5c348_plat_data *pdata = dev_get_platdata(&spi->dev);
	u8 txbuf[5], rxbuf[7];
	पूर्णांक ret;

	ret = spi_w8r8(spi, RS5C348_CMD_R(RS5C348_REG_CTL2));
	अगर (ret < 0)
		वापस ret;
	अगर (ret & RS5C348_BIT_VDET)
		dev_warn(&spi->dev, "voltage-low detected.\n");
	अगर (ret & RS5C348_BIT_XSTP) अणु
		dev_warn(&spi->dev, "oscillator-stop detected.\n");
		वापस -EINVAL;
	पूर्ण

	/* Transfer 5 byte beक्रमes पढ़ोing SEC.  This gives 31us क्रम carry. */
	txbuf[0] = RS5C348_CMD_R(RS5C348_REG_CTL2); /* cmd, ctl2 */
	txbuf[1] = 0;	/* dummy */
	txbuf[2] = RS5C348_CMD_R(RS5C348_REG_CTL2); /* cmd, ctl2 */
	txbuf[3] = 0;	/* dummy */
	txbuf[4] = RS5C348_CMD_MR(RS5C348_REG_SECS); /* cmd, sec, ... */

	/* पढ़ो in one transfer to aव्योम data inconsistency */
	ret = spi_ग_लिखो_then_पढ़ो(spi, txbuf, माप(txbuf),
				  rxbuf, माप(rxbuf));
	udelay(62);	/* Tcsr 62us */
	अगर (ret < 0)
		वापस ret;

	पंचांग->पंचांग_sec = bcd2bin(rxbuf[RS5C348_REG_SECS] & RS5C348_SECS_MASK);
	पंचांग->पंचांग_min = bcd2bin(rxbuf[RS5C348_REG_MINS] & RS5C348_MINS_MASK);
	पंचांग->पंचांग_hour = bcd2bin(rxbuf[RS5C348_REG_HOURS] & RS5C348_HOURS_MASK);
	अगर (!pdata->rtc_24h) अणु
		अगर (rxbuf[RS5C348_REG_HOURS] & RS5C348_BIT_PM) अणु
			पंचांग->पंचांग_hour -= 20;
			पंचांग->पंचांग_hour %= 12;
			पंचांग->पंचांग_hour += 12;
		पूर्ण अन्यथा
			पंचांग->पंचांग_hour %= 12;
	पूर्ण
	पंचांग->पंचांग_wday = bcd2bin(rxbuf[RS5C348_REG_WDAY] & RS5C348_WDAY_MASK);
	पंचांग->पंचांग_mday = bcd2bin(rxbuf[RS5C348_REG_DAY] & RS5C348_DAY_MASK);
	पंचांग->पंचांग_mon =
		bcd2bin(rxbuf[RS5C348_REG_MONTH] & RS5C348_MONTH_MASK) - 1;
	/* year is 1900 + पंचांग->पंचांग_year */
	पंचांग->पंचांग_year = bcd2bin(rxbuf[RS5C348_REG_YEAR]) +
		((rxbuf[RS5C348_REG_MONTH] & RS5C348_BIT_Y2K) ? 100 : 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rs5c348_rtc_ops = अणु
	.पढ़ो_समय	= rs5c348_rtc_पढ़ो_समय,
	.set_समय	= rs5c348_rtc_set_समय,
पूर्ण;

अटल पूर्णांक rs5c348_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा rtc_device *rtc;
	काष्ठा rs5c348_plat_data *pdata;

	pdata = devm_kzalloc(&spi->dev, माप(काष्ठा rs5c348_plat_data),
				GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;
	spi->dev.platक्रमm_data = pdata;

	/* Check D7 of SECOND रेजिस्टर */
	ret = spi_w8r8(spi, RS5C348_CMD_R(RS5C348_REG_SECS));
	अगर (ret < 0 || (ret & 0x80)) अणु
		dev_err(&spi->dev, "not found.\n");
		वापस ret;
	पूर्ण

	dev_info(&spi->dev, "spiclk %u KHz.\n",
		 (spi->max_speed_hz + 500) / 1000);

	ret = spi_w8r8(spi, RS5C348_CMD_R(RS5C348_REG_CTL1));
	अगर (ret < 0)
		वापस ret;
	अगर (ret & RS5C348_BIT_24H)
		pdata->rtc_24h = 1;

	rtc = devm_rtc_allocate_device(&spi->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	pdata->rtc = rtc;

	rtc->ops = &rs5c348_rtc_ops;

	वापस devm_rtc_रेजिस्टर_device(rtc);
पूर्ण

अटल काष्ठा spi_driver rs5c348_driver = अणु
	.driver = अणु
		.name	= "rtc-rs5c348",
	पूर्ण,
	.probe	= rs5c348_probe,
पूर्ण;

module_spi_driver(rs5c348_driver);

MODULE_AUTHOR("Atsushi Nemoto <anemo@mba.ocn.ne.jp>");
MODULE_DESCRIPTION("Ricoh RS5C348 RTC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:rtc-rs5c348");
