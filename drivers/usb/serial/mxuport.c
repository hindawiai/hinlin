<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	mxuport.c - MOXA UPort series driver
 *
 *	Copyright (c) 2006 Moxa Technologies Co., Ltd.
 *	Copyright (c) 2013 Andrew Lunn <andrew@lunn.ch>
 *
 *	Supports the following Moxa USB to serial converters:
 *	 2 ports : UPort 1250, UPort 1250I
 *	 4 ports : UPort 1410, UPort 1450, UPort 1450I
 *	 8 ports : UPort 1610-8, UPort 1650-8
 *	16 ports : UPort 1610-16, UPort 1650-16
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <यंत्र/unaligned.h>

/* Definitions क्रम the venकरोr ID and device ID */
#घोषणा MX_USBSERIAL_VID	0x110A
#घोषणा MX_UPORT1250_PID	0x1250
#घोषणा MX_UPORT1251_PID	0x1251
#घोषणा MX_UPORT1410_PID	0x1410
#घोषणा MX_UPORT1450_PID	0x1450
#घोषणा MX_UPORT1451_PID	0x1451
#घोषणा MX_UPORT1618_PID	0x1618
#घोषणा MX_UPORT1658_PID	0x1658
#घोषणा MX_UPORT1613_PID	0x1613
#घोषणा MX_UPORT1653_PID	0x1653

/* Definitions क्रम USB info */
#घोषणा HEADER_SIZE		4
#घोषणा EVENT_LENGTH		8
#घोषणा DOWN_BLOCK_SIZE		64

/* Definitions क्रम firmware info */
#घोषणा VER_ADDR_1		0x20
#घोषणा VER_ADDR_2		0x24
#घोषणा VER_ADDR_3		0x28

/* Definitions क्रम USB venकरोr request */
#घोषणा RQ_VENDOR_NONE			0x00
#घोषणा RQ_VENDOR_SET_BAUD		0x01 /* Set baud rate */
#घोषणा RQ_VENDOR_SET_LINE		0x02 /* Set line status */
#घोषणा RQ_VENDOR_SET_CHARS		0x03 /* Set Xon/Xoff अक्षरs */
#घोषणा RQ_VENDOR_SET_RTS		0x04 /* Set RTS */
#घोषणा RQ_VENDOR_SET_DTR		0x05 /* Set DTR */
#घोषणा RQ_VENDOR_SET_XONXOFF		0x06 /* Set स्वतः Xon/Xoff */
#घोषणा RQ_VENDOR_SET_RX_HOST_EN	0x07 /* Set RX host enable */
#घोषणा RQ_VENDOR_SET_OPEN		0x08 /* Set खोलो/बंद port */
#घोषणा RQ_VENDOR_PURGE			0x09 /* Purge Rx/Tx buffer */
#घोषणा RQ_VENDOR_SET_MCR		0x0A /* Set MCR रेजिस्टर */
#घोषणा RQ_VENDOR_SET_BREAK		0x0B /* Set Break संकेत */

#घोषणा RQ_VENDOR_START_FW_DOWN		0x0C /* Start firmware करोwnload */
#घोषणा RQ_VENDOR_STOP_FW_DOWN		0x0D /* Stop firmware करोwnload */
#घोषणा RQ_VENDOR_QUERY_FW_READY	0x0E /* Query अगर new firmware पढ़ोy */

#घोषणा RQ_VENDOR_SET_FIFO_DISABLE	0x0F /* Set fअगरo disable */
#घोषणा RQ_VENDOR_SET_INTERFACE		0x10 /* Set पूर्णांकerface */
#घोषणा RQ_VENDOR_SET_HIGH_PERFOR	0x11 /* Set hi-perक्रमmance */

#घोषणा RQ_VENDOR_ERASE_BLOCK		0x12 /* Erase flash block */
#घोषणा RQ_VENDOR_WRITE_PAGE		0x13 /* Write flash page */
#घोषणा RQ_VENDOR_PREPARE_WRITE		0x14 /* Prepare ग_लिखो flash */
#घोषणा RQ_VENDOR_CONFIRM_WRITE		0x15 /* Confirm ग_लिखो flash */
#घोषणा RQ_VENDOR_LOCATE		0x16 /* Locate the device */

#घोषणा RQ_VENDOR_START_ROM_DOWN	0x17 /* Start firmware करोwnload */
#घोषणा RQ_VENDOR_ROM_DATA		0x18 /* Rom file data */
#घोषणा RQ_VENDOR_STOP_ROM_DOWN		0x19 /* Stop firmware करोwnload */
#घोषणा RQ_VENDOR_FW_DATA		0x20 /* Firmware data */

#घोषणा RQ_VENDOR_RESET_DEVICE		0x23 /* Try to reset the device */
#घोषणा RQ_VENDOR_QUERY_FW_CONFIG	0x24

#घोषणा RQ_VENDOR_GET_VERSION		0x81 /* Get firmware version */
#घोषणा RQ_VENDOR_GET_PAGE		0x82 /* Read flash page */
#घोषणा RQ_VENDOR_GET_ROM_PROC		0x83 /* Get ROM process state */

#घोषणा RQ_VENDOR_GET_INQUEUE		0x84 /* Data in input buffer */
#घोषणा RQ_VENDOR_GET_OUTQUEUE		0x85 /* Data in output buffer */

#घोषणा RQ_VENDOR_GET_MSR		0x86 /* Get modem status रेजिस्टर */

/* Definitions क्रम UPort event type */
#घोषणा UPORT_EVENT_NONE		0 /* None */
#घोषणा UPORT_EVENT_TXBUF_THRESHOLD	1 /* Tx buffer threshold */
#घोषणा UPORT_EVENT_SEND_NEXT		2 /* Send next */
#घोषणा UPORT_EVENT_MSR			3 /* Modem status */
#घोषणा UPORT_EVENT_LSR			4 /* Line status */
#घोषणा UPORT_EVENT_MCR			5 /* Modem control */

