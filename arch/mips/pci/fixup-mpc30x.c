<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  fixup-mpc30x.c, The Victor MP-C303/304 specअगरic PCI fixups.
 *
 *  Copyright (C) 2002,2004  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/vr41xx/mpc30x.h>

अटल स्थिर पूर्णांक पूर्णांकernal_func_irqs[] = अणु
	VRC4173_CASCADE_IRQ,
	VRC4173_AC97_IRQ,
	VRC4173_USB_IRQ,
पूर्ण;

अटल स्थिर पूर्णांक irq_tab_mpc30x[] = अणु
 [12] = VRC4173_PCMCIA1_IRQ,
 [13] = VRC4173_PCMCIA2_IRQ,
 [29] = MQ200_IRQ,
पूर्ण;

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अगर (slot == 30)
		वापस पूर्णांकernal_func_irqs[PCI_FUNC(dev->devfn)];

	वापस irq_tab_mpc30x[slot];
पूर्ण

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण
