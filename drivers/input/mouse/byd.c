<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * BYD TouchPad PS/2 mouse driver
 *
 * Copyright (C) 2015 Chris Diamand <chris@diamand.org>
 * Copyright (C) 2015 Riअक्षरd Pospesel
 * Copyright (C) 2015 Tai Chi Minh Ralph Eastwood
 * Copyright (C) 2015 Martin Wimpress
 * Copyright (C) 2015 Jay Kuri
 */

#समावेश <linux/delay.h>
#समावेश <linux/input.h>
#समावेश <linux/libps2.h>
#समावेश <linux/serपन.स>
#समावेश <linux/slab.h>

#समावेश "psmouse.h"
#समावेश "byd.h"

/* PS2 Bits */
#घोषणा PS2_Y_OVERFLOW	BIT_MASK(7)
#घोषणा PS2_X_OVERFLOW	BIT_MASK(6)
#घोषणा PS2_Y_SIGN	BIT_MASK(5)
#घोषणा PS2_X_SIGN	BIT_MASK(4)
#घोषणा PS2_ALWAYS_1	BIT_MASK(3)
#घोषणा PS2_MIDDLE	BIT_MASK(2)
#घोषणा PS2_RIGHT	BIT_MASK(1)
#घोषणा PS2_LEFT	BIT_MASK(0)

/*
 * BYD pad स्थिरants
 */

/*
 * True device resolution is unknown, however experiments show the
 * resolution is about 111 units/mm.
 * Absolute coordinate packets are in the range 0-255 क्रम both X and Y
 * we pick ABS_X/ABS_Y dimensions which are multiples of 256 and in
 * the right ballpark given the touchpad's physical dimensions and estimate
 * resolution per spec sheet, device active area dimensions are
 * 101.6 x 60.1 mm.
 */
#घोषणा BYD_PAD_WIDTH		11264
#घोषणा BYD_PAD_HEIGHT		6656
#घोषणा BYD_PAD_RESOLUTION	111

/*
 * Given the above dimensions, relative packets velocity is in multiples of
 * 1 unit / 11 milliseconds.  We use this dt to estimate distance traveled
 */
#घोषणा BYD_DT			11
/* Time in jअगरfies used to समयout various touch events (64 ms) */
#घोषणा BYD_TOUCH_TIMEOUT	msecs_to_jअगरfies(64)

/* BYD commands reverse engineered from winकरोws driver */

/*
 * Swipe gesture from off-pad to on-pad
 *  0 : disable
 *  1 : enable
 */
#घोषणा BYD_CMD_SET_OFFSCREEN_SWIPE		0x10cc
/*
 * Tap and drag delay समय
 *  0 : disable
 *  1 - 8 : least to most delay
 */
#घोषणा BYD_CMD_SET_TAP_DRAG_DELAY_TIME		0x10cf
/*
 * Physical buttons function mapping
 *  0 : enable
 *  4 : normal
 *  5 : left button custom command
 *  6 : right button custom command
 *  8 : disable
 */
#घोषणा BYD_CMD_SET_PHYSICAL_BUTTONS		0x10d0
/*
 * Absolute mode (1 byte X/Y resolution)
 *  0 : disable
 *  2 : enable
 */
#घोषणा BYD_CMD_SET_ABSOLUTE_MODE		0x10d1
/*
 * Two finger scrolling
 *  1 : vertical
 *  2 : horizontal
 *  3 : vertical + horizontal
 *  4 : disable
 */
#घोषणा BYD_CMD_SET_TWO_FINGER_SCROLL		0x10d2
/*
 * Handedness
 *  1 : right handed
 *  2 : left handed
 */
#घोषणा BYD_CMD_SET_HANDEDNESS			0x10d3
/*
 * Tap to click
 *  1 : enable
 *  2 : disable
 */
#घोषणा BYD_CMD_SET_TAP				0x10d4
/*
 * Tap and drag
 *  1 : tap and hold to drag
 *  2 : tap and hold to drag + lock
 *  3 : disable
 */
#घोषणा BYD_CMD_SET_TAP_DRAG			0x10d5
/*
 * Touch sensitivity
 *  1 - 7 : least to most sensitive
 */
