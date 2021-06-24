<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम some cypress "special" devices
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2006-2007 Jiri Kosina
 *  Copyright (c) 2008 Jiri Slaby
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#घोषणा CP_RDESC_SWAPPED_MIN_MAX	0x01
#घोषणा CP_2WHEEL_MOUSE_HACK		0x02
#घोषणा CP_2WHEEL_MOUSE_HACK_ON		0x04

#घोषणा VA_INVAL_LOGICAL_BOUNDARY	0x08

/*
 * Some USB barcode पढ़ोers from cypress have usage min and usage max in
 * the wrong order
 */
अटल __u8 *cp_rdesc_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	अचिन्हित पूर्णांक i;

	अगर (*rsize < 4)
		वापस rdesc;

	क्रम (i = 0; i < *rsize - 4; i++)
		अगर (rdesc[i] == 0x29 && rdesc[i + 2] == 0x19) अणु
			rdesc[i] = 0x19;
			rdesc[i + 2] = 0x29;
			swap(rdesc[i + 3], rdesc[i + 1]);
		पूर्ण
	वापस rdesc;
पूर्ण

अटल __u8 *va_logical_boundary_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	/*
	 * Varmilo VA104M (with VID Cypress and device ID 07B1) incorrectly
	 * reports Logical Minimum of its Consumer Control device as 572
	 * (0x02 0x3c). Fix this by setting its Logical Minimum to zero.
	 */
	अगर (*rsize == 25 &&
			rdesc[0] == 0x05 && rdesc[1] == 0x0c &&
			rdesc[2] == 0x09 && rdesc[3] == 0x01 &&
			rdesc[6] == 0x19 && rdesc[7] == 0x00 &&
			rdesc[11] == 0x16 && rdesc[12] == 0x3c && rdesc[13] == 0x02) अणु
		hid_info(hdev,
			 "fixing up varmilo VA104M consumer control report descriptor\n");
		rdesc[12] = 0x00;
		rdesc[13] = 0x00;
	पूर्ण
	वापस rdesc;
पूर्ण

अटल __u8 *cp_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	अचिन्हित दीर्घ quirks = (अचिन्हित दीर्घ)hid_get_drvdata(hdev);

	अगर (quirks & CP_RDESC_SWAPPED_MIN_MAX)
		rdesc = cp_rdesc_fixup(hdev, rdesc, rsize);
	अगर (quirks & VA_INVAL_LOGICAL_BOUNDARY)
		rdesc = va_logical_boundary_fixup(hdev, rdesc, rsize);

	वापस rdesc;
पूर्ण

अटल पूर्णांक cp_input_mapped(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अचिन्हित दीर्घ quirks = (अचिन्हित दीर्घ)hid_get_drvdata(hdev);

	अगर (!(quirks & CP_2WHEEL_MOUSE_HACK))
		वापस 0;

	अगर (usage->type == EV_REL && usage->code == REL_WHEEL)
		set_bit(REL_HWHEEL, *bit);
	अगर (usage->hid == 0x00090005)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक cp_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	अचिन्हित दीर्घ quirks = (अचिन्हित दीर्घ)hid_get_drvdata(hdev);

	अगर (!(hdev->claimed & HID_CLAIMED_INPUT) || !field->hidinput ||
			!usage->type || !(quirks & CP_2WHEEL_MOUSE_HACK))
		वापस 0;

	अगर (usage->hid == 0x00090005) अणु
		अगर (value)
			quirks |=  CP_2WHEEL_MOUSE_HACK_ON;
		अन्यथा
			quirks &= ~CP_2WHEEL_MOUSE_HACK_ON;
		hid_set_drvdata(hdev, (व्योम *)quirks);
		वापस 1;
	पूर्ण

	अगर (usage->code == REL_WHEEL && (quirks & CP_2WHEEL_MOUSE_HACK_ON)) अणु
		काष्ठा input_dev *input = field->hidinput->input;

		input_event(input, usage->type, REL_HWHEEL, value);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cp_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	अचिन्हित दीर्घ quirks = id->driver_data;
	पूर्णांक ret;

	hid_set_drvdata(hdev, (व्योम *)quirks);

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		जाओ err_मुक्त;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ err_मुक्त;
	पूर्ण

	वापस 0;
err_मुक्त:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id cp_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CYPRESS, USB_DEVICE_ID_CYPRESS_BARCODE_1),
		.driver_data = CP_RDESC_SWAPPED_MIN_MAX पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CYPRESS, USB_DEVICE_ID_CYPRESS_BARCODE_2),
		.driver_data = CP_RDESC_SWAPPED_MIN_MAX पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CYPRESS, USB_DEVICE_ID_CYPRESS_BARCODE_3),
		.driver_data = CP_RDESC_SWAPPED_MIN_MAX पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CYPRESS, USB_DEVICE_ID_CYPRESS_BARCODE_4),
		.driver_data = CP_RDESC_SWAPPED_MIN_MAX पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CYPRESS, USB_DEVICE_ID_CYPRESS_MOUSE),
		.driver_data = CP_2WHEEL_MOUSE_HACK पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CYPRESS, USB_DEVICE_ID_CYPRESS_VARMILO_VA104M_07B1),
		.driver_data = VA_INVAL_LOGICAL_BOUNDARY पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, cp_devices);

अटल काष्ठा hid_driver cp_driver = अणु
	.name = "cypress",
	.id_table = cp_devices,
	.report_fixup = cp_report_fixup,
	.input_mapped = cp_input_mapped,
	.event = cp_event,
	.probe = cp_probe,
पूर्ण;
module_hid_driver(cp_driver);

MODULE_LICENSE("GPL");
