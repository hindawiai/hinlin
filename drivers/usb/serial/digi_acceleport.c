<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
*  Digi AccelePort USB-4 and USB-2 Serial Converters
*
*  Copyright 2000 by Digi International
*
*  Shamelessly based on Brian Warner's keyspan_pda.c and Greg Kroah-Hartman's
*  usb-serial driver.
*
*  Peter Berger (pberger@brimson.com)
*  Al Borchers (borchers@steinerpoपूर्णांक.com)
*/

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/usb/serial.h>

/* Defines */

#घोषणा DRIVER_AUTHOR "Peter Berger <pberger@brimson.com>, Al Borchers <borchers@steinerpoint.com>"
#घोषणा DRIVER_DESC "Digi AccelePort USB-2/USB-4 Serial Converter driver"

/* port output buffer length -- must be <= transfer buffer length - 2 */
/* so we can be sure to send the full buffer in one urb */
#घोषणा DIGI_OUT_BUF_SIZE		8

/* port input buffer length -- must be >= transfer buffer length - 3 */
/* so we can be sure to hold at least one full buffer from one urb */
#घोषणा DIGI_IN_BUF_SIZE		64

/* retry समयout जबतक sleeping */
#घोषणा DIGI_RETRY_TIMEOUT		(HZ/10)

/* समयout जबतक रुकोing क्रम tty output to drain in बंद */
/* this delay is used twice in बंद, so the total delay could */
/* be twice this value */
#घोषणा DIGI_CLOSE_TIMEOUT		(5*HZ)


/* AccelePort USB Defines */

/* ids */
#घोषणा DIGI_VENDOR_ID			0x05c5
#घोषणा DIGI_2_ID			0x0002	/* USB-2 */
#घोषणा DIGI_4_ID			0x0004	/* USB-4 */

/* commands
 * "INB": can be used on the in-band endpoपूर्णांक
 * "OOB": can be used on the out-of-band endpoपूर्णांक
 */
#घोषणा DIGI_CMD_SET_BAUD_RATE			0	/* INB, OOB */
#घोषणा DIGI_CMD_SET_WORD_SIZE			1	/* INB, OOB */
#घोषणा DIGI_CMD_SET_PARITY			2	/* INB, OOB */
#घोषणा DIGI_CMD_SET_STOP_BITS			3	/* INB, OOB */
#घोषणा DIGI_CMD_SET_INPUT_FLOW_CONTROL		4	/* INB, OOB */
#घोषणा DIGI_CMD_SET_OUTPUT_FLOW_CONTROL	5	/* INB, OOB */
#घोषणा DIGI_CMD_SET_DTR_SIGNAL			6	/* INB, OOB */
#घोषणा DIGI_CMD_SET_RTS_SIGNAL			7	/* INB, OOB */
#घोषणा DIGI_CMD_READ_INPUT_SIGNALS		8	/*      OOB */
#घोषणा DIGI_CMD_IFLUSH_FIFO			9	/*      OOB */
#घोषणा DIGI_CMD_RECEIVE_ENABLE			10	/* INB, OOB */
#घोषणा DIGI_CMD_BREAK_CONTROL			11	/* INB, OOB */
#घोषणा DIGI_CMD_LOCAL_LOOPBACK			12	/* INB, OOB */
#घोषणा DIGI_CMD_TRANSMIT_IDLE			13	/* INB, OOB */
#घोषणा DIGI_CMD_READ_UART_REGISTER		14	/*      OOB */
#घोषणा DIGI_CMD_WRITE_UART_REGISTER		15	/* INB, OOB */
#घोषणा DIGI_CMD_AND_UART_REGISTER		16	/* INB, OOB */
#घोषणा DIGI_CMD_OR_UART_REGISTER		17	/* INB, OOB */
#घोषणा DIGI_CMD_SEND_DATA			18	/* INB      */
#घोषणा DIGI_CMD_RECEIVE_DATA			19	/* INB      */
#घोषणा DIGI_CMD_RECEIVE_DISABLE		20	/* INB      */
#घोषणा DIGI_CMD_GET_PORT_TYPE			21	/*      OOB */

/* baud rates */
#घोषणा DIGI_BAUD_50				0
#घोषणा DIGI_BAUD_75				1
#घोषणा DIGI_BAUD_110				2
#घोषणा DIGI_BAUD_150				3
#घोषणा DIGI_BAUD_200				4
#घोषणा DIGI_BAUD_300				5
#घोषणा DIGI_BAUD_600				6
#घोषणा DIGI_BAUD_1200				7
#घोषणा DIGI_BAUD_1800				8
#घोषणा DIGI_BAUD_2400				9
#घोषणा DIGI_BAUD_4800				10
#घोषणा DIGI_BAUD_7200				11
#घोषणा DIGI_BAUD_9600				12
#घोषणा DIGI_BAUD_14400				13
#घोषणा DIGI_BAUD_19200				14
#घोषणा DIGI_BAUD_28800				15
#घोषणा DIGI_BAUD_38400				16
#घोषणा DIGI_BAUD_57600				17
#घोषणा DIGI_BAUD_76800				18
#घोषणा DIGI_BAUD_115200			19
#घोषणा DIGI_BAUD_153600			20
#घोषणा DIGI_BAUD_230400			21
#घोषणा DIGI_BAUD_460800			22

/* arguments */
#घोषणा DIGI_WORD_SIZE_5			0
#घोषणा DIGI_WORD_SIZE_6			1
#घोषणा DIGI_WORD_SIZE_7			2
#घोषणा DIGI_WORD_SIZE_8			3

#घोषणा DIGI_PARITY_NONE			0
#घोषणा DIGI_PARITY_ODD				1
#घोषणा DIGI_PARITY_EVEN			2
#घोषणा DIGI_PARITY_MARK			3
#घोषणा DIGI_PARITY_SPACE			4

#घोषणा DIGI_STOP_BITS_1			0
#घोषणा DIGI_STOP_BITS_2			1

#घोषणा DIGI_INPUT_FLOW_CONTROL_XON_XOFF	1
#घोषणा DIGI_INPUT_FLOW_CONTROL_RTS		2
#घोषणा DIGI_INPUT_FLOW_CONTROL_DTR		4

#घोषणा DIGI_OUTPUT_FLOW_CONTROL_XON_XOFF	1
#घोषणा DIGI_OUTPUT_FLOW_CONTROL_CTS		2
#घोषणा DIGI_OUTPUT_FLOW_CONTROL_DSR		4

#घोषणा DIGI_DTR_INACTIVE			0
#घोषणा DIGI_DTR_ACTIVE				1
#घोषणा DIGI_DTR_INPUT_FLOW_CONTROL		2

#घोषणा DIGI_RTS_INACTIVE			0
#घोषणा DIGI_RTS_ACTIVE				1
#घोषणा DIGI_RTS_INPUT_FLOW_CONTROL		2
#घोषणा DIGI_RTS_TOGGLE				3

#घोषणा DIGI_FLUSH_TX				1
#घोषणा DIGI_FLUSH_RX				2
#घोषणा DIGI_RESUME_TX				4 /* clears xoff condition */

#घोषणा DIGI_TRANSMIT_NOT_IDLE			0
#घोषणा DIGI_TRANSMIT_IDLE			1

#घोषणा DIGI_DISABLE				0
#घोषणा DIGI_ENABLE				1

#घोषणा DIGI_DEASSERT				0
#घोषणा DIGI_ASSERT				1

/* in band status codes */
#घोषणा DIGI_OVERRUN_ERROR			4
#घोषणा DIGI_PARITY_ERROR			8
#घोषणा DIGI_FRAMING_ERROR			16
#घोषणा DIGI_BREAK_ERROR			32

/* out of band status */
#घोषणा DIGI_NO_ERROR				0
#घोषणा DIGI_BAD_FIRST_PARAMETER		1
#घोषणा DIGI_BAD_SECOND_PARAMETER		2
#घोषणा DIGI_INVALID_LINE			3
#घोषणा DIGI_INVALID_OPCODE			4

/* input संकेतs */
#घोषणा DIGI_READ_INPUT_SIGNALS_SLOT		1
#घोषणा DIGI_READ_INPUT_SIGNALS_ERR		2
#घोषणा DIGI_READ_INPUT_SIGNALS_BUSY		4
#घोषणा DIGI_READ_INPUT_SIGNALS_PE		8
#घोषणा DIGI_READ_INPUT_SIGNALS_CTS		16
#घोषणा DIGI_READ_INPUT_SIGNALS_DSR		32
#घोषणा DIGI_READ_INPUT_SIGNALS_RI		64
#घोषणा DIGI_READ_INPUT_SIGNALS_DCD		128


/* Structures */

काष्ठा digi_serial अणु
	spinlock_t ds_serial_lock;
	काष्ठा usb_serial_port *ds_oob_port;	/* out-of-band port */
	पूर्णांक ds_oob_port_num;			/* index of out-of-band port */
	पूर्णांक ds_device_started;
पूर्ण;

काष्ठा digi_port अणु
	spinlock_t dp_port_lock;
	पूर्णांक dp_port_num;
	पूर्णांक dp_out_buf_len;
	अचिन्हित अक्षर dp_out_buf[DIGI_OUT_BUF_SIZE];
	पूर्णांक dp_ग_लिखो_urb_in_use;
	अचिन्हित पूर्णांक dp_modem_संकेतs;
	पूर्णांक dp_transmit_idle;
	रुको_queue_head_t dp_transmit_idle_रुको;
	पूर्णांक dp_throttled;
	पूर्णांक dp_throttle_restart;
	रुको_queue_head_t dp_flush_रुको;
	रुको_queue_head_t dp_बंद_रुको;	/* रुको queue क्रम बंद */
	रुको_queue_head_t ग_लिखो_रुको;
	काष्ठा usb_serial_port *dp_port;
पूर्ण;


/* Local Function Declarations */

अटल पूर्णांक digi_ग_लिखो_oob_command(काष्ठा usb_serial_port *port,
	अचिन्हित अक्षर *buf, पूर्णांक count, पूर्णांक पूर्णांकerruptible);
अटल पूर्णांक digi_ग_लिखो_inb_command(काष्ठा usb_serial_port *port,
	अचिन्हित अक्षर *buf, पूर्णांक count, अचिन्हित दीर्घ समयout);
अटल पूर्णांक digi_set_modem_संकेतs(काष्ठा usb_serial_port *port,
	अचिन्हित पूर्णांक modem_संकेतs, पूर्णांक पूर्णांकerruptible);
अटल पूर्णांक digi_transmit_idle(काष्ठा usb_serial_port *port,
	अचिन्हित दीर्घ समयout);
अटल व्योम digi_rx_throttle(काष्ठा tty_काष्ठा *tty);
अटल व्योम digi_rx_unthrottle(काष्ठा tty_काष्ठा *tty);
अटल व्योम digi_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios);
अटल व्योम digi_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state);
अटल पूर्णांक digi_tiocmget(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक digi_tiocmset(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक set,
		अचिन्हित पूर्णांक clear);
अटल पूर्णांक digi_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
		स्थिर अचिन्हित अक्षर *buf, पूर्णांक count);
अटल व्योम digi_ग_लिखो_bulk_callback(काष्ठा urb *urb);
अटल पूर्णांक digi_ग_लिखो_room(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक digi_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक digi_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port);
अटल व्योम digi_बंद(काष्ठा usb_serial_port *port);
अटल व्योम digi_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on);
अटल पूर्णांक digi_startup_device(काष्ठा usb_serial *serial);
अटल पूर्णांक digi_startup(काष्ठा usb_serial *serial);
अटल व्योम digi_disconnect(काष्ठा usb_serial *serial);
अटल व्योम digi_release(काष्ठा usb_serial *serial);
अटल पूर्णांक digi_port_probe(काष्ठा usb_serial_port *port);
अटल व्योम digi_port_हटाओ(काष्ठा usb_serial_port *port);
अटल व्योम digi_पढ़ो_bulk_callback(काष्ठा urb *urb);
अटल पूर्णांक digi_पढ़ो_inb_callback(काष्ठा urb *urb);
अटल पूर्णांक digi_पढ़ो_oob_callback(काष्ठा urb *urb);


अटल स्थिर काष्ठा usb_device_id id_table_combined[] = अणु
	अणु USB_DEVICE(DIGI_VENDOR_ID, DIGI_2_ID) पूर्ण,
	अणु USB_DEVICE(DIGI_VENDOR_ID, DIGI_4_ID) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id id_table_2[] = अणु
	अणु USB_DEVICE(DIGI_VENDOR_ID, DIGI_2_ID) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id id_table_4[] = अणु
	अणु USB_DEVICE(DIGI_VENDOR_ID, DIGI_4_ID) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table_combined);

/* device info needed क्रम the Digi serial converter */

अटल काष्ठा usb_serial_driver digi_acceleport_2_device = अणु
	.driver = अणु
		.owner =		THIS_MODULE,
		.name =			"digi_2",
	पूर्ण,
	.description =			"Digi 2 port USB adapter",
	.id_table =			id_table_2,
	.num_ports =			3,
	.num_bulk_in =			4,
	.num_bulk_out =			4,
	.खोलो =				digi_खोलो,
	.बंद =			digi_बंद,
	.dtr_rts =			digi_dtr_rts,
	.ग_लिखो =			digi_ग_लिखो,
	.ग_लिखो_room =			digi_ग_लिखो_room,
	.ग_लिखो_bulk_callback = 		digi_ग_लिखो_bulk_callback,
	.पढ़ो_bulk_callback =		digi_पढ़ो_bulk_callback,
	.अक्षरs_in_buffer =		digi_अक्षरs_in_buffer,
	.throttle =			digi_rx_throttle,
	.unthrottle =			digi_rx_unthrottle,
	.set_termios =			digi_set_termios,
	.अवरोध_ctl =			digi_अवरोध_ctl,
	.tiocmget =			digi_tiocmget,
	.tiocmset =			digi_tiocmset,
	.attach =			digi_startup,
	.disconnect =			digi_disconnect,
	.release =			digi_release,
	.port_probe =			digi_port_probe,
	.port_हटाओ =			digi_port_हटाओ,
पूर्ण;

अटल काष्ठा usb_serial_driver digi_acceleport_4_device = अणु
	.driver = अणु
		.owner =		THIS_MODULE,
		.name =			"digi_4",
	पूर्ण,
	.description =			"Digi 4 port USB adapter",
	.id_table =			id_table_4,
	.num_ports =			4,
	.num_bulk_in =			5,
	.num_bulk_out =			5,
	.खोलो =				digi_खोलो,
	.बंद =			digi_बंद,
	.ग_लिखो =			digi_ग_लिखो,
	.ग_लिखो_room =			digi_ग_लिखो_room,
	.ग_लिखो_bulk_callback = 		digi_ग_लिखो_bulk_callback,
	.पढ़ो_bulk_callback =		digi_पढ़ो_bulk_callback,
	.अक्षरs_in_buffer =		digi_अक्षरs_in_buffer,
	.throttle =			digi_rx_throttle,
	.unthrottle =			digi_rx_unthrottle,
	.set_termios =			digi_set_termios,
	.अवरोध_ctl =			digi_अवरोध_ctl,
	.tiocmget =			digi_tiocmget,
	.tiocmset =			digi_tiocmset,
	.attach =			digi_startup,
	.disconnect =			digi_disconnect,
	.release =			digi_release,
	.port_probe =			digi_port_probe,
	.port_हटाओ =			digi_port_हटाओ,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&digi_acceleport_2_device, &digi_acceleport_4_device, शून्य
पूर्ण;

/* Functions */

