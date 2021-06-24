<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An rtc driver क्रम the Dallas/Maxim DS1685/DS1687 and related real-समय
 * chips.
 *
 * Copyright (C) 2011-2014 Joshua Kinard <kumba@gentoo.org>.
 * Copyright (C) 2009 Matthias Fuchs <matthias.fuchs@esd-electronics.com>.
 *
 * References:
 *    DS1685/DS1687 3V/5V Real-Time Clocks, 19-5215, Rev 4/10.
 *    DS17x85/DS17x87 3V/5V Real-Time Clocks, 19-5222, Rev 4/10.
 *    DS1689/DS1693 3V/5V Serialized Real-Time Clocks, Rev 112105.
 *    Application Note 90, Using the Multiplex Bus RTC Extended Features.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bcd.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/rtc/ds1685.h>

#अगर_घोषित CONFIG_PROC_FS
#समावेश <linux/proc_fs.h>
#पूर्ण_अगर


/* ----------------------------------------------------------------------- */
/*
 *  Standard पढ़ो/ग_लिखो
 *  all रेजिस्टरs are mapped in CPU address space
 */

/**
 * ds1685_पढ़ो - पढ़ो a value from an rtc रेजिस्टर.
 * @rtc: poपूर्णांकer to the ds1685 rtc काष्ठाure.
 * @reg: the रेजिस्टर address to पढ़ो.
 */
अटल u8
ds1685_पढ़ो(काष्ठा ds1685_priv *rtc, पूर्णांक reg)
अणु
	वापस पढ़ोb((u8 __iomem *)rtc->regs +
		     (reg * rtc->regstep));
पूर्ण

/**
 * ds1685_ग_लिखो - ग_लिखो a value to an rtc रेजिस्टर.
 * @rtc: poपूर्णांकer to the ds1685 rtc काष्ठाure.
 * @reg: the रेजिस्टर address to ग_लिखो.
 * @value: value to ग_लिखो to the रेजिस्टर.
 */
अटल व्योम
ds1685_ग_लिखो(काष्ठा ds1685_priv *rtc, पूर्णांक reg, u8 value)
अणु
	ग_लिखोb(value, ((u8 __iomem *)rtc->regs +
		       (reg * rtc->regstep)));
पूर्ण
/* ----------------------------------------------------------------------- */

/*
 * Indirect पढ़ो/ग_लिखो functions
 * access happens via address and data रेजिस्टर mapped in CPU address space
 */

/**
 * ds1685_indirect_पढ़ो - पढ़ो a value from an rtc रेजिस्टर.
 * @rtc: poपूर्णांकer to the ds1685 rtc काष्ठाure.
 * @reg: the रेजिस्टर address to पढ़ो.
 */
अटल u8
ds1685_indirect_पढ़ो(काष्ठा ds1685_priv *rtc, पूर्णांक reg)
अणु
	ग_लिखोb(reg, rtc->regs);
	वापस पढ़ोb(rtc->data);
पूर्ण

/**
 * ds1685_indirect_ग_लिखो - ग_लिखो a value to an rtc रेजिस्टर.
 * @rtc: poपूर्णांकer to the ds1685 rtc काष्ठाure.
 * @reg: the रेजिस्टर address to ग_लिखो.
 * @value: value to ग_लिखो to the रेजिस्टर.
 */
अटल व्योम
ds1685_indirect_ग_लिखो(काष्ठा ds1685_priv *rtc, पूर्णांक reg, u8 value)
अणु
	ग_लिखोb(reg, rtc->regs);
	ग_लिखोb(value, rtc->data);
पूर्ण

/* ----------------------------------------------------------------------- */
/* Inlined functions */

/**
 * ds1685_rtc_bcd2bin - bcd2bin wrapper in हाल platक्रमm करोesn't support BCD.
 * @rtc: poपूर्णांकer to the ds1685 rtc काष्ठाure.
 * @val: u8 समय value to consider converting.
 * @bcd_mask: u8 mask value अगर BCD mode is used.
 * @bin_mask: u8 mask value अगर BIN mode is used.
 *
 * Returns the value, converted to BIN अगर originally in BCD and bcd_mode TRUE.
 */
अटल अंतरभूत u8
ds1685_rtc_bcd2bin(काष्ठा ds1685_priv *rtc, u8 val, u8 bcd_mask, u8 bin_mask)
अणु
	अगर (rtc->bcd_mode)
		वापस (bcd2bin(val) & bcd_mask);

	वापस (val & bin_mask);
पूर्ण

/**
 * ds1685_rtc_bin2bcd - bin2bcd wrapper in हाल platक्रमm करोesn't support BCD.
 * @rtc: poपूर्णांकer to the ds1685 rtc काष्ठाure.
 * @val: u8 समय value to consider converting.
 * @bin_mask: u8 mask value अगर BIN mode is used.
 * @bcd_mask: u8 mask value अगर BCD mode is used.
 *
 * Returns the value, converted to BCD अगर originally in BIN and bcd_mode TRUE.
 */
अटल अंतरभूत u8
ds1685_rtc_bin2bcd(काष्ठा ds1685_priv *rtc, u8 val, u8 bin_mask, u8 bcd_mask)
अणु
	अगर (rtc->bcd_mode)
		वापस (bin2bcd(val) & bcd_mask);

	वापस (val & bin_mask);
पूर्ण

/**
 * s1685_rtc_check_mday - check validity of the day of month.
 * @rtc: poपूर्णांकer to the ds1685 rtc काष्ठाure.
 * @mday: day of month.
 *
 * Returns -गलत_तर्क अगर the day of month is not within 1..31 range.
 */
अटल अंतरभूत पूर्णांक
ds1685_rtc_check_mday(काष्ठा ds1685_priv *rtc, u8 mday)
अणु
	अगर (rtc->bcd_mode) अणु
		अगर (mday < 0x01 || mday > 0x31 || (mday & 0x0f) > 0x09)
			वापस -गलत_तर्क;
	पूर्ण अन्यथा अणु
		अगर (mday < 1 || mday > 31)
			वापस -गलत_तर्क;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ds1685_rtc_चयन_to_bank0 - चयन the rtc to bank 0.
 * @rtc: poपूर्णांकer to the ds1685 rtc काष्ठाure.
 */
अटल अंतरभूत व्योम
ds1685_rtc_चयन_to_bank0(काष्ठा ds1685_priv *rtc)
अणु
	rtc->ग_लिखो(rtc, RTC_CTRL_A,
		   (rtc->पढ़ो(rtc, RTC_CTRL_A) & ~(RTC_CTRL_A_DV0)));
पूर्ण

/**
 * ds1685_rtc_चयन_to_bank1 - चयन the rtc to bank 1.
 * @rtc: poपूर्णांकer to the ds1685 rtc काष्ठाure.
 */
अटल अंतरभूत व्योम
ds1685_rtc_चयन_to_bank1(काष्ठा ds1685_priv *rtc)
अणु
	rtc->ग_लिखो(rtc, RTC_CTRL_A,
		   (rtc->पढ़ो(rtc, RTC_CTRL_A) | RTC_CTRL_A_DV0));
पूर्ण

/**
 * ds1685_rtc_begin_data_access - prepare the rtc क्रम data access.
 * @rtc: poपूर्णांकer to the ds1685 rtc काष्ठाure.
 *
 * This takes several steps to prepare the rtc क्रम access to get/set समय
 * and alarm values from the rtc रेजिस्टरs:
 *  - Sets the SET bit in Control Register B.
 *  - Reads Ext Control Register 4A and checks the INCR bit.
 *  - If INCR is active, a लघु delay is added beक्रमe Ext Control Register 4A
 *    is पढ़ो again in a loop until INCR is inactive.
 *  - Switches the rtc to bank 1.  This allows access to all relevant
 *    data क्रम normal rtc operation, as bank 0 contains only the nvram.
 */
अटल अंतरभूत व्योम
ds1685_rtc_begin_data_access(काष्ठा ds1685_priv *rtc)
अणु
	/* Set the SET bit in Ctrl B */
	rtc->ग_लिखो(rtc, RTC_CTRL_B,
		   (rtc->पढ़ो(rtc, RTC_CTRL_B) | RTC_CTRL_B_SET));

	/* Switch to Bank 1 */
	ds1685_rtc_चयन_to_bank1(rtc);

	/* Read Ext Ctrl 4A and check the INCR bit to aव्योम a lockout. */
	जबतक (rtc->पढ़ो(rtc, RTC_EXT_CTRL_4A) & RTC_CTRL_4A_INCR)
		cpu_relax();
