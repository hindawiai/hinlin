<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Amlogic Meson6 SoCs समयr handling.
 *
 * Copyright (C) 2014 Carlo Caione <carlo@caione.org>
 *
 * Based on code from Amlogic, Inc
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#अगर_घोषित CONFIG_ARM
#समावेश <linux/delay.h>
#पूर्ण_अगर

#घोषणा MESON_ISA_TIMER_MUX					0x00
#घोषणा MESON_ISA_TIMER_MUX_TIMERD_EN				BIT(19)
#घोषणा MESON_ISA_TIMER_MUX_TIMERC_EN				BIT(18)
#घोषणा MESON_ISA_TIMER_MUX_TIMERB_EN				BIT(17)
#घोषणा MESON_ISA_TIMER_MUX_TIMERA_EN				BIT(16)
#घोषणा MESON_ISA_TIMER_MUX_TIMERD_MODE				BIT(15)
#घोषणा MESON_ISA_TIMER_MUX_TIMERC_MODE				BIT(14)
#घोषणा MESON_ISA_TIMER_MUX_TIMERB_MODE				BIT(13)
#घोषणा MESON_ISA_TIMER_MUX_TIMERA_MODE				BIT(12)
#घोषणा MESON_ISA_TIMER_MUX_TIMERE_INPUT_CLOCK_MASK		GENMASK(10, 8)
#घोषणा MESON_ISA_TIMER_MUX_TIMERE_INPUT_CLOCK_SYSTEM_CLOCK	0x0
#घोषणा MESON_ISA_TIMER_MUX_TIMERE_INPUT_CLOCK_1US		0x1
#घोषणा MESON_ISA_TIMER_MUX_TIMERE_INPUT_CLOCK_10US		0x2
#घोषणा MESON_ISA_TIMER_MUX_TIMERE_INPUT_CLOCK_100US		0x3
#घोषणा MESON_ISA_TIMER_MUX_TIMERE_INPUT_CLOCK_1MS		0x4
#घोषणा MESON_ISA_TIMER_MUX_TIMERD_INPUT_CLOCK_MASK		GENMASK(7, 6)
#घोषणा MESON_ISA_TIMER_MUX_TIMERC_INPUT_CLOCK_MASK		GENMASK(5, 4)
#घोषणा MESON_ISA_TIMER_MUX_TIMERB_INPUT_CLOCK_MASK		GENMASK(3, 2)
#घोषणा MESON_ISA_TIMER_MUX_TIMERA_INPUT_CLOCK_MASK		GENMASK(1, 0)
#घोषणा MESON_ISA_TIMER_MUX_TIMERABCD_INPUT_CLOCK_1US		0x0
#घोषणा MESON_ISA_TIMER_MUX_TIMERABCD_INPUT_CLOCK_10US		0x1
#घोषणा MESON_ISA_TIMER_MUX_TIMERABCD_INPUT_CLOCK_100US		0x0
#घोषणा MESON_ISA_TIMER_MUX_TIMERABCD_INPUT_CLOCK_1MS		0x3

#घोषणा MESON_ISA_TIMERA					0x04
#घोषणा MESON_ISA_TIMERB					0x08
#घोषणा MESON_ISA_TIMERC					0x0c
#घोषणा MESON_ISA_TIMERD					0x10
#घोषणा MESON_ISA_TIMERE					0x14

अटल व्योम __iomem *समयr_base;

#अगर_घोषित CONFIG_ARM
अटल अचिन्हित दीर्घ meson6_पढ़ो_current_समयr(व्योम)
अणु
	वापस पढ़ोl_relaxed(समयr_base + MESON_ISA_TIMERE);
पूर्ण

अटल काष्ठा delay_समयr meson6_delay_समयr = अणु
	.पढ़ो_current_समयr = meson6_पढ़ो_current_समयr,
	.freq = 1000 * 1000,
पूर्ण;
#पूर्ण_अगर

अटल u64 notrace meson6_समयr_sched_पढ़ो(व्योम)
अणु
	वापस (u64)पढ़ोl(समयr_base + MESON_ISA_TIMERE);
पूर्ण

अटल व्योम meson6_clkevt_समय_stop(व्योम)
अणु
	u32 val = पढ़ोl(समयr_base + MESON_ISA_TIMER_MUX);

	ग_लिखोl(val & ~MESON_ISA_TIMER_MUX_TIMERA_EN,
	       समयr_base + MESON_ISA_TIMER_MUX);
पूर्ण

अटल व्योम meson6_clkevt_समय_setup(अचिन्हित दीर्घ delay)
अणु
	ग_लिखोl(delay, समयr_base + MESON_ISA_TIMERA);
पूर्ण

अटल व्योम meson6_clkevt_समय_start(bool periodic)
अणु
	u32 val = पढ़ोl(समयr_base + MESON_ISA_TIMER_MUX);

	अगर (periodic)
		val |= MESON_ISA_TIMER_MUX_TIMERA_MODE;
	अन्यथा
		val &= ~MESON_ISA_TIMER_MUX_TIMERA_MODE;

	ग_लिखोl(val | MESON_ISA_TIMER_MUX_TIMERA_EN,
	       समयr_base + MESON_ISA_TIMER_MUX);
पूर्ण

अटल पूर्णांक meson6_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	meson6_clkevt_समय_stop();
	वापस 0;
पूर्ण

अटल पूर्णांक meson6_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	meson6_clkevt_समय_stop();
	meson6_clkevt_समय_start(false);
	वापस 0;
पूर्ण

अटल पूर्णांक meson6_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	meson6_clkevt_समय_stop();
	meson6_clkevt_समय_setup(USEC_PER_SEC / HZ - 1);
	meson6_clkevt_समय_start(true);
	वापस 0;
पूर्ण

अटल पूर्णांक meson6_clkevt_next_event(अचिन्हित दीर्घ evt,
				    काष्ठा घड़ी_event_device *unused)
अणु
	meson6_clkevt_समय_stop();
	meson6_clkevt_समय_setup(evt);
	meson6_clkevt_समय_start(false);

	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device meson6_घड़ीevent = अणु
	.name			= "meson6_tick",
	.rating			= 400,
	.features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT,
	.set_state_shutकरोwn	= meson6_shutकरोwn,
	.set_state_periodic	= meson6_set_periodic,
	.set_state_oneshot	= meson6_set_oneshot,
	.tick_resume		= meson6_shutकरोwn,
	.set_next_event		= meson6_clkevt_next_event,
पूर्ण;

अटल irqवापस_t meson6_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = (काष्ठा घड़ी_event_device *)dev_id;

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init meson6_समयr_init(काष्ठा device_node *node)
अणु
	u32 val;
	पूर्णांक ret, irq;

	समयr_base = of_io_request_and_map(node, 0, "meson6-timer");
	अगर (IS_ERR(समयr_base)) अणु
		pr_err("Can't map registers\n");
		वापस -ENXIO;
	पूर्ण

	irq = irq_of_parse_and_map(node, 0);
	अगर (irq <= 0) अणु
		pr_err("Can't parse IRQ\n");
		वापस -EINVAL;
	पूर्ण

	/* Set 1us क्रम समयr E */
	val = पढ़ोl(समयr_base + MESON_ISA_TIMER_MUX);
	val &= ~MESON_ISA_TIMER_MUX_TIMERE_INPUT_CLOCK_MASK;
	val |= FIELD_PREP(MESON_ISA_TIMER_MUX_TIMERE_INPUT_CLOCK_MASK,
			  MESON_ISA_TIMER_MUX_TIMERE_INPUT_CLOCK_1US);
	ग_लिखोl(val, समयr_base + MESON_ISA_TIMER_MUX);

	sched_घड़ी_रेजिस्टर(meson6_समयr_sched_पढ़ो, 32, USEC_PER_SEC);
	घड़ीsource_mmio_init(समयr_base + MESON_ISA_TIMERE, node->name,
			      1000 * 1000, 300, 32, घड़ीsource_mmio_पढ़ोl_up);

	/* Timer A base 1us */
	val &= ~MESON_ISA_TIMER_MUX_TIMERA_INPUT_CLOCK_MASK;
	val |= FIELD_PREP(MESON_ISA_TIMER_MUX_TIMERA_INPUT_CLOCK_MASK,
			  MESON_ISA_TIMER_MUX_TIMERABCD_INPUT_CLOCK_1US);
	ग_लिखोl(val, समयr_base + MESON_ISA_TIMER_MUX);

	/* Stop the समयr A */
	meson6_clkevt_समय_stop();

	ret = request_irq(irq, meson6_समयr_पूर्णांकerrupt,
			  IRQF_TIMER | IRQF_IRQPOLL, "meson6_timer",
			  &meson6_घड़ीevent);
	अगर (ret) अणु
		pr_warn("failed to setup irq %d\n", irq);
		वापस ret;
	पूर्ण

	meson6_घड़ीevent.cpumask = cpu_possible_mask;
	meson6_घड़ीevent.irq = irq;

	घड़ीevents_config_and_रेजिस्टर(&meson6_घड़ीevent, USEC_PER_SEC,
					1, 0xfffe);

#अगर_घोषित CONFIG_ARM
	/* Also use MESON_ISA_TIMERE क्रम delays */
	रेजिस्टर_current_समयr_delay(&meson6_delay_समयr);
#पूर्ण_अगर

	वापस 0;
पूर्ण
TIMER_OF_DECLARE(meson6, "amlogic,meson6-timer",
		       meson6_समयr_init);
