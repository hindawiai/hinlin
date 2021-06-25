<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/drivers/pci/ops-snapgear.c
 *
 * Author:  David McCullough <davidm@snapgear.com>
 *
 * Ported to new API by Paul Mundt <lethal@linux-sh.org>
 *
 * Highly leveraged from pci-bigsur.c, written by Dustin McIntire.
 *
 * PCI initialization क्रम the SnapGear boards
 */
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश "pci-sh4.h"

पूर्णांक pcibios_map_platक्रमm_irq(स्थिर काष्ठा pci_dev *pdev, u8 slot, u8 pin)
अणु
	पूर्णांक irq = -1;

	चयन (slot) अणु
	हाल 8:  /* the PCI bridge */ अवरोध;
	हाल 11: irq = evt2irq(0x300); अवरोध; /* USB    */
	हाल 12: irq = evt2irq(0x360); अवरोध; /* PCMCIA */
	हाल 13: irq = evt2irq(0x2a0); अवरोध; /* eth0   */
	हाल 14: irq = evt2irq(0x300); अवरोध; /* eth1   */
	हाल 15: irq = evt2irq(0x360); अवरोध; /* safenet (unused) */
	पूर्ण

	prपूर्णांकk("PCI: Mapping SnapGear IRQ for slot %d, pin %c to irq %d\n",
	       slot, pin - 1 + 'A', irq);

	वापस irq;
पूर्ण
