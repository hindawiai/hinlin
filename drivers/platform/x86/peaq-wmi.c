<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PEAQ 2-in-1 WMI hotkey driver
 * Copyright (C) 2017 Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#घोषणा PEAQ_DOLBY_BUTTON_GUID		"ABBC0F6F-8EA1-11D1-00A0-C90629100000"
#घोषणा PEAQ_DOLBY_BUTTON_METHOD_ID	5
#घोषणा PEAQ_POLL_INTERVAL_MS		250
#घोषणा PEAQ_POLL_IGNORE_MS		500
#घोषणा PEAQ_POLL_MAX_MS		1000

MODULE_ALIAS("wmi:"PEAQ_DOLBY_BUTTON_GUID);

अटल काष्ठा input_dev *peaq_poll_dev;

/*
 * The Dolby button (yes really a Dolby button) causes an ACPI variable to get
 * set on both press and release. The WMI method checks and clears that flag.
 * So क्रम a press + release we will get back One from the WMI method either once
 * (अगर polling after the release) or twice (polling between press and release).
 * We ignore events क्रम 0.5s after the first event to aव्योम reporting 2 presses.
 */
अटल व्योम peaq_wmi_poll(काष्ठा input_dev *input_dev)
अणु
	अटल अचिन्हित दीर्घ last_event_समय;
	अटल bool had_events;
	जोड़ acpi_object obj;
	acpi_status status;
	u32 dummy = 0;

	काष्ठा acpi_buffer input = अणु माप(dummy), &dummy पूर्ण;
	काष्ठा acpi_buffer output = अणु माप(obj), &obj पूर्ण;

	status = wmi_evaluate_method(PEAQ_DOLBY_BUTTON_GUID, 0,
				     PEAQ_DOLBY_BUTTON_METHOD_ID,
				     &input, &output);
	अगर (ACPI_FAILURE(status))
		वापस;

	अगर (obj.type != ACPI_TYPE_INTEGER) अणु
		dev_err(&input_dev->dev,
			"Error WMBC did not return an integer\n");
		वापस;
	पूर्ण

	अगर (!obj.पूर्णांकeger.value)
		वापस;

	अगर (had_events && समय_beक्रमe(jअगरfies, last_event_समय +
					msecs_to_jअगरfies(PEAQ_POLL_IGNORE_MS)))
		वापस;

	input_event(input_dev, EV_KEY, KEY_SOUND, 1);
	input_sync(input_dev);
	input_event(input_dev, EV_KEY, KEY_SOUND, 0);
	input_sync(input_dev);

	last_event_समय = jअगरfies;
	had_events = true;
पूर्ण

/* Some other devices (Shuttle XS35) use the same WMI GUID क्रम other purposes */
अटल स्थिर काष्ठा dmi_प्रणाली_id peaq_dmi_table[] __initस्थिर = अणु
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "PEAQ"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PEAQ PMM C1010 MD99187"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init peaq_wmi_init(व्योम)
अणु
	पूर्णांक err;

	/* WMI GUID is not unique, also check क्रम a DMI match */
	अगर (!dmi_check_प्रणाली(peaq_dmi_table))
		वापस -ENODEV;

	अगर (!wmi_has_guid(PEAQ_DOLBY_BUTTON_GUID))
		वापस -ENODEV;

	peaq_poll_dev = input_allocate_device();
	अगर (!peaq_poll_dev)
		वापस -ENOMEM;

	peaq_poll_dev->name = "PEAQ WMI hotkeys";
	peaq_poll_dev->phys = "wmi/input0";
	peaq_poll_dev->id.bustype = BUS_HOST;
	input_set_capability(peaq_poll_dev, EV_KEY, KEY_SOUND);

	err = input_setup_polling(peaq_poll_dev, peaq_wmi_poll);
	अगर (err)
		जाओ err_out;

	input_set_poll_पूर्णांकerval(peaq_poll_dev, PEAQ_POLL_INTERVAL_MS);
	input_set_max_poll_पूर्णांकerval(peaq_poll_dev, PEAQ_POLL_MAX_MS);

	err = input_रेजिस्टर_device(peaq_poll_dev);
	अगर (err)
		जाओ err_out;

	वापस 0;

err_out:
	input_मुक्त_device(peaq_poll_dev);
	वापस err;
पूर्ण

अटल व्योम __निकास peaq_wmi_निकास(व्योम)
अणु
	input_unरेजिस्टर_device(peaq_poll_dev);
पूर्ण

module_init(peaq_wmi_init);
module_निकास(peaq_wmi_निकास);

MODULE_DESCRIPTION("PEAQ 2-in-1 WMI hotkey driver");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL");
