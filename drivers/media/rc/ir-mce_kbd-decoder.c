<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ir-mce_kbd-decoder.c - A decoder क्रम the RC6-ish keyboard/mouse IR protocol
 * used by the Microsoft Remote Keyboard क्रम Winकरोws Media Center Edition,
 * referred to by Microsoft's Winकरोws Media Center remote specअगरication करोcs
 * as "an internal protocol called MCIR-2".
 *
 * Copyright (C) 2011 by Jarod Wilson <jarod@redhat.com>
 */
#समावेश <linux/module.h>

#समावेश "rc-core-priv.h"

/*
 * This decoder currently supports:
 * - MCIR-2 29-bit IR संकेतs used क्रम mouse movement and buttons
 * - MCIR-2 32-bit IR संकेतs used क्रम standard keyboard keys
 *
 * The media keys on the keyboard send RC-6 संकेतs that are indistinguishable
 * from the keys of the same name on the stock MCE remote, and will be handled
 * by the standard RC-6 decoder, and be made available to the प्रणाली via the
 * input device क्रम the remote, rather than the keyboard/mouse one.
 */

#घोषणा MCIR2_UNIT		333	/* us */
#घोषणा MCIR2_HEADER_NBITS	5
#घोषणा MCIR2_MOUSE_NBITS	29
#घोषणा MCIR2_KEYBOARD_NBITS	32
#घोषणा MCIR2_PREFIX_PULSE	(8 * MCIR2_UNIT)
#घोषणा MCIR2_PREFIX_SPACE	(1 * MCIR2_UNIT)
#घोषणा MCIR2_MAX_LEN		(3 * MCIR2_UNIT)
#घोषणा MCIR2_BIT_START		(1 * MCIR2_UNIT)
#घोषणा MCIR2_BIT_END		(1 * MCIR2_UNIT)
#घोषणा MCIR2_BIT_0		(1 * MCIR2_UNIT)
#घोषणा MCIR2_BIT_SET		(2 * MCIR2_UNIT)
#घोषणा MCIR2_MODE_MASK		0xf	/* क्रम the header bits */
#घोषणा MCIR2_KEYBOARD_HEADER	0x4
#घोषणा MCIR2_MOUSE_HEADER	0x1
#घोषणा MCIR2_MASK_KEYS_START	0xe0

क्रमागत mce_kbd_mode अणु
	MCIR2_MODE_KEYBOARD,
	MCIR2_MODE_MOUSE,
	MCIR2_MODE_UNKNOWN,
पूर्ण;

क्रमागत mce_kbd_state अणु
	STATE_INACTIVE,
	STATE_HEADER_BIT_START,
	STATE_HEADER_BIT_END,
	STATE_BODY_BIT_START,
	STATE_BODY_BIT_END,
	STATE_FINISHED,
पूर्ण;

अटल अचिन्हित अक्षर kbd_keycodes[256] = अणु
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_A,
	KEY_B,		KEY_C,		KEY_D,		KEY_E,		KEY_F,
	KEY_G,		KEY_H,		KEY_I,		KEY_J,		KEY_K,
	KEY_L,		KEY_M,		KEY_N,		KEY_O,		KEY_P,
	KEY_Q,		KEY_R,		KEY_S,		KEY_T,		KEY_U,
	KEY_V,		KEY_W,		KEY_X,		KEY_Y,		KEY_Z,
	KEY_1,		KEY_2,		KEY_3,		KEY_4,		KEY_5,
	KEY_6,		KEY_7,		KEY_8,		KEY_9,		KEY_0,
	KEY_ENTER,	KEY_ESC,	KEY_BACKSPACE,	KEY_TAB,	KEY_SPACE,
	KEY_MINUS,	KEY_EQUAL,	KEY_LEFTBRACE,	KEY_RIGHTBRACE,	KEY_BACKSLASH,
	KEY_BACKSLASH,	KEY_SEMICOLON,	KEY_APOSTROPHE,	KEY_GRAVE,	KEY_COMMA,
	KEY_DOT,	KEY_SLASH,	KEY_CAPSLOCK,	KEY_F1,		KEY_F2,
	KEY_F3,		KEY_F4,		KEY_F5,		KEY_F6,		KEY_F7,
	KEY_F8,		KEY_F9,		KEY_F10,	KEY_F11,	KEY_F12,
	KEY_SYSRQ,	KEY_SCROLLLOCK,	KEY_PAUSE,	KEY_INSERT,	KEY_HOME,
	KEY_PAGEUP,	KEY_DELETE,	KEY_END,	KEY_PAGEDOWN,	KEY_RIGHT,
	KEY_LEFT,	KEY_DOWN,	KEY_UP,		KEY_NUMLOCK,	KEY_KPSLASH,
	KEY_KPASTERISK,	KEY_KPMINUS,	KEY_KPPLUS,	KEY_KPENTER,	KEY_KP1,
	KEY_KP2,	KEY_KP3,	KEY_KP4,	KEY_KP5,	KEY_KP6,
	KEY_KP7,	KEY_KP8,	KEY_KP9,	KEY_KP0,	KEY_KPDOT,
	KEY_102ND,	KEY_COMPOSE,	KEY_POWER,	KEY_KPEQUAL,	KEY_F13,
	KEY_F14,	KEY_F15,	KEY_F16,	KEY_F17,	KEY_F18,
	KEY_F19,	KEY_F20,	KEY_F21,	KEY_F22,	KEY_F23,
	KEY_F24,	KEY_OPEN,	KEY_HELP,	KEY_PROPS,	KEY_FRONT,
	KEY_STOP,	KEY_AGAIN,	KEY_UNDO,	KEY_CUT,	KEY_COPY,
	KEY_PASTE,	KEY_FIND,	KEY_MUTE,	KEY_VOLUMEUP,	KEY_VOLUMEDOWN,
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_KPCOMMA,	KEY_RESERVED,
	KEY_RO,		KEY_KATAKANAHIRAGANA, KEY_YEN,	KEY_HENKAN,	KEY_MUHENKAN,
	KEY_KPJPCOMMA,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_HANGUEL,
	KEY_HANJA,	KEY_KATAKANA,	KEY_HIRAGANA,	KEY_ZENKAKUHANKAKU, KEY_RESERVED,
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,
	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,	KEY_LEFTCTRL,
	KEY_LEFTSHIFT,	KEY_LEFTALT,	KEY_LEFTMETA,	KEY_RIGHTCTRL,	KEY_RIGHTSHIFT,
	KEY_RIGHTALT,	KEY_RIGHTMETA,	KEY_PLAYPAUSE,	KEY_STOPCD,	KEY_PREVIOUSSONG,
	KEY_NEXTSONG,	KEY_EJECTCD,	KEY_VOLUMEUP,	KEY_VOLUMEDOWN,	KEY_MUTE,
	KEY_WWW,	KEY_BACK,	KEY_FORWARD,	KEY_STOP,	KEY_FIND,
	KEY_SCROLLUP,	KEY_SCROLLDOWN,	KEY_EDIT,	KEY_SLEEP,	KEY_COFFEE,
	KEY_REFRESH,	KEY_CALC,	KEY_RESERVED,	KEY_RESERVED,	KEY_RESERVED,
	KEY_RESERVED
पूर्ण;

अटल व्योम mce_kbd_rx_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा ir_raw_event_ctrl *raw = from_समयr(raw, t, mce_kbd.rx_समयout);
	अचिन्हित अक्षर maskcode;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	dev_dbg(&raw->dev->dev, "timer callback clearing all keys\n");

	spin_lock_irqsave(&raw->mce_kbd.keylock, flags);

	अगर (समय_is_beक्रमe_eq_jअगरfies(raw->mce_kbd.rx_समयout.expires)) अणु
		क्रम (i = 0; i < 7; i++) अणु
			maskcode = kbd_keycodes[MCIR2_MASK_KEYS_START + i];
			input_report_key(raw->dev->input_dev, maskcode, 0);
		पूर्ण

		क्रम (i = 0; i < MCIR2_MASK_KEYS_START; i++)
			input_report_key(raw->dev->input_dev, kbd_keycodes[i],
					 0);

		input_sync(raw->dev->input_dev);
	पूर्ण
	spin_unlock_irqrestore(&raw->mce_kbd.keylock, flags);
पूर्ण

