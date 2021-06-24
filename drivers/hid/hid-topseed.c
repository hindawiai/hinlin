<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम TopSeed Cyberlink remote
 *
 *  Copyright (c) 2008 Lev Babiev
 *  based on hid-cherry driver
 *
 *  Modअगरied to also support BTC "Emprex 3009URF III Vista MCE Remote" by
 *  Wayne Thomas 2010.
 *
 *  Modअगरied to support Conceptronic CLLRCMCE by
 *  Kees Bakker 2010.
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
	हाल 0x00c: ts_map_key_clear(KEY_WLAN);		अवरोध;
	हाल 0x00d: ts_map_key_clear(KEY_MEDIA);	अवरोध;
	हाल 0x010: ts_map_key_clear(KEY_ZOOM);		अवरोध;
	हाल 0x024: ts_map_key_clear(KEY_MENU);		अवरोध;
	हाल 0x025: ts_map_key_clear(KEY_TV);		अवरोध;
	हाल 0x027: ts_map_key_clear(KEY_MODE);		अवरोध;
	हाल 0x031: ts_map_key_clear(KEY_AUDIO);	अवरोध;
	हाल 0x032: ts_map_key_clear(KEY_TEXT);		अवरोध;
	हाल 0x033: ts_map_key_clear(KEY_CHANNEL);	अवरोध;
	हाल 0x047: ts_map_key_clear(KEY_MP3);		अवरोध;
	हाल 0x048: ts_map_key_clear(KEY_TV2);		अवरोध;
	हाल 0x049: ts_map_key_clear(KEY_CAMERA);	अवरोध;
	हाल 0x04a: ts_map_key_clear(KEY_VIDEO);	अवरोध;
	हाल 0x04b: ts_map_key_clear(KEY_ANGLE);	अवरोध;
	हाल 0x04c: ts_map_key_clear(KEY_LANGUAGE);	अवरोध;
	हाल 0x04d: ts_map_key_clear(KEY_SUBTITLE);	अवरोध;
	हाल 0x050: ts_map_key_clear(KEY_RADIO);	अवरोध;
	हाल 0x05a: ts_map_key_clear(KEY_TEXT);		अवरोध;
	हाल 0x05b: ts_map_key_clear(KEY_RED);		अवरोध;
	हाल 0x05c: ts_map_key_clear(KEY_GREEN);	अवरोध;
	हाल 0x05d: ts_map_key_clear(KEY_YELLOW);	अवरोध;
	हाल 0x05e: ts_map_key_clear(KEY_BLUE);		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा hid_device_id ts_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_TOPSEED, USB_DEVICE_ID_TOPSEED_CYBERLINK) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_BTC, USB_DEVICE_ID_BTC_EMPREX_REMOTE) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_BTC, USB_DEVICE_ID_BTC_EMPREX_REMOTE_2) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_TOPSEED2, USB_DEVICE_ID_TOPSEED2_RF_COMBO) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CHICONY, USB_DEVICE_ID_CHICONY_WIRELESS) पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_CHICONY, USB_DEVICE_ID_CHICONY_TOSHIBA_WT10A) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, ts_devices);

अटल काष्ठा hid_driver ts_driver = अणु
	.name = "topseed",
	.id_table = ts_devices,
	.input_mapping = ts_input_mapping,
पूर्ण;
module_hid_driver(ts_driver);

MODULE_LICENSE("GPL");
