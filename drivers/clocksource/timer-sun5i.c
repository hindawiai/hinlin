<शैली गुरु>
/*
 * Allwinner SoCs hsसमयr driver.
 *
 * Copyright (C) 2013 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#घोषणा TIMER_IRQ_EN_REG		0x00
#घोषणा TIMER_IRQ_EN(val)			BIT(val)
#घोषणा TIMER_IRQ_ST_REG		0x04
#घोषणा TIMER_CTL_REG(val)		(0x20 * (val) + 0x10)
#घोषणा TIMER_CTL_ENABLE			BIT(0)
#घोषणा TIMER_CTL_RELOAD			BIT(1)
#घोषणा TIMER_CTL_CLK_PRES(val)			(((val) & 0x7) << 4)
#घोषणा TIMER_CTL_ONESHOT			BIT(7)
#घोषणा TIMER_INTVAL_LO_REG(val)	(0x20 * (val) + 0x14)
#घोषणा TIMER_INTVAL_HI_REG(val)	(0x20 * (val) + 0x18)
#घोषणा TIMER_CNTVAL_LO_REG(val)	(0x20 * (val) + 0x1c)
#घोषणा TIMER_CNTVAL_HI_REG(val)	(0x20 * (val) + 0x20)

#घोषणा TIMER_SYNC_TICKS	3

काष्ठा sun5i_समयr अणु
	व्योम __iomem		*base;
	काष्ठा clk		*clk;
	काष्ठा notअगरier_block	clk_rate_cb;
	u32			ticks_per_jअगरfy;
पूर्ण;

#घोषणा to_sun5i_समयr(x) \
	container_of(x, काष्ठा sun5i_समयr, clk_rate_cb)

काष्ठा sun5i_समयr_clksrc अणु
	काष्ठा sun5i_समयr	समयr;
	काष्ठा घड़ीsource	clksrc;
पूर्ण;

#घोषणा to_sun5i_समयr_clksrc(x) \
	container_of(x, काष्ठा sun5i_समयr_clksrc, clksrc)

काष्ठा sun5i_समयr_clkevt अणु
	काष्ठा sun5i_समयr		समयr;
	काष्ठा घड़ी_event_device	clkevt;
पूर्ण;

#घोषणा to_sun5i_समयr_clkevt(x) \
	container_of(x, काष्ठा sun5i_समयr_clkevt, clkevt)

/*
 * When we disable a समयr, we need to रुको at least क्रम 2 cycles of
 * the समयr source घड़ी. We will use क्रम that the घड़ीsource समयr
 * that is alपढ़ोy setup and runs at the same frequency than the other
 * समयrs, and we never will be disabled.
 */
अटल व्योम sun5i_clkevt_sync(काष्ठा sun5i_समयr_clkevt *ce)
अणु
	u32 old = पढ़ोl(ce->समयr.base + TIMER_CNTVAL_LO_REG(1));

	जबतक ((old - पढ़ोl(ce->समयr.base + TIMER_CNTVAL_LO_REG(1))) < TIMER_SYNC_TICKS)
		cpu_relax();
पूर्ण

अटल व्योम sun5i_clkevt_समय_stop(काष्ठा sun5i_समयr_clkevt *ce, u8 समयr)
अणु
	u32 val = पढ़ोl(ce->समयr.base + TIMER_CTL_REG(समयr));
	ग_लिखोl(val & ~TIMER_CTL_ENABLE, ce->समयr.base + TIMER_CTL_REG(समयr));

	sun5i_clkevt_sync(ce);
पूर्ण

अटल व्योम sun5i_clkevt_समय_setup(काष्ठा sun5i_समयr_clkevt *ce, u8 समयr, u32 delay)
अणु
	ग_लिखोl(delay, ce->समयr.base + TIMER_INTVAL_LO_REG(समयr));
पूर्ण

अटल व्योम sun5i_clkevt_समय_start(काष्ठा sun5i_समयr_clkevt *ce, u8 समयr, bool periodic)
अणु
	u32 val = पढ़ोl(ce->समयr.base + TIMER_CTL_REG(समयr));

	अगर (periodic)
		val &= ~TIMER_CTL_ONESHOT;
	अन्यथा
		val |= TIMER_CTL_ONESHOT;

	ग_लिखोl(val | TIMER_CTL_ENABLE | TIMER_CTL_RELOAD,
	       ce->समयr.base + TIMER_CTL_REG(समयr));
पूर्ण

