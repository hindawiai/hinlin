<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1999 Cort Dougan <cort@cs.nmt.edu>
 */
#अगर_अघोषित _ASM_POWERPC_HW_IRQ_H
#घोषणा _ASM_POWERPC_HW_IRQ_H

#अगर_घोषित __KERNEL__

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/compiler.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/processor.h>

#अगर_घोषित CONFIG_PPC64

/*
 * PACA flags in paca->irq_happened.
 *
 * This bits are set when पूर्णांकerrupts occur जबतक soft-disabled
 * and allow a proper replay. Additionally, PACA_IRQ_HARD_DIS
 * is set whenever we manually hard disable.
 */
#घोषणा PACA_IRQ_HARD_DIS	0x01
#घोषणा PACA_IRQ_DBELL		0x02
#घोषणा PACA_IRQ_EE		0x04
#घोषणा PACA_IRQ_DEC		0x08 /* Or FIT */
#घोषणा PACA_IRQ_HMI		0x10
#घोषणा PACA_IRQ_PMI		0x20

/*
 * Some soft-masked पूर्णांकerrupts must be hard masked until they are replayed
 * (e.g., because the soft-masked handler करोes not clear the exception).
 */
#अगर_घोषित CONFIG_PPC_BOOK3S
#घोषणा PACA_IRQ_MUST_HARD_MASK	(PACA_IRQ_EE|PACA_IRQ_PMI)
#अन्यथा
#घोषणा PACA_IRQ_MUST_HARD_MASK	(PACA_IRQ_EE)
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_PPC64 */

/*
 * flags क्रम paca->irq_soft_mask
 */
#घोषणा IRQS_ENABLED		0
#घोषणा IRQS_DISABLED		1 /* local_irq_disable() पूर्णांकerrupts */
#घोषणा IRQS_PMI_DISABLED	2
#घोषणा IRQS_ALL_DISABLED	(IRQS_DISABLED | IRQS_PMI_DISABLED)

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत व्योम __hard_irq_enable(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_BOOKE) || IS_ENABLED(CONFIG_40x))
		wrtee(MSR_EE);
	अन्यथा अगर (IS_ENABLED(CONFIG_PPC_8xx))
		wrtspr(SPRN_EIE);
	अन्यथा अगर (IS_ENABLED(CONFIG_PPC_BOOK3S_64))
		__mपंचांगsrd(MSR_EE | MSR_RI, 1);
	अन्यथा
		mपंचांगsr(mfmsr() | MSR_EE);
पूर्ण

अटल अंतरभूत व्योम __hard_irq_disable(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_BOOKE) || IS_ENABLED(CONFIG_40x))
		wrtee(0);
	अन्यथा अगर (IS_ENABLED(CONFIG_PPC_8xx))
		wrtspr(SPRN_EID);
	अन्यथा अगर (IS_ENABLED(CONFIG_PPC_BOOK3S_64))
		__mपंचांगsrd(MSR_RI, 1);
	अन्यथा
		mपंचांगsr(mfmsr() & ~MSR_EE);
पूर्ण

अटल अंतरभूत व्योम __hard_EE_RI_disable(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_BOOKE) || IS_ENABLED(CONFIG_40x))
		wrtee(0);
	अन्यथा अगर (IS_ENABLED(CONFIG_PPC_8xx))
		wrtspr(SPRN_NRI);
	अन्यथा अगर (IS_ENABLED(CONFIG_PPC_BOOK3S_64))
		__mपंचांगsrd(0, 1);
	अन्यथा
		mपंचांगsr(mfmsr() & ~(MSR_EE | MSR_RI));
पूर्ण

अटल अंतरभूत व्योम __hard_RI_enable(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_BOOKE) || IS_ENABLED(CONFIG_40x))
		वापस;

	अगर (IS_ENABLED(CONFIG_PPC_8xx))
		wrtspr(SPRN_EID);
	अन्यथा अगर (IS_ENABLED(CONFIG_PPC_BOOK3S_64))
		__mपंचांगsrd(MSR_RI, 1);
	अन्यथा
		mपंचांगsr(mfmsr() | MSR_RI);
पूर्ण

#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/paca.h>

अटल अंतरभूत notrace अचिन्हित दीर्घ irq_soft_mask_वापस(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	यंत्र अस्थिर(
		"lbz %0,%1(13)"
		: "=r" (flags)
		: "i" (दुरत्व(काष्ठा paca_काष्ठा, irq_soft_mask)));

	वापस flags;
पूर्ण

/*
 * The "memory" clobber acts as both a compiler barrier
 * क्रम the critical section and as a clobber because
 * we changed paca->irq_soft_mask
 */
अटल अंतरभूत notrace व्योम irq_soft_mask_set(अचिन्हित दीर्घ mask)
अणु
#अगर_घोषित CONFIG_PPC_IRQ_SOFT_MASK_DEBUG
	/*
	 * The irq mask must always include the STD bit अगर any are set.
	 *
	 * and पूर्णांकerrupts करोn't get replayed until the standard
	 * पूर्णांकerrupt (local_irq_disable()) is unmasked.
	 *
	 * Other masks must only provide additional masking beyond
	 * the standard, and they are also not replayed until the
	 * standard पूर्णांकerrupt becomes unmasked.
	 *
	 * This could be changed, but it will require partial
	 * unmasks to be replayed, among other things. For now, take
	 * the simple approach.
	 */
	WARN_ON(mask && !(mask & IRQS_DISABLED));
#पूर्ण_अगर

	यंत्र अस्थिर(
		"stb %0,%1(13)"
		:
		: "r" (mask),
		  "i" (दुरत्व(काष्ठा paca_काष्ठा, irq_soft_mask))
		: "memory");
पूर्ण

अटल अंतरभूत notrace अचिन्हित दीर्घ irq_soft_mask_set_वापस(अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ flags;

#अगर_घोषित CONFIG_PPC_IRQ_SOFT_MASK_DEBUG
	WARN_ON(mask && !(mask & IRQS_DISABLED));
#पूर्ण_अगर

	यंत्र अस्थिर(
		"lbz %0,%1(13); stb %2,%1(13)"
		: "=&r" (flags)
		: "i" (दुरत्व(काष्ठा paca_काष्ठा, irq_soft_mask)),
		  "r" (mask)
		: "memory");

	वापस flags;
पूर्ण

अटल अंतरभूत notrace अचिन्हित दीर्घ irq_soft_mask_or_वापस(अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ flags, पंचांगp;

	यंत्र अस्थिर(
		"lbz %0,%2(13); or %1,%0,%3; stb %1,%2(13)"
		: "=&r" (flags), "=r" (पंचांगp)
		: "i" (दुरत्व(काष्ठा paca_काष्ठा, irq_soft_mask)),
		  "r" (mask)
		: "memory");

#अगर_घोषित CONFIG_PPC_IRQ_SOFT_MASK_DEBUG
	WARN_ON((mask | flags) && !((mask | flags) & IRQS_DISABLED));
#पूर्ण_अगर

	वापस flags;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	वापस irq_soft_mask_वापस();
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	irq_soft_mask_set(IRQS_DISABLED);
पूर्ण

बाह्य व्योम arch_local_irq_restore(अचिन्हित दीर्घ);

अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	arch_local_irq_restore(IRQS_ENABLED);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	वापस irq_soft_mask_set_वापस(IRQS_DISABLED);
पूर्ण

अटल अंतरभूत bool arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस flags & IRQS_DISABLED;
पूर्ण

अटल अंतरभूत bool arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S
/*
 * To support disabling and enabling of irq with PMI, set of
 * new घातerpc_local_irq_pmu_save() and घातerpc_local_irq_restore()
 * functions are added. These macros are implemented using generic
 * linux local_irq_* code from include/linux/irqflags.h.
 */
#घोषणा raw_local_irq_pmu_save(flags)					\
	करो अणु								\
		typecheck(अचिन्हित दीर्घ, flags);			\
		flags = irq_soft_mask_or_वापस(IRQS_DISABLED |	\
				IRQS_PMI_DISABLED);			\
	पूर्ण जबतक(0)

#घोषणा raw_local_irq_pmu_restore(flags)				\
	करो अणु								\
		typecheck(अचिन्हित दीर्घ, flags);			\
		arch_local_irq_restore(flags);				\
	पूर्ण जबतक(0)

#अगर_घोषित CONFIG_TRACE_IRQFLAGS
#घोषणा घातerpc_local_irq_pmu_save(flags)			\
	 करो अणु							\
		raw_local_irq_pmu_save(flags);			\
		अगर (!raw_irqs_disabled_flags(flags))		\
			trace_hardirqs_off();			\
	पूर्ण जबतक(0)
#घोषणा घातerpc_local_irq_pmu_restore(flags)			\
	करो अणु							\
		अगर (!raw_irqs_disabled_flags(flags))		\
			trace_hardirqs_on();			\
		raw_local_irq_pmu_restore(flags);		\
	पूर्ण जबतक(0)
#अन्यथा
#घोषणा घातerpc_local_irq_pmu_save(flags)			\
	करो अणु							\
		raw_local_irq_pmu_save(flags);			\
	पूर्ण जबतक(0)
#घोषणा घातerpc_local_irq_pmu_restore(flags)			\
	करो अणु							\
		raw_local_irq_pmu_restore(flags);		\
	पूर्ण जबतक (0)
#पूर्ण_अगर  /* CONFIG_TRACE_IRQFLAGS */

#पूर्ण_अगर /* CONFIG_PPC_BOOK3S */

#घोषणा hard_irq_disable()	करो अणु					\
	अचिन्हित दीर्घ flags;						\
	__hard_irq_disable();						\
	flags = irq_soft_mask_set_वापस(IRQS_ALL_DISABLED);		\
	local_paca->irq_happened |= PACA_IRQ_HARD_DIS;			\
	अगर (!arch_irqs_disabled_flags(flags)) अणु				\
		यंत्र ("stdx %%r1, 0, %1 ;"				\
		     : "=m" (local_paca->saved_r1)			\
		     : "b" (&local_paca->saved_r1));			\
		trace_hardirqs_off();					\
	पूर्ण								\
पूर्ण जबतक(0)

अटल अंतरभूत bool __lazy_irq_pending(u8 irq_happened)
अणु
	वापस !!(irq_happened & ~PACA_IRQ_HARD_DIS);
पूर्ण

/*
 * Check अगर a lazy IRQ is pending. Should be called with IRQs hard disabled.
 */
अटल अंतरभूत bool lazy_irq_pending(व्योम)
अणु
	वापस __lazy_irq_pending(get_paca()->irq_happened);
पूर्ण

/*
 * Check अगर a lazy IRQ is pending, with no debugging checks.
 * Should be called with IRQs hard disabled.
 * For use in RI disabled code or other स्थिरrained situations.
 */
अटल अंतरभूत bool lazy_irq_pending_nocheck(व्योम)
अणु
	वापस __lazy_irq_pending(local_paca->irq_happened);
पूर्ण

/*
 * This is called by asynchronous पूर्णांकerrupts to conditionally
 * re-enable hard पूर्णांकerrupts after having cleared the source
 * of the पूर्णांकerrupt. They are kept disabled अगर there is a dअगरferent
 * soft-masked पूर्णांकerrupt pending that requires hard masking.
 */
अटल अंतरभूत व्योम may_hard_irq_enable(व्योम)
अणु
	अगर (!(get_paca()->irq_happened & PACA_IRQ_MUST_HARD_MASK)) अणु
		get_paca()->irq_happened &= ~PACA_IRQ_HARD_DIS;
		__hard_irq_enable();
	पूर्ण
पूर्ण

अटल अंतरभूत bool arch_irq_disabled_regs(काष्ठा pt_regs *regs)
अणु
	वापस (regs->softe & IRQS_DISABLED);
पूर्ण

बाह्य bool prep_irq_क्रम_idle(व्योम);
बाह्य bool prep_irq_क्रम_idle_irqsoff(व्योम);
बाह्य व्योम irq_set_pending_from_srr1(अचिन्हित दीर्घ srr1);

#घोषणा fini_irq_क्रम_idle_irqsoff() trace_hardirqs_off();

बाह्य व्योम क्रमce_बाह्यal_irq_replay(व्योम);

अटल अंतरभूत व्योम irq_soft_mask_regs_set_state(काष्ठा pt_regs *regs, अचिन्हित दीर्घ val)
अणु
	regs->softe = val;
पूर्ण
#अन्यथा /* CONFIG_PPC64 */

अटल अंतरभूत notrace अचिन्हित दीर्घ irq_soft_mask_वापस(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	वापस mfmsr();
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	अगर (IS_ENABLED(CONFIG_BOOKE))
		wrtee(flags);
	अन्यथा
		mपंचांगsr(flags);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags = arch_local_save_flags();

	अगर (IS_ENABLED(CONFIG_BOOKE))
		wrtee(0);
	अन्यथा अगर (IS_ENABLED(CONFIG_PPC_8xx))
		wrtspr(SPRN_EID);
	अन्यथा
		mपंचांगsr(flags & ~MSR_EE);

	वापस flags;
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	__hard_irq_disable();
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	__hard_irq_enable();
पूर्ण

अटल अंतरभूत bool arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस (flags & MSR_EE) == 0;
पूर्ण

अटल अंतरभूत bool arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

#घोषणा hard_irq_disable()		arch_local_irq_disable()

अटल अंतरभूत bool arch_irq_disabled_regs(काष्ठा pt_regs *regs)
अणु
	वापस !(regs->msr & MSR_EE);
पूर्ण

अटल अंतरभूत व्योम may_hard_irq_enable(व्योम) अणु पूर्ण

अटल अंतरभूत व्योम irq_soft_mask_regs_set_state(काष्ठा pt_regs *regs, अचिन्हित दीर्घ val)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */

#घोषणा ARCH_IRQ_INIT_FLAGS	IRQ_NOREQUEST

#पूर्ण_अगर  /* __ASSEMBLY__ */
#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर	/* _ASM_POWERPC_HW_IRQ_H */
