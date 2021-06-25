<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Micro Crystal RV-3029 / RV-3049 rtc class driver
 *
 * Author: Gregory Hermant <gregory.hermant@calao-प्रणालीs.com>
 *         Michael Buesch <m@bues.ch>
 *
 * based on previously existing rtc class drivers
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/bcd.h>
#समावेश <linux/rtc.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/regmap.h>

/* Register map */
/* control section */
#घोषणा RV3029_ONOFF_CTRL		0x00
#घोषणा RV3029_ONOFF_CTRL_WE		BIT(0)
#घोषणा RV3029_ONOFF_CTRL_TE		BIT(1)
#घोषणा RV3029_ONOFF_CTRL_TAR		BIT(2)
#घोषणा RV3029_ONOFF_CTRL_EERE		BIT(3)
#घोषणा RV3029_ONOFF_CTRL_SRON		BIT(4)
#घोषणा RV3029_ONOFF_CTRL_TD0		BIT(5)
#घोषणा RV3029_ONOFF_CTRL_TD1		BIT(6)
#घोषणा RV3029_ONOFF_CTRL_CLKINT	BIT(7)
#घोषणा RV3029_IRQ_CTRL			0x01
#घोषणा RV3029_IRQ_CTRL_AIE		BIT(0)
#घोषणा RV3029_IRQ_CTRL_TIE		BIT(1)
#घोषणा RV3029_IRQ_CTRL_V1IE		BIT(2)
#घोषणा RV3029_IRQ_CTRL_V2IE		BIT(3)
#घोषणा RV3029_IRQ_CTRL_SRIE		BIT(4)
#घोषणा RV3029_IRQ_FLAGS		0x02
#घोषणा RV3029_IRQ_FLAGS_AF		BIT(0)
#घोषणा RV3029_IRQ_FLAGS_TF		BIT(1)
#घोषणा RV3029_IRQ_FLAGS_V1IF		BIT(2)
#घोषणा RV3029_IRQ_FLAGS_V2IF		BIT(3)
#घोषणा RV3029_IRQ_FLAGS_SRF		BIT(4)
#घोषणा RV3029_STATUS			0x03
#घोषणा RV3029_STATUS_VLOW1		BIT(2)
#घोषणा RV3029_STATUS_VLOW2		BIT(3)
#घोषणा RV3029_STATUS_SR		BIT(4)
#घोषणा RV3029_STATUS_PON		BIT(5)
#घोषणा RV3029_STATUS_EEBUSY		BIT(7)
#घोषणा RV3029_RST_CTRL			0x04
#घोषणा RV3029_RST_CTRL_SYSR		BIT(4)
#घोषणा RV3029_CONTROL_SECTION_LEN	0x05

/* watch section */
#घोषणा RV3029_W_SEC			0x08
#घोषणा RV3029_W_MINUTES		0x09
#घोषणा RV3029_W_HOURS			0x0A
#घोषणा RV3029_REG_HR_12_24		BIT(6) /* 24h/12h mode */
#घोषणा RV3029_REG_HR_PM		BIT(5) /* PM/AM bit in 12h mode */
#घोषणा RV3029_W_DATE			0x0B
#घोषणा RV3029_W_DAYS			0x0C
#घोषणा RV3029_W_MONTHS			0x0D
#घोषणा RV3029_W_YEARS			0x0E
#घोषणा RV3029_WATCH_SECTION_LEN	0x07

/* alarm section */
#घोषणा RV3029_A_SC			0x10
#घोषणा RV3029_A_MN			0x11
#घोषणा RV3029_A_HR			0x12
#घोषणा RV3029_A_DT			0x13
#घोषणा RV3029_A_DW			0x14
#घोषणा RV3029_A_MO			0x15
#घोषणा RV3029_A_YR			0x16
#घोषणा RV3029_A_AE_X			BIT(7)
#घोषणा RV3029_ALARM_SECTION_LEN	0x07

/* समयr section */
#घोषणा RV3029_TIMER_LOW		0x18
#घोषणा RV3029_TIMER_HIGH		0x19

/* temperature section */
#घोषणा RV3029_TEMP_PAGE		0x20

/* eeprom data section */
#घोषणा RV3029_E2P_EEDATA1		0x28
#घोषणा RV3029_E2P_EEDATA2		0x29
#घोषणा RV3029_E2PDATA_SECTION_LEN	0x02

