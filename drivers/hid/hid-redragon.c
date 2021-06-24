<शैली गुरु>
/*
 *  HID driver क्रम Redragon keyboards
 *
 *  Copyright (c) 2017 Robert Munteanu
 *  SPDX-License-Identअगरier: GPL-2.0+
 */

/*
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"


/*
 * The Redragon Asura keyboard sends an incorrect HID descriptor.
 * At byte 100 it contains
 *
 *   0x81, 0x00
 *
 * which is Input (Data, Arr, Abs), but it should be
 *
 *   0x81, 0x02
 *
 * which is Input (Data, Var, Abs), which is consistent with the way
 * key codes are generated.
 */

अटल __u8 *redragon_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
	अचिन्हित पूर्णांक *rsize)
अणु
	अगर (*rsize >= 102 && rdesc[100] == 0x81 && rdesc[101] == 0x00) अणु
		dev_info(&hdev->dev, "Fixing Redragon ASURA report descriptor.\n");
		rdesc[101] = 0x02;
	पूर्ण

	वापस rdesc;
पूर्ण

अटल स्थिर काष्ठा hid_device_id redragon_devices[] = अणु
	अणुHID_USB_DEVICE(USB_VENDOR_ID_JESS, USB_DEVICE_ID_REDRAGON_ASURA)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, redragon_devices);

अटल काष्ठा hid_driver redragon_driver = अणु
	.name = "redragon",
	.id_table = redragon_devices,
	.report_fixup = redragon_report_fixup
पूर्ण;

module_hid_driver(redragon_driver);

MODULE_LICENSE("GPL");
