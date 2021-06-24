<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/syscore_ops.h>
#समावेश <soc/at91/aपंचांगel_tcb.h>


/*
 * We're configured to use a specific TC block, one that's not hooked
 * up to बाह्यal hardware, to provide a समय solution:
 *
 *   - Two channels combine to create a मुक्त-running 32 bit counter
 *     with a base rate of 5+ MHz, packaged as a घड़ीsource (with
 *     resolution better than 200 nsec).
 *   - Some chips support 32 bit counter. A single channel is used क्रम
 *     this 32 bit मुक्त-running counter. the second channel is not used.
 *
 *   - The third channel may be used to provide a घड़ीevent source, used in
 *   either periodic or oneshot mode. For 16-bit counter its runs at 32 KiHZ,
 *   and can handle delays of up to two seconds. For 32-bit counters, it runs at
 *   the same rate as the घड़ीsource
 *
 * REVISIT behavior during प्रणाली suspend states... we should disable
 * all घड़ीs and save the घातer.  Easily करोne क्रम घड़ीevent devices,
 * but घड़ीsources won't necessarily get the needed notअगरications.
 * For deeper प्रणाली sleep states, this will be mandatory...
 */

अटल व्योम __iomem *tcaddr;
अटल काष्ठा
अणु
	u32 cmr;
	u32 imr;
	u32 rc;
	bool clken;
पूर्ण tcb_cache[3];
अटल u32 bmr_cache;

अटल स्थिर u8 aपंचांगel_tcb_भागisors[] = अणु 2, 8, 32, 128 पूर्ण;

अटल u64 tc_get_cycles(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ	flags;
	u32		lower, upper;

	raw_local_irq_save(flags);
	करो अणु
		upper = पढ़ोl_relaxed(tcaddr + ATMEL_TC_REG(1, CV));
		lower = पढ़ोl_relaxed(tcaddr + ATMEL_TC_REG(0, CV));
	पूर्ण जबतक (upper != पढ़ोl_relaxed(tcaddr + ATMEL_TC_REG(1, CV)));

	raw_local_irq_restore(flags);
	वापस (upper << 16) | lower;
पूर्ण

अटल u64 tc_get_cycles32(काष्ठा घड़ीsource *cs)
अणु
	वापस पढ़ोl_relaxed(tcaddr + ATMEL_TC_REG(0, CV));
पूर्ण

अटल व्योम tc_clksrc_suspend(काष्ठा घड़ीsource *cs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tcb_cache); i++) अणु
		tcb_cache[i].cmr = पढ़ोl(tcaddr + ATMEL_TC_REG(i, CMR));
		tcb_cache[i].imr = पढ़ोl(tcaddr + ATMEL_TC_REG(i, IMR));
		tcb_cache[i].rc = पढ़ोl(tcaddr + ATMEL_TC_REG(i, RC));
		tcb_cache[i].clken = !!(पढ़ोl(tcaddr + ATMEL_TC_REG(i, SR)) &
					ATMEL_TC_CLKSTA);
	पूर्ण

	bmr_cache = पढ़ोl(tcaddr + ATMEL_TC_BMR);
पूर्ण

अटल व्योम tc_clksrc_resume(काष्ठा घड़ीsource *cs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tcb_cache); i++) अणु
		/* Restore रेजिस्टरs क्रम the channel, RA and RB are not used  */
		ग_लिखोl(tcb_cache[i].cmr, tcaddr + ATMEL_TC_REG(i, CMR));
		ग_लिखोl(tcb_cache[i].rc, tcaddr + ATMEL_TC_REG(i, RC));
		ग_लिखोl(0, tcaddr + ATMEL_TC_REG(i, RA));
		ग_लिखोl(0, tcaddr + ATMEL_TC_REG(i, RB));
		/* Disable all the पूर्णांकerrupts */
		ग_लिखोl(0xff, tcaddr + ATMEL_TC_REG(i, IDR));
		/* Reenable पूर्णांकerrupts that were enabled beक्रमe suspending */
		ग_लिखोl(tcb_cache[i].imr, tcaddr + ATMEL_TC_REG(i, IER));
		/* Start the घड़ी अगर it was used */
		अगर (tcb_cache[i].clken)
			ग_लिखोl(ATMEL_TC_CLKEN, tcaddr + ATMEL_TC_REG(i, CCR));
	पूर्ण

	/* Dual channel, chain channels */
	ग_लिखोl(bmr_cache, tcaddr + ATMEL_TC_BMR);
	/* Finally, trigger all the channels*/
	ग_लिखोl(ATMEL_TC_SYNC, tcaddr + ATMEL_TC_BCR);
