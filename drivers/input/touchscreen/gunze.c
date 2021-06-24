<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2000-2001 Vojtech Pavlik
 */

/*
 * Gunze AHL-51S touchscreen driver क्रम Linux
 */

/*
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"Gunze AHL-51S touchscreen driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Definitions & global arrays.
 */

#घोषणा	GUNZE_MAX_LENGTH	10

/*
 * Per-touchscreen data.
 */

काष्ठा gunze अणु
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	पूर्णांक idx;
	अचिन्हित अक्षर data[GUNZE_MAX_LENGTH];
	अक्षर phys[32];
पूर्ण;

अटल व्योम gunze_process_packet(काष्ठा gunze *gunze)
अणु
	काष्ठा input_dev *dev = gunze->dev;

	अगर (gunze->idx != GUNZE_MAX_LENGTH || gunze->data[5] != ',' ||
		(gunze->data[0] != 'T' && gunze->data[0] != 'R')) अणु
		prपूर्णांकk(KERN_WARNING "gunze.c: bad packet: >%.*s<\n", GUNZE_MAX_LENGTH, gunze->data);
		वापस;
	पूर्ण

	input_report_असल(dev, ABS_X, simple_म_से_अदीर्घ(gunze->data + 1, शून्य, 10));
	input_report_असल(dev, ABS_Y, 1024 - simple_म_से_अदीर्घ(gunze->data + 6, शून्य, 10));
	input_report_key(dev, BTN_TOUCH, gunze->data[0] == 'T');
	input_sync(dev);
पूर्ण

अटल irqवापस_t gunze_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा gunze *gunze = serio_get_drvdata(serio);

	अगर (data == '\r') अणु
		gunze_process_packet(gunze);
		gunze->idx = 0;
	पूर्ण अन्यथा अणु
		अगर (gunze->idx < GUNZE_MAX_LENGTH)
			gunze->data[gunze->idx++] = data;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/*
 * gunze_disconnect() is the opposite of gunze_connect()
 */

अटल व्योम gunze_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा gunze *gunze = serio_get_drvdata(serio);

	input_get_device(gunze->dev);
	input_unरेजिस्टर_device(gunze->dev);
	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_put_device(gunze->dev);
	kमुक्त(gunze);
पूर्ण

/*
 * gunze_connect() is the routine that is called when someone adds a
 * new serio device that supports Gunze protocol and रेजिस्टरs it as
 * an input device.
 */

अटल पूर्णांक gunze_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा gunze *gunze;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	gunze = kzalloc(माप(काष्ठा gunze), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!gunze || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	gunze->serio = serio;
	gunze->dev = input_dev;
	snम_लिखो(gunze->phys, माप(serio->phys), "%s/input0", serio->phys);

	input_dev->name = "Gunze AHL-51S TouchScreen";
	input_dev->phys = gunze->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_GUNZE;
	input_dev->id.product = 0x0051;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(input_dev, ABS_X, 24, 1000, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 24, 1000, 0, 0);

	serio_set_drvdata(serio, gunze);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(gunze->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(gunze);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id gunze_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_GUNZE,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, gunze_serio_ids);

अटल काष्ठा serio_driver gunze_drv = अणु
	.driver		= अणु
		.name	= "gunze",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= gunze_serio_ids,
	.पूर्णांकerrupt	= gunze_पूर्णांकerrupt,
	.connect	= gunze_connect,
	.disconnect	= gunze_disconnect,
पूर्ण;

module_serio_driver(gunze_drv);
