<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Apple "Magic" Wireless Mouse driver
 *
 *   Copyright (c) 2010 Michael Poole <mdpoole@troilus.org>
 *   Copyright (c) 2010 Chase Douglas <chase.करोuglas@canonical.com>
 */

/*
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश "hid-ids.h"

अटल bool emulate_3button = true;
module_param(emulate_3button, bool, 0644);
MODULE_PARM_DESC(emulate_3button, "Emulate a middle button");

अटल पूर्णांक middle_button_start = -350;
अटल पूर्णांक middle_button_stop = +350;

अटल bool emulate_scroll_wheel = true;
module_param(emulate_scroll_wheel, bool, 0644);
MODULE_PARM_DESC(emulate_scroll_wheel, "Emulate a scroll wheel");

अटल अचिन्हित पूर्णांक scroll_speed = 32;
अटल पूर्णांक param_set_scroll_speed(स्थिर अक्षर *val,
				  स्थिर काष्ठा kernel_param *kp) अणु
	अचिन्हित दीर्घ speed;
	अगर (!val || kम_से_अदीर्घ(val, 0, &speed) || speed > 63)
		वापस -EINVAL;
	scroll_speed = speed;
	वापस 0;
पूर्ण
module_param_call(scroll_speed, param_set_scroll_speed, param_get_uपूर्णांक, &scroll_speed, 0644);
MODULE_PARM_DESC(scroll_speed, "Scroll speed, value from 0 (slow) to 63 (fast)");

अटल bool scroll_acceleration = false;
module_param(scroll_acceleration, bool, 0644);
MODULE_PARM_DESC(scroll_acceleration, "Accelerate sequential scroll events");

अटल bool report_undeciphered;
module_param(report_undeciphered, bool, 0644);
MODULE_PARM_DESC(report_undeciphered, "Report undeciphered multi-touch state field using a MSC_RAW event");

#घोषणा TRACKPAD_REPORT_ID 0x28
#घोषणा TRACKPAD2_USB_REPORT_ID 0x02
#घोषणा TRACKPAD2_BT_REPORT_ID 0x31
#घोषणा MOUSE_REPORT_ID    0x29
#घोषणा MOUSE2_REPORT_ID   0x12
#घोषणा DOUBLE_REPORT_ID   0xf7
/* These definitions are not precise, but they're बंद enough.  (Bits
 * 0x03 seem to indicate the aspect ratio of the touch, bits 0x70 seem
 * to be some kind of bit mask -- 0x20 may be a near-field पढ़ोing,
 * and 0x40 is actual contact, and 0x10 may be a start/stop or change
 * indication.)
 */
#घोषणा TOUCH_STATE_MASK  0xf0
#घोषणा TOUCH_STATE_NONE  0x00
#घोषणा TOUCH_STATE_START 0x30
#घोषणा TOUCH_STATE_DRAG  0x40

#घोषणा SCROLL_ACCEL_DEFAULT 7

/* Touch surface inक्रमmation. Dimension is in hundredths of a mm, min and max
 * are in units. */
#घोषणा MOUSE_DIMENSION_X (भग्न)9056
#घोषणा MOUSE_MIN_X -1100
#घोषणा MOUSE_MAX_X 1258
#घोषणा MOUSE_RES_X ((MOUSE_MAX_X - MOUSE_MIN_X) / (MOUSE_DIMENSION_X / 100))
#घोषणा MOUSE_DIMENSION_Y (भग्न)5152
#घोषणा MOUSE_MIN_Y -1589
#घोषणा MOUSE_MAX_Y 2047
#घोषणा MOUSE_RES_Y ((MOUSE_MAX_Y - MOUSE_MIN_Y) / (MOUSE_DIMENSION_Y / 100))

#घोषणा TRACKPAD_DIMENSION_X (भग्न)13000
#घोषणा TRACKPAD_MIN_X -2909
#घोषणा TRACKPAD_MAX_X 3167
#घोषणा TRACKPAD_RES_X \
	((TRACKPAD_MAX_X - TRACKPAD_MIN_X) / (TRACKPAD_DIMENSION_X / 100))
#घोषणा TRACKPAD_DIMENSION_Y (भग्न)11000
#घोषणा TRACKPAD_MIN_Y -2456
#घोषणा TRACKPAD_MAX_Y 2565
#घोषणा TRACKPAD_RES_Y \
	((TRACKPAD_MAX_Y - TRACKPAD_MIN_Y) / (TRACKPAD_DIMENSION_Y / 100))

