<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Intel HID event & 5 button array driver
 *
 *  Copyright (C) 2015 Alex Hung <alex.hung@canonical.com>
 *  Copyright (C) 2015 Andrew Lutomirski <luto@kernel.org>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/suspend.h>

/* When NOT in tablet mode, VGBS वापसs with the flag 0x40 */
#घोषणा TABLET_MODE_FLAG BIT(6)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alex Hung");

अटल स्थिर काष्ठा acpi_device_id पूर्णांकel_hid_ids[] = अणु
	अणु"INT33D5", 0पूर्ण,
	अणु"INTC1051", 0पूर्ण,
	अणु"INTC1054", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, पूर्णांकel_hid_ids);

/* In theory, these are HID usages. */
अटल स्थिर काष्ठा key_entry पूर्णांकel_hid_keymap[] = अणु
	/* 1: LSuper (Page 0x07, usage 0xE3) -- unclear what to करो */
	/* 2: Toggle SW_ROTATE_LOCK -- easy to implement अगर seen in wild */
	अणु KE_KEY, 3, अणु KEY_NUMLOCK पूर्ण पूर्ण,
	अणु KE_KEY, 4, अणु KEY_HOME पूर्ण पूर्ण,
	अणु KE_KEY, 5, अणु KEY_END पूर्ण पूर्ण,
	अणु KE_KEY, 6, अणु KEY_PAGEUP पूर्ण पूर्ण,
	अणु KE_KEY, 7, अणु KEY_PAGEDOWN पूर्ण पूर्ण,
	अणु KE_KEY, 8, अणु KEY_RFKILL पूर्ण पूर्ण,
	अणु KE_KEY, 9, अणु KEY_POWER पूर्ण पूर्ण,
	अणु KE_KEY, 11, अणु KEY_SLEEP पूर्ण पूर्ण,
	/* 13 has two dअगरferent meanings in the spec -- ignore it. */
	अणु KE_KEY, 14, अणु KEY_STOPCD पूर्ण पूर्ण,
	अणु KE_KEY, 15, अणु KEY_PLAYPAUSE पूर्ण पूर्ण,
	अणु KE_KEY, 16, अणु KEY_MUTE पूर्ण पूर्ण,
	अणु KE_KEY, 17, अणु KEY_VOLUMEUP पूर्ण पूर्ण,
	अणु KE_KEY, 18, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,
	अणु KE_KEY, 19, अणु KEY_BRIGHTNESSUP पूर्ण पूर्ण,
	अणु KE_KEY, 20, अणु KEY_BRIGHTNESSDOWN पूर्ण पूर्ण,
	/* 27: wake -- needs special handling */
	अणु KE_END पूर्ण,
पूर्ण;

/* 5 button array notअगरication value. */
अटल स्थिर काष्ठा key_entry पूर्णांकel_array_keymap[] = अणु
	अणु KE_KEY,    0xC2, अणु KEY_LEFTMETA पूर्ण पूर्ण,                /* Press */
	अणु KE_IGNORE, 0xC3, अणु KEY_LEFTMETA पूर्ण पूर्ण,                /* Release */
	अणु KE_KEY,    0xC4, अणु KEY_VOLUMEUP पूर्ण पूर्ण,                /* Press */
	अणु KE_IGNORE, 0xC5, अणु KEY_VOLUMEUP पूर्ण पूर्ण,                /* Release */
	अणु KE_KEY,    0xC6, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,              /* Press */
	अणु KE_IGNORE, 0xC7, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,              /* Release */
	अणु KE_KEY,    0xC8, अणु KEY_ROTATE_LOCK_TOGGLE पूर्ण पूर्ण,      /* Press */
	अणु KE_IGNORE, 0xC9, अणु KEY_ROTATE_LOCK_TOGGLE पूर्ण पूर्ण,      /* Release */
	अणु KE_KEY,    0xCE, अणु KEY_POWER पूर्ण पूर्ण,                   /* Press */
	अणु KE_IGNORE, 0xCF, अणु KEY_POWER पूर्ण पूर्ण,                   /* Release */
	अणु KE_END पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id button_array_table[] = अणु
	अणु
		.ident = "Wacom MobileStudio Pro 13",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Wacom Co.,Ltd"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Wacom MobileStudio Pro 13"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Wacom MobileStudio Pro 16",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Wacom Co.,Ltd"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Wacom MobileStudio Pro 16"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "HP Spectre x2 (2015)",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP Spectre x2 Detachable"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Lenovo ThinkPad X1 Tablet Gen 2",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_FAMILY, "ThinkPad X1 Tablet Gen 2"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 * Some convertible use the पूर्णांकel-hid ACPI पूर्णांकerface to report SW_TABLET_MODE,
 * these need to be compared via a DMI based authorization list because some
 * models have unreliable VGBS वापस which could cause incorrect
 * SW_TABLET_MODE report.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id dmi_vgbs_allow_list[] = अणु
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP Spectre x360 Convertible 15-df0xxx"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

