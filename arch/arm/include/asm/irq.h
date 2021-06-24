<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARM_IRQ_H
#घोषणा __ASM_ARM_IRQ_H

#घोषणा NR_IRQS_LEGACY	16

#अगर_अघोषित CONFIG_SPARSE_IRQ
#समावेश <mach/irqs.h>
#अन्यथा
#घोषणा NR_IRQS NR_IRQS_LEGACY
#पूर्ण_अगर

#अगर_अघोषित irq_canonicalize
#घोषणा irq_canonicalize(i)	(i)
#पूर्ण_अगर

/*
 * Use this value to indicate lack of पूर्णांकerrupt
 * capability
 */
#अगर_अघोषित NO_IRQ
#घोषणा NO_IRQ	((अचिन्हित पूर्णांक)(-1))
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__
काष्ठा irqaction;
काष्ठा pt_regs;

बाह्य व्योम यंत्र_करो_IRQ(अचिन्हित पूर्णांक, काष्ठा pt_regs *);
व्योम handle_IRQ(अचिन्हित पूर्णांक, काष्ठा pt_regs *);
व्योम init_IRQ(व्योम);

#अगर_घोषित CONFIG_SMP
#समावेश <linux/cpumask.h>

बाह्य व्योम arch_trigger_cpumask_backtrace(स्थिर cpumask_t *mask,
					   bool exclude_self);
#घोषणा arch_trigger_cpumask_backtrace arch_trigger_cpumask_backtrace
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक nr_legacy_irqs(व्योम)
अणु
	वापस NR_IRQS_LEGACY;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर

