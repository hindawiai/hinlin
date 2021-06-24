<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * MCT (Magic Control Technology Corp.) USB RS232 Converter Driver
 *
 *   Copyright (C) 2000 Wolfgang Gअक्रमegger (wolfgang@ces.ch)
 *
 * This program is largely derived from the Belkin USB Serial Adapter Driver
 * (see belkin_sa.[ch]). All of the inक्रमmation about the device was acquired
 * by using SnअगरfUSB on Winकरोws98. For technical details see mct_u232.h.
 *
 * William G. Greathouse and Greg Kroah-Harपंचांगan provided great help on how to
 * करो the reverse engineering and how to ग_लिखो a USB serial device driver.
 *
 * TO BE DONE, TO BE CHECKED:
 *   DTR/RTS संकेत handling may be incomplete or incorrect. I have मुख्यly
 *   implemented what I have seen with SnअगरfUSB or found in belkin_sa.c.
 *   For further TODOs check also belkin_sa.c.
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
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/serial.h>
#समावेश "mct_u232.h"

#घोषणा DRIVER_AUTHOR "Wolfgang Grandegger <wolfgang@ces.ch>"
#घोषणा DRIVER_DESC "Magic Control Technology USB-RS232 converter driver"

/*
 * Function prototypes
 */
अटल पूर्णांक  mct_u232_port_probe(काष्ठा usb_serial_port *port);
अटल व्योम mct_u232_port_हटाओ(काष्ठा usb_serial_port *हटाओ);
अटल पूर्णांक  mct_u232_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port);
अटल व्योम mct_u232_बंद(काष्ठा usb_serial_port *port);
अटल व्योम mct_u232_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on);
अटल व्योम mct_u232_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb);
अटल व्योम mct_u232_set_termios(काष्ठा tty_काष्ठा *tty,
			काष्ठा usb_serial_port *port, काष्ठा ktermios *old);