#घोषणा BYD_CMD_SET_TOUCH_SENSITIVITY		0x10d6
/*
 * One finger scrolling
 *  1 : vertical
 *  2 : horizontal
 *  3 : vertical + horizontal
 *  4 : disable
 */
#घोषणा BYD_CMD_SET_ONE_FINGER_SCROLL		0x10d7
/*
 * One finger scrolling function
 *  1 : मुक्त scrolling
 *  2 : edge motion
 *  3 : मुक्त scrolling + edge motion
 *  4 : disable
 */
#घोषणा BYD_CMD_SET_ONE_FINGER_SCROLL_FUNC	0x10d8
/*
 * Sliding speed
 *  1 - 5 : slowest to fastest
 */
#घोषणा BYD_CMD_SET_SLIDING_SPEED		0x10da
/*
 * Edge motion
 *  1 : disable
 *  2 : enable when dragging
 *  3 : enable when dragging and poपूर्णांकing
 */
#घोषणा BYD_CMD_SET_EDGE_MOTION			0x10db
/*
 * Left edge region size
 *  0 - 7 : smallest to largest width
 */
#घोषणा BYD_CMD_SET_LEFT_EDGE_REGION		0x10dc
/*
 * Top edge region size
 *  0 - 9 : smallest to largest height
 */
#घोषणा BYD_CMD_SET_TOP_EDGE_REGION		0x10dd
/*
 * Disregard palm press as clicks
 *  1 - 6 : smallest to largest
 */
#घोषणा BYD_CMD_SET_PALM_CHECK			0x10de
/*
 * Right edge region size
 *  0 - 7 : smallest to largest width
 */
#घोषणा BYD_CMD_SET_RIGHT_EDGE_REGION		0x10df
/*
 * Bottom edge region size
 *  0 - 9 : smallest to largest height
 */
#घोषणा BYD_CMD_SET_BOTTOM_EDGE_REGION		0x10e1
/*
 * Multitouch gestures
 *  1 : enable
 *  2 : disable
 */
#घोषणा BYD_CMD_SET_MULTITOUCH			0x10e3
/*
 * Edge motion speed
 *  0 : control with finger pressure
 *  1 - 9 : slowest to fastest
 */
#घोषणा BYD_CMD_SET_EDGE_MOTION_SPEED		0x10e4
/*
 * Two finger scolling function
 *  0 : मुक्त scrolling
 *  1 : मुक्त scrolling (with momentum)
 *  2 : edge motion
 *  3 : मुक्त scrolling (with momentum) + edge motion
 *  4 : disable
 */
#घोषणा BYD_CMD_SET_TWO_FINGER_SCROLL_FUNC	0x10e5

/*
 * The touchpad generates a mixture of असलolute and relative packets, indicated
 * by the the last byte of each packet being set to one of the following:
 */
#घोषणा BYD_PACKET_ABSOLUTE			0xf8
#घोषणा BYD_PACKET_RELATIVE			0x00
/* Multitouch gesture packets */
#घोषणा BYD_PACKET_PINCH_IN			0xd8
#घोषणा BYD_PACKET_PINCH_OUT			0x28
#घोषणा BYD_PACKET_ROTATE_CLOCKWISE		0x29
#घोषणा BYD_PACKET_ROTATE_ANTICLOCKWISE		0xd7
#घोषणा BYD_PACKET_TWO_FINGER_SCROLL_RIGHT	0x2a
#घोषणा BYD_PACKET_TWO_FINGER_SCROLL_DOWN	0x2b
#घोषणा BYD_PACKET_TWO_FINGER_SCROLL_UP		0xd5
#घोषणा BYD_PACKET_TWO_FINGER_SCROLL_LEFT	0xd6
#घोषणा BYD_PACKET_THREE_FINGER_SWIPE_RIGHT	0x2c
#घोषणा BYD_PACKET_THREE_FINGER_SWIPE_DOWN	0x2d
#घोषणा BYD_PACKET_THREE_FINGER_SWIPE_UP	0xd3
#घोषणा BYD_PACKET_THREE_FINGER_SWIPE_LEFT	0xd4
#घोषणा BYD_PACKET_FOUR_FINGER_DOWN		0x33
#घोषणा BYD_PACKET_FOUR_FINGER_UP		0xcd
#घोषणा BYD_PACKET_REGION_SCROLL_RIGHT		0x35
#घोषणा BYD_PACKET_REGION_SCROLL_DOWN		0x36
#घोषणा BYD_PACKET_REGION_SCROLL_UP		0xca
#घोषणा BYD_PACKET_REGION_SCROLL_LEFT		0xcb
#घोषणा BYD_PACKET_RIGHT_CORNER_CLICK		0xd2
#घोषणा BYD_PACKET_LEFT_CORNER_CLICK		0x2e
#घोषणा BYD_PACKET_LEFT_AND_RIGHT_CORNER_CLICK	0x2f
#घोषणा BYD_PACKET_ONTO_PAD_SWIPE_RIGHT		0x37
#घोषणा BYD_PACKET_ONTO_PAD_SWIPE_DOWN		0x30
#घोषणा BYD_PACKET_ONTO_PAD_SWIPE_UP		0xd0
#घोषणा BYD_PACKET_ONTO_PAD_SWIPE_LEFT		0xc9

