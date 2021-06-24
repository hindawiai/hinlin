<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2019 Lorenzo Bianconi <lorenzo@kernel.org>
 */

#समावेश "mt76.h"
#समावेश <linux/pci.h>

व्योम mt76_pci_disable_aspm(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *parent = pdev->bus->self;
	u16 aspm_conf, parent_aspm_conf = 0;

	pcie_capability_पढ़ो_word(pdev, PCI_EXP_LNKCTL, &aspm_conf);
	aspm_conf &= PCI_EXP_LNKCTL_ASPMC;
	अगर (parent) अणु
		pcie_capability_पढ़ो_word(parent, PCI_EXP_LNKCTL,
					  &parent_aspm_conf);
		parent_aspm_conf &= PCI_EXP_LNKCTL_ASPMC;
	पूर्ण

	अगर (!aspm_conf && (!parent || !parent_aspm_conf)) अणु
		/* aspm alपढ़ोy disabled */
		वापस;
	पूर्ण

	dev_info(&pdev->dev, "disabling ASPM %s %s\n",
		 (aspm_conf & PCI_EXP_LNKCTL_ASPM_L0S) ? "L0s" : "",
		 (aspm_conf & PCI_EXP_LNKCTL_ASPM_L1) ? "L1" : "");

	अगर (IS_ENABLED(CONFIG_PCIEASPM)) अणु
		पूर्णांक err;

		err = pci_disable_link_state(pdev, aspm_conf);
		अगर (!err)
			वापस;
	पूर्ण

	/* both device and parent should have the same ASPM setting.
	 * disable ASPM in करोwnstream component first and then upstream.
	 */
	pcie_capability_clear_word(pdev, PCI_EXP_LNKCTL, aspm_conf);
	अगर (parent)
		pcie_capability_clear_word(parent, PCI_EXP_LNKCTL,
					   aspm_conf);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_pci_disable_aspm);
