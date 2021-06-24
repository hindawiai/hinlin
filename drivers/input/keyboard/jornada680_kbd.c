<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/input/keyboard/jornada680_kbd.c
 *
 * HP Jornada 620/660/680/690 scan keyboard platक्रमm driver
 *  Copyright (C) 2007  Kristoffer Ericson <Kristoffer.Ericson@gmail.com>
 *
 * Based on hp680_keyb.c
 *  Copyright (C) 2006 Paul Mundt
 *  Copyright (C) 2005 Andriy Skulysh
 * Split from drivers/input/keyboard/hp600_keyb.c
 *  Copyright (C) 2000 Yaegashi Takeshi (hp6xx kbd scan routine and translation table)
 *  Copyright (C) 2000 Niibe Yutaka (HP620 Keyb translation table)
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/पन.स>

#घोषणा PCCR 0xa4000104
#घोषणा PDCR 0xa4000106
#घोषणा PECR 0xa4000108
#घोषणा PFCR 0xa400010a
#घोषणा PCDR 0xa4000124
#घोषणा PDDR 0xa4000126
#घोषणा PEDR 0xa4000128
#घोषणा PFDR 0xa400012a
#घोषणा PGDR 0xa400012c
#घोषणा PHDR 0xa400012e
#घोषणा PJDR 0xa4000130
#घोषणा PKDR 0xa4000132
#घोषणा PLDR 0xa4000134

अटल स्थिर अचिन्हित लघु jornada_scancodes[] = अणु
/* PTD1 */	KEY_CAPSLOCK, KEY_MACRO, KEY_LEFTCTRL, 0, KEY_ESC, KEY_KP5, 0, 0,			/*  1  -> 8   */
		KEY_F1, KEY_F2, KEY_F3, KEY_F8, KEY_F7, KEY_F6, KEY_F4, KEY_F5,				/*  9  -> 16  */
/* PTD5 */	KEY_SLASH, KEY_APOSTROPHE, KEY_ENTER, 0, KEY_Z, 0, 0, 0,				/*  17 -> 24  */
		KEY_X, KEY_C, KEY_V, KEY_DOT, KEY_COMMA, KEY_M, KEY_B, KEY_N,				/*  25 -> 32  */
/* PTD7 */	KEY_KP2, KEY_KP6, KEY_KP3, 0, 0, 0, 0, 0,						/*  33 -> 40  */
		KEY_F10, KEY_RO, KEY_F9, KEY_KP4, KEY_NUMLOCK, KEY_SCROLLLOCK, KEY_LEFTALT, KEY_HANJA,	/*  41 -> 48  */
/* PTE0 */	KEY_KATAKANA, KEY_KP0, KEY_GRAVE, 0, KEY_FIन_अंकCE, 0, 0, 0,				/*  49 -> 56  */
		KEY_KPMINUS, KEY_HIRAGANA, KEY_SPACE, KEY_KPDOT, KEY_VOLUMEUP, 249, 0, 0,		/*  57 -> 64  */
/* PTE1 */	KEY_SEMICOLON, KEY_RIGHTBRACE, KEY_BACKSLASH, 0, KEY_A, 0, 0, 0,			/*  65 -> 72  */
		KEY_S, KEY_D, KEY_F, KEY_L, KEY_K, KEY_J, KEY_G, KEY_H,					/*  73 -> 80  */
/* PTE3 */	KEY_KP8, KEY_LEFTMETA, KEY_RIGHTSHIFT, 0, KEY_TAB, 0, 0, 0,				/*  81 -> 88  */
		0, KEY_LEFTSHIFT, KEY_KP7, KEY_KP9, KEY_KP1, KEY_F11, KEY_KPPLUS, KEY_KPASTERISK,	/*  89 -> 96  */