काष्ठा byd_data अणु
	काष्ठा समयr_list समयr;
	काष्ठा psmouse *psmouse;
	s32 असल_x;
	s32 असल_y;
	typeof(jअगरfies) last_touch_समय;
	bool btn_left;
	bool btn_right;
	bool touch;
पूर्ण;

अटल व्योम byd_report_input(काष्ठा psmouse *psmouse)
अणु
	काष्ठा byd_data *priv = psmouse->निजी;
	काष्ठा input_dev *dev = psmouse->dev;

	input_report_key(dev, BTN_TOUCH, priv->touch);
	input_report_key(dev, BTN_TOOL_FINGER, priv->touch);

	input_report_असल(dev, ABS_X, priv->असल_x);
	input_report_असल(dev, ABS_Y, priv->असल_y);
	input_report_key(dev, BTN_LEFT, priv->btn_left);
	input_report_key(dev, BTN_RIGHT, priv->btn_right);

	input_sync(dev);
पूर्ण

अटल व्योम byd_clear_touch(काष्ठा समयr_list *t)
अणु
	काष्ठा byd_data *priv = from_समयr(priv, t, समयr);
	काष्ठा psmouse *psmouse = priv->psmouse;

	serio_छोड़ो_rx(psmouse->ps2dev.serio);
	priv->touch = false;

	byd_report_input(psmouse);

	serio_जारी_rx(psmouse->ps2dev.serio);

	/*
	 * Move cursor back to center of pad when we lose touch - this
	 * specअगरically improves user experience when moving cursor with one
	 * finger, and pressing a button with another.
	 */
	priv->असल_x = BYD_PAD_WIDTH / 2;
	priv->असल_y = BYD_PAD_HEIGHT / 2;
पूर्ण

