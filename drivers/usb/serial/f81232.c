<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Fपूर्णांकek F81232 USB to serial adaptor driver
 * Fपूर्णांकek F81532A/534A/535/536 USB to 2/4/8/12 serial adaptor driver
 *
 * Copyright (C) 2012 Greg Kroah-Harपंचांगan (gregkh@linuxfoundation.org)
 * Copyright (C) 2012 Linux Foundation
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
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/serial_reg.h>

#घोषणा F81232_ID		\
	अणु USB_DEVICE(0x1934, 0x0706) पूर्ण	/* 1 port UART device */

#घोषणा F81534A_SERIES_ID	\
	अणु USB_DEVICE(0x2c42, 0x1602) पूर्ण,	/* In-Box 2 port UART device */	\
	अणु USB_DEVICE(0x2c42, 0x1604) पूर्ण,	/* In-Box 4 port UART device */	\
	अणु USB_DEVICE(0x2c42, 0x1605) पूर्ण,	/* In-Box 8 port UART device */	\
	अणु USB_DEVICE(0x2c42, 0x1606) पूर्ण,	/* In-Box 12 port UART device */ \
	अणु USB_DEVICE(0x2c42, 0x1608) पूर्ण,	/* Non-Flash type */ \
	अणु USB_DEVICE(0x2c42, 0x1632) पूर्ण,	/* 2 port UART device */ \
	अणु USB_DEVICE(0x2c42, 0x1634) पूर्ण,	/* 4 port UART device */ \
	अणु USB_DEVICE(0x2c42, 0x1635) पूर्ण,	/* 8 port UART device */ \
	अणु USB_DEVICE(0x2c42, 0x1636) पूर्ण	/* 12 port UART device */

#घोषणा F81534A_CTRL_ID		\
	अणु USB_DEVICE(0x2c42, 0x16f8) पूर्ण	/* Global control device */

अटल स्थिर काष्ठा usb_device_id f81232_id_table[] = अणु
	F81232_ID,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id f81534a_id_table[] = अणु
	F81534A_SERIES_ID,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id f81534a_ctrl_id_table[] = अणु
	F81534A_CTRL_ID,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id combined_id_table[] = अणु
	F81232_ID,
	F81534A_SERIES_ID,
	F81534A_CTRL_ID,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, combined_id_table);

/* Maximum baudrate क्रम F81232 */
#घोषणा F81232_MAX_BAUDRATE		1500000
#घोषणा F81232_DEF_BAUDRATE		9600

/* USB Control EP parameter */
#घोषणा F81232_REGISTER_REQUEST		0xa0
#घोषणा F81232_GET_REGISTER		0xc0
#घोषणा F81232_SET_REGISTER		0x40
#घोषणा F81534A_ACCESS_REG_RETRY	2

#घोषणा SERIAL_BASE_ADDRESS		0x0120
#घोषणा RECEIVE_BUFFER_REGISTER		(0x00 + SERIAL_BASE_ADDRESS)
#घोषणा INTERRUPT_ENABLE_REGISTER	(0x01 + SERIAL_BASE_ADDRESS)
#घोषणा FIFO_CONTROL_REGISTER		(0x02 + SERIAL_BASE_ADDRESS)
#घोषणा LINE_CONTROL_REGISTER		(0x03 + SERIAL_BASE_ADDRESS)
#घोषणा MODEM_CONTROL_REGISTER		(0x04 + SERIAL_BASE_ADDRESS)
#घोषणा LINE_STATUS_REGISTER		(0x05 + SERIAL_BASE_ADDRESS)
#घोषणा MODEM_STATUS_REGISTER		(0x06 + SERIAL_BASE_ADDRESS)

/*
 * F81232 Clock रेजिस्टरs (106h)
 *
 * Bit1-0:	Clock source selector
 *			00: 1.846MHz.
 *			01: 18.46MHz.
 *			10: 24MHz.
 *			11: 14.77MHz.
 */
#घोषणा F81232_CLK_REGISTER		0x106
#घोषणा F81232_CLK_1_846_MHZ		0
#घोषणा F81232_CLK_18_46_MHZ		BIT(0)
#घोषणा F81232_CLK_24_MHZ		BIT(1)
#घोषणा F81232_CLK_14_77_MHZ		(BIT(1) | BIT(0))
#घोषणा F81232_CLK_MASK			GENMASK(1, 0)

#घोषणा F81534A_MODE_REG		0x107
#घोषणा F81534A_TRIGGER_MASK		GENMASK(3, 2)
#घोषणा F81534A_TRIGGER_MULTIPLE_4X	BIT(3)
#घोषणा F81534A_FIFO_128BYTE		(BIT(1) | BIT(0))

/* Serial port self GPIO control, 2bytes [control&output data][input data] */
#घोषणा F81534A_GPIO_REG		0x10e
#घोषणा F81534A_GPIO_MODE2_सूची		BIT(6) /* 1: input, 0: output */
#घोषणा F81534A_GPIO_MODE1_सूची		BIT(5)
#घोषणा F81534A_GPIO_MODE0_सूची		BIT(4)
#घोषणा F81534A_GPIO_MODE2_OUTPUT	BIT(2)
#घोषणा F81534A_GPIO_MODE1_OUTPUT	BIT(1)
#घोषणा F81534A_GPIO_MODE0_OUTPUT	BIT(0)

#घोषणा F81534A_CTRL_CMD_ENABLE_PORT	0x116

काष्ठा f81232_निजी अणु
	काष्ठा mutex lock;
	u8 modem_control;
	u8 modem_status;
	u8 shaकरोw_lcr;
	speed_t baud_base;
	काष्ठा work_काष्ठा lsr_work;
	काष्ठा work_काष्ठा पूर्णांकerrupt_work;
	काष्ठा usb_serial_port *port;
पूर्ण;

अटल u32 स्थिर baudrate_table[] = अणु 115200, 921600, 1152000, 1500000 पूर्ण;
अटल u8 स्थिर घड़ी_प्रकारable[] = अणु F81232_CLK_1_846_MHZ, F81232_CLK_14_77_MHZ,
				F81232_CLK_18_46_MHZ, F81232_CLK_24_MHZ पूर्ण;

अटल पूर्णांक calc_baud_भागisor(speed_t baudrate, speed_t घड़ीrate)
अणु
	अगर (!baudrate)
		वापस 0;

	वापस DIV_ROUND_CLOSEST(घड़ीrate, baudrate);
पूर्ण

