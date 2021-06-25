<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PCI Express Hot Plug Controller Driver
 *
 * Copyright (C) 1995,2001 Compaq Computer Corporation
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001 IBM Corp.
 * Copyright (C) 2003-2004 Intel Corporation
 *
 * All rights reserved.
 *
 * Send feedback to <greg@kroah.com>, <kristen.c.accardi@पूर्णांकel.com>
 *
 */

#घोषणा dev_fmt(fmt) "pciehp: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश "../pci.h"
#समावेश "pciehp.h"

/**
 * pciehp_configure_device() - क्रमागतerate PCI devices below a hotplug bridge
 * @ctrl: PCIe hotplug controller
 *
 * Enumerate PCI devices below a hotplug bridge and add them to the प्रणाली.
 * Return 0 on success, %-EEXIST अगर the devices are alपढ़ोy क्रमागतerated or
 * %-ENODEV अगर क्रमागतeration failed.
 */
पूर्णांक pciehp_configure_device(काष्ठा controller *ctrl)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा pci_dev *bridge = ctrl->pcie->port;
	काष्ठा pci_bus *parent = bridge->subordinate;
	पूर्णांक num, ret = 0;

	pci_lock_rescan_हटाओ();

	dev = pci_get_slot(parent, PCI_DEVFN(0, 0));
	अगर (dev) अणु
		/*
		 * The device is alपढ़ोy there. Either configured by the
		 * boot firmware or a previous hotplug event.
		 */
		ctrl_dbg(ctrl, "Device %s already exists at %04x:%02x:00, skipping hot-add\n",
			 pci_name(dev), pci_करोमुख्य_nr(parent), parent->number);
		pci_dev_put(dev);
		ret = -EEXIST;
		जाओ out;
	पूर्ण

	num = pci_scan_slot(parent, PCI_DEVFN(0, 0));
	अगर (num == 0) अणु
		ctrl_err(ctrl, "No new device found\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	क्रम_each_pci_bridge(dev, parent)
		pci_hp_add_bridge(dev);

	pci_assign_unasचिन्हित_bridge_resources(bridge);
	pcie_bus_configure_settings(parent);
	pci_bus_add_devices(parent);

 out:
	pci_unlock_rescan_हटाओ();
	वापस ret;
पूर्ण

/**
 * pciehp_unconfigure_device() - हटाओ PCI devices below a hotplug bridge
 * @ctrl: PCIe hotplug controller
 * @presence: whether the card is still present in the slot;
 *	true क्रम safe removal via sysfs or an Attention Button press,
 *	false क्रम surprise removal
 *
 * Unbind PCI devices below a hotplug bridge from their drivers and हटाओ
 * them from the प्रणाली.  Safely हटाओd devices are quiesced.  Surprise
 * हटाओd devices are marked as such to prevent further accesses.
 */
व्योम pciehp_unconfigure_device(काष्ठा controller *ctrl, bool presence)
अणु
	काष्ठा pci_dev *dev, *temp;
	काष्ठा pci_bus *parent = ctrl->pcie->port->subordinate;
	u16 command;

	ctrl_dbg(ctrl, "%s: domain:bus:dev = %04x:%02x:00\n",
		 __func__, pci_करोमुख्य_nr(parent), parent->number);

	अगर (!presence)
		pci_walk_bus(parent, pci_dev_set_disconnected, शून्य);

	pci_lock_rescan_हटाओ();

	/*
	 * Stopping an SR-IOV PF device हटाओs all the associated VFs,
	 * which will update the bus->devices list and confuse the
	 * iterator.  Thereक्रमe, iterate in reverse so we हटाओ the VFs
	 * first, then the PF.  We करो the same in pci_stop_bus_device().
	 */
	list_क्रम_each_entry_safe_reverse(dev, temp, &parent->devices,
					 bus_list) अणु
		pci_dev_get(dev);
		pci_stop_and_हटाओ_bus_device(dev);
		/*
		 * Ensure that no new Requests will be generated from
		 * the device.
		 */
		अगर (presence) अणु
			pci_पढ़ो_config_word(dev, PCI_COMMAND, &command);
			command &= ~(PCI_COMMAND_MASTER | PCI_COMMAND_SERR);
			command |= PCI_COMMAND_INTX_DISABLE;
			pci_ग_लिखो_config_word(dev, PCI_COMMAND, command);
		पूर्ण
		pci_dev_put(dev);
	पूर्ण

	pci_unlock_rescan_हटाओ();
पूर्ण
