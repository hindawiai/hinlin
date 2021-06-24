<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_IRQFLAGS_H
#घोषणा __ASM_CSKY_IRQFLAGS_H
#समावेश <abi/reg_ops.h>

अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	flags = mfcr("psr");
	यंत्र अस्थिर("psrclr ie\n":::"memory");
	वापस flags;
पूर्ण
#घोषणा arch_local_irq_save arch_local_irq_save

अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	यंत्र अस्थिर("psrset ee, ie\n":::"memory");
पूर्ण
#घोषणा arch_local_irq_enable arch_local_irq_enable

अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	यंत्र अस्थिर("psrclr ie\n":::"memory");
पूर्ण
#घोषणा arch_local_irq_disable arch_local_irq_disable

अटल अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	वापस mfcr("psr");
पूर्ण
#घोषणा arch_local_save_flags arch_local_save_flags

अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	mtcr("psr", flags);
पूर्ण
#घोषणा arch_local_irq_restore arch_local_irq_restore

अटल अंतरभूत पूर्णांक arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस !(flags & (1<<6));
पूर्ण
#घोषणा arch_irqs_disabled_flags arch_irqs_disabled_flags

#समावेश <यंत्र-generic/irqflags.h>

#पूर्ण_अगर /* __ASM_CSKY_IRQFLAGS_H */
