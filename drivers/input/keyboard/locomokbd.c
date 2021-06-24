<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LoCoMo keyboard driver क्रम Linux-based ARM PDAs:
 * 	- SHARP Zaurus Collie (SL-5500)
 * 	- SHARP Zaurus Poodle (SL-5600)
 *
 * Copyright (c) 2005 John Lenz
 * Based on from xtkbd.c
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>

#समावेश <यंत्र/hardware/locomo.h>
#समावेश <यंत्र/irq.h>

MODULE_AUTHOR("John Lenz <lenz@cs.wisc.edu>");
MODULE_DESCRIPTION("LoCoMo keyboard driver");
MODULE_LICENSE("GPL");

#घोषणा LOCOMOKBD_NUMKEYS	128

#घोषणा KEY_ACTIVITY		KEY_F16
#घोषणा KEY_CONTACT		KEY_F18
#घोषणा KEY_CENTER		KEY_F15

अटल स्थिर अचिन्हित अक्षर
locomokbd_keycode[LOCOMOKBD_NUMKEYS] = अणु
	0, KEY_ESC, KEY_ACTIVITY, 0, 0, 0, 0, 0, 0, 0,				/* 0 - 9 */
	0, 0, 0, 0, 0, 0, 0, KEY_MENU, KEY_HOME, KEY_CONTACT,			/* 10 - 19 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,						/* 20 - 29 */
	0, 0, 0, KEY_CENTER, 0, KEY_MAIL, 0, 0, 0, 0,				/* 30 - 39 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, KEY_RIGHT,					/* 40 - 49 */
	KEY_UP, KEY_LEFT, 0, 0, KEY_P, 0, KEY_O, KEY_I, KEY_Y, KEY_T,		/* 50 - 59 */
	KEY_E, KEY_W, 0, 0, 0, 0, KEY_DOWN, KEY_ENTER, 0, 0,			/* 60 - 69 */
	KEY_BACKSPACE, 0, KEY_L, KEY_U, KEY_H, KEY_R, KEY_D, KEY_Q, 0, 0,	/* 70 - 79 */
	0, 0, 0, 0, 0, 0, KEY_ENTER, KEY_RIGHTSHIFT, KEY_K, KEY_J,		/* 80 - 89 */
	KEY_G, KEY_F, KEY_X, KEY_S, 0, 0, 0, 0, 0, 0,				/* 90 - 99 */
	0, 0, KEY_DOT, 0, KEY_COMMA, KEY_N, KEY_B, KEY_C, KEY_Z, KEY_A,		/* 100 - 109 */
	KEY_LEFTSHIFT, KEY_TAB, KEY_LEFTCTRL, 0, 0, 0, 0, 0, 0, 0,		/* 110 - 119 */
	KEY_M, KEY_SPACE, KEY_V, KEY_APOSTROPHE, KEY_SLASH, 0, 0, 0		/* 120 - 128 */
पूर्ण;

#घोषणा KB_ROWS			16
#घोषणा KB_COLS			8
#घोषणा KB_ROWMASK(r)		(1 << (r))
#घोषणा SCANCODE(c,r)		( ((c)<<4) + (r) + 1 )

#घोषणा KB_DELAY		8
#घोषणा SCAN_INTERVAL		(HZ/10)

काष्ठा locomokbd अणु
	अचिन्हित अक्षर keycode[LOCOMOKBD_NUMKEYS];
	काष्ठा input_dev *input;
	अक्षर phys[32];

	अचिन्हित दीर्घ base;
	spinlock_t lock;

	काष्ठा समयr_list समयr;
	अचिन्हित दीर्घ suspend_jअगरfies;
	अचिन्हित पूर्णांक count_cancel;
पूर्ण;

/* helper functions क्रम पढ़ोing the keyboard matrix */
अटल अंतरभूत व्योम locomokbd_अक्षरge_all(अचिन्हित दीर्घ membase)
अणु
	locomo_ग_लिखोl(0x00FF, membase + LOCOMO_KSC);
पूर्ण

अटल अंतरभूत व्योम locomokbd_activate_all(अचिन्हित दीर्घ membase)
अणु
	अचिन्हित दीर्घ r;

	locomo_ग_लिखोl(0, membase + LOCOMO_KSC);
	r = locomo_पढ़ोl(membase + LOCOMO_KIC);
	r &= 0xFEFF;
	locomo_ग_लिखोl(r, membase + LOCOMO_KIC);
पूर्ण