अटल व्योम mct_u232_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state);
अटल पूर्णांक  mct_u232_tiocmget(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक  mct_u232_tiocmset(काष्ठा tty_काष्ठा *tty,
			अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);
अटल व्योम mct_u232_throttle(काष्ठा tty_काष्ठा *tty);
अटल व्योम mct_u232_unthrottle(काष्ठा tty_काष्ठा *tty);


/*
 * All of the device info needed क्रम the MCT USB-RS232 converter.
 */
अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(MCT_U232_VID, MCT_U232_PID) पूर्ण,
	अणु USB_DEVICE(MCT_U232_VID, MCT_U232_SITECOM_PID) पूर्ण,
	अणु USB_DEVICE(MCT_U232_VID, MCT_U232_DU_H3SP_PID) पूर्ण,
	अणु USB_DEVICE(MCT_U232_BELKIN_F5U109_VID, MCT_U232_BELKIN_F5U109_PID) पूर्ण,
	अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

अटल काष्ठा usb_serial_driver mct_u232_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"mct_u232",
	पूर्ण,
	.description =	     "MCT U232",
	.id_table =	     id_table,
	.num_ports =	     1,
	.खोलो =		     mct_u232_खोलो,
	.बंद =	     mct_u232_बंद,
	.dtr_rts =	     mct_u232_dtr_rts,
	.throttle =	     mct_u232_throttle,
	.unthrottle =	     mct_u232_unthrottle,
	.पढ़ो_पूर्णांक_callback = mct_u232_पढ़ो_पूर्णांक_callback,
	.set_termios =	     mct_u232_set_termios,
	.अवरोध_ctl =	     mct_u232_अवरोध_ctl,
	.tiocmget =	     mct_u232_tiocmget,
	.tiocmset =	     mct_u232_tiocmset,
	.tiocmiरुको =        usb_serial_generic_tiocmiरुको,
	.port_probe =        mct_u232_port_probe,
	.port_हटाओ =       mct_u232_port_हटाओ,
	.get_icount =        usb_serial_generic_get_icount,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&mct_u232_device, शून्य
पूर्ण;

काष्ठा mct_u232_निजी अणु
	काष्ठा urb *पढ़ो_urb;
	spinlock_t lock;
	अचिन्हित पूर्णांक	     control_state; /* Modem Line Setting (TIOCM) */
	अचिन्हित अक्षर        last_lcr;      /* Line Control Register */
	अचिन्हित अक्षर	     last_lsr;      /* Line Status Register */
	अचिन्हित अक्षर	     last_msr;      /* Modem Status Register */
	अचिन्हित पूर्णांक	     rx_flags;      /* Throttling flags */
पूर्ण;

#घोषणा THROTTLED		0x01

/*
 * Handle venकरोr specअगरic USB requests
 */

#घोषणा WDR_TIMEOUT 5000 /* शेष urb समयout */

/*
 * Later day 2.6.0-test kernels have new baud rates like B230400 which
 * we करो not know how to support. We ignore them क्रम the moment.
 */
अटल पूर्णांक mct_u232_calculate_baud_rate(काष्ठा usb_serial *serial,
					speed_t value, speed_t *result)
अणु
	*result = value;

	अगर (le16_to_cpu(serial->dev->descriptor.idProduct) == MCT_U232_SITECOM_PID
		|| le16_to_cpu(serial->dev->descriptor.idProduct) == MCT_U232_BELKIN_F5U109_PID) अणु
		चयन (value) अणु
		हाल 300:
			वापस 0x01;
		हाल 600:
			वापस 0x02; /* this one not tested */
		हाल 1200:
			वापस 0x03;
		हाल 2400:
			वापस 0x04;
		हाल 4800:
			वापस 0x06;
		हाल 9600:
			वापस 0x08;
		हाल 19200:
			वापस 0x09;
		हाल 38400:
			वापस 0x0a;
		हाल 57600:
			वापस 0x0b;
		हाल 115200:
			वापस 0x0c;
		शेष:
			*result = 9600;
			वापस 0x08;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* FIXME: Can we use any भागider - should we करो
		   भागider = 115200/value;
		   real baud = 115200/भागider */
		चयन (value) अणु
		हाल 300: अवरोध;
		हाल 600: अवरोध;
		हाल 1200: अवरोध;
		हाल 2400: अवरोध;
		हाल 4800: अवरोध;
		हाल 9600: अवरोध;
		हाल 19200: अवरोध;
		हाल 38400: अवरोध;
		हाल 57600: अवरोध;
		हाल 115200: अवरोध;
		शेष:
			value = 9600;
			*result = 9600;
		पूर्ण
		वापस 115200/value;
	पूर्ण
पूर्ण

अटल पूर्णांक mct_u232_set_baud_rate(काष्ठा tty_काष्ठा *tty,
	काष्ठा usb_serial *serial, काष्ठा usb_serial_port *port, speed_t value)
अणु
	अचिन्हित पूर्णांक भागisor;
	पूर्णांक rc;
	अचिन्हित अक्षर *buf;
	अचिन्हित अक्षर cts_enable_byte = 0;
	speed_t speed;

	buf = kदो_स्मृति(MCT_U232_MAX_SIZE, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	भागisor = mct_u232_calculate_baud_rate(serial, value, &speed);
	put_unaligned_le32(भागisor, buf);
	rc = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
				MCT_U232_SET_BAUD_RATE_REQUEST,
				MCT_U232_SET_REQUEST_TYPE,
				0, 0, buf, MCT_U232_SET_BAUD_RATE_SIZE,
				WDR_TIMEOUT);
	अगर (rc < 0)	/*FIXME: What value speed results */
		dev_err(&port->dev, "Set BAUD RATE %d failed (error = %d)\n",
			value, rc);
	अन्यथा
		tty_encode_baud_rate(tty, speed, speed);
	dev_dbg(&port->dev, "set_baud_rate: value: 0x%x, divisor: 0x%x\n", value, भागisor);

	/* Mimic the MCT-supplied Winकरोws driver (version 1.21P.0104), which
	   always sends two extra USB 'device request' messages after the
	   'baud rate change' message.  The actual functionality of the
	   request codes in these messages is not fully understood but these
	   particular codes are never seen in any operation besides a baud
	   rate change.  Both of these messages send a single byte of data.
	   In the first message, the value of this byte is always zero.

	   The second message has been determined experimentally to control
	   whether data will be transmitted to a device which is not निश्चितing
	   the 'CTS' signal.  If the second message's data byte is zero, data
	   will be transmitted even अगर 'CTS' is not निश्चितed (i.e. no hardware
	   flow control).  अगर the second message's data byte is nonzero (a
	   value of 1 is used by this driver), data will not be transmitted to
	   a device which is not निश्चितing 'CTS'.
	*/

	buf[0] = 0;
	rc = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
				MCT_U232_SET_UNKNOWN1_REQUEST,
				MCT_U232_SET_REQUEST_TYPE,
				0, 0, buf, MCT_U232_SET_UNKNOWN1_SIZE,
				WDR_TIMEOUT);
	अगर (rc < 0)
		dev_err(&port->dev, "Sending USB device request code %d "
			"failed (error = %d)\n", MCT_U232_SET_UNKNOWN1_REQUEST,
			rc);

	अगर (port && C_CRTSCTS(tty))
	   cts_enable_byte = 1;

	dev_dbg(&port->dev, "set_baud_rate: send second control message, data = %02X\n",
		cts_enable_byte);
	buf[0] = cts_enable_byte;
	rc = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			MCT_U232_SET_CTS_REQUEST,
			MCT_U232_SET_REQUEST_TYPE,
			0, 0, buf, MCT_U232_SET_CTS_SIZE,
			WDR_TIMEOUT);
	अगर (rc < 0)
		dev_err(&port->dev, "Sending USB device request code %d "
			"failed (error = %d)\n", MCT_U232_SET_CTS_REQUEST, rc);

	kमुक्त(buf);
	वापस rc;
