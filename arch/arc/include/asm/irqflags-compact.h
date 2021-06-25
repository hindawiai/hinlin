<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014-15 Synopsys, Inc. (www.synopsys.com)
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ASM_IRQFLAGS_ARCOMPACT_H
#घोषणा __ASM_IRQFLAGS_ARCOMPACT_H

/* vineetg: March 2010 : local_irq_save( ) optimisation
 *  -Remove explicit mov of current status32 पूर्णांकo reg, that is not needed
 *  -Use BIC  insn instead of INVERTED + AND
 *  -Conditionally disable पूर्णांकerrupts (अगर they are not enabled, करोn't disable)
*/

#समावेश <यंत्र/arcregs.h>

/* status32 Reg bits related to Interrupt Handling */
#घोषणा STATUS_E1_BIT		1	/* Int 1 enable */
#घोषणा STATUS_E2_BIT		2	/* Int 2 enable */
#घोषणा STATUS_A1_BIT		3	/* Int 1 active */
#घोषणा STATUS_A2_BIT		4	/* Int 2 active */
#घोषणा STATUS_AE_BIT		5	/* Exception active */

#घोषणा STATUS_E1_MASK		(1<<STATUS_E1_BIT)
#घोषणा STATUS_E2_MASK		(1<<STATUS_E2_BIT)
#घोषणा STATUS_A1_MASK		(1<<STATUS_A1_BIT)
#घोषणा STATUS_A2_MASK		(1<<STATUS_A2_BIT)
#घोषणा STATUS_AE_MASK		(1<<STATUS_AE_BIT)
#घोषणा STATUS_IE_MASK		(STATUS_E1_MASK | STATUS_E2_MASK)

/* Other Interrupt Handling related Aux regs */
#घोषणा AUX_IRQ_LEV		0x200	/* IRQ Priority: L1 or L2 */
#घोषणा AUX_IRQ_HINT		0x201	/* For generating Soft Interrupts */
#घोषणा AUX_IRQ_LV12		0x43	/* पूर्णांकerrupt level रेजिस्टर */

#घोषणा AUX_IENABLE		0x40c
#घोषणा AUX_ITRIGGER		0x40d
#घोषणा AUX_IPULSE		0x415

#घोषणा ISA_INIT_STATUS_BITS	STATUS_IE_MASK

#अगर_अघोषित __ASSEMBLY__

/******************************************************************
 * IRQ Control Macros
 *
 * All of them have "memory" clobber (compiler barrier) which is needed to
 * ensure that LD/ST requiring irq safetly (R-M-W when LLSC is not available)
 * are reकरोne after IRQs are re-enabled (and gcc करोesn't reuse stale रेजिस्टर)
 *
 * Noted at the समय of Abilis Timer List corruption
 *	Orig Bug + Rejected solution	: https://lkml.org/lkml/2013/3/29/67
 *	Reasoning			: https://lkml.org/lkml/2013/4/8/15
 *
 ******************************************************************/

/*
 * Save IRQ state and disable IRQs
 */
अटल अंतरभूत दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ temp, flags;

	__यंत्र__ __अस्थिर__(
	"	lr  %1, [status32]	\n"
	"	bic %0, %1, %2		\n"
	"	and.f 0, %1, %2	\n"
	"	flag.nz %0		\n"
	: "=r"(temp), "=r"(flags)
	: "n"((STATUS_E1_MASK | STATUS_E2_MASK))
	: "memory", "cc");

	वापस flags;
पूर्ण

/*
 * restore saved IRQ state
 */
अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु

	__यंत्र__ __अस्थिर__(
	"	flag %0			\n"
	:
	: "r"(flags)
	: "memory");
पूर्ण

/*
 * Unconditionally Enable IRQs
 */
#अगर_घोषित CONFIG_ARC_COMPACT_IRQ_LEVELS
बाह्य व्योम arch_local_irq_enable(व्योम);
#अन्यथा
अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	अचिन्हित दीर्घ temp;

	__यंत्र__ __अस्थिर__(
	"	lr   %0, [status32]	\n"
	"	or   %0, %0, %1		\n"
	"	flag %0			\n"
	: "=&r"(temp)
	: "n"((STATUS_E1_MASK | STATUS_E2_MASK))
	: "cc", "memory");
पूर्ण
#पूर्ण_अगर

/*
 * Unconditionally Disable IRQs
 */
अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	अचिन्हित दीर्घ temp;

	__यंत्र__ __अस्थिर__(
	"	lr  %0, [status32]	\n"
	"	and %0, %0, %1		\n"
	"	flag %0			\n"
	: "=&r"(temp)
	: "n"(~(STATUS_E1_MASK | STATUS_E2_MASK))
	: "memory");
पूर्ण

/*
 * save IRQ state
 */
अटल अंतरभूत दीर्घ arch_local_save_flags(व्योम)
अणु
	अचिन्हित दीर्घ temp;

	__यंत्र__ __अस्थिर__(
	"	lr  %0, [status32]	\n"
	: "=&r"(temp)
	:
	: "memory");

	वापस temp;
पूर्ण

/*
 * Query IRQ state
 */
अटल अंतरभूत पूर्णांक arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस !(flags & (STATUS_E1_MASK
#अगर_घोषित CONFIG_ARC_COMPACT_IRQ_LEVELS
			| STATUS_E2_MASK
#पूर्ण_अगर
		));
पूर्ण

अटल अंतरभूत पूर्णांक arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

#अन्यथा

#अगर_घोषित CONFIG_TRACE_IRQFLAGS

.macro TRACE_ASM_IRQ_DISABLE
	bl	trace_hardirqs_off
.endm

.macro TRACE_ASM_IRQ_ENABLE
	bl	trace_hardirqs_on
.endm

#अन्यथा

.macro TRACE_ASM_IRQ_DISABLE
.endm

.macro TRACE_ASM_IRQ_ENABLE
.endm

#पूर्ण_अगर

.macro IRQ_DISABLE  scratch
	lr	\scratch, [status32]
	bic	\scratch, \scratch, (STATUS_E1_MASK | STATUS_E2_MASK)
	flag	\scratch
	TRACE_ASM_IRQ_DISABLE
.endm

.macro IRQ_ENABLE  scratch
	TRACE_ASM_IRQ_ENABLE
	lr	\scratch, [status32]
	or	\scratch, \scratch, (STATUS_E1_MASK | STATUS_E2_MASK)
	flag	\scratch
.endm

#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर
