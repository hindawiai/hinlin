<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An I2C driver क्रम the Epson RX8581 RTC
 *
 * Author: Martyn Welch <martyn.welch@ge.com>
 * Copyright 2008 GE Intelligent Platक्रमms Embedded Systems, Inc.
 *
 * Based on: rtc-pcf8563.c (An I2C driver क्रम the Philips PCF8563 RTC)
 * Copyright 2005-06 Tower Technologies
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/bcd.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>
#समावेश <linux/log2.h>

#घोषणा RX8581_REG_SC		0x00 /* Second in BCD */
#घोषणा RX8581_REG_MN		0x01 /* Minute in BCD */
#घोषणा RX8581_REG_HR		0x02 /* Hour in BCD */
#घोषणा RX8581_REG_DW		0x03 /* Day of Week */
#घोषणा RX8581_REG_DM		0x04 /* Day of Month in BCD */
#घोषणा RX8581_REG_MO		0x05 /* Month in BCD */
#घोषणा RX8581_REG_YR		0x06 /* Year in BCD */
#घोषणा RX8581_REG_RAM		0x07 /* RAM */
#घोषणा RX8581_REG_AMN		0x08 /* Alarm Min in BCD*/
#घोषणा RX8581_REG_AHR		0x09 /* Alarm Hour in BCD */
#घोषणा RX8581_REG_ADM		0x0A
#घोषणा RX8581_REG_ADW		0x0A
#घोषणा RX8581_REG_TMR0		0x0B
#घोषणा RX8581_REG_TMR1		0x0C
#घोषणा RX8581_REG_EXT		0x0D /* Extension Register */
#घोषणा RX8581_REG_FLAG		0x0E /* Flag Register */
#घोषणा RX8581_REG_CTRL		0x0F /* Control Register */


/* Flag Register bit definitions */
#घोषणा RX8581_FLAG_UF		0x20 /* Update */
#घोषणा RX8581_FLAG_TF		0x10 /* Timer */
#घोषणा RX8581_FLAG_AF		0x08 /* Alarm */
#घोषणा RX8581_FLAG_VLF		0x02 /* Voltage Low */

/* Control Register bit definitions */
#घोषणा RX8581_CTRL_UIE		0x20 /* Update Interrupt Enable */
#घोषणा RX8581_CTRL_TIE		0x10 /* Timer Interrupt Enable */
#घोषणा RX8581_CTRL_AIE		0x08 /* Alarm Interrupt Enable */
#घोषणा RX8581_CTRL_STOP	0x02 /* STOP bit */
#घोषणा RX8581_CTRL_RESET	0x01 /* RESET bit */

#घोषणा RX8571_USER_RAM		0x10
#घोषणा RX8571_NVRAM_SIZE	0x10

काष्ठा rx8581 अणु
	काष्ठा regmap		*regmap;
	काष्ठा rtc_device	*rtc;
पूर्ण;

काष्ठा rx85x1_config अणु
	काष्ठा regmap_config regmap;
	अचिन्हित पूर्णांक num_nvram;
पूर्ण;

/*
 * In the routines that deal directly with the rx8581 hardware, we use
 * rtc_समय -- month 0-11, hour 0-23, yr = calendar year-epoch.
 */
