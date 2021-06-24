<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  DS1287 घड़ीevent driver
 *
 *  Copyright (C) 2008	Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/समय.स>

पूर्णांक ds1287_समयr_state(व्योम)
अणु
	वापस (CMOS_READ(RTC_REG_C) & RTC_PF) != 0;
पूर्ण

पूर्णांक ds1287_set_base_घड़ी(अचिन्हित पूर्णांक hz)
अणु
	u8 rate;

	चयन (hz) अणु
	हाल 128:
		rate = 0x9;
		अवरोध;
	हाल 256:
		rate = 0x8;
		अवरोध;
	हाल 1024:
		rate = 0x6;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	CMOS_WRITE(RTC_REF_CLCK_32KHZ | rate, RTC_REG_A);

	वापस 0;
पूर्ण

अटल पूर्णांक ds1287_set_next_event(अचिन्हित दीर्घ delta,
				 काष्ठा घड़ी_event_device *evt)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ds1287_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	u8 val;

	spin_lock(&rtc_lock);

	val = CMOS_READ(RTC_REG_B);
	val &= ~RTC_PIE;
	CMOS_WRITE(val, RTC_REG_B);

	spin_unlock(&rtc_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक ds1287_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	u8 val;

	spin_lock(&rtc_lock);

	val = CMOS_READ(RTC_REG_B);
	val |= RTC_PIE;
	CMOS_WRITE(val, RTC_REG_B);

	spin_unlock(&rtc_lock);
	वापस 0;
पूर्ण

अटल व्योम ds1287_event_handler(काष्ठा घड़ी_event_device *dev)
अणु
पूर्ण

अटल काष्ठा घड़ी_event_device ds1287_घड़ीevent = अणु
	.name			= "ds1287",
	.features		= CLOCK_EVT_FEAT_PERIODIC,
	.set_next_event		= ds1287_set_next_event,
	.set_state_shutकरोwn	= ds1287_shutकरोwn,
	.set_state_periodic	= ds1287_set_periodic,
	.tick_resume		= ds1287_shutकरोwn,
	.event_handler		= ds1287_event_handler,
पूर्ण;

अटल irqवापस_t ds1287_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *cd = &ds1287_घड़ीevent;

	/* Ack the RTC पूर्णांकerrupt. */
	CMOS_READ(RTC_REG_C);

	cd->event_handler(cd);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक __init ds1287_घड़ीevent_init(पूर्णांक irq)
अणु
	अचिन्हित दीर्घ flags = IRQF_PERCPU | IRQF_TIMER;
	काष्ठा घड़ी_event_device *cd;

	cd = &ds1287_घड़ीevent;
	cd->rating = 100;
	cd->irq = irq;
	घड़ीevent_set_घड़ी(cd, 32768);
	cd->max_delta_ns = घड़ीevent_delta2ns(0x7fffffff, cd);
	cd->max_delta_ticks = 0x7fffffff;
	cd->min_delta_ns = घड़ीevent_delta2ns(0x300, cd);
	cd->min_delta_ticks = 0x300;
	cd->cpumask = cpumask_of(0);

	घड़ीevents_रेजिस्टर_device(&ds1287_घड़ीevent);

	वापस request_irq(irq, ds1287_पूर्णांकerrupt, flags, "ds1287", शून्य);
पूर्ण
