<शैली गुरु>
/*
 * Xtensa IRQ flags handling functions
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 * Copyright (C) 2015 Cadence Design Systems Inc.
 */

#अगर_अघोषित _XTENSA_IRQFLAGS_H
#घोषणा _XTENSA_IRQFLAGS_H

#समावेश <linux/stringअगरy.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/processor.h>

अटल अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	यंत्र अस्थिर("rsr %0, ps" : "=a" (flags));
	वापस flags;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags;
#अगर XTENSA_FAKE_NMI
#अगर defined(CONFIG_DEBUG_MISC) && (LOCKLEVEL | TOPLEVEL) >= XCHAL_DEBUGLEVEL
	अचिन्हित दीर्घ पंचांगp;

	यंत्र अस्थिर("rsr	%0, ps\t\n"
		     "extui	%1, %0, 0, 4\t\n"
		     "bgei	%1, "__stringअगरy(LOCKLEVEL)", 1f\t\n"
		     "rsil	%0, "__stringअगरy(LOCKLEVEL)"\n"
		     "1:"
		     : "=a" (flags), "=a" (पंचांगp) :: "memory");
#अन्यथा
	यंत्र अस्थिर("rsr	%0, ps\t\n"
		     "or	%0, %0, %1\t\n"
		     "xsr	%0, ps\t\n"
		     "rsync"
		     : "=&a" (flags) : "a" (LOCKLEVEL) : "memory");
#पूर्ण_अगर
#अन्यथा
	यंत्र अस्थिर("rsil	%0, "__stringअगरy(LOCKLEVEL)
		     : "=a" (flags) :: "memory");
#पूर्ण_अगर
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	arch_local_irq_save();
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	यंत्र अस्थिर("rsil %0, 0" : "=a" (flags) :: "memory");
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	यंत्र अस्थिर("wsr %0, ps; rsync"
		     :: "a" (flags) : "memory");
पूर्ण

अटल अंतरभूत bool arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
#अगर XCHAL_EXCM_LEVEL < LOCKLEVEL || (1 << PS_EXCM_BIT) < LOCKLEVEL
#त्रुटि "XCHAL_EXCM_LEVEL and 1<<PS_EXCM_BIT must be no less than LOCKLEVEL"
#पूर्ण_अगर
	वापस (flags & (PS_INTLEVEL_MASK | (1 << PS_EXCM_BIT))) >= LOCKLEVEL;
पूर्ण

अटल अंतरभूत bool arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

#पूर्ण_अगर /* _XTENSA_IRQFLAGS_H */
