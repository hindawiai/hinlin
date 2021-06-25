<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * F81532/F81534 USB to Serial Ports Bridge
 *
 * F81532 => 2 Serial Ports
 * F81534 => 4 Serial Ports
 *
 * Copyright (C) 2016 Feature Integration Technology Inc., (Fपूर्णांकek)
 * Copyright (C) 2016 Tom Tsai (Tom_Tsai@fपूर्णांकek.com.tw)
 * Copyright (C) 2016 Peter Hong (Peter_Hong@fपूर्णांकek.com.tw)
 *
 * The F81532/F81534 had 1 control endpoपूर्णांक क्रम setting, 1 endpoपूर्णांक bulk-out
 * क्रम all serial port TX and 1 endpoपूर्णांक bulk-in क्रम all serial port पढ़ो in
 * (Read Data/MSR/LSR).
 *
 * Write URB is fixed with 512bytes, per serial port used 128Bytes.
 * It can be described by f81534_prepare_ग_लिखो_buffer()
 *
 * Read URB is 512Bytes max, per serial port used 128Bytes.
 * It can be described by f81534_process_पढ़ो_urb() and maybe received with
 * 128x1,2,3,4 bytes.
 *
 */
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>

/* Serial Port रेजिस्टर Address */
#घोषणा F81534_UART_BASE_ADDRESS	0x1200
#घोषणा F81534_UART_OFFSET		0x10
#घोषणा F81534_DIVISOR_LSB_REG		(0x00 + F81534_UART_BASE_ADDRESS)
#घोषणा F81534_DIVISOR_MSB_REG		(0x01 + F81534_UART_BASE_ADDRESS)
#घोषणा F81534_INTERRUPT_ENABLE_REG	(0x01 + F81534_UART_BASE_ADDRESS)
#घोषणा F81534_FIFO_CONTROL_REG		(0x02 + F81534_UART_BASE_ADDRESS)
#घोषणा F81534_LINE_CONTROL_REG		(0x03 + F81534_UART_BASE_ADDRESS)
#घोषणा F81534_MODEM_CONTROL_REG	(0x04 + F81534_UART_BASE_ADDRESS)
#घोषणा F81534_LINE_STATUS_REG		(0x05 + F81534_UART_BASE_ADDRESS)
#घोषणा F81534_MODEM_STATUS_REG		(0x06 + F81534_UART_BASE_ADDRESS)
#घोषणा F81534_CLOCK_REG		(0x08 + F81534_UART_BASE_ADDRESS)
#घोषणा F81534_CONFIG1_REG		(0x09 + F81534_UART_BASE_ADDRESS)

#घोषणा F81534_DEF_CONF_ADDRESS_START	0x3000
#घोषणा F81534_DEF_CONF_SIZE		12

#घोषणा F81534_CUSTOM_ADDRESS_START	0x2f00
#घोषणा F81534_CUSTOM_DATA_SIZE		0x10
#घोषणा F81534_CUSTOM_NO_CUSTOM_DATA	0xff
#घोषणा F81534_CUSTOM_VALID_TOKEN	0xf0
#घोषणा F81534_CONF_OFFSET		1
#घोषणा F81534_CONF_INIT_GPIO_OFFSET	4
#घोषणा F81534_CONF_WORK_GPIO_OFFSET	8
#घोषणा F81534_CONF_GPIO_SHUTDOWN	7
#घोषणा F81534_CONF_GPIO_RS232		1

#घोषणा F81534_MAX_DATA_BLOCK		64
#घोषणा F81534_MAX_BUS_RETRY		20

/* Default URB समयout क्रम USB operations */
#घोषणा F81534_USB_MAX_RETRY		10
#घोषणा F81534_USB_TIMEOUT		2000
#घोषणा F81534_SET_GET_REGISTER		0xA0

#घोषणा F81534_NUM_PORT			4
#घोषणा F81534_UNUSED_PORT		0xff
#घोषणा F81534_WRITE_BUFFER_SIZE	512

#घोषणा DRIVER_DESC			"Fintek F81532/F81534"
#घोषणा FINTEK_VENDOR_ID_1		0x1934
#घोषणा FINTEK_VENDOR_ID_2		0x2C42
#घोषणा FINTEK_DEVICE_ID		0x1202
#घोषणा F81534_MAX_TX_SIZE		124
#घोषणा F81534_MAX_RX_SIZE		124
#घोषणा F81534_RECEIVE_BLOCK_SIZE	128
#घोषणा F81534_MAX_RECEIVE_BLOCK_SIZE	512

#घोषणा F81534_TOKEN_RECEIVE		0x01
#घोषणा F81534_TOKEN_WRITE		0x02
#घोषणा F81534_TOKEN_TX_EMPTY		0x03
#घोषणा F81534_TOKEN_MSR_CHANGE		0x04

/*
 * We used पूर्णांकeral SPI bus to access FLASH section. We must रुको the SPI bus to
 * idle अगर we perक्रमmed any command.
 *
 * SPI Bus status रेजिस्टर: F81534_BUS_REG_STATUS
 *	Bit 0/1	: BUSY
 *	Bit 2	: IDLE
 */
#घोषणा F81534_BUS_BUSY			(BIT(0) | BIT(1))
#घोषणा F81534_BUS_IDLE			BIT(2)
#घोषणा F81534_BUS_READ_DATA		0x1004
#घोषणा F81534_BUS_REG_STATUS		0x1003
#घोषणा F81534_BUS_REG_START		0x1002
#घोषणा F81534_BUS_REG_END		0x1001

#घोषणा F81534_CMD_READ			0x03

#घोषणा F81534_DEFAULT_BAUD_RATE	9600

#घोषणा F81534_PORT_CONF_RS232		0
#घोषणा F81534_PORT_CONF_RS485		BIT(0)
#घोषणा F81534_PORT_CONF_RS485_INVERT	(BIT(0) | BIT(1))
#घोषणा F81534_PORT_CONF_MODE_MASK	GENMASK(1, 0)
#घोषणा F81534_PORT_CONF_DISABLE_PORT	BIT(3)
#घोषणा F81534_PORT_CONF_NOT_EXIST_PORT	BIT(7)
#घोषणा F81534_PORT_UNAVAILABLE		\
	(F81534_PORT_CONF_DISABLE_PORT | F81534_PORT_CONF_NOT_EXIST_PORT)


#घोषणा F81534_1X_RXTRIGGER		0xc3
#घोषणा F81534_8X_RXTRIGGER		0xcf

/*
 * F81532/534 Clock रेजिस्टरs (offset +08h)
 *
 * Bit0:	UART Enable (always on)
 * Bit2-1:	Clock source selector
 *			00: 1.846MHz.
 *			01: 18.46MHz.
 *			10: 24MHz.
 *			11: 14.77MHz.
 * Bit4:	Auto direction(RTS) control (RTS pin Low when TX)
 * Bit5:	Invert direction(RTS) when Bit4 enabled (RTS pin high when TX)
 */

#घोषणा F81534_UART_EN			BIT(0)
#घोषणा F81534_CLK_1_846_MHZ		0
#घोषणा F81534_CLK_18_46_MHZ		BIT(1)
#घोषणा F81534_CLK_24_MHZ		BIT(2)
#घोषणा F81534_CLK_14_77_MHZ		(BIT(1) | BIT(2))
#घोषणा F81534_CLK_MASK			GENMASK(2, 1)
#घोषणा F81534_CLK_TX_DELAY_1BIT	BIT(3)
#घोषणा F81534_CLK_RS485_MODE		BIT(4)
#घोषणा F81534_CLK_RS485_INVERT		BIT(5)

