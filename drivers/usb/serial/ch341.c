<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2007, Frank A Kingswood <frank@kingswood-consulting.co.uk>
 * Copyright 2007, Werner Cornelius <werner@cornelius-consult.de>
 * Copyright 2009, Boris Hajduk <boris@hajduk.org>
 *
 * ch341.c implements a serial port driver क्रम the Winchiphead CH341.
 *
 * The CH341 device can be used to implement an RS232 asynchronous
 * serial port, an IEEE-1284 parallel prपूर्णांकer port or a memory-like
 * पूर्णांकerface. In all हालs the CH341 supports an I2C पूर्णांकerface as well.
 * This driver only supports the asynchronous serial पूर्णांकerface.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/serial.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा DEFAULT_BAUD_RATE 9600
#घोषणा DEFAULT_TIMEOUT   1000

/* flags क्रम IO-Bits */
#घोषणा CH341_BIT_RTS (1 << 6)
#घोषणा CH341_BIT_DTR (1 << 5)

/******************************/
/* पूर्णांकerrupt pipe definitions */
/******************************/
/* always 4 पूर्णांकerrupt bytes */
/* first irq byte normally 0x08 */
/* second irq byte base 0x7d + below */
/* third irq byte base 0x94 + below */
/* fourth irq byte normally 0xee */

/* second पूर्णांकerrupt byte */
#घोषणा CH341_MULT_STAT 0x04 /* multiple status since last पूर्णांकerrupt event */

/* status वापसed in third पूर्णांकerrupt answer byte, inverted in data
   from irq */
#घोषणा CH341_BIT_CTS 0x01
#घोषणा CH341_BIT_DSR 0x02
#घोषणा CH341_BIT_RI  0x04
#घोषणा CH341_BIT_DCD 0x08
#घोषणा CH341_BITS_MODEM_STAT 0x0f /* all bits */

/* Break support - the inक्रमmation used to implement this was gleaned from
 * the Net/FreeBSD uchcom.c driver by Takanori Watanabe.  Domo arigato.
 */

#घोषणा CH341_REQ_READ_VERSION 0x5F
#घोषणा CH341_REQ_WRITE_REG    0x9A
#घोषणा CH341_REQ_READ_REG     0x95
#घोषणा CH341_REQ_SERIAL_INIT  0xA1
#घोषणा CH341_REQ_MODEM_CTRL   0xA4

#घोषणा CH341_REG_BREAK        0x05
#घोषणा CH341_REG_PRESCALER    0x12
#घोषणा CH341_REG_DIVISOR      0x13
#घोषणा CH341_REG_LCR          0x18
#घोषणा CH341_REG_LCR2         0x25

#घोषणा CH341_NBREAK_BITS      0x01

#घोषणा CH341_LCR_ENABLE_RX    0x80
#घोषणा CH341_LCR_ENABLE_TX    0x40
#घोषणा CH341_LCR_MARK_SPACE   0x20
#घोषणा CH341_LCR_PAR_EVEN     0x10
#घोषणा CH341_LCR_ENABLE_PAR   0x08
#घोषणा CH341_LCR_STOP_BITS_2  0x04
#घोषणा CH341_LCR_CS8          0x03
#घोषणा CH341_LCR_CS7          0x02
#घोषणा CH341_LCR_CS6          0x01
#घोषणा CH341_LCR_CS5          0x00

#घोषणा CH341_QUIRK_LIMITED_PRESCALER	BIT(0)
#घोषणा CH341_QUIRK_SIMULATE_BREAK	BIT(1)

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(0x1a86, 0x5512) पूर्ण,
	अणु USB_DEVICE(0x1a86, 0x5523) पूर्ण,
	अणु USB_DEVICE(0x1a86, 0x7522) पूर्ण,
	अणु USB_DEVICE(0x1a86, 0x7523) पूर्ण,
	अणु USB_DEVICE(0x4348, 0x5523) पूर्ण,
	अणु USB_DEVICE(0x9986, 0x7523) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

काष्ठा ch341_निजी अणु
	spinlock_t lock; /* access lock */
	अचिन्हित baud_rate; /* set baud rate */
	u8 mcr;
	u8 msr;
	u8 lcr;
	अचिन्हित दीर्घ quirks;
	अचिन्हित दीर्घ अवरोध_end;
पूर्ण;

अटल व्योम ch341_set_termios(काष्ठा tty_काष्ठा *tty,
			      काष्ठा usb_serial_port *port,
			      काष्ठा ktermios *old_termios);

अटल पूर्णांक ch341_control_out(काष्ठा usb_device *dev, u8 request,
			     u16 value, u16 index)
अणु
	पूर्णांक r;

	dev_dbg(&dev->dev, "%s - (%02x,%04x,%04x)\n", __func__,
		request, value, index);

	r = usb_control_msg(dev, usb_sndctrlpipe(dev, 0), request,
			    USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
			    value, index, शून्य, 0, DEFAULT_TIMEOUT);
	अगर (r < 0)
		dev_err(&dev->dev, "failed to send control message: %d\n", r);

	वापस r;
पूर्ण

अटल पूर्णांक ch341_control_in(काष्ठा usb_device *dev,
			    u8 request, u16 value, u16 index,
			    अक्षर *buf, अचिन्हित bufsize)
अणु
	पूर्णांक r;

	dev_dbg(&dev->dev, "%s - (%02x,%04x,%04x,%u)\n", __func__,
		request, value, index, bufsize);

	r = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0), request,
			    USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
			    value, index, buf, bufsize, DEFAULT_TIMEOUT);
	अगर (r < (पूर्णांक)bufsize) अणु
		अगर (r >= 0) अणु
			dev_err(&dev->dev,
				"short control message received (%d < %u)\n",
				r, bufsize);
			r = -EIO;
		पूर्ण

		dev_err(&dev->dev, "failed to receive control message: %d\n",
			r);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा CH341_CLKRATE		48000000
#घोषणा CH341_CLK_DIV(ps, fact)	(1 << (12 - 3 * (ps) - (fact)))
#घोषणा CH341_MIN_RATE(ps)	(CH341_CLKRATE / (CH341_CLK_DIV((ps), 1) * 512))

अटल स्थिर speed_t ch341_min_rates[] = अणु
	CH341_MIN_RATE(0),
	CH341_MIN_RATE(1),
	CH341_MIN_RATE(2),
	CH341_MIN_RATE(3),
पूर्ण;

/* Supported range is 46 to 3000000 bps. */
#घोषणा CH341_MIN_BPS	DIV_ROUND_UP(CH341_CLKRATE, CH341_CLK_DIV(0, 0) * 256)
#घोषणा CH341_MAX_BPS	(CH341_CLKRATE / (CH341_CLK_DIV(3, 0) * 2))

/*
 * The device line speed is given by the following equation:
 *
 *	baudrate = 48000000 / (2^(12 - 3 * ps - fact) * भाग), where
 *
 *		0 <= ps <= 3,
 *		0 <= fact <= 1,
 *		2 <= भाग <= 256 अगर fact = 0, or
 *		9 <= भाग <= 256 अगर fact = 1
 */
अटल पूर्णांक ch341_get_भागisor(काष्ठा ch341_निजी *priv, speed_t speed)
अणु
	अचिन्हित पूर्णांक fact, भाग, clk_भाग;
	bool क्रमce_fact0 = false;
	पूर्णांक ps;

	/*
	 * Clamp to supported range, this makes the (ps < 0) and (भाग < 2)
	 * sanity checks below redundant.
	 */
	speed = clamp_val(speed, CH341_MIN_BPS, CH341_MAX_BPS);

	/*
	 * Start with highest possible base घड़ी (fact = 1) that will give a
	 * भागisor strictly less than 512.
	 */
	fact = 1;
	क्रम (ps = 3; ps >= 0; ps--) अणु
		अगर (speed > ch341_min_rates[ps])
			अवरोध;
	पूर्ण

	अगर (ps < 0)
		वापस -EINVAL;

	/* Determine corresponding भागisor, rounding करोwn. */
	clk_भाग = CH341_CLK_DIV(ps, fact);
	भाग = CH341_CLKRATE / (clk_भाग * speed);

	/* Some devices require a lower base घड़ी अगर ps < 3. */
	अगर (ps < 3 && (priv->quirks & CH341_QUIRK_LIMITED_PRESCALER))
		क्रमce_fact0 = true;

	/* Halve base घड़ी (fact = 0) अगर required. */
	अगर (भाग < 9 || भाग > 255 || क्रमce_fact0) अणु
		भाग /= 2;
		clk_भाग *= 2;
		fact = 0;
	पूर्ण

	अगर (भाग < 2)
		वापस -EINVAL;

	/*
	 * Pick next भागisor अगर resulting rate is बंदr to the requested one,
	 * scale up to aव्योम rounding errors on low rates.
	 */
	अगर (16 * CH341_CLKRATE / (clk_भाग * भाग) - 16 * speed >=
			16 * speed - 16 * CH341_CLKRATE / (clk_भाग * (भाग + 1)))
		भाग++;

	/*
	 * Prefer lower base घड़ी (fact = 0) अगर even भागisor.
	 *
	 * Note that this makes the receiver more tolerant to errors.
	 */
	अगर (fact == 1 && भाग % 2 == 0) अणु
		भाग /= 2;
		fact = 0;
	पूर्ण

	वापस (0x100 - भाग) << 8 | fact << 2 | ps;
