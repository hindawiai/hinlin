<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  HID driver क्रम UC-Logic devices not fully compliant with HID standard
 *
 *  Copyright (c) 2010-2014 Nikolai Kondrashov
 *  Copyright (c) 2013 Martin Rusko
 */

/*
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश "usbhid/usbhid.h"
#समावेश "hid-uclogic-params.h"

#समावेश "hid-ids.h"

/* Driver data */
काष्ठा uclogic_drvdata अणु
	/* Interface parameters */
	काष्ठा uclogic_params params;
	/* Poपूर्णांकer to the replacement report descriptor. शून्य अगर none. */
	__u8 *desc_ptr;
	/*
	 * Size of the replacement report descriptor.
	 * Only valid अगर desc_ptr is not शून्य
	 */
	अचिन्हित पूर्णांक desc_size;
	/* Pen input device */
	काष्ठा input_dev *pen_input;
	/* In-range समयr */
	काष्ठा समयr_list inrange_समयr;
	/* Last rotary encoder state, or U8_MAX क्रम none */
	u8 re_state;
पूर्ण;

/**
 * uclogic_inrange_समयout - handle pen in-range state समयout.
 * Emulate input events normally generated when pen goes out of range क्रम
 * tablets which करोn't report that.
 *
 * @t:	The समयr the समयout handler is attached to, stored in a काष्ठा
 *	uclogic_drvdata.
 */
अटल व्योम uclogic_inrange_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा uclogic_drvdata *drvdata = from_समयr(drvdata, t,
							inrange_समयr);
	काष्ठा input_dev *input = drvdata->pen_input;

	अगर (input == शून्य)
		वापस;
	input_report_असल(input, ABS_PRESSURE, 0);
	/* If BTN_TOUCH state is changing */
	अगर (test_bit(BTN_TOUCH, input->key)) अणु
		input_event(input, EV_MSC, MSC_SCAN,
				/* Digitizer Tip Switch usage */
				0xd0042);
		input_report_key(input, BTN_TOUCH, 0);
	पूर्ण
	input_report_key(input, BTN_TOOL_PEN, 0);
	input_sync(input);
पूर्ण

अटल __u8 *uclogic_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
					अचिन्हित पूर्णांक *rsize)
अणु
	काष्ठा uclogic_drvdata *drvdata = hid_get_drvdata(hdev);

	अगर (drvdata->desc_ptr != शून्य) अणु
		rdesc = drvdata->desc_ptr;
		*rsize = drvdata->desc_size;
	पूर्ण
	वापस rdesc;
पूर्ण

अटल पूर्णांक uclogic_input_mapping(काष्ठा hid_device *hdev,
				 काष्ठा hid_input *hi,
				 काष्ठा hid_field *field,
				 काष्ठा hid_usage *usage,
				 अचिन्हित दीर्घ **bit,
				 पूर्णांक *max)
अणु
	काष्ठा uclogic_drvdata *drvdata = hid_get_drvdata(hdev);
	काष्ठा uclogic_params *params = &drvdata->params;

	/* discard the unused pen पूर्णांकerface */
	अगर (params->pen_unused && (field->application == HID_DG_PEN))
		वापस -1;

	/* let hid-core decide what to करो */
	वापस 0;
पूर्ण

