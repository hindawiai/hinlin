<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Maxime Coquelin 2015
 * Author:  Maxime Coquelin <mcoquelin.sपंचांग32@gmail.com>
 *
 * Inspired by समय-efm32.c from Uwe Kleine-Koenig
 */

#समावेश <linux/kernel.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/clk.h>
#समावेश <linux/reset.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/slab.h>

#समावेश "timer-of.h"

#घोषणा TIM_CR1		0x00
#घोषणा TIM_DIER	0x0c
#घोषणा TIM_SR		0x10
#घोषणा TIM_EGR		0x14
#घोषणा TIM_CNT		0x24
#घोषणा TIM_PSC		0x28
#घोषणा TIM_ARR		0x2c
#घोषणा TIM_CCR1	0x34

#घोषणा TIM_CR1_CEN	BIT(0)
#घोषणा TIM_CR1_UDIS	BIT(1)
#घोषणा TIM_CR1_OPM	BIT(3)
#घोषणा TIM_CR1_ARPE	BIT(7)

#घोषणा TIM_DIER_UIE	BIT(0)
#घोषणा TIM_DIER_CC1IE	BIT(1)

#घोषणा TIM_SR_UIF	BIT(0)

#घोषणा TIM_EGR_UG	BIT(0)

#घोषणा TIM_PSC_MAX	अच_लघु_उच्च
#घोषणा TIM_PSC_CLKRATE	10000

काष्ठा sपंचांग32_समयr_निजी अणु
	पूर्णांक bits;
पूर्ण;

/**
 * sपंचांग32_समयr_of_bits_set - set accessor helper
 * @to: a समयr_of काष्ठाure poपूर्णांकer
 * @bits: the number of bits (16 or 32)
 *
 * Accessor helper to set the number of bits in the समयr-of निजी
 * काष्ठाure.
 *
 */
अटल व्योम sपंचांग32_समयr_of_bits_set(काष्ठा समयr_of *to, पूर्णांक bits)
अणु
	काष्ठा sपंचांग32_समयr_निजी *pd = to->निजी_data;

	pd->bits = bits;
पूर्ण

/**
 * sपंचांग32_समयr_of_bits_get - get accessor helper
 * @to: a समयr_of काष्ठाure poपूर्णांकer
 *
 * Accessor helper to get the number of bits in the समयr-of निजी
 * काष्ठाure.
 *
 * Returns an पूर्णांकeger corresponding to the number of bits.
 */
अटल पूर्णांक sपंचांग32_समयr_of_bits_get(काष्ठा समयr_of *to)
अणु
	काष्ठा sपंचांग32_समयr_निजी *pd = to->निजी_data;

	वापस pd->bits;
पूर्ण

अटल व्योम __iomem *sपंचांग32_समयr_cnt __पढ़ो_mostly;

अटल u64 notrace sपंचांग32_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस पढ़ोl_relaxed(sपंचांग32_समयr_cnt);
पूर्ण

अटल काष्ठा delay_समयr sपंचांग32_समयr_delay;

अटल अचिन्हित दीर्घ sपंचांग32_पढ़ो_delay(व्योम)
अणु
	वापस पढ़ोl_relaxed(sपंचांग32_समयr_cnt);
पूर्ण

अटल व्योम sपंचांग32_घड़ी_event_disable(काष्ठा समयr_of *to)
अणु
	ग_लिखोl_relaxed(0, समयr_of_base(to) + TIM_DIER);
पूर्ण

/**
 * sपंचांग32_समयr_start - Start the counter without event
 * @to: a समयr_of काष्ठाure poपूर्णांकer
 *
 * Start the समयr in order to have the counter reset and start
 * incrementing but disable पूर्णांकerrupt event when there is a counter
 * overflow. By शेष, the counter direction is used as upcounter.
 */
अटल व्योम sपंचांग32_समयr_start(काष्ठा समयr_of *to)
अणु
	ग_लिखोl_relaxed(TIM_CR1_UDIS | TIM_CR1_CEN, समयr_of_base(to) + TIM_CR1);
पूर्ण

