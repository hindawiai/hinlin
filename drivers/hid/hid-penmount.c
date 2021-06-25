<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम PenMount touchscreens
 *
 *  Copyright (c) 2014 Christian Gmeiner <christian.gmeiner <at> gmail.com>
 *
 *  based on hid-penmount copyrighted by
 *    PenMount Touch Solutions <penmount <at> seed.net.tw>
 */

/*
 */

#समावेश <linux/module.h>
#समावेश <linux/hid.h>
#समावेश "hid-ids.h"

अटल पूर्णांक penmount_input_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hi, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON) अणु
		अगर (((usage->hid - 1) & HID_USAGE) == 0) अणु
			hid_map_usage(hi, usage, bit, max, EV_KEY, BTN_TOUCH);
			वापस 1;
		पूर्ण अन्यथा अणु
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id penmount_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_PENMOUNT, USB_DEVICE_ID_PENMOUNT_6000) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, penmount_devices);

अटल काष्ठा hid_driver penmount_driver = अणु
	.name = "hid-penmount",
	.id_table = penmount_devices,
	.input_mapping = penmount_input_mapping,
पूर्ण;

module_hid_driver(penmount_driver);

MODULE_AUTHOR("Christian Gmeiner <christian.gmeiner@gmail.com>");
MODULE_DESCRIPTION("PenMount HID TouchScreen driver");
MODULE_LICENSE("GPL");
