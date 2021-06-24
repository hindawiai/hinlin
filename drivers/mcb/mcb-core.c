<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MEN Chameleon Bus.
 *
 * Copyright (C) 2013 MEN Mikroelektronik GmbH (www.men.de)
 * Author: Johannes Thumshirn <johannes.thumshirn@men.de>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/idr.h>
#समावेश <linux/mcb.h>

अटल DEFINE_IDA(mcb_ida);

अटल स्थिर काष्ठा mcb_device_id *mcb_match_id(स्थिर काष्ठा mcb_device_id *ids,
						काष्ठा mcb_device *dev)
अणु
	अगर (ids) अणु
		जबतक (ids->device) अणु
			अगर (ids->device == dev->id)
				वापस ids;
			ids++;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक mcb_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा mcb_driver *mdrv = to_mcb_driver(drv);
	काष्ठा mcb_device *mdev = to_mcb_device(dev);
	स्थिर काष्ठा mcb_device_id *found_id;

	found_id = mcb_match_id(mdrv->id_table, mdev);
	अगर (found_id)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mcb_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा mcb_device *mdev = to_mcb_device(dev);
	पूर्णांक ret;

	ret = add_uevent_var(env, "MODALIAS=mcb:16z%03d", mdev->id);
	अगर (ret)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक mcb_probe(काष्ठा device *dev)
अणु
	काष्ठा mcb_driver *mdrv = to_mcb_driver(dev->driver);
	काष्ठा mcb_device *mdev = to_mcb_device(dev);
	स्थिर काष्ठा mcb_device_id *found_id;
	काष्ठा module *carrier_mod;
	पूर्णांक ret;

	found_id = mcb_match_id(mdrv->id_table, mdev);
	अगर (!found_id)
		वापस -ENODEV;

	carrier_mod = mdev->dev.parent->driver->owner;
	अगर (!try_module_get(carrier_mod))
		वापस -EINVAL;

	get_device(dev);
	ret = mdrv->probe(mdev, found_id);
	अगर (ret)
		module_put(carrier_mod);

	वापस ret;
पूर्ण

अटल पूर्णांक mcb_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा mcb_driver *mdrv = to_mcb_driver(dev->driver);
	काष्ठा mcb_device *mdev = to_mcb_device(dev);
	काष्ठा module *carrier_mod;

	mdrv->हटाओ(mdev);

	carrier_mod = mdev->dev.parent->driver->owner;
	module_put(carrier_mod);

	put_device(&mdev->dev);

	वापस 0;
पूर्ण

अटल व्योम mcb_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा mcb_driver *mdrv = to_mcb_driver(dev->driver);
	काष्ठा mcb_device *mdev = to_mcb_device(dev);

	अगर (mdrv && mdrv->shutकरोwn)
		mdrv->shutकरोwn(mdev);
पूर्ण

