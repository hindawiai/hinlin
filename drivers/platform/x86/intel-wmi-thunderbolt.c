<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * WMI Thunderbolt driver
 *
 * Copyright (C) 2017 Dell Inc. All Rights Reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>
#समावेश <linux/wmi.h>

#घोषणा INTEL_WMI_THUNDERBOLT_GUID "86CCFD48-205E-4A77-9C48-2021CBEDE341"

अटल sमाप_प्रकार क्रमce_घातer_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_buffer input;
	acpi_status status;
	u8 mode;

	input.length = माप(u8);
	input.poपूर्णांकer = &mode;
	mode = hex_to_bin(buf[0]);
	dev_dbg(dev, "force_power: storing %#x\n", mode);
	अगर (mode == 0 || mode == 1) अणु
		status = wmi_evaluate_method(INTEL_WMI_THUNDERBOLT_GUID, 0, 1,
					     &input, शून्य);
		अगर (ACPI_FAILURE(status)) अणु
			dev_dbg(dev, "force_power: failed to evaluate ACPI method\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "force_power: unsupported mode\n");
		वापस -EINVAL;
	पूर्ण
	वापस count;
पूर्ण

अटल DEVICE_ATTR_WO(क्रमce_घातer);

अटल काष्ठा attribute *tbt_attrs[] = अणु
	&dev_attr_क्रमce_घातer.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group tbt_attribute_group = अणु
	.attrs = tbt_attrs,
पूर्ण;

अटल पूर्णांक पूर्णांकel_wmi_thunderbolt_probe(काष्ठा wmi_device *wdev,
				       स्थिर व्योम *context)
अणु
	पूर्णांक ret;

	ret = sysfs_create_group(&wdev->dev.kobj, &tbt_attribute_group);
	kobject_uevent(&wdev->dev.kobj, KOBJ_CHANGE);
	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_wmi_thunderbolt_हटाओ(काष्ठा wmi_device *wdev)
अणु
	sysfs_हटाओ_group(&wdev->dev.kobj, &tbt_attribute_group);
	kobject_uevent(&wdev->dev.kobj, KOBJ_CHANGE);
पूर्ण

अटल स्थिर काष्ठा wmi_device_id पूर्णांकel_wmi_thunderbolt_id_table[] = अणु
	अणु .guid_string = INTEL_WMI_THUNDERBOLT_GUID पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा wmi_driver पूर्णांकel_wmi_thunderbolt_driver = अणु
	.driver = अणु
		.name = "intel-wmi-thunderbolt",
	पूर्ण,
	.probe = पूर्णांकel_wmi_thunderbolt_probe,
	.हटाओ = पूर्णांकel_wmi_thunderbolt_हटाओ,
	.id_table = पूर्णांकel_wmi_thunderbolt_id_table,
पूर्ण;

module_wmi_driver(पूर्णांकel_wmi_thunderbolt_driver);

MODULE_DEVICE_TABLE(wmi, पूर्णांकel_wmi_thunderbolt_id_table);
MODULE_AUTHOR("Mario Limonciello <mario.limonciello@dell.com>");
MODULE_DESCRIPTION("Intel WMI Thunderbolt force power driver");
MODULE_LICENSE("GPL v2");
