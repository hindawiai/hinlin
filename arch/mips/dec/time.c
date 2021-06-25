<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1991, 1992, 1995  Linus Torvalds
 *  Copyright (C) 2000, 2003  Maciej W. Rozycki
 *
 * This file contains the समय handling details क्रम PC-style घड़ीs as
 * found in some MIPS प्रणालीs.
 *
 */
#समावेश <linux/bcd.h>
#समावेश <linux/init.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/param.h>

#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/ds1287.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/dec/पूर्णांकerrupts.h>
#समावेश <यंत्र/dec/ioasic.h>
#समावेश <यंत्र/dec/machtype.h>

व्योम पढ़ो_persistent_घड़ी64(काष्ठा बारpec64 *ts)
अणु
	अचिन्हित पूर्णांक year, mon, day, hour, min, sec, real_year;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtc_lock, flags);

	करो अणु
		sec = CMOS_READ(RTC_SECONDS);
		min = CMOS_READ(RTC_MINUTES);
		hour = CMOS_READ(RTC_HOURS);
		day = CMOS_READ(RTC_DAY_OF_MONTH);
		mon = CMOS_READ(RTC_MONTH);
		year = CMOS_READ(RTC_YEAR);
		/*
		 * The PROM will reset the year to either '72 or '73.
		 * Thereक्रमe we store the real year separately, in one
		 * of unused BBU RAM locations.
		 */
		real_year = CMOS_READ(RTC_DEC_YEAR);
	पूर्ण जबतक (sec != CMOS_READ(RTC_SECONDS));

	spin_unlock_irqrestore(&rtc_lock, flags);

	अगर (!(CMOS_READ(RTC_CONTROL) & RTC_DM_BINARY) || RTC_ALWAYS_BCD) अणु
		sec = bcd2bin(sec);
		min = bcd2bin(min);
		hour = bcd2bin(hour);
		day = bcd2bin(day);
		mon = bcd2bin(mon);
		year = bcd2bin(year);
	पूर्ण

	year += real_year - 72 + 2000;

	ts->tv_sec = स_गढ़ो64(year, mon, day, hour, min, sec);
	ts->tv_nsec = 0;
पूर्ण

/*
 * In order to set the CMOS घड़ी precisely, update_persistent_घड़ी64 has to
 * be called 500 ms after the second nowसमय has started, because when
 * nowसमय is written पूर्णांकo the रेजिस्टरs of the CMOS घड़ी, it will
 * jump to the next second precisely 500 ms later.  Check the Dallas
 * DS1287 data sheet क्रम details.
 */
पूर्णांक update_persistent_घड़ी64(काष्ठा बारpec64 now)
अणु
	समय64_t nowसमय = now.tv_sec;
	पूर्णांक retval = 0;
	पूर्णांक real_seconds, real_minutes, cmos_minutes;
	अचिन्हित अक्षर save_control, save_freq_select;

	/* irq are locally disabled here */
	spin_lock(&rtc_lock);
	/* tell the घड़ी it's being set */
	save_control = CMOS_READ(RTC_CONTROL);
	CMOS_WRITE((save_control | RTC_SET), RTC_CONTROL);

	/* stop and reset prescaler */
	save_freq_select = CMOS_READ(RTC_FREQ_SELECT);
	CMOS_WRITE((save_freq_select | RTC_DIV_RESET2), RTC_FREQ_SELECT);

	cmos_minutes = CMOS_READ(RTC_MINUTES);
	अगर (!(save_control & RTC_DM_BINARY) || RTC_ALWAYS_BCD)
		cmos_minutes = bcd2bin(cmos_minutes);

	/*
	 * since we're only adjusting minutes and seconds,
	 * करोn't पूर्णांकerfere with hour overflow. This aव्योमs
	 * messing with unknown समय zones but requires your
	 * RTC not to be off by more than 15 minutes
	 */
	real_minutes = भाग_s64_rem(nowसमय, 60, &real_seconds);
	अगर (((असल(real_minutes - cmos_minutes) + 15) / 30) & 1)
		real_minutes += 30;	/* correct क्रम half hour समय zone */
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
	 * otherwise the DS1287 will not reset the oscillator and will not
	 * update precisely 500 ms later.  You won't find this mentioned
	 * in the Dallas Semiconductor data sheets, but who believes data
	 * sheets anyway ...                           -- Markus Kuhn
	 */
	CMOS_WRITE(save_control, RTC_CONTROL);
	CMOS_WRITE(save_freq_select, RTC_FREQ_SELECT);
	spin_unlock(&rtc_lock);

	वापस retval;
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
	पूर्णांक ioasic_घड़ी = 0;
	u32 start, end;
	पूर्णांक i = HZ / 8;

	/* Set up the rate of periodic DS1287 पूर्णांकerrupts. */
	ds1287_set_base_घड़ी(HZ);

	/* On some I/O ASIC प्रणालीs we have the I/O ASIC's counter.  */
	अगर (IOASIC)
		ioasic_घड़ी = dec_ioasic_घड़ीsource_init() == 0;
	अगर (cpu_has_counter) अणु
		ds1287_समयr_state();
		जबतक (!ds1287_समयr_state())
			;

		start = पढ़ो_c0_count();

		जबतक (i--)
			जबतक (!ds1287_समयr_state())
				;

		end = पढ़ो_c0_count();

		mips_hpt_frequency = (end - start) * 8;
		prपूर्णांकk(KERN_INFO "MIPS counter frequency %dHz\n",
			mips_hpt_frequency);

		/*
		 * All R4k DECstations suffer from the CP0 Count erratum,
		 * so we can't use the समयr as a घड़ी source, and a घड़ी
		 * event both at a समय.  An accurate wall घड़ी is more
		 * important than a high-precision पूर्णांकerval समयr so only
		 * use the समयr as a घड़ी source, and not a घड़ी event
		 * अगर there's no I/O ASIC counter available to serve as a
		 * घड़ी source.
		 */
		अगर (!ioasic_घड़ी) अणु
			init_r4k_घड़ीsource();
			mips_hpt_frequency = 0;
		पूर्ण
	पूर्ण

	ds1287_घड़ीevent_init(dec_पूर्णांकerrupt[DEC_IRQ_RTC]);
पूर्ण