पूर्ण

अटल पूर्णांक ch341_set_baudrate_lcr(काष्ठा usb_device *dev,
				  काष्ठा ch341_निजी *priv,
				  speed_t baud_rate, u8 lcr)
अणु
	पूर्णांक val;
	पूर्णांक r;

	अगर (!baud_rate)
		वापस -EINVAL;

	val = ch341_get_भागisor(priv, baud_rate);
	अगर (val < 0)
		वापस -EINVAL;

	/*
	 * CH341A buffers data until a full endpoपूर्णांक-size packet (32 bytes)
	 * has been received unless bit 7 is set.
	 */
	val |= BIT(7);

	r = ch341_control_out(dev, CH341_REQ_WRITE_REG,
			      CH341_REG_DIVISOR << 8 | CH341_REG_PRESCALER,
			      val);
	अगर (r)
		वापस r;

	/*
	 * Chip versions beक्रमe version 0x30 as पढ़ो using
	 * CH341_REQ_READ_VERSION used separate रेजिस्टरs क्रम line control
	 * (stop bits, parity and word length). Version 0x30 and above use
	 * CH341_REG_LCR only and CH341_REG_LCR2 is always set to zero.
	 */
	r = ch341_control_out(dev, CH341_REQ_WRITE_REG,
			      CH341_REG_LCR2 << 8 | CH341_REG_LCR, lcr);
	अगर (r)
		वापस r;

	वापस r;
पूर्ण

अटल पूर्णांक ch341_set_handshake(काष्ठा usb_device *dev, u8 control)
अणु
	वापस ch341_control_out(dev, CH341_REQ_MODEM_CTRL, ~control, 0);
पूर्ण

अटल पूर्णांक ch341_get_status(काष्ठा usb_device *dev, काष्ठा ch341_निजी *priv)
अणु
	स्थिर अचिन्हित पूर्णांक size = 2;
	अक्षर *buffer;
	पूर्णांक r;
	अचिन्हित दीर्घ flags;

	buffer = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	r = ch341_control_in(dev, CH341_REQ_READ_REG, 0x0706, 0, buffer, size);
	अगर (r < 0)
		जाओ out;

	spin_lock_irqsave(&priv->lock, flags);
	priv->msr = (~(*buffer)) & CH341_BITS_MODEM_STAT;
	spin_unlock_irqrestore(&priv->lock, flags);

out:	kमुक्त(buffer);
	वापस r;
पूर्ण

/* -------------------------------------------------------------------------- */

अटल पूर्णांक ch341_configure(काष्ठा usb_device *dev, काष्ठा ch341_निजी *priv)
अणु
	स्थिर अचिन्हित पूर्णांक size = 2;
	अक्षर *buffer;
	पूर्णांक r;

	buffer = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	/* expect two bytes 0x27 0x00 */
	r = ch341_control_in(dev, CH341_REQ_READ_VERSION, 0, 0, buffer, size);
	अगर (r < 0)
		जाओ out;
	dev_dbg(&dev->dev, "Chip version: 0x%02x\n", buffer[0]);

	r = ch341_control_out(dev, CH341_REQ_SERIAL_INIT, 0, 0);
	अगर (r < 0)
		जाओ out;

	r = ch341_set_baudrate_lcr(dev, priv, priv->baud_rate, priv->lcr);
	अगर (r < 0)
		जाओ out;

	r = ch341_set_handshake(dev, priv->mcr);

out:	kमुक्त(buffer);
	वापस r;
पूर्ण

