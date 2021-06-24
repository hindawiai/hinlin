<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2004 by Jan-Benedict Glaw <jbglaw@lug-owl.de>
 */

/*
 * LK keyboard driver क्रम Linux, based on sunkbd.c (C) by Vojtech Pavlik
 */

/*
 * DEC LK201 and LK401 keyboard driver क्रम Linux (primary क्रम DECstations
 * and VAXstations, but can also be used on any standard RS232 with an
 * adaptor).
 *
 * DISCLAIMER: This works क्रम _me_. If you अवरोध anything by using the
 * inक्रमmation given below, I will _not_ be liable!
 *
 * RJ10 pinout:		To DE9:		Or DB25:
 *	1 - RxD <---->	Pin 3 (TxD) <->	Pin 2 (TxD)
 *	2 - GND <---->	Pin 5 (GND) <->	Pin 7 (GND)
 *	4 - TxD <---->	Pin 2 (RxD) <->	Pin 3 (RxD)
 *	3 - +12V (from HDD drive connector), DON'T connect to DE9 or DB25!!!
 *
 * Pin numbers क्रम DE9 and DB25 are noted on the plug (quite small:). For
 * RJ10, it's like this:
 *
 *      __=__	Hold the plug in front of you, cable करोwnwards,
 *     /___/|	nose is hidden behind the plug. Now, pin 1 is at
 *    |1234||	the left side, pin 4 at the right and 2 and 3 are
 *    |IIII||	in between, of course:)
 *    |    ||
 *    |____|/
 *      ||	So the adaptor consists of three connected cables
 *      ||	क्रम data transmission (RxD and TxD) and संकेत ground.
 *		Additionally, you have to get +12V from somewhere.
 * Most easily, you'll get that from a floppy or HDD घातer connector.
 * It's the yellow cable there (black is ground and red is +5V).
 *
 * The keyboard and all the commands it understands are करोcumented in
 * "VCB02 Video Subsystem - Technical Manual", EK-104AA-TM-001. This
 * करोcument is LK201 specअगरic, but LK401 is mostly compatible. It comes
 * up in LK201 mode and करोesn't report any of the additional keys it
 * has. These need to be चयनed on with the LK_CMD_ENABLE_LK401
 * command. You'll find this करोcument (scanned .pdf file) on MANX,
 * a search engine specअगरic to DEC करोcumentation. Try
 * http://www.vt100.net/manx/details?pn=EK-104AA-TM-001;id=21;cp=1
 */

/*
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>
#समावेश <linux/workqueue.h>

#घोषणा DRIVER_DESC	"LK keyboard driver"

MODULE_AUTHOR("Jan-Benedict Glaw <jbglaw@lug-owl.de>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Known parameters:
 *	bell_volume
 *	keyclick_volume
 *	ctrlclick_volume
 *
 * Please notice that there's not yet an API to set these at runसमय.
 */
अटल पूर्णांक bell_volume = 100; /* % */
module_param(bell_volume, पूर्णांक, 0);
MODULE_PARM_DESC(bell_volume, "Bell volume (in %). default is 100%");

अटल पूर्णांक keyclick_volume = 100; /* % */
module_param(keyclick_volume, पूर्णांक, 0);
MODULE_PARM_DESC(keyclick_volume, "Keyclick volume (in %), default is 100%");

अटल पूर्णांक ctrlclick_volume = 100; /* % */
module_param(ctrlclick_volume, पूर्णांक, 0);
MODULE_PARM_DESC(ctrlclick_volume, "Ctrlclick volume (in %), default is 100%");

अटल पूर्णांक lk201_compose_is_alt;
module_param(lk201_compose_is_alt, पूर्णांक, 0);
MODULE_PARM_DESC(lk201_compose_is_alt,
		 "If set non-zero, LK201' Compose key will act as an Alt key");



#अघोषित LKKBD_DEBUG
#अगर_घोषित LKKBD_DEBUG
#घोषणा DBG(x...) prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG(x...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/* LED control */
#घोषणा LK_LED_WAIT		0x81
#घोषणा LK_LED_COMPOSE		0x82
#घोषणा LK_LED_SHIFTLOCK	0x84
#घोषणा LK_LED_SCROLLLOCK	0x88
#घोषणा LK_CMD_LED_ON		0x13
#घोषणा LK_CMD_LED_OFF		0x11

/* Mode control */
#घोषणा LK_MODE_DOWN		0x80
#घोषणा LK_MODE_AUTODOWN	0x82
#घोषणा LK_MODE_UPDOWN		0x86
#घोषणा LK_CMD_SET_MODE(mode, भाग)	((mode) | ((भाग) << 3))

/* Misc commands */
#घोषणा LK_CMD_ENABLE_KEYCLICK	0x1b
#घोषणा LK_CMD_DISABLE_KEYCLICK	0x99
#घोषणा LK_CMD_DISABLE_BELL	0xa1
#घोषणा LK_CMD_SOUND_BELL	0xa7
#घोषणा LK_CMD_ENABLE_BELL	0x23
#घोषणा LK_CMD_DISABLE_CTRCLICK	0xb9
#घोषणा LK_CMD_ENABLE_CTRCLICK	0xbb
#घोषणा LK_CMD_SET_DEFAULTS	0xd3
#घोषणा LK_CMD_POWERCYCLE_RESET	0xfd
#घोषणा LK_CMD_ENABLE_LK401	0xe9
#घोषणा LK_CMD_REQUEST_ID	0xab

/* Misc responses from keyboard */
#घोषणा LK_STUCK_KEY		0x3d
#घोषणा LK_SELFTEST_FAILED	0x3e
#घोषणा LK_ALL_KEYS_UP		0xb3
#घोषणा LK_METRONOME		0xb4
#घोषणा LK_OUTPUT_ERROR		0xb5
#घोषणा LK_INPUT_ERROR		0xb6
#घोषणा LK_KBD_LOCKED		0xb7
#घोषणा LK_KBD_TEST_MODE_ACK	0xb8
#घोषणा LK_PREFIX_KEY_DOWN	0xb9
#घोषणा LK_MODE_CHANGE_ACK	0xba
#घोषणा LK_RESPONSE_RESERVED	0xbb

#घोषणा LK_NUM_KEYCODES		256
#घोषणा LK_NUM_IGNORE_BYTES	6

अटल अचिन्हित लघु lkkbd_keycode[LK_NUM_KEYCODES] = अणु
	[0x56] = KEY_F1,
	[0x57] = KEY_F2,
	[0x58] = KEY_F3,
	[0x59] = KEY_F4,
	[0x5a] = KEY_F5,
	[0x64] = KEY_F6,
	[0x65] = KEY_F7,
	[0x66] = KEY_F8,
	[0x67] = KEY_F9,
	[0x68] = KEY_F10,
	[0x71] = KEY_F11,
	[0x72] = KEY_F12,
	[0x73] = KEY_F13,
	[0x74] = KEY_F14,
	[0x7c] = KEY_F15,
	[0x7d] = KEY_F16,
	[0x80] = KEY_F17,
	[0x81] = KEY_F18,
	[0x82] = KEY_F19,
	[0x83] = KEY_F20,
	[0x8a] = KEY_FIND,
	[0x8b] = KEY_INSERT,
	[0x8c] = KEY_DELETE,
	[0x8d] = KEY_SELECT,
	[0x8e] = KEY_PAGEUP,
	[0x8f] = KEY_PAGEDOWN,
	[0x92] = KEY_KP0,
	[0x94] = KEY_KPDOT,
	[0x95] = KEY_KPENTER,
	[0x96] = KEY_KP1,
	[0x97] = KEY_KP2,
	[0x98] = KEY_KP3,
	[0x99] = KEY_KP4,
	[0x9a] = KEY_KP5,
	[0x9b] = KEY_KP6,
	[0x9c] = KEY_KPCOMMA,
	[0x9d] = KEY_KP7,
	[0x9e] = KEY_KP8,
	[0x9f] = KEY_KP9,
	[0xa0] = KEY_KPMINUS,
	[0xa1] = KEY_PROG1,
	[0xa2] = KEY_PROG2,
	[0xa3] = KEY_PROG3,
	[0xa4] = KEY_PROG4,
	[0xa7] = KEY_LEFT,
	[0xa8] = KEY_RIGHT,
	[0xa9] = KEY_DOWN,
	[0xaa] = KEY_UP,
	[0xab] = KEY_RIGHTSHIFT,
	[0xac] = KEY_LEFTALT,
	[0xad] = KEY_COMPOSE, /* Right Compose, that is. */
	[0xae] = KEY_LEFTSHIFT, /* Same as KEY_RIGHTSHIFT on LK201 */
	[0xaf] = KEY_LEFTCTRL,
	[0xb0] = KEY_CAPSLOCK,
	[0xb1] = KEY_COMPOSE, /* Left Compose, that is. */
	[0xb2] = KEY_RIGHTALT,
	[0xbc] = KEY_BACKSPACE,
	[0xbd] = KEY_ENTER,
	[0xbe] = KEY_TAB,
	[0xbf] = KEY_ESC,
	[0xc0] = KEY_1,
	[0xc1] = KEY_Q,
	[0xc2] = KEY_A,
	[0xc3] = KEY_Z,
	[0xc5] = KEY_2,
	[0xc6] = KEY_W,
	[0xc7] = KEY_S,
	[0xc8] = KEY_X,
	[0xc9] = KEY_102ND,
	[0xcb] = KEY_3,
	[0xcc] = KEY_E,
	[0xcd] = KEY_D,
	[0xce] = KEY_C,
	[0xd0] = KEY_4,
	[0xd1] = KEY_R,
	[0xd2] = KEY_F,
	[0xd3] = KEY_V,
	[0xd4] = KEY_SPACE,
	[0xd6] = KEY_5,
	[0xd7] = KEY_T,
	[0xd8] = KEY_G,
	[0xd9] = KEY_B,
	[0xdb] = KEY_6,
	[0xdc] = KEY_Y,
	[0xdd] = KEY_H,
	[0xde] = KEY_N,
	[0xe0] = KEY_7,
	[0xe1] = KEY_U,
	[0xe2] = KEY_J,
	[0xe3] = KEY_M,
	[0xe5] = KEY_8,
	[0xe6] = KEY_I,
	[0xe7] = KEY_K,
	[0xe8] = KEY_COMMA,
	[0xea] = KEY_9,
	[0xeb] = KEY_O,
	[0xec] = KEY_L,
	[0xed] = KEY_DOT,
	[0xef] = KEY_0,
	[0xf0] = KEY_P,
	[0xf2] = KEY_SEMICOLON,
	[0xf3] = KEY_SLASH,
	[0xf5] = KEY_EQUAL,
	[0xf6] = KEY_RIGHTBRACE,
	[0xf7] = KEY_BACKSLASH,
	[0xf9] = KEY_MINUS,
	[0xfa] = KEY_LEFTBRACE,
	[0xfb] = KEY_APOSTROPHE,
पूर्ण;

#घोषणा CHECK_LED(LK, VAR_ON, VAR_OFF, LED, BITS) करो अणु		\
	अगर (test_bit(LED, (LK)->dev->led))			\
		VAR_ON |= BITS;					\
	अन्यथा							\
		VAR_OFF |= BITS;				\
	पूर्ण जबतक (0)

/*
 * Per-keyboard data
 */
काष्ठा lkkbd अणु
	अचिन्हित लघु keycode[LK_NUM_KEYCODES];
	पूर्णांक ignore_bytes;
	अचिन्हित अक्षर id[LK_NUM_IGNORE_BYTES];
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	काष्ठा work_काष्ठा tq;
	अक्षर name[64];
	अक्षर phys[32];
	अक्षर type;
	पूर्णांक bell_volume;
	पूर्णांक keyclick_volume;
	पूर्णांक ctrlclick_volume;
पूर्ण;

#अगर_घोषित LKKBD_DEBUG
/*
 * Responses from the keyboard and mapping back to their names.
 */
अटल काष्ठा अणु
	अचिन्हित अक्षर value;
	अचिन्हित अक्षर *name;
पूर्ण lk_response[] = अणु
#घोषणा RESPONSE(x) अणु .value = (x), .name = #x, पूर्ण
	RESPONSE(LK_STUCK_KEY),
	RESPONSE(LK_SELFTEST_FAILED),
	RESPONSE(LK_ALL_KEYS_UP),
	RESPONSE(LK_METRONOME),
	RESPONSE(LK_OUTPUT_ERROR),
	RESPONSE(LK_INPUT_ERROR),
	RESPONSE(LK_KBD_LOCKED),
	RESPONSE(LK_KBD_TEST_MODE_ACK),
	RESPONSE(LK_PREFIX_KEY_DOWN),
	RESPONSE(LK_MODE_CHANGE_ACK),
	RESPONSE(LK_RESPONSE_RESERVED),
#अघोषित RESPONSE
पूर्ण;

अटल अचिन्हित अक्षर *response_name(अचिन्हित अक्षर value)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(lk_response); i++)
		अगर (lk_response[i].value == value)
			वापस lk_response[i].name;

	वापस "<unknown>";
पूर्ण
#पूर्ण_अगर /* LKKBD_DEBUG */

/*
 * Calculate volume parameter byte क्रम a given volume.
 */
अटल अचिन्हित अक्षर volume_to_hw(पूर्णांक volume_percent)
अणु
	अचिन्हित अक्षर ret = 0;

	अगर (volume_percent < 0)
		volume_percent = 0;
	अगर (volume_percent > 100)
		volume_percent = 100;

	अगर (volume_percent >= 0)
		ret = 7;
	अगर (volume_percent >= 13)	/* 12.5 */
		ret = 6;
	अगर (volume_percent >= 25)
		ret = 5;
	अगर (volume_percent >= 38)	/* 37.5 */
		ret = 4;
	अगर (volume_percent >= 50)
		ret = 3;
	अगर (volume_percent >= 63)	/* 62.5 */
		ret = 2;		/* This is the शेष volume */
	अगर (volume_percent >= 75)
		ret = 1;
	अगर (volume_percent >= 88)	/* 87.5 */
		ret = 0;

	ret |= 0x80;

	वापस ret;
पूर्ण