/*
 *  Cond Wait Interruptible Timeout Irqrestore
 *
 *  Do spin_unlock_irqrestore and पूर्णांकerruptible_sleep_on_समयout
 *  so that wake ups are not lost अगर they occur between the unlock
 *  and the sleep.  In other words, spin_unlock_irqrestore and
 *  पूर्णांकerruptible_sleep_on_समयout are "atomic" with respect to
 *  wake ups.  This is used to implement condition variables.
 *
 *  पूर्णांकerruptible_sleep_on_समयout is deprecated and has been replaced
 *  with the equivalent code.
 */

अटल दीर्घ cond_रुको_पूर्णांकerruptible_समयout_irqrestore(
	रुको_queue_head_t *q, दीर्घ समयout,
	spinlock_t *lock, अचिन्हित दीर्घ flags)
__releases(lock)
अणु
	DEFINE_WAIT(रुको);

	prepare_to_रुको(q, &रुको, TASK_INTERRUPTIBLE);
	spin_unlock_irqrestore(lock, flags);
	समयout = schedule_समयout(समयout);
	finish_रुको(q, &रुको);

	वापस समयout;
पूर्ण

/*
 *  Digi Write OOB Command
 *
 *  Write commands on the out of band port.  Commands are 4
 *  bytes each, multiple commands can be sent at once, and
 *  no command will be split across USB packets.  Returns 0
 *  अगर successful, -EINTR अगर पूर्णांकerrupted जबतक sleeping and
 *  the पूर्णांकerruptible flag is true, or a negative error
 *  वापसed by usb_submit_urb.
 */

अटल पूर्णांक digi_ग_लिखो_oob_command(काष्ठा usb_serial_port *port,
	अचिन्हित अक्षर *buf, पूर्णांक count, पूर्णांक पूर्णांकerruptible)
अणु
	पूर्णांक ret = 0;
	पूर्णांक len;
	काष्ठा usb_serial_port *oob_port = (काष्ठा usb_serial_port *)((काष्ठा digi_serial *)(usb_get_serial_data(port->serial)))->ds_oob_port;
	काष्ठा digi_port *oob_priv = usb_get_serial_port_data(oob_port);
	अचिन्हित दीर्घ flags = 0;

	dev_dbg(&port->dev,
		"digi_write_oob_command: TOP: port=%d, count=%d\n",
		oob_priv->dp_port_num, count);

	spin_lock_irqsave(&oob_priv->dp_port_lock, flags);
	जबतक (count > 0) अणु
		जबतक (oob_priv->dp_ग_लिखो_urb_in_use) अणु
			cond_रुको_पूर्णांकerruptible_समयout_irqrestore(
				&oob_priv->ग_लिखो_रुको, DIGI_RETRY_TIMEOUT,
				&oob_priv->dp_port_lock, flags);
			अगर (पूर्णांकerruptible && संकेत_pending(current))
				वापस -EINTR;
			spin_lock_irqsave(&oob_priv->dp_port_lock, flags);
		पूर्ण

		/* len must be a multiple of 4, so commands are not split */
		len = min(count, oob_port->bulk_out_size);
		अगर (len > 4)
			len &= ~3;
		स_नकल(oob_port->ग_लिखो_urb->transfer_buffer, buf, len);
		oob_port->ग_लिखो_urb->transfer_buffer_length = len;
		ret = usb_submit_urb(oob_port->ग_लिखो_urb, GFP_ATOMIC);
		अगर (ret == 0) अणु
			oob_priv->dp_ग_लिखो_urb_in_use = 1;
			count -= len;
			buf += len;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&oob_priv->dp_port_lock, flags);
	अगर (ret)
		dev_err(&port->dev, "%s: usb_submit_urb failed, ret=%d\n",
			__func__, ret);
	वापस ret;

पूर्ण


/*
 *  Digi Write In Band Command
 *
 *  Write commands on the given port.  Commands are 4
 *  bytes each, multiple commands can be sent at once, and
 *  no command will be split across USB packets.  If समयout
 *  is non-zero, ग_लिखो in band command will वापस after
 *  रुकोing unsuccessfully क्रम the URB status to clear क्रम
 *  समयout ticks.  Returns 0 अगर successful, or a negative
 *  error वापसed by digi_ग_लिखो.
 */

