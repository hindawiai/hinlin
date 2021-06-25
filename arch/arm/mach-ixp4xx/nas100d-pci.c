<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-ixp4xx/nas100d-pci.c
 *
 * NAS 100d board-level PCI initialization
 *
 * based on ixdp425-pci.c:
 *	Copyright (C) 2002 Intel Corporation.
 *	Copyright (C) 2003-2004 MontaVista Software, Inc.
 *
 * Maपूर्णांकainer: http://www.nslu2-linux.org/
 */

#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "irqs.h"

#घोषणा MAX_DEV		3
#घोषणा IRQ_LINES	3

/* PCI controller GPIO to IRQ pin mappings */
#घोषणा INTA		11
#घोषणा INTB		10
#घोषणा INTC		9
#घोषणा INTD		8
#घोषणा INTE		7

व्योम __init nas100d_pci_preinit(व्योम)
अणु
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTA), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTB), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTC), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTD), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTE), IRQ_TYPE_LEVEL_LOW);
	ixp4xx_pci_preinit();
पूर्ण

अटल पूर्णांक __init nas100d_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल पूर्णांक pci_irq_table[MAX_DEV][IRQ_LINES] = अणु
		अणु IXP4XX_GPIO_IRQ(INTA), -1, -1 पूर्ण,
		अणु IXP4XX_GPIO_IRQ(INTB), -1, -1 पूर्ण,
		अणु IXP4XX_GPIO_IRQ(INTC), IXP4XX_GPIO_IRQ(INTD),
		  IXP4XX_GPIO_IRQ(INTE) पूर्ण,
	पूर्ण;

	अगर (slot >= 1 && slot <= MAX_DEV && pin >= 1 && pin <= IRQ_LINES)
		वापस pci_irq_table[slot - 1][pin - 1];

	वापस -1;
पूर्ण

काष्ठा hw_pci __initdata nas100d_pci = अणु
	.nr_controllers = 1,
	.ops		= &ixp4xx_ops,
	.preinit	= nas100d_pci_preinit,
	.setup		= ixp4xx_setup,
	.map_irq	= nas100d_map_irq,
पूर्ण;

पूर्णांक __init nas100d_pci_init(व्योम)
अणु
	अगर (machine_is_nas100d())
		pci_common_init(&nas100d_pci);

	वापस 0;
पूर्ण

subsys_initcall(nas100d_pci_init);
