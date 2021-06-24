<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/***************************************************************************
 *   Copyright (C) 2010-2012 by Bruno Prथऊmont <bonbons@linux-vserver.org>  *
 *                                                                         *
 *   Based on Logitech G13 driver (v0.4)                                   *
 *     Copyright (C) 2009 by Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>   *
 *                                                                         *
 ***************************************************************************/

#समावेश <linux/hid.h>
#समावेश <linux/hid-debug.h>
#समावेश <linux/input.h>
#समावेश "hid-ids.h"

#समावेश <linux/fb.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <linux/completion.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>

#समावेश "hid-picolcd.h"


/* Input device
 *
 * The PicoLCD has an IR receiver header, a built-in keypad with 5 keys
 * and header क्रम 4x4 key matrix. The built-in keys are part of the matrix.
 */
अटल स्थिर अचिन्हित लघु def_keymap[PICOLCD_KEYS] = अणु
	KEY_RESERVED,	/* none */
	KEY_BACK,	/* col 4 + row 1 */
	KEY_HOMEPAGE,	/* col 3 + row 1 */
	KEY_RESERVED,	/* col 2 + row 1 */
	KEY_RESERVED,	/* col 1 + row 1 */
	KEY_SCROLLUP,	/* col 4 + row 2 */
	KEY_OK,		/* col 3 + row 2 */
	KEY_SCROLLDOWN,	/* col 2 + row 2 */
	KEY_RESERVED,	/* col 1 + row 2 */
	KEY_RESERVED,	/* col 4 + row 3 */
	KEY_RESERVED,	/* col 3 + row 3 */
	KEY_RESERVED,	/* col 2 + row 3 */
	KEY_RESERVED,	/* col 1 + row 3 */
	KEY_RESERVED,	/* col 4 + row 4 */
	KEY_RESERVED,	/* col 3 + row 4 */
	KEY_RESERVED,	/* col 2 + row 4 */
	KEY_RESERVED,	/* col 1 + row 4 */
पूर्ण;


/* Find a given report */
काष्ठा hid_report *picolcd_report(पूर्णांक id, काष्ठा hid_device *hdev, पूर्णांक dir)
अणु
	काष्ठा list_head *feature_report_list = &hdev->report_क्रमागत[dir].report_list;
	काष्ठा hid_report *report = शून्य;

	list_क्रम_each_entry(report, feature_report_list, list) अणु
		अगर (report->id == id)
			वापस report;
	पूर्ण
	hid_warn(hdev, "No report with id 0x%x found\n", id);
	वापस शून्य;
पूर्ण

/* Submit a report and रुको क्रम a reply from device - अगर device fades away
 * or करोes not respond in समय, वापस शून्य */
काष्ठा picolcd_pending *picolcd_send_and_रुको(काष्ठा hid_device *hdev,
		पूर्णांक report_id, स्थिर u8 *raw_data, पूर्णांक size)
अणु
	काष्ठा picolcd_data *data = hid_get_drvdata(hdev);
	काष्ठा picolcd_pending *work;
	काष्ठा hid_report *report = picolcd_out_report(report_id, hdev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i, j, k;

	अगर (!report || !data)
		वापस शून्य;
	अगर (data->status & PICOLCD_FAILED)
		वापस शून्य;
	work = kzalloc(माप(*work), GFP_KERNEL);
	अगर (!work)
		वापस शून्य;

	init_completion(&work->पढ़ोy);
	work->out_report = report;
	work->in_report  = शून्य;
	work->raw_size   = 0;

	mutex_lock(&data->mutex);
	spin_lock_irqsave(&data->lock, flags);
	क्रम (i = k = 0; i < report->maxfield; i++)
		क्रम (j = 0; j < report->field[i]->report_count; j++) अणु
			hid_set_field(report->field[i], j, k < size ? raw_data[k] : 0);
			k++;
		पूर्ण
	अगर (data->status & PICOLCD_FAILED) अणु
		kमुक्त(work);
		work = शून्य;
	पूर्ण अन्यथा अणु
		data->pending = work;
		hid_hw_request(data->hdev, report, HID_REQ_SET_REPORT);
		spin_unlock_irqrestore(&data->lock, flags);
		रुको_क्रम_completion_पूर्णांकerruptible_समयout(&work->पढ़ोy, HZ*2);
		spin_lock_irqsave(&data->lock, flags);
		data->pending = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&data->lock, flags);
	mutex_unlock(&data->mutex);
	वापस work;
पूर्ण

/*
 * input class device
 */
अटल पूर्णांक picolcd_raw_keypad(काष्ठा picolcd_data *data,
		काष्ठा hid_report *report, u8 *raw_data, पूर्णांक size)
अणु
	/*
	 * Keypad event
	 * First and second data bytes list currently pressed keys,
	 * 0x00 means no key and at most 2 keys may be pressed at same समय
	 */
	पूर्णांक i, j;

	/* determine newly pressed keys */
	क्रम (i = 0; i < size; i++) अणु
		अचिन्हित पूर्णांक key_code;
		अगर (raw_data[i] == 0)
			जारी;
		क्रम (j = 0; j < माप(data->pressed_keys); j++)
			अगर (data->pressed_keys[j] == raw_data[i])
				जाओ key_alपढ़ोy_करोwn;
		क्रम (j = 0; j < माप(data->pressed_keys); j++)
			अगर (data->pressed_keys[j] == 0) अणु
				data->pressed_keys[j] = raw_data[i];
				अवरोध;
			पूर्ण
		input_event(data->input_keys, EV_MSC, MSC_SCAN, raw_data[i]);
		अगर (raw_data[i] < PICOLCD_KEYS)
			key_code = data->keycode[raw_data[i]];
		अन्यथा
			key_code = KEY_UNKNOWN;
		अगर (key_code != KEY_UNKNOWN) अणु
			dbg_hid(PICOLCD_NAME " got key press for %u:%d",
					raw_data[i], key_code);
			input_report_key(data->input_keys, key_code, 1);
		पूर्ण
		input_sync(data->input_keys);
key_alपढ़ोy_करोwn:
		जारी;
	पूर्ण

	/* determine newly released keys */
	क्रम (j = 0; j < माप(data->pressed_keys); j++) अणु
		अचिन्हित पूर्णांक key_code;
		अगर (data->pressed_keys[j] == 0)
			जारी;
		क्रम (i = 0; i < size; i++)
			अगर (data->pressed_keys[j] == raw_data[i])
				जाओ key_still_करोwn;
		input_event(data->input_keys, EV_MSC, MSC_SCAN, data->pressed_keys[j]);
		अगर (data->pressed_keys[j] < PICOLCD_KEYS)
			key_code = data->keycode[data->pressed_keys[j]];
		अन्यथा
			key_code = KEY_UNKNOWN;
		अगर (key_code != KEY_UNKNOWN) अणु
			dbg_hid(PICOLCD_NAME " got key release for %u:%d",
					data->pressed_keys[j], key_code);
			input_report_key(data->input_keys, key_code, 0);
		पूर्ण
		input_sync(data->input_keys);
		data->pressed_keys[j] = 0;
key_still_करोwn:
		जारी;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक picolcd_check_version(काष्ठा hid_device *hdev)
अणु
	काष्ठा picolcd_data *data = hid_get_drvdata(hdev);
	काष्ठा picolcd_pending *verinfo;
	पूर्णांक ret = 0;

	अगर (!data)
		वापस -ENODEV;

	verinfo = picolcd_send_and_रुको(hdev, REPORT_VERSION, शून्य, 0);
	अगर (!verinfo) अणु
		hid_err(hdev, "no version response from PicoLCD\n");
		वापस -ENODEV;
	पूर्ण

	अगर (verinfo->raw_size == 2) अणु
		data->version[0] = verinfo->raw_data[1];
		data->version[1] = verinfo->raw_data[0];
		अगर (data->status & PICOLCD_BOOTLOADER) अणु
			hid_info(hdev, "PicoLCD, bootloader version %d.%d\n",
				 verinfo->raw_data[1], verinfo->raw_data[0]);
		पूर्ण अन्यथा अणु
			hid_info(hdev, "PicoLCD, firmware version %d.%d\n",
				 verinfo->raw_data[1], verinfo->raw_data[0]);
		पूर्ण
	पूर्ण अन्यथा अणु
		hid_err(hdev, "confused, got unexpected version response from PicoLCD\n");
		ret = -EINVAL;
	पूर्ण
	kमुक्त(verinfo);
	वापस ret;
