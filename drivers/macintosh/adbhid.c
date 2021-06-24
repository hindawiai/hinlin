<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/macपूर्णांकosh/adbhid.c
 *
 * ADB HID driver क्रम Power Macपूर्णांकosh computers.
 *
 * Adapted from drivers/macपूर्णांकosh/mac_keyb.c by Franz Sirl.
 * drivers/macपूर्णांकosh/mac_keyb.c was Copyright (C) 1996 Paul Mackerras
 * with considerable contributions from Ben Herrenschmidt and others.
 *
 * Copyright (C) 2000 Franz Sirl.
 *
 * Adapted to ADB changes and support क्रम more devices by
 * Benjamin Herrenschmidt. Adapted from code in MkLinux
 * and reworked.
 * 
 * Supported devices:
 *
 * - Standard 1 button mouse
 * - All standard Apple Extended protocol (handler ID 4)
 * - mouseman and trackman mice & trackballs 
 * - PowerBook Trackpad (शेष setup: enable tapping)
 * - MicroSpeed mouse & trackball (needs testing)
 * - CH Products Trackball Pro (needs testing)
 * - Contour Design (Contour Mouse)
 * - Hunter digital (NoHandsMouse)
 * - Kensignton TurboMouse 5 (needs testing)
 * - Mouse Systems A3 mice and trackballs <aidan@kublai.com>
 * - MacAlly 2-buttons mouse (needs testing) <pochini@denise.shiny.it>
 *
 * To करो:
 *
 * Improve Kensington support.
 * Split mouse/kbd
 * Move to syfs
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/input.h>

#समावेश <linux/adb.h>
#समावेश <linux/cuda.h>
#समावेश <linux/pmu.h>

#समावेश <यंत्र/machdep.h>
#अगर_घोषित CONFIG_PPC_PMAC
#समावेश <यंत्र/backlight.h>
#समावेश <यंत्र/pmac_feature.h>
#पूर्ण_अगर

MODULE_AUTHOR("Franz Sirl <Franz.Sirl-kernel@lauterbach.com>");

अटल पूर्णांक restore_capslock_events;
module_param(restore_capslock_events, पूर्णांक, 0644);
MODULE_PARM_DESC(restore_capslock_events,
	"Produce keypress events for capslock on both keyup and keydown.");

#घोषणा KEYB_KEYREG	0	/* रेजिस्टर # क्रम key up/करोwn data */
#घोषणा KEYB_LEDREG	2	/* रेजिस्टर # क्रम leds on ADB keyboard */
#घोषणा MOUSE_DATAREG	0	/* reg# क्रम movement/button codes from mouse */

अटल पूर्णांक adb_message_handler(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);
अटल काष्ठा notअगरier_block adbhid_adb_notअगरier = अणु
	.notअगरier_call	= adb_message_handler,
पूर्ण;

/* Some special keys */
#घोषणा ADB_KEY_DEL		0x33
#घोषणा ADB_KEY_CMD		0x37
#घोषणा ADB_KEY_CAPSLOCK	0x39
#घोषणा ADB_KEY_FN		0x3f
#घोषणा ADB_KEY_FWDEL		0x75
#घोषणा ADB_KEY_POWER_OLD	0x7e
#घोषणा ADB_KEY_POWER		0x7f

