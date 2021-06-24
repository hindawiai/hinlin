<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2001-2003 Patrick Mochel <mochel@osdl.org>
 * Copyright (c) 2004-2009 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Copyright (c) 2008-2012 Novell Inc.
 * Copyright (c) 2012-2019 Greg Kroah-Harपंचांगan <gregkh@linuxfoundation.org>
 * Copyright (c) 2012-2019 Linux Foundation
 *
 * Core driver model functions and काष्ठाures that should not be
 * shared outside of the drivers/base/ directory.
 *
 */
#समावेश <linux/notअगरier.h>

/**
 * काष्ठा subsys_निजी - काष्ठाure to hold the निजी to the driver core portions of the bus_type/class काष्ठाure.
 *
 * @subsys - the काष्ठा kset that defines this subप्रणाली
 * @devices_kset - the subप्रणाली's 'devices' directory
 * @पूर्णांकerfaces - list of subप्रणाली पूर्णांकerfaces associated
 * @mutex - protect the devices, and पूर्णांकerfaces lists.
 *
 * @drivers_kset - the list of drivers associated
 * @klist_devices - the klist to iterate over the @devices_kset
 * @klist_drivers - the klist to iterate over the @drivers_kset
 * @bus_notअगरier - the bus notअगरier list क्रम anything that cares about things
 *                 on this bus.
 * @bus - poपूर्णांकer back to the काष्ठा bus_type that this काष्ठाure is associated
 *        with.
 *
 * @glue_dirs - "glue" directory to put in-between the parent device to
 *              aव्योम namespace conflicts
 * @class - poपूर्णांकer back to the काष्ठा class that this काष्ठाure is associated
 *          with.
 *
 * This काष्ठाure is the one that is the actual kobject allowing काष्ठा
 * bus_type/class to be अटलally allocated safely.  Nothing outside of the
 * driver core should ever touch these fields.
 */
काष्ठा subsys_निजी अणु
	काष्ठा kset subsys;
	काष्ठा kset *devices_kset;
	काष्ठा list_head पूर्णांकerfaces;
	काष्ठा mutex mutex;

	काष्ठा kset *drivers_kset;
	काष्ठा klist klist_devices;
	काष्ठा klist klist_drivers;
	काष्ठा blocking_notअगरier_head bus_notअगरier;
	अचिन्हित पूर्णांक drivers_स्वतःprobe:1;
	काष्ठा bus_type *bus;

	काष्ठा kset glue_dirs;
	काष्ठा class *class;
पूर्ण;
#घोषणा to_subsys_निजी(obj) container_of(obj, काष्ठा subsys_निजी, subsys.kobj)

काष्ठा driver_निजी अणु
	काष्ठा kobject kobj;
	काष्ठा klist klist_devices;
	काष्ठा klist_node knode_bus;
	काष्ठा module_kobject *mkobj;
	काष्ठा device_driver *driver;
पूर्ण;
#घोषणा to_driver(obj) container_of(obj, काष्ठा driver_निजी, kobj)

/**
 * काष्ठा device_निजी - काष्ठाure to hold the निजी to the driver core portions of the device काष्ठाure.
 *
 * @klist_children - klist containing all children of this device
 * @knode_parent - node in sibling list
 * @knode_driver - node in driver list
 * @knode_bus - node in bus list
 * @knode_class - node in class list
 * @deferred_probe - entry in deferred_probe_list which is used to retry the
 *	binding of drivers which were unable to get all the resources needed by
 *	the device; typically because it depends on another driver getting
 *	probed first.
 * @async_driver - poपूर्णांकer to device driver aरुकोing probe via async_probe
 * @device - poपूर्णांकer back to the काष्ठा device that this काष्ठाure is
 * associated with.
 * @dead - This device is currently either in the process of or has been
 *	हटाओd from the प्रणाली. Any asynchronous events scheduled क्रम this
 *	device should निकास without taking any action.
 *
 * Nothing outside of the driver core should ever touch these fields.
 */
काष्ठा device_निजी अणु
	काष्ठा klist klist_children;
	काष्ठा klist_node knode_parent;
	काष्ठा klist_node knode_driver;
	काष्ठा klist_node knode_bus;
	काष्ठा klist_node knode_class;
	काष्ठा list_head deferred_probe;
	काष्ठा device_driver *async_driver;
	अक्षर *deferred_probe_reason;
	काष्ठा device *device;
	u8 dead:1;
पूर्ण;
#घोषणा to_device_निजी_parent(obj)	\
	container_of(obj, काष्ठा device_निजी, knode_parent)
#घोषणा to_device_निजी_driver(obj)	\
	container_of(obj, काष्ठा device_निजी, knode_driver)
#घोषणा to_device_निजी_bus(obj)	\
	container_of(obj, काष्ठा device_निजी, knode_bus)
#घोषणा to_device_निजी_class(obj)	\
	container_of(obj, काष्ठा device_निजी, knode_class)

