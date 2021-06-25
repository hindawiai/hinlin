<शैली गुरु>
/*
 * HID over I2C ACPI Subclass
 *
 * Copyright (c) 2012 Benjamin Tissoires <benjamin.tissoires@gmail.com>
 * Copyright (c) 2012 Ecole Nationale de l'Aviation Civile, France
 * Copyright (c) 2012 Red Hat, Inc
 *
 * This code was विभाजनed out of the core code, which was partly based on
 * "USB HID support for Linux":
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2007-2008 Oliver Neukum
 *  Copyright (c) 2006-2010 Jiri Kosina
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/uuid.h>

#समावेश "i2c-hid.h"

काष्ठा i2c_hid_acpi अणु
	काष्ठा i2chid_ops ops;
	काष्ठा acpi_device *adev;
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id i2c_hid_acpi_blacklist[] = अणु
	/*
	 * The CHPN0001 ACPI device, which is used to describe the Chipone
	 * ICN8505 controller, has a _CID of PNP0C50 but is not HID compatible.
	 */
	अणु"CHPN0001", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

/* HID IतऑC Device: 3cdff6f7-4267-4555-ad05-b30a3d8938de */
अटल guid_t i2c_hid_guid =
	GUID_INIT(0x3CDFF6F7, 0x4267, 0x4555,
		  0xAD, 0x05, 0xB3, 0x0A, 0x3D, 0x89, 0x38, 0xDE);

अटल पूर्णांक i2c_hid_acpi_get_descriptor(काष्ठा acpi_device *adev)
अणु
	acpi_handle handle = acpi_device_handle(adev);
	जोड़ acpi_object *obj;
	u16 hid_descriptor_address;

	अगर (acpi_match_device_ids(adev, i2c_hid_acpi_blacklist) == 0)
		वापस -ENODEV;

	obj = acpi_evaluate_dsm_typed(handle, &i2c_hid_guid, 1, 1, शून्य,
				      ACPI_TYPE_INTEGER);
	अगर (!obj) अणु
		acpi_handle_err(handle, "Error _DSM call to get HID descriptor address failed\n");
		वापस -ENODEV;
	पूर्ण

	hid_descriptor_address = obj->पूर्णांकeger.value;
	ACPI_FREE(obj);

	वापस hid_descriptor_address;
पूर्ण

अटल व्योम i2c_hid_acpi_shutकरोwn_tail(काष्ठा i2chid_ops *ops)
अणु
	काष्ठा i2c_hid_acpi *ihid_acpi = container_of(ops, काष्ठा i2c_hid_acpi, ops);

	acpi_device_set_घातer(ihid_acpi->adev, ACPI_STATE_D3_COLD);
पूर्ण

अटल पूर्णांक i2c_hid_acpi_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा i2c_hid_acpi *ihid_acpi;
	काष्ठा acpi_device *adev;
	u16 hid_descriptor_address;
	पूर्णांक ret;

	adev = ACPI_COMPANION(dev);
	अगर (!adev) अणु
		dev_err(&client->dev, "Error could not get ACPI device\n");
		वापस -ENODEV;
	पूर्ण

	ihid_acpi = devm_kzalloc(&client->dev, माप(*ihid_acpi), GFP_KERNEL);
	अगर (!ihid_acpi)
		वापस -ENOMEM;

	ihid_acpi->adev = adev;
	ihid_acpi->ops.shutकरोwn_tail = i2c_hid_acpi_shutकरोwn_tail;

	ret = i2c_hid_acpi_get_descriptor(adev);
	अगर (ret < 0)
		वापस ret;
	hid_descriptor_address = ret;

	acpi_device_fix_up_घातer(adev);

	अगर (acpi_gbl_FADT.flags & ACPI_FADT_LOW_POWER_S0) अणु
		device_set_wakeup_capable(dev, true);
		device_set_wakeup_enable(dev, false);
	पूर्ण

	वापस i2c_hid_core_probe(client, &ihid_acpi->ops,
				  hid_descriptor_address);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id i2c_hid_acpi_match[] = अणु
	अणु"ACPI0C50", 0 पूर्ण,
	अणु"PNP0C50", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, i2c_hid_acpi_match);

अटल काष्ठा i2c_driver i2c_hid_acpi_driver = अणु
	.driver = अणु
		.name	= "i2c_hid_acpi",
		.pm	= &i2c_hid_core_pm,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.acpi_match_table = i2c_hid_acpi_match,
	पूर्ण,

	.probe_new	= i2c_hid_acpi_probe,
	.हटाओ		= i2c_hid_core_हटाओ,
	.shutकरोwn	= i2c_hid_core_shutकरोwn,
पूर्ण;

module_i2c_driver(i2c_hid_acpi_driver);

MODULE_DESCRIPTION("HID over I2C ACPI driver");
MODULE_AUTHOR("Benjamin Tissoires <benjamin.tissoires@gmail.com>");
MODULE_LICENSE("GPL");
