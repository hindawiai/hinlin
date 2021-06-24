<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Force feedback support क्रम various HID compliant devices by ThrustMaster:
 *    ThrustMaster FireStorm Dual Power 2
 * and possibly others whose device ids haven't been added.
 *
 *  Modअगरied to support ThrustMaster devices by Zinx Verituse
 *  on 2003-01-25 from the Logitech क्रमce feedback driver,
 *  which is by Johann Deneux.
 *
 *  Copyright (c) 2003 Zinx Verituse <zinx@epicsol.org>
 *  Copyright (c) 2002 Johann Deneux
 */

/*
 */

#समावेश <linux/hid.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#घोषणा THRUSTMASTER_DEVICE_ID_2_IN_1_DT	0xb320

अटल स्थिर चिन्हित लघु ff_rumble[] = अणु
	FF_RUMBLE,
	-1
पूर्ण;

अटल स्थिर चिन्हित लघु ff_joystick[] = अणु
	FF_CONSTANT,
	-1
पूर्ण;

#अगर_घोषित CONFIG_THRUSTMASTER_FF

/* Usages क्रम thrusपंचांगaster devices I know about */
#घोषणा THRUSTMASTER_USAGE_FF	(HID_UP_GENDESK | 0xbb)

काष्ठा पंचांगff_device अणु
	काष्ठा hid_report *report;
	काष्ठा hid_field *ff_field;
पूर्ण;

/* Changes values from 0 to 0xffff पूर्णांकo values from minimum to maximum */
अटल अंतरभूत पूर्णांक पंचांगff_scale_u16(अचिन्हित पूर्णांक in, पूर्णांक minimum, पूर्णांक maximum)
अणु
	पूर्णांक ret;

	ret = (in * (maximum - minimum) / 0xffff) + minimum;
	अगर (ret < minimum)
		वापस minimum;
	अगर (ret > maximum)
		वापस maximum;
	वापस ret;
पूर्ण

/* Changes values from -0x80 to 0x7f पूर्णांकo values from minimum to maximum */
अटल अंतरभूत पूर्णांक पंचांगff_scale_s8(पूर्णांक in, पूर्णांक minimum, पूर्णांक maximum)
अणु
	पूर्णांक ret;

	ret = (((in + 0x80) * (maximum - minimum)) / 0xff) + minimum;
	अगर (ret < minimum)
		वापस minimum;
	अगर (ret > maximum)
		वापस maximum;
	वापस ret;
पूर्ण

