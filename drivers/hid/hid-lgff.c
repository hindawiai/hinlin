<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Force feedback support क्रम hid-compliant क्रम some of the devices from
 * Logitech, namely:
 * - WingMan Cordless RumblePad
 * - WingMan Force 3D
 *
 *  Copyright (c) 2002-2004 Johann Deneux
 *  Copyright (c) 2006 Anssi Hannula <anssi.hannula@gmail.com>
 */

/*
 *
 * Should you need to contact me, the author, you can करो so by
 * e-mail - mail your message to <johann.deneux@it.uu.se>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/input.h>
#समावेश <linux/hid.h>

#समावेश "hid-lg.h"

काष्ठा dev_type अणु
	u16 idVenकरोr;
	u16 idProduct;
	स्थिर चिन्हित लघु *ff;
पूर्ण;

अटल स्थिर चिन्हित लघु ff_rumble[] = अणु
	FF_RUMBLE,
	-1
पूर्ण;

अटल स्थिर चिन्हित लघु ff_joystick[] = अणु
	FF_CONSTANT,
	-1
पूर्ण;

अटल स्थिर चिन्हित लघु ff_joystick_ac[] = अणु
	FF_CONSTANT,
	FF_AUTOCENTER,
	-1
पूर्ण;

अटल स्थिर काष्ठा dev_type devices[] = अणु
	अणु 0x046d, 0xc211, ff_rumble पूर्ण,
	अणु 0x046d, 0xc219, ff_rumble पूर्ण,
	अणु 0x046d, 0xc283, ff_joystick पूर्ण,
	अणु 0x046d, 0xc286, ff_joystick_ac पूर्ण,
	अणु 0x046d, 0xc287, ff_joystick_ac पूर्ण,
	अणु 0x046d, 0xc293, ff_joystick पूर्ण,
	अणु 0x046d, 0xc295, ff_joystick पूर्ण,
पूर्ण;

अटल पूर्णांक hid_lgff_play(काष्ठा input_dev *dev, व्योम *data, काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा list_head *report_list = &hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list;
	काष्ठा hid_report *report = list_entry(report_list->next, काष्ठा hid_report, list);
	पूर्णांक x, y;
	अचिन्हित पूर्णांक left, right;

#घोषणा CLAMP(x) अगर (x < 0) x = 0; अगर (x > 0xff) x = 0xff

	चयन (effect->type) अणु
	हाल FF_CONSTANT:
		x = effect->u.ramp.start_level + 0x7f;	/* 0x7f is center */
		y = effect->u.ramp.end_level + 0x7f;
		CLAMP(x);
		CLAMP(y);
		report->field[0]->value[0] = 0x51;
		report->field[0]->value[1] = 0x08;
		report->field[0]->value[2] = x;
		report->field[0]->value[3] = y;
		dbg_hid("(x, y)=(%04x, %04x)\n", x, y);
		hid_hw_request(hid, report, HID_REQ_SET_REPORT);
		अवरोध;

	हाल FF_RUMBLE:
		right = effect->u.rumble.strong_magnitude;
		left = effect->u.rumble.weak_magnitude;
		right = right * 0xff / 0xffff;
		left = left * 0xff / 0xffff;
		CLAMP(left);
		CLAMP(right);
		report->field[0]->value[0] = 0x42;
		report->field[0]->value[1] = 0x00;
		report->field[0]->value[2] = left;
		report->field[0]->value[3] = right;
		dbg_hid("(left, right)=(%04x, %04x)\n", left, right);
		hid_hw_request(hid, report, HID_REQ_SET_REPORT);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hid_lgff_set_स्वतःcenter(काष्ठा input_dev *dev, u16 magnitude)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा list_head *report_list = &hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list;
	काष्ठा hid_report *report = list_entry(report_list->next, काष्ठा hid_report, list);
	__s32 *value = report->field[0]->value;
	magnitude = (magnitude >> 12) & 0xf;
	*value++ = 0xfe;
	*value++ = 0x0d;
	*value++ = magnitude;   /* घड़ीwise strength */
	*value++ = magnitude;   /* counter-घड़ीwise strength */
	*value++ = 0x80;
	*value++ = 0x00;
	*value = 0x00;
	hid_hw_request(hid, report, HID_REQ_SET_REPORT);
पूर्ण

पूर्णांक lgff_init(काष्ठा hid_device* hid)
अणु
	काष्ठा hid_input *hidinput;
	काष्ठा input_dev *dev;
	स्थिर चिन्हित लघु *ff_bits = ff_joystick;
	पूर्णांक error;
	पूर्णांक i;

	अगर (list_empty(&hid->inमाला_दो)) अणु
		hid_err(hid, "no inputs found\n");
		वापस -ENODEV;
	पूर्ण
	hidinput = list_entry(hid->inमाला_दो.next, काष्ठा hid_input, list);
	dev = hidinput->input;

	/* Check that the report looks ok */
	अगर (!hid_validate_values(hid, HID_OUTPUT_REPORT, 0, 0, 7))
		वापस -ENODEV;

	क्रम (i = 0; i < ARRAY_SIZE(devices); i++) अणु
		अगर (dev->id.venकरोr == devices[i].idVenकरोr &&
		    dev->id.product == devices[i].idProduct) अणु
			ff_bits = devices[i].ff;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; ff_bits[i] >= 0; i++)
		set_bit(ff_bits[i], dev->ffbit);

	error = input_ff_create_memless(dev, शून्य, hid_lgff_play);
	अगर (error)
		वापस error;

	अगर ( test_bit(FF_AUTOCENTER, dev->ffbit) )
		dev->ff->set_स्वतःcenter = hid_lgff_set_स्वतःcenter;

	pr_info("Force feedback for Logitech force feedback devices by Johann Deneux <johann.deneux@it.uu.se>\n");

	वापस 0;
पूर्ण
