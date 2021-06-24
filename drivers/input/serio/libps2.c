<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PS/2 driver library
 *
 * Copyright (c) 1999-2002 Vojtech Pavlik
 * Copyright (c) 2004 Dmitry Torokhov
 */


#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>
#समावेश <linux/i8042.h>
#समावेश <linux/libps2.h>

#घोषणा DRIVER_DESC	"PS/2 driver library"

MODULE_AUTHOR("Dmitry Torokhov <dtor@mail.ru>");
MODULE_DESCRIPTION("PS/2 driver library");
MODULE_LICENSE("GPL");

अटल पूर्णांक ps2_करो_sendbyte(काष्ठा ps2dev *ps2dev, u8 byte,
			   अचिन्हित पूर्णांक समयout, अचिन्हित पूर्णांक max_attempts)
	__releases(&ps2dev->serio->lock) __acquires(&ps2dev->serio->lock)
अणु
	पूर्णांक attempt = 0;
	पूर्णांक error;

	lockdep_निश्चित_held(&ps2dev->serio->lock);

	करो अणु
		ps2dev->nak = 1;
		ps2dev->flags |= PS2_FLAG_ACK;

		serio_जारी_rx(ps2dev->serio);

		error = serio_ग_लिखो(ps2dev->serio, byte);
		अगर (error)
			dev_dbg(&ps2dev->serio->dev,
				"failed to write %#02x: %d\n", byte, error);
		अन्यथा
			रुको_event_समयout(ps2dev->रुको,
					   !(ps2dev->flags & PS2_FLAG_ACK),
					   msecs_to_jअगरfies(समयout));

		serio_छोड़ो_rx(ps2dev->serio);
	पूर्ण जबतक (ps2dev->nak == PS2_RET_NAK && ++attempt < max_attempts);

	ps2dev->flags &= ~PS2_FLAG_ACK;

	अगर (!error) अणु
		चयन (ps2dev->nak) अणु
		हाल 0:
			अवरोध;
		हाल PS2_RET_NAK:
			error = -EAGAIN;
			अवरोध;
		हाल PS2_RET_ERR:
			error = -EPROTO;
			अवरोध;
		शेष:
			error = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (error || attempt > 1)
		dev_dbg(&ps2dev->serio->dev,
			"%02x - %d (%x), attempt %d\n",
			byte, error, ps2dev->nak, attempt);

	वापस error;
पूर्ण

/*
 * ps2_sendbyte() sends a byte to the device and रुकोs क्रम acknowledge.
 * It करोesn't handle retransmission, the caller is expected to handle
 * it when needed.
 *
 * ps2_sendbyte() can only be called from a process context.
 */

पूर्णांक ps2_sendbyte(काष्ठा ps2dev *ps2dev, u8 byte, अचिन्हित पूर्णांक समयout)
अणु
	पूर्णांक retval;

	serio_छोड़ो_rx(ps2dev->serio);

	retval = ps2_करो_sendbyte(ps2dev, byte, समयout, 1);
	dev_dbg(&ps2dev->serio->dev, "%02x - %x\n", byte, ps2dev->nak);

	serio_जारी_rx(ps2dev->serio);

	वापस retval;
पूर्ण
EXPORT_SYMBOL(ps2_sendbyte);

व्योम ps2_begin_command(काष्ठा ps2dev *ps2dev)
अणु
	काष्ठा mutex *m = ps2dev->serio->ps2_cmd_mutex ?: &ps2dev->cmd_mutex;

	mutex_lock(m);
पूर्ण
EXPORT_SYMBOL(ps2_begin_command);

व्योम ps2_end_command(काष्ठा ps2dev *ps2dev)
अणु
	काष्ठा mutex *m = ps2dev->serio->ps2_cmd_mutex ?: &ps2dev->cmd_mutex;

	mutex_unlock(m);
पूर्ण
EXPORT_SYMBOL(ps2_end_command);

/*
 * ps2_drain() रुकोs क्रम device to transmit requested number of bytes
 * and discards them.
 */

