<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HID driver क्रम Holtek gaming mice
 * Copyright (c) 2013 Christian Ohm
 * Heavily inspired by various other HID drivers that adjust the report
 * descriptor.
*/

/*
 */

#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#समावेश "hid-ids.h"

/*
 * The report descriptor of some Holtek based gaming mice specअगरies an
 * excessively large number of consumer usages (2^15), which is more than
 * HID_MAX_USAGES. This prevents proper parsing of the report descriptor.
 *
 * This driver fixes the report descriptor क्रम:
 * - USB ID 04d9:a067, sold as Sharkoon Drakonia and Perixx MX-2000
 * - USB ID 04d9:a04a, sold as Tracer Sniper TRM-503, NOVA Gaming Slider X200
 *   and Zalman ZM-GM1
 * - USB ID 04d9:a081, sold as SHARKOON DarkGlider Gaming mouse
 * - USB ID 04d9:a072, sold as LEETGION Hellion Gaming Mouse
 * - USB ID 04d9:a0c2, sold as ETEKCITY Scroll T-140 Gaming Mouse
 */

अटल __u8 *holtek_mouse_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber == 1) अणु
		/* Change usage maximum and logical maximum from 0x7fff to
		 * 0x2fff, so they करोn't exceed HID_MAX_USAGES */
		चयन (hdev->product) अणु
		हाल USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A067:
		हाल USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A072:
		हाल USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A0C2:
			अगर (*rsize >= 122 && rdesc[115] == 0xff && rdesc[116] == 0x7f
					&& rdesc[120] == 0xff && rdesc[121] == 0x7f) अणु
				hid_info(hdev, "Fixing up report descriptor\n");
				rdesc[116] = rdesc[121] = 0x2f;
			पूर्ण
			अवरोध;
		हाल USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A04A:
		हाल USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A070:
		हाल USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A081:
			अगर (*rsize >= 113 && rdesc[106] == 0xff && rdesc[107] == 0x7f
					&& rdesc[111] == 0xff && rdesc[112] == 0x7f) अणु
				hid_info(hdev, "Fixing up report descriptor\n");
				rdesc[107] = rdesc[112] = 0x2f;
			पूर्ण
			अवरोध;
		पूर्ण

	पूर्ण
	वापस rdesc;
पूर्ण

अटल स्थिर काष्ठा hid_device_id holtek_mouse_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_HOLTEK_ALT,
			USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A067) पूर्ण,
        अणु HID_USB_DEVICE(USB_VENDOR_ID_HOLTEK_ALT,
			USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A070) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_HOLTEK_ALT,
			USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A04A) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_HOLTEK_ALT,
			USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A072) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_HOLTEK_ALT,
			USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A081) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_HOLTEK_ALT,
			USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A0C2) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, holtek_mouse_devices);

अटल काष्ठा hid_driver holtek_mouse_driver = अणु
	.name = "holtek_mouse",
	.id_table = holtek_mouse_devices,
	.report_fixup = holtek_mouse_report_fixup,
पूर्ण;

module_hid_driver(holtek_mouse_driver);
MODULE_LICENSE("GPL");
