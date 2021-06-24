<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MEN 16z135 High Speed UART
 *
 * Copyright (C) 2014 MEN Mikroelektronik GmbH (www.men.de)
 * Author: Johannes Thumshirn <johannes.thumshirn@men.de>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":" fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/tty_flip.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mcb.h>

#घोषणा MEN_Z135_MAX_PORTS		12
#घोषणा MEN_Z135_BASECLK		29491200
#घोषणा MEN_Z135_FIFO_SIZE		1024
#घोषणा MEN_Z135_FIFO_WATERMARK		1020

#घोषणा MEN_Z135_STAT_REG		0x0
#घोषणा MEN_Z135_RX_RAM			0x4
#घोषणा MEN_Z135_TX_RAM			0x400
#घोषणा MEN_Z135_RX_CTRL		0x800
#घोषणा MEN_Z135_TX_CTRL		0x804
#घोषणा MEN_Z135_CONF_REG		0x808
#घोषणा MEN_Z135_UART_FREQ		0x80c
#घोषणा MEN_Z135_BAUD_REG		0x810
#घोषणा MEN_Z135_TIMEOUT		0x814

#घोषणा IRQ_ID(x) ((x) & 0x1f)

#घोषणा MEN_Z135_IER_RXCIEN BIT(0)		/* RX Space IRQ */
#घोषणा MEN_Z135_IER_TXCIEN BIT(1)		/* TX Space IRQ */
#घोषणा MEN_Z135_IER_RLSIEN BIT(2)		/* Receiver Line Status IRQ */
#घोषणा MEN_Z135_IER_MSIEN  BIT(3)		/* Modem Status IRQ */
#घोषणा MEN_Z135_ALL_IRQS (MEN_Z135_IER_RXCIEN		\
				| MEN_Z135_IER_RLSIEN	\
				| MEN_Z135_IER_MSIEN	\
				| MEN_Z135_IER_TXCIEN)

#घोषणा MEN_Z135_MCR_DTR	BIT(24)
#घोषणा MEN_Z135_MCR_RTS	BIT(25)
#घोषणा MEN_Z135_MCR_OUT1	BIT(26)
#घोषणा MEN_Z135_MCR_OUT2	BIT(27)
#घोषणा MEN_Z135_MCR_LOOP	BIT(28)
#घोषणा MEN_Z135_MCR_RCFC	BIT(29)

#घोषणा MEN_Z135_MSR_DCTS	BIT(0)
#घोषणा MEN_Z135_MSR_DDSR	BIT(1)
#घोषणा MEN_Z135_MSR_DRI	BIT(2)
#घोषणा MEN_Z135_MSR_DDCD	BIT(3)
#घोषणा MEN_Z135_MSR_CTS	BIT(4)
#घोषणा MEN_Z135_MSR_DSR	BIT(5)
#घोषणा MEN_Z135_MSR_RI		BIT(6)
#घोषणा MEN_Z135_MSR_DCD	BIT(7)

#घोषणा MEN_Z135_LCR_SHIFT 8	/* LCR shअगरt mask */

#घोषणा MEN_Z135_WL5 0		/* CS5 */
#घोषणा MEN_Z135_WL6 1		/* CS6 */
#घोषणा MEN_Z135_WL7 2		/* CS7 */
#घोषणा MEN_Z135_WL8 3		/* CS8 */

#घोषणा MEN_Z135_STB_SHIFT 2	/* Stopbits */
#घोषणा MEN_Z135_NSTB1 0
#घोषणा MEN_Z135_NSTB2 1

#घोषणा MEN_Z135_PEN_SHIFT 3	/* Parity enable */
#घोषणा MEN_Z135_PAR_DIS 0
#घोषणा MEN_Z135_PAR_ENA 1

#घोषणा MEN_Z135_PTY_SHIFT 4	/* Parity type */
#घोषणा MEN_Z135_PTY_ODD 0
#घोषणा MEN_Z135_PTY_EVN 1

#घोषणा MEN_Z135_LSR_DR BIT(0)
#घोषणा MEN_Z135_LSR_OE BIT(1)
#घोषणा MEN_Z135_LSR_PE BIT(2)
#घोषणा MEN_Z135_LSR_FE BIT(3)
#घोषणा MEN_Z135_LSR_BI BIT(4)
#घोषणा MEN_Z135_LSR_THEP BIT(5)
#घोषणा MEN_Z135_LSR_TEXP BIT(6)
#घोषणा MEN_Z135_LSR_RXFIFOERR BIT(7)

