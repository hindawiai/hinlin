<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम various devices which are apparently based on the same chipset
 *  from certain venकरोr which produces chips that contain wrong LogicalMaximum
 *  value in their HID report descriptor. Currently supported devices are:
 *
 *    Ortek PKB-1700
 *    Ortek WKB-2000
 *    iHome IMAC-A210S
 *    Skycable wireless presenter
 *
 *  Copyright (c) 2010 Johnathon Harris <jmharris@gmail.com>
 *  Copyright (c) 2011 Jiri Kosina
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

अटल __u8 *ortek_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	अगर (*rsize >= 56 && rdesc[54] == 0x25 && rdesc[55] == 0x01) अणु
		hid_info(hdev, "Fixing up logical maximum in report descriptor (Ortek)\n");
		rdesc[55] = 0x92;
	पूर्ण अन्यथा अगर (*rsize >= 54 && rdesc[52] == 0x25 && rdesc[53] == 0x01) अणु
		hid_info(hdev, "Fixing up logical maximum in report descriptor (Skycable)\n");
		rdesc[53] = 0x65;
	पूर्ण
	वापस rdesc;
पूर्ण

अटल स्थिर काष्ठा hid_device_id ortek_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ORTEK, USB_DEVICE_ID_ORTEK_PKB1700) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ORTEK, USB_DEVICE_ID_ORTEK_WKB2000) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ORTEK, USB_DEVICE_ID_ORTEK_IHOME_IMAC_A210S) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SKYCABLE, USB_DEVICE_ID_SKYCABLE_WIRELESS_PRESENTER) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, ortek_devices);

अटल काष्ठा hid_driver ortek_driver = अणु
	.name = "ortek",
	.id_table = ortek_devices,
	.report_fixup = ortek_report_fixup
पूर्ण;
module_hid_driver(ortek_driver);

MODULE_LICENSE("GPL");
