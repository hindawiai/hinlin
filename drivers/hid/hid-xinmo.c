<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम Xin-Mo devices, currently only the Dual Arcade controller.
 *  Fixes the negative axis event values (the devices sends -2) to match the
 *  logical axis minimum of the HID report descriptor (the report announces
 *  -1). It is needed because hid-input discards out of bounds values.
 *  (This module is based on "hid-saitek" and "hid-lg".)
 *
 *  Copyright (c) 2013 Olivier Scherler
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश "hid-ids.h"

/*
 * Fix negative events that are out of bounds.
 */
अटल पूर्णांक xinmo_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	चयन (usage->code) अणु
	हाल ABS_X:
	हाल ABS_Y:
	हाल ABS_Z:
	हाल ABS_RX:
		अगर (value < -1) अणु
			input_event(field->hidinput->input, usage->type,
				usage->code, -1);
			वापस 1;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id xinmo_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_XIN_MO, USB_DEVICE_ID_XIN_MO_DUAL_ARCADE) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_XIN_MO, USB_DEVICE_ID_THT_2P_ARCADE) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, xinmo_devices);

अटल काष्ठा hid_driver xinmo_driver = अणु
	.name = "xinmo",
	.id_table = xinmo_devices,
	.event = xinmo_event
पूर्ण;

module_hid_driver(xinmo_driver);
MODULE_LICENSE("GPL");
