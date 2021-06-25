<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Force feedback support क्रम EMS Trio Linker Plus II
 *
 *  Copyright (c) 2010 Ignaz Forster <ignaz.क्रमster@gmx.de>
 */

/*
 */


#समावेश <linux/hid.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

काष्ठा emsff_device अणु
	काष्ठा hid_report *report;
पूर्ण;

अटल पूर्णांक emsff_play(काष्ठा input_dev *dev, व्योम *data,
			 काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा emsff_device *emsff = data;
	पूर्णांक weak, strong;

	weak = effect->u.rumble.weak_magnitude;
	strong = effect->u.rumble.strong_magnitude;

	dbg_hid("called with 0x%04x 0x%04x\n", strong, weak);

	weak = weak * 0xff / 0xffff;
	strong = strong * 0xff / 0xffff;

	emsff->report->field[0]->value[1] = weak;
	emsff->report->field[0]->value[2] = strong;

	dbg_hid("running with 0x%02x 0x%02x\n", strong, weak);
	hid_hw_request(hid, emsff->report, HID_REQ_SET_REPORT);

	वापस 0;
पूर्ण

अटल पूर्णांक emsff_init(काष्ठा hid_device *hid)
अणु
	काष्ठा emsff_device *emsff;
	काष्ठा hid_report *report;
	काष्ठा hid_input *hidinput;
	काष्ठा list_head *report_list =
			&hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list;
	काष्ठा input_dev *dev;
	पूर्णांक error;

	अगर (list_empty(&hid->inमाला_दो)) अणु
		hid_err(hid, "no inputs found\n");
		वापस -ENODEV;
	पूर्ण
	hidinput = list_first_entry(&hid->inमाला_दो, काष्ठा hid_input, list);
	dev = hidinput->input;

	अगर (list_empty(report_list)) अणु
		hid_err(hid, "no output reports found\n");
		वापस -ENODEV;
	पूर्ण

	report = list_first_entry(report_list, काष्ठा hid_report, list);
	अगर (report->maxfield < 1) अणु
		hid_err(hid, "no fields in the report\n");
		वापस -ENODEV;
	पूर्ण

	अगर (report->field[0]->report_count < 7) अणु
		hid_err(hid, "not enough values in the field\n");
		वापस -ENODEV;
	पूर्ण

	emsff = kzalloc(माप(काष्ठा emsff_device), GFP_KERNEL);
	अगर (!emsff)
		वापस -ENOMEM;

	set_bit(FF_RUMBLE, dev->ffbit);

	error = input_ff_create_memless(dev, emsff, emsff_play);
	अगर (error) अणु
		kमुक्त(emsff);
		वापस error;
	पूर्ण

	emsff->report = report;
	emsff->report->field[0]->value[0] = 0x01;
	emsff->report->field[0]->value[1] = 0x00;
	emsff->report->field[0]->value[2] = 0x00;
	emsff->report->field[0]->value[3] = 0x00;
	emsff->report->field[0]->value[4] = 0x00;
	emsff->report->field[0]->value[5] = 0x00;
	emsff->report->field[0]->value[6] = 0x00;
	hid_hw_request(hid, emsff->report, HID_REQ_SET_REPORT);

	hid_info(hid, "force feedback for EMS based devices by Ignaz Forster <ignaz.forster@gmx.de>\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ems_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;

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

	ret = emsff_init(hdev);
	अगर (ret) अणु
		dev_err(&hdev->dev, "force feedback init failed\n");
		hid_hw_stop(hdev);
		जाओ err;
	पूर्ण

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id ems_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_EMS, USB_DEVICE_ID_EMS_TRIO_LINKER_PLUS_II) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, ems_devices);

अटल काष्ठा hid_driver ems_driver = अणु
	.name = "hkems",
	.id_table = ems_devices,
	.probe = ems_probe,
पूर्ण;
module_hid_driver(ems_driver);

MODULE_LICENSE("GPL");