#घोषणा TRACKPAD2_DIMENSION_X (भग्न)16000
#घोषणा TRACKPAD2_MIN_X -3678
#घोषणा TRACKPAD2_MAX_X 3934
#घोषणा TRACKPAD2_RES_X \
	((TRACKPAD2_MAX_X - TRACKPAD2_MIN_X) / (TRACKPAD2_DIMENSION_X / 100))
#घोषणा TRACKPAD2_DIMENSION_Y (भग्न)11490
#घोषणा TRACKPAD2_MIN_Y -2478
#घोषणा TRACKPAD2_MAX_Y 2587
#घोषणा TRACKPAD2_RES_Y \
	((TRACKPAD2_MAX_Y - TRACKPAD2_MIN_Y) / (TRACKPAD2_DIMENSION_Y / 100))

/**
 * काष्ठा magicmouse_sc - Tracks Magic Mouse-specअगरic data.
 * @input: Input device through which we report events.
 * @quirks: Currently unused.
 * @ntouches: Number of touches in most recent touch report.
 * @scroll_accel: Number of consecutive scroll motions.
 * @scroll_jअगरfies: Time of last scroll motion.
 * @touches: Most recent data क्रम a touch, indexed by tracking ID.
 * @tracking_ids: Mapping of current touch input data to @touches.
 */
काष्ठा magicmouse_sc अणु
	काष्ठा input_dev *input;
	अचिन्हित दीर्घ quirks;

	पूर्णांक ntouches;
	पूर्णांक scroll_accel;
	अचिन्हित दीर्घ scroll_jअगरfies;

	काष्ठा अणु
		लघु x;
		लघु y;
		लघु scroll_x;
		लघु scroll_y;
		u8 size;
	पूर्ण touches[16];
	पूर्णांक tracking_ids[16];

	काष्ठा hid_device *hdev;
	काष्ठा delayed_work work;
पूर्ण;

अटल पूर्णांक magicmouse_firm_touch(काष्ठा magicmouse_sc *msc)
अणु
	पूर्णांक touch = -1;
	पूर्णांक ii;

	/* If there is only one "firm" touch, set touch to its
	 * tracking ID.
	 */
	क्रम (ii = 0; ii < msc->ntouches; ii++) अणु
		पूर्णांक idx = msc->tracking_ids[ii];
		अगर (msc->touches[idx].size < 8) अणु
			/* Ignore this touch. */
		पूर्ण अन्यथा अगर (touch >= 0) अणु
			touch = -1;
			अवरोध;
		पूर्ण अन्यथा अणु
			touch = idx;
		पूर्ण
	पूर्ण

	वापस touch;
पूर्ण

अटल व्योम magicmouse_emit_buttons(काष्ठा magicmouse_sc *msc, पूर्णांक state)
अणु
	पूर्णांक last_state = test_bit(BTN_LEFT, msc->input->key) << 0 |
		test_bit(BTN_RIGHT, msc->input->key) << 1 |
		test_bit(BTN_MIDDLE, msc->input->key) << 2;

	अगर (emulate_3button) अणु
		पूर्णांक id;

		/* If some button was pressed beक्रमe, keep it held
		 * करोwn.  Otherwise, अगर there's exactly one firm
		 * touch, use that to override the mouse's guess.
		 */
		अगर (state == 0) अणु
			/* The button was released. */
		पूर्ण अन्यथा अगर (last_state != 0) अणु
			state = last_state;
		पूर्ण अन्यथा अगर ((id = magicmouse_firm_touch(msc)) >= 0) अणु
			पूर्णांक x = msc->touches[id].x;
			अगर (x < middle_button_start)
				state = 1;
			अन्यथा अगर (x > middle_button_stop)
				state = 2;
			अन्यथा
				state = 4;
		पूर्ण /* अन्यथा: we keep the mouse's guess */

		input_report_key(msc->input, BTN_MIDDLE, state & 4);
	पूर्ण

	input_report_key(msc->input, BTN_LEFT, state & 1);
	input_report_key(msc->input, BTN_RIGHT, state & 2);

	अगर (state != last_state)
		msc->scroll_accel = SCROLL_ACCEL_DEFAULT;
पूर्ण

