<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Dynapro serial touchscreen driver
 *
 * Copyright (c) 2009 Tias Guns
 * Based on the inexio driver (c) Vojtech Pavlik and Dan Streeपंचांगan and
 * Riअक्षरd Lemon
 */


/*
 * 2009/09/19 Tias Guns <tias@ulyssis.org>
 *   Copied inexio.c and edited क्रम Dynapro protocol (from retired Xorg module)
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"Dynapro serial touchscreen driver"

MODULE_AUTHOR("Tias Guns <tias@ulyssis.org>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Definitions & global arrays.
 */

#घोषणा DYNAPRO_FORMAT_TOUCH_BIT 0x40
#घोषणा DYNAPRO_FORMAT_LENGTH 3
#घोषणा DYNAPRO_RESPONSE_BEGIN_BYTE 0x80

#घोषणा DYNAPRO_MIN_XC 0
#घोषणा DYNAPRO_MAX_XC 0x3ff
#घोषणा DYNAPRO_MIN_YC 0
#घोषणा DYNAPRO_MAX_YC 0x3ff

#घोषणा DYNAPRO_GET_XC(data) (data[1] | ((data[0] & 0x38) << 4))
#घोषणा DYNAPRO_GET_YC(data) (data[2] | ((data[0] & 0x07) << 7))
#घोषणा DYNAPRO_GET_TOUCHED(data) (DYNAPRO_FORMAT_TOUCH_BIT & data[0])

/*
 * Per-touchscreen data.
 */

काष्ठा dynapro अणु
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	पूर्णांक idx;
	अचिन्हित अक्षर data[DYNAPRO_FORMAT_LENGTH];
	अक्षर phys[32];
पूर्ण;

अटल व्योम dynapro_process_data(काष्ठा dynapro *pdynapro)
अणु
	काष्ठा input_dev *dev = pdynapro->dev;

	अगर (DYNAPRO_FORMAT_LENGTH == ++pdynapro->idx) अणु
		input_report_असल(dev, ABS_X, DYNAPRO_GET_XC(pdynapro->data));
		input_report_असल(dev, ABS_Y, DYNAPRO_GET_YC(pdynapro->data));
		input_report_key(dev, BTN_TOUCH,
				 DYNAPRO_GET_TOUCHED(pdynapro->data));
		input_sync(dev);

		pdynapro->idx = 0;
	पूर्ण
पूर्ण

अटल irqवापस_t dynapro_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dynapro *pdynapro = serio_get_drvdata(serio);

	pdynapro->data[pdynapro->idx] = data;

	अगर (DYNAPRO_RESPONSE_BEGIN_BYTE & pdynapro->data[0])
		dynapro_process_data(pdynapro);
	अन्यथा
		dev_dbg(&serio->dev, "unknown/unsynchronized data: %x\n",
			pdynapro->data[0]);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम dynapro_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा dynapro *pdynapro = serio_get_drvdata(serio);

	input_get_device(pdynapro->dev);
	input_unरेजिस्टर_device(pdynapro->dev);
	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_put_device(pdynapro->dev);
	kमुक्त(pdynapro);
पूर्ण

/*
 * dynapro_connect() is the routine that is called when someone adds a
 * new serio device that supports dynapro protocol and रेजिस्टरs it as
 * an input device. This is usually accomplished using inputattach.
 */

अटल पूर्णांक dynapro_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा dynapro *pdynapro;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	pdynapro = kzalloc(माप(काष्ठा dynapro), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!pdynapro || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	pdynapro->serio = serio;
	pdynapro->dev = input_dev;
	snम_लिखो(pdynapro->phys, माप(pdynapro->phys),
		 "%s/input0", serio->phys);

	input_dev->name = "Dynapro Serial TouchScreen";
	input_dev->phys = pdynapro->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_DYNAPRO;
	input_dev->id.product = 0;
	input_dev->id.version = 0x0001;
	input_dev->dev.parent = &serio->dev;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(pdynapro->dev, ABS_X,
			     DYNAPRO_MIN_XC, DYNAPRO_MAX_XC, 0, 0);
	input_set_असल_params(pdynapro->dev, ABS_Y,
			     DYNAPRO_MIN_YC, DYNAPRO_MAX_YC, 0, 0);

	serio_set_drvdata(serio, pdynapro);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(pdynapro->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(pdynapro);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id dynapro_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_DYNAPRO,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, dynapro_serio_ids);

अटल काष्ठा serio_driver dynapro_drv = अणु
	.driver		= अणु
		.name	= "dynapro",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= dynapro_serio_ids,
	.पूर्णांकerrupt	= dynapro_पूर्णांकerrupt,
	.connect	= dynapro_connect,
	.disconnect	= dynapro_disconnect,
पूर्ण;

module_serio_driver(dynapro_drv);
