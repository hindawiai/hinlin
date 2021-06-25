<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Force feedback support क्रम PantherLord/GreenAsia based devices
 *
 *  The devices are distributed under various names and the same USB device ID
 *  can be used in both adapters and actual game controllers.
 *
 *  0810:0001 "Twin USB Joystick"
 *   - tested with PantherLord USB/PS2 2in1 Adapter
 *   - contains two reports, one क्रम each port (HID_QUIRK_MULTI_INPUT)
 *
 *  0e8f:0003 "GreenAsia Inc.    USB Joystick     "
 *   - tested with Kथघnig Gaming gamepad
 *
 *  0e8f:0003 "GASIA USB Gamepad"
 *   - another version of the Kथघnig gamepad
 *
 *  0f30:0111 "Saitek Color Rumble Pad"
 *
 *  Copyright (c) 2007, 2009 Anssi Hannula <anssi.hannula@gmail.com>
 */

/*
 */


/* #घोषणा DEBUG */

#घोषणा debug(क्रमmat, arg...) pr_debug("hid-plff: " क्रमmat "\n" , ## arg)

#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/hid.h>

#समावेश "hid-ids.h"

#अगर_घोषित CONFIG_PANTHERLORD_FF

काष्ठा plff_device अणु
	काष्ठा hid_report *report;
	s32 maxval;
	s32 *strong;
	s32 *weak;
पूर्ण;

अटल पूर्णांक hid_plff_play(काष्ठा input_dev *dev, व्योम *data,
			 काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा plff_device *plff = data;
	पूर्णांक left, right;

	left = effect->u.rumble.strong_magnitude;
	right = effect->u.rumble.weak_magnitude;
	debug("called with 0x%04x 0x%04x", left, right);

	left = left * plff->maxval / 0xffff;
	right = right * plff->maxval / 0xffff;

	*plff->strong = left;
	*plff->weak = right;
	debug("running with 0x%02x 0x%02x", left, right);
	hid_hw_request(hid, plff->report, HID_REQ_SET_REPORT);

	वापस 0;
पूर्ण

अटल पूर्णांक plff_init(काष्ठा hid_device *hid)
अणु
	काष्ठा plff_device *plff;
	काष्ठा hid_report *report;
	काष्ठा hid_input *hidinput;
	काष्ठा list_head *report_list =
			&hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list;
	काष्ठा list_head *report_ptr = report_list;
	काष्ठा input_dev *dev;
	पूर्णांक error;
	s32 maxval;
	s32 *strong;
	s32 *weak;

	/* The device contains one output report per physical device, all
	   containing 1 field, which contains 4 ff00.0002 usages and 4 16bit
	   असलolute values.

	   The input reports also contain a field which contains
	   8 ff00.0001 usages and 8 boolean values. Their meaning is
	   currently unknown.
	   
	   A version of the 0e8f:0003 exists that has all the values in
	   separate fields and misses the extra input field, thus resembling
	   Zeroplus (hid-zpff) devices.
	*/

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

		maxval = 0x7f;
		अगर (report->field[0]->report_count >= 4) अणु
			report->field[0]->value[0] = 0x00;
			report->field[0]->value[1] = 0x00;
			strong = &report->field[0]->value[2];
			weak = &report->field[0]->value[3];
			debug("detected single-field device");
		पूर्ण अन्यथा अगर (report->field[0]->maxusage == 1 &&
			   report->field[0]->usage[0].hid ==
				(HID_UP_LED | 0x43) &&
			   report->maxfield >= 4 &&
			   report->field[0]->report_count >= 1 &&
			   report->field[1]->report_count >= 1 &&
			   report->field[2]->report_count >= 1 &&
			   report->field[3]->report_count >= 1) अणु
			report->field[0]->value[0] = 0x00;
			report->field[1]->value[0] = 0x00;
			strong = &report->field[2]->value[0];
			weak = &report->field[3]->value[0];
			अगर (hid->venकरोr == USB_VENDOR_ID_JESS2)
				maxval = 0xff;
			debug("detected 4-field device");
		पूर्ण अन्यथा अणु
			hid_err(hid, "not enough fields or values\n");
			वापस -ENODEV;
		पूर्ण

		plff = kzalloc(माप(काष्ठा plff_device), GFP_KERNEL);
		अगर (!plff)
			वापस -ENOMEM;

		dev = hidinput->input;

		set_bit(FF_RUMBLE, dev->ffbit);

		error = input_ff_create_memless(dev, plff, hid_plff_play);
		अगर (error) अणु
			kमुक्त(plff);
			वापस error;
		पूर्ण

		plff->report = report;
		plff->strong = strong;
		plff->weak = weak;
		plff->maxval = maxval;

		*strong = 0x00;
		*weak = 0x00;
		hid_hw_request(hid, plff->report, HID_REQ_SET_REPORT);
	पूर्ण

	hid_info(hid, "Force feedback for PantherLord/GreenAsia devices by Anssi Hannula <anssi.hannula@gmail.com>\n");

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक plff_init(काष्ठा hid_device *hid)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pl_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
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

	plff_init(hdev);

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id pl_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_GAMERON, USB_DEVICE_ID_GAMERON_DUAL_PSX_ADAPTOR),
		.driver_data = 1 पूर्ण, /* Twin USB Joystick */
	अणु HID_USB_DEVICE(USB_VENDOR_ID_GAMERON, USB_DEVICE_ID_GAMERON_DUAL_PCS_ADAPTOR),
		.driver_data = 1 पूर्ण, /* Twin USB Joystick */
	अणु HID_USB_DEVICE(USB_VENDOR_ID_GREENASIA, 0x0003), पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_JESS2, USB_DEVICE_ID_JESS2_COLOR_RUMBLE_PAD), पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, pl_devices);

अटल काष्ठा hid_driver pl_driver = अणु
	.name = "pantherlord",
	.id_table = pl_devices,
	.probe = pl_probe,
पूर्ण;
module_hid_driver(pl_driver);

MODULE_LICENSE("GPL");
