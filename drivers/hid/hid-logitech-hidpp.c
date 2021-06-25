<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  HIDPP protocol क्रम Logitech receivers
 *
 *  Copyright (c) 2011 Logitech (c)
 *  Copyright (c) 2012-2013 Google (c)
 *  Copyright (c) 2013-2014 Red Hat Inc.
 */


#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/usb.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/atomic.h>
#समावेश <linux/fixp-arith.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "usbhid/usbhid.h"
#समावेश "hid-ids.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Benjamin Tissoires <benjamin.tissoires@gmail.com>");
MODULE_AUTHOR("Nestor Lopez Casado <nlopezcasad@logitech.com>");

अटल bool disable_raw_mode;
module_param(disable_raw_mode, bool, 0644);
MODULE_PARM_DESC(disable_raw_mode,
	"Disable Raw mode reporting for touchpads and keep firmware gestures.");

अटल bool disable_tap_to_click;
module_param(disable_tap_to_click, bool, 0644);
MODULE_PARM_DESC(disable_tap_to_click,
	"Disable Tap-To-Click mode reporting for touchpads (only on the K400 currently).");

#घोषणा REPORT_ID_HIDPP_SHORT			0x10
#घोषणा REPORT_ID_HIDPP_LONG			0x11
#घोषणा REPORT_ID_HIDPP_VERY_LONG		0x12

#घोषणा HIDPP_REPORT_SHORT_LENGTH		7
#घोषणा HIDPP_REPORT_LONG_LENGTH		20
#घोषणा HIDPP_REPORT_VERY_दीर्घ_उच्च_LENGTH	64

#घोषणा HIDPP_REPORT_SHORT_SUPPORTED		BIT(0)
#घोषणा HIDPP_REPORT_LONG_SUPPORTED		BIT(1)
#घोषणा HIDPP_REPORT_VERY_LONG_SUPPORTED	BIT(2)

#घोषणा HIDPP_SUB_ID_CONSUMER_VENDOR_KEYS	0x03
#घोषणा HIDPP_SUB_ID_ROLLER			0x05
#घोषणा HIDPP_SUB_ID_MOUSE_EXTRA_BTNS		0x06

#घोषणा HIDPP_QUIRK_CLASS_WTP			BIT(0)
#घोषणा HIDPP_QUIRK_CLASS_M560			BIT(1)
#घोषणा HIDPP_QUIRK_CLASS_K400			BIT(2)
#घोषणा HIDPP_QUIRK_CLASS_G920			BIT(3)
#घोषणा HIDPP_QUIRK_CLASS_K750			BIT(4)

/* bits 2..20 are reserved क्रम classes */
/* #घोषणा HIDPP_QUIRK_CONNECT_EVENTS		BIT(21) disabled */
#घोषणा HIDPP_QUIRK_WTP_PHYSICAL_BUTTONS	BIT(22)
#घोषणा HIDPP_QUIRK_NO_HIDINPUT			BIT(23)
#घोषणा HIDPP_QUIRK_FORCE_OUTPUT_REPORTS	BIT(24)
#घोषणा HIDPP_QUIRK_UNIFYING			BIT(25)
#घोषणा HIDPP_QUIRK_HI_RES_SCROLL_1P0		BIT(26)
#घोषणा HIDPP_QUIRK_HI_RES_SCROLL_X2120		BIT(27)
#घोषणा HIDPP_QUIRK_HI_RES_SCROLL_X2121		BIT(28)
#घोषणा HIDPP_QUIRK_HIDPP_WHEELS		BIT(29)
#घोषणा HIDPP_QUIRK_HIDPP_EXTRA_MOUSE_BTNS	BIT(30)
#घोषणा HIDPP_QUIRK_HIDPP_CONSUMER_VENDOR_KEYS	BIT(31)

/* These are just aliases क्रम now */
#घोषणा HIDPP_QUIRK_KBD_SCROLL_WHEEL HIDPP_QUIRK_HIDPP_WHEELS
#घोषणा HIDPP_QUIRK_KBD_ZOOM_WHEEL   HIDPP_QUIRK_HIDPP_WHEELS

/* Convenience स्थिरant to check क्रम any high-res support. */
#घोषणा HIDPP_QUIRK_HI_RES_SCROLL	(HIDPP_QUIRK_HI_RES_SCROLL_1P0 | \
					 HIDPP_QUIRK_HI_RES_SCROLL_X2120 | \
					 HIDPP_QUIRK_HI_RES_SCROLL_X2121)

#घोषणा HIDPP_QUIRK_DELAYED_INIT		HIDPP_QUIRK_NO_HIDINPUT

#घोषणा HIDPP_CAPABILITY_HIDPP10_BATTERY	BIT(0)
#घोषणा HIDPP_CAPABILITY_HIDPP20_BATTERY	BIT(1)
#घोषणा HIDPP_CAPABILITY_BATTERY_MILEAGE	BIT(2)
#घोषणा HIDPP_CAPABILITY_BATTERY_LEVEL_STATUS	BIT(3)
#घोषणा HIDPP_CAPABILITY_BATTERY_VOLTAGE	BIT(4)
#घोषणा HIDPP_CAPABILITY_BATTERY_PERCENTAGE	BIT(5)
#घोषणा HIDPP_CAPABILITY_UNIFIED_BATTERY	BIT(6)

#घोषणा lg_map_key_clear(c)  hid_map_usage_clear(hi, usage, bit, max, EV_KEY, (c))

/*
 * There are two hidpp protocols in use, the first version hidpp10 is known
 * as रेजिस्टर access protocol or RAP, the second version hidpp20 is known as
 * feature access protocol or FAP
 *
 * Most older devices (including the Unअगरying usb receiver) use the RAP protocol
 * where as most newer devices use the FAP protocol. Both protocols are
 * compatible with the underlying transport, which could be usb, Unअगरiying, or
 * bluetooth. The message lengths are defined by the hid venकरोr specअगरic report
 * descriptor क्रम the HIDPP_SHORT report type (total message lenth 7 bytes) and
 * the HIDPP_LONG report type (total message length 20 bytes)
 *
 * The RAP protocol uses both report types, whereas the FAP only uses HIDPP_LONG
 * messages. The Unअगरying receiver itself responds to RAP messages (device index
 * is 0xFF क्रम the receiver), and all messages (लघु or दीर्घ) with a device
 * index between 1 and 6 are passed untouched to the corresponding paired
 * Unअगरying device.
 *
 * The paired device can be RAP or FAP, it will receive the message untouched
 * from the Unअगरiying receiver.
 */

काष्ठा fap अणु
	u8 feature_index;
	u8 funcindex_clientid;
	u8 params[HIDPP_REPORT_VERY_दीर्घ_उच्च_LENGTH - 4U];
पूर्ण;

काष्ठा rap अणु
	u8 sub_id;
	u8 reg_address;
	u8 params[HIDPP_REPORT_VERY_दीर्घ_उच्च_LENGTH - 4U];
पूर्ण;

काष्ठा hidpp_report अणु
	u8 report_id;
	u8 device_index;
	जोड़ अणु
		काष्ठा fap fap;
		काष्ठा rap rap;
		u8 rawbytes[माप(काष्ठा fap)];
	पूर्ण;
पूर्ण __packed;

काष्ठा hidpp_battery अणु
	u8 feature_index;
	u8 solar_feature_index;
	u8 voltage_feature_index;
	काष्ठा घातer_supply_desc desc;
	काष्ठा घातer_supply *ps;
	अक्षर name[64];
	पूर्णांक status;
	पूर्णांक capacity;
	पूर्णांक level;
	पूर्णांक voltage;
	पूर्णांक अक्षरge_type;
	bool online;
	u8 supported_levels_1004;
पूर्ण;

/**
 * काष्ठा hidpp_scroll_counter - Utility class क्रम processing high-resolution
 *                             scroll events.
 * @dev: the input device क्रम which events should be reported.
 * @wheel_multiplier: the scalar multiplier to be applied to each wheel event
 * @reमुख्यder: counts the number of high-resolution units moved since the last
 *             low-resolution event (REL_WHEEL or REL_HWHEEL) was sent. Should
 *             only be used by class methods.
 * @direction: direction of last movement (1 or -1)
 * @last_समय: last event समय, used to reset reमुख्यder after inactivity
 */
काष्ठा hidpp_scroll_counter अणु
	पूर्णांक wheel_multiplier;
	पूर्णांक reमुख्यder;
	पूर्णांक direction;
	अचिन्हित दीर्घ दीर्घ last_समय;
पूर्ण;

काष्ठा hidpp_device अणु
	काष्ठा hid_device *hid_dev;
	काष्ठा input_dev *input;
	काष्ठा mutex send_mutex;
	व्योम *send_receive_buf;
	अक्षर *name;		/* will never be शून्य and should not be मुक्तd */
	रुको_queue_head_t रुको;
	पूर्णांक very_दीर्घ_report_length;
	bool answer_available;
	u8 protocol_major;
	u8 protocol_minor;

	व्योम *निजी_data;

	काष्ठा work_काष्ठा work;
	काष्ठा kfअगरo delayed_work_fअगरo;
	atomic_t connected;
	काष्ठा input_dev *delayed_input;

	अचिन्हित दीर्घ quirks;
	अचिन्हित दीर्घ capabilities;
	u8 supported_reports;

	काष्ठा hidpp_battery battery;
	काष्ठा hidpp_scroll_counter vertical_wheel_counter;

	u8 wireless_feature_index;
पूर्ण;

/* HID++ 1.0 error codes */
#घोषणा HIDPP_ERROR				0x8f
#घोषणा HIDPP_ERROR_SUCCESS			0x00
#घोषणा HIDPP_ERROR_INVALID_SUBID		0x01
#घोषणा HIDPP_ERROR_INVALID_ADRESS		0x02
#घोषणा HIDPP_ERROR_INVALID_VALUE		0x03
#घोषणा HIDPP_ERROR_CONNECT_FAIL		0x04
#घोषणा HIDPP_ERROR_TOO_MANY_DEVICES		0x05
#घोषणा HIDPP_ERROR_ALREADY_EXISTS		0x06
#घोषणा HIDPP_ERROR_BUSY			0x07
#घोषणा HIDPP_ERROR_UNKNOWN_DEVICE		0x08
#घोषणा HIDPP_ERROR_RESOURCE_ERROR		0x09
#घोषणा HIDPP_ERROR_REQUEST_UNAVAILABLE		0x0a
#घोषणा HIDPP_ERROR_INVALID_PARAM_VALUE		0x0b
#घोषणा HIDPP_ERROR_WRONG_PIN_CODE		0x0c
/* HID++ 2.0 error codes */
#घोषणा HIDPP20_ERROR				0xff

अटल व्योम hidpp_connect_event(काष्ठा hidpp_device *hidpp_dev);

अटल पूर्णांक __hidpp_send_report(काष्ठा hid_device *hdev,
				काष्ठा hidpp_report *hidpp_report)
अणु
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);
	पूर्णांक fields_count, ret;

	चयन (hidpp_report->report_id) अणु
	हाल REPORT_ID_HIDPP_SHORT:
		fields_count = HIDPP_REPORT_SHORT_LENGTH;
		अवरोध;
	हाल REPORT_ID_HIDPP_LONG:
		fields_count = HIDPP_REPORT_LONG_LENGTH;
		अवरोध;
	हाल REPORT_ID_HIDPP_VERY_LONG:
		fields_count = hidpp->very_दीर्घ_report_length;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	/*
	 * set the device_index as the receiver, it will be overwritten by
	 * hid_hw_request अगर needed
	 */
	hidpp_report->device_index = 0xff;

	अगर (hidpp->quirks & HIDPP_QUIRK_FORCE_OUTPUT_REPORTS) अणु
		ret = hid_hw_output_report(hdev, (u8 *)hidpp_report, fields_count);
	पूर्ण अन्यथा अणु
		ret = hid_hw_raw_request(hdev, hidpp_report->report_id,
			(u8 *)hidpp_report, fields_count, HID_OUTPUT_REPORT,
			HID_REQ_SET_REPORT);
	पूर्ण

	वापस ret == fields_count ? 0 : -1;
पूर्ण

/*
 * hidpp_send_message_sync() वापसs 0 in हाल of success, and something अन्यथा
 * in हाल of a failure.
 * - If ' something else' is positive, that means that an error has been उठाओd
 *   by the protocol itself.
 * - If ' something else' is negative, that means that we had a classic error
 *   (-ENOMEM, -EPIPE, etc...)
 */
अटल पूर्णांक hidpp_send_message_sync(काष्ठा hidpp_device *hidpp,
	काष्ठा hidpp_report *message,
	काष्ठा hidpp_report *response)
अणु
	पूर्णांक ret;

	mutex_lock(&hidpp->send_mutex);

	hidpp->send_receive_buf = response;
	hidpp->answer_available = false;

	/*
	 * So that we can later validate the answer when it arrives
	 * in hidpp_raw_event
	 */
	*response = *message;

	ret = __hidpp_send_report(hidpp->hid_dev, message);

	अगर (ret) अणु
		dbg_hid("__hidpp_send_report returned err: %d\n", ret);
		स_रखो(response, 0, माप(काष्ठा hidpp_report));
		जाओ निकास;
	पूर्ण

	अगर (!रुको_event_समयout(hidpp->रुको, hidpp->answer_available,
				5*HZ)) अणु
		dbg_hid("%s:timeout waiting for response\n", __func__);
		स_रखो(response, 0, माप(काष्ठा hidpp_report));
		ret = -ETIMEDOUT;
	पूर्ण

	अगर (response->report_id == REPORT_ID_HIDPP_SHORT &&
	    response->rap.sub_id == HIDPP_ERROR) अणु
		ret = response->rap.params[1];
		dbg_hid("%s:got hidpp error %02X\n", __func__, ret);
		जाओ निकास;
	पूर्ण

	अगर ((response->report_id == REPORT_ID_HIDPP_LONG ||
			response->report_id == REPORT_ID_HIDPP_VERY_LONG) &&
			response->fap.feature_index == HIDPP20_ERROR) अणु
		ret = response->fap.params[1];
		dbg_hid("%s:got hidpp 2.0 error %02X\n", __func__, ret);
		जाओ निकास;
	पूर्ण

निकास:
	mutex_unlock(&hidpp->send_mutex);
	वापस ret;

पूर्ण

अटल पूर्णांक hidpp_send_fap_command_sync(काष्ठा hidpp_device *hidpp,
	u8 feat_index, u8 funcindex_clientid, u8 *params, पूर्णांक param_count,
	काष्ठा hidpp_report *response)
अणु
	काष्ठा hidpp_report *message;
	पूर्णांक ret;

	अगर (param_count > माप(message->fap.params))
		वापस -EINVAL;

	message = kzalloc(माप(काष्ठा hidpp_report), GFP_KERNEL);
	अगर (!message)
		वापस -ENOMEM;

	अगर (param_count > (HIDPP_REPORT_LONG_LENGTH - 4))
		message->report_id = REPORT_ID_HIDPP_VERY_LONG;
	अन्यथा
		message->report_id = REPORT_ID_HIDPP_LONG;
	message->fap.feature_index = feat_index;
	message->fap.funcindex_clientid = funcindex_clientid;
	स_नकल(&message->fap.params, params, param_count);

	ret = hidpp_send_message_sync(hidpp, message, response);
	kमुक्त(message);
	वापस ret;
पूर्ण

अटल पूर्णांक hidpp_send_rap_command_sync(काष्ठा hidpp_device *hidpp_dev,
	u8 report_id, u8 sub_id, u8 reg_address, u8 *params, पूर्णांक param_count,
	काष्ठा hidpp_report *response)
अणु
	काष्ठा hidpp_report *message;
	पूर्णांक ret, max_count;

	/* Send as दीर्घ report अगर लघु reports are not supported. */
	अगर (report_id == REPORT_ID_HIDPP_SHORT &&
	    !(hidpp_dev->supported_reports & HIDPP_REPORT_SHORT_SUPPORTED))
		report_id = REPORT_ID_HIDPP_LONG;

	चयन (report_id) अणु
	हाल REPORT_ID_HIDPP_SHORT:
		max_count = HIDPP_REPORT_SHORT_LENGTH - 4;
		अवरोध;
	हाल REPORT_ID_HIDPP_LONG:
		max_count = HIDPP_REPORT_LONG_LENGTH - 4;
		अवरोध;
	हाल REPORT_ID_HIDPP_VERY_LONG:
		max_count = hidpp_dev->very_दीर्घ_report_length - 4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (param_count > max_count)
		वापस -EINVAL;

	message = kzalloc(माप(काष्ठा hidpp_report), GFP_KERNEL);
	अगर (!message)
		वापस -ENOMEM;
	message->report_id = report_id;
	message->rap.sub_id = sub_id;
	message->rap.reg_address = reg_address;
	स_नकल(&message->rap.params, params, param_count);

	ret = hidpp_send_message_sync(hidpp_dev, message, response);
	kमुक्त(message);
	वापस ret;
पूर्ण

