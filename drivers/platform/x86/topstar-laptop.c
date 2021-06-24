<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Topstar Laptop ACPI Extras driver
 *
 * Copyright (c) 2009 Herton Ronalकरो Krzesinski <herton@mandriva.com.br>
 * Copyright (c) 2018 Guillaume Douथऊzan-Grard
 *
 * Implementation inspired by existing x86 platक्रमm drivers, in special
 * asus/eepc/fujitsu-laptop, thanks to their authors.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा TOPSTAR_LAPTOP_CLASS "topstar"

काष्ठा topstar_laptop अणु
	काष्ठा acpi_device *device;
	काष्ठा platक्रमm_device *platक्रमm;
	काष्ठा input_dev *input;
	काष्ठा led_classdev led;
पूर्ण;

/*
 * LED
 */

अटल क्रमागत led_brightness topstar_led_get(काष्ठा led_classdev *led)
अणु
	वापस led->brightness;
पूर्ण

अटल पूर्णांक topstar_led_set(काष्ठा led_classdev *led,
		क्रमागत led_brightness state)
अणु
	काष्ठा topstar_laptop *topstar = container_of(led,
			काष्ठा topstar_laptop, led);

	काष्ठा acpi_object_list params;
	जोड़ acpi_object in_obj;
	अचिन्हित दीर्घ दीर्घ पूर्णांक ret;
	acpi_status status;

	params.count = 1;
	params.poपूर्णांकer = &in_obj;
	in_obj.type = ACPI_TYPE_INTEGER;
	in_obj.पूर्णांकeger.value = 0x83;

	/*
	 * Topstar ACPI वापसs 0x30001 when the LED is ON and 0x30000 when it
	 * is OFF.
	 */
	status = acpi_evaluate_पूर्णांकeger(topstar->device->handle,
			"GETX", &params, &ret);
	अगर (ACPI_FAILURE(status))
		वापस -1;

	/*
	 * FNCX(0x83) toggles the LED (more precisely, it is supposed to
	 * act as an hardware चयन and disconnect the WLAN adapter but
	 * it seems to be faulty on some models like the Topstar U931
	 * Notebook).
	 */
	अगर ((ret == 0x30001 && state == LED_OFF)
			|| (ret == 0x30000 && state != LED_OFF)) अणु
		status = acpi_execute_simple_method(topstar->device->handle,
				"FNCX", 0x83);
		अगर (ACPI_FAILURE(status))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक topstar_led_init(काष्ठा topstar_laptop *topstar)
अणु
	topstar->led = (काष्ठा led_classdev) अणु
		.शेष_trigger = "rfkill0",
		.brightness_get = topstar_led_get,
		.brightness_set_blocking = topstar_led_set,
		.name = TOPSTAR_LAPTOP_CLASS "::wlan",
	पूर्ण;

	वापस led_classdev_रेजिस्टर(&topstar->platक्रमm->dev, &topstar->led);
पूर्ण

अटल व्योम topstar_led_निकास(काष्ठा topstar_laptop *topstar)
अणु
	led_classdev_unरेजिस्टर(&topstar->led);
पूर्ण

/*
 * Input
 */

अटल स्थिर काष्ठा key_entry topstar_keymap[] = अणु
	अणु KE_KEY, 0x80, अणु KEY_BRIGHTNESSUP पूर्ण पूर्ण,
	अणु KE_KEY, 0x81, अणु KEY_BRIGHTNESSDOWN पूर्ण पूर्ण,
	अणु KE_KEY, 0x83, अणु KEY_VOLUMEUP पूर्ण पूर्ण,
	अणु KE_KEY, 0x84, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,
	अणु KE_KEY, 0x85, अणु KEY_MUTE पूर्ण पूर्ण,
	अणु KE_KEY, 0x86, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण,
	अणु KE_KEY, 0x87, अणु KEY_F13 पूर्ण पूर्ण, /* touchpad enable/disable key */
	अणु KE_KEY, 0x88, अणु KEY_WLAN पूर्ण पूर्ण,
	अणु KE_KEY, 0x8a, अणु KEY_WWW पूर्ण पूर्ण,
	अणु KE_KEY, 0x8b, अणु KEY_MAIL पूर्ण पूर्ण,
	अणु KE_KEY, 0x8c, अणु KEY_MEDIA पूर्ण पूर्ण,

	/* Known non hotkey events करोn't handled or that we don't care yet */
	अणु KE_IGNORE, 0x82, पूर्ण, /* backlight event */
	अणु KE_IGNORE, 0x8e, पूर्ण,
	अणु KE_IGNORE, 0x8f, पूर्ण,
	अणु KE_IGNORE, 0x90, पूर्ण,

	/*
	 * 'G key' generate two event codes, convert to only
	 * one event/key code क्रम now, consider replacing by
	 * a चयन (3G चयन - SW_3G?)
	 */
	अणु KE_KEY, 0x96, अणु KEY_F14 पूर्ण पूर्ण,
	अणु KE_KEY, 0x97, अणु KEY_F14 पूर्ण पूर्ण,

	अणु KE_END, 0 पूर्ण
पूर्ण;

अटल व्योम topstar_input_notअगरy(काष्ठा topstar_laptop *topstar, पूर्णांक event)
अणु
	अगर (!sparse_keymap_report_event(topstar->input, event, 1, true))
		pr_info("unknown event = 0x%02x\n", event);
पूर्ण

अटल पूर्णांक topstar_input_init(काष्ठा topstar_laptop *topstar)
अणु
	काष्ठा input_dev *input;
	पूर्णांक err;

	input = input_allocate_device();
	अगर (!input)
		वापस -ENOMEM;

	input->name = "Topstar Laptop extra buttons";
	input->phys = TOPSTAR_LAPTOP_CLASS "/input0";
	input->id.bustype = BUS_HOST;
	input->dev.parent = &topstar->platक्रमm->dev;

	err = sparse_keymap_setup(input, topstar_keymap, शून्य);
	अगर (err) अणु
		pr_err("Unable to setup input device keymap\n");
		जाओ err_मुक्त_dev;
	पूर्ण

	err = input_रेजिस्टर_device(input);
	अगर (err) अणु
		pr_err("Unable to register input device\n");
		जाओ err_मुक्त_dev;
	पूर्ण

	topstar->input = input;
	वापस 0;

err_मुक्त_dev:
	input_मुक्त_device(input);
	वापस err;
पूर्ण

अटल व्योम topstar_input_निकास(काष्ठा topstar_laptop *topstar)
अणु
	input_unरेजिस्टर_device(topstar->input);
पूर्ण

/*
 * Platक्रमm
 */

अटल काष्ठा platक्रमm_driver topstar_platक्रमm_driver = अणु
	.driver = अणु
		.name = TOPSTAR_LAPTOP_CLASS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक topstar_platक्रमm_init(काष्ठा topstar_laptop *topstar)
अणु
	पूर्णांक err;

	topstar->platक्रमm = platक्रमm_device_alloc(TOPSTAR_LAPTOP_CLASS, -1);
	अगर (!topstar->platक्रमm)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(topstar->platक्रमm, topstar);

	err = platक्रमm_device_add(topstar->platक्रमm);
	अगर (err)
		जाओ err_device_put;

	वापस 0;

err_device_put:
	platक्रमm_device_put(topstar->platक्रमm);
	वापस err;
पूर्ण

अटल व्योम topstar_platक्रमm_निकास(काष्ठा topstar_laptop *topstar)
अणु
	platक्रमm_device_unरेजिस्टर(topstar->platक्रमm);
पूर्ण

/*
 * ACPI
 */

अटल पूर्णांक topstar_acpi_fncx_चयन(काष्ठा acpi_device *device, bool state)
अणु
	acpi_status status;
	u64 arg = state ? 0x86 : 0x87;

	status = acpi_execute_simple_method(device->handle, "FNCX", arg);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Unable to switch FNCX notifications\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम topstar_acpi_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा topstar_laptop *topstar = acpi_driver_data(device);
	अटल bool dup_evnt[2];
	bool *dup;

	/* 0x83 and 0x84 key events comes duplicated... */
	अगर (event == 0x83 || event == 0x84) अणु
		dup = &dup_evnt[event - 0x83];
		अगर (*dup) अणु
			*dup = false;
			वापस;
		पूर्ण
		*dup = true;
	पूर्ण

	topstar_input_notअगरy(topstar, event);
पूर्ण

