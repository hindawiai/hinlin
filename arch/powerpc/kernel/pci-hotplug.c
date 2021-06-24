<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Derived from "arch/powerpc/platforms/pseries/pci_dlpar.c"
 *
 * Copyright (C) 2003 Linda Xie <lxie@us.ibm.com>
 * Copyright (C) 2005 International Business Machines
 *
 * Updates, 2005, John Rose <johnrose@austin.ibm.com>
 * Updates, 2005, Linas Vepstas <linas@austin.ibm.com>
 * Updates, 2013, Gavin Shan <shangw@linux.vnet.ibm.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/eeh.h>

अटल काष्ठा pci_bus *find_bus_among_children(काष्ठा pci_bus *bus,
					       काष्ठा device_node *dn)
अणु
	काष्ठा pci_bus *child = शून्य;
	काष्ठा pci_bus *पंचांगp;

	अगर (pci_bus_to_OF_node(bus) == dn)
		वापस bus;

	list_क्रम_each_entry(पंचांगp, &bus->children, node) अणु
		child = find_bus_among_children(पंचांगp, dn);
		अगर (child)
			अवरोध;
	पूर्ण

	वापस child;
पूर्ण

काष्ठा pci_bus *pci_find_bus_by_node(काष्ठा device_node *dn)
अणु
	काष्ठा pci_dn *pdn = PCI_DN(dn);

	अगर (!pdn  || !pdn->phb || !pdn->phb->bus)
		वापस शून्य;

	वापस find_bus_among_children(pdn->phb->bus, dn);
पूर्ण
EXPORT_SYMBOL_GPL(pci_find_bus_by_node);

/**
 * pcibios_release_device - release PCI device
 * @dev: PCI device
 *
 * The function is called beक्रमe releasing the indicated PCI device.
 */
व्योम pcibios_release_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *phb = pci_bus_to_host(dev->bus);
	काष्ठा pci_dn *pdn = pci_get_pdn(dev);

	अगर (phb->controller_ops.release_device)
		phb->controller_ops.release_device(dev);

	/* मुक्त()ing the pci_dn has been deferred to us, करो it now */
	अगर (pdn && (pdn->flags & PCI_DN_FLAG_DEAD)) अणु
		pci_dbg(dev, "freeing dead pdn\n");
		kमुक्त(pdn);
	पूर्ण
पूर्ण

/**
 * pci_hp_हटाओ_devices - हटाओ all devices under this bus
 * @bus: the indicated PCI bus
 *
 * Remove all of the PCI devices under this bus both from the
 * linux pci device tree, and from the घातerpc EEH address cache.
 */
व्योम pci_hp_हटाओ_devices(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev, *पंचांगp;
	काष्ठा pci_bus *child_bus;

	/* First go करोwn child busses */
	list_क्रम_each_entry(child_bus, &bus->children, node)
		pci_hp_हटाओ_devices(child_bus);

	pr_debug("PCI: Removing devices on bus %04x:%02x\n",
		 pci_करोमुख्य_nr(bus),  bus->number);
	list_क्रम_each_entry_safe_reverse(dev, पंचांगp, &bus->devices, bus_list) अणु
		pr_debug("   Removing %s...\n", pci_name(dev));
		pci_stop_and_हटाओ_bus_device(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pci_hp_हटाओ_devices);

/**
 * pci_hp_add_devices - adds new pci devices to bus
 * @bus: the indicated PCI bus
 *
 * This routine will find and fixup new pci devices under
 * the indicated bus. This routine presumes that there
 * might alपढ़ोy be some devices under this bridge, so
 * it carefully tries to add only new devices.  (And that
 * is how this routine dअगरfers from other, similar pcibios
 * routines.)
 */
व्योम pci_hp_add_devices(काष्ठा pci_bus *bus)
अणु
	पूर्णांक slotno, mode, max;
	काष्ठा pci_dev *dev;
	काष्ठा pci_controller *phb;
	काष्ठा device_node *dn = pci_bus_to_OF_node(bus);

	phb = pci_bus_to_host(bus);

	mode = PCI_PROBE_NORMAL;
	अगर (phb->controller_ops.probe_mode)
		mode = phb->controller_ops.probe_mode(bus);

	अगर (mode == PCI_PROBE_DEVTREE) अणु
		/* use ofdt-based probe */
		of_rescan_bus(dn, bus);
	पूर्ण अन्यथा अगर (mode == PCI_PROBE_NORMAL &&
		   dn->child && PCI_DN(dn->child)) अणु
		/*
		 * Use legacy probe. In the partial hotplug हाल, we
		 * probably have gअक्रमchildren devices unplugged. So
		 * we करोn't check the वापस value from pci_scan_slot() in
		 * order क्रम fully rescan all the way करोwn to pick them up.
		 * They can have been हटाओd during partial hotplug.
		 */
		slotno = PCI_SLOT(PCI_DN(dn->child)->devfn);
		pci_scan_slot(bus, PCI_DEVFN(slotno, 0));
		max = bus->busn_res.start;
		/*
		 * Scan bridges that are alपढ़ोy configured. We करोn't touch
		 * them unless they are misconfigured (which will be करोne in
		 * the second scan below).
		 */
		क्रम_each_pci_bridge(dev, bus)
			max = pci_scan_bridge(bus, dev, max, 0);

		/* Scan bridges that need to be reconfigured */
		क्रम_each_pci_bridge(dev, bus)
			max = pci_scan_bridge(bus, dev, max, 1);
	पूर्ण
	pcibios_finish_adding_to_bus(bus);
पूर्ण
EXPORT_SYMBOL_GPL(pci_hp_add_devices);
