<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IRQNR_H
#घोषणा _LINUX_IRQNR_H

#समावेश <uapi/linux/irqnr.h>


बाह्य पूर्णांक nr_irqs;
बाह्य काष्ठा irq_desc *irq_to_desc(अचिन्हित पूर्णांक irq);
अचिन्हित पूर्णांक irq_get_next_irq(अचिन्हित पूर्णांक offset);

# define क्रम_each_irq_desc(irq, desc)					\
	क्रम (irq = 0, desc = irq_to_desc(irq); irq < nr_irqs;		\
	     irq++, desc = irq_to_desc(irq))				\
		अगर (!desc)						\
			;						\
		अन्यथा


# define क्रम_each_irq_desc_reverse(irq, desc)				\
	क्रम (irq = nr_irqs - 1, desc = irq_to_desc(irq); irq >= 0;	\
	     irq--, desc = irq_to_desc(irq))				\
		अगर (!desc)						\
			;						\
		अन्यथा

# define क्रम_each_active_irq(irq)			\
	क्रम (irq = irq_get_next_irq(0); irq < nr_irqs;	\
	     irq = irq_get_next_irq(irq + 1))

#घोषणा क्रम_each_irq_nr(irq)                   \
       क्रम (irq = 0; irq < nr_irqs; irq++)

#पूर्ण_अगर
