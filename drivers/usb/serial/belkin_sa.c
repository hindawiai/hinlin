<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Belkin USB Serial Adapter Driver
 *
 *  Copyright (C) 2000		William Greathouse (wgreathouse@smva.com)
 *  Copyright (C) 2000-2001	Greg Kroah-Harपंचांगan (greg@kroah.com)
 *  Copyright (C) 2010		Johan Hovold (jhovold@gmail.com)
 *
 *  This program is largely derived from work by the linux-usb group
 *  and associated source files.  Please see the usb/serial files क्रम
 *  inभागidual credits and copyrights.
 *
 * See Documentation/usb/usb-serial.rst क्रम more inक्रमmation on using this
 * driver
 *
 * TODO:
 * -- Add true modem control line query capability.  Currently we track the
 *    states reported by the पूर्णांकerrupt and the states we request.
 * -- Add support क्रम flush commands
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
#समावेश <linux/usb/serial.h>
#समावेश "belkin_sa.h"

#घोषणा DRIVER_AUTHOR "William Greathouse <wgreathouse@smva.com>"
#घोषणा DRIVER_DESC "USB Belkin Serial converter driver"

/* function prototypes क्रम a Belkin USB Serial Adapter F5U103 */
अटल पूर्णांक belkin_sa_port_probe(काष्ठा usb_serial_port *port);
अटल व्योम belkin_sa_port_हटाओ(काष्ठा usb_serial_port *port);
अटल पूर्णांक  belkin_sa_खोलो(काष्ठा tty_काष्ठा *tty,
			काष्ठा usb_serial_port *port);
अटल व्योम belkin_sa_बंद(काष्ठा usb_serial_port *port);
अटल व्योम belkin_sa_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb);
अटल व्योम belkin_sa_process_पढ़ो_urb(काष्ठा urb *urb);
अटल व्योम belkin_sa_set_termios(काष्ठा tty_काष्ठा *tty,
			काष्ठा usb_serial_port *port, काष्ठा ktermios * old);
अटल व्योम belkin_sa_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state);
अटल पूर्णांक  belkin_sa_tiocmget(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक  belkin_sa_tiocmset(काष्ठा tty_काष्ठा *tty,
					अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);


अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(BELKIN_SA_VID, BELKIN_SA_PID) पूर्ण,
	अणु USB_DEVICE(BELKIN_OLD_VID, BELKIN_OLD_PID) पूर्ण,
	अणु USB_DEVICE(PERACOM_VID, PERACOM_PID) पूर्ण,
	अणु USB_DEVICE(GOHUBS_VID, GOHUBS_PID) पूर्ण,
	अणु USB_DEVICE(GOHUBS_VID, HANDYLINK_PID) पूर्ण,
	अणु USB_DEVICE(BELKIN_DOCKSTATION_VID, BELKIN_DOCKSTATION_PID) पूर्ण,
	अणु पूर्ण	/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

/* All of the device info needed क्रम the serial converters */
अटल काष्ठा usb_serial_driver belkin_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"belkin",
	पूर्ण,
	.description =		"Belkin / Peracom / GoHubs USB Serial Adapter",
	.id_table =		id_table,
	.num_ports =		1,
	.खोलो =			belkin_sa_खोलो,
	.बंद =		belkin_sa_बंद,
	.पढ़ो_पूर्णांक_callback =	belkin_sa_पढ़ो_पूर्णांक_callback,
	.process_पढ़ो_urb =	belkin_sa_process_पढ़ो_urb,
	.set_termios =		belkin_sa_set_termios,
	.अवरोध_ctl =		belkin_sa_अवरोध_ctl,
	.tiocmget =		belkin_sa_tiocmget,
	.tiocmset =		belkin_sa_tiocmset,
	.port_probe =		belkin_sa_port_probe,
	.port_हटाओ =		belkin_sa_port_हटाओ,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&belkin_device, शून्य
पूर्ण;

काष्ठा belkin_sa_निजी अणु
	spinlock_t		lock;
	अचिन्हित दीर्घ		control_state;
	अचिन्हित अक्षर		last_lsr;
	अचिन्हित अक्षर		last_msr;
	पूर्णांक			bad_flow_control;
पूर्ण;


/*
 * ***************************************************************************
 * Belkin USB Serial Adapter F5U103 specअगरic driver functions
 * ***************************************************************************
 */

#घोषणा WDR_TIMEOUT 5000 /* शेष urb समयout */

/* assumes that काष्ठा usb_serial *serial is available */
#घोषणा BSA_USB_CMD(c, v) usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0), \
					    (c), BELKIN_SA_SET_REQUEST_TYPE, \
					    (v), 0, शून्य, 0, WDR_TIMEOUT)