पूर्ण

/*
 * Reset our device and रुको क्रम answer to VERSION request
 */
पूर्णांक picolcd_reset(काष्ठा hid_device *hdev)
अणु
	काष्ठा picolcd_data *data = hid_get_drvdata(hdev);
	काष्ठा hid_report *report = picolcd_out_report(REPORT_RESET, hdev);
	अचिन्हित दीर्घ flags;
	पूर्णांक error;

	अगर (!data || !report || report->maxfield != 1)
		वापस -ENODEV;

	spin_lock_irqsave(&data->lock, flags);
	अगर (hdev->product == USB_DEVICE_ID_PICOLCD_BOOTLOADER)
		data->status |= PICOLCD_BOOTLOADER;

	/* perक्रमm the reset */
	hid_set_field(report->field[0], 0, 1);
	अगर (data->status & PICOLCD_FAILED) अणु
		spin_unlock_irqrestore(&data->lock, flags);
		वापस -ENODEV;
	पूर्ण
	hid_hw_request(hdev, report, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&data->lock, flags);

	error = picolcd_check_version(hdev);
	अगर (error)
		वापस error;

	picolcd_resume_lcd(data);
	picolcd_resume_backlight(data);
	picolcd_fb_refresh(data);
	picolcd_leds_set(data);
	वापस 0;
पूर्ण

/*
 * The "operation_mode" sysfs attribute
 */
अटल sमाप_प्रकार picolcd_operation_mode_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा picolcd_data *data = dev_get_drvdata(dev);

	अगर (data->status & PICOLCD_BOOTLOADER)
		वापस snम_लिखो(buf, PAGE_SIZE, "[bootloader] lcd\n");
	अन्यथा
		वापस snम_लिखो(buf, PAGE_SIZE, "bootloader [lcd]\n");
पूर्ण

अटल sमाप_प्रकार picolcd_operation_mode_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा picolcd_data *data = dev_get_drvdata(dev);
	काष्ठा hid_report *report = शून्य;
	पूर्णांक समयout = data->opmode_delay;
	अचिन्हित दीर्घ flags;

	अगर (sysfs_streq(buf, "lcd")) अणु
		अगर (data->status & PICOLCD_BOOTLOADER)
			report = picolcd_out_report(REPORT_EXIT_FLASHER, data->hdev);
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "bootloader")) अणु
		अगर (!(data->status & PICOLCD_BOOTLOADER))
			report = picolcd_out_report(REPORT_EXIT_KEYBOARD, data->hdev);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (!report || report->maxfield != 1)
		वापस -EINVAL;

	spin_lock_irqsave(&data->lock, flags);
	hid_set_field(report->field[0], 0, समयout & 0xff);
	hid_set_field(report->field[0], 1, (समयout >> 8) & 0xff);
	hid_hw_request(data->hdev, report, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&data->lock, flags);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(operation_mode, 0644, picolcd_operation_mode_show,
		picolcd_operation_mode_store);

/*
 * The "operation_mode_delay" sysfs attribute
 */
अटल sमाप_प्रकार picolcd_operation_mode_delay_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा picolcd_data *data = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%hu\n", data->opmode_delay);
पूर्ण

अटल sमाप_प्रकार picolcd_operation_mode_delay_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा picolcd_data *data = dev_get_drvdata(dev);
	अचिन्हित u;
	अगर (माला_पूछो(buf, "%u", &u) != 1)
		वापस -EINVAL;
	अगर (u > 30000)
		वापस -EINVAL;
	अन्यथा
		data->opmode_delay = u;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(operation_mode_delay, 0644, picolcd_operation_mode_delay_show,
		picolcd_operation_mode_delay_store);

/*
 * Handle raw report as sent by device
 */
