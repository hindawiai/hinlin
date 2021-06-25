<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  HID driver क्रम quirky Macally devices
 *
 *  Copyright (c) 2019 Alex Henrie <alexhenrie24@gmail.com>
 */

#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

MODULE_AUTHOR("Alex Henrie <alexhenrie24@gmail.com>");
MODULE_DESCRIPTION("Macally devices");
MODULE_LICENSE("GPL");

/*
 * The Macally ikey keyboard says that its logical and usage maximums are both
 * 101, but the घातer key is 102 and the equals key is 103
 */
अटल __u8 *macally_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
				 अचिन्हित पूर्णांक *rsize)
अणु
	अगर (*rsize >= 60 && rdesc[53] == 0x65 && rdesc[59] == 0x65) अणु
		hid_info(hdev,
			"fixing up Macally ikey keyboard report descriptor\n");
		rdesc[53] = rdesc[59] = 0x67;
	पूर्ण
	वापस rdesc;
पूर्ण

अटल स्थिर काष्ठा hid_device_id macally_id_table[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SOLID_YEAR,
			 USB_DEVICE_ID_MACALLY_IKEY_KEYBOARD) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, macally_id_table);

अटल काष्ठा hid_driver macally_driver = अणु
	.name			= "macally",
	.id_table		= macally_id_table,
	.report_fixup		= macally_report_fixup,
पूर्ण;

module_hid_driver(macally_driver);
