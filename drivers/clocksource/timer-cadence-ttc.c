<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file contains driver क्रम the Cadence Triple Timer Counter Rev 06
 *
 *  Copyright (C) 2011-2013 Xilinx
 *
 * based on arch/mips/kernel/समय.c समयr driver
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>

/*
 * This driver configures the 2 16/32-bit count-up समयrs as follows:
 *
 * T1: Timer 1, घड़ीsource क्रम generic समयkeeping
 * T2: Timer 2, घड़ीevent source क्रम hrसमयrs
 * T3: Timer 3, <unused>
 *
 * The input frequency to the समयr module क्रम emulation is 2.5MHz which is
 * common to all the समयr channels (T1, T2, and T3). With a pre-scaler of 32,
 * the समयrs are घड़ीed at 78.125KHz (12.8 us resolution).

 * The input frequency to the समयr module in silicon is configurable and
 * obtained from device tree. The pre-scaler of 32 is used.
 */

/*
 * Timer Register Offset Definitions of Timer 1, Increment base address by 4
 * and use same offsets क्रम Timer 2
 */
#घोषणा TTC_CLK_CNTRL_OFFSET		0x00 /* Clock Control Reg, RW */
#घोषणा TTC_CNT_CNTRL_OFFSET		0x0C /* Counter Control Reg, RW */
#घोषणा TTC_COUNT_VAL_OFFSET		0x18 /* Counter Value Reg, RO */
#घोषणा TTC_INTR_VAL_OFFSET		0x24 /* Interval Count Reg, RW */
#घोषणा TTC_ISR_OFFSET		0x54 /* Interrupt Status Reg, RO */
#घोषणा TTC_IER_OFFSET		0x60 /* Interrupt Enable Reg, RW */

#घोषणा TTC_CNT_CNTRL_DISABLE_MASK	0x1

#घोषणा TTC_CLK_CNTRL_CSRC_MASK		(1 << 5)	/* घड़ी source */
#घोषणा TTC_CLK_CNTRL_PSV_MASK		0x1e
#घोषणा TTC_CLK_CNTRL_PSV_SHIFT		1

/*
 * Setup the समयrs to use pre-scaling, using a fixed value क्रम now that will
 * work across most input frequency, but it may need to be more dynamic
 */
#घोषणा PRESCALE_EXPONENT	11	/* 2 ^ PRESCALE_EXPONENT = PRESCALE */
#घोषणा PRESCALE		2048	/* The exponent must match this */
#घोषणा CLK_CNTRL_PRESCALE	((PRESCALE_EXPONENT - 1) << 1)
#घोषणा CLK_CNTRL_PRESCALE_EN	1
#घोषणा CNT_CNTRL_RESET		(1 << 4)

#घोषणा MAX_F_ERR 50

/**
 * काष्ठा ttc_समयr - This definition defines local समयr काष्ठाure
 *
 * @base_addr:	Base address of समयr
 * @freq:	Timer input घड़ी frequency
 * @clk:	Associated घड़ी source
 * @clk_rate_change_nb	Notअगरier block क्रम घड़ी rate changes
 */
काष्ठा ttc_समयr अणु
	व्योम __iomem *base_addr;
	अचिन्हित दीर्घ freq;
	काष्ठा clk *clk;
	काष्ठा notअगरier_block clk_rate_change_nb;
पूर्ण;

#घोषणा to_ttc_समयr(x) \
		container_of(x, काष्ठा ttc_समयr, clk_rate_change_nb)

काष्ठा ttc_समयr_घड़ीsource अणु
	u32			scale_clk_ctrl_reg_old;
	u32			scale_clk_ctrl_reg_new;
	काष्ठा ttc_समयr	ttc;
	काष्ठा घड़ीsource	cs;
पूर्ण;

#घोषणा to_ttc_समयr_clksrc(x) \
		container_of(x, काष्ठा ttc_समयr_घड़ीsource, cs)

काष्ठा ttc_समयr_घड़ीevent अणु
	काष्ठा ttc_समयr		ttc;
	काष्ठा घड़ी_event_device	ce;
पूर्ण;

#घोषणा to_ttc_समयr_clkevent(x) \
		container_of(x, काष्ठा ttc_समयr_घड़ीevent, ce)

अटल व्योम __iomem *ttc_sched_घड़ी_val_reg;

/**
 * ttc_set_पूर्णांकerval - Set the समयr पूर्णांकerval value
 *
 * @समयr:	Poपूर्णांकer to the समयr instance
 * @cycles:	Timer पूर्णांकerval ticks
 **/
