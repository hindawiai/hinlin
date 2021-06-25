<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation
/*
 *  Andestech ATCPIT100 Timer Device Driver Implementation
 * Rick Chen, Andes Technology Corporation <rick@andestech.com>
 *
 */

#समावेश <linux/irq.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश "timer-of.h"
#अगर_घोषित CONFIG_NDS32
#समावेश <यंत्र/vdso_समयr_info.h>
#पूर्ण_अगर

/*
 * Definition of रेजिस्टर offsets
 */

/* ID and Revision Register */
#घोषणा ID_REV		0x0

/* Configuration Register */
#घोषणा CFG		0x10

/* Interrupt Enable Register */
#घोषणा INT_EN		0x14
#घोषणा CH_INT_EN(c, i)	((1<<i)<<(4*c))
#घोषणा CH0INT0EN	0x01

/* Interrupt Status Register */
#घोषणा INT_STA		0x18
#घोषणा CH0INT0		0x01

/* Channel Enable Register */
#घोषणा CH_EN		0x1C
#घोषणा CH0TMR0EN	0x1
#घोषणा CH1TMR0EN	0x10

/* Channel 0 , 1 Control Register */
#घोषणा CH0_CTL		(0x20)
#घोषणा CH1_CTL		(0x20 + 0x10)

/* Channel घड़ी source , bit 3 , 0:External घड़ी , 1:APB घड़ी */
#घोषणा APB_CLK		BIT(3)

/* Channel mode , bit 0~2 */
#घोषणा TMR_32		0x1
#घोषणा TMR_16		0x2
#घोषणा TMR_8		0x3

/* Channel 0 , 1 Reload Register */
#घोषणा CH0_REL		(0x24)
#घोषणा CH1_REL		(0x24 + 0x10)

/* Channel 0 , 1 Counter Register */
#घोषणा CH0_CNT		(0x28)
#घोषणा CH1_CNT		(0x28 + 0x10)

#घोषणा TIMER_SYNC_TICKS	3

अटल व्योम atcpit100_ch1_पंचांगr0_en(व्योम __iomem *base)
अणु
	ग_लिखोl(~0, base + CH1_REL);
	ग_लिखोl(APB_CLK|TMR_32, base + CH1_CTL);
पूर्ण

अटल व्योम atcpit100_ch0_पंचांगr0_en(व्योम __iomem *base)
अणु
	ग_लिखोl(APB_CLK|TMR_32, base + CH0_CTL);
पूर्ण

अटल व्योम atcpit100_clkevt_समय_setup(व्योम __iomem *base, अचिन्हित दीर्घ delay)
अणु
	ग_लिखोl(delay, base + CH0_CNT);
	ग_लिखोl(delay, base + CH0_REL);
पूर्ण

अटल व्योम atcpit100_समयr_clear_पूर्णांकerrupt(व्योम __iomem *base)
अणु
	u32 val;

	val = पढ़ोl(base + INT_STA);
	ग_लिखोl(val | CH0INT0, base + INT_STA);
पूर्ण

अटल व्योम atcpit100_घड़ीsource_start(व्योम __iomem *base)
अणु
	u32 val;

	val = पढ़ोl(base + CH_EN);
	ग_लिखोl(val | CH1TMR0EN, base + CH_EN);
पूर्ण

अटल व्योम atcpit100_clkevt_समय_start(व्योम __iomem *base)
अणु
	u32 val;

	val = पढ़ोl(base + CH_EN);
	ग_लिखोl(val | CH0TMR0EN, base + CH_EN);
पूर्ण

अटल व्योम atcpit100_clkevt_समय_stop(व्योम __iomem *base)
अणु
	u32 val;

	atcpit100_समयr_clear_पूर्णांकerrupt(base);
	val = पढ़ोl(base + CH_EN);
	ग_लिखोl(val & ~CH0TMR0EN, base + CH_EN);
पूर्ण

अटल पूर्णांक atcpit100_clkevt_next_event(अचिन्हित दीर्घ evt,
	काष्ठा घड़ी_event_device *clkevt)
अणु
	u32 val;
	काष्ठा समयr_of *to = to_समयr_of(clkevt);

	val = पढ़ोl(समयr_of_base(to) + CH_EN);
	ग_लिखोl(val & ~CH0TMR0EN, समयr_of_base(to) + CH_EN);
	ग_लिखोl(evt, समयr_of_base(to) + CH0_REL);
	ग_लिखोl(val | CH0TMR0EN, समयr_of_base(to) + CH_EN);

	वापस 0;
पूर्ण

