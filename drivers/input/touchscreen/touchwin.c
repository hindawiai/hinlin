<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Touchwinकरोw serial touchscreen driver
 *
 * Copyright (c) 2006 Rick Koch <n1gp@hoपंचांगail.com>
 *
 * Based on MicroTouch driver (drivers/input/touchscreen/mtouch.c)
 * Copyright (c) 2004 Vojtech Pavlik
 * and Dan Streeपंचांगan <ddstreet@ieee.org>
 */


/*
 * 2005/02/19 Rick Koch:
 *   The Touchwinकरोw I used is made by Edmark Corp. and
 *   स्थिरantly outमाला_दो a stream of 0's unless it is touched.
 *   It then outमाला_दो 3 bytes: X, Y, and a copy of Y.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"Touchwindow serial touchscreen driver"

MODULE_AUTHOR("Rick Koch <n1gp@hotmail.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Definitions & global arrays.
 */

#घोषणा TW_LENGTH 3

#घोषणा TW_MIN_XC 0
#घोषणा TW_MAX_XC 0xff
#घोषणा TW_MIN_YC 0
#घोषणा TW_MAX_YC 0xff

/*
 * Per-touchscreen data.
 */

काष्ठा tw अणु
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	पूर्णांक idx;
	पूर्णांक touched;
	अचिन्हित अक्षर data[TW_LENGTH];
	अक्षर phys[32];
पूर्ण;

अटल irqवापस_t tw_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा tw *tw = serio_get_drvdata(serio);
	काष्ठा input_dev *dev = tw->dev;

	अगर (data) अणु		/* touch */
		tw->touched = 1;
		tw->data[tw->idx++] = data;
		/* verअगरy length and that the two Y's are the same */
		अगर (tw->idx == TW_LENGTH && tw->data[1] == tw->data[2]) अणु
			input_report_असल(dev, ABS_X, tw->data[0]);
			input_report_असल(dev, ABS_Y, tw->data[1]);
			input_report_key(dev, BTN_TOUCH, 1);
			input_sync(dev);
			tw->idx = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (tw->touched) अणु	/* untouch */
		input_report_key(dev, BTN_TOUCH, 0);
		input_sync(dev);
		tw->idx = 0;
		tw->touched = 0;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * tw_disconnect() is the opposite of tw_connect()
 */

अटल व्योम tw_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा tw *tw = serio_get_drvdata(serio);

	input_get_device(tw->dev);
	input_unरेजिस्टर_device(tw->dev);
	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_put_device(tw->dev);
	kमुक्त(tw);
पूर्ण

/*
 * tw_connect() is the routine that is called when someone adds a
 * new serio device that supports the Touchwin protocol and रेजिस्टरs it as
 * an input device.
 */

अटल पूर्णांक tw_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा tw *tw;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	tw = kzalloc(माप(काष्ठा tw), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!tw || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	tw->serio = serio;
	tw->dev = input_dev;
	snम_लिखो(tw->phys, माप(tw->phys), "%s/input0", serio->phys);

	input_dev->name = "Touchwindow Serial TouchScreen";
	input_dev->phys = tw->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_TOUCHWIN;
	input_dev->id.product = 0;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(tw->dev, ABS_X, TW_MIN_XC, TW_MAX_XC, 0, 0);
	input_set_असल_params(tw->dev, ABS_Y, TW_MIN_YC, TW_MAX_YC, 0, 0);

	serio_set_drvdata(serio, tw);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(tw->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(tw);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id tw_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_TOUCHWIN,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, tw_serio_ids);

अटल काष्ठा serio_driver tw_drv = अणु
	.driver		= अणु
		.name	= "touchwin",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= tw_serio_ids,
	.पूर्णांकerrupt	= tw_पूर्णांकerrupt,
	.connect	= tw_connect,
	.disconnect	= tw_disconnect,
पूर्ण;

module_serio_driver(tw_drv);
