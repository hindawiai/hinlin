<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * coreboot_table.c
 *
 * Module providing coreboot table access.
 *
 * Copyright 2017 Google Inc.
 * Copyright 2017 Samuel Holland <samuel@sholland.org>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "coreboot_table.h"

#घोषणा CB_DEV(d) container_of(d, काष्ठा coreboot_device, dev)
#घोषणा CB_DRV(d) container_of(d, काष्ठा coreboot_driver, drv)

अटल पूर्णांक coreboot_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा coreboot_device *device = CB_DEV(dev);
	काष्ठा coreboot_driver *driver = CB_DRV(drv);

	वापस device->entry.tag == driver->tag;
पूर्ण

अटल पूर्णांक coreboot_bus_probe(काष्ठा device *dev)
अणु
	पूर्णांक ret = -ENODEV;
	काष्ठा coreboot_device *device = CB_DEV(dev);
	काष्ठा coreboot_driver *driver = CB_DRV(dev->driver);

	अगर (driver->probe)
		ret = driver->probe(device);

	वापस ret;
पूर्ण

अटल पूर्णांक coreboot_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा coreboot_device *device = CB_DEV(dev);
	काष्ठा coreboot_driver *driver = CB_DRV(dev->driver);

	अगर (driver->हटाओ)
		driver->हटाओ(device);

	वापस 0;
पूर्ण

अटल काष्ठा bus_type coreboot_bus_type = अणु
	.name		= "coreboot",
	.match		= coreboot_bus_match,
	.probe		= coreboot_bus_probe,
	.हटाओ		= coreboot_bus_हटाओ,
पूर्ण;

अटल व्योम coreboot_device_release(काष्ठा device *dev)
अणु
	काष्ठा coreboot_device *device = CB_DEV(dev);

	kमुक्त(device);
पूर्ण

पूर्णांक coreboot_driver_रेजिस्टर(काष्ठा coreboot_driver *driver)
अणु
	driver->drv.bus = &coreboot_bus_type;

	वापस driver_रेजिस्टर(&driver->drv);
पूर्ण
EXPORT_SYMBOL(coreboot_driver_रेजिस्टर);

व्योम coreboot_driver_unरेजिस्टर(काष्ठा coreboot_driver *driver)
अणु
	driver_unरेजिस्टर(&driver->drv);
पूर्ण
EXPORT_SYMBOL(coreboot_driver_unरेजिस्टर);

अटल पूर्णांक coreboot_table_populate(काष्ठा device *dev, व्योम *ptr)
अणु
	पूर्णांक i, ret;
	व्योम *ptr_entry;
	काष्ठा coreboot_device *device;
	काष्ठा coreboot_table_entry *entry;
	काष्ठा coreboot_table_header *header = ptr;

	ptr_entry = ptr + header->header_bytes;
	क्रम (i = 0; i < header->table_entries; i++) अणु
		entry = ptr_entry;

		device = kzalloc(माप(काष्ठा device) + entry->size, GFP_KERNEL);
		अगर (!device)
			वापस -ENOMEM;

		dev_set_name(&device->dev, "coreboot%d", i);
		device->dev.parent = dev;
		device->dev.bus = &coreboot_bus_type;
		device->dev.release = coreboot_device_release;
		स_नकल(&device->entry, ptr_entry, entry->size);

		ret = device_रेजिस्टर(&device->dev);
		अगर (ret) अणु
			put_device(&device->dev);
			वापस ret;
		पूर्ण

		ptr_entry += entry->size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक coreboot_table_probe(काष्ठा platक्रमm_device *pdev)
अणु
	resource_माप_प्रकार len;
	काष्ठा coreboot_table_header *header;
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	व्योम *ptr;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EINVAL;

	len = resource_size(res);
	अगर (!res->start || !len)
		वापस -EINVAL;

	/* Check just the header first to make sure things are sane */
	header = memremap(res->start, माप(*header), MEMREMAP_WB);
	अगर (!header)
		वापस -ENOMEM;

	len = header->header_bytes + header->table_bytes;
	ret = म_भेदन(header->signature, "LBIO", माप(header->signature));
	memunmap(header);
	अगर (ret) अणु
		dev_warn(dev, "coreboot table missing or corrupt!\n");
		वापस -ENODEV;
	पूर्ण

	ptr = memremap(res->start, len, MEMREMAP_WB);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = bus_रेजिस्टर(&coreboot_bus_type);
	अगर (!ret) अणु
		ret = coreboot_table_populate(dev, ptr);
		अगर (ret)
			bus_unरेजिस्टर(&coreboot_bus_type);
	पूर्ण
	memunmap(ptr);

	वापस ret;
पूर्ण

अटल पूर्णांक __cb_dev_unरेजिस्टर(काष्ठा device *dev, व्योम *dummy)
अणु
	device_unरेजिस्टर(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक coreboot_table_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	bus_क्रम_each_dev(&coreboot_bus_type, शून्य, शून्य, __cb_dev_unरेजिस्टर);
	bus_unरेजिस्टर(&coreboot_bus_type);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id cros_coreboot_acpi_match[] = अणु
	अणु "GOOGCB00", 0 पूर्ण,
	अणु "BOOT0000", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, cros_coreboot_acpi_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id coreboot_of_match[] = अणु
	अणु .compatible = "coreboot" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, coreboot_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver coreboot_table_driver = अणु
	.probe = coreboot_table_probe,
	.हटाओ = coreboot_table_हटाओ,
	.driver = अणु
		.name = "coreboot_table",
		.acpi_match_table = ACPI_PTR(cros_coreboot_acpi_match),
		.of_match_table = of_match_ptr(coreboot_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(coreboot_table_driver);
MODULE_AUTHOR("Google, Inc.");
MODULE_LICENSE("GPL");
