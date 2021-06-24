<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ours Technology Inc. OTi-6858 USB to serial adapter driver.
 *
 * Copyleft  (C) 2007 Kees Lemmens (adapted क्रम kernel 2.6.20)
 * Copyright (C) 2006 Tomasz Michal Lukaszewski (FIXME: add e-mail)
 * Copyright (C) 2001-2004 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2003 IBM Corp.
 *
 * Many thanks to the authors of pl2303 driver: all functions in this file
 * are heavily based on pl2303 code, buffering code is a 1-to-1 copy.
 *
 * Warning! You use this driver on your own risk! The only official
 * description of this device I have is datasheet from manufacturer,
 * and it करोesn't contain almost any inक्रमmation needed to ग_लिखो a driver.
 * Almost all knowlegde used जबतक writing this driver was gathered by:
 *  - analyzing traffic between device and the M$ Winकरोws 2000 driver,
 *  - trying dअगरferent bit combinations and checking pin states
 *    with a volपंचांगeter,
 *  - receiving malक्रमmed frames and producing buffer overflows
 *    to learn how errors are reported,
 * So, THIS CODE CAN DESTROY OTi-6858 AND ANY OTHER DEVICES, THAT ARE
 * CONNECTED TO IT!
 *
 * See Documentation/usb/usb-serial.rst क्रम more inक्रमmation on using this
 * driver
 *
 * TODO:
 *  - implement correct flushing क्रम ioctls and oti6858_बंद()
 *  - check how errors (rx overflow, parity error, framing error) are reported
 *  - implement oti6858_अवरोध_ctl()
 *  - implement more ioctls
 *  - test/implement flow control
 *  - allow setting custom baud rates
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kfअगरo.h>
#समावेश "oti6858.h"

#घोषणा OTI6858_DESCRIPTION \
	"Ours Technology Inc. OTi-6858 USB to serial adapter driver"
#घोषणा OTI6858_AUTHOR "Tomasz Michal Lukaszewski <FIXME@FIXME>"

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(OTI6858_VENDOR_ID, OTI6858_PRODUCT_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table);

/* requests */
#घोषणा	OTI6858_REQ_GET_STATUS		(USB_सूची_IN | USB_TYPE_VENDOR | 0x00)
#घोषणा	OTI6858_REQ_T_GET_STATUS	0x01

#घोषणा	OTI6858_REQ_SET_LINE		(USB_सूची_OUT | USB_TYPE_VENDOR | 0x00)
#घोषणा	OTI6858_REQ_T_SET_LINE		0x00

#घोषणा	OTI6858_REQ_CHECK_TXBUFF	(USB_सूची_IN | USB_TYPE_VENDOR | 0x01)
#घोषणा	OTI6858_REQ_T_CHECK_TXBUFF	0x00

/* क्रमmat of the control packet */
काष्ठा oti6858_control_pkt अणु
	__le16	भागisor;	/* baud rate = 96000000 / (16 * भागisor), LE */
#घोषणा OTI6858_MAX_BAUD_RATE	3000000
	u8	frame_fmt;
#घोषणा FMT_STOP_BITS_MASK	0xc0
#घोषणा FMT_STOP_BITS_1		0x00
#घोषणा FMT_STOP_BITS_2		0x40	/* 1.5 stop bits अगर FMT_DATA_BITS_5 */
#घोषणा FMT_PARITY_MASK		0x38
#घोषणा FMT_PARITY_NONE		0x00
#घोषणा FMT_PARITY_ODD		0x08
#घोषणा FMT_PARITY_EVEN		0x18
#घोषणा FMT_PARITY_MARK		0x28
#घोषणा FMT_PARITY_SPACE	0x38
#घोषणा FMT_DATA_BITS_MASK	0x03
#घोषणा FMT_DATA_BITS_5		0x00
#घोषणा FMT_DATA_BITS_6		0x01
#घोषणा FMT_DATA_BITS_7		0x02
#घोषणा FMT_DATA_BITS_8		0x03
	u8	something;	/* always equals 0x43 */
	u8	control;	/* settings of flow control lines */
#घोषणा CONTROL_MASK		0x0c
#घोषणा CONTROL_DTR_HIGH	0x08
#घोषणा CONTROL_RTS_HIGH	0x04
	u8	tx_status;
#घोषणा	TX_BUFFER_EMPTIED	0x09
	u8	pin_state;