पूर्ण /* mct_u232_set_baud_rate */

अटल पूर्णांक mct_u232_set_line_ctrl(काष्ठा usb_serial_port *port,
				  अचिन्हित अक्षर lcr)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर *buf;

	buf = kदो_स्मृति(MCT_U232_MAX_SIZE, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	buf[0] = lcr;
	rc = usb_control_msg(port->serial->dev, usb_sndctrlpipe(port->serial->dev, 0),
			MCT_U232_SET_LINE_CTRL_REQUEST,
			MCT_U232_SET_REQUEST_TYPE,
			0, 0, buf, MCT_U232_SET_LINE_CTRL_SIZE,
			WDR_TIMEOUT);
	अगर (rc < 0)
		dev_err(&port->dev, "Set LINE CTRL 0x%x failed (error = %d)\n", lcr, rc);
	dev_dbg(&port->dev, "set_line_ctrl: 0x%x\n", lcr);
	kमुक्त(buf);
	वापस rc;
पूर्ण /* mct_u232_set_line_ctrl */

अटल पूर्णांक mct_u232_set_modem_ctrl(काष्ठा usb_serial_port *port,
				   अचिन्हित पूर्णांक control_state)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर mcr;
	अचिन्हित अक्षर *buf;

	buf = kदो_स्मृति(MCT_U232_MAX_SIZE, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	mcr = MCT_U232_MCR_NONE;
	अगर (control_state & TIOCM_DTR)
		mcr |= MCT_U232_MCR_DTR;
	अगर (control_state & TIOCM_RTS)
		mcr |= MCT_U232_MCR_RTS;

	buf[0] = mcr;
	rc = usb_control_msg(port->serial->dev, usb_sndctrlpipe(port->serial->dev, 0),
			MCT_U232_SET_MODEM_CTRL_REQUEST,
			MCT_U232_SET_REQUEST_TYPE,
			0, 0, buf, MCT_U232_SET_MODEM_CTRL_SIZE,
			WDR_TIMEOUT);
	kमुक्त(buf);

	dev_dbg(&port->dev, "set_modem_ctrl: state=0x%x ==> mcr=0x%x\n", control_state, mcr);

	अगर (rc < 0) अणु
		dev_err(&port->dev, "Set MODEM CTRL 0x%x failed (error = %d)\n", mcr, rc);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण /* mct_u232_set_modem_ctrl */

अटल पूर्णांक mct_u232_get_modem_stat(काष्ठा usb_serial_port *port,
				   अचिन्हित अक्षर *msr)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर *buf;

	buf = kदो_स्मृति(MCT_U232_MAX_SIZE, GFP_KERNEL);
	अगर (buf == शून्य) अणु
		*msr = 0;
		वापस -ENOMEM;
	पूर्ण
	rc = usb_control_msg(port->serial->dev, usb_rcvctrlpipe(port->serial->dev, 0),
			MCT_U232_GET_MODEM_STAT_REQUEST,
			MCT_U232_GET_REQUEST_TYPE,
			0, 0, buf, MCT_U232_GET_MODEM_STAT_SIZE,
			WDR_TIMEOUT);
	अगर (rc < MCT_U232_GET_MODEM_STAT_SIZE) अणु
		dev_err(&port->dev, "Get MODEM STATus failed (error = %d)\n", rc);

		अगर (rc >= 0)
			rc = -EIO;

		*msr = 0;
	पूर्ण अन्यथा अणु
		*msr = buf[0];
	पूर्ण
	dev_dbg(&port->dev, "get_modem_stat: 0x%x\n", *msr);
	kमुक्त(buf);
	वापस rc;
पूर्ण /* mct_u232_get_modem_stat */

अटल व्योम mct_u232_msr_to_icount(काष्ठा async_icount *icount,
						अचिन्हित अक्षर msr)
अणु
	/* Translate Control Line states */
	अगर (msr & MCT_U232_MSR_DDSR)
		icount->dsr++;
	अगर (msr & MCT_U232_MSR_DCTS)
		icount->cts++;
	अगर (msr & MCT_U232_MSR_DRI)
		icount->rng++;
	अगर (msr & MCT_U232_MSR_DCD)
		icount->dcd++;
पूर्ण /* mct_u232_msr_to_icount */

अटल व्योम mct_u232_msr_to_state(काष्ठा usb_serial_port *port,
				  अचिन्हित पूर्णांक *control_state, अचिन्हित अक्षर msr)
अणु
	/* Translate Control Line states */
	अगर (msr & MCT_U232_MSR_DSR)
		*control_state |=  TIOCM_DSR;
	अन्यथा
		*control_state &= ~TIOCM_DSR;
	अगर (msr & MCT_U232_MSR_CTS)
		*control_state |=  TIOCM_CTS;
	अन्यथा
		*control_state &= ~TIOCM_CTS;
	अगर (msr & MCT_U232_MSR_RI)
		*control_state |=  TIOCM_RI;
	अन्यथा
		*control_state &= ~TIOCM_RI;
	अगर (msr & MCT_U232_MSR_CD)
		*control_state |=  TIOCM_CD;
	अन्यथा
		*control_state &= ~TIOCM_CD;
	dev_dbg(&port->dev, "msr_to_state: msr=0x%x ==> state=0x%x\n", msr, *control_state);
पूर्ण /* mct_u232_msr_to_state */

/*
 * Driver's tty पूर्णांकerface functions
 */

अटल पूर्णांक mct_u232_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा mct_u232_निजी *priv;

	/* check first to simplअगरy error handling */
	अगर (!serial->port[1] || !serial->port[1]->पूर्णांकerrupt_in_urb) अणु
		dev_err(&port->dev, "expected endpoint missing\n");
		वापस -ENODEV;
	पूर्ण

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* Use second पूर्णांकerrupt-in endpoपूर्णांक क्रम पढ़ोing. */
	priv->पढ़ो_urb = serial->port[1]->पूर्णांकerrupt_in_urb;
	priv->पढ़ो_urb->context = port;

	spin_lock_init(&priv->lock);

	usb_set_serial_port_data(port, priv);

	वापस 0;
पूर्ण

अटल व्योम mct_u232_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा mct_u232_निजी *priv;

	priv = usb_get_serial_port_data(port);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक  mct_u232_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा mct_u232_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक retval = 0;
	अचिन्हित पूर्णांक control_state;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर last_lcr;
	अचिन्हित अक्षर last_msr;

	/* Compensate क्रम a hardware bug: although the Sitecom U232-P25
	 * device reports a maximum output packet size of 32 bytes,
	 * it seems to be able to accept only 16 bytes (and that's what
	 * SnअगरfUSB says too...)
	 */
	अगर (le16_to_cpu(serial->dev->descriptor.idProduct)
						== MCT_U232_SITECOM_PID)
		port->bulk_out_size = 16;

	/* Do a defined restart: the normal serial device seems to
	 * always turn on DTR and RTS here, so करो the same. I'm not
	 * sure अगर this is really necessary. But it should not harm
	 * either.
	 */
	spin_lock_irqsave(&priv->lock, flags);
	अगर (tty && C_BAUD(tty))
		priv->control_state = TIOCM_DTR | TIOCM_RTS;
	अन्यथा
		priv->control_state = 0;

	priv->last_lcr = (MCT_U232_DATA_BITS_8 |
			  MCT_U232_PARITY_NONE |
			  MCT_U232_STOP_BITS_1);
	control_state = priv->control_state;
	last_lcr = priv->last_lcr;
	spin_unlock_irqrestore(&priv->lock, flags);
	mct_u232_set_modem_ctrl(port, control_state);
	mct_u232_set_line_ctrl(port, last_lcr);

	/* Read modem status and update control state */
	mct_u232_get_modem_stat(port, &last_msr);
	spin_lock_irqsave(&priv->lock, flags);
	priv->last_msr = last_msr;
	mct_u232_msr_to_state(port, &priv->control_state, priv->last_msr);
	spin_unlock_irqrestore(&priv->lock, flags);

	retval = usb_submit_urb(priv->पढ़ो_urb, GFP_KERNEL);
	अगर (retval) अणु
		dev_err(&port->dev,
			"usb_submit_urb(read) failed pipe 0x%x err %d\n",
			port->पढ़ो_urb->pipe, retval);
		जाओ error;
	पूर्ण

	retval = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
	अगर (retval) अणु
		usb_समाप्त_urb(priv->पढ़ो_urb);
		dev_err(&port->dev,
			"usb_submit_urb(read int) failed pipe 0x%x err %d",
			port->पूर्णांकerrupt_in_urb->pipe, retval);
		जाओ error;
	पूर्ण
	वापस 0;

error:
	वापस retval;
पूर्ण /* mct_u232_खोलो */

अटल व्योम mct_u232_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	अचिन्हित पूर्णांक control_state;
	काष्ठा mct_u232_निजी *priv = usb_get_serial_port_data(port);

	spin_lock_irq(&priv->lock);
	अगर (on)
		priv->control_state |= TIOCM_DTR | TIOCM_RTS;
	अन्यथा
		priv->control_state &= ~(TIOCM_DTR | TIOCM_RTS);
	control_state = priv->control_state;
	spin_unlock_irq(&priv->lock);

	mct_u232_set_modem_ctrl(port, control_state);
पूर्ण

अटल व्योम mct_u232_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा mct_u232_निजी *priv = usb_get_serial_port_data(port);

	usb_समाप्त_urb(priv->पढ़ो_urb);
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);

	usb_serial_generic_बंद(port);
पूर्ण /* mct_u232_बंद */


अटल व्योम mct_u232_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा mct_u232_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	पूर्णांक retval;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&port->dev, "%s - urb shutting down with status: %d\n",
			__func__, status);
		वापस;
	शेष:
		dev_dbg(&port->dev, "%s - nonzero urb status received: %d\n",
			__func__, status);
		जाओ निकास;
	पूर्ण

	usb_serial_debug_data(&port->dev, __func__, urb->actual_length, data);

	/*
	 * Work-a-round: handle the 'usual' bulk-in pipe here
	 */
	अगर (urb->transfer_buffer_length > 2) अणु
		अगर (urb->actual_length) अणु
			tty_insert_flip_string(&port->port, data,
					urb->actual_length);
			tty_flip_buffer_push(&port->port);
		पूर्ण
		जाओ निकास;
	पूर्ण

	/*
	 * The पूर्णांकerrupt-in pipe संकेतs exceptional conditions (modem line
	 * संकेत changes and errors). data[0] holds MSR, data[1] holds LSR.
	 */
	spin_lock_irqsave(&priv->lock, flags);
	priv->last_msr = data[MCT_U232_MSR_INDEX];

	/* Record Control Line states */
	mct_u232_msr_to_state(port, &priv->control_state, priv->last_msr);

	mct_u232_msr_to_icount(&port->icount, priv->last_msr);