अटल स्थिर काष्ठा usb_device_id f81534_id_table[] = अणु
	अणु USB_DEVICE(FINTEK_VENDOR_ID_1, FINTEK_DEVICE_ID) पूर्ण,
	अणु USB_DEVICE(FINTEK_VENDOR_ID_2, FINTEK_DEVICE_ID) पूर्ण,
	अणुपूर्ण			/* Terminating entry */
पूर्ण;

#घोषणा F81534_TX_EMPTY_BIT		0

काष्ठा f81534_serial_निजी अणु
	u8 conf_data[F81534_DEF_CONF_SIZE];
	पूर्णांक tty_idx[F81534_NUM_PORT];
	u8 setting_idx;
	पूर्णांक खोलोed_port;
	काष्ठा mutex urb_mutex;
पूर्ण;

काष्ठा f81534_port_निजी अणु
	काष्ठा mutex mcr_mutex;
	काष्ठा mutex lcr_mutex;
	काष्ठा work_काष्ठा lsr_work;
	काष्ठा usb_serial_port *port;
	अचिन्हित दीर्घ tx_empty;
	spinlock_t msr_lock;
	u32 baud_base;
	u8 shaकरोw_mcr;
	u8 shaकरोw_lcr;
	u8 shaकरोw_msr;
	u8 shaकरोw_clk;
	u8 phy_num;
पूर्ण;

काष्ठा f81534_pin_data अणु
	स्थिर u16 reg_addr;
	स्थिर u8 reg_mask;
पूर्ण;

काष्ठा f81534_port_out_pin अणु
	काष्ठा f81534_pin_data pin[3];
पूर्ण;

/* Pin output value क्रम M2/M1/M0(SD) */
अटल स्थिर काष्ठा f81534_port_out_pin f81534_port_out_pins[] = अणु
	 अणु अणु अणु 0x2ae8, BIT(7) पूर्ण, अणु 0x2a90, BIT(5) पूर्ण, अणु 0x2a90, BIT(4) पूर्ण पूर्ण पूर्ण,
	 अणु अणु अणु 0x2ae8, BIT(6) पूर्ण, अणु 0x2ae8, BIT(0) पूर्ण, अणु 0x2ae8, BIT(3) पूर्ण पूर्ण पूर्ण,
	 अणु अणु अणु 0x2a90, BIT(0) पूर्ण, अणु 0x2ae8, BIT(2) पूर्ण, अणु 0x2a80, BIT(6) पूर्ण पूर्ण पूर्ण,
	 अणु अणु अणु 0x2a90, BIT(3) पूर्ण, अणु 0x2a90, BIT(2) पूर्ण, अणु 0x2a90, BIT(1) पूर्ण पूर्ण पूर्ण,
पूर्ण;

अटल u32 स्थिर baudrate_table[] = अणु 115200, 921600, 1152000, 1500000 पूर्ण;
अटल u8 स्थिर घड़ी_प्रकारable[] = अणु F81534_CLK_1_846_MHZ, F81534_CLK_14_77_MHZ,
				F81534_CLK_18_46_MHZ, F81534_CLK_24_MHZ पूर्ण;

अटल पूर्णांक f81534_logic_to_phy_port(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_port *port)
अणु
	काष्ठा f81534_serial_निजी *serial_priv =
			usb_get_serial_data(port->serial);
	पूर्णांक count = 0;
	पूर्णांक i;

	क्रम (i = 0; i < F81534_NUM_PORT; ++i) अणु
		अगर (serial_priv->conf_data[i] & F81534_PORT_UNAVAILABLE)
			जारी;

		अगर (port->port_number == count)
			वापस i;

		++count;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक f81534_set_रेजिस्टर(काष्ठा usb_serial *serial, u16 reg, u8 data)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface = serial->पूर्णांकerface;
	काष्ठा usb_device *dev = serial->dev;
	माप_प्रकार count = F81534_USB_MAX_RETRY;
	पूर्णांक status;
	u8 *पंचांगp;

	पंचांगp = kदो_स्मृति(माप(u8), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	*पंचांगp = data;

	/*
	 * Our device maybe not reply when heavily loading, We'll retry क्रम
	 * F81534_USB_MAX_RETRY बार.
	 */
	जबतक (count--) अणु
		status = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
					 F81534_SET_GET_REGISTER,
					 USB_TYPE_VENDOR | USB_सूची_OUT,
					 reg, 0, पंचांगp, माप(u8),
					 F81534_USB_TIMEOUT);
		अगर (status == माप(u8)) अणु
			status = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (status < 0) अणु
		dev_err(&पूर्णांकerface->dev, "%s: reg: %x data: %x failed: %d\n",
				__func__, reg, data, status);
	पूर्ण

	kमुक्त(पंचांगp);
	वापस status;
पूर्ण

अटल पूर्णांक f81534_get_रेजिस्टर(काष्ठा usb_serial *serial, u16 reg, u8 *data)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface = serial->पूर्णांकerface;
	काष्ठा usb_device *dev = serial->dev;
	माप_प्रकार count = F81534_USB_MAX_RETRY;
	पूर्णांक status;
	u8 *पंचांगp;

	पंचांगp = kदो_स्मृति(माप(u8), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	/*
	 * Our device maybe not reply when heavily loading, We'll retry क्रम
	 * F81534_USB_MAX_RETRY बार.
	 */
	जबतक (count--) अणु
		status = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
					 F81534_SET_GET_REGISTER,
					 USB_TYPE_VENDOR | USB_सूची_IN,
					 reg, 0, पंचांगp, माप(u8),
					 F81534_USB_TIMEOUT);
		अगर (status > 0) अणु
			status = 0;
			अवरोध;
		पूर्ण अन्यथा अगर (status == 0) अणु
			status = -EIO;
		पूर्ण
	पूर्ण

	अगर (status < 0) अणु
		dev_err(&पूर्णांकerface->dev, "%s: reg: %x failed: %d\n", __func__,
				reg, status);
		जाओ end;
	पूर्ण

	*data = *पंचांगp;

end:
	kमुक्त(पंचांगp);
	वापस status;
पूर्ण

अटल पूर्णांक f81534_set_mask_रेजिस्टर(काष्ठा usb_serial *serial, u16 reg,
					u8 mask, u8 data)
अणु
	पूर्णांक status;
	u8 पंचांगp;

	status = f81534_get_रेजिस्टर(serial, reg, &पंचांगp);
	अगर (status)
		वापस status;

	पंचांगp &= ~mask;
	पंचांगp |= (mask & data);

	वापस f81534_set_रेजिस्टर(serial, reg, पंचांगp);
पूर्ण

अटल पूर्णांक f81534_set_phy_port_रेजिस्टर(काष्ठा usb_serial *serial, पूर्णांक phy,
					u16 reg, u8 data)
अणु
	वापस f81534_set_रेजिस्टर(serial, reg + F81534_UART_OFFSET * phy,
					data);
पूर्ण

अटल पूर्णांक f81534_get_phy_port_रेजिस्टर(काष्ठा usb_serial *serial, पूर्णांक phy,
					u16 reg, u8 *data)
अणु
	वापस f81534_get_रेजिस्टर(serial, reg + F81534_UART_OFFSET * phy,
					data);
पूर्ण

अटल पूर्णांक f81534_set_port_रेजिस्टर(काष्ठा usb_serial_port *port, u16 reg,
					u8 data)
