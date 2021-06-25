<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Intel Virtual Button driver क्रम Winकरोws 8.1+
 *
 *  Copyright (C) 2016 AceLan Kao <acelan.kao@canonical.com>
 *  Copyright (C) 2016 Alex Hung <alex.hung@canonical.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/suspend.h>

/* Returned when NOT in tablet mode on some HP Stream x360 11 models */
#घोषणा VGBS_TABLET_MODE_FLAG_ALT	0x10
/* When NOT in tablet mode, VGBS वापसs with the flag 0x40 */
#घोषणा VGBS_TABLET_MODE_FLAG		0x40
#घोषणा VGBS_DOCK_MODE_FLAG		0x80

#घोषणा VGBS_TABLET_MODE_FLAGS (VGBS_TABLET_MODE_FLAG | VGBS_TABLET_MODE_FLAG_ALT)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("AceLan Kao");

अटल स्थिर काष्ठा acpi_device_id पूर्णांकel_vbtn_ids[] = अणु
	अणु"INT33D6", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, पूर्णांकel_vbtn_ids);

/* In theory, these are HID usages. */
अटल स्थिर काष्ठा key_entry पूर्णांकel_vbtn_keymap[] = अणु
	अणु KE_KEY, 0xC0, अणु KEY_POWER पूर्ण पूर्ण,	/* घातer key press */
	अणु KE_IGNORE, 0xC1, अणु KEY_POWER पूर्ण पूर्ण,	/* घातer key release */
	अणु KE_KEY, 0xC2, अणु KEY_LEFTMETA पूर्ण पूर्ण,		/* 'Windows' key press */
	अणु KE_KEY, 0xC3, अणु KEY_LEFTMETA पूर्ण पूर्ण,		/* 'Windows' key release */
	अणु KE_KEY, 0xC4, अणु KEY_VOLUMEUP पूर्ण पूर्ण,		/* volume-up key press */
	अणु KE_IGNORE, 0xC5, अणु KEY_VOLUMEUP पूर्ण पूर्ण,		/* volume-up key release */
	अणु KE_KEY, 0xC6, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,		/* volume-करोwn key press */
	अणु KE_IGNORE, 0xC7, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,	/* volume-करोwn key release */
	अणु KE_KEY,    0xC8, अणु KEY_ROTATE_LOCK_TOGGLE पूर्ण पूर्ण,	/* rotate-lock key press */
	अणु KE_KEY,    0xC9, अणु KEY_ROTATE_LOCK_TOGGLE पूर्ण पूर्ण,	/* rotate-lock key release */
	अणु KE_END पूर्ण
पूर्ण;

अटल स्थिर काष्ठा key_entry पूर्णांकel_vbtn_चयनmap[] = अणु
	/*
	 * SW_DOCK should only be reported क्रम करोcking stations, but DSDTs using the
	 * पूर्णांकel-vbtn code, always seem to use this क्रम 2-in-1s / convertibles and set
	 * SW_DOCK=1 when in laptop-mode (in tandem with setting SW_TABLET_MODE=0).
	 * This causes userspace to think the laptop is करोcked to a port-replicator
	 * and to disable suspend-on-lid-बंद, which is undesirable.
	 * Map the करोck events to KEY_IGNORE to aव्योम this broken SW_DOCK reporting.
	 */
	अणु KE_IGNORE, 0xCA, अणु .sw = अणु SW_DOCK, 1 पूर्ण पूर्ण पूर्ण,		/* Docked */
	अणु KE_IGNORE, 0xCB, अणु .sw = अणु SW_DOCK, 0 पूर्ण पूर्ण पूर्ण,		/* Unकरोcked */
	अणु KE_SW,     0xCC, अणु .sw = अणु SW_TABLET_MODE, 1 पूर्ण पूर्ण पूर्ण,	/* Tablet */
	अणु KE_SW,     0xCD, अणु .sw = अणु SW_TABLET_MODE, 0 पूर्ण पूर्ण पूर्ण,	/* Laptop */
	अणु KE_END पूर्ण
