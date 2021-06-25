<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014-2018 Nuvoton Technologies tomer.maimon@nuvoton.com
 * All rights reserved.
 *
 * Copyright 2017 Google, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश "timer-of.h"

/* Timers रेजिस्टरs */
#घोषणा NPCM7XX_REG_TCSR0	0x0 /* Timer 0 Control and Status Register */
#घोषणा NPCM7XX_REG_TICR0	0x8 /* Timer 0 Initial Count Register */
#घोषणा NPCM7XX_REG_TCSR1	0x4 /* Timer 1 Control and Status Register */
#घोषणा NPCM7XX_REG_TICR1	0xc /* Timer 1 Initial Count Register */
#घोषणा NPCM7XX_REG_TDR1	0x14 /* Timer 1 Data Register */
#घोषणा NPCM7XX_REG_TISR	0x18 /* Timer Interrupt Status Register */

/* Timers control */
#घोषणा NPCM7XX_Tx_RESETINT		0x1f
#घोषणा NPCM7XX_Tx_PERIOD		BIT(27)
#घोषणा NPCM7XX_Tx_INTEN		BIT(29)
#घोषणा NPCM7XX_Tx_COUNTEN		BIT(30)
#घोषणा NPCM7XX_Tx_ONESHOT		0x0
#घोषणा NPCM7XX_Tx_OPER			GENMASK(28, 27)
#घोषणा NPCM7XX_Tx_MIN_PRESCALE		0x1
#घोषणा NPCM7XX_Tx_TDR_MASK_BITS	24
#घोषणा NPCM7XX_Tx_MAX_CNT		0xFFFFFF
#घोषणा NPCM7XX_T0_CLR_INT		0x1
#घोषणा NPCM7XX_Tx_CLR_CSR		0x0

/* Timers operating mode */
#घोषणा NPCM7XX_START_PERIODIC_Tx (NPCM7XX_Tx_PERIOD | NPCM7XX_Tx_COUNTEN | \
					NPCM7XX_Tx_INTEN | \
					NPCM7XX_Tx_MIN_PRESCALE)

#घोषणा NPCM7XX_START_ONESHOT_Tx (NPCM7XX_Tx_ONESHOT | NPCM7XX_Tx_COUNTEN | \
					NPCM7XX_Tx_INTEN | \
					NPCM7XX_Tx_MIN_PRESCALE)

#घोषणा NPCM7XX_START_Tx (NPCM7XX_Tx_COUNTEN | NPCM7XX_Tx_PERIOD | \
				NPCM7XX_Tx_MIN_PRESCALE)

#घोषणा NPCM7XX_DEFAULT_CSR (NPCM7XX_Tx_CLR_CSR | NPCM7XX_Tx_MIN_PRESCALE)

