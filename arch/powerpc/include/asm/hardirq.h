<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_HARसूचीQ_H
#घोषणा _ASM_POWERPC_HARसूचीQ_H

#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/irq.h>

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक __softirq_pending;
	अचिन्हित पूर्णांक समयr_irqs_event;
	अचिन्हित पूर्णांक broadcast_irqs_event;
	अचिन्हित पूर्णांक समयr_irqs_others;
	अचिन्हित पूर्णांक pmu_irqs;
	अचिन्हित पूर्णांक mce_exceptions;
	अचिन्हित पूर्णांक spurious_irqs;
	अचिन्हित पूर्णांक sreset_irqs;
#अगर_घोषित CONFIG_PPC_WATCHDOG
	अचिन्हित पूर्णांक soft_nmi_irqs;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_DOORBELL
	अचिन्हित पूर्णांक करोorbell_irqs;
#पूर्ण_अगर
पूर्ण ____cacheline_aligned irq_cpustat_t;

DECLARE_PER_CPU_SHARED_ALIGNED(irq_cpustat_t, irq_stat);

#घोषणा __ARCH_IRQ_STAT
#घोषणा __ARCH_IRQ_EXIT_IRQS_DISABLED

अटल अंतरभूत व्योम ack_bad_irq(अचिन्हित पूर्णांक irq)
अणु
	prपूर्णांकk(KERN_CRIT "unexpected IRQ trap at vector %02x\n", irq);
पूर्ण

बाह्य u64 arch_irq_stat_cpu(अचिन्हित पूर्णांक cpu);
#घोषणा arch_irq_stat_cpu	arch_irq_stat_cpu

#पूर्ण_अगर /* _ASM_POWERPC_HARसूचीQ_H */
