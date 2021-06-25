<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Faraday Technology FTTMR010 समयr driver
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 *
 * Based on a reग_लिखो of arch/arm/mach-gemini/समयr.c:
 * Copyright (C) 2001-2006 Storlink, Corp.
 * Copyright (C) 2008-2009 Paulius Zaleckas <paulius.zaleckas@teltonika.lt>
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>

/*
 * Register definitions common क्रम all the समयr variants.
 */
#घोषणा TIMER1_COUNT		(0x00)
#घोषणा TIMER1_LOAD		(0x04)
#घोषणा TIMER1_MATCH1		(0x08)
#घोषणा TIMER1_MATCH2		(0x0c)
#घोषणा TIMER2_COUNT		(0x10)
#घोषणा TIMER2_LOAD		(0x14)
#घोषणा TIMER2_MATCH1		(0x18)
#घोषणा TIMER2_MATCH2		(0x1c)
#घोषणा TIMER3_COUNT		(0x20)
#घोषणा TIMER3_LOAD		(0x24)
#घोषणा TIMER3_MATCH1		(0x28)
#घोषणा TIMER3_MATCH2		(0x2c)
#घोषणा TIMER_CR		(0x30)

/*
 * Control रेजिस्टर set to clear क्रम ast2600 only.
 */
#घोषणा AST2600_TIMER_CR_CLR	(0x3c)

/*
 * Control रेजिस्टर (TMC30) bit fields क्रम ftपंचांगr010/gemini/moxart समयrs.
 */
#घोषणा TIMER_1_CR_ENABLE	BIT(0)
#घोषणा TIMER_1_CR_CLOCK	BIT(1)
#घोषणा TIMER_1_CR_INT		BIT(2)
#घोषणा TIMER_2_CR_ENABLE	BIT(3)
#घोषणा TIMER_2_CR_CLOCK	BIT(4)
#घोषणा TIMER_2_CR_INT		BIT(5)
#घोषणा TIMER_3_CR_ENABLE	BIT(6)
#घोषणा TIMER_3_CR_CLOCK	BIT(7)
#घोषणा TIMER_3_CR_INT		BIT(8)
#घोषणा TIMER_1_CR_UPDOWN	BIT(9)
#घोषणा TIMER_2_CR_UPDOWN	BIT(10)
#घोषणा TIMER_3_CR_UPDOWN	BIT(11)

/*
 * Control रेजिस्टर (TMC30) bit fields क्रम aspeed ast2400/ast2500 समयrs.
 * The aspeed समयrs move bits around in the control रेजिस्टर and lacks
 * bits क्रम setting the समयr to count upwards.
 */
#घोषणा TIMER_1_CR_ASPEED_ENABLE	BIT(0)
#घोषणा TIMER_1_CR_ASPEED_CLOCK		BIT(1)
#घोषणा TIMER_1_CR_ASPEED_INT		BIT(2)
#घोषणा TIMER_2_CR_ASPEED_ENABLE	BIT(4)
#घोषणा TIMER_2_CR_ASPEED_CLOCK		BIT(5)
#घोषणा TIMER_2_CR_ASPEED_INT		BIT(6)
#घोषणा TIMER_3_CR_ASPEED_ENABLE	BIT(8)
#घोषणा TIMER_3_CR_ASPEED_CLOCK		BIT(9)
#घोषणा TIMER_3_CR_ASPEED_INT		BIT(10)

/*
 * Interrupt status/mask रेजिस्टर definitions क्रम ftपंचांगr010/gemini/moxart
 * समयrs.
 * The रेजिस्टरs करोn't exist and they are not needed on aspeed समयrs
 * because:
 *   - aspeed समयr overflow पूर्णांकerrupt is controlled by bits in Control
 *     Register (TMC30).
 *   - aspeed समयrs always generate पूर्णांकerrupt when either one of the
 *     Match रेजिस्टरs equals to Status रेजिस्टर.
 */
#घोषणा TIMER_INTR_STATE	(0x34)
#घोषणा TIMER_INTR_MASK		(0x38)
#घोषणा TIMER_1_INT_MATCH1	BIT(0)
#घोषणा TIMER_1_INT_MATCH2	BIT(1)
#घोषणा TIMER_1_INT_OVERFLOW	BIT(2)
#घोषणा TIMER_2_INT_MATCH1	BIT(3)
#घोषणा TIMER_2_INT_MATCH2	BIT(4)
#घोषणा TIMER_2_INT_OVERFLOW	BIT(5)
#घोषणा TIMER_3_INT_MATCH1	BIT(6)
#घोषणा TIMER_3_INT_MATCH2	BIT(7)
#घोषणा TIMER_3_INT_OVERFLOW	BIT(8)
#घोषणा TIMER_INT_ALL_MASK	0x1ff

काष्ठा ftपंचांगr010 अणु
	व्योम __iomem *base;
	अचिन्हित पूर्णांक tick_rate;
	bool is_aspeed;
	u32 t1_enable_val;
	काष्ठा घड़ी_event_device clkevt;
	पूर्णांक (*समयr_shutकरोwn)(काष्ठा घड़ी_event_device *evt);
#अगर_घोषित CONFIG_ARM
	काष्ठा delay_समयr delay_समयr;
#पूर्ण_अगर
पूर्ण;

/*
 * A local singleton used by sched_घड़ी and delay समयr पढ़ोs, which are
 * fast and stateless
 */
अटल काष्ठा ftपंचांगr010 *local_ftपंचांगr;

अटल अंतरभूत काष्ठा ftपंचांगr010 *to_ftपंचांगr010(काष्ठा घड़ी_event_device *evt)
अणु
	वापस container_of(evt, काष्ठा ftपंचांगr010, clkevt);
पूर्ण

अटल अचिन्हित दीर्घ ftपंचांगr010_पढ़ो_current_समयr_up(व्योम)
अणु
	वापस पढ़ोl(local_ftपंचांगr->base + TIMER2_COUNT);
पूर्ण

अटल अचिन्हित दीर्घ ftपंचांगr010_पढ़ो_current_समयr_करोwn(व्योम)
अणु
	वापस ~पढ़ोl(local_ftपंचांगr->base + TIMER2_COUNT);
पूर्ण

अटल u64 notrace ftपंचांगr010_पढ़ो_sched_घड़ी_up(व्योम)
अणु
	वापस ftपंचांगr010_पढ़ो_current_समयr_up();
पूर्ण

अटल u64 notrace ftपंचांगr010_पढ़ो_sched_घड़ी_करोwn(व्योम)
अणु
	वापस ftपंचांगr010_पढ़ो_current_समयr_करोwn();
पूर्ण

