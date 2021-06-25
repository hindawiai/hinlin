<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम ELECOM devices:
 *  - BM084 Bluetooth Mouse
 *  - EX-G Trackballs (M-XT3DRBK, M-XT3URBK, M-XT4DRBK)
 *  - DEFT Trackballs (M-DT1DRBK, M-DT1URBK, M-DT2DRBK, M-DT2URBK)
 *  - HUGE Trackballs (M-HT1DRBK, M-HT1URBK)
 *
 *  Copyright (c) 2010 Riअक्षरd Nauber <Riअक्षरd.Nauber@gmail.com>
 *  Copyright (c) 2016 Yuxuan Shui <yshuiv7@gmail.com>
 *  Copyright (c) 2017 Diego Elio Pettenथऑ <flameeyes@flameeyes.eu>
 *  Copyright (c) 2017 Alex Manoussakis <amanou@gnu.org>
 *  Copyright (c) 2017 Tomasz Kramkowski <tk@the-tk.com>
 *  Copyright (c) 2020 YOSHIOKA Takuma <lo48576@hard-wi.red>
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

/*
 * Certain ELECOM mice misreport their button count meaning that they only work
 * correctly with the ELECOM mouse assistant software which is unavailable क्रम
 * Linux. A four extra INPUT reports and a FEATURE report are described by the
 * report descriptor but it करोes not appear that these enable software to
 * control what the extra buttons map to. The only simple and straightक्रमward
 * solution seems to involve fixing up the report descriptor.
 */
#घोषणा MOUSE_BUTTONS_MAX 8
अटल व्योम mouse_button_fixup(काष्ठा hid_device *hdev,
			       __u8 *rdesc, अचिन्हित पूर्णांक rsize,
			       अचिन्हित पूर्णांक button_bit_count,
			       अचिन्हित पूर्णांक padding_bit,
			       अचिन्हित पूर्णांक button_report_size,
			       अचिन्हित पूर्णांक button_usage_maximum,
			       पूर्णांक nbuttons)
अणु
	अगर (rsize < 32 || rdesc[button_bit_count] != 0x95 ||
	    rdesc[button_report_size] != 0x75 ||
	    rdesc[button_report_size + 1] != 0x01 ||
	    rdesc[button_usage_maximum] != 0x29 || rdesc[padding_bit] != 0x75)
		वापस;
	hid_info(hdev, "Fixing up Elecom mouse button count\n");
	nbuttons = clamp(nbuttons, 0, MOUSE_BUTTONS_MAX);
	rdesc[button_bit_count + 1] = nbuttons;
	rdesc[button_usage_maximum + 1] = nbuttons;
	rdesc[padding_bit + 1] = MOUSE_BUTTONS_MAX - nbuttons;
पूर्ण

अटल __u8 *elecom_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	चयन (hdev->product) अणु
	हाल USB_DEVICE_ID_ELECOM_BM084:
		/* The BM084 Bluetooth mouse includes a non-existing horizontal
		 * wheel in the HID descriptor. */
		अगर (*rsize >= 48 && rdesc[46] == 0x05 && rdesc[47] == 0x0c) अणु
			hid_info(hdev, "Fixing up Elecom BM084 report descriptor\n");
			rdesc[47] = 0x00;
		पूर्ण
		अवरोध;
	हाल USB_DEVICE_ID_ELECOM_M_XGL20DLBK:
		/*
		 * Report descriptor क्रमmat:
		 * 20: button bit count
		 * 28: padding bit count
		 * 22: button report size
		 * 14: button usage maximum
		 */
		mouse_button_fixup(hdev, rdesc, *rsize, 20, 28, 22, 14, 8);
		अवरोध;
	हाल USB_DEVICE_ID_ELECOM_M_XT3URBK:
	हाल USB_DEVICE_ID_ELECOM_M_XT3DRBK:
	हाल USB_DEVICE_ID_ELECOM_M_XT4DRBK:
		/*
		 * Report descriptor क्रमmat:
		 * 12: button bit count
		 * 30: padding bit count
		 * 14: button report size
		 * 20: button usage maximum
		 */
		mouse_button_fixup(hdev, rdesc, *rsize, 12, 30, 14, 20, 6);
		अवरोध;
	हाल USB_DEVICE_ID_ELECOM_M_DT1URBK:
	हाल USB_DEVICE_ID_ELECOM_M_DT1DRBK:
	हाल USB_DEVICE_ID_ELECOM_M_HT1URBK:
	हाल USB_DEVICE_ID_ELECOM_M_HT1DRBK:
		/*
		 * Report descriptor क्रमmat:
		 * 12: button bit count
		 * 30: padding bit count
		 * 14: button report size
		 * 20: button usage maximum
		 */
		mouse_button_fixup(hdev, rdesc, *rsize, 12, 30, 14, 20, 8);
		अवरोध;
	पूर्ण
	वापस rdesc;
पूर्ण

अटल स्थिर काष्ठा hid_device_id elecom_devices[] = अणु
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_ELECOM, USB_DEVICE_ID_ELECOM_BM084) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ELECOM, USB_DEVICE_ID_ELECOM_M_XGL20DLBK) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ELECOM, USB_DEVICE_ID_ELECOM_M_XT3URBK) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ELECOM, USB_DEVICE_ID_ELECOM_M_XT3DRBK) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ELECOM, USB_DEVICE_ID_ELECOM_M_XT4DRBK) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ELECOM, USB_DEVICE_ID_ELECOM_M_DT1URBK) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ELECOM, USB_DEVICE_ID_ELECOM_M_DT1DRBK) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ELECOM, USB_DEVICE_ID_ELECOM_M_HT1URBK) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ELECOM, USB_DEVICE_ID_ELECOM_M_HT1DRBK) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, elecom_devices);

अटल काष्ठा hid_driver elecom_driver = अणु
	.name = "elecom",
	.id_table = elecom_devices,
	.report_fixup = elecom_report_fixup
पूर्ण;
module_hid_driver(elecom_driver);

MODULE_LICENSE("GPL");