पूर्ण

/**
 * ds1685_rtc_end_data_access - end data access on the rtc.
 * @rtc: poपूर्णांकer to the ds1685 rtc काष्ठाure.
 *
 * This ends what was started by ds1685_rtc_begin_data_access:
 *  - Switches the rtc back to bank 0.
 *  - Clears the SET bit in Control Register B.
 */
अटल अंतरभूत व्योम
ds1685_rtc_end_data_access(काष्ठा ds1685_priv *rtc)
अणु
	/* Switch back to Bank 0 */
	ds1685_rtc_चयन_to_bank0(rtc);

	/* Clear the SET bit in Ctrl B */
	rtc->ग_लिखो(rtc, RTC_CTRL_B,
		   (rtc->पढ़ो(rtc, RTC_CTRL_B) & ~(RTC_CTRL_B_SET)));
पूर्ण

/**
 * ds1685_rtc_get_ssn - retrieve the silicon serial number.
 * @rtc: poपूर्णांकer to the ds1685 rtc काष्ठाure.
 * @ssn: u8 array to hold the bits of the silicon serial number.
 *
 * This number starts at 0x40, and is 8-bytes दीर्घ, ending at 0x47. The
 * first byte is the model number, the next six bytes are the serial number
 * digits, and the final byte is a CRC check byte.  Together, they क्रमm the
 * silicon serial number.
 *
 * These values are stored in bank1, so ds1685_rtc_चयन_to_bank1 must be
 * called first beक्रमe calling this function, अन्यथा data will be पढ़ो out of
 * the bank0 NVRAM.  Be sure to call ds1685_rtc_चयन_to_bank0 when करोne.
 */
अटल अंतरभूत व्योम
ds1685_rtc_get_ssn(काष्ठा ds1685_priv *rtc, u8 *ssn)
अणु
	ssn[0] = rtc->पढ़ो(rtc, RTC_BANK1_SSN_MODEL);
	ssn[1] = rtc->पढ़ो(rtc, RTC_BANK1_SSN_BYTE_1);
	ssn[2] = rtc->पढ़ो(rtc, RTC_BANK1_SSN_BYTE_2);
	ssn[3] = rtc->पढ़ो(rtc, RTC_BANK1_SSN_BYTE_3);
	ssn[4] = rtc->पढ़ो(rtc, RTC_BANK1_SSN_BYTE_4);
	ssn[5] = rtc->पढ़ो(rtc, RTC_BANK1_SSN_BYTE_5);
	ssn[6] = rtc->पढ़ो(rtc, RTC_BANK1_SSN_BYTE_6);
	ssn[7] = rtc->पढ़ो(rtc, RTC_BANK1_SSN_CRC);
पूर्ण
/* ----------------------------------------------------------------------- */


/* ----------------------------------------------------------------------- */
/* Read/Set Time & Alarm functions */

/**
 * ds1685_rtc_पढ़ो_समय - पढ़ोs the समय रेजिस्टरs.
 * @dev: poपूर्णांकer to device काष्ठाure.
 * @पंचांग: poपूर्णांकer to rtc_समय काष्ठाure.
 */
अटल पूर्णांक
ds1685_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा ds1685_priv *rtc = dev_get_drvdata(dev);
	u8 century;
	u8 seconds, minutes, hours, wday, mday, month, years;

	/* Fetch the समय info from the RTC रेजिस्टरs. */
	ds1685_rtc_begin_data_access(rtc);
	seconds = rtc->पढ़ो(rtc, RTC_SECS);
	minutes = rtc->पढ़ो(rtc, RTC_MINS);
	hours   = rtc->पढ़ो(rtc, RTC_HRS);
	wday    = rtc->पढ़ो(rtc, RTC_WDAY);
	mday    = rtc->पढ़ो(rtc, RTC_MDAY);
	month   = rtc->पढ़ो(rtc, RTC_MONTH);
	years   = rtc->पढ़ो(rtc, RTC_YEAR);
	century = rtc->पढ़ो(rtc, RTC_CENTURY);
	ds1685_rtc_end_data_access(rtc);

	/* bcd2bin अगर needed, perक्रमm fixups, and store to rtc_समय. */
	years        = ds1685_rtc_bcd2bin(rtc, years, RTC_YEAR_BCD_MASK,
					  RTC_YEAR_BIN_MASK);
	century      = ds1685_rtc_bcd2bin(rtc, century, RTC_CENTURY_MASK,
					  RTC_CENTURY_MASK);
	पंचांग->पंचांग_sec   = ds1685_rtc_bcd2bin(rtc, seconds, RTC_SECS_BCD_MASK,
					  RTC_SECS_BIN_MASK);
	पंचांग->पंचांग_min   = ds1685_rtc_bcd2bin(rtc, minutes, RTC_MINS_BCD_MASK,
					  RTC_MINS_BIN_MASK);
	पंचांग->पंचांग_hour  = ds1685_rtc_bcd2bin(rtc, hours, RTC_HRS_24_BCD_MASK,
					  RTC_HRS_24_BIN_MASK);
	पंचांग->पंचांग_wday  = (ds1685_rtc_bcd2bin(rtc, wday, RTC_WDAY_MASK,
					   RTC_WDAY_MASK) - 1);
	पंचांग->पंचांग_mday  = ds1685_rtc_bcd2bin(rtc, mday, RTC_MDAY_BCD_MASK,
					  RTC_MDAY_BIN_MASK);
	पंचांग->पंचांग_mon   = (ds1685_rtc_bcd2bin(rtc, month, RTC_MONTH_BCD_MASK,
					   RTC_MONTH_BIN_MASK) - 1);
	पंचांग->पंचांग_year  = ((years + (century * 100)) - 1900);
	पंचांग->पंचांग_yday  = rtc_year_days(पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year);
	पंचांग->पंचांग_isdst = 0; /* RTC has hardcoded समयzone, so करोn't use. */

	वापस 0;
पूर्ण

/**
 * ds1685_rtc_set_समय - sets the समय रेजिस्टरs.
 * @dev: poपूर्णांकer to device काष्ठाure.
 * @पंचांग: poपूर्णांकer to rtc_समय काष्ठाure.
 */
अटल पूर्णांक
ds1685_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा ds1685_priv *rtc = dev_get_drvdata(dev);
	u8 ctrlb, seconds, minutes, hours, wday, mday, month, years, century;

	/* Fetch the समय info from rtc_समय. */
	seconds = ds1685_rtc_bin2bcd(rtc, पंचांग->पंचांग_sec, RTC_SECS_BIN_MASK,
				     RTC_SECS_BCD_MASK);
	minutes = ds1685_rtc_bin2bcd(rtc, पंचांग->पंचांग_min, RTC_MINS_BIN_MASK,
				     RTC_MINS_BCD_MASK);
	hours   = ds1685_rtc_bin2bcd(rtc, पंचांग->पंचांग_hour, RTC_HRS_24_BIN_MASK,
				     RTC_HRS_24_BCD_MASK);
	wday    = ds1685_rtc_bin2bcd(rtc, (पंचांग->पंचांग_wday + 1), RTC_WDAY_MASK,
				     RTC_WDAY_MASK);
	mday    = ds1685_rtc_bin2bcd(rtc, पंचांग->पंचांग_mday, RTC_MDAY_BIN_MASK,
				     RTC_MDAY_BCD_MASK);
	month   = ds1685_rtc_bin2bcd(rtc, (पंचांग->पंचांग_mon + 1), RTC_MONTH_BIN_MASK,
				     RTC_MONTH_BCD_MASK);
	years   = ds1685_rtc_bin2bcd(rtc, (पंचांग->पंचांग_year % 100),
				     RTC_YEAR_BIN_MASK, RTC_YEAR_BCD_MASK);
	century = ds1685_rtc_bin2bcd(rtc, ((पंचांग->पंचांग_year + 1900) / 100),
				     RTC_CENTURY_MASK, RTC_CENTURY_MASK);

	/*
	 * Perक्रमm Sanity Checks:
	 *   - Months: !> 12, Month Day != 0.
	 *   - Month Day !> Max days in current month.
	 *   - Hours !>= 24, Mins !>= 60, Secs !>= 60, & Weekday !> 7.
	 */
	अगर ((पंचांग->पंचांग_mon > 11) || (mday == 0))
		वापस -गलत_तर्क;

	अगर (पंचांग->पंचांग_mday > rtc_month_days(पंचांग->पंचांग_mon, पंचांग->पंचांग_year))
		वापस -गलत_तर्क;

	अगर ((पंचांग->पंचांग_hour >= 24) || (पंचांग->पंचांग_min >= 60) ||
	    (पंचांग->पंचांग_sec >= 60)  || (wday > 7))
		वापस -गलत_तर्क;

	/*
	 * Set the data mode to use and store the समय values in the
	 * RTC रेजिस्टरs.
	 */
	ds1685_rtc_begin_data_access(rtc);
	ctrlb = rtc->पढ़ो(rtc, RTC_CTRL_B);
	अगर (rtc->bcd_mode)
		ctrlb &= ~(RTC_CTRL_B_DM);
	अन्यथा
		ctrlb |= RTC_CTRL_B_DM;
	rtc->ग_लिखो(rtc, RTC_CTRL_B, ctrlb);
	rtc->ग_लिखो(rtc, RTC_SECS, seconds);
	rtc->ग_लिखो(rtc, RTC_MINS, minutes);
	rtc->ग_लिखो(rtc, RTC_HRS, hours);
	rtc->ग_लिखो(rtc, RTC_WDAY, wday);
	rtc->ग_लिखो(rtc, RTC_MDAY, mday);
	rtc->ग_लिखो(rtc, RTC_MONTH, month);
	rtc->ग_लिखो(rtc, RTC_YEAR, years);
	rtc->ग_लिखो(rtc, RTC_CENTURY, century);
	ds1685_rtc_end_data_access(rtc);

	वापस 0;
पूर्ण

/**
 * ds1685_rtc_पढ़ो_alarm - पढ़ोs the alarm रेजिस्टरs.
 * @dev: poपूर्णांकer to device काष्ठाure.
 * @alrm: poपूर्णांकer to rtc_wkalrm काष्ठाure.
 *
 * There are three primary alarm रेजिस्टरs: seconds, minutes, and hours.
 * A fourth alarm रेजिस्टर क्रम the month date is also available in bank1 क्रम
 * kickstart/wakeup features.  The DS1685/DS1687 manual states that a
 * "don't care" value ranging from 0xc0 to 0xff may be written पूर्णांकo one or
 * more of the three alarm bytes to act as a wildcard value.  The fourth
 * byte करोesn't support a "don't care" value.
 */
अटल पूर्णांक
ds1685_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा ds1685_priv *rtc = dev_get_drvdata(dev);
	u8 seconds, minutes, hours, mday, ctrlb, ctrlc;
	पूर्णांक ret;

	/* Fetch the alarm info from the RTC alarm रेजिस्टरs. */
	ds1685_rtc_begin_data_access(rtc);
	seconds	= rtc->पढ़ो(rtc, RTC_SECS_ALARM);
	minutes	= rtc->पढ़ो(rtc, RTC_MINS_ALARM);
	hours	= rtc->पढ़ो(rtc, RTC_HRS_ALARM);
	mday	= rtc->पढ़ो(rtc, RTC_MDAY_ALARM);
	ctrlb	= rtc->पढ़ो(rtc, RTC_CTRL_B);
	ctrlc	= rtc->पढ़ो(rtc, RTC_CTRL_C);
	ds1685_rtc_end_data_access(rtc);

	/* Check the month date क्रम validity. */
	ret = ds1685_rtc_check_mday(rtc, mday);
	अगर (ret)
		वापस ret;

	/*
	 * Check the three alarm bytes.
	 *
	 * The Linux RTC प्रणाली करोesn't support the "don't care" capability
	 * of this RTC chip.  We check क्रम it anyways in हाल support is
	 * added in the future and only assign when we care.
	 */
	अगर (likely(seconds < 0xc0))
		alrm->समय.पंचांग_sec = ds1685_rtc_bcd2bin(rtc, seconds,
						       RTC_SECS_BCD_MASK,
						       RTC_SECS_BIN_MASK);

	अगर (likely(minutes < 0xc0))
		alrm->समय.पंचांग_min = ds1685_rtc_bcd2bin(rtc, minutes,
						       RTC_MINS_BCD_MASK,
						       RTC_MINS_BIN_MASK);

	अगर (likely(hours < 0xc0))
		alrm->समय.पंचांग_hour = ds1685_rtc_bcd2bin(rtc, hours,
							RTC_HRS_24_BCD_MASK,
							RTC_HRS_24_BIN_MASK);

	/* Write the data to rtc_wkalrm. */
	alrm->समय.पंचांग_mday = ds1685_rtc_bcd2bin(rtc, mday, RTC_MDAY_BCD_MASK,
						RTC_MDAY_BIN_MASK);
	alrm->enabled = !!(ctrlb & RTC_CTRL_B_AIE);
	alrm->pending = !!(ctrlc & RTC_CTRL_C_AF);

	वापस 0;
पूर्ण

/**
 * ds1685_rtc_set_alarm - sets the alarm in रेजिस्टरs.
 * @dev: poपूर्णांकer to device काष्ठाure.
 * @alrm: poपूर्णांकer to rtc_wkalrm काष्ठाure.
 */
अटल पूर्णांक
ds1685_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा ds1685_priv *rtc = dev_get_drvdata(dev);
	u8 ctrlb, seconds, minutes, hours, mday;
	पूर्णांक ret;

	/* Fetch the alarm info and convert to BCD. */
	seconds	= ds1685_rtc_bin2bcd(rtc, alrm->समय.पंचांग_sec,
				     RTC_SECS_BIN_MASK,
				     RTC_SECS_BCD_MASK);
	minutes	= ds1685_rtc_bin2bcd(rtc, alrm->समय.पंचांग_min,
				     RTC_MINS_BIN_MASK,
				     RTC_MINS_BCD_MASK);
	hours	= ds1685_rtc_bin2bcd(rtc, alrm->समय.पंचांग_hour,
				     RTC_HRS_24_BIN_MASK,
				     RTC_HRS_24_BCD_MASK);
	mday	= ds1685_rtc_bin2bcd(rtc, alrm->समय.पंचांग_mday,
				     RTC_MDAY_BIN_MASK,
				     RTC_MDAY_BCD_MASK);

	/* Check the month date क्रम validity. */
	ret = ds1685_rtc_check_mday(rtc, mday);
	अगर (ret)
		वापस ret;

	/*
	 * Check the three alarm bytes.
	 *
	 * The Linux RTC प्रणाली करोesn't support the "don't care" capability
	 * of this RTC chip because rtc_valid_पंचांग tries to validate every
	 * field, and we only support four fields.  We put the support
	 * here anyways क्रम the future.
	 */
	अगर (unlikely(seconds >= 0xc0))
		seconds = 0xff;

	अगर (unlikely(minutes >= 0xc0))
		minutes = 0xff;

	अगर (unlikely(hours >= 0xc0))
		hours = 0xff;

	alrm->समय.पंचांग_mon	= -1;
	alrm->समय.पंचांग_year	= -1;
	alrm->समय.पंचांग_wday	= -1;
	alrm->समय.पंचांग_yday	= -1;
	alrm->समय.पंचांग_isdst	= -1;

	/* Disable the alarm पूर्णांकerrupt first. */
	ds1685_rtc_begin_data_access(rtc);
	ctrlb = rtc->पढ़ो(rtc, RTC_CTRL_B);
	rtc->ग_लिखो(rtc, RTC_CTRL_B, (ctrlb & ~(RTC_CTRL_B_AIE)));

	/* Read ctrlc to clear RTC_CTRL_C_AF. */
	rtc->पढ़ो(rtc, RTC_CTRL_C);

	/*
	 * Set the data mode to use and store the समय values in the
	 * RTC रेजिस्टरs.
	 */
	ctrlb = rtc->पढ़ो(rtc, RTC_CTRL_B);
	अगर (rtc->bcd_mode)
		ctrlb &= ~(RTC_CTRL_B_DM);
	अन्यथा
		ctrlb |= RTC_CTRL_B_DM;
	rtc->ग_लिखो(rtc, RTC_CTRL_B, ctrlb);
	rtc->ग_लिखो(rtc, RTC_SECS_ALARM, seconds);
	rtc->ग_लिखो(rtc, RTC_MINS_ALARM, minutes);
	rtc->ग_लिखो(rtc, RTC_HRS_ALARM, hours);
	rtc->ग_लिखो(rtc, RTC_MDAY_ALARM, mday);

	/* Re-enable the alarm अगर needed. */
	अगर (alrm->enabled) अणु
		ctrlb = rtc->पढ़ो(rtc, RTC_CTRL_B);
		ctrlb |= RTC_CTRL_B_AIE;
		rtc->ग_लिखो(rtc, RTC_CTRL_B, ctrlb);
	पूर्ण

	/* Done! */
	ds1685_rtc_end_data_access(rtc);

	वापस 0;