अटल पूर्णांक ch341_detect_quirks(काष्ठा usb_serial_port *port)
अणु
	काष्ठा ch341_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा usb_device *udev = port->serial->dev;
	स्थिर अचिन्हित पूर्णांक size = 2;
	अचिन्हित दीर्घ quirks = 0;
	अक्षर *buffer;
	पूर्णांक r;

	buffer = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	/*
	 * A subset of CH34x devices करोes not support all features. The
	 * prescaler is limited and there is no support क्रम sending a RS232
	 * अवरोध condition. A पढ़ो failure when trying to set up the latter is
	 * used to detect these devices.
	 */
	r = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), CH341_REQ_READ_REG,
			    USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
			    CH341_REG_BREAK, 0, buffer, size, DEFAULT_TIMEOUT);
	अगर (r == -EPIPE) अणु
		dev_info(&port->dev, "break control not supported, using simulated break\n");
		quirks = CH341_QUIRK_LIMITED_PRESCALER | CH341_QUIRK_SIMULATE_BREAK;
		r = 0;
		जाओ out;
	पूर्ण

	अगर (r != size) अणु
		अगर (r >= 0)
			r = -EIO;
		dev_err(&port->dev, "failed to read break control: %d\n", r);
		जाओ out;
	पूर्ण

	r = 0;
out:
	kमुक्त(buffer);

	अगर (quirks) अणु
		dev_dbg(&port->dev, "enabling quirk flags: 0x%02lx\n", quirks);
		priv->quirks |= quirks;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक ch341_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा ch341_निजी *priv;
	पूर्णांक r;

	priv = kzalloc(माप(काष्ठा ch341_निजी), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	spin_lock_init(&priv->lock);
	priv->baud_rate = DEFAULT_BAUD_RATE;
	/*
	 * Some CH340 devices appear unable to change the initial LCR
	 * settings, so set a sane 8N1 शेष.
	 */
	priv->lcr = CH341_LCR_ENABLE_RX | CH341_LCR_ENABLE_TX | CH341_LCR_CS8;

	r = ch341_configure(port->serial->dev, priv);
	अगर (r < 0)
		जाओ error;

	usb_set_serial_port_data(port, priv);

	r = ch341_detect_quirks(port);
	अगर (r < 0)
		जाओ error;

	वापस 0;

error:	kमुक्त(priv);
	वापस r;
पूर्ण

अटल व्योम ch341_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा ch341_निजी *priv;

	priv = usb_get_serial_port_data(port);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक ch341_carrier_उठाओd(काष्ठा usb_serial_port *port)
अणु
	काष्ठा ch341_निजी *priv = usb_get_serial_port_data(port);
	अगर (priv->msr & CH341_BIT_DCD)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम ch341_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	काष्ठा ch341_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;

	/* drop DTR and RTS */
	spin_lock_irqsave(&priv->lock, flags);
	अगर (on)
		priv->mcr |= CH341_BIT_RTS | CH341_BIT_DTR;
	अन्यथा
		priv->mcr &= ~(CH341_BIT_RTS | CH341_BIT_DTR);
	spin_unlock_irqrestore(&priv->lock, flags);
	ch341_set_handshake(port->serial->dev, priv->mcr);
पूर्ण

अटल व्योम ch341_बंद(काष्ठा usb_serial_port *port)
अणु
	usb_serial_generic_बंद(port);
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
पूर्ण


/* खोलो this device, set शेष parameters */
अटल पूर्णांक ch341_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा ch341_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक r;

	अगर (tty)
		ch341_set_termios(tty, port, शून्य);

	dev_dbg(&port->dev, "%s - submitting interrupt urb\n", __func__);
	r = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
	अगर (r) अणु
		dev_err(&port->dev, "%s - failed to submit interrupt urb: %d\n",
			__func__, r);
		वापस r;
	पूर्ण

	r = ch341_get_status(port->serial->dev, priv);
	अगर (r < 0) अणु
		dev_err(&port->dev, "failed to read modem status: %d\n", r);
		जाओ err_समाप्त_पूर्णांकerrupt_urb;
	पूर्ण

	r = usb_serial_generic_खोलो(tty, port);
	अगर (r)
		जाओ err_समाप्त_पूर्णांकerrupt_urb;

	वापस 0;

err_समाप्त_पूर्णांकerrupt_urb:
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);

	वापस r;
पूर्ण

/* Old_termios contains the original termios settings and
 * tty->termios contains the new setting to be used.
 */
