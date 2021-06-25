<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID driver क्रम THQ PS3 uDraw tablet
 *
 * Copyright (C) 2016 Red Hat Inc. All Rights Reserved
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश "hid-ids.h"

MODULE_AUTHOR("Bastien Nocera <hadess@hadess.net>");
MODULE_DESCRIPTION("PS3 uDraw tablet driver");
MODULE_LICENSE("GPL");

/*
 * Protocol inक्रमmation from:
 * https://bअक्रमonw.net/udraw/
 * and the source code of:
 * https://vvvv.org/contribution/udraw-hid
 */

/*
 * The device is setup with multiple input devices:
 * - the touch area which works as a touchpad
 * - the tablet area which works as a touchpad/drawing tablet
 * - a joypad with a d-pad, and 7 buttons
 * - an accelerometer device
 */

क्रमागत अणु
	TOUCH_NONE,
	TOUCH_PEN,
	TOUCH_FINGER,
	TOUCH_TWOFINGER
पूर्ण;

क्रमागत अणु
	AXIS_X,
	AXIS_Y,
	AXIS_Z
पूर्ण;

/*
 * Accelerometer min/max values
 * in order, X, Y and Z
 */
अटल काष्ठा अणु
	पूर्णांक min;
	पूर्णांक max;
पूर्ण accel_limits[] = अणु
	[AXIS_X] = अणु 490, 534 पूर्ण,
	[AXIS_Y] = अणु 490, 534 पूर्ण,
	[AXIS_Z] = अणु 492, 536 पूर्ण
पूर्ण;

#घोषणा DEVICE_NAME "THQ uDraw Game Tablet for PS3"
/* resolution in pixels */
#घोषणा RES_X 1920
#घोषणा RES_Y 1080
/* size in mm */
#घोषणा WIDTH  160
#घोषणा HEIGHT 90
#घोषणा PRESSURE_OFFSET 113
#घोषणा MAX_PRESSURE (255 - PRESSURE_OFFSET)

काष्ठा udraw अणु
	काष्ठा input_dev *joy_input_dev;
	काष्ठा input_dev *touch_input_dev;
	काष्ठा input_dev *pen_input_dev;
	काष्ठा input_dev *accel_input_dev;
	काष्ठा hid_device *hdev;

	/*
	 * The device's two-finger support is pretty unreliable, as
	 * the device could report a single touch when the two fingers
	 * are too बंद together, and the distance between fingers, even
	 * though reported is not in the same unit as the touches.
	 *
	 * We'll make करो without it, and try to report the first touch
	 * as reliably as possible.
	 */
	पूर्णांक last_one_finger_x;
	पूर्णांक last_one_finger_y;
	पूर्णांक last_two_finger_x;
	पूर्णांक last_two_finger_y;
पूर्ण;

अटल पूर्णांक clamp_accel(पूर्णांक axis, पूर्णांक offset)
अणु
	axis = clamp(axis,
			accel_limits[offset].min,
			accel_limits[offset].max);
	axis = (axis - accel_limits[offset].min) /
			((accel_limits[offset].max -
			  accel_limits[offset].min) * 0xFF);
	वापस axis;
पूर्ण

अटल पूर्णांक udraw_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
	 u8 *data, पूर्णांक len)