अटल पूर्णांक picolcd_raw_event(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report, u8 *raw_data, पूर्णांक size)
अणु
	काष्ठा picolcd_data *data = hid_get_drvdata(hdev);
	अचिन्हित दीर्घ flags;

	अगर (!data)
		वापस 1;

	अगर (size > 64) अणु
		hid_warn(hdev, "invalid size value (%d) for picolcd raw event (%d)\n",
				size, report->id);
		वापस 0;
	पूर्ण

	अगर (report->id == REPORT_KEY_STATE) अणु
		अगर (data->input_keys)
			picolcd_raw_keypad(data, report, raw_data+1, size-1);
	पूर्ण अन्यथा अगर (report->id == REPORT_IR_DATA) अणु
		picolcd_raw_cir(data, report, raw_data+1, size-1);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&data->lock, flags);
		/*
		 * We let the caller of picolcd_send_and_रुको() check अगर the
		 * report we got is one of the expected ones or not.
		 */
		अगर (data->pending) अणु
			स_नकल(data->pending->raw_data, raw_data+1, size-1);
			data->pending->raw_size  = size-1;
			data->pending->in_report = report;
			complete(&data->pending->पढ़ोy);
		पूर्ण
		spin_unlock_irqrestore(&data->lock, flags);
	पूर्ण

	picolcd_debug_raw_event(data, hdev, report, raw_data, size);
	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक picolcd_suspend(काष्ठा hid_device *hdev, pm_message_t message)
अणु
	अगर (PMSG_IS_AUTO(message))
		वापस 0;

	picolcd_suspend_backlight(hid_get_drvdata(hdev));
	dbg_hid(PICOLCD_NAME " device ready for suspend\n");
	वापस 0;
पूर्ण

अटल पूर्णांक picolcd_resume(काष्ठा hid_device *hdev)
अणु
	पूर्णांक ret;
	ret = picolcd_resume_backlight(hid_get_drvdata(hdev));
	अगर (ret)
		dbg_hid(PICOLCD_NAME " restoring backlight failed: %d\n", ret);
	वापस 0;
पूर्ण

अटल पूर्णांक picolcd_reset_resume(काष्ठा hid_device *hdev)
अणु
	पूर्णांक ret;
	ret = picolcd_reset(hdev);
	अगर (ret)
		dbg_hid(PICOLCD_NAME " resetting our device failed: %d\n", ret);
	ret = picolcd_fb_reset(hid_get_drvdata(hdev), 0);
	अगर (ret)
		dbg_hid(PICOLCD_NAME " restoring framebuffer content failed: %d\n", ret);
	ret = picolcd_resume_lcd(hid_get_drvdata(hdev));
	अगर (ret)
		dbg_hid(PICOLCD_NAME " restoring lcd failed: %d\n", ret);
	ret = picolcd_resume_backlight(hid_get_drvdata(hdev));
	अगर (ret)
		dbg_hid(PICOLCD_NAME " restoring backlight failed: %d\n", ret);
	picolcd_leds_set(hid_get_drvdata(hdev));
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* initialize keypad input device */
अटल पूर्णांक picolcd_init_keys(काष्ठा picolcd_data *data,
		काष्ठा hid_report *report)