अटल क्रमागत mce_kbd_mode mce_kbd_mode(काष्ठा mce_kbd_dec *data)
अणु
	चयन (data->header & MCIR2_MODE_MASK) अणु
	हाल MCIR2_KEYBOARD_HEADER:
		वापस MCIR2_MODE_KEYBOARD;
	हाल MCIR2_MOUSE_HEADER:
		वापस MCIR2_MODE_MOUSE;
	शेष:
		वापस MCIR2_MODE_UNKNOWN;
	पूर्ण
पूर्ण

अटल व्योम ir_mce_kbd_process_keyboard_data(काष्ठा rc_dev *dev, u32 scancode)
अणु
	u8 keydata1  = (scancode >> 8) & 0xff;
	u8 keydata2  = (scancode >> 16) & 0xff;
	u8 shअगरपंचांगask = scancode & 0xff;
	अचिन्हित अक्षर maskcode;
	पूर्णांक i, keystate;

	dev_dbg(&dev->dev, "keyboard: keydata2 = 0x%02x, keydata1 = 0x%02x, shiftmask = 0x%02x\n",
		keydata2, keydata1, shअगरपंचांगask);

	क्रम (i = 0; i < 7; i++) अणु
		maskcode = kbd_keycodes[MCIR2_MASK_KEYS_START + i];
		अगर (shअगरपंचांगask & (1 << i))
			keystate = 1;
		अन्यथा
			keystate = 0;
		input_report_key(dev->input_dev, maskcode, keystate);
	पूर्ण

	अगर (keydata1)
		input_report_key(dev->input_dev, kbd_keycodes[keydata1], 1);
	अगर (keydata2)
		input_report_key(dev->input_dev, kbd_keycodes[keydata2], 1);

	अगर (!keydata1 && !keydata2) अणु
		क्रम (i = 0; i < MCIR2_MASK_KEYS_START; i++)
			input_report_key(dev->input_dev, kbd_keycodes[i], 0);
	पूर्ण
पूर्ण

अटल व्योम ir_mce_kbd_process_mouse_data(काष्ठा rc_dev *dev, u32 scancode)
अणु
	/* raw mouse coordinates */
	u8 xdata = (scancode >> 7) & 0x7f;
	u8 ydata = (scancode >> 14) & 0x7f;
	पूर्णांक x, y;
	/* mouse buttons */
	bool right = scancode & 0x40;
	bool left  = scancode & 0x20;

	अगर (xdata & 0x40)
		x = -((~xdata & 0x7f) + 1);
	अन्यथा
		x = xdata;

	अगर (ydata & 0x40)
		y = -((~ydata & 0x7f) + 1);
	अन्यथा
		y = ydata;

	dev_dbg(&dev->dev, "mouse: x = %d, y = %d, btns = %s%s\n",
		x, y, left ? "L" : "", right ? "R" : "");

	input_report_rel(dev->input_dev, REL_X, x);
	input_report_rel(dev->input_dev, REL_Y, y);

	input_report_key(dev->input_dev, BTN_LEFT, left);
	input_report_key(dev->input_dev, BTN_RIGHT, right);
पूर्ण

/**
 * ir_mce_kbd_decode() - Decode one mce_kbd pulse or space
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @ev:		the काष्ठा ir_raw_event descriptor of the pulse/space
 *
 * This function वापसs -EINVAL अगर the pulse violates the state machine
 */
अटल पूर्णांक ir_mce_kbd_decode(काष्ठा rc_dev *dev, काष्ठा ir_raw_event ev)
अणु
	काष्ठा mce_kbd_dec *data = &dev->raw->mce_kbd;
	u32 scancode;
	अचिन्हित दीर्घ delay;
	काष्ठा lirc_scancode lsc = अणुपूर्ण;

	अगर (!is_timing_event(ev)) अणु
		अगर (ev.reset)
			data->state = STATE_INACTIVE;
		वापस 0;
	पूर्ण

	अगर (!geq_margin(ev.duration, MCIR2_UNIT, MCIR2_UNIT / 2))
		जाओ out;

