<शैली गुरु>
/*
 * Clocksource driver क्रम NXP LPC32xx/18xx/43xx समयr
 *
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 *
 * Based on:
 * समय-efm32 Copyright (C) 2013 Pengutronix
 * mach-lpc32xx/समयr.c Copyright (C) 2009 - 2010 NXP Semiconductors
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sched_घड़ी.h>

#घोषणा LPC32XX_TIMER_IR		0x000
#घोषणा  LPC32XX_TIMER_IR_MR0INT	BIT(0)
#घोषणा LPC32XX_TIMER_TCR		0x004
#घोषणा  LPC32XX_TIMER_TCR_CEN		BIT(0)
#घोषणा  LPC32XX_TIMER_TCR_CRST		BIT(1)
#घोषणा LPC32XX_TIMER_TC		0x008
#घोषणा LPC32XX_TIMER_PR		0x00c
#घोषणा LPC32XX_TIMER_MCR		0x014
#घोषणा  LPC32XX_TIMER_MCR_MR0I		BIT(0)
#घोषणा  LPC32XX_TIMER_MCR_MR0R		BIT(1)
#घोषणा  LPC32XX_TIMER_MCR_MR0S		BIT(2)
#घोषणा LPC32XX_TIMER_MR0		0x018
#घोषणा LPC32XX_TIMER_CTCR		0x070

काष्ठा lpc32xx_घड़ी_event_ddata अणु
	काष्ठा घड़ी_event_device evtdev;
	व्योम __iomem *base;
	u32 ticks_per_jअगरfy;
पूर्ण;

/* Needed क्रम the sched घड़ी */
अटल व्योम __iomem *घड़ीsource_समयr_counter;

अटल u64 notrace lpc32xx_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस पढ़ोl(घड़ीsource_समयr_counter);
पूर्ण

अटल अचिन्हित दीर्घ lpc32xx_delay_समयr_पढ़ो(व्योम)
अणु
	वापस पढ़ोl(घड़ीsource_समयr_counter);
पूर्ण

अटल काष्ठा delay_समयr lpc32xx_delay_समयr = अणु
	.पढ़ो_current_समयr = lpc32xx_delay_समयr_पढ़ो,
पूर्ण;

अटल पूर्णांक lpc32xx_clkevt_next_event(अचिन्हित दीर्घ delta,
				     काष्ठा घड़ी_event_device *evtdev)
अणु
	काष्ठा lpc32xx_घड़ी_event_ddata *ddata =
		container_of(evtdev, काष्ठा lpc32xx_घड़ी_event_ddata, evtdev);

	/*
	 * Place समयr in reset and program the delta in the match
	 * channel 0 (MR0). When the समयr counter matches the value
	 * in MR0 रेजिस्टर the match will trigger an पूर्णांकerrupt.
	 * After setup the समयr is released from reset and enabled.
	 */
	ग_लिखोl_relaxed(LPC32XX_TIMER_TCR_CRST, ddata->base + LPC32XX_TIMER_TCR);
	ग_लिखोl_relaxed(delta, ddata->base + LPC32XX_TIMER_MR0);
	ग_लिखोl_relaxed(LPC32XX_TIMER_TCR_CEN, ddata->base + LPC32XX_TIMER_TCR);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_clkevt_shutकरोwn(काष्ठा घड़ी_event_device *evtdev)
अणु
	काष्ठा lpc32xx_घड़ी_event_ddata *ddata =
		container_of(evtdev, काष्ठा lpc32xx_घड़ी_event_ddata, evtdev);

	/* Disable the समयr */
	ग_लिखोl_relaxed(0, ddata->base + LPC32XX_TIMER_TCR);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_clkevt_oneshot(काष्ठा घड़ी_event_device *evtdev)
