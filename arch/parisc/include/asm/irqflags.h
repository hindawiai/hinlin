<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PARISC_IRQFLAGS_H
#घोषणा __PARISC_IRQFLAGS_H

#समावेश <linux/types.h>
#समावेश <यंत्र/psw.h>

अटल अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	यंत्र अस्थिर("ssm 0, %0" : "=r" (flags) : : "memory");
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	यंत्र अस्थिर("rsm %0,%%r0\n" : : "i" (PSW_I) : "memory");
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	यंत्र अस्थिर("ssm %0,%%r0\n" : : "i" (PSW_I) : "memory");
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	यंत्र अस्थिर("rsm %1,%0" : "=r" (flags) : "i" (PSW_I) : "memory");
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	यंत्र अस्थिर("mtsm %0" : : "r" (flags) : "memory");
पूर्ण

अटल अंतरभूत bool arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस (flags & PSW_I) == 0;
पूर्ण

अटल अंतरभूत bool arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

#पूर्ण_अगर /* __PARISC_IRQFLAGS_H */
