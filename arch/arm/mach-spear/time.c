<शैली गुरु>
/*
 * arch/arm/plat-spear/समय.c
 *
 * Copyright (C) 2010 ST Microelectronics
 * Shiraz Hashim<shiraz.linux.kernel@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/समय.स>
#समावेश <linux/irq.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश "generic.h"

/*
 * We would use TIMER0 and TIMER1 as घड़ीevent and घड़ीsource.
 * Timer0 and Timer1 both beदीर्घ to same gpt block in cpu subbप्रणाली. Further
 * they share same functional घड़ी. Any change in one's functional घड़ी will
 * also affect other समयr.
 */

#घोषणा CLKEVT	0	/* gpt0, channel0 as घड़ीevent */
#घोषणा CLKSRC	1	/* gpt0, channel1 as घड़ीsource */

/* Register offsets, x is channel number */
#घोषणा CR(x)		((x) * 0x80 + 0x80)
#घोषणा IR(x)		((x) * 0x80 + 0x84)
#घोषणा LOAD(x)		((x) * 0x80 + 0x88)
#घोषणा COUNT(x)	((x) * 0x80 + 0x8C)

/* Reg bit definitions */
#घोषणा CTRL_INT_ENABLE		0x0100
#घोषणा CTRL_ENABLE		0x0020
#घोषणा CTRL_ONE_SHOT		0x0010

#घोषणा CTRL_PRESCALER1		0x0
#घोषणा CTRL_PRESCALER2		0x1
#घोषणा CTRL_PRESCALER4		0x2
#घोषणा CTRL_PRESCALER8		0x3
#घोषणा CTRL_PRESCALER16	0x4
#घोषणा CTRL_PRESCALER32	0x5
#घोषणा CTRL_PRESCALER64	0x6
#घोषणा CTRL_PRESCALER128	0x7
#घोषणा CTRL_PRESCALER256	0x8

#घोषणा INT_STATUS		0x1

/*
 * Minimum घड़ीsource/घड़ीevent समयr range in seconds
 */
#घोषणा SPEAR_MIN_RANGE 4

अटल __iomem व्योम *gpt_base;
अटल काष्ठा clk *gpt_clk;

अटल पूर्णांक घड़ीevent_next_event(अचिन्हित दीर्घ evt,
				 काष्ठा घड़ी_event_device *clk_event_dev);

अटल व्योम __init spear_घड़ीsource_init(व्योम)
अणु
	u32 tick_rate;
	u16 val;

	/* program the prescaler (/256)*/
	ग_लिखोw(CTRL_PRESCALER256, gpt_base + CR(CLKSRC));

	/* find out actual घड़ी driving Timer */
	tick_rate = clk_get_rate(gpt_clk);
	tick_rate >>= CTRL_PRESCALER256;

	ग_लिखोw(0xFFFF, gpt_base + LOAD(CLKSRC));

	val = पढ़ोw(gpt_base + CR(CLKSRC));
	val &= ~CTRL_ONE_SHOT;	/* स्वतःreload mode */
	val |= CTRL_ENABLE ;
	ग_लिखोw(val, gpt_base + CR(CLKSRC));

	/* रेजिस्टर the घड़ीsource */
	घड़ीsource_mmio_init(gpt_base + COUNT(CLKSRC), "tmr1", tick_rate,
		200, 16, घड़ीsource_mmio_पढ़ोw_up);
पूर्ण

अटल अंतरभूत व्योम समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	u16 val = पढ़ोw(gpt_base + CR(CLKEVT));

	/* stop the समयr */
	val &= ~CTRL_ENABLE;
	ग_लिखोw(val, gpt_base + CR(CLKEVT));
पूर्ण

अटल पूर्णांक spear_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	समयr_shutकरोwn(evt);

	वापस 0;
पूर्ण

अटल पूर्णांक spear_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	u16 val;

	/* stop the समयr */
	समयr_shutकरोwn(evt);

	val = पढ़ोw(gpt_base + CR(CLKEVT));
	val |= CTRL_ONE_SHOT;
	ग_लिखोw(val, gpt_base + CR(CLKEVT));

	वापस 0;
पूर्ण

