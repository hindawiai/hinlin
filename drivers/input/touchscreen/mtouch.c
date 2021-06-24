<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MicroTouch (3M) serial touchscreen driver
 *
 * Copyright (c) 2004 Vojtech Pavlik
 */


/*
 * 2005/02/19 Dan Streeपंचांगan <ddstreet@ieee.org>
 *   Copied elo.c and edited क्रम MicroTouch protocol
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"MicroTouch serial touchscreen driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Definitions & global arrays.
 */

#घोषणा MTOUCH_FORMAT_TABLET_STATUS_BIT 0x80
#घोषणा MTOUCH_FORMAT_TABLET_TOUCH_BIT 0x40
#घोषणा MTOUCH_FORMAT_TABLET_LENGTH 5
#घोषणा MTOUCH_RESPONSE_BEGIN_BYTE 0x01
#घोषणा MTOUCH_RESPONSE_END_BYTE 0x0d

/* toकरो: check specs क्रम max length of all responses */
#घोषणा MTOUCH_MAX_LENGTH 16

#घोषणा MTOUCH_MIN_XC 0
#घोषणा MTOUCH_MAX_XC 0x3fff
#घोषणा MTOUCH_MIN_YC 0
#घोषणा MTOUCH_MAX_YC 0x3fff

#घोषणा MTOUCH_GET_XC(data) (((data[2])<<7) | data[1])
#घोषणा MTOUCH_GET_YC(data) (((data[4])<<7) | data[3])
#घोषणा MTOUCH_GET_TOUCHED(data) (MTOUCH_FORMAT_TABLET_TOUCH_BIT & data[0])

/*
 * Per-touchscreen data.
 */

काष्ठा mtouch अणु
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	पूर्णांक idx;
	अचिन्हित अक्षर data[MTOUCH_MAX_LENGTH];
	अक्षर phys[32];
पूर्ण;

अटल व्योम mtouch_process_क्रमmat_tablet(काष्ठा mtouch *mtouch)
अणु
	काष्ठा input_dev *dev = mtouch->dev;

	अगर (MTOUCH_FORMAT_TABLET_LENGTH == ++mtouch->idx) अणु
		input_report_असल(dev, ABS_X, MTOUCH_GET_XC(mtouch->data));
		input_report_असल(dev, ABS_Y, MTOUCH_MAX_YC - MTOUCH_GET_YC(mtouch->data));
		input_report_key(dev, BTN_TOUCH, MTOUCH_GET_TOUCHED(mtouch->data));
		input_sync(dev);

		mtouch->idx = 0;
	पूर्ण
पूर्ण

अटल व्योम mtouch_process_response(काष्ठा mtouch *mtouch)
अणु
	अगर (MTOUCH_RESPONSE_END_BYTE == mtouch->data[mtouch->idx++]) अणु
		/* FIXME - process response */
		mtouch->idx = 0;
	पूर्ण अन्यथा अगर (MTOUCH_MAX_LENGTH == mtouch->idx) अणु
		prपूर्णांकk(KERN_ERR "mtouch.c: too many response bytes\n");
		mtouch->idx = 0;
	पूर्ण
पूर्ण

अटल irqवापस_t mtouch_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा mtouch *mtouch = serio_get_drvdata(serio);

	mtouch->data[mtouch->idx] = data;

	अगर (MTOUCH_FORMAT_TABLET_STATUS_BIT & mtouch->data[0])
		mtouch_process_क्रमmat_tablet(mtouch);
	अन्यथा अगर (MTOUCH_RESPONSE_BEGIN_BYTE == mtouch->data[0])
		mtouch_process_response(mtouch);
	अन्यथा
		prपूर्णांकk(KERN_DEBUG "mtouch.c: unknown/unsynchronized data from device, byte %x\n",mtouch->data[0]);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * mtouch_disconnect() is the opposite of mtouch_connect()
 */

अटल व्योम mtouch_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा mtouch *mtouch = serio_get_drvdata(serio);

	input_get_device(mtouch->dev);
	input_unरेजिस्टर_device(mtouch->dev);
	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_put_device(mtouch->dev);
	kमुक्त(mtouch);
पूर्ण

/*
 * mtouch_connect() is the routine that is called when someone adds a
 * new serio device that supports MicroTouch (Format Tablet) protocol and रेजिस्टरs it as
 * an input device.
 */

अटल पूर्णांक mtouch_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा mtouch *mtouch;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	mtouch = kzalloc(माप(काष्ठा mtouch), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!mtouch || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	mtouch->serio = serio;
	mtouch->dev = input_dev;
	snम_लिखो(mtouch->phys, माप(mtouch->phys), "%s/input0", serio->phys);

	input_dev->name = "MicroTouch Serial TouchScreen";
	input_dev->phys = mtouch->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_MICROTOUCH;
	input_dev->id.product = 0;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(mtouch->dev, ABS_X, MTOUCH_MIN_XC, MTOUCH_MAX_XC, 0, 0);
	input_set_असल_params(mtouch->dev, ABS_Y, MTOUCH_MIN_YC, MTOUCH_MAX_YC, 0, 0);

	serio_set_drvdata(serio, mtouch);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(mtouch->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(mtouch);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id mtouch_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_MICROTOUCH,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, mtouch_serio_ids);

अटल काष्ठा serio_driver mtouch_drv = अणु
	.driver		= अणु
		.name	= "mtouch",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= mtouch_serio_ids,
	.पूर्णांकerrupt	= mtouch_पूर्णांकerrupt,
	.connect	= mtouch_connect,
	.disconnect	= mtouch_disconnect,
पूर्ण;

module_serio_driver(mtouch_drv);
