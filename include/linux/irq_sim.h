<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2017-2018 Bartosz Golaszewski <brgl@bgdev.pl>
 * Copyright (C) 2020 Bartosz Golaszewski <bgolaszewski@baylibre.com>
 */

#अगर_अघोषित _LINUX_IRQ_SIM_H
#घोषणा _LINUX_IRQ_SIM_H

#समावेश <linux/device.h>
#समावेश <linux/fwnode.h>
#समावेश <linux/irqकरोमुख्य.h>

/*
 * Provides a framework क्रम allocating simulated पूर्णांकerrupts which can be
 * requested like normal irqs and enqueued from process context.
 */

काष्ठा irq_करोमुख्य *irq_करोमुख्य_create_sim(काष्ठा fwnode_handle *fwnode,
					 अचिन्हित पूर्णांक num_irqs);
काष्ठा irq_करोमुख्य *devm_irq_करोमुख्य_create_sim(काष्ठा device *dev,
					      काष्ठा fwnode_handle *fwnode,
					      अचिन्हित पूर्णांक num_irqs);
व्योम irq_करोमुख्य_हटाओ_sim(काष्ठा irq_करोमुख्य *करोमुख्य);

#पूर्ण_अगर /* _LINUX_IRQ_SIM_H */
