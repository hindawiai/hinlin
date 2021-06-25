<शैली गुरु>
/*
 * linux/arch/m68k/atari/समय.c
 *
 * Atari समय and real समय घड़ी stuff
 *
 * Assembled of parts of क्रमmer atari/config.c 97-12-18 by Roman Hodek
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/atariपूर्णांकs.h>
#समावेश <यंत्र/machdep.h>

DEFINE_SPINLOCK(rtc_lock);
EXPORT_SYMBOL_GPL(rtc_lock);

अटल u64 atari_पढ़ो_clk(काष्ठा घड़ीsource *cs);

अटल काष्ठा घड़ीsource atari_clk = अणु
	.name   = "mfp",
	.rating = 100,
	.पढ़ो   = atari_पढ़ो_clk,
	.mask   = CLOCKSOURCE_MASK(32),
	.flags  = CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल u32 clk_total;
अटल u8 last_समयr_count;

अटल irqवापस_t mfp_समयr_c_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	करो अणु
		last_समयr_count = st_mfp.tim_dt_c;
	पूर्ण जबतक (last_समयr_count == 1);
	clk_total += INT_TICKS;
	legacy_समयr_tick(1);
	समयr_heartbeat();
	local_irq_restore(flags);

	वापस IRQ_HANDLED;
पूर्ण

व्योम __init
atari_sched_init(व्योम)
अणु
    /* set Timer C data Register */
    st_mfp.tim_dt_c = INT_TICKS;
    /* start समयr C, भाग = 1:100 */
    st_mfp.tim_ct_cd = (st_mfp.tim_ct_cd & 15) | 0x60;
    /* install पूर्णांकerrupt service routine क्रम MFP Timer C */
    अगर (request_irq(IRQ_MFP_TIMC, mfp_समयr_c_handler, IRQF_TIMER, "timer",
                    शून्य))
	pr_err("Couldn't register timer interrupt\n");

    घड़ीsource_रेजिस्टर_hz(&atari_clk, INT_CLK);
पूर्ण

/* ++andreas: समय_लोoffset fixed to check क्रम pending पूर्णांकerrupt */

अटल u64 atari_पढ़ो_clk(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ flags;
	u8 count;
	u32 ticks;

	local_irq_save(flags);
	/* Ensure that the count is monotonically decreasing, even though
	 * the result may briefly stop changing after counter wrap-around.
	 */
	count = min(st_mfp.tim_dt_c, last_समयr_count);
	last_समयr_count = count;

	ticks = INT_TICKS - count;
	ticks += clk_total;
	local_irq_restore(flags);

	वापस ticks;
पूर्ण


अटल व्योम mste_पढ़ो(काष्ठा MSTE_RTC *val)
अणु
#घोषणा COPY(v) val->v=(mste_rtc.v & 0xf)
	करो अणु
		COPY(sec_ones) ; COPY(sec_tens) ; COPY(min_ones) ;
		COPY(min_tens) ; COPY(hr_ones) ; COPY(hr_tens) ;
		COPY(weekday) ; COPY(day_ones) ; COPY(day_tens) ;
		COPY(mon_ones) ; COPY(mon_tens) ; COPY(year_ones) ;
		COPY(year_tens) ;
	/* prevent from पढ़ोing the घड़ी जबतक it changed */
	पूर्ण जबतक (val->sec_ones != (mste_rtc.sec_ones & 0xf));
#अघोषित COPY
पूर्ण

अटल व्योम mste_ग_लिखो(काष्ठा MSTE_RTC *val)
अणु
#घोषणा COPY(v) mste_rtc.v=val->v
	करो अणु
		COPY(sec_ones) ; COPY(sec_tens) ; COPY(min_ones) ;
		COPY(min_tens) ; COPY(hr_ones) ; COPY(hr_tens) ;
		COPY(weekday) ; COPY(day_ones) ; COPY(day_tens) ;
		COPY(mon_ones) ; COPY(mon_tens) ; COPY(year_ones) ;
		COPY(year_tens) ;
	/* prevent from writing the घड़ी जबतक it changed */
	पूर्ण जबतक (val->sec_ones != (mste_rtc.sec_ones & 0xf));
#अघोषित COPY
पूर्ण

#घोषणा	RTC_READ(reg)				\
    (अणु	अचिन्हित अक्षर	__val;			\
		(व्योम) atari_ग_लिखोb(reg,&tt_rtc.regsel);	\
		__val = tt_rtc.data;		\
		__val;				\
	पूर्ण)

#घोषणा	RTC_WRITE(reg,val)			\
    करो अणु					\
		atari_ग_लिखोb(reg,&tt_rtc.regsel);	\
		tt_rtc.data = (val);		\
	पूर्ण जबतक(0)


#घोषणा HWCLK_POLL_INTERVAL	5

पूर्णांक atari_mste_hwclk( पूर्णांक op, काष्ठा rtc_समय *t )
अणु
    पूर्णांक hour, year;
    पूर्णांक hr24=0;
    काष्ठा MSTE_RTC val;

    mste_rtc.mode=(mste_rtc.mode | 1);
    hr24=mste_rtc.mon_tens & 1;
    mste_rtc.mode=(mste_rtc.mode & ~1);

    अगर (op) अणु
        /* ग_लिखो: prepare values */

        val.sec_ones = t->पंचांग_sec % 10;
        val.sec_tens = t->पंचांग_sec / 10;
        val.min_ones = t->पंचांग_min % 10;
        val.min_tens = t->पंचांग_min / 10;
        hour = t->पंचांग_hour;
        अगर (!hr24) अणु
	    अगर (hour > 11)
		hour += 20 - 12;
	    अगर (hour == 0 || hour == 20)
		hour += 12;
        पूर्ण
        val.hr_ones = hour % 10;
        val.hr_tens = hour / 10;
        val.day_ones = t->पंचांग_mday % 10;
        val.day_tens = t->पंचांग_mday / 10;
        val.mon_ones = (t->पंचांग_mon+1) % 10;
        val.mon_tens = (t->पंचांग_mon+1) / 10;
        year = t->पंचांग_year - 80;
        val.year_ones = year % 10;
        val.year_tens = year / 10;
        val.weekday = t->पंचांग_wday;
        mste_ग_लिखो(&val);
        mste_rtc.mode=(mste_rtc.mode | 1);
        val.year_ones = (year % 4);	/* leap year रेजिस्टर */
        mste_rtc.mode=(mste_rtc.mode & ~1);
    पूर्ण
    अन्यथा अणु
        mste_पढ़ो(&val);
        t->पंचांग_sec = val.sec_ones + val.sec_tens * 10;
        t->पंचांग_min = val.min_ones + val.min_tens * 10;
        hour = val.hr_ones + val.hr_tens * 10;
	अगर (!hr24) अणु
	    अगर (hour == 12 || hour == 12 + 20)
		hour -= 12;
	    अगर (hour >= 20)
                hour += 12 - 20;
        पूर्ण
	t->पंचांग_hour = hour;
	t->पंचांग_mday = val.day_ones + val.day_tens * 10;
        t->पंचांग_mon  = val.mon_ones + val.mon_tens * 10 - 1;
        t->पंचांग_year = val.year_ones + val.year_tens * 10 + 80;
        t->पंचांग_wday = val.weekday;
    पूर्ण
    वापस 0;
पूर्ण

पूर्णांक atari_tt_hwclk( पूर्णांक op, काष्ठा rtc_समय *t )
अणु
    पूर्णांक sec=0, min=0, hour=0, day=0, mon=0, year=0, wday=0;
    अचिन्हित दीर्घ	flags;
    अचिन्हित अक्षर	ctrl;
    पूर्णांक pm = 0;

    ctrl = RTC_READ(RTC_CONTROL); /* control रेजिस्टरs are
                                   * independent from the UIP */

    अगर (op) अणु
        /* ग_लिखो: prepare values */

        sec  = t->पंचांग_sec;
        min  = t->पंचांग_min;
        hour = t->पंचांग_hour;
        day  = t->पंचांग_mday;
        mon  = t->पंचांग_mon + 1;
        year = t->पंचांग_year - atari_rtc_year_offset;
        wday = t->पंचांग_wday + (t->पंचांग_wday >= 0);

        अगर (!(ctrl & RTC_24H)) अणु
	    अगर (hour > 11) अणु
		pm = 0x80;
		अगर (hour != 12)
		    hour -= 12;
	    पूर्ण
	    अन्यथा अगर (hour == 0)
		hour = 12;
        पूर्ण

        अगर (!(ctrl & RTC_DM_BINARY)) अणु
	    sec = bin2bcd(sec);
	    min = bin2bcd(min);
	    hour = bin2bcd(hour);
	    day = bin2bcd(day);
	    mon = bin2bcd(mon);
	    year = bin2bcd(year);
	    अगर (wday >= 0)
		wday = bin2bcd(wday);
        पूर्ण
    पूर्ण

    /* Reading/writing the घड़ी रेजिस्टरs is a bit critical due to
     * the regular update cycle of the RTC. While an update is in
     * progress, रेजिस्टरs 0..9 shouldn't be touched.
     * The problem is solved like that: If an update is currently in
     * progress (the UIP bit is set), the process sleeps क्रम a जबतक
     * (50ms). This really should be enough, since the update cycle
     * normally needs 2 ms.
     * If the UIP bit पढ़ोs as 0, we have at least 244 usecs until the
     * update starts. This should be enough... But to be sure,
     * additionally the RTC_SET bit is set to prevent an update cycle.
     */

    जबतक( RTC_READ(RTC_FREQ_SELECT) & RTC_UIP ) अणु
	अगर (in_atomic() || irqs_disabled())
	    mdelay(1);
	अन्यथा
	    schedule_समयout_पूर्णांकerruptible(HWCLK_POLL_INTERVAL);
    पूर्ण

    local_irq_save(flags);
    RTC_WRITE( RTC_CONTROL, ctrl | RTC_SET );
    अगर (!op) अणु
        sec  = RTC_READ( RTC_SECONDS );
        min  = RTC_READ( RTC_MINUTES );
        hour = RTC_READ( RTC_HOURS );
        day  = RTC_READ( RTC_DAY_OF_MONTH );
        mon  = RTC_READ( RTC_MONTH );
        year = RTC_READ( RTC_YEAR );
        wday = RTC_READ( RTC_DAY_OF_WEEK );
    पूर्ण
    अन्यथा अणु
        RTC_WRITE( RTC_SECONDS, sec );
        RTC_WRITE( RTC_MINUTES, min );
        RTC_WRITE( RTC_HOURS, hour + pm);
        RTC_WRITE( RTC_DAY_OF_MONTH, day );
        RTC_WRITE( RTC_MONTH, mon );
        RTC_WRITE( RTC_YEAR, year );
        अगर (wday >= 0) RTC_WRITE( RTC_DAY_OF_WEEK, wday );
    पूर्ण
    RTC_WRITE( RTC_CONTROL, ctrl & ~RTC_SET );
    local_irq_restore(flags);

    अगर (!op) अणु
        /* पढ़ो: adjust values */

        अगर (hour & 0x80) अणु
	    hour &= ~0x80;
	    pm = 1;
	पूर्ण

	अगर (!(ctrl & RTC_DM_BINARY)) अणु
	    sec = bcd2bin(sec);
	    min = bcd2bin(min);
	    hour = bcd2bin(hour);
	    day = bcd2bin(day);
	    mon = bcd2bin(mon);
	    year = bcd2bin(year);
	    wday = bcd2bin(wday);
        पूर्ण

        अगर (!(ctrl & RTC_24H)) अणु
	    अगर (!pm && hour == 12)
		hour = 0;
	    अन्यथा अगर (pm && hour != 12)
		hour += 12;
        पूर्ण

        t->पंचांग_sec  = sec;
        t->पंचांग_min  = min;
        t->पंचांग_hour = hour;
        t->पंचांग_mday = day;
        t->पंचांग_mon  = mon - 1;
        t->पंचांग_year = year + atari_rtc_year_offset;
        t->पंचांग_wday = wday - 1;
    पूर्ण

    वापस( 0 );
पूर्ण
