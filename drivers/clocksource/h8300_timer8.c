<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/h8300/kernel/cpu/समयr/समयr8.c
 *
 *  Yoshinori Sato <ysato@users.sourcefoge.jp>
 *
 *  8bit Timer driver
 *
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#घोषणा _8TCR	0
#घोषणा _8TCSR	2
#घोषणा TCORA	4
#घोषणा TCORB	6
#घोषणा _8TCNT	8

#घोषणा CMIEA	6
#घोषणा CMFA	6

#घोषणा FLAG_STARTED (1 << 3)

#घोषणा SCALE 64

#घोषणा bset(b, a) ioग_लिखो8(ioपढ़ो8(a) | (1 << (b)), (a))
#घोषणा bclr(b, a) ioग_लिखो8(ioपढ़ो8(a) & ~(1 << (b)), (a))

काष्ठा समयr8_priv अणु
	काष्ठा घड़ी_event_device ced;
	व्योम __iomem *mapbase;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक rate;
पूर्ण;

अटल irqवापस_t समयr8_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा समयr8_priv *p = dev_id;

	अगर (घड़ीevent_state_oneshot(&p->ced))
		ioग_लिखो16be(0x0000, p->mapbase + _8TCR);

	p->ced.event_handler(&p->ced);

	bclr(CMFA, p->mapbase + _8TCSR);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम समयr8_set_next(काष्ठा समयr8_priv *p, अचिन्हित दीर्घ delta)
अणु
	अगर (delta >= 0x10000)
		pr_warn("delta out of range\n");
	bclr(CMIEA, p->mapbase + _8TCR);
	ioग_लिखो16be(delta, p->mapbase + TCORA);
	ioग_लिखो16be(0x0000, p->mapbase + _8TCNT);
	bclr(CMFA, p->mapbase + _8TCSR);
	bset(CMIEA, p->mapbase + _8TCR);
पूर्ण

अटल पूर्णांक समयr8_enable(काष्ठा समयr8_priv *p)
अणु
	ioग_लिखो16be(0xffff, p->mapbase + TCORA);
	ioग_लिखो16be(0x0000, p->mapbase + _8TCNT);
	ioग_लिखो16be(0x0c02, p->mapbase + _8TCR);

	वापस 0;
पूर्ण

अटल पूर्णांक समयr8_start(काष्ठा समयr8_priv *p)
अणु
	पूर्णांक ret;

	अगर ((p->flags & FLAG_STARTED))
		वापस 0;

	ret = समयr8_enable(p);
	अगर (!ret)
		p->flags |= FLAG_STARTED;

	वापस ret;
पूर्ण

अटल व्योम समयr8_stop(काष्ठा समयr8_priv *p)
अणु
	ioग_लिखो16be(0x0000, p->mapbase + _8TCR);
पूर्ण

अटल अंतरभूत काष्ठा समयr8_priv *ced_to_priv(काष्ठा घड़ी_event_device *ced)
अणु
	वापस container_of(ced, काष्ठा समयr8_priv, ced);
पूर्ण

अटल व्योम समयr8_घड़ी_event_start(काष्ठा समयr8_priv *p, अचिन्हित दीर्घ delta)
अणु
	समयr8_start(p);
	समयr8_set_next(p, delta);
पूर्ण

अटल पूर्णांक समयr8_घड़ी_event_shutकरोwn(काष्ठा घड़ी_event_device *ced)
अणु
	समयr8_stop(ced_to_priv(ced));
	वापस 0;
पूर्ण

अटल पूर्णांक समयr8_घड़ी_event_periodic(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा समयr8_priv *p = ced_to_priv(ced);

	pr_info("%s: used for periodic clock events\n", ced->name);
	समयr8_stop(p);
	समयr8_घड़ी_event_start(p, (p->rate + HZ/2) / HZ);

	वापस 0;
पूर्ण

अटल पूर्णांक समयr8_घड़ी_event_oneshot(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा समयr8_priv *p = ced_to_priv(ced);

	pr_info("%s: used for oneshot clock events\n", ced->name);
	समयr8_stop(p);
	समयr8_घड़ी_event_start(p, 0x10000);

	वापस 0;
पूर्ण

अटल पूर्णांक समयr8_घड़ी_event_next(अचिन्हित दीर्घ delta,
				   काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा समयr8_priv *p = ced_to_priv(ced);

	BUG_ON(!घड़ीevent_state_oneshot(ced));
	समयr8_set_next(p, delta - 1);

	वापस 0;
पूर्ण

अटल काष्ठा समयr8_priv समयr8_priv = अणु
	.ced = अणु
		.name = "h8300_8timer",
		.features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT,
		.rating = 200,
		.set_next_event = समयr8_घड़ी_event_next,
		.set_state_shutकरोwn = समयr8_घड़ी_event_shutकरोwn,
		.set_state_periodic = समयr8_घड़ी_event_periodic,
		.set_state_oneshot = समयr8_घड़ी_event_oneshot,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init h8300_8समयr_init(काष्ठा device_node *node)
अणु
	व्योम __iomem *base;
	पूर्णांक irq, ret;
	काष्ठा clk *clk;

	clk = of_clk_get(node, 0);
	अगर (IS_ERR(clk)) अणु
		pr_err("failed to get clock for clockevent\n");
		वापस PTR_ERR(clk);
	पूर्ण

	ret = -ENXIO;
	base = of_iomap(node, 0);
	अगर (!base) अणु
		pr_err("failed to map registers for clockevent\n");
		जाओ मुक्त_clk;
	पूर्ण

	ret = -EINVAL;
	irq = irq_of_parse_and_map(node, 0);
	अगर (!irq) अणु
		pr_err("failed to get irq for clockevent\n");
		जाओ unmap_reg;
	पूर्ण

	समयr8_priv.mapbase = base;

	समयr8_priv.rate = clk_get_rate(clk) / SCALE;
	अगर (!समयr8_priv.rate) अणु
		pr_err("Failed to get rate for the clocksource\n");
		जाओ unmap_reg;
	पूर्ण

	अगर (request_irq(irq, समयr8_पूर्णांकerrupt, IRQF_TIMER,
			समयr8_priv.ced.name, &समयr8_priv) < 0) अणु
		pr_err("failed to request irq %d for clockevent\n", irq);
		जाओ unmap_reg;
	पूर्ण

	घड़ीevents_config_and_रेजिस्टर(&समयr8_priv.ced,
					समयr8_priv.rate, 1, 0x0000ffff);

	वापस 0;
unmap_reg:
	iounmap(base);
मुक्त_clk:
	clk_put(clk);
	वापस ret;
पूर्ण

TIMER_OF_DECLARE(h8300_8bit, "renesas,8bit-timer", h8300_8समयr_init);
