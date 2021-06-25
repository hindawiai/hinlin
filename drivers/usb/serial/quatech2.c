<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * usb-serial driver क्रम Quatech USB 2 devices
 *
 * Copyright (C) 2012 Bill Pemberton (wfp5p@virginia.edu)
 *
 *  These devices all have only 1 bulk in and 1 bulk out that is shared
 *  क्रम all serial ports.
 *
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/serial.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/uaccess.h>

/* शेष urb समयout क्रम usb operations */
#घोषणा QT2_USB_TIMEOUT USB_CTRL_SET_TIMEOUT

#घोषणा QT_OPEN_CLOSE_CHANNEL       0xca
#घोषणा QT_SET_GET_DEVICE           0xc2
#घोषणा QT_SET_GET_REGISTER         0xc0
#घोषणा QT_GET_SET_PREBUF_TRIG_LVL  0xcc
#घोषणा QT_SET_ATF                  0xcd
#घोषणा QT_TRANSFER_IN              0xc0
#घोषणा QT_HW_FLOW_CONTROL_MASK     0xc5
#घोषणा QT_SW_FLOW_CONTROL_MASK     0xc6
#घोषणा QT2_BREAK_CONTROL	    0xc8
#घोषणा QT2_GET_SET_UART            0xc1
#घोषणा QT2_FLUSH_DEVICE	    0xc4
#घोषणा QT2_GET_SET_QMCR            0xe1
#घोषणा QT2_QMCR_RS232              0x40
#घोषणा QT2_QMCR_RS422              0x10

#घोषणा  SERIAL_CRTSCTS ((UART_MCR_RTS << 8) | UART_MSR_CTS)

#घोषणा  SERIAL_EVEN_PARITY         (UART_LCR_PARITY | UART_LCR_EPAR)

/* status bytes क्रम the device */
#घोषणा QT2_CONTROL_BYTE    0x1b
#घोषणा QT2_LINE_STATUS     0x00  /* following 1 byte is line status */
#घोषणा QT2_MODEM_STATUS    0x01  /* following 1 byte is modem status */
#घोषणा QT2_XMIT_HOLD       0x02  /* following 2 bytes are ?? */
#घोषणा QT2_CHANGE_PORT     0x03  /* following 1 byte is port to change to */
#घोषणा QT2_REC_FLUSH       0x04  /* no following info */
#घोषणा QT2_XMIT_FLUSH      0x05  /* no following info */
#घोषणा QT2_CONTROL_ESCAPE  0xff  /* pass through previous 2 control bytes */

#घोषणा  MAX_BAUD_RATE              921600
#घोषणा  DEFAULT_BAUD_RATE          9600

#घोषणा QT2_READ_BUFFER_SIZE    512  /* size of पढ़ो buffer */
#घोषणा QT2_WRITE_BUFFER_SIZE   512  /* size of ग_लिखो buffer */
#घोषणा QT2_WRITE_CONTROL_SIZE  5    /* control bytes used क्रम a ग_लिखो */

#घोषणा DRIVER_DESC "Quatech 2nd gen USB to Serial Driver"

#घोषणा	USB_VENDOR_ID_QUATECH	0x061d
#घोषणा QUATECH_SSU2_100	0xC120	/* RS232 single port */
#घोषणा QUATECH_DSU2_100	0xC140	/* RS232 dual port */
#घोषणा QUATECH_DSU2_400	0xC150	/* RS232/422/485 dual port */
#घोषणा QUATECH_QSU2_100	0xC160	/* RS232 four port */
#घोषणा QUATECH_QSU2_400	0xC170	/* RS232/422/485 four port */
#घोषणा QUATECH_ESU2_100	0xC1A0	/* RS232 eight port */
#घोषणा QUATECH_ESU2_400	0xC180	/* RS232/422/485 eight port */

काष्ठा qt2_device_detail अणु
	पूर्णांक product_id;
	पूर्णांक num_ports;
पूर्ण;

#घोषणा QT_DETAILS(prod, ports)	\
	.product_id = (prod),   \
	.num_ports = (ports)

अटल स्थिर काष्ठा qt2_device_detail qt2_device_details[] = अणु
	अणुQT_DETAILS(QUATECH_SSU2_100, 1)पूर्ण,
	अणुQT_DETAILS(QUATECH_DSU2_400, 2)पूर्ण,
	अणुQT_DETAILS(QUATECH_DSU2_100, 2)पूर्ण,
	अणुQT_DETAILS(QUATECH_QSU2_400, 4)पूर्ण,
	अणुQT_DETAILS(QUATECH_QSU2_100, 4)पूर्ण,
	अणुQT_DETAILS(QUATECH_ESU2_400, 8)पूर्ण,
	अणुQT_DETAILS(QUATECH_ESU2_100, 8)पूर्ण,
	अणुQT_DETAILS(0, 0)पूर्ण	/* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणुUSB_DEVICE(USB_VENDOR_ID_QUATECH, QUATECH_SSU2_100)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_QUATECH, QUATECH_DSU2_100)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_QUATECH, QUATECH_DSU2_400)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_QUATECH, QUATECH_QSU2_100)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_QUATECH, QUATECH_QSU2_400)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_QUATECH, QUATECH_ESU2_100)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_QUATECH, QUATECH_ESU2_400)पूर्ण,
	अणुपूर्ण			/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

काष्ठा qt2_serial_निजी अणु
	अचिन्हित अक्षर current_port;  /* current port क्रम incoming data */

	काष्ठा urb	*पढ़ो_urb;   /* shared among all ports */
	अक्षर		*पढ़ो_buffer;
पूर्ण;

काष्ठा qt2_port_निजी अणु
	u8   device_port;

	spinlock_t urb_lock;
	bool       urb_in_use;
	काष्ठा urb *ग_लिखो_urb;
	अक्षर       *ग_लिखो_buffer;

	spinlock_t  lock;
	u8          shaकरोwLSR;
	u8          shaकरोwMSR;

	काष्ठा usb_serial_port *port;
पूर्ण;

अटल व्योम qt2_update_lsr(काष्ठा usb_serial_port *port, अचिन्हित अक्षर *ch);
अटल व्योम qt2_update_msr(काष्ठा usb_serial_port *port, अचिन्हित अक्षर *ch);
अटल व्योम qt2_ग_लिखो_bulk_callback(काष्ठा urb *urb);
अटल व्योम qt2_पढ़ो_bulk_callback(काष्ठा urb *urb);

अटल व्योम qt2_release(काष्ठा usb_serial *serial)
अणु
	काष्ठा qt2_serial_निजी *serial_priv;

	serial_priv = usb_get_serial_data(serial);

	usb_समाप्त_urb(serial_priv->पढ़ो_urb);
	usb_मुक्त_urb(serial_priv->पढ़ो_urb);
	kमुक्त(serial_priv->पढ़ो_buffer);
	kमुक्त(serial_priv);
पूर्ण

अटल अंतरभूत पूर्णांक calc_baud_भागisor(पूर्णांक baudrate)
अणु
	पूर्णांक भागisor, rem;

	भागisor = MAX_BAUD_RATE / baudrate;
	rem = MAX_BAUD_RATE % baudrate;
	/* Round to nearest भागisor */
	अगर (((rem * 2) >= baudrate) && (baudrate != 110))
		भागisor++;

	वापस भागisor;
पूर्ण

अटल अंतरभूत पूर्णांक qt2_set_port_config(काष्ठा usb_device *dev,
				      अचिन्हित अक्षर port_number,
				      u16 baudrate, u16 lcr)
अणु
	पूर्णांक भागisor = calc_baud_भागisor(baudrate);
	u16 index = ((u16) (lcr << 8) | (u16) (port_number));

	वापस usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			       QT2_GET_SET_UART, 0x40,
			       भागisor, index, शून्य, 0, QT2_USB_TIMEOUT);
पूर्ण

अटल अंतरभूत पूर्णांक qt2_control_msg(काष्ठा usb_device *dev,
				  u8 request, u16 data, u16 index)
अणु
	वापस usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			       request, 0x40, data, index,
			       शून्य, 0, QT2_USB_TIMEOUT);
पूर्ण

अटल अंतरभूत पूर्णांक qt2_setdevice(काष्ठा usb_device *dev, u8 *data)
अणु
	u16 x = ((u16) (data[1] << 8) | (u16) (data[0]));

	वापस qt2_control_msg(dev, QT_SET_GET_DEVICE, x, 0);
पूर्ण


अटल अंतरभूत पूर्णांक qt2_getरेजिस्टर(काष्ठा usb_device *dev,
				  u8 uart,
				  u8 reg,
				  u8 *data)