/* eeprom control section */
#घोषणा RV3029_CONTROL_E2P_EECTRL	0x30
#घोषणा RV3029_EECTRL_THP		BIT(0) /* temp scan पूर्णांकerval */
#घोषणा RV3029_EECTRL_THE		BIT(1) /* thermometer enable */
#घोषणा RV3029_EECTRL_FD0		BIT(2) /* CLKOUT */
#घोषणा RV3029_EECTRL_FD1		BIT(3) /* CLKOUT */
#घोषणा RV3029_TRICKLE_1K		BIT(4) /* 1.5K resistance */
#घोषणा RV3029_TRICKLE_5K		BIT(5) /* 5K   resistance */
#घोषणा RV3029_TRICKLE_20K		BIT(6) /* 20K  resistance */
#घोषणा RV3029_TRICKLE_80K		BIT(7) /* 80K  resistance */
#घोषणा RV3029_TRICKLE_MASK		(RV3029_TRICKLE_1K |\
					 RV3029_TRICKLE_5K |\
					 RV3029_TRICKLE_20K |\
					 RV3029_TRICKLE_80K)
#घोषणा RV3029_TRICKLE_SHIFT		4
#घोषणा RV3029_CONTROL_E2P_XOFFS	0x31 /* XTAL offset */
#घोषणा RV3029_CONTROL_E2P_XOFFS_SIGN	BIT(7) /* Sign: 1->pos, 0->neg */
#घोषणा RV3029_CONTROL_E2P_QCOEF	0x32 /* XTAL temp drअगरt coef */
#घोषणा RV3029_CONTROL_E2P_TURNOVER	0x33 /* XTAL turnover temp (in *C) */
#घोषणा RV3029_CONTROL_E2P_TOV_MASK	0x3F /* XTAL turnover temp mask */

/* user ram section */
#घोषणा RV3029_RAM_PAGE			0x38
#घोषणा RV3029_RAM_SECTION_LEN		8

काष्ठा rv3029_data अणु
	काष्ठा device		*dev;
	काष्ठा rtc_device	*rtc;
	काष्ठा regmap		*regmap;
	पूर्णांक irq;
पूर्ण;

अटल पूर्णांक rv3029_eeprom_busyरुको(काष्ठा rv3029_data *rv3029)
अणु
	अचिन्हित पूर्णांक sr;
	पूर्णांक i, ret;

	क्रम (i = 100; i > 0; i--) अणु
		ret = regmap_पढ़ो(rv3029->regmap, RV3029_STATUS, &sr);
		अगर (ret < 0)
			अवरोध;
		अगर (!(sr & RV3029_STATUS_EEBUSY))
			अवरोध;
		usleep_range(1000, 10000);
	पूर्ण
	अगर (i <= 0) अणु
		dev_err(rv3029->dev, "EEPROM busy wait timeout.\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rv3029_eeprom_निकास(काष्ठा rv3029_data *rv3029)
अणु
	/* Re-enable eeprom refresh */
	वापस regmap_update_bits(rv3029->regmap, RV3029_ONOFF_CTRL,
				  RV3029_ONOFF_CTRL_EERE,
				  RV3029_ONOFF_CTRL_EERE);
पूर्ण

अटल पूर्णांक rv3029_eeprom_enter(काष्ठा rv3029_data *rv3029)
अणु
	अचिन्हित पूर्णांक sr;
	पूर्णांक ret;

	/* Check whether we are in the allowed voltage range. */
	ret = regmap_पढ़ो(rv3029->regmap, RV3029_STATUS, &sr);
	अगर (ret < 0)
		वापस ret;
	अगर (sr & RV3029_STATUS_VLOW2)
		वापस -ENODEV;
	अगर (sr & RV3029_STATUS_VLOW1) अणु
		/* We clear the bits and retry once just in हाल
		 * we had a brown out in early startup.
		 */
		ret = regmap_update_bits(rv3029->regmap, RV3029_STATUS,
					 RV3029_STATUS_VLOW1, 0);
		अगर (ret < 0)
			वापस ret;
		usleep_range(1000, 10000);
		ret = regmap_पढ़ो(rv3029->regmap, RV3029_STATUS, &sr);
		अगर (ret < 0)
			वापस ret;
		अगर (sr & RV3029_STATUS_VLOW1) अणु
			dev_err(rv3029->dev,
				"Supply voltage is too low to safely access the EEPROM.\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* Disable eeprom refresh. */
	ret = regmap_update_bits(rv3029->regmap, RV3029_ONOFF_CTRL,
				 RV3029_ONOFF_CTRL_EERE, 0);
	अगर (ret < 0)
		वापस ret;

	/* Wait क्रम any previous eeprom accesses to finish. */
	ret = rv3029_eeprom_busyरुको(rv3029);
	अगर (ret < 0)
		rv3029_eeprom_निकास(rv3029);

	वापस ret;
पूर्ण

अटल पूर्णांक rv3029_eeprom_पढ़ो(काष्ठा rv3029_data *rv3029, u8 reg,
			      u8 buf[], माप_प्रकार len)
अणु
	पूर्णांक ret, err;

	err = rv3029_eeprom_enter(rv3029);
	अगर (err < 0)
		वापस err;

	ret = regmap_bulk_पढ़ो(rv3029->regmap, reg, buf, len);

	err = rv3029_eeprom_निकास(rv3029);
	अगर (err < 0)
		वापस err;

	वापस ret;
पूर्ण

अटल पूर्णांक rv3029_eeprom_ग_लिखो(काष्ठा rv3029_data *rv3029, u8 reg,
			       u8 स्थिर buf[], माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret, err;
	माप_प्रकार i;

	err = rv3029_eeprom_enter(rv3029);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < len; i++, reg++) अणु
		ret = regmap_पढ़ो(rv3029->regmap, reg, &पंचांगp);
		अगर (ret < 0)
			अवरोध;
		अगर (पंचांगp != buf[i]) अणु
			पंचांगp = buf[i];
			ret = regmap_ग_लिखो(rv3029->regmap, reg, पंचांगp);
			अगर (ret < 0)
				अवरोध;
		पूर्ण
		ret = rv3029_eeprom_busyरुको(rv3029);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	err = rv3029_eeprom_निकास(rv3029);
	अगर (err < 0)
		वापस err;

	वापस ret;
पूर्ण

अटल पूर्णांक rv3029_eeprom_update_bits(काष्ठा rv3029_data *rv3029,
				     u8 reg, u8 mask, u8 set)
अणु
	u8 buf;
	पूर्णांक ret;

	ret = rv3029_eeprom_पढ़ो(rv3029, reg, &buf, 1);
	अगर (ret < 0)
		वापस ret;
	buf &= ~mask;
	buf |= set & mask;
	ret = rv3029_eeprom_ग_लिखो(rv3029, reg, &buf, 1);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल irqवापस_t rv3029_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा device *dev = dev_id;
	काष्ठा rv3029_data *rv3029 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक flags, controls;
	अचिन्हित दीर्घ events = 0;
	पूर्णांक ret;

	rtc_lock(rv3029->rtc);

	ret = regmap_पढ़ो(rv3029->regmap, RV3029_IRQ_CTRL, &controls);
	अगर (ret) अणु
		dev_warn(dev, "Read IRQ Control Register error %d\n", ret);
		rtc_unlock(rv3029->rtc);
		वापस IRQ_NONE;
	पूर्ण

	ret = regmap_पढ़ो(rv3029->regmap, RV3029_IRQ_FLAGS, &flags);
	अगर (ret) अणु
		dev_warn(dev, "Read IRQ Flags Register error %d\n", ret);
		rtc_unlock(rv3029->rtc);
		वापस IRQ_NONE;
	पूर्ण

	अगर (flags & RV3029_IRQ_FLAGS_AF) अणु
		flags &= ~RV3029_IRQ_FLAGS_AF;
		controls &= ~RV3029_IRQ_CTRL_AIE;
		events |= RTC_AF;
	पूर्ण

	अगर (events) अणु
		rtc_update_irq(rv3029->rtc, 1, events);
		regmap_ग_लिखो(rv3029->regmap, RV3029_IRQ_FLAGS, flags);
		regmap_ग_लिखो(rv3029->regmap, RV3029_IRQ_CTRL, controls);
	पूर्ण
	rtc_unlock(rv3029->rtc);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rv3029_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rv3029_data *rv3029 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक sr;
	पूर्णांक ret;
	u8 regs[RV3029_WATCH_SECTION_LEN] = अणु 0, पूर्ण;

	ret = regmap_पढ़ो(rv3029->regmap, RV3029_STATUS, &sr);
	अगर (ret < 0)
		वापस ret;

	अगर (sr & (RV3029_STATUS_VLOW2 | RV3029_STATUS_PON))
		वापस -EINVAL;

	ret = regmap_bulk_पढ़ो(rv3029->regmap, RV3029_W_SEC, regs,
			       RV3029_WATCH_SECTION_LEN);
	अगर (ret < 0)
		वापस ret;

	पंचांग->पंचांग_sec = bcd2bin(regs[RV3029_W_SEC - RV3029_W_SEC]);
	पंचांग->पंचांग_min = bcd2bin(regs[RV3029_W_MINUTES - RV3029_W_SEC]);

	/* HR field has a more complex पूर्णांकerpretation */
	अणु
		स्थिर u8 _hr = regs[RV3029_W_HOURS - RV3029_W_SEC];

		अगर (_hr & RV3029_REG_HR_12_24) अणु
			/* 12h क्रमmat */
			पंचांग->पंचांग_hour = bcd2bin(_hr & 0x1f);
			अगर (_hr & RV3029_REG_HR_PM)	/* PM flag set */
				पंचांग->पंचांग_hour += 12;
		पूर्ण अन्यथा /* 24h क्रमmat */
			पंचांग->पंचांग_hour = bcd2bin(_hr & 0x3f);
	पूर्ण

	पंचांग->पंचांग_mday = bcd2bin(regs[RV3029_W_DATE - RV3029_W_SEC]);
	पंचांग->पंचांग_mon = bcd2bin(regs[RV3029_W_MONTHS - RV3029_W_SEC]) - 1;
	पंचांग->पंचांग_year = bcd2bin(regs[RV3029_W_YEARS - RV3029_W_SEC]) + 100;
	पंचांग->पंचांग_wday = bcd2bin(regs[RV3029_W_DAYS - RV3029_W_SEC]) - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक rv3029_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा rv3029_data *rv3029 = dev_get_drvdata(dev);
	काष्ठा rtc_समय *स्थिर पंचांग = &alarm->समय;
	अचिन्हित पूर्णांक controls, flags;
	पूर्णांक ret;
	u8 regs[8];

	ret = regmap_bulk_पढ़ो(rv3029->regmap, RV3029_A_SC, regs,
			       RV3029_ALARM_SECTION_LEN);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(rv3029->regmap, RV3029_IRQ_CTRL, &controls);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(rv3029->regmap, RV3029_IRQ_FLAGS, &flags);
	अगर (ret < 0)
		वापस ret;

	पंचांग->पंचांग_sec = bcd2bin(regs[RV3029_A_SC - RV3029_A_SC] & 0x7f);
	पंचांग->पंचांग_min = bcd2bin(regs[RV3029_A_MN - RV3029_A_SC] & 0x7f);
	पंचांग->पंचांग_hour = bcd2bin(regs[RV3029_A_HR - RV3029_A_SC] & 0x3f);
	पंचांग->पंचांग_mday = bcd2bin(regs[RV3029_A_DT - RV3029_A_SC] & 0x3f);
	पंचांग->पंचांग_mon = bcd2bin(regs[RV3029_A_MO - RV3029_A_SC] & 0x1f) - 1;
	पंचांग->पंचांग_year = bcd2bin(regs[RV3029_A_YR - RV3029_A_SC] & 0x7f) + 100;
	पंचांग->पंचांग_wday = bcd2bin(regs[RV3029_A_DW - RV3029_A_SC] & 0x07) - 1;

	alarm->enabled = !!(controls & RV3029_IRQ_CTRL_AIE);
	alarm->pending = (flags & RV3029_IRQ_FLAGS_AF) && alarm->enabled;

	वापस 0;
पूर्ण

अटल पूर्णांक rv3029_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enable)
अणु
	काष्ठा rv3029_data *rv3029 = dev_get_drvdata(dev);

	वापस regmap_update_bits(rv3029->regmap, RV3029_IRQ_CTRL,
				  RV3029_IRQ_CTRL_AIE,
				  enable ? RV3029_IRQ_CTRL_AIE : 0);
पूर्ण

अटल पूर्णांक rv3029_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा rv3029_data *rv3029 = dev_get_drvdata(dev);
	काष्ठा rtc_समय *स्थिर पंचांग = &alarm->समय;
	पूर्णांक ret;
	u8 regs[8];

	/* Activate all the alarms with AE_x bit */
	regs[RV3029_A_SC - RV3029_A_SC] = bin2bcd(पंचांग->पंचांग_sec) | RV3029_A_AE_X;
	regs[RV3029_A_MN - RV3029_A_SC] = bin2bcd(पंचांग->पंचांग_min) | RV3029_A_AE_X;
	regs[RV3029_A_HR - RV3029_A_SC] = (bin2bcd(पंचांग->पंचांग_hour) & 0x3f)
		| RV3029_A_AE_X;
	regs[RV3029_A_DT - RV3029_A_SC] = (bin2bcd(पंचांग->पंचांग_mday) & 0x3f)
		| RV3029_A_AE_X;
	regs[RV3029_A_MO - RV3029_A_SC] = (bin2bcd(पंचांग->पंचांग_mon + 1) & 0x1f)
		| RV3029_A_AE_X;
	regs[RV3029_A_DW - RV3029_A_SC] = (bin2bcd(पंचांग->पंचांग_wday + 1) & 0x7)
		| RV3029_A_AE_X;
	regs[RV3029_A_YR - RV3029_A_SC] = (bin2bcd(पंचांग->पंचांग_year - 100))
		| RV3029_A_AE_X;

	/* Write the alarm */
	ret = regmap_bulk_ग_लिखो(rv3029->regmap, RV3029_A_SC, regs,
				RV3029_ALARM_SECTION_LEN);
	अगर (ret < 0)
		वापस ret;

	वापस rv3029_alarm_irq_enable(dev, alarm->enabled);
पूर्ण

अटल पूर्णांक rv3029_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rv3029_data *rv3029 = dev_get_drvdata(dev);
	u8 regs[8];
	पूर्णांक ret;

	regs[RV3029_W_SEC - RV3029_W_SEC] = bin2bcd(पंचांग->पंचांग_sec);
	regs[RV3029_W_MINUTES - RV3029_W_SEC] = bin2bcd(पंचांग->पंचांग_min);
	regs[RV3029_W_HOURS - RV3029_W_SEC] = bin2bcd(पंचांग->पंचांग_hour);
	regs[RV3029_W_DATE - RV3029_W_SEC] = bin2bcd(पंचांग->पंचांग_mday);
	regs[RV3029_W_MONTHS - RV3029_W_SEC] = bin2bcd(पंचांग->पंचांग_mon + 1);
	regs[RV3029_W_DAYS - RV3029_W_SEC] = bin2bcd(पंचांग->पंचांग_wday + 1) & 0x7;
	regs[RV3029_W_YEARS - RV3029_W_SEC] = bin2bcd(पंचांग->पंचांग_year - 100);

	ret = regmap_bulk_ग_लिखो(rv3029->regmap, RV3029_W_SEC, regs,
				RV3029_WATCH_SECTION_LEN);
	अगर (ret < 0)
		वापस ret;

	/* clear PON and VLOW2 bits */
	वापस regmap_update_bits(rv3029->regmap, RV3029_STATUS,
				  RV3029_STATUS_PON | RV3029_STATUS_VLOW2, 0);
पूर्ण

अटल पूर्णांक rv3029_ioctl(काष्ठा device *dev, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा rv3029_data *rv3029 = dev_get_drvdata(dev);
	अचिन्हित दीर्घ vl = 0;
	पूर्णांक sr, ret = 0;

	चयन (cmd) अणु
	हाल RTC_VL_READ:
		ret = regmap_पढ़ो(rv3029->regmap, RV3029_STATUS, &sr);
		अगर (ret < 0)
			वापस ret;

		अगर (sr & RV3029_STATUS_VLOW1)
			vl = RTC_VL_ACCURACY_LOW;

		अगर (sr & (RV3029_STATUS_VLOW2 | RV3029_STATUS_PON))
			vl |= RTC_VL_DATA_INVALID;

		वापस put_user(vl, (अचिन्हित पूर्णांक __user *)arg);

	हाल RTC_VL_CLR:
		वापस regmap_update_bits(rv3029->regmap, RV3029_STATUS,
					  RV3029_STATUS_VLOW1, 0);

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल पूर्णांक rv3029_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			      माप_प्रकार bytes)
अणु
	वापस regmap_bulk_ग_लिखो(priv, RV3029_RAM_PAGE + offset, val, bytes);
पूर्ण

अटल पूर्णांक rv3029_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			     माप_प्रकार bytes)
अणु
	वापस regmap_bulk_पढ़ो(priv, RV3029_RAM_PAGE + offset, val, bytes);