अटल पूर्णांक ftपंचांगr010_समयr_set_next_event(अचिन्हित दीर्घ cycles,
				       काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ftपंचांगr010 *ftपंचांगr010 = to_ftपंचांगr010(evt);
	u32 cr;

	/* Stop */
	ftपंचांगr010->समयr_shutकरोwn(evt);

	अगर (ftपंचांगr010->is_aspeed) अणु
		/*
		 * ASPEED Timer Controller will load TIMER1_LOAD रेजिस्टर
		 * पूर्णांकo TIMER1_COUNT रेजिस्टर when the समयr is re-enabled.
		 */
		ग_लिखोl(cycles, ftपंचांगr010->base + TIMER1_LOAD);
	पूर्ण अन्यथा अणु
		/* Setup the match रेजिस्टर क्रमward in समय */
		cr = पढ़ोl(ftपंचांगr010->base + TIMER1_COUNT);
		ग_लिखोl(cr + cycles, ftपंचांगr010->base + TIMER1_MATCH1);
	पूर्ण

	/* Start */
	cr = पढ़ोl(ftपंचांगr010->base + TIMER_CR);
	cr |= ftपंचांगr010->t1_enable_val;
	ग_लिखोl(cr, ftपंचांगr010->base + TIMER_CR);

	वापस 0;
पूर्ण

अटल पूर्णांक ast2600_समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ftपंचांगr010 *ftपंचांगr010 = to_ftपंचांगr010(evt);

	/* Stop */
	ग_लिखोl(ftपंचांगr010->t1_enable_val, ftपंचांगr010->base + AST2600_TIMER_CR_CLR);

	वापस 0;
पूर्ण

अटल पूर्णांक ftपंचांगr010_समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ftपंचांगr010 *ftपंचांगr010 = to_ftपंचांगr010(evt);
	u32 cr;

	/* Stop */
	cr = पढ़ोl(ftपंचांगr010->base + TIMER_CR);
	cr &= ~ftपंचांगr010->t1_enable_val;
	ग_लिखोl(cr, ftपंचांगr010->base + TIMER_CR);

	वापस 0;
पूर्ण

अटल पूर्णांक ftपंचांगr010_समयr_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ftपंचांगr010 *ftपंचांगr010 = to_ftपंचांगr010(evt);
	u32 cr;

	/* Stop */
	ftपंचांगr010->समयr_shutकरोwn(evt);

	/* Setup counter start from 0 or ~0 */
	ग_लिखोl(0, ftपंचांगr010->base + TIMER1_COUNT);
	अगर (ftपंचांगr010->is_aspeed) अणु
		ग_लिखोl(~0, ftपंचांगr010->base + TIMER1_LOAD);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, ftपंचांगr010->base + TIMER1_LOAD);

		/* Enable पूर्णांकerrupt */
		cr = पढ़ोl(ftपंचांगr010->base + TIMER_INTR_MASK);
		cr &= ~(TIMER_1_INT_OVERFLOW | TIMER_1_INT_MATCH2);
		cr |= TIMER_1_INT_MATCH1;
		ग_लिखोl(cr, ftपंचांगr010->base + TIMER_INTR_MASK);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ftपंचांगr010_समयr_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ftपंचांगr010 *ftपंचांगr010 = to_ftपंचांगr010(evt);
	u32 period = DIV_ROUND_CLOSEST(ftपंचांगr010->tick_rate, HZ);
	u32 cr;

	/* Stop */
	ftपंचांगr010->समयr_shutकरोwn(evt);

	/* Setup समयr to fire at 1/HZ पूर्णांकervals. */
	अगर (ftपंचांगr010->is_aspeed) अणु
		ग_लिखोl(period, ftपंचांगr010->base + TIMER1_LOAD);
	पूर्ण अन्यथा अणु
		cr = 0xffffffff - (period - 1);
		ग_लिखोl(cr, ftपंचांगr010->base + TIMER1_COUNT);
		ग_लिखोl(cr, ftपंचांगr010->base + TIMER1_LOAD);

		/* Enable पूर्णांकerrupt on overflow */
		cr = पढ़ोl(ftपंचांगr010->base + TIMER_INTR_MASK);
		cr &= ~(TIMER_1_INT_MATCH1 | TIMER_1_INT_MATCH2);
		cr |= TIMER_1_INT_OVERFLOW;
		ग_लिखोl(cr, ftपंचांगr010->base + TIMER_INTR_MASK);
	पूर्ण

	/* Start the समयr */
	cr = पढ़ोl(ftपंचांगr010->base + TIMER_CR);
	cr |= ftपंचांगr010->t1_enable_val;
	ग_लिखोl(cr, ftपंचांगr010->base + TIMER_CR);

	वापस 0;
पूर्ण

/*
 * IRQ handler क्रम the समयr
 */
अटल irqवापस_t ftपंचांगr010_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	evt->event_handler(evt);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ast2600_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;
	काष्ठा ftपंचांगr010 *ftपंचांगr010 = to_ftपंचांगr010(evt);

	ग_लिखोl(0x1, ftपंचांगr010->base + TIMER_INTR_STATE);

	evt->event_handler(evt);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init ftपंचांगr010_common_init(काष्ठा device_node *np,
		bool is_aspeed,
		पूर्णांक (*समयr_shutकरोwn)(काष्ठा घड़ी_event_device *),
		irq_handler_t irq_handler)
अणु
	काष्ठा ftपंचांगr010 *ftपंचांगr010;
	पूर्णांक irq;
	काष्ठा clk *clk;
	पूर्णांक ret;
	u32 val;

	/*
	 * These implementations require a घड़ी reference.
	 * FIXME: we currently only support घड़ीing using PCLK
	 * and using EXTCLK is not supported in the driver.
	 */
	clk = of_clk_get_by_name(np, "PCLK");
	अगर (IS_ERR(clk)) अणु
		pr_err("could not get PCLK\n");
		वापस PTR_ERR(clk);
	पूर्ण
	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		pr_err("failed to enable PCLK\n");
		वापस ret;
	पूर्ण

	ftपंचांगr010 = kzalloc(माप(*ftपंचांगr010), GFP_KERNEL);
	अगर (!ftपंचांगr010) अणु
		ret = -ENOMEM;
		जाओ out_disable_घड़ी;
	पूर्ण
	ftपंचांगr010->tick_rate = clk_get_rate(clk);

	ftपंचांगr010->base = of_iomap(np, 0);
	अगर (!ftपंचांगr010->base) अणु
		pr_err("Can't remap registers\n");
		ret = -ENXIO;
		जाओ out_मुक्त;
	पूर्ण
	/* IRQ क्रम समयr 1 */
	irq = irq_of_parse_and_map(np, 0);
	अगर (irq <= 0) अणु
		pr_err("Can't parse IRQ\n");
		ret = -EINVAL;
		जाओ out_unmap;
	पूर्ण

	/*
	 * The Aspeed समयrs move bits around in the control रेजिस्टर.
	 */
	अगर (is_aspeed) अणु
		ftपंचांगr010->t1_enable_val = TIMER_1_CR_ASPEED_ENABLE |
			TIMER_1_CR_ASPEED_INT;
		ftपंचांगr010->is_aspeed = true;
	पूर्ण अन्यथा अणु
		ftपंचांगr010->t1_enable_val = TIMER_1_CR_ENABLE | TIMER_1_CR_INT;

		/*
		 * Reset the पूर्णांकerrupt mask and status
		 */
		ग_लिखोl(TIMER_INT_ALL_MASK, ftपंचांगr010->base + TIMER_INTR_MASK);
		ग_लिखोl(0, ftपंचांगr010->base + TIMER_INTR_STATE);
	पूर्ण

	/*
	 * Enable समयr 1 count up, समयr 2 count up, except on Aspeed,
	 * where everything just counts करोwn.
	 */
	अगर (is_aspeed)
		val = TIMER_2_CR_ASPEED_ENABLE;
	अन्यथा अणु
		val = TIMER_2_CR_ENABLE | TIMER_1_CR_UPDOWN |
			TIMER_2_CR_UPDOWN;
	पूर्ण
	ग_लिखोl(val, ftपंचांगr010->base + TIMER_CR);

	/*
	 * Setup मुक्त-running घड़ीsource समयr (पूर्णांकerrupts
	 * disabled.)
	 */
	local_ftपंचांगr = ftपंचांगr010;
	ग_लिखोl(0, ftपंचांगr010->base + TIMER2_COUNT);
	ग_लिखोl(0, ftपंचांगr010->base + TIMER2_MATCH1);
	ग_लिखोl(0, ftपंचांगr010->base + TIMER2_MATCH2);

	अगर (ftपंचांगr010->is_aspeed) अणु
		ग_लिखोl(~0, ftपंचांगr010->base + TIMER2_LOAD);
		घड़ीsource_mmio_init(ftपंचांगr010->base + TIMER2_COUNT,
				      "FTTMR010-TIMER2",
				      ftपंचांगr010->tick_rate,
				      300, 32, घड़ीsource_mmio_पढ़ोl_करोwn);
		sched_घड़ी_रेजिस्टर(ftपंचांगr010_पढ़ो_sched_घड़ी_करोwn, 32,
				     ftपंचांगr010->tick_rate);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, ftपंचांगr010->base + TIMER2_LOAD);
		घड़ीsource_mmio_init(ftपंचांगr010->base + TIMER2_COUNT,
				      "FTTMR010-TIMER2",
				      ftपंचांगr010->tick_rate,
				      300, 32, घड़ीsource_mmio_पढ़ोl_up);
		sched_घड़ी_रेजिस्टर(ftपंचांगr010_पढ़ो_sched_घड़ी_up, 32,
				     ftपंचांगr010->tick_rate);
	पूर्ण

	ftपंचांगr010->समयr_shutकरोwn = समयr_shutकरोwn;

	/*
	 * Setup घड़ीevent समयr (पूर्णांकerrupt-driven) on समयr 1.
	 */
	ग_लिखोl(0, ftपंचांगr010->base + TIMER1_COUNT);
	ग_लिखोl(0, ftपंचांगr010->base + TIMER1_LOAD);
	ग_लिखोl(0, ftपंचांगr010->base + TIMER1_MATCH1);
	ग_लिखोl(0, ftपंचांगr010->base + TIMER1_MATCH2);
	ret = request_irq(irq, irq_handler, IRQF_TIMER,
			  "FTTMR010-TIMER1", &ftपंचांगr010->clkevt);
	अगर (ret) अणु
		pr_err("FTTMR010-TIMER1 no IRQ\n");
		जाओ out_unmap;
	पूर्ण

	ftपंचांगr010->clkevt.name = "FTTMR010-TIMER1";
	/* Reasonably fast and accurate घड़ी event */
	ftपंचांगr010->clkevt.rating = 300;
	ftपंचांगr010->clkevt.features = CLOCK_EVT_FEAT_PERIODIC |
		CLOCK_EVT_FEAT_ONESHOT;
	ftपंचांगr010->clkevt.set_next_event = ftपंचांगr010_समयr_set_next_event;
	ftपंचांगr010->clkevt.set_state_shutकरोwn = ftपंचांगr010->समयr_shutकरोwn;
	ftपंचांगr010->clkevt.set_state_periodic = ftपंचांगr010_समयr_set_periodic;
	ftपंचांगr010->clkevt.set_state_oneshot = ftपंचांगr010_समयr_set_oneshot;
	ftपंचांगr010->clkevt.tick_resume = ftपंचांगr010->समयr_shutकरोwn;
	ftपंचांगr010->clkevt.cpumask = cpumask_of(0);
	ftपंचांगr010->clkevt.irq = irq;
	घड़ीevents_config_and_रेजिस्टर(&ftपंचांगr010->clkevt,
					ftपंचांगr010->tick_rate,
					1, 0xffffffff);