अटल sमाप_प्रकार revision_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा mcb_bus *bus = to_mcb_bus(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", bus->revision);
पूर्ण
अटल DEVICE_ATTR_RO(revision);

अटल sमाप_प्रकार model_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा mcb_bus *bus = to_mcb_bus(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%c\n", bus->model);
पूर्ण
अटल DEVICE_ATTR_RO(model);

अटल sमाप_प्रकार minor_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा mcb_bus *bus = to_mcb_bus(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", bus->minor);
पूर्ण
अटल DEVICE_ATTR_RO(minor);

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा mcb_bus *bus = to_mcb_bus(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", bus->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल काष्ठा attribute *mcb_bus_attrs[] = अणु
	&dev_attr_revision.attr,
	&dev_attr_model.attr,
	&dev_attr_minor.attr,
	&dev_attr_name.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mcb_carrier_group = अणु
	.attrs = mcb_bus_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *mcb_carrier_groups[] = अणु
	&mcb_carrier_group,
	शून्य,
पूर्ण;


अटल काष्ठा bus_type mcb_bus_type = अणु
	.name = "mcb",
	.match = mcb_match,
	.uevent = mcb_uevent,
	.probe = mcb_probe,
	.हटाओ = mcb_हटाओ,
	.shutकरोwn = mcb_shutकरोwn,
पूर्ण;

अटल काष्ठा device_type mcb_carrier_device_type = अणु
	.name = "mcb-carrier",
	.groups = mcb_carrier_groups,
पूर्ण;

/**
 * __mcb_रेजिस्टर_driver() - Register a @mcb_driver at the प्रणाली
 * @drv: The @mcb_driver
 * @owner: The @mcb_driver's module
 * @mod_name: The name of the @mcb_driver's module
 *
 * Register a @mcb_driver at the प्रणाली. Perक्रमm some sanity checks, अगर
 * the .probe and .हटाओ methods are provided by the driver.
 */
पूर्णांक __mcb_रेजिस्टर_driver(काष्ठा mcb_driver *drv, काष्ठा module *owner,
			स्थिर अक्षर *mod_name)
अणु
	अगर (!drv->probe || !drv->हटाओ)
		वापस -EINVAL;

	drv->driver.owner = owner;
	drv->driver.bus = &mcb_bus_type;
	drv->driver.mod_name = mod_name;

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_NS_GPL(__mcb_रेजिस्टर_driver, MCB);

/**
 * mcb_unरेजिस्टर_driver() - Unरेजिस्टर a @mcb_driver from the प्रणाली
 * @drv: The @mcb_driver
 *
 * Unरेजिस्टर a @mcb_driver from the प्रणाली.
 */
व्योम mcb_unरेजिस्टर_driver(काष्ठा mcb_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_NS_GPL(mcb_unरेजिस्टर_driver, MCB);

अटल व्योम mcb_release_dev(काष्ठा device *dev)
अणु
	काष्ठा mcb_device *mdev = to_mcb_device(dev);

	mcb_bus_put(mdev->bus);
	kमुक्त(mdev);
पूर्ण

/**
 * mcb_device_रेजिस्टर() - Register a mcb_device
 * @bus: The @mcb_bus of the device
 * @dev: The @mcb_device
 *
 * Register a specअगरic @mcb_device at a @mcb_bus and the प्रणाली itself.
 */
पूर्णांक mcb_device_रेजिस्टर(काष्ठा mcb_bus *bus, काष्ठा mcb_device *dev)
अणु
	पूर्णांक ret;
	पूर्णांक device_id;

	device_initialize(&dev->dev);
	mcb_bus_get(bus);
	dev->dev.bus = &mcb_bus_type;
	dev->dev.parent = bus->dev.parent;
	dev->dev.release = mcb_release_dev;
	dev->dma_dev = bus->carrier;

	device_id = dev->id;
	dev_set_name(&dev->dev, "mcb%d-16z%03d-%d:%d:%d",
		bus->bus_nr, device_id, dev->inst, dev->group, dev->var);

	ret = device_add(&dev->dev);
	अगर (ret < 0) अणु
		pr_err("Failed registering device 16z%03d on bus mcb%d (%d)\n",
			device_id, bus->bus_nr, ret);
		जाओ out;
	पूर्ण

	वापस 0;

out:

	वापस ret;
पूर्ण
EXPORT_SYMBOL_NS_GPL(mcb_device_रेजिस्टर, MCB);

अटल व्योम mcb_मुक्त_bus(काष्ठा device *dev)
अणु
	काष्ठा mcb_bus *bus = to_mcb_bus(dev);

	put_device(bus->carrier);
	ida_simple_हटाओ(&mcb_ida, bus->bus_nr);
	kमुक्त(bus);
पूर्ण

/**
 * mcb_alloc_bus() - Allocate a new @mcb_bus
 *
 * Allocate a new @mcb_bus.
 */
काष्ठा mcb_bus *mcb_alloc_bus(काष्ठा device *carrier)
अणु
	काष्ठा mcb_bus *bus;
	पूर्णांक bus_nr;
	पूर्णांक rc;

	bus = kzalloc(माप(काष्ठा mcb_bus), GFP_KERNEL);
	अगर (!bus)
		वापस ERR_PTR(-ENOMEM);

	bus_nr = ida_simple_get(&mcb_ida, 0, 0, GFP_KERNEL);
	अगर (bus_nr < 0) अणु
		rc = bus_nr;
		जाओ err_मुक्त;
	पूर्ण

	bus->bus_nr = bus_nr;
	bus->carrier = get_device(carrier);

	device_initialize(&bus->dev);
	bus->dev.parent = carrier;
	bus->dev.bus = &mcb_bus_type;
	bus->dev.type = &mcb_carrier_device_type;
	bus->dev.release = &mcb_मुक्त_bus;

	dev_set_name(&bus->dev, "mcb:%d", bus_nr);
	rc = device_add(&bus->dev);
	अगर (rc)
		जाओ err_मुक्त;

	वापस bus;
err_मुक्त:
	put_device(carrier);
	kमुक्त(bus);
	वापस ERR_PTR(rc);
पूर्ण
EXPORT_SYMBOL_NS_GPL(mcb_alloc_bus, MCB);

अटल पूर्णांक __mcb_devices_unरेजिस्टर(काष्ठा device *dev, व्योम *data)
अणु
	device_unरेजिस्टर(dev);
	वापस 0;
पूर्ण

अटल व्योम mcb_devices_unरेजिस्टर(काष्ठा mcb_bus *bus)
अणु
	bus_क्रम_each_dev(&mcb_bus_type, शून्य, शून्य, __mcb_devices_unरेजिस्टर);
पूर्ण
/**
 * mcb_release_bus() - Free a @mcb_bus
 * @bus: The @mcb_bus to release
 *
 * Release an allocated @mcb_bus from the प्रणाली.
 */
व्योम mcb_release_bus(काष्ठा mcb_bus *bus)
अणु
	mcb_devices_unरेजिस्टर(bus);
पूर्ण
EXPORT_SYMBOL_NS_GPL(mcb_release_bus, MCB);

/**
 * mcb_bus_put() - Increment refcnt
 * @bus: The @mcb_bus
 *
 * Get a @mcb_bus' ref
 */
काष्ठा mcb_bus *mcb_bus_get(काष्ठा mcb_bus *bus)
अणु
	अगर (bus)
		get_device(&bus->dev);

	वापस bus;
पूर्ण
EXPORT_SYMBOL_NS_GPL(mcb_bus_get, MCB);

/**
 * mcb_bus_put() - Decrement refcnt
 * @bus: The @mcb_bus
 *
 * Release a @mcb_bus' ref
 */
व्योम mcb_bus_put(काष्ठा mcb_bus *bus)
अणु
	अगर (bus)
		put_device(&bus->dev);
पूर्ण
EXPORT_SYMBOL_NS_GPL(mcb_bus_put, MCB);

/**
 * mcb_alloc_dev() - Allocate a device
 * @bus: The @mcb_bus the device is part of
 *
 * Allocate a @mcb_device and add bus.
 */
काष्ठा mcb_device *mcb_alloc_dev(काष्ठा mcb_bus *bus)
अणु
	काष्ठा mcb_device *dev;

	dev = kzalloc(माप(काष्ठा mcb_device), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	dev->bus = bus;

	वापस dev;
पूर्ण
EXPORT_SYMBOL_NS_GPL(mcb_alloc_dev, MCB);

/**
 * mcb_मुक्त_dev() - Free @mcb_device
 * @dev: The device to मुक्त
 *
 * Free a @mcb_device
 */
व्योम mcb_मुक्त_dev(काष्ठा mcb_device *dev)
अणु
	kमुक्त(dev);
पूर्ण
EXPORT_SYMBOL_NS_GPL(mcb_मुक्त_dev, MCB);

अटल पूर्णांक __mcb_bus_add_devices(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा mcb_device *mdev = to_mcb_device(dev);
	पूर्णांक retval;

	अगर (mdev->is_added)
		वापस 0;

	retval = device_attach(dev);
	अगर (retval < 0)
		dev_err(dev, "Error adding device (%d)\n", retval);

	mdev->is_added = true;

	वापस 0;
पूर्ण

/**
 * mcb_bus_add_devices() - Add devices in the bus' पूर्णांकernal device list
 * @bus: The @mcb_bus we add the devices
 *
 * Add devices in the bus' पूर्णांकernal device list to the प्रणाली.
 */
व्योम mcb_bus_add_devices(स्थिर काष्ठा mcb_bus *bus)
अणु
	bus_क्रम_each_dev(&mcb_bus_type, शून्य, शून्य, __mcb_bus_add_devices);
पूर्ण
EXPORT_SYMBOL_NS_GPL(mcb_bus_add_devices, MCB);

/**
 * mcb_get_resource() - get a resource क्रम a mcb device
 * @dev: the mcb device
 * @type: the type of resource
 */
काष्ठा resource *mcb_get_resource(काष्ठा mcb_device *dev, अचिन्हित पूर्णांक type)
अणु
	अगर (type == IORESOURCE_MEM)
		वापस &dev->mem;
	अन्यथा अगर (type == IORESOURCE_IRQ)
		वापस &dev->irq;
	अन्यथा
		वापस शून्य;
पूर्ण
EXPORT_SYMBOL_NS_GPL(mcb_get_resource, MCB);

/**
 * mcb_request_mem() - Request memory
 * @dev: The @mcb_device the memory is क्रम
 * @name: The name क्रम the memory reference.
 *
 * Request memory क्रम a @mcb_device. If @name is शून्य the driver name will
 * be used.
 */
काष्ठा resource *mcb_request_mem(काष्ठा mcb_device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा resource *mem;
	u32 size;

	अगर (!name)
		name = dev->dev.driver->name;

	size = resource_size(&dev->mem);

	mem = request_mem_region(dev->mem.start, size, name);
	अगर (!mem)
		वापस ERR_PTR(-EBUSY);

	वापस mem;
पूर्ण
EXPORT_SYMBOL_NS_GPL(mcb_request_mem, MCB);

/**
 * mcb_release_mem() - Release memory requested by device
 * @dev: The @mcb_device that requested the memory
 *
 * Release memory that was prior requested via @mcb_request_mem().
 */
व्योम mcb_release_mem(काष्ठा resource *mem)
अणु
	u32 size;

	size = resource_size(mem);
	release_mem_region(mem->start, size);
पूर्ण
EXPORT_SYMBOL_NS_GPL(mcb_release_mem, MCB);

अटल पूर्णांक __mcb_get_irq(काष्ठा mcb_device *dev)
अणु
	काष्ठा resource *irq;

	irq = mcb_get_resource(dev, IORESOURCE_IRQ);

	वापस irq->start;
पूर्ण

/**
 * mcb_get_irq() - Get device's IRQ number
 * @dev: The @mcb_device the IRQ is क्रम
 *
 * Get the IRQ number of a given @mcb_device.
 */
पूर्णांक mcb_get_irq(काष्ठा mcb_device *dev)
अणु
	काष्ठा mcb_bus *bus = dev->bus;

	अगर (bus->get_irq)
		वापस bus->get_irq(dev);

	वापस __mcb_get_irq(dev);
पूर्ण
EXPORT_SYMBOL_NS_GPL(mcb_get_irq, MCB);

अटल पूर्णांक mcb_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&mcb_bus_type);
पूर्ण

अटल व्योम mcb_निकास(व्योम)
अणु
	ida_destroy(&mcb_ida);
	bus_unरेजिस्टर(&mcb_bus_type);
पूर्ण

/* mcb must be initialized after PCI but beक्रमe the chameleon drivers.
 * That means we must use some initcall between subsys_initcall and
 * device_initcall.
 */
fs_initcall(mcb_init);
module_निकास(mcb_निकास);

MODULE_DESCRIPTION("MEN Chameleon Bus Driver");
MODULE_AUTHOR("Johannes Thumshirn <johannes.thumshirn@men.de>");
MODULE_LICENSE("GPL v2");
