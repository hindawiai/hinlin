<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  drivers/rtc/rtc-pcf8583.c
 *
 *  Copyright (C) 2000 Russell King
 *  Copyright (C) 2008 Wolfram Sang & Juergen Beisert, Pengutronix
 *
 *  Driver क्रम PCF8583 RTC & RAM chip
 *
 *  Converted to the generic RTC susbप्रणाली by G. Liakhovetski (2006)
 */
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/rtc.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bcd.h>

काष्ठा rtc_mem अणु
	अचिन्हित पूर्णांक	loc;
	अचिन्हित पूर्णांक	nr;
	अचिन्हित अक्षर	*data;
पूर्ण;

काष्ठा pcf8583 अणु
	काष्ठा rtc_device *rtc;
	अचिन्हित अक्षर ctrl;
पूर्ण;

#घोषणा CTRL_STOP	0x80
#घोषणा CTRL_HOLD	0x40
#घोषणा CTRL_32KHZ	0x00
#घोषणा CTRL_MASK	0x08
#घोषणा CTRL_ALARMEN	0x04
#घोषणा CTRL_ALARM	0x02
#घोषणा CTRL_TIMER	0x01


अटल काष्ठा i2c_driver pcf8583_driver;

#घोषणा get_ctrl(x)    ((काष्ठा pcf8583 *)i2c_get_clientdata(x))->ctrl
#घोषणा set_ctrl(x, v) get_ctrl(x) = v

#घोषणा CMOS_YEAR	(64 + 128)
#घोषणा CMOS_CHECKSUM	(63)

अटल पूर्णांक pcf8583_get_dateसमय(काष्ठा i2c_client *client, काष्ठा rtc_समय *dt)
अणु
	अचिन्हित अक्षर buf[8], addr[1] = अणु 1 पूर्ण;
	काष्ठा i2c_msg msgs[2] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = 1,
			.buf = addr,
		पूर्ण, अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 6,
			.buf = buf,
		पूर्ण
	पूर्ण;
	पूर्णांक ret;

	स_रखो(buf, 0, माप(buf));

	ret = i2c_transfer(client->adapter, msgs, 2);
	अगर (ret == 2) अणु
		dt->पंचांग_year = buf[4] >> 6;
		dt->पंचांग_wday = buf[5] >> 5;

		buf[4] &= 0x3f;
		buf[5] &= 0x1f;

		dt->पंचांग_sec = bcd2bin(buf[1]);
		dt->पंचांग_min = bcd2bin(buf[2]);
		dt->पंचांग_hour = bcd2bin(buf[3]);
		dt->पंचांग_mday = bcd2bin(buf[4]);
		dt->पंचांग_mon = bcd2bin(buf[5]) - 1;
	पूर्ण

	वापस ret == 2 ? 0 : -EIO;
पूर्ण

अटल पूर्णांक pcf8583_set_dateसमय(काष्ठा i2c_client *client, काष्ठा rtc_समय *dt, पूर्णांक datetoo)
अणु
	अचिन्हित अक्षर buf[8];
	पूर्णांक ret, len = 6;

	buf[0] = 0;
	buf[1] = get_ctrl(client) | 0x80;
	buf[2] = 0;
	buf[3] = bin2bcd(dt->पंचांग_sec);
	buf[4] = bin2bcd(dt->पंचांग_min);
	buf[5] = bin2bcd(dt->पंचांग_hour);

	अगर (datetoo) अणु
		len = 8;
		buf[6] = bin2bcd(dt->पंचांग_mday) | (dt->पंचांग_year << 6);
		buf[7] = bin2bcd(dt->पंचांग_mon + 1)  | (dt->पंचांग_wday << 5);
	पूर्ण

	ret = i2c_master_send(client, (अक्षर *)buf, len);
	अगर (ret != len)
		वापस -EIO;

	buf[1] = get_ctrl(client);
	ret = i2c_master_send(client, (अक्षर *)buf, 2);

	वापस ret == 2 ? 0 : -EIO;
पूर्ण

अटल पूर्णांक pcf8583_get_ctrl(काष्ठा i2c_client *client, अचिन्हित अक्षर *ctrl)
अणु
	*ctrl = get_ctrl(client);
	वापस 0;
पूर्ण

अटल पूर्णांक pcf8583_set_ctrl(काष्ठा i2c_client *client, अचिन्हित अक्षर *ctrl)
अणु
	अचिन्हित अक्षर buf[2];

	buf[0] = 0;
	buf[1] = *ctrl;
	set_ctrl(client, *ctrl);

	वापस i2c_master_send(client, (अक्षर *)buf, 2);
पूर्ण

अटल पूर्णांक pcf8583_पढ़ो_mem(काष्ठा i2c_client *client, काष्ठा rtc_mem *mem)
अणु
	अचिन्हित अक्षर addr[1];
	काष्ठा i2c_msg msgs[2] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = 1,
			.buf = addr,
		पूर्ण, अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = mem->nr,
			.buf = mem->data,
		पूर्ण
	पूर्ण;

	अगर (mem->loc < 8)
		वापस -EINVAL;

	addr[0] = mem->loc;

	वापस i2c_transfer(client->adapter, msgs, 2) == 2 ? 0 : -EIO;