अटल व्योम delayed_work_cb(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hidpp_device *hidpp = container_of(work, काष्ठा hidpp_device,
							work);
	hidpp_connect_event(hidpp);
पूर्ण

अटल अंतरभूत bool hidpp_match_answer(काष्ठा hidpp_report *question,
		काष्ठा hidpp_report *answer)
अणु
	वापस (answer->fap.feature_index == question->fap.feature_index) &&
	   (answer->fap.funcindex_clientid == question->fap.funcindex_clientid);
पूर्ण

अटल अंतरभूत bool hidpp_match_error(काष्ठा hidpp_report *question,
		काष्ठा hidpp_report *answer)
अणु
	वापस ((answer->rap.sub_id == HIDPP_ERROR) ||
	    (answer->fap.feature_index == HIDPP20_ERROR)) &&
	    (answer->fap.funcindex_clientid == question->fap.feature_index) &&
	    (answer->fap.params[0] == question->fap.funcindex_clientid);
पूर्ण

अटल अंतरभूत bool hidpp_report_is_connect_event(काष्ठा hidpp_device *hidpp,
		काष्ठा hidpp_report *report)
अणु
	वापस (hidpp->wireless_feature_index &&
		(report->fap.feature_index == hidpp->wireless_feature_index)) ||
		((report->report_id == REPORT_ID_HIDPP_SHORT) &&
		(report->rap.sub_id == 0x41));
पूर्ण

/*
 * hidpp_prefix_name() prefixes the current given name with "Logitech ".
 */
अटल व्योम hidpp_prefix_name(अक्षर **name, पूर्णांक name_length)
अणु
#घोषणा PREFIX_LENGTH 9 /* "Logitech " */

	पूर्णांक new_length;
	अक्षर *new_name;

	अगर (name_length > PREFIX_LENGTH &&
	    म_भेदन(*name, "Logitech ", PREFIX_LENGTH) == 0)
		/* The prefix has is alपढ़ोy in the name */
		वापस;

	new_length = PREFIX_LENGTH + name_length;
	new_name = kzalloc(new_length, GFP_KERNEL);
	अगर (!new_name)
		वापस;

	snम_लिखो(new_name, new_length, "Logitech %s", *name);

	kमुक्त(*name);

	*name = new_name;
पूर्ण

/**
 * hidpp_scroll_counter_handle_scroll() - Send high- and low-resolution scroll
 *                                        events given a high-resolution wheel
 *                                        movement.
 * @input_dev: Poपूर्णांकer to the input device
 * @counter: a hid_scroll_counter काष्ठा describing the wheel.
 * @hi_res_value: the movement of the wheel, in the mouse's high-resolution
 *                units.
 *
 * Given a high-resolution movement, this function converts the movement पूर्णांकo
 * fractions of 120 and emits high-resolution scroll events क्रम the input
 * device. It also uses the multiplier from &काष्ठा hid_scroll_counter to
 * emit low-resolution scroll events when appropriate क्रम
 * backwards-compatibility with userspace input libraries.
 */
अटल व्योम hidpp_scroll_counter_handle_scroll(काष्ठा input_dev *input_dev,
					       काष्ठा hidpp_scroll_counter *counter,
					       पूर्णांक hi_res_value)
अणु
	पूर्णांक low_res_value, reमुख्यder, direction;
	अचिन्हित दीर्घ दीर्घ now, previous;

	hi_res_value = hi_res_value * 120/counter->wheel_multiplier;
	input_report_rel(input_dev, REL_WHEEL_HI_RES, hi_res_value);

	reमुख्यder = counter->reमुख्यder;
	direction = hi_res_value > 0 ? 1 : -1;

	now = sched_घड़ी();
	previous = counter->last_समय;
	counter->last_समय = now;
	/*
	 * Reset the reमुख्यder after a period of inactivity or when the
	 * direction changes. This prevents the REL_WHEEL emulation poपूर्णांक
	 * from sliding क्रम devices that करोn't always provide the same
	 * number of movements per detent.
	 */
	अगर (now - previous > 1000000000 || direction != counter->direction)
		reमुख्यder = 0;

	counter->direction = direction;
	reमुख्यder += hi_res_value;

	/* Some wheels will rest 7/8ths of a detent from the previous detent
	 * after slow movement, so we want the threshold क्रम low-res events to
	 * be in the middle between two detents (e.g. after 4/8ths) as
	 * opposed to on the detents themselves (8/8ths).
	 */
	अगर (असल(reमुख्यder) >= 60) अणु
		/* Add (or subtract) 1 because we want to trigger when the wheel
		 * is half-way to the next detent (i.e. scroll 1 detent after a
		 * 1/2 detent movement, 2 detents after a 1 1/2 detent movement,
		 * etc.).
		 */
		low_res_value = reमुख्यder / 120;
		अगर (low_res_value == 0)
			low_res_value = (hi_res_value > 0 ? 1 : -1);
		input_report_rel(input_dev, REL_WHEEL, low_res_value);
		reमुख्यder -= low_res_value * 120;
	पूर्ण
	counter->reमुख्यder = reमुख्यder;
पूर्ण

/* -------------------------------------------------------------------------- */
/* HIDP++ 1.0 commands                                                        */
/* -------------------------------------------------------------------------- */

#घोषणा HIDPP_SET_REGISTER				0x80
#घोषणा HIDPP_GET_REGISTER				0x81
#घोषणा HIDPP_SET_LONG_REGISTER				0x82
#घोषणा HIDPP_GET_LONG_REGISTER				0x83

/**
 * hidpp10_set_रेजिस्टर - Modअगरy a HID++ 1.0 रेजिस्टर.
 * @hidpp_dev: the device to set the रेजिस्टर on.
 * @रेजिस्टर_address: the address of the रेजिस्टर to modअगरy.
 * @byte: the byte of the रेजिस्टर to modअगरy. Should be less than 3.
 * @mask: mask of the bits to modअगरy
 * @value: new values क्रम the bits in mask
 * Return: 0 अगर successful, otherwise a negative error code.
 */
अटल पूर्णांक hidpp10_set_रेजिस्टर(काष्ठा hidpp_device *hidpp_dev,
	u8 रेजिस्टर_address, u8 byte, u8 mask, u8 value)
अणु
	काष्ठा hidpp_report response;
	पूर्णांक ret;
	u8 params[3] = अणु 0 पूर्ण;

	ret = hidpp_send_rap_command_sync(hidpp_dev,
					  REPORT_ID_HIDPP_SHORT,
					  HIDPP_GET_REGISTER,
					  रेजिस्टर_address,
					  शून्य, 0, &response);
	अगर (ret)
		वापस ret;

	स_नकल(params, response.rap.params, 3);

	params[byte] &= ~mask;
	params[byte] |= value & mask;

	वापस hidpp_send_rap_command_sync(hidpp_dev,
					   REPORT_ID_HIDPP_SHORT,
					   HIDPP_SET_REGISTER,
					   रेजिस्टर_address,
					   params, 3, &response);
पूर्ण

#घोषणा HIDPP_REG_ENABLE_REPORTS			0x00
#घोषणा HIDPP_ENABLE_CONSUMER_REPORT			BIT(0)
#घोषणा HIDPP_ENABLE_WHEEL_REPORT			BIT(2)
#घोषणा HIDPP_ENABLE_MOUSE_EXTRA_BTN_REPORT		BIT(3)
#घोषणा HIDPP_ENABLE_BAT_REPORT				BIT(4)
#घोषणा HIDPP_ENABLE_HWHEEL_REPORT			BIT(5)

अटल पूर्णांक hidpp10_enable_battery_reporting(काष्ठा hidpp_device *hidpp_dev)
अणु
	वापस hidpp10_set_रेजिस्टर(hidpp_dev, HIDPP_REG_ENABLE_REPORTS, 0,
			  HIDPP_ENABLE_BAT_REPORT, HIDPP_ENABLE_BAT_REPORT);
पूर्ण

#घोषणा HIDPP_REG_FEATURES				0x01
#घोषणा HIDPP_ENABLE_SPECIAL_BUTTON_FUNC		BIT(1)
#घोषणा HIDPP_ENABLE_FAST_SCROLL			BIT(6)

/* On HID++ 1.0 devices, high-res scroll was called "scrolling acceleration". */
अटल पूर्णांक hidpp10_enable_scrolling_acceleration(काष्ठा hidpp_device *hidpp_dev)
अणु
	वापस hidpp10_set_रेजिस्टर(hidpp_dev, HIDPP_REG_FEATURES, 0,
			  HIDPP_ENABLE_FAST_SCROLL, HIDPP_ENABLE_FAST_SCROLL);
पूर्ण

#घोषणा HIDPP_REG_BATTERY_STATUS			0x07

अटल पूर्णांक hidpp10_battery_status_map_level(u8 param)
अणु
	पूर्णांक level;

	चयन (param) अणु
	हाल 1 ... 2:
		level = POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
		अवरोध;
	हाल 3 ... 4:
		level = POWER_SUPPLY_CAPACITY_LEVEL_LOW;
		अवरोध;
	हाल 5 ... 6:
		level = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
		अवरोध;
	हाल 7:
		level = POWER_SUPPLY_CAPACITY_LEVEL_HIGH;
		अवरोध;
	शेष:
		level = POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;
	पूर्ण

	वापस level;
पूर्ण

अटल पूर्णांक hidpp10_battery_status_map_status(u8 param)
अणु
	पूर्णांक status;

	चयन (param) अणु
	हाल 0x00:
		/* disअक्षरging (in use) */
		status = POWER_SUPPLY_STATUS_DISCHARGING;
		अवरोध;
	हाल 0x21: /* (standard) अक्षरging */
	हाल 0x24: /* fast अक्षरging */
	हाल 0x25: /* slow अक्षरging */
		status = POWER_SUPPLY_STATUS_CHARGING;
		अवरोध;
	हाल 0x26: /* topping अक्षरge */
	हाल 0x22: /* अक्षरge complete */
		status = POWER_SUPPLY_STATUS_FULL;
		अवरोध;
	हाल 0x20: /* unknown */
		status = POWER_SUPPLY_STATUS_UNKNOWN;
		अवरोध;
	/*
	 * 0x01...0x1F = reserved (not अक्षरging)
	 * 0x23 = अक्षरging error
	 * 0x27..0xff = reserved
	 */
	शेष:
		status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक hidpp10_query_battery_status(काष्ठा hidpp_device *hidpp)
अणु
	काष्ठा hidpp_report response;
	पूर्णांक ret, status;

	ret = hidpp_send_rap_command_sync(hidpp,
					REPORT_ID_HIDPP_SHORT,
					HIDPP_GET_REGISTER,
					HIDPP_REG_BATTERY_STATUS,
					शून्य, 0, &response);
	अगर (ret)
		वापस ret;

	hidpp->battery.level =
		hidpp10_battery_status_map_level(response.rap.params[0]);
	status = hidpp10_battery_status_map_status(response.rap.params[1]);
	hidpp->battery.status = status;
	/* the capacity is only available when disअक्षरging or full */
	hidpp->battery.online = status == POWER_SUPPLY_STATUS_DISCHARGING ||
				status == POWER_SUPPLY_STATUS_FULL;

	वापस 0;
पूर्ण

#घोषणा HIDPP_REG_BATTERY_MILEAGE			0x0D

अटल पूर्णांक hidpp10_battery_mileage_map_status(u8 param)
अणु
	पूर्णांक status;

	चयन (param >> 6) अणु
	हाल 0x00:
		/* disअक्षरging (in use) */
		status = POWER_SUPPLY_STATUS_DISCHARGING;
		अवरोध;
	हाल 0x01: /* अक्षरging */
		status = POWER_SUPPLY_STATUS_CHARGING;
		अवरोध;
	हाल 0x02: /* अक्षरge complete */
		status = POWER_SUPPLY_STATUS_FULL;
		अवरोध;
	/*
	 * 0x03 = अक्षरging error
	 */
	शेष:
		status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक hidpp10_query_battery_mileage(काष्ठा hidpp_device *hidpp)
अणु
	काष्ठा hidpp_report response;
	पूर्णांक ret, status;

	ret = hidpp_send_rap_command_sync(hidpp,
					REPORT_ID_HIDPP_SHORT,
					HIDPP_GET_REGISTER,
					HIDPP_REG_BATTERY_MILEAGE,
					शून्य, 0, &response);
	अगर (ret)
		वापस ret;

	hidpp->battery.capacity = response.rap.params[0];
	status = hidpp10_battery_mileage_map_status(response.rap.params[2]);
	hidpp->battery.status = status;
	/* the capacity is only available when disअक्षरging or full */
	hidpp->battery.online = status == POWER_SUPPLY_STATUS_DISCHARGING ||
				status == POWER_SUPPLY_STATUS_FULL;

	वापस 0;
पूर्ण

अटल पूर्णांक hidpp10_battery_event(काष्ठा hidpp_device *hidpp, u8 *data, पूर्णांक size)
अणु
	काष्ठा hidpp_report *report = (काष्ठा hidpp_report *)data;
	पूर्णांक status, capacity, level;
	bool changed;

	अगर (report->report_id != REPORT_ID_HIDPP_SHORT)
		वापस 0;

	चयन (report->rap.sub_id) अणु
	हाल HIDPP_REG_BATTERY_STATUS:
		capacity = hidpp->battery.capacity;
		level = hidpp10_battery_status_map_level(report->rawbytes[1]);
		status = hidpp10_battery_status_map_status(report->rawbytes[2]);
		अवरोध;
	हाल HIDPP_REG_BATTERY_MILEAGE:
		capacity = report->rap.params[0];
		level = hidpp->battery.level;
		status = hidpp10_battery_mileage_map_status(report->rawbytes[3]);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	changed = capacity != hidpp->battery.capacity ||
		  level != hidpp->battery.level ||
		  status != hidpp->battery.status;

	/* the capacity is only available when disअक्षरging or full */
	hidpp->battery.online = status == POWER_SUPPLY_STATUS_DISCHARGING ||
				status == POWER_SUPPLY_STATUS_FULL;

	अगर (changed) अणु
		hidpp->battery.level = level;
		hidpp->battery.status = status;
		अगर (hidpp->battery.ps)
			घातer_supply_changed(hidpp->battery.ps);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा HIDPP_REG_PAIRING_INFORMATION			0xB5
#घोषणा HIDPP_EXTENDED_PAIRING				0x30
#घोषणा HIDPP_DEVICE_NAME				0x40

अटल अक्षर *hidpp_unअगरying_get_name(काष्ठा hidpp_device *hidpp_dev)
अणु
	काष्ठा hidpp_report response;
	पूर्णांक ret;
	u8 params[1] = अणु HIDPP_DEVICE_NAME पूर्ण;
	अक्षर *name;
	पूर्णांक len;

	ret = hidpp_send_rap_command_sync(hidpp_dev,
					REPORT_ID_HIDPP_SHORT,
					HIDPP_GET_LONG_REGISTER,
					HIDPP_REG_PAIRING_INFORMATION,
					params, 1, &response);
	अगर (ret)
		वापस शून्य;

	len = response.rap.params[1];

	अगर (2 + len > माप(response.rap.params))
		वापस शून्य;

	अगर (len < 4) /* logitech devices are usually at least Xddd */
		वापस शून्य;

	name = kzalloc(len + 1, GFP_KERNEL);
	अगर (!name)
		वापस शून्य;

	स_नकल(name, &response.rap.params[2], len);

	/* include the terminating '\0' */
	hidpp_prefix_name(&name, len + 1);

	वापस name;
पूर्ण

अटल पूर्णांक hidpp_unअगरying_get_serial(काष्ठा hidpp_device *hidpp, u32 *serial)
अणु
	काष्ठा hidpp_report response;
	पूर्णांक ret;
	u8 params[1] = अणु HIDPP_EXTENDED_PAIRING पूर्ण;

	ret = hidpp_send_rap_command_sync(hidpp,
					REPORT_ID_HIDPP_SHORT,
					HIDPP_GET_LONG_REGISTER,
					HIDPP_REG_PAIRING_INFORMATION,
					params, 1, &response);
	अगर (ret)
		वापस ret;

	/*
	 * We करोn't care about LE or BE, we will output it as a string
	 * with %4phD, so we need to keep the order.
	 */
	*serial = *((u32 *)&response.rap.params[1]);
	वापस 0;
पूर्ण

अटल पूर्णांक hidpp_unअगरying_init(काष्ठा hidpp_device *hidpp)
अणु
	काष्ठा hid_device *hdev = hidpp->hid_dev;
	स्थिर अक्षर *name;
	u32 serial;
	पूर्णांक ret;

	ret = hidpp_unअगरying_get_serial(hidpp, &serial);
	अगर (ret)
		वापस ret;

	snम_लिखो(hdev->uniq, माप(hdev->uniq), "%04x-%4phD",
		 hdev->product, &serial);
	dbg_hid("HID++ Unifying: Got serial: %s\n", hdev->uniq);

	name = hidpp_unअगरying_get_name(hidpp);
	अगर (!name)
		वापस -EIO;

	snम_लिखो(hdev->name, माप(hdev->name), "%s", name);
	dbg_hid("HID++ Unifying: Got name: %s\n", name);

	kमुक्त(name);
	वापस 0;
पूर्ण

/* -------------------------------------------------------------------------- */
/* 0x0000: Root                                                               */
/* -------------------------------------------------------------------------- */

#घोषणा HIDPP_PAGE_ROOT					0x0000
#घोषणा HIDPP_PAGE_ROOT_IDX				0x00

#घोषणा CMD_ROOT_GET_FEATURE				0x01
#घोषणा CMD_ROOT_GET_PROTOCOL_VERSION			0x11

अटल पूर्णांक hidpp_root_get_feature(काष्ठा hidpp_device *hidpp, u16 feature,
	u8 *feature_index, u8 *feature_type)
अणु
	काष्ठा hidpp_report response;
	पूर्णांक ret;
	u8 params[2] = अणु feature >> 8, feature & 0x00FF पूर्ण;

	ret = hidpp_send_fap_command_sync(hidpp,
			HIDPP_PAGE_ROOT_IDX,
			CMD_ROOT_GET_FEATURE,
			params, 2, &response);
	अगर (ret)
		वापस ret;

	अगर (response.fap.params[0] == 0)
		वापस -ENOENT;

	*feature_index = response.fap.params[0];
	*feature_type = response.fap.params[1];

	वापस ret;
पूर्ण

अटल पूर्णांक hidpp_root_get_protocol_version(काष्ठा hidpp_device *hidpp)
अणु
	स्थिर u8 ping_byte = 0x5a;
	u8 ping_data[3] = अणु 0, 0, ping_byte पूर्ण;
	काष्ठा hidpp_report response;
	पूर्णांक ret;

	ret = hidpp_send_rap_command_sync(hidpp,
			REPORT_ID_HIDPP_SHORT,
			HIDPP_PAGE_ROOT_IDX,
			CMD_ROOT_GET_PROTOCOL_VERSION,
			ping_data, माप(ping_data), &response);

	अगर (ret == HIDPP_ERROR_INVALID_SUBID) अणु
		hidpp->protocol_major = 1;
		hidpp->protocol_minor = 0;
		जाओ prपूर्णांक_version;
	पूर्ण

	/* the device might not be connected */
	अगर (ret == HIDPP_ERROR_RESOURCE_ERROR)
		वापस -EIO;

	अगर (ret > 0) अणु
		hid_err(hidpp->hid_dev, "%s: received protocol error 0x%02x\n",
			__func__, ret);
		वापस -EPROTO;
	पूर्ण
	अगर (ret)
		वापस ret;

	अगर (response.rap.params[2] != ping_byte) अणु
		hid_err(hidpp->hid_dev, "%s: ping mismatch 0x%02x != 0x%02x\n",
			__func__, response.rap.params[2], ping_byte);
		वापस -EPROTO;
	पूर्ण

	hidpp->protocol_major = response.rap.params[0];
	hidpp->protocol_minor = response.rap.params[1];

prपूर्णांक_version:
	hid_info(hidpp->hid_dev, "HID++ %u.%u device connected.\n",
		 hidpp->protocol_major, hidpp->protocol_minor);
	वापस 0;
पूर्ण

/* -------------------------------------------------------------------------- */
/* 0x0005: GetDeviceNameType                                                  */
/* -------------------------------------------------------------------------- */

#घोषणा HIDPP_PAGE_GET_DEVICE_NAME_TYPE			0x0005

#घोषणा CMD_GET_DEVICE_NAME_TYPE_GET_COUNT		0x01
#घोषणा CMD_GET_DEVICE_NAME_TYPE_GET_DEVICE_NAME	0x11
#घोषणा CMD_GET_DEVICE_NAME_TYPE_GET_TYPE		0x21

अटल पूर्णांक hidpp_devicenametype_get_count(काष्ठा hidpp_device *hidpp,
	u8 feature_index, u8 *nameLength)
अणु
	काष्ठा hidpp_report response;
	पूर्णांक ret;

	ret = hidpp_send_fap_command_sync(hidpp, feature_index,
		CMD_GET_DEVICE_NAME_TYPE_GET_COUNT, शून्य, 0, &response);

	अगर (ret > 0) अणु
		hid_err(hidpp->hid_dev, "%s: received protocol error 0x%02x\n",
			__func__, ret);
		वापस -EPROTO;
	पूर्ण
	अगर (ret)
		वापस ret;

	*nameLength = response.fap.params[0];

	वापस ret;
पूर्ण

अटल पूर्णांक hidpp_devicenametype_get_device_name(काष्ठा hidpp_device *hidpp,
	u8 feature_index, u8 अक्षर_index, अक्षर *device_name, पूर्णांक len_buf)
अणु
	काष्ठा hidpp_report response;
	पूर्णांक ret, i;
	पूर्णांक count;

	ret = hidpp_send_fap_command_sync(hidpp, feature_index,
		CMD_GET_DEVICE_NAME_TYPE_GET_DEVICE_NAME, &अक्षर_index, 1,
		&response);

	अगर (ret > 0) अणु
		hid_err(hidpp->hid_dev, "%s: received protocol error 0x%02x\n",
			__func__, ret);
		वापस -EPROTO;
	पूर्ण
	अगर (ret)
		वापस ret;

	चयन (response.report_id) अणु
	हाल REPORT_ID_HIDPP_VERY_LONG:
		count = hidpp->very_दीर्घ_report_length - 4;
		अवरोध;
	हाल REPORT_ID_HIDPP_LONG:
		count = HIDPP_REPORT_LONG_LENGTH - 4;
		अवरोध;
	हाल REPORT_ID_HIDPP_SHORT:
		count = HIDPP_REPORT_SHORT_LENGTH - 4;
		अवरोध;
	शेष:
		वापस -EPROTO;
	पूर्ण

	अगर (len_buf < count)
		count = len_buf;

	क्रम (i = 0; i < count; i++)
		device_name[i] = response.fap.params[i];

	वापस count;
पूर्ण

अटल अक्षर *hidpp_get_device_name(काष्ठा hidpp_device *hidpp)
अणु
	u8 feature_type;
	u8 feature_index;
	u8 __name_length;
	अक्षर *name;
	अचिन्हित index = 0;
	पूर्णांक ret;

	ret = hidpp_root_get_feature(hidpp, HIDPP_PAGE_GET_DEVICE_NAME_TYPE,
		&feature_index, &feature_type);
	अगर (ret)
		वापस शून्य;

	ret = hidpp_devicenametype_get_count(hidpp, feature_index,
		&__name_length);
	अगर (ret)
		वापस शून्य;

	name = kzalloc(__name_length + 1, GFP_KERNEL);
	अगर (!name)
		वापस शून्य;

	जबतक (index < __name_length) अणु
		ret = hidpp_devicenametype_get_device_name(hidpp,
			feature_index, index, name + index,
			__name_length - index);
		अगर (ret <= 0) अणु
			kमुक्त(name);
			वापस शून्य;
		पूर्ण
		index += ret;
	पूर्ण

	/* include the terminating '\0' */
	hidpp_prefix_name(&name, __name_length + 1);

	वापस name;
पूर्ण

/* -------------------------------------------------------------------------- */
/* 0x1000: Battery level status                                               */
/* -------------------------------------------------------------------------- */

#घोषणा HIDPP_PAGE_BATTERY_LEVEL_STATUS				0x1000

#घोषणा CMD_BATTERY_LEVEL_STATUS_GET_BATTERY_LEVEL_STATUS	0x00
#घोषणा CMD_BATTERY_LEVEL_STATUS_GET_BATTERY_CAPABILITY		0x10

#घोषणा EVENT_BATTERY_LEVEL_STATUS_BROADCAST			0x00

#घोषणा FLAG_BATTERY_LEVEL_DISABLE_OSD				BIT(0)
#घोषणा FLAG_BATTERY_LEVEL_MILEAGE				BIT(1)
#घोषणा FLAG_BATTERY_LEVEL_RECHARGEABLE				BIT(2)

अटल पूर्णांक hidpp_map_battery_level(पूर्णांक capacity)
अणु
	अगर (capacity < 11)
		वापस POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
	/*
	 * The spec says this should be < 31 but some devices report 30
	 * with bअक्रम new batteries and Winकरोws reports 30 as "Good".
	 */
	अन्यथा अगर (capacity < 30)
		वापस POWER_SUPPLY_CAPACITY_LEVEL_LOW;
	अन्यथा अगर (capacity < 81)
		वापस POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
	वापस POWER_SUPPLY_CAPACITY_LEVEL_FULL;
पूर्ण

अटल पूर्णांक hidpp20_batterylevel_map_status_capacity(u8 data[3], पूर्णांक *capacity,
						    पूर्णांक *next_capacity,
						    पूर्णांक *level)
अणु
	पूर्णांक status;

	*capacity = data[0];
	*next_capacity = data[1];
	*level = POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;

	/* When disअक्षरging, we can rely on the device reported capacity.
	 * For all other states the device reports 0 (unknown).
	 */
	चयन (data[2]) अणु
		हाल 0: /* disअक्षरging (in use) */
			status = POWER_SUPPLY_STATUS_DISCHARGING;
			*level = hidpp_map_battery_level(*capacity);
			अवरोध;
		हाल 1: /* reअक्षरging */
			status = POWER_SUPPLY_STATUS_CHARGING;
			अवरोध;
		हाल 2: /* अक्षरge in final stage */
			status = POWER_SUPPLY_STATUS_CHARGING;
			अवरोध;
		हाल 3: /* अक्षरge complete */
			status = POWER_SUPPLY_STATUS_FULL;
			*level = POWER_SUPPLY_CAPACITY_LEVEL_FULL;
			*capacity = 100;
			अवरोध;
		हाल 4: /* reअक्षरging below optimal speed */
			status = POWER_SUPPLY_STATUS_CHARGING;
			अवरोध;
		/* 5 = invalid battery type
		   6 = thermal error
		   7 = other अक्षरging error */
		शेष:
			status = POWER_SUPPLY_STATUS_NOT_CHARGING;
			अवरोध;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक hidpp20_batterylevel_get_battery_capacity(काष्ठा hidpp_device *hidpp,
						     u8 feature_index,
						     पूर्णांक *status,
						     पूर्णांक *capacity,
						     पूर्णांक *next_capacity,
						     पूर्णांक *level)
अणु
	काष्ठा hidpp_report response;
	पूर्णांक ret;
	u8 *params = (u8 *)response.fap.params;

	ret = hidpp_send_fap_command_sync(hidpp, feature_index,
					  CMD_BATTERY_LEVEL_STATUS_GET_BATTERY_LEVEL_STATUS,
					  शून्य, 0, &response);
	/* Ignore these पूर्णांकermittent errors */
	अगर (ret == HIDPP_ERROR_RESOURCE_ERROR)
		वापस -EIO;
	अगर (ret > 0) अणु
		hid_err(hidpp->hid_dev, "%s: received protocol error 0x%02x\n",
			__func__, ret);
		वापस -EPROTO;
	पूर्ण
	अगर (ret)
		वापस ret;

	*status = hidpp20_batterylevel_map_status_capacity(params, capacity,
							   next_capacity,
							   level);

	वापस 0;
पूर्ण

अटल पूर्णांक hidpp20_batterylevel_get_battery_info(काष्ठा hidpp_device *hidpp,
						  u8 feature_index)
अणु
	काष्ठा hidpp_report response;
	पूर्णांक ret;
	u8 *params = (u8 *)response.fap.params;
	अचिन्हित पूर्णांक level_count, flags;

	ret = hidpp_send_fap_command_sync(hidpp, feature_index,
					  CMD_BATTERY_LEVEL_STATUS_GET_BATTERY_CAPABILITY,
					  शून्य, 0, &response);
	अगर (ret > 0) अणु
		hid_err(hidpp->hid_dev, "%s: received protocol error 0x%02x\n",
			__func__, ret);
		वापस -EPROTO;
	पूर्ण
	अगर (ret)
		वापस ret;

	level_count = params[0];
	flags = params[1];

	अगर (level_count < 10 || !(flags & FLAG_BATTERY_LEVEL_MILEAGE))
		hidpp->capabilities |= HIDPP_CAPABILITY_BATTERY_LEVEL_STATUS;
	अन्यथा
		hidpp->capabilities |= HIDPP_CAPABILITY_BATTERY_MILEAGE;

	वापस 0;
पूर्ण

अटल पूर्णांक hidpp20_query_battery_info_1000(काष्ठा hidpp_device *hidpp)
अणु
	u8 feature_type;
	पूर्णांक ret;
	पूर्णांक status, capacity, next_capacity, level;

	अगर (hidpp->battery.feature_index == 0xff) अणु
		ret = hidpp_root_get_feature(hidpp,
					     HIDPP_PAGE_BATTERY_LEVEL_STATUS,
					     &hidpp->battery.feature_index,
					     &feature_type);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = hidpp20_batterylevel_get_battery_capacity(hidpp,
						hidpp->battery.feature_index,
						&status, &capacity,
						&next_capacity, &level);
	अगर (ret)
		वापस ret;

	ret = hidpp20_batterylevel_get_battery_info(hidpp,
						hidpp->battery.feature_index);
	अगर (ret)
		वापस ret;

	hidpp->battery.status = status;
	hidpp->battery.capacity = capacity;
	hidpp->battery.level = level;
	/* the capacity is only available when disअक्षरging or full */
	hidpp->battery.online = status == POWER_SUPPLY_STATUS_DISCHARGING ||
				status == POWER_SUPPLY_STATUS_FULL;

	वापस 0;
पूर्ण

अटल पूर्णांक hidpp20_battery_event_1000(काष्ठा hidpp_device *hidpp,
				 u8 *data, पूर्णांक size)
अणु
	काष्ठा hidpp_report *report = (काष्ठा hidpp_report *)data;
	पूर्णांक status, capacity, next_capacity, level;
	bool changed;

	अगर (report->fap.feature_index != hidpp->battery.feature_index ||
	    report->fap.funcindex_clientid != EVENT_BATTERY_LEVEL_STATUS_BROADCAST)
		वापस 0;

	status = hidpp20_batterylevel_map_status_capacity(report->fap.params,
							  &capacity,
							  &next_capacity,
							  &level);

	/* the capacity is only available when disअक्षरging or full */
	hidpp->battery.online = status == POWER_SUPPLY_STATUS_DISCHARGING ||
				status == POWER_SUPPLY_STATUS_FULL;

	changed = capacity != hidpp->battery.capacity ||
		  level != hidpp->battery.level ||
		  status != hidpp->battery.status;

	अगर (changed) अणु
		hidpp->battery.level = level;
		hidpp->battery.capacity = capacity;
		hidpp->battery.status = status;
		अगर (hidpp->battery.ps)
			घातer_supply_changed(hidpp->battery.ps);
	पूर्ण

	वापस 0;
पूर्ण

/* -------------------------------------------------------------------------- */
/* 0x1001: Battery voltage                                                    */
/* -------------------------------------------------------------------------- */

#घोषणा HIDPP_PAGE_BATTERY_VOLTAGE 0x1001

#घोषणा CMD_BATTERY_VOLTAGE_GET_BATTERY_VOLTAGE 0x00

#घोषणा EVENT_BATTERY_VOLTAGE_STATUS_BROADCAST 0x00

अटल पूर्णांक hidpp20_battery_map_status_voltage(u8 data[3], पूर्णांक *voltage,
						पूर्णांक *level, पूर्णांक *अक्षरge_type)
अणु
	पूर्णांक status;

	दीर्घ flags = (दीर्घ) data[2];
	*level = POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;

	अगर (flags & 0x80)
		चयन (flags & 0x07) अणु
		हाल 0:
			status = POWER_SUPPLY_STATUS_CHARGING;
			अवरोध;
		हाल 1:
			status = POWER_SUPPLY_STATUS_FULL;
			*level = POWER_SUPPLY_CAPACITY_LEVEL_FULL;
			अवरोध;
		हाल 2:
			status = POWER_SUPPLY_STATUS_NOT_CHARGING;
			अवरोध;
		शेष:
			status = POWER_SUPPLY_STATUS_UNKNOWN;
			अवरोध;
		पूर्ण
	अन्यथा
		status = POWER_SUPPLY_STATUS_DISCHARGING;

	*अक्षरge_type = POWER_SUPPLY_CHARGE_TYPE_STANDARD;
	अगर (test_bit(3, &flags)) अणु
		*अक्षरge_type = POWER_SUPPLY_CHARGE_TYPE_FAST;
	पूर्ण
	अगर (test_bit(4, &flags)) अणु
		*अक्षरge_type = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
	पूर्ण
	अगर (test_bit(5, &flags)) अणु
		*level = POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
	पूर्ण

	*voltage = get_unaligned_be16(data);

	वापस status;
पूर्ण

अटल पूर्णांक hidpp20_battery_get_battery_voltage(काष्ठा hidpp_device *hidpp,
						 u8 feature_index,
						 पूर्णांक *status, पूर्णांक *voltage,
						 पूर्णांक *level, पूर्णांक *अक्षरge_type)
अणु
	काष्ठा hidpp_report response;
	पूर्णांक ret;
	u8 *params = (u8 *)response.fap.params;

	ret = hidpp_send_fap_command_sync(hidpp, feature_index,
					  CMD_BATTERY_VOLTAGE_GET_BATTERY_VOLTAGE,
					  शून्य, 0, &response);

	अगर (ret > 0) अणु
		hid_err(hidpp->hid_dev, "%s: received protocol error 0x%02x\n",
			__func__, ret);
		वापस -EPROTO;
	पूर्ण
	अगर (ret)
		वापस ret;

	hidpp->capabilities |= HIDPP_CAPABILITY_BATTERY_VOLTAGE;

	*status = hidpp20_battery_map_status_voltage(params, voltage,
						     level, अक्षरge_type);

	वापस 0;
पूर्ण

अटल पूर्णांक hidpp20_query_battery_voltage_info(काष्ठा hidpp_device *hidpp)
अणु
	u8 feature_type;
	पूर्णांक ret;
	पूर्णांक status, voltage, level, अक्षरge_type;

	अगर (hidpp->battery.voltage_feature_index == 0xff) अणु
		ret = hidpp_root_get_feature(hidpp, HIDPP_PAGE_BATTERY_VOLTAGE,
					     &hidpp->battery.voltage_feature_index,
					     &feature_type);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = hidpp20_battery_get_battery_voltage(hidpp,
						  hidpp->battery.voltage_feature_index,
						  &status, &voltage, &level, &अक्षरge_type);

	अगर (ret)
		वापस ret;

	hidpp->battery.status = status;
	hidpp->battery.voltage = voltage;
	hidpp->battery.level = level;
	hidpp->battery.अक्षरge_type = अक्षरge_type;
	hidpp->battery.online = status != POWER_SUPPLY_STATUS_NOT_CHARGING;

	वापस 0;
पूर्ण

अटल पूर्णांक hidpp20_battery_voltage_event(काष्ठा hidpp_device *hidpp,
					    u8 *data, पूर्णांक size)
अणु
	काष्ठा hidpp_report *report = (काष्ठा hidpp_report *)data;
	पूर्णांक status, voltage, level, अक्षरge_type;

	अगर (report->fap.feature_index != hidpp->battery.voltage_feature_index ||
		report->fap.funcindex_clientid != EVENT_BATTERY_VOLTAGE_STATUS_BROADCAST)
		वापस 0;

	status = hidpp20_battery_map_status_voltage(report->fap.params, &voltage,
						    &level, &अक्षरge_type);

	hidpp->battery.online = status != POWER_SUPPLY_STATUS_NOT_CHARGING;

	अगर (voltage != hidpp->battery.voltage || status != hidpp->battery.status) अणु
		hidpp->battery.voltage = voltage;
		hidpp->battery.status = status;
		hidpp->battery.level = level;
		hidpp->battery.अक्षरge_type = अक्षरge_type;
		अगर (hidpp->battery.ps)
			घातer_supply_changed(hidpp->battery.ps);
	पूर्ण
	वापस 0;
पूर्ण

/* -------------------------------------------------------------------------- */
/* 0x1004: Unअगरied battery                                                    */
/* -------------------------------------------------------------------------- */

#घोषणा HIDPP_PAGE_UNIFIED_BATTERY				0x1004

#घोषणा CMD_UNIFIED_BATTERY_GET_CAPABILITIES			0x00
#घोषणा CMD_UNIFIED_BATTERY_GET_STATUS				0x10

#घोषणा EVENT_UNIFIED_BATTERY_STATUS_EVENT			0x00

#घोषणा FLAG_UNIFIED_BATTERY_LEVEL_CRITICAL			BIT(0)
#घोषणा FLAG_UNIFIED_BATTERY_LEVEL_LOW				BIT(1)
#घोषणा FLAG_UNIFIED_BATTERY_LEVEL_GOOD				BIT(2)
#घोषणा FLAG_UNIFIED_BATTERY_LEVEL_FULL				BIT(3)

#घोषणा FLAG_UNIFIED_BATTERY_FLAGS_RECHARGEABLE			BIT(0)
#घोषणा FLAG_UNIFIED_BATTERY_FLAGS_STATE_OF_CHARGE		BIT(1)

अटल पूर्णांक hidpp20_unअगरiedbattery_get_capabilities(काष्ठा hidpp_device *hidpp,
						   u8 feature_index)
अणु
	काष्ठा hidpp_report response;
	पूर्णांक ret;
	u8 *params = (u8 *)response.fap.params;

	अगर (hidpp->capabilities & HIDPP_CAPABILITY_BATTERY_LEVEL_STATUS ||
	    hidpp->capabilities & HIDPP_CAPABILITY_BATTERY_PERCENTAGE) अणु
		/* we have alपढ़ोy set the device capabilities, so let's skip */
		वापस 0;
	पूर्ण

	ret = hidpp_send_fap_command_sync(hidpp, feature_index,
					  CMD_UNIFIED_BATTERY_GET_CAPABILITIES,
					  शून्य, 0, &response);
	/* Ignore these पूर्णांकermittent errors */
	अगर (ret == HIDPP_ERROR_RESOURCE_ERROR)
		वापस -EIO;
	अगर (ret > 0) अणु
		hid_err(hidpp->hid_dev, "%s: received protocol error 0x%02x\n",
			__func__, ret);
		वापस -EPROTO;
	पूर्ण
	अगर (ret)
		वापस ret;

	/*
	 * If the device supports state of अक्षरge (battery percentage) we won't
	 * export the battery level inक्रमmation. there are 4 possible battery
	 * levels and they all are optional, this means that the device might
	 * not support any of them, we are just better off with the battery
	 * percentage.
	 */
	अगर (params[1] & FLAG_UNIFIED_BATTERY_FLAGS_STATE_OF_CHARGE) अणु
		hidpp->capabilities |= HIDPP_CAPABILITY_BATTERY_PERCENTAGE;
		hidpp->battery.supported_levels_1004 = 0;
	पूर्ण अन्यथा अणु
		hidpp->capabilities |= HIDPP_CAPABILITY_BATTERY_LEVEL_STATUS;
		hidpp->battery.supported_levels_1004 = params[0];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hidpp20_unअगरiedbattery_map_status(काष्ठा hidpp_device *hidpp,
					     u8 अक्षरging_status,
					     u8 बाह्यal_घातer_status)
अणु
	पूर्णांक status;

	चयन (अक्षरging_status) अणु
		हाल 0: /* disअक्षरging */
			status = POWER_SUPPLY_STATUS_DISCHARGING;
			अवरोध;
		हाल 1: /* अक्षरging */
		हाल 2: /* अक्षरging slow */
			status = POWER_SUPPLY_STATUS_CHARGING;
			अवरोध;
		हाल 3: /* complete */
			status = POWER_SUPPLY_STATUS_FULL;
			अवरोध;
		हाल 4: /* error */
			status = POWER_SUPPLY_STATUS_NOT_CHARGING;
			hid_info(hidpp->hid_dev, "%s: charging error",
				 hidpp->name);
			अवरोध;
		शेष:
			status = POWER_SUPPLY_STATUS_NOT_CHARGING;
			अवरोध;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक hidpp20_unअगरiedbattery_map_level(काष्ठा hidpp_device *hidpp,
					    u8 battery_level)
अणु
	/* cler unsupported level bits */
	battery_level &= hidpp->battery.supported_levels_1004;

	अगर (battery_level & FLAG_UNIFIED_BATTERY_LEVEL_FULL)
		वापस POWER_SUPPLY_CAPACITY_LEVEL_FULL;
	अन्यथा अगर (battery_level & FLAG_UNIFIED_BATTERY_LEVEL_GOOD)
		वापस POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
	अन्यथा अगर (battery_level & FLAG_UNIFIED_BATTERY_LEVEL_LOW)
		वापस POWER_SUPPLY_CAPACITY_LEVEL_LOW;
	अन्यथा अगर (battery_level & FLAG_UNIFIED_BATTERY_LEVEL_CRITICAL)
		वापस POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;

	वापस POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;
पूर्ण

अटल पूर्णांक hidpp20_unअगरiedbattery_get_status(काष्ठा hidpp_device *hidpp,
					     u8 feature_index,
					     u8 *state_of_अक्षरge,
					     पूर्णांक *status,
					     पूर्णांक *level)
अणु
	काष्ठा hidpp_report response;
	पूर्णांक ret;
	u8 *params = (u8 *)response.fap.params;

	ret = hidpp_send_fap_command_sync(hidpp, feature_index,
					  CMD_UNIFIED_BATTERY_GET_STATUS,
					  शून्य, 0, &response);
	/* Ignore these पूर्णांकermittent errors */
	अगर (ret == HIDPP_ERROR_RESOURCE_ERROR)
		वापस -EIO;
	अगर (ret > 0) अणु
		hid_err(hidpp->hid_dev, "%s: received protocol error 0x%02x\n",
			__func__, ret);
		वापस -EPROTO;
	पूर्ण
	अगर (ret)
		वापस ret;

	*state_of_अक्षरge = params[0];
	*status = hidpp20_unअगरiedbattery_map_status(hidpp, params[2], params[3]);
	*level = hidpp20_unअगरiedbattery_map_level(hidpp, params[1]);

	वापस 0;
पूर्ण

अटल पूर्णांक hidpp20_query_battery_info_1004(काष्ठा hidpp_device *hidpp)
अणु
	u8 feature_type;
	पूर्णांक ret;
	u8 state_of_अक्षरge;
	पूर्णांक status, level;

	अगर (hidpp->battery.feature_index == 0xff) अणु
		ret = hidpp_root_get_feature(hidpp,
					     HIDPP_PAGE_UNIFIED_BATTERY,
					     &hidpp->battery.feature_index,
					     &feature_type);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = hidpp20_unअगरiedbattery_get_capabilities(hidpp,
					hidpp->battery.feature_index);
	अगर (ret)
		वापस ret;

	ret = hidpp20_unअगरiedbattery_get_status(hidpp,
						hidpp->battery.feature_index,
						&state_of_अक्षरge,
						&status,
						&level);
	अगर (ret)
		वापस ret;

	hidpp->capabilities |= HIDPP_CAPABILITY_UNIFIED_BATTERY;
	hidpp->battery.capacity = state_of_अक्षरge;
	hidpp->battery.status = status;
	hidpp->battery.level = level;
	hidpp->battery.online = true;

	वापस 0;
पूर्ण

अटल पूर्णांक hidpp20_battery_event_1004(काष्ठा hidpp_device *hidpp,
				 u8 *data, पूर्णांक size)
अणु
	काष्ठा hidpp_report *report = (काष्ठा hidpp_report *)data;
	u8 *params = (u8 *)report->fap.params;
	पूर्णांक state_of_अक्षरge, status, level;
	bool changed;

	अगर (report->fap.feature_index != hidpp->battery.feature_index ||
	    report->fap.funcindex_clientid != EVENT_UNIFIED_BATTERY_STATUS_EVENT)
		वापस 0;

	state_of_अक्षरge = params[0];
	status = hidpp20_unअगरiedbattery_map_status(hidpp, params[2], params[3]);
	level = hidpp20_unअगरiedbattery_map_level(hidpp, params[1]);

	changed = status != hidpp->battery.status ||
		  (state_of_अक्षरge != hidpp->battery.capacity &&
		   hidpp->capabilities & HIDPP_CAPABILITY_BATTERY_PERCENTAGE) ||
		  (level != hidpp->battery.level &&
		   hidpp->capabilities & HIDPP_CAPABILITY_BATTERY_LEVEL_STATUS);

	अगर (changed) अणु
		hidpp->battery.capacity = state_of_अक्षरge;
		hidpp->battery.status = status;
		hidpp->battery.level = level;
		अगर (hidpp->battery.ps)
			घातer_supply_changed(hidpp->battery.ps);
	पूर्ण

	वापस 0;
पूर्ण

/* -------------------------------------------------------------------------- */
/* Battery feature helpers                                                    */
/* -------------------------------------------------------------------------- */

अटल क्रमागत घातer_supply_property hidpp_battery_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_SCOPE,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_SERIAL_NUMBER,
	0, /* placeholder क्रम POWER_SUPPLY_PROP_CAPACITY, */
	0, /* placeholder क्रम POWER_SUPPLY_PROP_CAPACITY_LEVEL, */
	0, /* placeholder क्रम POWER_SUPPLY_PROP_VOLTAGE_NOW, */
पूर्ण;

अटल पूर्णांक hidpp_battery_get_property(काष्ठा घातer_supply *psy,
				      क्रमागत घातer_supply_property psp,
				      जोड़ घातer_supply_propval *val)
अणु
	काष्ठा hidpp_device *hidpp = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;

	चयन(psp) अणु
		हाल POWER_SUPPLY_PROP_STATUS:
			val->पूर्णांकval = hidpp->battery.status;
			अवरोध;
		हाल POWER_SUPPLY_PROP_CAPACITY:
			val->पूर्णांकval = hidpp->battery.capacity;
			अवरोध;
		हाल POWER_SUPPLY_PROP_CAPACITY_LEVEL:
			val->पूर्णांकval = hidpp->battery.level;
			अवरोध;
		हाल POWER_SUPPLY_PROP_SCOPE:
			val->पूर्णांकval = POWER_SUPPLY_SCOPE_DEVICE;
			अवरोध;
		हाल POWER_SUPPLY_PROP_ONLINE:
			val->पूर्णांकval = hidpp->battery.online;
			अवरोध;
		हाल POWER_SUPPLY_PROP_MODEL_NAME:
			अगर (!म_भेदन(hidpp->name, "Logitech ", 9))
				val->strval = hidpp->name + 9;
			अन्यथा
				val->strval = hidpp->name;
			अवरोध;
		हाल POWER_SUPPLY_PROP_MANUFACTURER:
			val->strval = "Logitech";
			अवरोध;
		हाल POWER_SUPPLY_PROP_SERIAL_NUMBER:
			val->strval = hidpp->hid_dev->uniq;
			अवरोध;
		हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
			/* hardware reports voltage in in mV. sysfs expects uV */
			val->पूर्णांकval = hidpp->battery.voltage * 1000;
			अवरोध;
		हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
			val->पूर्णांकval = hidpp->battery.अक्षरge_type;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* -------------------------------------------------------------------------- */
/* 0x1d4b: Wireless device status                                             */
/* -------------------------------------------------------------------------- */
#घोषणा HIDPP_PAGE_WIRELESS_DEVICE_STATUS			0x1d4b

अटल पूर्णांक hidpp_set_wireless_feature_index(काष्ठा hidpp_device *hidpp)
अणु
	u8 feature_type;
	पूर्णांक ret;

	ret = hidpp_root_get_feature(hidpp,
				     HIDPP_PAGE_WIRELESS_DEVICE_STATUS,
				     &hidpp->wireless_feature_index,
				     &feature_type);

	वापस ret;
पूर्ण

/* -------------------------------------------------------------------------- */
/* 0x2120: Hi-resolution scrolling                                            */
/* -------------------------------------------------------------------------- */

#घोषणा HIDPP_PAGE_HI_RESOLUTION_SCROLLING			0x2120

#घोषणा CMD_HI_RESOLUTION_SCROLLING_SET_HIGHRES_SCROLLING_MODE	0x10

अटल पूर्णांक hidpp_hrs_set_highres_scrolling_mode(काष्ठा hidpp_device *hidpp,
	bool enabled, u8 *multiplier)
अणु
	u8 feature_index;
	u8 feature_type;
	पूर्णांक ret;
	u8 params[1];
	काष्ठा hidpp_report response;

	ret = hidpp_root_get_feature(hidpp,
				     HIDPP_PAGE_HI_RESOLUTION_SCROLLING,
				     &feature_index,
				     &feature_type);
	अगर (ret)
		वापस ret;

	params[0] = enabled ? BIT(0) : 0;
	ret = hidpp_send_fap_command_sync(hidpp, feature_index,
					  CMD_HI_RESOLUTION_SCROLLING_SET_HIGHRES_SCROLLING_MODE,
					  params, माप(params), &response);
	अगर (ret)
		वापस ret;
	*multiplier = response.fap.params[1];
	वापस 0;
पूर्ण

/* -------------------------------------------------------------------------- */
/* 0x2121: HiRes Wheel                                                        */
/* -------------------------------------------------------------------------- */

#घोषणा HIDPP_PAGE_HIRES_WHEEL		0x2121

#घोषणा CMD_HIRES_WHEEL_GET_WHEEL_CAPABILITY	0x00
#घोषणा CMD_HIRES_WHEEL_SET_WHEEL_MODE		0x20

अटल पूर्णांक hidpp_hrw_get_wheel_capability(काष्ठा hidpp_device *hidpp,
	u8 *multiplier)
अणु
	u8 feature_index;
	u8 feature_type;
	पूर्णांक ret;
	काष्ठा hidpp_report response;

	ret = hidpp_root_get_feature(hidpp, HIDPP_PAGE_HIRES_WHEEL,
				     &feature_index, &feature_type);
	अगर (ret)
		जाओ वापस_शेष;

	ret = hidpp_send_fap_command_sync(hidpp, feature_index,
					  CMD_HIRES_WHEEL_GET_WHEEL_CAPABILITY,
					  शून्य, 0, &response);
	अगर (ret)
		जाओ वापस_शेष;

	*multiplier = response.fap.params[0];
	वापस 0;
वापस_शेष:
	hid_warn(hidpp->hid_dev,
		 "Couldn't get wheel multiplier (error %d)\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hidpp_hrw_set_wheel_mode(काष्ठा hidpp_device *hidpp, bool invert,
	bool high_resolution, bool use_hidpp)
अणु
	u8 feature_index;
	u8 feature_type;
	पूर्णांक ret;
	u8 params[1];
	काष्ठा hidpp_report response;

	ret = hidpp_root_get_feature(hidpp, HIDPP_PAGE_HIRES_WHEEL,
				     &feature_index, &feature_type);
	अगर (ret)
		वापस ret;

	params[0] = (invert          ? BIT(2) : 0) |
		    (high_resolution ? BIT(1) : 0) |
		    (use_hidpp       ? BIT(0) : 0);

	वापस hidpp_send_fap_command_sync(hidpp, feature_index,
					   CMD_HIRES_WHEEL_SET_WHEEL_MODE,
					   params, माप(params), &response);
पूर्ण

/* -------------------------------------------------------------------------- */
/* 0x4301: Solar Keyboard                                                     */
/* -------------------------------------------------------------------------- */

#घोषणा HIDPP_PAGE_SOLAR_KEYBOARD			0x4301

#घोषणा CMD_SOLAR_SET_LIGHT_MEASURE			0x00

#घोषणा EVENT_SOLAR_BATTERY_BROADCAST			0x00
#घोषणा EVENT_SOLAR_BATTERY_LIGHT_MEASURE		0x10
#घोषणा EVENT_SOLAR_CHECK_LIGHT_BUTTON			0x20

अटल पूर्णांक hidpp_solar_request_battery_event(काष्ठा hidpp_device *hidpp)
अणु
	काष्ठा hidpp_report response;
	u8 params[2] = अणु 1, 1 पूर्ण;
	u8 feature_type;
	पूर्णांक ret;

	अगर (hidpp->battery.feature_index == 0xff) अणु
		ret = hidpp_root_get_feature(hidpp,
					     HIDPP_PAGE_SOLAR_KEYBOARD,
					     &hidpp->battery.solar_feature_index,
					     &feature_type);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = hidpp_send_fap_command_sync(hidpp,
					  hidpp->battery.solar_feature_index,
					  CMD_SOLAR_SET_LIGHT_MEASURE,
					  params, 2, &response);
	अगर (ret > 0) अणु
		hid_err(hidpp->hid_dev, "%s: received protocol error 0x%02x\n",
			__func__, ret);
		वापस -EPROTO;
	पूर्ण
	अगर (ret)
		वापस ret;

	hidpp->capabilities |= HIDPP_CAPABILITY_BATTERY_MILEAGE;

	वापस 0;
पूर्ण

अटल पूर्णांक hidpp_solar_battery_event(काष्ठा hidpp_device *hidpp,
				     u8 *data, पूर्णांक size)
अणु
	काष्ठा hidpp_report *report = (काष्ठा hidpp_report *)data;
	पूर्णांक capacity, lux, status;
	u8 function;

	function = report->fap.funcindex_clientid;


	अगर (report->fap.feature_index != hidpp->battery.solar_feature_index ||
	    !(function == EVENT_SOLAR_BATTERY_BROADCAST ||
	      function == EVENT_SOLAR_BATTERY_LIGHT_MEASURE ||
	      function == EVENT_SOLAR_CHECK_LIGHT_BUTTON))
		वापस 0;

	capacity = report->fap.params[0];

	चयन (function) अणु
	हाल EVENT_SOLAR_BATTERY_LIGHT_MEASURE:
		lux = (report->fap.params[1] << 8) | report->fap.params[2];
		अगर (lux > 200)
			status = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा
			status = POWER_SUPPLY_STATUS_DISCHARGING;
		अवरोध;
	हाल EVENT_SOLAR_CHECK_LIGHT_BUTTON:
	शेष:
		अगर (capacity < hidpp->battery.capacity)
			status = POWER_SUPPLY_STATUS_DISCHARGING;
		अन्यथा
			status = POWER_SUPPLY_STATUS_CHARGING;

	पूर्ण

	अगर (capacity == 100)
		status = POWER_SUPPLY_STATUS_FULL;

	hidpp->battery.online = true;
	अगर (capacity != hidpp->battery.capacity ||
	    status != hidpp->battery.status) अणु
		hidpp->battery.capacity = capacity;
		hidpp->battery.status = status;
		अगर (hidpp->battery.ps)
			घातer_supply_changed(hidpp->battery.ps);
	पूर्ण

	वापस 0;
पूर्ण

/* -------------------------------------------------------------------------- */
/* 0x6010: Touchpad FW items                                                  */
/* -------------------------------------------------------------------------- */

#घोषणा HIDPP_PAGE_TOUCHPAD_FW_ITEMS			0x6010

#घोषणा CMD_TOUCHPAD_FW_ITEMS_SET			0x10

काष्ठा hidpp_touchpad_fw_items अणु
	uपूर्णांक8_t presence;
	uपूर्णांक8_t desired_state;
	uपूर्णांक8_t state;
	uपूर्णांक8_t persistent;
पूर्ण;

/*
 * send a set state command to the device by पढ़ोing the current items->state
 * field. items is then filled with the current state.
 */
अटल पूर्णांक hidpp_touchpad_fw_items_set(काष्ठा hidpp_device *hidpp,
				       u8 feature_index,
				       काष्ठा hidpp_touchpad_fw_items *items)
अणु
	काष्ठा hidpp_report response;
	पूर्णांक ret;
	u8 *params = (u8 *)response.fap.params;

	ret = hidpp_send_fap_command_sync(hidpp, feature_index,
		CMD_TOUCHPAD_FW_ITEMS_SET, &items->state, 1, &response);

	अगर (ret > 0) अणु
		hid_err(hidpp->hid_dev, "%s: received protocol error 0x%02x\n",
			__func__, ret);
		वापस -EPROTO;
	पूर्ण
	अगर (ret)
		वापस ret;

	items->presence = params[0];
	items->desired_state = params[1];
	items->state = params[2];
	items->persistent = params[3];

	वापस 0;
पूर्ण

/* -------------------------------------------------------------------------- */
/* 0x6100: TouchPadRawXY                                                      */
/* -------------------------------------------------------------------------- */

#घोषणा HIDPP_PAGE_TOUCHPAD_RAW_XY			0x6100

#घोषणा CMD_TOUCHPAD_GET_RAW_INFO			0x01
#घोषणा CMD_TOUCHPAD_SET_RAW_REPORT_STATE		0x21

#घोषणा EVENT_TOUCHPAD_RAW_XY				0x00

#घोषणा TOUCHPAD_RAW_XY_ORIGIN_LOWER_LEFT		0x01
#घोषणा TOUCHPAD_RAW_XY_ORIGIN_UPPER_LEFT		0x03

काष्ठा hidpp_touchpad_raw_info अणु
	u16 x_size;
	u16 y_size;
	u8 z_range;
	u8 area_range;
	u8 बारtamp_unit;
	u8 maxcontacts;
	u8 origin;
	u16 res;
पूर्ण;

काष्ठा hidpp_touchpad_raw_xy_finger अणु
	u8 contact_type;
	u8 contact_status;
	u16 x;
	u16 y;
	u8 z;
	u8 area;
	u8 finger_id;
पूर्ण;

काष्ठा hidpp_touchpad_raw_xy अणु
	u16 बारtamp;
	काष्ठा hidpp_touchpad_raw_xy_finger fingers[2];
	u8 spurious_flag;
	u8 end_of_frame;
	u8 finger_count;
	u8 button;
पूर्ण;

अटल पूर्णांक hidpp_touchpad_get_raw_info(काष्ठा hidpp_device *hidpp,
	u8 feature_index, काष्ठा hidpp_touchpad_raw_info *raw_info)
अणु
	काष्ठा hidpp_report response;
	पूर्णांक ret;
	u8 *params = (u8 *)response.fap.params;

	ret = hidpp_send_fap_command_sync(hidpp, feature_index,
		CMD_TOUCHPAD_GET_RAW_INFO, शून्य, 0, &response);

	अगर (ret > 0) अणु
		hid_err(hidpp->hid_dev, "%s: received protocol error 0x%02x\n",
			__func__, ret);
		वापस -EPROTO;
	पूर्ण
	अगर (ret)
		वापस ret;

	raw_info->x_size = get_unaligned_be16(&params[0]);
	raw_info->y_size = get_unaligned_be16(&params[2]);
	raw_info->z_range = params[4];
	raw_info->area_range = params[5];
	raw_info->maxcontacts = params[7];
	raw_info->origin = params[8];
	/* res is given in unit per inch */
	raw_info->res = get_unaligned_be16(&params[13]) * 2 / 51;

	वापस ret;
पूर्ण

अटल पूर्णांक hidpp_touchpad_set_raw_report_state(काष्ठा hidpp_device *hidpp_dev,
		u8 feature_index, bool send_raw_reports,
		bool sensor_enhanced_settings)
अणु
	काष्ठा hidpp_report response;

	/*
	 * Params:
	 *   bit 0 - enable raw
	 *   bit 1 - 16bit Z, no area
	 *   bit 2 - enhanced sensitivity
	 *   bit 3 - width, height (4 bits each) instead of area
	 *   bit 4 - send raw + gestures (degrades smoothness)
	 *   reमुख्यing bits - reserved
	 */
	u8 params = send_raw_reports | (sensor_enhanced_settings << 2);

	वापस hidpp_send_fap_command_sync(hidpp_dev, feature_index,
		CMD_TOUCHPAD_SET_RAW_REPORT_STATE, &params, 1, &response);
पूर्ण

अटल व्योम hidpp_touchpad_touch_event(u8 *data,
	काष्ठा hidpp_touchpad_raw_xy_finger *finger)
अणु
	u8 x_m = data[0] << 2;
	u8 y_m = data[2] << 2;

	finger->x = x_m << 6 | data[1];
	finger->y = y_m << 6 | data[3];

	finger->contact_type = data[0] >> 6;
	finger->contact_status = data[2] >> 6;

	finger->z = data[4];
	finger->area = data[5];
	finger->finger_id = data[6] >> 4;
पूर्ण

अटल व्योम hidpp_touchpad_raw_xy_event(काष्ठा hidpp_device *hidpp_dev,
		u8 *data, काष्ठा hidpp_touchpad_raw_xy *raw_xy)
अणु
	स_रखो(raw_xy, 0, माप(काष्ठा hidpp_touchpad_raw_xy));
	raw_xy->end_of_frame = data[8] & 0x01;
	raw_xy->spurious_flag = (data[8] >> 1) & 0x01;
	raw_xy->finger_count = data[15] & 0x0f;
	raw_xy->button = (data[8] >> 2) & 0x01;

	अगर (raw_xy->finger_count) अणु
		hidpp_touchpad_touch_event(&data[2], &raw_xy->fingers[0]);
		hidpp_touchpad_touch_event(&data[9], &raw_xy->fingers[1]);
	पूर्ण
पूर्ण

/* -------------------------------------------------------------------------- */
/* 0x8123: Force feedback support                                             */
/* -------------------------------------------------------------------------- */

#घोषणा HIDPP_FF_GET_INFO		0x01
#घोषणा HIDPP_FF_RESET_ALL		0x11
#घोषणा HIDPP_FF_DOWNLOAD_EFFECT	0x21
#घोषणा HIDPP_FF_SET_EFFECT_STATE	0x31
#घोषणा HIDPP_FF_DESTROY_EFFECT		0x41
#घोषणा HIDPP_FF_GET_APERTURE		0x51
#घोषणा HIDPP_FF_SET_APERTURE		0x61
#घोषणा HIDPP_FF_GET_GLOBAL_GAINS	0x71
#घोषणा HIDPP_FF_SET_GLOBAL_GAINS	0x81

#घोषणा HIDPP_FF_EFFECT_STATE_GET	0x00
#घोषणा HIDPP_FF_EFFECT_STATE_STOP	0x01
#घोषणा HIDPP_FF_EFFECT_STATE_PLAY	0x02
#घोषणा HIDPP_FF_EFFECT_STATE_PAUSE	0x03

#घोषणा HIDPP_FF_EFFECT_CONSTANT	0x00
#घोषणा HIDPP_FF_EFFECT_PERIODIC_SINE		0x01
#घोषणा HIDPP_FF_EFFECT_PERIODIC_SQUARE		0x02
#घोषणा HIDPP_FF_EFFECT_PERIODIC_TRIANGLE	0x03
#घोषणा HIDPP_FF_EFFECT_PERIODIC_SAWTOOTHUP	0x04
#घोषणा HIDPP_FF_EFFECT_PERIODIC_SAWTOOTHDOWN	0x05
#घोषणा HIDPP_FF_EFFECT_SPRING		0x06
#घोषणा HIDPP_FF_EFFECT_DAMPER		0x07
#घोषणा HIDPP_FF_EFFECT_FRICTION	0x08
#घोषणा HIDPP_FF_EFFECT_INERTIA		0x09
#घोषणा HIDPP_FF_EFFECT_RAMP		0x0A

#घोषणा HIDPP_FF_EFFECT_AUTOSTART	0x80

#घोषणा HIDPP_FF_EFFECTID_NONE		-1
#घोषणा HIDPP_FF_EFFECTID_AUTOCENTER	-2
#घोषणा HIDPP_AUTOCENTER_PARAMS_LENGTH	18

#घोषणा HIDPP_FF_MAX_PARAMS	20
#घोषणा HIDPP_FF_RESERVED_SLOTS	1

काष्ठा hidpp_ff_निजी_data अणु
	काष्ठा hidpp_device *hidpp;
	u8 feature_index;
	u8 version;
	u16 gain;
	s16 range;
	u8 slot_स्वतःcenter;
	u8 num_effects;
	पूर्णांक *effect_ids;
	काष्ठा workqueue_काष्ठा *wq;
	atomic_t workqueue_size;
पूर्ण;

काष्ठा hidpp_ff_work_data अणु
	काष्ठा work_काष्ठा work;
	काष्ठा hidpp_ff_निजी_data *data;
	पूर्णांक effect_id;
	u8 command;
	u8 params[HIDPP_FF_MAX_PARAMS];
	u8 size;
पूर्ण;

अटल स्थिर चिन्हित लघु hidpp_ff_effects[] = अणु
	FF_CONSTANT,
	FF_PERIODIC,
	FF_SINE,
	FF_SQUARE,
	FF_SAW_UP,
	FF_SAW_DOWN,
	FF_TRIANGLE,
	FF_SPRING,
	FF_DAMPER,
	FF_AUTOCENTER,
	FF_GAIN,
	-1
पूर्ण;

अटल स्थिर चिन्हित लघु hidpp_ff_effects_v2[] = अणु
	FF_RAMP,
	FF_FRICTION,
	FF_INERTIA,
	-1
पूर्ण;

अटल स्थिर u8 HIDPP_FF_CONDITION_CMDS[] = अणु
	HIDPP_FF_EFFECT_SPRING,
	HIDPP_FF_EFFECT_FRICTION,
	HIDPP_FF_EFFECT_DAMPER,
	HIDPP_FF_EFFECT_INERTIA
पूर्ण;

अटल स्थिर अक्षर *HIDPP_FF_CONDITION_NAMES[] = अणु
	"spring",
	"friction",
	"damper",
	"inertia"
पूर्ण;


अटल u8 hidpp_ff_find_effect(काष्ठा hidpp_ff_निजी_data *data, पूर्णांक effect_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < data->num_effects; i++)
		अगर (data->effect_ids[i] == effect_id)
			वापस i+1;

	वापस 0;
पूर्ण

अटल व्योम hidpp_ff_work_handler(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा hidpp_ff_work_data *wd = container_of(w, काष्ठा hidpp_ff_work_data, work);
	काष्ठा hidpp_ff_निजी_data *data = wd->data;
	काष्ठा hidpp_report response;
	u8 slot;
	पूर्णांक ret;

	/* add slot number अगर needed */
	चयन (wd->effect_id) अणु
	हाल HIDPP_FF_EFFECTID_AUTOCENTER:
		wd->params[0] = data->slot_स्वतःcenter;
		अवरोध;
	हाल HIDPP_FF_EFFECTID_NONE:
		/* leave slot as zero */
		अवरोध;
	शेष:
		/* find current slot क्रम effect */
		wd->params[0] = hidpp_ff_find_effect(data, wd->effect_id);
		अवरोध;
	पूर्ण

	/* send command and रुको क्रम reply */
	ret = hidpp_send_fap_command_sync(data->hidpp, data->feature_index,
		wd->command, wd->params, wd->size, &response);

	अगर (ret) अणु
		hid_err(data->hidpp->hid_dev, "Failed to send command to device!\n");
		जाओ out;
	पूर्ण

	/* parse वापस data */
	चयन (wd->command) अणु
	हाल HIDPP_FF_DOWNLOAD_EFFECT:
		slot = response.fap.params[0];
		अगर (slot > 0 && slot <= data->num_effects) अणु
			अगर (wd->effect_id >= 0)
				/* regular effect uploaded */
				data->effect_ids[slot-1] = wd->effect_id;
			अन्यथा अगर (wd->effect_id >= HIDPP_FF_EFFECTID_AUTOCENTER)
				/* स्वतःcenter spring uploaded */
				data->slot_स्वतःcenter = slot;
		पूर्ण
		अवरोध;
	हाल HIDPP_FF_DESTROY_EFFECT:
		अगर (wd->effect_id >= 0)
			/* regular effect destroyed */
			data->effect_ids[wd->params[0]-1] = -1;
		अन्यथा अगर (wd->effect_id >= HIDPP_FF_EFFECTID_AUTOCENTER)
			/* स्वतःcenter spring destoyed */
			data->slot_स्वतःcenter = 0;
		अवरोध;
	हाल HIDPP_FF_SET_GLOBAL_GAINS:
		data->gain = (wd->params[0] << 8) + wd->params[1];
		अवरोध;
	हाल HIDPP_FF_SET_APERTURE:
		data->range = (wd->params[0] << 8) + wd->params[1];
		अवरोध;
	शेष:
		/* no action needed */
		अवरोध;
	पूर्ण

out:
	atomic_dec(&data->workqueue_size);
	kमुक्त(wd);
पूर्ण

अटल पूर्णांक hidpp_ff_queue_work(काष्ठा hidpp_ff_निजी_data *data, पूर्णांक effect_id, u8 command, u8 *params, u8 size)
अणु
	काष्ठा hidpp_ff_work_data *wd = kzalloc(माप(*wd), GFP_KERNEL);
	पूर्णांक s;

	अगर (!wd)
		वापस -ENOMEM;

	INIT_WORK(&wd->work, hidpp_ff_work_handler);

	wd->data = data;
	wd->effect_id = effect_id;
	wd->command = command;
	wd->size = size;
	स_नकल(wd->params, params, size);

	atomic_inc(&data->workqueue_size);
	queue_work(data->wq, &wd->work);

	/* warn about excessive queue size */
	s = atomic_पढ़ो(&data->workqueue_size);
	अगर (s >= 20 && s % 20 == 0)
		hid_warn(data->hidpp->hid_dev, "Force feedback command queue contains %d commands, causing substantial delays!", s);

	वापस 0;
पूर्ण

अटल पूर्णांक hidpp_ff_upload_effect(काष्ठा input_dev *dev, काष्ठा ff_effect *effect, काष्ठा ff_effect *old)
अणु
	काष्ठा hidpp_ff_निजी_data *data = dev->ff->निजी;
	u8 params[20];
	u8 size;
	पूर्णांक क्रमce;

	/* set common parameters */
	params[2] = effect->replay.length >> 8;
	params[3] = effect->replay.length & 255;
	params[4] = effect->replay.delay >> 8;
	params[5] = effect->replay.delay & 255;

	चयन (effect->type) अणु
	हाल FF_CONSTANT:
		क्रमce = (effect->u.स्थिरant.level * fixp_sin16((effect->direction * 360) >> 16)) >> 15;
		params[1] = HIDPP_FF_EFFECT_CONSTANT;
		params[6] = क्रमce >> 8;
		params[7] = क्रमce & 255;
		params[8] = effect->u.स्थिरant.envelope.attack_level >> 7;
		params[9] = effect->u.स्थिरant.envelope.attack_length >> 8;
		params[10] = effect->u.स्थिरant.envelope.attack_length & 255;
		params[11] = effect->u.स्थिरant.envelope.fade_level >> 7;
		params[12] = effect->u.स्थिरant.envelope.fade_length >> 8;
		params[13] = effect->u.स्थिरant.envelope.fade_length & 255;
		size = 14;
		dbg_hid("Uploading constant force level=%d in dir %d = %d\n",
				effect->u.स्थिरant.level,
				effect->direction, क्रमce);
		dbg_hid("          envelope attack=(%d, %d ms) fade=(%d, %d ms)\n",
				effect->u.स्थिरant.envelope.attack_level,
				effect->u.स्थिरant.envelope.attack_length,
				effect->u.स्थिरant.envelope.fade_level,
				effect->u.स्थिरant.envelope.fade_length);
		अवरोध;
	हाल FF_PERIODIC:
	अणु
		चयन (effect->u.periodic.waveक्रमm) अणु
		हाल FF_SINE:
			params[1] = HIDPP_FF_EFFECT_PERIODIC_SINE;
			अवरोध;
		हाल FF_SQUARE:
			params[1] = HIDPP_FF_EFFECT_PERIODIC_SQUARE;
			अवरोध;
		हाल FF_SAW_UP:
			params[1] = HIDPP_FF_EFFECT_PERIODIC_SAWTOOTHUP;
			अवरोध;
		हाल FF_SAW_DOWN:
			params[1] = HIDPP_FF_EFFECT_PERIODIC_SAWTOOTHDOWN;
			अवरोध;
		हाल FF_TRIANGLE:
			params[1] = HIDPP_FF_EFFECT_PERIODIC_TRIANGLE;
			अवरोध;
		शेष:
			hid_err(data->hidpp->hid_dev, "Unexpected periodic waveform type %i!\n", effect->u.periodic.waveक्रमm);
			वापस -EINVAL;
		पूर्ण
		क्रमce = (effect->u.periodic.magnitude * fixp_sin16((effect->direction * 360) >> 16)) >> 15;
		params[6] = effect->u.periodic.magnitude >> 8;
		params[7] = effect->u.periodic.magnitude & 255;
		params[8] = effect->u.periodic.offset >> 8;
		params[9] = effect->u.periodic.offset & 255;
		params[10] = effect->u.periodic.period >> 8;
		params[11] = effect->u.periodic.period & 255;
		params[12] = effect->u.periodic.phase >> 8;
		params[13] = effect->u.periodic.phase & 255;
		params[14] = effect->u.periodic.envelope.attack_level >> 7;
		params[15] = effect->u.periodic.envelope.attack_length >> 8;
		params[16] = effect->u.periodic.envelope.attack_length & 255;
		params[17] = effect->u.periodic.envelope.fade_level >> 7;
		params[18] = effect->u.periodic.envelope.fade_length >> 8;
		params[19] = effect->u.periodic.envelope.fade_length & 255;
		size = 20;
		dbg_hid("Uploading periodic force mag=%d/dir=%d, offset=%d, period=%d ms, phase=%d\n",
				effect->u.periodic.magnitude, effect->direction,
				effect->u.periodic.offset,
				effect->u.periodic.period,
				effect->u.periodic.phase);
		dbg_hid("          envelope attack=(%d, %d ms) fade=(%d, %d ms)\n",
				effect->u.periodic.envelope.attack_level,
				effect->u.periodic.envelope.attack_length,
				effect->u.periodic.envelope.fade_level,
				effect->u.periodic.envelope.fade_length);
		अवरोध;
	पूर्ण
	हाल FF_RAMP:
		params[1] = HIDPP_FF_EFFECT_RAMP;
		क्रमce = (effect->u.ramp.start_level * fixp_sin16((effect->direction * 360) >> 16)) >> 15;
		params[6] = क्रमce >> 8;
		params[7] = क्रमce & 255;
		क्रमce = (effect->u.ramp.end_level * fixp_sin16((effect->direction * 360) >> 16)) >> 15;
		params[8] = क्रमce >> 8;
		params[9] = क्रमce & 255;
		params[10] = effect->u.ramp.envelope.attack_level >> 7;
		params[11] = effect->u.ramp.envelope.attack_length >> 8;
		params[12] = effect->u.ramp.envelope.attack_length & 255;
		params[13] = effect->u.ramp.envelope.fade_level >> 7;
		params[14] = effect->u.ramp.envelope.fade_length >> 8;
		params[15] = effect->u.ramp.envelope.fade_length & 255;
		size = 16;
		dbg_hid("Uploading ramp force level=%d -> %d in dir %d = %d\n",
				effect->u.ramp.start_level,
				effect->u.ramp.end_level,
				effect->direction, क्रमce);
		dbg_hid("          envelope attack=(%d, %d ms) fade=(%d, %d ms)\n",
				effect->u.ramp.envelope.attack_level,
				effect->u.ramp.envelope.attack_length,
				effect->u.ramp.envelope.fade_level,
				effect->u.ramp.envelope.fade_length);
		अवरोध;
	हाल FF_FRICTION:
	हाल FF_INERTIA:
	हाल FF_SPRING:
	हाल FF_DAMPER:
		params[1] = HIDPP_FF_CONDITION_CMDS[effect->type - FF_SPRING];
		params[6] = effect->u.condition[0].left_saturation >> 9;
		params[7] = (effect->u.condition[0].left_saturation >> 1) & 255;
		params[8] = effect->u.condition[0].left_coeff >> 8;
		params[9] = effect->u.condition[0].left_coeff & 255;
		params[10] = effect->u.condition[0].deadband >> 9;
		params[11] = (effect->u.condition[0].deadband >> 1) & 255;
		params[12] = effect->u.condition[0].center >> 8;
		params[13] = effect->u.condition[0].center & 255;
		params[14] = effect->u.condition[0].right_coeff >> 8;
		params[15] = effect->u.condition[0].right_coeff & 255;
		params[16] = effect->u.condition[0].right_saturation >> 9;
		params[17] = (effect->u.condition[0].right_saturation >> 1) & 255;
		size = 18;
		dbg_hid("Uploading %s force left coeff=%d, left sat=%d, right coeff=%d, right sat=%d\n",
				HIDPP_FF_CONDITION_NAMES[effect->type - FF_SPRING],
				effect->u.condition[0].left_coeff,
				effect->u.condition[0].left_saturation,
				effect->u.condition[0].right_coeff,
				effect->u.condition[0].right_saturation);
		dbg_hid("          deadband=%d, center=%d\n",
				effect->u.condition[0].deadband,
				effect->u.condition[0].center);
		अवरोध;
	शेष:
		hid_err(data->hidpp->hid_dev, "Unexpected force type %i!\n", effect->type);
		वापस -EINVAL;
	पूर्ण

	वापस hidpp_ff_queue_work(data, effect->id, HIDPP_FF_DOWNLOAD_EFFECT, params, size);
पूर्ण

अटल पूर्णांक hidpp_ff_playback(काष्ठा input_dev *dev, पूर्णांक effect_id, पूर्णांक value)
अणु
	काष्ठा hidpp_ff_निजी_data *data = dev->ff->निजी;
	u8 params[2];

	params[1] = value ? HIDPP_FF_EFFECT_STATE_PLAY : HIDPP_FF_EFFECT_STATE_STOP;

	dbg_hid("St%sing playback of effect %d.\n", value?"art":"opp", effect_id);

	वापस hidpp_ff_queue_work(data, effect_id, HIDPP_FF_SET_EFFECT_STATE, params, ARRAY_SIZE(params));
पूर्ण

अटल पूर्णांक hidpp_ff_erase_effect(काष्ठा input_dev *dev, पूर्णांक effect_id)
अणु
	काष्ठा hidpp_ff_निजी_data *data = dev->ff->निजी;
	u8 slot = 0;

	dbg_hid("Erasing effect %d.\n", effect_id);

	वापस hidpp_ff_queue_work(data, effect_id, HIDPP_FF_DESTROY_EFFECT, &slot, 1);
पूर्ण

अटल व्योम hidpp_ff_set_स्वतःcenter(काष्ठा input_dev *dev, u16 magnitude)
अणु
	काष्ठा hidpp_ff_निजी_data *data = dev->ff->निजी;
	u8 params[HIDPP_AUTOCENTER_PARAMS_LENGTH];

	dbg_hid("Setting autocenter to %d.\n", magnitude);

	/* start a standard spring effect */
	params[1] = HIDPP_FF_EFFECT_SPRING | HIDPP_FF_EFFECT_AUTOSTART;
	/* zero delay and duration */
	params[2] = params[3] = params[4] = params[5] = 0;
	/* set coeff to 25% of saturation */
	params[8] = params[14] = magnitude >> 11;
	params[9] = params[15] = (magnitude >> 3) & 255;
	params[6] = params[16] = magnitude >> 9;
	params[7] = params[17] = (magnitude >> 1) & 255;
	/* zero deadband and center */
	params[10] = params[11] = params[12] = params[13] = 0;

	hidpp_ff_queue_work(data, HIDPP_FF_EFFECTID_AUTOCENTER, HIDPP_FF_DOWNLOAD_EFFECT, params, ARRAY_SIZE(params));
पूर्ण

अटल व्योम hidpp_ff_set_gain(काष्ठा input_dev *dev, u16 gain)
अणु
	काष्ठा hidpp_ff_निजी_data *data = dev->ff->निजी;
	u8 params[4];

	dbg_hid("Setting gain to %d.\n", gain);

	params[0] = gain >> 8;
	params[1] = gain & 255;
	params[2] = 0; /* no boost */
	params[3] = 0;

	hidpp_ff_queue_work(data, HIDPP_FF_EFFECTID_NONE, HIDPP_FF_SET_GLOBAL_GAINS, params, ARRAY_SIZE(params));
पूर्ण

अटल sमाप_प्रकार hidpp_ff_range_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा hid_input *hidinput = list_entry(hid->inमाला_दो.next, काष्ठा hid_input, list);
	काष्ठा input_dev *idev = hidinput->input;
	काष्ठा hidpp_ff_निजी_data *data = idev->ff->निजी;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", data->range);
पूर्ण

अटल sमाप_प्रकार hidpp_ff_range_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा hid_input *hidinput = list_entry(hid->inमाला_दो.next, काष्ठा hid_input, list);
	काष्ठा input_dev *idev = hidinput->input;
	काष्ठा hidpp_ff_निजी_data *data = idev->ff->निजी;
	u8 params[2];
	पूर्णांक range = simple_म_से_अदीर्घ(buf, शून्य, 10);

	range = clamp(range, 180, 900);

	params[0] = range >> 8;
	params[1] = range & 0x00FF;

	hidpp_ff_queue_work(data, -1, HIDPP_FF_SET_APERTURE, params, ARRAY_SIZE(params));

	वापस count;
पूर्ण

अटल DEVICE_ATTR(range, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH, hidpp_ff_range_show, hidpp_ff_range_store);

अटल व्योम hidpp_ff_destroy(काष्ठा ff_device *ff)
अणु
	काष्ठा hidpp_ff_निजी_data *data = ff->निजी;
	काष्ठा hid_device *hid = data->hidpp->hid_dev;

	hid_info(hid, "Unloading HID++ force feedback.\n");

	device_हटाओ_file(&hid->dev, &dev_attr_range);
	destroy_workqueue(data->wq);
	kमुक्त(data->effect_ids);
पूर्ण

अटल पूर्णांक hidpp_ff_init(काष्ठा hidpp_device *hidpp,
			 काष्ठा hidpp_ff_निजी_data *data)
अणु
	काष्ठा hid_device *hid = hidpp->hid_dev;
	काष्ठा hid_input *hidinput;
	काष्ठा input_dev *dev;
	स्थिर काष्ठा usb_device_descriptor *udesc = &(hid_to_usb_dev(hid)->descriptor);
	स्थिर u16 bcdDevice = le16_to_cpu(udesc->bcdDevice);
	काष्ठा ff_device *ff;
	पूर्णांक error, j, num_slots = data->num_effects;
	u8 version;

	अगर (list_empty(&hid->inमाला_दो)) अणु
		hid_err(hid, "no inputs found\n");
		वापस -ENODEV;
	पूर्ण
	hidinput = list_entry(hid->inमाला_दो.next, काष्ठा hid_input, list);
	dev = hidinput->input;

	अगर (!dev) अणु
		hid_err(hid, "Struct input_dev not set!\n");
		वापस -EINVAL;
	पूर्ण

	/* Get firmware release */
	version = bcdDevice & 255;

	/* Set supported क्रमce feedback capabilities */
	क्रम (j = 0; hidpp_ff_effects[j] >= 0; j++)
		set_bit(hidpp_ff_effects[j], dev->ffbit);
	अगर (version > 1)
		क्रम (j = 0; hidpp_ff_effects_v2[j] >= 0; j++)
			set_bit(hidpp_ff_effects_v2[j], dev->ffbit);

	error = input_ff_create(dev, num_slots);

	अगर (error) अणु
		hid_err(dev, "Failed to create FF device!\n");
		वापस error;
	पूर्ण
	/*
	 * Create a copy of passed data, so we can transfer memory
	 * ownership to FF core
	 */
	data = kmemdup(data, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	data->effect_ids = kसुस्मृति(num_slots, माप(पूर्णांक), GFP_KERNEL);
	अगर (!data->effect_ids) अणु
		kमुक्त(data);
		वापस -ENOMEM;
	पूर्ण
	data->wq = create_singlethपढ़ो_workqueue("hidpp-ff-sendqueue");
	अगर (!data->wq) अणु
		kमुक्त(data->effect_ids);
		kमुक्त(data);
		वापस -ENOMEM;
	पूर्ण

	data->hidpp = hidpp;
	data->version = version;
	क्रम (j = 0; j < num_slots; j++)
		data->effect_ids[j] = -1;

	ff = dev->ff;
	ff->निजी = data;

	ff->upload = hidpp_ff_upload_effect;
	ff->erase = hidpp_ff_erase_effect;
	ff->playback = hidpp_ff_playback;
	ff->set_gain = hidpp_ff_set_gain;
	ff->set_स्वतःcenter = hidpp_ff_set_स्वतःcenter;
	ff->destroy = hidpp_ff_destroy;

	/* Create sysfs पूर्णांकerface */
	error = device_create_file(&(hidpp->hid_dev->dev), &dev_attr_range);
	अगर (error)
		hid_warn(hidpp->hid_dev, "Unable to create sysfs interface for \"range\", errno %d!\n", error);

	/* init the hardware command queue */
	atomic_set(&data->workqueue_size, 0);

	hid_info(hid, "Force feedback support loaded (firmware release %d).\n",
		 version);

	वापस 0;
पूर्ण

/* ************************************************************************** */
/*                                                                            */
/* Device Support                                                             */
/*                                                                            */
/* ************************************************************************** */

/* -------------------------------------------------------------------------- */
/* Touchpad HID++ devices                                                     */
/* -------------------------------------------------------------------------- */

#घोषणा WTP_MANUAL_RESOLUTION				39

काष्ठा wtp_data अणु
	u16 x_size, y_size;
	u8 finger_count;
	u8 mt_feature_index;
	u8 button_feature_index;
	u8 maxcontacts;
	bool flip_y;
	अचिन्हित पूर्णांक resolution;
पूर्ण;

अटल पूर्णांक wtp_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	वापस -1;
पूर्ण

अटल व्योम wtp_populate_input(काष्ठा hidpp_device *hidpp,
			       काष्ठा input_dev *input_dev)
अणु
	काष्ठा wtp_data *wd = hidpp->निजी_data;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__clear_bit(EV_REL, input_dev->evbit);
	__clear_bit(EV_LED, input_dev->evbit);

	input_set_असल_params(input_dev, ABS_MT_POSITION_X, 0, wd->x_size, 0, 0);
	input_असल_set_res(input_dev, ABS_MT_POSITION_X, wd->resolution);
	input_set_असल_params(input_dev, ABS_MT_POSITION_Y, 0, wd->y_size, 0, 0);
	input_असल_set_res(input_dev, ABS_MT_POSITION_Y, wd->resolution);

	/* Max pressure is not given by the devices, pick one */
	input_set_असल_params(input_dev, ABS_MT_PRESSURE, 0, 50, 0, 0);

	input_set_capability(input_dev, EV_KEY, BTN_LEFT);

	अगर (hidpp->quirks & HIDPP_QUIRK_WTP_PHYSICAL_BUTTONS)
		input_set_capability(input_dev, EV_KEY, BTN_RIGHT);
	अन्यथा
		__set_bit(INPUT_PROP_BUTTONPAD, input_dev->propbit);

	input_mt_init_slots(input_dev, wd->maxcontacts, INPUT_MT_POINTER |
		INPUT_MT_DROP_UNUSED);
पूर्ण

अटल व्योम wtp_touch_event(काष्ठा hidpp_device *hidpp,
	काष्ठा hidpp_touchpad_raw_xy_finger *touch_report)
अणु
	काष्ठा wtp_data *wd = hidpp->निजी_data;
	पूर्णांक slot;

	अगर (!touch_report->finger_id || touch_report->contact_type)
		/* no actual data */
		वापस;

	slot = input_mt_get_slot_by_key(hidpp->input, touch_report->finger_id);

	input_mt_slot(hidpp->input, slot);
	input_mt_report_slot_state(hidpp->input, MT_TOOL_FINGER,
					touch_report->contact_status);
	अगर (touch_report->contact_status) अणु
		input_event(hidpp->input, EV_ABS, ABS_MT_POSITION_X,
				touch_report->x);
		input_event(hidpp->input, EV_ABS, ABS_MT_POSITION_Y,
				wd->flip_y ? wd->y_size - touch_report->y :
					     touch_report->y);
		input_event(hidpp->input, EV_ABS, ABS_MT_PRESSURE,
				touch_report->area);
	पूर्ण
पूर्ण

अटल व्योम wtp_send_raw_xy_event(काष्ठा hidpp_device *hidpp,
		काष्ठा hidpp_touchpad_raw_xy *raw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++)
		wtp_touch_event(hidpp, &(raw->fingers[i]));

	अगर (raw->end_of_frame &&
	    !(hidpp->quirks & HIDPP_QUIRK_WTP_PHYSICAL_BUTTONS))
		input_event(hidpp->input, EV_KEY, BTN_LEFT, raw->button);

	अगर (raw->end_of_frame || raw->finger_count <= 2) अणु
		input_mt_sync_frame(hidpp->input);
		input_sync(hidpp->input);
	पूर्ण
पूर्ण

अटल पूर्णांक wtp_mouse_raw_xy_event(काष्ठा hidpp_device *hidpp, u8 *data)
अणु
	काष्ठा wtp_data *wd = hidpp->निजी_data;
	u8 c1_area = ((data[7] & 0xf) * (data[7] & 0xf) +
		      (data[7] >> 4) * (data[7] >> 4)) / 2;
	u8 c2_area = ((data[13] & 0xf) * (data[13] & 0xf) +
		      (data[13] >> 4) * (data[13] >> 4)) / 2;
	काष्ठा hidpp_touchpad_raw_xy raw = अणु
		.बारtamp = data[1],
		.fingers = अणु
			अणु
				.contact_type = 0,
				.contact_status = !!data[7],
				.x = get_unaligned_le16(&data[3]),
				.y = get_unaligned_le16(&data[5]),
				.z = c1_area,
				.area = c1_area,
				.finger_id = data[2],
			पूर्ण, अणु
				.contact_type = 0,
				.contact_status = !!data[13],
				.x = get_unaligned_le16(&data[9]),
				.y = get_unaligned_le16(&data[11]),
				.z = c2_area,
				.area = c2_area,
				.finger_id = data[8],
			पूर्ण
		पूर्ण,
		.finger_count = wd->maxcontacts,
		.spurious_flag = 0,
		.end_of_frame = (data[0] >> 7) == 0,
		.button = data[0] & 0x01,
	पूर्ण;

	wtp_send_raw_xy_event(hidpp, &raw);

	वापस 1;
पूर्ण

अटल पूर्णांक wtp_raw_event(काष्ठा hid_device *hdev, u8 *data, पूर्णांक size)
अणु
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);
	काष्ठा wtp_data *wd = hidpp->निजी_data;
	काष्ठा hidpp_report *report = (काष्ठा hidpp_report *)data;
	काष्ठा hidpp_touchpad_raw_xy raw;

	अगर (!wd || !hidpp->input)
		वापस 1;

	चयन (data[0]) अणु
	हाल 0x02:
		अगर (size < 2) अणु
			hid_err(hdev, "Received HID report of bad size (%d)",
				size);
			वापस 1;
		पूर्ण
		अगर (hidpp->quirks & HIDPP_QUIRK_WTP_PHYSICAL_BUTTONS) अणु
			input_event(hidpp->input, EV_KEY, BTN_LEFT,
					!!(data[1] & 0x01));
			input_event(hidpp->input, EV_KEY, BTN_RIGHT,
					!!(data[1] & 0x02));
			input_sync(hidpp->input);
			वापस 0;
		पूर्ण अन्यथा अणु
			अगर (size < 21)
				वापस 1;
			वापस wtp_mouse_raw_xy_event(hidpp, &data[7]);
		पूर्ण
	हाल REPORT_ID_HIDPP_LONG:
		/* size is alपढ़ोy checked in hidpp_raw_event. */
		अगर ((report->fap.feature_index != wd->mt_feature_index) ||
		    (report->fap.funcindex_clientid != EVENT_TOUCHPAD_RAW_XY))
			वापस 1;
		hidpp_touchpad_raw_xy_event(hidpp, data + 4, &raw);

		wtp_send_raw_xy_event(hidpp, &raw);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wtp_get_config(काष्ठा hidpp_device *hidpp)
अणु
	काष्ठा wtp_data *wd = hidpp->निजी_data;
	काष्ठा hidpp_touchpad_raw_info raw_info = अणु0पूर्ण;
	u8 feature_type;
	पूर्णांक ret;

	ret = hidpp_root_get_feature(hidpp, HIDPP_PAGE_TOUCHPAD_RAW_XY,
		&wd->mt_feature_index, &feature_type);
	अगर (ret)
		/* means that the device is not घातered up */
		वापस ret;

	ret = hidpp_touchpad_get_raw_info(hidpp, wd->mt_feature_index,
		&raw_info);
	अगर (ret)
		वापस ret;

	wd->x_size = raw_info.x_size;
	wd->y_size = raw_info.y_size;
	wd->maxcontacts = raw_info.maxcontacts;
	wd->flip_y = raw_info.origin == TOUCHPAD_RAW_XY_ORIGIN_LOWER_LEFT;
	wd->resolution = raw_info.res;
	अगर (!wd->resolution)
		wd->resolution = WTP_MANUAL_RESOLUTION;

	वापस 0;
पूर्ण

अटल पूर्णांक wtp_allocate(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);
	काष्ठा wtp_data *wd;

	wd = devm_kzalloc(&hdev->dev, माप(काष्ठा wtp_data),
			GFP_KERNEL);
	अगर (!wd)
		वापस -ENOMEM;

	hidpp->निजी_data = wd;

	वापस 0;
पूर्ण;

अटल पूर्णांक wtp_connect(काष्ठा hid_device *hdev, bool connected)
अणु
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);
	काष्ठा wtp_data *wd = hidpp->निजी_data;
	पूर्णांक ret;

	अगर (!wd->x_size) अणु
		ret = wtp_get_config(hidpp);
		अगर (ret) अणु
			hid_err(hdev, "Can not get wtp config: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस hidpp_touchpad_set_raw_report_state(hidpp, wd->mt_feature_index,
			true, true);
पूर्ण

/* ------------------------------------------------------------------------- */
/* Logitech M560 devices                                                     */
/* ------------------------------------------------------------------------- */

/*
 * Logitech M560 protocol overview
 *
 * The Logitech M560 mouse, is deचिन्हित क्रम winकरोws 8. When the middle and/or
 * the sides buttons are pressed, it sends some keyboard keys events
 * instead of buttons ones.
 * To complicate things further, the middle button keys sequence
 * is dअगरferent from the odd press and the even press.
 *
 * क्रमward button -> Super_R
 * backward button -> Super_L+'d' (press only)
 * middle button -> 1st समय: Alt_L+SuperL+XF86TouchpadOff (press only)
 *                  2nd समय: left-click (press only)
 * NB: press-only means that when the button is pressed, the
 * KeyPress/ButtonPress and KeyRelease/ButtonRelease events are generated
 * together sequentially; instead when the button is released, no event is
 * generated !
 *
 * With the command
 *	10<xx>0a 3500af03 (where <xx> is the mouse id),
 * the mouse reacts dअगरferently:
 * - it never sends a keyboard key event
 * - क्रम the three mouse button it sends:
 *	middle button               press   11<xx>0a 3500af00...
 *	side 1 button (क्रमward)     press   11<xx>0a 3500b000...
 *	side 2 button (backward)    press   11<xx>0a 3500ae00...
 *	middle/side1/side2 button   release 11<xx>0a 35000000...
 */

अटल स्थिर u8 m560_config_parameter[] = अणु0x00, 0xaf, 0x03पूर्ण;

/* how buttons are mapped in the report */
#घोषणा M560_MOUSE_BTN_LEFT		0x01
#घोषणा M560_MOUSE_BTN_RIGHT		0x02
#घोषणा M560_MOUSE_BTN_WHEEL_LEFT	0x08
#घोषणा M560_MOUSE_BTN_WHEEL_RIGHT	0x10

#घोषणा M560_SUB_ID			0x0a
#घोषणा M560_BUTTON_MODE_REGISTER	0x35

अटल पूर्णांक m560_send_config_command(काष्ठा hid_device *hdev, bool connected)
अणु
	काष्ठा hidpp_report response;
	काष्ठा hidpp_device *hidpp_dev;

	hidpp_dev = hid_get_drvdata(hdev);

	वापस hidpp_send_rap_command_sync(
		hidpp_dev,
		REPORT_ID_HIDPP_SHORT,
		M560_SUB_ID,
		M560_BUTTON_MODE_REGISTER,
		(u8 *)m560_config_parameter,
		माप(m560_config_parameter),
		&response
	);
पूर्ण

अटल पूर्णांक m560_raw_event(काष्ठा hid_device *hdev, u8 *data, पूर्णांक size)
अणु
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);

	/* sanity check */
	अगर (!hidpp->input) अणु
		hid_err(hdev, "error in parameter\n");
		वापस -EINVAL;
	पूर्ण

	अगर (size < 7) अणु
		hid_err(hdev, "error in report\n");
		वापस 0;
	पूर्ण

	अगर (data[0] == REPORT_ID_HIDPP_LONG &&
	    data[2] == M560_SUB_ID && data[6] == 0x00) अणु
		/*
		 * m560 mouse report क्रम middle, क्रमward and backward button
		 *
		 * data[0] = 0x11
		 * data[1] = device-id
		 * data[2] = 0x0a
		 * data[5] = 0xaf -> middle
		 *	     0xb0 -> क्रमward
		 *	     0xae -> backward
		 *	     0x00 -> release all
		 * data[6] = 0x00
		 */

		चयन (data[5]) अणु
		हाल 0xaf:
			input_report_key(hidpp->input, BTN_MIDDLE, 1);
			अवरोध;
		हाल 0xb0:
			input_report_key(hidpp->input, BTN_FORWARD, 1);
			अवरोध;
		हाल 0xae:
			input_report_key(hidpp->input, BTN_BACK, 1);
			अवरोध;
		हाल 0x00:
			input_report_key(hidpp->input, BTN_BACK, 0);
			input_report_key(hidpp->input, BTN_FORWARD, 0);
			input_report_key(hidpp->input, BTN_MIDDLE, 0);
			अवरोध;
		शेष:
			hid_err(hdev, "error in report\n");
			वापस 0;
		पूर्ण
		input_sync(hidpp->input);

	पूर्ण अन्यथा अगर (data[0] == 0x02) अणु
		/*
		 * Logitech M560 mouse report
		 *
		 * data[0] = type (0x02)
		 * data[1..2] = buttons
		 * data[3..5] = xy
		 * data[6] = wheel
		 */

		पूर्णांक v;

		input_report_key(hidpp->input, BTN_LEFT,
			!!(data[1] & M560_MOUSE_BTN_LEFT));
		input_report_key(hidpp->input, BTN_RIGHT,
			!!(data[1] & M560_MOUSE_BTN_RIGHT));

		अगर (data[1] & M560_MOUSE_BTN_WHEEL_LEFT) अणु
			input_report_rel(hidpp->input, REL_HWHEEL, -1);
			input_report_rel(hidpp->input, REL_HWHEEL_HI_RES,
					 -120);
		पूर्ण अन्यथा अगर (data[1] & M560_MOUSE_BTN_WHEEL_RIGHT) अणु
			input_report_rel(hidpp->input, REL_HWHEEL, 1);
			input_report_rel(hidpp->input, REL_HWHEEL_HI_RES,
					 120);
		पूर्ण

		v = hid_snto32(hid_field_extract(hdev, data+3, 0, 12), 12);
		input_report_rel(hidpp->input, REL_X, v);

		v = hid_snto32(hid_field_extract(hdev, data+3, 12, 12), 12);
		input_report_rel(hidpp->input, REL_Y, v);

		v = hid_snto32(data[6], 8);
		अगर (v != 0)
			hidpp_scroll_counter_handle_scroll(hidpp->input,
					&hidpp->vertical_wheel_counter, v);

		input_sync(hidpp->input);
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम m560_populate_input(काष्ठा hidpp_device *hidpp,
				काष्ठा input_dev *input_dev)
