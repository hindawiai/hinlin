<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bus.c - bus driver management
 *
 * Copyright (c) 2002-3 Patrick Mochel
 * Copyright (c) 2002-3 Open Source Development Lअसल
 * Copyright (c) 2007 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Copyright (c) 2007 Novell Inc.
 */

#समावेश <linux/async.h>
#समावेश <linux/device/bus.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>
#समावेश "base.h"
#समावेश "power/power.h"

/* /sys/devices/प्रणाली */
अटल काष्ठा kset *प्रणाली_kset;

#घोषणा to_bus_attr(_attr) container_of(_attr, काष्ठा bus_attribute, attr)

/*
 * sysfs bindings क्रम drivers
 */

#घोषणा to_drv_attr(_attr) container_of(_attr, काष्ठा driver_attribute, attr)

#घोषणा DRIVER_ATTR_IGNORE_LOCKDEP(_name, _mode, _show, _store) \
	काष्ठा driver_attribute driver_attr_##_name =		\
		__ATTR_IGNORE_LOCKDEP(_name, _mode, _show, _store)

अटल पूर्णांक __must_check bus_rescan_devices_helper(काष्ठा device *dev,
						व्योम *data);

अटल काष्ठा bus_type *bus_get(काष्ठा bus_type *bus)
अणु
	अगर (bus) अणु
		kset_get(&bus->p->subsys);
		वापस bus;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम bus_put(काष्ठा bus_type *bus)
अणु
	अगर (bus)
		kset_put(&bus->p->subsys);
पूर्ण

अटल sमाप_प्रकार drv_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा driver_attribute *drv_attr = to_drv_attr(attr);
	काष्ठा driver_निजी *drv_priv = to_driver(kobj);
	sमाप_प्रकार ret = -EIO;

	अगर (drv_attr->show)
		ret = drv_attr->show(drv_priv->driver, buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार drv_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा driver_attribute *drv_attr = to_drv_attr(attr);
	काष्ठा driver_निजी *drv_priv = to_driver(kobj);
	sमाप_प्रकार ret = -EIO;

	अगर (drv_attr->store)
		ret = drv_attr->store(drv_priv->driver, buf, count);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops driver_sysfs_ops = अणु
	.show	= drv_attr_show,
	.store	= drv_attr_store,
पूर्ण;

अटल व्योम driver_release(काष्ठा kobject *kobj)
अणु
	काष्ठा driver_निजी *drv_priv = to_driver(kobj);

	pr_debug("driver: '%s': %s\n", kobject_name(kobj), __func__);
	kमुक्त(drv_priv);
पूर्ण

अटल काष्ठा kobj_type driver_ktype = अणु
	.sysfs_ops	= &driver_sysfs_ops,
	.release	= driver_release,
पूर्ण;

/*
 * sysfs bindings क्रम buses
 */
अटल sमाप_प्रकार bus_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा bus_attribute *bus_attr = to_bus_attr(attr);
	काष्ठा subsys_निजी *subsys_priv = to_subsys_निजी(kobj);
	sमाप_प्रकार ret = 0;

	अगर (bus_attr->show)
		ret = bus_attr->show(subsys_priv->bus, buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार bus_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा bus_attribute *bus_attr = to_bus_attr(attr);
	काष्ठा subsys_निजी *subsys_priv = to_subsys_निजी(kobj);
	sमाप_प्रकार ret = 0;

	अगर (bus_attr->store)
		ret = bus_attr->store(subsys_priv->bus, buf, count);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops bus_sysfs_ops = अणु
	.show	= bus_attr_show,
	.store	= bus_attr_store,
पूर्ण;

पूर्णांक bus_create_file(काष्ठा bus_type *bus, काष्ठा bus_attribute *attr)
अणु
	पूर्णांक error;
	अगर (bus_get(bus)) अणु
		error = sysfs_create_file(&bus->p->subsys.kobj, &attr->attr);
		bus_put(bus);
	पूर्ण अन्यथा
		error = -EINVAL;
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(bus_create_file);

व्योम bus_हटाओ_file(काष्ठा bus_type *bus, काष्ठा bus_attribute *attr)
अणु
	अगर (bus_get(bus)) अणु
		sysfs_हटाओ_file(&bus->p->subsys.kobj, &attr->attr);
		bus_put(bus);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(bus_हटाओ_file);

अटल व्योम bus_release(काष्ठा kobject *kobj)
अणु
	काष्ठा subsys_निजी *priv = to_subsys_निजी(kobj);
	काष्ठा bus_type *bus = priv->bus;

	kमुक्त(priv);
	bus->p = शून्य;
पूर्ण

अटल काष्ठा kobj_type bus_ktype = अणु
	.sysfs_ops	= &bus_sysfs_ops,
	.release	= bus_release,
पूर्ण;

अटल पूर्णांक bus_uevent_filter(काष्ठा kset *kset, काष्ठा kobject *kobj)
अणु
	काष्ठा kobj_type *ktype = get_ktype(kobj);

	अगर (ktype == &bus_ktype)
		वापस 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kset_uevent_ops bus_uevent_ops = अणु
	.filter = bus_uevent_filter,
पूर्ण;

अटल काष्ठा kset *bus_kset;

/* Manually detach a device from its associated driver. */
अटल sमाप_प्रकार unbind_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	काष्ठा bus_type *bus = bus_get(drv->bus);
	काष्ठा device *dev;
	पूर्णांक err = -ENODEV;

	dev = bus_find_device_by_name(bus, शून्य, buf);
	अगर (dev && dev->driver == drv) अणु
		device_driver_detach(dev);
		err = count;
	पूर्ण
	put_device(dev);
	bus_put(bus);
	वापस err;
पूर्ण
अटल DRIVER_ATTR_IGNORE_LOCKDEP(unbind, S_IWUSR, शून्य, unbind_store);

/*
 * Manually attach a device to a driver.
 * Note: the driver must want to bind to the device,
 * it is not possible to override the driver's id table.
 */
अटल sमाप_प्रकार bind_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
			  माप_प्रकार count)
अणु
	काष्ठा bus_type *bus = bus_get(drv->bus);
	काष्ठा device *dev;
	पूर्णांक err = -ENODEV;

	dev = bus_find_device_by_name(bus, शून्य, buf);
	अगर (dev && dev->driver == शून्य && driver_match_device(drv, dev)) अणु
		err = device_driver_attach(drv, dev);

		अगर (err > 0) अणु
			/* success */
			err = count;
		पूर्ण अन्यथा अगर (err == 0) अणु
			/* driver didn't accept device */
			err = -ENODEV;
		पूर्ण
	पूर्ण
	put_device(dev);
	bus_put(bus);
	वापस err;
पूर्ण
अटल DRIVER_ATTR_IGNORE_LOCKDEP(bind, S_IWUSR, शून्य, bind_store);

अटल sमाप_प्रकार drivers_स्वतःprobe_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", bus->p->drivers_स्वतःprobe);
पूर्ण

अटल sमाप_प्रकार drivers_स्वतःprobe_store(काष्ठा bus_type *bus,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (buf[0] == '0')
		bus->p->drivers_स्वतःprobe = 0;
	अन्यथा
		bus->p->drivers_स्वतःprobe = 1;
	वापस count;
पूर्ण

अटल sमाप_प्रकार drivers_probe_store(काष्ठा bus_type *bus,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा device *dev;
	पूर्णांक err = -EINVAL;

	dev = bus_find_device_by_name(bus, शून्य, buf);
	अगर (!dev)
		वापस -ENODEV;
	अगर (bus_rescan_devices_helper(dev, शून्य) == 0)
		err = count;
	put_device(dev);
	वापस err;
पूर्ण

अटल काष्ठा device *next_device(काष्ठा klist_iter *i)
अणु
	काष्ठा klist_node *n = klist_next(i);
	काष्ठा device *dev = शून्य;
	काष्ठा device_निजी *dev_prv;

	अगर (n) अणु
		dev_prv = to_device_निजी_bus(n);
		dev = dev_prv->device;
	पूर्ण
	वापस dev;
पूर्ण

/**
 * bus_क्रम_each_dev - device iterator.
 * @bus: bus type.
 * @start: device to start iterating from.
 * @data: data क्रम the callback.
 * @fn: function to be called क्रम each device.
 *
 * Iterate over @bus's list of devices, and call @fn क्रम each,
 * passing it @data. If @start is not शून्य, we use that device to
 * begin iterating from.
 *
 * We check the वापस of @fn each समय. If it वापसs anything
 * other than 0, we अवरोध out and वापस that value.
 *
 * NOTE: The device that वापसs a non-zero value is not retained
 * in any way, nor is its refcount incremented. If the caller needs
 * to retain this data, it should करो so, and increment the reference
 * count in the supplied callback.
 */
पूर्णांक bus_क्रम_each_dev(काष्ठा bus_type *bus, काष्ठा device *start,
		     व्योम *data, पूर्णांक (*fn)(काष्ठा device *, व्योम *))
अणु
	काष्ठा klist_iter i;
	काष्ठा device *dev;
	पूर्णांक error = 0;

	अगर (!bus || !bus->p)
		वापस -EINVAL;

	klist_iter_init_node(&bus->p->klist_devices, &i,
			     (start ? &start->p->knode_bus : शून्य));
	जबतक (!error && (dev = next_device(&i)))
		error = fn(dev, data);
	klist_iter_निकास(&i);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(bus_क्रम_each_dev);

/**
 * bus_find_device - device iterator क्रम locating a particular device.
 * @bus: bus type
 * @start: Device to begin with
 * @data: Data to pass to match function
 * @match: Callback function to check device
 *
 * This is similar to the bus_क्रम_each_dev() function above, but it
 * वापसs a reference to a device that is 'found' क्रम later use, as
 * determined by the @match callback.
 *
 * The callback should वापस 0 अगर the device करोesn't match and non-zero
 * अगर it करोes.  If the callback वापसs non-zero, this function will
 * वापस to the caller and not iterate over any more devices.
 */
काष्ठा device *bus_find_device(काष्ठा bus_type *bus,
			       काष्ठा device *start, स्थिर व्योम *data,
			       पूर्णांक (*match)(काष्ठा device *dev, स्थिर व्योम *data))
अणु
	काष्ठा klist_iter i;
	काष्ठा device *dev;

	अगर (!bus || !bus->p)
		वापस शून्य;

	klist_iter_init_node(&bus->p->klist_devices, &i,
			     (start ? &start->p->knode_bus : शून्य));
	जबतक ((dev = next_device(&i)))
		अगर (match(dev, data) && get_device(dev))
			अवरोध;
	klist_iter_निकास(&i);
	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(bus_find_device);

/**
 * subsys_find_device_by_id - find a device with a specअगरic क्रमागतeration number
 * @subsys: subप्रणाली
 * @id: index 'id' in काष्ठा device
 * @hपूर्णांक: device to check first
 *
 * Check the hपूर्णांक's next object and अगर it is a match वापस it directly,
 * otherwise, fall back to a full list search. Either way a reference क्रम
 * the वापसed object is taken.
 */
काष्ठा device *subsys_find_device_by_id(काष्ठा bus_type *subsys, अचिन्हित पूर्णांक id,
					काष्ठा device *hपूर्णांक)
अणु
	काष्ठा klist_iter i;
	काष्ठा device *dev;

	अगर (!subsys)
		वापस शून्य;

	अगर (hपूर्णांक) अणु
		klist_iter_init_node(&subsys->p->klist_devices, &i, &hपूर्णांक->p->knode_bus);
		dev = next_device(&i);
		अगर (dev && dev->id == id && get_device(dev)) अणु
			klist_iter_निकास(&i);
			वापस dev;
		पूर्ण
		klist_iter_निकास(&i);
	पूर्ण

	klist_iter_init_node(&subsys->p->klist_devices, &i, शून्य);
	जबतक ((dev = next_device(&i))) अणु
		अगर (dev->id == id && get_device(dev)) अणु
			klist_iter_निकास(&i);
			वापस dev;
		पूर्ण
	पूर्ण
	klist_iter_निकास(&i);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(subsys_find_device_by_id);

अटल काष्ठा device_driver *next_driver(काष्ठा klist_iter *i)
अणु
	काष्ठा klist_node *n = klist_next(i);
	काष्ठा driver_निजी *drv_priv;

	अगर (n) अणु
		drv_priv = container_of(n, काष्ठा driver_निजी, knode_bus);
		वापस drv_priv->driver;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * bus_क्रम_each_drv - driver iterator
 * @bus: bus we're dealing with.
 * @start: driver to start iterating on.
 * @data: data to pass to the callback.
 * @fn: function to call क्रम each driver.
 *
 * This is nearly identical to the device iterator above.
 * We iterate over each driver that beदीर्घs to @bus, and call
 * @fn क्रम each. If @fn वापसs anything but 0, we अवरोध out
 * and वापस it. If @start is not शून्य, we use it as the head
 * of the list.
 *
 * NOTE: we करोn't वापस the driver that वापसs a non-zero
 * value, nor करो we leave the reference count incremented क्रम that
 * driver. If the caller needs to know that info, it must set it
 * in the callback. It must also be sure to increment the refcount
 * so it करोesn't disappear beक्रमe वापसing to the caller.
 */
पूर्णांक bus_क्रम_each_drv(काष्ठा bus_type *bus, काष्ठा device_driver *start,
		     व्योम *data, पूर्णांक (*fn)(काष्ठा device_driver *, व्योम *))
अणु
	काष्ठा klist_iter i;
	काष्ठा device_driver *drv;
	पूर्णांक error = 0;

	अगर (!bus)
		वापस -EINVAL;

	klist_iter_init_node(&bus->p->klist_drivers, &i,
			     start ? &start->p->knode_bus : शून्य);
	जबतक ((drv = next_driver(&i)) && !error)
		error = fn(drv, data);
	klist_iter_निकास(&i);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(bus_क्रम_each_drv);

/**
 * bus_add_device - add device to bus
 * @dev: device being added
 *
 * - Add device's bus attributes.
 * - Create links to device's bus.
 * - Add the device to its bus's list of devices.
 */
पूर्णांक bus_add_device(काष्ठा device *dev)
अणु
	काष्ठा bus_type *bus = bus_get(dev->bus);
	पूर्णांक error = 0;

	अगर (bus) अणु
		pr_debug("bus: '%s': add device %s\n", bus->name, dev_name(dev));
		error = device_add_groups(dev, bus->dev_groups);
		अगर (error)
			जाओ out_put;
		error = sysfs_create_link(&bus->p->devices_kset->kobj,
						&dev->kobj, dev_name(dev));
		अगर (error)
			जाओ out_groups;
		error = sysfs_create_link(&dev->kobj,
				&dev->bus->p->subsys.kobj, "subsystem");
		अगर (error)
			जाओ out_subsys;
		klist_add_tail(&dev->p->knode_bus, &bus->p->klist_devices);
	पूर्ण
	वापस 0;

out_subsys:
	sysfs_हटाओ_link(&bus->p->devices_kset->kobj, dev_name(dev));
out_groups:
	device_हटाओ_groups(dev, bus->dev_groups);
out_put:
	bus_put(dev->bus);
	वापस error;
पूर्ण

/**
 * bus_probe_device - probe drivers क्रम a new device
 * @dev: device to probe
 *
 * - Automatically probe क्रम a driver अगर the bus allows it.
 */
व्योम bus_probe_device(काष्ठा device *dev)
अणु
	काष्ठा bus_type *bus = dev->bus;
	काष्ठा subsys_पूर्णांकerface *sअगर;

	अगर (!bus)
		वापस;

	अगर (bus->p->drivers_स्वतःprobe)
		device_initial_probe(dev);

	mutex_lock(&bus->p->mutex);
	list_क्रम_each_entry(sअगर, &bus->p->पूर्णांकerfaces, node)
		अगर (sअगर->add_dev)
			sअगर->add_dev(dev, sअगर);
	mutex_unlock(&bus->p->mutex);
पूर्ण

/**
 * bus_हटाओ_device - हटाओ device from bus
 * @dev: device to be हटाओd
 *
 * - Remove device from all पूर्णांकerfaces.
 * - Remove symlink from bus' directory.
 * - Delete device from bus's list.
 * - Detach from its driver.
 * - Drop reference taken in bus_add_device().
 */
व्योम bus_हटाओ_device(काष्ठा device *dev)
अणु
	काष्ठा bus_type *bus = dev->bus;
	काष्ठा subsys_पूर्णांकerface *sअगर;

	अगर (!bus)
		वापस;

	mutex_lock(&bus->p->mutex);
	list_क्रम_each_entry(sअगर, &bus->p->पूर्णांकerfaces, node)
		अगर (sअगर->हटाओ_dev)
			sअगर->हटाओ_dev(dev, sअगर);
	mutex_unlock(&bus->p->mutex);

	sysfs_हटाओ_link(&dev->kobj, "subsystem");
	sysfs_हटाओ_link(&dev->bus->p->devices_kset->kobj,
			  dev_name(dev));
	device_हटाओ_groups(dev, dev->bus->dev_groups);
	अगर (klist_node_attached(&dev->p->knode_bus))
		klist_del(&dev->p->knode_bus);

	pr_debug("bus: '%s': remove device %s\n",
		 dev->bus->name, dev_name(dev));
	device_release_driver(dev);
	bus_put(dev->bus);
पूर्ण

अटल पूर्णांक __must_check add_bind_files(काष्ठा device_driver *drv)
अणु
	पूर्णांक ret;

	ret = driver_create_file(drv, &driver_attr_unbind);
	अगर (ret == 0) अणु
		ret = driver_create_file(drv, &driver_attr_bind);
		अगर (ret)
			driver_हटाओ_file(drv, &driver_attr_unbind);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम हटाओ_bind_files(काष्ठा device_driver *drv)
अणु
	driver_हटाओ_file(drv, &driver_attr_bind);
	driver_हटाओ_file(drv, &driver_attr_unbind);
पूर्ण

अटल BUS_ATTR_WO(drivers_probe);
अटल BUS_ATTR_RW(drivers_स्वतःprobe);

अटल पूर्णांक add_probe_files(काष्ठा bus_type *bus)
अणु
	पूर्णांक retval;

	retval = bus_create_file(bus, &bus_attr_drivers_probe);
	अगर (retval)
		जाओ out;

	retval = bus_create_file(bus, &bus_attr_drivers_स्वतःprobe);
	अगर (retval)
		bus_हटाओ_file(bus, &bus_attr_drivers_probe);
out:
	वापस retval;
पूर्ण

अटल व्योम हटाओ_probe_files(काष्ठा bus_type *bus)
अणु
	bus_हटाओ_file(bus, &bus_attr_drivers_स्वतःprobe);
	bus_हटाओ_file(bus, &bus_attr_drivers_probe);
पूर्ण

अटल sमाप_प्रकार uevent_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	पूर्णांक rc;

	rc = kobject_synth_uevent(&drv->p->kobj, buf, count);
	वापस rc ? rc : count;
पूर्ण
अटल DRIVER_ATTR_WO(uevent);

/**
 * bus_add_driver - Add a driver to the bus.
 * @drv: driver.
 */
पूर्णांक bus_add_driver(काष्ठा device_driver *drv)
अणु
	काष्ठा bus_type *bus;
	काष्ठा driver_निजी *priv;
	पूर्णांक error = 0;

	bus = bus_get(drv->bus);
	अगर (!bus)
		वापस -EINVAL;

	pr_debug("bus: '%s': add driver %s\n", bus->name, drv->name);

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		error = -ENOMEM;
		जाओ out_put_bus;
	पूर्ण
	klist_init(&priv->klist_devices, शून्य, शून्य);
	priv->driver = drv;
	drv->p = priv;
	priv->kobj.kset = bus->p->drivers_kset;
	error = kobject_init_and_add(&priv->kobj, &driver_ktype, शून्य,
				     "%s", drv->name);
	अगर (error)
		जाओ out_unरेजिस्टर;

	klist_add_tail(&priv->knode_bus, &bus->p->klist_drivers);
	अगर (drv->bus->p->drivers_स्वतःprobe) अणु
		error = driver_attach(drv);
		अगर (error)
			जाओ out_unरेजिस्टर;
	पूर्ण
	module_add_driver(drv->owner, drv);

	error = driver_create_file(drv, &driver_attr_uevent);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "%s: uevent attr (%s) failed\n",
			__func__, drv->name);
	पूर्ण
	error = driver_add_groups(drv, bus->drv_groups);
	अगर (error) अणु
		/* How the hell करो we get out of this pickle? Give up */
		prपूर्णांकk(KERN_ERR "%s: driver_add_groups(%s) failed\n",
			__func__, drv->name);
	पूर्ण

	अगर (!drv->suppress_bind_attrs) अणु
		error = add_bind_files(drv);
		अगर (error) अणु
			/* Ditto */
			prपूर्णांकk(KERN_ERR "%s: add_bind_files(%s) failed\n",
				__func__, drv->name);
		पूर्ण
	पूर्ण

	वापस 0;

out_unरेजिस्टर:
	kobject_put(&priv->kobj);
	/* drv->p is मुक्तd in driver_release()  */
	drv->p = शून्य;
out_put_bus:
	bus_put(bus);
	वापस error;
पूर्ण

/**
 * bus_हटाओ_driver - delete driver from bus's knowledge.
 * @drv: driver.
 *
 * Detach the driver from the devices it controls, and हटाओ
 * it from its bus's list of drivers. Finally, we drop the reference
 * to the bus we took in bus_add_driver().
 */
व्योम bus_हटाओ_driver(काष्ठा device_driver *drv)
अणु
	अगर (!drv->bus)
		वापस;

	अगर (!drv->suppress_bind_attrs)
		हटाओ_bind_files(drv);
	driver_हटाओ_groups(drv, drv->bus->drv_groups);
	driver_हटाओ_file(drv, &driver_attr_uevent);
	klist_हटाओ(&drv->p->knode_bus);
	pr_debug("bus: '%s': remove driver %s\n", drv->bus->name, drv->name);
	driver_detach(drv);
	module_हटाओ_driver(drv);
	kobject_put(&drv->p->kobj);
	bus_put(drv->bus);
पूर्ण

/* Helper क्रम bus_rescan_devices's iter */
अटल पूर्णांक __must_check bus_rescan_devices_helper(काष्ठा device *dev,
						  व्योम *data)
अणु
	पूर्णांक ret = 0;

	अगर (!dev->driver) अणु
		अगर (dev->parent && dev->bus->need_parent_lock)
			device_lock(dev->parent);
		ret = device_attach(dev);
		अगर (dev->parent && dev->bus->need_parent_lock)
			device_unlock(dev->parent);
	पूर्ण
	वापस ret < 0 ? ret : 0;
पूर्ण

/**
 * bus_rescan_devices - rescan devices on the bus क्रम possible drivers
 * @bus: the bus to scan.
 *
 * This function will look क्रम devices on the bus with no driver
 * attached and rescan it against existing drivers to see अगर it matches
 * any by calling device_attach() क्रम the unbound devices.
 */
पूर्णांक bus_rescan_devices(काष्ठा bus_type *bus)
अणु
	वापस bus_क्रम_each_dev(bus, शून्य, शून्य, bus_rescan_devices_helper);
पूर्ण
EXPORT_SYMBOL_GPL(bus_rescan_devices);

/**
 * device_reprobe - हटाओ driver क्रम a device and probe क्रम a new driver
 * @dev: the device to reprobe
 *
 * This function detaches the attached driver (अगर any) क्रम the given
 * device and restarts the driver probing process.  It is पूर्णांकended
 * to use अगर probing criteria changed during a devices lअगरeसमय and
 * driver attachment should change accordingly.
 */
पूर्णांक device_reprobe(काष्ठा device *dev)
अणु
	अगर (dev->driver)
		device_driver_detach(dev);
	वापस bus_rescan_devices_helper(dev, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(device_reprobe);

अटल पूर्णांक bus_add_groups(काष्ठा bus_type *bus,
			  स्थिर काष्ठा attribute_group **groups)
अणु
	वापस sysfs_create_groups(&bus->p->subsys.kobj, groups);
पूर्ण

अटल व्योम bus_हटाओ_groups(काष्ठा bus_type *bus,
			      स्थिर काष्ठा attribute_group **groups)
अणु
	sysfs_हटाओ_groups(&bus->p->subsys.kobj, groups);
पूर्ण

अटल व्योम klist_devices_get(काष्ठा klist_node *n)
अणु
	काष्ठा device_निजी *dev_prv = to_device_निजी_bus(n);
	काष्ठा device *dev = dev_prv->device;

	get_device(dev);
पूर्ण

अटल व्योम klist_devices_put(काष्ठा klist_node *n)
अणु
	काष्ठा device_निजी *dev_prv = to_device_निजी_bus(n);
	काष्ठा device *dev = dev_prv->device;

	put_device(dev);
पूर्ण

अटल sमाप_प्रकार bus_uevent_store(काष्ठा bus_type *bus,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;

	rc = kobject_synth_uevent(&bus->p->subsys.kobj, buf, count);
	वापस rc ? rc : count;
पूर्ण
/*
 * "open code" the old BUS_ATTR() macro here.  We want to use BUS_ATTR_WO()
 * here, but can not use it as earlier in the file we have
 * DEVICE_ATTR_WO(uevent), which would cause a clash with the with the store
 * function name.
 */
अटल काष्ठा bus_attribute bus_attr_uevent = __ATTR(uevent, S_IWUSR, शून्य,
						     bus_uevent_store);

/**
 * bus_रेजिस्टर - रेजिस्टर a driver-core subप्रणाली
 * @bus: bus to रेजिस्टर
 *
 * Once we have that, we रेजिस्टर the bus with the kobject
 * infraकाष्ठाure, then रेजिस्टर the children subप्रणालीs it has:
 * the devices and drivers that beदीर्घ to the subप्रणाली.
 */
पूर्णांक bus_रेजिस्टर(काष्ठा bus_type *bus)
अणु
	पूर्णांक retval;
	काष्ठा subsys_निजी *priv;
	काष्ठा lock_class_key *key = &bus->lock_key;

	priv = kzalloc(माप(काष्ठा subsys_निजी), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->bus = bus;
	bus->p = priv;

	BLOCKING_INIT_NOTIFIER_HEAD(&priv->bus_notअगरier);

	retval = kobject_set_name(&priv->subsys.kobj, "%s", bus->name);
	अगर (retval)
		जाओ out;

	priv->subsys.kobj.kset = bus_kset;
	priv->subsys.kobj.ktype = &bus_ktype;
	priv->drivers_स्वतःprobe = 1;

	retval = kset_रेजिस्टर(&priv->subsys);
	अगर (retval)
		जाओ out;

	retval = bus_create_file(bus, &bus_attr_uevent);
	अगर (retval)
		जाओ bus_uevent_fail;

	priv->devices_kset = kset_create_and_add("devices", शून्य,
						 &priv->subsys.kobj);
	अगर (!priv->devices_kset) अणु
		retval = -ENOMEM;
		जाओ bus_devices_fail;
	पूर्ण

	priv->drivers_kset = kset_create_and_add("drivers", शून्य,
						 &priv->subsys.kobj);
	अगर (!priv->drivers_kset) अणु
		retval = -ENOMEM;
		जाओ bus_drivers_fail;
	पूर्ण

	INIT_LIST_HEAD(&priv->पूर्णांकerfaces);
	__mutex_init(&priv->mutex, "subsys mutex", key);
	klist_init(&priv->klist_devices, klist_devices_get, klist_devices_put);
	klist_init(&priv->klist_drivers, शून्य, शून्य);

	retval = add_probe_files(bus);
	अगर (retval)
		जाओ bus_probe_files_fail;

	retval = bus_add_groups(bus, bus->bus_groups);
	अगर (retval)
		जाओ bus_groups_fail;

	pr_debug("bus: '%s': registered\n", bus->name);
	वापस 0;

bus_groups_fail:
	हटाओ_probe_files(bus);
bus_probe_files_fail:
	kset_unरेजिस्टर(bus->p->drivers_kset);
bus_drivers_fail:
	kset_unरेजिस्टर(bus->p->devices_kset);
bus_devices_fail:
	bus_हटाओ_file(bus, &bus_attr_uevent);
bus_uevent_fail:
	kset_unरेजिस्टर(&bus->p->subsys);
out:
	kमुक्त(bus->p);
	bus->p = शून्य;
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(bus_रेजिस्टर);

/**
 * bus_unरेजिस्टर - हटाओ a bus from the प्रणाली
 * @bus: bus.
 *
 * Unरेजिस्टर the child subप्रणालीs and the bus itself.
 * Finally, we call bus_put() to release the refcount
 */
व्योम bus_unरेजिस्टर(काष्ठा bus_type *bus)
अणु
	pr_debug("bus: '%s': unregistering\n", bus->name);
	अगर (bus->dev_root)
		device_unरेजिस्टर(bus->dev_root);
	bus_हटाओ_groups(bus, bus->bus_groups);
	हटाओ_probe_files(bus);
	kset_unरेजिस्टर(bus->p->drivers_kset);
	kset_unरेजिस्टर(bus->p->devices_kset);
	bus_हटाओ_file(bus, &bus_attr_uevent);
	kset_unरेजिस्टर(&bus->p->subsys);
पूर्ण
EXPORT_SYMBOL_GPL(bus_unरेजिस्टर);

पूर्णांक bus_रेजिस्टर_notअगरier(काष्ठा bus_type *bus, काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&bus->p->bus_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL_GPL(bus_रेजिस्टर_notअगरier);

पूर्णांक bus_unरेजिस्टर_notअगरier(काष्ठा bus_type *bus, काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&bus->p->bus_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL_GPL(bus_unरेजिस्टर_notअगरier);

काष्ठा kset *bus_get_kset(काष्ठा bus_type *bus)
अणु
	वापस &bus->p->subsys;
पूर्ण
EXPORT_SYMBOL_GPL(bus_get_kset);

काष्ठा klist *bus_get_device_klist(काष्ठा bus_type *bus)
अणु
	वापस &bus->p->klist_devices;
पूर्ण
EXPORT_SYMBOL_GPL(bus_get_device_klist);

/*
 * Yes, this क्रमcibly अवरोधs the klist असलtraction temporarily.  It
 * just wants to sort the klist, not change reference counts and
 * take/drop locks rapidly in the process.  It करोes all this जबतक
 * holding the lock क्रम the list, so objects can't otherwise be
 * added/हटाओd जबतक we're swizzling.
 */
अटल व्योम device_insertion_sort_klist(काष्ठा device *a, काष्ठा list_head *list,
					पूर्णांक (*compare)(स्थिर काष्ठा device *a,
							स्थिर काष्ठा device *b))
अणु
	काष्ठा klist_node *n;
	काष्ठा device_निजी *dev_prv;
	काष्ठा device *b;

	list_क्रम_each_entry(n, list, n_node) अणु
		dev_prv = to_device_निजी_bus(n);
		b = dev_prv->device;
		अगर (compare(a, b) <= 0) अणु
			list_move_tail(&a->p->knode_bus.n_node,
				       &b->p->knode_bus.n_node);
			वापस;
		पूर्ण
	पूर्ण
	list_move_tail(&a->p->knode_bus.n_node, list);
पूर्ण

व्योम bus_sort_bपढ़ोthfirst(काष्ठा bus_type *bus,
			   पूर्णांक (*compare)(स्थिर काष्ठा device *a,
					  स्थिर काष्ठा device *b))
अणु
	LIST_HEAD(sorted_devices);
	काष्ठा klist_node *n, *पंचांगp;
	काष्ठा device_निजी *dev_prv;
	काष्ठा device *dev;
	काष्ठा klist *device_klist;

	device_klist = bus_get_device_klist(bus);

	spin_lock(&device_klist->k_lock);
	list_क्रम_each_entry_safe(n, पंचांगp, &device_klist->k_list, n_node) अणु
		dev_prv = to_device_निजी_bus(n);
		dev = dev_prv->device;
		device_insertion_sort_klist(dev, &sorted_devices, compare);
	पूर्ण
	list_splice(&sorted_devices, &device_klist->k_list);
	spin_unlock(&device_klist->k_lock);
पूर्ण
EXPORT_SYMBOL_GPL(bus_sort_bपढ़ोthfirst);

/**
 * subsys_dev_iter_init - initialize subsys device iterator
 * @iter: subsys iterator to initialize
 * @subsys: the subsys we wanna iterate over
 * @start: the device to start iterating from, अगर any
 * @type: device_type of the devices to iterate over, शून्य क्रम all
 *
 * Initialize subsys iterator @iter such that it iterates over devices
 * of @subsys.  If @start is set, the list iteration will start there,
 * otherwise अगर it is शून्य, the iteration starts at the beginning of
 * the list.
 */
व्योम subsys_dev_iter_init(काष्ठा subsys_dev_iter *iter, काष्ठा bus_type *subsys,
			  काष्ठा device *start, स्थिर काष्ठा device_type *type)
अणु
	काष्ठा klist_node *start_knode = शून्य;

	अगर (start)
		start_knode = &start->p->knode_bus;
	klist_iter_init_node(&subsys->p->klist_devices, &iter->ki, start_knode);
	iter->type = type;
पूर्ण
EXPORT_SYMBOL_GPL(subsys_dev_iter_init);

/**
 * subsys_dev_iter_next - iterate to the next device
 * @iter: subsys iterator to proceed
 *
 * Proceed @iter to the next device and वापस it.  Returns शून्य अगर
 * iteration is complete.
 *
 * The वापसed device is referenced and won't be released till
 * iterator is proceed to the next device or निकासed.  The caller is
 * मुक्त to करो whatever it wants to करो with the device including
 * calling back पूर्णांकo subsys code.
 */
काष्ठा device *subsys_dev_iter_next(काष्ठा subsys_dev_iter *iter)
अणु
	काष्ठा klist_node *knode;
	काष्ठा device *dev;

	क्रम (;;) अणु
		knode = klist_next(&iter->ki);
		अगर (!knode)
			वापस शून्य;
		dev = to_device_निजी_bus(knode)->device;
		अगर (!iter->type || iter->type == dev->type)
			वापस dev;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(subsys_dev_iter_next);

/**
 * subsys_dev_iter_निकास - finish iteration
 * @iter: subsys iterator to finish
 *
 * Finish an iteration.  Always call this function after iteration is
 * complete whether the iteration ran till the end or not.
 */
व्योम subsys_dev_iter_निकास(काष्ठा subsys_dev_iter *iter)
अणु
	klist_iter_निकास(&iter->ki);
पूर्ण
EXPORT_SYMBOL_GPL(subsys_dev_iter_निकास);

पूर्णांक subsys_पूर्णांकerface_रेजिस्टर(काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	काष्ठा bus_type *subsys;
	काष्ठा subsys_dev_iter iter;
	काष्ठा device *dev;

	अगर (!sअगर || !sअगर->subsys)
		वापस -ENODEV;

	subsys = bus_get(sअगर->subsys);
	अगर (!subsys)
		वापस -EINVAL;

	mutex_lock(&subsys->p->mutex);
	list_add_tail(&sअगर->node, &subsys->p->पूर्णांकerfaces);
	अगर (sअगर->add_dev) अणु
		subsys_dev_iter_init(&iter, subsys, शून्य, शून्य);
		जबतक ((dev = subsys_dev_iter_next(&iter)))
			sअगर->add_dev(dev, sअगर);
		subsys_dev_iter_निकास(&iter);
	पूर्ण
	mutex_unlock(&subsys->p->mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(subsys_पूर्णांकerface_रेजिस्टर);

व्योम subsys_पूर्णांकerface_unरेजिस्टर(काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	काष्ठा bus_type *subsys;
	काष्ठा subsys_dev_iter iter;
	काष्ठा device *dev;

	अगर (!sअगर || !sअगर->subsys)
		वापस;

	subsys = sअगर->subsys;

	mutex_lock(&subsys->p->mutex);
	list_del_init(&sअगर->node);
	अगर (sअगर->हटाओ_dev) अणु
		subsys_dev_iter_init(&iter, subsys, शून्य, शून्य);
		जबतक ((dev = subsys_dev_iter_next(&iter)))
			sअगर->हटाओ_dev(dev, sअगर);
		subsys_dev_iter_निकास(&iter);
	पूर्ण
	mutex_unlock(&subsys->p->mutex);

	bus_put(subsys);
पूर्ण
EXPORT_SYMBOL_GPL(subsys_पूर्णांकerface_unरेजिस्टर);

अटल व्योम प्रणाली_root_device_release(काष्ठा device *dev)
अणु
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक subsys_रेजिस्टर(काष्ठा bus_type *subsys,
			   स्थिर काष्ठा attribute_group **groups,
			   काष्ठा kobject *parent_of_root)
अणु
	काष्ठा device *dev;
	पूर्णांक err;

	err = bus_रेजिस्टर(subsys);
	अगर (err < 0)
		वापस err;

	dev = kzalloc(माप(काष्ठा device), GFP_KERNEL);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_dev;
	पूर्ण

	err = dev_set_name(dev, "%s", subsys->name);
	अगर (err < 0)
		जाओ err_name;

	dev->kobj.parent = parent_of_root;
	dev->groups = groups;
	dev->release = प्रणाली_root_device_release;

	err = device_रेजिस्टर(dev);
	अगर (err < 0)
		जाओ err_dev_reg;

	subsys->dev_root = dev;
	वापस 0;

err_dev_reg:
	put_device(dev);
	dev = शून्य;
err_name:
	kमुक्त(dev);
err_dev:
	bus_unरेजिस्टर(subsys);
	वापस err;
पूर्ण

/**
 * subsys_प्रणाली_रेजिस्टर - रेजिस्टर a subप्रणाली at /sys/devices/प्रणाली/
 * @subsys: प्रणाली subप्रणाली
 * @groups: शेष attributes क्रम the root device
 *
 * All 'system' subप्रणालीs have a /sys/devices/प्रणाली/<name> root device
 * with the name of the subप्रणाली. The root device can carry subप्रणाली-
 * wide attributes. All रेजिस्टरed devices are below this single root
 * device and are named after the subप्रणाली with a simple क्रमागतeration
 * number appended. The रेजिस्टरed devices are not explicitly named;
 * only 'id' in the device needs to be set.
 *
 * Do not use this पूर्णांकerface क्रम anything new, it exists क्रम compatibility
 * with bad ideas only. New subप्रणालीs should use plain subप्रणालीs; and
 * add the subप्रणाली-wide attributes should be added to the subप्रणाली
 * directory itself and not some create fake root-device placed in
 * /sys/devices/प्रणाली/<name>.
 */
पूर्णांक subsys_प्रणाली_रेजिस्टर(काष्ठा bus_type *subsys,
			   स्थिर काष्ठा attribute_group **groups)
अणु
	वापस subsys_रेजिस्टर(subsys, groups, &प्रणाली_kset->kobj);
पूर्ण
EXPORT_SYMBOL_GPL(subsys_प्रणाली_रेजिस्टर);

/**
 * subsys_भव_रेजिस्टर - रेजिस्टर a subप्रणाली at /sys/devices/भव/
 * @subsys: भव subप्रणाली
 * @groups: शेष attributes क्रम the root device
 *
 * All 'virtual' subप्रणालीs have a /sys/devices/प्रणाली/<name> root device
 * with the name of the subystem.  The root device can carry subप्रणाली-wide
 * attributes.  All रेजिस्टरed devices are below this single root device.
 * There's no restriction on device naming.  This is क्रम kernel software
 * स्थिरructs which need sysfs पूर्णांकerface.
 */
पूर्णांक subsys_भव_रेजिस्टर(काष्ठा bus_type *subsys,
			    स्थिर काष्ठा attribute_group **groups)
अणु
	काष्ठा kobject *भव_dir;

	भव_dir = भव_device_parent(शून्य);
	अगर (!भव_dir)
		वापस -ENOMEM;

	वापस subsys_रेजिस्टर(subsys, groups, भव_dir);
पूर्ण
EXPORT_SYMBOL_GPL(subsys_भव_रेजिस्टर);

पूर्णांक __init buses_init(व्योम)
अणु
	bus_kset = kset_create_and_add("bus", &bus_uevent_ops, शून्य);
	अगर (!bus_kset)
		वापस -ENOMEM;

	प्रणाली_kset = kset_create_and_add("system", शून्य, &devices_kset->kobj);
	अगर (!प्रणाली_kset)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
