<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Chained IRQ handlers support.
 *
 * Copyright (C) 2011 ARM Ltd.
 */
#अगर_अघोषित __IRQCHIP_CHAINED_IRQ_H
#घोषणा __IRQCHIP_CHAINED_IRQ_H

#समावेश <linux/irq.h>

/*
 * Entry/निकास functions क्रम chained handlers where the primary IRQ chip
 * may implement either fasteoi or level-trigger flow control.
 */
अटल अंतरभूत व्योम chained_irq_enter(काष्ठा irq_chip *chip,
				     काष्ठा irq_desc *desc)
अणु
	/* FastEOI controllers require no action on entry. */
	अगर (chip->irq_eoi)
		वापस;

	अगर (chip->irq_mask_ack) अणु
		chip->irq_mask_ack(&desc->irq_data);
	पूर्ण अन्यथा अणु
		chip->irq_mask(&desc->irq_data);
		अगर (chip->irq_ack)
			chip->irq_ack(&desc->irq_data);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम chained_irq_निकास(काष्ठा irq_chip *chip,
				    काष्ठा irq_desc *desc)
अणु
	अगर (chip->irq_eoi)
		chip->irq_eoi(&desc->irq_data);
	अन्यथा
		chip->irq_unmask(&desc->irq_data);
पूर्ण

#पूर्ण_अगर /* __IRQCHIP_CHAINED_IRQ_H */