#घोषणा PIN_MASK		0x3f
#घोषणा PIN_MSR_MASK		0x1b
#घोषणा PIN_RTS			0x20	/* output pin */
#घोषणा PIN_CTS			0x10	/* input pin, active low */
#घोषणा PIN_DSR			0x08	/* input pin, active low */
#घोषणा PIN_DTR			0x04	/* output pin */
#घोषणा PIN_RI			0x02	/* input pin, active low */
#घोषणा PIN_DCD			0x01	/* input pin, active low */
	u8	rx_bytes_avail;		/* number of bytes in rx buffer */;
पूर्ण;

#घोषणा OTI6858_CTRL_PKT_SIZE	माप(काष्ठा oti6858_control_pkt)
#घोषणा OTI6858_CTRL_EQUALS_PENDING(a, priv) \
	(((a)->भागisor == (priv)->pending_setup.भागisor) \
	  && ((a)->control == (priv)->pending_setup.control) \
	  && ((a)->frame_fmt == (priv)->pending_setup.frame_fmt))

/* function prototypes */
अटल पूर्णांक oti6858_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port);
अटल व्योम oti6858_बंद(काष्ठा usb_serial_port *port);
अटल व्योम oti6858_set_termios(काष्ठा tty_काष्ठा *tty,
			काष्ठा usb_serial_port *port, काष्ठा ktermios *old);
अटल व्योम oti6858_init_termios(काष्ठा tty_काष्ठा *tty);
अटल व्योम oti6858_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb);
अटल व्योम oti6858_पढ़ो_bulk_callback(काष्ठा urb *urb);
अटल व्योम oti6858_ग_लिखो_bulk_callback(काष्ठा urb *urb);
अटल पूर्णांक oti6858_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
			स्थिर अचिन्हित अक्षर *buf, पूर्णांक count);
अटल पूर्णांक oti6858_ग_लिखो_room(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक oti6858_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक oti6858_tiocmget(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक oti6858_tiocmset(काष्ठा tty_काष्ठा *tty,
				अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);
अटल पूर्णांक oti6858_port_probe(काष्ठा usb_serial_port *port);
अटल व्योम oti6858_port_हटाओ(काष्ठा usb_serial_port *port);

/* device info */
अटल काष्ठा usb_serial_driver oti6858_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"oti6858",
	पूर्ण,
	.id_table =		id_table,
	.num_ports =		1,
	.num_bulk_in =		1,
	.num_bulk_out =		1,
	.num_पूर्णांकerrupt_in =	1,
	.खोलो =			oti6858_खोलो,
	.बंद =		oti6858_बंद,
	.ग_लिखो =		oti6858_ग_लिखो,
	.set_termios =		oti6858_set_termios,
	.init_termios = 	oti6858_init_termios,
	.tiocmget =		oti6858_tiocmget,
	.tiocmset =		oti6858_tiocmset,
	.tiocmiरुको =		usb_serial_generic_tiocmiरुको,
	.पढ़ो_bulk_callback =	oti6858_पढ़ो_bulk_callback,
	.पढ़ो_पूर्णांक_callback =	oti6858_पढ़ो_पूर्णांक_callback,
	.ग_लिखो_bulk_callback =	oti6858_ग_लिखो_bulk_callback,
	.ग_लिखो_room =		oti6858_ग_लिखो_room,
	.अक्षरs_in_buffer =	oti6858_अक्षरs_in_buffer,
	.port_probe =		oti6858_port_probe,
	.port_हटाओ =		oti6858_port_हटाओ,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&oti6858_device, शून्य
पूर्ण;

काष्ठा oti6858_निजी अणु
	spinlock_t lock;

	काष्ठा oti6858_control_pkt status;

	काष्ठा अणु
		u8 पढ़ो_urb_in_use;
		u8 ग_लिखो_urb_in_use;
	पूर्ण flags;
	काष्ठा delayed_work delayed_ग_लिखो_work;

	काष्ठा अणु
		__le16 भागisor;
		u8 frame_fmt;
		u8 control;
	पूर्ण pending_setup;
	u8 transient;
	u8 setup_करोne;
	काष्ठा delayed_work delayed_setup_work;

	काष्ठा usb_serial_port *port;   /* USB port with which associated */
पूर्ण;

अटल व्योम setup_line(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा oti6858_निजी *priv = container_of(work,
			काष्ठा oti6858_निजी, delayed_setup_work.work);
	काष्ठा usb_serial_port *port = priv->port;
	काष्ठा oti6858_control_pkt *new_setup;
	अचिन्हित दीर्घ flags;
	पूर्णांक result;

	new_setup = kदो_स्मृति(OTI6858_CTRL_PKT_SIZE, GFP_KERNEL);
	अगर (!new_setup) अणु
		/* we will try again */
		schedule_delayed_work(&priv->delayed_setup_work,
						msecs_to_jअगरfies(2));
		वापस;
	पूर्ण

	result = usb_control_msg(port->serial->dev,
				usb_rcvctrlpipe(port->serial->dev, 0),
				OTI6858_REQ_T_GET_STATUS,
				OTI6858_REQ_GET_STATUS,
				0, 0,
				new_setup, OTI6858_CTRL_PKT_SIZE,
				100);

	अगर (result != OTI6858_CTRL_PKT_SIZE) अणु
		dev_err(&port->dev, "%s(): error reading status\n", __func__);
		kमुक्त(new_setup);
		/* we will try again */
		schedule_delayed_work(&priv->delayed_setup_work,
							msecs_to_jअगरfies(2));
		वापस;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);
	अगर (!OTI6858_CTRL_EQUALS_PENDING(new_setup, priv)) अणु
		new_setup->भागisor = priv->pending_setup.भागisor;
		new_setup->control = priv->pending_setup.control;
		new_setup->frame_fmt = priv->pending_setup.frame_fmt;

		spin_unlock_irqrestore(&priv->lock, flags);
		result = usb_control_msg(port->serial->dev,
					usb_sndctrlpipe(port->serial->dev, 0),
					OTI6858_REQ_T_SET_LINE,
					OTI6858_REQ_SET_LINE,
					0, 0,
					new_setup, OTI6858_CTRL_PKT_SIZE,
					100);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		result = 0;
	पूर्ण
	kमुक्त(new_setup);

	spin_lock_irqsave(&priv->lock, flags);
	अगर (result != OTI6858_CTRL_PKT_SIZE)
		priv->transient = 0;
	priv->setup_करोne = 1;
	spin_unlock_irqrestore(&priv->lock, flags);

	dev_dbg(&port->dev, "%s(): submitting interrupt urb\n", __func__);
	result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
	अगर (result != 0) अणु
		dev_err(&port->dev, "%s(): usb_submit_urb() failed with error %d\n",
			__func__, result);
	पूर्ण
पूर्ण

अटल व्योम send_data(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा oti6858_निजी *priv = container_of(work,
			काष्ठा oti6858_निजी, delayed_ग_लिखो_work.work);
	काष्ठा usb_serial_port *port = priv->port;
	पूर्णांक count = 0, result;
	अचिन्हित दीर्घ flags;
	u8 *allow;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->flags.ग_लिखो_urb_in_use) अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		schedule_delayed_work(&priv->delayed_ग_लिखो_work,
						msecs_to_jअगरfies(2));
		वापस;
	पूर्ण
	priv->flags.ग_लिखो_urb_in_use = 1;
	spin_unlock_irqrestore(&priv->lock, flags);

	spin_lock_irqsave(&port->lock, flags);
	count = kfअगरo_len(&port->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&port->lock, flags);

	अगर (count > port->bulk_out_size)
		count = port->bulk_out_size;

	अगर (count != 0) अणु
		allow = kदो_स्मृति(1, GFP_KERNEL);
		अगर (!allow)
			वापस;

		result = usb_control_msg(port->serial->dev,
				usb_rcvctrlpipe(port->serial->dev, 0),
				OTI6858_REQ_T_CHECK_TXBUFF,
				OTI6858_REQ_CHECK_TXBUFF,
				count, 0, allow, 1, 100);
		अगर (result != 1 || *allow != 0)
			count = 0;
		kमुक्त(allow);
	पूर्ण

	अगर (count == 0) अणु
		priv->flags.ग_लिखो_urb_in_use = 0;

		dev_dbg(&port->dev, "%s(): submitting interrupt urb\n", __func__);
		result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_NOIO);
		अगर (result != 0) अणु
			dev_err(&port->dev, "%s(): usb_submit_urb() failed with error %d\n",
				__func__, result);
		पूर्ण
		वापस;
	पूर्ण

	count = kfअगरo_out_locked(&port->ग_लिखो_fअगरo,
					port->ग_लिखो_urb->transfer_buffer,
					count, &port->lock);
	port->ग_लिखो_urb->transfer_buffer_length = count;
	result = usb_submit_urb(port->ग_लिखो_urb, GFP_NOIO);
	अगर (result != 0) अणु
		dev_err_console(port, "%s(): usb_submit_urb() failed with error %d\n",
				__func__, result);
		priv->flags.ग_लिखो_urb_in_use = 0;
	पूर्ण

	usb_serial_port_softपूर्णांक(port);
पूर्ण

अटल पूर्णांक oti6858_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा oti6858_निजी *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	spin_lock_init(&priv->lock);
	priv->port = port;
	INIT_DELAYED_WORK(&priv->delayed_setup_work, setup_line);
	INIT_DELAYED_WORK(&priv->delayed_ग_लिखो_work, send_data);

	usb_set_serial_port_data(port, priv);

	port->port.drain_delay = 256;	/* FIXME: check the FIFO length */

	वापस 0;
पूर्ण

अटल व्योम oti6858_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा oti6858_निजी *priv;

	priv = usb_get_serial_port_data(port);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक oti6858_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
			स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	अगर (!count)
		वापस count;

	count = kfअगरo_in_locked(&port->ग_लिखो_fअगरo, buf, count, &port->lock);

	वापस count;
पूर्ण

अटल पूर्णांक oti6858_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	पूर्णांक room = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	room = kfअगरo_avail(&port->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&port->lock, flags);

	वापस room;
पूर्ण

अटल पूर्णांक oti6858_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	पूर्णांक अक्षरs = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	अक्षरs = kfअगरo_len(&port->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&port->lock, flags);

	वापस अक्षरs;
पूर्ण

अटल व्योम oti6858_init_termios(काष्ठा tty_काष्ठा *tty)
अणु
	tty_encode_baud_rate(tty, 38400, 38400);
पूर्ण

अटल व्योम oti6858_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा oti6858_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक cflag;
	u8 frame_fmt, control;
	__le16 भागisor;
	पूर्णांक br;

	cflag = tty->termios.c_cflag;

	spin_lock_irqsave(&priv->lock, flags);
	भागisor = priv->pending_setup.भागisor;
	frame_fmt = priv->pending_setup.frame_fmt;
	control = priv->pending_setup.control;
	spin_unlock_irqrestore(&priv->lock, flags);

	frame_fmt &= ~FMT_DATA_BITS_MASK;
	चयन (cflag & CSIZE) अणु
	हाल CS5:
		frame_fmt |= FMT_DATA_BITS_5;
		अवरोध;
	हाल CS6:
		frame_fmt |= FMT_DATA_BITS_6;
		अवरोध;
	हाल CS7:
		frame_fmt |= FMT_DATA_BITS_7;
		अवरोध;
	शेष:
	हाल CS8:
		frame_fmt |= FMT_DATA_BITS_8;
		अवरोध;
	पूर्ण

	/* manufacturer claims that this device can work with baud rates
	 * up to 3 Mbps; I've tested it only on 115200 bps, so I can't
	 * guarantee that any other baud rate will work (especially
	 * the higher ones)
	 */
	br = tty_get_baud_rate(tty);
	अगर (br == 0) अणु
		भागisor = 0;
	पूर्ण अन्यथा अणु
		पूर्णांक real_br;
		पूर्णांक new_भागisor;
		br = min(br, OTI6858_MAX_BAUD_RATE);

		new_भागisor = (96000000 + 8 * br) / (16 * br);
		real_br = 96000000 / (16 * new_भागisor);
		भागisor = cpu_to_le16(new_भागisor);
		tty_encode_baud_rate(tty, real_br, real_br);
	पूर्ण

	frame_fmt &= ~FMT_STOP_BITS_MASK;
	अगर ((cflag & CSTOPB) != 0)
		frame_fmt |= FMT_STOP_BITS_2;
	अन्यथा
		frame_fmt |= FMT_STOP_BITS_1;

	frame_fmt &= ~FMT_PARITY_MASK;
	अगर ((cflag & PARENB) != 0) अणु
		अगर ((cflag & PARODD) != 0)
			frame_fmt |= FMT_PARITY_ODD;
		अन्यथा
			frame_fmt |= FMT_PARITY_EVEN;
	पूर्ण अन्यथा अणु
		frame_fmt |= FMT_PARITY_NONE;
	पूर्ण

	control &= ~CONTROL_MASK;
	अगर ((cflag & CRTSCTS) != 0)
		control |= (CONTROL_DTR_HIGH | CONTROL_RTS_HIGH);

	/* change control lines अगर we are चयनing to or from B0 */
	/* FIXME:
	spin_lock_irqsave(&priv->lock, flags);
	control = priv->line_control;
	अगर ((cflag & CBAUD) == B0)
		priv->line_control &= ~(CONTROL_DTR | CONTROL_RTS);
	अन्यथा
		priv->line_control |= (CONTROL_DTR | CONTROL_RTS);
	अगर (control != priv->line_control) अणु
		control = priv->line_control;
		spin_unlock_irqrestore(&priv->lock, flags);
		set_control_lines(serial->dev, control);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&priv->lock, flags);
	पूर्ण
	*/

	spin_lock_irqsave(&priv->lock, flags);
	अगर (भागisor != priv->pending_setup.भागisor
			|| control != priv->pending_setup.control
			|| frame_fmt != priv->pending_setup.frame_fmt) अणु
		priv->pending_setup.भागisor = भागisor;
		priv->pending_setup.control = control;
		priv->pending_setup.frame_fmt = frame_fmt;
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल पूर्णांक oti6858_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा oti6858_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा oti6858_control_pkt *buf;
	अचिन्हित दीर्घ flags;
	पूर्णांक result;

	usb_clear_halt(serial->dev, port->ग_लिखो_urb->pipe);
	usb_clear_halt(serial->dev, port->पढ़ो_urb->pipe);

	buf = kदो_स्मृति(OTI6858_CTRL_PKT_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	result = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
				OTI6858_REQ_T_GET_STATUS,
				OTI6858_REQ_GET_STATUS,
				0, 0,
				buf, OTI6858_CTRL_PKT_SIZE,
				100);
	अगर (result != OTI6858_CTRL_PKT_SIZE) अणु
		/* assume शेष (after घातer-on reset) values */
		buf->भागisor = cpu_to_le16(0x009c);	/* 38400 bps */
		buf->frame_fmt = 0x03;	/* 8N1 */
		buf->something = 0x43;
		buf->control = 0x4c;	/* DTR, RTS */
		buf->tx_status = 0x00;
		buf->pin_state = 0x5b;	/* RTS, CTS, DSR, DTR, RI, DCD */
		buf->rx_bytes_avail = 0x00;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);
	स_नकल(&priv->status, buf, OTI6858_CTRL_PKT_SIZE);
	priv->pending_setup.भागisor = buf->भागisor;
	priv->pending_setup.frame_fmt = buf->frame_fmt;
	priv->pending_setup.control = buf->control;
	spin_unlock_irqrestore(&priv->lock, flags);
	kमुक्त(buf);

	dev_dbg(&port->dev, "%s(): submitting interrupt urb\n", __func__);
	result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
	अगर (result != 0) अणु
		dev_err(&port->dev, "%s(): usb_submit_urb() failed with error %d\n",
			__func__, result);
		oti6858_बंद(port);
		वापस result;
	पूर्ण

	/* setup termios */
	अगर (tty)
		oti6858_set_termios(tty, port, शून्य);

	वापस 0;
पूर्ण

अटल व्योम oti6858_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा oti6858_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	/* clear out any reमुख्यing data in the buffer */
	kfअगरo_reset_out(&port->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&port->lock, flags);

	dev_dbg(&port->dev, "%s(): after buf_clear()\n", __func__);

	/* cancel scheduled setup */
	cancel_delayed_work_sync(&priv->delayed_setup_work);
	cancel_delayed_work_sync(&priv->delayed_ग_लिखो_work);

	/* shutकरोwn our urbs */
	dev_dbg(&port->dev, "%s(): shutting down urbs\n", __func__);
	usb_समाप्त_urb(port->ग_लिखो_urb);
	usb_समाप्त_urb(port->पढ़ो_urb);
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
पूर्ण

अटल पूर्णांक oti6858_tiocmset(काष्ठा tty_काष्ठा *tty,
				अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा oti6858_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	u8 control;

	dev_dbg(&port->dev, "%s(set = 0x%08x, clear = 0x%08x)\n",
		__func__, set, clear);

	/* FIXME: check अगर this is correct (active high/low) */
	spin_lock_irqsave(&priv->lock, flags);
	control = priv->pending_setup.control;
	अगर ((set & TIOCM_RTS) != 0)
		control |= CONTROL_RTS_HIGH;
	अगर ((set & TIOCM_DTR) != 0)
		control |= CONTROL_DTR_HIGH;
	अगर ((clear & TIOCM_RTS) != 0)
		control &= ~CONTROL_RTS_HIGH;
	अगर ((clear & TIOCM_DTR) != 0)
		control &= ~CONTROL_DTR_HIGH;

	अगर (control != priv->pending_setup.control)
		priv->pending_setup.control = control;

	spin_unlock_irqrestore(&priv->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक oti6858_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा oti6858_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	अचिन्हित pin_state;
	अचिन्हित result = 0;

	spin_lock_irqsave(&priv->lock, flags);
	pin_state = priv->status.pin_state & PIN_MASK;
	spin_unlock_irqrestore(&priv->lock, flags);

	/* FIXME: check अगर this is correct (active high/low) */
	अगर ((pin_state & PIN_RTS) != 0)
		result |= TIOCM_RTS;
	अगर ((pin_state & PIN_CTS) != 0)
		result |= TIOCM_CTS;
	अगर ((pin_state & PIN_DSR) != 0)
		result |= TIOCM_DSR;
	अगर ((pin_state & PIN_DTR) != 0)
		result |= TIOCM_DTR;
	अगर ((pin_state & PIN_RI) != 0)
		result |= TIOCM_RI;
	अगर ((pin_state & PIN_DCD) != 0)
		result |= TIOCM_CD;

	dev_dbg(&port->dev, "%s() = 0x%08x\n", __func__, result);

	वापस result;
पूर्ण

अटल व्योम oti6858_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port =  urb->context;
	काष्ठा oti6858_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक transient = 0, can_recv = 0, resubmit = 1;
	पूर्णांक status = urb->status;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&urb->dev->dev, "%s(): urb shutting down with status: %d\n",
			__func__, status);
		वापस;
	शेष:
		dev_dbg(&urb->dev->dev, "%s(): nonzero urb status received: %d\n",
			__func__, status);
		अवरोध;
	पूर्ण

	अगर (status == 0 && urb->actual_length == OTI6858_CTRL_PKT_SIZE) अणु
		काष्ठा oti6858_control_pkt *xs = urb->transfer_buffer;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&priv->lock, flags);

		अगर (!priv->transient) अणु
			अगर (!OTI6858_CTRL_EQUALS_PENDING(xs, priv)) अणु
				अगर (xs->rx_bytes_avail == 0) अणु
					priv->transient = 4;
					priv->setup_करोne = 0;
					resubmit = 0;
					dev_dbg(&port->dev, "%s(): scheduling setup_line()\n", __func__);
					schedule_delayed_work(&priv->delayed_setup_work, 0);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (OTI6858_CTRL_EQUALS_PENDING(xs, priv)) अणु
				priv->transient = 0;
			पूर्ण अन्यथा अगर (!priv->setup_करोne) अणु
				resubmit = 0;
			पूर्ण अन्यथा अगर (--priv->transient == 0) अणु
				अगर (xs->rx_bytes_avail == 0) अणु
					priv->transient = 4;
					priv->setup_करोne = 0;
					resubmit = 0;
					dev_dbg(&port->dev, "%s(): scheduling setup_line()\n", __func__);
					schedule_delayed_work(&priv->delayed_setup_work, 0);
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (!priv->transient) अणु
			u8 delta = xs->pin_state ^ priv->status.pin_state;

			अगर (delta & PIN_MSR_MASK) अणु
				अगर (delta & PIN_CTS)
					port->icount.cts++;
				अगर (delta & PIN_DSR)
					port->icount.dsr++;
				अगर (delta & PIN_RI)
					port->icount.rng++;
				अगर (delta & PIN_DCD)
					port->icount.dcd++;

				wake_up_पूर्णांकerruptible(&port->port.delta_msr_रुको);
			पूर्ण

			स_नकल(&priv->status, xs, OTI6858_CTRL_PKT_SIZE);
		पूर्ण

		अगर (!priv->transient && xs->rx_bytes_avail != 0) अणु
			can_recv = xs->rx_bytes_avail;
			priv->flags.पढ़ो_urb_in_use = 1;
		पूर्ण

		transient = priv->transient;
		spin_unlock_irqrestore(&priv->lock, flags);
	पूर्ण

	अगर (can_recv) अणु
		पूर्णांक result;

		result = usb_submit_urb(port->पढ़ो_urb, GFP_ATOMIC);
		अगर (result != 0) अणु
			priv->flags.पढ़ो_urb_in_use = 0;
			dev_err(&port->dev, "%s(): usb_submit_urb() failed,"
					" error %d\n", __func__, result);
		पूर्ण अन्यथा अणु
			resubmit = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (!transient) अणु
		अचिन्हित दीर्घ flags;
		पूर्णांक count;

		spin_lock_irqsave(&port->lock, flags);
		count = kfअगरo_len(&port->ग_लिखो_fअगरo);
		spin_unlock_irqrestore(&port->lock, flags);

		spin_lock_irqsave(&priv->lock, flags);
		अगर (priv->flags.ग_लिखो_urb_in_use == 0 && count != 0) अणु
			schedule_delayed_work(&priv->delayed_ग_लिखो_work, 0);
			resubmit = 0;
		पूर्ण
		spin_unlock_irqrestore(&priv->lock, flags);
	पूर्ण

	अगर (resubmit) अणु
		पूर्णांक result;

/*		dev_dbg(&urb->dev->dev, "%s(): submitting interrupt urb\n", __func__); */
		result = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (result != 0) अणु
			dev_err(&urb->dev->dev,
					"%s(): usb_submit_urb() failed with"
					" error %d\n", __func__, result);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम oti6858_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port =  urb->context;
	काष्ठा oti6858_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	अचिन्हित दीर्घ flags;
	पूर्णांक status = urb->status;
	पूर्णांक result;

	spin_lock_irqsave(&priv->lock, flags);
	priv->flags.पढ़ो_urb_in_use = 0;
	spin_unlock_irqrestore(&priv->lock, flags);

	अगर (status != 0) अणु
		dev_dbg(&urb->dev->dev, "%s(): unable to handle the error, exiting\n", __func__);
		वापस;
	पूर्ण

	अगर (urb->actual_length > 0) अणु
		tty_insert_flip_string(&port->port, data, urb->actual_length);
		tty_flip_buffer_push(&port->port);
	पूर्ण

	/* schedule the पूर्णांकerrupt urb */
	result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_ATOMIC);
	अगर (result != 0 && result != -EPERM) अणु
		dev_err(&port->dev, "%s(): usb_submit_urb() failed,"
				" error %d\n", __func__, result);
	पूर्ण
पूर्ण

अटल व्योम oti6858_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port =  urb->context;
	काष्ठा oti6858_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक status = urb->status;
	पूर्णांक result;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&urb->dev->dev, "%s(): urb shutting down with status: %d\n", __func__, status);
		priv->flags.ग_लिखो_urb_in_use = 0;
		वापस;
	शेष:
		/* error in the urb, so we have to resubmit it */
		dev_dbg(&urb->dev->dev, "%s(): nonzero write bulk status received: %d\n", __func__, status);
		dev_dbg(&urb->dev->dev, "%s(): overflow in write\n", __func__);

		port->ग_लिखो_urb->transfer_buffer_length = 1;
		result = usb_submit_urb(port->ग_लिखो_urb, GFP_ATOMIC);
		अगर (result) अणु
			dev_err_console(port, "%s(): usb_submit_urb() failed,"
					" error %d\n", __func__, result);
		पूर्ण अन्यथा अणु
			वापस;
		पूर्ण
	पूर्ण

	priv->flags.ग_लिखो_urb_in_use = 0;

	/* schedule the पूर्णांकerrupt urb अगर we are still खोलो */
	dev_dbg(&port->dev, "%s(): submitting interrupt urb\n", __func__);
	result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_ATOMIC);
	अगर (result != 0) अणु
		dev_err(&port->dev, "%s(): failed submitting int urb,"
					" error %d\n", __func__, result);
	पूर्ण
पूर्ण

module_usb_serial_driver(serial_drivers, id_table);

MODULE_DESCRIPTION(OTI6858_DESCRIPTION);
MODULE_AUTHOR(OTI6858_AUTHOR);
MODULE_LICENSE("GPL v2");