अटल स्थिर u16 adb_to_linux_keycodes[128] = अणु
	/* 0x00 */ KEY_A, 		/*  30 */
	/* 0x01 */ KEY_S, 		/*  31 */
	/* 0x02 */ KEY_D,		/*  32 */
	/* 0x03 */ KEY_F,		/*  33 */
	/* 0x04 */ KEY_H,		/*  35 */
	/* 0x05 */ KEY_G,		/*  34 */
	/* 0x06 */ KEY_Z,		/*  44 */
	/* 0x07 */ KEY_X,		/*  45 */
	/* 0x08 */ KEY_C,		/*  46 */
	/* 0x09 */ KEY_V,		/*  47 */
	/* 0x0a */ KEY_102ND,		/*  86 */
	/* 0x0b */ KEY_B,		/*  48 */
	/* 0x0c */ KEY_Q,		/*  16 */
	/* 0x0d */ KEY_W,		/*  17 */
	/* 0x0e */ KEY_E,		/*  18 */
	/* 0x0f */ KEY_R,		/*  19 */
	/* 0x10 */ KEY_Y,		/*  21 */
	/* 0x11 */ KEY_T,		/*  20 */
	/* 0x12 */ KEY_1,		/*   2 */
	/* 0x13 */ KEY_2,		/*   3 */
	/* 0x14 */ KEY_3,		/*   4 */
	/* 0x15 */ KEY_4,		/*   5 */
	/* 0x16 */ KEY_6,		/*   7 */
	/* 0x17 */ KEY_5,		/*   6 */
	/* 0x18 */ KEY_EQUAL,		/*  13 */
	/* 0x19 */ KEY_9,		/*  10 */
	/* 0x1a */ KEY_7,		/*   8 */
	/* 0x1b */ KEY_MINUS,		/*  12 */
	/* 0x1c */ KEY_8,		/*   9 */
	/* 0x1d */ KEY_0,		/*  11 */
	/* 0x1e */ KEY_RIGHTBRACE,	/*  27 */
	/* 0x1f */ KEY_O,		/*  24 */
	/* 0x20 */ KEY_U,		/*  22 */
	/* 0x21 */ KEY_LEFTBRACE,	/*  26 */
	/* 0x22 */ KEY_I,		/*  23 */
	/* 0x23 */ KEY_P,		/*  25 */
	/* 0x24 */ KEY_ENTER,		/*  28 */
	/* 0x25 */ KEY_L,		/*  38 */
	/* 0x26 */ KEY_J,		/*  36 */
	/* 0x27 */ KEY_APOSTROPHE,	/*  40 */
	/* 0x28 */ KEY_K,		/*  37 */
	/* 0x29 */ KEY_SEMICOLON,	/*  39 */
	/* 0x2a */ KEY_BACKSLASH,	/*  43 */
	/* 0x2b */ KEY_COMMA,		/*  51 */
	/* 0x2c */ KEY_SLASH,		/*  53 */
	/* 0x2d */ KEY_N,		/*  49 */
	/* 0x2e */ KEY_M,		/*  50 */
	/* 0x2f */ KEY_DOT,		/*  52 */
	/* 0x30 */ KEY_TAB,		/*  15 */
	/* 0x31 */ KEY_SPACE,		/*  57 */
	/* 0x32 */ KEY_GRAVE,		/*  41 */
	/* 0x33 */ KEY_BACKSPACE,	/*  14 */
	/* 0x34 */ KEY_KPENTER,		/*  96 */
	/* 0x35 */ KEY_ESC,		/*   1 */
	/* 0x36 */ KEY_LEFTCTRL,	/*  29 */
	/* 0x37 */ KEY_LEFTMETA,	/* 125 */
	/* 0x38 */ KEY_LEFTSHIFT,	/*  42 */
	/* 0x39 */ KEY_CAPSLOCK,	/*  58 */
	/* 0x3a */ KEY_LEFTALT,		/*  56 */
	/* 0x3b */ KEY_LEFT,		/* 105 */
	/* 0x3c */ KEY_RIGHT,		/* 106 */
	/* 0x3d */ KEY_DOWN,		/* 108 */
	/* 0x3e */ KEY_UP,		/* 103 */
	/* 0x3f */ KEY_FN,		/* 0x1d0 */
	/* 0x40 */ 0,
	/* 0x41 */ KEY_KPDOT,		/*  83 */
	/* 0x42 */ 0,
	/* 0x43 */ KEY_KPASTERISK,	/*  55 */
	/* 0x44 */ 0,
	/* 0x45 */ KEY_KPPLUS,		/*  78 */
	/* 0x46 */ 0,
	/* 0x47 */ KEY_NUMLOCK,		/*  69 */
	/* 0x48 */ 0,
	/* 0x49 */ 0,
	/* 0x4a */ 0,
	/* 0x4b */ KEY_KPSLASH,		/*  98 */
	/* 0x4c */ KEY_KPENTER,		/*  96 */
	/* 0x4d */ 0,
	/* 0x4e */ KEY_KPMINUS,		/*  74 */
	/* 0x4f */ 0,
	/* 0x50 */ 0,
	/* 0x51 */ KEY_KPEQUAL,		/* 117 */
	/* 0x52 */ KEY_KP0,		/*  82 */
	/* 0x53 */ KEY_KP1,		/*  79 */
	/* 0x54 */ KEY_KP2,		/*  80 */
	/* 0x55 */ KEY_KP3,		/*  81 */
	/* 0x56 */ KEY_KP4,		/*  75 */
	/* 0x57 */ KEY_KP5,		/*  76 */
	/* 0x58 */ KEY_KP6,		/*  77 */
	/* 0x59 */ KEY_KP7,		/*  71 */
	/* 0x5a */ 0,
	/* 0x5b */ KEY_KP8,		/*  72 */
	/* 0x5c */ KEY_KP9,		/*  73 */
	/* 0x5d */ KEY_YEN,		/* 124 */
	/* 0x5e */ KEY_RO,		/*  89 */
	/* 0x5f */ KEY_KPCOMMA,		/* 121 */
	/* 0x60 */ KEY_F5,		/*  63 */
	/* 0x61 */ KEY_F6,		/*  64 */
	/* 0x62 */ KEY_F7,		/*  65 */
	/* 0x63 */ KEY_F3,		/*  61 */
	/* 0x64 */ KEY_F8,		/*  66 */
	/* 0x65 */ KEY_F9,		/*  67 */
	/* 0x66 */ KEY_HANJA,		/* 123 */
	/* 0x67 */ KEY_F11,		/*  87 */
	/* 0x68 */ KEY_HANGEUL,		/* 122 */
	/* 0x69 */ KEY_SYSRQ,		/*  99 */
	/* 0x6a */ 0,
	/* 0x6b */ KEY_SCROLLLOCK,	/*  70 */
	/* 0x6c */ 0,
	/* 0x6d */ KEY_F10,		/*  68 */
	/* 0x6e */ KEY_COMPOSE,		/* 127 */
	/* 0x6f */ KEY_F12,		/*  88 */
	/* 0x70 */ 0,
	/* 0x71 */ KEY_PAUSE,		/* 119 */
	/* 0x72 */ KEY_INSERT,		/* 110 */
	/* 0x73 */ KEY_HOME,		/* 102 */
	/* 0x74 */ KEY_PAGEUP,		/* 104 */
	/* 0x75 */ KEY_DELETE,		/* 111 */
	/* 0x76 */ KEY_F4,		/*  62 */
	/* 0x77 */ KEY_END,		/* 107 */
	/* 0x78 */ KEY_F2,		/*  60 */
	/* 0x79 */ KEY_PAGEDOWN,	/* 109 */
	/* 0x7a */ KEY_F1,		/*  59 */
	/* 0x7b */ KEY_RIGHTSHIFT,	/*  54 */
	/* 0x7c */ KEY_RIGHTALT,	/* 100 */
	/* 0x7d */ KEY_RIGHTCTRL,	/*  97 */
	/* 0x7e */ KEY_RIGHTMETA,	/* 126 */
	/* 0x7f */ KEY_POWER,		/* 116 */
पूर्ण;

काष्ठा adbhid अणु
	काष्ठा input_dev *input;
	पूर्णांक id;
	पूर्णांक शेष_id;
	पूर्णांक original_handler_id;
	पूर्णांक current_handler_id;
	पूर्णांक mouse_kind;
	u16 *keycode;
	अक्षर name[64];
	अक्षर phys[32];
	पूर्णांक flags;
पूर्ण;

#घोषणा FLAG_FN_KEY_PRESSED		0x00000001
#घोषणा FLAG_POWER_FROM_FN		0x00000002
#घोषणा FLAG_EMU_FWDEL_DOWN		0x00000004
#घोषणा FLAG_CAPSLOCK_TRANSLATE		0x00000008
#घोषणा FLAG_CAPSLOCK_DOWN		0x00000010
#घोषणा FLAG_CAPSLOCK_IGNORE_NEXT	0x00000020
#घोषणा FLAG_POWER_KEY_PRESSED		0x00000040

अटल काष्ठा adbhid *adbhid[16];

अटल व्योम adbhid_probe(व्योम);

अटल व्योम adbhid_input_keycode(पूर्णांक, पूर्णांक, पूर्णांक);

अटल व्योम init_trackpad(पूर्णांक id);
अटल व्योम init_trackball(पूर्णांक id);
अटल व्योम init_turbomouse(पूर्णांक id);
अटल व्योम init_microspeed(पूर्णांक id);
अटल व्योम init_ms_a3(पूर्णांक id);

अटल काष्ठा adb_ids keyboard_ids;
अटल काष्ठा adb_ids mouse_ids;
अटल काष्ठा adb_ids buttons_ids;

/* Kind of keyboard, see Apple technote 1152  */
#घोषणा ADB_KEYBOARD_UNKNOWN	0
#घोषणा ADB_KEYBOARD_ANSI	0x0100
#घोषणा ADB_KEYBOARD_ISO	0x0200
#घोषणा ADB_KEYBOARD_JIS	0x0300

