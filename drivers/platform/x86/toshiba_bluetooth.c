<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Toshiba Bluetooth Enable Driver
 *
 * Copyright (C) 2009 Jes Sorensen <Jes.Sorensen@gmail.com>
 * Copyright (C) 2015 Azael Avalos <coproscefalo@gmail.com>
 *
 * Thanks to Matthew Garrett क्रम background info on ACPI innards which
 * normal people aren't meant to understand :-)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/acpi.h>
#समावेश <linux/rfसमाप्त.h>

#घोषणा BT_KILLSWITCH_MASK	0x01
#घोषणा BT_PLUGGED_MASK		0x40
#घोषणा BT_POWER_MASK		0x80

MODULE_AUTHOR("Jes Sorensen <Jes.Sorensen@gmail.com>");
MODULE_DESCRIPTION("Toshiba Laptop ACPI Bluetooth Enable Driver");
MODULE_LICENSE("GPL");

काष्ठा toshiba_bluetooth_dev अणु
	काष्ठा acpi_device *acpi_dev;
	काष्ठा rfसमाप्त *rfk;

	bool समाप्तचयन;
	bool plugged;
	bool घातered;
पूर्ण;

अटल पूर्णांक toshiba_bt_rfसमाप्त_add(काष्ठा acpi_device *device);
अटल पूर्णांक toshiba_bt_rfसमाप्त_हटाओ(काष्ठा acpi_device *device);
अटल व्योम toshiba_bt_rfसमाप्त_notअगरy(काष्ठा acpi_device *device, u32 event);

अटल स्थिर काष्ठा acpi_device_id bt_device_ids[] = अणु
	अणु "TOS6205", 0पूर्ण,
	अणु "", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bt_device_ids);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक toshiba_bt_resume(काष्ठा device *dev);
#पूर्ण_अगर
अटल SIMPLE_DEV_PM_OPS(toshiba_bt_pm, शून्य, toshiba_bt_resume);

अटल काष्ठा acpi_driver toshiba_bt_rfसमाप्त_driver = अणु
	.name =		"Toshiba BT",
	.class =	"Toshiba",
	.ids =		bt_device_ids,
	.ops =		अणु
				.add =		toshiba_bt_rfसमाप्त_add,
				.हटाओ =	toshiba_bt_rfसमाप्त_हटाओ,
				.notअगरy =	toshiba_bt_rfसमाप्त_notअगरy,
			पूर्ण,
	.owner = 	THIS_MODULE,
	.drv.pm =	&toshiba_bt_pm,
पूर्ण;

