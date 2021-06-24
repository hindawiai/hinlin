<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम some gyration "special" devices
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2008 Jiri Slaby
 *  Copyright (c) 2006-2008 Jiri Kosina
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#घोषणा gy_map_key_clear(c)	hid_map_usage_clear(hi, usage, bit, max, \
					EV_KEY, (c))
अटल पूर्णांक gyration_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_LOGIVENDOR)
		वापस 0;

	set_bit(EV_REP, hi->input->evbit);
	चयन (usage->hid & HID_USAGE) अणु
	/* Reported on Gyration MCE Remote */
	हाल 0x00d: gy_map_key_clear(KEY_HOME);		अवरोध;
	हाल 0x024: gy_map_key_clear(KEY_DVD);		अवरोध;
	हाल 0x025: gy_map_key_clear(KEY_PVR);		अवरोध;
	हाल 0x046: gy_map_key_clear(KEY_MEDIA);	अवरोध;
	हाल 0x047: gy_map_key_clear(KEY_MP3);		अवरोध;
	हाल 0x048: gy_map_key_clear(KEY_MEDIA);	अवरोध;
	हाल 0x049: gy_map_key_clear(KEY_CAMERA);	अवरोध;
	हाल 0x04a: gy_map_key_clear(KEY_VIDEO);	अवरोध;
	हाल 0x05a: gy_map_key_clear(KEY_TEXT);		अवरोध;
	हाल 0x05b: gy_map_key_clear(KEY_RED);		अवरोध;
	हाल 0x05c: gy_map_key_clear(KEY_GREEN);	अवरोध;
	हाल 0x05d: gy_map_key_clear(KEY_YELLOW);	अवरोध;
	हाल 0x05e: gy_map_key_clear(KEY_BLUE);		अवरोध;

	शेष:
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक gyration_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु

	अगर (!(hdev->claimed & HID_CLAIMED_INPUT) || !field->hidinput)
		वापस 0;

	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_GENDESK &&
			(usage->hid & 0xff) == 0x82) अणु
		काष्ठा input_dev *input = field->hidinput->input;
		input_event(input, usage->type, usage->code, 1);
		input_sync(input);
		input_event(input, usage->type, usage->code, 0);
		input_sync(input);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id gyration_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_GYRATION, USB_DEVICE_ID_GYRATION_REMOTE) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_GYRATION, USB_DEVICE_ID_GYRATION_REMOTE_2) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_GYRATION, USB_DEVICE_ID_GYRATION_REMOTE_3) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, gyration_devices);

अटल काष्ठा hid_driver gyration_driver = अणु
	.name = "gyration",
	.id_table = gyration_devices,
	.input_mapping = gyration_input_mapping,
	.event = gyration_event,
पूर्ण;
module_hid_driver(gyration_driver);

MODULE_LICENSE("GPL");
