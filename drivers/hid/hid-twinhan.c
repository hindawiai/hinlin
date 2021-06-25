<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID driver क्रम TwinHan IR remote control
 *
 * Based on hid-gyration.c
 *
 * Copyright (c) 2009 Bruno Prथऊmont <bonbons@linux-vserver.org>
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

/*	Remote control key layout + listing:
 *
 * 	Full Screen                              Power
 *	KEY_SCREEN                          KEY_POWER2
 *
 *	1                     2                      3
 *	KEY_NUMERIC_1   KEY_NUMERIC_2    KEY_NUMERIC_3
 *
 *	4                     5                      6
 *	KEY_NUMERIC_4   KEY_NUMERIC_5    KEY_NUMERIC_6
 *
 *	7                     8                      9
 *	KEY_NUMERIC_7   KEY_NUMERIC_8    KEY_NUMERIC_9
 *
 *	REC                   0               Favorite
 *	KEY_RECORD      KEY_NUMERIC_0    KEY_FAVORITES
 *
 *	Rewind                                 Forward
 *	KEY_REWIND           CH+           KEY_FORWARD
 *	               KEY_CHANNELUP
 *
 *	VOL-                  >                   VOL+
 *	KEY_VOLUMEDOWN    KEY_PLAY        KEY_VOLUMEUP
 *
 *	                     CH-
 *	              KEY_CHANNELDOWN
 *	Recall                                    Stop
 *	KEY_RESTART                           KEY_STOP
 *
 *	Timeshअगरt/Pause     Mute                Cancel
 *	KEY_PAUSE         KEY_MUTE          KEY_CANCEL
 *
 *	Capture            Preview                 EPG
 *	KEY_PRINT        KEY_PROGRAM           KEY_EPG
 *
 *	Record List          Tab              Teletext
 *	KEY_LIST            KEY_TAB           KEY_TEXT
 */

#घोषणा th_map_key_clear(c)	hid_map_usage_clear(hi, usage, bit, max, \
					EV_KEY, (c))
अटल पूर्णांक twinhan_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_KEYBOARD)
		वापस 0;

	चयन (usage->hid & HID_USAGE) अणु
	/* Map all keys from Twinhan Remote */
	हाल 0x004: th_map_key_clear(KEY_TEXT);         अवरोध;
	हाल 0x006: th_map_key_clear(KEY_RESTART);      अवरोध;
	हाल 0x008: th_map_key_clear(KEY_EPG);          अवरोध;
	हाल 0x00c: th_map_key_clear(KEY_REWIND);       अवरोध;
	हाल 0x00e: th_map_key_clear(KEY_PROGRAM);      अवरोध;
	हाल 0x00f: th_map_key_clear(KEY_LIST);         अवरोध;
	हाल 0x010: th_map_key_clear(KEY_MUTE);         अवरोध;
	हाल 0x011: th_map_key_clear(KEY_FORWARD);      अवरोध;
	हाल 0x013: th_map_key_clear(KEY_PRINT);        अवरोध;
	हाल 0x017: th_map_key_clear(KEY_PAUSE);        अवरोध;
	हाल 0x019: th_map_key_clear(KEY_FAVORITES);    अवरोध;
	हाल 0x01d: th_map_key_clear(KEY_SCREEN);       अवरोध;
	हाल 0x01e: th_map_key_clear(KEY_NUMERIC_1);    अवरोध;
	हाल 0x01f: th_map_key_clear(KEY_NUMERIC_2);    अवरोध;
	हाल 0x020: th_map_key_clear(KEY_NUMERIC_3);    अवरोध;
	हाल 0x021: th_map_key_clear(KEY_NUMERIC_4);    अवरोध;
	हाल 0x022: th_map_key_clear(KEY_NUMERIC_5);    अवरोध;
	हाल 0x023: th_map_key_clear(KEY_NUMERIC_6);    अवरोध;
	हाल 0x024: th_map_key_clear(KEY_NUMERIC_7);    अवरोध;
	हाल 0x025: th_map_key_clear(KEY_NUMERIC_8);    अवरोध;
	हाल 0x026: th_map_key_clear(KEY_NUMERIC_9);    अवरोध;
	हाल 0x027: th_map_key_clear(KEY_NUMERIC_0);    अवरोध;
	हाल 0x028: th_map_key_clear(KEY_PLAY);         अवरोध;
	हाल 0x029: th_map_key_clear(KEY_CANCEL);       अवरोध;
	हाल 0x02b: th_map_key_clear(KEY_TAB);          अवरोध;
	/* Power       = 0x0e0 + 0x0e1 + 0x0e2 + 0x03f */
	हाल 0x03f: th_map_key_clear(KEY_POWER2);       अवरोध;
	हाल 0x04a: th_map_key_clear(KEY_RECORD);       अवरोध;
	हाल 0x04b: th_map_key_clear(KEY_CHANNELUP);    अवरोध;
	हाल 0x04d: th_map_key_clear(KEY_STOP);         अवरोध;
	हाल 0x04e: th_map_key_clear(KEY_CHANNELDOWN);  अवरोध;
	/* Volume करोwn = 0x0e1 + 0x051                 */
	हाल 0x051: th_map_key_clear(KEY_VOLUMEDOWN);   अवरोध;
	/* Volume up   = 0x0e1 + 0x052                 */
	हाल 0x052: th_map_key_clear(KEY_VOLUMEUP);     अवरोध;
	/* Kill the extra keys used क्रम multi-key "power" and "volume" keys
	 * as well as continuously to release CTRL,ALT,META,... keys */
	हाल 0x0e0:
	हाल 0x0e1:
	हाल 0x0e2:
	हाल 0x0e3:
	हाल 0x0e4:
	हाल 0x0e5:
	हाल 0x0e6:
	हाल 0x0e7:
	शेष:
		वापस -1;
	पूर्ण
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा hid_device_id twinhan_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_TWINHAN, USB_DEVICE_ID_TWINHAN_IR_REMOTE) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, twinhan_devices);

अटल काष्ठा hid_driver twinhan_driver = अणु
	.name = "twinhan",
	.id_table = twinhan_devices,
	.input_mapping = twinhan_input_mapping,
पूर्ण;
module_hid_driver(twinhan_driver);

MODULE_LICENSE("GPL");
