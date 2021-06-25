<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Epson RTC module RX-6110 SA
 *
 * Copyright(C) 2015 Pengutronix, Steffen Trumtrar <kernel@pengutronix.de>
 * Copyright(C) SEIKO EPSON CORPORATION 2013. All rights reserved.
 */

#समावेश <linux/bcd.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/i2c.h>

/* RX-6110 Register definitions */
#घोषणा RX6110_REG_SEC		0x10
#घोषणा RX6110_REG_MIN		0x11
#घोषणा RX6110_REG_HOUR		0x12
#घोषणा RX6110_REG_WDAY		0x13
#घोषणा RX6110_REG_MDAY		0x14
#घोषणा RX6110_REG_MONTH	0x15
#घोषणा RX6110_REG_YEAR		0x16
#घोषणा RX6110_REG_RES1		0x17
#घोषणा RX6110_REG_ALMIN	0x18
#घोषणा RX6110_REG_ALHOUR	0x19
#घोषणा RX6110_REG_ALWDAY	0x1A
#घोषणा RX6110_REG_TCOUNT0	0x1B
#घोषणा RX6110_REG_TCOUNT1	0x1C
#घोषणा RX6110_REG_EXT		0x1D
#घोषणा RX6110_REG_FLAG		0x1E
#घोषणा RX6110_REG_CTRL		0x1F
#घोषणा RX6110_REG_USER0	0x20
#घोषणा RX6110_REG_USER1	0x21
#घोषणा RX6110_REG_USER2	0x22
#घोषणा RX6110_REG_USER3	0x23
#घोषणा RX6110_REG_USER4	0x24
#घोषणा RX6110_REG_USER5	0x25
#घोषणा RX6110_REG_USER6	0x26
#घोषणा RX6110_REG_USER7	0x27
#घोषणा RX6110_REG_USER8	0x28
#घोषणा RX6110_REG_USER9	0x29
#घोषणा RX6110_REG_USERA	0x2A
#घोषणा RX6110_REG_USERB	0x2B
#घोषणा RX6110_REG_USERC	0x2C
#घोषणा RX6110_REG_USERD	0x2D
#घोषणा RX6110_REG_USERE	0x2E
#घोषणा RX6110_REG_USERF	0x2F
#घोषणा RX6110_REG_RES2		0x30
#घोषणा RX6110_REG_RES3		0x31
#घोषणा RX6110_REG_IRQ		0x32

#घोषणा RX6110_BIT_ALARM_EN		BIT(7)

/* Extension Register (1Dh) bit positions */
#घोषणा RX6110_BIT_EXT_TSEL0		BIT(0)
#घोषणा RX6110_BIT_EXT_TSEL1		BIT(1)
#घोषणा RX6110_BIT_EXT_TSEL2		BIT(2)
#घोषणा RX6110_BIT_EXT_WADA		BIT(3)
#घोषणा RX6110_BIT_EXT_TE		BIT(4)
#घोषणा RX6110_BIT_EXT_USEL		BIT(5)
#घोषणा RX6110_BIT_EXT_FSEL0		BIT(6)
#घोषणा RX6110_BIT_EXT_FSEL1		BIT(7)

/* Flag Register (1Eh) bit positions */
#घोषणा RX6110_BIT_FLAG_VLF		BIT(1)
#घोषणा RX6110_BIT_FLAG_AF		BIT(3)
#घोषणा RX6110_BIT_FLAG_TF		BIT(4)
#घोषणा RX6110_BIT_FLAG_UF		BIT(5)

/* Control Register (1Fh) bit positions */
#घोषणा RX6110_BIT_CTRL_TBKE		BIT(0)
#घोषणा RX6110_BIT_CTRL_TBKON		BIT(1)
#घोषणा RX6110_BIT_CTRL_TSTP		BIT(2)
#घोषणा RX6110_BIT_CTRL_AIE		BIT(3)
#घोषणा RX6110_BIT_CTRL_TIE		BIT(4)
#घोषणा RX6110_BIT_CTRL_UIE		BIT(5)
#घोषणा RX6110_BIT_CTRL_STOP		BIT(6)
#घोषणा RX6110_BIT_CTRL_TEST		BIT(7)

क्रमागत अणु
	RTC_SEC = 0,
	RTC_MIN,
	RTC_HOUR,
	RTC_WDAY,
	RTC_MDAY,
	RTC_MONTH,
	RTC_YEAR,
	RTC_NR_TIME
पूर्ण;

#घोषणा RX6110_DRIVER_NAME		"rx6110"

काष्ठा rx6110_data अणु
	काष्ठा rtc_device *rtc;
	काष्ठा regmap *regmap;
पूर्ण;

/**
 * rx6110_rtc_पंचांग_to_data - convert rtc_समय to native समय encoding
 *
 * @पंचांग: holds date and समय
 * @data: holds the encoding in rx6110 native क्रमm
 */
अटल पूर्णांक rx6110_rtc_पंचांग_to_data(काष्ठा rtc_समय *पंचांग, u8 *data)
अणु
	pr_debug("%s: date %ptRr\n", __func__, पंचांग);

	/*
	 * The year in the RTC is a value between 0 and 99.
	 * Assume that this represents the current century
	 * and disregard all other values.
	 */
	अगर (पंचांग->पंचांग_year < 100 || पंचांग->पंचांग_year >= 200)
		वापस -EINVAL;

	data[RTC_SEC] = bin2bcd(पंचांग->पंचांग_sec);
	data[RTC_MIN] = bin2bcd(पंचांग->पंचांग_min);
	data[RTC_HOUR] = bin2bcd(पंचांग->पंचांग_hour);
	data[RTC_WDAY] = BIT(bin2bcd(पंचांग->पंचांग_wday));
	data[RTC_MDAY] = bin2bcd(पंचांग->पंचांग_mday);
	data[RTC_MONTH] = bin2bcd(पंचांग->पंचांग_mon + 1);
	data[RTC_YEAR] = bin2bcd(पंचांग->पंचांग_year % 100);

	वापस 0;
पूर्ण

/**
 * rx6110_data_to_rtc_पंचांग - convert native समय encoding to rtc_समय
 *
 * @data: holds the encoding in rx6110 native क्रमm
 * @पंचांग: holds date and समय
 */
अटल पूर्णांक rx6110_data_to_rtc_पंचांग(u8 *data, काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_sec = bcd2bin(data[RTC_SEC] & 0x7f);
	पंचांग->पंचांग_min = bcd2bin(data[RTC_MIN] & 0x7f);
	/* only 24-hour घड़ी */
	पंचांग->पंचांग_hour = bcd2bin(data[RTC_HOUR] & 0x3f);
	पंचांग->पंचांग_wday = ffs(data[RTC_WDAY] & 0x7f);
	पंचांग->पंचांग_mday = bcd2bin(data[RTC_MDAY] & 0x3f);
	पंचांग->पंचांग_mon = bcd2bin(data[RTC_MONTH] & 0x1f) - 1;
	पंचांग->पंचांग_year = bcd2bin(data[RTC_YEAR]) + 100;

	pr_debug("%s: date %ptRr\n", __func__, पंचांग);

	/*
	 * The year in the RTC is a value between 0 and 99.
	 * Assume that this represents the current century
	 * and disregard all other values.
	 */
	अगर (पंचांग->पंचांग_year < 100 || पंचांग->पंचांग_year >= 200)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * rx6110_set_समय - set the current समय in the rx6110 रेजिस्टरs
 *
 * @dev: the rtc device in use
 * @पंचांग: holds date and समय
 *
 * BUG: The HW assumes every year that is a multiple of 4 to be a leap
 * year. Next समय this is wrong is 2100, which will not be a leap year
 *
 * Note: If STOP is not set/cleared, the घड़ी will start when the seconds
 *       रेजिस्टर is written
 *
 */
अटल पूर्णांक rx6110_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rx6110_data *rx6110 = dev_get_drvdata(dev);
	u8 data[RTC_NR_TIME];
	पूर्णांक ret;

	ret = rx6110_rtc_पंचांग_to_data(पंचांग, data);
	अगर (ret < 0)
		वापस ret;

	/* set STOP bit beक्रमe changing घड़ी/calendar */
	ret = regmap_update_bits(rx6110->regmap, RX6110_REG_CTRL,
				 RX6110_BIT_CTRL_STOP, RX6110_BIT_CTRL_STOP);
	अगर (ret)
		वापस ret;

	ret = regmap_bulk_ग_लिखो(rx6110->regmap, RX6110_REG_SEC, data,
				RTC_NR_TIME);
	अगर (ret)
		वापस ret;

	/* The समय in the RTC is valid. Be sure to have VLF cleared. */
	ret = regmap_update_bits(rx6110->regmap, RX6110_REG_FLAG,
				 RX6110_BIT_FLAG_VLF, 0);
	अगर (ret)
		वापस ret;

	/* clear STOP bit after changing घड़ी/calendar */
	ret = regmap_update_bits(rx6110->regmap, RX6110_REG_CTRL,
				 RX6110_BIT_CTRL_STOP, 0);

	वापस ret;
पूर्ण

/**
 * rx6110_get_समय - get the current समय from the rx6110 रेजिस्टरs
 * @dev: the rtc device in use
 * @पंचांग: holds date and समय
 */
अटल पूर्णांक rx6110_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rx6110_data *rx6110 = dev_get_drvdata(dev);
	u8 data[RTC_NR_TIME];
	पूर्णांक flags;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rx6110->regmap, RX6110_REG_FLAG, &flags);
	अगर (ret)
		वापस -EINVAL;

	/* check क्रम VLF Flag (set at घातer-on) */
	अगर ((flags & RX6110_BIT_FLAG_VLF)) अणु
		dev_warn(dev, "Voltage low, data is invalid.\n");
		वापस -EINVAL;
	पूर्ण

	/* पढ़ो रेजिस्टरs to date */
	ret = regmap_bulk_पढ़ो(rx6110->regmap, RX6110_REG_SEC, data,
			       RTC_NR_TIME);
	अगर (ret)
		वापस ret;

	ret = rx6110_data_to_rtc_पंचांग(data, पंचांग);
	अगर (ret)
		वापस ret;

	dev_dbg(dev, "%s: date %ptRr\n", __func__, पंचांग);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reg_sequence rx6110_शेष_regs[] = अणु
	अणु RX6110_REG_RES1,   0xB8 पूर्ण,
	अणु RX6110_REG_RES2,   0x00 पूर्ण,
	अणु RX6110_REG_RES3,   0x10 पूर्ण,
	अणु RX6110_REG_IRQ,    0x00 पूर्ण,
	अणु RX6110_REG_ALMIN,  0x00 पूर्ण,
	अणु RX6110_REG_ALHOUR, 0x00 पूर्ण,
	अणु RX6110_REG_ALWDAY, 0x00 पूर्ण,
पूर्ण;

/**
 * rx6110_init - initialize the rx6110 रेजिस्टरs
 *
 * @rx6110: poपूर्णांकer to the rx6110 काष्ठा in use
 *
 */
