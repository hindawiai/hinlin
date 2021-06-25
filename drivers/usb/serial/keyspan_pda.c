<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * USB Keyspan PDA / Xircom / Entrega Converter driver
 *
 * Copyright (C) 1999 - 2001 Greg Kroah-Harपंचांगan	<greg@kroah.com>
 * Copyright (C) 1999, 2000 Brian Warner	<warner@lothar.com>
 * Copyright (C) 2000 Al Borchers		<borchers@steinerpoपूर्णांक.com>
 * Copyright (C) 2020 Johan Hovold <johan@kernel.org>
 *
 * See Documentation/usb/usb-serial.rst क्रम more inक्रमmation on using this
 * driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/usb/ezusb.h>

#घोषणा DRIVER_AUTHOR "Brian Warner <warner@lothar.com>, Johan Hovold <johan@kernel.org>"
#घोषणा DRIVER_DESC "USB Keyspan PDA Converter driver"

#घोषणा KEYSPAN_TX_THRESHOLD	128

काष्ठा keyspan_pda_निजी अणु
	पूर्णांक			tx_room;
	काष्ठा work_काष्ठा	unthrottle_work;
	काष्ठा usb_serial	*serial;
	काष्ठा usb_serial_port	*port;
पूर्ण;

अटल पूर्णांक keyspan_pda_ग_लिखो_start(काष्ठा usb_serial_port *port);

#घोषणा KEYSPAN_VENDOR_ID		0x06cd
#घोषणा KEYSPAN_PDA_FAKE_ID		0x0103
#घोषणा KEYSPAN_PDA_ID			0x0104 /* no clue */

/* For Xircom PGSDB9 and older Entrega version of the same device */
#घोषणा XIRCOM_VENDOR_ID		0x085a
#घोषणा XIRCOM_FAKE_ID			0x8027
#घोषणा XIRCOM_FAKE_ID_2		0x8025 /* "PGMFHUB" serial */
#घोषणा ENTREGA_VENDOR_ID		0x1645
#घोषणा ENTREGA_FAKE_ID			0x8093

अटल स्थिर काष्ठा usb_device_id id_table_combined[] = अणु
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, KEYSPAN_PDA_FAKE_ID) पूर्ण,
	अणु USB_DEVICE(XIRCOM_VENDOR_ID, XIRCOM_FAKE_ID) पूर्ण,
	अणु USB_DEVICE(XIRCOM_VENDOR_ID, XIRCOM_FAKE_ID_2) पूर्ण,
	अणु USB_DEVICE(ENTREGA_VENDOR_ID, ENTREGA_FAKE_ID) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, KEYSPAN_PDA_ID) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table_combined);

अटल स्थिर काष्ठा usb_device_id id_table_std[] = अणु
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, KEYSPAN_PDA_ID) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id id_table_fake[] = अणु
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, KEYSPAN_PDA_FAKE_ID) पूर्ण,
	अणु USB_DEVICE(XIRCOM_VENDOR_ID, XIRCOM_FAKE_ID) पूर्ण,
	अणु USB_DEVICE(XIRCOM_VENDOR_ID, XIRCOM_FAKE_ID_2) पूर्ण,
	अणु USB_DEVICE(ENTREGA_VENDOR_ID, ENTREGA_FAKE_ID) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

अटल पूर्णांक keyspan_pda_get_ग_लिखो_room(काष्ठा keyspan_pda_निजी *priv)
अणु
	काष्ठा usb_serial_port *port = priv->port;
	काष्ठा usb_serial *serial = port->serial;
	u8 *room;
	पूर्णांक rc;

	room = kदो_स्मृति(1, GFP_KERNEL);
	अगर (!room)
		वापस -ENOMEM;

	rc = usb_control_msg(serial->dev,
			     usb_rcvctrlpipe(serial->dev, 0),
			     6, /* ग_लिखो_room */
			     USB_TYPE_VENDOR | USB_RECIP_INTERFACE
			     | USB_सूची_IN,
			     0, /* value: 0 means "remaining room" */
			     0, /* index */
			     room,
			     1,
			     2000);
	अगर (rc != 1) अणु
		अगर (rc >= 0)
			rc = -EIO;
		dev_dbg(&port->dev, "roomquery failed: %d\n", rc);
		जाओ out_मुक्त;
	पूर्ण

	dev_dbg(&port->dev, "roomquery says %d\n", *room);
	rc = *room;
out_मुक्त:
	kमुक्त(room);

	वापस rc;
पूर्ण

अटल व्योम keyspan_pda_request_unthrottle(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा keyspan_pda_निजी *priv =
		container_of(work, काष्ठा keyspan_pda_निजी, unthrottle_work);
	काष्ठा usb_serial_port *port = priv->port;
	काष्ठा usb_serial *serial = port->serial;
	अचिन्हित दीर्घ flags;
	पूर्णांक result;

	dev_dbg(&port->dev, "%s\n", __func__);

	/*
	 * Ask the device to tell us when the tx buffer becomes
	 * sufficiently empty.
	 */
	result = usb_control_msg(serial->dev,
				 usb_sndctrlpipe(serial->dev, 0),
				 7, /* request_unthrottle */
				 USB_TYPE_VENDOR | USB_RECIP_INTERFACE
				 | USB_सूची_OUT,
				 KEYSPAN_TX_THRESHOLD,
				 0, /* index */
				 शून्य,
				 0,
				 2000);
	अगर (result < 0)
		dev_dbg(&serial->dev->dev, "%s - error %d from usb_control_msg\n",
			__func__, result);
	/*
	 * Need to check available space after requesting notअगरication in हाल
	 * buffer is alपढ़ोy empty so that no notअगरication is sent.
	 */
	result = keyspan_pda_get_ग_लिखो_room(priv);
	अगर (result > KEYSPAN_TX_THRESHOLD) अणु
		spin_lock_irqsave(&port->lock, flags);
		priv->tx_room = max(priv->tx_room, result);
		spin_unlock_irqrestore(&port->lock, flags);

		usb_serial_port_softपूर्णांक(port);
	पूर्ण
पूर्ण

अटल व्योम keyspan_pda_rx_पूर्णांकerrupt(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	अचिन्हित पूर्णांक len = urb->actual_length;
	पूर्णांक retval;
	पूर्णांक status = urb->status;
	काष्ठा keyspan_pda_निजी *priv;
	अचिन्हित दीर्घ flags;

	priv = usb_get_serial_port_data(port);

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&urb->dev->dev, "%s - urb shutting down with status: %d\n", __func__, status);
		वापस;
	शेष:
		dev_dbg(&urb->dev->dev, "%s - nonzero urb status received: %d\n", __func__, status);
		जाओ निकास;
	पूर्ण

	अगर (len < 1) अणु
		dev_warn(&port->dev, "short message received\n");
		जाओ निकास;
	पूर्ण

	/* see अगर the message is data or a status पूर्णांकerrupt */
	चयन (data[0]) अणु
	हाल 0:
		 /* rest of message is rx data */
		अगर (len < 2)
			अवरोध;
		tty_insert_flip_string(&port->port, data + 1, len - 1);
		tty_flip_buffer_push(&port->port);
		अवरोध;
	हाल 1:
		/* status पूर्णांकerrupt */
		अगर (len < 2) अणु
			dev_warn(&port->dev, "short interrupt message received\n");
			अवरोध;
		पूर्ण
		dev_dbg(&port->dev, "rx int, d1=%d\n", data[1]);
		चयन (data[1]) अणु
		हाल 1: /* modemline change */
			अवरोध;
		हाल 2: /* tx unthrottle पूर्णांकerrupt */
			spin_lock_irqsave(&port->lock, flags);
			priv->tx_room = max(priv->tx_room, KEYSPAN_TX_THRESHOLD);
			spin_unlock_irqrestore(&port->lock, flags);

			keyspan_pda_ग_लिखो_start(port);

			usb_serial_port_softपूर्णांक(port);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

निकास:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&port->dev,
			"%s - usb_submit_urb failed with result %d\n",
			__func__, retval);
