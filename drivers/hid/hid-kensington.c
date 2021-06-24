<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम Kensigton Slimblade Trackball
 *
 *  Copyright (c) 2009 Jiri Kosina
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#घोषणा ks_map_key(c)	hid_map_usage(hi, usage, bit, max, EV_KEY, (c))

अटल पूर्णांक ks_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_MSVENDOR)
		वापस 0;

	चयन (usage->hid & HID_USAGE) अणु
	हाल 0x01: ks_map_key(BTN_MIDDLE);	अवरोध;
	हाल 0x02: ks_map_key(BTN_SIDE);	अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा hid_device_id ks_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_KENSINGTON, USB_DEVICE_ID_KS_SLIMBLADE) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, ks_devices);

अटल काष्ठा hid_driver ks_driver = अणु
	.name = "kensington",
	.id_table = ks_devices,
	.input_mapping = ks_input_mapping,
पूर्ण;
module_hid_driver(ks_driver);

MODULE_LICENSE("GPL");