अटल पूर्णांक rx6110_init(काष्ठा rx6110_data *rx6110)
अणु
	काष्ठा rtc_device *rtc = rx6110->rtc;
	पूर्णांक flags;
	पूर्णांक ret;

	ret = regmap_update_bits(rx6110->regmap, RX6110_REG_EXT,
				 RX6110_BIT_EXT_TE, 0);
	अगर (ret)
		वापस ret;

	ret = regmap_रेजिस्टर_patch(rx6110->regmap, rx6110_शेष_regs,
				    ARRAY_SIZE(rx6110_शेष_regs));
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(rx6110->regmap, RX6110_REG_FLAG, &flags);
	अगर (ret)
		वापस ret;

	/* check क्रम VLF Flag (set at घातer-on) */
	अगर ((flags & RX6110_BIT_FLAG_VLF))
		dev_warn(&rtc->dev, "Voltage low, data loss detected.\n");

	/* check क्रम Alarm Flag */
	अगर (flags & RX6110_BIT_FLAG_AF)
		dev_warn(&rtc->dev, "An alarm may have been missed.\n");

	/* check क्रम Periodic Timer Flag */
	अगर (flags & RX6110_BIT_FLAG_TF)
		dev_warn(&rtc->dev, "Periodic timer was detected\n");

	/* check क्रम Update Timer Flag */
	अगर (flags & RX6110_BIT_FLAG_UF)
		dev_warn(&rtc->dev, "Update timer was detected\n");

	/* clear all flags BUT VLF */
	ret = regmap_update_bits(rx6110->regmap, RX6110_REG_FLAG,
				 RX6110_BIT_FLAG_AF |
				 RX6110_BIT_FLAG_UF |
				 RX6110_BIT_FLAG_TF,
				 0);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rx6110_rtc_ops = अणु
	.पढ़ो_समय = rx6110_get_समय,
	.set_समय = rx6110_set_समय,
पूर्ण;

अटल पूर्णांक rx6110_probe(काष्ठा rx6110_data *rx6110, काष्ठा device *dev)
अणु
	पूर्णांक err;

	rx6110->rtc = devm_rtc_device_रेजिस्टर(dev,
					       RX6110_DRIVER_NAME,
					       &rx6110_rtc_ops, THIS_MODULE);

	अगर (IS_ERR(rx6110->rtc))
		वापस PTR_ERR(rx6110->rtc);

	err = rx6110_init(rx6110);
	अगर (err)
		वापस err;

	rx6110->rtc->max_user_freq = 1;

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_SPI_MASTER)
अटल काष्ठा regmap_config regmap_spi_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = RX6110_REG_IRQ,
	.पढ़ो_flag_mask = 0x80,
पूर्ण;

/**
 * rx6110_spi_probe - initialize rtc driver
 * @spi: poपूर्णांकer to spi device
 */
अटल पूर्णांक rx6110_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा rx6110_data *rx6110;

	अगर ((spi->bits_per_word && spi->bits_per_word != 8) ||
	    (spi->max_speed_hz > 2000000) ||
	    (spi->mode != (SPI_CS_HIGH | SPI_CPOL | SPI_CPHA))) अणु
		dev_warn(&spi->dev, "SPI settings: bits_per_word: %d, max_speed_hz: %d, mode: %xh\n",
			 spi->bits_per_word, spi->max_speed_hz, spi->mode);
		dev_warn(&spi->dev, "driving device in an unsupported mode");
	पूर्ण

	rx6110 = devm_kzalloc(&spi->dev, माप(*rx6110), GFP_KERNEL);
	अगर (!rx6110)
		वापस -ENOMEM;

	rx6110->regmap = devm_regmap_init_spi(spi, &regmap_spi_config);
	अगर (IS_ERR(rx6110->regmap)) अणु
		dev_err(&spi->dev, "regmap init failed for rtc rx6110\n");
		वापस PTR_ERR(rx6110->regmap);
	पूर्ण

	spi_set_drvdata(spi, rx6110);

	वापस rx6110_probe(rx6110, &spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id rx6110_spi_id[] = अणु
	अणु "rx6110", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, rx6110_spi_id);

अटल स्थिर काष्ठा of_device_id rx6110_spi_of_match[] = अणु
	अणु .compatible = "epson,rx6110" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rx6110_spi_of_match);

