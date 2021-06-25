<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  USB HID quirks support क्रम Network Technologies, Inc. "USB-SUN" USB
 *  adapter क्रम pre-USB Sun keyboards
 *
 *  Copyright (c) 2011 Google, Inc.
 *
 * Based on HID apple driver by
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2006-2007 Jiri Kosina
 *  Copyright (c) 2008 Jiri Slaby <jirislaby@gmail.com>
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

MODULE_AUTHOR("Jonathan Klabunde Tomer <jktomer@google.com>");
MODULE_DESCRIPTION("HID driver for Network Technologies USB-SUN keyboard adapter");

/*
 * NTI Sun keyboard adapter has wrong logical maximum in report descriptor
 */
अटल __u8 *nti_usbsun_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	अगर (*rsize >= 60 && rdesc[53] == 0x65 && rdesc[59] == 0x65) अणु
		hid_info(hdev, "fixing up NTI USB-SUN keyboard adapter report descriptor\n");
		rdesc[53] = rdesc[59] = 0xe7;
	पूर्ण
	वापस rdesc;
पूर्ण

अटल स्थिर काष्ठा hid_device_id nti_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_NTI, USB_DEVICE_ID_USB_SUN) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, nti_devices);

अटल काष्ठा hid_driver nti_driver = अणु
	.name = "nti",
	.id_table = nti_devices,
	.report_fixup = nti_usbsun_report_fixup
पूर्ण;

module_hid_driver(nti_driver);

MODULE_LICENSE("GPL");