पूर्ण

अटल व्योम keyspan_pda_rx_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	/*
	 * Stop receiving अक्षरacters. We just turn off the URB request, and
	 * let अक्षरs pile up in the device. If we're करोing hardware
	 * flowcontrol, the device will संकेत the other end when its buffer
	 * fills up. If we're करोing XON/XOFF, this would be a good समय to
	 * send an XOFF, although it might make sense to foist that off upon
	 * the device too.
	 */
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
पूर्ण

अटल व्योम keyspan_pda_rx_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	/* just restart the receive पूर्णांकerrupt URB */
	अगर (usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL))
		dev_dbg(&port->dev, "usb_submit_urb(read urb) failed\n");
पूर्ण

अटल speed_t keyspan_pda_setbaud(काष्ठा usb_serial *serial, speed_t baud)
अणु
	पूर्णांक rc;
	पूर्णांक bindex;

	चयन (baud) अणु
	हाल 110:
		bindex = 0;
		अवरोध;
	हाल 300:
		bindex = 1;
		अवरोध;
	हाल 1200:
		bindex = 2;
		अवरोध;
	हाल 2400:
		bindex = 3;
		अवरोध;
	हाल 4800:
		bindex = 4;
		अवरोध;
	हाल 9600:
		bindex = 5;
		अवरोध;
	हाल 19200:
		bindex = 6;
		अवरोध;
	हाल 38400:
		bindex = 7;
		अवरोध;
	हाल 57600:
		bindex = 8;
		अवरोध;
	हाल 115200:
		bindex = 9;
		अवरोध;
	शेष:
		bindex = 5;	/* Default to 9600 */
		baud = 9600;
	पूर्ण

	rc = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			     0, /* set baud */
			     USB_TYPE_VENDOR
			     | USB_RECIP_INTERFACE
			     | USB_सूची_OUT, /* type */
			     bindex, /* value */
			     0, /* index */
			     शून्य, /* &data */
			     0, /* size */
			     2000); /* समयout */
	अगर (rc < 0)
		वापस 0;

	वापस baud;
पूर्ण

अटल व्योम keyspan_pda_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_serial *serial = port->serial;
	पूर्णांक value;
	पूर्णांक result;

	अगर (अवरोध_state == -1)
		value = 1; /* start अवरोध */
	अन्यथा
		value = 0; /* clear अवरोध */

	result = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			4, /* set अवरोध */
			USB_TYPE_VENDOR | USB_RECIP_INTERFACE | USB_सूची_OUT,
			value, 0, शून्य, 0, 2000);
	अगर (result < 0)
		dev_dbg(&port->dev, "%s - error %d from usb_control_msg\n",
			__func__, result);
पूर्ण

अटल व्योम keyspan_pda_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा usb_serial *serial = port->serial;
	speed_t speed;

	/*
	 * cflag specअगरies lots of stuff: number of stop bits, parity, number
	 * of data bits, baud. What can the device actually handle?:
	 * CSTOPB (1 stop bit or 2)
	 * PARENB (parity)
	 * CSIZE (5bit .. 8bit)
	 * There is minimal hw support क्रम parity (a PSW bit seems to hold the
	 * parity of whatever is in the accumulator). The UART either deals
	 * with 10 bits (start, 8 data, stop) or 11 bits (start, 8 data,
	 * 1 special, stop). So, with firmware changes, we could करो:
	 * 8N1: 10 bit
	 * 8N2: 11 bit, extra bit always (mark?)
	 * 8[EOMS]1: 11 bit, extra bit is parity
	 * 7[EOMS]1: 10 bit, b0/b7 is parity
	 * 7[EOMS]2: 11 bit, b0/b7 is parity, extra bit always (mark?)
	 *
	 * HW flow control is dictated by the tty->termios.c_cflags & CRTSCTS
	 * bit.
	 *
	 * For now, just करो baud.
	 */
	speed = tty_get_baud_rate(tty);
	speed = keyspan_pda_setbaud(serial, speed);

	अगर (speed == 0) अणु
		dev_dbg(&port->dev, "can't handle requested baud rate\n");
		/* It hasn't changed so.. */
		speed = tty_termios_baud_rate(old_termios);
	पूर्ण
	/*
	 * Only speed can change so copy the old h/w parameters then encode
	 * the new speed.
	 */
	tty_termios_copy_hw(&tty->termios, old_termios);
	tty_encode_baud_rate(tty, speed, speed);
