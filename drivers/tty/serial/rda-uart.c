<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * RDA8810PL serial device driver
 *
 * Copyright RDA Microelectronics Company Limited
 * Copyright (c) 2017 Andreas Fथअrber
 * Copyright (c) 2018 Manivannan Sadhasivam
 */

#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

#घोषणा RDA_UART_PORT_NUM 3
#घोषणा RDA_UART_DEV_NAME "ttyRDA"

#घोषणा RDA_UART_CTRL		0x00
#घोषणा RDA_UART_STATUS		0x04
#घोषणा RDA_UART_RXTX_BUFFER	0x08
#घोषणा RDA_UART_IRQ_MASK	0x0c
#घोषणा RDA_UART_IRQ_CAUSE	0x10
#घोषणा RDA_UART_IRQ_TRIGGERS	0x14
#घोषणा RDA_UART_CMD_SET	0x18
#घोषणा RDA_UART_CMD_CLR	0x1c

/* UART_CTRL Bits */
#घोषणा RDA_UART_ENABLE			BIT(0)
#घोषणा RDA_UART_DBITS_8		BIT(1)
#घोषणा RDA_UART_TX_SBITS_2		BIT(2)
#घोषणा RDA_UART_PARITY_EN		BIT(3)
#घोषणा RDA_UART_PARITY(x)		(((x) & 0x3) << 4)
#घोषणा RDA_UART_PARITY_ODD		RDA_UART_PARITY(0)
#घोषणा RDA_UART_PARITY_EVEN		RDA_UART_PARITY(1)
#घोषणा RDA_UART_PARITY_SPACE		RDA_UART_PARITY(2)
#घोषणा RDA_UART_PARITY_MARK		RDA_UART_PARITY(3)
#घोषणा RDA_UART_DIV_MODE		BIT(20)
#घोषणा RDA_UART_IRDA_EN		BIT(21)
#घोषणा RDA_UART_DMA_EN			BIT(22)
#घोषणा RDA_UART_FLOW_CNT_EN		BIT(23)
#घोषणा RDA_UART_LOOP_BACK_EN		BIT(24)
#घोषणा RDA_UART_RX_LOCK_ERR		BIT(25)
#घोषणा RDA_UART_RX_BREAK_LEN(x)	(((x) & 0xf) << 28)

/* UART_STATUS Bits */
#घोषणा RDA_UART_RX_FIFO(x)		(((x) & 0x7f) << 0)
#घोषणा RDA_UART_RX_FIFO_MASK		(0x7f << 0)
#घोषणा RDA_UART_TX_FIFO(x)		(((x) & 0x1f) << 8)
#घोषणा RDA_UART_TX_FIFO_MASK		(0x1f << 8)
#घोषणा RDA_UART_TX_ACTIVE		BIT(14)
#घोषणा RDA_UART_RX_ACTIVE		BIT(15)
#घोषणा RDA_UART_RX_OVERFLOW_ERR	BIT(16)
#घोषणा RDA_UART_TX_OVERFLOW_ERR	BIT(17)
#घोषणा RDA_UART_RX_PARITY_ERR		BIT(18)
#घोषणा RDA_UART_RX_FRAMING_ERR		BIT(19)
#घोषणा RDA_UART_RX_BREAK_INT		BIT(20)
#घोषणा RDA_UART_DCTS			BIT(24)
#घोषणा RDA_UART_CTS			BIT(25)
#घोषणा RDA_UART_DTR			BIT(28)
#घोषणा RDA_UART_CLK_ENABLED		BIT(31)

/* UART_RXTX_BUFFER Bits */
#घोषणा RDA_UART_RX_DATA(x)		(((x) & 0xff) << 0)
#घोषणा RDA_UART_TX_DATA(x)		(((x) & 0xff) << 0)

/* UART_IRQ_MASK Bits */
#घोषणा RDA_UART_TX_MODEM_STATUS	BIT(0)
#घोषणा RDA_UART_RX_DATA_AVAILABLE	BIT(1)
#घोषणा RDA_UART_TX_DATA_NEEDED		BIT(2)
#घोषणा RDA_UART_RX_TIMEOUT		BIT(3)
#घोषणा RDA_UART_RX_LINE_ERR		BIT(4)
#घोषणा RDA_UART_TX_DMA_DONE		BIT(5)
#घोषणा RDA_UART_RX_DMA_DONE		BIT(6)
#घोषणा RDA_UART_RX_DMA_TIMEOUT		BIT(7)
#घोषणा RDA_UART_DTR_RISE		BIT(8)
#घोषणा RDA_UART_DTR_FALL		BIT(9)

/* UART_IRQ_CAUSE Bits */
#घोषणा RDA_UART_TX_MODEM_STATUS_U	BIT(16)
#घोषणा RDA_UART_RX_DATA_AVAILABLE_U	BIT(17)
#घोषणा RDA_UART_TX_DATA_NEEDED_U	BIT(18)
#घोषणा RDA_UART_RX_TIMEOUT_U		BIT(19)
#घोषणा RDA_UART_RX_LINE_ERR_U		BIT(20)
#घोषणा RDA_UART_TX_DMA_DONE_U		BIT(21)
#घोषणा RDA_UART_RX_DMA_DONE_U		BIT(22)
#घोषणा RDA_UART_RX_DMA_TIMEOUT_U	BIT(23)
#घोषणा RDA_UART_DTR_RISE_U		BIT(24)
#घोषणा RDA_UART_DTR_FALL_U		BIT(25)

/* UART_TRIGGERS Bits */
#घोषणा RDA_UART_RX_TRIGGER(x)		(((x) & 0x1f) << 0)
#घोषणा RDA_UART_TX_TRIGGER(x)		(((x) & 0xf) << 8)
#घोषणा RDA_UART_AFC_LEVEL(x)		(((x) & 0x1f) << 16)

/* UART_CMD_SET Bits */
#घोषणा RDA_UART_RI			BIT(0)
#घोषणा RDA_UART_DCD			BIT(1)
#घोषणा RDA_UART_DSR			BIT(2)
#घोषणा RDA_UART_TX_BREAK_CONTROL	BIT(3)
#घोषणा RDA_UART_TX_FINISH_N_WAIT	BIT(4)
#घोषणा RDA_UART_RTS			BIT(5)
#घोषणा RDA_UART_RX_FIFO_RESET		BIT(6)
#घोषणा RDA_UART_TX_FIFO_RESET		BIT(7)

#घोषणा RDA_UART_TX_FIFO_SIZE	16

अटल काष्ठा uart_driver rda_uart_driver;

काष्ठा rda_uart_port अणु
	काष्ठा uart_port port;
	काष्ठा clk *clk;
पूर्ण;

#घोषणा to_rda_uart_port(port) container_of(port, काष्ठा rda_uart_port, port)

अटल काष्ठा rda_uart_port *rda_uart_ports[RDA_UART_PORT_NUM];

अटल अंतरभूत व्योम rda_uart_ग_लिखो(काष्ठा uart_port *port, u32 val,
				  अचिन्हित पूर्णांक off)
अणु
	ग_लिखोl(val, port->membase + off);
पूर्ण

अटल अंतरभूत u32 rda_uart_पढ़ो(काष्ठा uart_port *port, अचिन्हित पूर्णांक off)
अणु
	वापस पढ़ोl(port->membase + off);
पूर्ण

अटल अचिन्हित पूर्णांक rda_uart_tx_empty(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ret;
	u32 val;

	spin_lock_irqsave(&port->lock, flags);

	val = rda_uart_पढ़ो(port, RDA_UART_STATUS);
	ret = (val & RDA_UART_TX_FIFO_MASK) ? TIOCSER_TEMT : 0;

	spin_unlock_irqrestore(&port->lock, flags);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक rda_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक mctrl = 0;
	u32 cmd_set, status;

	cmd_set = rda_uart_पढ़ो(port, RDA_UART_CMD_SET);
	status = rda_uart_पढ़ो(port, RDA_UART_STATUS);
	अगर (cmd_set & RDA_UART_RTS)
		mctrl |= TIOCM_RTS;
	अगर (!(status & RDA_UART_CTS))
		mctrl |= TIOCM_CTS;

	वापस mctrl;
पूर्ण

अटल व्योम rda_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	u32 val;

	अगर (mctrl & TIOCM_RTS) अणु
		val = rda_uart_पढ़ो(port, RDA_UART_CMD_SET);
		rda_uart_ग_लिखो(port, (val | RDA_UART_RTS), RDA_UART_CMD_SET);
	पूर्ण अन्यथा अणु
		/* Clear RTS to stop to receive. */
		val = rda_uart_पढ़ो(port, RDA_UART_CMD_CLR);
		rda_uart_ग_लिखो(port, (val | RDA_UART_RTS), RDA_UART_CMD_CLR);
	पूर्ण

	val = rda_uart_पढ़ो(port, RDA_UART_CTRL);

	अगर (mctrl & TIOCM_LOOP)
		val |= RDA_UART_LOOP_BACK_EN;
	अन्यथा
		val &= ~RDA_UART_LOOP_BACK_EN;

	rda_uart_ग_लिखो(port, val, RDA_UART_CTRL);
पूर्ण

अटल व्योम rda_uart_stop_tx(काष्ठा uart_port *port)
अणु
	u32 val;

	val = rda_uart_पढ़ो(port, RDA_UART_IRQ_MASK);
	val &= ~RDA_UART_TX_DATA_NEEDED;
	rda_uart_ग_लिखो(port, val, RDA_UART_IRQ_MASK);

	val = rda_uart_पढ़ो(port, RDA_UART_CMD_SET);
	val |= RDA_UART_TX_FIFO_RESET;
	rda_uart_ग_लिखो(port, val, RDA_UART_CMD_SET);
पूर्ण

अटल व्योम rda_uart_stop_rx(काष्ठा uart_port *port)
अणु
	u32 val;

	val = rda_uart_पढ़ो(port, RDA_UART_IRQ_MASK);
	val &= ~(RDA_UART_RX_DATA_AVAILABLE | RDA_UART_RX_TIMEOUT);
	rda_uart_ग_लिखो(port, val, RDA_UART_IRQ_MASK);

	/* Read Rx buffer beक्रमe reset to aव्योम Rx समयout पूर्णांकerrupt */
	val = rda_uart_पढ़ो(port, RDA_UART_RXTX_BUFFER);

	val = rda_uart_पढ़ो(port, RDA_UART_CMD_SET);
	val |= RDA_UART_RX_FIFO_RESET;
	rda_uart_ग_लिखो(port, val, RDA_UART_CMD_SET);
पूर्ण

अटल व्योम rda_uart_start_tx(काष्ठा uart_port *port)
अणु
	u32 val;

	अगर (uart_tx_stopped(port)) अणु
		rda_uart_stop_tx(port);
		वापस;
	पूर्ण

	val = rda_uart_पढ़ो(port, RDA_UART_IRQ_MASK);
	val |= RDA_UART_TX_DATA_NEEDED;
	rda_uart_ग_लिखो(port, val, RDA_UART_IRQ_MASK);
पूर्ण

अटल व्योम rda_uart_change_baudrate(काष्ठा rda_uart_port *rda_port,
				     अचिन्हित दीर्घ baud)
अणु
	clk_set_rate(rda_port->clk, baud * 8);
पूर्ण

अटल व्योम rda_uart_set_termios(काष्ठा uart_port *port,
				 काष्ठा ktermios *termios,
				 काष्ठा ktermios *old)
अणु
	काष्ठा rda_uart_port *rda_port = to_rda_uart_port(port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ctrl, cmd_set, cmd_clr, triggers;
	अचिन्हित पूर्णांक baud;
	u32 irq_mask;

	spin_lock_irqsave(&port->lock, flags);

	baud = uart_get_baud_rate(port, termios, old, 9600, port->uartclk / 4);
	rda_uart_change_baudrate(rda_port, baud);

	ctrl = rda_uart_पढ़ो(port, RDA_UART_CTRL);
	cmd_set = rda_uart_पढ़ो(port, RDA_UART_CMD_SET);
	cmd_clr = rda_uart_पढ़ो(port, RDA_UART_CMD_CLR);

	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
	हाल CS6:
		dev_warn(port->dev, "bit size not supported, using 7 bits\n");
		fallthrough;
	हाल CS7:
		ctrl &= ~RDA_UART_DBITS_8;
		अवरोध;
	शेष:
		ctrl |= RDA_UART_DBITS_8;
		अवरोध;
	पूर्ण

	/* stop bits */
	अगर (termios->c_cflag & CSTOPB)
		ctrl |= RDA_UART_TX_SBITS_2;
	अन्यथा
		ctrl &= ~RDA_UART_TX_SBITS_2;

	/* parity check */
	अगर (termios->c_cflag & PARENB) अणु
		ctrl |= RDA_UART_PARITY_EN;

		/* Mark or Space parity */
		अगर (termios->c_cflag & CMSPAR) अणु
			अगर (termios->c_cflag & PARODD)
				ctrl |= RDA_UART_PARITY_MARK;
			अन्यथा
				ctrl |= RDA_UART_PARITY_SPACE;
		पूर्ण अन्यथा अगर (termios->c_cflag & PARODD) अणु
			ctrl |= RDA_UART_PARITY_ODD;
		पूर्ण अन्यथा अणु
			ctrl |= RDA_UART_PARITY_EVEN;
		पूर्ण
	पूर्ण अन्यथा अणु
		ctrl &= ~RDA_UART_PARITY_EN;
	पूर्ण

	/* Hardware handshake (RTS/CTS) */
	अगर (termios->c_cflag & CRTSCTS) अणु
		ctrl   |= RDA_UART_FLOW_CNT_EN;
		cmd_set |= RDA_UART_RTS;
	पूर्ण अन्यथा अणु
		ctrl   &= ~RDA_UART_FLOW_CNT_EN;
		cmd_clr |= RDA_UART_RTS;
	पूर्ण

	ctrl |= RDA_UART_ENABLE;
	ctrl &= ~RDA_UART_DMA_EN;

	triggers  = (RDA_UART_AFC_LEVEL(20) | RDA_UART_RX_TRIGGER(16));
	irq_mask = rda_uart_पढ़ो(port, RDA_UART_IRQ_MASK);
	rda_uart_ग_लिखो(port, 0, RDA_UART_IRQ_MASK);

	rda_uart_ग_लिखो(port, triggers, RDA_UART_IRQ_TRIGGERS);
	rda_uart_ग_लिखो(port, ctrl, RDA_UART_CTRL);
	rda_uart_ग_लिखो(port, cmd_set, RDA_UART_CMD_SET);
	rda_uart_ग_लिखो(port, cmd_clr, RDA_UART_CMD_CLR);

	rda_uart_ग_लिखो(port, irq_mask, RDA_UART_IRQ_MASK);

	/* Don't reग_लिखो B0 */
	अगर (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);

	/* update the per-port समयout */
	uart_update_समयout(port, termios->c_cflag, baud);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम rda_uart_send_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित पूर्णांक ch;
	u32 val;

	अगर (uart_tx_stopped(port))
		वापस;

	अगर (port->x_अक्षर) अणु
		जबतक (!(rda_uart_पढ़ो(port, RDA_UART_STATUS) &
			 RDA_UART_TX_FIFO_MASK))
			cpu_relax();

		rda_uart_ग_लिखो(port, port->x_अक्षर, RDA_UART_RXTX_BUFFER);
		port->icount.tx++;
		port->x_अक्षर = 0;
	पूर्ण

	जबतक (rda_uart_पढ़ो(port, RDA_UART_STATUS) & RDA_UART_TX_FIFO_MASK) अणु
		अगर (uart_circ_empty(xmit))
			अवरोध;

		ch = xmit->buf[xmit->tail];
		rda_uart_ग_लिखो(port, ch, RDA_UART_RXTX_BUFFER);
		xmit->tail = (xmit->tail + 1) & (SERIAL_XMIT_SIZE - 1);
		port->icount.tx++;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (!uart_circ_empty(xmit)) अणु
		/* Re-enable Tx FIFO पूर्णांकerrupt */
		val = rda_uart_पढ़ो(port, RDA_UART_IRQ_MASK);
		val |= RDA_UART_TX_DATA_NEEDED;
		rda_uart_ग_लिखो(port, val, RDA_UART_IRQ_MASK);
	पूर्ण
पूर्ण

अटल व्योम rda_uart_receive_अक्षरs(काष्ठा uart_port *port)
अणु
	u32 status, val;

	status = rda_uart_पढ़ो(port, RDA_UART_STATUS);
	जबतक ((status & RDA_UART_RX_FIFO_MASK)) अणु
		अक्षर flag = TTY_NORMAL;

		अगर (status & RDA_UART_RX_PARITY_ERR) अणु
			port->icount.parity++;
			flag = TTY_PARITY;
		पूर्ण

		अगर (status & RDA_UART_RX_FRAMING_ERR) अणु
			port->icount.frame++;
			flag = TTY_FRAME;
		पूर्ण

		अगर (status & RDA_UART_RX_OVERFLOW_ERR) अणु
			port->icount.overrun++;
			flag = TTY_OVERRUN;
		पूर्ण

		val = rda_uart_पढ़ो(port, RDA_UART_RXTX_BUFFER);
		val &= 0xff;

		port->icount.rx++;
		tty_insert_flip_अक्षर(&port->state->port, val, flag);

		status = rda_uart_पढ़ो(port, RDA_UART_STATUS);
	पूर्ण

	tty_flip_buffer_push(&port->state->port);
पूर्ण

अटल irqवापस_t rda_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	अचिन्हित दीर्घ flags;
	u32 val, irq_mask;

	spin_lock_irqsave(&port->lock, flags);

	/* Clear IRQ cause */
	val = rda_uart_पढ़ो(port, RDA_UART_IRQ_CAUSE);
	rda_uart_ग_लिखो(port, val, RDA_UART_IRQ_CAUSE);

	अगर (val & (RDA_UART_RX_DATA_AVAILABLE | RDA_UART_RX_TIMEOUT))
		rda_uart_receive_अक्षरs(port);

	अगर (val & (RDA_UART_TX_DATA_NEEDED)) अणु
		irq_mask = rda_uart_पढ़ो(port, RDA_UART_IRQ_MASK);
		irq_mask &= ~RDA_UART_TX_DATA_NEEDED;
		rda_uart_ग_लिखो(port, irq_mask, RDA_UART_IRQ_MASK);

		rda_uart_send_अक्षरs(port);
	पूर्ण

	spin_unlock_irqrestore(&port->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rda_uart_startup(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	u32 val;

	spin_lock_irqsave(&port->lock, flags);
	rda_uart_ग_लिखो(port, 0, RDA_UART_IRQ_MASK);
	spin_unlock_irqrestore(&port->lock, flags);

	ret = request_irq(port->irq, rda_पूर्णांकerrupt, IRQF_NO_SUSPEND,
			  "rda-uart", port);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&port->lock, flags);

	val = rda_uart_पढ़ो(port, RDA_UART_CTRL);
	val |= RDA_UART_ENABLE;
	rda_uart_ग_लिखो(port, val, RDA_UART_CTRL);

	/* enable rx पूर्णांकerrupt */
	val = rda_uart_पढ़ो(port, RDA_UART_IRQ_MASK);
	val |= (RDA_UART_RX_DATA_AVAILABLE | RDA_UART_RX_TIMEOUT);
	rda_uart_ग_लिखो(port, val, RDA_UART_IRQ_MASK);

	spin_unlock_irqrestore(&port->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम rda_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&port->lock, flags);

	rda_uart_stop_tx(port);
	rda_uart_stop_rx(port);

	val = rda_uart_पढ़ो(port, RDA_UART_CTRL);
	val &= ~RDA_UART_ENABLE;
	rda_uart_ग_लिखो(port, val, RDA_UART_CTRL);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *rda_uart_type(काष्ठा uart_port *port)
अणु
	वापस (port->type == PORT_RDA) ? "rda-uart" : शून्य;
पूर्ण

अटल पूर्णांक rda_uart_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(port->dev);
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENXIO;

	अगर (!devm_request_mem_region(port->dev, port->mapbase,
				     resource_size(res), dev_name(port->dev)))
		वापस -EBUSY;

	अगर (port->flags & UPF_IOREMAP) अणु
		port->membase = devm_ioremap(port->dev, port->mapbase,
						     resource_size(res));
		अगर (!port->membase)
			वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rda_uart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अचिन्हित दीर्घ irq_flags;

	अगर (flags & UART_CONFIG_TYPE) अणु
		port->type = PORT_RDA;
		rda_uart_request_port(port);
	पूर्ण

	spin_lock_irqsave(&port->lock, irq_flags);

	/* Clear mask, so no surprise पूर्णांकerrupts. */
	rda_uart_ग_लिखो(port, 0, RDA_UART_IRQ_MASK);

	/* Clear status रेजिस्टर */
	rda_uart_ग_लिखो(port, 0, RDA_UART_STATUS);

	spin_unlock_irqrestore(&port->lock, irq_flags);
पूर्ण

अटल व्योम rda_uart_release_port(काष्ठा uart_port *port)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(port->dev);
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस;

	अगर (port->flags & UPF_IOREMAP) अणु
		devm_release_mem_region(port->dev, port->mapbase,
					resource_size(res));
		devm_iounmap(port->dev, port->membase);
		port->membase = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक rda_uart_verअगरy_port(काष्ठा uart_port *port,
				काष्ठा serial_काष्ठा *ser)
अणु
	अगर (port->type != PORT_RDA)
		वापस -EINVAL;

	अगर (port->irq != ser->irq)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uart_ops rda_uart_ops = अणु
	.tx_empty       = rda_uart_tx_empty,
	.get_mctrl      = rda_uart_get_mctrl,
	.set_mctrl      = rda_uart_set_mctrl,
	.start_tx       = rda_uart_start_tx,
	.stop_tx        = rda_uart_stop_tx,
	.stop_rx        = rda_uart_stop_rx,
	.startup        = rda_uart_startup,
	.shutकरोwn       = rda_uart_shutकरोwn,
	.set_termios    = rda_uart_set_termios,
	.type           = rda_uart_type,
	.request_port	= rda_uart_request_port,
	.release_port	= rda_uart_release_port,
	.config_port	= rda_uart_config_port,
	.verअगरy_port	= rda_uart_verअगरy_port,
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_RDA_CONSOLE

अटल व्योम rda_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	अगर (!port->membase)
		वापस;

	जबतक (!(rda_uart_पढ़ो(port, RDA_UART_STATUS) & RDA_UART_TX_FIFO_MASK))
		cpu_relax();

	rda_uart_ग_लिखो(port, ch, RDA_UART_RXTX_BUFFER);
पूर्ण

अटल व्योम rda_uart_port_ग_लिखो(काष्ठा uart_port *port, स्थिर अक्षर *s,
				u_पूर्णांक count)
अणु
	u32 old_irq_mask;
	अचिन्हित दीर्घ flags;
	पूर्णांक locked;

	local_irq_save(flags);

	अगर (port->sysrq) अणु
		locked = 0;
	पूर्ण अन्यथा अगर (oops_in_progress) अणु
		locked = spin_trylock(&port->lock);
	पूर्ण अन्यथा अणु
		spin_lock(&port->lock);
		locked = 1;
	पूर्ण

	old_irq_mask = rda_uart_पढ़ो(port, RDA_UART_IRQ_MASK);
	rda_uart_ग_लिखो(port, 0, RDA_UART_IRQ_MASK);

	uart_console_ग_लिखो(port, s, count, rda_console_अक्षर_दो);

	/* रुको until all contents have been sent out */
	जबतक (!(rda_uart_पढ़ो(port, RDA_UART_STATUS) & RDA_UART_TX_FIFO_MASK))
		cpu_relax();

	rda_uart_ग_लिखो(port, old_irq_mask, RDA_UART_IRQ_MASK);

	अगर (locked)
		spin_unlock(&port->lock);

	local_irq_restore(flags);
पूर्ण

अटल व्योम rda_uart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				   u_पूर्णांक count)
अणु
	काष्ठा rda_uart_port *rda_port;

	rda_port = rda_uart_ports[co->index];
	अगर (!rda_port)
		वापस;

	rda_uart_port_ग_लिखो(&rda_port->port, s, count);
पूर्ण

अटल पूर्णांक rda_uart_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा rda_uart_port *rda_port;
	पूर्णांक baud = 921600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (co->index < 0 || co->index >= RDA_UART_PORT_NUM)
		वापस -EINVAL;

	rda_port = rda_uart_ports[co->index];
	अगर (!rda_port || !rda_port->port.membase)
		वापस -ENODEV;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(&rda_port->port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा console rda_uart_console = अणु
	.name = RDA_UART_DEV_NAME,
	.ग_लिखो = rda_uart_console_ग_लिखो,
	.device = uart_console_device,
	.setup = rda_uart_console_setup,
	.flags = CON_PRINTBUFFER,
	.index = -1,
	.data = &rda_uart_driver,
पूर्ण;

अटल पूर्णांक __init rda_uart_console_init(व्योम)
अणु
	रेजिस्टर_console(&rda_uart_console);

	वापस 0;
पूर्ण
console_initcall(rda_uart_console_init);

अटल व्योम rda_uart_early_console_ग_लिखो(काष्ठा console *co,
					 स्थिर अक्षर *s,
					 u_पूर्णांक count)
अणु
	काष्ठा earlycon_device *dev = co->data;

	rda_uart_port_ग_लिखो(&dev->port, s, count);
पूर्ण

अटल पूर्णांक __init
rda_uart_early_console_setup(काष्ठा earlycon_device *device, स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->con->ग_लिखो = rda_uart_early_console_ग_लिखो;

	वापस 0;
पूर्ण

OF_EARLYCON_DECLARE(rda, "rda,8810pl-uart",
		    rda_uart_early_console_setup);

#घोषणा RDA_UART_CONSOLE (&rda_uart_console)
#अन्यथा
#घोषणा RDA_UART_CONSOLE शून्य
#पूर्ण_अगर /* CONFIG_SERIAL_RDA_CONSOLE */

अटल काष्ठा uart_driver rda_uart_driver = अणु
	.owner = THIS_MODULE,
	.driver_name = "rda-uart",
	.dev_name = RDA_UART_DEV_NAME,
	.nr = RDA_UART_PORT_NUM,
	.cons = RDA_UART_CONSOLE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rda_uart_dt_matches[] = अणु
	अणु .compatible = "rda,8810pl-uart" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rda_uart_dt_matches);

अटल पूर्णांक rda_uart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res_mem;
	काष्ठा rda_uart_port *rda_port;
	पूर्णांक ret, irq;

	अगर (pdev->dev.of_node)
		pdev->id = of_alias_get_id(pdev->dev.of_node, "serial");

	अगर (pdev->id < 0 || pdev->id >= RDA_UART_PORT_NUM) अणु
		dev_err(&pdev->dev, "id %d out of range\n", pdev->id);
		वापस -EINVAL;
	पूर्ण

	res_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res_mem) अणु
		dev_err(&pdev->dev, "could not get mem\n");
		वापस -ENODEV;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	अगर (rda_uart_ports[pdev->id]) अणु
		dev_err(&pdev->dev, "port %d already allocated\n", pdev->id);
		वापस -EBUSY;
	पूर्ण

	rda_port = devm_kzalloc(&pdev->dev, माप(*rda_port), GFP_KERNEL);
	अगर (!rda_port)
		वापस -ENOMEM;

	rda_port->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(rda_port->clk)) अणु
		dev_err(&pdev->dev, "could not get clk\n");
		वापस PTR_ERR(rda_port->clk);
	पूर्ण

	rda_port->port.dev = &pdev->dev;
	rda_port->port.regshअगरt = 0;
	rda_port->port.line = pdev->id;
	rda_port->port.type = PORT_RDA;
	rda_port->port.iotype = UPIO_MEM;
	rda_port->port.mapbase = res_mem->start;
	rda_port->port.irq = irq;
	rda_port->port.uartclk = clk_get_rate(rda_port->clk);
	अगर (rda_port->port.uartclk == 0) अणु
		dev_err(&pdev->dev, "clock rate is zero\n");
		वापस -EINVAL;
	पूर्ण
	rda_port->port.flags = UPF_BOOT_AUTOCONF | UPF_IOREMAP |
			       UPF_LOW_LATENCY;
	rda_port->port.x_अक्षर = 0;
	rda_port->port.fअगरosize = RDA_UART_TX_FIFO_SIZE;
	rda_port->port.ops = &rda_uart_ops;

	rda_uart_ports[pdev->id] = rda_port;
	platक्रमm_set_drvdata(pdev, rda_port);

	ret = uart_add_one_port(&rda_uart_driver, &rda_port->port);
	अगर (ret)
		rda_uart_ports[pdev->id] = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक rda_uart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rda_uart_port *rda_port = platक्रमm_get_drvdata(pdev);

	uart_हटाओ_one_port(&rda_uart_driver, &rda_port->port);
	rda_uart_ports[pdev->id] = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rda_uart_platक्रमm_driver = अणु
	.probe = rda_uart_probe,
	.हटाओ = rda_uart_हटाओ,
	.driver = अणु
		.name = "rda-uart",
		.of_match_table = rda_uart_dt_matches,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init rda_uart_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&rda_uart_driver);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&rda_uart_platक्रमm_driver);
	अगर (ret)
		uart_unरेजिस्टर_driver(&rda_uart_driver);

	वापस ret;
पूर्ण

अटल व्योम __निकास rda_uart_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&rda_uart_platक्रमm_driver);
	uart_unरेजिस्टर_driver(&rda_uart_driver);
पूर्ण

module_init(rda_uart_init);
module_निकास(rda_uart_निकास);

MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_DESCRIPTION("RDA8810PL serial device driver");
MODULE_LICENSE("GPL");
