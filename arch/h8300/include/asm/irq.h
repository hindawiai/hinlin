<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _H8300_IRQ_H_
#घोषणा _H8300_IRQ_H_

#समावेश <linux/irqchip.h>

#अगर defined(CONFIG_CPU_H8300H)
#घोषणा NR_IRQS 64
#घोषणा IRQ_CHIP h8300h_irq_chip
#घोषणा EXT_IRQ0 12
#घोषणा EXT_IRQS 6
#या_अगर defined(CONFIG_CPU_H8S)
#घोषणा NR_IRQS 128
#घोषणा IRQ_CHIP h8s_irq_chip
#घोषणा EXT_IRQ0 16
#घोषणा EXT_IRQS 16
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक irq_canonicalize(पूर्णांक irq)
अणु
	वापस irq;
पूर्ण

व्योम h8300_init_ipr(व्योम);
बाह्य काष्ठा irq_chip h8300h_irq_chip;
बाह्य काष्ठा irq_chip h8s_irq_chip;
#पूर्ण_अगर /* _H8300_IRQ_H_ */
