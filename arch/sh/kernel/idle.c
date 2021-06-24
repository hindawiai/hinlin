<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * The idle loop क्रम all SuperH platक्रमms.
 *
 *  Copyright (C) 2002 - 2009  Paul Mundt
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/pm.h>
#समावेश <linux/tick.h>
#समावेश <linux/preempt.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/smp.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/bl_bit.h>

अटल व्योम (*sh_idle)(व्योम);

व्योम शेष_idle(व्योम)
अणु
	set_bl_bit();
	raw_local_irq_enable();
	/* Isn't this racy ? */
	cpu_sleep();
	clear_bl_bit();
पूर्ण

व्योम arch_cpu_idle_dead(व्योम)
अणु
	play_dead();
पूर्ण

व्योम arch_cpu_idle(व्योम)
अणु
	sh_idle();
पूर्ण

व्योम __init select_idle_routine(व्योम)
अणु
	/*
	 * If a platक्रमm has set its own idle routine, leave it alone.
	 */
	अगर (!sh_idle)
		sh_idle = शेष_idle;
पूर्ण

व्योम stop_this_cpu(व्योम *unused)
अणु
	local_irq_disable();
	set_cpu_online(smp_processor_id(), false);

	क्रम (;;)
		cpu_sleep();
पूर्ण
