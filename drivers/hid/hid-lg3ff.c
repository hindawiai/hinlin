<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Force feedback support क्रम Logitech Flight System G940
 *
 *  Copyright (c) 2009 Gary Stein <LordCnidarian@gmail.com>
 */

/*
 */


#समावेश <linux/input.h>
#समावेश <linux/hid.h>

#समावेश "hid-lg.h"

/*
 * G940 Theory of Operation (from experimentation)
 *
 * There are 63 fields (only 3 of them currently used)
 * 0 - seems to be command field
 * 1 - 30 deal with the x axis
 * 31 -60 deal with the y axis
 *
 * Field 1 is x axis स्थिरant क्रमce
 * Field 31 is y axis स्थिरant क्रमce
 *
 * other पूर्णांकeresting fields 1,2,3,4 on x axis
 * (same क्रम 31,32,33,34 on y axis)
 *
 * 0 0 127 127 makes the joystick स्वतःcenter hard
 *
 * 127 0 127 127 makes the joystick loose on the right,
 * but stops all movemnt left
 *
 * -127 0 -127 -127 makes the joystick loose on the left,
 * but stops all movement right
 *
 * 0 0 -127 -127 makes the joystick rattle very hard
 *
 * I'm sure these are effects that I don't know enough about them
 */

काष्ठा lg3ff_device अणु
	काष्ठा hid_report *report;
पूर्ण;

अटल पूर्णांक hid_lg3ff_play(काष्ठा input_dev *dev, व्योम *data,
			 काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा list_head *report_list = &hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list;
	काष्ठा hid_report *report = list_entry(report_list->next, काष्ठा hid_report, list);
	पूर्णांक x, y;

/*
 * Available values in the field should always be 63, but we only use up to
 * 35. Instead, clear the entire area, however big it is.
 */
	स_रखो(report->field[0]->value, 0,
	       माप(__s32) * report->field[0]->report_count);

	चयन (effect->type) अणु
	हाल FF_CONSTANT:
/*
 * Alपढ़ोy clamped in ff_memless
 * 0 is center (dअगरferent then other logitech)
 */
		x = effect->u.ramp.start_level;
		y = effect->u.ramp.end_level;

		/* send command byte */
		report->field[0]->value[0] = 0x51;

/*
 * Sign backwards from other Force3d pro
 * which get recast here in two's complement 8 bits
 */
		report->field[0]->value[1] = (अचिन्हित अक्षर)(-x);
		report->field[0]->value[31] = (अचिन्हित अक्षर)(-y);

		hid_hw_request(hid, report, HID_REQ_SET_REPORT);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
अटल व्योम hid_lg3ff_set_स्वतःcenter(काष्ठा input_dev *dev, u16 magnitude)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा list_head *report_list = &hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list;
	काष्ठा hid_report *report = list_entry(report_list->next, काष्ठा hid_report, list);

/*
 * Auto Centering probed from device
 * NOTE: deadman's चयन on G940 must be covered
 * क्रम effects to work
 */
	report->field[0]->value[0] = 0x51;
	report->field[0]->value[1] = 0x00;
	report->field[0]->value[2] = 0x00;
	report->field[0]->value[3] = 0x7F;
	report->field[0]->value[4] = 0x7F;
	report->field[0]->value[31] = 0x00;
	report->field[0]->value[32] = 0x00;
	report->field[0]->value[33] = 0x7F;
	report->field[0]->value[34] = 0x7F;

	hid_hw_request(hid, report, HID_REQ_SET_REPORT);
पूर्ण


अटल स्थिर चिन्हित लघु ff3_joystick_ac[] = अणु
	FF_CONSTANT,
	FF_AUTOCENTER,
	-1
पूर्ण;

पूर्णांक lg3ff_init(काष्ठा hid_device *hid)
अणु
	काष्ठा hid_input *hidinput;
	काष्ठा input_dev *dev;
	स्थिर चिन्हित लघु *ff_bits = ff3_joystick_ac;
	पूर्णांक error;
	पूर्णांक i;

	अगर (list_empty(&hid->inमाला_दो)) अणु
		hid_err(hid, "no inputs found\n");
		वापस -ENODEV;
	पूर्ण
	hidinput = list_entry(hid->inमाला_दो.next, काष्ठा hid_input, list);
	dev = hidinput->input;

	/* Check that the report looks ok */
	अगर (!hid_validate_values(hid, HID_OUTPUT_REPORT, 0, 0, 35))
		वापस -ENODEV;

	/* Assume single fixed device G940 */
	क्रम (i = 0; ff_bits[i] >= 0; i++)
		set_bit(ff_bits[i], dev->ffbit);

	error = input_ff_create_memless(dev, शून्य, hid_lg3ff_play);
	अगर (error)
		वापस error;

	अगर (test_bit(FF_AUTOCENTER, dev->ffbit))
		dev->ff->set_स्वतःcenter = hid_lg3ff_set_स्वतःcenter;

	hid_info(hid, "Force feedback for Logitech Flight System G940 by Gary Stein <LordCnidarian@gmail.com>\n");
	वापस 0;
पूर्ण

