<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_HARसूचीQ_H
#घोषणा __ASM_GENERIC_HARसूचीQ_H

#समावेश <linux/cache.h>
#समावेश <linux/thपढ़ोs.h>

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक __softirq_pending;
#अगर_घोषित ARCH_WANTS_NMI_IRQSTAT
	अचिन्हित पूर्णांक __nmi_count;
#पूर्ण_अगर
पूर्ण ____cacheline_aligned irq_cpustat_t;

DECLARE_PER_CPU_ALIGNED(irq_cpustat_t, irq_stat);

#समावेश <linux/irq.h>

#अगर_अघोषित ack_bad_irq
अटल अंतरभूत व्योम ack_bad_irq(अचिन्हित पूर्णांक irq)
अणु
	prपूर्णांकk(KERN_CRIT "unexpected IRQ trap at vector %02x\n", irq);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_GENERIC_HARसूचीQ_H */
