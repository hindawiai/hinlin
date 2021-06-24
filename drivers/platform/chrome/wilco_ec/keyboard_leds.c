<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Keyboard backlight LED driver क्रम the Wilco Embedded Controller
 *
 * Copyright 2019 Google LLC
 *
 * Since the EC will never change the backlight level of its own accord,
 * we करोn't need to implement a brightness_get() method.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_data/wilco-ec.h>
#समावेश <linux/slab.h>

#घोषणा WILCO_EC_COMMAND_KBBL		0x75
#घोषणा WILCO_KBBL_MODE_FLAG_PWM	BIT(1)	/* Set brightness by percent. */
#घोषणा WILCO_KBBL_DEFAULT_BRIGHTNESS   0

काष्ठा wilco_keyboard_leds अणु
	काष्ठा wilco_ec_device *ec;
	काष्ठा led_classdev keyboard;
पूर्ण;

क्रमागत wilco_kbbl_subcommand अणु
	WILCO_KBBL_SUBCMD_GET_FEATURES = 0x00,
	WILCO_KBBL_SUBCMD_GET_STATE    = 0x01,
	WILCO_KBBL_SUBCMD_SET_STATE    = 0x02,
पूर्ण;

/**
 * काष्ठा wilco_keyboard_leds_msg - Message to/from EC क्रम keyboard LED control.
 * @command: Always WILCO_EC_COMMAND_KBBL.
 * @status: Set by EC to 0 on success, 0xFF on failure.
 * @subcmd: One of क्रमागत wilco_kbbl_subcommand.
 * @reserved3: Should be 0.
 * @mode: Bit flags क्रम used mode, we want to use WILCO_KBBL_MODE_FLAG_PWM.
 * @reserved5to8: Should be 0.
 * @percent: Brightness in 0-100. Only meaningful in PWM mode.
 * @reserved10to15: Should be 0.
 */
काष्ठा wilco_keyboard_leds_msg अणु
	u8 command;
	u8 status;
	u8 subcmd;
	u8 reserved3;
	u8 mode;
	u8 reserved5to8[4];
	u8 percent;
	u8 reserved10to15[6];
पूर्ण __packed;

/* Send a request, get a response, and check that the response is good. */
अटल पूर्णांक send_kbbl_msg(काष्ठा wilco_ec_device *ec,
			 काष्ठा wilco_keyboard_leds_msg *request,
			 काष्ठा wilco_keyboard_leds_msg *response)
अणु
	काष्ठा wilco_ec_message msg;
	पूर्णांक ret;

	स_रखो(&msg, 0, माप(msg));
	msg.type = WILCO_EC_MSG_LEGACY;
	msg.request_data = request;
	msg.request_size = माप(*request);
	msg.response_data = response;
	msg.response_size = माप(*response);

	ret = wilco_ec_mailbox(ec, &msg);
	अगर (ret < 0) अणु
		dev_err(ec->dev,
			"Failed sending keyboard LEDs command: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_kbbl(काष्ठा wilco_ec_device *ec, क्रमागत led_brightness brightness)
अणु
	काष्ठा wilco_keyboard_leds_msg request;
	काष्ठा wilco_keyboard_leds_msg response;
	पूर्णांक ret;

	स_रखो(&request, 0, माप(request));
	request.command = WILCO_EC_COMMAND_KBBL;
	request.subcmd  = WILCO_KBBL_SUBCMD_SET_STATE;
	request.mode    = WILCO_KBBL_MODE_FLAG_PWM;
	request.percent = brightness;

	ret = send_kbbl_msg(ec, &request, &response);
	अगर (ret < 0)
		वापस ret;

	अगर (response.status) अणु
		dev_err(ec->dev,
			"EC reported failure sending keyboard LEDs command: %d\n",
			response.status);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kbbl_exist(काष्ठा wilco_ec_device *ec, bool *exists)
अणु
	काष्ठा wilco_keyboard_leds_msg request;
	काष्ठा wilco_keyboard_leds_msg response;
	पूर्णांक ret;

	स_रखो(&request, 0, माप(request));
	request.command = WILCO_EC_COMMAND_KBBL;
	request.subcmd  = WILCO_KBBL_SUBCMD_GET_FEATURES;

	ret = send_kbbl_msg(ec, &request, &response);
	अगर (ret < 0)
		वापस ret;

	*exists = response.status != 0xFF;

	वापस 0;
पूर्ण

/**
 * kbbl_init() - Initialize the state of the keyboard backlight.
 * @ec: EC device to talk to.
 *
 * Gets the current brightness, ensuring that the BIOS alपढ़ोy initialized the
 * backlight to PWM mode. If not in PWM mode, then the current brightness is
 * meaningless, so set the brightness to WILCO_KBBL_DEFAULT_BRIGHTNESS.
 *
 * Return: Final brightness of the keyboard, or negative error code on failure.
 */
अटल पूर्णांक kbbl_init(काष्ठा wilco_ec_device *ec)
अणु
	काष्ठा wilco_keyboard_leds_msg request;
	काष्ठा wilco_keyboard_leds_msg response;
	पूर्णांक ret;

	स_रखो(&request, 0, माप(request));
	request.command = WILCO_EC_COMMAND_KBBL;
	request.subcmd  = WILCO_KBBL_SUBCMD_GET_STATE;

	ret = send_kbbl_msg(ec, &request, &response);
	अगर (ret < 0)
		वापस ret;

	अगर (response.status) अणु
		dev_err(ec->dev,
			"EC reported failure sending keyboard LEDs command: %d\n",
			response.status);
		वापस -EIO;
	पूर्ण

	अगर (response.mode & WILCO_KBBL_MODE_FLAG_PWM)
		वापस response.percent;

	ret = set_kbbl(ec, WILCO_KBBL_DEFAULT_BRIGHTNESS);
	अगर (ret < 0)
		वापस ret;

	वापस WILCO_KBBL_DEFAULT_BRIGHTNESS;
पूर्ण

अटल पूर्णांक wilco_keyboard_leds_set(काष्ठा led_classdev *cdev,
				   क्रमागत led_brightness brightness)
अणु
	काष्ठा wilco_keyboard_leds *wkl =
		container_of(cdev, काष्ठा wilco_keyboard_leds, keyboard);
	वापस set_kbbl(wkl->ec, brightness);
पूर्ण

पूर्णांक wilco_keyboard_leds_init(काष्ठा wilco_ec_device *ec)
अणु
	काष्ठा wilco_keyboard_leds *wkl;
	bool leds_exist;
	पूर्णांक ret;

	ret = kbbl_exist(ec, &leds_exist);
	अगर (ret < 0) अणु
		dev_err(ec->dev,
			"Failed checking keyboard LEDs support: %d\n", ret);
		वापस ret;
	पूर्ण
	अगर (!leds_exist)
		वापस 0;

	wkl = devm_kzalloc(ec->dev, माप(*wkl), GFP_KERNEL);
	अगर (!wkl)
		वापस -ENOMEM;

	wkl->ec = ec;
	wkl->keyboard.name = "platform::kbd_backlight";
	wkl->keyboard.max_brightness = 100;
	wkl->keyboard.flags = LED_CORE_SUSPENDRESUME;
	wkl->keyboard.brightness_set_blocking = wilco_keyboard_leds_set;
	ret = kbbl_init(ec);
	अगर (ret < 0)
		वापस ret;
	wkl->keyboard.brightness = ret;

	वापस devm_led_classdev_रेजिस्टर(ec->dev, &wkl->keyboard);
पूर्ण