अणु
	पूर्णांक ret;

	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			      QT_SET_GET_REGISTER, 0xc0, reg,
			      uart, data, माप(*data), QT2_USB_TIMEOUT);
	अगर (ret < (पूर्णांक)माप(*data)) अणु
		अगर (ret >= 0)
			ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक qt2_setरेजिस्टर(काष्ठा usb_device *dev,
				  u8 uart, u8 reg, u16 data)
अणु
	u16 value = (data << 8) | reg;

	वापस usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			       QT_SET_GET_REGISTER, 0x40, value, uart,
			       शून्य, 0, QT2_USB_TIMEOUT);
पूर्ण

अटल अंतरभूत पूर्णांक update_mctrl(काष्ठा qt2_port_निजी *port_priv,
			       अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = port_priv->port;
	काष्ठा usb_device *dev = port->serial->dev;
	अचिन्हित urb_value;
	पूर्णांक status;

	अगर (((set | clear) & (TIOCM_DTR | TIOCM_RTS)) == 0) अणु
		dev_dbg(&port->dev,
			"update_mctrl - DTR|RTS not being set|cleared\n");
		वापस 0;	/* no change */
	पूर्ण

	clear &= ~set;	/* 'set' takes precedence over 'clear' */
	urb_value = 0;
	अगर (set & TIOCM_DTR)
		urb_value |= UART_MCR_DTR;
	अगर (set & TIOCM_RTS)
		urb_value |= UART_MCR_RTS;

	status = qt2_setरेजिस्टर(dev, port_priv->device_port, UART_MCR,
				 urb_value);
	अगर (status < 0)
		dev_err(&port->dev,
			"update_mctrl - Error from MODEM_CTRL urb: %i\n",
			status);
	वापस status;
पूर्ण

अटल पूर्णांक qt2_calc_num_ports(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds)
अणु
	काष्ठा qt2_device_detail d;
	पूर्णांक i;

	क्रम (i = 0; d = qt2_device_details[i], d.product_id != 0; i++) अणु
		अगर (d.product_id == le16_to_cpu(serial->dev->descriptor.idProduct))
			वापस d.num_ports;
	पूर्ण

	/* we didn't recognize the device */
	dev_err(&serial->dev->dev,
		 "don't know the number of ports, assuming 1\n");

	वापस 1;
पूर्ण

अटल व्योम qt2_set_termios(काष्ठा tty_काष्ठा *tty,
			    काष्ठा usb_serial_port *port,
			    काष्ठा ktermios *old_termios)
अणु
	काष्ठा usb_device *dev = port->serial->dev;
	काष्ठा qt2_port_निजी *port_priv;
	काष्ठा ktermios *termios = &tty->termios;
	u16 baud;
	अचिन्हित पूर्णांक cflag = termios->c_cflag;
	u16 new_lcr = 0;
	पूर्णांक status;

	port_priv = usb_get_serial_port_data(port);

	अगर (cflag & PARENB) अणु
		अगर (cflag & PARODD)
			new_lcr |= UART_LCR_PARITY;
		अन्यथा
			new_lcr |= SERIAL_EVEN_PARITY;
	पूर्ण

	चयन (cflag & CSIZE) अणु
	हाल CS5:
		new_lcr |= UART_LCR_WLEN5;
		अवरोध;
	हाल CS6:
		new_lcr |= UART_LCR_WLEN6;
		अवरोध;
	हाल CS7:
		new_lcr |= UART_LCR_WLEN7;
		अवरोध;
	शेष:
	हाल CS8:
		new_lcr |= UART_LCR_WLEN8;
		अवरोध;
	पूर्ण

	baud = tty_get_baud_rate(tty);
	अगर (!baud)
		baud = 9600;

	status = qt2_set_port_config(dev, port_priv->device_port, baud,
				     new_lcr);
	अगर (status < 0)
		dev_err(&port->dev, "%s - qt2_set_port_config failed: %i\n",
			__func__, status);

	अगर (cflag & CRTSCTS)
		status = qt2_control_msg(dev, QT_HW_FLOW_CONTROL_MASK,
					 SERIAL_CRTSCTS,
					 port_priv->device_port);
	अन्यथा
		status = qt2_control_msg(dev, QT_HW_FLOW_CONTROL_MASK,
					 0, port_priv->device_port);
	अगर (status < 0)
		dev_err(&port->dev, "%s - set HW flow control failed: %i\n",
			__func__, status);

	अगर (I_IXOFF(tty) || I_IXON(tty)) अणु
		u16 x = ((u16) (START_CHAR(tty) << 8) | (u16) (STOP_CHAR(tty)));

		status = qt2_control_msg(dev, QT_SW_FLOW_CONTROL_MASK,
					 x, port_priv->device_port);
	पूर्ण अन्यथा
		status = qt2_control_msg(dev, QT_SW_FLOW_CONTROL_MASK,
					 0, port_priv->device_port);

	अगर (status < 0)
		dev_err(&port->dev, "%s - set SW flow control failed: %i\n",
			__func__, status);

पूर्ण

अटल पूर्णांक qt2_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial;
	काष्ठा qt2_port_निजी *port_priv;
	u8 *data;
	u16 device_port;
	पूर्णांक status;
	अचिन्हित दीर्घ flags;

	device_port = port->port_number;

	serial = port->serial;

	port_priv = usb_get_serial_port_data(port);

	/* set the port to RS232 mode */
	status = qt2_control_msg(serial->dev, QT2_GET_SET_QMCR,
				 QT2_QMCR_RS232, device_port);
	अगर (status < 0) अणु
		dev_err(&port->dev,
			"%s failed to set RS232 mode for port %i error %i\n",
			__func__, device_port, status);
		वापस status;
	पूर्ण

	data = kzalloc(2, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/* खोलो the port */
	status = usb_control_msg(serial->dev,
				 usb_rcvctrlpipe(serial->dev, 0),
				 QT_OPEN_CLOSE_CHANNEL,
				 0xc0, 0,
				 device_port, data, 2, QT2_USB_TIMEOUT);

	अगर (status < 2) अणु
		dev_err(&port->dev, "%s - open port failed %i\n", __func__,
			status);
		अगर (status >= 0)
			status = -EIO;
		kमुक्त(data);
		वापस status;
	पूर्ण

	spin_lock_irqsave(&port_priv->lock, flags);
	port_priv->shaकरोwLSR = data[0];
	port_priv->shaकरोwMSR = data[1];
	spin_unlock_irqrestore(&port_priv->lock, flags);

	kमुक्त(data);

	/* set to शेष speed and 8bit word size */
	status = qt2_set_port_config(serial->dev, device_port,
				     DEFAULT_BAUD_RATE, UART_LCR_WLEN8);
	अगर (status < 0) अणु
		dev_err(&port->dev, "%s - initial setup failed (%i)\n",
			__func__, device_port);
		वापस status;
	पूर्ण

	port_priv->device_port = (u8) device_port;

	अगर (tty)
		qt2_set_termios(tty, port, &tty->termios);

	वापस 0;

पूर्ण

अटल व्योम qt2_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial;
	काष्ठा qt2_port_निजी *port_priv;
	पूर्णांक i;

	serial = port->serial;
	port_priv = usb_get_serial_port_data(port);

	usb_समाप्त_urb(port_priv->ग_लिखो_urb);

	/* flush the port transmit buffer */
	i = usb_control_msg(serial->dev,
			    usb_sndctrlpipe(serial->dev, 0),
			    QT2_FLUSH_DEVICE, 0x40, 1,
			    port_priv->device_port, शून्य, 0, QT2_USB_TIMEOUT);

	अगर (i < 0)
		dev_err(&port->dev, "%s - transmit buffer flush failed: %i\n",
			__func__, i);

	/* flush the port receive buffer */
	i = usb_control_msg(serial->dev,
			    usb_sndctrlpipe(serial->dev, 0),
			    QT2_FLUSH_DEVICE, 0x40, 0,
			    port_priv->device_port, शून्य, 0, QT2_USB_TIMEOUT);

	अगर (i < 0)
		dev_err(&port->dev, "%s - receive buffer flush failed: %i\n",
			__func__, i);

	/* बंद the port */
	i = usb_control_msg(serial->dev,
			    usb_sndctrlpipe(serial->dev, 0),
			    QT_OPEN_CLOSE_CHANNEL,
			    0x40, 0,
			    port_priv->device_port, शून्य, 0, QT2_USB_TIMEOUT);

	अगर (i < 0)
		dev_err(&port->dev, "%s - close port failed %i\n",
			__func__, i);
पूर्ण

अटल व्योम qt2_disconnect(काष्ठा usb_serial *serial)
अणु
	काष्ठा qt2_serial_निजी *serial_priv = usb_get_serial_data(serial);

	usb_समाप्त_urb(serial_priv->पढ़ो_urb);
पूर्ण

अटल व्योम qt2_process_status(काष्ठा usb_serial_port *port, अचिन्हित अक्षर *ch)
अणु
	चयन (*ch) अणु
	हाल QT2_LINE_STATUS:
		qt2_update_lsr(port, ch + 1);
		अवरोध;
	हाल QT2_MODEM_STATUS:
		qt2_update_msr(port, ch + 1);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम qt2_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial *serial;
	काष्ठा qt2_serial_निजी *serial_priv;
	काष्ठा usb_serial_port *port;
	bool escapeflag;
	अचिन्हित अक्षर *ch;
	पूर्णांक i;
	अचिन्हित अक्षर newport;
	पूर्णांक len = urb->actual_length;

	अगर (!len)
		वापस;

	ch = urb->transfer_buffer;
	serial = urb->context;
	serial_priv = usb_get_serial_data(serial);
	port = serial->port[serial_priv->current_port];

	क्रम (i = 0; i < urb->actual_length; i++) अणु
		ch = (अचिन्हित अक्षर *)urb->transfer_buffer + i;
		अगर ((i <= (len - 3)) &&
		    (*ch == QT2_CONTROL_BYTE) &&
		    (*(ch + 1) == QT2_CONTROL_BYTE)) अणु
			escapeflag = false;
			चयन (*(ch + 2)) अणु
			हाल QT2_LINE_STATUS:
			हाल QT2_MODEM_STATUS:
				अगर (i > (len - 4)) अणु
					dev_warn(&port->dev,
						 "%s - status message too short\n",
						__func__);
					अवरोध;
				पूर्ण
				qt2_process_status(port, ch + 2);
				i += 3;
				escapeflag = true;
				अवरोध;
			हाल QT2_XMIT_HOLD:
				अगर (i > (len - 5)) अणु
					dev_warn(&port->dev,
						 "%s - xmit_empty message too short\n",
						 __func__);
					अवरोध;
				पूर्ण
				/* bytes_written = (ch[1] << 4) + ch[0]; */
				i += 4;
				escapeflag = true;
				अवरोध;
			हाल QT2_CHANGE_PORT:
				अगर (i > (len - 4)) अणु
					dev_warn(&port->dev,
						 "%s - change_port message too short\n",
						 __func__);
					अवरोध;
				पूर्ण
				tty_flip_buffer_push(&port->port);

				newport = *(ch + 3);

				अगर (newport > serial->num_ports) अणु
					dev_err(&port->dev,
						"%s - port change to invalid port: %i\n",
						__func__, newport);
					अवरोध;
				पूर्ण

				serial_priv->current_port = newport;
				port = serial->port[serial_priv->current_port];
				i += 3;
				escapeflag = true;
				अवरोध;
			हाल QT2_REC_FLUSH:
			हाल QT2_XMIT_FLUSH:
				i += 2;
				escapeflag = true;
				अवरोध;
			हाल QT2_CONTROL_ESCAPE:
				tty_insert_flip_string(&port->port, ch, 2);
				i += 2;
				escapeflag = true;
				अवरोध;
			शेष:
				dev_warn(&port->dev,
					 "%s - unsupported command %i\n",
					 __func__, *(ch + 2));
				अवरोध;
			पूर्ण
			अगर (escapeflag)
				जारी;
		पूर्ण

		tty_insert_flip_अक्षर(&port->port, *ch, TTY_NORMAL);
	पूर्ण

	tty_flip_buffer_push(&port->port);
पूर्ण

अटल व्योम qt2_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port;
	काष्ठा qt2_port_निजी *port_priv;
	अचिन्हित दीर्घ flags;

	port = urb->context;
	port_priv = usb_get_serial_port_data(port);

	spin_lock_irqsave(&port_priv->urb_lock, flags);

	port_priv->urb_in_use = false;
	usb_serial_port_softपूर्णांक(port);

	spin_unlock_irqrestore(&port_priv->urb_lock, flags);

पूर्ण

अटल व्योम qt2_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial *serial = urb->context;
	पूर्णांक status;

	अगर (urb->status) अणु
		dev_warn(&serial->dev->dev,
			 "%s - non-zero urb status: %i\n", __func__,
			 urb->status);
		वापस;
	पूर्ण

	qt2_process_पढ़ो_urb(urb);

	status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (status != 0)
		dev_err(&serial->dev->dev,
			"%s - resubmit read urb failed: %i\n",
			__func__, status);
पूर्ण

अटल पूर्णांक qt2_setup_urbs(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_serial_port *port0;
	काष्ठा qt2_serial_निजी *serial_priv;
	पूर्णांक status;

	port0 = serial->port[0];

	serial_priv = usb_get_serial_data(serial);
	serial_priv->पढ़ो_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!serial_priv->पढ़ो_urb)
		वापस -ENOMEM;

	usb_fill_bulk_urb(serial_priv->पढ़ो_urb, serial->dev,
			  usb_rcvbulkpipe(serial->dev,
					  port0->bulk_in_endpoपूर्णांकAddress),
			  serial_priv->पढ़ो_buffer,
			  QT2_READ_BUFFER_SIZE,
			  qt2_पढ़ो_bulk_callback, serial);

	status = usb_submit_urb(serial_priv->पढ़ो_urb, GFP_KERNEL);
	अगर (status != 0) अणु
		dev_err(&serial->dev->dev,
			"%s - submit read urb failed %i\n", __func__, status);
		usb_मुक्त_urb(serial_priv->पढ़ो_urb);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qt2_attach(काष्ठा usb_serial *serial)
अणु
	काष्ठा qt2_serial_निजी *serial_priv;
	पूर्णांक status;

	/* घातer on unit */
	status = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
				 0xc2, 0x40, 0x8000, 0, शून्य, 0,
				 QT2_USB_TIMEOUT);
	अगर (status < 0) अणु
		dev_err(&serial->dev->dev,
			"%s - failed to power on unit: %i\n", __func__, status);
		वापस status;
	पूर्ण

	serial_priv = kzalloc(माप(*serial_priv), GFP_KERNEL);
	अगर (!serial_priv)
		वापस -ENOMEM;

	serial_priv->पढ़ो_buffer = kदो_स्मृति(QT2_READ_BUFFER_SIZE, GFP_KERNEL);
	अगर (!serial_priv->पढ़ो_buffer) अणु
		status = -ENOMEM;
		जाओ err_buf;
	पूर्ण

	usb_set_serial_data(serial, serial_priv);

	status = qt2_setup_urbs(serial);
	अगर (status != 0)
		जाओ attach_failed;

	वापस 0;

attach_failed:
	kमुक्त(serial_priv->पढ़ो_buffer);
err_buf:
	kमुक्त(serial_priv);
	वापस status;
पूर्ण

अटल पूर्णांक qt2_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा qt2_port_निजी *port_priv;
	u8 bEndpoपूर्णांकAddress;

	port_priv = kzalloc(माप(*port_priv), GFP_KERNEL);
	अगर (!port_priv)
		वापस -ENOMEM;

	spin_lock_init(&port_priv->lock);
	spin_lock_init(&port_priv->urb_lock);
	port_priv->port = port;

	port_priv->ग_लिखो_buffer = kदो_स्मृति(QT2_WRITE_BUFFER_SIZE, GFP_KERNEL);
	अगर (!port_priv->ग_लिखो_buffer)
		जाओ err_buf;

	port_priv->ग_लिखो_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!port_priv->ग_लिखो_urb)
		जाओ err_urb;

	bEndpoपूर्णांकAddress = serial->port[0]->bulk_out_endpoपूर्णांकAddress;
	usb_fill_bulk_urb(port_priv->ग_लिखो_urb, serial->dev,
				usb_sndbulkpipe(serial->dev, bEndpoपूर्णांकAddress),
				port_priv->ग_लिखो_buffer,
				QT2_WRITE_BUFFER_SIZE,
				qt2_ग_लिखो_bulk_callback, port);

	usb_set_serial_port_data(port, port_priv);

	वापस 0;
err_urb:
	kमुक्त(port_priv->ग_लिखो_buffer);
err_buf:
	kमुक्त(port_priv);
	वापस -ENOMEM;
पूर्ण

अटल व्योम qt2_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा qt2_port_निजी *port_priv;

	port_priv = usb_get_serial_port_data(port);
	usb_मुक्त_urb(port_priv->ग_लिखो_urb);
	kमुक्त(port_priv->ग_लिखो_buffer);
	kमुक्त(port_priv);
पूर्ण

अटल पूर्णांक qt2_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_device *dev = port->serial->dev;
	काष्ठा qt2_port_निजी *port_priv = usb_get_serial_port_data(port);
	u8 *d;
	पूर्णांक r;

	d = kzalloc(2, GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;

	r = qt2_getरेजिस्टर(dev, port_priv->device_port, UART_MCR, d);
	अगर (r < 0)
		जाओ mget_out;

	r = qt2_getरेजिस्टर(dev, port_priv->device_port, UART_MSR, d + 1);
	अगर (r < 0)
		जाओ mget_out;

	r = (d[0] & UART_MCR_DTR ? TIOCM_DTR : 0) |
	    (d[0] & UART_MCR_RTS ? TIOCM_RTS : 0) |
	    (d[1] & UART_MSR_CTS ? TIOCM_CTS : 0) |
	    (d[1] & UART_MSR_DCD ? TIOCM_CAR : 0) |
	    (d[1] & UART_MSR_RI ? TIOCM_RI : 0) |
	    (d[1] & UART_MSR_DSR ? TIOCM_DSR : 0);

mget_out:
	kमुक्त(d);
	वापस r;
पूर्ण

अटल पूर्णांक qt2_tiocmset(काष्ठा tty_काष्ठा *tty,
			अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा qt2_port_निजी *port_priv;

	port_priv = usb_get_serial_port_data(tty->driver_data);
	वापस update_mctrl(port_priv, set, clear);
पूर्ण

अटल व्योम qt2_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा qt2_port_निजी *port_priv;
	पूर्णांक status;
	u16 val;

	port_priv = usb_get_serial_port_data(port);

	val = (अवरोध_state == -1) ? 1 : 0;

	status = qt2_control_msg(port->serial->dev, QT2_BREAK_CONTROL,
				 val, port_priv->device_port);
	अगर (status < 0)
		dev_warn(&port->dev,
			 "%s - failed to send control message: %i\n", __func__,
			 status);
पूर्ण



अटल व्योम qt2_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	काष्ठा usb_device *dev = port->serial->dev;
	काष्ठा qt2_port_निजी *port_priv = usb_get_serial_port_data(port);

	/* Disable flow control */
	अगर (!on) अणु
		अगर (qt2_setरेजिस्टर(dev, port_priv->device_port,
					   UART_MCR, 0) < 0)
			dev_warn(&port->dev, "error from flowcontrol urb\n");
	पूर्ण
	/* drop RTS and DTR */
	अगर (on)
		update_mctrl(port_priv, TIOCM_DTR | TIOCM_RTS, 0);
	अन्यथा
		update_mctrl(port_priv, 0, TIOCM_DTR | TIOCM_RTS);
पूर्ण

अटल व्योम qt2_update_msr(काष्ठा usb_serial_port *port, अचिन्हित अक्षर *ch)
अणु
	काष्ठा qt2_port_निजी *port_priv;
	u8 newMSR = (u8) *ch;
	अचिन्हित दीर्घ flags;

	/* May be called from qt2_process_पढ़ो_urb() क्रम an unbound port. */
	port_priv = usb_get_serial_port_data(port);
	अगर (!port_priv)
		वापस;

	spin_lock_irqsave(&port_priv->lock, flags);
	port_priv->shaकरोwMSR = newMSR;
	spin_unlock_irqrestore(&port_priv->lock, flags);

	अगर (newMSR & UART_MSR_ANY_DELTA) अणु
		/* update input line counters */
		अगर (newMSR & UART_MSR_DCTS)
			port->icount.cts++;
		अगर (newMSR & UART_MSR_DDSR)
			port->icount.dsr++;
		अगर (newMSR & UART_MSR_DDCD)
			port->icount.dcd++;
		अगर (newMSR & UART_MSR_TERI)
			port->icount.rng++;

		wake_up_पूर्णांकerruptible(&port->port.delta_msr_रुको);
	पूर्ण
पूर्ण

अटल व्योम qt2_update_lsr(काष्ठा usb_serial_port *port, अचिन्हित अक्षर *ch)
अणु
	काष्ठा qt2_port_निजी *port_priv;
	काष्ठा async_icount *icount;
	अचिन्हित दीर्घ flags;
	u8 newLSR = (u8) *ch;

	/* May be called from qt2_process_पढ़ो_urb() क्रम an unbound port. */
	port_priv = usb_get_serial_port_data(port);
	अगर (!port_priv)
		वापस;

	अगर (newLSR & UART_LSR_BI)
		newLSR &= (u8) (UART_LSR_OE | UART_LSR_BI);

	spin_lock_irqsave(&port_priv->lock, flags);
	port_priv->shaकरोwLSR = newLSR;
	spin_unlock_irqrestore(&port_priv->lock, flags);

	icount = &port->icount;

	अगर (newLSR & UART_LSR_BRK_ERROR_BITS) अणु

		अगर (newLSR & UART_LSR_BI)
			icount->brk++;

		अगर (newLSR & UART_LSR_OE)
			icount->overrun++;

		अगर (newLSR & UART_LSR_PE)
			icount->parity++;

		अगर (newLSR & UART_LSR_FE)
			icount->frame++;
	पूर्ण

पूर्ण

अटल पूर्णांक qt2_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा qt2_port_निजी *port_priv;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक r;

	port_priv = usb_get_serial_port_data(port);

	spin_lock_irqsave(&port_priv->urb_lock, flags);

	अगर (port_priv->urb_in_use)
		r = 0;
	अन्यथा
		r = QT2_WRITE_BUFFER_SIZE - QT2_WRITE_CONTROL_SIZE;

	spin_unlock_irqrestore(&port_priv->urb_lock, flags);

	वापस r;
पूर्ण

अटल पूर्णांक qt2_ग_लिखो(काष्ठा tty_काष्ठा *tty,
		     काष्ठा usb_serial_port *port,
		     स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा qt2_port_निजी *port_priv;
	काष्ठा urb *ग_लिखो_urb;
	अचिन्हित अक्षर *data;
	अचिन्हित दीर्घ flags;
	पूर्णांक status;
	पूर्णांक bytes_out = 0;

	port_priv = usb_get_serial_port_data(port);

	अगर (port_priv->ग_लिखो_urb == शून्य) अणु
		dev_err(&port->dev, "%s - no output urb\n", __func__);
		वापस 0;
	पूर्ण
	ग_लिखो_urb = port_priv->ग_लिखो_urb;

	count = min(count, QT2_WRITE_BUFFER_SIZE - QT2_WRITE_CONTROL_SIZE);

	data = ग_लिखो_urb->transfer_buffer;
	spin_lock_irqsave(&port_priv->urb_lock, flags);
	अगर (port_priv->urb_in_use) अणु
		dev_err(&port->dev, "qt2_write - urb is in use\n");
		जाओ ग_लिखो_out;
	पूर्ण

	*data++ = QT2_CONTROL_BYTE;
	*data++ = QT2_CONTROL_BYTE;
	*data++ = port_priv->device_port;
	put_unaligned_le16(count, data);
	data += 2;
	स_नकल(data, buf, count);

	ग_लिखो_urb->transfer_buffer_length = count + QT2_WRITE_CONTROL_SIZE;

	status = usb_submit_urb(ग_लिखो_urb, GFP_ATOMIC);
	अगर (status == 0) अणु
		port_priv->urb_in_use = true;
		bytes_out += count;
	पूर्ण

ग_लिखो_out:
	spin_unlock_irqrestore(&port_priv->urb_lock, flags);
	वापस bytes_out;
पूर्ण


अटल काष्ठा usb_serial_driver qt2_device = अणु
	.driver = अणु
		.owner = THIS_MODULE,
		.name = "quatech-serial",
	पूर्ण,
	.description	     = DRIVER_DESC,
	.id_table	     = id_table,
	.खोलो		     = qt2_खोलो,
	.बंद		     = qt2_बंद,
	.ग_लिखो               = qt2_ग_लिखो,
	.ग_लिखो_room          = qt2_ग_लिखो_room,
	.calc_num_ports      = qt2_calc_num_ports,
	.attach              = qt2_attach,
	.release             = qt2_release,
	.disconnect          = qt2_disconnect,
	.port_probe          = qt2_port_probe,
	.port_हटाओ         = qt2_port_हटाओ,
	.dtr_rts             = qt2_dtr_rts,
	.अवरोध_ctl           = qt2_अवरोध_ctl,
	.tiocmget            = qt2_tiocmget,
	.tiocmset            = qt2_tiocmset,
	.tiocmiरुको          = usb_serial_generic_tiocmiरुको,
	.get_icount	     = usb_serial_generic_get_icount,
	.set_termios         = qt2_set_termios,
पूर्ण;

अटल काष्ठा usb_serial_driver *स्थिर serial_drivers[] = अणु
	&qt2_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");
