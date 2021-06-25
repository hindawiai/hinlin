<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Real Time Clock (RTC) Driver क्रम sd3078
 * Copyright (C) 2018 Zoro Li
 */

#समावेश <linux/bcd.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>

#घोषणा SD3078_REG_SC			0x00
#घोषणा SD3078_REG_MN			0x01
#घोषणा SD3078_REG_HR			0x02
#घोषणा SD3078_REG_DW			0x03
#घोषणा SD3078_REG_DM			0x04
#घोषणा SD3078_REG_MO			0x05
#घोषणा SD3078_REG_YR			0x06

#घोषणा SD3078_REG_CTRL1		0x0f
#घोषणा SD3078_REG_CTRL2		0x10
#घोषणा SD3078_REG_CTRL3		0x11

#घोषणा KEY_WRITE1		0x80
#घोषणा KEY_WRITE2		0x04
#घोषणा KEY_WRITE3		0x80

#घोषणा NUM_TIME_REGS   (SD3078_REG_YR - SD3078_REG_SC + 1)

/*
 * The sd3078 has ग_लिखो protection
 * and we can choose whether or not to use it.
 * Write protection is turned off by शेष.
 */
#घोषणा WRITE_PROTECT_EN	0

काष्ठा sd3078 अणु
	काष्ठा rtc_device	*rtc;
	काष्ठा regmap		*regmap;
पूर्ण;

/*
 * In order to prevent arbitrary modअगरication of the समय रेजिस्टर,
 * when modअगरication of the रेजिस्टर,
 * the "write" bit needs to be written in a certain order.
 * 1. set WRITE1 bit
 * 2. set WRITE2 bit
 * 3. set WRITE3 bit
 */
अटल व्योम sd3078_enable_reg_ग_लिखो(काष्ठा sd3078 *sd3078)
अणु
	regmap_update_bits(sd3078->regmap, SD3078_REG_CTRL2,
			   KEY_WRITE1, KEY_WRITE1);
	regmap_update_bits(sd3078->regmap, SD3078_REG_CTRL1,
			   KEY_WRITE2, KEY_WRITE2);
	regmap_update_bits(sd3078->regmap, SD3078_REG_CTRL1,
			   KEY_WRITE3, KEY_WRITE3);
पूर्ण

#अगर WRITE_PROTECT_EN
/*
 * In order to prevent arbitrary modअगरication of the समय रेजिस्टर,
 * we should disable the ग_लिखो function.
 * when disable ग_लिखो,
 * the "write" bit needs to be clear in a certain order.
 * 1. clear WRITE2 bit
 * 2. clear WRITE3 bit
 * 3. clear WRITE1 bit
 */
अटल व्योम sd3078_disable_reg_ग_लिखो(काष्ठा sd3078 *sd3078)
अणु
	regmap_update_bits(sd3078->regmap, SD3078_REG_CTRL1,
			   KEY_WRITE2, 0);
	regmap_update_bits(sd3078->regmap, SD3078_REG_CTRL1,
			   KEY_WRITE3, 0);
	regmap_update_bits(sd3078->regmap, SD3078_REG_CTRL2,
			   KEY_WRITE1, 0);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sd3078_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित अक्षर hour;
	अचिन्हित अक्षर rtc_data[NUM_TIME_REGS] = अणु0पूर्ण;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा sd3078 *sd3078 = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(sd3078->regmap, SD3078_REG_SC, rtc_data,
			       NUM_TIME_REGS);
	अगर (ret < 0) अणु
		dev_err(dev, "reading from RTC failed with err:%d\n", ret);
		वापस ret;
	पूर्ण

	पंचांग->पंचांग_sec	= bcd2bin(rtc_data[SD3078_REG_SC] & 0x7F);
	पंचांग->पंचांग_min	= bcd2bin(rtc_data[SD3078_REG_MN] & 0x7F);

	/*
	 * The sd3078 supports 12/24 hour mode.
	 * When getting समय,
	 * we need to convert the 12 hour mode to the 24 hour mode.
	 */
	hour = rtc_data[SD3078_REG_HR];
	अगर (hour & 0x80) /* 24H MODE */
		पंचांग->पंचांग_hour = bcd2bin(rtc_data[SD3078_REG_HR] & 0x3F);
	अन्यथा अगर (hour & 0x20) /* 12H MODE PM */
		पंचांग->पंचांग_hour = bcd2bin(rtc_data[SD3078_REG_HR] & 0x1F) + 12;
	अन्यथा /* 12H MODE AM */
		पंचांग->पंचांग_hour = bcd2bin(rtc_data[SD3078_REG_HR] & 0x1F);

	पंचांग->पंचांग_mday = bcd2bin(rtc_data[SD3078_REG_DM] & 0x3F);
	पंचांग->पंचांग_wday = rtc_data[SD3078_REG_DW] & 0x07;
	पंचांग->पंचांग_mon	= bcd2bin(rtc_data[SD3078_REG_MO] & 0x1F) - 1;
	पंचांग->पंचांग_year = bcd2bin(rtc_data[SD3078_REG_YR]) + 100;

	वापस 0;
पूर्ण

अटल पूर्णांक sd3078_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित अक्षर rtc_data[NUM_TIME_REGS];
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा sd3078 *sd3078 = i2c_get_clientdata(client);
	पूर्णांक ret;

	rtc_data[SD3078_REG_SC] = bin2bcd(पंचांग->पंचांग_sec);
	rtc_data[SD3078_REG_MN] = bin2bcd(पंचांग->पंचांग_min);
	rtc_data[SD3078_REG_HR] = bin2bcd(पंचांग->पंचांग_hour) | 0x80;
	rtc_data[SD3078_REG_DM] = bin2bcd(पंचांग->पंचांग_mday);
	rtc_data[SD3078_REG_DW] = पंचांग->पंचांग_wday & 0x07;
	rtc_data[SD3078_REG_MO] = bin2bcd(पंचांग->पंचांग_mon) + 1;
	rtc_data[SD3078_REG_YR] = bin2bcd(पंचांग->पंचांग_year - 100);

#अगर WRITE_PROTECT_EN
	sd3078_enable_reg_ग_लिखो(sd3078);
#पूर्ण_अगर

	ret = regmap_bulk_ग_लिखो(sd3078->regmap, SD3078_REG_SC, rtc_data,
				NUM_TIME_REGS);
	अगर (ret < 0) अणु
		dev_err(dev, "writing to RTC failed with err:%d\n", ret);
		वापस ret;
	पूर्ण

#अगर WRITE_PROTECT_EN
	sd3078_disable_reg_ग_लिखो(sd3078);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops sd3078_rtc_ops = अणु
	.पढ़ो_समय	= sd3078_rtc_पढ़ो_समय,
	.set_समय	= sd3078_rtc_set_समय,
पूर्ण;

अटल स्थिर काष्ठा regmap_config regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x11,
पूर्ण;

अटल पूर्णांक sd3078_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा sd3078 *sd3078;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	sd3078 = devm_kzalloc(&client->dev, माप(*sd3078), GFP_KERNEL);
	अगर (!sd3078)
		वापस -ENOMEM;

	sd3078->regmap = devm_regmap_init_i2c(client, &regmap_config);
	अगर (IS_ERR(sd3078->regmap)) अणु
		dev_err(&client->dev, "regmap allocation failed\n");
		वापस PTR_ERR(sd3078->regmap);
	पूर्ण

	i2c_set_clientdata(client, sd3078);

	sd3078->rtc = devm_rtc_allocate_device(&client->dev);
	अगर (IS_ERR(sd3078->rtc))
		वापस PTR_ERR(sd3078->rtc);

	sd3078->rtc->ops = &sd3078_rtc_ops;
	sd3078->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	sd3078->rtc->range_max = RTC_TIMESTAMP_END_2099;

	ret = devm_rtc_रेजिस्टर_device(sd3078->rtc);
	अगर (ret)
		वापस ret;

	sd3078_enable_reg_ग_लिखो(sd3078);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id sd3078_id[] = अणु
	अणु"sd3078", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sd3078_id);

अटल स्थिर __maybe_unused काष्ठा of_device_id rtc_dt_match[] = अणु
	अणु .compatible = "whwave,sd3078" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rtc_dt_match);

अटल काष्ठा i2c_driver sd3078_driver = अणु
	.driver     = अणु
		.name   = "sd3078",
		.of_match_table = of_match_ptr(rtc_dt_match),
	पूर्ण,
	.probe      = sd3078_probe,
	.id_table   = sd3078_id,
पूर्ण;

module_i2c_driver(sd3078_driver);

MODULE_AUTHOR("Dianlong Li <long17.cool@163.com>");
MODULE_DESCRIPTION("SD3078 RTC driver");
MODULE_LICENSE("GPL v2");
