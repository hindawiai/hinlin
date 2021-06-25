<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An i2c driver क्रम the Xicor/Intersil X1205 RTC
 * Copyright 2004 Karen Spearel
 * Copyright 2005 Alessandro Zummo
 *
 * please send all reports to:
 *	Karen Spearel <kas111 at gmail करोt com>
 *	Alessandro Zummo <a.zummo@towertech.it>
 *
 * based on a lot of other RTC drivers.
 *
 * Inक्रमmation and datasheet:
 * http://www.पूर्णांकersil.com/cda/deviceinfo/0,1477,X1205,00.hपंचांगl
 */

#समावेश <linux/i2c.h>
#समावेश <linux/bcd.h>
#समावेश <linux/rtc.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>

/* offsets पूर्णांकo CCR area */

#घोषणा CCR_SEC			0
#घोषणा CCR_MIN			1
#घोषणा CCR_HOUR		2
#घोषणा CCR_MDAY		3
#घोषणा CCR_MONTH		4
#घोषणा CCR_YEAR		5
#घोषणा CCR_WDAY		6
#घोषणा CCR_Y2K			7

#घोषणा X1205_REG_SR		0x3F	/* status रेजिस्टर */
#घोषणा X1205_REG_Y2K		0x37
#घोषणा X1205_REG_DW		0x36
#घोषणा X1205_REG_YR		0x35
#घोषणा X1205_REG_MO		0x34
#घोषणा X1205_REG_DT		0x33
#घोषणा X1205_REG_HR		0x32
#घोषणा X1205_REG_MN		0x31
#घोषणा X1205_REG_SC		0x30
#घोषणा X1205_REG_DTR		0x13
#घोषणा X1205_REG_ATR		0x12
#घोषणा X1205_REG_INT		0x11
#घोषणा X1205_REG_0		0x10
#घोषणा X1205_REG_Y2K1		0x0F
#घोषणा X1205_REG_DWA1		0x0E
#घोषणा X1205_REG_YRA1		0x0D
#घोषणा X1205_REG_MOA1		0x0C
#घोषणा X1205_REG_DTA1		0x0B
#घोषणा X1205_REG_HRA1		0x0A
#घोषणा X1205_REG_MNA1		0x09
#घोषणा X1205_REG_SCA1		0x08
#घोषणा X1205_REG_Y2K0		0x07
#घोषणा X1205_REG_DWA0		0x06
#घोषणा X1205_REG_YRA0		0x05
#घोषणा X1205_REG_MOA0		0x04
#घोषणा X1205_REG_DTA0		0x03
#घोषणा X1205_REG_HRA0		0x02
#घोषणा X1205_REG_MNA0		0x01
#घोषणा X1205_REG_SCA0		0x00

#घोषणा X1205_CCR_BASE		0x30	/* Base address of CCR */
#घोषणा X1205_ALM0_BASE		0x00	/* Base address of ALARM0 */

#घोषणा X1205_SR_RTCF		0x01	/* Clock failure */
#घोषणा X1205_SR_WEL		0x02	/* Write Enable Latch */
#घोषणा X1205_SR_RWEL		0x04	/* Register Write Enable */
#घोषणा X1205_SR_AL0		0x20	/* Alarm 0 match */

#घोषणा X1205_DTR_DTR0		0x01
#घोषणा X1205_DTR_DTR1		0x02
#घोषणा X1205_DTR_DTR2		0x04

#घोषणा X1205_HR_MIL		0x80	/* Set in ccr.hour क्रम 24 hr mode */

#घोषणा X1205_INT_AL0E		0x20	/* Alarm 0 enable */

अटल काष्ठा i2c_driver x1205_driver;

/*
 * In the routines that deal directly with the x1205 hardware, we use
 * rtc_समय -- month 0-11, hour 0-23, yr = calendar year-epoch
 * Epoch is initialized as 2000. Time is set to UTC.
 */
अटल पूर्णांक x1205_get_dateसमय(काष्ठा i2c_client *client, काष्ठा rtc_समय *पंचांग,
				अचिन्हित अक्षर reg_base)
