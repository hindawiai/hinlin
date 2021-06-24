<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  HID driver क्रम Aureal Cy se W-01RN USB_V3.1 devices
 *
 *  Copyright (c) 2010 Franco Catrin <fcatrin@gmail.com>
 *  Copyright (c) 2010 Ben Cropley <bcropley@पूर्णांकernode.on.net>
 *
 *  Based on HID sunplus driver by
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2006-2007 Jiri Kosina
 *  Copyright (c) 2008 Jiri Slaby
 */
#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

अटल __u8 *aureal_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	अगर (*rsize >= 54 && rdesc[52] == 0x25 && rdesc[53] == 0x01) अणु
		dev_info(&hdev->dev, "fixing Aureal Cy se W-01RN USB_V3.1 report descriptor.\n");
		rdesc[53] = 0x65;
	पूर्ण
	वापस rdesc;
पूर्ण

अटल स्थिर काष्ठा hid_device_id aureal_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_AUREAL, USB_DEVICE_ID_AUREAL_W01RN) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, aureal_devices);

अटल काष्ठा hid_driver aureal_driver = अणु
	.name = "aureal",
	.id_table = aureal_devices,
	.report_fixup = aureal_report_fixup,
पूर्ण;
module_hid_driver(aureal_driver);

MODULE_LICENSE("GPL");