पूर्ण

/*
 * Modem control pins: DTR and RTS are outमाला_दो and can be controlled.
 * DCD, RI, DSR, CTS are inमाला_दो and can be पढ़ो. All outमाला_दो can also be
 * पढ़ो. The byte passed is: DTR(b7) DCD RI DSR CTS RTS(b2) unused unused.
 */
अटल पूर्णांक keyspan_pda_get_modem_info(काष्ठा usb_serial *serial,
				      अचिन्हित अक्षर *value)
अणु
	पूर्णांक rc;
	u8 *data;

	data = kदो_स्मृति(1, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	rc = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
			     3, /* get pins */
			     USB_TYPE_VENDOR|USB_RECIP_INTERFACE|USB_सूची_IN,
			     0, 0, data, 1, 2000);
	अगर (rc == 1)
		*value = *data;
	अन्यथा अगर (rc >= 0)
		rc = -EIO;

	kमुक्त(data);
	वापस rc;
पूर्ण

अटल पूर्णांक keyspan_pda_set_modem_info(काष्ठा usb_serial *serial,
				      अचिन्हित अक्षर value)
अणु
	पूर्णांक rc;
	rc = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			     3, /* set pins */
			     USB_TYPE_VENDOR|USB_RECIP_INTERFACE|USB_सूची_OUT,
			     value, 0, शून्य, 0, 2000);
	वापस rc;
पूर्ण

अटल पूर्णांक keyspan_pda_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_serial *serial = port->serial;
	पूर्णांक rc;
	अचिन्हित अक्षर status;
	पूर्णांक value;

	rc = keyspan_pda_get_modem_info(serial, &status);
	अगर (rc < 0)
		वापस rc;

	value = ((status & BIT(7)) ? TIOCM_DTR : 0) |
		((status & BIT(6)) ? TIOCM_CAR : 0) |
		((status & BIT(5)) ? TIOCM_RNG : 0) |
		((status & BIT(4)) ? TIOCM_DSR : 0) |
		((status & BIT(3)) ? TIOCM_CTS : 0) |
		((status & BIT(2)) ? TIOCM_RTS : 0);

	वापस value;
पूर्ण

