<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arch/mach-ixp4xx/vulcan-pci.c
 *
 * Vulcan board-level PCI initialization
 *
 * Copyright (C) 2010 Marc Zyngier <maz@misterjones.org>
 *
 * based on ixdp425-pci.c:
 *	Copyright (C) 2002 Intel Corporation.
 *	Copyright (C) 2003-2004 MontaVista Software, Inc.
 */

#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "irqs.h"

/* PCI controller GPIO to IRQ pin mappings */
#घोषणा INTA	2
#घोषणा INTB	3

व्योम __init vulcan_pci_preinit(व्योम)
अणु
#अगर_अघोषित CONFIG_IXP4XX_INसूचीECT_PCI
	/*
	 * Cardbus bridge wants way more than the SoC can actually offer,
	 * and leaves the whole PCI bus in a mess. Artअगरicially limit it
	 * to 8MB per region. Of course indirect mode करोesn't have this
	 * limitation...
	 */
	pci_cardbus_mem_size = SZ_8M;
	pr_info("Vulcan PCI: limiting CardBus memory size to %dMB\n",
		(पूर्णांक)(pci_cardbus_mem_size >> 20));
#पूर्ण_अगर
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTA), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTB), IRQ_TYPE_LEVEL_LOW);
	ixp4xx_pci_preinit();
पूर्ण

अटल पूर्णांक __init vulcan_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अगर (slot == 1)
		वापस IXP4XX_GPIO_IRQ(INTA);

	अगर (slot == 2)
		वापस IXP4XX_GPIO_IRQ(INTB);

	वापस -1;
पूर्ण

काष्ठा hw_pci vulcan_pci __initdata = अणु
	.nr_controllers	= 1,
	.ops		= &ixp4xx_ops,
	.preinit	= vulcan_pci_preinit,
	.setup		= ixp4xx_setup,
	.map_irq	= vulcan_map_irq,
पूर्ण;

पूर्णांक __init vulcan_pci_init(व्योम)
अणु
	अगर (machine_is_arcom_vulcan())
		pci_common_init(&vulcan_pci);
	वापस 0;
पूर्ण

subsys_initcall(vulcan_pci_init);