अटल psmouse_ret_t byd_process_byte(काष्ठा psmouse *psmouse)
अणु
	काष्ठा byd_data *priv = psmouse->निजी;
	u8 *pkt = psmouse->packet;

	अगर (psmouse->pktcnt > 0 && !(pkt[0] & PS2_ALWAYS_1)) अणु
		psmouse_warn(psmouse, "Always_1 bit not 1. pkt[0] = %02x\n",
			     pkt[0]);
		वापस PSMOUSE_BAD_DATA;
	पूर्ण

	अगर (psmouse->pktcnt < psmouse->pktsize)
		वापस PSMOUSE_GOOD_DATA;

	/* Otherwise, a full packet has been received */
	चयन (pkt[3]) अणु
	हाल BYD_PACKET_ABSOLUTE:
		/* Only use असलolute packets क्रम the start of movement. */
		अगर (!priv->touch) अणु
			/* needed to detect tap */
			typeof(jअगरfies) tap_समय =
				priv->last_touch_समय + BYD_TOUCH_TIMEOUT;
			priv->touch = समय_after(jअगरfies, tap_समय);

			/* init असल position */
			priv->असल_x = pkt[1] * (BYD_PAD_WIDTH / 256);
			priv->असल_y = (255 - pkt[2]) * (BYD_PAD_HEIGHT / 256);
		पूर्ण
		अवरोध;
	हाल BYD_PACKET_RELATIVE: अणु
		/* Standard packet */
		/* Sign-extend अगर a sign bit is set. */
		u32 signx = pkt[0] & PS2_X_SIGN ? ~0xFF : 0;
		u32 signy = pkt[0] & PS2_Y_SIGN ? ~0xFF : 0;
		s32 dx = signx | (पूर्णांक) pkt[1];
		s32 dy = signy | (पूर्णांक) pkt[2];

		/* Update position based on velocity */
		priv->असल_x += dx * BYD_DT;
		priv->असल_y -= dy * BYD_DT;

		priv->touch = true;
		अवरोध;
	पूर्ण
	शेष:
		psmouse_warn(psmouse,
			     "Unrecognized Z: pkt = %02x %02x %02x %02x\n",
			     psmouse->packet[0], psmouse->packet[1],
			     psmouse->packet[2], psmouse->packet[3]);
		वापस PSMOUSE_BAD_DATA;
	पूर्ण

	priv->btn_left = pkt[0] & PS2_LEFT;
	priv->btn_right = pkt[0] & PS2_RIGHT;

	byd_report_input(psmouse);

	/* Reset समय since last touch. */
	अगर (priv->touch) अणु
		priv->last_touch_समय = jअगरfies;
		mod_समयr(&priv->समयr, jअगरfies + BYD_TOUCH_TIMEOUT);
	पूर्ण

	वापस PSMOUSE_FULL_PACKET;
पूर्ण

अटल पूर्णांक byd_reset_touchpad(काष्ठा psmouse *psmouse)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	u8 param[4];
	माप_प्रकार i;

	अटल स्थिर काष्ठा अणु
		u16 command;
		u8 arg;
	पूर्ण seq[] = अणु
		/*
		 * Intellimouse initialization sequence, to get 4-byte instead
		 * of 3-byte packets.
		 */
		अणु PSMOUSE_CMD_SETRATE, 0xC8 पूर्ण,
		अणु PSMOUSE_CMD_SETRATE, 0x64 पूर्ण,
		अणु PSMOUSE_CMD_SETRATE, 0x50 पूर्ण,
		अणु PSMOUSE_CMD_GETID, 0 पूर्ण,
		अणु PSMOUSE_CMD_ENABLE, 0 पूर्ण,
		/*
		 * BYD-specअगरic initialization, which enables असलolute mode and
		 * (अगर desired), the touchpad's built-in gesture detection.
		 */
		अणु 0x10E2, 0x00 पूर्ण,
		अणु 0x10E0, 0x02 पूर्ण,
		/* The touchpad should reply with 4 seemingly-अक्रमom bytes */
		अणु 0x14E0, 0x01 पूर्ण,
		/* Pairs of parameters and values. */
		अणु BYD_CMD_SET_HANDEDNESS, 0x01 पूर्ण,
		अणु BYD_CMD_SET_PHYSICAL_BUTTONS, 0x04 पूर्ण,
		अणु BYD_CMD_SET_TAP, 0x02 पूर्ण,
		अणु BYD_CMD_SET_ONE_FINGER_SCROLL, 0x04 पूर्ण,
		अणु BYD_CMD_SET_ONE_FINGER_SCROLL_FUNC, 0x04 पूर्ण,
		अणु BYD_CMD_SET_EDGE_MOTION, 0x01 पूर्ण,
		अणु BYD_CMD_SET_PALM_CHECK, 0x00 पूर्ण,
		अणु BYD_CMD_SET_MULTITOUCH, 0x02 पूर्ण,
		अणु BYD_CMD_SET_TWO_FINGER_SCROLL, 0x04 पूर्ण,
		अणु BYD_CMD_SET_TWO_FINGER_SCROLL_FUNC, 0x04 पूर्ण,
		अणु BYD_CMD_SET_LEFT_EDGE_REGION, 0x00 पूर्ण,
		अणु BYD_CMD_SET_TOP_EDGE_REGION, 0x00 पूर्ण,
		अणु BYD_CMD_SET_RIGHT_EDGE_REGION, 0x00 पूर्ण,
		अणु BYD_CMD_SET_BOTTOM_EDGE_REGION, 0x00 पूर्ण,
		अणु BYD_CMD_SET_ABSOLUTE_MODE, 0x02 पूर्ण,
		/* Finalize initialization. */
		अणु 0x10E0, 0x00 पूर्ण,
		अणु 0x10E2, 0x01 पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(seq); ++i) अणु
		स_रखो(param, 0, माप(param));
		param[0] = seq[i].arg;
		अगर (ps2_command(ps2dev, param, seq[i].command))
			वापस -EIO;
	पूर्ण

	psmouse_set_state(psmouse, PSMOUSE_ACTIVATED);
	वापस 0;