अटल पूर्णांक digi_ग_लिखो_inb_command(काष्ठा usb_serial_port *port,
	अचिन्हित अक्षर *buf, पूर्णांक count, अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक ret = 0;
	पूर्णांक len;
	काष्ठा digi_port *priv = usb_get_serial_port_data(port);
	अचिन्हित अक्षर *data = port->ग_लिखो_urb->transfer_buffer;
	अचिन्हित दीर्घ flags = 0;

	dev_dbg(&port->dev, "digi_write_inb_command: TOP: port=%d, count=%d\n",
		priv->dp_port_num, count);

	अगर (समयout)
		समयout += jअगरfies;
	अन्यथा
		समयout = अच_दीर्घ_उच्च;

	spin_lock_irqsave(&priv->dp_port_lock, flags);
	जबतक (count > 0 && ret == 0) अणु
		जबतक (priv->dp_ग_लिखो_urb_in_use &&
		       समय_beक्रमe(jअगरfies, समयout)) अणु
			cond_रुको_पूर्णांकerruptible_समयout_irqrestore(
				&priv->ग_लिखो_रुको, DIGI_RETRY_TIMEOUT,
				&priv->dp_port_lock, flags);
			अगर (संकेत_pending(current))
				वापस -EINTR;
			spin_lock_irqsave(&priv->dp_port_lock, flags);
		पूर्ण

		/* len must be a multiple of 4 and small enough to */
		/* guarantee the ग_लिखो will send buffered data first, */
		/* so commands are in order with data and not split */
		len = min(count, port->bulk_out_size-2-priv->dp_out_buf_len);
		अगर (len > 4)
			len &= ~3;

		/* ग_लिखो any buffered data first */
		अगर (priv->dp_out_buf_len > 0) अणु
			data[0] = DIGI_CMD_SEND_DATA;
			data[1] = priv->dp_out_buf_len;
			स_नकल(data + 2, priv->dp_out_buf,
				priv->dp_out_buf_len);
			स_नकल(data + 2 + priv->dp_out_buf_len, buf, len);
			port->ग_लिखो_urb->transfer_buffer_length
				= priv->dp_out_buf_len + 2 + len;
		पूर्ण अन्यथा अणु
			स_नकल(data, buf, len);
			port->ग_लिखो_urb->transfer_buffer_length = len;
		पूर्ण

		ret = usb_submit_urb(port->ग_लिखो_urb, GFP_ATOMIC);
		अगर (ret == 0) अणु
			priv->dp_ग_लिखो_urb_in_use = 1;
			priv->dp_out_buf_len = 0;
			count -= len;
			buf += len;
		पूर्ण

	पूर्ण
	spin_unlock_irqrestore(&priv->dp_port_lock, flags);

	अगर (ret)
		dev_err(&port->dev,
			"%s: usb_submit_urb failed, ret=%d, port=%d\n",
			__func__, ret, priv->dp_port_num);
	वापस ret;
पूर्ण


/*
 *  Digi Set Modem Signals
 *
 *  Sets or clears DTR and RTS on the port, according to the
 *  modem_संकेतs argument.  Use TIOCM_DTR and TIOCM_RTS flags
 *  क्रम the modem_संकेतs argument.  Returns 0 अगर successful,
 *  -EINTR अगर पूर्णांकerrupted जबतक sleeping, or a non-zero error
 *  वापसed by usb_submit_urb.
 */

अटल पूर्णांक digi_set_modem_संकेतs(काष्ठा usb_serial_port *port,
	अचिन्हित पूर्णांक modem_संकेतs, पूर्णांक पूर्णांकerruptible)
अणु

	पूर्णांक ret;
	काष्ठा digi_port *port_priv = usb_get_serial_port_data(port);
	काष्ठा usb_serial_port *oob_port = (काष्ठा usb_serial_port *) ((काष्ठा digi_serial *)(usb_get_serial_data(port->serial)))->ds_oob_port;
	काष्ठा digi_port *oob_priv = usb_get_serial_port_data(oob_port);
	अचिन्हित अक्षर *data = oob_port->ग_लिखो_urb->transfer_buffer;
	अचिन्हित दीर्घ flags = 0;


	dev_dbg(&port->dev,
		"digi_set_modem_signals: TOP: port=%d, modem_signals=0x%x\n",
		port_priv->dp_port_num, modem_संकेतs);

	spin_lock_irqsave(&oob_priv->dp_port_lock, flags);
	spin_lock(&port_priv->dp_port_lock);

	जबतक (oob_priv->dp_ग_लिखो_urb_in_use) अणु
		spin_unlock(&port_priv->dp_port_lock);
		cond_रुको_पूर्णांकerruptible_समयout_irqrestore(
			&oob_priv->ग_लिखो_रुको, DIGI_RETRY_TIMEOUT,
			&oob_priv->dp_port_lock, flags);
		अगर (पूर्णांकerruptible && संकेत_pending(current))
			वापस -EINTR;
		spin_lock_irqsave(&oob_priv->dp_port_lock, flags);
		spin_lock(&port_priv->dp_port_lock);
	पूर्ण
	data[0] = DIGI_CMD_SET_DTR_SIGNAL;
	data[1] = port_priv->dp_port_num;
	data[2] = (modem_संकेतs & TIOCM_DTR) ?
					DIGI_DTR_ACTIVE : DIGI_DTR_INACTIVE;
	data[3] = 0;
	data[4] = DIGI_CMD_SET_RTS_SIGNAL;
	data[5] = port_priv->dp_port_num;
	data[6] = (modem_संकेतs & TIOCM_RTS) ?
					DIGI_RTS_ACTIVE : DIGI_RTS_INACTIVE;
	data[7] = 0;

	oob_port->ग_लिखो_urb->transfer_buffer_length = 8;

	ret = usb_submit_urb(oob_port->ग_लिखो_urb, GFP_ATOMIC);
	अगर (ret == 0) अणु
		oob_priv->dp_ग_लिखो_urb_in_use = 1;
		port_priv->dp_modem_संकेतs &= ~(TIOCM_DTR | TIOCM_RTS);
		port_priv->dp_modem_संकेतs |=
				modem_संकेतs & (TIOCM_DTR | TIOCM_RTS);
	पूर्ण
	spin_unlock(&port_priv->dp_port_lock);
	spin_unlock_irqrestore(&oob_priv->dp_port_lock, flags);
	अगर (ret)
		dev_err(&port->dev, "%s: usb_submit_urb failed, ret=%d\n",
			__func__, ret);
	वापस ret;
पूर्ण

/*
 *  Digi Transmit Idle
 *
 *  Digi transmit idle रुकोs, up to समयout ticks, क्रम the transmitter
 *  to go idle.  It वापसs 0 अगर successful or a negative error.
 *
 *  There are race conditions here अगर more than one process is calling
 *  digi_transmit_idle on the same port at the same समय.  However, this
 *  is only called from बंद, and only one process can be in बंद on a
 *  port at a समय, so its ok.
 */

अटल पूर्णांक digi_transmit_idle(काष्ठा usb_serial_port *port,
	अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर buf[2];
	काष्ठा digi_port *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&priv->dp_port_lock, flags);
	priv->dp_transmit_idle = 0;
	spin_unlock_irqrestore(&priv->dp_port_lock, flags);

	buf[0] = DIGI_CMD_TRANSMIT_IDLE;
	buf[1] = 0;

	समयout += jअगरfies;

	ret = digi_ग_लिखो_inb_command(port, buf, 2, समयout - jअगरfies);
	अगर (ret != 0)
		वापस ret;

	spin_lock_irqsave(&priv->dp_port_lock, flags);

	जबतक (समय_beक्रमe(jअगरfies, समयout) && !priv->dp_transmit_idle) अणु
		cond_रुको_पूर्णांकerruptible_समयout_irqrestore(
			&priv->dp_transmit_idle_रुको, DIGI_RETRY_TIMEOUT,
			&priv->dp_port_lock, flags);
		अगर (संकेत_pending(current))
			वापस -EINTR;
		spin_lock_irqsave(&priv->dp_port_lock, flags);
	पूर्ण
	priv->dp_transmit_idle = 0;
	spin_unlock_irqrestore(&priv->dp_port_lock, flags);
	वापस 0;

पूर्ण


अटल व्योम digi_rx_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा digi_port *priv = usb_get_serial_port_data(port);

	/* stop receiving अक्षरacters by not resubmitting the पढ़ो urb */
	spin_lock_irqsave(&priv->dp_port_lock, flags);
	priv->dp_throttled = 1;
	priv->dp_throttle_restart = 0;
	spin_unlock_irqrestore(&priv->dp_port_lock, flags);
पूर्ण


अटल व्योम digi_rx_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा digi_port *priv = usb_get_serial_port_data(port);

	spin_lock_irqsave(&priv->dp_port_lock, flags);

	/* restart पढ़ो chain */
	अगर (priv->dp_throttle_restart)
		ret = usb_submit_urb(port->पढ़ो_urb, GFP_ATOMIC);

	/* turn throttle off */
	priv->dp_throttled = 0;
	priv->dp_throttle_restart = 0;

	spin_unlock_irqrestore(&priv->dp_port_lock, flags);

	अगर (ret)
		dev_err(&port->dev,
			"%s: usb_submit_urb failed, ret=%d, port=%d\n",
			__func__, ret, priv->dp_port_num);
पूर्ण


अटल व्योम digi_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा digi_port *priv = usb_get_serial_port_data(port);
	काष्ठा device *dev = &port->dev;
	अचिन्हित पूर्णांक अगरlag = tty->termios.c_अगरlag;
	अचिन्हित पूर्णांक cflag = tty->termios.c_cflag;
	अचिन्हित पूर्णांक old_अगरlag = old_termios->c_अगरlag;
	अचिन्हित पूर्णांक old_cflag = old_termios->c_cflag;
	अचिन्हित अक्षर buf[32];
	अचिन्हित पूर्णांक modem_संकेतs;
	पूर्णांक arg, ret;
	पूर्णांक i = 0;
	speed_t baud;

	dev_dbg(dev,
		"digi_set_termios: TOP: port=%d, iflag=0x%x, old_iflag=0x%x, cflag=0x%x, old_cflag=0x%x\n",
		priv->dp_port_num, अगरlag, old_अगरlag, cflag, old_cflag);

	/* set baud rate */
	baud = tty_get_baud_rate(tty);
	अगर (baud != tty_termios_baud_rate(old_termios)) अणु
		arg = -1;

		/* reनिश्चित DTR and (maybe) RTS on transition from B0 */
		अगर ((old_cflag & CBAUD) == B0) अणु
			/* करोn't set RTS अगर using hardware flow control */
			/* and throttling input */
			modem_संकेतs = TIOCM_DTR;
			अगर (!C_CRTSCTS(tty) || !tty_throttled(tty))
				modem_संकेतs |= TIOCM_RTS;
			digi_set_modem_संकेतs(port, modem_संकेतs, 1);
		पूर्ण
		चयन (baud) अणु
		/* drop DTR and RTS on transition to B0 */
		हाल 0: digi_set_modem_संकेतs(port, 0, 1); अवरोध;
		हाल 50: arg = DIGI_BAUD_50; अवरोध;
		हाल 75: arg = DIGI_BAUD_75; अवरोध;
		हाल 110: arg = DIGI_BAUD_110; अवरोध;
		हाल 150: arg = DIGI_BAUD_150; अवरोध;
		हाल 200: arg = DIGI_BAUD_200; अवरोध;
		हाल 300: arg = DIGI_BAUD_300; अवरोध;
		हाल 600: arg = DIGI_BAUD_600; अवरोध;
		हाल 1200: arg = DIGI_BAUD_1200; अवरोध;
		हाल 1800: arg = DIGI_BAUD_1800; अवरोध;
		हाल 2400: arg = DIGI_BAUD_2400; अवरोध;
		हाल 4800: arg = DIGI_BAUD_4800; अवरोध;
		हाल 9600: arg = DIGI_BAUD_9600; अवरोध;
		हाल 19200: arg = DIGI_BAUD_19200; अवरोध;
		हाल 38400: arg = DIGI_BAUD_38400; अवरोध;
		हाल 57600: arg = DIGI_BAUD_57600; अवरोध;
		हाल 115200: arg = DIGI_BAUD_115200; अवरोध;
		हाल 230400: arg = DIGI_BAUD_230400; अवरोध;
		हाल 460800: arg = DIGI_BAUD_460800; अवरोध;
		शेष:
			arg = DIGI_BAUD_9600;
			baud = 9600;
			अवरोध;
		पूर्ण
		अगर (arg != -1) अणु
			buf[i++] = DIGI_CMD_SET_BAUD_RATE;
			buf[i++] = priv->dp_port_num;
			buf[i++] = arg;
			buf[i++] = 0;
		पूर्ण
	पूर्ण
	/* set parity */
	tty->termios.c_cflag &= ~CMSPAR;

	अगर ((cflag & (PARENB | PARODD)) != (old_cflag & (PARENB | PARODD))) अणु
		अगर (cflag & PARENB) अणु
			अगर (cflag & PARODD)
				arg = DIGI_PARITY_ODD;
			अन्यथा
				arg = DIGI_PARITY_EVEN;
		पूर्ण अन्यथा अणु
			arg = DIGI_PARITY_NONE;
		पूर्ण
		buf[i++] = DIGI_CMD_SET_PARITY;
		buf[i++] = priv->dp_port_num;
		buf[i++] = arg;
		buf[i++] = 0;
	पूर्ण
	/* set word size */
	अगर ((cflag & CSIZE) != (old_cflag & CSIZE)) अणु
		arg = -1;
		चयन (cflag & CSIZE) अणु
		हाल CS5: arg = DIGI_WORD_SIZE_5; अवरोध;
		हाल CS6: arg = DIGI_WORD_SIZE_6; अवरोध;
		हाल CS7: arg = DIGI_WORD_SIZE_7; अवरोध;
		हाल CS8: arg = DIGI_WORD_SIZE_8; अवरोध;
		शेष:
			dev_dbg(dev,
				"digi_set_termios: can't handle word size %d\n",
				cflag & CSIZE);
			अवरोध;
		पूर्ण

		अगर (arg != -1) अणु
			buf[i++] = DIGI_CMD_SET_WORD_SIZE;
			buf[i++] = priv->dp_port_num;
			buf[i++] = arg;
			buf[i++] = 0;
		पूर्ण

	पूर्ण

	/* set stop bits */
	अगर ((cflag & CSTOPB) != (old_cflag & CSTOPB)) अणु

		अगर ((cflag & CSTOPB))
			arg = DIGI_STOP_BITS_2;
		अन्यथा
			arg = DIGI_STOP_BITS_1;

		buf[i++] = DIGI_CMD_SET_STOP_BITS;
		buf[i++] = priv->dp_port_num;
		buf[i++] = arg;
		buf[i++] = 0;

	पूर्ण

	/* set input flow control */
	अगर ((अगरlag & IXOFF) != (old_अगरlag & IXOFF) ||
			(cflag & CRTSCTS) != (old_cflag & CRTSCTS)) अणु
		arg = 0;
		अगर (अगरlag & IXOFF)
			arg |= DIGI_INPUT_FLOW_CONTROL_XON_XOFF;
		अन्यथा
			arg &= ~DIGI_INPUT_FLOW_CONTROL_XON_XOFF;

		अगर (cflag & CRTSCTS) अणु
			arg |= DIGI_INPUT_FLOW_CONTROL_RTS;

			/* On USB-4 it is necessary to निश्चित RTS prior */
			/* to selecting RTS input flow control.  */
			buf[i++] = DIGI_CMD_SET_RTS_SIGNAL;
			buf[i++] = priv->dp_port_num;
			buf[i++] = DIGI_RTS_ACTIVE;
			buf[i++] = 0;

		पूर्ण अन्यथा अणु
			arg &= ~DIGI_INPUT_FLOW_CONTROL_RTS;
		पूर्ण
		buf[i++] = DIGI_CMD_SET_INPUT_FLOW_CONTROL;
		buf[i++] = priv->dp_port_num;
		buf[i++] = arg;
		buf[i++] = 0;
	पूर्ण

	/* set output flow control */
	अगर ((अगरlag & IXON) != (old_अगरlag & IXON) ||
			(cflag & CRTSCTS) != (old_cflag & CRTSCTS)) अणु
		arg = 0;
		अगर (अगरlag & IXON)
			arg |= DIGI_OUTPUT_FLOW_CONTROL_XON_XOFF;
		अन्यथा
			arg &= ~DIGI_OUTPUT_FLOW_CONTROL_XON_XOFF;

		अगर (cflag & CRTSCTS)
			arg |= DIGI_OUTPUT_FLOW_CONTROL_CTS;
		अन्यथा
			arg &= ~DIGI_OUTPUT_FLOW_CONTROL_CTS;

		buf[i++] = DIGI_CMD_SET_OUTPUT_FLOW_CONTROL;
		buf[i++] = priv->dp_port_num;
		buf[i++] = arg;
		buf[i++] = 0;
	पूर्ण

	/* set receive enable/disable */
	अगर ((cflag & CREAD) != (old_cflag & CREAD)) अणु
		अगर (cflag & CREAD)
			arg = DIGI_ENABLE;
		अन्यथा
			arg = DIGI_DISABLE;

		buf[i++] = DIGI_CMD_RECEIVE_ENABLE;
		buf[i++] = priv->dp_port_num;
		buf[i++] = arg;
		buf[i++] = 0;
	पूर्ण
	ret = digi_ग_लिखो_oob_command(port, buf, i, 1);
	अगर (ret != 0)
		dev_dbg(dev, "digi_set_termios: write oob failed, ret=%d\n", ret);
	tty_encode_baud_rate(tty, baud, baud);
पूर्ण


अटल व्योम digi_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	अचिन्हित अक्षर buf[4];

	buf[0] = DIGI_CMD_BREAK_CONTROL;
	buf[1] = 2;				/* length */
	buf[2] = अवरोध_state ? 1 : 0;
	buf[3] = 0;				/* pad */
	digi_ग_लिखो_inb_command(port, buf, 4, 0);
पूर्ण


अटल पूर्णांक digi_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा digi_port *priv = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->dp_port_lock, flags);
	val = priv->dp_modem_संकेतs;
	spin_unlock_irqrestore(&priv->dp_port_lock, flags);
	वापस val;
