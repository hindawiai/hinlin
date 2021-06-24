<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-ixp4xx/miccpt-pci.c
 *
 * MICCPT board-level PCI initialization
 *
 * Copyright (C) 2002 Intel Corporation.
 * Copyright (C) 2003-2004 MontaVista Software, Inc.
 * Copyright (C) 2006 OMICRON electronics GmbH
 *
 * Author: Michael Jochum <michael.jochum@omicron.at>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <यंत्र/irq.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "irqs.h"

#घोषणा MAX_DEV		4
#घोषणा IRQ_LINES	4

/* PCI controller GPIO to IRQ pin mappings */
#घोषणा INTA		1
#घोषणा INTB		2
#घोषणा INTC		3
#घोषणा INTD		4


व्योम __init miccpt_pci_preinit(व्योम)
अणु
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTA), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTB), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTC), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTD), IRQ_TYPE_LEVEL_LOW);
	ixp4xx_pci_preinit();
पूर्ण

अटल पूर्णांक __init miccpt_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल पूर्णांक pci_irq_table[IRQ_LINES] = अणु
		IXP4XX_GPIO_IRQ(INTA),
		IXP4XX_GPIO_IRQ(INTB),
		IXP4XX_GPIO_IRQ(INTC),
		IXP4XX_GPIO_IRQ(INTD)
	पूर्ण;

	अगर (slot >= 1 && slot <= MAX_DEV && pin >= 1 && pin <= IRQ_LINES)
		वापस pci_irq_table[(slot + pin - 2) % 4];

	वापस -1;
पूर्ण

काष्ठा hw_pci miccpt_pci __initdata = अणु
	.nr_controllers = 1,
	.ops		= &ixp4xx_ops,
	.preinit	= miccpt_pci_preinit,
	.setup		= ixp4xx_setup,
	.map_irq	= miccpt_map_irq,
पूर्ण;

पूर्णांक __init miccpt_pci_init(व्योम)
अणु
	अगर (machine_is_miccpt())
		pci_common_init(&miccpt_pci);
	वापस 0;
पूर्ण

subsys_initcall(miccpt_pci_init);
