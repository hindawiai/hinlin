<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * KLSI KL5KUSB105 chip RS232 converter driver
 *
 *   Copyright (C) 2010 Johan Hovold <jhovold@gmail.com>
 *   Copyright (C) 2001 Utz-Uwe Haus <haus@uuhaus.de>
 *
 * All inक्रमmation about the device was acquired using SnअगरfUSB ans snoopUSB
 * on Winकरोws98.
 * It was written out of frustration with the PalmConnect USB Serial adapter
 * sold by Palm Inc.
 * Neither Palm, nor their contractor (MCCI) or their supplier (KLSI) provided
 * inक्रमmation that was not alपढ़ोy available.
 *
 * It seems that KLSI bought some silicon-design inक्रमmation from ScanLogic,
 * whose SL11R processor is at the core of the KL5KUSB chipset from KLSI.
 * KLSI has firmware available क्रम their devices; it is probable that the
 * firmware dअगरfers from that used by KLSI in their products. If you have an
 * original KLSI device and can provide some inक्रमmation on it, I would be
 * most पूर्णांकerested in adding support क्रम it here. If you have any inक्रमmation
 * on the protocol used (or find errors in my reverse-engineered stuff), please
 * let me know.
 *
 * The code was only tested with a PalmConnect USB adapter; अगर you
 * are adventurous, try it with any KLSI-based device and let me know how it
 * अवरोधs so that I can fix it!
 */

/* TODO:
 *	check modem line संकेतs
 *	implement handshaking or decide that we करो not support it
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश "kl5kusb105.h"

#घोषणा DRIVER_AUTHOR "Utz-Uwe Haus <haus@uuhaus.de>, Johan Hovold <jhovold@gmail.com>"
#घोषणा DRIVER_DESC "KLSI KL5KUSB105 chipset USB->Serial Converter driver"


/*
 * Function prototypes
 */
अटल पूर्णांक klsi_105_port_probe(काष्ठा usb_serial_port *port);
अटल व्योम klsi_105_port_हटाओ(काष्ठा usb_serial_port *port);
अटल पूर्णांक  klsi_105_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port);
अटल व्योम klsi_105_बंद(काष्ठा usb_serial_port *port);
अटल व्योम klsi_105_set_termios(काष्ठा tty_काष्ठा *tty,
			काष्ठा usb_serial_port *port, काष्ठा ktermios *old);
अटल पूर्णांक  klsi_105_tiocmget(काष्ठा tty_काष्ठा *tty);
अटल व्योम klsi_105_process_पढ़ो_urb(काष्ठा urb *urb);
अटल पूर्णांक klsi_105_prepare_ग_लिखो_buffer(काष्ठा usb_serial_port *port,
						व्योम *dest, माप_प्रकार size);

/*
 * All of the device info needed क्रम the KLSI converters.
 */
अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(PALMCONNECT_VID, PALMCONNECT_PID) पूर्ण,
	अणु पूर्ण		/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table);

अटल काष्ठा usb_serial_driver kl5kusb105d_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"kl5kusb105d",
	पूर्ण,
	.description =		"KL5KUSB105D / PalmConnect",
	.id_table =		id_table,
	.num_ports =		1,
	.bulk_out_size =	64,
	.खोलो =			klsi_105_खोलो,
	.बंद =		klsi_105_बंद,
	.set_termios =		klsi_105_set_termios,
	.tiocmget =		klsi_105_tiocmget,
	.port_probe =		klsi_105_port_probe,
	.port_हटाओ =		klsi_105_port_हटाओ,
	.throttle =		usb_serial_generic_throttle,
	.unthrottle =		usb_serial_generic_unthrottle,
	.process_पढ़ो_urb =	klsi_105_process_पढ़ो_urb,
	.prepare_ग_लिखो_buffer =	klsi_105_prepare_ग_लिखो_buffer,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&kl5kusb105d_device, शून्य
पूर्ण;

काष्ठा klsi_105_port_settings अणु
	u8	pktlen;		/* always 5, it seems */
	u8	baudrate;
	u8	databits;
	u8	unknown1;
	u8	unknown2;
पूर्ण;

काष्ठा klsi_105_निजी अणु
	काष्ठा klsi_105_port_settings	cfg;
	अचिन्हित दीर्घ			line_state; /* modem line settings */
	spinlock_t			lock;
पूर्ण;


/*
 * Handle venकरोr specअगरic USB requests
 */


#घोषणा KLSI_TIMEOUT	 5000 /* शेष urb समयout */

अटल पूर्णांक klsi_105_chg_port_settings(काष्ठा usb_serial_port *port,
				      काष्ठा klsi_105_port_settings *settings)
अणु
	पूर्णांक rc;

	rc = usb_control_msg(port->serial->dev,
			usb_sndctrlpipe(port->serial->dev, 0),
			KL5KUSB105A_SIO_SET_DATA,
			USB_TYPE_VENDOR | USB_सूची_OUT | USB_RECIP_INTERFACE,
			0, /* value */
			0, /* index */
			settings,
			माप(काष्ठा klsi_105_port_settings),
			KLSI_TIMEOUT);
	अगर (rc < 0)
		dev_err(&port->dev,
			"Change port settings failed (error = %d)\n", rc);

	dev_dbg(&port->dev,
		"pktlen %u, baudrate 0x%02x, databits %u, u1 %u, u2 %u\n",
		settings->pktlen, settings->baudrate, settings->databits,
		settings->unknown1, settings->unknown2);

	वापस rc;
पूर्ण

/* translate a 16-bit status value from the device to linux's TIO bits */
अटल अचिन्हित दीर्घ klsi_105_status2linestate(स्थिर __u16 status)
अणु
	अचिन्हित दीर्घ res = 0;

	res =   ((status & KL5KUSB105A_DSR) ? TIOCM_DSR : 0)
	      | ((status & KL5KUSB105A_CTS) ? TIOCM_CTS : 0)
	      ;

	वापस res;
पूर्ण

/*
 * Read line control via venकरोr command and वापस result through
 * *line_state_p
 */
/* It seems that the status buffer has always only 2 bytes length */
#घोषणा KLSI_STATUSBUF_LEN	2
अटल पूर्णांक klsi_105_get_line_state(काष्ठा usb_serial_port *port,
				   अचिन्हित दीर्घ *line_state_p)
अणु
	पूर्णांक rc;
	u8 *status_buf;
	__u16 status;

	status_buf = kदो_स्मृति(KLSI_STATUSBUF_LEN, GFP_KERNEL);
	अगर (!status_buf)
		वापस -ENOMEM;

	status_buf[0] = 0xff;
	status_buf[1] = 0xff;
	rc = usb_control_msg(port->serial->dev,
			     usb_rcvctrlpipe(port->serial->dev, 0),
			     KL5KUSB105A_SIO_POLL,
			     USB_TYPE_VENDOR | USB_सूची_IN,
			     0, /* value */
			     0, /* index */
			     status_buf, KLSI_STATUSBUF_LEN,
			     10000
			     );
	अगर (rc != KLSI_STATUSBUF_LEN) अणु
		dev_err(&port->dev, "reading line status failed: %d\n", rc);
		अगर (rc >= 0)
			rc = -EIO;
	पूर्ण अन्यथा अणु
		status = get_unaligned_le16(status_buf);

		dev_dbg(&port->dev, "read status %02x %02x\n",
			status_buf[0], status_buf[1]);

		*line_state_p = klsi_105_status2linestate(status);
	पूर्ण

	kमुक्त(status_buf);
	वापस rc;
पूर्ण


/*
 * Driver's tty पूर्णांकerface functions
 */