अटल पूर्णांक rx8581_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित अक्षर date[7];
	अचिन्हित पूर्णांक data;
	पूर्णांक err;
	काष्ठा rx8581 *rx8581 = i2c_get_clientdata(client);

	/* First we ensure that the "update flag" is not set, we पढ़ो the
	 * समय and date then re-पढ़ो the "update flag". If the update flag
	 * has been set, we know that the समय has changed during the पढ़ो so
	 * we repeat the whole process again.
	 */
	err = regmap_पढ़ो(rx8581->regmap, RX8581_REG_FLAG, &data);
	अगर (err < 0)
		वापस err;

	अगर (data & RX8581_FLAG_VLF) अणु
		dev_warn(dev,
			 "low voltage detected, date/time is not reliable.\n");
		वापस -EINVAL;
	पूर्ण

	करो अणु
		/* If update flag set, clear it */
		अगर (data & RX8581_FLAG_UF) अणु
			err = regmap_ग_लिखो(rx8581->regmap, RX8581_REG_FLAG,
					  data & ~RX8581_FLAG_UF);
			अगर (err < 0)
				वापस err;
		पूर्ण

		/* Now पढ़ो समय and date */
		err = regmap_bulk_पढ़ो(rx8581->regmap, RX8581_REG_SC, date,
				       माप(date));
		अगर (err < 0)
			वापस err;

		/* Check flag रेजिस्टर */
		err = regmap_पढ़ो(rx8581->regmap, RX8581_REG_FLAG, &data);
		अगर (err < 0)
			वापस err;
	पूर्ण जबतक (data & RX8581_FLAG_UF);

	dev_dbg(dev, "%s: raw data is sec=%02x, min=%02x, hr=%02x, "
		"wday=%02x, mday=%02x, mon=%02x, year=%02x\n",
		__func__,
		date[0], date[1], date[2], date[3], date[4], date[5], date[6]);

	पंचांग->पंचांग_sec = bcd2bin(date[RX8581_REG_SC] & 0x7F);
	पंचांग->पंचांग_min = bcd2bin(date[RX8581_REG_MN] & 0x7F);
	पंचांग->पंचांग_hour = bcd2bin(date[RX8581_REG_HR] & 0x3F); /* rtc hr 0-23 */
	पंचांग->पंचांग_wday = ilog2(date[RX8581_REG_DW] & 0x7F);
	पंचांग->पंचांग_mday = bcd2bin(date[RX8581_REG_DM] & 0x3F);
	पंचांग->पंचांग_mon = bcd2bin(date[RX8581_REG_MO] & 0x1F) - 1; /* rtc mn 1-12 */
	पंचांग->पंचांग_year = bcd2bin(date[RX8581_REG_YR]) + 100;

	dev_dbg(dev, "%s: tm is secs=%d, mins=%d, hours=%d, "
		"mday=%d, mon=%d, year=%d, wday=%d\n",
		__func__,
		पंचांग->पंचांग_sec, पंचांग->पंचांग_min, पंचांग->पंचांग_hour,
		पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	वापस 0;
पूर्ण

अटल पूर्णांक rx8581_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक err;
	अचिन्हित अक्षर buf[7];
	काष्ठा rx8581 *rx8581 = i2c_get_clientdata(client);

	dev_dbg(dev, "%s: secs=%d, mins=%d, hours=%d, "
		"mday=%d, mon=%d, year=%d, wday=%d\n",
		__func__,
		पंचांग->पंचांग_sec, पंचांग->पंचांग_min, पंचांग->पंचांग_hour,
		पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	/* hours, minutes and seconds */
	buf[RX8581_REG_SC] = bin2bcd(पंचांग->पंचांग_sec);
	buf[RX8581_REG_MN] = bin2bcd(पंचांग->पंचांग_min);
	buf[RX8581_REG_HR] = bin2bcd(पंचांग->पंचांग_hour);

	buf[RX8581_REG_DM] = bin2bcd(पंचांग->पंचांग_mday);

	/* month, 1 - 12 */
	buf[RX8581_REG_MO] = bin2bcd(पंचांग->पंचांग_mon + 1);

	/* year and century */
	buf[RX8581_REG_YR] = bin2bcd(पंचांग->पंचांग_year - 100);
	buf[RX8581_REG_DW] = (0x1 << पंचांग->पंचांग_wday);

	/* Stop the घड़ी */
	err = regmap_update_bits(rx8581->regmap, RX8581_REG_CTRL,
				 RX8581_CTRL_STOP, RX8581_CTRL_STOP);
	अगर (err < 0)
		वापस err;

	/* ग_लिखो रेजिस्टर's data */
	err = regmap_bulk_ग_लिखो(rx8581->regmap, RX8581_REG_SC,
				buf, माप(buf));
	अगर (err < 0)
		वापस err;

	/* get VLF and clear it */
	err = regmap_update_bits(rx8581->regmap, RX8581_REG_FLAG,
				 RX8581_FLAG_VLF, 0);
	अगर (err < 0)
		वापस err;

	/* Restart the घड़ी */
	वापस regmap_update_bits(rx8581->regmap, RX8581_REG_CTRL,
				 RX8581_CTRL_STOP, 0);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rx8581_rtc_ops = अणु
	.पढ़ो_समय	= rx8581_rtc_पढ़ो_समय,
	.set_समय	= rx8581_rtc_set_समय,
पूर्ण;

अटल पूर्णांक rx8571_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			     माप_प्रकार bytes)
अणु
	काष्ठा rx8581 *rx8581 = priv;

	वापस regmap_bulk_पढ़ो(rx8581->regmap, RX8571_USER_RAM + offset,
				val, bytes);
पूर्ण

अटल पूर्णांक rx8571_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			      माप_प्रकार bytes)
अणु
	काष्ठा rx8581 *rx8581 = priv;

	वापस regmap_bulk_ग_लिखो(rx8581->regmap, RX8571_USER_RAM + offset,
				 val, bytes);