#अगर 0
	/* Not yet handled. See belkin_sa.c क्रम further inक्रमmation */
	/* Now to report any errors */
	priv->last_lsr = data[MCT_U232_LSR_INDEX];
	/*
	 * fill in the flip buffer here, but I करो not know the relation
	 * to the current/next receive buffer or अक्षरacters.  I need
	 * to look in to this beक्रमe committing any code.
	 */
	अगर (priv->last_lsr & MCT_U232_LSR_ERR) अणु
		tty = tty_port_tty_get(&port->port);
		/* Overrun Error */
		अगर (priv->last_lsr & MCT_U232_LSR_OE) अणु
		पूर्ण
		/* Parity Error */
		अगर (priv->last_lsr & MCT_U232_LSR_PE) अणु
		पूर्ण
		/* Framing Error */
		अगर (priv->last_lsr & MCT_U232_LSR_FE) अणु
		पूर्ण
		/* Break Indicator */
		अगर (priv->last_lsr & MCT_U232_LSR_BI) अणु
		पूर्ण
		tty_kref_put(tty);
	पूर्ण
#पूर्ण_अगर
	wake_up_पूर्णांकerruptible(&port->port.delta_msr_रुको);
	spin_unlock_irqrestore(&priv->lock, flags);
निकास:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&port->dev,
			"%s - usb_submit_urb failed with result %d\n",
			__func__, retval);