अटल व्योम lkkbd_detection_करोne(काष्ठा lkkbd *lk)
अणु
	पूर्णांक i;

	/*
	 * Reset setting क्रम Compose key. Let Compose be KEY_COMPOSE.
	 */
	lk->keycode[0xb1] = KEY_COMPOSE;

	/*
	 * Prपूर्णांक keyboard name and modअगरy Compose=Alt on user's request.
	 */
	चयन (lk->id[4]) अणु
	हाल 1:
		strlcpy(lk->name, "DEC LK201 keyboard", माप(lk->name));

		अगर (lk201_compose_is_alt)
			lk->keycode[0xb1] = KEY_LEFTALT;
		अवरोध;

	हाल 2:
		strlcpy(lk->name, "DEC LK401 keyboard", माप(lk->name));
		अवरोध;

	शेष:
		strlcpy(lk->name, "Unknown DEC keyboard", माप(lk->name));
		prपूर्णांकk(KERN_ERR
			"lkkbd: keyboard on %s is unknown, please report to "
			"Jan-Benedict Glaw <jbglaw@lug-owl.de>\n", lk->phys);
		prपूर्णांकk(KERN_ERR "lkkbd: keyboard ID'ed as:");
		क्रम (i = 0; i < LK_NUM_IGNORE_BYTES; i++)
			prपूर्णांकk(" 0x%02x", lk->id[i]);
		prपूर्णांकk("\n");
		अवरोध;
	पूर्ण

	prपूर्णांकk(KERN_INFO "lkkbd: keyboard on %s identified as: %s\n",
		lk->phys, lk->name);

	/*
	 * Report errors during keyboard boot-up.
	 */
	चयन (lk->id[2]) अणु
	हाल 0x00:
		/* All okay */
		अवरोध;

	हाल LK_STUCK_KEY:
		prपूर्णांकk(KERN_ERR "lkkbd: Stuck key on keyboard at %s\n",
			lk->phys);
		अवरोध;

	हाल LK_SELFTEST_FAILED:
		prपूर्णांकk(KERN_ERR
			"lkkbd: Selftest failed on keyboard at %s, "
			"keyboard may not work properly\n", lk->phys);
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR
			"lkkbd: Unknown error %02x on keyboard at %s\n",
			lk->id[2], lk->phys);
		अवरोध;
	पूर्ण

	/*
	 * Try to hपूर्णांक user अगर there's a stuck key.
	 */
	अगर (lk->id[2] == LK_STUCK_KEY && lk->id[3] != 0)
		prपूर्णांकk(KERN_ERR
			"Scancode of stuck key is 0x%02x, keycode is 0x%04x\n",
			lk->id[3], lk->keycode[lk->id[3]]);
पूर्ण

/*
 * lkkbd_पूर्णांकerrupt() is called by the low level driver when a अक्षरacter
 * is received.
 */
अटल irqवापस_t lkkbd_पूर्णांकerrupt(काष्ठा serio *serio,
				   अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा lkkbd *lk = serio_get_drvdata(serio);
	काष्ठा input_dev *input_dev = lk->dev;
	अचिन्हित पूर्णांक keycode;
	पूर्णांक i;

	DBG(KERN_INFO "Got byte 0x%02x\n", data);

	अगर (lk->ignore_bytes > 0) अणु
		DBG(KERN_INFO "Ignoring a byte on %s\n", lk->name);
		lk->id[LK_NUM_IGNORE_BYTES - lk->ignore_bytes--] = data;

		अगर (lk->ignore_bytes == 0)
			lkkbd_detection_करोne(lk);

		वापस IRQ_HANDLED;
	पूर्ण

	चयन (data) अणु
	हाल LK_ALL_KEYS_UP:
		क्रम (i = 0; i < ARRAY_SIZE(lkkbd_keycode); i++)
			input_report_key(input_dev, lk->keycode[i], 0);
		input_sync(input_dev);
		अवरोध;

	हाल 0x01:
		DBG(KERN_INFO "Got 0x01, scheduling re-initialization\n");
		lk->ignore_bytes = LK_NUM_IGNORE_BYTES;
		lk->id[LK_NUM_IGNORE_BYTES - lk->ignore_bytes--] = data;
		schedule_work(&lk->tq);
		अवरोध;

	हाल LK_METRONOME:
	हाल LK_OUTPUT_ERROR:
	हाल LK_INPUT_ERROR:
	हाल LK_KBD_LOCKED:
	हाल LK_KBD_TEST_MODE_ACK:
	हाल LK_PREFIX_KEY_DOWN:
	हाल LK_MODE_CHANGE_ACK:
	हाल LK_RESPONSE_RESERVED:
		DBG(KERN_INFO "Got %s and don't know how to handle...\n",
			response_name(data));
		अवरोध;

	शेष:
		keycode = lk->keycode[data];
		अगर (keycode != KEY_RESERVED) अणु
			input_report_key(input_dev, keycode,
					 !test_bit(keycode, input_dev->key));
			input_sync(input_dev);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING
				"%s: Unknown key with scancode 0x%02x on %s.\n",
				__खाता__, data, lk->name);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम lkkbd_toggle_leds(काष्ठा lkkbd *lk)
अणु
	काष्ठा serio *serio = lk->serio;
	अचिन्हित अक्षर leds_on = 0;
	अचिन्हित अक्षर leds_off = 0;

	CHECK_LED(lk, leds_on, leds_off, LED_CAPSL, LK_LED_SHIFTLOCK);
	CHECK_LED(lk, leds_on, leds_off, LED_COMPOSE, LK_LED_COMPOSE);
	CHECK_LED(lk, leds_on, leds_off, LED_SCROLLL, LK_LED_SCROLLLOCK);
	CHECK_LED(lk, leds_on, leds_off, LED_SLEEP, LK_LED_WAIT);
	अगर (leds_on != 0) अणु
		serio_ग_लिखो(serio, LK_CMD_LED_ON);
		serio_ग_लिखो(serio, leds_on);
	पूर्ण
	अगर (leds_off != 0) अणु
		serio_ग_लिखो(serio, LK_CMD_LED_OFF);
		serio_ग_लिखो(serio, leds_off);
	पूर्ण
पूर्ण

अटल व्योम lkkbd_toggle_keyclick(काष्ठा lkkbd *lk, bool on)
अणु
	काष्ठा serio *serio = lk->serio;

	अगर (on) अणु
		DBG("%s: Activating key clicks\n", __func__);
		serio_ग_लिखो(serio, LK_CMD_ENABLE_KEYCLICK);
		serio_ग_लिखो(serio, volume_to_hw(lk->keyclick_volume));
		serio_ग_लिखो(serio, LK_CMD_ENABLE_CTRCLICK);
		serio_ग_लिखो(serio, volume_to_hw(lk->ctrlclick_volume));
	पूर्ण अन्यथा अणु
		DBG("%s: Deactivating key clicks\n", __func__);
		serio_ग_लिखो(serio, LK_CMD_DISABLE_KEYCLICK);
		serio_ग_लिखो(serio, LK_CMD_DISABLE_CTRCLICK);
	पूर्ण

पूर्ण

/*
 * lkkbd_event() handles events from the input module.
 */
अटल पूर्णांक lkkbd_event(काष्ठा input_dev *dev,
			अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा lkkbd *lk = input_get_drvdata(dev);

	चयन (type) अणु
	हाल EV_LED:
		lkkbd_toggle_leds(lk);
		वापस 0;

	हाल EV_SND:
		चयन (code) अणु
		हाल SND_CLICK:
			lkkbd_toggle_keyclick(lk, value);
			वापस 0;

		हाल SND_BELL:
			अगर (value != 0)
				serio_ग_लिखो(lk->serio, LK_CMD_SOUND_BELL);

			वापस 0;
		पूर्ण

		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR "%s(): Got unknown type %d, code %d, value %d\n",
			__func__, type, code, value);
	पूर्ण

	वापस -1;
पूर्ण

/*
 * lkkbd_reinit() sets leds and beeps to a state the computer remembers they
 * were in.
 */
