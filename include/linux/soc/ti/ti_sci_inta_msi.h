<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Texas Instruments' K3 TI SCI INTA MSI helper
 *
 * Copyright (C) 2018-2019 Texas Instruments Incorporated - https://www.ti.com/
 *	Lokesh Vutla <lokeshvutla@ti.com>
 */

#अगर_अघोषित __INCLUDE_LINUX_TI_SCI_INTA_MSI_H
#घोषणा __INCLUDE_LINUX_TI_SCI_INTA_MSI_H

#समावेश <linux/msi.h>
#समावेश <linux/soc/ti/ti_sci_protocol.h>

काष्ठा irq_करोमुख्य
*ti_sci_पूर्णांकa_msi_create_irq_करोमुख्य(काष्ठा fwnode_handle *fwnode,
				   काष्ठा msi_करोमुख्य_info *info,
				   काष्ठा irq_करोमुख्य *parent);
पूर्णांक ti_sci_पूर्णांकa_msi_करोमुख्य_alloc_irqs(काष्ठा device *dev,
				      काष्ठा ti_sci_resource *res);
अचिन्हित पूर्णांक ti_sci_पूर्णांकa_msi_get_virq(काष्ठा device *dev, u32 index);
व्योम ti_sci_पूर्णांकa_msi_करोमुख्य_मुक्त_irqs(काष्ठा device *dev);
#पूर्ण_अगर /* __INCLUDE_LINUX_IRQCHIP_TI_SCI_INTA_H */