अटल पूर्णांक spear_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	u32 period;
	u16 val;

	/* stop the समयr */
	समयr_shutकरोwn(evt);

	period = clk_get_rate(gpt_clk) / HZ;
	period >>= CTRL_PRESCALER16;
	ग_लिखोw(period, gpt_base + LOAD(CLKEVT));

	val = पढ़ोw(gpt_base + CR(CLKEVT));
	val &= ~CTRL_ONE_SHOT;
	val |= CTRL_ENABLE | CTRL_INT_ENABLE;
	ग_लिखोw(val, gpt_base + CR(CLKEVT));

	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device clkevt = अणु
	.name = "tmr0",
	.features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT,
	.set_state_shutकरोwn = spear_shutकरोwn,
	.set_state_periodic = spear_set_periodic,
	.set_state_oneshot = spear_set_oneshot,
	.tick_resume = spear_shutकरोwn,
	.set_next_event = घड़ीevent_next_event,
	.shअगरt = 0,	/* to be computed */
पूर्ण;

अटल पूर्णांक घड़ीevent_next_event(अचिन्हित दीर्घ cycles,
				 काष्ठा घड़ी_event_device *clk_event_dev)
अणु
	u16 val = पढ़ोw(gpt_base + CR(CLKEVT));

	अगर (val & CTRL_ENABLE)
		ग_लिखोw(val & ~CTRL_ENABLE, gpt_base + CR(CLKEVT));

	ग_लिखोw(cycles, gpt_base + LOAD(CLKEVT));

	val |= CTRL_ENABLE | CTRL_INT_ENABLE;
	ग_लिखोw(val, gpt_base + CR(CLKEVT));

	वापस 0;
पूर्ण

अटल irqवापस_t spear_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = &clkevt;

	ग_लिखोw(INT_STATUS, gpt_base + IR(CLKEVT));

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __init spear_घड़ीevent_init(पूर्णांक irq)
अणु
	u32 tick_rate;

	/* program the prescaler */
	ग_लिखोw(CTRL_PRESCALER16, gpt_base + CR(CLKEVT));

	tick_rate = clk_get_rate(gpt_clk);
	tick_rate >>= CTRL_PRESCALER16;

	clkevt.cpumask = cpumask_of(0);

	घड़ीevents_config_and_रेजिस्टर(&clkevt, tick_rate, 3, 0xfff0);

	अगर (request_irq(irq, spear_समयr_पूर्णांकerrupt, IRQF_TIMER, "timer", शून्य))
		pr_err("Failed to request irq %d (timer)\n", irq);
पूर्ण

अटल स्थिर काष्ठा of_device_id समयr_of_match[] __initस्थिर = अणु
	अणु .compatible = "st,spear-timer", पूर्ण,
	अणु पूर्ण,
पूर्ण;

व्योम __init spear_setup_of_समयr(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक irq, ret;

	np = of_find_matching_node(शून्य, समयr_of_match);
	अगर (!np) अणु
		pr_err("%s: No timer passed via DT\n", __func__);
		वापस;
	पूर्ण

	irq = irq_of_parse_and_map(np, 0);
	अगर (!irq) अणु
		pr_err("%s: No irq passed for timer via DT\n", __func__);
		वापस;
	पूर्ण

	gpt_base = of_iomap(np, 0);
	अगर (!gpt_base) अणु
		pr_err("%s: of iomap failed\n", __func__);
		वापस;
	पूर्ण

	gpt_clk = clk_get_sys("gpt0", शून्य);
	अगर (IS_ERR(gpt_clk)) अणु
		pr_err("%s:couldn't get clk for gpt\n", __func__);
		जाओ err_iomap;
	पूर्ण

	ret = clk_prepare_enable(gpt_clk);
	अगर (ret < 0) अणु
		pr_err("%s:couldn't prepare-enable gpt clock\n", __func__);
		जाओ err_prepare_enable_clk;
	पूर्ण

	spear_घड़ीevent_init(irq);
	spear_घड़ीsource_init();

	वापस;

err_prepare_enable_clk:
	clk_put(gpt_clk);
err_iomap:
	iounmap(gpt_base);
पूर्ण