अटल पूर्णांक keyspan_pda_tiocmset(काष्ठा tty_काष्ठा *tty,
				अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_serial *serial = port->serial;
	पूर्णांक rc;
	अचिन्हित अक्षर status;

	rc = keyspan_pda_get_modem_info(serial, &status);
	अगर (rc < 0)
		वापस rc;

	अगर (set & TIOCM_RTS)
		status |= BIT(2);
	अगर (set & TIOCM_DTR)
		status |= BIT(7);

	अगर (clear & TIOCM_RTS)
		status &= ~BIT(2);
	अगर (clear & TIOCM_DTR)
		status &= ~BIT(7);
	rc = keyspan_pda_set_modem_info(serial, status);
	वापस rc;
पूर्ण

अटल पूर्णांक keyspan_pda_ग_लिखो_start(काष्ठा usb_serial_port *port)
अणु
	काष्ठा keyspan_pda_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	काष्ठा urb *urb;
	पूर्णांक count;
	पूर्णांक room;
	पूर्णांक rc;

	/*
	 * Guess how much room is left in the device's ring buffer. If our
	 * ग_लिखो will result in no room left, ask the device to give us an
	 * पूर्णांकerrupt when the room available rises above a threshold but also
	 * query how much room is currently available (in हाल our guess was
	 * too conservative and the buffer is alपढ़ोy empty when the
	 * unthrottle work is scheduled).
	 */

	/*
	 * We might block because of:
	 * the TX urb is in-flight (रुको until it completes)
	 * the device is full (रुको until it says there is room)
	 */
	spin_lock_irqsave(&port->lock, flags);

	room = priv->tx_room;
	count = kfअगरo_len(&port->ग_लिखो_fअगरo);

	अगर (!test_bit(0, &port->ग_लिखो_urbs_मुक्त) || count == 0 || room == 0) अणु
		spin_unlock_irqrestore(&port->lock, flags);
		वापस 0;
	पूर्ण
	__clear_bit(0, &port->ग_लिखो_urbs_मुक्त);

	अगर (count > room)
		count = room;
	अगर (count > port->bulk_out_size)
		count = port->bulk_out_size;

	urb = port->ग_लिखो_urb;
	count = kfअगरo_out(&port->ग_लिखो_fअगरo, urb->transfer_buffer, count);
	urb->transfer_buffer_length = count;

	port->tx_bytes += count;
	priv->tx_room -= count;

	spin_unlock_irqrestore(&port->lock, flags);

	dev_dbg(&port->dev, "%s - count = %d, txroom = %d\n", __func__, count, room);

	rc = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (rc) अणु
		dev_dbg(&port->dev, "usb_submit_urb(write bulk) failed\n");

		spin_lock_irqsave(&port->lock, flags);
		port->tx_bytes -= count;
		priv->tx_room = max(priv->tx_room, room + count);
		__set_bit(0, &port->ग_लिखो_urbs_मुक्त);
		spin_unlock_irqrestore(&port->lock, flags);

		वापस rc;
	पूर्ण

	अगर (count == room)
		schedule_work(&priv->unthrottle_work);

	वापस count;
पूर्ण

अटल व्योम keyspan_pda_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	port->tx_bytes -= urb->transfer_buffer_length;
	__set_bit(0, &port->ग_लिखो_urbs_मुक्त);
	spin_unlock_irqrestore(&port->lock, flags);

	keyspan_pda_ग_लिखो_start(port);

	usb_serial_port_softपूर्णांक(port);
पूर्ण

अटल पूर्णांक keyspan_pda_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
		स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक rc;

	dev_dbg(&port->dev, "%s - count = %d\n", __func__, count);

	अगर (!count)
		वापस 0;

	count = kfअगरo_in_locked(&port->ग_लिखो_fअगरo, buf, count, &port->lock);

	rc = keyspan_pda_ग_लिखो_start(port);
	अगर (rc)
		वापस rc;

	वापस count;
पूर्ण

अटल व्योम keyspan_pda_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	काष्ठा usb_serial *serial = port->serial;

	अगर (on)
		keyspan_pda_set_modem_info(serial, BIT(7) | BIT(2));
	अन्यथा
		keyspan_pda_set_modem_info(serial, 0);
पूर्ण


अटल पूर्णांक keyspan_pda_खोलो(काष्ठा tty_काष्ठा *tty,
					काष्ठा usb_serial_port *port)
अणु
	काष्ठा keyspan_pda_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक rc;

	/* find out how much room is in the Tx ring */
	rc = keyspan_pda_get_ग_लिखो_room(priv);
	अगर (rc < 0)
		वापस rc;

	spin_lock_irq(&port->lock);
	priv->tx_room = rc;
	spin_unlock_irq(&port->lock);

	rc = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
	अगर (rc) अणु
		dev_dbg(&port->dev, "%s - usb_submit_urb(read int) failed\n", __func__);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम keyspan_pda_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा keyspan_pda_निजी *priv = usb_get_serial_port_data(port);

	/*
	 * Stop the पूर्णांकerrupt URB first as its completion handler may submit
	 * the ग_लिखो URB.
	 */
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
	usb_समाप्त_urb(port->ग_लिखो_urb);

	cancel_work_sync(&priv->unthrottle_work);

	spin_lock_irq(&port->lock);
	kfअगरo_reset(&port->ग_लिखो_fअगरo);
	spin_unlock_irq(&port->lock);
पूर्ण

/* करोwnload the firmware to a "fake" device (pre-rक्रमागतeration) */
अटल पूर्णांक keyspan_pda_fake_startup(काष्ठा usb_serial *serial)
अणु
	अचिन्हित पूर्णांक vid = le16_to_cpu(serial->dev->descriptor.idVenकरोr);
	स्थिर अक्षर *fw_name;

	/* करोwnload the firmware here ... */
	ezusb_fx1_set_reset(serial->dev, 1);

	चयन (vid) अणु
	हाल KEYSPAN_VENDOR_ID:
		fw_name = "keyspan_pda/keyspan_pda.fw";
		अवरोध;
	हाल XIRCOM_VENDOR_ID:
	हाल ENTREGA_VENDOR_ID:
		fw_name = "keyspan_pda/xircom_pgs.fw";
		अवरोध;
	शेष:
		dev_err(&serial->dev->dev, "%s: unknown vendor, aborting.\n",
			__func__);
		वापस -ENODEV;
	पूर्ण

	अगर (ezusb_fx1_ihex_firmware_करोwnload(serial->dev, fw_name) < 0) अणु
		dev_err(&serial->dev->dev, "failed to load firmware \"%s\"\n",
			fw_name);
		वापस -ENOENT;
	पूर्ण

	/*
	 * After करोwnloading firmware rक्रमागतeration will occur in a moment and
	 * the new device will bind to the real driver.
	 */

	/* We want this device to fail to have a driver asचिन्हित to it. */
	वापस 1;
पूर्ण

MODULE_FIRMWARE("keyspan_pda/keyspan_pda.fw");
MODULE_FIRMWARE("keyspan_pda/xircom_pgs.fw");

अटल पूर्णांक keyspan_pda_port_probe(काष्ठा usb_serial_port *port)
अणु

	काष्ठा keyspan_pda_निजी *priv;

	priv = kदो_स्मृति(माप(काष्ठा keyspan_pda_निजी), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	INIT_WORK(&priv->unthrottle_work, keyspan_pda_request_unthrottle);
	priv->port = port;

	usb_set_serial_port_data(port, priv);

	वापस 0;
पूर्ण

अटल व्योम keyspan_pda_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा keyspan_pda_निजी *priv;

	priv = usb_get_serial_port_data(port);
	kमुक्त(priv);
पूर्ण

अटल काष्ठा usb_serial_driver keyspan_pda_fake_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"keyspan_pda_pre",
	पूर्ण,
	.description =		"Keyspan PDA - (prerenumeration)",
	.id_table =		id_table_fake,
	.num_ports =		1,
	.attach =		keyspan_pda_fake_startup,
पूर्ण;

अटल काष्ठा usb_serial_driver keyspan_pda_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"keyspan_pda",
	पूर्ण,
	.description =		"Keyspan PDA",
	.id_table =		id_table_std,
	.num_ports =		1,
	.num_bulk_out =		1,
	.num_पूर्णांकerrupt_in =	1,
	.dtr_rts =		keyspan_pda_dtr_rts,
	.खोलो =			keyspan_pda_खोलो,
	.बंद =		keyspan_pda_बंद,
	.ग_लिखो =		keyspan_pda_ग_लिखो,
	.ग_लिखो_bulk_callback =	keyspan_pda_ग_लिखो_bulk_callback,
	.पढ़ो_पूर्णांक_callback =	keyspan_pda_rx_पूर्णांकerrupt,
	.throttle =		keyspan_pda_rx_throttle,
	.unthrottle =		keyspan_pda_rx_unthrottle,
	.set_termios =		keyspan_pda_set_termios,
	.अवरोध_ctl =		keyspan_pda_अवरोध_ctl,
	.tiocmget =		keyspan_pda_tiocmget,
	.tiocmset =		keyspan_pda_tiocmset,
	.port_probe =		keyspan_pda_port_probe,
	.port_हटाओ =		keyspan_pda_port_हटाओ,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&keyspan_pda_device,
	&keyspan_pda_fake_device,
	शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table_combined);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
