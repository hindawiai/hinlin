<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम Asus notebook built-in keyboard.
 *  Fixes small logical maximum to match usage maximum.
 *
 *  Currently supported devices are:
 *    EeeBook X205TA
 *    VivoBook E200HA
 *
 *  Copyright (c) 2016 Yusuke Fujimaki <usk.fujimaki@gmail.com>
 *
 *  This module based on hid-ortek by
 *  Copyright (c) 2010 Johnathon Harris <jmharris@gmail.com>
 *  Copyright (c) 2011 Jiri Kosina
 *
 *  This module has been updated to add support क्रम Asus i2c touchpad.
 *
 *  Copyright (c) 2016 Brendan McGrath <redmcg@redmandi.dyndns.org>
 *  Copyright (c) 2016 Victor Vlasenko <victor.vlasenko@sysgears.com>
 *  Copyright (c) 2016 Frederik Wenigwieser <frederik.wenigwieser@gmail.com>
 */

/*
 */

#समावेश <linux/dmi.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/x86/asus-wmi.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/usb.h> /* For to_usb_पूर्णांकerface क्रम T100 touchpad पूर्णांकf check */
#समावेश <linux/घातer_supply.h>

#समावेश "hid-ids.h"

MODULE_AUTHOR("Yusuke Fujimaki <usk.fujimaki@gmail.com>");
MODULE_AUTHOR("Brendan McGrath <redmcg@redmandi.dyndns.org>");
MODULE_AUTHOR("Victor Vlasenko <victor.vlasenko@sysgears.com>");
MODULE_AUTHOR("Frederik Wenigwieser <frederik.wenigwieser@gmail.com>");
MODULE_DESCRIPTION("Asus HID Keyboard and TouchPad");

#घोषणा T100_TPAD_INTF 2
#घोषणा MEDION_E1239T_TPAD_INTF 1

#घोषणा E1239T_TP_TOGGLE_REPORT_ID 0x05
#घोषणा T100CHI_MOUSE_REPORT_ID 0x06
#घोषणा FEATURE_REPORT_ID 0x0d
#घोषणा INPUT_REPORT_ID 0x5d
#घोषणा FEATURE_KBD_REPORT_ID 0x5a
#घोषणा FEATURE_KBD_REPORT_SIZE 16
#घोषणा FEATURE_KBD_LED_REPORT_ID1 0x5d
#घोषणा FEATURE_KBD_LED_REPORT_ID2 0x5e

#घोषणा SUPPORT_KBD_BACKLIGHT BIT(0)

#घोषणा MAX_TOUCH_MAJOR 8
#घोषणा MAX_PRESSURE 128

#घोषणा BTN_LEFT_MASK 0x01
#घोषणा CONTACT_TOOL_TYPE_MASK 0x80
#घोषणा CONTACT_X_MSB_MASK 0xf0
#घोषणा CONTACT_Y_MSB_MASK 0x0f
#घोषणा CONTACT_TOUCH_MAJOR_MASK 0x07
#घोषणा CONTACT_PRESSURE_MASK 0x7f

#घोषणा	BATTERY_REPORT_ID	(0x03)
#घोषणा	BATTERY_REPORT_SIZE	(1 + 8)
#घोषणा	BATTERY_LEVEL_MAX	((u8)255)
#घोषणा	BATTERY_STAT_DISCONNECT	(0)
#घोषणा	BATTERY_STAT_CHARGING	(1)
#घोषणा	BATTERY_STAT_FULL	(2)

#घोषणा QUIRK_FIX_NOTEBOOK_REPORT	BIT(0)
#घोषणा QUIRK_NO_INIT_REPORTS		BIT(1)
#घोषणा QUIRK_SKIP_INPUT_MAPPING	BIT(2)
#घोषणा QUIRK_IS_MULTITOUCH		BIT(3)
#घोषणा QUIRK_NO_CONSUMER_USAGES	BIT(4)
#घोषणा QUIRK_USE_KBD_BACKLIGHT		BIT(5)
#घोषणा QUIRK_T100_KEYBOARD		BIT(6)
#घोषणा QUIRK_T100CHI			BIT(7)
#घोषणा QUIRK_G752_KEYBOARD		BIT(8)
#घोषणा QUIRK_T90CHI			BIT(9)
#घोषणा QUIRK_MEDION_E1239T		BIT(10)
#घोषणा QUIRK_ROG_NKEY_KEYBOARD		BIT(11)

#घोषणा I2C_KEYBOARD_QUIRKS			(QUIRK_FIX_NOTEBOOK_REPORT | \
						 QUIRK_NO_INIT_REPORTS | \
						 QUIRK_NO_CONSUMER_USAGES)
#घोषणा I2C_TOUCHPAD_QUIRKS			(QUIRK_NO_INIT_REPORTS | \
						 QUIRK_SKIP_INPUT_MAPPING | \
						 QUIRK_IS_MULTITOUCH)

#घोषणा TRKID_SGN       ((TRKID_MAX + 1) >> 1)

काष्ठा asus_kbd_leds अणु
	काष्ठा led_classdev cdev;
	काष्ठा hid_device *hdev;
	काष्ठा work_काष्ठा work;
	अचिन्हित पूर्णांक brightness;
	bool हटाओd;
पूर्ण;

काष्ठा asus_touchpad_info अणु
	पूर्णांक max_x;
	पूर्णांक max_y;
	पूर्णांक res_x;
	पूर्णांक res_y;
	पूर्णांक contact_size;
	पूर्णांक max_contacts;
	पूर्णांक report_size;
पूर्ण;

काष्ठा asus_drvdata अणु
	अचिन्हित दीर्घ quirks;
	काष्ठा hid_device *hdev;
	काष्ठा input_dev *input;
	काष्ठा input_dev *tp_kbd_input;
	काष्ठा asus_kbd_leds *kbd_backlight;
	स्थिर काष्ठा asus_touchpad_info *tp;
	bool enable_backlight;
	काष्ठा घातer_supply *battery;
	काष्ठा घातer_supply_desc battery_desc;
	पूर्णांक battery_capacity;
	पूर्णांक battery_stat;
	bool battery_in_query;
	अचिन्हित दीर्घ battery_next_query;
पूर्ण;

अटल पूर्णांक asus_report_battery(काष्ठा asus_drvdata *, u8 *, पूर्णांक);

अटल स्थिर काष्ठा asus_touchpad_info asus_i2c_tp = अणु
	.max_x = 2794,
	.max_y = 1758,
	.contact_size = 5,
	.max_contacts = 5,
	.report_size = 28 /* 2 byte header + 5 * 5 + 1 byte footer */,
