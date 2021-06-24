<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ip30-समयr.c: Clocksource/घड़ीevent support क्रम the
 *               HEART chip in SGI Octane (IP30) प्रणालीs.
 *
 * Copyright (C) 2004-2007 Stanislaw Skowronek <skylark@unaligned.org>
 * Copyright (C) 2009 Johannes Dickgreber <tanzy@gmx.de>
 * Copyright (C) 2011 Joshua Kinard <kumba@gentoo.org>
 */

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/percpu.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/cevt-r4k.h>
#समावेश <यंत्र/sgi/heart.h>

अटल u64 ip30_heart_counter_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस heart_पढ़ो(&heart_regs->count);
पूर्ण

काष्ठा घड़ीsource ip30_heart_घड़ीsource = अणु
	.name	= "HEART",
	.rating	= 400,
	.पढ़ो	= ip30_heart_counter_पढ़ो,
	.mask	= CLOCKSOURCE_MASK(52),
	.flags	= (CLOCK_SOURCE_IS_CONTINUOUS | CLOCK_SOURCE_VALID_FOR_HRES),
पूर्ण;

अटल u64 notrace ip30_heart_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस heart_पढ़ो(&heart_regs->count);
पूर्ण

अटल व्योम __init ip30_heart_घड़ीsource_init(व्योम)
अणु
	काष्ठा घड़ीsource *cs = &ip30_heart_घड़ीsource;

	घड़ीsource_रेजिस्टर_hz(cs, HEART_CYCLES_PER_SEC);

	sched_घड़ी_रेजिस्टर(ip30_heart_पढ़ो_sched_घड़ी, 52,
			     HEART_CYCLES_PER_SEC);
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
	पूर्णांक irq = get_c0_compare_पूर्णांक();

	cp0_समयr_irq_installed = 1;
	c0_compare_irqaction.percpu_dev_id = &mips_घड़ीevent_device;
	c0_compare_irqaction.flags &= ~IRQF_SHARED;
	irq_set_handler(irq, handle_percpu_devid_irq);
	irq_set_percpu_devid(irq);
	setup_percpu_irq(irq, &c0_compare_irqaction);
	enable_percpu_irq(irq, IRQ_TYPE_NONE);

	ip30_heart_घड़ीsource_init();
पूर्ण
