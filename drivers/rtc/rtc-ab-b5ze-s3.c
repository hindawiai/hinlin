<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * rtc-ab-b5ze-s3 - Driver क्रम Abracon AB-RTCMC-32.768Khz-B5ZE-S3
 *                  I2C RTC / Alarm chip
 *
 * Copyright (C) 2014, Arnaud EBALARD <arno@natisbad.org>
 *
 * Detailed datasheet of the chip is available here:
 *
 *  https://www.abracon.com/realसमयघड़ी/AB-RTCMC-32.768kHz-B5ZE-S3-Application-Manual.pdf
 *
 * This work is based on ISL12057 driver (drivers/rtc/rtc-isl12057.c).
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/i2c.h>
#समावेश <linux/bcd.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा DRV_NAME "rtc-ab-b5ze-s3"

/* Control section */
#घोषणा ABB5ZES3_REG_CTRL1	   0x00	   /* Control 1 रेजिस्टर */
#घोषणा ABB5ZES3_REG_CTRL1_CIE	   BIT(0)  /* Pulse पूर्णांकerrupt enable */
#घोषणा ABB5ZES3_REG_CTRL1_AIE	   BIT(1)  /* Alarm पूर्णांकerrupt enable */
#घोषणा ABB5ZES3_REG_CTRL1_SIE	   BIT(2)  /* Second पूर्णांकerrupt enable */
#घोषणा ABB5ZES3_REG_CTRL1_PM	   BIT(3)  /* 24h/12h mode */
#घोषणा ABB5ZES3_REG_CTRL1_SR	   BIT(4)  /* Software reset */
#घोषणा ABB5ZES3_REG_CTRL1_STOP	   BIT(5)  /* RTC circuit enable */
#घोषणा ABB5ZES3_REG_CTRL1_CAP	   BIT(7)

#घोषणा ABB5ZES3_REG_CTRL2	   0x01	   /* Control 2 रेजिस्टर */
#घोषणा ABB5ZES3_REG_CTRL2_CTBIE   BIT(0)  /* Countकरोwn समयr B पूर्णांक. enable */
#घोषणा ABB5ZES3_REG_CTRL2_CTAIE   BIT(1)  /* Countकरोwn समयr A पूर्णांक. enable */
#घोषणा ABB5ZES3_REG_CTRL2_WTAIE   BIT(2)  /* Watchकरोg समयr A पूर्णांक. enable */
#घोषणा ABB5ZES3_REG_CTRL2_AF	   BIT(3)  /* Alarm पूर्णांकerrupt status */
#घोषणा ABB5ZES3_REG_CTRL2_SF	   BIT(4)  /* Second पूर्णांकerrupt status */
#घोषणा ABB5ZES3_REG_CTRL2_CTBF	   BIT(5)  /* Countकरोwn समयr B पूर्णांक. status */
#घोषणा ABB5ZES3_REG_CTRL2_CTAF	   BIT(6)  /* Countकरोwn समयr A पूर्णांक. status */
#घोषणा ABB5ZES3_REG_CTRL2_WTAF	   BIT(7)  /* Watchकरोg समयr A पूर्णांक. status */

#घोषणा ABB5ZES3_REG_CTRL3	   0x02	   /* Control 3 रेजिस्टर */
#घोषणा ABB5ZES3_REG_CTRL3_PM2	   BIT(7)  /* Power Management bit 2 */
#घोषणा ABB5ZES3_REG_CTRL3_PM1	   BIT(6)  /* Power Management bit 1 */
#घोषणा ABB5ZES3_REG_CTRL3_PM0	   BIT(5)  /* Power Management bit 0 */
#घोषणा ABB5ZES3_REG_CTRL3_BSF	   BIT(3)  /* Battery चयनover पूर्णांक. status */
#घोषणा ABB5ZES3_REG_CTRL3_BLF	   BIT(2)  /* Battery low पूर्णांक. status */
#घोषणा ABB5ZES3_REG_CTRL3_BSIE	   BIT(1)  /* Battery चयनover पूर्णांक. enable */
#घोषणा ABB5ZES3_REG_CTRL3_BLIE	   BIT(0)  /* Battery low पूर्णांक. enable */

#घोषणा ABB5ZES3_CTRL_SEC_LEN	   3

/* RTC section */
#घोषणा ABB5ZES3_REG_RTC_SC	   0x03	   /* RTC Seconds रेजिस्टर */
#घोषणा ABB5ZES3_REG_RTC_SC_OSC	   BIT(7)  /* Clock पूर्णांकegrity status */
#घोषणा ABB5ZES3_REG_RTC_MN	   0x04	   /* RTC Minutes रेजिस्टर */
#घोषणा ABB5ZES3_REG_RTC_HR	   0x05	   /* RTC Hours रेजिस्टर */
#घोषणा ABB5ZES3_REG_RTC_HR_PM	   BIT(5)  /* RTC Hours PM bit */
#घोषणा ABB5ZES3_REG_RTC_DT	   0x06	   /* RTC Date रेजिस्टर */
#घोषणा ABB5ZES3_REG_RTC_DW	   0x07	   /* RTC Day of the week रेजिस्टर */
#घोषणा ABB5ZES3_REG_RTC_MO	   0x08	   /* RTC Month रेजिस्टर */
#घोषणा ABB5ZES3_REG_RTC_YR	   0x09	   /* RTC Year रेजिस्टर */

