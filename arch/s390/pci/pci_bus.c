<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2020
 *
 * Author(s):
 *   Pierre Morel <pmorel@linux.ibm.com>
 *
 */

#घोषणा KMSG_COMPONENT "zpci"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/pci.h>
#समावेश <linux/prपूर्णांकk.h>

#समावेश <यंत्र/pci_clp.h>
#समावेश <यंत्र/pci_dma.h>

#समावेश "pci_bus.h"
#समावेश "pci_iov.h"

अटल LIST_HEAD(zbus_list);
अटल DEFINE_MUTEX(zbus_list_lock);
अटल पूर्णांक zpci_nb_devices;

/* zpci_bus_prepare_device - Prepare a zPCI function क्रम scanning
 * @zdev: the zPCI function to be prepared
 *
 * The PCI resources क्रम the function are set up and added to its zbus and the
 * function is enabled. The function must be added to a zbus which must have
 * a PCI bus created. If an error occurs the zPCI function is not enabled.
 *
 * Return: 0 on success, an error code otherwise
 */
अटल पूर्णांक zpci_bus_prepare_device(काष्ठा zpci_dev *zdev)
अणु
	काष्ठा resource_entry *winकरोw, *n;
	काष्ठा resource *res;
	पूर्णांक rc;

	अगर (!zdev_enabled(zdev)) अणु
		rc = zpci_enable_device(zdev);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (!zdev->has_resources) अणु
		zpci_setup_bus_resources(zdev, &zdev->zbus->resources);
		resource_list_क्रम_each_entry_safe(winकरोw, n, &zdev->zbus->resources) अणु
			res = winकरोw->res;
			pci_bus_add_resource(zdev->zbus->bus, res, 0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* zpci_bus_scan_device - Scan a single device adding it to the PCI core
 * @zdev: the zdev to be scanned
 *
 * Scans the PCI function making it available to the common PCI code.
 *
 * Return: 0 on success, an error value otherwise
 */
पूर्णांक zpci_bus_scan_device(काष्ठा zpci_dev *zdev)
अणु
	काष्ठा pci_dev *pdev;
	पूर्णांक rc;

	rc = zpci_bus_prepare_device(zdev);
	अगर (rc)
		वापस rc;

	pdev = pci_scan_single_device(zdev->zbus->bus, zdev->devfn);
	अगर (!pdev)
		वापस -ENODEV;

	pci_bus_add_device(pdev);
	pci_lock_rescan_हटाओ();
	pci_bus_add_devices(zdev->zbus->bus);
	pci_unlock_rescan_हटाओ();

	वापस 0;
पूर्ण

/* zpci_bus_हटाओ_device - Removes the given zdev from the PCI core
 * @zdev: the zdev to be हटाओd from the PCI core
 * @set_error: अगर true the device's error state is set to permanent failure
 *
 * Sets a zPCI device to a configured but offline state; the zPCI
 * device is still accessible through its hotplug slot and the zPCI
 * API but is हटाओd from the common code PCI bus, making it
 * no दीर्घer available to drivers.
 */
व्योम zpci_bus_हटाओ_device(काष्ठा zpci_dev *zdev, bool set_error)
अणु
	काष्ठा zpci_bus *zbus = zdev->zbus;
	काष्ठा pci_dev *pdev;

	अगर (!zdev->zbus->bus)
		वापस;

	pdev = pci_get_slot(zbus->bus, zdev->devfn);
	अगर (pdev) अणु
		अगर (set_error)
			pdev->error_state = pci_channel_io_perm_failure;
		अगर (pdev->is_virtfn) अणु
			zpci_iov_हटाओ_virtfn(pdev, zdev->vfn);
			/* balance pci_get_slot */
			pci_dev_put(pdev);
			वापस;
		पूर्ण
		pci_stop_and_हटाओ_bus_device_locked(pdev);
		/* balance pci_get_slot */
		pci_dev_put(pdev);
	पूर्ण
पूर्ण

/* zpci_bus_scan_bus - Scan all configured zPCI functions on the bus
 * @zbus: the zbus to be scanned
 *
 * Enables and scans all PCI functions on the bus making them available to the
 * common PCI code. If there is no function 0 on the zbus nothing is scanned. If
 * a function करोes not have a slot yet because it was added to the zbus beक्रमe
 * function 0 the slot is created. If a PCI function fails to be initialized
 * an error will be वापसed but attempts will still be made क्रम all other
 * functions on the bus.
 *
 * Return: 0 on success, an error value otherwise
 */
पूर्णांक zpci_bus_scan_bus(काष्ठा zpci_bus *zbus)
अणु
	काष्ठा zpci_dev *zdev;
	पूर्णांक devfn, rc, ret = 0;

	अगर (!zbus->function[0])
		वापस 0;

	क्रम (devfn = 0; devfn < ZPCI_FUNCTIONS_PER_BUS; devfn++) अणु
		zdev = zbus->function[devfn];
		अगर (zdev && zdev->state == ZPCI_FN_STATE_CONFIGURED) अणु
			rc = zpci_bus_prepare_device(zdev);
			अगर (rc)
				ret = -EIO;
		पूर्ण
	पूर्ण

	pci_lock_rescan_हटाओ();
	pci_scan_child_bus(zbus->bus);
	pci_bus_add_devices(zbus->bus);
	pci_unlock_rescan_हटाओ();

	वापस ret;
पूर्ण

/* zpci_bus_scan_busses - Scan all रेजिस्टरed busses
 *
 * Scan all available zbusses
 *
 */
व्योम zpci_bus_scan_busses(व्योम)
अणु
	काष्ठा zpci_bus *zbus = शून्य;

	mutex_lock(&zbus_list_lock);
	list_क्रम_each_entry(zbus, &zbus_list, bus_next) अणु
		zpci_bus_scan_bus(zbus);
		cond_resched();
	पूर्ण
	mutex_unlock(&zbus_list_lock);
पूर्ण

/* zpci_bus_create_pci_bus - Create the PCI bus associated with this zbus
 * @zbus: the zbus holding the zdevices
 * @f0: function 0 of the bus
 * @ops: the pci operations
 *
 * Function zero is taken as a parameter as this is used to determine the
 * करोमुख्य, multअगरunction property and maximum bus speed of the entire bus.
 *
 * Return: 0 on success, an error code otherwise
 */
अटल पूर्णांक zpci_bus_create_pci_bus(काष्ठा zpci_bus *zbus, काष्ठा zpci_dev *f0, काष्ठा pci_ops *ops)
अणु
	काष्ठा pci_bus *bus;
	पूर्णांक करोमुख्य;

	करोमुख्य = zpci_alloc_करोमुख्य((u16)f0->uid);
	अगर (करोमुख्य < 0)
		वापस करोमुख्य;

	zbus->करोमुख्य_nr = करोमुख्य;
	zbus->multअगरunction = f0->rid_available;
	zbus->max_bus_speed = f0->max_bus_speed;

	/*
	 * Note that the zbus->resources are taken over and zbus->resources
	 * is empty after a successful call
	 */
	bus = pci_create_root_bus(शून्य, ZPCI_BUS_NR, ops, zbus, &zbus->resources);
	अगर (!bus) अणु
		zpci_मुक्त_करोमुख्य(zbus->करोमुख्य_nr);
		वापस -EFAULT;
	पूर्ण

	zbus->bus = bus;
	pci_bus_add_devices(bus);

	वापस 0;
पूर्ण

अटल व्योम zpci_bus_release(काष्ठा kref *kref)
अणु
	काष्ठा zpci_bus *zbus = container_of(kref, काष्ठा zpci_bus, kref);

	अगर (zbus->bus) अणु
		pci_lock_rescan_हटाओ();
		pci_stop_root_bus(zbus->bus);

		zpci_मुक्त_करोमुख्य(zbus->करोमुख्य_nr);
		pci_मुक्त_resource_list(&zbus->resources);

		pci_हटाओ_root_bus(zbus->bus);
		pci_unlock_rescan_हटाओ();
	पूर्ण

	mutex_lock(&zbus_list_lock);
	list_del(&zbus->bus_next);
	mutex_unlock(&zbus_list_lock);
	kमुक्त(zbus);
पूर्ण

अटल व्योम zpci_bus_put(काष्ठा zpci_bus *zbus)
अणु
	kref_put(&zbus->kref, zpci_bus_release);
पूर्ण

अटल काष्ठा zpci_bus *zpci_bus_get(पूर्णांक pchid)
अणु
	काष्ठा zpci_bus *zbus;

	mutex_lock(&zbus_list_lock);
	list_क्रम_each_entry(zbus, &zbus_list, bus_next) अणु
		अगर (pchid == zbus->pchid) अणु
			kref_get(&zbus->kref);
			जाओ out_unlock;
		पूर्ण
	पूर्ण
	zbus = शून्य;
out_unlock:
	mutex_unlock(&zbus_list_lock);
	वापस zbus;
पूर्ण

अटल काष्ठा zpci_bus *zpci_bus_alloc(पूर्णांक pchid)
अणु
	काष्ठा zpci_bus *zbus;

	zbus = kzalloc(माप(*zbus), GFP_KERNEL);
	अगर (!zbus)
		वापस शून्य;

	zbus->pchid = pchid;
	INIT_LIST_HEAD(&zbus->bus_next);
	mutex_lock(&zbus_list_lock);
	list_add_tail(&zbus->bus_next, &zbus_list);
	mutex_unlock(&zbus_list_lock);

	kref_init(&zbus->kref);
	INIT_LIST_HEAD(&zbus->resources);

	zbus->bus_resource.start = 0;
	zbus->bus_resource.end = ZPCI_BUS_NR;
	zbus->bus_resource.flags = IORESOURCE_BUS;
	pci_add_resource(&zbus->resources, &zbus->bus_resource);

	वापस zbus;
पूर्ण

व्योम pcibios_bus_add_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(pdev);

	/*
	 * With pdev->no_vf_scan the common PCI probing code करोes not
	 * perक्रमm PF/VF linking.
	 */
	अगर (zdev->vfn) अणु
		zpci_iov_setup_virtfn(zdev->zbus, pdev, zdev->vfn);
		pdev->no_command_memory = 1;
	पूर्ण
पूर्ण

/* zpci_bus_create_hotplug_slots - Add hotplug slot(s) क्रम device added to bus
 * @zdev: the zPCI device that was newly added
 *
 * Add the hotplug slot(s) क्रम the newly added PCI function. Normally this is
 * simply the slot क्रम the function itself. If however we are adding the
 * function 0 on a zbus, it might be that we alपढ़ोy रेजिस्टरed functions on
 * that zbus but could not create their hotplug slots yet so add those now too.
 *
 * Return: 0 on success, an error code otherwise
 */
अटल पूर्णांक zpci_bus_create_hotplug_slots(काष्ठा zpci_dev *zdev)
अणु
	काष्ठा zpci_bus *zbus = zdev->zbus;
	पूर्णांक devfn, rc = 0;

	rc = zpci_init_slot(zdev);
	अगर (rc)
		वापस rc;
	zdev->has_hp_slot = 1;

	अगर (zdev->devfn == 0 && zbus->multअगरunction) अणु
		/* Now that function 0 is there we can finally create the
		 * hotplug slots क्रम those functions with devfn != 0 that have
		 * been parked in zbus->function[] रुकोing क्रम us to be able to
		 * create the PCI bus.
		 */
		क्रम  (devfn = 1; devfn < ZPCI_FUNCTIONS_PER_BUS; devfn++) अणु
			zdev = zbus->function[devfn];
			अगर (zdev && !zdev->has_hp_slot) अणु
				rc = zpci_init_slot(zdev);
				अगर (rc)
					वापस rc;
				zdev->has_hp_slot = 1;
			पूर्ण
		पूर्ण

	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक zpci_bus_add_device(काष्ठा zpci_bus *zbus, काष्ठा zpci_dev *zdev)
अणु
	पूर्णांक rc = -EINVAL;

	zdev->zbus = zbus;
	अगर (zbus->function[zdev->devfn]) अणु
		pr_err("devfn %04x is already assigned\n", zdev->devfn);
		वापस rc;
	पूर्ण
	zbus->function[zdev->devfn] = zdev;
	zpci_nb_devices++;

	अगर (zbus->bus) अणु
		अगर (zbus->multअगरunction && !zdev->rid_available) अणु
			WARN_ONCE(1, "rid_available not set for multifunction\n");
			जाओ error;
		पूर्ण

		zpci_bus_create_hotplug_slots(zdev);
	पूर्ण अन्यथा अणु
		/* Hotplug slot will be created once function 0 appears */
		zbus->multअगरunction = 1;
	पूर्ण

	वापस 0;

error:
	zbus->function[zdev->devfn] = शून्य;
	zpci_nb_devices--;
	वापस rc;
पूर्ण

पूर्णांक zpci_bus_device_रेजिस्टर(काष्ठा zpci_dev *zdev, काष्ठा pci_ops *ops)
अणु
	काष्ठा zpci_bus *zbus = शून्य;
	पूर्णांक rc = -EBADF;

	अगर (zpci_nb_devices == ZPCI_NR_DEVICES) अणु
		pr_warn("Adding PCI function %08x failed because the configured limit of %d is reached\n",
			zdev->fid, ZPCI_NR_DEVICES);
		वापस -ENOSPC;
	पूर्ण

	अगर (zdev->devfn >= ZPCI_FUNCTIONS_PER_BUS)
		वापस -EINVAL;

	अगर (!s390_pci_no_rid && zdev->rid_available)
		zbus = zpci_bus_get(zdev->pchid);

	अगर (!zbus) अणु
		zbus = zpci_bus_alloc(zdev->pchid);
		अगर (!zbus)
			वापस -ENOMEM;
	पूर्ण

	अगर (zdev->devfn == 0) अणु
		rc = zpci_bus_create_pci_bus(zbus, zdev, ops);
		अगर (rc)
			जाओ error;
	पूर्ण

	rc = zpci_bus_add_device(zbus, zdev);
	अगर (rc)
		जाओ error;

	वापस 0;

error:
	pr_err("Adding PCI function %08x failed\n", zdev->fid);
	zpci_bus_put(zbus);
	वापस rc;
पूर्ण

व्योम zpci_bus_device_unरेजिस्टर(काष्ठा zpci_dev *zdev)
अणु
	काष्ठा zpci_bus *zbus = zdev->zbus;

	zpci_nb_devices--;
	zbus->function[zdev->devfn] = शून्य;
	zpci_bus_put(zbus);
पूर्ण
