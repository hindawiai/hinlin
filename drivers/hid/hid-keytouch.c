<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम Keytouch devices not fully compliant with HID standard
 *
 *  Copyright (c) 2011 Jiri Kosina
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

/* Replace the broken report descriptor of this device with rather
 * a शेष one */
अटल __u8 keytouch_fixed_rdesc[] = अणु
0x05, 0x01, 0x09, 0x06, 0xa1, 0x01, 0x05, 0x07, 0x19, 0xe0, 0x29, 0xe7, 0x15,
0x00, 0x25, 0x01, 0x75, 0x01, 0x95, 0x08, 0x81, 0x02, 0x95, 0x01, 0x75, 0x08,
0x81, 0x01, 0x95, 0x03, 0x75, 0x01, 0x05, 0x08, 0x19, 0x01, 0x29, 0x03, 0x91,
0x02, 0x95, 0x05, 0x75, 0x01, 0x91, 0x01, 0x95, 0x06, 0x75, 0x08, 0x15, 0x00,
0x26, 0xff, 0x00, 0x05, 0x07, 0x19, 0x00, 0x2a, 0xff, 0x00, 0x81, 0x00, 0xc0
पूर्ण;

अटल __u8 *keytouch_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	hid_info(hdev, "fixing up Keytouch IEC report descriptor\n");

	rdesc = keytouch_fixed_rdesc;
	*rsize = माप(keytouch_fixed_rdesc);

	वापस rdesc;
पूर्ण

अटल स्थिर काष्ठा hid_device_id keytouch_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_KEYTOUCH, USB_DEVICE_ID_KEYTOUCH_IEC) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, keytouch_devices);

अटल काष्ठा hid_driver keytouch_driver = अणु
	.name = "keytouch",
	.id_table = keytouch_devices,
	.report_fixup = keytouch_report_fixup,
पूर्ण;
module_hid_driver(keytouch_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jiri Kosina");
