<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2006-2007, Michael Ellerman, IBM Corporation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/msi.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/machdep.h>

पूर्णांक arch_setup_msi_irqs(काष्ठा pci_dev *dev, पूर्णांक nvec, पूर्णांक type)
अणु
	काष्ठा pci_controller *phb = pci_bus_to_host(dev->bus);

	अगर (!phb->controller_ops.setup_msi_irqs ||
	    !phb->controller_ops.tearकरोwn_msi_irqs) अणु
		pr_debug("msi: Platform doesn't provide MSI callbacks.\n");
		वापस -ENOSYS;
	पूर्ण

	/* PowerPC करोesn't support multiple MSI yet */
	अगर (type == PCI_CAP_ID_MSI && nvec > 1)
		वापस 1;

	वापस phb->controller_ops.setup_msi_irqs(dev, nvec, type);
पूर्ण

व्योम arch_tearकरोwn_msi_irqs(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *phb = pci_bus_to_host(dev->bus);

	/*
	 * We can be called even when arch_setup_msi_irqs() वापसs -ENOSYS,
	 * so check the poपूर्णांकer again.
	 */
	अगर (phb->controller_ops.tearकरोwn_msi_irqs)
		phb->controller_ops.tearकरोwn_msi_irqs(dev);
पूर्ण