पूर्ण
/* ----------------------------------------------------------------------- */


/* ----------------------------------------------------------------------- */
/* /dev/rtcX Interface functions */

/**
 * ds1685_rtc_alarm_irq_enable - replaces ioctl() RTC_AIE on/off.
 * @dev: poपूर्णांकer to device काष्ठाure.
 * @enabled: flag indicating whether to enable or disable.
 */
अटल पूर्णांक
ds1685_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा ds1685_priv *rtc = dev_get_drvdata(dev);

	/* Flip the requisite पूर्णांकerrupt-enable bit. */
	अगर (enabled)
		rtc->ग_लिखो(rtc, RTC_CTRL_B, (rtc->पढ़ो(rtc, RTC_CTRL_B) |
					     RTC_CTRL_B_AIE));
	अन्यथा
		rtc->ग_लिखो(rtc, RTC_CTRL_B, (rtc->पढ़ो(rtc, RTC_CTRL_B) &
					     ~(RTC_CTRL_B_AIE)));

	/* Read Control C to clear all the flag bits. */
	rtc->पढ़ो(rtc, RTC_CTRL_C);

	वापस 0;
पूर्ण
/* ----------------------------------------------------------------------- */


/* ----------------------------------------------------------------------- */
/* IRQ handler */

/**
 * ds1685_rtc_extended_irq - take care of extended पूर्णांकerrupts
 * @rtc: poपूर्णांकer to the ds1685 rtc काष्ठाure.
 * @pdev: platक्रमm device poपूर्णांकer.
 */
अटल व्योम
ds1685_rtc_extended_irq(काष्ठा ds1685_priv *rtc, काष्ठा platक्रमm_device *pdev)
अणु
	u8 ctrl4a, ctrl4b;

	ds1685_rtc_चयन_to_bank1(rtc);
	ctrl4a = rtc->पढ़ो(rtc, RTC_EXT_CTRL_4A);
	ctrl4b = rtc->पढ़ो(rtc, RTC_EXT_CTRL_4B);

	/*
	 * Check क्रम a kickstart पूर्णांकerrupt. With Vcc applied, this
	 * typically means that the घातer button was pressed, so we
	 * begin the shutकरोwn sequence.
	 */
	अगर ((ctrl4b & RTC_CTRL_4B_KSE) && (ctrl4a & RTC_CTRL_4A_KF)) अणु
		/* Briefly disable kickstarts to debounce button presses. */
		rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4B,
			   (rtc->पढ़ो(rtc, RTC_EXT_CTRL_4B) &
			    ~(RTC_CTRL_4B_KSE)));

		/* Clear the kickstart flag. */
		rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4A,
			   (ctrl4a & ~(RTC_CTRL_4A_KF)));


		/*
		 * Sleep 500ms beक्रमe re-enabling kickstarts.  This allows
		 * adequate समय to aव्योम पढ़ोing संकेत jitter as additional
		 * button presses.
		 */
		msleep(500);
		rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4B,
			   (rtc->पढ़ो(rtc, RTC_EXT_CTRL_4B) |
			    RTC_CTRL_4B_KSE));

		/* Call the platक्रमm pre-घातeroff function. Else, shutकरोwn. */
		अगर (rtc->prepare_घातeroff != शून्य)
			rtc->prepare_घातeroff();
		अन्यथा
			ds1685_rtc_घातeroff(pdev);
	पूर्ण

	/*
	 * Check क्रम a wake-up पूर्णांकerrupt.  With Vcc applied, this is
	 * essentially a second alarm पूर्णांकerrupt, except it takes पूर्णांकo
	 * account the 'date' रेजिस्टर in bank1 in addition to the
	 * standard three alarm रेजिस्टरs.
	 */
	अगर ((ctrl4b & RTC_CTRL_4B_WIE) && (ctrl4a & RTC_CTRL_4A_WF)) अणु
		rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4A,
			   (ctrl4a & ~(RTC_CTRL_4A_WF)));

		/* Call the platक्रमm wake_alarm function अगर defined. */
		अगर (rtc->wake_alarm != शून्य)
			rtc->wake_alarm();
		अन्यथा
			dev_warn(&pdev->dev,
				 "Wake Alarm IRQ just occurred!\n");
	पूर्ण

	/*
	 * Check क्रम a ram-clear पूर्णांकerrupt.  This happens अगर RIE=1 and RF=0
	 * when RCE=1 in 4B.  This clears all NVRAM bytes in bank0 by setting
	 * each byte to a logic 1.  This has no effect on any extended
	 * NV-SRAM that might be present, nor on the समय/calendar/alarm
	 * रेजिस्टरs.  After a ram-clear is completed, there is a minimum
	 * recovery समय of ~150ms in which all पढ़ोs/ग_लिखोs are locked out.
	 * NOTE: A ram-clear can still occur अगर RCE=1 and RIE=0.  We cannot
	 * catch this scenario.
	 */
	अगर ((ctrl4b & RTC_CTRL_4B_RIE) && (ctrl4a & RTC_CTRL_4A_RF)) अणु
		rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4A,
			   (ctrl4a & ~(RTC_CTRL_4A_RF)));
		msleep(150);

		/* Call the platक्रमm post_ram_clear function अगर defined. */
		अगर (rtc->post_ram_clear != शून्य)
			rtc->post_ram_clear();
		अन्यथा
			dev_warn(&pdev->dev,
				 "RAM-Clear IRQ just occurred!\n");
	पूर्ण
	ds1685_rtc_चयन_to_bank0(rtc);
पूर्ण

/**
 * ds1685_rtc_irq_handler - IRQ handler.
 * @irq: IRQ number.
 * @dev_id: platक्रमm device poपूर्णांकer.
 */
अटल irqवापस_t
ds1685_rtc_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *pdev = dev_id;
	काष्ठा ds1685_priv *rtc = platक्रमm_get_drvdata(pdev);
	u8 ctrlb, ctrlc;
	अचिन्हित दीर्घ events = 0;
	u8 num_irqs = 0;

	/* Abort early अगर the device isn't पढ़ोy yet (i.e., DEBUG_SHIRQ). */
	अगर (unlikely(!rtc))
		वापस IRQ_HANDLED;

	rtc_lock(rtc->dev);

	/* Ctrlb holds the पूर्णांकerrupt-enable bits and ctrlc the flag bits. */
	ctrlb = rtc->पढ़ो(rtc, RTC_CTRL_B);
	ctrlc = rtc->पढ़ो(rtc, RTC_CTRL_C);

	/* Is the IRQF bit set? */
	अगर (likely(ctrlc & RTC_CTRL_C_IRQF)) अणु
		/*
		 * We need to determine अगर it was one of the standard
		 * events: PF, AF, or UF.  If so, we handle them and
		 * update the RTC core.
		 */
		अगर (likely(ctrlc & RTC_CTRL_B_PAU_MASK)) अणु
			events = RTC_IRQF;

			/* Check क्रम a periodic पूर्णांकerrupt. */
			अगर ((ctrlb & RTC_CTRL_B_PIE) &&
			    (ctrlc & RTC_CTRL_C_PF)) अणु
				events |= RTC_PF;
				num_irqs++;
			पूर्ण

			/* Check क्रम an alarm पूर्णांकerrupt. */
			अगर ((ctrlb & RTC_CTRL_B_AIE) &&
			    (ctrlc & RTC_CTRL_C_AF)) अणु
				events |= RTC_AF;
				num_irqs++;
			पूर्ण

			/* Check क्रम an update पूर्णांकerrupt. */
			अगर ((ctrlb & RTC_CTRL_B_UIE) &&
			    (ctrlc & RTC_CTRL_C_UF)) अणु
				events |= RTC_UF;
				num_irqs++;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * One of the "extended" पूर्णांकerrupts was received that
			 * is not recognized by the RTC core.
			 */
			ds1685_rtc_extended_irq(rtc, pdev);
		पूर्ण
	पूर्ण
	rtc_update_irq(rtc->dev, num_irqs, events);
	rtc_unlock(rtc->dev);

	वापस events ? IRQ_HANDLED : IRQ_NONE;
