<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  arch/arm/mach-vt8500/समयr.c
 *
 *  Copyright (C) 2012 Tony Prisk <linux@prisktech.co.nz>
 *  Copyright (C) 2010 Alexey Charkov <alअक्षरk@gmail.com>
 */

/*
 * This file is copied and modअगरied from the original समयr.c provided by
 * Alexey Charkov. Minor changes have been made क्रम Device Tree Support.
 */

#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/delay.h>

#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#घोषणा VT8500_TIMER_OFFSET	0x0100
#घोषणा VT8500_TIMER_HZ		3000000
#घोषणा TIMER_MATCH_VAL		0x0000
#घोषणा TIMER_COUNT_VAL		0x0010
#घोषणा TIMER_STATUS_VAL	0x0014
#घोषणा TIMER_IER_VAL		0x001c		/* पूर्णांकerrupt enable */
#घोषणा TIMER_CTRL_VAL		0x0020
#घोषणा TIMER_AS_VAL		0x0024		/* access status */
#घोषणा TIMER_COUNT_R_ACTIVE	(1 << 5)	/* not पढ़ोy क्रम पढ़ो */
#घोषणा TIMER_COUNT_W_ACTIVE	(1 << 4)	/* not पढ़ोy क्रम ग_लिखो */
#घोषणा TIMER_MATCH_W_ACTIVE	(1 << 0)	/* not पढ़ोy क्रम ग_लिखो */

#घोषणा msecs_to_loops(t) (loops_per_jअगरfy / 1000 * HZ * t)

#घोषणा MIN_OSCR_DELTA		16

अटल व्योम __iomem *regbase;

अटल u64 vt8500_समयr_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	पूर्णांक loops = msecs_to_loops(10);
	ग_लिखोl(3, regbase + TIMER_CTRL_VAL);
	जबतक ((पढ़ोl((regbase + TIMER_AS_VAL)) & TIMER_COUNT_R_ACTIVE)
						&& --loops)
		cpu_relax();
	वापस पढ़ोl(regbase + TIMER_COUNT_VAL);
पूर्ण

अटल काष्ठा घड़ीsource घड़ीsource = अणु
	.name           = "vt8500_timer",
	.rating         = 200,
	.पढ़ो           = vt8500_समयr_पढ़ो,
	.mask           = CLOCKSOURCE_MASK(32),
	.flags          = CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल पूर्णांक vt8500_समयr_set_next_event(अचिन्हित दीर्घ cycles,
				    काष्ठा घड़ी_event_device *evt)
अणु
	पूर्णांक loops = msecs_to_loops(10);
	u64 alarm = घड़ीsource.पढ़ो(&घड़ीsource) + cycles;
	जबतक ((पढ़ोl(regbase + TIMER_AS_VAL) & TIMER_MATCH_W_ACTIVE)
						&& --loops)
		cpu_relax();
	ग_लिखोl((अचिन्हित दीर्घ)alarm, regbase + TIMER_MATCH_VAL);

	अगर ((चिन्हित)(alarm - घड़ीsource.पढ़ो(&घड़ीsource)) <= MIN_OSCR_DELTA)
		वापस -ETIME;

	ग_लिखोl(1, regbase + TIMER_IER_VAL);

	वापस 0;
पूर्ण

अटल पूर्णांक vt8500_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	ग_लिखोl(पढ़ोl(regbase + TIMER_CTRL_VAL) | 1, regbase + TIMER_CTRL_VAL);
	ग_लिखोl(0, regbase + TIMER_IER_VAL);
	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device घड़ीevent = अणु
	.name			= "vt8500_timer",
	.features		= CLOCK_EVT_FEAT_ONESHOT,
	.rating			= 200,
	.set_next_event		= vt8500_समयr_set_next_event,
	.set_state_shutकरोwn	= vt8500_shutकरोwn,
	.set_state_oneshot	= vt8500_shutकरोwn,
पूर्ण;

अटल irqवापस_t vt8500_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;
	ग_लिखोl(0xf, regbase + TIMER_STATUS_VAL);
	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init vt8500_समयr_init(काष्ठा device_node *np)
अणु
	पूर्णांक समयr_irq, ret;

	regbase = of_iomap(np, 0);
	अगर (!regbase) अणु
		pr_err("%s: Missing iobase description in Device Tree\n",
								__func__);
		वापस -ENXIO;
	पूर्ण

	समयr_irq = irq_of_parse_and_map(np, 0);
	अगर (!समयr_irq) अणु
		pr_err("%s: Missing irq description in Device Tree\n",
								__func__);
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(1, regbase + TIMER_CTRL_VAL);
	ग_लिखोl(0xf, regbase + TIMER_STATUS_VAL);
	ग_लिखोl(~0, regbase + TIMER_MATCH_VAL);

	ret = घड़ीsource_रेजिस्टर_hz(&घड़ीsource, VT8500_TIMER_HZ);
	अगर (ret) अणु
		pr_err("%s: clocksource_register failed for %s\n",
		       __func__, घड़ीsource.name);
		वापस ret;
	पूर्ण

	घड़ीevent.cpumask = cpumask_of(0);

	ret = request_irq(समयr_irq, vt8500_समयr_पूर्णांकerrupt,
			  IRQF_TIMER | IRQF_IRQPOLL, "vt8500_timer",
			  &घड़ीevent);
	अगर (ret) अणु
		pr_err("%s: setup_irq failed for %s\n", __func__,
							घड़ीevent.name);
		वापस ret;
	पूर्ण

	घड़ीevents_config_and_रेजिस्टर(&घड़ीevent, VT8500_TIMER_HZ,
					MIN_OSCR_DELTA * 2, 0xf0000000);

	वापस 0;
पूर्ण

TIMER_OF_DECLARE(vt8500, "via,vt8500-timer", vt8500_समयr_init);