अटल पूर्णांक atcpit100_clkevt_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(evt);

	atcpit100_clkevt_समय_setup(समयr_of_base(to), समयr_of_period(to));
	atcpit100_clkevt_समय_start(समयr_of_base(to));

	वापस 0;
पूर्ण
अटल पूर्णांक atcpit100_clkevt_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(evt);

	atcpit100_clkevt_समय_stop(समयr_of_base(to));

	वापस 0;
पूर्ण
अटल पूर्णांक atcpit100_clkevt_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(evt);
	u32 val;

	ग_लिखोl(~0x0, समयr_of_base(to) + CH0_REL);
	val = पढ़ोl(समयr_of_base(to) + CH_EN);
	ग_लिखोl(val | CH0TMR0EN, समयr_of_base(to) + CH_EN);

	वापस 0;
पूर्ण

अटल irqवापस_t atcpit100_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = (काष्ठा घड़ी_event_device *)dev_id;
	काष्ठा समयr_of *to = to_समयr_of(evt);

	atcpit100_समयr_clear_पूर्णांकerrupt(समयr_of_base(to));

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा समयr_of to = अणु
	.flags = TIMER_OF_IRQ | TIMER_OF_CLOCK | TIMER_OF_BASE,

	.clkevt = अणु
		.name = "atcpit100_tick",
		.rating = 300,
		.features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT,
		.set_state_shutकरोwn = atcpit100_clkevt_shutकरोwn,
		.set_state_periodic = atcpit100_clkevt_set_periodic,
		.set_state_oneshot = atcpit100_clkevt_set_oneshot,
		.tick_resume = atcpit100_clkevt_shutकरोwn,
		.set_next_event = atcpit100_clkevt_next_event,
		.cpumask = cpu_possible_mask,
	पूर्ण,

	.of_irq = अणु
		.handler = atcpit100_समयr_पूर्णांकerrupt,
		.flags = IRQF_TIMER | IRQF_IRQPOLL,
	पूर्ण,

	/*
	 * FIXME: we currently only support घड़ीing using PCLK
	 * and using EXTCLK is not supported in the driver.
	 */
	.of_clk = अणु
		.name = "PCLK",
	पूर्ण
पूर्ण;

अटल u64 notrace atcpit100_समयr_sched_पढ़ो(व्योम)
अणु
	वापस ~पढ़ोl(समयr_of_base(&to) + CH1_CNT);
पूर्ण

#अगर_घोषित CONFIG_NDS32
अटल व्योम fill_vdso_need_info(काष्ठा device_node *node)
अणु
	काष्ठा resource समयr_res;
	of_address_to_resource(node, 0, &समयr_res);
	समयr_info.mapping_base = (अचिन्हित दीर्घ)समयr_res.start;
	समयr_info.cycle_count_करोwn = true;
	समयr_info.cycle_count_reg_offset = CH1_CNT;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init atcpit100_समयr_init(काष्ठा device_node *node)
अणु
	पूर्णांक ret;
	u32 val;
	व्योम __iomem *base;

	ret = समयr_of_init(node, &to);
	अगर (ret)
		वापस ret;

	base = समयr_of_base(&to);

	sched_घड़ी_रेजिस्टर(atcpit100_समयr_sched_पढ़ो, 32,
		समयr_of_rate(&to));

	ret = घड़ीsource_mmio_init(base + CH1_CNT,
		node->name, समयr_of_rate(&to), 300, 32,
		घड़ीsource_mmio_पढ़ोl_करोwn);

	अगर (ret) अणु
		pr_err("Failed to register clocksource\n");
		वापस ret;
	पूर्ण

	/* clear channel 0 समयr0 पूर्णांकerrupt */
	atcpit100_समयr_clear_पूर्णांकerrupt(base);

	घड़ीevents_config_and_रेजिस्टर(&to.clkevt, समयr_of_rate(&to),
					TIMER_SYNC_TICKS, 0xffffffff);
	atcpit100_ch0_पंचांगr0_en(base);
	atcpit100_ch1_पंचांगr0_en(base);
	atcpit100_घड़ीsource_start(base);
	atcpit100_clkevt_समय_start(base);

	/* Enable channel 0 समयr0 पूर्णांकerrupt */
	val = पढ़ोl(base + INT_EN);
	ग_लिखोl(val | CH0INT0EN, base + INT_EN);

#अगर_घोषित CONFIG_NDS32
	fill_vdso_need_info(node);
#पूर्ण_अगर

	वापस ret;
पूर्ण

TIMER_OF_DECLARE(atcpit100, "andestech,atcpit100", atcpit100_समयr_init);