अणु
	काष्ठा hid_device *hdev = data->hdev;
	काष्ठा input_dev *idev;
	पूर्णांक error, i;

	अगर (!report)
		वापस -ENODEV;
	अगर (report->maxfield != 1 || report->field[0]->report_count != 2 ||
			report->field[0]->report_size != 8) अणु
		hid_err(hdev, "unsupported KEY_STATE report\n");
		वापस -EINVAL;
	पूर्ण

	idev = input_allocate_device();
	अगर (idev == शून्य) अणु
		hid_err(hdev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण
	input_set_drvdata(idev, hdev);
	स_नकल(data->keycode, def_keymap, माप(def_keymap));
	idev->name = hdev->name;
	idev->phys = hdev->phys;
	idev->uniq = hdev->uniq;
	idev->id.bustype = hdev->bus;
	idev->id.venकरोr  = hdev->venकरोr;
	idev->id.product = hdev->product;
	idev->id.version = hdev->version;
	idev->dev.parent = &hdev->dev;
	idev->keycode     = &data->keycode;
	idev->keycodemax  = PICOLCD_KEYS;
	idev->keycodesize = माप(data->keycode[0]);
	input_set_capability(idev, EV_MSC, MSC_SCAN);
	set_bit(EV_REP, idev->evbit);
	क्रम (i = 0; i < PICOLCD_KEYS; i++)
		input_set_capability(idev, EV_KEY, data->keycode[i]);
	error = input_रेजिस्टर_device(idev);
	अगर (error) अणु
		hid_err(hdev, "error registering the input device\n");
		input_मुक्त_device(idev);
		वापस error;
	पूर्ण
	data->input_keys = idev;
	वापस 0;
पूर्ण

अटल व्योम picolcd_निकास_keys(काष्ठा picolcd_data *data)
अणु
	काष्ठा input_dev *idev = data->input_keys;

	data->input_keys = शून्य;
	अगर (idev)
		input_unरेजिस्टर_device(idev);
पूर्ण

अटल पूर्णांक picolcd_probe_lcd(काष्ठा hid_device *hdev, काष्ठा picolcd_data *data)
अणु
	पूर्णांक error;

	/* Setup keypad input device */
	error = picolcd_init_keys(data, picolcd_in_report(REPORT_KEY_STATE, hdev));
	अगर (error)
		जाओ err;

	/* Setup CIR input device */
	error = picolcd_init_cir(data, picolcd_in_report(REPORT_IR_DATA, hdev));
	अगर (error)
		जाओ err;

	/* Set up the framebuffer device */
	error = picolcd_init_framebuffer(data);
	अगर (error)
		जाओ err;

	/* Setup lcd class device */
	error = picolcd_init_lcd(data, picolcd_out_report(REPORT_CONTRAST, hdev));
	अगर (error)
		जाओ err;

	/* Setup backlight class device */
	error = picolcd_init_backlight(data, picolcd_out_report(REPORT_BRIGHTNESS, hdev));
	अगर (error)
		जाओ err;

	/* Setup the LED class devices */
	error = picolcd_init_leds(data, picolcd_out_report(REPORT_LED_STATE, hdev));
	अगर (error)
		जाओ err;

	picolcd_init_devfs(data, picolcd_out_report(REPORT_EE_READ, hdev),
			picolcd_out_report(REPORT_EE_WRITE, hdev),
			picolcd_out_report(REPORT_READ_MEMORY, hdev),
			picolcd_out_report(REPORT_WRITE_MEMORY, hdev),
			picolcd_out_report(REPORT_RESET, hdev));
	वापस 0;
err:
	picolcd_निकास_leds(data);
	picolcd_निकास_backlight(data);
	picolcd_निकास_lcd(data);
	picolcd_निकास_framebuffer(data);
	picolcd_निकास_cir(data);
	picolcd_निकास_keys(data);
	वापस error;
पूर्ण

अटल पूर्णांक picolcd_probe_bootloader(काष्ठा hid_device *hdev, काष्ठा picolcd_data *data)
अणु
	picolcd_init_devfs(data, शून्य, शून्य,
			picolcd_out_report(REPORT_BL_READ_MEMORY, hdev),
			picolcd_out_report(REPORT_BL_WRITE_MEMORY, hdev), शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक picolcd_probe(काष्ठा hid_device *hdev,
		     स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा picolcd_data *data;
	पूर्णांक error = -ENOMEM;

	dbg_hid(PICOLCD_NAME " hardware probe...\n");

	/*
	 * Let's allocate the picolcd data काष्ठाure, set some reasonable
	 * शेषs, and associate it with the device
	 */
	data = kzalloc(माप(काष्ठा picolcd_data), GFP_KERNEL);
	अगर (data == शून्य) अणु
		hid_err(hdev, "can't allocate space for Minibox PicoLCD device data\n");
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&data->lock);
	mutex_init(&data->mutex);
	data->hdev = hdev;
	data->opmode_delay = 5000;
	अगर (hdev->product == USB_DEVICE_ID_PICOLCD_BOOTLOADER)
		data->status |= PICOLCD_BOOTLOADER;
	hid_set_drvdata(hdev, data);

	/* Parse the device reports and start it up */
	error = hid_parse(hdev);
	अगर (error) अणु
		hid_err(hdev, "device report parse failed\n");
		जाओ err_cleanup_data;
	पूर्ण

	error = hid_hw_start(hdev, 0);
	अगर (error) अणु
		hid_err(hdev, "hardware start failed\n");
		जाओ err_cleanup_data;
	पूर्ण

	error = hid_hw_खोलो(hdev);
	अगर (error) अणु
		hid_err(hdev, "failed to open input interrupt pipe for key and IR events\n");
		जाओ err_cleanup_hid_hw;
	पूर्ण

	error = device_create_file(&hdev->dev, &dev_attr_operation_mode_delay);
	अगर (error) अणु
		hid_err(hdev, "failed to create sysfs attributes\n");
		जाओ err_cleanup_hid_ll;
	पूर्ण

	error = device_create_file(&hdev->dev, &dev_attr_operation_mode);
	अगर (error) अणु
		hid_err(hdev, "failed to create sysfs attributes\n");
		जाओ err_cleanup_sysfs1;
	पूर्ण

	अगर (data->status & PICOLCD_BOOTLOADER)
		error = picolcd_probe_bootloader(hdev, data);
	अन्यथा
		error = picolcd_probe_lcd(hdev, data);
	अगर (error)
		जाओ err_cleanup_sysfs2;

	dbg_hid(PICOLCD_NAME " activated and initialized\n");
	वापस 0;

err_cleanup_sysfs2:
	device_हटाओ_file(&hdev->dev, &dev_attr_operation_mode);
err_cleanup_sysfs1:
	device_हटाओ_file(&hdev->dev, &dev_attr_operation_mode_delay);
err_cleanup_hid_ll:
	hid_hw_बंद(hdev);
err_cleanup_hid_hw:
	hid_hw_stop(hdev);
err_cleanup_data:
	kमुक्त(data);
	वापस error;
पूर्ण

अटल व्योम picolcd_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा picolcd_data *data = hid_get_drvdata(hdev);
	अचिन्हित दीर्घ flags;

	dbg_hid(PICOLCD_NAME " hardware remove...\n");
	spin_lock_irqsave(&data->lock, flags);
	data->status |= PICOLCD_FAILED;
	spin_unlock_irqrestore(&data->lock, flags);

	picolcd_निकास_devfs(data);
	device_हटाओ_file(&hdev->dev, &dev_attr_operation_mode);
	device_हटाओ_file(&hdev->dev, &dev_attr_operation_mode_delay);
	hid_hw_बंद(hdev);
	hid_hw_stop(hdev);

	/* Shortcut potential pending reply that will never arrive */
	spin_lock_irqsave(&data->lock, flags);
	अगर (data->pending)
		complete(&data->pending->पढ़ोy);
	spin_unlock_irqrestore(&data->lock, flags);

	/* Cleanup LED */
	picolcd_निकास_leds(data);
	/* Clean up the framebuffer */
	picolcd_निकास_backlight(data);
	picolcd_निकास_lcd(data);
	picolcd_निकास_framebuffer(data);
	/* Cleanup input */
	picolcd_निकास_cir(data);
	picolcd_निकास_keys(data);

	mutex_destroy(&data->mutex);
	/* Finally, clean up the picolcd data itself */
	kमुक्त(data);
पूर्ण

अटल स्थिर काष्ठा hid_device_id picolcd_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROCHIP, USB_DEVICE_ID_PICOLCD) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROCHIP, USB_DEVICE_ID_PICOLCD_BOOTLOADER) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, picolcd_devices);

अटल काष्ठा hid_driver picolcd_driver = अणु
	.name =          "hid-picolcd",
	.id_table =      picolcd_devices,
	.probe =         picolcd_probe,
	.हटाओ =        picolcd_हटाओ,
	.raw_event =     picolcd_raw_event,
#अगर_घोषित CONFIG_PM
	.suspend =       picolcd_suspend,
	.resume =        picolcd_resume,
	.reset_resume =  picolcd_reset_resume,
#पूर्ण_अगर
पूर्ण;
module_hid_driver(picolcd_driver);

MODULE_DESCRIPTION("Minibox graphics PicoLCD Driver");
MODULE_LICENSE("GPL v2");