अणु
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_MIDDLE, input_dev->keybit);
	__set_bit(BTN_RIGHT, input_dev->keybit);
	__set_bit(BTN_LEFT, input_dev->keybit);
	__set_bit(BTN_BACK, input_dev->keybit);
	__set_bit(BTN_FORWARD, input_dev->keybit);

	__set_bit(EV_REL, input_dev->evbit);
	__set_bit(REL_X, input_dev->relbit);
	__set_bit(REL_Y, input_dev->relbit);
	__set_bit(REL_WHEEL, input_dev->relbit);
	__set_bit(REL_HWHEEL, input_dev->relbit);
	__set_bit(REL_WHEEL_HI_RES, input_dev->relbit);
	__set_bit(REL_HWHEEL_HI_RES, input_dev->relbit);
पूर्ण

अटल पूर्णांक m560_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	वापस -1;
पूर्ण

/* ------------------------------------------------------------------------- */
/* Logitech K400 devices                                                     */
/* ------------------------------------------------------------------------- */

/*
 * The Logitech K400 keyboard has an embedded touchpad which is seen
 * as a mouse from the OS poपूर्णांक of view. There is a hardware लघुcut to disable
 * tap-to-click but the setting is not remembered accross reset, annoying some
 * users.
 *
 * We can toggle this feature from the host by using the feature 0x6010:
 * Touchpad FW items
 */

