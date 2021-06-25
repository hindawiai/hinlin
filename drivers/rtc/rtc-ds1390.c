<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rtc-ds1390.c -- driver क्रम the Dallas/Maxim DS1390/93/94 SPI RTC
 *
 * Copyright (C) 2008 Mercury IMC Ltd
 * Written by Mark Jackson <mpfj@mimc.co.uk>
 *
 * NOTE: Currently this driver only supports the bare minimum क्रम पढ़ो
 * and ग_लिखो the RTC. The extra features provided by the chip family
 * (alarms, trickle अक्षरger, dअगरferent control रेजिस्टरs) are unavailable.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/bcd.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

#घोषणा DS1390_REG_100THS		0x00
#घोषणा DS1390_REG_SECONDS		0x01
#घोषणा DS1390_REG_MINUTES		0x02
#घोषणा DS1390_REG_HOURS		0x03
#घोषणा DS1390_REG_DAY			0x04
#घोषणा DS1390_REG_DATE			0x05
#घोषणा DS1390_REG_MONTH_CENT		0x06
#घोषणा DS1390_REG_YEAR			0x07

#घोषणा DS1390_REG_ALARM_100THS		0x08
#घोषणा DS1390_REG_ALARM_SECONDS	0x09
#घोषणा DS1390_REG_ALARM_MINUTES	0x0A
#घोषणा DS1390_REG_ALARM_HOURS		0x0B
#घोषणा DS1390_REG_ALARM_DAY_DATE	0x0C

#घोषणा DS1390_REG_CONTROL		0x0D
#घोषणा DS1390_REG_STATUS		0x0E
#घोषणा DS1390_REG_TRICKLE		0x0F

#घोषणा DS1390_TRICKLE_CHARGER_ENABLE	0xA0
#घोषणा DS1390_TRICKLE_CHARGER_250_OHM	0x01
#घोषणा DS1390_TRICKLE_CHARGER_2K_OHM	0x02
#घोषणा DS1390_TRICKLE_CHARGER_4K_OHM	0x03
#घोषणा DS1390_TRICKLE_CHARGER_NO_DIODE	0x04
#घोषणा DS1390_TRICKLE_CHARGER_DIODE	0x08

काष्ठा ds1390 अणु
	काष्ठा rtc_device *rtc;
	u8 txrx_buf[9];	/* cmd + 8 रेजिस्टरs */
पूर्ण;

अटल व्योम ds1390_set_reg(काष्ठा device *dev, अचिन्हित अक्षर address,
			   अचिन्हित अक्षर data)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	अचिन्हित अक्षर buf[2];

	/* MSB must be '1' to ग_लिखो */
	buf[0] = address | 0x80;
	buf[1] = data;

	spi_ग_लिखो(spi, buf, 2);
पूर्ण

अटल पूर्णांक ds1390_get_reg(काष्ठा device *dev, अचिन्हित अक्षर address,
				अचिन्हित अक्षर *data)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा ds1390 *chip = dev_get_drvdata(dev);
	पूर्णांक status;

	अगर (!data)
		वापस -EINVAL;

	/* Clear MSB to indicate पढ़ो */
	chip->txrx_buf[0] = address & 0x7f;
	/* करो the i/o */
	status = spi_ग_लिखो_then_पढ़ो(spi, chip->txrx_buf, 1, chip->txrx_buf, 1);
	अगर (status != 0)
		वापस status;

	*data = chip->txrx_buf[0];

	वापस 0;
पूर्ण

अटल व्योम ds1390_trickle_of_init(काष्ठा spi_device *spi)
अणु
	u32 ohms = 0;
	u8 value;

	अगर (of_property_पढ़ो_u32(spi->dev.of_node, "trickle-resistor-ohms",
				 &ohms))
		जाओ out;

	/* Enable अक्षरger */
	value = DS1390_TRICKLE_CHARGER_ENABLE;
	अगर (of_property_पढ़ो_bool(spi->dev.of_node, "trickle-diode-disable"))
		value |= DS1390_TRICKLE_CHARGER_NO_DIODE;
	अन्यथा
		value |= DS1390_TRICKLE_CHARGER_DIODE;

	/* Resistor select */
	चयन (ohms) अणु
	हाल 250:
		value |= DS1390_TRICKLE_CHARGER_250_OHM;
		अवरोध;
	हाल 2000:
		value |= DS1390_TRICKLE_CHARGER_2K_OHM;
		अवरोध;
	हाल 4000:
		value |= DS1390_TRICKLE_CHARGER_4K_OHM;
		अवरोध;
	शेष:
		dev_warn(&spi->dev,
			 "Unsupported ohm value %02ux in dt\n", ohms);
		वापस;
	पूर्ण

	ds1390_set_reg(&spi->dev, DS1390_REG_TRICKLE, value);

