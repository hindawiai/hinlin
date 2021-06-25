<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2000-2001 Vojtech Pavlik
 *
 *  Based on the work of:
 *	Hamish Macकरोnald
 */

/*
 * Amiga keyboard driver क्रम Linux/m68k
 */

/*
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/keyboard.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/irq.h>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Amiga keyboard driver");
MODULE_LICENSE("GPL");

#अगर_घोषित CONFIG_HW_CONSOLE
अटल अचिन्हित अक्षर amikbd_keycode[0x78] __initdata = अणु
	[0]	 = KEY_GRAVE,
	[1]	 = KEY_1,
	[2]	 = KEY_2,
	[3]	 = KEY_3,
	[4]	 = KEY_4,
	[5]	 = KEY_5,
	[6]	 = KEY_6,
	[7]	 = KEY_7,
	[8]	 = KEY_8,
	[9]	 = KEY_9,
	[10]	 = KEY_0,
	[11]	 = KEY_MINUS,
	[12]	 = KEY_EQUAL,
	[13]	 = KEY_BACKSLASH,
	[15]	 = KEY_KP0,
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
	[29]	 = KEY_KP1,
	[30]	 = KEY_KP2,
	[31]	 = KEY_KP3,
	[32]	 = KEY_A,
	[33]	 = KEY_S,
	[34]	 = KEY_D,
	[35]	 = KEY_F,
	[36]	 = KEY_G,
	[37]	 = KEY_H,
	[38]	 = KEY_J,
	[39]	 = KEY_K,
	[40]	 = KEY_L,
	[41]	 = KEY_SEMICOLON,
	[42]	 = KEY_APOSTROPHE,
	[43]	 = KEY_BACKSLASH,
	[45]	 = KEY_KP4,
	[46]	 = KEY_KP5,
	[47]	 = KEY_KP6,
	[48]	 = KEY_102ND,
	[49]	 = KEY_Z,
	[50]	 = KEY_X,
	[51]	 = KEY_C,
	[52]	 = KEY_V,
	[53]	 = KEY_B,
	[54]	 = KEY_N,
	[55]	 = KEY_M,
	[56]	 = KEY_COMMA,
	[57]	 = KEY_DOT,
	[58]	 = KEY_SLASH,
	[60]	 = KEY_KPDOT,
	[61]	 = KEY_KP7,
	[62]	 = KEY_KP8,
	[63]	 = KEY_KP9,
	[64]	 = KEY_SPACE,
	[65]	 = KEY_BACKSPACE,
	[66]	 = KEY_TAB,
	[67]	 = KEY_KPENTER,
	[68]	 = KEY_ENTER,
	[69]	 = KEY_ESC,
	[70]	 = KEY_DELETE,
	[74]	 = KEY_KPMINUS,
	[76]	 = KEY_UP,
	[77]	 = KEY_DOWN,
	[78]	 = KEY_RIGHT,
	[79]	 = KEY_LEFT,
	[80]	 = KEY_F1,
	[81]	 = KEY_F2,
	[82]	 = KEY_F3,
	[83]	 = KEY_F4,
	[84]	 = KEY_F5,
	[85]	 = KEY_F6,
	[86]	 = KEY_F7,
	[87]	 = KEY_F8,
	[88]	 = KEY_F9,
	[89]	 = KEY_F10,
	[90]	 = KEY_KPLEFTPAREN,
	[91]	 = KEY_KPRIGHTPAREN,
	[92]	 = KEY_KPSLASH,
	[93]	 = KEY_KPASTERISK,
	[94]	 = KEY_KPPLUS,
	[95]	 = KEY_HELP,
	[96]	 = KEY_LEFTSHIFT,
	[97]	 = KEY_RIGHTSHIFT,
	[98]	 = KEY_CAPSLOCK,
	[99]	 = KEY_LEFTCTRL,
	[100]	 = KEY_LEFTALT,
	[101]	 = KEY_RIGHTALT,
	[102]	 = KEY_LEFTMETA,
	[103]	 = KEY_RIGHTMETA
पूर्ण;

अटल व्योम __init amikbd_init_console_keymaps(व्योम)
अणु
	/* We can spare 512 bytes on stack क्रम temp_map in init path. */
	अचिन्हित लघु temp_map[NR_KEYS];
	पूर्णांक i, j;

	क्रम (i = 0; i < MAX_NR_KEYMAPS; i++) अणु
		अगर (!key_maps[i])
			जारी;
		स_रखो(temp_map, 0, माप(temp_map));
		क्रम (j = 0; j < 0x78; j++) अणु
			अगर (!amikbd_keycode[j])
				जारी;
			temp_map[j] = key_maps[i][amikbd_keycode[j]];
		पूर्ण
		क्रम (j = 0; j < NR_KEYS; j++) अणु
			अगर (!temp_map[j])
				temp_map[j] = 0xf200;
		पूर्ण
		स_नकल(key_maps[i], temp_map, माप(temp_map));
	पूर्ण
