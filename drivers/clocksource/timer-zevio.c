<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/घड़ीsource/zevio-समयr.c
 *
 *  Copyright (C) 2013 Daniel Tang <tangrs@tangrs.id.au>
 */

#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>

#घोषणा IO_CURRENT_VAL	0x00
#घोषणा IO_DIVIDER	0x04
#घोषणा IO_CONTROL	0x08

#घोषणा IO_TIMER1	0x00
#घोषणा IO_TIMER2	0x0C

#घोषणा IO_MATCH_BEGIN	0x18
#घोषणा IO_MATCH(x)	(IO_MATCH_BEGIN + ((x) << 2))

#घोषणा IO_INTR_STS	0x00
#घोषणा IO_INTR_ACK	0x00
#घोषणा IO_INTR_MSK	0x04

#घोषणा CNTL_STOP_TIMER	(1 << 4)
#घोषणा CNTL_RUN_TIMER	(0 << 4)

#घोषणा CNTL_INC	(1 << 3)
#घोषणा CNTL_DEC	(0 << 3)

#घोषणा CNTL_TOZERO	0
#घोषणा CNTL_MATCH(x)	((x) + 1)
#घोषणा CNTL_FOREVER	7

/* There are 6 match रेजिस्टरs but we only use one. */
#घोषणा TIMER_MATCH	0

#घोषणा TIMER_INTR_MSK	(1 << (TIMER_MATCH))
#घोषणा TIMER_INTR_ALL	0x3F

काष्ठा zevio_समयr अणु
	व्योम __iomem *base;
	व्योम __iomem *समयr1, *समयr2;
	व्योम __iomem *पूर्णांकerrupt_regs;

	काष्ठा clk *clk;
	काष्ठा घड़ी_event_device clkevt;

	अक्षर घड़ीsource_name[64];
	अक्षर घड़ीevent_name[64];
पूर्ण;

अटल पूर्णांक zevio_समयr_set_event(अचिन्हित दीर्घ delta,
				 काष्ठा घड़ी_event_device *dev)
अणु
	काष्ठा zevio_समयr *समयr = container_of(dev, काष्ठा zevio_समयr,
						 clkevt);

	ग_लिखोl(delta, समयr->समयr1 + IO_CURRENT_VAL);
	ग_लिखोl(CNTL_RUN_TIMER | CNTL_DEC | CNTL_MATCH(TIMER_MATCH),
			समयr->समयr1 + IO_CONTROL);

	वापस 0;
पूर्ण

अटल पूर्णांक zevio_समयr_shutकरोwn(काष्ठा घड़ी_event_device *dev)
अणु
	काष्ठा zevio_समयr *समयr = container_of(dev, काष्ठा zevio_समयr,
						 clkevt);

	/* Disable समयr पूर्णांकerrupts */
	ग_लिखोl(0, समयr->पूर्णांकerrupt_regs + IO_INTR_MSK);
	ग_लिखोl(TIMER_INTR_ALL, समयr->पूर्णांकerrupt_regs + IO_INTR_ACK);
	/* Stop समयr */
	ग_लिखोl(CNTL_STOP_TIMER, समयr->समयr1 + IO_CONTROL);
	वापस 0;
पूर्ण

अटल पूर्णांक zevio_समयr_set_oneshot(काष्ठा घड़ी_event_device *dev)
अणु
	काष्ठा zevio_समयr *समयr = container_of(dev, काष्ठा zevio_समयr,
						 clkevt);

	/* Enable समयr पूर्णांकerrupts */
	ग_लिखोl(TIMER_INTR_MSK, समयr->पूर्णांकerrupt_regs + IO_INTR_MSK);
	ग_लिखोl(TIMER_INTR_ALL, समयr->पूर्णांकerrupt_regs + IO_INTR_ACK);
	वापस 0;
पूर्ण

अटल irqवापस_t zevio_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा zevio_समयr *समयr = dev_id;
	u32 पूर्णांकr;

	पूर्णांकr = पढ़ोl(समयr->पूर्णांकerrupt_regs + IO_INTR_ACK);
	अगर (!(पूर्णांकr & TIMER_INTR_MSK))
		वापस IRQ_NONE;

	ग_लिखोl(TIMER_INTR_MSK, समयr->पूर्णांकerrupt_regs + IO_INTR_ACK);
	ग_लिखोl(CNTL_STOP_TIMER, समयr->समयr1 + IO_CONTROL);

	अगर (समयr->clkevt.event_handler)
		समयr->clkevt.event_handler(&समयr->clkevt);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init zevio_समयr_add(काष्ठा device_node *node)
