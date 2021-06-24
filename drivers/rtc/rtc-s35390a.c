<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Seiko Instruments S-35390A RTC Driver
 *
 * Copyright (c) 2007 Byron Bradley
 */

#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/i2c.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/bcd.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>

#घोषणा S35390A_CMD_STATUS1	0
#घोषणा S35390A_CMD_STATUS2	1
#घोषणा S35390A_CMD_TIME1	2
#घोषणा S35390A_CMD_TIME2	3
#घोषणा S35390A_CMD_INT2_REG1	5

#घोषणा S35390A_BYTE_YEAR	0
#घोषणा S35390A_BYTE_MONTH	1
#घोषणा S35390A_BYTE_DAY	2
#घोषणा S35390A_BYTE_WDAY	3
#घोषणा S35390A_BYTE_HOURS	4
#घोषणा S35390A_BYTE_MINS	5
#घोषणा S35390A_BYTE_SECS	6

#घोषणा S35390A_ALRM_BYTE_WDAY	0
#घोषणा S35390A_ALRM_BYTE_HOURS	1
#घोषणा S35390A_ALRM_BYTE_MINS	2

/* flags क्रम STATUS1 */
#घोषणा S35390A_FLAG_POC	BIT(0)
#घोषणा S35390A_FLAG_BLD	BIT(1)
#घोषणा S35390A_FLAG_INT2	BIT(2)
#घोषणा S35390A_FLAG_24H	BIT(6)
#घोषणा S35390A_FLAG_RESET	BIT(7)

/* flag क्रम STATUS2 */
#घोषणा S35390A_FLAG_TEST	BIT(0)

/* INT2 pin output mode */
#घोषणा S35390A_INT2_MODE_MASK		0x0E
#घोषणा S35390A_INT2_MODE_NOINTR	0x00
#घोषणा S35390A_INT2_MODE_ALARM		BIT(1) /* INT2AE */
#घोषणा S35390A_INT2_MODE_PMIN_EDG	BIT(2) /* INT2ME */
#घोषणा S35390A_INT2_MODE_FREQ		BIT(3) /* INT2FE */
#घोषणा S35390A_INT2_MODE_PMIN		(BIT(3) | BIT(2)) /* INT2FE | INT2ME */

अटल स्थिर काष्ठा i2c_device_id s35390a_id[] = अणु
	अणु "s35390a", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, s35390a_id);

अटल स्थिर __maybe_unused काष्ठा of_device_id s35390a_of_match[] = अणु
	अणु .compatible = "s35390a" पूर्ण,
	अणु .compatible = "sii,s35390a" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, s35390a_of_match);

काष्ठा s35390a अणु
	काष्ठा i2c_client *client[8];
	काष्ठा rtc_device *rtc;
	पूर्णांक twentyfourhour;
पूर्ण;

