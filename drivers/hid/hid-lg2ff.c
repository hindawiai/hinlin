<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Force feedback support क्रम Logitech RumblePad and Rumblepad 2
 *
 *  Copyright (c) 2008 Anssi Hannula <anssi.hannula@gmail.com>
 */

/*
 */


#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/hid.h>

#समावेश "hid-lg.h"

काष्ठा lg2ff_device अणु
	काष्ठा hid_report *report;
पूर्ण;

अटल पूर्णांक play_effect(काष्ठा input_dev *dev, व्योम *data,
			 काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा lg2ff_device *lg2ff = data;
	पूर्णांक weak, strong;

	strong = effect->u.rumble.strong_magnitude;
	weak = effect->u.rumble.weak_magnitude;

	अगर (weak || strong) अणु
		weak = weak * 0xff / 0xffff;
		strong = strong * 0xff / 0xffff;

		lg2ff->report->field[0]->value[0] = 0x51;
		lg2ff->report->field[0]->value[2] = weak;
		lg2ff->report->field[0]->value[4] = strong;
	पूर्ण अन्यथा अणु
		lg2ff->report->field[0]->value[0] = 0xf3;
		lg2ff->report->field[0]->value[2] = 0x00;
		lg2ff->report->field[0]->value[4] = 0x00;
	पूर्ण

	hid_hw_request(hid, lg2ff->report, HID_REQ_SET_REPORT);
	वापस 0;
पूर्ण

पूर्णांक lg2ff_init(काष्ठा hid_device *hid)
अणु
	काष्ठा lg2ff_device *lg2ff;
	काष्ठा hid_report *report;
	काष्ठा hid_input *hidinput;
	काष्ठा input_dev *dev;
	पूर्णांक error;

	अगर (list_empty(&hid->inमाला_दो)) अणु
		hid_err(hid, "no inputs found\n");
		वापस -ENODEV;
	पूर्ण
	hidinput = list_entry(hid->inमाला_दो.next, काष्ठा hid_input, list);
	dev = hidinput->input;

	/* Check that the report looks ok */
	report = hid_validate_values(hid, HID_OUTPUT_REPORT, 0, 0, 7);
	अगर (!report)
		वापस -ENODEV;

	lg2ff = kदो_स्मृति(माप(काष्ठा lg2ff_device), GFP_KERNEL);
	अगर (!lg2ff)
		वापस -ENOMEM;

	set_bit(FF_RUMBLE, dev->ffbit);

	error = input_ff_create_memless(dev, lg2ff, play_effect);
	अगर (error) अणु
		kमुक्त(lg2ff);
		वापस error;
	पूर्ण

	lg2ff->report = report;
	report->field[0]->value[0] = 0xf3;
	report->field[0]->value[1] = 0x00;
	report->field[0]->value[2] = 0x00;
	report->field[0]->value[3] = 0x00;
	report->field[0]->value[4] = 0x00;
	report->field[0]->value[5] = 0x00;
	report->field[0]->value[6] = 0x00;

	hid_hw_request(hid, report, HID_REQ_SET_REPORT);

	hid_info(hid, "Force feedback for Logitech variant 2 rumble devices by Anssi Hannula <anssi.hannula@gmail.com>\n");

	वापस 0;
पूर्ण
