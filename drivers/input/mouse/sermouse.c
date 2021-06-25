<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 */

/*
 *  Serial mouse driver क्रम Linux
 */

/*
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"Serial mouse driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

अटल स्थिर अक्षर *sermouse_protocols[] = अणु "None", "Mouse Systems Mouse", "Sun Mouse", "Microsoft Mouse",
					"Logitech M+ Mouse", "Microsoft MZ Mouse", "Logitech MZ+ Mouse",
					"Logitech MZ++ Mouse"पूर्ण;

काष्ठा sermouse अणु
	काष्ठा input_dev *dev;
	चिन्हित अक्षर buf[8];
	अचिन्हित अक्षर count;
	अचिन्हित अक्षर type;
	अचिन्हित दीर्घ last;
	अक्षर phys[32];
पूर्ण;

/*
 * sermouse_process_msc() analyzes the incoming MSC/Sun bytestream and
 * applies some prediction to the data, resulting in 96 updates per
 * second, which is as good as a PS/2 or USB mouse.
 */

अटल व्योम sermouse_process_msc(काष्ठा sermouse *sermouse, चिन्हित अक्षर data)
अणु
	काष्ठा input_dev *dev = sermouse->dev;
	चिन्हित अक्षर *buf = sermouse->buf;

	चयन (sermouse->count) अणु

		हाल 0:
			अगर ((data & 0xf8) != 0x80)
				वापस;
			input_report_key(dev, BTN_LEFT,   !(data & 4));
			input_report_key(dev, BTN_RIGHT,  !(data & 1));
			input_report_key(dev, BTN_MIDDLE, !(data & 2));
			अवरोध;

		हाल 1:
		हाल 3:
			input_report_rel(dev, REL_X, data / 2);
			input_report_rel(dev, REL_Y, -buf[1]);
			buf[0] = data - data / 2;
			अवरोध;

		हाल 2:
		हाल 4:
			input_report_rel(dev, REL_X, buf[0]);
			input_report_rel(dev, REL_Y, buf[1] - data);
			buf[1] = data / 2;
			अवरोध;
	पूर्ण

	input_sync(dev);

	अगर (++sermouse->count == 5)
		sermouse->count = 0;
पूर्ण

/*
 * sermouse_process_ms() anlyzes the incoming MS(Z/+/++) bytestream and
 * generates events. With prediction it माला_लो 80 updates/sec, assuming
 * standard 3-byte packets and 1200 bps.
 */

अटल व्योम sermouse_process_ms(काष्ठा sermouse *sermouse, चिन्हित अक्षर data)
अणु
	काष्ठा input_dev *dev = sermouse->dev;
	चिन्हित अक्षर *buf = sermouse->buf;

	अगर (data & 0x40)
		sermouse->count = 0;
	अन्यथा अगर (sermouse->count == 0)
		वापस;

	चयन (sermouse->count) अणु

		हाल 0:
			buf[1] = data;
			input_report_key(dev, BTN_LEFT,   (data >> 5) & 1);
			input_report_key(dev, BTN_RIGHT,  (data >> 4) & 1);
			अवरोध;

		हाल 1:
			buf[2] = data;
			data = (चिन्हित अक्षर) (((buf[1] << 6) & 0xc0) | (data & 0x3f));
			input_report_rel(dev, REL_X, data / 2);
			input_report_rel(dev, REL_Y, buf[4]);
			buf[3] = data - data / 2;
			अवरोध;

		हाल 2:
			/* Guessing the state of the middle button on 3-button MS-protocol mice - ugly. */
			अगर ((sermouse->type == SERIO_MS) && !data && !buf[2] && !((buf[0] & 0xf0) ^ buf[1]))
				input_report_key(dev, BTN_MIDDLE, !test_bit(BTN_MIDDLE, dev->key));
			buf[0] = buf[1];

			data = (चिन्हित अक्षर) (((buf[1] << 4) & 0xc0) | (data & 0x3f));
			input_report_rel(dev, REL_X, buf[3]);
			input_report_rel(dev, REL_Y, data - buf[4]);
			buf[4] = data / 2;
			अवरोध;

		हाल 3:

			चयन (sermouse->type) अणु

				हाल SERIO_MS:
					sermouse->type = SERIO_MP;
					fallthrough;

				हाल SERIO_MP:
					अगर ((data >> 2) & 3) अवरोध;	/* M++ Wireless Extension packet. */
					input_report_key(dev, BTN_MIDDLE, (data >> 5) & 1);
					input_report_key(dev, BTN_SIDE,   (data >> 4) & 1);
					अवरोध;

				हाल SERIO_MZP:
				हाल SERIO_MZPP:
					input_report_key(dev, BTN_SIDE,   (data >> 5) & 1);
					fallthrough;

				हाल SERIO_MZ:
					input_report_key(dev, BTN_MIDDLE, (data >> 4) & 1);
					input_report_rel(dev, REL_WHEEL,  (data & 8) - (data & 7));
					अवरोध;
			पूर्ण

			अवरोध;

		हाल 4:
		हाल 6:	/* MZ++ packet type. We can get these bytes क्रम M++ too but we ignore them later. */
			buf[1] = (data >> 2) & 0x0f;
			अवरोध;

		हाल 5:
		हाल 7: /* Ignore anything besides MZ++ */
			अगर (sermouse->type != SERIO_MZPP)
				अवरोध;

			चयन (buf[1]) अणु

				हाल 1: /* Extra mouse info */

					input_report_key(dev, BTN_SIDE, (data >> 4) & 1);
					input_report_key(dev, BTN_EXTRA, (data >> 5) & 1);
					input_report_rel(dev, data & 0x80 ? REL_HWHEEL : REL_WHEEL, (data & 7) - (data & 8));

					अवरोध;

				शेष: /* We करोn't decode anything अन्यथा yet. */

					prपूर्णांकk(KERN_WARNING
						"sermouse.c: Received MZ++ packet %x, don't know how to handle.\n", buf[1]);
					अवरोध;
			पूर्ण

			अवरोध;
	पूर्ण

	input_sync(dev);

	sermouse->count++;
पूर्ण

/*
 * sermouse_पूर्णांकerrupt() handles incoming अक्षरacters, either gathering them पूर्णांकo
 * packets or passing them to the command routine as command output.
 */

अटल irqवापस_t sermouse_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sermouse *sermouse = serio_get_drvdata(serio);

	अगर (समय_after(jअगरfies, sermouse->last + HZ/10))
		sermouse->count = 0;

	sermouse->last = jअगरfies;

	अगर (sermouse->type > SERIO_SUN)
		sermouse_process_ms(sermouse, data);
	अन्यथा
		sermouse_process_msc(sermouse, data);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * sermouse_disconnect() cleans up after we करोn't want talk
 * to the mouse anymore.
 */

अटल व्योम sermouse_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा sermouse *sermouse = serio_get_drvdata(serio);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_unरेजिस्टर_device(sermouse->dev);
	kमुक्त(sermouse);
पूर्ण

/*
 * sermouse_connect() is a callback क्रमm the serio module when
 * an unhandled serio port is found.
 */

अटल पूर्णांक sermouse_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा sermouse *sermouse;
	काष्ठा input_dev *input_dev;
	अचिन्हित अक्षर c = serio->id.extra;
	पूर्णांक err = -ENOMEM;

	sermouse = kzalloc(माप(काष्ठा sermouse), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!sermouse || !input_dev)
		जाओ fail1;

	sermouse->dev = input_dev;
	snम_लिखो(sermouse->phys, माप(sermouse->phys), "%s/input0", serio->phys);
	sermouse->type = serio->id.proto;

	input_dev->name = sermouse_protocols[sermouse->type];
	input_dev->phys = sermouse->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr  = sermouse->type;
	input_dev->id.product = c;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);
	input_dev->keybit[BIT_WORD(BTN_MOUSE)] = BIT_MASK(BTN_LEFT) |
		BIT_MASK(BTN_RIGHT);
	input_dev->relbit[0] = BIT_MASK(REL_X) | BIT_MASK(REL_Y);

	अगर (c & 0x01) set_bit(BTN_MIDDLE, input_dev->keybit);
	अगर (c & 0x02) set_bit(BTN_SIDE, input_dev->keybit);
	अगर (c & 0x04) set_bit(BTN_EXTRA, input_dev->keybit);
	अगर (c & 0x10) set_bit(REL_WHEEL, input_dev->relbit);
	अगर (c & 0x20) set_bit(REL_HWHEEL, input_dev->relbit);

	serio_set_drvdata(serio, sermouse);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(sermouse->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(sermouse);
	वापस err;
पूर्ण

अटल काष्ठा serio_device_id sermouse_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_MSC,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_SUN,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_MS,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_MP,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_MZ,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_MZP,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_MZPP,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, sermouse_serio_ids);

अटल काष्ठा serio_driver sermouse_drv = अणु
	.driver		= अणु
		.name	= "sermouse",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= sermouse_serio_ids,
	.पूर्णांकerrupt	= sermouse_पूर्णांकerrupt,
	.connect	= sermouse_connect,
	.disconnect	= sermouse_disconnect,
पूर्ण;

module_serio_driver(sermouse_drv);