अटल पूर्णांक f81232_get_रेजिस्टर(काष्ठा usb_serial_port *port, u16 reg, u8 *val)
अणु
	पूर्णांक status;
	u8 *पंचांगp;
	काष्ठा usb_device *dev = port->serial->dev;

	पंचांगp = kदो_स्मृति(माप(*val), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	status = usb_control_msg(dev,
				usb_rcvctrlpipe(dev, 0),
				F81232_REGISTER_REQUEST,
				F81232_GET_REGISTER,
				reg,
				0,
				पंचांगp,
				माप(*val),
				USB_CTRL_GET_TIMEOUT);
	अगर (status != माप(*val)) अणु
		dev_err(&port->dev, "%s failed status: %d\n", __func__, status);

		अगर (status < 0)
			status = usb_translate_errors(status);
		अन्यथा
			status = -EIO;
	पूर्ण अन्यथा अणु
		status = 0;
		*val = *पंचांगp;
	पूर्ण

	kमुक्त(पंचांगp);
	वापस status;
पूर्ण

अटल पूर्णांक f81232_set_रेजिस्टर(काष्ठा usb_serial_port *port, u16 reg, u8 val)
अणु
	पूर्णांक status;
	u8 *पंचांगp;
	काष्ठा usb_device *dev = port->serial->dev;

	पंचांगp = kदो_स्मृति(माप(val), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	*पंचांगp = val;

	status = usb_control_msg(dev,
				usb_sndctrlpipe(dev, 0),
				F81232_REGISTER_REQUEST,
				F81232_SET_REGISTER,
				reg,
				0,
				पंचांगp,
				माप(val),
				USB_CTRL_SET_TIMEOUT);
	अगर (status < 0) अणु
		dev_err(&port->dev, "%s failed status: %d\n", __func__, status);
		status = usb_translate_errors(status);
	पूर्ण अन्यथा अणु
		status = 0;
	पूर्ण

	kमुक्त(पंचांगp);
	वापस status;
पूर्ण

अटल पूर्णांक f81232_set_mask_रेजिस्टर(काष्ठा usb_serial_port *port, u16 reg,
					u8 mask, u8 val)
अणु
	पूर्णांक status;
	u8 पंचांगp;

	status = f81232_get_रेजिस्टर(port, reg, &पंचांगp);
	अगर (status)
		वापस status;

	पंचांगp = (पंचांगp & ~mask) | (val & mask);

	वापस f81232_set_रेजिस्टर(port, reg, पंचांगp);
पूर्ण

अटल व्योम f81232_पढ़ो_msr(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक status;
	u8 current_msr;
	काष्ठा tty_काष्ठा *tty;
	काष्ठा f81232_निजी *priv = usb_get_serial_port_data(port);

	mutex_lock(&priv->lock);
	status = f81232_get_रेजिस्टर(port, MODEM_STATUS_REGISTER,
			&current_msr);
	अगर (status) अणु
		dev_err(&port->dev, "%s fail, status: %d\n", __func__, status);
		mutex_unlock(&priv->lock);
		वापस;
	पूर्ण

	अगर (!(current_msr & UART_MSR_ANY_DELTA)) अणु
		mutex_unlock(&priv->lock);
		वापस;
	पूर्ण

	priv->modem_status = current_msr;

	अगर (current_msr & UART_MSR_DCTS)
		port->icount.cts++;
	अगर (current_msr & UART_MSR_DDSR)
		port->icount.dsr++;
	अगर (current_msr & UART_MSR_TERI)
		port->icount.rng++;
	अगर (current_msr & UART_MSR_DDCD) अणु
		port->icount.dcd++;
		tty = tty_port_tty_get(&port->port);
		अगर (tty) अणु
			usb_serial_handle_dcd_change(port, tty,
					current_msr & UART_MSR_DCD);

			tty_kref_put(tty);
		पूर्ण
	पूर्ण

	wake_up_पूर्णांकerruptible(&port->port.delta_msr_रुको);
	mutex_unlock(&priv->lock);
पूर्ण

अटल पूर्णांक f81232_set_mctrl(काष्ठा usb_serial_port *port,
					   अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	u8 val;
	पूर्णांक status;
	काष्ठा f81232_निजी *priv = usb_get_serial_port_data(port);

	अगर (((set | clear) & (TIOCM_DTR | TIOCM_RTS)) == 0)
		वापस 0;	/* no change */

	/* 'set' takes precedence over 'clear' */
	clear &= ~set;

	/* क्रमce enable पूर्णांकerrupt with OUT2 */
	mutex_lock(&priv->lock);
	val = UART_MCR_OUT2 | priv->modem_control;

	अगर (clear & TIOCM_DTR)
		val &= ~UART_MCR_DTR;

	अगर (clear & TIOCM_RTS)
		val &= ~UART_MCR_RTS;

	अगर (set & TIOCM_DTR)
		val |= UART_MCR_DTR;

	अगर (set & TIOCM_RTS)
		val |= UART_MCR_RTS;

	dev_dbg(&port->dev, "%s new:%02x old:%02x\n", __func__,
			val, priv->modem_control);

	status = f81232_set_रेजिस्टर(port, MODEM_CONTROL_REGISTER, val);
	अगर (status) अणु
		dev_err(&port->dev, "%s set MCR status < 0\n", __func__);
		mutex_unlock(&priv->lock);
		वापस status;
	पूर्ण

	priv->modem_control = val;
	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल व्योम f81232_update_line_status(काष्ठा usb_serial_port *port,
				      अचिन्हित अक्षर *data,
				      माप_प्रकार actual_length)
अणु
	काष्ठा f81232_निजी *priv = usb_get_serial_port_data(port);

	अगर (!actual_length)
		वापस;

	चयन (data[0] & 0x07) अणु
	हाल 0x00: /* msr change */
		dev_dbg(&port->dev, "IIR: MSR Change: %02x\n", data[0]);
		schedule_work(&priv->पूर्णांकerrupt_work);
		अवरोध;
	हाल 0x02: /* tx-empty */
		अवरोध;
	हाल 0x04: /* rx data available */
		अवरोध;
	हाल 0x06: /* lsr change */
		/* we can क्रमget it. the LSR will पढ़ो from bulk-in */
		dev_dbg(&port->dev, "IIR: LSR Change: %02x\n", data[0]);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम f81232_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port =  urb->context;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	अचिन्हित पूर्णांक actual_length = urb->actual_length;
	पूर्णांक status = urb->status;
	पूर्णांक retval;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
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
		जाओ निकास;
	पूर्ण

	usb_serial_debug_data(&port->dev, __func__,
			      urb->actual_length, urb->transfer_buffer);

	f81232_update_line_status(port, data, actual_length);

निकास:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&urb->dev->dev,
			"%s - usb_submit_urb failed with result %d\n",
			__func__, retval);
पूर्ण

अटल अक्षर f81232_handle_lsr(काष्ठा usb_serial_port *port, u8 lsr)
अणु
	काष्ठा f81232_निजी *priv = usb_get_serial_port_data(port);
	अक्षर tty_flag = TTY_NORMAL;

	अगर (!(lsr & UART_LSR_BRK_ERROR_BITS))
		वापस tty_flag;

	अगर (lsr & UART_LSR_BI) अणु
		tty_flag = TTY_BREAK;
		port->icount.brk++;
		usb_serial_handle_अवरोध(port);
	पूर्ण अन्यथा अगर (lsr & UART_LSR_PE) अणु
		tty_flag = TTY_PARITY;
		port->icount.parity++;
	पूर्ण अन्यथा अगर (lsr & UART_LSR_FE) अणु
		tty_flag = TTY_FRAME;
		port->icount.frame++;
	पूर्ण

	अगर (lsr & UART_LSR_OE) अणु
		port->icount.overrun++;
		schedule_work(&priv->lsr_work);
		tty_insert_flip_अक्षर(&port->port, 0, TTY_OVERRUN);
	पूर्ण

	वापस tty_flag;
पूर्ण

अटल व्योम f81232_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	अक्षर tty_flag;
	अचिन्हित पूर्णांक i;
	u8 lsr;

	/*
	 * When खोलोing the port we get a 1-byte packet with the current LSR,
	 * which we discard.
	 */
	अगर ((urb->actual_length < 2) || (urb->actual_length % 2))
		वापस;

	/* bulk-in data: [LSR(1Byte)+DATA(1Byte)][LSR(1Byte)+DATA(1Byte)]... */

	क्रम (i = 0; i < urb->actual_length; i += 2) अणु
		lsr = data[i];
		tty_flag = f81232_handle_lsr(port, lsr);

		अगर (port->sysrq) अणु
			अगर (usb_serial_handle_sysrq_अक्षर(port, data[i + 1]))
				जारी;
		पूर्ण

		tty_insert_flip_अक्षर(&port->port, data[i + 1], tty_flag);
	पूर्ण

	tty_flip_buffer_push(&port->port);
पूर्ण

अटल व्योम f81534a_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	अक्षर tty_flag;
	अचिन्हित पूर्णांक i;
	u8 lsr;
	u8 len;

	अगर (urb->actual_length < 3) अणु
		dev_err(&port->dev, "short message received: %d\n",
				urb->actual_length);
		वापस;
	पूर्ण

	len = data[0];
	अगर (len != urb->actual_length) अणु
		dev_err(&port->dev, "malformed message received: %d (%d)\n",
				urb->actual_length, len);
		वापस;
	पूर्ण

	/* bulk-in data: [LEN][Data.....][LSR] */
	lsr = data[len - 1];
	tty_flag = f81232_handle_lsr(port, lsr);

	अगर (port->sysrq) अणु
		क्रम (i = 1; i < len - 1; ++i) अणु
			अगर (!usb_serial_handle_sysrq_अक्षर(port, data[i])) अणु
				tty_insert_flip_अक्षर(&port->port, data[i],
						tty_flag);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		tty_insert_flip_string_fixed_flag(&port->port, &data[1],
							tty_flag, len - 2);
	पूर्ण

	tty_flip_buffer_push(&port->port);
पूर्ण

अटल व्योम f81232_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा f81232_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक status;

	mutex_lock(&priv->lock);

	अगर (अवरोध_state)
		priv->shaकरोw_lcr |= UART_LCR_SBC;
	अन्यथा
		priv->shaकरोw_lcr &= ~UART_LCR_SBC;

	status = f81232_set_रेजिस्टर(port, LINE_CONTROL_REGISTER,
					priv->shaकरोw_lcr);
	अगर (status)
		dev_err(&port->dev, "set break failed: %d\n", status);

	mutex_unlock(&priv->lock);
पूर्ण

अटल पूर्णांक f81232_find_clk(speed_t baudrate)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < ARRAY_SIZE(baudrate_table); ++idx) अणु
		अगर (baudrate <= baudrate_table[idx] &&
				baudrate_table[idx] % baudrate == 0)
			वापस idx;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम f81232_set_baudrate(काष्ठा tty_काष्ठा *tty,
				काष्ठा usb_serial_port *port, speed_t baudrate,
				speed_t old_baudrate)
अणु
	काष्ठा f81232_निजी *priv = usb_get_serial_port_data(port);
	u8 lcr;
	पूर्णांक भागisor;
	पूर्णांक status = 0;
	पूर्णांक i;
	पूर्णांक idx;
	speed_t baud_list[] = अणु baudrate, old_baudrate, F81232_DEF_BAUDRATE पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(baud_list); ++i) अणु
		idx = f81232_find_clk(baud_list[i]);
		अगर (idx >= 0) अणु
			baudrate = baud_list[i];
			tty_encode_baud_rate(tty, baudrate, baudrate);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (idx < 0)
		वापस;

	priv->baud_base = baudrate_table[idx];
	भागisor = calc_baud_भागisor(baudrate, priv->baud_base);

	status = f81232_set_mask_रेजिस्टर(port, F81232_CLK_REGISTER,
			F81232_CLK_MASK, घड़ी_प्रकारable[idx]);
	अगर (status) अणु
		dev_err(&port->dev, "%s failed to set CLK_REG: %d\n",
			__func__, status);
		वापस;
	पूर्ण

	status = f81232_get_रेजिस्टर(port, LINE_CONTROL_REGISTER,
			 &lcr); /* get LCR */
	अगर (status) अणु
		dev_err(&port->dev, "%s failed to get LCR: %d\n",
			__func__, status);
		वापस;
	पूर्ण

	status = f81232_set_रेजिस्टर(port, LINE_CONTROL_REGISTER,
			 lcr | UART_LCR_DLAB); /* Enable DLAB */
	अगर (status) अणु
		dev_err(&port->dev, "%s failed to set DLAB: %d\n",
			__func__, status);
		वापस;
	पूर्ण

	status = f81232_set_रेजिस्टर(port, RECEIVE_BUFFER_REGISTER,
			 भागisor & 0x00ff); /* low */
	अगर (status) अणु
		dev_err(&port->dev, "%s failed to set baudrate MSB: %d\n",
			__func__, status);
		जाओ reapply_lcr;
	पूर्ण

	status = f81232_set_रेजिस्टर(port, INTERRUPT_ENABLE_REGISTER,
			 (भागisor & 0xff00) >> 8); /* high */
	अगर (status) अणु
		dev_err(&port->dev, "%s failed to set baudrate LSB: %d\n",
			__func__, status);
	पूर्ण

reapply_lcr:
	status = f81232_set_रेजिस्टर(port, LINE_CONTROL_REGISTER,
			lcr & ~UART_LCR_DLAB);
	अगर (status) अणु
		dev_err(&port->dev, "%s failed to set DLAB: %d\n",
			__func__, status);
	पूर्ण
पूर्ण

अटल पूर्णांक f81232_port_enable(काष्ठा usb_serial_port *port)
अणु
	u8 val;
	पूर्णांक status;

	/* fअगरo on, trigger8, clear TX/RX*/
	val = UART_FCR_TRIGGER_8 | UART_FCR_ENABLE_FIFO | UART_FCR_CLEAR_RCVR |
			UART_FCR_CLEAR_XMIT;

	status = f81232_set_रेजिस्टर(port, FIFO_CONTROL_REGISTER, val);
	अगर (status) अणु
		dev_err(&port->dev, "%s failed to set FCR: %d\n",
			__func__, status);
		वापस status;
	पूर्ण

	/* MSR Interrupt only, LSR will पढ़ो from Bulk-in odd byte */
	status = f81232_set_रेजिस्टर(port, INTERRUPT_ENABLE_REGISTER,
			UART_IER_MSI);
	अगर (status) अणु
		dev_err(&port->dev, "%s failed to set IER: %d\n",
			__func__, status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक f81232_port_disable(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक status;

	status = f81232_set_रेजिस्टर(port, INTERRUPT_ENABLE_REGISTER, 0);
	अगर (status) अणु
		dev_err(&port->dev, "%s failed to set IER: %d\n",
			__func__, status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम f81232_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा f81232_निजी *priv = usb_get_serial_port_data(port);
	u8 new_lcr = 0;
	पूर्णांक status = 0;
	speed_t baudrate;
	speed_t old_baud;

	/* Don't change anything अगर nothing has changed */
	अगर (old_termios && !tty_termios_hw_change(&tty->termios, old_termios))
		वापस;

	अगर (C_BAUD(tty) == B0)
		f81232_set_mctrl(port, 0, TIOCM_DTR | TIOCM_RTS);
	अन्यथा अगर (old_termios && (old_termios->c_cflag & CBAUD) == B0)
		f81232_set_mctrl(port, TIOCM_DTR | TIOCM_RTS, 0);

	baudrate = tty_get_baud_rate(tty);
	अगर (baudrate > 0) अणु
		अगर (old_termios)
			old_baud = tty_termios_baud_rate(old_termios);
		अन्यथा
			old_baud = F81232_DEF_BAUDRATE;

		f81232_set_baudrate(tty, port, baudrate, old_baud);
	पूर्ण

	अगर (C_PARENB(tty)) अणु
		new_lcr |= UART_LCR_PARITY;

		अगर (!C_PARODD(tty))
			new_lcr |= UART_LCR_EPAR;

		अगर (C_CMSPAR(tty))
			new_lcr |= UART_LCR_SPAR;
	पूर्ण

	अगर (C_CSTOPB(tty))
		new_lcr |= UART_LCR_STOP;

	चयन (C_CSIZE(tty)) अणु
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

	mutex_lock(&priv->lock);

	new_lcr |= (priv->shaकरोw_lcr & UART_LCR_SBC);
	status = f81232_set_रेजिस्टर(port, LINE_CONTROL_REGISTER, new_lcr);
	अगर (status) अणु
		dev_err(&port->dev, "%s failed to set LCR: %d\n",
			__func__, status);
	पूर्ण

	priv->shaकरोw_lcr = new_lcr;

	mutex_unlock(&priv->lock);
पूर्ण

अटल पूर्णांक f81232_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक r;
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा f81232_निजी *port_priv = usb_get_serial_port_data(port);
	u8 mcr, msr;

	/* क्रमce get current MSR changed state */
	f81232_पढ़ो_msr(port);

	mutex_lock(&port_priv->lock);
	mcr = port_priv->modem_control;
	msr = port_priv->modem_status;
	mutex_unlock(&port_priv->lock);

	r = (mcr & UART_MCR_DTR ? TIOCM_DTR : 0) |
		(mcr & UART_MCR_RTS ? TIOCM_RTS : 0) |
		(msr & UART_MSR_CTS ? TIOCM_CTS : 0) |
		(msr & UART_MSR_DCD ? TIOCM_CAR : 0) |
		(msr & UART_MSR_RI ? TIOCM_RI : 0) |
		(msr & UART_MSR_DSR ? TIOCM_DSR : 0);

	वापस r;
पूर्ण

अटल पूर्णांक f81232_tiocmset(काष्ठा tty_काष्ठा *tty,
			अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	वापस f81232_set_mctrl(port, set, clear);
पूर्ण

अटल पूर्णांक f81232_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	पूर्णांक result;

	result = f81232_port_enable(port);
	अगर (result)
		वापस result;

	/* Setup termios */
	अगर (tty)
		f81232_set_termios(tty, port, शून्य);

	result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
	अगर (result) अणु
		dev_err(&port->dev, "%s - failed submitting interrupt urb,"
			" error %d\n", __func__, result);
		वापस result;
	पूर्ण

	result = usb_serial_generic_खोलो(tty, port);
	अगर (result) अणु
		usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक f81534a_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	पूर्णांक status;
	u8 mask;
	u8 val;

	val = F81534A_TRIGGER_MULTIPLE_4X | F81534A_FIFO_128BYTE;
	mask = F81534A_TRIGGER_MASK | F81534A_FIFO_128BYTE;

	status = f81232_set_mask_रेजिस्टर(port, F81534A_MODE_REG, mask, val);
	अगर (status) अणु
		dev_err(&port->dev, "failed to set MODE_REG: %d\n", status);
		वापस status;
	पूर्ण

	वापस f81232_खोलो(tty, port);
पूर्ण

अटल व्योम f81232_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा f81232_निजी *port_priv = usb_get_serial_port_data(port);

	f81232_port_disable(port);
	usb_serial_generic_बंद(port);
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
	flush_work(&port_priv->पूर्णांकerrupt_work);
	flush_work(&port_priv->lsr_work);
पूर्ण

अटल व्योम f81232_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	अगर (on)
		f81232_set_mctrl(port, TIOCM_DTR | TIOCM_RTS, 0);
	अन्यथा
		f81232_set_mctrl(port, 0, TIOCM_DTR | TIOCM_RTS);
पूर्ण

अटल bool f81232_tx_empty(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक status;
	u8 पंचांगp;

	status = f81232_get_रेजिस्टर(port, LINE_STATUS_REGISTER, &पंचांगp);
	अगर (!status) अणु
		अगर ((पंचांगp & UART_LSR_TEMT) != UART_LSR_TEMT)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक f81232_carrier_उठाओd(काष्ठा usb_serial_port *port)
अणु
	u8 msr;
	काष्ठा f81232_निजी *priv = usb_get_serial_port_data(port);

	mutex_lock(&priv->lock);
	msr = priv->modem_status;
	mutex_unlock(&priv->lock);

	अगर (msr & UART_MSR_DCD)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम f81232_get_serial(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा f81232_निजी *priv = usb_get_serial_port_data(port);

	ss->baud_base = priv->baud_base;
पूर्ण

अटल व्योम  f81232_पूर्णांकerrupt_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा f81232_निजी *priv =
		container_of(work, काष्ठा f81232_निजी, पूर्णांकerrupt_work);

	f81232_पढ़ो_msr(priv->port);
पूर्ण

अटल व्योम f81232_lsr_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा f81232_निजी *priv;
	काष्ठा usb_serial_port *port;
	पूर्णांक status;
	u8 पंचांगp;

	priv = container_of(work, काष्ठा f81232_निजी, lsr_work);
	port = priv->port;

	status = f81232_get_रेजिस्टर(port, LINE_STATUS_REGISTER, &पंचांगp);
	अगर (status)
		dev_warn(&port->dev, "read LSR failed: %d\n", status);
पूर्ण

अटल पूर्णांक f81534a_ctrl_set_रेजिस्टर(काष्ठा usb_पूर्णांकerface *पूर्णांकf, u16 reg,
					u16 size, व्योम *val)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्णांक retry = F81534A_ACCESS_REG_RETRY;
	पूर्णांक status;
	u8 *पंचांगp;

	पंचांगp = kmemdup(val, size, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	जबतक (retry--) अणु
		status = usb_control_msg(dev,
					usb_sndctrlpipe(dev, 0),
					F81232_REGISTER_REQUEST,
					F81232_SET_REGISTER,
					reg,
					0,
					पंचांगp,
					size,
					USB_CTRL_SET_TIMEOUT);
		अगर (status < 0) अणु
			status = usb_translate_errors(status);
			अगर (status == -EIO)
				जारी;
		पूर्ण अन्यथा अणु
			status = 0;
		पूर्ण

		अवरोध;
	पूर्ण

	अगर (status) अणु
		dev_err(&पूर्णांकf->dev, "failed to set register 0x%x: %d\n",
				reg, status);
	पूर्ण

	kमुक्त(पंचांगp);
	वापस status;
पूर्ण

अटल पूर्णांक f81534a_ctrl_enable_all_ports(काष्ठा usb_पूर्णांकerface *पूर्णांकf, bool en)
अणु
	अचिन्हित अक्षर enable[2] = अणु0पूर्ण;
	पूर्णांक status;

	/*
	 * Enable all available serial ports, define as following:
	 * bit 15	: Reset behavior (when HUB got soft reset)
	 *			0: मुख्यtain all serial port enabled state.
	 *			1: disable all serial port.
	 * bit 0~11	: Serial port enable bit.
	 */
	अगर (en) अणु
		enable[0] = 0xff;
		enable[1] = 0x8f;
	पूर्ण

	status = f81534a_ctrl_set_रेजिस्टर(पूर्णांकf, F81534A_CTRL_CMD_ENABLE_PORT,
			माप(enable), enable);
	अगर (status)
		dev_err(&पूर्णांकf->dev, "failed to enable ports: %d\n", status);

	वापस status;
पूर्ण

अटल पूर्णांक f81534a_ctrl_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				स्थिर काष्ठा usb_device_id *id)
अणु
	वापस f81534a_ctrl_enable_all_ports(पूर्णांकf, true);
पूर्ण

अटल व्योम f81534a_ctrl_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	f81534a_ctrl_enable_all_ports(पूर्णांकf, false);
पूर्ण

अटल पूर्णांक f81534a_ctrl_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस f81534a_ctrl_enable_all_ports(पूर्णांकf, true);
पूर्ण

अटल पूर्णांक f81232_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा f81232_निजी *priv;

	priv = devm_kzalloc(&port->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_init(&priv->lock);
	INIT_WORK(&priv->पूर्णांकerrupt_work,  f81232_पूर्णांकerrupt_work);
	INIT_WORK(&priv->lsr_work, f81232_lsr_worker);

	usb_set_serial_port_data(port, priv);

	priv->port = port;

	वापस 0;
पूर्ण

अटल पूर्णांक f81534a_port_probe(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक status;

	/* tri-state with pull-high, शेष RS232 Mode */
	status = f81232_set_रेजिस्टर(port, F81534A_GPIO_REG,
					F81534A_GPIO_MODE2_सूची);
	अगर (status)
		वापस status;

	वापस f81232_port_probe(port);
पूर्ण

अटल पूर्णांक f81232_suspend(काष्ठा usb_serial *serial, pm_message_t message)
अणु
	काष्ठा usb_serial_port *port = serial->port[0];
	काष्ठा f81232_निजी *port_priv = usb_get_serial_port_data(port);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(port->पढ़ो_urbs); ++i)
		usb_समाप्त_urb(port->पढ़ो_urbs[i]);

	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);

	अगर (port_priv) अणु
		flush_work(&port_priv->पूर्णांकerrupt_work);
		flush_work(&port_priv->lsr_work);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक f81232_resume(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_serial_port *port = serial->port[0];
	पूर्णांक result;

	अगर (tty_port_initialized(&port->port)) अणु
		result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_NOIO);
		अगर (result) अणु
			dev_err(&port->dev, "submit interrupt urb failed: %d\n",
					result);
			वापस result;
		पूर्ण
	पूर्ण

	वापस usb_serial_generic_resume(serial);
पूर्ण

अटल काष्ठा usb_serial_driver f81232_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"f81232",
	पूर्ण,
	.id_table =		f81232_id_table,
	.num_ports =		1,
	.bulk_in_size =		256,
	.bulk_out_size =	256,
	.खोलो =			f81232_खोलो,
	.बंद =		f81232_बंद,
	.dtr_rts =		f81232_dtr_rts,
	.carrier_उठाओd =	f81232_carrier_उठाओd,
	.get_serial =		f81232_get_serial,
	.अवरोध_ctl =		f81232_अवरोध_ctl,
	.set_termios =		f81232_set_termios,
	.tiocmget =		f81232_tiocmget,
	.tiocmset =		f81232_tiocmset,
	.tiocmiरुको =		usb_serial_generic_tiocmiरुको,
	.tx_empty =		f81232_tx_empty,
	.process_पढ़ो_urb =	f81232_process_पढ़ो_urb,
	.पढ़ो_पूर्णांक_callback =	f81232_पढ़ो_पूर्णांक_callback,
	.port_probe =		f81232_port_probe,
	.suspend =		f81232_suspend,
	.resume =		f81232_resume,
पूर्ण;

अटल काष्ठा usb_serial_driver f81534a_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"f81534a",
	पूर्ण,
	.id_table =		f81534a_id_table,
	.num_ports =		1,
	.खोलो =			f81534a_खोलो,
	.बंद =		f81232_बंद,
	.dtr_rts =		f81232_dtr_rts,
	.carrier_उठाओd =	f81232_carrier_उठाओd,
	.get_serial =		f81232_get_serial,
	.अवरोध_ctl =		f81232_अवरोध_ctl,
	.set_termios =		f81232_set_termios,
	.tiocmget =		f81232_tiocmget,
	.tiocmset =		f81232_tiocmset,
	.tiocmiरुको =		usb_serial_generic_tiocmiरुको,
	.tx_empty =		f81232_tx_empty,
	.process_पढ़ो_urb =	f81534a_process_पढ़ो_urb,
	.पढ़ो_पूर्णांक_callback =	f81232_पढ़ो_पूर्णांक_callback,
	.port_probe =		f81534a_port_probe,
	.suspend =		f81232_suspend,
	.resume =		f81232_resume,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&f81232_device,
	&f81534a_device,
	शून्य,
पूर्ण;

अटल काष्ठा usb_driver f81534a_ctrl_driver = अणु
	.name =		"f81534a_ctrl",
	.id_table =	f81534a_ctrl_id_table,
	.probe =	f81534a_ctrl_probe,
	.disconnect =	f81534a_ctrl_disconnect,
	.resume =	f81534a_ctrl_resume,
पूर्ण;

अटल पूर्णांक __init f81232_init(व्योम)
अणु
	पूर्णांक status;

	status = usb_रेजिस्टर_driver(&f81534a_ctrl_driver, THIS_MODULE,
			KBUILD_MODNAME);
	अगर (status)
		वापस status;

	status = usb_serial_रेजिस्टर_drivers(serial_drivers, KBUILD_MODNAME,
			combined_id_table);
	अगर (status) अणु
		usb_deरेजिस्टर(&f81534a_ctrl_driver);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास f81232_निकास(व्योम)
अणु
	usb_serial_deरेजिस्टर_drivers(serial_drivers);
	usb_deरेजिस्टर(&f81534a_ctrl_driver);
पूर्ण

module_init(f81232_init);
module_निकास(f81232_निकास);

MODULE_DESCRIPTION("Fintek F81232/532A/534A/535/536 USB to serial driver");
MODULE_AUTHOR("Greg Kroah-Hartman <gregkh@linuxfoundation.org>");
MODULE_AUTHOR("Peter Hong <peter_hong@fintek.com.tw>");
MODULE_LICENSE("GPL v2");
