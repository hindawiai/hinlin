<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Stowaway keyboard driver क्रम Linux
 */

/*
 *  Copyright (c) 2006 Marek Vasut
 *
 *  Based on Newton keyboard driver क्रम Linux
 *  by Justin Cormack
 */

/*
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"Stowaway keyboard driver"

MODULE_AUTHOR("Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#घोषणा SKBD_KEY_MASK	0x7f
#घोषणा SKBD_RELEASE	0x80

अटल अचिन्हित अक्षर skbd_keycode[128] = अणु
	KEY_1, KEY_2, KEY_3, KEY_Z, KEY_4, KEY_5, KEY_6, KEY_7,
	0, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_GRAVE,
	KEY_X, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_SPACE,
	KEY_CAPSLOCK, KEY_TAB, KEY_LEFTCTRL, 0, 0, 0, 0, 0,
	0, 0, 0, KEY_LEFTALT, 0, 0, 0, 0,
	0, 0, 0, 0, KEY_C, KEY_V, KEY_B, KEY_N,
	KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, KEY_HOME, KEY_8, KEY_9, KEY_0, KEY_ESC,
	KEY_LEFTBRACE, KEY_RIGHTBRACE, KEY_BACKSLASH, KEY_END, KEY_U, KEY_I, KEY_O, KEY_P,
	KEY_APOSTROPHE, KEY_ENTER, KEY_PAGEUP,0, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON,
	KEY_SLASH, KEY_UP, KEY_PAGEDOWN, 0,KEY_M, KEY_COMMA, KEY_DOT, KEY_INSERT,
	KEY_DELETE, KEY_LEFT, KEY_DOWN, KEY_RIGHT,  0, 0, 0,
	KEY_LEFTSHIFT, KEY_RIGHTSHIFT, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7,
	KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, 0, 0, 0
पूर्ण;

काष्ठा skbd अणु
	अचिन्हित अक्षर keycode[128];
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	अक्षर phys[32];
पूर्ण;

अटल irqवापस_t skbd_पूर्णांकerrupt(काष्ठा serio *serio, अचिन्हित अक्षर data,
				  अचिन्हित पूर्णांक flags)
अणु
	काष्ठा skbd *skbd = serio_get_drvdata(serio);
	काष्ठा input_dev *dev = skbd->dev;

	अगर (skbd->keycode[data & SKBD_KEY_MASK]) अणु
		input_report_key(dev, skbd->keycode[data & SKBD_KEY_MASK],
				 !(data & SKBD_RELEASE));
		input_sync(dev);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक skbd_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा skbd *skbd;
	काष्ठा input_dev *input_dev;
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;

	skbd = kzalloc(माप(काष्ठा skbd), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!skbd || !input_dev)
		जाओ fail1;

	skbd->serio = serio;
	skbd->dev = input_dev;
	snम_लिखो(skbd->phys, माप(skbd->phys), "%s/input0", serio->phys);
	स_नकल(skbd->keycode, skbd_keycode, माप(skbd->keycode));

	input_dev->name = "Stowaway Keyboard";
	input_dev->phys = skbd->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_STOWAWAY;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	input_dev->keycode = skbd->keycode;
	input_dev->keycodesize = माप(अचिन्हित अक्षर);
	input_dev->keycodemax = ARRAY_SIZE(skbd_keycode);
	क्रम (i = 0; i < ARRAY_SIZE(skbd_keycode); i++)
		set_bit(skbd_keycode[i], input_dev->keybit);
	clear_bit(0, input_dev->keybit);

	serio_set_drvdata(serio, skbd);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(skbd->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3: serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(skbd);
	वापस err;
पूर्ण

अटल व्योम skbd_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा skbd *skbd = serio_get_drvdata(serio);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_unरेजिस्टर_device(skbd->dev);
	kमुक्त(skbd);
पूर्ण

अटल स्थिर काष्ठा serio_device_id skbd_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_STOWAWAY,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, skbd_serio_ids);

अटल काष्ठा serio_driver skbd_drv = अणु
	.driver		= अणु
		.name	= "stowaway",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= skbd_serio_ids,
	.पूर्णांकerrupt	= skbd_पूर्णांकerrupt,
	.connect	= skbd_connect,
	.disconnect	= skbd_disconnect,
पूर्ण;

module_serio_driver(skbd_drv);
