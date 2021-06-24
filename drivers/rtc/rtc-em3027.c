<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An rtc/i2c driver क्रम the EM Microelectronic EM3027
 * Copyright 2011 CompuLab, Ltd.
 *
 * Author: Mike Rapoport <mike@compulab.co.il>
 *
 * Based on rtc-ds1672.c by Alessandro Zummo <a.zummo@towertech.it>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>

/* Registers */
#घोषणा EM3027_REG_ON_OFF_CTRL	0x00
#घोषणा EM3027_REG_IRQ_CTRL	0x01
#घोषणा EM3027_REG_IRQ_FLAGS	0x02
#घोषणा EM3027_REG_STATUS	0x03
#घोषणा EM3027_REG_RST_CTRL	0x04

#घोषणा EM3027_REG_WATCH_SEC	0x08
#घोषणा EM3027_REG_WATCH_MIN	0x09
#घोषणा EM3027_REG_WATCH_HOUR	0x0a
#घोषणा EM3027_REG_WATCH_DATE	0x0b
#घोषणा EM3027_REG_WATCH_DAY	0x0c
#घोषणा EM3027_REG_WATCH_MON	0x0d
#घोषणा EM3027_REG_WATCH_YEAR	0x0e

#घोषणा EM3027_REG_ALARM_SEC	0x10
#घोषणा EM3027_REG_ALARM_MIN	0x11
#घोषणा EM3027_REG_ALARM_HOUR	0x12
#घोषणा EM3027_REG_ALARM_DATE	0x13
#घोषणा EM3027_REG_ALARM_DAY	0x14
#घोषणा EM3027_REG_ALARM_MON	0x15
#घोषणा EM3027_REG_ALARM_YEAR	0x16

अटल काष्ठा i2c_driver em3027_driver;

अटल पूर्णांक em3027_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	अचिन्हित अक्षर addr = EM3027_REG_WATCH_SEC;
	अचिन्हित अक्षर buf[7];

	काष्ठा i2c_msg msgs[] = अणु
		अणु/* setup पढ़ो addr */
			.addr = client->addr,
			.len = 1,
			.buf = &addr
		पूर्ण,
		अणु/* पढ़ो समय/date */
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 7,
			.buf = buf
		पूर्ण,
	पूर्ण;

	/* पढ़ो समय/date रेजिस्टरs */
	अगर ((i2c_transfer(client->adapter, &msgs[0], 2)) != 2) अणु
		dev_err(&client->dev, "%s: read error\n", __func__);
		वापस -EIO;
	पूर्ण

	पंचांग->पंचांग_sec	= bcd2bin(buf[0]);
	पंचांग->पंचांग_min	= bcd2bin(buf[1]);
	पंचांग->पंचांग_hour	= bcd2bin(buf[2]);
	पंचांग->पंचांग_mday	= bcd2bin(buf[3]);
	पंचांग->पंचांग_wday	= bcd2bin(buf[4]);
	पंचांग->पंचांग_mon	= bcd2bin(buf[5]) - 1;
	पंचांग->पंचांग_year	= bcd2bin(buf[6]) + 100;

	वापस 0;
पूर्ण

अटल पूर्णांक em3027_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित अक्षर buf[8];

	काष्ठा i2c_msg msg = अणु
		.addr = client->addr,
		.len = 8,
		.buf = buf,	/* ग_लिखो समय/date */
	पूर्ण;

	buf[0] = EM3027_REG_WATCH_SEC;
	buf[1] = bin2bcd(पंचांग->पंचांग_sec);
	buf[2] = bin2bcd(पंचांग->पंचांग_min);
	buf[3] = bin2bcd(पंचांग->पंचांग_hour);
	buf[4] = bin2bcd(पंचांग->पंचांग_mday);
	buf[5] = bin2bcd(पंचांग->पंचांग_wday);
	buf[6] = bin2bcd(पंचांग->पंचांग_mon + 1);
	buf[7] = bin2bcd(पंचांग->पंचांग_year % 100);

	/* ग_लिखो समय/date रेजिस्टरs */
	अगर ((i2c_transfer(client->adapter, &msg, 1)) != 1) अणु
		dev_err(&client->dev, "%s: write error\n", __func__);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops em3027_rtc_ops = अणु
	.पढ़ो_समय = em3027_get_समय,
	.set_समय = em3027_set_समय,
पूर्ण;

अटल पूर्णांक em3027_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rtc_device *rtc;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	rtc = devm_rtc_device_रेजिस्टर(&client->dev, em3027_driver.driver.name,
				  &em3027_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	i2c_set_clientdata(client, rtc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id em3027_id[] = अणु
	अणु "em3027", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, em3027_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id em3027_of_match[] = अणु
	अणु .compatible = "emmicro,em3027", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, em3027_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver em3027_driver = अणु
	.driver = अणु
		   .name = "rtc-em3027",
		   .of_match_table = of_match_ptr(em3027_of_match),
	पूर्ण,
	.probe = &em3027_probe,
	.id_table = em3027_id,
पूर्ण;

module_i2c_driver(em3027_driver);

MODULE_AUTHOR("Mike Rapoport <mike@compulab.co.il>");
MODULE_DESCRIPTION("EM Microelectronic EM3027 RTC driver");
MODULE_LICENSE("GPL");