अणु
	काष्ठा f81534_port_निजी *port_priv = usb_get_serial_port_data(port);

	वापस f81534_set_रेजिस्टर(port->serial,
			reg + port_priv->phy_num * F81534_UART_OFFSET, data);
पूर्ण

अटल पूर्णांक f81534_get_port_रेजिस्टर(काष्ठा usb_serial_port *port, u16 reg,
					u8 *data)
अणु
	काष्ठा f81534_port_निजी *port_priv = usb_get_serial_port_data(port);

	वापस f81534_get_रेजिस्टर(port->serial,
			reg + port_priv->phy_num * F81534_UART_OFFSET, data);
पूर्ण

/*
 * If we try to access the पूर्णांकernal flash via SPI bus, we should check the bus
 * status क्रम every command. e.g., F81534_BUS_REG_START/F81534_BUS_REG_END
 */
अटल पूर्णांक f81534_रुको_क्रम_spi_idle(काष्ठा usb_serial *serial)
अणु
	माप_प्रकार count = F81534_MAX_BUS_RETRY;
	u8 पंचांगp;
	पूर्णांक status;

	करो अणु
		status = f81534_get_रेजिस्टर(serial, F81534_BUS_REG_STATUS,
						&पंचांगp);
		अगर (status)
			वापस status;

		अगर (पंचांगp & F81534_BUS_BUSY)
			जारी;

		अगर (पंचांगp & F81534_BUS_IDLE)
			अवरोध;

	पूर्ण जबतक (--count);

	अगर (!count) अणु
		dev_err(&serial->पूर्णांकerface->dev,
				"%s: timed out waiting for idle SPI bus\n",
				__func__);
		वापस -EIO;
	पूर्ण

	वापस f81534_set_रेजिस्टर(serial, F81534_BUS_REG_STATUS,
				पंचांगp & ~F81534_BUS_IDLE);
पूर्ण

अटल पूर्णांक f81534_get_spi_रेजिस्टर(काष्ठा usb_serial *serial, u16 reg,
					u8 *data)
अणु
	पूर्णांक status;

	status = f81534_get_रेजिस्टर(serial, reg, data);
	अगर (status)
		वापस status;

	वापस f81534_रुको_क्रम_spi_idle(serial);
पूर्ण

अटल पूर्णांक f81534_set_spi_रेजिस्टर(काष्ठा usb_serial *serial, u16 reg, u8 data)
अणु
	पूर्णांक status;

	status = f81534_set_रेजिस्टर(serial, reg, data);
	अगर (status)
		वापस status;

	वापस f81534_रुको_क्रम_spi_idle(serial);
पूर्ण

अटल पूर्णांक f81534_पढ़ो_flash(काष्ठा usb_serial *serial, u32 address,
				माप_प्रकार size, u8 *buf)
अणु
	u8 पंचांगp_buf[F81534_MAX_DATA_BLOCK];
	माप_प्रकार block = 0;
	माप_प्रकार पढ़ो_size;
	माप_प्रकार count;
	पूर्णांक status;
	पूर्णांक offset;
	u16 reg_पंचांगp;

	status = f81534_set_spi_रेजिस्टर(serial, F81534_BUS_REG_START,
					F81534_CMD_READ);
	अगर (status)
		वापस status;

	status = f81534_set_spi_रेजिस्टर(serial, F81534_BUS_REG_START,
					(address >> 16) & 0xff);
	अगर (status)
		वापस status;

	status = f81534_set_spi_रेजिस्टर(serial, F81534_BUS_REG_START,
					(address >> 8) & 0xff);
	अगर (status)
		वापस status;

	status = f81534_set_spi_रेजिस्टर(serial, F81534_BUS_REG_START,
					(address >> 0) & 0xff);
	अगर (status)
		वापस status;

	/* Continuous पढ़ो mode */
	करो अणु
		पढ़ो_size = min_t(माप_प्रकार, F81534_MAX_DATA_BLOCK, size);

		क्रम (count = 0; count < पढ़ो_size; ++count) अणु
			/* To ग_लिखो F81534_BUS_REG_END when final byte */
			अगर (size <= F81534_MAX_DATA_BLOCK &&
					पढ़ो_size == count + 1)
				reg_पंचांगp = F81534_BUS_REG_END;
			अन्यथा
				reg_पंचांगp = F81534_BUS_REG_START;

			/*
			 * Dummy code, क्रमce IC to generate a पढ़ो pulse, the
			 * set of value 0xf1 is करोnt care (any value is ok)
			 */
			status = f81534_set_spi_रेजिस्टर(serial, reg_पंचांगp,
					0xf1);
			अगर (status)
				वापस status;

			status = f81534_get_spi_रेजिस्टर(serial,
						F81534_BUS_READ_DATA,
						&पंचांगp_buf[count]);
			अगर (status)
				वापस status;

			offset = count + block * F81534_MAX_DATA_BLOCK;
			buf[offset] = पंचांगp_buf[count];
		पूर्ण

		size -= पढ़ो_size;
		++block;
	पूर्ण जबतक (size);

	वापस 0;
पूर्ण

अटल व्योम f81534_prepare_ग_लिखो_buffer(काष्ठा usb_serial_port *port, u8 *buf)
अणु
	काष्ठा f81534_port_निजी *port_priv = usb_get_serial_port_data(port);
	पूर्णांक phy_num = port_priv->phy_num;
	u8 tx_len;
	पूर्णांक i;

	/*
	 * The block layout is fixed with 4x128 Bytes, per 128 Bytes a port.
	 * index 0: port phy idx (e.g., 0,1,2,3)
	 * index 1: only F81534_TOKEN_WRITE
	 * index 2: serial TX out length
	 * index 3: fix to 0
	 * index 4~127: serial out data block
	 */
	क्रम (i = 0; i < F81534_NUM_PORT; ++i) अणु
		buf[i * F81534_RECEIVE_BLOCK_SIZE] = i;
		buf[i * F81534_RECEIVE_BLOCK_SIZE + 1] = F81534_TOKEN_WRITE;
		buf[i * F81534_RECEIVE_BLOCK_SIZE + 2] = 0;
		buf[i * F81534_RECEIVE_BLOCK_SIZE + 3] = 0;
	पूर्ण

	tx_len = kfअगरo_out_locked(&port->ग_लिखो_fअगरo,
				&buf[phy_num * F81534_RECEIVE_BLOCK_SIZE + 4],
				F81534_MAX_TX_SIZE, &port->lock);

	buf[phy_num * F81534_RECEIVE_BLOCK_SIZE + 2] = tx_len;
पूर्ण

अटल पूर्णांक f81534_submit_ग_लिखोr(काष्ठा usb_serial_port *port, gfp_t mem_flags)
अणु
	काष्ठा f81534_port_निजी *port_priv = usb_get_serial_port_data(port);
	काष्ठा urb *urb;
	अचिन्हित दीर्घ flags;
	पूर्णांक result;

	/* Check is any data in ग_लिखो_fअगरo */
	spin_lock_irqsave(&port->lock, flags);

	अगर (kfअगरo_is_empty(&port->ग_लिखो_fअगरo)) अणु
		spin_unlock_irqrestore(&port->lock, flags);
		वापस 0;
	पूर्ण

	spin_unlock_irqrestore(&port->lock, flags);

	/* Check H/W is TXEMPTY */
	अगर (!test_and_clear_bit(F81534_TX_EMPTY_BIT, &port_priv->tx_empty))
		वापस 0;

	urb = port->ग_लिखो_urbs[0];
	f81534_prepare_ग_लिखो_buffer(port, port->bulk_out_buffers[0]);
	urb->transfer_buffer_length = F81534_WRITE_BUFFER_SIZE;

	result = usb_submit_urb(urb, mem_flags);
	अगर (result) अणु
		set_bit(F81534_TX_EMPTY_BIT, &port_priv->tx_empty);
		dev_err(&port->dev, "%s: submit failed: %d\n", __func__,
				result);
		वापस result;
	पूर्ण

	usb_serial_port_softपूर्णांक(port);
	वापस 0;
