<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम Lenovo:
 *  - ThinkPad USB Keyboard with TrackPoपूर्णांक (tpkbd)
 *  - ThinkPad Compact Bluetooth Keyboard with TrackPoपूर्णांक (cptkbd)
 *  - ThinkPad Compact USB Keyboard with TrackPoपूर्णांक (cptkbd)
 *
 *  Copyright (c) 2012 Bernhard Seibold
 *  Copyright (c) 2014 Jamie Lentin <jm@lentin.co.uk>
 *
 * Linux IBM/Lenovo Scrollpoपूर्णांक mouse driver:
 * - IBM Scrollpoपूर्णांक III
 * - IBM Scrollpoपूर्णांक Pro
 * - IBM Scrollpoपूर्णांक Optical
 * - IBM Scrollpoपूर्णांक Optical 800dpi
 * - IBM Scrollpoपूर्णांक Optical 800dpi Pro
 * - Lenovo Scrollpoपूर्णांक Optical
 *
 *  Copyright (c) 2012 Peter De Wachter <pdewacht@gmail.com>
 *  Copyright (c) 2018 Peter Ganzhorn <peter.ganzhorn@gmail.com>
 */

/*
 */

#समावेश <linux/module.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/input.h>
#समावेश <linux/leds.h>
#समावेश <linux/workqueue.h>

#समावेश "hid-ids.h"

/* Userspace expects F20 क्रम mic-mute KEY_MICMUTE करोes not work */
#घोषणा LENOVO_KEY_MICMUTE KEY_F20

काष्ठा lenovo_drvdata अणु
	u8 led_report[3]; /* Must be first क्रम proper alignment */
	पूर्णांक led_state;
	काष्ठा mutex led_report_mutex;
	काष्ठा led_classdev led_mute;
	काष्ठा led_classdev led_micmute;
	काष्ठा work_काष्ठा fn_lock_sync_work;
	काष्ठा hid_device *hdev;
	पूर्णांक press_to_select;
	पूर्णांक dragging;
	पूर्णांक release_to_select;
	पूर्णांक select_right;
	पूर्णांक sensitivity;
	पूर्णांक press_speed;
	u8 middlebutton_state; /* 0:Up, 1:Down (undecided), 2:Scrolling */
	bool fn_lock;
पूर्ण;

#घोषणा map_key_clear(c) hid_map_usage_clear(hi, usage, bit, max, EV_KEY, (c))

#घोषणा TP10UBKBD_LED_OUTPUT_REPORT	9

#घोषणा TP10UBKBD_FN_LOCK_LED		0x54
#घोषणा TP10UBKBD_MUTE_LED		0x64
#घोषणा TP10UBKBD_MICMUTE_LED		0x74

#घोषणा TP10UBKBD_LED_OFF		1
#घोषणा TP10UBKBD_LED_ON		2

अटल पूर्णांक lenovo_led_set_tp10ubkbd(काष्ठा hid_device *hdev, u8 led_code,
				    क्रमागत led_brightness value)
अणु
	काष्ठा lenovo_drvdata *data = hid_get_drvdata(hdev);
	पूर्णांक ret;

	mutex_lock(&data->led_report_mutex);

	data->led_report[0] = TP10UBKBD_LED_OUTPUT_REPORT;
	data->led_report[1] = led_code;
	data->led_report[2] = value ? TP10UBKBD_LED_ON : TP10UBKBD_LED_OFF;
	ret = hid_hw_raw_request(hdev, data->led_report[0], data->led_report, 3,
				 HID_OUTPUT_REPORT, HID_REQ_SET_REPORT);
	अगर (ret != 3) अणु
		अगर (ret != -ENODEV)
			hid_err(hdev, "Set LED output report error: %d\n", ret);

		ret = ret < 0 ? ret : -EIO;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	mutex_unlock(&data->led_report_mutex);

	वापस ret;
पूर्ण

