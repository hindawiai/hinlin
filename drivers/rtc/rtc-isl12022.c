<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An I2C driver क्रम the Intersil ISL 12022
 *
 * Author: Roman Fietze <roman.fietze@telemotive.de>
 *
 * Based on the Philips PCF8563 RTC
 * by Alessandro Zummo <a.zummo@towertech.it>.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/bcd.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

/* ISL रेजिस्टर offsets */
#घोषणा ISL12022_REG_SC		0x00
#घोषणा ISL12022_REG_MN		0x01
#घोषणा ISL12022_REG_HR		0x02
#घोषणा ISL12022_REG_DT		0x03
#घोषणा ISL12022_REG_MO		0x04
#घोषणा ISL12022_REG_YR		0x05
#घोषणा ISL12022_REG_DW		0x06

#घोषणा ISL12022_REG_SR		0x07
#घोषणा ISL12022_REG_INT	0x08

/* ISL रेजिस्टर bits */
#घोषणा ISL12022_HR_MIL		(1 << 7)	/* military or 24 hour समय */

#घोषणा ISL12022_SR_LBAT85	(1 << 2)
#घोषणा ISL12022_SR_LBAT75	(1 << 1)

#घोषणा ISL12022_INT_WRTC	(1 << 6)


अटल काष्ठा i2c_driver isl12022_driver;

काष्ठा isl12022 अणु
	काष्ठा rtc_device *rtc;

	bool ग_लिखो_enabled;	/* true अगर ग_लिखो enable is set */
पूर्ण;


अटल पूर्णांक isl12022_पढ़ो_regs(काष्ठा i2c_client *client, uपूर्णांक8_t reg,
			      uपूर्णांक8_t *data, माप_प्रकार n)
अणु
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr	= client->addr,
			.flags	= 0,
			.len	= 1,
			.buf	= data
		पूर्ण,		/* setup पढ़ो ptr */
		अणु
			.addr	= client->addr,
			.flags	= I2C_M_RD,
			.len	= n,
			.buf	= data
		पूर्ण
	पूर्ण;

	पूर्णांक ret;

	data[0] = reg;
	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret != ARRAY_SIZE(msgs)) अणु
		dev_err(&client->dev, "%s: read error, ret=%d\n",
			__func__, ret);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक isl12022_ग_लिखो_reg(काष्ठा i2c_client *client,
			      uपूर्णांक8_t reg, uपूर्णांक8_t val)
अणु
	uपूर्णांक8_t data[2] = अणु reg, val पूर्ण;
	पूर्णांक err;

	err = i2c_master_send(client, data, माप(data));
	अगर (err != माप(data)) अणु
		dev_err(&client->dev,
			"%s: err=%d addr=%02x, data=%02x\n",
			__func__, err, data[0], data[1]);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * In the routines that deal directly with the isl12022 hardware, we use
 * rtc_समय -- month 0-11, hour 0-23, yr = calendar year-epoch.
 */
