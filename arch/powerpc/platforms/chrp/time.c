<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1991, 1992, 1995  Linus Torvalds
 *
 * Adapted क्रम PowerPC (PReP) by Gary Thomas
 * Modअगरied by Cort Dougan (cort@cs.nmt.edu).
 * Copied and modअगरied from arch/i386/kernel/समय.c
 *
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयx.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/init.h>
#समावेश <linux/bcd.h>
#समावेश <linux/ioport.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/nvram.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/समय.स>

#समावेश <platक्रमms/chrp/chrp.h>

बाह्य spinlock_t rtc_lock;

#घोषणा NVRAM_AS0  0x74
#घोषणा NVRAM_AS1  0x75
#घोषणा NVRAM_DATA 0x77

अटल पूर्णांक nvram_as1 = NVRAM_AS1;
अटल पूर्णांक nvram_as0 = NVRAM_AS0;
अटल पूर्णांक nvram_data = NVRAM_DATA;

दीर्घ __init chrp_समय_init(व्योम)
अणु
	काष्ठा device_node *rtcs;
	काष्ठा resource r;
	पूर्णांक base;

	rtcs = of_find_compatible_node(शून्य, "rtc", "pnpPNP,b00");
	अगर (rtcs == शून्य)
		rtcs = of_find_compatible_node(शून्य, "rtc", "ds1385-rtc");
	अगर (rtcs == शून्य)
		वापस 0;
	अगर (of_address_to_resource(rtcs, 0, &r)) अणु
		of_node_put(rtcs);
		वापस 0;
	पूर्ण
	of_node_put(rtcs);

	base = r.start;
	nvram_as1 = 0;
	nvram_as0 = base;
	nvram_data = base + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक chrp_cmos_घड़ी_पढ़ो(पूर्णांक addr)
अणु
	अगर (nvram_as1 != 0)
		outb(addr>>8, nvram_as1);
	outb(addr, nvram_as0);
	वापस (inb(nvram_data));
पूर्ण

अटल व्योम chrp_cmos_घड़ी_ग_लिखो(अचिन्हित दीर्घ val, पूर्णांक addr)
अणु
	अगर (nvram_as1 != 0)
		outb(addr>>8, nvram_as1);
	outb(addr, nvram_as0);
	outb(val, nvram_data);
	वापस;
पूर्ण

/*
 * Set the hardware घड़ी. -- Cort
 */
पूर्णांक chrp_set_rtc_समय(काष्ठा rtc_समय *पंचांगarg)
अणु
	अचिन्हित अक्षर save_control, save_freq_select;
	काष्ठा rtc_समय पंचांग = *पंचांगarg;

	spin_lock(&rtc_lock);

	save_control = chrp_cmos_घड़ी_पढ़ो(RTC_CONTROL); /* tell the घड़ी it's being set */

	chrp_cmos_घड़ी_ग_लिखो((save_control|RTC_SET), RTC_CONTROL);

	save_freq_select = chrp_cmos_घड़ी_पढ़ो(RTC_FREQ_SELECT); /* stop and reset prescaler */

	chrp_cmos_घड़ी_ग_लिखो((save_freq_select|RTC_DIV_RESET2), RTC_FREQ_SELECT);

	अगर (!(save_control & RTC_DM_BINARY) || RTC_ALWAYS_BCD) अणु
		पंचांग.पंचांग_sec = bin2bcd(पंचांग.पंचांग_sec);
		पंचांग.पंचांग_min = bin2bcd(पंचांग.पंचांग_min);
		पंचांग.पंचांग_hour = bin2bcd(पंचांग.पंचांग_hour);
		पंचांग.पंचांग_mon = bin2bcd(पंचांग.पंचांग_mon);
		पंचांग.पंचांग_mday = bin2bcd(पंचांग.पंचांग_mday);
		पंचांग.पंचांग_year = bin2bcd(पंचांग.पंचांग_year);
	पूर्ण
	chrp_cmos_घड़ी_ग_लिखो(पंचांग.पंचांग_sec,RTC_SECONDS);
	chrp_cmos_घड़ी_ग_लिखो(पंचांग.पंचांग_min,RTC_MINUTES);
	chrp_cmos_घड़ी_ग_लिखो(पंचांग.पंचांग_hour,RTC_HOURS);
	chrp_cmos_घड़ी_ग_लिखो(पंचांग.पंचांग_mon,RTC_MONTH);
	chrp_cmos_घड़ी_ग_लिखो(पंचांग.पंचांग_mday,RTC_DAY_OF_MONTH);
	chrp_cmos_घड़ी_ग_लिखो(पंचांग.पंचांग_year,RTC_YEAR);

	/* The following flags have to be released exactly in this order,
	 * otherwise the DS12887 (popular MC146818A clone with पूर्णांकegrated
	 * battery and quartz) will not reset the oscillator and will not
	 * update precisely 500 ms later. You won't find this mentioned in
	 * the Dallas Semiconductor data sheets, but who believes data
	 * sheets anyway ...                           -- Markus Kuhn
	 */
	chrp_cmos_घड़ी_ग_लिखो(save_control, RTC_CONTROL);
	chrp_cmos_घड़ी_ग_लिखो(save_freq_select, RTC_FREQ_SELECT);

	spin_unlock(&rtc_lock);
	वापस 0;
पूर्ण

व्योम chrp_get_rtc_समय(काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित पूर्णांक year, mon, day, hour, min, sec;

	करो अणु
		sec = chrp_cmos_घड़ी_पढ़ो(RTC_SECONDS);
		min = chrp_cmos_घड़ी_पढ़ो(RTC_MINUTES);
		hour = chrp_cmos_घड़ी_पढ़ो(RTC_HOURS);
		day = chrp_cmos_घड़ी_पढ़ो(RTC_DAY_OF_MONTH);
		mon = chrp_cmos_घड़ी_पढ़ो(RTC_MONTH);
		year = chrp_cmos_घड़ी_पढ़ो(RTC_YEAR);
	पूर्ण जबतक (sec != chrp_cmos_घड़ी_पढ़ो(RTC_SECONDS));

	अगर (!(chrp_cmos_घड़ी_पढ़ो(RTC_CONTROL) & RTC_DM_BINARY) || RTC_ALWAYS_BCD) अणु
		sec = bcd2bin(sec);
		min = bcd2bin(min);
		hour = bcd2bin(hour);
		day = bcd2bin(day);
		mon = bcd2bin(mon);
		year = bcd2bin(year);
	पूर्ण
	अगर (year < 70)
		year += 100;
	पंचांग->पंचांग_sec = sec;
	पंचांग->पंचांग_min = min;
	पंचांग->पंचांग_hour = hour;
	पंचांग->पंचांग_mday = day;
	पंचांग->पंचांग_mon = mon;
	पंचांग->पंचांग_year = year;
पूर्ण