अटल व्योम magicmouse_emit_touch(काष्ठा magicmouse_sc *msc, पूर्णांक raw_id, u8 *tdata)
अणु
	काष्ठा input_dev *input = msc->input;
	पूर्णांक id, x, y, size, orientation, touch_major, touch_minor, state, करोwn;
	पूर्णांक pressure = 0;

	अगर (input->id.product == USB_DEVICE_ID_APPLE_MAGICMOUSE ||
	    input->id.product == USB_DEVICE_ID_APPLE_MAGICMOUSE2) अणु
		id = (tdata[6] << 2 | tdata[5] >> 6) & 0xf;
		x = (tdata[1] << 28 | tdata[0] << 20) >> 20;
		y = -((tdata[2] << 24 | tdata[1] << 16) >> 20);
		size = tdata[5] & 0x3f;
		orientation = (tdata[6] >> 2) - 32;
		touch_major = tdata[3];
		touch_minor = tdata[4];
		state = tdata[7] & TOUCH_STATE_MASK;
		करोwn = state != TOUCH_STATE_NONE;
	पूर्ण अन्यथा अगर (input->id.product == USB_DEVICE_ID_APPLE_MAGICTRACKPAD2) अणु
		id = tdata[8] & 0xf;
		x = (tdata[1] << 27 | tdata[0] << 19) >> 19;
		y = -((tdata[3] << 30 | tdata[2] << 22 | tdata[1] << 14) >> 19);
		size = tdata[6];
		orientation = (tdata[8] >> 5) - 4;
		touch_major = tdata[4];
		touch_minor = tdata[5];
		pressure = tdata[7];
		state = tdata[3] & 0xC0;
		करोwn = state == 0x80;
	पूर्ण अन्यथा अणु /* USB_DEVICE_ID_APPLE_MAGICTRACKPAD */
		id = (tdata[7] << 2 | tdata[6] >> 6) & 0xf;
		x = (tdata[1] << 27 | tdata[0] << 19) >> 19;
		y = -((tdata[3] << 30 | tdata[2] << 22 | tdata[1] << 14) >> 19);
		size = tdata[6] & 0x3f;
		orientation = (tdata[7] >> 2) - 32;
		touch_major = tdata[4];
		touch_minor = tdata[5];
		state = tdata[8] & TOUCH_STATE_MASK;
		करोwn = state != TOUCH_STATE_NONE;
	पूर्ण

	/* Store tracking ID and other fields. */
	msc->tracking_ids[raw_id] = id;
	msc->touches[id].x = x;
	msc->touches[id].y = y;
	msc->touches[id].size = size;

	/* If requested, emulate a scroll wheel by detecting small
	 * vertical touch motions.
	 */
	अगर (emulate_scroll_wheel && (input->id.product !=
			USB_DEVICE_ID_APPLE_MAGICTRACKPAD2)) अणु
		अचिन्हित दीर्घ now = jअगरfies;
		पूर्णांक step_x = msc->touches[id].scroll_x - x;
		पूर्णांक step_y = msc->touches[id].scroll_y - y;

		/* Calculate and apply the scroll motion. */
		चयन (state) अणु
		हाल TOUCH_STATE_START:
			msc->touches[id].scroll_x = x;
			msc->touches[id].scroll_y = y;

			/* Reset acceleration after half a second. */
			अगर (scroll_acceleration && समय_beक्रमe(now,
						msc->scroll_jअगरfies + HZ / 2))
				msc->scroll_accel = max_t(पूर्णांक,
						msc->scroll_accel - 1, 1);
			अन्यथा
				msc->scroll_accel = SCROLL_ACCEL_DEFAULT;

			अवरोध;
		हाल TOUCH_STATE_DRAG:
			step_x /= (64 - (पूर्णांक)scroll_speed) * msc->scroll_accel;
			अगर (step_x != 0) अणु
				msc->touches[id].scroll_x -= step_x *
					(64 - scroll_speed) * msc->scroll_accel;
				msc->scroll_jअगरfies = now;
				input_report_rel(input, REL_HWHEEL, -step_x);
			पूर्ण

			step_y /= (64 - (पूर्णांक)scroll_speed) * msc->scroll_accel;
			अगर (step_y != 0) अणु
				msc->touches[id].scroll_y -= step_y *
					(64 - scroll_speed) * msc->scroll_accel;
				msc->scroll_jअगरfies = now;
				input_report_rel(input, REL_WHEEL, step_y);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (करोwn)
		msc->ntouches++;

	input_mt_slot(input, id);
	input_mt_report_slot_state(input, MT_TOOL_FINGER, करोwn);

	/* Generate the input events क्रम this touch. */
	अगर (करोwn) अणु
		input_report_असल(input, ABS_MT_TOUCH_MAJOR, touch_major << 2);
		input_report_असल(input, ABS_MT_TOUCH_MINOR, touch_minor << 2);
		input_report_असल(input, ABS_MT_ORIENTATION, -orientation);
		input_report_असल(input, ABS_MT_POSITION_X, x);
		input_report_असल(input, ABS_MT_POSITION_Y, y);

		अगर (input->id.product == USB_DEVICE_ID_APPLE_MAGICTRACKPAD2)
			input_report_असल(input, ABS_MT_PRESSURE, pressure);

		अगर (report_undeciphered) अणु
			अगर (input->id.product == USB_DEVICE_ID_APPLE_MAGICMOUSE ||
			    input->id.product == USB_DEVICE_ID_APPLE_MAGICMOUSE2)
				input_event(input, EV_MSC, MSC_RAW, tdata[7]);
			अन्यथा अगर (input->id.product !=
					USB_DEVICE_ID_APPLE_MAGICTRACKPAD2)
				input_event(input, EV_MSC, MSC_RAW, tdata[8]);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक magicmouse_raw_event(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	काष्ठा magicmouse_sc *msc = hid_get_drvdata(hdev);
	काष्ठा input_dev *input = msc->input;
	पूर्णांक x = 0, y = 0, ii, clicks = 0, npoपूर्णांकs;

	चयन (data[0]) अणु
	हाल TRACKPAD_REPORT_ID:
	हाल TRACKPAD2_BT_REPORT_ID:
		/* Expect four bytes of prefix, and N*9 bytes of touch data. */
		अगर (size < 4 || ((size - 4) % 9) != 0)
			वापस 0;
		npoपूर्णांकs = (size - 4) / 9;
		अगर (npoपूर्णांकs > 15) अणु
			hid_warn(hdev, "invalid size value (%d) for TRACKPAD_REPORT_ID\n",
					size);
			वापस 0;
		पूर्ण
		msc->ntouches = 0;
		क्रम (ii = 0; ii < npoपूर्णांकs; ii++)
			magicmouse_emit_touch(msc, ii, data + ii * 9 + 4);

		clicks = data[1];

		/* The following bits provide a device specअगरic बारtamp. They
		 * are unused here.
		 *
		 * ts = data[1] >> 6 | data[2] << 2 | data[3] << 10;
		 */
		अवरोध;
	हाल TRACKPAD2_USB_REPORT_ID:
		/* Expect twelve bytes of prefix and N*9 bytes of touch data. */
		अगर (size < 12 || ((size - 12) % 9) != 0)
			वापस 0;
		npoपूर्णांकs = (size - 12) / 9;
		अगर (npoपूर्णांकs > 15) अणु
			hid_warn(hdev, "invalid size value (%d) for TRACKPAD2_USB_REPORT_ID\n",
					size);
			वापस 0;
		पूर्ण
		msc->ntouches = 0;
		क्रम (ii = 0; ii < npoपूर्णांकs; ii++)
			magicmouse_emit_touch(msc, ii, data + ii * 9 + 12);

		clicks = data[1];
		अवरोध;
	हाल MOUSE_REPORT_ID:
		/* Expect six bytes of prefix, and N*8 bytes of touch data. */
		अगर (size < 6 || ((size - 6) % 8) != 0)
			वापस 0;
		npoपूर्णांकs = (size - 6) / 8;
		अगर (npoपूर्णांकs > 15) अणु
			hid_warn(hdev, "invalid size value (%d) for MOUSE_REPORT_ID\n",
					size);
			वापस 0;
		पूर्ण
		msc->ntouches = 0;
		क्रम (ii = 0; ii < npoपूर्णांकs; ii++)
			magicmouse_emit_touch(msc, ii, data + ii * 8 + 6);

		/* When emulating three-button mode, it is important
		 * to have the current touch inक्रमmation beक्रमe
		 * generating a click event.
		 */
		x = (पूर्णांक)(((data[3] & 0x0c) << 28) | (data[1] << 22)) >> 22;
		y = (पूर्णांक)(((data[3] & 0x30) << 26) | (data[2] << 22)) >> 22;
		clicks = data[3];

		/* The following bits provide a device specअगरic बारtamp. They
		 * are unused here.
		 *
		 * ts = data[3] >> 6 | data[4] << 2 | data[5] << 10;
		 */
		अवरोध;
	हाल MOUSE2_REPORT_ID:
		/* Size is either 8 or (14 + 8 * N) */
		अगर (size != 8 && (size < 14 || (size - 14) % 8 != 0))
			वापस 0;
		npoपूर्णांकs = (size - 14) / 8;
		अगर (npoपूर्णांकs > 15) अणु
			hid_warn(hdev, "invalid size value (%d) for MOUSE2_REPORT_ID\n",
					size);
			वापस 0;
		पूर्ण
		msc->ntouches = 0;
		क्रम (ii = 0; ii < npoपूर्णांकs; ii++)
			magicmouse_emit_touch(msc, ii, data + ii * 8 + 14);

		/* When emulating three-button mode, it is important
		 * to have the current touch inक्रमmation beक्रमe
		 * generating a click event.
		 */
		x = (पूर्णांक)((data[3] << 24) | (data[2] << 16)) >> 16;
		y = (पूर्णांक)((data[5] << 24) | (data[4] << 16)) >> 16;
		clicks = data[1];

		/* The following bits provide a device specअगरic बारtamp. They
		 * are unused here.
		 *
		 * ts = data[11] >> 6 | data[12] << 2 | data[13] << 10;
		 */
		अवरोध;
	हाल DOUBLE_REPORT_ID:
		/* Someबार the trackpad sends two touch reports in one
		 * packet.
		 */
		magicmouse_raw_event(hdev, report, data + 2, data[1]);
		magicmouse_raw_event(hdev, report, data + 2 + data[1],
			size - 2 - data[1]);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (input->id.product == USB_DEVICE_ID_APPLE_MAGICMOUSE ||
	    input->id.product == USB_DEVICE_ID_APPLE_MAGICMOUSE2) अणु
		magicmouse_emit_buttons(msc, clicks & 3);
		input_report_rel(input, REL_X, x);
		input_report_rel(input, REL_Y, y);
	पूर्ण अन्यथा अगर (input->id.product == USB_DEVICE_ID_APPLE_MAGICTRACKPAD2) अणु
		input_mt_sync_frame(input);
		input_report_key(input, BTN_MOUSE, clicks & 1);
	पूर्ण अन्यथा अणु /* USB_DEVICE_ID_APPLE_MAGICTRACKPAD */
		input_report_key(input, BTN_MOUSE, clicks & 1);
		input_mt_report_poपूर्णांकer_emulation(input, true);
	पूर्ण

	input_sync(input);
	वापस 1;
पूर्ण

अटल पूर्णांक magicmouse_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा magicmouse_sc *msc = hid_get_drvdata(hdev);
	अगर (msc->input->id.product == USB_DEVICE_ID_APPLE_MAGICMOUSE2 &&
	    field->report->id == MOUSE2_REPORT_ID) अणु
		/*
		 * magic_mouse_raw_event has करोne all the work. Skip hidinput.
		 *
		 * Specअगरically, hidinput may modअगरy BTN_LEFT and BTN_RIGHT,
		 * अवरोधing emulate_3button.
		 */
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक magicmouse_setup_input(काष्ठा input_dev *input, काष्ठा hid_device *hdev)
अणु
	पूर्णांक error;
	पूर्णांक mt_flags = 0;

	__set_bit(EV_KEY, input->evbit);

	अगर (input->id.product == USB_DEVICE_ID_APPLE_MAGICMOUSE ||
	    input->id.product == USB_DEVICE_ID_APPLE_MAGICMOUSE2) अणु
		__set_bit(BTN_LEFT, input->keybit);
		__set_bit(BTN_RIGHT, input->keybit);
		अगर (emulate_3button)
			__set_bit(BTN_MIDDLE, input->keybit);

		__set_bit(EV_REL, input->evbit);
		__set_bit(REL_X, input->relbit);
		__set_bit(REL_Y, input->relbit);
		अगर (emulate_scroll_wheel) अणु
			__set_bit(REL_WHEEL, input->relbit);
			__set_bit(REL_HWHEEL, input->relbit);
		पूर्ण
	पूर्ण अन्यथा अगर (input->id.product == USB_DEVICE_ID_APPLE_MAGICTRACKPAD2) अणु
		/* setting the device name to ensure the same driver settings
		 * get loaded, whether connected through bluetooth or USB
		 */
		input->name = "Apple Inc. Magic Trackpad 2";

		__clear_bit(EV_MSC, input->evbit);
		__clear_bit(BTN_0, input->keybit);
		__clear_bit(BTN_RIGHT, input->keybit);
		__clear_bit(BTN_MIDDLE, input->keybit);
		__set_bit(BTN_MOUSE, input->keybit);
		__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);
		__set_bit(BTN_TOOL_FINGER, input->keybit);

		mt_flags = INPUT_MT_POINTER | INPUT_MT_DROP_UNUSED |
				INPUT_MT_TRACK;
	पूर्ण अन्यथा अणु /* USB_DEVICE_ID_APPLE_MAGICTRACKPAD */
		/* input->keybit is initialized with incorrect button info
		 * क्रम Magic Trackpad. There really is only one physical
		 * button (BTN_LEFT == BTN_MOUSE). Make sure we करोn't
		 * advertise buttons that करोn't exist...
		 */
		__clear_bit(BTN_RIGHT, input->keybit);
		__clear_bit(BTN_MIDDLE, input->keybit);
		__set_bit(BTN_MOUSE, input->keybit);
		__set_bit(BTN_TOOL_FINGER, input->keybit);
		__set_bit(BTN_TOOL_DOUBLETAP, input->keybit);
		__set_bit(BTN_TOOL_TRIPLETAP, input->keybit);
		__set_bit(BTN_TOOL_QUADTAP, input->keybit);
		__set_bit(BTN_TOOL_QUINTTAP, input->keybit);
		__set_bit(BTN_TOUCH, input->keybit);
		__set_bit(INPUT_PROP_POINTER, input->propbit);
		__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);
	पूर्ण


	__set_bit(EV_ABS, input->evbit);

	error = input_mt_init_slots(input, 16, mt_flags);
	अगर (error)
		वापस error;
	input_set_असल_params(input, ABS_MT_TOUCH_MAJOR, 0, 255 << 2,
			     4, 0);
	input_set_असल_params(input, ABS_MT_TOUCH_MINOR, 0, 255 << 2,
			     4, 0);

	/* Note: Touch Y position from the device is inverted relative
	 * to how poपूर्णांकer motion is reported (and relative to how USB
	 * HID recommends the coordinates work).  This driver keeps
	 * the origin at the same position, and just uses the additive
	 * inverse of the reported Y.
	 */
	अगर (input->id.product == USB_DEVICE_ID_APPLE_MAGICMOUSE ||
	    input->id.product == USB_DEVICE_ID_APPLE_MAGICMOUSE2) अणु
		input_set_असल_params(input, ABS_MT_ORIENTATION, -31, 32, 1, 0);
		input_set_असल_params(input, ABS_MT_POSITION_X,
				     MOUSE_MIN_X, MOUSE_MAX_X, 4, 0);
		input_set_असल_params(input, ABS_MT_POSITION_Y,
				     MOUSE_MIN_Y, MOUSE_MAX_Y, 4, 0);

		input_असल_set_res(input, ABS_MT_POSITION_X,
				  MOUSE_RES_X);
		input_असल_set_res(input, ABS_MT_POSITION_Y,
				  MOUSE_RES_Y);
	पूर्ण अन्यथा अगर (input->id.product ==  USB_DEVICE_ID_APPLE_MAGICTRACKPAD2) अणु
		input_set_असल_params(input, ABS_MT_PRESSURE, 0, 253, 0, 0);
		input_set_असल_params(input, ABS_PRESSURE, 0, 253, 0, 0);
		input_set_असल_params(input, ABS_MT_ORIENTATION, -3, 4, 0, 0);
		input_set_असल_params(input, ABS_X, TRACKPAD2_MIN_X,
				     TRACKPAD2_MAX_X, 0, 0);
		input_set_असल_params(input, ABS_Y, TRACKPAD2_MIN_Y,
				     TRACKPAD2_MAX_Y, 0, 0);
		input_set_असल_params(input, ABS_MT_POSITION_X,
				     TRACKPAD2_MIN_X, TRACKPAD2_MAX_X, 0, 0);
		input_set_असल_params(input, ABS_MT_POSITION_Y,
				     TRACKPAD2_MIN_Y, TRACKPAD2_MAX_Y, 0, 0);

		input_असल_set_res(input, ABS_X, TRACKPAD2_RES_X);
		input_असल_set_res(input, ABS_Y, TRACKPAD2_RES_Y);
		input_असल_set_res(input, ABS_MT_POSITION_X, TRACKPAD2_RES_X);
		input_असल_set_res(input, ABS_MT_POSITION_Y, TRACKPAD2_RES_Y);
	पूर्ण अन्यथा अणु /* USB_DEVICE_ID_APPLE_MAGICTRACKPAD */
		input_set_असल_params(input, ABS_MT_ORIENTATION, -31, 32, 1, 0);
		input_set_असल_params(input, ABS_X, TRACKPAD_MIN_X,
				     TRACKPAD_MAX_X, 4, 0);
		input_set_असल_params(input, ABS_Y, TRACKPAD_MIN_Y,
				     TRACKPAD_MAX_Y, 4, 0);
		input_set_असल_params(input, ABS_MT_POSITION_X,
				     TRACKPAD_MIN_X, TRACKPAD_MAX_X, 4, 0);
		input_set_असल_params(input, ABS_MT_POSITION_Y,
				     TRACKPAD_MIN_Y, TRACKPAD_MAX_Y, 4, 0);

		input_असल_set_res(input, ABS_X, TRACKPAD_RES_X);
		input_असल_set_res(input, ABS_Y, TRACKPAD_RES_Y);
		input_असल_set_res(input, ABS_MT_POSITION_X,
				  TRACKPAD_RES_X);
		input_असल_set_res(input, ABS_MT_POSITION_Y,
				  TRACKPAD_RES_Y);
	पूर्ण

	input_set_events_per_packet(input, 60);

	अगर (report_undeciphered &&
	    input->id.product != USB_DEVICE_ID_APPLE_MAGICTRACKPAD2) अणु
		__set_bit(EV_MSC, input->evbit);
		__set_bit(MSC_RAW, input->mscbit);
	पूर्ण

	/*
	 * hid-input may mark device as using स्वतःrepeat, but neither
	 * the trackpad, nor the mouse actually want it.
	 */
	__clear_bit(EV_REP, input->evbit);

	वापस 0;
