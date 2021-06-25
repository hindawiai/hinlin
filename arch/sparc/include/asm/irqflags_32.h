<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/यंत्र/irqflags.h
 *
 * IRQ flags handling
 *
 * This file माला_लो included from lowlevel यंत्र headers too, to provide
 * wrapped versions of the local_irq_*() APIs, based on the
 * arch_local_irq_*() functions from the lowlevel headers.
 */
#अगर_अघोषित _ASM_IRQFLAGS_H
#घोषणा _ASM_IRQFLAGS_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <यंत्र/psr.h>

व्योम arch_local_irq_restore(अचिन्हित दीर्घ);
अचिन्हित दीर्घ arch_local_irq_save(व्योम);
व्योम arch_local_irq_enable(व्योम);

अटल अंतरभूत notrace अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	यंत्र अस्थिर("rd        %%psr, %0" : "=r" (flags));
	वापस flags;
पूर्ण

अटल अंतरभूत notrace व्योम arch_local_irq_disable(व्योम)
अणु
	arch_local_irq_save();
पूर्ण

अटल अंतरभूत notrace bool arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस (flags & PSR_PIL) != 0;
पूर्ण

अटल अंतरभूत notrace bool arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

#पूर्ण_अगर /* (__ASSEMBLY__) */

#पूर्ण_अगर /* !(_ASM_IRQFLAGS_H) */
