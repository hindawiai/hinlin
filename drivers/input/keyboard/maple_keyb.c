<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SEGA Dreamcast keyboard driver
 * Based on drivers/usb/usbkbd.c
 * Copyright (c) YAEGASHI Takeshi, 2001
 * Porting to 2.6 Copyright (c) Adrian McMenamin, 2007 - 2009
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/समयr.h>
#समावेश <linux/maple.h>

/* Very simple mutex to ensure proper cleanup */
अटल DEFINE_MUTEX(maple_keyb_mutex);

#घोषणा NR_SCANCODES 256

MODULE_AUTHOR("Adrian McMenamin <adrian@mcmen.demon.co.uk");
MODULE_DESCRIPTION("SEGA Dreamcast keyboard driver");
MODULE_LICENSE("GPL");

काष्ठा dc_kbd अणु
	काष्ठा input_dev *dev;
	अचिन्हित लघु keycode[NR_SCANCODES];
	अचिन्हित अक्षर new[8];
	अचिन्हित अक्षर old[8];
पूर्ण;

अटल स्थिर अचिन्हित लघु dc_kbd_keycode[NR_SCANCODES] = अणु
	KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_A, KEY_B,
	KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L,
	KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V,
	KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6,
	KEY_7, KEY_8, KEY_9, KEY_0, KEY_ENTER, KEY_ESC, KEY_BACKSPACE,
	KEY_TAB, KEY_SPACE, KEY_MINUS, KEY_EQUAL, KEY_LEFTBRACE,
	KEY_RIGHTBRACE, KEY_BACKSLASH, KEY_BACKSLASH, KEY_SEMICOLON,
	KEY_APOSTROPHE, KEY_GRAVE, KEY_COMMA, KEY_DOT, KEY_SLASH,
	KEY_CAPSLOCK, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6,
	KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_SYSRQ,
	KEY_SCROLLLOCK, KEY_PAUSE, KEY_INSERT, KEY_HOME, KEY_PAGEUP,
	KEY_DELETE, KEY_END, KEY_PAGEDOWN, KEY_RIGHT, KEY_LEFT, KEY_DOWN,
	KEY_UP, KEY_NUMLOCK, KEY_KPSLASH, KEY_KPASTERISK, KEY_KPMINUS,
	KEY_KPPLUS, KEY_KPENTER, KEY_KP1, KEY_KP2, KEY_KP3, KEY_KP4, KEY_KP5,
	KEY_KP6, KEY_KP7, KEY_KP8, KEY_KP9, KEY_KP0, KEY_KPDOT, KEY_102ND,
	KEY_COMPOSE, KEY_POWER, KEY_KPEQUAL, KEY_F13, KEY_F14, KEY_F15,
	KEY_F16, KEY_F17, KEY_F18, KEY_F19, KEY_F20, KEY_F21, KEY_F22,
	KEY_F23, KEY_F24, KEY_OPEN, KEY_HELP, KEY_PROPS, KEY_FRONT, KEY_STOP,
	KEY_AGAIN, KEY_UNDO, KEY_CUT, KEY_COPY, KEY_PASTE, KEY_FIND, KEY_MUTE,
	KEY_VOLUMEUP, KEY_VOLUMEDOWN, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED,
	KEY_KPCOMMA, KEY_RESERVED, KEY_RO, KEY_KATAKANAHIRAGANA , KEY_YEN,
	KEY_HENKAN, KEY_MUHENKAN, KEY_KPJPCOMMA, KEY_RESERVED, KEY_RESERVED,
	KEY_RESERVED, KEY_HANGEUL, KEY_HANJA, KEY_KATAKANA, KEY_HIRAGANA,
	KEY_ZENKAKUHANKAKU, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED,
	KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED,
	KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED,
	KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED,
	KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED,
	KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED,
	KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED,
	KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED,
	KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED,
	KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED,
	KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED,
	KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED,
	KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED,
	KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED,
	KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED,
	KEY_RESERVED, KEY_RESERVED, KEY_LEFTCTRL, KEY_LEFTSHIFT, KEY_LEFTALT,
	KEY_LEFTMETA, KEY_RIGHTCTRL, KEY_RIGHTSHIFT, KEY_RIGHTALT,
	KEY_RIGHTMETA, KEY_PLAYPAUSE, KEY_STOPCD, KEY_PREVIOUSSONG,
	KEY_NEXTSONG, KEY_EJECTCD, KEY_VOLUMEUP, KEY_VOLUMEDOWN, KEY_MUTE,
	KEY_WWW, KEY_BACK, KEY_FORWARD, KEY_STOP, KEY_FIND, KEY_SCROLLUP,
	KEY_SCROLLDOWN, KEY_EDIT, KEY_SLEEP, KEY_SCREENLOCK, KEY_REFRESH,
	KEY_CALC, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED
पूर्ण;