काष्ठा k400_निजी_data अणु
	u8 feature_index;
पूर्ण;

अटल पूर्णांक k400_disable_tap_to_click(काष्ठा hidpp_device *hidpp)
अणु
	काष्ठा k400_निजी_data *k400 = hidpp->निजी_data;
	काष्ठा hidpp_touchpad_fw_items items = अणुपूर्ण;
	पूर्णांक ret;
	u8 feature_type;

	अगर (!k400->feature_index) अणु
		ret = hidpp_root_get_feature(hidpp,
			HIDPP_PAGE_TOUCHPAD_FW_ITEMS,
			&k400->feature_index, &feature_type);
		अगर (ret)
			/* means that the device is not घातered up */
			वापस ret;
	पूर्ण

	ret = hidpp_touchpad_fw_items_set(hidpp, k400->feature_index, &items);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक k400_allocate(काष्ठा hid_device *hdev)
अणु
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);
	काष्ठा k400_निजी_data *k400;

	k400 = devm_kzalloc(&hdev->dev, माप(काष्ठा k400_निजी_data),
			    GFP_KERNEL);
	अगर (!k400)
		वापस -ENOMEM;

	hidpp->निजी_data = k400;

	वापस 0;
पूर्ण;

अटल पूर्णांक k400_connect(काष्ठा hid_device *hdev, bool connected)
अणु
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);

	अगर (!disable_tap_to_click)
		वापस 0;

	वापस k400_disable_tap_to_click(hidpp);
