<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_IRQFLAGS_H
#घोषणा __ASM_IRQFLAGS_H

#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sysreg.h>

/*
 * Aarch64 has flags क्रम masking: Debug, Asynchronous (serror), Interrupts and
 * FIQ exceptions, in the 'daif' register. We mask and unmask them in 'daif'
 * order:
 * Masking debug exceptions causes all other exceptions to be masked too/
 * Masking SError masks IRQ/FIQ, but not debug exceptions. IRQ and FIQ are
 * always masked and unmasked together, and have no side effects क्रम other
 * flags. Keeping to this order makes it easier क्रम entry.S to know which
 * exceptions should be unmasked.
 */

/*
 * CPU पूर्णांकerrupt mask handling.
 */
अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	अगर (प्रणाली_has_prio_mask_debugging()) अणु
		u32 pmr = पढ़ो_sysreg_s(SYS_ICC_PMR_EL1);

		WARN_ON_ONCE(pmr != GIC_PRIO_IRQON && pmr != GIC_PRIO_IRQOFF);
	पूर्ण

	यंत्र अस्थिर(ALTERNATIVE(
		"msr	daifclr, #3		// arch_local_irq_enable",
		__msr_s(SYS_ICC_PMR_EL1, "%0"),
		ARM64_HAS_IRQ_PRIO_MASKING)
		:
		: "r" ((अचिन्हित दीर्घ) GIC_PRIO_IRQON)
		: "memory");

	pmr_sync();
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	अगर (प्रणाली_has_prio_mask_debugging()) अणु
		u32 pmr = पढ़ो_sysreg_s(SYS_ICC_PMR_EL1);

		WARN_ON_ONCE(pmr != GIC_PRIO_IRQON && pmr != GIC_PRIO_IRQOFF);
	पूर्ण

	यंत्र अस्थिर(ALTERNATIVE(
		"msr	daifset, #3		// arch_local_irq_disable",
		__msr_s(SYS_ICC_PMR_EL1, "%0"),
		ARM64_HAS_IRQ_PRIO_MASKING)
		:
		: "r" ((अचिन्हित दीर्घ) GIC_PRIO_IRQOFF)
		: "memory");
पूर्ण

/*
 * Save the current पूर्णांकerrupt enable state.
 */
अटल अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	यंत्र अस्थिर(ALTERNATIVE(
		"mrs	%0, daif",
		__mrs_s("%0", SYS_ICC_PMR_EL1),
		ARM64_HAS_IRQ_PRIO_MASKING)
		: "=&r" (flags)
		:
		: "memory");

	वापस flags;
पूर्ण

अटल अंतरभूत पूर्णांक arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	पूर्णांक res;

	यंत्र अस्थिर(ALTERNATIVE(
		"and	%w0, %w1, #" __stringअगरy(PSR_I_BIT),
		"eor	%w0, %w1, #" __stringअगरy(GIC_PRIO_IRQON),
		ARM64_HAS_IRQ_PRIO_MASKING)
		: "=&r" (res)
		: "r" ((पूर्णांक) flags)
		: "memory");

	वापस res;
पूर्ण

अटल अंतरभूत पूर्णांक arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	flags = arch_local_save_flags();

	/*
	 * There are too many states with IRQs disabled, just keep the current
	 * state अगर पूर्णांकerrupts are alपढ़ोy disabled/masked.
	 */
	अगर (!arch_irqs_disabled_flags(flags))
		arch_local_irq_disable();

	वापस flags;
पूर्ण

/*
 * restore saved IRQ state
 */
अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	यंत्र अस्थिर(ALTERNATIVE(
		"msr	daif, %0",
		__msr_s(SYS_ICC_PMR_EL1, "%0"),
		ARM64_HAS_IRQ_PRIO_MASKING)
		:
		: "r" (flags)
		: "memory");

	pmr_sync();
पूर्ण

#पूर्ण_अगर /* __ASM_IRQFLAGS_H */
