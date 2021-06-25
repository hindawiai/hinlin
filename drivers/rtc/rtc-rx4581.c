<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/rtc/rtc-rx4581.c
 *
 * written by Torben Hohn <torbenh@linutronix.de>
 *
 * Based on:
 * drivers/rtc/rtc-max6902.c
 *
 * Copyright (C) 2006 8D Technologies inc.
 * Copyright (C) 2004 Compulab Ltd.
 *
 * Driver क्रम MAX6902 spi RTC
 *
 * and based on:
 * drivers/rtc/rtc-rx8581.c
 *
 * An I2C driver क्रम the Epson RX8581 RTC
 *
 * Author: Martyn Welch <martyn.welch@ge.com>
 * Copyright 2008 GE Intelligent Platक्रमms Embedded Systems, Inc.
 *
 * Based on: rtc-pcf8563.c (An I2C driver क्रम the Philips PCF8563 RTC)
 * Copyright 2005-06 Tower Technologies
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/rtc.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/bcd.h>

#घोषणा RX4581_REG_SC		0x00 /* Second in BCD */
#घोषणा RX4581_REG_MN		0x01 /* Minute in BCD */
#घोषणा RX4581_REG_HR		0x02 /* Hour in BCD */
#घोषणा RX4581_REG_DW		0x03 /* Day of Week */
#घोषणा RX4581_REG_DM		0x04 /* Day of Month in BCD */
#घोषणा RX4581_REG_MO		0x05 /* Month in BCD */
#घोषणा RX4581_REG_YR		0x06 /* Year in BCD */
#घोषणा RX4581_REG_RAM		0x07 /* RAM */
#घोषणा RX4581_REG_AMN		0x08 /* Alarm Min in BCD*/
#घोषणा RX4581_REG_AHR		0x09 /* Alarm Hour in BCD */
#घोषणा RX4581_REG_ADM		0x0A
#घोषणा RX4581_REG_ADW		0x0A
#घोषणा RX4581_REG_TMR0		0x0B
#घोषणा RX4581_REG_TMR1		0x0C
#घोषणा RX4581_REG_EXT		0x0D /* Extension Register */
#घोषणा RX4581_REG_FLAG		0x0E /* Flag Register */
#घोषणा RX4581_REG_CTRL		0x0F /* Control Register */


/* Flag Register bit definitions */
#घोषणा RX4581_FLAG_UF		0x20 /* Update */
#घोषणा RX4581_FLAG_TF		0x10 /* Timer */
#घोषणा RX4581_FLAG_AF		0x08 /* Alarm */
#घोषणा RX4581_FLAG_VLF		0x02 /* Voltage Low */

/* Control Register bit definitions */
#घोषणा RX4581_CTRL_UIE		0x20 /* Update Interrupt Enable */
#घोषणा RX4581_CTRL_TIE		0x10 /* Timer Interrupt Enable */
#घोषणा RX4581_CTRL_AIE		0x08 /* Alarm Interrupt Enable */
#घोषणा RX4581_CTRL_STOP	0x02 /* STOP bit */
#घोषणा RX4581_CTRL_RESET	0x01 /* RESET bit */

अटल पूर्णांक rx4581_set_reg(काष्ठा device *dev, अचिन्हित अक्षर address,
				अचिन्हित अक्षर data)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	अचिन्हित अक्षर buf[2];

	/* high nibble must be '0' to ग_लिखो */
	buf[0] = address & 0x0f;
	buf[1] = data;

	वापस spi_ग_लिखो_then_पढ़ो(spi, buf, 2, शून्य, 0);
पूर्ण

अटल पूर्णांक rx4581_get_reg(काष्ठा device *dev, अचिन्हित अक्षर address,
				अचिन्हित अक्षर *data)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);

	/* Set MSB to indicate पढ़ो */
	*data = address | 0x80;

	वापस spi_ग_लिखो_then_पढ़ो(spi, data, 1, data, 1);