अटल पूर्णांक belkin_sa_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_device *dev = port->serial->dev;
	काष्ठा belkin_sa_निजी *priv;

	priv = kदो_स्मृति(माप(काष्ठा belkin_sa_निजी), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	spin_lock_init(&priv->lock);
	priv->control_state = 0;
	priv->last_lsr = 0;
	priv->last_msr = 0;
	/* see comments at top of file */
	priv->bad_flow_control =
		(le16_to_cpu(dev->descriptor.bcdDevice) <= 0x0206) ? 1 : 0;
	dev_info(&dev->dev, "bcdDevice: %04x, bfc: %d\n",
					le16_to_cpu(dev->descriptor.bcdDevice),
					priv->bad_flow_control);

	usb_set_serial_port_data(port, priv);

	वापस 0;
पूर्ण

अटल व्योम belkin_sa_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा belkin_sa_निजी *priv;

	priv = usb_get_serial_port_data(port);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक belkin_sa_खोलो(काष्ठा tty_काष्ठा *tty,
					काष्ठा usb_serial_port *port)
अणु
	पूर्णांक retval;

	retval = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
	अगर (retval) अणु
		dev_err(&port->dev, "usb_submit_urb(read int) failed\n");
		वापस retval;
	पूर्ण

	retval = usb_serial_generic_खोलो(tty, port);
	अगर (retval)
		usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);

	वापस retval;
पूर्ण

अटल व्योम belkin_sa_बंद(काष्ठा usb_serial_port *port)
अणु
	usb_serial_generic_बंद(port);
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
पूर्ण

अटल व्योम belkin_sa_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा belkin_sa_निजी *priv;
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

	/* Handle known पूर्णांकerrupt data */
	/* ignore data[0] and data[1] */

	priv = usb_get_serial_port_data(port);
	spin_lock_irqsave(&priv->lock, flags);
	priv->last_msr = data[BELKIN_SA_MSR_INDEX];

	/* Record Control Line states */
	अगर (priv->last_msr & BELKIN_SA_MSR_DSR)
		priv->control_state |= TIOCM_DSR;
	अन्यथा
		priv->control_state &= ~TIOCM_DSR;

	अगर (priv->last_msr & BELKIN_SA_MSR_CTS)
		priv->control_state |= TIOCM_CTS;
	अन्यथा
		priv->control_state &= ~TIOCM_CTS;

	अगर (priv->last_msr & BELKIN_SA_MSR_RI)
		priv->control_state |= TIOCM_RI;
	अन्यथा
		priv->control_state &= ~TIOCM_RI;

	अगर (priv->last_msr & BELKIN_SA_MSR_CD)
		priv->control_state |= TIOCM_CD;
	अन्यथा
		priv->control_state &= ~TIOCM_CD;

	priv->last_lsr = data[BELKIN_SA_LSR_INDEX];
	spin_unlock_irqrestore(&priv->lock, flags);
निकास:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&port->dev, "%s - usb_submit_urb failed with "
			"result %d\n", __func__, retval);
पूर्ण

अटल व्योम belkin_sa_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा belkin_sa_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर status;
	अक्षर tty_flag;

	/* Update line status */
	tty_flag = TTY_NORMAL;

	spin_lock_irqsave(&priv->lock, flags);
	status = priv->last_lsr;
	priv->last_lsr &= ~BELKIN_SA_LSR_ERR;
	spin_unlock_irqrestore(&priv->lock, flags);

	अगर (!urb->actual_length)
		वापस;

	अगर (status & BELKIN_SA_LSR_ERR) अणु
		/* Break takes precedence over parity, which takes precedence
		 * over framing errors. */
		अगर (status & BELKIN_SA_LSR_BI)
			tty_flag = TTY_BREAK;
		अन्यथा अगर (status & BELKIN_SA_LSR_PE)
			tty_flag = TTY_PARITY;
		अन्यथा अगर (status & BELKIN_SA_LSR_FE)
			tty_flag = TTY_FRAME;
		dev_dbg(&port->dev, "tty_flag = %d\n", tty_flag);

		/* Overrun is special, not associated with a अक्षर. */
		अगर (status & BELKIN_SA_LSR_OE)
			tty_insert_flip_अक्षर(&port->port, 0, TTY_OVERRUN);
	पूर्ण

	tty_insert_flip_string_fixed_flag(&port->port, data, tty_flag,
							urb->actual_length);
	tty_flip_buffer_push(&port->port);
