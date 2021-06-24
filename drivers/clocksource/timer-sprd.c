<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Spपढ़ोtrum Communications Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "timer-of.h"

#घोषणा TIMER_NAME		"sprd_timer"

#घोषणा TIMER_LOAD_LO		0x0
#घोषणा TIMER_LOAD_HI		0x4
#घोषणा TIMER_VALUE_LO		0x8
#घोषणा TIMER_VALUE_HI		0xc

#घोषणा TIMER_CTL		0x10
#घोषणा TIMER_CTL_PERIOD_MODE	BIT(0)
#घोषणा TIMER_CTL_ENABLE	BIT(1)
#घोषणा TIMER_CTL_64BIT_WIDTH	BIT(16)

#घोषणा TIMER_INT		0x14
#घोषणा TIMER_INT_EN		BIT(0)
#घोषणा TIMER_INT_RAW_STS	BIT(1)
#घोषणा TIMER_INT_MASK_STS	BIT(2)
#घोषणा TIMER_INT_CLR		BIT(3)

#घोषणा TIMER_VALUE_SHDW_LO	0x18
#घोषणा TIMER_VALUE_SHDW_HI	0x1c

#घोषणा TIMER_VALUE_LO_MASK	GENMASK(31, 0)

अटल व्योम sprd_समयr_enable(व्योम __iomem *base, u32 flag)
अणु
	u32 val = पढ़ोl_relaxed(base + TIMER_CTL);

	val |= TIMER_CTL_ENABLE;
	अगर (flag & TIMER_CTL_64BIT_WIDTH)
		val |= TIMER_CTL_64BIT_WIDTH;
	अन्यथा
		val &= ~TIMER_CTL_64BIT_WIDTH;

	अगर (flag & TIMER_CTL_PERIOD_MODE)
		val |= TIMER_CTL_PERIOD_MODE;
	अन्यथा
		val &= ~TIMER_CTL_PERIOD_MODE;

	ग_लिखोl_relaxed(val, base + TIMER_CTL);
पूर्ण

अटल व्योम sprd_समयr_disable(व्योम __iomem *base)
अणु
	u32 val = पढ़ोl_relaxed(base + TIMER_CTL);

	val &= ~TIMER_CTL_ENABLE;
	ग_लिखोl_relaxed(val, base + TIMER_CTL);
पूर्ण

अटल व्योम sprd_समयr_update_counter(व्योम __iomem *base, अचिन्हित दीर्घ cycles)
अणु
	ग_लिखोl_relaxed(cycles & TIMER_VALUE_LO_MASK, base + TIMER_LOAD_LO);
	ग_लिखोl_relaxed(0, base + TIMER_LOAD_HI);
पूर्ण

अटल व्योम sprd_समयr_enable_पूर्णांकerrupt(व्योम __iomem *base)
अणु
	ग_लिखोl_relaxed(TIMER_INT_EN, base + TIMER_INT);
पूर्ण

अटल व्योम sprd_समयr_clear_पूर्णांकerrupt(व्योम __iomem *base)
अणु
	u32 val = पढ़ोl_relaxed(base + TIMER_INT);

	val |= TIMER_INT_CLR;
	ग_लिखोl_relaxed(val, base + TIMER_INT);
पूर्ण

अटल पूर्णांक sprd_समयr_set_next_event(अचिन्हित दीर्घ cycles,
				     काष्ठा घड़ी_event_device *ce)
अणु
	काष्ठा समयr_of *to = to_समयr_of(ce);

	sprd_समयr_disable(समयr_of_base(to));
	sprd_समयr_update_counter(समयr_of_base(to), cycles);
	sprd_समयr_enable(समयr_of_base(to), 0);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_समयr_set_periodic(काष्ठा घड़ी_event_device *ce)
अणु
	काष्ठा समयr_of *to = to_समयr_of(ce);

	sprd_समयr_disable(समयr_of_base(to));
	sprd_समयr_update_counter(समयr_of_base(to), समयr_of_period(to));
	sprd_समयr_enable(समयr_of_base(to), TIMER_CTL_PERIOD_MODE);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_समयr_shutकरोwn(काष्ठा घड़ी_event_device *ce)
