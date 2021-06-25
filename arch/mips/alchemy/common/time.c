<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008-2009 Manuel Lauss <manuel.lauss@gmail.com>
 *
 * Previous incarnations were:
 * Copyright (C) 2001, 2006, 2008 MontaVista Software, <source@mvista.com>
 * Copied and modअगरied Carsten Langgaard's समय.c
 *
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.
 *
 * ########################################################################
 *
 * ########################################################################
 *
 * Clocksource/event using the 32.768kHz-घड़ीed Counter1 ('RTC' in the
 * databooks).  Firmware/Board init code must enable the counters in the
 * counter control रेजिस्टर, otherwise the CP0 counter घड़ीsource/event
 * will be installed instead (and use of 'wait' inकाष्ठाion is prohibited).
 */

#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mach-au1x00/au1000.h>

/* 32kHz घड़ी enabled and detected */
#घोषणा CNTR_OK (SYS_CNTRL_E0 | SYS_CNTRL_32S)

अटल u64 au1x_counter1_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस alchemy_rdsys(AU1000_SYS_RTCREAD);
पूर्ण

अटल काष्ठा घड़ीsource au1x_counter1_घड़ीsource = अणु
	.name		= "alchemy-counter1",
	.पढ़ो		= au1x_counter1_पढ़ो,
	.mask		= CLOCKSOURCE_MASK(32),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
	.rating		= 1500,
पूर्ण;

अटल पूर्णांक au1x_rtcmatch2_set_next_event(अचिन्हित दीर्घ delta,
					 काष्ठा घड़ी_event_device *cd)
अणु
	delta += alchemy_rdsys(AU1000_SYS_RTCREAD);
	/* रुको क्रम रेजिस्टर access */
	जबतक (alchemy_rdsys(AU1000_SYS_CNTRCTRL) & SYS_CNTRL_M21)
		;
	alchemy_wrsys(delta, AU1000_SYS_RTCMATCH2);

	वापस 0;
पूर्ण

अटल irqवापस_t au1x_rtcmatch2_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *cd = dev_id;
	cd->event_handler(cd);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा घड़ी_event_device au1x_rtcmatch2_घड़ीdev = अणु
	.name		= "rtcmatch2",
	.features	= CLOCK_EVT_FEAT_ONESHOT,
	.rating		= 1500,
	.set_next_event = au1x_rtcmatch2_set_next_event,
	.cpumask	= cpu_possible_mask,
पूर्ण;

अटल पूर्णांक __init alchemy_समय_init(अचिन्हित पूर्णांक m2पूर्णांक)
अणु
	काष्ठा घड़ी_event_device *cd = &au1x_rtcmatch2_घड़ीdev;
	अचिन्हित दीर्घ t;

	au1x_rtcmatch2_घड़ीdev.irq = m2पूर्णांक;

	/* Check अगर firmware (YAMON, ...) has enabled 32kHz and घड़ी
	 * has been detected.  If so install the rtcmatch2 घड़ीsource,
	 * otherwise करोn't bother.  Note that both bits being set is by
	 * no means a definite guarantee that the counters actually work
	 * (the 32S bit seems to be stuck set to 1 once a single घड़ी-
	 * edge is detected, hence the समयouts).
	 */
	अगर (CNTR_OK != (alchemy_rdsys(AU1000_SYS_CNTRCTRL) & CNTR_OK))
		जाओ cntr_err;

	/*
	 * setup counter 1 (RTC) to tick at full speed
	 */
	t = 0xffffff;
	जबतक ((alchemy_rdsys(AU1000_SYS_CNTRCTRL) & SYS_CNTRL_T1S) && --t)
		यंत्र अस्थिर ("nop");
	अगर (!t)
		जाओ cntr_err;

	alchemy_wrsys(0, AU1000_SYS_RTCTRIM);	/* 32.768 kHz */

	t = 0xffffff;
	जबतक ((alchemy_rdsys(AU1000_SYS_CNTRCTRL) & SYS_CNTRL_C1S) && --t)
		यंत्र अस्थिर ("nop");
	अगर (!t)
		जाओ cntr_err;
	alchemy_wrsys(0, AU1000_SYS_RTCWRITE);

	t = 0xffffff;
	जबतक ((alchemy_rdsys(AU1000_SYS_CNTRCTRL) & SYS_CNTRL_C1S) && --t)
		यंत्र अस्थिर ("nop");
	अगर (!t)
		जाओ cntr_err;

	/* रेजिस्टर counter1 घड़ीsource and event device */
	घड़ीsource_रेजिस्टर_hz(&au1x_counter1_घड़ीsource, 32768);

	cd->shअगरt = 32;
	cd->mult = भाग_sc(32768, NSEC_PER_SEC, cd->shअगरt);
	cd->max_delta_ns = घड़ीevent_delta2ns(0xffffffff, cd);
	cd->max_delta_ticks = 0xffffffff;
	cd->min_delta_ns = घड़ीevent_delta2ns(9, cd);
	cd->min_delta_ticks = 9;	/* ~0.28ms */
	घड़ीevents_रेजिस्टर_device(cd);
	अगर (request_irq(m2पूर्णांक, au1x_rtcmatch2_irq, IRQF_TIMER, "timer",
			&au1x_rtcmatch2_घड़ीdev))
		pr_err("Failed to register timer interrupt\n");

	prपूर्णांकk(KERN_INFO "Alchemy clocksource installed\n");

	वापस 0;

cntr_err:
	वापस -1;
पूर्ण

अटल पूर्णांक alchemy_m2पूर्णांकtab[] __initdata = अणु
	AU1000_RTC_MATCH2_INT,
	AU1500_RTC_MATCH2_INT,
	AU1100_RTC_MATCH2_INT,
	AU1550_RTC_MATCH2_INT,
	AU1200_RTC_MATCH2_INT,
	AU1300_RTC_MATCH2_INT,
पूर्ण;

व्योम __init plat_समय_init(व्योम)
अणु
	पूर्णांक t;

	t = alchemy_get_cputype();
	अगर (t == ALCHEMY_CPU_UNKNOWN ||
	    alchemy_समय_init(alchemy_m2पूर्णांकtab[t]))
		cpu_रुको = शून्य;	/* रुको करोesn't work with r4k समयr */
पूर्ण