out:
	वापस;
पूर्ण

अटल पूर्णांक ds1390_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा ds1390 *chip = dev_get_drvdata(dev);
	पूर्णांक status;

	/* build the message */
	chip->txrx_buf[0] = DS1390_REG_SECONDS;

	/* करो the i/o */
	status = spi_ग_लिखो_then_पढ़ो(spi, chip->txrx_buf, 1, chip->txrx_buf, 8);
	अगर (status != 0)
		वापस status;

	/* The chip sends data in this order:
	 * Seconds, Minutes, Hours, Day, Date, Month / Century, Year */
	dt->पंचांग_sec	= bcd2bin(chip->txrx_buf[0]);
	dt->पंचांग_min	= bcd2bin(chip->txrx_buf[1]);
	dt->पंचांग_hour	= bcd2bin(chip->txrx_buf[2]);
	dt->पंचांग_wday	= bcd2bin(chip->txrx_buf[3]);
	dt->पंचांग_mday	= bcd2bin(chip->txrx_buf[4]);
	/* mask off century bit */
	dt->पंचांग_mon	= bcd2bin(chip->txrx_buf[5] & 0x7f) - 1;
	/* adjust क्रम century bit */
	dt->पंचांग_year = bcd2bin(chip->txrx_buf[6]) + ((chip->txrx_buf[5] & 0x80) ? 100 : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ds1390_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा ds1390 *chip = dev_get_drvdata(dev);

	/* build the message */
	chip->txrx_buf[0] = DS1390_REG_SECONDS | 0x80;
	chip->txrx_buf[1] = bin2bcd(dt->पंचांग_sec);
	chip->txrx_buf[2] = bin2bcd(dt->पंचांग_min);
	chip->txrx_buf[3] = bin2bcd(dt->पंचांग_hour);
	chip->txrx_buf[4] = bin2bcd(dt->पंचांग_wday);
	chip->txrx_buf[5] = bin2bcd(dt->पंचांग_mday);
	chip->txrx_buf[6] = bin2bcd(dt->पंचांग_mon + 1) |
				((dt->पंचांग_year > 99) ? 0x80 : 0x00);
	chip->txrx_buf[7] = bin2bcd(dt->पंचांग_year % 100);

	/* करो the i/o */
	वापस spi_ग_लिखो_then_पढ़ो(spi, chip->txrx_buf, 8, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ds1390_rtc_ops = अणु
	.पढ़ो_समय	= ds1390_पढ़ो_समय,
	.set_समय	= ds1390_set_समय,
पूर्ण;

अटल पूर्णांक ds1390_probe(काष्ठा spi_device *spi)
अणु
	अचिन्हित अक्षर पंचांगp;
	काष्ठा ds1390 *chip;
	पूर्णांक res;

	spi->mode = SPI_MODE_3;
	spi->bits_per_word = 8;
	spi_setup(spi);

	chip = devm_kzalloc(&spi->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	spi_set_drvdata(spi, chip);

	res = ds1390_get_reg(&spi->dev, DS1390_REG_SECONDS, &पंचांगp);
	अगर (res != 0) अणु
		dev_err(&spi->dev, "unable to read device\n");
		वापस res;
	पूर्ण

	अगर (spi->dev.of_node)
		ds1390_trickle_of_init(spi);

	chip->rtc = devm_rtc_device_रेजिस्टर(&spi->dev, "ds1390",
					&ds1390_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(chip->rtc)) अणु
		dev_err(&spi->dev, "unable to register device\n");
		res = PTR_ERR(chip->rtc);
	पूर्ण

	वापस res;
पूर्ण

अटल स्थिर काष्ठा of_device_id ds1390_of_match[] = अणु
	अणु .compatible = "dallas,ds1390" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ds1390_of_match);

अटल काष्ठा spi_driver ds1390_driver = अणु
	.driver = अणु
		.name	= "rtc-ds1390",
		.of_match_table = of_match_ptr(ds1390_of_match),
	पूर्ण,
	.probe	= ds1390_probe,
पूर्ण;

module_spi_driver(ds1390_driver);

MODULE_DESCRIPTION("Dallas/Maxim DS1390/93/94 SPI RTC driver");
MODULE_AUTHOR("Mark Jackson <mpfj@mimc.co.uk>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:rtc-ds1390");
