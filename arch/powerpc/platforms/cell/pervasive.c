<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CBE Pervasive Monitor and Debug
 *
 * (C) Copyright IBM Corporation 2005
 *
 * Authors: Maximino Aguilar (maguilar@us.ibm.com)
 *          Michael N. Day (mnday@us.ibm.com)
 */

#अघोषित DEBUG

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/percpu.h>
#समावेश <linux/types.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/cell-regs.h>
#समावेश <यंत्र/cpu_has_feature.h>

#समावेश "pervasive.h"
#समावेश "ras.h"

अटल व्योम cbe_घातer_save(व्योम)
अणु
	अचिन्हित दीर्घ ctrl, thपढ़ो_चयन_control;

	/* Ensure our पूर्णांकerrupt state is properly tracked */
	अगर (!prep_irq_क्रम_idle())
		वापस;

	ctrl = mfspr(SPRN_CTRLF);

	/* Enable DEC and EE पूर्णांकerrupt request */
	thपढ़ो_चयन_control  = mfspr(SPRN_TSC_CELL);
	thपढ़ो_चयन_control |= TSC_CELL_EE_ENABLE | TSC_CELL_EE_BOOST;

	चयन (ctrl & CTRL_CT) अणु
	हाल CTRL_CT0:
		thपढ़ो_चयन_control |= TSC_CELL_DEC_ENABLE_0;
		अवरोध;
	हाल CTRL_CT1:
		thपढ़ो_चयन_control |= TSC_CELL_DEC_ENABLE_1;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "%s: unknown configuration\n",
			__func__);
		अवरोध;
	पूर्ण
	mtspr(SPRN_TSC_CELL, thपढ़ो_चयन_control);

	/*
	 * go पूर्णांकo low thपढ़ो priority, medium priority will be
	 * restored क्रम us after wake-up.
	 */
	HMT_low();

	/*
	 * atomically disable thपढ़ो execution and runlatch.
	 * External and Decrementer exceptions are still handled when the
	 * thपढ़ो is disabled but now enter in cbe_प्रणाली_reset_exception()
	 */
	ctrl &= ~(CTRL_RUNLATCH | CTRL_TE);
	mtspr(SPRN_CTRLT, ctrl);

	/* Re-enable पूर्णांकerrupts in MSR */
	__hard_irq_enable();
पूर्ण

अटल पूर्णांक cbe_प्रणाली_reset_exception(काष्ठा pt_regs *regs)
अणु
	चयन (regs->msr & SRR1_WAKEMASK) अणु
	हाल SRR1_WAKEDEC:
		set_dec(1);
	हाल SRR1_WAKEEE:
		/*
		 * Handle these when पूर्णांकerrupts get re-enabled and we take
		 * them as regular exceptions. We are in an NMI context
		 * and can't handle these here.
		 */
		अवरोध;
	हाल SRR1_WAKEMT:
		वापस cbe_sysreset_hack();
#अगर_घोषित CONFIG_CBE_RAS
	हाल SRR1_WAKESYSERR:
		cbe_प्रणाली_error_exception(regs);
		अवरोध;
	हाल SRR1_WAKETHERM:
		cbe_thermal_exception(regs);
		अवरोध;
#पूर्ण_अगर /* CONFIG_CBE_RAS */
	शेष:
		/* करो प्रणाली reset */
		वापस 0;
	पूर्ण
	/* everything handled */
	वापस 1;
पूर्ण

व्योम __init cbe_pervasive_init(व्योम)
अणु
	पूर्णांक cpu;

	अगर (!cpu_has_feature(CPU_FTR_PAUSE_ZERO))
		वापस;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा cbe_pmd_regs __iomem *regs = cbe_get_cpu_pmd_regs(cpu);
		अगर (!regs)
			जारी;

		 /* Enable Pause(0) control bit */
		out_be64(&regs->pmcr, in_be64(&regs->pmcr) |
					    CBE_PMD_PAUSE_ZERO_CONTROL);
	पूर्ण

	ppc_md.घातer_save = cbe_घातer_save;
	ppc_md.प्रणाली_reset_exception = cbe_प्रणाली_reset_exception;
पूर्ण
