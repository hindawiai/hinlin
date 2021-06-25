<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * driver.c - centralized device driver management
 *
 * Copyright (c) 2002-3 Patrick Mochel
 * Copyright (c) 2002-3 Open Source Development Lअसल
 * Copyright (c) 2007 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Copyright (c) 2007 Novell Inc.
 */

#समावेश <linux/device/driver.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>
#समावेश "base.h"

अटल काष्ठा device *next_device(काष्ठा klist_iter *i)
अणु
	काष्ठा klist_node *n = klist_next(i);
	काष्ठा device *dev = शून्य;
	काष्ठा device_निजी *dev_prv;

	अगर (n) अणु
		dev_prv = to_device_निजी_driver(n);
		dev = dev_prv->device;
	पूर्ण
	वापस dev;
पूर्ण

/**
 * driver_क्रम_each_device - Iterator क्रम devices bound to a driver.
 * @drv: Driver we're iterating.
 * @start: Device to begin with
 * @data: Data to pass to the callback.
 * @fn: Function to call क्रम each device.
 *
 * Iterate over the @drv's list of devices calling @fn क्रम each one.
 */
पूर्णांक driver_क्रम_each_device(काष्ठा device_driver *drv, काष्ठा device *start,
			   व्योम *data, पूर्णांक (*fn)(काष्ठा device *, व्योम *))
अणु
	काष्ठा klist_iter i;
	काष्ठा device *dev;
	पूर्णांक error = 0;

	अगर (!drv)
		वापस -EINVAL;

	klist_iter_init_node(&drv->p->klist_devices, &i,
			     start ? &start->p->knode_driver : शून्य);
	जबतक (!error && (dev = next_device(&i)))
		error = fn(dev, data);
	klist_iter_निकास(&i);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(driver_क्रम_each_device);

/**
 * driver_find_device - device iterator क्रम locating a particular device.
 * @drv: The device's driver
 * @start: Device to begin with
 * @data: Data to pass to match function
 * @match: Callback function to check device
 *
 * This is similar to the driver_क्रम_each_device() function above, but
 * it वापसs a reference to a device that is 'found' क्रम later use, as
 * determined by the @match callback.
 *
 * The callback should वापस 0 अगर the device करोesn't match and non-zero
 * अगर it करोes.  If the callback वापसs non-zero, this function will
 * वापस to the caller and not iterate over any more devices.
 */
काष्ठा device *driver_find_device(काष्ठा device_driver *drv,
				  काष्ठा device *start, स्थिर व्योम *data,
				  पूर्णांक (*match)(काष्ठा device *dev, स्थिर व्योम *data))
अणु
	काष्ठा klist_iter i;
	काष्ठा device *dev;

	अगर (!drv || !drv->p)
		वापस शून्य;

	klist_iter_init_node(&drv->p->klist_devices, &i,
			     (start ? &start->p->knode_driver : शून्य));
	जबतक ((dev = next_device(&i)))
		अगर (match(dev, data) && get_device(dev))
			अवरोध;
	klist_iter_निकास(&i);
	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(driver_find_device);

/**
 * driver_create_file - create sysfs file क्रम driver.
 * @drv: driver.
 * @attr: driver attribute descriptor.
 */
पूर्णांक driver_create_file(काष्ठा device_driver *drv,
		       स्थिर काष्ठा driver_attribute *attr)
अणु
	पूर्णांक error;

	अगर (drv)
		error = sysfs_create_file(&drv->p->kobj, &attr->attr);
	अन्यथा
		error = -EINVAL;
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(driver_create_file);

/**
 * driver_हटाओ_file - हटाओ sysfs file क्रम driver.
 * @drv: driver.
 * @attr: driver attribute descriptor.
 */
व्योम driver_हटाओ_file(काष्ठा device_driver *drv,
			स्थिर काष्ठा driver_attribute *attr)
अणु
	अगर (drv)
		sysfs_हटाओ_file(&drv->p->kobj, &attr->attr);
पूर्ण
EXPORT_SYMBOL_GPL(driver_हटाओ_file);

पूर्णांक driver_add_groups(काष्ठा device_driver *drv,
		      स्थिर काष्ठा attribute_group **groups)
अणु
	वापस sysfs_create_groups(&drv->p->kobj, groups);
पूर्ण

व्योम driver_हटाओ_groups(काष्ठा device_driver *drv,
			  स्थिर काष्ठा attribute_group **groups)
अणु
	sysfs_हटाओ_groups(&drv->p->kobj, groups);
पूर्ण

/**
 * driver_रेजिस्टर - रेजिस्टर driver with bus
 * @drv: driver to रेजिस्टर
 *
 * We pass off most of the work to the bus_add_driver() call,
 * since most of the things we have to करो deal with the bus
 * काष्ठाures.
 */
पूर्णांक driver_रेजिस्टर(काष्ठा device_driver *drv)
अणु
	पूर्णांक ret;
	काष्ठा device_driver *other;

	अगर (!drv->bus->p) अणु
		pr_err("Driver '%s' was unable to register with bus_type '%s' because the bus was not initialized.\n",
			   drv->name, drv->bus->name);
		वापस -EINVAL;
	पूर्ण

	अगर ((drv->bus->probe && drv->probe) ||
	    (drv->bus->हटाओ && drv->हटाओ) ||
	    (drv->bus->shutकरोwn && drv->shutकरोwn))
		pr_warn("Driver '%s' needs updating - please use "
			"bus_type methods\n", drv->name);

	other = driver_find(drv->name, drv->bus);
	अगर (other) अणु
		pr_err("Error: Driver '%s' is already registered, "
			"aborting...\n", drv->name);
		वापस -EBUSY;
	पूर्ण

	ret = bus_add_driver(drv);
	अगर (ret)
		वापस ret;
	ret = driver_add_groups(drv, drv->groups);
	अगर (ret) अणु
		bus_हटाओ_driver(drv);
		वापस ret;
	पूर्ण
	kobject_uevent(&drv->p->kobj, KOBJ_ADD);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(driver_रेजिस्टर);

/**
 * driver_unरेजिस्टर - हटाओ driver from प्रणाली.
 * @drv: driver.
 *
 * Again, we pass off most of the work to the bus-level call.
 */
व्योम driver_unरेजिस्टर(काष्ठा device_driver *drv)
अणु
	अगर (!drv || !drv->p) अणु
		WARN(1, "Unexpected driver unregister!\n");
		वापस;
	पूर्ण
	driver_हटाओ_groups(drv, drv->groups);
	bus_हटाओ_driver(drv);
पूर्ण
EXPORT_SYMBOL_GPL(driver_unरेजिस्टर);

/**
 * driver_find - locate driver on a bus by its name.
 * @name: name of the driver.
 * @bus: bus to scan क्रम the driver.
 *
 * Call kset_find_obj() to iterate over list of drivers on
 * a bus to find driver by name. Return driver अगर found.
 *
 * This routine provides no locking to prevent the driver it वापसs
 * from being unरेजिस्टरed or unloaded जबतक the caller is using it.
 * The caller is responsible क्रम preventing this.
 */
काष्ठा device_driver *driver_find(स्थिर अक्षर *name, काष्ठा bus_type *bus)
अणु
	काष्ठा kobject *k = kset_find_obj(bus->p->drivers_kset, name);
	काष्ठा driver_निजी *priv;

	अगर (k) अणु
		/* Drop reference added by kset_find_obj() */
		kobject_put(k);
		priv = to_driver(k);
		वापस priv->driver;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(driver_find);