अटल पूर्णांक klsi_105_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा klsi_105_निजी *priv;

	priv = kदो_स्मृति(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* set initial values क्रम control काष्ठाures */
	priv->cfg.pktlen    = 5;
	priv->cfg.baudrate  = kl5kusb105a_sio_b9600;
	priv->cfg.databits  = kl5kusb105a_dtb_8;
	priv->cfg.unknown1  = 0;
	priv->cfg.unknown2  = 1;

	priv->line_state    = 0;

	spin_lock_init(&priv->lock);

	usb_set_serial_port_data(port, priv);

	वापस 0;
पूर्ण

अटल व्योम klsi_105_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा klsi_105_निजी *priv;

	priv = usb_get_serial_port_data(port);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक  klsi_105_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा klsi_105_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक retval = 0;
	पूर्णांक rc;
	अचिन्हित दीर्घ line_state;
	काष्ठा klsi_105_port_settings *cfg;
	अचिन्हित दीर्घ flags;

	/* Do a defined restart:
	 * Set up sane शेष baud rate and send the 'READ_ON'
	 * venकरोr command.
	 * FIXME: set modem line control (how?)
	 * Then पढ़ो the modem line control and store values in
	 * priv->line_state.
	 */
	cfg = kदो_स्मृति(माप(*cfg), GFP_KERNEL);
	अगर (!cfg)
		वापस -ENOMEM;

	cfg->pktlen   = 5;
	cfg->baudrate = kl5kusb105a_sio_b9600;
	cfg->databits = kl5kusb105a_dtb_8;
	cfg->unknown1 = 0;
	cfg->unknown2 = 1;
	klsi_105_chg_port_settings(port, cfg);

	spin_lock_irqsave(&priv->lock, flags);
	priv->cfg.pktlen   = cfg->pktlen;
	priv->cfg.baudrate = cfg->baudrate;
	priv->cfg.databits = cfg->databits;
	priv->cfg.unknown1 = cfg->unknown1;
	priv->cfg.unknown2 = cfg->unknown2;
	spin_unlock_irqrestore(&priv->lock, flags);

	kमुक्त(cfg);

	/* READ_ON and urb submission */
	rc = usb_serial_generic_खोलो(tty, port);
	अगर (rc)
		वापस rc;

	rc = usb_control_msg(port->serial->dev,
			     usb_sndctrlpipe(port->serial->dev, 0),
			     KL5KUSB105A_SIO_CONFIGURE,
			     USB_TYPE_VENDOR|USB_सूची_OUT|USB_RECIP_INTERFACE,
			     KL5KUSB105A_SIO_CONFIGURE_READ_ON,
			     0, /* index */
			     शून्य,
			     0,
			     KLSI_TIMEOUT);
	अगर (rc < 0) अणु
		dev_err(&port->dev, "Enabling read failed (error = %d)\n", rc);
		retval = rc;
		जाओ err_generic_बंद;
	पूर्ण अन्यथा
		dev_dbg(&port->dev, "%s - enabled reading\n", __func__);

	rc = klsi_105_get_line_state(port, &line_state);
	अगर (rc < 0) अणु
		retval = rc;
		जाओ err_disable_पढ़ो;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);
	priv->line_state = line_state;
	spin_unlock_irqrestore(&priv->lock, flags);
	dev_dbg(&port->dev, "%s - read line state 0x%lx\n", __func__,
			line_state);

	वापस 0;

err_disable_पढ़ो:
	usb_control_msg(port->serial->dev,
			     usb_sndctrlpipe(port->serial->dev, 0),
			     KL5KUSB105A_SIO_CONFIGURE,
			     USB_TYPE_VENDOR | USB_सूची_OUT,
			     KL5KUSB105A_SIO_CONFIGURE_READ_OFF,
			     0, /* index */
			     शून्य, 0,
			     KLSI_TIMEOUT);
err_generic_बंद:
	usb_serial_generic_बंद(port);

	वापस retval;
पूर्ण

अटल व्योम klsi_105_बंद(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक rc;

	/* send READ_OFF */
	rc = usb_control_msg(port->serial->dev,
			     usb_sndctrlpipe(port->serial->dev, 0),
			     KL5KUSB105A_SIO_CONFIGURE,
			     USB_TYPE_VENDOR | USB_सूची_OUT,
			     KL5KUSB105A_SIO_CONFIGURE_READ_OFF,
			     0, /* index */
			     शून्य, 0,
			     KLSI_TIMEOUT);
	अगर (rc < 0)
		dev_err(&port->dev, "failed to disable read: %d\n", rc);

	/* shutकरोwn our bulk पढ़ोs and ग_लिखोs */
	usb_serial_generic_बंद(port);
पूर्ण

/* We need to ग_लिखो a complete 64-byte data block and encode the
 * number actually sent in the first द्विगुन-byte, LSB-order. That
 * leaves at most 62 bytes of payload.
 */
#घोषणा KLSI_HDR_LEN		2
अटल पूर्णांक klsi_105_prepare_ग_लिखो_buffer(काष्ठा usb_serial_port *port,
						व्योम *dest, माप_प्रकार size)
अणु
	अचिन्हित अक्षर *buf = dest;
	पूर्णांक count;

	count = kfअगरo_out_locked(&port->ग_लिखो_fअगरo, buf + KLSI_HDR_LEN, size,
								&port->lock);
	put_unaligned_le16(count, buf);

	वापस count + KLSI_HDR_LEN;
पूर्ण

/* The data received is preceded by a length द्विगुन-byte in LSB-first order.
 */
अटल व्योम klsi_105_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	अचिन्हित len;

	/* empty urbs seem to happen, we ignore them */
	अगर (!urb->actual_length)
		वापस;

	अगर (urb->actual_length <= KLSI_HDR_LEN) अणु
		dev_dbg(&port->dev, "%s - malformed packet\n", __func__);
		वापस;
	पूर्ण

	len = get_unaligned_le16(data);
	अगर (len > urb->actual_length - KLSI_HDR_LEN) अणु
		dev_dbg(&port->dev, "%s - packet length mismatch\n", __func__);
		len = urb->actual_length - KLSI_HDR_LEN;
	पूर्ण

	tty_insert_flip_string(&port->port, data + KLSI_HDR_LEN, len);
	tty_flip_buffer_push(&port->port);
पूर्ण

अटल व्योम klsi_105_set_termios(काष्ठा tty_काष्ठा *tty,
				 काष्ठा usb_serial_port *port,
				 काष्ठा ktermios *old_termios)
अणु
	काष्ठा klsi_105_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा device *dev = &port->dev;
	अचिन्हित पूर्णांक अगरlag = tty->termios.c_अगरlag;
	अचिन्हित पूर्णांक old_अगरlag = old_termios->c_अगरlag;
	अचिन्हित पूर्णांक cflag = tty->termios.c_cflag;
	अचिन्हित पूर्णांक old_cflag = old_termios->c_cflag;
	काष्ठा klsi_105_port_settings *cfg;
	अचिन्हित दीर्घ flags;
	speed_t baud;

	cfg = kदो_स्मृति(माप(*cfg), GFP_KERNEL);
	अगर (!cfg)
		वापस;

	/* lock जबतक we are modअगरying the settings */
	spin_lock_irqsave(&priv->lock, flags);

	/*
	 * Update baud rate
	 */
	baud = tty_get_baud_rate(tty);

	चयन (baud) अणु
	हाल 0: /* handled below */
		अवरोध;
	हाल 1200:
		priv->cfg.baudrate = kl5kusb105a_sio_b1200;
		अवरोध;
	हाल 2400:
		priv->cfg.baudrate = kl5kusb105a_sio_b2400;
		अवरोध;
	हाल 4800:
		priv->cfg.baudrate = kl5kusb105a_sio_b4800;
		अवरोध;
	हाल 9600:
		priv->cfg.baudrate = kl5kusb105a_sio_b9600;
		अवरोध;
	हाल 19200:
		priv->cfg.baudrate = kl5kusb105a_sio_b19200;
		अवरोध;
	हाल 38400:
		priv->cfg.baudrate = kl5kusb105a_sio_b38400;
		अवरोध;
	हाल 57600:
		priv->cfg.baudrate = kl5kusb105a_sio_b57600;
		अवरोध;
	हाल 115200:
		priv->cfg.baudrate = kl5kusb105a_sio_b115200;
		अवरोध;
	शेष:
		dev_dbg(dev, "unsupported baudrate, using 9600\n");
		priv->cfg.baudrate = kl5kusb105a_sio_b9600;
		baud = 9600;
		अवरोध;
	पूर्ण

	/*
	 * FIXME: implement B0 handling
	 *
	 * Maybe this should be simulated by sending पढ़ो disable and पढ़ो
	 * enable messages?
	 */

	tty_encode_baud_rate(tty, baud, baud);

	अगर ((cflag & CSIZE) != (old_cflag & CSIZE)) अणु
		/* set the number of data bits */
		चयन (cflag & CSIZE) अणु
		हाल CS5:
			dev_dbg(dev, "%s - 5 bits/byte not supported\n", __func__);
			spin_unlock_irqrestore(&priv->lock, flags);
			जाओ err;
		हाल CS6:
			dev_dbg(dev, "%s - 6 bits/byte not supported\n", __func__);
			spin_unlock_irqrestore(&priv->lock, flags);
			जाओ err;
		हाल CS7:
			priv->cfg.databits = kl5kusb105a_dtb_7;
			अवरोध;
		हाल CS8:
			priv->cfg.databits = kl5kusb105a_dtb_8;
			अवरोध;
		शेष:
			dev_err(dev, "CSIZE was not CS5-CS8, using default of 8\n");
			priv->cfg.databits = kl5kusb105a_dtb_8;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Update line control रेजिस्टर (LCR)
	 */
	अगर ((cflag & (PARENB|PARODD)) != (old_cflag & (PARENB|PARODD))
	    || (cflag & CSTOPB) != (old_cflag & CSTOPB)) अणु
		/* Not currently supported */
		tty->termios.c_cflag &= ~(PARENB|PARODD|CSTOPB);
	पूर्ण
	/*
	 * Set flow control: well, I करो not really now how to handle DTR/RTS.
	 * Just करो what we have seen with SnअगरfUSB on Win98.
	 */
	अगर ((अगरlag & IXOFF) != (old_अगरlag & IXOFF)
	    || (अगरlag & IXON) != (old_अगरlag & IXON)
	    ||  (cflag & CRTSCTS) != (old_cflag & CRTSCTS)) अणु
		/* Not currently supported */
		tty->termios.c_cflag &= ~CRTSCTS;
	पूर्ण
	स_नकल(cfg, &priv->cfg, माप(*cfg));
	spin_unlock_irqrestore(&priv->lock, flags);

	/* now commit changes to device */
	klsi_105_chg_port_settings(port, cfg);
err:
	kमुक्त(cfg);
पूर्ण

अटल पूर्णांक klsi_105_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा klsi_105_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;
	अचिन्हित दीर्घ line_state;

	rc = klsi_105_get_line_state(port, &line_state);
	अगर (rc < 0) अणु
		dev_err(&port->dev,
			"Reading line control failed (error = %d)\n", rc);
		/* better वापस value? EAGAIN? */
		वापस rc;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);
	priv->line_state = line_state;
	spin_unlock_irqrestore(&priv->lock, flags);
	dev_dbg(&port->dev, "%s - read line state 0x%lx\n", __func__, line_state);
	वापस (पूर्णांक)line_state;
पूर्ण

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
