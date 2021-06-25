<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Eee PC WMI hotkey driver
 *
 * Copyright(C) 2010 Intel Corporation.
 * Copyright(C) 2010-2011 Corentin Chary <corentin.अक्षरy@gmail.com>
 *
 * Portions based on wistron_btns.c:
 * Copyright (C) 2005 Miloslav Trmac <mitr@volny.cz>
 * Copyright (C) 2005 Bernhard Rosenkraenzer <bero@arklinux.org>
 * Copyright (C) 2005 Dmitry Torokhov <dtor@mail.ru>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/dmi.h>
#समावेश <linux/fb.h>
#समावेश <linux/acpi.h>

#समावेश "asus-wmi.h"

#घोषणा	EEEPC_WMI_खाता	"eeepc-wmi"

MODULE_AUTHOR("Corentin Chary <corentin.chary@gmail.com>");
MODULE_DESCRIPTION("Eee PC WMI Hotkey Driver");
MODULE_LICENSE("GPL");

#घोषणा EEEPC_ACPI_HID		"ASUS010" /* old _HID used in eeepc-laptop */

#घोषणा EEEPC_WMI_EVENT_GUID	"ABBC0F72-8EA1-11D1-00A0-C90629100000"

MODULE_ALIAS("wmi:"EEEPC_WMI_EVENT_GUID);

अटल bool hotplug_wireless;

module_param(hotplug_wireless, bool, 0444);
MODULE_PARM_DESC(hotplug_wireless,
		 "Enable hotplug for wireless device. "
		 "If your laptop needs that, please report to "
		 "acpi4asus-user@lists.sourceforge.net.");

/* Values क्रम T101MT "Home" key */
#घोषणा HOME_PRESS	0xe4
#घोषणा HOME_HOLD	0xea
#घोषणा HOME_RELEASE	0xe5

अटल स्थिर काष्ठा key_entry eeepc_wmi_keymap[] = अणु
	अणु KE_KEY, ASUS_WMI_BRN_DOWN, अणु KEY_BRIGHTNESSDOWN पूर्ण पूर्ण,
	अणु KE_KEY, ASUS_WMI_BRN_UP, अणु KEY_BRIGHTNESSUP पूर्ण पूर्ण,
	/* Sleep alपढ़ोy handled via generic ACPI code */
	अणु KE_KEY, 0x30, अणु KEY_VOLUMEUP पूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,
	अणु KE_KEY, 0x32, अणु KEY_MUTE पूर्ण पूर्ण,
	अणु KE_KEY, 0x5c, अणु KEY_F15 पूर्ण पूर्ण, /* Power Gear key */
	अणु KE_KEY, 0x5d, अणु KEY_WLAN पूर्ण पूर्ण,
	अणु KE_KEY, 0x6b, अणु KEY_TOUCHPAD_TOGGLE पूर्ण पूर्ण, /* Toggle Touchpad */
	अणु KE_KEY, 0x82, अणु KEY_CAMERA पूर्ण पूर्ण,
	अणु KE_KEY, 0x83, अणु KEY_CAMERA_ZOOMIN पूर्ण पूर्ण,
	अणु KE_KEY, 0x88, अणु KEY_WLAN पूर्ण पूर्ण,
	अणु KE_KEY, 0xbd, अणु KEY_CAMERA पूर्ण पूर्ण,
	अणु KE_KEY, 0xcc, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण,
	अणु KE_KEY, 0xe0, अणु KEY_PROG1 पूर्ण पूर्ण, /* Task Manager */
	अणु KE_KEY, 0xe1, अणु KEY_F14 पूर्ण पूर्ण, /* Change Resolution */
	अणु KE_KEY, HOME_PRESS, अणु KEY_CONFIG पूर्ण पूर्ण, /* Home/Express gate key */
	अणु KE_KEY, 0xe8, अणु KEY_SCREENLOCK पूर्ण पूर्ण,
	अणु KE_KEY, 0xe9, अणु KEY_DISPLAYTOGGLE पूर्ण पूर्ण,
	अणु KE_KEY, 0xeb, अणु KEY_CAMERA_ZOOMOUT पूर्ण पूर्ण,
	अणु KE_KEY, 0xec, अणु KEY_CAMERA_UP पूर्ण पूर्ण,
	अणु KE_KEY, 0xed, अणु KEY_CAMERA_DOWN पूर्ण पूर्ण,
	अणु KE_KEY, 0xee, अणु KEY_CAMERA_LEFT पूर्ण पूर्ण,
	अणु KE_KEY, 0xef, अणु KEY_CAMERA_RIGHT पूर्ण पूर्ण,
	अणु KE_KEY, 0xf3, अणु KEY_MENU पूर्ण पूर्ण,
	अणु KE_KEY, 0xf5, अणु KEY_HOMEPAGE पूर्ण पूर्ण,
	अणु KE_KEY, 0xf6, अणु KEY_ESC पूर्ण पूर्ण,
	अणु KE_END, 0पूर्ण,
