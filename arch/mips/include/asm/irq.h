<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994 by Walकरोrf GMBH, written by Ralf Baechle
 * Copyright (C) 1995, 96, 97, 98, 99, 2000, 01, 02, 03 by Ralf Baechle
 */
#अगर_अघोषित _ASM_IRQ_H
#घोषणा _ASM_IRQ_H

#समावेश <linux/linkage.h>
#समावेश <linux/smp.h>
#समावेश <linux/irqकरोमुख्य.h>

#समावेश <यंत्र/mipsmtregs.h>

#समावेश <irq.h>

#घोषणा IRQ_STACK_SIZE			THREAD_SIZE
#घोषणा IRQ_STACK_START			(IRQ_STACK_SIZE - 16)

बाह्य व्योम __init init_IRQ(व्योम);
बाह्य व्योम *irq_stack[NR_CPUS];

/*
 * The highest address on the IRQ stack contains a dummy frame put करोwn in
 * genex.S (handle_पूर्णांक & except_vec_vi_handler) which is काष्ठाured as follows:
 *
 *   top ------------
 *       | task sp  | <- irq_stack[cpu] + IRQ_STACK_START
 *       ------------
 *       |          | <- First frame of IRQ context
 *       ------------
 *
 * task sp holds a copy of the task stack poपूर्णांकer where the काष्ठा pt_regs
 * from exception entry can be found.
 */

अटल अंतरभूत bool on_irq_stack(पूर्णांक cpu, अचिन्हित दीर्घ sp)
अणु
	अचिन्हित दीर्घ low = (अचिन्हित दीर्घ)irq_stack[cpu];
	अचिन्हित दीर्घ high = low + IRQ_STACK_SIZE;

	वापस (low <= sp && sp <= high);
पूर्ण

#अगर_घोषित CONFIG_I8259
अटल अंतरभूत पूर्णांक irq_canonicalize(पूर्णांक irq)
अणु
	वापस ((irq == I8259A_IRQ_BASE + 2) ? I8259A_IRQ_BASE + 9 : irq);
पूर्ण
#अन्यथा
#घोषणा irq_canonicalize(irq) (irq)	/* Sane hardware, sane code ... */
#पूर्ण_अगर

यंत्रlinkage व्योम plat_irq_dispatch(व्योम);

बाह्य व्योम करो_IRQ(अचिन्हित पूर्णांक irq);

बाह्य व्योम arch_init_irq(व्योम);
बाह्य व्योम spurious_पूर्णांकerrupt(व्योम);

बाह्य पूर्णांक allocate_irqno(व्योम);
बाह्य व्योम alloc_legacy_irqno(व्योम);
बाह्य व्योम मुक्त_irqno(अचिन्हित पूर्णांक irq);

/*
 * Beक्रमe R2 the समयr and perक्रमmance counter पूर्णांकerrupts were both fixed to
 * IE7.	 Since R2 their number has to be पढ़ो from the c0_पूर्णांकctl रेजिस्टर.
 */
#घोषणा CP0_LEGACY_COMPARE_IRQ 7
#घोषणा CP0_LEGACY_PERFCNT_IRQ 7

बाह्य पूर्णांक cp0_compare_irq;
बाह्य पूर्णांक cp0_compare_irq_shअगरt;
बाह्य पूर्णांक cp0_perfcount_irq;
बाह्य पूर्णांक cp0_fdc_irq;

बाह्य पूर्णांक get_c0_fdc_पूर्णांक(व्योम);

व्योम arch_trigger_cpumask_backtrace(स्थिर काष्ठा cpumask *mask,
				    bool exclude_self);
#घोषणा arch_trigger_cpumask_backtrace arch_trigger_cpumask_backtrace

#पूर्ण_अगर /* _ASM_IRQ_H */
