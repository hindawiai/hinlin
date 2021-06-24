<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2000-2001 Vojtech Pavlik <vojtech@ucw.cz>
 *  Copyright (c) 2001, 2007 Johann Deneux <johann.deneux@gmail.com>
 *
 *  USB/RS232 I-Force joysticks and wheels.
 */

#समावेश <linux/serपन.स>
#समावेश "iforce.h"

काष्ठा अगरorce_serio अणु
	काष्ठा अगरorce अगरorce;

	काष्ठा serio *serio;
	पूर्णांक idx, pkt, len, id;
	u8 csum;
	u8 expect_packet;
	u8 cmd_response[IFORCE_MAX_LENGTH];
	u8 cmd_response_len;
	u8 data_in[IFORCE_MAX_LENGTH];
पूर्ण;

अटल व्योम अगरorce_serio_xmit(काष्ठा अगरorce *अगरorce)
अणु
	काष्ठा अगरorce_serio *अगरorce_serio = container_of(अगरorce,
							 काष्ठा अगरorce_serio,
							 अगरorce);
	अचिन्हित अक्षर cs;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (test_and_set_bit(IFORCE_XMIT_RUNNING, अगरorce->xmit_flags)) अणु
		set_bit(IFORCE_XMIT_AGAIN, अगरorce->xmit_flags);
		वापस;
	पूर्ण

	spin_lock_irqsave(&अगरorce->xmit_lock, flags);

again:
	अगर (अगरorce->xmit.head == अगरorce->xmit.tail) अणु
		clear_bit(IFORCE_XMIT_RUNNING, अगरorce->xmit_flags);
		spin_unlock_irqrestore(&अगरorce->xmit_lock, flags);
		वापस;
	पूर्ण

	cs = 0x2b;

	serio_ग_लिखो(अगरorce_serio->serio, 0x2b);

	serio_ग_लिखो(अगरorce_serio->serio, अगरorce->xmit.buf[अगरorce->xmit.tail]);
	cs ^= अगरorce->xmit.buf[अगरorce->xmit.tail];
	XMIT_INC(अगरorce->xmit.tail, 1);

	क्रम (i=अगरorce->xmit.buf[अगरorce->xmit.tail]; i >= 0; --i) अणु
		serio_ग_लिखो(अगरorce_serio->serio,
			    अगरorce->xmit.buf[अगरorce->xmit.tail]);
		cs ^= अगरorce->xmit.buf[अगरorce->xmit.tail];
		XMIT_INC(अगरorce->xmit.tail, 1);
	पूर्ण

	serio_ग_लिखो(अगरorce_serio->serio, cs);

	अगर (test_and_clear_bit(IFORCE_XMIT_AGAIN, अगरorce->xmit_flags))
		जाओ again;

	clear_bit(IFORCE_XMIT_RUNNING, अगरorce->xmit_flags);

	spin_unlock_irqrestore(&अगरorce->xmit_lock, flags);
पूर्ण

अटल पूर्णांक अगरorce_serio_get_id(काष्ठा अगरorce *अगरorce, u8 id,
			       u8 *response_data, माप_प्रकार *response_len)
अणु
	काष्ठा अगरorce_serio *अगरorce_serio = container_of(अगरorce,
							 काष्ठा अगरorce_serio,
							 अगरorce);

	अगरorce_serio->expect_packet = HI(FF_CMD_QUERY);
	अगरorce_serio->cmd_response_len = 0;

	अगरorce_send_packet(अगरorce, FF_CMD_QUERY, &id);

	रुको_event_पूर्णांकerruptible_समयout(अगरorce->रुको,
					 !अगरorce_serio->expect_packet, HZ);

	अगर (अगरorce_serio->expect_packet) अणु
		अगरorce_serio->expect_packet = 0;
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (अगरorce_serio->cmd_response[0] != id)
		वापस -EIO;

	स_नकल(response_data, अगरorce_serio->cmd_response,
	       अगरorce_serio->cmd_response_len);
	*response_len = अगरorce_serio->cmd_response_len;

	वापस 0;
पूर्ण

अटल पूर्णांक अगरorce_serio_start_io(काष्ठा अगरorce *अगरorce)
अणु
	/* No special handling required */
	वापस 0;
पूर्ण

अटल व्योम अगरorce_serio_stop_io(काष्ठा अगरorce *अगरorce)
अणु
	//TODO: Wait क्रम the last packets to be sent
पूर्ण

अटल स्थिर काष्ठा अगरorce_xport_ops अगरorce_serio_xport_ops = अणु
	.xmit		= अगरorce_serio_xmit,
	.get_id		= अगरorce_serio_get_id,
	.start_io	= अगरorce_serio_start_io,
	.stop_io	= अगरorce_serio_stop_io,
