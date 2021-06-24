<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_IRQFLAGS_H
#घोषणा _M68K_IRQFLAGS_H

#समावेश <linux/types.h>
#समावेश <linux/preempt.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/entry.h>

अटल अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	यंत्र अस्थिर ("movew %%sr,%0" : "=d" (flags) : : "memory");
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
#अगर_घोषित CONFIG_COLDFIRE
	यंत्र अस्थिर (
		"move	%/sr,%%d0	\n\t"
		"ori.l	#0x0700,%%d0	\n\t"
		"move	%%d0,%/sr	\n"
		: /* no outमाला_दो */
		:
		: "cc", "%d0", "memory");
#अन्यथा
	यंत्र अस्थिर ("oriw  #0x0700,%%sr" : : : "memory");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
#अगर defined(CONFIG_COLDFIRE)
	यंत्र अस्थिर (
		"move	%/sr,%%d0	\n\t"
		"andi.l	#0xf8ff,%%d0	\n\t"
		"move	%%d0,%/sr	\n"
		: /* no outमाला_दो */
		:
		: "cc", "%d0", "memory");
#अन्यथा
# अगर defined(CONFIG_MMU)
	अगर (MACH_IS_Q40 || !hardirq_count())
# endअगर
		यंत्र अस्थिर (
			"andiw %0,%%sr"
			:
			: "i" (ALLOWINT)
			: "memory");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags = arch_local_save_flags();
	arch_local_irq_disable();
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	यंत्र अस्थिर ("movew %0,%%sr" : : "d" (flags) : "memory");
पूर्ण

अटल अंतरभूत bool arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	अगर (MACH_IS_ATARI) अणु
		/* Ignore HSYNC = ipl 2 on Atari */
		वापस (flags & ~(ALLOWINT | 0x200)) != 0;
	पूर्ण
	वापस (flags & ~ALLOWINT) != 0;
पूर्ण

अटल अंतरभूत bool arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

#पूर्ण_अगर /* _M68K_IRQFLAGS_H */
