<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम some cherry "special" devices
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2006-2007 Jiri Kosina
 *  Copyright (c) 2008 Jiri Slaby
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

/*
 * Cherry Cymotion keyboard have an invalid HID report descriptor,
 * that needs fixing beक्रमe we can parse it.
 */
अटल __u8 *ch_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	अगर (*rsize >= 18 && rdesc[11] == 0x3c && rdesc[12] == 0x02) अणु
		hid_info(hdev, "fixing up Cherry Cymotion report descriptor\n");
		rdesc[11] = rdesc[16] = 0xff;
		rdesc[12] = rdesc[17] = 0x03;
	पूर्ण
	वापस rdesc;
पूर्ण

#घोषणा ch_map_key_clear(c)	hid_map_usage_clear(hi, usage, bit, max, \
					EV_KEY, (c))
अटल पूर्णांक ch_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_CONSUMER)
		वापस 0;

	चयन (usage->hid & HID_USAGE) अणु
	हाल 0x301: ch_map_key_clear(KEY_PROG1);	अवरोध;
	हाल 0x302: ch_map_key_clear(KEY_PROG2);	अवरोध;
	हाल 0x303: ch_map_key_clear(KEY_PROG3);	अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा hid_device_id ch_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CHERRY, USB_DEVICE_ID_CHERRY_CYMOTION) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CHERRY, USB_DEVICE_ID_CHERRY_CYMOTION_SOLAR) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, ch_devices);

अटल काष्ठा hid_driver ch_driver = अणु
	.name = "cherry",
	.id_table = ch_devices,
	.report_fixup = ch_report_fixup,
	.input_mapping = ch_input_mapping,
पूर्ण;
module_hid_driver(ch_driver);

MODULE_LICENSE("GPL");