पूर्ण


अटल पूर्णांक digi_tiocmset(काष्ठा tty_काष्ठा *tty,
					अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा digi_port *priv = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->dp_port_lock, flags);
	val = (priv->dp_modem_संकेतs & ~clear) | set;
	spin_unlock_irqrestore(&priv->dp_port_lock, flags);
	वापस digi_set_modem_संकेतs(port, val, 1);
पूर्ण


अटल पूर्णांक digi_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
					स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु

	पूर्णांक ret, data_len, new_len;
	काष्ठा digi_port *priv = usb_get_serial_port_data(port);
	अचिन्हित अक्षर *data = port->ग_लिखो_urb->transfer_buffer;
	अचिन्हित दीर्घ flags = 0;

	dev_dbg(&port->dev, "digi_write: TOP: port=%d, count=%d\n",
		priv->dp_port_num, count);

	/* copy user data (which can sleep) beक्रमe getting spin lock */
	count = min(count, port->bulk_out_size-2);
	count = min(64, count);

	/* be sure only one ग_लिखो proceeds at a समय */
	/* there are races on the port निजी buffer */
	spin_lock_irqsave(&priv->dp_port_lock, flags);

	/* रुको क्रम urb status clear to submit another urb */
	अगर (priv->dp_ग_लिखो_urb_in_use) अणु
		/* buffer data अगर count is 1 (probably put_अक्षर) अगर possible */
		अगर (count == 1 && priv->dp_out_buf_len < DIGI_OUT_BUF_SIZE) अणु
			priv->dp_out_buf[priv->dp_out_buf_len++] = *buf;
			new_len = 1;
		पूर्ण अन्यथा अणु
			new_len = 0;
		पूर्ण
		spin_unlock_irqrestore(&priv->dp_port_lock, flags);
		वापस new_len;
	पूर्ण

	/* allow space क्रम any buffered data and क्रम new data, up to */
	/* transfer buffer size - 2 (क्रम command and length bytes) */
	new_len = min(count, port->bulk_out_size-2-priv->dp_out_buf_len);
	data_len = new_len + priv->dp_out_buf_len;

	अगर (data_len == 0) अणु
		spin_unlock_irqrestore(&priv->dp_port_lock, flags);
		वापस 0;
	पूर्ण

	port->ग_लिखो_urb->transfer_buffer_length = data_len+2;

	*data++ = DIGI_CMD_SEND_DATA;
	*data++ = data_len;

	/* copy in buffered data first */
	स_नकल(data, priv->dp_out_buf, priv->dp_out_buf_len);
	data += priv->dp_out_buf_len;

	/* copy in new data */
	स_नकल(data, buf, new_len);

	ret = usb_submit_urb(port->ग_लिखो_urb, GFP_ATOMIC);
	अगर (ret == 0) अणु
		priv->dp_ग_लिखो_urb_in_use = 1;
		ret = new_len;
		priv->dp_out_buf_len = 0;
	पूर्ण

	/* वापस length of new data written, or error */
	spin_unlock_irqrestore(&priv->dp_port_lock, flags);
	अगर (ret < 0)
		dev_err_console(port,
			"%s: usb_submit_urb failed, ret=%d, port=%d\n",
			__func__, ret, priv->dp_port_num);
	dev_dbg(&port->dev, "digi_write: returning %d\n", ret);
	वापस ret;

