<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * spcp8x5 USB to serial adaptor driver
 *
 * Copyright (C) 2010-2013 Johan Hovold (jhovold@gmail.com)
 * Copyright (C) 2006 Linxb (xubin.lin@worldplus.com.cn)
 * Copyright (C) 2006 S1 Corp.
 *
 * Original driver क्रम 2.6.10 pl2303 driver by
 *   Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Changes क्रम 2.6.20 by Harald Klein <hari@vt100.at>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>

#घोषणा DRIVER_DESC	"SPCP8x5 USB to serial adaptor driver"

#घोषणा SPCP825_QUIRK_NO_UART_STATUS	0x01
#घोषणा SPCP825_QUIRK_NO_WORK_MODE	0x02

#घोषणा SPCP8x5_007_VID		0x04FC
#घोषणा SPCP8x5_007_PID		0x0201
#घोषणा SPCP8x5_008_VID		0x04fc
#घोषणा SPCP8x5_008_PID		0x0235
#घोषणा SPCP8x5_PHILIPS_VID	0x0471
#घोषणा SPCP8x5_PHILIPS_PID	0x081e
#घोषणा SPCP8x5_INTERMATIC_VID	0x04FC
#घोषणा SPCP8x5_INTERMATIC_PID	0x0204
#घोषणा SPCP8x5_835_VID		0x04fc
#घोषणा SPCP8x5_835_PID		0x0231

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(SPCP8x5_PHILIPS_VID , SPCP8x5_PHILIPS_PID)पूर्ण,
	अणु USB_DEVICE(SPCP8x5_INTERMATIC_VID, SPCP8x5_INTERMATIC_PID)पूर्ण,
	अणु USB_DEVICE(SPCP8x5_835_VID, SPCP8x5_835_PID)पूर्ण,
	अणु USB_DEVICE(SPCP8x5_008_VID, SPCP8x5_008_PID)पूर्ण,
	अणु USB_DEVICE(SPCP8x5_007_VID, SPCP8x5_007_PID),
	  .driver_info = SPCP825_QUIRK_NO_UART_STATUS |
				SPCP825_QUIRK_NO_WORK_MODE पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

काष्ठा spcp8x5_usb_ctrl_arg अणु
	u8	type;
	u8	cmd;
	u8	cmd_type;
	u16	value;
	u16	index;
	u16	length;
पूर्ण;


/* spcp8x5 spec रेजिस्टर define */
#घोषणा MCR_CONTROL_LINE_RTS		0x02
#घोषणा MCR_CONTROL_LINE_DTR		0x01
#घोषणा MCR_DTR				0x01
#घोषणा MCR_RTS				0x02

#घोषणा MSR_STATUS_LINE_DCD		0x80
#घोषणा MSR_STATUS_LINE_RI		0x40
#घोषणा MSR_STATUS_LINE_DSR		0x20
#घोषणा MSR_STATUS_LINE_CTS		0x10

/* verकरोr command here , we should define myself */
#घोषणा SET_DEFAULT			0x40
#घोषणा SET_DEFAULT_TYPE		0x20

#घोषणा SET_UART_FORMAT			0x40
#घोषणा SET_UART_FORMAT_TYPE		0x21
#घोषणा SET_UART_FORMAT_SIZE_5		0x00
#घोषणा SET_UART_FORMAT_SIZE_6		0x01
#घोषणा SET_UART_FORMAT_SIZE_7		0x02
#घोषणा SET_UART_FORMAT_SIZE_8		0x03
#घोषणा SET_UART_FORMAT_STOP_1		0x00
#घोषणा SET_UART_FORMAT_STOP_2		0x04
#घोषणा SET_UART_FORMAT_PAR_NONE	0x00
#घोषणा SET_UART_FORMAT_PAR_ODD		0x10
#घोषणा SET_UART_FORMAT_PAR_EVEN	0x30
#घोषणा SET_UART_FORMAT_PAR_MASK	0xD0
#घोषणा SET_UART_FORMAT_PAR_SPACE	0x90

#घोषणा GET_UART_STATUS_TYPE		0xc0
#घोषणा GET_UART_STATUS			0x22
#घोषणा GET_UART_STATUS_MSR		0x06

#घोषणा SET_UART_STATUS			0x40
#घोषणा SET_UART_STATUS_TYPE		0x23
#घोषणा SET_UART_STATUS_MCR		0x0004
#घोषणा SET_UART_STATUS_MCR_DTR		0x01
#घोषणा SET_UART_STATUS_MCR_RTS		0x02
#घोषणा SET_UART_STATUS_MCR_LOOP	0x10

#घोषणा SET_WORKING_MODE		0x40
#घोषणा SET_WORKING_MODE_TYPE		0x24
#घोषणा SET_WORKING_MODE_U2C		0x00
#घोषणा SET_WORKING_MODE_RS485		0x01
#घोषणा SET_WORKING_MODE_PDMA		0x02
#घोषणा SET_WORKING_MODE_SPP		0x03

#घोषणा SET_FLOWCTL_CHAR		0x40
#घोषणा SET_FLOWCTL_CHAR_TYPE		0x25

#घोषणा GET_VERSION			0xc0
#घोषणा GET_VERSION_TYPE		0x26

#घोषणा SET_REGISTER			0x40
#घोषणा SET_REGISTER_TYPE		0x27

#घोषणा	GET_REGISTER			0xc0
#घोषणा GET_REGISTER_TYPE		0x28

#घोषणा SET_RAM				0x40
#घोषणा SET_RAM_TYPE			0x31

#घोषणा GET_RAM				0xc0
#घोषणा GET_RAM_TYPE			0x32

/* how come ??? */
#घोषणा UART_STATE			0x08
#घोषणा UART_STATE_TRANSIENT_MASK	0x75
#घोषणा UART_DCD			0x01
#घोषणा UART_DSR			0x02
#घोषणा UART_BREAK_ERROR		0x04
#घोषणा UART_RING			0x08
#घोषणा UART_FRAME_ERROR		0x10
#घोषणा UART_PARITY_ERROR		0x20
#घोषणा UART_OVERRUN_ERROR		0x40
#घोषणा UART_CTS			0x80

काष्ठा spcp8x5_निजी अणु
	अचिन्हित		quirks;
	spinlock_t		lock;
	u8			line_control;
पूर्ण;

अटल पूर्णांक spcp8x5_probe(काष्ठा usb_serial *serial,
						स्थिर काष्ठा usb_device_id *id)
अणु
	usb_set_serial_data(serial, (व्योम *)id);

	वापस 0;
पूर्ण

अटल पूर्णांक spcp8x5_port_probe(काष्ठा usb_serial_port *port)
अणु
	स्थिर काष्ठा usb_device_id *id = usb_get_serial_data(port->serial);
	काष्ठा spcp8x5_निजी *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	spin_lock_init(&priv->lock);
	priv->quirks = id->driver_info;

	usb_set_serial_port_data(port, priv);

	port->port.drain_delay = 256;

	वापस 0;
पूर्ण

अटल व्योम spcp8x5_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा spcp8x5_निजी *priv;

	priv = usb_get_serial_port_data(port);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक spcp8x5_set_ctrl_line(काष्ठा usb_serial_port *port, u8 mcr)
अणु
	काष्ठा spcp8x5_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा usb_device *dev = port->serial->dev;
	पूर्णांक retval;

	अगर (priv->quirks & SPCP825_QUIRK_NO_UART_STATUS)
		वापस -EPERM;

	retval = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
				 SET_UART_STATUS_TYPE, SET_UART_STATUS,
				 mcr, 0x04, शून्य, 0, 100);
	अगर (retval != 0) अणु
		dev_err(&port->dev, "failed to set control lines: %d\n",
								retval);
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक spcp8x5_get_msr(काष्ठा usb_serial_port *port, u8 *status)
अणु
	काष्ठा spcp8x5_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा usb_device *dev = port->serial->dev;
	u8 *buf;
	पूर्णांक ret;

	अगर (priv->quirks & SPCP825_QUIRK_NO_UART_STATUS)
		वापस -EPERM;

	buf = kzalloc(1, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			      GET_UART_STATUS, GET_UART_STATUS_TYPE,
			      0, GET_UART_STATUS_MSR, buf, 1, 100);
	अगर (ret < 1) अणु
		dev_err(&port->dev, "failed to get modem status: %d\n", ret);
		अगर (ret >= 0)
			ret = -EIO;
		जाओ out;
	पूर्ण

	dev_dbg(&port->dev, "0xc0:0x22:0:6  %d - 0x02%x\n", ret, *buf);
	*status = *buf;
	ret = 0;
out:
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल व्योम spcp8x5_set_work_mode(काष्ठा usb_serial_port *port, u16 value,
								 u16 index)
अणु
	काष्ठा spcp8x5_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा usb_device *dev = port->serial->dev;
	पूर्णांक ret;

	अगर (priv->quirks & SPCP825_QUIRK_NO_WORK_MODE)
		वापस;

	ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			      SET_WORKING_MODE_TYPE, SET_WORKING_MODE,
			      value, index, शून्य, 0, 100);
	dev_dbg(&port->dev, "value = %#x , index = %#x\n", value, index);
	अगर (ret < 0)
		dev_err(&port->dev, "failed to set work mode: %d\n", ret);
पूर्ण

अटल पूर्णांक spcp8x5_carrier_उठाओd(काष्ठा usb_serial_port *port)
अणु
	u8 msr;
	पूर्णांक ret;

	ret = spcp8x5_get_msr(port, &msr);
	अगर (ret || msr & MSR_STATUS_LINE_DCD)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम spcp8x5_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	काष्ठा spcp8x5_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	u8 control;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (on)
		priv->line_control = MCR_CONTROL_LINE_DTR
						| MCR_CONTROL_LINE_RTS;
	अन्यथा
		priv->line_control &= ~ (MCR_CONTROL_LINE_DTR
						| MCR_CONTROL_LINE_RTS);
	control = priv->line_control;
	spin_unlock_irqrestore(&priv->lock, flags);
	spcp8x5_set_ctrl_line(port, control);
पूर्ण

अटल व्योम spcp8x5_init_termios(काष्ठा tty_काष्ठा *tty)
अणु
	tty_encode_baud_rate(tty, 115200, 115200);
पूर्ण

अटल व्योम spcp8x5_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा spcp8x5_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक cflag = tty->termios.c_cflag;
	अचिन्हित लघु uartdata;
	अचिन्हित अक्षर buf[2] = अणु0, 0पूर्ण;
	पूर्णांक baud;
	पूर्णांक i;
	u8 control;

	/* check that they really want us to change something */
	अगर (old_termios && !tty_termios_hw_change(&tty->termios, old_termios))
		वापस;

	/* set DTR/RTS active */
	spin_lock_irqsave(&priv->lock, flags);
	control = priv->line_control;
	अगर (old_termios && (old_termios->c_cflag & CBAUD) == B0) अणु
		priv->line_control |= MCR_DTR;
		अगर (!(old_termios->c_cflag & CRTSCTS))
			priv->line_control |= MCR_RTS;
	पूर्ण
	अगर (control != priv->line_control) अणु
		control = priv->line_control;
		spin_unlock_irqrestore(&priv->lock, flags);
		spcp8x5_set_ctrl_line(port, control);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&priv->lock, flags);
	पूर्ण

	/* Set Baud Rate */
	baud = tty_get_baud_rate(tty);
	चयन (baud) अणु
	हाल 300:	buf[0] = 0x00;	अवरोध;
	हाल 600:	buf[0] = 0x01;	अवरोध;
	हाल 1200:	buf[0] = 0x02;	अवरोध;
	हाल 2400:	buf[0] = 0x03;	अवरोध;
	हाल 4800:	buf[0] = 0x04;	अवरोध;
	हाल 9600:	buf[0] = 0x05;	अवरोध;
	हाल 19200:	buf[0] = 0x07;	अवरोध;
	हाल 38400:	buf[0] = 0x09;	अवरोध;
	हाल 57600:	buf[0] = 0x0a;	अवरोध;
	हाल 115200:	buf[0] = 0x0b;	अवरोध;
	हाल 230400:	buf[0] = 0x0c;	अवरोध;
	हाल 460800:	buf[0] = 0x0d;	अवरोध;
	हाल 921600:	buf[0] = 0x0e;	अवरोध;
/*	हाल 1200000:	buf[0] = 0x0f;	अवरोध; */
/*	हाल 2400000:	buf[0] = 0x10;	अवरोध; */
	हाल 3000000:	buf[0] = 0x11;	अवरोध;
/*	हाल 6000000:	buf[0] = 0x12;	अवरोध; */
	हाल 0:
	हाल 1000000:
			buf[0] = 0x0b;	अवरोध;
	शेष:
		dev_err(&port->dev, "unsupported baudrate, using 9600\n");
	पूर्ण

	/* Set Data Length : 00:5bit, 01:6bit, 10:7bit, 11:8bit */
	चयन (cflag & CSIZE) अणु
	हाल CS5:
		buf[1] |= SET_UART_FORMAT_SIZE_5;
		अवरोध;
	हाल CS6:
		buf[1] |= SET_UART_FORMAT_SIZE_6;
		अवरोध;
	हाल CS7:
		buf[1] |= SET_UART_FORMAT_SIZE_7;
		अवरोध;
	शेष:
	हाल CS8:
		buf[1] |= SET_UART_FORMAT_SIZE_8;
		अवरोध;
	पूर्ण

	/* Set Stop bit2 : 0:1bit 1:2bit */
	buf[1] |= (cflag & CSTOPB) ? SET_UART_FORMAT_STOP_2 :
				     SET_UART_FORMAT_STOP_1;

	/* Set Parity bit3-4 01:Odd 11:Even */
	अगर (cflag & PARENB) अणु
		buf[1] |= (cflag & PARODD) ?
		SET_UART_FORMAT_PAR_ODD : SET_UART_FORMAT_PAR_EVEN ;
	पूर्ण अन्यथा अणु
		buf[1] |= SET_UART_FORMAT_PAR_NONE;
	पूर्ण
	uartdata = buf[0] | buf[1]<<8;

	i = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			    SET_UART_FORMAT_TYPE, SET_UART_FORMAT,
			    uartdata, 0, शून्य, 0, 100);
	अगर (i < 0)
		dev_err(&port->dev, "Set UART format %#x failed (error = %d)\n",
			uartdata, i);
	dev_dbg(&port->dev, "0x21:0x40:0:0  %d\n", i);

	अगर (cflag & CRTSCTS) अणु
		/* enable hardware flow control */
		spcp8x5_set_work_mode(port, 0x000a, SET_WORKING_MODE_U2C);
	पूर्ण
पूर्ण

अटल पूर्णांक spcp8x5_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा spcp8x5_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक ret;

	usb_clear_halt(serial->dev, port->ग_लिखो_urb->pipe);
	usb_clear_halt(serial->dev, port->पढ़ो_urb->pipe);

	ret = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			      0x09, 0x00,
			      0x01, 0x00, शून्य, 0x00, 100);
	अगर (ret)
		वापस ret;

	spcp8x5_set_ctrl_line(port, priv->line_control);

	अगर (tty)
		spcp8x5_set_termios(tty, port, शून्य);

	वापस usb_serial_generic_खोलो(tty, port);
पूर्ण

अटल पूर्णांक spcp8x5_tiocmset(काष्ठा tty_काष्ठा *tty,
			    अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा spcp8x5_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	u8 control;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (set & TIOCM_RTS)
		priv->line_control |= MCR_RTS;
	अगर (set & TIOCM_DTR)
		priv->line_control |= MCR_DTR;
	अगर (clear & TIOCM_RTS)
		priv->line_control &= ~MCR_RTS;
	अगर (clear & TIOCM_DTR)
		priv->line_control &= ~MCR_DTR;
	control = priv->line_control;
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस spcp8x5_set_ctrl_line(port, control);
पूर्ण

अटल पूर्णांक spcp8x5_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा spcp8x5_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक mcr;
	u8 status;
	अचिन्हित पूर्णांक result;

	result = spcp8x5_get_msr(port, &status);
	अगर (result)
		वापस result;

	spin_lock_irqsave(&priv->lock, flags);
	mcr = priv->line_control;
	spin_unlock_irqrestore(&priv->lock, flags);

	result = ((mcr & MCR_DTR)			? TIOCM_DTR : 0)
		  | ((mcr & MCR_RTS)			? TIOCM_RTS : 0)
		  | ((status & MSR_STATUS_LINE_CTS)	? TIOCM_CTS : 0)
		  | ((status & MSR_STATUS_LINE_DSR)	? TIOCM_DSR : 0)
		  | ((status & MSR_STATUS_LINE_RI)	? TIOCM_RI  : 0)
		  | ((status & MSR_STATUS_LINE_DCD)	? TIOCM_CD  : 0);

	वापस result;
पूर्ण

अटल काष्ठा usb_serial_driver spcp8x5_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"SPCP8x5",
	पूर्ण,
	.id_table		= id_table,
	.num_ports		= 1,
	.num_bulk_in		= 1,
	.num_bulk_out		= 1,
	.खोलो			= spcp8x5_खोलो,
	.dtr_rts		= spcp8x5_dtr_rts,
	.carrier_उठाओd		= spcp8x5_carrier_उठाओd,
	.set_termios		= spcp8x5_set_termios,
	.init_termios		= spcp8x5_init_termios,
	.tiocmget		= spcp8x5_tiocmget,
	.tiocmset		= spcp8x5_tiocmset,
	.probe			= spcp8x5_probe,
	.port_probe		= spcp8x5_port_probe,
	.port_हटाओ		= spcp8x5_port_हटाओ,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&spcp8x5_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
