<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Elo serial touchscreen driver
 *
 * Copyright (c) 2004 Vojtech Pavlik
 */


/*
 * This driver can handle serial Elo touchscreens using either the Elo standard
 * 'E271-2210' 10-byte protocol, Elo legacy 'E281A-4002' 6-byte protocol, Elo
 * legacy 'E271-140' 4-byte protocol and Elo legacy 'E261-280' 3-byte protocol.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>
#समावेश <linux/प्रकार.स>

#घोषणा DRIVER_DESC	"Elo serial touchscreen driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Definitions & global arrays.
 */

#घोषणा ELO_MAX_LENGTH		10

#घोषणा ELO10_PACKET_LEN	8
#घोषणा ELO10_TOUCH		0x03
#घोषणा ELO10_PRESSURE		0x80

#घोषणा ELO10_LEAD_BYTE		'U'

#घोषणा ELO10_ID_CMD		'i'

#घोषणा ELO10_TOUCH_PACKET	'T'
#घोषणा ELO10_ACK_PACKET	'A'
#घोषणा ELI10_ID_PACKET		'I'

/*
 * Per-touchscreen data.
 */

काष्ठा elo अणु
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
	काष्ठा mutex cmd_mutex;
	काष्ठा completion cmd_करोne;
	पूर्णांक id;
	पूर्णांक idx;
	अचिन्हित अक्षर expected_packet;
	अचिन्हित अक्षर csum;
	अचिन्हित अक्षर data[ELO_MAX_LENGTH];
	अचिन्हित अक्षर response[ELO10_PACKET_LEN];
	अक्षर phys[32];
पूर्ण;

अटल व्योम elo_process_data_10(काष्ठा elo *elo, अचिन्हित अक्षर data)
अणु
	काष्ठा input_dev *dev = elo->dev;

	elo->data[elo->idx] = data;

	चयन (elo->idx++) अणु
	हाल 0:
		elo->csum = 0xaa;
		अगर (data != ELO10_LEAD_BYTE) अणु
			dev_dbg(&elo->serio->dev,
				"unsynchronized data: 0x%02x\n", data);
			elo->idx = 0;
		पूर्ण
		अवरोध;

	हाल 9:
		elo->idx = 0;
		अगर (data != elo->csum) अणु
			dev_dbg(&elo->serio->dev,
				"bad checksum: 0x%02x, expected 0x%02x\n",
				 data, elo->csum);
			अवरोध;
		पूर्ण
		अगर (elo->data[1] != elo->expected_packet) अणु
			अगर (elo->data[1] != ELO10_TOUCH_PACKET)
				dev_dbg(&elo->serio->dev,
					"unexpected packet: 0x%02x\n",
					 elo->data[1]);
			अवरोध;
		पूर्ण
		अगर (likely(elo->data[1] == ELO10_TOUCH_PACKET)) अणु
			input_report_असल(dev, ABS_X, (elo->data[4] << 8) | elo->data[3]);
			input_report_असल(dev, ABS_Y, (elo->data[6] << 8) | elo->data[5]);
			अगर (elo->data[2] & ELO10_PRESSURE)
				input_report_असल(dev, ABS_PRESSURE,
						(elo->data[8] << 8) | elo->data[7]);
			input_report_key(dev, BTN_TOUCH, elo->data[2] & ELO10_TOUCH);
			input_sync(dev);
		पूर्ण अन्यथा अगर (elo->data[1] == ELO10_ACK_PACKET) अणु
			अगर (elo->data[2] == '0')
				elo->expected_packet = ELO10_TOUCH_PACKET;
			complete(&elo->cmd_करोne);
		पूर्ण अन्यथा अणु
			स_नकल(elo->response, &elo->data[1], ELO10_PACKET_LEN);
			elo->expected_packet = ELO10_ACK_PACKET;
		पूर्ण
		अवरोध;
	पूर्ण
	elo->csum += data;
पूर्ण

