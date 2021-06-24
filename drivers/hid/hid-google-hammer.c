<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  HID driver क्रम Google Hammer device.
 *
 *  Copyright (c) 2017 Google Inc.
 *  Author: Wei-Ning Huang <wnhuang@google.com>
 */

/*
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/hid.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_wakeup.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "hid-ids.h"

/*
 * C(hrome)B(ase)A(ttached)S(witch) - चयन exported by Chrome EC and reporting
 * state of the "Whiskers" base - attached or detached. Whiskers USB device also
 * reports position of the keyboard - folded or not. Combining base state and
 * position allows us to generate proper "Tablet mode" events.
 */
काष्ठा cbas_ec अणु
	काष्ठा device *dev;	/* The platक्रमm device (EC) */
	काष्ठा input_dev *input;
	bool base_present;
	bool base_folded;
	काष्ठा notअगरier_block notअगरier;
पूर्ण;

अटल काष्ठा cbas_ec cbas_ec;
अटल DEFINE_SPINLOCK(cbas_ec_lock);
अटल DEFINE_MUTEX(cbas_ec_reglock);

अटल bool cbas_parse_base_state(स्थिर व्योम *data)
अणु
	u32 चयनes = get_unaligned_le32(data);

	वापस !!(चयनes & BIT(EC_MKBP_BASE_ATTACHED));
पूर्ण

अटल पूर्णांक cbas_ec_query_base(काष्ठा cros_ec_device *ec_dev, bool get_state,
				  bool *state)