पूर्ण
/* ----------------------------------------------------------------------- */


/* ----------------------------------------------------------------------- */
/* ProcFS पूर्णांकerface */

#अगर_घोषित CONFIG_PROC_FS
#घोषणा NUM_REGS	6	/* Num of control रेजिस्टरs. */
#घोषणा NUM_BITS	8	/* Num bits per रेजिस्टर. */
#घोषणा NUM_SPACES	4	/* Num spaces between each bit. */

/*
 * Periodic Interrupt Rates.
 */
अटल स्थिर अक्षर *ds1685_rtc_pirq_rate[16] = अणु
	"none", "3.90625ms", "7.8125ms", "0.122070ms", "0.244141ms",
	"0.488281ms", "0.9765625ms", "1.953125ms", "3.90625ms", "7.8125ms",
	"15.625ms", "31.25ms", "62.5ms", "125ms", "250ms", "500ms"
पूर्ण;

/*
 * Square-Wave Output Frequencies.
 */
अटल स्थिर अक्षर *ds1685_rtc_sqw_freq[16] = अणु
	"none", "256Hz", "128Hz", "8192Hz", "4096Hz", "2048Hz", "1024Hz",
	"512Hz", "256Hz", "128Hz", "64Hz", "32Hz", "16Hz", "8Hz", "4Hz", "2Hz"
पूर्ण;

/**
 * ds1685_rtc_proc - procfs access function.
 * @dev: poपूर्णांकer to device काष्ठाure.
 * @seq: poपूर्णांकer to seq_file काष्ठाure.
 */
अटल पूर्णांक
ds1685_rtc_proc(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	काष्ठा ds1685_priv *rtc = dev_get_drvdata(dev);
	u8 ctrla, ctrlb, ctrld, ctrl4a, ctrl4b, ssn[8];
	अक्षर *model;

	/* Read all the relevant data from the control रेजिस्टरs. */
	ds1685_rtc_चयन_to_bank1(rtc);
	ds1685_rtc_get_ssn(rtc, ssn);
	ctrla = rtc->पढ़ो(rtc, RTC_CTRL_A);
	ctrlb = rtc->पढ़ो(rtc, RTC_CTRL_B);
	ctrld = rtc->पढ़ो(rtc, RTC_CTRL_D);
	ctrl4a = rtc->पढ़ो(rtc, RTC_EXT_CTRL_4A);
	ctrl4b = rtc->पढ़ो(rtc, RTC_EXT_CTRL_4B);
	ds1685_rtc_चयन_to_bank0(rtc);

	/* Determine the RTC model. */
	चयन (ssn[0]) अणु
	हाल RTC_MODEL_DS1685:
		model = "DS1685/DS1687\0";
		अवरोध;
	हाल RTC_MODEL_DS1689:
		model = "DS1689/DS1693\0";
		अवरोध;
	हाल RTC_MODEL_DS17285:
		model = "DS17285/DS17287\0";
		अवरोध;
	हाल RTC_MODEL_DS17485:
		model = "DS17485/DS17487\0";
		अवरोध;
	हाल RTC_MODEL_DS17885:
		model = "DS17885/DS17887\0";
		अवरोध;
	शेष:
		model = "Unknown\0";
		अवरोध;
	पूर्ण

	/* Prपूर्णांक out the inक्रमmation. */
	seq_म_लिखो(seq,
	   "Model\t\t: %s\n"
	   "Oscillator\t: %s\n"
	   "12/24hr\t\t: %s\n"
	   "DST\t\t: %s\n"
	   "Data mode\t: %s\n"
	   "Battery\t\t: %s\n"
	   "Aux batt\t: %s\n"
	   "Update IRQ\t: %s\n"
	   "Periodic IRQ\t: %s\n"
	   "Periodic Rate\t: %s\n"
	   "SQW Freq\t: %s\n"
	   "Serial #\t: %8phC\n",
	   model,
	   ((ctrla & RTC_CTRL_A_DV1) ? "enabled" : "disabled"),
	   ((ctrlb & RTC_CTRL_B_2412) ? "24-hour" : "12-hour"),
	   ((ctrlb & RTC_CTRL_B_DSE) ? "enabled" : "disabled"),
	   ((ctrlb & RTC_CTRL_B_DM) ? "binary" : "BCD"),
	   ((ctrld & RTC_CTRL_D_VRT) ? "ok" : "exhausted or n/a"),
	   ((ctrl4a & RTC_CTRL_4A_VRT2) ? "ok" : "exhausted or n/a"),
	   ((ctrlb & RTC_CTRL_B_UIE) ? "yes" : "no"),
	   ((ctrlb & RTC_CTRL_B_PIE) ? "yes" : "no"),
	   (!(ctrl4b & RTC_CTRL_4B_E32K) ?
	    ds1685_rtc_pirq_rate[(ctrla & RTC_CTRL_A_RS_MASK)] : "none"),
	   (!((ctrl4b & RTC_CTRL_4B_E32K)) ?
	    ds1685_rtc_sqw_freq[(ctrla & RTC_CTRL_A_RS_MASK)] : "32768Hz"),
	   ssn);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ds1685_rtc_proc शून्य
#पूर्ण_अगर /* CONFIG_PROC_FS */
/* ----------------------------------------------------------------------- */


/* ----------------------------------------------------------------------- */
/* RTC Class operations */

अटल स्थिर काष्ठा rtc_class_ops
ds1685_rtc_ops = अणु
	.proc = ds1685_rtc_proc,
	.पढ़ो_समय = ds1685_rtc_पढ़ो_समय,
	.set_समय = ds1685_rtc_set_समय,
	.पढ़ो_alarm = ds1685_rtc_पढ़ो_alarm,
	.set_alarm = ds1685_rtc_set_alarm,
	.alarm_irq_enable = ds1685_rtc_alarm_irq_enable,
पूर्ण;
/* ----------------------------------------------------------------------- */

अटल पूर्णांक ds1685_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक pos, व्योम *val,
			     माप_प्रकार size)
अणु
	काष्ठा ds1685_priv *rtc = priv;
	काष्ठा mutex *rtc_mutex = &rtc->dev->ops_lock;
	sमाप_प्रकार count;
	u8 *buf = val;
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(rtc_mutex);
	अगर (err)
		वापस err;

	ds1685_rtc_चयन_to_bank0(rtc);

	/* Read NVRAM in समय and bank0 रेजिस्टरs. */
	क्रम (count = 0; size > 0 && pos < NVRAM_TOTAL_SZ_BANK0;
	     count++, size--) अणु
		अगर (count < NVRAM_SZ_TIME)
			*buf++ = rtc->पढ़ो(rtc, (NVRAM_TIME_BASE + pos++));
		अन्यथा
			*buf++ = rtc->पढ़ो(rtc, (NVRAM_BANK0_BASE + pos++));
	पूर्ण

#अगर_अघोषित CONFIG_RTC_DRV_DS1689
	अगर (size > 0) अणु
		ds1685_rtc_चयन_to_bank1(rtc);

#अगर_अघोषित CONFIG_RTC_DRV_DS1685
		/* Enable burst-mode on DS17x85/DS17x87 */
		rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4A,
			   (rtc->पढ़ो(rtc, RTC_EXT_CTRL_4A) |
			    RTC_CTRL_4A_BME));

		/* We need one ग_लिखो to RTC_BANK1_RAM_ADDR_LSB to start
		 * पढ़ोing with burst-mode */
		rtc->ग_लिखो(rtc, RTC_BANK1_RAM_ADDR_LSB,
			   (pos - NVRAM_TOTAL_SZ_BANK0));
