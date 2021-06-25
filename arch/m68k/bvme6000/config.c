<शैली गुरु>
/*
 *  arch/m68k/bvme6000/config.c
 *
 *  Copyright (C) 1997 Riअक्षरd Hirst [riअक्षरd@sleepie.demon.co.uk]
 *
 * Based on:
 *
 *  linux/amiga/config.c
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
#समावेश <linux/bcd.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/bootinfo-vme.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/bvme6000hw.h>

अटल व्योम bvme6000_get_model(अक्षर *model);
बाह्य व्योम bvme6000_sched_init(व्योम);
बाह्य पूर्णांक bvme6000_hwclk (पूर्णांक, काष्ठा rtc_समय *);
बाह्य व्योम bvme6000_reset (व्योम);
व्योम bvme6000_set_vectors (व्योम);


पूर्णांक __init bvme6000_parse_bootinfo(स्थिर काष्ठा bi_record *bi)
अणु
	अगर (be16_to_cpu(bi->tag) == BI_VME_TYPE)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

व्योम bvme6000_reset(व्योम)
अणु
	अस्थिर PitRegsPtr pit = (PitRegsPtr)BVME_PIT_BASE;

	pr_info("\r\n\nCalled bvme6000_reset\r\n"
		"\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r");
	/* The string of वापसs is to delay the reset until the whole
	 * message is output. */
	/* Enable the watchकरोg, via PIT port C bit 4 */

	pit->pcddr	|= 0x10;	/* WDOG enable */

	जबतक(1)
		;
पूर्ण

अटल व्योम bvme6000_get_model(अक्षर *model)
अणु
    प्र_लिखो(model, "BVME%d000", m68k_cputype == CPU_68060 ? 6 : 4);
पूर्ण

/*
 * This function is called during kernel startup to initialize
 * the bvme6000 IRQ handling routines.
 */
अटल व्योम __init bvme6000_init_IRQ(व्योम)
अणु
	m68k_setup_user_पूर्णांकerrupt(VEC_USER, 192);
पूर्ण

व्योम __init config_bvme6000(व्योम)
अणु
    अस्थिर PitRegsPtr pit = (PitRegsPtr)BVME_PIT_BASE;

    /* Board type is only set by newer versions of vmelilo/tftplilo */
    अगर (!vme_brdtype) अणु
	अगर (m68k_cputype == CPU_68060)
	    vme_brdtype = VME_TYPE_BVME6000;
	अन्यथा
	    vme_brdtype = VME_TYPE_BVME4000;
    पूर्ण
#अगर 0
    /* Call bvme6000_set_vectors() so ABORT will work, aदीर्घ with BVMBug
     * debugger.  Note trap_init() will splat the पात vector, but
     * bvme6000_init_IRQ() will put it back again.  Hopefully. */

    bvme6000_set_vectors();
#पूर्ण_अगर

    mach_sched_init      = bvme6000_sched_init;
    mach_init_IRQ        = bvme6000_init_IRQ;
    mach_hwclk           = bvme6000_hwclk;
    mach_reset		 = bvme6000_reset;
    mach_get_model       = bvme6000_get_model;

    pr_info("Board is %sconfigured as a System Controller\n",
	    *config_reg_ptr & BVME_CONFIG_SW1 ? "" : "not ");

    /* Now करो the PIT configuration */

    pit->pgcr	= 0x00;	/* Unidirectional 8 bit, no handshake क्रम now */
    pit->psrr	= 0x18;	/* PIACK and PIRQ functions enabled */
    pit->pacr	= 0x00;	/* Sub Mode 00, H2 i/p, no DMA */
    pit->padr	= 0x00;	/* Just to be tidy! */
    pit->paddr	= 0x00;	/* All inमाला_दो क्रम now (safest) */
    pit->pbcr	= 0x80;	/* Sub Mode 1x, H4 i/p, no DMA */
    pit->pbdr	= 0xbc | (*config_reg_ptr & BVME_CONFIG_SW1 ? 0 : 0x40);
			/* PRI, SYSCON?, Level3, SCC clks from xtal */
    pit->pbddr	= 0xf3;	/* Mostly outमाला_दो */
    pit->pcdr	= 0x01;	/* PA transceiver disabled */
    pit->pcddr	= 0x03;	/* WDOG disable */

    /* Disable snooping क्रम Ethernet and VME accesses */

    bvme_acr_addrctl = 0;
पूर्ण


