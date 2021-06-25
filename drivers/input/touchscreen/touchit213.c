<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sahara TouchIT-213 serial touchscreen driver
 *
 * Copyright (c) 2007-2008 Claudio Nieder <निजी@claudio.ch>
 *
 * Based on Touchright driver (drivers/input/touchscreen/touchright.c)
 * Copyright (c) 2006 Rick Koch <n1gp@hoपंचांगail.com>
 * Copyright (c) 2004 Vojtech Pavlik
 * and Dan Streeपंचांगan <ddstreet@ieee.org>
 */


#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"Sahara TouchIT-213 serial touchscreen driver"

MODULE_AUTHOR("Claudio Nieder <private@claudio.ch>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Definitions & global arrays.
 */

/*
 * Data is received through COM1 at 9600bit/s,8bit,no parity in packets
 * of 5 byte each.
 *
 *   +--------+   +--------+   +--------+   +--------+   +--------+
 *   |1000000p|   |0xxxxxxx|   |0xxxxxxx|   |0yyyyyyy|   |0yyyyyyy|
 *   +--------+   +--------+   +--------+   +--------+   +--------+
 *                    MSB          LSB          MSB          LSB
 *
 * The value of p is 1 as दीर्घ as the screen is touched and 0 when
 * reporting the location where touching stopped, e.g. where the pen was
 * lअगरted from the screen.
 *
 * When holding the screen in landscape mode as the BIOS text output is
 * presented, x is the horizontal axis with values growing from left to
 * right and y is the vertical axis with values growing from top to
 * bottom.
 *
 * When holding the screen in portrait mode with the Sahara logo in its
 * correct position, x ist the vertical axis with values growing from
 * top to bottom and y is the horizontal axis with values growing from
 * right to left.
 */

#घोषणा T213_FORMAT_TOUCH_BIT	0x01
#घोषणा T213_FORMAT_STATUS_BYTE	0x80
#घोषणा T213_FORMAT_STATUS_MASK	~T213_FORMAT_TOUCH_BIT

/*
 * On my Sahara Touch-IT 213 I have observed x values from 0 to 0x7f0
 * and y values from 0x1d to 0x7e9, so the actual measurement is
 * probably करोne with an 11 bit precision.
 */
#घोषणा T213_MIN_XC 0
#घोषणा T213_MAX_XC 0x07ff
#घोषणा T213_MIN_YC 0
#घोषणा T213_MAX_YC 0x07ff

/*
 * Per-touchscreen data.
 */

काष्ठा touchit213 अणु
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	पूर्णांक idx;
	अचिन्हित अक्षर csum;
	अचिन्हित अक्षर data[5];
	अक्षर phys[32];
पूर्ण;

अटल irqवापस_t touchit213_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा touchit213 *touchit213 = serio_get_drvdata(serio);
	काष्ठा input_dev *dev = touchit213->dev;

	touchit213->data[touchit213->idx] = data;

	चयन (touchit213->idx++) अणु
	हाल 0:
		अगर ((touchit213->data[0] & T213_FORMAT_STATUS_MASK) !=
				T213_FORMAT_STATUS_BYTE) अणु
			pr_debug("unsynchronized data: 0x%02x\n", data);
			touchit213->idx = 0;
		पूर्ण
		अवरोध;

	हाल 4:
		touchit213->idx = 0;
		input_report_असल(dev, ABS_X,
			(touchit213->data[1] << 7) | touchit213->data[2]);
		input_report_असल(dev, ABS_Y,
			(touchit213->data[3] << 7) | touchit213->data[4]);
		input_report_key(dev, BTN_TOUCH,
			touchit213->data[0] & T213_FORMAT_TOUCH_BIT);
		input_sync(dev);
		अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * touchit213_disconnect() is the opposite of touchit213_connect()
 */

अटल व्योम touchit213_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा touchit213 *touchit213 = serio_get_drvdata(serio);

	input_get_device(touchit213->dev);
	input_unरेजिस्टर_device(touchit213->dev);
	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_put_device(touchit213->dev);
	kमुक्त(touchit213);
पूर्ण

/*
 * touchit213_connect() is the routine that is called when someone adds a
 * new serio device that supports the Touchright protocol and रेजिस्टरs it as
 * an input device.
 */

अटल पूर्णांक touchit213_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा touchit213 *touchit213;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	touchit213 = kzalloc(माप(काष्ठा touchit213), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!touchit213 || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	touchit213->serio = serio;
	touchit213->dev = input_dev;
	snम_लिखो(touchit213->phys, माप(touchit213->phys),
		 "%s/input0", serio->phys);

	input_dev->name = "Sahara Touch-iT213 Serial TouchScreen";
	input_dev->phys = touchit213->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_TOUCHIT213;
	input_dev->id.product = 0;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(touchit213->dev, ABS_X,
			     T213_MIN_XC, T213_MAX_XC, 0, 0);
	input_set_असल_params(touchit213->dev, ABS_Y,
			     T213_MIN_YC, T213_MAX_YC, 0, 0);

	serio_set_drvdata(serio, touchit213);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(touchit213->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(touchit213);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id touchit213_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_TOUCHIT213,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, touchit213_serio_ids);

अटल काष्ठा serio_driver touchit213_drv = अणु
	.driver		= अणु
		.name	= "touchit213",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= touchit213_serio_ids,
	.पूर्णांकerrupt	= touchit213_पूर्णांकerrupt,
	.connect	= touchit213_connect,
	.disconnect	= touchit213_disconnect,
पूर्ण;

module_serio_driver(touchit213_drv);