#पूर्ण_अगर

		/* Read NVRAM in bank1 रेजिस्टरs. */
		क्रम (count = 0; size > 0 && pos < NVRAM_TOTAL_SZ;
		     count++, size--) अणु
#अगर_घोषित CONFIG_RTC_DRV_DS1685
			/* DS1685/DS1687 has to ग_लिखो to RTC_BANK1_RAM_ADDR
			 * beक्रमe each पढ़ो. */
			rtc->ग_लिखो(rtc, RTC_BANK1_RAM_ADDR,
				   (pos - NVRAM_TOTAL_SZ_BANK0));
#पूर्ण_अगर
			*buf++ = rtc->पढ़ो(rtc, RTC_BANK1_RAM_DATA_PORT);
			pos++;
		पूर्ण

#अगर_अघोषित CONFIG_RTC_DRV_DS1685
		/* Disable burst-mode on DS17x85/DS17x87 */
		rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4A,
			   (rtc->पढ़ो(rtc, RTC_EXT_CTRL_4A) &
			    ~(RTC_CTRL_4A_BME)));
#पूर्ण_अगर
		ds1685_rtc_चयन_to_bank0(rtc);
	पूर्ण
#पूर्ण_अगर /* !CONFIG_RTC_DRV_DS1689 */
	mutex_unlock(rtc_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ds1685_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक pos, व्योम *val,
			      माप_प्रकार size)
अणु
	काष्ठा ds1685_priv *rtc = priv;
	काष्ठा mutex *rtc_mutex = &rtc->dev->ops_lock;
	sमाप_प्रकार count;
	u8 *buf = val;
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(rtc_mutex);
	अगर (err)
		वापस err;

	ds1685_rtc_चयन_to_bank0(rtc);

	/* Write NVRAM in समय and bank0 रेजिस्टरs. */
	क्रम (count = 0; size > 0 && pos < NVRAM_TOTAL_SZ_BANK0;
	     count++, size--)
		अगर (count < NVRAM_SZ_TIME)
			rtc->ग_लिखो(rtc, (NVRAM_TIME_BASE + pos++),
				   *buf++);
		अन्यथा
			rtc->ग_लिखो(rtc, (NVRAM_BANK0_BASE), *buf++);

#अगर_अघोषित CONFIG_RTC_DRV_DS1689
	अगर (size > 0) अणु
		ds1685_rtc_चयन_to_bank1(rtc);

#अगर_अघोषित CONFIG_RTC_DRV_DS1685
		/* Enable burst-mode on DS17x85/DS17x87 */
		rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4A,
			   (rtc->पढ़ो(rtc, RTC_EXT_CTRL_4A) |
			    RTC_CTRL_4A_BME));

		/* We need one ग_लिखो to RTC_BANK1_RAM_ADDR_LSB to start
		 * writing with burst-mode */
		rtc->ग_लिखो(rtc, RTC_BANK1_RAM_ADDR_LSB,
			   (pos - NVRAM_TOTAL_SZ_BANK0));
#पूर्ण_अगर

		/* Write NVRAM in bank1 रेजिस्टरs. */
		क्रम (count = 0; size > 0 && pos < NVRAM_TOTAL_SZ;
		     count++, size--) अणु
#अगर_घोषित CONFIG_RTC_DRV_DS1685
			/* DS1685/DS1687 has to ग_लिखो to RTC_BANK1_RAM_ADDR
			 * beक्रमe each पढ़ो. */
			rtc->ग_लिखो(rtc, RTC_BANK1_RAM_ADDR,
				   (pos - NVRAM_TOTAL_SZ_BANK0));
#पूर्ण_अगर
			rtc->ग_लिखो(rtc, RTC_BANK1_RAM_DATA_PORT, *buf++);
			pos++;
		पूर्ण

#अगर_अघोषित CONFIG_RTC_DRV_DS1685
		/* Disable burst-mode on DS17x85/DS17x87 */
		rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4A,
			   (rtc->पढ़ो(rtc, RTC_EXT_CTRL_4A) &
			    ~(RTC_CTRL_4A_BME)));
#पूर्ण_अगर
		ds1685_rtc_चयन_to_bank0(rtc);
	पूर्ण
#पूर्ण_अगर /* !CONFIG_RTC_DRV_DS1689 */
	mutex_unlock(rtc_mutex);

	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */
/* SysFS पूर्णांकerface */

/**
 * ds1685_rtc_sysfs_battery_show - sysfs file क्रम मुख्य battery status.
 * @dev: poपूर्णांकer to device काष्ठाure.
 * @attr: poपूर्णांकer to device_attribute काष्ठाure.
 * @buf: poपूर्णांकer to अक्षर array to hold the output.
 */
अटल sमाप_प्रकार
ds1685_rtc_sysfs_battery_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ds1685_priv *rtc = dev_get_drvdata(dev->parent);
	u8 ctrld;

	ctrld = rtc->पढ़ो(rtc, RTC_CTRL_D);

	वापस प्र_लिखो(buf, "%s\n",
			(ctrld & RTC_CTRL_D_VRT) ? "ok" : "not ok or N/A");
पूर्ण
अटल DEVICE_ATTR(battery, S_IRUGO, ds1685_rtc_sysfs_battery_show, शून्य);

/**
 * ds1685_rtc_sysfs_auxbatt_show - sysfs file क्रम aux battery status.
 * @dev: poपूर्णांकer to device काष्ठाure.
 * @attr: poपूर्णांकer to device_attribute काष्ठाure.
 * @buf: poपूर्णांकer to अक्षर array to hold the output.
 */
अटल sमाप_प्रकार
ds1685_rtc_sysfs_auxbatt_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ds1685_priv *rtc = dev_get_drvdata(dev->parent);
	u8 ctrl4a;

	ds1685_rtc_चयन_to_bank1(rtc);
	ctrl4a = rtc->पढ़ो(rtc, RTC_EXT_CTRL_4A);
	ds1685_rtc_चयन_to_bank0(rtc);

	वापस प्र_लिखो(buf, "%s\n",
			(ctrl4a & RTC_CTRL_4A_VRT2) ? "ok" : "not ok or N/A");
पूर्ण
अटल DEVICE_ATTR(auxbatt, S_IRUGO, ds1685_rtc_sysfs_auxbatt_show, शून्य);

/**
 * ds1685_rtc_sysfs_serial_show - sysfs file क्रम silicon serial number.
 * @dev: poपूर्णांकer to device काष्ठाure.
 * @attr: poपूर्णांकer to device_attribute काष्ठाure.
 * @buf: poपूर्णांकer to अक्षर array to hold the output.
 */
अटल sमाप_प्रकार
ds1685_rtc_sysfs_serial_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ds1685_priv *rtc = dev_get_drvdata(dev->parent);
	u8 ssn[8];

	ds1685_rtc_चयन_to_bank1(rtc);
	ds1685_rtc_get_ssn(rtc, ssn);
	ds1685_rtc_चयन_to_bank0(rtc);

	वापस प्र_लिखो(buf, "%8phC\n", ssn);
पूर्ण
अटल DEVICE_ATTR(serial, S_IRUGO, ds1685_rtc_sysfs_serial_show, शून्य);

/*
 * काष्ठा ds1685_rtc_sysfs_misc_attrs - list क्रम misc RTC features.
 */
अटल काष्ठा attribute*
ds1685_rtc_sysfs_misc_attrs[] = अणु
	&dev_attr_battery.attr,
	&dev_attr_auxbatt.attr,
	&dev_attr_serial.attr,
	शून्य,
पूर्ण;

/*
 * काष्ठा ds1685_rtc_sysfs_misc_grp - attr group क्रम misc RTC features.
 */
अटल स्थिर काष्ठा attribute_group
ds1685_rtc_sysfs_misc_grp = अणु
	.name = "misc",
	.attrs = ds1685_rtc_sysfs_misc_attrs,
पूर्ण;

/* ----------------------------------------------------------------------- */
/* Driver Probe/Removal */

/**
 * ds1685_rtc_probe - initializes rtc driver.
 * @pdev: poपूर्णांकer to platक्रमm_device काष्ठाure.
 */