#घोषणा ABB5ZES3_RTC_SEC_LEN	   7

/* Alarm section (enable bits are all active low) */
#घोषणा ABB5ZES3_REG_ALRM_MN	   0x0A	   /* Alarm - minute रेजिस्टर */
#घोषणा ABB5ZES3_REG_ALRM_MN_AE	   BIT(7)  /* Minute enable */
#घोषणा ABB5ZES3_REG_ALRM_HR	   0x0B	   /* Alarm - hours रेजिस्टर */
#घोषणा ABB5ZES3_REG_ALRM_HR_AE	   BIT(7)  /* Hour enable */
#घोषणा ABB5ZES3_REG_ALRM_DT	   0x0C	   /* Alarm - date रेजिस्टर */
#घोषणा ABB5ZES3_REG_ALRM_DT_AE	   BIT(7)  /* Date (day of the month) enable */
#घोषणा ABB5ZES3_REG_ALRM_DW	   0x0D	   /* Alarm - day of the week reg. */
#घोषणा ABB5ZES3_REG_ALRM_DW_AE	   BIT(7)  /* Day of the week enable */

#घोषणा ABB5ZES3_ALRM_SEC_LEN	   4

/* Frequency offset section */
#घोषणा ABB5ZES3_REG_FREQ_OF	   0x0E	   /* Frequency offset रेजिस्टर */
#घोषणा ABB5ZES3_REG_FREQ_OF_MODE  0x0E	   /* Offset mode: 2 hours / minute */

/* CLOCKOUT section */
#घोषणा ABB5ZES3_REG_TIM_CLK	   0x0F	   /* Timer & Clockout रेजिस्टर */
#घोषणा ABB5ZES3_REG_TIM_CLK_TAM   BIT(7)  /* Permanent/pulsed समयr A/पूर्णांक. 2 */
#घोषणा ABB5ZES3_REG_TIM_CLK_TBM   BIT(6)  /* Permanent/pulsed समयr B */
#घोषणा ABB5ZES3_REG_TIM_CLK_COF2  BIT(5)  /* Clkout Freq bit 2 */
#घोषणा ABB5ZES3_REG_TIM_CLK_COF1  BIT(4)  /* Clkout Freq bit 1 */
#घोषणा ABB5ZES3_REG_TIM_CLK_COF0  BIT(3)  /* Clkout Freq bit 0 */
#घोषणा ABB5ZES3_REG_TIM_CLK_TAC1  BIT(2)  /* Timer A: - 01 : countकरोwn */
#घोषणा ABB5ZES3_REG_TIM_CLK_TAC0  BIT(1)  /*	       - 10 : समयr	*/
#घोषणा ABB5ZES3_REG_TIM_CLK_TBC   BIT(0)  /* Timer B enable */

/* Timer A Section */
#घोषणा ABB5ZES3_REG_TIMA_CLK	   0x10	   /* Timer A घड़ी रेजिस्टर */
#घोषणा ABB5ZES3_REG_TIMA_CLK_TAQ2 BIT(2)  /* Freq bit 2 */
#घोषणा ABB5ZES3_REG_TIMA_CLK_TAQ1 BIT(1)  /* Freq bit 1 */
#घोषणा ABB5ZES3_REG_TIMA_CLK_TAQ0 BIT(0)  /* Freq bit 0 */
#घोषणा ABB5ZES3_REG_TIMA	   0x11	   /* Timer A रेजिस्टर */

#घोषणा ABB5ZES3_TIMA_SEC_LEN	   2

/* Timer B Section */
#घोषणा ABB5ZES3_REG_TIMB_CLK	   0x12	   /* Timer B घड़ी रेजिस्टर */
#घोषणा ABB5ZES3_REG_TIMB_CLK_TBW2 BIT(6)
#घोषणा ABB5ZES3_REG_TIMB_CLK_TBW1 BIT(5)
#घोषणा ABB5ZES3_REG_TIMB_CLK_TBW0 BIT(4)
#घोषणा ABB5ZES3_REG_TIMB_CLK_TAQ2 BIT(2)
#घोषणा ABB5ZES3_REG_TIMB_CLK_TAQ1 BIT(1)
#घोषणा ABB5ZES3_REG_TIMB_CLK_TAQ0 BIT(0)
#घोषणा ABB5ZES3_REG_TIMB	   0x13	   /* Timer B रेजिस्टर */
#घोषणा ABB5ZES3_TIMB_SEC_LEN	   2

#घोषणा ABB5ZES3_MEM_MAP_LEN	   0x14

काष्ठा abb5zes3_rtc_data अणु
	काष्ठा rtc_device *rtc;
	काष्ठा regmap *regmap;

	पूर्णांक irq;

	bool battery_low;
	bool समयr_alarm; /* current alarm is via समयr A */
पूर्ण;

/*
 * Try and match रेजिस्टर bits w/ fixed null values to see whether we
 * are dealing with an ABB5ZES3.
 */
अटल पूर्णांक abb5zes3_i2c_validate_chip(काष्ठा regmap *regmap)
अणु
	u8 regs[ABB5ZES3_MEM_MAP_LEN];
	अटल स्थिर u8 mask[ABB5ZES3_MEM_MAP_LEN] = अणु 0x00, 0x00, 0x10, 0x00,
						       0x80, 0xc0, 0xc0, 0xf8,
						       0xe0, 0x00, 0x00, 0x40,
						       0x40, 0x78, 0x00, 0x00,
						       0xf8, 0x00, 0x88, 0x00 पूर्ण;
	पूर्णांक ret, i;

	ret = regmap_bulk_पढ़ो(regmap, 0, regs, ABB5ZES3_MEM_MAP_LEN);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ABB5ZES3_MEM_MAP_LEN; ++i) अणु
		अगर (regs[i] & mask[i]) /* check अगर bits are cleared */
			वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/* Clear alarm status bit. */