again:
	dev_dbg(&dev->dev, "started at state %i (%uus %s)\n",
		data->state, ev.duration, TO_STR(ev.pulse));

	अगर (!geq_margin(ev.duration, MCIR2_UNIT, MCIR2_UNIT / 2))
		वापस 0;

	चयन (data->state) अणु

	हाल STATE_INACTIVE:
		अगर (!ev.pulse)
			अवरोध;

		/* Note: larger margin on first pulse since each MCIR2_UNIT
		   is quite लघु and some hardware takes some समय to
		   adjust to the संकेत */
		अगर (!eq_margin(ev.duration, MCIR2_PREFIX_PULSE, MCIR2_UNIT))
			अवरोध;

		data->state = STATE_HEADER_BIT_START;
		data->count = 0;
		data->header = 0;
		वापस 0;

	हाल STATE_HEADER_BIT_START:
		अगर (geq_margin(ev.duration, MCIR2_MAX_LEN, MCIR2_UNIT / 2))
			अवरोध;

		data->header <<= 1;
		अगर (ev.pulse)
			data->header |= 1;
		data->count++;
		data->state = STATE_HEADER_BIT_END;
		वापस 0;

	हाल STATE_HEADER_BIT_END:
		decrease_duration(&ev, MCIR2_BIT_END);

		अगर (data->count != MCIR2_HEADER_NBITS) अणु
			data->state = STATE_HEADER_BIT_START;
			जाओ again;
		पूर्ण

		चयन (mce_kbd_mode(data)) अणु
		हाल MCIR2_MODE_KEYBOARD:
			data->wanted_bits = MCIR2_KEYBOARD_NBITS;
			अवरोध;
		हाल MCIR2_MODE_MOUSE:
			data->wanted_bits = MCIR2_MOUSE_NBITS;
			अवरोध;
		शेष:
			dev_dbg(&dev->dev, "not keyboard or mouse data\n");
			जाओ out;
		पूर्ण

		data->count = 0;
		data->body = 0;
		data->state = STATE_BODY_BIT_START;
		जाओ again;

	हाल STATE_BODY_BIT_START:
		अगर (geq_margin(ev.duration, MCIR2_MAX_LEN, MCIR2_UNIT / 2))
			अवरोध;

		data->body <<= 1;
		अगर (ev.pulse)
			data->body |= 1;
		data->count++;
		data->state = STATE_BODY_BIT_END;
		वापस 0;

	हाल STATE_BODY_BIT_END:
		अगर (data->count == data->wanted_bits)
			data->state = STATE_FINISHED;
		अन्यथा
			data->state = STATE_BODY_BIT_START;

		decrease_duration(&ev, MCIR2_BIT_END);
		जाओ again;

	हाल STATE_FINISHED:
		अगर (ev.pulse)
			अवरोध;

		चयन (data->wanted_bits) अणु
		हाल MCIR2_KEYBOARD_NBITS:
			scancode = data->body & 0xffffff;
			dev_dbg(&dev->dev, "keyboard data 0x%08x\n",
				data->body);
			spin_lock(&data->keylock);
			अगर (scancode) अणु
				delay = usecs_to_jअगरfies(dev->समयout) +
					msecs_to_jअगरfies(100);
				mod_समयr(&data->rx_समयout, jअगरfies + delay);
			पूर्ण अन्यथा अणु
				del_समयr(&data->rx_समयout);
			पूर्ण
			/* Pass data to keyboard buffer parser */
			ir_mce_kbd_process_keyboard_data(dev, scancode);
			spin_unlock(&data->keylock);
			lsc.rc_proto = RC_PROTO_MCIR2_KBD;
			अवरोध;
		हाल MCIR2_MOUSE_NBITS:
			scancode = data->body & 0x1fffff;
			dev_dbg(&dev->dev, "mouse data 0x%06x\n", scancode);
			/* Pass data to mouse buffer parser */
			ir_mce_kbd_process_mouse_data(dev, scancode);
			lsc.rc_proto = RC_PROTO_MCIR2_MSE;
			अवरोध;
		शेष:
			dev_dbg(&dev->dev, "not keyboard or mouse data\n");
			जाओ out;
		पूर्ण

		lsc.scancode = scancode;
		lirc_scancode_event(dev, &lsc);
		data->state = STATE_INACTIVE;
		input_event(dev->input_dev, EV_MSC, MSC_SCAN, scancode);
		input_sync(dev->input_dev);
		वापस 0;
	पूर्ण