अटल व्योम ch341_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा ch341_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित baud_rate;
	अचिन्हित दीर्घ flags;
	u8 lcr;
	पूर्णांक r;

	/* redundant changes may cause the chip to lose bytes */
	अगर (old_termios && !tty_termios_hw_change(&tty->termios, old_termios))
		वापस;

	baud_rate = tty_get_baud_rate(tty);

	lcr = CH341_LCR_ENABLE_RX | CH341_LCR_ENABLE_TX;

	चयन (C_CSIZE(tty)) अणु
	हाल CS5:
		lcr |= CH341_LCR_CS5;
		अवरोध;
	हाल CS6:
		lcr |= CH341_LCR_CS6;
		अवरोध;
	हाल CS7:
		lcr |= CH341_LCR_CS7;
		अवरोध;
	हाल CS8:
		lcr |= CH341_LCR_CS8;
		अवरोध;
	पूर्ण

	अगर (C_PARENB(tty)) अणु
		lcr |= CH341_LCR_ENABLE_PAR;
		अगर (C_PARODD(tty) == 0)
			lcr |= CH341_LCR_PAR_EVEN;
		अगर (C_CMSPAR(tty))
			lcr |= CH341_LCR_MARK_SPACE;
	पूर्ण

	अगर (C_CSTOPB(tty))
		lcr |= CH341_LCR_STOP_BITS_2;

	अगर (baud_rate) अणु
		priv->baud_rate = baud_rate;

		r = ch341_set_baudrate_lcr(port->serial->dev, priv,
					   priv->baud_rate, lcr);
		अगर (r < 0 && old_termios) अणु
			priv->baud_rate = tty_termios_baud_rate(old_termios);
			tty_termios_copy_hw(&tty->termios, old_termios);
		पूर्ण अन्यथा अगर (r == 0) अणु
			priv->lcr = lcr;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);
	अगर (C_BAUD(tty) == B0)
		priv->mcr &= ~(CH341_BIT_DTR | CH341_BIT_RTS);
	अन्यथा अगर (old_termios && (old_termios->c_cflag & CBAUD) == B0)
		priv->mcr |= (CH341_BIT_DTR | CH341_BIT_RTS);
	spin_unlock_irqrestore(&priv->lock, flags);

	ch341_set_handshake(port->serial->dev, priv->mcr);
पूर्ण

/*
 * A subset of all CH34x devices करोn't support a real अवरोध condition and
 * पढ़ोing CH341_REG_BREAK fails (see also ch341_detect_quirks). This function
 * simulates a अवरोध condition by lowering the baud rate to the minimum
 * supported by the hardware upon enabling the अवरोध condition and sending
 * a NUL byte.
 *
 * Incoming data is corrupted जबतक the अवरोध condition is being simulated.
 *
 * Normally the duration of the अवरोध condition can be controlled inभागidually
 * by userspace using TIOCSBRK and TIOCCBRK or by passing an argument to
 * TCSBRKP. Due to how the simulation is implemented the duration can't be
 * controlled. The duration is always about (1s / 46bd * 9bit) = 196ms.
 */