अटल व्योम ttc_set_पूर्णांकerval(काष्ठा ttc_समयr *समयr,
					अचिन्हित दीर्घ cycles)
अणु
	u32 ctrl_reg;

	/* Disable the counter, set the counter value  and re-enable counter */
	ctrl_reg = पढ़ोl_relaxed(समयr->base_addr + TTC_CNT_CNTRL_OFFSET);
	ctrl_reg |= TTC_CNT_CNTRL_DISABLE_MASK;
	ग_लिखोl_relaxed(ctrl_reg, समयr->base_addr + TTC_CNT_CNTRL_OFFSET);

	ग_लिखोl_relaxed(cycles, समयr->base_addr + TTC_INTR_VAL_OFFSET);

	/*
	 * Reset the counter (0x10) so that it starts from 0, one-shot
	 * mode makes this needed क्रम timing to be right.
	 */
	ctrl_reg |= CNT_CNTRL_RESET;
	ctrl_reg &= ~TTC_CNT_CNTRL_DISABLE_MASK;
	ग_लिखोl_relaxed(ctrl_reg, समयr->base_addr + TTC_CNT_CNTRL_OFFSET);
पूर्ण

/**
 * ttc_घड़ी_event_पूर्णांकerrupt - Clock event समयr पूर्णांकerrupt handler
 *
 * @irq:	IRQ number of the Timer
 * @dev_id:	व्योम poपूर्णांकer to the ttc_समयr instance
 *
 * वापसs: Always IRQ_HANDLED - success
 **/
अटल irqवापस_t ttc_घड़ी_event_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ttc_समयr_घड़ीevent *ttce = dev_id;
	काष्ठा ttc_समयr *समयr = &ttce->ttc;

	/* Acknowledge the पूर्णांकerrupt and call event handler */
	पढ़ोl_relaxed(समयr->base_addr + TTC_ISR_OFFSET);

	ttce->ce.event_handler(&ttce->ce);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * __ttc_घड़ीsource_पढ़ो - Reads the समयr counter रेजिस्टर
 *
 * वापसs: Current समयr counter रेजिस्टर value
 **/
अटल u64 __ttc_घड़ीsource_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा ttc_समयr *समयr = &to_ttc_समयr_clksrc(cs)->ttc;

	वापस (u64)पढ़ोl_relaxed(समयr->base_addr +
				TTC_COUNT_VAL_OFFSET);
पूर्ण

अटल u64 notrace ttc_sched_घड़ी_पढ़ो(व्योम)
अणु
	वापस पढ़ोl_relaxed(ttc_sched_घड़ी_val_reg);
पूर्ण

/**
 * ttc_set_next_event - Sets the समय पूर्णांकerval क्रम next event
 *
 * @cycles:	Timer पूर्णांकerval ticks
 * @evt:	Address of घड़ी event instance
 *
 * वापसs: Always 0 - success
 **/
