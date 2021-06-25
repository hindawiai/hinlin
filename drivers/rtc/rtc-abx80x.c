<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * A driver क्रम the I2C members of the Abracon AB x8xx RTC family,
 * and compatible: AB 1805 and AB 0805
 *
 * Copyright 2014-2015 Macq S.A.
 *
 * Author: Philippe De Muyter <phdm@macqel.be>
 * Author: Alexandre Belloni <alexandre.belloni@bootlin.com>
 *
 */

#समावेश <linux/bcd.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/watchकरोg.h>

#घोषणा ABX8XX_REG_HTH		0x00
#घोषणा ABX8XX_REG_SC		0x01
#घोषणा ABX8XX_REG_MN		0x02
#घोषणा ABX8XX_REG_HR		0x03
#घोषणा ABX8XX_REG_DA		0x04
#घोषणा ABX8XX_REG_MO		0x05
#घोषणा ABX8XX_REG_YR		0x06
#घोषणा ABX8XX_REG_WD		0x07

#घोषणा ABX8XX_REG_AHTH		0x08
#घोषणा ABX8XX_REG_ASC		0x09
#घोषणा ABX8XX_REG_AMN		0x0a
#घोषणा ABX8XX_REG_AHR		0x0b
#घोषणा ABX8XX_REG_ADA		0x0c
#घोषणा ABX8XX_REG_AMO		0x0d
#घोषणा ABX8XX_REG_AWD		0x0e

#घोषणा ABX8XX_REG_STATUS	0x0f
#घोषणा ABX8XX_STATUS_AF	BIT(2)
#घोषणा ABX8XX_STATUS_BLF	BIT(4)
#घोषणा ABX8XX_STATUS_WDT	BIT(6)

#घोषणा ABX8XX_REG_CTRL1	0x10
#घोषणा ABX8XX_CTRL_WRITE	BIT(0)
#घोषणा ABX8XX_CTRL_ARST	BIT(2)
#घोषणा ABX8XX_CTRL_12_24	BIT(6)

#घोषणा ABX8XX_REG_CTRL2	0x11
#घोषणा ABX8XX_CTRL2_RSVD	BIT(5)

#घोषणा ABX8XX_REG_IRQ		0x12
#घोषणा ABX8XX_IRQ_AIE		BIT(2)
#घोषणा ABX8XX_IRQ_IM_1_4	(0x3 << 5)

#घोषणा ABX8XX_REG_CD_TIMER_CTL	0x18

#घोषणा ABX8XX_REG_OSC		0x1c
#घोषणा ABX8XX_OSC_FOS		BIT(3)
#घोषणा ABX8XX_OSC_BOS		BIT(4)
#घोषणा ABX8XX_OSC_ACAL_512	BIT(5)
#घोषणा ABX8XX_OSC_ACAL_1024	BIT(6)

#घोषणा ABX8XX_OSC_OSEL		BIT(7)

#घोषणा ABX8XX_REG_OSS		0x1d
#घोषणा ABX8XX_OSS_OF		BIT(1)
#घोषणा ABX8XX_OSS_OMODE	BIT(4)

#घोषणा ABX8XX_REG_WDT		0x1b
#घोषणा ABX8XX_WDT_WDS		BIT(7)
#घोषणा ABX8XX_WDT_BMB_MASK	0x7c
#घोषणा ABX8XX_WDT_BMB_SHIFT	2
#घोषणा ABX8XX_WDT_MAX_TIME	(ABX8XX_WDT_BMB_MASK >> ABX8XX_WDT_BMB_SHIFT)
#घोषणा ABX8XX_WDT_WRB_MASK	0x03
#घोषणा ABX8XX_WDT_WRB_1HZ	0x02

#घोषणा ABX8XX_REG_CFG_KEY	0x1f
#घोषणा ABX8XX_CFG_KEY_OSC	0xa1
#घोषणा ABX8XX_CFG_KEY_MISC	0x9d

#घोषणा ABX8XX_REG_ID0		0x28

#घोषणा ABX8XX_REG_OUT_CTRL	0x30
#घोषणा ABX8XX_OUT_CTRL_EXDS	BIT(4)

#घोषणा ABX8XX_REG_TRICKLE	0x20
#घोषणा ABX8XX_TRICKLE_CHARGE_ENABLE	0xa0
#घोषणा ABX8XX_TRICKLE_STANDARD_DIODE	0x8
#घोषणा ABX8XX_TRICKLE_SCHOTTKY_DIODE	0x4

अटल u8 trickle_resistors[] = अणु0, 3, 6, 11पूर्ण;

क्रमागत abx80x_chip अणुAB0801, AB0803, AB0804, AB0805,
	AB1801, AB1803, AB1804, AB1805, RV1805, ABX80Xपूर्ण;

काष्ठा abx80x_cap अणु
	u16 pn;
	bool has_tc;
	bool has_wकरोg;
पूर्ण;

अटल काष्ठा abx80x_cap abx80x_caps[] = अणु
	[AB0801] = अणु.pn = 0x0801पूर्ण,
	[AB0803] = अणु.pn = 0x0803पूर्ण,
	[AB0804] = अणु.pn = 0x0804, .has_tc = true, .has_wकरोg = trueपूर्ण,
	[AB0805] = अणु.pn = 0x0805, .has_tc = true, .has_wकरोg = trueपूर्ण,
	[AB1801] = अणु.pn = 0x1801पूर्ण,
	[AB1803] = अणु.pn = 0x1803पूर्ण,
	[AB1804] = अणु.pn = 0x1804, .has_tc = true, .has_wकरोg = trueपूर्ण,
	[AB1805] = अणु.pn = 0x1805, .has_tc = true, .has_wकरोg = trueपूर्ण,
	[RV1805] = अणु.pn = 0x1805, .has_tc = true, .has_wकरोg = trueपूर्ण,
	[ABX80X] = अणु.pn = 0पूर्ण
पूर्ण;

काष्ठा abx80x_priv अणु
	काष्ठा rtc_device *rtc;
	काष्ठा i2c_client *client;
	काष्ठा watchकरोg_device wकरोg;
पूर्ण;

