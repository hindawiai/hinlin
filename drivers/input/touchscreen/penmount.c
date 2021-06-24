<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Penmount serial touchscreen driver
 *
 * Copyright (c) 2006 Rick Koch <n1gp@hoपंचांगail.com>
 * Copyright (c) 2011 John Sung <penmount.touch@gmail.com>
 *
 * Based on ELO driver (drivers/input/touchscreen/elo.c)
 * Copyright (c) 2004 Vojtech Pavlik
 */


#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"PenMount serial touchscreen driver"

MODULE_AUTHOR("Rick Koch <n1gp@hotmail.com>");
MODULE_AUTHOR("John Sung <penmount.touch@gmail.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Definitions & global arrays.
 */

#घोषणा	PM_MAX_LENGTH	6
#घोषणा	PM_MAX_MTSLOT	16
#घोषणा	PM_3000_MTSLOT	2
#घोषणा	PM_6250_MTSLOT	12

/*
 * Multi-touch slot
 */

काष्ठा mt_slot अणु
	अचिन्हित लघु x, y;
	bool active; /* is the touch valid? */
पूर्ण;

/*
 * Per-touchscreen data.
 */

काष्ठा pm अणु
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	पूर्णांक idx;
	अचिन्हित अक्षर data[PM_MAX_LENGTH];
	अक्षर phys[32];
	अचिन्हित अक्षर packetsize;
	अचिन्हित अक्षर maxcontacts;
	काष्ठा mt_slot slots[PM_MAX_MTSLOT];
	व्योम (*parse_packet)(काष्ठा pm *);
पूर्ण;

/*
 * pm_mtevent() sends mt events and also emulates poपूर्णांकer movement
 */

अटल व्योम pm_mtevent(काष्ठा pm *pm, काष्ठा input_dev *input)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pm->maxcontacts; ++i) अणु
		input_mt_slot(input, i);
		input_mt_report_slot_state(input, MT_TOOL_FINGER,
				pm->slots[i].active);
		अगर (pm->slots[i].active) अणु
			input_event(input, EV_ABS, ABS_MT_POSITION_X, pm->slots[i].x);
			input_event(input, EV_ABS, ABS_MT_POSITION_Y, pm->slots[i].y);
		पूर्ण
	पूर्ण

	input_mt_report_poपूर्णांकer_emulation(input, true);
	input_sync(input);
पूर्ण

/*
 * pm_checkpacket() checks अगर data packet is valid
 */

अटल bool pm_checkpacket(अचिन्हित अक्षर *packet)
अणु
	पूर्णांक total = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++)
		total += packet[i];

	वापस packet[5] == (अचिन्हित अक्षर)~(total & 0xff);
पूर्ण

अटल व्योम pm_parse_9000(काष्ठा pm *pm)
अणु
	काष्ठा input_dev *dev = pm->dev;

	अगर ((pm->data[0] & 0x80) && pm->packetsize == ++pm->idx) अणु
		input_report_असल(dev, ABS_X, pm->data[1] * 128 + pm->data[2]);
		input_report_असल(dev, ABS_Y, pm->data[3] * 128 + pm->data[4]);
		input_report_key(dev, BTN_TOUCH, !!(pm->data[0] & 0x40));
		input_sync(dev);
		pm->idx = 0;
	पूर्ण
पूर्ण

अटल व्योम pm_parse_6000(काष्ठा pm *pm)
अणु
	काष्ठा input_dev *dev = pm->dev;

	अगर ((pm->data[0] & 0xbf) == 0x30 && pm->packetsize == ++pm->idx) अणु
		अगर (pm_checkpacket(pm->data)) अणु
			input_report_असल(dev, ABS_X,
					pm->data[2] * 256 + pm->data[1]);
			input_report_असल(dev, ABS_Y,
					pm->data[4] * 256 + pm->data[3]);
			input_report_key(dev, BTN_TOUCH, pm->data[0] & 0x40);
			input_sync(dev);
		पूर्ण
		pm->idx = 0;
	पूर्ण
पूर्ण

अटल व्योम pm_parse_3000(काष्ठा pm *pm)
अणु
	काष्ठा input_dev *dev = pm->dev;

	अगर ((pm->data[0] & 0xce) == 0x40 && pm->packetsize == ++pm->idx) अणु
		अगर (pm_checkpacket(pm->data)) अणु
			पूर्णांक slotnum = pm->data[0] & 0x0f;
			pm->slots[slotnum].active = pm->data[0] & 0x30;
			pm->slots[slotnum].x = pm->data[2] * 256 + pm->data[1];
			pm->slots[slotnum].y = pm->data[4] * 256 + pm->data[3];
			pm_mtevent(pm, dev);
		पूर्ण
		pm->idx = 0;
	पूर्ण
पूर्ण

अटल व्योम pm_parse_6250(काष्ठा pm *pm)
अणु
	काष्ठा input_dev *dev = pm->dev;

	अगर ((pm->data[0] & 0xb0) == 0x30 && pm->packetsize == ++pm->idx) अणु
		अगर (pm_checkpacket(pm->data)) अणु
			पूर्णांक slotnum = pm->data[0] & 0x0f;
			pm->slots[slotnum].active = pm->data[0] & 0x40;
			pm->slots[slotnum].x = pm->data[2] * 256 + pm->data[1];
			pm->slots[slotnum].y = pm->data[4] * 256 + pm->data[3];
			pm_mtevent(pm, dev);
		पूर्ण
		pm->idx = 0;
	पूर्ण
पूर्ण

अटल irqवापस_t pm_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा pm *pm = serio_get_drvdata(serio);

	pm->data[pm->idx] = data;

	pm->parse_packet(pm);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * pm_disconnect() is the opposite of pm_connect()
 */

अटल व्योम pm_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा pm *pm = serio_get_drvdata(serio);

	serio_बंद(serio);

	input_unरेजिस्टर_device(pm->dev);
	kमुक्त(pm);

	serio_set_drvdata(serio, शून्य);
पूर्ण

/*
 * pm_connect() is the routine that is called when someone adds a
 * new serio device that supports PenMount protocol and रेजिस्टरs it as
 * an input device.
 */

अटल पूर्णांक pm_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा pm *pm;
	काष्ठा input_dev *input_dev;
	पूर्णांक max_x, max_y;
	पूर्णांक err;

	pm = kzalloc(माप(काष्ठा pm), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!pm || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	pm->serio = serio;
	pm->dev = input_dev;
	snम_लिखो(pm->phys, माप(pm->phys), "%s/input0", serio->phys);
	pm->maxcontacts = 1;

	input_dev->name = "PenMount Serial TouchScreen";
	input_dev->phys = pm->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_PENMOUNT;
	input_dev->id.product = 0;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	चयन (serio->id.id) अणु
	शेष:
	हाल 0:
		pm->packetsize = 5;
		pm->parse_packet = pm_parse_9000;
		input_dev->id.product = 0x9000;
		max_x = max_y = 0x3ff;
		अवरोध;

	हाल 1:
		pm->packetsize = 6;
		pm->parse_packet = pm_parse_6000;
		input_dev->id.product = 0x6000;
		max_x = max_y = 0x3ff;
		अवरोध;

	हाल 2:
		pm->packetsize = 6;
		pm->parse_packet = pm_parse_3000;
		input_dev->id.product = 0x3000;
		max_x = max_y = 0x7ff;
		pm->maxcontacts = PM_3000_MTSLOT;
		अवरोध;

	हाल 3:
		pm->packetsize = 6;
		pm->parse_packet = pm_parse_6250;
		input_dev->id.product = 0x6250;
		max_x = max_y = 0x3ff;
		pm->maxcontacts = PM_6250_MTSLOT;
		अवरोध;
	पूर्ण

	input_set_असल_params(pm->dev, ABS_X, 0, max_x, 0, 0);
	input_set_असल_params(pm->dev, ABS_Y, 0, max_y, 0, 0);

	अगर (pm->maxcontacts > 1) अणु
		input_mt_init_slots(pm->dev, pm->maxcontacts, 0);
		input_set_असल_params(pm->dev,
				     ABS_MT_POSITION_X, 0, max_x, 0, 0);
		input_set_असल_params(pm->dev,
				     ABS_MT_POSITION_Y, 0, max_y, 0, 0);
	पूर्ण

	serio_set_drvdata(serio, pm);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(pm->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(pm);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id pm_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_PENMOUNT,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, pm_serio_ids);

अटल काष्ठा serio_driver pm_drv = अणु
	.driver		= अणु
		.name	= "serio-penmount",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= pm_serio_ids,
	.पूर्णांकerrupt	= pm_पूर्णांकerrupt,
	.connect	= pm_connect,
	.disconnect	= pm_disconnect,
पूर्ण;

module_serio_driver(pm_drv);
