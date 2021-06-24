<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  (c) Copyright 2004 Benjamin Herrenschmidt (benh@kernel.crashing.org),
 *                     IBM Corp. 
 */

#अघोषित DEBUG

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/bcd.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/समय.स>

#समावेश "maple.h"

#अगर_घोषित DEBUG
#घोषणा DBG(x...) prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG(x...)
#पूर्ण_अगर

अटल पूर्णांक maple_rtc_addr;

अटल पूर्णांक maple_घड़ी_पढ़ो(पूर्णांक addr)
अणु
	outb_p(addr, maple_rtc_addr);
	वापस inb_p(maple_rtc_addr+1);
पूर्ण

अटल व्योम maple_घड़ी_ग_लिखो(अचिन्हित दीर्घ val, पूर्णांक addr)
अणु
	outb_p(addr, maple_rtc_addr);
	outb_p(val, maple_rtc_addr+1);
पूर्ण

व्योम maple_get_rtc_समय(काष्ठा rtc_समय *पंचांग)
अणु
	करो अणु
		पंचांग->पंचांग_sec = maple_घड़ी_पढ़ो(RTC_SECONDS);
		पंचांग->पंचांग_min = maple_घड़ी_पढ़ो(RTC_MINUTES);
		पंचांग->पंचांग_hour = maple_घड़ी_पढ़ो(RTC_HOURS);
		पंचांग->पंचांग_mday = maple_घड़ी_पढ़ो(RTC_DAY_OF_MONTH);
		पंचांग->पंचांग_mon = maple_घड़ी_पढ़ो(RTC_MONTH);
		पंचांग->पंचांग_year = maple_घड़ी_पढ़ो(RTC_YEAR);
	पूर्ण जबतक (पंचांग->पंचांग_sec != maple_घड़ी_पढ़ो(RTC_SECONDS));

	अगर (!(maple_घड़ी_पढ़ो(RTC_CONTROL) & RTC_DM_BINARY)
	    || RTC_ALWAYS_BCD) अणु
		पंचांग->पंचांग_sec = bcd2bin(पंचांग->पंचांग_sec);
		पंचांग->पंचांग_min = bcd2bin(पंचांग->पंचांग_min);
		पंचांग->पंचांग_hour = bcd2bin(पंचांग->पंचांग_hour);
		पंचांग->पंचांग_mday = bcd2bin(पंचांग->पंचांग_mday);
		पंचांग->पंचांग_mon = bcd2bin(पंचांग->पंचांग_mon);
		पंचांग->पंचांग_year = bcd2bin(पंचांग->पंचांग_year);
	  पूर्ण
	अगर ((पंचांग->पंचांग_year + 1900) < 1970)
		पंचांग->पंचांग_year += 100;

	पंचांग->पंचांग_wday = -1;
पूर्ण

पूर्णांक maple_set_rtc_समय(काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित अक्षर save_control, save_freq_select;
	पूर्णांक sec, min, hour, mon, mday, year;

	spin_lock(&rtc_lock);

	save_control = maple_घड़ी_पढ़ो(RTC_CONTROL); /* tell the घड़ी it's being set */

	maple_घड़ी_ग_लिखो((save_control|RTC_SET), RTC_CONTROL);

	save_freq_select = maple_घड़ी_पढ़ो(RTC_FREQ_SELECT); /* stop and reset prescaler */

	maple_घड़ी_ग_लिखो((save_freq_select|RTC_DIV_RESET2), RTC_FREQ_SELECT);

	sec = पंचांग->पंचांग_sec;
	min = पंचांग->पंचांग_min;
	hour = पंचांग->पंचांग_hour;
	mon = पंचांग->पंचांग_mon;
	mday = पंचांग->पंचांग_mday;
	year = पंचांग->पंचांग_year;

	अगर (!(save_control & RTC_DM_BINARY) || RTC_ALWAYS_BCD) अणु
		sec = bin2bcd(sec);
		min = bin2bcd(min);
		hour = bin2bcd(hour);
		mon = bin2bcd(mon);
		mday = bin2bcd(mday);
		year = bin2bcd(year);
	पूर्ण
	maple_घड़ी_ग_लिखो(sec, RTC_SECONDS);
	maple_घड़ी_ग_लिखो(min, RTC_MINUTES);
	maple_घड़ी_ग_लिखो(hour, RTC_HOURS);
	maple_घड़ी_ग_लिखो(mon, RTC_MONTH);
	maple_घड़ी_ग_लिखो(mday, RTC_DAY_OF_MONTH);
	maple_घड़ी_ग_लिखो(year, RTC_YEAR);

	/* The following flags have to be released exactly in this order,
	 * otherwise the DS12887 (popular MC146818A clone with पूर्णांकegrated
	 * battery and quartz) will not reset the oscillator and will not
	 * update precisely 500 ms later. You won't find this mentioned in
	 * the Dallas Semiconductor data sheets, but who believes data
	 * sheets anyway ...                           -- Markus Kuhn
	 */
	maple_घड़ी_ग_लिखो(save_control, RTC_CONTROL);
	maple_घड़ी_ग_लिखो(save_freq_select, RTC_FREQ_SELECT);

	spin_unlock(&rtc_lock);

	वापस 0;
पूर्ण

अटल काष्ठा resource rtc_iores = अणु
	.name = "rtc",
	.flags = IORESOURCE_IO | IORESOURCE_BUSY,
पूर्ण;

समय64_t __init maple_get_boot_समय(व्योम)
अणु
	काष्ठा rtc_समय पंचांग;
	काष्ठा device_node *rtcs;

	rtcs = of_find_compatible_node(शून्य, "rtc", "pnpPNP,b00");
	अगर (rtcs) अणु
		काष्ठा resource r;
		अगर (of_address_to_resource(rtcs, 0, &r)) अणु
			prपूर्णांकk(KERN_EMERG "Maple: Unable to translate RTC"
			       " address\n");
			जाओ bail;
		पूर्ण
		अगर (!(r.flags & IORESOURCE_IO)) अणु
			prपूर्णांकk(KERN_EMERG "Maple: RTC address isn't PIO!\n");
			जाओ bail;
		पूर्ण
		maple_rtc_addr = r.start;
		prपूर्णांकk(KERN_INFO "Maple: Found RTC at IO 0x%x\n",
		       maple_rtc_addr);
	पूर्ण
 bail:
	अगर (maple_rtc_addr == 0) अणु
		maple_rtc_addr = RTC_PORT(0); /* legacy address */
		prपूर्णांकk(KERN_INFO "Maple: No device node for RTC, assuming "
		       "legacy address (0x%x)\n", maple_rtc_addr);
	पूर्ण

	rtc_iores.start = maple_rtc_addr;
	rtc_iores.end = maple_rtc_addr + 7;
	request_resource(&ioport_resource, &rtc_iores);

	maple_get_rtc_समय(&पंचांग);
	वापस rtc_पंचांग_to_समय64(&पंचांग);
पूर्ण

