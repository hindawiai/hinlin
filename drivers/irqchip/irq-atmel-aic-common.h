<शैली गुरु>
/*
 * Aपंचांगel AT91 common AIC (Advanced Interrupt Controller) header file
 *
 *  Copyright (C) 2004 SAN People
 *  Copyright (C) 2004 ATMEL
 *  Copyright (C) Rick Bronson
 *  Copyright (C) 2014 Free Electrons
 *
 *  Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __IRQ_ATMEL_AIC_COMMON_H
#घोषणा __IRQ_ATMEL_AIC_COMMON_H


पूर्णांक aic_common_set_type(काष्ठा irq_data *d, अचिन्हित type, अचिन्हित *val);

व्योम aic_common_set_priority(पूर्णांक priority, अचिन्हित *val);

पूर्णांक aic_common_irq_करोमुख्य_xlate(काष्ठा irq_करोमुख्य *d,
				काष्ठा device_node *ctrlr,
				स्थिर u32 *पूर्णांकspec,
				अचिन्हित पूर्णांक पूर्णांकsize,
				irq_hw_number_t *out_hwirq,
				अचिन्हित पूर्णांक *out_type);

काष्ठा irq_करोमुख्य *__init aic_common_of_init(काष्ठा device_node *node,
					     स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					     स्थिर अक्षर *name, पूर्णांक nirqs,
					     स्थिर काष्ठा of_device_id *matches);

व्योम __init aic_common_rtc_irq_fixup(व्योम);

व्योम __init aic_common_rtt_irq_fixup(व्योम);

#पूर्ण_अगर /* __IRQ_ATMEL_AIC_COMMON_H */