अटल पूर्णांक s35390a_set_reg(काष्ठा s35390a *s35390a, पूर्णांक reg, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा i2c_client *client = s35390a->client[reg];
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = client->addr,
			.len = len,
			.buf = buf
		पूर्ण,
	पूर्ण;

	अगर ((i2c_transfer(client->adapter, msg, 1)) != 1)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक s35390a_get_reg(काष्ठा s35390a *s35390a, पूर्णांक reg, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा i2c_client *client = s35390a->client[reg];
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = len,
			.buf = buf
		पूर्ण,
	पूर्ण;

	अगर ((i2c_transfer(client->adapter, msg, 1)) != 1)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक s35390a_init(काष्ठा s35390a *s35390a)
अणु
	u8 buf;
	पूर्णांक ret;
	अचिन्हित initcount = 0;

	/*
	 * At least one of POC and BLD are set, so reinitialise chip. Keeping
	 * this inक्रमmation in the hardware to know later that the समय isn't
	 * valid is unक्रमtunately not possible because POC and BLD are cleared
	 * on पढ़ो. So the reset is best करोne now.
	 *
	 * The 24H bit is kept over reset, so set it alपढ़ोy here.
	 */
initialize:
	buf = S35390A_FLAG_RESET | S35390A_FLAG_24H;
	ret = s35390a_set_reg(s35390a, S35390A_CMD_STATUS1, &buf, 1);

	अगर (ret < 0)
		वापस ret;

	ret = s35390a_get_reg(s35390a, S35390A_CMD_STATUS1, &buf, 1);
	अगर (ret < 0)
		वापस ret;

	अगर (buf & (S35390A_FLAG_POC | S35390A_FLAG_BLD)) अणु
		/* Try up to five बार to reset the chip */
		अगर (initcount < 5) अणु
			++initcount;
			जाओ initialize;
		पूर्ण अन्यथा
			वापस -EIO;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Returns <0 on error, 0 अगर rtc is setup fine and 1 अगर the chip was reset.
 * To keep the inक्रमmation अगर an irq is pending, pass the value पढ़ो from
 * STATUS1 to the caller.
 */
अटल पूर्णांक s35390a_पढ़ो_status(काष्ठा s35390a *s35390a, अक्षर *status1)
अणु
	पूर्णांक ret;

	ret = s35390a_get_reg(s35390a, S35390A_CMD_STATUS1, status1, 1);
	अगर (ret < 0)
		वापस ret;

	अगर (*status1 & S35390A_FLAG_POC) अणु
		/*
		 * Do not communicate क्रम 0.5 seconds since the घातer-on
		 * detection circuit is in operation.
		 */
		msleep(500);
		वापस 1;
	पूर्ण अन्यथा अगर (*status1 & S35390A_FLAG_BLD)
		वापस 1;
	/*
	 * If both POC and BLD are unset everything is fine.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक s35390a_disable_test_mode(काष्ठा s35390a *s35390a)
अणु
	अक्षर buf[1];

	अगर (s35390a_get_reg(s35390a, S35390A_CMD_STATUS2, buf, माप(buf)) < 0)
		वापस -EIO;

	अगर (!(buf[0] & S35390A_FLAG_TEST))
		वापस 0;

	buf[0] &= ~S35390A_FLAG_TEST;
	वापस s35390a_set_reg(s35390a, S35390A_CMD_STATUS2, buf, माप(buf));
पूर्ण

अटल अक्षर s35390a_hr2reg(काष्ठा s35390a *s35390a, पूर्णांक hour)
अणु
	अगर (s35390a->twentyfourhour)
		वापस bin2bcd(hour);

	अगर (hour < 12)
		वापस bin2bcd(hour);

	वापस 0x40 | bin2bcd(hour - 12);
पूर्ण

अटल पूर्णांक s35390a_reg2hr(काष्ठा s35390a *s35390a, अक्षर reg)
अणु
	अचिन्हित hour;

	अगर (s35390a->twentyfourhour)
		वापस bcd2bin(reg & 0x3f);

	hour = bcd2bin(reg & 0x3f);
	अगर (reg & 0x40)
		hour += 12;

	वापस hour;
पूर्ण

अटल पूर्णांक s35390a_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा s35390a	*s35390a = i2c_get_clientdata(client);
	पूर्णांक i, err;
	अक्षर buf[7], status;

	dev_dbg(&client->dev, "%s: tm is secs=%d, mins=%d, hours=%d mday=%d, "
		"mon=%d, year=%d, wday=%d\n", __func__, पंचांग->पंचांग_sec,
		पंचांग->पंचांग_min, पंचांग->पंचांग_hour, पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year,
		पंचांग->पंचांग_wday);

	अगर (s35390a_पढ़ो_status(s35390a, &status) == 1)
		s35390a_init(s35390a);

	buf[S35390A_BYTE_YEAR] = bin2bcd(पंचांग->पंचांग_year - 100);
	buf[S35390A_BYTE_MONTH] = bin2bcd(पंचांग->पंचांग_mon + 1);
	buf[S35390A_BYTE_DAY] = bin2bcd(पंचांग->पंचांग_mday);
	buf[S35390A_BYTE_WDAY] = bin2bcd(पंचांग->पंचांग_wday);
	buf[S35390A_BYTE_HOURS] = s35390a_hr2reg(s35390a, पंचांग->पंचांग_hour);
	buf[S35390A_BYTE_MINS] = bin2bcd(पंचांग->पंचांग_min);
	buf[S35390A_BYTE_SECS] = bin2bcd(पंचांग->पंचांग_sec);

	/* This chip expects the bits of each byte to be in reverse order */
	क्रम (i = 0; i < 7; ++i)
		buf[i] = bitrev8(buf[i]);

	err = s35390a_set_reg(s35390a, S35390A_CMD_TIME1, buf, माप(buf));

	वापस err;
पूर्ण

अटल पूर्णांक s35390a_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा s35390a *s35390a = i2c_get_clientdata(client);
	अक्षर buf[7], status;
	पूर्णांक i, err;

	अगर (s35390a_पढ़ो_status(s35390a, &status) == 1)
		वापस -EINVAL;

	err = s35390a_get_reg(s35390a, S35390A_CMD_TIME1, buf, माप(buf));
	अगर (err < 0)
		वापस err;

	/* This chip वापसs the bits of each byte in reverse order */
	क्रम (i = 0; i < 7; ++i)
		buf[i] = bitrev8(buf[i]);

	पंचांग->पंचांग_sec = bcd2bin(buf[S35390A_BYTE_SECS]);
	पंचांग->पंचांग_min = bcd2bin(buf[S35390A_BYTE_MINS]);
	पंचांग->पंचांग_hour = s35390a_reg2hr(s35390a, buf[S35390A_BYTE_HOURS]);
	पंचांग->पंचांग_wday = bcd2bin(buf[S35390A_BYTE_WDAY]);
	पंचांग->पंचांग_mday = bcd2bin(buf[S35390A_BYTE_DAY]);
	पंचांग->पंचांग_mon = bcd2bin(buf[S35390A_BYTE_MONTH]) - 1;
	पंचांग->पंचांग_year = bcd2bin(buf[S35390A_BYTE_YEAR]) + 100;

	dev_dbg(&client->dev, "%s: tm is secs=%d, mins=%d, hours=%d, mday=%d, "
		"mon=%d, year=%d, wday=%d\n", __func__, पंचांग->पंचांग_sec,
		पंचांग->पंचांग_min, पंचांग->पंचांग_hour, पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year,
		पंचांग->पंचांग_wday);

	वापस 0;
पूर्ण

अटल पूर्णांक s35390a_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा s35390a *s35390a = i2c_get_clientdata(client);
	अक्षर buf[3], sts = 0;
	पूर्णांक err, i;

	dev_dbg(&client->dev, "%s: alm is secs=%d, mins=%d, hours=%d mday=%d, "\
		"mon=%d, year=%d, wday=%d\n", __func__, alm->समय.पंचांग_sec,
		alm->समय.पंचांग_min, alm->समय.पंचांग_hour, alm->समय.पंचांग_mday,
		alm->समय.पंचांग_mon, alm->समय.पंचांग_year, alm->समय.पंचांग_wday);

	अगर (alm->समय.पंचांग_sec != 0)
		dev_warn(&client->dev, "Alarms are only supported on a per minute basis!\n");

	/* disable पूर्णांकerrupt (which deनिश्चितs the irq line) */
	err = s35390a_set_reg(s35390a, S35390A_CMD_STATUS2, &sts, माप(sts));
	अगर (err < 0)
		वापस err;

	/* clear pending पूर्णांकerrupt (in STATUS1 only), अगर any */
	err = s35390a_get_reg(s35390a, S35390A_CMD_STATUS1, &sts, माप(sts));
	अगर (err < 0)
		वापस err;

	अगर (alm->enabled)
		sts = S35390A_INT2_MODE_ALARM;
	अन्यथा
		sts = S35390A_INT2_MODE_NOINTR;

	/* set पूर्णांकerupt mode*/
	err = s35390a_set_reg(s35390a, S35390A_CMD_STATUS2, &sts, माप(sts));
	अगर (err < 0)
		वापस err;

	अगर (alm->समय.पंचांग_wday != -1)
		buf[S35390A_ALRM_BYTE_WDAY] = bin2bcd(alm->समय.पंचांग_wday) | 0x80;
	अन्यथा
		buf[S35390A_ALRM_BYTE_WDAY] = 0;

	buf[S35390A_ALRM_BYTE_HOURS] = s35390a_hr2reg(s35390a,
			alm->समय.पंचांग_hour) | 0x80;
	buf[S35390A_ALRM_BYTE_MINS] = bin2bcd(alm->समय.पंचांग_min) | 0x80;

	अगर (alm->समय.पंचांग_hour >= 12)
		buf[S35390A_ALRM_BYTE_HOURS] |= 0x40;

	क्रम (i = 0; i < 3; ++i)
		buf[i] = bitrev8(buf[i]);

	err = s35390a_set_reg(s35390a, S35390A_CMD_INT2_REG1, buf,
								माप(buf));

	वापस err;
पूर्ण

अटल पूर्णांक s35390a_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा s35390a *s35390a = i2c_get_clientdata(client);
	अक्षर buf[3], sts;
	पूर्णांक i, err;

	err = s35390a_get_reg(s35390a, S35390A_CMD_STATUS2, &sts, माप(sts));
	अगर (err < 0)
		वापस err;

	अगर ((sts & S35390A_INT2_MODE_MASK) != S35390A_INT2_MODE_ALARM) अणु
		/*
		 * When the alarm isn't enabled, the रेजिस्टर to configure
		 * the alarm समय isn't accessible.
		 */
		alm->enabled = 0;
		वापस 0;
	पूर्ण अन्यथा अणु
		alm->enabled = 1;
	पूर्ण

	err = s35390a_get_reg(s35390a, S35390A_CMD_INT2_REG1, buf, माप(buf));
	अगर (err < 0)
		वापस err;

	/* This chip वापसs the bits of each byte in reverse order */
	क्रम (i = 0; i < 3; ++i)
		buf[i] = bitrev8(buf[i]);

	/*
	 * B0 of the three matching रेजिस्टरs is an enable flag. Iff it is set
	 * the configured value is used क्रम matching.
	 */
	अगर (buf[S35390A_ALRM_BYTE_WDAY] & 0x80)
		alm->समय.पंचांग_wday =
			bcd2bin(buf[S35390A_ALRM_BYTE_WDAY] & ~0x80);

	अगर (buf[S35390A_ALRM_BYTE_HOURS] & 0x80)
		alm->समय.पंचांग_hour =
			s35390a_reg2hr(s35390a,
				       buf[S35390A_ALRM_BYTE_HOURS] & ~0x80);

	अगर (buf[S35390A_ALRM_BYTE_MINS] & 0x80)
		alm->समय.पंचांग_min = bcd2bin(buf[S35390A_ALRM_BYTE_MINS] & ~0x80);

	/* alarm triggers always at s=0 */
	alm->समय.पंचांग_sec = 0;

	dev_dbg(&client->dev, "%s: alm is mins=%d, hours=%d, wday=%d\n",
			__func__, alm->समय.पंचांग_min, alm->समय.पंचांग_hour,
			alm->समय.पंचांग_wday);

	वापस 0;
पूर्ण

अटल पूर्णांक s35390a_rtc_ioctl(काष्ठा device *dev, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा s35390a *s35390a = i2c_get_clientdata(client);
	अक्षर sts;
	पूर्णांक err;

	चयन (cmd) अणु
	हाल RTC_VL_READ:
		/* s35390a_reset set lowvoltage flag and init RTC अगर needed */
		err = s35390a_पढ़ो_status(s35390a, &sts);
		अगर (err < 0)
			वापस err;
		अगर (copy_to_user((व्योम __user *)arg, &err, माप(पूर्णांक)))
			वापस -EFAULT;
		अवरोध;
	हाल RTC_VL_CLR:
		/* update flag and clear रेजिस्टर */
		err = s35390a_init(s35390a);
		अगर (err < 0)
			वापस err;
		अवरोध;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops s35390a_rtc_ops = अणु
	.पढ़ो_समय	= s35390a_rtc_पढ़ो_समय,
	.set_समय	= s35390a_rtc_set_समय,
	.set_alarm	= s35390a_rtc_set_alarm,
	.पढ़ो_alarm	= s35390a_rtc_पढ़ो_alarm,
	.ioctl          = s35390a_rtc_ioctl,
पूर्ण;

अटल पूर्णांक s35390a_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक err, err_पढ़ो;
	अचिन्हित पूर्णांक i;
	काष्ठा s35390a *s35390a;
	अक्षर buf, status1;
	काष्ठा device *dev = &client->dev;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	s35390a = devm_kzalloc(dev, माप(काष्ठा s35390a), GFP_KERNEL);
	अगर (!s35390a)
		वापस -ENOMEM;

	s35390a->client[0] = client;
	i2c_set_clientdata(client, s35390a);

	/* This chip uses multiple addresses, use dummy devices क्रम them */
	क्रम (i = 1; i < 8; ++i) अणु
		s35390a->client[i] = devm_i2c_new_dummy_device(dev,
							       client->adapter,
							       client->addr + i);
		अगर (IS_ERR(s35390a->client[i])) अणु
			dev_err(dev, "Address %02x unavailable\n",
				client->addr + i);
			वापस PTR_ERR(s35390a->client[i]);
		पूर्ण
	पूर्ण

	s35390a->rtc = devm_rtc_allocate_device(dev);
	अगर (IS_ERR(s35390a->rtc))
		वापस PTR_ERR(s35390a->rtc);

	err_पढ़ो = s35390a_पढ़ो_status(s35390a, &status1);
	अगर (err_पढ़ो < 0) अणु
		dev_err(dev, "error resetting chip\n");
		वापस err_पढ़ो;
	पूर्ण

	अगर (status1 & S35390A_FLAG_24H)
		s35390a->twentyfourhour = 1;
	अन्यथा
		s35390a->twentyfourhour = 0;

	अगर (status1 & S35390A_FLAG_INT2) अणु
		/* disable alarm (and maybe test mode) */
		buf = 0;
		err = s35390a_set_reg(s35390a, S35390A_CMD_STATUS2, &buf, 1);
		अगर (err < 0) अणु
			dev_err(dev, "error disabling alarm");
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = s35390a_disable_test_mode(s35390a);
		अगर (err < 0) अणु
			dev_err(dev, "error disabling test mode\n");
			वापस err;
		पूर्ण
	पूर्ण

	device_set_wakeup_capable(dev, 1);

	s35390a->rtc->ops = &s35390a_rtc_ops;
	s35390a->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	s35390a->rtc->range_max = RTC_TIMESTAMP_END_2099;

	/* supports per-minute alarms only, thereक्रमe set uie_unsupported */
	s35390a->rtc->uie_unsupported = 1;

	अगर (status1 & S35390A_FLAG_INT2)
		rtc_update_irq(s35390a->rtc, 1, RTC_AF);

	वापस devm_rtc_रेजिस्टर_device(s35390a->rtc);
पूर्ण

अटल काष्ठा i2c_driver s35390a_driver = अणु
	.driver		= अणु
		.name	= "rtc-s35390a",
		.of_match_table = of_match_ptr(s35390a_of_match),
	पूर्ण,
	.probe		= s35390a_probe,
	.id_table	= s35390a_id,
पूर्ण;

module_i2c_driver(s35390a_driver);

MODULE_AUTHOR("Byron Bradley <byron.bbradley@gmail.com>");
MODULE_DESCRIPTION("S35390A RTC driver");
MODULE_LICENSE("GPL");
