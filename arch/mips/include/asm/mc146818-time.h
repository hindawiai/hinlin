<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Machine dependent access functions क्रम RTC रेजिस्टरs.
 */
#अगर_अघोषित __ASM_MC146818_TIME_H
#घोषणा __ASM_MC146818_TIME_H

#समावेश <linux/bcd.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/समय.स>

/*
 * For check timing call set_rtc_mmss() 500ms; used in समयr पूर्णांकerrupt.
 */
#घोषणा USEC_AFTER	500000
#घोषणा USEC_BEFORE	500000

/*
 * In order to set the CMOS घड़ी precisely, set_rtc_mmss has to be
 * called 500 ms after the second nowसमय has started, because when
 * nowसमय is written पूर्णांकo the रेजिस्टरs of the CMOS घड़ी, it will
 * jump to the next second precisely 500 ms later. Check the Motorola
 * MC146818A or Dallas DS12887 data sheet क्रम details.
 *
 * BUG: This routine करोes not handle hour overflow properly; it just
 *	sets the minutes. Usually you'll only notice that after reboot!
 */
अटल अंतरभूत पूर्णांक mc146818_set_rtc_mmss(अचिन्हित दीर्घ nowसमय)
अणु
	पूर्णांक real_seconds, real_minutes, cmos_minutes;
	अचिन्हित अक्षर save_control, save_freq_select;
	पूर्णांक retval = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtc_lock, flags);
	save_control = CMOS_READ(RTC_CONTROL); /* tell the घड़ी it's being set */
	CMOS_WRITE((save_control|RTC_SET), RTC_CONTROL);

	save_freq_select = CMOS_READ(RTC_FREQ_SELECT); /* stop and reset prescaler */
	CMOS_WRITE((save_freq_select|RTC_DIV_RESET2), RTC_FREQ_SELECT);

	cmos_minutes = CMOS_READ(RTC_MINUTES);
	अगर (!(save_control & RTC_DM_BINARY) || RTC_ALWAYS_BCD)
		cmos_minutes = bcd2bin(cmos_minutes);

	/*
	 * since we're only adjusting minutes and seconds,
	 * करोn't पूर्णांकerfere with hour overflow. This aव्योमs
	 * messing with unknown समय zones but requires your
	 * RTC not to be off by more than 15 minutes
	 */
	real_seconds = nowसमय % 60;
	real_minutes = nowसमय / 60;
	अगर (((असल(real_minutes - cmos_minutes) + 15)/30) & 1)
		real_minutes += 30;		/* correct क्रम half hour समय zone */
	real_minutes %= 60;

	अगर (असल(real_minutes - cmos_minutes) < 30) अणु
		अगर (!(save_control & RTC_DM_BINARY) || RTC_ALWAYS_BCD) अणु
			real_seconds = bin2bcd(real_seconds);
			real_minutes = bin2bcd(real_minutes);
		पूर्ण
		CMOS_WRITE(real_seconds, RTC_SECONDS);
		CMOS_WRITE(real_minutes, RTC_MINUTES);
	पूर्ण अन्यथा अणु
		prपूर्णांकk_once(KERN_NOTICE
		       "set_rtc_mmss: can't update from %d to %d\n",
		       cmos_minutes, real_minutes);
		retval = -1;
	पूर्ण

	/* The following flags have to be released exactly in this order,
	 * otherwise the DS12887 (popular MC146818A clone with पूर्णांकegrated
	 * battery and quartz) will not reset the oscillator and will not
	 * update precisely 500 ms later. You won't find this mentioned in
	 * the Dallas Semiconductor data sheets, but who believes data
	 * sheets anyway ...			       -- Markus Kuhn
	 */
	CMOS_WRITE(save_control, RTC_CONTROL);
	CMOS_WRITE(save_freq_select, RTC_FREQ_SELECT);
	spin_unlock_irqrestore(&rtc_lock, flags);

	वापस retval;
पूर्ण

अटल अंतरभूत समय64_t mc146818_get_cmos_समय(व्योम)
अणु
	अचिन्हित पूर्णांक year, mon, day, hour, min, sec;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtc_lock, flags);

	करो अणु
		sec = CMOS_READ(RTC_SECONDS);
		min = CMOS_READ(RTC_MINUTES);
		hour = CMOS_READ(RTC_HOURS);
		day = CMOS_READ(RTC_DAY_OF_MONTH);
		mon = CMOS_READ(RTC_MONTH);
		year = CMOS_READ(RTC_YEAR);
	पूर्ण जबतक (sec != CMOS_READ(RTC_SECONDS));

	अगर (!(CMOS_READ(RTC_CONTROL) & RTC_DM_BINARY) || RTC_ALWAYS_BCD) अणु
		sec = bcd2bin(sec);
		min = bcd2bin(min);
		hour = bcd2bin(hour);
		day = bcd2bin(day);
		mon = bcd2bin(mon);
		year = bcd2bin(year);
	पूर्ण
	spin_unlock_irqrestore(&rtc_lock, flags);
	year = mc146818_decode_year(year);

	वापस स_गढ़ो64(year, mon, day, hour, min, sec);
पूर्ण

#पूर्ण_अगर /* __ASM_MC146818_TIME_H */