पूर्ण

अटल स्थिर काष्ठा rv3029_trickle_tab_elem अणु
	u32 r;		/* resistance in ohms */
	u8 conf;	/* trickle config bits */
पूर्ण rv3029_trickle_tab[] = अणु
	अणु
		.r	= 1076,
		.conf	= RV3029_TRICKLE_1K | RV3029_TRICKLE_5K |
			  RV3029_TRICKLE_20K | RV3029_TRICKLE_80K,
	पूर्ण, अणु
		.r	= 1091,
		.conf	= RV3029_TRICKLE_1K | RV3029_TRICKLE_5K |
			  RV3029_TRICKLE_20K,
	पूर्ण, अणु
		.r	= 1137,
		.conf	= RV3029_TRICKLE_1K | RV3029_TRICKLE_5K |
			  RV3029_TRICKLE_80K,
	पूर्ण, अणु
		.r	= 1154,
		.conf	= RV3029_TRICKLE_1K | RV3029_TRICKLE_5K,
	पूर्ण, अणु
		.r	= 1371,
		.conf	= RV3029_TRICKLE_1K | RV3029_TRICKLE_20K |
			  RV3029_TRICKLE_80K,
	पूर्ण, अणु
		.r	= 1395,
		.conf	= RV3029_TRICKLE_1K | RV3029_TRICKLE_20K,
	पूर्ण, अणु
		.r	= 1472,
		.conf	= RV3029_TRICKLE_1K | RV3029_TRICKLE_80K,
	पूर्ण, अणु
		.r	= 1500,
		.conf	= RV3029_TRICKLE_1K,
	पूर्ण, अणु
		.r	= 3810,
		.conf	= RV3029_TRICKLE_5K | RV3029_TRICKLE_20K |
			  RV3029_TRICKLE_80K,
	पूर्ण, अणु
		.r	= 4000,
		.conf	= RV3029_TRICKLE_5K | RV3029_TRICKLE_20K,
	पूर्ण, अणु
		.r	= 4706,
		.conf	= RV3029_TRICKLE_5K | RV3029_TRICKLE_80K,
	पूर्ण, अणु
		.r	= 5000,
		.conf	= RV3029_TRICKLE_5K,
	पूर्ण, अणु
		.r	= 16000,
		.conf	= RV3029_TRICKLE_20K | RV3029_TRICKLE_80K,
	पूर्ण, अणु
		.r	= 20000,
		.conf	= RV3029_TRICKLE_20K,
	पूर्ण, अणु
		.r	= 80000,
		.conf	= RV3029_TRICKLE_80K,
	पूर्ण,