अटल पूर्णांक पंचांगff_play(काष्ठा input_dev *dev, व्योम *data,
		काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा पंचांगff_device *पंचांगff = data;
	काष्ठा hid_field *ff_field = पंचांगff->ff_field;
	पूर्णांक x, y;
	पूर्णांक left, right;	/* Rumbling */
	पूर्णांक motor_swap;

	चयन (effect->type) अणु
	हाल FF_CONSTANT:
		x = पंचांगff_scale_s8(effect->u.ramp.start_level,
					ff_field->logical_minimum,
					ff_field->logical_maximum);
		y = पंचांगff_scale_s8(effect->u.ramp.end_level,
					ff_field->logical_minimum,
					ff_field->logical_maximum);

		dbg_hid("(x, y)=(%04x, %04x)\n", x, y);
		ff_field->value[0] = x;
		ff_field->value[1] = y;
		hid_hw_request(hid, पंचांगff->report, HID_REQ_SET_REPORT);
		अवरोध;

	हाल FF_RUMBLE:
		left = पंचांगff_scale_u16(effect->u.rumble.weak_magnitude,
					ff_field->logical_minimum,
					ff_field->logical_maximum);
		right = पंचांगff_scale_u16(effect->u.rumble.strong_magnitude,
					ff_field->logical_minimum,
					ff_field->logical_maximum);

		/* 2-in-1 strong motor is left */
		अगर (hid->product == THRUSTMASTER_DEVICE_ID_2_IN_1_DT) अणु
			motor_swap = left;
			left = right;
			right = motor_swap;
		पूर्ण

		dbg_hid("(left,right)=(%08x, %08x)\n", left, right);
		ff_field->value[0] = left;
		ff_field->value[1] = right;
		hid_hw_request(hid, पंचांगff->report, HID_REQ_SET_REPORT);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगff_init(काष्ठा hid_device *hid, स्थिर चिन्हित लघु *ff_bits)
अणु
	काष्ठा पंचांगff_device *पंचांगff;
	काष्ठा hid_report *report;
	काष्ठा list_head *report_list;
	काष्ठा hid_input *hidinput;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;
	पूर्णांक i;

	अगर (list_empty(&hid->inमाला_दो)) अणु
		hid_err(hid, "no inputs found\n");
		वापस -ENODEV;
	पूर्ण
	hidinput = list_entry(hid->inमाला_दो.next, काष्ठा hid_input, list);
	input_dev = hidinput->input;

	पंचांगff = kzalloc(माप(काष्ठा पंचांगff_device), GFP_KERNEL);
	अगर (!पंचांगff)
		वापस -ENOMEM;

	/* Find the report to use */
	report_list = &hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list;
	list_क्रम_each_entry(report, report_list, list) अणु
		पूर्णांक fieldnum;

		क्रम (fieldnum = 0; fieldnum < report->maxfield; ++fieldnum) अणु
			काष्ठा hid_field *field = report->field[fieldnum];

			अगर (field->maxusage <= 0)
				जारी;

			चयन (field->usage[0].hid) अणु
			हाल THRUSTMASTER_USAGE_FF:
				अगर (field->report_count < 2) अणु
					hid_warn(hid, "ignoring FF field with report_count < 2\n");
					जारी;
				पूर्ण

				अगर (field->logical_maximum ==
						field->logical_minimum) अणु
					hid_warn(hid, "ignoring FF field with logical_maximum == logical_minimum\n");
					जारी;
				पूर्ण

				अगर (पंचांगff->report && पंचांगff->report != report) अणु
					hid_warn(hid, "ignoring FF field in other report\n");
					जारी;
				पूर्ण

				अगर (पंचांगff->ff_field && पंचांगff->ff_field != field) अणु
					hid_warn(hid, "ignoring duplicate FF field\n");
					जारी;
				पूर्ण

				पंचांगff->report = report;
				पंचांगff->ff_field = field;

				क्रम (i = 0; ff_bits[i] >= 0; i++)
					set_bit(ff_bits[i], input_dev->ffbit);

				अवरोध;

			शेष:
				hid_warn(hid, "ignoring unknown output usage %08x\n",
					 field->usage[0].hid);
				जारी;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!पंचांगff->report) अणु
		hid_err(hid, "can't find FF field in output reports\n");
		error = -ENODEV;
		जाओ fail;
	पूर्ण

	error = input_ff_create_memless(input_dev, पंचांगff, पंचांगff_play);
	अगर (error)
		जाओ fail;

	hid_info(hid, "force feedback for ThrustMaster devices by Zinx Verituse <zinx@epicsol.org>\n");
	वापस 0;

fail:
	kमुक्त(पंचांगff);
	वापस error;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक पंचांगff_init(काष्ठा hid_device *hid, स्थिर चिन्हित लघु *ff_bits)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक पंचांग_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
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

	पंचांगff_init(hdev, (व्योम *)id->driver_data);

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id पंचांग_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_THRUSTMASTER, 0xb300),
		.driver_data = (अचिन्हित दीर्घ)ff_rumble पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_THRUSTMASTER, 0xb304),   /* FireStorm Dual Power 2 (and 3) */
		.driver_data = (अचिन्हित दीर्घ)ff_rumble पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_THRUSTMASTER, THRUSTMASTER_DEVICE_ID_2_IN_1_DT),   /* Dual Trigger 2-in-1 */
		.driver_data = (अचिन्हित दीर्घ)ff_rumble पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_THRUSTMASTER, 0xb323),   /* Dual Trigger 3-in-1 (PC Mode) */
		.driver_data = (अचिन्हित दीर्घ)ff_rumble पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_THRUSTMASTER, 0xb324),   /* Dual Trigger 3-in-1 (PS3 Mode) */
		.driver_data = (अचिन्हित दीर्घ)ff_rumble पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_THRUSTMASTER, 0xb605),   /* NASCAR PRO FF2 Wheel */
		.driver_data = (अचिन्हित दीर्घ)ff_joystick पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_THRUSTMASTER, 0xb651),	/* FGT Rumble Force Wheel */
		.driver_data = (अचिन्हित दीर्घ)ff_rumble पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_THRUSTMASTER, 0xb653),	/* RGT Force Feedback CLUTCH Raging Wheel */
		.driver_data = (अचिन्हित दीर्घ)ff_joystick पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_THRUSTMASTER, 0xb654),	/* FGT Force Feedback Wheel */
		.driver_data = (अचिन्हित दीर्घ)ff_joystick पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_THRUSTMASTER, 0xb65a),	/* F430 Force Feedback Wheel */
		.driver_data = (अचिन्हित दीर्घ)ff_joystick पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, पंचांग_devices);

अटल काष्ठा hid_driver पंचांग_driver = अणु
	.name = "thrustmaster",
	.id_table = पंचांग_devices,
	.probe = पंचांग_probe,
पूर्ण;
module_hid_driver(पंचांग_driver);

MODULE_LICENSE("GPL");
