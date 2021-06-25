<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश "pci.h"

अटल व्योम pci_मुक्त_resources(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PCI_NUM_RESOURCES; i++) अणु
		काष्ठा resource *res = dev->resource + i;
		अगर (res->parent)
			release_resource(res);
	पूर्ण
पूर्ण

अटल व्योम pci_stop_dev(काष्ठा pci_dev *dev)
अणु
	pci_pme_active(dev, false);

	अगर (pci_dev_is_added(dev)) अणु
		dev->reset_fn = 0;

		device_release_driver(&dev->dev);
		pci_proc_detach_device(dev);
		pci_हटाओ_sysfs_dev_files(dev);

		pci_dev_assign_added(dev, false);
	पूर्ण
पूर्ण

अटल व्योम pci_destroy_dev(काष्ठा pci_dev *dev)
अणु
	अगर (!dev->dev.kobj.parent)
		वापस;

	device_del(&dev->dev);

	करोwn_ग_लिखो(&pci_bus_sem);
	list_del(&dev->bus_list);
	up_ग_लिखो(&pci_bus_sem);

	pcie_aspm_निकास_link_state(dev);
	pci_bridge_d3_update(dev);
	pci_मुक्त_resources(dev);
	put_device(&dev->dev);
पूर्ण

व्योम pci_हटाओ_bus(काष्ठा pci_bus *bus)
अणु
	pci_proc_detach_bus(bus);

	करोwn_ग_लिखो(&pci_bus_sem);
	list_del(&bus->node);
	pci_bus_release_busn_res(bus);
	up_ग_लिखो(&pci_bus_sem);
	pci_हटाओ_legacy_files(bus);

	अगर (bus->ops->हटाओ_bus)
		bus->ops->हटाओ_bus(bus);

	pcibios_हटाओ_bus(bus);
	device_unरेजिस्टर(&bus->dev);
पूर्ण
EXPORT_SYMBOL(pci_हटाओ_bus);

अटल व्योम pci_stop_bus_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_bus *bus = dev->subordinate;
	काष्ठा pci_dev *child, *पंचांगp;

	/*
	 * Stopping an SR-IOV PF device हटाओs all the associated VFs,
	 * which will update the bus->devices list and confuse the
	 * iterator.  Thereक्रमe, iterate in reverse so we हटाओ the VFs
	 * first, then the PF.
	 */
	अगर (bus) अणु
		list_क्रम_each_entry_safe_reverse(child, पंचांगp,
						 &bus->devices, bus_list)
			pci_stop_bus_device(child);
	पूर्ण

	pci_stop_dev(dev);
पूर्ण

अटल व्योम pci_हटाओ_bus_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_bus *bus = dev->subordinate;
	काष्ठा pci_dev *child, *पंचांगp;

	अगर (bus) अणु
		list_क्रम_each_entry_safe(child, पंचांगp,
					 &bus->devices, bus_list)
			pci_हटाओ_bus_device(child);

		pci_हटाओ_bus(bus);
		dev->subordinate = शून्य;
	पूर्ण

	pci_destroy_dev(dev);
पूर्ण

/**
 * pci_stop_and_हटाओ_bus_device - हटाओ a PCI device and any children
 * @dev: the device to हटाओ
 *
 * Remove a PCI device from the device lists, inक्रमming the drivers
 * that the device has been हटाओd.  We also हटाओ any subordinate
 * buses and children in a depth-first manner.
 *
 * For each device we हटाओ, delete the device काष्ठाure from the
 * device lists, हटाओ the /proc entry, and notअगरy userspace
 * (/sbin/hotplug).
 */
व्योम pci_stop_and_हटाओ_bus_device(काष्ठा pci_dev *dev)
अणु
	pci_stop_bus_device(dev);
	pci_हटाओ_bus_device(dev);
पूर्ण
EXPORT_SYMBOL(pci_stop_and_हटाओ_bus_device);

व्योम pci_stop_and_हटाओ_bus_device_locked(काष्ठा pci_dev *dev)
अणु
	pci_lock_rescan_हटाओ();
	pci_stop_and_हटाओ_bus_device(dev);
	pci_unlock_rescan_हटाओ();
पूर्ण
EXPORT_SYMBOL_GPL(pci_stop_and_हटाओ_bus_device_locked);

व्योम pci_stop_root_bus(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *child, *पंचांगp;
	काष्ठा pci_host_bridge *host_bridge;

	अगर (!pci_is_root_bus(bus))
		वापस;

	host_bridge = to_pci_host_bridge(bus->bridge);
	list_क्रम_each_entry_safe_reverse(child, पंचांगp,
					 &bus->devices, bus_list)
		pci_stop_bus_device(child);

	/* stop the host bridge */
	device_release_driver(&host_bridge->dev);
पूर्ण
EXPORT_SYMBOL_GPL(pci_stop_root_bus);

व्योम pci_हटाओ_root_bus(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *child, *पंचांगp;
	काष्ठा pci_host_bridge *host_bridge;

	अगर (!pci_is_root_bus(bus))
		वापस;

	host_bridge = to_pci_host_bridge(bus->bridge);
	list_क्रम_each_entry_safe(child, पंचांगp,
				 &bus->devices, bus_list)
		pci_हटाओ_bus_device(child);
	pci_हटाओ_bus(bus);
	host_bridge->bus = शून्य;

	/* हटाओ the host bridge */
	device_del(&host_bridge->dev);
पूर्ण
EXPORT_SYMBOL_GPL(pci_हटाओ_root_bus);
