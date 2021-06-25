<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 */

/*
 * XT keyboard driver क्रम Linux
 */

/*
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"XT keyboard driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#घोषणा XTKBD_EMUL0	0xe0
#घोषणा XTKBD_EMUL1	0xe1
#घोषणा XTKBD_KEY	0x7f
#घोषणा XTKBD_RELEASE	0x80

अटल अचिन्हित अक्षर xtkbd_keycode[256] = अणु
	  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
	 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
	 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
	 80, 81, 82, 83,  0,  0,  0, 87, 88,  0,  0,  0,  0,  0,  0,  0,
	  0,  0,  0,  0,  0, 87, 88,  0,  0,  0,  0,110,111,103,108,105,
	106
पूर्ण;

काष्ठा xtkbd अणु
	अचिन्हित अक्षर keycode[256];
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	अक्षर phys[32];
पूर्ण;

अटल irqवापस_t xtkbd_पूर्णांकerrupt(काष्ठा serio *serio,
	अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा xtkbd *xtkbd = serio_get_drvdata(serio);

	चयन (data) अणु
		हाल XTKBD_EMUL0:
		हाल XTKBD_EMUL1:
			अवरोध;
		शेष:

			अगर (xtkbd->keycode[data & XTKBD_KEY]) अणु
				input_report_key(xtkbd->dev, xtkbd->keycode[data & XTKBD_KEY], !(data & XTKBD_RELEASE));
				input_sync(xtkbd->dev);
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_WARNING "xtkbd.c: Unknown key (scancode %#x) %s.\n",
					data & XTKBD_KEY, data & XTKBD_RELEASE ? "released" : "pressed");
			पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xtkbd_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा xtkbd *xtkbd;
	काष्ठा input_dev *input_dev;
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;

	xtkbd = kदो_स्मृति(माप(काष्ठा xtkbd), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!xtkbd || !input_dev)
		जाओ fail1;

	xtkbd->serio = serio;
	xtkbd->dev = input_dev;
	snम_लिखो(xtkbd->phys, माप(xtkbd->phys), "%s/input0", serio->phys);
	स_नकल(xtkbd->keycode, xtkbd_keycode, माप(xtkbd->keycode));

	input_dev->name = "XT Keyboard";
	input_dev->phys = xtkbd->phys;
	input_dev->id.bustype = BUS_XTKBD;
	input_dev->id.venकरोr  = 0x0001;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	input_dev->keycode = xtkbd->keycode;
	input_dev->keycodesize = माप(अचिन्हित अक्षर);
	input_dev->keycodemax = ARRAY_SIZE(xtkbd_keycode);

	क्रम (i = 0; i < 255; i++)
		set_bit(xtkbd->keycode[i], input_dev->keybit);
	clear_bit(0, input_dev->keybit);

	serio_set_drvdata(serio, xtkbd);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(xtkbd->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(xtkbd);
	वापस err;
पूर्ण

अटल व्योम xtkbd_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा xtkbd *xtkbd = serio_get_drvdata(serio);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_unरेजिस्टर_device(xtkbd->dev);
	kमुक्त(xtkbd);
पूर्ण

अटल स्थिर काष्ठा serio_device_id xtkbd_serio_ids[] = अणु
	अणु
		.type	= SERIO_XT,
		.proto	= SERIO_ANY,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, xtkbd_serio_ids);

अटल काष्ठा serio_driver xtkbd_drv = अणु
	.driver		= अणु
		.name	= "xtkbd",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= xtkbd_serio_ids,
	.पूर्णांकerrupt	= xtkbd_पूर्णांकerrupt,
	.connect	= xtkbd_connect,
	.disconnect	= xtkbd_disconnect,
पूर्ण;

module_serio_driver(xtkbd_drv);
