<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Common corrected MCE threshold handler code:
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/irq_vectors.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/trace/irq_vectors.h>

#समावेश "internal.h"

अटल व्योम शेष_threshold_पूर्णांकerrupt(व्योम)
अणु
	pr_err("Unexpected threshold interrupt at vector %x\n",
		THRESHOLD_APIC_VECTOR);
पूर्ण

व्योम (*mce_threshold_vector)(व्योम) = शेष_threshold_पूर्णांकerrupt;

DEFINE_IDTENTRY_SYSVEC(sysvec_threshold)
अणु
	trace_threshold_apic_entry(THRESHOLD_APIC_VECTOR);
	inc_irq_stat(irq_threshold_count);
	mce_threshold_vector();
	trace_threshold_apic_निकास(THRESHOLD_APIC_VECTOR);
	ack_APIC_irq();
पूर्ण
