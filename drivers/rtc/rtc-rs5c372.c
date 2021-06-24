<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An I2C driver क्रम Ricoh RS5C372, R2025S/D and RV5C38[67] RTCs
 *
 * Copyright (C) 2005 Pavel Mironchik <pmironchik@optअगरacio.net>
 * Copyright (C) 2006 Tower Technologies
 * Copyright (C) 2008 Paul Mundt
 */

#समावेश <linux/i2c.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>

/*
 * Ricoh has a family of I2C based RTCs, which dअगरfer only slightly from
 * each other.  Dअगरferences center on pinout (e.g. how many पूर्णांकerrupts,
 * output घड़ी, etc) and how the control रेजिस्टरs are used.  The '372
 * is signअगरicant only because that's the one this driver first supported.
 */
#घोषणा RS5C372_REG_SECS	0
#घोषणा RS5C372_REG_MINS	1
#घोषणा RS5C372_REG_HOURS	2
#घोषणा RS5C372_REG_WDAY	3
#घोषणा RS5C372_REG_DAY		4
#घोषणा RS5C372_REG_MONTH	5
#घोषणा RS5C372_REG_YEAR	6
#घोषणा RS5C372_REG_TRIM	7
#	define RS5C372_TRIM_XSL		0x80
#	define RS5C372_TRIM_MASK	0x7F

#घोषणा RS5C_REG_ALARM_A_MIN	8			/* or ALARM_W */
#घोषणा RS5C_REG_ALARM_A_HOURS	9
#घोषणा RS5C_REG_ALARM_A_WDAY	10

#घोषणा RS5C_REG_ALARM_B_MIN	11			/* or ALARM_D */
#घोषणा RS5C_REG_ALARM_B_HOURS	12
#घोषणा RS5C_REG_ALARM_B_WDAY	13			/* (ALARM_B only) */

#घोषणा RS5C_REG_CTRL1		14
#	define RS5C_CTRL1_AALE		(1 << 7)	/* or WALE */
#	define RS5C_CTRL1_BALE		(1 << 6)	/* or DALE */
#	define RV5C387_CTRL1_24		(1 << 5)
#	define RS5C372A_CTRL1_SL1	(1 << 5)
#	define RS5C_CTRL1_CT_MASK	(7 << 0)
#	define RS5C_CTRL1_CT0		(0 << 0)	/* no periodic irq */
#	define RS5C_CTRL1_CT4		(4 << 0)	/* 1 Hz level irq */
#घोषणा RS5C_REG_CTRL2		15
#	define RS5C372_CTRL2_24		(1 << 5)
#	define RS5C_CTRL2_XSTP		(1 << 4)	/* only अगर !R2x2x */
#	define R2x2x_CTRL2_VDET		(1 << 6)	/* only अगर  R2x2x */
#	define R2x2x_CTRL2_XSTP		(1 << 5)	/* only अगर  R2x2x */
#	define R2x2x_CTRL2_PON		(1 << 4)	/* only अगर  R2x2x */
#	define RS5C_CTRL2_CTFG		(1 << 2)
#	define RS5C_CTRL2_AAFG		(1 << 1)	/* or WAFG */
#	define RS5C_CTRL2_BAFG		(1 << 0)	/* or DAFG */


/* to पढ़ो (style 1) or ग_लिखो रेजिस्टरs starting at R */
#घोषणा RS5C_ADDR(R)		(((R) << 4) | 0)


क्रमागत rtc_type अणु
	rtc_undef = 0,
	rtc_r2025sd,
	rtc_r2221tl,
	rtc_rs5c372a,
	rtc_rs5c372b,
	rtc_rv5c386,
	rtc_rv5c387a,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id rs5c372_id[] = अणु
	अणु "r2025sd", rtc_r2025sd पूर्ण,
	अणु "r2221tl", rtc_r2221tl पूर्ण,
	अणु "rs5c372a", rtc_rs5c372a पूर्ण,
	अणु "rs5c372b", rtc_rs5c372b पूर्ण,
	अणु "rv5c386", rtc_rv5c386 पूर्ण,
	अणु "rv5c387a", rtc_rv5c387a पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rs5c372_id);

अटल स्थिर __maybe_unused काष्ठा of_device_id rs5c372_of_match[] = अणु
	अणु
		.compatible = "ricoh,r2025sd",
		.data = (व्योम *)rtc_r2025sd
	पूर्ण,
	अणु
		.compatible = "ricoh,r2221tl",
		.data = (व्योम *)rtc_r2221tl
	पूर्ण,
	अणु
		.compatible = "ricoh,rs5c372a",
		.data = (व्योम *)rtc_rs5c372a
	पूर्ण,
	अणु
		.compatible = "ricoh,rs5c372b",
		.data = (व्योम *)rtc_rs5c372b
	पूर्ण,
	अणु
		.compatible = "ricoh,rv5c386",
		.data = (व्योम *)rtc_rv5c386
	पूर्ण,
	अणु
		.compatible = "ricoh,rv5c387a",
		.data = (व्योम *)rtc_rv5c387a
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rs5c372_of_match);

/* REVISIT:  this assumes that:
 *  - we're in the 21st century, so it's safe to ignore the century
 *    bit क्रम rv5c38[67] (REG_MONTH bit 7);
 *  - we should use ALARM_A not ALARM_B (may be wrong on some boards)
 */
काष्ठा rs5c372 अणु
	काष्ठा i2c_client	*client;
	काष्ठा rtc_device	*rtc;
	क्रमागत rtc_type		type;
	अचिन्हित		समय24:1;
	अचिन्हित		has_irq:1;
	अचिन्हित		smbus:1;
	अक्षर			buf[17];
	अक्षर			*regs;
पूर्ण;

अटल पूर्णांक rs5c_get_regs(काष्ठा rs5c372 *rs5c)
अणु
	काष्ठा i2c_client	*client = rs5c->client;
	काष्ठा i2c_msg		msgs[] = अणु
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = माप(rs5c->buf),
			.buf = rs5c->buf
		पूर्ण,
	पूर्ण;

	/* This implements the third पढ़ोing method from the datasheet, using
	 * an पूर्णांकernal address that's reset after each transaction (by STOP)
	 * to 0x0f ... so we पढ़ो extra रेजिस्टरs, and skip the first one.
	 *
	 * The first method करोesn't work with the iop3xx adapter driver, on at
	 * least 80219 chips; this works around that bug.
	 *
	 * The third method on the other hand करोesn't work क्रम the SMBus-only
	 * configurations, so we use the the first method there, stripping off
	 * the extra रेजिस्टर in the process.
	 */
	अगर (rs5c->smbus) अणु
		पूर्णांक addr = RS5C_ADDR(RS5C372_REG_SECS);
		पूर्णांक size = माप(rs5c->buf) - 1;

		अगर (i2c_smbus_पढ़ो_i2c_block_data(client, addr, size,
						  rs5c->buf + 1) != size) अणु
			dev_warn(&client->dev, "can't read registers\n");
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((i2c_transfer(client->adapter, msgs, 1)) != 1) अणु
			dev_warn(&client->dev, "can't read registers\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	dev_dbg(&client->dev,
		"%3ph (%02x) %3ph (%02x), %3ph, %3ph; %02x %02x\n",
		rs5c->regs + 0, rs5c->regs[3],
		rs5c->regs + 4, rs5c->regs[7],
		rs5c->regs + 8, rs5c->regs + 11,
		rs5c->regs[14], rs5c->regs[15]);

	वापस 0;
पूर्ण

अटल अचिन्हित rs5c_reg2hr(काष्ठा rs5c372 *rs5c, अचिन्हित reg)
अणु
	अचिन्हित	hour;

	अगर (rs5c->समय24)
		वापस bcd2bin(reg & 0x3f);

	hour = bcd2bin(reg & 0x1f);
	अगर (hour == 12)
		hour = 0;
	अगर (reg & 0x20)
		hour += 12;
	वापस hour;
पूर्ण

अटल अचिन्हित rs5c_hr2reg(काष्ठा rs5c372 *rs5c, अचिन्हित hour)
अणु
	अगर (rs5c->समय24)
		वापस bin2bcd(hour);

	अगर (hour > 12)
		वापस 0x20 | bin2bcd(hour - 12);
	अगर (hour == 12)
		वापस 0x20 | bin2bcd(12);
	अगर (hour == 0)
		वापस bin2bcd(12);
	वापस bin2bcd(hour);
पूर्ण