अणु
	काष्ठा udraw *udraw = hid_get_drvdata(hdev);
	पूर्णांक touch;
	पूर्णांक x, y, z;

	अगर (len != 27)
		वापस 0;

	अगर (data[11] == 0x00)
		touch = TOUCH_NONE;
	अन्यथा अगर (data[11] == 0x40)
		touch = TOUCH_PEN;
	अन्यथा अगर (data[11] == 0x80)
		touch = TOUCH_FINGER;
	अन्यथा
		touch = TOUCH_TWOFINGER;

	/* joypad */
	input_report_key(udraw->joy_input_dev, BTN_WEST, data[0] & 1);
	input_report_key(udraw->joy_input_dev, BTN_SOUTH, !!(data[0] & 2));
	input_report_key(udraw->joy_input_dev, BTN_EAST, !!(data[0] & 4));
	input_report_key(udraw->joy_input_dev, BTN_NORTH, !!(data[0] & 8));

	input_report_key(udraw->joy_input_dev, BTN_SELECT, !!(data[1] & 1));
	input_report_key(udraw->joy_input_dev, BTN_START, !!(data[1] & 2));
	input_report_key(udraw->joy_input_dev, BTN_MODE, !!(data[1] & 16));

	x = y = 0;
	चयन (data[2]) अणु
	हाल 0x0:
		y = -127;
		अवरोध;
	हाल 0x1:
		y = -127;
		x = 127;
		अवरोध;
	हाल 0x2:
		x = 127;
		अवरोध;
	हाल 0x3:
		y = 127;
		x = 127;
		अवरोध;
	हाल 0x4:
		y = 127;
		अवरोध;
	हाल 0x5:
		y = 127;
		x = -127;
		अवरोध;
	हाल 0x6:
		x = -127;
		अवरोध;
	हाल 0x7:
		y = -127;
		x = -127;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	input_report_असल(udraw->joy_input_dev, ABS_X, x);
	input_report_असल(udraw->joy_input_dev, ABS_Y, y);

	input_sync(udraw->joy_input_dev);

	/* For pen and touchpad */
	x = y = 0;
	अगर (touch != TOUCH_NONE) अणु
		अगर (data[15] != 0x0F)
			x = data[15] * 256 + data[17];
		अगर (data[16] != 0x0F)
			y = data[16] * 256 + data[18];
	पूर्ण

	अगर (touch == TOUCH_FINGER) अणु
		/* Save the last one-finger touch */
		udraw->last_one_finger_x = x;
		udraw->last_one_finger_y = y;
		udraw->last_two_finger_x = -1;
		udraw->last_two_finger_y = -1;
	पूर्ण अन्यथा अगर (touch == TOUCH_TWOFINGER) अणु
		/*
		 * We have a problem because x/y is the one क्रम the
		 * second finger but we want the first finger given
		 * to user-space otherwise it'll look as अगर it jumped.
		 *
		 * See the udraw काष्ठा definition क्रम why this was
		 * implemented this way.
		 */
		अगर (udraw->last_two_finger_x == -1) अणु
			/* Save the position of the 2nd finger */
			udraw->last_two_finger_x = x;
			udraw->last_two_finger_y = y;

			x = udraw->last_one_finger_x;
			y = udraw->last_one_finger_y;
		पूर्ण अन्यथा अणु
			/*
			 * Offset the 2-finger coords using the
			 * saved data from the first finger
			 */
			x = x - (udraw->last_two_finger_x
				- udraw->last_one_finger_x);
			y = y - (udraw->last_two_finger_y
				- udraw->last_one_finger_y);
		पूर्ण
	पूर्ण

	/* touchpad */
	अगर (touch == TOUCH_FINGER || touch == TOUCH_TWOFINGER) अणु
		input_report_key(udraw->touch_input_dev, BTN_TOUCH, 1);
		input_report_key(udraw->touch_input_dev, BTN_TOOL_FINGER,
				touch == TOUCH_FINGER);
		input_report_key(udraw->touch_input_dev, BTN_TOOL_DOUBLETAP,
				touch == TOUCH_TWOFINGER);

		input_report_असल(udraw->touch_input_dev, ABS_X, x);
		input_report_असल(udraw->touch_input_dev, ABS_Y, y);
	पूर्ण अन्यथा अणु
		input_report_key(udraw->touch_input_dev, BTN_TOUCH, 0);
		input_report_key(udraw->touch_input_dev, BTN_TOOL_FINGER, 0);
		input_report_key(udraw->touch_input_dev, BTN_TOOL_DOUBLETAP, 0);
	पूर्ण
	input_sync(udraw->touch_input_dev);

	/* pen */
	अगर (touch == TOUCH_PEN) अणु
		पूर्णांक level;

		level = clamp(data[13] - PRESSURE_OFFSET,
				0, MAX_PRESSURE);

		input_report_key(udraw->pen_input_dev, BTN_TOUCH, (level != 0));
		input_report_key(udraw->pen_input_dev, BTN_TOOL_PEN, 1);
		input_report_असल(udraw->pen_input_dev, ABS_PRESSURE, level);
		input_report_असल(udraw->pen_input_dev, ABS_X, x);
		input_report_असल(udraw->pen_input_dev, ABS_Y, y);
	पूर्ण अन्यथा अणु
		input_report_key(udraw->pen_input_dev, BTN_TOUCH, 0);
		input_report_key(udraw->pen_input_dev, BTN_TOOL_PEN, 0);
		input_report_असल(udraw->pen_input_dev, ABS_PRESSURE, 0);
	पूर्ण
	input_sync(udraw->pen_input_dev);

	/* accel */
	x = (data[19] + (data[20] << 8));
	x = clamp_accel(x, AXIS_X);
	y = (data[21] + (data[22] << 8));
	y = clamp_accel(y, AXIS_Y);
	z = (data[23] + (data[24] << 8));
	z = clamp_accel(z, AXIS_Z);
	input_report_असल(udraw->accel_input_dev, ABS_X, x);
	input_report_असल(udraw->accel_input_dev, ABS_Y, y);
	input_report_असल(udraw->accel_input_dev, ABS_Z, z);
	input_sync(udraw->accel_input_dev);

	/* let hidraw and hiddev handle the report */
	वापस 0;
