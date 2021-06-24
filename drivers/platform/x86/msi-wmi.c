<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MSI WMI hotkeys
 *
 * Copyright (C) 2009 Novell <trenn@suse.de>
 *
 * Most stuff taken over from hp-wmi
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/acpi.h>
#समावेश <linux/backlight.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <acpi/video.h>

MODULE_AUTHOR("Thomas Renninger <trenn@suse.de>");
MODULE_DESCRIPTION("MSI laptop WMI hotkeys driver");
MODULE_LICENSE("GPL");

#घोषणा DRV_NAME "msi-wmi"

#घोषणा MSIWMI_BIOS_GUID "551A1F84-FBDD-4125-91DB-3EA8F44F1D45"
#घोषणा MSIWMI_MSI_EVENT_GUID "B6F3EEF2-3D2F-49DC-9DE3-85BCE18C62F2"
#घोषणा MSIWMI_WIND_EVENT_GUID "5B3CC38A-40D9-7245-8AE6-1145B751BE3F"

MODULE_ALIAS("wmi:" MSIWMI_BIOS_GUID);
MODULE_ALIAS("wmi:" MSIWMI_MSI_EVENT_GUID);
MODULE_ALIAS("wmi:" MSIWMI_WIND_EVENT_GUID);

क्रमागत msi_scancodes अणु
	/* Generic MSI keys (not present on MSI Wind) */
	MSI_KEY_BRIGHTNESSUP	= 0xD0,
	MSI_KEY_BRIGHTNESSDOWN,
	MSI_KEY_VOLUMEUP,
	MSI_KEY_VOLUMEDOWN,
	MSI_KEY_MUTE,
	/* MSI Wind keys */
	WIND_KEY_TOUCHPAD	= 0x08,	/* Fn+F3 touchpad toggle */
	WIND_KEY_BLUETOOTH	= 0x56,	/* Fn+F11 Bluetooth toggle */
	WIND_KEY_CAMERA,		/* Fn+F6 webcam toggle */
	WIND_KEY_WLAN		= 0x5f,	/* Fn+F11 Wi-Fi toggle */
	WIND_KEY_TURBO,			/* Fn+F10 turbo mode toggle */
	WIND_KEY_ECO		= 0x69,	/* Fn+F10 ECO mode toggle */
पूर्ण;
अटल काष्ठा key_entry msi_wmi_keymap[] = अणु
	अणु KE_KEY, MSI_KEY_BRIGHTNESSUP,		अणुKEY_BRIGHTNESSUPपूर्ण पूर्ण,
	अणु KE_KEY, MSI_KEY_BRIGHTNESSDOWN,	अणुKEY_BRIGHTNESSDOWNपूर्ण पूर्ण,
	अणु KE_KEY, MSI_KEY_VOLUMEUP,		अणुKEY_VOLUMEUPपूर्ण पूर्ण,
	अणु KE_KEY, MSI_KEY_VOLUMEDOWN,		अणुKEY_VOLUMEDOWNपूर्ण पूर्ण,
	अणु KE_KEY, MSI_KEY_MUTE,			अणुKEY_MUTEपूर्ण पूर्ण,

	/* These keys work without WMI. Ignore them to aव्योम द्विगुन keycodes */
	अणु KE_IGNORE, WIND_KEY_TOUCHPAD,		अणुKEY_TOUCHPAD_TOGGLEपूर्ण पूर्ण,
	अणु KE_IGNORE, WIND_KEY_BLUETOOTH,	अणुKEY_BLUETOOTHपूर्ण पूर्ण,
	अणु KE_IGNORE, WIND_KEY_CAMERA,		अणुKEY_CAMERAपूर्ण पूर्ण,
	अणु KE_IGNORE, WIND_KEY_WLAN,		अणुKEY_WLANपूर्ण पूर्ण,

	/* These are unknown WMI events found on MSI Wind */
	अणु KE_IGNORE, 0x00 पूर्ण,
	अणु KE_IGNORE, 0x62 पूर्ण,
	अणु KE_IGNORE, 0x63 पूर्ण,

	/* These are MSI Wind keys that should be handled via WMI */
	अणु KE_KEY, WIND_KEY_TURBO,		अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, WIND_KEY_ECO,			अणुKEY_PROG2पूर्ण पूर्ण,

	अणु KE_END, 0 पूर्ण
पूर्ण;

अटल kसमय_प्रकार last_pressed;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *guid;
	bool quirk_last_pressed;
पूर्ण *event_wmi, event_wmis[] = अणु
	अणु MSIWMI_MSI_EVENT_GUID, true पूर्ण,
	अणु MSIWMI_WIND_EVENT_GUID, false पूर्ण,
