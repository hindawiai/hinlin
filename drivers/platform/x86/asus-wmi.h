<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Asus PC WMI hotkey driver
 *
 * Copyright(C) 2010 Intel Corporation.
 * Copyright(C) 2010-2011 Corentin Chary <corentin.अक्षरy@gmail.com>
 *
 * Portions based on wistron_btns.c:
 * Copyright (C) 2005 Miloslav Trmac <mitr@volny.cz>
 * Copyright (C) 2005 Bernhard Rosenkraenzer <bero@arklinux.org>
 * Copyright (C) 2005 Dmitry Torokhov <dtor@mail.ru>
 */

#अगर_अघोषित _ASUS_WMI_H_
#घोषणा _ASUS_WMI_H_

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i8042.h>

#घोषणा ASUS_WMI_KEY_IGNORE (-1)
#घोषणा ASUS_WMI_BRN_DOWN	0x20
#घोषणा ASUS_WMI_BRN_UP		0x2f

काष्ठा module;
काष्ठा key_entry;
काष्ठा asus_wmi;

काष्ठा quirk_entry अणु
	bool hotplug_wireless;
	bool scalar_panel_brightness;
	bool store_backlight_घातer;
	bool wmi_backlight_घातer;
	bool wmi_backlight_native;
	bool wmi_backlight_set_devstate;
	bool wmi_क्रमce_als_set;
	bool use_kbd_करोck_devid;
	bool use_lid_flip_devid;
	पूर्णांक wapf;
	/*
	 * For machines with AMD graphic chips, it will send out WMI event
	 * and ACPI पूर्णांकerrupt at the same समय जबतक hitting the hotkey.
	 * To simplअगरy the problem, we just have to ignore the WMI event,
	 * and let the ACPI पूर्णांकerrupt to send out the key event.
	 */
	पूर्णांक no_display_toggle;
	u32 xusb2pr;

	bool (*i8042_filter)(अचिन्हित अक्षर data, अचिन्हित अक्षर str,
			     काष्ठा serio *serio);
पूर्ण;

काष्ठा asus_wmi_driver अणु
	पूर्णांक			brightness;
	पूर्णांक			panel_घातer;
	पूर्णांक			wlan_ctrl_by_user;

	स्थिर अक्षर		*name;
	काष्ठा module		*owner;

	स्थिर अक्षर		*event_guid;

	स्थिर काष्ठा key_entry	*keymap;
	स्थिर अक्षर		*input_name;
	स्थिर अक्षर		*input_phys;
	काष्ठा quirk_entry	*quirks;
	/* Returns new code, value, and स्वतःrelease values in arguments.
	 * Return ASUS_WMI_KEY_IGNORE in code अगर event should be ignored. */
	व्योम (*key_filter) (काष्ठा asus_wmi_driver *driver, पूर्णांक *code,
			    अचिन्हित पूर्णांक *value, bool *स्वतःrelease);

	पूर्णांक (*probe) (काष्ठा platक्रमm_device *device);
	व्योम (*detect_quirks) (काष्ठा asus_wmi_driver *driver);

	काष्ठा platक्रमm_driver	platक्रमm_driver;
	काष्ठा platक्रमm_device *platक्रमm_device;
पूर्ण;

पूर्णांक asus_wmi_रेजिस्टर_driver(काष्ठा asus_wmi_driver *driver);
व्योम asus_wmi_unरेजिस्टर_driver(काष्ठा asus_wmi_driver *driver);

#पूर्ण_अगर /* !_ASUS_WMI_H_ */
