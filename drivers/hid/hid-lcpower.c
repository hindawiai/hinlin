<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम LC Power Model RC1000MCE
 *
 *  Copyright (c) 2011 Chris Schlund 
 *  based on hid-topseed module
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#घोषणा ts_map_key_clear(c)	hid_map_usage_clear(hi, usage, bit, max, \
					EV_KEY, (c))
अटल पूर्णांक ts_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_LOGIVENDOR)
		वापस 0;

	चयन (usage->hid & HID_USAGE) अणु
        हाल 0x046: ts_map_key_clear(KEY_YELLOW);         अवरोध;
        हाल 0x047: ts_map_key_clear(KEY_GREEN);          अवरोध;
        हाल 0x049: ts_map_key_clear(KEY_BLUE);           अवरोध;
        हाल 0x04a: ts_map_key_clear(KEY_RED);		  अवरोध;
        हाल 0x00d: ts_map_key_clear(KEY_HOME);           अवरोध;
        हाल 0x025: ts_map_key_clear(KEY_TV);             अवरोध;
        हाल 0x048: ts_map_key_clear(KEY_VCR);            अवरोध;
        हाल 0x024: ts_map_key_clear(KEY_MENU);           अवरोध;
        शेष:
        वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा hid_device_id ts_devices[] = अणु
	अणु HID_USB_DEVICE( USB_VENDOR_ID_LCPOWER, USB_DEVICE_ID_LCPOWER_LC1000) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, ts_devices);

अटल काष्ठा hid_driver ts_driver = अणु
	.name = "LC RC1000MCE",
	.id_table = ts_devices,
	.input_mapping = ts_input_mapping,
पूर्ण;
module_hid_driver(ts_driver);

MODULE_LICENSE("GPL");
