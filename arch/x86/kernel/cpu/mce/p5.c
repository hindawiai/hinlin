<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * P5 specअगरic Machine Check Exception Reporting
 * (C) Copyright 2002 Alan Cox <alan@lxorguk.ukuu.org.uk>
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/smp.h>
#समावेश <linux/hardirq.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/msr.h>

#समावेश "internal.h"

/* By शेष disabled */
पूर्णांक mce_p5_enabled __पढ़ो_mostly;

/* Machine check handler क्रम Pentium class Intel CPUs: */
अटल noinstr व्योम pentium_machine_check(काष्ठा pt_regs *regs)
अणु
	u32 loaddr, hi, lotype;

	instrumentation_begin();
	rdmsr(MSR_IA32_P5_MC_ADDR, loaddr, hi);
	rdmsr(MSR_IA32_P5_MC_TYPE, lotype, hi);

	pr_emerg("CPU#%d: Machine Check Exception:  0x%8X (type 0x%8X).\n",
		 smp_processor_id(), loaddr, lotype);

	अगर (lotype & (1<<5)) अणु
		pr_emerg("CPU#%d: Possible thermal failure (CPU on fire ?).\n",
			 smp_processor_id());
	पूर्ण

	add_taपूर्णांक(TAINT_MACHINE_CHECK, LOCKDEP_NOW_UNRELIABLE);
	instrumentation_end();
पूर्ण

/* Set up machine check reporting क्रम processors with Intel style MCE: */
व्योम पूर्णांकel_p5_mcheck_init(काष्ठा cpuinfo_x86 *c)
अणु
	u32 l, h;

	/* Default P5 to off as its often misconnected: */
	अगर (!mce_p5_enabled)
		वापस;

	/* Check क्रम MCE support: */
	अगर (!cpu_has(c, X86_FEATURE_MCE))
		वापस;

	machine_check_vector = pentium_machine_check;
	/* Make sure the vector poपूर्णांकer is visible beक्रमe we enable MCEs: */
	wmb();

	/* Read रेजिस्टरs beक्रमe enabling: */
	rdmsr(MSR_IA32_P5_MC_ADDR, l, h);
	rdmsr(MSR_IA32_P5_MC_TYPE, l, h);
	pr_info("Intel old style machine check architecture supported.\n");

	/* Enable MCE: */
	cr4_set_bits(X86_CR4_MCE);
	pr_info("Intel old style machine check reporting enabled on CPU#%d.\n",
		smp_processor_id());
पूर्ण