व्योम ps2_drain(काष्ठा ps2dev *ps2dev, माप_प्रकार maxbytes, अचिन्हित पूर्णांक समयout)
अणु
	अगर (maxbytes > माप(ps2dev->cmdbuf)) अणु
		WARN_ON(1);
		maxbytes = माप(ps2dev->cmdbuf);
	पूर्ण

	ps2_begin_command(ps2dev);

	serio_छोड़ो_rx(ps2dev->serio);
	ps2dev->flags = PS2_FLAG_CMD;
	ps2dev->cmdcnt = maxbytes;
	serio_जारी_rx(ps2dev->serio);

	रुको_event_समयout(ps2dev->रुको,
			   !(ps2dev->flags & PS2_FLAG_CMD),
			   msecs_to_jअगरfies(समयout));

	ps2_end_command(ps2dev);
पूर्ण
EXPORT_SYMBOL(ps2_drain);

/*
 * ps2_is_keyboard_id() checks received ID byte against the list of
 * known keyboard IDs.
 */

bool ps2_is_keyboard_id(u8 id_byte)
अणु
	अटल स्थिर u8 keyboard_ids[] = अणु
		0xab,	/* Regular keyboards		*/
		0xac,	/* NCD Sun keyboard		*/
		0x2b,	/* Trust keyboard, translated	*/
		0x5d,	/* Trust keyboard		*/
		0x60,	/* NMB SGI keyboard, translated */
		0x47,	/* NMB SGI keyboard		*/
	पूर्ण;

	वापस स_प्रथम(keyboard_ids, id_byte, माप(keyboard_ids)) != शून्य;
पूर्ण
EXPORT_SYMBOL(ps2_is_keyboard_id);

/*
 * ps2_adjust_समयout() is called after receiving 1st byte of command
 * response and tries to reduce reमुख्यing समयout to speed up command
 * completion.
 */

अटल पूर्णांक ps2_adjust_समयout(काष्ठा ps2dev *ps2dev,
			      अचिन्हित पूर्णांक command, अचिन्हित पूर्णांक समयout)
अणु
	चयन (command) अणु
	हाल PS2_CMD_RESET_BAT:
		/*
		 * Device has sent the first response byte after
		 * reset command, reset is thus करोne, so we can
		 * लघुen the समयout.
		 * The next byte will come soon (keyboard) or not
		 * at all (mouse).
		 */
		अगर (समयout > msecs_to_jअगरfies(100))
			समयout = msecs_to_jअगरfies(100);
		अवरोध;

	हाल PS2_CMD_GETID:
		/*
		 * Microsoft Natural Elite keyboard responds to
		 * the GET ID command as it were a mouse, with
		 * a single byte. Fail the command so atkbd will
		 * use alternative probe to detect it.
		 */
		अगर (ps2dev->cmdbuf[1] == 0xaa) अणु
			serio_छोड़ो_rx(ps2dev->serio);
			ps2dev->flags = 0;
			serio_जारी_rx(ps2dev->serio);
			समयout = 0;
		पूर्ण

		/*
		 * If device behind the port is not a keyboard there
		 * won't be 2nd byte of ID response.
		 */
		अगर (!ps2_is_keyboard_id(ps2dev->cmdbuf[1])) अणु
			serio_छोड़ो_rx(ps2dev->serio);
			ps2dev->flags = ps2dev->cmdcnt = 0;
			serio_जारी_rx(ps2dev->serio);
			समयout = 0;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस समयout;
पूर्ण

/*
 * ps2_command() sends a command and its parameters to the mouse,
 * then रुकोs क्रम the response and माला_दो it in the param array.
 *
 * ps2_command() can only be called from a process context
 */

