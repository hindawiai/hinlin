<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  fixup-tb0219.c, The TANBAC TB0219 specअगरic PCI fixups.
 *
 *  Copyright (C) 2003	Megasolution Inc. <matsu@megasolution.jp>
 *  Copyright (C) 2004-2005  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/vr41xx/tb0219.h>

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक irq = -1;

	चयन (slot) अणु
	हाल 12:
		irq = TB0219_PCI_SLOT1_IRQ;
		अवरोध;
	हाल 13:
		irq = TB0219_PCI_SLOT2_IRQ;
		अवरोध;
	हाल 14:
		irq = TB0219_PCI_SLOT3_IRQ;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस irq;
पूर्ण

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण
