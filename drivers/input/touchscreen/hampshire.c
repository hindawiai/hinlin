<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hampshire serial touchscreen driver
 *
 * Copyright (c) 2010 Adam Bennett
 * Based on the dynapro driver (c) Tias Guns
 */


/*
 * 2010/04/08 Adam Bennett <abennett72@gmail.com>
 *   Copied dynapro.c and edited क्रम Hampshire 4-byte protocol
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"Hampshire serial touchscreen driver"

MODULE_AUTHOR("Adam Bennett <abennett72@gmail.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Definitions & global arrays.
 */

#घोषणा HAMPSHIRE_FORMAT_TOUCH_BIT 0x40
#घोषणा HAMPSHIRE_FORMAT_LENGTH 4
#घोषणा HAMPSHIRE_RESPONSE_BEGIN_BYTE 0x80

#घोषणा HAMPSHIRE_MIN_XC 0
#घोषणा HAMPSHIRE_MAX_XC 0x1000
#घोषणा HAMPSHIRE_MIN_YC 0
#घोषणा HAMPSHIRE_MAX_YC 0x1000

#घोषणा HAMPSHIRE_GET_XC(data) (((data[3] & 0x0c) >> 2) | (data[1] << 2) | ((data[0] & 0x38) << 6))
#घोषणा HAMPSHIRE_GET_YC(data) ((data[3] & 0x03) | (data[2] << 2) | ((data[0] & 0x07) << 9))
#घोषणा HAMPSHIRE_GET_TOUCHED(data) (HAMPSHIRE_FORMAT_TOUCH_BIT & data[0])

/*
 * Per-touchscreen data.
 */

काष्ठा hampshire अणु
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	पूर्णांक idx;
	अचिन्हित अक्षर data[HAMPSHIRE_FORMAT_LENGTH];
	अक्षर phys[32];
पूर्ण;

अटल व्योम hampshire_process_data(काष्ठा hampshire *phampshire)
अणु
	काष्ठा input_dev *dev = phampshire->dev;

	अगर (HAMPSHIRE_FORMAT_LENGTH == ++phampshire->idx) अणु
		input_report_असल(dev, ABS_X, HAMPSHIRE_GET_XC(phampshire->data));
		input_report_असल(dev, ABS_Y, HAMPSHIRE_GET_YC(phampshire->data));
		input_report_key(dev, BTN_TOUCH,
				 HAMPSHIRE_GET_TOUCHED(phampshire->data));
		input_sync(dev);

		phampshire->idx = 0;
	पूर्ण
पूर्ण

अटल irqवापस_t hampshire_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा hampshire *phampshire = serio_get_drvdata(serio);

	phampshire->data[phampshire->idx] = data;

	अगर (HAMPSHIRE_RESPONSE_BEGIN_BYTE & phampshire->data[0])
		hampshire_process_data(phampshire);
	अन्यथा
		dev_dbg(&serio->dev, "unknown/unsynchronized data: %x\n",
			phampshire->data[0]);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम hampshire_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा hampshire *phampshire = serio_get_drvdata(serio);

	input_get_device(phampshire->dev);
	input_unरेजिस्टर_device(phampshire->dev);
	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_put_device(phampshire->dev);
	kमुक्त(phampshire);
पूर्ण

/*
 * hampshire_connect() is the routine that is called when someone adds a
 * new serio device that supports hampshire protocol and रेजिस्टरs it as
 * an input device. This is usually accomplished using inputattach.
 */

अटल पूर्णांक hampshire_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा hampshire *phampshire;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	phampshire = kzalloc(माप(काष्ठा hampshire), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!phampshire || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	phampshire->serio = serio;
	phampshire->dev = input_dev;
	snम_लिखो(phampshire->phys, माप(phampshire->phys),
		 "%s/input0", serio->phys);

	input_dev->name = "Hampshire Serial TouchScreen";
	input_dev->phys = phampshire->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_HAMPSHIRE;
	input_dev->id.product = 0;
	input_dev->id.version = 0x0001;
	input_dev->dev.parent = &serio->dev;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(phampshire->dev, ABS_X,
			     HAMPSHIRE_MIN_XC, HAMPSHIRE_MAX_XC, 0, 0);
	input_set_असल_params(phampshire->dev, ABS_Y,
			     HAMPSHIRE_MIN_YC, HAMPSHIRE_MAX_YC, 0, 0);

	serio_set_drvdata(serio, phampshire);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(phampshire->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(phampshire);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id hampshire_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_HAMPSHIRE,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, hampshire_serio_ids);

अटल काष्ठा serio_driver hampshire_drv = अणु
	.driver		= अणु
		.name	= "hampshire",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= hampshire_serio_ids,
	.पूर्णांकerrupt	= hampshire_पूर्णांकerrupt,
	.connect	= hampshire_connect,
	.disconnect	= hampshire_disconnect,
पूर्ण;

module_serio_driver(hampshire_drv);
