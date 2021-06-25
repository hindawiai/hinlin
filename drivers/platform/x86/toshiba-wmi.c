<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * toshiba_wmi.c - Toshiba WMI Hotkey Driver
 *
 * Copyright (C) 2015 Azael Avalos <coproscefalo@gmail.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/acpi.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/dmi.h>

MODULE_AUTHOR("Azael Avalos");
MODULE_DESCRIPTION("Toshiba WMI Hotkey Driver");
MODULE_LICENSE("GPL");

#घोषणा WMI_EVENT_GUID	"59142400-C6A3-40FA-BADB-8A2652834100"

MODULE_ALIAS("wmi:"WMI_EVENT_GUID);

अटल काष्ठा input_dev *toshiba_wmi_input_dev;

अटल स्थिर काष्ठा key_entry toshiba_wmi_keymap[] __initस्थिर = अणु
	/* TODO: Add keymap values once found... */
	/*अणु KE_KEY, 0x00, अणु KEY_ पूर्ण पूर्ण,*/
	अणु KE_END, 0 पूर्ण
पूर्ण;

अटल व्योम toshiba_wmi_notअगरy(u32 value, व्योम *context)
अणु
	काष्ठा acpi_buffer response = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;

	status = wmi_get_event_data(value, &response);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Bad event status 0x%x\n", status);
		वापस;
	पूर्ण

	obj = (जोड़ acpi_object *)response.poपूर्णांकer;
	अगर (!obj)
		वापस;

	/* TODO: Add proper checks once we have data */
	pr_debug("Unknown event received, obj type %x\n", obj->type);

	kमुक्त(response.poपूर्णांकer);
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id toshiba_wmi_dmi_table[] __initस्थिर = अणु
	अणु
		.ident = "Toshiba laptop",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init toshiba_wmi_input_setup(व्योम)
अणु
	acpi_status status;
	पूर्णांक err;

	toshiba_wmi_input_dev = input_allocate_device();
	अगर (!toshiba_wmi_input_dev)
		वापस -ENOMEM;

	toshiba_wmi_input_dev->name = "Toshiba WMI hotkeys";
	toshiba_wmi_input_dev->phys = "wmi/input0";
	toshiba_wmi_input_dev->id.bustype = BUS_HOST;

	err = sparse_keymap_setup(toshiba_wmi_input_dev,
				  toshiba_wmi_keymap, शून्य);
	अगर (err)
		जाओ err_मुक्त_dev;

	status = wmi_install_notअगरy_handler(WMI_EVENT_GUID,
					    toshiba_wmi_notअगरy, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		err = -EIO;
		जाओ err_मुक्त_dev;
	पूर्ण

	err = input_रेजिस्टर_device(toshiba_wmi_input_dev);
	अगर (err)
		जाओ err_हटाओ_notअगरier;

	वापस 0;

 err_हटाओ_notअगरier:
	wmi_हटाओ_notअगरy_handler(WMI_EVENT_GUID);
 err_मुक्त_dev:
	input_मुक्त_device(toshiba_wmi_input_dev);
	वापस err;
पूर्ण

अटल व्योम toshiba_wmi_input_destroy(व्योम)
अणु
	wmi_हटाओ_notअगरy_handler(WMI_EVENT_GUID);
	input_unरेजिस्टर_device(toshiba_wmi_input_dev);
पूर्ण

अटल पूर्णांक __init toshiba_wmi_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!wmi_has_guid(WMI_EVENT_GUID) ||
	    !dmi_check_प्रणाली(toshiba_wmi_dmi_table))
		वापस -ENODEV;

	ret = toshiba_wmi_input_setup();
	अगर (ret) अणु
		pr_err("Failed to setup input device\n");
		वापस ret;
	पूर्ण

	pr_info("Toshiba WMI Hotkey Driver\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास toshiba_wmi_निकास(व्योम)
अणु
	अगर (wmi_has_guid(WMI_EVENT_GUID))
		toshiba_wmi_input_destroy();
पूर्ण

module_init(toshiba_wmi_init);
module_निकास(toshiba_wmi_निकास);
