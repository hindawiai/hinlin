<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम TiVo Slide Bluetooth remote
 *
 *  Copyright (c) 2011 Jarod Wilson <jarod@redhat.com>
 *  based on the hid-topseed driver, which is in turn, based on hid-cherry...
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#घोषणा HID_UP_TIVOVENDOR	0xffff0000
#घोषणा tivo_map_key_clear(c)	hid_map_usage_clear(hi, usage, bit, max, \
					EV_KEY, (c))

अटल पूर्णांक tivo_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	चयन (usage->hid & HID_USAGE_PAGE) अणु
	हाल HID_UP_TIVOVENDOR:
		चयन (usage->hid & HID_USAGE) अणु
		/* TiVo button */
		हाल 0x3d: tivo_map_key_clear(KEY_MEDIA);	अवरोध;
		/* Live TV */
		हाल 0x3e: tivo_map_key_clear(KEY_TV);		अवरोध;
		/* Red thumbs करोwn */
		हाल 0x41: tivo_map_key_clear(KEY_KPMINUS);	अवरोध;
		/* Green thumbs up */
		हाल 0x42: tivo_map_key_clear(KEY_KPPLUS);	अवरोध;
		शेष:
			वापस 0;
		पूर्ण
		अवरोध;
	हाल HID_UP_CONSUMER:
		चयन (usage->hid & HID_USAGE) अणु
		/* Enter/Last (शेष mapping: KEY_LAST) */
		हाल 0x083: tivo_map_key_clear(KEY_ENTER);	अवरोध;
		/* Info (शेष mapping: KEY_PROPS) */
		हाल 0x209: tivo_map_key_clear(KEY_INFO);	अवरोध;
		शेष:
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	/* This means we found a matching mapping here, अन्यथा, look in the
	 * standard hid mappings in hid-input.c */
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा hid_device_id tivo_devices[] = अणु
	/* TiVo Slide Bluetooth remote, pairs with a Broadcom करोngle */
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_TIVO, USB_DEVICE_ID_TIVO_SLIDE_BT) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_TIVO, USB_DEVICE_ID_TIVO_SLIDE) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_TIVO, USB_DEVICE_ID_TIVO_SLIDE_PRO) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, tivo_devices);

अटल काष्ठा hid_driver tivo_driver = अणु
	.name = "tivo_slide",
	.id_table = tivo_devices,
	.input_mapping = tivo_input_mapping,
पूर्ण;
module_hid_driver(tivo_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jarod Wilson <jarod@redhat.com>");