पूर्ण

/* ------------------------------------------------------------------------- */
/* Logitech G920 Driving Force Racing Wheel क्रम Xbox One                     */
/* ------------------------------------------------------------------------- */

#घोषणा HIDPP_PAGE_G920_FORCE_FEEDBACK			0x8123

अटल पूर्णांक g920_ff_set_स्वतःcenter(काष्ठा hidpp_device *hidpp,
				  काष्ठा hidpp_ff_निजी_data *data)
अणु
	काष्ठा hidpp_report response;
	u8 params[HIDPP_AUTOCENTER_PARAMS_LENGTH] = अणु
		[1] = HIDPP_FF_EFFECT_SPRING | HIDPP_FF_EFFECT_AUTOSTART,
	पूर्ण;
	पूर्णांक ret;

	/* initialize with zero स्वतःcenter to get wheel in usable state */

	dbg_hid("Setting autocenter to 0.\n");
	ret = hidpp_send_fap_command_sync(hidpp, data->feature_index,
					  HIDPP_FF_DOWNLOAD_EFFECT,
					  params, ARRAY_SIZE(params),
					  &response);
	अगर (ret)
		hid_warn(hidpp->hid_dev, "Failed to autocenter device!\n");
	अन्यथा
		data->slot_स्वतःcenter = response.fap.params[0];

	वापस ret;
