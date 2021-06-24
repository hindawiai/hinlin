<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IXP4 समयr driver
 * Copyright (C) 2019 Linus Walleij <linus.walleij@linaro.org>
 *
 * Based on arch/arm/mach-ixp4xx/common.c
 * Copyright 2002 (C) Intel Corporation
 * Copyright 2003-2004 (C) MontaVista, Software, Inc.
 * Copyright (C) Deepak Saxena <dsaxena@plनिकासy.net>
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
/* Goes away with OF conversion */
#समावेश <linux/platक्रमm_data/समयr-ixp4xx.h>

/*
 * Constants to make it easy to access Timer Control/Status रेजिस्टरs
 */
#घोषणा IXP4XX_OSTS_OFFSET	0x00  /* Continuous Timestamp */
#घोषणा IXP4XX_OST1_OFFSET	0x04  /* Timer 1 Timestamp */
#घोषणा IXP4XX_OSRT1_OFFSET	0x08  /* Timer 1 Reload */
#घोषणा IXP4XX_OST2_OFFSET	0x0C  /* Timer 2 Timestamp */
#घोषणा IXP4XX_OSRT2_OFFSET	0x10  /* Timer 2 Reload */
#घोषणा IXP4XX_OSWT_OFFSET	0x14  /* Watchकरोg Timer */
#घोषणा IXP4XX_OSWE_OFFSET	0x18  /* Watchकरोg Enable */
#घोषणा IXP4XX_OSWK_OFFSET	0x1C  /* Watchकरोg Key */
#घोषणा IXP4XX_OSST_OFFSET	0x20  /* Timer Status */

/*
 * Timer रेजिस्टर values and bit definitions
 */
#घोषणा IXP4XX_OST_ENABLE		0x00000001
#घोषणा IXP4XX_OST_ONE_SHOT		0x00000002
/* Low order bits of reload value ignored */
#घोषणा IXP4XX_OST_RELOAD_MASK		0x00000003
#घोषणा IXP4XX_OST_DISABLED		0x00000000
#घोषणा IXP4XX_OSST_TIMER_1_PEND	0x00000001
#घोषणा IXP4XX_OSST_TIMER_2_PEND	0x00000002
#घोषणा IXP4XX_OSST_TIMER_TS_PEND	0x00000004
#घोषणा IXP4XX_OSST_TIMER_WDOG_PEND	0x00000008
#घोषणा IXP4XX_OSST_TIMER_WARM_RESET	0x00000010

#घोषणा	IXP4XX_WDT_KEY			0x0000482E
#घोषणा	IXP4XX_WDT_RESET_ENABLE		0x00000001
#घोषणा	IXP4XX_WDT_IRQ_ENABLE		0x00000002
#घोषणा	IXP4XX_WDT_COUNT_ENABLE		0x00000004

काष्ठा ixp4xx_समयr अणु
	व्योम __iomem *base;
	अचिन्हित पूर्णांक tick_rate;
	u32 latch;
	काष्ठा घड़ी_event_device clkevt;
#अगर_घोषित CONFIG_ARM
	काष्ठा delay_समयr delay_समयr;
#पूर्ण_अगर
पूर्ण;

/*
 * A local singleton used by sched_घड़ी and delay समयr पढ़ोs, which are
 * fast and stateless
 */
अटल काष्ठा ixp4xx_समयr *local_ixp4xx_समयr;

अटल अंतरभूत काष्ठा ixp4xx_समयr *
to_ixp4xx_समयr(काष्ठा घड़ी_event_device *evt)
अणु
	वापस container_of(evt, काष्ठा ixp4xx_समयr, clkevt);
पूर्ण

अटल अचिन्हित दीर्घ ixp4xx_पढ़ो_समयr(व्योम)
अणु
	वापस __raw_पढ़ोl(local_ixp4xx_समयr->base + IXP4XX_OSTS_OFFSET);
पूर्ण

अटल u64 notrace ixp4xx_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस ixp4xx_पढ़ो_समयr();
पूर्ण

अटल u64 ixp4xx_घड़ीsource_पढ़ो(काष्ठा घड़ीsource *c)
अणु
	वापस ixp4xx_पढ़ो_समयr();
