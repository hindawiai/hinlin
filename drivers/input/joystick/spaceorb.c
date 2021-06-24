<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 *
 *  Based on the work of:
 *	David Thompson
 */

/*
 * SpaceTec SpaceOrb 360 and Avenger 6करोf controller driver क्रम Linux
 */

/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"SpaceTec SpaceOrb 360 and Avenger 6dof controller driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Constants.
 */

#घोषणा SPACEORB_MAX_LENGTH	64

अटल पूर्णांक spaceorb_buttons[] = अणु BTN_TL, BTN_TR, BTN_Y, BTN_X, BTN_B, BTN_A पूर्ण;
अटल पूर्णांक spaceorb_axes[] = अणु ABS_X, ABS_Y, ABS_Z, ABS_RX, ABS_RY, ABS_RZ पूर्ण;

/*
 * Per-Orb data.
 */

काष्ठा spaceorb अणु
	काष्ठा input_dev *dev;
	पूर्णांक idx;
	अचिन्हित अक्षर data[SPACEORB_MAX_LENGTH];
	अक्षर phys[32];
पूर्ण;

अटल अचिन्हित अक्षर spaceorb_xor[] = "SpaceWare";

अटल अचिन्हित अक्षर *spaceorb_errors[] = अणु "EEPROM storing 0 failed", "Receive queue overflow", "Transmit queue timeout",
		"Bad packet", "Power brown-out", "EEPROM checksum error", "Hardware fault" पूर्ण;

/*
 * spaceorb_process_packet() decodes packets the driver receives from the
 * SpaceOrb.
 */

अटल व्योम spaceorb_process_packet(काष्ठा spaceorb *spaceorb)
अणु
	काष्ठा input_dev *dev = spaceorb->dev;
	अचिन्हित अक्षर *data = spaceorb->data;
	अचिन्हित अक्षर c = 0;
	पूर्णांक axes[6];
	पूर्णांक i;

	अगर (spaceorb->idx < 2) वापस;
	क्रम (i = 0; i < spaceorb->idx; i++) c ^= data[i];
	अगर (c) वापस;

	चयन (data[0]) अणु

		हाल 'R':				/* Reset packet */
			spaceorb->data[spaceorb->idx - 1] = 0;
			क्रम (i = 1; i < spaceorb->idx && spaceorb->data[i] == ' '; i++);
			prपूर्णांकk(KERN_INFO "input: %s [%s] is %s\n",
				 dev->name, spaceorb->data + i, spaceorb->phys);
			अवरोध;

		हाल 'D':				/* Ball + button data */
			अगर (spaceorb->idx != 12) वापस;
			क्रम (i = 0; i < 9; i++) spaceorb->data[i+2] ^= spaceorb_xor[i];
			axes[0] = ( data[2]	 << 3) | (data[ 3] >> 4);
			axes[1] = ((data[3] & 0x0f) << 6) | (data[ 4] >> 1);
			axes[2] = ((data[4] & 0x01) << 9) | (data[ 5] << 2) | (data[4] >> 5);
			axes[3] = ((data[6] & 0x1f) << 5) | (data[ 7] >> 2);
			axes[4] = ((data[7] & 0x03) << 8) | (data[ 8] << 1) | (data[7] >> 6);
			axes[5] = ((data[9] & 0x3f) << 4) | (data[10] >> 3);
			क्रम (i = 0; i < 6; i++)
				input_report_असल(dev, spaceorb_axes[i], axes[i] - ((axes[i] & 0x200) ? 1024 : 0));
			क्रम (i = 0; i < 6; i++)
				input_report_key(dev, spaceorb_buttons[i], (data[1] >> i) & 1);
			अवरोध;

		हाल 'K':				/* Button data */
			अगर (spaceorb->idx != 5) वापस;
			क्रम (i = 0; i < 6; i++)
				input_report_key(dev, spaceorb_buttons[i], (data[2] >> i) & 1);

			अवरोध;

		हाल 'E':				/* Error packet */
			अगर (spaceorb->idx != 4) वापस;
			prपूर्णांकk(KERN_ERR "spaceorb: Device error. [ ");
			क्रम (i = 0; i < 7; i++) अगर (data[1] & (1 << i)) prपूर्णांकk("%s ", spaceorb_errors[i]);
			prपूर्णांकk("]\n");
			अवरोध;
	पूर्ण

	input_sync(dev);
पूर्ण

अटल irqवापस_t spaceorb_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा spaceorb* spaceorb = serio_get_drvdata(serio);

	अगर (~data & 0x80) अणु
		अगर (spaceorb->idx) spaceorb_process_packet(spaceorb);
		spaceorb->idx = 0;
	पूर्ण
	अगर (spaceorb->idx < SPACEORB_MAX_LENGTH)
		spaceorb->data[spaceorb->idx++] = data & 0x7f;
	वापस IRQ_HANDLED;
पूर्ण

/*
 * spaceorb_disconnect() is the opposite of spaceorb_connect()
 */

अटल व्योम spaceorb_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा spaceorb* spaceorb = serio_get_drvdata(serio);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_unरेजिस्टर_device(spaceorb->dev);
	kमुक्त(spaceorb);
पूर्ण

/*
 * spaceorb_connect() is the routine that is called when someone adds a
 * new serio device that supports SpaceOrb/Avenger protocol and रेजिस्टरs
 * it as an input device.
 */

अटल पूर्णांक spaceorb_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा spaceorb *spaceorb;
	काष्ठा input_dev *input_dev;
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;

	spaceorb = kzalloc(माप(काष्ठा spaceorb), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!spaceorb || !input_dev)
		जाओ fail1;

	spaceorb->dev = input_dev;
	snम_लिखो(spaceorb->phys, माप(spaceorb->phys), "%s/input0", serio->phys);

	input_dev->name = "SpaceTec SpaceOrb 360 / Avenger";
	input_dev->phys = spaceorb->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_SPACEORB;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	क्रम (i = 0; i < 6; i++)
		set_bit(spaceorb_buttons[i], input_dev->keybit);

	क्रम (i = 0; i < 6; i++)
		input_set_असल_params(input_dev, spaceorb_axes[i], -508, 508, 0, 0);

	serio_set_drvdata(serio, spaceorb);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(spaceorb->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(spaceorb);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id spaceorb_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_SPACEORB,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, spaceorb_serio_ids);

अटल काष्ठा serio_driver spaceorb_drv = अणु
	.driver		= अणु
		.name	= "spaceorb",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= spaceorb_serio_ids,
	.पूर्णांकerrupt	= spaceorb_पूर्णांकerrupt,
	.connect	= spaceorb_connect,
	.disconnect	= spaceorb_disconnect,
पूर्ण;

module_serio_driver(spaceorb_drv);