पूर्ण

अटल पूर्णांक byd_reconnect(काष्ठा psmouse *psmouse)
अणु
	पूर्णांक retry = 0, error = 0;

	psmouse_dbg(psmouse, "Reconnect\n");
	करो अणु
		psmouse_reset(psmouse);
		अगर (retry)
			ssleep(1);
		error = byd_detect(psmouse, 0);
	पूर्ण जबतक (error && ++retry < 3);

	अगर (error)
		वापस error;

	psmouse_dbg(psmouse, "Reconnected after %d attempts\n", retry);

	error = byd_reset_touchpad(psmouse);
	अगर (error) अणु
		psmouse_err(psmouse, "Unable to initialize device\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम byd_disconnect(काष्ठा psmouse *psmouse)
अणु
	काष्ठा byd_data *priv = psmouse->निजी;

	अगर (priv) अणु
		del_समयr(&priv->समयr);
		kमुक्त(psmouse->निजी);
		psmouse->निजी = शून्य;
	पूर्ण
पूर्ण

पूर्णांक byd_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	u8 param[4] = अणु0x03, 0x00, 0x00, 0x00पूर्ण;

	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES))
		वापस -1;
	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES))
		वापस -1;
	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES))
		वापस -1;
	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES))
		वापस -1;
	अगर (ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO))
		वापस -1;

	अगर (param[1] != 0x03 || param[2] != 0x64)
		वापस -ENODEV;

	psmouse_dbg(psmouse, "BYD touchpad detected\n");

	अगर (set_properties) अणु
		psmouse->venकरोr = "BYD";
		psmouse->name = "TouchPad";
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक byd_init(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा byd_data *priv;

	अगर (psmouse_reset(psmouse))
		वापस -EIO;

	अगर (byd_reset_touchpad(psmouse))
		वापस -EIO;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->psmouse = psmouse;
	समयr_setup(&priv->समयr, byd_clear_touch, 0);

	psmouse->निजी = priv;
	psmouse->disconnect = byd_disconnect;
	psmouse->reconnect = byd_reconnect;
	psmouse->protocol_handler = byd_process_byte;
	psmouse->pktsize = 4;
	psmouse->resync_समय = 0;

	__set_bit(INPUT_PROP_POINTER, dev->propbit);
	/* Touchpad */
	__set_bit(BTN_TOUCH, dev->keybit);
	__set_bit(BTN_TOOL_FINGER, dev->keybit);
	/* Buttons */
	__set_bit(BTN_LEFT, dev->keybit);
	__set_bit(BTN_RIGHT, dev->keybit);
	__clear_bit(BTN_MIDDLE, dev->keybit);

	/* Absolute position */
	__set_bit(EV_ABS, dev->evbit);
	input_set_असल_params(dev, ABS_X, 0, BYD_PAD_WIDTH, 0, 0);
	input_set_असल_params(dev, ABS_Y, 0, BYD_PAD_HEIGHT, 0, 0);
	input_असल_set_res(dev, ABS_X, BYD_PAD_RESOLUTION);
	input_असल_set_res(dev, ABS_Y, BYD_PAD_RESOLUTION);
	/* No relative support */
	__clear_bit(EV_REL, dev->evbit);
	__clear_bit(REL_X, dev->relbit);
	__clear_bit(REL_Y, dev->relbit);

	वापस 0;
पूर्ण
