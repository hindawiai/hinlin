<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2002 ARM Limited, All Rights Reserved.
 */

#अगर_अघोषित _IRQ_GIC_COMMON_H
#घोषणा _IRQ_GIC_COMMON_H

#समावेश <linux/of.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip/arm-gic-common.h>

काष्ठा gic_quirk अणु
	स्थिर अक्षर *desc;
	स्थिर अक्षर *compatible;
	bool (*init)(व्योम *data);
	u32 iidr;
	u32 mask;
पूर्ण;

पूर्णांक gic_configure_irq(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक type,
                       व्योम __iomem *base, व्योम (*sync_access)(व्योम));
व्योम gic_dist_config(व्योम __iomem *base, पूर्णांक gic_irqs,
		     व्योम (*sync_access)(व्योम));
व्योम gic_cpu_config(व्योम __iomem *base, पूर्णांक nr, व्योम (*sync_access)(व्योम));
व्योम gic_enable_quirks(u32 iidr, स्थिर काष्ठा gic_quirk *quirks,
		व्योम *data);
व्योम gic_enable_of_quirks(स्थिर काष्ठा device_node *np,
			  स्थिर काष्ठा gic_quirk *quirks, व्योम *data);

व्योम gic_set_kvm_info(स्थिर काष्ठा gic_kvm_info *info);

#पूर्ण_अगर /* _IRQ_GIC_COMMON_H */
