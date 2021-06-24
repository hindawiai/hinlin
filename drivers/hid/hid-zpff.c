<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Force feedback support क्रम Zeroplus based devices
 *
 *  Copyright (c) 2005, 2006 Anssi Hannula <anssi.hannula@gmail.com>
 */

/*
 */


#समावेश <linux/hid.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#अगर_घोषित CONFIG_ZEROPLUS_FF

काष्ठा zpff_device अणु
	काष्ठा hid_report *report;
पूर्ण;

अटल पूर्णांक zpff_play(काष्ठा input_dev *dev, व्योम *data,
			 काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा zpff_device *zpff = data;
	पूर्णांक left, right;

	/*
	 * The following is specअगरied the other way around in the Zeroplus
	 * datasheet but the order below is correct क्रम the XFX Executioner;
	 * however it is possible that the XFX Executioner is an exception
	 */

	left = effect->u.rumble.strong_magnitude;
	right = effect->u.rumble.weak_magnitude;
	dbg_hid("called with 0x%04x 0x%04x\n", left, right);

	left = left * 0x7f / 0xffff;
	right = right * 0x7f / 0xffff;

	zpff->report->field[2]->value[0] = left;
	zpff->report->field[3]->value[0] = right;
	dbg_hid("running with 0x%02x 0x%02x\n", left, right);
	hid_hw_request(hid, zpff->report, HID_REQ_SET_REPORT);

	वापस 0;
पूर्ण

अटल पूर्णांक zpff_init(काष्ठा hid_device *hid)
अणु
	काष्ठा zpff_device *zpff;
	काष्ठा hid_report *report;
	काष्ठा hid_input *hidinput;
	काष्ठा input_dev *dev;
	पूर्णांक i, error;

	अगर (list_empty(&hid->inमाला_दो)) अणु
		hid_err(hid, "no inputs found\n");
		वापस -ENODEV;
	पूर्ण
	hidinput = list_entry(hid->inमाला_दो.next, काष्ठा hid_input, list);
	dev = hidinput->input;

	क्रम (i = 0; i < 4; i++) अणु
		report = hid_validate_values(hid, HID_OUTPUT_REPORT, 0, i, 1);
		अगर (!report)
			वापस -ENODEV;
	पूर्ण

	zpff = kzalloc(माप(काष्ठा zpff_device), GFP_KERNEL);
	अगर (!zpff)
		वापस -ENOMEM;

	set_bit(FF_RUMBLE, dev->ffbit);

	error = input_ff_create_memless(dev, zpff, zpff_play);
	अगर (error) अणु
		kमुक्त(zpff);
		वापस error;
	पूर्ण

	zpff->report = report;
	zpff->report->field[0]->value[0] = 0x00;
	zpff->report->field[1]->value[0] = 0x02;
	zpff->report->field[2]->value[0] = 0x00;
	zpff->report->field[3]->value[0] = 0x00;
	hid_hw_request(hid, zpff->report, HID_REQ_SET_REPORT);

	hid_info(hid, "force feedback for Zeroplus based devices by Anssi Hannula <anssi.hannula@gmail.com>\n");

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक zpff_init(काष्ठा hid_device *hid)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक zp_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
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

	zpff_init(hdev);

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id zp_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ZEROPLUS, 0x0005) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ZEROPLUS, 0x0030) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, zp_devices);

अटल काष्ठा hid_driver zp_driver = अणु
	.name = "zeroplus",
	.id_table = zp_devices,
	.probe = zp_probe,
पूर्ण;
module_hid_driver(zp_driver);

MODULE_LICENSE("GPL");