अटल पूर्णांक
ds1685_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_device *rtc_dev;
	काष्ठा ds1685_priv *rtc;
	काष्ठा ds1685_rtc_platक्रमm_data *pdata;
	u8 ctrla, ctrlb, hours;
	अचिन्हित अक्षर am_pm;
	पूर्णांक ret = 0;
	काष्ठा nvmem_config nvmem_cfg = अणु
		.name = "ds1685_nvram",
		.size = NVRAM_TOTAL_SZ,
		.reg_पढ़ो = ds1685_nvram_पढ़ो,
		.reg_ग_लिखो = ds1685_nvram_ग_लिखो,
	पूर्ण;

	/* Get the platक्रमm data. */
	pdata = (काष्ठा ds1685_rtc_platक्रमm_data *) pdev->dev.platक्रमm_data;
	अगर (!pdata)
		वापस -ENODEV;

	/* Allocate memory क्रम the rtc device. */
	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	/* Setup resources and access functions */
	चयन (pdata->access_type) अणु
	हाल ds1685_reg_direct:
		rtc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
		अगर (IS_ERR(rtc->regs))
			वापस PTR_ERR(rtc->regs);
		rtc->पढ़ो = ds1685_पढ़ो;
		rtc->ग_लिखो = ds1685_ग_लिखो;
		अवरोध;
	हाल ds1685_reg_indirect:
		rtc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
		अगर (IS_ERR(rtc->regs))
			वापस PTR_ERR(rtc->regs);
		rtc->data = devm_platक्रमm_ioremap_resource(pdev, 1);
		अगर (IS_ERR(rtc->data))
			वापस PTR_ERR(rtc->data);
		rtc->पढ़ो = ds1685_indirect_पढ़ो;
		rtc->ग_लिखो = ds1685_indirect_ग_लिखो;
		अवरोध;
	पूर्ण

	अगर (!rtc->पढ़ो || !rtc->ग_लिखो)
		वापस -ENXIO;

	/* Get the रेजिस्टर step size. */
	अगर (pdata->regstep > 0)
		rtc->regstep = pdata->regstep;
	अन्यथा
		rtc->regstep = 1;

	/* Platक्रमm pre-shutकरोwn function, अगर defined. */
	अगर (pdata->plat_prepare_घातeroff)
		rtc->prepare_घातeroff = pdata->plat_prepare_घातeroff;

	/* Platक्रमm wake_alarm function, अगर defined. */
	अगर (pdata->plat_wake_alarm)
		rtc->wake_alarm = pdata->plat_wake_alarm;

	/* Platक्रमm post_ram_clear function, अगर defined. */
	अगर (pdata->plat_post_ram_clear)
		rtc->post_ram_clear = pdata->plat_post_ram_clear;

	/* set the driver data. */
	platक्रमm_set_drvdata(pdev, rtc);

	/* Turn the oscillator on अगर is not alपढ़ोy on (DV1 = 1). */
	ctrla = rtc->पढ़ो(rtc, RTC_CTRL_A);
	अगर (!(ctrla & RTC_CTRL_A_DV1))
		ctrla |= RTC_CTRL_A_DV1;

	/* Enable the countकरोwn chain (DV2 = 0) */
	ctrla &= ~(RTC_CTRL_A_DV2);

	/* Clear RS3-RS0 in Control A. */
	ctrla &= ~(RTC_CTRL_A_RS_MASK);

	/*
	 * All करोne with Control A.  Switch to Bank 1 क्रम the reमुख्यder of
	 * the RTC setup so we have access to the extended functions.
	 */
	ctrla |= RTC_CTRL_A_DV0;
	rtc->ग_लिखो(rtc, RTC_CTRL_A, ctrla);

	/* Default to 32768kHz output. */
	rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4B,
		   (rtc->पढ़ो(rtc, RTC_EXT_CTRL_4B) | RTC_CTRL_4B_E32K));

	/* Set the SET bit in Control B so we can करो some housekeeping. */
	rtc->ग_लिखो(rtc, RTC_CTRL_B,
		   (rtc->पढ़ो(rtc, RTC_CTRL_B) | RTC_CTRL_B_SET));

	/* Read Ext Ctrl 4A and check the INCR bit to aव्योम a lockout. */
	जबतक (rtc->पढ़ो(rtc, RTC_EXT_CTRL_4A) & RTC_CTRL_4A_INCR)
		cpu_relax();

	/*
	 * If the platक्रमm supports BCD mode, then set DM=0 in Control B.
	 * Otherwise, set DM=1 क्रम BIN mode.
	 */
	ctrlb = rtc->पढ़ो(rtc, RTC_CTRL_B);
	अगर (pdata->bcd_mode)
		ctrlb &= ~(RTC_CTRL_B_DM);
	अन्यथा
		ctrlb |= RTC_CTRL_B_DM;
	rtc->bcd_mode = pdata->bcd_mode;

	/*
	 * Disable Daylight Savings Time (DSE = 0).
	 * The RTC has hardcoded समयzone inक्रमmation that is rendered
	 * obselete.  We'll let the OS deal with DST settings instead.
	 */
	अगर (ctrlb & RTC_CTRL_B_DSE)
		ctrlb &= ~(RTC_CTRL_B_DSE);

	/* Force 24-hour mode (2412 = 1). */
	अगर (!(ctrlb & RTC_CTRL_B_2412)) अणु
		/* Reinitialize the समय hours. */
		hours = rtc->पढ़ो(rtc, RTC_HRS);
		am_pm = hours & RTC_HRS_AMPM_MASK;
		hours = ds1685_rtc_bcd2bin(rtc, hours, RTC_HRS_12_BCD_MASK,
					   RTC_HRS_12_BIN_MASK);
		hours = ((hours == 12) ? 0 : ((am_pm) ? hours + 12 : hours));

		/* Enable 24-hour mode. */
		ctrlb |= RTC_CTRL_B_2412;

		/* Write back to Control B, including DM & DSE bits. */
		rtc->ग_लिखो(rtc, RTC_CTRL_B, ctrlb);

		/* Write the समय hours back. */
		rtc->ग_लिखो(rtc, RTC_HRS,
			   ds1685_rtc_bin2bcd(rtc, hours,
					      RTC_HRS_24_BIN_MASK,
					      RTC_HRS_24_BCD_MASK));

		/* Reinitialize the alarm hours. */
		hours = rtc->पढ़ो(rtc, RTC_HRS_ALARM);
		am_pm = hours & RTC_HRS_AMPM_MASK;
		hours = ds1685_rtc_bcd2bin(rtc, hours, RTC_HRS_12_BCD_MASK,
					   RTC_HRS_12_BIN_MASK);
		hours = ((hours == 12) ? 0 : ((am_pm) ? hours + 12 : hours));

		/* Write the alarm hours back. */
		rtc->ग_लिखो(rtc, RTC_HRS_ALARM,
			   ds1685_rtc_bin2bcd(rtc, hours,
					      RTC_HRS_24_BIN_MASK,
					      RTC_HRS_24_BCD_MASK));
	पूर्ण अन्यथा अणु
		/* 24-hour mode is alपढ़ोy set, so ग_लिखो Control B back. */
		rtc->ग_लिखो(rtc, RTC_CTRL_B, ctrlb);
	पूर्ण

	/* Unset the SET bit in Control B so the RTC can update. */
	rtc->ग_लिखो(rtc, RTC_CTRL_B,
		   (rtc->पढ़ो(rtc, RTC_CTRL_B) & ~(RTC_CTRL_B_SET)));

	/* Check the मुख्य battery. */
	अगर (!(rtc->पढ़ो(rtc, RTC_CTRL_D) & RTC_CTRL_D_VRT))
		dev_warn(&pdev->dev,
			 "Main battery is exhausted! RTC may be invalid!\n");

	/* Check the auxillary battery.  It is optional. */
	अगर (!(rtc->पढ़ो(rtc, RTC_EXT_CTRL_4A) & RTC_CTRL_4A_VRT2))
		dev_warn(&pdev->dev,
			 "Aux battery is exhausted or not available.\n");

	/* Read Ctrl B and clear PIE/AIE/UIE. */
	rtc->ग_लिखो(rtc, RTC_CTRL_B,
		   (rtc->पढ़ो(rtc, RTC_CTRL_B) & ~(RTC_CTRL_B_PAU_MASK)));

	/* Reading Ctrl C स्वतः-clears PF/AF/UF. */
	rtc->पढ़ो(rtc, RTC_CTRL_C);

	/* Read Ctrl 4B and clear RIE/WIE/KSE. */
	rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4B,
		   (rtc->पढ़ो(rtc, RTC_EXT_CTRL_4B) & ~(RTC_CTRL_4B_RWK_MASK)));

	/* Clear RF/WF/KF in Ctrl 4A. */
	rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4A,
		   (rtc->पढ़ो(rtc, RTC_EXT_CTRL_4A) & ~(RTC_CTRL_4A_RWK_MASK)));

	/*
	 * Re-enable KSE to handle घातer button events.  We करो not enable
	 * WIE or RIE by शेष.
	 */
	rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4B,
		   (rtc->पढ़ो(rtc, RTC_EXT_CTRL_4B) | RTC_CTRL_4B_KSE));

	rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc_dev))
		वापस PTR_ERR(rtc_dev);

	rtc_dev->ops = &ds1685_rtc_ops;

	/* Century bit is useless because leap year fails in 1900 and 2100 */
	rtc_dev->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rtc_dev->range_max = RTC_TIMESTAMP_END_2099;

	/* Maximum periodic rate is 8192Hz (0.122070ms). */
	rtc_dev->max_user_freq = RTC_MAX_USER_FREQ;

	/* See अगर the platक्रमm करोesn't support UIE. */
	अगर (pdata->uie_unsupported)
		rtc_dev->uie_unsupported = 1;

	rtc->dev = rtc_dev;

	/*
	 * Fetch the IRQ and setup the पूर्णांकerrupt handler.
	 *
	 * Not all platक्रमms have the IRQF pin tied to something.  If not, the
	 * RTC will still set the *IE / *F flags and उठाओ IRQF in ctrlc, but
	 * there won't be an स्वतःmatic way of notअगरying the kernel about it,
	 * unless ctrlc is explicitly polled.
	 */
	अगर (!pdata->no_irq) अणु
		ret = platक्रमm_get_irq(pdev, 0);
		अगर (ret <= 0)
			वापस ret;

		rtc->irq_num = ret;

		/* Request an IRQ. */
		ret = devm_request_thपढ़ोed_irq(&pdev->dev, rtc->irq_num,
				       शून्य, ds1685_rtc_irq_handler,
				       IRQF_SHARED | IRQF_ONESHOT,
				       pdev->name, pdev);

		/* Check to see अगर something came back. */
		अगर (unlikely(ret)) अणु
			dev_warn(&pdev->dev,
				 "RTC interrupt not available\n");
			rtc->irq_num = 0;
		पूर्ण
	पूर्ण
	rtc->no_irq = pdata->no_irq;

	/* Setup complete. */
	ds1685_rtc_चयन_to_bank0(rtc);

	ret = rtc_add_group(rtc_dev, &ds1685_rtc_sysfs_misc_grp);
	अगर (ret)
		वापस ret;

	nvmem_cfg.priv = rtc;
	ret = devm_rtc_nvmem_रेजिस्टर(rtc_dev, &nvmem_cfg);
	अगर (ret)
		वापस ret;

	वापस devm_rtc_रेजिस्टर_device(rtc_dev);
