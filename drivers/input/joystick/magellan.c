<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 */

/*
 * Magellan and Space Mouse 6करोf controller driver क्रम Linux
 */

/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"Magellan and SpaceMouse 6dof controller driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Definitions & global arrays.
 */

#घोषणा	MAGELLAN_MAX_LENGTH	32

अटल पूर्णांक magellan_buttons[] = अणु BTN_0, BTN_1, BTN_2, BTN_3, BTN_4, BTN_5, BTN_6, BTN_7, BTN_8 पूर्ण;
अटल पूर्णांक magellan_axes[] = अणु ABS_X, ABS_Y, ABS_Z, ABS_RX, ABS_RY, ABS_RZ पूर्ण;

/*
 * Per-Magellan data.
 */

काष्ठा magellan अणु
	काष्ठा input_dev *dev;
	पूर्णांक idx;
	अचिन्हित अक्षर data[MAGELLAN_MAX_LENGTH];
	अक्षर phys[32];
पूर्ण;

/*
 * magellan_crunch_nibbles() verअगरies that the bytes sent from the Magellan
 * have correct upper nibbles क्रम the lower ones, अगर not, the packet will
 * be thrown away. It also strips these upper halves to simplअगरy further
 * processing.
 */

अटल पूर्णांक magellan_crunch_nibbles(अचिन्हित अक्षर *data, पूर्णांक count)
अणु
	अटल अचिन्हित अक्षर nibbles[16] = "0AB3D56GH9:K<MN?";

	करो अणु
		अगर (data[count] == nibbles[data[count] & 0xf])
			data[count] = data[count] & 0xf;
		अन्यथा
			वापस -1;
	पूर्ण जबतक (--count);

	वापस 0;
पूर्ण

अटल व्योम magellan_process_packet(काष्ठा magellan* magellan)
अणु
	काष्ठा input_dev *dev = magellan->dev;
	अचिन्हित अक्षर *data = magellan->data;
	पूर्णांक i, t;

	अगर (!magellan->idx) वापस;

	चयन (magellan->data[0]) अणु

		हाल 'd':				/* Axis data */
			अगर (magellan->idx != 25) वापस;
			अगर (magellan_crunch_nibbles(data, 24)) वापस;
			क्रम (i = 0; i < 6; i++)
				input_report_असल(dev, magellan_axes[i],
					(data[(i << 2) + 1] << 12 | data[(i << 2) + 2] << 8 |
					 data[(i << 2) + 3] <<  4 | data[(i << 2) + 4]) - 32768);
			अवरोध;

		हाल 'k':				/* Button data */
			अगर (magellan->idx != 4) वापस;
			अगर (magellan_crunch_nibbles(data, 3)) वापस;
			t = (data[1] << 1) | (data[2] << 5) | data[3];
			क्रम (i = 0; i < 9; i++) input_report_key(dev, magellan_buttons[i], (t >> i) & 1);
			अवरोध;
	पूर्ण

	input_sync(dev);
पूर्ण

अटल irqवापस_t magellan_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा magellan* magellan = serio_get_drvdata(serio);

	अगर (data == '\r') अणु
		magellan_process_packet(magellan);
		magellan->idx = 0;
	पूर्ण अन्यथा अणु
		अगर (magellan->idx < MAGELLAN_MAX_LENGTH)
			magellan->data[magellan->idx++] = data;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/*
 * magellan_disconnect() is the opposite of magellan_connect()
 */

अटल व्योम magellan_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा magellan* magellan = serio_get_drvdata(serio);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_unरेजिस्टर_device(magellan->dev);
	kमुक्त(magellan);
पूर्ण

/*
 * magellan_connect() is the routine that is called when someone adds a
 * new serio device that supports Magellan protocol and रेजिस्टरs it as
 * an input device.
 */

अटल पूर्णांक magellan_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा magellan *magellan;
	काष्ठा input_dev *input_dev;
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;

	magellan = kzalloc(माप(काष्ठा magellan), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!magellan || !input_dev)
		जाओ fail1;

	magellan->dev = input_dev;
	snम_लिखो(magellan->phys, माप(magellan->phys), "%s/input0", serio->phys);

	input_dev->name = "LogiCad3D Magellan / SpaceMouse";
	input_dev->phys = magellan->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_MAGELLAN;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	क्रम (i = 0; i < 9; i++)
		set_bit(magellan_buttons[i], input_dev->keybit);

	क्रम (i = 0; i < 6; i++)
		input_set_असल_params(input_dev, magellan_axes[i], -360, 360, 0, 0);

	serio_set_drvdata(serio, magellan);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(magellan->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(magellan);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id magellan_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_MAGELLAN,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, magellan_serio_ids);

अटल काष्ठा serio_driver magellan_drv = अणु
	.driver		= अणु
		.name	= "magellan",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= magellan_serio_ids,
	.पूर्णांकerrupt	= magellan_पूर्णांकerrupt,
	.connect	= magellan_connect,
	.disconnect	= magellan_disconnect,
पूर्ण;

module_serio_driver(magellan_drv);
