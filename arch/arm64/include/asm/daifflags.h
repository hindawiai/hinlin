<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2017 ARM Ltd.
 */
#अगर_अघोषित __ASM_DAIFFLAGS_H
#घोषणा __ASM_DAIFFLAGS_H

#समावेश <linux/irqflags.h>

#समावेश <यंत्र/arch_gicv3.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/ptrace.h>

#घोषणा DAIF_PROCCTX		0
#घोषणा DAIF_PROCCTX_NOIRQ	(PSR_I_BIT | PSR_F_BIT)
#घोषणा DAIF_ERRCTX		(PSR_A_BIT | PSR_I_BIT | PSR_F_BIT)
#घोषणा DAIF_MASK		(PSR_D_BIT | PSR_A_BIT | PSR_I_BIT | PSR_F_BIT)


/* mask/save/unmask/restore all exceptions, including पूर्णांकerrupts. */
अटल अंतरभूत व्योम local_daअगर_mask(व्योम)
अणु
	WARN_ON(प्रणाली_has_prio_mask_debugging() &&
		(पढ़ो_sysreg_s(SYS_ICC_PMR_EL1) == (GIC_PRIO_IRQOFF |
						    GIC_PRIO_PSR_I_SET)));

	यंत्र अस्थिर(
		"msr	daifset, #0xf		// local_daif_mask\n"
		:
		:
		: "memory");

	/* Don't really care for a dsb here, we don't पूर्णांकend to enable IRQs */
	अगर (प्रणाली_uses_irq_prio_masking())
		gic_ग_लिखो_pmr(GIC_PRIO_IRQON | GIC_PRIO_PSR_I_SET);

	trace_hardirqs_off();
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ local_daअगर_save_flags(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	flags = पढ़ो_sysreg(daअगर);

	अगर (प्रणाली_uses_irq_prio_masking()) अणु
		/* If IRQs are masked with PMR, reflect it in the flags */
		अगर (पढ़ो_sysreg_s(SYS_ICC_PMR_EL1) != GIC_PRIO_IRQON)
			flags |= PSR_I_BIT | PSR_F_BIT;
	पूर्ण

	वापस flags;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ local_daअगर_save(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	flags = local_daअगर_save_flags();

	local_daअगर_mask();

	वापस flags;
पूर्ण

अटल अंतरभूत व्योम local_daअगर_restore(अचिन्हित दीर्घ flags)
अणु
	bool irq_disabled = flags & PSR_I_BIT;

	WARN_ON(प्रणाली_has_prio_mask_debugging() &&
		(पढ़ो_sysreg(daअगर) & (PSR_I_BIT | PSR_F_BIT)) != (PSR_I_BIT | PSR_F_BIT));

	अगर (!irq_disabled) अणु
		trace_hardirqs_on();

		अगर (प्रणाली_uses_irq_prio_masking()) अणु
			gic_ग_लिखो_pmr(GIC_PRIO_IRQON);
			pmr_sync();
		पूर्ण
	पूर्ण अन्यथा अगर (प्रणाली_uses_irq_prio_masking()) अणु
		u64 pmr;

		अगर (!(flags & PSR_A_BIT)) अणु
			/*
			 * If पूर्णांकerrupts are disabled but we can take
			 * asynchronous errors, we can take NMIs
			 */
			flags &= ~(PSR_I_BIT | PSR_F_BIT);
			pmr = GIC_PRIO_IRQOFF;
		पूर्ण अन्यथा अणु
			pmr = GIC_PRIO_IRQON | GIC_PRIO_PSR_I_SET;
		पूर्ण

		/*
		 * There has been concern that the ग_लिखो to daअगर
		 * might be reordered beक्रमe this ग_लिखो to PMR.
		 * From the ARM ARM DDI 0487D.a, section D1.7.1
		 * "Accessing PSTATE fields":
		 *   Writes to the PSTATE fields have side-effects on
		 *   various aspects of the PE operation. All of these
		 *   side-effects are guaranteed:
		 *     - Not to be visible to earlier inकाष्ठाions in
		 *       the execution stream.
		 *     - To be visible to later inकाष्ठाions in the
		 *       execution stream
		 *
		 * Also, ग_लिखोs to PMR are self-synchronizing, so no
		 * पूर्णांकerrupts with a lower priority than PMR is संकेतed
		 * to the PE after the ग_लिखो.
		 *
		 * So we करोn't need additional synchronization here.
		 */
		gic_ग_लिखो_pmr(pmr);
	पूर्ण

	ग_लिखो_sysreg(flags, daअगर);

	अगर (irq_disabled)
		trace_hardirqs_off();
पूर्ण

/*
 * Called by synchronous exception handlers to restore the DAIF bits that were
 * modअगरied by taking an exception.
 */
अटल अंतरभूत व्योम local_daअगर_inherit(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ flags = regs->pstate & DAIF_MASK;

	अगर (पूर्णांकerrupts_enabled(regs))
		trace_hardirqs_on();

	अगर (प्रणाली_uses_irq_prio_masking())
		gic_ग_लिखो_pmr(regs->pmr_save);

	/*
	 * We can't use local_daअगर_restore(regs->pstate) here as
	 * प्रणाली_has_prio_mask_debugging() won't restore the I bit अगर it can
	 * use the pmr instead.
	 */
	ग_लिखो_sysreg(flags, daअगर);
पूर्ण
#पूर्ण_अगर
