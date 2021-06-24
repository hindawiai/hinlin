<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014-15 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ASM_IRQFLAGS_ARCV2_H
#घोषणा __ASM_IRQFLAGS_ARCV2_H

#समावेश <यंत्र/arcregs.h>

/* status32 Bits */
#घोषणा STATUS_AD_BIT	19   /* Disable Align chk: core supports non-aligned */
#घोषणा STATUS_IE_BIT	31

#घोषणा STATUS_AD_MASK		(1<<STATUS_AD_BIT)
#घोषणा STATUS_IE_MASK		(1<<STATUS_IE_BIT)

/* status32 Bits as encoded/expected by CLRI/SETI */
#घोषणा CLRI_STATUS_IE_BIT	4

#घोषणा CLRI_STATUS_E_MASK	0xF
#घोषणा CLRI_STATUS_IE_MASK	(1 << CLRI_STATUS_IE_BIT)

#घोषणा AUX_USER_SP		0x00D
#घोषणा AUX_IRQ_CTRL		0x00E
#घोषणा AUX_IRQ_ACT		0x043	/* Active Intr across all levels */
#घोषणा AUX_IRQ_LVL_PEND	0x200	/* Pending Intr across all levels */
#घोषणा AUX_IRQ_HINT		0x201	/* For generating Soft Interrupts */
#घोषणा AUX_IRQ_PRIORITY	0x206
#घोषणा ICAUSE			0x40a
#घोषणा AUX_IRQ_SELECT		0x40b
#घोषणा AUX_IRQ_ENABLE		0x40c

/* Was Intr taken in User Mode */
#घोषणा AUX_IRQ_ACT_BIT_U	31

/*
 * Hardware supports 16 priorities (0 highest, 15 lowest)
 * Linux by शेष runs at 1, priority 0 reserved क्रम NMI style पूर्णांकerrupts
 */
#घोषणा ARCV2_IRQ_DEF_PRIO	1

/* seed value क्रम status रेजिस्टर */
#अगर_घोषित CONFIG_ARC_USE_UNALIGNED_MEM_ACCESS
#घोषणा __AD_ENB	STATUS_AD_MASK
#अन्यथा
#घोषणा __AD_ENB	0
#पूर्ण_अगर

#घोषणा ISA_INIT_STATUS_BITS	(STATUS_IE_MASK | __AD_ENB | \
					(ARCV2_IRQ_DEF_PRIO << 1))

#अगर_अघोषित __ASSEMBLY__

/*
 * Save IRQ state and disable IRQs
 */
अटल अंतरभूत दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	__यंत्र__ __अस्थिर__("	clri %0	\n" : "=r" (flags) : : "memory");

	वापस flags;
पूर्ण

/*
 * restore saved IRQ state
 */
अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	__यंत्र__ __अस्थिर__("	seti %0	\n" : : "r" (flags) : "memory");
पूर्ण

/*
 * Unconditionally Enable IRQs
 */
अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	अचिन्हित पूर्णांक irqact = पढ़ो_aux_reg(AUX_IRQ_ACT);

	अगर (irqact & 0xffff)
		ग_लिखो_aux_reg(AUX_IRQ_ACT, irqact & ~0xffff);

	__यंत्र__ __अस्थिर__("	seti	\n" : : : "memory");
पूर्ण

/*
 * Unconditionally Disable IRQs
 */
अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	__यंत्र__ __अस्थिर__("	clri	\n" : : : "memory");
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

	/* To be compatible with irq_save()/irq_restore()
	 * encode the irq bits as expected by CLRI/SETI
	 * (this was needed to make CONFIG_TRACE_IRQFLAGS work)
	 */
	temp = (1 << 5) |
		((!!(temp & STATUS_IE_MASK)) << CLRI_STATUS_IE_BIT) |
		((temp >> 1) & CLRI_STATUS_E_MASK);
	वापस temp;
पूर्ण

/*
 * Query IRQ state
 */
अटल अंतरभूत पूर्णांक arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस !(flags & CLRI_STATUS_IE_MASK);
पूर्ण

अटल अंतरभूत पूर्णांक arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

अटल अंतरभूत व्योम arc_softirq_trigger(पूर्णांक irq)
अणु
	ग_लिखो_aux_reg(AUX_IRQ_HINT, irq);
पूर्ण

अटल अंतरभूत व्योम arc_softirq_clear(पूर्णांक irq)
अणु
	ग_लिखो_aux_reg(AUX_IRQ_HINT, 0);
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
	clri
	TRACE_ASM_IRQ_DISABLE
.endm

.macro IRQ_ENABLE  scratch
	TRACE_ASM_IRQ_ENABLE
	seti
.endm

#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर
