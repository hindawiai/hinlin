<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Touchright serial touchscreen driver
 *
 * Copyright (c) 2006 Rick Koch <n1gp@hoपंचांगail.com>
 *
 * Based on MicroTouch driver (drivers/input/touchscreen/mtouch.c)
 * Copyright (c) 2004 Vojtech Pavlik
 * and Dan Streeपंचांगan <ddstreet@ieee.org>
 */


#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"Touchright serial touchscreen driver"

MODULE_AUTHOR("Rick Koch <n1gp@hotmail.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Definitions & global arrays.
 */

#घोषणा TR_FORMAT_TOUCH_BIT	0x01
#घोषणा TR_FORMAT_STATUS_BYTE	0x40
#घोषणा TR_FORMAT_STATUS_MASK	~TR_FORMAT_TOUCH_BIT

#घोषणा TR_LENGTH 5

#घोषणा TR_MIN_XC 0
#घोषणा TR_MAX_XC 0x1ff
#घोषणा TR_MIN_YC 0
#घोषणा TR_MAX_YC 0x1ff

/*
 * Per-touchscreen data.
 */

काष्ठा tr अणु
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	पूर्णांक idx;
	अचिन्हित अक्षर data[TR_LENGTH];
	अक्षर phys[32];
पूर्ण;

अटल irqवापस_t tr_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा tr *tr = serio_get_drvdata(serio);
	काष्ठा input_dev *dev = tr->dev;

	tr->data[tr->idx] = data;

	अगर ((tr->data[0] & TR_FORMAT_STATUS_MASK) == TR_FORMAT_STATUS_BYTE) अणु
		अगर (++tr->idx == TR_LENGTH) अणु
			input_report_असल(dev, ABS_X,
				(tr->data[1] << 5) | (tr->data[2] >> 1));
			input_report_असल(dev, ABS_Y,
				(tr->data[3] << 5) | (tr->data[4] >> 1));
			input_report_key(dev, BTN_TOUCH,
				tr->data[0] & TR_FORMAT_TOUCH_BIT);
			input_sync(dev);
			tr->idx = 0;
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * tr_disconnect() is the opposite of tr_connect()
 */

अटल व्योम tr_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा tr *tr = serio_get_drvdata(serio);

	input_get_device(tr->dev);
	input_unरेजिस्टर_device(tr->dev);
	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_put_device(tr->dev);
	kमुक्त(tr);
पूर्ण

/*
 * tr_connect() is the routine that is called when someone adds a
 * new serio device that supports the Touchright protocol and रेजिस्टरs it as
 * an input device.
 */

अटल पूर्णांक tr_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा tr *tr;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	tr = kzalloc(माप(काष्ठा tr), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!tr || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	tr->serio = serio;
	tr->dev = input_dev;
	snम_लिखो(tr->phys, माप(tr->phys), "%s/input0", serio->phys);

	input_dev->name = "Touchright Serial TouchScreen";
	input_dev->phys = tr->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_TOUCHRIGHT;
	input_dev->id.product = 0;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(tr->dev, ABS_X, TR_MIN_XC, TR_MAX_XC, 0, 0);
	input_set_असल_params(tr->dev, ABS_Y, TR_MIN_YC, TR_MAX_YC, 0, 0);

	serio_set_drvdata(serio, tr);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(tr->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(tr);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id tr_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_TOUCHRIGHT,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, tr_serio_ids);

अटल काष्ठा serio_driver tr_drv = अणु
	.driver		= अणु
		.name	= "touchright",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= tr_serio_ids,
	.पूर्णांकerrupt	= tr_पूर्णांकerrupt,
	.connect	= tr_connect,
	.disconnect	= tr_disconnect,
पूर्ण;

module_serio_driver(tr_drv);
