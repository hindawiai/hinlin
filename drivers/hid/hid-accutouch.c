<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HID driver क्रम Elo Accutouch touchscreens
 *
 * Copyright (c) 2016, Collabora Ltd.
 * Copyright (c) 2016, General Electric Company
 *
 * based on hid-penmount.c
 *  Copyright (c) 2014 Christian Gmeiner <christian.gmeiner <at> gmail.com>
 */

/*
 */

#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश "hid-ids.h"

अटल पूर्णांक accutouch_input_mapping(काष्ठा hid_device *hdev,
				   काष्ठा hid_input *hi,
				   काष्ठा hid_field *field,
				   काष्ठा hid_usage *usage,
				   अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON) अणु
		hid_map_usage(hi, usage, bit, max, EV_KEY, BTN_TOUCH);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id accutouch_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ELO, USB_DEVICE_ID_ELO_ACCUTOUCH_2216) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, accutouch_devices);

अटल काष्ठा hid_driver accutouch_driver = अणु
	.name = "hid-accutouch",
	.id_table = accutouch_devices,
	.input_mapping = accutouch_input_mapping,
पूर्ण;

module_hid_driver(accutouch_driver);

MODULE_AUTHOR("Martyn Welch <martyn.welch@collabora.co.uk");
MODULE_DESCRIPTION("Elo Accutouch HID TouchScreen driver");
MODULE_LICENSE("GPL");