पूर्ण

अटल व्योम digi_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु

	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा usb_serial *serial;
	काष्ठा digi_port *priv;
	काष्ठा digi_serial *serial_priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	पूर्णांक status = urb->status;
	bool wakeup;

	/* port and serial sanity check */
	अगर (port == शून्य || (priv = usb_get_serial_port_data(port)) == शून्य) अणु
		pr_err("%s: port or port->private is NULL, status=%d\n",
			__func__, status);
		वापस;
	पूर्ण
	serial = port->serial;
	अगर (serial == शून्य || (serial_priv = usb_get_serial_data(serial)) == शून्य) अणु
		dev_err(&port->dev,
			"%s: serial or serial->private is NULL, status=%d\n",
			__func__, status);
		वापस;
	पूर्ण

	/* handle oob callback */
	अगर (priv->dp_port_num == serial_priv->ds_oob_port_num) अणु
		dev_dbg(&port->dev, "digi_write_bulk_callback: oob callback\n");
		spin_lock_irqsave(&priv->dp_port_lock, flags);
		priv->dp_ग_लिखो_urb_in_use = 0;
		wake_up_पूर्णांकerruptible(&priv->ग_लिखो_रुको);
		spin_unlock_irqrestore(&priv->dp_port_lock, flags);
		वापस;
	पूर्ण

	/* try to send any buffered data on this port */
	wakeup = true;
	spin_lock_irqsave(&priv->dp_port_lock, flags);
	priv->dp_ग_लिखो_urb_in_use = 0;
	अगर (priv->dp_out_buf_len > 0) अणु
		*((अचिन्हित अक्षर *)(port->ग_लिखो_urb->transfer_buffer))
			= (अचिन्हित अक्षर)DIGI_CMD_SEND_DATA;
		*((अचिन्हित अक्षर *)(port->ग_लिखो_urb->transfer_buffer) + 1)
			= (अचिन्हित अक्षर)priv->dp_out_buf_len;
		port->ग_लिखो_urb->transfer_buffer_length =
						priv->dp_out_buf_len + 2;
		स_नकल(port->ग_लिखो_urb->transfer_buffer + 2, priv->dp_out_buf,
			priv->dp_out_buf_len);
		ret = usb_submit_urb(port->ग_लिखो_urb, GFP_ATOMIC);
		अगर (ret == 0) अणु
			priv->dp_ग_लिखो_urb_in_use = 1;
			priv->dp_out_buf_len = 0;
			wakeup = false;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&priv->dp_port_lock, flags);

	अगर (ret && ret != -EPERM)
		dev_err_console(port,
			"%s: usb_submit_urb failed, ret=%d, port=%d\n",
			__func__, ret, priv->dp_port_num);

	अगर (wakeup)
		tty_port_tty_wakeup(&port->port);
पूर्ण

अटल पूर्णांक digi_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा digi_port *priv = usb_get_serial_port_data(port);
	पूर्णांक room;
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&priv->dp_port_lock, flags);

	अगर (priv->dp_ग_लिखो_urb_in_use)
		room = 0;
	अन्यथा
		room = port->bulk_out_size - 2 - priv->dp_out_buf_len;

	spin_unlock_irqrestore(&priv->dp_port_lock, flags);
	dev_dbg(&port->dev, "digi_write_room: port=%d, room=%d\n", priv->dp_port_num, room);
	वापस room;

पूर्ण

अटल पूर्णांक digi_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा digi_port *priv = usb_get_serial_port_data(port);

	अगर (priv->dp_ग_लिखो_urb_in_use) अणु
		dev_dbg(&port->dev, "digi_chars_in_buffer: port=%d, chars=%d\n",
			priv->dp_port_num, port->bulk_out_size - 2);
		/* वापस(port->bulk_out_size - 2); */
		वापस 256;
	पूर्ण अन्यथा अणु
		dev_dbg(&port->dev, "digi_chars_in_buffer: port=%d, chars=%d\n",
			priv->dp_port_num, priv->dp_out_buf_len);
		वापस priv->dp_out_buf_len;
	पूर्ण

पूर्ण

अटल व्योम digi_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	/* Adjust DTR and RTS */
	digi_set_modem_संकेतs(port, on * (TIOCM_DTR | TIOCM_RTS), 1);
पूर्ण

अटल पूर्णांक digi_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर buf[32];
	काष्ठा digi_port *priv = usb_get_serial_port_data(port);
	काष्ठा ktermios not_termios;

	/* be sure the device is started up */
	अगर (digi_startup_device(port->serial) != 0)
		वापस -ENXIO;

	/* पढ़ो modem संकेतs स्वतःmatically whenever they change */
	buf[0] = DIGI_CMD_READ_INPUT_SIGNALS;
	buf[1] = priv->dp_port_num;
	buf[2] = DIGI_ENABLE;
	buf[3] = 0;

	/* flush fअगरos */
	buf[4] = DIGI_CMD_IFLUSH_FIFO;
	buf[5] = priv->dp_port_num;
	buf[6] = DIGI_FLUSH_TX | DIGI_FLUSH_RX;
	buf[7] = 0;

	ret = digi_ग_लिखो_oob_command(port, buf, 8, 1);
	अगर (ret != 0)
		dev_dbg(&port->dev, "digi_open: write oob failed, ret=%d\n", ret);

	/* set termios settings */
	अगर (tty) अणु
		not_termios.c_cflag = ~tty->termios.c_cflag;
		not_termios.c_अगरlag = ~tty->termios.c_अगरlag;
		digi_set_termios(tty, port, &not_termios);
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम digi_बंद(काष्ठा usb_serial_port *port)
अणु
	DEFINE_WAIT(रुको);
	पूर्णांक ret;
	अचिन्हित अक्षर buf[32];
	काष्ठा digi_port *priv = usb_get_serial_port_data(port);

	mutex_lock(&port->serial->disc_mutex);
	/* अगर disconnected, just clear flags */
	अगर (port->serial->disconnected)
		जाओ निकास;

	/* FIXME: Transmit idle beदीर्घs in the रुको_unti_sent path */
	digi_transmit_idle(port, DIGI_CLOSE_TIMEOUT);

	/* disable input flow control */
	buf[0] = DIGI_CMD_SET_INPUT_FLOW_CONTROL;
	buf[1] = priv->dp_port_num;
	buf[2] = DIGI_DISABLE;
	buf[3] = 0;

	/* disable output flow control */
	buf[4] = DIGI_CMD_SET_OUTPUT_FLOW_CONTROL;
	buf[5] = priv->dp_port_num;
	buf[6] = DIGI_DISABLE;
	buf[7] = 0;

	/* disable पढ़ोing modem संकेतs स्वतःmatically */
	buf[8] = DIGI_CMD_READ_INPUT_SIGNALS;
	buf[9] = priv->dp_port_num;
	buf[10] = DIGI_DISABLE;
	buf[11] = 0;

	/* disable receive */
	buf[12] = DIGI_CMD_RECEIVE_ENABLE;
	buf[13] = priv->dp_port_num;
	buf[14] = DIGI_DISABLE;
	buf[15] = 0;

	/* flush fअगरos */
	buf[16] = DIGI_CMD_IFLUSH_FIFO;
	buf[17] = priv->dp_port_num;
	buf[18] = DIGI_FLUSH_TX | DIGI_FLUSH_RX;
	buf[19] = 0;

	ret = digi_ग_लिखो_oob_command(port, buf, 20, 0);
	अगर (ret != 0)
		dev_dbg(&port->dev, "digi_close: write oob failed, ret=%d\n",
									ret);
	/* रुको क्रम final commands on oob port to complete */
	prepare_to_रुको(&priv->dp_flush_रुको, &रुको,
			TASK_INTERRUPTIBLE);
	schedule_समयout(DIGI_CLOSE_TIMEOUT);
	finish_रुको(&priv->dp_flush_रुको, &रुको);

	/* shutकरोwn any outstanding bulk ग_लिखोs */
	usb_समाप्त_urb(port->ग_लिखो_urb);
निकास:
	spin_lock_irq(&priv->dp_port_lock);
	priv->dp_ग_लिखो_urb_in_use = 0;
	wake_up_पूर्णांकerruptible(&priv->dp_बंद_रुको);
	spin_unlock_irq(&priv->dp_port_lock);
	mutex_unlock(&port->serial->disc_mutex);
पूर्ण


/*
 *  Digi Startup Device
 *
 *  Starts पढ़ोs on all ports.  Must be called AFTER startup, with
 *  urbs initialized.  Returns 0 अगर successful, non-zero error otherwise.
 */

अटल पूर्णांक digi_startup_device(काष्ठा usb_serial *serial)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा digi_serial *serial_priv = usb_get_serial_data(serial);
	काष्ठा usb_serial_port *port;

	/* be sure this happens exactly once */
	spin_lock(&serial_priv->ds_serial_lock);
	अगर (serial_priv->ds_device_started) अणु
		spin_unlock(&serial_priv->ds_serial_lock);
		वापस 0;
	पूर्ण
	serial_priv->ds_device_started = 1;
	spin_unlock(&serial_priv->ds_serial_lock);

	/* start पढ़ोing from each bulk in endpoपूर्णांक क्रम the device */
	/* set USB_DISABLE_SPD flag क्रम ग_लिखो bulk urbs */
	क्रम (i = 0; i < serial->type->num_ports + 1; i++) अणु
		port = serial->port[i];
		ret = usb_submit_urb(port->पढ़ो_urb, GFP_KERNEL);
		अगर (ret != 0) अणु
			dev_err(&port->dev,
				"%s: usb_submit_urb failed, ret=%d, port=%d\n",
				__func__, ret, i);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक digi_port_init(काष्ठा usb_serial_port *port, अचिन्हित port_num)
अणु
	काष्ठा digi_port *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	spin_lock_init(&priv->dp_port_lock);
	priv->dp_port_num = port_num;
	init_रुकोqueue_head(&priv->dp_transmit_idle_रुको);
	init_रुकोqueue_head(&priv->dp_flush_रुको);
	init_रुकोqueue_head(&priv->dp_बंद_रुको);
	init_रुकोqueue_head(&priv->ग_लिखो_रुको);
	priv->dp_port = port;

	usb_set_serial_port_data(port, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक digi_startup(काष्ठा usb_serial *serial)
अणु
	काष्ठा digi_serial *serial_priv;
	पूर्णांक ret;

	serial_priv = kzalloc(माप(*serial_priv), GFP_KERNEL);
	अगर (!serial_priv)
		वापस -ENOMEM;

	spin_lock_init(&serial_priv->ds_serial_lock);
	serial_priv->ds_oob_port_num = serial->type->num_ports;
	serial_priv->ds_oob_port = serial->port[serial_priv->ds_oob_port_num];

	ret = digi_port_init(serial_priv->ds_oob_port,
						serial_priv->ds_oob_port_num);
	अगर (ret) अणु
		kमुक्त(serial_priv);
		वापस ret;
	पूर्ण

	usb_set_serial_data(serial, serial_priv);

	वापस 0;
पूर्ण


अटल व्योम digi_disconnect(काष्ठा usb_serial *serial)
अणु
	पूर्णांक i;

	/* stop पढ़ोs and ग_लिखोs on all ports */
	क्रम (i = 0; i < serial->type->num_ports + 1; i++) अणु
		usb_समाप्त_urb(serial->port[i]->पढ़ो_urb);
		usb_समाप्त_urb(serial->port[i]->ग_लिखो_urb);
	पूर्ण
पूर्ण


अटल व्योम digi_release(काष्ठा usb_serial *serial)
अणु
	काष्ठा digi_serial *serial_priv;
	काष्ठा digi_port *priv;

	serial_priv = usb_get_serial_data(serial);

	priv = usb_get_serial_port_data(serial_priv->ds_oob_port);
	kमुक्त(priv);

	kमुक्त(serial_priv);
पूर्ण

अटल पूर्णांक digi_port_probe(काष्ठा usb_serial_port *port)
अणु
	वापस digi_port_init(port, port->port_number);
पूर्ण

अटल व्योम digi_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा digi_port *priv;

	priv = usb_get_serial_port_data(port);
	kमुक्त(priv);
पूर्ण

अटल व्योम digi_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा digi_port *priv;
	काष्ठा digi_serial *serial_priv;
	पूर्णांक ret;
	पूर्णांक status = urb->status;

	/* port sanity check, करो not resubmit अगर port is not valid */
	अगर (port == शून्य)
		वापस;
	priv = usb_get_serial_port_data(port);
	अगर (priv == शून्य) अणु
		dev_err(&port->dev, "%s: port->private is NULL, status=%d\n",
			__func__, status);
		वापस;
	पूर्ण
	अगर (port->serial == शून्य ||
		(serial_priv = usb_get_serial_data(port->serial)) == शून्य) अणु
		dev_err(&port->dev, "%s: serial is bad or serial->private "
			"is NULL, status=%d\n", __func__, status);
		वापस;
	पूर्ण

	/* करो not resubmit urb अगर it has any status error */
	अगर (status) अणु
		dev_err(&port->dev,
			"%s: nonzero read bulk status: status=%d, port=%d\n",
			__func__, status, priv->dp_port_num);
		वापस;
	पूर्ण

	/* handle oob or inb callback, करो not resubmit अगर error */
	अगर (priv->dp_port_num == serial_priv->ds_oob_port_num) अणु
		अगर (digi_पढ़ो_oob_callback(urb) != 0)
			वापस;
	पूर्ण अन्यथा अणु
		अगर (digi_पढ़ो_inb_callback(urb) != 0)
			वापस;
	पूर्ण

	/* जारी पढ़ो */
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret != 0 && ret != -EPERM) अणु
		dev_err(&port->dev,
			"%s: failed resubmitting urb, ret=%d, port=%d\n",
			__func__, ret, priv->dp_port_num);
	पूर्ण

