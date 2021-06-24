<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Acer Wireless Radio Control Driver
 *
 * Copyright (C) 2017 Endless Mobile, Inc.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/types.h>

अटल स्थिर काष्ठा acpi_device_id acer_wireless_acpi_ids[] = अणु
	अणु"10251229", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, acer_wireless_acpi_ids);

अटल व्योम acer_wireless_notअगरy(काष्ठा acpi_device *adev, u32 event)
अणु
	काष्ठा input_dev *idev = acpi_driver_data(adev);

	dev_dbg(&adev->dev, "event=%#x\n", event);
	अगर (event != 0x80) अणु
		dev_notice(&adev->dev, "Unknown SMKB event: %#x\n", event);
		वापस;
	पूर्ण
	input_report_key(idev, KEY_RFKILL, 1);
	input_sync(idev);
	input_report_key(idev, KEY_RFKILL, 0);
	input_sync(idev);
पूर्ण

अटल पूर्णांक acer_wireless_add(काष्ठा acpi_device *adev)
अणु
	काष्ठा input_dev *idev;

	idev = devm_input_allocate_device(&adev->dev);
	अगर (!idev)
		वापस -ENOMEM;

	adev->driver_data = idev;
	idev->name = "Acer Wireless Radio Control";
	idev->phys = "acer-wireless/input0";
	idev->id.bustype = BUS_HOST;
	idev->id.venकरोr = PCI_VENDOR_ID_AI;
	idev->id.product = 0x1229;
	set_bit(EV_KEY, idev->evbit);
	set_bit(KEY_RFKILL, idev->keybit);

	वापस input_रेजिस्टर_device(idev);
पूर्ण

अटल काष्ठा acpi_driver acer_wireless_driver = अणु
	.name = "Acer Wireless Radio Control Driver",
	.class = "hotkey",
	.ids = acer_wireless_acpi_ids,
	.ops = अणु
		.add = acer_wireless_add,
		.notअगरy = acer_wireless_notअगरy,
	पूर्ण,
पूर्ण;
module_acpi_driver(acer_wireless_driver);

MODULE_DESCRIPTION("Acer Wireless Radio Control Driver");
MODULE_AUTHOR("Chris Chiu <chiu@gmail.com>");
MODULE_LICENSE("GPL v2");
