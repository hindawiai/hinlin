<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * x86 specअगरic code क्रम irq_work
 *
 * Copyright (C) 2010 Red Hat, Inc., Peter Zijlstra
 */

#समावेश <linux/kernel.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/hardirq.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/idtentry.h>
#समावेश <यंत्र/trace/irq_vectors.h>
#समावेश <linux/पूर्णांकerrupt.h>

#अगर_घोषित CONFIG_X86_LOCAL_APIC
DEFINE_IDTENTRY_SYSVEC(sysvec_irq_work)
अणु
	ack_APIC_irq();
	trace_irq_work_entry(IRQ_WORK_VECTOR);
	inc_irq_stat(apic_irq_work_irqs);
	irq_work_run();
	trace_irq_work_निकास(IRQ_WORK_VECTOR);
पूर्ण

व्योम arch_irq_work_उठाओ(व्योम)
अणु
	अगर (!arch_irq_work_has_पूर्णांकerrupt())
		वापस;

	apic->send_IPI_self(IRQ_WORK_VECTOR);
	apic_रुको_icr_idle();
पूर्ण
#पूर्ण_अगर
