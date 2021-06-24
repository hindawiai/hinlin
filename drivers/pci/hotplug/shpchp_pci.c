<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Standard Hot Plug Controller Driver
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

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश "../pci.h"
#समावेश "shpchp.h"

पूर्णांक shpchp_configure_device(काष्ठा slot *p_slot)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा controller *ctrl = p_slot->ctrl;
	काष्ठा pci_dev *bridge = ctrl->pci_dev;
	काष्ठा pci_bus *parent = bridge->subordinate;
	पूर्णांक num, ret = 0;

	pci_lock_rescan_हटाओ();

	dev = pci_get_slot(parent, PCI_DEVFN(p_slot->device, 0));
	अगर (dev) अणु
		ctrl_err(ctrl, "Device %s already exists at %04x:%02x:%02x, cannot hot-add\n",
			 pci_name(dev), pci_करोमुख्य_nr(parent),
			 p_slot->bus, p_slot->device);
		pci_dev_put(dev);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	num = pci_scan_slot(parent, PCI_DEVFN(p_slot->device, 0));
	अगर (num == 0) अणु
		ctrl_err(ctrl, "No new device found\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	क्रम_each_pci_bridge(dev, parent) अणु
		अगर (PCI_SLOT(dev->devfn) == p_slot->device)
			pci_hp_add_bridge(dev);
	पूर्ण

	pci_assign_unasचिन्हित_bridge_resources(bridge);
	pcie_bus_configure_settings(parent);
	pci_bus_add_devices(parent);

 out:
	pci_unlock_rescan_हटाओ();
	वापस ret;
पूर्ण

व्योम shpchp_unconfigure_device(काष्ठा slot *p_slot)
अणु
	काष्ठा pci_bus *parent = p_slot->ctrl->pci_dev->subordinate;
	काष्ठा pci_dev *dev, *temp;
	काष्ठा controller *ctrl = p_slot->ctrl;

	ctrl_dbg(ctrl, "%s: domain:bus:dev = %04x:%02x:%02x\n",
		 __func__, pci_करोमुख्य_nr(parent), p_slot->bus, p_slot->device);

	pci_lock_rescan_हटाओ();

	list_क्रम_each_entry_safe(dev, temp, &parent->devices, bus_list) अणु
		अगर (PCI_SLOT(dev->devfn) != p_slot->device)
			जारी;

		pci_dev_get(dev);
		pci_stop_and_हटाओ_bus_device(dev);
		pci_dev_put(dev);
	पूर्ण

	pci_unlock_rescan_हटाओ();
पूर्ण
