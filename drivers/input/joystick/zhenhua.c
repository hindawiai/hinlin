<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  derived from "twidjoy.c"
 *
 *  Copyright (c) 2008 Martin Kebert
 *  Copyright (c) 2001 Arndt Schoenewald
 *  Copyright (c) 2000-2001 Vojtech Pavlik
 *  Copyright (c) 2000 Mark Fletcher
 */

/*
 * Driver to use 4CH RC transmitter using Zhen Hua 5-byte protocol (Walkera Lama,
 * EasyCopter etc.) as a joystick under Linux.
 *
 * RC transmitters using Zhen Hua 5-byte protocol are cheap four channels
 * transmitters क्रम control a RC planes or RC helicopters with possibility to
 * connect on a serial port.
 * Data coming from transmitter is in this order:
 * 1. byte = synchronisation byte
 * 2. byte = X axis
 * 3. byte = Y axis
 * 4. byte = RZ axis
 * 5. byte = Z axis
 * (and this is repeated)
 *
 * For questions or feedback regarding this driver module please contact:
 * Martin Kebert <gkmarty@gmail.com> - but I am not a C-programmer nor kernel
 * coder :-(
 */

/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"RC transmitter with 5-byte Zhen Hua protocol joystick driver"

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Constants.
 */

#घोषणा ZHENHUA_MAX_LENGTH 5

/*
 * Zhen Hua data.
 */

काष्ठा zhenhua अणु
	काष्ठा input_dev *dev;
	पूर्णांक idx;
	अचिन्हित अक्षर data[ZHENHUA_MAX_LENGTH];
	अक्षर phys[32];
पूर्ण;

/*
 * zhenhua_process_packet() decodes packets the driver receives from the
 * RC transmitter. It updates the data accordingly.
 */

अटल व्योम zhenhua_process_packet(काष्ठा zhenhua *zhenhua)
अणु
	काष्ठा input_dev *dev = zhenhua->dev;
	अचिन्हित अक्षर *data = zhenhua->data;

	input_report_असल(dev, ABS_Y, data[1]);
	input_report_असल(dev, ABS_X, data[2]);
	input_report_असल(dev, ABS_RZ, data[3]);
	input_report_असल(dev, ABS_Z, data[4]);

	input_sync(dev);
पूर्ण

/*
 * zhenhua_पूर्णांकerrupt() is called by the low level driver when अक्षरacters
 * are पढ़ोy क्रम us. We then buffer them क्रम further processing, or call the
 * packet processing routine.
 */

अटल irqवापस_t zhenhua_पूर्णांकerrupt(काष्ठा serio *serio, अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा zhenhua *zhenhua = serio_get_drvdata(serio);

	/* All Zhen Hua packets are 5 bytes. The fact that the first byte
	 * is allways 0xf7 and all others are in range 0x32 - 0xc8 (50-200)
	 * can be used to check and regain sync. */

	अगर (data == 0xef)
		zhenhua->idx = 0;	/* this byte starts a new packet */
	अन्यथा अगर (zhenhua->idx == 0)
		वापस IRQ_HANDLED;	/* wrong MSB -- ignore this byte */

	अगर (zhenhua->idx < ZHENHUA_MAX_LENGTH)
		zhenhua->data[zhenhua->idx++] = bitrev8(data);

	अगर (zhenhua->idx == ZHENHUA_MAX_LENGTH) अणु
		zhenhua_process_packet(zhenhua);
		zhenhua->idx = 0;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * zhenhua_disconnect() is the opposite of zhenhua_connect()
 */

अटल व्योम zhenhua_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा zhenhua *zhenhua = serio_get_drvdata(serio);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_unरेजिस्टर_device(zhenhua->dev);
	kमुक्त(zhenhua);
पूर्ण

/*
 * zhenhua_connect() is the routine that is called when someone adds a
 * new serio device. It looks क्रम the Twiddler, and अगर found, रेजिस्टरs
 * it as an input device.
 */

अटल पूर्णांक zhenhua_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा zhenhua *zhenhua;
	काष्ठा input_dev *input_dev;
	पूर्णांक err = -ENOMEM;

	zhenhua = kzalloc(माप(काष्ठा zhenhua), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!zhenhua || !input_dev)
		जाओ fail1;

	zhenhua->dev = input_dev;
	snम_लिखो(zhenhua->phys, माप(zhenhua->phys), "%s/input0", serio->phys);

	input_dev->name = "Zhen Hua 5-byte device";
	input_dev->phys = zhenhua->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_ZHENHUA;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT(EV_ABS);
	input_set_असल_params(input_dev, ABS_X, 50, 200, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 50, 200, 0, 0);
	input_set_असल_params(input_dev, ABS_Z, 50, 200, 0, 0);
	input_set_असल_params(input_dev, ABS_RZ, 50, 200, 0, 0);

	serio_set_drvdata(serio, zhenhua);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(zhenhua->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(zhenhua);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id zhenhua_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_ZHENHUA,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, zhenhua_serio_ids);

अटल काष्ठा serio_driver zhenhua_drv = अणु
	.driver		= अणु
		.name	= "zhenhua",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= zhenhua_serio_ids,
	.पूर्णांकerrupt	= zhenhua_पूर्णांकerrupt,
	.connect	= zhenhua_connect,
	.disconnect	= zhenhua_disconnect,
पूर्ण;

module_serio_driver(zhenhua_drv);