irqवापस_t bvme6000_पात_पूर्णांक (पूर्णांक irq, व्योम *dev_id)
अणु
        अचिन्हित दीर्घ *new = (अचिन्हित दीर्घ *)vectors;
        अचिन्हित दीर्घ *old = (अचिन्हित दीर्घ *)0xf8000000;

        /* Wait क्रम button release */
        जबतक (*(अस्थिर अचिन्हित अक्षर *)BVME_LOCAL_IRQ_STAT & BVME_ABORT_STATUS)
                ;

        *(new+4) = *(old+4);            /* Illegal inकाष्ठाion */
        *(new+9) = *(old+9);            /* Trace */
        *(new+47) = *(old+47);          /* Trap #15 */
        *(new+0x1f) = *(old+0x1f);      /* ABORT चयन */
	वापस IRQ_HANDLED;
पूर्ण

अटल u64 bvme6000_पढ़ो_clk(काष्ठा घड़ीsource *cs);

अटल काष्ठा घड़ीsource bvme6000_clk = अणु
	.name   = "rtc",
	.rating = 250,
	.पढ़ो   = bvme6000_पढ़ो_clk,
	.mask   = CLOCKSOURCE_MASK(32),
	.flags  = CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल u32 clk_total, clk_offset;

#घोषणा RTC_TIMER_CLOCK_FREQ 8000000
#घोषणा RTC_TIMER_CYCLES     (RTC_TIMER_CLOCK_FREQ / HZ)
#घोषणा RTC_TIMER_COUNT      ((RTC_TIMER_CYCLES / 2) - 1)

अटल irqवापस_t bvme6000_समयr_पूर्णांक (पूर्णांक irq, व्योम *dev_id)
अणु
    अचिन्हित दीर्घ flags;
    अस्थिर RtcPtr_t rtc = (RtcPtr_t)BVME_RTC_BASE;
    अचिन्हित अक्षर msr;

    local_irq_save(flags);
    msr = rtc->msr & 0xc0;
    rtc->msr = msr | 0x20;		/* Ack the पूर्णांकerrupt */
    clk_total += RTC_TIMER_CYCLES;
    clk_offset = 0;
    legacy_समयr_tick(1);
    local_irq_restore(flags);

    वापस IRQ_HANDLED;
पूर्ण

/*
 * Set up the RTC समयr 1 to mode 2, so T1 output toggles every 5ms
 * (40000 x 125ns).  It will पूर्णांकerrupt every 10ms, when T1 goes low.
 * So, when पढ़ोing the elapsed समय, you should पढ़ो समयr1,
 * subtract it from 39999, and then add 40000 अगर T1 is high.
 * That gives you the number of 125ns ticks in to the 10ms period,
 * so भागide by 8 to get the microsecond result.
 */

व्योम bvme6000_sched_init (व्योम)
अणु
    अस्थिर RtcPtr_t rtc = (RtcPtr_t)BVME_RTC_BASE;
    अचिन्हित अक्षर msr = rtc->msr & 0xc0;

    rtc->msr = 0;	/* Ensure समयr रेजिस्टरs accessible */

    अगर (request_irq(BVME_IRQ_RTC, bvme6000_समयr_पूर्णांक, IRQF_TIMER, "timer",
                    शून्य))
	panic ("Couldn't register timer int");

    rtc->t1cr_omr = 0x04;	/* Mode 2, ext clk */
    rtc->t1msb = RTC_TIMER_COUNT >> 8;
    rtc->t1lsb = RTC_TIMER_COUNT & 0xff;
    rtc->irr_icr1 &= 0xef;	/* Route समयr 1 to INTR pin */
    rtc->msr = 0x40;		/* Access पूर्णांक.cntrl, etc */
    rtc->pfr_icr0 = 0x80;	/* Just समयr 1 पूर्णांकs enabled */
    rtc->irr_icr1 = 0;
    rtc->t1cr_omr = 0x0a;	/* INTR+T1 active lo, push-pull */
    rtc->t0cr_rपंचांगr &= 0xdf;	/* Stop समयrs in standby */
    rtc->msr = 0;		/* Access समयr 1 control */
    rtc->t1cr_omr = 0x05;	/* Mode 2, ext clk, GO */

    rtc->msr = msr;

    घड़ीsource_रेजिस्टर_hz(&bvme6000_clk, RTC_TIMER_CLOCK_FREQ);

    अगर (request_irq(BVME_IRQ_ABORT, bvme6000_पात_पूर्णांक, 0,
				"abort", bvme6000_पात_पूर्णांक))
	panic ("Couldn't register abort int");
