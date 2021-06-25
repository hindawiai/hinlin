<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_HARसूचीQ_H
#घोषणा _ASM_IA64_HARसूचीQ_H

/*
 * Modअगरied 1998-2002, 2004 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */

/*
 * No irq_cpustat_t क्रम IA-64.  The data is held in the per-CPU data काष्ठाure.
 */

#घोषणा __ARCH_IRQ_STAT	1

#घोषणा local_softirq_pending_ref	ia64_cpu_info.softirq_pending

#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/processor.h>

बाह्य व्योम __iomem *ipi_base_addr;

व्योम ack_bad_irq(अचिन्हित पूर्णांक irq);

#पूर्ण_अगर /* _ASM_IA64_HARसूचीQ_H */