पूर्ण;

अटल व्योम rv3029_trickle_config(काष्ठा device *dev)
अणु
	काष्ठा rv3029_data *rv3029 = dev_get_drvdata(dev);
	काष्ठा device_node *of_node = dev->of_node;
	स्थिर काष्ठा rv3029_trickle_tab_elem *elem;
	पूर्णांक i, err;
	u32 ohms;
	u8 trickle_set_bits;

	अगर (!of_node)
		वापस;

	/* Configure the trickle अक्षरger. */
	err = of_property_पढ़ो_u32(of_node, "trickle-resistor-ohms", &ohms);
	अगर (err) अणु
		/* Disable trickle अक्षरger. */
		trickle_set_bits = 0;
	पूर्ण अन्यथा अणु
		/* Enable trickle अक्षरger. */
		क्रम (i = 0; i < ARRAY_SIZE(rv3029_trickle_tab); i++) अणु
			elem = &rv3029_trickle_tab[i];
			अगर (elem->r >= ohms)
				अवरोध;
		पूर्ण
		trickle_set_bits = elem->conf;
		dev_info(dev,
			 "Trickle charger enabled at %d ohms resistance.\n",
			 elem->r);
	पूर्ण
	err = rv3029_eeprom_update_bits(rv3029, RV3029_CONTROL_E2P_EECTRL,
					RV3029_TRICKLE_MASK,
					trickle_set_bits);
	अगर (err < 0)
		dev_err(dev, "Failed to update trickle charger config\n");
