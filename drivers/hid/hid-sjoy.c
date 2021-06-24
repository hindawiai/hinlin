<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Force feedback support क्रम SmartJoy PLUS PS2->USB adapter
 *
 *  Copyright (c) 2009 Jussi Kivilinna <jussi.kivilinna@mbnet.fi>
 *
 *  Based of hid-pl.c and hid-gaff.c
 *   Copyright (c) 2007, 2009 Anssi Hannula <anssi.hannula@gmail.com>
 *   Copyright (c) 2008 Lukasz Lubojanski <lukasz@lubojanski.info>
 */

/*
 */

/* #घोषणा DEBUG */

#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश "hid-ids.h"

#अगर_घोषित CONFIG_SMARTJOYPLUS_FF

काष्ठा sjoyff_device अणु
	काष्ठा hid_report *report;
पूर्ण;

अटल पूर्णांक hid_sjoyff_play(काष्ठा input_dev *dev, व्योम *data,
			 काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा sjoyff_device *sjoyff = data;
	u32 left, right;

	left = effect->u.rumble.strong_magnitude;
	right = effect->u.rumble.weak_magnitude;
	dev_dbg(&dev->dev, "called with 0x%08x 0x%08x\n", left, right);

	left = left * 0xff / 0xffff;
	right = (right != 0); /* on/off only */

	sjoyff->report->field[0]->value[1] = right;
	sjoyff->report->field[0]->value[2] = left;
	dev_dbg(&dev->dev, "running with 0x%02x 0x%02x\n", left, right);
	hid_hw_request(hid, sjoyff->report, HID_REQ_SET_REPORT);

	वापस 0;
पूर्ण

अटल पूर्णांक sjoyff_init(काष्ठा hid_device *hid)
अणु
	काष्ठा sjoyff_device *sjoyff;
	काष्ठा hid_report *report;
	काष्ठा hid_input *hidinput;
	काष्ठा list_head *report_list =
			&hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list;
	काष्ठा list_head *report_ptr = report_list;
	काष्ठा input_dev *dev;
	पूर्णांक error;

	अगर (list_empty(report_list)) अणु
		hid_err(hid, "no output reports found\n");
		वापस -ENODEV;
	पूर्ण

	list_क्रम_each_entry(hidinput, &hid->inमाला_दो, list) अणु
		report_ptr = report_ptr->next;

		अगर (report_ptr == report_list) अणु
			hid_err(hid, "required output report is missing\n");
			वापस -ENODEV;
		पूर्ण

		report = list_entry(report_ptr, काष्ठा hid_report, list);
		अगर (report->maxfield < 1) अणु
			hid_err(hid, "no fields in the report\n");
			वापस -ENODEV;
		पूर्ण

		अगर (report->field[0]->report_count < 3) अणु
			hid_err(hid, "not enough values in the field\n");
			वापस -ENODEV;
		पूर्ण

		sjoyff = kzalloc(माप(काष्ठा sjoyff_device), GFP_KERNEL);
		अगर (!sjoyff)
			वापस -ENOMEM;

		dev = hidinput->input;

		set_bit(FF_RUMBLE, dev->ffbit);

		error = input_ff_create_memless(dev, sjoyff, hid_sjoyff_play);
		अगर (error) अणु
			kमुक्त(sjoyff);
			वापस error;
		पूर्ण

		sjoyff->report = report;
		sjoyff->report->field[0]->value[0] = 0x01;
		sjoyff->report->field[0]->value[1] = 0x00;
		sjoyff->report->field[0]->value[2] = 0x00;
		hid_hw_request(hid, sjoyff->report, HID_REQ_SET_REPORT);
	पूर्ण

	hid_info(hid, "Force feedback for SmartJoy PLUS PS2/USB adapter\n");

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक sjoyff_init(काष्ठा hid_device *hid)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sjoy_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;

	hdev->quirks |= id->driver_data;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		जाओ err;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT & ~HID_CONNECT_FF);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ err;
	पूर्ण

	sjoyff_init(hdev);

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id sjoy_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_WISEGROUP_LTD, USB_DEVICE_ID_SUPER_JOY_BOX_3_PRO),
		.driver_data = HID_QUIRK_NOGET पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_WISEGROUP_LTD, USB_DEVICE_ID_SUPER_DUAL_BOX_PRO),
		.driver_data = HID_QUIRK_MULTI_INPUT | HID_QUIRK_NOGET |
			       HID_QUIRK_SKIP_OUTPUT_REPORTS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_WISEGROUP_LTD, USB_DEVICE_ID_SUPER_JOY_BOX_5_PRO),
		.driver_data = HID_QUIRK_MULTI_INPUT | HID_QUIRK_NOGET |
			       HID_QUIRK_SKIP_OUTPUT_REPORTS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_WISEGROUP, USB_DEVICE_ID_SMARTJOY_PLUS) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_WISEGROUP, USB_DEVICE_ID_SUPER_JOY_BOX_3) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_WISEGROUP, USB_DEVICE_ID_DUAL_USB_JOYPAD),
		.driver_data = HID_QUIRK_MULTI_INPUT |
			       HID_QUIRK_SKIP_OUTPUT_REPORTS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_PLAYDOTCOM, USB_DEVICE_ID_PLAYDOTCOM_EMS_USBII),
		.driver_data = HID_QUIRK_MULTI_INPUT |
			       HID_QUIRK_SKIP_OUTPUT_REPORTS पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, sjoy_devices);

अटल काष्ठा hid_driver sjoy_driver = अणु
	.name = "smartjoyplus",
	.id_table = sjoy_devices,
	.probe = sjoy_probe,
पूर्ण;
module_hid_driver(sjoy_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jussi Kivilinna");