पूर्ण
#अन्यथा /* !CONFIG_HW_CONSOLE */
अटल अंतरभूत व्योम amikbd_init_console_keymaps(व्योम) अणुपूर्ण
#पूर्ण_अगर /* !CONFIG_HW_CONSOLE */

अटल स्थिर अक्षर *amikbd_messages[8] = अणु
	[0] = KERN_ALERT "amikbd: Ctrl-Amiga-Amiga reset warning!!\n",
	[1] = KERN_WARNING "amikbd: keyboard lost sync\n",
	[2] = KERN_WARNING "amikbd: keyboard buffer overflow\n",
	[3] = KERN_WARNING "amikbd: keyboard controller failure\n",
	[4] = KERN_ERR "amikbd: keyboard selftest failure\n",
	[5] = KERN_INFO "amikbd: initiate power-up key stream\n",
	[6] = KERN_INFO "amikbd: terminate power-up key stream\n",
	[7] = KERN_WARNING "amikbd: keyboard interrupt\n"
पूर्ण;

अटल irqवापस_t amikbd_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा input_dev *dev = data;
	अचिन्हित अक्षर scancode, करोwn;

	scancode = ~ciaa.sdr;		/* get and invert scancode (keyboard is active low) */
	ciaa.cra |= 0x40;		/* चयन SP pin to output क्रम handshake */
	udelay(85);			/* रुको until 85 us have expired */
	ciaa.cra &= ~0x40;		/* चयन CIA serial port to input mode */

	करोwn = !(scancode & 1);		/* lowest bit is release bit */
	scancode >>= 1;

	अगर (scancode < 0x78) अणु		/* scancodes < 0x78 are keys */
		अगर (scancode == 98) अणु	/* CapsLock is a toggle चयन key on Amiga */
			input_report_key(dev, scancode, 1);
			input_report_key(dev, scancode, 0);
		पूर्ण अन्यथा अणु
			input_report_key(dev, scancode, करोwn);
		पूर्ण

		input_sync(dev);
	पूर्ण अन्यथा				/* scancodes >= 0x78 are error codes */
		prपूर्णांकk(amikbd_messages[scancode - 0x78]);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init amikbd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा input_dev *dev;
	पूर्णांक i, err;

	dev = input_allocate_device();
	अगर (!dev) अणु
		dev_err(&pdev->dev, "Not enough memory for input device\n");
		वापस -ENOMEM;
	पूर्ण

	dev->name = pdev->name;
	dev->phys = "amikbd/input0";
	dev->id.bustype = BUS_AMIGA;
	dev->id.venकरोr = 0x0001;
	dev->id.product = 0x0001;
	dev->id.version = 0x0100;
	dev->dev.parent = &pdev->dev;

	dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);

	क्रम (i = 0; i < 0x78; i++)
		set_bit(i, dev->keybit);

	amikbd_init_console_keymaps();

	ciaa.cra &= ~0x41;	 /* serial data in, turn off TA */
	err = request_irq(IRQ_AMIGA_CIAA_SP, amikbd_पूर्णांकerrupt, 0, "amikbd",
			  dev);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(dev);
	अगर (err)
		जाओ fail3;

	platक्रमm_set_drvdata(pdev, dev);

	वापस 0;

 fail3:	मुक्त_irq(IRQ_AMIGA_CIAA_SP, dev);
 fail2:	input_मुक्त_device(dev);
	वापस err;
पूर्ण

अटल पूर्णांक __निकास amikbd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा input_dev *dev = platक्रमm_get_drvdata(pdev);

	मुक्त_irq(IRQ_AMIGA_CIAA_SP, dev);
	input_unरेजिस्टर_device(dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver amikbd_driver = अणु
	.हटाओ = __निकास_p(amikbd_हटाओ),
	.driver   = अणु
		.name	= "amiga-keyboard",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(amikbd_driver, amikbd_probe);

MODULE_ALIAS("platform:amiga-keyboard");
