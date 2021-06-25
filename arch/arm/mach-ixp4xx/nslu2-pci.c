<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-ixp4xx/nslu2-pci.c
 *
 * NSLU2 board-level PCI initialization
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

व्योम __init nslu2_pci_preinit(व्योम)
अणु
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTA), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTB), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTC), IRQ_TYPE_LEVEL_LOW);
	ixp4xx_pci_preinit();
पूर्ण

अटल पूर्णांक __init nslu2_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल पूर्णांक pci_irq_table[IRQ_LINES] = अणु
		IXP4XX_GPIO_IRQ(INTA),
		IXP4XX_GPIO_IRQ(INTB),
		IXP4XX_GPIO_IRQ(INTC),
	पूर्ण;

	अगर (slot >= 1 && slot <= MAX_DEV && pin >= 1 && pin <= IRQ_LINES)
		वापस pci_irq_table[(slot + pin - 2) % IRQ_LINES];

	वापस -1;
पूर्ण

काष्ठा hw_pci __initdata nslu2_pci = अणु
	.nr_controllers = 1,
	.ops		= &ixp4xx_ops,
	.preinit	= nslu2_pci_preinit,
	.setup		= ixp4xx_setup,
	.map_irq	= nslu2_map_irq,
पूर्ण;

पूर्णांक __init nslu2_pci_init(व्योम) /* monkey see, monkey करो */
अणु
	अगर (machine_is_nslu2())
		pci_common_init(&nslu2_pci);

	वापस 0;
पूर्ण

subsys_initcall(nslu2_pci_init);