अटल पूर्णांक sपंचांग32_घड़ी_event_shutकरोwn(काष्ठा घड़ी_event_device *clkevt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(clkevt);

	sपंचांग32_घड़ी_event_disable(to);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_घड़ी_event_set_next_event(अचिन्हित दीर्घ evt,
					    काष्ठा घड़ी_event_device *clkevt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(clkevt);
	अचिन्हित दीर्घ now, next;

	next = पढ़ोl_relaxed(समयr_of_base(to) + TIM_CNT) + evt;
	ग_लिखोl_relaxed(next, समयr_of_base(to) + TIM_CCR1);
	now = पढ़ोl_relaxed(समयr_of_base(to) + TIM_CNT);

	अगर ((next - now) > evt)
		वापस -ETIME;

	ग_लिखोl_relaxed(TIM_DIER_CC1IE, समयr_of_base(to) + TIM_DIER);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_घड़ी_event_set_periodic(काष्ठा घड़ी_event_device *clkevt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(clkevt);

	sपंचांग32_समयr_start(to);

	वापस sपंचांग32_घड़ी_event_set_next_event(समयr_of_period(to), clkevt);
पूर्ण

अटल पूर्णांक sपंचांग32_घड़ी_event_set_oneshot(काष्ठा घड़ी_event_device *clkevt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(clkevt);

	sपंचांग32_समयr_start(to);

	वापस 0;
पूर्ण

अटल irqवापस_t sपंचांग32_घड़ी_event_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *clkevt = (काष्ठा घड़ी_event_device *)dev_id;
	काष्ठा समयr_of *to = to_समयr_of(clkevt);

	ग_लिखोl_relaxed(0, समयr_of_base(to) + TIM_SR);

	अगर (घड़ीevent_state_periodic(clkevt))
		sपंचांग32_घड़ी_event_set_periodic(clkevt);
	अन्यथा
		sपंचांग32_घड़ी_event_shutकरोwn(clkevt);

	clkevt->event_handler(clkevt);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * sपंचांग32_समयr_width - Sort out the समयr width (32/16)
 * @to: a poपूर्णांकer to a समयr-of काष्ठाure
 *
 * Write the 32-bit max value and पढ़ो/वापस the result. If the समयr
 * is 32 bits wide, the result will be अच_पूर्णांक_उच्च, otherwise it will
 * be truncated by the 16-bit रेजिस्टर to अच_लघु_उच्च.
 *
 */
अटल व्योम __init sपंचांग32_समयr_set_width(काष्ठा समयr_of *to)
अणु
	u32 width;

	ग_लिखोl_relaxed(अच_पूर्णांक_उच्च, समयr_of_base(to) + TIM_ARR);

	width = पढ़ोl_relaxed(समयr_of_base(to) + TIM_ARR);

	sपंचांग32_समयr_of_bits_set(to, width == अच_पूर्णांक_उच्च ? 32 : 16);
पूर्ण

/**
 * sपंचांग32_समयr_set_prescaler - Compute and set the prescaler रेजिस्टर
 * @to: a poपूर्णांकer to a समयr-of काष्ठाure
 *
 * Depending on the समयr width, compute the prescaler to always
 * target a 10MHz समयr rate क्रम 16 bits. 32-bit समयrs are
 * considered precise and दीर्घ enough to not use the prescaler.
 */
अटल व्योम __init sपंचांग32_समयr_set_prescaler(काष्ठा समयr_of *to)
अणु
	पूर्णांक prescaler = 1;

	अगर (sपंचांग32_समयr_of_bits_get(to) != 32) अणु
		prescaler = DIV_ROUND_CLOSEST(समयr_of_rate(to),
					      TIM_PSC_CLKRATE);
		/*
		 * The prescaler रेजिस्टर is an u16, the variable
		 * can't be greater than TIM_PSC_MAX, let's cap it in
		 * this हाल.
		 */
		prescaler = prescaler < TIM_PSC_MAX ? prescaler : TIM_PSC_MAX;
	पूर्ण

	ग_लिखोl_relaxed(prescaler - 1, समयr_of_base(to) + TIM_PSC);
	ग_लिखोl_relaxed(TIM_EGR_UG, समयr_of_base(to) + TIM_EGR);
	ग_लिखोl_relaxed(0, समयr_of_base(to) + TIM_SR);

	/* Adjust rate and period given the prescaler value */
	to->of_clk.rate = DIV_ROUND_CLOSEST(to->of_clk.rate, prescaler);
	to->of_clk.period = DIV_ROUND_UP(to->of_clk.rate, HZ);
पूर्ण

अटल पूर्णांक __init sपंचांग32_घड़ीsource_init(काष्ठा समयr_of *to)
अणु
        u32 bits = sपंचांग32_समयr_of_bits_get(to);
	स्थिर अक्षर *name = to->np->full_name;

	/*
	 * This driver allows to रेजिस्टर several समयrs and relies on
	 * the generic समय framework to select the right one.
	 * However, nothing allows to करो the same क्रम the
	 * sched_घड़ी. We are not पूर्णांकerested in a sched_घड़ी क्रम the
	 * 16-bit समयrs but only क्रम the 32-bit one, so अगर no 32-bit
	 * समयr is रेजिस्टरed yet, we select this 32-bit समयr as a
	 * sched_घड़ी.
	 */
	अगर (bits == 32 && !sपंचांग32_समयr_cnt) अणु

		/*
		 * Start immediately the counter as we will be using
		 * it right after.
		 */
		sपंचांग32_समयr_start(to);

		sपंचांग32_समयr_cnt = समयr_of_base(to) + TIM_CNT;
		sched_घड़ी_रेजिस्टर(sपंचांग32_पढ़ो_sched_घड़ी, bits, समयr_of_rate(to));
		pr_info("%s: STM32 sched_clock registered\n", name);

		sपंचांग32_समयr_delay.पढ़ो_current_समयr = sपंचांग32_पढ़ो_delay;
		sपंचांग32_समयr_delay.freq = समयr_of_rate(to);
		रेजिस्टर_current_समयr_delay(&sपंचांग32_समयr_delay);
		pr_info("%s: STM32 delay timer registered\n", name);
	पूर्ण

	वापस घड़ीsource_mmio_init(समयr_of_base(to) + TIM_CNT, name,
				     समयr_of_rate(to), bits == 32 ? 250 : 100,
				     bits, घड़ीsource_mmio_पढ़ोl_up);
पूर्ण

अटल व्योम __init sपंचांग32_घड़ीevent_init(काष्ठा समयr_of *to)
अणु
	u32 bits = sपंचांग32_समयr_of_bits_get(to);

	to->clkevt.name = to->np->full_name;
	to->clkevt.features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT;
	to->clkevt.set_state_shutकरोwn = sपंचांग32_घड़ी_event_shutकरोwn;
	to->clkevt.set_state_periodic = sपंचांग32_घड़ी_event_set_periodic;
	to->clkevt.set_state_oneshot = sपंचांग32_घड़ी_event_set_oneshot;
	to->clkevt.tick_resume = sपंचांग32_घड़ी_event_shutकरोwn;
	to->clkevt.set_next_event = sपंचांग32_घड़ी_event_set_next_event;
	to->clkevt.rating = bits == 32 ? 250 : 100;

	घड़ीevents_config_and_रेजिस्टर(&to->clkevt, समयr_of_rate(to), 0x1,
					(1 <<  bits) - 1);

	pr_info("%pOF: STM32 clockevent driver initialized (%d bits)\n",
		to->np, bits);
पूर्ण

अटल पूर्णांक __init sपंचांग32_समयr_init(काष्ठा device_node *node)
अणु
	काष्ठा reset_control *rstc;
	काष्ठा समयr_of *to;
	पूर्णांक ret;

	to = kzalloc(माप(*to), GFP_KERNEL);
	अगर (!to)
		वापस -ENOMEM;

	to->flags = TIMER_OF_IRQ | TIMER_OF_CLOCK | TIMER_OF_BASE;
	to->of_irq.handler = sपंचांग32_घड़ी_event_handler;

	ret = समयr_of_init(node, to);
	अगर (ret)
		जाओ err;

	to->निजी_data = kzalloc(माप(काष्ठा sपंचांग32_समयr_निजी),
				   GFP_KERNEL);
	अगर (!to->निजी_data) अणु
		ret = -ENOMEM;
		जाओ deinit;
	पूर्ण

	rstc = of_reset_control_get(node, शून्य);
	अगर (!IS_ERR(rstc)) अणु
		reset_control_निश्चित(rstc);
		reset_control_deनिश्चित(rstc);
	पूर्ण

	sपंचांग32_समयr_set_width(to);

	sपंचांग32_समयr_set_prescaler(to);

	ret = sपंचांग32_घड़ीsource_init(to);
	अगर (ret)
		जाओ deinit;

	sपंचांग32_घड़ीevent_init(to);
	वापस 0;

deinit:
	समयr_of_cleanup(to);
err:
	kमुक्त(to);
	वापस ret;
पूर्ण

TIMER_OF_DECLARE(sपंचांग32, "st,stm32-timer", sपंचांग32_समयr_init);
