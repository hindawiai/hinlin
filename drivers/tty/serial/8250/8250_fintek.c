<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Probe क्रम F81216A LPC to 4 UART
 *
 *  Copyright (C) 2014-2016 Ricarकरो Ribalda, Qtechnology A/S
 */
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pnp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/irq.h>
#समावेश  "8250.h"

#घोषणा ADDR_PORT 0
#घोषणा DATA_PORT 1
#घोषणा EXIT_KEY 0xAA
#घोषणा CHIP_ID1  0x20
#घोषणा CHIP_ID2  0x21
#घोषणा CHIP_ID_F81865 0x0407
#घोषणा CHIP_ID_F81866 0x1010
#घोषणा CHIP_ID_F81966 0x0215
#घोषणा CHIP_ID_F81216AD 0x1602
#घोषणा CHIP_ID_F81216H 0x0501
#घोषणा CHIP_ID_F81216 0x0802
#घोषणा VENDOR_ID1 0x23
#घोषणा VENDOR_ID1_VAL 0x19
#घोषणा VENDOR_ID2 0x24
#घोषणा VENDOR_ID2_VAL 0x34
#घोषणा IO_ADDR1 0x61
#घोषणा IO_ADDR2 0x60
#घोषणा LDN 0x7

#घोषणा FINTEK_IRQ_MODE	0x70
#घोषणा IRQ_SHARE	BIT(4)
#घोषणा IRQ_MODE_MASK	(BIT(6) | BIT(5))
#घोषणा IRQ_LEVEL_LOW	0
#घोषणा IRQ_EDGE_HIGH	BIT(5)

/*
 * F81216H घड़ी source रेजिस्टर, the value and mask is the same with F81866,
 * but it's on F0h.
 *
 * Clock speeds क्रम UART (रेजिस्टर F0h)
 * 00: 1.8432MHz.
 * 01: 18.432MHz.
 * 10: 24MHz.
 * 11: 14.769MHz.
 */
#घोषणा RS485  0xF0
#घोषणा RTS_INVERT BIT(5)
#घोषणा RS485_URA BIT(4)
#घोषणा RXW4C_IRA BIT(3)
#घोषणा TXW4C_IRA BIT(2)

#घोषणा FIFO_CTRL		0xF6
#घोषणा FIFO_MODE_MASK		(BIT(1) | BIT(0))
#घोषणा FIFO_MODE_128		(BIT(1) | BIT(0))
#घोषणा RXFTHR_MODE_MASK	(BIT(5) | BIT(4))
#घोषणा RXFTHR_MODE_4X		BIT(5)

#घोषणा F81216_LDN_LOW	0x0
#घोषणा F81216_LDN_HIGH	0x4

/*
 * F81866/966 रेजिस्टरs
 *
 * The IRQ setting mode of F81866/966 is not the same with F81216 series.
 *	Level/Low: IRQ_MODE0:0, IRQ_MODE1:0
 *	Edge/High: IRQ_MODE0:1, IRQ_MODE1:0
 *
 * Clock speeds क्रम UART (रेजिस्टर F2h)
 * 00: 1.8432MHz.
 * 01: 18.432MHz.
 * 10: 24MHz.
 * 11: 14.769MHz.
 */
#घोषणा F81866_IRQ_MODE		0xf0
#घोषणा F81866_IRQ_SHARE	BIT(0)
#घोषणा F81866_IRQ_MODE0	BIT(1)

#घोषणा F81866_FIFO_CTRL	FIFO_CTRL
#घोषणा F81866_IRQ_MODE1	BIT(3)

#घोषणा F81866_LDN_LOW		0x10
#घोषणा F81866_LDN_HIGH		0x16

#घोषणा F81866_UART_CLK 0xF2
#घोषणा F81866_UART_CLK_MASK (BIT(1) | BIT(0))
#घोषणा F81866_UART_CLK_1_8432MHZ 0
#घोषणा F81866_UART_CLK_14_769MHZ (BIT(1) | BIT(0))
#घोषणा F81866_UART_CLK_18_432MHZ BIT(0)
#घोषणा F81866_UART_CLK_24MHZ BIT(1)

काष्ठा fपूर्णांकek_8250 अणु
	u16 pid;
	u16 base_port;
	u8 index;
	u8 key;
पूर्ण;

अटल u8 sio_पढ़ो_reg(काष्ठा fपूर्णांकek_8250 *pdata, u8 reg)
अणु
	outb(reg, pdata->base_port + ADDR_PORT);
	वापस inb(pdata->base_port + DATA_PORT);
पूर्ण

अटल व्योम sio_ग_लिखो_reg(काष्ठा fपूर्णांकek_8250 *pdata, u8 reg, u8 data)
अणु
	outb(reg, pdata->base_port + ADDR_PORT);
	outb(data, pdata->base_port + DATA_PORT);
पूर्ण

अटल व्योम sio_ग_लिखो_mask_reg(काष्ठा fपूर्णांकek_8250 *pdata, u8 reg, u8 mask,
			       u8 data)
अणु
	u8 पंचांगp;

	पंचांगp = (sio_पढ़ो_reg(pdata, reg) & ~mask) | (mask & data);
	sio_ग_लिखो_reg(pdata, reg, पंचांगp);
पूर्ण

अटल पूर्णांक fपूर्णांकek_8250_enter_key(u16 base_port, u8 key)
अणु
	अगर (!request_muxed_region(base_port, 2, "8250_fintek"))
		वापस -EBUSY;

	/* Force to deactive all SuperIO in this base_port */
	outb(EXIT_KEY, base_port + ADDR_PORT);

	outb(key, base_port + ADDR_PORT);
	outb(key, base_port + ADDR_PORT);
	वापस 0;
पूर्ण

अटल व्योम fपूर्णांकek_8250_निकास_key(u16 base_port)
अणु

	outb(EXIT_KEY, base_port + ADDR_PORT);
	release_region(base_port + ADDR_PORT, 2);
पूर्ण

अटल पूर्णांक fपूर्णांकek_8250_check_id(काष्ठा fपूर्णांकek_8250 *pdata)
अणु
	u16 chip;

	अगर (sio_पढ़ो_reg(pdata, VENDOR_ID1) != VENDOR_ID1_VAL)
		वापस -ENODEV;

	अगर (sio_पढ़ो_reg(pdata, VENDOR_ID2) != VENDOR_ID2_VAL)
		वापस -ENODEV;

	chip = sio_पढ़ो_reg(pdata, CHIP_ID1);
	chip |= sio_पढ़ो_reg(pdata, CHIP_ID2) << 8;

	चयन (chip) अणु
	हाल CHIP_ID_F81865:
	हाल CHIP_ID_F81866:
	हाल CHIP_ID_F81966:
	हाल CHIP_ID_F81216AD:
	हाल CHIP_ID_F81216H:
	हाल CHIP_ID_F81216:
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	pdata->pid = chip;
	वापस 0;
पूर्ण

अटल पूर्णांक fपूर्णांकek_8250_get_ldn_range(काष्ठा fपूर्णांकek_8250 *pdata, पूर्णांक *min,
				     पूर्णांक *max)
अणु
	चयन (pdata->pid) अणु
	हाल CHIP_ID_F81966:
	हाल CHIP_ID_F81865:
	हाल CHIP_ID_F81866:
		*min = F81866_LDN_LOW;
		*max = F81866_LDN_HIGH;
		वापस 0;

	हाल CHIP_ID_F81216AD:
	हाल CHIP_ID_F81216H:
	हाल CHIP_ID_F81216:
		*min = F81216_LDN_LOW;
		*max = F81216_LDN_HIGH;
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक fपूर्णांकek_8250_rs485_config(काष्ठा uart_port *port,
			      काष्ठा serial_rs485 *rs485)
अणु
	uपूर्णांक8_t config = 0;
	काष्ठा fपूर्णांकek_8250 *pdata = port->निजी_data;

	अगर (!pdata)
		वापस -EINVAL;

	/* Hardware करो not support same RTS level on send and receive */
	अगर (!(rs485->flags & SER_RS485_RTS_ON_SEND) ==
			!(rs485->flags & SER_RS485_RTS_AFTER_SEND))
		वापस -EINVAL;

	अगर (rs485->flags & SER_RS485_ENABLED) अणु
		स_रखो(rs485->padding, 0, माप(rs485->padding));
		config |= RS485_URA;
	पूर्ण अन्यथा अणु
		स_रखो(rs485, 0, माप(*rs485));
	पूर्ण

	rs485->flags &= SER_RS485_ENABLED | SER_RS485_RTS_ON_SEND |
			SER_RS485_RTS_AFTER_SEND;

	/* Only the first port supports delays */
	अगर (pdata->index) अणु
		rs485->delay_rts_beक्रमe_send = 0;
		rs485->delay_rts_after_send = 0;
	पूर्ण

	अगर (rs485->delay_rts_beक्रमe_send) अणु
		rs485->delay_rts_beक्रमe_send = 1;
		config |= TXW4C_IRA;
	पूर्ण

	अगर (rs485->delay_rts_after_send) अणु
		rs485->delay_rts_after_send = 1;
		config |= RXW4C_IRA;
	पूर्ण

	अगर (rs485->flags & SER_RS485_RTS_ON_SEND)
		config |= RTS_INVERT;

	अगर (fपूर्णांकek_8250_enter_key(pdata->base_port, pdata->key))
		वापस -EBUSY;

	sio_ग_लिखो_reg(pdata, LDN, pdata->index);
	sio_ग_लिखो_reg(pdata, RS485, config);
	fपूर्णांकek_8250_निकास_key(pdata->base_port);

	port->rs485 = *rs485;

	वापस 0;
