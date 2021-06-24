<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/*
 *  LED & क्रमce feedback support क्रम BigBen Interactive
 *
 *  0x146b:0x0902 "Bigben Interactive Bigben Game Pad"
 *  "Kid-friendly Wired Controller" PS3OFMINIPAD SONY
 *  sold क्रम use with the PS3
 *
 *  Copyright (c) 2018 Hanno Zulla <kontakt@hanno.de>
 */

#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/leds.h>
#समावेश <linux/hid.h>

#समावेश "hid-ids.h"


/*
 * The original descriptor क्रम 0x146b:0x0902
 *
 *   0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
 *   0x09, 0x05,        // Usage (Game Pad)
 *   0xA1, 0x01,        // Collection (Application)
 *   0x15, 0x00,        //   Logical Minimum (0)
 *   0x25, 0x01,        //   Logical Maximum (1)
 *   0x35, 0x00,        //   Physical Minimum (0)
 *   0x45, 0x01,        //   Physical Maximum (1)
 *   0x75, 0x01,        //   Report Size (1)
 *   0x95, 0x0D,        //   Report Count (13)
 *   0x05, 0x09,        //   Usage Page (Button)
 *   0x19, 0x01,        //   Usage Minimum (0x01)
 *   0x29, 0x0D,        //   Usage Maximum (0x0D)
 *   0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
 *   0x95, 0x03,        //   Report Count (3)
 *   0x81, 0x01,        //   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
 *   0x05, 0x01,        //   Usage Page (Generic Desktop Ctrls)
 *   0x25, 0x07,        //   Logical Maximum (7)
 *   0x46, 0x3B, 0x01,  //   Physical Maximum (315)
 *   0x75, 0x04,        //   Report Size (4)
 *   0x95, 0x01,        //   Report Count (1)
 *   0x65, 0x14,        //   Unit (System: English Rotation, Length: Cenसमयter)
 *   0x09, 0x39,        //   Usage (Hat चयन)
 *   0x81, 0x42,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State)
 *   0x65, 0x00,        //   Unit (None)
 *   0x95, 0x01,        //   Report Count (1)
 *   0x81, 0x01,        //   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
 *   0x26, 0xFF, 0x00,  //   Logical Maximum (255)
 *   0x46, 0xFF, 0x00,  //   Physical Maximum (255)
 *   0x09, 0x30,        //   Usage (X)
 *   0x09, 0x31,        //   Usage (Y)
 *   0x09, 0x32,        //   Usage (Z)
 *   0x09, 0x35,        //   Usage (Rz)
 *   0x75, 0x08,        //   Report Size (8)
 *   0x95, 0x04,        //   Report Count (4)
 *   0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
 *   0x06, 0x00, 0xFF,  //   Usage Page (Venकरोr Defined 0xFF00)
 *   0x09, 0x20,        //   Usage (0x20)
 *   0x09, 0x21,        //   Usage (0x21)
 *   0x09, 0x22,        //   Usage (0x22)
 *   0x09, 0x23,        //   Usage (0x23)
 *   0x09, 0x24,        //   Usage (0x24)
 *   0x09, 0x25,        //   Usage (0x25)
 *   0x09, 0x26,        //   Usage (0x26)
 *   0x09, 0x27,        //   Usage (0x27)
 *   0x09, 0x28,        //   Usage (0x28)
 *   0x09, 0x29,        //   Usage (0x29)
 *   0x09, 0x2A,        //   Usage (0x2A)
 *   0x09, 0x2B,        //   Usage (0x2B)
 *   0x95, 0x0C,        //   Report Count (12)
 *   0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
 *   0x0A, 0x21, 0x26,  //   Usage (0x2621)
 *   0x95, 0x08,        //   Report Count (8)
 *   0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-अस्थिर)
 *   0x0A, 0x21, 0x26,  //   Usage (0x2621)
 *   0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-अस्थिर)
 *   0x26, 0xFF, 0x03,  //   Logical Maximum (1023)
 *   0x46, 0xFF, 0x03,  //   Physical Maximum (1023)
 *   0x09, 0x2C,        //   Usage (0x2C)
 *   0x09, 0x2D,        //   Usage (0x2D)
 *   0x09, 0x2E,        //   Usage (0x2E)
 *   0x09, 0x2F,        //   Usage (0x2F)
 *   0x75, 0x10,        //   Report Size (16)
 *   0x95, 0x04,        //   Report Count (4)
 *   0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
 *   0xC0,              // End Collection
 */

#घोषणा PID0902_RDESC_ORIG_SIZE 137

/*
 * The fixed descriptor क्रम 0x146b:0x0902
 *
 * - map buttons according to gamepad.rst
 * - assign right stick from Z/Rz to Rx/Ry
 * - map previously unused analog trigger data to Z/RZ
 * - simplअगरy feature and output descriptor
 */
अटल __u8 pid0902_rdesc_fixed[] = अणु
	0x05, 0x01,        /* Usage Page (Generic Desktop Ctrls) */
	0x09, 0x05,        /* Usage (Game Pad) */
	0xA1, 0x01,        /* Collection (Application) */
	0x15, 0x00,        /*   Logical Minimum (0) */
	0x25, 0x01,        /*   Logical Maximum (1) */
	0x35, 0x00,        /*   Physical Minimum (0) */
	0x45, 0x01,        /*   Physical Maximum (1) */
	0x75, 0x01,        /*   Report Size (1) */
	0x95, 0x0D,        /*   Report Count (13) */
	0x05, 0x09,        /*   Usage Page (Button) */
	0x09, 0x05,        /*   Usage (BTN_WEST) */
	0x09, 0x01,        /*   Usage (BTN_SOUTH) */
	0x09, 0x02,        /*   Usage (BTN_EAST) */
	0x09, 0x04,        /*   Usage (BTN_NORTH) */
	0x09, 0x07,        /*   Usage (BTN_TL) */
	0x09, 0x08,        /*   Usage (BTN_TR) */
	0x09, 0x09,        /*   Usage (BTN_TL2) */
	0x09, 0x0A,        /*   Usage (BTN_TR2) */
	0x09, 0x0B,        /*   Usage (BTN_SELECT) */
	0x09, 0x0C,        /*   Usage (BTN_START) */
	0x09, 0x0E,        /*   Usage (BTN_THUMBL) */
	0x09, 0x0F,        /*   Usage (BTN_THUMBR) */
	0x09, 0x0D,        /*   Usage (BTN_MODE) */
	0x81, 0x02,        /*   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position) */
	0x75, 0x01,        /*   Report Size (1) */
	0x95, 0x03,        /*   Report Count (3) */
	0x81, 0x01,        /*   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position) */
	0x05, 0x01,        /*   Usage Page (Generic Desktop Ctrls) */
	0x25, 0x07,        /*   Logical Maximum (7) */
	0x46, 0x3B, 0x01,  /*   Physical Maximum (315) */
	0x75, 0x04,        /*   Report Size (4) */
	0x95, 0x01,        /*   Report Count (1) */
	0x65, 0x14,        /*   Unit (System: English Rotation, Length: Cenसमयter) */
	0x09, 0x39,        /*   Usage (Hat चयन) */
	0x81, 0x42,        /*   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State) */
	0x65, 0x00,        /*   Unit (None) */
	0x95, 0x01,        /*   Report Count (1) */
	0x81, 0x01,        /*   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position) */
	0x26, 0xFF, 0x00,  /*   Logical Maximum (255) */
	0x46, 0xFF, 0x00,  /*   Physical Maximum (255) */
	0x09, 0x30,        /*   Usage (X) */
	0x09, 0x31,        /*   Usage (Y) */
	0x09, 0x33,        /*   Usage (Rx) */
	0x09, 0x34,        /*   Usage (Ry) */
	0x75, 0x08,        /*   Report Size (8) */
	0x95, 0x04,        /*   Report Count (4) */
	0x81, 0x02,        /*   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position) */
	0x95, 0x0A,        /*   Report Count (10) */
	0x81, 0x01,        /*   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position) */
	0x05, 0x01,        /*   Usage Page (Generic Desktop Ctrls) */
	0x26, 0xFF, 0x00,  /*   Logical Maximum (255) */
	0x46, 0xFF, 0x00,  /*   Physical Maximum (255) */
	0x09, 0x32,        /*   Usage (Z) */
	0x09, 0x35,        /*   Usage (Rz) */
	0x95, 0x02,        /*   Report Count (2) */
	0x81, 0x02,        /*   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position) */
	0x95, 0x08,        /*   Report Count (8) */
	0x81, 0x01,        /*   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position) */
	0x06, 0x00, 0xFF,  /*   Usage Page (Venकरोr Defined 0xFF00) */
	0xB1, 0x02,        /*   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-अस्थिर) */
	0x0A, 0x21, 0x26,  /*   Usage (0x2621) */
	0x95, 0x08,        /*   Report Count (8) */
	0x91, 0x02,        /*   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-अस्थिर) */
	0x0A, 0x21, 0x26,  /*   Usage (0x2621) */
	0x95, 0x08,        /*   Report Count (8) */
	0x81, 0x02,        /*   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position) */
	0xC0,              /* End Collection */
