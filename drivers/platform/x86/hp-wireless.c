<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Airplane mode button क्रम HP & Xiaomi laptops
 *
 *  Copyright (C) 2014-2017 Alex Hung <alex.hung@canonical.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>
#समावेश <acpi/acpi_bus.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alex Hung");
MODULE_ALIAS("acpi*:HPQ6001:*");
MODULE_ALIAS("acpi*:WSTADEF:*");
MODULE_ALIAS("acpi*:AMDI0051:*");

अटल काष्ठा input_dev *hpwl_input_dev;

अटल स्थिर काष्ठा acpi_device_id hpwl_ids[] = अणु
	अणु"HPQ6001", 0पूर्ण,
	अणु"WSTADEF", 0पूर्ण,
	अणु"AMDI0051", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

अटल पूर्णांक hp_wireless_input_setup(व्योम)
अणु
	पूर्णांक err;

	hpwl_input_dev = input_allocate_device();
	अगर (!hpwl_input_dev)
		वापस -ENOMEM;

	hpwl_input_dev->name = "HP Wireless hotkeys";
	hpwl_input_dev->phys = "hpq6001/input0";
	hpwl_input_dev->id.bustype = BUS_HOST;
	hpwl_input_dev->evbit[0] = BIT(EV_KEY);
	set_bit(KEY_RFKILL, hpwl_input_dev->keybit);

	err = input_रेजिस्टर_device(hpwl_input_dev);
	अगर (err)
		जाओ err_मुक्त_dev;

	वापस 0;

err_मुक्त_dev:
	input_मुक्त_device(hpwl_input_dev);
	वापस err;
पूर्ण

अटल व्योम hp_wireless_input_destroy(व्योम)
अणु
	input_unरेजिस्टर_device(hpwl_input_dev);
पूर्ण

अटल व्योम hpwl_notअगरy(काष्ठा acpi_device *acpi_dev, u32 event)
अणु
	अगर (event != 0x80) अणु
		pr_info("Received unknown event (0x%x)\n", event);
		वापस;
	पूर्ण

	input_report_key(hpwl_input_dev, KEY_RFKILL, 1);
	input_sync(hpwl_input_dev);
	input_report_key(hpwl_input_dev, KEY_RFKILL, 0);
	input_sync(hpwl_input_dev);
पूर्ण

अटल पूर्णांक hpwl_add(काष्ठा acpi_device *device)
अणु
	पूर्णांक err;

	err = hp_wireless_input_setup();
	अगर (err)
		pr_err("Failed to setup hp wireless hotkeys\n");

	वापस err;
पूर्ण

अटल पूर्णांक hpwl_हटाओ(काष्ठा acpi_device *device)
अणु
	hp_wireless_input_destroy();
	वापस 0;
पूर्ण

अटल काष्ठा acpi_driver hpwl_driver = अणु
	.name	= "hp-wireless",
	.owner	= THIS_MODULE,
	.ids	= hpwl_ids,
	.ops	= अणु
		.add	= hpwl_add,
		.हटाओ	= hpwl_हटाओ,
		.notअगरy	= hpwl_notअगरy,
	पूर्ण,
पूर्ण;

module_acpi_driver(hpwl_driver);
