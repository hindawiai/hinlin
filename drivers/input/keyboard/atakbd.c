<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  atakbd.c
 *
 *  Copyright (c) 2005 Michael Schmitz
 *
 * Based on amikbd.c, which is
 *
 *  Copyright (c) 2000-2001 Vojtech Pavlik
 *
 *  Based on the work of:
 *	Hamish Macकरोnald
 */

/*
 * Atari keyboard driver क्रम Linux/m68k
 *
 * The low level init and पूर्णांकerrupt stuff is handled in arch/mm68k/atari/atakeyb.c
 * (the keyboard ACIA also handles the mouse and joystick data, and the keyboard
 * पूर्णांकerrupt is shared with the MIDI ACIA so MIDI data also get handled there).
 * This driver only deals with handing key events off to the input layer.
 */

/*
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/atariपूर्णांकs.h>
#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/atarikb.h>
#समावेश <यंत्र/irq.h>

MODULE_AUTHOR("Michael Schmitz <schmitz@biophys.uni-duesseldorf.de>");
MODULE_DESCRIPTION("Atari keyboard driver");
MODULE_LICENSE("GPL");

/*
 0x47: KP_7     71
 0x48: KP_8     72
 0x49: KP_9     73
 0x62: KP_/     98
 0x4b: KP_4     75
 0x4c: KP_5     76
 0x4d: KP_6     77
 0x37: KP_*     55
 0x4f: KP_1     79
 0x50: KP_2     80
 0x51: KP_3     81
 0x4a: KP_-     74
 0x52: KP_0     82
 0x53: KP_.     83
 0x4e: KP_+     78

 0x67: Up       103
 0x6c: Down     108
 0x69: Left     105
 0x6a: Right    106
 */


अटल अचिन्हित अक्षर atakbd_keycode[0x73] = अणु	/* American layout */
	[1]	 = KEY_ESC,
	[2]	 = KEY_1,
	[3]	 = KEY_2,
	[4]	 = KEY_3,
	[5]	 = KEY_4,
	[6]	 = KEY_5,
	[7]	 = KEY_6,
	[8]	 = KEY_7,
	[9]	 = KEY_8,
	[10]	 = KEY_9,
	[11]	 = KEY_0,
	[12]	 = KEY_MINUS,
	[13]	 = KEY_EQUAL,
	[14]	 = KEY_BACKSPACE,
	[15]	 = KEY_TAB,
	[16]	 = KEY_Q,
	[17]	 = KEY_W,
	[18]	 = KEY_E,
	[19]	 = KEY_R,
	[20]	 = KEY_T,
	[21]	 = KEY_Y,
	[22]	 = KEY_U,
	[23]	 = KEY_I,
	[24]	 = KEY_O,
	[25]	 = KEY_P,
	[26]	 = KEY_LEFTBRACE,
	[27]	 = KEY_RIGHTBRACE,
	[28]	 = KEY_ENTER,
	[29]	 = KEY_LEFTCTRL,
	[30]	 = KEY_A,
	[31]	 = KEY_S,
	[32]	 = KEY_D,
	[33]	 = KEY_F,
	[34]	 = KEY_G,
	[35]	 = KEY_H,
	[36]	 = KEY_J,
	[37]	 = KEY_K,
	[38]	 = KEY_L,
	[39]	 = KEY_SEMICOLON,
	[40]	 = KEY_APOSTROPHE,
	[41]	 = KEY_GRAVE,
	[42]	 = KEY_LEFTSHIFT,
	[43]	 = KEY_BACKSLASH,
	[44]	 = KEY_Z,
	[45]	 = KEY_X,
	[46]	 = KEY_C,
	[47]	 = KEY_V,
	[48]	 = KEY_B,
	[49]	 = KEY_N,
	[50]	 = KEY_M,
	[51]	 = KEY_COMMA,
	[52]	 = KEY_DOT,
	[53]	 = KEY_SLASH,
	[54]	 = KEY_RIGHTSHIFT,
	[55]	 = KEY_KPASTERISK,
	[56]	 = KEY_LEFTALT,
	[57]	 = KEY_SPACE,
	[58]	 = KEY_CAPSLOCK,
	[59]	 = KEY_F1,
	[60]	 = KEY_F2,
	[61]	 = KEY_F3,
	[62]	 = KEY_F4,
	[63]	 = KEY_F5,
	[64]	 = KEY_F6,
	[65]	 = KEY_F7,
	[66]	 = KEY_F8,
	[67]	 = KEY_F9,
	[68]	 = KEY_F10,
	[71]	 = KEY_HOME,
	[72]	 = KEY_UP,
	[74]	 = KEY_KPMINUS,
	[75]	 = KEY_LEFT,
	[77]	 = KEY_RIGHT,
	[78]	 = KEY_KPPLUS,
	[80]	 = KEY_DOWN,
	[82]	 = KEY_INSERT,
	[83]	 = KEY_DELETE,
	[96]	 = KEY_102ND,
	[97]	 = KEY_UNDO,
	[98]	 = KEY_HELP,
	[99]	 = KEY_KPLEFTPAREN,
	[100]	 = KEY_KPRIGHTPAREN,
	[101]	 = KEY_KPSLASH,
	[102]	 = KEY_KPASTERISK,
	[103]	 = KEY_KP7,
	[104]	 = KEY_KP8,
	[105]	 = KEY_KP9,
	[106]	 = KEY_KP4,
	[107]	 = KEY_KP5,
	[108]	 = KEY_KP6,
	[109]	 = KEY_KP1,
	[110]	 = KEY_KP2,
	[111]	 = KEY_KP3,
	[112]	 = KEY_KP0,
	[113]	 = KEY_KPDOT,
	[114]	 = KEY_KPENTER,
