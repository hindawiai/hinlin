<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * usb-serial driver क्रम Quatech SSU-100
 *
 * based on ftdi_sio.c and the original serqt_usb.c from Quatech
 *
 */

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

#घोषणा QT_OPEN_CLOSE_CHANNEL       0xca
#घोषणा QT_SET_GET_DEVICE           0xc2
#घोषणा QT_SET_GET_REGISTER         0xc0
#घोषणा QT_GET_SET_PREBUF_TRIG_LVL  0xcc
#घोषणा QT_SET_ATF                  0xcd
#घोषणा QT_GET_SET_UART             0xc1
#घोषणा QT_TRANSFER_IN              0xc0
#घोषणा QT_HW_FLOW_CONTROL_MASK     0xc5
#घोषणा QT_SW_FLOW_CONTROL_MASK     0xc6

#घोषणा  SERIAL_MSR_MASK            0xf0

#घोषणा  SERIAL_CRTSCTS ((UART_MCR_RTS << 8) | UART_MSR_CTS)

#घोषणा  SERIAL_EVEN_PARITY         (UART_LCR_PARITY | UART_LCR_EPAR)

#घोषणा  MAX_BAUD_RATE              460800

#घोषणा ATC_DISABLED                0x00
#घोषणा DUPMODE_BITS        0xc0
#घोषणा RR_BITS             0x03
#घोषणा LOOPMODE_BITS       0x41
#घोषणा RS232_MODE          0x00
#घोषणा RTSCTS_TO_CONNECTOR 0x40
#घोषणा CLKS_X4             0x02
#घोषणा FULLPWRBIT          0x00000080
#घोषणा NEXT_BOARD_POWER_BIT        0x00000004

#घोषणा DRIVER_DESC "Quatech SSU-100 USB to Serial Driver"

#घोषणा	USB_VENDOR_ID_QUATECH	0x061d	/* Quatech VID */
#घोषणा QUATECH_SSU100	0xC020	/* SSU100 */

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणुUSB_DEVICE(USB_VENDOR_ID_QUATECH, QUATECH_SSU100)पूर्ण,
	अणुपूर्ण			/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

काष्ठा ssu100_port_निजी अणु
	spinlock_t status_lock;
	u8 shaकरोwLSR;
	u8 shaकरोwMSR;
पूर्ण;

अटल अंतरभूत पूर्णांक ssu100_control_msg(काष्ठा usb_device *dev,
				     u8 request, u16 data, u16 index)
अणु
	वापस usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			       request, 0x40, data, index,
			       शून्य, 0, 300);
पूर्ण

अटल अंतरभूत पूर्णांक ssu100_setdevice(काष्ठा usb_device *dev, u8 *data)
अणु
	u16 x = ((u16)(data[1] << 8) | (u16)(data[0]));

	वापस ssu100_control_msg(dev, QT_SET_GET_DEVICE, x, 0);
पूर्ण


अटल अंतरभूत पूर्णांक ssu100_getdevice(काष्ठा usb_device *dev, u8 *data)
अणु
	पूर्णांक ret;

	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			      QT_SET_GET_DEVICE, 0xc0, 0, 0,
			      data, 3, 300);
	अगर (ret < 3) अणु
		अगर (ret >= 0)
			ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ssu100_getरेजिस्टर(काष्ठा usb_device *dev,
				     अचिन्हित लघु uart,
				     अचिन्हित लघु reg,
				     u8 *data)
अणु
	पूर्णांक ret;

	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			      QT_SET_GET_REGISTER, 0xc0, reg,
			      uart, data, माप(*data), 300);
	अगर (ret < (पूर्णांक)माप(*data)) अणु
		अगर (ret >= 0)
			ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण


अटल अंतरभूत पूर्णांक ssu100_setरेजिस्टर(काष्ठा usb_device *dev,
				     अचिन्हित लघु uart,
				     अचिन्हित लघु reg,
				     u16 data)
अणु
	u16 value = (data << 8) | reg;

	वापस usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			       QT_SET_GET_REGISTER, 0x40, value, uart,
			       शून्य, 0, 300);

पूर्ण

#घोषणा set_mctrl(dev, set)		update_mctrl((dev), (set), 0)
#घोषणा clear_mctrl(dev, clear)	update_mctrl((dev), 0, (clear))

/* these करो not deal with device that have more than 1 port */
अटल अंतरभूत पूर्णांक update_mctrl(काष्ठा usb_device *dev, अचिन्हित पूर्णांक set,
			       अचिन्हित पूर्णांक clear)
अणु
	अचिन्हित urb_value;
	पूर्णांक result;

	अगर (((set | clear) & (TIOCM_DTR | TIOCM_RTS)) == 0) अणु
		dev_dbg(&dev->dev, "%s - DTR|RTS not being set|cleared\n", __func__);
		वापस 0;	/* no change */
	पूर्ण

	clear &= ~set;	/* 'set' takes precedence over 'clear' */
	urb_value = 0;
	अगर (set & TIOCM_DTR)
		urb_value |= UART_MCR_DTR;
	अगर (set & TIOCM_RTS)
		urb_value |= UART_MCR_RTS;

	result = ssu100_setरेजिस्टर(dev, 0, UART_MCR, urb_value);
	अगर (result < 0)
		dev_dbg(&dev->dev, "%s Error from MODEM_CTRL urb\n", __func__);

	वापस result;
पूर्ण

अटल पूर्णांक ssu100_initdevice(काष्ठा usb_device *dev)
अणु
	u8 *data;
	पूर्णांक result = 0;

	data = kzalloc(3, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	result = ssu100_getdevice(dev, data);
	अगर (result < 0) अणु
		dev_dbg(&dev->dev, "%s - get_device failed %i\n", __func__, result);
		जाओ out;
	पूर्ण

	data[1] &= ~FULLPWRBIT;

	result = ssu100_setdevice(dev, data);
	अगर (result < 0) अणु
		dev_dbg(&dev->dev, "%s - setdevice failed %i\n", __func__, result);
		जाओ out;
	पूर्ण

	result = ssu100_control_msg(dev, QT_GET_SET_PREBUF_TRIG_LVL, 128, 0);
	अगर (result < 0) अणु
		dev_dbg(&dev->dev, "%s - set prebuffer level failed %i\n", __func__, result);
		जाओ out;
	पूर्ण

	result = ssu100_control_msg(dev, QT_SET_ATF, ATC_DISABLED, 0);
	अगर (result < 0) अणु
		dev_dbg(&dev->dev, "%s - set ATFprebuffer level failed %i\n", __func__, result);
		जाओ out;
	पूर्ण

	result = ssu100_getdevice(dev, data);
	अगर (result < 0) अणु
		dev_dbg(&dev->dev, "%s - get_device failed %i\n", __func__, result);
		जाओ out;
	पूर्ण

	data[0] &= ~(RR_BITS | DUPMODE_BITS);
	data[0] |= CLKS_X4;
	data[1] &= ~(LOOPMODE_BITS);
	data[1] |= RS232_MODE;

	result = ssu100_setdevice(dev, data);
	अगर (result < 0) अणु
		dev_dbg(&dev->dev, "%s - setdevice failed %i\n", __func__, result);
		जाओ out;
	पूर्ण

out:	kमुक्त(data);
	वापस result;

पूर्ण


अटल व्योम ssu100_set_termios(काष्ठा tty_काष्ठा *tty,
			       काष्ठा usb_serial_port *port,
			       काष्ठा ktermios *old_termios)
अणु
	काष्ठा usb_device *dev = port->serial->dev;
	काष्ठा ktermios *termios = &tty->termios;
	u16 baud, भागisor, reमुख्यder;
	अचिन्हित पूर्णांक cflag = termios->c_cflag;
	u16 urb_value = 0; /* will hold the new flags */
	पूर्णांक result;

	अगर (cflag & PARENB) अणु
		अगर (cflag & PARODD)
			urb_value |= UART_LCR_PARITY;
		अन्यथा
			urb_value |= SERIAL_EVEN_PARITY;
	पूर्ण

	चयन (cflag & CSIZE) अणु
	हाल CS5:
		urb_value |= UART_LCR_WLEN5;
		अवरोध;
	हाल CS6:
		urb_value |= UART_LCR_WLEN6;
		अवरोध;
	हाल CS7:
		urb_value |= UART_LCR_WLEN7;
		अवरोध;
	शेष:
	हाल CS8:
		urb_value |= UART_LCR_WLEN8;
		अवरोध;
	पूर्ण

	baud = tty_get_baud_rate(tty);
	अगर (!baud)
		baud = 9600;

	dev_dbg(&port->dev, "%s - got baud = %d\n", __func__, baud);


	भागisor = MAX_BAUD_RATE / baud;
	reमुख्यder = MAX_BAUD_RATE % baud;
	अगर (((reमुख्यder * 2) >= baud) && (baud != 110))
		भागisor++;

	urb_value = urb_value << 8;

	result = ssu100_control_msg(dev, QT_GET_SET_UART, भागisor, urb_value);
	अगर (result < 0)
		dev_dbg(&port->dev, "%s - set uart failed\n", __func__);

	अगर (cflag & CRTSCTS)
		result = ssu100_control_msg(dev, QT_HW_FLOW_CONTROL_MASK,
					    SERIAL_CRTSCTS, 0);
	अन्यथा
		result = ssu100_control_msg(dev, QT_HW_FLOW_CONTROL_MASK,
					    0, 0);
	अगर (result < 0)
		dev_dbg(&port->dev, "%s - set HW flow control failed\n", __func__);

	अगर (I_IXOFF(tty) || I_IXON(tty)) अणु
		u16 x = ((u16)(START_CHAR(tty) << 8) | (u16)(STOP_CHAR(tty)));

		result = ssu100_control_msg(dev, QT_SW_FLOW_CONTROL_MASK,
					    x, 0);
	पूर्ण अन्यथा
		result = ssu100_control_msg(dev, QT_SW_FLOW_CONTROL_MASK,
					    0, 0);

	अगर (result < 0)
		dev_dbg(&port->dev, "%s - set SW flow control failed\n", __func__);

पूर्ण


अटल पूर्णांक ssu100_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_device *dev = port->serial->dev;
	काष्ठा ssu100_port_निजी *priv = usb_get_serial_port_data(port);
	u8 *data;
	पूर्णांक result;
	अचिन्हित दीर्घ flags;

	data = kzalloc(2, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	result = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
				 QT_OPEN_CLOSE_CHANNEL,
				 QT_TRANSFER_IN, 0x01,
				 0, data, 2, 300);
	अगर (result < 2) अणु
		dev_dbg(&port->dev, "%s - open failed %i\n", __func__, result);
		अगर (result >= 0)
			result = -EIO;
		kमुक्त(data);
		वापस result;
	पूर्ण

	spin_lock_irqsave(&priv->status_lock, flags);
	priv->shaकरोwLSR = data[0];
	priv->shaकरोwMSR = data[1];
	spin_unlock_irqrestore(&priv->status_lock, flags);

	kमुक्त(data);

/* set to 9600 */
	result = ssu100_control_msg(dev, QT_GET_SET_UART, 0x30, 0x0300);
	अगर (result < 0)
		dev_dbg(&port->dev, "%s - set uart failed\n", __func__);

	अगर (tty)
		ssu100_set_termios(tty, port, &tty->termios);

	वापस usb_serial_generic_खोलो(tty, port);
पूर्ण

अटल पूर्णांक ssu100_attach(काष्ठा usb_serial *serial)
अणु
	वापस ssu100_initdevice(serial->dev);
पूर्ण

अटल पूर्णांक ssu100_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा ssu100_port_निजी *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	spin_lock_init(&priv->status_lock);

	usb_set_serial_port_data(port, priv);

	वापस 0;
पूर्ण

अटल व्योम ssu100_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा ssu100_port_निजी *priv;

	priv = usb_get_serial_port_data(port);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक ssu100_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_device *dev = port->serial->dev;
	u8 *d;
	पूर्णांक r;

	d = kzalloc(2, GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;

	r = ssu100_getरेजिस्टर(dev, 0, UART_MCR, d);
	अगर (r < 0)
		जाओ mget_out;

	r = ssu100_getरेजिस्टर(dev, 0, UART_MSR, d+1);
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

अटल पूर्णांक ssu100_tiocmset(काष्ठा tty_काष्ठा *tty,
			   अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_device *dev = port->serial->dev;

	वापस update_mctrl(dev, set, clear);
पूर्ण

अटल व्योम ssu100_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	काष्ठा usb_device *dev = port->serial->dev;

	/* Disable flow control */
	अगर (!on) अणु
		अगर (ssu100_setरेजिस्टर(dev, 0, UART_MCR, 0) < 0)
			dev_err(&port->dev, "error from flowcontrol urb\n");
	पूर्ण
	/* drop RTS and DTR */
	अगर (on)
		set_mctrl(dev, TIOCM_DTR | TIOCM_RTS);
	अन्यथा
		clear_mctrl(dev, TIOCM_DTR | TIOCM_RTS);
पूर्ण

अटल व्योम ssu100_update_msr(काष्ठा usb_serial_port *port, u8 msr)
अणु
	काष्ठा ssu100_port_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->status_lock, flags);
	priv->shaकरोwMSR = msr;
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

अटल व्योम ssu100_update_lsr(काष्ठा usb_serial_port *port, u8 lsr,
			      अक्षर *tty_flag)
अणु
	काष्ठा ssu100_port_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->status_lock, flags);
	priv->shaकरोwLSR = lsr;
	spin_unlock_irqrestore(&priv->status_lock, flags);

	*tty_flag = TTY_NORMAL;
	अगर (lsr & UART_LSR_BRK_ERROR_BITS) अणु
		/* we always want to update icount, but we only want to
		 * update tty_flag क्रम one हाल */
		अगर (lsr & UART_LSR_BI) अणु
			port->icount.brk++;
			*tty_flag = TTY_BREAK;
			usb_serial_handle_अवरोध(port);
		पूर्ण
		अगर (lsr & UART_LSR_PE) अणु
			port->icount.parity++;
			अगर (*tty_flag == TTY_NORMAL)
				*tty_flag = TTY_PARITY;
		पूर्ण
		अगर (lsr & UART_LSR_FE) अणु
			port->icount.frame++;
			अगर (*tty_flag == TTY_NORMAL)
				*tty_flag = TTY_FRAME;
		पूर्ण
		अगर (lsr & UART_LSR_OE) अणु
			port->icount.overrun++;
			tty_insert_flip_अक्षर(&port->port, 0, TTY_OVERRUN);
		पूर्ण
	पूर्ण

पूर्ण

अटल व्योम ssu100_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	अक्षर *packet = urb->transfer_buffer;
	अक्षर flag = TTY_NORMAL;
	u32 len = urb->actual_length;
	पूर्णांक i;
	अक्षर *ch;

	अगर ((len >= 4) &&
	    (packet[0] == 0x1b) && (packet[1] == 0x1b) &&
	    ((packet[2] == 0x00) || (packet[2] == 0x01))) अणु
		अगर (packet[2] == 0x00)
			ssu100_update_lsr(port, packet[3], &flag);
		अगर (packet[2] == 0x01)
			ssu100_update_msr(port, packet[3]);

		len -= 4;
		ch = packet + 4;
	पूर्ण अन्यथा
		ch = packet;

	अगर (!len)
		वापस;	/* status only */

	अगर (port->sysrq) अणु
		क्रम (i = 0; i < len; i++, ch++) अणु
			अगर (!usb_serial_handle_sysrq_अक्षर(port, *ch))
				tty_insert_flip_अक्षर(&port->port, *ch, flag);
		पूर्ण
	पूर्ण अन्यथा अणु
		tty_insert_flip_string_fixed_flag(&port->port, ch, flag, len);
	पूर्ण

	tty_flip_buffer_push(&port->port);
पूर्ण

अटल काष्ठा usb_serial_driver ssu100_device = अणु
	.driver = अणु
		.owner = THIS_MODULE,
		.name = "ssu100",
	पूर्ण,
	.description	     = DRIVER_DESC,
	.id_table	     = id_table,
	.num_ports	     = 1,
	.खोलो		     = ssu100_खोलो,
	.attach              = ssu100_attach,
	.port_probe          = ssu100_port_probe,
	.port_हटाओ         = ssu100_port_हटाओ,
	.dtr_rts             = ssu100_dtr_rts,
	.process_पढ़ो_urb    = ssu100_process_पढ़ो_urb,
	.tiocmget            = ssu100_tiocmget,
	.tiocmset            = ssu100_tiocmset,
	.tiocmiरुको          = usb_serial_generic_tiocmiरुको,
	.get_icount	     = usb_serial_generic_get_icount,
	.set_termios         = ssu100_set_termios,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&ssu100_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");