अटल पूर्णांक rs5c372_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rs5c372	*rs5c = i2c_get_clientdata(client);
	पूर्णांक		status = rs5c_get_regs(rs5c);
	अचिन्हित अक्षर ctrl2 = rs5c->regs[RS5C_REG_CTRL2];

	अगर (status < 0)
		वापस status;

	चयन (rs5c->type) अणु
	हाल rtc_r2025sd:
	हाल rtc_r2221tl:
		अगर ((rs5c->type == rtc_r2025sd && !(ctrl2 & R2x2x_CTRL2_XSTP)) ||
		    (rs5c->type == rtc_r2221tl &&  (ctrl2 & R2x2x_CTRL2_XSTP))) अणु
			dev_warn(&client->dev, "rtc oscillator interruption detected. Please reset the rtc clock.\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		अगर (ctrl2 & RS5C_CTRL2_XSTP) अणु
			dev_warn(&client->dev, "rtc oscillator interruption detected. Please reset the rtc clock.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	पंचांग->पंचांग_sec = bcd2bin(rs5c->regs[RS5C372_REG_SECS] & 0x7f);
	पंचांग->पंचांग_min = bcd2bin(rs5c->regs[RS5C372_REG_MINS] & 0x7f);
	पंचांग->पंचांग_hour = rs5c_reg2hr(rs5c, rs5c->regs[RS5C372_REG_HOURS]);

	पंचांग->पंचांग_wday = bcd2bin(rs5c->regs[RS5C372_REG_WDAY] & 0x07);
	पंचांग->पंचांग_mday = bcd2bin(rs5c->regs[RS5C372_REG_DAY] & 0x3f);

	/* पंचांग->पंचांग_mon is zero-based */
	पंचांग->पंचांग_mon = bcd2bin(rs5c->regs[RS5C372_REG_MONTH] & 0x1f) - 1;

	/* year is 1900 + पंचांग->पंचांग_year */
	पंचांग->पंचांग_year = bcd2bin(rs5c->regs[RS5C372_REG_YEAR]) + 100;

	dev_dbg(&client->dev, "%s: tm is secs=%d, mins=%d, hours=%d, "
		"mday=%d, mon=%d, year=%d, wday=%d\n",
		__func__,
		पंचांग->पंचांग_sec, पंचांग->पंचांग_min, पंचांग->पंचांग_hour,
		पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	वापस 0;
पूर्ण

अटल पूर्णांक rs5c372_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rs5c372	*rs5c = i2c_get_clientdata(client);
	अचिन्हित अक्षर	buf[7];
	अचिन्हित अक्षर	ctrl2;
	पूर्णांक		addr;

	dev_dbg(&client->dev, "%s: tm is secs=%d, mins=%d, hours=%d "
		"mday=%d, mon=%d, year=%d, wday=%d\n",
		__func__,
		पंचांग->पंचांग_sec, पंचांग->पंचांग_min, पंचांग->पंचांग_hour,
		पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	addr   = RS5C_ADDR(RS5C372_REG_SECS);
	buf[0] = bin2bcd(पंचांग->पंचांग_sec);
	buf[1] = bin2bcd(पंचांग->पंचांग_min);
	buf[2] = rs5c_hr2reg(rs5c, पंचांग->पंचांग_hour);
	buf[3] = bin2bcd(पंचांग->पंचांग_wday);
	buf[4] = bin2bcd(पंचांग->पंचांग_mday);
	buf[5] = bin2bcd(पंचांग->पंचांग_mon + 1);
	buf[6] = bin2bcd(पंचांग->पंचांग_year - 100);

	अगर (i2c_smbus_ग_लिखो_i2c_block_data(client, addr, माप(buf), buf) < 0) अणु
		dev_dbg(&client->dev, "%s: write error in line %i\n",
			__func__, __LINE__);
		वापस -EIO;
	पूर्ण

	addr = RS5C_ADDR(RS5C_REG_CTRL2);
	ctrl2 = i2c_smbus_पढ़ो_byte_data(client, addr);

	/* clear rtc warning bits */
	चयन (rs5c->type) अणु
	हाल rtc_r2025sd:
	हाल rtc_r2221tl:
		ctrl2 &= ~(R2x2x_CTRL2_VDET | R2x2x_CTRL2_PON);
		अगर (rs5c->type == rtc_r2025sd)
			ctrl2 |= R2x2x_CTRL2_XSTP;
		अन्यथा
			ctrl2 &= ~R2x2x_CTRL2_XSTP;
		अवरोध;
	शेष:
		ctrl2 &= ~RS5C_CTRL2_XSTP;
		अवरोध;
	पूर्ण

	अगर (i2c_smbus_ग_लिखो_byte_data(client, addr, ctrl2) < 0) अणु
		dev_dbg(&client->dev, "%s: write error in line %i\n",
			__func__, __LINE__);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_RTC_INTF_PROC)
#घोषणा	NEED_TRIM
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_RTC_INTF_SYSFS)
#घोषणा	NEED_TRIM
#पूर्ण_अगर

#अगर_घोषित	NEED_TRIM
अटल पूर्णांक rs5c372_get_trim(काष्ठा i2c_client *client, पूर्णांक *osc, पूर्णांक *trim)
अणु
	काष्ठा rs5c372 *rs5c372 = i2c_get_clientdata(client);
	u8 पंचांगp = rs5c372->regs[RS5C372_REG_TRIM];

	अगर (osc)
		*osc = (पंचांगp & RS5C372_TRIM_XSL) ? 32000 : 32768;

	अगर (trim) अणु
		dev_dbg(&client->dev, "%s: raw trim=%x\n", __func__, पंचांगp);
		पंचांगp &= RS5C372_TRIM_MASK;
		अगर (पंचांगp & 0x3e) अणु
			पूर्णांक t = पंचांगp & 0x3f;

			अगर (पंचांगp & 0x40)
				t = (~t | (s8)0xc0) + 1;
			अन्यथा
				t = t - 1;

			पंचांगp = t * 2;
		पूर्ण अन्यथा
			पंचांगp = 0;
		*trim = पंचांगp;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rs5c_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा i2c_client	*client = to_i2c_client(dev);
	काष्ठा rs5c372		*rs5c = i2c_get_clientdata(client);
	अचिन्हित अक्षर		buf;
	पूर्णांक			status, addr;

	buf = rs5c->regs[RS5C_REG_CTRL1];

	अगर (!rs5c->has_irq)
		वापस -EINVAL;

	status = rs5c_get_regs(rs5c);
	अगर (status < 0)
		वापस status;

	addr = RS5C_ADDR(RS5C_REG_CTRL1);
	अगर (enabled)
		buf |= RS5C_CTRL1_AALE;
	अन्यथा
		buf &= ~RS5C_CTRL1_AALE;

	अगर (i2c_smbus_ग_लिखो_byte_data(client, addr, buf) < 0) अणु
		dev_warn(dev, "can't update alarm\n");
		status = -EIO;
	पूर्ण अन्यथा
		rs5c->regs[RS5C_REG_CTRL1] = buf;

	वापस status;
पूर्ण


/* NOTE:  Since RTC_WKALM_अणुRD,SETपूर्ण were originally defined क्रम EFI,
 * which only exposes a polled programming पूर्णांकerface; and since
 * these calls map directly to those EFI requests; we करोn't demand
 * we have an IRQ क्रम this chip when we go through this API.
 *
 * The older x86_pc derived RTC_ALM_अणुREAD,SETपूर्ण calls require irqs
 * though, managed through RTC_AIE_अणुON,OFFपूर्ण requests.
 */

अटल पूर्णांक rs5c_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा i2c_client	*client = to_i2c_client(dev);
	काष्ठा rs5c372		*rs5c = i2c_get_clientdata(client);
	पूर्णांक			status;

	status = rs5c_get_regs(rs5c);
	अगर (status < 0)
		वापस status;

	/* report alarm समय */
	t->समय.पंचांग_sec = 0;
	t->समय.पंचांग_min = bcd2bin(rs5c->regs[RS5C_REG_ALARM_A_MIN] & 0x7f);
	t->समय.पंचांग_hour = rs5c_reg2hr(rs5c, rs5c->regs[RS5C_REG_ALARM_A_HOURS]);

	/* ... and status */
	t->enabled = !!(rs5c->regs[RS5C_REG_CTRL1] & RS5C_CTRL1_AALE);
	t->pending = !!(rs5c->regs[RS5C_REG_CTRL2] & RS5C_CTRL2_AAFG);

	वापस 0;
पूर्ण

अटल पूर्णांक rs5c_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा i2c_client	*client = to_i2c_client(dev);
	काष्ठा rs5c372		*rs5c = i2c_get_clientdata(client);
	पूर्णांक			status, addr, i;
	अचिन्हित अक्षर		buf[3];

	/* only handle up to 24 hours in the future, like RTC_ALM_SET */
	अगर (t->समय.पंचांग_mday != -1
			|| t->समय.पंचांग_mon != -1
			|| t->समय.पंचांग_year != -1)
		वापस -EINVAL;

	/* REVISIT: round up पंचांग_sec */

	/* अगर needed, disable irq (clears pending status) */
	status = rs5c_get_regs(rs5c);
	अगर (status < 0)
		वापस status;
	अगर (rs5c->regs[RS5C_REG_CTRL1] & RS5C_CTRL1_AALE) अणु
		addr = RS5C_ADDR(RS5C_REG_CTRL1);
		buf[0] = rs5c->regs[RS5C_REG_CTRL1] & ~RS5C_CTRL1_AALE;
		अगर (i2c_smbus_ग_लिखो_byte_data(client, addr, buf[0]) < 0) अणु
			dev_dbg(dev, "can't disable alarm\n");
			वापस -EIO;
		पूर्ण
		rs5c->regs[RS5C_REG_CTRL1] = buf[0];
	पूर्ण

	/* set alarm */
	buf[0] = bin2bcd(t->समय.पंचांग_min);
	buf[1] = rs5c_hr2reg(rs5c, t->समय.पंचांग_hour);
	buf[2] = 0x7f;	/* any/all days */

	क्रम (i = 0; i < माप(buf); i++) अणु
		addr = RS5C_ADDR(RS5C_REG_ALARM_A_MIN + i);
		अगर (i2c_smbus_ग_लिखो_byte_data(client, addr, buf[i]) < 0) अणु
			dev_dbg(dev, "can't set alarm time\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	/* ... and maybe enable its irq */
	अगर (t->enabled) अणु
		addr = RS5C_ADDR(RS5C_REG_CTRL1);
		buf[0] = rs5c->regs[RS5C_REG_CTRL1] | RS5C_CTRL1_AALE;
		अगर (i2c_smbus_ग_लिखो_byte_data(client, addr, buf[0]) < 0)
			dev_warn(dev, "can't enable alarm\n");
		rs5c->regs[RS5C_REG_CTRL1] = buf[0];
	पूर्ण

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_RTC_INTF_PROC)

अटल पूर्णांक rs5c372_rtc_proc(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	पूर्णांक err, osc, trim;

	err = rs5c372_get_trim(to_i2c_client(dev), &osc, &trim);
	अगर (err == 0) अणु
		seq_म_लिखो(seq, "crystal\t\t: %d.%03d KHz\n",
				osc / 1000, osc % 1000);
		seq_म_लिखो(seq, "trim\t\t: %d\n", trim);
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा	rs5c372_rtc_proc	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा rtc_class_ops rs5c372_rtc_ops = अणु
	.proc		= rs5c372_rtc_proc,
	.पढ़ो_समय	= rs5c372_rtc_पढ़ो_समय,
	.set_समय	= rs5c372_rtc_set_समय,
	.पढ़ो_alarm	= rs5c_पढ़ो_alarm,
	.set_alarm	= rs5c_set_alarm,
	.alarm_irq_enable = rs5c_rtc_alarm_irq_enable,
पूर्ण;

#अगर IS_ENABLED(CONFIG_RTC_INTF_SYSFS)

अटल sमाप_प्रकार rs5c372_sysfs_show_trim(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक err, trim;

	err = rs5c372_get_trim(to_i2c_client(dev), शून्य, &trim);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%d\n", trim);
पूर्ण
अटल DEVICE_ATTR(trim, S_IRUGO, rs5c372_sysfs_show_trim, शून्य);

अटल sमाप_प्रकार rs5c372_sysfs_show_osc(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक err, osc;

	err = rs5c372_get_trim(to_i2c_client(dev), &osc, शून्य);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%d.%03d KHz\n", osc / 1000, osc % 1000);
पूर्ण
अटल DEVICE_ATTR(osc, S_IRUGO, rs5c372_sysfs_show_osc, शून्य);

अटल पूर्णांक rs5c_sysfs_रेजिस्टर(काष्ठा device *dev)
अणु
	पूर्णांक err;

	err = device_create_file(dev, &dev_attr_trim);
	अगर (err)
		वापस err;
	err = device_create_file(dev, &dev_attr_osc);
	अगर (err)
		device_हटाओ_file(dev, &dev_attr_trim);

	वापस err;
पूर्ण

अटल व्योम rs5c_sysfs_unरेजिस्टर(काष्ठा device *dev)
अणु
	device_हटाओ_file(dev, &dev_attr_trim);
	device_हटाओ_file(dev, &dev_attr_osc);
पूर्ण

#अन्यथा
अटल पूर्णांक rs5c_sysfs_रेजिस्टर(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल व्योम rs5c_sysfs_unरेजिस्टर(काष्ठा device *dev)
अणु
	/* nothing */
पूर्ण
#पूर्ण_अगर	/* SYSFS */

अटल काष्ठा i2c_driver rs5c372_driver;

अटल पूर्णांक rs5c_oscillator_setup(काष्ठा rs5c372 *rs5c372)
अणु
	अचिन्हित अक्षर buf[2];
	पूर्णांक addr, i, ret = 0;

	addr   = RS5C_ADDR(RS5C_REG_CTRL1);
	buf[0] = rs5c372->regs[RS5C_REG_CTRL1];
	buf[1] = rs5c372->regs[RS5C_REG_CTRL2];

	चयन (rs5c372->type) अणु
	हाल rtc_r2025sd:
		अगर (buf[1] & R2x2x_CTRL2_XSTP)
			वापस ret;
		अवरोध;
	हाल rtc_r2221tl:
		अगर (!(buf[1] & R2x2x_CTRL2_XSTP))
			वापस ret;
		अवरोध;
	शेष:
		अगर (!(buf[1] & RS5C_CTRL2_XSTP))
			वापस ret;
		अवरोध;
	पूर्ण

	/* use 24hr mode */
	चयन (rs5c372->type) अणु
	हाल rtc_rs5c372a:
	हाल rtc_rs5c372b:
		buf[1] |= RS5C372_CTRL2_24;
		rs5c372->समय24 = 1;
		अवरोध;
	हाल rtc_r2025sd:
	हाल rtc_r2221tl:
	हाल rtc_rv5c386:
	हाल rtc_rv5c387a:
		buf[0] |= RV5C387_CTRL1_24;
		rs5c372->समय24 = 1;
		अवरोध;
	शेष:
		/* impossible */
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < माप(buf); i++) अणु
		addr = RS5C_ADDR(RS5C_REG_CTRL1 + i);
		ret = i2c_smbus_ग_लिखो_byte_data(rs5c372->client, addr, buf[i]);
		अगर (unlikely(ret < 0))
			वापस ret;
	पूर्ण

	rs5c372->regs[RS5C_REG_CTRL1] = buf[0];
	rs5c372->regs[RS5C_REG_CTRL2] = buf[1];

	वापस 0;
पूर्ण

अटल पूर्णांक rs5c372_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक err = 0;
	पूर्णांक smbus_mode = 0;
	काष्ठा rs5c372 *rs5c372;

	dev_dbg(&client->dev, "%s\n", __func__);

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C |
			I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_I2C_BLOCK)) अणु
		/*
		 * If we करोn't have any master mode adapter, try अवरोधing
		 * it करोwn in to the barest of capabilities.
		 */
		अगर (i2c_check_functionality(client->adapter,
				I2C_FUNC_SMBUS_BYTE_DATA |
				I2C_FUNC_SMBUS_I2C_BLOCK))
			smbus_mode = 1;
		अन्यथा अणु
			/* Still no good, give up */
			err = -ENODEV;
			जाओ निकास;
		पूर्ण
	पूर्ण

	rs5c372 = devm_kzalloc(&client->dev, माप(काष्ठा rs5c372),
				GFP_KERNEL);
	अगर (!rs5c372) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	rs5c372->client = client;
	i2c_set_clientdata(client, rs5c372);
	अगर (client->dev.of_node)
		rs5c372->type = (क्रमागत rtc_type)
			of_device_get_match_data(&client->dev);
	अन्यथा
		rs5c372->type = id->driver_data;

	/* we पढ़ो रेजिस्टरs 0x0f then 0x00-0x0f; skip the first one */
	rs5c372->regs = &rs5c372->buf[1];
	rs5c372->smbus = smbus_mode;

	err = rs5c_get_regs(rs5c372);
	अगर (err < 0)
		जाओ निकास;

	/* घड़ी may be set क्रम am/pm or 24 hr समय */
	चयन (rs5c372->type) अणु
	हाल rtc_rs5c372a:
	हाल rtc_rs5c372b:
		/* alarm uses ALARM_A; and nINTRA on 372a, nINTR on 372b.
		 * so करोes periodic irq, except some 327a modes.
		 */
		अगर (rs5c372->regs[RS5C_REG_CTRL2] & RS5C372_CTRL2_24)
			rs5c372->समय24 = 1;
		अवरोध;
	हाल rtc_r2025sd:
	हाल rtc_r2221tl:
	हाल rtc_rv5c386:
	हाल rtc_rv5c387a:
		अगर (rs5c372->regs[RS5C_REG_CTRL1] & RV5C387_CTRL1_24)
			rs5c372->समय24 = 1;
		/* alarm uses ALARM_W; and nINTRB क्रम alarm and periodic
		 * irq, on both 386 and 387
		 */
		अवरोध;
	शेष:
		dev_err(&client->dev, "unknown RTC type\n");
		जाओ निकास;
	पूर्ण

	/* अगर the oscillator lost घातer and no other software (like
	 * the bootloader) set it up, करो it here.
	 *
	 * The R2025S/D करोes this a little dअगरferently than the other
	 * parts, so we special हाल that..
	 */
	err = rs5c_oscillator_setup(rs5c372);
	अगर (unlikely(err < 0)) अणु
		dev_err(&client->dev, "setup error\n");
		जाओ निकास;
	पूर्ण

	dev_info(&client->dev, "%s found, %s\n",
			(अणु अक्षर *s; चयन (rs5c372->type) अणु
			हाल rtc_r2025sd:	s = "r2025sd"; अवरोध;
			हाल rtc_r2221tl:	s = "r2221tl"; अवरोध;
			हाल rtc_rs5c372a:	s = "rs5c372a"; अवरोध;
			हाल rtc_rs5c372b:	s = "rs5c372b"; अवरोध;
			हाल rtc_rv5c386:	s = "rv5c386"; अवरोध;
			हाल rtc_rv5c387a:	s = "rv5c387a"; अवरोध;
			शेष:		s = "chip"; अवरोध;
			पूर्ण; s;पूर्ण),
			rs5c372->समय24 ? "24hr" : "am/pm"
			);

	/* REVISIT use client->irq to रेजिस्टर alarm irq ... */
	rs5c372->rtc = devm_rtc_device_रेजिस्टर(&client->dev,
					rs5c372_driver.driver.name,
					&rs5c372_rtc_ops, THIS_MODULE);

	अगर (IS_ERR(rs5c372->rtc)) अणु
		err = PTR_ERR(rs5c372->rtc);
		जाओ निकास;
	पूर्ण

	err = rs5c_sysfs_रेजिस्टर(&client->dev);
	अगर (err)
		जाओ निकास;

	वापस 0;

निकास:
	वापस err;
पूर्ण

अटल पूर्णांक rs5c372_हटाओ(काष्ठा i2c_client *client)
अणु
	rs5c_sysfs_unरेजिस्टर(&client->dev);
	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver rs5c372_driver = अणु
	.driver		= अणु
		.name	= "rtc-rs5c372",
		.of_match_table = of_match_ptr(rs5c372_of_match),
	पूर्ण,
	.probe		= rs5c372_probe,
	.हटाओ		= rs5c372_हटाओ,
	.id_table	= rs5c372_id,
पूर्ण;

module_i2c_driver(rs5c372_driver);

MODULE_AUTHOR(
		"Pavel Mironchik <pmironchik@optifacio.net>, "
		"Alessandro Zummo <a.zummo@towertech.it>, "
		"Paul Mundt <lethal@linux-sh.org>");
MODULE_DESCRIPTION("Ricoh RS5C372 RTC driver");
MODULE_LICENSE("GPL");