पूर्ण

/*
 * In the routines that deal directly with the rx8581 hardware, we use
 * rtc_समय -- month 0-11, hour 0-23, yr = calendar year-epoch.
 */
अटल पूर्णांक rx4581_get_dateसमय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	अचिन्हित अक्षर date[7];
	अचिन्हित अक्षर data;
	पूर्णांक err;

	/* First we ensure that the "update flag" is not set, we पढ़ो the
	 * समय and date then re-पढ़ो the "update flag". If the update flag
	 * has been set, we know that the समय has changed during the पढ़ो so
	 * we repeat the whole process again.
	 */
	err = rx4581_get_reg(dev, RX4581_REG_FLAG, &data);
	अगर (err != 0) अणु
		dev_err(dev, "Unable to read device flags\n");
		वापस -EIO;
	पूर्ण

	करो अणु
		/* If update flag set, clear it */
		अगर (data & RX4581_FLAG_UF) अणु
			err = rx4581_set_reg(dev,
				RX4581_REG_FLAG, (data & ~RX4581_FLAG_UF));
			अगर (err != 0) अणु
				dev_err(dev, "Unable to write device "
					"flags\n");
				वापस -EIO;
			पूर्ण
		पूर्ण

		/* Now पढ़ो समय and date */
		date[0] = 0x80;
		err = spi_ग_लिखो_then_पढ़ो(spi, date, 1, date, 7);
		अगर (err < 0) अणु
			dev_err(dev, "Unable to read date\n");
			वापस -EIO;
		पूर्ण

		/* Check flag रेजिस्टर */
		err = rx4581_get_reg(dev, RX4581_REG_FLAG, &data);
		अगर (err != 0) अणु
			dev_err(dev, "Unable to read device flags\n");
			वापस -EIO;
		पूर्ण
	पूर्ण जबतक (data & RX4581_FLAG_UF);

	अगर (data & RX4581_FLAG_VLF)
		dev_info(dev,
			"low voltage detected, date/time is not reliable.\n");

	dev_dbg(dev,
		"%s: raw data is sec=%02x, min=%02x, hr=%02x, "
		"wday=%02x, mday=%02x, mon=%02x, year=%02x\n",
		__func__,
		date[0], date[1], date[2], date[3], date[4], date[5], date[6]);

	पंचांग->पंचांग_sec = bcd2bin(date[RX4581_REG_SC] & 0x7F);
	पंचांग->पंचांग_min = bcd2bin(date[RX4581_REG_MN] & 0x7F);
	पंचांग->पंचांग_hour = bcd2bin(date[RX4581_REG_HR] & 0x3F); /* rtc hr 0-23 */
	पंचांग->पंचांग_wday = ilog2(date[RX4581_REG_DW] & 0x7F);
	पंचांग->पंचांग_mday = bcd2bin(date[RX4581_REG_DM] & 0x3F);
	पंचांग->पंचांग_mon = bcd2bin(date[RX4581_REG_MO] & 0x1F) - 1; /* rtc mn 1-12 */
	पंचांग->पंचांग_year = bcd2bin(date[RX4581_REG_YR]);
	अगर (पंचांग->पंचांग_year < 70)
		पंचांग->पंचांग_year += 100;	/* assume we are in 1970...2069 */


	dev_dbg(dev, "%s: tm is secs=%d, mins=%d, hours=%d, "
		"mday=%d, mon=%d, year=%d, wday=%d\n",
		__func__,
		पंचांग->पंचांग_sec, पंचांग->पंचांग_min, पंचांग->पंचांग_hour,
		पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	वापस 0;
पूर्ण

अटल पूर्णांक rx4581_set_dateसमय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	पूर्णांक err;
	अचिन्हित अक्षर buf[8], data;

	dev_dbg(dev, "%s: secs=%d, mins=%d, hours=%d, "
		"mday=%d, mon=%d, year=%d, wday=%d\n",
		__func__,
		पंचांग->पंचांग_sec, पंचांग->पंचांग_min, पंचांग->पंचांग_hour,
		पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	buf[0] = 0x00;
	/* hours, minutes and seconds */
	buf[RX4581_REG_SC+1] = bin2bcd(पंचांग->पंचांग_sec);
	buf[RX4581_REG_MN+1] = bin2bcd(पंचांग->पंचांग_min);
	buf[RX4581_REG_HR+1] = bin2bcd(पंचांग->पंचांग_hour);

	buf[RX4581_REG_DM+1] = bin2bcd(पंचांग->पंचांग_mday);

	/* month, 1 - 12 */
	buf[RX4581_REG_MO+1] = bin2bcd(पंचांग->पंचांग_mon + 1);

	/* year and century */
	buf[RX4581_REG_YR+1] = bin2bcd(पंचांग->पंचांग_year % 100);
	buf[RX4581_REG_DW+1] = (0x1 << पंचांग->पंचांग_wday);

	/* Stop the घड़ी */
	err = rx4581_get_reg(dev, RX4581_REG_CTRL, &data);
	अगर (err != 0) अणु
		dev_err(dev, "Unable to read control register\n");
		वापस -EIO;
	पूर्ण

	err = rx4581_set_reg(dev, RX4581_REG_CTRL,
		(data | RX4581_CTRL_STOP));
	अगर (err != 0) अणु
		dev_err(dev, "Unable to write control register\n");
		वापस -EIO;
	पूर्ण

	/* ग_लिखो रेजिस्टर's data */
	err = spi_ग_लिखो_then_पढ़ो(spi, buf, 8, शून्य, 0);
	अगर (err != 0) अणु
		dev_err(dev, "Unable to write to date registers\n");
		वापस -EIO;
	पूर्ण

	/* get VLF and clear it */
	err = rx4581_get_reg(dev, RX4581_REG_FLAG, &data);
	अगर (err != 0) अणु
		dev_err(dev, "Unable to read flag register\n");
		वापस -EIO;
	पूर्ण

	err = rx4581_set_reg(dev, RX4581_REG_FLAG,
		(data & ~(RX4581_FLAG_VLF)));
	अगर (err != 0) अणु
		dev_err(dev, "Unable to write flag register\n");
		वापस -EIO;
	पूर्ण

	/* Restart the घड़ी */
	err = rx4581_get_reg(dev, RX4581_REG_CTRL, &data);
	अगर (err != 0) अणु
		dev_err(dev, "Unable to read control register\n");
		वापस -EIO;
	पूर्ण

	err = rx4581_set_reg(dev, RX4581_REG_CTRL,
		(data & ~(RX4581_CTRL_STOP)));
	अगर (err != 0) अणु
		dev_err(dev, "Unable to write control register\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rx4581_rtc_ops = अणु
	.पढ़ो_समय	= rx4581_get_dateसमय,
	.set_समय	= rx4581_set_dateसमय,
पूर्ण;

अटल पूर्णांक rx4581_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा rtc_device *rtc;
	अचिन्हित अक्षर पंचांगp;
	पूर्णांक res;

	res = rx4581_get_reg(&spi->dev, RX4581_REG_SC, &पंचांगp);
	अगर (res != 0)
		वापस res;

	rtc = devm_rtc_device_रेजिस्टर(&spi->dev, "rx4581",
				&rx4581_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	spi_set_drvdata(spi, rtc);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id rx4581_id[] = अणु
	अणु "rx4581", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, rx4581_id);

अटल काष्ठा spi_driver rx4581_driver = अणु
	.driver = अणु
		.name	= "rtc-rx4581",
	पूर्ण,
	.probe	= rx4581_probe,
	.id_table = rx4581_id,
पूर्ण;

module_spi_driver(rx4581_driver);

MODULE_DESCRIPTION("rx4581 spi RTC driver");
MODULE_AUTHOR("Torben Hohn");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:rtc-rx4581");
