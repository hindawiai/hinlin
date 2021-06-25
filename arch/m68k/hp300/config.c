<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/m68k/hp300/config.c
 *
 *  Copyright (C) 1998 Philip Blundell <philb@gnu.org>
 *
 *  This file contains the HP300-specअगरic initialisation code.  It माला_लो
 *  called by setup.c.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/console.h>
#समावेश <linux/rtc.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/bootinfo-hp300.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/blinken.h>
#समावेश <यंत्र/पन.स>                               /* पढ़ोb() and ग_लिखोb() */
#समावेश <यंत्र/hp300hw.h>

#समावेश "time.h"

अचिन्हित दीर्घ hp300_model;
अचिन्हित दीर्घ hp300_uart_scode = -1;
अचिन्हित अक्षर hp300_ledstate;
EXPORT_SYMBOL(hp300_ledstate);

अटल अक्षर s_hp330[] __initdata = "330";
अटल अक्षर s_hp340[] __initdata = "340";
अटल अक्षर s_hp345[] __initdata = "345";
अटल अक्षर s_hp360[] __initdata = "360";
अटल अक्षर s_hp370[] __initdata = "370";
अटल अक्षर s_hp375[] __initdata = "375";
अटल अक्षर s_hp380[] __initdata = "380";
अटल अक्षर s_hp385[] __initdata = "385";
अटल अक्षर s_hp400[] __initdata = "400";
अटल अक्षर s_hp425t[] __initdata = "425t";
अटल अक्षर s_hp425s[] __initdata = "425s";
अटल अक्षर s_hp425e[] __initdata = "425e";
अटल अक्षर s_hp433t[] __initdata = "433t";
अटल अक्षर s_hp433s[] __initdata = "433s";
अटल अक्षर *hp300_models[] __initdata = अणु
	[HP_320]	= शून्य,
	[HP_330]	= s_hp330,
	[HP_340]	= s_hp340,
	[HP_345]	= s_hp345,
	[HP_350]	= शून्य,
	[HP_360]	= s_hp360,
	[HP_370]	= s_hp370,
	[HP_375]	= s_hp375,
	[HP_380]	= s_hp380,
	[HP_385]	= s_hp385,
	[HP_400]	= s_hp400,
	[HP_425T]	= s_hp425t,
	[HP_425S]	= s_hp425s,
	[HP_425E]	= s_hp425e,
	[HP_433T]	= s_hp433t,
	[HP_433S]	= s_hp433s,
पूर्ण;

अटल अक्षर hp300_model_name[13] = "HP9000/";

बाह्य व्योम hp300_reset(व्योम);
#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
बाह्य पूर्णांक hp300_setup_serial_console(व्योम) __init;
#पूर्ण_अगर

पूर्णांक __init hp300_parse_bootinfo(स्थिर काष्ठा bi_record *record)
अणु
	पूर्णांक unknown = 0;
	स्थिर व्योम *data = record->data;

	चयन (be16_to_cpu(record->tag)) अणु
	हाल BI_HP300_MODEL:
		hp300_model = be32_to_cpup(data);
		अवरोध;

	हाल BI_HP300_UART_SCODE:
		hp300_uart_scode = be32_to_cpup(data);
		अवरोध;

	हाल BI_HP300_UART_ADDR:
		/* serial port address: ignored here */
		अवरोध;

	शेष:
		unknown = 1;
	पूर्ण

	वापस unknown;
पूर्ण

#अगर_घोषित CONFIG_HEARTBEAT
अटल व्योम hp300_pulse(पूर्णांक x)
अणु
	अगर (x)
		blinken_leds(0x10, 0);
	अन्यथा
		blinken_leds(0, 0x10);
पूर्ण
#पूर्ण_अगर

अटल व्योम hp300_get_model(अक्षर *model)
अणु
	म_नकल(model, hp300_model_name);
पूर्ण

#घोषणा RTCBASE			0xf0420000
#घोषणा RTC_DATA		0x1
#घोषणा RTC_CMD			0x3

#घोषणा	RTC_BUSY		0x02
#घोषणा	RTC_DATA_RDY		0x01

#घोषणा rtc_busy()		(in_8(RTCBASE + RTC_CMD) & RTC_BUSY)
#घोषणा rtc_data_available()	(in_8(RTCBASE + RTC_CMD) & RTC_DATA_RDY)
#घोषणा rtc_status()		(in_8(RTCBASE + RTC_CMD))
#घोषणा rtc_command(x)		out_8(RTCBASE + RTC_CMD, (x))
#घोषणा rtc_पढ़ो_data()		(in_8(RTCBASE + RTC_DATA))
#घोषणा rtc_ग_लिखो_data(x)	out_8(RTCBASE + RTC_DATA, (x))

#घोषणा RTC_SETREG	0xe0
#घोषणा RTC_WRITEREG	0xc2
#घोषणा RTC_READREG	0xc3

#घोषणा RTC_REG_SEC2	0
#घोषणा RTC_REG_SEC1	1
#घोषणा RTC_REG_MIN2	2
#घोषणा RTC_REG_MIN1	3
#घोषणा RTC_REG_HOUR2	4
#घोषणा RTC_REG_HOUR1	5
#घोषणा RTC_REG_WDAY	6
#घोषणा RTC_REG_DAY2	7
#घोषणा RTC_REG_DAY1	8
#घोषणा RTC_REG_MON2	9
#घोषणा RTC_REG_MON1	10
#घोषणा RTC_REG_YEAR2	11
#घोषणा RTC_REG_YEAR1	12

#घोषणा RTC_HOUR1_24HMODE 0x8

#घोषणा RTC_STAT_MASK	0xf0
#घोषणा RTC_STAT_RDY	0x40

