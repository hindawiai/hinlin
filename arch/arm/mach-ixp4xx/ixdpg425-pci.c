<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-ixp4xx/ixdpg425-pci.c
 *
 * PCI setup routines क्रम Intel IXDPG425 Platक्रमm
 *
 * Copyright (C) 2004 MontaVista Softwrae, Inc.
 *
 * Maपूर्णांकainer: Deepak Saxena <dsaxena@plनिकासy.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>

#समावेश <यंत्र/mach/pci.h>

#समावेश "irqs.h"

व्योम __init ixdpg425_pci_preinit(व्योम)
अणु
	irq_set_irq_type(IRQ_IXP4XX_GPIO6, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IRQ_IXP4XX_GPIO7, IRQ_TYPE_LEVEL_LOW);

	ixp4xx_pci_preinit();
पूर्ण

अटल पूर्णांक __init ixdpg425_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अगर (slot == 12 || slot == 13)
		वापस IRQ_IXP4XX_GPIO7;
	अन्यथा अगर (slot == 14)
		वापस IRQ_IXP4XX_GPIO6;
	अन्यथा वापस -1;
पूर्ण

काष्ठा hw_pci ixdpg425_pci __initdata = अणु
	.nr_controllers = 1,
	.ops		= &ixp4xx_ops,
	.preinit =        ixdpg425_pci_preinit,
	.setup =          ixp4xx_setup,
	.map_irq =        ixdpg425_map_irq,
पूर्ण;

पूर्णांक __init ixdpg425_pci_init(व्योम)
अणु
	अगर (machine_is_ixdpg425())
		pci_common_init(&ixdpg425_pci);
	वापस 0;
पूर्ण

subsys_initcall(ixdpg425_pci_init);
