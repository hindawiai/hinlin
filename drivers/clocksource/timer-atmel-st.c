<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/arch/arm/mach-at91/at91rm9200_समय.c
 *
 *  Copyright (C) 2003 SAN People
 *  Copyright (C) 2003 ATMEL
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/export.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/aपंचांगel-st.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/regmap.h>

अटल अचिन्हित दीर्घ last_crtr;
अटल u32 irqmask;
अटल काष्ठा घड़ी_event_device clkevt;
अटल काष्ठा regmap *regmap_st;
अटल पूर्णांक समयr_latch;

/*
 * The ST_CRTR is updated asynchronously to the master घड़ी ... but
 * the updates as seen by the CPU करोn't seem to be strictly monotonic.
 * Waiting until we पढ़ो the same value twice aव्योमs glitching.
 */
अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_CRTR(व्योम)
अणु
	अचिन्हित पूर्णांक x1, x2;

	regmap_पढ़ो(regmap_st, AT91_ST_CRTR, &x1);
	करो अणु
		regmap_पढ़ो(regmap_st, AT91_ST_CRTR, &x2);
		अगर (x1 == x2)
			अवरोध;
		x1 = x2;
	पूर्ण जबतक (1);
	वापस x1;
पूर्ण

/*
 * IRQ handler क्रम the समयr.
 */
अटल irqवापस_t at91rm9200_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 sr;

	regmap_पढ़ो(regmap_st, AT91_ST_SR, &sr);
	sr &= irqmask;

	/*
	 * irqs should be disabled here, but as the irq is shared they are only
	 * guaranteed to be off अगर the समयr irq is रेजिस्टरed first.
	 */
	WARN_ON_ONCE(!irqs_disabled());

	/* simulate "oneshot" समयr with alarm */
	अगर (sr & AT91_ST_ALMS) अणु
		clkevt.event_handler(&clkevt);
		वापस IRQ_HANDLED;
	पूर्ण

	/* periodic mode should handle delayed ticks */
	अगर (sr & AT91_ST_PITS) अणु
		u32	crtr = पढ़ो_CRTR();

		जबतक (((crtr - last_crtr) & AT91_ST_CRTV) >= समयr_latch) अणु
			last_crtr += समयr_latch;
			clkevt.event_handler(&clkevt);
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण

	/* this irq is shared ... */
	वापस IRQ_NONE;
पूर्ण

अटल u64 पढ़ो_clk32k(काष्ठा घड़ीsource *cs)
अणु
	वापस पढ़ो_CRTR();
पूर्ण

अटल काष्ठा घड़ीsource clk32k = अणु
	.name		= "32k_counter",
	.rating		= 150,
	.पढ़ो		= पढ़ो_clk32k,
	.mask		= CLOCKSOURCE_MASK(20),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल व्योम clkdev32k_disable_and_flush_irq(व्योम)
अणु
	अचिन्हित पूर्णांक val;

	/* Disable and flush pending समयr पूर्णांकerrupts */
	regmap_ग_लिखो(regmap_st, AT91_ST_IDR, AT91_ST_PITS | AT91_ST_ALMS);
	regmap_पढ़ो(regmap_st, AT91_ST_SR, &val);
	last_crtr = पढ़ो_CRTR();
पूर्ण

अटल पूर्णांक clkevt32k_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	clkdev32k_disable_and_flush_irq();
	irqmask = 0;
	regmap_ग_लिखो(regmap_st, AT91_ST_IER, irqmask);
	वापस 0;
पूर्ण

अटल पूर्णांक clkevt32k_set_oneshot(काष्ठा घड़ी_event_device *dev)
अणु
	clkdev32k_disable_and_flush_irq();

	/*
	 * ALM क्रम oneshot irqs, set by next_event()
	 * beक्रमe 32 seconds have passed.
	 */
	irqmask = AT91_ST_ALMS;
	regmap_ग_लिखो(regmap_st, AT91_ST_RTAR, last_crtr);
	regmap_ग_लिखो(regmap_st, AT91_ST_IER, irqmask);
	वापस 0;
पूर्ण

अटल पूर्णांक clkevt32k_set_periodic(काष्ठा घड़ी_event_device *dev)
अणु
	clkdev32k_disable_and_flush_irq();

	/* PIT क्रम periodic irqs; fixed rate of 1/HZ */
	irqmask = AT91_ST_PITS;
	regmap_ग_लिखो(regmap_st, AT91_ST_PIMR, समयr_latch);
	regmap_ग_लिखो(regmap_st, AT91_ST_IER, irqmask);
	वापस 0;
पूर्ण

अटल पूर्णांक
clkevt32k_next_event(अचिन्हित दीर्घ delta, काष्ठा घड़ी_event_device *dev)
अणु
	u32		alm;
	अचिन्हित पूर्णांक	val;

	BUG_ON(delta < 2);

	/* The alarm IRQ uses असलolute समय (now+delta), not the relative
	 * समय (delta) in our calling convention.  Like all घड़ीevents
	 * using such "match" hardware, we have a race to defend against.
	 *
	 * Our defense here is to have set up the घड़ीevent device so the
	 * delta is at least two.  That way we never end up writing RTAR
	 * with the value then held in CRTR ... which would mean the match
	 * wouldn't trigger until 32 seconds later, after CRTR wraps.
	 */
	alm = पढ़ो_CRTR();

	/* Cancel any pending alarm; flush any pending IRQ */
	regmap_ग_लिखो(regmap_st, AT91_ST_RTAR, alm);
	regmap_पढ़ो(regmap_st, AT91_ST_SR, &val);

	/* Schedule alarm by writing RTAR. */
	alm += delta;
	regmap_ग_लिखो(regmap_st, AT91_ST_RTAR, alm);

	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device clkevt = अणु
	.name			= "at91_tick",
	.features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT,
	.rating			= 150,
	.set_next_event		= clkevt32k_next_event,
	.set_state_shutकरोwn	= clkevt32k_shutकरोwn,
	.set_state_periodic	= clkevt32k_set_periodic,
	.set_state_oneshot	= clkevt32k_set_oneshot,
	.tick_resume		= clkevt32k_shutकरोwn,
पूर्ण;

/*
 * ST (प्रणाली समयr) module supports both घड़ीevents and घड़ीsource.
 */
अटल पूर्णांक __init aपंचांगel_st_समयr_init(काष्ठा device_node *node)
अणु
	काष्ठा clk *sclk;
	अचिन्हित पूर्णांक sclk_rate, val;
	पूर्णांक irq, ret;

	regmap_st = syscon_node_to_regmap(node);
	अगर (IS_ERR(regmap_st)) अणु
		pr_err("Unable to get regmap\n");
		वापस PTR_ERR(regmap_st);
	पूर्ण

	/* Disable all समयr पूर्णांकerrupts, and clear any pending ones */
	regmap_ग_लिखो(regmap_st, AT91_ST_IDR,
		AT91_ST_PITS | AT91_ST_WDOVF | AT91_ST_RTTINC | AT91_ST_ALMS);
	regmap_पढ़ो(regmap_st, AT91_ST_SR, &val);

	/* Get the पूर्णांकerrupts property */
	irq  = irq_of_parse_and_map(node, 0);
	अगर (!irq) अणु
		pr_err("Unable to get IRQ from DT\n");
		वापस -EINVAL;
	पूर्ण

	/* Make IRQs happen क्रम the प्रणाली समयr */
	ret = request_irq(irq, at91rm9200_समयr_पूर्णांकerrupt,
			  IRQF_SHARED | IRQF_TIMER | IRQF_IRQPOLL,
			  "at91_tick", regmap_st);
	अगर (ret) अणु
		pr_err("Unable to setup IRQ\n");
		वापस ret;
	पूर्ण

	sclk = of_clk_get(node, 0);
	अगर (IS_ERR(sclk)) अणु
		pr_err("Unable to get slow clock\n");
		वापस PTR_ERR(sclk);
	पूर्ण

	ret = clk_prepare_enable(sclk);
	अगर (ret) अणु
		pr_err("Could not enable slow clock\n");
		वापस ret;
	पूर्ण

	sclk_rate = clk_get_rate(sclk);
	अगर (!sclk_rate) अणु
		pr_err("Invalid slow clock rate\n");
		वापस -EINVAL;
	पूर्ण
	समयr_latch = (sclk_rate + HZ / 2) / HZ;

	/* The 32KiHz "Slow Clock" (tick every 30517.58 nanoseconds) is used
	 * directly क्रम the घड़ीsource and all घड़ीevents, after adjusting
	 * its prescaler from the 1 Hz शेष.
	 */
	regmap_ग_लिखो(regmap_st, AT91_ST_RTMR, 1);

	/* Setup समयr घड़ीevent, with minimum of two ticks (important!!) */
	clkevt.cpumask = cpumask_of(0);
	घड़ीevents_config_and_रेजिस्टर(&clkevt, sclk_rate,
					2, AT91_ST_ALMV);

	/* रेजिस्टर घड़ीsource */
	वापस घड़ीsource_रेजिस्टर_hz(&clk32k, sclk_rate);
पूर्ण
TIMER_OF_DECLARE(aपंचांगel_st_समयr, "atmel,at91rm9200-st",
		       aपंचांगel_st_समयr_init);
