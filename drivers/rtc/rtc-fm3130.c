<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rtc-fm3130.c - RTC driver क्रम Ramtron FM3130 I2C chip.
 *
 *  Copyright (C) 2008 Sergey Lapin
 *  Based on ds1307 driver by James Chapman and David Brownell
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/slab.h>

#घोषणा FM3130_RTC_CONTROL	(0x0)
#घोषणा FM3130_CAL_CONTROL	(0x1)
#घोषणा FM3130_RTC_SECONDS	(0x2)
#घोषणा FM3130_RTC_MINUTES	(0x3)
#घोषणा FM3130_RTC_HOURS	(0x4)
#घोषणा FM3130_RTC_DAY		(0x5)
#घोषणा FM3130_RTC_DATE		(0x6)
#घोषणा FM3130_RTC_MONTHS	(0x7)
#घोषणा FM3130_RTC_YEARS	(0x8)

#घोषणा FM3130_ALARM_SECONDS	(0x9)
#घोषणा FM3130_ALARM_MINUTES	(0xa)
#घोषणा FM3130_ALARM_HOURS	(0xb)
#घोषणा FM3130_ALARM_DATE	(0xc)
#घोषणा FM3130_ALARM_MONTHS	(0xd)
#घोषणा FM3130_ALARM_WP_CONTROL	(0xe)

#घोषणा FM3130_CAL_CONTROL_BIT_nOSCEN (1 << 7) /* Osciallator enabled */
#घोषणा FM3130_RTC_CONTROL_BIT_LB (1 << 7) /* Low battery */
#घोषणा FM3130_RTC_CONTROL_BIT_AF (1 << 6) /* Alarm flag */
#घोषणा FM3130_RTC_CONTROL_BIT_CF (1 << 5) /* Century overflow */
#घोषणा FM3130_RTC_CONTROL_BIT_POR (1 << 4) /* Power on reset */
#घोषणा FM3130_RTC_CONTROL_BIT_AEN (1 << 3) /* Alarm enable */
#घोषणा FM3130_RTC_CONTROL_BIT_CAL (1 << 2) /* Calibration mode */
#घोषणा FM3130_RTC_CONTROL_BIT_WRITE (1 << 1) /* W=1 -> ग_लिखो mode W=0 normal */
#घोषणा FM3130_RTC_CONTROL_BIT_READ (1 << 0) /* R=1 -> पढ़ो mode R=0 normal */

#घोषणा FM3130_CLOCK_REGS 7
#घोषणा FM3130_ALARM_REGS 5

काष्ठा fm3130 अणु
	u8			reg_addr_समय;
	u8			reg_addr_alarm;
	u8			regs[15];
	काष्ठा i2c_msg		msg[4];
	काष्ठा i2c_client	*client;
	काष्ठा rtc_device	*rtc;
	पूर्णांक			alarm_valid;
	पूर्णांक			data_valid;
पूर्ण;
अटल स्थिर काष्ठा i2c_device_id fm3130_id[] = अणु
	अणु "fm3130", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, fm3130_id);

#घोषणा FM3130_MODE_NORMAL		0
#घोषणा FM3130_MODE_WRITE		1
#घोषणा FM3130_MODE_READ		2

अटल व्योम fm3130_rtc_mode(काष्ठा device *dev, पूर्णांक mode)
अणु
	काष्ठा fm3130 *fm3130 = dev_get_drvdata(dev);

	fm3130->regs[FM3130_RTC_CONTROL] =
		i2c_smbus_पढ़ो_byte_data(fm3130->client, FM3130_RTC_CONTROL);
	चयन (mode) अणु
	हाल FM3130_MODE_NORMAL:
		fm3130->regs[FM3130_RTC_CONTROL] &=
			~(FM3130_RTC_CONTROL_BIT_WRITE |
			FM3130_RTC_CONTROL_BIT_READ);
		अवरोध;
	हाल FM3130_MODE_WRITE:
		fm3130->regs[FM3130_RTC_CONTROL] |= FM3130_RTC_CONTROL_BIT_WRITE;
		अवरोध;
	हाल FM3130_MODE_READ:
		fm3130->regs[FM3130_RTC_CONTROL] |= FM3130_RTC_CONTROL_BIT_READ;
		अवरोध;
	शेष:
		dev_dbg(dev, "invalid mode %d\n", mode);
		अवरोध;
	पूर्ण

	i2c_smbus_ग_लिखो_byte_data(fm3130->client,
		 FM3130_RTC_CONTROL, fm3130->regs[FM3130_RTC_CONTROL]);
पूर्ण

अटल पूर्णांक fm3130_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *t)
अणु
	काष्ठा fm3130 *fm3130 = dev_get_drvdata(dev);
	पूर्णांक		पंचांगp;

	अगर (!fm3130->data_valid) अणु
		/* We have invalid data in RTC, probably due
		to battery faults or other problems. Return EIO
		क्रम now, it will allow us to set data later instead
		of error during probing which disables device */
		वापस -EIO;
	पूर्ण
	fm3130_rtc_mode(dev, FM3130_MODE_READ);

	/* पढ़ो the RTC date and समय रेजिस्टरs all at once */
	पंचांगp = i2c_transfer(fm3130->client->adapter, fm3130->msg, 2);
	अगर (पंचांगp != 2) अणु
		dev_err(dev, "%s error %d\n", "read", पंचांगp);
		वापस -EIO;
	पूर्ण

	fm3130_rtc_mode(dev, FM3130_MODE_NORMAL);

	dev_dbg(dev, "%s: %15ph\n", "read", fm3130->regs);

	t->पंचांग_sec = bcd2bin(fm3130->regs[FM3130_RTC_SECONDS] & 0x7f);
	t->पंचांग_min = bcd2bin(fm3130->regs[FM3130_RTC_MINUTES] & 0x7f);
	पंचांगp = fm3130->regs[FM3130_RTC_HOURS] & 0x3f;
	t->पंचांग_hour = bcd2bin(पंचांगp);
	t->पंचांग_wday = bcd2bin(fm3130->regs[FM3130_RTC_DAY] & 0x07) - 1;
	t->पंचांग_mday = bcd2bin(fm3130->regs[FM3130_RTC_DATE] & 0x3f);
	पंचांगp = fm3130->regs[FM3130_RTC_MONTHS] & 0x1f;
	t->पंचांग_mon = bcd2bin(पंचांगp) - 1;

	/* assume 20YY not 19YY, and ignore CF bit */
	t->पंचांग_year = bcd2bin(fm3130->regs[FM3130_RTC_YEARS]) + 100;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"read", t->पंचांग_sec, t->पंचांग_min,
		t->पंचांग_hour, t->पंचांग_mday,
		t->पंचांग_mon, t->पंचांग_year, t->पंचांग_wday);

	वापस 0;
पूर्ण


अटल पूर्णांक fm3130_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *t)
अणु
	काष्ठा fm3130 *fm3130 = dev_get_drvdata(dev);
	पूर्णांक		पंचांगp, i;
	u8		*buf = fm3130->regs;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"write", t->पंचांग_sec, t->पंचांग_min,
		t->पंचांग_hour, t->पंचांग_mday,
		t->पंचांग_mon, t->पंचांग_year, t->पंचांग_wday);

	/* first रेजिस्टर addr */
	buf[FM3130_RTC_SECONDS] = bin2bcd(t->पंचांग_sec);
	buf[FM3130_RTC_MINUTES] = bin2bcd(t->पंचांग_min);
	buf[FM3130_RTC_HOURS] = bin2bcd(t->पंचांग_hour);
	buf[FM3130_RTC_DAY] = bin2bcd(t->पंचांग_wday + 1);
	buf[FM3130_RTC_DATE] = bin2bcd(t->पंचांग_mday);
	buf[FM3130_RTC_MONTHS] = bin2bcd(t->पंचांग_mon + 1);

	/* assume 20YY not 19YY */
	पंचांगp = t->पंचांग_year - 100;
	buf[FM3130_RTC_YEARS] = bin2bcd(पंचांगp);

	dev_dbg(dev, "%s: %15ph\n", "write", buf);

	fm3130_rtc_mode(dev, FM3130_MODE_WRITE);

	/* Writing समय रेजिस्टरs, we करोn't support multibyte transfers */
	क्रम (i = 0; i < FM3130_CLOCK_REGS; i++) अणु
		i2c_smbus_ग_लिखो_byte_data(fm3130->client,
					FM3130_RTC_SECONDS + i,
					fm3130->regs[FM3130_RTC_SECONDS + i]);
	पूर्ण

	fm3130_rtc_mode(dev, FM3130_MODE_NORMAL);

	/* We assume here that data are valid once written */
	अगर (!fm3130->data_valid)
		fm3130->data_valid = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक fm3130_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा fm3130 *fm3130 = dev_get_drvdata(dev);
	पूर्णांक पंचांगp;
	काष्ठा rtc_समय *पंचांग = &alrm->समय;

	अगर (!fm3130->alarm_valid) अणु
		/*
		 * We have invalid alarm in RTC, probably due to battery faults
		 * or other problems. Return EIO क्रम now, it will allow us to
		 * set alarm value later instead of error during probing which
		 * disables device
		 */
		वापस -EIO;
	पूर्ण

	/* पढ़ो the RTC alarm रेजिस्टरs all at once */
	पंचांगp = i2c_transfer(fm3130->client->adapter, &fm3130->msg[2], 2);
	अगर (पंचांगp != 2) अणु
		dev_err(dev, "%s error %d\n", "read", पंचांगp);
		वापस -EIO;
	पूर्ण
	dev_dbg(dev, "alarm read %02x %02x %02x %02x %02x\n",
			fm3130->regs[FM3130_ALARM_SECONDS],
			fm3130->regs[FM3130_ALARM_MINUTES],
			fm3130->regs[FM3130_ALARM_HOURS],
			fm3130->regs[FM3130_ALARM_DATE],
			fm3130->regs[FM3130_ALARM_MONTHS]);

	पंचांग->पंचांग_sec	= bcd2bin(fm3130->regs[FM3130_ALARM_SECONDS] & 0x7F);
	पंचांग->पंचांग_min	= bcd2bin(fm3130->regs[FM3130_ALARM_MINUTES] & 0x7F);
	पंचांग->पंचांग_hour	= bcd2bin(fm3130->regs[FM3130_ALARM_HOURS] & 0x3F);
	पंचांग->पंचांग_mday	= bcd2bin(fm3130->regs[FM3130_ALARM_DATE] & 0x3F);
	पंचांग->पंचांग_mon	= bcd2bin(fm3130->regs[FM3130_ALARM_MONTHS] & 0x1F);

	अगर (पंचांग->पंचांग_mon > 0)
		पंचांग->पंचांग_mon -= 1; /* RTC is 1-12, पंचांग_mon is 0-11 */

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"read alarm", पंचांग->पंचांग_sec, पंचांग->पंचांग_min,
		पंचांग->पंचांग_hour, पंचांग->पंचांग_mday,
		पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	/* check अगर alarm enabled */
	fm3130->regs[FM3130_RTC_CONTROL] =
		i2c_smbus_पढ़ो_byte_data(fm3130->client, FM3130_RTC_CONTROL);

	अगर ((fm3130->regs[FM3130_RTC_CONTROL] & FM3130_RTC_CONTROL_BIT_AEN) &&
		(~fm3130->regs[FM3130_RTC_CONTROL] &
			FM3130_RTC_CONTROL_BIT_CAL)) अणु
		alrm->enabled = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fm3130_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा fm3130 *fm3130 = dev_get_drvdata(dev);
	काष्ठा rtc_समय *पंचांग = &alrm->समय;
	पूर्णांक i;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"write alarm", पंचांग->पंचांग_sec, पंचांग->पंचांग_min,
		पंचांग->पंचांग_hour, पंचांग->पंचांग_mday,
		पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	fm3130->regs[FM3130_ALARM_SECONDS] =
		(पंचांग->पंचांग_sec != -1) ? bin2bcd(पंचांग->पंचांग_sec) : 0x80;

	fm3130->regs[FM3130_ALARM_MINUTES] =
		(पंचांग->पंचांग_min != -1) ? bin2bcd(पंचांग->पंचांग_min) : 0x80;

	fm3130->regs[FM3130_ALARM_HOURS] =
		(पंचांग->पंचांग_hour != -1) ? bin2bcd(पंचांग->पंचांग_hour) : 0x80;

	fm3130->regs[FM3130_ALARM_DATE] =
		(पंचांग->पंचांग_mday != -1) ? bin2bcd(पंचांग->पंचांग_mday) : 0x80;

	fm3130->regs[FM3130_ALARM_MONTHS] =
		(पंचांग->पंचांग_mon != -1) ? bin2bcd(पंचांग->पंचांग_mon + 1) : 0x80;

	dev_dbg(dev, "alarm write %02x %02x %02x %02x %02x\n",
			fm3130->regs[FM3130_ALARM_SECONDS],
			fm3130->regs[FM3130_ALARM_MINUTES],
			fm3130->regs[FM3130_ALARM_HOURS],
			fm3130->regs[FM3130_ALARM_DATE],
			fm3130->regs[FM3130_ALARM_MONTHS]);
	/* Writing समय रेजिस्टरs, we करोn't support multibyte transfers */
	क्रम (i = 0; i < FM3130_ALARM_REGS; i++) अणु
		i2c_smbus_ग_लिखो_byte_data(fm3130->client,
					FM3130_ALARM_SECONDS + i,
					fm3130->regs[FM3130_ALARM_SECONDS + i]);
	पूर्ण
	fm3130->regs[FM3130_RTC_CONTROL] =
		i2c_smbus_पढ़ो_byte_data(fm3130->client, FM3130_RTC_CONTROL);

	/* enable or disable alarm */
	अगर (alrm->enabled) अणु
		i2c_smbus_ग_लिखो_byte_data(fm3130->client, FM3130_RTC_CONTROL,
			(fm3130->regs[FM3130_RTC_CONTROL] &
				~(FM3130_RTC_CONTROL_BIT_CAL)) |
					FM3130_RTC_CONTROL_BIT_AEN);
	पूर्ण अन्यथा अणु
		i2c_smbus_ग_लिखो_byte_data(fm3130->client, FM3130_RTC_CONTROL,
			fm3130->regs[FM3130_RTC_CONTROL] &
				~(FM3130_RTC_CONTROL_BIT_CAL) &
					~(FM3130_RTC_CONTROL_BIT_AEN));
	पूर्ण

	/* We assume here that data is valid once written */
	अगर (!fm3130->alarm_valid)
		fm3130->alarm_valid = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक fm3130_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा fm3130 *fm3130 = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	fm3130->regs[FM3130_RTC_CONTROL] =
		i2c_smbus_पढ़ो_byte_data(fm3130->client, FM3130_RTC_CONTROL);

	dev_dbg(dev, "alarm_irq_enable: enable=%d, FM3130_RTC_CONTROL=%02x\n",
		enabled, fm3130->regs[FM3130_RTC_CONTROL]);

	चयन (enabled) अणु
	हाल 0:		/* alarm off */
		ret = i2c_smbus_ग_लिखो_byte_data(fm3130->client,
			FM3130_RTC_CONTROL, fm3130->regs[FM3130_RTC_CONTROL] &
				~(FM3130_RTC_CONTROL_BIT_CAL) &
					~(FM3130_RTC_CONTROL_BIT_AEN));
		अवरोध;
	हाल 1:		/* alarm on */
		ret = i2c_smbus_ग_लिखो_byte_data(fm3130->client,
			FM3130_RTC_CONTROL, (fm3130->regs[FM3130_RTC_CONTROL] &
				~(FM3130_RTC_CONTROL_BIT_CAL)) |
					FM3130_RTC_CONTROL_BIT_AEN);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops fm3130_rtc_ops = अणु
	.पढ़ो_समय	= fm3130_get_समय,
	.set_समय	= fm3130_set_समय,
	.पढ़ो_alarm	= fm3130_पढ़ो_alarm,
	.set_alarm	= fm3130_set_alarm,
	.alarm_irq_enable = fm3130_alarm_irq_enable,
पूर्ण;

अटल काष्ठा i2c_driver fm3130_driver;

अटल पूर्णांक fm3130_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा fm3130		*fm3130;
	पूर्णांक			err = -ENODEV;
	पूर्णांक			पंचांगp;
	काष्ठा i2c_adapter	*adapter = client->adapter;

	अगर (!i2c_check_functionality(adapter,
			I2C_FUNC_I2C | I2C_FUNC_SMBUS_WRITE_BYTE_DATA))
		वापस -EIO;

	fm3130 = devm_kzalloc(&client->dev, माप(काष्ठा fm3130), GFP_KERNEL);

	अगर (!fm3130)
		वापस -ENOMEM;

	fm3130->client = client;
	i2c_set_clientdata(client, fm3130);
	fm3130->reg_addr_समय = FM3130_RTC_SECONDS;
	fm3130->reg_addr_alarm = FM3130_ALARM_SECONDS;

	/* Messages to पढ़ो समय */
	fm3130->msg[0].addr = client->addr;
	fm3130->msg[0].flags = 0;
	fm3130->msg[0].len = 1;
	fm3130->msg[0].buf = &fm3130->reg_addr_समय;

	fm3130->msg[1].addr = client->addr;
	fm3130->msg[1].flags = I2C_M_RD;
	fm3130->msg[1].len = FM3130_CLOCK_REGS;
	fm3130->msg[1].buf = &fm3130->regs[FM3130_RTC_SECONDS];

	/* Messages to पढ़ो alarm */
	fm3130->msg[2].addr = client->addr;
	fm3130->msg[2].flags = 0;
	fm3130->msg[2].len = 1;
	fm3130->msg[2].buf = &fm3130->reg_addr_alarm;

	fm3130->msg[3].addr = client->addr;
	fm3130->msg[3].flags = I2C_M_RD;
	fm3130->msg[3].len = FM3130_ALARM_REGS;
	fm3130->msg[3].buf = &fm3130->regs[FM3130_ALARM_SECONDS];

	fm3130->alarm_valid = 0;
	fm3130->data_valid = 0;

	पंचांगp = i2c_transfer(adapter, fm3130->msg, 4);
	अगर (पंचांगp != 4) अणु
		dev_dbg(&client->dev, "read error %d\n", पंचांगp);
		err = -EIO;
		जाओ निकास_मुक्त;
	पूर्ण

	fm3130->regs[FM3130_RTC_CONTROL] =
		i2c_smbus_पढ़ो_byte_data(client, FM3130_RTC_CONTROL);
	fm3130->regs[FM3130_CAL_CONTROL] =
		i2c_smbus_पढ़ो_byte_data(client, FM3130_CAL_CONTROL);

	/* Disabling calibration mode */
	अगर (fm3130->regs[FM3130_RTC_CONTROL] & FM3130_RTC_CONTROL_BIT_CAL) अणु
		i2c_smbus_ग_लिखो_byte_data(client, FM3130_RTC_CONTROL,
			fm3130->regs[FM3130_RTC_CONTROL] &
				~(FM3130_RTC_CONTROL_BIT_CAL));
		dev_warn(&client->dev, "Disabling calibration mode!\n");
	पूर्ण

	/* Disabling पढ़ो and ग_लिखो modes */
	अगर (fm3130->regs[FM3130_RTC_CONTROL] & FM3130_RTC_CONTROL_BIT_WRITE ||
	    fm3130->regs[FM3130_RTC_CONTROL] & FM3130_RTC_CONTROL_BIT_READ) अणु
		i2c_smbus_ग_लिखो_byte_data(client, FM3130_RTC_CONTROL,
			fm3130->regs[FM3130_RTC_CONTROL] &
				~(FM3130_RTC_CONTROL_BIT_READ |
					FM3130_RTC_CONTROL_BIT_WRITE));
		dev_warn(&client->dev, "Disabling READ or WRITE mode!\n");
	पूर्ण

	/* oscillator off?  turn it on, so घड़ी can tick. */
	अगर (fm3130->regs[FM3130_CAL_CONTROL] & FM3130_CAL_CONTROL_BIT_nOSCEN)
		i2c_smbus_ग_लिखो_byte_data(client, FM3130_CAL_CONTROL,
			fm3130->regs[FM3130_CAL_CONTROL] &
				~(FM3130_CAL_CONTROL_BIT_nOSCEN));

	/* low battery?  clear flag, and warn */
	अगर (fm3130->regs[FM3130_RTC_CONTROL] & FM3130_RTC_CONTROL_BIT_LB) अणु
		i2c_smbus_ग_लिखो_byte_data(client, FM3130_RTC_CONTROL,
			fm3130->regs[FM3130_RTC_CONTROL] &
				~(FM3130_RTC_CONTROL_BIT_LB));
		dev_warn(&client->dev, "Low battery!\n");
	पूर्ण

	/* check अगर Power On Reset bit is set */
	अगर (fm3130->regs[FM3130_RTC_CONTROL] & FM3130_RTC_CONTROL_BIT_POR) अणु
		i2c_smbus_ग_लिखो_byte_data(client, FM3130_RTC_CONTROL,
			fm3130->regs[FM3130_RTC_CONTROL] &
				~FM3130_RTC_CONTROL_BIT_POR);
		dev_dbg(&client->dev, "POR bit is set\n");
	पूर्ण
	/* ACS is controlled by alarm */
	i2c_smbus_ग_लिखो_byte_data(client, FM3130_ALARM_WP_CONTROL, 0x80);

	/* alarm रेजिस्टरs sanity check */
	पंचांगp = bcd2bin(fm3130->regs[FM3130_RTC_SECONDS] & 0x7f);
	अगर (पंचांगp > 59)
		जाओ bad_alarm;

	पंचांगp = bcd2bin(fm3130->regs[FM3130_RTC_MINUTES] & 0x7f);
	अगर (पंचांगp > 59)
		जाओ bad_alarm;

	पंचांगp = bcd2bin(fm3130->regs[FM3130_RTC_HOURS] & 0x3f);
	अगर (पंचांगp > 23)
		जाओ bad_alarm;

	पंचांगp = bcd2bin(fm3130->regs[FM3130_RTC_DATE] & 0x3f);
	अगर (पंचांगp == 0 || पंचांगp > 31)
		जाओ bad_alarm;

	पंचांगp = bcd2bin(fm3130->regs[FM3130_RTC_MONTHS] & 0x1f);
	अगर (पंचांगp == 0 || पंचांगp > 12)
		जाओ bad_alarm;

	fm3130->alarm_valid = 1;

