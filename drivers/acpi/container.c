<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * container.c  - ACPI Generic Container Driver
 *
 * Copyright (C) 2004 Anil S Keshavamurthy (anil.s.keshavamurthy@पूर्णांकel.com)
 * Copyright (C) 2004 Keiichiro Tokunaga (tokunaga.keiich@jp.fujitsu.com)
 * Copyright (C) 2004 Motoyuki Ito (motoyuki@soft.fujitsu.com)
 * Copyright (C) 2004 FUJITSU LIMITED
 * Copyright (C) 2004, 2013 Intel Corp.
 * Author: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */
#समावेश <linux/acpi.h>
#समावेश <linux/container.h>

#समावेश "internal.h"

अटल स्थिर काष्ठा acpi_device_id container_device_ids[] = अणु
	अणु"ACPI0004", 0पूर्ण,
	अणु"PNP0A05", 0पूर्ण,
	अणु"PNP0A06", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_ACPI_CONTAINER

अटल पूर्णांक acpi_container_offline(काष्ठा container_dev *cdev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&cdev->dev);
	काष्ठा acpi_device *child;

	/* Check all of the dependent devices' physical companions. */
	list_क्रम_each_entry(child, &adev->children, node)
		अगर (!acpi_scan_is_offline(child, false))
			वापस -EBUSY;

	वापस 0;
पूर्ण

अटल व्योम acpi_container_release(काष्ठा device *dev)
अणु
	kमुक्त(to_container_dev(dev));
पूर्ण

अटल पूर्णांक container_device_attach(काष्ठा acpi_device *adev,
				   स्थिर काष्ठा acpi_device_id *not_used)
अणु
	काष्ठा container_dev *cdev;
	काष्ठा device *dev;
	पूर्णांक ret;

	अगर (adev->flags.is_करोck_station)
		वापस 0;

	cdev = kzalloc(माप(*cdev), GFP_KERNEL);
	अगर (!cdev)
		वापस -ENOMEM;

	cdev->offline = acpi_container_offline;
	dev = &cdev->dev;
	dev->bus = &container_subsys;
	dev_set_name(dev, "%s", dev_name(&adev->dev));
	ACPI_COMPANION_SET(dev, adev);
	dev->release = acpi_container_release;
	ret = device_रेजिस्टर(dev);
	अगर (ret) अणु
		put_device(dev);
		वापस ret;
	पूर्ण
	adev->driver_data = dev;
	वापस 1;
पूर्ण

अटल व्योम container_device_detach(काष्ठा acpi_device *adev)
अणु
	काष्ठा device *dev = acpi_driver_data(adev);

	adev->driver_data = शून्य;
	अगर (dev)
		device_unरेजिस्टर(dev);
पूर्ण

अटल व्योम container_device_online(काष्ठा acpi_device *adev)
अणु
	काष्ठा device *dev = acpi_driver_data(adev);

	kobject_uevent(&dev->kobj, KOBJ_ONLINE);
पूर्ण

अटल काष्ठा acpi_scan_handler container_handler = अणु
	.ids = container_device_ids,
	.attach = container_device_attach,
	.detach = container_device_detach,
	.hotplug = अणु
		.enabled = true,
		.demand_offline = true,
		.notअगरy_online = container_device_online,
	पूर्ण,
पूर्ण;

व्योम __init acpi_container_init(व्योम)
अणु
	acpi_scan_add_handler(&container_handler);
पूर्ण

#अन्यथा

अटल काष्ठा acpi_scan_handler container_handler = अणु
	.ids = container_device_ids,
पूर्ण;

व्योम __init acpi_container_init(व्योम)
अणु
	acpi_scan_add_handler_with_hotplug(&container_handler, "container");
पूर्ण

#पूर्ण_अगर /* CONFIG_ACPI_CONTAINER */