पूर्ण

अटल irqवापस_t ixp4xx_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ixp4xx_समयr *पंचांगr = dev_id;
	काष्ठा घड़ी_event_device *evt = &पंचांगr->clkevt;

	/* Clear Pending Interrupt */
	__raw_ग_लिखोl(IXP4XX_OSST_TIMER_1_PEND,
		     पंचांगr->base + IXP4XX_OSST_OFFSET);

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ixp4xx_set_next_event(अचिन्हित दीर्घ cycles,
				 काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ixp4xx_समयr *पंचांगr = to_ixp4xx_समयr(evt);
	u32 val;

	val = __raw_पढ़ोl(पंचांगr->base + IXP4XX_OSRT1_OFFSET);
	/* Keep enable/oneshot bits */
	val &= IXP4XX_OST_RELOAD_MASK;
	__raw_ग_लिखोl((cycles & ~IXP4XX_OST_RELOAD_MASK) | val,
		     पंचांगr->base + IXP4XX_OSRT1_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक ixp4xx_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ixp4xx_समयr *पंचांगr = to_ixp4xx_समयr(evt);
	u32 val;

	val = __raw_पढ़ोl(पंचांगr->base + IXP4XX_OSRT1_OFFSET);
	val &= ~IXP4XX_OST_ENABLE;
	__raw_ग_लिखोl(val, पंचांगr->base + IXP4XX_OSRT1_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक ixp4xx_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ixp4xx_समयr *पंचांगr = to_ixp4xx_समयr(evt);

	__raw_ग_लिखोl(IXP4XX_OST_ENABLE | IXP4XX_OST_ONE_SHOT,
		     पंचांगr->base + IXP4XX_OSRT1_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक ixp4xx_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ixp4xx_समयr *पंचांगr = to_ixp4xx_समयr(evt);
	u32 val;

	val = पंचांगr->latch & ~IXP4XX_OST_RELOAD_MASK;
	val |= IXP4XX_OST_ENABLE;
	__raw_ग_लिखोl(val, पंचांगr->base + IXP4XX_OSRT1_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक ixp4xx_resume(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ixp4xx_समयr *पंचांगr = to_ixp4xx_समयr(evt);
	u32 val;

	val = __raw_पढ़ोl(पंचांगr->base + IXP4XX_OSRT1_OFFSET);
	val |= IXP4XX_OST_ENABLE;
	__raw_ग_लिखोl(val, पंचांगr->base + IXP4XX_OSRT1_OFFSET);

	वापस 0;
पूर्ण

/*
 * IXP4xx समयr tick
 * We use OS समयr1 on the CPU क्रम the समयr tick and the बारtamp
 * counter as a source of real घड़ी ticks to account क्रम missed jअगरfies.
 */
अटल __init पूर्णांक ixp4xx_समयr_रेजिस्टर(व्योम __iomem *base,
					पूर्णांक समयr_irq,
					अचिन्हित पूर्णांक समयr_freq)
अणु
	काष्ठा ixp4xx_समयr *पंचांगr;
	पूर्णांक ret;

	पंचांगr = kzalloc(माप(*पंचांगr), GFP_KERNEL);
	अगर (!पंचांगr)
		वापस -ENOMEM;
	पंचांगr->base = base;
	पंचांगr->tick_rate = समयr_freq;

	/*
	 * The समयr रेजिस्टर करोesn't allow to specअगरy the two least
	 * signअगरicant bits of the समयout value and assumes them being zero.
	 * So make sure the latch is the best value with the two least
	 * signअगरicant bits unset.
	 */
	पंचांगr->latch = DIV_ROUND_CLOSEST(समयr_freq,
				       (IXP4XX_OST_RELOAD_MASK + 1) * HZ)
		* (IXP4XX_OST_RELOAD_MASK + 1);

	local_ixp4xx_समयr = पंचांगr;

	/* Reset/disable counter */
	__raw_ग_लिखोl(0, पंचांगr->base + IXP4XX_OSRT1_OFFSET);

	/* Clear any pending पूर्णांकerrupt on समयr 1 */
	__raw_ग_लिखोl(IXP4XX_OSST_TIMER_1_PEND,
		     पंचांगr->base + IXP4XX_OSST_OFFSET);

	/* Reset समय-stamp counter */
	__raw_ग_लिखोl(0, पंचांगr->base + IXP4XX_OSTS_OFFSET);

	घड़ीsource_mmio_init(शून्य, "OSTS", समयr_freq, 200, 32,
			      ixp4xx_घड़ीsource_पढ़ो);

	पंचांगr->clkevt.name = "ixp4xx timer1";
	पंचांगr->clkevt.features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT;
	पंचांगr->clkevt.rating = 200;
	पंचांगr->clkevt.set_state_shutकरोwn = ixp4xx_shutकरोwn;
	पंचांगr->clkevt.set_state_periodic = ixp4xx_set_periodic;
	पंचांगr->clkevt.set_state_oneshot = ixp4xx_set_oneshot;
	पंचांगr->clkevt.tick_resume = ixp4xx_resume;
	पंचांगr->clkevt.set_next_event = ixp4xx_set_next_event;
	पंचांगr->clkevt.cpumask = cpumask_of(0);
	पंचांगr->clkevt.irq = समयr_irq;
	ret = request_irq(समयr_irq, ixp4xx_समयr_पूर्णांकerrupt,
			  IRQF_TIMER, "IXP4XX-TIMER1", पंचांगr);
	अगर (ret) अणु
		pr_crit("no timer IRQ\n");
		वापस -ENODEV;
	पूर्ण
	घड़ीevents_config_and_रेजिस्टर(&पंचांगr->clkevt, समयr_freq,
					0xf, 0xfffffffe);

	sched_घड़ी_रेजिस्टर(ixp4xx_पढ़ो_sched_घड़ी, 32, समयr_freq);

#अगर_घोषित CONFIG_ARM
	/* Also use this समयr क्रम delays */
	पंचांगr->delay_समयr.पढ़ो_current_समयr = ixp4xx_पढ़ो_समयr;
	पंचांगr->delay_समयr.freq = समयr_freq;
	रेजिस्टर_current_समयr_delay(&पंचांगr->delay_समयr);
#पूर्ण_अगर

	वापस 0;
पूर्ण

/**
 * ixp4xx_समयr_setup() - Timer setup function to be called from boardfiles
 * @समयrbase: physical base of समयr block
 * @समयr_irq: Linux IRQ number क्रम the समयr
 * @समयr_freq: Fixed frequency of the समयr
 */
व्योम __init ixp4xx_समयr_setup(resource_माप_प्रकार समयrbase,
			       पूर्णांक समयr_irq,
			       अचिन्हित पूर्णांक समयr_freq)
अणु
	व्योम __iomem *base;

	base = ioremap(समयrbase, 0x100);
	अगर (!base) अणु
		pr_crit("IXP4xx: can't remap timer\n");
		वापस;
	पूर्ण
	ixp4xx_समयr_रेजिस्टर(base, समयr_irq, समयr_freq);
पूर्ण
EXPORT_SYMBOL_GPL(ixp4xx_समयr_setup);

#अगर_घोषित CONFIG_OF
अटल __init पूर्णांक ixp4xx_of_समयr_init(काष्ठा device_node *np)
अणु
	व्योम __iomem *base;
	पूर्णांक irq;
	पूर्णांक ret;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_crit("IXP4xx: can't remap timer\n");
		वापस -ENODEV;
	पूर्ण

	irq = irq_of_parse_and_map(np, 0);
	अगर (irq <= 0) अणु
		pr_err("Can't parse IRQ\n");
		ret = -EINVAL;
		जाओ out_unmap;
	पूर्ण

	/* TODO: get some fixed घड़ीs पूर्णांकo the device tree */
	ret = ixp4xx_समयr_रेजिस्टर(base, irq, 66666000);
	अगर (ret)
		जाओ out_unmap;
	वापस 0;

out_unmap:
	iounmap(base);
	वापस ret;
पूर्ण
TIMER_OF_DECLARE(ixp4xx, "intel,ixp4xx-timer", ixp4xx_of_समयr_init);
#पूर्ण_अगर
