<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम Saitek devices.
 *
 *  PS1000 (USB gamepad):
 *  Fixes the HID report descriptor by removing a non-existent axis and
 *  clearing the स्थिरant bit on the input reports क्रम buttons and d-pad.
 *  (This module is based on "hid-ortek".)
 *  Copyright (c) 2012 Andreas Hथञbner
 *
 *  R.A.T.7, R.A.T.9, M.M.O.7 (USB gaming mice):
 *  Fixes the mode button which cycles through three स्थिरantly pressed
 *  buttons. All three press events are mapped to one button and the
 *  missing release event is generated immediately.
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश "hid-ids.h"

#घोषणा SAITEK_FIX_PS1000	0x0001
#घोषणा SAITEK_RELEASE_MODE_RAT7	0x0002
#घोषणा SAITEK_RELEASE_MODE_MMO7	0x0004

काष्ठा saitek_sc अणु
	अचिन्हित दीर्घ quirks;
	पूर्णांक mode;
पूर्ण;

अटल पूर्णांक saitek_probe(काष्ठा hid_device *hdev,
		स्थिर काष्ठा hid_device_id *id)
अणु
	अचिन्हित दीर्घ quirks = id->driver_data;
	काष्ठा saitek_sc *ssc;
	पूर्णांक ret;

	ssc = devm_kzalloc(&hdev->dev, माप(*ssc), GFP_KERNEL);
	अगर (ssc == शून्य) अणु
		hid_err(hdev, "can't alloc saitek descriptor\n");
		वापस -ENOMEM;
	पूर्ण

	ssc->quirks = quirks;
	ssc->mode = -1;

	hid_set_drvdata(hdev, ssc);

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		वापस ret;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल __u8 *saitek_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	काष्ठा saitek_sc *ssc = hid_get_drvdata(hdev);

	अगर ((ssc->quirks & SAITEK_FIX_PS1000) && *rsize == 137 &&
			rdesc[20] == 0x09 && rdesc[21] == 0x33 &&
			rdesc[94] == 0x81 && rdesc[95] == 0x03 &&
			rdesc[110] == 0x81 && rdesc[111] == 0x03) अणु

		hid_info(hdev, "Fixing up Saitek PS1000 report descriptor\n");

		/* convert spurious axis to a "noop" Logical Minimum (0) */
		rdesc[20] = 0x15;
		rdesc[21] = 0x00;

		/* clear स्थिरant bit on buttons and d-pad */
		rdesc[95] = 0x02;
		rdesc[111] = 0x02;

	पूर्ण
	वापस rdesc;
पूर्ण

अटल पूर्णांक saitek_raw_event(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report, u8 *raw_data, पूर्णांक size)
अणु
	काष्ठा saitek_sc *ssc = hid_get_drvdata(hdev);

	अगर (ssc->quirks & SAITEK_RELEASE_MODE_RAT7 && size == 7) अणु
		/* R.A.T.7 uses bits 13, 14, 15 क्रम the mode */
		पूर्णांक mode = -1;
		अगर (raw_data[1] & 0x01)
			mode = 0;
		अन्यथा अगर (raw_data[1] & 0x02)
			mode = 1;
		अन्यथा अगर (raw_data[1] & 0x04)
			mode = 2;

		/* clear mode bits */
		raw_data[1] &= ~0x07;

		अगर (mode != ssc->mode) अणु
			hid_dbg(hdev, "entered mode %d\n", mode);
			अगर (ssc->mode != -1) अणु
				/* use bit 13 as the mode button */
				raw_data[1] |= 0x04;
			पूर्ण
			ssc->mode = mode;
		पूर्ण
	पूर्ण अन्यथा अगर (ssc->quirks & SAITEK_RELEASE_MODE_MMO7 && size == 8) अणु

		/* M.M.O.7 uses bits 8, 22, 23 क्रम the mode */
		पूर्णांक mode = -1;
		अगर (raw_data[1] & 0x80)
			mode = 0;
		अन्यथा अगर (raw_data[2] & 0x01)
			mode = 1;
		अन्यथा अगर (raw_data[2] & 0x02)
			mode = 2;

		/* clear mode bits */
		raw_data[1] &= ~0x80;
		raw_data[2] &= ~0x03;

		अगर (mode != ssc->mode) अणु
			hid_dbg(hdev, "entered mode %d\n", mode);
			अगर (ssc->mode != -1) अणु
				/* use bit 8 as the mode button, bits 22
				 * and 23 करो not represent buttons
				 * according to the HID report descriptor
				 */
				raw_data[1] |= 0x80;
			पूर्ण
			ssc->mode = mode;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक saitek_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा saitek_sc *ssc = hid_get_drvdata(hdev);
	काष्ठा input_dev *input = field->hidinput->input;

	अगर (usage->type == EV_KEY && value &&
			(((ssc->quirks & SAITEK_RELEASE_MODE_RAT7) &&
			  usage->code - BTN_MOUSE == 10) ||
			((ssc->quirks & SAITEK_RELEASE_MODE_MMO7) &&
			 usage->code - BTN_MOUSE == 15))) अणु

		input_report_key(input, usage->code, 1);

		/* report missing release event */
		input_report_key(input, usage->code, 0);

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id saitek_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SAITEK, USB_DEVICE_ID_SAITEK_PS1000),
		.driver_data = SAITEK_FIX_PS1000 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MADCATZ, USB_DEVICE_ID_MADCATZ_RAT5),
		.driver_data = SAITEK_RELEASE_MODE_RAT7 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SAITEK, USB_DEVICE_ID_SAITEK_RAT7_OLD),
		.driver_data = SAITEK_RELEASE_MODE_RAT7 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SAITEK, USB_DEVICE_ID_SAITEK_RAT7),
		.driver_data = SAITEK_RELEASE_MODE_RAT7 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SAITEK, USB_DEVICE_ID_SAITEK_RAT7_CONTAGION),
		.driver_data = SAITEK_RELEASE_MODE_RAT7 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SAITEK, USB_DEVICE_ID_SAITEK_RAT9),
		.driver_data = SAITEK_RELEASE_MODE_RAT7 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MADCATZ, USB_DEVICE_ID_MADCATZ_RAT9),
		.driver_data = SAITEK_RELEASE_MODE_RAT7 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SAITEK, USB_DEVICE_ID_SAITEK_MMO7),
		.driver_data = SAITEK_RELEASE_MODE_MMO7 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, saitek_devices);

अटल काष्ठा hid_driver saitek_driver = अणु
	.name = "saitek",
	.id_table = saitek_devices,
	.probe = saitek_probe,
	.report_fixup = saitek_report_fixup,
	.raw_event = saitek_raw_event,
	.event = saitek_event,
पूर्ण;
module_hid_driver(saitek_driver);

MODULE_LICENSE("GPL");
