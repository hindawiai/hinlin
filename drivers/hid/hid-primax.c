<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID driver क्रम primax and similar keyboards with in-band modअगरiers
 *
 * Copyright 2011 Google Inc. All Rights Reserved
 *
 * Author:
 *	Terry Lambert <tlambert@google.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

अटल पूर्णांक px_raw_event(काष्ठा hid_device *hid, काष्ठा hid_report *report,
	 u8 *data, पूर्णांक size)
अणु
	पूर्णांक idx = size;

	चयन (report->id) अणु
	हाल 0:		/* keyboard input */
		/*
		 * Convert in-band modअगरier key values पूर्णांकo out of band
		 * modअगरier bits and pull the key strokes from the report.
		 * Thus a report data set which looked like:
		 *
		 * [00][00][E0][30][00][00][00][00]
		 * (no modअगरier bits + "Left Shift" key + "1" key)
		 *
		 * Would be converted to:
		 *
		 * [01][00][00][30][00][00][00][00]
		 * (Left Shअगरt modअगरier bit + "1" key)
		 *
		 * As दीर्घ as it's in the size range, the upper level
		 * drivers करोn't particularly care अगर there are in-band
		 * 0-valued keys, so they करोn't stop parsing.
		 */
		जबतक (--idx > 1) अणु
			अगर (data[idx] < 0xE0 || data[idx] > 0xE7)
				जारी;
			data[0] |= (1 << (data[idx] - 0xE0));
			data[idx] = 0;
		पूर्ण
		hid_report_raw_event(hid, HID_INPUT_REPORT, data, size, 0);
		वापस 1;

	शेष:	/* unknown report */
		/* Unknown report type; pass upstream */
		hid_info(hid, "unknown report type %d\n", report->id);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id px_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_PRIMAX, USB_DEVICE_ID_PRIMAX_KEYBOARD) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, px_devices);

अटल काष्ठा hid_driver px_driver = अणु
	.name = "primax",
	.id_table = px_devices,
	.raw_event = px_raw_event,
पूर्ण;
module_hid_driver(px_driver);

MODULE_AUTHOR("Terry Lambert <tlambert@google.com>");
MODULE_LICENSE("GPL");