पूर्ण;

#घोषणा NUM_LEDS 4

काष्ठा bigben_device अणु
	काष्ठा hid_device *hid;
	काष्ठा hid_report *report;
	bool हटाओd;
	u8 led_state;         /* LED1 = 1 .. LED4 = 8 */
	u8 right_motor_on;    /* right motor off/on 0/1 */
	u8 left_motor_क्रमce;  /* left motor क्रमce 0-255 */
	काष्ठा led_classdev *leds[NUM_LEDS];
	bool work_led;
	bool work_ff;
	काष्ठा work_काष्ठा worker;
पूर्ण;


अटल व्योम bigben_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bigben_device *bigben = container_of(work,
		काष्ठा bigben_device, worker);
	काष्ठा hid_field *report_field = bigben->report->field[0];

	अगर (bigben->हटाओd)
		वापस;

	अगर (bigben->work_led) अणु
		bigben->work_led = false;
		report_field->value[0] = 0x01; /* 1 = led message */
		report_field->value[1] = 0x08; /* reserved value, always 8 */
		report_field->value[2] = bigben->led_state;
		report_field->value[3] = 0x00; /* padding */
		report_field->value[4] = 0x00; /* padding */
		report_field->value[5] = 0x00; /* padding */
		report_field->value[6] = 0x00; /* padding */
		report_field->value[7] = 0x00; /* padding */
		hid_hw_request(bigben->hid, bigben->report, HID_REQ_SET_REPORT);
	पूर्ण

	अगर (bigben->work_ff) अणु
		bigben->work_ff = false;
		report_field->value[0] = 0x02; /* 2 = rumble effect message */
		report_field->value[1] = 0x08; /* reserved value, always 8 */
		report_field->value[2] = bigben->right_motor_on;
		report_field->value[3] = bigben->left_motor_क्रमce;
		report_field->value[4] = 0xff; /* duration 0-254 (255 = nonstop) */
		report_field->value[5] = 0x00; /* padding */
		report_field->value[6] = 0x00; /* padding */
		report_field->value[7] = 0x00; /* padding */
		hid_hw_request(bigben->hid, bigben->report, HID_REQ_SET_REPORT);
	पूर्ण
पूर्ण