पूर्ण


/*
 * NOTE:  Don't accept any पढ़ोings within 5us of rollover, as
 * the T1INT bit may be a little slow getting set.  There is also
 * a fault in the chip, meaning that पढ़ोs may produce invalid
 * results...
 */

अटल u64 bvme6000_पढ़ो_clk(काष्ठा घड़ीsource *cs)
अणु
    अचिन्हित दीर्घ flags;
    अस्थिर RtcPtr_t rtc = (RtcPtr_t)BVME_RTC_BASE;
    अस्थिर PitRegsPtr pit = (PitRegsPtr)BVME_PIT_BASE;
    अचिन्हित अक्षर msr, msb;
    अचिन्हित अक्षर t1पूर्णांक, t1op;
    u32 v = 800000, ov;

    local_irq_save(flags);

    msr = rtc->msr & 0xc0;
    rtc->msr = 0;	/* Ensure समयr रेजिस्टरs accessible */

    करो अणु
	ov = v;
	t1पूर्णांक = rtc->msr & 0x20;
	t1op  = pit->pcdr & 0x04;
	rtc->t1cr_omr |= 0x40;		/* Latch समयr1 */
	msb = rtc->t1msb;		/* Read समयr1 */
	v = (msb << 8) | rtc->t1lsb;	/* Read समयr1 */
    पूर्ण जबतक (t1पूर्णांक != (rtc->msr & 0x20) ||
		t1op != (pit->pcdr & 0x04) ||
			असल(ov-v) > 80 ||
				v > RTC_TIMER_COUNT - (RTC_TIMER_COUNT / 100));

    v = RTC_TIMER_COUNT - v;
    अगर (!t1op)				/* If in second half cycle.. */
	v += RTC_TIMER_CYCLES / 2;
    अगर (msb > 0 && t1पूर्णांक)
	clk_offset = RTC_TIMER_CYCLES;
    rtc->msr = msr;

    v += clk_offset + clk_total;

    local_irq_restore(flags);

    वापस v;
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

पूर्णांक bvme6000_hwclk(पूर्णांक op, काष्ठा rtc_समय *t)
अणु
	अस्थिर RtcPtr_t rtc = (RtcPtr_t)BVME_RTC_BASE;
	अचिन्हित अक्षर msr = rtc->msr & 0xc0;

	rtc->msr = 0x40;	/* Ensure घड़ी and real-समय-mode-रेजिस्टर
				 * are accessible */
	अगर (op)
	अणु	/* Write.... */
		rtc->t0cr_rपंचांगr = t->पंचांग_year%4;
		rtc->bcd_tenms = 0;
		rtc->bcd_sec = bin2bcd(t->पंचांग_sec);
		rtc->bcd_min = bin2bcd(t->पंचांग_min);
		rtc->bcd_hr  = bin2bcd(t->पंचांग_hour);
		rtc->bcd_करोm = bin2bcd(t->पंचांग_mday);
		rtc->bcd_mth = bin2bcd(t->पंचांग_mon + 1);
		rtc->bcd_year = bin2bcd(t->पंचांग_year%100);
		अगर (t->पंचांग_wday >= 0)
			rtc->bcd_करोw = bin2bcd(t->पंचांग_wday+1);
		rtc->t0cr_rपंचांगr = t->पंचांग_year%4 | 0x08;
	पूर्ण
	अन्यथा
	अणु	/* Read....  */
		करो अणु
			t->पंचांग_sec  = bcd2bin(rtc->bcd_sec);
			t->पंचांग_min  = bcd2bin(rtc->bcd_min);
			t->पंचांग_hour = bcd2bin(rtc->bcd_hr);
			t->पंचांग_mday = bcd2bin(rtc->bcd_करोm);
			t->पंचांग_mon  = bcd2bin(rtc->bcd_mth)-1;
			t->पंचांग_year = bcd2bin(rtc->bcd_year);
			अगर (t->पंचांग_year < 70)
				t->पंचांग_year += 100;
			t->पंचांग_wday = bcd2bin(rtc->bcd_करोw)-1;
		पूर्ण जबतक (t->पंचांग_sec != bcd2bin(rtc->bcd_sec));
	पूर्ण

	rtc->msr = msr;

	वापस 0;
पूर्ण