पूर्ण;

अटल काष्ठा input_dev *atakbd_dev;

अटल व्योम atakbd_पूर्णांकerrupt(अचिन्हित अक्षर scancode, अक्षर करोwn)
अणु

	अगर (scancode < 0x73) अणु		/* scancodes < 0xf3 are keys */

		// report raw events here?

		scancode = atakbd_keycode[scancode];

		input_report_key(atakbd_dev, scancode, करोwn);
		input_sync(atakbd_dev);
	पूर्ण अन्यथा				/* scancodes >= 0xf3 are mouse data, most likely */
		prपूर्णांकk(KERN_INFO "atakbd: unhandled scancode %x\n", scancode);

	वापस;
पूर्ण

अटल पूर्णांक __init atakbd_init(व्योम)
अणु
	पूर्णांक i, error;

	अगर (!MACH_IS_ATARI || !ATARIHW_PRESENT(ST_MFP))
		वापस -ENODEV;

	// need to init core driver अगर not alपढ़ोy करोne so
	error = atari_keyb_init();
	अगर (error)
		वापस error;

	atakbd_dev = input_allocate_device();
	अगर (!atakbd_dev)
		वापस -ENOMEM;

	atakbd_dev->name = "Atari Keyboard";
	atakbd_dev->phys = "atakbd/input0";
	atakbd_dev->id.bustype = BUS_HOST;
	atakbd_dev->id.venकरोr = 0x0001;
	atakbd_dev->id.product = 0x0001;
	atakbd_dev->id.version = 0x0100;

	atakbd_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	atakbd_dev->keycode = atakbd_keycode;
	atakbd_dev->keycodesize = माप(अचिन्हित अक्षर);
	atakbd_dev->keycodemax = ARRAY_SIZE(atakbd_keycode);

	क्रम (i = 1; i < 0x72; i++) अणु
		set_bit(atakbd_keycode[i], atakbd_dev->keybit);
	पूर्ण

	/* error check */
	error = input_रेजिस्टर_device(atakbd_dev);
	अगर (error) अणु
		input_मुक्त_device(atakbd_dev);
		वापस error;
	पूर्ण

	atari_input_keyboard_पूर्णांकerrupt_hook = atakbd_पूर्णांकerrupt;

	वापस 0;
पूर्ण

अटल व्योम __निकास atakbd_निकास(व्योम)
अणु
	atari_input_keyboard_पूर्णांकerrupt_hook = शून्य;
	input_unरेजिस्टर_device(atakbd_dev);
पूर्ण

module_init(atakbd_init);
module_निकास(atakbd_निकास);