पूर्ण

अटल पूर्णांक g920_get_config(काष्ठा hidpp_device *hidpp,
			   काष्ठा hidpp_ff_निजी_data *data)
अणु
	काष्ठा hidpp_report response;
	u8 feature_type;
	पूर्णांक ret;

	स_रखो(data, 0, माप(*data));

	/* Find feature and store क्रम later use */
	ret = hidpp_root_get_feature(hidpp, HIDPP_PAGE_G920_FORCE_FEEDBACK,
				     &data->feature_index, &feature_type);
	अगर (ret)
		वापस ret;

	/* Read number of slots available in device */
	ret = hidpp_send_fap_command_sync(hidpp, data->feature_index,
					  HIDPP_FF_GET_INFO,
					  शून्य, 0,
					  &response);
	अगर (ret) अणु
		अगर (ret < 0)
			वापस ret;
		hid_err(hidpp->hid_dev,
			"%s: received protocol error 0x%02x\n", __func__, ret);
		वापस -EPROTO;
	पूर्ण

	data->num_effects = response.fap.params[0] - HIDPP_FF_RESERVED_SLOTS;

	/* reset all क्रमces */
	ret = hidpp_send_fap_command_sync(hidpp, data->feature_index,
					  HIDPP_FF_RESET_ALL,
					  शून्य, 0,
					  &response);
	अगर (ret)
		hid_warn(hidpp->hid_dev, "Failed to reset all forces!\n");

	ret = hidpp_send_fap_command_sync(hidpp, data->feature_index,
					  HIDPP_FF_GET_APERTURE,
					  शून्य, 0,
					  &response);
	अगर (ret) अणु
		hid_warn(hidpp->hid_dev,
			 "Failed to read range from device!\n");
	पूर्ण
	data->range = ret ?
		900 : get_unaligned_be16(&response.fap.params[0]);

	/* Read the current gain values */
	ret = hidpp_send_fap_command_sync(hidpp, data->feature_index,
					  HIDPP_FF_GET_GLOBAL_GAINS,
					  शून्य, 0,
					  &response);
	अगर (ret)
		hid_warn(hidpp->hid_dev,
			 "Failed to read gain values from device!\n");
	data->gain = ret ?
		0xffff : get_unaligned_be16(&response.fap.params[0]);

	/* ignore boost value at response.fap.params[2] */

	वापस g920_ff_set_स्वतःcenter(hidpp, data);
पूर्ण

/* -------------------------------------------------------------------------- */
/* Logitech Dinovo Mini keyboard with builtin touchpad                        */
/* -------------------------------------------------------------------------- */
#घोषणा DINOVO_MINI_PRODUCT_ID		0xb30c

अटल पूर्णांक lg_dinovo_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_LOGIVENDOR)
		वापस 0;

	चयन (usage->hid & HID_USAGE) अणु
	हाल 0x00d: lg_map_key_clear(KEY_MEDIA);	अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/* -------------------------------------------------------------------------- */
/* HID++1.0 devices which use HID++ reports क्रम their wheels                  */
/* -------------------------------------------------------------------------- */
अटल पूर्णांक hidpp10_wheel_connect(काष्ठा hidpp_device *hidpp)
अणु
	वापस hidpp10_set_रेजिस्टर(hidpp, HIDPP_REG_ENABLE_REPORTS, 0,
			HIDPP_ENABLE_WHEEL_REPORT | HIDPP_ENABLE_HWHEEL_REPORT,
			HIDPP_ENABLE_WHEEL_REPORT | HIDPP_ENABLE_HWHEEL_REPORT);
पूर्ण

अटल पूर्णांक hidpp10_wheel_raw_event(काष्ठा hidpp_device *hidpp,
				   u8 *data, पूर्णांक size)
अणु
	s8 value, hvalue;

	अगर (!hidpp->input)
		वापस -EINVAL;

	अगर (size < 7)
		वापस 0;

	अगर (data[0] != REPORT_ID_HIDPP_SHORT || data[2] != HIDPP_SUB_ID_ROLLER)
		वापस 0;

	value = data[3];
	hvalue = data[4];

	input_report_rel(hidpp->input, REL_WHEEL, value);
	input_report_rel(hidpp->input, REL_WHEEL_HI_RES, value * 120);
	input_report_rel(hidpp->input, REL_HWHEEL, hvalue);
	input_report_rel(hidpp->input, REL_HWHEEL_HI_RES, hvalue * 120);
	input_sync(hidpp->input);

	वापस 1;
पूर्ण

अटल व्योम hidpp10_wheel_populate_input(काष्ठा hidpp_device *hidpp,
					 काष्ठा input_dev *input_dev)
अणु
	__set_bit(EV_REL, input_dev->evbit);
	__set_bit(REL_WHEEL, input_dev->relbit);
	__set_bit(REL_WHEEL_HI_RES, input_dev->relbit);
	__set_bit(REL_HWHEEL, input_dev->relbit);
	__set_bit(REL_HWHEEL_HI_RES, input_dev->relbit);
पूर्ण

/* -------------------------------------------------------------------------- */
/* HID++1.0 mice which use HID++ reports क्रम extra mouse buttons              */
/* -------------------------------------------------------------------------- */
अटल पूर्णांक hidpp10_extra_mouse_buttons_connect(काष्ठा hidpp_device *hidpp)
अणु
	वापस hidpp10_set_रेजिस्टर(hidpp, HIDPP_REG_ENABLE_REPORTS, 0,
				    HIDPP_ENABLE_MOUSE_EXTRA_BTN_REPORT,
				    HIDPP_ENABLE_MOUSE_EXTRA_BTN_REPORT);
पूर्ण

अटल पूर्णांक hidpp10_extra_mouse_buttons_raw_event(काष्ठा hidpp_device *hidpp,
				    u8 *data, पूर्णांक size)
