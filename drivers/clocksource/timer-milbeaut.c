<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Socionext Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश "timer-of.h"

#घोषणा MLB_TMR_TMCSR_OFS	0x0
#घोषणा MLB_TMR_TMR_OFS		0x4
#घोषणा MLB_TMR_TMRLR1_OFS	0x8
#घोषणा MLB_TMR_TMRLR2_OFS	0xc
#घोषणा MLB_TMR_REGSZPCH	0x10

#घोषणा MLB_TMR_TMCSR_OUTL	BIT(5)
#घोषणा MLB_TMR_TMCSR_RELD	BIT(4)
#घोषणा MLB_TMR_TMCSR_INTE	BIT(3)
#घोषणा MLB_TMR_TMCSR_UF	BIT(2)
#घोषणा MLB_TMR_TMCSR_CNTE	BIT(1)
#घोषणा MLB_TMR_TMCSR_TRG	BIT(0)

#घोषणा MLB_TMR_TMCSR_CSL_DIV2	0
#घोषणा MLB_TMR_DIV_CNT		2

#घोषणा MLB_TMR_SRC_CH		1
#घोषणा MLB_TMR_EVT_CH		0

#घोषणा MLB_TMR_SRC_CH_OFS	(MLB_TMR_REGSZPCH * MLB_TMR_SRC_CH)
#घोषणा MLB_TMR_EVT_CH_OFS	(MLB_TMR_REGSZPCH * MLB_TMR_EVT_CH)

#घोषणा MLB_TMR_SRC_TMCSR_OFS	(MLB_TMR_SRC_CH_OFS + MLB_TMR_TMCSR_OFS)
#घोषणा MLB_TMR_SRC_TMR_OFS	(MLB_TMR_SRC_CH_OFS + MLB_TMR_TMR_OFS)
#घोषणा MLB_TMR_SRC_TMRLR1_OFS	(MLB_TMR_SRC_CH_OFS + MLB_TMR_TMRLR1_OFS)
#घोषणा MLB_TMR_SRC_TMRLR2_OFS	(MLB_TMR_SRC_CH_OFS + MLB_TMR_TMRLR2_OFS)

#घोषणा MLB_TMR_EVT_TMCSR_OFS	(MLB_TMR_EVT_CH_OFS + MLB_TMR_TMCSR_OFS)
#घोषणा MLB_TMR_EVT_TMR_OFS	(MLB_TMR_EVT_CH_OFS + MLB_TMR_TMR_OFS)
#घोषणा MLB_TMR_EVT_TMRLR1_OFS	(MLB_TMR_EVT_CH_OFS + MLB_TMR_TMRLR1_OFS)
#घोषणा MLB_TMR_EVT_TMRLR2_OFS	(MLB_TMR_EVT_CH_OFS + MLB_TMR_TMRLR2_OFS)

#घोषणा MLB_TIMER_RATING	500
#घोषणा MLB_TIMER_ONESHOT	0
#घोषणा MLB_TIMER_PERIODIC	1

अटल irqवापस_t mlb_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *clk = dev_id;
	काष्ठा समयr_of *to = to_समयr_of(clk);
	u32 val;

	val = पढ़ोl_relaxed(समयr_of_base(to) + MLB_TMR_EVT_TMCSR_OFS);
	val &= ~MLB_TMR_TMCSR_UF;
	ग_लिखोl_relaxed(val, समयr_of_base(to) + MLB_TMR_EVT_TMCSR_OFS);

	clk->event_handler(clk);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mlb_evt_समयr_start(काष्ठा समयr_of *to, bool periodic)
अणु
	u32 val = MLB_TMR_TMCSR_CSL_DIV2;

	val |= MLB_TMR_TMCSR_CNTE | MLB_TMR_TMCSR_TRG | MLB_TMR_TMCSR_INTE;
	अगर (periodic)
		val |= MLB_TMR_TMCSR_RELD;
	ग_लिखोl_relaxed(val, समयr_of_base(to) + MLB_TMR_EVT_TMCSR_OFS);
पूर्ण

अटल व्योम mlb_evt_समयr_stop(काष्ठा समयr_of *to)
अणु
	u32 val = पढ़ोl_relaxed(समयr_of_base(to) + MLB_TMR_EVT_TMCSR_OFS);

	val &= ~MLB_TMR_TMCSR_CNTE;
	ग_लिखोl_relaxed(val, समयr_of_base(to) + MLB_TMR_EVT_TMCSR_OFS);
पूर्ण

अटल व्योम mlb_evt_समयr_रेजिस्टर_count(काष्ठा समयr_of *to, अचिन्हित दीर्घ cnt)
अणु
	ग_लिखोl_relaxed(cnt, समयr_of_base(to) + MLB_TMR_EVT_TMRLR1_OFS);
पूर्ण

अटल पूर्णांक mlb_set_state_periodic(काष्ठा घड़ी_event_device *clk)
अणु
	काष्ठा समयr_of *to = to_समयr_of(clk);

	mlb_evt_समयr_stop(to);
	mlb_evt_समयr_रेजिस्टर_count(to, to->of_clk.period);
	mlb_evt_समयr_start(to, MLB_TIMER_PERIODIC);
	वापस 0;
पूर्ण

अटल पूर्णांक mlb_set_state_oneshot(काष्ठा घड़ी_event_device *clk)
अणु
	काष्ठा समयr_of *to = to_समयr_of(clk);

	mlb_evt_समयr_stop(to);
	mlb_evt_समयr_start(to, MLB_TIMER_ONESHOT);
	वापस 0;
पूर्ण

अटल पूर्णांक mlb_set_state_shutकरोwn(काष्ठा घड़ी_event_device *clk)
अणु
	काष्ठा समयr_of *to = to_समयr_of(clk);

	mlb_evt_समयr_stop(to);
	वापस 0;
पूर्ण

अटल पूर्णांक mlb_clkevt_next_event(अचिन्हित दीर्घ event,
				   काष्ठा घड़ी_event_device *clk)
अणु
	काष्ठा समयr_of *to = to_समयr_of(clk);

	mlb_evt_समयr_stop(to);
	mlb_evt_समयr_रेजिस्टर_count(to, event);
	mlb_evt_समयr_start(to, MLB_TIMER_ONESHOT);
	वापस 0;
पूर्ण

अटल पूर्णांक mlb_config_घड़ी_source(काष्ठा समयr_of *to)
अणु
	u32 val = MLB_TMR_TMCSR_CSL_DIV2;

	ग_लिखोl_relaxed(val, समयr_of_base(to) + MLB_TMR_SRC_TMCSR_OFS);
	ग_लिखोl_relaxed(~0, समयr_of_base(to) + MLB_TMR_SRC_TMRLR1_OFS);
	ग_लिखोl_relaxed(~0, समयr_of_base(to) + MLB_TMR_SRC_TMRLR2_OFS);
	val |= MLB_TMR_TMCSR_RELD | MLB_TMR_TMCSR_CNTE | MLB_TMR_TMCSR_TRG;
	ग_लिखोl_relaxed(val, समयr_of_base(to) + MLB_TMR_SRC_TMCSR_OFS);
	वापस 0;
पूर्ण

अटल पूर्णांक mlb_config_घड़ी_event(काष्ठा समयr_of *to)
अणु
	ग_लिखोl_relaxed(0, समयr_of_base(to) + MLB_TMR_EVT_TMCSR_OFS);
	वापस 0;
पूर्ण

अटल काष्ठा समयr_of to = अणु
	.flags = TIMER_OF_IRQ | TIMER_OF_BASE | TIMER_OF_CLOCK,

	.clkevt = अणु
		.name = "mlb-clkevt",
		.rating = MLB_TIMER_RATING,
		.cpumask = cpu_possible_mask,
		.features = CLOCK_EVT_FEAT_DYNIRQ | CLOCK_EVT_FEAT_ONESHOT,
		.set_state_oneshot = mlb_set_state_oneshot,
		.set_state_periodic = mlb_set_state_periodic,
		.set_state_shutकरोwn = mlb_set_state_shutकरोwn,
		.set_next_event = mlb_clkevt_next_event,
	पूर्ण,

	.of_irq = अणु
		.flags = IRQF_TIMER | IRQF_IRQPOLL,
		.handler = mlb_समयr_पूर्णांकerrupt,
	पूर्ण,
पूर्ण;

अटल u64 notrace mlb_समयr_sched_पढ़ो(व्योम)
अणु
	वापस ~पढ़ोl_relaxed(समयr_of_base(&to) + MLB_TMR_SRC_TMR_OFS);
पूर्ण

अटल पूर्णांक __init mlb_समयr_init(काष्ठा device_node *node)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ rate;

	ret = समयr_of_init(node, &to);
	अगर (ret)
		वापस ret;

	rate = समयr_of_rate(&to) / MLB_TMR_DIV_CNT;
	mlb_config_घड़ी_source(&to);
	घड़ीsource_mmio_init(समयr_of_base(&to) + MLB_TMR_SRC_TMR_OFS,
		node->name, rate, MLB_TIMER_RATING, 32,
		घड़ीsource_mmio_पढ़ोl_करोwn);
	sched_घड़ी_रेजिस्टर(mlb_समयr_sched_पढ़ो, 32, rate);
	mlb_config_घड़ी_event(&to);
	घड़ीevents_config_and_रेजिस्टर(&to.clkevt, समयr_of_rate(&to), 15,
		0xffffffff);
	वापस 0;
पूर्ण
TIMER_OF_DECLARE(mlb_periसमयr, "socionext,milbeaut-timer",
		mlb_समयr_init);