/* Kind of mouse  */
#घोषणा ADBMOUSE_STANDARD_100	0	/* Standard 100cpi mouse (handler 1) */
#घोषणा ADBMOUSE_STANDARD_200	1	/* Standard 200cpi mouse (handler 2) */
#घोषणा ADBMOUSE_EXTENDED	2	/* Apple Extended mouse (handler 4) */
#घोषणा ADBMOUSE_TRACKBALL	3	/* TrackBall (handler 4) */
#घोषणा ADBMOUSE_TRACKPAD       4	/* Apple's PowerBook trackpad (handler 4) */
#घोषणा ADBMOUSE_TURBOMOUSE5    5	/* Turbomouse 5 (previously req. mousehack) */
#घोषणा ADBMOUSE_MICROSPEED	6	/* Microspeed mouse (&trackball ?), MacPoपूर्णांक */
#घोषणा ADBMOUSE_TRACKBALLPRO	7	/* Trackball Pro (special buttons) */
#घोषणा ADBMOUSE_MS_A3		8	/* Mouse प्रणालीs A3 trackball (handler 3) */
#घोषणा ADBMOUSE_MACALLY2	9	/* MacAlly 2-button mouse */

अटल व्योम
adbhid_keyboard_input(अचिन्हित अक्षर *data, पूर्णांक nb, पूर्णांक apoll)
अणु
	पूर्णांक id = (data[0] >> 4) & 0x0f;

	अगर (!adbhid[id]) अणु
		pr_err("ADB HID on ID %d not yet registered, packet %#02x, %#02x, %#02x, %#02x\n",
		       id, data[0], data[1], data[2], data[3]);
		वापस;
	पूर्ण

	/* first check this is from रेजिस्टर 0 */
	अगर (nb != 3 || (data[0] & 3) != KEYB_KEYREG)
		वापस;		/* ignore it */
	adbhid_input_keycode(id, data[1], 0);
	अगर (!(data[2] == 0xff || (data[2] == 0x7f && data[1] == 0x7f)))
		adbhid_input_keycode(id, data[2], 0);
पूर्ण

अटल व्योम
adbhid_input_keycode(पूर्णांक id, पूर्णांक scancode, पूर्णांक repeat)
अणु
	काष्ठा adbhid *ahid = adbhid[id];
	पूर्णांक keycode, up_flag, key;

	keycode = scancode & 0x7f;
	up_flag = scancode & 0x80;

	अगर (restore_capslock_events) अणु
		अगर (keycode == ADB_KEY_CAPSLOCK && !up_flag) अणु
			/* Key pressed, turning on the CapsLock LED.
			 * The next 0xff will be पूर्णांकerpreted as a release. */
			अगर (ahid->flags & FLAG_CAPSLOCK_IGNORE_NEXT) अणु
				/* Throw away this key event अगर it happens
				 * just after resume. */
				ahid->flags &= ~FLAG_CAPSLOCK_IGNORE_NEXT;
				वापस;
			पूर्ण अन्यथा अणु
				ahid->flags |= FLAG_CAPSLOCK_TRANSLATE
					| FLAG_CAPSLOCK_DOWN;
			पूर्ण
		पूर्ण अन्यथा अगर (scancode == 0xff &&
			   !(ahid->flags & FLAG_POWER_KEY_PRESSED)) अणु
			/* Scancode 0xff usually signअगरies that the capslock
			 * key was either pressed or released, or that the
			 * घातer button was released. */
			अगर (ahid->flags & FLAG_CAPSLOCK_TRANSLATE) अणु
				keycode = ADB_KEY_CAPSLOCK;
				अगर (ahid->flags & FLAG_CAPSLOCK_DOWN) अणु
					/* Key released */
					up_flag = 1;
					ahid->flags &= ~FLAG_CAPSLOCK_DOWN;
				पूर्ण अन्यथा अणु
					/* Key pressed */
					up_flag = 0;
					ahid->flags &= ~FLAG_CAPSLOCK_TRANSLATE;
				पूर्ण
			पूर्ण अन्यथा अणु
				pr_info("Spurious caps lock event (scancode 0xff).\n");
			पूर्ण
		पूर्ण
	पूर्ण

	चयन (keycode) अणु
	हाल ADB_KEY_CAPSLOCK:
		अगर (!restore_capslock_events) अणु
			/* Generate करोwn/up events क्रम CapsLock every समय. */
			input_report_key(ahid->input, KEY_CAPSLOCK, 1);
			input_sync(ahid->input);
			input_report_key(ahid->input, KEY_CAPSLOCK, 0);
			input_sync(ahid->input);
			वापस;
		पूर्ण
		अवरोध;
#अगर_घोषित CONFIG_PPC_PMAC
	हाल ADB_KEY_POWER_OLD: /* Power key on PBook 3400 needs remapping */
		चयन(pmac_call_feature(PMAC_FTR_GET_MB_INFO,
			शून्य, PMAC_MB_INFO_MODEL, 0)) अणु
		हाल PMAC_TYPE_COMET:
		हाल PMAC_TYPE_HOOPER:
		हाल PMAC_TYPE_KANGA:
			keycode = ADB_KEY_POWER;
		पूर्ण
		अवरोध;
	हाल ADB_KEY_POWER:
		/* Keep track of the घातer key state */
		अगर (up_flag)
			ahid->flags &= ~FLAG_POWER_KEY_PRESSED;
		अन्यथा
			ahid->flags |= FLAG_POWER_KEY_PRESSED;

		/* Fn + Command will produce a bogus "power" keycode */
		अगर (ahid->flags & FLAG_FN_KEY_PRESSED) अणु
			keycode = ADB_KEY_CMD;
			अगर (up_flag)
				ahid->flags &= ~FLAG_POWER_FROM_FN;
			अन्यथा
				ahid->flags |= FLAG_POWER_FROM_FN;
		पूर्ण अन्यथा अगर (ahid->flags & FLAG_POWER_FROM_FN) अणु
			keycode = ADB_KEY_CMD;
			ahid->flags &= ~FLAG_POWER_FROM_FN;
		पूर्ण
		अवरोध;
	हाल ADB_KEY_FN:
		/* Keep track of the Fn key state */
		अगर (up_flag) अणु
			ahid->flags &= ~FLAG_FN_KEY_PRESSED;
			/* Emulate Fn+delete = क्रमward delete */
			अगर (ahid->flags & FLAG_EMU_FWDEL_DOWN) अणु
				ahid->flags &= ~FLAG_EMU_FWDEL_DOWN;
				keycode = ADB_KEY_FWDEL;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा
			ahid->flags |= FLAG_FN_KEY_PRESSED;
		अवरोध;
	हाल ADB_KEY_DEL:
		/* Emulate Fn+delete = क्रमward delete */
		अगर (ahid->flags & FLAG_FN_KEY_PRESSED) अणु
			keycode = ADB_KEY_FWDEL;
			अगर (up_flag)
				ahid->flags &= ~FLAG_EMU_FWDEL_DOWN;
			अन्यथा
				ahid->flags |= FLAG_EMU_FWDEL_DOWN;
		पूर्ण
		अवरोध;