#अगर_घोषित CONFIG_ARM
	/* Also use this समयr क्रम delays */
	अगर (ftपंचांगr010->is_aspeed)
		ftपंचांगr010->delay_समयr.पढ़ो_current_समयr =
			ftपंचांगr010_पढ़ो_current_समयr_करोwn;
	अन्यथा
		ftपंचांगr010->delay_समयr.पढ़ो_current_समयr =
			ftपंचांगr010_पढ़ो_current_समयr_up;
	ftपंचांगr010->delay_समयr.freq = ftपंचांगr010->tick_rate;
	रेजिस्टर_current_समयr_delay(&ftपंचांगr010->delay_समयr);
#पूर्ण_अगर

	वापस 0;

out_unmap:
	iounmap(ftपंचांगr010->base);
out_मुक्त:
	kमुक्त(ftपंचांगr010);
out_disable_घड़ी:
	clk_disable_unprepare(clk);

	वापस ret;
पूर्ण

अटल __init पूर्णांक ast2600_समयr_init(काष्ठा device_node *np)
अणु
	वापस ftपंचांगr010_common_init(np, true,
			ast2600_समयr_shutकरोwn,
			ast2600_समयr_पूर्णांकerrupt);
पूर्ण

अटल __init पूर्णांक aspeed_समयr_init(काष्ठा device_node *np)
अणु
	वापस ftपंचांगr010_common_init(np, true,
			ftपंचांगr010_समयr_shutकरोwn,
			ftपंचांगr010_समयr_पूर्णांकerrupt);
पूर्ण

अटल __init पूर्णांक ftपंचांगr010_समयr_init(काष्ठा device_node *np)
अणु
	वापस ftपंचांगr010_common_init(np, false,
			ftपंचांगr010_समयr_shutकरोwn,
			ftपंचांगr010_समयr_पूर्णांकerrupt);
पूर्ण

TIMER_OF_DECLARE(ftपंचांगr010, "faraday,fttmr010", ftपंचांगr010_समयr_init);
TIMER_OF_DECLARE(gemini, "cortina,gemini-timer", ftपंचांगr010_समयr_init);
TIMER_OF_DECLARE(moxart, "moxa,moxart-timer", ftपंचांगr010_समयr_init);
TIMER_OF_DECLARE(ast2400, "aspeed,ast2400-timer", aspeed_समयr_init);
TIMER_OF_DECLARE(ast2500, "aspeed,ast2500-timer", aspeed_समयr_init);
TIMER_OF_DECLARE(ast2600, "aspeed,ast2600-timer", ast2600_समयr_init);