अणु
	काष्ठा lpc32xx_घड़ी_event_ddata *ddata =
		container_of(evtdev, काष्ठा lpc32xx_घड़ी_event_ddata, evtdev);

	/*
	 * When using oneshot, we must also disable the समयr
	 * to रुको क्रम the first call to set_next_event().
	 */
	ग_लिखोl_relaxed(0, ddata->base + LPC32XX_TIMER_TCR);

	/* Enable पूर्णांकerrupt, reset on match and stop on match (MCR). */
	ग_लिखोl_relaxed(LPC32XX_TIMER_MCR_MR0I | LPC32XX_TIMER_MCR_MR0R |
		       LPC32XX_TIMER_MCR_MR0S, ddata->base + LPC32XX_TIMER_MCR);
	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_clkevt_periodic(काष्ठा घड़ी_event_device *evtdev)
अणु
	काष्ठा lpc32xx_घड़ी_event_ddata *ddata =
		container_of(evtdev, काष्ठा lpc32xx_घड़ी_event_ddata, evtdev);

	/* Enable पूर्णांकerrupt and reset on match. */
	ग_लिखोl_relaxed(LPC32XX_TIMER_MCR_MR0I | LPC32XX_TIMER_MCR_MR0R,
		       ddata->base + LPC32XX_TIMER_MCR);

	/*
	 * Place समयr in reset and program the delta in the match
	 * channel 0 (MR0).
	 */
	ग_लिखोl_relaxed(LPC32XX_TIMER_TCR_CRST, ddata->base + LPC32XX_TIMER_TCR);
	ग_लिखोl_relaxed(ddata->ticks_per_jअगरfy, ddata->base + LPC32XX_TIMER_MR0);
	ग_लिखोl_relaxed(LPC32XX_TIMER_TCR_CEN, ddata->base + LPC32XX_TIMER_TCR);

	वापस 0;
पूर्ण

अटल irqवापस_t lpc32xx_घड़ी_event_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा lpc32xx_घड़ी_event_ddata *ddata = dev_id;

	/* Clear match on channel 0 */
	ग_लिखोl_relaxed(LPC32XX_TIMER_IR_MR0INT, ddata->base + LPC32XX_TIMER_IR);

	ddata->evtdev.event_handler(&ddata->evtdev);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा lpc32xx_घड़ी_event_ddata lpc32xx_clk_event_ddata = अणु
	.evtdev = अणु
		.name			= "lpc3220 clockevent",
		.features		= CLOCK_EVT_FEAT_ONESHOT |
					  CLOCK_EVT_FEAT_PERIODIC,
		.rating			= 300,
		.set_next_event		= lpc32xx_clkevt_next_event,
		.set_state_shutकरोwn	= lpc32xx_clkevt_shutकरोwn,
		.set_state_oneshot	= lpc32xx_clkevt_oneshot,
		.set_state_periodic	= lpc32xx_clkevt_periodic,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init lpc32xx_घड़ीsource_init(काष्ठा device_node *np)
अणु
	व्योम __iomem *base;
	अचिन्हित दीर्घ rate;
	काष्ठा clk *clk;
	पूर्णांक ret;

	clk = of_clk_get_by_name(np, "timerclk");
	अगर (IS_ERR(clk)) अणु
		pr_err("clock get failed (%ld)\n", PTR_ERR(clk));
		वापस PTR_ERR(clk);
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		pr_err("clock enable failed (%d)\n", ret);
		जाओ err_clk_enable;
	पूर्ण

	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_err("unable to map registers\n");
		ret = -EADDRNOTAVAIL;
		जाओ err_iomap;
	पूर्ण

	/*
	 * Disable and reset समयr then set it to मुक्त running समयr
	 * mode (CTCR) with no prescaler (PR) or match operations (MCR).
	 * After setup the समयr is released from reset and enabled.
	 */
	ग_लिखोl_relaxed(LPC32XX_TIMER_TCR_CRST, base + LPC32XX_TIMER_TCR);
	ग_लिखोl_relaxed(0, base + LPC32XX_TIMER_PR);
	ग_लिखोl_relaxed(0, base + LPC32XX_TIMER_MCR);
	ग_लिखोl_relaxed(0, base + LPC32XX_TIMER_CTCR);
	ग_लिखोl_relaxed(LPC32XX_TIMER_TCR_CEN, base + LPC32XX_TIMER_TCR);

	rate = clk_get_rate(clk);
	ret = घड़ीsource_mmio_init(base + LPC32XX_TIMER_TC, "lpc3220 timer",
				    rate, 300, 32, घड़ीsource_mmio_पढ़ोl_up);
	अगर (ret) अणु
		pr_err("failed to init clocksource (%d)\n", ret);
		जाओ err_घड़ीsource_init;
	पूर्ण

	घड़ीsource_समयr_counter = base + LPC32XX_TIMER_TC;
	lpc32xx_delay_समयr.freq = rate;
	रेजिस्टर_current_समयr_delay(&lpc32xx_delay_समयr);
	sched_घड़ी_रेजिस्टर(lpc32xx_पढ़ो_sched_घड़ी, 32, rate);

	वापस 0;

