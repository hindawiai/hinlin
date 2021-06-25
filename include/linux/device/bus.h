<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bus.h - the bus-specअगरic portions of the driver model
 *
 * Copyright (c) 2001-2003 Patrick Mochel <mochel@osdl.org>
 * Copyright (c) 2004-2009 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Copyright (c) 2008-2009 Novell Inc.
 * Copyright (c) 2012-2019 Greg Kroah-Harपंचांगan <gregkh@linuxfoundation.org>
 * Copyright (c) 2012-2019 Linux Foundation
 *
 * See Documentation/driver-api/driver-model/ क्रम more inक्रमmation.
 */

#अगर_अघोषित _DEVICE_BUS_H_
#घोषणा _DEVICE_BUS_H_

#समावेश <linux/kobject.h>
#समावेश <linux/klist.h>
#समावेश <linux/pm.h>

काष्ठा device_driver;
काष्ठा fwnode_handle;

/**
 * काष्ठा bus_type - The bus type of the device
 *
 * @name:	The name of the bus.
 * @dev_name:	Used क्रम subप्रणालीs to क्रमागतerate devices like ("foo%u", dev->id).
 * @dev_root:	Default device to use as the parent.
 * @bus_groups:	Default attributes of the bus.
 * @dev_groups:	Default attributes of the devices on the bus.
 * @drv_groups: Default attributes of the device drivers on the bus.
 * @match:	Called, perhaps multiple बार, whenever a new device or driver
 *		is added क्रम this bus. It should वापस a positive value अगर the
 *		given device can be handled by the given driver and zero
 *		otherwise. It may also वापस error code अगर determining that
 *		the driver supports the device is not possible. In हाल of
 *		-EPROBE_DEFER it will queue the device क्रम deferred probing.
 * @uevent:	Called when a device is added, हटाओd, or a few other things
 *		that generate uevents to add the environment variables.
 * @probe:	Called when a new device or driver add to this bus, and callback
 *		the specअगरic driver's probe to initial the matched device.
 * @sync_state:	Called to sync device state to software state after all the
 *		state tracking consumers linked to this device (present at
 *		the समय of late_initcall) have successfully bound to a
 *		driver. If the device has no consumers, this function will
 *		be called at late_initcall_sync level. If the device has
 *		consumers that are never bound to a driver, this function
 *		will never get called until they करो.
 * @हटाओ:	Called when a device हटाओd from this bus.
 * @shutकरोwn:	Called at shut-करोwn समय to quiesce the device.
 *
 * @online:	Called to put the device back online (after offlining it).
 * @offline:	Called to put the device offline क्रम hot-removal. May fail.
 *
 * @suspend:	Called when a device on this bus wants to go to sleep mode.
 * @resume:	Called to bring a device on this bus out of sleep mode.
 * @num_vf:	Called to find out how many भव functions a device on this
 *		bus supports.
 * @dma_configure:	Called to setup DMA configuration on a device on
 *			this bus.
 * @pm:		Power management operations of this bus, callback the specअगरic
 *		device driver's pm-ops.
 * @iommu_ops:  IOMMU specअगरic operations क्रम this bus, used to attach IOMMU
 *              driver implementations to a bus and allow the driver to करो
 *              bus-specअगरic setup
 * @p:		The निजी data of the driver core, only the driver core can
 *		touch this.
 * @lock_key:	Lock class key क्रम use by the lock validator
 * @need_parent_lock:	When probing or removing a device on this bus, the
 *			device core should lock the device's parent.
 *
 * A bus is a channel between the processor and one or more devices. For the
 * purposes of the device model, all devices are connected via a bus, even अगर
 * it is an पूर्णांकernal, भव, "platform" bus. Buses can plug पूर्णांकo each other.
 * A USB controller is usually a PCI device, क्रम example. The device model
 * represents the actual connections between buses and the devices they control.
 * A bus is represented by the bus_type काष्ठाure. It contains the name, the
 * शेष attributes, the bus' methods, PM operations, and the driver core's
 * निजी data.
 */
