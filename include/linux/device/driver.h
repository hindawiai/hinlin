<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * The driver-specअगरic portions of the driver model
 *
 * Copyright (c) 2001-2003 Patrick Mochel <mochel@osdl.org>
 * Copyright (c) 2004-2009 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Copyright (c) 2008-2009 Novell Inc.
 * Copyright (c) 2012-2019 Greg Kroah-Harपंचांगan <gregkh@linuxfoundation.org>
 * Copyright (c) 2012-2019 Linux Foundation
 *
 * See Documentation/driver-api/driver-model/ क्रम more inक्रमmation.
 */

#अगर_अघोषित _DEVICE_DRIVER_H_
#घोषणा _DEVICE_DRIVER_H_

#समावेश <linux/kobject.h>
#समावेश <linux/klist.h>
#समावेश <linux/pm.h>
#समावेश <linux/device/bus.h>

/**
 * क्रमागत probe_type - device driver probe type to try
 *	Device drivers may opt in क्रम special handling of their
 *	respective probe routines. This tells the core what to
 *	expect and prefer.
 *
 * @PROBE_DEFAULT_STRATEGY: Used by drivers that work equally well
 *	whether probed synchronously or asynchronously.
 * @PROBE_PREFER_ASYNCHRONOUS: Drivers क्रम "slow" devices which
 *	probing order is not essential क्रम booting the प्रणाली may
 *	opt पूर्णांकo executing their probes asynchronously.
 * @PROBE_FORCE_SYNCHRONOUS: Use this to annotate drivers that need
 *	their probe routines to run synchronously with driver and
 *	device registration (with the exception of -EPROBE_DEFER
 *	handling - re-probing always ends up being करोne asynchronously).
 *
 * Note that the end goal is to चयन the kernel to use asynchronous
 * probing by शेष, so annotating drivers with
 * %PROBE_PREFER_ASYNCHRONOUS is a temporary measure that allows us
 * to speed up boot process जबतक we are validating the rest of the
 * drivers.
 */
क्रमागत probe_type अणु
	PROBE_DEFAULT_STRATEGY,
	PROBE_PREFER_ASYNCHRONOUS,
	PROBE_FORCE_SYNCHRONOUS,
पूर्ण;

/**
 * काष्ठा device_driver - The basic device driver काष्ठाure
 * @name:	Name of the device driver.
 * @bus:	The bus which the device of this driver beदीर्घs to.
 * @owner:	The module owner.
 * @mod_name:	Used क्रम built-in modules.
 * @suppress_bind_attrs: Disables bind/unbind via sysfs.
 * @probe_type:	Type of the probe (synchronous or asynchronous) to use.
 * @of_match_table: The खोलो firmware table.
 * @acpi_match_table: The ACPI match table.
 * @probe:	Called to query the existence of a specअगरic device,
 *		whether this driver can work with it, and bind the driver
 *		to a specअगरic device.
 * @sync_state:	Called to sync device state to software state after all the
 *		state tracking consumers linked to this device (present at
 *		the समय of late_initcall) have successfully bound to a
 *		driver. If the device has no consumers, this function will
 *		be called at late_initcall_sync level. If the device has
 *		consumers that are never bound to a driver, this function
 *		will never get called until they करो.
 * @हटाओ:	Called when the device is हटाओd from the प्रणाली to
 *		unbind a device from this driver.
 * @shutकरोwn:	Called at shut-करोwn समय to quiesce the device.
 * @suspend:	Called to put the device to sleep mode. Usually to a
 *		low घातer state.
 * @resume:	Called to bring a device from sleep mode.
 * @groups:	Default attributes that get created by the driver core
 *		स्वतःmatically.
 * @dev_groups:	Additional attributes attached to device instance once
 *		it is bound to the driver.
 * @pm:		Power management operations of the device which matched
 *		this driver.
 * @coredump:	Called when sysfs entry is written to. The device driver
 *		is expected to call the dev_coredump API resulting in a
 *		uevent.
 * @p:		Driver core's निजी data, no one other than the driver
 *		core can touch this.
 *
 * The device driver-model tracks all of the drivers known to the प्रणाली.
 * The मुख्य reason क्रम this tracking is to enable the driver core to match
 * up drivers with new devices. Once drivers are known objects within the
 * प्रणाली, however, a number of other things become possible. Device drivers
 * can export inक्रमmation and configuration variables that are independent
 * of any specअगरic device.
 */
