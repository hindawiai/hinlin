<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2009 by Bart Hartgers (bart.hartgers+ark3116@gmail.com)
 * Original version:
 * Copyright (C) 2006
 *   Simon Schulz (ark3116_driver <at> auctionant.de)
 *
 * ark3116
 * - implements a driver क्रम the arkmicro ark3116 chipset (venकरोr=0x6547,
 *   productid=0x0232) (used in a datacable called KQ-U8A)
 *
 * Supports full modem status lines, अवरोध, hardware flow control. Does not
 * support software flow control, since I करो not know how to enable it in hw.
 *
 * This driver is a essentially new implementation. I initially dug
 * पूर्णांकo the old ark3116.c driver and suddenly realized the ark3116 is
 * a 16450 with a USB पूर्णांकerface glued to it. See comments at the
 * bottom of this file.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/tty.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>

#घोषणा DRIVER_AUTHOR "Bart Hartgers <bart.hartgers+ark3116@gmail.com>"
#घोषणा DRIVER_DESC "USB ARK3116 serial/IrDA driver"
#घोषणा DRIVER_DEV_DESC "ARK3116 RS232/IrDA"
#घोषणा DRIVER_NAME "ark3116"

/* usb समयout of 1 second */
#घोषणा ARK_TIMEOUT 1000

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(0x6547, 0x0232) पूर्ण,
	अणु USB_DEVICE(0x18ec, 0x3118) पूर्ण,		/* USB to IrDA adapter */
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