अणु
	काष्ठा ec_params_mkbp_info *params;
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;

	msg = kzalloc(माप(*msg) + max(माप(u32), माप(*params)),
		      GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	msg->command = EC_CMD_MKBP_INFO;
	msg->version = 1;
	msg->outsize = माप(*params);
	msg->insize = माप(u32);
	params = (काष्ठा ec_params_mkbp_info *)msg->data;
	params->info_type = get_state ?
		EC_MKBP_INFO_CURRENT : EC_MKBP_INFO_SUPPORTED;
	params->event_type = EC_MKBP_EVENT_SWITCH;

	ret = cros_ec_cmd_xfer_status(ec_dev, msg);
	अगर (ret >= 0) अणु
		अगर (ret != माप(u32)) अणु
			dev_warn(ec_dev->dev, "wrong result size: %d != %zu\n",
				 ret, माप(u32));
			ret = -EPROTO;
		पूर्ण अन्यथा अणु
			*state = cbas_parse_base_state(msg->data);
			ret = 0;
		पूर्ण
	पूर्ण

	kमुक्त(msg);

	वापस ret;
पूर्ण

अटल पूर्णांक cbas_ec_notअगरy(काष्ठा notअगरier_block *nb,
			      अचिन्हित दीर्घ queued_during_suspend,
			      व्योम *_notअगरy)
अणु
	काष्ठा cros_ec_device *ec = _notअगरy;
	अचिन्हित दीर्घ flags;
	bool base_present;

	अगर (ec->event_data.event_type == EC_MKBP_EVENT_SWITCH) अणु
		base_present = cbas_parse_base_state(
					&ec->event_data.data.चयनes);
		dev_dbg(cbas_ec.dev,
			"%s: base: %d\n", __func__, base_present);

		अगर (device_may_wakeup(cbas_ec.dev) ||
		    !queued_during_suspend) अणु

			pm_wakeup_event(cbas_ec.dev, 0);

			spin_lock_irqsave(&cbas_ec_lock, flags);

			/*
			 * While input layer dedupes the events, we करो not want
			 * to disrupt the state reported by the base by
			 * overriding it with state reported by the LID. Only
			 * report changes, as we assume that on attach the base
			 * is not folded.
			 */
			अगर (base_present != cbas_ec.base_present) अणु
				input_report_चयन(cbas_ec.input,
						    SW_TABLET_MODE,
						    !base_present);
				input_sync(cbas_ec.input);
				cbas_ec.base_present = base_present;
			पूर्ण

			spin_unlock_irqrestore(&cbas_ec_lock, flags);
		पूर्ण
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल __maybe_unused पूर्णांक cbas_ec_resume(काष्ठा device *dev)
अणु
	काष्ठा cros_ec_device *ec = dev_get_drvdata(dev->parent);
	bool base_present;
	पूर्णांक error;

	error = cbas_ec_query_base(ec, true, &base_present);
	अगर (error) अणु
		dev_warn(dev, "failed to fetch base state on resume: %d\n",
			 error);
	पूर्ण अन्यथा अणु
		spin_lock_irq(&cbas_ec_lock);

		cbas_ec.base_present = base_present;

		/*
		 * Only report अगर base is disconnected. If base is connected,
		 * it will resend its state on resume, and we'll update it
		 * in hammer_event().
		 */
		अगर (!cbas_ec.base_present) अणु
			input_report_चयन(cbas_ec.input, SW_TABLET_MODE, 1);
			input_sync(cbas_ec.input);
		पूर्ण

		spin_unlock_irq(&cbas_ec_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cbas_ec_pm_ops, शून्य, cbas_ec_resume);

अटल व्योम cbas_ec_set_input(काष्ठा input_dev *input)
अणु
	/* Take the lock so hammer_event() करोes not race with us here */
	spin_lock_irq(&cbas_ec_lock);
	cbas_ec.input = input;
	spin_unlock_irq(&cbas_ec_lock);
पूर्ण

अटल पूर्णांक __cbas_ec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_ec_device *ec = dev_get_drvdata(pdev->dev.parent);
	काष्ठा input_dev *input;
	bool base_supported;
	पूर्णांक error;

	error = cbas_ec_query_base(ec, false, &base_supported);
	अगर (error)
		वापस error;

	अगर (!base_supported)
		वापस -ENXIO;

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	input->name = "Whiskers Tablet Mode Switch";
	input->id.bustype = BUS_HOST;

	input_set_capability(input, EV_SW, SW_TABLET_MODE);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&pdev->dev, "cannot register input device: %d\n",
			error);
		वापस error;
	पूर्ण

	/* Seed the state */
	error = cbas_ec_query_base(ec, true, &cbas_ec.base_present);
	अगर (error) अणु
		dev_err(&pdev->dev, "cannot query base state: %d\n", error);
		वापस error;
	पूर्ण

	अगर (!cbas_ec.base_present)
		cbas_ec.base_folded = false;

	dev_dbg(&pdev->dev, "%s: base: %d, folded: %d\n", __func__,
		cbas_ec.base_present, cbas_ec.base_folded);

	input_report_चयन(input, SW_TABLET_MODE,
			    !cbas_ec.base_present || cbas_ec.base_folded);

	cbas_ec_set_input(input);

	cbas_ec.dev = &pdev->dev;
	cbas_ec.notअगरier.notअगरier_call = cbas_ec_notअगरy;
	error = blocking_notअगरier_chain_रेजिस्टर(&ec->event_notअगरier,
						 &cbas_ec.notअगरier);
	अगर (error) अणु
		dev_err(&pdev->dev, "cannot register notifier: %d\n", error);
		cbas_ec_set_input(शून्य);
		वापस error;
	पूर्ण

	device_init_wakeup(&pdev->dev, true);
	वापस 0;
पूर्ण

अटल पूर्णांक cbas_ec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक retval;

	mutex_lock(&cbas_ec_reglock);

	अगर (cbas_ec.input) अणु
		retval = -EBUSY;
		जाओ out;
	पूर्ण

	retval = __cbas_ec_probe(pdev);

out:
	mutex_unlock(&cbas_ec_reglock);
	वापस retval;
पूर्ण

अटल पूर्णांक cbas_ec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_ec_device *ec = dev_get_drvdata(pdev->dev.parent);

	mutex_lock(&cbas_ec_reglock);

	blocking_notअगरier_chain_unरेजिस्टर(&ec->event_notअगरier,
					   &cbas_ec.notअगरier);
	cbas_ec_set_input(शून्य);

	mutex_unlock(&cbas_ec_reglock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id cbas_ec_acpi_ids[] = अणु
	अणु "GOOG000B", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, cbas_ec_acpi_ids);

अटल काष्ठा platक्रमm_driver cbas_ec_driver = अणु
	.probe = cbas_ec_probe,
	.हटाओ = cbas_ec_हटाओ,
	.driver = अणु
		.name = "cbas_ec",
		.acpi_match_table = ACPI_PTR(cbas_ec_acpi_ids),
		.pm = &cbas_ec_pm_ops,
	पूर्ण,
