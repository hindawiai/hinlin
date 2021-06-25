<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    Copyright (C) 2006 Benjamin Herrenschmidt, IBM Corp.
 *			 <benh@kernel.crashing.org>
 *    and		 Arnd Bergmann, IBM Corp.
 */

#अघोषित DEBUG

#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/pci.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/atomic.h>

#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/topology.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/eeh.h>

#अगर_घोषित CONFIG_PPC_OF_PLATFORM_PCI

/* The probing of PCI controllers from of_platक्रमm is currently
 * 64 bits only, mostly due to gratuitous dअगरferences between
 * the 32 and 64 bits PCI code on PowerPC and the 32 bits one
 * lacking some bits needed here.
 */

अटल पूर्णांक of_pci_phb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा pci_controller *phb;

	/* Check अगर we can करो that ... */
	अगर (ppc_md.pci_setup_phb == शून्य)
		वापस -ENODEV;

	pr_info("Setting up PCI bus %pOF\n", dev->dev.of_node);

	/* Alloc and setup PHB data काष्ठाure */
	phb = pcibios_alloc_controller(dev->dev.of_node);
	अगर (!phb)
		वापस -ENODEV;

	/* Setup parent in sysfs */
	phb->parent = &dev->dev;

	/* Setup the PHB using arch provided callback */
	अगर (ppc_md.pci_setup_phb(phb)) अणु
		pcibios_मुक्त_controller(phb);
		वापस -ENODEV;
	पूर्ण

	/* Process "ranges" property */
	pci_process_bridge_OF_ranges(phb, dev->dev.of_node, 0);

	/* Init pci_dn data काष्ठाures */
	pci_devs_phb_init_dynamic(phb);

	/* Create EEH PE क्रम the PHB */
	eeh_phb_pe_create(phb);

	/* Scan the bus */
	pcibios_scan_phb(phb);
	अगर (phb->bus == शून्य)
		वापस -ENXIO;

	/* Claim resources. This might need some rework as well depending
	 * whether we are करोing probe-only or not, like assigning unasचिन्हित
	 * resources etc...
	 */
	pcibios_claim_one_bus(phb->bus);

	/* Add probed PCI devices to the device model */
	pci_bus_add_devices(phb->bus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_pci_phb_ids[] = अणु
	अणु .type = "pci", पूर्ण,
	अणु .type = "pcix", पूर्ण,
	अणु .type = "pcie", पूर्ण,
	अणु .type = "pciex", पूर्ण,
	अणु .type = "ht", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver of_pci_phb_driver = अणु
	.probe = of_pci_phb_probe,
	.driver = अणु
		.name = "of-pci",
		.of_match_table = of_pci_phb_ids,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(of_pci_phb_driver);

#पूर्ण_अगर /* CONFIG_PPC_OF_PLATFORM_PCI */