अटल पूर्णांक is_irda(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_device *dev = serial->dev;
	अगर (le16_to_cpu(dev->descriptor.idVenकरोr) == 0x18ec &&
			le16_to_cpu(dev->descriptor.idProduct) == 0x3118)
		वापस 1;
	वापस 0;
पूर्ण

काष्ठा ark3116_निजी अणु
	पूर्णांक			irda;	/* 1 क्रम irda device */

	/* protects hw रेजिस्टर updates */
	काष्ठा mutex		hw_lock;

	पूर्णांक			quot;	/* baudrate भागisor */
	__u32			lcr;	/* line control रेजिस्टर value */
	__u32			hcr;	/* handshake control रेजिस्टर (0x8)
					 * value */
	__u32			mcr;	/* modem control रेजिस्टर value */

	/* protects the status values below */
	spinlock_t		status_lock;
	__u32			msr;	/* modem status रेजिस्टर value */
	__u32			lsr;	/* line status रेजिस्टर value */
पूर्ण;

अटल पूर्णांक ark3116_ग_लिखो_reg(काष्ठा usb_serial *serial,
			     अचिन्हित reg, __u8 val)
अणु
	पूर्णांक result;
	 /* 0xfe 0x40 are magic values taken from original driver */
	result = usb_control_msg(serial->dev,
				 usb_sndctrlpipe(serial->dev, 0),
				 0xfe, 0x40, val, reg,
				 शून्य, 0, ARK_TIMEOUT);
	अगर (result)
		वापस result;

	वापस 0;
पूर्ण

अटल पूर्णांक ark3116_पढ़ो_reg(काष्ठा usb_serial *serial,
			    अचिन्हित reg, अचिन्हित अक्षर *buf)
अणु
	पूर्णांक result;
	/* 0xfe 0xc0 are magic values taken from original driver */
	result = usb_control_msg(serial->dev,
				 usb_rcvctrlpipe(serial->dev, 0),
				 0xfe, 0xc0, 0, reg,
				 buf, 1, ARK_TIMEOUT);
	अगर (result < 1) अणु
		dev_err(&serial->पूर्णांकerface->dev,
				"failed to read register %u: %d\n",
				reg, result);
		अगर (result >= 0)
			result = -EIO;

		वापस result;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक calc_भागisor(पूर्णांक bps)
अणु
	/* Original ark3116 made some exceptions in rounding here
	 * because winकरोws did the same. Assume that is not really
	 * necessary.
	 * Crystal is 12MHz, probably because of USB, but we भागide by 4?
	 */
	वापस (12000000 + 2*bps) / (4*bps);
पूर्ण

अटल पूर्णांक ark3116_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा ark3116_निजी *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_init(&priv->hw_lock);
	spin_lock_init(&priv->status_lock);

	priv->irda = is_irda(serial);

	usb_set_serial_port_data(port, priv);

	/* setup the hardware */
	ark3116_ग_लिखो_reg(serial, UART_IER, 0);
	/* disable DMA */
	ark3116_ग_लिखो_reg(serial, UART_FCR, 0);
	/* handshake control */
	priv->hcr = 0;
	ark3116_ग_लिखो_reg(serial, 0x8     , 0);
	/* modem control */
	priv->mcr = 0;
	ark3116_ग_लिखो_reg(serial, UART_MCR, 0);

	अगर (!(priv->irda)) अणु
		ark3116_ग_लिखो_reg(serial, 0xb , 0);
	पूर्ण अन्यथा अणु
		ark3116_ग_लिखो_reg(serial, 0xb , 1);
		ark3116_ग_लिखो_reg(serial, 0xc , 0);
		ark3116_ग_लिखो_reg(serial, 0xd , 0x41);
		ark3116_ग_लिखो_reg(serial, 0xa , 1);
	पूर्ण

	/* setup baudrate */
	ark3116_ग_लिखो_reg(serial, UART_LCR, UART_LCR_DLAB);

	/* setup क्रम 9600 8N1 */
	priv->quot = calc_भागisor(9600);
	ark3116_ग_लिखो_reg(serial, UART_DLL, priv->quot & 0xff);
	ark3116_ग_लिखो_reg(serial, UART_DLM, (priv->quot>>8) & 0xff);

	priv->lcr = UART_LCR_WLEN8;
	ark3116_ग_लिखो_reg(serial, UART_LCR, UART_LCR_WLEN8);

	ark3116_ग_लिखो_reg(serial, 0xe, 0);

	अगर (priv->irda)
		ark3116_ग_लिखो_reg(serial, 0x9, 0);

	dev_info(&port->dev, "using %s mode\n", priv->irda ? "IrDA" : "RS232");

	वापस 0;
पूर्ण

अटल व्योम ark3116_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा ark3116_निजी *priv = usb_get_serial_port_data(port);

	/* device is बंदd, so URBs and DMA should be करोwn */
	mutex_destroy(&priv->hw_lock);
	kमुक्त(priv);
पूर्ण

अटल व्योम ark3116_set_termios(काष्ठा tty_काष्ठा *tty,
				काष्ठा usb_serial_port *port,
				काष्ठा ktermios *old_termios)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा ark3116_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा ktermios *termios = &tty->termios;
	अचिन्हित पूर्णांक cflag = termios->c_cflag;
	पूर्णांक bps = tty_get_baud_rate(tty);
	पूर्णांक quot;
	__u8 lcr, hcr, eval;

	/* set data bit count */
	चयन (cflag & CSIZE) अणु
	हाल CS5:
		lcr = UART_LCR_WLEN5;
		अवरोध;
	हाल CS6:
		lcr = UART_LCR_WLEN6;
		अवरोध;
	हाल CS7:
		lcr = UART_LCR_WLEN7;
		अवरोध;
	शेष:
	हाल CS8:
		lcr = UART_LCR_WLEN8;
		अवरोध;
	पूर्ण
	अगर (cflag & CSTOPB)
		lcr |= UART_LCR_STOP;
	अगर (cflag & PARENB)
		lcr |= UART_LCR_PARITY;
	अगर (!(cflag & PARODD))
		lcr |= UART_LCR_EPAR;
#अगर_घोषित CMSPAR
	अगर (cflag & CMSPAR)
		lcr |= UART_LCR_SPAR;
#पूर्ण_अगर
	/* handshake control */
	hcr = (cflag & CRTSCTS) ? 0x03 : 0x00;

	/* calc baudrate */
	dev_dbg(&port->dev, "%s - setting bps to %d\n", __func__, bps);
	eval = 0;
	चयन (bps) अणु
	हाल 0:
		quot = calc_भागisor(9600);
		अवरोध;
	शेष:
		अगर ((bps < 75) || (bps > 3000000))
			bps = 9600;
		quot = calc_भागisor(bps);
		अवरोध;
	हाल 460800:
		eval = 1;
		quot = calc_भागisor(bps);
		अवरोध;
	हाल 921600:
		eval = 2;
		quot = calc_भागisor(bps);
		अवरोध;
	पूर्ण

	/* Update state: synchronize */
	mutex_lock(&priv->hw_lock);

	/* keep old LCR_SBC bit */
	lcr |= (priv->lcr & UART_LCR_SBC);

	dev_dbg(&port->dev, "%s - setting hcr:0x%02x,lcr:0x%02x,quot:%d\n",
		__func__, hcr, lcr, quot);

	/* handshake control */
	अगर (priv->hcr != hcr) अणु
		priv->hcr = hcr;
		ark3116_ग_लिखो_reg(serial, 0x8, hcr);
	पूर्ण

	/* baudrate */
	अगर (priv->quot != quot) अणु
		priv->quot = quot;
		priv->lcr = lcr; /* need to ग_लिखो lcr anyway */

		/* disable DMA since transmit/receive is
		 * shaकरोwed by UART_DLL
		 */
		ark3116_ग_लिखो_reg(serial, UART_FCR, 0);

		ark3116_ग_लिखो_reg(serial, UART_LCR,
				  lcr|UART_LCR_DLAB);
		ark3116_ग_लिखो_reg(serial, UART_DLL, quot & 0xff);
		ark3116_ग_लिखो_reg(serial, UART_DLM, (quot>>8) & 0xff);

		/* restore lcr */
		ark3116_ग_लिखो_reg(serial, UART_LCR, lcr);
		/* magic baudrate thingy: not sure what it करोes,
		 * but winकरोws करोes this as well.
		 */
		ark3116_ग_लिखो_reg(serial, 0xe, eval);

		/* enable DMA */
		ark3116_ग_लिखो_reg(serial, UART_FCR, UART_FCR_DMA_SELECT);
	पूर्ण अन्यथा अगर (priv->lcr != lcr) अणु
		priv->lcr = lcr;
		ark3116_ग_लिखो_reg(serial, UART_LCR, lcr);
	पूर्ण

	mutex_unlock(&priv->hw_lock);

	/* check क्रम software flow control */
	अगर (I_IXOFF(tty) || I_IXON(tty)) अणु
		dev_warn(&port->dev,
				"software flow control not implemented\n");
	पूर्ण

	/* Don't reग_लिखो B0 */
	अगर (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, bps, bps);
पूर्ण

अटल व्योम ark3116_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;

	/* disable DMA */
	ark3116_ग_लिखो_reg(serial, UART_FCR, 0);

	/* deactivate पूर्णांकerrupts */
	ark3116_ग_लिखो_reg(serial, UART_IER, 0);

	usb_serial_generic_बंद(port);

	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
पूर्ण

अटल पूर्णांक ark3116_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा ark3116_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा usb_serial *serial = port->serial;
	अचिन्हित अक्षर *buf;
	पूर्णांक result;

	buf = kदो_स्मृति(1, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	result = usb_serial_generic_खोलो(tty, port);
	अगर (result) अणु
		dev_dbg(&port->dev,
			"%s - usb_serial_generic_open failed: %d\n",
			__func__, result);
		जाओ err_मुक्त;
	पूर्ण

	/* हटाओ any data still left: also clears error state */
	ark3116_पढ़ो_reg(serial, UART_RX, buf);

	/* पढ़ो modem status */
	result = ark3116_पढ़ो_reg(serial, UART_MSR, buf);
	अगर (result)
		जाओ err_बंद;
	priv->msr = *buf;

	/* पढ़ो line status */
	result = ark3116_पढ़ो_reg(serial, UART_LSR, buf);
	अगर (result)
		जाओ err_बंद;
	priv->lsr = *buf;

	result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
	अगर (result) अणु
		dev_err(&port->dev, "submit irq_in urb failed %d\n",
			result);
		जाओ err_बंद;
	पूर्ण

	/* activate पूर्णांकerrupts */
	ark3116_ग_लिखो_reg(port->serial, UART_IER, UART_IER_MSI|UART_IER_RLSI);

	/* enable DMA */
	ark3116_ग_लिखो_reg(port->serial, UART_FCR, UART_FCR_DMA_SELECT);

	/* setup termios */
	अगर (tty)
		ark3116_set_termios(tty, port, शून्य);

	kमुक्त(buf);

	वापस 0;

err_बंद:
	usb_serial_generic_बंद(port);
err_मुक्त:
	kमुक्त(buf);

	वापस result;
पूर्ण

अटल पूर्णांक ark3116_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा ark3116_निजी *priv = usb_get_serial_port_data(port);
	__u32 status;
	__u32 ctrl;
	अचिन्हित दीर्घ flags;

	mutex_lock(&priv->hw_lock);
	ctrl = priv->mcr;
	mutex_unlock(&priv->hw_lock);

	spin_lock_irqsave(&priv->status_lock, flags);
	status = priv->msr;
	spin_unlock_irqrestore(&priv->status_lock, flags);

	वापस  (status & UART_MSR_DSR  ? TIOCM_DSR  : 0) |
		(status & UART_MSR_CTS  ? TIOCM_CTS  : 0) |
		(status & UART_MSR_RI   ? TIOCM_RI   : 0) |
		(status & UART_MSR_DCD  ? TIOCM_CD   : 0) |
		(ctrl   & UART_MCR_DTR  ? TIOCM_DTR  : 0) |
		(ctrl   & UART_MCR_RTS  ? TIOCM_RTS  : 0) |
		(ctrl   & UART_MCR_OUT1 ? TIOCM_OUT1 : 0) |
		(ctrl   & UART_MCR_OUT2 ? TIOCM_OUT2 : 0);
पूर्ण

अटल पूर्णांक ark3116_tiocmset(काष्ठा tty_काष्ठा *tty,
			अचिन्हित set, अचिन्हित clr)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा ark3116_निजी *priv = usb_get_serial_port_data(port);

	/* we need to take the mutex here, to make sure that the value
	 * in priv->mcr is actually the one that is in the hardware
	 */

	mutex_lock(&priv->hw_lock);

	अगर (set & TIOCM_RTS)
		priv->mcr |= UART_MCR_RTS;
	अगर (set & TIOCM_DTR)
		priv->mcr |= UART_MCR_DTR;
	अगर (set & TIOCM_OUT1)
		priv->mcr |= UART_MCR_OUT1;
	अगर (set & TIOCM_OUT2)
		priv->mcr |= UART_MCR_OUT2;
	अगर (clr & TIOCM_RTS)
		priv->mcr &= ~UART_MCR_RTS;
	अगर (clr & TIOCM_DTR)
		priv->mcr &= ~UART_MCR_DTR;
	अगर (clr & TIOCM_OUT1)
		priv->mcr &= ~UART_MCR_OUT1;
	अगर (clr & TIOCM_OUT2)
		priv->mcr &= ~UART_MCR_OUT2;

	ark3116_ग_लिखो_reg(port->serial, UART_MCR, priv->mcr);

	mutex_unlock(&priv->hw_lock);

	वापस 0;
पूर्ण

अटल व्योम ark3116_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा ark3116_निजी *priv = usb_get_serial_port_data(port);

	/* LCR is also used क्रम other things: protect access */
	mutex_lock(&priv->hw_lock);

	अगर (अवरोध_state)
		priv->lcr |= UART_LCR_SBC;
	अन्यथा
		priv->lcr &= ~UART_LCR_SBC;

	ark3116_ग_लिखो_reg(port->serial, UART_LCR, priv->lcr);

	mutex_unlock(&priv->hw_lock);
पूर्ण

अटल व्योम ark3116_update_msr(काष्ठा usb_serial_port *port, __u8 msr)
अणु
	काष्ठा ark3116_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->status_lock, flags);
	priv->msr = msr;
	spin_unlock_irqrestore(&priv->status_lock, flags);

	अगर (msr & UART_MSR_ANY_DELTA) अणु
		/* update input line counters */
		अगर (msr & UART_MSR_DCTS)
			port->icount.cts++;
		अगर (msr & UART_MSR_DDSR)
			port->icount.dsr++;
		अगर (msr & UART_MSR_DDCD)
			port->icount.dcd++;
		अगर (msr & UART_MSR_TERI)
			port->icount.rng++;
		wake_up_पूर्णांकerruptible(&port->port.delta_msr_रुको);
	पूर्ण
पूर्ण

अटल व्योम ark3116_update_lsr(काष्ठा usb_serial_port *port, __u8 lsr)
अणु
	काष्ठा ark3116_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->status_lock, flags);
	/* combine bits */
	priv->lsr |= lsr;
	spin_unlock_irqrestore(&priv->status_lock, flags);

	अगर (lsr&UART_LSR_BRK_ERROR_BITS) अणु
		अगर (lsr & UART_LSR_BI)
			port->icount.brk++;
		अगर (lsr & UART_LSR_FE)
			port->icount.frame++;
		अगर (lsr & UART_LSR_PE)
			port->icount.parity++;
		अगर (lsr & UART_LSR_OE)
			port->icount.overrun++;
	पूर्ण