पूर्ण

अटल u32 f81534_calc_baud_भागisor(u32 baudrate, u32 घड़ीrate)
अणु
	अगर (!baudrate)
		वापस 0;

	/* Round to nearest भागisor */
	वापस DIV_ROUND_CLOSEST(घड़ीrate, baudrate);
पूर्ण

अटल पूर्णांक f81534_find_clk(u32 baudrate)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < ARRAY_SIZE(baudrate_table); ++idx) अणु
		अगर (baudrate <= baudrate_table[idx] &&
				baudrate_table[idx] % baudrate == 0)
			वापस idx;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक f81534_set_port_config(काष्ठा usb_serial_port *port,
		काष्ठा tty_काष्ठा *tty, u32 baudrate, u32 old_baudrate, u8 lcr)
अणु
	काष्ठा f81534_port_निजी *port_priv = usb_get_serial_port_data(port);
	u32 भागisor;
	पूर्णांक status;
	पूर्णांक i;
	पूर्णांक idx;
	u8 value;
	u32 baud_list[] = अणुbaudrate, old_baudrate, F81534_DEFAULT_BAUD_RATEपूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(baud_list); ++i) अणु
		idx = f81534_find_clk(baud_list[i]);
		अगर (idx >= 0) अणु
			baudrate = baud_list[i];
			tty_encode_baud_rate(tty, baudrate, baudrate);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (idx < 0)
		वापस -EINVAL;

	port_priv->baud_base = baudrate_table[idx];
	port_priv->shaकरोw_clk &= ~F81534_CLK_MASK;
	port_priv->shaकरोw_clk |= घड़ी_प्रकारable[idx];

	status = f81534_set_port_रेजिस्टर(port, F81534_CLOCK_REG,
			port_priv->shaकरोw_clk);
	अगर (status) अणु
		dev_err(&port->dev, "CLOCK_REG setting failed\n");
		वापस status;
	पूर्ण

	अगर (baudrate <= 1200)
		value = F81534_1X_RXTRIGGER;	/* 128 FIFO & TL: 1x */
	अन्यथा
		value = F81534_8X_RXTRIGGER;	/* 128 FIFO & TL: 8x */

	status = f81534_set_port_रेजिस्टर(port, F81534_CONFIG1_REG, value);
	अगर (status) अणु
		dev_err(&port->dev, "%s: CONFIG1 setting failed\n", __func__);
		वापस status;
	पूर्ण

	अगर (baudrate <= 1200)
		value = UART_FCR_TRIGGER_1 | UART_FCR_ENABLE_FIFO; /* TL: 1 */
	अन्यथा
		value = UART_FCR_TRIGGER_8 | UART_FCR_ENABLE_FIFO; /* TL: 8 */

	status = f81534_set_port_रेजिस्टर(port, F81534_FIFO_CONTROL_REG,
						value);
	अगर (status) अणु
		dev_err(&port->dev, "%s: FCR setting failed\n", __func__);
		वापस status;
	पूर्ण

	भागisor = f81534_calc_baud_भागisor(baudrate, port_priv->baud_base);

	mutex_lock(&port_priv->lcr_mutex);

	value = UART_LCR_DLAB;
	status = f81534_set_port_रेजिस्टर(port, F81534_LINE_CONTROL_REG,
						value);
	अगर (status) अणु
		dev_err(&port->dev, "%s: set LCR failed\n", __func__);
		जाओ out_unlock;
	पूर्ण

	value = भागisor & 0xff;
	status = f81534_set_port_रेजिस्टर(port, F81534_DIVISOR_LSB_REG, value);
	अगर (status) अणु
		dev_err(&port->dev, "%s: set DLAB LSB failed\n", __func__);
		जाओ out_unlock;
	पूर्ण

	value = (भागisor >> 8) & 0xff;
	status = f81534_set_port_रेजिस्टर(port, F81534_DIVISOR_MSB_REG, value);
	अगर (status) अणु
		dev_err(&port->dev, "%s: set DLAB MSB failed\n", __func__);
		जाओ out_unlock;
	पूर्ण

	value = lcr | (port_priv->shaकरोw_lcr & UART_LCR_SBC);
	status = f81534_set_port_रेजिस्टर(port, F81534_LINE_CONTROL_REG,
						value);
	अगर (status) अणु
		dev_err(&port->dev, "%s: set LCR failed\n", __func__);
		जाओ out_unlock;
	पूर्ण

	port_priv->shaकरोw_lcr = value;
out_unlock:
	mutex_unlock(&port_priv->lcr_mutex);

	वापस status;
पूर्ण

अटल व्योम f81534_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा f81534_port_निजी *port_priv = usb_get_serial_port_data(port);
	पूर्णांक status;

	mutex_lock(&port_priv->lcr_mutex);

	अगर (अवरोध_state)
		port_priv->shaकरोw_lcr |= UART_LCR_SBC;
	अन्यथा
		port_priv->shaकरोw_lcr &= ~UART_LCR_SBC;

	status = f81534_set_port_रेजिस्टर(port, F81534_LINE_CONTROL_REG,
					port_priv->shaकरोw_lcr);
	अगर (status)
		dev_err(&port->dev, "set break failed: %d\n", status);

	mutex_unlock(&port_priv->lcr_mutex);
पूर्ण

अटल पूर्णांक f81534_update_mctrl(काष्ठा usb_serial_port *port, अचिन्हित पूर्णांक set,
				अचिन्हित पूर्णांक clear)
अणु
	काष्ठा f81534_port_निजी *port_priv = usb_get_serial_port_data(port);
	पूर्णांक status;
	u8 पंचांगp;

	अगर (((set | clear) & (TIOCM_DTR | TIOCM_RTS)) == 0)
		वापस 0;	/* no change */

	mutex_lock(&port_priv->mcr_mutex);

	/* 'Set' takes precedence over 'Clear' */
	clear &= ~set;

	/* Always enable UART_MCR_OUT2 */
	पंचांगp = UART_MCR_OUT2 | port_priv->shaकरोw_mcr;

	अगर (clear & TIOCM_DTR)
		पंचांगp &= ~UART_MCR_DTR;

	अगर (clear & TIOCM_RTS)
		पंचांगp &= ~UART_MCR_RTS;

	अगर (set & TIOCM_DTR)
		पंचांगp |= UART_MCR_DTR;

	अगर (set & TIOCM_RTS)
		पंचांगp |= UART_MCR_RTS;

	status = f81534_set_port_रेजिस्टर(port, F81534_MODEM_CONTROL_REG, पंचांगp);
	अगर (status < 0) अणु
		dev_err(&port->dev, "%s: MCR write failed\n", __func__);
		mutex_unlock(&port_priv->mcr_mutex);
		वापस status;
	पूर्ण

	port_priv->shaकरोw_mcr = पंचांगp;
	mutex_unlock(&port_priv->mcr_mutex);
	वापस 0;
पूर्ण