पूर्ण

अटल पूर्णांक rx85x1_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			     माप_प्रकार bytes)
अणु
	काष्ठा rx8581 *rx8581 = priv;
	अचिन्हित पूर्णांक पंचांगp_val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rx8581->regmap, RX8581_REG_RAM, &पंचांगp_val);
	(*(अचिन्हित अक्षर *)val) = (अचिन्हित अक्षर) पंचांगp_val;

	वापस ret;
पूर्ण

अटल पूर्णांक rx85x1_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			      माप_प्रकार bytes)
अणु
	काष्ठा rx8581 *rx8581 = priv;
	अचिन्हित अक्षर पंचांगp_val;

	पंचांगp_val = *((अचिन्हित अक्षर *)val);
	वापस regmap_ग_लिखो(rx8581->regmap, RX8581_REG_RAM,
				(अचिन्हित पूर्णांक)पंचांगp_val);
पूर्ण

अटल स्थिर काष्ठा rx85x1_config rx8581_config = अणु
	.regmap = अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0xf,
	पूर्ण,
	.num_nvram = 1
पूर्ण;

अटल स्थिर काष्ठा rx85x1_config rx8571_config = अणु
	.regmap = अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0x1f,
	पूर्ण,
	.num_nvram = 2
पूर्ण;

अटल पूर्णांक rx8581_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rx8581 *rx8581;
	स्थिर काष्ठा rx85x1_config *config = &rx8581_config;
	स्थिर व्योम *data = of_device_get_match_data(&client->dev);
	अटल काष्ठा nvmem_config nvmem_cfg[] = अणु
		अणु
			.name = "rx85x1-",
			.word_size = 1,
			.stride = 1,
			.size = 1,
			.reg_पढ़ो = rx85x1_nvram_पढ़ो,
			.reg_ग_लिखो = rx85x1_nvram_ग_लिखो,
		पूर्ण, अणु
			.name = "rx8571-",
			.word_size = 1,
			.stride = 1,
			.size = RX8571_NVRAM_SIZE,
			.reg_पढ़ो = rx8571_nvram_पढ़ो,
			.reg_ग_लिखो = rx8571_nvram_ग_लिखो,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret, i;

	dev_dbg(&client->dev, "%s\n", __func__);

	अगर (data)
		config = data;

	rx8581 = devm_kzalloc(&client->dev, माप(काष्ठा rx8581), GFP_KERNEL);
	अगर (!rx8581)
		वापस -ENOMEM;

	i2c_set_clientdata(client, rx8581);

	rx8581->regmap = devm_regmap_init_i2c(client, &config->regmap);
	अगर (IS_ERR(rx8581->regmap))
		वापस PTR_ERR(rx8581->regmap);

	rx8581->rtc = devm_rtc_allocate_device(&client->dev);
	अगर (IS_ERR(rx8581->rtc))
		वापस PTR_ERR(rx8581->rtc);

	rx8581->rtc->ops = &rx8581_rtc_ops;
	rx8581->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rx8581->rtc->range_max = RTC_TIMESTAMP_END_2099;
	rx8581->rtc->start_secs = 0;
	rx8581->rtc->set_start_समय = true;

	ret = devm_rtc_रेजिस्टर_device(rx8581->rtc);

	क्रम (i = 0; i < config->num_nvram; i++) अणु
		nvmem_cfg[i].priv = rx8581;
		devm_rtc_nvmem_रेजिस्टर(rx8581->rtc, &nvmem_cfg[i]);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id rx8581_id[] = अणु
	अणु "rx8581", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rx8581_id);

अटल स्थिर __maybe_unused काष्ठा of_device_id rx8581_of_match[] = अणु
	अणु .compatible = "epson,rx8571", .data = &rx8571_config पूर्ण,
	अणु .compatible = "epson,rx8581", .data = &rx8581_config पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rx8581_of_match);

अटल काष्ठा i2c_driver rx8581_driver = अणु
	.driver		= अणु
		.name	= "rtc-rx8581",
		.of_match_table = of_match_ptr(rx8581_of_match),
	पूर्ण,
	.probe		= rx8581_probe,
	.id_table	= rx8581_id,
पूर्ण;

module_i2c_driver(rx8581_driver);

MODULE_AUTHOR("Martyn Welch <martyn.welch@ge.com>");
MODULE_DESCRIPTION("Epson RX-8571/RX-8581 RTC driver");
MODULE_LICENSE("GPL");