अटल पूर्णांक toshiba_bluetooth_present(acpi_handle handle)
अणु
	acpi_status result;
	u64 bt_present;

	/*
	 * Some Toshiba laptops may have a fake TOS6205 device in
	 * their ACPI BIOS, so query the _STA method to see अगर there
	 * is really anything there.
	 */
	result = acpi_evaluate_पूर्णांकeger(handle, "_STA", शून्य, &bt_present);
	अगर (ACPI_FAILURE(result)) अणु
		pr_err("ACPI call to query Bluetooth presence failed\n");
		वापस -ENXIO;
	पूर्ण

	अगर (!bt_present) अणु
		pr_info("Bluetooth device not present\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक toshiba_bluetooth_status(acpi_handle handle)
अणु
	acpi_status result;
	u64 status;

	result = acpi_evaluate_पूर्णांकeger(handle, "BTST", शून्य, &status);
	अगर (ACPI_FAILURE(result)) अणु
		pr_err("Could not get Bluetooth device status\n");
		वापस -ENXIO;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक toshiba_bluetooth_enable(acpi_handle handle)
अणु
	acpi_status result;

	result = acpi_evaluate_object(handle, "AUSB", शून्य, शून्य);
	अगर (ACPI_FAILURE(result)) अणु
		pr_err("Could not attach USB Bluetooth device\n");
		वापस -ENXIO;
	पूर्ण

	result = acpi_evaluate_object(handle, "BTPO", शून्य, शून्य);
	अगर (ACPI_FAILURE(result)) अणु
		pr_err("Could not power ON Bluetooth device\n");
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक toshiba_bluetooth_disable(acpi_handle handle)
अणु
	acpi_status result;

	result = acpi_evaluate_object(handle, "BTPF", शून्य, शून्य);
	अगर (ACPI_FAILURE(result)) अणु
		pr_err("Could not power OFF Bluetooth device\n");
		वापस -ENXIO;
	पूर्ण

	result = acpi_evaluate_object(handle, "DUSB", शून्य, शून्य);
	अगर (ACPI_FAILURE(result)) अणु
		pr_err("Could not detach USB Bluetooth device\n");
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

/* Helper function */
अटल पूर्णांक toshiba_bluetooth_sync_status(काष्ठा toshiba_bluetooth_dev *bt_dev)
अणु
	पूर्णांक status;

	status = toshiba_bluetooth_status(bt_dev->acpi_dev->handle);
	अगर (status < 0) अणु
		pr_err("Could not sync bluetooth device status\n");
		वापस status;
	पूर्ण

	bt_dev->समाप्तचयन = (status & BT_KILLSWITCH_MASK) ? true : false;
	bt_dev->plugged = (status & BT_PLUGGED_MASK) ? true : false;
	bt_dev->घातered = (status & BT_POWER_MASK) ? true : false;

	pr_debug("Bluetooth status %d killswitch %d plugged %d powered %d\n",
		 status, bt_dev->समाप्तचयन, bt_dev->plugged, bt_dev->घातered);

	वापस 0;
पूर्ण

/* RFKill handlers */
अटल पूर्णांक bt_rfसमाप्त_set_block(व्योम *data, bool blocked)
अणु
	काष्ठा toshiba_bluetooth_dev *bt_dev = data;
	पूर्णांक ret;

	ret = toshiba_bluetooth_sync_status(bt_dev);
	अगर (ret)
		वापस ret;

	अगर (!bt_dev->समाप्तचयन)
		वापस 0;

	अगर (blocked)
		ret = toshiba_bluetooth_disable(bt_dev->acpi_dev->handle);
	अन्यथा
		ret = toshiba_bluetooth_enable(bt_dev->acpi_dev->handle);

	वापस ret;
पूर्ण

अटल व्योम bt_rfसमाप्त_poll(काष्ठा rfसमाप्त *rfसमाप्त, व्योम *data)
अणु
	काष्ठा toshiba_bluetooth_dev *bt_dev = data;

	अगर (toshiba_bluetooth_sync_status(bt_dev))
		वापस;

	/*
	 * Note the Toshiba Bluetooth RFKill चयन seems to be a strange
	 * fish. It only provides a BT event when the चयन is flipped to
	 * the 'on' position. When flipping it to 'off', the USB device is
	 * simply pulled away underneath us, without any BT event being
	 * delivered.
	 */
	rfसमाप्त_set_hw_state(bt_dev->rfk, !bt_dev->समाप्तचयन);
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops rfk_ops = अणु
	.set_block = bt_rfसमाप्त_set_block,
	.poll = bt_rfसमाप्त_poll,
पूर्ण;

/* ACPI driver functions */
अटल व्योम toshiba_bt_rfसमाप्त_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा toshiba_bluetooth_dev *bt_dev = acpi_driver_data(device);

	अगर (toshiba_bluetooth_sync_status(bt_dev))
		वापस;

	rfसमाप्त_set_hw_state(bt_dev->rfk, !bt_dev->समाप्तचयन);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक toshiba_bt_resume(काष्ठा device *dev)
अणु
	काष्ठा toshiba_bluetooth_dev *bt_dev;
	पूर्णांक ret;

	bt_dev = acpi_driver_data(to_acpi_device(dev));

	ret = toshiba_bluetooth_sync_status(bt_dev);
	अगर (ret)
		वापस ret;

	rfसमाप्त_set_hw_state(bt_dev->rfk, !bt_dev->समाप्तचयन);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक toshiba_bt_rfसमाप्त_add(काष्ठा acpi_device *device)
अणु
	काष्ठा toshiba_bluetooth_dev *bt_dev;
	पूर्णांक result;

	result = toshiba_bluetooth_present(device->handle);
	अगर (result)
		वापस result;

	pr_info("Toshiba ACPI Bluetooth device driver\n");

	bt_dev = kzalloc(माप(*bt_dev), GFP_KERNEL);
	अगर (!bt_dev)
		वापस -ENOMEM;
	bt_dev->acpi_dev = device;
	device->driver_data = bt_dev;
	dev_set_drvdata(&device->dev, bt_dev);

	result = toshiba_bluetooth_sync_status(bt_dev);
	अगर (result) अणु
		kमुक्त(bt_dev);
		वापस result;
	पूर्ण

	bt_dev->rfk = rfसमाप्त_alloc("Toshiba Bluetooth",
				   &device->dev,
				   RFKILL_TYPE_BLUETOOTH,
				   &rfk_ops,
				   bt_dev);
	अगर (!bt_dev->rfk) अणु
		pr_err("Unable to allocate rfkill device\n");
		kमुक्त(bt_dev);
		वापस -ENOMEM;
	पूर्ण

	rfसमाप्त_set_hw_state(bt_dev->rfk, !bt_dev->समाप्तचयन);

	result = rfसमाप्त_रेजिस्टर(bt_dev->rfk);
	अगर (result) अणु
		pr_err("Unable to register rfkill device\n");
		rfसमाप्त_destroy(bt_dev->rfk);
		kमुक्त(bt_dev);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक toshiba_bt_rfसमाप्त_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा toshiba_bluetooth_dev *bt_dev = acpi_driver_data(device);

	/* clean up */
	अगर (bt_dev->rfk) अणु
		rfसमाप्त_unरेजिस्टर(bt_dev->rfk);
		rfसमाप्त_destroy(bt_dev->rfk);
	पूर्ण

	kमुक्त(bt_dev);

	वापस toshiba_bluetooth_disable(device->handle);
पूर्ण

module_acpi_driver(toshiba_bt_rfसमाप्त_driver);