काष्ठा bus_type अणु
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*dev_name;
	काष्ठा device		*dev_root;
	स्थिर काष्ठा attribute_group **bus_groups;
	स्थिर काष्ठा attribute_group **dev_groups;
	स्थिर काष्ठा attribute_group **drv_groups;

	पूर्णांक (*match)(काष्ठा device *dev, काष्ठा device_driver *drv);
	पूर्णांक (*uevent)(काष्ठा device *dev, काष्ठा kobj_uevent_env *env);
	पूर्णांक (*probe)(काष्ठा device *dev);
	व्योम (*sync_state)(काष्ठा device *dev);
	पूर्णांक (*हटाओ)(काष्ठा device *dev);
	व्योम (*shutकरोwn)(काष्ठा device *dev);

	पूर्णांक (*online)(काष्ठा device *dev);
	पूर्णांक (*offline)(काष्ठा device *dev);

	पूर्णांक (*suspend)(काष्ठा device *dev, pm_message_t state);
	पूर्णांक (*resume)(काष्ठा device *dev);

	पूर्णांक (*num_vf)(काष्ठा device *dev);

	पूर्णांक (*dma_configure)(काष्ठा device *dev);

	स्थिर काष्ठा dev_pm_ops *pm;

	स्थिर काष्ठा iommu_ops *iommu_ops;

	काष्ठा subsys_निजी *p;
	काष्ठा lock_class_key lock_key;

	bool need_parent_lock;
पूर्ण;

बाह्य पूर्णांक __must_check bus_रेजिस्टर(काष्ठा bus_type *bus);

बाह्य व्योम bus_unरेजिस्टर(काष्ठा bus_type *bus);

बाह्य पूर्णांक __must_check bus_rescan_devices(काष्ठा bus_type *bus);

