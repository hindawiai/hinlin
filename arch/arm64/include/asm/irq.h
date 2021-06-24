<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_IRQ_H
#घोषणा __ASM_IRQ_H

#अगर_अघोषित __ASSEMBLER__

#समावेश <यंत्र-generic/irq.h>

काष्ठा pt_regs;

पूर्णांक set_handle_irq(व्योम (*handle_irq)(काष्ठा pt_regs *));
#घोषणा set_handle_irq	set_handle_irq
पूर्णांक set_handle_fiq(व्योम (*handle_fiq)(काष्ठा pt_regs *));

अटल अंतरभूत पूर्णांक nr_legacy_irqs(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLER__ */
#पूर्ण_अगर
