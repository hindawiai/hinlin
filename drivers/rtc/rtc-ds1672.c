<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * An rtc/i2c driver क्रम the Dallas DS1672
 * Copyright 2005-06 Tower Technologies
 *
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/rtc.h>
#समावेश <linux/module.h>

/* Registers */

#घोषणा DS1672_REG_CNT_BASE	0
#घोषणा DS1672_REG_CONTROL	4
#घोषणा DS1672_REG_TRICKLE	5

#घोषणा DS1672_REG_CONTROL_EOSC	0x80

/*
 * In the routines that deal directly with the ds1672 hardware, we use
 * rtc_समय -- month 0-11, hour 0-23, yr = calendar year-epoch
 * Time is set to UTC.
 */
अटल पूर्णांक ds1672_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित दीर्घ समय;
	अचिन्हित अक्षर addr = DS1672_REG_CONTROL;
	अचिन्हित अक्षर buf[4];

	काष्ठा i2c_msg msgs[] = अणु
		अणु/* setup पढ़ो ptr */
			.addr = client->addr,
			.len = 1,
			.buf = &addr
		पूर्ण,
		अणु/* पढ़ो date */
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = buf
		पूर्ण,
	पूर्ण;

	/* पढ़ो control रेजिस्टर */
	अगर ((i2c_transfer(client->adapter, &msgs[0], 2)) != 2) अणु
		dev_warn(&client->dev, "Unable to read the control register\n");
		वापस -EIO;
	पूर्ण

	अगर (buf[0] & DS1672_REG_CONTROL_EOSC) अणु
		dev_warn(&client->dev, "Oscillator not enabled. Set time to enable.\n");
		वापस -EINVAL;
	पूर्ण

	addr = DS1672_REG_CNT_BASE;
	msgs[1].len = 4;

	/* पढ़ो date रेजिस्टरs */
	अगर ((i2c_transfer(client->adapter, &msgs[0], 2)) != 2) अणु
		dev_err(&client->dev, "%s: read error\n", __func__);
		वापस -EIO;
	पूर्ण

	dev_dbg(&client->dev,
		"%s: raw read data - counters=%02x,%02x,%02x,%02x\n",
		__func__, buf[0], buf[1], buf[2], buf[3]);

	समय = ((अचिन्हित दीर्घ)buf[3] << 24) | (buf[2] << 16) |
	       (buf[1] << 8) | buf[0];

	rtc_समय64_to_पंचांग(समय, पंचांग);

	dev_dbg(&client->dev, "%s: tm is %ptR\n", __func__, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक ds1672_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक xfer;
	अचिन्हित अक्षर buf[6];
	अचिन्हित दीर्घ secs = rtc_पंचांग_to_समय64(पंचांग);

	buf[0] = DS1672_REG_CNT_BASE;
	buf[1] = secs & 0x000000FF;
	buf[2] = (secs & 0x0000FF00) >> 8;
	buf[3] = (secs & 0x00FF0000) >> 16;
	buf[4] = (secs & 0xFF000000) >> 24;
	buf[5] = 0;		/* set control reg to enable counting */

	xfer = i2c_master_send(client, buf, 6);
	अगर (xfer != 6) अणु
		dev_err(&client->dev, "%s: send: %d\n", __func__, xfer);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ds1672_rtc_ops = अणु
	.पढ़ो_समय = ds1672_पढ़ो_समय,
	.set_समय = ds1672_set_समय,
पूर्ण;

अटल पूर्णांक ds1672_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक err = 0;
	काष्ठा rtc_device *rtc;

	dev_dbg(&client->dev, "%s\n", __func__);

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	rtc = devm_rtc_allocate_device(&client->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	rtc->ops = &ds1672_rtc_ops;
	rtc->range_max = U32_MAX;

	err = devm_rtc_रेजिस्टर_device(rtc);
	अगर (err)
		वापस err;

	i2c_set_clientdata(client, rtc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ds1672_id[] = अणु
	अणु "ds1672", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ds1672_id);

अटल स्थिर __maybe_unused काष्ठा of_device_id ds1672_of_match[] = अणु
	अणु .compatible = "dallas,ds1672" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ds1672_of_match);

अटल काष्ठा i2c_driver ds1672_driver = अणु
	.driver = अणु
		   .name = "rtc-ds1672",
		   .of_match_table = of_match_ptr(ds1672_of_match),
	पूर्ण,
	.probe = &ds1672_probe,
	.id_table = ds1672_id,
पूर्ण;

module_i2c_driver(ds1672_driver);

MODULE_AUTHOR("Alessandro Zummo <a.zummo@towertech.it>");
MODULE_DESCRIPTION("Dallas/Maxim DS1672 timekeeper driver");
MODULE_LICENSE("GPL");