अटल पूर्णांक ttc_set_next_event(अचिन्हित दीर्घ cycles,
					काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ttc_समयr_घड़ीevent *ttce = to_ttc_समयr_clkevent(evt);
	काष्ठा ttc_समयr *समयr = &ttce->ttc;

	ttc_set_पूर्णांकerval(समयr, cycles);
	वापस 0;
पूर्ण

/**
 * ttc_set_अणुshutकरोwn|oneshot|periodicपूर्ण - Sets the state of समयr
 *
 * @evt:	Address of घड़ी event instance
 **/
अटल पूर्णांक ttc_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ttc_समयr_घड़ीevent *ttce = to_ttc_समयr_clkevent(evt);
	काष्ठा ttc_समयr *समयr = &ttce->ttc;
	u32 ctrl_reg;

	ctrl_reg = पढ़ोl_relaxed(समयr->base_addr + TTC_CNT_CNTRL_OFFSET);
	ctrl_reg |= TTC_CNT_CNTRL_DISABLE_MASK;
	ग_लिखोl_relaxed(ctrl_reg, समयr->base_addr + TTC_CNT_CNTRL_OFFSET);
	वापस 0;
पूर्ण

अटल पूर्णांक ttc_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ttc_समयr_घड़ीevent *ttce = to_ttc_समयr_clkevent(evt);
	काष्ठा ttc_समयr *समयr = &ttce->ttc;

	ttc_set_पूर्णांकerval(समयr,
			 DIV_ROUND_CLOSEST(ttce->ttc.freq, PRESCALE * HZ));
	वापस 0;
पूर्ण

अटल पूर्णांक ttc_resume(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ttc_समयr_घड़ीevent *ttce = to_ttc_समयr_clkevent(evt);
	काष्ठा ttc_समयr *समयr = &ttce->ttc;
	u32 ctrl_reg;

	ctrl_reg = पढ़ोl_relaxed(समयr->base_addr + TTC_CNT_CNTRL_OFFSET);
	ctrl_reg &= ~TTC_CNT_CNTRL_DISABLE_MASK;
	ग_लिखोl_relaxed(ctrl_reg, समयr->base_addr + TTC_CNT_CNTRL_OFFSET);
	वापस 0;
पूर्ण

अटल पूर्णांक ttc_rate_change_घड़ीsource_cb(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *ndata = data;
	काष्ठा ttc_समयr *ttc = to_ttc_समयr(nb);
	काष्ठा ttc_समयr_घड़ीsource *ttccs = container_of(ttc,
			काष्ठा ttc_समयr_घड़ीsource, ttc);

	चयन (event) अणु
	हाल PRE_RATE_CHANGE:
	अणु
		u32 psv;
		अचिन्हित दीर्घ factor, rate_low, rate_high;

		अगर (ndata->new_rate > ndata->old_rate) अणु
			factor = DIV_ROUND_CLOSEST(ndata->new_rate,
					ndata->old_rate);
			rate_low = ndata->old_rate;
			rate_high = ndata->new_rate;
		पूर्ण अन्यथा अणु
			factor = DIV_ROUND_CLOSEST(ndata->old_rate,
					ndata->new_rate);
			rate_low = ndata->new_rate;
			rate_high = ndata->old_rate;
		पूर्ण

		अगर (!is_घातer_of_2(factor))
				वापस NOTIFY_BAD;

		अगर (असल(rate_high - (factor * rate_low)) > MAX_F_ERR)
			वापस NOTIFY_BAD;

		factor = __ilog2_u32(factor);

		/*
		 * store समयr घड़ी ctrl रेजिस्टर so we can restore it in हाल
		 * of an पात.
		 */
		ttccs->scale_clk_ctrl_reg_old =
			पढ़ोl_relaxed(ttccs->ttc.base_addr +
			TTC_CLK_CNTRL_OFFSET);

		psv = (ttccs->scale_clk_ctrl_reg_old &
				TTC_CLK_CNTRL_PSV_MASK) >>
				TTC_CLK_CNTRL_PSV_SHIFT;
		अगर (ndata->new_rate < ndata->old_rate)
			psv -= factor;
		अन्यथा
			psv += factor;

		/* prescaler within legal range? */
		अगर (psv & ~(TTC_CLK_CNTRL_PSV_MASK >> TTC_CLK_CNTRL_PSV_SHIFT))
			वापस NOTIFY_BAD;

		ttccs->scale_clk_ctrl_reg_new = ttccs->scale_clk_ctrl_reg_old &
			~TTC_CLK_CNTRL_PSV_MASK;
		ttccs->scale_clk_ctrl_reg_new |= psv << TTC_CLK_CNTRL_PSV_SHIFT;


		/* scale करोwn: adjust भागider in post-change notअगरication */
		अगर (ndata->new_rate < ndata->old_rate)
			वापस NOTIFY_DONE;

		/* scale up: adjust भागider now - beक्रमe frequency change */
		ग_लिखोl_relaxed(ttccs->scale_clk_ctrl_reg_new,
			       ttccs->ttc.base_addr + TTC_CLK_CNTRL_OFFSET);
		अवरोध;
	पूर्ण
	हाल POST_RATE_CHANGE:
		/* scale up: pre-change notअगरication did the adjusपंचांगent */
		अगर (ndata->new_rate > ndata->old_rate)
			वापस NOTIFY_OK;

		/* scale करोwn: adjust भागider now - after frequency change */
		ग_लिखोl_relaxed(ttccs->scale_clk_ctrl_reg_new,
			       ttccs->ttc.base_addr + TTC_CLK_CNTRL_OFFSET);
		अवरोध;

	हाल ABORT_RATE_CHANGE:
		/* we have to unकरो the adjusपंचांगent in हाल we scale up */
		अगर (ndata->new_rate < ndata->old_rate)
			वापस NOTIFY_OK;

		/* restore original रेजिस्टर value */
		ग_लिखोl_relaxed(ttccs->scale_clk_ctrl_reg_old,
			       ttccs->ttc.base_addr + TTC_CLK_CNTRL_OFFSET);
		fallthrough;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक __init ttc_setup_घड़ीsource(काष्ठा clk *clk, व्योम __iomem *base,
					 u32 समयr_width)
अणु
	काष्ठा ttc_समयr_घड़ीsource *ttccs;
	पूर्णांक err;

	ttccs = kzalloc(माप(*ttccs), GFP_KERNEL);
	अगर (!ttccs)
		वापस -ENOMEM;

	ttccs->ttc.clk = clk;

	err = clk_prepare_enable(ttccs->ttc.clk);
	अगर (err) अणु
		kमुक्त(ttccs);
		वापस err;
	पूर्ण

	ttccs->ttc.freq = clk_get_rate(ttccs->ttc.clk);

	ttccs->ttc.clk_rate_change_nb.notअगरier_call =
		ttc_rate_change_घड़ीsource_cb;
	ttccs->ttc.clk_rate_change_nb.next = शून्य;

	err = clk_notअगरier_रेजिस्टर(ttccs->ttc.clk,
				    &ttccs->ttc.clk_rate_change_nb);
	अगर (err)
		pr_warn("Unable to register clock notifier.\n");

	ttccs->ttc.base_addr = base;
	ttccs->cs.name = "ttc_clocksource";
	ttccs->cs.rating = 200;
	ttccs->cs.पढ़ो = __ttc_घड़ीsource_पढ़ो;
	ttccs->cs.mask = CLOCKSOURCE_MASK(समयr_width);
	ttccs->cs.flags = CLOCK_SOURCE_IS_CONTINUOUS;

	/*
	 * Setup the घड़ी source counter to be an incrementing counter
	 * with no पूर्णांकerrupt and it rolls over at 0xFFFF. Pre-scale
	 * it by 32 also. Let it start running now.
	 */
	ग_लिखोl_relaxed(0x0,  ttccs->ttc.base_addr + TTC_IER_OFFSET);
	ग_लिखोl_relaxed(CLK_CNTRL_PRESCALE | CLK_CNTRL_PRESCALE_EN,
		     ttccs->ttc.base_addr + TTC_CLK_CNTRL_OFFSET);
	ग_लिखोl_relaxed(CNT_CNTRL_RESET,
		     ttccs->ttc.base_addr + TTC_CNT_CNTRL_OFFSET);

	err = घड़ीsource_रेजिस्टर_hz(&ttccs->cs, ttccs->ttc.freq / PRESCALE);
	अगर (err) अणु
		kमुक्त(ttccs);
		वापस err;
	पूर्ण

	ttc_sched_घड़ी_val_reg = base + TTC_COUNT_VAL_OFFSET;
	sched_घड़ी_रेजिस्टर(ttc_sched_घड़ी_पढ़ो, समयr_width,
			     ttccs->ttc.freq / PRESCALE);

	वापस 0;
पूर्ण

अटल पूर्णांक ttc_rate_change_घड़ीevent_cb(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *ndata = data;
	काष्ठा ttc_समयr *ttc = to_ttc_समयr(nb);
	काष्ठा ttc_समयr_घड़ीevent *ttcce = container_of(ttc,
			काष्ठा ttc_समयr_घड़ीevent, ttc);

	चयन (event) अणु
	हाल POST_RATE_CHANGE:
		/* update cached frequency */
		ttc->freq = ndata->new_rate;

		घड़ीevents_update_freq(&ttcce->ce, ndata->new_rate / PRESCALE);

		fallthrough;
	हाल PRE_RATE_CHANGE:
	हाल ABORT_RATE_CHANGE:
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

अटल पूर्णांक __init ttc_setup_घड़ीevent(काष्ठा clk *clk,
				       व्योम __iomem *base, u32 irq)
अणु
	काष्ठा ttc_समयr_घड़ीevent *ttcce;
	पूर्णांक err;

	ttcce = kzalloc(माप(*ttcce), GFP_KERNEL);
	अगर (!ttcce)
		वापस -ENOMEM;

	ttcce->ttc.clk = clk;

	err = clk_prepare_enable(ttcce->ttc.clk);
	अगर (err)
		जाओ out_kमुक्त;

	ttcce->ttc.clk_rate_change_nb.notअगरier_call =
		ttc_rate_change_घड़ीevent_cb;
	ttcce->ttc.clk_rate_change_nb.next = शून्य;

	err = clk_notअगरier_रेजिस्टर(ttcce->ttc.clk,
				    &ttcce->ttc.clk_rate_change_nb);
	अगर (err) अणु
		pr_warn("Unable to register clock notifier.\n");
		जाओ out_kमुक्त;
	पूर्ण

	ttcce->ttc.freq = clk_get_rate(ttcce->ttc.clk);

	ttcce->ttc.base_addr = base;
	ttcce->ce.name = "ttc_clockevent";
	ttcce->ce.features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT;
	ttcce->ce.set_next_event = ttc_set_next_event;
	ttcce->ce.set_state_shutकरोwn = ttc_shutकरोwn;
	ttcce->ce.set_state_periodic = ttc_set_periodic;
	ttcce->ce.set_state_oneshot = ttc_shutकरोwn;
	ttcce->ce.tick_resume = ttc_resume;
	ttcce->ce.rating = 200;
	ttcce->ce.irq = irq;
	ttcce->ce.cpumask = cpu_possible_mask;

	/*
	 * Setup the घड़ी event समयr to be an पूर्णांकerval समयr which
	 * is prescaled by 32 using the पूर्णांकerval पूर्णांकerrupt. Leave it
	 * disabled क्रम now.
	 */
	ग_लिखोl_relaxed(0x23, ttcce->ttc.base_addr + TTC_CNT_CNTRL_OFFSET);
	ग_लिखोl_relaxed(CLK_CNTRL_PRESCALE | CLK_CNTRL_PRESCALE_EN,
		     ttcce->ttc.base_addr + TTC_CLK_CNTRL_OFFSET);
	ग_लिखोl_relaxed(0x1,  ttcce->ttc.base_addr + TTC_IER_OFFSET);

	err = request_irq(irq, ttc_घड़ी_event_पूर्णांकerrupt,
			  IRQF_TIMER, ttcce->ce.name, ttcce);
	अगर (err)
		जाओ out_kमुक्त;

	घड़ीevents_config_and_रेजिस्टर(&ttcce->ce,
			ttcce->ttc.freq / PRESCALE, 1, 0xfffe);

	वापस 0;

out_kमुक्त:
	kमुक्त(ttcce);
	वापस err;
पूर्ण

अटल पूर्णांक __init ttc_समयr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक irq;
	व्योम __iomem *समयr_baseaddr;
	काष्ठा clk *clk_cs, *clk_ce;
	अटल पूर्णांक initialized;
	पूर्णांक clksel, ret;
	u32 समयr_width = 16;
	काष्ठा device_node *समयr = pdev->dev.of_node;

	अगर (initialized)
		वापस 0;

	initialized = 1;

	/*
	 * Get the 1st Triple Timer Counter (TTC) block from the device tree
	 * and use it. Note that the event समयr uses the पूर्णांकerrupt and it's the
	 * 2nd TTC hence the irq_of_parse_and_map(,1)
	 */
	समयr_baseaddr = of_iomap(समयr, 0);
	अगर (!समयr_baseaddr) अणु
		pr_err("ERROR: invalid timer base address\n");
		वापस -ENXIO;
	पूर्ण

	irq = irq_of_parse_and_map(समयr, 1);
	अगर (irq <= 0) अणु
		pr_err("ERROR: invalid interrupt number\n");
		वापस -EINVAL;
	पूर्ण

	of_property_पढ़ो_u32(समयr, "timer-width", &समयr_width);

	clksel = पढ़ोl_relaxed(समयr_baseaddr + TTC_CLK_CNTRL_OFFSET);
	clksel = !!(clksel & TTC_CLK_CNTRL_CSRC_MASK);
	clk_cs = of_clk_get(समयr, clksel);
	अगर (IS_ERR(clk_cs)) अणु
		pr_err("ERROR: timer input clock not found\n");
		वापस PTR_ERR(clk_cs);
	पूर्ण

	clksel = पढ़ोl_relaxed(समयr_baseaddr + 4 + TTC_CLK_CNTRL_OFFSET);
	clksel = !!(clksel & TTC_CLK_CNTRL_CSRC_MASK);
	clk_ce = of_clk_get(समयr, clksel);
	अगर (IS_ERR(clk_ce)) अणु
		pr_err("ERROR: timer input clock not found\n");
		वापस PTR_ERR(clk_ce);
	पूर्ण

	ret = ttc_setup_घड़ीsource(clk_cs, समयr_baseaddr, समयr_width);
	अगर (ret)
		वापस ret;

	ret = ttc_setup_घड़ीevent(clk_ce, समयr_baseaddr + 4, irq);
	अगर (ret)
		वापस ret;

	pr_info("%pOFn #0 at %p, irq=%d\n", समयr, समयr_baseaddr, irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ttc_समयr_of_match[] = अणु
	अणु.compatible = "cdns,ttc"पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, ttc_समयr_of_match);

अटल काष्ठा platक्रमm_driver ttc_समयr_driver = अणु
	.driver = अणु
		.name	= "cdns_ttc_timer",
		.of_match_table = ttc_समयr_of_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver_probe(ttc_समयr_driver, ttc_समयr_probe);