पूर्ण;

काष्ठा पूर्णांकel_vbtn_priv अणु
	काष्ठा input_dev *buttons_dev;
	काष्ठा input_dev *चयनes_dev;
	bool has_buttons;
	bool has_चयनes;
	bool wakeup_mode;
पूर्ण;

अटल व्योम detect_tablet_mode(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा पूर्णांकel_vbtn_priv *priv = dev_get_drvdata(&device->dev);
	acpi_handle handle = ACPI_HANDLE(&device->dev);
	अचिन्हित दीर्घ दीर्घ vgbs;
	acpi_status status;
	पूर्णांक m;

	status = acpi_evaluate_पूर्णांकeger(handle, "VGBS", शून्य, &vgbs);
	अगर (ACPI_FAILURE(status))
		वापस;

	m = !(vgbs & VGBS_TABLET_MODE_FLAGS);
	input_report_चयन(priv->चयनes_dev, SW_TABLET_MODE, m);
	m = (vgbs & VGBS_DOCK_MODE_FLAG) ? 1 : 0;
	input_report_चयन(priv->चयनes_dev, SW_DOCK, m);
पूर्ण

/*
 * Note this unconditionally creates the 2 input_dev-s and sets up
 * the sparse-keymaps. Only the registration is conditional on
 * have_buttons / have_चयनes. This is करोne so that the notअगरy
 * handler can always call sparse_keymap_entry_from_scancode()
 * on the input_dev-s करो determine the event type.
 */
अटल पूर्णांक पूर्णांकel_vbtn_input_setup(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा पूर्णांकel_vbtn_priv *priv = dev_get_drvdata(&device->dev);
	पूर्णांक ret;

	priv->buttons_dev = devm_input_allocate_device(&device->dev);
	अगर (!priv->buttons_dev)
		वापस -ENOMEM;

	ret = sparse_keymap_setup(priv->buttons_dev, पूर्णांकel_vbtn_keymap, शून्य);
	अगर (ret)
		वापस ret;

	priv->buttons_dev->dev.parent = &device->dev;
	priv->buttons_dev->name = "Intel Virtual Buttons";
	priv->buttons_dev->id.bustype = BUS_HOST;

	अगर (priv->has_buttons) अणु
		ret = input_रेजिस्टर_device(priv->buttons_dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	priv->चयनes_dev = devm_input_allocate_device(&device->dev);
	अगर (!priv->चयनes_dev)
		वापस -ENOMEM;

	ret = sparse_keymap_setup(priv->चयनes_dev, पूर्णांकel_vbtn_चयनmap, शून्य);
	अगर (ret)
		वापस ret;

	priv->चयनes_dev->dev.parent = &device->dev;
	priv->चयनes_dev->name = "Intel Virtual Switches";
	priv->चयनes_dev->id.bustype = BUS_HOST;

	अगर (priv->has_चयनes) अणु
		detect_tablet_mode(device);

		ret = input_रेजिस्टर_device(priv->चयनes_dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम notअगरy_handler(acpi_handle handle, u32 event, व्योम *context)
अणु
	काष्ठा platक्रमm_device *device = context;
	काष्ठा पूर्णांकel_vbtn_priv *priv = dev_get_drvdata(&device->dev);
	अचिन्हित पूर्णांक val = !(event & 1); /* Even=press, Odd=release */
	स्थिर काष्ठा key_entry *ke, *ke_rel;
	काष्ठा input_dev *input_dev;
	bool स्वतःrelease;
	पूर्णांक ret;

	अगर ((ke = sparse_keymap_entry_from_scancode(priv->buttons_dev, event))) अणु
		अगर (!priv->has_buttons) अणु
			dev_warn(&device->dev, "Warning: received a button event on a device without buttons, please report this.\n");
			वापस;
		पूर्ण
		input_dev = priv->buttons_dev;
	पूर्ण अन्यथा अगर ((ke = sparse_keymap_entry_from_scancode(priv->चयनes_dev, event))) अणु
		अगर (!priv->has_चयनes) अणु
			dev_info(&device->dev, "Registering Intel Virtual Switches input-dev after receiving a switch event\n");
			ret = input_रेजिस्टर_device(priv->चयनes_dev);
			अगर (ret)
				वापस;

			priv->has_चयनes = true;
		पूर्ण
		input_dev = priv->चयनes_dev;
	पूर्ण अन्यथा अणु
		dev_dbg(&device->dev, "unknown event index 0x%x\n", event);
		वापस;
	पूर्ण

	अगर (priv->wakeup_mode) अणु
		pm_wakeup_hard_event(&device->dev);

		/*
		 * Skip reporting an evdev event क्रम button wake events,
		 * mirroring how the drivers/acpi/button.c code skips this too.
		 */
		अगर (ke->type == KE_KEY)
			वापस;
	पूर्ण

	/*
	 * Even press events are स्वतःrelease अगर there is no corresponding odd
	 * release event, or अगर the odd event is KE_IGNORE.
	 */
	ke_rel = sparse_keymap_entry_from_scancode(input_dev, event | 1);
	स्वतःrelease = val && (!ke_rel || ke_rel->type == KE_IGNORE);

	sparse_keymap_report_event(input_dev, event, val, स्वतःrelease);
पूर्ण

/*
 * There are several laptops (non 2-in-1) models out there which support VGBS,
 * but simply always वापस 0, which we translate to SW_TABLET_MODE=1. This in
 * turn causes userspace (libinput) to suppress events from the builtin
 * keyboard and touchpad, making the laptop essentially unusable.
 *
 * Since the problem of wrongly reporting SW_TABLET_MODE=1 in combination
 * with libinput, leads to a non-usable प्रणाली. Where as OTOH many people will
 * not even notice when SW_TABLET_MODE is not being reported, a DMI based allow
 * list is used here. This list मुख्यly matches on the chassis-type of 2-in-1s.
 *
 * There are also some 2-in-1s which use the पूर्णांकel-vbtn ACPI पूर्णांकerface to report
 * SW_TABLET_MODE with a chassis-type of 8 ("Portable") or 10 ("Notebook"),
 * these are matched on a per model basis, since many normal laptops with a
 * possible broken VGBS ACPI-method also use these chassis-types.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id dmi_चयनes_allow_list[] = अणु
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_CHASSIS_TYPE, "31" /* Convertible */),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_CHASSIS_TYPE, "32" /* Detachable */),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Venue 11 Pro 7130"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP Pavilion 13 x360 PC"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Switch SA5-271"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 7352"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण /* Array terminator */
पूर्ण;

अटल bool पूर्णांकel_vbtn_has_चयनes(acpi_handle handle)
अणु
	अचिन्हित दीर्घ दीर्घ vgbs;
	acpi_status status;

	अगर (!dmi_check_प्रणाली(dmi_चयनes_allow_list))
		वापस false;

	status = acpi_evaluate_पूर्णांकeger(handle, "VGBS", शून्य, &vgbs);
	वापस ACPI_SUCCESS(status);
पूर्ण

अटल पूर्णांक पूर्णांकel_vbtn_probe(काष्ठा platक्रमm_device *device)
अणु
	acpi_handle handle = ACPI_HANDLE(&device->dev);
	bool has_buttons, has_चयनes;
	काष्ठा पूर्णांकel_vbtn_priv *priv;
	acpi_status status;
	पूर्णांक err;

	has_buttons = acpi_has_method(handle, "VBDL");
	has_चयनes = पूर्णांकel_vbtn_has_चयनes(handle);

	अगर (!has_buttons && !has_चयनes) अणु
		dev_warn(&device->dev, "failed to read Intel Virtual Button driver\n");
		वापस -ENODEV;
	पूर्ण

	priv = devm_kzalloc(&device->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	dev_set_drvdata(&device->dev, priv);

	priv->has_buttons = has_buttons;
	priv->has_चयनes = has_चयनes;

	err = पूर्णांकel_vbtn_input_setup(device);
	अगर (err) अणु
		pr_err("Failed to setup Intel Virtual Button\n");
		वापस err;
	पूर्ण

	status = acpi_install_notअगरy_handler(handle,
					     ACPI_DEVICE_NOTIFY,
					     notअगरy_handler,
					     device);
	अगर (ACPI_FAILURE(status))
		वापस -EBUSY;

	अगर (has_buttons) अणु
		status = acpi_evaluate_object(handle, "VBDL", शून्य, शून्य);
		अगर (ACPI_FAILURE(status))
			dev_err(&device->dev, "Error VBDL failed with ACPI status %d\n", status);
	पूर्ण

	device_init_wakeup(&device->dev, true);
	/*
	 * In order क्रम प्रणाली wakeup to work, the EC GPE has to be marked as
	 * a wakeup one, so करो that here (this setting will persist, but it has
	 * no effect until the wakeup mask is set क्रम the EC GPE).
	 */
	acpi_ec_mark_gpe_क्रम_wake();
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_vbtn_हटाओ(काष्ठा platक्रमm_device *device)
अणु
	acpi_handle handle = ACPI_HANDLE(&device->dev);

	device_init_wakeup(&device->dev, false);
	acpi_हटाओ_notअगरy_handler(handle, ACPI_DEVICE_NOTIFY, notअगरy_handler);

	/*
	 * Even अगर we failed to shut off the event stream, we can still
	 * safely detach from the device.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_vbtn_pm_prepare(काष्ठा device *dev)
अणु
	अगर (device_may_wakeup(dev)) अणु
		काष्ठा पूर्णांकel_vbtn_priv *priv = dev_get_drvdata(dev);

		priv->wakeup_mode = true;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_vbtn_pm_complete(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_vbtn_priv *priv = dev_get_drvdata(dev);

	priv->wakeup_mode = false;
पूर्ण

अटल पूर्णांक पूर्णांकel_vbtn_pm_resume(काष्ठा device *dev)
अणु
	पूर्णांकel_vbtn_pm_complete(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops पूर्णांकel_vbtn_pm_ops = अणु
	.prepare = पूर्णांकel_vbtn_pm_prepare,
	.complete = पूर्णांकel_vbtn_pm_complete,
	.resume = पूर्णांकel_vbtn_pm_resume,
	.restore = पूर्णांकel_vbtn_pm_resume,
	.thaw = पूर्णांकel_vbtn_pm_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver पूर्णांकel_vbtn_pl_driver = अणु
	.driver = अणु
		.name = "intel-vbtn",
		.acpi_match_table = पूर्णांकel_vbtn_ids,
		.pm = &पूर्णांकel_vbtn_pm_ops,
	पूर्ण,
	.probe = पूर्णांकel_vbtn_probe,
	.हटाओ = पूर्णांकel_vbtn_हटाओ,
पूर्ण;

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
				 "intel-vbtn: created platform device\n");

	वापस AE_OK;
पूर्ण

अटल पूर्णांक __init पूर्णांकel_vbtn_init(व्योम)
अणु
	acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
			    ACPI_UINT32_MAX, check_acpi_dev, शून्य,
			    (व्योम *)पूर्णांकel_vbtn_ids, शून्य);

	वापस platक्रमm_driver_रेजिस्टर(&पूर्णांकel_vbtn_pl_driver);
पूर्ण
module_init(पूर्णांकel_vbtn_init);

अटल व्योम __निकास पूर्णांकel_vbtn_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&पूर्णांकel_vbtn_pl_driver);
पूर्ण
module_निकास(पूर्णांकel_vbtn_निकास);
