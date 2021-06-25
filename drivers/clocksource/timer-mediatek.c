<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Mediatek SoCs General-Purpose Timer handling.
 *
 * Copyright (C) 2014 Matthias Brugger
 *
 * Matthias Brugger <matthias.bgg@gmail.com>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/slab.h>
#समावेश "timer-of.h"

#घोषणा TIMER_CLK_EVT           (1)
#घोषणा TIMER_CLK_SRC           (2)

#घोषणा TIMER_SYNC_TICKS        (3)

/* gpt */
#घोषणा GPT_IRQ_EN_REG          0x00
#घोषणा GPT_IRQ_ENABLE(val)     BIT((val) - 1)
#घोषणा GPT_IRQ_ACK_REG	        0x08
#घोषणा GPT_IRQ_ACK(val)        BIT((val) - 1)

#घोषणा GPT_CTRL_REG(val)       (0x10 * (val))
#घोषणा GPT_CTRL_OP(val)        (((val) & 0x3) << 4)
#घोषणा GPT_CTRL_OP_ONESHOT     (0)
#घोषणा GPT_CTRL_OP_REPEAT      (1)
#घोषणा GPT_CTRL_OP_FREERUN     (3)
#घोषणा GPT_CTRL_CLEAR          (2)
#घोषणा GPT_CTRL_ENABLE         (1)
#घोषणा GPT_CTRL_DISABLE        (0)

#घोषणा GPT_CLK_REG(val)        (0x04 + (0x10 * (val)))
#घोषणा GPT_CLK_SRC(val)        (((val) & 0x1) << 4)
#घोषणा GPT_CLK_SRC_SYS13M      (0)
#घोषणा GPT_CLK_SRC_RTC32K      (1)
#घोषणा GPT_CLK_DIV1            (0x0)
#घोषणा GPT_CLK_DIV2            (0x1)

#घोषणा GPT_CNT_REG(val)        (0x08 + (0x10 * (val)))
#घोषणा GPT_CMP_REG(val)        (0x0C + (0x10 * (val)))

/* प्रणाली समयr */
#घोषणा SYST_BASE               (0x40)

#घोषणा SYST_CON                (SYST_BASE + 0x0)
#घोषणा SYST_VAL                (SYST_BASE + 0x4)

#घोषणा SYST_CON_REG(to)        (समयr_of_base(to) + SYST_CON)
#घोषणा SYST_VAL_REG(to)        (समयr_of_base(to) + SYST_VAL)

/*
 * SYST_CON_EN: Clock enable. Shall be set to
 *   - Start समयr countकरोwn.
 *   - Allow समयout ticks being updated.
 *   - Allow changing पूर्णांकerrupt functions.
 *
 * SYST_CON_IRQ_EN: Set to allow पूर्णांकerrupt.
 *
 * SYST_CON_IRQ_CLR: Set to clear पूर्णांकerrupt.
 */
#घोषणा SYST_CON_EN              BIT(0)
#घोषणा SYST_CON_IRQ_EN          BIT(1)
#घोषणा SYST_CON_IRQ_CLR         BIT(4)

अटल व्योम __iomem *gpt_sched_reg __पढ़ो_mostly;

अटल व्योम mtk_syst_ack_irq(काष्ठा समयr_of *to)
अणु
	/* Clear and disable पूर्णांकerrupt */
	ग_लिखोl(SYST_CON_IRQ_CLR | SYST_CON_EN, SYST_CON_REG(to));
पूर्ण

अटल irqवापस_t mtk_syst_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *clkevt = dev_id;
	काष्ठा समयr_of *to = to_समयr_of(clkevt);

	mtk_syst_ack_irq(to);
	clkevt->event_handler(clkevt);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mtk_syst_clkevt_next_event(अचिन्हित दीर्घ ticks,
				      काष्ठा घड़ी_event_device *clkevt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(clkevt);

	/* Enable घड़ी to allow समयout tick update later */
	ग_लिखोl(SYST_CON_EN, SYST_CON_REG(to));

	/*
	 * Write new समयout ticks. Timer shall start countकरोwn
	 * after समयout ticks are updated.
	 */
	ग_लिखोl(ticks, SYST_VAL_REG(to));

	/* Enable पूर्णांकerrupt */
	ग_लिखोl(SYST_CON_EN | SYST_CON_IRQ_EN, SYST_CON_REG(to));

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_syst_clkevt_shutकरोwn(काष्ठा घड़ी_event_device *clkevt)
अणु
	/* Disable समयr */
	ग_लिखोl(0, SYST_CON_REG(to_समयr_of(clkevt)));

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_syst_clkevt_resume(काष्ठा घड़ी_event_device *clkevt)
अणु
	वापस mtk_syst_clkevt_shutकरोwn(clkevt);
पूर्ण

अटल पूर्णांक mtk_syst_clkevt_oneshot(काष्ठा घड़ी_event_device *clkevt)
अणु
	वापस 0;
पूर्ण

अटल u64 notrace mtk_gpt_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस पढ़ोl_relaxed(gpt_sched_reg);
पूर्ण

अटल व्योम mtk_gpt_clkevt_समय_stop(काष्ठा समयr_of *to, u8 समयr)
अणु
	u32 val;

	val = पढ़ोl(समयr_of_base(to) + GPT_CTRL_REG(समयr));
	ग_लिखोl(val & ~GPT_CTRL_ENABLE, समयr_of_base(to) +
	       GPT_CTRL_REG(समयr));
पूर्ण

अटल व्योम mtk_gpt_clkevt_समय_setup(काष्ठा समयr_of *to,
				      अचिन्हित दीर्घ delay, u8 समयr)
अणु
	ग_लिखोl(delay, समयr_of_base(to) + GPT_CMP_REG(समयr));
पूर्ण

अटल व्योम mtk_gpt_clkevt_समय_start(काष्ठा समयr_of *to,
				      bool periodic, u8 समयr)
अणु
	u32 val;

	/* Acknowledge पूर्णांकerrupt */
	ग_लिखोl(GPT_IRQ_ACK(समयr), समयr_of_base(to) + GPT_IRQ_ACK_REG);

	val = पढ़ोl(समयr_of_base(to) + GPT_CTRL_REG(समयr));

	/* Clear 2 bit समयr operation mode field */
	val &= ~GPT_CTRL_OP(0x3);

	अगर (periodic)
		val |= GPT_CTRL_OP(GPT_CTRL_OP_REPEAT);
	अन्यथा
		val |= GPT_CTRL_OP(GPT_CTRL_OP_ONESHOT);

	ग_लिखोl(val | GPT_CTRL_ENABLE | GPT_CTRL_CLEAR,
	       समयr_of_base(to) + GPT_CTRL_REG(समयr));
पूर्ण

अटल पूर्णांक mtk_gpt_clkevt_shutकरोwn(काष्ठा घड़ी_event_device *clk)
अणु
	mtk_gpt_clkevt_समय_stop(to_समयr_of(clk), TIMER_CLK_EVT);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_gpt_clkevt_set_periodic(काष्ठा घड़ी_event_device *clk)
अणु
	काष्ठा समयr_of *to = to_समयr_of(clk);

	mtk_gpt_clkevt_समय_stop(to, TIMER_CLK_EVT);
	mtk_gpt_clkevt_समय_setup(to, to->of_clk.period, TIMER_CLK_EVT);
	mtk_gpt_clkevt_समय_start(to, true, TIMER_CLK_EVT);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_gpt_clkevt_next_event(अचिन्हित दीर्घ event,
				     काष्ठा घड़ी_event_device *clk)
अणु
	काष्ठा समयr_of *to = to_समयr_of(clk);

	mtk_gpt_clkevt_समय_stop(to, TIMER_CLK_EVT);
	mtk_gpt_clkevt_समय_setup(to, event, TIMER_CLK_EVT);
	mtk_gpt_clkevt_समय_start(to, false, TIMER_CLK_EVT);

	वापस 0;
पूर्ण

अटल irqवापस_t mtk_gpt_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *clkevt = (काष्ठा घड़ी_event_device *)dev_id;
	काष्ठा समयr_of *to = to_समयr_of(clkevt);

	/* Acknowledge समयr0 irq */
	ग_लिखोl(GPT_IRQ_ACK(TIMER_CLK_EVT), समयr_of_base(to) + GPT_IRQ_ACK_REG);
	clkevt->event_handler(clkevt);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम
__init mtk_gpt_setup(काष्ठा समयr_of *to, u8 समयr, u8 option)
अणु
	ग_लिखोl(GPT_CTRL_CLEAR | GPT_CTRL_DISABLE,
	       समयr_of_base(to) + GPT_CTRL_REG(समयr));

	ग_लिखोl(GPT_CLK_SRC(GPT_CLK_SRC_SYS13M) | GPT_CLK_DIV1,
	       समयr_of_base(to) + GPT_CLK_REG(समयr));

	ग_लिखोl(0x0, समयr_of_base(to) + GPT_CMP_REG(समयr));

	ग_लिखोl(GPT_CTRL_OP(option) | GPT_CTRL_ENABLE,
	       समयr_of_base(to) + GPT_CTRL_REG(समयr));
पूर्ण

अटल व्योम mtk_gpt_enable_irq(काष्ठा समयr_of *to, u8 समयr)
अणु
	u32 val;

	/* Disable all पूर्णांकerrupts */
	ग_लिखोl(0x0, समयr_of_base(to) + GPT_IRQ_EN_REG);

	/* Acknowledge all spurious pending पूर्णांकerrupts */
	ग_लिखोl(0x3f, समयr_of_base(to) + GPT_IRQ_ACK_REG);

	val = पढ़ोl(समयr_of_base(to) + GPT_IRQ_EN_REG);
	ग_लिखोl(val | GPT_IRQ_ENABLE(समयr),
	       समयr_of_base(to) + GPT_IRQ_EN_REG);
पूर्ण

अटल काष्ठा समयr_of to = अणु
	.flags = TIMER_OF_IRQ | TIMER_OF_BASE | TIMER_OF_CLOCK,

	.clkevt = अणु
		.name = "mtk-clkevt",
		.rating = 300,
		.cpumask = cpu_possible_mask,
	पूर्ण,

	.of_irq = अणु
		.flags = IRQF_TIMER | IRQF_IRQPOLL,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mtk_syst_init(काष्ठा device_node *node)
अणु
	पूर्णांक ret;

	to.clkevt.features = CLOCK_EVT_FEAT_DYNIRQ | CLOCK_EVT_FEAT_ONESHOT;
	to.clkevt.set_state_shutकरोwn = mtk_syst_clkevt_shutकरोwn;
	to.clkevt.set_state_oneshot = mtk_syst_clkevt_oneshot;
	to.clkevt.tick_resume = mtk_syst_clkevt_resume;
	to.clkevt.set_next_event = mtk_syst_clkevt_next_event;
	to.of_irq.handler = mtk_syst_handler;

	ret = समयr_of_init(node, &to);
	अगर (ret)
		वापस ret;

	घड़ीevents_config_and_रेजिस्टर(&to.clkevt, समयr_of_rate(&to),
					TIMER_SYNC_TICKS, 0xffffffff);

	वापस 0;
पूर्ण

अटल पूर्णांक __init mtk_gpt_init(काष्ठा device_node *node)
अणु
	पूर्णांक ret;

	to.clkevt.features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT;
	to.clkevt.set_state_shutकरोwn = mtk_gpt_clkevt_shutकरोwn;
	to.clkevt.set_state_periodic = mtk_gpt_clkevt_set_periodic;
	to.clkevt.set_state_oneshot = mtk_gpt_clkevt_shutकरोwn;
	to.clkevt.tick_resume = mtk_gpt_clkevt_shutकरोwn;
	to.clkevt.set_next_event = mtk_gpt_clkevt_next_event;
	to.of_irq.handler = mtk_gpt_पूर्णांकerrupt;

	ret = समयr_of_init(node, &to);
	अगर (ret)
		वापस ret;

	/* Configure घड़ी source */
	mtk_gpt_setup(&to, TIMER_CLK_SRC, GPT_CTRL_OP_FREERUN);
	घड़ीsource_mmio_init(समयr_of_base(&to) + GPT_CNT_REG(TIMER_CLK_SRC),
			      node->name, समयr_of_rate(&to), 300, 32,
			      घड़ीsource_mmio_पढ़ोl_up);
	gpt_sched_reg = समयr_of_base(&to) + GPT_CNT_REG(TIMER_CLK_SRC);
	sched_घड़ी_रेजिस्टर(mtk_gpt_पढ़ो_sched_घड़ी, 32, समयr_of_rate(&to));

	/* Configure घड़ी event */
	mtk_gpt_setup(&to, TIMER_CLK_EVT, GPT_CTRL_OP_REPEAT);
	घड़ीevents_config_and_रेजिस्टर(&to.clkevt, समयr_of_rate(&to),
					TIMER_SYNC_TICKS, 0xffffffff);

	mtk_gpt_enable_irq(&to, TIMER_CLK_EVT);

	वापस 0;
पूर्ण
TIMER_OF_DECLARE(mtk_mt6577, "mediatek,mt6577-timer", mtk_gpt_init);
TIMER_OF_DECLARE(mtk_mt6765, "mediatek,mt6765-timer", mtk_syst_init);