अटल काष्ठा spi_driver rx6110_spi_driver = अणु
	.driver = अणु
		.name = RX6110_DRIVER_NAME,
		.of_match_table = of_match_ptr(rx6110_spi_of_match),
	पूर्ण,
	.probe		= rx6110_spi_probe,
	.id_table	= rx6110_spi_id,
पूर्ण;

अटल पूर्णांक rx6110_spi_रेजिस्टर(व्योम)
अणु
	वापस spi_रेजिस्टर_driver(&rx6110_spi_driver);
पूर्ण

अटल व्योम rx6110_spi_unरेजिस्टर(व्योम)
अणु
	spi_unरेजिस्टर_driver(&rx6110_spi_driver);
पूर्ण
#अन्यथा
अटल पूर्णांक rx6110_spi_रेजिस्टर(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम rx6110_spi_unरेजिस्टर(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SPI_MASTER */

#अगर IS_ENABLED(CONFIG_I2C)
अटल काष्ठा regmap_config regmap_i2c_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = RX6110_REG_IRQ,
	.पढ़ो_flag_mask = 0x80,
पूर्ण;

अटल पूर्णांक rx6110_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	काष्ठा rx6110_data *rx6110;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA
				| I2C_FUNC_SMBUS_I2C_BLOCK)) अणु
		dev_err(&adapter->dev,
			"doesn't support required functionality\n");
		वापस -EIO;
	पूर्ण

	rx6110 = devm_kzalloc(&client->dev, माप(*rx6110), GFP_KERNEL);
	अगर (!rx6110)
		वापस -ENOMEM;

	rx6110->regmap = devm_regmap_init_i2c(client, &regmap_i2c_config);
	अगर (IS_ERR(rx6110->regmap)) अणु
		dev_err(&client->dev, "regmap init failed for rtc rx6110\n");
		वापस PTR_ERR(rx6110->regmap);
	पूर्ण

	i2c_set_clientdata(client, rx6110);

	वापस rx6110_probe(rx6110, &client->dev);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id rx6110_i2c_acpi_match[] = अणु
	अणु "SECC6110" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rx6110_i2c_acpi_match);

अटल स्थिर काष्ठा i2c_device_id rx6110_i2c_id[] = अणु
	अणु "rx6110", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rx6110_i2c_id);

अटल काष्ठा i2c_driver rx6110_i2c_driver = अणु
	.driver = अणु
		.name = RX6110_DRIVER_NAME,
		.acpi_match_table = rx6110_i2c_acpi_match,
	पूर्ण,
	.probe		= rx6110_i2c_probe,
	.id_table	= rx6110_i2c_id,
पूर्ण;

अटल पूर्णांक rx6110_i2c_रेजिस्टर(व्योम)
अणु
	वापस i2c_add_driver(&rx6110_i2c_driver);
पूर्ण

अटल व्योम rx6110_i2c_unरेजिस्टर(व्योम)
अणु
	i2c_del_driver(&rx6110_i2c_driver);
पूर्ण
#अन्यथा
अटल पूर्णांक rx6110_i2c_रेजिस्टर(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम rx6110_i2c_unरेजिस्टर(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_I2C */

अटल पूर्णांक __init rx6110_module_init(व्योम)
अणु
	पूर्णांक ret;

	ret = rx6110_spi_रेजिस्टर();
	अगर (ret)
		वापस ret;

	ret = rx6110_i2c_रेजिस्टर();
	अगर (ret)
		rx6110_spi_unरेजिस्टर();

	वापस ret;
पूर्ण
module_init(rx6110_module_init);

अटल व्योम __निकास rx6110_module_निकास(व्योम)
अणु
	rx6110_spi_unरेजिस्टर();
	rx6110_i2c_unरेजिस्टर();
पूर्ण
module_निकास(rx6110_module_निकास);

MODULE_AUTHOR("Val Krutov <val.krutov@erd.epson.com>");
MODULE_DESCRIPTION("RX-6110 SA RTC driver");
MODULE_LICENSE("GPL");
