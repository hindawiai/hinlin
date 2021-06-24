<शैली गुरु>
/***************************************************************************/

/*
 *  समयrs.c - Generic hardware समयr support.
 *
 *  Copyright (C) 1993 Hamish Macकरोnald
 *  Copyright (C) 1999 D. Jeff Dionne
 *  Copyright (C) 2001 Georges Menie, Ken Desmet
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

/***************************************************************************/

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/rtc.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/MC68VZ328.h>

/***************************************************************************/

#अगर defined(CONFIG_DRAGEN2)
/* with a 33.16 MHz घड़ी, this will give usec resolution to the समय functions */
#घोषणा CLOCK_SOURCE	TCTL_CLKSOURCE_SYSCLK
#घोषणा CLOCK_PRE	7
#घोषणा TICKS_PER_JIFFY	41450

#या_अगर defined(CONFIG_XCOPILOT_BUGS)
/*
 * The only thing I know is that CLK32 is not available on Xcopilot
 * I have little idea about what frequency SYSCLK has on Xcopilot.
 * The values क्रम prescaler and compare रेजिस्टरs were simply
 * taken from the original source
 */
#घोषणा CLOCK_SOURCE	TCTL_CLKSOURCE_SYSCLK
#घोषणा CLOCK_PRE	2
#घोषणा TICKS_PER_JIFFY	0xd7e4

#अन्यथा
/* शेष to using the 32Khz घड़ी */
#घोषणा CLOCK_SOURCE	TCTL_CLKSOURCE_32KHZ
#घोषणा CLOCK_PRE	31
#घोषणा TICKS_PER_JIFFY	10
#पूर्ण_अगर

अटल u32 m68328_tick_cnt;

/***************************************************************************/

अटल irqवापस_t hw_tick(पूर्णांक irq, व्योम *dummy)
अणु
	/* Reset Timer1 */
	TSTAT &= 0;

	m68328_tick_cnt += TICKS_PER_JIFFY;
	legacy_समयr_tick(1);
	वापस IRQ_HANDLED;
पूर्ण

/***************************************************************************/

अटल u64 m68328_पढ़ो_clk(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ flags;
	u32 cycles;

	local_irq_save(flags);
	cycles = m68328_tick_cnt + TCN;
	local_irq_restore(flags);

	वापस cycles;
पूर्ण

/***************************************************************************/

अटल काष्ठा घड़ीsource m68328_clk = अणु
	.name	= "timer",
	.rating	= 250,
	.पढ़ो	= m68328_पढ़ो_clk,
	.mask	= CLOCKSOURCE_MASK(32),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

/***************************************************************************/

व्योम hw_समयr_init(व्योम)
अणु
	पूर्णांक ret;

	/* disable समयr 1 */
	TCTL = 0;

	/* set ISR */
	ret = request_irq(TMR_IRQ_NUM, hw_tick, IRQF_TIMER, "timer", शून्य);
	अगर (ret) अणु
		pr_err("Failed to request irq %d (timer): %pe\n", TMR_IRQ_NUM,
		       ERR_PTR(ret));
	पूर्ण

	/* Restart mode, Enable पूर्णांक, Set घड़ी source */
	TCTL = TCTL_OM | TCTL_IRQEN | CLOCK_SOURCE;
	TPRER = CLOCK_PRE;
	TCMP = TICKS_PER_JIFFY;

	/* Enable समयr 1 */
	TCTL |= TCTL_TEN;
	घड़ीsource_रेजिस्टर_hz(&m68328_clk, TICKS_PER_JIFFY*HZ);
पूर्ण

/***************************************************************************/

पूर्णांक m68328_hwclk(पूर्णांक set, काष्ठा rtc_समय *t)
अणु
	अगर (!set) अणु
		दीर्घ now = RTCTIME;
		t->पंचांग_year = 1;
		t->पंचांग_mon = 0;
		t->पंचांग_mday = 1;
		t->पंचांग_hour = (now >> 24) % 24;
		t->पंचांग_min = (now >> 16) % 60;
		t->पंचांग_sec = now % 60;
	पूर्ण

	वापस 0;
पूर्ण

/***************************************************************************/