पूर्ण

#अगर_घोषित CONFIG_RTC_DRV_RV3029_HWMON

अटल पूर्णांक rv3029_पढ़ो_temp(काष्ठा rv3029_data *rv3029, पूर्णांक *temp_mC)
अणु
	अचिन्हित पूर्णांक temp;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rv3029->regmap, RV3029_TEMP_PAGE, &temp);
	अगर (ret < 0)
		वापस ret;

	*temp_mC = ((पूर्णांक)temp - 60) * 1000;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार rv3029_hwmon_show_temp(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा rv3029_data *rv3029 = dev_get_drvdata(dev);
	पूर्णांक ret, temp_mC;

	ret = rv3029_पढ़ो_temp(rv3029, &temp_mC);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", temp_mC);
पूर्ण

अटल sमाप_प्रकार rv3029_hwmon_set_update_पूर्णांकerval(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf,
						माप_प्रकार count)
अणु
	काष्ठा rv3029_data *rv3029 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक th_set_bits = 0;
	अचिन्हित दीर्घ पूर्णांकerval_ms;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &पूर्णांकerval_ms);
	अगर (ret < 0)
		वापस ret;

	अगर (पूर्णांकerval_ms != 0) अणु
		th_set_bits |= RV3029_EECTRL_THE;
		अगर (पूर्णांकerval_ms >= 16000)
			th_set_bits |= RV3029_EECTRL_THP;
	पूर्ण
	ret = rv3029_eeprom_update_bits(rv3029, RV3029_CONTROL_E2P_EECTRL,
					RV3029_EECTRL_THE | RV3029_EECTRL_THP,
					th_set_bits);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार rv3029_hwmon_show_update_पूर्णांकerval(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 अक्षर *buf)
