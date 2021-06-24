<शैली गुरु>
/*
 *  arch/m68k/q40/config.c
 *
 *  Copyright (C) 1999 Riअक्षरd Zidlicky
 *
 * originally based on:
 *
 *  linux/bvme/config.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file README.legal in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/tty.h>
#समावेश <linux/console.h>
#समावेश <linux/linkage.h>
#समावेश <linux/init.h>
#समावेश <linux/major.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/rtc.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/bcd.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/q40_master.h>

बाह्य व्योम q40_init_IRQ(व्योम);
अटल व्योम q40_get_model(अक्षर *model);
बाह्य व्योम q40_sched_init(व्योम);

अटल पूर्णांक q40_hwclk(पूर्णांक, काष्ठा rtc_समय *);
अटल अचिन्हित पूर्णांक q40_get_ss(व्योम);
अटल पूर्णांक q40_get_rtc_pll(काष्ठा rtc_pll_info *pll);
अटल पूर्णांक q40_set_rtc_pll(काष्ठा rtc_pll_info *pll);

बाह्य व्योम q40_mksound(अचिन्हित पूर्णांक /*freq*/, अचिन्हित पूर्णांक /*ticks*/);

अटल व्योम q40_mem_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *b,
				  अचिन्हित पूर्णांक count);

बाह्य पूर्णांक ql_ticks;

अटल काष्ठा console q40_console_driver = अणु
	.name	= "debug",
	.ग_लिखो	= q40_mem_console_ग_लिखो,
	.flags	= CON_PRINTBUFFER,
	.index	= -1,
पूर्ण;


/* early debugging function:*/
बाह्य अक्षर *q40_mem_cptr; /*=(अक्षर *)0xff020000;*/
अटल पूर्णांक _cpleft;

अटल व्योम q40_mem_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				  अचिन्हित पूर्णांक count)
अणु
	स्थिर अक्षर *p = s;

	अगर (count < _cpleft) अणु
		जबतक (count-- > 0) अणु
			*q40_mem_cptr = *p++;
			q40_mem_cptr += 4;
			_cpleft--;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init q40_debug_setup(अक्षर *arg)
अणु
	/* useful क्रम early debugging stages - ग_लिखोs kernel messages पूर्णांकo SRAM */
	अगर (MACH_IS_Q40 && !म_भेदन(arg, "mem", 3)) अणु
		/*pr_info("using NVRAM debug, q40_mem_cptr=%p\n",q40_mem_cptr);*/
		_cpleft = 2000 - ((दीर्घ)q40_mem_cptr-0xff020000) / 4;
		रेजिस्टर_console(&q40_console_driver);
	पूर्ण
	वापस 0;
पूर्ण

early_param("debug", q40_debug_setup);

#अगर 0
व्योम prपूर्णांकq40(अक्षर *str)
अणु
	पूर्णांक l = म_माप(str);
	अक्षर *p = q40_mem_cptr;

	जबतक (l-- > 0 && _cpleft-- > 0) अणु
		*p = *str++;
		p += 4;
	पूर्ण
	q40_mem_cptr = p;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक halted;

#अगर_घोषित CONFIG_HEARTBEAT
अटल व्योम q40_heartbeat(पूर्णांक on)
अणु
	अगर (halted)
		वापस;

	अगर (on)
		Q40_LED_ON();
	अन्यथा
		Q40_LED_OFF();
पूर्ण
#पूर्ण_अगर

अटल व्योम q40_reset(व्योम)
अणु
	halted = 1;
	pr_info("*******************************************\n"
		"Called q40_reset : press the RESET button!!\n"
		"*******************************************\n");
	Q40_LED_ON();
	जबतक (1)
		;
पूर्ण

अटल व्योम q40_halt(व्योम)
अणु
	halted = 1;
	pr_info("*******************\n"
		"  Called q40_halt\n"
		"*******************\n");
	Q40_LED_ON();
	जबतक (1)
		;
पूर्ण

अटल व्योम q40_get_model(अक्षर *model)
अणु
	प्र_लिखो(model, "Q40");
पूर्ण

अटल अचिन्हित पूर्णांक serports[] =
अणु
	0x3f8,0x2f8,0x3e8,0x2e8,0
पूर्ण;

अटल व्योम __init q40_disable_irqs(व्योम)
अणु
	अचिन्हित i, j;

	j = 0;
	जबतक ((i = serports[j++]))
		outb(0, i + UART_IER);
	master_outb(0, EXT_ENABLE_REG);
	master_outb(0, KEY_IRQ_ENABLE_REG);
पूर्ण

व्योम __init config_q40(व्योम)
अणु
	mach_sched_init = q40_sched_init;

	mach_init_IRQ = q40_init_IRQ;
	mach_hwclk = q40_hwclk;
	mach_get_ss = q40_get_ss;
	mach_get_rtc_pll = q40_get_rtc_pll;
	mach_set_rtc_pll = q40_set_rtc_pll;

	mach_reset = q40_reset;
	mach_get_model = q40_get_model;

#अगर IS_ENABLED(CONFIG_INPUT_M68K_BEEP)
	mach_beep = q40_mksound;
#पूर्ण_अगर
#अगर_घोषित CONFIG_HEARTBEAT
	mach_heartbeat = q40_heartbeat;
#पूर्ण_अगर
	mach_halt = q40_halt;

	/* disable a few things that SMSQ might have left enabled */
	q40_disable_irqs();
पूर्ण


पूर्णांक __init q40_parse_bootinfo(स्थिर काष्ठा bi_record *rec)
अणु
	वापस 1;
पूर्ण

/*
 * Looks like op is non-zero क्रम setting the घड़ी, and zero क्रम
 * पढ़ोing the घड़ी.
 *
 *  काष्ठा hwclk_समय अणु
 *         अचिन्हित        sec;       0..59
 *         अचिन्हित        min;       0..59
 *         अचिन्हित        hour;      0..23
 *         अचिन्हित        day;       1..31
 *         अचिन्हित        mon;       0..11
 *         अचिन्हित        year;      00...
 *         पूर्णांक             wday;      0..6, 0 is Sunday, -1 means unknown/करोn't set
 * पूर्ण;
 */

अटल पूर्णांक q40_hwclk(पूर्णांक op, काष्ठा rtc_समय *t)
अणु
	अगर (op) अणु
		/* Write.... */
		Q40_RTC_CTRL |= Q40_RTC_WRITE;

		Q40_RTC_SECS = bin2bcd(t->पंचांग_sec);
		Q40_RTC_MINS = bin2bcd(t->पंचांग_min);
		Q40_RTC_HOUR = bin2bcd(t->पंचांग_hour);
		Q40_RTC_DATE = bin2bcd(t->पंचांग_mday);
		Q40_RTC_MNTH = bin2bcd(t->पंचांग_mon + 1);
		Q40_RTC_YEAR = bin2bcd(t->पंचांग_year%100);
		अगर (t->पंचांग_wday >= 0)
			Q40_RTC_DOW = bin2bcd(t->पंचांग_wday+1);

		Q40_RTC_CTRL &= ~(Q40_RTC_WRITE);
	पूर्ण अन्यथा अणु
		/* Read....  */
		Q40_RTC_CTRL |= Q40_RTC_READ;

		t->पंचांग_year = bcd2bin (Q40_RTC_YEAR);
		t->पंचांग_mon  = bcd2bin (Q40_RTC_MNTH)-1;
		t->पंचांग_mday = bcd2bin (Q40_RTC_DATE);
		t->पंचांग_hour = bcd2bin (Q40_RTC_HOUR);
		t->पंचांग_min  = bcd2bin (Q40_RTC_MINS);
		t->पंचांग_sec  = bcd2bin (Q40_RTC_SECS);

		Q40_RTC_CTRL &= ~(Q40_RTC_READ);

		अगर (t->पंचांग_year < 70)
			t->पंचांग_year += 100;
		t->पंचांग_wday = bcd2bin(Q40_RTC_DOW)-1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक q40_get_ss(व्योम)
अणु
	वापस bcd2bin(Q40_RTC_SECS);
पूर्ण

/* get and set PLL calibration of RTC घड़ी */
#घोषणा Q40_RTC_PLL_MASK ((1<<5)-1)
#घोषणा Q40_RTC_PLL_SIGN (1<<5)

अटल पूर्णांक q40_get_rtc_pll(काष्ठा rtc_pll_info *pll)
अणु
	पूर्णांक पंचांगp = Q40_RTC_CTRL;

	pll->pll_ctrl = 0;
	pll->pll_value = पंचांगp & Q40_RTC_PLL_MASK;
	अगर (पंचांगp & Q40_RTC_PLL_SIGN)
		pll->pll_value = -pll->pll_value;
	pll->pll_max = 31;
	pll->pll_min = -31;
	pll->pll_posmult = 512;
	pll->pll_negmult = 256;
	pll->pll_घड़ी = 125829120;

	वापस 0;
पूर्ण

अटल पूर्णांक q40_set_rtc_pll(काष्ठा rtc_pll_info *pll)
अणु
	अगर (!pll->pll_ctrl) अणु
		/* the करोcs are a bit unclear so I am द्विगुनsetting */
		/* RTC_WRITE here ... */
		पूर्णांक पंचांगp = (pll->pll_value & 31) | (pll->pll_value<0 ? 32 : 0) |
			  Q40_RTC_WRITE;
		Q40_RTC_CTRL |= Q40_RTC_WRITE;
		Q40_RTC_CTRL = पंचांगp;
		Q40_RTC_CTRL &= ~(Q40_RTC_WRITE);
		वापस 0;
	पूर्ण अन्यथा
		वापस -EINVAL;
पूर्ण

अटल __init पूर्णांक q40_add_kbd_device(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;

	अगर (!MACH_IS_Q40)
		वापस -ENODEV;

	pdev = platक्रमm_device_रेजिस्टर_simple("q40kbd", -1, शून्य, 0);
	वापस PTR_ERR_OR_ZERO(pdev);
पूर्ण
arch_initcall(q40_add_kbd_device);