पूर्ण;

अटल स्थिर काष्ठा asus_touchpad_info asus_t100ta_tp = अणु
	.max_x = 2240,
	.max_y = 1120,
	.res_x = 30, /* units/mm */
	.res_y = 27, /* units/mm */
	.contact_size = 5,
	.max_contacts = 5,
	.report_size = 28 /* 2 byte header + 5 * 5 + 1 byte footer */,
पूर्ण;

अटल स्थिर काष्ठा asus_touchpad_info asus_t100ha_tp = अणु
	.max_x = 2640,
	.max_y = 1320,
	.res_x = 30, /* units/mm */
	.res_y = 29, /* units/mm */
	.contact_size = 5,
	.max_contacts = 5,
	.report_size = 28 /* 2 byte header + 5 * 5 + 1 byte footer */,
पूर्ण;

अटल स्थिर काष्ठा asus_touchpad_info asus_t200ta_tp = अणु
	.max_x = 3120,
	.max_y = 1716,
	.res_x = 30, /* units/mm */
	.res_y = 28, /* units/mm */
	.contact_size = 5,
	.max_contacts = 5,
	.report_size = 28 /* 2 byte header + 5 * 5 + 1 byte footer */,
पूर्ण;

अटल स्थिर काष्ठा asus_touchpad_info asus_t100chi_tp = अणु
	.max_x = 2640,
	.max_y = 1320,
	.res_x = 31, /* units/mm */
	.res_y = 29, /* units/mm */
	.contact_size = 3,
	.max_contacts = 4,
	.report_size = 15 /* 2 byte header + 3 * 4 + 1 byte footer */,
पूर्ण;

अटल स्थिर काष्ठा asus_touchpad_info medion_e1239t_tp = अणु
	.max_x = 2640,
	.max_y = 1380,
	.res_x = 29, /* units/mm */
	.res_y = 28, /* units/mm */
	.contact_size = 5,
	.max_contacts = 5,
	.report_size = 32 /* 2 byte header + 5 * 5 + 5 byte footer */,
पूर्ण;

अटल व्योम asus_report_contact_करोwn(काष्ठा asus_drvdata *drvdat,
		पूर्णांक toolType, u8 *data)
अणु
	काष्ठा input_dev *input = drvdat->input;
	पूर्णांक touch_major, pressure, x, y;

	x = (data[0] & CONTACT_X_MSB_MASK) << 4 | data[1];
	y = drvdat->tp->max_y - ((data[0] & CONTACT_Y_MSB_MASK) << 8 | data[2]);

	input_report_असल(input, ABS_MT_POSITION_X, x);
	input_report_असल(input, ABS_MT_POSITION_Y, y);

	अगर (drvdat->tp->contact_size < 5)
		वापस;

	अगर (toolType == MT_TOOL_PALM) अणु
		touch_major = MAX_TOUCH_MAJOR;
		pressure = MAX_PRESSURE;
	पूर्ण अन्यथा अणु
		touch_major = (data[3] >> 4) & CONTACT_TOUCH_MAJOR_MASK;
		pressure = data[4] & CONTACT_PRESSURE_MASK;
	पूर्ण

	input_report_असल(input, ABS_MT_TOUCH_MAJOR, touch_major);
	input_report_असल(input, ABS_MT_PRESSURE, pressure);
पूर्ण

/* Required क्रम Synaptics Palm Detection */
अटल व्योम asus_report_tool_width(काष्ठा asus_drvdata *drvdat)
अणु
	काष्ठा input_mt *mt = drvdat->input->mt;
	काष्ठा input_mt_slot *oldest;
	पूर्णांक oldid, count, i;

	अगर (drvdat->tp->contact_size < 5)
		वापस;

	oldest = शून्य;
	oldid = mt->trkid;
	count = 0;

	क्रम (i = 0; i < mt->num_slots; ++i) अणु
		काष्ठा input_mt_slot *ps = &mt->slots[i];
		पूर्णांक id = input_mt_get_value(ps, ABS_MT_TRACKING_ID);

		अगर (id < 0)
			जारी;
		अगर ((id - oldid) & TRKID_SGN) अणु
			oldest = ps;
			oldid = id;
		पूर्ण
		count++;
	पूर्ण

	अगर (oldest) अणु
		input_report_असल(drvdat->input, ABS_TOOL_WIDTH,
			input_mt_get_value(oldest, ABS_MT_TOUCH_MAJOR));
	पूर्ण
पूर्ण

अटल पूर्णांक asus_report_input(काष्ठा asus_drvdata *drvdat, u8 *data, पूर्णांक size)
अणु
	पूर्णांक i, toolType = MT_TOOL_FINGER;
	u8 *contactData = data + 2;

	अगर (size != drvdat->tp->report_size)
		वापस 0;

	क्रम (i = 0; i < drvdat->tp->max_contacts; i++) अणु
		bool करोwn = !!(data[1] & BIT(i+3));

		अगर (drvdat->tp->contact_size >= 5)
			toolType = contactData[3] & CONTACT_TOOL_TYPE_MASK ?
						MT_TOOL_PALM : MT_TOOL_FINGER;

		input_mt_slot(drvdat->input, i);
		input_mt_report_slot_state(drvdat->input, toolType, करोwn);

		अगर (करोwn) अणु
			asus_report_contact_करोwn(drvdat, toolType, contactData);
			contactData += drvdat->tp->contact_size;
		पूर्ण
	पूर्ण

	input_report_key(drvdat->input, BTN_LEFT, data[1] & BTN_LEFT_MASK);
	asus_report_tool_width(drvdat);

	input_mt_sync_frame(drvdat->input);
	input_sync(drvdat->input);

	वापस 1;
पूर्ण