अटल पूर्णांक _abb5zes3_rtc_clear_alarm(काष्ठा device *dev)
अणु
	काष्ठा abb5zes3_rtc_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regmap_update_bits(data->regmap, ABB5ZES3_REG_CTRL2,
				 ABB5ZES3_REG_CTRL2_AF, 0);
	अगर (ret)
		dev_err(dev, "%s: clearing alarm failed (%d)\n", __func__, ret);

	वापस ret;
पूर्ण

/* Enable or disable alarm (i.e. alarm पूर्णांकerrupt generation) */
अटल पूर्णांक _abb5zes3_rtc_update_alarm(काष्ठा device *dev, bool enable)
अणु
	काष्ठा abb5zes3_rtc_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regmap_update_bits(data->regmap, ABB5ZES3_REG_CTRL1,
				 ABB5ZES3_REG_CTRL1_AIE,
				 enable ? ABB5ZES3_REG_CTRL1_AIE : 0);
	अगर (ret)
		dev_err(dev, "%s: writing alarm INT failed (%d)\n",
			__func__, ret);

	वापस ret;
पूर्ण

/* Enable or disable समयr (watchकरोg समयr A पूर्णांकerrupt generation) */
अटल पूर्णांक _abb5zes3_rtc_update_समयr(काष्ठा device *dev, bool enable)
अणु
	काष्ठा abb5zes3_rtc_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regmap_update_bits(data->regmap, ABB5ZES3_REG_CTRL2,
				 ABB5ZES3_REG_CTRL2_WTAIE,
				 enable ? ABB5ZES3_REG_CTRL2_WTAIE : 0);
	अगर (ret)
		dev_err(dev, "%s: writing timer INT failed (%d)\n",
			__func__, ret);

	वापस ret;
पूर्ण

/*
 * Note: we only पढ़ो, so regmap inner lock protection is sufficient, i.e.
 * we करो not need driver's मुख्य lock protection.
 */