अटल पूर्णांक sun5i_clkevt_shutकरोwn(काष्ठा घड़ी_event_device *clkevt)
अणु
	काष्ठा sun5i_समयr_clkevt *ce = to_sun5i_समयr_clkevt(clkevt);

	sun5i_clkevt_समय_stop(ce, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक sun5i_clkevt_set_oneshot(काष्ठा घड़ी_event_device *clkevt)
अणु
	काष्ठा sun5i_समयr_clkevt *ce = to_sun5i_समयr_clkevt(clkevt);

	sun5i_clkevt_समय_stop(ce, 0);
	sun5i_clkevt_समय_start(ce, 0, false);
	वापस 0;
पूर्ण

अटल पूर्णांक sun5i_clkevt_set_periodic(काष्ठा घड़ी_event_device *clkevt)
अणु
	काष्ठा sun5i_समयr_clkevt *ce = to_sun5i_समयr_clkevt(clkevt);

	sun5i_clkevt_समय_stop(ce, 0);
	sun5i_clkevt_समय_setup(ce, 0, ce->समयr.ticks_per_jअगरfy);
	sun5i_clkevt_समय_start(ce, 0, true);
	वापस 0;
पूर्ण

अटल पूर्णांक sun5i_clkevt_next_event(अचिन्हित दीर्घ evt,
				   काष्ठा घड़ी_event_device *clkevt)
अणु
	काष्ठा sun5i_समयr_clkevt *ce = to_sun5i_समयr_clkevt(clkevt);

	sun5i_clkevt_समय_stop(ce, 0);
	sun5i_clkevt_समय_setup(ce, 0, evt - TIMER_SYNC_TICKS);
	sun5i_clkevt_समय_start(ce, 0, false);

	वापस 0;
पूर्ण

अटल irqवापस_t sun5i_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sun5i_समयr_clkevt *ce = (काष्ठा sun5i_समयr_clkevt *)dev_id;

	ग_लिखोl(0x1, ce->समयr.base + TIMER_IRQ_ST_REG);
	ce->clkevt.event_handler(&ce->clkevt);

	वापस IRQ_HANDLED;
पूर्ण

अटल u64 sun5i_clksrc_पढ़ो(काष्ठा घड़ीsource *clksrc)
अणु
	काष्ठा sun5i_समयr_clksrc *cs = to_sun5i_समयr_clksrc(clksrc);

	वापस ~पढ़ोl(cs->समयr.base + TIMER_CNTVAL_LO_REG(1));
पूर्ण

अटल पूर्णांक sun5i_rate_cb_clksrc(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *ndata = data;
	काष्ठा sun5i_समयr *समयr = to_sun5i_समयr(nb);
	काष्ठा sun5i_समयr_clksrc *cs = container_of(समयr, काष्ठा sun5i_समयr_clksrc, समयr);

	चयन (event) अणु
	हाल PRE_RATE_CHANGE:
		घड़ीsource_unरेजिस्टर(&cs->clksrc);
		अवरोध;

	हाल POST_RATE_CHANGE:
		घड़ीsource_रेजिस्टर_hz(&cs->clksrc, ndata->new_rate);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक __init sun5i_setup_घड़ीsource(काष्ठा device_node *node,
					  व्योम __iomem *base,
					  काष्ठा clk *clk, पूर्णांक irq)
अणु
	काष्ठा sun5i_समयr_clksrc *cs;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	cs = kzalloc(माप(*cs), GFP_KERNEL);
	अगर (!cs)
		वापस -ENOMEM;

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		pr_err("Couldn't enable parent clock\n");
		जाओ err_मुक्त;
	पूर्ण

	rate = clk_get_rate(clk);
	अगर (!rate) अणु
		pr_err("Couldn't get parent clock rate\n");
		ret = -EINVAL;
		जाओ err_disable_clk;
	पूर्ण

	cs->समयr.base = base;
	cs->समयr.clk = clk;
	cs->समयr.clk_rate_cb.notअगरier_call = sun5i_rate_cb_clksrc;
	cs->समयr.clk_rate_cb.next = शून्य;

	ret = clk_notअगरier_रेजिस्टर(clk, &cs->समयr.clk_rate_cb);
	अगर (ret) अणु
		pr_err("Unable to register clock notifier.\n");
		जाओ err_disable_clk;
	पूर्ण

	ग_लिखोl(~0, base + TIMER_INTVAL_LO_REG(1));
	ग_लिखोl(TIMER_CTL_ENABLE | TIMER_CTL_RELOAD,
	       base + TIMER_CTL_REG(1));

	cs->clksrc.name = node->name;
	cs->clksrc.rating = 340;
	cs->clksrc.पढ़ो = sun5i_clksrc_पढ़ो;
	cs->clksrc.mask = CLOCKSOURCE_MASK(32);
	cs->clksrc.flags = CLOCK_SOURCE_IS_CONTINUOUS;

	ret = घड़ीsource_रेजिस्टर_hz(&cs->clksrc, rate);
	अगर (ret) अणु
		pr_err("Couldn't register clock source.\n");
		जाओ err_हटाओ_notअगरier;
	पूर्ण

	वापस 0;

err_हटाओ_notअगरier:
	clk_notअगरier_unरेजिस्टर(clk, &cs->समयr.clk_rate_cb);
err_disable_clk:
	clk_disable_unprepare(clk);
err_मुक्त:
	kमुक्त(cs);
	वापस ret;
पूर्ण

अटल पूर्णांक sun5i_rate_cb_clkevt(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *ndata = data;
	काष्ठा sun5i_समयr *समयr = to_sun5i_समयr(nb);
	काष्ठा sun5i_समयr_clkevt *ce = container_of(समयr, काष्ठा sun5i_समयr_clkevt, समयr);

	अगर (event == POST_RATE_CHANGE) अणु
		घड़ीevents_update_freq(&ce->clkevt, ndata->new_rate);
		ce->समयr.ticks_per_jअगरfy = DIV_ROUND_UP(ndata->new_rate, HZ);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक __init sun5i_setup_घड़ीevent(काष्ठा device_node *node, व्योम __iomem *base,
					 काष्ठा clk *clk, पूर्णांक irq)
अणु
	काष्ठा sun5i_समयr_clkevt *ce;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;
	u32 val;

	ce = kzalloc(माप(*ce), GFP_KERNEL);
	अगर (!ce)
		वापस -ENOMEM;

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		pr_err("Couldn't enable parent clock\n");
		जाओ err_मुक्त;
	पूर्ण

	rate = clk_get_rate(clk);
	अगर (!rate) अणु
		pr_err("Couldn't get parent clock rate\n");
		ret = -EINVAL;
		जाओ err_disable_clk;
	पूर्ण

	ce->समयr.base = base;
	ce->समयr.ticks_per_jअगरfy = DIV_ROUND_UP(rate, HZ);
	ce->समयr.clk = clk;
	ce->समयr.clk_rate_cb.notअगरier_call = sun5i_rate_cb_clkevt;
	ce->समयr.clk_rate_cb.next = शून्य;

	ret = clk_notअगरier_रेजिस्टर(clk, &ce->समयr.clk_rate_cb);
	अगर (ret) अणु
		pr_err("Unable to register clock notifier.\n");
		जाओ err_disable_clk;
	पूर्ण

	ce->clkevt.name = node->name;
	ce->clkevt.features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT;
	ce->clkevt.set_next_event = sun5i_clkevt_next_event;
	ce->clkevt.set_state_shutकरोwn = sun5i_clkevt_shutकरोwn;
	ce->clkevt.set_state_periodic = sun5i_clkevt_set_periodic;
	ce->clkevt.set_state_oneshot = sun5i_clkevt_set_oneshot;
	ce->clkevt.tick_resume = sun5i_clkevt_shutकरोwn;
	ce->clkevt.rating = 340;
	ce->clkevt.irq = irq;
	ce->clkevt.cpumask = cpu_possible_mask;

	/* Enable समयr0 पूर्णांकerrupt */
	val = पढ़ोl(base + TIMER_IRQ_EN_REG);
	ग_लिखोl(val | TIMER_IRQ_EN(0), base + TIMER_IRQ_EN_REG);

	घड़ीevents_config_and_रेजिस्टर(&ce->clkevt, rate,
					TIMER_SYNC_TICKS, 0xffffffff);

	ret = request_irq(irq, sun5i_समयr_पूर्णांकerrupt, IRQF_TIMER | IRQF_IRQPOLL,
			  "sun5i_timer0", ce);
	अगर (ret) अणु
		pr_err("Unable to register interrupt\n");
		जाओ err_हटाओ_notअगरier;
	पूर्ण

	वापस 0;

err_हटाओ_notअगरier:
	clk_notअगरier_unरेजिस्टर(clk, &ce->समयr.clk_rate_cb);
err_disable_clk:
	clk_disable_unprepare(clk);
err_मुक्त:
	kमुक्त(ce);
	वापस ret;
पूर्ण

अटल पूर्णांक __init sun5i_समयr_init(काष्ठा device_node *node)
अणु
	काष्ठा reset_control *rstc;
	व्योम __iomem *समयr_base;
	काष्ठा clk *clk;
	पूर्णांक irq, ret;

	समयr_base = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(समयr_base)) अणु
		pr_err("Can't map registers\n");
		वापस PTR_ERR(समयr_base);
	पूर्ण

	irq = irq_of_parse_and_map(node, 0);
	अगर (irq <= 0) अणु
		pr_err("Can't parse IRQ\n");
		वापस -EINVAL;
	पूर्ण

	clk = of_clk_get(node, 0);
	अगर (IS_ERR(clk)) अणु
		pr_err("Can't get timer clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	rstc = of_reset_control_get(node, शून्य);
	अगर (!IS_ERR(rstc))
		reset_control_deनिश्चित(rstc);

	ret = sun5i_setup_घड़ीsource(node, समयr_base, clk, irq);
	अगर (ret)
		वापस ret;

	वापस sun5i_setup_घड़ीevent(node, समयr_base, clk, irq);
पूर्ण
TIMER_OF_DECLARE(sun5i_a13, "allwinner,sun5i-a13-hstimer",
			   sun5i_समयr_init);
TIMER_OF_DECLARE(sun7i_a20, "allwinner,sun7i-a20-hstimer",
			   sun5i_समयr_init);
