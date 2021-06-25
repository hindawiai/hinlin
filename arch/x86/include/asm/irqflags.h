<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _X86_IRQFLAGS_H_
#घोषणा _X86_IRQFLAGS_H_

#समावेश <यंत्र/processor-flags.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/nospec-branch.h>

/* Provide __cpuidle; we can't safely include <linux/cpu.h> */
#घोषणा __cpuidle __section(".cpuidle.text")

/*
 * Interrupt control:
 */

/* Declaration required क्रम gcc < 4.9 to prevent -Werror=missing-prototypes */
बाह्य अंतरभूत अचिन्हित दीर्घ native_save_fl(व्योम);
बाह्य __always_अंतरभूत अचिन्हित दीर्घ native_save_fl(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * "=rm" is safe here, because "pop" adjusts the stack beक्रमe
	 * it evaluates its effective address -- this is part of the
	 * करोcumented behavior of the "pop" inकाष्ठाion.
	 */
	यंत्र अस्थिर("# __raw_save_flags\n\t"
		     "pushf ; pop %0"
		     : "=rm" (flags)
		     : /* no input */
		     : "memory");

	वापस flags;
पूर्ण

अटल __always_अंतरभूत व्योम native_irq_disable(व्योम)
अणु
	यंत्र अस्थिर("cli": : :"memory");
पूर्ण

अटल __always_अंतरभूत व्योम native_irq_enable(व्योम)
अणु
	यंत्र अस्थिर("sti": : :"memory");
पूर्ण

अटल अंतरभूत __cpuidle व्योम native_safe_halt(व्योम)
अणु
	mds_idle_clear_cpu_buffers();
	यंत्र अस्थिर("sti; hlt": : :"memory");
पूर्ण

अटल अंतरभूत __cpuidle व्योम native_halt(व्योम)
अणु
	mds_idle_clear_cpu_buffers();
	यंत्र अस्थिर("hlt": : :"memory");
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_PARAVIRT_XXL
#समावेश <यंत्र/paravirt.h>
#अन्यथा
#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>

अटल __always_अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	वापस native_save_fl();
पूर्ण

अटल __always_अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	native_irq_disable();
पूर्ण

अटल __always_अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	native_irq_enable();
पूर्ण

/*
 * Used in the idle loop; sti takes one inकाष्ठाion cycle
 * to complete:
 */
अटल अंतरभूत __cpuidle व्योम arch_safe_halt(व्योम)
अणु
	native_safe_halt();
पूर्ण

/*
 * Used when पूर्णांकerrupts are alपढ़ोy enabled or to
 * shutकरोwn the processor:
 */
अटल अंतरभूत __cpuidle व्योम halt(व्योम)
अणु
	native_halt();
पूर्ण

/*
 * For spinlocks, etc:
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags = arch_local_save_flags();
	arch_local_irq_disable();
	वापस flags;
पूर्ण
#अन्यथा

#अगर_घोषित CONFIG_X86_64
#अगर_घोषित CONFIG_DEBUG_ENTRY
#घोषणा SAVE_FLAGS		pushfq; popq %rax
#पूर्ण_अगर

#घोषणा INTERRUPT_RETURN	jmp native_iret

#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* CONFIG_PARAVIRT_XXL */

#अगर_अघोषित __ASSEMBLY__
अटल __always_अंतरभूत पूर्णांक arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस !(flags & X86_EFLAGS_IF);
पूर्ण

अटल __always_अंतरभूत पूर्णांक arch_irqs_disabled(व्योम)
अणु
	अचिन्हित दीर्घ flags = arch_local_save_flags();

	वापस arch_irqs_disabled_flags(flags);
पूर्ण

अटल __always_अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	अगर (!arch_irqs_disabled_flags(flags))
		arch_local_irq_enable();
पूर्ण
#अन्यथा
#अगर_घोषित CONFIG_X86_64
#अगर_घोषित CONFIG_XEN_PV
#घोषणा SWAPGS	ALTERNATIVE "swapgs", "", X86_FEATURE_XENPV
#अन्यथा
#घोषणा SWAPGS	swapgs
#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर
