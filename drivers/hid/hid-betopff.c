<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Force feedback support क्रम Betop based devices
 *
 *  The devices are distributed under various names and the same USB device ID
 *  can be used in both adapters and actual game controllers.
 *
 *  0x11c2:0x2208 "BTP2185 BFM mode Joystick"
 *   - tested with BTP2185 BFM Mode.
 *
 *  0x11C0:0x5506 "BTP2185 PC mode Joystick"
 *   - tested with BTP2185 PC Mode.
 *
 *  0x8380:0x1850 "BTP2185 V2 PC mode USB Gamepad"
 *   - tested with BTP2185 PC Mode with another version.
 *
 *  0x20bc:0x5500 "BTP2185 V2 BFM mode Joystick"
 *   - tested with BTP2171s.
 *  Copyright (c) 2014 Huang Bo <huangbobupt@163.com>
 */

/*
 */


#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/hid.h>

#समावेश "hid-ids.h"

काष्ठा betopff_device अणु
	काष्ठा hid_report *report;
पूर्ण;

अटल पूर्णांक hid_betopff_play(काष्ठा input_dev *dev, व्योम *data,
			 काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा betopff_device *betopff = data;
	__u16 left, right;

	left = effect->u.rumble.strong_magnitude;
	right = effect->u.rumble.weak_magnitude;

	betopff->report->field[2]->value[0] = left / 256;
	betopff->report->field[3]->value[0] = right / 256;

	hid_hw_request(hid, betopff->report, HID_REQ_SET_REPORT);

	वापस 0;
पूर्ण

अटल पूर्णांक betopff_init(काष्ठा hid_device *hid)
अणु
	काष्ठा betopff_device *betopff;
	काष्ठा hid_report *report;
	काष्ठा hid_input *hidinput =
			list_first_entry(&hid->inमाला_दो, काष्ठा hid_input, list);
	काष्ठा list_head *report_list =
			&hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list;
	काष्ठा input_dev *dev = hidinput->input;
	पूर्णांक field_count = 0;
	पूर्णांक error;
	पूर्णांक i, j;

	अगर (list_empty(report_list)) अणु
		hid_err(hid, "no output reports found\n");
		वापस -ENODEV;
	पूर्ण

	report = list_first_entry(report_list, काष्ठा hid_report, list);
	/*
	 * Actually there are 4 fields क्रम 4 Bytes as below:
	 * -----------------------------------------
	 * Byte0  Byte1  Byte2	  Byte3
	 * 0x00   0x00   left_motor right_motor
	 * -----------------------------------------
	 * Do init them with शेष value.
	 */
	क्रम (i = 0; i < report->maxfield; i++) अणु
		क्रम (j = 0; j < report->field[i]->report_count; j++) अणु
			report->field[i]->value[j] = 0x00;
			field_count++;
		पूर्ण
	पूर्ण

	अगर (field_count < 4) अणु
		hid_err(hid, "not enough fields in the report: %d\n",
				field_count);
		वापस -ENODEV;
	पूर्ण

	betopff = kzalloc(माप(*betopff), GFP_KERNEL);
	अगर (!betopff)
		वापस -ENOMEM;

	set_bit(FF_RUMBLE, dev->ffbit);

	error = input_ff_create_memless(dev, betopff, hid_betopff_play);
	अगर (error) अणु
		kमुक्त(betopff);
		वापस error;
	पूर्ण

	betopff->report = report;
	hid_hw_request(hid, betopff->report, HID_REQ_SET_REPORT);

	hid_info(hid, "Force feedback for betop devices by huangbo <huangbobupt@163.com>\n");

	वापस 0;
पूर्ण

अटल पूर्णांक betop_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;

	अगर (id->driver_data)
		hdev->quirks |= HID_QUIRK_MULTI_INPUT;

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

	betopff_init(hdev);

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id betop_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_BETOP_2185BFM, 0x2208) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_BETOP_2185PC, 0x5506) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_BETOP_2185V2PC, 0x1850) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_BETOP_2185V2BFM, 0x5500) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, betop_devices);

अटल काष्ठा hid_driver betop_driver = अणु
	.name = "betop",
	.id_table = betop_devices,
	.probe = betop_probe,
पूर्ण;
module_hid_driver(betop_driver);

MODULE_LICENSE("GPL");