अणु
	पूर्णांक i;

	अगर (!hidpp->input)
		वापस -EINVAL;

	अगर (size < 7)
		वापस 0;

	अगर (data[0] != REPORT_ID_HIDPP_SHORT ||
	    data[2] != HIDPP_SUB_ID_MOUSE_EXTRA_BTNS)
		वापस 0;

	/*
	 * Buttons are either delivered through the regular mouse report *or*
	 * through the extra buttons report. At least क्रम button 6 how it is
	 * delivered dअगरfers per receiver firmware version. Even receivers with
	 * the same usb-id show dअगरferent behavior, so we handle both हालs.
	 */
	क्रम (i = 0; i < 8; i++)
		input_report_key(hidpp->input, BTN_MOUSE + i,
				 (data[3] & (1 << i)));

	/* Some mice report events on button 9+, use BTN_MISC */
	क्रम (i = 0; i < 8; i++)
		input_report_key(hidpp->input, BTN_MISC + i,
				 (data[4] & (1 << i)));

	input_sync(hidpp->input);
	वापस 1;
पूर्ण

अटल व्योम hidpp10_extra_mouse_buttons_populate_input(
			काष्ठा hidpp_device *hidpp, काष्ठा input_dev *input_dev)
अणु
	/* BTN_MOUSE - BTN_MOUSE+7 are set alपढ़ोy by the descriptor */
	__set_bit(BTN_0, input_dev->keybit);
	__set_bit(BTN_1, input_dev->keybit);
	__set_bit(BTN_2, input_dev->keybit);
	__set_bit(BTN_3, input_dev->keybit);
	__set_bit(BTN_4, input_dev->keybit);
	__set_bit(BTN_5, input_dev->keybit);
	__set_bit(BTN_6, input_dev->keybit);
	__set_bit(BTN_7, input_dev->keybit);
पूर्ण

/* -------------------------------------------------------------------------- */
/* HID++1.0 kbds which only report 0x10xx consumer usages through sub-id 0x03 */
/* -------------------------------------------------------------------------- */

/* Find the consumer-page input report desc and change Maximums to 0x107f */
अटल u8 *hidpp10_consumer_keys_report_fixup(काष्ठा hidpp_device *hidpp,
					      u8 *_rdesc, अचिन्हित पूर्णांक *rsize)
अणु
	/* Note 0 terminated so we can use strnstr to search क्रम this. */
	अटल स्थिर अक्षर consumer_rdesc_start[] = अणु
		0x05, 0x0C,	/* USAGE_PAGE (Consumer Devices)       */
		0x09, 0x01,	/* USAGE (Consumer Control)            */
		0xA1, 0x01,	/* COLLECTION (Application)            */
		0x85, 0x03,	/* REPORT_ID = 3                       */
		0x75, 0x10,	/* REPORT_SIZE (16)                    */
		0x95, 0x02,	/* REPORT_COUNT (2)                    */
		0x15, 0x01,	/* LOGICAL_MIN (1)                     */
		0x26, 0x00	/* LOGICAL_MAX (...                    */
	पूर्ण;
	अक्षर *consumer_rdesc, *rdesc = (अक्षर *)_rdesc;
	अचिन्हित पूर्णांक size;

	consumer_rdesc = strnstr(rdesc, consumer_rdesc_start, *rsize);
	size = *rsize - (consumer_rdesc - rdesc);
	अगर (consumer_rdesc && size >= 25) अणु
		consumer_rdesc[15] = 0x7f;
		consumer_rdesc[16] = 0x10;
		consumer_rdesc[20] = 0x7f;
		consumer_rdesc[21] = 0x10;
	पूर्ण
	वापस _rdesc;
पूर्ण

अटल पूर्णांक hidpp10_consumer_keys_connect(काष्ठा hidpp_device *hidpp)
अणु
	वापस hidpp10_set_रेजिस्टर(hidpp, HIDPP_REG_ENABLE_REPORTS, 0,
				    HIDPP_ENABLE_CONSUMER_REPORT,
				    HIDPP_ENABLE_CONSUMER_REPORT);
पूर्ण

अटल पूर्णांक hidpp10_consumer_keys_raw_event(काष्ठा hidpp_device *hidpp,
					   u8 *data, पूर्णांक size)
अणु
	u8 consumer_report[5];

	अगर (size < 7)
		वापस 0;

	अगर (data[0] != REPORT_ID_HIDPP_SHORT ||
	    data[2] != HIDPP_SUB_ID_CONSUMER_VENDOR_KEYS)
		वापस 0;

	/*
	 * Build a normal consumer report (3) out of the data, this detour
	 * is necessary to get some keyboards to report their 0x10xx usages.
	 */
	consumer_report[0] = 0x03;
	स_नकल(&consumer_report[1], &data[3], 4);
	/* We are called from atomic context */
	hid_report_raw_event(hidpp->hid_dev, HID_INPUT_REPORT,
			     consumer_report, 5, 1);

	वापस 1;
पूर्ण

/* -------------------------------------------------------------------------- */
/* High-resolution scroll wheels                                              */
/* -------------------------------------------------------------------------- */

अटल पूर्णांक hi_res_scroll_enable(काष्ठा hidpp_device *hidpp)
अणु
	पूर्णांक ret;
	u8 multiplier = 1;

	अगर (hidpp->quirks & HIDPP_QUIRK_HI_RES_SCROLL_X2121) अणु
		ret = hidpp_hrw_set_wheel_mode(hidpp, false, true, false);
		अगर (ret == 0)
			ret = hidpp_hrw_get_wheel_capability(hidpp, &multiplier);
	पूर्ण अन्यथा अगर (hidpp->quirks & HIDPP_QUIRK_HI_RES_SCROLL_X2120) अणु
		ret = hidpp_hrs_set_highres_scrolling_mode(hidpp, true,
							   &multiplier);
	पूर्ण अन्यथा /* अगर (hidpp->quirks & HIDPP_QUIRK_HI_RES_SCROLL_1P0) */ अणु
		ret = hidpp10_enable_scrolling_acceleration(hidpp);
		multiplier = 8;
	पूर्ण
	अगर (ret)
		वापस ret;

	अगर (multiplier == 0)
		multiplier = 1;

	hidpp->vertical_wheel_counter.wheel_multiplier = multiplier;
	hid_dbg(hidpp->hid_dev, "wheel multiplier = %d\n", multiplier);
	वापस 0;
पूर्ण

/* -------------------------------------------------------------------------- */
/* Generic HID++ devices                                                      */
/* -------------------------------------------------------------------------- */

अटल u8 *hidpp_report_fixup(काष्ठा hid_device *hdev, u8 *rdesc,
			      अचिन्हित पूर्णांक *rsize)
अणु
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);

	अगर (!hidpp)
		वापस rdesc;

	/* For 27 MHz keyboards the quirk माला_लो set after hid_parse. */
	अगर (hdev->group == HID_GROUP_LOGITECH_27MHZ_DEVICE ||
	    (hidpp->quirks & HIDPP_QUIRK_HIDPP_CONSUMER_VENDOR_KEYS))
		rdesc = hidpp10_consumer_keys_report_fixup(hidpp, rdesc, rsize);

	वापस rdesc;
पूर्ण

अटल पूर्णांक hidpp_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);

	अगर (!hidpp)
		वापस 0;

	अगर (hidpp->quirks & HIDPP_QUIRK_CLASS_WTP)
		वापस wtp_input_mapping(hdev, hi, field, usage, bit, max);
	अन्यथा अगर (hidpp->quirks & HIDPP_QUIRK_CLASS_M560 &&
			field->application != HID_GD_MOUSE)
		वापस m560_input_mapping(hdev, hi, field, usage, bit, max);

	अगर (hdev->product == DINOVO_MINI_PRODUCT_ID)
		वापस lg_dinovo_input_mapping(hdev, hi, field, usage, bit, max);

	वापस 0;
पूर्ण

अटल पूर्णांक hidpp_input_mapped(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);

	अगर (!hidpp)
		वापस 0;

	/* Ensure that Logitech G920 is not given a शेष fuzz/flat value */
	अगर (hidpp->quirks & HIDPP_QUIRK_CLASS_G920) अणु
		अगर (usage->type == EV_ABS && (usage->code == ABS_X ||
				usage->code == ABS_Y || usage->code == ABS_Z ||
				usage->code == ABS_RZ)) अणु
			field->application = HID_GD_MULTIAXIS;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम hidpp_populate_input(काष्ठा hidpp_device *hidpp,
				 काष्ठा input_dev *input)
अणु
	hidpp->input = input;

	अगर (hidpp->quirks & HIDPP_QUIRK_CLASS_WTP)
		wtp_populate_input(hidpp, input);
	अन्यथा अगर (hidpp->quirks & HIDPP_QUIRK_CLASS_M560)
		m560_populate_input(hidpp, input);

	अगर (hidpp->quirks & HIDPP_QUIRK_HIDPP_WHEELS)
		hidpp10_wheel_populate_input(hidpp, input);

	अगर (hidpp->quirks & HIDPP_QUIRK_HIDPP_EXTRA_MOUSE_BTNS)
		hidpp10_extra_mouse_buttons_populate_input(hidpp, input);
पूर्ण

अटल पूर्णांक hidpp_input_configured(काष्ठा hid_device *hdev,
				काष्ठा hid_input *hidinput)
अणु
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);
	काष्ठा input_dev *input = hidinput->input;

	अगर (!hidpp)
		वापस 0;

	hidpp_populate_input(hidpp, input);

	वापस 0;
पूर्ण

अटल पूर्णांक hidpp_raw_hidpp_event(काष्ठा hidpp_device *hidpp, u8 *data,
		पूर्णांक size)
अणु
	काष्ठा hidpp_report *question = hidpp->send_receive_buf;
	काष्ठा hidpp_report *answer = hidpp->send_receive_buf;
	काष्ठा hidpp_report *report = (काष्ठा hidpp_report *)data;
	पूर्णांक ret;

	/*
	 * If the mutex is locked then we have a pending answer from a
	 * previously sent command.
	 */
	अगर (unlikely(mutex_is_locked(&hidpp->send_mutex))) अणु
		/*
		 * Check क्रम a correct hidpp20 answer or the corresponding
		 * error
		 */
		अगर (hidpp_match_answer(question, report) ||
				hidpp_match_error(question, report)) अणु
			*answer = *report;
			hidpp->answer_available = true;
			wake_up(&hidpp->रुको);
			/*
			 * This was an answer to a command that this driver sent
			 * We वापस 1 to hid-core to aव्योम क्रमwarding the
			 * command upstream as it has been treated by the driver
			 */

			वापस 1;
		पूर्ण
	पूर्ण

	अगर (unlikely(hidpp_report_is_connect_event(hidpp, report))) अणु
		atomic_set(&hidpp->connected,
				!(report->rap.params[0] & (1 << 6)));
		अगर (schedule_work(&hidpp->work) == 0)
			dbg_hid("%s: connect event already queued\n", __func__);
		वापस 1;
	पूर्ण

	अगर (hidpp->capabilities & HIDPP_CAPABILITY_HIDPP20_BATTERY) अणु
		ret = hidpp20_battery_event_1000(hidpp, data, size);
		अगर (ret != 0)
			वापस ret;
		ret = hidpp20_battery_event_1004(hidpp, data, size);
		अगर (ret != 0)
			वापस ret;
		ret = hidpp_solar_battery_event(hidpp, data, size);
		अगर (ret != 0)
			वापस ret;
		ret = hidpp20_battery_voltage_event(hidpp, data, size);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	अगर (hidpp->capabilities & HIDPP_CAPABILITY_HIDPP10_BATTERY) अणु
		ret = hidpp10_battery_event(hidpp, data, size);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	अगर (hidpp->quirks & HIDPP_QUIRK_HIDPP_WHEELS) अणु
		ret = hidpp10_wheel_raw_event(hidpp, data, size);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	अगर (hidpp->quirks & HIDPP_QUIRK_HIDPP_EXTRA_MOUSE_BTNS) अणु
		ret = hidpp10_extra_mouse_buttons_raw_event(hidpp, data, size);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	अगर (hidpp->quirks & HIDPP_QUIRK_HIDPP_CONSUMER_VENDOR_KEYS) अणु
		ret = hidpp10_consumer_keys_raw_event(hidpp, data, size);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hidpp_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
		u8 *data, पूर्णांक size)
अणु
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);
	पूर्णांक ret = 0;

	अगर (!hidpp)
		वापस 0;

	/* Generic HID++ processing. */
	चयन (data[0]) अणु
	हाल REPORT_ID_HIDPP_VERY_LONG:
		अगर (size != hidpp->very_दीर्घ_report_length) अणु
			hid_err(hdev, "received hid++ report of bad size (%d)",
				size);
			वापस 1;
		पूर्ण
		ret = hidpp_raw_hidpp_event(hidpp, data, size);
		अवरोध;
	हाल REPORT_ID_HIDPP_LONG:
		अगर (size != HIDPP_REPORT_LONG_LENGTH) अणु
			hid_err(hdev, "received hid++ report of bad size (%d)",
				size);
			वापस 1;
		पूर्ण
		ret = hidpp_raw_hidpp_event(hidpp, data, size);
		अवरोध;
	हाल REPORT_ID_HIDPP_SHORT:
		अगर (size != HIDPP_REPORT_SHORT_LENGTH) अणु
			hid_err(hdev, "received hid++ report of bad size (%d)",
				size);
			वापस 1;
		पूर्ण
		ret = hidpp_raw_hidpp_event(hidpp, data, size);
		अवरोध;
	पूर्ण

	/* If no report is available क्रम further processing, skip calling
	 * raw_event of subclasses. */
	अगर (ret != 0)
		वापस ret;

	अगर (hidpp->quirks & HIDPP_QUIRK_CLASS_WTP)
		वापस wtp_raw_event(hdev, data, size);
	अन्यथा अगर (hidpp->quirks & HIDPP_QUIRK_CLASS_M560)
		वापस m560_raw_event(hdev, data, size);

	वापस 0;
पूर्ण

अटल पूर्णांक hidpp_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
	काष्ठा hid_usage *usage, __s32 value)
अणु
	/* This function will only be called क्रम scroll events, due to the
	 * restriction imposed in hidpp_usages.
	 */
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);
	काष्ठा hidpp_scroll_counter *counter;

	अगर (!hidpp)
		वापस 0;

	counter = &hidpp->vertical_wheel_counter;
	/* A scroll event may occur beक्रमe the multiplier has been retrieved or
	 * the input device set, or high-res scroll enabling may fail. In such
	 * हालs we must वापस early (falling back to शेष behaviour) to
	 * aव्योम a crash in hidpp_scroll_counter_handle_scroll.
	 */
	अगर (!(hidpp->quirks & HIDPP_QUIRK_HI_RES_SCROLL) || value == 0
	    || hidpp->input == शून्य || counter->wheel_multiplier == 0)
		वापस 0;

	hidpp_scroll_counter_handle_scroll(hidpp->input, counter, value);
	वापस 1;
पूर्ण

अटल पूर्णांक hidpp_initialize_battery(काष्ठा hidpp_device *hidpp)
अणु
	अटल atomic_t battery_no = ATOMIC_INIT(0);
	काष्ठा घातer_supply_config cfg = अणु .drv_data = hidpp पूर्ण;
	काष्ठा घातer_supply_desc *desc = &hidpp->battery.desc;
	क्रमागत घातer_supply_property *battery_props;
	काष्ठा hidpp_battery *battery;
	अचिन्हित पूर्णांक num_battery_props;
	अचिन्हित दीर्घ n;
	पूर्णांक ret;

	अगर (hidpp->battery.ps)
		वापस 0;

	hidpp->battery.feature_index = 0xff;
	hidpp->battery.solar_feature_index = 0xff;
	hidpp->battery.voltage_feature_index = 0xff;

	अगर (hidpp->protocol_major >= 2) अणु
		अगर (hidpp->quirks & HIDPP_QUIRK_CLASS_K750)
			ret = hidpp_solar_request_battery_event(hidpp);
		अन्यथा अणु
			/* we only support one battery feature right now, so let's
			   first check the ones that support battery level first
			   and leave voltage क्रम last */
			ret = hidpp20_query_battery_info_1000(hidpp);
			अगर (ret)
				ret = hidpp20_query_battery_info_1004(hidpp);
			अगर (ret)
				ret = hidpp20_query_battery_voltage_info(hidpp);
		पूर्ण

		अगर (ret)
			वापस ret;
		hidpp->capabilities |= HIDPP_CAPABILITY_HIDPP20_BATTERY;
	पूर्ण अन्यथा अणु
		ret = hidpp10_query_battery_status(hidpp);
		अगर (ret) अणु
			ret = hidpp10_query_battery_mileage(hidpp);
			अगर (ret)
				वापस -ENOENT;
			hidpp->capabilities |= HIDPP_CAPABILITY_BATTERY_MILEAGE;
		पूर्ण अन्यथा अणु
			hidpp->capabilities |= HIDPP_CAPABILITY_BATTERY_LEVEL_STATUS;
		पूर्ण
		hidpp->capabilities |= HIDPP_CAPABILITY_HIDPP10_BATTERY;
	पूर्ण

	battery_props = devm_kmemdup(&hidpp->hid_dev->dev,
				     hidpp_battery_props,
				     माप(hidpp_battery_props),
				     GFP_KERNEL);
	अगर (!battery_props)
		वापस -ENOMEM;

	num_battery_props = ARRAY_SIZE(hidpp_battery_props) - 3;

	अगर (hidpp->capabilities & HIDPP_CAPABILITY_BATTERY_MILEAGE ||
	    hidpp->capabilities & HIDPP_CAPABILITY_BATTERY_PERCENTAGE)
		battery_props[num_battery_props++] =
				POWER_SUPPLY_PROP_CAPACITY;

	अगर (hidpp->capabilities & HIDPP_CAPABILITY_BATTERY_LEVEL_STATUS)
		battery_props[num_battery_props++] =
				POWER_SUPPLY_PROP_CAPACITY_LEVEL;

	अगर (hidpp->capabilities & HIDPP_CAPABILITY_BATTERY_VOLTAGE)
		battery_props[num_battery_props++] =
			POWER_SUPPLY_PROP_VOLTAGE_NOW;

	battery = &hidpp->battery;

	n = atomic_inc_वापस(&battery_no) - 1;
	desc->properties = battery_props;
	desc->num_properties = num_battery_props;
	desc->get_property = hidpp_battery_get_property;
	प्र_लिखो(battery->name, "hidpp_battery_%ld", n);
	desc->name = battery->name;
	desc->type = POWER_SUPPLY_TYPE_BATTERY;
	desc->use_क्रम_apm = 0;

	battery->ps = devm_घातer_supply_रेजिस्टर(&hidpp->hid_dev->dev,
						 &battery->desc,
						 &cfg);
	अगर (IS_ERR(battery->ps))
		वापस PTR_ERR(battery->ps);

	घातer_supply_घातers(battery->ps, &hidpp->hid_dev->dev);

	वापस ret;
पूर्ण

अटल व्योम hidpp_overग_लिखो_name(काष्ठा hid_device *hdev)
अणु
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);
	अक्षर *name;

	अगर (hidpp->protocol_major < 2)
		वापस;

	name = hidpp_get_device_name(hidpp);

	अगर (!name) अणु
		hid_err(hdev, "unable to retrieve the name of the device");
	पूर्ण अन्यथा अणु
		dbg_hid("HID++: Got name: %s\n", name);
		snम_लिखो(hdev->name, माप(hdev->name), "%s", name);
	पूर्ण

	kमुक्त(name);
पूर्ण

अटल पूर्णांक hidpp_input_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);

	वापस hid_hw_खोलो(hid);
पूर्ण

अटल व्योम hidpp_input_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);

	hid_hw_बंद(hid);
पूर्ण

अटल काष्ठा input_dev *hidpp_allocate_input(काष्ठा hid_device *hdev)
अणु
	काष्ठा input_dev *input_dev = devm_input_allocate_device(&hdev->dev);
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);

	अगर (!input_dev)
		वापस शून्य;

	input_set_drvdata(input_dev, hdev);
	input_dev->खोलो = hidpp_input_खोलो;
	input_dev->बंद = hidpp_input_बंद;

	input_dev->name = hidpp->name;
	input_dev->phys = hdev->phys;
	input_dev->uniq = hdev->uniq;
	input_dev->id.bustype = hdev->bus;
	input_dev->id.venकरोr  = hdev->venकरोr;
	input_dev->id.product = hdev->product;
	input_dev->id.version = hdev->version;
	input_dev->dev.parent = &hdev->dev;

	वापस input_dev;
पूर्ण

