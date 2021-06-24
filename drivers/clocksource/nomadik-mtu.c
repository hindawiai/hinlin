<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008 STMicroelectronics
 * Copyright (C) 2010 Alessandro Rubini
 * Copyright (C) 2010 Linus Walleij क्रम ST-Ericsson
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/clk.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <यंत्र/mach/समय.स>

/*
 * The MTU device hosts four dअगरferent counters, with 4 set of
 * रेजिस्टरs. These are रेजिस्टर names.
 */

#घोषणा MTU_IMSC	0x00	/* Interrupt mask set/clear */
#घोषणा MTU_RIS		0x04	/* Raw पूर्णांकerrupt status */
#घोषणा MTU_MIS		0x08	/* Masked पूर्णांकerrupt status */
#घोषणा MTU_ICR		0x0C	/* Interrupt clear रेजिस्टर */

/* per-समयr रेजिस्टरs take 0..3 as argument */
#घोषणा MTU_LR(x)	(0x10 + 0x10 * (x) + 0x00)	/* Load value */
#घोषणा MTU_VAL(x)	(0x10 + 0x10 * (x) + 0x04)	/* Current value */
#घोषणा MTU_CR(x)	(0x10 + 0x10 * (x) + 0x08)	/* Control reg */
#घोषणा MTU_BGLR(x)	(0x10 + 0x10 * (x) + 0x0c)	/* At next overflow */

/* bits क्रम the control रेजिस्टर */
#घोषणा MTU_CRn_ENA		0x80
#घोषणा MTU_CRn_PERIODIC	0x40	/* अगर 0 = मुक्त-running */
#घोषणा MTU_CRn_PRESCALE_MASK	0x0c
#घोषणा MTU_CRn_PRESCALE_1		0x00
#घोषणा MTU_CRn_PRESCALE_16		0x04
#घोषणा MTU_CRn_PRESCALE_256		0x08
#घोषणा MTU_CRn_32BITS		0x02
#घोषणा MTU_CRn_ONESHOT		0x01	/* अगर 0 = wraps reloading from BGLR*/

/* Other रेजिस्टरs are usual amba/primecell रेजिस्टरs, currently not used */
#घोषणा MTU_ITCR	0xff0
#घोषणा MTU_ITOP	0xff4

#घोषणा MTU_PERIPH_ID0	0xfe0
#घोषणा MTU_PERIPH_ID1	0xfe4
#घोषणा MTU_PERIPH_ID2	0xfe8
#घोषणा MTU_PERIPH_ID3	0xfeC

#घोषणा MTU_PCELL0	0xff0
#घोषणा MTU_PCELL1	0xff4
#घोषणा MTU_PCELL2	0xff8
#घोषणा MTU_PCELL3	0xffC

अटल व्योम __iomem *mtu_base;
अटल bool clkevt_periodic;
अटल u32 clk_prescale;
अटल u32 nmdk_cycle;		/* ग_लिखो-once */
अटल काष्ठा delay_समयr mtu_delay_समयr;

/*
 * Override the global weak sched_घड़ी symbol with this
 * local implementation which uses the घड़ीsource to get some
 * better resolution when scheduling the kernel.
 */
अटल u64 notrace nomadik_पढ़ो_sched_घड़ी(व्योम)
अणु
	अगर (unlikely(!mtu_base))
		वापस 0;

	वापस -पढ़ोl(mtu_base + MTU_VAL(0));
पूर्ण

अटल अचिन्हित दीर्घ nmdk_समयr_पढ़ो_current_समयr(व्योम)
अणु
	वापस ~पढ़ोl_relaxed(mtu_base + MTU_VAL(0));
पूर्ण

/* Clockevent device: use one-shot mode */
अटल पूर्णांक nmdk_clkevt_next(अचिन्हित दीर्घ evt, काष्ठा घड़ी_event_device *ev)
अणु
	ग_लिखोl(1 << 1, mtu_base + MTU_IMSC);
	ग_लिखोl(evt, mtu_base + MTU_LR(1));
	/* Load highest value, enable device, enable पूर्णांकerrupts */
	ग_लिखोl(MTU_CRn_ONESHOT | clk_prescale |
	       MTU_CRn_32BITS | MTU_CRn_ENA,
	       mtu_base + MTU_CR(1));

	वापस 0;
पूर्ण

अटल व्योम nmdk_clkevt_reset(व्योम)
अणु
	अगर (clkevt_periodic) अणु
		/* Timer: configure load and background-load, and fire it up */
		ग_लिखोl(nmdk_cycle, mtu_base + MTU_LR(1));
		ग_लिखोl(nmdk_cycle, mtu_base + MTU_BGLR(1));

		ग_लिखोl(MTU_CRn_PERIODIC | clk_prescale |
		       MTU_CRn_32BITS | MTU_CRn_ENA,
		       mtu_base + MTU_CR(1));
		ग_लिखोl(1 << 1, mtu_base + MTU_IMSC);
	पूर्ण अन्यथा अणु
		/* Generate an पूर्णांकerrupt to start the घड़ीevent again */
		(व्योम) nmdk_clkevt_next(nmdk_cycle, शून्य);
	पूर्ण
पूर्ण

अटल पूर्णांक nmdk_clkevt_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	ग_लिखोl(0, mtu_base + MTU_IMSC);
	/* disable समयr */
	ग_लिखोl(0, mtu_base + MTU_CR(1));
	/* load some high शेष value */
	ग_लिखोl(0xffffffff, mtu_base + MTU_LR(1));
	वापस 0;
पूर्ण

अटल पूर्णांक nmdk_clkevt_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	clkevt_periodic = false;
	वापस 0;
पूर्ण

अटल पूर्णांक nmdk_clkevt_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	clkevt_periodic = true;
	nmdk_clkevt_reset();
	वापस 0;
