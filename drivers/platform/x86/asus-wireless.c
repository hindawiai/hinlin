<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Asus Wireless Radio Control Driver
 *
 * Copyright (C) 2015-2016 Endless Mobile, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/acpi.h>
#समावेश <linux/input.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/leds.h>

काष्ठा hswc_params अणु
	u8 on;
	u8 off;
	u8 status;
पूर्ण;

काष्ठा asus_wireless_data अणु
	काष्ठा input_dev *idev;
	काष्ठा acpi_device *adev;
	स्थिर काष्ठा hswc_params *hswc_params;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा work_काष्ठा led_work;
	काष्ठा led_classdev led;
	पूर्णांक led_state;
पूर्ण;

अटल स्थिर काष्ठा hswc_params atk4001_id_params = अणु
	.on = 0x0,
	.off = 0x1,
	.status = 0x2,
पूर्ण;

अटल स्थिर काष्ठा hswc_params atk4002_id_params = अणु
	.on = 0x5,
	.off = 0x4,
	.status = 0x2,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id device_ids[] = अणु
	अणु"ATK4001", (kernel_uदीर्घ_t)&atk4001_id_paramsपूर्ण,
	अणु"ATK4002", (kernel_uदीर्घ_t)&atk4002_id_paramsपूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, device_ids);

अटल acpi_status asus_wireless_method(acpi_handle handle, स्थिर अक्षर *method,
					पूर्णांक param, u64 *ret)
अणु
	काष्ठा acpi_object_list p;
	जोड़ acpi_object obj;
	acpi_status s;

	acpi_handle_debug(handle, "Evaluating method %s, parameter %#x\n",
			  method, param);
	obj.type = ACPI_TYPE_INTEGER;
	obj.पूर्णांकeger.value = param;
	p.count = 1;
	p.poपूर्णांकer = &obj;

	s = acpi_evaluate_पूर्णांकeger(handle, (acpi_string) method, &p, ret);
	अगर (ACPI_FAILURE(s))
		acpi_handle_err(handle,
				"Failed to eval method %s, param %#x (%d)\n",
				method, param, s);
	अन्यथा
		acpi_handle_debug(handle, "%s returned %#llx\n", method, *ret);

	वापस s;
पूर्ण

अटल क्रमागत led_brightness led_state_get(काष्ठा led_classdev *led)
अणु
	काष्ठा asus_wireless_data *data;
	acpi_status s;
	u64 ret;

	data = container_of(led, काष्ठा asus_wireless_data, led);
	s = asus_wireless_method(acpi_device_handle(data->adev), "HSWC",
				 data->hswc_params->status, &ret);
	अगर (ACPI_SUCCESS(s) && ret == data->hswc_params->on)
		वापस LED_FULL;
	वापस LED_OFF;
पूर्ण

अटल व्योम led_state_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asus_wireless_data *data;
	u64 ret;

	data = container_of(work, काष्ठा asus_wireless_data, led_work);
	asus_wireless_method(acpi_device_handle(data->adev), "HSWC",
			     data->led_state, &ret);
पूर्ण

अटल व्योम led_state_set(काष्ठा led_classdev *led, क्रमागत led_brightness value)
अणु
	काष्ठा asus_wireless_data *data;

	data = container_of(led, काष्ठा asus_wireless_data, led);
	data->led_state = value == LED_OFF ? data->hswc_params->off :
					     data->hswc_params->on;
	queue_work(data->wq, &data->led_work);
पूर्ण

अटल व्योम asus_wireless_notअगरy(काष्ठा acpi_device *adev, u32 event)
अणु
	काष्ठा asus_wireless_data *data = acpi_driver_data(adev);

	dev_dbg(&adev->dev, "event=%#x\n", event);
	अगर (event != 0x88) अणु
		dev_notice(&adev->dev, "Unknown ASHS event: %#x\n", event);
		वापस;
	पूर्ण
	input_report_key(data->idev, KEY_RFKILL, 1);
	input_sync(data->idev);
	input_report_key(data->idev, KEY_RFKILL, 0);
	input_sync(data->idev);
पूर्ण

अटल पूर्णांक asus_wireless_add(काष्ठा acpi_device *adev)
अणु
	काष्ठा asus_wireless_data *data;
	स्थिर काष्ठा acpi_device_id *id;
	पूर्णांक err;

	data = devm_kzalloc(&adev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	adev->driver_data = data;
	data->adev = adev;

	data->idev = devm_input_allocate_device(&adev->dev);
	अगर (!data->idev)
		वापस -ENOMEM;
	data->idev->name = "Asus Wireless Radio Control";
	data->idev->phys = "asus-wireless/input0";
	data->idev->id.bustype = BUS_HOST;
	data->idev->id.venकरोr = PCI_VENDOR_ID_ASUSTEK;
	set_bit(EV_KEY, data->idev->evbit);
	set_bit(KEY_RFKILL, data->idev->keybit);
	err = input_रेजिस्टर_device(data->idev);
	अगर (err)
		वापस err;

	क्रम (id = device_ids; id->id[0]; id++) अणु
		अगर (!म_भेद((अक्षर *) id->id, acpi_device_hid(adev))) अणु
			data->hswc_params =
				(स्थिर काष्ठा hswc_params *)id->driver_data;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!data->hswc_params)
		वापस 0;

	data->wq = create_singlethपढ़ो_workqueue("asus_wireless_workqueue");
	अगर (!data->wq)
		वापस -ENOMEM;
	INIT_WORK(&data->led_work, led_state_update);
	data->led.name = "asus-wireless::airplane";
	data->led.brightness_set = led_state_set;
	data->led.brightness_get = led_state_get;
	data->led.flags = LED_CORE_SUSPENDRESUME;
	data->led.max_brightness = 1;
	data->led.शेष_trigger = "rfkill-none";
	err = devm_led_classdev_रेजिस्टर(&adev->dev, &data->led);
	अगर (err)
		destroy_workqueue(data->wq);

	वापस err;
पूर्ण

अटल पूर्णांक asus_wireless_हटाओ(काष्ठा acpi_device *adev)
अणु
	काष्ठा asus_wireless_data *data = acpi_driver_data(adev);

	अगर (data->wq) अणु
		devm_led_classdev_unरेजिस्टर(&adev->dev, &data->led);
		destroy_workqueue(data->wq);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा acpi_driver asus_wireless_driver = अणु
	.name = "Asus Wireless Radio Control Driver",
	.class = "hotkey",
	.ids = device_ids,
	.ops = अणु
		.add = asus_wireless_add,
		.हटाओ = asus_wireless_हटाओ,
		.notअगरy = asus_wireless_notअगरy,
	पूर्ण,
पूर्ण;
module_acpi_driver(asus_wireless_driver);

MODULE_DESCRIPTION("Asus Wireless Radio Control Driver");
MODULE_AUTHOR("Joथःo Paulo Rechi Vita <jprvita@gmail.com>");
MODULE_LICENSE("GPL");
