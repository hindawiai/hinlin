<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 */

/*
 * Logitech WingMan Warrior joystick driver क्रम Linux
 */

/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"Logitech WingMan Warrior joystick driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Constants.
 */

#घोषणा WARRIOR_MAX_LENGTH	16
अटल अक्षर warrior_lengths[] = अणु 0, 4, 12, 3, 4, 4, 0, 0 पूर्ण;

/*
 * Per-Warrior data.
 */

काष्ठा warrior अणु
	काष्ठा input_dev *dev;
	पूर्णांक idx, len;
	अचिन्हित अक्षर data[WARRIOR_MAX_LENGTH];
	अक्षर phys[32];
पूर्ण;

/*
 * warrior_process_packet() decodes packets the driver receives from the
 * Warrior. It updates the data accordingly.
 */

अटल व्योम warrior_process_packet(काष्ठा warrior *warrior)
अणु
	काष्ठा input_dev *dev = warrior->dev;
	अचिन्हित अक्षर *data = warrior->data;

	अगर (!warrior->idx) वापस;

	चयन ((data[0] >> 4) & 7) अणु
		हाल 1:					/* Button data */
			input_report_key(dev, BTN_TRIGGER,  data[3]       & 1);
			input_report_key(dev, BTN_THUMB,   (data[3] >> 1) & 1);
			input_report_key(dev, BTN_TOP,     (data[3] >> 2) & 1);
			input_report_key(dev, BTN_TOP2,    (data[3] >> 3) & 1);
			अवरोध;
		हाल 3:					/* XY-axis info->data */
			input_report_असल(dev, ABS_X, ((data[0] & 8) << 5) - (data[2] | ((data[0] & 4) << 5)));
			input_report_असल(dev, ABS_Y, (data[1] | ((data[0] & 1) << 7)) - ((data[0] & 2) << 7));
			अवरोध;
		हाल 5:					/* Throttle, spinner, hat info->data */
			input_report_असल(dev, ABS_THROTTLE, (data[1] | ((data[0] & 1) << 7)) - ((data[0] & 2) << 7));
			input_report_असल(dev, ABS_HAT0X, (data[3] & 2 ? 1 : 0) - (data[3] & 1 ? 1 : 0));
			input_report_असल(dev, ABS_HAT0Y, (data[3] & 8 ? 1 : 0) - (data[3] & 4 ? 1 : 0));
			input_report_rel(dev, REL_DIAL,  (data[2] | ((data[0] & 4) << 5)) - ((data[0] & 8) << 5));
			अवरोध;
	पूर्ण
	input_sync(dev);
पूर्ण

/*
 * warrior_पूर्णांकerrupt() is called by the low level driver when अक्षरacters
 * are पढ़ोy क्रम us. We then buffer them क्रम further processing, or call the
 * packet processing routine.
 */

अटल irqवापस_t warrior_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा warrior *warrior = serio_get_drvdata(serio);

	अगर (data & 0x80) अणु
		अगर (warrior->idx) warrior_process_packet(warrior);
		warrior->idx = 0;
		warrior->len = warrior_lengths[(data >> 4) & 7];
	पूर्ण

	अगर (warrior->idx < warrior->len)
		warrior->data[warrior->idx++] = data;

	अगर (warrior->idx == warrior->len) अणु
		अगर (warrior->idx) warrior_process_packet(warrior);
		warrior->idx = 0;
		warrior->len = 0;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/*
 * warrior_disconnect() is the opposite of warrior_connect()
 */

अटल व्योम warrior_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा warrior *warrior = serio_get_drvdata(serio);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_unरेजिस्टर_device(warrior->dev);
	kमुक्त(warrior);
पूर्ण

/*
 * warrior_connect() is the routine that is called when someone adds a
 * new serio device. It looks क्रम the Warrior, and अगर found, रेजिस्टरs
 * it as an input device.
 */

अटल पूर्णांक warrior_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा warrior *warrior;
	काष्ठा input_dev *input_dev;
	पूर्णांक err = -ENOMEM;

	warrior = kzalloc(माप(काष्ठा warrior), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!warrior || !input_dev)
		जाओ fail1;

	warrior->dev = input_dev;
	snम_लिखो(warrior->phys, माप(warrior->phys), "%s/input0", serio->phys);

	input_dev->name = "Logitech WingMan Warrior";
	input_dev->phys = warrior->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_WARRIOR;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL) |
		BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TRIGGER)] = BIT_MASK(BTN_TRIGGER) |
		BIT_MASK(BTN_THUMB) | BIT_MASK(BTN_TOP) | BIT_MASK(BTN_TOP2);
	input_dev->relbit[0] = BIT_MASK(REL_DIAL);
	input_set_असल_params(input_dev, ABS_X, -64, 64, 0, 8);
	input_set_असल_params(input_dev, ABS_Y, -64, 64, 0, 8);
	input_set_असल_params(input_dev, ABS_THROTTLE, -112, 112, 0, 0);
	input_set_असल_params(input_dev, ABS_HAT0X, -1, 1, 0, 0);
	input_set_असल_params(input_dev, ABS_HAT0Y, -1, 1, 0, 0);

	serio_set_drvdata(serio, warrior);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(warrior->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(warrior);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id warrior_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_WARRIOR,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, warrior_serio_ids);

अटल काष्ठा serio_driver warrior_drv = अणु
	.driver		= अणु
		.name	= "warrior",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= warrior_serio_ids,
	.पूर्णांकerrupt	= warrior_पूर्णांकerrupt,
	.connect	= warrior_connect,
	.disconnect	= warrior_disconnect,
पूर्ण;

module_serio_driver(warrior_drv);
