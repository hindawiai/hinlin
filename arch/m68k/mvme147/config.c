<शैली गुरु>
/*
 *  arch/m68k/mvme147/config.c
 *
 *  Copyright (C) 1996 Dave Frascone [chaos@mindspring.com]
 *  Cloned from        Riअक्षरd Hirst [riअक्षरd@sleepie.demon.co.uk]
 *
 * Based on:
 *
 *  Copyright (C) 1993 Hamish Macकरोnald
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file README.legal in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/tty.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/console.h>
#समावेश <linux/linkage.h>
#समावेश <linux/init.h>
#समावेश <linux/major.h>
#समावेश <linux/genhd.h>
#समावेश <linux/rtc.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/bootinfo-vme.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mvme147hw.h>


अटल व्योम mvme147_get_model(अक्षर *model);
बाह्य व्योम mvme147_sched_init(व्योम);
बाह्य पूर्णांक mvme147_hwclk (पूर्णांक, काष्ठा rtc_समय *);
बाह्य व्योम mvme147_reset (व्योम);


अटल पूर्णांक bcd2पूर्णांक (अचिन्हित अक्षर b);


पूर्णांक __init mvme147_parse_bootinfo(स्थिर काष्ठा bi_record *bi)
अणु
	uपूर्णांक16_t tag = be16_to_cpu(bi->tag);
	अगर (tag == BI_VME_TYPE || tag == BI_VME_BRDINFO)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

व्योम mvme147_reset(व्योम)
अणु
	pr_info("\r\n\nCalled mvme147_reset\r\n");
	m147_pcc->watchकरोg = 0x0a;	/* Clear समयr */
	m147_pcc->watchकरोg = 0xa5;	/* Enable watchकरोg - 100ms to reset */
	जबतक (1)
		;
पूर्ण

अटल व्योम mvme147_get_model(अक्षर *model)
अणु
	प्र_लिखो(model, "Motorola MVME147");
पूर्ण

/*
 * This function is called during kernel startup to initialize
 * the mvme147 IRQ handling routines.
 */

व्योम __init mvme147_init_IRQ(व्योम)
अणु
	m68k_setup_user_पूर्णांकerrupt(VEC_USER, 192);
पूर्ण

व्योम __init config_mvme147(व्योम)
अणु
	mach_sched_init		= mvme147_sched_init;
	mach_init_IRQ		= mvme147_init_IRQ;
	mach_hwclk		= mvme147_hwclk;
	mach_reset		= mvme147_reset;
	mach_get_model		= mvme147_get_model;

	/* Board type is only set by newer versions of vmelilo/tftplilo */
	अगर (!vme_brdtype)
		vme_brdtype = VME_TYPE_MVME147;
पूर्ण

अटल u64 mvme147_पढ़ो_clk(काष्ठा घड़ीsource *cs);

अटल काष्ठा घड़ीsource mvme147_clk = अणु
	.name   = "pcc",
	.rating = 250,
	.पढ़ो   = mvme147_पढ़ो_clk,
	.mask   = CLOCKSOURCE_MASK(32),
	.flags  = CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल u32 clk_total;

#घोषणा PCC_TIMER_CLOCK_FREQ 160000
#घोषणा PCC_TIMER_CYCLES     (PCC_TIMER_CLOCK_FREQ / HZ)
#घोषणा PCC_TIMER_PRELOAD    (0x10000 - PCC_TIMER_CYCLES)

/* Using pcc tick समयr 1 */

अटल irqवापस_t mvme147_समयr_पूर्णांक (पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	m147_pcc->t1_cntrl = PCC_TIMER_CLR_OVF | PCC_TIMER_COC_EN |
			     PCC_TIMER_TIC_EN;
	m147_pcc->t1_पूर्णांक_cntrl = PCC_INT_ENAB | PCC_TIMER_INT_CLR |
				 PCC_LEVEL_TIMER1;
	clk_total += PCC_TIMER_CYCLES;
	legacy_समयr_tick(1);
	local_irq_restore(flags);

	वापस IRQ_HANDLED;
पूर्ण


व्योम mvme147_sched_init (व्योम)
अणु
	अगर (request_irq(PCC_IRQ_TIMER1, mvme147_समयr_पूर्णांक, IRQF_TIMER,
			"timer 1", शून्य))
		pr_err("Couldn't register timer interrupt\n");

	/* Init the घड़ी with a value */
	/* The घड़ी counter increments until 0xFFFF then reloads */
	m147_pcc->t1_preload = PCC_TIMER_PRELOAD;
	m147_pcc->t1_cntrl = PCC_TIMER_CLR_OVF | PCC_TIMER_COC_EN |
			     PCC_TIMER_TIC_EN;
	m147_pcc->t1_पूर्णांक_cntrl = PCC_INT_ENAB | PCC_TIMER_INT_CLR |
				 PCC_LEVEL_TIMER1;

	घड़ीsource_रेजिस्टर_hz(&mvme147_clk, PCC_TIMER_CLOCK_FREQ);
पूर्ण

अटल u64 mvme147_पढ़ो_clk(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ flags;
	u8 overflow, पंचांगp;
	u16 count;
	u32 ticks;

	local_irq_save(flags);
	पंचांगp = m147_pcc->t1_cntrl >> 4;
	count = m147_pcc->t1_count;
	overflow = m147_pcc->t1_cntrl >> 4;
	अगर (overflow != पंचांगp)
		count = m147_pcc->t1_count;
	count -= PCC_TIMER_PRELOAD;
	ticks = count + overflow * PCC_TIMER_CYCLES;
	ticks += clk_total;
	local_irq_restore(flags);

	वापस ticks;
पूर्ण

अटल पूर्णांक bcd2पूर्णांक (अचिन्हित अक्षर b)
अणु
	वापस ((b>>4)*10 + (b&15));
पूर्ण

पूर्णांक mvme147_hwclk(पूर्णांक op, काष्ठा rtc_समय *t)
अणु
#warning check me!
	अगर (!op) अणु
		m147_rtc->ctrl = RTC_READ;
		t->पंचांग_year = bcd2पूर्णांक (m147_rtc->bcd_year);
		t->पंचांग_mon  = bcd2पूर्णांक(m147_rtc->bcd_mth) - 1;
		t->पंचांग_mday = bcd2पूर्णांक (m147_rtc->bcd_करोm);
		t->पंचांग_hour = bcd2पूर्णांक (m147_rtc->bcd_hr);
		t->पंचांग_min  = bcd2पूर्णांक (m147_rtc->bcd_min);
		t->पंचांग_sec  = bcd2पूर्णांक (m147_rtc->bcd_sec);
		m147_rtc->ctrl = 0;
		अगर (t->पंचांग_year < 70)
			t->पंचांग_year += 100;
	पूर्ण
	वापस 0;
पूर्ण
