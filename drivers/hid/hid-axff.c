<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Force feedback support क्रम ACRUX game controllers
 *
 * From what I have gathered, these devices are mass produced in China
 * by several venकरोrs. They often share the same design as the original
 * Xbox 360 controller.
 *
 * 1a34:0802 "ACRUX USB GAMEPAD 8116"
 *  - tested with an EXEQ EQ-PCU-02090 game controller.
 *
 * Copyright (c) 2010 Sergei Kolzun <x0r@dv-lअगरe.ru>
 */

/*
 */

#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#अगर_घोषित CONFIG_HID_ACRUX_FF

काष्ठा axff_device अणु
	काष्ठा hid_report *report;
पूर्ण;

अटल पूर्णांक axff_play(काष्ठा input_dev *dev, व्योम *data, काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा axff_device *axff = data;
	काष्ठा hid_report *report = axff->report;
	पूर्णांक field_count = 0;
	पूर्णांक left, right;
	पूर्णांक i, j;

	left = effect->u.rumble.strong_magnitude;
	right = effect->u.rumble.weak_magnitude;

	dbg_hid("called with 0x%04x 0x%04x", left, right);

	left = left * 0xff / 0xffff;
	right = right * 0xff / 0xffff;

	क्रम (i = 0; i < report->maxfield; i++) अणु
		क्रम (j = 0; j < report->field[i]->report_count; j++) अणु
			report->field[i]->value[j] =
				field_count % 2 ? right : left;
			field_count++;
		पूर्ण
	पूर्ण

	dbg_hid("running with 0x%02x 0x%02x", left, right);
	hid_hw_request(hid, axff->report, HID_REQ_SET_REPORT);

	वापस 0;
पूर्ण

अटल पूर्णांक axff_init(काष्ठा hid_device *hid)
अणु
	काष्ठा axff_device *axff;
	काष्ठा hid_report *report;
	काष्ठा hid_input *hidinput;
	काष्ठा list_head *report_list =&hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list;
	काष्ठा input_dev *dev;
	पूर्णांक field_count = 0;
	पूर्णांक i, j;
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
	क्रम (i = 0; i < report->maxfield; i++) अणु
		क्रम (j = 0; j < report->field[i]->report_count; j++) अणु
			report->field[i]->value[j] = 0x00;
			field_count++;
		पूर्ण
	पूर्ण

	अगर (field_count < 4 && hid->product != 0xf705) अणु
		hid_err(hid, "not enough fields in the report: %d\n",
			field_count);
		वापस -ENODEV;
	पूर्ण

	axff = kzalloc(माप(काष्ठा axff_device), GFP_KERNEL);
	अगर (!axff)
		वापस -ENOMEM;

	set_bit(FF_RUMBLE, dev->ffbit);

	error = input_ff_create_memless(dev, axff, axff_play);
	अगर (error)
		जाओ err_मुक्त_mem;

	axff->report = report;
	hid_hw_request(hid, axff->report, HID_REQ_SET_REPORT);

	hid_info(hid, "Force Feedback for ACRUX game controllers by Sergei Kolzun <x0r@dv-life.ru>\n");

	वापस 0;

err_मुक्त_mem:
	kमुक्त(axff);
	वापस error;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक axff_init(काष्ठा hid_device *hid)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ax_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक error;

	dev_dbg(&hdev->dev, "ACRUX HID hardware probe...\n");

	error = hid_parse(hdev);
	अगर (error) अणु
		hid_err(hdev, "parse failed\n");
		वापस error;
	पूर्ण

	error = hid_hw_start(hdev, HID_CONNECT_DEFAULT & ~HID_CONNECT_FF);
	अगर (error) अणु
		hid_err(hdev, "hw start failed\n");
		वापस error;
	पूर्ण

	error = axff_init(hdev);
	अगर (error) अणु
		/*
		 * Do not fail device initialization completely as device
		 * may still be partially operable, just warn.
		 */
		hid_warn(hdev,
			 "Failed to enable force feedback support, error: %d\n",
			 error);
	पूर्ण

	/*
	 * We need to start polling device right away, otherwise
	 * it will go पूर्णांकo a coma.
	 */
	error = hid_hw_खोलो(hdev);
	अगर (error) अणु
		dev_err(&hdev->dev, "hw open failed\n");
		hid_hw_stop(hdev);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ax_हटाओ(काष्ठा hid_device *hdev)
अणु
	hid_hw_बंद(hdev);
	hid_hw_stop(hdev);
पूर्ण

अटल स्थिर काष्ठा hid_device_id ax_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ACRUX, 0x0802), पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ACRUX, 0xf705), पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, ax_devices);

अटल काष्ठा hid_driver ax_driver = अणु
	.name		= "acrux",
	.id_table	= ax_devices,
	.probe		= ax_probe,
	.हटाओ		= ax_हटाओ,
पूर्ण;
module_hid_driver(ax_driver);

MODULE_AUTHOR("Sergei Kolzun");
MODULE_DESCRIPTION("Force feedback support for ACRUX game controllers");
MODULE_LICENSE("GPL");