अटल पूर्णांक topstar_acpi_init(काष्ठा topstar_laptop *topstar)
अणु
	वापस topstar_acpi_fncx_चयन(topstar->device, true);
पूर्ण

अटल व्योम topstar_acpi_निकास(काष्ठा topstar_laptop *topstar)
अणु
	topstar_acpi_fncx_चयन(topstar->device, false);
पूर्ण

/*
 * Enable software-based WLAN LED control on प्रणालीs with defective
 * hardware चयन.
 */
अटल bool led_workaround;

अटल पूर्णांक dmi_led_workaround(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	led_workaround = true;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id topstar_dmi_ids[] = अणु
	अणु
		.callback = dmi_led_workaround,
		.ident = "Topstar U931/RVP7",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "U931"),
			DMI_MATCH(DMI_BOARD_VERSION, "RVP7"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक topstar_acpi_add(काष्ठा acpi_device *device)
अणु
	काष्ठा topstar_laptop *topstar;
	पूर्णांक err;

	dmi_check_प्रणाली(topstar_dmi_ids);

	topstar = kzalloc(माप(काष्ठा topstar_laptop), GFP_KERNEL);
	अगर (!topstar)
		वापस -ENOMEM;

	म_नकल(acpi_device_name(device), "Topstar TPSACPI");
	म_नकल(acpi_device_class(device), TOPSTAR_LAPTOP_CLASS);
	device->driver_data = topstar;
	topstar->device = device;

	err = topstar_acpi_init(topstar);
	अगर (err)
		जाओ err_मुक्त;

	err = topstar_platक्रमm_init(topstar);
	अगर (err)
		जाओ err_acpi_निकास;

	err = topstar_input_init(topstar);
	अगर (err)
		जाओ err_platक्रमm_निकास;

	अगर (led_workaround) अणु
		err = topstar_led_init(topstar);
		अगर (err)
			जाओ err_input_निकास;
	पूर्ण

	वापस 0;

err_input_निकास:
	topstar_input_निकास(topstar);
err_platक्रमm_निकास:
	topstar_platक्रमm_निकास(topstar);
err_acpi_निकास:
	topstar_acpi_निकास(topstar);
err_मुक्त:
	kमुक्त(topstar);
	वापस err;
पूर्ण

अटल पूर्णांक topstar_acpi_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा topstar_laptop *topstar = acpi_driver_data(device);

	अगर (led_workaround)
		topstar_led_निकास(topstar);

	topstar_input_निकास(topstar);
	topstar_platक्रमm_निकास(topstar);
	topstar_acpi_निकास(topstar);

	kमुक्त(topstar);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id topstar_device_ids[] = अणु
	अणु "TPS0001", 0 पूर्ण,
	अणु "TPSACPI01", 0 पूर्ण,
	अणु "", 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, topstar_device_ids);

अटल काष्ठा acpi_driver topstar_acpi_driver = अणु
	.name = "Topstar laptop ACPI driver",
	.class = TOPSTAR_LAPTOP_CLASS,
	.ids = topstar_device_ids,
	.ops = अणु
		.add = topstar_acpi_add,
		.हटाओ = topstar_acpi_हटाओ,
		.notअगरy = topstar_acpi_notअगरy,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init topstar_laptop_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&topstar_platक्रमm_driver);
	अगर (ret < 0)
		वापस ret;

	ret = acpi_bus_रेजिस्टर_driver(&topstar_acpi_driver);
	अगर (ret < 0)
		जाओ err_driver_unreg;

	pr_info("ACPI extras driver loaded\n");
	वापस 0;

err_driver_unreg:
	platक्रमm_driver_unरेजिस्टर(&topstar_platक्रमm_driver);
	वापस ret;
पूर्ण

अटल व्योम __निकास topstar_laptop_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&topstar_acpi_driver);
	platक्रमm_driver_unरेजिस्टर(&topstar_platक्रमm_driver);
पूर्ण

module_init(topstar_laptop_init);
module_निकास(topstar_laptop_निकास);

MODULE_AUTHOR("Herton Ronaldo Krzesinski");
MODULE_AUTHOR("Guillaume Douथऊzan-Grard");
MODULE_DESCRIPTION("Topstar Laptop ACPI Extras driver");
MODULE_LICENSE("GPL");
