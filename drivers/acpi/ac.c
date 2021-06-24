<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  acpi_ac.c - ACPI AC Adapter Driver (Revision: 27)
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) "ACPI: AC: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/dmi.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/acpi.h>
#समावेश <acpi/battery.h>

#घोषणा ACPI_AC_CLASS			"ac_adapter"
#घोषणा ACPI_AC_DEVICE_NAME		"AC Adapter"
#घोषणा ACPI_AC_खाता_STATE		"state"
#घोषणा ACPI_AC_NOTIFY_STATUS		0x80
#घोषणा ACPI_AC_STATUS_OFFLINE		0x00
#घोषणा ACPI_AC_STATUS_ONLINE		0x01
#घोषणा ACPI_AC_STATUS_UNKNOWN		0xFF

MODULE_AUTHOR("Paul Diefenbaugh");
MODULE_DESCRIPTION("ACPI AC Adapter Driver");
MODULE_LICENSE("GPL");


अटल पूर्णांक acpi_ac_add(काष्ठा acpi_device *device);
अटल पूर्णांक acpi_ac_हटाओ(काष्ठा acpi_device *device);
अटल व्योम acpi_ac_notअगरy(काष्ठा acpi_device *device, u32 event);

काष्ठा acpi_ac_bl अणु
	स्थिर अक्षर *hid;
	पूर्णांक hrv;
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id ac_device_ids[] = अणु
	अणु"ACPI0003", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ac_device_ids);

/* Lists of PMIC ACPI HIDs with an (often better) native अक्षरger driver */
अटल स्थिर काष्ठा acpi_ac_bl acpi_ac_blacklist[] = अणु
	अणु "INT33F4", -1 पूर्ण, /* X-Powers AXP288 PMIC */
	अणु "INT34D3",  3 पूर्ण, /* Intel Cherrytrail Whiskey Cove PMIC */
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acpi_ac_resume(काष्ठा device *dev);
#पूर्ण_अगर
अटल SIMPLE_DEV_PM_OPS(acpi_ac_pm, शून्य, acpi_ac_resume);

अटल पूर्णांक ac_sleep_beक्रमe_get_state_ms;
अटल पूर्णांक ac_check_pmic = 1;

अटल काष्ठा acpi_driver acpi_ac_driver = अणु
	.name = "ac",
	.class = ACPI_AC_CLASS,
	.ids = ac_device_ids,
	.flags = ACPI_DRIVER_ALL_NOTIFY_EVENTS,
	.ops = अणु
		.add = acpi_ac_add,
		.हटाओ = acpi_ac_हटाओ,
		.notअगरy = acpi_ac_notअगरy,
		पूर्ण,
	.drv.pm = &acpi_ac_pm,
पूर्ण;

काष्ठा acpi_ac अणु
	काष्ठा घातer_supply *अक्षरger;
	काष्ठा घातer_supply_desc अक्षरger_desc;
	काष्ठा acpi_device *device;
	अचिन्हित दीर्घ दीर्घ state;
	काष्ठा notअगरier_block battery_nb;
पूर्ण;

#घोषणा to_acpi_ac(x) घातer_supply_get_drvdata(x)

/* AC Adapter Management */
अटल पूर्णांक acpi_ac_get_state(काष्ठा acpi_ac *ac)
अणु
	acpi_status status = AE_OK;

	अगर (!ac)
		वापस -EINVAL;

	status = acpi_evaluate_पूर्णांकeger(ac->device->handle, "_PSR", शून्य,
				       &ac->state);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_info(ac->device->handle,
				"Error reading AC Adapter state: %s\n",
				acpi_क्रमmat_exception(status));
		ac->state = ACPI_AC_STATUS_UNKNOWN;
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/* sysfs I/F */
अटल पूर्णांक get_ac_property(काष्ठा घातer_supply *psy,
			   क्रमागत घातer_supply_property psp,
			   जोड़ घातer_supply_propval *val)
अणु
	काष्ठा acpi_ac *ac = to_acpi_ac(psy);

	अगर (!ac)
		वापस -ENODEV;

	अगर (acpi_ac_get_state(ac))
		वापस -ENODEV;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = ac->state;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property ac_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

