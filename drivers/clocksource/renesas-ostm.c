<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas Timer Support - OSTM
 *
 * Copyright (C) 2017 Renesas Electronics America, Inc.
 * Copyright (C) 2017 Chris Bअक्रमt
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/slab.h>

#समावेश "timer-of.h"

/*
 * The OSTM contains independent channels.
 * The first OSTM channel probed will be set up as a मुक्त running
 * घड़ीsource. Additionally we will use this घड़ीsource क्रम the प्रणाली
 * schedule समयr sched_घड़ी().
 *
 * The second (or more) channel probed will be set up as an पूर्णांकerrupt
 * driven घड़ी event.
 */

अटल व्योम __iomem *प्रणाली_घड़ी;	/* For sched_घड़ी() */

/* OSTM REGISTERS */
#घोषणा	OSTM_CMP		0x000	/* RW,32 */
#घोषणा	OSTM_CNT		0x004	/* R,32 */
#घोषणा	OSTM_TE			0x010	/* R,8 */
#घोषणा	OSTM_TS			0x014	/* W,8 */
#घोषणा	OSTM_TT			0x018	/* W,8 */
#घोषणा	OSTM_CTL		0x020	/* RW,8 */

#घोषणा	TE			0x01
#घोषणा	TS			0x01
#घोषणा	TT			0x01
#घोषणा	CTL_PERIODIC		0x00
#घोषणा	CTL_ONESHOT		0x02
#घोषणा	CTL_FREERUN		0x02

अटल व्योम osपंचांग_समयr_stop(काष्ठा समयr_of *to)
अणु
	अगर (पढ़ोb(समयr_of_base(to) + OSTM_TE) & TE) अणु
		ग_लिखोb(TT, समयr_of_base(to) + OSTM_TT);

		/*
		 * Read back the रेजिस्टर simply to confirm the ग_लिखो operation
		 * has completed since I/O ग_लिखोs can someबार get queued by
		 * the bus architecture.
		 */
		जबतक (पढ़ोb(समयr_of_base(to) + OSTM_TE) & TE)
			;
	पूर्ण
पूर्ण

अटल पूर्णांक __init osपंचांग_init_clksrc(काष्ठा समयr_of *to)
अणु
	osपंचांग_समयr_stop(to);

	ग_लिखोl(0, समयr_of_base(to) + OSTM_CMP);
	ग_लिखोb(CTL_FREERUN, समयr_of_base(to) + OSTM_CTL);
	ग_लिखोb(TS, समयr_of_base(to) + OSTM_TS);

	वापस घड़ीsource_mmio_init(समयr_of_base(to) + OSTM_CNT,
				     to->np->full_name, समयr_of_rate(to), 300,
				     32, घड़ीsource_mmio_पढ़ोl_up);
पूर्ण

अटल u64 notrace osपंचांग_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस पढ़ोl(प्रणाली_घड़ी);
पूर्ण

अटल व्योम __init osपंचांग_init_sched_घड़ी(काष्ठा समयr_of *to)
अणु
	प्रणाली_घड़ी = समयr_of_base(to) + OSTM_CNT;
	sched_घड़ी_रेजिस्टर(osपंचांग_पढ़ो_sched_घड़ी, 32, समयr_of_rate(to));
पूर्ण

अटल पूर्णांक osपंचांग_घड़ी_event_next(अचिन्हित दीर्घ delta,
				 काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा समयr_of *to = to_समयr_of(ced);

	osपंचांग_समयr_stop(to);

	ग_लिखोl(delta, समयr_of_base(to) + OSTM_CMP);
	ग_लिखोb(CTL_ONESHOT, समयr_of_base(to) + OSTM_CTL);
	ग_लिखोb(TS, समयr_of_base(to) + OSTM_TS);

	वापस 0;
पूर्ण

अटल पूर्णांक osपंचांग_shutकरोwn(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा समयr_of *to = to_समयr_of(ced);

	osपंचांग_समयr_stop(to);

	वापस 0;
पूर्ण
अटल पूर्णांक osपंचांग_set_periodic(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा समयr_of *to = to_समयr_of(ced);

	अगर (घड़ीevent_state_oneshot(ced) || घड़ीevent_state_periodic(ced))
		osपंचांग_समयr_stop(to);

	ग_लिखोl(समयr_of_period(to) - 1, समयr_of_base(to) + OSTM_CMP);
	ग_लिखोb(CTL_PERIODIC, समयr_of_base(to) + OSTM_CTL);
	ग_लिखोb(TS, समयr_of_base(to) + OSTM_TS);

	वापस 0;
पूर्ण

अटल पूर्णांक osपंचांग_set_oneshot(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा समयr_of *to = to_समयr_of(ced);

	osपंचांग_समयr_stop(to);

	वापस 0;
पूर्ण

अटल irqवापस_t osपंचांग_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *ced = dev_id;

	अगर (घड़ीevent_state_oneshot(ced))
		osपंचांग_समयr_stop(to_समयr_of(ced));

	/* notअगरy घड़ीevent layer */
	अगर (ced->event_handler)
		ced->event_handler(ced);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init osपंचांग_init_clkevt(काष्ठा समयr_of *to)
अणु
	काष्ठा घड़ी_event_device *ced = &to->clkevt;

	ced->features = CLOCK_EVT_FEAT_ONESHOT | CLOCK_EVT_FEAT_PERIODIC;
	ced->set_state_shutकरोwn = osपंचांग_shutकरोwn;
	ced->set_state_periodic = osपंचांग_set_periodic;
	ced->set_state_oneshot = osपंचांग_set_oneshot;
	ced->set_next_event = osपंचांग_घड़ी_event_next;
	ced->shअगरt = 32;
	ced->rating = 300;
	ced->cpumask = cpumask_of(0);
	घड़ीevents_config_and_रेजिस्टर(ced, समयr_of_rate(to), 0xf,
					0xffffffff);

	वापस 0;
पूर्ण

अटल पूर्णांक __init osपंचांग_init(काष्ठा device_node *np)
अणु
	काष्ठा समयr_of *to;
	पूर्णांक ret;

	to = kzalloc(माप(*to), GFP_KERNEL);
	अगर (!to)
		वापस -ENOMEM;

	to->flags = TIMER_OF_BASE | TIMER_OF_CLOCK;
	अगर (प्रणाली_घड़ी) अणु
		/*
		 * घड़ी sources करोn't use पूर्णांकerrupts, घड़ी events करो
		 */
		to->flags |= TIMER_OF_IRQ;
		to->of_irq.flags = IRQF_TIMER | IRQF_IRQPOLL;
		to->of_irq.handler = osपंचांग_समयr_पूर्णांकerrupt;
	पूर्ण

	ret = समयr_of_init(np, to);
	अगर (ret)
		जाओ err_मुक्त;

	/*
	 * First probed device will be used as प्रणाली घड़ीsource. Any
	 * additional devices will be used as घड़ी events.
	 */
	अगर (!प्रणाली_घड़ी) अणु
		ret = osपंचांग_init_clksrc(to);
		अगर (ret)
			जाओ err_cleanup;

		osपंचांग_init_sched_घड़ी(to);
		pr_info("%pOF: used for clocksource\n", np);
	पूर्ण अन्यथा अणु
		ret = osपंचांग_init_clkevt(to);
		अगर (ret)
			जाओ err_cleanup;

		pr_info("%pOF: used for clock events\n", np);
	पूर्ण

	वापस 0;

err_cleanup:
	समयr_of_cleanup(to);
err_मुक्त:
	kमुक्त(to);
	वापस ret;
पूर्ण

TIMER_OF_DECLARE(osपंचांग, "renesas,ostm", osपंचांग_init);
