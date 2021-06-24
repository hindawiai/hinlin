<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas Electronics uPD78F0730 USB to serial converter driver
 *
 * Copyright (C) 2014,2016 Maksim Salau <maksim.salau@gmail.com>
 *
 * Protocol of the adaptor is described in the application note U19660EJ1V0AN00
 * NञPD78F0730 8-bit Single-Chip Microcontroller
 * USB-to-Serial Conversion Software
 * <https://www.renesas.com/en-eu/करोc/DocumentServer/026/U19660EJ1V0AN00.pdf>
 *
 * The adaptor functionality is limited to the following:
 * - data bits: 7 or 8
 * - stop bits: 1 or 2
 * - parity: even, odd or none
 * - flow control: none
 * - baud rates: 0, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 153600
 * - संकेतs: DTR, RTS and BREAK
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>

#घोषणा DRIVER_DESC "Renesas uPD78F0730 USB to serial converter driver"

#घोषणा DRIVER_AUTHOR "Maksim Salau <maksim.salau@gmail.com>"

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(0x0409, 0x0063) पूर्ण, /* V850ESJX3-STICK */
	अणु USB_DEVICE(0x045B, 0x0212) पूर्ण, /* YRPBRL78G13, YRPBRL78G14 */
	अणु USB_DEVICE(0x064B, 0x7825) पूर्ण, /* Analog Devices EVAL-ADXL362Z-DB */
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table);

/*
 * Each adaptor is associated with a निजी काष्ठाure, that holds the current
 * state of control संकेतs (DTR, RTS and BREAK).
 */
काष्ठा upd78f0730_port_निजी अणु
	काष्ठा mutex	lock;		/* mutex to protect line_संकेतs */
	u8		line_संकेतs;
पूर्ण;

/* Op-codes of control commands */
#घोषणा UPD78F0730_CMD_LINE_CONTROL	0x00
#घोषणा UPD78F0730_CMD_SET_DTR_RTS	0x01
#घोषणा UPD78F0730_CMD_SET_XON_XOFF_CHR	0x02
#घोषणा UPD78F0730_CMD_OPEN_CLOSE	0x03
#घोषणा UPD78F0730_CMD_SET_ERR_CHR	0x04

/* Data sizes in UPD78F0730_CMD_LINE_CONTROL command */
#घोषणा UPD78F0730_DATA_SIZE_7_BITS	0x00
#घोषणा UPD78F0730_DATA_SIZE_8_BITS	0x01
#घोषणा UPD78F0730_DATA_SIZE_MASK	0x01

/* Stop-bit modes in UPD78F0730_CMD_LINE_CONTROL command */
#घोषणा UPD78F0730_STOP_BIT_1_BIT	0x00
#घोषणा UPD78F0730_STOP_BIT_2_BIT	0x02
#घोषणा UPD78F0730_STOP_BIT_MASK	0x02

/* Parity modes in UPD78F0730_CMD_LINE_CONTROL command */
#घोषणा UPD78F0730_PARITY_NONE	0x00
#घोषणा UPD78F0730_PARITY_EVEN	0x04
#घोषणा UPD78F0730_PARITY_ODD	0x08
#घोषणा UPD78F0730_PARITY_MASK	0x0C

/* Flow control modes in UPD78F0730_CMD_LINE_CONTROL command */
#घोषणा UPD78F0730_FLOW_CONTROL_NONE	0x00
#घोषणा UPD78F0730_FLOW_CONTROL_HW	0x10
#घोषणा UPD78F0730_FLOW_CONTROL_SW	0x20
#घोषणा UPD78F0730_FLOW_CONTROL_MASK	0x30

/* Control संकेत bits in UPD78F0730_CMD_SET_DTR_RTS command */
#घोषणा UPD78F0730_RTS		0x01
#घोषणा UPD78F0730_DTR		0x02
#घोषणा UPD78F0730_BREAK	0x04

/* Port modes in UPD78F0730_CMD_OPEN_CLOSE command */
#घोषणा UPD78F0730_PORT_CLOSE	0x00
#घोषणा UPD78F0730_PORT_OPEN	0x01

/* Error अक्षरacter substitution modes in UPD78F0730_CMD_SET_ERR_CHR command */
#घोषणा UPD78F0730_ERR_CHR_DISABLED	0x00
#घोषणा UPD78F0730_ERR_CHR_ENABLED	0x01

/*
 * Declaration of command काष्ठाures
 */

/* UPD78F0730_CMD_LINE_CONTROL command */
काष्ठा upd78f0730_line_control अणु
	u8	opcode;
	__le32	baud_rate;
	u8	params;
पूर्ण __packed;

/* UPD78F0730_CMD_SET_DTR_RTS command */
काष्ठा upd78f0730_set_dtr_rts अणु
	u8 opcode;
	u8 params;
पूर्ण;

/* UPD78F0730_CMD_SET_XON_OFF_CHR command */
काष्ठा upd78f0730_set_xon_xoff_chr अणु
	u8 opcode;
	u8 xon;
	u8 xoff;
पूर्ण;

/* UPD78F0730_CMD_OPEN_CLOSE command */
काष्ठा upd78f0730_खोलो_बंद अणु
	u8 opcode;
	u8 state;
पूर्ण;

/* UPD78F0730_CMD_SET_ERR_CHR command */
काष्ठा upd78f0730_set_err_chr अणु
	u8 opcode;
	u8 state;
	u8 err_अक्षर;
पूर्ण;

अटल पूर्णांक upd78f0730_send_ctl(काष्ठा usb_serial_port *port,
			स्थिर व्योम *data, पूर्णांक size)
अणु
	काष्ठा usb_device *usbdev = port->serial->dev;
	व्योम *buf;
	पूर्णांक res;

	अगर (size <= 0 || !data)
		वापस -EINVAL;

	buf = kmemdup(data, size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	res = usb_control_msg(usbdev, usb_sndctrlpipe(usbdev, 0), 0x00,
			USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
			0x0000, 0x0000, buf, size, USB_CTRL_SET_TIMEOUT);

	kमुक्त(buf);

	अगर (res < 0) अणु
		काष्ठा device *dev = &port->dev;

		dev_err(dev, "failed to send control request %02x: %d\n",
			*(u8 *)data, res);

		वापस res;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक upd78f0730_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा upd78f0730_port_निजी *निजी;

	निजी = kzalloc(माप(*निजी), GFP_KERNEL);
	अगर (!निजी)
		वापस -ENOMEM;

	mutex_init(&निजी->lock);
	usb_set_serial_port_data(port, निजी);

	वापस 0;
पूर्ण

अटल व्योम upd78f0730_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा upd78f0730_port_निजी *निजी;

	निजी = usb_get_serial_port_data(port);
	mutex_destroy(&निजी->lock);
	kमुक्त(निजी);
पूर्ण

अटल पूर्णांक upd78f0730_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा upd78f0730_port_निजी *निजी;
	काष्ठा usb_serial_port *port = tty->driver_data;
	पूर्णांक संकेतs;
	पूर्णांक res;

	निजी = usb_get_serial_port_data(port);

	mutex_lock(&निजी->lock);
	संकेतs = निजी->line_संकेतs;
	mutex_unlock(&निजी->lock);

	res = ((संकेतs & UPD78F0730_DTR) ? TIOCM_DTR : 0) |
		((संकेतs & UPD78F0730_RTS) ? TIOCM_RTS : 0);

	dev_dbg(&port->dev, "%s - res = %x\n", __func__, res);

	वापस res;
पूर्ण

अटल पूर्णांक upd78f0730_tiocmset(काष्ठा tty_काष्ठा *tty,
			अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा upd78f0730_port_निजी *निजी;
	काष्ठा upd78f0730_set_dtr_rts request;
	काष्ठा device *dev = &port->dev;
	पूर्णांक res;

	निजी = usb_get_serial_port_data(port);

	mutex_lock(&निजी->lock);
	अगर (set & TIOCM_DTR) अणु
		निजी->line_संकेतs |= UPD78F0730_DTR;
		dev_dbg(dev, "%s - set DTR\n", __func__);
	पूर्ण
	अगर (set & TIOCM_RTS) अणु
		निजी->line_संकेतs |= UPD78F0730_RTS;
		dev_dbg(dev, "%s - set RTS\n", __func__);
	पूर्ण
	अगर (clear & TIOCM_DTR) अणु
		निजी->line_संकेतs &= ~UPD78F0730_DTR;
		dev_dbg(dev, "%s - clear DTR\n", __func__);
	पूर्ण
	अगर (clear & TIOCM_RTS) अणु
		निजी->line_संकेतs &= ~UPD78F0730_RTS;
		dev_dbg(dev, "%s - clear RTS\n", __func__);
	पूर्ण
	request.opcode = UPD78F0730_CMD_SET_DTR_RTS;
	request.params = निजी->line_संकेतs;

	res = upd78f0730_send_ctl(port, &request, माप(request));
	mutex_unlock(&निजी->lock);

	वापस res;
पूर्ण

अटल व्योम upd78f0730_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा upd78f0730_port_निजी *निजी;
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा upd78f0730_set_dtr_rts request;
	काष्ठा device *dev = &port->dev;

	निजी = usb_get_serial_port_data(port);

	mutex_lock(&निजी->lock);
	अगर (अवरोध_state) अणु
		निजी->line_संकेतs |= UPD78F0730_BREAK;
		dev_dbg(dev, "%s - set BREAK\n", __func__);
	पूर्ण अन्यथा अणु
		निजी->line_संकेतs &= ~UPD78F0730_BREAK;
		dev_dbg(dev, "%s - clear BREAK\n", __func__);
	पूर्ण
	request.opcode = UPD78F0730_CMD_SET_DTR_RTS;
	request.params = निजी->line_संकेतs;

	upd78f0730_send_ctl(port, &request, माप(request));
	mutex_unlock(&निजी->lock);
पूर्ण

अटल व्योम upd78f0730_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	काष्ठा tty_काष्ठा *tty = port->port.tty;
	अचिन्हित पूर्णांक set = 0;
	अचिन्हित पूर्णांक clear = 0;

	अगर (on)
		set = TIOCM_DTR | TIOCM_RTS;
	अन्यथा
		clear = TIOCM_DTR | TIOCM_RTS;

	upd78f0730_tiocmset(tty, set, clear);
पूर्ण

अटल speed_t upd78f0730_get_baud_rate(काष्ठा tty_काष्ठा *tty)
अणु
	स्थिर speed_t baud_rate = tty_get_baud_rate(tty);
	अटल स्थिर speed_t supported[] = अणु
		0, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 153600
	पूर्ण;
	पूर्णांक i;

	क्रम (i = ARRAY_SIZE(supported) - 1; i >= 0; i--) अणु
		अगर (baud_rate == supported[i])
			वापस baud_rate;
	पूर्ण

	/* If the baud rate is not supported, चयन to the शेष one */
	tty_encode_baud_rate(tty, 9600, 9600);

	वापस tty_get_baud_rate(tty);
पूर्ण

अटल व्योम upd78f0730_set_termios(काष्ठा tty_काष्ठा *tty,
				काष्ठा usb_serial_port *port,
				काष्ठा ktermios *old_termios)
अणु
	काष्ठा device *dev = &port->dev;
	काष्ठा upd78f0730_line_control request;
	speed_t baud_rate;

	अगर (old_termios && !tty_termios_hw_change(&tty->termios, old_termios))
		वापस;

	अगर (C_BAUD(tty) == B0)
		upd78f0730_dtr_rts(port, 0);
	अन्यथा अगर (old_termios && (old_termios->c_cflag & CBAUD) == B0)
		upd78f0730_dtr_rts(port, 1);

	baud_rate = upd78f0730_get_baud_rate(tty);
	request.opcode = UPD78F0730_CMD_LINE_CONTROL;
	request.baud_rate = cpu_to_le32(baud_rate);
	request.params = 0;
	dev_dbg(dev, "%s - baud rate = %d\n", __func__, baud_rate);

	चयन (C_CSIZE(tty)) अणु
	हाल CS7:
		request.params |= UPD78F0730_DATA_SIZE_7_BITS;
		dev_dbg(dev, "%s - 7 data bits\n", __func__);
		अवरोध;
	शेष:
		tty->termios.c_cflag &= ~CSIZE;
		tty->termios.c_cflag |= CS8;
		dev_warn(dev, "data size is not supported, using 8 bits\n");
		fallthrough;
	हाल CS8:
		request.params |= UPD78F0730_DATA_SIZE_8_BITS;
		dev_dbg(dev, "%s - 8 data bits\n", __func__);
		अवरोध;
	पूर्ण

	अगर (C_PARENB(tty)) अणु
		अगर (C_PARODD(tty)) अणु
			request.params |= UPD78F0730_PARITY_ODD;
			dev_dbg(dev, "%s - odd parity\n", __func__);
		पूर्ण अन्यथा अणु
			request.params |= UPD78F0730_PARITY_EVEN;
			dev_dbg(dev, "%s - even parity\n", __func__);
		पूर्ण

		अगर (C_CMSPAR(tty)) अणु
			tty->termios.c_cflag &= ~CMSPAR;
			dev_warn(dev, "MARK/SPACE parity is not supported\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		request.params |= UPD78F0730_PARITY_NONE;
		dev_dbg(dev, "%s - no parity\n", __func__);
	पूर्ण

	अगर (C_CSTOPB(tty)) अणु
		request.params |= UPD78F0730_STOP_BIT_2_BIT;
		dev_dbg(dev, "%s - 2 stop bits\n", __func__);
	पूर्ण अन्यथा अणु
		request.params |= UPD78F0730_STOP_BIT_1_BIT;
		dev_dbg(dev, "%s - 1 stop bit\n", __func__);
	पूर्ण

	अगर (C_CRTSCTS(tty)) अणु
		tty->termios.c_cflag &= ~CRTSCTS;
		dev_warn(dev, "RTSCTS flow control is not supported\n");
	पूर्ण
	अगर (I_IXOFF(tty) || I_IXON(tty)) अणु
		tty->termios.c_अगरlag &= ~(IXOFF | IXON);
		dev_warn(dev, "XON/XOFF flow control is not supported\n");
	पूर्ण
	request.params |= UPD78F0730_FLOW_CONTROL_NONE;
	dev_dbg(dev, "%s - no flow control\n", __func__);

	upd78f0730_send_ctl(port, &request, माप(request));
पूर्ण

अटल पूर्णांक upd78f0730_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	अटल स्थिर काष्ठा upd78f0730_खोलो_बंद request = अणु
		.opcode = UPD78F0730_CMD_OPEN_CLOSE,
		.state = UPD78F0730_PORT_OPEN
	पूर्ण;
	पूर्णांक res;

	res = upd78f0730_send_ctl(port, &request, माप(request));
	अगर (res)
		वापस res;

	अगर (tty)
		upd78f0730_set_termios(tty, port, शून्य);

	वापस usb_serial_generic_खोलो(tty, port);
पूर्ण

अटल व्योम upd78f0730_बंद(काष्ठा usb_serial_port *port)
अणु
	अटल स्थिर काष्ठा upd78f0730_खोलो_बंद request = अणु
		.opcode = UPD78F0730_CMD_OPEN_CLOSE,
		.state = UPD78F0730_PORT_CLOSE
	पूर्ण;

	usb_serial_generic_बंद(port);
	upd78f0730_send_ctl(port, &request, माप(request));
पूर्ण

अटल काष्ठा usb_serial_driver upd78f0730_device = अणु
	.driver	 = अणु
		.owner	= THIS_MODULE,
		.name	= "upd78f0730",
	पूर्ण,
	.id_table	= id_table,
	.num_ports	= 1,
	.port_probe	= upd78f0730_port_probe,
	.port_हटाओ	= upd78f0730_port_हटाओ,
	.खोलो		= upd78f0730_खोलो,
	.बंद		= upd78f0730_बंद,
	.set_termios	= upd78f0730_set_termios,
	.tiocmget	= upd78f0730_tiocmget,
	.tiocmset	= upd78f0730_tiocmset,
	.dtr_rts	= upd78f0730_dtr_rts,
	.अवरोध_ctl	= upd78f0730_अवरोध_ctl,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&upd78f0730_device,
	शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_LICENSE("GPL v2");
