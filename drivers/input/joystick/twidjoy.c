<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2001 Arndt Schoenewald
 *  Copyright (c) 2000-2001 Vojtech Pavlik
 *  Copyright (c) 2000 Mark Fletcher
 *
 *  Sponsored by Quelltext AG (http://www.quelltext-ag.de), Dorपंचांगund, Germany
 */

/*
 * Driver to use Handykey's Twiddler (the first edition, i.e. the one with
 * the RS232 पूर्णांकerface) as a joystick under Linux
 *
 * The Twiddler is a one-handed chording keyboard featuring twelve buttons on
 * the front, six buttons on the top, and a built-in tilt sensor. The buttons
 * on the front, which are grouped as four rows of three buttons, are pressed
 * by the four fingers (this implies only one button per row can be held करोwn
 * at the same समय) and the buttons on the top are क्रम the thumb. The tilt
 * sensor delivers X and Y axis data depending on how the Twiddler is held.
 * Additional inक्रमmation can be found at http://www.handykey.com.
 *
 * This driver करोes not use the Twiddler क्रम its पूर्णांकended purpose, i.e. as
 * a chording keyboard, but as a joystick: pressing and releasing a button
 * immediately sends a corresponding button event, and tilting it generates
 * corresponding ABS_X and ABS_Y events. This turns the Twiddler पूर्णांकo a game
 * controller with amazing 18 buttons :-)
 *
 * Note: The Twiddler2 (the successor of the Twiddler that connects directly
 * to the PS/2 keyboard and mouse ports) is NOT supported by this driver!
 *
 * For questions or feedback regarding this driver module please contact:
 * Arndt Schoenewald <arndt@quelltext.com>
 */

/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"Handykey Twiddler keyboard as a joystick driver"

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Constants.
 */

#घोषणा TWIDJOY_MAX_LENGTH 5

अटल काष्ठा twidjoy_button_spec अणु
	पूर्णांक bitshअगरt;
	पूर्णांक biपंचांगask;
	पूर्णांक buttons[3];
पूर्ण
twidjoy_buttons[] = अणु
	अणु  0, 3, अणु BTN_A,      BTN_B,     BTN_C    पूर्ण पूर्ण,
	अणु  2, 3, अणु BTN_X,      BTN_Y,     BTN_Z    पूर्ण पूर्ण,
	अणु  4, 3, अणु BTN_TL,     BTN_TR,    BTN_TR2  पूर्ण पूर्ण,
	अणु  6, 3, अणु BTN_SELECT, BTN_START, BTN_MODE पूर्ण पूर्ण,
	अणु  8, 1, अणु BTN_BASE5                       पूर्ण पूर्ण,
	अणु  9, 1, अणु BTN_BASE                        पूर्ण पूर्ण,
	अणु 10, 1, अणु BTN_BASE3                       पूर्ण पूर्ण,
	अणु 11, 1, अणु BTN_BASE4                       पूर्ण पूर्ण,
	अणु 12, 1, अणु BTN_BASE2                       पूर्ण पूर्ण,
	अणु 13, 1, अणु BTN_BASE6                       पूर्ण पूर्ण,
	अणु 0,  0, अणु 0                               पूर्ण पूर्ण
पूर्ण;

/*
 * Per-Twiddler data.
 */

काष्ठा twidjoy अणु
	काष्ठा input_dev *dev;
	पूर्णांक idx;
	अचिन्हित अक्षर data[TWIDJOY_MAX_LENGTH];
	अक्षर phys[32];
पूर्ण;

/*
 * twidjoy_process_packet() decodes packets the driver receives from the
 * Twiddler. It updates the data accordingly.
 */

अटल व्योम twidjoy_process_packet(काष्ठा twidjoy *twidjoy)
अणु
	काष्ठा input_dev *dev = twidjoy->dev;
	अचिन्हित अक्षर *data = twidjoy->data;
	काष्ठा twidjoy_button_spec *bp;
	पूर्णांक button_bits, असल_x, असल_y;

	button_bits = ((data[1] & 0x7f) << 7) | (data[0] & 0x7f);

	क्रम (bp = twidjoy_buttons; bp->biपंचांगask; bp++) अणु
		पूर्णांक value = (button_bits & (bp->biपंचांगask << bp->bitshअगरt)) >> bp->bitshअगरt;
		पूर्णांक i;

		क्रम (i = 0; i < bp->biपंचांगask; i++)
			input_report_key(dev, bp->buttons[i], i+1 == value);
	पूर्ण

	असल_x = ((data[4] & 0x07) << 5) | ((data[3] & 0x7C) >> 2);
	अगर (data[4] & 0x08) असल_x -= 256;

	असल_y = ((data[3] & 0x01) << 7) | ((data[2] & 0x7F) >> 0);
	अगर (data[3] & 0x02) असल_y -= 256;

	input_report_असल(dev, ABS_X, -असल_x);
	input_report_असल(dev, ABS_Y, +असल_y);

	input_sync(dev);
पूर्ण

/*
 * twidjoy_पूर्णांकerrupt() is called by the low level driver when अक्षरacters
 * are पढ़ोy क्रम us. We then buffer them क्रम further processing, or call the
 * packet processing routine.
 */

अटल irqवापस_t twidjoy_पूर्णांकerrupt(काष्ठा serio *serio, अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा twidjoy *twidjoy = serio_get_drvdata(serio);

	/* All Twiddler packets are 5 bytes. The fact that the first byte
	 * has a MSB of 0 and all other bytes have a MSB of 1 can be used
	 * to check and regain sync. */

	अगर ((data & 0x80) == 0)
		twidjoy->idx = 0;	/* this byte starts a new packet */
	अन्यथा अगर (twidjoy->idx == 0)
		वापस IRQ_HANDLED;	/* wrong MSB -- ignore this byte */

	अगर (twidjoy->idx < TWIDJOY_MAX_LENGTH)
		twidjoy->data[twidjoy->idx++] = data;

	अगर (twidjoy->idx == TWIDJOY_MAX_LENGTH) अणु
		twidjoy_process_packet(twidjoy);
		twidjoy->idx = 0;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * twidjoy_disconnect() is the opposite of twidjoy_connect()
 */

अटल व्योम twidjoy_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा twidjoy *twidjoy = serio_get_drvdata(serio);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_unरेजिस्टर_device(twidjoy->dev);
	kमुक्त(twidjoy);
पूर्ण

/*
 * twidjoy_connect() is the routine that is called when someone adds a
 * new serio device. It looks क्रम the Twiddler, and अगर found, रेजिस्टरs
 * it as an input device.
 */

अटल पूर्णांक twidjoy_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा twidjoy_button_spec *bp;
	काष्ठा twidjoy *twidjoy;
	काष्ठा input_dev *input_dev;
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;

	twidjoy = kzalloc(माप(काष्ठा twidjoy), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!twidjoy || !input_dev)
		जाओ fail1;

	twidjoy->dev = input_dev;
	snम_लिखो(twidjoy->phys, माप(twidjoy->phys), "%s/input0", serio->phys);

	input_dev->name = "Handykey Twiddler";
	input_dev->phys = twidjoy->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_TWIDJOY;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_set_असल_params(input_dev, ABS_X, -50, 50, 4, 4);
	input_set_असल_params(input_dev, ABS_Y, -50, 50, 4, 4);

	क्रम (bp = twidjoy_buttons; bp->biपंचांगask; bp++)
		क्रम (i = 0; i < bp->biपंचांगask; i++)
			set_bit(bp->buttons[i], input_dev->keybit);

	serio_set_drvdata(serio, twidjoy);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(twidjoy->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(twidjoy);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id twidjoy_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_TWIDJOY,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, twidjoy_serio_ids);

अटल काष्ठा serio_driver twidjoy_drv = अणु
	.driver		= अणु
		.name	= "twidjoy",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= twidjoy_serio_ids,
	.पूर्णांकerrupt	= twidjoy_पूर्णांकerrupt,
	.connect	= twidjoy_connect,
	.disconnect	= twidjoy_disconnect,
पूर्ण;

module_serio_driver(twidjoy_drv);