/*
 * This function will search the data area with token F81534_CUSTOM_VALID_TOKEN
 * क्रम latest configuration index. If nothing found
 * (*index = F81534_CUSTOM_NO_CUSTOM_DATA), We'll load शेष configure in
 * F81534_DEF_CONF_ADDRESS_START section.
 *
 * Due to we only use block0 to save data, so *index should be 0 or
 * F81534_CUSTOM_NO_CUSTOM_DATA.
 */
अटल पूर्णांक f81534_find_config_idx(काष्ठा usb_serial *serial, u8 *index)
अणु
	u8 पंचांगp;
	पूर्णांक status;

	status = f81534_पढ़ो_flash(serial, F81534_CUSTOM_ADDRESS_START, 1,
					&पंचांगp);
	अगर (status) अणु
		dev_err(&serial->पूर्णांकerface->dev, "%s: read failed: %d\n",
				__func__, status);
		वापस status;
	पूर्ण

	/* We'll use the custom data when the data is valid. */
	अगर (पंचांगp == F81534_CUSTOM_VALID_TOKEN)
		*index = 0;
	अन्यथा
		*index = F81534_CUSTOM_NO_CUSTOM_DATA;

	वापस 0;
पूर्ण

/*
 * The F81532/534 will not report serial port to USB serial subप्रणाली when
 * H/W DCD/DSR/CTS/RI/RX pin connected to ground.
 *
 * To detect RX pin status, we'll enable MCR पूर्णांकeral loopback, disable it and
 * delayed क्रम 60ms. It connected to ground If LSR रेजिस्टर report UART_LSR_BI.
 */
