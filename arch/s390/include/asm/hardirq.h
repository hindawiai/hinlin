<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *    Copyright IBM Corp. 1999, 2000
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),
 *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)
 *
 *  Derived from "include/asm-i386/hardirq.h"
 */

#अगर_अघोषित __ASM_HARसूचीQ_H
#घोषणा __ASM_HARसूचीQ_H

#समावेश <यंत्र/lowcore.h>

#घोषणा local_softirq_pending() (S390_lowcore.softirq_pending)
#घोषणा set_softirq_pending(x) (S390_lowcore.softirq_pending = (x))
#घोषणा or_softirq_pending(x)  (S390_lowcore.softirq_pending |= (x))

#घोषणा __ARCH_IRQ_STAT
#घोषणा __ARCH_IRQ_EXIT_IRQS_DISABLED

अटल अंतरभूत व्योम ack_bad_irq(अचिन्हित पूर्णांक irq)
अणु
	prपूर्णांकk(KERN_CRIT "unexpected IRQ trap at vector %02x\n", irq);
पूर्ण

#पूर्ण_अगर /* __ASM_HARसूचीQ_H */