पूर्णांक __ps2_command(काष्ठा ps2dev *ps2dev, u8 *param, अचिन्हित पूर्णांक command)
अणु
	अचिन्हित पूर्णांक समयout;
	अचिन्हित पूर्णांक send = (command >> 12) & 0xf;
	अचिन्हित पूर्णांक receive = (command >> 8) & 0xf;
	पूर्णांक rc;
	पूर्णांक i;
	u8 send_param[16];

	अगर (receive > माप(ps2dev->cmdbuf)) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	अगर (send && !param) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	स_नकल(send_param, param, send);

	serio_छोड़ो_rx(ps2dev->serio);

	ps2dev->flags = command == PS2_CMD_GETID ? PS2_FLAG_WAITID : 0;
	ps2dev->cmdcnt = receive;
	अगर (receive && param)
		क्रम (i = 0; i < receive; i++)
			ps2dev->cmdbuf[(receive - 1) - i] = param[i];

	/* Signal that we are sending the command byte */
	ps2dev->flags |= PS2_FLAG_ACK_CMD;

	/*
	 * Some devices (Synaptics) peक्रमm the reset beक्रमe
	 * ACKing the reset command, and so it can take a दीर्घ
	 * समय beक्रमe the ACK arrives.
	 */
	समयout = command == PS2_CMD_RESET_BAT ? 1000 : 200;

	rc = ps2_करो_sendbyte(ps2dev, command & 0xff, समयout, 2);
	अगर (rc)
		जाओ out_reset_flags;

	/* Now we are sending command parameters, अगर any */
	ps2dev->flags &= ~PS2_FLAG_ACK_CMD;

	क्रम (i = 0; i < send; i++) अणु
		rc = ps2_करो_sendbyte(ps2dev, param[i], 200, 2);
		अगर (rc)
			जाओ out_reset_flags;
	पूर्ण

	serio_जारी_rx(ps2dev->serio);

	/*
	 * The reset command takes a दीर्घ समय to execute.
	 */
	समयout = msecs_to_jअगरfies(command == PS2_CMD_RESET_BAT ? 4000 : 500);

	समयout = रुको_event_समयout(ps2dev->रुको,
				     !(ps2dev->flags & PS2_FLAG_CMD1), समयout);

	अगर (ps2dev->cmdcnt && !(ps2dev->flags & PS2_FLAG_CMD1)) अणु

		समयout = ps2_adjust_समयout(ps2dev, command, समयout);
		रुको_event_समयout(ps2dev->रुको,
				   !(ps2dev->flags & PS2_FLAG_CMD), समयout);
	पूर्ण

	serio_छोड़ो_rx(ps2dev->serio);

	अगर (param)
		क्रम (i = 0; i < receive; i++)
			param[i] = ps2dev->cmdbuf[(receive - 1) - i];

	अगर (ps2dev->cmdcnt &&
	    (command != PS2_CMD_RESET_BAT || ps2dev->cmdcnt != 1)) अणु
		rc = -EPROTO;
		जाओ out_reset_flags;
	पूर्ण

	rc = 0;

 out_reset_flags:
	ps2dev->flags = 0;
	serio_जारी_rx(ps2dev->serio);

	dev_dbg(&ps2dev->serio->dev,
		"%02x [%*ph] - %x/%08lx [%*ph]\n",
		command & 0xff, send, send_param,
		ps2dev->nak, ps2dev->flags,
		receive, param ?: send_param);

	/*
	 * ps_command() handles resends itself, so करो not leak -EAGAIN
	 * to the callers.
	 */
	वापस rc != -EAGAIN ? rc : -EPROTO;
पूर्ण
EXPORT_SYMBOL(__ps2_command);

पूर्णांक ps2_command(काष्ठा ps2dev *ps2dev, u8 *param, अचिन्हित पूर्णांक command)
अणु
	पूर्णांक rc;

	ps2_begin_command(ps2dev);
	rc = __ps2_command(ps2dev, param, command);
	ps2_end_command(ps2dev);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(ps2_command);

/*
 * ps2_sliced_command() sends an extended PS/2 command to the mouse
 * using sliced syntax, understood by advanced devices, such as Logitech
 * or Synaptics touchpads. The command is encoded as:
 * 0xE6 0xE8 rr 0xE8 ss 0xE8 tt 0xE8 uu where (rr*64)+(ss*16)+(tt*4)+uu
 * is the command.
 */

पूर्णांक ps2_sliced_command(काष्ठा ps2dev *ps2dev, u8 command)
अणु
	पूर्णांक i;
	पूर्णांक retval;

	ps2_begin_command(ps2dev);

	retval = __ps2_command(ps2dev, शून्य, PS2_CMD_SETSCALE11);
	अगर (retval)
		जाओ out;

	क्रम (i = 6; i >= 0; i -= 2) अणु
		u8 d = (command >> i) & 3;
		retval = __ps2_command(ps2dev, &d, PS2_CMD_SETRES);
		अगर (retval)
			अवरोध;
	पूर्ण

out:
	dev_dbg(&ps2dev->serio->dev, "%02x - %d\n", command, retval);
	ps2_end_command(ps2dev);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(ps2_sliced_command);

/*
 * ps2_init() initializes ps2dev काष्ठाure
 */