पूर्ण

अटल पूर्णांक udraw_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा udraw *udraw = input_get_drvdata(dev);

	वापस hid_hw_खोलो(udraw->hdev);
पूर्ण

अटल व्योम udraw_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा udraw *udraw = input_get_drvdata(dev);

	hid_hw_बंद(udraw->hdev);
पूर्ण

अटल काष्ठा input_dev *allocate_and_setup(काष्ठा hid_device *hdev,
		स्थिर अक्षर *name)
अणु
	काष्ठा input_dev *input_dev;

	input_dev = devm_input_allocate_device(&hdev->dev);
	अगर (!input_dev)
		वापस शून्य;

	input_dev->name = name;
	input_dev->phys = hdev->phys;
	input_dev->dev.parent = &hdev->dev;
	input_dev->खोलो = udraw_खोलो;
	input_dev->बंद = udraw_बंद;
	input_dev->uniq = hdev->uniq;
	input_dev->id.bustype = hdev->bus;
	input_dev->id.venकरोr  = hdev->venकरोr;
	input_dev->id.product = hdev->product;
	input_dev->id.version = hdev->version;
	input_set_drvdata(input_dev, hid_get_drvdata(hdev));

	वापस input_dev;
पूर्ण

अटल bool udraw_setup_touch(काष्ठा udraw *udraw,
		काष्ठा hid_device *hdev)
अणु
	काष्ठा input_dev *input_dev;

	input_dev = allocate_and_setup(hdev, DEVICE_NAME " Touchpad");
	अगर (!input_dev)
		वापस false;

	input_dev->evbit[0] = BIT(EV_ABS) | BIT(EV_KEY);

	input_set_असल_params(input_dev, ABS_X, 0, RES_X, 1, 0);
	input_असल_set_res(input_dev, ABS_X, RES_X / WIDTH);
	input_set_असल_params(input_dev, ABS_Y, 0, RES_Y, 1, 0);
	input_असल_set_res(input_dev, ABS_Y, RES_Y / HEIGHT);

	set_bit(BTN_TOUCH, input_dev->keybit);
	set_bit(BTN_TOOL_FINGER, input_dev->keybit);
	set_bit(BTN_TOOL_DOUBLETAP, input_dev->keybit);

	set_bit(INPUT_PROP_POINTER, input_dev->propbit);

	udraw->touch_input_dev = input_dev;

	वापस true;
पूर्ण

अटल bool udraw_setup_pen(काष्ठा udraw *udraw,
		काष्ठा hid_device *hdev)
