<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * i8253.c  8253/PIT functions
 *
 */
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/i8253.h>
#समावेश <linux/export.h>
#समावेश <linux/smp.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/समय.स>

अटल irqवापस_t समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	i8253_घड़ीevent.event_handler(&i8253_घड़ीevent);

	वापस IRQ_HANDLED;
पूर्ण

व्योम __init setup_pit_समयr(व्योम)
अणु
	अचिन्हित दीर्घ flags = IRQF_NOBALANCING | IRQF_TIMER;

	घड़ीevent_i8253_init(true);
	अगर (request_irq(0, समयr_पूर्णांकerrupt, flags, "timer", शून्य))
		pr_err("Failed to request irq 0 (timer)\n");
पूर्ण

अटल पूर्णांक __init init_pit_घड़ीsource(व्योम)
अणु
	अगर (num_possible_cpus() > 1 || /* PIT करोes not scale! */
	    !घड़ीevent_state_periodic(&i8253_घड़ीevent))
		वापस 0;

	वापस घड़ीsource_i8253_init();
पूर्ण
arch_initcall(init_pit_घड़ीsource);