पूर्ण /* mct_u232_पढ़ो_पूर्णांक_callback */

अटल व्योम mct_u232_set_termios(काष्ठा tty_काष्ठा *tty,
				 काष्ठा usb_serial_port *port,
				 काष्ठा ktermios *old_termios)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा mct_u232_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा ktermios *termios = &tty->termios;
	अचिन्हित पूर्णांक cflag = termios->c_cflag;
	अचिन्हित पूर्णांक old_cflag = old_termios->c_cflag;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक control_state;
	अचिन्हित अक्षर last_lcr;

	/* get a local copy of the current port settings */
	spin_lock_irqsave(&priv->lock, flags);
	control_state = priv->control_state;
	spin_unlock_irqrestore(&priv->lock, flags);
	last_lcr = 0;

	/*
	 * Update baud rate.
	 * Do not attempt to cache old rates and skip settings,
	 * disconnects screw such tricks up completely.
	 * Premature optimization is the root of all evil.
	 */

	/* reनिश्चित DTR and RTS on transition from B0 */
	अगर ((old_cflag & CBAUD) == B0) अणु
		dev_dbg(&port->dev, "%s: baud was B0\n", __func__);
		control_state |= TIOCM_DTR | TIOCM_RTS;
		mct_u232_set_modem_ctrl(port, control_state);
	पूर्ण

	mct_u232_set_baud_rate(tty, serial, port, tty_get_baud_rate(tty));

	अगर ((cflag & CBAUD) == B0) अणु
		dev_dbg(&port->dev, "%s: baud is B0\n", __func__);
		/* Drop RTS and DTR */
		control_state &= ~(TIOCM_DTR | TIOCM_RTS);
		mct_u232_set_modem_ctrl(port, control_state);
	पूर्ण

	/*
	 * Update line control रेजिस्टर (LCR)
	 */

	/* set the parity */
	अगर (cflag & PARENB)
		last_lcr |= (cflag & PARODD) ?
			MCT_U232_PARITY_ODD : MCT_U232_PARITY_EVEN;
	अन्यथा
		last_lcr |= MCT_U232_PARITY_NONE;

	/* set the number of data bits */
	चयन (cflag & CSIZE) अणु
	हाल CS5:
		last_lcr |= MCT_U232_DATA_BITS_5; अवरोध;
	हाल CS6:
		last_lcr |= MCT_U232_DATA_BITS_6; अवरोध;
	हाल CS7:
		last_lcr |= MCT_U232_DATA_BITS_7; अवरोध;
	हाल CS8:
		last_lcr |= MCT_U232_DATA_BITS_8; अवरोध;
	शेष:
		dev_err(&port->dev,
			"CSIZE was not CS5-CS8, using default of 8\n");
		last_lcr |= MCT_U232_DATA_BITS_8;
		अवरोध;
	पूर्ण

	termios->c_cflag &= ~CMSPAR;

	/* set the number of stop bits */
	last_lcr |= (cflag & CSTOPB) ?
		MCT_U232_STOP_BITS_2 : MCT_U232_STOP_BITS_1;

	mct_u232_set_line_ctrl(port, last_lcr);

	/* save off the modअगरied port settings */
	spin_lock_irqsave(&priv->lock, flags);
	priv->control_state = control_state;
	priv->last_lcr = last_lcr;
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण /* mct_u232_set_termios */