अटल पूर्णांक isl12022_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	uपूर्णांक8_t buf[ISL12022_REG_INT + 1];
	पूर्णांक ret;

	ret = isl12022_पढ़ो_regs(client, ISL12022_REG_SC, buf, माप(buf));
	अगर (ret)
		वापस ret;

	अगर (buf[ISL12022_REG_SR] & (ISL12022_SR_LBAT85 | ISL12022_SR_LBAT75)) अणु
		dev_warn(&client->dev,
			 "voltage dropped below %u%%, "
			 "date and time is not reliable.\n",
			 buf[ISL12022_REG_SR] & ISL12022_SR_LBAT85 ? 85 : 75);
	पूर्ण

	dev_dbg(&client->dev,
		"%s: raw data is sec=%02x, min=%02x, hr=%02x, "
		"mday=%02x, mon=%02x, year=%02x, wday=%02x, "
		"sr=%02x, int=%02x",
		__func__,
		buf[ISL12022_REG_SC],
		buf[ISL12022_REG_MN],
		buf[ISL12022_REG_HR],
		buf[ISL12022_REG_DT],
		buf[ISL12022_REG_MO],
		buf[ISL12022_REG_YR],
		buf[ISL12022_REG_DW],
		buf[ISL12022_REG_SR],
		buf[ISL12022_REG_INT]);

	पंचांग->पंचांग_sec = bcd2bin(buf[ISL12022_REG_SC] & 0x7F);
	पंचांग->पंचांग_min = bcd2bin(buf[ISL12022_REG_MN] & 0x7F);
	पंचांग->पंचांग_hour = bcd2bin(buf[ISL12022_REG_HR] & 0x3F);
	पंचांग->पंचांग_mday = bcd2bin(buf[ISL12022_REG_DT] & 0x3F);
	पंचांग->पंचांग_wday = buf[ISL12022_REG_DW] & 0x07;
	पंचांग->पंचांग_mon = bcd2bin(buf[ISL12022_REG_MO] & 0x1F) - 1;
	पंचांग->पंचांग_year = bcd2bin(buf[ISL12022_REG_YR]) + 100;

	dev_dbg(&client->dev, "%s: secs=%d, mins=%d, hours=%d, "
		"mday=%d, mon=%d, year=%d, wday=%d\n",
		__func__,
		पंचांग->पंचांग_sec, पंचांग->पंचांग_min, पंचांग->पंचांग_hour,
		पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	वापस 0;
पूर्ण

अटल पूर्णांक isl12022_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा isl12022 *isl12022 = i2c_get_clientdata(client);
	माप_प्रकार i;
	पूर्णांक ret;
	uपूर्णांक8_t buf[ISL12022_REG_DW + 1];

	dev_dbg(&client->dev, "%s: secs=%d, mins=%d, hours=%d, "
		"mday=%d, mon=%d, year=%d, wday=%d\n",
		__func__,
		पंचांग->पंचांग_sec, पंचांग->पंचांग_min, पंचांग->पंचांग_hour,
		पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	अगर (!isl12022->ग_लिखो_enabled) अणु

		ret = isl12022_पढ़ो_regs(client, ISL12022_REG_INT, buf, 1);
		अगर (ret)
			वापस ret;

		/* Check अगर WRTC (ग_लिखो rtc enable) is set factory शेष is
		 * 0 (not set) */
		अगर (!(buf[0] & ISL12022_INT_WRTC)) अणु
			dev_info(&client->dev,
				 "init write enable and 24 hour format\n");

			/* Set the ग_लिखो enable bit. */
			ret = isl12022_ग_लिखो_reg(client,
						 ISL12022_REG_INT,
						 buf[0] | ISL12022_INT_WRTC);
			अगर (ret)
				वापस ret;

			/* Write to any RTC रेजिस्टर to start RTC, we use the
			 * HR रेजिस्टर, setting the MIL bit to use the 24 hour
			 * क्रमmat. */
			ret = isl12022_पढ़ो_regs(client, ISL12022_REG_HR,
						 buf, 1);
			अगर (ret)
				वापस ret;

			ret = isl12022_ग_लिखो_reg(client,
						 ISL12022_REG_HR,
						 buf[0] | ISL12022_HR_MIL);
			अगर (ret)
				वापस ret;
		पूर्ण

		isl12022->ग_लिखो_enabled = true;
	पूर्ण

	/* hours, minutes and seconds */
	buf[ISL12022_REG_SC] = bin2bcd(पंचांग->पंचांग_sec);
	buf[ISL12022_REG_MN] = bin2bcd(पंचांग->पंचांग_min);
	buf[ISL12022_REG_HR] = bin2bcd(पंचांग->पंचांग_hour) | ISL12022_HR_MIL;

	buf[ISL12022_REG_DT] = bin2bcd(पंचांग->पंचांग_mday);

	/* month, 1 - 12 */
	buf[ISL12022_REG_MO] = bin2bcd(पंचांग->पंचांग_mon + 1);

	/* year and century */
	buf[ISL12022_REG_YR] = bin2bcd(पंचांग->पंचांग_year % 100);

	buf[ISL12022_REG_DW] = पंचांग->पंचांग_wday & 0x07;

	/* ग_लिखो रेजिस्टर's data */
	क्रम (i = 0; i < ARRAY_SIZE(buf); i++) अणु
		ret = isl12022_ग_लिखो_reg(client, ISL12022_REG_SC + i,
					 buf[ISL12022_REG_SC + i]);
		अगर (ret)
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops isl12022_rtc_ops = अणु
	.पढ़ो_समय	= isl12022_rtc_पढ़ो_समय,
	.set_समय	= isl12022_rtc_set_समय,
पूर्ण;

अटल पूर्णांक isl12022_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा isl12022 *isl12022;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	isl12022 = devm_kzalloc(&client->dev, माप(काष्ठा isl12022),
				GFP_KERNEL);
	अगर (!isl12022)
		वापस -ENOMEM;

	i2c_set_clientdata(client, isl12022);

	isl12022->rtc = devm_rtc_device_रेजिस्टर(&client->dev,
					isl12022_driver.driver.name,
					&isl12022_rtc_ops, THIS_MODULE);
	वापस PTR_ERR_OR_ZERO(isl12022->rtc);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id isl12022_dt_match[] = अणु
	अणु .compatible = "isl,isl12022" पूर्ण, /* क्रम backward compat., करोn't use */
	अणु .compatible = "isil,isl12022" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, isl12022_dt_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id isl12022_id[] = अणु
	अणु "isl12022", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, isl12022_id);

अटल काष्ठा i2c_driver isl12022_driver = अणु
	.driver		= अणु
		.name	= "rtc-isl12022",
#अगर_घोषित CONFIG_OF
		.of_match_table = of_match_ptr(isl12022_dt_match),
#पूर्ण_अगर
	पूर्ण,
	.probe		= isl12022_probe,
	.id_table	= isl12022_id,
पूर्ण;

module_i2c_driver(isl12022_driver);

MODULE_AUTHOR("roman.fietze@telemotive.de");
MODULE_DESCRIPTION("ISL 12022 RTC driver");
MODULE_LICENSE("GPL");
