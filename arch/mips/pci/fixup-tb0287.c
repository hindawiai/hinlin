<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  fixup-tb0287.c, The TANBAC TB0287 specअगरic PCI fixups.
 *
 *  Copyright (C) 2005	Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/vr41xx/tb0287.h>

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अचिन्हित अक्षर bus;
	पूर्णांक irq = -1;

	bus = dev->bus->number;
	अगर (bus == 0) अणु
		चयन (slot) अणु
		हाल 16:
			irq = TB0287_SM501_IRQ;
			अवरोध;
		हाल 17:
			irq = TB0287_SIL680A_IRQ;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (bus == 1) अणु
		चयन (PCI_SLOT(dev->devfn)) अणु
		हाल 0:
			irq = TB0287_PCI_SLOT_IRQ;
			अवरोध;
		हाल 2:
		हाल 3:
			irq = TB0287_RTL8110_IRQ;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (bus > 1) अणु
		irq = TB0287_PCI_SLOT_IRQ;
	पूर्ण

	वापस irq;
पूर्ण

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण
