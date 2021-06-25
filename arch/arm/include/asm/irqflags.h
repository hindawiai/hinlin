<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARM_IRQFLAGS_H
#घोषणा __ASM_ARM_IRQFLAGS_H

#अगर_घोषित __KERNEL__

#समावेश <यंत्र/ptrace.h>

/*
 * CPU पूर्णांकerrupt mask handling.
 */
#अगर_घोषित CONFIG_CPU_V7M
#घोषणा IRQMASK_REG_NAME_R "primask"
#घोषणा IRQMASK_REG_NAME_W "primask"
#घोषणा IRQMASK_I_BIT	1
#अन्यथा
#घोषणा IRQMASK_REG_NAME_R "cpsr"
#घोषणा IRQMASK_REG_NAME_W "cpsr_c"
#घोषणा IRQMASK_I_BIT	PSR_I_BIT
#पूर्ण_अगर

#अगर __LINUX_ARM_ARCH__ >= 6

#घोषणा arch_local_irq_save arch_local_irq_save
अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	यंत्र अस्थिर(
		"	mrs	%0, " IRQMASK_REG_NAME_R "	@ arch_local_irq_save\n"
		"	cpsid	i"
		: "=r" (flags) : : "memory", "cc");
	वापस flags;
पूर्ण

#घोषणा arch_local_irq_enable arch_local_irq_enable
अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	यंत्र अस्थिर(
		"	cpsie i			@ arch_local_irq_enable"
		:
		:
		: "memory", "cc");
पूर्ण

#घोषणा arch_local_irq_disable arch_local_irq_disable
अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	यंत्र अस्थिर(
		"	cpsid i			@ arch_local_irq_disable"
		:
		:
		: "memory", "cc");
पूर्ण

#घोषणा local_fiq_enable()  __यंत्र__("cpsie f	@ __stf" : : : "memory", "cc")
#घोषणा local_fiq_disable() __यंत्र__("cpsid f	@ __clf" : : : "memory", "cc")

#अगर_अघोषित CONFIG_CPU_V7M
#घोषणा local_abt_enable()  __यंत्र__("cpsie a	@ __sta" : : : "memory", "cc")
#घोषणा local_abt_disable() __यंत्र__("cpsid a	@ __cla" : : : "memory", "cc")
#अन्यथा
#घोषणा local_abt_enable()	करो अणु पूर्ण जबतक (0)
#घोषणा local_abt_disable()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर
#अन्यथा

/*
 * Save the current पूर्णांकerrupt enable state & disable IRQs
 */
#घोषणा arch_local_irq_save arch_local_irq_save
अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags, temp;

	यंत्र अस्थिर(
		"	mrs	%0, cpsr	@ arch_local_irq_save\n"
		"	orr	%1, %0, #128\n"
		"	msr	cpsr_c, %1"
		: "=r" (flags), "=r" (temp)
		:
		: "memory", "cc");
	वापस flags;
पूर्ण

/*
 * Enable IRQs
 */
#घोषणा arch_local_irq_enable arch_local_irq_enable
अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	अचिन्हित दीर्घ temp;
	यंत्र अस्थिर(
		"	mrs	%0, cpsr	@ arch_local_irq_enable\n"
		"	bic	%0, %0, #128\n"
		"	msr	cpsr_c, %0"
		: "=r" (temp)
		:
		: "memory", "cc");
पूर्ण

/*
 * Disable IRQs
 */
#घोषणा arch_local_irq_disable arch_local_irq_disable
अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	अचिन्हित दीर्घ temp;
	यंत्र अस्थिर(
		"	mrs	%0, cpsr	@ arch_local_irq_disable\n"
		"	orr	%0, %0, #128\n"
		"	msr	cpsr_c, %0"
		: "=r" (temp)
		:
		: "memory", "cc");
पूर्ण

/*
 * Enable FIQs
 */
#घोषणा local_fiq_enable()					\
	(अणु							\
		अचिन्हित दीर्घ temp;				\
	__यंत्र__ __अस्थिर__(					\
	"mrs	%0, cpsr		@ stf\n"		\
"	bic	%0, %0, #64\n"					\
"	msr	cpsr_c, %0"					\
	: "=r" (temp)						\
	:							\
	: "memory", "cc");					\
	पूर्ण)

/*
 * Disable FIQs
 */
#घोषणा local_fiq_disable()					\
	(अणु							\
		अचिन्हित दीर्घ temp;				\
	__यंत्र__ __अस्थिर__(					\
	"mrs	%0, cpsr		@ clf\n"		\
"	orr	%0, %0, #64\n"					\
"	msr	cpsr_c, %0"					\
	: "=r" (temp)						\
	:							\
	: "memory", "cc");					\
	पूर्ण)

#घोषणा local_abt_enable()	करो अणु पूर्ण जबतक (0)
#घोषणा local_abt_disable()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * Save the current पूर्णांकerrupt enable state.
 */
#घोषणा arch_local_save_flags arch_local_save_flags
अटल अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	यंत्र अस्थिर(
		"	mrs	%0, " IRQMASK_REG_NAME_R "	@ local_save_flags"
		: "=r" (flags) : : "memory", "cc");
	वापस flags;
पूर्ण

/*
 * restore saved IRQ & FIQ state
 */
#घोषणा arch_local_irq_restore arch_local_irq_restore
अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	यंत्र अस्थिर(
		"	msr	" IRQMASK_REG_NAME_W ", %0	@ local_irq_restore"
		:
		: "r" (flags)
		: "memory", "cc");
पूर्ण

#घोषणा arch_irqs_disabled_flags arch_irqs_disabled_flags
अटल अंतरभूत पूर्णांक arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस flags & IRQMASK_I_BIT;
पूर्ण

#समावेश <यंत्र-generic/irqflags.h>

#पूर्ण_अगर /* अगरdef __KERNEL__ */
#पूर्ण_अगर /* अगरndef __ASM_ARM_IRQFLAGS_H */
