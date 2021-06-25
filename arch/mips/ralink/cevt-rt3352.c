<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2013 by John Crispin <john@phrozen.org>
 */

#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reset.h>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/mach-ralink/ralink_regs.h>

#घोषणा SYSTICK_FREQ		(50 * 1000)

#घोषणा SYSTICK_CONFIG		0x00
#घोषणा SYSTICK_COMPARE		0x04
#घोषणा SYSTICK_COUNT		0x08

/* route systick irq to mips irq 7 instead of the r4k-समयr */
#घोषणा CFG_EXT_STK_EN		0x2
/* enable the counter */
#घोषणा CFG_CNT_EN		0x1

काष्ठा systick_device अणु
	व्योम __iomem *membase;
	काष्ठा घड़ी_event_device dev;
	पूर्णांक irq_requested;
	पूर्णांक freq_scale;
पूर्ण;

अटल पूर्णांक systick_set_oneshot(काष्ठा घड़ी_event_device *evt);
अटल पूर्णांक systick_shutकरोwn(काष्ठा घड़ी_event_device *evt);

अटल पूर्णांक systick_next_event(अचिन्हित दीर्घ delta,
				काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा systick_device *sdev;
	u32 count;

	sdev = container_of(evt, काष्ठा systick_device, dev);
	count = ioपढ़ो32(sdev->membase + SYSTICK_COUNT);
	count = (count + delta) % SYSTICK_FREQ;
	ioग_लिखो32(count, sdev->membase + SYSTICK_COMPARE);

	वापस 0;
पूर्ण

अटल व्योम systick_event_handler(काष्ठा घड़ी_event_device *dev)
अणु
	/* noting to करो here */
पूर्ण

अटल irqवापस_t systick_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *dev = (काष्ठा घड़ी_event_device *) dev_id;

	dev->event_handler(dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा systick_device systick = अणु
	.dev = अणु
		/*
		 * cevt-r4k uses 300, make sure systick
		 * माला_लो used अगर available
		 */
		.rating			= 310,
		.features		= CLOCK_EVT_FEAT_ONESHOT,
		.set_next_event		= systick_next_event,
		.set_state_shutकरोwn	= systick_shutकरोwn,
		.set_state_oneshot	= systick_set_oneshot,
		.event_handler		= systick_event_handler,
	पूर्ण,
पूर्ण;

अटल पूर्णांक systick_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा systick_device *sdev;

	sdev = container_of(evt, काष्ठा systick_device, dev);

	अगर (sdev->irq_requested)
		मुक्त_irq(systick.dev.irq, &systick.dev);
	sdev->irq_requested = 0;
	ioग_लिखो32(0, systick.membase + SYSTICK_CONFIG);

	वापस 0;
पूर्ण

अटल पूर्णांक systick_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	स्थिर अक्षर *name = systick.dev.name;
	काष्ठा systick_device *sdev;
	पूर्णांक irq = systick.dev.irq;

	sdev = container_of(evt, काष्ठा systick_device, dev);

	अगर (!sdev->irq_requested) अणु
		अगर (request_irq(irq, systick_पूर्णांकerrupt,
				IRQF_PERCPU | IRQF_TIMER, name, &systick.dev))
			pr_err("Failed to request irq %d (%s)\n", irq, name);
	पूर्ण
	sdev->irq_requested = 1;
	ioग_लिखो32(CFG_EXT_STK_EN | CFG_CNT_EN,
		  systick.membase + SYSTICK_CONFIG);

	वापस 0;
पूर्ण

अटल पूर्णांक __init ralink_systick_init(काष्ठा device_node *np)
अणु
	पूर्णांक ret;

	systick.membase = of_iomap(np, 0);
	अगर (!systick.membase)
		वापस -ENXIO;

	systick.dev.name = np->name;
	घड़ीevents_calc_mult_shअगरt(&systick.dev, SYSTICK_FREQ, 60);
	systick.dev.max_delta_ns = घड़ीevent_delta2ns(0x7fff, &systick.dev);
	systick.dev.max_delta_ticks = 0x7fff;
	systick.dev.min_delta_ns = घड़ीevent_delta2ns(0x3, &systick.dev);
	systick.dev.min_delta_ticks = 0x3;
	systick.dev.irq = irq_of_parse_and_map(np, 0);
	अगर (!systick.dev.irq) अणु
		pr_err("%pOFn: request_irq failed", np);
		वापस -EINVAL;
	पूर्ण

	ret = घड़ीsource_mmio_init(systick.membase + SYSTICK_COUNT, np->name,
				    SYSTICK_FREQ, 301, 16,
				    घड़ीsource_mmio_पढ़ोl_up);
	अगर (ret)
		वापस ret;

	घड़ीevents_रेजिस्टर_device(&systick.dev);

	pr_info("%pOFn: running - mult: %d, shift: %d\n",
			np, systick.dev.mult, systick.dev.shअगरt);

	वापस 0;
पूर्ण

TIMER_OF_DECLARE(systick, "ralink,cevt-systick", ralink_systick_init);