पूर्ण;

अटल व्योम अगरorce_serio_ग_लिखो_wakeup(काष्ठा serio *serio)
अणु
	काष्ठा अगरorce *अगरorce = serio_get_drvdata(serio);

	अगरorce_serio_xmit(अगरorce);
पूर्ण

अटल irqवापस_t अगरorce_serio_irq(काष्ठा serio *serio,
				    अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा अगरorce_serio *अगरorce_serio = serio_get_drvdata(serio);
	काष्ठा अगरorce *अगरorce = &अगरorce_serio->अगरorce;

	अगर (!अगरorce_serio->pkt) अणु
		अगर (data == 0x2b)
			अगरorce_serio->pkt = 1;
		जाओ out;
	पूर्ण

	अगर (!अगरorce_serio->id) अणु
		अगर (data > 3 && data != 0xff)
			अगरorce_serio->pkt = 0;
		अन्यथा
			अगरorce_serio->id = data;
		जाओ out;
	पूर्ण

	अगर (!अगरorce_serio->len) अणु
		अगर (data > IFORCE_MAX_LENGTH) अणु
			अगरorce_serio->pkt = 0;
			अगरorce_serio->id = 0;
		पूर्ण अन्यथा अणु
			अगरorce_serio->len = data;
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (अगरorce_serio->idx < अगरorce_serio->len) अणु
		अगरorce_serio->data_in[अगरorce_serio->idx++] = data;
		अगरorce_serio->csum += data;
		जाओ out;
	पूर्ण

	अगर (अगरorce_serio->idx == अगरorce_serio->len) अणु
		/* Handle command completion */
		अगर (अगरorce_serio->expect_packet == अगरorce_serio->id) अणु
			अगरorce_serio->expect_packet = 0;
			स_नकल(अगरorce_serio->cmd_response,
			       अगरorce_serio->data_in, IFORCE_MAX_LENGTH);
			अगरorce_serio->cmd_response_len = अगरorce_serio->len;

			/* Signal that command is करोne */
			wake_up(&अगरorce->रुको);
		पूर्ण अन्यथा अगर (likely(अगरorce->type)) अणु
			अगरorce_process_packet(अगरorce, अगरorce_serio->id,
					      अगरorce_serio->data_in,
					      अगरorce_serio->len);
		पूर्ण

		अगरorce_serio->pkt = 0;
		अगरorce_serio->id  = 0;
		अगरorce_serio->len = 0;
		अगरorce_serio->idx = 0;
		अगरorce_serio->csum = 0;
	पूर्ण
out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक अगरorce_serio_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा अगरorce_serio *अगरorce_serio;
	पूर्णांक err;

	अगरorce_serio = kzalloc(माप(*अगरorce_serio), GFP_KERNEL);
	अगर (!अगरorce_serio)
		वापस -ENOMEM;

	अगरorce_serio->अगरorce.xport_ops = &अगरorce_serio_xport_ops;

	अगरorce_serio->serio = serio;
	serio_set_drvdata(serio, अगरorce_serio);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail1;

	err = अगरorce_init_device(&serio->dev, BUS_RS232, &अगरorce_serio->अगरorce);
	अगर (err)
		जाओ fail2;

	वापस 0;

 fail2:	serio_बंद(serio);
 fail1:	serio_set_drvdata(serio, शून्य);
	kमुक्त(अगरorce_serio);
	वापस err;
पूर्ण

अटल व्योम अगरorce_serio_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा अगरorce_serio *अगरorce_serio = serio_get_drvdata(serio);

	input_unरेजिस्टर_device(अगरorce_serio->अगरorce.dev);
	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	kमुक्त(अगरorce_serio);
पूर्ण

अटल स्थिर काष्ठा serio_device_id अगरorce_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_IFORCE,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, अगरorce_serio_ids);

काष्ठा serio_driver अगरorce_serio_drv = अणु
	.driver		= अणु
		.name	= "iforce",
	पूर्ण,
	.description	= "RS232 I-Force joysticks and wheels driver",
	.id_table	= अगरorce_serio_ids,
	.ग_लिखो_wakeup	= अगरorce_serio_ग_लिखो_wakeup,
	.पूर्णांकerrupt	= अगरorce_serio_irq,
	.connect	= अगरorce_serio_connect,
	.disconnect	= अगरorce_serio_disconnect,
पूर्ण;

module_serio_driver(अगरorce_serio_drv);

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>, Johann Deneux <johann.deneux@gmail.com>");
MODULE_DESCRIPTION("RS232 I-Force joysticks and wheels driver");
MODULE_LICENSE("GPL");