पूर्ण

अटल व्योम ark3116_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	पूर्णांक status = urb->status;
	स्थिर __u8 *data = urb->transfer_buffer;
	पूर्णांक result;

	चयन (status) अणु
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
		अवरोध;
	हाल 0: /* success */
		/* discovered this by trail and error... */
		अगर ((urb->actual_length == 4) && (data[0] == 0xe8)) अणु
			स्थिर __u8 id = data[1]&UART_IIR_ID;
			dev_dbg(&port->dev, "%s: iir=%02x\n", __func__, data[1]);
			अगर (id == UART_IIR_MSI) अणु
				dev_dbg(&port->dev, "%s: msr=%02x\n",
					__func__, data[3]);
				ark3116_update_msr(port, data[3]);
				अवरोध;
			पूर्ण अन्यथा अगर (id == UART_IIR_RLSI) अणु
				dev_dbg(&port->dev, "%s: lsr=%02x\n",
					__func__, data[2]);
				ark3116_update_lsr(port, data[2]);
				अवरोध;
			पूर्ण
		पूर्ण
		/*
		 * Not sure what this data meant...
		 */
		usb_serial_debug_data(&port->dev, __func__,
				      urb->actual_length,
				      urb->transfer_buffer);
		अवरोध;
	पूर्ण

	result = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (result)
		dev_err(&port->dev, "failed to resubmit interrupt urb: %d\n",
			result);
पूर्ण


/* Data comes in via the bulk (data) URB, errors/पूर्णांकerrupts via the पूर्णांक URB.
 * This means that we cannot be sure which data byte has an associated error
 * condition, so we report an error क्रम all data in the next bulk पढ़ो.
 *
 * Actually, there might even be a winकरोw between the bulk data leaving the
 * ark and पढ़ोing/resetting the lsr in the पढ़ो_bulk_callback where an
 * पूर्णांकerrupt क्रम the next data block could come in.
 * Without somekind of ordering on the ark, we would have to report the
 * error क्रम the next block of data as well...
 * For now, let's pretend this can't happen.
 */
अटल व्योम ark3116_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा ark3116_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	अक्षर tty_flag = TTY_NORMAL;
	अचिन्हित दीर्घ flags;
	__u32 lsr;

	/* update line status */
	spin_lock_irqsave(&priv->status_lock, flags);
	lsr = priv->lsr;
	priv->lsr &= ~UART_LSR_BRK_ERROR_BITS;
	spin_unlock_irqrestore(&priv->status_lock, flags);

	अगर (!urb->actual_length)
		वापस;

	अगर (lsr & UART_LSR_BRK_ERROR_BITS) अणु
		अगर (lsr & UART_LSR_BI)
			tty_flag = TTY_BREAK;
		अन्यथा अगर (lsr & UART_LSR_PE)
			tty_flag = TTY_PARITY;
		अन्यथा अगर (lsr & UART_LSR_FE)
			tty_flag = TTY_FRAME;

		/* overrun is special, not associated with a अक्षर */
		अगर (lsr & UART_LSR_OE)
			tty_insert_flip_अक्षर(&port->port, 0, TTY_OVERRUN);
	पूर्ण
	tty_insert_flip_string_fixed_flag(&port->port, data, tty_flag,
							urb->actual_length);
	tty_flip_buffer_push(&port->port);
पूर्ण

अटल काष्ठा usb_serial_driver ark3116_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"ark3116",
	पूर्ण,
	.id_table =		id_table,
	.num_ports =		1,
	.num_bulk_in =		1,
	.num_bulk_out =		1,
	.num_पूर्णांकerrupt_in =	1,
	.port_probe =		ark3116_port_probe,
	.port_हटाओ =		ark3116_port_हटाओ,
	.set_termios =		ark3116_set_termios,
	.tiocmget =		ark3116_tiocmget,
	.tiocmset =		ark3116_tiocmset,
	.tiocmiरुको =		usb_serial_generic_tiocmiरुको,
	.get_icount =		usb_serial_generic_get_icount,
	.खोलो =			ark3116_खोलो,
	.बंद =		ark3116_बंद,
	.अवरोध_ctl = 		ark3116_अवरोध_ctl,
	.पढ़ो_पूर्णांक_callback = 	ark3116_पढ़ो_पूर्णांक_callback,
	.process_पढ़ो_urb =	ark3116_process_पढ़ो_urb,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&ark3116_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_LICENSE("GPL");

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

/*
 * The following describes what I learned from studying the old
 * ark3116.c driver, disassembling the winकरोws driver, and some lucky
 * guesses. Since I करो not have any datasheet or other
 * करोcumentation, inaccuracies are almost guaranteed.
 *
 * Some specs क्रम the ARK3116 can be found here:
 * http://web.archive.org/web/20060318000438/
 *   www.arkmicro.com/en/products/view.php?id=10
 * On that page, 2 GPIO pins are mentioned: I assume these are the
 * OUT1 and OUT2 pins of the UART, so I added support क्रम those
 * through the MCR. Since the pins are not available on my hardware,
 * I could not verअगरy this.
 * Also, it states there is "on-chip hardware flow control". I have
 * discovered how to enable that. Unक्रमtunately, I करो not know how to
 * enable XON/XOFF (software) flow control, which would need support
 * from the chip as well to work. Because of the wording on the web
 * page there is a real possibility the chip simply करोes not support
 * software flow control.
 *
 * I got my ark3116 as part of a mobile phone adapter cable. On the
 * PCB, the following numbered contacts are present:
 *
 *  1:- +5V
 *  2:o DTR
 *  3:i RX
 *  4:i DCD
 *  5:o RTS
 *  6:o TX
 *  7:i RI
 *  8:i DSR
 * 10:- 0V
 * 11:i CTS
 *
 * On my chip, all संकेतs seem to be 3.3V, but 5V tolerant. But that
 * may be dअगरferent क्रम the one you have ;-).
 *
 * The winकरोws driver limits the रेजिस्टरs to 0-F, so I assume there
 * are actually 16 present on the device.
 *
 * On an UART पूर्णांकerrupt, 4 bytes of data come in on the पूर्णांकerrupt
 * endpoपूर्णांक. The bytes are 0xe8 IIR LSR MSR.
 *
 * The baudrate seems to be generated from the 12MHz crystal, using
 * 4-बार subsampling. So quot=12e6/(4*baud). Also see description
 * of रेजिस्टर E.
 *
 * Registers 0-7:
 * These seem to be the same as क्रम a regular 16450. The FCR is set
 * to UART_FCR_DMA_SELECT (0x8), I guess to enable transfers between
 * the UART and the USB bridge/DMA engine.
 *
 * Register 8:
 * By trial and error, I found out that bit 0 enables hardware CTS,
 * stopping TX when CTS is +5V. Bit 1 करोes the same क्रम RTS, making
 * RTS +5V when the 3116 cannot transfer the data to the USB bus
 * (verअगरied by disabling the पढ़ोing URB). Note that as far as I can
 * tell, the winकरोws driver करोes NOT use this, so there might be some
 * hardware bug or something.
 *
 * According to a patch provided here
 * https://lore.kernel.org/lkml/200907261419.50702.linux@rainbow-software.org
 * the ARK3116 can also be used as an IrDA करोngle. Since I करो not have
 * such a thing, I could not investigate that aspect. However, I can
 * speculate ;-).
 *
 * - IrDA encodes data dअगरferently than RS232. Most likely, one of
 *   the bits in रेजिस्टरs 9..E enables the IR ENDEC (encoder/decoder).
 * - Depending on the IR transceiver, the input and output need to be
 *   inverted, so there are probably bits क्रम that as well.
 * - IrDA is half-duplex, so there should be a bit क्रम selecting that.
 *
 * This still leaves at least two रेजिस्टरs unaccounted क्रम. Perhaps
 * The chip can करो XON/XOFF or CRC in HW?
 *
 * Register 9:
 * Set to 0x00 क्रम IrDA, when the baudrate is initialised.
 *
 * Register A:
 * Set to 0x01 क्रम IrDA, at init.
 *
 * Register B:
 * Set to 0x01 क्रम IrDA, 0x00 क्रम RS232, at init.
 *
 * Register C:
 * Set to 00 क्रम IrDA, at init.
 *
 * Register D:
 * Set to 0x41 क्रम IrDA, at init.
 *
 * Register E:
 * Somekind of baudrate override. The winकरोws driver seems to set
 * this to 0x00 क्रम normal baudrates, 0x01 क्रम 460800, 0x02 क्रम 921600.
 * Since 460800 and 921600 cannot be obtained by भागiding 3MHz by an पूर्णांकeger,
 * it could be somekind of subभागisor thingy.
 * However,it करोes not seem to करो anything: selecting 921600 (भागisor 3,
 * reg E=2), still माला_लो 1 MHz. I also checked अगर रेजिस्टरs 9, C or F would
 * work, but they करोn't.
 *
 * Register F: unknown
 */
