<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Force feedback support क्रम Mayflash game controller adapters.
 *
 * These devices are manufactured by Mayflash but identअगरy themselves
 * using the venकरोr ID of DragonRise Inc.
 *
 * Tested with:
 * 0079:1801 "DragonRise Inc. Mayflash PS3 Game Controller Adapter"
 * 0079:1803 "DragonRise Inc. Mayflash Wireless Sensor DolphinBar"
 * 0079:1843 "DragonRise Inc. Mayflash GameCube Game Controller Adapter"
 * 0079:1844 "DragonRise Inc. Mayflash GameCube Game Controller Adapter (v04)"
 *
 * The following adapters probably work too, but need to be tested:
 * 0079:1800 "DragonRise Inc. Mayflash WIIU Game Controller Adapter"
 *
 * Copyright (c) 2016-2017 Marcel Hasler <mahasler@gmail.com>
 */

/*
 */

#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

काष्ठा mf_device अणु
	काष्ठा hid_report *report;
पूर्ण;

अटल पूर्णांक mf_play(काष्ठा input_dev *dev, व्योम *data, काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा mf_device *mf = data;
	पूर्णांक strong, weak;

	strong = effect->u.rumble.strong_magnitude;
	weak = effect->u.rumble.weak_magnitude;

	dbg_hid("Called with 0x%04x 0x%04x.\n", strong, weak);

	strong = strong * 0xff / 0xffff;
	weak = weak * 0xff / 0xffff;

	dbg_hid("Running with 0x%02x 0x%02x.\n", strong, weak);

	mf->report->field[0]->value[0] = weak;
	mf->report->field[0]->value[1] = strong;
	hid_hw_request(hid, mf->report, HID_REQ_SET_REPORT);

	वापस 0;
पूर्ण

अटल पूर्णांक mf_init(काष्ठा hid_device *hid)
अणु
	काष्ठा mf_device *mf;

	काष्ठा list_head *report_list =
			&hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list;

	काष्ठा list_head *report_ptr;
	काष्ठा hid_report *report;

	काष्ठा list_head *input_ptr = &hid->inमाला_दो;
	काष्ठा hid_input *input;

	काष्ठा input_dev *dev;

	पूर्णांक error;

	/* Setup each of the four inमाला_दो */
	list_क्रम_each(report_ptr, report_list) अणु
		report = list_entry(report_ptr, काष्ठा hid_report, list);

		अगर (report->maxfield < 1 || report->field[0]->report_count < 2) अणु
			hid_err(hid, "Invalid report, this should never happen!\n");
			वापस -ENODEV;
		पूर्ण

		अगर (list_is_last(input_ptr, &hid->inमाला_दो)) अणु
			hid_err(hid, "Missing input, this should never happen!\n");
			वापस -ENODEV;
		पूर्ण

		input_ptr = input_ptr->next;
		input = list_entry(input_ptr, काष्ठा hid_input, list);

		mf = kzalloc(माप(काष्ठा mf_device), GFP_KERNEL);
		अगर (!mf)
			वापस -ENOMEM;

		dev = input->input;
		set_bit(FF_RUMBLE, dev->ffbit);

		error = input_ff_create_memless(dev, mf, mf_play);
		अगर (error) अणु
			kमुक्त(mf);
			वापस error;
		पूर्ण

		mf->report = report;
		mf->report->field[0]->value[0] = 0x00;
		mf->report->field[0]->value[1] = 0x00;
		hid_hw_request(hid, mf->report, HID_REQ_SET_REPORT);
	पूर्ण

	hid_info(hid, "Force feedback for HJZ Mayflash game controller "
		      "adapters by Marcel Hasler <mahasler@gmail.com>\n");

	वापस 0;
पूर्ण

अटल पूर्णांक mf_probe(काष्ठा hid_device *hid, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक error;

	dev_dbg(&hid->dev, "Mayflash HID hardware probe...\n");

	/* Apply quirks as needed */
	hid->quirks |= id->driver_data;

	error = hid_parse(hid);
	अगर (error) अणु
		hid_err(hid, "HID parse failed.\n");
		वापस error;
	पूर्ण

	error = hid_hw_start(hid, HID_CONNECT_DEFAULT & ~HID_CONNECT_FF);
	अगर (error) अणु
		hid_err(hid, "HID hw start failed\n");
		वापस error;
	पूर्ण

	error = mf_init(hid);
	अगर (error) अणु
		hid_err(hid, "Force feedback init failed.\n");
		hid_hw_stop(hid);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id mf_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_DRAGONRISE, USB_DEVICE_ID_DRAGONRISE_PS3),
		.driver_data = HID_QUIRK_MULTI_INPUT पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_DRAGONRISE, USB_DEVICE_ID_DRAGONRISE_DOLPHINBAR),
		.driver_data = HID_QUIRK_MULTI_INPUT पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_DRAGONRISE, USB_DEVICE_ID_DRAGONRISE_GAMECUBE1),
		.driver_data = HID_QUIRK_MULTI_INPUT पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_DRAGONRISE, USB_DEVICE_ID_DRAGONRISE_GAMECUBE2),
		.driver_data = 0 पूर्ण, /* No quirk required */
	अणु HID_USB_DEVICE(USB_VENDOR_ID_DRAGONRISE, USB_DEVICE_ID_DRAGONRISE_GAMECUBE3),
		.driver_data = HID_QUIRK_MULTI_INPUT पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, mf_devices);

अटल काष्ठा hid_driver mf_driver = अणु
	.name = "hid_mf",
	.id_table = mf_devices,
	.probe = mf_probe,
पूर्ण;
module_hid_driver(mf_driver);

MODULE_LICENSE("GPL");