काष्ठा पूर्णांकel_hid_priv अणु
	काष्ठा input_dev *input_dev;
	काष्ठा input_dev *array;
	काष्ठा input_dev *चयनes;
	bool wakeup_mode;
पूर्ण;

#घोषणा HID_EVENT_FILTER_UUID	"eeec56b3-4442-408f-a792-4edd4d758054"

क्रमागत पूर्णांकel_hid_dsm_fn_codes अणु
	INTEL_HID_DSM_FN_INVALID,
	INTEL_HID_DSM_BTNL_FN,
	INTEL_HID_DSM_HDMM_FN,
	INTEL_HID_DSM_HDSM_FN,
	INTEL_HID_DSM_HDEM_FN,
	INTEL_HID_DSM_BTNS_FN,
	INTEL_HID_DSM_BTNE_FN,
	INTEL_HID_DSM_HEBC_V1_FN,
	INTEL_HID_DSM_VGBS_FN,
	INTEL_HID_DSM_HEBC_V2_FN,
	INTEL_HID_DSM_FN_MAX
पूर्ण;

अटल स्थिर अक्षर *पूर्णांकel_hid_dsm_fn_to_method[INTEL_HID_DSM_FN_MAX] = अणु
	शून्य,
	"BTNL",
	"HDMM",
	"HDSM",
	"HDEM",
	"BTNS",
	"BTNE",
	"HEBC",
	"VGBS",
	"HEBC"
पूर्ण;

अटल अचिन्हित दीर्घ दीर्घ पूर्णांकel_hid_dsm_fn_mask;
अटल guid_t पूर्णांकel_dsm_guid;

अटल bool पूर्णांकel_hid_execute_method(acpi_handle handle,
				     क्रमागत पूर्णांकel_hid_dsm_fn_codes fn_index,
				     अचिन्हित दीर्घ दीर्घ arg)
अणु
	जोड़ acpi_object *obj, argv4, req;
	acpi_status status;
	अक्षर *method_name;

	अगर (fn_index <= INTEL_HID_DSM_FN_INVALID ||
	    fn_index >= INTEL_HID_DSM_FN_MAX)
		वापस false;

	method_name = (अक्षर *)पूर्णांकel_hid_dsm_fn_to_method[fn_index];

	अगर (!(पूर्णांकel_hid_dsm_fn_mask & BIT(fn_index)))
		जाओ skip_dsm_exec;

	/* All methods expects a package with one पूर्णांकeger element */
	req.type = ACPI_TYPE_INTEGER;
	req.पूर्णांकeger.value = arg;

	argv4.type = ACPI_TYPE_PACKAGE;
	argv4.package.count = 1;
	argv4.package.elements = &req;

	obj = acpi_evaluate_dsm(handle, &पूर्णांकel_dsm_guid, 1, fn_index, &argv4);
	अगर (obj) अणु
		acpi_handle_debug(handle, "Exec DSM Fn code: %d[%s] success\n",
				  fn_index, method_name);
		ACPI_FREE(obj);
		वापस true;
	पूर्ण

skip_dsm_exec:
	status = acpi_execute_simple_method(handle, method_name, arg);
	अगर (ACPI_SUCCESS(status))
		वापस true;

	वापस false;
पूर्ण

