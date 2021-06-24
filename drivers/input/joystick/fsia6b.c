<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FS-iA6B iBus RC receiver driver
 *
 * This driver provides all 14 channels of the FlySky FS-ia6B RC receiver
 * as analog values.
 *
 * Additionally, the channels can be converted to discrete चयन values.
 * By शेष, it is configured क्रम the offical FS-i6 remote control.
 * If you use a dअगरferent hardware configuration, you can configure it
 * using the `चयन_config` parameter.
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/serपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#घोषणा DRIVER_DESC		"FS-iA6B iBus RC receiver"

MODULE_AUTHOR("Markus Koch <markus@notsyncing.net>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#घोषणा IBUS_SERVO_COUNT	14

अटल अक्षर *चयन_config = "00000022320000";
module_param(चयन_config, अक्षरp, 0444);
MODULE_PARM_DESC(चयन_config,
		 "Amount of switch positions per channel (14 characters, 0-3)");

अटल पूर्णांक fsia6b_axes[IBUS_SERVO_COUNT] = अणु
	ABS_X, ABS_Y,
	ABS_Z, ABS_RX,
	ABS_RY, ABS_RZ,
	ABS_HAT0X, ABS_HAT0Y,
	ABS_HAT1X, ABS_HAT1Y,
	ABS_HAT2X, ABS_HAT2Y,
	ABS_HAT3X, ABS_HAT3Y
पूर्ण;

क्रमागत ibus_state अणु SYNC, COLLECT, PROCESS पूर्ण;

काष्ठा ibus_packet अणु
	क्रमागत ibus_state state;

	पूर्णांक offset;
	u16 ibuf;
	u16 channel[IBUS_SERVO_COUNT];
पूर्ण;

काष्ठा fsia6b अणु
	काष्ठा input_dev *dev;
	काष्ठा ibus_packet packet;

	अक्षर phys[32];
पूर्ण;

अटल irqवापस_t fsia6b_serio_irq(काष्ठा serio *serio,
				    अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा fsia6b *fsia6b = serio_get_drvdata(serio);
	पूर्णांक i;
	पूर्णांक sw_state;
	पूर्णांक sw_id = BTN_0;

	fsia6b->packet.ibuf = (data << 8) | ((fsia6b->packet.ibuf >> 8) & 0xFF);

	चयन (fsia6b->packet.state) अणु
	हाल SYNC:
		अगर (fsia6b->packet.ibuf == 0x4020)
			fsia6b->packet.state = COLLECT;
		अवरोध;

	हाल COLLECT:
		fsia6b->packet.state = PROCESS;
		अवरोध;

	हाल PROCESS:
		fsia6b->packet.channel[fsia6b->packet.offset] =
				fsia6b->packet.ibuf;
		fsia6b->packet.offset++;

		अगर (fsia6b->packet.offset == IBUS_SERVO_COUNT) अणु
			fsia6b->packet.offset = 0;
			fsia6b->packet.state = SYNC;
			क्रम (i = 0; i < IBUS_SERVO_COUNT; ++i) अणु
				input_report_असल(fsia6b->dev, fsia6b_axes[i],
						 fsia6b->packet.channel[i]);

				sw_state = 0;
				अगर (fsia6b->packet.channel[i] > 1900)
					sw_state = 1;
				अन्यथा अगर (fsia6b->packet.channel[i] < 1100)
					sw_state = 2;

				चयन (चयन_config[i]) अणु
				हाल '3':
					input_report_key(fsia6b->dev,
							 sw_id++,
							 sw_state == 0);
					fallthrough;
				हाल '2':
					input_report_key(fsia6b->dev,
							 sw_id++,
							 sw_state == 1);
					fallthrough;
				हाल '1':
					input_report_key(fsia6b->dev,
							 sw_id++,
							 sw_state == 2);
				पूर्ण
			पूर्ण
			input_sync(fsia6b->dev);
		पूर्ण अन्यथा अणु
			fsia6b->packet.state = COLLECT;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fsia6b_serio_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा fsia6b *fsia6b;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;
	पूर्णांक i, j;
	पूर्णांक sw_id = 0;

	fsia6b = kzalloc(माप(*fsia6b), GFP_KERNEL);
	अगर (!fsia6b)
		वापस -ENOMEM;

	fsia6b->packet.ibuf = 0;
	fsia6b->packet.offset = 0;
	fsia6b->packet.state = SYNC;

	serio_set_drvdata(serio, fsia6b);

	input_dev = input_allocate_device();
	अगर (!input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण
	fsia6b->dev = input_dev;

	snम_लिखो(fsia6b->phys, माप(fsia6b->phys), "%s/input0", serio->phys);

	input_dev->name = DRIVER_DESC;
	input_dev->phys = fsia6b->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_FSIA6B;
	input_dev->id.product = serio->id.id;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	क्रम (i = 0; i < IBUS_SERVO_COUNT; i++)
		input_set_असल_params(input_dev, fsia6b_axes[i],
				     1000, 2000, 2, 2);

	/* Register चयन configuration */
	क्रम (i = 0; i < IBUS_SERVO_COUNT; i++) अणु
		अगर (चयन_config[i] < '0' || switch_config[i] > '3') अणु
			dev_err(&fsia6b->dev->dev,
				"Invalid switch configuration supplied for fsia6b.\n");
			err = -EINVAL;
			जाओ fail2;
		पूर्ण

		क्रम (j = '1'; j <= चयन_config[i]; j++) अणु
			input_set_capability(input_dev, EV_KEY, BTN_0 + sw_id);
			sw_id++;
		पूर्ण
	पूर्ण

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = input_रेजिस्टर_device(fsia6b->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

fail3:	serio_बंद(serio);
fail2:	input_मुक्त_device(input_dev);
fail1:	serio_set_drvdata(serio, शून्य);
	kमुक्त(fsia6b);
	वापस err;
पूर्ण

अटल व्योम fsia6b_serio_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा fsia6b *fsia6b = serio_get_drvdata(serio);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_unरेजिस्टर_device(fsia6b->dev);
	kमुक्त(fsia6b);
पूर्ण

अटल स्थिर काष्ठा serio_device_id fsia6b_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_FSIA6B,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, fsia6b_serio_ids);

अटल काष्ठा serio_driver fsia6b_serio_drv = अणु
	.driver		= अणु
		.name	= "fsia6b"
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= fsia6b_serio_ids,
	.पूर्णांकerrupt	= fsia6b_serio_irq,
	.connect	= fsia6b_serio_connect,
	.disconnect	= fsia6b_serio_disconnect
पूर्ण;

module_serio_driver(fsia6b_serio_drv)