पूर्ण

/**
 * ds1685_rtc_हटाओ - हटाओs rtc driver.
 * @pdev: poपूर्णांकer to platक्रमm_device काष्ठाure.
 */
अटल पूर्णांक
ds1685_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ds1685_priv *rtc = platक्रमm_get_drvdata(pdev);

	/* Read Ctrl B and clear PIE/AIE/UIE. */
	rtc->ग_लिखो(rtc, RTC_CTRL_B,
		   (rtc->पढ़ो(rtc, RTC_CTRL_B) &
		    ~(RTC_CTRL_B_PAU_MASK)));

	/* Reading Ctrl C स्वतः-clears PF/AF/UF. */
	rtc->पढ़ो(rtc, RTC_CTRL_C);

	/* Read Ctrl 4B and clear RIE/WIE/KSE. */
	rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4B,
		   (rtc->पढ़ो(rtc, RTC_EXT_CTRL_4B) &
		    ~(RTC_CTRL_4B_RWK_MASK)));

	/* Manually clear RF/WF/KF in Ctrl 4A. */
	rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4A,
		   (rtc->पढ़ो(rtc, RTC_EXT_CTRL_4A) &
		    ~(RTC_CTRL_4A_RWK_MASK)));

	वापस 0;
पूर्ण

/*
 * ds1685_rtc_driver - rtc driver properties.
 */
अटल काष्ठा platक्रमm_driver ds1685_rtc_driver = अणु
	.driver		= अणु
		.name	= "rtc-ds1685",
	पूर्ण,
	.probe		= ds1685_rtc_probe,
	.हटाओ		= ds1685_rtc_हटाओ,
पूर्ण;
module_platक्रमm_driver(ds1685_rtc_driver);
/* ----------------------------------------------------------------------- */


/* ----------------------------------------------------------------------- */
/* Poweroff function */

/**
 * ds1685_rtc_घातeroff - uses the RTC chip to घातer the प्रणाली off.
 * @pdev: poपूर्णांकer to platक्रमm_device काष्ठाure.
 */
व्योम __noवापस
ds1685_rtc_घातeroff(काष्ठा platक्रमm_device *pdev)
अणु
	u8 ctrla, ctrl4a, ctrl4b;
	काष्ठा ds1685_priv *rtc;

	/* Check क्रम valid RTC data, अन्यथा, spin क्रमever. */
	अगर (unlikely(!pdev)) अणु
		pr_emerg("platform device data not available, spinning forever ...\n");
		जबतक(1);
		unreachable();
	पूर्ण अन्यथा अणु
		/* Get the rtc data. */
		rtc = platक्रमm_get_drvdata(pdev);

		/*
		 * Disable our IRQ.  We're powering down, so we're not
		 * going to worry about cleaning up.  Most of that should
		 * have been taken care of by the shutकरोwn scripts and this
		 * is the final function call.
		 */
		अगर (!rtc->no_irq)
			disable_irq_nosync(rtc->irq_num);

		/* Oscillator must be on and the countकरोwn chain enabled. */
		ctrla = rtc->पढ़ो(rtc, RTC_CTRL_A);
		ctrla |= RTC_CTRL_A_DV1;
		ctrla &= ~(RTC_CTRL_A_DV2);
		rtc->ग_लिखो(rtc, RTC_CTRL_A, ctrla);

		/*
		 * Read Control 4A and check the status of the auxillary
		 * battery.  This must be present and working (VRT2 = 1)
		 * क्रम wakeup and kickstart functionality to be useful.
		 */
		ds1685_rtc_चयन_to_bank1(rtc);
		ctrl4a = rtc->पढ़ो(rtc, RTC_EXT_CTRL_4A);
		अगर (ctrl4a & RTC_CTRL_4A_VRT2) अणु
			/* Clear all of the पूर्णांकerrupt flags on Control 4A. */
			ctrl4a &= ~(RTC_CTRL_4A_RWK_MASK);
			rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4A, ctrl4a);

			/*
			 * The auxillary battery is present and working.
			 * Enable extended functions (ABE=1), enable
			 * wake-up (WIE=1), and enable kickstart (KSE=1)
			 * in Control 4B.
			 */
			ctrl4b = rtc->पढ़ो(rtc, RTC_EXT_CTRL_4B);
			ctrl4b |= (RTC_CTRL_4B_ABE | RTC_CTRL_4B_WIE |
				   RTC_CTRL_4B_KSE);
			rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4B, ctrl4b);
		पूर्ण

		/* Set PAB to 1 in Control 4A to घातer the प्रणाली करोwn. */
		dev_warn(&pdev->dev, "Powerdown.\n");
		msleep(20);
		rtc->ग_लिखो(rtc, RTC_EXT_CTRL_4A,
			   (ctrl4a | RTC_CTRL_4A_PAB));

		/* Spin ... we करो not चयन back to bank0. */
		जबतक(1);
		unreachable();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ds1685_rtc_घातeroff);
/* ----------------------------------------------------------------------- */


MODULE_AUTHOR("Joshua Kinard <kumba@gentoo.org>");
MODULE_AUTHOR("Matthias Fuchs <matthias.fuchs@esd-electronics.com>");
MODULE_DESCRIPTION("Dallas/Maxim DS1685/DS1687-series RTC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtc-ds1685");