अणु
	अचिन्हित अक्षर dt_addr[2] = अणु 0, reg_base पूर्ण;
	अचिन्हित अक्षर buf[8];
	पूर्णांक i;

	काष्ठा i2c_msg msgs[] = अणु
		अणु/* setup पढ़ो ptr */
			.addr = client->addr,
			.len = 2,
			.buf = dt_addr
		पूर्ण,
		अणु/* पढ़ो date */
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 8,
			.buf = buf
		पूर्ण,
	पूर्ण;

	/* पढ़ो date रेजिस्टरs */
	अगर (i2c_transfer(client->adapter, &msgs[0], 2) != 2) अणु
		dev_err(&client->dev, "%s: read error\n", __func__);
		वापस -EIO;
	पूर्ण

	dev_dbg(&client->dev,
		"%s: raw read data - sec=%02x, min=%02x, hr=%02x, "
		"mday=%02x, mon=%02x, year=%02x, wday=%02x, y2k=%02x\n",
		__func__,
		buf[0], buf[1], buf[2], buf[3],
		buf[4], buf[5], buf[6], buf[7]);

	/* Mask out the enable bits अगर these are alarm रेजिस्टरs */
	अगर (reg_base < X1205_CCR_BASE)
		क्रम (i = 0; i <= 4; i++)
			buf[i] &= 0x7F;

	पंचांग->पंचांग_sec = bcd2bin(buf[CCR_SEC]);
	पंचांग->पंचांग_min = bcd2bin(buf[CCR_MIN]);
	पंचांग->पंचांग_hour = bcd2bin(buf[CCR_HOUR] & 0x3F); /* hr is 0-23 */
	पंचांग->पंचांग_mday = bcd2bin(buf[CCR_MDAY]);
	पंचांग->पंचांग_mon = bcd2bin(buf[CCR_MONTH]) - 1; /* mon is 0-11 */
	पंचांग->पंचांग_year = bcd2bin(buf[CCR_YEAR])
			+ (bcd2bin(buf[CCR_Y2K]) * 100) - 1900;
	पंचांग->पंचांग_wday = buf[CCR_WDAY];

	dev_dbg(&client->dev, "%s: tm is secs=%d, mins=%d, hours=%d, "
		"mday=%d, mon=%d, year=%d, wday=%d\n",
		__func__,
		पंचांग->पंचांग_sec, पंचांग->पंचांग_min, पंचांग->पंचांग_hour,
		पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	वापस 0;
पूर्ण

अटल पूर्णांक x1205_get_status(काष्ठा i2c_client *client, अचिन्हित अक्षर *sr)
अणु
	अटल अचिन्हित अक्षर sr_addr[2] = अणु 0, X1205_REG_SR पूर्ण;

	काष्ठा i2c_msg msgs[] = अणु
		अणु     /* setup पढ़ो ptr */
			.addr = client->addr,
			.len = 2,
			.buf = sr_addr
		पूर्ण,
		अणु    /* पढ़ो status */
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = sr
		पूर्ण,
	पूर्ण;

	/* पढ़ो status रेजिस्टर */
	अगर (i2c_transfer(client->adapter, &msgs[0], 2) != 2) अणु
		dev_err(&client->dev, "%s: read error\n", __func__);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक x1205_set_dateसमय(काष्ठा i2c_client *client, काष्ठा rtc_समय *पंचांग,
			u8 reg_base, अचिन्हित अक्षर alm_enable)
अणु
	पूर्णांक i, xfer;
	अचिन्हित अक्षर rdata[10] = अणु 0, reg_base पूर्ण;
	अचिन्हित अक्षर *buf = rdata + 2;

	अटल स्थिर अचिन्हित अक्षर wel[3] = अणु 0, X1205_REG_SR,
						X1205_SR_WEL पूर्ण;

	अटल स्थिर अचिन्हित अक्षर rwel[3] = अणु 0, X1205_REG_SR,
						X1205_SR_WEL | X1205_SR_RWEL पूर्ण;

	अटल स्थिर अचिन्हित अक्षर diswe[3] = अणु 0, X1205_REG_SR, 0 पूर्ण;

	dev_dbg(&client->dev,
		"%s: sec=%d min=%d hour=%d mday=%d mon=%d year=%d wday=%d\n",
		__func__, पंचांग->पंचांग_sec, पंचांग->पंचांग_min, पंचांग->पंचांग_hour, पंचांग->पंचांग_mday,
		पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	buf[CCR_SEC] = bin2bcd(पंचांग->पंचांग_sec);
	buf[CCR_MIN] = bin2bcd(पंचांग->पंचांग_min);

	/* set hour and 24hr bit */
	buf[CCR_HOUR] = bin2bcd(पंचांग->पंचांग_hour) | X1205_HR_MIL;

	buf[CCR_MDAY] = bin2bcd(पंचांग->पंचांग_mday);

	/* month, 1 - 12 */
	buf[CCR_MONTH] = bin2bcd(पंचांग->पंचांग_mon + 1);

	/* year, since the rtc epoch*/
	buf[CCR_YEAR] = bin2bcd(पंचांग->पंचांग_year % 100);
	buf[CCR_WDAY] = पंचांग->पंचांग_wday & 0x07;
	buf[CCR_Y2K] = bin2bcd((पंचांग->पंचांग_year + 1900) / 100);

	/* If writing alarm रेजिस्टरs, set compare bits on रेजिस्टरs 0-4 */
	अगर (reg_base < X1205_CCR_BASE)
		क्रम (i = 0; i <= 4; i++)
			buf[i] |= 0x80;

	/* this sequence is required to unlock the chip */
	xfer = i2c_master_send(client, wel, 3);
	अगर (xfer != 3) अणु
		dev_err(&client->dev, "%s: wel - %d\n", __func__, xfer);
		वापस -EIO;
	पूर्ण

	xfer = i2c_master_send(client, rwel, 3);
	अगर (xfer != 3) अणु
		dev_err(&client->dev, "%s: rwel - %d\n", __func__, xfer);
		वापस -EIO;
	पूर्ण

	xfer = i2c_master_send(client, rdata, माप(rdata));
	अगर (xfer != माप(rdata)) अणु
		dev_err(&client->dev,
			"%s: result=%d addr=%02x, data=%02x\n",
			__func__,
			 xfer, rdata[1], rdata[2]);
		वापस -EIO;
	पूर्ण

	/* If we wrote to the nonअस्थिर region, रुको 10msec क्रम ग_लिखो cycle*/
	अगर (reg_base < X1205_CCR_BASE) अणु
		अचिन्हित अक्षर al0e[3] = अणु 0, X1205_REG_INT, 0 पूर्ण;

		msleep(10);

		/* ...and set or clear the AL0E bit in the INT रेजिस्टर */

		/* Need to set RWEL again as the ग_लिखो has cleared it */
		xfer = i2c_master_send(client, rwel, 3);
		अगर (xfer != 3) अणु
			dev_err(&client->dev,
				"%s: aloe rwel - %d\n",
				__func__,
				xfer);
			वापस -EIO;
		पूर्ण

		अगर (alm_enable)
			al0e[2] = X1205_INT_AL0E;

		xfer = i2c_master_send(client, al0e, 3);
		अगर (xfer != 3) अणु
			dev_err(&client->dev,
				"%s: al0e - %d\n",
				__func__,
				xfer);
			वापस -EIO;
		पूर्ण

		/* and रुको 10msec again क्रम this ग_लिखो to complete */
		msleep(10);
	पूर्ण

	/* disable further ग_लिखोs */
	xfer = i2c_master_send(client, diswe, 3);
	अगर (xfer != 3) अणु
		dev_err(&client->dev, "%s: diswe - %d\n", __func__, xfer);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक x1205_fix_osc(काष्ठा i2c_client *client)
अणु
	पूर्णांक err;
	काष्ठा rtc_समय पंचांग;

	स_रखो(&पंचांग, 0, माप(पंचांग));

	err = x1205_set_dateसमय(client, &पंचांग, X1205_CCR_BASE, 0);
	अगर (err < 0)
		dev_err(&client->dev, "unable to restart the oscillator\n");

	वापस err;
पूर्ण

अटल पूर्णांक x1205_get_dtrim(काष्ठा i2c_client *client, पूर्णांक *trim)
अणु
	अचिन्हित अक्षर dtr;
	अटल अचिन्हित अक्षर dtr_addr[2] = अणु 0, X1205_REG_DTR पूर्ण;

	काष्ठा i2c_msg msgs[] = अणु
		अणु	/* setup पढ़ो ptr */
			.addr = client->addr,
			.len = 2,
			.buf = dtr_addr
		पूर्ण,
		अणु      /* पढ़ो dtr */
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = &dtr
		पूर्ण,
	पूर्ण;

	/* पढ़ो dtr रेजिस्टर */
	अगर (i2c_transfer(client->adapter, &msgs[0], 2) != 2) अणु
		dev_err(&client->dev, "%s: read error\n", __func__);
		वापस -EIO;
	पूर्ण

	dev_dbg(&client->dev, "%s: raw dtr=%x\n", __func__, dtr);

	*trim = 0;

	अगर (dtr & X1205_DTR_DTR0)
		*trim += 20;

	अगर (dtr & X1205_DTR_DTR1)
		*trim += 10;

	अगर (dtr & X1205_DTR_DTR2)
		*trim = -*trim;

	वापस 0;
पूर्ण

अटल पूर्णांक x1205_get_atrim(काष्ठा i2c_client *client, पूर्णांक *trim)
अणु
	s8 atr;
	अटल अचिन्हित अक्षर atr_addr[2] = अणु 0, X1205_REG_ATR पूर्ण;

	काष्ठा i2c_msg msgs[] = अणु
		अणु/* setup पढ़ो ptr */
			.addr = client->addr,
			.len = 2,
			.buf = atr_addr
		पूर्ण,
		अणु/* पढ़ो atr */
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = &atr
		पूर्ण,
	पूर्ण;

	/* पढ़ो atr रेजिस्टर */
	अगर (i2c_transfer(client->adapter, &msgs[0], 2) != 2) अणु
		dev_err(&client->dev, "%s: read error\n", __func__);
		वापस -EIO;
	पूर्ण

	dev_dbg(&client->dev, "%s: raw atr=%x\n", __func__, atr);

	/* atr is a two's complement value on 6 bits,
	 * perक्रमm sign extension. The क्रमmula is
	 * Catr = (atr * 0.25pF) + 11.00pF.
	 */
	atr = sign_extend32(atr, 5);

	dev_dbg(&client->dev, "%s: raw atr=%x (%d)\n", __func__, atr, atr);

	*trim = (atr * 250) + 11000;

	dev_dbg(&client->dev, "%s: real=%d\n", __func__, *trim);

	वापस 0;
पूर्ण

काष्ठा x1205_limit अणु
	अचिन्हित अक्षर reg, mask, min, max;
पूर्ण;

अटल पूर्णांक x1205_validate_client(काष्ठा i2c_client *client)
अणु
	पूर्णांक i, xfer;

	/* Probe array. We will पढ़ो the रेजिस्टर at the specअगरied
	 * address and check अगर the given bits are zero.
	 */
	अटल स्थिर अचिन्हित अक्षर probe_zero_pattern[] = अणु
		/* रेजिस्टर, mask */
		X1205_REG_SR,	0x18,
		X1205_REG_DTR,	0xF8,
		X1205_REG_ATR,	0xC0,
		X1205_REG_INT,	0x18,
		X1205_REG_0,	0xFF,
	पूर्ण;

	अटल स्थिर काष्ठा x1205_limit probe_limits_pattern[] = अणु
		/* रेजिस्टर, mask, min, max */
		अणु X1205_REG_Y2K,	0xFF,	19,	20	पूर्ण,
		अणु X1205_REG_DW,		0xFF,	0,	6	पूर्ण,
		अणु X1205_REG_YR,		0xFF,	0,	99	पूर्ण,
		अणु X1205_REG_MO,		0xFF,	0,	12	पूर्ण,
		अणु X1205_REG_DT,		0xFF,	0,	31	पूर्ण,
		अणु X1205_REG_HR,		0x7F,	0,	23	पूर्ण,
		अणु X1205_REG_MN,		0xFF,	0,	59	पूर्ण,
		अणु X1205_REG_SC,		0xFF,	0,	59	पूर्ण,
		अणु X1205_REG_Y2K1,	0xFF,	19,	20	पूर्ण,
		अणु X1205_REG_Y2K0,	0xFF,	19,	20	पूर्ण,
	पूर्ण;

	/* check that रेजिस्टरs have bits a 0 where expected */
	क्रम (i = 0; i < ARRAY_SIZE(probe_zero_pattern); i += 2) अणु
		अचिन्हित अक्षर buf;

		अचिन्हित अक्षर addr[2] = अणु 0, probe_zero_pattern[i] पूर्ण;

		काष्ठा i2c_msg msgs[2] = अणु
			अणु
				.addr = client->addr,
				.len = 2,
				.buf = addr
			पूर्ण,
			अणु
				.addr = client->addr,
				.flags = I2C_M_RD,
				.len = 1,
				.buf = &buf
			पूर्ण,
		पूर्ण;

		xfer = i2c_transfer(client->adapter, msgs, 2);
		अगर (xfer != 2) अणु
			dev_err(&client->dev,
				"%s: could not read register %x\n",
				__func__, probe_zero_pattern[i]);

			वापस -EIO;
		पूर्ण

		अगर ((buf & probe_zero_pattern[i+1]) != 0) अणु
			dev_err(&client->dev,
				"%s: register=%02x, zero pattern=%d, value=%x\n",
				__func__, probe_zero_pattern[i], i, buf);

			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* check limits (only रेजिस्टरs with bcd values) */
	क्रम (i = 0; i < ARRAY_SIZE(probe_limits_pattern); i++) अणु
		अचिन्हित अक्षर reg, value;

		अचिन्हित अक्षर addr[2] = अणु 0, probe_limits_pattern[i].reg पूर्ण;

		काष्ठा i2c_msg msgs[2] = अणु
			अणु
				.addr = client->addr,
				.len = 2,
				.buf = addr
			पूर्ण,
			अणु
				.addr = client->addr,
				.flags = I2C_M_RD,
				.len = 1,
				.buf = &reg
			पूर्ण,
		पूर्ण;

		xfer = i2c_transfer(client->adapter, msgs, 2);
		अगर (xfer != 2) अणु
			dev_err(&client->dev,
				"%s: could not read register %x\n",
				__func__, probe_limits_pattern[i].reg);

			वापस -EIO;
		पूर्ण

		value = bcd2bin(reg & probe_limits_pattern[i].mask);

		अगर (value > probe_limits_pattern[i].max ||
			value < probe_limits_pattern[i].min) अणु
			dev_dbg(&client->dev,
				"%s: register=%x, lim pattern=%d, value=%d\n",
				__func__, probe_limits_pattern[i].reg,
				i, value);

			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक x1205_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	पूर्णांक err;
	अचिन्हित अक्षर पूर्णांकreg, status;
	अटल अचिन्हित अक्षर पूर्णांक_addr[2] = अणु 0, X1205_REG_INT पूर्ण;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा i2c_msg msgs[] = अणु
		अणु /* setup पढ़ो ptr */
			.addr = client->addr,
			.len = 2,
			.buf = पूर्णांक_addr
		पूर्ण,
		अणु/* पढ़ो INT रेजिस्टर */

			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = &पूर्णांकreg
		पूर्ण,
	पूर्ण;

	/* पढ़ो पूर्णांकerrupt रेजिस्टर and status रेजिस्टर */
	अगर (i2c_transfer(client->adapter, &msgs[0], 2) != 2) अणु
		dev_err(&client->dev, "%s: read error\n", __func__);
		वापस -EIO;
	पूर्ण
	err = x1205_get_status(client, &status);
	अगर (err == 0) अणु
		alrm->pending = (status & X1205_SR_AL0) ? 1 : 0;
		alrm->enabled = (पूर्णांकreg & X1205_INT_AL0E) ? 1 : 0;
		err = x1205_get_dateसमय(client, &alrm->समय, X1205_ALM0_BASE);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक x1205_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	वापस x1205_set_dateसमय(to_i2c_client(dev),
		&alrm->समय, X1205_ALM0_BASE, alrm->enabled);
पूर्ण

अटल पूर्णांक x1205_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	वापस x1205_get_dateसमय(to_i2c_client(dev),
		पंचांग, X1205_CCR_BASE);
पूर्ण

अटल पूर्णांक x1205_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	वापस x1205_set_dateसमय(to_i2c_client(dev),
		पंचांग, X1205_CCR_BASE, 0);
पूर्ण

अटल पूर्णांक x1205_rtc_proc(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	पूर्णांक err, dtrim, atrim;

	err = x1205_get_dtrim(to_i2c_client(dev), &dtrim);
	अगर (!err)
		seq_म_लिखो(seq, "digital_trim\t: %d ppm\n", dtrim);

	err = x1205_get_atrim(to_i2c_client(dev), &atrim);
	अगर (!err)
		seq_म_लिखो(seq, "analog_trim\t: %d.%02d pF\n",
			atrim / 1000, atrim % 1000);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops x1205_rtc_ops = अणु
	.proc		= x1205_rtc_proc,
	.पढ़ो_समय	= x1205_rtc_पढ़ो_समय,
	.set_समय	= x1205_rtc_set_समय,
	.पढ़ो_alarm	= x1205_rtc_पढ़ो_alarm,
	.set_alarm	= x1205_rtc_set_alarm,
पूर्ण;

अटल sमाप_प्रकार x1205_sysfs_show_atrim(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक err, atrim;

	err = x1205_get_atrim(to_i2c_client(dev), &atrim);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%d.%02d pF\n", atrim / 1000, atrim % 1000);
पूर्ण
अटल DEVICE_ATTR(atrim, S_IRUGO, x1205_sysfs_show_atrim, शून्य);

अटल sमाप_प्रकार x1205_sysfs_show_dtrim(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक err, dtrim;

	err = x1205_get_dtrim(to_i2c_client(dev), &dtrim);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%d ppm\n", dtrim);
पूर्ण
अटल DEVICE_ATTR(dtrim, S_IRUGO, x1205_sysfs_show_dtrim, शून्य);

अटल पूर्णांक x1205_sysfs_रेजिस्टर(काष्ठा device *dev)
अणु
	पूर्णांक err;

	err = device_create_file(dev, &dev_attr_atrim);
	अगर (err)
		वापस err;

	err = device_create_file(dev, &dev_attr_dtrim);
	अगर (err)
		device_हटाओ_file(dev, &dev_attr_atrim);

	वापस err;
पूर्ण

अटल व्योम x1205_sysfs_unरेजिस्टर(काष्ठा device *dev)
अणु
	device_हटाओ_file(dev, &dev_attr_atrim);
	device_हटाओ_file(dev, &dev_attr_dtrim);
पूर्ण


अटल पूर्णांक x1205_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक err = 0;
	अचिन्हित अक्षर sr;
	काष्ठा rtc_device *rtc;

	dev_dbg(&client->dev, "%s\n", __func__);

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	अगर (x1205_validate_client(client) < 0)
		वापस -ENODEV;

	rtc = devm_rtc_device_रेजिस्टर(&client->dev, x1205_driver.driver.name,
					&x1205_rtc_ops, THIS_MODULE);

	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	i2c_set_clientdata(client, rtc);

	/* Check क्रम घातer failures and eventually enable the osc */
	err = x1205_get_status(client, &sr);
	अगर (!err) अणु
		अगर (sr & X1205_SR_RTCF) अणु
			dev_err(&client->dev,
				"power failure detected, "
				"please set the clock\n");
			udelay(50);
			x1205_fix_osc(client);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&client->dev, "couldn't read status\n");
	पूर्ण

	err = x1205_sysfs_रेजिस्टर(&client->dev);
	अगर (err)
		dev_err(&client->dev, "Unable to create sysfs entries\n");

	वापस 0;
पूर्ण

अटल पूर्णांक x1205_हटाओ(काष्ठा i2c_client *client)
अणु
	x1205_sysfs_unरेजिस्टर(&client->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id x1205_id[] = अणु
	अणु "x1205", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, x1205_id);

अटल स्थिर काष्ठा of_device_id x1205_dt_ids[] = अणु
	अणु .compatible = "xircom,x1205", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, x1205_dt_ids);

अटल काष्ठा i2c_driver x1205_driver = अणु
	.driver		= अणु
		.name	= "rtc-x1205",
		.of_match_table = x1205_dt_ids,
	पूर्ण,
	.probe		= x1205_probe,
	.हटाओ		= x1205_हटाओ,
	.id_table	= x1205_id,
पूर्ण;

module_i2c_driver(x1205_driver);

MODULE_AUTHOR(
	"Karen Spearel <kas111 at gmail dot com>, "
	"Alessandro Zummo <a.zummo@towertech.it>");
MODULE_DESCRIPTION("Xicor/Intersil X1205 RTC driver");
MODULE_LICENSE("GPL");
