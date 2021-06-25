<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HID Driver क्रम ELAN Touchpad
 *
 * Currently only supports touchpad found on HP Pavilion X2 10
 *
 * Copyright (c) 2016 Alexandrov Stanislav <neko@nya.ai>
 */

#समावेश <linux/hid.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#समावेश "hid-ids.h"

#घोषणा ELAN_MT_I2C		0x5d
#घोषणा ELAN_SINGLE_FINGER	0x81
#घोषणा ELAN_MT_FIRST_FINGER	0x82
#घोषणा ELAN_MT_SECOND_FINGER	0x83
#घोषणा ELAN_INPUT_REPORT_SIZE	8
#घोषणा ELAN_I2C_REPORT_SIZE	32
#घोषणा ELAN_FINGER_DATA_LEN	5
#घोषणा ELAN_MAX_FINGERS	5
#घोषणा ELAN_MAX_PRESSURE	255
#घोषणा ELAN_TP_USB_INTF	1

#घोषणा ELAN_FEATURE_REPORT	0x0d
#घोषणा ELAN_FEATURE_SIZE	5
#घोषणा ELAN_PARAM_MAX_X	6
#घोषणा ELAN_PARAM_MAX_Y	7
#घोषणा ELAN_PARAM_RES		8

#घोषणा ELAN_MUTE_LED_REPORT	0xBC
#घोषणा ELAN_LED_REPORT_SIZE	8

#घोषणा ELAN_HAS_LED		BIT(0)

काष्ठा elan_drvdata अणु
	काष्ठा input_dev *input;
	u8 prev_report[ELAN_INPUT_REPORT_SIZE];
	काष्ठा led_classdev mute_led;
	u8 mute_led_state;
	u16 max_x;
	u16 max_y;
	u16 res_x;
	u16 res_y;
पूर्ण;

अटल पूर्णांक is_not_elan_touchpad(काष्ठा hid_device *hdev)
अणु
	अगर (hdev->bus == BUS_USB) अणु
		काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);

		वापस (पूर्णांकf->altsetting->desc.bInterfaceNumber !=
			ELAN_TP_USB_INTF);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
			      काष्ठा hid_field *field, काष्ठा hid_usage *usage,
			      अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर (is_not_elan_touchpad(hdev))
		वापस 0;

	अगर (field->report->id == ELAN_SINGLE_FINGER ||
	    field->report->id == ELAN_MT_FIRST_FINGER ||
	    field->report->id == ELAN_MT_SECOND_FINGER ||
	    field->report->id == ELAN_MT_I2C)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक elan_get_device_param(काष्ठा hid_device *hdev,
				 अचिन्हित अक्षर *dmabuf, अचिन्हित अक्षर param)