अटल अंतरभूत अचिन्हित अक्षर hp300_rtc_पढ़ो(अचिन्हित अक्षर reg)
अणु
	अचिन्हित अक्षर s, ret;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	जबतक (rtc_busy());
	rtc_command(RTC_SETREG);
	जबतक (rtc_busy());
	rtc_ग_लिखो_data(reg);
	जबतक (rtc_busy());
	rtc_command(RTC_READREG);

	करो अणु
		जबतक (!rtc_data_available());
		s = rtc_status();
		ret = rtc_पढ़ो_data();
	पूर्ण जबतक ((s & RTC_STAT_MASK) != RTC_STAT_RDY);

	local_irq_restore(flags);

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर hp300_rtc_ग_लिखो(अचिन्हित अक्षर reg,
					    अचिन्हित अक्षर val)
अणु
	अचिन्हित अक्षर s, ret;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	जबतक (rtc_busy());
	rtc_command(RTC_SETREG);
	जबतक (rtc_busy());
	rtc_ग_लिखो_data((val << 4) | reg);
	जबतक (rtc_busy());
	rtc_command(RTC_WRITEREG);
	जबतक (rtc_busy());
	rtc_command(RTC_READREG);

	करो अणु
		जबतक (!rtc_data_available());
		s = rtc_status();
		ret = rtc_पढ़ो_data();
	पूर्ण जबतक ((s & RTC_STAT_MASK) != RTC_STAT_RDY);

	local_irq_restore(flags);

	वापस ret;
पूर्ण

अटल पूर्णांक hp300_hwclk(पूर्णांक op, काष्ठा rtc_समय *t)
अणु
	अगर (!op) अणु /* पढ़ो */
		t->पंचांग_sec  = hp300_rtc_पढ़ो(RTC_REG_SEC1) * 10 +
			hp300_rtc_पढ़ो(RTC_REG_SEC2);
		t->पंचांग_min  = hp300_rtc_पढ़ो(RTC_REG_MIN1) * 10 +
			hp300_rtc_पढ़ो(RTC_REG_MIN2);
		t->पंचांग_hour = (hp300_rtc_पढ़ो(RTC_REG_HOUR1) & 3) * 10 +
			hp300_rtc_पढ़ो(RTC_REG_HOUR2);
		t->पंचांग_wday = -1;
		t->पंचांग_mday = hp300_rtc_पढ़ो(RTC_REG_DAY1) * 10 +
			hp300_rtc_पढ़ो(RTC_REG_DAY2);
		t->पंचांग_mon  = hp300_rtc_पढ़ो(RTC_REG_MON1) * 10 +
			hp300_rtc_पढ़ो(RTC_REG_MON2) - 1;
		t->पंचांग_year = hp300_rtc_पढ़ो(RTC_REG_YEAR1) * 10 +
			hp300_rtc_पढ़ो(RTC_REG_YEAR2);
		अगर (t->पंचांग_year <= 69)
			t->पंचांग_year += 100;
	पूर्ण अन्यथा अणु
		hp300_rtc_ग_लिखो(RTC_REG_SEC1, t->पंचांग_sec / 10);
		hp300_rtc_ग_लिखो(RTC_REG_SEC2, t->पंचांग_sec % 10);
		hp300_rtc_ग_लिखो(RTC_REG_MIN1, t->पंचांग_min / 10);
		hp300_rtc_ग_लिखो(RTC_REG_MIN2, t->पंचांग_min % 10);
		hp300_rtc_ग_लिखो(RTC_REG_HOUR1,
				((t->पंचांग_hour / 10) & 3) | RTC_HOUR1_24HMODE);
		hp300_rtc_ग_लिखो(RTC_REG_HOUR2, t->पंचांग_hour % 10);
		hp300_rtc_ग_लिखो(RTC_REG_DAY1, t->पंचांग_mday / 10);
		hp300_rtc_ग_लिखो(RTC_REG_DAY2, t->पंचांग_mday % 10);
		hp300_rtc_ग_लिखो(RTC_REG_MON1, (t->पंचांग_mon + 1) / 10);
		hp300_rtc_ग_लिखो(RTC_REG_MON2, (t->पंचांग_mon + 1) % 10);
		अगर (t->पंचांग_year >= 100)
			t->पंचांग_year -= 100;
		hp300_rtc_ग_लिखो(RTC_REG_YEAR1, t->पंचांग_year / 10);
		hp300_rtc_ग_लिखो(RTC_REG_YEAR2, t->पंचांग_year % 10);
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक hp300_get_ss(व्योम)
अणु
	वापस hp300_rtc_पढ़ो(RTC_REG_SEC1) * 10 +
		hp300_rtc_पढ़ो(RTC_REG_SEC2);
पूर्ण

अटल व्योम __init hp300_init_IRQ(व्योम)
अणु
पूर्ण

व्योम __init config_hp300(व्योम)
अणु
	mach_sched_init      = hp300_sched_init;
	mach_init_IRQ        = hp300_init_IRQ;
	mach_get_model       = hp300_get_model;
	mach_hwclk	     = hp300_hwclk;
	mach_get_ss	     = hp300_get_ss;
	mach_reset           = hp300_reset;
#अगर_घोषित CONFIG_HEARTBEAT
	mach_heartbeat       = hp300_pulse;
#पूर्ण_अगर

	अगर (hp300_model >= HP_330 && hp300_model <= HP_433S &&
	    hp300_model != HP_350) अणु
		pr_info("Detected HP9000 model %s\n",
			hp300_models[hp300_model-HP_320]);
		म_जोड़ो(hp300_model_name, hp300_models[hp300_model-HP_320]);
	पूर्ण अन्यथा अणु
		panic("Unknown HP9000 Model");
	पूर्ण
#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
	hp300_setup_serial_console();
#पूर्ण_अगर
पूर्ण