अटल व्योम lenovo_tp10ubkbd_sync_fn_lock(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lenovo_drvdata *data =
		container_of(work, काष्ठा lenovo_drvdata, fn_lock_sync_work);

	lenovo_led_set_tp10ubkbd(data->hdev, TP10UBKBD_FN_LOCK_LED,
				 data->fn_lock);
पूर्ण

अटल स्थिर __u8 lenovo_pro_करोck_need_fixup_collection[] = अणु
	0x05, 0x88,		/* Usage Page (Venकरोr Usage Page 0x88)	*/
	0x09, 0x01,		/* Usage (Venकरोr Usage 0x01)		*/
	0xa1, 0x01,		/* Collection (Application)		*/
	0x85, 0x04,		/*  Report ID (4)			*/
	0x19, 0x00,		/*  Usage Minimum (0)			*/
	0x2a, 0xff, 0xff,	/*  Usage Maximum (65535)		*/
पूर्ण;

अटल __u8 *lenovo_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	चयन (hdev->product) अणु
	हाल USB_DEVICE_ID_LENOVO_TPPRODOCK:
		/* the fixups that need to be करोne:
		 *   - get a reasonable usage max क्रम the venकरोr collection
		 *     0x8801 from the report ID 4
		 */
		अगर (*rsize >= 153 &&
		    स_भेद(&rdesc[140], lenovo_pro_करोck_need_fixup_collection,
			  माप(lenovo_pro_करोck_need_fixup_collection)) == 0) अणु
			rdesc[151] = 0x01;
			rdesc[152] = 0x00;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस rdesc;
पूर्ण

अटल पूर्णांक lenovo_input_mapping_tpkbd(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hi, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर (usage->hid == (HID_UP_BUTTON | 0x0010)) अणु
		/* This sub-device contains trackpoपूर्णांक, mark it */
		hid_set_drvdata(hdev, (व्योम *)1);
		map_key_clear(LENOVO_KEY_MICMUTE);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lenovo_input_mapping_cptkbd(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hi, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	/* HID_UP_LNVENDOR = USB, HID_UP_MSVENDOR = BT */
	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_MSVENDOR ||
	    (usage->hid & HID_USAGE_PAGE) == HID_UP_LNVENDOR) अणु
		चयन (usage->hid & HID_USAGE) अणु
		हाल 0x00f1: /* Fn-F4: Mic mute */
			map_key_clear(LENOVO_KEY_MICMUTE);
			वापस 1;
		हाल 0x00f2: /* Fn-F5: Brightness करोwn */
			map_key_clear(KEY_BRIGHTNESSDOWN);
			वापस 1;
		हाल 0x00f3: /* Fn-F6: Brightness up */
			map_key_clear(KEY_BRIGHTNESSUP);
			वापस 1;
		हाल 0x00f4: /* Fn-F7: External display (projector) */
			map_key_clear(KEY_SWITCHVIDEOMODE);
			वापस 1;
		हाल 0x00f5: /* Fn-F8: Wireless */
			map_key_clear(KEY_WLAN);
			वापस 1;
		हाल 0x00f6: /* Fn-F9: Control panel */
			map_key_clear(KEY_CONFIG);
			वापस 1;
		हाल 0x00f8: /* Fn-F11: View खोलो applications (3 boxes) */
			map_key_clear(KEY_SCALE);
			वापस 1;
		हाल 0x00f9: /* Fn-F12: Open My computer (6 boxes) USB-only */
			/* NB: This mapping is invented in raw_event below */
			map_key_clear(KEY_खाता);
			वापस 1;
		हाल 0x00fa: /* Fn-Esc: Fn-lock toggle */
			map_key_clear(KEY_FN_ESC);
			वापस 1;
		हाल 0x00fb: /* Middle mouse button (in native mode) */
			map_key_clear(BTN_MIDDLE);
			वापस 1;
		पूर्ण
	पूर्ण

	/* Compatibility middle/wheel mappings should be ignored */
	अगर (usage->hid == HID_GD_WHEEL)
		वापस -1;
	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON &&
			(usage->hid & HID_USAGE) == 0x003)
		वापस -1;
	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_CONSUMER &&
			(usage->hid & HID_USAGE) == 0x238)
		वापस -1;

	/* Map wheel emulation reports: 0xffa1 = USB, 0xff10 = BT */
	अगर ((usage->hid & HID_USAGE_PAGE) == 0xff100000 ||
	    (usage->hid & HID_USAGE_PAGE) == 0xffa10000) अणु
		field->flags |= HID_MAIN_ITEM_RELATIVE | HID_MAIN_ITEM_VARIABLE;
		field->logical_minimum = -127;
		field->logical_maximum = 127;

		चयन (usage->hid & HID_USAGE) अणु
		हाल 0x0000:
			hid_map_usage(hi, usage, bit, max, EV_REL, REL_HWHEEL);
			वापस 1;
		हाल 0x0001:
			hid_map_usage(hi, usage, bit, max, EV_REL, REL_WHEEL);
			वापस 1;
		शेष:
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lenovo_input_mapping_scrollpoपूर्णांक(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hi, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर (usage->hid == HID_GD_Z) अणु
		hid_map_usage(hi, usage, bit, max, EV_REL, REL_HWHEEL);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lenovo_input_mapping_tp10_ultrabook_kbd(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hi, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	/*
	 * The ThinkPad 10 Ultrabook Keyboard uses 0x000c0001 usage क्रम
	 * a bunch of keys which have no standard consumer page code.
	 */
	अगर (usage->hid == 0x000c0001) अणु
		चयन (usage->usage_index) अणु
		हाल 8: /* Fn-Esc: Fn-lock toggle */
			map_key_clear(KEY_FN_ESC);
			वापस 1;
		हाल 9: /* Fn-F4: Mic mute */
			map_key_clear(LENOVO_KEY_MICMUTE);
			वापस 1;
		हाल 10: /* Fn-F7: Control panel */
			map_key_clear(KEY_CONFIG);
			वापस 1;
		हाल 11: /* Fn-F8: Search (magnअगरier glass) */
			map_key_clear(KEY_SEARCH);
			वापस 1;
		हाल 12: /* Fn-F10: Open My computer (6 boxes) */
			map_key_clear(KEY_खाता);
			वापस 1;
		पूर्ण
	पूर्ण

	/*
	 * The Ultrabook Keyboard sends a spurious F23 key-press when resuming
	 * from suspend and it करोes not actually have a F23 key, ignore it.
	 */
	अगर (usage->hid == 0x00070072)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक lenovo_input_mapping_x1_tab_kbd(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hi, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	/*
	 * The ThinkPad X1 Tablet Thin Keyboard uses 0x000c0001 usage क्रम
	 * a bunch of keys which have no standard consumer page code.
	 */
	अगर (usage->hid == 0x000c0001) अणु
		चयन (usage->usage_index) अणु
		हाल 0: /* Fn-F10: Enable/disable bluetooth */
			map_key_clear(KEY_BLUETOOTH);
			वापस 1;
		हाल 1: /* Fn-F11: Keyboard settings */
			map_key_clear(KEY_KEYBOARD);
			वापस 1;
		हाल 2: /* Fn-F12: User function / Cortana */
			map_key_clear(KEY_MACRO1);
			वापस 1;
		हाल 3: /* Fn-PrtSc: Snipping tool */
			map_key_clear(KEY_SELECTIVE_SCREENSHOT);
			वापस 1;
		हाल 8: /* Fn-Esc: Fn-lock toggle */
			map_key_clear(KEY_FN_ESC);
			वापस 1;
		हाल 9: /* Fn-F4: Mute/unmute microphone */
			map_key_clear(KEY_MICMUTE);
			वापस 1;
		हाल 10: /* Fn-F9: Settings */
			map_key_clear(KEY_CONFIG);
			वापस 1;
		हाल 13: /* Fn-F7: Manage बाह्यal displays */
			map_key_clear(KEY_SWITCHVIDEOMODE);
			वापस 1;
		हाल 14: /* Fn-F8: Enable/disable wअगरi */
			map_key_clear(KEY_WLAN);
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (usage->hid == (HID_UP_KEYBOARD | 0x009a)) अणु
		map_key_clear(KEY_SYSRQ);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lenovo_input_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hi, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	चयन (hdev->product) अणु
	हाल USB_DEVICE_ID_LENOVO_TPKBD:
		वापस lenovo_input_mapping_tpkbd(hdev, hi, field,
							usage, bit, max);
	हाल USB_DEVICE_ID_LENOVO_CUSBKBD:
	हाल USB_DEVICE_ID_LENOVO_CBTKBD:
		वापस lenovo_input_mapping_cptkbd(hdev, hi, field,
							usage, bit, max);
	हाल USB_DEVICE_ID_IBM_SCROLLPOINT_III:
	हाल USB_DEVICE_ID_IBM_SCROLLPOINT_PRO:
	हाल USB_DEVICE_ID_IBM_SCROLLPOINT_OPTICAL:
	हाल USB_DEVICE_ID_IBM_SCROLLPOINT_800DPI_OPTICAL:
	हाल USB_DEVICE_ID_IBM_SCROLLPOINT_800DPI_OPTICAL_PRO:
	हाल USB_DEVICE_ID_LENOVO_SCROLLPOINT_OPTICAL:
		वापस lenovo_input_mapping_scrollpoपूर्णांक(hdev, hi, field,
							usage, bit, max);
	हाल USB_DEVICE_ID_LENOVO_TP10UBKBD:
		वापस lenovo_input_mapping_tp10_ultrabook_kbd(hdev, hi, field,
							       usage, bit, max);
	हाल USB_DEVICE_ID_LENOVO_X1_TAB:
		वापस lenovo_input_mapping_x1_tab_kbd(hdev, hi, field, usage, bit, max);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

#अघोषित map_key_clear

/* Send a config command to the keyboard */
अटल पूर्णांक lenovo_send_cmd_cptkbd(काष्ठा hid_device *hdev,
			अचिन्हित अक्षर byte2, अचिन्हित अक्षर byte3)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर *buf;

	buf = kzalloc(3, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf[0] = 0x18;
	buf[1] = byte2;
	buf[2] = byte3;

	चयन (hdev->product) अणु
	हाल USB_DEVICE_ID_LENOVO_CUSBKBD:
		ret = hid_hw_raw_request(hdev, 0x13, buf, 3,
					HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
		अवरोध;
	हाल USB_DEVICE_ID_LENOVO_CBTKBD:
		ret = hid_hw_output_report(hdev, buf, 3);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	kमुक्त(buf);

	वापस ret < 0 ? ret : 0; /* BT वापसs 0, USB वापसs माप(buf) */
पूर्ण

अटल व्योम lenovo_features_set_cptkbd(काष्ठा hid_device *hdev)
अणु
	पूर्णांक ret;
	काष्ठा lenovo_drvdata *cptkbd_data = hid_get_drvdata(hdev);

	ret = lenovo_send_cmd_cptkbd(hdev, 0x05, cptkbd_data->fn_lock);
	अगर (ret)
		hid_err(hdev, "Fn-lock setting failed: %d\n", ret);

	ret = lenovo_send_cmd_cptkbd(hdev, 0x02, cptkbd_data->sensitivity);
	अगर (ret)
		hid_err(hdev, "Sensitivity setting failed: %d\n", ret);
पूर्ण

अटल sमाप_प्रकार attr_fn_lock_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *data = hid_get_drvdata(hdev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", data->fn_lock);
पूर्ण

अटल sमाप_प्रकार attr_fn_lock_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *data = hid_get_drvdata(hdev);
	पूर्णांक value, ret;

	अगर (kstrtoपूर्णांक(buf, 10, &value))
		वापस -EINVAL;
	अगर (value < 0 || value > 1)
		वापस -EINVAL;

	data->fn_lock = !!value;

	चयन (hdev->product) अणु
	हाल USB_DEVICE_ID_LENOVO_CUSBKBD:
	हाल USB_DEVICE_ID_LENOVO_CBTKBD:
		lenovo_features_set_cptkbd(hdev);
		अवरोध;
	हाल USB_DEVICE_ID_LENOVO_TP10UBKBD:
	हाल USB_DEVICE_ID_LENOVO_X1_TAB:
		ret = lenovo_led_set_tp10ubkbd(hdev, TP10UBKBD_FN_LOCK_LED, value);
		अगर (ret)
			वापस ret;
		अवरोध;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार attr_sensitivity_show_cptkbd(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *cptkbd_data = hid_get_drvdata(hdev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n",
		cptkbd_data->sensitivity);
पूर्ण

अटल sमाप_प्रकार attr_sensitivity_store_cptkbd(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *cptkbd_data = hid_get_drvdata(hdev);
	पूर्णांक value;

	अगर (kstrtoपूर्णांक(buf, 10, &value) || value < 1 || value > 255)
		वापस -EINVAL;

	cptkbd_data->sensitivity = value;
	lenovo_features_set_cptkbd(hdev);

	वापस count;
पूर्ण


अटल काष्ठा device_attribute dev_attr_fn_lock =
	__ATTR(fn_lock, S_IWUSR | S_IRUGO,
			attr_fn_lock_show,
			attr_fn_lock_store);

अटल काष्ठा device_attribute dev_attr_sensitivity_cptkbd =
	__ATTR(sensitivity, S_IWUSR | S_IRUGO,
			attr_sensitivity_show_cptkbd,
			attr_sensitivity_store_cptkbd);


अटल काष्ठा attribute *lenovo_attributes_cptkbd[] = अणु
	&dev_attr_fn_lock.attr,
	&dev_attr_sensitivity_cptkbd.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lenovo_attr_group_cptkbd = अणु
	.attrs = lenovo_attributes_cptkbd,
पूर्ण;

अटल पूर्णांक lenovo_raw_event(काष्ठा hid_device *hdev,
			काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	/*
	 * Compact USB keyboard's Fn-F12 report holds करोwn many other keys, and
	 * its own key is outside the usage page range. Remove extra
	 * keypresses and remap to inside usage page.
	 */
	अगर (unlikely(hdev->product == USB_DEVICE_ID_LENOVO_CUSBKBD
			&& size == 3
			&& data[0] == 0x15
			&& data[1] == 0x94
			&& data[2] == 0x01)) अणु
		data[1] = 0x00;
		data[2] = 0x01;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lenovo_event_tp10ubkbd(काष्ठा hid_device *hdev,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा lenovo_drvdata *data = hid_get_drvdata(hdev);

	अगर (usage->type == EV_KEY && usage->code == KEY_FN_ESC && value == 1) अणु
		/*
		 * The user has toggled the Fn-lock state. Toggle our own
		 * cached value of it and sync our value to the keyboard to
		 * ensure things are in sync (the sycning should be a no-op).
		 */
		data->fn_lock = !data->fn_lock;
		schedule_work(&data->fn_lock_sync_work);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lenovo_event_cptkbd(काष्ठा hid_device *hdev,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा lenovo_drvdata *cptkbd_data = hid_get_drvdata(hdev);

	/* "wheel" scroll events */
	अगर (usage->type == EV_REL && (usage->code == REL_WHEEL ||
			usage->code == REL_HWHEEL)) अणु
		/* Scroll events disable middle-click event */
		cptkbd_data->middlebutton_state = 2;
		वापस 0;
	पूर्ण

	/* Middle click events */
	अगर (usage->type == EV_KEY && usage->code == BTN_MIDDLE) अणु
		अगर (value == 1) अणु
			cptkbd_data->middlebutton_state = 1;
		पूर्ण अन्यथा अगर (value == 0) अणु
			अगर (cptkbd_data->middlebutton_state == 1) अणु
				/* No scrolling inbetween, send middle-click */
				input_event(field->hidinput->input,
					EV_KEY, BTN_MIDDLE, 1);
				input_sync(field->hidinput->input);
				input_event(field->hidinput->input,
					EV_KEY, BTN_MIDDLE, 0);
				input_sync(field->hidinput->input);
			पूर्ण
			cptkbd_data->middlebutton_state = 0;
		पूर्ण
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lenovo_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	अगर (!hid_get_drvdata(hdev))
		वापस 0;

	चयन (hdev->product) अणु
	हाल USB_DEVICE_ID_LENOVO_CUSBKBD:
	हाल USB_DEVICE_ID_LENOVO_CBTKBD:
		वापस lenovo_event_cptkbd(hdev, field, usage, value);
	हाल USB_DEVICE_ID_LENOVO_TP10UBKBD:
	हाल USB_DEVICE_ID_LENOVO_X1_TAB:
		वापस lenovo_event_tp10ubkbd(hdev, field, usage, value);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक lenovo_features_set_tpkbd(काष्ठा hid_device *hdev)
अणु
	काष्ठा hid_report *report;
	काष्ठा lenovo_drvdata *data_poपूर्णांकer = hid_get_drvdata(hdev);

	report = hdev->report_क्रमागत[HID_FEATURE_REPORT].report_id_hash[4];

	report->field[0]->value[0]  = data_poपूर्णांकer->press_to_select   ? 0x01 : 0x02;
	report->field[0]->value[0] |= data_poपूर्णांकer->dragging          ? 0x04 : 0x08;
	report->field[0]->value[0] |= data_poपूर्णांकer->release_to_select ? 0x10 : 0x20;
	report->field[0]->value[0] |= data_poपूर्णांकer->select_right      ? 0x80 : 0x40;
	report->field[1]->value[0] = 0x03; // unknown setting, imitate winकरोws driver
	report->field[2]->value[0] = data_poपूर्णांकer->sensitivity;
	report->field[3]->value[0] = data_poपूर्णांकer->press_speed;

	hid_hw_request(hdev, report, HID_REQ_SET_REPORT);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार attr_press_to_select_show_tpkbd(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *data_poपूर्णांकer = hid_get_drvdata(hdev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", data_poपूर्णांकer->press_to_select);
पूर्ण

अटल sमाप_प्रकार attr_press_to_select_store_tpkbd(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *data_poपूर्णांकer = hid_get_drvdata(hdev);
	पूर्णांक value;

	अगर (kstrtoपूर्णांक(buf, 10, &value))
		वापस -EINVAL;
	अगर (value < 0 || value > 1)
		वापस -EINVAL;

	data_poपूर्णांकer->press_to_select = value;
	lenovo_features_set_tpkbd(hdev);

	वापस count;
पूर्ण

अटल sमाप_प्रकार attr_dragging_show_tpkbd(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *data_poपूर्णांकer = hid_get_drvdata(hdev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", data_poपूर्णांकer->dragging);
पूर्ण

अटल sमाप_प्रकार attr_dragging_store_tpkbd(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *data_poपूर्णांकer = hid_get_drvdata(hdev);
	पूर्णांक value;

	अगर (kstrtoपूर्णांक(buf, 10, &value))
		वापस -EINVAL;
	अगर (value < 0 || value > 1)
		वापस -EINVAL;

	data_poपूर्णांकer->dragging = value;
	lenovo_features_set_tpkbd(hdev);

	वापस count;
पूर्ण

अटल sमाप_प्रकार attr_release_to_select_show_tpkbd(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *data_poपूर्णांकer = hid_get_drvdata(hdev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", data_poपूर्णांकer->release_to_select);
पूर्ण

अटल sमाप_प्रकार attr_release_to_select_store_tpkbd(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *data_poपूर्णांकer = hid_get_drvdata(hdev);
	पूर्णांक value;

	अगर (kstrtoपूर्णांक(buf, 10, &value))
		वापस -EINVAL;
	अगर (value < 0 || value > 1)
		वापस -EINVAL;

	data_poपूर्णांकer->release_to_select = value;
	lenovo_features_set_tpkbd(hdev);

	वापस count;
पूर्ण

अटल sमाप_प्रकार attr_select_right_show_tpkbd(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *data_poपूर्णांकer = hid_get_drvdata(hdev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", data_poपूर्णांकer->select_right);
पूर्ण

अटल sमाप_प्रकार attr_select_right_store_tpkbd(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *data_poपूर्णांकer = hid_get_drvdata(hdev);
	पूर्णांक value;

	अगर (kstrtoपूर्णांक(buf, 10, &value))
		वापस -EINVAL;
	अगर (value < 0 || value > 1)
		वापस -EINVAL;

	data_poपूर्णांकer->select_right = value;
	lenovo_features_set_tpkbd(hdev);

	वापस count;
पूर्ण

अटल sमाप_प्रकार attr_sensitivity_show_tpkbd(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *data_poपूर्णांकer = hid_get_drvdata(hdev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n",
		data_poपूर्णांकer->sensitivity);
पूर्ण

अटल sमाप_प्रकार attr_sensitivity_store_tpkbd(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *data_poपूर्णांकer = hid_get_drvdata(hdev);
	पूर्णांक value;

	अगर (kstrtoपूर्णांक(buf, 10, &value) || value < 1 || value > 255)
		वापस -EINVAL;

	data_poपूर्णांकer->sensitivity = value;
	lenovo_features_set_tpkbd(hdev);

	वापस count;
पूर्ण

अटल sमाप_प्रकार attr_press_speed_show_tpkbd(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *data_poपूर्णांकer = hid_get_drvdata(hdev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n",
		data_poपूर्णांकer->press_speed);
पूर्ण

अटल sमाप_प्रकार attr_press_speed_store_tpkbd(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *data_poपूर्णांकer = hid_get_drvdata(hdev);
	पूर्णांक value;

	अगर (kstrtoपूर्णांक(buf, 10, &value) || value < 1 || value > 255)
		वापस -EINVAL;

	data_poपूर्णांकer->press_speed = value;
	lenovo_features_set_tpkbd(hdev);

	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_press_to_select_tpkbd =
	__ATTR(press_to_select, S_IWUSR | S_IRUGO,
			attr_press_to_select_show_tpkbd,
			attr_press_to_select_store_tpkbd);

अटल काष्ठा device_attribute dev_attr_dragging_tpkbd =
	__ATTR(dragging, S_IWUSR | S_IRUGO,
			attr_dragging_show_tpkbd,
			attr_dragging_store_tpkbd);

अटल काष्ठा device_attribute dev_attr_release_to_select_tpkbd =
	__ATTR(release_to_select, S_IWUSR | S_IRUGO,
			attr_release_to_select_show_tpkbd,
			attr_release_to_select_store_tpkbd);

अटल काष्ठा device_attribute dev_attr_select_right_tpkbd =
	__ATTR(select_right, S_IWUSR | S_IRUGO,
			attr_select_right_show_tpkbd,
			attr_select_right_store_tpkbd);

अटल काष्ठा device_attribute dev_attr_sensitivity_tpkbd =
	__ATTR(sensitivity, S_IWUSR | S_IRUGO,
			attr_sensitivity_show_tpkbd,
			attr_sensitivity_store_tpkbd);

अटल काष्ठा device_attribute dev_attr_press_speed_tpkbd =
	__ATTR(press_speed, S_IWUSR | S_IRUGO,
			attr_press_speed_show_tpkbd,
			attr_press_speed_store_tpkbd);

अटल काष्ठा attribute *lenovo_attributes_tpkbd[] = अणु
	&dev_attr_press_to_select_tpkbd.attr,
	&dev_attr_dragging_tpkbd.attr,
	&dev_attr_release_to_select_tpkbd.attr,
	&dev_attr_select_right_tpkbd.attr,
	&dev_attr_sensitivity_tpkbd.attr,
	&dev_attr_press_speed_tpkbd.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lenovo_attr_group_tpkbd = अणु
	.attrs = lenovo_attributes_tpkbd,
पूर्ण;

अटल व्योम lenovo_led_set_tpkbd(काष्ठा hid_device *hdev)
अणु
	काष्ठा lenovo_drvdata *data_poपूर्णांकer = hid_get_drvdata(hdev);
	काष्ठा hid_report *report;

	report = hdev->report_क्रमागत[HID_OUTPUT_REPORT].report_id_hash[3];
	report->field[0]->value[0] = (data_poपूर्णांकer->led_state >> 0) & 1;
	report->field[0]->value[1] = (data_poपूर्णांकer->led_state >> 1) & 1;
	hid_hw_request(hdev, report, HID_REQ_SET_REPORT);
पूर्ण

अटल पूर्णांक lenovo_led_brightness_set(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness value)
अणु
	काष्ठा device *dev = led_cdev->dev->parent;
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा lenovo_drvdata *data_poपूर्णांकer = hid_get_drvdata(hdev);
	u8 tp10ubkbd_led[] = अणु TP10UBKBD_MUTE_LED, TP10UBKBD_MICMUTE_LED पूर्ण;
	पूर्णांक led_nr = 0;
	पूर्णांक ret = 0;

	अगर (led_cdev == &data_poपूर्णांकer->led_micmute)
		led_nr = 1;

	अगर (value == LED_OFF)
		data_poपूर्णांकer->led_state &= ~(1 << led_nr);
	अन्यथा
		data_poपूर्णांकer->led_state |= 1 << led_nr;

	चयन (hdev->product) अणु
	हाल USB_DEVICE_ID_LENOVO_TPKBD:
		lenovo_led_set_tpkbd(hdev);
		अवरोध;
	हाल USB_DEVICE_ID_LENOVO_TP10UBKBD:
	हाल USB_DEVICE_ID_LENOVO_X1_TAB:
		ret = lenovo_led_set_tp10ubkbd(hdev, tp10ubkbd_led[led_nr], value);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक lenovo_रेजिस्टर_leds(काष्ठा hid_device *hdev)
अणु
	काष्ठा lenovo_drvdata *data = hid_get_drvdata(hdev);
	माप_प्रकार name_sz = म_माप(dev_name(&hdev->dev)) + 16;
	अक्षर *name_mute, *name_micm;
	पूर्णांक ret;

	name_mute = devm_kzalloc(&hdev->dev, name_sz, GFP_KERNEL);
	name_micm = devm_kzalloc(&hdev->dev, name_sz, GFP_KERNEL);
	अगर (name_mute == शून्य || name_micm == शून्य) अणु
		hid_err(hdev, "Could not allocate memory for led data\n");
		वापस -ENOMEM;
	पूर्ण
	snम_लिखो(name_mute, name_sz, "%s:amber:mute", dev_name(&hdev->dev));
	snम_लिखो(name_micm, name_sz, "%s:amber:micmute", dev_name(&hdev->dev));

	data->led_mute.name = name_mute;
	data->led_mute.शेष_trigger = "audio-mute";
	data->led_mute.brightness_set_blocking = lenovo_led_brightness_set;
	data->led_mute.max_brightness = 1;
	data->led_mute.flags = LED_HW_PLUGGABLE;
	data->led_mute.dev = &hdev->dev;
	ret = led_classdev_रेजिस्टर(&hdev->dev, &data->led_mute);
	अगर (ret < 0)
		वापस ret;

	data->led_micmute.name = name_micm;
	data->led_micmute.शेष_trigger = "audio-micmute";
	data->led_micmute.brightness_set_blocking = lenovo_led_brightness_set;
	data->led_micmute.max_brightness = 1;
	data->led_micmute.flags = LED_HW_PLUGGABLE;
	data->led_micmute.dev = &hdev->dev;
	ret = led_classdev_रेजिस्टर(&hdev->dev, &data->led_micmute);
	अगर (ret < 0) अणु
		led_classdev_unरेजिस्टर(&data->led_mute);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lenovo_probe_tpkbd(काष्ठा hid_device *hdev)
अणु
	काष्ठा lenovo_drvdata *data_poपूर्णांकer;
	पूर्णांक i, ret;

	/*
	 * Only रेजिस्टर extra settings against subdevice where input_mapping
	 * set drvdata to 1, i.e. the trackpoपूर्णांक.
	 */
	अगर (!hid_get_drvdata(hdev))
		वापस 0;

	hid_set_drvdata(hdev, शून्य);

	/* Validate required reports. */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (!hid_validate_values(hdev, HID_FEATURE_REPORT, 4, i, 1))
			वापस -ENODEV;
	पूर्ण
	अगर (!hid_validate_values(hdev, HID_OUTPUT_REPORT, 3, 0, 2))
		वापस -ENODEV;

	ret = sysfs_create_group(&hdev->dev.kobj, &lenovo_attr_group_tpkbd);
	अगर (ret)
		hid_warn(hdev, "Could not create sysfs group: %d\n", ret);

	data_poपूर्णांकer = devm_kzalloc(&hdev->dev,
				    माप(काष्ठा lenovo_drvdata),
				    GFP_KERNEL);
	अगर (data_poपूर्णांकer == शून्य) अणु
		hid_err(hdev, "Could not allocate memory for driver data\n");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	// set same शेष values as winकरोws driver
	data_poपूर्णांकer->sensitivity = 0xa0;
	data_poपूर्णांकer->press_speed = 0x38;

	hid_set_drvdata(hdev, data_poपूर्णांकer);

	ret = lenovo_रेजिस्टर_leds(hdev);
	अगर (ret)
		जाओ err;

	lenovo_features_set_tpkbd(hdev);

	वापस 0;
err:
	sysfs_हटाओ_group(&hdev->dev.kobj, &lenovo_attr_group_tpkbd);
	वापस ret;
पूर्ण

अटल पूर्णांक lenovo_probe_cptkbd(काष्ठा hid_device *hdev)
अणु
	पूर्णांक ret;
	काष्ठा lenovo_drvdata *cptkbd_data;

	/* All the custom action happens on the USBMOUSE device क्रम USB */
	अगर (hdev->product == USB_DEVICE_ID_LENOVO_CUSBKBD
			&& hdev->type != HID_TYPE_USBMOUSE) अणु
		hid_dbg(hdev, "Ignoring keyboard half of device\n");
		वापस 0;
	पूर्ण

	cptkbd_data = devm_kzalloc(&hdev->dev,
					माप(*cptkbd_data),
					GFP_KERNEL);
	अगर (cptkbd_data == शून्य) अणु
		hid_err(hdev, "can't alloc keyboard descriptor\n");
		वापस -ENOMEM;
	पूर्ण
	hid_set_drvdata(hdev, cptkbd_data);

	/*
	 * Tell the keyboard a driver understands it, and turn F7, F9, F11 पूर्णांकo
	 * regular keys
	 */
	ret = lenovo_send_cmd_cptkbd(hdev, 0x01, 0x03);
	अगर (ret)
		hid_warn(hdev, "Failed to switch F7/9/11 mode: %d\n", ret);

	/* Switch middle button to native mode */
	ret = lenovo_send_cmd_cptkbd(hdev, 0x09, 0x01);
	अगर (ret)
		hid_warn(hdev, "Failed to switch middle button: %d\n", ret);

	/* Set keyboard settings to known state */
	cptkbd_data->middlebutton_state = 0;
	cptkbd_data->fn_lock = true;
	cptkbd_data->sensitivity = 0x05;
	lenovo_features_set_cptkbd(hdev);

	ret = sysfs_create_group(&hdev->dev.kobj, &lenovo_attr_group_cptkbd);
	अगर (ret)
		hid_warn(hdev, "Could not create sysfs group: %d\n", ret);

	वापस 0;
पूर्ण

अटल काष्ठा attribute *lenovo_attributes_tp10ubkbd[] = अणु
	&dev_attr_fn_lock.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lenovo_attr_group_tp10ubkbd = अणु
	.attrs = lenovo_attributes_tp10ubkbd,
पूर्ण;

अटल पूर्णांक lenovo_probe_tp10ubkbd(काष्ठा hid_device *hdev)
अणु
	काष्ठा hid_report_क्रमागत *rep_क्रमागत;
	काष्ठा lenovo_drvdata *data;
	काष्ठा hid_report *rep;
	bool found;
	पूर्णांक ret;

	/*
	 * The LEDs and the Fn-lock functionality use output report 9,
	 * with an application of 0xffa0001, add the LEDs on the पूर्णांकerface
	 * with this output report.
	 */
	found = false;
	rep_क्रमागत = &hdev->report_क्रमागत[HID_OUTPUT_REPORT];
	list_क्रम_each_entry(rep, &rep_क्रमागत->report_list, list) अणु
		अगर (rep->application == 0xffa00001)
			found = true;
	पूर्ण
	अगर (!found)
		वापस 0;

	data = devm_kzalloc(&hdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	mutex_init(&data->led_report_mutex);
	INIT_WORK(&data->fn_lock_sync_work, lenovo_tp10ubkbd_sync_fn_lock);
	data->hdev = hdev;

	hid_set_drvdata(hdev, data);

	/*
	 * The Thinkpad 10 ultrabook USB kbd करोck's Fn-lock शेषs to on.
	 * We cannot पढ़ो the state, only set it, so we क्रमce it to on here
	 * (which should be a no-op) to make sure that our state matches the
	 * keyboard's FN-lock state. This is the same as what Winकरोws करोes.
	 */
	data->fn_lock = true;
	lenovo_led_set_tp10ubkbd(hdev, TP10UBKBD_FN_LOCK_LED, data->fn_lock);

	ret = sysfs_create_group(&hdev->dev.kobj, &lenovo_attr_group_tp10ubkbd);
	अगर (ret)
		वापस ret;

	ret = lenovo_रेजिस्टर_leds(hdev);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	sysfs_हटाओ_group(&hdev->dev.kobj, &lenovo_attr_group_tp10ubkbd);
	वापस ret;
पूर्ण

अटल पूर्णांक lenovo_probe(काष्ठा hid_device *hdev,
		स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "hid_parse failed\n");
		जाओ err;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hdev, "hid_hw_start failed\n");
		जाओ err;
	पूर्ण

	चयन (hdev->product) अणु
	हाल USB_DEVICE_ID_LENOVO_TPKBD:
		ret = lenovo_probe_tpkbd(hdev);
		अवरोध;
	हाल USB_DEVICE_ID_LENOVO_CUSBKBD:
	हाल USB_DEVICE_ID_LENOVO_CBTKBD:
		ret = lenovo_probe_cptkbd(hdev);
		अवरोध;
	हाल USB_DEVICE_ID_LENOVO_TP10UBKBD:
	हाल USB_DEVICE_ID_LENOVO_X1_TAB:
		ret = lenovo_probe_tp10ubkbd(hdev);
		अवरोध;
	शेष:
		ret = 0;
		अवरोध;
	पूर्ण
	अगर (ret)
		जाओ err_hid;

	वापस 0;
err_hid:
	hid_hw_stop(hdev);
err:
	वापस ret;
पूर्ण

अटल व्योम lenovo_हटाओ_tpkbd(काष्ठा hid_device *hdev)
अणु
	काष्ठा lenovo_drvdata *data_poपूर्णांकer = hid_get_drvdata(hdev);

	/*
	 * Only the trackpoपूर्णांक half of the keyboard has drvdata and stuff that
	 * needs unरेजिस्टरing.
	 */
	अगर (data_poपूर्णांकer == शून्य)
		वापस;

	sysfs_हटाओ_group(&hdev->dev.kobj,
			&lenovo_attr_group_tpkbd);

	led_classdev_unरेजिस्टर(&data_poपूर्णांकer->led_micmute);
	led_classdev_unरेजिस्टर(&data_poपूर्णांकer->led_mute);
पूर्ण

अटल व्योम lenovo_हटाओ_cptkbd(काष्ठा hid_device *hdev)
अणु
	sysfs_हटाओ_group(&hdev->dev.kobj,
			&lenovo_attr_group_cptkbd);
पूर्ण

अटल व्योम lenovo_हटाओ_tp10ubkbd(काष्ठा hid_device *hdev)
अणु
	काष्ठा lenovo_drvdata *data = hid_get_drvdata(hdev);

	अगर (data == शून्य)
		वापस;

	led_classdev_unरेजिस्टर(&data->led_micmute);
	led_classdev_unरेजिस्टर(&data->led_mute);

	sysfs_हटाओ_group(&hdev->dev.kobj, &lenovo_attr_group_tp10ubkbd);
	cancel_work_sync(&data->fn_lock_sync_work);
पूर्ण

अटल व्योम lenovo_हटाओ(काष्ठा hid_device *hdev)
अणु
	चयन (hdev->product) अणु
	हाल USB_DEVICE_ID_LENOVO_TPKBD:
		lenovo_हटाओ_tpkbd(hdev);
		अवरोध;
	हाल USB_DEVICE_ID_LENOVO_CUSBKBD:
	हाल USB_DEVICE_ID_LENOVO_CBTKBD:
		lenovo_हटाओ_cptkbd(hdev);
		अवरोध;
	हाल USB_DEVICE_ID_LENOVO_TP10UBKBD:
	हाल USB_DEVICE_ID_LENOVO_X1_TAB:
		lenovo_हटाओ_tp10ubkbd(hdev);
		अवरोध;
	पूर्ण

	hid_hw_stop(hdev);
पूर्ण

अटल पूर्णांक lenovo_input_configured(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hi)
अणु
	चयन (hdev->product) अणु
		हाल USB_DEVICE_ID_LENOVO_TPKBD:
		हाल USB_DEVICE_ID_LENOVO_CUSBKBD:
		हाल USB_DEVICE_ID_LENOVO_CBTKBD:
			अगर (test_bit(EV_REL, hi->input->evbit)) अणु
				/* set only क्रम trackpoपूर्णांक device */
				__set_bit(INPUT_PROP_POINTER, hi->input->propbit);
				__set_bit(INPUT_PROP_POINTING_STICK,
						hi->input->propbit);
			पूर्ण
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा hid_device_id lenovo_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LENOVO, USB_DEVICE_ID_LENOVO_TPKBD) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LENOVO, USB_DEVICE_ID_LENOVO_CUSBKBD) पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_LENOVO, USB_DEVICE_ID_LENOVO_CBTKBD) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LENOVO, USB_DEVICE_ID_LENOVO_TPPRODOCK) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_IBM, USB_DEVICE_ID_IBM_SCROLLPOINT_III) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_IBM, USB_DEVICE_ID_IBM_SCROLLPOINT_PRO) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_IBM, USB_DEVICE_ID_IBM_SCROLLPOINT_OPTICAL) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_IBM, USB_DEVICE_ID_IBM_SCROLLPOINT_800DPI_OPTICAL) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_IBM, USB_DEVICE_ID_IBM_SCROLLPOINT_800DPI_OPTICAL_PRO) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LENOVO, USB_DEVICE_ID_LENOVO_SCROLLPOINT_OPTICAL) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LENOVO, USB_DEVICE_ID_LENOVO_TP10UBKBD) पूर्ण,
	/*
	 * Note bind to the HID_GROUP_GENERIC group, so that we only bind to the keyboard
	 * part, जबतक letting hid-multitouch.c handle the touchpad and trackpoपूर्णांक.
	 */
	अणु HID_DEVICE(BUS_USB, HID_GROUP_GENERIC,
		     USB_VENDOR_ID_LENOVO, USB_DEVICE_ID_LENOVO_X1_TAB) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, lenovo_devices);

अटल काष्ठा hid_driver lenovo_driver = अणु
	.name = "lenovo",
	.id_table = lenovo_devices,
	.input_configured = lenovo_input_configured,
	.input_mapping = lenovo_input_mapping,
	.probe = lenovo_probe,
	.हटाओ = lenovo_हटाओ,
	.raw_event = lenovo_raw_event,
	.event = lenovo_event,
	.report_fixup = lenovo_report_fixup,
पूर्ण;
module_hid_driver(lenovo_driver);

MODULE_LICENSE("GPL");
