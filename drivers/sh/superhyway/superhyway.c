<शैली गुरु>
/*
 * drivers/sh/superhyway/superhyway.c
 *
 * SuperHyway Bus Driver
 *
 * Copyright (C) 2004, 2005  Paul Mundt <lethal@linux-sh.org>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/superhyway.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

अटल पूर्णांक superhyway_devices;

अटल काष्ठा device superhyway_bus_device = अणु
	.init_name = "superhyway",
पूर्ण;

अटल व्योम superhyway_device_release(काष्ठा device *dev)
अणु
	काष्ठा superhyway_device *sdev = to_superhyway_device(dev);

	kमुक्त(sdev->resource);
	kमुक्त(sdev);
पूर्ण

/**
 * superhyway_add_device - Add a SuperHyway module
 * @base: Physical address where module is mapped.
 * @sdev: SuperHyway device to add, or शून्य to allocate a new one.
 * @bus: Bus where SuperHyway module resides.
 *
 * This is responsible क्रम adding a new SuperHyway module. This sets up a new
 * काष्ठा superhyway_device क्रम the module being added अगर @sdev == शून्य.
 *
 * Devices are initially added in the order that they are scanned (from the
 * top-करोwn of the memory map), and are asचिन्हित an ID based on the order that
 * they are added. Any manual addition of a module will thus get the ID after
 * the devices alपढ़ोy discovered regardless of where it resides in memory.
 *
 * Further work can and should be करोne in superhyway_scan_bus(), to be sure
 * that any new modules are properly discovered and subsequently रेजिस्टरed.
 */
पूर्णांक superhyway_add_device(अचिन्हित दीर्घ base, काष्ठा superhyway_device *sdev,
			  काष्ठा superhyway_bus *bus)
अणु
	काष्ठा superhyway_device *dev = sdev;

	अगर (!dev) अणु
		dev = kzalloc(माप(काष्ठा superhyway_device), GFP_KERNEL);
		अगर (!dev)
			वापस -ENOMEM;

	पूर्ण

	dev->bus = bus;
	superhyway_पढ़ो_vcr(dev, base, &dev->vcr);

	अगर (!dev->resource) अणु
		dev->resource = kzalloc(माप(काष्ठा resource), GFP_KERNEL);
		अगर (!dev->resource) अणु
			kमुक्त(dev);
			वापस -ENOMEM;
		पूर्ण

		dev->resource->name	= dev->name;
		dev->resource->start	= base;
		dev->resource->end	= dev->resource->start + 0x01000000;
	पूर्ण

	dev->dev.parent		= &superhyway_bus_device;
	dev->dev.bus		= &superhyway_bus_type;
	dev->dev.release	= superhyway_device_release;
	dev->id.id		= dev->vcr.mod_id;

	प्र_लिखो(dev->name, "SuperHyway device %04x", dev->id.id);
	dev_set_name(&dev->dev, "%02x", superhyway_devices);

	superhyway_devices++;

	वापस device_रेजिस्टर(&dev->dev);
पूर्ण

पूर्णांक superhyway_add_devices(काष्ठा superhyway_bus *bus,
			   काष्ठा superhyway_device **devices,
			   पूर्णांक nr_devices)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < nr_devices; i++) अणु
		काष्ठा superhyway_device *dev = devices[i];
		ret |= superhyway_add_device(dev->resource[0].start, dev, bus);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __init superhyway_init(व्योम)
अणु
	काष्ठा superhyway_bus *bus;
	पूर्णांक ret;

	ret = device_रेजिस्टर(&superhyway_bus_device);
	अगर (unlikely(ret))
		वापस ret;

	क्रम (bus = superhyway_channels; bus->ops; bus++)
		ret |= superhyway_scan_bus(bus);

	वापस ret;
पूर्ण
postcore_initcall(superhyway_init);

अटल स्थिर काष्ठा superhyway_device_id *
superhyway_match_id(स्थिर काष्ठा superhyway_device_id *ids,
		    काष्ठा superhyway_device *dev)
अणु
	जबतक (ids->id) अणु
		अगर (ids->id == dev->id.id)
			वापस ids;

		ids++;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक superhyway_device_probe(काष्ठा device *dev)
अणु
	काष्ठा superhyway_device *shyway_dev = to_superhyway_device(dev);
	काष्ठा superhyway_driver *shyway_drv = to_superhyway_driver(dev->driver);

	अगर (shyway_drv && shyway_drv->probe) अणु
		स्थिर काष्ठा superhyway_device_id *id;

		id = superhyway_match_id(shyway_drv->id_table, shyway_dev);
		अगर (id)
			वापस shyway_drv->probe(shyway_dev, id);
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक superhyway_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा superhyway_device *shyway_dev = to_superhyway_device(dev);
	काष्ठा superhyway_driver *shyway_drv = to_superhyway_driver(dev->driver);

	अगर (shyway_drv && shyway_drv->हटाओ) अणु
		shyway_drv->हटाओ(shyway_dev);
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

/**
 * superhyway_रेजिस्टर_driver - Register a new SuperHyway driver
 * @drv: SuperHyway driver to रेजिस्टर.
 *
 * This रेजिस्टरs the passed in @drv. Any devices matching the id table will
 * स्वतःmatically be populated and handed off to the driver's specअगरied probe
 * routine.
 */
पूर्णांक superhyway_रेजिस्टर_driver(काष्ठा superhyway_driver *drv)
अणु
	drv->drv.name	= drv->name;
	drv->drv.bus	= &superhyway_bus_type;

	वापस driver_रेजिस्टर(&drv->drv);
पूर्ण

/**
 * superhyway_unरेजिस्टर_driver - Unरेजिस्टर a SuperHyway driver
 * @drv: SuperHyway driver to unरेजिस्टर.
 *
 * This cleans up after superhyway_रेजिस्टर_driver(), and should be invoked in
 * the निकास path of any module drivers.
 */
व्योम superhyway_unरेजिस्टर_driver(काष्ठा superhyway_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->drv);
पूर्ण

अटल पूर्णांक superhyway_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा superhyway_device *shyway_dev = to_superhyway_device(dev);
	काष्ठा superhyway_driver *shyway_drv = to_superhyway_driver(drv);
	स्थिर काष्ठा superhyway_device_id *ids = shyway_drv->id_table;

	अगर (!ids)
		वापस -EINVAL;
	अगर (superhyway_match_id(ids, shyway_dev))
		वापस 1;

	वापस -ENODEV;
पूर्ण

काष्ठा bus_type superhyway_bus_type = अणु
	.name		= "superhyway",
	.match		= superhyway_bus_match,
#अगर_घोषित CONFIG_SYSFS
	.dev_groups	= superhyway_dev_groups,
#पूर्ण_अगर
	.probe		= superhyway_device_probe,
	.हटाओ		= superhyway_device_हटाओ,
पूर्ण;

अटल पूर्णांक __init superhyway_bus_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&superhyway_bus_type);
पूर्ण

अटल व्योम __निकास superhyway_bus_निकास(व्योम)
अणु
	device_unरेजिस्टर(&superhyway_bus_device);
	bus_unरेजिस्टर(&superhyway_bus_type);
पूर्ण

core_initcall(superhyway_bus_init);
module_निकास(superhyway_bus_निकास);

EXPORT_SYMBOL(superhyway_bus_type);
EXPORT_SYMBOL(superhyway_add_device);
EXPORT_SYMBOL(superhyway_add_devices);
EXPORT_SYMBOL(superhyway_रेजिस्टर_driver);
EXPORT_SYMBOL(superhyway_unरेजिस्टर_driver);

MODULE_LICENSE("GPL");