पूर्ण;

#घोषणा MAX_BRIGHTNESS 100

काष्ठा hammer_kbd_leds अणु
	काष्ठा led_classdev cdev;
	काष्ठा hid_device *hdev;
	u8 buf[2] ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक hammer_kbd_brightness_set_blocking(काष्ठा led_classdev *cdev,
		क्रमागत led_brightness br)
अणु
	काष्ठा hammer_kbd_leds *led = container_of(cdev,
						   काष्ठा hammer_kbd_leds,
						   cdev);
	पूर्णांक ret;

	led->buf[0] = 0;
	led->buf[1] = br;

	/*
	 * Request USB HID device to be in Full On mode, so that sending
	 * hardware output report and hardware raw request won't fail.
	 */
	ret = hid_hw_घातer(led->hdev, PM_HINT_FULLON);
	अगर (ret < 0) अणु
		hid_err(led->hdev, "failed: device not resumed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hid_hw_output_report(led->hdev, led->buf, माप(led->buf));
	अगर (ret == -ENOSYS)
		ret = hid_hw_raw_request(led->hdev, 0, led->buf,
					 माप(led->buf),
					 HID_OUTPUT_REPORT,
					 HID_REQ_SET_REPORT);
	अगर (ret < 0)
		hid_err(led->hdev, "failed to set keyboard backlight: %d\n",
			ret);

	/* Request USB HID device back to Normal Mode. */
	hid_hw_घातer(led->hdev, PM_HINT_NORMAL);

	वापस ret;
पूर्ण

अटल पूर्णांक hammer_रेजिस्टर_leds(काष्ठा hid_device *hdev)
अणु
	काष्ठा hammer_kbd_leds *kbd_backlight;
	पूर्णांक error;

	kbd_backlight = kzalloc(माप(*kbd_backlight), GFP_KERNEL);
	अगर (!kbd_backlight)
		वापस -ENOMEM;

	kbd_backlight->hdev = hdev;
	kbd_backlight->cdev.name = "hammer::kbd_backlight";
	kbd_backlight->cdev.max_brightness = MAX_BRIGHTNESS;
	kbd_backlight->cdev.brightness_set_blocking =
		hammer_kbd_brightness_set_blocking;
	kbd_backlight->cdev.flags = LED_HW_PLUGGABLE;

	/* Set backlight to 0% initially. */
	hammer_kbd_brightness_set_blocking(&kbd_backlight->cdev, 0);

	error = led_classdev_रेजिस्टर(&hdev->dev, &kbd_backlight->cdev);
	अगर (error)
		जाओ err_मुक्त_mem;

	hid_set_drvdata(hdev, kbd_backlight);
	वापस 0;

err_मुक्त_mem:
	kमुक्त(kbd_backlight);
	वापस error;
पूर्ण

अटल व्योम hammer_unरेजिस्टर_leds(काष्ठा hid_device *hdev)
अणु
	काष्ठा hammer_kbd_leds *kbd_backlight = hid_get_drvdata(hdev);

	अगर (kbd_backlight) अणु
		led_classdev_unरेजिस्टर(&kbd_backlight->cdev);
		kमुक्त(kbd_backlight);
	पूर्ण
पूर्ण

#घोषणा HID_UP_GOOGLEVENDOR	0xffd10000
#घोषणा HID_VD_KBD_FOLDED	0x00000019
#घोषणा HID_USAGE_KBD_FOLDED	(HID_UP_GOOGLEVENDOR | HID_VD_KBD_FOLDED)

/* HID usage क्रम keyboard backlight (Alphanumeric display brightness) */
#घोषणा HID_AD_BRIGHTNESS	0x00140046

अटल पूर्णांक hammer_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
				काष्ठा hid_field *field,
				काष्ठा hid_usage *usage,
				अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर (usage->hid == HID_USAGE_KBD_FOLDED) अणु
		/*
		 * We करो not want to have this usage mapped as it will get
		 * mixed in with "base attached" संकेत and delivered over
		 * separate input device क्रम tablet चयन mode.
		 */
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hammer_folded_event(काष्ठा hid_device *hdev, bool folded)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cbas_ec_lock, flags);

	/*
	 * If we are getting events from Whiskers that means that it
	 * is attached to the lid.
	 */
	cbas_ec.base_present = true;
	cbas_ec.base_folded = folded;
	hid_dbg(hdev, "%s: base: %d, folded: %d\n", __func__,
		cbas_ec.base_present, cbas_ec.base_folded);

	अगर (cbas_ec.input) अणु
		input_report_चयन(cbas_ec.input, SW_TABLET_MODE, folded);
		input_sync(cbas_ec.input);
	पूर्ण

	spin_unlock_irqrestore(&cbas_ec_lock, flags);