अटल व्योम mct_u232_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा mct_u232_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित अक्षर lcr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	lcr = priv->last_lcr;

	अगर (अवरोध_state)
		lcr |= MCT_U232_SET_BREAK;
	spin_unlock_irqrestore(&priv->lock, flags);

	mct_u232_set_line_ctrl(port, lcr);
पूर्ण /* mct_u232_अवरोध_ctl */


अटल पूर्णांक mct_u232_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा mct_u232_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक control_state;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	control_state = priv->control_state;
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस control_state;
पूर्ण

अटल पूर्णांक mct_u232_tiocmset(काष्ठा tty_काष्ठा *tty,
			      अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा mct_u232_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक control_state;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	control_state = priv->control_state;

	अगर (set & TIOCM_RTS)
		control_state |= TIOCM_RTS;
	अगर (set & TIOCM_DTR)
		control_state |= TIOCM_DTR;
	अगर (clear & TIOCM_RTS)
		control_state &= ~TIOCM_RTS;
	अगर (clear & TIOCM_DTR)
		control_state &= ~TIOCM_DTR;

	priv->control_state = control_state;
	spin_unlock_irqrestore(&priv->lock, flags);
	वापस mct_u232_set_modem_ctrl(port, control_state);
पूर्ण

अटल व्योम mct_u232_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा mct_u232_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक control_state;

	spin_lock_irq(&priv->lock);
	priv->rx_flags |= THROTTLED;
	अगर (C_CRTSCTS(tty)) अणु
		priv->control_state &= ~TIOCM_RTS;
		control_state = priv->control_state;
		spin_unlock_irq(&priv->lock);
		mct_u232_set_modem_ctrl(port, control_state);
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&priv->lock);
	पूर्ण
पूर्ण

अटल व्योम mct_u232_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा mct_u232_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक control_state;

	spin_lock_irq(&priv->lock);
	अगर ((priv->rx_flags & THROTTLED) && C_CRTSCTS(tty)) अणु
		priv->rx_flags &= ~THROTTLED;
		priv->control_state |= TIOCM_RTS;
		control_state = priv->control_state;
		spin_unlock_irq(&priv->lock);
		mct_u232_set_modem_ctrl(port, control_state);
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&priv->lock);
	पूर्ण
पूर्ण

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