अटल व्योम elo_process_data_6(काष्ठा elo *elo, अचिन्हित अक्षर data)
अणु
	काष्ठा input_dev *dev = elo->dev;

	elo->data[elo->idx] = data;

	चयन (elo->idx++) अणु

	हाल 0:
		अगर ((data & 0xc0) != 0xc0)
			elo->idx = 0;
		अवरोध;

	हाल 1:
		अगर ((data & 0xc0) != 0x80)
			elo->idx = 0;
		अवरोध;

	हाल 2:
		अगर ((data & 0xc0) != 0x40)
			elo->idx = 0;
		अवरोध;

	हाल 3:
		अगर (data & 0xc0) अणु
			elo->idx = 0;
			अवरोध;
		पूर्ण

		input_report_असल(dev, ABS_X, ((elo->data[0] & 0x3f) << 6) | (elo->data[1] & 0x3f));
		input_report_असल(dev, ABS_Y, ((elo->data[2] & 0x3f) << 6) | (elo->data[3] & 0x3f));

		अगर (elo->id == 2) अणु
			input_report_key(dev, BTN_TOUCH, 1);
			input_sync(dev);
			elo->idx = 0;
		पूर्ण

		अवरोध;

	हाल 4:
		अगर (data) अणु
			input_sync(dev);
			elo->idx = 0;
		पूर्ण
		अवरोध;

	हाल 5:
		अगर ((data & 0xf0) == 0) अणु
			input_report_असल(dev, ABS_PRESSURE, elo->data[5]);
			input_report_key(dev, BTN_TOUCH, !!elo->data[5]);
		पूर्ण
		input_sync(dev);
		elo->idx = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम elo_process_data_3(काष्ठा elo *elo, अचिन्हित अक्षर data)
