<शैली गुरु>
/*
 * rtc class driver क्रम the Maxim MAX6900 chip
 *
 * Author: Dale Farnsworth <dale@farnsworth.org>
 *
 * based on previously existing rtc class drivers
 *
 * 2007 (c) MontaVista, Software, Inc.  This file is licensed under
 * the terms of the GNU General Public License version 2.  This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/bcd.h>
#समावेश <linux/rtc.h>
#समावेश <linux/delay.h>

/*
 * रेजिस्टर indices
 */
#घोषणा MAX6900_REG_SC			0	/* seconds      00-59 */
#घोषणा MAX6900_REG_MN			1	/* minutes      00-59 */
#घोषणा MAX6900_REG_HR			2	/* hours        00-23 */
#घोषणा MAX6900_REG_DT			3	/* day of month 00-31 */
#घोषणा MAX6900_REG_MO			4	/* month        01-12 */
#घोषणा MAX6900_REG_DW			5	/* day of week   1-7  */
#घोषणा MAX6900_REG_YR			6	/* year         00-99 */
#घोषणा MAX6900_REG_CT			7	/* control */
						/* रेजिस्टर 8 is unकरोcumented */
#घोषणा MAX6900_REG_CENTURY		9	/* century */
#घोषणा MAX6900_REG_LEN			10

#घोषणा MAX6900_BURST_LEN		8	/* can burst r/w first 8 regs */

#घोषणा MAX6900_REG_CT_WP		(1 << 7)	/* Write Protect */

/*
 * रेजिस्टर पढ़ो/ग_लिखो commands
 */
#घोषणा MAX6900_REG_CONTROL_WRITE	0x8e
#घोषणा MAX6900_REG_CENTURY_WRITE	0x92
#घोषणा MAX6900_REG_CENTURY_READ	0x93
#घोषणा MAX6900_REG_RESERVED_READ	0x96
#घोषणा MAX6900_REG_BURST_WRITE		0xbe
#घोषणा MAX6900_REG_BURST_READ		0xbf

#घोषणा MAX6900_IDLE_TIME_AFTER_WRITE	3	/* specअगरication says 2.5 mS */

अटल काष्ठा i2c_driver max6900_driver;

अटल पूर्णांक max6900_i2c_पढ़ो_regs(काष्ठा i2c_client *client, u8 *buf)
अणु
	u8 reg_burst_पढ़ो[1] = अणु MAX6900_REG_BURST_READ पूर्ण;
	u8 reg_century_पढ़ो[1] = अणु MAX6900_REG_CENTURY_READ पूर्ण;
	काष्ठा i2c_msg msgs[4] = अणु
		अणु
		 .addr = client->addr,
		 .flags = 0,	/* ग_लिखो */
		 .len = माप(reg_burst_पढ़ो),
		 .buf = reg_burst_पढ़ोपूर्ण
		,
		अणु
		 .addr = client->addr,
		 .flags = I2C_M_RD,
		 .len = MAX6900_BURST_LEN,
		 .buf = bufपूर्ण
		,
		अणु
		 .addr = client->addr,
		 .flags = 0,	/* ग_लिखो */
		 .len = माप(reg_century_पढ़ो),
		 .buf = reg_century_पढ़ोपूर्ण
		,
		अणु
		 .addr = client->addr,
		 .flags = I2C_M_RD,
		 .len = माप(buf[MAX6900_REG_CENTURY]),
		 .buf = &buf[MAX6900_REG_CENTURY]
		 पूर्ण
	पूर्ण;
	पूर्णांक rc;

	rc = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (rc != ARRAY_SIZE(msgs)) अणु
		dev_err(&client->dev, "%s: register read failed\n", __func__);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max6900_i2c_ग_लिखो_regs(काष्ठा i2c_client *client, u8 स्थिर *buf)