अटल पूर्णांक abx80x_ग_लिखो_config_key(काष्ठा i2c_client *client, u8 key)
अणु
	अगर (i2c_smbus_ग_लिखो_byte_data(client, ABX8XX_REG_CFG_KEY, key) < 0) अणु
		dev_err(&client->dev, "Unable to write configuration key\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक abx80x_is_rc_mode(काष्ठा i2c_client *client)
अणु
	पूर्णांक flags = 0;

	flags =  i2c_smbus_पढ़ो_byte_data(client, ABX8XX_REG_OSS);
	अगर (flags < 0) अणु
		dev_err(&client->dev,
			"Failed to read autocalibration attribute\n");
		वापस flags;
	पूर्ण

	वापस (flags & ABX8XX_OSS_OMODE) ? 1 : 0;
पूर्ण

अटल पूर्णांक abx80x_enable_trickle_अक्षरger(काष्ठा i2c_client *client,
					 u8 trickle_cfg)
अणु
	पूर्णांक err;

	/*
	 * Write the configuration key रेजिस्टर to enable access to the Trickle
	 * रेजिस्टर
	 */
	अगर (abx80x_ग_लिखो_config_key(client, ABX8XX_CFG_KEY_MISC) < 0)
		वापस -EIO;

	err = i2c_smbus_ग_लिखो_byte_data(client, ABX8XX_REG_TRICKLE,
					ABX8XX_TRICKLE_CHARGE_ENABLE |
					trickle_cfg);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Unable to write trickle register\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक abx80x_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित अक्षर buf[8];
	पूर्णांक err, flags, rc_mode = 0;

	/* Read the Oscillator Failure only in XT mode */
	rc_mode = abx80x_is_rc_mode(client);
	अगर (rc_mode < 0)
		वापस rc_mode;

	अगर (!rc_mode) अणु
		flags = i2c_smbus_पढ़ो_byte_data(client, ABX8XX_REG_OSS);
		अगर (flags < 0)
			वापस flags;

		अगर (flags & ABX8XX_OSS_OF) अणु
			dev_err(dev, "Oscillator failure, data is invalid.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	err = i2c_smbus_पढ़ो_i2c_block_data(client, ABX8XX_REG_HTH,
					    माप(buf), buf);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Unable to read date\n");
		वापस -EIO;
	पूर्ण

	पंचांग->पंचांग_sec = bcd2bin(buf[ABX8XX_REG_SC] & 0x7F);
	पंचांग->पंचांग_min = bcd2bin(buf[ABX8XX_REG_MN] & 0x7F);
	पंचांग->पंचांग_hour = bcd2bin(buf[ABX8XX_REG_HR] & 0x3F);
	पंचांग->पंचांग_wday = buf[ABX8XX_REG_WD] & 0x7;
	पंचांग->पंचांग_mday = bcd2bin(buf[ABX8XX_REG_DA] & 0x3F);
	पंचांग->पंचांग_mon = bcd2bin(buf[ABX8XX_REG_MO] & 0x1F) - 1;
	पंचांग->पंचांग_year = bcd2bin(buf[ABX8XX_REG_YR]) + 100;

	वापस 0;
पूर्ण

अटल पूर्णांक abx80x_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित अक्षर buf[8];
	पूर्णांक err, flags;

	अगर (पंचांग->पंचांग_year < 100)
		वापस -EINVAL;

	buf[ABX8XX_REG_HTH] = 0;
	buf[ABX8XX_REG_SC] = bin2bcd(पंचांग->पंचांग_sec);
	buf[ABX8XX_REG_MN] = bin2bcd(पंचांग->पंचांग_min);
	buf[ABX8XX_REG_HR] = bin2bcd(पंचांग->पंचांग_hour);
	buf[ABX8XX_REG_DA] = bin2bcd(पंचांग->पंचांग_mday);
	buf[ABX8XX_REG_MO] = bin2bcd(पंचांग->पंचांग_mon + 1);
	buf[ABX8XX_REG_YR] = bin2bcd(पंचांग->पंचांग_year - 100);
	buf[ABX8XX_REG_WD] = पंचांग->पंचांग_wday;

	err = i2c_smbus_ग_लिखो_i2c_block_data(client, ABX8XX_REG_HTH,
					     माप(buf), buf);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Unable to write to date registers\n");
		वापस -EIO;
	पूर्ण

	/* Clear the OF bit of Oscillator Status Register */
	flags = i2c_smbus_पढ़ो_byte_data(client, ABX8XX_REG_OSS);
	अगर (flags < 0)
		वापस flags;

	err = i2c_smbus_ग_लिखो_byte_data(client, ABX8XX_REG_OSS,
					flags & ~ABX8XX_OSS_OF);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Unable to write oscillator status register\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t abx80x_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा i2c_client *client = dev_id;
	काष्ठा abx80x_priv *priv = i2c_get_clientdata(client);
	काष्ठा rtc_device *rtc = priv->rtc;
	पूर्णांक status;

	status = i2c_smbus_पढ़ो_byte_data(client, ABX8XX_REG_STATUS);
	अगर (status < 0)
		वापस IRQ_NONE;

	अगर (status & ABX8XX_STATUS_AF)
		rtc_update_irq(rtc, 1, RTC_AF | RTC_IRQF);

	/*
	 * It is unclear अगर we'll get an पूर्णांकerrupt beक्रमe the बाह्यal
	 * reset kicks in.
	 */
	अगर (status & ABX8XX_STATUS_WDT)
		dev_alert(&client->dev, "watchdog timeout interrupt.\n");

	i2c_smbus_ग_लिखो_byte_data(client, ABX8XX_REG_STATUS, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक abx80x_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित अक्षर buf[7];

	पूर्णांक irq_mask, err;

	अगर (client->irq <= 0)
		वापस -EINVAL;

	err = i2c_smbus_पढ़ो_i2c_block_data(client, ABX8XX_REG_ASC,
					    माप(buf), buf);
	अगर (err)
		वापस err;

	irq_mask = i2c_smbus_पढ़ो_byte_data(client, ABX8XX_REG_IRQ);
	अगर (irq_mask < 0)
		वापस irq_mask;

	t->समय.पंचांग_sec = bcd2bin(buf[0] & 0x7F);
	t->समय.पंचांग_min = bcd2bin(buf[1] & 0x7F);
	t->समय.पंचांग_hour = bcd2bin(buf[2] & 0x3F);
	t->समय.पंचांग_mday = bcd2bin(buf[3] & 0x3F);
	t->समय.पंचांग_mon = bcd2bin(buf[4] & 0x1F) - 1;
	t->समय.पंचांग_wday = buf[5] & 0x7;

	t->enabled = !!(irq_mask & ABX8XX_IRQ_AIE);
	t->pending = (buf[6] & ABX8XX_STATUS_AF) && t->enabled;

	वापस err;
पूर्ण

अटल पूर्णांक abx80x_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u8 alarm[6];
	पूर्णांक err;

	अगर (client->irq <= 0)
		वापस -EINVAL;

	alarm[0] = 0x0;
	alarm[1] = bin2bcd(t->समय.पंचांग_sec);
	alarm[2] = bin2bcd(t->समय.पंचांग_min);
	alarm[3] = bin2bcd(t->समय.पंचांग_hour);
	alarm[4] = bin2bcd(t->समय.पंचांग_mday);
	alarm[5] = bin2bcd(t->समय.पंचांग_mon + 1);

	err = i2c_smbus_ग_लिखो_i2c_block_data(client, ABX8XX_REG_AHTH,
					     माप(alarm), alarm);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Unable to write alarm registers\n");
		वापस -EIO;
	पूर्ण

	अगर (t->enabled) अणु
		err = i2c_smbus_ग_लिखो_byte_data(client, ABX8XX_REG_IRQ,
						(ABX8XX_IRQ_IM_1_4 |
						 ABX8XX_IRQ_AIE));
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक abx80x_rtc_set_स्वतःcalibration(काष्ठा device *dev,
					  पूर्णांक स्वतःcalibration)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक retval, flags = 0;

	अगर ((स्वतःcalibration != 0) && (स्वतःcalibration != 1024) &&
	    (स्वतःcalibration != 512)) अणु
		dev_err(dev, "autocalibration value outside permitted range\n");
		वापस -EINVAL;
	पूर्ण

	flags = i2c_smbus_पढ़ो_byte_data(client, ABX8XX_REG_OSC);
	अगर (flags < 0)
		वापस flags;

	अगर (स्वतःcalibration == 0) अणु
		flags &= ~(ABX8XX_OSC_ACAL_512 | ABX8XX_OSC_ACAL_1024);
	पूर्ण अन्यथा अगर (स्वतःcalibration == 1024) अणु
		/* 1024 स्वतःcalibration is 0x10 */
		flags |= ABX8XX_OSC_ACAL_1024;
		flags &= ~(ABX8XX_OSC_ACAL_512);
	पूर्ण अन्यथा अणु
		/* 512 स्वतःcalibration is 0x11 */
		flags |= (ABX8XX_OSC_ACAL_1024 | ABX8XX_OSC_ACAL_512);
	पूर्ण

	/* Unlock ग_लिखो access to Oscillator Control Register */
	अगर (abx80x_ग_लिखो_config_key(client, ABX8XX_CFG_KEY_OSC) < 0)
		वापस -EIO;

	retval = i2c_smbus_ग_लिखो_byte_data(client, ABX8XX_REG_OSC, flags);

	वापस retval;
पूर्ण

अटल पूर्णांक abx80x_rtc_get_स्वतःcalibration(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक flags = 0, स्वतःcalibration;

	flags =  i2c_smbus_पढ़ो_byte_data(client, ABX8XX_REG_OSC);
	अगर (flags < 0)
		वापस flags;

	अगर (flags & ABX8XX_OSC_ACAL_512)
		स्वतःcalibration = 512;
	अन्यथा अगर (flags & ABX8XX_OSC_ACAL_1024)
		स्वतःcalibration = 1024;
	अन्यथा
		स्वतःcalibration = 0;

	वापस स्वतःcalibration;
पूर्ण

अटल sमाप_प्रकार स्वतःcalibration_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ स्वतःcalibration = 0;

	retval = kम_से_अदीर्घ(buf, 10, &स्वतःcalibration);
	अगर (retval < 0) अणु
		dev_err(dev, "Failed to store RTC autocalibration attribute\n");
		वापस -EINVAL;
	पूर्ण

	retval = abx80x_rtc_set_स्वतःcalibration(dev->parent, स्वतःcalibration);

	वापस retval ? retval : count;
पूर्ण

अटल sमाप_प्रकार स्वतःcalibration_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक स्वतःcalibration = 0;

	स्वतःcalibration = abx80x_rtc_get_स्वतःcalibration(dev->parent);
	अगर (स्वतःcalibration < 0) अणु
		dev_err(dev, "Failed to read RTC autocalibration\n");
		प्र_लिखो(buf, "0\n");
		वापस स्वतःcalibration;
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", स्वतःcalibration);
पूर्ण

अटल DEVICE_ATTR_RW(स्वतःcalibration);

अटल sमाप_प्रकार oscillator_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	पूर्णांक retval, flags, rc_mode = 0;

	अगर (म_भेदन(buf, "rc", 2) == 0) अणु
		rc_mode = 1;
	पूर्ण अन्यथा अगर (म_भेदन(buf, "xtal", 4) == 0) अणु
		rc_mode = 0;
	पूर्ण अन्यथा अणु
		dev_err(dev, "Oscillator selection value outside permitted ones\n");
		वापस -EINVAL;
	पूर्ण

	flags =  i2c_smbus_पढ़ो_byte_data(client, ABX8XX_REG_OSC);
	अगर (flags < 0)
		वापस flags;

	अगर (rc_mode == 0)
		flags &= ~(ABX8XX_OSC_OSEL);
	अन्यथा
		flags |= (ABX8XX_OSC_OSEL);

	/* Unlock ग_लिखो access on Oscillator Control रेजिस्टर */
	अगर (abx80x_ग_लिखो_config_key(client, ABX8XX_CFG_KEY_OSC) < 0)
		वापस -EIO;

	retval = i2c_smbus_ग_लिखो_byte_data(client, ABX8XX_REG_OSC, flags);
	अगर (retval < 0) अणु
		dev_err(dev, "Failed to write Oscillator Control register\n");
		वापस retval;
	पूर्ण

	वापस retval ? retval : count;
पूर्ण

अटल sमाप_प्रकार oscillator_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rc_mode = 0;
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);

	rc_mode = abx80x_is_rc_mode(client);

	अगर (rc_mode < 0) अणु
		dev_err(dev, "Failed to read RTC oscillator selection\n");
		प्र_लिखो(buf, "\n");
		वापस rc_mode;
	पूर्ण

	अगर (rc_mode)
		वापस प्र_लिखो(buf, "rc\n");
	अन्यथा
		वापस प्र_लिखो(buf, "xtal\n");
पूर्ण

अटल DEVICE_ATTR_RW(oscillator);

अटल काष्ठा attribute *rtc_calib_attrs[] = अणु
	&dev_attr_स्वतःcalibration.attr,
	&dev_attr_oscillator.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group rtc_calib_attr_group = अणु
	.attrs		= rtc_calib_attrs,
पूर्ण;

अटल पूर्णांक abx80x_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक err;

	अगर (enabled)
		err = i2c_smbus_ग_लिखो_byte_data(client, ABX8XX_REG_IRQ,
						(ABX8XX_IRQ_IM_1_4 |
						 ABX8XX_IRQ_AIE));
	अन्यथा
		err = i2c_smbus_ग_लिखो_byte_data(client, ABX8XX_REG_IRQ,
						ABX8XX_IRQ_IM_1_4);
	वापस err;
पूर्ण

अटल पूर्णांक abx80x_ioctl(काष्ठा device *dev, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक status, पंचांगp;

	चयन (cmd) अणु
	हाल RTC_VL_READ:
		status = i2c_smbus_पढ़ो_byte_data(client, ABX8XX_REG_STATUS);
		अगर (status < 0)
			वापस status;

		पंचांगp = status & ABX8XX_STATUS_BLF ? RTC_VL_BACKUP_LOW : 0;

		वापस put_user(पंचांगp, (अचिन्हित पूर्णांक __user *)arg);

	हाल RTC_VL_CLR:
		status = i2c_smbus_पढ़ो_byte_data(client, ABX8XX_REG_STATUS);
		अगर (status < 0)
			वापस status;

		status &= ~ABX8XX_STATUS_BLF;

		पंचांगp = i2c_smbus_ग_लिखो_byte_data(client, ABX8XX_REG_STATUS, 0);
		अगर (पंचांगp < 0)
			वापस पंचांगp;

		वापस 0;

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops abx80x_rtc_ops = अणु
	.पढ़ो_समय	= abx80x_rtc_पढ़ो_समय,
	.set_समय	= abx80x_rtc_set_समय,
	.पढ़ो_alarm	= abx80x_पढ़ो_alarm,
	.set_alarm	= abx80x_set_alarm,
	.alarm_irq_enable = abx80x_alarm_irq_enable,
	.ioctl		= abx80x_ioctl,
पूर्ण;

अटल पूर्णांक abx80x_dt_trickle_cfg(काष्ठा i2c_client *client)
अणु
	काष्ठा device_node *np = client->dev.of_node;
	स्थिर अक्षर *diode;
	पूर्णांक trickle_cfg = 0;
	पूर्णांक i, ret;
	u32 पंचांगp;

	ret = of_property_पढ़ो_string(np, "abracon,tc-diode", &diode);
	अगर (ret)
		वापस ret;

	अगर (!म_भेद(diode, "standard")) अणु
		trickle_cfg |= ABX8XX_TRICKLE_STANDARD_DIODE;
	पूर्ण अन्यथा अगर (!म_भेद(diode, "schottky")) अणु
		trickle_cfg |= ABX8XX_TRICKLE_SCHOTTKY_DIODE;
	पूर्ण अन्यथा अणु
		dev_dbg(&client->dev, "Invalid tc-diode value: %s\n", diode);
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "abracon,tc-resistor", &पंचांगp);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < माप(trickle_resistors); i++)
		अगर (trickle_resistors[i] == पंचांगp)
			अवरोध;

	अगर (i == माप(trickle_resistors)) अणु
		dev_dbg(&client->dev, "Invalid tc-resistor value: %u\n", पंचांगp);
		वापस -EINVAL;
	पूर्ण

	वापस (trickle_cfg | i);
पूर्ण

#अगर_घोषित CONFIG_WATCHDOG

अटल अंतरभूत u8 समयout_bits(अचिन्हित पूर्णांक समयout)
अणु
	वापस ((समयout << ABX8XX_WDT_BMB_SHIFT) & ABX8XX_WDT_BMB_MASK) |
		 ABX8XX_WDT_WRB_1HZ;
पूर्ण

अटल पूर्णांक __abx80x_wकरोg_set_समयout(काष्ठा watchकरोg_device *wकरोg,
				     अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा abx80x_priv *priv = watchकरोg_get_drvdata(wकरोg);
	u8 val = ABX8XX_WDT_WDS | समयout_bits(समयout);

	/*
	 * Writing any समयout to the WDT रेजिस्टर resets the watchकरोg समयr.
	 * Writing 0 disables it.
	 */
	वापस i2c_smbus_ग_लिखो_byte_data(priv->client, ABX8XX_REG_WDT, val);
पूर्ण

अटल पूर्णांक abx80x_wकरोg_set_समयout(काष्ठा watchकरोg_device *wकरोg,
				   अचिन्हित पूर्णांक new_समयout)
अणु
	पूर्णांक err = 0;

	अगर (watchकरोg_hw_running(wकरोg))
		err = __abx80x_wकरोg_set_समयout(wकरोg, new_समयout);

	अगर (err == 0)
		wकरोg->समयout = new_समयout;

	वापस err;
पूर्ण

अटल पूर्णांक abx80x_wकरोg_ping(काष्ठा watchकरोg_device *wकरोg)
अणु
	वापस __abx80x_wकरोg_set_समयout(wकरोg, wकरोg->समयout);
पूर्ण

अटल पूर्णांक abx80x_wकरोg_start(काष्ठा watchकरोg_device *wकरोg)
अणु
	वापस __abx80x_wकरोg_set_समयout(wकरोg, wकरोg->समयout);
पूर्ण

अटल पूर्णांक abx80x_wकरोg_stop(काष्ठा watchकरोg_device *wकरोg)
अणु
	वापस __abx80x_wकरोg_set_समयout(wकरोg, 0);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info abx80x_wकरोg_info = अणु
	.identity = "abx80x watchdog",
	.options = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops abx80x_wकरोg_ops = अणु
	.owner = THIS_MODULE,
	.start = abx80x_wकरोg_start,
	.stop = abx80x_wकरोg_stop,
	.ping = abx80x_wकरोg_ping,
	.set_समयout = abx80x_wकरोg_set_समयout,
पूर्ण;

अटल पूर्णांक abx80x_setup_watchकरोg(काष्ठा abx80x_priv *priv)
अणु
	priv->wकरोg.parent = &priv->client->dev;
	priv->wकरोg.ops = &abx80x_wकरोg_ops;
	priv->wकरोg.info = &abx80x_wकरोg_info;
	priv->wकरोg.min_समयout = 1;
	priv->wकरोg.max_समयout = ABX8XX_WDT_MAX_TIME;
	priv->wकरोg.समयout = ABX8XX_WDT_MAX_TIME;

	watchकरोg_set_drvdata(&priv->wकरोg, priv);

	वापस devm_watchकरोg_रेजिस्टर_device(&priv->client->dev, &priv->wकरोg);
पूर्ण
#अन्यथा
अटल पूर्णांक abx80x_setup_watchकरोg(काष्ठा abx80x_priv *priv)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक abx80x_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device_node *np = client->dev.of_node;
	काष्ठा abx80x_priv *priv;
	पूर्णांक i, data, err, trickle_cfg = -EINVAL;
	अक्षर buf[7];
	अचिन्हित पूर्णांक part = id->driver_data;
	अचिन्हित पूर्णांक partnumber;
	अचिन्हित पूर्णांक majrev, minrev;
	अचिन्हित पूर्णांक lot;
	अचिन्हित पूर्णांक wafer;
	अचिन्हित पूर्णांक uid;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	err = i2c_smbus_पढ़ो_i2c_block_data(client, ABX8XX_REG_ID0,
					    माप(buf), buf);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Unable to read partnumber\n");
		वापस -EIO;
	पूर्ण

	partnumber = (buf[0] << 8) | buf[1];
	majrev = buf[2] >> 3;
	minrev = buf[2] & 0x7;
	lot = ((buf[4] & 0x80) << 2) | ((buf[6] & 0x80) << 1) | buf[3];
	uid = ((buf[4] & 0x7f) << 8) | buf[5];
	wafer = (buf[6] & 0x7c) >> 2;
	dev_info(&client->dev, "model %04x, revision %u.%u, lot %x, wafer %x, uid %x\n",
		 partnumber, majrev, minrev, lot, wafer, uid);

	data = i2c_smbus_पढ़ो_byte_data(client, ABX8XX_REG_CTRL1);
	अगर (data < 0) अणु
		dev_err(&client->dev, "Unable to read control register\n");
		वापस -EIO;
	पूर्ण

	err = i2c_smbus_ग_लिखो_byte_data(client, ABX8XX_REG_CTRL1,
					((data & ~(ABX8XX_CTRL_12_24 |
						   ABX8XX_CTRL_ARST)) |
					 ABX8XX_CTRL_WRITE));
	अगर (err < 0) अणु
		dev_err(&client->dev, "Unable to write control register\n");
		वापस -EIO;
	पूर्ण

	/* Configure RV1805 specअगरics */
	अगर (part == RV1805) अणु
		/*
		 * Aव्योम accidentally entering test mode. This can happen
		 * on the RV1805 in हाल the reserved bit 5 in control2
		 * रेजिस्टर is set. RV-1805-C3 datasheet indicates that
		 * the bit should be cleared in section 11h - Control2.
		 */
		data = i2c_smbus_पढ़ो_byte_data(client, ABX8XX_REG_CTRL2);
		अगर (data < 0) अणु
			dev_err(&client->dev,
				"Unable to read control2 register\n");
			वापस -EIO;
		पूर्ण

		err = i2c_smbus_ग_लिखो_byte_data(client, ABX8XX_REG_CTRL2,
						data & ~ABX8XX_CTRL2_RSVD);
		अगर (err < 0) अणु
			dev_err(&client->dev,
				"Unable to write control2 register\n");
			वापस -EIO;
		पूर्ण

		/*
		 * Aव्योम extra घातer leakage. The RV1805 uses smaller
		 * 10pin package and the EXTI input is not present.
		 * Disable it to aव्योम leakage.
		 */
		data = i2c_smbus_पढ़ो_byte_data(client, ABX8XX_REG_OUT_CTRL);
		अगर (data < 0) अणु
			dev_err(&client->dev,
				"Unable to read output control register\n");
			वापस -EIO;
		पूर्ण

		/*
		 * Write the configuration key रेजिस्टर to enable access to
		 * the config2 रेजिस्टर
		 */
		अगर (abx80x_ग_लिखो_config_key(client, ABX8XX_CFG_KEY_MISC) < 0)
			वापस -EIO;

		err = i2c_smbus_ग_लिखो_byte_data(client, ABX8XX_REG_OUT_CTRL,
						data | ABX8XX_OUT_CTRL_EXDS);
		अगर (err < 0) अणु
			dev_err(&client->dev,
				"Unable to write output control register\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	/* part स्वतःdetection */
	अगर (part == ABX80X) अणु
		क्रम (i = 0; abx80x_caps[i].pn; i++)
			अगर (partnumber == abx80x_caps[i].pn)
				अवरोध;
		अगर (abx80x_caps[i].pn == 0) अणु
			dev_err(&client->dev, "Unknown part: %04x\n",
				partnumber);
			वापस -EINVAL;
		पूर्ण
		part = i;
	पूर्ण

	अगर (partnumber != abx80x_caps[part].pn) अणु
		dev_err(&client->dev, "partnumber mismatch %04x != %04x\n",
			partnumber, abx80x_caps[part].pn);
		वापस -EINVAL;
	पूर्ण

	अगर (np && abx80x_caps[part].has_tc)
		trickle_cfg = abx80x_dt_trickle_cfg(client);

	अगर (trickle_cfg > 0) अणु
		dev_info(&client->dev, "Enabling trickle charger: %02x\n",
			 trickle_cfg);
		abx80x_enable_trickle_अक्षरger(client, trickle_cfg);
	पूर्ण

	err = i2c_smbus_ग_लिखो_byte_data(client, ABX8XX_REG_CD_TIMER_CTL,
					BIT(2));
	अगर (err)
		वापस err;

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस -ENOMEM;

	priv->rtc = devm_rtc_allocate_device(&client->dev);
	अगर (IS_ERR(priv->rtc))
		वापस PTR_ERR(priv->rtc);

	priv->rtc->ops = &abx80x_rtc_ops;
	priv->client = client;

	i2c_set_clientdata(client, priv);

	अगर (abx80x_caps[part].has_wकरोg) अणु
		err = abx80x_setup_watchकरोg(priv);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (client->irq > 0) अणु
		dev_info(&client->dev, "IRQ %d supplied\n", client->irq);
		err = devm_request_thपढ़ोed_irq(&client->dev, client->irq, शून्य,
						abx80x_handle_irq,
						IRQF_SHARED | IRQF_ONESHOT,
						"abx8xx",
						client);
		अगर (err) अणु
			dev_err(&client->dev, "unable to request IRQ, alarms disabled\n");
			client->irq = 0;
		पूर्ण
	पूर्ण

	err = rtc_add_group(priv->rtc, &rtc_calib_attr_group);
	अगर (err) अणु
		dev_err(&client->dev, "Failed to create sysfs group: %d\n",
			err);
		वापस err;
	पूर्ण

	वापस devm_rtc_रेजिस्टर_device(priv->rtc);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id abx80x_id[] = अणु
	अणु "abx80x", ABX80X पूर्ण,
	अणु "ab0801", AB0801 पूर्ण,
	अणु "ab0803", AB0803 पूर्ण,
	अणु "ab0804", AB0804 पूर्ण,
	अणु "ab0805", AB0805 पूर्ण,
	अणु "ab1801", AB1801 पूर्ण,
	अणु "ab1803", AB1803 पूर्ण,
	अणु "ab1804", AB1804 पूर्ण,
	अणु "ab1805", AB1805 पूर्ण,
	अणु "rv1805", RV1805 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, abx80x_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id abx80x_of_match[] = अणु
	अणु
		.compatible = "abracon,abx80x",
		.data = (व्योम *)ABX80X
	पूर्ण,
	अणु
		.compatible = "abracon,ab0801",
		.data = (व्योम *)AB0801
	पूर्ण,
	अणु
		.compatible = "abracon,ab0803",
		.data = (व्योम *)AB0803
	पूर्ण,
	अणु
		.compatible = "abracon,ab0804",
		.data = (व्योम *)AB0804
	पूर्ण,
	अणु
		.compatible = "abracon,ab0805",
		.data = (व्योम *)AB0805
	पूर्ण,
	अणु
		.compatible = "abracon,ab1801",
		.data = (व्योम *)AB1801
	पूर्ण,
	अणु
		.compatible = "abracon,ab1803",
		.data = (व्योम *)AB1803
	पूर्ण,
	अणु
		.compatible = "abracon,ab1804",
		.data = (व्योम *)AB1804
	पूर्ण,
	अणु
		.compatible = "abracon,ab1805",
		.data = (व्योम *)AB1805
	पूर्ण,
	अणु
		.compatible = "microcrystal,rv1805",
		.data = (व्योम *)RV1805
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, abx80x_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver abx80x_driver = अणु
	.driver		= अणु
		.name	= "rtc-abx80x",
		.of_match_table = of_match_ptr(abx80x_of_match),
	पूर्ण,
	.probe		= abx80x_probe,
	.id_table	= abx80x_id,
पूर्ण;

module_i2c_driver(abx80x_driver);

MODULE_AUTHOR("Philippe De Muyter <phdm@macqel.be>");
MODULE_AUTHOR("Alexandre Belloni <alexandre.belloni@bootlin.com>");
MODULE_DESCRIPTION("Abracon ABX80X RTC driver");
MODULE_LICENSE("GPL v2");
