<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-ixp4xx/gtwx5715-pci.c
 *
 * Gemtek GTWX5715 (Linksys WRV54G) board setup
 *
 * Copyright (C) 2004 George T. Joseph
 * Derived from Coyote
 */

#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach/pci.h>

#समावेश "irqs.h"

#घोषणा SLOT0_DEVID	0
#घोषणा SLOT1_DEVID	1
#घोषणा INTA		10 /* slot 1 has INTA and INTB crossed */
#घोषणा INTB		11

/*
 * Slot 0 isn't actually populated with a card connector but
 * we initialize it anyway in हाल a future version has the
 * slot populated or someone with good soldering sसमाप्तs has
 * some मुक्त समय.
 */
व्योम __init gtwx5715_pci_preinit(व्योम)
अणु
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTA), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTB), IRQ_TYPE_LEVEL_LOW);
	ixp4xx_pci_preinit();
पूर्ण


अटल पूर्णांक __init gtwx5715_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक rc = -1;

	अगर ((slot == SLOT0_DEVID && pin == 1) ||
	    (slot == SLOT1_DEVID && pin == 2))
		rc = IXP4XX_GPIO_IRQ(INTA);
	अन्यथा अगर ((slot == SLOT0_DEVID && pin == 2) ||
		 (slot == SLOT1_DEVID && pin == 1))
		rc = IXP4XX_GPIO_IRQ(INTB);

	prपूर्णांकk(KERN_INFO "%s: Mapped slot %d pin %d to IRQ %d\n",
	       __func__, slot, pin, rc);
	वापस rc;
पूर्ण

काष्ठा hw_pci gtwx5715_pci __initdata = अणु
	.nr_controllers = 1,
	.ops		= &ixp4xx_ops,
	.preinit =        gtwx5715_pci_preinit,
	.setup =          ixp4xx_setup,
	.map_irq =        gtwx5715_map_irq,
पूर्ण;

पूर्णांक __init gtwx5715_pci_init(व्योम)
अणु
	अगर (machine_is_gtwx5715())
		pci_common_init(&gtwx5715_pci);

	वापस 0;
पूर्ण

subsys_initcall(gtwx5715_pci_init);
