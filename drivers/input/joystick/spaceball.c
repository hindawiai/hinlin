<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 *
 *  Based on the work of:
 *	David Thompson
 *	Joseph Krahn
 */

/*
 * SpaceTec SpaceBall 2003/3003/4000 FLX driver क्रम Linux
 */

/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"SpaceTec SpaceBall 2003/3003/4000 FLX driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Constants.
 */

#घोषणा SPACEBALL_MAX_LENGTH	128
#घोषणा SPACEBALL_MAX_ID	9

#घोषणा SPACEBALL_1003      1
#घोषणा SPACEBALL_2003B     3
#घोषणा SPACEBALL_2003C     4
#घोषणा SPACEBALL_3003C     7
#घोषणा SPACEBALL_4000FLX   8
#घोषणा SPACEBALL_4000FLX_L 9

अटल पूर्णांक spaceball_axes[] = अणु ABS_X, ABS_Z, ABS_Y, ABS_RX, ABS_RZ, ABS_RY पूर्ण;
अटल अक्षर *spaceball_names[] = अणु
	"?", "SpaceTec SpaceBall 1003", "SpaceTec SpaceBall 2003", "SpaceTec SpaceBall 2003B",
	"SpaceTec SpaceBall 2003C", "SpaceTec SpaceBall 3003", "SpaceTec SpaceBall SpaceController",
	"SpaceTec SpaceBall 3003C", "SpaceTec SpaceBall 4000FLX", "SpaceTec SpaceBall 4000FLX Lefty" पूर्ण;

/*
 * Per-Ball data.
 */

काष्ठा spaceball अणु
	काष्ठा input_dev *dev;
	पूर्णांक idx;
	पूर्णांक escape;
	अचिन्हित अक्षर data[SPACEBALL_MAX_LENGTH];
	अक्षर phys[32];
पूर्ण;

/*
 * spaceball_process_packet() decodes packets the driver receives from the
 * SpaceBall.
 */

अटल व्योम spaceball_process_packet(काष्ठा spaceball* spaceball)
अणु
	काष्ठा input_dev *dev = spaceball->dev;
	अचिन्हित अक्षर *data = spaceball->data;
	पूर्णांक i;

	अगर (spaceball->idx < 2) वापस;

	चयन (spaceball->data[0]) अणु

		हाल 'D':					/* Ball data */
			अगर (spaceball->idx != 15) वापस;
			क्रम (i = 0; i < 6; i++)
				input_report_असल(dev, spaceball_axes[i],
					(__s16)((data[2 * i + 3] << 8) | data[2 * i + 2]));
			अवरोध;

		हाल 'K':					/* Button data */
			अगर (spaceball->idx != 3) वापस;
			input_report_key(dev, BTN_1, (data[2] & 0x01) || (data[2] & 0x20));
			input_report_key(dev, BTN_2, data[2] & 0x02);
			input_report_key(dev, BTN_3, data[2] & 0x04);
			input_report_key(dev, BTN_4, data[2] & 0x08);
			input_report_key(dev, BTN_5, data[1] & 0x01);
			input_report_key(dev, BTN_6, data[1] & 0x02);
			input_report_key(dev, BTN_7, data[1] & 0x04);
			input_report_key(dev, BTN_8, data[1] & 0x10);
			अवरोध;

		हाल '.':					/* Advanced button data */
			अगर (spaceball->idx != 3) वापस;
			input_report_key(dev, BTN_1, data[2] & 0x01);
			input_report_key(dev, BTN_2, data[2] & 0x02);
			input_report_key(dev, BTN_3, data[2] & 0x04);
			input_report_key(dev, BTN_4, data[2] & 0x08);
			input_report_key(dev, BTN_5, data[2] & 0x10);
			input_report_key(dev, BTN_6, data[2] & 0x20);
			input_report_key(dev, BTN_7, data[2] & 0x80);
			input_report_key(dev, BTN_8, data[1] & 0x01);
			input_report_key(dev, BTN_9, data[1] & 0x02);
			input_report_key(dev, BTN_A, data[1] & 0x04);
			input_report_key(dev, BTN_B, data[1] & 0x08);
			input_report_key(dev, BTN_C, data[1] & 0x10);
			input_report_key(dev, BTN_MODE, data[1] & 0x20);
			अवरोध;

		हाल 'E':					/* Device error */
			spaceball->data[spaceball->idx - 1] = 0;
			prपूर्णांकk(KERN_ERR "spaceball: Device error. [%s]\n", spaceball->data + 1);
			अवरोध;

		हाल '?':					/* Bad command packet */
			spaceball->data[spaceball->idx - 1] = 0;
			prपूर्णांकk(KERN_ERR "spaceball: Bad command. [%s]\n", spaceball->data + 1);
			अवरोध;
	पूर्ण

	input_sync(dev);
पूर्ण

/*
 * Spaceball 4000 FLX packets all start with a one letter packet-type decriptor,
 * and end in 0x0d. It uses '^' as an escape क्रम CR, XOFF and XON अक्षरacters which
 * can occur in the axis values.
 */

अटल irqवापस_t spaceball_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा spaceball *spaceball = serio_get_drvdata(serio);

	चयन (data) अणु
		हाल 0xd:
			spaceball_process_packet(spaceball);
			spaceball->idx = 0;
			spaceball->escape = 0;
			अवरोध;
		हाल '^':
			अगर (!spaceball->escape) अणु
				spaceball->escape = 1;
				अवरोध;
			पूर्ण
			spaceball->escape = 0;
			fallthrough;
		हाल 'M':
		हाल 'Q':
		हाल 'S':
			अगर (spaceball->escape) अणु
				spaceball->escape = 0;
				data &= 0x1f;
			पूर्ण
			fallthrough;
		शेष:
			अगर (spaceball->escape)
				spaceball->escape = 0;
			अगर (spaceball->idx < SPACEBALL_MAX_LENGTH)
				spaceball->data[spaceball->idx++] = data;
			अवरोध;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/*
 * spaceball_disconnect() is the opposite of spaceball_connect()
 */

अटल व्योम spaceball_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा spaceball* spaceball = serio_get_drvdata(serio);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_unरेजिस्टर_device(spaceball->dev);
	kमुक्त(spaceball);
पूर्ण

/*
 * spaceball_connect() is the routine that is called when someone adds a
 * new serio device that supports Spaceball protocol and रेजिस्टरs it as
 * an input device.
 */

अटल पूर्णांक spaceball_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा spaceball *spaceball;
	काष्ठा input_dev *input_dev;
	पूर्णांक err = -ENOMEM;
	पूर्णांक i, id;

	अगर ((id = serio->id.id) > SPACEBALL_MAX_ID)
		वापस -ENODEV;

	spaceball = kदो_स्मृति(माप(काष्ठा spaceball), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!spaceball || !input_dev)
		जाओ fail1;

	spaceball->dev = input_dev;
	snम_लिखो(spaceball->phys, माप(spaceball->phys), "%s/input0", serio->phys);

	input_dev->name = spaceball_names[id];
	input_dev->phys = spaceball->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_SPACEBALL;
	input_dev->id.product = id;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	चयन (id) अणु
		हाल SPACEBALL_4000FLX:
		हाल SPACEBALL_4000FLX_L:
			input_dev->keybit[BIT_WORD(BTN_0)] |= BIT_MASK(BTN_9);
			input_dev->keybit[BIT_WORD(BTN_A)] |= BIT_MASK(BTN_A) |
				BIT_MASK(BTN_B) | BIT_MASK(BTN_C) |
				BIT_MASK(BTN_MODE);
			fallthrough;
		शेष:
			input_dev->keybit[BIT_WORD(BTN_0)] |= BIT_MASK(BTN_2) |
				BIT_MASK(BTN_3) | BIT_MASK(BTN_4) |
				BIT_MASK(BTN_5) | BIT_MASK(BTN_6) |
				BIT_MASK(BTN_7) | BIT_MASK(BTN_8);
			fallthrough;
		हाल SPACEBALL_3003C:
			input_dev->keybit[BIT_WORD(BTN_0)] |= BIT_MASK(BTN_1) |
				BIT_MASK(BTN_8);
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		input_set_असल_params(input_dev, ABS_X + i, -8000, 8000, 8, 40);
		input_set_असल_params(input_dev, ABS_RX + i, -1600, 1600, 2, 8);
	पूर्ण

	serio_set_drvdata(serio, spaceball);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(spaceball->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(spaceball);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id spaceball_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_SPACEBALL,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, spaceball_serio_ids);

अटल काष्ठा serio_driver spaceball_drv = अणु
	.driver		= अणु
		.name	= "spaceball",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= spaceball_serio_ids,
	.पूर्णांकerrupt	= spaceball_पूर्णांकerrupt,
	.connect	= spaceball_connect,
	.disconnect	= spaceball_disconnect,
पूर्ण;

module_serio_driver(spaceball_drv);