पूर्ण

अटल पूर्णांक hammer_event(काष्ठा hid_device *hid, काष्ठा hid_field *field,
			काष्ठा hid_usage *usage, __s32 value)
अणु
	अगर (usage->hid == HID_USAGE_KBD_FOLDED) अणु
		hammer_folded_event(hid, value);
		वापस 1; /* We handled this event */
	पूर्ण

	वापस 0;
पूर्ण

अटल bool hammer_has_usage(काष्ठा hid_device *hdev, अचिन्हित पूर्णांक report_type,
			अचिन्हित application, अचिन्हित usage)
अणु
	काष्ठा hid_report_क्रमागत *re = &hdev->report_क्रमागत[report_type];
	काष्ठा hid_report *report;
	पूर्णांक i, j;

	list_क्रम_each_entry(report, &re->report_list, list) अणु
		अगर (report->application != application)
			जारी;

		क्रम (i = 0; i < report->maxfield; i++) अणु
			काष्ठा hid_field *field = report->field[i];

			क्रम (j = 0; j < field->maxusage; j++)
				अगर (field->usage[j].hid == usage)
					वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool hammer_has_folded_event(काष्ठा hid_device *hdev)
अणु
	वापस hammer_has_usage(hdev, HID_INPUT_REPORT,
				HID_GD_KEYBOARD, HID_USAGE_KBD_FOLDED);
पूर्ण

अटल bool hammer_has_backlight_control(काष्ठा hid_device *hdev)
अणु
	वापस hammer_has_usage(hdev, HID_OUTPUT_REPORT,
				HID_GD_KEYBOARD, HID_AD_BRIGHTNESS);
पूर्ण

अटल व्योम hammer_get_folded_state(काष्ठा hid_device *hdev)
अणु
	काष्ठा hid_report *report;
	अक्षर *buf;
	पूर्णांक len, rlen;
	पूर्णांक a;

	report = hdev->report_क्रमागत[HID_INPUT_REPORT].report_id_hash[0x0];

	अगर (!report || report->maxfield < 1)
		वापस;

	len = hid_report_len(report) + 1;

	buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!buf)
		वापस;

	rlen = hid_hw_raw_request(hdev, report->id, buf, len, report->type, HID_REQ_GET_REPORT);

	अगर (rlen != len) अणु
		hid_warn(hdev, "Unable to read base folded state: %d (expected %d)\n", rlen, len);
		जाओ out;
	पूर्ण

	क्रम (a = 0; a < report->maxfield; a++) अणु
		काष्ठा hid_field *field = report->field[a];

		अगर (field->usage->hid == HID_USAGE_KBD_FOLDED) अणु
			u32 value = hid_field_extract(hdev, buf+1,
					field->report_offset, field->report_size);

			hammer_folded_event(hdev, value);
			अवरोध;
		पूर्ण
	पूर्ण

out:
	kमुक्त(buf);
पूर्ण