अटल व्योम dc_scan_kbd(काष्ठा dc_kbd *kbd)
अणु
	काष्ठा input_dev *dev = kbd->dev;
	व्योम *ptr;
	पूर्णांक code, keycode;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		code = i + 224;
		keycode = kbd->keycode[code];
		input_event(dev, EV_MSC, MSC_SCAN, code);
		input_report_key(dev, keycode, (kbd->new[0] >> i) & 1);
	पूर्ण

	क्रम (i = 2; i < 8; i++) अणु
		ptr = स_प्रथम(kbd->new + 2, kbd->old[i], 6);
		code = kbd->old[i];
		अगर (code > 3 && ptr == शून्य) अणु
			keycode = kbd->keycode[code];
			अगर (keycode) अणु
				input_event(dev, EV_MSC, MSC_SCAN, code);
				input_report_key(dev, keycode, 0);
			पूर्ण अन्यथा
				dev_dbg(&dev->dev,
					"Unknown key (scancode %#x) released.",
					code);
		पूर्ण
		ptr = स_प्रथम(kbd->old + 2, kbd->new[i], 6);
		code = kbd->new[i];
		अगर (code > 3 && ptr) अणु
			keycode = kbd->keycode[code];
			अगर (keycode) अणु
				input_event(dev, EV_MSC, MSC_SCAN, code);
				input_report_key(dev, keycode, 1);
			पूर्ण अन्यथा
				dev_dbg(&dev->dev,
					"Unknown key (scancode %#x) pressed.",
					code);
		पूर्ण
	पूर्ण
	input_sync(dev);
	स_नकल(kbd->old, kbd->new, 8);
पूर्ण

अटल व्योम dc_kbd_callback(काष्ठा mapleq *mq)
अणु
	काष्ठा maple_device *mapledev = mq->dev;
	काष्ठा dc_kbd *kbd = maple_get_drvdata(mapledev);
	अचिन्हित दीर्घ *buf = (अचिन्हित दीर्घ *)(mq->recvbuf->buf);

	/*
	 * We should always get the lock because the only
	 * समय it may be locked is अगर the driver is in the cleanup phase.
	 */
	अगर (likely(mutex_trylock(&maple_keyb_mutex))) अणु

		अगर (buf[1] == mapledev->function) अणु
			स_नकल(kbd->new, buf + 2, 8);
			dc_scan_kbd(kbd);
		पूर्ण

		mutex_unlock(&maple_keyb_mutex);
	पूर्ण
पूर्ण

अटल पूर्णांक probe_maple_kbd(काष्ठा device *dev)
अणु
	काष्ठा maple_device *mdev;
	काष्ठा maple_driver *mdrv;
	पूर्णांक i, error;
	काष्ठा dc_kbd *kbd;
	काष्ठा input_dev *idev;

	mdev = to_maple_dev(dev);
	mdrv = to_maple_driver(dev->driver);

	kbd = kzalloc(माप(काष्ठा dc_kbd), GFP_KERNEL);
	अगर (!kbd) अणु
		error = -ENOMEM;
		जाओ fail;
	पूर्ण

	idev = input_allocate_device();
	अगर (!idev) अणु
		error = -ENOMEM;
		जाओ fail_idev_alloc;
	पूर्ण

	kbd->dev = idev;
	स_नकल(kbd->keycode, dc_kbd_keycode, माप(kbd->keycode));

	idev->name = mdev->product_name;
	idev->evbit[0] = BIT(EV_KEY) | BIT(EV_REP);
	idev->keycode = kbd->keycode;
	idev->keycodesize = माप(अचिन्हित लघु);
	idev->keycodemax = ARRAY_SIZE(kbd->keycode);
	idev->id.bustype = BUS_HOST;
	idev->dev.parent = &mdev->dev;

	क्रम (i = 0; i < NR_SCANCODES; i++)
		__set_bit(dc_kbd_keycode[i], idev->keybit);
	__clear_bit(KEY_RESERVED, idev->keybit);

	input_set_capability(idev, EV_MSC, MSC_SCAN);

	error = input_रेजिस्टर_device(idev);
	अगर (error)
		जाओ fail_रेजिस्टर;

	/* Maple polling is locked to VBLANK - which may be just 50/s */
	maple_अ_लोond_callback(mdev, dc_kbd_callback, HZ/50,
		MAPLE_FUNC_KEYBOARD);

	mdev->driver = mdrv;

	maple_set_drvdata(mdev, kbd);

	वापस error;

fail_रेजिस्टर:
	maple_set_drvdata(mdev, शून्य);
	input_मुक्त_device(idev);
fail_idev_alloc:
	kमुक्त(kbd);
fail:
	वापस error;
पूर्ण

अटल पूर्णांक हटाओ_maple_kbd(काष्ठा device *dev)
अणु
	काष्ठा maple_device *mdev = to_maple_dev(dev);
	काष्ठा dc_kbd *kbd = maple_get_drvdata(mdev);

	mutex_lock(&maple_keyb_mutex);

	input_unरेजिस्टर_device(kbd->dev);
	kमुक्त(kbd);

	maple_set_drvdata(mdev, शून्य);

	mutex_unlock(&maple_keyb_mutex);
	वापस 0;
पूर्ण

अटल काष्ठा maple_driver dc_kbd_driver = अणु
	.function = MAPLE_FUNC_KEYBOARD,
	.drv = अणु
		.name = "Dreamcast_keyboard",
		.probe = probe_maple_kbd,
		.हटाओ = हटाओ_maple_kbd,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init dc_kbd_init(व्योम)
अणु
	वापस maple_driver_रेजिस्टर(&dc_kbd_driver);
पूर्ण

अटल व्योम __निकास dc_kbd_निकास(व्योम)
अणु
	maple_driver_unरेजिस्टर(&dc_kbd_driver);
पूर्ण

module_init(dc_kbd_init);
module_निकास(dc_kbd_निकास);
