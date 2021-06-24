<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PCI Dynamic LPAR, PCI Hot Plug and PCI EEH recovery code
 * क्रम RPA-compliant PPC64 platक्रमm.
 * Copyright (C) 2003 Linda Xie <lxie@us.ibm.com>
 * Copyright (C) 2005 International Business Machines
 *
 * Updates, 2005, John Rose <johnrose@austin.ibm.com>
 * Updates, 2005, Linas Vepstas <linas@austin.ibm.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/eeh.h>

#समावेश "pseries.h"

काष्ठा pci_controller *init_phb_dynamic(काष्ठा device_node *dn)
अणु
	काष्ठा pci_controller *phb;

	pr_debug("PCI: Initializing new hotplug PHB %pOF\n", dn);

	phb = pcibios_alloc_controller(dn);
	अगर (!phb)
		वापस शून्य;
	rtas_setup_phb(phb);
	pci_process_bridge_OF_ranges(phb, dn, 0);
	phb->controller_ops = pseries_pci_controller_ops;

	pci_devs_phb_init_dynamic(phb);

	/* Create EEH devices क्रम the PHB */
	eeh_phb_pe_create(phb);

	अगर (dn->child)
		pseries_eeh_init_edev_recursive(PCI_DN(dn));

	pcibios_scan_phb(phb);
	pcibios_finish_adding_to_bus(phb->bus);

	वापस phb;
पूर्ण
EXPORT_SYMBOL_GPL(init_phb_dynamic);

/* RPA-specअगरic bits क्रम removing PHBs */
पूर्णांक हटाओ_phb_dynamic(काष्ठा pci_controller *phb)
अणु
	काष्ठा pci_bus *b = phb->bus;
	काष्ठा pci_host_bridge *host_bridge = to_pci_host_bridge(b->bridge);
	काष्ठा resource *res;
	पूर्णांक rc, i;

	pr_debug("PCI: Removing PHB %04x:%02x...\n",
		 pci_करोमुख्य_nr(b), b->number);

	/* We cannot to हटाओ a root bus that has children */
	अगर (!(list_empty(&b->children) && list_empty(&b->devices)))
		वापस -EBUSY;

	/* We -know- there aren't any child devices anymore at this stage
	 * and thus, we can safely unmap the IO space as it's not in use
	 */
	res = &phb->io_resource;
	अगर (res->flags & IORESOURCE_IO) अणु
		rc = pcibios_unmap_io_space(b);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "%s: failed to unmap IO on bus %s\n",
			       __func__, b->name);
			वापस 1;
		पूर्ण
	पूर्ण

	/* Remove the PCI bus and unरेजिस्टर the bridge device from sysfs */
	phb->bus = शून्य;
	pci_हटाओ_bus(b);
	host_bridge->bus = शून्य;
	device_unरेजिस्टर(&host_bridge->dev);

	/* Now release the IO resource */
	अगर (res->flags & IORESOURCE_IO)
		release_resource(res);

	/* Release memory resources */
	क्रम (i = 0; i < 3; ++i) अणु
		res = &phb->mem_resources[i];
		अगर (!(res->flags & IORESOURCE_MEM))
			जारी;
		release_resource(res);
	पूर्ण

	/*
	 * The pci_controller data काष्ठाure is मुक्तd by
	 * the pcibios_मुक्त_controller_deferred() callback;
	 * see pseries_root_bridge_prepare().
	 */

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(हटाओ_phb_dynamic);