काष्ठा bus_attribute अणु
	काष्ठा attribute	attr;
	sमाप_प्रकार (*show)(काष्ठा bus_type *bus, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा bus_type *bus, स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;

#घोषणा BUS_ATTR_RW(_name) \
	काष्ठा bus_attribute bus_attr_##_name = __ATTR_RW(_name)
#घोषणा BUS_ATTR_RO(_name) \
	काष्ठा bus_attribute bus_attr_##_name = __ATTR_RO(_name)
#घोषणा BUS_ATTR_WO(_name) \
	काष्ठा bus_attribute bus_attr_##_name = __ATTR_WO(_name)

बाह्य पूर्णांक __must_check bus_create_file(काष्ठा bus_type *,
					काष्ठा bus_attribute *);
बाह्य व्योम bus_हटाओ_file(काष्ठा bus_type *, काष्ठा bus_attribute *);

/* Generic device matching functions that all busses can use to match with */
पूर्णांक device_match_name(काष्ठा device *dev, स्थिर व्योम *name);
पूर्णांक device_match_of_node(काष्ठा device *dev, स्थिर व्योम *np);
पूर्णांक device_match_fwnode(काष्ठा device *dev, स्थिर व्योम *fwnode);
पूर्णांक device_match_devt(काष्ठा device *dev, स्थिर व्योम *pdevt);
पूर्णांक device_match_acpi_dev(काष्ठा device *dev, स्थिर व्योम *adev);
पूर्णांक device_match_any(काष्ठा device *dev, स्थिर व्योम *unused);

/* iterator helpers क्रम buses */
काष्ठा subsys_dev_iter अणु
	काष्ठा klist_iter		ki;
	स्थिर काष्ठा device_type	*type;
पूर्ण;
व्योम subsys_dev_iter_init(काष्ठा subsys_dev_iter *iter,
			 काष्ठा bus_type *subsys,
			 काष्ठा device *start,
			 स्थिर काष्ठा device_type *type);
काष्ठा device *subsys_dev_iter_next(काष्ठा subsys_dev_iter *iter);
व्योम subsys_dev_iter_निकास(काष्ठा subsys_dev_iter *iter);

पूर्णांक bus_क्रम_each_dev(काष्ठा bus_type *bus, काष्ठा device *start, व्योम *data,
		     पूर्णांक (*fn)(काष्ठा device *dev, व्योम *data));
काष्ठा device *bus_find_device(काष्ठा bus_type *bus, काष्ठा device *start,
			       स्थिर व्योम *data,
			       पूर्णांक (*match)(काष्ठा device *dev, स्थिर व्योम *data));
/**
 * bus_find_device_by_name - device iterator क्रम locating a particular device
 * of a specअगरic name.
 * @bus: bus type
 * @start: Device to begin with
 * @name: name of the device to match
 */
अटल अंतरभूत काष्ठा device *bus_find_device_by_name(काष्ठा bus_type *bus,
						     काष्ठा device *start,
						     स्थिर अक्षर *name)
अणु
	वापस bus_find_device(bus, start, name, device_match_name);
पूर्ण

/**
 * bus_find_device_by_of_node : device iterator क्रम locating a particular device
 * matching the of_node.
 * @bus: bus type
 * @np: of_node of the device to match.
 */
अटल अंतरभूत काष्ठा device *
bus_find_device_by_of_node(काष्ठा bus_type *bus, स्थिर काष्ठा device_node *np)
अणु
	वापस bus_find_device(bus, शून्य, np, device_match_of_node);
पूर्ण

/**
 * bus_find_device_by_fwnode : device iterator क्रम locating a particular device
 * matching the fwnode.
 * @bus: bus type
 * @fwnode: fwnode of the device to match.
 */
अटल अंतरभूत काष्ठा device *
bus_find_device_by_fwnode(काष्ठा bus_type *bus, स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस bus_find_device(bus, शून्य, fwnode, device_match_fwnode);
पूर्ण

/**
 * bus_find_device_by_devt : device iterator क्रम locating a particular device
 * matching the device type.
 * @bus: bus type
 * @devt: device type of the device to match.
 */
अटल अंतरभूत काष्ठा device *bus_find_device_by_devt(काष्ठा bus_type *bus,
						     dev_t devt)
अणु
	वापस bus_find_device(bus, शून्य, &devt, device_match_devt);
पूर्ण

/**
 * bus_find_next_device - Find the next device after a given device in a
 * given bus.
 * @bus: bus type
 * @cur: device to begin the search with.
 */
अटल अंतरभूत काष्ठा device *
bus_find_next_device(काष्ठा bus_type *bus,काष्ठा device *cur)
अणु
	वापस bus_find_device(bus, cur, शून्य, device_match_any);
पूर्ण

#अगर_घोषित CONFIG_ACPI
काष्ठा acpi_device;

/**
 * bus_find_device_by_acpi_dev : device iterator क्रम locating a particular device
 * matching the ACPI COMPANION device.
 * @bus: bus type
 * @adev: ACPI COMPANION device to match.
 */
अटल अंतरभूत काष्ठा device *
bus_find_device_by_acpi_dev(काष्ठा bus_type *bus, स्थिर काष्ठा acpi_device *adev)
अणु
	वापस bus_find_device(bus, शून्य, adev, device_match_acpi_dev);
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा device *
bus_find_device_by_acpi_dev(काष्ठा bus_type *bus, स्थिर व्योम *adev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

काष्ठा device *subsys_find_device_by_id(काष्ठा bus_type *bus, अचिन्हित पूर्णांक id,
					काष्ठा device *hपूर्णांक);
पूर्णांक bus_क्रम_each_drv(काष्ठा bus_type *bus, काष्ठा device_driver *start,
		     व्योम *data, पूर्णांक (*fn)(काष्ठा device_driver *, व्योम *));
व्योम bus_sort_bपढ़ोthfirst(काष्ठा bus_type *bus,
			   पूर्णांक (*compare)(स्थिर काष्ठा device *a,
					  स्थिर काष्ठा device *b));
/*
 * Bus notअगरiers: Get notअगरied of addition/removal of devices
 * and binding/unbinding of drivers to devices.
 * In the दीर्घ run, it should be a replacement क्रम the platक्रमm
 * notअगरy hooks.
 */
काष्ठा notअगरier_block;

बाह्य पूर्णांक bus_रेजिस्टर_notअगरier(काष्ठा bus_type *bus,
				 काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक bus_unरेजिस्टर_notअगरier(काष्ठा bus_type *bus,
				   काष्ठा notअगरier_block *nb);

/* All 4 notअगरers below get called with the target काष्ठा device *
 * as an argument. Note that those functions are likely to be called
 * with the device lock held in the core, so be careful.
 */
#घोषणा BUS_NOTIFY_ADD_DEVICE		0x00000001 /* device added */
#घोषणा BUS_NOTIFY_DEL_DEVICE		0x00000002 /* device to be हटाओd */
#घोषणा BUS_NOTIFY_REMOVED_DEVICE	0x00000003 /* device हटाओd */
#घोषणा BUS_NOTIFY_BIND_DRIVER		0x00000004 /* driver about to be
						      bound */
#घोषणा BUS_NOTIFY_BOUND_DRIVER		0x00000005 /* driver bound to device */
#घोषणा BUS_NOTIFY_UNBIND_DRIVER	0x00000006 /* driver about to be
						      unbound */
#घोषणा BUS_NOTIFY_UNBOUND_DRIVER	0x00000007 /* driver is unbound
						      from the device */
#घोषणा BUS_NOTIFY_DRIVER_NOT_BOUND	0x00000008 /* driver fails to be bound */

बाह्य काष्ठा kset *bus_get_kset(काष्ठा bus_type *bus);
बाह्य काष्ठा klist *bus_get_device_klist(काष्ठा bus_type *bus);

#पूर्ण_अगर
