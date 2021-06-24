<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * MaxLinear/Exar USB to Serial driver
 *
 * Copyright (c) 2020 Manivannan Sadhasivam <mani@kernel.org>
 * Copyright (c) 2021 Johan Hovold <johan@kernel.org>
 *
 * Based on the initial driver written by Patong Yang:
 *
 *   https://lore.kernel.org/r/20180404070634.nhspvmxcjwfgjkcv@advantechmxl-desktop
 *
 *   Copyright (c) 2018 Patong Yang <patong.mxl@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/usb/serial.h>

काष्ठा xr_txrx_clk_mask अणु
	u16 tx;
	u16 rx0;
	u16 rx1;
पूर्ण;

#घोषणा XR_INT_OSC_HZ			48000000U
#घोषणा XR21V141X_MIN_SPEED		46U
#घोषणा XR21V141X_MAX_SPEED		XR_INT_OSC_HZ

/* XR21V141X रेजिस्टर blocks */
#घोषणा XR21V141X_UART_REG_BLOCK	0
#घोषणा XR21V141X_UM_REG_BLOCK		4
#घोषणा XR21V141X_UART_CUSTOM_BLOCK	0x66

/* XR21V141X UART रेजिस्टरs */
#घोषणा XR21V141X_CLOCK_DIVISOR_0	0x04
#घोषणा XR21V141X_CLOCK_DIVISOR_1	0x05
#घोषणा XR21V141X_CLOCK_DIVISOR_2	0x06
#घोषणा XR21V141X_TX_CLOCK_MASK_0	0x07
#घोषणा XR21V141X_TX_CLOCK_MASK_1	0x08
#घोषणा XR21V141X_RX_CLOCK_MASK_0	0x09
#घोषणा XR21V141X_RX_CLOCK_MASK_1	0x0a
#घोषणा XR21V141X_REG_FORMAT		0x0b

/* XR21V141X UART Manager रेजिस्टरs */
#घोषणा XR21V141X_UM_FIFO_ENABLE_REG	0x10
#घोषणा XR21V141X_UM_ENABLE_TX_FIFO	0x01
#घोषणा XR21V141X_UM_ENABLE_RX_FIFO	0x02

#घोषणा XR21V141X_UM_RX_FIFO_RESET	0x18
#घोषणा XR21V141X_UM_TX_FIFO_RESET	0x1c

#घोषणा XR_UART_ENABLE_TX		0x1
#घोषणा XR_UART_ENABLE_RX		0x2

#घोषणा XR_GPIO_RI			BIT(0)
#घोषणा XR_GPIO_CD			BIT(1)
#घोषणा XR_GPIO_DSR			BIT(2)
#घोषणा XR_GPIO_DTR			BIT(3)
#घोषणा XR_GPIO_CTS			BIT(4)
#घोषणा XR_GPIO_RTS			BIT(5)
#घोषणा XR_GPIO_CLK			BIT(6)
#घोषणा XR_GPIO_XEN			BIT(7)
#घोषणा XR_GPIO_TXT			BIT(8)
#घोषणा XR_GPIO_RXT			BIT(9)

#घोषणा XR_UART_DATA_MASK		GENMASK(3, 0)
#घोषणा XR_UART_DATA_7			0x7
#घोषणा XR_UART_DATA_8			0x8

#घोषणा XR_UART_PARITY_MASK		GENMASK(6, 4)
#घोषणा XR_UART_PARITY_SHIFT		4
#घोषणा XR_UART_PARITY_NONE		(0x0 << XR_UART_PARITY_SHIFT)
#घोषणा XR_UART_PARITY_ODD		(0x1 << XR_UART_PARITY_SHIFT)
#घोषणा XR_UART_PARITY_EVEN		(0x2 <<	XR_UART_PARITY_SHIFT)
#घोषणा XR_UART_PARITY_MARK		(0x3 << XR_UART_PARITY_SHIFT)
#घोषणा XR_UART_PARITY_SPACE		(0x4 << XR_UART_PARITY_SHIFT)

#घोषणा XR_UART_STOP_MASK		BIT(7)
#घोषणा XR_UART_STOP_SHIFT		7
#घोषणा XR_UART_STOP_1			(0x0 << XR_UART_STOP_SHIFT)
#घोषणा XR_UART_STOP_2			(0x1 << XR_UART_STOP_SHIFT)

#घोषणा XR_UART_FLOW_MODE_NONE		0x0
#घोषणा XR_UART_FLOW_MODE_HW		0x1
#घोषणा XR_UART_FLOW_MODE_SW		0x2

#घोषणा XR_GPIO_MODE_SEL_MASK		GENMASK(2, 0)
#घोषणा XR_GPIO_MODE_SEL_RTS_CTS	0x1
#घोषणा XR_GPIO_MODE_SEL_DTR_DSR	0x2
#घोषणा XR_GPIO_MODE_SEL_RS485		0x3
#घोषणा XR_GPIO_MODE_SEL_RS485_ADDR	0x4
#घोषणा XR_GPIO_MODE_TX_TOGGLE		0x100
#घोषणा XR_GPIO_MODE_RX_TOGGLE		0x200