पूर्ण

अटल पूर्णांक pcf8583_ग_लिखो_mem(काष्ठा i2c_client *client, काष्ठा rtc_mem *mem)
अणु
	अचिन्हित अक्षर buf[9];
	पूर्णांक ret;

	अगर (mem->loc < 8 || mem->nr > 8)
		वापस -EINVAL;

	buf[0] = mem->loc;
	स_नकल(buf + 1, mem->data, mem->nr);

	ret = i2c_master_send(client, buf, mem->nr + 1);
	वापस ret == mem->nr + 1 ? 0 : -EIO;
पूर्ण

अटल पूर्णांक pcf8583_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित अक्षर ctrl, year[2];
	काष्ठा rtc_mem mem = अणु
		.loc = CMOS_YEAR,
		.nr = माप(year),
		.data = year
	पूर्ण;
	पूर्णांक real_year, year_offset, err;

	/*
	 * Ensure that the RTC is running.
	 */
	pcf8583_get_ctrl(client, &ctrl);
	अगर (ctrl & (CTRL_STOP | CTRL_HOLD)) अणु
		अचिन्हित अक्षर new_ctrl = ctrl & ~(CTRL_STOP | CTRL_HOLD);

		dev_warn(dev, "resetting control %02x -> %02x\n",
			ctrl, new_ctrl);

		err = pcf8583_set_ctrl(client, &new_ctrl);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (pcf8583_get_dateसमय(client, पंचांग) ||
	    pcf8583_पढ़ो_mem(client, &mem))
		वापस -EIO;

	real_year = year[0];

	/*
	 * The RTC year holds the LSB two bits of the current
	 * year, which should reflect the LSB two bits of the
	 * CMOS copy of the year.  Any dअगरference indicates
	 * that we have to correct the CMOS version.
	 */
	year_offset = पंचांग->पंचांग_year - (real_year & 3);
	अगर (year_offset < 0)
		/*
		 * RTC year wrapped.  Adjust it appropriately.
		 */
		year_offset += 4;

	पंचांग->पंचांग_year = (real_year + year_offset + year[1] * 100) - 1900;

	वापस 0;
पूर्ण

अटल पूर्णांक pcf8583_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित अक्षर year[2], chk;
	काष्ठा rtc_mem cmos_year  = अणु
		.loc = CMOS_YEAR,
		.nr = माप(year),
		.data = year
	पूर्ण;
	काष्ठा rtc_mem cmos_check = अणु
		.loc = CMOS_CHECKSUM,
		.nr = 1,
		.data = &chk
	पूर्ण;
	अचिन्हित पूर्णांक proper_year = पंचांग->पंचांग_year + 1900;
	पूर्णांक ret;

	/*
	 * The RTC's own 2-bit year must reflect the least
	 * signअगरicant two bits of the CMOS year.
	 */

	ret = pcf8583_set_dateसमय(client, पंचांग, 1);
	अगर (ret)
		वापस ret;

	ret = pcf8583_पढ़ो_mem(client, &cmos_check);
	अगर (ret)
		वापस ret;

	ret = pcf8583_पढ़ो_mem(client, &cmos_year);
	अगर (ret)
		वापस ret;

	chk -= year[1] + year[0];

	year[1] = proper_year / 100;
	year[0] = proper_year % 100;

	chk += year[1] + year[0];

	ret = pcf8583_ग_लिखो_mem(client, &cmos_year);

	अगर (ret)
		वापस ret;

	ret = pcf8583_ग_लिखो_mem(client, &cmos_check);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops pcf8583_rtc_ops = अणु
	.पढ़ो_समय	= pcf8583_rtc_पढ़ो_समय,
	.set_समय	= pcf8583_rtc_set_समय,
पूर्ण;

अटल पूर्णांक pcf8583_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा pcf8583 *pcf8583;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	pcf8583 = devm_kzalloc(&client->dev, माप(काष्ठा pcf8583),
				GFP_KERNEL);
	अगर (!pcf8583)
		वापस -ENOMEM;

	i2c_set_clientdata(client, pcf8583);

	pcf8583->rtc = devm_rtc_device_रेजिस्टर(&client->dev,
				pcf8583_driver.driver.name,
				&pcf8583_rtc_ops, THIS_MODULE);

	वापस PTR_ERR_OR_ZERO(pcf8583->rtc);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pcf8583_id[] = अणु
	अणु "pcf8583", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pcf8583_id);

अटल काष्ठा i2c_driver pcf8583_driver = अणु
	.driver = अणु
		.name	= "pcf8583",
	पूर्ण,
	.probe		= pcf8583_probe,
	.id_table	= pcf8583_id,
पूर्ण;

module_i2c_driver(pcf8583_driver);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("PCF8583 I2C RTC driver");
MODULE_LICENSE("GPL");