अटल bool पूर्णांकel_hid_evaluate_method(acpi_handle handle,
				      क्रमागत पूर्णांकel_hid_dsm_fn_codes fn_index,
				      अचिन्हित दीर्घ दीर्घ *result)
अणु
	जोड़ acpi_object *obj;
	acpi_status status;
	अक्षर *method_name;

	अगर (fn_index <= INTEL_HID_DSM_FN_INVALID ||
	    fn_index >= INTEL_HID_DSM_FN_MAX)
		वापस false;

	method_name = (अक्षर *)पूर्णांकel_hid_dsm_fn_to_method[fn_index];

	अगर (!(पूर्णांकel_hid_dsm_fn_mask & fn_index))
		जाओ skip_dsm_eval;

	obj = acpi_evaluate_dsm_typed(handle, &पूर्णांकel_dsm_guid,
				      1, fn_index,
				      शून्य,  ACPI_TYPE_INTEGER);
	अगर (obj) अणु
		*result = obj->पूर्णांकeger.value;
		acpi_handle_debug(handle,
				  "Eval DSM Fn code: %d[%s] results: 0x%llx\n",
				  fn_index, method_name, *result);
		ACPI_FREE(obj);
		वापस true;
	पूर्ण

skip_dsm_eval:
	status = acpi_evaluate_पूर्णांकeger(handle, method_name, शून्य, result);
	अगर (ACPI_SUCCESS(status))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम पूर्णांकel_hid_init_dsm(acpi_handle handle)
अणु
	जोड़ acpi_object *obj;

	guid_parse(HID_EVENT_FILTER_UUID, &पूर्णांकel_dsm_guid);

	obj = acpi_evaluate_dsm_typed(handle, &पूर्णांकel_dsm_guid, 1, 0, शून्य,
				      ACPI_TYPE_BUFFER);
	अगर (obj) अणु
		चयन (obj->buffer.length) अणु
		शेष:
		हाल 2:
			पूर्णांकel_hid_dsm_fn_mask = *(u16 *)obj->buffer.poपूर्णांकer;
			अवरोध;
		हाल 1:
			पूर्णांकel_hid_dsm_fn_mask = *obj->buffer.poपूर्णांकer;
			अवरोध;
		हाल 0:
			acpi_handle_warn(handle, "intel_hid_dsm_fn_mask length is zero\n");
			पूर्णांकel_hid_dsm_fn_mask = 0;
			अवरोध;
		पूर्ण
		ACPI_FREE(obj);
	पूर्ण

	acpi_handle_debug(handle, "intel_hid_dsm_fn_mask = %llx\n",
			  पूर्णांकel_hid_dsm_fn_mask);
पूर्ण

अटल पूर्णांक पूर्णांकel_hid_set_enable(काष्ठा device *device, bool enable)
अणु
	acpi_handle handle = ACPI_HANDLE(device);

	/* Enable|disable features - घातer button is always enabled */
	अगर (!पूर्णांकel_hid_execute_method(handle, INTEL_HID_DSM_HDSM_FN,
				      enable)) अणु
		dev_warn(device, "failed to %sable hotkeys\n",
			 enable ? "en" : "dis");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_button_array_enable(काष्ठा device *device, bool enable)
अणु
	काष्ठा पूर्णांकel_hid_priv *priv = dev_get_drvdata(device);
	acpi_handle handle = ACPI_HANDLE(device);
	अचिन्हित दीर्घ दीर्घ button_cap;
	acpi_status status;

	अगर (!priv->array)
		वापस;

	/* Query supported platक्रमm features */
	status = acpi_evaluate_पूर्णांकeger(handle, "BTNC", शून्य, &button_cap);
	अगर (ACPI_FAILURE(status)) अणु
		dev_warn(device, "failed to get button capability\n");
		वापस;
	पूर्ण

	/* Enable|disable features - घातer button is always enabled */
	अगर (!पूर्णांकel_hid_execute_method(handle, INTEL_HID_DSM_BTNE_FN,
				      enable ? button_cap : 1))
		dev_warn(device, "failed to set button capability\n");
पूर्ण

