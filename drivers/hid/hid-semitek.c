<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम Semitek keyboards
 *
 *  Copyright (c) 2021 Benjamin Moody
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

अटल __u8 *semitek_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
                                  अचिन्हित पूर्णांक *rsize)
अणु
	/* In the report descriptor क्रम पूर्णांकerface 2, fix the incorrect
	   description of report ID 0x04 (the report contains a
	   biपंचांगask, not an array of keycodes.) */
	अगर (*rsize == 0xcb && rdesc[0x83] == 0x81 && rdesc[0x84] == 0x00) अणु
		hid_info(hdev, "fixing up Semitek report descriptor\n");
		rdesc[0x84] = 0x02;
	पूर्ण
	वापस rdesc;
पूर्ण

अटल स्थिर काष्ठा hid_device_id semitek_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SEMITEK, USB_DEVICE_ID_SEMITEK_KEYBOARD) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, semitek_devices);

अटल काष्ठा hid_driver semitek_driver = अणु
	.name = "semitek",
	.id_table = semitek_devices,
	.report_fixup = semitek_report_fixup,
पूर्ण;
module_hid_driver(semitek_driver);

MODULE_LICENSE("GPL");
