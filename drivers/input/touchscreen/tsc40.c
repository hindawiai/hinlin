<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TSC-40 serial touchscreen driver. It should be compatible with
 * TSC-10 and 25.
 *
 * Author: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा PACKET_LENGTH  5
काष्ठा tsc_ser अणु
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	u32 idx;
	अचिन्हित अक्षर data[PACKET_LENGTH];
	अक्षर phys[32];
पूर्ण;

अटल व्योम tsc_process_data(काष्ठा tsc_ser *ptsc)
अणु
	काष्ठा input_dev *dev = ptsc->dev;
	u8 *data = ptsc->data;
	u32 x;
	u32 y;

	x = ((data[1] & 0x03) << 8) | data[2];
	y = ((data[3] & 0x03) << 8) | data[4];

	input_report_असल(dev, ABS_X, x);
	input_report_असल(dev, ABS_Y, y);
	input_report_key(dev, BTN_TOUCH, 1);

	input_sync(dev);
पूर्ण

अटल irqवापस_t tsc_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा tsc_ser *ptsc = serio_get_drvdata(serio);
	काष्ठा input_dev *dev = ptsc->dev;

	ptsc->data[ptsc->idx] = data;
	चयन (ptsc->idx++) अणु
	हाल 0:
		अगर (unlikely((data & 0x3e) != 0x10)) अणु
			dev_dbg(&serio->dev,
				"unsynchronized packet start (0x%02x)\n", data);
			ptsc->idx = 0;
		पूर्ण अन्यथा अगर (!(data & 0x01)) अणु
			input_report_key(dev, BTN_TOUCH, 0);
			input_sync(dev);
			ptsc->idx = 0;
		पूर्ण
		अवरोध;

	हाल 1:
	हाल 3:
		अगर (unlikely(data & 0xfc)) अणु
			dev_dbg(&serio->dev,
				"unsynchronized data 0x%02x at offset %d\n",
				data, ptsc->idx - 1);
			ptsc->idx = 0;
		पूर्ण
		अवरोध;

	हाल 4:
		tsc_process_data(ptsc);
		ptsc->idx = 0;
		अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tsc_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा tsc_ser *ptsc;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;

	ptsc = kzalloc(माप(काष्ठा tsc_ser), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!ptsc || !input_dev) अणु
		error = -ENOMEM;
		जाओ fail1;
	पूर्ण

	ptsc->serio = serio;
	ptsc->dev = input_dev;
	snम_लिखो(ptsc->phys, माप(ptsc->phys), "%s/input0", serio->phys);

	input_dev->name = "TSC-10/25/40 Serial TouchScreen";
	input_dev->phys = ptsc->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_TSC40;
	input_dev->id.product = 40;
	input_dev->id.version = 0x0001;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	__set_bit(BTN_TOUCH, input_dev->keybit);
	input_set_असल_params(ptsc->dev, ABS_X, 0, 0x3ff, 0, 0);
	input_set_असल_params(ptsc->dev, ABS_Y, 0, 0x3ff, 0, 0);

	serio_set_drvdata(serio, ptsc);

	error = serio_खोलो(serio, drv);
	अगर (error)
		जाओ fail2;

	error = input_रेजिस्टर_device(ptsc->dev);
	अगर (error)
		जाओ fail3;

	वापस 0;

fail3:
	serio_बंद(serio);
fail2:
	serio_set_drvdata(serio, शून्य);
fail1:
	input_मुक्त_device(input_dev);
	kमुक्त(ptsc);
	वापस error;
पूर्ण

अटल व्योम tsc_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा tsc_ser *ptsc = serio_get_drvdata(serio);

	serio_बंद(serio);

	input_unरेजिस्टर_device(ptsc->dev);
	kमुक्त(ptsc);

	serio_set_drvdata(serio, शून्य);
पूर्ण

अटल स्थिर काष्ठा serio_device_id tsc_serio_ids[] = अणु
	अणु
		.type   = SERIO_RS232,
		.proto  = SERIO_TSC40,
		.id     = SERIO_ANY,
		.extra  = SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(serio, tsc_serio_ids);

#घोषणा DRIVER_DESC    "TSC-10/25/40 serial touchscreen driver"

अटल काष्ठा serio_driver tsc_drv = अणु
	.driver	= अणु
		.name   = "tsc40",
	पूर्ण,
	.description    = DRIVER_DESC,
	.id_table	= tsc_serio_ids,
	.पूर्णांकerrupt      = tsc_पूर्णांकerrupt,
	.connect	= tsc_connect,
	.disconnect     = tsc_disconnect,
पूर्ण;

module_serio_driver(tsc_drv);

MODULE_AUTHOR("Sebastian Andrzej Siewior <bigeasy@linutronix.de>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");