पूर्ण;

अटल काष्ठा backlight_device *backlight;

अटल पूर्णांक backlight_map[] = अणु 0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF पूर्ण;

अटल काष्ठा input_dev *msi_wmi_input_dev;

अटल पूर्णांक msi_wmi_query_block(पूर्णांक instance, पूर्णांक *ret)
अणु
	acpi_status status;
	जोड़ acpi_object *obj;

	काष्ठा acpi_buffer output = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;

	status = wmi_query_block(MSIWMI_BIOS_GUID, instance, &output);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	obj = output.poपूर्णांकer;

	अगर (!obj || obj->type != ACPI_TYPE_INTEGER) अणु
		अगर (obj) अणु
			pr_err("query block returned object "
			       "type: %d - buffer length:%d\n", obj->type,
			       obj->type == ACPI_TYPE_BUFFER ?
			       obj->buffer.length : 0);
		पूर्ण
		kमुक्त(obj);
		वापस -EINVAL;
	पूर्ण
	*ret = obj->पूर्णांकeger.value;
	kमुक्त(obj);
	वापस 0;
पूर्ण

अटल पूर्णांक msi_wmi_set_block(पूर्णांक instance, पूर्णांक value)
अणु
	acpi_status status;

	काष्ठा acpi_buffer input = अणु माप(पूर्णांक), &value पूर्ण;

	pr_debug("Going to set block of instance: %d - value: %d\n",
		 instance, value);

	status = wmi_set_block(MSIWMI_BIOS_GUID, instance, &input);

	वापस ACPI_SUCCESS(status) ? 0 : 1;
पूर्ण

अटल पूर्णांक bl_get(काष्ठा backlight_device *bd)
अणु
	पूर्णांक level, err, ret;

	/* Instance 1 is "get backlight", cmp with DSDT */
	err = msi_wmi_query_block(1, &ret);
	अगर (err) अणु
		pr_err("Could not query backlight: %d\n", err);
		वापस -EINVAL;
	पूर्ण
	pr_debug("Get: Query block returned: %d\n", ret);
	क्रम (level = 0; level < ARRAY_SIZE(backlight_map); level++) अणु
		अगर (backlight_map[level] == ret) अणु
			pr_debug("Current backlight level: 0x%X - index: %d\n",
				 backlight_map[level], level);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (level == ARRAY_SIZE(backlight_map)) अणु
		pr_err("get: Invalid brightness value: 0x%X\n", ret);
		वापस -EINVAL;
	पूर्ण
	वापस level;
पूर्ण

अटल पूर्णांक bl_set_status(काष्ठा backlight_device *bd)
अणु
	पूर्णांक bright = bd->props.brightness;
	अगर (bright >= ARRAY_SIZE(backlight_map) || bright < 0)
		वापस -EINVAL;

	/* Instance 0 is "set backlight" */
	वापस msi_wmi_set_block(0, backlight_map[bright]);
पूर्ण

अटल स्थिर काष्ठा backlight_ops msi_backlight_ops = अणु
	.get_brightness	= bl_get,
	.update_status	= bl_set_status,
पूर्ण;

अटल व्योम msi_wmi_notअगरy(u32 value, व्योम *context)
अणु
	काष्ठा acpi_buffer response = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा key_entry *key;
	जोड़ acpi_object *obj;
	acpi_status status;

	status = wmi_get_event_data(value, &response);
	अगर (status != AE_OK) अणु
		pr_info("bad event status 0x%x\n", status);
		वापस;
	पूर्ण

	obj = (जोड़ acpi_object *)response.poपूर्णांकer;

	अगर (obj && obj->type == ACPI_TYPE_INTEGER) अणु
		पूर्णांक eventcode = obj->पूर्णांकeger.value;
		pr_debug("Eventcode: 0x%x\n", eventcode);
		key = sparse_keymap_entry_from_scancode(msi_wmi_input_dev,
				eventcode);
		अगर (!key) अणु
			pr_info("Unknown key pressed - %x\n", eventcode);
			जाओ msi_wmi_notअगरy_निकास;
		पूर्ण

		अगर (event_wmi->quirk_last_pressed) अणु
			kसमय_प्रकार cur = kसमय_get_real();
			kसमय_प्रकार dअगरf = kसमय_sub(cur, last_pressed);
			/* Ignore event अगर any event happened in a 50 ms
			   समयframe -> Key press may result in 10-20 GPEs */
			अगर (kसमय_प्रकारo_us(dअगरf) < 1000 * 50) अणु
				pr_debug("Suppressed key event 0x%X - "
					 "Last press was %lld us ago\n",
					 key->code, kसमय_प्रकारo_us(dअगरf));
				जाओ msi_wmi_notअगरy_निकास;
			पूर्ण
			last_pressed = cur;
		पूर्ण

		अगर (key->type == KE_KEY &&
		/* Brightness is served via acpi video driver */
		(backlight ||
		(key->code != MSI_KEY_BRIGHTNESSUP &&
		key->code != MSI_KEY_BRIGHTNESSDOWN))) अणु
			pr_debug("Send key: 0x%X - Input layer keycode: %d\n",
				 key->code, key->keycode);
			sparse_keymap_report_entry(msi_wmi_input_dev, key, 1,
						   true);
		पूर्ण
	पूर्ण अन्यथा
		pr_info("Unknown event received\n");