अणु
	काष्ठा zevio_समयr *समयr;
	काष्ठा resource res;
	पूर्णांक irqnr, ret;

	समयr = kzalloc(माप(*समयr), GFP_KERNEL);
	अगर (!समयr)
		वापस -ENOMEM;

	समयr->base = of_iomap(node, 0);
	अगर (!समयr->base) अणु
		ret = -EINVAL;
		जाओ error_मुक्त;
	पूर्ण
	समयr->समयr1 = समयr->base + IO_TIMER1;
	समयr->समयr2 = समयr->base + IO_TIMER2;

	समयr->clk = of_clk_get(node, 0);
	अगर (IS_ERR(समयr->clk)) अणु
		ret = PTR_ERR(समयr->clk);
		pr_err("Timer clock not found! (error %d)\n", ret);
		जाओ error_unmap;
	पूर्ण

	समयr->पूर्णांकerrupt_regs = of_iomap(node, 1);
	irqnr = irq_of_parse_and_map(node, 0);

	of_address_to_resource(node, 0, &res);
	scnम_लिखो(समयr->घड़ीsource_name, माप(समयr->घड़ीsource_name),
			"%llx.%pOFn_clocksource",
			(अचिन्हित दीर्घ दीर्घ)res.start, node);

	scnम_लिखो(समयr->घड़ीevent_name, माप(समयr->घड़ीevent_name),
			"%llx.%pOFn_clockevent",
			(अचिन्हित दीर्घ दीर्घ)res.start, node);

	अगर (समयr->पूर्णांकerrupt_regs && irqnr) अणु
		समयr->clkevt.name		= समयr->घड़ीevent_name;
		समयr->clkevt.set_next_event	= zevio_समयr_set_event;
		समयr->clkevt.set_state_shutकरोwn = zevio_समयr_shutकरोwn;
		समयr->clkevt.set_state_oneshot = zevio_समयr_set_oneshot;
		समयr->clkevt.tick_resume	= zevio_समयr_set_oneshot;
		समयr->clkevt.rating		= 200;
		समयr->clkevt.cpumask		= cpu_possible_mask;
		समयr->clkevt.features		= CLOCK_EVT_FEAT_ONESHOT;
		समयr->clkevt.irq		= irqnr;

		ग_लिखोl(CNTL_STOP_TIMER, समयr->समयr1 + IO_CONTROL);
		ग_लिखोl(0, समयr->समयr1 + IO_DIVIDER);

		/* Start with समयr पूर्णांकerrupts disabled */
		ग_लिखोl(0, समयr->पूर्णांकerrupt_regs + IO_INTR_MSK);
		ग_लिखोl(TIMER_INTR_ALL, समयr->पूर्णांकerrupt_regs + IO_INTR_ACK);

		/* Interrupt to occur when समयr value matches 0 */
		ग_लिखोl(0, समयr->base + IO_MATCH(TIMER_MATCH));

		अगर (request_irq(irqnr, zevio_समयr_पूर्णांकerrupt,
				IRQF_TIMER | IRQF_IRQPOLL,
				समयr->घड़ीevent_name, समयr)) अणु
			pr_err("%s: request_irq() failed\n",
			       समयr->घड़ीevent_name);
		पूर्ण

		घड़ीevents_config_and_रेजिस्टर(&समयr->clkevt,
				clk_get_rate(समयr->clk), 0x0001, 0xffff);
		pr_info("Added %s as clockevent\n", समयr->घड़ीevent_name);
	पूर्ण

	ग_लिखोl(CNTL_STOP_TIMER, समयr->समयr2 + IO_CONTROL);
	ग_लिखोl(0, समयr->समयr2 + IO_CURRENT_VAL);
	ग_लिखोl(0, समयr->समयr2 + IO_DIVIDER);
	ग_लिखोl(CNTL_RUN_TIMER | CNTL_FOREVER | CNTL_INC,
			समयr->समयr2 + IO_CONTROL);

	घड़ीsource_mmio_init(समयr->समयr2 + IO_CURRENT_VAL,
			समयr->घड़ीsource_name,
			clk_get_rate(समयr->clk),
			200, 16,
			घड़ीsource_mmio_पढ़ोw_up);

	pr_info("Added %s as clocksource\n", समयr->घड़ीsource_name);

	वापस 0;
error_unmap:
	iounmap(समयr->base);
error_मुक्त:
	kमुक्त(समयr);
	वापस ret;
पूर्ण

अटल पूर्णांक __init zevio_समयr_init(काष्ठा device_node *node)
अणु
	वापस zevio_समयr_add(node);
पूर्ण

TIMER_OF_DECLARE(zevio_समयr, "lsi,zevio-timer", zevio_समयr_init);