अटल व्योम hidpp_connect_event(काष्ठा hidpp_device *hidpp)
अणु
	काष्ठा hid_device *hdev = hidpp->hid_dev;
	पूर्णांक ret = 0;
	bool connected = atomic_पढ़ो(&hidpp->connected);
	काष्ठा input_dev *input;
	अक्षर *name, *devm_name;

	अगर (!connected) अणु
		अगर (hidpp->battery.ps) अणु
			hidpp->battery.online = false;
			hidpp->battery.status = POWER_SUPPLY_STATUS_UNKNOWN;
			hidpp->battery.level = POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;
			घातer_supply_changed(hidpp->battery.ps);
		पूर्ण
		वापस;
	पूर्ण

	अगर (hidpp->quirks & HIDPP_QUIRK_CLASS_WTP) अणु
		ret = wtp_connect(hdev, connected);
		अगर (ret)
			वापस;
	पूर्ण अन्यथा अगर (hidpp->quirks & HIDPP_QUIRK_CLASS_M560) अणु
		ret = m560_send_config_command(hdev, connected);
		अगर (ret)
			वापस;
	पूर्ण अन्यथा अगर (hidpp->quirks & HIDPP_QUIRK_CLASS_K400) अणु
		ret = k400_connect(hdev, connected);
		अगर (ret)
			वापस;
	पूर्ण

	अगर (hidpp->quirks & HIDPP_QUIRK_HIDPP_WHEELS) अणु
		ret = hidpp10_wheel_connect(hidpp);
		अगर (ret)
			वापस;
	पूर्ण

	अगर (hidpp->quirks & HIDPP_QUIRK_HIDPP_EXTRA_MOUSE_BTNS) अणु
		ret = hidpp10_extra_mouse_buttons_connect(hidpp);
		अगर (ret)
			वापस;
	पूर्ण

	अगर (hidpp->quirks & HIDPP_QUIRK_HIDPP_CONSUMER_VENDOR_KEYS) अणु
		ret = hidpp10_consumer_keys_connect(hidpp);
		अगर (ret)
			वापस;
	पूर्ण

	/* the device is alपढ़ोy connected, we can ask क्रम its name and
	 * protocol */
	अगर (!hidpp->protocol_major) अणु
		ret = hidpp_root_get_protocol_version(hidpp);
		अगर (ret) अणु
			hid_err(hdev, "Can not get the protocol version.\n");
			वापस;
		पूर्ण
	पूर्ण

	अगर (hidpp->name == hdev->name && hidpp->protocol_major >= 2) अणु
		name = hidpp_get_device_name(hidpp);
		अगर (name) अणु
			devm_name = devm_kaप्र_लिखो(&hdev->dev, GFP_KERNEL,
						   "%s", name);
			kमुक्त(name);
			अगर (!devm_name)
				वापस;

			hidpp->name = devm_name;
		पूर्ण
	पूर्ण

	hidpp_initialize_battery(hidpp);

	/* क्रमward current battery state */
	अगर (hidpp->capabilities & HIDPP_CAPABILITY_HIDPP10_BATTERY) अणु
		hidpp10_enable_battery_reporting(hidpp);
		अगर (hidpp->capabilities & HIDPP_CAPABILITY_BATTERY_MILEAGE)
			hidpp10_query_battery_mileage(hidpp);
		अन्यथा
			hidpp10_query_battery_status(hidpp);
	पूर्ण अन्यथा अगर (hidpp->capabilities & HIDPP_CAPABILITY_HIDPP20_BATTERY) अणु
		अगर (hidpp->capabilities & HIDPP_CAPABILITY_BATTERY_VOLTAGE)
			hidpp20_query_battery_voltage_info(hidpp);
		अन्यथा अगर (hidpp->capabilities & HIDPP_CAPABILITY_UNIFIED_BATTERY)
			hidpp20_query_battery_info_1004(hidpp);
		अन्यथा
			hidpp20_query_battery_info_1000(hidpp);
	पूर्ण
	अगर (hidpp->battery.ps)
		घातer_supply_changed(hidpp->battery.ps);

	अगर (hidpp->quirks & HIDPP_QUIRK_HI_RES_SCROLL)
		hi_res_scroll_enable(hidpp);

	अगर (!(hidpp->quirks & HIDPP_QUIRK_NO_HIDINPUT) || hidpp->delayed_input)
		/* अगर the input nodes are alपढ़ोy created, we can stop now */
		वापस;

	input = hidpp_allocate_input(hdev);
	अगर (!input) अणु
		hid_err(hdev, "cannot allocate new input device: %d\n", ret);
		वापस;
	पूर्ण

	hidpp_populate_input(hidpp, input);

	ret = input_रेजिस्टर_device(input);
	अगर (ret)
		input_मुक्त_device(input);

	hidpp->delayed_input = input;
पूर्ण

अटल DEVICE_ATTR(builtin_घातer_supply, 0000, शून्य, शून्य);

अटल काष्ठा attribute *sysfs_attrs[] = अणु
	&dev_attr_builtin_घातer_supply.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ps_attribute_group = अणु
	.attrs = sysfs_attrs
पूर्ण;

अटल पूर्णांक hidpp_get_report_length(काष्ठा hid_device *hdev, पूर्णांक id)
अणु
	काष्ठा hid_report_क्रमागत *re;
	काष्ठा hid_report *report;

	re = &(hdev->report_क्रमागत[HID_OUTPUT_REPORT]);
	report = re->report_id_hash[id];
	अगर (!report)
		वापस 0;

	वापस report->field[0]->report_count + 1;
पूर्ण

अटल u8 hidpp_validate_device(काष्ठा hid_device *hdev)
अणु
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);
	पूर्णांक id, report_length;
	u8 supported_reports = 0;

	id = REPORT_ID_HIDPP_SHORT;
	report_length = hidpp_get_report_length(hdev, id);
	अगर (report_length) अणु
		अगर (report_length < HIDPP_REPORT_SHORT_LENGTH)
			जाओ bad_device;

		supported_reports |= HIDPP_REPORT_SHORT_SUPPORTED;
	पूर्ण

	id = REPORT_ID_HIDPP_LONG;
	report_length = hidpp_get_report_length(hdev, id);
	अगर (report_length) अणु
		अगर (report_length < HIDPP_REPORT_LONG_LENGTH)
			जाओ bad_device;

		supported_reports |= HIDPP_REPORT_LONG_SUPPORTED;
	पूर्ण

	id = REPORT_ID_HIDPP_VERY_LONG;
	report_length = hidpp_get_report_length(hdev, id);
	अगर (report_length) अणु
		अगर (report_length < HIDPP_REPORT_LONG_LENGTH ||
		    report_length > HIDPP_REPORT_VERY_दीर्घ_उच्च_LENGTH)
			जाओ bad_device;

		supported_reports |= HIDPP_REPORT_VERY_LONG_SUPPORTED;
		hidpp->very_दीर्घ_report_length = report_length;
	पूर्ण

	वापस supported_reports;

bad_device:
	hid_warn(hdev, "not enough values in hidpp report %d\n", id);
	वापस false;
पूर्ण

अटल bool hidpp_application_equals(काष्ठा hid_device *hdev,
				     अचिन्हित पूर्णांक application)
अणु
	काष्ठा list_head *report_list;
	काष्ठा hid_report *report;

	report_list = &hdev->report_क्रमागत[HID_INPUT_REPORT].report_list;
	report = list_first_entry_or_null(report_list, काष्ठा hid_report, list);
	वापस report && report->application == application;
पूर्ण

अटल पूर्णांक hidpp_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा hidpp_device *hidpp;
	पूर्णांक ret;
	bool connected;
	अचिन्हित पूर्णांक connect_mask = HID_CONNECT_DEFAULT;
	काष्ठा hidpp_ff_निजी_data data;

	/* report_fixup needs drvdata to be set beक्रमe we call hid_parse */
	hidpp = devm_kzalloc(&hdev->dev, माप(*hidpp), GFP_KERNEL);
	अगर (!hidpp)
		वापस -ENOMEM;

	hidpp->hid_dev = hdev;
	hidpp->name = hdev->name;
	hidpp->quirks = id->driver_data;
	hid_set_drvdata(hdev, hidpp);

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "%s:parse failed\n", __func__);
		वापस ret;
	पूर्ण

	/*
	 * Make sure the device is HID++ capable, otherwise treat as generic HID
	 */
	hidpp->supported_reports = hidpp_validate_device(hdev);

	अगर (!hidpp->supported_reports) अणु
		hid_set_drvdata(hdev, शून्य);
		devm_kमुक्त(&hdev->dev, hidpp);
		वापस hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	पूर्ण

	अगर (id->group == HID_GROUP_LOGITECH_DJ_DEVICE)
		hidpp->quirks |= HIDPP_QUIRK_UNIFYING;

	अगर (id->group == HID_GROUP_LOGITECH_27MHZ_DEVICE &&
	    hidpp_application_equals(hdev, HID_GD_MOUSE))
		hidpp->quirks |= HIDPP_QUIRK_HIDPP_WHEELS |
				 HIDPP_QUIRK_HIDPP_EXTRA_MOUSE_BTNS;

	अगर (id->group == HID_GROUP_LOGITECH_27MHZ_DEVICE &&
	    hidpp_application_equals(hdev, HID_GD_KEYBOARD))
		hidpp->quirks |= HIDPP_QUIRK_HIDPP_CONSUMER_VENDOR_KEYS;

	अगर (disable_raw_mode) अणु
		hidpp->quirks &= ~HIDPP_QUIRK_CLASS_WTP;
		hidpp->quirks &= ~HIDPP_QUIRK_NO_HIDINPUT;
	पूर्ण

	अगर (hidpp->quirks & HIDPP_QUIRK_CLASS_WTP) अणु
		ret = wtp_allocate(hdev, id);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (hidpp->quirks & HIDPP_QUIRK_CLASS_K400) अणु
		ret = k400_allocate(hdev);
		अगर (ret)
			वापस ret;
	पूर्ण

	INIT_WORK(&hidpp->work, delayed_work_cb);
	mutex_init(&hidpp->send_mutex);
	init_रुकोqueue_head(&hidpp->रुको);

	/* indicates we are handling the battery properties in the kernel */
	ret = sysfs_create_group(&hdev->dev.kobj, &ps_attribute_group);
	अगर (ret)
		hid_warn(hdev, "Cannot allocate sysfs group for %s\n",
			 hdev->name);

	/*
	 * Plain USB connections need to actually call start and खोलो
	 * on the transport driver to allow incoming data.
	 */
	ret = hid_hw_start(hdev, 0);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ hid_hw_start_fail;
	पूर्ण

	ret = hid_hw_खोलो(hdev);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "%s:hid_hw_open returned error:%d\n",
			__func__, ret);
		जाओ hid_hw_खोलो_fail;
	पूर्ण

	/* Allow incoming packets */
	hid_device_io_start(hdev);

	अगर (hidpp->quirks & HIDPP_QUIRK_UNIFYING)
		hidpp_unअगरying_init(hidpp);

	connected = hidpp_root_get_protocol_version(hidpp) == 0;
	atomic_set(&hidpp->connected, connected);
	अगर (!(hidpp->quirks & HIDPP_QUIRK_UNIFYING)) अणु
		अगर (!connected) अणु
			ret = -ENODEV;
			hid_err(hdev, "Device not connected");
			जाओ hid_hw_init_fail;
		पूर्ण

		hidpp_overग_लिखो_name(hdev);
	पूर्ण

	अगर (connected && hidpp->protocol_major >= 2) अणु
		ret = hidpp_set_wireless_feature_index(hidpp);
		अगर (ret == -ENOENT)
			hidpp->wireless_feature_index = 0;
		अन्यथा अगर (ret)
			जाओ hid_hw_init_fail;
	पूर्ण

	अगर (connected && (hidpp->quirks & HIDPP_QUIRK_CLASS_WTP)) अणु
		ret = wtp_get_config(hidpp);
		अगर (ret)
			जाओ hid_hw_init_fail;
	पूर्ण अन्यथा अगर (connected && (hidpp->quirks & HIDPP_QUIRK_CLASS_G920)) अणु
		ret = g920_get_config(hidpp, &data);
		अगर (ret)
			जाओ hid_hw_init_fail;
	पूर्ण

	hidpp_connect_event(hidpp);

	/* Reset the HID node state */
	hid_device_io_stop(hdev);
	hid_hw_बंद(hdev);
	hid_hw_stop(hdev);

	अगर (hidpp->quirks & HIDPP_QUIRK_NO_HIDINPUT)
		connect_mask &= ~HID_CONNECT_HIDINPUT;

	/* Now export the actual inमाला_दो and hidraw nodes to the world */
	ret = hid_hw_start(hdev, connect_mask);
	अगर (ret) अणु
		hid_err(hdev, "%s:hid_hw_start returned error\n", __func__);
		जाओ hid_hw_start_fail;
	पूर्ण

	अगर (hidpp->quirks & HIDPP_QUIRK_CLASS_G920) अणु
		ret = hidpp_ff_init(hidpp, &data);
		अगर (ret)
			hid_warn(hidpp->hid_dev,
		     "Unable to initialize force feedback support, errno %d\n",
				 ret);
	पूर्ण

	वापस ret;

hid_hw_init_fail:
	hid_hw_बंद(hdev);
hid_hw_खोलो_fail:
	hid_hw_stop(hdev);
hid_hw_start_fail:
	sysfs_हटाओ_group(&hdev->dev.kobj, &ps_attribute_group);
	cancel_work_sync(&hidpp->work);
	mutex_destroy(&hidpp->send_mutex);
	वापस ret;
पूर्ण

अटल व्योम hidpp_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा hidpp_device *hidpp = hid_get_drvdata(hdev);

	अगर (!hidpp)
		वापस hid_hw_stop(hdev);

	sysfs_हटाओ_group(&hdev->dev.kobj, &ps_attribute_group);

	hid_hw_stop(hdev);
	cancel_work_sync(&hidpp->work);
	mutex_destroy(&hidpp->send_mutex);
पूर्ण

#घोषणा LDJ_DEVICE(product) \
	HID_DEVICE(BUS_USB, HID_GROUP_LOGITECH_DJ_DEVICE, \
		   USB_VENDOR_ID_LOGITECH, (product))

#घोषणा L27MHZ_DEVICE(product) \
	HID_DEVICE(BUS_USB, HID_GROUP_LOGITECH_27MHZ_DEVICE, \
		   USB_VENDOR_ID_LOGITECH, (product))

अटल स्थिर काष्ठा hid_device_id hidpp_devices[] = अणु
	अणु /* wireless touchpad */
	  LDJ_DEVICE(0x4011),
	  .driver_data = HIDPP_QUIRK_CLASS_WTP | HIDPP_QUIRK_DELAYED_INIT |
			 HIDPP_QUIRK_WTP_PHYSICAL_BUTTONS पूर्ण,
	अणु /* wireless touchpad T650 */
	  LDJ_DEVICE(0x4101),
	  .driver_data = HIDPP_QUIRK_CLASS_WTP | HIDPP_QUIRK_DELAYED_INIT पूर्ण,
	अणु /* wireless touchpad T651 */
	  HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_LOGITECH_T651),
	  .driver_data = HIDPP_QUIRK_CLASS_WTP पूर्ण,
	अणु /* Mouse Logitech Anywhere MX */
	  LDJ_DEVICE(0x1017), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_1P0 पूर्ण,
	अणु /* Mouse Logitech Cube */
	  LDJ_DEVICE(0x4010), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2120 पूर्ण,
	अणु /* Mouse Logitech M335 */
	  LDJ_DEVICE(0x4050), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणु /* Mouse Logitech M515 */
	  LDJ_DEVICE(0x4007), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2120 पूर्ण,
	अणु /* Mouse logitech M560 */
	  LDJ_DEVICE(0x402d),
	  .driver_data = HIDPP_QUIRK_DELAYED_INIT | HIDPP_QUIRK_CLASS_M560
		| HIDPP_QUIRK_HI_RES_SCROLL_X2120 पूर्ण,
	अणु /* Mouse Logitech M705 (firmware RQM17) */
	  LDJ_DEVICE(0x101b), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_1P0 पूर्ण,
	अणु /* Mouse Logitech M705 (firmware RQM67) */
	  LDJ_DEVICE(0x406d), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणु /* Mouse Logitech M720 */
	  LDJ_DEVICE(0x405e), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणु /* Mouse Logitech MX Anywhere 2 */
	  LDJ_DEVICE(0x404a), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणु LDJ_DEVICE(0x4072), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणु LDJ_DEVICE(0xb013), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणु LDJ_DEVICE(0xb018), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणु LDJ_DEVICE(0xb01f), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणु /* Mouse Logitech MX Anywhere 2S */
	  LDJ_DEVICE(0x406a), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणु /* Mouse Logitech MX Master */
	  LDJ_DEVICE(0x4041), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणु LDJ_DEVICE(0x4060), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणु LDJ_DEVICE(0x4071), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणु /* Mouse Logitech MX Master 2S */
	  LDJ_DEVICE(0x4069), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणु /* Mouse Logitech MX Master 3 */
	  LDJ_DEVICE(0x4082), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणु /* Mouse Logitech Perक्रमmance MX */
	  LDJ_DEVICE(0x101a), .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_1P0 पूर्ण,
	अणु /* Keyboard logitech K400 */
	  LDJ_DEVICE(0x4024),
	  .driver_data = HIDPP_QUIRK_CLASS_K400 पूर्ण,
	अणु /* Solar Keyboard Logitech K750 */
	  LDJ_DEVICE(0x4002),
	  .driver_data = HIDPP_QUIRK_CLASS_K750 पूर्ण,
	अणु /* Keyboard MX5000 (Bluetooth-receiver in HID proxy mode) */
	  LDJ_DEVICE(0xb305),
	  .driver_data = HIDPP_QUIRK_HIDPP_CONSUMER_VENDOR_KEYS पूर्ण,
	अणु /* Dinovo Edge (Bluetooth-receiver in HID proxy mode) */
	  LDJ_DEVICE(0xb309),
	  .driver_data = HIDPP_QUIRK_HIDPP_CONSUMER_VENDOR_KEYS पूर्ण,
	अणु /* Keyboard MX5500 (Bluetooth-receiver in HID proxy mode) */
	  LDJ_DEVICE(0xb30b),
	  .driver_data = HIDPP_QUIRK_HIDPP_CONSUMER_VENDOR_KEYS पूर्ण,

	अणु LDJ_DEVICE(HID_ANY_ID) पूर्ण,

	अणु /* Keyboard LX501 (Y-RR53) */
	  L27MHZ_DEVICE(0x0049),
	  .driver_data = HIDPP_QUIRK_KBD_ZOOM_WHEEL पूर्ण,
	अणु /* Keyboard MX3000 (Y-RAM74) */
	  L27MHZ_DEVICE(0x0057),
	  .driver_data = HIDPP_QUIRK_KBD_SCROLL_WHEEL पूर्ण,
	अणु /* Keyboard MX3200 (Y-RAV80) */
	  L27MHZ_DEVICE(0x005c),
	  .driver_data = HIDPP_QUIRK_KBD_ZOOM_WHEEL पूर्ण,
	अणु /* S510 Media Remote */
	  L27MHZ_DEVICE(0x00fe),
	  .driver_data = HIDPP_QUIRK_KBD_SCROLL_WHEEL पूर्ण,

	अणु L27MHZ_DEVICE(HID_ANY_ID) पूर्ण,

	अणु /* Logitech G403 Wireless Gaming Mouse over USB */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, 0xC082) पूर्ण,
	अणु /* Logitech G703 Gaming Mouse over USB */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, 0xC087) पूर्ण,
	अणु /* Logitech G703 Hero Gaming Mouse over USB */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, 0xC090) पूर्ण,
	अणु /* Logitech G900 Gaming Mouse over USB */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, 0xC081) पूर्ण,
	अणु /* Logitech G903 Gaming Mouse over USB */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, 0xC086) पूर्ण,
	अणु /* Logitech G903 Hero Gaming Mouse over USB */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, 0xC091) पूर्ण,
	अणु /* Logitech G920 Wheel over USB */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_G920_WHEEL),
		.driver_data = HIDPP_QUIRK_CLASS_G920 | HIDPP_QUIRK_FORCE_OUTPUT_REPORTSपूर्ण,
	अणु /* Logitech G Pro Gaming Mouse over USB */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, 0xC088) पूर्ण,

	अणु /* MX5000 keyboard over Bluetooth */
	  HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_LOGITECH, 0xb305),
	  .driver_data = HIDPP_QUIRK_HIDPP_CONSUMER_VENDOR_KEYS पूर्ण,
	अणु /* Dinovo Edge keyboard over Bluetooth */
	  HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_LOGITECH, 0xb309),
	  .driver_data = HIDPP_QUIRK_HIDPP_CONSUMER_VENDOR_KEYS पूर्ण,
	अणु /* MX5500 keyboard over Bluetooth */
	  HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_LOGITECH, 0xb30b),
	  .driver_data = HIDPP_QUIRK_HIDPP_CONSUMER_VENDOR_KEYS पूर्ण,
	अणु /* M-RCQ142 V470 Cordless Laser Mouse over Bluetooth */
	  HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_LOGITECH, 0xb008) पूर्ण,
	अणु /* MX Master mouse over Bluetooth */
	  HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_LOGITECH, 0xb012),
	  .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणु /* MX Ergo trackball over Bluetooth */
	  HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_LOGITECH, 0xb01d) पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_LOGITECH, 0xb01e),
	  .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणु /* MX Master 3 mouse over Bluetooth */
	  HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_LOGITECH, 0xb023),
	  .driver_data = HIDPP_QUIRK_HI_RES_SCROLL_X2121 पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, hidpp_devices);

अटल स्थिर काष्ठा hid_usage_id hidpp_usages[] = अणु
	अणु HID_GD_WHEEL, EV_REL, REL_WHEEL_HI_RES पूर्ण,
	अणु HID_ANY_ID - 1, HID_ANY_ID - 1, HID_ANY_ID - 1पूर्ण
पूर्ण;

अटल काष्ठा hid_driver hidpp_driver = अणु
	.name = "logitech-hidpp-device",
	.id_table = hidpp_devices,
	.report_fixup = hidpp_report_fixup,
	.probe = hidpp_probe,
	.हटाओ = hidpp_हटाओ,
	.raw_event = hidpp_raw_event,
	.usage_table = hidpp_usages,
	.event = hidpp_event,
	.input_configured = hidpp_input_configured,
	.input_mapping = hidpp_input_mapping,
	.input_mapped = hidpp_input_mapped,
पूर्ण;

module_hid_driver(hidpp_driver);