msi_wmi_notअगरy_निकास:
	kमुक्त(response.poपूर्णांकer);
पूर्ण

अटल पूर्णांक __init msi_wmi_backlight_setup(व्योम)
अणु
	पूर्णांक err;
	काष्ठा backlight_properties props;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = ARRAY_SIZE(backlight_map) - 1;
	backlight = backlight_device_रेजिस्टर(DRV_NAME, शून्य, शून्य,
					      &msi_backlight_ops,
					      &props);
	अगर (IS_ERR(backlight))
		वापस PTR_ERR(backlight);

	err = bl_get(शून्य);
	अगर (err < 0) अणु
		backlight_device_unरेजिस्टर(backlight);
		वापस err;
	पूर्ण

	backlight->props.brightness = err;

	वापस 0;
पूर्ण

अटल पूर्णांक __init msi_wmi_input_setup(व्योम)
अणु
	पूर्णांक err;

	msi_wmi_input_dev = input_allocate_device();
	अगर (!msi_wmi_input_dev)
		वापस -ENOMEM;

	msi_wmi_input_dev->name = "MSI WMI hotkeys";
	msi_wmi_input_dev->phys = "wmi/input0";
	msi_wmi_input_dev->id.bustype = BUS_HOST;

	err = sparse_keymap_setup(msi_wmi_input_dev, msi_wmi_keymap, शून्य);
	अगर (err)
		जाओ err_मुक्त_dev;

	err = input_रेजिस्टर_device(msi_wmi_input_dev);

	अगर (err)
		जाओ err_मुक्त_dev;

	last_pressed = 0;

	वापस 0;

err_मुक्त_dev:
	input_मुक्त_device(msi_wmi_input_dev);
	वापस err;
पूर्ण

अटल पूर्णांक __init msi_wmi_init(व्योम)
अणु
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(event_wmis); i++) अणु
		अगर (!wmi_has_guid(event_wmis[i].guid))
			जारी;

		err = msi_wmi_input_setup();
		अगर (err) अणु
			pr_err("Unable to setup input device\n");
			वापस err;
		पूर्ण

		err = wmi_install_notअगरy_handler(event_wmis[i].guid,
			msi_wmi_notअगरy, शून्य);
		अगर (ACPI_FAILURE(err)) अणु
			pr_err("Unable to setup WMI notify handler\n");
			जाओ err_मुक्त_input;
		पूर्ण

		pr_debug("Event handler installed\n");
		event_wmi = &event_wmis[i];
		अवरोध;
	पूर्ण

	अगर (wmi_has_guid(MSIWMI_BIOS_GUID) &&
	    acpi_video_get_backlight_type() == acpi_backlight_venकरोr) अणु
		err = msi_wmi_backlight_setup();
		अगर (err) अणु
			pr_err("Unable to setup backlight device\n");
			जाओ err_uninstall_handler;
		पूर्ण
		pr_debug("Backlight device created\n");
	पूर्ण

	अगर (!event_wmi && !backlight) अणु
		pr_err("This machine doesn't have neither MSI-hotkeys nor backlight through WMI\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;

err_uninstall_handler:
	अगर (event_wmi)
		wmi_हटाओ_notअगरy_handler(event_wmi->guid);
err_मुक्त_input:
	अगर (event_wmi)
		input_unरेजिस्टर_device(msi_wmi_input_dev);
	वापस err;
पूर्ण

अटल व्योम __निकास msi_wmi_निकास(व्योम)
अणु
	अगर (event_wmi) अणु
		wmi_हटाओ_notअगरy_handler(event_wmi->guid);
		input_unरेजिस्टर_device(msi_wmi_input_dev);
	पूर्ण
	backlight_device_unरेजिस्टर(backlight);
पूर्ण

module_init(msi_wmi_init);
module_निकास(msi_wmi_निकास);