पूर्ण

अटल काष्ठा घड़ीsource clksrc = अणु
	.rating         = 200,
	.पढ़ो           = tc_get_cycles,
	.mask           = CLOCKSOURCE_MASK(32),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
	.suspend	= tc_clksrc_suspend,
	.resume		= tc_clksrc_resume,
पूर्ण;

अटल u64 notrace tc_sched_घड़ी_पढ़ो(व्योम)
अणु
	वापस tc_get_cycles(&clksrc);
पूर्ण

अटल u64 notrace tc_sched_घड़ी_पढ़ो32(व्योम)
अणु
	वापस tc_get_cycles32(&clksrc);
पूर्ण

अटल काष्ठा delay_समयr tc_delay_समयr;

अटल अचिन्हित दीर्घ tc_delay_समयr_पढ़ो(व्योम)
अणु
	वापस tc_get_cycles(&clksrc);
पूर्ण

अटल अचिन्हित दीर्घ notrace tc_delay_समयr_पढ़ो32(व्योम)
अणु
	वापस tc_get_cycles32(&clksrc);
पूर्ण

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS

काष्ठा tc_clkevt_device अणु
	काष्ठा घड़ी_event_device	clkevt;
	काष्ठा clk			*clk;
	u32				rate;
	व्योम __iomem			*regs;
पूर्ण;

अटल काष्ठा tc_clkevt_device *to_tc_clkevt(काष्ठा घड़ी_event_device *clkevt)
अणु
	वापस container_of(clkevt, काष्ठा tc_clkevt_device, clkevt);
पूर्ण

अटल u32 समयr_घड़ी;

