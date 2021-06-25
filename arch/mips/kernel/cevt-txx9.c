<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Based on linux/arch/mips/kernel/cevt-r4k.c,
 *	    linux/arch/mips/jmr3927/rbhma3100/setup.c
 *
 * Copyright 2001 MontaVista Software Inc.
 * Copyright (C) 2000-2001 Toshiba Corporation
 * Copyright (C) 2007 MIPS Technologies, Inc.
 * Copyright (C) 2007 Ralf Baechle <ralf@linux-mips.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/txx9पंचांगr.h>

#घोषणा TCR_BASE (TXx9_TMTCR_CCDE | TXx9_TMTCR_CRE | TXx9_TMTCR_TMODE_ITVL)
#घोषणा TIMER_CCD	0	/* 1/2 */
#घोषणा TIMER_CLK(imclk)	((imclk) / (2 << TIMER_CCD))

काष्ठा txx9_घड़ीsource अणु
	काष्ठा घड़ीsource cs;
	काष्ठा txx9_पंचांगr_reg __iomem *पंचांगrptr;
पूर्ण;

अटल u64 txx9_cs_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा txx9_घड़ीsource *txx9_cs =
		container_of(cs, काष्ठा txx9_घड़ीsource, cs);
	वापस __raw_पढ़ोl(&txx9_cs->पंचांगrptr->trr);
पूर्ण

/* Use 1 bit smaller width to use full bits in that width */
#घोषणा TXX9_CLOCKSOURCE_BITS (TXX9_TIMER_BITS - 1)

अटल काष्ठा txx9_घड़ीsource txx9_घड़ीsource = अणु
	.cs = अणु
		.name		= "TXx9",
		.rating		= 200,
		.पढ़ो		= txx9_cs_पढ़ो,
		.mask		= CLOCKSOURCE_MASK(TXX9_CLOCKSOURCE_BITS),
		.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
	पूर्ण,
पूर्ण;

अटल u64 notrace txx9_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस __raw_पढ़ोl(&txx9_घड़ीsource.पंचांगrptr->trr);
पूर्ण

व्योम __init txx9_घड़ीsource_init(अचिन्हित दीर्घ baseaddr,
				  अचिन्हित पूर्णांक imbusclk)
अणु
	काष्ठा txx9_पंचांगr_reg __iomem *पंचांगrptr;

	घड़ीsource_रेजिस्टर_hz(&txx9_घड़ीsource.cs, TIMER_CLK(imbusclk));

	पंचांगrptr = ioremap(baseaddr, माप(काष्ठा txx9_पंचांगr_reg));
	__raw_ग_लिखोl(TCR_BASE, &पंचांगrptr->tcr);
	__raw_ग_लिखोl(0, &पंचांगrptr->tisr);
	__raw_ग_लिखोl(TIMER_CCD, &पंचांगrptr->ccdr);
	__raw_ग_लिखोl(TXx9_TMITMR_TZCE, &पंचांगrptr->iपंचांगr);
	__raw_ग_लिखोl(1 << TXX9_CLOCKSOURCE_BITS, &पंचांगrptr->cpra);
	__raw_ग_लिखोl(TCR_BASE | TXx9_TMTCR_TCE, &पंचांगrptr->tcr);
	txx9_घड़ीsource.पंचांगrptr = पंचांगrptr;

	sched_घड़ी_रेजिस्टर(txx9_पढ़ो_sched_घड़ी, TXX9_CLOCKSOURCE_BITS,
			     TIMER_CLK(imbusclk));
पूर्ण

काष्ठा txx9_घड़ी_event_device अणु
	काष्ठा घड़ी_event_device cd;
	काष्ठा txx9_पंचांगr_reg __iomem *पंचांगrptr;
पूर्ण;

अटल व्योम txx9पंचांगr_stop_and_clear(काष्ठा txx9_पंचांगr_reg __iomem *पंचांगrptr)
अणु
	/* stop and reset counter */
	__raw_ग_लिखोl(TCR_BASE, &पंचांगrptr->tcr);
	/* clear pending पूर्णांकerrupt */
	__raw_ग_लिखोl(0, &पंचांगrptr->tisr);
