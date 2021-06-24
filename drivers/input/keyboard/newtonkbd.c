<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2000 Justin Cormack
 */

/*
 * Newton keyboard driver क्रम Linux
 */

/*
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"Newton keyboard driver"

MODULE_AUTHOR("Justin Cormack <j.cormack@doc.ic.ac.uk>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#घोषणा NKBD_KEY	0x7f
#घोषणा NKBD_PRESS	0x80

अटल अचिन्हित अक्षर nkbd_keycode[128] = अणु
	KEY_A, KEY_S, KEY_D, KEY_F, KEY_H, KEY_G, KEY_Z, KEY_X,
	KEY_C, KEY_V, 0, KEY_B, KEY_Q, KEY_W, KEY_E, KEY_R,
	KEY_Y, KEY_T, KEY_1, KEY_2, KEY_3, KEY_4, KEY_6, KEY_5,
	KEY_EQUAL, KEY_9, KEY_7, KEY_MINUS, KEY_8, KEY_0, KEY_RIGHTBRACE, KEY_O,
	KEY_U, KEY_LEFTBRACE, KEY_I, KEY_P, KEY_ENTER, KEY_L, KEY_J, KEY_APOSTROPHE,
	KEY_K, KEY_SEMICOLON, KEY_BACKSLASH, KEY_COMMA, KEY_SLASH, KEY_N, KEY_M, KEY_DOT,
	KEY_TAB, KEY_SPACE, KEY_GRAVE, KEY_DELETE, 0, 0, 0, KEY_LEFTMETA,
	KEY_LEFTSHIFT, KEY_CAPSLOCK, KEY_LEFTALT, KEY_LEFTCTRL, KEY_RIGHTSHIFT, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	KEY_LEFT, KEY_RIGHT, KEY_DOWN, KEY_UP, 0
पूर्ण;

काष्ठा nkbd अणु
	अचिन्हित अक्षर keycode[128];
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	अक्षर phys[32];
पूर्ण;

अटल irqवापस_t nkbd_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा nkbd *nkbd = serio_get_drvdata(serio);

	/* invalid scan codes are probably the init sequence, so we ignore them */
	अगर (nkbd->keycode[data & NKBD_KEY]) अणु
		input_report_key(nkbd->dev, nkbd->keycode[data & NKBD_KEY], data & NKBD_PRESS);
		input_sync(nkbd->dev);
	पूर्ण

	अन्यथा अगर (data == 0xe7) /* end of init sequence */
		prपूर्णांकk(KERN_INFO "input: %s on %s\n", nkbd->dev->name, serio->phys);
	वापस IRQ_HANDLED;

पूर्ण

अटल पूर्णांक nkbd_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा nkbd *nkbd;
	काष्ठा input_dev *input_dev;
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;

	nkbd = kzalloc(माप(काष्ठा nkbd), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!nkbd || !input_dev)
		जाओ fail1;

	nkbd->serio = serio;
	nkbd->dev = input_dev;
	snम_लिखो(nkbd->phys, माप(nkbd->phys), "%s/input0", serio->phys);
	स_नकल(nkbd->keycode, nkbd_keycode, माप(nkbd->keycode));

	input_dev->name = "Newton Keyboard";
	input_dev->phys = nkbd->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_NEWTON;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	input_dev->keycode = nkbd->keycode;
	input_dev->keycodesize = माप(अचिन्हित अक्षर);
	input_dev->keycodemax = ARRAY_SIZE(nkbd_keycode);
	क्रम (i = 0; i < 128; i++)
		set_bit(nkbd->keycode[i], input_dev->keybit);
	clear_bit(0, input_dev->keybit);

	serio_set_drvdata(serio, nkbd);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(nkbd->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(nkbd);
	वापस err;
पूर्ण

अटल व्योम nkbd_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा nkbd *nkbd = serio_get_drvdata(serio);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_unरेजिस्टर_device(nkbd->dev);
	kमुक्त(nkbd);
पूर्ण

अटल स्थिर काष्ठा serio_device_id nkbd_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_NEWTON,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, nkbd_serio_ids);

अटल काष्ठा serio_driver nkbd_drv = अणु
	.driver		= अणु
		.name	= "newtonkbd",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= nkbd_serio_ids,
	.पूर्णांकerrupt	= nkbd_पूर्णांकerrupt,
	.connect	= nkbd_connect,
	.disconnect	= nkbd_disconnect,
पूर्ण;

module_serio_driver(nkbd_drv);