out:
	dev_dbg(&dev->dev, "failed at state %i (%uus %s)\n",
		data->state, ev.duration, TO_STR(ev.pulse));
	data->state = STATE_INACTIVE;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ir_mce_kbd_रेजिस्टर(काष्ठा rc_dev *dev)
अणु
	काष्ठा mce_kbd_dec *mce_kbd = &dev->raw->mce_kbd;

	समयr_setup(&mce_kbd->rx_समयout, mce_kbd_rx_समयout, 0);
	spin_lock_init(&mce_kbd->keylock);

	वापस 0;
पूर्ण

अटल पूर्णांक ir_mce_kbd_unरेजिस्टर(काष्ठा rc_dev *dev)
अणु
	काष्ठा mce_kbd_dec *mce_kbd = &dev->raw->mce_kbd;

	del_समयr_sync(&mce_kbd->rx_समयout);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ir_raw_timings_manchester ir_mce_kbd_timings = अणु
	.leader_pulse	= MCIR2_PREFIX_PULSE,
	.invert		= 1,
	.घड़ी		= MCIR2_UNIT,
	.trailer_space	= MCIR2_UNIT * 10,
पूर्ण;

/**
 * ir_mce_kbd_encode() - Encode a scancode as a stream of raw events
 *
 * @protocol:   protocol to encode
 * @scancode:   scancode to encode
 * @events:     array of raw ir events to ग_लिखो पूर्णांकo
 * @max:        maximum size of @events
 *
 * Returns:     The number of events written.
 *              -ENOBUFS अगर there isn't enough space in the array to fit the
 *              encoding. In this हाल all @max events will have been written.
 */
अटल पूर्णांक ir_mce_kbd_encode(क्रमागत rc_proto protocol, u32 scancode,
			     काष्ठा ir_raw_event *events, अचिन्हित पूर्णांक max)
अणु
	काष्ठा ir_raw_event *e = events;
	पूर्णांक len, ret;
	u64 raw;

	अगर (protocol == RC_PROTO_MCIR2_KBD) अणु
		raw = scancode |
		      ((u64)MCIR2_KEYBOARD_HEADER << MCIR2_KEYBOARD_NBITS);
		len = MCIR2_KEYBOARD_NBITS + MCIR2_HEADER_NBITS;
	पूर्ण अन्यथा अणु
		raw = scancode |
		      ((u64)MCIR2_MOUSE_HEADER << MCIR2_MOUSE_NBITS);
		len = MCIR2_MOUSE_NBITS + MCIR2_HEADER_NBITS;
	पूर्ण

	ret = ir_raw_gen_manchester(&e, max, &ir_mce_kbd_timings, len, raw);
	अगर (ret < 0)
		वापस ret;

	वापस e - events;
पूर्ण

अटल काष्ठा ir_raw_handler mce_kbd_handler = अणु
	.protocols	= RC_PROTO_BIT_MCIR2_KBD | RC_PROTO_BIT_MCIR2_MSE,
	.decode		= ir_mce_kbd_decode,
	.encode		= ir_mce_kbd_encode,
	.raw_रेजिस्टर	= ir_mce_kbd_रेजिस्टर,
	.raw_unरेजिस्टर	= ir_mce_kbd_unरेजिस्टर,
	.carrier	= 36000,
	.min_समयout	= MCIR2_MAX_LEN + MCIR2_UNIT / 2,
पूर्ण;

अटल पूर्णांक __init ir_mce_kbd_decode_init(व्योम)
अणु
	ir_raw_handler_रेजिस्टर(&mce_kbd_handler);

	prपूर्णांकk(KERN_INFO "IR MCE Keyboard/mouse protocol handler initialized\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास ir_mce_kbd_decode_निकास(व्योम)
अणु
	ir_raw_handler_unरेजिस्टर(&mce_kbd_handler);
पूर्ण

module_init(ir_mce_kbd_decode_init);
module_निकास(ir_mce_kbd_decode_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jarod Wilson <jarod@redhat.com>");
MODULE_DESCRIPTION("MCE Keyboard/mouse IR protocol decoder");