अणु
	काष्ठा rv3029_data *rv3029 = dev_get_drvdata(dev);
	पूर्णांक ret, पूर्णांकerval_ms;
	u8 eectrl;

	ret = rv3029_eeprom_पढ़ो(rv3029, RV3029_CONTROL_E2P_EECTRL,
				 &eectrl, 1);
	अगर (ret < 0)
		वापस ret;

	अगर (eectrl & RV3029_EECTRL_THE) अणु
		अगर (eectrl & RV3029_EECTRL_THP)
			पूर्णांकerval_ms = 16000;
		अन्यथा
			पूर्णांकerval_ms = 1000;
	पूर्ण अन्यथा अणु
		पूर्णांकerval_ms = 0;
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", पूर्णांकerval_ms);
पूर्ण

अटल SENSOR_DEVICE_ATTR(temp1_input, S_IRUGO, rv3029_hwmon_show_temp,
			  शून्य, 0);
अटल SENSOR_DEVICE_ATTR(update_पूर्णांकerval, S_IWUSR | S_IRUGO,
			  rv3029_hwmon_show_update_पूर्णांकerval,
			  rv3029_hwmon_set_update_पूर्णांकerval, 0);

अटल काष्ठा attribute *rv3029_hwmon_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_update_पूर्णांकerval.dev_attr.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(rv3029_hwmon);

अटल व्योम rv3029_hwmon_रेजिस्टर(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा rv3029_data *rv3029 = dev_get_drvdata(dev);
	काष्ठा device *hwmon_dev;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, name, rv3029,
							   rv3029_hwmon_groups);
	अगर (IS_ERR(hwmon_dev)) अणु
		dev_warn(dev, "unable to register hwmon device %ld\n",
			 PTR_ERR(hwmon_dev));
	पूर्ण
पूर्ण

#अन्यथा /* CONFIG_RTC_DRV_RV3029_HWMON */

अटल व्योम rv3029_hwmon_रेजिस्टर(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_RTC_DRV_RV3029_HWMON */

अटल स्थिर काष्ठा rtc_class_ops rv3029_rtc_ops = अणु
	.पढ़ो_समय	= rv3029_पढ़ो_समय,
	.set_समय	= rv3029_set_समय,
	.ioctl		= rv3029_ioctl,
	.पढ़ो_alarm	= rv3029_पढ़ो_alarm,
	.set_alarm	= rv3029_set_alarm,
	.alarm_irq_enable = rv3029_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक rv3029_probe(काष्ठा device *dev, काष्ठा regmap *regmap, पूर्णांक irq,
			स्थिर अक्षर *name)
अणु
	काष्ठा rv3029_data *rv3029;
	काष्ठा nvmem_config nvmem_cfg = अणु
		.name = "rv3029_nvram",
		.word_size = 1,
		.stride = 1,
		.size = RV3029_RAM_SECTION_LEN,
		.type = NVMEM_TYPE_BATTERY_BACKED,
		.reg_पढ़ो = rv3029_nvram_पढ़ो,
		.reg_ग_लिखो = rv3029_nvram_ग_लिखो,
	पूर्ण;
	पूर्णांक rc = 0;

	rv3029 = devm_kzalloc(dev, माप(*rv3029), GFP_KERNEL);
	अगर (!rv3029)
		वापस -ENOMEM;

	rv3029->regmap = regmap;
	rv3029->irq = irq;
	rv3029->dev = dev;
	dev_set_drvdata(dev, rv3029);

	rv3029_trickle_config(dev);
	rv3029_hwmon_रेजिस्टर(dev, name);

	rv3029->rtc = devm_rtc_allocate_device(dev);
	अगर (IS_ERR(rv3029->rtc))
		वापस PTR_ERR(rv3029->rtc);

	अगर (rv3029->irq > 0) अणु
		rc = devm_request_thपढ़ोed_irq(dev, rv3029->irq,
					       शून्य, rv3029_handle_irq,
					       IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					       "rv3029", dev);
		अगर (rc) अणु
			dev_warn(dev, "unable to request IRQ, alarms disabled\n");
			rv3029->irq = 0;
		पूर्ण
	पूर्ण
	अगर (!rv3029->irq)
		clear_bit(RTC_FEATURE_ALARM, rv3029->rtc->features);

	rv3029->rtc->ops = &rv3029_rtc_ops;
	rv3029->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rv3029->rtc->range_max = RTC_TIMESTAMP_END_2079;

	rc = devm_rtc_रेजिस्टर_device(rv3029->rtc);
	अगर (rc)
		वापस rc;

	nvmem_cfg.priv = rv3029->regmap;
	devm_rtc_nvmem_रेजिस्टर(rv3029->rtc, &nvmem_cfg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_range rv3029_holes_range[] = अणु
	regmap_reg_range(0x05, 0x07),
	regmap_reg_range(0x0f, 0x0f),
	regmap_reg_range(0x17, 0x17),
	regmap_reg_range(0x1a, 0x1f),
	regmap_reg_range(0x21, 0x27),
	regmap_reg_range(0x34, 0x37),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table rv3029_regs = अणु
	.no_ranges =	rv3029_holes_range,
	.n_no_ranges =	ARRAY_SIZE(rv3029_holes_range),
पूर्ण;

अटल स्थिर काष्ठा regmap_config config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.rd_table = &rv3029_regs,
	.wr_table = &rv3029_regs,
	.max_रेजिस्टर = 0x3f,
पूर्ण;

#अगर IS_ENABLED(CONFIG_I2C)

अटल पूर्णांक rv3029_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_I2C_BLOCK |
				     I2C_FUNC_SMBUS_BYTE)) अणु
		dev_err(&client->dev, "Adapter does not support SMBUS_I2C_BLOCK or SMBUS_I2C_BYTE\n");
		वापस -ENODEV;
	पूर्ण

	regmap = devm_regmap_init_i2c(client, &config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस rv3029_probe(&client->dev, regmap, client->irq, client->name);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id rv3029_id[] = अणु
	अणु "rv3029", 0 पूर्ण,
	अणु "rv3029c2", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rv3029_id);