अणु
	काष्ठा input_dev *input_dev;

	input_dev = allocate_and_setup(hdev, DEVICE_NAME " Pen");
	अगर (!input_dev)
		वापस false;

	input_dev->evbit[0] = BIT(EV_ABS) | BIT(EV_KEY);

	input_set_असल_params(input_dev, ABS_X, 0, RES_X, 1, 0);
	input_असल_set_res(input_dev, ABS_X, RES_X / WIDTH);
	input_set_असल_params(input_dev, ABS_Y, 0, RES_Y, 1, 0);
	input_असल_set_res(input_dev, ABS_Y, RES_Y / HEIGHT);
	input_set_असल_params(input_dev, ABS_PRESSURE,
			0, MAX_PRESSURE, 0, 0);

	set_bit(BTN_TOUCH, input_dev->keybit);
	set_bit(BTN_TOOL_PEN, input_dev->keybit);

	set_bit(INPUT_PROP_POINTER, input_dev->propbit);

	udraw->pen_input_dev = input_dev;

	वापस true;
पूर्ण

अटल bool udraw_setup_accel(काष्ठा udraw *udraw,
		काष्ठा hid_device *hdev)
अणु
	काष्ठा input_dev *input_dev;

	input_dev = allocate_and_setup(hdev, DEVICE_NAME " Accelerometer");
	अगर (!input_dev)
		वापस false;

	input_dev->evbit[0] = BIT(EV_ABS);

	/* 1G accel is reported as ~256, so clamp to 2G */
	input_set_असल_params(input_dev, ABS_X, -512, 512, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, -512, 512, 0, 0);
	input_set_असल_params(input_dev, ABS_Z, -512, 512, 0, 0);

	set_bit(INPUT_PROP_ACCELEROMETER, input_dev->propbit);

	udraw->accel_input_dev = input_dev;

	वापस true;
पूर्ण

अटल bool udraw_setup_joypad(काष्ठा udraw *udraw,
		काष्ठा hid_device *hdev)
अणु
	काष्ठा input_dev *input_dev;

	input_dev = allocate_and_setup(hdev, DEVICE_NAME " Joypad");
	अगर (!input_dev)
		वापस false;

	input_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_ABS);

	set_bit(BTN_SOUTH, input_dev->keybit);
	set_bit(BTN_NORTH, input_dev->keybit);
	set_bit(BTN_EAST, input_dev->keybit);
	set_bit(BTN_WEST, input_dev->keybit);
	set_bit(BTN_SELECT, input_dev->keybit);
	set_bit(BTN_START, input_dev->keybit);
	set_bit(BTN_MODE, input_dev->keybit);

	input_set_असल_params(input_dev, ABS_X, -127, 127, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, -127, 127, 0, 0);

	udraw->joy_input_dev = input_dev;

	वापस true;
पूर्ण

अटल पूर्णांक udraw_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा udraw *udraw;
	पूर्णांक ret;

	udraw = devm_kzalloc(&hdev->dev, माप(काष्ठा udraw), GFP_KERNEL);
	अगर (!udraw)
		वापस -ENOMEM;

	udraw->hdev = hdev;
	udraw->last_two_finger_x = -1;
	udraw->last_two_finger_y = -1;

	hid_set_drvdata(hdev, udraw);

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		वापस ret;
	पूर्ण

	अगर (!udraw_setup_joypad(udraw, hdev) ||
	    !udraw_setup_touch(udraw, hdev) ||
	    !udraw_setup_pen(udraw, hdev) ||
	    !udraw_setup_accel(udraw, hdev)) अणु
		hid_err(hdev, "could not allocate interfaces\n");
		वापस -ENOMEM;
	पूर्ण

	ret = input_रेजिस्टर_device(udraw->joy_input_dev) ||
		input_रेजिस्टर_device(udraw->touch_input_dev) ||
		input_रेजिस्टर_device(udraw->pen_input_dev) ||
		input_रेजिस्टर_device(udraw->accel_input_dev);
	अगर (ret) अणु
		hid_err(hdev, "failed to register interfaces\n");
		वापस ret;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_HIDRAW | HID_CONNECT_DRIVER);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id udraw_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_THQ, USB_DEVICE_ID_THQ_PS3_UDRAW) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, udraw_devices);

अटल काष्ठा hid_driver udraw_driver = अणु
	.name = "hid-udraw",
	.id_table = udraw_devices,
	.raw_event = udraw_raw_event,
	.probe = udraw_probe,
पूर्ण;
module_hid_driver(udraw_driver);
