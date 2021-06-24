<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Force feedback support क्रम Holtek On Line Grip based gamepads
 *
 *  These include at least a Brazilian "Clone Joypad Super Power Fire"
 *  which uses venकरोr ID 0x1241 and identअगरies as "HOLTEK On Line Grip".
 *
 *  Copyright (c) 2011 Anssi Hannula <anssi.hannula@iki.fi>
 */

/*
 */

#समावेश <linux/hid.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "hid-ids.h"

#अगर_घोषित CONFIG_HOLTEK_FF

/*
 * These commands and parameters are currently known:
 *
 * byte 0: command id:
 * 	01  set effect parameters
 * 	02  play specअगरied effect
 * 	03  stop specअगरied effect
 * 	04  stop all effects
 * 	06  stop all effects
 * 	(the dअगरference between 04 and 06 isn't known; win driver
 * 	 sends 06,04 on application init, and 06 otherwise)
 * 
 * Commands 01 and 02 need to be sent as pairs, i.e. you need to send 01
 * beक्रमe each 02.
 *
 * The rest of the bytes are parameters. Command 01 takes all of them, and
 * commands 02,03 take only the effect id.
 *
 * byte 1:
 *	bits 0-3: effect id:
 * 		1: very strong rumble
 * 		2: periodic rumble, लघु पूर्णांकervals
 * 		3: very strong rumble
 * 		4: periodic rumble, दीर्घ पूर्णांकervals
 * 		5: weak periodic rumble, दीर्घ पूर्णांकervals
 * 		6: weak periodic rumble, लघु पूर्णांकervals
 * 		7: periodic rumble, लघु पूर्णांकervals
 * 		8: strong periodic rumble, लघु पूर्णांकervals
 * 		9: very strong rumble
 * 		a: causes an error
 * 		b: very strong periodic rumble, very लघु पूर्णांकervals
 * 		c-f: nothing
 *	bit 6: right (weak) motor enabled
 *	bit 7: left (strong) motor enabled
 *
 * bytes 2-3:  समय in milliseconds, big-endian
 * bytes 5-6:  unknown (win driver seems to use at least 10e0 with effect 1
 * 		       and 0014 with effect 6)
 * byte 7:
 *	bits 0-3: effect magnitude
 */

#घोषणा HOLTEKFF_MSG_LENGTH     7

अटल स्थिर u8 start_effect_1[] = अणु 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
अटल स्थिर u8 stop_all4[] =	   अणु 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
अटल स्थिर u8 stop_all6[] =	   अणु 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;

काष्ठा holtekff_device अणु
	काष्ठा hid_field *field;
पूर्ण;

अटल व्योम holtekff_send(काष्ठा holtekff_device *holtekff,
			  काष्ठा hid_device *hid,
			  स्थिर u8 data[HOLTEKFF_MSG_LENGTH])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HOLTEKFF_MSG_LENGTH; i++) अणु
		holtekff->field->value[i] = data[i];
	पूर्ण

	dbg_hid("sending %7ph\n", data);

	hid_hw_request(hid, holtekff->field->report, HID_REQ_SET_REPORT);
पूर्ण

अटल पूर्णांक holtekff_play(काष्ठा input_dev *dev, व्योम *data,
			 काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा holtekff_device *holtekff = data;
	पूर्णांक left, right;
	/* effect type 1, length 65535 msec */
	u8 buf[HOLTEKFF_MSG_LENGTH] =
		अणु 0x01, 0x01, 0xff, 0xff, 0x10, 0xe0, 0x00 पूर्ण;

	left = effect->u.rumble.strong_magnitude;
	right = effect->u.rumble.weak_magnitude;
	dbg_hid("called with 0x%04x 0x%04x\n", left, right);

	अगर (!left && !right) अणु
		holtekff_send(holtekff, hid, stop_all6);
		वापस 0;
	पूर्ण

	अगर (left)
		buf[1] |= 0x80;
	अगर (right)
		buf[1] |= 0x40;

	/* The device takes a single magnitude, so we just sum them up. */
	buf[6] = min(0xf, (left >> 12) + (right >> 12));

	holtekff_send(holtekff, hid, buf);
	holtekff_send(holtekff, hid, start_effect_1);

	वापस 0;
पूर्ण

अटल पूर्णांक holtekff_init(काष्ठा hid_device *hid)
अणु
	काष्ठा holtekff_device *holtekff;
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
	hidinput = list_entry(hid->inमाला_दो.next, काष्ठा hid_input, list);
	dev = hidinput->input;

	अगर (list_empty(report_list)) अणु
		hid_err(hid, "no output report found\n");
		वापस -ENODEV;
	पूर्ण

	report = list_entry(report_list->next, काष्ठा hid_report, list);

	अगर (report->maxfield < 1 || report->field[0]->report_count != 7) अणु
		hid_err(hid, "unexpected output report layout\n");
		वापस -ENODEV;
	पूर्ण

	holtekff = kzalloc(माप(*holtekff), GFP_KERNEL);
	अगर (!holtekff)
		वापस -ENOMEM;

	set_bit(FF_RUMBLE, dev->ffbit);

	holtekff->field = report->field[0];

	/* initialize the same way as win driver करोes */
	holtekff_send(holtekff, hid, stop_all4);
	holtekff_send(holtekff, hid, stop_all6);

	error = input_ff_create_memless(dev, holtekff, holtekff_play);
	अगर (error) अणु
		kमुक्त(holtekff);
		वापस error;
	पूर्ण

	hid_info(hid, "Force feedback for Holtek On Line Grip based devices by Anssi Hannula <anssi.hannula@iki.fi>\n");

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक holtekff_init(काष्ठा hid_device *hid)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक holtek_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
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

	holtekff_init(hdev);

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id holtek_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_HOLTEK, USB_DEVICE_ID_HOLTEK_ON_LINE_GRIP) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, holtek_devices);

अटल काष्ठा hid_driver holtek_driver = अणु
	.name = "holtek",
	.id_table = holtek_devices,
	.probe = holtek_probe,
पूर्ण;
module_hid_driver(holtek_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anssi Hannula <anssi.hannula@iki.fi>");
MODULE_DESCRIPTION("Force feedback support for Holtek On Line Grip based devices");