अणु
	काष्ठा input_dev *dev = elo->dev;

	elo->data[elo->idx] = data;

	चयन (elo->idx++) अणु

	हाल 0:
		अगर ((data & 0x7f) != 0x01)
			elo->idx = 0;
		अवरोध;
	हाल 2:
		input_report_key(dev, BTN_TOUCH, !(elo->data[1] & 0x80));
		input_report_असल(dev, ABS_X, elo->data[1]);
		input_report_असल(dev, ABS_Y, elo->data[2]);
		input_sync(dev);
		elo->idx = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t elo_पूर्णांकerrupt(काष्ठा serio *serio,
		अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा elo *elo = serio_get_drvdata(serio);

	चयन (elo->id) अणु
	हाल 0:
		elo_process_data_10(elo, data);
		अवरोध;

	हाल 1:
	हाल 2:
		elo_process_data_6(elo, data);
		अवरोध;

	हाल 3:
		elo_process_data_3(elo, data);
		अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक elo_command_10(काष्ठा elo *elo, अचिन्हित अक्षर *packet)
अणु
	पूर्णांक rc = -1;
	पूर्णांक i;
	अचिन्हित अक्षर csum = 0xaa + ELO10_LEAD_BYTE;

	mutex_lock(&elo->cmd_mutex);

	serio_छोड़ो_rx(elo->serio);
	elo->expected_packet = बड़े(packet[0]);
	init_completion(&elo->cmd_करोne);
	serio_जारी_rx(elo->serio);

	अगर (serio_ग_लिखो(elo->serio, ELO10_LEAD_BYTE))
		जाओ out;

	क्रम (i = 0; i < ELO10_PACKET_LEN; i++) अणु
		csum += packet[i];
		अगर (serio_ग_लिखो(elo->serio, packet[i]))
			जाओ out;
	पूर्ण

	अगर (serio_ग_लिखो(elo->serio, csum))
		जाओ out;

	रुको_क्रम_completion_समयout(&elo->cmd_करोne, HZ);

	अगर (elo->expected_packet == ELO10_TOUCH_PACKET) अणु
		/* We are back in reporting mode, the command was ACKed */
		स_नकल(packet, elo->response, ELO10_PACKET_LEN);
		rc = 0;
	पूर्ण

 out:
	mutex_unlock(&elo->cmd_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक elo_setup_10(काष्ठा elo *elo)
अणु
	अटल स्थिर अक्षर *elo_types[] = अणु "Accu", "Dura", "Intelli", "Carroll" पूर्ण;
	काष्ठा input_dev *dev = elo->dev;
	अचिन्हित अक्षर packet[ELO10_PACKET_LEN] = अणु ELO10_ID_CMD पूर्ण;

	अगर (elo_command_10(elo, packet))
		वापस -1;

	dev->id.version = (packet[5] << 8) | packet[4];

	input_set_असल_params(dev, ABS_X, 96, 4000, 0, 0);
	input_set_असल_params(dev, ABS_Y, 96, 4000, 0, 0);
	अगर (packet[3] & ELO10_PRESSURE)
		input_set_असल_params(dev, ABS_PRESSURE, 0, 255, 0, 0);

	dev_info(&elo->serio->dev,
		 "%sTouch touchscreen, fw: %02x.%02x, features: 0x%02x, controller: 0x%02x\n",
		 elo_types[(packet[1] -'0') & 0x03],
		 packet[5], packet[4], packet[3], packet[7]);

	वापस 0;
पूर्ण

/*
 * elo_disconnect() is the opposite of elo_connect()
 */

अटल व्योम elo_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा elo *elo = serio_get_drvdata(serio);

	input_get_device(elo->dev);
	input_unरेजिस्टर_device(elo->dev);
	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_put_device(elo->dev);
	kमुक्त(elo);
पूर्ण

/*
 * elo_connect() is the routine that is called when someone adds a
 * new serio device that supports Gunze protocol and रेजिस्टरs it as
 * an input device.
 */

अटल पूर्णांक elo_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा elo *elo;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	elo = kzalloc(माप(काष्ठा elo), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!elo || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	elo->serio = serio;
	elo->id = serio->id.id;
	elo->dev = input_dev;
	elo->expected_packet = ELO10_TOUCH_PACKET;
	mutex_init(&elo->cmd_mutex);
	init_completion(&elo->cmd_करोne);
	snम_लिखो(elo->phys, माप(elo->phys), "%s/input0", serio->phys);

	input_dev->name = "Elo Serial TouchScreen";
	input_dev->phys = elo->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_ELO;
	input_dev->id.product = elo->id;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	serio_set_drvdata(serio, elo);
	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	चयन (elo->id) अणु

	हाल 0: /* 10-byte protocol */
		अगर (elo_setup_10(elo)) अणु
			err = -EIO;
			जाओ fail3;
		पूर्ण

		अवरोध;

	हाल 1: /* 6-byte protocol */
		input_set_असल_params(input_dev, ABS_PRESSURE, 0, 15, 0, 0);
		fallthrough;

	हाल 2: /* 4-byte protocol */
		input_set_असल_params(input_dev, ABS_X, 96, 4000, 0, 0);
		input_set_असल_params(input_dev, ABS_Y, 96, 4000, 0, 0);
		अवरोध;

	हाल 3: /* 3-byte protocol */
		input_set_असल_params(input_dev, ABS_X, 0, 255, 0, 0);
		input_set_असल_params(input_dev, ABS_Y, 0, 255, 0, 0);
		अवरोध;
	पूर्ण

	err = input_रेजिस्टर_device(elo->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3: serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(elo);
	वापस err;
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id elo_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_ELO,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, elo_serio_ids);

अटल काष्ठा serio_driver elo_drv = अणु
	.driver		= अणु
		.name	= "elo",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= elo_serio_ids,
	.पूर्णांकerrupt	= elo_पूर्णांकerrupt,
	.connect	= elo_connect,
	.disconnect	= elo_disconnect,
पूर्ण;

module_serio_driver(elo_drv);
