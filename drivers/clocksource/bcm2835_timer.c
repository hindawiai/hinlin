<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2012 Simon Arlott
 */

#समावेश <linux/bitops.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched_घड़ी.h>

#समावेश <यंत्र/irq.h>

#घोषणा REG_CONTROL	0x00
#घोषणा REG_COUNTER_LO	0x04
#घोषणा REG_COUNTER_HI	0x08
#घोषणा REG_COMPARE(n)	(0x0c + (n) * 4)
#घोषणा MAX_TIMER	3
#घोषणा DEFAULT_TIMER	3

काष्ठा bcm2835_समयr अणु
	व्योम __iomem *control;
	व्योम __iomem *compare;
	पूर्णांक match_mask;
	काष्ठा घड़ी_event_device evt;
पूर्ण;

अटल व्योम __iomem *प्रणाली_घड़ी __पढ़ो_mostly;

अटल u64 notrace bcm2835_sched_पढ़ो(व्योम)
अणु
	वापस पढ़ोl_relaxed(प्रणाली_घड़ी);
पूर्ण

अटल पूर्णांक bcm2835_समय_set_next_event(अचिन्हित दीर्घ event,
	काष्ठा घड़ी_event_device *evt_dev)
अणु
	काष्ठा bcm2835_समयr *समयr = container_of(evt_dev,
		काष्ठा bcm2835_समयr, evt);
	ग_लिखोl_relaxed(पढ़ोl_relaxed(प्रणाली_घड़ी) + event,
		समयr->compare);
	वापस 0;
पूर्ण

अटल irqवापस_t bcm2835_समय_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcm2835_समयr *समयr = dev_id;
	व्योम (*event_handler)(काष्ठा घड़ी_event_device *);
	अगर (पढ़ोl_relaxed(समयr->control) & समयr->match_mask) अणु
		ग_लिखोl_relaxed(समयr->match_mask, समयr->control);

		event_handler = READ_ONCE(समयr->evt.event_handler);
		अगर (event_handler)
			event_handler(&समयr->evt);
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अणु
		वापस IRQ_NONE;
	पूर्ण
पूर्ण

अटल पूर्णांक __init bcm2835_समयr_init(काष्ठा device_node *node)
अणु
	व्योम __iomem *base;
	u32 freq;
	पूर्णांक irq, ret;
	काष्ठा bcm2835_समयr *समयr;

	base = of_iomap(node, 0);
	अगर (!base) अणु
		pr_err("Can't remap registers\n");
		वापस -ENXIO;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "clock-frequency", &freq);
	अगर (ret) अणु
		pr_err("Can't read clock-frequency\n");
		जाओ err_iounmap;
	पूर्ण

	प्रणाली_घड़ी = base + REG_COUNTER_LO;
	sched_घड़ी_रेजिस्टर(bcm2835_sched_पढ़ो, 32, freq);

	घड़ीsource_mmio_init(base + REG_COUNTER_LO, node->name,
		freq, 300, 32, घड़ीsource_mmio_पढ़ोl_up);

	irq = irq_of_parse_and_map(node, DEFAULT_TIMER);
	अगर (irq <= 0) अणु
		pr_err("Can't parse IRQ\n");
		ret = -EINVAL;
		जाओ err_iounmap;
	पूर्ण

	समयr = kzalloc(माप(*समयr), GFP_KERNEL);
	अगर (!समयr) अणु
		ret = -ENOMEM;
		जाओ err_iounmap;
	पूर्ण

	समयr->control = base + REG_CONTROL;
	समयr->compare = base + REG_COMPARE(DEFAULT_TIMER);
	समयr->match_mask = BIT(DEFAULT_TIMER);
	समयr->evt.name = node->name;
	समयr->evt.rating = 300;
	समयr->evt.features = CLOCK_EVT_FEAT_ONESHOT;
	समयr->evt.set_next_event = bcm2835_समय_set_next_event;
	समयr->evt.cpumask = cpumask_of(0);

	ret = request_irq(irq, bcm2835_समय_पूर्णांकerrupt, IRQF_TIMER | IRQF_SHARED,
			  node->name, समयr);
	अगर (ret) अणु
		pr_err("Can't set up timer IRQ\n");
		जाओ err_समयr_मुक्त;
	पूर्ण

	घड़ीevents_config_and_रेजिस्टर(&समयr->evt, freq, 0xf, 0xffffffff);

	pr_info("bcm2835: system timer (irq = %d)\n", irq);

	वापस 0;

err_समयr_मुक्त:
	kमुक्त(समयr);

err_iounmap:
	iounmap(base);
	वापस ret;
पूर्ण
TIMER_OF_DECLARE(bcm2835, "brcm,bcm2835-system-timer",
			bcm2835_समयr_init);