अटल स्थिर __maybe_unused काष्ठा of_device_id rv3029_of_match[] = अणु
	अणु .compatible = "microcrystal,rv3029" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rv3029_of_match);

अटल काष्ठा i2c_driver rv3029_driver = अणु
	.driver = अणु
		.name = "rv3029",
		.of_match_table = of_match_ptr(rv3029_of_match),
	पूर्ण,
	.probe		= rv3029_i2c_probe,
	.id_table	= rv3029_id,
पूर्ण;

अटल पूर्णांक __init rv3029_रेजिस्टर_driver(व्योम)
अणु
	वापस i2c_add_driver(&rv3029_driver);
पूर्ण

अटल व्योम rv3029_unरेजिस्टर_driver(व्योम)
अणु
	i2c_del_driver(&rv3029_driver);
पूर्ण

#अन्यथा

अटल पूर्णांक __init rv3029_रेजिस्टर_driver(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम rv3029_unरेजिस्टर_driver(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SPI_MASTER)

अटल पूर्णांक rv3049_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_spi(spi, &config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस rv3029_probe(&spi->dev, regmap, spi->irq, "rv3049");
पूर्ण

अटल काष्ठा spi_driver rv3049_driver = अणु
	.driver = अणु
		.name    = "rv3049",
	पूर्ण,
	.probe   = rv3049_probe,
पूर्ण;

अटल पूर्णांक __init rv3049_रेजिस्टर_driver(व्योम)
अणु
	वापस spi_रेजिस्टर_driver(&rv3049_driver);
पूर्ण

अटल व्योम __निकास rv3049_unरेजिस्टर_driver(व्योम)
अणु
	spi_unरेजिस्टर_driver(&rv3049_driver);
पूर्ण

#अन्यथा

अटल पूर्णांक __init rv3049_रेजिस्टर_driver(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम __निकास rv3049_unरेजिस्टर_driver(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __init rv30x9_init(व्योम)
अणु
	पूर्णांक ret;

	ret = rv3029_रेजिस्टर_driver();
	अगर (ret)
		वापस ret;

	ret = rv3049_रेजिस्टर_driver();
	अगर (ret)
		rv3029_unरेजिस्टर_driver();

	वापस ret;
पूर्ण
module_init(rv30x9_init)

अटल व्योम __निकास rv30x9_निकास(व्योम)
अणु
	rv3049_unरेजिस्टर_driver();
	rv3029_unरेजिस्टर_driver();
पूर्ण
module_निकास(rv30x9_निकास)

MODULE_AUTHOR("Gregory Hermant <gregory.hermant@calao-systems.com>");
MODULE_AUTHOR("Michael Buesch <m@bues.ch>");
MODULE_DESCRIPTION("Micro Crystal RV3029/RV3049 RTC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:rv3049");