अटल व्योम ch341_simulate_अवरोध(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा ch341_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ now, delay;
	पूर्णांक r;

	अगर (अवरोध_state != 0) अणु
		dev_dbg(&port->dev, "enter break state requested\n");

		r = ch341_set_baudrate_lcr(port->serial->dev, priv,
				CH341_MIN_BPS,
				CH341_LCR_ENABLE_RX | CH341_LCR_ENABLE_TX | CH341_LCR_CS8);
		अगर (r < 0) अणु
			dev_err(&port->dev,
				"failed to change baud rate to %u: %d\n",
				CH341_MIN_BPS, r);
			जाओ restore;
		पूर्ण

		r = tty_put_अक्षर(tty, '\0');
		अगर (r < 0) अणु
			dev_err(&port->dev,
				"failed to write NUL byte for simulated break condition: %d\n",
				r);
			जाओ restore;
		पूर्ण

		/*
		 * Compute expected transmission duration including safety
		 * margin. The original baud rate is only restored after the
		 * computed poपूर्णांक in समय.
		 *
		 * 11 bits = 1 start, 8 data, 1 stop, 1 margin
		 */
		priv->अवरोध_end = jअगरfies + (11 * HZ / CH341_MIN_BPS);

		वापस;
	पूर्ण

	dev_dbg(&port->dev, "leave break state requested\n");

	now = jअगरfies;

	अगर (समय_beक्रमe(now, priv->अवरोध_end)) अणु
		/* Wait until NUL byte is written */
		delay = priv->अवरोध_end - now;
		dev_dbg(&port->dev,
			"wait %d ms while transmitting NUL byte at %u baud\n",
			jअगरfies_to_msecs(delay), CH341_MIN_BPS);
		schedule_समयout_पूर्णांकerruptible(delay);
	पूर्ण

restore:
	/* Restore original baud rate */
	r = ch341_set_baudrate_lcr(port->serial->dev, priv, priv->baud_rate,
				   priv->lcr);
	अगर (r < 0)
		dev_err(&port->dev,
			"restoring original baud rate of %u failed: %d\n",
			priv->baud_rate, r);
पूर्ण

अटल व्योम ch341_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	स्थिर uपूर्णांक16_t ch341_अवरोध_reg =
			((uपूर्णांक16_t) CH341_REG_LCR << 8) | CH341_REG_BREAK;
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा ch341_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक r;
	uपूर्णांक16_t reg_contents;
	uपूर्णांक8_t *अवरोध_reg;

	अगर (priv->quirks & CH341_QUIRK_SIMULATE_BREAK) अणु
		ch341_simulate_अवरोध(tty, अवरोध_state);
		वापस;
	पूर्ण

	अवरोध_reg = kदो_स्मृति(2, GFP_KERNEL);
	अगर (!अवरोध_reg)
		वापस;

	r = ch341_control_in(port->serial->dev, CH341_REQ_READ_REG,
			ch341_अवरोध_reg, 0, अवरोध_reg, 2);
	अगर (r < 0) अणु
		dev_err(&port->dev, "%s - USB control read error (%d)\n",
				__func__, r);
		जाओ out;
	पूर्ण
	dev_dbg(&port->dev, "%s - initial ch341 break register contents - reg1: %x, reg2: %x\n",
		__func__, अवरोध_reg[0], अवरोध_reg[1]);
	अगर (अवरोध_state != 0) अणु
		dev_dbg(&port->dev, "%s - Enter break state requested\n", __func__);
		अवरोध_reg[0] &= ~CH341_NBREAK_BITS;
		अवरोध_reg[1] &= ~CH341_LCR_ENABLE_TX;
	पूर्ण अन्यथा अणु
		dev_dbg(&port->dev, "%s - Leave break state requested\n", __func__);
		अवरोध_reg[0] |= CH341_NBREAK_BITS;
		अवरोध_reg[1] |= CH341_LCR_ENABLE_TX;
	पूर्ण
	dev_dbg(&port->dev, "%s - New ch341 break register contents - reg1: %x, reg2: %x\n",
		__func__, अवरोध_reg[0], अवरोध_reg[1]);
	reg_contents = get_unaligned_le16(अवरोध_reg);
	r = ch341_control_out(port->serial->dev, CH341_REQ_WRITE_REG,
			ch341_अवरोध_reg, reg_contents);
	अगर (r < 0)
		dev_err(&port->dev, "%s - USB control write error (%d)\n",
				__func__, r);
out:
	kमुक्त(अवरोध_reg);
पूर्ण

अटल पूर्णांक ch341_tiocmset(काष्ठा tty_काष्ठा *tty,
			  अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा ch341_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	u8 control;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (set & TIOCM_RTS)
		priv->mcr |= CH341_BIT_RTS;
	अगर (set & TIOCM_DTR)
		priv->mcr |= CH341_BIT_DTR;
	अगर (clear & TIOCM_RTS)
		priv->mcr &= ~CH341_BIT_RTS;
	अगर (clear & TIOCM_DTR)
		priv->mcr &= ~CH341_BIT_DTR;
	control = priv->mcr;
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस ch341_set_handshake(port->serial->dev, control);
पूर्ण

अटल व्योम ch341_update_status(काष्ठा usb_serial_port *port,
					अचिन्हित अक्षर *data, माप_प्रकार len)
अणु
	काष्ठा ch341_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा tty_काष्ठा *tty;
	अचिन्हित दीर्घ flags;
	u8 status;
	u8 delta;

	अगर (len < 4)
		वापस;

	status = ~data[2] & CH341_BITS_MODEM_STAT;

	spin_lock_irqsave(&priv->lock, flags);
	delta = status ^ priv->msr;
	priv->msr = status;
	spin_unlock_irqrestore(&priv->lock, flags);

	अगर (data[1] & CH341_MULT_STAT)
		dev_dbg(&port->dev, "%s - multiple status change\n", __func__);

	अगर (!delta)
		वापस;

	अगर (delta & CH341_BIT_CTS)
		port->icount.cts++;
	अगर (delta & CH341_BIT_DSR)
		port->icount.dsr++;
	अगर (delta & CH341_BIT_RI)
		port->icount.rng++;
	अगर (delta & CH341_BIT_DCD) अणु
		port->icount.dcd++;
		tty = tty_port_tty_get(&port->port);
		अगर (tty) अणु
			usb_serial_handle_dcd_change(port, tty,
						status & CH341_BIT_DCD);
			tty_kref_put(tty);
		पूर्ण
	पूर्ण

	wake_up_पूर्णांकerruptible(&port->port.delta_msr_रुको);
पूर्ण

अटल व्योम ch341_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	अचिन्हित पूर्णांक len = urb->actual_length;
	पूर्णांक status;

	चयन (urb->status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&urb->dev->dev, "%s - urb shutting down: %d\n",
			__func__, urb->status);
		वापस;
	शेष:
		dev_dbg(&urb->dev->dev, "%s - nonzero urb status: %d\n",
			__func__, urb->status);
		जाओ निकास;
	पूर्ण

	usb_serial_debug_data(&port->dev, __func__, len, data);
	ch341_update_status(port, data, len);
निकास:
	status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (status) अणु
		dev_err(&urb->dev->dev, "%s - usb_submit_urb failed: %d\n",
			__func__, status);
	पूर्ण
पूर्ण

अटल पूर्णांक ch341_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा ch341_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	u8 mcr;
	u8 status;
	अचिन्हित पूर्णांक result;

	spin_lock_irqsave(&priv->lock, flags);
	mcr = priv->mcr;
	status = priv->msr;
	spin_unlock_irqrestore(&priv->lock, flags);

	result = ((mcr & CH341_BIT_DTR)		? TIOCM_DTR : 0)
		  | ((mcr & CH341_BIT_RTS)	? TIOCM_RTS : 0)
		  | ((status & CH341_BIT_CTS)	? TIOCM_CTS : 0)
		  | ((status & CH341_BIT_DSR)	? TIOCM_DSR : 0)
		  | ((status & CH341_BIT_RI)	? TIOCM_RI  : 0)
		  | ((status & CH341_BIT_DCD)	? TIOCM_CD  : 0);

	dev_dbg(&port->dev, "%s - result = %x\n", __func__, result);

	वापस result;
पूर्ण

अटल पूर्णांक ch341_reset_resume(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_serial_port *port = serial->port[0];
	काष्ठा ch341_निजी *priv;
	पूर्णांक ret;

	priv = usb_get_serial_port_data(port);
	अगर (!priv)
		वापस 0;

	/* reconfigure ch341 serial port after bus-reset */
	ch341_configure(serial->dev, priv);

	अगर (tty_port_initialized(&port->port)) अणु
		ret = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_NOIO);
		अगर (ret) अणु
			dev_err(&port->dev, "failed to submit interrupt urb: %d\n",
				ret);
			वापस ret;
		पूर्ण

		ret = ch341_get_status(port->serial->dev, priv);
		अगर (ret < 0) अणु
			dev_err(&port->dev, "failed to read modem status: %d\n",
				ret);
		पूर्ण
	पूर्ण

	वापस usb_serial_generic_resume(serial);
पूर्ण

अटल काष्ठा usb_serial_driver ch341_device = अणु
	.driver = अणु
		.owner	= THIS_MODULE,
		.name	= "ch341-uart",
	पूर्ण,
	.id_table          = id_table,
	.num_ports         = 1,
	.खोलो              = ch341_खोलो,
	.dtr_rts	   = ch341_dtr_rts,
	.carrier_उठाओd	   = ch341_carrier_उठाओd,
	.बंद             = ch341_बंद,
	.set_termios       = ch341_set_termios,
	.अवरोध_ctl         = ch341_अवरोध_ctl,
	.tiocmget          = ch341_tiocmget,
	.tiocmset          = ch341_tiocmset,
	.tiocmiरुको        = usb_serial_generic_tiocmiरुको,
	.पढ़ो_पूर्णांक_callback = ch341_पढ़ो_पूर्णांक_callback,
	.port_probe        = ch341_port_probe,
	.port_हटाओ       = ch341_port_हटाओ,
	.reset_resume      = ch341_reset_resume,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&ch341_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_LICENSE("GPL v2");