/* initialisation functions */
बाह्य पूर्णांक devices_init(व्योम);
बाह्य पूर्णांक buses_init(व्योम);
बाह्य पूर्णांक classes_init(व्योम);
बाह्य पूर्णांक firmware_init(व्योम);
#अगर_घोषित CONFIG_SYS_HYPERVISOR
बाह्य पूर्णांक hypervisor_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक hypervisor_init(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर
बाह्य पूर्णांक platक्रमm_bus_init(व्योम);
बाह्य व्योम cpu_dev_init(व्योम);
बाह्य व्योम container_dev_init(व्योम);
#अगर_घोषित CONFIG_AUXILIARY_BUS
बाह्य व्योम auxiliary_bus_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम auxiliary_bus_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

काष्ठा kobject *भव_device_parent(काष्ठा device *dev);

बाह्य पूर्णांक bus_add_device(काष्ठा device *dev);
बाह्य व्योम bus_probe_device(काष्ठा device *dev);
बाह्य व्योम bus_हटाओ_device(काष्ठा device *dev);

बाह्य पूर्णांक bus_add_driver(काष्ठा device_driver *drv);
बाह्य व्योम bus_हटाओ_driver(काष्ठा device_driver *drv);
बाह्य व्योम device_release_driver_पूर्णांकernal(काष्ठा device *dev,
					   काष्ठा device_driver *drv,
					   काष्ठा device *parent);

बाह्य व्योम driver_detach(काष्ठा device_driver *drv);
बाह्य व्योम driver_deferred_probe_del(काष्ठा device *dev);
बाह्य व्योम device_set_deferred_probe_reason(स्थिर काष्ठा device *dev,
					     काष्ठा va_क्रमmat *vaf);
अटल अंतरभूत पूर्णांक driver_match_device(काष्ठा device_driver *drv,
				      काष्ठा device *dev)
अणु
	वापस drv->bus->match ? drv->bus->match(dev, drv) : 1;
पूर्ण
बाह्य bool driver_allows_async_probing(काष्ठा device_driver *drv);

बाह्य पूर्णांक driver_add_groups(काष्ठा device_driver *drv,
			     स्थिर काष्ठा attribute_group **groups);
बाह्य व्योम driver_हटाओ_groups(काष्ठा device_driver *drv,
				 स्थिर काष्ठा attribute_group **groups);
पूर्णांक device_driver_attach(काष्ठा device_driver *drv, काष्ठा device *dev);
व्योम device_driver_detach(काष्ठा device *dev);

बाह्य अक्षर *make_class_name(स्थिर अक्षर *name, काष्ठा kobject *kobj);

बाह्य पूर्णांक devres_release_all(काष्ठा device *dev);
बाह्य व्योम device_block_probing(व्योम);
बाह्य व्योम device_unblock_probing(व्योम);

/* /sys/devices directory */
बाह्य काष्ठा kset *devices_kset;
बाह्य व्योम devices_kset_move_last(काष्ठा device *dev);

#अगर defined(CONFIG_MODULES) && defined(CONFIG_SYSFS)
बाह्य व्योम module_add_driver(काष्ठा module *mod, काष्ठा device_driver *drv);
बाह्य व्योम module_हटाओ_driver(काष्ठा device_driver *drv);
#अन्यथा
अटल अंतरभूत व्योम module_add_driver(काष्ठा module *mod,
				     काष्ठा device_driver *drv) अणु पूर्ण
अटल अंतरभूत व्योम module_हटाओ_driver(काष्ठा device_driver *drv) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEVTMPFS
बाह्य पूर्णांक devपंचांगpfs_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक devपंचांगpfs_init(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/* Device links support */
बाह्य पूर्णांक device_links_पढ़ो_lock(व्योम);
बाह्य व्योम device_links_पढ़ो_unlock(पूर्णांक idx);
बाह्य पूर्णांक device_links_पढ़ो_lock_held(व्योम);
बाह्य पूर्णांक device_links_check_suppliers(काष्ठा device *dev);
बाह्य व्योम device_links_क्रमce_bind(काष्ठा device *dev);
बाह्य व्योम device_links_driver_bound(काष्ठा device *dev);
बाह्य व्योम device_links_driver_cleanup(काष्ठा device *dev);
बाह्य व्योम device_links_no_driver(काष्ठा device *dev);
बाह्य bool device_links_busy(काष्ठा device *dev);
बाह्य व्योम device_links_unbind_consumers(काष्ठा device *dev);
बाह्य व्योम fw_devlink_drivers_करोne(व्योम);

/* device pm support */
व्योम device_pm_move_to_tail(काष्ठा device *dev);

#अगर_घोषित CONFIG_DEVTMPFS
पूर्णांक devपंचांगpfs_create_node(काष्ठा device *dev);
पूर्णांक devपंचांगpfs_delete_node(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक devपंचांगpfs_create_node(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक devपंचांगpfs_delete_node(काष्ठा device *dev) अणु वापस 0; पूर्ण
#पूर्ण_अगर
