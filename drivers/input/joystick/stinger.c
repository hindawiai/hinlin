<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2000-2001 Vojtech Pavlik
 *  Copyright (c) 2000 Mark Fletcher
 */

/*
 * Gravis Stinger gamepad driver क्रम Linux
 */

/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"Gravis Stinger gamepad driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Constants.
 */

#घोषणा STINGER_MAX_LENGTH 8

/*
 * Per-Stinger data.
 */

काष्ठा stinger अणु
	काष्ठा input_dev *dev;
	पूर्णांक idx;
	अचिन्हित अक्षर data[STINGER_MAX_LENGTH];
	अक्षर phys[32];
पूर्ण;

/*
 * stinger_process_packet() decodes packets the driver receives from the
 * Stinger. It updates the data accordingly.
 */

अटल व्योम stinger_process_packet(काष्ठा stinger *stinger)
अणु
	काष्ठा input_dev *dev = stinger->dev;
	अचिन्हित अक्षर *data = stinger->data;

	अगर (!stinger->idx) वापस;

	input_report_key(dev, BTN_A,	  ((data[0] & 0x20) >> 5));
	input_report_key(dev, BTN_B,	  ((data[0] & 0x10) >> 4));
	input_report_key(dev, BTN_C,	  ((data[0] & 0x08) >> 3));
	input_report_key(dev, BTN_X,	  ((data[0] & 0x04) >> 2));
	input_report_key(dev, BTN_Y,	  ((data[3] & 0x20) >> 5));
	input_report_key(dev, BTN_Z,	  ((data[3] & 0x10) >> 4));
	input_report_key(dev, BTN_TL,     ((data[3] & 0x08) >> 3));
	input_report_key(dev, BTN_TR,     ((data[3] & 0x04) >> 2));
	input_report_key(dev, BTN_SELECT, ((data[3] & 0x02) >> 1));
	input_report_key(dev, BTN_START,   (data[3] & 0x01));

	input_report_असल(dev, ABS_X, (data[1] & 0x3F) - ((data[0] & 0x01) << 6));
	input_report_असल(dev, ABS_Y, ((data[0] & 0x02) << 5) - (data[2] & 0x3F));

	input_sync(dev);

	वापस;
पूर्ण

/*
 * stinger_पूर्णांकerrupt() is called by the low level driver when अक्षरacters
 * are पढ़ोy क्रम us. We then buffer them क्रम further processing, or call the
 * packet processing routine.
 */

अटल irqवापस_t stinger_पूर्णांकerrupt(काष्ठा serio *serio,
	अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा stinger *stinger = serio_get_drvdata(serio);

	/* All Stinger packets are 4 bytes */

	अगर (stinger->idx < STINGER_MAX_LENGTH)
		stinger->data[stinger->idx++] = data;

	अगर (stinger->idx == 4) अणु
		stinger_process_packet(stinger);
		stinger->idx = 0;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * stinger_disconnect() is the opposite of stinger_connect()
 */

अटल व्योम stinger_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा stinger *stinger = serio_get_drvdata(serio);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_unरेजिस्टर_device(stinger->dev);
	kमुक्त(stinger);
पूर्ण

/*
 * stinger_connect() is the routine that is called when someone adds a
 * new serio device that supports Stinger protocol and रेजिस्टरs it as
 * an input device.
 */

अटल पूर्णांक stinger_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा stinger *stinger;
	काष्ठा input_dev *input_dev;
	पूर्णांक err = -ENOMEM;

	stinger = kदो_स्मृति(माप(काष्ठा stinger), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!stinger || !input_dev)
		जाओ fail1;

	stinger->dev = input_dev;
	snम_लिखो(stinger->phys, माप(stinger->phys), "%s/serio0", serio->phys);

	input_dev->name = "Gravis Stinger";
	input_dev->phys = stinger->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_STINGER;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_A)] = BIT_MASK(BTN_A) | BIT_MASK(BTN_B) |
		BIT_MASK(BTN_C) | BIT_MASK(BTN_X) | BIT_MASK(BTN_Y) |
		BIT_MASK(BTN_Z) | BIT_MASK(BTN_TL) | BIT_MASK(BTN_TR) |
		BIT_MASK(BTN_START) | BIT_MASK(BTN_SELECT);
	input_set_असल_params(input_dev, ABS_X, -64, 64, 0, 4);
	input_set_असल_params(input_dev, ABS_Y, -64, 64, 0, 4);

	serio_set_drvdata(serio, stinger);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(stinger->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(stinger);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id stinger_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_STINGER,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, stinger_serio_ids);

अटल काष्ठा serio_driver stinger_drv = अणु
	.driver		= अणु
		.name	= "stinger",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= stinger_serio_ids,
	.पूर्णांकerrupt	= stinger_पूर्णांकerrupt,
	.connect	= stinger_connect,
	.disconnect	= stinger_disconnect,
पूर्ण;

module_serio_driver(stinger_drv);
