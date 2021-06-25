<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_घोषित __KERNEL__
#अगर_अघोषित _ASM_POWERPC_IRQ_H
#घोषणा _ASM_POWERPC_IRQ_H

/*
 */

#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/list.h>
#समावेश <linux/radix-tree.h>

#समावेश <यंत्र/types.h>
#समावेश <linux/atomic.h>


बाह्य atomic_t ppc_n_lost_पूर्णांकerrupts;

/* This number is used when no पूर्णांकerrupt has been asचिन्हित */
#घोषणा NO_IRQ			(0)

/* Total number of virq in the platक्रमm */
#घोषणा NR_IRQS		CONFIG_NR_IRQS

/* Same thing, used by the generic IRQ code */
#घोषणा NR_IRQS_LEGACY		NUM_ISA_INTERRUPTS

बाह्य irq_hw_number_t virq_to_hw(अचिन्हित पूर्णांक virq);

अटल __अंतरभूत__ पूर्णांक irq_canonicalize(पूर्णांक irq)
अणु
	वापस irq;
पूर्ण

बाह्य पूर्णांक distribute_irqs;

काष्ठा pt_regs;

#अगर defined(CONFIG_BOOKE) || defined(CONFIG_40x)
/*
 * Per-cpu stacks क्रम handling critical, debug and machine check
 * level पूर्णांकerrupts.
 */
बाह्य व्योम *critirq_ctx[NR_CPUS];
बाह्य व्योम *dbgirq_ctx[NR_CPUS];
बाह्य व्योम *mcheckirq_ctx[NR_CPUS];
#पूर्ण_अगर

/*
 * Per-cpu stacks क्रम handling hard and soft पूर्णांकerrupts.
 */
बाह्य व्योम *hardirq_ctx[NR_CPUS];
बाह्य व्योम *softirq_ctx[NR_CPUS];

बाह्य व्योम करो_IRQ(काष्ठा pt_regs *regs);
बाह्य व्योम __init init_IRQ(व्योम);
बाह्य व्योम __करो_irq(काष्ठा pt_regs *regs);

पूर्णांक irq_choose_cpu(स्थिर काष्ठा cpumask *mask);

#पूर्ण_अगर /* _ASM_IRQ_H */
#पूर्ण_अगर /* __KERNEL__ */
