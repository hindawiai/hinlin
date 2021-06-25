<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/linux/irqchip/arm-gic-common.h
 *
 * Copyright (C) 2016 ARM Limited, All Rights Reserved.
 */
#अगर_अघोषित __LINUX_IRQCHIP_ARM_GIC_COMMON_H
#घोषणा __LINUX_IRQCHIP_ARM_GIC_COMMON_H

#समावेश <linux/types.h>
#समावेश <linux/ioport.h>

#घोषणा GICD_INT_DEF_PRI		0xa0
#घोषणा GICD_INT_DEF_PRI_X4		((GICD_INT_DEF_PRI << 24) |\
					(GICD_INT_DEF_PRI << 16) |\
					(GICD_INT_DEF_PRI << 8) |\
					GICD_INT_DEF_PRI)

क्रमागत gic_type अणु
	GIC_V2,
	GIC_V3,
पूर्ण;

काष्ठा gic_kvm_info अणु
	/* GIC type */
	क्रमागत gic_type	type;
	/* Virtual CPU पूर्णांकerface */
	काष्ठा resource vcpu;
	/* Interrupt number */
	अचिन्हित पूर्णांक	मुख्यt_irq;
	/* Virtual control पूर्णांकerface */
	काष्ठा resource vctrl;
	/* vlpi support */
	bool		has_v4;
	/* rvpeid support */
	bool		has_v4_1;
पूर्ण;

स्थिर काष्ठा gic_kvm_info *gic_get_kvm_info(व्योम);

काष्ठा irq_करोमुख्य;
काष्ठा fwnode_handle;
पूर्णांक gicv2m_init(काष्ठा fwnode_handle *parent_handle,
		काष्ठा irq_करोमुख्य *parent);

#पूर्ण_अगर /* __LINUX_IRQCHIP_ARM_GIC_COMMON_H */
