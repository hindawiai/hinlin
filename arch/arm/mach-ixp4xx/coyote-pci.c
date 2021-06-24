<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-ixp4xx/coyote-pci.c
 *
 * PCI setup routines क्रम ADI Engineering Coyote platक्रमm
 *
 * Copyright (C) 2002 Jungo Software Technologies.
 * Copyright (C) 2003 MontaVista Softwrae, Inc.
 *
 * Maपूर्णांकainer: Deepak Saxena <dsaxena@mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach/pci.h>

#समावेश "irqs.h"

#घोषणा SLOT0_DEVID	14
#घोषणा SLOT1_DEVID	15

/* PCI controller GPIO to IRQ pin mappings */
#घोषणा SLOT0_INTA	6
#घोषणा SLOT1_INTA	11

व्योम __init coyote_pci_preinit(व्योम)
अणु
	irq_set_irq_type(IXP4XX_GPIO_IRQ(SLOT0_INTA), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(SLOT1_INTA), IRQ_TYPE_LEVEL_LOW);
	ixp4xx_pci_preinit();
पूर्ण

अटल पूर्णांक __init coyote_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अगर (slot == SLOT0_DEVID)
		वापस IXP4XX_GPIO_IRQ(SLOT0_INTA);
	अन्यथा अगर (slot == SLOT1_DEVID)
		वापस IXP4XX_GPIO_IRQ(SLOT1_INTA);
	अन्यथा वापस -1;
पूर्ण

काष्ठा hw_pci coyote_pci __initdata = अणु
	.nr_controllers = 1,
	.ops		= &ixp4xx_ops,
	.preinit =        coyote_pci_preinit,
	.setup =          ixp4xx_setup,
	.map_irq =        coyote_map_irq,
पूर्ण;

पूर्णांक __init coyote_pci_init(व्योम)
अणु
	अगर (machine_is_adi_coyote())
		pci_common_init(&coyote_pci);
	वापस 0;
पूर्ण

subsys_initcall(coyote_pci_init);
