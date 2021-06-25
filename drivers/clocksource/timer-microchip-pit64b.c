<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * 64-bit Periodic Interval Timer driver
 *
 * Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
 *
 * Author: Claudiu Beznea <claudiu.beznea@microchip.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/slab.h>

#घोषणा MCHP_PIT64B_CR			0x00	/* Control Register */
#घोषणा MCHP_PIT64B_CR_START		BIT(0)
#घोषणा MCHP_PIT64B_CR_SWRST		BIT(8)

#घोषणा MCHP_PIT64B_MR			0x04	/* Mode Register */
#घोषणा MCHP_PIT64B_MR_CONT		BIT(0)
#घोषणा MCHP_PIT64B_MR_ONE_SHOT		(0)
#घोषणा MCHP_PIT64B_MR_SGCLK		BIT(3)
#घोषणा MCHP_PIT64B_MR_PRES		GENMASK(11, 8)

#घोषणा MCHP_PIT64B_LSB_PR		0x08	/* LSB Period Register */

#घोषणा MCHP_PIT64B_MSB_PR		0x0C	/* MSB Period Register */

#घोषणा MCHP_PIT64B_IER			0x10	/* Interrupt Enable Register */
#घोषणा MCHP_PIT64B_IER_PERIOD		BIT(0)

#घोषणा MCHP_PIT64B_ISR			0x1C	/* Interrupt Status Register */

#घोषणा MCHP_PIT64B_TLSBR		0x20	/* Timer LSB Register */

#घोषणा MCHP_PIT64B_TMSBR		0x24	/* Timer MSB Register */

#घोषणा MCHP_PIT64B_PRES_MAX		0x10
#घोषणा MCHP_PIT64B_LSBMASK		GENMASK_ULL(31, 0)
#घोषणा MCHP_PIT64B_PRES_TO_MODE(p)	(MCHP_PIT64B_MR_PRES & ((p) << 8))
#घोषणा MCHP_PIT64B_MODE_TO_PRES(m)	((MCHP_PIT64B_MR_PRES & (m)) >> 8)
#घोषणा MCHP_PIT64B_DEF_CS_FREQ		5000000UL	/* 5 MHz */
#घोषणा MCHP_PIT64B_DEF_CE_FREQ		32768		/* 32 KHz */

#घोषणा MCHP_PIT64B_NAME		"pit64b"

/**
 * काष्ठा mchp_pit64b_समयr - PIT64B समयr data काष्ठाure
 * @base: base address of PIT64B hardware block
 * @pclk: PIT64B's peripheral घड़ी
 * @gclk: PIT64B's generic घड़ी
 * @mode: precomputed value क्रम mode रेजिस्टर
 */
काष्ठा mchp_pit64b_समयr अणु
	व्योम __iomem	*base;
	काष्ठा clk	*pclk;
	काष्ठा clk	*gclk;
	u32		mode;
पूर्ण;

/**
 * mchp_pit64b_clkevt - PIT64B घड़ीevent data काष्ठाure
 * @समयr: PIT64B समयr
 * @clkevt: घड़ीevent
 */
काष्ठा mchp_pit64b_clkevt अणु
	काष्ठा mchp_pit64b_समयr	समयr;
	काष्ठा घड़ी_event_device	clkevt;
पूर्ण;

#घोषणा clkevt_to_mchp_pit64b_समयr(x) \
	((काष्ठा mchp_pit64b_समयr *)container_of(x,\
		काष्ठा mchp_pit64b_clkevt, clkevt))

/**
 * mchp_pit64b_clksrc - PIT64B घड़ीsource data काष्ठाure
 * @समयr: PIT64B समयr
 * @clksrc: घड़ीsource
 */
काष्ठा mchp_pit64b_clksrc अणु
	काष्ठा mchp_pit64b_समयr	समयr;
	काष्ठा घड़ीsource		clksrc;
पूर्ण;

#घोषणा clksrc_to_mchp_pit64b_समयr(x) \
	((काष्ठा mchp_pit64b_समयr *)container_of(x,\
		काष्ठा mchp_pit64b_clksrc, clksrc))

/* Base address क्रम घड़ीsource समयr. */
अटल व्योम __iomem *mchp_pit64b_cs_base;
/* Default cycles क्रम घड़ीevent समयr. */
अटल u64 mchp_pit64b_ce_cycles;

अटल अंतरभूत u64 mchp_pit64b_cnt_पढ़ो(व्योम __iomem *base)
अणु
	अचिन्हित दीर्घ	flags;
	u32		low, high;

	raw_local_irq_save(flags);

	/*
	 * When using a 64 bit period TLSB must be पढ़ो first, followed by the
	 * पढ़ो of TMSB. This sequence generates an atomic पढ़ो of the 64 bit
	 * समयr value whatever the lapse of समय between the accesses.
	 */
	low = पढ़ोl_relaxed(base + MCHP_PIT64B_TLSBR);
	high = पढ़ोl_relaxed(base + MCHP_PIT64B_TMSBR);

	raw_local_irq_restore(flags);

	वापस (((u64)high << 32) | low);
पूर्ण

अटल अंतरभूत व्योम mchp_pit64b_reset(काष्ठा mchp_pit64b_समयr *समयr,
				     u64 cycles, u32 mode, u32 irqs)
अणु
	u32 low, high;

	low = cycles & MCHP_PIT64B_LSBMASK;
	high = cycles >> 32;

	ग_लिखोl_relaxed(MCHP_PIT64B_CR_SWRST, समयr->base + MCHP_PIT64B_CR);
	ग_लिखोl_relaxed(mode | समयr->mode, समयr->base + MCHP_PIT64B_MR);
	ग_लिखोl_relaxed(high, समयr->base + MCHP_PIT64B_MSB_PR);
	ग_लिखोl_relaxed(low, समयr->base + MCHP_PIT64B_LSB_PR);
	ग_लिखोl_relaxed(irqs, समयr->base + MCHP_PIT64B_IER);
	ग_लिखोl_relaxed(MCHP_PIT64B_CR_START, समयr->base + MCHP_PIT64B_CR);
पूर्ण

अटल व्योम mchp_pit64b_suspend(काष्ठा mchp_pit64b_समयr *समयr)
अणु
	ग_लिखोl_relaxed(MCHP_PIT64B_CR_SWRST, समयr->base + MCHP_PIT64B_CR);
	अगर (समयr->mode & MCHP_PIT64B_MR_SGCLK)
		clk_disable_unprepare(समयr->gclk);
	clk_disable_unprepare(समयr->pclk);
पूर्ण

अटल व्योम mchp_pit64b_resume(काष्ठा mchp_pit64b_समयr *समयr)
अणु
	clk_prepare_enable(समयr->pclk);
	अगर (समयr->mode & MCHP_PIT64B_MR_SGCLK)
		clk_prepare_enable(समयr->gclk);
पूर्ण

