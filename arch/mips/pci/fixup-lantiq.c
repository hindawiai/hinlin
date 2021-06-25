<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2012 John Crispin <john@phrozen.org>
 */

#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>

पूर्णांक (*ltq_pci_plat_arch_init)(काष्ठा pci_dev *dev) = शून्य;
पूर्णांक (*ltq_pci_plat_dev_init)(काष्ठा pci_dev *dev) = शून्य;

पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	अगर (ltq_pci_plat_arch_init)
		वापस ltq_pci_plat_arch_init(dev);

	अगर (ltq_pci_plat_dev_init)
		वापस ltq_pci_plat_dev_init(dev);

	वापस 0;
पूर्ण

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	वापस of_irq_parse_and_map_pci(dev, slot, pin);
पूर्ण