#पूर्ण_अगर /* CONFIG_PPC_PMAC */
	पूर्ण

	key = adbhid[id]->keycode[keycode];
	अगर (key) अणु
		input_report_key(adbhid[id]->input, key, !up_flag);
		input_sync(adbhid[id]->input);
	पूर्ण अन्यथा
		pr_info("Unhandled ADB key (scancode %#02x) %s.\n", keycode,
			up_flag ? "released" : "pressed");

पूर्ण

अटल व्योम
adbhid_mouse_input(अचिन्हित अक्षर *data, पूर्णांक nb, पूर्णांक स्वतःpoll)
अणु
	पूर्णांक id = (data[0] >> 4) & 0x0f;

	अगर (!adbhid[id]) अणु
		pr_err("ADB HID on ID %d not yet registered\n", id);
		वापस;
	पूर्ण

  /*
    Handler 1 -- 100cpi original Apple mouse protocol.
    Handler 2 -- 200cpi original Apple mouse protocol.

    For Apple's standard one-button mouse protocol the data array will
    contain the following values:

                BITS    COMMENTS
    data[0] = dddd 1100 ADB command: Talk, रेजिस्टर 0, क्रम device dddd.
    data[1] = bxxx xxxx First button and x-axis motion.
    data[2] = byyy yyyy Second button and y-axis motion.

    Handler 4 -- Apple Extended mouse protocol.

    For Apple's 3-button mouse protocol the data array will contain the
    following values:

		BITS    COMMENTS
    data[0] = dddd 1100 ADB command: Talk, रेजिस्टर 0, क्रम device dddd.
    data[1] = bxxx xxxx Left button and x-axis motion.
    data[2] = byyy yyyy Second button and y-axis motion.
    data[3] = byyy bxxx Third button and fourth button.  Y is additional
	      high bits of y-axis motion.  XY is additional
	      high bits of x-axis motion.

    MacAlly 2-button mouse protocol.

    For MacAlly 2-button mouse protocol the data array will contain the
    following values:

		BITS    COMMENTS
    data[0] = dddd 1100 ADB command: Talk, रेजिस्टर 0, क्रम device dddd.
    data[1] = bxxx xxxx Left button and x-axis motion.
    data[2] = byyy yyyy Right button and y-axis motion.
    data[3] = ???? ???? unknown
    data[4] = ???? ???? unknown

  */

	/* If it's a trackpad, we alias the second button to the first.
	   NOTE: Apple sends an ADB flush command to the trackpad when
	         the first (the real) button is released. We could करो
		 this here using async flush requests.
	*/
	चयन (adbhid[id]->mouse_kind)
	अणु
	    हाल ADBMOUSE_TRACKPAD:
		data[1] = (data[1] & 0x7f) | ((data[1] & data[2]) & 0x80);
		data[2] = data[2] | 0x80;
		अवरोध;
	    हाल ADBMOUSE_MICROSPEED:
		data[1] = (data[1] & 0x7f) | ((data[3] & 0x01) << 7);
		data[2] = (data[2] & 0x7f) | ((data[3] & 0x02) << 6);
		data[3] = (data[3] & 0x77) | ((data[3] & 0x04) << 5)
			| (data[3] & 0x08);
		अवरोध;
	    हाल ADBMOUSE_TRACKBALLPRO:
		data[1] = (data[1] & 0x7f) | (((data[3] & 0x04) << 5)
			& ((data[3] & 0x08) << 4));
		data[2] = (data[2] & 0x7f) | ((data[3] & 0x01) << 7);
		data[3] = (data[3] & 0x77) | ((data[3] & 0x02) << 6);
		अवरोध;
	    हाल ADBMOUSE_MS_A3:
		data[1] = (data[1] & 0x7f) | ((data[3] & 0x01) << 7);
		data[2] = (data[2] & 0x7f) | ((data[3] & 0x02) << 6);
		data[3] = ((data[3] & 0x04) << 5);
		अवरोध;
            हाल ADBMOUSE_MACALLY2:
		data[3] = (data[2] & 0x80) ? 0x80 : 0x00;
		data[2] |= 0x80;  /* Right button is mapped as button 3 */
		nb=4;
                अवरोध;
	पूर्ण

	input_report_key(adbhid[id]->input, BTN_LEFT,   !((data[1] >> 7) & 1));
	input_report_key(adbhid[id]->input, BTN_MIDDLE, !((data[2] >> 7) & 1));

	अगर (nb >= 4 && adbhid[id]->mouse_kind != ADBMOUSE_TRACKPAD)
		input_report_key(adbhid[id]->input, BTN_RIGHT,  !((data[3] >> 7) & 1));

	input_report_rel(adbhid[id]->input, REL_X,
			 ((data[2]&0x7f) < 64 ? (data[2]&0x7f) : (data[2]&0x7f)-128 ));
	input_report_rel(adbhid[id]->input, REL_Y,
			 ((data[1]&0x7f) < 64 ? (data[1]&0x7f) : (data[1]&0x7f)-128 ));

	input_sync(adbhid[id]->input);
पूर्ण

अटल व्योम
adbhid_buttons_input(अचिन्हित अक्षर *data, पूर्णांक nb, पूर्णांक स्वतःpoll)
अणु
	पूर्णांक id = (data[0] >> 4) & 0x0f;

	अगर (!adbhid[id]) अणु
		pr_err("ADB HID on ID %d not yet registered\n", id);
		वापस;
	पूर्ण

	चयन (adbhid[id]->original_handler_id) अणु
	शेष:
	हाल 0x02: /* Adjustable keyboard button device */
	  अणु
		पूर्णांक करोwn = (data[1] == (data[1] & 0xf));

		चयन (data[1] & 0x0f) अणु
		हाल 0x0:	/* microphone */
			input_report_key(adbhid[id]->input, KEY_SOUND, करोwn);
			अवरोध;

		हाल 0x1:	/* mute */
			input_report_key(adbhid[id]->input, KEY_MUTE, करोwn);
			अवरोध;

		हाल 0x2:	/* volume decrease */
			input_report_key(adbhid[id]->input, KEY_VOLUMEDOWN, करोwn);
			अवरोध;

		हाल 0x3:	/* volume increase */
			input_report_key(adbhid[id]->input, KEY_VOLUMEUP, करोwn);
			अवरोध;

		शेष:
			pr_info("Unhandled ADB_MISC event %02x, %02x, %02x, %02x\n",
				data[0], data[1], data[2], data[3]);
			अवरोध;
		पूर्ण
	  पूर्ण
	  अवरोध;

	हाल 0x1f: /* Powerbook button device */
	  अणु
		पूर्णांक करोwn = (data[1] == (data[1] & 0xf));

		/*
		 * XXX: Where is the contrast control क्रम the passive?
		 *  -- Cort
		 */

		चयन (data[1] & 0x0f) अणु
		हाल 0x8:	/* mute */
			input_report_key(adbhid[id]->input, KEY_MUTE, करोwn);
			अवरोध;

		हाल 0x7:	/* volume decrease */
			input_report_key(adbhid[id]->input, KEY_VOLUMEDOWN, करोwn);
			अवरोध;

		हाल 0x6:	/* volume increase */
			input_report_key(adbhid[id]->input, KEY_VOLUMEUP, करोwn);
			अवरोध;

		हाल 0xb:	/* eject */
			input_report_key(adbhid[id]->input, KEY_EJECTCD, करोwn);
			अवरोध;

		हाल 0xa:	/* brightness decrease */
#अगर_घोषित CONFIG_PMAC_BACKLIGHT
			अगर (करोwn)
				pmac_backlight_key_करोwn();
#पूर्ण_अगर
			input_report_key(adbhid[id]->input, KEY_BRIGHTNESSDOWN, करोwn);
			अवरोध;

		हाल 0x9:	/* brightness increase */
#अगर_घोषित CONFIG_PMAC_BACKLIGHT
			अगर (करोwn)
				pmac_backlight_key_up();
#पूर्ण_अगर
			input_report_key(adbhid[id]->input, KEY_BRIGHTNESSUP, करोwn);
			अवरोध;

		हाल 0xc:	/* videomode चयन */
			input_report_key(adbhid[id]->input, KEY_SWITCHVIDEOMODE, करोwn);
			अवरोध;

		हाल 0xd:	/* keyboard illumination toggle */
			input_report_key(adbhid[id]->input, KEY_KBDILLUMTOGGLE, करोwn);
			अवरोध;

		हाल 0xe:	/* keyboard illumination decrease */
			input_report_key(adbhid[id]->input, KEY_KBDILLUMDOWN, करोwn);
			अवरोध;

		हाल 0xf:
			चयन (data[1]) अणु
			हाल 0x8f:
			हाल 0x0f:
				/* keyboard illumination increase */
				input_report_key(adbhid[id]->input, KEY_KBDILLUMUP, करोwn);
				अवरोध;

			हाल 0x7f:
			हाल 0xff:
				/* keypad overlay toogle */
				अवरोध;

			शेष:
				pr_info("Unhandled ADB_MISC event %02x, %02x, %02x, %02x\n",
					data[0], data[1], data[2], data[3]);
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			pr_info("Unhandled ADB_MISC event %02x, %02x, %02x, %02x\n",
				data[0], data[1], data[2], data[3]);
			अवरोध;
		पूर्ण
	  पूर्ण
	  अवरोध;
	पूर्ण

	input_sync(adbhid[id]->input);
पूर्ण

अटल काष्ठा adb_request led_request;
अटल पूर्णांक leds_pending[16];
अटल पूर्णांक leds_req_pending;
अटल पूर्णांक pending_devs[16];
अटल पूर्णांक pending_led_start;
अटल पूर्णांक pending_led_end;
अटल DEFINE_SPINLOCK(leds_lock);

अटल व्योम leds_करोne(काष्ठा adb_request *req)
अणु
	पूर्णांक leds = 0, device = 0, pending = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&leds_lock, flags);

	अगर (pending_led_start != pending_led_end) अणु
		device = pending_devs[pending_led_start];
		leds = leds_pending[device] & 0xff;
		leds_pending[device] = 0;
		pending_led_start++;
		pending_led_start = (pending_led_start < 16) ? pending_led_start : 0;
		pending = leds_req_pending;
	पूर्ण अन्यथा
		leds_req_pending = 0;
	spin_unlock_irqrestore(&leds_lock, flags);
	अगर (pending)
		adb_request(&led_request, leds_करोne, 0, 3,
			    ADB_WRITEREG(device, KEYB_LEDREG), 0xff, ~leds);
पूर्ण

अटल व्योम real_leds(अचिन्हित अक्षर leds, पूर्णांक device)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&leds_lock, flags);
	अगर (!leds_req_pending) अणु
		leds_req_pending = 1;
		spin_unlock_irqrestore(&leds_lock, flags);	       
		adb_request(&led_request, leds_करोne, 0, 3,
			    ADB_WRITEREG(device, KEYB_LEDREG), 0xff, ~leds);
		वापस;
	पूर्ण अन्यथा अणु
		अगर (!(leds_pending[device] & 0x100)) अणु
			pending_devs[pending_led_end] = device;
			pending_led_end++;
			pending_led_end = (pending_led_end < 16) ? pending_led_end : 0;
		पूर्ण
		leds_pending[device] = leds | 0x100;
	पूर्ण
	spin_unlock_irqrestore(&leds_lock, flags);	       
पूर्ण

/*
 * Event callback from the input module. Events that change the state of
 * the hardware are processed here.
 */
अटल पूर्णांक adbhid_kbd_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा adbhid *adbhid = input_get_drvdata(dev);
	अचिन्हित अक्षर leds;

	चयन (type) अणु
	हाल EV_LED:
		leds =  (test_bit(LED_SCROLLL, dev->led) ? 4 : 0) |
			(test_bit(LED_NUML,    dev->led) ? 1 : 0) |
			(test_bit(LED_CAPSL,   dev->led) ? 2 : 0);
		real_leds(leds, adbhid->id);
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम
adbhid_kbd_capslock_remember(व्योम)
अणु
	काष्ठा adbhid *ahid;
	पूर्णांक i;

	क्रम (i = 1; i < 16; i++) अणु
		ahid = adbhid[i];

		अगर (ahid && ahid->id == ADB_KEYBOARD)
			अगर (ahid->flags & FLAG_CAPSLOCK_TRANSLATE)
				ahid->flags |= FLAG_CAPSLOCK_IGNORE_NEXT;
	पूर्ण
पूर्ण

अटल पूर्णांक
adb_message_handler(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code, व्योम *x)
अणु
	चयन (code) अणु
	हाल ADB_MSG_PRE_RESET:
	हाल ADB_MSG_POWERDOWN:
		/* Stop the repeat समयr. Autopoll is alपढ़ोy off at this poपूर्णांक */
		अणु
			पूर्णांक i;
			क्रम (i = 1; i < 16; i++) अणु
				अगर (adbhid[i])
					del_समयr_sync(&adbhid[i]->input->समयr);
			पूर्ण
		पूर्ण

		/* Stop pending led requests */
		जबतक (leds_req_pending)
			adb_poll();

		/* After resume, and अगर the capslock LED is on, the PMU will
		 * send a "capslock down" key event. This confuses the
		 * restore_capslock_events logic. Remember अगर the capslock
		 * LED was on beक्रमe suspend so the unwanted key event can
		 * be ignored after resume. */
		अगर (restore_capslock_events)
			adbhid_kbd_capslock_remember();

		अवरोध;

	हाल ADB_MSG_POST_RESET:
		adbhid_probe();
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक
adbhid_input_रेजिस्टर(पूर्णांक id, पूर्णांक शेष_id, पूर्णांक original_handler_id,
		      पूर्णांक current_handler_id, पूर्णांक mouse_kind)