पूर्ण

अटल व्योम belkin_sa_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा belkin_sa_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक अगरlag;
	अचिन्हित पूर्णांक cflag;
	अचिन्हित पूर्णांक old_अगरlag = 0;
	अचिन्हित पूर्णांक old_cflag = 0;
	__u16 urb_value = 0; /* Will hold the new flags */
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ control_state;
	पूर्णांक bad_flow_control;
	speed_t baud;
	काष्ठा ktermios *termios = &tty->termios;

	अगरlag = termios->c_अगरlag;
	cflag = termios->c_cflag;

	termios->c_cflag &= ~CMSPAR;

	/* get a local copy of the current port settings */
	spin_lock_irqsave(&priv->lock, flags);
	control_state = priv->control_state;
	bad_flow_control = priv->bad_flow_control;
	spin_unlock_irqrestore(&priv->lock, flags);

	old_अगरlag = old_termios->c_अगरlag;
	old_cflag = old_termios->c_cflag;

	/* Set the baud rate */
	अगर ((cflag & CBAUD) != (old_cflag & CBAUD)) अणु
		/* reनिश्चित DTR and (maybe) RTS on transition from B0 */
		अगर ((old_cflag & CBAUD) == B0) अणु
			control_state |= (TIOCM_DTR|TIOCM_RTS);
			अगर (BSA_USB_CMD(BELKIN_SA_SET_DTR_REQUEST, 1) < 0)
				dev_err(&port->dev, "Set DTR error\n");
			/* करोn't set RTS अगर using hardware flow control */
			अगर (!(old_cflag & CRTSCTS))
				अगर (BSA_USB_CMD(BELKIN_SA_SET_RTS_REQUEST
								, 1) < 0)
					dev_err(&port->dev, "Set RTS error\n");
		पूर्ण
	पूर्ण

	baud = tty_get_baud_rate(tty);
	अगर (baud) अणु
		urb_value = BELKIN_SA_BAUD(baud);
		/* Clip to maximum speed */
		अगर (urb_value == 0)
			urb_value = 1;
		/* Turn it back पूर्णांकo a resulting real baud rate */
		baud = BELKIN_SA_BAUD(urb_value);

		/* Report the actual baud rate back to the caller */
		tty_encode_baud_rate(tty, baud, baud);
		अगर (BSA_USB_CMD(BELKIN_SA_SET_BAUDRATE_REQUEST, urb_value) < 0)
			dev_err(&port->dev, "Set baudrate error\n");
	पूर्ण अन्यथा अणु
		/* Disable flow control */
		अगर (BSA_USB_CMD(BELKIN_SA_SET_FLOW_CTRL_REQUEST,
						BELKIN_SA_FLOW_NONE) < 0)
			dev_err(&port->dev, "Disable flowcontrol error\n");
		/* Drop RTS and DTR */
		control_state &= ~(TIOCM_DTR | TIOCM_RTS);
		अगर (BSA_USB_CMD(BELKIN_SA_SET_DTR_REQUEST, 0) < 0)
			dev_err(&port->dev, "DTR LOW error\n");
		अगर (BSA_USB_CMD(BELKIN_SA_SET_RTS_REQUEST, 0) < 0)
			dev_err(&port->dev, "RTS LOW error\n");
	पूर्ण

	/* set the parity */
	अगर ((cflag ^ old_cflag) & (PARENB | PARODD)) अणु
		अगर (cflag & PARENB)
			urb_value = (cflag & PARODD) ?  BELKIN_SA_PARITY_ODD
						: BELKIN_SA_PARITY_EVEN;
		अन्यथा
			urb_value = BELKIN_SA_PARITY_NONE;
		अगर (BSA_USB_CMD(BELKIN_SA_SET_PARITY_REQUEST, urb_value) < 0)
			dev_err(&port->dev, "Set parity error\n");
	पूर्ण

	/* set the number of data bits */
	अगर ((cflag & CSIZE) != (old_cflag & CSIZE)) अणु
		चयन (cflag & CSIZE) अणु
		हाल CS5:
			urb_value = BELKIN_SA_DATA_BITS(5);
			अवरोध;
		हाल CS6:
			urb_value = BELKIN_SA_DATA_BITS(6);
			अवरोध;
		हाल CS7:
			urb_value = BELKIN_SA_DATA_BITS(7);
			अवरोध;
		हाल CS8:
			urb_value = BELKIN_SA_DATA_BITS(8);
			अवरोध;
		शेष:
			dev_dbg(&port->dev,
				"CSIZE was not CS5-CS8, using default of 8\n");
			urb_value = BELKIN_SA_DATA_BITS(8);
			अवरोध;
		पूर्ण
		अगर (BSA_USB_CMD(BELKIN_SA_SET_DATA_BITS_REQUEST, urb_value) < 0)
			dev_err(&port->dev, "Set data bits error\n");
	पूर्ण

	/* set the number of stop bits */
	अगर ((cflag & CSTOPB) != (old_cflag & CSTOPB)) अणु
		urb_value = (cflag & CSTOPB) ? BELKIN_SA_STOP_BITS(2)
						: BELKIN_SA_STOP_BITS(1);
		अगर (BSA_USB_CMD(BELKIN_SA_SET_STOP_BITS_REQUEST,
							urb_value) < 0)
			dev_err(&port->dev, "Set stop bits error\n");
	पूर्ण

	/* Set flow control */
	अगर (((अगरlag ^ old_अगरlag) & (IXOFF | IXON)) ||
		((cflag ^ old_cflag) & CRTSCTS)) अणु
		urb_value = 0;
		अगर ((अगरlag & IXOFF) || (अगरlag & IXON))
			urb_value |= (BELKIN_SA_FLOW_OXON | BELKIN_SA_FLOW_IXON);
		अन्यथा
			urb_value &= ~(BELKIN_SA_FLOW_OXON | BELKIN_SA_FLOW_IXON);

		अगर (cflag & CRTSCTS)
			urb_value |=  (BELKIN_SA_FLOW_OCTS | BELKIN_SA_FLOW_IRTS);
		अन्यथा
			urb_value &= ~(BELKIN_SA_FLOW_OCTS | BELKIN_SA_FLOW_IRTS);

		अगर (bad_flow_control)
			urb_value &= ~(BELKIN_SA_FLOW_IRTS);

		अगर (BSA_USB_CMD(BELKIN_SA_SET_FLOW_CTRL_REQUEST, urb_value) < 0)
			dev_err(&port->dev, "Set flow control error\n");
	पूर्ण

	/* save off the modअगरied port settings */
	spin_lock_irqsave(&priv->lock, flags);
	priv->control_state = control_state;
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम belkin_sa_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_serial *serial = port->serial;

	अगर (BSA_USB_CMD(BELKIN_SA_SET_BREAK_REQUEST, अवरोध_state ? 1 : 0) < 0)
		dev_err(&port->dev, "Set break_ctl %d\n", अवरोध_state);
पूर्ण

अटल पूर्णांक belkin_sa_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा belkin_sa_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ control_state;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	control_state = priv->control_state;
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस control_state;
पूर्ण

अटल पूर्णांक belkin_sa_tiocmset(काष्ठा tty_काष्ठा *tty,
			       अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा belkin_sa_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ control_state;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;
	पूर्णांक rts = 0;
	पूर्णांक dtr = 0;

	spin_lock_irqsave(&priv->lock, flags);
	control_state = priv->control_state;

	अगर (set & TIOCM_RTS) अणु
		control_state |= TIOCM_RTS;
		rts = 1;
	पूर्ण
	अगर (set & TIOCM_DTR) अणु
		control_state |= TIOCM_DTR;
		dtr = 1;
	पूर्ण
	अगर (clear & TIOCM_RTS) अणु
		control_state &= ~TIOCM_RTS;
		rts = 0;
	पूर्ण
	अगर (clear & TIOCM_DTR) अणु
		control_state &= ~TIOCM_DTR;
		dtr = 0;
	पूर्ण

	priv->control_state = control_state;
	spin_unlock_irqrestore(&priv->lock, flags);

	retval = BSA_USB_CMD(BELKIN_SA_SET_RTS_REQUEST, rts);
	अगर (retval < 0) अणु
		dev_err(&port->dev, "Set RTS error %d\n", retval);
		जाओ निकास;
	पूर्ण

	retval = BSA_USB_CMD(BELKIN_SA_SET_DTR_REQUEST, dtr);
	अगर (retval < 0) अणु
		dev_err(&port->dev, "Set DTR error %d\n", retval);
		जाओ निकास;
	पूर्ण
निकास:
	वापस retval;
पूर्ण

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