पूर्ण

अटल व्योम fपूर्णांकek_8250_set_irq_mode(काष्ठा fपूर्णांकek_8250 *pdata, bool is_level)
अणु
	sio_ग_लिखो_reg(pdata, LDN, pdata->index);

	चयन (pdata->pid) अणु
	हाल CHIP_ID_F81966:
	हाल CHIP_ID_F81866:
		sio_ग_लिखो_mask_reg(pdata, F81866_FIFO_CTRL, F81866_IRQ_MODE1,
				   0);
		fallthrough;
	हाल CHIP_ID_F81865:
		sio_ग_लिखो_mask_reg(pdata, F81866_IRQ_MODE, F81866_IRQ_SHARE,
				   F81866_IRQ_SHARE);
		sio_ग_लिखो_mask_reg(pdata, F81866_IRQ_MODE, F81866_IRQ_MODE0,
				   is_level ? 0 : F81866_IRQ_MODE0);
		अवरोध;

	हाल CHIP_ID_F81216AD:
	हाल CHIP_ID_F81216H:
	हाल CHIP_ID_F81216:
		sio_ग_लिखो_mask_reg(pdata, FINTEK_IRQ_MODE, IRQ_SHARE,
				   IRQ_SHARE);
		sio_ग_लिखो_mask_reg(pdata, FINTEK_IRQ_MODE, IRQ_MODE_MASK,
				   is_level ? IRQ_LEVEL_LOW : IRQ_EDGE_HIGH);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम fपूर्णांकek_8250_set_max_fअगरo(काष्ठा fपूर्णांकek_8250 *pdata)
अणु
	चयन (pdata->pid) अणु
	हाल CHIP_ID_F81216H: /* 128Bytes FIFO */
	हाल CHIP_ID_F81966:
	हाल CHIP_ID_F81866:
		sio_ग_लिखो_mask_reg(pdata, FIFO_CTRL,
				   FIFO_MODE_MASK | RXFTHR_MODE_MASK,
				   FIFO_MODE_128 | RXFTHR_MODE_4X);
		अवरोध;

	शेष: /* Default 16Bytes FIFO */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम fपूर्णांकek_8250_जाओ_highspeed(काष्ठा uart_8250_port *uart,
			      काष्ठा fपूर्णांकek_8250 *pdata)
अणु
	sio_ग_लिखो_reg(pdata, LDN, pdata->index);

	चयन (pdata->pid) अणु
	हाल CHIP_ID_F81966:
	हाल CHIP_ID_F81866: /* set uart घड़ी क्रम high speed serial mode */
		sio_ग_लिखो_mask_reg(pdata, F81866_UART_CLK,
			F81866_UART_CLK_MASK,
			F81866_UART_CLK_14_769MHZ);

		uart->port.uartclk = 921600 * 16;
		अवरोध;
	शेष: /* leave घड़ी speed untouched */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम fपूर्णांकek_8250_set_termios(काष्ठा uart_port *port,
				    काष्ठा ktermios *termios,
				    काष्ठा ktermios *old)
अणु
	काष्ठा fपूर्णांकek_8250 *pdata = port->निजी_data;
	अचिन्हित पूर्णांक baud = tty_termios_baud_rate(termios);
	पूर्णांक i;
	u8 reg;
	अटल u32 baudrate_table[] = अणु115200, 921600, 1152000, 1500000पूर्ण;
	अटल u8 घड़ी_प्रकारable[] = अणु F81866_UART_CLK_1_8432MHZ,
			F81866_UART_CLK_14_769MHZ, F81866_UART_CLK_18_432MHZ,
			F81866_UART_CLK_24MHZ पूर्ण;

	/*
	 * We'll use serial8250_do_set_termios() for baud = 0, otherwise It'll
	 * crash on baudrate_table[i] % baud with "division by zero".
	 */
	अगर (!baud)
		जाओ निकास;

	चयन (pdata->pid) अणु
	हाल CHIP_ID_F81216H:
		reg = RS485;
		अवरोध;
	हाल CHIP_ID_F81966:
	हाल CHIP_ID_F81866:
		reg = F81866_UART_CLK;
		अवरोध;
	शेष:
		/* Don't change घड़ीsource with unknown PID */
		dev_warn(port->dev,
			"%s: pid: %x Not support. use default set_termios.\n",
			__func__, pdata->pid);
		जाओ निकास;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(baudrate_table); ++i) अणु
		अगर (baud > baudrate_table[i] || baudrate_table[i] % baud != 0)
			जारी;

		अगर (port->uartclk == baudrate_table[i] * 16)
			अवरोध;

		अगर (fपूर्णांकek_8250_enter_key(pdata->base_port, pdata->key))
			जारी;

		port->uartclk = baudrate_table[i] * 16;

		sio_ग_लिखो_reg(pdata, LDN, pdata->index);
		sio_ग_लिखो_mask_reg(pdata, reg, F81866_UART_CLK_MASK,
				घड़ी_प्रकारable[i]);

		fपूर्णांकek_8250_निकास_key(pdata->base_port);
		अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(baudrate_table)) अणु
		baud = tty_termios_baud_rate(old);
		tty_termios_encode_baud_rate(termios, baud, baud);
	पूर्ण

निकास:
	serial8250_करो_set_termios(port, termios, old);
पूर्ण

अटल व्योम fपूर्णांकek_8250_set_termios_handler(काष्ठा uart_8250_port *uart)
अणु
	काष्ठा fपूर्णांकek_8250 *pdata = uart->port.निजी_data;

	चयन (pdata->pid) अणु
	हाल CHIP_ID_F81216H:
	हाल CHIP_ID_F81966:
	हाल CHIP_ID_F81866:
		uart->port.set_termios = fपूर्णांकek_8250_set_termios;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक probe_setup_port(काष्ठा fपूर्णांकek_8250 *pdata,
					काष्ठा uart_8250_port *uart)
अणु
	अटल स्थिर u16 addr[] = अणु0x4e, 0x2eपूर्ण;
	अटल स्थिर u8 keys[] = अणु0x77, 0xa0, 0x87, 0x67पूर्ण;
	काष्ठा irq_data *irq_data;
	bool level_mode = false;
	पूर्णांक i, j, k, min, max;

	क्रम (i = 0; i < ARRAY_SIZE(addr); i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(keys); j++) अणु
			pdata->base_port = addr[i];
			pdata->key = keys[j];

			अगर (fपूर्णांकek_8250_enter_key(addr[i], keys[j]))
				जारी;
			अगर (fपूर्णांकek_8250_check_id(pdata) ||
			    fपूर्णांकek_8250_get_ldn_range(pdata, &min, &max)) अणु
				fपूर्णांकek_8250_निकास_key(addr[i]);
				जारी;
			पूर्ण

			क्रम (k = min; k < max; k++) अणु
				u16 aux;

				sio_ग_लिखो_reg(pdata, LDN, k);
				aux = sio_पढ़ो_reg(pdata, IO_ADDR1);
				aux |= sio_पढ़ो_reg(pdata, IO_ADDR2) << 8;
				अगर (aux != uart->port.iobase)
					जारी;

				pdata->index = k;

				irq_data = irq_get_irq_data(uart->port.irq);
				अगर (irq_data)
					level_mode =
						irqd_is_level_type(irq_data);

				fपूर्णांकek_8250_set_irq_mode(pdata, level_mode);
				fपूर्णांकek_8250_set_max_fअगरo(pdata);
				fपूर्णांकek_8250_जाओ_highspeed(uart, pdata);

				fपूर्णांकek_8250_निकास_key(addr[i]);

				वापस 0;
			पूर्ण

			fपूर्णांकek_8250_निकास_key(addr[i]);
		पूर्ण
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल व्योम fपूर्णांकek_8250_set_rs485_handler(काष्ठा uart_8250_port *uart)
अणु
	काष्ठा fपूर्णांकek_8250 *pdata = uart->port.निजी_data;

	चयन (pdata->pid) अणु
	हाल CHIP_ID_F81216AD:
	हाल CHIP_ID_F81216H:
	हाल CHIP_ID_F81966:
	हाल CHIP_ID_F81866:
	हाल CHIP_ID_F81865:
		uart->port.rs485_config = fपूर्णांकek_8250_rs485_config;
		अवरोध;

	शेष: /* No RS485 Auto direction functional */
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक fपूर्णांकek_8250_probe(काष्ठा uart_8250_port *uart)
अणु
	काष्ठा fपूर्णांकek_8250 *pdata;
	काष्ठा fपूर्णांकek_8250 probe_data;

	अगर (probe_setup_port(&probe_data, uart))
		वापस -ENODEV;

	pdata = devm_kzalloc(uart->port.dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	स_नकल(pdata, &probe_data, माप(probe_data));
	uart->port.निजी_data = pdata;
	fपूर्णांकek_8250_set_rs485_handler(uart);
	fपूर्णांकek_8250_set_termios_handler(uart);

	वापस 0;
पूर्ण