#घोषणा MEN_Z135_IRQ_ID_RLS BIT(0)
#घोषणा MEN_Z135_IRQ_ID_RDA BIT(1)
#घोषणा MEN_Z135_IRQ_ID_CTI BIT(2)
#घोषणा MEN_Z135_IRQ_ID_TSA BIT(3)
#घोषणा MEN_Z135_IRQ_ID_MST BIT(4)

#घोषणा LCR(x) (((x) >> MEN_Z135_LCR_SHIFT) & 0xff)

#घोषणा BYTES_TO_ALIGN(x) ((x) & 0x3)

अटल पूर्णांक line;

अटल पूर्णांक txlvl = 5;
module_param(txlvl, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(txlvl, "TX IRQ trigger level 0-7, default 5 (128 byte)");

अटल पूर्णांक rxlvl = 6;
module_param(rxlvl, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(rxlvl, "RX IRQ trigger level 0-7, default 6 (256 byte)");

अटल पूर्णांक align;
module_param(align, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(align, "Keep hardware FIFO write pointer aligned, default 0");

अटल uपूर्णांक rx_समयout;
module_param(rx_समयout, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(rx_समयout, "RX timeout. "
		"Timeout in seconds = (timeout_reg * baud_reg * 4) / freq_reg");

काष्ठा men_z135_port अणु
	काष्ठा uart_port port;
	काष्ठा mcb_device *mdev;
	काष्ठा resource *mem;
	अचिन्हित अक्षर *rxbuf;
	u32 stat_reg;
	spinlock_t lock;
	bool स्वतःmode;
पूर्ण;
#घोषणा to_men_z135(port) container_of((port), काष्ठा men_z135_port, port)

/**
 * men_z135_reg_set() - Set value in रेजिस्टर
 * @uart: The UART port
 * @addr: Register address
 * @val: value to set
 */
अटल अंतरभूत व्योम men_z135_reg_set(काष्ठा men_z135_port *uart,
				u32 addr, u32 val)
अणु
	काष्ठा uart_port *port = &uart->port;
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&uart->lock, flags);

	reg = ioपढ़ो32(port->membase + addr);
	reg |= val;
	ioग_लिखो32(reg, port->membase + addr);

	spin_unlock_irqrestore(&uart->lock, flags);
पूर्ण

/**
 * men_z135_reg_clr() - Unset value in रेजिस्टर
 * @uart: The UART port
 * @addr: Register address
 * @val: value to clear
 */
अटल व्योम men_z135_reg_clr(काष्ठा men_z135_port *uart,
				u32 addr, u32 val)
अणु
	काष्ठा uart_port *port = &uart->port;
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&uart->lock, flags);

	reg = ioपढ़ो32(port->membase + addr);
	reg &= ~val;
	ioग_लिखो32(reg, port->membase + addr);

	spin_unlock_irqrestore(&uart->lock, flags);
पूर्ण

/**
 * men_z135_handle_modem_status() - Handle change of modem status
 * @uart: The UART port
 *
 * Handle change of modem status रेजिस्टर. This is करोne by पढ़ोing the "delta"
 * versions of DCD (Data Carrier Detect) and CTS (Clear To Send).
 */
अटल व्योम men_z135_handle_modem_status(काष्ठा men_z135_port *uart)
अणु
	u8 msr;

	msr = (uart->stat_reg >> 8) & 0xff;

	अगर (msr & MEN_Z135_MSR_DDCD)
		uart_handle_dcd_change(&uart->port,
				msr & MEN_Z135_MSR_DCD);
	अगर (msr & MEN_Z135_MSR_DCTS)
		uart_handle_cts_change(&uart->port,
				msr & MEN_Z135_MSR_CTS);
पूर्ण

अटल व्योम men_z135_handle_lsr(काष्ठा men_z135_port *uart)
अणु
	काष्ठा uart_port *port = &uart->port;
	u8 lsr;

	lsr = (uart->stat_reg >> 16) & 0xff;

	अगर (lsr & MEN_Z135_LSR_OE)
		port->icount.overrun++;
	अगर (lsr & MEN_Z135_LSR_PE)
		port->icount.parity++;
	अगर (lsr & MEN_Z135_LSR_FE)
		port->icount.frame++;
	अगर (lsr & MEN_Z135_LSR_BI) अणु
		port->icount.brk++;
		uart_handle_अवरोध(port);
	पूर्ण
पूर्ण

/**
 * get_rx_fअगरo_content() - Get the number of bytes in RX FIFO
 * @uart: The UART port
 *
 * Read RXC रेजिस्टर from hardware and वापस current FIFO fill size.
 */
अटल u16 get_rx_fअगरo_content(काष्ठा men_z135_port *uart)
अणु
	काष्ठा uart_port *port = &uart->port;
	u32 stat_reg;
	u16 rxc;
	u8 rxc_lo;
	u8 rxc_hi;

	stat_reg = ioपढ़ो32(port->membase + MEN_Z135_STAT_REG);
	rxc_lo = stat_reg >> 24;
	rxc_hi = (stat_reg & 0xC0) >> 6;

	rxc = rxc_lo | (rxc_hi << 8);

	वापस rxc;
पूर्ण

/**
 * men_z135_handle_rx() - RX tasklet routine
 * @uart: Poपूर्णांकer to काष्ठा men_z135_port
 *
 * Copy from RX FIFO and acknowledge number of bytes copied.
 */
अटल व्योम men_z135_handle_rx(काष्ठा men_z135_port *uart)
अणु
	काष्ठा uart_port *port = &uart->port;
	काष्ठा tty_port *tport = &port->state->port;
	पूर्णांक copied;
	u16 size;
	पूर्णांक room;

	size = get_rx_fअगरo_content(uart);

	अगर (size == 0)
		वापस;

	/* Aव्योम accidently accessing TX FIFO instead of RX FIFO. Last
	 * दीर्घword in RX FIFO cannot be पढ़ो.(0x004-0x3FF)
	 */
	अगर (size > MEN_Z135_FIFO_WATERMARK)
		size = MEN_Z135_FIFO_WATERMARK;

	room = tty_buffer_request_room(tport, size);
	अगर (room != size)
		dev_warn(&uart->mdev->dev,
			"Not enough room in flip buffer, truncating to %d\n",
			room);

	अगर (room == 0)
		वापस;

	स_नकल_fromio(uart->rxbuf, port->membase + MEN_Z135_RX_RAM, room);
	/* Be sure to first copy all data and then acknowledge it */
	mb();
	ioग_लिखो32(room, port->membase +  MEN_Z135_RX_CTRL);

	copied = tty_insert_flip_string(tport, uart->rxbuf, room);
	अगर (copied != room)
		dev_warn(&uart->mdev->dev,
			"Only copied %d instead of %d bytes\n",
			copied, room);

	port->icount.rx += copied;

	tty_flip_buffer_push(tport);

पूर्ण

/**
 * men_z135_handle_tx() - TX tasklet routine
 * @uart: Poपूर्णांकer to काष्ठा men_z135_port
 *
 */
अटल व्योम men_z135_handle_tx(काष्ठा men_z135_port *uart)
अणु
	काष्ठा uart_port *port = &uart->port;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	u32 txc;
	u32 wptr;
	पूर्णांक qlen;
	पूर्णांक n;
	पूर्णांक txमुक्त;
	पूर्णांक head;
	पूर्णांक tail;
	पूर्णांक s;

	अगर (uart_circ_empty(xmit))
		जाओ out;

	अगर (uart_tx_stopped(port))
		जाओ out;

	अगर (port->x_अक्षर)
		जाओ out;

	/* calculate bytes to copy */
	qlen = uart_circ_अक्षरs_pending(xmit);
	अगर (qlen <= 0)
		जाओ out;

	wptr = ioपढ़ो32(port->membase + MEN_Z135_TX_CTRL);
	txc = (wptr >> 16) & 0x3ff;
	wptr &= 0x3ff;

	अगर (txc > MEN_Z135_FIFO_WATERMARK)
		txc = MEN_Z135_FIFO_WATERMARK;

	txमुक्त = MEN_Z135_FIFO_WATERMARK - txc;
	अगर (txमुक्त <= 0) अणु
		dev_err(&uart->mdev->dev,
			"Not enough room in TX FIFO have %d, need %d\n",
			txमुक्त, qlen);
		जाओ irq_en;
	पूर्ण

	/* अगर we're not aligned, it's better to copy only 1 or 2 bytes and
	 * then the rest.
	 */
	अगर (align && qlen >= 3 && BYTES_TO_ALIGN(wptr))
		n = 4 - BYTES_TO_ALIGN(wptr);
	अन्यथा अगर (qlen > txमुक्त)
		n = txमुक्त;
	अन्यथा
		n = qlen;

	अगर (n <= 0)
		जाओ irq_en;

	head = xmit->head & (UART_XMIT_SIZE - 1);
	tail = xmit->tail & (UART_XMIT_SIZE - 1);

	s = ((head >= tail) ? head : UART_XMIT_SIZE) - tail;
	n = min(n, s);

	स_नकल_toio(port->membase + MEN_Z135_TX_RAM, &xmit->buf[xmit->tail], n);
	xmit->tail = (xmit->tail + n) & (UART_XMIT_SIZE - 1);

	ioग_लिखो32(n & 0x3ff, port->membase + MEN_Z135_TX_CTRL);

	port->icount.tx += n;

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

irq_en:
	अगर (!uart_circ_empty(xmit))
		men_z135_reg_set(uart, MEN_Z135_CONF_REG, MEN_Z135_IER_TXCIEN);
	अन्यथा
		men_z135_reg_clr(uart, MEN_Z135_CONF_REG, MEN_Z135_IER_TXCIEN);

out:
	वापस;

पूर्ण

/**
 * men_z135_पूर्णांकr() - Handle legacy IRQs
 * @irq: The IRQ number
 * @data: Poपूर्णांकer to UART port
 *
 * Check IIR रेजिस्टर to find the cause of the पूर्णांकerrupt and handle it.
 * It is possible that multiple पूर्णांकerrupts reason bits are set and पढ़ोing
 * the IIR is a deकाष्ठाive पढ़ो, so we always need to check क्रम all possible
 * पूर्णांकerrupts and handle them.
 */
अटल irqवापस_t men_z135_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा men_z135_port *uart = (काष्ठा men_z135_port *)data;
	काष्ठा uart_port *port = &uart->port;
	bool handled = false;
	पूर्णांक irq_id;

	uart->stat_reg = ioपढ़ो32(port->membase + MEN_Z135_STAT_REG);
	irq_id = IRQ_ID(uart->stat_reg);

	अगर (!irq_id)
		जाओ out;

	spin_lock(&port->lock);
	/* It's save to ग_लिखो to IIR[7:6] RXC[9:8] */
	ioग_लिखो8(irq_id, port->membase + MEN_Z135_STAT_REG);

	अगर (irq_id & MEN_Z135_IRQ_ID_RLS) अणु
		men_z135_handle_lsr(uart);
		handled = true;
	पूर्ण

	अगर (irq_id & (MEN_Z135_IRQ_ID_RDA | MEN_Z135_IRQ_ID_CTI)) अणु
		अगर (irq_id & MEN_Z135_IRQ_ID_CTI)
			dev_dbg(&uart->mdev->dev, "Character Timeout Indication\n");
		men_z135_handle_rx(uart);
		handled = true;
	पूर्ण

	अगर (irq_id & MEN_Z135_IRQ_ID_TSA) अणु
		men_z135_handle_tx(uart);
		handled = true;
	पूर्ण

	अगर (irq_id & MEN_Z135_IRQ_ID_MST) अणु
		men_z135_handle_modem_status(uart);
		handled = true;
	पूर्ण

	spin_unlock(&port->lock);
out:
	वापस IRQ_RETVAL(handled);
पूर्ण

/**
 * men_z135_request_irq() - Request IRQ क्रम 16z135 core
 * @uart: z135 निजी uart port काष्ठाure
 *
 * Request an IRQ क्रम 16z135 to use. First try using MSI, अगर it fails
 * fall back to using legacy पूर्णांकerrupts.
 */
अटल पूर्णांक men_z135_request_irq(काष्ठा men_z135_port *uart)
अणु
	काष्ठा device *dev = &uart->mdev->dev;
	काष्ठा uart_port *port = &uart->port;
	पूर्णांक err = 0;

	err = request_irq(port->irq, men_z135_पूर्णांकr, IRQF_SHARED,
			"men_z135_intr", uart);
	अगर (err)
		dev_err(dev, "Error %d getting interrupt\n", err);

	वापस err;
पूर्ण

/**
 * men_z135_tx_empty() - Handle tx_empty call
 * @port: The UART port
 *
 * This function tests whether the TX FIFO and shअगरter क्रम the port
 * described by @port is empty.
 */
अटल अचिन्हित पूर्णांक men_z135_tx_empty(काष्ठा uart_port *port)
अणु
	u32 wptr;
	u16 txc;

	wptr = ioपढ़ो32(port->membase + MEN_Z135_TX_CTRL);
	txc = (wptr >> 16) & 0x3ff;

	अगर (txc == 0)
		वापस TIOCSER_TEMT;
	अन्यथा
		वापस 0;
पूर्ण

/**
 * men_z135_set_mctrl() - Set modem control lines
 * @port: The UART port
 * @mctrl: The modem control lines
 *
 * This function sets the modem control lines क्रम a port described by @port
 * to the state described by @mctrl
 */
अटल व्योम men_z135_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	u32 old;
	u32 conf_reg;

	conf_reg = old = ioपढ़ो32(port->membase + MEN_Z135_CONF_REG);
	अगर (mctrl & TIOCM_RTS)
		conf_reg |= MEN_Z135_MCR_RTS;
	अन्यथा
		conf_reg &= ~MEN_Z135_MCR_RTS;

	अगर (mctrl & TIOCM_DTR)
		conf_reg |= MEN_Z135_MCR_DTR;
	अन्यथा
		conf_reg &= ~MEN_Z135_MCR_DTR;

	अगर (mctrl & TIOCM_OUT1)
		conf_reg |= MEN_Z135_MCR_OUT1;
	अन्यथा
		conf_reg &= ~MEN_Z135_MCR_OUT1;

	अगर (mctrl & TIOCM_OUT2)
		conf_reg |= MEN_Z135_MCR_OUT2;
	अन्यथा
		conf_reg &= ~MEN_Z135_MCR_OUT2;

	अगर (mctrl & TIOCM_LOOP)
		conf_reg |= MEN_Z135_MCR_LOOP;
	अन्यथा
		conf_reg &= ~MEN_Z135_MCR_LOOP;

	अगर (conf_reg != old)
		ioग_लिखो32(conf_reg, port->membase + MEN_Z135_CONF_REG);
पूर्ण

/**
 * men_z135_get_mctrl() - Get modem control lines
 * @port: The UART port
 *
 * Retruns the current state of modem control inमाला_दो.
 */
अटल अचिन्हित पूर्णांक men_z135_get_mctrl(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक mctrl = 0;
	u8 msr;

	msr = ioपढ़ो8(port->membase + MEN_Z135_STAT_REG + 1);

	अगर (msr & MEN_Z135_MSR_CTS)
		mctrl |= TIOCM_CTS;
	अगर (msr & MEN_Z135_MSR_DSR)
		mctrl |= TIOCM_DSR;
	अगर (msr & MEN_Z135_MSR_RI)
		mctrl |= TIOCM_RI;
	अगर (msr & MEN_Z135_MSR_DCD)
		mctrl |= TIOCM_CAR;

	वापस mctrl;
पूर्ण

/**
 * men_z135_stop_tx() - Stop transmitting अक्षरacters
 * @port: The UART port
 *
 * Stop transmitting अक्षरacters. This might be due to CTS line becomming
 * inactive or the tty layer indicating we want to stop transmission due to
 * an XOFF अक्षरacter.
 */
अटल व्योम men_z135_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा men_z135_port *uart = to_men_z135(port);

	men_z135_reg_clr(uart, MEN_Z135_CONF_REG, MEN_Z135_IER_TXCIEN);
पूर्ण

/*
 * men_z135_disable_ms() - Disable Modem Status
 * port: The UART port
 *
 * Enable Modem Status IRQ.
 */
अटल व्योम men_z135_disable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा men_z135_port *uart = to_men_z135(port);

	men_z135_reg_clr(uart, MEN_Z135_CONF_REG, MEN_Z135_IER_MSIEN);
पूर्ण

/**
 * men_z135_start_tx() - Start transmitting अक्षरacters
 * @port: The UART port
 *
 * Start transmitting अक्षरacter. This actually करोesn't transmit anything, but
 * fires off the TX tasklet.
 */
अटल व्योम men_z135_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा men_z135_port *uart = to_men_z135(port);

	अगर (uart->स्वतःmode)
		men_z135_disable_ms(port);

	men_z135_handle_tx(uart);
पूर्ण

/**
 * men_z135_stop_rx() - Stop receiving अक्षरacters
 * @port: The UART port
 *
 * Stop receiving अक्षरacters; the port is in the process of being बंदd.
 */
अटल व्योम men_z135_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा men_z135_port *uart = to_men_z135(port);

	men_z135_reg_clr(uart, MEN_Z135_CONF_REG, MEN_Z135_IER_RXCIEN);
पूर्ण

/**
 * men_z135_enable_ms() - Enable Modem Status
 * @port: the port
 *
 * Enable Modem Status IRQ.
 */
अटल व्योम men_z135_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा men_z135_port *uart = to_men_z135(port);

	men_z135_reg_set(uart, MEN_Z135_CONF_REG, MEN_Z135_IER_MSIEN);
पूर्ण

अटल पूर्णांक men_z135_startup(काष्ठा uart_port *port)
अणु
	काष्ठा men_z135_port *uart = to_men_z135(port);
	पूर्णांक err;
	u32 conf_reg = 0;

	err = men_z135_request_irq(uart);
	अगर (err)
		वापस -ENODEV;

	conf_reg = ioपढ़ो32(port->membase + MEN_Z135_CONF_REG);

	/* Activate all but TX space available IRQ */
	conf_reg |= MEN_Z135_ALL_IRQS & ~MEN_Z135_IER_TXCIEN;
	conf_reg &= ~(0xff << 16);
	conf_reg |= (txlvl << 16);
	conf_reg |= (rxlvl << 20);

	ioग_लिखो32(conf_reg, port->membase + MEN_Z135_CONF_REG);

	अगर (rx_समयout)
		ioग_लिखो32(rx_समयout, port->membase + MEN_Z135_TIMEOUT);

	वापस 0;
पूर्ण

अटल व्योम men_z135_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा men_z135_port *uart = to_men_z135(port);
	u32 conf_reg = 0;

	conf_reg |= MEN_Z135_ALL_IRQS;

	men_z135_reg_clr(uart, MEN_Z135_CONF_REG, conf_reg);

	मुक्त_irq(uart->port.irq, uart);
पूर्ण

अटल व्योम men_z135_set_termios(काष्ठा uart_port *port,
				काष्ठा ktermios *termios,
				काष्ठा ktermios *old)
अणु
	काष्ठा men_z135_port *uart = to_men_z135(port);
	अचिन्हित पूर्णांक baud;
	u32 conf_reg;
	u32 bd_reg;
	u32 uart_freq;
	u8 lcr;

	conf_reg = ioपढ़ो32(port->membase + MEN_Z135_CONF_REG);
	lcr = LCR(conf_reg);

	/* byte size */
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		lcr |= MEN_Z135_WL5;
		अवरोध;
	हाल CS6:
		lcr |= MEN_Z135_WL6;
		अवरोध;
	हाल CS7:
		lcr |= MEN_Z135_WL7;
		अवरोध;
	हाल CS8:
		lcr |= MEN_Z135_WL8;
		अवरोध;
	पूर्ण

	/* stop bits */
	अगर (termios->c_cflag & CSTOPB)
		lcr |= MEN_Z135_NSTB2 << MEN_Z135_STB_SHIFT;

	/* parity */
	अगर (termios->c_cflag & PARENB) अणु
		lcr |= MEN_Z135_PAR_ENA << MEN_Z135_PEN_SHIFT;

		अगर (termios->c_cflag & PARODD)
			lcr |= MEN_Z135_PTY_ODD << MEN_Z135_PTY_SHIFT;
		अन्यथा
			lcr |= MEN_Z135_PTY_EVN << MEN_Z135_PTY_SHIFT;
	पूर्ण अन्यथा
		lcr |= MEN_Z135_PAR_DIS << MEN_Z135_PEN_SHIFT;

	conf_reg |= MEN_Z135_IER_MSIEN;
	अगर (termios->c_cflag & CRTSCTS) अणु
		conf_reg |= MEN_Z135_MCR_RCFC;
		uart->स्वतःmode = true;
		termios->c_cflag &= ~CLOCAL;
	पूर्ण अन्यथा अणु
		conf_reg &= ~MEN_Z135_MCR_RCFC;
		uart->स्वतःmode = false;
	पूर्ण

	termios->c_cflag &= ~CMSPAR; /* Mark/Space parity is not supported */

	conf_reg |= lcr << MEN_Z135_LCR_SHIFT;
	ioग_लिखो32(conf_reg, port->membase + MEN_Z135_CONF_REG);

	uart_freq = ioपढ़ो32(port->membase + MEN_Z135_UART_FREQ);
	अगर (uart_freq == 0)
		uart_freq = MEN_Z135_BASECLK;

	baud = uart_get_baud_rate(port, termios, old, 0, uart_freq / 16);

	spin_lock_irq(&port->lock);
	अगर (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);

	bd_reg = uart_freq / (4 * baud);
	ioग_लिखो32(bd_reg, port->membase + MEN_Z135_BAUD_REG);

	uart_update_समयout(port, termios->c_cflag, baud);
	spin_unlock_irq(&port->lock);
पूर्ण

अटल स्थिर अक्षर *men_z135_type(काष्ठा uart_port *port)
अणु
	वापस KBUILD_MODNAME;
पूर्ण

अटल व्योम men_z135_release_port(काष्ठा uart_port *port)
अणु
	काष्ठा men_z135_port *uart = to_men_z135(port);

	iounmap(port->membase);
	port->membase = शून्य;

	mcb_release_mem(uart->mem);
पूर्ण

अटल पूर्णांक men_z135_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा men_z135_port *uart = to_men_z135(port);
	काष्ठा mcb_device *mdev = uart->mdev;
	काष्ठा resource *mem;

	mem = mcb_request_mem(uart->mdev, dev_name(&mdev->dev));
	अगर (IS_ERR(mem))
		वापस PTR_ERR(mem);

	port->mapbase = mem->start;
	uart->mem = mem;

	port->membase = ioremap(mem->start, resource_size(mem));
	अगर (port->membase == शून्य) अणु
		mcb_release_mem(mem);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम men_z135_config_port(काष्ठा uart_port *port, पूर्णांक type)
अणु
	port->type = PORT_MEN_Z135;
	men_z135_request_port(port);
पूर्ण

अटल पूर्णांक men_z135_verअगरy_port(काष्ठा uart_port *port,
				काष्ठा serial_काष्ठा *serinfo)
अणु
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा uart_ops men_z135_ops = अणु
	.tx_empty = men_z135_tx_empty,
	.set_mctrl = men_z135_set_mctrl,
	.get_mctrl = men_z135_get_mctrl,
	.stop_tx = men_z135_stop_tx,
	.start_tx = men_z135_start_tx,
	.stop_rx = men_z135_stop_rx,
	.enable_ms = men_z135_enable_ms,
	.startup = men_z135_startup,
	.shutकरोwn = men_z135_shutकरोwn,
	.set_termios = men_z135_set_termios,
	.type = men_z135_type,
	.release_port = men_z135_release_port,
	.request_port = men_z135_request_port,
	.config_port = men_z135_config_port,
	.verअगरy_port = men_z135_verअगरy_port,
पूर्ण;

अटल काष्ठा uart_driver men_z135_driver = अणु
	.owner = THIS_MODULE,
	.driver_name = KBUILD_MODNAME,
	.dev_name = "ttyHSU",
	.major = 0,
	.minor = 0,
	.nr = MEN_Z135_MAX_PORTS,
पूर्ण;

/**
 * men_z135_probe() - Probe a z135 instance
 * @mdev: The MCB device
 * @id: The MCB device ID
 *
 * men_z135_probe करोes the basic setup of hardware resources and रेजिस्टरs the
 * new uart port to the tty layer.
 */
अटल पूर्णांक men_z135_probe(काष्ठा mcb_device *mdev,
			स्थिर काष्ठा mcb_device_id *id)
अणु
	काष्ठा men_z135_port *uart;
	काष्ठा resource *mem;
	काष्ठा device *dev;
	पूर्णांक err;

	dev = &mdev->dev;

	uart = devm_kzalloc(dev, माप(काष्ठा men_z135_port), GFP_KERNEL);
	अगर (!uart)
		वापस -ENOMEM;

	uart->rxbuf = (अचिन्हित अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!uart->rxbuf)
		वापस -ENOMEM;

	mem = &mdev->mem;

	mcb_set_drvdata(mdev, uart);

	uart->port.uartclk = MEN_Z135_BASECLK * 16;
	uart->port.fअगरosize = MEN_Z135_FIFO_SIZE;
	uart->port.iotype = UPIO_MEM;
	uart->port.ops = &men_z135_ops;
	uart->port.irq = mcb_get_irq(mdev);
	uart->port.iotype = UPIO_MEM;
	uart->port.flags = UPF_BOOT_AUTOCONF | UPF_IOREMAP;
	uart->port.line = line++;
	uart->port.dev = dev;
	uart->port.type = PORT_MEN_Z135;
	uart->port.mapbase = mem->start;
	uart->port.membase = शून्य;
	uart->mdev = mdev;

	spin_lock_init(&uart->lock);

	err = uart_add_one_port(&men_z135_driver, &uart->port);
	अगर (err)
		जाओ err;

	वापस 0;

err:
	मुक्त_page((अचिन्हित दीर्घ) uart->rxbuf);
	dev_err(dev, "Failed to add UART: %d\n", err);

	वापस err;
पूर्ण

/**
 * men_z135_हटाओ() - Remove a z135 instance from the प्रणाली
 *
 * @mdev: The MCB device
 */
अटल व्योम men_z135_हटाओ(काष्ठा mcb_device *mdev)
अणु
	काष्ठा men_z135_port *uart = mcb_get_drvdata(mdev);

	line--;
	uart_हटाओ_one_port(&men_z135_driver, &uart->port);
	मुक्त_page((अचिन्हित दीर्घ) uart->rxbuf);
पूर्ण

अटल स्थिर काष्ठा mcb_device_id men_z135_ids[] = अणु
	अणु .device = 0x87 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(mcb, men_z135_ids);

अटल काष्ठा mcb_driver mcb_driver = अणु
	.driver = अणु
		.name = "z135-uart",
		.owner = THIS_MODULE,
	पूर्ण,
	.probe = men_z135_probe,
	.हटाओ = men_z135_हटाओ,
	.id_table = men_z135_ids,
पूर्ण;

/**
 * men_z135_init() - Driver Registration Routine
 *
 * men_z135_init is the first routine called when the driver is loaded. All it
 * करोes is रेजिस्टर with the legacy MEN Chameleon subप्रणाली.
 */
अटल पूर्णांक __init men_z135_init(व्योम)
अणु
	पूर्णांक err;

	err = uart_रेजिस्टर_driver(&men_z135_driver);
	अगर (err) अणु
		pr_err("Failed to register UART: %d\n", err);
		वापस err;
	पूर्ण

	err = mcb_रेजिस्टर_driver(&mcb_driver);
	अगर  (err) अणु
		pr_err("Failed to register MCB driver: %d\n", err);
		uart_unरेजिस्टर_driver(&men_z135_driver);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
module_init(men_z135_init);

/**
 * men_z135_निकास() - Driver Exit Routine
 *
 * men_z135_निकास is called just beक्रमe the driver is हटाओd from memory.
 */
अटल व्योम __निकास men_z135_निकास(व्योम)
अणु
	mcb_unरेजिस्टर_driver(&mcb_driver);
	uart_unरेजिस्टर_driver(&men_z135_driver);
पूर्ण
module_निकास(men_z135_निकास);

MODULE_AUTHOR("Johannes Thumshirn <johannes.thumshirn@men.de>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MEN 16z135 High Speed UART");
MODULE_ALIAS("mcb:16z135");
MODULE_IMPORT_NS(MCB);