अटल पूर्णांक hammer_probe(काष्ठा hid_device *hdev,
			स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक error;

	error = hid_parse(hdev);
	अगर (error)
		वापस error;

	error = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (error)
		वापस error;

	/*
	 * We always want to poll क्रम, and handle tablet mode events from
	 * devices that have folded usage, even when nobody has खोलोed the input
	 * device. This also prevents the hid core from dropping early tablet
	 * mode events from the device.
	 */
	अगर (hammer_has_folded_event(hdev)) अणु
		hdev->quirks |= HID_QUIRK_ALWAYS_POLL;
		error = hid_hw_खोलो(hdev);
		अगर (error)
			वापस error;

		hammer_get_folded_state(hdev);
	पूर्ण

	अगर (hammer_has_backlight_control(hdev)) अणु
		error = hammer_रेजिस्टर_leds(hdev);
		अगर (error)
			hid_warn(hdev,
				"Failed to register keyboard backlight: %d\n",
				error);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hammer_हटाओ(काष्ठा hid_device *hdev)
अणु
	अचिन्हित दीर्घ flags;

	अगर (hammer_has_folded_event(hdev)) अणु
		hid_hw_बंद(hdev);

		/*
		 * If we are disconnecting then most likely Whiskers is
		 * being हटाओd. Even अगर it is not हटाओd, without proper
		 * keyboard we should not stay in clamshell mode.
		 *
		 * The reason क्रम करोing it here and not रुकोing क्रम संकेत
		 * from EC, is that on some devices there are high leakage
		 * on Whiskers pins and we करो not detect disconnect reliably,
		 * resulting in devices being stuck in clamshell mode.
		 */
		spin_lock_irqsave(&cbas_ec_lock, flags);
		अगर (cbas_ec.input && cbas_ec.base_present) अणु
			input_report_चयन(cbas_ec.input, SW_TABLET_MODE, 1);
			input_sync(cbas_ec.input);
		पूर्ण
		cbas_ec.base_present = false;
		spin_unlock_irqrestore(&cbas_ec_lock, flags);
	पूर्ण

	hammer_unरेजिस्टर_leds(hdev);

	hid_hw_stop(hdev);
पूर्ण

अटल स्थिर काष्ठा hid_device_id hammer_devices[] = अणु
	अणु HID_DEVICE(BUS_USB, HID_GROUP_GENERIC,
		     USB_VENDOR_ID_GOOGLE, USB_DEVICE_ID_GOOGLE_DON) पूर्ण,
	अणु HID_DEVICE(BUS_USB, HID_GROUP_GENERIC,
		     USB_VENDOR_ID_GOOGLE, USB_DEVICE_ID_GOOGLE_HAMMER) पूर्ण,
	अणु HID_DEVICE(BUS_USB, HID_GROUP_GENERIC,
		     USB_VENDOR_ID_GOOGLE, USB_DEVICE_ID_GOOGLE_MAGNEMITE) पूर्ण,
	अणु HID_DEVICE(BUS_USB, HID_GROUP_GENERIC,
		     USB_VENDOR_ID_GOOGLE, USB_DEVICE_ID_GOOGLE_MASTERBALL) पूर्ण,
	अणु HID_DEVICE(BUS_USB, HID_GROUP_GENERIC,
		     USB_VENDOR_ID_GOOGLE, USB_DEVICE_ID_GOOGLE_MOONBALL) पूर्ण,
	अणु HID_DEVICE(BUS_USB, HID_GROUP_GENERIC,
		     USB_VENDOR_ID_GOOGLE, USB_DEVICE_ID_GOOGLE_STAFF) पूर्ण,
	अणु HID_DEVICE(BUS_USB, HID_GROUP_GENERIC,
		     USB_VENDOR_ID_GOOGLE, USB_DEVICE_ID_GOOGLE_WAND) पूर्ण,
	अणु HID_DEVICE(BUS_USB, HID_GROUP_GENERIC,
		     USB_VENDOR_ID_GOOGLE, USB_DEVICE_ID_GOOGLE_WHISKERS) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, hammer_devices);

अटल काष्ठा hid_driver hammer_driver = अणु
	.name = "hammer",
	.id_table = hammer_devices,
	.probe = hammer_probe,
	.हटाओ = hammer_हटाओ,
	.input_mapping = hammer_input_mapping,
	.event = hammer_event,
पूर्ण;

अटल पूर्णांक __init hammer_init(व्योम)
अणु
	पूर्णांक error;

	error = platक्रमm_driver_रेजिस्टर(&cbas_ec_driver);
	अगर (error)
		वापस error;

	error = hid_रेजिस्टर_driver(&hammer_driver);
	अगर (error) अणु
		platक्रमm_driver_unरेजिस्टर(&cbas_ec_driver);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण
module_init(hammer_init);

अटल व्योम __निकास hammer_निकास(व्योम)
अणु
	hid_unरेजिस्टर_driver(&hammer_driver);
	platक्रमm_driver_unरेजिस्टर(&cbas_ec_driver);
पूर्ण
module_निकास(hammer_निकास);

MODULE_LICENSE("GPL");
