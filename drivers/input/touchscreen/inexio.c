<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * iNexio serial touchscreen driver
 *
 * Copyright (c) 2008 Riअक्षरd Lemon
 * Based on the mtouch driver (c) Vojtech Pavlik and Dan Streeपंचांगan
 */


/*
 * 2008/06/19 Riअक्षरd Lemon <riअक्षरd@codelemon.com>
 *   Copied mtouch.c and edited क्रम iNexio protocol
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"iNexio serial touchscreen driver"

MODULE_AUTHOR("Richard Lemon <richard@codelemon.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Definitions & global arrays.
 */

#घोषणा INEXIO_FORMAT_TOUCH_BIT 0x01
#घोषणा INEXIO_FORMAT_LENGTH 5
#घोषणा INEXIO_RESPONSE_BEGIN_BYTE 0x80

/* toकरो: check specs क्रम max length of all responses */
#घोषणा INEXIO_MAX_LENGTH 16

#घोषणा INEXIO_MIN_XC 0
#घोषणा INEXIO_MAX_XC 0x3fff
#घोषणा INEXIO_MIN_YC 0
#घोषणा INEXIO_MAX_YC 0x3fff

#घोषणा INEXIO_GET_XC(data) (((data[1])<<7) | data[2])
#घोषणा INEXIO_GET_YC(data) (((data[3])<<7) | data[4])
#घोषणा INEXIO_GET_TOUCHED(data) (INEXIO_FORMAT_TOUCH_BIT & data[0])

/*
 * Per-touchscreen data.
 */

काष्ठा inexio अणु
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	पूर्णांक idx;
	अचिन्हित अक्षर data[INEXIO_MAX_LENGTH];
	अक्षर phys[32];
पूर्ण;

अटल व्योम inexio_process_data(काष्ठा inexio *pinexio)
अणु
	काष्ठा input_dev *dev = pinexio->dev;

	अगर (INEXIO_FORMAT_LENGTH == ++pinexio->idx) अणु
		input_report_असल(dev, ABS_X, INEXIO_GET_XC(pinexio->data));
		input_report_असल(dev, ABS_Y, INEXIO_GET_YC(pinexio->data));
		input_report_key(dev, BTN_TOUCH, INEXIO_GET_TOUCHED(pinexio->data));
		input_sync(dev);

		pinexio->idx = 0;
	पूर्ण
पूर्ण

अटल irqवापस_t inexio_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inexio *pinexio = serio_get_drvdata(serio);

	pinexio->data[pinexio->idx] = data;

	अगर (INEXIO_RESPONSE_BEGIN_BYTE&pinexio->data[0])
		inexio_process_data(pinexio);
	अन्यथा
		prपूर्णांकk(KERN_DEBUG "inexio.c: unknown/unsynchronized data from device, byte %x\n",pinexio->data[0]);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * inexio_disconnect() is the opposite of inexio_connect()
 */

अटल व्योम inexio_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा inexio *pinexio = serio_get_drvdata(serio);

	input_get_device(pinexio->dev);
	input_unरेजिस्टर_device(pinexio->dev);
	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_put_device(pinexio->dev);
	kमुक्त(pinexio);
पूर्ण

/*
 * inexio_connect() is the routine that is called when someone adds a
 * new serio device that supports iNexio protocol and रेजिस्टरs it as
 * an input device. This is usually accomplished using inputattach.
 */

अटल पूर्णांक inexio_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा inexio *pinexio;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	pinexio = kzalloc(माप(काष्ठा inexio), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!pinexio || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	pinexio->serio = serio;
	pinexio->dev = input_dev;
	snम_लिखो(pinexio->phys, माप(pinexio->phys), "%s/input0", serio->phys);

	input_dev->name = "iNexio Serial TouchScreen";
	input_dev->phys = pinexio->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_INEXIO;
	input_dev->id.product = 0;
	input_dev->id.version = 0x0001;
	input_dev->dev.parent = &serio->dev;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(pinexio->dev, ABS_X, INEXIO_MIN_XC, INEXIO_MAX_XC, 0, 0);
	input_set_असल_params(pinexio->dev, ABS_Y, INEXIO_MIN_YC, INEXIO_MAX_YC, 0, 0);

	serio_set_drvdata(serio, pinexio);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(pinexio->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(pinexio);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id inexio_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_INEXIO,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, inexio_serio_ids);

अटल काष्ठा serio_driver inexio_drv = अणु
	.driver		= अणु
		.name	= "inexio",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= inexio_serio_ids,
	.पूर्णांकerrupt	= inexio_पूर्णांकerrupt,
	.connect	= inexio_connect,
	.disconnect	= inexio_disconnect,
पूर्ण;

module_serio_driver(inexio_drv);
