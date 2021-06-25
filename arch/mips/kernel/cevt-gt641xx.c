<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  GT641xx घड़ीevent routines.
 *
 *  Copyright (C) 2007	Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/gt64120.h>
#समावेश <यंत्र/समय.स>

अटल DEFINE_RAW_SPINLOCK(gt641xx_समयr_lock);
अटल अचिन्हित पूर्णांक gt641xx_base_घड़ी;

व्योम gt641xx_set_base_घड़ी(अचिन्हित पूर्णांक घड़ी)
अणु
	gt641xx_base_घड़ी = घड़ी;
पूर्ण

पूर्णांक gt641xx_समयr0_state(व्योम)
अणु
	अगर (GT_READ(GT_TC0_OFS))
		वापस 0;

	GT_WRITE(GT_TC0_OFS, gt641xx_base_घड़ी / HZ);
	GT_WRITE(GT_TC_CONTROL_OFS, GT_TC_CONTROL_ENTC0_MSK);

	वापस 1;
पूर्ण

अटल पूर्णांक gt641xx_समयr0_set_next_event(अचिन्हित दीर्घ delta,
					 काष्ठा घड़ी_event_device *evt)
अणु
	u32 ctrl;

	raw_spin_lock(&gt641xx_समयr_lock);

	ctrl = GT_READ(GT_TC_CONTROL_OFS);
	ctrl &= ~(GT_TC_CONTROL_ENTC0_MSK | GT_TC_CONTROL_SELTC0_MSK);
	ctrl |= GT_TC_CONTROL_ENTC0_MSK;

	GT_WRITE(GT_TC0_OFS, delta);
	GT_WRITE(GT_TC_CONTROL_OFS, ctrl);

	raw_spin_unlock(&gt641xx_समयr_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक gt641xx_समयr0_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	u32 ctrl;

	raw_spin_lock(&gt641xx_समयr_lock);

	ctrl = GT_READ(GT_TC_CONTROL_OFS);
	ctrl &= ~(GT_TC_CONTROL_ENTC0_MSK | GT_TC_CONTROL_SELTC0_MSK);
	GT_WRITE(GT_TC_CONTROL_OFS, ctrl);

	raw_spin_unlock(&gt641xx_समयr_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक gt641xx_समयr0_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	u32 ctrl;

	raw_spin_lock(&gt641xx_समयr_lock);

	ctrl = GT_READ(GT_TC_CONTROL_OFS);
	ctrl &= ~GT_TC_CONTROL_SELTC0_MSK;
	ctrl |= GT_TC_CONTROL_ENTC0_MSK;
	GT_WRITE(GT_TC_CONTROL_OFS, ctrl);

	raw_spin_unlock(&gt641xx_समयr_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक gt641xx_समयr0_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	u32 ctrl;

	raw_spin_lock(&gt641xx_समयr_lock);

	ctrl = GT_READ(GT_TC_CONTROL_OFS);
	ctrl |= GT_TC_CONTROL_ENTC0_MSK | GT_TC_CONTROL_SELTC0_MSK;
	GT_WRITE(GT_TC_CONTROL_OFS, ctrl);

	raw_spin_unlock(&gt641xx_समयr_lock);
	वापस 0;
पूर्ण

अटल व्योम gt641xx_समयr0_event_handler(काष्ठा घड़ी_event_device *dev)
अणु
पूर्ण

अटल काष्ठा घड़ी_event_device gt641xx_समयr0_घड़ीevent = अणु
	.name			= "gt641xx-timer0",
	.features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT,
	.irq			= GT641XX_TIMER0_IRQ,
	.set_next_event		= gt641xx_समयr0_set_next_event,
	.set_state_shutकरोwn	= gt641xx_समयr0_shutकरोwn,
	.set_state_periodic	= gt641xx_समयr0_set_periodic,
	.set_state_oneshot	= gt641xx_समयr0_set_oneshot,
	.tick_resume		= gt641xx_समयr0_shutकरोwn,
	.event_handler		= gt641xx_समयr0_event_handler,
पूर्ण;

अटल irqवापस_t gt641xx_समयr0_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *cd = &gt641xx_समयr0_घड़ीevent;

	cd->event_handler(cd);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init gt641xx_समयr0_घड़ीevent_init(व्योम)
अणु
	काष्ठा घड़ी_event_device *cd;

	अगर (!gt641xx_base_घड़ी)
		वापस 0;

	GT_WRITE(GT_TC0_OFS, gt641xx_base_घड़ी / HZ);

	cd = &gt641xx_समयr0_घड़ीevent;
	cd->rating = 200 + gt641xx_base_घड़ी / 10000000;
	घड़ीevent_set_घड़ी(cd, gt641xx_base_घड़ी);
	cd->max_delta_ns = घड़ीevent_delta2ns(0x7fffffff, cd);
	cd->max_delta_ticks = 0x7fffffff;
	cd->min_delta_ns = घड़ीevent_delta2ns(0x300, cd);
	cd->min_delta_ticks = 0x300;
	cd->cpumask = cpumask_of(0);

	घड़ीevents_रेजिस्टर_device(&gt641xx_समयr0_घड़ीevent);

	वापस request_irq(GT641XX_TIMER0_IRQ, gt641xx_समयr0_पूर्णांकerrupt,
			   IRQF_PERCPU | IRQF_TIMER, "gt641xx_timer0", शून्य);
पूर्ण
arch_initcall(gt641xx_समयr0_घड़ीevent_init);
