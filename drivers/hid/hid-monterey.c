<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम some monterey "special" devices
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

अटल __u8 *mr_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	अगर (*rsize >= 31 && rdesc[29] == 0x05 && rdesc[30] == 0x09) अणु
		hid_info(hdev, "fixing up button/consumer in HID report descriptor\n");
		rdesc[30] = 0x0c;
	पूर्ण
	वापस rdesc;
पूर्ण

#घोषणा mr_map_key_clear(c)	hid_map_usage_clear(hi, usage, bit, max, \
					EV_KEY, (c))
अटल पूर्णांक mr_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_CONSUMER)
		वापस 0;

	चयन (usage->hid & HID_USAGE) अणु
	हाल 0x156: mr_map_key_clear(KEY_WORDPROCESSOR);	अवरोध;
	हाल 0x157: mr_map_key_clear(KEY_SPREADSHEET);		अवरोध;
	हाल 0x158: mr_map_key_clear(KEY_PRESENTATION);		अवरोध;
	हाल 0x15c: mr_map_key_clear(KEY_STOP);			अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा hid_device_id mr_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MONTEREY, USB_DEVICE_ID_GENIUS_KB29E) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, mr_devices);

अटल काष्ठा hid_driver mr_driver = अणु
	.name = "monterey",
	.id_table = mr_devices,
	.report_fixup = mr_report_fixup,
	.input_mapping = mr_input_mapping,
पूर्ण;
module_hid_driver(mr_driver);

MODULE_LICENSE("GPL");