व्योम ps2_init(काष्ठा ps2dev *ps2dev, काष्ठा serio *serio)
अणु
	mutex_init(&ps2dev->cmd_mutex);
	lockdep_set_subclass(&ps2dev->cmd_mutex, serio->depth);
	init_रुकोqueue_head(&ps2dev->रुको);
	ps2dev->serio = serio;
पूर्ण
EXPORT_SYMBOL(ps2_init);

/*
 * ps2_handle_ack() is supposed to be used in पूर्णांकerrupt handler
 * to properly process ACK/NAK of a command from a PS/2 device.
 */

bool ps2_handle_ack(काष्ठा ps2dev *ps2dev, u8 data)
अणु
	चयन (data) अणु
	हाल PS2_RET_ACK:
		ps2dev->nak = 0;
		अवरोध;

	हाल PS2_RET_NAK:
		ps2dev->flags |= PS2_FLAG_NAK;
		ps2dev->nak = PS2_RET_NAK;
		अवरोध;

	हाल PS2_RET_ERR:
		अगर (ps2dev->flags & PS2_FLAG_NAK) अणु
			ps2dev->flags &= ~PS2_FLAG_NAK;
			ps2dev->nak = PS2_RET_ERR;
			अवरोध;
		पूर्ण
		fallthrough;

	/*
	 * Workaround क्रम mice which करोn't ACK the Get ID command.
	 * These are valid mouse IDs that we recognize.
	 */
	हाल 0x00:
	हाल 0x03:
	हाल 0x04:
		अगर (ps2dev->flags & PS2_FLAG_WAITID) अणु
			ps2dev->nak = 0;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		/*
		 * Do not संकेत errors अगर we get unexpected reply जबतक
		 * रुकोing क्रम an ACK to the initial (first) command byte:
		 * the device might not be quiesced yet and जारी
		 * delivering data.
		 * Note that we reset PS2_FLAG_WAITID flag, so the workaround
		 * क्रम mice not acknowledging the Get ID command only triggers
		 * on the 1st byte; अगर device spews data we really want to see
		 * a real ACK from it.
		 */
		dev_dbg(&ps2dev->serio->dev, "unexpected %#02x\n", data);
		ps2dev->flags &= ~PS2_FLAG_WAITID;
		वापस ps2dev->flags & PS2_FLAG_ACK_CMD;
	पूर्ण

	अगर (!ps2dev->nak) अणु
		ps2dev->flags &= ~PS2_FLAG_NAK;
		अगर (ps2dev->cmdcnt)
			ps2dev->flags |= PS2_FLAG_CMD | PS2_FLAG_CMD1;
	पूर्ण

	ps2dev->flags &= ~PS2_FLAG_ACK;
	wake_up(&ps2dev->रुको);

	अगर (data != PS2_RET_ACK)
		ps2_handle_response(ps2dev, data);

	वापस true;
पूर्ण
EXPORT_SYMBOL(ps2_handle_ack);

/*
 * ps2_handle_response() is supposed to be used in पूर्णांकerrupt handler
 * to properly store device's response to a command and notअगरy process
 * रुकोing क्रम completion of the command.
 */

bool ps2_handle_response(काष्ठा ps2dev *ps2dev, u8 data)
अणु
	अगर (ps2dev->cmdcnt)
		ps2dev->cmdbuf[--ps2dev->cmdcnt] = data;

	अगर (ps2dev->flags & PS2_FLAG_CMD1) अणु
		ps2dev->flags &= ~PS2_FLAG_CMD1;
		अगर (ps2dev->cmdcnt)
			wake_up(&ps2dev->रुको);
	पूर्ण

	अगर (!ps2dev->cmdcnt) अणु
		ps2dev->flags &= ~PS2_FLAG_CMD;
		wake_up(&ps2dev->रुको);
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(ps2_handle_response);

व्योम ps2_cmd_पातed(काष्ठा ps2dev *ps2dev)
अणु
	अगर (ps2dev->flags & PS2_FLAG_ACK)
		ps2dev->nak = 1;

	अगर (ps2dev->flags & (PS2_FLAG_ACK | PS2_FLAG_CMD))
		wake_up(&ps2dev->रुको);

	/* reset all flags except last nack */
	ps2dev->flags &= PS2_FLAG_NAK;
पूर्ण
EXPORT_SYMBOL(ps2_cmd_पातed);