अटल अंतरभूत व्योम locomokbd_activate_col(अचिन्हित दीर्घ membase, पूर्णांक col)
अणु
	अचिन्हित लघु nset;
	अचिन्हित लघु nbset;

	nset = 0xFF & ~(1 << col);
	nbset = (nset << 8) + nset;
	locomo_ग_लिखोl(nbset, membase + LOCOMO_KSC);
पूर्ण

अटल अंतरभूत व्योम locomokbd_reset_col(अचिन्हित दीर्घ membase, पूर्णांक col)
अणु
	अचिन्हित लघु nbset;

	nbset = ((0xFF & ~(1 << col)) << 8) + 0xFF;
	locomo_ग_लिखोl(nbset, membase + LOCOMO_KSC);
पूर्ण

/*
 * The LoCoMo keyboard only generates पूर्णांकerrupts when a key is pressed.
 * So when a key is pressed, we enable a समयr.  This समयr scans the
 * keyboard, and this is how we detect when the key is released.
 */

/* Scan the hardware keyboard and push any changes up through the input layer */
अटल व्योम locomokbd_scankeyboard(काष्ठा locomokbd *locomokbd)
अणु
	अचिन्हित पूर्णांक row, col, rowd;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक num_pressed;
	अचिन्हित दीर्घ membase = locomokbd->base;

	spin_lock_irqsave(&locomokbd->lock, flags);

	locomokbd_अक्षरge_all(membase);

	num_pressed = 0;
	क्रम (col = 0; col < KB_COLS; col++) अणु

		locomokbd_activate_col(membase, col);
		udelay(KB_DELAY);

		rowd = ~locomo_पढ़ोl(membase + LOCOMO_KIB);
		क्रम (row = 0; row < KB_ROWS; row++) अणु
			अचिन्हित पूर्णांक scancode, pressed, key;

			scancode = SCANCODE(col, row);
			pressed = rowd & KB_ROWMASK(row);
			key = locomokbd->keycode[scancode];

			input_report_key(locomokbd->input, key, pressed);
			अगर (likely(!pressed))
				जारी;

			num_pressed++;

			/* The "Cancel/ESC" key is labeled "On/Off" on
			 * Collie and Poodle and should suspend the device
			 * अगर it was pressed क्रम more than a second. */
			अगर (unlikely(key == KEY_ESC)) अणु
				अगर (!समय_after(jअगरfies,
					locomokbd->suspend_jअगरfies + HZ))
					जारी;
				अगर (locomokbd->count_cancel++
					!= (HZ/SCAN_INTERVAL + 1))
					जारी;
				input_event(locomokbd->input, EV_PWR,
					KEY_SUSPEND, 1);
				locomokbd->suspend_jअगरfies = jअगरfies;
			पूर्ण अन्यथा
				locomokbd->count_cancel = 0;
		पूर्ण
		locomokbd_reset_col(membase, col);
	पूर्ण
	locomokbd_activate_all(membase);

	input_sync(locomokbd->input);

	/* अगर any keys are pressed, enable the समयr */
	अगर (num_pressed)
		mod_समयr(&locomokbd->समयr, jअगरfies + SCAN_INTERVAL);
	अन्यथा
		locomokbd->count_cancel = 0;

	spin_unlock_irqrestore(&locomokbd->lock, flags);
पूर्ण

/*
 * LoCoMo keyboard पूर्णांकerrupt handler.
 */
अटल irqवापस_t locomokbd_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा locomokbd *locomokbd = dev_id;
	u16 r;

	r = locomo_पढ़ोl(locomokbd->base + LOCOMO_KIC);
	अगर ((r & 0x0001) == 0)
		वापस IRQ_HANDLED;

	locomo_ग_लिखोl(r & ~0x0100, locomokbd->base + LOCOMO_KIC); /* Ack */

	/** रुको chattering delay **/
	udelay(100);

	locomokbd_scankeyboard(locomokbd);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * LoCoMo समयr checking क्रम released keys
 */
अटल व्योम locomokbd_समयr_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा locomokbd *locomokbd = from_समयr(locomokbd, t, समयr);

	locomokbd_scankeyboard(locomokbd);
पूर्ण

अटल पूर्णांक locomokbd_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा locomokbd *locomokbd = input_get_drvdata(dev);
	u16 r;
	
	r = locomo_पढ़ोl(locomokbd->base + LOCOMO_KIC) | 0x0010;
	locomo_ग_लिखोl(r, locomokbd->base + LOCOMO_KIC);
	वापस 0;
पूर्ण