अणु
	काष्ठा adbhid *hid;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;
	पूर्णांक i;
	अक्षर *keyboard_type;

	अगर (adbhid[id]) अणु
		pr_err("Trying to reregister ADB HID on ID %d\n", id);
		वापस -EEXIST;
	पूर्ण

	adbhid[id] = hid = kzalloc(माप(काष्ठा adbhid), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!hid || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	प्र_लिखो(hid->phys, "adb%d:%d.%02x/input", id, शेष_id, original_handler_id);

	hid->input = input_dev;
	hid->id = शेष_id;
	hid->original_handler_id = original_handler_id;
	hid->current_handler_id = current_handler_id;
	hid->mouse_kind = mouse_kind;
	hid->flags = 0;
	input_set_drvdata(input_dev, hid);
	input_dev->name = hid->name;
	input_dev->phys = hid->phys;
	input_dev->id.bustype = BUS_ADB;
	input_dev->id.venकरोr = 0x0001;
	input_dev->id.product = (id << 12) | (शेष_id << 8) | original_handler_id;
	input_dev->id.version = 0x0100;

	चयन (शेष_id) अणु
	हाल ADB_KEYBOARD:
		hid->keycode = kदो_स्मृति(माप(adb_to_linux_keycodes), GFP_KERNEL);
		अगर (!hid->keycode) अणु
			err = -ENOMEM;
			जाओ fail;
		पूर्ण

		प्र_लिखो(hid->name, "ADB keyboard");

		स_नकल(hid->keycode, adb_to_linux_keycodes, माप(adb_to_linux_keycodes));

		चयन (original_handler_id) अणु
		शेष:
			keyboard_type = "<unknown>";
			input_dev->id.version = ADB_KEYBOARD_UNKNOWN;
			अवरोध;

		हाल 0x01: हाल 0x02: हाल 0x03: हाल 0x06: हाल 0x08:
		हाल 0x0C: हाल 0x10: हाल 0x18: हाल 0x1B: हाल 0x1C:
		हाल 0xC0: हाल 0xC3: हाल 0xC6:
			keyboard_type = "ANSI";
			input_dev->id.version = ADB_KEYBOARD_ANSI;
			अवरोध;

		हाल 0x04: हाल 0x05: हाल 0x07: हाल 0x09: हाल 0x0D:
		हाल 0x11: हाल 0x14: हाल 0x19: हाल 0x1D: हाल 0xC1:
		हाल 0xC4: हाल 0xC7:
			keyboard_type = "ISO, swapping keys";
			input_dev->id.version = ADB_KEYBOARD_ISO;
			i = hid->keycode[10];
			hid->keycode[10] = hid->keycode[50];
			hid->keycode[50] = i;
			अवरोध;

		हाल 0x12: हाल 0x15: हाल 0x16: हाल 0x17: हाल 0x1A:
		हाल 0x1E: हाल 0xC2: हाल 0xC5: हाल 0xC8: हाल 0xC9:
			keyboard_type = "JIS";
			input_dev->id.version = ADB_KEYBOARD_JIS;
			अवरोध;
		पूर्ण
		pr_info("Detected ADB keyboard, type %s.\n", keyboard_type);

		क्रम (i = 0; i < 128; i++)
			अगर (hid->keycode[i])
				set_bit(hid->keycode[i], input_dev->keybit);

		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_LED) |
			BIT_MASK(EV_REP);
		input_dev->ledbit[0] = BIT_MASK(LED_SCROLLL) |
			BIT_MASK(LED_CAPSL) | BIT_MASK(LED_NUML);
		input_dev->event = adbhid_kbd_event;
		input_dev->keycodemax = KEY_FN;
		input_dev->keycodesize = माप(hid->keycode[0]);
		अवरोध;

	हाल ADB_MOUSE:
		प्र_लिखो(hid->name, "ADB mouse");

		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);
		input_dev->keybit[BIT_WORD(BTN_MOUSE)] = BIT_MASK(BTN_LEFT) |
			BIT_MASK(BTN_MIDDLE) | BIT_MASK(BTN_RIGHT);
		input_dev->relbit[0] = BIT_MASK(REL_X) | BIT_MASK(REL_Y);
		अवरोध;

	हाल ADB_MISC:
		चयन (original_handler_id) अणु
		हाल 0x02: /* Adjustable keyboard button device */
			प्र_लिखो(hid->name, "ADB adjustable keyboard buttons");
			input_dev->evbit[0] = BIT_MASK(EV_KEY) |
				BIT_MASK(EV_REP);
			set_bit(KEY_SOUND, input_dev->keybit);
			set_bit(KEY_MUTE, input_dev->keybit);
			set_bit(KEY_VOLUMEUP, input_dev->keybit);
			set_bit(KEY_VOLUMEDOWN, input_dev->keybit);
			अवरोध;
		हाल 0x1f: /* Powerbook button device */
			प्र_लिखो(hid->name, "ADB Powerbook buttons");
			input_dev->evbit[0] = BIT_MASK(EV_KEY) |
				BIT_MASK(EV_REP);
			set_bit(KEY_MUTE, input_dev->keybit);
			set_bit(KEY_VOLUMEUP, input_dev->keybit);
			set_bit(KEY_VOLUMEDOWN, input_dev->keybit);
			set_bit(KEY_BRIGHTNESSUP, input_dev->keybit);
			set_bit(KEY_BRIGHTNESSDOWN, input_dev->keybit);
			set_bit(KEY_EJECTCD, input_dev->keybit);
			set_bit(KEY_SWITCHVIDEOMODE, input_dev->keybit);
			set_bit(KEY_KBDILLUMTOGGLE, input_dev->keybit);
			set_bit(KEY_KBDILLUMDOWN, input_dev->keybit);
			set_bit(KEY_KBDILLUMUP, input_dev->keybit);
			अवरोध;
		पूर्ण
		अगर (hid->name[0])
			अवरोध;
		fallthrough;

	शेष:
		pr_info("Trying to register unknown ADB device to input layer.\n");
		err = -ENODEV;
		जाओ fail;
	पूर्ण

	input_dev->keycode = hid->keycode;

	err = input_रेजिस्टर_device(input_dev);
	अगर (err)
		जाओ fail;

	अगर (शेष_id == ADB_KEYBOARD) अणु
		/* HACK WARNING!! This should go away as soon there is an utility
		 * to control that क्रम event devices.
		 */
		input_dev->rep[REP_DELAY] = 500;   /* input layer शेष: 250 */
		input_dev->rep[REP_PERIOD] = 66; /* input layer शेष: 33 */
	पूर्ण

	वापस 0;

 fail:	input_मुक्त_device(input_dev);
	अगर (hid) अणु
		kमुक्त(hid->keycode);
		kमुक्त(hid);
	पूर्ण
	adbhid[id] = शून्य;
	वापस err;
पूर्ण

अटल व्योम adbhid_input_unरेजिस्टर(पूर्णांक id)
अणु
	input_unरेजिस्टर_device(adbhid[id]->input);
	kमुक्त(adbhid[id]->keycode);
	kमुक्त(adbhid[id]);
	adbhid[id] = शून्य;
पूर्ण


अटल u16
adbhid_input_reरेजिस्टर(पूर्णांक id, पूर्णांक शेष_id, पूर्णांक org_handler_id,
			पूर्णांक cur_handler_id, पूर्णांक mk)
अणु
	अगर (adbhid[id]) अणु
		अगर (adbhid[id]->input->id.product !=
		    ((id << 12)|(शेष_id << 8)|org_handler_id)) अणु
			adbhid_input_unरेजिस्टर(id);
			adbhid_input_रेजिस्टर(id, शेष_id, org_handler_id,
					      cur_handler_id, mk);
		पूर्ण
	पूर्ण अन्यथा
		adbhid_input_रेजिस्टर(id, शेष_id, org_handler_id,
				      cur_handler_id, mk);
	वापस 1<<id;
पूर्ण

अटल व्योम
adbhid_input_devcleanup(u16 exist)
अणु
	पूर्णांक i;
	क्रम(i=1; i<16; i++)
		अगर (adbhid[i] && !(exist&(1<<i)))
			adbhid_input_unरेजिस्टर(i);
पूर्ण

अटल व्योम
adbhid_probe(व्योम)
अणु
	काष्ठा adb_request req;
	पूर्णांक i, शेष_id, org_handler_id, cur_handler_id;
	u16 reg = 0;

	adb_रेजिस्टर(ADB_MOUSE, 0, &mouse_ids, adbhid_mouse_input);
	adb_रेजिस्टर(ADB_KEYBOARD, 0, &keyboard_ids, adbhid_keyboard_input);
	adb_रेजिस्टर(ADB_MISC, 0, &buttons_ids, adbhid_buttons_input);

	क्रम (i = 0; i < keyboard_ids.nids; i++) अणु
		पूर्णांक id = keyboard_ids.id[i];

		adb_get_infos(id, &शेष_id, &org_handler_id);

		/* turn off all leds */
		adb_request(&req, शून्य, ADBREQ_SYNC, 3,
			    ADB_WRITEREG(id, KEYB_LEDREG), 0xff, 0xff);

		/* Enable full feature set of the keyboard
		   ->get it to send separate codes क्रम left and right shअगरt,
		   control, option keys */
#अगर 0		/* handler 5 करोesn't send separate codes क्रम R modअगरiers */
		अगर (!adb_try_handler_change(id, 5))
#पूर्ण_अगर
		adb_try_handler_change(id, 3);

		adb_get_infos(id, &शेष_id, &cur_handler_id);
		prपूर्णांकk(KERN_DEBUG "ADB keyboard at %d has handler 0x%X\n",
		       id, cur_handler_id);
		reg |= adbhid_input_reरेजिस्टर(id, शेष_id, org_handler_id,
					       cur_handler_id, 0);
	पूर्ण

	क्रम (i = 0; i < buttons_ids.nids; i++) अणु
		पूर्णांक id = buttons_ids.id[i];

		adb_get_infos(id, &शेष_id, &org_handler_id);
		reg |= adbhid_input_reरेजिस्टर(id, शेष_id, org_handler_id,
					       org_handler_id, 0);
	पूर्ण

	/* Try to चयन all mice to handler 4, or 2 क्रम three-button
	   mode and full resolution. */
	क्रम (i = 0; i < mouse_ids.nids; i++) अणु
		पूर्णांक id = mouse_ids.id[i];
		पूर्णांक mouse_kind;
		अक्षर *desc = "standard";

		adb_get_infos(id, &शेष_id, &org_handler_id);

		अगर (adb_try_handler_change(id, 4)) अणु
			mouse_kind = ADBMOUSE_EXTENDED;
		पूर्ण
		अन्यथा अगर (adb_try_handler_change(id, 0x2F)) अणु
			mouse_kind = ADBMOUSE_MICROSPEED;
		पूर्ण
		अन्यथा अगर (adb_try_handler_change(id, 0x42)) अणु
			mouse_kind = ADBMOUSE_TRACKBALLPRO;
		पूर्ण
		अन्यथा अगर (adb_try_handler_change(id, 0x66)) अणु
			mouse_kind = ADBMOUSE_MICROSPEED;
		पूर्ण
		अन्यथा अगर (adb_try_handler_change(id, 0x5F)) अणु
			mouse_kind = ADBMOUSE_MICROSPEED;
		पूर्ण
		अन्यथा अगर (adb_try_handler_change(id, 3)) अणु
			mouse_kind = ADBMOUSE_MS_A3;
		पूर्ण
		अन्यथा अगर (adb_try_handler_change(id, 2)) अणु
			mouse_kind = ADBMOUSE_STANDARD_200;
		पूर्ण
		अन्यथा अणु
			mouse_kind = ADBMOUSE_STANDARD_100;
		पूर्ण

		अगर ((mouse_kind == ADBMOUSE_TRACKBALLPRO)
		    || (mouse_kind == ADBMOUSE_MICROSPEED)) अणु
			desc = "Microspeed/MacPoint or compatible";
			init_microspeed(id);
		पूर्ण अन्यथा अगर (mouse_kind == ADBMOUSE_MS_A3) अणु
			desc = "Mouse Systems A3 Mouse or compatible";
			init_ms_a3(id);
		पूर्ण अन्यथा अगर (mouse_kind ==  ADBMOUSE_EXTENDED) अणु
			desc = "extended";
			/*
			 * Register 1 is usually used क्रम device
			 * identअगरication.  Here, we try to identअगरy
			 * a known device and call the appropriate
			 * init function.
			 */
			adb_request(&req, शून्य, ADBREQ_SYNC | ADBREQ_REPLY, 1,
				    ADB_READREG(id, 1));

			अगर ((req.reply_len) &&
			    (req.reply[1] == 0x9a) && ((req.reply[2] == 0x21)
			    	|| (req.reply[2] == 0x20))) अणु
				mouse_kind = ADBMOUSE_TRACKBALL;
				desc = "trackman/mouseman";
				init_trackball(id);
			पूर्ण
			अन्यथा अगर ((req.reply_len >= 4) &&
			    (req.reply[1] == 0x74) && (req.reply[2] == 0x70) &&
			    (req.reply[3] == 0x61) && (req.reply[4] == 0x64)) अणु
				mouse_kind = ADBMOUSE_TRACKPAD;
				desc = "trackpad";
				init_trackpad(id);
			पूर्ण
			अन्यथा अगर ((req.reply_len >= 4) &&
			    (req.reply[1] == 0x4b) && (req.reply[2] == 0x4d) &&
			    (req.reply[3] == 0x4c) && (req.reply[4] == 0x31)) अणु
				mouse_kind = ADBMOUSE_TURBOMOUSE5;
				desc = "TurboMouse 5";
				init_turbomouse(id);
			पूर्ण
			अन्यथा अगर ((req.reply_len == 9) &&
			    (req.reply[1] == 0x4b) && (req.reply[2] == 0x4f) &&
			    (req.reply[3] == 0x49) && (req.reply[4] == 0x54)) अणु
				अगर (adb_try_handler_change(id, 0x42)) अणु
					mouse_kind = ADBMOUSE_MACALLY2;
					desc = "MacAlly 2-button";
				पूर्ण
			पूर्ण
		पूर्ण

		adb_get_infos(id, &शेष_id, &cur_handler_id);
		prपूर्णांकk(KERN_DEBUG "ADB mouse (%s) at %d has handler 0x%X\n",
		       desc, id, cur_handler_id);
		reg |= adbhid_input_reरेजिस्टर(id, शेष_id, org_handler_id,
					       cur_handler_id, mouse_kind);
	पूर्ण
	adbhid_input_devcleanup(reg);
