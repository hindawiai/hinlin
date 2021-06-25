<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012-2013 Freescale Semiconductor, Inc.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/clk.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sched_घड़ी.h>

/*
 * Each pit takes 0x10 Bytes रेजिस्टर space
 */
#घोषणा PITMCR		0x00
#घोषणा PIT0_OFFSET	0x100
#घोषणा PITn_OFFSET(n)	(PIT0_OFFSET + 0x10 * (n))
#घोषणा PITLDVAL	0x00
#घोषणा PITCVAL		0x04
#घोषणा PITTCTRL	0x08
#घोषणा PITTFLG		0x0c

#घोषणा PITMCR_MDIS	(0x1 << 1)

#घोषणा PITTCTRL_TEN	(0x1 << 0)
#घोषणा PITTCTRL_TIE	(0x1 << 1)
#घोषणा PITCTRL_CHN	(0x1 << 2)

#घोषणा PITTFLG_TIF	0x1

अटल व्योम __iomem *clksrc_base;
अटल व्योम __iomem *clkevt_base;
अटल अचिन्हित दीर्घ cycle_per_jअगरfy;

अटल अंतरभूत व्योम pit_समयr_enable(व्योम)
अणु
	__raw_ग_लिखोl(PITTCTRL_TEN | PITTCTRL_TIE, clkevt_base + PITTCTRL);
पूर्ण

अटल अंतरभूत व्योम pit_समयr_disable(व्योम)
अणु
	__raw_ग_लिखोl(0, clkevt_base + PITTCTRL);
पूर्ण

अटल अंतरभूत व्योम pit_irq_acknowledge(व्योम)
अणु
	__raw_ग_लिखोl(PITTFLG_TIF, clkevt_base + PITTFLG);
पूर्ण

अटल u64 notrace pit_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस ~__raw_पढ़ोl(clksrc_base + PITCVAL);
पूर्ण

अटल पूर्णांक __init pit_घड़ीsource_init(अचिन्हित दीर्घ rate)
अणु
	/* set the max load value and start the घड़ी source counter */
	__raw_ग_लिखोl(0, clksrc_base + PITTCTRL);
	__raw_ग_लिखोl(~0UL, clksrc_base + PITLDVAL);
	__raw_ग_लिखोl(PITTCTRL_TEN, clksrc_base + PITTCTRL);

	sched_घड़ी_रेजिस्टर(pit_पढ़ो_sched_घड़ी, 32, rate);
	वापस घड़ीsource_mmio_init(clksrc_base + PITCVAL, "vf-pit", rate,
			300, 32, घड़ीsource_mmio_पढ़ोl_करोwn);
पूर्ण

अटल पूर्णांक pit_set_next_event(अचिन्हित दीर्घ delta,
				काष्ठा घड़ी_event_device *unused)
अणु
	/*
	 * set a new value to PITLDVAL रेजिस्टर will not restart the समयr,
	 * to पात the current cycle and start a समयr period with the new
	 * value, the समयr must be disabled and enabled again.
	 * and the PITLAVAL should be set to delta minus one according to pit
	 * hardware requirement.
	 */
	pit_समयr_disable();
	__raw_ग_लिखोl(delta - 1, clkevt_base + PITLDVAL);
	pit_समयr_enable();

	वापस 0;
पूर्ण

अटल पूर्णांक pit_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	pit_समयr_disable();
	वापस 0;
पूर्ण

अटल पूर्णांक pit_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	pit_set_next_event(cycle_per_jअगरfy, evt);
	वापस 0;
पूर्ण

अटल irqवापस_t pit_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	pit_irq_acknowledge();

	/*
	 * pit hardware करोesn't support oneshot, it will generate an पूर्णांकerrupt
	 * and reload the counter value from PITLDVAL when PITCVAL reach zero,
	 * and start the counter again. So software need to disable the समयr
	 * to stop the counter loop in ONESHOT mode.
	 */
	अगर (likely(घड़ीevent_state_oneshot(evt)))
		pit_समयr_disable();

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा घड़ी_event_device घड़ीevent_pit = अणु
	.name		= "VF pit timer",
	.features	= CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT,
	.set_state_shutकरोwn = pit_shutकरोwn,
	.set_state_periodic = pit_set_periodic,
	.set_next_event	= pit_set_next_event,
	.rating		= 300,
पूर्ण;

अटल पूर्णांक __init pit_घड़ीevent_init(अचिन्हित दीर्घ rate, पूर्णांक irq)
अणु
	__raw_ग_लिखोl(0, clkevt_base + PITTCTRL);
	__raw_ग_लिखोl(PITTFLG_TIF, clkevt_base + PITTFLG);

	BUG_ON(request_irq(irq, pit_समयr_पूर्णांकerrupt, IRQF_TIMER | IRQF_IRQPOLL,
			   "VF pit timer", &घड़ीevent_pit));

	घड़ीevent_pit.cpumask = cpumask_of(0);
	घड़ीevent_pit.irq = irq;
	/*
	 * The value क्रम the LDVAL रेजिस्टर trigger is calculated as:
	 * LDVAL trigger = (period / घड़ी period) - 1
	 * The pit is a 32-bit करोwn count समयr, when the counter value
	 * reaches 0, it will generate an पूर्णांकerrupt, thus the minimal
	 * LDVAL trigger value is 1. And then the min_delta is
	 * minimal LDVAL trigger value + 1, and the max_delta is full 32-bit.
	 */
	घड़ीevents_config_and_रेजिस्टर(&घड़ीevent_pit, rate, 2, 0xffffffff);

	वापस 0;
पूर्ण

अटल पूर्णांक __init pit_समयr_init(काष्ठा device_node *np)
अणु
	काष्ठा clk *pit_clk;
	व्योम __iomem *समयr_base;
	अचिन्हित दीर्घ clk_rate;
	पूर्णांक irq, ret;

	समयr_base = of_iomap(np, 0);
	अगर (!समयr_base) अणु
		pr_err("Failed to iomap\n");
		वापस -ENXIO;
	पूर्ण

	/*
	 * PIT0 and PIT1 can be chained to build a 64-bit समयr,
	 * so choose PIT2 as घड़ीsource, PIT3 as घड़ीevent device,
	 * and leave PIT0 and PIT1 unused क्रम anyone अन्यथा who needs them.
	 */
	clksrc_base = समयr_base + PITn_OFFSET(2);
	clkevt_base = समयr_base + PITn_OFFSET(3);

	irq = irq_of_parse_and_map(np, 0);
	अगर (irq <= 0)
		वापस -EINVAL;

	pit_clk = of_clk_get(np, 0);
	अगर (IS_ERR(pit_clk))
		वापस PTR_ERR(pit_clk);

	ret = clk_prepare_enable(pit_clk);
	अगर (ret)
		वापस ret;

	clk_rate = clk_get_rate(pit_clk);
	cycle_per_jअगरfy = clk_rate / (HZ);

	/* enable the pit module */
	__raw_ग_लिखोl(~PITMCR_MDIS, समयr_base + PITMCR);

	ret = pit_घड़ीsource_init(clk_rate);
	अगर (ret)
		वापस ret;

	वापस pit_घड़ीevent_init(clk_rate, irq);
पूर्ण
TIMER_OF_DECLARE(vf610, "fsl,vf610-pit", pit_समयr_init);