/* Driver Model */
अटल व्योम acpi_ac_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा acpi_ac *ac = acpi_driver_data(device);

	अगर (!ac)
		वापस;

	चयन (event) अणु
	शेष:
		acpi_handle_debug(device->handle, "Unsupported event [0x%x]\n",
				  event);
		fallthrough;
	हाल ACPI_AC_NOTIFY_STATUS:
	हाल ACPI_NOTIFY_BUS_CHECK:
	हाल ACPI_NOTIFY_DEVICE_CHECK:
		/*
		 * A buggy BIOS may notअगरy AC first and then sleep क्रम
		 * a specअगरic समय beक्रमe करोing actual operations in the
		 * EC event handler (_Qxx). This will cause the AC state
		 * reported by the ACPI event to be incorrect, so रुको क्रम a
		 * specअगरic समय क्रम the EC event handler to make progress.
		 */
		अगर (ac_sleep_beक्रमe_get_state_ms > 0)
			msleep(ac_sleep_beक्रमe_get_state_ms);

		acpi_ac_get_state(ac);
		acpi_bus_generate_netlink_event(device->pnp.device_class,
						  dev_name(&device->dev), event,
						  (u32) ac->state);
		acpi_notअगरier_call_chain(device, event, (u32) ac->state);
		kobject_uevent(&ac->अक्षरger->dev.kobj, KOBJ_CHANGE);
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_ac_battery_notअगरy(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा acpi_ac *ac = container_of(nb, काष्ठा acpi_ac, battery_nb);
	काष्ठा acpi_bus_event *event = (काष्ठा acpi_bus_event *)data;

	/*
	 * On HP Pavilion dv6-6179er AC status notअगरications aren't triggered
	 * when adapter is plugged/unplugged. However, battery status
	 * notअगरications are triggered when battery starts अक्षरging or
	 * disअक्षरging. Re-पढ़ोing AC status triggers lost AC notअगरications,
	 * अगर AC status has changed.
	 */
	अगर (म_भेद(event->device_class, ACPI_BATTERY_CLASS) == 0 &&
	    event->type == ACPI_BATTERY_NOTIFY_STATUS)
		acpi_ac_get_state(ac);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक __init thinkpad_e530_quirk(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	ac_sleep_beक्रमe_get_state_ms = 1000;
	वापस 0;
पूर्ण

अटल पूर्णांक __init ac_करो_not_check_pmic_quirk(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	ac_check_pmic = 0;
	वापस 0;
पूर्ण

/* Please keep this list alphabetically sorted */
अटल स्थिर काष्ठा dmi_प्रणाली_id ac_dmi_table[]  __initस्थिर = अणु
	अणु
		/* ECS EF20EA, AXP288 PMIC but uses separate fuel-gauge */
		.callback = ac_करो_not_check_pmic_quirk,
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "EF20EA"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Lenovo Ideapad Miix 320, AXP288 PMIC, separate fuel-gauge */
		.callback = ac_करो_not_check_pmic_quirk,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "80XF"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "Lenovo MIIX 320-10ICR"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Lenovo Thinkpad e530, see comment in acpi_ac_notअगरy() */
		.callback = thinkpad_e530_quirk,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "32597CG"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक acpi_ac_add(काष्ठा acpi_device *device)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	पूर्णांक result = 0;
	काष्ठा acpi_ac *ac = शून्य;


	अगर (!device)
		वापस -EINVAL;

	ac = kzalloc(माप(काष्ठा acpi_ac), GFP_KERNEL);
	अगर (!ac)
		वापस -ENOMEM;

	ac->device = device;
	म_नकल(acpi_device_name(device), ACPI_AC_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_AC_CLASS);
	device->driver_data = ac;

	result = acpi_ac_get_state(ac);
	अगर (result)
		जाओ end;

	psy_cfg.drv_data = ac;

	ac->अक्षरger_desc.name = acpi_device_bid(device);
	ac->अक्षरger_desc.type = POWER_SUPPLY_TYPE_MAINS;
	ac->अक्षरger_desc.properties = ac_props;
	ac->अक्षरger_desc.num_properties = ARRAY_SIZE(ac_props);
	ac->अक्षरger_desc.get_property = get_ac_property;
	ac->अक्षरger = घातer_supply_रेजिस्टर(&ac->device->dev,
					    &ac->अक्षरger_desc, &psy_cfg);
	अगर (IS_ERR(ac->अक्षरger)) अणु
		result = PTR_ERR(ac->अक्षरger);
		जाओ end;
	पूर्ण

	pr_info("%s [%s] (%s)\n", acpi_device_name(device),
		acpi_device_bid(device), ac->state ? "on-line" : "off-line");

	ac->battery_nb.notअगरier_call = acpi_ac_battery_notअगरy;
	रेजिस्टर_acpi_notअगरier(&ac->battery_nb);
end:
	अगर (result)
		kमुक्त(ac);

	वापस result;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acpi_ac_resume(काष्ठा device *dev)
अणु
	काष्ठा acpi_ac *ac;
	अचिन्हित पूर्णांक old_state;

	अगर (!dev)
		वापस -EINVAL;

	ac = acpi_driver_data(to_acpi_device(dev));
	अगर (!ac)
		वापस -EINVAL;

	old_state = ac->state;
	अगर (acpi_ac_get_state(ac))
		वापस 0;
	अगर (old_state != ac->state)
		kobject_uevent(&ac->अक्षरger->dev.kobj, KOBJ_CHANGE);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा acpi_ac_resume शून्य
#पूर्ण_अगर

अटल पूर्णांक acpi_ac_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_ac *ac = शून्य;


	अगर (!device || !acpi_driver_data(device))
		वापस -EINVAL;

	ac = acpi_driver_data(device);

	घातer_supply_unरेजिस्टर(ac->अक्षरger);
	unरेजिस्टर_acpi_notअगरier(&ac->battery_nb);

	kमुक्त(ac);

	वापस 0;
पूर्ण

अटल पूर्णांक __init acpi_ac_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक result;

	अगर (acpi_disabled)
		वापस -ENODEV;

	dmi_check_प्रणाली(ac_dmi_table);

	अगर (ac_check_pmic) अणु
		क्रम (i = 0; i < ARRAY_SIZE(acpi_ac_blacklist); i++)
			अगर (acpi_dev_present(acpi_ac_blacklist[i].hid, "1",
					     acpi_ac_blacklist[i].hrv)) अणु
				pr_info("found native %s PMIC, not loading\n",
					acpi_ac_blacklist[i].hid);
				वापस -ENODEV;
			पूर्ण
	पूर्ण

	result = acpi_bus_रेजिस्टर_driver(&acpi_ac_driver);
	अगर (result < 0)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम __निकास acpi_ac_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&acpi_ac_driver);
पूर्ण
module_init(acpi_ac_init);
module_निकास(acpi_ac_निकास);