अणु
	काष्ठा समयr_of *to = to_समयr_of(ce);

	sprd_समयr_disable(समयr_of_base(to));
	वापस 0;
पूर्ण

अटल irqवापस_t sprd_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *ce = (काष्ठा घड़ी_event_device *)dev_id;
	काष्ठा समयr_of *to = to_समयr_of(ce);

	sprd_समयr_clear_पूर्णांकerrupt(समयr_of_base(to));

	अगर (घड़ीevent_state_oneshot(ce))
		sprd_समयr_disable(समयr_of_base(to));

	ce->event_handler(ce);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा समयr_of to = अणु
	.flags = TIMER_OF_IRQ | TIMER_OF_BASE | TIMER_OF_CLOCK,

	.clkevt = अणु
		.name = TIMER_NAME,
		.rating = 300,
		.features = CLOCK_EVT_FEAT_DYNIRQ | CLOCK_EVT_FEAT_PERIODIC |
			CLOCK_EVT_FEAT_ONESHOT,
		.set_state_shutकरोwn = sprd_समयr_shutकरोwn,
		.set_state_periodic = sprd_समयr_set_periodic,
		.set_next_event = sprd_समयr_set_next_event,
		.cpumask = cpu_possible_mask,
	पूर्ण,

	.of_irq = अणु
		.handler = sprd_समयr_पूर्णांकerrupt,
		.flags = IRQF_TIMER | IRQF_IRQPOLL,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sprd_समयr_init(काष्ठा device_node *np)
अणु
	पूर्णांक ret;

	ret = समयr_of_init(np, &to);
	अगर (ret)
		वापस ret;

	sprd_समयr_enable_पूर्णांकerrupt(समयr_of_base(&to));
	घड़ीevents_config_and_रेजिस्टर(&to.clkevt, समयr_of_rate(&to),
					1, अच_पूर्णांक_उच्च);

	वापस 0;
पूर्ण

अटल काष्ठा समयr_of suspend_to = अणु
	.flags = TIMER_OF_BASE | TIMER_OF_CLOCK,
पूर्ण;

अटल u64 sprd_suspend_समयr_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस ~(u64)पढ़ोl_relaxed(समयr_of_base(&suspend_to) +
				   TIMER_VALUE_SHDW_LO) & cs->mask;
पूर्ण

अटल पूर्णांक sprd_suspend_समयr_enable(काष्ठा घड़ीsource *cs)
अणु
	sprd_समयr_update_counter(समयr_of_base(&suspend_to),
				  TIMER_VALUE_LO_MASK);
	sprd_समयr_enable(समयr_of_base(&suspend_to), TIMER_CTL_PERIOD_MODE);

	वापस 0;
पूर्ण

अटल व्योम sprd_suspend_समयr_disable(काष्ठा घड़ीsource *cs)
अणु
	sprd_समयr_disable(समयr_of_base(&suspend_to));
पूर्ण

अटल काष्ठा घड़ीsource suspend_घड़ीsource = अणु
	.name	= "sprd_suspend_timer",
	.rating	= 200,
	.पढ़ो	= sprd_suspend_समयr_पढ़ो,
	.enable = sprd_suspend_समयr_enable,
	.disable = sprd_suspend_समयr_disable,
	.mask	= CLOCKSOURCE_MASK(32),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS | CLOCK_SOURCE_SUSPEND_NONSTOP,
पूर्ण;

अटल पूर्णांक __init sprd_suspend_समयr_init(काष्ठा device_node *np)
अणु
	पूर्णांक ret;

	ret = समयr_of_init(np, &suspend_to);
	अगर (ret)
		वापस ret;

	घड़ीsource_रेजिस्टर_hz(&suspend_घड़ीsource,
				समयr_of_rate(&suspend_to));

	वापस 0;
पूर्ण

TIMER_OF_DECLARE(sc9860_समयr, "sprd,sc9860-timer", sprd_समयr_init);
TIMER_OF_DECLARE(sc9860_persistent_समयr, "sprd,sc9860-suspend-timer",
		 sprd_suspend_समयr_init);
