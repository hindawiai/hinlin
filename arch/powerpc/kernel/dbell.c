<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Author: Kumar Gala <galak@kernel.crashing.org>
 *
 * Copyright 2009 Freescale Semiconductor Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/hardirq.h>

#समावेश <यंत्र/dbell.h>
#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/trace.h>

#अगर_घोषित CONFIG_SMP

DEFINE_INTERRUPT_HANDLER_ASYNC(करोorbell_exception)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);

	trace_करोorbell_entry(regs);

	ppc_msgsync();

	may_hard_irq_enable();

	kvmppc_clear_host_ipi(smp_processor_id());
	__this_cpu_inc(irq_stat.करोorbell_irqs);

	smp_ipi_demux_relaxed(); /* alपढ़ोy perक्रमmed the barrier */

	trace_करोorbell_निकास(regs);

	set_irq_regs(old_regs);
पूर्ण
#अन्यथा /* CONFIG_SMP */
DEFINE_INTERRUPT_HANDLER_ASYNC(करोorbell_exception)
अणु
	prपूर्णांकk(KERN_WARNING "Received doorbell on non-smp system\n");
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */
