<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 2020
 *
 * Author(s):
 *   Pierre Morel <pmorel@linux.ibm.com>
 *
 */

पूर्णांक zpci_bus_device_रेजिस्टर(काष्ठा zpci_dev *zdev, काष्ठा pci_ops *ops);
व्योम zpci_bus_device_unरेजिस्टर(काष्ठा zpci_dev *zdev);

पूर्णांक zpci_bus_scan_bus(काष्ठा zpci_bus *zbus);
व्योम zpci_bus_scan_busses(व्योम);

पूर्णांक zpci_bus_scan_device(काष्ठा zpci_dev *zdev);
व्योम zpci_bus_हटाओ_device(काष्ठा zpci_dev *zdev, bool set_error);

व्योम zpci_release_device(काष्ठा kref *kref);
अटल अंतरभूत व्योम zpci_zdev_put(काष्ठा zpci_dev *zdev)
अणु
	kref_put(&zdev->kref, zpci_release_device);
पूर्ण

पूर्णांक zpci_alloc_करोमुख्य(पूर्णांक करोमुख्य);
व्योम zpci_मुक्त_करोमुख्य(पूर्णांक करोमुख्य);
पूर्णांक zpci_setup_bus_resources(काष्ठा zpci_dev *zdev,
			     काष्ठा list_head *resources);

अटल अंतरभूत काष्ठा zpci_dev *get_zdev_by_bus(काष्ठा pci_bus *bus,
					       अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा zpci_bus *zbus = bus->sysdata;

	वापस (devfn >= ZPCI_FUNCTIONS_PER_BUS) ? शून्य : zbus->function[devfn];
पूर्ण