पूर्ण

/*
 *  Digi Read INB Callback
 *
 *  Digi Read INB Callback handles पढ़ोs on the in band ports, sending
 *  the data on to the tty subप्रणाली.  When called we know port and
 *  port->निजी are not शून्य and port->serial has been validated.
 *  It वापसs 0 अगर successful, 1 अगर successful but the port is
 *  throttled, and -1 अगर the sanity checks failed.
 */

अटल पूर्णांक digi_पढ़ो_inb_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा digi_port *priv = usb_get_serial_port_data(port);
	अचिन्हित अक्षर *buf = urb->transfer_buffer;
	अचिन्हित दीर्घ flags;
	पूर्णांक opcode;
	पूर्णांक len;
	पूर्णांक port_status;
	अचिन्हित अक्षर *data;
	पूर्णांक tty_flag, throttled;

	/* लघु/multiple packet check */
	अगर (urb->actual_length < 2) अणु
		dev_warn(&port->dev, "short packet received\n");
		वापस -1;
	पूर्ण

	opcode = buf[0];
	len = buf[1];

	अगर (urb->actual_length != len + 2) अणु
		dev_err(&port->dev, "malformed packet received: port=%d, opcode=%d, len=%d, actual_length=%u\n",
			priv->dp_port_num, opcode, len, urb->actual_length);
		वापस -1;
	पूर्ण

	अगर (opcode == DIGI_CMD_RECEIVE_DATA && len < 1) अणु
		dev_err(&port->dev, "malformed data packet received\n");
		वापस -1;
	पूर्ण

	spin_lock_irqsave(&priv->dp_port_lock, flags);

	/* check क्रम throttle; अगर set, करो not resubmit पढ़ो urb */
	/* indicate the पढ़ो chain needs to be restarted on unthrottle */
	throttled = priv->dp_throttled;
	अगर (throttled)
		priv->dp_throttle_restart = 1;

	/* receive data */
	अगर (opcode == DIGI_CMD_RECEIVE_DATA) अणु
		port_status = buf[2];
		data = &buf[3];

		/* get flag from port_status */
		tty_flag = 0;

		/* overrun is special, not associated with a अक्षर */
		अगर (port_status & DIGI_OVERRUN_ERROR)
			tty_insert_flip_अक्षर(&port->port, 0, TTY_OVERRUN);

		/* अवरोध takes precedence over parity, */
		/* which takes precedence over framing errors */
		अगर (port_status & DIGI_BREAK_ERROR)
			tty_flag = TTY_BREAK;
		अन्यथा अगर (port_status & DIGI_PARITY_ERROR)
			tty_flag = TTY_PARITY;
		अन्यथा अगर (port_status & DIGI_FRAMING_ERROR)
			tty_flag = TTY_FRAME;

		/* data length is len-1 (one byte of len is port_status) */
		--len;
		अगर (len > 0) अणु
			tty_insert_flip_string_fixed_flag(&port->port, data,
					tty_flag, len);
			tty_flip_buffer_push(&port->port);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&priv->dp_port_lock, flags);

	अगर (opcode == DIGI_CMD_RECEIVE_DISABLE)
		dev_dbg(&port->dev, "%s: got RECEIVE_DISABLE\n", __func__);
	अन्यथा अगर (opcode != DIGI_CMD_RECEIVE_DATA)
		dev_dbg(&port->dev, "%s: unknown opcode: %d\n", __func__, opcode);

	वापस throttled ? 1 : 0;

पूर्ण


/*
 *  Digi Read OOB Callback
 *
 *  Digi Read OOB Callback handles पढ़ोs on the out of band port.
 *  When called we know port and port->निजी are not शून्य and
 *  the port->serial is valid.  It वापसs 0 अगर successful, and
 *  -1 अगर the sanity checks failed.
 */

अटल पूर्णांक digi_पढ़ो_oob_callback(काष्ठा urb *urb)
अणु

	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा tty_काष्ठा *tty;
	काष्ठा digi_port *priv;
	अचिन्हित अक्षर *buf = urb->transfer_buffer;
	पूर्णांक opcode, line, status, val;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	अचिन्हित पूर्णांक rts;

	अगर (urb->actual_length < 4)
		वापस -1;

	/* handle each oob command */
	क्रम (i = 0; i < urb->actual_length - 3; i += 4) अणु
		opcode = buf[i];
		line = buf[i + 1];
		status = buf[i + 2];
		val = buf[i + 3];

		dev_dbg(&port->dev, "digi_read_oob_callback: opcode=%d, line=%d, status=%d, val=%d\n",
			opcode, line, status, val);

		अगर (status != 0 || line >= serial->type->num_ports)
			जारी;

		port = serial->port[line];

		priv = usb_get_serial_port_data(port);
		अगर (priv == शून्य)
			वापस -1;

		tty = tty_port_tty_get(&port->port);

		rts = 0;
		अगर (tty)
			rts = C_CRTSCTS(tty);

		अगर (tty && opcode == DIGI_CMD_READ_INPUT_SIGNALS) अणु
			bool wakeup = false;

			spin_lock_irqsave(&priv->dp_port_lock, flags);
			/* convert from digi flags to termiox flags */
			अगर (val & DIGI_READ_INPUT_SIGNALS_CTS) अणु
				priv->dp_modem_संकेतs |= TIOCM_CTS;
				अगर (rts)
					wakeup = true;
			पूर्ण अन्यथा अणु
				priv->dp_modem_संकेतs &= ~TIOCM_CTS;
				/* port must be खोलो to use tty काष्ठा */
			पूर्ण
			अगर (val & DIGI_READ_INPUT_SIGNALS_DSR)
				priv->dp_modem_संकेतs |= TIOCM_DSR;
			अन्यथा
				priv->dp_modem_संकेतs &= ~TIOCM_DSR;
			अगर (val & DIGI_READ_INPUT_SIGNALS_RI)
				priv->dp_modem_संकेतs |= TIOCM_RI;
			अन्यथा
				priv->dp_modem_संकेतs &= ~TIOCM_RI;
			अगर (val & DIGI_READ_INPUT_SIGNALS_DCD)
				priv->dp_modem_संकेतs |= TIOCM_CD;
			अन्यथा
				priv->dp_modem_संकेतs &= ~TIOCM_CD;

			spin_unlock_irqrestore(&priv->dp_port_lock, flags);

			अगर (wakeup)
				tty_port_tty_wakeup(&port->port);
		पूर्ण अन्यथा अगर (opcode == DIGI_CMD_TRANSMIT_IDLE) अणु
			spin_lock_irqsave(&priv->dp_port_lock, flags);
			priv->dp_transmit_idle = 1;
			wake_up_पूर्णांकerruptible(&priv->dp_transmit_idle_रुको);
			spin_unlock_irqrestore(&priv->dp_port_lock, flags);
		पूर्ण अन्यथा अगर (opcode == DIGI_CMD_IFLUSH_FIFO) अणु
			wake_up_पूर्णांकerruptible(&priv->dp_flush_रुको);
		पूर्ण
		tty_kref_put(tty);
	पूर्ण
	वापस 0;

पूर्ण

module_usb_serial_driver(serial_drivers, id_table_combined);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