अटल व्योम mchp_pit64b_clksrc_suspend(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा mchp_pit64b_समयr *समयr = clksrc_to_mchp_pit64b_समयr(cs);

	mchp_pit64b_suspend(समयr);
पूर्ण

अटल व्योम mchp_pit64b_clksrc_resume(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा mchp_pit64b_समयr *समयr = clksrc_to_mchp_pit64b_समयr(cs);

	mchp_pit64b_resume(समयr);
	mchp_pit64b_reset(समयr, ULदीर्घ_उच्च, MCHP_PIT64B_MR_CONT, 0);
पूर्ण

अटल u64 mchp_pit64b_clksrc_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस mchp_pit64b_cnt_पढ़ो(mchp_pit64b_cs_base);
पूर्ण

अटल u64 mchp_pit64b_sched_पढ़ो_clk(व्योम)
अणु
	वापस mchp_pit64b_cnt_पढ़ो(mchp_pit64b_cs_base);
पूर्ण

अटल पूर्णांक mchp_pit64b_clkevt_shutकरोwn(काष्ठा घड़ी_event_device *cedev)
अणु
	काष्ठा mchp_pit64b_समयr *समयr = clkevt_to_mchp_pit64b_समयr(cedev);

	ग_लिखोl_relaxed(MCHP_PIT64B_CR_SWRST, समयr->base + MCHP_PIT64B_CR);

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_pit64b_clkevt_set_periodic(काष्ठा घड़ी_event_device *cedev)
अणु
	काष्ठा mchp_pit64b_समयr *समयr = clkevt_to_mchp_pit64b_समयr(cedev);

	mchp_pit64b_reset(समयr, mchp_pit64b_ce_cycles, MCHP_PIT64B_MR_CONT,
			  MCHP_PIT64B_IER_PERIOD);

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_pit64b_clkevt_set_next_event(अचिन्हित दीर्घ evt,
					     काष्ठा घड़ी_event_device *cedev)
अणु
	काष्ठा mchp_pit64b_समयr *समयr = clkevt_to_mchp_pit64b_समयr(cedev);

	mchp_pit64b_reset(समयr, evt, MCHP_PIT64B_MR_ONE_SHOT,
			  MCHP_PIT64B_IER_PERIOD);

	वापस 0;
पूर्ण

अटल व्योम mchp_pit64b_clkevt_suspend(काष्ठा घड़ी_event_device *cedev)
अणु
	काष्ठा mchp_pit64b_समयr *समयr = clkevt_to_mchp_pit64b_समयr(cedev);

	mchp_pit64b_suspend(समयr);
पूर्ण

अटल व्योम mchp_pit64b_clkevt_resume(काष्ठा घड़ी_event_device *cedev)
अणु
	काष्ठा mchp_pit64b_समयr *समयr = clkevt_to_mchp_pit64b_समयr(cedev);

	mchp_pit64b_resume(समयr);
पूर्ण

अटल irqवापस_t mchp_pit64b_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mchp_pit64b_clkevt *irq_data = dev_id;

	/* Need to clear the पूर्णांकerrupt. */
	पढ़ोl_relaxed(irq_data->समयr.base + MCHP_PIT64B_ISR);

	irq_data->clkevt.event_handler(&irq_data->clkevt);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __init mchp_pit64b_pres_compute(u32 *pres, u32 clk_rate,
					    u32 max_rate)
अणु
	u32 पंचांगp;

	क्रम (*pres = 0; *pres < MCHP_PIT64B_PRES_MAX; (*pres)++) अणु
		पंचांगp = clk_rate / (*pres + 1);
		अगर (पंचांगp <= max_rate)
			अवरोध;
	पूर्ण

	/* Use the biggest prescaler अगर we didn't match one. */
	अगर (*pres == MCHP_PIT64B_PRES_MAX)
		*pres = MCHP_PIT64B_PRES_MAX - 1;
पूर्ण

/**
 * mchp_pit64b_init_mode - prepare PIT64B mode रेजिस्टर value to be used at
 *			   runसमय; this includes prescaler and SGCLK bit
 *
 * PIT64B समयr may be fed by gclk or pclk. When gclk is used its rate has to
 * be at least 3 बार lower that pclk's rate. pclk rate is fixed, gclk rate
 * could be changed via घड़ी APIs. The chosen घड़ी (pclk or gclk) could be
 * भागided by the पूर्णांकernal PIT64B's भागider.
 *
 * This function, first tries to use GCLK by requesting the desired rate from
 * PMC and then using the पूर्णांकernal PIT64B prescaler, अगर any, to reach the
 * requested rate. If PCLK/GCLK < 3 (condition requested by PIT64B hardware)
 * then the function falls back on using PCLK as घड़ी source क्रम PIT64B समयr
 * choosing the highest prescaler in हाल it करोesn't locate one to match the
 * requested frequency.
 *
 * Below is presented the PIT64B block in relation with PMC:
 *
 *                                PIT64B
 *  PMC             +------------------------------------+
 * +----+           |   +-----+                          |
 * |    |-->gclk -->|-->|     |    +---------+  +-----+  |
 * |    |           |   | MUX |--->| Divider |->|समयr|  |
 * |    |-->pclk -->|-->|     |    +---------+  +-----+  |
 * +----+           |   +-----+                          |
 *                  |      ^                             |
 *                  |     sel                            |
 *                  +------------------------------------+
 *
 * Where:
 *	- gclk rate <= pclk rate/3
 *	- gclk rate could be requested from PMC
 *	- pclk rate is fixed (cannot be requested from PMC)
 */
अटल पूर्णांक __init mchp_pit64b_init_mode(काष्ठा mchp_pit64b_समयr *समयr,
					अचिन्हित दीर्घ max_rate)
अणु
	अचिन्हित दीर्घ pclk_rate, dअगरf = 0, best_dअगरf = अच_दीर्घ_उच्च;
	दीर्घ gclk_round = 0;
	u32 pres, best_pres = 0;

	pclk_rate = clk_get_rate(समयr->pclk);
	अगर (!pclk_rate)
		वापस -EINVAL;

	समयr->mode = 0;

	/* Try using GCLK. */
	gclk_round = clk_round_rate(समयr->gclk, max_rate);
	अगर (gclk_round < 0)
		जाओ pclk;

	अगर (pclk_rate / gclk_round < 3)
		जाओ pclk;

	mchp_pit64b_pres_compute(&pres, gclk_round, max_rate);
	best_dअगरf = असल(gclk_round / (pres + 1) - max_rate);
	best_pres = pres;

	अगर (!best_dअगरf) अणु
		समयr->mode |= MCHP_PIT64B_MR_SGCLK;
		clk_set_rate(समयr->gclk, gclk_round);
		जाओ करोne;
	पूर्ण

pclk:
	/* Check अगर requested rate could be obtained using PCLK. */
	mchp_pit64b_pres_compute(&pres, pclk_rate, max_rate);
	dअगरf = असल(pclk_rate / (pres + 1) - max_rate);

	अगर (best_dअगरf > dअगरf) अणु
		/* Use PCLK. */
		best_pres = pres;
	पूर्ण अन्यथा अणु
		/* Use GCLK. */
		समयr->mode |= MCHP_PIT64B_MR_SGCLK;
		clk_set_rate(समयr->gclk, gclk_round);
	पूर्ण

करोne:
	समयr->mode |= MCHP_PIT64B_PRES_TO_MODE(best_pres);

	pr_info("PIT64B: using clk=%s with prescaler %u, freq=%lu [Hz]\n",
		समयr->mode & MCHP_PIT64B_MR_SGCLK ? "gclk" : "pclk", best_pres,
		समयr->mode & MCHP_PIT64B_MR_SGCLK ?
		gclk_round / (best_pres + 1) : pclk_rate / (best_pres + 1));

	वापस 0;
पूर्ण

अटल पूर्णांक __init mchp_pit64b_init_clksrc(काष्ठा mchp_pit64b_समयr *समयr,
					  u32 clk_rate)
अणु
	काष्ठा mchp_pit64b_clksrc *cs;
	पूर्णांक ret;

	cs = kzalloc(माप(*cs), GFP_KERNEL);
	अगर (!cs)
		वापस -ENOMEM;

	mchp_pit64b_reset(समयr, ULदीर्घ_उच्च, MCHP_PIT64B_MR_CONT, 0);

	mchp_pit64b_cs_base = समयr->base;

	cs->समयr.base = समयr->base;
	cs->समयr.pclk = समयr->pclk;
	cs->समयr.gclk = समयr->gclk;
	cs->समयr.mode = समयr->mode;
	cs->clksrc.name = MCHP_PIT64B_NAME;
	cs->clksrc.mask = CLOCKSOURCE_MASK(64);
	cs->clksrc.flags = CLOCK_SOURCE_IS_CONTINUOUS;
	cs->clksrc.rating = 210;
	cs->clksrc.पढ़ो = mchp_pit64b_clksrc_पढ़ो;
	cs->clksrc.suspend = mchp_pit64b_clksrc_suspend;
	cs->clksrc.resume = mchp_pit64b_clksrc_resume;

	ret = घड़ीsource_रेजिस्टर_hz(&cs->clksrc, clk_rate);
	अगर (ret) अणु
		pr_debug("clksrc: Failed to register PIT64B clocksource!\n");

		/* Stop समयr. */
		ग_लिखोl_relaxed(MCHP_PIT64B_CR_SWRST,
			       समयr->base + MCHP_PIT64B_CR);
		kमुक्त(cs);

		वापस ret;
	पूर्ण

	sched_घड़ी_रेजिस्टर(mchp_pit64b_sched_पढ़ो_clk, 64, clk_rate);

	वापस 0;
पूर्ण

अटल पूर्णांक __init mchp_pit64b_init_clkevt(काष्ठा mchp_pit64b_समयr *समयr,
					  u32 clk_rate, u32 irq)
अणु
	काष्ठा mchp_pit64b_clkevt *ce;
	पूर्णांक ret;

	ce = kzalloc(माप(*ce), GFP_KERNEL);
	अगर (!ce)
		वापस -ENOMEM;

	mchp_pit64b_ce_cycles = DIV_ROUND_CLOSEST(clk_rate, HZ);

	ce->समयr.base = समयr->base;
	ce->समयr.pclk = समयr->pclk;
	ce->समयr.gclk = समयr->gclk;
	ce->समयr.mode = समयr->mode;
	ce->clkevt.name = MCHP_PIT64B_NAME;
	ce->clkevt.features = CLOCK_EVT_FEAT_ONESHOT | CLOCK_EVT_FEAT_PERIODIC;
	ce->clkevt.rating = 150;
	ce->clkevt.set_state_shutकरोwn = mchp_pit64b_clkevt_shutकरोwn;
	ce->clkevt.set_state_periodic = mchp_pit64b_clkevt_set_periodic;
	ce->clkevt.set_next_event = mchp_pit64b_clkevt_set_next_event;
	ce->clkevt.suspend = mchp_pit64b_clkevt_suspend;
	ce->clkevt.resume = mchp_pit64b_clkevt_resume;
	ce->clkevt.cpumask = cpumask_of(0);
	ce->clkevt.irq = irq;

	ret = request_irq(irq, mchp_pit64b_पूर्णांकerrupt, IRQF_TIMER,
			  "pit64b_tick", ce);
	अगर (ret) अणु
		pr_debug("clkevt: Failed to setup PIT64B IRQ\n");
		kमुक्त(ce);
		वापस ret;
	पूर्ण

	घड़ीevents_config_and_रेजिस्टर(&ce->clkevt, clk_rate, 1, अच_दीर्घ_उच्च);

	वापस 0;
पूर्ण

अटल पूर्णांक __init mchp_pit64b_dt_init_समयr(काष्ठा device_node *node,
					    bool clkevt)
अणु
	u32 freq = clkevt ? MCHP_PIT64B_DEF_CE_FREQ : MCHP_PIT64B_DEF_CS_FREQ;
	काष्ठा mchp_pit64b_समयr समयr;
	अचिन्हित दीर्घ clk_rate;
	u32 irq = 0;
	पूर्णांक ret;

	/* Parse DT node. */
	समयr.pclk = of_clk_get_by_name(node, "pclk");
	अगर (IS_ERR(समयr.pclk))
		वापस PTR_ERR(समयr.pclk);

	समयr.gclk = of_clk_get_by_name(node, "gclk");
	अगर (IS_ERR(समयr.gclk))
		वापस PTR_ERR(समयr.gclk);

	समयr.base = of_iomap(node, 0);
	अगर (!समयr.base)
		वापस -ENXIO;

	अगर (clkevt) अणु
		irq = irq_of_parse_and_map(node, 0);
		अगर (!irq) अणु
			ret = -ENODEV;
			जाओ io_unmap;
		पूर्ण
	पूर्ण

	/* Initialize mode (prescaler + SGCK bit). To be used at runसमय. */
	ret = mchp_pit64b_init_mode(&समयr, freq);
	अगर (ret)
		जाओ irq_unmap;

	ret = clk_prepare_enable(समयr.pclk);
	अगर (ret)
		जाओ irq_unmap;

	अगर (समयr.mode & MCHP_PIT64B_MR_SGCLK) अणु
		ret = clk_prepare_enable(समयr.gclk);
		अगर (ret)
			जाओ pclk_unprepare;

		clk_rate = clk_get_rate(समयr.gclk);
	पूर्ण अन्यथा अणु
		clk_rate = clk_get_rate(समयr.pclk);
	पूर्ण
	clk_rate = clk_rate / (MCHP_PIT64B_MODE_TO_PRES(समयr.mode) + 1);

	अगर (clkevt)
		ret = mchp_pit64b_init_clkevt(&समयr, clk_rate, irq);
	अन्यथा
		ret = mchp_pit64b_init_clksrc(&समयr, clk_rate);

	अगर (ret)
		जाओ gclk_unprepare;

	वापस 0;

gclk_unprepare:
	अगर (समयr.mode & MCHP_PIT64B_MR_SGCLK)
		clk_disable_unprepare(समयr.gclk);
pclk_unprepare:
	clk_disable_unprepare(समयr.pclk);
irq_unmap:
	irq_dispose_mapping(irq);
io_unmap:
	iounmap(समयr.base);

	वापस ret;
पूर्ण

अटल पूर्णांक __init mchp_pit64b_dt_init(काष्ठा device_node *node)
अणु
	अटल पूर्णांक inits;

	चयन (inits++) अणु
	हाल 0:
		/* 1st request, रेजिस्टर घड़ीevent. */
		वापस mchp_pit64b_dt_init_समयr(node, true);
	हाल 1:
		/* 2nd request, रेजिस्टर घड़ीsource. */
		वापस mchp_pit64b_dt_init_समयr(node, false);
	पूर्ण

	/* The rest, करोn't care. */
	वापस -EINVAL;
पूर्ण

TIMER_OF_DECLARE(mchp_pit64b, "microchip,sam9x60-pit64b", mchp_pit64b_dt_init);