काष्ठा device_driver अणु
	स्थिर अक्षर		*name;
	काष्ठा bus_type		*bus;

	काष्ठा module		*owner;
	स्थिर अक्षर		*mod_name;	/* used क्रम built-in modules */

	bool suppress_bind_attrs;	/* disables bind/unbind via sysfs */
	क्रमागत probe_type probe_type;

	स्थिर काष्ठा of_device_id	*of_match_table;
	स्थिर काष्ठा acpi_device_id	*acpi_match_table;

	पूर्णांक (*probe) (काष्ठा device *dev);
	व्योम (*sync_state)(काष्ठा device *dev);
	पूर्णांक (*हटाओ) (काष्ठा device *dev);
	व्योम (*shutकरोwn) (काष्ठा device *dev);
	पूर्णांक (*suspend) (काष्ठा device *dev, pm_message_t state);
	पूर्णांक (*resume) (काष्ठा device *dev);
	स्थिर काष्ठा attribute_group **groups;
	स्थिर काष्ठा attribute_group **dev_groups;

	स्थिर काष्ठा dev_pm_ops *pm;
	व्योम (*coredump) (काष्ठा device *dev);

	काष्ठा driver_निजी *p;
पूर्ण;


बाह्य पूर्णांक __must_check driver_रेजिस्टर(काष्ठा device_driver *drv);
बाह्य व्योम driver_unरेजिस्टर(काष्ठा device_driver *drv);

बाह्य काष्ठा device_driver *driver_find(स्थिर अक्षर *name,
					 काष्ठा bus_type *bus);
बाह्य पूर्णांक driver_probe_करोne(व्योम);
बाह्य व्योम रुको_क्रम_device_probe(व्योम);

/* sysfs पूर्णांकerface क्रम exporting driver attributes */

काष्ठा driver_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा device_driver *driver, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा device_driver *driver, स्थिर अक्षर *buf,
			 माप_प्रकार count);
पूर्ण;

#घोषणा DRIVER_ATTR_RW(_name) \
	काष्ठा driver_attribute driver_attr_##_name = __ATTR_RW(_name)
#घोषणा DRIVER_ATTR_RO(_name) \
	काष्ठा driver_attribute driver_attr_##_name = __ATTR_RO(_name)
#घोषणा DRIVER_ATTR_WO(_name) \
	काष्ठा driver_attribute driver_attr_##_name = __ATTR_WO(_name)

बाह्य पूर्णांक __must_check driver_create_file(काष्ठा device_driver *driver,
					स्थिर काष्ठा driver_attribute *attr);
बाह्य व्योम driver_हटाओ_file(काष्ठा device_driver *driver,
			       स्थिर काष्ठा driver_attribute *attr);

बाह्य पूर्णांक __must_check driver_क्रम_each_device(काष्ठा device_driver *drv,
					       काष्ठा device *start,
					       व्योम *data,
					       पूर्णांक (*fn)(काष्ठा device *dev,
							 व्योम *));
काष्ठा device *driver_find_device(काष्ठा device_driver *drv,
				  काष्ठा device *start, स्थिर व्योम *data,
				  पूर्णांक (*match)(काष्ठा device *dev, स्थिर व्योम *data));

/**
 * driver_find_device_by_name - device iterator क्रम locating a particular device
 * of a specअगरic name.
 * @drv: the driver we're iterating
 * @name: name of the device to match
 */
अटल अंतरभूत काष्ठा device *driver_find_device_by_name(काष्ठा device_driver *drv,
							स्थिर अक्षर *name)
अणु
	वापस driver_find_device(drv, शून्य, name, device_match_name);
पूर्ण

/**
 * driver_find_device_by_of_node- device iterator क्रम locating a particular device
 * by of_node poपूर्णांकer.
 * @drv: the driver we're iterating
 * @np: of_node poपूर्णांकer to match.
 */
अटल अंतरभूत काष्ठा device *
driver_find_device_by_of_node(काष्ठा device_driver *drv,
			      स्थिर काष्ठा device_node *np)
अणु
	वापस driver_find_device(drv, शून्य, np, device_match_of_node);
पूर्ण

/**
 * driver_find_device_by_fwnode- device iterator क्रम locating a particular device
 * by fwnode poपूर्णांकer.
 * @drv: the driver we're iterating
 * @fwnode: fwnode poपूर्णांकer to match.
 */
अटल अंतरभूत काष्ठा device *
driver_find_device_by_fwnode(काष्ठा device_driver *drv,
			     स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस driver_find_device(drv, शून्य, fwnode, device_match_fwnode);
पूर्ण

/**
 * driver_find_device_by_devt- device iterator क्रम locating a particular device
 * by devt.
 * @drv: the driver we're iterating
 * @devt: devt poपूर्णांकer to match.
 */
अटल अंतरभूत काष्ठा device *driver_find_device_by_devt(काष्ठा device_driver *drv,
							dev_t devt)
अणु
	वापस driver_find_device(drv, शून्य, &devt, device_match_devt);
पूर्ण

अटल अंतरभूत काष्ठा device *driver_find_next_device(काष्ठा device_driver *drv,
						     काष्ठा device *start)
अणु
	वापस driver_find_device(drv, start, शून्य, device_match_any);
पूर्ण

#अगर_घोषित CONFIG_ACPI
/**
 * driver_find_device_by_acpi_dev : device iterator क्रम locating a particular
 * device matching the ACPI_COMPANION device.
 * @drv: the driver we're iterating
 * @adev: ACPI_COMPANION device to match.
 */
अटल अंतरभूत काष्ठा device *
driver_find_device_by_acpi_dev(काष्ठा device_driver *drv,
			       स्थिर काष्ठा acpi_device *adev)
अणु
	वापस driver_find_device(drv, शून्य, adev, device_match_acpi_dev);
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा device *
driver_find_device_by_acpi_dev(काष्ठा device_driver *drv, स्थिर व्योम *adev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक driver_deferred_probe_समयout;
व्योम driver_deferred_probe_add(काष्ठा device *dev);
पूर्णांक driver_deferred_probe_check_state(काष्ठा device *dev);
व्योम driver_init(व्योम);

/**
 * module_driver() - Helper macro क्रम drivers that करोn't करो anything
 * special in module init/निकास. This eliminates a lot of boilerplate.
 * Each module may only use this macro once, and calling it replaces
 * module_init() and module_निकास().
 *
 * @__driver: driver name
 * @__रेजिस्टर: रेजिस्टर function क्रम this driver type
 * @__unरेजिस्टर: unरेजिस्टर function क्रम this driver type
 * @...: Additional arguments to be passed to __रेजिस्टर and __unरेजिस्टर.
 *
 * Use this macro to स्थिरruct bus specअगरic macros क्रम रेजिस्टरing
 * drivers, and करो not use it on its own.
 */
#घोषणा module_driver(__driver, __रेजिस्टर, __unरेजिस्टर, ...) \
अटल पूर्णांक __init __driver##_init(व्योम) \
अणु \
	वापस __रेजिस्टर(&(__driver) , ##__VA_ARGS__); \
पूर्ण \
module_init(__driver##_init); \
अटल व्योम __निकास __driver##_निकास(व्योम) \
अणु \
	__unरेजिस्टर(&(__driver) , ##__VA_ARGS__); \
पूर्ण \
module_निकास(__driver##_निकास);

/**
 * builtin_driver() - Helper macro क्रम drivers that करोn't करो anything
 * special in init and have no निकास. This eliminates some boilerplate.
 * Each driver may only use this macro once, and calling it replaces
 * device_initcall (or in some हालs, the legacy __initcall).  This is
 * meant to be a direct parallel of module_driver() above but without
 * the __निकास stuff that is not used क्रम builtin हालs.
 *
 * @__driver: driver name
 * @__रेजिस्टर: रेजिस्टर function क्रम this driver type
 * @...: Additional arguments to be passed to __रेजिस्टर
 *
 * Use this macro to स्थिरruct bus specअगरic macros क्रम रेजिस्टरing
 * drivers, and करो not use it on its own.
 */
#घोषणा builtin_driver(__driver, __रेजिस्टर, ...) \
अटल पूर्णांक __init __driver##_init(व्योम) \
अणु \
	वापस __रेजिस्टर(&(__driver) , ##__VA_ARGS__); \
पूर्ण \
device_initcall(__driver##_init);

#पूर्ण_अगर	/* _DEVICE_DRIVER_H_ */