अटल पूर्णांक uclogic_input_configured(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hi)
अणु
	काष्ठा uclogic_drvdata *drvdata = hid_get_drvdata(hdev);
	काष्ठा uclogic_params *params = &drvdata->params;
	अक्षर *name;
	स्थिर अक्षर *suffix = शून्य;
	काष्ठा hid_field *field;
	माप_प्रकार len;

	/* no report associated (HID_QUIRK_MULTI_INPUT not set) */
	अगर (!hi->report)
		वापस 0;

	/*
	 * If this is the input corresponding to the pen report
	 * in need of tweaking.
	 */
	अगर (hi->report->id == params->pen.id) अणु
		/* Remember the input device so we can simulate events */
		drvdata->pen_input = hi->input;
	पूर्ण

	field = hi->report->field[0];

	चयन (field->application) अणु
	हाल HID_GD_KEYBOARD:
		suffix = "Keyboard";
		अवरोध;
	हाल HID_GD_MOUSE:
		suffix = "Mouse";
		अवरोध;
	हाल HID_GD_KEYPAD:
		suffix = "Pad";
		अवरोध;
	हाल HID_DG_PEN:
		suffix = "Pen";
		अवरोध;
	हाल HID_CP_CONSUMER_CONTROL:
		suffix = "Consumer Control";
		अवरोध;
	हाल HID_GD_SYSTEM_CONTROL:
		suffix = "System Control";
		अवरोध;
	पूर्ण

	अगर (suffix) अणु
		len = म_माप(hdev->name) + 2 + म_माप(suffix);
		name = devm_kzalloc(&hi->input->dev, len, GFP_KERNEL);
		अगर (name) अणु
			snम_लिखो(name, len, "%s %s", hdev->name, suffix);
			hi->input->name = name;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uclogic_probe(काष्ठा hid_device *hdev,
		स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक rc;
	काष्ठा uclogic_drvdata *drvdata = शून्य;
	bool params_initialized = false;

	/*
	 * libinput requires the pad पूर्णांकerface to be on a dअगरferent node
	 * than the pen, so use QUIRK_MULTI_INPUT क्रम all tablets.
	 */
	hdev->quirks |= HID_QUIRK_MULTI_INPUT;

	/* Allocate and assign driver data */
	drvdata = devm_kzalloc(&hdev->dev, माप(*drvdata), GFP_KERNEL);
	अगर (drvdata == शून्य) अणु
		rc = -ENOMEM;
		जाओ failure;
	पूर्ण
	समयr_setup(&drvdata->inrange_समयr, uclogic_inrange_समयout, 0);
	drvdata->re_state = U8_MAX;
	hid_set_drvdata(hdev, drvdata);

	/* Initialize the device and retrieve पूर्णांकerface parameters */
	rc = uclogic_params_init(&drvdata->params, hdev);
	अगर (rc != 0) अणु
		hid_err(hdev, "failed probing parameters: %d\n", rc);
		जाओ failure;
	पूर्ण
	params_initialized = true;
	hid_dbg(hdev, "parameters:\n" UCLOGIC_PARAMS_FMT_STR,
		UCLOGIC_PARAMS_FMT_ARGS(&drvdata->params));
	अगर (drvdata->params.invalid) अणु
		hid_info(hdev, "interface is invalid, ignoring\n");
		rc = -ENODEV;
		जाओ failure;
	पूर्ण

	/* Generate replacement report descriptor */
	rc = uclogic_params_get_desc(&drvdata->params,
				     &drvdata->desc_ptr,
				     &drvdata->desc_size);
	अगर (rc) अणु
		hid_err(hdev,
			"failed generating replacement report descriptor: %d\n",
			rc);
		जाओ failure;
	पूर्ण

	rc = hid_parse(hdev);
	अगर (rc) अणु
		hid_err(hdev, "parse failed\n");
		जाओ failure;
	पूर्ण

	rc = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (rc) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ failure;
	पूर्ण

	वापस 0;
failure:
	/* Assume "remove" might not be called अगर "probe" failed */
	अगर (params_initialized)
		uclogic_params_cleanup(&drvdata->params);
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक uclogic_resume(काष्ठा hid_device *hdev)
अणु
	पूर्णांक rc;
	काष्ठा uclogic_params params;

	/* Re-initialize the device, but discard parameters */
	rc = uclogic_params_init(&params, hdev);
	अगर (rc != 0)
		hid_err(hdev, "failed to re-initialize the device\n");
	अन्यथा
		uclogic_params_cleanup(&params);

	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक uclogic_raw_event(काष्ठा hid_device *hdev,
				काष्ठा hid_report *report,
				u8 *data, पूर्णांक size)
अणु
	काष्ठा uclogic_drvdata *drvdata = hid_get_drvdata(hdev);
	काष्ठा uclogic_params *params = &drvdata->params;

	/* Tweak pen reports, अगर necessary */
	अगर (!params->pen_unused &&
	    (report->type == HID_INPUT_REPORT) &&
	    (report->id == params->pen.id) &&
	    (size >= 2)) अणु
		/* If it's the "virtual" frame controls report */
		अगर (params->frame.id != 0 &&
		    data[1] & params->pen_frame_flag) अणु
			/* Change to भव frame controls report ID */
			data[0] = params->frame.id;
			वापस 0;
		पूर्ण
		/* If in-range reports are inverted */
		अगर (params->pen.inrange ==
			UCLOGIC_PARAMS_PEN_INRANGE_INVERTED) अणु
			/* Invert the in-range bit */
			data[1] ^= 0x40;
		पूर्ण
		/*
		 * If report contains fragmented high-resolution pen
		 * coordinates
		 */
		अगर (size >= 10 && params->pen.fragmented_hires) अणु
			u8 pressure_low_byte;
			u8 pressure_high_byte;

			/* Lअगरt pressure bytes */
			pressure_low_byte = data[6];
			pressure_high_byte = data[7];
			/*
			 * Move Y coord to make space क्रम high-order X
			 * coord byte
			 */
			data[6] = data[5];
			data[5] = data[4];
			/* Move high-order X coord byte */
			data[4] = data[8];
			/* Move high-order Y coord byte */
			data[7] = data[9];
			/* Place pressure bytes */
			data[8] = pressure_low_byte;
			data[9] = pressure_high_byte;
		पूर्ण
		/* If we need to emulate in-range detection */
		अगर (params->pen.inrange == UCLOGIC_PARAMS_PEN_INRANGE_NONE) अणु
			/* Set in-range bit */
			data[1] |= 0x40;
			/* (Re-)start in-range समयout */
			mod_समयr(&drvdata->inrange_समयr,
					jअगरfies + msecs_to_jअगरfies(100));
		पूर्ण
	पूर्ण

	/* Tweak frame control reports, अगर necessary */
	अगर ((report->type == HID_INPUT_REPORT) &&
	    (report->id == params->frame.id)) अणु
		/* If need to, and can, set pad device ID क्रम Wacom drivers */
		अगर (params->frame.dev_id_byte > 0 &&
		    params->frame.dev_id_byte < size) अणु
			data[params->frame.dev_id_byte] = 0xf;
		पूर्ण
		/* If need to, and can, पढ़ो rotary encoder state change */
		अगर (params->frame.re_lsb > 0 &&
		    params->frame.re_lsb / 8 < size) अणु
			अचिन्हित पूर्णांक byte = params->frame.re_lsb / 8;
			अचिन्हित पूर्णांक bit = params->frame.re_lsb % 8;

			u8 change;
			u8 prev_state = drvdata->re_state;
			/* Read Gray-coded state */
			u8 state = (data[byte] >> bit) & 0x3;
			/* Encode state change पूर्णांकo 2-bit चिन्हित पूर्णांकeger */
			अगर ((prev_state == 1 && state == 0) ||
			    (prev_state == 2 && state == 3)) अणु
				change = 1;
			पूर्ण अन्यथा अगर ((prev_state == 2 && state == 0) ||
				   (prev_state == 1 && state == 3)) अणु
				change = 3;
			पूर्ण अन्यथा अणु
				change = 0;
			पूर्ण
			/* Write change */
			data[byte] = (data[byte] & ~((u8)3 << bit)) |
					(change << bit);
			/* Remember state */
			drvdata->re_state = state;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम uclogic_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा uclogic_drvdata *drvdata = hid_get_drvdata(hdev);

	del_समयr_sync(&drvdata->inrange_समयr);
	hid_hw_stop(hdev);
	kमुक्त(drvdata->desc_ptr);
	uclogic_params_cleanup(&drvdata->params);
पूर्ण

अटल स्थिर काष्ठा hid_device_id uclogic_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UCLOGIC,
				USB_DEVICE_ID_UCLOGIC_TABLET_PF1209) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UCLOGIC,
				USB_DEVICE_ID_UCLOGIC_TABLET_WP4030U) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UCLOGIC,
				USB_DEVICE_ID_UCLOGIC_TABLET_WP5540U) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UCLOGIC,
				USB_DEVICE_ID_UCLOGIC_TABLET_WP8060U) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UCLOGIC,
				USB_DEVICE_ID_UCLOGIC_TABLET_WP1062) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UCLOGIC,
				USB_DEVICE_ID_UCLOGIC_WIRELESS_TABLET_TWHL850) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UCLOGIC,
				USB_DEVICE_ID_UCLOGIC_TABLET_TWHA60) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_HUION,
				USB_DEVICE_ID_HUION_TABLET) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_HUION,
				USB_DEVICE_ID_HUION_HS64) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_TRUST,
				USB_DEVICE_ID_TRUST_PANORA_TABLET) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UCLOGIC,
				USB_DEVICE_ID_HUION_TABLET) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UCLOGIC,
				USB_DEVICE_ID_YIYNOVA_TABLET) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UCLOGIC,
				USB_DEVICE_ID_UCLOGIC_UGEE_TABLET_81) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UCLOGIC,
				USB_DEVICE_ID_UCLOGIC_UGEE_TABLET_45) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UCLOGIC,
				USB_DEVICE_ID_UCLOGIC_UGEE_TABLET_47) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UCLOGIC,
				USB_DEVICE_ID_UCLOGIC_DRAWIMAGE_G3) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UGTIZER,
				USB_DEVICE_ID_UGTIZER_TABLET_GP0610) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UGTIZER,
				USB_DEVICE_ID_UGTIZER_TABLET_GT5040) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UGEE,
				USB_DEVICE_ID_UGEE_TABLET_G5) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UGEE,
				USB_DEVICE_ID_UGEE_TABLET_EX07S) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UGEE,
				USB_DEVICE_ID_UGEE_TABLET_RAINBOW_CV720) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UGEE,
				USB_DEVICE_ID_UGEE_XPPEN_TABLET_G540) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UGEE,
				USB_DEVICE_ID_UGEE_XPPEN_TABLET_G640) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_UGEE,
				USB_DEVICE_ID_UGEE_XPPEN_TABLET_DECO01) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, uclogic_devices);

अटल काष्ठा hid_driver uclogic_driver = अणु
	.name = "uclogic",
	.id_table = uclogic_devices,
	.probe = uclogic_probe,
	.हटाओ = uclogic_हटाओ,
	.report_fixup = uclogic_report_fixup,
	.raw_event = uclogic_raw_event,
	.input_mapping = uclogic_input_mapping,
	.input_configured = uclogic_input_configured,
#अगर_घोषित CONFIG_PM
	.resume	          = uclogic_resume,
	.reset_resume     = uclogic_resume,
#पूर्ण_अगर
पूर्ण;
module_hid_driver(uclogic_driver);

MODULE_AUTHOR("Martin Rusko");
MODULE_AUTHOR("Nikolai Kondrashov");
MODULE_LICENSE("GPL");