पूर्ण

अटल व्योम nmdk_clksrc_reset(व्योम)
अणु
	/* Disable */
	ग_लिखोl(0, mtu_base + MTU_CR(0));

	/* ClockSource: configure load and background-load, and fire it up */
	ग_लिखोl(nmdk_cycle, mtu_base + MTU_LR(0));
	ग_लिखोl(nmdk_cycle, mtu_base + MTU_BGLR(0));

	ग_लिखोl(clk_prescale | MTU_CRn_32BITS | MTU_CRn_ENA,
	       mtu_base + MTU_CR(0));
पूर्ण

अटल व्योम nmdk_clkevt_resume(काष्ठा घड़ी_event_device *cedev)
अणु
	nmdk_clkevt_reset();
	nmdk_clksrc_reset();
पूर्ण

अटल काष्ठा घड़ी_event_device nmdk_clkevt = अणु
	.name			= "mtu_1",
	.features		= CLOCK_EVT_FEAT_ONESHOT |
				  CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_DYNIRQ,
	.rating			= 200,
	.set_state_shutकरोwn	= nmdk_clkevt_shutकरोwn,
	.set_state_periodic	= nmdk_clkevt_set_periodic,
	.set_state_oneshot	= nmdk_clkevt_set_oneshot,
	.set_next_event		= nmdk_clkevt_next,
	.resume			= nmdk_clkevt_resume,
पूर्ण;

/*
 * IRQ Handler क्रम समयr 1 of the MTU block.
 */
अटल irqवापस_t nmdk_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evdev = dev_id;

	ग_लिखोl(1 << 1, mtu_base + MTU_ICR); /* Interrupt clear reg */
	evdev->event_handler(evdev);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init nmdk_समयr_init(व्योम __iomem *base, पूर्णांक irq,
				   काष्ठा clk *pclk, काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;
	पूर्णांक min_ticks;

	mtu_base = base;

	BUG_ON(clk_prepare_enable(pclk));
	BUG_ON(clk_prepare_enable(clk));

	/*
	 * Tick rate is 2.4MHz क्रम Nomadik and 2.4Mhz, 100MHz or 133 MHz
	 * क्रम ux500, and in one specअगरic Ux500 हाल 32768 Hz.
	 *
	 * Use a भागide-by-16 counter अगर the tick rate is more than 32MHz.
	 * At 32 MHz, the समयr (with 32 bit counter) can be programmed
	 * to wake-up at a max 127s a head in समय. Dividing a 2.4 MHz समयr
	 * with 16 gives too low समयr resolution.
	 */
	rate = clk_get_rate(clk);
	अगर (rate > 32000000) अणु
		rate /= 16;
		clk_prescale = MTU_CRn_PRESCALE_16;
	पूर्ण अन्यथा अणु
		clk_prescale = MTU_CRn_PRESCALE_1;
	पूर्ण

	/* Cycles क्रम periodic mode */
	nmdk_cycle = DIV_ROUND_CLOSEST(rate, HZ);


	/* Timer 0 is the मुक्त running घड़ीsource */
	nmdk_clksrc_reset();

	ret = घड़ीsource_mmio_init(mtu_base + MTU_VAL(0), "mtu_0",
				    rate, 200, 32, घड़ीsource_mmio_पढ़ोl_करोwn);
	अगर (ret) अणु
		pr_err("timer: failed to initialize clock source %s\n", "mtu_0");
		वापस ret;
	पूर्ण

	sched_घड़ी_रेजिस्टर(nomadik_पढ़ो_sched_घड़ी, 32, rate);

	/* Timer 1 is used क्रम events, रेजिस्टर irq and घड़ीevents */
	अगर (request_irq(irq, nmdk_समयr_पूर्णांकerrupt, IRQF_TIMER,
			"Nomadik Timer Tick", &nmdk_clkevt))
		pr_err("%s: request_irq() failed\n", "Nomadik Timer Tick");
	nmdk_clkevt.cpumask = cpumask_of(0);
	nmdk_clkevt.irq = irq;
	अगर (rate < 100000)
		min_ticks = 5;
	अन्यथा
		min_ticks = 2;
	घड़ीevents_config_and_रेजिस्टर(&nmdk_clkevt, rate, min_ticks,
					0xffffffffU);

	mtu_delay_समयr.पढ़ो_current_समयr = &nmdk_समयr_पढ़ो_current_समयr;
	mtu_delay_समयr.freq = rate;
	रेजिस्टर_current_समयr_delay(&mtu_delay_समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक __init nmdk_समयr_of_init(काष्ठा device_node *node)
अणु
	काष्ठा clk *pclk;
	काष्ठा clk *clk;
	व्योम __iomem *base;
	पूर्णांक irq;

	base = of_iomap(node, 0);
	अगर (!base) अणु
		pr_err("Can't remap registers\n");
		वापस -ENXIO;
	पूर्ण

	pclk = of_clk_get_by_name(node, "apb_pclk");
	अगर (IS_ERR(pclk)) अणु
		pr_err("could not get apb_pclk\n");
		वापस PTR_ERR(pclk);
	पूर्ण

	clk = of_clk_get_by_name(node, "timclk");
	अगर (IS_ERR(clk)) अणु
		pr_err("could not get timclk\n");
		वापस PTR_ERR(clk);
	पूर्ण

	irq = irq_of_parse_and_map(node, 0);
	अगर (irq <= 0) अणु
		pr_err("Can't parse IRQ\n");
		वापस -EINVAL;
	पूर्ण

	वापस nmdk_समयr_init(base, irq, pclk, clk);
पूर्ण
TIMER_OF_DECLARE(nomadik_mtu, "st,nomadik-mtu",
		       nmdk_समयr_of_init);
