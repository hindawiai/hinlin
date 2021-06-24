<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Nothing to see here yet
 */
#अगर_अघोषित _ARCH_ARM_HW_IRQ_H
#घोषणा _ARCH_ARM_HW_IRQ_H

अटल अंतरभूत व्योम ack_bad_irq(पूर्णांक irq)
अणु
	बाह्य अचिन्हित दीर्घ irq_err_count;
	irq_err_count++;
	pr_crit("unexpected IRQ trap at vector %02x\n", irq);
पूर्ण

#घोषणा ARCH_IRQ_INIT_FLAGS	(IRQ_NOREQUEST | IRQ_NOPROBE)

#पूर्ण_अगर