पूर्ण

अटल पूर्णांक txx9पंचांगr_set_state_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा txx9_घड़ी_event_device *txx9_cd =
		container_of(evt, काष्ठा txx9_घड़ी_event_device, cd);
	काष्ठा txx9_पंचांगr_reg __iomem *पंचांगrptr = txx9_cd->पंचांगrptr;

	txx9पंचांगr_stop_and_clear(पंचांगrptr);

	__raw_ग_लिखोl(TXx9_TMITMR_TIIE | TXx9_TMITMR_TZCE, &पंचांगrptr->iपंचांगr);
	/* start समयr */
	__raw_ग_लिखोl(((u64)(NSEC_PER_SEC / HZ) * evt->mult) >> evt->shअगरt,
		     &पंचांगrptr->cpra);
	__raw_ग_लिखोl(TCR_BASE | TXx9_TMTCR_TCE, &पंचांगrptr->tcr);
	वापस 0;
पूर्ण

अटल पूर्णांक txx9पंचांगr_set_state_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा txx9_घड़ी_event_device *txx9_cd =
		container_of(evt, काष्ठा txx9_घड़ी_event_device, cd);
	काष्ठा txx9_पंचांगr_reg __iomem *पंचांगrptr = txx9_cd->पंचांगrptr;

	txx9पंचांगr_stop_and_clear(पंचांगrptr);
	__raw_ग_लिखोl(TXx9_TMITMR_TIIE, &पंचांगrptr->iपंचांगr);
	वापस 0;
पूर्ण

अटल पूर्णांक txx9पंचांगr_set_state_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा txx9_घड़ी_event_device *txx9_cd =
		container_of(evt, काष्ठा txx9_घड़ी_event_device, cd);
	काष्ठा txx9_पंचांगr_reg __iomem *पंचांगrptr = txx9_cd->पंचांगrptr;

	txx9पंचांगr_stop_and_clear(पंचांगrptr);
	__raw_ग_लिखोl(0, &पंचांगrptr->iपंचांगr);
	वापस 0;
पूर्ण

अटल पूर्णांक txx9पंचांगr_tick_resume(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा txx9_घड़ी_event_device *txx9_cd =
		container_of(evt, काष्ठा txx9_घड़ी_event_device, cd);
	काष्ठा txx9_पंचांगr_reg __iomem *पंचांगrptr = txx9_cd->पंचांगrptr;

	txx9पंचांगr_stop_and_clear(पंचांगrptr);
	__raw_ग_लिखोl(TIMER_CCD, &पंचांगrptr->ccdr);
	__raw_ग_लिखोl(0, &पंचांगrptr->iपंचांगr);
	वापस 0;
पूर्ण

अटल पूर्णांक txx9पंचांगr_set_next_event(अचिन्हित दीर्घ delta,
				  काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा txx9_घड़ी_event_device *txx9_cd =
		container_of(evt, काष्ठा txx9_घड़ी_event_device, cd);
	काष्ठा txx9_पंचांगr_reg __iomem *पंचांगrptr = txx9_cd->पंचांगrptr;

	txx9पंचांगr_stop_and_clear(पंचांगrptr);
	/* start समयr */
	__raw_ग_लिखोl(delta, &पंचांगrptr->cpra);
	__raw_ग_लिखोl(TCR_BASE | TXx9_TMTCR_TCE, &पंचांगrptr->tcr);
	वापस 0;
पूर्ण

अटल काष्ठा txx9_घड़ी_event_device txx9_घड़ी_event_device = अणु
	.cd = अणु
		.name			= "TXx9",
		.features		= CLOCK_EVT_FEAT_PERIODIC |
					  CLOCK_EVT_FEAT_ONESHOT,
		.rating			= 200,
		.set_state_shutकरोwn	= txx9पंचांगr_set_state_shutकरोwn,
		.set_state_periodic	= txx9पंचांगr_set_state_periodic,
		.set_state_oneshot	= txx9पंचांगr_set_state_oneshot,
		.tick_resume		= txx9पंचांगr_tick_resume,
		.set_next_event		= txx9पंचांगr_set_next_event,
	पूर्ण,
पूर्ण;

अटल irqवापस_t txx9पंचांगr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा txx9_घड़ी_event_device *txx9_cd = dev_id;
	काष्ठा घड़ी_event_device *cd = &txx9_cd->cd;
	काष्ठा txx9_पंचांगr_reg __iomem *पंचांगrptr = txx9_cd->पंचांगrptr;

	__raw_ग_लिखोl(0, &पंचांगrptr->tisr); /* ack पूर्णांकerrupt */
	cd->event_handler(cd);
	वापस IRQ_HANDLED;
पूर्ण

व्योम __init txx9_घड़ीevent_init(अचिन्हित दीर्घ baseaddr, पूर्णांक irq,
				 अचिन्हित पूर्णांक imbusclk)
अणु
	काष्ठा घड़ी_event_device *cd = &txx9_घड़ी_event_device.cd;
	काष्ठा txx9_पंचांगr_reg __iomem *पंचांगrptr;

	पंचांगrptr = ioremap(baseaddr, माप(काष्ठा txx9_पंचांगr_reg));
	txx9पंचांगr_stop_and_clear(पंचांगrptr);
	__raw_ग_लिखोl(TIMER_CCD, &पंचांगrptr->ccdr);
	__raw_ग_लिखोl(0, &पंचांगrptr->iपंचांगr);
	txx9_घड़ी_event_device.पंचांगrptr = पंचांगrptr;

	घड़ीevent_set_घड़ी(cd, TIMER_CLK(imbusclk));
	cd->max_delta_ns =
		घड़ीevent_delta2ns(0xffffffff >> (32 - TXX9_TIMER_BITS), cd);
	cd->max_delta_ticks = 0xffffffff >> (32 - TXX9_TIMER_BITS);
	cd->min_delta_ns = घड़ीevent_delta2ns(0xf, cd);
	cd->min_delta_ticks = 0xf;
	cd->irq = irq;
	cd->cpumask = cpumask_of(0);
	घड़ीevents_रेजिस्टर_device(cd);
	अगर (request_irq(irq, txx9पंचांगr_पूर्णांकerrupt, IRQF_PERCPU | IRQF_TIMER,
			"txx9tmr", &txx9_घड़ी_event_device))
		pr_err("Failed to request irq %d (txx9tmr)\n", irq);
	prपूर्णांकk(KERN_INFO "TXx9: clockevent device at 0x%lx, irq %d\n",
	       baseaddr, irq);
पूर्ण

व्योम __init txx9_पंचांगr_init(अचिन्हित दीर्घ baseaddr)
अणु
	काष्ठा txx9_पंचांगr_reg __iomem *पंचांगrptr;

	पंचांगrptr = ioremap(baseaddr, माप(काष्ठा txx9_पंचांगr_reg));
	/* Start once to make CounterResetEnable effective */
	__raw_ग_लिखोl(TXx9_TMTCR_CRE | TXx9_TMTCR_TCE, &पंचांगrptr->tcr);
	/* Stop and reset the counter */
	__raw_ग_लिखोl(TXx9_TMTCR_CRE, &पंचांगrptr->tcr);
	__raw_ग_लिखोl(0, &पंचांगrptr->tisr);
	__raw_ग_लिखोl(0xffffffff, &पंचांगrptr->cpra);
	__raw_ग_लिखोl(0, &पंचांगrptr->iपंचांगr);
	__raw_ग_लिखोl(0, &पंचांगrptr->ccdr);
	__raw_ग_लिखोl(0, &पंचांगrptr->pgmr);
	iounmap(पंचांगrptr);
पूर्ण
