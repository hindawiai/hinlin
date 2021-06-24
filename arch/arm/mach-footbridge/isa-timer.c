<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/arm/mach-footbridge/isa-समयr.c
 *
 *  Copyright (C) 1998 Russell King.
 *  Copyright (C) 1998 Phil Blundell
 */
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/i8253.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयx.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach/समय.स>

#समावेश "common.h"

अटल irqवापस_t pit_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *ce = dev_id;
	ce->event_handler(ce);
	वापस IRQ_HANDLED;
पूर्ण

व्योम __init isa_समयr_init(व्योम)
अणु
	घड़ीsource_i8253_init();

	अगर (request_irq(i8253_घड़ीevent.irq, pit_समयr_पूर्णांकerrupt,
			IRQF_TIMER | IRQF_IRQPOLL, "pit", &i8253_घड़ीevent))
		pr_err("Failed to request irq %d(pit)\n", i8253_घड़ीevent.irq);
	घड़ीevent_i8253_init(false);
पूर्ण