अटल पूर्णांक hid_bigben_play_effect(काष्ठा input_dev *dev, व्योम *data,
			 काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा bigben_device *bigben = hid_get_drvdata(hid);
	u8 right_motor_on;
	u8 left_motor_क्रमce;

	अगर (!bigben) अणु
		hid_err(hid, "no device data\n");
		वापस 0;
	पूर्ण

	अगर (effect->type != FF_RUMBLE)
		वापस 0;

	right_motor_on   = effect->u.rumble.weak_magnitude ? 1 : 0;
	left_motor_क्रमce = effect->u.rumble.strong_magnitude / 256;

	अगर (right_motor_on != bigben->right_motor_on ||
			left_motor_क्रमce != bigben->left_motor_क्रमce) अणु
		bigben->right_motor_on   = right_motor_on;
		bigben->left_motor_क्रमce = left_motor_क्रमce;
		bigben->work_ff = true;
		schedule_work(&bigben->worker);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bigben_set_led(काष्ठा led_classdev *led,
	क्रमागत led_brightness value)
अणु
	काष्ठा device *dev = led->dev->parent;
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा bigben_device *bigben = hid_get_drvdata(hid);
	पूर्णांक n;
	bool work;

	अगर (!bigben) अणु
		hid_err(hid, "no device data\n");
		वापस;
	पूर्ण

	क्रम (n = 0; n < NUM_LEDS; n++) अणु
		अगर (led == bigben->leds[n]) अणु
			अगर (value == LED_OFF) अणु
				work = (bigben->led_state & BIT(n));
				bigben->led_state &= ~BIT(n);
			पूर्ण अन्यथा अणु
				work = !(bigben->led_state & BIT(n));
				bigben->led_state |= BIT(n);
			पूर्ण

			अगर (work) अणु
				bigben->work_led = true;
				schedule_work(&bigben->worker);
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल क्रमागत led_brightness bigben_get_led(काष्ठा led_classdev *led)
अणु
	काष्ठा device *dev = led->dev->parent;
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा bigben_device *bigben = hid_get_drvdata(hid);
	पूर्णांक n;

	अगर (!bigben) अणु
		hid_err(hid, "no device data\n");
		वापस LED_OFF;
	पूर्ण

	क्रम (n = 0; n < NUM_LEDS; n++) अणु
		अगर (led == bigben->leds[n])
			वापस (bigben->led_state & BIT(n)) ? LED_ON : LED_OFF;
	पूर्ण

	वापस LED_OFF;
पूर्ण

अटल व्योम bigben_हटाओ(काष्ठा hid_device *hid)
अणु
	काष्ठा bigben_device *bigben = hid_get_drvdata(hid);

	bigben->हटाओd = true;
	cancel_work_sync(&bigben->worker);
	hid_hw_stop(hid);
पूर्ण

अटल पूर्णांक bigben_probe(काष्ठा hid_device *hid,
	स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा bigben_device *bigben;
	काष्ठा hid_input *hidinput;
	काष्ठा list_head *report_list;
	काष्ठा led_classdev *led;
	अक्षर *name;
	माप_प्रकार name_sz;
	पूर्णांक n, error;

	bigben = devm_kzalloc(&hid->dev, माप(*bigben), GFP_KERNEL);
	अगर (!bigben)
		वापस -ENOMEM;
	hid_set_drvdata(hid, bigben);
	bigben->hid = hid;
	bigben->हटाओd = false;

	error = hid_parse(hid);
	अगर (error) अणु
		hid_err(hid, "parse failed\n");
		वापस error;
	पूर्ण

	error = hid_hw_start(hid, HID_CONNECT_DEFAULT & ~HID_CONNECT_FF);
	अगर (error) अणु
		hid_err(hid, "hw start failed\n");
		वापस error;
	पूर्ण

	report_list = &hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list;
	bigben->report = list_entry(report_list->next,
		काष्ठा hid_report, list);

	hidinput = list_first_entry(&hid->inमाला_दो, काष्ठा hid_input, list);
	set_bit(FF_RUMBLE, hidinput->input->ffbit);

	INIT_WORK(&bigben->worker, bigben_worker);

	error = input_ff_create_memless(hidinput->input, शून्य,
		hid_bigben_play_effect);
	अगर (error)
		जाओ error_hw_stop;

	name_sz = म_माप(dev_name(&hid->dev)) + म_माप(":red:bigben#") + 1;

	क्रम (n = 0; n < NUM_LEDS; n++) अणु
		led = devm_kzalloc(
			&hid->dev,
			माप(काष्ठा led_classdev) + name_sz,
			GFP_KERNEL
		);
		अगर (!led) अणु
			error = -ENOMEM;
			जाओ error_hw_stop;
		पूर्ण
		name = (व्योम *)(&led[1]);
		snम_लिखो(name, name_sz,
			"%s:red:bigben%d",
			dev_name(&hid->dev), n + 1
		);
		led->name = name;
		led->brightness = (n == 0) ? LED_ON : LED_OFF;
		led->max_brightness = 1;
		led->brightness_get = bigben_get_led;
		led->brightness_set = bigben_set_led;
		bigben->leds[n] = led;
		error = devm_led_classdev_रेजिस्टर(&hid->dev, led);
		अगर (error)
			जाओ error_hw_stop;
	पूर्ण

	/* initial state: LED1 is on, no rumble effect */
	bigben->led_state = BIT(0);
	bigben->right_motor_on = 0;
	bigben->left_motor_क्रमce = 0;
	bigben->work_led = true;
	bigben->work_ff = true;
	schedule_work(&bigben->worker);

	hid_info(hid, "LED and force feedback support for BigBen gamepad\n");

	वापस 0;

error_hw_stop:
	hid_hw_stop(hid);
	वापस error;
पूर्ण

अटल __u8 *bigben_report_fixup(काष्ठा hid_device *hid, __u8 *rdesc,
	अचिन्हित पूर्णांक *rsize)
अणु
	अगर (*rsize == PID0902_RDESC_ORIG_SIZE) अणु
		rdesc = pid0902_rdesc_fixed;
		*rsize = माप(pid0902_rdesc_fixed);
	पूर्ण अन्यथा
		hid_warn(hid, "unexpected rdesc, please submit for review\n");
	वापस rdesc;
पूर्ण

अटल स्थिर काष्ठा hid_device_id bigben_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_BIGBEN, USB_DEVICE_ID_BIGBEN_PS3OFMINIPAD) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, bigben_devices);

अटल काष्ठा hid_driver bigben_driver = अणु
	.name = "bigben",
	.id_table = bigben_devices,
	.probe = bigben_probe,
	.report_fixup = bigben_report_fixup,
	.हटाओ = bigben_हटाओ,
पूर्ण;
module_hid_driver(bigben_driver);

MODULE_LICENSE("GPL");