अटल bool f81534_check_port_hw_disabled(काष्ठा usb_serial *serial, पूर्णांक phy)
अणु
	पूर्णांक status;
	u8 old_mcr;
	u8 msr;
	u8 lsr;
	u8 msr_mask;

	msr_mask = UART_MSR_DCD | UART_MSR_RI | UART_MSR_DSR | UART_MSR_CTS;

	status = f81534_get_phy_port_रेजिस्टर(serial, phy,
				F81534_MODEM_STATUS_REG, &msr);
	अगर (status)
		वापस false;

	अगर ((msr & msr_mask) != msr_mask)
		वापस false;

	status = f81534_set_phy_port_रेजिस्टर(serial, phy,
				F81534_FIFO_CONTROL_REG, UART_FCR_ENABLE_FIFO |
				UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
	अगर (status)
		वापस false;

	status = f81534_get_phy_port_रेजिस्टर(serial, phy,
				F81534_MODEM_CONTROL_REG, &old_mcr);
	अगर (status)
		वापस false;

	status = f81534_set_phy_port_रेजिस्टर(serial, phy,
				F81534_MODEM_CONTROL_REG, UART_MCR_LOOP);
	अगर (status)
		वापस false;

	status = f81534_set_phy_port_रेजिस्टर(serial, phy,
				F81534_MODEM_CONTROL_REG, 0x0);
	अगर (status)
		वापस false;

	msleep(60);

	status = f81534_get_phy_port_रेजिस्टर(serial, phy,
				F81534_LINE_STATUS_REG, &lsr);
	अगर (status)
		वापस false;

	status = f81534_set_phy_port_रेजिस्टर(serial, phy,
				F81534_MODEM_CONTROL_REG, old_mcr);
	अगर (status)
		वापस false;

	अगर ((lsr & UART_LSR_BI) == UART_LSR_BI)
		वापस true;

	वापस false;
पूर्ण

/*
 * We had 2 generation of F81532/534 IC. All has an पूर्णांकernal storage.
 *
 * 1st is pure USB-to-TTL RS232 IC and deचिन्हित क्रम 4 ports only, no any
 * पूर्णांकernal data will used. All mode and gpio control should manually set
 * by AP or Driver and all storage space value are 0xff. The
 * f81534_calc_num_ports() will run to final we marked as "oldest version"
 * क्रम this IC.
 *
 * 2rd is deचिन्हित to more generic to use any transceiver and this is our
 * mass production type. We'll save data in F81534_CUSTOM_ADDRESS_START
 * (0x2f00) with 9bytes. The 1st byte is a indicater. If the token is
 * F81534_CUSTOM_VALID_TOKEN(0xf0), the IC is 2nd gen type, the following
 * 4bytes save port mode (0:RS232/1:RS485 Invert/2:RS485), and the last
 * 4bytes save GPIO state(value from 0~7 to represent 3 GPIO output pin).
 * The f81534_calc_num_ports() will run to "new style" with checking
 * F81534_PORT_UNAVAILABLE section.
 */
अटल पूर्णांक f81534_calc_num_ports(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds)
अणु
	काष्ठा f81534_serial_निजी *serial_priv;
	काष्ठा device *dev = &serial->पूर्णांकerface->dev;
	पूर्णांक size_bulk_in = usb_endpoपूर्णांक_maxp(epds->bulk_in[0]);
	पूर्णांक size_bulk_out = usb_endpoपूर्णांक_maxp(epds->bulk_out[0]);
	u8 num_port = 0;
	पूर्णांक index = 0;
	पूर्णांक status;
	पूर्णांक i;

	अगर (size_bulk_out != F81534_WRITE_BUFFER_SIZE ||
			size_bulk_in != F81534_MAX_RECEIVE_BLOCK_SIZE) अणु
		dev_err(dev, "unsupported endpoint max packet size\n");
		वापस -ENODEV;
	पूर्ण

	serial_priv = devm_kzalloc(&serial->पूर्णांकerface->dev,
					माप(*serial_priv), GFP_KERNEL);
	अगर (!serial_priv)
		वापस -ENOMEM;

	usb_set_serial_data(serial, serial_priv);
	mutex_init(&serial_priv->urb_mutex);

	/* Check had custom setting */
	status = f81534_find_config_idx(serial, &serial_priv->setting_idx);
	अगर (status) अणु
		dev_err(&serial->पूर्णांकerface->dev, "%s: find idx failed: %d\n",
				__func__, status);
		वापस status;
	पूर्ण

	/*
	 * We'll read custom data only when data available, otherwise we'll
	 * पढ़ो शेष value instead.
	 */
	अगर (serial_priv->setting_idx != F81534_CUSTOM_NO_CUSTOM_DATA) अणु
		status = f81534_पढ़ो_flash(serial,
						F81534_CUSTOM_ADDRESS_START +
						F81534_CONF_OFFSET,
						माप(serial_priv->conf_data),
						serial_priv->conf_data);
		अगर (status) अणु
			dev_err(&serial->पूर्णांकerface->dev,
					"%s: get custom data failed: %d\n",
					__func__, status);
			वापस status;
		पूर्ण

		dev_dbg(&serial->पूर्णांकerface->dev,
				"%s: read config from block: %d\n", __func__,
				serial_priv->setting_idx);
	पूर्ण अन्यथा अणु
		/* Read शेष board setting */
		status = f81534_पढ़ो_flash(serial,
				F81534_DEF_CONF_ADDRESS_START,
				माप(serial_priv->conf_data),
				serial_priv->conf_data);
		अगर (status) अणु
			dev_err(&serial->पूर्णांकerface->dev,
					"%s: read failed: %d\n", __func__,
					status);
			वापस status;
		पूर्ण

		dev_dbg(&serial->पूर्णांकerface->dev, "%s: read default config\n",
				__func__);
	पूर्ण

	/* New style, find all possible ports */
	क्रम (i = 0; i < F81534_NUM_PORT; ++i) अणु
		अगर (f81534_check_port_hw_disabled(serial, i))
			serial_priv->conf_data[i] |= F81534_PORT_UNAVAILABLE;

		अगर (serial_priv->conf_data[i] & F81534_PORT_UNAVAILABLE)
			जारी;

		++num_port;
	पूर्ण

	अगर (!num_port) अणु
		dev_warn(&serial->पूर्णांकerface->dev,
			"no config found, assuming 4 ports\n");
		num_port = 4;		/* Nothing found, oldest version IC */
	पूर्ण

	/* Assign phy-to-logic mapping */
	क्रम (i = 0; i < F81534_NUM_PORT; ++i) अणु
		अगर (serial_priv->conf_data[i] & F81534_PORT_UNAVAILABLE)
			जारी;

		serial_priv->tty_idx[i] = index++;
		dev_dbg(&serial->पूर्णांकerface->dev,
				"%s: phy_num: %d, tty_idx: %d\n", __func__, i,
				serial_priv->tty_idx[i]);
	पूर्ण

	/*
	 * Setup bulk-out endpoपूर्णांक multiplexing. All ports share the same
	 * bulk-out endpoपूर्णांक.
	 */
	BUILD_BUG_ON(ARRAY_SIZE(epds->bulk_out) < F81534_NUM_PORT);

	क्रम (i = 1; i < num_port; ++i)
		epds->bulk_out[i] = epds->bulk_out[0];

	epds->num_bulk_out = num_port;

	वापस num_port;
पूर्ण

अटल व्योम f81534_set_termios(काष्ठा tty_काष्ठा *tty,
				काष्ठा usb_serial_port *port,
				काष्ठा ktermios *old_termios)
अणु
	u8 new_lcr = 0;
	पूर्णांक status;
	u32 baud;
	u32 old_baud;

	अगर (C_BAUD(tty) == B0)
		f81534_update_mctrl(port, 0, TIOCM_DTR | TIOCM_RTS);
	अन्यथा अगर (old_termios && (old_termios->c_cflag & CBAUD) == B0)
		f81534_update_mctrl(port, TIOCM_DTR | TIOCM_RTS, 0);

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

	baud = tty_get_baud_rate(tty);
	अगर (!baud)
		वापस;

	अगर (old_termios)
		old_baud = tty_termios_baud_rate(old_termios);
	अन्यथा
		old_baud = F81534_DEFAULT_BAUD_RATE;

	dev_dbg(&port->dev, "%s: baud: %d\n", __func__, baud);

	status = f81534_set_port_config(port, tty, baud, old_baud, new_lcr);
	अगर (status < 0) अणु
		dev_err(&port->dev, "%s: set port config failed: %d\n",
				__func__, status);
	पूर्ण
पूर्ण

अटल पूर्णांक f81534_submit_पढ़ो_urb(काष्ठा usb_serial *serial, gfp_t flags)
अणु
	वापस usb_serial_generic_submit_पढ़ो_urbs(serial->port[0], flags);
पूर्ण

अटल व्योम f81534_msr_changed(काष्ठा usb_serial_port *port, u8 msr)
अणु
	काष्ठा f81534_port_निजी *port_priv = usb_get_serial_port_data(port);
	काष्ठा tty_काष्ठा *tty;
	अचिन्हित दीर्घ flags;
	u8 old_msr;

	अगर (!(msr & UART_MSR_ANY_DELTA))
		वापस;

	spin_lock_irqsave(&port_priv->msr_lock, flags);
	old_msr = port_priv->shaकरोw_msr;
	port_priv->shaकरोw_msr = msr;
	spin_unlock_irqrestore(&port_priv->msr_lock, flags);

	dev_dbg(&port->dev, "%s: MSR from %02x to %02x\n", __func__, old_msr,
			msr);

	/* Update input line counters */
	अगर (msr & UART_MSR_DCTS)
		port->icount.cts++;
	अगर (msr & UART_MSR_DDSR)
		port->icount.dsr++;
	अगर (msr & UART_MSR_DDCD)
		port->icount.dcd++;
	अगर (msr & UART_MSR_TERI)
		port->icount.rng++;

	wake_up_पूर्णांकerruptible(&port->port.delta_msr_रुको);

	अगर (!(msr & UART_MSR_DDCD))
		वापस;

	dev_dbg(&port->dev, "%s: DCD Changed: phy_num: %d from %x to %x\n",
			__func__, port_priv->phy_num, old_msr, msr);

	tty = tty_port_tty_get(&port->port);
	अगर (!tty)
		वापस;

	usb_serial_handle_dcd_change(port, tty, msr & UART_MSR_DCD);
	tty_kref_put(tty);
पूर्ण

अटल पूर्णांक f81534_पढ़ो_msr(काष्ठा usb_serial_port *port)
अणु
	काष्ठा f81534_port_निजी *port_priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	पूर्णांक status;
	u8 msr;

	/* Get MSR initial value */
	status = f81534_get_port_रेजिस्टर(port, F81534_MODEM_STATUS_REG, &msr);
	अगर (status)
		वापस status;

	/* Force update current state */
	spin_lock_irqsave(&port_priv->msr_lock, flags);
	port_priv->shaकरोw_msr = msr;
	spin_unlock_irqrestore(&port_priv->msr_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक f81534_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा f81534_serial_निजी *serial_priv =
			usb_get_serial_data(port->serial);
	काष्ठा f81534_port_निजी *port_priv = usb_get_serial_port_data(port);
	पूर्णांक status;

	status = f81534_set_port_रेजिस्टर(port,
				F81534_FIFO_CONTROL_REG, UART_FCR_ENABLE_FIFO |
				UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
	अगर (status) अणु
		dev_err(&port->dev, "%s: Clear FIFO failed: %d\n", __func__,
				status);
		वापस status;
	पूर्ण

	अगर (tty)
		f81534_set_termios(tty, port, शून्य);

	status = f81534_पढ़ो_msr(port);
	अगर (status)
		वापस status;

	mutex_lock(&serial_priv->urb_mutex);

	/* Submit Read URBs क्रम first port खोलोed */
	अगर (!serial_priv->खोलोed_port) अणु
		status = f81534_submit_पढ़ो_urb(port->serial, GFP_KERNEL);
		अगर (status)
			जाओ निकास;
	पूर्ण

	serial_priv->खोलोed_port++;

निकास:
	mutex_unlock(&serial_priv->urb_mutex);

	set_bit(F81534_TX_EMPTY_BIT, &port_priv->tx_empty);
	वापस status;
पूर्ण

अटल व्योम f81534_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा f81534_serial_निजी *serial_priv =
			usb_get_serial_data(port->serial);
	काष्ठा usb_serial_port *port0 = port->serial->port[0];
	अचिन्हित दीर्घ flags;
	माप_प्रकार i;

	usb_समाप्त_urb(port->ग_लिखो_urbs[0]);

	spin_lock_irqsave(&port->lock, flags);
	kfअगरo_reset_out(&port->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&port->lock, flags);

	/* Kill Read URBs when final port बंदd */
	mutex_lock(&serial_priv->urb_mutex);
	serial_priv->खोलोed_port--;

	अगर (!serial_priv->खोलोed_port) अणु
		क्रम (i = 0; i < ARRAY_SIZE(port0->पढ़ो_urbs); ++i)
			usb_समाप्त_urb(port0->पढ़ो_urbs[i]);
	पूर्ण

	mutex_unlock(&serial_priv->urb_mutex);
पूर्ण

अटल व्योम f81534_get_serial_info(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा f81534_port_निजी *port_priv;

	port_priv = usb_get_serial_port_data(port);

	ss->baud_base = port_priv->baud_base;
पूर्ण

अटल व्योम f81534_process_per_serial_block(काष्ठा usb_serial_port *port,
		u8 *data)
अणु
	काष्ठा f81534_port_निजी *port_priv = usb_get_serial_port_data(port);
	पूर्णांक phy_num = data[0];
	माप_प्रकार पढ़ो_size = 0;
	माप_प्रकार i;
	अक्षर tty_flag;
	पूर्णांक status;
	u8 lsr;

	/*
	 * The block layout is 128 Bytes
	 * index 0: port phy idx (e.g., 0,1,2,3),
	 * index 1: It's could be
	 *			F81534_TOKEN_RECEIVE
	 *			F81534_TOKEN_TX_EMPTY
	 *			F81534_TOKEN_MSR_CHANGE
	 * index 2: serial in size (data+lsr, must be even)
	 *			meaningful क्रम F81534_TOKEN_RECEIVE only
	 * index 3: current MSR with this device
	 * index 4~127: serial in data block (data+lsr, must be even)
	 */
	चयन (data[1]) अणु
	हाल F81534_TOKEN_TX_EMPTY:
		set_bit(F81534_TX_EMPTY_BIT, &port_priv->tx_empty);

		/* Try to submit ग_लिखोr */
		status = f81534_submit_ग_लिखोr(port, GFP_ATOMIC);
		अगर (status)
			dev_err(&port->dev, "%s: submit failed\n", __func__);
		वापस;

	हाल F81534_TOKEN_MSR_CHANGE:
		f81534_msr_changed(port, data[3]);
		वापस;

	हाल F81534_TOKEN_RECEIVE:
		पढ़ो_size = data[2];
		अगर (पढ़ो_size > F81534_MAX_RX_SIZE) अणु
			dev_err(&port->dev,
				"%s: phy: %d read_size: %zu larger than: %d\n",
				__func__, phy_num, पढ़ो_size,
				F81534_MAX_RX_SIZE);
			वापस;
		पूर्ण

		अवरोध;

	शेष:
		dev_warn(&port->dev, "%s: unknown token: %02x\n", __func__,
				data[1]);
		वापस;
	पूर्ण

	क्रम (i = 4; i < 4 + पढ़ो_size; i += 2) अणु
		tty_flag = TTY_NORMAL;
		lsr = data[i + 1];

		अगर (lsr & UART_LSR_BRK_ERROR_BITS) अणु
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
				tty_insert_flip_अक्षर(&port->port, 0,
						TTY_OVERRUN);
			पूर्ण

			schedule_work(&port_priv->lsr_work);
		पूर्ण

		अगर (port->sysrq) अणु
			अगर (usb_serial_handle_sysrq_अक्षर(port, data[i]))
				जारी;
		पूर्ण

		tty_insert_flip_अक्षर(&port->port, data[i], tty_flag);
	पूर्ण

	tty_flip_buffer_push(&port->port);
पूर्ण

अटल व्योम f81534_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा f81534_serial_निजी *serial_priv;
	काष्ठा usb_serial_port *port;
	काष्ठा usb_serial *serial;
	u8 *buf;
	पूर्णांक phy_port_num;
	पूर्णांक tty_port_num;
	माप_प्रकार i;

	अगर (!urb->actual_length ||
			urb->actual_length % F81534_RECEIVE_BLOCK_SIZE) अणु
		वापस;
	पूर्ण

	port = urb->context;
	serial = port->serial;
	buf = urb->transfer_buffer;
	serial_priv = usb_get_serial_data(serial);

	क्रम (i = 0; i < urb->actual_length; i += F81534_RECEIVE_BLOCK_SIZE) अणु
		phy_port_num = buf[i];
		अगर (phy_port_num >= F81534_NUM_PORT) अणु
			dev_err(&port->dev,
				"%s: phy_port_num: %d larger than: %d\n",
				__func__, phy_port_num, F81534_NUM_PORT);
			जारी;
		पूर्ण

		tty_port_num = serial_priv->tty_idx[phy_port_num];
		port = serial->port[tty_port_num];

		अगर (tty_port_initialized(&port->port))
			f81534_process_per_serial_block(port, &buf[i]);
	पूर्ण
पूर्ण

अटल व्योम f81534_ग_लिखो_usb_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		dev_dbg(&port->dev, "%s - urb stopped: %d\n",
				__func__, urb->status);
		वापस;
	हाल -EPIPE:
		dev_err(&port->dev, "%s - urb stopped: %d\n",
				__func__, urb->status);
		वापस;
	शेष:
		dev_dbg(&port->dev, "%s - nonzero urb status: %d\n",
				__func__, urb->status);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम f81534_lsr_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा f81534_port_निजी *port_priv;
	काष्ठा usb_serial_port *port;
	पूर्णांक status;
	u8 पंचांगp;

	port_priv = container_of(work, काष्ठा f81534_port_निजी, lsr_work);
	port = port_priv->port;

	status = f81534_get_port_रेजिस्टर(port, F81534_LINE_STATUS_REG, &पंचांगp);
	अगर (status)
		dev_warn(&port->dev, "read LSR failed: %d\n", status);
पूर्ण

अटल पूर्णांक f81534_set_port_output_pin(काष्ठा usb_serial_port *port)
अणु
	काष्ठा f81534_serial_निजी *serial_priv;
	काष्ठा f81534_port_निजी *port_priv;
	काष्ठा usb_serial *serial;
	स्थिर काष्ठा f81534_port_out_pin *pins;
	पूर्णांक status;
	पूर्णांक i;
	u8 value;
	u8 idx;

	serial = port->serial;
	serial_priv = usb_get_serial_data(serial);
	port_priv = usb_get_serial_port_data(port);

	idx = F81534_CONF_INIT_GPIO_OFFSET + port_priv->phy_num;
	value = serial_priv->conf_data[idx];
	अगर (value >= F81534_CONF_GPIO_SHUTDOWN) अणु
		/*
		 * Newer IC configure will make transceiver in shutकरोwn mode on
		 * initial घातer on. We need enable it beक्रमe using UARTs.
		 */
		idx = F81534_CONF_WORK_GPIO_OFFSET + port_priv->phy_num;
		value = serial_priv->conf_data[idx];
		अगर (value >= F81534_CONF_GPIO_SHUTDOWN)
			value = F81534_CONF_GPIO_RS232;
	पूर्ण

	pins = &f81534_port_out_pins[port_priv->phy_num];

	क्रम (i = 0; i < ARRAY_SIZE(pins->pin); ++i) अणु
		status = f81534_set_mask_रेजिस्टर(serial,
				pins->pin[i].reg_addr, pins->pin[i].reg_mask,
				value & BIT(i) ? pins->pin[i].reg_mask : 0);
		अगर (status)
			वापस status;
	पूर्ण

	dev_dbg(&port->dev, "Output pin (M0/M1/M2): %d\n", value);
	वापस 0;
पूर्ण

अटल पूर्णांक f81534_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा f81534_serial_निजी *serial_priv;
	काष्ठा f81534_port_निजी *port_priv;
	पूर्णांक ret;
	u8 value;

	serial_priv = usb_get_serial_data(port->serial);
	port_priv = devm_kzalloc(&port->dev, माप(*port_priv), GFP_KERNEL);
	अगर (!port_priv)
		वापस -ENOMEM;

	/*
	 * We'll make tx frame error when baud rate from 384~500kps. So we'll
	 * delay all tx data frame with 1bit.
	 */
	port_priv->shaकरोw_clk = F81534_UART_EN | F81534_CLK_TX_DELAY_1BIT;
	spin_lock_init(&port_priv->msr_lock);
	mutex_init(&port_priv->mcr_mutex);
	mutex_init(&port_priv->lcr_mutex);
	INIT_WORK(&port_priv->lsr_work, f81534_lsr_worker);

	/* Assign logic-to-phy mapping */
	ret = f81534_logic_to_phy_port(port->serial, port);
	अगर (ret < 0)
		वापस ret;

	port_priv->phy_num = ret;
	port_priv->port = port;
	usb_set_serial_port_data(port, port_priv);
	dev_dbg(&port->dev, "%s: port_number: %d, phy_num: %d\n", __func__,
			port->port_number, port_priv->phy_num);

	/*
	 * The F81532/534 will hang-up when enable LSR पूर्णांकerrupt in IER and
	 * occur data overrun. So we'll disable the LSR पूर्णांकerrupt in probe()
	 * and submit the LSR worker to clear LSR state when reported LSR error
	 * bit with bulk-in data in f81534_process_per_serial_block().
	 */
	ret = f81534_set_port_रेजिस्टर(port, F81534_INTERRUPT_ENABLE_REG,
			UART_IER_RDI | UART_IER_THRI | UART_IER_MSI);
	अगर (ret)
		वापस ret;

	value = serial_priv->conf_data[port_priv->phy_num];
	चयन (value & F81534_PORT_CONF_MODE_MASK) अणु
	हाल F81534_PORT_CONF_RS485_INVERT:
		port_priv->shaकरोw_clk |= F81534_CLK_RS485_MODE |
					F81534_CLK_RS485_INVERT;
		dev_dbg(&port->dev, "RS485 invert mode\n");
		अवरोध;
	हाल F81534_PORT_CONF_RS485:
		port_priv->shaकरोw_clk |= F81534_CLK_RS485_MODE;
		dev_dbg(&port->dev, "RS485 mode\n");
		अवरोध;

	शेष:
	हाल F81534_PORT_CONF_RS232:
		dev_dbg(&port->dev, "RS232 mode\n");
		अवरोध;
	पूर्ण

	वापस f81534_set_port_output_pin(port);
पूर्ण

अटल व्योम f81534_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा f81534_port_निजी *port_priv = usb_get_serial_port_data(port);

	flush_work(&port_priv->lsr_work);
पूर्ण

अटल पूर्णांक f81534_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा f81534_port_निजी *port_priv = usb_get_serial_port_data(port);
	पूर्णांक status;
	पूर्णांक r;
	u8 msr;
	u8 mcr;

	/* Read current MSR from device */
	status = f81534_get_port_रेजिस्टर(port, F81534_MODEM_STATUS_REG, &msr);
	अगर (status)
		वापस status;

	mutex_lock(&port_priv->mcr_mutex);
	mcr = port_priv->shaकरोw_mcr;
	mutex_unlock(&port_priv->mcr_mutex);

	r = (mcr & UART_MCR_DTR ? TIOCM_DTR : 0) |
	    (mcr & UART_MCR_RTS ? TIOCM_RTS : 0) |
	    (msr & UART_MSR_CTS ? TIOCM_CTS : 0) |
	    (msr & UART_MSR_DCD ? TIOCM_CAR : 0) |
	    (msr & UART_MSR_RI ? TIOCM_RI : 0) |
	    (msr & UART_MSR_DSR ? TIOCM_DSR : 0);

	वापस r;
पूर्ण

अटल पूर्णांक f81534_tiocmset(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक set,
				अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	वापस f81534_update_mctrl(port, set, clear);
पूर्ण

अटल व्योम f81534_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	अगर (on)
		f81534_update_mctrl(port, TIOCM_DTR | TIOCM_RTS, 0);
	अन्यथा
		f81534_update_mctrl(port, 0, TIOCM_DTR | TIOCM_RTS);
पूर्ण

अटल पूर्णांक f81534_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
			स्थिर u8 *buf, पूर्णांक count)
अणु
	पूर्णांक bytes_out, status;

	अगर (!count)
		वापस 0;

	bytes_out = kfअगरo_in_locked(&port->ग_लिखो_fअगरo, buf, count,
					&port->lock);

	status = f81534_submit_ग_लिखोr(port, GFP_ATOMIC);
	अगर (status) अणु
		dev_err(&port->dev, "%s: submit failed\n", __func__);
		वापस status;
	पूर्ण

	वापस bytes_out;
पूर्ण

अटल bool f81534_tx_empty(काष्ठा usb_serial_port *port)
अणु
	काष्ठा f81534_port_निजी *port_priv = usb_get_serial_port_data(port);

	वापस test_bit(F81534_TX_EMPTY_BIT, &port_priv->tx_empty);
पूर्ण

अटल पूर्णांक f81534_resume(काष्ठा usb_serial *serial)
अणु
	काष्ठा f81534_serial_निजी *serial_priv =
			usb_get_serial_data(serial);
	काष्ठा usb_serial_port *port;
	पूर्णांक error = 0;
	पूर्णांक status;
	माप_प्रकार i;

	/*
	 * We'll register port 0 bulkin when port had opened, It'll take all
	 * port received data, MSR रेजिस्टर change and TX_EMPTY inक्रमmation.
	 */
	mutex_lock(&serial_priv->urb_mutex);

	अगर (serial_priv->खोलोed_port) अणु
		status = f81534_submit_पढ़ो_urb(serial, GFP_NOIO);
		अगर (status) अणु
			mutex_unlock(&serial_priv->urb_mutex);
			वापस status;
		पूर्ण
	पूर्ण

	mutex_unlock(&serial_priv->urb_mutex);

	क्रम (i = 0; i < serial->num_ports; i++) अणु
		port = serial->port[i];
		अगर (!tty_port_initialized(&port->port))
			जारी;

		status = f81534_submit_ग_लिखोr(port, GFP_NOIO);
		अगर (status) अणु
			dev_err(&port->dev, "%s: submit failed\n", __func__);
			++error;
		पूर्ण
	पूर्ण

	अगर (error)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल काष्ठा usb_serial_driver f81534_device = अणु
	.driver = अणु
		   .owner = THIS_MODULE,
		   .name = "f81534",
	पूर्ण,
	.description =		DRIVER_DESC,
	.id_table =		f81534_id_table,
	.num_bulk_in =		1,
	.num_bulk_out =		1,
	.खोलो =			f81534_खोलो,
	.बंद =		f81534_बंद,
	.ग_लिखो =		f81534_ग_लिखो,
	.tx_empty =		f81534_tx_empty,
	.calc_num_ports =	f81534_calc_num_ports,
	.port_probe =		f81534_port_probe,
	.port_हटाओ =		f81534_port_हटाओ,
	.अवरोध_ctl =		f81534_अवरोध_ctl,
	.dtr_rts =		f81534_dtr_rts,
	.process_पढ़ो_urb =	f81534_process_पढ़ो_urb,
	.get_serial =		f81534_get_serial_info,
	.tiocmget =		f81534_tiocmget,
	.tiocmset =		f81534_tiocmset,
	.ग_लिखो_bulk_callback =	f81534_ग_लिखो_usb_callback,
	.set_termios =		f81534_set_termios,
	.resume =		f81534_resume,
पूर्ण;

अटल काष्ठा usb_serial_driver *स्थिर serial_drivers[] = अणु
	&f81534_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, f81534_id_table);

MODULE_DEVICE_TABLE(usb, f81534_id_table);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Peter Hong <Peter_Hong@fintek.com.tw>");
MODULE_AUTHOR("Tom Tsai <Tom_Tsai@fintek.com.tw>");
MODULE_LICENSE("GPL");
