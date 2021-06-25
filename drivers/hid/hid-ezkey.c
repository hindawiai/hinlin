<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम some ezkey "special" devices
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
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#घोषणा ez_map_rel(c)	hid_map_usage(hi, usage, bit, max, EV_REL, (c))
#घोषणा ez_map_key(c)	hid_map_usage(hi, usage, bit, max, EV_KEY, (c))

अटल पूर्णांक ez_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_CONSUMER)
		वापस 0;

	चयन (usage->hid & HID_USAGE) अणु
	हाल 0x230: ez_map_key(BTN_MOUSE);	अवरोध;
	हाल 0x231: ez_map_rel(REL_WHEEL);	अवरोध;
	/*
	 * this keyboard has a scrollwheel implemented in
	 * totally broken way. We map this usage temporarily
	 * to HWHEEL and handle it in the event quirk handler
	 */
	हाल 0x232: ez_map_rel(REL_HWHEEL);	अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक ez_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	अगर (!(hdev->claimed & HID_CLAIMED_INPUT) || !field->hidinput ||
			!usage->type)
		वापस 0;

	/* handle the temporary quirky mapping to HWHEEL */
	अगर (usage->type == EV_REL && usage->code == REL_HWHEEL) अणु
		काष्ठा input_dev *input = field->hidinput->input;
		input_event(input, usage->type, REL_WHEEL, -value);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id ez_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_EZKEY, USB_DEVICE_ID_BTC_8193) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, ez_devices);

अटल काष्ठा hid_driver ez_driver = अणु
	.name = "ezkey",
	.id_table = ez_devices,
	.input_mapping = ez_input_mapping,
	.event = ez_event,
पूर्ण;
module_hid_driver(ez_driver);

MODULE_LICENSE("GPL");