अटल पूर्णांक asus_e1239t_event(काष्ठा asus_drvdata *drvdat, u8 *data, पूर्णांक size)
अणु
	अगर (size != 3)
		वापस 0;

	/* Handle broken mute key which only sends press events */
	अगर (!drvdat->tp &&
	    data[0] == 0x02 && data[1] == 0xe2 && data[2] == 0x00) अणु
		input_report_key(drvdat->input, KEY_MUTE, 1);
		input_sync(drvdat->input);
		input_report_key(drvdat->input, KEY_MUTE, 0);
		input_sync(drvdat->input);
		वापस 1;
	पूर्ण

	/* Handle custom touchpad toggle key which only sends press events */
	अगर (drvdat->tp_kbd_input &&
	    data[0] == 0x05 && data[1] == 0x02 && data[2] == 0x28) अणु
		input_report_key(drvdat->tp_kbd_input, KEY_F21, 1);
		input_sync(drvdat->tp_kbd_input);
		input_report_key(drvdat->tp_kbd_input, KEY_F21, 0);
		input_sync(drvdat->tp_kbd_input);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक asus_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		      काष्ठा hid_usage *usage, __s32 value)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) == 0xff310000 &&
	    (usage->hid & HID_USAGE) != 0x00 &&
	    (usage->hid & HID_USAGE) != 0xff && !usage->type) अणु
		hid_warn(hdev, "Unmapped Asus vendor usagepage code 0x%02x\n",
			 usage->hid & HID_USAGE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक asus_raw_event(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	काष्ठा asus_drvdata *drvdata = hid_get_drvdata(hdev);

	अगर (drvdata->battery && data[0] == BATTERY_REPORT_ID)
		वापस asus_report_battery(drvdata, data, size);

	अगर (drvdata->tp && data[0] == INPUT_REPORT_ID)
		वापस asus_report_input(drvdata, data, size);

	अगर (drvdata->quirks & QUIRK_MEDION_E1239T)
		वापस asus_e1239t_event(drvdata, data, size);

	अगर (drvdata->quirks & QUIRK_USE_KBD_BACKLIGHT) अणु
		/*
		 * Skip these report ID, the device emits a continuous stream associated
		 * with the AURA mode it is in which looks like an 'echo'.
		*/
		अगर (report->id == FEATURE_KBD_LED_REPORT_ID1 ||
				report->id == FEATURE_KBD_LED_REPORT_ID2) अणु
			वापस -1;
		/* Additional report filtering */
		पूर्ण अन्यथा अगर (report->id == FEATURE_KBD_REPORT_ID) अणु
			/*
			 * G14 and G15 send these codes on some keypresses with no
			 * discernable reason क्रम करोing so. We'll filter them out to aव्योम
			 * unmapped warning messages later.
			*/
			अगर (data[1] == 0xea || data[1] == 0xec || data[1] == 0x02 ||
					data[1] == 0x8a || data[1] == 0x9e) अणु
				वापस -1;
			पूर्ण
		पूर्ण
		अगर (drvdata->quirks & QUIRK_ROG_NKEY_KEYBOARD) अणु
			/*
			 * G713 and G733 send these codes on some keypresses, depending on
			 * the key pressed it can trigger a shutकरोwn event अगर not caught.
			*/
			अगर(data[0] == 0x02 && data[1] == 0x30) अणु
				वापस -1;
			पूर्ण
		पूर्ण

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक asus_kbd_set_report(काष्ठा hid_device *hdev, u8 *buf, माप_प्रकार buf_size)
अणु
	अचिन्हित अक्षर *dmabuf;
	पूर्णांक ret;

	dmabuf = kmemdup(buf, buf_size, GFP_KERNEL);
	अगर (!dmabuf)
		वापस -ENOMEM;

	/*
	 * The report ID should be set from the incoming buffer due to LED and key
	 * पूर्णांकerfaces having dअगरferent pages
	*/
	ret = hid_hw_raw_request(hdev, buf[0], dmabuf,
				 buf_size, HID_FEATURE_REPORT,
				 HID_REQ_SET_REPORT);
	kमुक्त(dmabuf);

	वापस ret;
पूर्ण

अटल पूर्णांक asus_kbd_init(काष्ठा hid_device *hdev)
अणु
	u8 buf[] = अणु FEATURE_KBD_REPORT_ID, 0x41, 0x53, 0x55, 0x53, 0x20, 0x54,
		     0x65, 0x63, 0x68, 0x2e, 0x49, 0x6e, 0x63, 0x2e, 0x00 पूर्ण;
	पूर्णांक ret;

	ret = asus_kbd_set_report(hdev, buf, माप(buf));
	अगर (ret < 0)
		hid_err(hdev, "Asus failed to send init command: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक asus_kbd_get_functions(काष्ठा hid_device *hdev,
				  अचिन्हित अक्षर *kbd_func)
अणु
	u8 buf[] = अणु FEATURE_KBD_REPORT_ID, 0x05, 0x20, 0x31, 0x00, 0x08 पूर्ण;
	u8 *पढ़ोbuf;
	पूर्णांक ret;

	ret = asus_kbd_set_report(hdev, buf, माप(buf));
	अगर (ret < 0) अणु
		hid_err(hdev, "Asus failed to send configuration command: %d\n", ret);
		वापस ret;
	पूर्ण

	पढ़ोbuf = kzalloc(FEATURE_KBD_REPORT_SIZE, GFP_KERNEL);
	अगर (!पढ़ोbuf)
		वापस -ENOMEM;

	ret = hid_hw_raw_request(hdev, FEATURE_KBD_REPORT_ID, पढ़ोbuf,
				 FEATURE_KBD_REPORT_SIZE, HID_FEATURE_REPORT,
				 HID_REQ_GET_REPORT);
	अगर (ret < 0) अणु
		hid_err(hdev, "Asus failed to request functions: %d\n", ret);
		kमुक्त(पढ़ोbuf);
		वापस ret;
	पूर्ण

	*kbd_func = पढ़ोbuf[6];

	kमुक्त(पढ़ोbuf);
	वापस ret;
पूर्ण

अटल पूर्णांक rog_nkey_led_init(काष्ठा hid_device *hdev)
अणु
	u8 buf_init_start[] = अणु FEATURE_KBD_LED_REPORT_ID1, 0xB9 पूर्ण;
	u8 buf_init2[] = अणु FEATURE_KBD_LED_REPORT_ID1, 0x41, 0x53, 0x55, 0x53, 0x20,
				0x54, 0x65, 0x63, 0x68, 0x2e, 0x49, 0x6e, 0x63, 0x2e, 0x00 पूर्ण;
	u8 buf_init3[] = अणु FEATURE_KBD_LED_REPORT_ID1,
						0x05, 0x20, 0x31, 0x00, 0x08 पूर्ण;
	पूर्णांक ret;

	hid_info(hdev, "Asus initialise N-KEY Device");
	/* The first message is an init start */
	ret = asus_kbd_set_report(hdev, buf_init_start, माप(buf_init_start));
	अगर (ret < 0) अणु
		hid_warn(hdev, "Asus failed to send init start command: %d\n", ret);
		वापस ret;
	पूर्ण
	/* Followed by a string */
	ret = asus_kbd_set_report(hdev, buf_init2, माप(buf_init2));
	अगर (ret < 0) अणु
		hid_warn(hdev, "Asus failed to send init command 1.0: %d\n", ret);
		वापस ret;
	पूर्ण
	/* Followed by a string */
	ret = asus_kbd_set_report(hdev, buf_init3, माप(buf_init3));
	अगर (ret < 0) अणु
		hid_warn(hdev, "Asus failed to send init command 1.1: %d\n", ret);
		वापस ret;
	पूर्ण

	/* begin second report ID with same data */
	buf_init2[0] = FEATURE_KBD_LED_REPORT_ID2;
	buf_init3[0] = FEATURE_KBD_LED_REPORT_ID2;

	ret = asus_kbd_set_report(hdev, buf_init2, माप(buf_init2));
	अगर (ret < 0) अणु
		hid_warn(hdev, "Asus failed to send init command 2.0: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = asus_kbd_set_report(hdev, buf_init3, माप(buf_init3));
	अगर (ret < 0)
		hid_warn(hdev, "Asus failed to send init command 2.1: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम asus_kbd_backlight_set(काष्ठा led_classdev *led_cdev,
				   क्रमागत led_brightness brightness)
अणु
	काष्ठा asus_kbd_leds *led = container_of(led_cdev, काष्ठा asus_kbd_leds,
						 cdev);
	अगर (led->brightness == brightness)
		वापस;

	led->brightness = brightness;
	schedule_work(&led->work);
पूर्ण

अटल क्रमागत led_brightness asus_kbd_backlight_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा asus_kbd_leds *led = container_of(led_cdev, काष्ठा asus_kbd_leds,
						 cdev);

	वापस led->brightness;
पूर्ण

अटल व्योम asus_kbd_backlight_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asus_kbd_leds *led = container_of(work, काष्ठा asus_kbd_leds, work);
	u8 buf[] = अणु FEATURE_KBD_REPORT_ID, 0xba, 0xc5, 0xc4, 0x00 पूर्ण;
	पूर्णांक ret;

	अगर (led->हटाओd)
		वापस;

	buf[4] = led->brightness;

	ret = asus_kbd_set_report(led->hdev, buf, माप(buf));
	अगर (ret < 0)
		hid_err(led->hdev, "Asus failed to set keyboard backlight: %d\n", ret);
पूर्ण

/* WMI-based keyboard backlight LED control (via asus-wmi driver) takes
 * precedence. We only activate HID-based backlight control when the
 * WMI control is not available.
 */
अटल bool asus_kbd_wmi_led_control_present(काष्ठा hid_device *hdev)
अणु
	u32 value;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_ASUS_WMI))
		वापस false;

	ret = asus_wmi_evaluate_method(ASUS_WMI_METHODID_DSTS,
				       ASUS_WMI_DEVID_KBD_BACKLIGHT, 0, &value);
	hid_dbg(hdev, "WMI backlight check: rc %d value %x", ret, value);
	अगर (ret)
		वापस false;

	वापस !!(value & ASUS_WMI_DSTS_PRESENCE_BIT);
पूर्ण

अटल पूर्णांक asus_kbd_रेजिस्टर_leds(काष्ठा hid_device *hdev)
अणु
	काष्ठा asus_drvdata *drvdata = hid_get_drvdata(hdev);
	अचिन्हित अक्षर kbd_func;
	पूर्णांक ret;

	अगर (drvdata->quirks & QUIRK_ROG_NKEY_KEYBOARD) अणु
		ret = rog_nkey_led_init(hdev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		/* Initialize keyboard */
		ret = asus_kbd_init(hdev);
		अगर (ret < 0)
			वापस ret;

		/* Get keyboard functions */
		ret = asus_kbd_get_functions(hdev, &kbd_func);
		अगर (ret < 0)
			वापस ret;

		/* Check क्रम backlight support */
		अगर (!(kbd_func & SUPPORT_KBD_BACKLIGHT))
			वापस -ENODEV;
	पूर्ण

	drvdata->kbd_backlight = devm_kzalloc(&hdev->dev,
					      माप(काष्ठा asus_kbd_leds),
					      GFP_KERNEL);
	अगर (!drvdata->kbd_backlight)
		वापस -ENOMEM;

	drvdata->kbd_backlight->हटाओd = false;
	drvdata->kbd_backlight->brightness = 0;
	drvdata->kbd_backlight->hdev = hdev;
	drvdata->kbd_backlight->cdev.name = "asus::kbd_backlight";
	drvdata->kbd_backlight->cdev.max_brightness = 3;
	drvdata->kbd_backlight->cdev.brightness_set = asus_kbd_backlight_set;
	drvdata->kbd_backlight->cdev.brightness_get = asus_kbd_backlight_get;
	INIT_WORK(&drvdata->kbd_backlight->work, asus_kbd_backlight_work);

	ret = devm_led_classdev_रेजिस्टर(&hdev->dev, &drvdata->kbd_backlight->cdev);
	अगर (ret < 0) अणु
		/* No need to have this still around */
		devm_kमुक्त(&hdev->dev, drvdata->kbd_backlight);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * [0]       REPORT_ID (same value defined in report descriptor)
 * [1]	     rest battery level. range [0..255]
 * [2]..[7]  Bluetooth hardware address (MAC address)
 * [8]       अक्षरging status
 *            = 0 : AC offline / disअक्षरging
 *            = 1 : AC online  / अक्षरging
 *            = 2 : AC online  / fully अक्षरged
 */
अटल पूर्णांक asus_parse_battery(काष्ठा asus_drvdata *drvdata, u8 *data, पूर्णांक size)
अणु
	u8 sts;
	u8 lvl;
	पूर्णांक val;

	lvl = data[1];
	sts = data[8];

	drvdata->battery_capacity = ((पूर्णांक)lvl * 100) / (पूर्णांक)BATTERY_LEVEL_MAX;

	चयन (sts) अणु
	हाल BATTERY_STAT_CHARGING:
		val = POWER_SUPPLY_STATUS_CHARGING;
		अवरोध;
	हाल BATTERY_STAT_FULL:
		val = POWER_SUPPLY_STATUS_FULL;
		अवरोध;
	हाल BATTERY_STAT_DISCONNECT:
	शेष:
		val = POWER_SUPPLY_STATUS_DISCHARGING;
		अवरोध;
	पूर्ण
	drvdata->battery_stat = val;

	वापस 0;
पूर्ण

अटल पूर्णांक asus_report_battery(काष्ठा asus_drvdata *drvdata, u8 *data, पूर्णांक size)
अणु
	/* notअगरy only the स्वतःnomous event by device */
	अगर ((drvdata->battery_in_query == false) &&
			 (size == BATTERY_REPORT_SIZE))
		घातer_supply_changed(drvdata->battery);

	वापस 0;
पूर्ण

अटल पूर्णांक asus_battery_query(काष्ठा asus_drvdata *drvdata)
अणु
	u8 *buf;
	पूर्णांक ret = 0;

	buf = kदो_स्मृति(BATTERY_REPORT_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	drvdata->battery_in_query = true;
	ret = hid_hw_raw_request(drvdata->hdev, BATTERY_REPORT_ID,
				buf, BATTERY_REPORT_SIZE,
				HID_INPUT_REPORT, HID_REQ_GET_REPORT);
	drvdata->battery_in_query = false;
	अगर (ret == BATTERY_REPORT_SIZE)
		ret = asus_parse_battery(drvdata, buf, BATTERY_REPORT_SIZE);
	अन्यथा
		ret = -ENODATA;

	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property asus_battery_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_SCOPE,
	POWER_SUPPLY_PROP_MODEL_NAME,
पूर्ण;

#घोषणा	QUERY_MIN_INTERVAL	(60 * HZ)	/* 60[sec] */

अटल पूर्णांक asus_battery_get_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा asus_drvdata *drvdata = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
	हाल POWER_SUPPLY_PROP_CAPACITY:
		अगर (समय_beक्रमe(drvdata->battery_next_query, jअगरfies)) अणु
			drvdata->battery_next_query =
					 jअगरfies + QUERY_MIN_INTERVAL;
			ret = asus_battery_query(drvdata);
			अगर (ret)
				वापस ret;
		पूर्ण
		अगर (psp == POWER_SUPPLY_PROP_STATUS)
			val->पूर्णांकval = drvdata->battery_stat;
		अन्यथा
			val->पूर्णांकval = drvdata->battery_capacity;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = 1;
		अवरोध;
	हाल POWER_SUPPLY_PROP_SCOPE:
		val->पूर्णांकval = POWER_SUPPLY_SCOPE_DEVICE;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = drvdata->hdev->name;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक asus_battery_probe(काष्ठा hid_device *hdev)
अणु
	काष्ठा asus_drvdata *drvdata = hid_get_drvdata(hdev);
	काष्ठा घातer_supply_config pscfg = अणु .drv_data = drvdata पूर्ण;
	पूर्णांक ret = 0;

	drvdata->battery_capacity = 0;
	drvdata->battery_stat = POWER_SUPPLY_STATUS_UNKNOWN;
	drvdata->battery_in_query = false;

	drvdata->battery_desc.properties = asus_battery_props;
	drvdata->battery_desc.num_properties = ARRAY_SIZE(asus_battery_props);
	drvdata->battery_desc.get_property = asus_battery_get_property;
	drvdata->battery_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	drvdata->battery_desc.use_क्रम_apm = 0;
	drvdata->battery_desc.name = devm_kaप्र_लिखो(&hdev->dev, GFP_KERNEL,
					"asus-keyboard-%s-battery",
					म_माप(hdev->uniq) ?
					hdev->uniq : dev_name(&hdev->dev));
	अगर (!drvdata->battery_desc.name)
		वापस -ENOMEM;

	drvdata->battery_next_query = jअगरfies;

	drvdata->battery = devm_घातer_supply_रेजिस्टर(&hdev->dev,
				&(drvdata->battery_desc), &pscfg);
	अगर (IS_ERR(drvdata->battery)) अणु
		ret = PTR_ERR(drvdata->battery);
		drvdata->battery = शून्य;
		hid_err(hdev, "Unable to register battery device\n");
		वापस ret;
	पूर्ण

	घातer_supply_घातers(drvdata->battery, &hdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक asus_input_configured(काष्ठा hid_device *hdev, काष्ठा hid_input *hi)
अणु
	काष्ठा input_dev *input = hi->input;
	काष्ठा asus_drvdata *drvdata = hid_get_drvdata(hdev);

	/* T100CHI uses MULTI_INPUT, bind the touchpad to the mouse hid_input */
	अगर (drvdata->quirks & QUIRK_T100CHI &&
	    hi->report->id != T100CHI_MOUSE_REPORT_ID)
		वापस 0;

	/* Handle MULTI_INPUT on E1239T mouse/touchpad USB पूर्णांकerface */
	अगर (drvdata->tp && (drvdata->quirks & QUIRK_MEDION_E1239T)) अणु
		चयन (hi->report->id) अणु
		हाल E1239T_TP_TOGGLE_REPORT_ID:
			input_set_capability(input, EV_KEY, KEY_F21);
			input->name = "Asus Touchpad Keys";
			drvdata->tp_kbd_input = input;
			वापस 0;
		हाल INPUT_REPORT_ID:
			अवरोध; /* Touchpad report, handled below */
		शेष:
			वापस 0; /* Ignore other reports */
		पूर्ण
	पूर्ण

	अगर (drvdata->tp) अणु
		पूर्णांक ret;

		input_set_असल_params(input, ABS_MT_POSITION_X, 0,
				     drvdata->tp->max_x, 0, 0);
		input_set_असल_params(input, ABS_MT_POSITION_Y, 0,
				     drvdata->tp->max_y, 0, 0);
		input_असल_set_res(input, ABS_MT_POSITION_X, drvdata->tp->res_x);
		input_असल_set_res(input, ABS_MT_POSITION_Y, drvdata->tp->res_y);

		अगर (drvdata->tp->contact_size >= 5) अणु
			input_set_असल_params(input, ABS_TOOL_WIDTH, 0,
					     MAX_TOUCH_MAJOR, 0, 0);
			input_set_असल_params(input, ABS_MT_TOUCH_MAJOR, 0,
					     MAX_TOUCH_MAJOR, 0, 0);
			input_set_असल_params(input, ABS_MT_PRESSURE, 0,
					      MAX_PRESSURE, 0, 0);
		पूर्ण

		__set_bit(BTN_LEFT, input->keybit);
		__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);

		ret = input_mt_init_slots(input, drvdata->tp->max_contacts,
					  INPUT_MT_POINTER);

		अगर (ret) अणु
			hid_err(hdev, "Asus input mt init slots failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	drvdata->input = input;

	अगर (drvdata->enable_backlight &&
	    !asus_kbd_wmi_led_control_present(hdev) &&
	    asus_kbd_रेजिस्टर_leds(hdev))
		hid_warn(hdev, "Failed to initialize backlight.\n");

	वापस 0;
पूर्ण

#घोषणा asus_map_key_clear(c)	hid_map_usage_clear(hi, usage, bit, \
						    max, EV_KEY, (c))
अटल पूर्णांक asus_input_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hi, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit,
		पूर्णांक *max)
अणु
	काष्ठा asus_drvdata *drvdata = hid_get_drvdata(hdev);

	अगर (drvdata->quirks & QUIRK_SKIP_INPUT_MAPPING) अणु
		/* Don't map anything from the HID report.
		 * We करो it all manually in asus_input_configured
		 */
		वापस -1;
	पूर्ण

	/*
	 * Ignore a bunch of bogus collections in the T100CHI descriptor.
	 * This aव्योमs a bunch of non-functional hid_input devices getting
	 * created because of the T100CHI using HID_QUIRK_MULTI_INPUT.
	 */
	अगर ((drvdata->quirks & (QUIRK_T100CHI | QUIRK_T90CHI)) &&
	    (field->application == (HID_UP_GENDESK | 0x0080) ||
	     field->application == HID_GD_MOUSE ||
	     usage->hid == (HID_UP_GENDEVCTRLS | 0x0024) ||
	     usage->hid == (HID_UP_GENDEVCTRLS | 0x0025) ||
	     usage->hid == (HID_UP_GENDEVCTRLS | 0x0026)))
		वापस -1;

	/* ASUS-specअगरic keyboard hotkeys and led backlight */
	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_ASUSVENDOR) अणु
		चयन (usage->hid & HID_USAGE) अणु
		हाल 0x10: asus_map_key_clear(KEY_BRIGHTNESSDOWN);	अवरोध;
		हाल 0x20: asus_map_key_clear(KEY_BRIGHTNESSUP);		अवरोध;
		हाल 0x35: asus_map_key_clear(KEY_DISPLAY_OFF);		अवरोध;
		हाल 0x6c: asus_map_key_clear(KEY_SLEEP);		अवरोध;
		हाल 0x7c: asus_map_key_clear(KEY_MICMUTE);		अवरोध;
		हाल 0x82: asus_map_key_clear(KEY_CAMERA);		अवरोध;
		हाल 0x88: asus_map_key_clear(KEY_RFKILL);			अवरोध;
		हाल 0xb5: asus_map_key_clear(KEY_CALC);			अवरोध;
		हाल 0xc4: asus_map_key_clear(KEY_KBDILLUMUP);		अवरोध;
		हाल 0xc5: asus_map_key_clear(KEY_KBDILLUMDOWN);		अवरोध;

		/* ASUS touchpad toggle */
		हाल 0x6b: asus_map_key_clear(KEY_F21);			अवरोध;

		/* ROG key */
		हाल 0x38: asus_map_key_clear(KEY_PROG1);		अवरोध;

		/* Fn+C ASUS Splendid */
		हाल 0xba: asus_map_key_clear(KEY_PROG2);		अवरोध;

		/* Fn+Space Power4Gear Hybrid */
		हाल 0x5c: asus_map_key_clear(KEY_PROG3);		अवरोध;

		/* Fn+F5 "fan" symbol on FX503VD */
		हाल 0x99: asus_map_key_clear(KEY_PROG4);		अवरोध;

		/* Fn+F5 "fan" symbol on N-Key keyboard */
		हाल 0xae: asus_map_key_clear(KEY_PROG4);		अवरोध;

		/* Fn+Ret "Calc" symbol on N-Key keyboard */
		हाल 0x92: asus_map_key_clear(KEY_CALC);		अवरोध;

		/* Fn+Left Aura mode previous on N-Key keyboard */
		हाल 0xb2: asus_map_key_clear(KEY_PROG2);		अवरोध;

		/* Fn+Right Aura mode next on N-Key keyboard */
		हाल 0xb3: asus_map_key_clear(KEY_PROG3);		अवरोध;

		शेष:
			/* ASUS lazily declares 256 usages, ignore the rest,
			 * as some make the keyboard appear as a poपूर्णांकer device. */
			वापस -1;
		पूर्ण

		/*
		 * Check and enable backlight only on devices with UsagePage ==
		 * 0xff31 to aव्योम initializing the keyboard firmware multiple
		 * बार on devices with multiple HID descriptors but same
		 * PID/VID.
		 */
		अगर (drvdata->quirks & QUIRK_USE_KBD_BACKLIGHT)
			drvdata->enable_backlight = true;

		set_bit(EV_REP, hi->input->evbit);
		वापस 1;
	पूर्ण

	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_MSVENDOR) अणु
		चयन (usage->hid & HID_USAGE) अणु
		हाल 0xff01: asus_map_key_clear(BTN_1);	अवरोध;
		हाल 0xff02: asus_map_key_clear(BTN_2);	अवरोध;
		हाल 0xff03: asus_map_key_clear(BTN_3);	अवरोध;
		हाल 0xff04: asus_map_key_clear(BTN_4);	अवरोध;
		हाल 0xff05: asus_map_key_clear(BTN_5);	अवरोध;
		हाल 0xff06: asus_map_key_clear(BTN_6);	अवरोध;
		हाल 0xff07: asus_map_key_clear(BTN_7);	अवरोध;
		हाल 0xff08: asus_map_key_clear(BTN_8);	अवरोध;
		हाल 0xff09: asus_map_key_clear(BTN_9);	अवरोध;
		हाल 0xff0a: asus_map_key_clear(BTN_A);	अवरोध;
		हाल 0xff0b: asus_map_key_clear(BTN_B);	अवरोध;
		हाल 0x00f1: asus_map_key_clear(KEY_WLAN);	अवरोध;
		हाल 0x00f2: asus_map_key_clear(KEY_BRIGHTNESSDOWN);	अवरोध;
		हाल 0x00f3: asus_map_key_clear(KEY_BRIGHTNESSUP);	अवरोध;
		हाल 0x00f4: asus_map_key_clear(KEY_DISPLAY_OFF);	अवरोध;
		हाल 0x00f7: asus_map_key_clear(KEY_CAMERA);	अवरोध;
		हाल 0x00f8: asus_map_key_clear(KEY_PROG1);	अवरोध;
		शेष:
			वापस 0;
		पूर्ण

		set_bit(EV_REP, hi->input->evbit);
		वापस 1;
	पूर्ण

	अगर (drvdata->quirks & QUIRK_NO_CONSUMER_USAGES &&
		(usage->hid & HID_USAGE_PAGE) == HID_UP_CONSUMER) अणु
		चयन (usage->hid & HID_USAGE) अणु
		हाल 0xe2: /* Mute */
		हाल 0xe9: /* Volume up */
		हाल 0xea: /* Volume करोwn */
			वापस 0;
		शेष:
			/* Ignore dummy Consumer usages which make the
			 * keyboard incorrectly appear as a poपूर्णांकer device.
			 */
			वापस -1;
		पूर्ण
	पूर्ण

	/*
	 * The mute button is broken and only sends press events, we
	 * deal with this in our raw_event handler, so करो not map it.
	 */
	अगर ((drvdata->quirks & QUIRK_MEDION_E1239T) &&
	    usage->hid == (HID_UP_CONSUMER | 0xe2)) अणु
		input_set_capability(hi->input, EV_KEY, KEY_MUTE);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक asus_start_multitouch(काष्ठा hid_device *hdev)
