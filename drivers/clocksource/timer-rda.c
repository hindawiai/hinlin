<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * RDA8810PL SoC समयr driver
 *
 * Copyright RDA Microelectronics Company Limited
 * Copyright (c) 2017 Andreas Fथअrber
 * Copyright (c) 2018 Manivannan Sadhasivam
 *
 * RDA8810PL has two independent समयrs: OSTIMER (56 bit) and HWTIMER (64 bit).
 * Each समयr provides optional पूर्णांकerrupt support. In this driver, OSTIMER is
 * used क्रम घड़ीevents and HWTIMER is used क्रम घड़ीsource.
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "timer-of.h"

#घोषणा RDA_OSTIMER_LOADVAL_L	0x000
#घोषणा RDA_OSTIMER_CTRL	0x004
#घोषणा RDA_HWTIMER_LOCKVAL_L	0x024
#घोषणा RDA_HWTIMER_LOCKVAL_H	0x028
#घोषणा RDA_TIMER_IRQ_MASK_SET	0x02c
#घोषणा RDA_TIMER_IRQ_MASK_CLR	0x030
#घोषणा RDA_TIMER_IRQ_CLR	0x034

#घोषणा RDA_OSTIMER_CTRL_ENABLE		BIT(24)
#घोषणा RDA_OSTIMER_CTRL_REPEAT		BIT(28)
#घोषणा RDA_OSTIMER_CTRL_LOAD		BIT(30)

#घोषणा RDA_TIMER_IRQ_MASK_OSTIMER	BIT(0)

#घोषणा RDA_TIMER_IRQ_CLR_OSTIMER	BIT(0)

अटल पूर्णांक rda_osसमयr_start(व्योम __iomem *base, bool periodic, u64 cycles)
अणु
	u32 ctrl, load_l;

	load_l = (u32)cycles;
	ctrl = ((cycles >> 32) & 0xffffff);
	ctrl |= RDA_OSTIMER_CTRL_LOAD | RDA_OSTIMER_CTRL_ENABLE;
	अगर (periodic)
		ctrl |= RDA_OSTIMER_CTRL_REPEAT;

	/* Enable osसमयr पूर्णांकerrupt first */
	ग_लिखोl_relaxed(RDA_TIMER_IRQ_MASK_OSTIMER,
		       base + RDA_TIMER_IRQ_MASK_SET);

	/* Write low 32 bits first, high 24 bits are with ctrl */
	ग_लिखोl_relaxed(load_l, base + RDA_OSTIMER_LOADVAL_L);
	ग_लिखोl_relaxed(ctrl, base + RDA_OSTIMER_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक rda_osसमयr_stop(व्योम __iomem *base)
अणु
	/* Disable osसमयr पूर्णांकerrupt first */
	ग_लिखोl_relaxed(RDA_TIMER_IRQ_MASK_OSTIMER,
		       base + RDA_TIMER_IRQ_MASK_CLR);

	ग_लिखोl_relaxed(0, base + RDA_OSTIMER_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक rda_osसमयr_set_state_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(evt);

	rda_osसमयr_stop(समयr_of_base(to));

	वापस 0;
पूर्ण

अटल पूर्णांक rda_osसमयr_set_state_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(evt);

	rda_osसमयr_stop(समयr_of_base(to));

	वापस 0;
पूर्ण

अटल पूर्णांक rda_osसमयr_set_state_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(evt);
	अचिन्हित दीर्घ cycles_per_jअगरfy;

	rda_osसमयr_stop(समयr_of_base(to));

	cycles_per_jअगरfy = ((अचिन्हित दीर्घ दीर्घ)NSEC_PER_SEC / HZ *
			     evt->mult) >> evt->shअगरt;
	rda_osसमयr_start(समयr_of_base(to), true, cycles_per_jअगरfy);

	वापस 0;
पूर्ण

अटल पूर्णांक rda_osसमयr_tick_resume(काष्ठा घड़ी_event_device *evt)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक rda_osसमयr_set_next_event(अचिन्हित दीर्घ evt,
				      काष्ठा घड़ी_event_device *ev)
अणु
	काष्ठा समयr_of *to = to_समयr_of(ev);

	rda_osसमयr_start(समयr_of_base(to), false, evt);

	वापस 0;
पूर्ण

अटल irqवापस_t rda_osसमयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;
	काष्ठा समयr_of *to = to_समयr_of(evt);

	/* clear समयr पूर्णांक */
	ग_लिखोl_relaxed(RDA_TIMER_IRQ_CLR_OSTIMER,
		       समयr_of_base(to) + RDA_TIMER_IRQ_CLR);

	अगर (evt->event_handler)
		evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा समयr_of rda_osसमयr_of = अणु
	.flags = TIMER_OF_IRQ | TIMER_OF_BASE,

	.clkevt = अणु
		.name = "rda-ostimer",
		.rating = 250,
		.features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT |
			    CLOCK_EVT_FEAT_DYNIRQ,
		.set_state_shutकरोwn = rda_osसमयr_set_state_shutकरोwn,
		.set_state_oneshot = rda_osसमयr_set_state_oneshot,
		.set_state_periodic = rda_osसमयr_set_state_periodic,
		.tick_resume = rda_osसमयr_tick_resume,
		.set_next_event	= rda_osसमयr_set_next_event,
	पूर्ण,

	.of_base = अणु
		.name = "rda-timer",
		.index = 0,
	पूर्ण,

	.of_irq = अणु
		.name = "ostimer",
		.handler = rda_osसमयr_पूर्णांकerrupt,
		.flags = IRQF_TIMER,
	पूर्ण,
पूर्ण;

अटल u64 rda_hwसमयr_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	व्योम __iomem *base = समयr_of_base(&rda_osसमयr_of);
	u32 lo, hi;

	/* Always पढ़ो low 32 bits first */
	करो अणु
		lo = पढ़ोl_relaxed(base + RDA_HWTIMER_LOCKVAL_L);
		hi = पढ़ोl_relaxed(base + RDA_HWTIMER_LOCKVAL_H);
	पूर्ण जबतक (hi != पढ़ोl_relaxed(base + RDA_HWTIMER_LOCKVAL_H));

	वापस ((u64)hi << 32) | lo;
पूर्ण

अटल काष्ठा घड़ीsource rda_hwसमयr_घड़ीsource = अणु
	.name           = "rda-timer",
	.rating         = 400,
	.पढ़ो           = rda_hwसमयr_पढ़ो,
	.mask           = CLOCKSOURCE_MASK(64),
	.flags          = CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल पूर्णांक __init rda_समयr_init(काष्ठा device_node *np)
अणु
	अचिन्हित दीर्घ rate = 2000000;
	पूर्णांक ret;

	ret = समयr_of_init(np, &rda_osसमयr_of);
	अगर (ret)
		वापस ret;

	घड़ीsource_रेजिस्टर_hz(&rda_hwसमयr_घड़ीsource, rate);

	घड़ीevents_config_and_रेजिस्टर(&rda_osसमयr_of.clkevt, rate,
					0x2, अच_पूर्णांक_उच्च);

	वापस 0;
पूर्ण

TIMER_OF_DECLARE(rda8810pl, "rda,8810pl-timer", rda_समयr_init);
