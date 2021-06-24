<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arch/mach-ixp4xx/wg302v2-pci.c
 *
 * PCI setup routines क्रम the Netgear WG302 v2 and WAG302 v2
 *
 * Copyright (C) 2007 Imre Kaloz <kaloz@खोलोwrt.org>
 *
 * based on coyote-pci.c:
 *	Copyright (C) 2002 Jungo Software Technologies.
 *	Copyright (C) 2003 MontaVista Software, Inc.
 *
 * Maपूर्णांकainer: Imre Kaloz <kaloz@खोलोwrt.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>

#समावेश <यंत्र/mach/pci.h>

#समावेश "irqs.h"

व्योम __init wg302v2_pci_preinit(व्योम)
अणु
	irq_set_irq_type(IRQ_IXP4XX_GPIO8, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IRQ_IXP4XX_GPIO9, IRQ_TYPE_LEVEL_LOW);

	ixp4xx_pci_preinit();
पूर्ण

अटल पूर्णांक __init wg302v2_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अगर (slot == 1)
		वापस IRQ_IXP4XX_GPIO8;
	अन्यथा अगर (slot == 2)
		वापस IRQ_IXP4XX_GPIO9;
	अन्यथा वापस -1;
पूर्ण

काष्ठा hw_pci wg302v2_pci __initdata = अणु
	.nr_controllers = 1,
	.ops = &ixp4xx_ops,
	.preinit =        wg302v2_pci_preinit,
	.setup =          ixp4xx_setup,
	.map_irq =        wg302v2_map_irq,
पूर्ण;

पूर्णांक __init wg302v2_pci_init(व्योम)
अणु
	अगर (machine_is_wg302v2())
		pci_common_init(&wg302v2_pci);
	वापस 0;
पूर्ण

subsys_initcall(wg302v2_pci_init);
