<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Fujitsu serial touchscreen driver
 *
 * Copyright (c) Dmitry Torokhov <dtor@mail.ru>
 */


#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"Fujitsu serial touchscreen driver"

MODULE_AUTHOR("Dmitry Torokhov <dtor@mail.ru>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#घोषणा FUJITSU_LENGTH 5

/*
 * Per-touchscreen data.
 */
काष्ठा fujitsu अणु
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	पूर्णांक idx;
	अचिन्हित अक्षर data[FUJITSU_LENGTH];
	अक्षर phys[32];
पूर्ण;

/*
 * Decode serial data (5 bytes per packet)
 * First byte
 * 1 C 0 0 R S S S
 * Where C is 1 जबतक in calibration mode (which we करोn't use)
 * R is 1 when no coordinate corection was करोne.
 * S are button state
 */
अटल irqवापस_t fujitsu_पूर्णांकerrupt(काष्ठा serio *serio,
				     अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा fujitsu *fujitsu = serio_get_drvdata(serio);
	काष्ठा input_dev *dev = fujitsu->dev;

	अगर (fujitsu->idx == 0) अणु
		/* resync skip until start of frame */
		अगर ((data & 0xf0) != 0x80)
			वापस IRQ_HANDLED;
	पूर्ण अन्यथा अणु
		/* resync skip garbage */
		अगर (data & 0x80) अणु
			fujitsu->idx = 0;
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण

	fujitsu->data[fujitsu->idx++] = data;
	अगर (fujitsu->idx == FUJITSU_LENGTH) अणु
		input_report_असल(dev, ABS_X,
				 (fujitsu->data[2] << 7) | fujitsu->data[1]);
		input_report_असल(dev, ABS_Y,
				 (fujitsu->data[4] << 7) | fujitsu->data[3]);
		input_report_key(dev, BTN_TOUCH,
				 (fujitsu->data[0] & 0x03) != 2);
		input_sync(dev);
		fujitsu->idx = 0;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * fujitsu_disconnect() is the opposite of fujitsu_connect()
 */
अटल व्योम fujitsu_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा fujitsu *fujitsu = serio_get_drvdata(serio);

	input_get_device(fujitsu->dev);
	input_unरेजिस्टर_device(fujitsu->dev);
	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_put_device(fujitsu->dev);
	kमुक्त(fujitsu);
पूर्ण

/*
 * fujitsu_connect() is the routine that is called when someone adds a
 * new serio device that supports the Fujitsu protocol and रेजिस्टरs it
 * as input device.
 */
अटल पूर्णांक fujitsu_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा fujitsu *fujitsu;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	fujitsu = kzalloc(माप(काष्ठा fujitsu), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!fujitsu || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	fujitsu->serio = serio;
	fujitsu->dev = input_dev;
	snम_लिखो(fujitsu->phys, माप(fujitsu->phys),
		 "%s/input0", serio->phys);

	input_dev->name = "Fujitsu Serial Touchscreen";
	input_dev->phys = fujitsu->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_FUJITSU;
	input_dev->id.product = 0;
	input_dev->id.version = 0x0100;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	input_set_असल_params(input_dev, ABS_X, 0, 4096, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, 4096, 0, 0);
	serio_set_drvdata(serio, fujitsu);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(fujitsu->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:
	serio_बंद(serio);
 fail2:
	serio_set_drvdata(serio, शून्य);
 fail1:
	input_मुक्त_device(input_dev);
	kमुक्त(fujitsu);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */
अटल स्थिर काष्ठा serio_device_id fujitsu_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_FUJITSU,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, fujitsu_serio_ids);

अटल काष्ठा serio_driver fujitsu_drv = अणु
	.driver		= अणु
		.name	= "fujitsu_ts",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= fujitsu_serio_ids,
	.पूर्णांकerrupt	= fujitsu_पूर्णांकerrupt,
	.connect	= fujitsu_connect,
	.disconnect	= fujitsu_disconnect,
पूर्ण;

module_serio_driver(fujitsu_drv);