अणु
	u8 i2c_century_buf[1 + 1] = अणु MAX6900_REG_CENTURY_WRITE पूर्ण;
	काष्ठा i2c_msg century_msgs[1] = अणु
		अणु
		 .addr = client->addr,
		 .flags = 0,	/* ग_लिखो */
		 .len = माप(i2c_century_buf),
		 .buf = i2c_century_bufपूर्ण
	पूर्ण;
	u8 i2c_burst_buf[MAX6900_BURST_LEN + 1] = अणु MAX6900_REG_BURST_WRITE पूर्ण;
	काष्ठा i2c_msg burst_msgs[1] = अणु
		अणु
		 .addr = client->addr,
		 .flags = 0,	/* ग_लिखो */
		 .len = माप(i2c_burst_buf),
		 .buf = i2c_burst_bufपूर्ण
	पूर्ण;
	पूर्णांक rc;

	/*
	 * We have to make separate calls to i2c_transfer because of
	 * the need to delay after each ग_लिखो to the chip.  Also,
	 * we ग_लिखो the century byte first, since we set the ग_लिखो-protect
	 * bit as part of the burst ग_लिखो.
	 */
	i2c_century_buf[1] = buf[MAX6900_REG_CENTURY];

	rc = i2c_transfer(client->adapter, century_msgs,
			  ARRAY_SIZE(century_msgs));
	अगर (rc != ARRAY_SIZE(century_msgs))
		जाओ ग_लिखो_failed;

	msleep(MAX6900_IDLE_TIME_AFTER_WRITE);

	स_नकल(&i2c_burst_buf[1], buf, MAX6900_BURST_LEN);

	rc = i2c_transfer(client->adapter, burst_msgs, ARRAY_SIZE(burst_msgs));
	अगर (rc != ARRAY_SIZE(burst_msgs))
		जाओ ग_लिखो_failed;
	msleep(MAX6900_IDLE_TIME_AFTER_WRITE);

	वापस 0;

 ग_लिखो_failed:
	dev_err(&client->dev, "%s: register write failed\n", __func__);
	वापस -EIO;
पूर्ण

अटल पूर्णांक max6900_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक rc;
	u8 regs[MAX6900_REG_LEN];

	rc = max6900_i2c_पढ़ो_regs(client, regs);
	अगर (rc < 0)
		वापस rc;

	पंचांग->पंचांग_sec = bcd2bin(regs[MAX6900_REG_SC]);
	पंचांग->पंचांग_min = bcd2bin(regs[MAX6900_REG_MN]);
	पंचांग->पंचांग_hour = bcd2bin(regs[MAX6900_REG_HR] & 0x3f);
	पंचांग->पंचांग_mday = bcd2bin(regs[MAX6900_REG_DT]);
	पंचांग->पंचांग_mon = bcd2bin(regs[MAX6900_REG_MO]) - 1;
	पंचांग->पंचांग_year = bcd2bin(regs[MAX6900_REG_YR]) +
		      bcd2bin(regs[MAX6900_REG_CENTURY]) * 100 - 1900;
	पंचांग->पंचांग_wday = bcd2bin(regs[MAX6900_REG_DW]);

	वापस 0;
पूर्ण

अटल पूर्णांक max6900_i2c_clear_ग_लिखो_protect(काष्ठा i2c_client *client)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, MAX6900_REG_CONTROL_WRITE, 0);
पूर्ण

अटल पूर्णांक max6900_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u8 regs[MAX6900_REG_LEN];
	पूर्णांक rc;

	rc = max6900_i2c_clear_ग_लिखो_protect(client);
	अगर (rc < 0)
		वापस rc;

	regs[MAX6900_REG_SC] = bin2bcd(पंचांग->पंचांग_sec);
	regs[MAX6900_REG_MN] = bin2bcd(पंचांग->पंचांग_min);
	regs[MAX6900_REG_HR] = bin2bcd(पंचांग->पंचांग_hour);
	regs[MAX6900_REG_DT] = bin2bcd(पंचांग->पंचांग_mday);
	regs[MAX6900_REG_MO] = bin2bcd(पंचांग->पंचांग_mon + 1);
	regs[MAX6900_REG_DW] = bin2bcd(पंचांग->पंचांग_wday);
	regs[MAX6900_REG_YR] = bin2bcd(पंचांग->पंचांग_year % 100);
	regs[MAX6900_REG_CENTURY] = bin2bcd((पंचांग->पंचांग_year + 1900) / 100);
	/* set ग_लिखो protect */
	regs[MAX6900_REG_CT] = MAX6900_REG_CT_WP;

	rc = max6900_i2c_ग_लिखो_regs(client, regs);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops max6900_rtc_ops = अणु
	.पढ़ो_समय = max6900_rtc_पढ़ो_समय,
	.set_समय = max6900_rtc_set_समय,
पूर्ण;

अटल पूर्णांक
max6900_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rtc_device *rtc;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	rtc = devm_rtc_device_रेजिस्टर(&client->dev, max6900_driver.driver.name,
					&max6900_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	i2c_set_clientdata(client, rtc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max6900_id[] = अणु
	अणु "max6900", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max6900_id);

अटल काष्ठा i2c_driver max6900_driver = अणु
	.driver = अणु
		   .name = "rtc-max6900",
		   पूर्ण,
	.probe = max6900_probe,
	.id_table = max6900_id,
पूर्ण;

module_i2c_driver(max6900_driver);

MODULE_DESCRIPTION("Maxim MAX6900 RTC driver");
MODULE_AUTHOR("Dale Farnsworth <dale@farnsworth.org>");
MODULE_LICENSE("GPL");