अणु
	पूर्णांक ret;
	अटल स्थिर अचिन्हित अक्षर buf[] = अणु
		FEATURE_REPORT_ID, 0x00, 0x03, 0x01, 0x00
	पूर्ण;
	अचिन्हित अक्षर *dmabuf = kmemdup(buf, माप(buf), GFP_KERNEL);

	अगर (!dmabuf) अणु
		ret = -ENOMEM;
		hid_err(hdev, "Asus failed to alloc dma buf: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hid_hw_raw_request(hdev, dmabuf[0], dmabuf, माप(buf),
					HID_FEATURE_REPORT, HID_REQ_SET_REPORT);

	kमुक्त(dmabuf);

	अगर (ret != माप(buf)) अणु
		hid_err(hdev, "Asus failed to start multitouch: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused asus_reset_resume(काष्ठा hid_device *hdev)
अणु
	काष्ठा asus_drvdata *drvdata = hid_get_drvdata(hdev);

	अगर (drvdata->tp)
		वापस asus_start_multitouch(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक asus_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा asus_drvdata *drvdata;

	drvdata = devm_kzalloc(&hdev->dev, माप(*drvdata), GFP_KERNEL);
	अगर (drvdata == शून्य) अणु
		hid_err(hdev, "Can't alloc Asus descriptor\n");
		वापस -ENOMEM;
	पूर्ण

	hid_set_drvdata(hdev, drvdata);

	drvdata->quirks = id->driver_data;

	/*
	 * T90CHI's keyboard dock returns same ID values as T100CHI's करोck.
	 * Thus, identअगरy T90CHI करोck with product name string.
	 */
	अगर (म_माला(hdev->name, "T90CHI")) अणु
		drvdata->quirks &= ~QUIRK_T100CHI;
		drvdata->quirks |= QUIRK_T90CHI;
	पूर्ण

	अगर (drvdata->quirks & QUIRK_IS_MULTITOUCH)
		drvdata->tp = &asus_i2c_tp;

	अगर ((drvdata->quirks & QUIRK_T100_KEYBOARD) &&
	    hid_is_using_ll_driver(hdev, &usb_hid_driver)) अणु
		काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);

		अगर (पूर्णांकf->altsetting->desc.bInterfaceNumber == T100_TPAD_INTF) अणु
			drvdata->quirks = QUIRK_SKIP_INPUT_MAPPING;
			/*
			 * The T100HA uses the same USB-ids as the T100TAF and
			 * the T200TA uses the same USB-ids as the T100TA, जबतक
			 * both have dअगरferent max x/y values as the T100TA[F].
			 */
			अगर (dmi_match(DMI_PRODUCT_NAME, "T100HAN"))
				drvdata->tp = &asus_t100ha_tp;
			अन्यथा अगर (dmi_match(DMI_PRODUCT_NAME, "T200TA"))
				drvdata->tp = &asus_t200ta_tp;
			अन्यथा
				drvdata->tp = &asus_t100ta_tp;
		पूर्ण
	पूर्ण

	अगर (drvdata->quirks & QUIRK_T100CHI) अणु
		/*
		 * All functionality is on a single HID पूर्णांकerface and क्रम
		 * userspace the touchpad must be a separate input_dev.
		 */
		hdev->quirks |= HID_QUIRK_MULTI_INPUT;
		drvdata->tp = &asus_t100chi_tp;
	पूर्ण

	अगर ((drvdata->quirks & QUIRK_MEDION_E1239T) &&
	    hid_is_using_ll_driver(hdev, &usb_hid_driver)) अणु
		काष्ठा usb_host_पूर्णांकerface *alt =
			to_usb_पूर्णांकerface(hdev->dev.parent)->altsetting;

		अगर (alt->desc.bInterfaceNumber == MEDION_E1239T_TPAD_INTF) अणु
			/* For separate input-devs क्रम tp and tp toggle key */
			hdev->quirks |= HID_QUIRK_MULTI_INPUT;
			drvdata->quirks |= QUIRK_SKIP_INPUT_MAPPING;
			drvdata->tp = &medion_e1239t_tp;
		पूर्ण
	पूर्ण

	अगर (drvdata->quirks & QUIRK_NO_INIT_REPORTS)
		hdev->quirks |= HID_QUIRK_NO_INIT_REPORTS;

	drvdata->hdev = hdev;

	अगर (drvdata->quirks & (QUIRK_T100CHI | QUIRK_T90CHI)) अणु
		ret = asus_battery_probe(hdev);
		अगर (ret) अणु
			hid_err(hdev,
			    "Asus hid battery_probe failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "Asus hid parse failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hdev, "Asus hw start failed: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!drvdata->input) अणु
		hid_err(hdev, "Asus input not registered\n");
		ret = -ENOMEM;
		जाओ err_stop_hw;
	पूर्ण

	अगर (drvdata->tp) अणु
		drvdata->input->name = "Asus TouchPad";
	पूर्ण अन्यथा अणु
		drvdata->input->name = "Asus Keyboard";
	पूर्ण

	अगर (drvdata->tp) अणु
		ret = asus_start_multitouch(hdev);
		अगर (ret)
			जाओ err_stop_hw;
	पूर्ण

	वापस 0;
err_stop_hw:
	hid_hw_stop(hdev);
	वापस ret;
पूर्ण

अटल व्योम asus_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा asus_drvdata *drvdata = hid_get_drvdata(hdev);

	अगर (drvdata->kbd_backlight) अणु
		drvdata->kbd_backlight->हटाओd = true;
		cancel_work_sync(&drvdata->kbd_backlight->work);
	पूर्ण

	hid_hw_stop(hdev);
पूर्ण

अटल स्थिर __u8 asus_g752_fixed_rdesc[] = अणु
        0x19, 0x00,			/*   Usage Minimum (0x00)       */
        0x2A, 0xFF, 0x00,		/*   Usage Maximum (0xFF)       */
पूर्ण;

अटल __u8 *asus_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	काष्ठा asus_drvdata *drvdata = hid_get_drvdata(hdev);

	अगर (drvdata->quirks & QUIRK_FIX_NOTEBOOK_REPORT &&
			*rsize >= 56 && rdesc[54] == 0x25 && rdesc[55] == 0x65) अणु
		hid_info(hdev, "Fixing up Asus notebook report descriptor\n");
		rdesc[55] = 0xdd;
	पूर्ण
	/* For the T100TA/T200TA keyboard करोck */
	अगर (drvdata->quirks & QUIRK_T100_KEYBOARD &&
		 (*rsize == 76 || *rsize == 101) &&
		 rdesc[73] == 0x81 && rdesc[74] == 0x01) अणु
		hid_info(hdev, "Fixing up Asus T100 keyb report descriptor\n");
		rdesc[74] &= ~HID_MAIN_ITEM_CONSTANT;
	पूर्ण
	/* For the T100CHI/T90CHI keyboard करोck */
	अगर (drvdata->quirks & (QUIRK_T100CHI | QUIRK_T90CHI)) अणु
		पूर्णांक rsize_orig;
		पूर्णांक offs;

		अगर (drvdata->quirks & QUIRK_T100CHI) अणु
			rsize_orig = 403;
			offs = 388;
		पूर्ण अन्यथा अणु
			rsize_orig = 306;
			offs = 291;
		पूर्ण

		/*
		 * Change Usage (76h) to Usage Minimum (00h), Usage Maximum
		 * (FFh) and clear the flags in the Input() byte.
		 * Note the descriptor has a bogus 0 byte at the end so we
		 * only need 1 extra byte.
		 */
		अगर (*rsize == rsize_orig &&
			rdesc[offs] == 0x09 && rdesc[offs + 1] == 0x76) अणु
			*rsize = rsize_orig + 1;
			rdesc = kmemdup(rdesc, *rsize, GFP_KERNEL);
			अगर (!rdesc)
				वापस शून्य;

			hid_info(hdev, "Fixing up %s keyb report descriptor\n",
				drvdata->quirks & QUIRK_T100CHI ?
				"T100CHI" : "T90CHI");
			स_हटाओ(rdesc + offs + 4, rdesc + offs + 2, 12);
			rdesc[offs] = 0x19;
			rdesc[offs + 1] = 0x00;
			rdesc[offs + 2] = 0x29;
			rdesc[offs + 3] = 0xff;
			rdesc[offs + 14] = 0x00;
		पूर्ण
	पूर्ण

	अगर (drvdata->quirks & QUIRK_G752_KEYBOARD &&
		 *rsize == 75 && rdesc[61] == 0x15 && rdesc[62] == 0x00) अणु
		/* report is missing usage mninum and maximum */
		__u8 *new_rdesc;
		माप_प्रकार new_size = *rsize + माप(asus_g752_fixed_rdesc);

		new_rdesc = devm_kzalloc(&hdev->dev, new_size, GFP_KERNEL);
		अगर (new_rdesc == शून्य)
			वापस rdesc;

		hid_info(hdev, "Fixing up Asus G752 keyb report descriptor\n");
		/* copy the valid part */
		स_नकल(new_rdesc, rdesc, 61);
		/* insert missing part */
		स_नकल(new_rdesc + 61, asus_g752_fixed_rdesc, माप(asus_g752_fixed_rdesc));
		/* copy reमुख्यing data */
		स_नकल(new_rdesc + 61 + माप(asus_g752_fixed_rdesc), rdesc + 61, *rsize - 61);

		*rsize = new_size;
		rdesc = new_rdesc;
	पूर्ण

	वापस rdesc;
पूर्ण

अटल स्थिर काष्ठा hid_device_id asus_devices[] = अणु
	अणु HID_I2C_DEVICE(USB_VENDOR_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_I2C_KEYBOARD), I2C_KEYBOARD_QUIRKSपूर्ण,
	अणु HID_I2C_DEVICE(USB_VENDOR_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_I2C_TOUCHPAD), I2C_TOUCHPAD_QUIRKS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_ROG_KEYBOARD1), QUIRK_USE_KBD_BACKLIGHT पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_ROG_KEYBOARD2), QUIRK_USE_KBD_BACKLIGHT पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_ROG_KEYBOARD3), QUIRK_G752_KEYBOARD पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_FX503VD_KEYBOARD),
	  QUIRK_USE_KBD_BACKLIGHT पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ASUSTEK,
	    USB_DEVICE_ID_ASUSTEK_ROG_NKEY_KEYBOARD),
	  QUIRK_USE_KBD_BACKLIGHT | QUIRK_ROG_NKEY_KEYBOARD पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ASUSTEK,
	    USB_DEVICE_ID_ASUSTEK_ROG_NKEY_KEYBOARD2),
	  QUIRK_USE_KBD_BACKLIGHT | QUIRK_ROG_NKEY_KEYBOARD पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_T100TA_KEYBOARD),
	  QUIRK_T100_KEYBOARD | QUIRK_NO_CONSUMER_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_T100TAF_KEYBOARD),
	  QUIRK_T100_KEYBOARD | QUIRK_NO_CONSUMER_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CHICONY, USB_DEVICE_ID_ASUS_AK1D) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_TURBOX, USB_DEVICE_ID_ASUS_MD_5110) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_JESS, USB_DEVICE_ID_ASUS_MD_5112) पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_T100CHI_KEYBOARD), QUIRK_T100CHI पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ITE, USB_DEVICE_ID_ITE_MEDION_E1239T),
		QUIRK_MEDION_E1239T पूर्ण,
	/*
	 * Note bind to the HID_GROUP_GENERIC group, so that we only bind to the keyboard
	 * part, जबतक letting hid-multitouch.c handle the touchpad.
	 */
	अणु HID_DEVICE(BUS_USB, HID_GROUP_GENERIC,
		USB_VENDOR_ID_ASUSTEK, USB_DEVICE_ID_ASUSTEK_T101HA_KEYBOARD) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, asus_devices);

अटल काष्ठा hid_driver asus_driver = अणु
	.name			= "asus",
	.id_table		= asus_devices,
	.report_fixup		= asus_report_fixup,
	.probe                  = asus_probe,
	.हटाओ			= asus_हटाओ,
	.input_mapping          = asus_input_mapping,
	.input_configured       = asus_input_configured,
#अगर_घोषित CONFIG_PM
	.reset_resume           = asus_reset_resume,
#पूर्ण_अगर
	.event			= asus_event,
	.raw_event		= asus_raw_event
पूर्ण;
module_hid_driver(asus_driver);

MODULE_LICENSE("GPL");
