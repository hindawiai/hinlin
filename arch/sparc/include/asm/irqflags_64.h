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

#समावेश <यंत्र/pil.h>

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत notrace अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	__यंत्र__ __अस्थिर__(
		"rdpr	%%pil, %0"
		: "=r" (flags)
	);

	वापस flags;
पूर्ण

अटल अंतरभूत notrace व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	__यंत्र__ __अस्थिर__(
		"wrpr	%0, %%pil"
		: /* no output */
		: "r" (flags)
		: "memory"
	);
पूर्ण

अटल अंतरभूत notrace व्योम arch_local_irq_disable(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
		"wrpr	%0, %%pil"
		: /* no outमाला_दो */
		: "i" (PIL_NORMAL_MAX)
		: "memory"
	);
पूर्ण

अटल अंतरभूत notrace व्योम arch_local_irq_enable(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
		"wrpr	0, %%pil"
		: /* no outमाला_दो */
		: /* no inमाला_दो */
		: "memory"
	);
पूर्ण

अटल अंतरभूत notrace पूर्णांक arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस (flags > 0);
पूर्ण

अटल अंतरभूत notrace पूर्णांक arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

अटल अंतरभूत notrace अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags, पंचांगp;

	/* Disable पूर्णांकerrupts to PIL_NORMAL_MAX unless we alपढ़ोy
	 * are using PIL_NMI, in which हाल PIL_NMI is retained.
	 *
	 * The only values we ever program पूर्णांकo the %pil are 0,
	 * PIL_NORMAL_MAX and PIL_NMI.
	 *
	 * Since PIL_NMI is the largest %pil value and all bits are
	 * set in it (0xf), it करोesn't matter what PIL_NORMAL_MAX
	 * actually is.
	 */
	__यंत्र__ __अस्थिर__(
		"rdpr	%%pil, %0\n\t"
		"or	%0, %2, %1\n\t"
		"wrpr	%1, 0x0, %%pil"
		: "=r" (flags), "=r" (पंचांगp)
		: "i" (PIL_NORMAL_MAX)
		: "memory"
	);

	वापस flags;
पूर्ण

#पूर्ण_अगर /* (__ASSEMBLY__) */

#पूर्ण_अगर /* !(_ASM_IRQFLAGS_H) */