bad_alarm:

	/* घड़ी रेजिस्टरs sanity chek */
	पंचांगp = bcd2bin(fm3130->regs[FM3130_RTC_SECONDS] & 0x7f);
	अगर (पंचांगp > 59)
		जाओ bad_घड़ी;

	पंचांगp = bcd2bin(fm3130->regs[FM3130_RTC_MINUTES] & 0x7f);
	अगर (पंचांगp > 59)
		जाओ bad_घड़ी;

	पंचांगp = bcd2bin(fm3130->regs[FM3130_RTC_HOURS] & 0x3f);
	अगर (पंचांगp > 23)
		जाओ bad_घड़ी;

	पंचांगp = bcd2bin(fm3130->regs[FM3130_RTC_DAY] & 0x7);
	अगर (पंचांगp == 0 || पंचांगp > 7)
		जाओ bad_घड़ी;

	पंचांगp = bcd2bin(fm3130->regs[FM3130_RTC_DATE] & 0x3f);
	अगर (पंचांगp == 0 || पंचांगp > 31)
		जाओ bad_घड़ी;

	पंचांगp = bcd2bin(fm3130->regs[FM3130_RTC_MONTHS] & 0x1f);
	अगर (पंचांगp == 0 || पंचांगp > 12)
		जाओ bad_घड़ी;

	fm3130->data_valid = 1;

bad_घड़ी:

	अगर (!fm3130->data_valid || !fm3130->alarm_valid)
		dev_dbg(&client->dev, "%s: %15ph\n", "bogus registers",
			fm3130->regs);

	/* We won't bail out here because we just got invalid data.
	   Time setting from u-boot करोesn't work anyway */
	fm3130->rtc = devm_rtc_device_रेजिस्टर(&client->dev, client->name,
				&fm3130_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(fm3130->rtc)) अणु
		err = PTR_ERR(fm3130->rtc);
		dev_err(&client->dev,
			"unable to register the class device\n");
		जाओ निकास_मुक्त;
	पूर्ण
	वापस 0;
निकास_मुक्त:
	वापस err;
पूर्ण

अटल काष्ठा i2c_driver fm3130_driver = अणु
	.driver = अणु
		.name	= "rtc-fm3130",
	पूर्ण,
	.probe		= fm3130_probe,
	.id_table	= fm3130_id,
पूर्ण;

module_i2c_driver(fm3130_driver);

MODULE_DESCRIPTION("RTC driver for FM3130");
MODULE_AUTHOR("Sergey Lapin <slapin@ossfans.org>");
MODULE_LICENSE("GPL");