पूर्ण;

अटल काष्ठा quirk_entry quirk_asus_unknown = अणु
पूर्ण;

अटल काष्ठा quirk_entry quirk_asus_1000h = अणु
	.hotplug_wireless = true,
पूर्ण;

अटल काष्ठा quirk_entry quirk_asus_et2012_type1 = अणु
	.store_backlight_घातer = true,
पूर्ण;

अटल काष्ठा quirk_entry quirk_asus_et2012_type3 = अणु
	.scalar_panel_brightness = true,
	.store_backlight_घातer = true,
पूर्ण;

अटल काष्ठा quirk_entry quirk_asus_x101ch = अणु
	/* We need this when ACPI function करोesn't करो this well */
	.wmi_backlight_घातer = true,
पूर्ण;

अटल काष्ठा quirk_entry *quirks;

अटल व्योम et2012_quirks(व्योम)
अणु
	स्थिर काष्ठा dmi_device *dev = शून्य;
	अक्षर oemstring[30];

	जबतक ((dev = dmi_find_device(DMI_DEV_TYPE_OEM_STRING, शून्य, dev))) अणु
		अगर (माला_पूछो(dev->name, "AEMS%24c", oemstring) == 1) अणु
			अगर (oemstring[18] == '1')
				quirks = &quirk_asus_et2012_type1;
			अन्यथा अगर (oemstring[18] == '3')
				quirks = &quirk_asus_et2012_type3;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dmi_matched(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	अक्षर *model;

	quirks = dmi->driver_data;

	model = (अक्षर *)dmi->matches[1].substr;
	अगर (unlikely(म_भेदन(model, "ET2012", 6) == 0))
		et2012_quirks();

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id asus_quirks[] = अणु
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK Computer INC. 1000H",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "1000H"),
		पूर्ण,
		.driver_data = &quirk_asus_1000h,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK Computer INC. ET2012E/I",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "ET2012"),
		पूर्ण,
		.driver_data = &quirk_asus_unknown,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK Computer INC. X101CH",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X101CH"),
		पूर्ण,
		.driver_data = &quirk_asus_x101ch,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK Computer INC. 1015CX",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "1015CX"),
		पूर्ण,
		.driver_data = &quirk_asus_x101ch,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम eeepc_wmi_key_filter(काष्ठा asus_wmi_driver *asus_wmi, पूर्णांक *code,
				 अचिन्हित पूर्णांक *value, bool *स्वतःrelease)
अणु
	चयन (*code) अणु
	हाल HOME_PRESS:
		*value = 1;
		*स्वतःrelease = 0;
		अवरोध;
	हाल HOME_HOLD:
		*code = ASUS_WMI_KEY_IGNORE;
		अवरोध;
	हाल HOME_RELEASE:
		*code = HOME_PRESS;
		*value = 0;
		*स्वतःrelease = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक eeepc_wmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (acpi_dev_found(EEEPC_ACPI_HID)) अणु
		pr_warn("Found legacy ATKD device (%s)\n", EEEPC_ACPI_HID);
		pr_warn("WMI device present, but legacy ATKD device is also "
			"present and enabled\n");
		pr_warn("You probably booted with acpi_osi=\"Linux\" or "
			"acpi_osi=\"!Windows 2009\"\n");
		pr_warn("Can't load eeepc-wmi, use default acpi_osi "
			"(preferred) or eeepc-laptop\n");
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम eeepc_wmi_quirks(काष्ठा asus_wmi_driver *driver)
अणु
	quirks = &quirk_asus_unknown;
	quirks->hotplug_wireless = hotplug_wireless;

	dmi_check_प्रणाली(asus_quirks);

	driver->quirks = quirks;
	driver->quirks->wapf = -1;
	driver->panel_घातer = FB_BLANK_UNBLANK;
पूर्ण

अटल काष्ठा asus_wmi_driver asus_wmi_driver = अणु
	.name = EEEPC_WMI_खाता,
	.owner = THIS_MODULE,
	.event_guid = EEEPC_WMI_EVENT_GUID,
	.keymap = eeepc_wmi_keymap,
	.input_name = "Eee PC WMI hotkeys",
	.input_phys = EEEPC_WMI_खाता "/input0",
	.key_filter = eeepc_wmi_key_filter,
	.probe = eeepc_wmi_probe,
	.detect_quirks = eeepc_wmi_quirks,
पूर्ण;


अटल पूर्णांक __init eeepc_wmi_init(व्योम)
अणु
	वापस asus_wmi_रेजिस्टर_driver(&asus_wmi_driver);
पूर्ण

अटल व्योम __निकास eeepc_wmi_निकास(व्योम)
अणु
	asus_wmi_unरेजिस्टर_driver(&asus_wmi_driver);
पूर्ण

module_init(eeepc_wmi_init);
module_निकास(eeepc_wmi_निकास);