/* PTE6 */	KEY_P, KEY_LEFTBRACE, KEY_BACKSPACE, 0, KEY_Q, 0, 0, 0,					/*  97 -> 104 */
		KEY_W, KEY_E, KEY_R, KEY_O, KEY_I, KEY_U, KEY_T, KEY_Y,					/* 105 -> 112 */
/* PTE7 */	KEY_0, KEY_MINUS, KEY_EQUAL, 0, KEY_1, 0, 0, 0,						/* 113 -> 120 */
		KEY_2, KEY_3, KEY_4, KEY_9, KEY_8, KEY_7, KEY_5, KEY_6,					/* 121 -> 128 */
/* **** */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
पूर्ण;

#घोषणा JORNADA_SCAN_SIZE	18

काष्ठा jornadakbd अणु
	काष्ठा input_dev *input;
	अचिन्हित लघु keymap[ARRAY_SIZE(jornada_scancodes)];
	अचिन्हित अक्षर length;
	अचिन्हित अक्षर old_scan[JORNADA_SCAN_SIZE];
	अचिन्हित अक्षर new_scan[JORNADA_SCAN_SIZE];
पूर्ण;

अटल व्योम jornada_parse_kbd(काष्ठा jornadakbd *jornadakbd)
अणु
	काष्ठा input_dev *input_dev = jornadakbd->input;
	अचिन्हित लघु *keymap = jornadakbd->keymap;
	अचिन्हित पूर्णांक sync_me = 0;
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < JORNADA_SCAN_SIZE; i++) अणु
		अचिन्हित अक्षर new = jornadakbd->new_scan[i];
		अचिन्हित अक्षर old = jornadakbd->old_scan[i];
		अचिन्हित पूर्णांक xor = new ^ old;

		अगर (xor == 0)
			जारी;

		क्रम (j = 0; j < 8; j++) अणु
			अचिन्हित पूर्णांक bit = 1 << j;
			अगर (xor & bit) अणु
				अचिन्हित पूर्णांक scancode = (i << 3) + j;
				input_event(input_dev,
					    EV_MSC, MSC_SCAN, scancode);
				input_report_key(input_dev,
						 keymap[scancode],
						 !(new & bit));
				sync_me = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (sync_me)
	    input_sync(input_dev);
पूर्ण

अटल व्योम jornada_scan_keyb(अचिन्हित अक्षर *s)
अणु
	पूर्णांक i;
	अचिन्हित लघु ec_अटल, dc_अटल; /* = UINT16_t */
	अचिन्हित अक्षर matrix_चयन[] = अणु
		0xfd, 0xff,   /* PTD1 PD(1) */
		0xdf, 0xff,   /* PTD5 PD(5) */
		0x7f, 0xff,   /* PTD7 PD(7) */
		0xff, 0xfe,   /* PTE0 PE(0) */
		0xff, 0xfd,   /* PTE1 PE(1) */
		0xff, 0xf7,   /* PTE3 PE(3) */
		0xff, 0xbf,   /* PTE6 PE(6) */
		0xff, 0x7f,   /* PTE7 PE(7) */
	पूर्ण, *t = matrix_चयन;
	/* PD(x) :
	1.   0xcc0c & (1~(1 << (2*(x)+1)))))
	2.   (0xf0cf & 0xfffff) */
	/* PE(x) :
	1.   0xcc0c & 0xffff
	2.   0xf0cf & (1~(1 << (2*(x)+1))))) */
	अचिन्हित लघु matrix_PDE[] = अणु
		0xcc04, 0xf0cf,  /* PD(1) */
		0xc40c, 0xf0cf,	 /* PD(5) */
		0x4c0c, 0xf0cf,  /* PD(7) */
		0xcc0c, 0xf0cd,  /* PE(0) */
		0xcc0c, 0xf0c7,	 /* PE(1) */
		0xcc0c, 0xf04f,  /* PE(3) */
		0xcc0c, 0xd0cf,	 /* PE(6) */
		0xcc0c, 0x70cf,	 /* PE(7) */
	पूर्ण, *y = matrix_PDE;

	/* Save these control reg bits */
	dc_अटल = (__raw_पढ़ोw(PDCR) & (~0xcc0c));
	ec_अटल = (__raw_पढ़ोw(PECR) & (~0xf0cf));

	क्रम (i = 0; i < 8; i++) अणु
		/* disable output क्रम all but the one we want to scan */
		__raw_ग_लिखोw((dc_अटल | *y++), PDCR);
		__raw_ग_लिखोw((ec_अटल | *y++), PECR);
		udelay(5);

		/* Get scanline row */
		__raw_ग_लिखोb(*t++, PDDR);
		__raw_ग_लिखोb(*t++, PEDR);
		udelay(50);

		/* Read data */
		*s++ = __raw_पढ़ोb(PCDR);
		*s++ = __raw_पढ़ोb(PFDR);
	पूर्ण
	/* Scan no lines */
	__raw_ग_लिखोb(0xff, PDDR);
	__raw_ग_लिखोb(0xff, PEDR);

	/* Enable all scanlines */
	__raw_ग_लिखोw((dc_अटल | (0x5555 & 0xcc0c)),PDCR);
	__raw_ग_लिखोw((ec_अटल | (0x5555 & 0xf0cf)),PECR);

	/* Ignore extra keys and events */
	*s++ = __raw_पढ़ोb(PGDR);
	*s++ = __raw_पढ़ोb(PHDR);