#घोषणा XR_FIFO_RESET			0x1

#घोषणा XR_CUSTOM_DRIVER_ACTIVE		0x1

अटल पूर्णांक xr21v141x_uart_enable(काष्ठा usb_serial_port *port);
अटल पूर्णांक xr21v141x_uart_disable(काष्ठा usb_serial_port *port);
अटल पूर्णांक xr21v141x_fअगरo_reset(काष्ठा usb_serial_port *port);
अटल व्योम xr21v141x_set_line_settings(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios);

काष्ठा xr_type अणु
	पूर्णांक reg_width;
	u8 reg_recipient;
	u8 set_reg;
	u8 get_reg;

	u16 uart_enable;
	u16 flow_control;
	u16 xon_अक्षर;
	u16 xoff_अक्षर;
	u16 tx_अवरोध;
	u16 gpio_mode;
	u16 gpio_direction;
	u16 gpio_set;
	u16 gpio_clear;
	u16 gpio_status;
	u16 tx_fअगरo_reset;
	u16 rx_fअगरo_reset;
	u16 custom_driver;

	bool have_5_6_bit_mode;
	bool have_xmit_toggle;

	पूर्णांक (*enable)(काष्ठा usb_serial_port *port);
	पूर्णांक (*disable)(काष्ठा usb_serial_port *port);
	पूर्णांक (*fअगरo_reset)(काष्ठा usb_serial_port *port);
	व्योम (*set_line_settings)(काष्ठा tty_काष्ठा *tty,
			काष्ठा usb_serial_port *port,
			काष्ठा ktermios *old_termios);
पूर्ण;

क्रमागत xr_type_id अणु
	XR21V141X,
	XR21B142X,
	XR21B1411,
	XR2280X,
	XR_TYPE_COUNT,
पूर्ण;

अटल स्थिर काष्ठा xr_type xr_types[] = अणु
	[XR21V141X] = अणु
		.reg_width	= 8,
		.reg_recipient	= USB_RECIP_DEVICE,
		.set_reg	= 0x00,
		.get_reg	= 0x01,

		.uart_enable	= 0x03,
		.flow_control	= 0x0c,
		.xon_अक्षर	= 0x10,
		.xoff_अक्षर	= 0x11,
		.tx_अवरोध	= 0x14,
		.gpio_mode	= 0x1a,
		.gpio_direction	= 0x1b,
		.gpio_set	= 0x1d,
		.gpio_clear	= 0x1e,
		.gpio_status	= 0x1f,

		.enable			= xr21v141x_uart_enable,
		.disable		= xr21v141x_uart_disable,
		.fअगरo_reset		= xr21v141x_fअगरo_reset,
		.set_line_settings	= xr21v141x_set_line_settings,
	पूर्ण,
	[XR21B142X] = अणु
		.reg_width	= 16,
		.reg_recipient	= USB_RECIP_INTERFACE,
		.set_reg	= 0x00,
		.get_reg	= 0x00,

		.uart_enable	= 0x00,
		.flow_control	= 0x06,
		.xon_अक्षर	= 0x07,
		.xoff_अक्षर	= 0x08,
		.tx_अवरोध	= 0x0a,
		.gpio_mode	= 0x0c,
		.gpio_direction	= 0x0d,
		.gpio_set	= 0x0e,
		.gpio_clear	= 0x0f,
		.gpio_status	= 0x10,
		.tx_fअगरo_reset	= 0x40,
		.rx_fअगरo_reset	= 0x43,
		.custom_driver	= 0x60,

		.have_5_6_bit_mode	= true,
		.have_xmit_toggle	= true,
	पूर्ण,
	[XR21B1411] = अणु
		.reg_width	= 12,
		.reg_recipient	= USB_RECIP_DEVICE,
		.set_reg	= 0x00,
		.get_reg	= 0x01,

		.uart_enable	= 0xc00,
		.flow_control	= 0xc06,
		.xon_अक्षर	= 0xc07,
		.xoff_अक्षर	= 0xc08,
		.tx_अवरोध	= 0xc0a,
		.gpio_mode	= 0xc0c,
		.gpio_direction	= 0xc0d,
		.gpio_set	= 0xc0e,
		.gpio_clear	= 0xc0f,
		.gpio_status	= 0xc10,
		.tx_fअगरo_reset	= 0xc80,
		.rx_fअगरo_reset	= 0xcc0,
		.custom_driver	= 0x20d,
	पूर्ण,
	[XR2280X] = अणु
		.reg_width	= 16,
		.reg_recipient	= USB_RECIP_DEVICE,
		.set_reg	= 0x05,
		.get_reg	= 0x05,

		.uart_enable	= 0x40,
		.flow_control	= 0x46,
		.xon_अक्षर	= 0x47,
		.xoff_अक्षर	= 0x48,
		.tx_अवरोध	= 0x4a,
		.gpio_mode	= 0x4c,
		.gpio_direction	= 0x4d,
		.gpio_set	= 0x4e,
		.gpio_clear	= 0x4f,
		.gpio_status	= 0x50,
		.tx_fअगरo_reset	= 0x60,
		.rx_fअगरo_reset	= 0x63,
		.custom_driver	= 0x81,
	पूर्ण,
