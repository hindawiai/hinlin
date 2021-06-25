<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* hardirq.h: PA-RISC hard IRQ support.
 *
 * Copyright (C) 2001 Matthew Wilcox <matthew@wil.cx>
 * Copyright (C) 2013 Helge Deller <deller@gmx.de>
 */

#अगर_अघोषित _PARISC_HARसूचीQ_H
#घोषणा _PARISC_HARसूचीQ_H

#समावेश <linux/cache.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/irq.h>

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक __softirq_pending;
	अचिन्हित पूर्णांक kernel_stack_usage;
	अचिन्हित पूर्णांक irq_stack_usage;
#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक irq_resched_count;
	अचिन्हित पूर्णांक irq_call_count;
#पूर्ण_अगर
	अचिन्हित पूर्णांक irq_unaligned_count;
	अचिन्हित पूर्णांक irq_fpassist_count;
	अचिन्हित पूर्णांक irq_tlb_count;
पूर्ण ____cacheline_aligned irq_cpustat_t;

DECLARE_PER_CPU_SHARED_ALIGNED(irq_cpustat_t, irq_stat);

#घोषणा __ARCH_IRQ_STAT
#घोषणा inc_irq_stat(member)	this_cpu_inc(irq_stat.member)
#घोषणा __inc_irq_stat(member)	__this_cpu_inc(irq_stat.member)
#घोषणा ack_bad_irq(irq) WARN(1, "unexpected IRQ trap at vector %02x\n", irq)

#पूर्ण_अगर /* _PARISC_HARसूचीQ_H */
