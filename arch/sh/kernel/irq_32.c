<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SHcompact irqflags support
 *
 * Copyright (C) 2006 - 2009 Paul Mundt
 */
#समावेश <linux/irqflags.h>
#समावेश <linux/module.h>

व्योम notrace arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ __dummy0, __dummy1;

	अगर (flags == ARCH_IRQ_DISABLED) अणु
		__यंत्र__ __अस्थिर__ (
			"stc	sr, %0\n\t"
			"or	#0xf0, %0\n\t"
			"ldc	%0, sr\n\t"
			: "=&z" (__dummy0)
			: /* no inमाला_दो */
			: "memory"
		);
	पूर्ण अन्यथा अणु
		__यंत्र__ __अस्थिर__ (
			"stc	sr, %0\n\t"
			"and	%1, %0\n\t"
#अगर_घोषित CONFIG_CPU_HAS_SR_RB
			"stc	r6_bank, %1\n\t"
			"or	%1, %0\n\t"
#पूर्ण_अगर
			"ldc	%0, sr\n\t"
			: "=&r" (__dummy0), "=r" (__dummy1)
			: "1" (~ARCH_IRQ_DISABLED)
			: "memory"
		);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(arch_local_irq_restore);

अचिन्हित दीर्घ notrace arch_local_save_flags(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	__यंत्र__ __अस्थिर__ (
		"stc	sr, %0\n\t"
		"and	#0xf0, %0\n\t"
		: "=&z" (flags)
		: /* no inमाला_दो */
		: "memory"
	);

	वापस flags;
पूर्ण
EXPORT_SYMBOL(arch_local_save_flags);
