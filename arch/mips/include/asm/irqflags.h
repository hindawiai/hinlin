<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994, 95, 96, 97, 98, 99, 2003 by Ralf Baechle
 * Copyright (C) 1996 by Paul M. Antoine
 * Copyright (C) 1999 Silicon Graphics
 * Copyright (C) 2000 MIPS Technologies, Inc.
 */
#अगर_अघोषित _ASM_IRQFLAGS_H
#घोषणा _ASM_IRQFLAGS_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/compiler.h>
#समावेश <linux/stringअगरy.h>
#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र/hazards.h>

#अगर defined(CONFIG_CPU_HAS_DIEI)

अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
	"	.set	push						\n"
	"	.set	noat						\n"
	"	di							\n"
	"	" __stringअगरy(__irq_disable_hazard) "			\n"
	"	.set	pop						\n"
	: /* no outमाला_दो */
	: /* no inमाला_दो */
	: "memory");
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	यंत्र __अस्थिर__(
	"	.set	push						\n"
	"	.set	reorder						\n"
	"	.set	noat						\n"
#अगर defined(CONFIG_CPU_LOONGSON64) || defined(CONFIG_CPU_LOONGSON32)
	"	mfc0	%[flags], $12					\n"
	"	di							\n"
#अन्यथा
	"	di	%[flags]					\n"
#पूर्ण_अगर
	"	andi	%[flags], 1					\n"
	"	" __stringअगरy(__irq_disable_hazard) "			\n"
	"	.set	pop						\n"
	: [flags] "=r" (flags)
	: /* no inमाला_दो */
	: "memory");

	वापस flags;
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ __पंचांगp1;

	__यंत्र__ __अस्थिर__(
	"	.set	push						\n"
	"	.set	noreorder					\n"
	"	.set	noat						\n"
#अगर defined(CONFIG_IRQ_MIPS_CPU)
	/*
	 * Slow, but करोesn't suffer from a relatively unlikely race
	 * condition we're having since days 1.
	 */
	"	beqz	%[flags], 1f					\n"
	"	di							\n"
	"	ei							\n"
	"1:								\n"
#अन्यथा
	/*
	 * Fast, dangerous.  Lअगरe is fun, lअगरe is good.
	 */
	"	mfc0	$1, $12						\n"
	"	ins	$1, %[flags], 0, 1				\n"
	"	mtc0	$1, $12						\n"
#पूर्ण_अगर
	"	" __stringअगरy(__irq_disable_hazard) "			\n"
	"	.set	pop						\n"
	: [flags] "=r" (__पंचांगp1)
	: "0" (flags)
	: "memory");
पूर्ण

#अन्यथा
/* Functions that require preempt_अणुdis,enपूर्णable() are in mips-atomic.c */
व्योम arch_local_irq_disable(व्योम);
अचिन्हित दीर्घ arch_local_irq_save(व्योम);
व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags);
#पूर्ण_अगर /* CONFIG_CPU_HAS_DIEI */

अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
	"	.set	push						\n"
	"	.set	reorder						\n"
	"	.set	noat						\n"
#अगर defined(CONFIG_CPU_HAS_DIEI)
	"	ei							\n"
#अन्यथा
	"	mfc0	$1,$12						\n"
	"	ori	$1,0x1f						\n"
	"	xori	$1,0x1e						\n"
	"	mtc0	$1,$12						\n"
#पूर्ण_अगर
	"	" __stringअगरy(__irq_enable_hazard) "			\n"
	"	.set	pop						\n"
	: /* no outमाला_दो */
	: /* no inमाला_दो */
	: "memory");
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	यंत्र __अस्थिर__(
	"	.set	push						\n"
	"	.set	reorder						\n"
	"	mfc0	%[flags], $12					\n"
	"	.set	pop						\n"
	: [flags] "=r" (flags));

	वापस flags;
पूर्ण


अटल अंतरभूत पूर्णांक arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस !(flags & 1);
पूर्ण

अटल अंतरभूत पूर्णांक arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

#पूर्ण_अगर /* #अगर_अघोषित __ASSEMBLY__ */

/*
 * Do the CPU's IRQ-state tracing from assembly code.
 */
#अगर_घोषित CONFIG_TRACE_IRQFLAGS
/* Reload some रेजिस्टरs clobbered by trace_hardirqs_on */
#अगर_घोषित CONFIG_64BIT
# define TRACE_IRQS_RELOAD_REGS						\
	LONG_L	$11, PT_R11(sp);					\
	LONG_L	$10, PT_R10(sp);					\
	LONG_L	$9, PT_R9(sp);						\
	LONG_L	$8, PT_R8(sp);						\
	LONG_L	$7, PT_R7(sp);						\
	LONG_L	$6, PT_R6(sp);						\
	LONG_L	$5, PT_R5(sp);						\
	LONG_L	$4, PT_R4(sp);						\
	LONG_L	$2, PT_R2(sp)
#अन्यथा
# define TRACE_IRQS_RELOAD_REGS						\
	LONG_L	$7, PT_R7(sp);						\
	LONG_L	$6, PT_R6(sp);						\
	LONG_L	$5, PT_R5(sp);						\
	LONG_L	$4, PT_R4(sp);						\
	LONG_L	$2, PT_R2(sp)
#पूर्ण_अगर
# define TRACE_IRQS_ON							\
	CLI;	/* make sure trace_hardirqs_on() is called in kernel level */ \
	jal	trace_hardirqs_on
# define TRACE_IRQS_ON_RELOAD						\
	TRACE_IRQS_ON;							\
	TRACE_IRQS_RELOAD_REGS
# define TRACE_IRQS_OFF							\
	jal	trace_hardirqs_off
#अन्यथा
# define TRACE_IRQS_ON
# define TRACE_IRQS_ON_RELOAD
# define TRACE_IRQS_OFF
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_IRQFLAGS_H */
