<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * IRQ flags defines.
 *
 * Copyright (C) 1998-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 1999 Asit Mallick <asit.k.mallick@पूर्णांकel.com>
 * Copyright (C) 1999 Don Dugger <करोn.dugger@पूर्णांकel.com>
 */

#अगर_अघोषित _ASM_IA64_IRQFLAGS_H
#घोषणा _ASM_IA64_IRQFLAGS_H

#समावेश <यंत्र/pal.h>
#समावेश <यंत्र/kregs.h>

#अगर_घोषित CONFIG_IA64_DEBUG_IRQ
बाह्य अचिन्हित दीर्घ last_cli_ip;
अटल अंतरभूत व्योम arch_maybe_save_ip(अचिन्हित दीर्घ flags)
अणु
	अगर (flags & IA64_PSR_I)
		last_cli_ip = ia64_getreg(_IA64_REG_IP);
पूर्ण
#अन्यथा
#घोषणा arch_maybe_save_ip(flags) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * - clearing psr.i is implicitly serialized (visible by next insn)
 * - setting psr.i requires data serialization
 * - we need a stop-bit beक्रमe पढ़ोing PSR because we someबार
 *   ग_लिखो a भग्नing-poपूर्णांक रेजिस्टर right beक्रमe पढ़ोing the PSR
 *   and that ग_लिखोs to PSR.mfl
 */

अटल अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	ia64_stop();
	वापस ia64_getreg(_IA64_REG_PSR);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags = arch_local_save_flags();

	ia64_stop();
	ia64_rsm(IA64_PSR_I);
	arch_maybe_save_ip(flags);
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
#अगर_घोषित CONFIG_IA64_DEBUG_IRQ
	arch_local_irq_save();
#अन्यथा
	ia64_stop();
	ia64_rsm(IA64_PSR_I);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	ia64_stop();
	ia64_ssm(IA64_PSR_I);
	ia64_srlz_d();
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
#अगर_घोषित CONFIG_IA64_DEBUG_IRQ
	अचिन्हित दीर्घ old_psr = arch_local_save_flags();
#पूर्ण_अगर
	ia64_पूर्णांकrin_local_irq_restore(flags & IA64_PSR_I);
	arch_maybe_save_ip(old_psr & ~flags);
पूर्ण

अटल अंतरभूत bool arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस (flags & IA64_PSR_I) == 0;
पूर्ण

अटल अंतरभूत bool arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

अटल अंतरभूत व्योम arch_safe_halt(व्योम)
अणु
	arch_local_irq_enable();
	ia64_pal_halt_light();	/* PAL_HALT_LIGHT */
पूर्ण


#पूर्ण_अगर /* _ASM_IA64_IRQFLAGS_H */