/* Definitions क्रम serial event type */
#घोषणा SERIAL_EV_CTS			0x0008	/* CTS changed state */
#घोषणा SERIAL_EV_DSR			0x0010	/* DSR changed state */
#घोषणा SERIAL_EV_RLSD			0x0020	/* RLSD changed state */

/* Definitions क्रम modem control event type */
#घोषणा SERIAL_EV_XOFF			0x40	/* XOFF received */

/* Definitions क्रम line control of communication */
#घोषणा MX_WORDLENGTH_5			5
#घोषणा MX_WORDLENGTH_6			6
#घोषणा MX_WORDLENGTH_7			7
#घोषणा MX_WORDLENGTH_8			8

#घोषणा MX_PARITY_NONE			0
#घोषणा MX_PARITY_ODD			1
#घोषणा MX_PARITY_EVEN			2
#घोषणा MX_PARITY_MARK			3
#घोषणा MX_PARITY_SPACE			4

#घोषणा MX_STOP_BITS_1			0
#घोषणा MX_STOP_BITS_1_5		1
#घोषणा MX_STOP_BITS_2			2

#घोषणा MX_RTS_DISABLE			0x0
#घोषणा MX_RTS_ENABLE			0x1
#घोषणा MX_RTS_HW			0x2
#घोषणा MX_RTS_NO_CHANGE		0x3 /* Flag, not valid रेजिस्टर value*/

#घोषणा MX_INT_RS232			0
#घोषणा MX_INT_2W_RS485			1
#घोषणा MX_INT_RS422			2
#घोषणा MX_INT_4W_RS485			3

/* Definitions क्रम holding reason */
#घोषणा MX_WAIT_FOR_CTS			0x0001
#घोषणा MX_WAIT_FOR_DSR			0x0002
#घोषणा MX_WAIT_FOR_DCD			0x0004
#घोषणा MX_WAIT_FOR_XON			0x0008
#घोषणा MX_WAIT_FOR_START_TX		0x0010
#घोषणा MX_WAIT_FOR_UNTHROTTLE		0x0020
#घोषणा MX_WAIT_FOR_LOW_WATER		0x0040
#घोषणा MX_WAIT_FOR_SEND_NEXT		0x0080

#घोषणा MX_UPORT_2_PORT			BIT(0)
#घोषणा MX_UPORT_4_PORT			BIT(1)
#घोषणा MX_UPORT_8_PORT			BIT(2)
#घोषणा MX_UPORT_16_PORT		BIT(3)

/* This काष्ठाure holds all of the local port inक्रमmation */
काष्ठा mxuport_port अणु
	u8 mcr_state;		/* Last MCR state */
	u8 msr_state;		/* Last MSR state */
	काष्ठा mutex mutex;	/* Protects mcr_state */
	spinlock_t spinlock;	/* Protects msr_state */
पूर्ण;

/* Table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id mxuport_idtable[] = अणु
	अणु USB_DEVICE(MX_USBSERIAL_VID, MX_UPORT1250_PID),
	  .driver_info = MX_UPORT_2_PORT पूर्ण,
	अणु USB_DEVICE(MX_USBSERIAL_VID, MX_UPORT1251_PID),
	  .driver_info = MX_UPORT_2_PORT पूर्ण,
	अणु USB_DEVICE(MX_USBSERIAL_VID, MX_UPORT1410_PID),
	  .driver_info = MX_UPORT_4_PORT पूर्ण,
	अणु USB_DEVICE(MX_USBSERIAL_VID, MX_UPORT1450_PID),
	  .driver_info = MX_UPORT_4_PORT पूर्ण,
	अणु USB_DEVICE(MX_USBSERIAL_VID, MX_UPORT1451_PID),
	  .driver_info = MX_UPORT_4_PORT पूर्ण,
	अणु USB_DEVICE(MX_USBSERIAL_VID, MX_UPORT1618_PID),
	  .driver_info = MX_UPORT_8_PORT पूर्ण,
	अणु USB_DEVICE(MX_USBSERIAL_VID, MX_UPORT1658_PID),
	  .driver_info = MX_UPORT_8_PORT पूर्ण,
	अणु USB_DEVICE(MX_USBSERIAL_VID, MX_UPORT1613_PID),
	  .driver_info = MX_UPORT_16_PORT पूर्ण,
	अणु USB_DEVICE(MX_USBSERIAL_VID, MX_UPORT1653_PID),
	  .driver_info = MX_UPORT_16_PORT पूर्ण,
	अणुपूर्ण			/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, mxuport_idtable);

/*
 * Add a four byte header containing the port number and the number of
 * bytes of data in the message. Return the number of bytes in the
 * buffer.
 */
अटल पूर्णांक mxuport_prepare_ग_लिखो_buffer(काष्ठा usb_serial_port *port,
					व्योम *dest, माप_प्रकार size)
अणु
	u8 *buf = dest;
	पूर्णांक count;

	count = kfअगरo_out_locked(&port->ग_लिखो_fअगरo, buf + HEADER_SIZE,
				 size - HEADER_SIZE,
				 &port->lock);

	put_unaligned_be16(port->port_number, buf);
	put_unaligned_be16(count, buf + 2);

	dev_dbg(&port->dev, "%s - size %zd count %d\n", __func__,
		size, count);

	वापस count + HEADER_SIZE;
पूर्ण

/* Read the given buffer in from the control pipe. */
अटल पूर्णांक mxuport_recv_ctrl_urb(काष्ठा usb_serial *serial,
				 u8 request, u16 value, u16 index,
				 u8 *data, माप_प्रकार size)
अणु
	पूर्णांक status;

	status = usb_control_msg(serial->dev,
				 usb_rcvctrlpipe(serial->dev, 0),
				 request,
				 (USB_सूची_IN | USB_TYPE_VENDOR |
				  USB_RECIP_DEVICE), value, index,
				 data, size,
				 USB_CTRL_GET_TIMEOUT);
	अगर (status < 0) अणु
		dev_err(&serial->पूर्णांकerface->dev,
			"%s - usb_control_msg failed (%d)\n",
			__func__, status);
		वापस status;
	पूर्ण

	अगर (status != size) अणु
		dev_err(&serial->पूर्णांकerface->dev,
			"%s - short read (%d / %zd)\n",
			__func__, status, size);
		वापस -EIO;
	पूर्ण

	वापस status;
पूर्ण

/* Write the given buffer out to the control pipe.  */
अटल पूर्णांक mxuport_send_ctrl_data_urb(काष्ठा usb_serial *serial,
				      u8 request,
				      u16 value, u16 index,
				      u8 *data, माप_प्रकार size)
अणु
	पूर्णांक status;

	status = usb_control_msg(serial->dev,
				 usb_sndctrlpipe(serial->dev, 0),
				 request,
				 (USB_सूची_OUT | USB_TYPE_VENDOR |
				  USB_RECIP_DEVICE), value, index,
				 data, size,
				 USB_CTRL_SET_TIMEOUT);
	अगर (status < 0) अणु
		dev_err(&serial->पूर्णांकerface->dev,
			"%s - usb_control_msg failed (%d)\n",
			__func__, status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

/* Send a venकरोr request without any data */
अटल पूर्णांक mxuport_send_ctrl_urb(काष्ठा usb_serial *serial,
				 u8 request, u16 value, u16 index)
अणु
	वापस mxuport_send_ctrl_data_urb(serial, request, value, index,
					  शून्य, 0);
पूर्ण

/*
 * mxuport_throttle - throttle function of driver
 *
 * This function is called by the tty driver when it wants to stop the
 * data being पढ़ो from the port. Since all the data comes over one
 * bulk in endpoपूर्णांक, we cannot stop submitting urbs by setting
 * port->throttle. Instead tell the device to stop sending us data क्रम
 * the port.
 */
अटल व्योम mxuport_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_serial *serial = port->serial;

	dev_dbg(&port->dev, "%s\n", __func__);

	mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_RX_HOST_EN,
			      0, port->port_number);
पूर्ण

/*
 * mxuport_unthrottle - unthrottle function of driver
 *
 * This function is called by the tty driver when it wants to resume
 * the data being पढ़ो from the port. Tell the device it can resume
 * sending us received data from the port.
 */
अटल व्योम mxuport_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु

	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_serial *serial = port->serial;

	dev_dbg(&port->dev, "%s\n", __func__);

	mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_RX_HOST_EN,
			      1, port->port_number);
पूर्ण

/*
 * Processes one chunk of data received क्रम a port.  Mostly a copy of
 * usb_serial_generic_process_पढ़ो_urb().
 */
अटल व्योम mxuport_process_पढ़ो_urb_data(काष्ठा usb_serial_port *port,
					  अक्षर *data, पूर्णांक size)
अणु
	पूर्णांक i;

	अगर (port->sysrq) अणु
		क्रम (i = 0; i < size; i++, data++) अणु
			अगर (!usb_serial_handle_sysrq_अक्षर(port, *data))
				tty_insert_flip_अक्षर(&port->port, *data,
						     TTY_NORMAL);
		पूर्ण
	पूर्ण अन्यथा अणु
		tty_insert_flip_string(&port->port, data, size);
	पूर्ण
	tty_flip_buffer_push(&port->port);
पूर्ण

अटल व्योम mxuport_msr_event(काष्ठा usb_serial_port *port, u8 buf[4])
अणु
	काष्ठा mxuport_port *mxport = usb_get_serial_port_data(port);
	u8 rcv_msr_hold = buf[2] & 0xF0;
	u16 rcv_msr_event = get_unaligned_be16(buf);
	अचिन्हित दीर्घ flags;

	अगर (rcv_msr_event == 0)
		वापस;

	/* Update MSR status */
	spin_lock_irqsave(&mxport->spinlock, flags);

	dev_dbg(&port->dev, "%s - current MSR status = 0x%x\n",
		__func__, mxport->msr_state);

	अगर (rcv_msr_hold & UART_MSR_CTS) अणु
		mxport->msr_state |= UART_MSR_CTS;
		dev_dbg(&port->dev, "%s - CTS high\n", __func__);
	पूर्ण अन्यथा अणु
		mxport->msr_state &= ~UART_MSR_CTS;
		dev_dbg(&port->dev, "%s - CTS low\n", __func__);
	पूर्ण

	अगर (rcv_msr_hold & UART_MSR_DSR) अणु
		mxport->msr_state |= UART_MSR_DSR;
		dev_dbg(&port->dev, "%s - DSR high\n", __func__);
	पूर्ण अन्यथा अणु
		mxport->msr_state &= ~UART_MSR_DSR;
		dev_dbg(&port->dev, "%s - DSR low\n", __func__);
	पूर्ण

	अगर (rcv_msr_hold & UART_MSR_DCD) अणु
		mxport->msr_state |= UART_MSR_DCD;
		dev_dbg(&port->dev, "%s - DCD high\n", __func__);
	पूर्ण अन्यथा अणु
		mxport->msr_state &= ~UART_MSR_DCD;
		dev_dbg(&port->dev, "%s - DCD low\n", __func__);
	पूर्ण
	spin_unlock_irqrestore(&mxport->spinlock, flags);

	अगर (rcv_msr_event &
	    (SERIAL_EV_CTS | SERIAL_EV_DSR | SERIAL_EV_RLSD)) अणु

		अगर (rcv_msr_event & SERIAL_EV_CTS) अणु
			port->icount.cts++;
			dev_dbg(&port->dev, "%s - CTS change\n", __func__);
		पूर्ण

		अगर (rcv_msr_event & SERIAL_EV_DSR) अणु
			port->icount.dsr++;
			dev_dbg(&port->dev, "%s - DSR change\n", __func__);
		पूर्ण

		अगर (rcv_msr_event & SERIAL_EV_RLSD) अणु
			port->icount.dcd++;
			dev_dbg(&port->dev, "%s - DCD change\n", __func__);
		पूर्ण
		wake_up_पूर्णांकerruptible(&port->port.delta_msr_रुको);
	पूर्ण
पूर्ण

अटल व्योम mxuport_lsr_event(काष्ठा usb_serial_port *port, u8 buf[4])
अणु
	u8 lsr_event = buf[2];

	अगर (lsr_event & UART_LSR_BI) अणु
		port->icount.brk++;
		dev_dbg(&port->dev, "%s - break error\n", __func__);
	पूर्ण

	अगर (lsr_event & UART_LSR_FE) अणु
		port->icount.frame++;
		dev_dbg(&port->dev, "%s - frame error\n", __func__);
	पूर्ण

	अगर (lsr_event & UART_LSR_PE) अणु
		port->icount.parity++;
		dev_dbg(&port->dev, "%s - parity error\n", __func__);
	पूर्ण

	अगर (lsr_event & UART_LSR_OE) अणु
		port->icount.overrun++;
		dev_dbg(&port->dev, "%s - overrun error\n", __func__);
	पूर्ण
पूर्ण

/*
 * When something पूर्णांकeresting happens, modem control lines XON/XOFF
 * etc, the device sends an event. Process these events.
 */
अटल व्योम mxuport_process_पढ़ो_urb_event(काष्ठा usb_serial_port *port,
					   u8 buf[4], u32 event)
अणु
	dev_dbg(&port->dev, "%s - receive event : %04x\n", __func__, event);

	चयन (event) अणु
	हाल UPORT_EVENT_SEND_NEXT:
		/*
		 * Sent as part of the flow control on device buffers.
		 * Not currently used.
		 */
		अवरोध;
	हाल UPORT_EVENT_MSR:
		mxuport_msr_event(port, buf);
		अवरोध;
	हाल UPORT_EVENT_LSR:
		mxuport_lsr_event(port, buf);
		अवरोध;
	हाल UPORT_EVENT_MCR:
		/*
		 * Event to indicate a change in XON/XOFF from the
		 * peer.  Currently not used. We just जारी
		 * sending the device data and it will buffer it अगर
		 * needed. This event could be used क्रम flow control
		 * between the host and the device.
		 */
		अवरोध;
	शेष:
		dev_dbg(&port->dev, "Unexpected event\n");
		अवरोध;
	पूर्ण
पूर्ण

/*
 * One URB can contain data क्रम multiple ports. Demultiplex the data,
 * checking the port exists, is खोलोed and the message is valid.
 */
अटल व्योम mxuport_process_पढ़ो_urb_demux_data(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा usb_serial *serial = port->serial;
	u8 *data = urb->transfer_buffer;
	u8 *end = data + urb->actual_length;
	काष्ठा usb_serial_port *demux_port;
	u8 *ch;
	u16 rcv_port;
	u16 rcv_len;

	जबतक (data < end) अणु
		अगर (data + HEADER_SIZE > end) अणु
			dev_warn(&port->dev, "%s - message with short header\n",
				 __func__);
			वापस;
		पूर्ण

		rcv_port = get_unaligned_be16(data);
		अगर (rcv_port >= serial->num_ports) अणु
			dev_warn(&port->dev, "%s - message for invalid port\n",
				 __func__);
			वापस;
		पूर्ण

		demux_port = serial->port[rcv_port];
		rcv_len = get_unaligned_be16(data + 2);
		अगर (!rcv_len || data + HEADER_SIZE + rcv_len > end) अणु
			dev_warn(&port->dev, "%s - short data\n", __func__);
			वापस;
		पूर्ण

		अगर (tty_port_initialized(&demux_port->port)) अणु
			ch = data + HEADER_SIZE;
			mxuport_process_पढ़ो_urb_data(demux_port, ch, rcv_len);
		पूर्ण अन्यथा अणु
			dev_dbg(&demux_port->dev, "%s - data for closed port\n",
				__func__);
		पूर्ण
		data += HEADER_SIZE + rcv_len;
	पूर्ण
पूर्ण

/*
 * One URB can contain events क्रम multiple ports. Demultiplex the event,
 * checking the port exists, and is खोलोed.
 */
अटल व्योम mxuport_process_पढ़ो_urb_demux_event(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा usb_serial *serial = port->serial;
	u8 *data = urb->transfer_buffer;
	u8 *end = data + urb->actual_length;
	काष्ठा usb_serial_port *demux_port;
	u8 *ch;
	u16 rcv_port;
	u16 rcv_event;

	जबतक (data < end) अणु
		अगर (data + EVENT_LENGTH > end) अणु
			dev_warn(&port->dev, "%s - message with short event\n",
				 __func__);
			वापस;
		पूर्ण

		rcv_port = get_unaligned_be16(data);
		अगर (rcv_port >= serial->num_ports) अणु
			dev_warn(&port->dev, "%s - message for invalid port\n",
				 __func__);
			वापस;
		पूर्ण

		demux_port = serial->port[rcv_port];
		अगर (tty_port_initialized(&demux_port->port)) अणु
			ch = data + HEADER_SIZE;
			rcv_event = get_unaligned_be16(data + 2);
			mxuport_process_पढ़ो_urb_event(demux_port, ch,
						       rcv_event);
		पूर्ण अन्यथा अणु
			dev_dbg(&demux_port->dev,
				"%s - event for closed port\n", __func__);
		पूर्ण
		data += EVENT_LENGTH;
	पूर्ण
पूर्ण

/*
 * This is called when we have received data on the bulk in
 * endpoपूर्णांक. Depending on which port it was received on, it can
 * contain serial data or events.
 */
अटल व्योम mxuport_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा usb_serial *serial = port->serial;

	अगर (port == serial->port[0])
		mxuport_process_पढ़ो_urb_demux_data(urb);

	अगर (port == serial->port[1])
		mxuport_process_पढ़ो_urb_demux_event(urb);
पूर्ण

/*
 * Ask the device how many bytes it has queued to be sent out. If
 * there are none, वापस true.
 */
अटल bool mxuport_tx_empty(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	bool is_empty = true;
	u32 txlen;
	u8 *len_buf;
	पूर्णांक err;

	len_buf = kzalloc(4, GFP_KERNEL);
	अगर (!len_buf)
		जाओ out;

	err = mxuport_recv_ctrl_urb(serial, RQ_VENDOR_GET_OUTQUEUE, 0,
				    port->port_number, len_buf, 4);
	अगर (err < 0)
		जाओ out;

	txlen = get_unaligned_be32(len_buf);
	dev_dbg(&port->dev, "%s - tx len = %u\n", __func__, txlen);

	अगर (txlen != 0)
		is_empty = false;

out:
	kमुक्त(len_buf);
	वापस is_empty;
पूर्ण

अटल पूर्णांक mxuport_set_mcr(काष्ठा usb_serial_port *port, u8 mcr_state)
अणु
	काष्ठा usb_serial *serial = port->serial;
	पूर्णांक err;

	dev_dbg(&port->dev, "%s - %02x\n", __func__, mcr_state);

	err = mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_MCR,
				    mcr_state, port->port_number);
	अगर (err)
		dev_err(&port->dev, "%s - failed to change MCR\n", __func__);

	वापस err;
पूर्ण

अटल पूर्णांक mxuport_set_dtr(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	काष्ठा mxuport_port *mxport = usb_get_serial_port_data(port);
	काष्ठा usb_serial *serial = port->serial;
	पूर्णांक err;

	mutex_lock(&mxport->mutex);

	err = mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_DTR,
				    !!on, port->port_number);
	अगर (!err) अणु
		अगर (on)
			mxport->mcr_state |= UART_MCR_DTR;
		अन्यथा
			mxport->mcr_state &= ~UART_MCR_DTR;
	पूर्ण

	mutex_unlock(&mxport->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक mxuport_set_rts(काष्ठा usb_serial_port *port, u8 state)
अणु
	काष्ठा mxuport_port *mxport = usb_get_serial_port_data(port);
	काष्ठा usb_serial *serial = port->serial;
	पूर्णांक err;
	u8 mcr_state;

	mutex_lock(&mxport->mutex);
	mcr_state = mxport->mcr_state;

	चयन (state) अणु
	हाल MX_RTS_DISABLE:
		mcr_state &= ~UART_MCR_RTS;
		अवरोध;
	हाल MX_RTS_ENABLE:
		mcr_state |= UART_MCR_RTS;
		अवरोध;
	हाल MX_RTS_HW:
		/*
		 * Do not update mxport->mcr_state when करोing hardware
		 * flow control.
		 */
		अवरोध;
	शेष:
		/*
		 * Should not happen, but somebody might try passing
		 * MX_RTS_NO_CHANGE, which is not valid.
		 */
		err = -EINVAL;
		जाओ out;
	पूर्ण
	err = mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_RTS,
				    state, port->port_number);
	अगर (!err)
		mxport->mcr_state = mcr_state;

out:
	mutex_unlock(&mxport->mutex);

	वापस err;
पूर्ण

अटल व्योम mxuport_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	काष्ठा mxuport_port *mxport = usb_get_serial_port_data(port);
	u8 mcr_state;
	पूर्णांक err;

	mutex_lock(&mxport->mutex);
	mcr_state = mxport->mcr_state;

	अगर (on)
		mcr_state |= (UART_MCR_RTS | UART_MCR_DTR);
	अन्यथा
		mcr_state &= ~(UART_MCR_RTS | UART_MCR_DTR);

	err = mxuport_set_mcr(port, mcr_state);
	अगर (!err)
		mxport->mcr_state = mcr_state;

	mutex_unlock(&mxport->mutex);
पूर्ण

अटल पूर्णांक mxuport_tiocmset(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक set,
			    अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा mxuport_port *mxport = usb_get_serial_port_data(port);
	पूर्णांक err;
	u8 mcr_state;

	mutex_lock(&mxport->mutex);
	mcr_state = mxport->mcr_state;

	अगर (set & TIOCM_RTS)
		mcr_state |= UART_MCR_RTS;

	अगर (set & TIOCM_DTR)
		mcr_state |= UART_MCR_DTR;

	अगर (clear & TIOCM_RTS)
		mcr_state &= ~UART_MCR_RTS;

	अगर (clear & TIOCM_DTR)
		mcr_state &= ~UART_MCR_DTR;

	err = mxuport_set_mcr(port, mcr_state);
	अगर (!err)
		mxport->mcr_state = mcr_state;

	mutex_unlock(&mxport->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक mxuport_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mxuport_port *mxport;
	काष्ठा usb_serial_port *port = tty->driver_data;
	अचिन्हित पूर्णांक result;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक msr;
	अचिन्हित पूर्णांक mcr;

	mxport = usb_get_serial_port_data(port);

	mutex_lock(&mxport->mutex);
	spin_lock_irqsave(&mxport->spinlock, flags);

	msr = mxport->msr_state;
	mcr = mxport->mcr_state;

	spin_unlock_irqrestore(&mxport->spinlock, flags);
	mutex_unlock(&mxport->mutex);

	result = (((mcr & UART_MCR_DTR) ? TIOCM_DTR : 0) |	/* 0x002 */
		  ((mcr & UART_MCR_RTS) ? TIOCM_RTS : 0) |	/* 0x004 */
		  ((msr & UART_MSR_CTS) ? TIOCM_CTS : 0) |	/* 0x020 */
		  ((msr & UART_MSR_DCD) ? TIOCM_CAR : 0) |	/* 0x040 */
		  ((msr & UART_MSR_RI) ? TIOCM_RI : 0) |	/* 0x080 */
		  ((msr & UART_MSR_DSR) ? TIOCM_DSR : 0));	/* 0x100 */

	dev_dbg(&port->dev, "%s - 0x%04x\n", __func__, result);

	वापस result;
पूर्ण

अटल पूर्णांक mxuport_set_termios_flow(काष्ठा tty_काष्ठा *tty,
				    काष्ठा ktermios *old_termios,
				    काष्ठा usb_serial_port *port,
				    काष्ठा usb_serial *serial)
अणु
	u8 xon = START_CHAR(tty);
	u8 xoff = STOP_CHAR(tty);
	पूर्णांक enable;
	पूर्णांक err;
	u8 *buf;
	u8 rts;

	buf = kदो_स्मृति(2, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* S/W flow control settings */
	अगर (I_IXOFF(tty) || I_IXON(tty)) अणु
		enable = 1;
		buf[0] = xon;
		buf[1] = xoff;

		err = mxuport_send_ctrl_data_urb(serial, RQ_VENDOR_SET_CHARS,
						 0, port->port_number,
						 buf, 2);
		अगर (err)
			जाओ out;

		dev_dbg(&port->dev, "%s - XON = 0x%02x, XOFF = 0x%02x\n",
			__func__, xon, xoff);
	पूर्ण अन्यथा अणु
		enable = 0;
	पूर्ण

	err = mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_XONXOFF,
				    enable, port->port_number);
	अगर (err)
		जाओ out;

	rts = MX_RTS_NO_CHANGE;

	/* H/W flow control settings */
	अगर (!old_termios ||
	    C_CRTSCTS(tty) != (old_termios->c_cflag & CRTSCTS)) अणु
		अगर (C_CRTSCTS(tty))
			rts = MX_RTS_HW;
		अन्यथा
			rts = MX_RTS_ENABLE;
	पूर्ण

	अगर (C_BAUD(tty)) अणु
		अगर (old_termios && (old_termios->c_cflag & CBAUD) == B0) अणु
			/* Raise DTR and RTS */
			अगर (C_CRTSCTS(tty))
				rts = MX_RTS_HW;
			अन्यथा
				rts = MX_RTS_ENABLE;
			mxuport_set_dtr(port, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Drop DTR and RTS */
		rts = MX_RTS_DISABLE;
		mxuport_set_dtr(port, 0);
	पूर्ण

	अगर (rts != MX_RTS_NO_CHANGE)
		err = mxuport_set_rts(port, rts);

out:
	kमुक्त(buf);
	वापस err;
पूर्ण

अटल व्योम mxuport_set_termios(काष्ठा tty_काष्ठा *tty,
				काष्ठा usb_serial_port *port,
				काष्ठा ktermios *old_termios)
अणु
	काष्ठा usb_serial *serial = port->serial;
	u8 *buf;
	u8 data_bits;
	u8 stop_bits;
	u8 parity;
	पूर्णांक baud;
	पूर्णांक err;

	अगर (old_termios &&
	    !tty_termios_hw_change(&tty->termios, old_termios) &&
	    tty->termios.c_अगरlag == old_termios->c_अगरlag) अणु
		dev_dbg(&port->dev, "%s - nothing to change\n", __func__);
		वापस;
	पूर्ण

	buf = kदो_स्मृति(4, GFP_KERNEL);
	अगर (!buf)
		वापस;

	/* Set data bit of termios */
	चयन (C_CSIZE(tty)) अणु
	हाल CS5:
		data_bits = MX_WORDLENGTH_5;
		अवरोध;
	हाल CS6:
		data_bits = MX_WORDLENGTH_6;
		अवरोध;
	हाल CS7:
		data_bits = MX_WORDLENGTH_7;
		अवरोध;
	हाल CS8:
	शेष:
		data_bits = MX_WORDLENGTH_8;
		अवरोध;
	पूर्ण

	/* Set parity of termios */
	अगर (C_PARENB(tty)) अणु
		अगर (C_CMSPAR(tty)) अणु
			अगर (C_PARODD(tty))
				parity = MX_PARITY_MARK;
			अन्यथा
				parity = MX_PARITY_SPACE;
		पूर्ण अन्यथा अणु
			अगर (C_PARODD(tty))
				parity = MX_PARITY_ODD;
			अन्यथा
				parity = MX_PARITY_EVEN;
		पूर्ण
	पूर्ण अन्यथा अणु
		parity = MX_PARITY_NONE;
	पूर्ण

	/* Set stop bit of termios */
	अगर (C_CSTOPB(tty))
		stop_bits = MX_STOP_BITS_2;
	अन्यथा
		stop_bits = MX_STOP_BITS_1;

	buf[0] = data_bits;
	buf[1] = parity;
	buf[2] = stop_bits;
	buf[3] = 0;

	err = mxuport_send_ctrl_data_urb(serial, RQ_VENDOR_SET_LINE,
					 0, port->port_number, buf, 4);
	अगर (err)
		जाओ out;

	err = mxuport_set_termios_flow(tty, old_termios, port, serial);
	अगर (err)
		जाओ out;

	baud = tty_get_baud_rate(tty);
	अगर (!baud)
		baud = 9600;

	/* Note: Little Endian */
	put_unaligned_le32(baud, buf);

	err = mxuport_send_ctrl_data_urb(serial, RQ_VENDOR_SET_BAUD,
					 0, port->port_number,
					 buf, 4);
	अगर (err)
		जाओ out;

	dev_dbg(&port->dev, "baud_rate	: %d\n", baud);
	dev_dbg(&port->dev, "data_bits	: %d\n", data_bits);
	dev_dbg(&port->dev, "parity	: %d\n", parity);
	dev_dbg(&port->dev, "stop_bits	: %d\n", stop_bits);

out:
	kमुक्त(buf);
पूर्ण

/*
 * Determine how many ports this device has dynamically.  It will be
 * called after the probe() callback is called, but beक्रमe attach().
 */
अटल पूर्णांक mxuport_calc_num_ports(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds)
अणु
	अचिन्हित दीर्घ features = (अचिन्हित दीर्घ)usb_get_serial_data(serial);
	पूर्णांक num_ports;
	पूर्णांक i;

	अगर (features & MX_UPORT_2_PORT) अणु
		num_ports = 2;
	पूर्ण अन्यथा अगर (features & MX_UPORT_4_PORT) अणु
		num_ports = 4;
	पूर्ण अन्यथा अगर (features & MX_UPORT_8_PORT) अणु
		num_ports = 8;
	पूर्ण अन्यथा अगर (features & MX_UPORT_16_PORT) अणु
		num_ports = 16;
	पूर्ण अन्यथा अणु
		dev_warn(&serial->पूर्णांकerface->dev,
				"unknown device, assuming two ports\n");
		num_ports = 2;
	पूर्ण

	/*
	 * Setup bulk-out endpoपूर्णांक multiplexing. All ports share the same
	 * bulk-out endpoपूर्णांक.
	 */
	BUILD_BUG_ON(ARRAY_SIZE(epds->bulk_out) < 16);

	क्रम (i = 1; i < num_ports; ++i)
		epds->bulk_out[i] = epds->bulk_out[0];

	epds->num_bulk_out = num_ports;

	वापस num_ports;
पूर्ण

/* Get the version of the firmware currently running. */
अटल पूर्णांक mxuport_get_fw_version(काष्ठा usb_serial *serial, u32 *version)
अणु
	u8 *ver_buf;
	पूर्णांक err;

	ver_buf = kzalloc(4, GFP_KERNEL);
	अगर (!ver_buf)
		वापस -ENOMEM;

	/* Get firmware version from SDRAM */
	err = mxuport_recv_ctrl_urb(serial, RQ_VENDOR_GET_VERSION, 0, 0,
				    ver_buf, 4);
	अगर (err != 4) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	*version = (ver_buf[0] << 16) | (ver_buf[1] << 8) | ver_buf[2];
	err = 0;
out:
	kमुक्त(ver_buf);
	वापस err;
पूर्ण

/* Given a firmware blob, करोwnload it to the device. */
अटल पूर्णांक mxuport_करोwnload_fw(काष्ठा usb_serial *serial,
			       स्थिर काष्ठा firmware *fw_p)
अणु
	u8 *fw_buf;
	माप_प्रकार txlen;
	माप_प्रकार fwidx;
	पूर्णांक err;

	fw_buf = kदो_स्मृति(DOWN_BLOCK_SIZE, GFP_KERNEL);
	अगर (!fw_buf)
		वापस -ENOMEM;

	dev_dbg(&serial->पूर्णांकerface->dev, "Starting firmware download...\n");
	err = mxuport_send_ctrl_urb(serial, RQ_VENDOR_START_FW_DOWN, 0, 0);
	अगर (err)
		जाओ out;

	fwidx = 0;
	करो अणु
		txlen = min_t(माप_प्रकार, (fw_p->size - fwidx), DOWN_BLOCK_SIZE);

		स_नकल(fw_buf, &fw_p->data[fwidx], txlen);
		err = mxuport_send_ctrl_data_urb(serial, RQ_VENDOR_FW_DATA,
						 0, 0, fw_buf, txlen);
		अगर (err) अणु
			mxuport_send_ctrl_urb(serial, RQ_VENDOR_STOP_FW_DOWN,
					      0, 0);
			जाओ out;
		पूर्ण

		fwidx += txlen;
		usleep_range(1000, 2000);

	पूर्ण जबतक (fwidx < fw_p->size);

	msleep(1000);
	err = mxuport_send_ctrl_urb(serial, RQ_VENDOR_STOP_FW_DOWN, 0, 0);
	अगर (err)
		जाओ out;

	msleep(1000);
	err = mxuport_send_ctrl_urb(serial, RQ_VENDOR_QUERY_FW_READY, 0, 0);

out:
	kमुक्त(fw_buf);
	वापस err;
पूर्ण

अटल पूर्णांक mxuport_probe(काष्ठा usb_serial *serial,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	u16 productid = le16_to_cpu(serial->dev->descriptor.idProduct);
	स्थिर काष्ठा firmware *fw_p = शून्य;
	u32 version;
	पूर्णांक local_ver;
	अक्षर buf[32];
	पूर्णांक err;

	/* Load our firmware */
	err = mxuport_send_ctrl_urb(serial, RQ_VENDOR_QUERY_FW_CONFIG, 0, 0);
	अगर (err) अणु
		mxuport_send_ctrl_urb(serial, RQ_VENDOR_RESET_DEVICE, 0, 0);
		वापस err;
	पूर्ण

	err = mxuport_get_fw_version(serial, &version);
	अगर (err < 0)
		वापस err;

	dev_dbg(&serial->पूर्णांकerface->dev, "Device firmware version v%x.%x.%x\n",
		(version & 0xff0000) >> 16,
		(version & 0xff00) >> 8,
		(version & 0xff));

	snम_लिखो(buf, माप(buf) - 1, "moxa/moxa-%04x.fw", productid);

	err = request_firmware(&fw_p, buf, &serial->पूर्णांकerface->dev);
	अगर (err) अणु
		dev_warn(&serial->पूर्णांकerface->dev, "Firmware %s not found\n",
			 buf);

		/* Use the firmware alपढ़ोy in the device */
		err = 0;
	पूर्ण अन्यथा अणु
		local_ver = ((fw_p->data[VER_ADDR_1] << 16) |
			     (fw_p->data[VER_ADDR_2] << 8) |
			     fw_p->data[VER_ADDR_3]);
		dev_dbg(&serial->पूर्णांकerface->dev,
			"Available firmware version v%x.%x.%x\n",
			fw_p->data[VER_ADDR_1], fw_p->data[VER_ADDR_2],
			fw_p->data[VER_ADDR_3]);
		अगर (local_ver > version) अणु
			err = mxuport_करोwnload_fw(serial, fw_p);
			अगर (err)
				जाओ out;
			err  = mxuport_get_fw_version(serial, &version);
			अगर (err < 0)
				जाओ out;
		पूर्ण
	पूर्ण

	dev_info(&serial->पूर्णांकerface->dev,
		 "Using device firmware version v%x.%x.%x\n",
		 (version & 0xff0000) >> 16,
		 (version & 0xff00) >> 8,
		 (version & 0xff));

	/*
	 * Contains the features of this hardware. Store away क्रम
	 * later use, eg, number of ports.
	 */
	usb_set_serial_data(serial, (व्योम *)id->driver_info);
out:
	अगर (fw_p)
		release_firmware(fw_p);
	वापस err;
पूर्ण


अटल पूर्णांक mxuport_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा mxuport_port *mxport;
	पूर्णांक err;

	mxport = devm_kzalloc(&port->dev, माप(काष्ठा mxuport_port),
			      GFP_KERNEL);
	अगर (!mxport)
		वापस -ENOMEM;

	mutex_init(&mxport->mutex);
	spin_lock_init(&mxport->spinlock);

	/* Set the port निजी data */
	usb_set_serial_port_data(port, mxport);

	/* Set FIFO (Enable) */
	err = mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_FIFO_DISABLE,
				    0, port->port_number);
	अगर (err)
		वापस err;

	/* Set transmission mode (Hi-Perक्रमmance) */
	err = mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_HIGH_PERFOR,
				    0, port->port_number);
	अगर (err)
		वापस err;

	/* Set पूर्णांकerface (RS-232) */
	वापस mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_INTERFACE,
				     MX_INT_RS232,
				     port->port_number);
पूर्ण

अटल पूर्णांक mxuport_attach(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_serial_port *port0 = serial->port[0];
	काष्ठा usb_serial_port *port1 = serial->port[1];
	पूर्णांक err;

	/*
	 * All data from the ports is received on the first bulk in
	 * endpoपूर्णांक, with a multiplex header. The second bulk in is
	 * used क्रम events.
	 *
	 * Start to पढ़ो from the device.
	 */
	err = usb_serial_generic_submit_पढ़ो_urbs(port0, GFP_KERNEL);
	अगर (err)
		वापस err;

	err = usb_serial_generic_submit_पढ़ो_urbs(port1, GFP_KERNEL);
	अगर (err) अणु
		usb_serial_generic_बंद(port0);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mxuport_release(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_serial_port *port0 = serial->port[0];
	काष्ठा usb_serial_port *port1 = serial->port[1];

	usb_serial_generic_बंद(port1);
	usb_serial_generic_बंद(port0);
पूर्ण

अटल पूर्णांक mxuport_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा mxuport_port *mxport = usb_get_serial_port_data(port);
	काष्ठा usb_serial *serial = port->serial;
	पूर्णांक err;

	/* Set receive host (enable) */
	err = mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_RX_HOST_EN,
				    1, port->port_number);
	अगर (err)
		वापस err;

	err = mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_OPEN,
				    1, port->port_number);
	अगर (err) अणु
		mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_RX_HOST_EN,
				      0, port->port_number);
		वापस err;
	पूर्ण

	/* Initial port termios */
	अगर (tty)
		mxuport_set_termios(tty, port, शून्य);

	/*
	 * TODO: use RQ_VENDOR_GET_MSR, once we know what it
	 * वापसs.
	 */
	mxport->msr_state = 0;

	वापस err;
पूर्ण

अटल व्योम mxuport_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;

	mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_OPEN, 0,
			      port->port_number);

	mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_RX_HOST_EN, 0,
			      port->port_number);
पूर्ण

/* Send a अवरोध to the port. */
अटल व्योम mxuport_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_serial *serial = port->serial;
	पूर्णांक enable;

	अगर (अवरोध_state == -1) अणु
		enable = 1;
		dev_dbg(&port->dev, "%s - sending break\n", __func__);
	पूर्ण अन्यथा अणु
		enable = 0;
		dev_dbg(&port->dev, "%s - clearing break\n", __func__);
	पूर्ण

	mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_BREAK,
			      enable, port->port_number);
पूर्ण

अटल पूर्णांक mxuport_resume(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_serial_port *port;
	पूर्णांक c = 0;
	पूर्णांक i;
	पूर्णांक r;

	क्रम (i = 0; i < 2; i++) अणु
		port = serial->port[i];

		r = usb_serial_generic_submit_पढ़ो_urbs(port, GFP_NOIO);
		अगर (r < 0)
			c++;
	पूर्ण

	क्रम (i = 0; i < serial->num_ports; i++) अणु
		port = serial->port[i];
		अगर (!tty_port_initialized(&port->port))
			जारी;

		r = usb_serial_generic_ग_लिखो_start(port, GFP_NOIO);
		अगर (r < 0)
			c++;
	पूर्ण

	वापस c ? -EIO : 0;
पूर्ण

अटल काष्ठा usb_serial_driver mxuport_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"mxuport",
	पूर्ण,
	.description		= "MOXA UPort",
	.id_table		= mxuport_idtable,
	.num_bulk_in		= 2,
	.num_bulk_out		= 1,
	.probe			= mxuport_probe,
	.port_probe		= mxuport_port_probe,
	.attach			= mxuport_attach,
	.release		= mxuport_release,
	.calc_num_ports		= mxuport_calc_num_ports,
	.खोलो			= mxuport_खोलो,
	.बंद			= mxuport_बंद,
	.set_termios		= mxuport_set_termios,
	.अवरोध_ctl		= mxuport_अवरोध_ctl,
	.tx_empty		= mxuport_tx_empty,
	.tiocmiरुको		= usb_serial_generic_tiocmiरुको,
	.get_icount		= usb_serial_generic_get_icount,
	.throttle		= mxuport_throttle,
	.unthrottle		= mxuport_unthrottle,
	.tiocmget		= mxuport_tiocmget,
	.tiocmset		= mxuport_tiocmset,
	.dtr_rts		= mxuport_dtr_rts,
	.process_पढ़ो_urb	= mxuport_process_पढ़ो_urb,
	.prepare_ग_लिखो_buffer	= mxuport_prepare_ग_लिखो_buffer,
	.resume			= mxuport_resume,
पूर्ण;

अटल काष्ठा usb_serial_driver *स्थिर serial_drivers[] = अणु
	&mxuport_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, mxuport_idtable);

MODULE_AUTHOR("Andrew Lunn <andrew@lunn.ch>");
MODULE_AUTHOR("<support@moxa.com>");
MODULE_LICENSE("GPL");