err_घड़ीsource_init:
	iounmap(base);
err_iomap:
	clk_disable_unprepare(clk);
err_clk_enable:
	clk_put(clk);
	वापस ret;
पूर्ण

अटल पूर्णांक __init lpc32xx_घड़ीevent_init(काष्ठा device_node *np)
अणु
	व्योम __iomem *base;
	अचिन्हित दीर्घ rate;
	काष्ठा clk *clk;
	पूर्णांक ret, irq;

	clk = of_clk_get_by_name(np, "timerclk");
	अगर (IS_ERR(clk)) अणु
		pr_err("clock get failed (%ld)\n", PTR_ERR(clk));
		वापस PTR_ERR(clk);
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		pr_err("clock enable failed (%d)\n", ret);
		जाओ err_clk_enable;
	पूर्ण

	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_err("unable to map registers\n");
		ret = -EADDRNOTAVAIL;
		जाओ err_iomap;
	पूर्ण

	irq = irq_of_parse_and_map(np, 0);
	अगर (!irq) अणु
		pr_err("get irq failed\n");
		ret = -ENOENT;
		जाओ err_irq;
	पूर्ण

	/*
	 * Disable समयr and clear any pending पूर्णांकerrupt (IR) on match
	 * channel 0 (MR0). Clear the prescaler as it's not used.
	 */
	ग_लिखोl_relaxed(0, base + LPC32XX_TIMER_TCR);
	ग_लिखोl_relaxed(0, base + LPC32XX_TIMER_PR);
	ग_लिखोl_relaxed(0, base + LPC32XX_TIMER_CTCR);
	ग_लिखोl_relaxed(LPC32XX_TIMER_IR_MR0INT, base + LPC32XX_TIMER_IR);

	rate = clk_get_rate(clk);
	lpc32xx_clk_event_ddata.base = base;
	lpc32xx_clk_event_ddata.ticks_per_jअगरfy = DIV_ROUND_CLOSEST(rate, HZ);
	घड़ीevents_config_and_रेजिस्टर(&lpc32xx_clk_event_ddata.evtdev,
					rate, 1, -1);

	ret = request_irq(irq, lpc32xx_घड़ी_event_handler,
			  IRQF_TIMER | IRQF_IRQPOLL, "lpc3220 clockevent",
			  &lpc32xx_clk_event_ddata);
	अगर (ret) अणु
		pr_err("request irq failed\n");
		जाओ err_irq;
	पूर्ण

	वापस 0;

err_irq:
	iounmap(base);
err_iomap:
	clk_disable_unprepare(clk);
err_clk_enable:
	clk_put(clk);
	वापस ret;
पूर्ण

/*
 * This function निश्चितs that we have exactly one घड़ीsource and one
 * घड़ी_event_device in the end.
 */
अटल पूर्णांक __init lpc32xx_समयr_init(काष्ठा device_node *np)
अणु
	अटल पूर्णांक has_घड़ीsource, has_घड़ीevent;
	पूर्णांक ret = 0;

	अगर (!has_घड़ीsource) अणु
		ret = lpc32xx_घड़ीsource_init(np);
		अगर (!ret) अणु
			has_घड़ीsource = 1;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (!has_घड़ीevent) अणु
		ret = lpc32xx_घड़ीevent_init(np);
		अगर (!ret) अणु
			has_घड़ीevent = 1;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
TIMER_OF_DECLARE(lpc32xx_समयr, "nxp,lpc3220-timer", lpc32xx_समयr_init);
