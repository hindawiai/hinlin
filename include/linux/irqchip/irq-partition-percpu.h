<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 ARM Limited, All Rights Reserved.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#अगर_अघोषित __LINUX_IRQCHIP_IRQ_PARTITION_PERCPU_H
#घोषणा __LINUX_IRQCHIP_IRQ_PARTITION_PERCPU_H

#समावेश <linux/fwnode.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/irqकरोमुख्य.h>

काष्ठा partition_affinity अणु
	cpumask_t			mask;
	व्योम				*partition_id;
पूर्ण;

काष्ठा partition_desc;

#अगर_घोषित CONFIG_PARTITION_PERCPU
पूर्णांक partition_translate_id(काष्ठा partition_desc *desc, व्योम *partition_id);
काष्ठा partition_desc *partition_create_desc(काष्ठा fwnode_handle *fwnode,
					     काष्ठा partition_affinity *parts,
					     पूर्णांक nr_parts,
					     पूर्णांक chained_irq,
					     स्थिर काष्ठा irq_करोमुख्य_ops *ops);
काष्ठा irq_करोमुख्य *partition_get_करोमुख्य(काष्ठा partition_desc *dsc);
#अन्यथा
अटल अंतरभूत पूर्णांक partition_translate_id(काष्ठा partition_desc *desc,
					 व्योम *partition_id)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत
काष्ठा partition_desc *partition_create_desc(काष्ठा fwnode_handle *fwnode,
					     काष्ठा partition_affinity *parts,
					     पूर्णांक nr_parts,
					     पूर्णांक chained_irq,
					     स्थिर काष्ठा irq_करोमुख्य_ops *ops)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत
काष्ठा irq_करोमुख्य *partition_get_करोमुख्य(काष्ठा partition_desc *dsc)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_IRQCHIP_IRQ_PARTITION_PERCPU_H */