अटल पूर्णांक पूर्णांकel_hid_pm_prepare(काष्ठा device *device)
अणु
	अगर (device_may_wakeup(device)) अणु
		काष्ठा पूर्णांकel_hid_priv *priv = dev_get_drvdata(device);

		priv->wakeup_mode = true;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_hid_pm_complete(काष्ठा device *device)
अणु
	काष्ठा पूर्णांकel_hid_priv *priv = dev_get_drvdata(device);

	priv->wakeup_mode = false;
पूर्ण

अटल पूर्णांक पूर्णांकel_hid_pl_suspend_handler(काष्ठा device *device)
अणु
	पूर्णांकel_button_array_enable(device, false);

	अगर (!pm_suspend_no_platक्रमm())
		पूर्णांकel_hid_set_enable(device, false);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_hid_pl_resume_handler(काष्ठा device *device)
अणु
	पूर्णांकel_hid_pm_complete(device);

	अगर (!pm_suspend_no_platक्रमm())
		पूर्णांकel_hid_set_enable(device, true);

	पूर्णांकel_button_array_enable(device, true);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops पूर्णांकel_hid_pl_pm_ops = अणु
	.prepare = पूर्णांकel_hid_pm_prepare,
	.complete = पूर्णांकel_hid_pm_complete,
	.मुक्तze  = पूर्णांकel_hid_pl_suspend_handler,
	.thaw  = पूर्णांकel_hid_pl_resume_handler,
	.restore  = पूर्णांकel_hid_pl_resume_handler,
	.suspend  = पूर्णांकel_hid_pl_suspend_handler,
	.resume  = पूर्णांकel_hid_pl_resume_handler,
पूर्ण;

