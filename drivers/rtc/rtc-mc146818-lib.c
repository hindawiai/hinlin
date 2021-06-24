<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/bcd.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/mc146818rtc.h>

#अगर_घोषित CONFIG_ACPI
#समावेश <linux/acpi.h>
#पूर्ण_अगर

अचिन्हित पूर्णांक mc146818_get_समय(काष्ठा rtc_समय *समय)
अणु
	अचिन्हित अक्षर ctrl;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर century = 0;
	bool retry;

#अगर_घोषित CONFIG_MACH_DECSTATION
	अचिन्हित पूर्णांक real_year;
#पूर्ण_अगर

again:
	spin_lock_irqsave(&rtc_lock, flags);
	/* Ensure that the RTC is accessible. Bit 6 must be 0! */
	अगर (WARN_ON_ONCE((CMOS_READ(RTC_VALID) & 0x40) != 0)) अणु
		spin_unlock_irqrestore(&rtc_lock, flags);
		स_रखो(समय, 0xff, माप(*समय));
		वापस 0;
	पूर्ण

	/*
	 * Check whether there is an update in progress during which the
	 * पढ़ोout is unspecअगरied. The maximum update समय is ~2ms. Poll
	 * every msec क्रम completion.
	 *
	 * Store the second value beक्रमe checking UIP so a दीर्घ lasting NMI
	 * which happens to hit after the UIP check cannot make an update
	 * cycle invisible.
	 */
	समय->पंचांग_sec = CMOS_READ(RTC_SECONDS);

	अगर (CMOS_READ(RTC_FREQ_SELECT) & RTC_UIP) अणु
		spin_unlock_irqrestore(&rtc_lock, flags);
		mdelay(1);
		जाओ again;
	पूर्ण

	/* Revalidate the above पढ़ोout */
	अगर (समय->पंचांग_sec != CMOS_READ(RTC_SECONDS)) अणु
		spin_unlock_irqrestore(&rtc_lock, flags);
		जाओ again;
	पूर्ण

	/*
	 * Only the values that we पढ़ो from the RTC are set. We leave
	 * पंचांग_wday, पंचांग_yday and पंचांग_isdst untouched. Even though the
	 * RTC has RTC_DAY_OF_WEEK, we ignore it, as it is only updated
	 * by the RTC when initially set to a non-zero value.
	 */
	समय->पंचांग_min = CMOS_READ(RTC_MINUTES);
	समय->पंचांग_hour = CMOS_READ(RTC_HOURS);
	समय->पंचांग_mday = CMOS_READ(RTC_DAY_OF_MONTH);
	समय->पंचांग_mon = CMOS_READ(RTC_MONTH);
	समय->पंचांग_year = CMOS_READ(RTC_YEAR);
#अगर_घोषित CONFIG_MACH_DECSTATION
	real_year = CMOS_READ(RTC_DEC_YEAR);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ACPI
	अगर (acpi_gbl_FADT.header.revision >= FADT2_REVISION_ID &&
	    acpi_gbl_FADT.century)
		century = CMOS_READ(acpi_gbl_FADT.century);
#पूर्ण_अगर
	ctrl = CMOS_READ(RTC_CONTROL);
	/*
	 * Check क्रम the UIP bit again. If it is set now then
	 * the above values may contain garbage.
	 */
	retry = CMOS_READ(RTC_FREQ_SELECT) & RTC_UIP;
	/*
	 * A NMI might have पूर्णांकerrupted the above sequence so check whether
	 * the seconds value has changed which indicates that the NMI took
	 * दीर्घer than the UIP bit was set. Unlikely, but possible and
	 * there is also virt...
	 */
	retry |= समय->पंचांग_sec != CMOS_READ(RTC_SECONDS);

	spin_unlock_irqrestore(&rtc_lock, flags);

	अगर (retry)
		जाओ again;

	अगर (!(ctrl & RTC_DM_BINARY) || RTC_ALWAYS_BCD)
	अणु
		समय->पंचांग_sec = bcd2bin(समय->पंचांग_sec);
		समय->पंचांग_min = bcd2bin(समय->पंचांग_min);
		समय->पंचांग_hour = bcd2bin(समय->पंचांग_hour);
		समय->पंचांग_mday = bcd2bin(समय->पंचांग_mday);
		समय->पंचांग_mon = bcd2bin(समय->पंचांग_mon);
		समय->पंचांग_year = bcd2bin(समय->पंचांग_year);
		century = bcd2bin(century);
	पूर्ण

