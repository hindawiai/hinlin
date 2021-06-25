<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/input/keyboard/jornada720_kbd.c
 *
 * HP Jornada 720 keyboard platक्रमm driver
 *
 * Copyright (C) 2006/2007 Kristoffer Ericson <Kristoffer.Ericson@Gmail.com>
 *
 *    Copyright (C) 2006 jornada 720 kbd driver by
		Filip Zyzniewsk <Filip.Zyzniewski@tefnet.plX
 *     based on (C) 2004 jornada 720 kbd driver by
		Alex Lange <chicken@handhelds.org>
 */
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <mach/jornada720.h>

MODULE_AUTHOR("Kristoffer Ericson <Kristoffer.Ericson@gmail.com>");
MODULE_DESCRIPTION("HP Jornada 710/720/728 keyboard driver");
MODULE_LICENSE("GPL v2");

अटल अचिन्हित लघु jornada_std_keymap[128] = अणु					/* ROW */
	0, KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7,		/* #1  */
	KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_VOLUMEUP, KEY_VOLUMEDOWN, KEY_MUTE,	/*  -> */
	0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,		/* #2  */
	KEY_0, KEY_MINUS, KEY_EQUAL,0, 0, 0,						/*  -> */
	0, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O,		/* #3  */
	KEY_P, KEY_BACKSLASH, KEY_BACKSPACE, 0, 0, 0,					/*  -> */
	0, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L,		/* #4  */
	KEY_SEMICOLON, KEY_LEFTBRACE, KEY_RIGHTBRACE, 0, 0, 0,				/*  -> */
	0, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA,			/* #5  */
	KEY_DOT, KEY_KPMINUS, KEY_APOSTROPHE, KEY_ENTER, 0, 0,0,			/*  -> */
	0, KEY_TAB, 0, KEY_LEFTSHIFT, 0, KEY_APOSTROPHE, 0, 0, 0, 0,			/* #6  */
	KEY_UP, 0, KEY_RIGHTSHIFT, 0, 0, 0,0, 0, 0, 0, 0, KEY_LEFTALT, KEY_GRAVE,	/*  -> */
	0, 0, KEY_LEFT, KEY_DOWN, KEY_RIGHT, 0, 0, 0, 0,0, KEY_KPASTERISK,		/*  -> */
	KEY_LEFTCTRL, 0, KEY_SPACE, 0, 0, 0, KEY_SLASH, KEY_DELETE, 0, 0,		/*  -> */
	0, 0, 0, KEY_POWER,								/*  -> */
पूर्ण;

काष्ठा jornadakbd अणु
	अचिन्हित लघु keymap[ARRAY_SIZE(jornada_std_keymap)];
	काष्ठा input_dev *input;
पूर्ण;

अटल irqवापस_t jornada720_kbd_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *pdev = dev_id;
	काष्ठा jornadakbd *jornadakbd = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input = jornadakbd->input;
	u8 count, kbd_data, scan_code;

	/* startup ssp with spinlock */
	jornada_ssp_start();

	अगर (jornada_ssp_inout(GETSCANKEYCODE) != TXDUMMY) अणु
		dev_dbg(&pdev->dev,
			"GetKeycode command failed with ETIMEDOUT, flushed bus\n");
	पूर्ण अन्यथा अणु
		/* How many keycodes are रुकोing क्रम us? */
		count = jornada_ssp_byte(TXDUMMY);

		/* Lets drag them out one at a समय */
		जबतक (count--) अणु
			/* Exchange TxDummy क्रम location (keymap[kbddata]) */
			kbd_data = jornada_ssp_byte(TXDUMMY);
			scan_code = kbd_data & 0x7f;

			input_event(input, EV_MSC, MSC_SCAN, scan_code);
			input_report_key(input, jornadakbd->keymap[scan_code],
					 !(kbd_data & 0x80));
			input_sync(input);
		पूर्ण
	पूर्ण

	/* release spinlock and turn off ssp */
	jornada_ssp_end();

	वापस IRQ_HANDLED;
पूर्ण;

अटल पूर्णांक jornada720_kbd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा jornadakbd *jornadakbd;
	काष्ठा input_dev *input_dev;
	पूर्णांक i, err, irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस irq < 0 ? irq : -EINVAL;

	jornadakbd = devm_kzalloc(&pdev->dev, माप(*jornadakbd), GFP_KERNEL);
	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!jornadakbd || !input_dev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, jornadakbd);

	स_नकल(jornadakbd->keymap, jornada_std_keymap,
		माप(jornada_std_keymap));
	jornadakbd->input = input_dev;

	input_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_REP);
	input_dev->name = "HP Jornada 720 keyboard";
	input_dev->phys = "jornadakbd/input0";
	input_dev->keycode = jornadakbd->keymap;
	input_dev->keycodesize = माप(अचिन्हित लघु);
	input_dev->keycodemax = ARRAY_SIZE(jornada_std_keymap);
	input_dev->id.bustype = BUS_HOST;
	input_dev->dev.parent = &pdev->dev;

	क्रम (i = 0; i < ARRAY_SIZE(jornadakbd->keymap); i++)
		__set_bit(jornadakbd->keymap[i], input_dev->keybit);
	__clear_bit(KEY_RESERVED, input_dev->keybit);

	input_set_capability(input_dev, EV_MSC, MSC_SCAN);

	err = devm_request_irq(&pdev->dev, irq, jornada720_kbd_पूर्णांकerrupt,
			       IRQF_TRIGGER_FALLING, "jornadakbd", pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "unable to grab IRQ%d: %d\n", irq, err);
		वापस err;
	पूर्ण

	वापस input_रेजिस्टर_device(jornadakbd->input);
पूर्ण;

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:jornada720_kbd");

अटल काष्ठा platक्रमm_driver jornada720_kbd_driver = अणु
	.driver  = अणु
		.name    = "jornada720_kbd",
	 पूर्ण,
	.probe   = jornada720_kbd_probe,
पूर्ण;
module_platक्रमm_driver(jornada720_kbd_driver);
