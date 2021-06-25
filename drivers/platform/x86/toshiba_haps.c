<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Toshiba HDD Active Protection Sensor (HAPS) driver
 *
 * Copyright (C) 2014 Azael Avalos <coproscefalo@gmail.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/acpi.h>

MODULE_AUTHOR("Azael Avalos <coproscefalo@gmail.com>");
MODULE_DESCRIPTION("Toshiba HDD Active Protection Sensor");
MODULE_LICENSE("GPL");

काष्ठा toshiba_haps_dev अणु
	काष्ठा acpi_device *acpi_dev;

	पूर्णांक protection_level;
पूर्ण;

अटल काष्ठा toshiba_haps_dev *toshiba_haps;

/* HAPS functions */
अटल पूर्णांक toshiba_haps_reset_protection(acpi_handle handle)
अणु
	acpi_status status;

	status = acpi_evaluate_object(handle, "RSSS", शून्य, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Unable to reset the HDD protection\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक toshiba_haps_protection_level(acpi_handle handle, पूर्णांक level)
अणु
	acpi_status status;

	status = acpi_execute_simple_method(handle, "PTLV", level);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Error while setting the protection level\n");
		वापस -EIO;
	पूर्ण

	pr_debug("HDD protection level set to: %d\n", level);

	वापस 0;
पूर्ण

/* sysfs files */
अटल sमाप_प्रकार protection_level_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा toshiba_haps_dev *haps = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%i\n", haps->protection_level);
पूर्ण

अटल sमाप_प्रकार protection_level_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा toshiba_haps_dev *haps = dev_get_drvdata(dev);
	पूर्णांक level;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &level);
	अगर (ret)
		वापस ret;
	/*
	 * Check क्रम supported levels, which can be:
	 * 0 - Disabled | 1 - Low | 2 - Medium | 3 - High
	 */
	अगर (level < 0 || level > 3)
		वापस -EINVAL;

	/* Set the sensor level */
	ret = toshiba_haps_protection_level(haps->acpi_dev->handle, level);
	अगर (ret != 0)
		वापस ret;

	haps->protection_level = level;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(protection_level);

अटल sमाप_प्रकार reset_protection_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा toshiba_haps_dev *haps = dev_get_drvdata(dev);
	पूर्णांक reset;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &reset);
	अगर (ret)
		वापस ret;
	/* The only accepted value is 1 */
	अगर (reset != 1)
		वापस -EINVAL;

	/* Reset the protection पूर्णांकerface */
	ret = toshiba_haps_reset_protection(haps->acpi_dev->handle);
	अगर (ret != 0)
		वापस ret;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(reset_protection);

अटल काष्ठा attribute *haps_attributes[] = अणु
	&dev_attr_protection_level.attr,
	&dev_attr_reset_protection.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group haps_attr_group = अणु
	.attrs = haps_attributes,
पूर्ण;

/*
 * ACPI stuff
 */
अटल व्योम toshiba_haps_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	pr_debug("Received event: 0x%x", event);

	acpi_bus_generate_netlink_event(device->pnp.device_class,
					dev_name(&device->dev),
					event, 0);
पूर्ण

अटल पूर्णांक toshiba_haps_हटाओ(काष्ठा acpi_device *device)
अणु
	sysfs_हटाओ_group(&device->dev.kobj, &haps_attr_group);

	अगर (toshiba_haps)
		toshiba_haps = शून्य;

	वापस 0;
पूर्ण

/* Helper function */
अटल पूर्णांक toshiba_haps_available(acpi_handle handle)
अणु
	acpi_status status;
	u64 hdd_present;

	/*
	 * A non existent device as well as having (only)
	 * Solid State Drives can cause the call to fail.
	 */
	status = acpi_evaluate_पूर्णांकeger(handle, "_STA", शून्य, &hdd_present);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to query HDD protection failed\n");
		वापस 0;
	पूर्ण

	अगर (!hdd_present) अणु
		pr_info("HDD protection not available or using SSD\n");
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक toshiba_haps_add(काष्ठा acpi_device *acpi_dev)
अणु
	काष्ठा toshiba_haps_dev *haps;
	पूर्णांक ret;

	अगर (toshiba_haps)
		वापस -EBUSY;

	अगर (!toshiba_haps_available(acpi_dev->handle))
		वापस -ENODEV;

	pr_info("Toshiba HDD Active Protection Sensor device\n");

	haps = kzalloc(माप(काष्ठा toshiba_haps_dev), GFP_KERNEL);
	अगर (!haps)
		वापस -ENOMEM;

	haps->acpi_dev = acpi_dev;
	haps->protection_level = 2;
	acpi_dev->driver_data = haps;
	dev_set_drvdata(&acpi_dev->dev, haps);

	/* Set the protection level, currently at level 2 (Medium) */
	ret = toshiba_haps_protection_level(acpi_dev->handle, 2);
	अगर (ret != 0)
		वापस ret;

	ret = sysfs_create_group(&acpi_dev->dev.kobj, &haps_attr_group);
	अगर (ret)
		वापस ret;

	toshiba_haps = haps;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक toshiba_haps_suspend(काष्ठा device *device)
अणु
	काष्ठा toshiba_haps_dev *haps;
	पूर्णांक ret;

	haps = acpi_driver_data(to_acpi_device(device));

	/* Deactivate the protection on suspend */
	ret = toshiba_haps_protection_level(haps->acpi_dev->handle, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक toshiba_haps_resume(काष्ठा device *device)
अणु
	काष्ठा toshiba_haps_dev *haps;
	पूर्णांक ret;

	haps = acpi_driver_data(to_acpi_device(device));

	/* Set the stored protection level */
	ret = toshiba_haps_protection_level(haps->acpi_dev->handle,
					    haps->protection_level);

	/* Reset the protection on resume */
	ret = toshiba_haps_reset_protection(haps->acpi_dev->handle);
	अगर (ret != 0)
		वापस ret;

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(toshiba_haps_pm,
			 toshiba_haps_suspend, toshiba_haps_resume);

अटल स्थिर काष्ठा acpi_device_id haps_device_ids[] = अणु
	अणु"TOS620A", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, haps_device_ids);

अटल काष्ठा acpi_driver toshiba_haps_driver = अणु
	.name = "Toshiba HAPS",
	.owner = THIS_MODULE,
	.ids = haps_device_ids,
	.flags = ACPI_DRIVER_ALL_NOTIFY_EVENTS,
	.ops = अणु
		.add =		toshiba_haps_add,
		.हटाओ =	toshiba_haps_हटाओ,
		.notअगरy =	toshiba_haps_notअगरy,
	पूर्ण,
	.drv.pm = &toshiba_haps_pm,
पूर्ण;

module_acpi_driver(toshiba_haps_driver);