पूर्ण;

काष्ठा xr_data अणु
	स्थिर काष्ठा xr_type *type;
	u8 channel;			/* zero-based index or पूर्णांकerface number */
पूर्ण;

अटल पूर्णांक xr_set_reg(काष्ठा usb_serial_port *port, u8 channel, u16 reg, u16 val)
अणु
	काष्ठा xr_data *data = usb_get_serial_port_data(port);
	स्थिर काष्ठा xr_type *type = data->type;
	काष्ठा usb_serial *serial = port->serial;
	पूर्णांक ret;

	ret = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			type->set_reg,
			USB_सूची_OUT | USB_TYPE_VENDOR | type->reg_recipient,
			val, (channel << 8) | reg, शून्य, 0,
			USB_CTRL_SET_TIMEOUT);
	अगर (ret < 0) अणु
		dev_err(&port->dev, "Failed to set reg 0x%02x: %d\n", reg, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xr_get_reg(काष्ठा usb_serial_port *port, u8 channel, u16 reg, u16 *val)
अणु
	काष्ठा xr_data *data = usb_get_serial_port_data(port);
	स्थिर काष्ठा xr_type *type = data->type;
	काष्ठा usb_serial *serial = port->serial;
	u8 *dmabuf;
	पूर्णांक ret, len;

	अगर (type->reg_width == 8)
		len = 1;
	अन्यथा
		len = 2;

	dmabuf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!dmabuf)
		वापस -ENOMEM;

	ret = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
			type->get_reg,
			USB_सूची_IN | USB_TYPE_VENDOR | type->reg_recipient,
			0, (channel << 8) | reg, dmabuf, len,
			USB_CTRL_GET_TIMEOUT);
	अगर (ret == len) अणु
		अगर (len == 2)
			*val = le16_to_cpup((__le16 *)dmabuf);
		अन्यथा
			*val = *dmabuf;
		ret = 0;
	पूर्ण अन्यथा अणु
		dev_err(&port->dev, "Failed to get reg 0x%02x: %d\n", reg, ret);
		अगर (ret >= 0)
			ret = -EIO;
	पूर्ण

	kमुक्त(dmabuf);

	वापस ret;
पूर्ण

अटल पूर्णांक xr_set_reg_uart(काष्ठा usb_serial_port *port, u16 reg, u16 val)
अणु
	काष्ठा xr_data *data = usb_get_serial_port_data(port);

	वापस xr_set_reg(port, data->channel, reg, val);
पूर्ण

अटल पूर्णांक xr_get_reg_uart(काष्ठा usb_serial_port *port, u16 reg, u16 *val)
अणु
	काष्ठा xr_data *data = usb_get_serial_port_data(port);

	वापस xr_get_reg(port, data->channel, reg, val);
पूर्ण

अटल पूर्णांक xr_set_reg_um(काष्ठा usb_serial_port *port, u8 reg_base, u8 val)
अणु
	काष्ठा xr_data *data = usb_get_serial_port_data(port);
	u8 reg;

	reg = reg_base + data->channel;

	वापस xr_set_reg(port, XR21V141X_UM_REG_BLOCK, reg, val);
पूर्ण

अटल पूर्णांक __xr_uart_enable(काष्ठा usb_serial_port *port)
अणु
	काष्ठा xr_data *data = usb_get_serial_port_data(port);

	वापस xr_set_reg_uart(port, data->type->uart_enable,
			XR_UART_ENABLE_TX | XR_UART_ENABLE_RX);
पूर्ण

अटल पूर्णांक __xr_uart_disable(काष्ठा usb_serial_port *port)
अणु
	काष्ठा xr_data *data = usb_get_serial_port_data(port);

	वापस xr_set_reg_uart(port, data->type->uart_enable, 0);
पूर्ण

/*
 * According to datasheet, below is the recommended sequence क्रम enabling UART
 * module in XR21V141X:
 *
 * Enable Tx FIFO
 * Enable Tx and Rx
 * Enable Rx FIFO
 */