अटल पूर्णांक _abb5zes3_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा abb5zes3_rtc_data *data = dev_get_drvdata(dev);
	u8 regs[ABB5ZES3_REG_RTC_SC + ABB5ZES3_RTC_SEC_LEN];
	पूर्णांक ret = 0;

	/*
	 * As we need to पढ़ो CTRL1 रेजिस्टर anyway to access 24/12h
	 * mode bit, we करो a single bulk पढ़ो of both control and RTC
	 * sections (they are consecutive). This also ease indexing
	 * of रेजिस्टर values after bulk पढ़ो.
	 */
	ret = regmap_bulk_पढ़ो(data->regmap, ABB5ZES3_REG_CTRL1, regs,
			       माप(regs));
	अगर (ret) अणु
		dev_err(dev, "%s: reading RTC time failed (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	/* If घड़ी पूर्णांकegrity is not guaranteed, करो not वापस a समय value */
	अगर (regs[ABB5ZES3_REG_RTC_SC] & ABB5ZES3_REG_RTC_SC_OSC)
		वापस -ENODATA;

	पंचांग->पंचांग_sec = bcd2bin(regs[ABB5ZES3_REG_RTC_SC] & 0x7F);
	पंचांग->पंचांग_min = bcd2bin(regs[ABB5ZES3_REG_RTC_MN]);

	अगर (regs[ABB5ZES3_REG_CTRL1] & ABB5ZES3_REG_CTRL1_PM) अणु /* 12hr mode */
		पंचांग->पंचांग_hour = bcd2bin(regs[ABB5ZES3_REG_RTC_HR] & 0x1f);
		अगर (regs[ABB5ZES3_REG_RTC_HR] & ABB5ZES3_REG_RTC_HR_PM) /* PM */
			पंचांग->पंचांग_hour += 12;
	पूर्ण अन्यथा अणु						/* 24hr mode */
		पंचांग->पंचांग_hour = bcd2bin(regs[ABB5ZES3_REG_RTC_HR]);
	पूर्ण

	पंचांग->पंचांग_mday = bcd2bin(regs[ABB5ZES3_REG_RTC_DT]);
	पंचांग->पंचांग_wday = bcd2bin(regs[ABB5ZES3_REG_RTC_DW]);
	पंचांग->पंचांग_mon  = bcd2bin(regs[ABB5ZES3_REG_RTC_MO]) - 1; /* starts at 1 */
	पंचांग->पंचांग_year = bcd2bin(regs[ABB5ZES3_REG_RTC_YR]) + 100;

	वापस ret;
पूर्ण

अटल पूर्णांक abb5zes3_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा abb5zes3_rtc_data *data = dev_get_drvdata(dev);
	u8 regs[ABB5ZES3_REG_RTC_SC + ABB5ZES3_RTC_SEC_LEN];
	पूर्णांक ret;

	regs[ABB5ZES3_REG_RTC_SC] = bin2bcd(पंचांग->पंचांग_sec); /* MSB=0 clears OSC */
	regs[ABB5ZES3_REG_RTC_MN] = bin2bcd(पंचांग->पंचांग_min);
	regs[ABB5ZES3_REG_RTC_HR] = bin2bcd(पंचांग->पंचांग_hour); /* 24-hour क्रमmat */
	regs[ABB5ZES3_REG_RTC_DT] = bin2bcd(पंचांग->पंचांग_mday);
	regs[ABB5ZES3_REG_RTC_DW] = bin2bcd(पंचांग->पंचांग_wday);
	regs[ABB5ZES3_REG_RTC_MO] = bin2bcd(पंचांग->पंचांग_mon + 1);
	regs[ABB5ZES3_REG_RTC_YR] = bin2bcd(पंचांग->पंचांग_year - 100);

	ret = regmap_bulk_ग_लिखो(data->regmap, ABB5ZES3_REG_RTC_SC,
				regs + ABB5ZES3_REG_RTC_SC,
				ABB5ZES3_RTC_SEC_LEN);

	वापस ret;
पूर्ण

/*
 * Set provided TAQ and Timer A रेजिस्टरs (TIMA_CLK and TIMA) based on
 * given number of seconds.
 */
अटल अंतरभूत व्योम sec_to_समयr_a(u8 secs, u8 *taq, u8 *समयr_a)
अणु
	*taq = ABB5ZES3_REG_TIMA_CLK_TAQ1; /* 1Hz */
	*समयr_a = secs;
पूर्ण

/*
 * Return current number of seconds in Timer A. As we only use
 * समयr A with a 1Hz freq, this is what we expect to have.
 */
अटल अंतरभूत पूर्णांक sec_from_समयr_a(u8 *secs, u8 taq, u8 समयr_a)
अणु
	अगर (taq != ABB5ZES3_REG_TIMA_CLK_TAQ1) /* 1Hz */
		वापस -EINVAL;

	*secs = समयr_a;

	वापस 0;
पूर्ण

/*
 * Read alarm currently configured via a watchकरोg समयr using समयr A. This
 * is करोne by पढ़ोing current RTC समय and adding reमुख्यing समयr समय.
 */
अटल पूर्णांक _abb5zes3_rtc_पढ़ो_समयr(काष्ठा device *dev,
				    काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा abb5zes3_rtc_data *data = dev_get_drvdata(dev);
	काष्ठा rtc_समय rtc_पंचांग, *alarm_पंचांग = &alarm->समय;
	u8 regs[ABB5ZES3_TIMA_SEC_LEN + 1];
	अचिन्हित दीर्घ rtc_secs;
	अचिन्हित पूर्णांक reg;
	u8 समयr_secs;
	पूर्णांक ret;

	/*
	 * Instead of करोing two separate calls, because they are consecutive,
	 * we grab both घड़ीout रेजिस्टर and Timer A section. The latter is
	 * used to decide अगर समयr A is enabled (as a watchकरोg समयr).
	 */
	ret = regmap_bulk_पढ़ो(data->regmap, ABB5ZES3_REG_TIM_CLK, regs,
			       ABB5ZES3_TIMA_SEC_LEN + 1);
	अगर (ret) अणु
		dev_err(dev, "%s: reading Timer A section failed (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	/* get current समय ... */
	ret = _abb5zes3_rtc_पढ़ो_समय(dev, &rtc_पंचांग);
	अगर (ret)
		वापस ret;

	/* ... convert to seconds ... */
	rtc_secs = rtc_पंचांग_to_समय64(&rtc_पंचांग);

	/* ... add reमुख्यing समयr A समय ... */
	ret = sec_from_समयr_a(&समयr_secs, regs[1], regs[2]);
	अगर (ret)
		वापस ret;

	/* ... and convert back. */
	rtc_समय64_to_पंचांग(rtc_secs + समयr_secs, alarm_पंचांग);

	ret = regmap_पढ़ो(data->regmap, ABB5ZES3_REG_CTRL2, &reg);
	अगर (ret) अणु
		dev_err(dev, "%s: reading ctrl reg failed (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	alarm->enabled = !!(reg & ABB5ZES3_REG_CTRL2_WTAIE);

	वापस 0;
पूर्ण

/* Read alarm currently configured via a RTC alarm रेजिस्टरs. */
अटल पूर्णांक _abb5zes3_rtc_पढ़ो_alarm(काष्ठा device *dev,
				    काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा abb5zes3_rtc_data *data = dev_get_drvdata(dev);
	काष्ठा rtc_समय rtc_पंचांग, *alarm_पंचांग = &alarm->समय;
	अचिन्हित दीर्घ rtc_secs, alarm_secs;
	u8 regs[ABB5ZES3_ALRM_SEC_LEN];
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(data->regmap, ABB5ZES3_REG_ALRM_MN, regs,
			       ABB5ZES3_ALRM_SEC_LEN);
	अगर (ret) अणु
		dev_err(dev, "%s: reading alarm section failed (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	alarm_पंचांग->पंचांग_sec  = 0;
	alarm_पंचांग->पंचांग_min  = bcd2bin(regs[0] & 0x7f);
	alarm_पंचांग->पंचांग_hour = bcd2bin(regs[1] & 0x3f);
	alarm_पंचांग->पंचांग_mday = bcd2bin(regs[2] & 0x3f);
	alarm_पंचांग->पंचांग_wday = -1;

	/*
	 * The alarm section करोes not store year/month. We use the ones in rtc
	 * section as a basis and increment month and then year अगर needed to get
	 * alarm after current समय.
	 */
	ret = _abb5zes3_rtc_पढ़ो_समय(dev, &rtc_पंचांग);
	अगर (ret)
		वापस ret;

	alarm_पंचांग->पंचांग_year = rtc_पंचांग.पंचांग_year;
	alarm_पंचांग->पंचांग_mon = rtc_पंचांग.पंचांग_mon;

	rtc_secs = rtc_पंचांग_to_समय64(&rtc_पंचांग);
	alarm_secs = rtc_पंचांग_to_समय64(alarm_पंचांग);

	अगर (alarm_secs < rtc_secs) अणु
		अगर (alarm_पंचांग->पंचांग_mon == 11) अणु
			alarm_पंचांग->पंचांग_mon = 0;
			alarm_पंचांग->पंचांग_year += 1;
		पूर्ण अन्यथा अणु
			alarm_पंचांग->पंचांग_mon += 1;
		पूर्ण
	पूर्ण

	ret = regmap_पढ़ो(data->regmap, ABB5ZES3_REG_CTRL1, &reg);
	अगर (ret) अणु
		dev_err(dev, "%s: reading ctrl reg failed (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	alarm->enabled = !!(reg & ABB5ZES3_REG_CTRL1_AIE);

	वापस 0;
पूर्ण

/*
 * As the Alarm mechanism supported by the chip is only accurate to the
 * minute, we use the watchकरोg समयr mechanism provided by समयr A
 * (up to 256 seconds w/ a second accuracy) क्रम low alarm values (below
 * 4 minutes). Otherwise, we use the common alarm mechanism provided
 * by the chip. In order क्रम that to work, we keep track of currently
 * configured समयr type via 'timer_alarm' flag in our निजी data
 * काष्ठाure.
 */
अटल पूर्णांक abb5zes3_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा abb5zes3_rtc_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (data->समयr_alarm)
		ret = _abb5zes3_rtc_पढ़ो_समयr(dev, alarm);
	अन्यथा
		ret = _abb5zes3_rtc_पढ़ो_alarm(dev, alarm);

	वापस ret;
पूर्ण

/*
 * Set alarm using chip alarm mechanism. It is only accurate to the
 * minute (not the second). The function expects alarm पूर्णांकerrupt to
 * be disabled.
 */
अटल पूर्णांक _abb5zes3_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा abb5zes3_rtc_data *data = dev_get_drvdata(dev);
	काष्ठा rtc_समय *alarm_पंचांग = &alarm->समय;
	u8 regs[ABB5ZES3_ALRM_SEC_LEN];
	काष्ठा rtc_समय rtc_पंचांग;
	पूर्णांक ret, enable = 1;

	अगर (!alarm->enabled) अणु
		enable = 0;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ rtc_secs, alarm_secs;

		/*
		 * Chip only support alarms up to one month in the future. Let's
		 * वापस an error अगर we get something after that limit.
		 * Comparison is करोne by incrementing rtc_पंचांग month field by one
		 * and checking alarm value is still below.
		 */
		ret = _abb5zes3_rtc_पढ़ो_समय(dev, &rtc_पंचांग);
		अगर (ret)
			वापस ret;

		अगर (rtc_पंचांग.पंचांग_mon == 11) अणु /* handle year wrapping */
			rtc_पंचांग.पंचांग_mon = 0;
			rtc_पंचांग.पंचांग_year += 1;
		पूर्ण अन्यथा अणु
			rtc_पंचांग.पंचांग_mon += 1;
		पूर्ण

		rtc_secs = rtc_पंचांग_to_समय64(&rtc_पंचांग);
		alarm_secs = rtc_पंचांग_to_समय64(alarm_पंचांग);

		अगर (alarm_secs > rtc_secs) अणु
			dev_err(dev, "%s: alarm maximum is one month in the future (%d)\n",
				__func__, ret);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * Program all alarm रेजिस्टरs but DW one. For each रेजिस्टर, setting
	 * MSB to 0 enables associated alarm.
	 */
	regs[0] = bin2bcd(alarm_पंचांग->पंचांग_min) & 0x7f;
	regs[1] = bin2bcd(alarm_पंचांग->पंचांग_hour) & 0x3f;
	regs[2] = bin2bcd(alarm_पंचांग->पंचांग_mday) & 0x3f;
	regs[3] = ABB5ZES3_REG_ALRM_DW_AE; /* करो not match day of the week */

	ret = regmap_bulk_ग_लिखो(data->regmap, ABB5ZES3_REG_ALRM_MN, regs,
				ABB5ZES3_ALRM_SEC_LEN);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: writing ALARM section failed (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	/* Record currently configured alarm is not a समयr */
	data->समयr_alarm = 0;

	/* Enable or disable alarm पूर्णांकerrupt generation */
	वापस _abb5zes3_rtc_update_alarm(dev, enable);
पूर्ण

/*
 * Set alarm using समयr watchकरोg (via समयr A) mechanism. The function expects
 * समयr A पूर्णांकerrupt to be disabled.
 */
अटल पूर्णांक _abb5zes3_rtc_set_समयr(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm,
				   u8 secs)
अणु
	काष्ठा abb5zes3_rtc_data *data = dev_get_drvdata(dev);
	u8 regs[ABB5ZES3_TIMA_SEC_LEN];
	u8 mask = ABB5ZES3_REG_TIM_CLK_TAC0 | ABB5ZES3_REG_TIM_CLK_TAC1;
	पूर्णांक ret = 0;

	/* Program given number of seconds to Timer A रेजिस्टरs */
	sec_to_समयr_a(secs, &regs[0], &regs[1]);
	ret = regmap_bulk_ग_लिखो(data->regmap, ABB5ZES3_REG_TIMA_CLK, regs,
				ABB5ZES3_TIMA_SEC_LEN);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: writing timer section failed\n", __func__);
		वापस ret;
	पूर्ण

	/* Configure Timer A as a watchकरोg समयr */
	ret = regmap_update_bits(data->regmap, ABB5ZES3_REG_TIM_CLK,
				 mask, ABB5ZES3_REG_TIM_CLK_TAC1);
	अगर (ret)
		dev_err(dev, "%s: failed to update timer\n", __func__);

	/* Record currently configured alarm is a समयr */
	data->समयr_alarm = 1;

	/* Enable or disable समयr पूर्णांकerrupt generation */
	वापस _abb5zes3_rtc_update_समयr(dev, alarm->enabled);
पूर्ण

/*
 * The chip has an alarm which is only accurate to the minute. In order to
 * handle alarms below that limit, we use the watchकरोg समयr function of
 * समयr A. More precisely, the समयr method is used क्रम alarms below 240
 * seconds.
 */
अटल पूर्णांक abb5zes3_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा abb5zes3_rtc_data *data = dev_get_drvdata(dev);
	काष्ठा rtc_समय *alarm_पंचांग = &alarm->समय;
	अचिन्हित दीर्घ rtc_secs, alarm_secs;
	काष्ठा rtc_समय rtc_पंचांग;
	पूर्णांक ret;

	ret = _abb5zes3_rtc_पढ़ो_समय(dev, &rtc_पंचांग);
	अगर (ret)
		वापस ret;

	rtc_secs = rtc_पंचांग_to_समय64(&rtc_पंचांग);
	alarm_secs = rtc_पंचांग_to_समय64(alarm_पंचांग);

	/* Let's first disable both the alarm and the समयr पूर्णांकerrupts */
	ret = _abb5zes3_rtc_update_alarm(dev, false);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: unable to disable alarm (%d)\n", __func__,
			ret);
		वापस ret;
	पूर्ण
	ret = _abb5zes3_rtc_update_समयr(dev, false);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: unable to disable timer (%d)\n", __func__,
			ret);
		वापस ret;
	पूर्ण

	data->समयr_alarm = 0;

	/*
	 * Let's now configure the alarm; अगर we are expected to ring in
	 * more than 240s, then we setup an alarm. Otherwise, a समयr.
	 */
	अगर ((alarm_secs > rtc_secs) && ((alarm_secs - rtc_secs) <= 240))
		ret = _abb5zes3_rtc_set_समयr(dev, alarm,
					      alarm_secs - rtc_secs);
	अन्यथा
		ret = _abb5zes3_rtc_set_alarm(dev, alarm);

	अगर (ret)
		dev_err(dev, "%s: unable to configure alarm (%d)\n", __func__,
			ret);

	वापस ret;
पूर्ण

/* Enable or disable battery low irq generation */
अटल अंतरभूत पूर्णांक _abb5zes3_rtc_battery_low_irq_enable(काष्ठा regmap *regmap,
						       bool enable)
अणु
	वापस regmap_update_bits(regmap, ABB5ZES3_REG_CTRL3,
				  ABB5ZES3_REG_CTRL3_BLIE,
				  enable ? ABB5ZES3_REG_CTRL3_BLIE : 0);
पूर्ण

/*
 * Check current RTC status and enable/disable what needs to be. Return 0 अगर
 * everything went ok and a negative value upon error.
 */
अटल पूर्णांक abb5zes3_rtc_check_setup(काष्ठा device *dev)
अणु
	काष्ठा abb5zes3_rtc_data *data = dev_get_drvdata(dev);
	काष्ठा regmap *regmap = data->regmap;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;
	u8 mask;

	/*
	 * By शेष, the devices generates a 32.768KHz संकेत on IRQ#1 pin. It
	 * is disabled here to prevent polluting the पूर्णांकerrupt line and
	 * uselessly triggering the IRQ handler we install क्रम alarm and battery
	 * low events. Note: this is करोne beक्रमe clearing पूर्णांक. status below
	 * in this function.
	 * We also disable all समयrs and set समयr पूर्णांकerrupt to permanent (not
	 * pulsed).
	 */
	mask = (ABB5ZES3_REG_TIM_CLK_TBC | ABB5ZES3_REG_TIM_CLK_TAC0 |
		ABB5ZES3_REG_TIM_CLK_TAC1 | ABB5ZES3_REG_TIM_CLK_COF0 |
		ABB5ZES3_REG_TIM_CLK_COF1 | ABB5ZES3_REG_TIM_CLK_COF2 |
		ABB5ZES3_REG_TIM_CLK_TBM | ABB5ZES3_REG_TIM_CLK_TAM);
	ret = regmap_update_bits(regmap, ABB5ZES3_REG_TIM_CLK, mask,
				 ABB5ZES3_REG_TIM_CLK_COF0 |
				 ABB5ZES3_REG_TIM_CLK_COF1 |
				 ABB5ZES3_REG_TIM_CLK_COF2);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: unable to initialize clkout register (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	/*
	 * Each component of the alarm (MN, HR, DT, DW) can be enabled/disabled
	 * inभागidually by clearing/setting MSB of each associated रेजिस्टर. So,
	 * we set all alarm enable bits to disable current alarm setting.
	 */
	mask = (ABB5ZES3_REG_ALRM_MN_AE | ABB5ZES3_REG_ALRM_HR_AE |
		ABB5ZES3_REG_ALRM_DT_AE | ABB5ZES3_REG_ALRM_DW_AE);
	ret = regmap_update_bits(regmap, ABB5ZES3_REG_CTRL2, mask, mask);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: unable to disable alarm setting (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	/* Set Control 1 रेजिस्टर (RTC enabled, 24hr mode, all पूर्णांक. disabled) */
	mask = (ABB5ZES3_REG_CTRL1_CIE | ABB5ZES3_REG_CTRL1_AIE |
		ABB5ZES3_REG_CTRL1_SIE | ABB5ZES3_REG_CTRL1_PM |
		ABB5ZES3_REG_CTRL1_CAP | ABB5ZES3_REG_CTRL1_STOP);
	ret = regmap_update_bits(regmap, ABB5ZES3_REG_CTRL1, mask, 0);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: unable to initialize CTRL1 register (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	/*
	 * Set Control 2 रेजिस्टर (समयr पूर्णांक. disabled, alarm status cleared).
	 * WTAF is पढ़ो-only and cleared स्वतःmatically by पढ़ोing the रेजिस्टर.
	 */
	mask = (ABB5ZES3_REG_CTRL2_CTBIE | ABB5ZES3_REG_CTRL2_CTAIE |
		ABB5ZES3_REG_CTRL2_WTAIE | ABB5ZES3_REG_CTRL2_AF |
		ABB5ZES3_REG_CTRL2_SF | ABB5ZES3_REG_CTRL2_CTBF |
		ABB5ZES3_REG_CTRL2_CTAF);
	ret = regmap_update_bits(regmap, ABB5ZES3_REG_CTRL2, mask, 0);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: unable to initialize CTRL2 register (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	/*
	 * Enable battery low detection function and battery चयनover function
	 * (standard mode). Disable associated पूर्णांकerrupts. Clear battery
	 * चयनover flag but not battery low flag. The latter is checked
	 * later below.
	 */
	mask = (ABB5ZES3_REG_CTRL3_PM0  | ABB5ZES3_REG_CTRL3_PM1 |
		ABB5ZES3_REG_CTRL3_PM2  | ABB5ZES3_REG_CTRL3_BLIE |
		ABB5ZES3_REG_CTRL3_BSIE | ABB5ZES3_REG_CTRL3_BSF);
	ret = regmap_update_bits(regmap, ABB5ZES3_REG_CTRL3, mask, 0);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: unable to initialize CTRL3 register (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	/* Check oscillator पूर्णांकegrity flag */
	ret = regmap_पढ़ो(regmap, ABB5ZES3_REG_RTC_SC, &reg);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: unable to read osc. integrity flag (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	अगर (reg & ABB5ZES3_REG_RTC_SC_OSC) अणु
		dev_err(dev, "clock integrity not guaranteed. Osc. has stopped or has been interrupted.\n");
		dev_err(dev, "change battery (if not already done) and then set time to reset osc. failure flag.\n");
	पूर्ण

	/*
	 * Check battery low flag at startup: this allows reporting battery
	 * is low at startup when IRQ line is not connected. Note: we record
	 * current status to aव्योम reenabling this पूर्णांकerrupt later in probe
	 * function अगर battery is low.
	 */
	ret = regmap_पढ़ो(regmap, ABB5ZES3_REG_CTRL3, &reg);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: unable to read battery low flag (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	data->battery_low = reg & ABB5ZES3_REG_CTRL3_BLF;
	अगर (data->battery_low) अणु
		dev_err(dev, "RTC battery is low; please, consider changing it!\n");

		ret = _abb5zes3_rtc_battery_low_irq_enable(regmap, false);
		अगर (ret)
			dev_err(dev, "%s: disabling battery low interrupt generation failed (%d)\n",
				__func__, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक abb5zes3_rtc_alarm_irq_enable(काष्ठा device *dev,
					 अचिन्हित पूर्णांक enable)
अणु
	काष्ठा abb5zes3_rtc_data *rtc_data = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (rtc_data->irq) अणु
		अगर (rtc_data->समयr_alarm)
			ret = _abb5zes3_rtc_update_समयr(dev, enable);
		अन्यथा
			ret = _abb5zes3_rtc_update_alarm(dev, enable);
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t _abb5zes3_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा i2c_client *client = data;
	काष्ठा device *dev = &client->dev;
	काष्ठा abb5zes3_rtc_data *rtc_data = dev_get_drvdata(dev);
	काष्ठा rtc_device *rtc = rtc_data->rtc;
	u8 regs[ABB5ZES3_CTRL_SEC_LEN];
	पूर्णांक ret, handled = IRQ_NONE;

	ret = regmap_bulk_पढ़ो(rtc_data->regmap, 0, regs,
			       ABB5ZES3_CTRL_SEC_LEN);
	अगर (ret) अणु
		dev_err(dev, "%s: unable to read control section (%d)!\n",
			__func__, ret);
		वापस handled;
	पूर्ण

	/*
	 * Check battery low detection flag and disable battery low पूर्णांकerrupt
	 * generation अगर flag is set (पूर्णांकerrupt can only be cleared when
	 * battery is replaced).
	 */
	अगर (regs[ABB5ZES3_REG_CTRL3] & ABB5ZES3_REG_CTRL3_BLF) अणु
		dev_err(dev, "RTC battery is low; please change it!\n");

		_abb5zes3_rtc_battery_low_irq_enable(rtc_data->regmap, false);

		handled = IRQ_HANDLED;
	पूर्ण

	/* Check alarm flag */
	अगर (regs[ABB5ZES3_REG_CTRL2] & ABB5ZES3_REG_CTRL2_AF) अणु
		dev_dbg(dev, "RTC alarm!\n");

		rtc_update_irq(rtc, 1, RTC_IRQF | RTC_AF);

		/* Acknowledge and disable the alarm */
		_abb5zes3_rtc_clear_alarm(dev);
		_abb5zes3_rtc_update_alarm(dev, 0);

		handled = IRQ_HANDLED;
	पूर्ण

	/* Check watchकरोg Timer A flag */
	अगर (regs[ABB5ZES3_REG_CTRL2] & ABB5ZES3_REG_CTRL2_WTAF) अणु
		dev_dbg(dev, "RTC timer!\n");

		rtc_update_irq(rtc, 1, RTC_IRQF | RTC_AF);

		/*
		 * Acknowledge and disable the alarm. Note: WTAF
		 * flag had been cleared when पढ़ोing CTRL2
		 */
		_abb5zes3_rtc_update_समयr(dev, 0);

		rtc_data->समयr_alarm = 0;

		handled = IRQ_HANDLED;
	पूर्ण

	वापस handled;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rtc_ops = अणु
	.पढ़ो_समय = _abb5zes3_rtc_पढ़ो_समय,
	.set_समय = abb5zes3_rtc_set_समय,
	.पढ़ो_alarm = abb5zes3_rtc_पढ़ो_alarm,
	.set_alarm = abb5zes3_rtc_set_alarm,
	.alarm_irq_enable = abb5zes3_rtc_alarm_irq_enable,
पूर्ण;

अटल स्थिर काष्ठा regmap_config abb5zes3_rtc_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक abb5zes3_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा abb5zes3_rtc_data *data = शून्य;
	काष्ठा device *dev = &client->dev;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C |
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_I2C_BLOCK))
		वापस -ENODEV;

	regmap = devm_regmap_init_i2c(client, &abb5zes3_rtc_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(dev, "%s: regmap allocation failed: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	ret = abb5zes3_i2c_validate_chip(regmap);
	अगर (ret)
		वापस ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->regmap = regmap;
	dev_set_drvdata(dev, data);

	ret = abb5zes3_rtc_check_setup(dev);
	अगर (ret)
		वापस ret;

	data->rtc = devm_rtc_allocate_device(dev);
	ret = PTR_ERR_OR_ZERO(data->rtc);
	अगर (ret) अणु
		dev_err(dev, "%s: unable to allocate RTC device (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
						_abb5zes3_rtc_पूर्णांकerrupt,
						IRQF_SHARED | IRQF_ONESHOT,
						DRV_NAME, client);
		अगर (!ret) अणु
			device_init_wakeup(dev, true);
			data->irq = client->irq;
			dev_dbg(dev, "%s: irq %d used by RTC\n", __func__,
				client->irq);
		पूर्ण अन्यथा अणु
			dev_err(dev, "%s: irq %d unavailable (%d)\n",
				__func__, client->irq, ret);
			जाओ err;
		पूर्ण
	पूर्ण

	data->rtc->ops = &rtc_ops;
	data->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	data->rtc->range_max = RTC_TIMESTAMP_END_2099;

	/* Enable battery low detection पूर्णांकerrupt अगर battery not alपढ़ोy low */
	अगर (!data->battery_low && data->irq) अणु
		ret = _abb5zes3_rtc_battery_low_irq_enable(regmap, true);
		अगर (ret) अणु
			dev_err(dev, "%s: enabling battery low interrupt generation failed (%d)\n",
				__func__, ret);
			जाओ err;
		पूर्ण
	पूर्ण

	ret = devm_rtc_रेजिस्टर_device(data->rtc);

err:
	अगर (ret && data->irq)
		device_init_wakeup(dev, false);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक abb5zes3_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा abb5zes3_rtc_data *rtc_data = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		वापस enable_irq_wake(rtc_data->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक abb5zes3_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा abb5zes3_rtc_data *rtc_data = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		वापस disable_irq_wake(rtc_data->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(abb5zes3_rtc_pm_ops, abb5zes3_rtc_suspend,
			 abb5zes3_rtc_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id abb5zes3_dt_match[] = अणु
	अणु .compatible = "abracon,abb5zes3" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, abb5zes3_dt_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id abb5zes3_id[] = अणु
	अणु "abb5zes3", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, abb5zes3_id);

अटल काष्ठा i2c_driver abb5zes3_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &abb5zes3_rtc_pm_ops,
		.of_match_table = of_match_ptr(abb5zes3_dt_match),
	पूर्ण,
	.probe	  = abb5zes3_probe,
	.id_table = abb5zes3_id,
पूर्ण;
module_i2c_driver(abb5zes3_driver);

MODULE_AUTHOR("Arnaud EBALARD <arno@natisbad.org>");
MODULE_DESCRIPTION("Abracon AB-RTCMC-32.768kHz-B5ZE-S3 RTC/Alarm driver");
MODULE_LICENSE("GPL");