अटल व्योम locomokbd_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा locomokbd *locomokbd = input_get_drvdata(dev);
	u16 r;
	
	r = locomo_पढ़ोl(locomokbd->base + LOCOMO_KIC) & ~0x0010;
	locomo_ग_लिखोl(r, locomokbd->base + LOCOMO_KIC);
पूर्ण

अटल पूर्णांक locomokbd_probe(काष्ठा locomo_dev *dev)
अणु
	काष्ठा locomokbd *locomokbd;
	काष्ठा input_dev *input_dev;
	पूर्णांक i, err;

	locomokbd = kzalloc(माप(काष्ठा locomokbd), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!locomokbd || !input_dev) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	/* try and claim memory region */
	अगर (!request_mem_region((अचिन्हित दीर्घ) dev->mapbase,
				dev->length,
				LOCOMO_DRIVER_NAME(dev))) अणु
		err = -EBUSY;
		prपूर्णांकk(KERN_ERR "locomokbd: Can't acquire access to io memory for keyboard\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	locomo_set_drvdata(dev, locomokbd);

	locomokbd->base = (अचिन्हित दीर्घ) dev->mapbase;

	spin_lock_init(&locomokbd->lock);

	समयr_setup(&locomokbd->समयr, locomokbd_समयr_callback, 0);

	locomokbd->suspend_jअगरfies = jअगरfies;

	locomokbd->input = input_dev;
	म_नकल(locomokbd->phys, "locomokbd/input0");

	input_dev->name = "LoCoMo keyboard";
	input_dev->phys = locomokbd->phys;
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.venकरोr = 0x0001;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->खोलो = locomokbd_खोलो;
	input_dev->बंद = locomokbd_बंद;
	input_dev->dev.parent = &dev->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP) |
				BIT_MASK(EV_PWR);
	input_dev->keycode = locomokbd->keycode;
	input_dev->keycodesize = माप(locomokbd_keycode[0]);
	input_dev->keycodemax = ARRAY_SIZE(locomokbd_keycode);

	input_set_drvdata(input_dev, locomokbd);

	स_नकल(locomokbd->keycode, locomokbd_keycode, माप(locomokbd->keycode));
	क्रम (i = 0; i < LOCOMOKBD_NUMKEYS; i++)
		set_bit(locomokbd->keycode[i], input_dev->keybit);
	clear_bit(0, input_dev->keybit);

	/* attempt to get the पूर्णांकerrupt */
	err = request_irq(dev->irq[0], locomokbd_पूर्णांकerrupt, 0, "locomokbd", locomokbd);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "locomokbd: Can't get irq for keyboard\n");
		जाओ err_release_region;
	पूर्ण

	err = input_रेजिस्टर_device(locomokbd->input);
	अगर (err)
		जाओ err_मुक्त_irq;

	वापस 0;

 err_मुक्त_irq:
	मुक्त_irq(dev->irq[0], locomokbd);
 err_release_region:
	release_mem_region((अचिन्हित दीर्घ) dev->mapbase, dev->length);
	locomo_set_drvdata(dev, शून्य);
 err_मुक्त_mem:
	input_मुक्त_device(input_dev);
	kमुक्त(locomokbd);

	वापस err;
पूर्ण

अटल व्योम locomokbd_हटाओ(काष्ठा locomo_dev *dev)
अणु
	काष्ठा locomokbd *locomokbd = locomo_get_drvdata(dev);

	मुक्त_irq(dev->irq[0], locomokbd);

	del_समयr_sync(&locomokbd->समयr);

	input_unरेजिस्टर_device(locomokbd->input);
	locomo_set_drvdata(dev, शून्य);

	release_mem_region((अचिन्हित दीर्घ) dev->mapbase, dev->length);

	kमुक्त(locomokbd);
पूर्ण

अटल काष्ठा locomo_driver keyboard_driver = अणु
	.drv = अणु
		.name = "locomokbd"
	पूर्ण,
	.devid	= LOCOMO_DEVID_KEYBOARD,
	.probe	= locomokbd_probe,
	.हटाओ	= locomokbd_हटाओ,
पूर्ण;

अटल पूर्णांक __init locomokbd_init(व्योम)
अणु
	वापस locomo_driver_रेजिस्टर(&keyboard_driver);
पूर्ण

अटल व्योम __निकास locomokbd_निकास(व्योम)
अणु
	locomo_driver_unरेजिस्टर(&keyboard_driver);
पूर्ण

module_init(locomokbd_init);
module_निकास(locomokbd_निकास);