अटल पूर्णांक xr21v141x_uart_enable(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक ret;

	ret = xr_set_reg_um(port, XR21V141X_UM_FIFO_ENABLE_REG,
			    XR21V141X_UM_ENABLE_TX_FIFO);
	अगर (ret)
		वापस ret;

	ret = __xr_uart_enable(port);
	अगर (ret)
		वापस ret;

	ret = xr_set_reg_um(port, XR21V141X_UM_FIFO_ENABLE_REG,
			    XR21V141X_UM_ENABLE_TX_FIFO | XR21V141X_UM_ENABLE_RX_FIFO);
	अगर (ret)
		__xr_uart_disable(port);

	वापस ret;
पूर्ण

अटल पूर्णांक xr21v141x_uart_disable(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक ret;

	ret = __xr_uart_disable(port);
	अगर (ret)
		वापस ret;

	ret = xr_set_reg_um(port, XR21V141X_UM_FIFO_ENABLE_REG, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक xr_uart_enable(काष्ठा usb_serial_port *port)
अणु
	काष्ठा xr_data *data = usb_get_serial_port_data(port);

	अगर (data->type->enable)
		वापस data->type->enable(port);

	वापस __xr_uart_enable(port);
पूर्ण

अटल पूर्णांक xr_uart_disable(काष्ठा usb_serial_port *port)
अणु
	काष्ठा xr_data *data = usb_get_serial_port_data(port);

	अगर (data->type->disable)
		वापस data->type->disable(port);

	वापस __xr_uart_disable(port);
पूर्ण

अटल पूर्णांक xr21v141x_fअगरo_reset(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक ret;

	ret = xr_set_reg_um(port, XR21V141X_UM_TX_FIFO_RESET, XR_FIFO_RESET);
	अगर (ret)
		वापस ret;

	ret = xr_set_reg_um(port, XR21V141X_UM_RX_FIFO_RESET, XR_FIFO_RESET);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक xr_fअगरo_reset(काष्ठा usb_serial_port *port)
अणु
	काष्ठा xr_data *data = usb_get_serial_port_data(port);
	पूर्णांक ret;

	अगर (data->type->fअगरo_reset)
		वापस data->type->fअगरo_reset(port);

	ret = xr_set_reg_uart(port, data->type->tx_fअगरo_reset, XR_FIFO_RESET);
	अगर (ret)
		वापस ret;

	ret = xr_set_reg_uart(port, data->type->rx_fअगरo_reset, XR_FIFO_RESET);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक xr_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा xr_data *data = usb_get_serial_port_data(port);
	u16 status;
	पूर्णांक ret;

	ret = xr_get_reg_uart(port, data->type->gpio_status, &status);
	अगर (ret)
		वापस ret;

	/*
	 * Modem control pins are active low, so पढ़ोing '0' means it is active
	 * and '1' means not active.
	 */
	ret = ((status & XR_GPIO_DTR) ? 0 : TIOCM_DTR) |
	      ((status & XR_GPIO_RTS) ? 0 : TIOCM_RTS) |
	      ((status & XR_GPIO_CTS) ? 0 : TIOCM_CTS) |
	      ((status & XR_GPIO_DSR) ? 0 : TIOCM_DSR) |
	      ((status & XR_GPIO_RI) ? 0 : TIOCM_RI) |
	      ((status & XR_GPIO_CD) ? 0 : TIOCM_CD);

	वापस ret;
पूर्ण

अटल पूर्णांक xr_tiocmset_port(काष्ठा usb_serial_port *port,
			    अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा xr_data *data = usb_get_serial_port_data(port);
	स्थिर काष्ठा xr_type *type = data->type;
	u16 gpio_set = 0;
	u16 gpio_clr = 0;
	पूर्णांक ret = 0;

	/* Modem control pins are active low, so set & clr are swapped */
	अगर (set & TIOCM_RTS)
		gpio_clr |= XR_GPIO_RTS;
	अगर (set & TIOCM_DTR)
		gpio_clr |= XR_GPIO_DTR;
	अगर (clear & TIOCM_RTS)
		gpio_set |= XR_GPIO_RTS;
	अगर (clear & TIOCM_DTR)
		gpio_set |= XR_GPIO_DTR;

	/* Writing '0' to gpio_अणुset/clrपूर्ण bits has no effect, so no need to करो */
	अगर (gpio_clr)
		ret = xr_set_reg_uart(port, type->gpio_clear, gpio_clr);

	अगर (gpio_set)
		ret = xr_set_reg_uart(port, type->gpio_set, gpio_set);

	वापस ret;
पूर्ण

अटल पूर्णांक xr_tiocmset(काष्ठा tty_काष्ठा *tty,
		       अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	वापस xr_tiocmset_port(port, set, clear);
पूर्ण

अटल व्योम xr_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	अगर (on)
		xr_tiocmset_port(port, TIOCM_DTR | TIOCM_RTS, 0);
	अन्यथा
		xr_tiocmset_port(port, 0, TIOCM_DTR | TIOCM_RTS);
पूर्ण

अटल व्योम xr_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा xr_data *data = usb_get_serial_port_data(port);
	स्थिर काष्ठा xr_type *type = data->type;
	u16 state;

	अगर (अवरोध_state == 0)
		state = 0;
	अन्यथा
		state = GENMASK(type->reg_width - 1, 0);

	dev_dbg(&port->dev, "Turning break %s\n", state == 0 ? "off" : "on");

	xr_set_reg_uart(port, type->tx_अवरोध, state);
पूर्ण

/* Tx and Rx घड़ी mask values obtained from section 3.3.4 of datasheet */
अटल स्थिर काष्ठा xr_txrx_clk_mask xr21v141x_txrx_clk_masks[] = अणु
	अणु 0x000, 0x000, 0x000 पूर्ण,
	अणु 0x000, 0x000, 0x000 पूर्ण,
	अणु 0x100, 0x000, 0x100 पूर्ण,
	अणु 0x020, 0x400, 0x020 पूर्ण,
	अणु 0x010, 0x100, 0x010 पूर्ण,
	अणु 0x208, 0x040, 0x208 पूर्ण,
	अणु 0x104, 0x820, 0x108 पूर्ण,
	अणु 0x844, 0x210, 0x884 पूर्ण,
	अणु 0x444, 0x110, 0x444 पूर्ण,
	अणु 0x122, 0x888, 0x224 पूर्ण,
	अणु 0x912, 0x448, 0x924 पूर्ण,
	अणु 0x492, 0x248, 0x492 पूर्ण,
	अणु 0x252, 0x928, 0x292 पूर्ण,
	अणु 0x94a, 0x4a4, 0xa52 पूर्ण,
	अणु 0x52a, 0xaa4, 0x54a पूर्ण,
	अणु 0xaaa, 0x954, 0x4aa पूर्ण,
	अणु 0xaaa, 0x554, 0xaaa पूर्ण,
	अणु 0x555, 0xad4, 0x5aa पूर्ण,
	अणु 0xb55, 0xab4, 0x55a पूर्ण,
	अणु 0x6b5, 0x5ac, 0xb56 पूर्ण,
	अणु 0x5b5, 0xd6c, 0x6d6 पूर्ण,
	अणु 0xb6d, 0xb6a, 0xdb6 पूर्ण,
	अणु 0x76d, 0x6da, 0xbb6 पूर्ण,
	अणु 0xedd, 0xdda, 0x76e पूर्ण,
	अणु 0xddd, 0xbba, 0xeee पूर्ण,
	अणु 0x7bb, 0xf7a, 0xdde पूर्ण,
	अणु 0xf7b, 0xef6, 0x7de पूर्ण,
	अणु 0xdf7, 0xbf6, 0xf7e पूर्ण,
	अणु 0x7f7, 0xfee, 0xefe पूर्ण,
	अणु 0xfdf, 0xfbe, 0x7fe पूर्ण,
	अणु 0xf7f, 0xefe, 0xffe पूर्ण,
	अणु 0xfff, 0xffe, 0xffd पूर्ण,
पूर्ण;

अटल पूर्णांक xr21v141x_set_baudrate(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	u32 भागisor, baud, idx;
	u16 tx_mask, rx_mask;
	पूर्णांक ret;

	baud = tty->termios.c_ospeed;
	अगर (!baud)
		वापस 0;

	baud = clamp(baud, XR21V141X_MIN_SPEED, XR21V141X_MAX_SPEED);
	भागisor = XR_INT_OSC_HZ / baud;
	idx = ((32 * XR_INT_OSC_HZ) / baud) & 0x1f;
	tx_mask = xr21v141x_txrx_clk_masks[idx].tx;

	अगर (भागisor & 0x01)
		rx_mask = xr21v141x_txrx_clk_masks[idx].rx1;
	अन्यथा
		rx_mask = xr21v141x_txrx_clk_masks[idx].rx0;

	dev_dbg(&port->dev, "Setting baud rate: %u\n", baud);
	/*
	 * XR21V141X uses fractional baud rate generator with 48MHz पूर्णांकernal
	 * oscillator and 19-bit programmable भागisor. So theoretically it can
	 * generate most commonly used baud rates with high accuracy.
	 */
	ret = xr_set_reg_uart(port, XR21V141X_CLOCK_DIVISOR_0,
			      भागisor & 0xff);
	अगर (ret)
		वापस ret;

	ret = xr_set_reg_uart(port, XR21V141X_CLOCK_DIVISOR_1,
			      (भागisor >>  8) & 0xff);
	अगर (ret)
		वापस ret;

	ret = xr_set_reg_uart(port, XR21V141X_CLOCK_DIVISOR_2,
			      (भागisor >> 16) & 0xff);
	अगर (ret)
		वापस ret;

	ret = xr_set_reg_uart(port, XR21V141X_TX_CLOCK_MASK_0,
			      tx_mask & 0xff);
	अगर (ret)
		वापस ret;

	ret = xr_set_reg_uart(port, XR21V141X_TX_CLOCK_MASK_1,
			      (tx_mask >>  8) & 0xff);
	अगर (ret)
		वापस ret;

	ret = xr_set_reg_uart(port, XR21V141X_RX_CLOCK_MASK_0,
			      rx_mask & 0xff);
	अगर (ret)
		वापस ret;

	ret = xr_set_reg_uart(port, XR21V141X_RX_CLOCK_MASK_1,
			      (rx_mask >>  8) & 0xff);
	अगर (ret)
		वापस ret;

	tty_encode_baud_rate(tty, baud, baud);

	वापस 0;
पूर्ण

अटल व्योम xr_set_flow_mode(काष्ठा tty_काष्ठा *tty,
			     काष्ठा usb_serial_port *port,
			     काष्ठा ktermios *old_termios)
अणु
	काष्ठा xr_data *data = usb_get_serial_port_data(port);
	स्थिर काष्ठा xr_type *type = data->type;
	u16 flow, gpio_mode;
	पूर्णांक ret;

	ret = xr_get_reg_uart(port, type->gpio_mode, &gpio_mode);
	अगर (ret)
		वापस;

	/*
	 * According to the datasheets, the UART needs to be disabled जबतक
	 * writing to the FLOW_CONTROL रेजिस्टर (XR21V141X), or any रेजिस्टर
	 * but GPIO_SET, GPIO_CLEAR, TX_BREAK and ERROR_STATUS (XR21B142X).
	 */
	xr_uart_disable(port);

	/* Set GPIO mode क्रम controlling the pins manually by शेष. */
	gpio_mode &= ~XR_GPIO_MODE_SEL_MASK;

	अगर (C_CRTSCTS(tty) && C_BAUD(tty) != B0) अणु
		dev_dbg(&port->dev, "Enabling hardware flow ctrl\n");
		gpio_mode |= XR_GPIO_MODE_SEL_RTS_CTS;
		flow = XR_UART_FLOW_MODE_HW;
	पूर्ण अन्यथा अगर (I_IXON(tty)) अणु
		u8 start_अक्षर = START_CHAR(tty);
		u8 stop_अक्षर = STOP_CHAR(tty);

		dev_dbg(&port->dev, "Enabling sw flow ctrl\n");
		flow = XR_UART_FLOW_MODE_SW;

		xr_set_reg_uart(port, type->xon_अक्षर, start_अक्षर);
		xr_set_reg_uart(port, type->xoff_अक्षर, stop_अक्षर);
	पूर्ण अन्यथा अणु
		dev_dbg(&port->dev, "Disabling flow ctrl\n");
		flow = XR_UART_FLOW_MODE_NONE;
	पूर्ण

	xr_set_reg_uart(port, type->flow_control, flow);
	xr_set_reg_uart(port, type->gpio_mode, gpio_mode);

	xr_uart_enable(port);

	अगर (C_BAUD(tty) == B0)
		xr_dtr_rts(port, 0);
	अन्यथा अगर (old_termios && (old_termios->c_cflag & CBAUD) == B0)
		xr_dtr_rts(port, 1);
पूर्ण

अटल व्योम xr21v141x_set_line_settings(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा ktermios *termios = &tty->termios;
	u8 bits = 0;
	पूर्णांक ret;

	अगर (!old_termios || (tty->termios.c_ospeed != old_termios->c_ospeed))
		xr21v141x_set_baudrate(tty, port);

	चयन (C_CSIZE(tty)) अणु
	हाल CS5:
	हाल CS6:
		/* CS5 and CS6 are not supported, so just restore old setting */
		termios->c_cflag &= ~CSIZE;
		अगर (old_termios)
			termios->c_cflag |= old_termios->c_cflag & CSIZE;
		अन्यथा
			termios->c_cflag |= CS8;

		अगर (C_CSIZE(tty) == CS7)
			bits |= XR_UART_DATA_7;
		अन्यथा
			bits |= XR_UART_DATA_8;
		अवरोध;
	हाल CS7:
		bits |= XR_UART_DATA_7;
		अवरोध;
	हाल CS8:
	शेष:
		bits |= XR_UART_DATA_8;
		अवरोध;
	पूर्ण

	अगर (C_PARENB(tty)) अणु
		अगर (C_CMSPAR(tty)) अणु
			अगर (C_PARODD(tty))
				bits |= XR_UART_PARITY_MARK;
			अन्यथा
				bits |= XR_UART_PARITY_SPACE;
		पूर्ण अन्यथा अणु
			अगर (C_PARODD(tty))
				bits |= XR_UART_PARITY_ODD;
			अन्यथा
				bits |= XR_UART_PARITY_EVEN;
		पूर्ण
	पूर्ण

	अगर (C_CSTOPB(tty))
		bits |= XR_UART_STOP_2;
	अन्यथा
		bits |= XR_UART_STOP_1;

	ret = xr_set_reg_uart(port, XR21V141X_REG_FORMAT, bits);
	अगर (ret)
		वापस;
पूर्ण

अटल व्योम xr_cdc_set_line_coding(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा xr_data *data = usb_get_serial_port_data(port);
	काष्ठा usb_host_पूर्णांकerface *alt = port->serial->पूर्णांकerface->cur_altsetting;
	काष्ठा usb_device *udev = port->serial->dev;
	काष्ठा usb_cdc_line_coding *lc;
	पूर्णांक ret;

	lc = kzalloc(माप(*lc), GFP_KERNEL);
	अगर (!lc)
		वापस;

	अगर (tty->termios.c_ospeed)
		lc->dwDTERate = cpu_to_le32(tty->termios.c_ospeed);
	अन्यथा अगर (old_termios)
		lc->dwDTERate = cpu_to_le32(old_termios->c_ospeed);
	अन्यथा
		lc->dwDTERate = cpu_to_le32(9600);

	अगर (C_CSTOPB(tty))
		lc->bCharFormat = USB_CDC_2_STOP_BITS;
	अन्यथा
		lc->bCharFormat = USB_CDC_1_STOP_BITS;

	अगर (C_PARENB(tty)) अणु
		अगर (C_CMSPAR(tty)) अणु
			अगर (C_PARODD(tty))
				lc->bParityType = USB_CDC_MARK_PARITY;
			अन्यथा
				lc->bParityType = USB_CDC_SPACE_PARITY;
		पूर्ण अन्यथा अणु
			अगर (C_PARODD(tty))
				lc->bParityType = USB_CDC_ODD_PARITY;
			अन्यथा
				lc->bParityType = USB_CDC_EVEN_PARITY;
		पूर्ण
	पूर्ण अन्यथा अणु
		lc->bParityType = USB_CDC_NO_PARITY;
	पूर्ण

	अगर (!data->type->have_5_6_bit_mode &&
			(C_CSIZE(tty) == CS5 || C_CSIZE(tty) == CS6)) अणु
		tty->termios.c_cflag &= ~CSIZE;
		अगर (old_termios)
			tty->termios.c_cflag |= old_termios->c_cflag & CSIZE;
		अन्यथा
			tty->termios.c_cflag |= CS8;
	पूर्ण

	चयन (C_CSIZE(tty)) अणु
	हाल CS5:
		lc->bDataBits = 5;
		अवरोध;
	हाल CS6:
		lc->bDataBits = 6;
		अवरोध;
	हाल CS7:
		lc->bDataBits = 7;
		अवरोध;
	हाल CS8:
	शेष:
		lc->bDataBits = 8;
		अवरोध;
	पूर्ण

	ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			USB_CDC_REQ_SET_LINE_CODING,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			0, alt->desc.bInterfaceNumber,
			lc, माप(*lc), USB_CTRL_SET_TIMEOUT);
	अगर (ret < 0)
		dev_err(&port->dev, "Failed to set line coding: %d\n", ret);

	kमुक्त(lc);
पूर्ण

अटल व्योम xr_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा xr_data *data = usb_get_serial_port_data(port);

	/*
	 * XR21V141X करोes not have a CUSTOM_DRIVER flag and always enters CDC
	 * mode upon receiving CDC requests.
	 */
	अगर (data->type->set_line_settings)
		data->type->set_line_settings(tty, port, old_termios);
	अन्यथा
		xr_cdc_set_line_coding(tty, port, old_termios);

	xr_set_flow_mode(tty, port, old_termios);
पूर्ण

अटल पूर्णांक xr_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	पूर्णांक ret;

	ret = xr_fअगरo_reset(port);
	अगर (ret)
		वापस ret;

	ret = xr_uart_enable(port);
	अगर (ret) अणु
		dev_err(&port->dev, "Failed to enable UART\n");
		वापस ret;
	पूर्ण

	/* Setup termios */
	अगर (tty)
		xr_set_termios(tty, port, शून्य);

	ret = usb_serial_generic_खोलो(tty, port);
	अगर (ret) अणु
		xr_uart_disable(port);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xr_बंद(काष्ठा usb_serial_port *port)
अणु
	usb_serial_generic_बंद(port);

	xr_uart_disable(port);
पूर्ण

अटल पूर्णांक xr_probe(काष्ठा usb_serial *serial, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_पूर्णांकerface *control = serial->पूर्णांकerface;
	काष्ठा usb_host_पूर्णांकerface *alt = control->cur_altsetting;
	काष्ठा usb_cdc_parsed_header hdrs;
	काष्ठा usb_cdc_जोड़_desc *desc;
	काष्ठा usb_पूर्णांकerface *data;
	पूर्णांक ret;

	ret = cdc_parse_cdc_header(&hdrs, control, alt->extra, alt->extralen);
	अगर (ret < 0)
		वापस -ENODEV;

	desc = hdrs.usb_cdc_जोड़_desc;
	अगर (!desc)
		वापस -ENODEV;

	data = usb_अगरnum_to_अगर(serial->dev, desc->bSlaveInterface0);
	अगर (!data)
		वापस -ENODEV;

	ret = usb_serial_claim_पूर्णांकerface(serial, data);
	अगर (ret)
		वापस ret;

	usb_set_serial_data(serial, (व्योम *)id->driver_info);

	वापस 0;
पूर्ण

अटल पूर्णांक xr_gpio_init(काष्ठा usb_serial_port *port, स्थिर काष्ठा xr_type *type)
अणु
	u16 mask, mode;
	पूर्णांक ret;

	/*
	 * Configure all pins as GPIO except क्रम Receive and Transmit Toggle.
	 */
	mode = 0;
	अगर (type->have_xmit_toggle)
		mode |= XR_GPIO_MODE_RX_TOGGLE | XR_GPIO_MODE_TX_TOGGLE;

	ret = xr_set_reg_uart(port, type->gpio_mode, mode);
	अगर (ret)
		वापस ret;

	/*
	 * Configure DTR and RTS as outमाला_दो and make sure they are deनिश्चितed
	 * (active low), and configure RI, CD, DSR and CTS as inमाला_दो.
	 */
	mask = XR_GPIO_DTR | XR_GPIO_RTS;
	ret = xr_set_reg_uart(port, type->gpio_direction, mask);
	अगर (ret)
		वापस ret;

	ret = xr_set_reg_uart(port, type->gpio_set, mask);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक xr_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_पूर्णांकerface_descriptor *desc;
	स्थिर काष्ठा xr_type *type;
	काष्ठा xr_data *data;
	क्रमागत xr_type_id type_id;
	पूर्णांक ret;

	type_id = (पूर्णांक)(अचिन्हित दीर्घ)usb_get_serial_data(port->serial);
	type = &xr_types[type_id];

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->type = type;

	desc = &port->serial->पूर्णांकerface->cur_altsetting->desc;
	अगर (type_id == XR21V141X)
		data->channel = desc->bInterfaceNumber / 2;
	अन्यथा
		data->channel = desc->bInterfaceNumber;

	usb_set_serial_port_data(port, data);

	अगर (type->custom_driver) अणु
		ret = xr_set_reg_uart(port, type->custom_driver,
				XR_CUSTOM_DRIVER_ACTIVE);
		अगर (ret)
			जाओ err_मुक्त;
	पूर्ण

	ret = xr_gpio_init(port, type);
	अगर (ret)
		जाओ err_मुक्त;

	वापस 0;

err_मुक्त:
	kमुक्त(data);

	वापस ret;
पूर्ण

अटल व्योम xr_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा xr_data *data = usb_get_serial_port_data(port);

	kमुक्त(data);
पूर्ण

#घोषणा XR_DEVICE(vid, pid, type)					\
	USB_DEVICE_INTERFACE_CLASS((vid), (pid), USB_CLASS_COMM),	\
	.driver_info = (type)

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु XR_DEVICE(0x04e2, 0x1400, XR2280X) पूर्ण,
	अणु XR_DEVICE(0x04e2, 0x1401, XR2280X) पूर्ण,
	अणु XR_DEVICE(0x04e2, 0x1402, XR2280X) पूर्ण,
	अणु XR_DEVICE(0x04e2, 0x1403, XR2280X) पूर्ण,
	अणु XR_DEVICE(0x04e2, 0x1410, XR21V141X) पूर्ण,
	अणु XR_DEVICE(0x04e2, 0x1411, XR21B1411) पूर्ण,
	अणु XR_DEVICE(0x04e2, 0x1412, XR21V141X) पूर्ण,
	अणु XR_DEVICE(0x04e2, 0x1414, XR21V141X) पूर्ण,
	अणु XR_DEVICE(0x04e2, 0x1420, XR21B142X) पूर्ण,
	अणु XR_DEVICE(0x04e2, 0x1422, XR21B142X) पूर्ण,
	अणु XR_DEVICE(0x04e2, 0x1424, XR21B142X) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

अटल काष्ठा usb_serial_driver xr_device = अणु
	.driver = अणु
		.owner = THIS_MODULE,
		.name =	"xr_serial",
	पूर्ण,
	.id_table		= id_table,
	.num_ports		= 1,
	.probe			= xr_probe,
	.port_probe		= xr_port_probe,
	.port_हटाओ		= xr_port_हटाओ,
	.खोलो			= xr_खोलो,
	.बंद			= xr_बंद,
	.अवरोध_ctl		= xr_अवरोध_ctl,
	.set_termios		= xr_set_termios,
	.tiocmget		= xr_tiocmget,
	.tiocmset		= xr_tiocmset,
	.dtr_rts		= xr_dtr_rts
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&xr_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR("Manivannan Sadhasivam <mani@kernel.org>");
MODULE_DESCRIPTION("MaxLinear/Exar USB to Serial driver");
MODULE_LICENSE("GPL");