अटल पूर्णांक पूर्णांकel_hid_input_setup(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा पूर्णांकel_hid_priv *priv = dev_get_drvdata(&device->dev);
	पूर्णांक ret;

	priv->input_dev = devm_input_allocate_device(&device->dev);
	अगर (!priv->input_dev)
		वापस -ENOMEM;

	ret = sparse_keymap_setup(priv->input_dev, पूर्णांकel_hid_keymap, शून्य);
	अगर (ret)
		वापस ret;

	priv->input_dev->name = "Intel HID events";
	priv->input_dev->id.bustype = BUS_HOST;

	वापस input_रेजिस्टर_device(priv->input_dev);
पूर्ण

अटल पूर्णांक पूर्णांकel_button_array_input_setup(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा पूर्णांकel_hid_priv *priv = dev_get_drvdata(&device->dev);
	पूर्णांक ret;

	/* Setup input device क्रम 5 button array */
	priv->array = devm_input_allocate_device(&device->dev);
	अगर (!priv->array)
		वापस -ENOMEM;

	ret = sparse_keymap_setup(priv->array, पूर्णांकel_array_keymap, शून्य);
	अगर (ret)
		वापस ret;

	priv->array->name = "Intel HID 5 button array";
	priv->array->id.bustype = BUS_HOST;

	वापस input_रेजिस्टर_device(priv->array);
पूर्ण

अटल पूर्णांक पूर्णांकel_hid_चयनes_setup(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा पूर्णांकel_hid_priv *priv = dev_get_drvdata(&device->dev);

	/* Setup input device क्रम चयनes */
	priv->चयनes = devm_input_allocate_device(&device->dev);
	अगर (!priv->चयनes)
		वापस -ENOMEM;

	__set_bit(EV_SW, priv->चयनes->evbit);
	__set_bit(SW_TABLET_MODE, priv->चयनes->swbit);

	priv->चयनes->name = "Intel HID switches";
	priv->चयनes->id.bustype = BUS_HOST;
	वापस input_रेजिस्टर_device(priv->चयनes);
पूर्ण

अटल व्योम report_tablet_mode_state(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा पूर्णांकel_hid_priv *priv = dev_get_drvdata(&device->dev);
	acpi_handle handle = ACPI_HANDLE(&device->dev);
	अचिन्हित दीर्घ दीर्घ vgbs;
	पूर्णांक m;

	अगर (!पूर्णांकel_hid_evaluate_method(handle, INTEL_HID_DSM_VGBS_FN, &vgbs))
		वापस;

	m = !(vgbs & TABLET_MODE_FLAG);
	input_report_चयन(priv->चयनes, SW_TABLET_MODE, m);
	input_sync(priv->चयनes);
पूर्ण

अटल bool report_tablet_mode_event(काष्ठा input_dev *input_dev, u32 event)
अणु
	अगर (!input_dev)
		वापस false;

	चयन (event) अणु
	हाल 0xcc:
		input_report_चयन(input_dev, SW_TABLET_MODE, 1);
		input_sync(input_dev);
		वापस true;
	हाल 0xcd:
		input_report_चयन(input_dev, SW_TABLET_MODE, 0);
		input_sync(input_dev);
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम notअगरy_handler(acpi_handle handle, u32 event, व्योम *context)
अणु
	काष्ठा platक्रमm_device *device = context;
	काष्ठा पूर्णांकel_hid_priv *priv = dev_get_drvdata(&device->dev);
	अचिन्हित दीर्घ दीर्घ ev_index;
	पूर्णांक err;

	/*
	 * Some convertible have unreliable VGBS वापस which could cause incorrect
	 * SW_TABLET_MODE report, in these हालs we enable support when receiving
	 * the first event instead of during driver setup.
	 *
	 * Some 360 degree hinges (yoga) style 2-in-1 devices use 2 accelerometers
	 * to allow the OS to determine the angle between the display and the base
	 * of the device. On Winकरोws these are पढ़ो by a special HingeAngleService
	 * process which calls an ACPI DSM (Device Specअगरic Method) on the
	 * ACPI KIOX010A device node क्रम the sensor in the display, to let the
	 * firmware know अगर the 2-in-1 is in tablet- or laptop-mode so that it can
	 * disable the kbd and touchpad to aव्योम spurious input in tablet-mode.
	 *
	 * The linux kxcjk1013 driver calls the DSM क्रम this once at probe समय
	 * to ensure that the builtin kbd and touchpad work. On some devices this
	 * causes a "spurious" 0xcd event on the पूर्णांकel-hid ACPI dev. In this हाल
	 * there is not a functional tablet-mode चयन, so we should not रेजिस्टर
	 * the tablet-mode चयन device.
	 */
	अगर (!priv->चयनes && (event == 0xcc || event == 0xcd) &&
	    !acpi_dev_present("KIOX010A", शून्य, -1)) अणु
		dev_info(&device->dev, "switch event received, enable switches supports\n");
		err = पूर्णांकel_hid_चयनes_setup(device);
		अगर (err)
			pr_err("Failed to setup Intel HID switches\n");
	पूर्ण

	अगर (priv->wakeup_mode) अणु
		/*
		 * Needed क्रम wakeup from suspend-to-idle to work on some
		 * platक्रमms that करोn't expose the 5-button array, but still
		 * send notअगरies with the घातer button event code to this
		 * device object on घातer button actions जबतक suspended.
		 */
		अगर (event == 0xce)
			जाओ wakeup;

		/*
		 * Some devices send (duplicate) tablet-mode events when moved
		 * around even though the mode has not changed; and they करो this
		 * even when suspended.
		 * Update the चयन state in हाल it changed and then वापस
		 * without waking up to aव्योम spurious wakeups.
		 */
		अगर (event == 0xcc || event == 0xcd) अणु
			report_tablet_mode_event(priv->चयनes, event);
			वापस;
		पूर्ण

		/* Wake up on 5-button array events only. */
		अगर (event == 0xc0 || !priv->array)
			वापस;

		अगर (!sparse_keymap_entry_from_scancode(priv->array, event)) अणु
			dev_info(&device->dev, "unknown event 0x%x\n", event);
			वापस;
		पूर्ण

wakeup:
		pm_wakeup_hard_event(&device->dev);

		वापस;
	पूर्ण

	/*
	 * Needed क्रम suspend to work on some platक्रमms that करोn't expose
	 * the 5-button array, but still send notअगरies with घातer button
	 * event code to this device object on घातer button actions.
	 *
	 * Report the घातer button press and release.
	 */
	अगर (!priv->array) अणु
		अगर (event == 0xce) अणु
			input_report_key(priv->input_dev, KEY_POWER, 1);
			input_sync(priv->input_dev);
			वापस;
		पूर्ण

		अगर (event == 0xcf) अणु
			input_report_key(priv->input_dev, KEY_POWER, 0);
			input_sync(priv->input_dev);
			वापस;
		पूर्ण
	पूर्ण

	अगर (report_tablet_mode_event(priv->चयनes, event))
		वापस;

	/* 0xC0 is क्रम HID events, other values are क्रम 5 button array */
	अगर (event != 0xc0) अणु
		अगर (!priv->array ||
		    !sparse_keymap_report_event(priv->array, event, 1, true))
			dev_dbg(&device->dev, "unknown event 0x%x\n", event);
		वापस;
	पूर्ण

	अगर (!पूर्णांकel_hid_evaluate_method(handle, INTEL_HID_DSM_HDEM_FN,
				       &ev_index)) अणु
		dev_warn(&device->dev, "failed to get event index\n");
		वापस;
	पूर्ण

	अगर (!sparse_keymap_report_event(priv->input_dev, ev_index, 1, true))
		dev_dbg(&device->dev, "unknown event index 0x%llx\n",
			 ev_index);
पूर्ण

अटल bool button_array_present(काष्ठा platक्रमm_device *device)
अणु
	acpi_handle handle = ACPI_HANDLE(&device->dev);
	अचिन्हित दीर्घ दीर्घ event_cap;

	अगर (पूर्णांकel_hid_evaluate_method(handle, INTEL_HID_DSM_HEBC_V2_FN,
				      &event_cap)) अणु
		/* Check presence of 5 button array or v2 घातer button */
		अगर (event_cap & 0x60000)
			वापस true;
	पूर्ण

	अगर (पूर्णांकel_hid_evaluate_method(handle, INTEL_HID_DSM_HEBC_V1_FN,
				      &event_cap)) अणु
		अगर (event_cap & 0x20000)
			वापस true;
	पूर्ण

	अगर (dmi_check_प्रणाली(button_array_table))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक पूर्णांकel_hid_probe(काष्ठा platक्रमm_device *device)
अणु
	acpi_handle handle = ACPI_HANDLE(&device->dev);
	अचिन्हित दीर्घ दीर्घ mode;
	काष्ठा पूर्णांकel_hid_priv *priv;
	acpi_status status;
	पूर्णांक err;

	पूर्णांकel_hid_init_dsm(handle);

	अगर (!पूर्णांकel_hid_evaluate_method(handle, INTEL_HID_DSM_HDMM_FN, &mode)) अणु
		dev_warn(&device->dev, "failed to read mode\n");
		वापस -ENODEV;
	पूर्ण

	अगर (mode != 0) अणु
		/*
		 * This driver only implements "simple" mode.  There appear
		 * to be no other modes, but we should be paranoid and check
		 * क्रम compatibility.
		 */
		dev_info(&device->dev, "platform is not in simple mode\n");
		वापस -ENODEV;
	पूर्ण

	priv = devm_kzalloc(&device->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	dev_set_drvdata(&device->dev, priv);

	err = पूर्णांकel_hid_input_setup(device);
	अगर (err) अणु
		pr_err("Failed to setup Intel HID hotkeys\n");
		वापस err;
	पूर्ण

	/* Setup 5 button array */
	अगर (button_array_present(device)) अणु
		dev_info(&device->dev, "platform supports 5 button array\n");
		err = पूर्णांकel_button_array_input_setup(device);
		अगर (err)
			pr_err("Failed to setup Intel 5 button array hotkeys\n");
	पूर्ण

	/* Setup चयनes क्रम devices that we know VGBS वापस correctly */
	अगर (dmi_check_प्रणाली(dmi_vgbs_allow_list)) अणु
		dev_info(&device->dev, "platform supports switches\n");
		err = पूर्णांकel_hid_चयनes_setup(device);
		अगर (err)
			pr_err("Failed to setup Intel HID switches\n");
		अन्यथा
			report_tablet_mode_state(device);
	पूर्ण

	status = acpi_install_notअगरy_handler(handle,
					     ACPI_DEVICE_NOTIFY,
					     notअगरy_handler,
					     device);
	अगर (ACPI_FAILURE(status))
		वापस -EBUSY;

	err = पूर्णांकel_hid_set_enable(&device->dev, true);
	अगर (err)
		जाओ err_हटाओ_notअगरy;

	अगर (priv->array) अणु
		अचिन्हित दीर्घ दीर्घ dummy;

		पूर्णांकel_button_array_enable(&device->dev, true);

		/* Call button load method to enable HID घातer button */
		अगर (!पूर्णांकel_hid_evaluate_method(handle, INTEL_HID_DSM_BTNL_FN,
					       &dummy)) अणु
			dev_warn(&device->dev,
				 "failed to enable HID power button\n");
		पूर्ण
	पूर्ण

	device_init_wakeup(&device->dev, true);
	/*
	 * In order क्रम प्रणाली wakeup to work, the EC GPE has to be marked as
	 * a wakeup one, so करो that here (this setting will persist, but it has
	 * no effect until the wakeup mask is set क्रम the EC GPE).
	 */
	acpi_ec_mark_gpe_क्रम_wake();
	वापस 0;

err_हटाओ_notअगरy:
	acpi_हटाओ_notअगरy_handler(handle, ACPI_DEVICE_NOTIFY, notअगरy_handler);

	वापस err;
पूर्ण

अटल पूर्णांक पूर्णांकel_hid_हटाओ(काष्ठा platक्रमm_device *device)
अणु
	acpi_handle handle = ACPI_HANDLE(&device->dev);

	device_init_wakeup(&device->dev, false);
	acpi_हटाओ_notअगरy_handler(handle, ACPI_DEVICE_NOTIFY, notअगरy_handler);
	पूर्णांकel_hid_set_enable(&device->dev, false);
	पूर्णांकel_button_array_enable(&device->dev, false);

	/*
	 * Even अगर we failed to shut off the event stream, we can still
	 * safely detach from the device.
	 */
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver पूर्णांकel_hid_pl_driver = अणु
	.driver = अणु
		.name = "intel-hid",
		.acpi_match_table = पूर्णांकel_hid_ids,
		.pm = &पूर्णांकel_hid_pl_pm_ops,
	पूर्ण,
	.probe = पूर्णांकel_hid_probe,
	.हटाओ = पूर्णांकel_hid_हटाओ,
पूर्ण;

/*
 * Unक्रमtunately, some laptops provide a _HID="INT33D5" device with
 * _CID="PNP0C02".  This causes the pnpacpi scan driver to claim the
 * ACPI node, so no platक्रमm device will be created.  The pnpacpi
 * driver rejects this device in subsequent processing, so no physical
 * node is created at all.
 *
 * As a workaround until the ACPI core figures out how to handle
 * this corner हाल, manually ask the ACPI platक्रमm device code to
 * claim the ACPI node.
 */
अटल acpi_status __init
check_acpi_dev(acpi_handle handle, u32 lvl, व्योम *context, व्योम **rv)
अणु
	स्थिर काष्ठा acpi_device_id *ids = context;
	काष्ठा acpi_device *dev;

	अगर (acpi_bus_get_device(handle, &dev) != 0)
		वापस AE_OK;

	अगर (acpi_match_device_ids(dev, ids) == 0)
		अगर (!IS_ERR_OR_शून्य(acpi_create_platक्रमm_device(dev, शून्य)))
			dev_info(&dev->dev,
				 "intel-hid: created platform device\n");

	वापस AE_OK;
पूर्ण

अटल पूर्णांक __init पूर्णांकel_hid_init(व्योम)
अणु
	acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
			    ACPI_UINT32_MAX, check_acpi_dev, शून्य,
			    (व्योम *)पूर्णांकel_hid_ids, शून्य);

	वापस platक्रमm_driver_रेजिस्टर(&पूर्णांकel_hid_pl_driver);
पूर्ण
module_init(पूर्णांकel_hid_init);

अटल व्योम __निकास पूर्णांकel_hid_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&पूर्णांकel_hid_pl_driver);
पूर्ण
module_निकास(पूर्णांकel_hid_निकास);
