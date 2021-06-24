<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* rtc-ds1347.c
 *
 * Driver क्रम Dallas Semiconductor DS1347 Low Current, SPI Compatible
 * Real Time Clock
 *
 * Author : Raghavendra Chandra Ganiga <ravi23ganiga@gmail.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/bcd.h>
#समावेश <linux/regmap.h>

/* Registers in ds1347 rtc */

#घोषणा DS1347_SECONDS_REG	0x01
#घोषणा DS1347_MINUTES_REG	0x03
#घोषणा DS1347_HOURS_REG	0x05
#घोषणा DS1347_DATE_REG		0x07
#घोषणा DS1347_MONTH_REG	0x09
#घोषणा DS1347_DAY_REG		0x0B
#घोषणा DS1347_YEAR_REG		0x0D
#घोषणा DS1347_CONTROL_REG	0x0F
#घोषणा DS1347_CENTURY_REG	0x13
#घोषणा DS1347_STATUS_REG	0x17
#घोषणा DS1347_CLOCK_BURST	0x3F

#घोषणा DS1347_WP_BIT		BIT(7)

#घोषणा DS1347_NEOSC_BIT	BIT(7)
#घोषणा DS1347_OSF_BIT		BIT(2)

अटल स्थिर काष्ठा regmap_range ds1347_ranges[] = अणु
	अणु
		.range_min = DS1347_SECONDS_REG,
		.range_max = DS1347_STATUS_REG,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table ds1347_access_table = अणु
	.yes_ranges = ds1347_ranges,
	.n_yes_ranges = ARRAY_SIZE(ds1347_ranges),
पूर्ण;

अटल पूर्णांक ds1347_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	काष्ठा regmap *map = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक status, century, secs;
	अचिन्हित अक्षर buf[8];
	पूर्णांक err;

	err = regmap_पढ़ो(map, DS1347_STATUS_REG, &status);
	अगर (err)
		वापस err;

	अगर (status & DS1347_OSF_BIT)
		वापस -EINVAL;

	करो अणु
		err = regmap_bulk_पढ़ो(map, DS1347_CLOCK_BURST, buf, 8);
		अगर (err)
			वापस err;

		err = regmap_पढ़ो(map, DS1347_CENTURY_REG, &century);
		अगर (err)
			वापस err;

		err = regmap_पढ़ो(map, DS1347_SECONDS_REG, &secs);
		अगर (err)
			वापस err;
	पूर्ण जबतक (buf[0] != secs);

	dt->पंचांग_sec = bcd2bin(buf[0]);
	dt->पंचांग_min = bcd2bin(buf[1] & 0x7f);
	dt->पंचांग_hour = bcd2bin(buf[2] & 0x3F);
	dt->पंचांग_mday = bcd2bin(buf[3]);
	dt->पंचांग_mon = bcd2bin(buf[4]) - 1;
	dt->पंचांग_wday = bcd2bin(buf[5]) - 1;
	dt->पंचांग_year = (bcd2bin(century) * 100) + bcd2bin(buf[6]) - 1900;

	वापस 0;
पूर्ण

अटल पूर्णांक ds1347_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	काष्ठा regmap *map = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक century;
	अचिन्हित अक्षर buf[8];
	पूर्णांक err;

	err = regmap_update_bits(map, DS1347_STATUS_REG,
				 DS1347_NEOSC_BIT, DS1347_NEOSC_BIT);
	अगर (err)
		वापस err;

	buf[0] = bin2bcd(dt->पंचांग_sec);
	buf[1] = bin2bcd(dt->पंचांग_min);
	buf[2] = (bin2bcd(dt->पंचांग_hour) & 0x3F);
	buf[3] = bin2bcd(dt->पंचांग_mday);
	buf[4] = bin2bcd(dt->पंचांग_mon + 1);
	buf[5] = bin2bcd(dt->पंचांग_wday + 1);
	buf[6] = bin2bcd(dt->पंचांग_year % 100);
	buf[7] = bin2bcd(0x00);

	err = regmap_bulk_ग_लिखो(map, DS1347_CLOCK_BURST, buf, 8);
	अगर (err)
		वापस err;

	century = (dt->पंचांग_year / 100) + 19;
	err = regmap_ग_लिखो(map, DS1347_CENTURY_REG, century);
	अगर (err)
		वापस err;

	वापस regmap_update_bits(map, DS1347_STATUS_REG,
				  DS1347_NEOSC_BIT | DS1347_OSF_BIT, 0);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ds1347_rtc_ops = अणु
	.पढ़ो_समय = ds1347_पढ़ो_समय,
	.set_समय = ds1347_set_समय,
पूर्ण;

अटल पूर्णांक ds1347_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा rtc_device *rtc;
	काष्ठा regmap_config config;
	काष्ठा regmap *map;
	पूर्णांक err;

	स_रखो(&config, 0, माप(config));
	config.reg_bits = 8;
	config.val_bits = 8;
	config.पढ़ो_flag_mask = 0x80;
	config.max_रेजिस्टर = 0x3F;
	config.wr_table = &ds1347_access_table;

	/* spi setup with ds1347 in mode 3 and bits per word as 8 */
	spi->mode = SPI_MODE_3;
	spi->bits_per_word = 8;
	spi_setup(spi);

	map = devm_regmap_init_spi(spi, &config);

	अगर (IS_ERR(map)) अणु
		dev_err(&spi->dev, "ds1347 regmap init spi failed\n");
		वापस PTR_ERR(map);
	पूर्ण

	spi_set_drvdata(spi, map);

	/* Disable the ग_लिखो protect of rtc */
	err = regmap_update_bits(map, DS1347_CONTROL_REG, DS1347_WP_BIT, 0);
	अगर (err)
		वापस err;

	rtc = devm_rtc_allocate_device(&spi->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	rtc->ops = &ds1347_rtc_ops;
	rtc->range_min = RTC_TIMESTAMP_BEGIN_0000;
	rtc->range_max = RTC_TIMESTAMP_END_9999;

	वापस devm_rtc_रेजिस्टर_device(rtc);
पूर्ण

अटल काष्ठा spi_driver ds1347_driver = अणु
	.driver = अणु
		.name = "ds1347",
	पूर्ण,
	.probe = ds1347_probe,
पूर्ण;

module_spi_driver(ds1347_driver);

MODULE_DESCRIPTION("DS1347 SPI RTC DRIVER");
MODULE_AUTHOR("Raghavendra C Ganiga <ravi23ganiga@gmail.com>");
MODULE_LICENSE("GPL v2");