अणु
	पूर्णांक ret;

	dmabuf[0] = ELAN_FEATURE_REPORT;
	dmabuf[1] = 0x05;
	dmabuf[2] = 0x03;
	dmabuf[3] = param;
	dmabuf[4] = 0x01;

	ret = hid_hw_raw_request(hdev, ELAN_FEATURE_REPORT, dmabuf,
				 ELAN_FEATURE_SIZE, HID_FEATURE_REPORT,
				 HID_REQ_SET_REPORT);
	अगर (ret != ELAN_FEATURE_SIZE) अणु
		hid_err(hdev, "Set report error for parm %d: %d\n", param, ret);
		वापस ret;
	पूर्ण

	ret = hid_hw_raw_request(hdev, ELAN_FEATURE_REPORT, dmabuf,
				 ELAN_FEATURE_SIZE, HID_FEATURE_REPORT,
				 HID_REQ_GET_REPORT);
	अगर (ret != ELAN_FEATURE_SIZE) अणु
		hid_err(hdev, "Get report error for parm %d: %d\n", param, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक elan_convert_res(अक्षर val)
अणु
	/*
	 * (value from firmware) * 10 + 790 = dpi
	 * dpi * 10 / 254 = करोts/mm
	 */
	वापस (val * 10 + 790) * 10 / 254;
पूर्ण

अटल पूर्णांक elan_get_device_params(काष्ठा hid_device *hdev)
अणु
	काष्ठा elan_drvdata *drvdata = hid_get_drvdata(hdev);
	अचिन्हित अक्षर *dmabuf;
	पूर्णांक ret;

	dmabuf = kदो_स्मृति(ELAN_FEATURE_SIZE, GFP_KERNEL);
	अगर (!dmabuf)
		वापस -ENOMEM;

	ret = elan_get_device_param(hdev, dmabuf, ELAN_PARAM_MAX_X);
	अगर (ret)
		जाओ err;

	drvdata->max_x = (dmabuf[4] << 8) | dmabuf[3];

	ret = elan_get_device_param(hdev, dmabuf, ELAN_PARAM_MAX_Y);
	अगर (ret)
		जाओ err;

	drvdata->max_y = (dmabuf[4] << 8) | dmabuf[3];

	ret = elan_get_device_param(hdev, dmabuf, ELAN_PARAM_RES);
	अगर (ret)
		जाओ err;

	drvdata->res_x = elan_convert_res(dmabuf[3]);
	drvdata->res_y = elan_convert_res(dmabuf[4]);

err:
	kमुक्त(dmabuf);
	वापस ret;
पूर्ण

अटल पूर्णांक elan_input_configured(काष्ठा hid_device *hdev, काष्ठा hid_input *hi)
अणु
	पूर्णांक ret;
	काष्ठा input_dev *input;
	काष्ठा elan_drvdata *drvdata = hid_get_drvdata(hdev);

	अगर (is_not_elan_touchpad(hdev))
		वापस 0;

	ret = elan_get_device_params(hdev);
	अगर (ret)
		वापस ret;

	input = devm_input_allocate_device(&hdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	input->name = "Elan Touchpad";
	input->phys = hdev->phys;
	input->uniq = hdev->uniq;
	input->id.bustype = hdev->bus;
	input->id.venकरोr  = hdev->venकरोr;
	input->id.product = hdev->product;
	input->id.version = hdev->version;
	input->dev.parent = &hdev->dev;

	input_set_असल_params(input, ABS_MT_POSITION_X, 0, drvdata->max_x,
			     0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y, 0, drvdata->max_y,
			     0, 0);
	input_set_असल_params(input, ABS_MT_PRESSURE, 0, ELAN_MAX_PRESSURE,
			     0, 0);

	__set_bit(BTN_LEFT, input->keybit);
	__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);

	ret = input_mt_init_slots(input, ELAN_MAX_FINGERS, INPUT_MT_POINTER);
	अगर (ret) अणु
		hid_err(hdev, "Failed to init elan MT slots: %d\n", ret);
		input_मुक्त_device(input);
		वापस ret;
	पूर्ण

	input_असल_set_res(input, ABS_X, drvdata->res_x);
	input_असल_set_res(input, ABS_Y, drvdata->res_y);

	ret = input_रेजिस्टर_device(input);
	अगर (ret) अणु
		hid_err(hdev, "Failed to register elan input device: %d\n",
			ret);
		input_mt_destroy_slots(input);
		input_मुक्त_device(input);
		वापस ret;
	पूर्ण

	drvdata->input = input;

	वापस 0;
पूर्ण

अटल व्योम elan_report_mt_slot(काष्ठा elan_drvdata *drvdata, u8 *data,
				अचिन्हित पूर्णांक slot_num)
अणु
	काष्ठा input_dev *input = drvdata->input;
	पूर्णांक x, y, p;

	bool active = !!data;

	input_mt_slot(input, slot_num);
	input_mt_report_slot_state(input, MT_TOOL_FINGER, active);
	अगर (active) अणु
		x = ((data[0] & 0xF0) << 4) | data[1];
		y = drvdata->max_y -
		    (((data[0] & 0x07) << 8) | data[2]);
		p = data[4];

		input_report_असल(input, ABS_MT_POSITION_X, x);
		input_report_असल(input, ABS_MT_POSITION_Y, y);
		input_report_असल(input, ABS_MT_PRESSURE, p);
	पूर्ण
पूर्ण

अटल व्योम elan_usb_report_input(काष्ठा elan_drvdata *drvdata, u8 *data)
अणु
	पूर्णांक i;
	काष्ठा input_dev *input = drvdata->input;

	/*
	 * There is 3 types of reports: क्रम single touch,
	 * क्रम multitouch - first finger and क्रम multitouch - second finger
	 *
	 * packet काष्ठाure क्रम ELAN_SINGLE_FINGER and ELAN_MT_FIRST_FINGER:
	 *
	 * byte 1: 1   0   0   0   0   0   0   1  // 0x81 or 0x82
	 * byte 2: 0   0   0   0   0   0   0   0  // looks like unused
	 * byte 3: f5  f4  f3  f2  f1  0   0   L
	 * byte 4: x12 x11 x10 x9  0?  y11 y10 y9
	 * byte 5: x8  x7  x6  x5  x4  x3  x2  x1
	 * byte 6: y8  y7  y6  y5  y4  y3  y2  y1
	 * byte 7: sy4 sy3 sy2 sy1 sx4 sx3 sx2 sx1
	 * byte 8: p8  p7  p6  p5  p4  p3  p2  p1
	 *
	 * packet काष्ठाure क्रम ELAN_MT_SECOND_FINGER:
	 *
	 * byte 1: 1   0   0   0   0   0   1   1  // 0x83
	 * byte 2: x12 x11 x10 x9  0   y11 y10 y9
	 * byte 3: x8  x7  x6  x5  x4  x3  x2  x1
	 * byte 4: y8  y7  y6  y5  y4  y3  y2  y1
	 * byte 5: sy4 sy3 sy2 sy1 sx4 sx3 sx2 sx1
	 * byte 6: p8  p7  p6  p5  p4  p3  p2  p1
	 * byte 7: 0   0   0   0   0   0   0   0
	 * byte 8: 0   0   0   0   0   0   0   0
	 *
	 * f5-f1: finger touch bits
	 * L: clickpad button
	 * sy / sx: finger width / height expressed in traces, the total number
	 *          of traces can be queried by करोing a HID_REQ_SET_REPORT
	 *          अणु 0x0d, 0x05, 0x03, 0x05, 0x01 पूर्ण followed by a GET, in the
	 *          वापसed buf, buf[3]=no-x-traces, buf[4]=no-y-traces.
	 * p: pressure
	 */

	अगर (data[0] == ELAN_SINGLE_FINGER) अणु
		क्रम (i = 0; i < ELAN_MAX_FINGERS; i++) अणु
			अगर (data[2] & BIT(i + 3))
				elan_report_mt_slot(drvdata, data + 3, i);
			अन्यथा
				elan_report_mt_slot(drvdata, शून्य, i);
		पूर्ण
		input_report_key(input, BTN_LEFT, data[2] & 0x01);
	पूर्ण
	/*
	 * When touched with two fingers Elan touchpad will emit two HID reports
	 * first is ELAN_MT_FIRST_FINGER and second is ELAN_MT_SECOND_FINGER
	 * we will save ELAN_MT_FIRST_FINGER report and रुको क्रम
	 * ELAN_MT_SECOND_FINGER to finish multitouch
	 */
	अगर (data[0] == ELAN_MT_FIRST_FINGER) अणु
		स_नकल(drvdata->prev_report, data,
		       माप(drvdata->prev_report));
		वापस;
	पूर्ण

	अगर (data[0] == ELAN_MT_SECOND_FINGER) अणु
		पूर्णांक first = 0;
		u8 *prev_report = drvdata->prev_report;

		अगर (prev_report[0] != ELAN_MT_FIRST_FINGER)
			वापस;

		क्रम (i = 0; i < ELAN_MAX_FINGERS; i++) अणु
			अगर (prev_report[2] & BIT(i + 3)) अणु
				अगर (!first) अणु
					first = 1;
					elan_report_mt_slot(drvdata, prev_report + 3, i);
				पूर्ण अन्यथा अणु
					elan_report_mt_slot(drvdata, data + 1, i);
				पूर्ण
			पूर्ण अन्यथा अणु
				elan_report_mt_slot(drvdata, शून्य, i);
			पूर्ण
		पूर्ण
		input_report_key(input, BTN_LEFT, prev_report[2] & 0x01);
	पूर्ण

	input_mt_sync_frame(input);
	input_sync(input);
पूर्ण

अटल व्योम elan_i2c_report_input(काष्ठा elan_drvdata *drvdata, u8 *data)
अणु
	काष्ठा input_dev *input = drvdata->input;
	u8 *finger_data;
	पूर्णांक i;

	/*
	 * Elan MT touchpads in i2c mode send finger data in the same क्रमmat
	 * as in USB mode, but then with all fingers in a single packet.
	 *
	 * packet काष्ठाure क्रम ELAN_MT_I2C:
	 *
	 * byte     1: 1   0   0   1   1   1   0   1   // 0x5d
	 * byte     2: f5  f4  f3  f2  f1  0   0   L
	 * byte     3: x12 x11 x10 x9  0?  y11 y10 y9
	 * byte     4: x8  x7  x6  x5  x4  x3  x2  x1
	 * byte     5: y8  y7  y6  y5  y4  y3  y2  y1
	 * byte     6: sy4 sy3 sy2 sy1 sx4 sx3 sx2 sx1
	 * byte     7: p8  p7  p6  p5  p4  p3  p2  p1
	 * byte  8-12: Same as byte 3-7 क्रम second finger करोwn
	 * byte 13-17: Same as byte 3-7 क्रम third finger करोwn
	 * byte 18-22: Same as byte 3-7 क्रम fourth finger करोwn
	 * byte 23-27: Same as byte 3-7 क्रम fअगरth finger करोwn
	 */

	finger_data = data + 2;
	क्रम (i = 0; i < ELAN_MAX_FINGERS; i++) अणु
		अगर (data[1] & BIT(i + 3)) अणु
			elan_report_mt_slot(drvdata, finger_data, i);
			finger_data += ELAN_FINGER_DATA_LEN;
		पूर्ण अन्यथा अणु
			elan_report_mt_slot(drvdata, शून्य, i);
		पूर्ण
	पूर्ण

	input_report_key(input, BTN_LEFT, data[1] & 0x01);
	input_mt_sync_frame(input);
	input_sync(input);
पूर्ण

अटल पूर्णांक elan_raw_event(काष्ठा hid_device *hdev,
			  काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	काष्ठा elan_drvdata *drvdata = hid_get_drvdata(hdev);

	अगर (is_not_elan_touchpad(hdev))
		वापस 0;

	अगर (data[0] == ELAN_SINGLE_FINGER ||
	    data[0] == ELAN_MT_FIRST_FINGER ||
	    data[0] == ELAN_MT_SECOND_FINGER) अणु
		अगर (size == ELAN_INPUT_REPORT_SIZE) अणु
			elan_usb_report_input(drvdata, data);
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (data[0] == ELAN_MT_I2C && size == ELAN_I2C_REPORT_SIZE) अणु
		elan_i2c_report_input(drvdata, data);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_start_multitouch(काष्ठा hid_device *hdev)
अणु
	पूर्णांक ret;

	/*
	 * This byte sequence will enable multitouch mode and disable
	 * mouse emulation
	 */
	अटल स्थिर अचिन्हित अक्षर buf[] = अणु 0x0D, 0x00, 0x03, 0x21, 0x00 पूर्ण;
	अचिन्हित अक्षर *dmabuf = kmemdup(buf, माप(buf), GFP_KERNEL);

	अगर (!dmabuf)
		वापस -ENOMEM;

	ret = hid_hw_raw_request(hdev, dmabuf[0], dmabuf, माप(buf),
				 HID_FEATURE_REPORT, HID_REQ_SET_REPORT);

	kमुक्त(dmabuf);

	अगर (ret != माप(buf)) अणु
		hid_err(hdev, "Failed to start multitouch: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_mute_led_set_brigtness(काष्ठा led_classdev *led_cdev,
				       क्रमागत led_brightness value)
अणु
	पूर्णांक ret;
	u8 led_state;
	काष्ठा device *dev = led_cdev->dev->parent;
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा elan_drvdata *drvdata = hid_get_drvdata(hdev);

	अचिन्हित अक्षर *dmabuf = kzalloc(ELAN_LED_REPORT_SIZE, GFP_KERNEL);

	अगर (!dmabuf)
		वापस -ENOMEM;

	led_state = !!value;

	dmabuf[0] = ELAN_MUTE_LED_REPORT;
	dmabuf[1] = 0x02;
	dmabuf[2] = led_state;

	ret = hid_hw_raw_request(hdev, dmabuf[0], dmabuf, ELAN_LED_REPORT_SIZE,
				 HID_FEATURE_REPORT, HID_REQ_SET_REPORT);

	kमुक्त(dmabuf);

	अगर (ret != ELAN_LED_REPORT_SIZE) अणु
		अगर (ret != -ENODEV)
			hid_err(hdev, "Failed to set mute led brightness: %d\n", ret);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण

	drvdata->mute_led_state = led_state;
	वापस 0;
पूर्ण

अटल पूर्णांक elan_init_mute_led(काष्ठा hid_device *hdev)
अणु
	काष्ठा elan_drvdata *drvdata = hid_get_drvdata(hdev);
	काष्ठा led_classdev *mute_led = &drvdata->mute_led;

	mute_led->name = "elan:red:mute";
	mute_led->शेष_trigger = "audio-mute";
	mute_led->brightness_set_blocking = elan_mute_led_set_brigtness;
	mute_led->max_brightness = LED_ON;
	mute_led->flags = LED_HW_PLUGGABLE;
	mute_led->dev = &hdev->dev;

	वापस devm_led_classdev_रेजिस्टर(&hdev->dev, mute_led);
पूर्ण

अटल पूर्णांक elan_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा elan_drvdata *drvdata;

	drvdata = devm_kzalloc(&hdev->dev, माप(*drvdata), GFP_KERNEL);

	अगर (!drvdata)
		वापस -ENOMEM;

	hid_set_drvdata(hdev, drvdata);

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "Hid Parse failed\n");
		वापस ret;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hdev, "Hid hw start failed\n");
		वापस ret;
	पूर्ण

	अगर (is_not_elan_touchpad(hdev))
		वापस 0;

	अगर (!drvdata->input) अणु
		hid_err(hdev, "Input device is not registered\n");
		ret = -ENAVAIL;
		जाओ err;
	पूर्ण

	ret = elan_start_multitouch(hdev);
	अगर (ret)
		जाओ err;

	अगर (id->driver_data & ELAN_HAS_LED) अणु
		ret = elan_init_mute_led(hdev);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	hid_hw_stop(hdev);
	वापस ret;
पूर्ण

अटल व्योम elan_हटाओ(काष्ठा hid_device *hdev)
अणु
	hid_hw_stop(hdev);
पूर्ण

अटल स्थिर काष्ठा hid_device_id elan_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ELAN, USB_DEVICE_ID_HP_X2),
	  .driver_data = ELAN_HAS_LED पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ELAN, USB_DEVICE_ID_HP_X2_10_COVER),
	  .driver_data = ELAN_HAS_LED पूर्ण,
	अणु HID_I2C_DEVICE(USB_VENDOR_ID_ELAN, USB_DEVICE_ID_TOSHIBA_CLICK_L9W) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, elan_devices);

अटल काष्ठा hid_driver elan_driver = अणु
	.name = "elan",
	.id_table = elan_devices,
	.input_mapping = elan_input_mapping,
	.input_configured = elan_input_configured,
	.raw_event = elan_raw_event,
	.probe = elan_probe,
	.हटाओ = elan_हटाओ,
पूर्ण;

module_hid_driver(elan_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexandrov Stanislav");
MODULE_DESCRIPTION("Driver for HID ELAN Touchpads");