#अगर_घोषित CONFIG_MACH_DECSTATION
	समय->पंचांग_year += real_year - 72;
#पूर्ण_अगर

	अगर (century > 20)
		समय->पंचांग_year += (century - 19) * 100;

	/*
	 * Account क्रम dअगरferences between how the RTC uses the values
	 * and how they are defined in a काष्ठा rtc_समय;
	 */
	अगर (समय->पंचांग_year <= 69)
		समय->पंचांग_year += 100;

	समय->पंचांग_mon--;

	वापस RTC_24H;
पूर्ण
EXPORT_SYMBOL_GPL(mc146818_get_समय);

/* Set the current date and समय in the real समय घड़ी. */
पूर्णांक mc146818_set_समय(काष्ठा rtc_समय *समय)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर mon, day, hrs, min, sec;
	अचिन्हित अक्षर save_control, save_freq_select;
	अचिन्हित पूर्णांक yrs;
#अगर_घोषित CONFIG_MACH_DECSTATION
	अचिन्हित पूर्णांक real_yrs, leap_yr;
#पूर्ण_अगर
	अचिन्हित अक्षर century = 0;

	yrs = समय->पंचांग_year;
	mon = समय->पंचांग_mon + 1;   /* पंचांग_mon starts at zero */
	day = समय->पंचांग_mday;
	hrs = समय->पंचांग_hour;
	min = समय->पंचांग_min;
	sec = समय->पंचांग_sec;

	अगर (yrs > 255)	/* They are अचिन्हित */
		वापस -EINVAL;

#अगर_घोषित CONFIG_MACH_DECSTATION
	real_yrs = yrs;
	leap_yr = ((!((yrs + 1900) % 4) && ((yrs + 1900) % 100)) ||
			!((yrs + 1900) % 400));
	yrs = 72;

	/*
	 * We want to keep the year set to 73 until March
	 * क्रम non-leap years, so that Feb, 29th is handled
	 * correctly.
	 */
	अगर (!leap_yr && mon < 3) अणु
		real_yrs--;
		yrs = 73;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
	अगर (acpi_gbl_FADT.header.revision >= FADT2_REVISION_ID &&
	    acpi_gbl_FADT.century) अणु
		century = (yrs + 1900) / 100;
		yrs %= 100;
	पूर्ण
#पूर्ण_अगर

	/* These limits and adjusपंचांगents are independent of
	 * whether the chip is in binary mode or not.
	 */
	अगर (yrs > 169)
		वापस -EINVAL;

	अगर (yrs >= 100)
		yrs -= 100;

	अगर (!(CMOS_READ(RTC_CONTROL) & RTC_DM_BINARY)
	    || RTC_ALWAYS_BCD) अणु
		sec = bin2bcd(sec);
		min = bin2bcd(min);
		hrs = bin2bcd(hrs);
		day = bin2bcd(day);
		mon = bin2bcd(mon);
		yrs = bin2bcd(yrs);
		century = bin2bcd(century);
	पूर्ण

	spin_lock_irqsave(&rtc_lock, flags);
	save_control = CMOS_READ(RTC_CONTROL);
	CMOS_WRITE((save_control|RTC_SET), RTC_CONTROL);
	save_freq_select = CMOS_READ(RTC_FREQ_SELECT);
	CMOS_WRITE((save_freq_select|RTC_DIV_RESET2), RTC_FREQ_SELECT);

#अगर_घोषित CONFIG_MACH_DECSTATION
	CMOS_WRITE(real_yrs, RTC_DEC_YEAR);
#पूर्ण_अगर
	CMOS_WRITE(yrs, RTC_YEAR);
	CMOS_WRITE(mon, RTC_MONTH);
	CMOS_WRITE(day, RTC_DAY_OF_MONTH);
	CMOS_WRITE(hrs, RTC_HOURS);
	CMOS_WRITE(min, RTC_MINUTES);
	CMOS_WRITE(sec, RTC_SECONDS);
#अगर_घोषित CONFIG_ACPI
	अगर (acpi_gbl_FADT.header.revision >= FADT2_REVISION_ID &&
	    acpi_gbl_FADT.century)
		CMOS_WRITE(century, acpi_gbl_FADT.century);
#पूर्ण_अगर

	CMOS_WRITE(save_control, RTC_CONTROL);
	CMOS_WRITE(save_freq_select, RTC_FREQ_SELECT);

	spin_unlock_irqrestore(&rtc_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mc146818_set_समय);