पूर्ण

अटल व्योम 
init_trackpad(पूर्णांक id)
अणु
	काष्ठा adb_request req;
	अचिन्हित अक्षर r1_buffer[8];

	adb_request(&req, शून्य, ADBREQ_SYNC | ADBREQ_REPLY, 1,
		    ADB_READREG(id,1));
	अगर (req.reply_len < 8)
		pr_err("%s: bad length for reg. 1\n", __func__);
	अन्यथा
	अणु
	    स_नकल(r1_buffer, &req.reply[1], 8);

	    adb_request(&req, शून्य, ADBREQ_SYNC, 9,
	        ADB_WRITEREG(id,1),
	            r1_buffer[0],
	            r1_buffer[1],
	            r1_buffer[2],
	            r1_buffer[3],
	            r1_buffer[4],
	            r1_buffer[5],
	            0x0d,
	            r1_buffer[7]);

            adb_request(&req, शून्य, ADBREQ_SYNC, 9,
	        ADB_WRITEREG(id,2),
	    	    0x99,
	    	    0x94,
	    	    0x19,
	    	    0xff,
	    	    0xb2,
	    	    0x8a,
	    	    0x1b,
	    	    0x50);

	    adb_request(&req, शून्य, ADBREQ_SYNC, 9,
	        ADB_WRITEREG(id,1),
	            r1_buffer[0],
	            r1_buffer[1],
	            r1_buffer[2],
	            r1_buffer[3],
	            r1_buffer[4],
	            r1_buffer[5],
	            0x03, /*r1_buffer[6],*/
	            r1_buffer[7]);

	    /* Without this flush, the trackpad may be locked up */
	    adb_request(&req, शून्य, ADBREQ_SYNC, 1, ADB_FLUSH(id));
        पूर्ण
पूर्ण

अटल व्योम 
init_trackball(पूर्णांक id)
अणु
	काष्ठा adb_request req;

	adb_request(&req, शून्य, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id,1), 00,0x81);

	adb_request(&req, शून्य, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id,1), 01,0x81);

	adb_request(&req, शून्य, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id,1), 02,0x81);

	adb_request(&req, शून्य, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id,1), 03,0x38);

	adb_request(&req, शून्य, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id,1), 00,0x81);

	adb_request(&req, शून्य, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id,1), 01,0x81);

	adb_request(&req, शून्य, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id,1), 02,0x81);

	adb_request(&req, शून्य, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id,1), 03,0x38);
पूर्ण

अटल व्योम
init_turbomouse(पूर्णांक id)
अणु
	काष्ठा adb_request req;

	adb_request(&req, शून्य, ADBREQ_SYNC, 1, ADB_FLUSH(id));

	adb_request(&req, शून्य, ADBREQ_SYNC, 1, ADB_FLUSH(3));

	adb_request(&req, शून्य, ADBREQ_SYNC, 9,
	ADB_WRITEREG(3,2),
	    0xe7,
	    0x8c,
	    0,
	    0,
	    0,
	    0xff,
	    0xff,
	    0x94);

	adb_request(&req, शून्य, ADBREQ_SYNC, 1, ADB_FLUSH(3));

	adb_request(&req, शून्य, ADBREQ_SYNC, 9,
	ADB_WRITEREG(3,2),
	    0xa5,
	    0x14,
	    0,
	    0,
	    0x69,
	    0xff,
	    0xff,
	    0x27);
पूर्ण

अटल व्योम
init_microspeed(पूर्णांक id)
अणु
	काष्ठा adb_request req;

	adb_request(&req, शून्य, ADBREQ_SYNC, 1, ADB_FLUSH(id));

	/* This will initialize mice using the Microspeed, MacPoपूर्णांक and
	   other compatible firmware. Bit 12 enables extended protocol.
	   
	   Register 1 Listen (4 Bytes)
            0 -  3     Button is mouse (set also क्रम द्विगुन clicking!!!)
            4 -  7     Button is locking (affects change speed also)
            8 - 11     Button changes speed
           12          1 = Extended mouse mode, 0 = normal mouse mode
           13 - 15     unused 0
           16 - 23     normal speed
           24 - 31     changed speed

       Register 1 talk holds version and product identअगरication inक्रमmation.
       Register 1 Talk (4 Bytes):
            0 -  7     Product code
            8 - 23     undefined, reserved
           24 - 31     Version number
        
       Speed 0 is max. 1 to 255 set speed in increments of 1/256 of max.
 */
	adb_request(&req, शून्य, ADBREQ_SYNC, 5,
	ADB_WRITEREG(id,1),
	    0x20,	/* alt speed = 0x20 (rather slow) */
	    0x00,	/* norm speed = 0x00 (fastest) */
	    0x10,	/* extended protocol, no speed change */
	    0x07);	/* all buttons enabled as mouse buttons, no locking */


	adb_request(&req, शून्य, ADBREQ_SYNC, 1, ADB_FLUSH(id));
पूर्ण

अटल व्योम
init_ms_a3(पूर्णांक id)
अणु
	काष्ठा adb_request req;

	adb_request(&req, शून्य, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id, 0x2),
	    0x00,
	    0x07);
 
 	adb_request(&req, शून्य, ADBREQ_SYNC, 1, ADB_FLUSH(id));
पूर्ण

अटल पूर्णांक __init adbhid_init(व्योम)
अणु
#अगर_अघोषित CONFIG_MAC
	अगर (!machine_is(chrp) && !machine_is(घातermac))
		वापस 0;
#पूर्ण_अगर

	led_request.complete = 1;

	adbhid_probe();

	blocking_notअगरier_chain_रेजिस्टर(&adb_client_list,
			&adbhid_adb_notअगरier);

	वापस 0;
पूर्ण

अटल व्योम __निकास adbhid_निकास(व्योम)
अणु
पूर्ण
 
module_init(adbhid_init);
module_निकास(adbhid_निकास);
