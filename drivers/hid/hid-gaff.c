<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Force feedback support क्रम GreenAsia (Product ID 0x12) based devices
 *
 *  The devices are distributed under various names and the same USB device ID
 *  can be used in many game controllers.
 *
 *  0e8f:0012 "GreenAsia Inc.    USB Joystick     "
 *   - tested with MANTA Warior MM816 and SpeedLink Strike2 SL-6635.
 *
 *  Copyright (c) 2008 Lukasz Lubojanski <lukasz@lubojanski.info>
 */

/*
 */

#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश "hid-ids.h"

#अगर_घोषित CONFIG_GREENASIA_FF

काष्ठा gaff_device अणु
	काष्ठा hid_report *report;
पूर्ण;

अटल पूर्णांक hid_gaff_play(काष्ठा input_dev *dev, व्योम *data,
			 काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा gaff_device *gaff = data;
	पूर्णांक left, right;

	left = effect->u.rumble.strong_magnitude;
	right = effect->u.rumble.weak_magnitude;

	dbg_hid("called with 0x%04x 0x%04x", left, right);

	left = left * 0xfe / 0xffff;
	right = right * 0xfe / 0xffff;

	gaff->report->field[0]->value[0] = 0x51;
	gaff->report->field[0]->value[1] = 0x0;
	gaff->report->field[0]->value[2] = right;
	gaff->report->field[0]->value[3] = 0;
	gaff->report->field[0]->value[4] = left;
	gaff->report->field[0]->value[5] = 0;
	dbg_hid("running with 0x%02x 0x%02x", left, right);
	hid_hw_request(hid, gaff->report, HID_REQ_SET_REPORT);

	gaff->report->field[0]->value[0] = 0xfa;
	gaff->report->field[0]->value[1] = 0xfe;
	gaff->report->field[0]->value[2] = 0x0;
	gaff->report->field[0]->value[4] = 0x0;

	hid_hw_request(hid, gaff->report, HID_REQ_SET_REPORT);

	वापस 0;
पूर्ण

अटल पूर्णांक gaff_init(काष्ठा hid_device *hid)
अणु
	काष्ठा gaff_device *gaff;
	काष्ठा hid_report *report;
	काष्ठा hid_input *hidinput;
	काष्ठा list_head *report_list =
			&hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list;
	काष्ठा list_head *report_ptr = report_list;
	काष्ठा input_dev *dev;
	पूर्णांक error;

	अगर (list_empty(&hid->inमाला_दो)) अणु
		hid_err(hid, "no inputs found\n");
		वापस -ENODEV;
	पूर्ण
	hidinput = list_entry(hid->inमाला_दो.next, काष्ठा hid_input, list);
	dev = hidinput->input;

	अगर (list_empty(report_list)) अणु
		hid_err(hid, "no output reports found\n");
		वापस -ENODEV;
	पूर्ण

	report_ptr = report_ptr->next;

	report = list_entry(report_ptr, काष्ठा hid_report, list);
	अगर (report->maxfield < 1) अणु
		hid_err(hid, "no fields in the report\n");
		वापस -ENODEV;
	पूर्ण

	अगर (report->field[0]->report_count < 6) अणु
		hid_err(hid, "not enough values in the field\n");
		वापस -ENODEV;
	पूर्ण

	gaff = kzalloc(माप(काष्ठा gaff_device), GFP_KERNEL);
	अगर (!gaff)
		वापस -ENOMEM;

	set_bit(FF_RUMBLE, dev->ffbit);

	error = input_ff_create_memless(dev, gaff, hid_gaff_play);
	अगर (error) अणु
		kमुक्त(gaff);
		वापस error;
	पूर्ण

	gaff->report = report;
	gaff->report->field[0]->value[0] = 0x51;
	gaff->report->field[0]->value[1] = 0x00;
	gaff->report->field[0]->value[2] = 0x00;
	gaff->report->field[0]->value[3] = 0x00;
	hid_hw_request(hid, gaff->report, HID_REQ_SET_REPORT);

	gaff->report->field[0]->value[0] = 0xfa;
	gaff->report->field[0]->value[1] = 0xfe;

	hid_hw_request(hid, gaff->report, HID_REQ_SET_REPORT);

	hid_info(hid, "Force Feedback for GreenAsia 0x12 devices by Lukasz Lubojanski <lukasz@lubojanski.info>\n");

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक gaff_init(काष्ठा hid_device *hdev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ga_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;

	dev_dbg(&hdev->dev, "Greenasia HID hardware probe...");

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

	gaff_init(hdev);

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id ga_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_GREENASIA, 0x0012),  पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, ga_devices);

अटल काष्ठा hid_driver ga_driver = अणु
	.name = "greenasia",
	.id_table = ga_devices,
	.probe = ga_probe,
पूर्ण;
module_hid_driver(ga_driver);

MODULE_LICENSE("GPL");