अटल पूर्णांक tc_shutकरोwn(काष्ठा घड़ी_event_device *d)
अणु
	काष्ठा tc_clkevt_device *tcd = to_tc_clkevt(d);
	व्योम __iomem		*regs = tcd->regs;

	ग_लिखोl(0xff, regs + ATMEL_TC_REG(2, IDR));
	ग_लिखोl(ATMEL_TC_CLKDIS, regs + ATMEL_TC_REG(2, CCR));
	अगर (!घड़ीevent_state_detached(d))
		clk_disable(tcd->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक tc_set_oneshot(काष्ठा घड़ी_event_device *d)
अणु
	काष्ठा tc_clkevt_device *tcd = to_tc_clkevt(d);
	व्योम __iomem		*regs = tcd->regs;

	अगर (घड़ीevent_state_oneshot(d) || घड़ीevent_state_periodic(d))
		tc_shutकरोwn(d);

	clk_enable(tcd->clk);

	/* count up to RC, then irq and stop */
	ग_लिखोl(समयr_घड़ी | ATMEL_TC_CPCSTOP | ATMEL_TC_WAVE |
		     ATMEL_TC_WAVESEL_UP_AUTO, regs + ATMEL_TC_REG(2, CMR));
	ग_लिखोl(ATMEL_TC_CPCS, regs + ATMEL_TC_REG(2, IER));

	/* set_next_event() configures and starts the समयr */
	वापस 0;
पूर्ण

अटल पूर्णांक tc_set_periodic(काष्ठा घड़ी_event_device *d)
अणु
	काष्ठा tc_clkevt_device *tcd = to_tc_clkevt(d);
	व्योम __iomem		*regs = tcd->regs;

	अगर (घड़ीevent_state_oneshot(d) || घड़ीevent_state_periodic(d))
		tc_shutकरोwn(d);

	/* By not making the genसमय core emulate periodic mode on top
	 * of oneshot, we get lower overhead and improved accuracy.
	 */
	clk_enable(tcd->clk);

	/* count up to RC, then irq and restart */
	ग_लिखोl(समयr_घड़ी | ATMEL_TC_WAVE | ATMEL_TC_WAVESEL_UP_AUTO,
		     regs + ATMEL_TC_REG(2, CMR));
	ग_लिखोl((tcd->rate + HZ / 2) / HZ, tcaddr + ATMEL_TC_REG(2, RC));

	/* Enable घड़ी and पूर्णांकerrupts on RC compare */
	ग_लिखोl(ATMEL_TC_CPCS, regs + ATMEL_TC_REG(2, IER));

	/* go go gadget! */
	ग_लिखोl(ATMEL_TC_CLKEN | ATMEL_TC_SWTRG, regs +
		     ATMEL_TC_REG(2, CCR));
	वापस 0;
पूर्ण

अटल पूर्णांक tc_next_event(अचिन्हित दीर्घ delta, काष्ठा घड़ी_event_device *d)
अणु
	ग_लिखोl_relaxed(delta, tcaddr + ATMEL_TC_REG(2, RC));

	/* go go gadget! */
	ग_लिखोl_relaxed(ATMEL_TC_CLKEN | ATMEL_TC_SWTRG,
			tcaddr + ATMEL_TC_REG(2, CCR));
	वापस 0;
पूर्ण

अटल काष्ठा tc_clkevt_device clkevt = अणु
	.clkevt	= अणु
		.features		= CLOCK_EVT_FEAT_PERIODIC |
					  CLOCK_EVT_FEAT_ONESHOT,
		/* Should be lower than at91rm9200's प्रणाली समयr */
		.rating			= 125,
		.set_next_event		= tc_next_event,
		.set_state_shutकरोwn	= tc_shutकरोwn,
		.set_state_periodic	= tc_set_periodic,
		.set_state_oneshot	= tc_set_oneshot,
	पूर्ण,
पूर्ण;

अटल irqवापस_t ch2_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा tc_clkevt_device	*dev = handle;
	अचिन्हित पूर्णांक		sr;

	sr = पढ़ोl_relaxed(dev->regs + ATMEL_TC_REG(2, SR));
	अगर (sr & ATMEL_TC_CPCS) अणु
		dev->clkevt.event_handler(&dev->clkevt);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक __init setup_clkevents(काष्ठा aपंचांगel_tc *tc, पूर्णांक भागisor_idx)
अणु
	पूर्णांक ret;
	काष्ठा clk *t2_clk = tc->clk[2];
	पूर्णांक irq = tc->irq[2];
	पूर्णांक bits = tc->tcb_config->counter_width;

	/* try to enable t2 clk to aव्योम future errors in mode change */
	ret = clk_prepare_enable(t2_clk);
	अगर (ret)
		वापस ret;

	clkevt.regs = tc->regs;
	clkevt.clk = t2_clk;

	अगर (bits == 32) अणु
		समयr_घड़ी = भागisor_idx;
		clkevt.rate = clk_get_rate(t2_clk) / aपंचांगel_tcb_भागisors[भागisor_idx];
	पूर्ण अन्यथा अणु
		ret = clk_prepare_enable(tc->slow_clk);
		अगर (ret) अणु
			clk_disable_unprepare(t2_clk);
			वापस ret;
		पूर्ण

		clkevt.rate = clk_get_rate(tc->slow_clk);
		समयr_घड़ी = ATMEL_TC_TIMER_CLOCK5;
	पूर्ण

	clk_disable(t2_clk);

	clkevt.clkevt.cpumask = cpumask_of(0);

	ret = request_irq(irq, ch2_irq, IRQF_TIMER, "tc_clkevt", &clkevt);
	अगर (ret) अणु
		clk_unprepare(t2_clk);
		अगर (bits != 32)
			clk_disable_unprepare(tc->slow_clk);
		वापस ret;
	पूर्ण

	घड़ीevents_config_and_रेजिस्टर(&clkevt.clkevt, clkevt.rate, 1, BIT(bits) - 1);

	वापस ret;
पूर्ण

#अन्यथा /* !CONFIG_GENERIC_CLOCKEVENTS */

अटल पूर्णांक __init setup_clkevents(काष्ठा aपंचांगel_tc *tc, पूर्णांक भागisor_idx)
अणु
	/* NOTHING */
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल व्योम __init tcb_setup_dual_chan(काष्ठा aपंचांगel_tc *tc, पूर्णांक mck_भागisor_idx)
अणु
	/* channel 0:  waveक्रमm mode, input mclk/8, घड़ी TIOA0 on overflow */
	ग_लिखोl(mck_भागisor_idx			/* likely भागide-by-8 */
			| ATMEL_TC_WAVE
			| ATMEL_TC_WAVESEL_UP		/* मुक्त-run */
			| ATMEL_TC_ACPA_SET		/* TIOA0 rises at 0 */
			| ATMEL_TC_ACPC_CLEAR,		/* (duty cycle 50%) */
			tcaddr + ATMEL_TC_REG(0, CMR));
	ग_लिखोl(0x0000, tcaddr + ATMEL_TC_REG(0, RA));
	ग_लिखोl(0x8000, tcaddr + ATMEL_TC_REG(0, RC));
	ग_लिखोl(0xff, tcaddr + ATMEL_TC_REG(0, IDR));	/* no irqs */
	ग_लिखोl(ATMEL_TC_CLKEN, tcaddr + ATMEL_TC_REG(0, CCR));

	/* channel 1:  waveक्रमm mode, input TIOA0 */
	ग_लिखोl(ATMEL_TC_XC1			/* input: TIOA0 */
			| ATMEL_TC_WAVE
			| ATMEL_TC_WAVESEL_UP,		/* मुक्त-run */
			tcaddr + ATMEL_TC_REG(1, CMR));
	ग_लिखोl(0xff, tcaddr + ATMEL_TC_REG(1, IDR));	/* no irqs */
	ग_लिखोl(ATMEL_TC_CLKEN, tcaddr + ATMEL_TC_REG(1, CCR));

	/* chain channel 0 to channel 1*/
	ग_लिखोl(ATMEL_TC_TC1XC1S_TIOA0, tcaddr + ATMEL_TC_BMR);
	/* then reset all the समयrs */
	ग_लिखोl(ATMEL_TC_SYNC, tcaddr + ATMEL_TC_BCR);
पूर्ण

अटल व्योम __init tcb_setup_single_chan(काष्ठा aपंचांगel_tc *tc, पूर्णांक mck_भागisor_idx)
अणु
	/* channel 0:  waveक्रमm mode, input mclk/8 */
	ग_लिखोl(mck_भागisor_idx			/* likely भागide-by-8 */
			| ATMEL_TC_WAVE
			| ATMEL_TC_WAVESEL_UP,		/* मुक्त-run */
			tcaddr + ATMEL_TC_REG(0, CMR));
	ग_लिखोl(0xff, tcaddr + ATMEL_TC_REG(0, IDR));	/* no irqs */
	ग_लिखोl(ATMEL_TC_CLKEN, tcaddr + ATMEL_TC_REG(0, CCR));

	/* then reset all the समयrs */
	ग_लिखोl(ATMEL_TC_SYNC, tcaddr + ATMEL_TC_BCR);
पूर्ण

अटल काष्ठा aपंचांगel_tcb_config tcb_rm9200_config = अणु
	.counter_width = 16,
पूर्ण;

अटल काष्ठा aपंचांगel_tcb_config tcb_sam9x5_config = अणु
	.counter_width = 32,
पूर्ण;

अटल काष्ठा aपंचांगel_tcb_config tcb_sama5d2_config = अणु
	.counter_width = 32,
	.has_gclk = 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_tcb_of_match[] = अणु
	अणु .compatible = "atmel,at91rm9200-tcb", .data = &tcb_rm9200_config, पूर्ण,
	अणु .compatible = "atmel,at91sam9x5-tcb", .data = &tcb_sam9x5_config, पूर्ण,
	अणु .compatible = "atmel,sama5d2-tcb", .data = &tcb_sama5d2_config, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक __init tcb_clksrc_init(काष्ठा device_node *node)
अणु
	काष्ठा aपंचांगel_tc tc;
	काष्ठा clk *t0_clk;
	स्थिर काष्ठा of_device_id *match;
	u64 (*tc_sched_घड़ी)(व्योम);
	u32 rate, भागided_rate = 0;
	पूर्णांक best_भागisor_idx = -1;
	पूर्णांक bits;
	पूर्णांक i;
	पूर्णांक ret;

	/* Protect against multiple calls */
	अगर (tcaddr)
		वापस 0;

	tc.regs = of_iomap(node->parent, 0);
	अगर (!tc.regs)
		वापस -ENXIO;

	t0_clk = of_clk_get_by_name(node->parent, "t0_clk");
	अगर (IS_ERR(t0_clk))
		वापस PTR_ERR(t0_clk);

	tc.slow_clk = of_clk_get_by_name(node->parent, "slow_clk");
	अगर (IS_ERR(tc.slow_clk))
		वापस PTR_ERR(tc.slow_clk);

	tc.clk[0] = t0_clk;
	tc.clk[1] = of_clk_get_by_name(node->parent, "t1_clk");
	अगर (IS_ERR(tc.clk[1]))
		tc.clk[1] = t0_clk;
	tc.clk[2] = of_clk_get_by_name(node->parent, "t2_clk");
	अगर (IS_ERR(tc.clk[2]))
		tc.clk[2] = t0_clk;

	tc.irq[2] = of_irq_get(node->parent, 2);
	अगर (tc.irq[2] <= 0) अणु
		tc.irq[2] = of_irq_get(node->parent, 0);
		अगर (tc.irq[2] <= 0)
			वापस -EINVAL;
	पूर्ण

	match = of_match_node(aपंचांगel_tcb_of_match, node->parent);
	अगर (!match)
		वापस -ENODEV;

	tc.tcb_config = match->data;
	bits = tc.tcb_config->counter_width;

	क्रम (i = 0; i < ARRAY_SIZE(tc.irq); i++)
		ग_लिखोl(ATMEL_TC_ALL_IRQ, tc.regs + ATMEL_TC_REG(i, IDR));

	ret = clk_prepare_enable(t0_clk);
	अगर (ret) अणु
		pr_debug("can't enable T0 clk\n");
		वापस ret;
	पूर्ण

	/* How fast will we be counting?  Pick something over 5 MHz.  */
	rate = (u32) clk_get_rate(t0_clk);
	i = 0;
	अगर (tc.tcb_config->has_gclk)
		i = 1;
	क्रम (; i < ARRAY_SIZE(aपंचांगel_tcb_भागisors); i++) अणु
		अचिन्हित भागisor = aपंचांगel_tcb_भागisors[i];
		अचिन्हित पंचांगp;

		पंचांगp = rate / भागisor;
		pr_debug("TC: %u / %-3u [%d] --> %u\n", rate, भागisor, i, पंचांगp);
		अगर ((best_भागisor_idx >= 0) && (पंचांगp < 5 * 1000 * 1000))
			अवरोध;
		भागided_rate = पंचांगp;
		best_भागisor_idx = i;
	पूर्ण

	clksrc.name = kbasename(node->parent->full_name);
	clkevt.clkevt.name = kbasename(node->parent->full_name);
	pr_debug("%s at %d.%03d MHz\n", clksrc.name, भागided_rate / 1000000,
			((भागided_rate % 1000000) + 500) / 1000);

	tcaddr = tc.regs;

	अगर (bits == 32) अणु
		/* use appropriate function to पढ़ो 32 bit counter */
		clksrc.पढ़ो = tc_get_cycles32;
		/* setup only channel 0 */
		tcb_setup_single_chan(&tc, best_भागisor_idx);
		tc_sched_घड़ी = tc_sched_घड़ी_पढ़ो32;
		tc_delay_समयr.पढ़ो_current_समयr = tc_delay_समयr_पढ़ो32;
	पूर्ण अन्यथा अणु
		/* we have three घड़ीs no matter what the
		 * underlying platक्रमm supports.
		 */
		ret = clk_prepare_enable(tc.clk[1]);
		अगर (ret) अणु
			pr_debug("can't enable T1 clk\n");
			जाओ err_disable_t0;
		पूर्ण
		/* setup both channel 0 & 1 */
		tcb_setup_dual_chan(&tc, best_भागisor_idx);
		tc_sched_घड़ी = tc_sched_घड़ी_पढ़ो;
		tc_delay_समयr.पढ़ो_current_समयr = tc_delay_समयr_पढ़ो;
	पूर्ण

	/* and away we go! */
	ret = घड़ीsource_रेजिस्टर_hz(&clksrc, भागided_rate);
	अगर (ret)
		जाओ err_disable_t1;

	/* channel 2:  periodic and oneshot समयr support */
	ret = setup_clkevents(&tc, best_भागisor_idx);
	अगर (ret)
		जाओ err_unरेजिस्टर_clksrc;

	sched_घड़ी_रेजिस्टर(tc_sched_घड़ी, 32, भागided_rate);

	tc_delay_समयr.freq = भागided_rate;
	रेजिस्टर_current_समयr_delay(&tc_delay_समयr);

	वापस 0;

err_unरेजिस्टर_clksrc:
	घड़ीsource_unरेजिस्टर(&clksrc);

err_disable_t1:
	अगर (bits != 32)
		clk_disable_unprepare(tc.clk[1]);

err_disable_t0:
	clk_disable_unprepare(t0_clk);

	tcaddr = शून्य;

	वापस ret;
पूर्ण
TIMER_OF_DECLARE(aपंचांगel_tcb_clksrc, "atmel,tcb-timer", tcb_clksrc_init);
