<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IDT Winchip specअगरic Machine Check Exception Reporting
 * (C) Copyright 2002 Alan Cox <alan@lxorguk.ukuu.org.uk>
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/hardirq.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/msr.h>

#समावेश "internal.h"

/* Machine check handler क्रम WinChip C6: */
अटल noinstr व्योम winchip_machine_check(काष्ठा pt_regs *regs)
अणु
	instrumentation_begin();
	pr_emerg("CPU0: Machine Check Exception.\n");
	add_taपूर्णांक(TAINT_MACHINE_CHECK, LOCKDEP_NOW_UNRELIABLE);
	instrumentation_end();
पूर्ण

/* Set up machine check reporting on the Winchip C6 series */
व्योम winchip_mcheck_init(काष्ठा cpuinfo_x86 *c)
अणु
	u32 lo, hi;

	machine_check_vector = winchip_machine_check;
	/* Make sure the vector poपूर्णांकer is visible beक्रमe we enable MCEs: */
	wmb();

	rdmsr(MSR_IDT_FCR1, lo, hi);
	lo |= (1<<2);	/* Enable EIERRINT (पूर्णांक 18 MCE) */
	lo &= ~(1<<4);	/* Enable MCE */
	wrmsr(MSR_IDT_FCR1, lo, hi);

	cr4_set_bits(X86_CR4_MCE);

	pr_info("Winchip machine check reporting enabled on CPU#0.\n");
पूर्ण
