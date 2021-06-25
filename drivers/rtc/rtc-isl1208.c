<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Intersil ISL1208 rtc class driver
 *
 * Copyright 2005,2006 Hebert Valerio Riedel <hvr@gnu.org>
 */

#समावेश <linux/bcd.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/rtc.h>

/* Register map */
/* rtc section */
#घोषणा ISL1208_REG_SC  0x00
#घोषणा ISL1208_REG_MN  0x01
#घोषणा ISL1208_REG_HR  0x02
#घोषणा ISL1208_REG_HR_MIL     (1<<7)	/* 24h/12h mode */
#घोषणा ISL1208_REG_HR_PM      (1<<5)	/* PM/AM bit in 12h mode */
#घोषणा ISL1208_REG_DT  0x03
#घोषणा ISL1208_REG_MO  0x04
#घोषणा ISL1208_REG_YR  0x05
#घोषणा ISL1208_REG_DW  0x06
#घोषणा ISL1208_RTC_SECTION_LEN 7

/* control/status section */
#घोषणा ISL1208_REG_SR  0x07
#घोषणा ISL1208_REG_SR_ARST    (1<<7)	/* स्वतः reset */
#घोषणा ISL1208_REG_SR_XTOSCB  (1<<6)	/* crystal oscillator */
#घोषणा ISL1208_REG_SR_WRTC    (1<<4)	/* ग_लिखो rtc */
#घोषणा ISL1208_REG_SR_EVT     (1<<3)	/* event */
#घोषणा ISL1208_REG_SR_ALM     (1<<2)	/* alarm */
#घोषणा ISL1208_REG_SR_BAT     (1<<1)	/* battery */
#घोषणा ISL1208_REG_SR_RTCF    (1<<0)	/* rtc fail */
#घोषणा ISL1208_REG_INT 0x08
#घोषणा ISL1208_REG_INT_ALME   (1<<6)   /* alarm enable */
#घोषणा ISL1208_REG_INT_IM     (1<<7)   /* पूर्णांकerrupt/alarm mode */
#घोषणा ISL1219_REG_EV  0x09
#घोषणा ISL1219_REG_EV_EVEN    (1<<4)   /* event detection enable */
#घोषणा ISL1219_REG_EV_EVIENB  (1<<7)   /* event in pull-up disable */
#घोषणा ISL1208_REG_ATR 0x0a
#घोषणा ISL1208_REG_DTR 0x0b

/* alarm section */
#घोषणा ISL1208_REG_SCA 0x0c
#घोषणा ISL1208_REG_MNA 0x0d
#घोषणा ISL1208_REG_HRA 0x0e
#घोषणा ISL1208_REG_DTA 0x0f
#घोषणा ISL1208_REG_MOA 0x10
#घोषणा ISL1208_REG_DWA 0x11
#घोषणा ISL1208_ALARM_SECTION_LEN 6

/* user section */
#घोषणा ISL1208_REG_USR1 0x12
#घोषणा ISL1208_REG_USR2 0x13
#घोषणा ISL1208_USR_SECTION_LEN 2

/* event section */
#घोषणा ISL1219_REG_SCT 0x14
#घोषणा ISL1219_REG_MNT 0x15
#घोषणा ISL1219_REG_HRT 0x16
#घोषणा ISL1219_REG_DTT 0x17
#घोषणा ISL1219_REG_MOT 0x18
#घोषणा ISL1219_REG_YRT 0x19
#घोषणा ISL1219_EVT_SECTION_LEN 6

अटल काष्ठा i2c_driver isl1208_driver;

/* ISL1208 various variants */
क्रमागत isl1208_id अणु
	TYPE_ISL1208 = 0,
	TYPE_ISL1209,
	TYPE_ISL1218,
	TYPE_ISL1219,
	ISL_LAST_ID
पूर्ण;

/* Chip capabilities table */
अटल स्थिर काष्ठा isl1208_config अणु
	स्थिर अक्षर	name[8];
	अचिन्हित पूर्णांक	nvmem_length;
	अचिन्हित	has_tamper:1;
	अचिन्हित	has_बारtamp:1;
पूर्ण isl1208_configs[] = अणु
	[TYPE_ISL1208] = अणु "isl1208", 2, false, false पूर्ण,
	[TYPE_ISL1209] = अणु "isl1209", 2, true,  false पूर्ण,
	[TYPE_ISL1218] = अणु "isl1218", 8, false, false पूर्ण,
	[TYPE_ISL1219] = अणु "isl1219", 2, true,  true पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id isl1208_id[] = अणु
	अणु "isl1208", TYPE_ISL1208 पूर्ण,
	अणु "isl1209", TYPE_ISL1209 पूर्ण,
	अणु "isl1218", TYPE_ISL1218 पूर्ण,
	अणु "isl1219", TYPE_ISL1219 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, isl1208_id);

अटल स्थिर __maybe_unused काष्ठा of_device_id isl1208_of_match[] = अणु
	अणु .compatible = "isil,isl1208", .data = &isl1208_configs[TYPE_ISL1208] पूर्ण,
	अणु .compatible = "isil,isl1209", .data = &isl1208_configs[TYPE_ISL1209] पूर्ण,
	अणु .compatible = "isil,isl1218", .data = &isl1208_configs[TYPE_ISL1218] पूर्ण,
	अणु .compatible = "isil,isl1219", .data = &isl1208_configs[TYPE_ISL1219] पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, isl1208_of_match);

/* Device state */
काष्ठा isl1208_state अणु
	काष्ठा nvmem_config nvmem_config;
	काष्ठा rtc_device *rtc;
	स्थिर काष्ठा isl1208_config *config;
पूर्ण;

/* block पढ़ो */
अटल पूर्णांक
isl1208_i2c_पढ़ो_regs(काष्ठा i2c_client *client, u8 reg, u8 buf[],
		      अचिन्हित len)
अणु
	पूर्णांक ret;

	WARN_ON(reg > ISL1219_REG_YRT);
	WARN_ON(reg + len > ISL1219_REG_YRT + 1);

	ret = i2c_smbus_पढ़ो_i2c_block_data(client, reg, len, buf);
	वापस (ret < 0) ? ret : 0;
पूर्ण

/* block ग_लिखो */
अटल पूर्णांक
isl1208_i2c_set_regs(काष्ठा i2c_client *client, u8 reg, u8 स्थिर buf[],
		     अचिन्हित len)
अणु
	पूर्णांक ret;

	WARN_ON(reg > ISL1219_REG_YRT);
	WARN_ON(reg + len > ISL1219_REG_YRT + 1);

	ret = i2c_smbus_ग_लिखो_i2c_block_data(client, reg, len, buf);
	वापस (ret < 0) ? ret : 0;
पूर्ण

/* simple check to see whether we have a isl1208 */
अटल पूर्णांक
isl1208_i2c_validate_client(काष्ठा i2c_client *client)
अणु
	u8 regs[ISL1208_RTC_SECTION_LEN] = अणु 0, पूर्ण;
	u8 zero_mask[ISL1208_RTC_SECTION_LEN] = अणु
		0x80, 0x80, 0x40, 0xc0, 0xe0, 0x00, 0xf8
	पूर्ण;
	पूर्णांक i;
	पूर्णांक ret;

	ret = isl1208_i2c_पढ़ो_regs(client, 0, regs, ISL1208_RTC_SECTION_LEN);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ISL1208_RTC_SECTION_LEN; ++i) अणु
		अगर (regs[i] & zero_mask[i])	/* check अगर bits are cleared */
			वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
isl1208_i2c_get_sr(काष्ठा i2c_client *client)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(client, ISL1208_REG_SR);
पूर्ण

अटल पूर्णांक
isl1208_i2c_get_atr(काष्ठा i2c_client *client)
अणु
	पूर्णांक atr = i2c_smbus_पढ़ो_byte_data(client, ISL1208_REG_ATR);
	अगर (atr < 0)
		वापस atr;

	/* The 6bit value in the ATR रेजिस्टर controls the load
	 * capacitance C_load * in steps of 0.25pF
	 *
	 * bit (1<<5) of the ATR रेजिस्टर is inverted
	 *
	 * C_load(ATR=0x20) =  4.50pF
	 * C_load(ATR=0x00) = 12.50pF
	 * C_load(ATR=0x1f) = 20.25pF
	 *
	 */

	atr &= 0x3f;		/* mask out lsb */
	atr ^= 1 << 5;		/* invert 6th bit */
	atr += 2 * 9;		/* add offset of 4.5pF; unit[atr] = 0.25pF */

	वापस atr;
पूर्ण

/* वापसs adjusपंचांगent value + 100 */
अटल पूर्णांक
isl1208_i2c_get_dtr(काष्ठा i2c_client *client)
अणु
	पूर्णांक dtr = i2c_smbus_पढ़ो_byte_data(client, ISL1208_REG_DTR);
	अगर (dtr < 0)
		वापस -EIO;

	/* dtr encodes adjusपंचांगents of अणु-60,-40,-20,0,20,40,60पूर्ण ppm */
	dtr = ((dtr & 0x3) * 20) * (dtr & (1 << 2) ? -1 : 1);

	वापस dtr + 100;
पूर्ण

अटल पूर्णांक
isl1208_i2c_get_usr(काष्ठा i2c_client *client)
अणु
	u8 buf[ISL1208_USR_SECTION_LEN] = अणु 0, पूर्ण;
	पूर्णांक ret;

	ret = isl1208_i2c_पढ़ो_regs(client, ISL1208_REG_USR1, buf,
				    ISL1208_USR_SECTION_LEN);
	अगर (ret < 0)
		वापस ret;

	वापस (buf[1] << 8) | buf[0];
पूर्ण

अटल पूर्णांक
isl1208_i2c_set_usr(काष्ठा i2c_client *client, u16 usr)
अणु
	u8 buf[ISL1208_USR_SECTION_LEN];

	buf[0] = usr & 0xff;
	buf[1] = (usr >> 8) & 0xff;

	वापस isl1208_i2c_set_regs(client, ISL1208_REG_USR1, buf,
				    ISL1208_USR_SECTION_LEN);
पूर्ण

अटल पूर्णांक
isl1208_rtc_toggle_alarm(काष्ठा i2c_client *client, पूर्णांक enable)
अणु
	पूर्णांक icr = i2c_smbus_पढ़ो_byte_data(client, ISL1208_REG_INT);

	अगर (icr < 0) अणु
		dev_err(&client->dev, "%s: reading INT failed\n", __func__);
		वापस icr;
	पूर्ण

	अगर (enable)
		icr |= ISL1208_REG_INT_ALME | ISL1208_REG_INT_IM;
	अन्यथा
		icr &= ~(ISL1208_REG_INT_ALME | ISL1208_REG_INT_IM);

	icr = i2c_smbus_ग_लिखो_byte_data(client, ISL1208_REG_INT, icr);
	अगर (icr < 0) अणु
		dev_err(&client->dev, "%s: writing INT failed\n", __func__);
		वापस icr;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
isl1208_rtc_proc(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	काष्ठा i2c_client *स्थिर client = to_i2c_client(dev);
	पूर्णांक sr, dtr, atr, usr;

	sr = isl1208_i2c_get_sr(client);
	अगर (sr < 0) अणु
		dev_err(&client->dev, "%s: reading SR failed\n", __func__);
		वापस sr;
	पूर्ण

	seq_म_लिखो(seq, "status_reg\t:%s%s%s%s%s%s (0x%.2x)\n",
		   (sr & ISL1208_REG_SR_RTCF) ? " RTCF" : "",
		   (sr & ISL1208_REG_SR_BAT) ? " BAT" : "",
		   (sr & ISL1208_REG_SR_ALM) ? " ALM" : "",
		   (sr & ISL1208_REG_SR_WRTC) ? " WRTC" : "",
		   (sr & ISL1208_REG_SR_XTOSCB) ? " XTOSCB" : "",
		   (sr & ISL1208_REG_SR_ARST) ? " ARST" : "", sr);

	seq_म_लिखो(seq, "batt_status\t: %s\n",
		   (sr & ISL1208_REG_SR_RTCF) ? "bad" : "okay");

	dtr = isl1208_i2c_get_dtr(client);
	अगर (dtr >= 0)
		seq_म_लिखो(seq, "digital_trim\t: %d ppm\n", dtr - 100);

	atr = isl1208_i2c_get_atr(client);
	अगर (atr >= 0)
		seq_म_लिखो(seq, "analog_trim\t: %d.%.2d pF\n",
			   atr >> 2, (atr & 0x3) * 25);

	usr = isl1208_i2c_get_usr(client);
	अगर (usr >= 0)
		seq_म_लिखो(seq, "user_data\t: 0x%.4x\n", usr);

	वापस 0;
पूर्ण

अटल पूर्णांक
isl1208_i2c_पढ़ो_समय(काष्ठा i2c_client *client, काष्ठा rtc_समय *पंचांग)
अणु
	पूर्णांक sr;
	u8 regs[ISL1208_RTC_SECTION_LEN] = अणु 0, पूर्ण;

	sr = isl1208_i2c_get_sr(client);
	अगर (sr < 0) अणु
		dev_err(&client->dev, "%s: reading SR failed\n", __func__);
		वापस -EIO;
	पूर्ण

	sr = isl1208_i2c_पढ़ो_regs(client, 0, regs, ISL1208_RTC_SECTION_LEN);
	अगर (sr < 0) अणु
		dev_err(&client->dev, "%s: reading RTC section failed\n",
			__func__);
		वापस sr;
	पूर्ण

	पंचांग->पंचांग_sec = bcd2bin(regs[ISL1208_REG_SC]);
	पंचांग->पंचांग_min = bcd2bin(regs[ISL1208_REG_MN]);

	/* HR field has a more complex पूर्णांकerpretation */
	अणु
		स्थिर u8 _hr = regs[ISL1208_REG_HR];
		अगर (_hr & ISL1208_REG_HR_MIL)	/* 24h क्रमmat */
			पंचांग->पंचांग_hour = bcd2bin(_hr & 0x3f);
		अन्यथा अणु
			/* 12h क्रमmat */
			पंचांग->पंचांग_hour = bcd2bin(_hr & 0x1f);
			अगर (_hr & ISL1208_REG_HR_PM)	/* PM flag set */
				पंचांग->पंचांग_hour += 12;
		पूर्ण
	पूर्ण

	पंचांग->पंचांग_mday = bcd2bin(regs[ISL1208_REG_DT]);
	पंचांग->पंचांग_mon = bcd2bin(regs[ISL1208_REG_MO]) - 1;	/* rtc starts at 1 */
	पंचांग->पंचांग_year = bcd2bin(regs[ISL1208_REG_YR]) + 100;
	पंचांग->पंचांग_wday = bcd2bin(regs[ISL1208_REG_DW]);

	वापस 0;
पूर्ण

अटल पूर्णांक
isl1208_i2c_पढ़ो_alarm(काष्ठा i2c_client *client, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा rtc_समय *स्थिर पंचांग = &alarm->समय;
	u8 regs[ISL1208_ALARM_SECTION_LEN] = अणु 0, पूर्ण;
	पूर्णांक icr, yr, sr = isl1208_i2c_get_sr(client);

	अगर (sr < 0) अणु
		dev_err(&client->dev, "%s: reading SR failed\n", __func__);
		वापस sr;
	पूर्ण

	sr = isl1208_i2c_पढ़ो_regs(client, ISL1208_REG_SCA, regs,
				   ISL1208_ALARM_SECTION_LEN);
	अगर (sr < 0) अणु
		dev_err(&client->dev, "%s: reading alarm section failed\n",
			__func__);
		वापस sr;
	पूर्ण

	/* MSB of each alarm रेजिस्टर is an enable bit */
	पंचांग->पंचांग_sec = bcd2bin(regs[ISL1208_REG_SCA - ISL1208_REG_SCA] & 0x7f);
	पंचांग->पंचांग_min = bcd2bin(regs[ISL1208_REG_MNA - ISL1208_REG_SCA] & 0x7f);
	पंचांग->पंचांग_hour = bcd2bin(regs[ISL1208_REG_HRA - ISL1208_REG_SCA] & 0x3f);
	पंचांग->पंचांग_mday = bcd2bin(regs[ISL1208_REG_DTA - ISL1208_REG_SCA] & 0x3f);
	पंचांग->पंचांग_mon =
		bcd2bin(regs[ISL1208_REG_MOA - ISL1208_REG_SCA] & 0x1f) - 1;
	पंचांग->पंचांग_wday = bcd2bin(regs[ISL1208_REG_DWA - ISL1208_REG_SCA] & 0x03);

	/* The alarm करोesn't store the year so get it from the rtc section */
	yr = i2c_smbus_पढ़ो_byte_data(client, ISL1208_REG_YR);
	अगर (yr < 0) अणु
		dev_err(&client->dev, "%s: reading RTC YR failed\n", __func__);
		वापस yr;
	पूर्ण
	पंचांग->पंचांग_year = bcd2bin(yr) + 100;

	icr = i2c_smbus_पढ़ो_byte_data(client, ISL1208_REG_INT);
	अगर (icr < 0) अणु
		dev_err(&client->dev, "%s: reading INT failed\n", __func__);
		वापस icr;
	पूर्ण
	alarm->enabled = !!(icr & ISL1208_REG_INT_ALME);

	वापस 0;
पूर्ण

अटल पूर्णांक
isl1208_i2c_set_alarm(काष्ठा i2c_client *client, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा rtc_समय *alarm_पंचांग = &alarm->समय;
	u8 regs[ISL1208_ALARM_SECTION_LEN] = अणु 0, पूर्ण;
	स्थिर पूर्णांक offs = ISL1208_REG_SCA;
	काष्ठा rtc_समय rtc_पंचांग;
	पूर्णांक err, enable;

	err = isl1208_i2c_पढ़ो_समय(client, &rtc_पंचांग);
	अगर (err)
		वापस err;

	/* If the alarm समय is beक्रमe the current समय disable the alarm */
	अगर (!alarm->enabled || rtc_पंचांग_sub(alarm_पंचांग, &rtc_पंचांग) <= 0)
		enable = 0x00;
	अन्यथा
		enable = 0x80;

	/* Program the alarm and enable it क्रम each setting */
	regs[ISL1208_REG_SCA - offs] = bin2bcd(alarm_पंचांग->पंचांग_sec) | enable;
	regs[ISL1208_REG_MNA - offs] = bin2bcd(alarm_पंचांग->पंचांग_min) | enable;
	regs[ISL1208_REG_HRA - offs] = bin2bcd(alarm_पंचांग->पंचांग_hour) |
		ISL1208_REG_HR_MIL | enable;

	regs[ISL1208_REG_DTA - offs] = bin2bcd(alarm_पंचांग->पंचांग_mday) | enable;
	regs[ISL1208_REG_MOA - offs] = bin2bcd(alarm_पंचांग->पंचांग_mon + 1) | enable;
	regs[ISL1208_REG_DWA - offs] = bin2bcd(alarm_पंचांग->पंचांग_wday & 7) | enable;

	/* ग_लिखो ALARM रेजिस्टरs */
	err = isl1208_i2c_set_regs(client, offs, regs,
				  ISL1208_ALARM_SECTION_LEN);
	अगर (err < 0) अणु
		dev_err(&client->dev, "%s: writing ALARM section failed\n",
			__func__);
		वापस err;
	पूर्ण

	err = isl1208_rtc_toggle_alarm(client, enable);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक
isl1208_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	वापस isl1208_i2c_पढ़ो_समय(to_i2c_client(dev), पंचांग);
पूर्ण

अटल पूर्णांक
isl1208_i2c_set_समय(काष्ठा i2c_client *client, काष्ठा rtc_समय स्थिर *पंचांग)
अणु
	पूर्णांक sr;
	u8 regs[ISL1208_RTC_SECTION_LEN] = अणु 0, पूर्ण;

	/* The घड़ी has an 8 bit wide bcd-coded रेजिस्टर (they never learn)
	 * क्रम the year. पंचांग_year is an offset from 1900 and we are पूर्णांकerested
	 * in the 2000-2099 range, so any value less than 100 is invalid.
	 */
	अगर (पंचांग->पंचांग_year < 100)
		वापस -EINVAL;

	regs[ISL1208_REG_SC] = bin2bcd(पंचांग->पंचांग_sec);
	regs[ISL1208_REG_MN] = bin2bcd(पंचांग->पंचांग_min);
	regs[ISL1208_REG_HR] = bin2bcd(पंचांग->पंचांग_hour) | ISL1208_REG_HR_MIL;

	regs[ISL1208_REG_DT] = bin2bcd(पंचांग->पंचांग_mday);
	regs[ISL1208_REG_MO] = bin2bcd(पंचांग->पंचांग_mon + 1);
	regs[ISL1208_REG_YR] = bin2bcd(पंचांग->पंचांग_year - 100);

	regs[ISL1208_REG_DW] = bin2bcd(पंचांग->पंचांग_wday & 7);

	sr = isl1208_i2c_get_sr(client);
	अगर (sr < 0) अणु
		dev_err(&client->dev, "%s: reading SR failed\n", __func__);
		वापस sr;
	पूर्ण

	/* set WRTC */
	sr = i2c_smbus_ग_लिखो_byte_data(client, ISL1208_REG_SR,
				       sr | ISL1208_REG_SR_WRTC);
	अगर (sr < 0) अणु
		dev_err(&client->dev, "%s: writing SR failed\n", __func__);
		वापस sr;
	पूर्ण

	/* ग_लिखो RTC रेजिस्टरs */
	sr = isl1208_i2c_set_regs(client, 0, regs, ISL1208_RTC_SECTION_LEN);
	अगर (sr < 0) अणु
		dev_err(&client->dev, "%s: writing RTC section failed\n",
			__func__);
		वापस sr;
	पूर्ण

	/* clear WRTC again */
	sr = isl1208_i2c_get_sr(client);
	अगर (sr < 0) अणु
		dev_err(&client->dev, "%s: reading SR failed\n", __func__);
		वापस sr;
	पूर्ण
	sr = i2c_smbus_ग_लिखो_byte_data(client, ISL1208_REG_SR,
				       sr & ~ISL1208_REG_SR_WRTC);
	अगर (sr < 0) अणु
		dev_err(&client->dev, "%s: writing SR failed\n", __func__);
		वापस sr;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक
isl1208_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	वापस isl1208_i2c_set_समय(to_i2c_client(dev), पंचांग);
पूर्ण

अटल पूर्णांक
isl1208_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	वापस isl1208_i2c_पढ़ो_alarm(to_i2c_client(dev), alarm);
पूर्ण

अटल पूर्णांक
isl1208_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	वापस isl1208_i2c_set_alarm(to_i2c_client(dev), alarm);
पूर्ण

अटल sमाप_प्रकार बारtamp0_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	पूर्णांक sr;

	sr = isl1208_i2c_get_sr(client);
	अगर (sr < 0) अणु
		dev_err(dev, "%s: reading SR failed\n", __func__);
		वापस sr;
	पूर्ण

	sr &= ~ISL1208_REG_SR_EVT;

	sr = i2c_smbus_ग_लिखो_byte_data(client, ISL1208_REG_SR, sr);
	अगर (sr < 0)
		dev_err(dev, "%s: writing SR failed\n",
			__func__);

	वापस count;
पूर्ण;

अटल sमाप_प्रकार बारtamp0_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	u8 regs[ISL1219_EVT_SECTION_LEN] = अणु 0, पूर्ण;
	काष्ठा rtc_समय पंचांग;
	पूर्णांक sr;

	sr = isl1208_i2c_get_sr(client);
	अगर (sr < 0) अणु
		dev_err(dev, "%s: reading SR failed\n", __func__);
		वापस sr;
	पूर्ण

	अगर (!(sr & ISL1208_REG_SR_EVT))
		वापस 0;

	sr = isl1208_i2c_पढ़ो_regs(client, ISL1219_REG_SCT, regs,
				   ISL1219_EVT_SECTION_LEN);
	अगर (sr < 0) अणु
		dev_err(dev, "%s: reading event section failed\n",
			__func__);
		वापस 0;
	पूर्ण

	/* MSB of each alarm रेजिस्टर is an enable bit */
	पंचांग.पंचांग_sec = bcd2bin(regs[ISL1219_REG_SCT - ISL1219_REG_SCT] & 0x7f);
	पंचांग.पंचांग_min = bcd2bin(regs[ISL1219_REG_MNT - ISL1219_REG_SCT] & 0x7f);
	पंचांग.पंचांग_hour = bcd2bin(regs[ISL1219_REG_HRT - ISL1219_REG_SCT] & 0x3f);
	पंचांग.पंचांग_mday = bcd2bin(regs[ISL1219_REG_DTT - ISL1219_REG_SCT] & 0x3f);
	पंचांग.पंचांग_mon =
		bcd2bin(regs[ISL1219_REG_MOT - ISL1219_REG_SCT] & 0x1f) - 1;
	पंचांग.पंचांग_year = bcd2bin(regs[ISL1219_REG_YRT - ISL1219_REG_SCT]) + 100;

	sr = rtc_valid_पंचांग(&पंचांग);
	अगर (sr)
		वापस sr;

	वापस प्र_लिखो(buf, "%llu\n",
				(अचिन्हित दीर्घ दीर्घ)rtc_पंचांग_to_समय64(&पंचांग));
पूर्ण;

अटल DEVICE_ATTR_RW(बारtamp0);

अटल irqवापस_t
isl1208_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);
	काष्ठा i2c_client *client = data;
	काष्ठा isl1208_state *isl1208 = i2c_get_clientdata(client);
	पूर्णांक handled = 0, sr, err;

	/*
	 * I2C पढ़ोs get NAK'ed अगर we पढ़ो straight away after an पूर्णांकerrupt?
	 * Using a mdelay/msleep didn't seem to help either, so we work around
	 * this by continually trying to पढ़ो the रेजिस्टर क्रम a लघु समय.
	 */
	जबतक (1) अणु
		sr = isl1208_i2c_get_sr(client);
		अगर (sr >= 0)
			अवरोध;

		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(&client->dev, "%s: reading SR failed\n",
				__func__);
			वापस sr;
		पूर्ण
	पूर्ण

	अगर (sr & ISL1208_REG_SR_ALM) अणु
		dev_dbg(&client->dev, "alarm!\n");

		rtc_update_irq(isl1208->rtc, 1, RTC_IRQF | RTC_AF);

		/* Clear the alarm */
		sr &= ~ISL1208_REG_SR_ALM;
		sr = i2c_smbus_ग_लिखो_byte_data(client, ISL1208_REG_SR, sr);
		अगर (sr < 0)
			dev_err(&client->dev, "%s: writing SR failed\n",
				__func__);
		अन्यथा
			handled = 1;

		/* Disable the alarm */
		err = isl1208_rtc_toggle_alarm(client, 0);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (isl1208->config->has_tamper && (sr & ISL1208_REG_SR_EVT)) अणु
		dev_warn(&client->dev, "event detected");
		handled = 1;
		अगर (isl1208->config->has_बारtamp)
			sysfs_notअगरy(&isl1208->rtc->dev.kobj, शून्य,
				     dev_attr_बारtamp0.attr.name);
	पूर्ण

	वापस handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops isl1208_rtc_ops = अणु
	.proc = isl1208_rtc_proc,
	.पढ़ो_समय = isl1208_rtc_पढ़ो_समय,
	.set_समय = isl1208_rtc_set_समय,
	.पढ़ो_alarm = isl1208_rtc_पढ़ो_alarm,
	.set_alarm = isl1208_rtc_set_alarm,
पूर्ण;

/* sysfs पूर्णांकerface */

अटल sमाप_प्रकार
isl1208_sysfs_show_atrim(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक atr = isl1208_i2c_get_atr(to_i2c_client(dev->parent));
	अगर (atr < 0)
		वापस atr;

	वापस प्र_लिखो(buf, "%d.%.2d pF\n", atr >> 2, (atr & 0x3) * 25);
पूर्ण

अटल DEVICE_ATTR(atrim, S_IRUGO, isl1208_sysfs_show_atrim, शून्य);

अटल sमाप_प्रकार
isl1208_sysfs_show_dtrim(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक dtr = isl1208_i2c_get_dtr(to_i2c_client(dev->parent));
	अगर (dtr < 0)
		वापस dtr;

	वापस प्र_लिखो(buf, "%d ppm\n", dtr - 100);
पूर्ण

अटल DEVICE_ATTR(dtrim, S_IRUGO, isl1208_sysfs_show_dtrim, शून्य);

अटल sमाप_प्रकार
isl1208_sysfs_show_usr(काष्ठा device *dev,
		       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक usr = isl1208_i2c_get_usr(to_i2c_client(dev->parent));
	अगर (usr < 0)
		वापस usr;

	वापस प्र_लिखो(buf, "0x%.4x\n", usr);
पूर्ण

अटल sमाप_प्रकार
isl1208_sysfs_store_usr(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक usr = -1;

	अगर (buf[0] == '0' && (buf[1] == 'x' || buf[1] == 'X')) अणु
		अगर (माला_पूछो(buf, "%x", &usr) != 1)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (माला_पूछो(buf, "%d", &usr) != 1)
			वापस -EINVAL;
	पूर्ण

	अगर (usr < 0 || usr > 0xffff)
		वापस -EINVAL;

	अगर (isl1208_i2c_set_usr(to_i2c_client(dev->parent), usr))
		वापस -EIO;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(usr, S_IRUGO | S_IWUSR, isl1208_sysfs_show_usr,
		   isl1208_sysfs_store_usr);

अटल काष्ठा attribute *isl1208_rtc_attrs[] = अणु
	&dev_attr_atrim.attr,
	&dev_attr_dtrim.attr,
	&dev_attr_usr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group isl1208_rtc_sysfs_files = अणु
	.attrs	= isl1208_rtc_attrs,
पूर्ण;

अटल काष्ठा attribute *isl1219_rtc_attrs[] = अणु
	&dev_attr_बारtamp0.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group isl1219_rtc_sysfs_files = अणु
	.attrs	= isl1219_rtc_attrs,
पूर्ण;

अटल पूर्णांक isl1208_nvmem_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक off, व्योम *buf,
			      माप_प्रकार count)
अणु
	काष्ठा isl1208_state *isl1208 = priv;
	काष्ठा i2c_client *client = to_i2c_client(isl1208->rtc->dev.parent);
	पूर्णांक ret;

	/* nvmem sanitizes offset/count क्रम us, but count==0 is possible */
	अगर (!count)
		वापस count;
	ret = isl1208_i2c_पढ़ो_regs(client, ISL1208_REG_USR1 + off, buf,
				    count);
	वापस ret == 0 ? count : ret;
पूर्ण

अटल पूर्णांक isl1208_nvmem_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक off, व्योम *buf,
			       माप_प्रकार count)
अणु
	काष्ठा isl1208_state *isl1208 = priv;
	काष्ठा i2c_client *client = to_i2c_client(isl1208->rtc->dev.parent);
	पूर्णांक ret;

	/* nvmem sanitizes off/count क्रम us, but count==0 is possible */
	अगर (!count)
		वापस count;
	ret = isl1208_i2c_set_regs(client, ISL1208_REG_USR1 + off, buf,
				   count);

	वापस ret == 0 ? count : ret;
पूर्ण

अटल स्थिर काष्ठा nvmem_config isl1208_nvmem_config = अणु
	.name = "isl1208_nvram",
	.word_size = 1,
	.stride = 1,
	/* .size from chip specअगरic config */
	.reg_पढ़ो = isl1208_nvmem_पढ़ो,
	.reg_ग_लिखो = isl1208_nvmem_ग_लिखो,
पूर्ण;

अटल पूर्णांक isl1208_setup_irq(काष्ठा i2c_client *client, पूर्णांक irq)
अणु
	पूर्णांक rc = devm_request_thपढ़ोed_irq(&client->dev, irq, शून्य,
					isl1208_rtc_पूर्णांकerrupt,
					IRQF_SHARED | IRQF_ONESHOT,
					isl1208_driver.driver.name,
					client);
	अगर (!rc) अणु
		device_init_wakeup(&client->dev, 1);
		enable_irq_wake(irq);
	पूर्ण अन्यथा अणु
		dev_err(&client->dev,
			"Unable to request irq %d, no alarm support\n",
			irq);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक
isl1208_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक rc = 0;
	काष्ठा isl1208_state *isl1208;
	पूर्णांक evdet_irq = -1;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	अगर (isl1208_i2c_validate_client(client) < 0)
		वापस -ENODEV;

	/* Allocate driver state, poपूर्णांक i2c client data to it */
	isl1208 = devm_kzalloc(&client->dev, माप(*isl1208), GFP_KERNEL);
	अगर (!isl1208)
		वापस -ENOMEM;
	i2c_set_clientdata(client, isl1208);

	/* Determine which chip we have */
	अगर (client->dev.of_node) अणु
		isl1208->config = of_device_get_match_data(&client->dev);
		अगर (!isl1208->config)
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		अगर (id->driver_data >= ISL_LAST_ID)
			वापस -ENODEV;
		isl1208->config = &isl1208_configs[id->driver_data];
	पूर्ण

	isl1208->rtc = devm_rtc_allocate_device(&client->dev);
	अगर (IS_ERR(isl1208->rtc))
		वापस PTR_ERR(isl1208->rtc);

	isl1208->rtc->ops = &isl1208_rtc_ops;

	/* Setup nvmem configuration in driver state काष्ठा */
	isl1208->nvmem_config = isl1208_nvmem_config;
	isl1208->nvmem_config.size = isl1208->config->nvmem_length;
	isl1208->nvmem_config.priv = isl1208;

	rc = isl1208_i2c_get_sr(client);
	अगर (rc < 0) अणु
		dev_err(&client->dev, "reading status failed\n");
		वापस rc;
	पूर्ण

	अगर (rc & ISL1208_REG_SR_RTCF)
		dev_warn(&client->dev, "rtc power failure detected, "
			 "please set clock.\n");

	अगर (isl1208->config->has_tamper) अणु
		काष्ठा device_node *np = client->dev.of_node;
		u32 evienb;

		rc = i2c_smbus_पढ़ो_byte_data(client, ISL1219_REG_EV);
		अगर (rc < 0) अणु
			dev_err(&client->dev, "failed to read EV reg\n");
			वापस rc;
		पूर्ण
		rc |= ISL1219_REG_EV_EVEN;
		अगर (!of_property_पढ़ो_u32(np, "isil,ev-evienb", &evienb)) अणु
			अगर (evienb)
				rc |= ISL1219_REG_EV_EVIENB;
			अन्यथा
				rc &= ~ISL1219_REG_EV_EVIENB;
		पूर्ण
		rc = i2c_smbus_ग_लिखो_byte_data(client, ISL1219_REG_EV, rc);
		अगर (rc < 0) अणु
			dev_err(&client->dev, "could not enable tamper detection\n");
			वापस rc;
		पूर्ण
		evdet_irq = of_irq_get_byname(np, "evdet");
	पूर्ण
	अगर (isl1208->config->has_बारtamp) अणु
		rc = rtc_add_group(isl1208->rtc, &isl1219_rtc_sysfs_files);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = rtc_add_group(isl1208->rtc, &isl1208_rtc_sysfs_files);
	अगर (rc)
		वापस rc;

	अगर (client->irq > 0)
		rc = isl1208_setup_irq(client, client->irq);
	अगर (rc)
		वापस rc;

	अगर (evdet_irq > 0 && evdet_irq != client->irq)
		rc = isl1208_setup_irq(client, evdet_irq);
	अगर (rc)
		वापस rc;

	rc = devm_rtc_nvmem_रेजिस्टर(isl1208->rtc, &isl1208->nvmem_config);
	अगर (rc)
		वापस rc;

	वापस devm_rtc_रेजिस्टर_device(isl1208->rtc);
पूर्ण

अटल काष्ठा i2c_driver isl1208_driver = अणु
	.driver = अणु
		.name = "rtc-isl1208",
		.of_match_table = of_match_ptr(isl1208_of_match),
	पूर्ण,
	.probe = isl1208_probe,
	.id_table = isl1208_id,
पूर्ण;

module_i2c_driver(isl1208_driver);

MODULE_AUTHOR("Herbert Valerio Riedel <hvr@gnu.org>");
MODULE_DESCRIPTION("Intersil ISL1208 RTC driver");
MODULE_LICENSE("GPL");