अटल व्योम lkkbd_reinit(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lkkbd *lk = container_of(work, काष्ठा lkkbd, tq);
	पूर्णांक भागision;

	/* Ask क्रम ID */
	serio_ग_लिखो(lk->serio, LK_CMD_REQUEST_ID);

	/* Reset parameters */
	serio_ग_लिखो(lk->serio, LK_CMD_SET_DEFAULTS);

	/* Set LEDs */
	lkkbd_toggle_leds(lk);

	/*
	 * Try to activate extended LK401 mode. This command will
	 * only work with a LK401 keyboard and grants access to
	 * LAlt, RAlt, RCompose and RShअगरt.
	 */
	serio_ग_लिखो(lk->serio, LK_CMD_ENABLE_LK401);

	/* Set all keys to UPDOWN mode */
	क्रम (भागision = 1; भागision <= 14; भागision++)
		serio_ग_लिखो(lk->serio,
			    LK_CMD_SET_MODE(LK_MODE_UPDOWN, भागision));

	/* Enable bell and set volume */
	serio_ग_लिखो(lk->serio, LK_CMD_ENABLE_BELL);
	serio_ग_लिखो(lk->serio, volume_to_hw(lk->bell_volume));

	/* Enable/disable keyclick (and possibly set volume) */
	lkkbd_toggle_keyclick(lk, test_bit(SND_CLICK, lk->dev->snd));

	/* Sound the bell अगर needed */
	अगर (test_bit(SND_BELL, lk->dev->snd))
		serio_ग_लिखो(lk->serio, LK_CMD_SOUND_BELL);
पूर्ण

/*
 * lkkbd_connect() probes क्रम a LK keyboard and fills the necessary काष्ठाures.
 */
अटल पूर्णांक lkkbd_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा lkkbd *lk;
	काष्ठा input_dev *input_dev;
	पूर्णांक i;
	पूर्णांक err;

	lk = kzalloc(माप(काष्ठा lkkbd), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!lk || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	lk->serio = serio;
	lk->dev = input_dev;
	INIT_WORK(&lk->tq, lkkbd_reinit);
	lk->bell_volume = bell_volume;
	lk->keyclick_volume = keyclick_volume;
	lk->ctrlclick_volume = ctrlclick_volume;
	स_नकल(lk->keycode, lkkbd_keycode, माप(lk->keycode));

	strlcpy(lk->name, "DEC LK keyboard", माप(lk->name));
	snम_लिखो(lk->phys, माप(lk->phys), "%s/input0", serio->phys);

	input_dev->name = lk->name;
	input_dev->phys = lk->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_LKKBD;
	input_dev->id.product = 0;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;
	input_dev->event = lkkbd_event;

	input_set_drvdata(input_dev, lk);

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(EV_LED, input_dev->evbit);
	__set_bit(EV_SND, input_dev->evbit);
	__set_bit(EV_REP, input_dev->evbit);
	__set_bit(LED_CAPSL, input_dev->ledbit);
	__set_bit(LED_SLEEP, input_dev->ledbit);
	__set_bit(LED_COMPOSE, input_dev->ledbit);
	__set_bit(LED_SCROLLL, input_dev->ledbit);
	__set_bit(SND_BELL, input_dev->sndbit);
	__set_bit(SND_CLICK, input_dev->sndbit);

	input_dev->keycode = lk->keycode;
	input_dev->keycodesize = माप(lk->keycode[0]);
	input_dev->keycodemax = ARRAY_SIZE(lk->keycode);

	क्रम (i = 0; i < LK_NUM_KEYCODES; i++)
		__set_bit(lk->keycode[i], input_dev->keybit);
	__clear_bit(KEY_RESERVED, input_dev->keybit);

	serio_set_drvdata(serio, lk);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(lk->dev);
	अगर (err)
		जाओ fail3;

	serio_ग_लिखो(lk->serio, LK_CMD_POWERCYCLE_RESET);

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(lk);
	वापस err;
पूर्ण

/*
 * lkkbd_disconnect() unरेजिस्टरs and बंदs behind us.
 */
अटल व्योम lkkbd_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा lkkbd *lk = serio_get_drvdata(serio);

	input_get_device(lk->dev);
	input_unरेजिस्टर_device(lk->dev);
	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_put_device(lk->dev);
	kमुक्त(lk);
पूर्ण

अटल स्थिर काष्ठा serio_device_id lkkbd_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_LKKBD,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, lkkbd_serio_ids);

अटल काष्ठा serio_driver lkkbd_drv = अणु
	.driver		= अणु
		.name	= "lkkbd",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= lkkbd_serio_ids,
	.connect	= lkkbd_connect,
	.disconnect	= lkkbd_disconnect,
	.पूर्णांकerrupt	= lkkbd_पूर्णांकerrupt,
पूर्ण;

module_serio_driver(lkkbd_drv);