पूर्ण

अटल व्योम jornadakbd680_poll(काष्ठा input_dev *input)
अणु
	काष्ठा jornadakbd *jornadakbd = input_get_drvdata(input);

	jornada_scan_keyb(jornadakbd->new_scan);
	jornada_parse_kbd(jornadakbd);
	स_नकल(jornadakbd->old_scan, jornadakbd->new_scan, JORNADA_SCAN_SIZE);
पूर्ण

अटल पूर्णांक jornada680kbd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा jornadakbd *jornadakbd;
	काष्ठा input_dev *input_dev;
	पूर्णांक i, error;

	jornadakbd = devm_kzalloc(&pdev->dev, माप(काष्ठा jornadakbd),
				  GFP_KERNEL);
	अगर (!jornadakbd)
		वापस -ENOMEM;

	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!input_dev) अणु
		dev_err(&pdev->dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	jornadakbd->input = input_dev;

	स_नकल(jornadakbd->keymap, jornada_scancodes,
		माप(jornadakbd->keymap));

	input_set_drvdata(input_dev, jornadakbd);
	input_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_REP);
	input_dev->name = "HP Jornada 680 keyboard";
	input_dev->phys = "jornadakbd/input0";
	input_dev->keycode = jornadakbd->keymap;
	input_dev->keycodesize = माप(अचिन्हित लघु);
	input_dev->keycodemax = ARRAY_SIZE(jornada_scancodes);
	input_dev->id.bustype = BUS_HOST;

	क्रम (i = 0; i < 128; i++)
		अगर (jornadakbd->keymap[i])
			__set_bit(jornadakbd->keymap[i], input_dev->keybit);
	__clear_bit(KEY_RESERVED, input_dev->keybit);

	input_set_capability(input_dev, EV_MSC, MSC_SCAN);

	error = input_setup_polling(input_dev, jornadakbd680_poll);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to set up polling\n");
		वापस error;
	पूर्ण

	input_set_poll_पूर्णांकerval(input_dev, 50 /* msec */);

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register input device\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver jornada680kbd_driver = अणु
	.driver	= अणु
		.name	= "jornada680_kbd",
	पूर्ण,
	.probe	= jornada680kbd_probe,
पूर्ण;
module_platक्रमm_driver(jornada680kbd_driver);

MODULE_AUTHOR("Kristoffer Ericson <kristoffer.ericson@gmail.com>");
MODULE_DESCRIPTION("HP Jornada 620/660/680/690 Keyboard Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:jornada680_kbd");