पूर्ण

अटल पूर्णांक magicmouse_input_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hi, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा magicmouse_sc *msc = hid_get_drvdata(hdev);

	अगर (!msc->input)
		msc->input = hi->input;

	/* Magic Trackpad करोes not give relative data after चयनing to MT */
	अगर ((hi->input->id.product == USB_DEVICE_ID_APPLE_MAGICTRACKPAD ||
	     hi->input->id.product == USB_DEVICE_ID_APPLE_MAGICTRACKPAD2) &&
	    field->flags & HID_MAIN_ITEM_RELATIVE)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक magicmouse_input_configured(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hi)

अणु
	काष्ठा magicmouse_sc *msc = hid_get_drvdata(hdev);
	पूर्णांक ret;

	ret = magicmouse_setup_input(msc->input, hdev);
	अगर (ret) अणु
		hid_err(hdev, "magicmouse setup input failed (%d)\n", ret);
		/* clean msc->input to notअगरy probe() of the failure */
		msc->input = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक magicmouse_enable_multitouch(काष्ठा hid_device *hdev)
अणु
	स्थिर u8 *feature;
	स्थिर u8 feature_mt[] = अणु 0xD7, 0x01 पूर्ण;
	स्थिर u8 feature_mt_mouse2[] = अणु 0xF1, 0x02, 0x01 पूर्ण;
	स्थिर u8 feature_mt_trackpad2_usb[] = अणु 0x02, 0x01 पूर्ण;
	स्थिर u8 feature_mt_trackpad2_bt[] = अणु 0xF1, 0x02, 0x01 पूर्ण;
	u8 *buf;
	पूर्णांक ret;
	पूर्णांक feature_size;

	अगर (hdev->product == USB_DEVICE_ID_APPLE_MAGICTRACKPAD2) अणु
		अगर (hdev->venकरोr == BT_VENDOR_ID_APPLE) अणु
			feature_size = माप(feature_mt_trackpad2_bt);
			feature = feature_mt_trackpad2_bt;
		पूर्ण अन्यथा अणु /* USB_VENDOR_ID_APPLE */
			feature_size = माप(feature_mt_trackpad2_usb);
			feature = feature_mt_trackpad2_usb;
		पूर्ण
	पूर्ण अन्यथा अगर (hdev->product == USB_DEVICE_ID_APPLE_MAGICMOUSE2) अणु
		feature_size = माप(feature_mt_mouse2);
		feature = feature_mt_mouse2;
	पूर्ण अन्यथा अणु
		feature_size = माप(feature_mt);
		feature = feature_mt;
	पूर्ण

	buf = kmemdup(feature, feature_size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = hid_hw_raw_request(hdev, buf[0], buf, feature_size,
				HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल व्योम magicmouse_enable_mt_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा magicmouse_sc *msc =
		container_of(work, काष्ठा magicmouse_sc, work.work);
	पूर्णांक ret;

	ret = magicmouse_enable_multitouch(msc->hdev);
	अगर (ret < 0)
		hid_err(msc->hdev, "unable to request touch data (%d)\n", ret);
पूर्ण

अटल पूर्णांक magicmouse_probe(काष्ठा hid_device *hdev,
	स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा magicmouse_sc *msc;
	काष्ठा hid_report *report;
	पूर्णांक ret;

	अगर (id->venकरोr == USB_VENDOR_ID_APPLE &&
	    id->product == USB_DEVICE_ID_APPLE_MAGICTRACKPAD2 &&
	    hdev->type != HID_TYPE_USBMOUSE)
		वापस -ENODEV;

	msc = devm_kzalloc(&hdev->dev, माप(*msc), GFP_KERNEL);
	अगर (msc == शून्य) अणु
		hid_err(hdev, "can't alloc magicmouse descriptor\n");
		वापस -ENOMEM;
	पूर्ण

	msc->scroll_accel = SCROLL_ACCEL_DEFAULT;
	msc->hdev = hdev;
	INIT_DEFERRABLE_WORK(&msc->work, magicmouse_enable_mt_work);

	msc->quirks = id->driver_data;
	hid_set_drvdata(hdev, msc);

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "magicmouse hid parse failed\n");
		वापस ret;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hdev, "magicmouse hw start failed\n");
		वापस ret;
	पूर्ण

	अगर (!msc->input) अणु
		hid_err(hdev, "magicmouse input not registered\n");
		ret = -ENOMEM;
		जाओ err_stop_hw;
	पूर्ण

	अगर (id->product == USB_DEVICE_ID_APPLE_MAGICMOUSE)
		report = hid_रेजिस्टर_report(hdev, HID_INPUT_REPORT,
			MOUSE_REPORT_ID, 0);
	अन्यथा अगर (id->product == USB_DEVICE_ID_APPLE_MAGICMOUSE2)
		report = hid_रेजिस्टर_report(hdev, HID_INPUT_REPORT,
			MOUSE2_REPORT_ID, 0);
	अन्यथा अगर (id->product == USB_DEVICE_ID_APPLE_MAGICTRACKPAD2) अणु
		अगर (id->venकरोr == BT_VENDOR_ID_APPLE)
			report = hid_रेजिस्टर_report(hdev, HID_INPUT_REPORT,
				TRACKPAD2_BT_REPORT_ID, 0);
		अन्यथा /* USB_VENDOR_ID_APPLE */
			report = hid_रेजिस्टर_report(hdev, HID_INPUT_REPORT,
				TRACKPAD2_USB_REPORT_ID, 0);
	पूर्ण अन्यथा अणु /* USB_DEVICE_ID_APPLE_MAGICTRACKPAD */
		report = hid_रेजिस्टर_report(hdev, HID_INPUT_REPORT,
			TRACKPAD_REPORT_ID, 0);
		report = hid_रेजिस्टर_report(hdev, HID_INPUT_REPORT,
			DOUBLE_REPORT_ID, 0);
	पूर्ण

	अगर (!report) अणु
		hid_err(hdev, "unable to register touch report\n");
		ret = -ENOMEM;
		जाओ err_stop_hw;
	पूर्ण
	report->size = 6;

	/*
	 * Some devices repond with 'invalid report id' when feature
	 * report चयनing it पूर्णांकo multitouch mode is sent to it.
	 *
	 * This results in -EIO from the _raw low-level transport callback,
	 * but there seems to be no other way of चयनing the mode.
	 * Thus the super-ugly hacky success check below.
	 */
	ret = magicmouse_enable_multitouch(hdev);
	अगर (ret != -EIO && ret < 0) अणु
		hid_err(hdev, "unable to request touch data (%d)\n", ret);
		जाओ err_stop_hw;
	पूर्ण
	अगर (ret == -EIO && id->product == USB_DEVICE_ID_APPLE_MAGICMOUSE2) अणु
		schedule_delayed_work(&msc->work, msecs_to_jअगरfies(500));
	पूर्ण

	वापस 0;
err_stop_hw:
	hid_hw_stop(hdev);
	वापस ret;
पूर्ण

अटल व्योम magicmouse_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा magicmouse_sc *msc = hid_get_drvdata(hdev);

	अगर (msc)
		cancel_delayed_work_sync(&msc->work);

	hid_hw_stop(hdev);
पूर्ण

अटल स्थिर काष्ठा hid_device_id magic_mice[] = अणु
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE,
		USB_DEVICE_ID_APPLE_MAGICMOUSE), .driver_data = 0 पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(BT_VENDOR_ID_APPLE,
		USB_DEVICE_ID_APPLE_MAGICMOUSE2), .driver_data = 0 पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE,
		USB_DEVICE_ID_APPLE_MAGICTRACKPAD), .driver_data = 0 पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(BT_VENDOR_ID_APPLE,
		USB_DEVICE_ID_APPLE_MAGICTRACKPAD2), .driver_data = 0 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE,
		USB_DEVICE_ID_APPLE_MAGICTRACKPAD2), .driver_data = 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, magic_mice);

अटल काष्ठा hid_driver magicmouse_driver = अणु
	.name = "magicmouse",
	.id_table = magic_mice,
	.probe = magicmouse_probe,
	.हटाओ = magicmouse_हटाओ,
	.raw_event = magicmouse_raw_event,
	.event = magicmouse_event,
	.input_mapping = magicmouse_input_mapping,
	.input_configured = magicmouse_input_configured,
पूर्ण;
module_hid_driver(magicmouse_driver);

MODULE_LICENSE("GPL");
