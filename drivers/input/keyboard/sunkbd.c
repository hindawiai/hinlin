<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 */

/*
 * Sun keyboard driver क्रम Linux
 */

/*
 */

#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>
#समावेश <linux/workqueue.h>

#घोषणा DRIVER_DESC	"Sun keyboard driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

अटल अचिन्हित अक्षर sunkbd_keycode[128] = अणु
	  0,128,114,129,115, 59, 60, 68, 61, 87, 62, 88, 63,100, 64,112,
	 65, 66, 67, 56,103,119, 99, 70,105,130,131,108,106,  1,  2,  3,
	  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 41, 14,110,113, 98, 55,
	116,132, 83,133,102, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
	 26, 27,111,127, 71, 72, 73, 74,134,135,107,  0, 29, 30, 31, 32,
	 33, 34, 35, 36, 37, 38, 39, 40, 43, 28, 96, 75, 76, 77, 82,136,
	104,137, 69, 42, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,101,
	 79, 80, 81,  0,  0,  0,138, 58,125, 57,126,109, 86, 78
पूर्ण;

#घोषणा SUNKBD_CMD_RESET	0x1
#घोषणा SUNKBD_CMD_BELLON	0x2
#घोषणा SUNKBD_CMD_BELLOFF	0x3
#घोषणा SUNKBD_CMD_CLICK	0xa
#घोषणा SUNKBD_CMD_NOCLICK	0xb
#घोषणा SUNKBD_CMD_SETLED	0xe
#घोषणा SUNKBD_CMD_LAYOUT	0xf

#घोषणा SUNKBD_RET_RESET	0xff
#घोषणा SUNKBD_RET_ALLUP	0x7f
#घोषणा SUNKBD_RET_LAYOUT	0xfe

#घोषणा SUNKBD_LAYOUT_5_MASK	0x20
#घोषणा SUNKBD_RELEASE		0x80
#घोषणा SUNKBD_KEY		0x7f

/*
 * Per-keyboard data.
 */

काष्ठा sunkbd अणु
	अचिन्हित अक्षर keycode[ARRAY_SIZE(sunkbd_keycode)];
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	काष्ठा work_काष्ठा tq;
	रुको_queue_head_t रुको;
	अक्षर name[64];
	अक्षर phys[32];
	अक्षर type;
	bool enabled;
	अस्थिर s8 reset;
	अस्थिर s8 layout;
पूर्ण;

/*
 * sunkbd_पूर्णांकerrupt() is called by the low level driver when a अक्षरacter
 * is received.
 */

अटल irqवापस_t sunkbd_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sunkbd *sunkbd = serio_get_drvdata(serio);

	अगर (sunkbd->reset <= -1) अणु
		/*
		 * If cp[i] is 0xff, sunkbd->reset will stay -1.
		 * The keyboard sends 0xff 0xff 0xID on घातerup.
		 */
		sunkbd->reset = data;
		wake_up_पूर्णांकerruptible(&sunkbd->रुको);
		जाओ out;
	पूर्ण

	अगर (sunkbd->layout == -1) अणु
		sunkbd->layout = data;
		wake_up_पूर्णांकerruptible(&sunkbd->रुको);
		जाओ out;
	पूर्ण

	चयन (data) अणु

	हाल SUNKBD_RET_RESET:
		अगर (sunkbd->enabled)
			schedule_work(&sunkbd->tq);
		sunkbd->reset = -1;
		अवरोध;

	हाल SUNKBD_RET_LAYOUT:
		sunkbd->layout = -1;
		अवरोध;

	हाल SUNKBD_RET_ALLUP: /* All keys released */
		अवरोध;

	शेष:
		अगर (!sunkbd->enabled)
			अवरोध;

		अगर (sunkbd->keycode[data & SUNKBD_KEY]) अणु
			input_report_key(sunkbd->dev,
					 sunkbd->keycode[data & SUNKBD_KEY],
					 !(data & SUNKBD_RELEASE));
			input_sync(sunkbd->dev);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING
				"sunkbd.c: Unknown key (scancode %#x) %s.\n",
				data & SUNKBD_KEY,
				data & SUNKBD_RELEASE ? "released" : "pressed");
		पूर्ण
	पूर्ण
out:
	वापस IRQ_HANDLED;
पूर्ण

/*
 * sunkbd_event() handles events from the input module.
 */

अटल पूर्णांक sunkbd_event(काष्ठा input_dev *dev,
			अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा sunkbd *sunkbd = input_get_drvdata(dev);

	चयन (type) अणु

	हाल EV_LED:

		serio_ग_लिखो(sunkbd->serio, SUNKBD_CMD_SETLED);
		serio_ग_लिखो(sunkbd->serio,
			(!!test_bit(LED_CAPSL,   dev->led) << 3) |
			(!!test_bit(LED_SCROLLL, dev->led) << 2) |
			(!!test_bit(LED_COMPOSE, dev->led) << 1) |
			 !!test_bit(LED_NUML,    dev->led));
		वापस 0;

	हाल EV_SND:

		चयन (code) अणु

		हाल SND_CLICK:
			serio_ग_लिखो(sunkbd->serio, SUNKBD_CMD_NOCLICK - value);
			वापस 0;

		हाल SND_BELL:
			serio_ग_लिखो(sunkbd->serio, SUNKBD_CMD_BELLOFF - value);
			वापस 0;
		पूर्ण

		अवरोध;
	पूर्ण

	वापस -1;
पूर्ण

/*
 * sunkbd_initialize() checks क्रम a Sun keyboard attached, and determines
 * its type.
 */

अटल पूर्णांक sunkbd_initialize(काष्ठा sunkbd *sunkbd)
अणु
	sunkbd->reset = -2;
	serio_ग_लिखो(sunkbd->serio, SUNKBD_CMD_RESET);
	रुको_event_पूर्णांकerruptible_समयout(sunkbd->रुको, sunkbd->reset >= 0, HZ);
	अगर (sunkbd->reset < 0)
		वापस -1;

	sunkbd->type = sunkbd->reset;

	अगर (sunkbd->type == 4) अणु	/* Type 4 keyboard */
		sunkbd->layout = -2;
		serio_ग_लिखो(sunkbd->serio, SUNKBD_CMD_LAYOUT);
		रुको_event_पूर्णांकerruptible_समयout(sunkbd->रुको,
						 sunkbd->layout >= 0, HZ / 4);
		अगर (sunkbd->layout < 0)
			वापस -1;
		अगर (sunkbd->layout & SUNKBD_LAYOUT_5_MASK)
			sunkbd->type = 5;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * sunkbd_set_leds_beeps() sets leds and beeps to a state the computer remembers
 * they were in.
 */

अटल व्योम sunkbd_set_leds_beeps(काष्ठा sunkbd *sunkbd)
अणु
	serio_ग_लिखो(sunkbd->serio, SUNKBD_CMD_SETLED);
	serio_ग_लिखो(sunkbd->serio,
		(!!test_bit(LED_CAPSL,   sunkbd->dev->led) << 3) |
		(!!test_bit(LED_SCROLLL, sunkbd->dev->led) << 2) |
		(!!test_bit(LED_COMPOSE, sunkbd->dev->led) << 1) |
		 !!test_bit(LED_NUML,    sunkbd->dev->led));
	serio_ग_लिखो(sunkbd->serio,
		SUNKBD_CMD_NOCLICK - !!test_bit(SND_CLICK, sunkbd->dev->snd));
	serio_ग_लिखो(sunkbd->serio,
		SUNKBD_CMD_BELLOFF - !!test_bit(SND_BELL, sunkbd->dev->snd));
पूर्ण


/*
 * sunkbd_reinit() रुको क्रम the keyboard reset to complete and restores state
 * of leds and beeps.
 */

अटल व्योम sunkbd_reinit(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sunkbd *sunkbd = container_of(work, काष्ठा sunkbd, tq);

	/*
	 * It is OK that we check sunkbd->enabled without pausing serio,
	 * as we only want to catch true->false transition that will
	 * happen once and we will be woken up क्रम it.
	 */
	रुको_event_पूर्णांकerruptible_समयout(sunkbd->रुको,
					 sunkbd->reset >= 0 || !sunkbd->enabled,
					 HZ);

	अगर (sunkbd->reset >= 0 && sunkbd->enabled)
		sunkbd_set_leds_beeps(sunkbd);
पूर्ण

अटल व्योम sunkbd_enable(काष्ठा sunkbd *sunkbd, bool enable)
अणु
	serio_छोड़ो_rx(sunkbd->serio);
	sunkbd->enabled = enable;
	serio_जारी_rx(sunkbd->serio);

	अगर (!enable) अणु
		wake_up_पूर्णांकerruptible(&sunkbd->रुको);
		cancel_work_sync(&sunkbd->tq);
	पूर्ण
पूर्ण

/*
 * sunkbd_connect() probes क्रम a Sun keyboard and fills the necessary
 * काष्ठाures.
 */

अटल पूर्णांक sunkbd_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा sunkbd *sunkbd;
	काष्ठा input_dev *input_dev;
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;

	sunkbd = kzalloc(माप(काष्ठा sunkbd), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!sunkbd || !input_dev)
		जाओ fail1;

	sunkbd->serio = serio;
	sunkbd->dev = input_dev;
	init_रुकोqueue_head(&sunkbd->रुको);
	INIT_WORK(&sunkbd->tq, sunkbd_reinit);
	snम_लिखो(sunkbd->phys, माप(sunkbd->phys), "%s/input0", serio->phys);

	serio_set_drvdata(serio, sunkbd);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	अगर (sunkbd_initialize(sunkbd) < 0) अणु
		err = -ENODEV;
		जाओ fail3;
	पूर्ण

	snम_लिखो(sunkbd->name, माप(sunkbd->name),
		 "Sun Type %d keyboard", sunkbd->type);
	स_नकल(sunkbd->keycode, sunkbd_keycode, माप(sunkbd->keycode));

	input_dev->name = sunkbd->name;
	input_dev->phys = sunkbd->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr  = SERIO_SUNKBD;
	input_dev->id.product = sunkbd->type;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_set_drvdata(input_dev, sunkbd);

	input_dev->event = sunkbd_event;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_LED) |
		BIT_MASK(EV_SND) | BIT_MASK(EV_REP);
	input_dev->ledbit[0] = BIT_MASK(LED_CAPSL) | BIT_MASK(LED_COMPOSE) |
		BIT_MASK(LED_SCROLLL) | BIT_MASK(LED_NUML);
	input_dev->sndbit[0] = BIT_MASK(SND_CLICK) | BIT_MASK(SND_BELL);

	input_dev->keycode = sunkbd->keycode;
	input_dev->keycodesize = माप(अचिन्हित अक्षर);
	input_dev->keycodemax = ARRAY_SIZE(sunkbd_keycode);
	क्रम (i = 0; i < ARRAY_SIZE(sunkbd_keycode); i++)
		__set_bit(sunkbd->keycode[i], input_dev->keybit);
	__clear_bit(KEY_RESERVED, input_dev->keybit);

	sunkbd_enable(sunkbd, true);

	err = input_रेजिस्टर_device(sunkbd->dev);
	अगर (err)
		जाओ fail4;

	वापस 0;

 fail4:	sunkbd_enable(sunkbd, false);
 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(sunkbd);
	वापस err;
पूर्ण

/*
 * sunkbd_disconnect() unरेजिस्टरs and बंदs behind us.
 */

अटल व्योम sunkbd_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा sunkbd *sunkbd = serio_get_drvdata(serio);

	sunkbd_enable(sunkbd, false);
	input_unरेजिस्टर_device(sunkbd->dev);
	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	kमुक्त(sunkbd);
पूर्ण

अटल स्थिर काष्ठा serio_device_id sunkbd_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_SUNKBD,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_UNKNOWN, /* sunkbd करोes probe */
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, sunkbd_serio_ids);

अटल काष्ठा serio_driver sunkbd_drv = अणु
	.driver		= अणु
		.name	= "sunkbd",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= sunkbd_serio_ids,
	.पूर्णांकerrupt	= sunkbd_पूर्णांकerrupt,
	.connect	= sunkbd_connect,
	.disconnect	= sunkbd_disconnect,
पूर्ण;

module_serio_driver(sunkbd_drv);
