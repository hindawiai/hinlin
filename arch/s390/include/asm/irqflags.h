<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    Copyright IBM Corp. 2006, 2010
 *    Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित __ASM_IRQFLAGS_H
#घोषणा __ASM_IRQFLAGS_H

#समावेश <linux/types.h>

#घोषणा ARCH_IRQ_ENABLED	(3UL << (BITS_PER_LONG - 8))

/* store then OR प्रणाली mask. */
#घोषणा __arch_local_irq_stosm(__or)					\
(अणु									\
	अचिन्हित दीर्घ __mask;						\
	यंत्र अस्थिर(							\
		"	stosm	%0,%1"					\
		: "=Q" (__mask) : "i" (__or) : "memory");		\
	__mask;								\
पूर्ण)

/* store then AND प्रणाली mask. */
#घोषणा __arch_local_irq_stnsm(__and)					\
(अणु									\
	अचिन्हित दीर्घ __mask;						\
	यंत्र अस्थिर(							\
		"	stnsm	%0,%1"					\
		: "=Q" (__mask) : "i" (__and) : "memory");		\
	__mask;								\
पूर्ण)

/* set प्रणाली mask. */
अटल अंतरभूत notrace व्योम __arch_local_irq_ssm(अचिन्हित दीर्घ flags)
अणु
	यंत्र अस्थिर("ssm   %0" : : "Q" (flags) : "memory");
पूर्ण

अटल अंतरभूत notrace अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	वापस __arch_local_irq_stnsm(0xff);
पूर्ण

अटल अंतरभूत notrace अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	वापस __arch_local_irq_stnsm(0xfc);
पूर्ण

अटल अंतरभूत notrace व्योम arch_local_irq_disable(व्योम)
अणु
	arch_local_irq_save();
पूर्ण

अटल अंतरभूत notrace व्योम arch_local_irq_enable(व्योम)
अणु
	__arch_local_irq_stosm(0x03);
पूर्ण

/* This only restores बाह्यal and I/O पूर्णांकerrupt state */
अटल अंतरभूत notrace व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	/* only disabled->disabled and disabled->enabled is valid */
	अगर (flags & ARCH_IRQ_ENABLED)
		arch_local_irq_enable();
पूर्ण

अटल अंतरभूत notrace bool arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस !(flags & ARCH_IRQ_ENABLED);
पूर्ण

अटल अंतरभूत notrace bool arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

#पूर्ण_अगर /* __ASM_IRQFLAGS_H */