अटल पूर्णांक npcm7xx_समयr_resume(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(evt);
	u32 val;

	val = पढ़ोl(समयr_of_base(to) + NPCM7XX_REG_TCSR0);
	val |= NPCM7XX_Tx_COUNTEN;
	ग_लिखोl(val, समयr_of_base(to) + NPCM7XX_REG_TCSR0);

	वापस 0;
पूर्ण

अटल पूर्णांक npcm7xx_समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(evt);
	u32 val;

	val = पढ़ोl(समयr_of_base(to) + NPCM7XX_REG_TCSR0);
	val &= ~NPCM7XX_Tx_COUNTEN;
	ग_लिखोl(val, समयr_of_base(to) + NPCM7XX_REG_TCSR0);

	वापस 0;
पूर्ण

अटल पूर्णांक npcm7xx_समयr_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(evt);
	u32 val;

	val = पढ़ोl(समयr_of_base(to) + NPCM7XX_REG_TCSR0);
	val &= ~NPCM7XX_Tx_OPER;
	val |= NPCM7XX_START_ONESHOT_Tx;
	ग_लिखोl(val, समयr_of_base(to) + NPCM7XX_REG_TCSR0);

	वापस 0;
पूर्ण

अटल पूर्णांक npcm7xx_समयr_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(evt);
	u32 val;

	ग_लिखोl(समयr_of_period(to), समयr_of_base(to) + NPCM7XX_REG_TICR0);

	val = पढ़ोl(समयr_of_base(to) + NPCM7XX_REG_TCSR0);
	val &= ~NPCM7XX_Tx_OPER;
	val |= NPCM7XX_START_PERIODIC_Tx;
	ग_लिखोl(val, समयr_of_base(to) + NPCM7XX_REG_TCSR0);

	वापस 0;
पूर्ण

अटल पूर्णांक npcm7xx_घड़ीevent_set_next_event(अचिन्हित दीर्घ evt,
		काष्ठा घड़ी_event_device *clk)
अणु
	काष्ठा समयr_of *to = to_समयr_of(clk);
	u32 val;

	ग_लिखोl(evt, समयr_of_base(to) + NPCM7XX_REG_TICR0);
	val = पढ़ोl(समयr_of_base(to) + NPCM7XX_REG_TCSR0);
	val |= NPCM7XX_START_Tx;
	ग_लिखोl(val, समयr_of_base(to) + NPCM7XX_REG_TCSR0);

	वापस 0;
पूर्ण

अटल irqवापस_t npcm7xx_समयr0_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = (काष्ठा घड़ी_event_device *)dev_id;
	काष्ठा समयr_of *to = to_समयr_of(evt);

	ग_लिखोl(NPCM7XX_T0_CLR_INT, समयr_of_base(to) + NPCM7XX_REG_TISR);

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा समयr_of npcm7xx_to = अणु
	.flags = TIMER_OF_IRQ | TIMER_OF_BASE | TIMER_OF_CLOCK,

	.clkevt = अणु
		.name		    = "npcm7xx-timer0",
		.features	    = CLOCK_EVT_FEAT_PERIODIC |
				      CLOCK_EVT_FEAT_ONESHOT,
		.set_next_event	    = npcm7xx_घड़ीevent_set_next_event,
		.set_state_shutकरोwn = npcm7xx_समयr_shutकरोwn,
		.set_state_periodic = npcm7xx_समयr_periodic,
		.set_state_oneshot  = npcm7xx_समयr_oneshot,
		.tick_resume	    = npcm7xx_समयr_resume,
		.rating		    = 300,
	पूर्ण,

	.of_irq = अणु
		.handler = npcm7xx_समयr0_पूर्णांकerrupt,
		.flags = IRQF_TIMER | IRQF_IRQPOLL,
	पूर्ण,
पूर्ण;

अटल व्योम __init npcm7xx_घड़ीevents_init(व्योम)
अणु
	ग_लिखोl(NPCM7XX_DEFAULT_CSR,
		समयr_of_base(&npcm7xx_to) + NPCM7XX_REG_TCSR0);

	ग_लिखोl(NPCM7XX_Tx_RESETINT,
		समयr_of_base(&npcm7xx_to) + NPCM7XX_REG_TISR);

	npcm7xx_to.clkevt.cpumask = cpumask_of(0);
	घड़ीevents_config_and_रेजिस्टर(&npcm7xx_to.clkevt,
					समयr_of_rate(&npcm7xx_to),
					0x1, NPCM7XX_Tx_MAX_CNT);
पूर्ण

अटल व्योम __init npcm7xx_घड़ीsource_init(व्योम)
अणु
	u32 val;

	ग_लिखोl(NPCM7XX_DEFAULT_CSR,
		समयr_of_base(&npcm7xx_to) + NPCM7XX_REG_TCSR1);
	ग_लिखोl(NPCM7XX_Tx_MAX_CNT,
		समयr_of_base(&npcm7xx_to) + NPCM7XX_REG_TICR1);

	val = पढ़ोl(समयr_of_base(&npcm7xx_to) + NPCM7XX_REG_TCSR1);
	val |= NPCM7XX_START_Tx;
	ग_लिखोl(val, समयr_of_base(&npcm7xx_to) + NPCM7XX_REG_TCSR1);

	घड़ीsource_mmio_init(समयr_of_base(&npcm7xx_to) +
				NPCM7XX_REG_TDR1,
				"npcm7xx-timer1", समयr_of_rate(&npcm7xx_to),
				200, (अचिन्हित पूर्णांक)NPCM7XX_Tx_TDR_MASK_BITS,
				घड़ीsource_mmio_पढ़ोl_करोwn);
पूर्ण

अटल पूर्णांक __init npcm7xx_समयr_init(काष्ठा device_node *np)
अणु
	पूर्णांक ret;

	ret = समयr_of_init(np, &npcm7xx_to);
	अगर (ret)
		वापस ret;

	/* Clock input is भागided by PRESCALE + 1 beक्रमe it is fed */
	/* to the counter */
	npcm7xx_to.of_clk.rate = npcm7xx_to.of_clk.rate /
		(NPCM7XX_Tx_MIN_PRESCALE + 1);

	npcm7xx_घड़ीsource_init();
	npcm7xx_घड़ीevents_init();

	pr_info("Enabling NPCM7xx clocksource timer base: %px, IRQ: %d ",
		समयr_of_base(&npcm7xx_to), समयr_of_irq(&npcm7xx_to));

	वापस 0;
पूर्ण

TIMER_OF_DECLARE(wpcm450, "nuvoton,wpcm450-timer", npcm7xx_समयr_init);
TIMER_OF_DECLARE(npcm7xx, "nuvoton,npcm750-timer", npcm7xx_समयr_init);

