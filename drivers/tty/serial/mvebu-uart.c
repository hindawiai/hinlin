<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
* ***************************************************************************
* Marvell Armada-3700 Serial Driver
* Author: Wilson Ding <dingwei@marvell.com>
* Copyright (C) 2015 Marvell International Ltd.
* ***************************************************************************
*/

#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

/* Register Map */
#घोषणा UART_STD_RBR		0x00
#घोषणा UART_EXT_RBR		0x18

#घोषणा UART_STD_TSH		0x04
#घोषणा UART_EXT_TSH		0x1C

#घोषणा UART_STD_CTRL1		0x08
#घोषणा UART_EXT_CTRL1		0x04
#घोषणा  CTRL_SOFT_RST		BIT(31)
#घोषणा  CTRL_TXFIFO_RST	BIT(15)
#घोषणा  CTRL_RXFIFO_RST	BIT(14)
#घोषणा  CTRL_SND_BRK_SEQ	BIT(11)
#घोषणा  CTRL_BRK_DET_INT	BIT(3)
#घोषणा  CTRL_FRM_ERR_INT	BIT(2)
#घोषणा  CTRL_PAR_ERR_INT	BIT(1)
#घोषणा  CTRL_OVR_ERR_INT	BIT(0)
#घोषणा  CTRL_BRK_INT		(CTRL_BRK_DET_INT | CTRL_FRM_ERR_INT | \
				CTRL_PAR_ERR_INT | CTRL_OVR_ERR_INT)

#घोषणा UART_STD_CTRL2		UART_STD_CTRL1
#घोषणा UART_EXT_CTRL2		0x20
#घोषणा  CTRL_STD_TX_RDY_INT	BIT(5)
#घोषणा  CTRL_EXT_TX_RDY_INT	BIT(6)
#घोषणा  CTRL_STD_RX_RDY_INT	BIT(4)
#घोषणा  CTRL_EXT_RX_RDY_INT	BIT(5)

#घोषणा UART_STAT		0x0C
#घोषणा  STAT_TX_FIFO_EMP	BIT(13)
#घोषणा  STAT_TX_FIFO_FUL	BIT(11)
#घोषणा  STAT_TX_EMP		BIT(6)
#घोषणा  STAT_STD_TX_RDY	BIT(5)
#घोषणा  STAT_EXT_TX_RDY	BIT(15)
#घोषणा  STAT_STD_RX_RDY	BIT(4)
#घोषणा  STAT_EXT_RX_RDY	BIT(14)
#घोषणा  STAT_BRK_DET		BIT(3)
#घोषणा  STAT_FRM_ERR		BIT(2)
#घोषणा  STAT_PAR_ERR		BIT(1)
#घोषणा  STAT_OVR_ERR		BIT(0)
#घोषणा  STAT_BRK_ERR		(STAT_BRK_DET | STAT_FRM_ERR \
				 | STAT_PAR_ERR | STAT_OVR_ERR)

#घोषणा UART_BRDV		0x10
#घोषणा  BRDV_BAUD_MASK         0x3FF

#घोषणा UART_OSAMP		0x14
#घोषणा  OSAMP_DEFAULT_DIVISOR	16
#घोषणा  OSAMP_DIVISORS_MASK	0x3F3F3F3F

#घोषणा MVEBU_NR_UARTS		2

#घोषणा MVEBU_UART_TYPE		"mvebu-uart"
#घोषणा DRIVER_NAME		"mvebu_serial"

क्रमागत अणु
	/* Either there is only one summed IRQ... */
	UART_IRQ_SUM = 0,
	/* ...or there are two separate IRQ क्रम RX and TX */
	UART_RX_IRQ = 0,
	UART_TX_IRQ,
	UART_IRQ_COUNT
पूर्ण;

/* Diverging रेजिस्टर offsets */
काष्ठा uart_regs_layout अणु
	अचिन्हित पूर्णांक rbr;
	अचिन्हित पूर्णांक tsh;
	अचिन्हित पूर्णांक ctrl;
	अचिन्हित पूर्णांक पूर्णांकr;
पूर्ण;

/* Diverging flags */
काष्ठा uart_flags अणु
	अचिन्हित पूर्णांक ctrl_tx_rdy_पूर्णांक;
	अचिन्हित पूर्णांक ctrl_rx_rdy_पूर्णांक;
	अचिन्हित पूर्णांक stat_tx_rdy;
	अचिन्हित पूर्णांक stat_rx_rdy;
पूर्ण;

/* Driver data, a काष्ठाure क्रम each UART port */
काष्ठा mvebu_uart_driver_data अणु
	bool is_ext;
	काष्ठा uart_regs_layout regs;
	काष्ठा uart_flags flags;
पूर्ण;

/* Saved रेजिस्टरs during suspend */
काष्ठा mvebu_uart_pm_regs अणु
	अचिन्हित पूर्णांक rbr;
	अचिन्हित पूर्णांक tsh;
	अचिन्हित पूर्णांक ctrl;
	अचिन्हित पूर्णांक पूर्णांकr;
	अचिन्हित पूर्णांक stat;
	अचिन्हित पूर्णांक brdv;
	अचिन्हित पूर्णांक osamp;
पूर्ण;

/* MVEBU UART driver काष्ठाure */
काष्ठा mvebu_uart अणु
	काष्ठा uart_port *port;
	काष्ठा clk *clk;
	पूर्णांक irq[UART_IRQ_COUNT];
	अचिन्हित अक्षर __iomem *nb;
	काष्ठा mvebu_uart_driver_data *data;
#अगर defined(CONFIG_PM)
	काष्ठा mvebu_uart_pm_regs pm_regs;
#पूर्ण_अगर /* CONFIG_PM */
पूर्ण;

अटल काष्ठा mvebu_uart *to_mvuart(काष्ठा uart_port *port)
अणु
	वापस (काष्ठा mvebu_uart *)port->निजी_data;
पूर्ण

#घोषणा IS_EXTENDED(port) (to_mvuart(port)->data->is_ext)

#घोषणा UART_RBR(port) (to_mvuart(port)->data->regs.rbr)
#घोषणा UART_TSH(port) (to_mvuart(port)->data->regs.tsh)
#घोषणा UART_CTRL(port) (to_mvuart(port)->data->regs.ctrl)
#घोषणा UART_INTR(port) (to_mvuart(port)->data->regs.पूर्णांकr)

#घोषणा CTRL_TX_RDY_INT(port) (to_mvuart(port)->data->flags.ctrl_tx_rdy_पूर्णांक)
#घोषणा CTRL_RX_RDY_INT(port) (to_mvuart(port)->data->flags.ctrl_rx_rdy_पूर्णांक)
#घोषणा STAT_TX_RDY(port) (to_mvuart(port)->data->flags.stat_tx_rdy)
#घोषणा STAT_RX_RDY(port) (to_mvuart(port)->data->flags.stat_rx_rdy)

अटल काष्ठा uart_port mvebu_uart_ports[MVEBU_NR_UARTS];

/* Core UART Driver Operations */
अटल अचिन्हित पूर्णांक mvebu_uart_tx_empty(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक st;

	spin_lock_irqsave(&port->lock, flags);
	st = पढ़ोl(port->membase + UART_STAT);
	spin_unlock_irqrestore(&port->lock, flags);

	वापस (st & STAT_TX_FIFO_EMP) ? TIOCSER_TEMT : 0;
पूर्ण

अटल अचिन्हित पूर्णांक mvebu_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस TIOCM_CTS | TIOCM_DSR | TIOCM_CAR;
पूर्ण

अटल व्योम mvebu_uart_set_mctrl(काष्ठा uart_port *port,
				 अचिन्हित पूर्णांक mctrl)
अणु
/*
 * Even अगर we करो not support configuring the modem control lines, this
 * function must be proided to the serial core
 */
पूर्ण

अटल व्योम mvebu_uart_stop_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक ctl = पढ़ोl(port->membase + UART_INTR(port));

	ctl &= ~CTRL_TX_RDY_INT(port);
	ग_लिखोl(ctl, port->membase + UART_INTR(port));
पूर्ण

अटल व्योम mvebu_uart_start_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक ctl;
	काष्ठा circ_buf *xmit = &port->state->xmit;

	अगर (IS_EXTENDED(port) && !uart_circ_empty(xmit)) अणु
		ग_लिखोl(xmit->buf[xmit->tail], port->membase + UART_TSH(port));
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
	पूर्ण

	ctl = पढ़ोl(port->membase + UART_INTR(port));
	ctl |= CTRL_TX_RDY_INT(port);
	ग_लिखोl(ctl, port->membase + UART_INTR(port));
पूर्ण

अटल व्योम mvebu_uart_stop_rx(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक ctl;

	ctl = पढ़ोl(port->membase + UART_CTRL(port));
	ctl &= ~CTRL_BRK_INT;
	ग_लिखोl(ctl, port->membase + UART_CTRL(port));

	ctl = पढ़ोl(port->membase + UART_INTR(port));
	ctl &= ~CTRL_RX_RDY_INT(port);
	ग_लिखोl(ctl, port->membase + UART_INTR(port));
पूर्ण

अटल व्योम mvebu_uart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक brk)
अणु
	अचिन्हित पूर्णांक ctl;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	ctl = पढ़ोl(port->membase + UART_CTRL(port));
	अगर (brk == -1)
		ctl |= CTRL_SND_BRK_SEQ;
	अन्यथा
		ctl &= ~CTRL_SND_BRK_SEQ;
	ग_लिखोl(ctl, port->membase + UART_CTRL(port));
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम mvebu_uart_rx_अक्षरs(काष्ठा uart_port *port, अचिन्हित पूर्णांक status)
अणु
	काष्ठा tty_port *tport = &port->state->port;
	अचिन्हित अक्षर ch = 0;
	अक्षर flag = 0;

	करो अणु
		अगर (status & STAT_RX_RDY(port)) अणु
			ch = पढ़ोl(port->membase + UART_RBR(port));
			ch &= 0xff;
			flag = TTY_NORMAL;
			port->icount.rx++;

			अगर (status & STAT_PAR_ERR)
				port->icount.parity++;
		पूर्ण

		अगर (status & STAT_BRK_DET) अणु
			port->icount.brk++;
			status &= ~(STAT_FRM_ERR | STAT_PAR_ERR);
			अगर (uart_handle_अवरोध(port))
				जाओ ignore_अक्षर;
		पूर्ण

		अगर (status & STAT_OVR_ERR)
			port->icount.overrun++;

		अगर (status & STAT_FRM_ERR)
			port->icount.frame++;

		अगर (uart_handle_sysrq_अक्षर(port, ch))
			जाओ ignore_अक्षर;

		अगर (status & port->ignore_status_mask & STAT_PAR_ERR)
			status &= ~STAT_RX_RDY(port);

		status &= port->पढ़ो_status_mask;

		अगर (status & STAT_PAR_ERR)
			flag = TTY_PARITY;

		status &= ~port->ignore_status_mask;

		अगर (status & STAT_RX_RDY(port))
			tty_insert_flip_अक्षर(tport, ch, flag);

		अगर (status & STAT_BRK_DET)
			tty_insert_flip_अक्षर(tport, 0, TTY_BREAK);

		अगर (status & STAT_FRM_ERR)
			tty_insert_flip_अक्षर(tport, 0, TTY_FRAME);

		अगर (status & STAT_OVR_ERR)
			tty_insert_flip_अक्षर(tport, 0, TTY_OVERRUN);

ignore_अक्षर:
		status = पढ़ोl(port->membase + UART_STAT);
	पूर्ण जबतक (status & (STAT_RX_RDY(port) | STAT_BRK_DET));

	tty_flip_buffer_push(tport);
पूर्ण

अटल व्योम mvebu_uart_tx_अक्षरs(काष्ठा uart_port *port, अचिन्हित पूर्णांक status)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक st;

	अगर (port->x_अक्षर) अणु
		ग_लिखोl(port->x_अक्षर, port->membase + UART_TSH(port));
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		mvebu_uart_stop_tx(port);
		वापस;
	पूर्ण

	क्रम (count = 0; count < port->fअगरosize; count++) अणु
		ग_लिखोl(xmit->buf[xmit->tail], port->membase + UART_TSH(port));
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;

		अगर (uart_circ_empty(xmit))
			अवरोध;

		st = पढ़ोl(port->membase + UART_STAT);
		अगर (st & STAT_TX_FIFO_FUL)
			अवरोध;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (uart_circ_empty(xmit))
		mvebu_uart_stop_tx(port);
पूर्ण

अटल irqवापस_t mvebu_uart_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = (काष्ठा uart_port *)dev_id;
	अचिन्हित पूर्णांक st = पढ़ोl(port->membase + UART_STAT);

	अगर (st & (STAT_RX_RDY(port) | STAT_OVR_ERR | STAT_FRM_ERR |
		  STAT_BRK_DET))
		mvebu_uart_rx_अक्षरs(port, st);

	अगर (st & STAT_TX_RDY(port))
		mvebu_uart_tx_अक्षरs(port, st);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mvebu_uart_rx_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = (काष्ठा uart_port *)dev_id;
	अचिन्हित पूर्णांक st = पढ़ोl(port->membase + UART_STAT);

	अगर (st & (STAT_RX_RDY(port) | STAT_OVR_ERR | STAT_FRM_ERR |
			STAT_BRK_DET))
		mvebu_uart_rx_अक्षरs(port, st);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mvebu_uart_tx_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = (काष्ठा uart_port *)dev_id;
	अचिन्हित पूर्णांक st = पढ़ोl(port->membase + UART_STAT);

	अगर (st & STAT_TX_RDY(port))
		mvebu_uart_tx_अक्षरs(port, st);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mvebu_uart_startup(काष्ठा uart_port *port)
अणु
	काष्ठा mvebu_uart *mvuart = to_mvuart(port);
	अचिन्हित पूर्णांक ctl;
	पूर्णांक ret;

	ग_लिखोl(CTRL_TXFIFO_RST | CTRL_RXFIFO_RST,
	       port->membase + UART_CTRL(port));
	udelay(1);

	/* Clear the error bits of state रेजिस्टर beक्रमe IRQ request */
	ret = पढ़ोl(port->membase + UART_STAT);
	ret |= STAT_BRK_ERR;
	ग_लिखोl(ret, port->membase + UART_STAT);

	ग_लिखोl(CTRL_BRK_INT, port->membase + UART_CTRL(port));

	ctl = पढ़ोl(port->membase + UART_INTR(port));
	ctl |= CTRL_RX_RDY_INT(port);
	ग_लिखोl(ctl, port->membase + UART_INTR(port));

	अगर (!mvuart->irq[UART_TX_IRQ]) अणु
		/* Old bindings with just one पूर्णांकerrupt (UART0 only) */
		ret = devm_request_irq(port->dev, mvuart->irq[UART_IRQ_SUM],
				       mvebu_uart_isr, port->irqflags,
				       dev_name(port->dev), port);
		अगर (ret) अणु
			dev_err(port->dev, "unable to request IRQ %d\n",
				mvuart->irq[UART_IRQ_SUM]);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* New bindings with an IRQ क्रम RX and TX (both UART) */
		ret = devm_request_irq(port->dev, mvuart->irq[UART_RX_IRQ],
				       mvebu_uart_rx_isr, port->irqflags,
				       dev_name(port->dev), port);
		अगर (ret) अणु
			dev_err(port->dev, "unable to request IRQ %d\n",
				mvuart->irq[UART_RX_IRQ]);
			वापस ret;
		पूर्ण

		ret = devm_request_irq(port->dev, mvuart->irq[UART_TX_IRQ],
				       mvebu_uart_tx_isr, port->irqflags,
				       dev_name(port->dev),
				       port);
		अगर (ret) अणु
			dev_err(port->dev, "unable to request IRQ %d\n",
				mvuart->irq[UART_TX_IRQ]);
			devm_मुक्त_irq(port->dev, mvuart->irq[UART_RX_IRQ],
				      port);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mvebu_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा mvebu_uart *mvuart = to_mvuart(port);

	ग_लिखोl(0, port->membase + UART_INTR(port));

	अगर (!mvuart->irq[UART_TX_IRQ]) अणु
		devm_मुक्त_irq(port->dev, mvuart->irq[UART_IRQ_SUM], port);
	पूर्ण अन्यथा अणु
		devm_मुक्त_irq(port->dev, mvuart->irq[UART_RX_IRQ], port);
		devm_मुक्त_irq(port->dev, mvuart->irq[UART_TX_IRQ], port);
	पूर्ण
पूर्ण

अटल पूर्णांक mvebu_uart_baud_rate_set(काष्ठा uart_port *port, अचिन्हित पूर्णांक baud)
अणु
	काष्ठा mvebu_uart *mvuart = to_mvuart(port);
	अचिन्हित पूर्णांक d_भागisor, m_भागisor;
	u32 brdv, osamp;

	अगर (IS_ERR(mvuart->clk))
		वापस -PTR_ERR(mvuart->clk);

	/*
	 * The baudrate is derived from the UART घड़ी thanks to two भागisors:
	 *   > D ("baud generator"): can भागide the घड़ी from 2 to 2^10 - 1.
	 *   > M ("fractional divisor"): allows a better accuracy क्रम
	 *     baudrates higher than 230400.
	 *
	 * As the derivation of M is rather complicated, the code sticks to its
	 * शेष value (x16) when all the prescalers are zeroed, and only
	 * makes use of D to configure the desired baudrate.
	 */
	m_भागisor = OSAMP_DEFAULT_DIVISOR;
	d_भागisor = DIV_ROUND_UP(port->uartclk, baud * m_भागisor);

	brdv = पढ़ोl(port->membase + UART_BRDV);
	brdv &= ~BRDV_BAUD_MASK;
	brdv |= d_भागisor;
	ग_लिखोl(brdv, port->membase + UART_BRDV);

	osamp = पढ़ोl(port->membase + UART_OSAMP);
	osamp &= ~OSAMP_DIVISORS_MASK;
	ग_लिखोl(osamp, port->membase + UART_OSAMP);

	वापस 0;
पूर्ण

अटल व्योम mvebu_uart_set_termios(काष्ठा uart_port *port,
				   काष्ठा ktermios *termios,
				   काष्ठा ktermios *old)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud;

	spin_lock_irqsave(&port->lock, flags);

	port->पढ़ो_status_mask = STAT_RX_RDY(port) | STAT_OVR_ERR |
		STAT_TX_RDY(port) | STAT_TX_FIFO_FUL;

	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= STAT_FRM_ERR | STAT_PAR_ERR;

	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |=
			STAT_FRM_ERR | STAT_PAR_ERR | STAT_OVR_ERR;

	अगर ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= STAT_RX_RDY(port) | STAT_BRK_ERR;

	/*
	 * Maximum achievable frequency with simple baudrate भागisor is 230400.
	 * Since the error per bit frame would be of more than 15%, achieving
	 * higher frequencies would require to implement the fractional भागisor
	 * feature.
	 */
	baud = uart_get_baud_rate(port, termios, old, 0, 230400);
	अगर (mvebu_uart_baud_rate_set(port, baud)) अणु
		/* No घड़ी available, baudrate cannot be changed */
		अगर (old)
			baud = uart_get_baud_rate(port, old, शून्य, 0, 230400);
	पूर्ण अन्यथा अणु
		tty_termios_encode_baud_rate(termios, baud, baud);
		uart_update_समयout(port, termios->c_cflag, baud);
	पूर्ण

	/* Only the following flag changes are supported */
	अगर (old) अणु
		termios->c_अगरlag &= INPCK | IGNPAR;
		termios->c_अगरlag |= old->c_अगरlag & ~(INPCK | IGNPAR);
		termios->c_cflag &= CREAD | CBAUD;
		termios->c_cflag |= old->c_cflag & ~(CREAD | CBAUD);
		termios->c_cflag |= CS8;
	पूर्ण

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *mvebu_uart_type(काष्ठा uart_port *port)
अणु
	वापस MVEBU_UART_TYPE;
पूर्ण

अटल व्योम mvebu_uart_release_port(काष्ठा uart_port *port)
अणु
	/* Nothing to करो here */
पूर्ण

अटल पूर्णांक mvebu_uart_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
अटल पूर्णांक mvebu_uart_get_poll_अक्षर(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक st = पढ़ोl(port->membase + UART_STAT);

	अगर (!(st & STAT_RX_RDY(port)))
		वापस NO_POLL_CHAR;

	वापस पढ़ोl(port->membase + UART_RBR(port));
पूर्ण

अटल व्योम mvebu_uart_put_poll_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर c)
अणु
	अचिन्हित पूर्णांक st;

	क्रम (;;) अणु
		st = पढ़ोl(port->membase + UART_STAT);

		अगर (!(st & STAT_TX_FIFO_FUL))
			अवरोध;

		udelay(1);
	पूर्ण

	ग_लिखोl(c, port->membase + UART_TSH(port));
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा uart_ops mvebu_uart_ops = अणु
	.tx_empty	= mvebu_uart_tx_empty,
	.set_mctrl	= mvebu_uart_set_mctrl,
	.get_mctrl	= mvebu_uart_get_mctrl,
	.stop_tx	= mvebu_uart_stop_tx,
	.start_tx	= mvebu_uart_start_tx,
	.stop_rx	= mvebu_uart_stop_rx,
	.अवरोध_ctl	= mvebu_uart_अवरोध_ctl,
	.startup	= mvebu_uart_startup,
	.shutकरोwn	= mvebu_uart_shutकरोwn,
	.set_termios	= mvebu_uart_set_termios,
	.type		= mvebu_uart_type,
	.release_port	= mvebu_uart_release_port,
	.request_port	= mvebu_uart_request_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर	= mvebu_uart_get_poll_अक्षर,
	.poll_put_अक्षर	= mvebu_uart_put_poll_अक्षर,
#पूर्ण_अगर
पूर्ण;

/* Console Driver Operations  */

#अगर_घोषित CONFIG_SERIAL_MVEBU_CONSOLE
/* Early Console */
अटल व्योम mvebu_uart_अ_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	अचिन्हित पूर्णांक st;

	क्रम (;;) अणु
		st = पढ़ोl(port->membase + UART_STAT);
		अगर (!(st & STAT_TX_FIFO_FUL))
			अवरोध;
	पूर्ण

	/* At early stage, DT is not parsed yet, only use UART0 */
	ग_लिखोl(c, port->membase + UART_STD_TSH);

	क्रम (;;) अणु
		st = पढ़ोl(port->membase + UART_STAT);
		अगर (st & STAT_TX_FIFO_EMP)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mvebu_uart_अ_दो_early_ग_लिखो(काष्ठा console *con,
					स्थिर अक्षर *s,
					अचिन्हित n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	uart_console_ग_लिखो(&dev->port, s, n, mvebu_uart_अ_दो);
पूर्ण

अटल पूर्णांक __init
mvebu_uart_early_console_setup(काष्ठा earlycon_device *device,
			       स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->con->ग_लिखो = mvebu_uart_अ_दो_early_ग_लिखो;

	वापस 0;
पूर्ण

EARLYCON_DECLARE(ar3700_uart, mvebu_uart_early_console_setup);
OF_EARLYCON_DECLARE(ar3700_uart, "marvell,armada-3700-uart",
		    mvebu_uart_early_console_setup);

अटल व्योम रुको_क्रम_xmitr(काष्ठा uart_port *port)
अणु
	u32 val;

	पढ़ोl_poll_समयout_atomic(port->membase + UART_STAT, val,
				  (val & STAT_TX_RDY(port)), 1, 10000);
पूर्ण

अटल व्योम रुको_क्रम_xmite(काष्ठा uart_port *port)
अणु
	u32 val;

	पढ़ोl_poll_समयout_atomic(port->membase + UART_STAT, val,
				  (val & STAT_TX_EMP), 1, 10000);
पूर्ण

अटल व्योम mvebu_uart_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	रुको_क्रम_xmitr(port);
	ग_लिखोl(ch, port->membase + UART_TSH(port));
पूर्ण

अटल व्योम mvebu_uart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				     अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_port *port = &mvebu_uart_ports[co->index];
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ier, पूर्णांकr, ctl;
	पूर्णांक locked = 1;

	अगर (oops_in_progress)
		locked = spin_trylock_irqsave(&port->lock, flags);
	अन्यथा
		spin_lock_irqsave(&port->lock, flags);

	ier = पढ़ोl(port->membase + UART_CTRL(port)) & CTRL_BRK_INT;
	पूर्णांकr = पढ़ोl(port->membase + UART_INTR(port)) &
		(CTRL_RX_RDY_INT(port) | CTRL_TX_RDY_INT(port));
	ग_लिखोl(0, port->membase + UART_CTRL(port));
	ग_लिखोl(0, port->membase + UART_INTR(port));

	uart_console_ग_लिखो(port, s, count, mvebu_uart_console_अक्षर_दो);

	रुको_क्रम_xmite(port);

	अगर (ier)
		ग_लिखोl(ier, port->membase + UART_CTRL(port));

	अगर (पूर्णांकr) अणु
		ctl = पूर्णांकr | पढ़ोl(port->membase + UART_INTR(port));
		ग_लिखोl(ctl, port->membase + UART_INTR(port));
	पूर्ण

	अगर (locked)
		spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल पूर्णांक mvebu_uart_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (co->index < 0 || co->index >= MVEBU_NR_UARTS)
		वापस -EINVAL;

	port = &mvebu_uart_ports[co->index];

	अगर (!port->mapbase || !port->membase) अणु
		pr_debug("console on ttyMV%i not present\n", co->index);
		वापस -ENODEV;
	पूर्ण

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver mvebu_uart_driver;

अटल काष्ठा console mvebu_uart_console = अणु
	.name	= "ttyMV",
	.ग_लिखो	= mvebu_uart_console_ग_लिखो,
	.device	= uart_console_device,
	.setup	= mvebu_uart_console_setup,
	.flags	= CON_PRINTBUFFER,
	.index	= -1,
	.data	= &mvebu_uart_driver,
पूर्ण;

अटल पूर्णांक __init mvebu_uart_console_init(व्योम)
अणु
	रेजिस्टर_console(&mvebu_uart_console);
	वापस 0;
पूर्ण

console_initcall(mvebu_uart_console_init);


#पूर्ण_अगर /* CONFIG_SERIAL_MVEBU_CONSOLE */

अटल काष्ठा uart_driver mvebu_uart_driver = अणु
	.owner			= THIS_MODULE,
	.driver_name		= DRIVER_NAME,
	.dev_name		= "ttyMV",
	.nr			= MVEBU_NR_UARTS,
#अगर_घोषित CONFIG_SERIAL_MVEBU_CONSOLE
	.cons			= &mvebu_uart_console,
#पूर्ण_अगर
पूर्ण;

#अगर defined(CONFIG_PM)
अटल पूर्णांक mvebu_uart_suspend(काष्ठा device *dev)
अणु
	काष्ठा mvebu_uart *mvuart = dev_get_drvdata(dev);
	काष्ठा uart_port *port = mvuart->port;

	uart_suspend_port(&mvebu_uart_driver, port);

	mvuart->pm_regs.rbr = पढ़ोl(port->membase + UART_RBR(port));
	mvuart->pm_regs.tsh = पढ़ोl(port->membase + UART_TSH(port));
	mvuart->pm_regs.ctrl = पढ़ोl(port->membase + UART_CTRL(port));
	mvuart->pm_regs.पूर्णांकr = पढ़ोl(port->membase + UART_INTR(port));
	mvuart->pm_regs.stat = पढ़ोl(port->membase + UART_STAT);
	mvuart->pm_regs.brdv = पढ़ोl(port->membase + UART_BRDV);
	mvuart->pm_regs.osamp = पढ़ोl(port->membase + UART_OSAMP);

	device_set_wakeup_enable(dev, true);

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_uart_resume(काष्ठा device *dev)
अणु
	काष्ठा mvebu_uart *mvuart = dev_get_drvdata(dev);
	काष्ठा uart_port *port = mvuart->port;

	ग_लिखोl(mvuart->pm_regs.rbr, port->membase + UART_RBR(port));
	ग_लिखोl(mvuart->pm_regs.tsh, port->membase + UART_TSH(port));
	ग_लिखोl(mvuart->pm_regs.ctrl, port->membase + UART_CTRL(port));
	ग_लिखोl(mvuart->pm_regs.पूर्णांकr, port->membase + UART_INTR(port));
	ग_लिखोl(mvuart->pm_regs.stat, port->membase + UART_STAT);
	ग_लिखोl(mvuart->pm_regs.brdv, port->membase + UART_BRDV);
	ग_लिखोl(mvuart->pm_regs.osamp, port->membase + UART_OSAMP);

	uart_resume_port(&mvebu_uart_driver, port);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mvebu_uart_pm_ops = अणु
	.suspend        = mvebu_uart_suspend,
	.resume         = mvebu_uart_resume,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा of_device_id mvebu_uart_of_match[];

/* Counter to keep track of each UART port id when not using CONFIG_OF */
अटल पूर्णांक uart_num_counter;

अटल पूर्णांक mvebu_uart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *reg = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	स्थिर काष्ठा of_device_id *match = of_match_device(mvebu_uart_of_match,
							   &pdev->dev);
	काष्ठा uart_port *port;
	काष्ठा mvebu_uart *mvuart;
	पूर्णांक id, irq;

	अगर (!reg) अणु
		dev_err(&pdev->dev, "no registers defined\n");
		वापस -EINVAL;
	पूर्ण

	/* Assume that all UART ports have a DT alias or none has */
	id = of_alias_get_id(pdev->dev.of_node, "serial");
	अगर (!pdev->dev.of_node || id < 0)
		pdev->id = uart_num_counter++;
	अन्यथा
		pdev->id = id;

	अगर (pdev->id >= MVEBU_NR_UARTS) अणु
		dev_err(&pdev->dev, "cannot have more than %d UART ports\n",
			MVEBU_NR_UARTS);
		वापस -EINVAL;
	पूर्ण

	port = &mvebu_uart_ports[pdev->id];

	spin_lock_init(&port->lock);

	port->dev        = &pdev->dev;
	port->type       = PORT_MVEBU;
	port->ops        = &mvebu_uart_ops;
	port->regshअगरt   = 0;

	port->fअगरosize   = 32;
	port->iotype     = UPIO_MEM32;
	port->flags      = UPF_FIXED_PORT;
	port->line       = pdev->id;

	/*
	 * IRQ number is not stored in this काष्ठाure because we may have two of
	 * them per port (RX and TX). Instead, use the driver UART काष्ठाure
	 * array so called ->irq[].
	 */
	port->irq        = 0;
	port->irqflags   = 0;
	port->mapbase    = reg->start;

	port->membase = devm_ioremap_resource(&pdev->dev, reg);
	अगर (IS_ERR(port->membase))
		वापस PTR_ERR(port->membase);

	mvuart = devm_kzalloc(&pdev->dev, माप(काष्ठा mvebu_uart),
			      GFP_KERNEL);
	अगर (!mvuart)
		वापस -ENOMEM;

	/* Get controller data depending on the compatible string */
	mvuart->data = (काष्ठा mvebu_uart_driver_data *)match->data;
	mvuart->port = port;

	port->निजी_data = mvuart;
	platक्रमm_set_drvdata(pdev, mvuart);

	/* Get fixed घड़ी frequency */
	mvuart->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(mvuart->clk)) अणु
		अगर (PTR_ERR(mvuart->clk) == -EPROBE_DEFER)
			वापस PTR_ERR(mvuart->clk);

		अगर (IS_EXTENDED(port)) अणु
			dev_err(&pdev->dev, "unable to get UART clock\n");
			वापस PTR_ERR(mvuart->clk);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!clk_prepare_enable(mvuart->clk))
			port->uartclk = clk_get_rate(mvuart->clk);
	पूर्ण

	/* Manage पूर्णांकerrupts */
	अगर (platक्रमm_irq_count(pdev) == 1) अणु
		/* Old bindings: no name on the single unamed UART0 IRQ */
		irq = platक्रमm_get_irq(pdev, 0);
		अगर (irq < 0)
			वापस irq;

		mvuart->irq[UART_IRQ_SUM] = irq;
	पूर्ण अन्यथा अणु
		/*
		 * New bindings: named पूर्णांकerrupts (RX, TX) क्रम both UARTS,
		 * only make use of uart-rx and uart-tx पूर्णांकerrupts, करो not use
		 * uart-sum of UART0 port.
		 */
		irq = platक्रमm_get_irq_byname(pdev, "uart-rx");
		अगर (irq < 0)
			वापस irq;

		mvuart->irq[UART_RX_IRQ] = irq;

		irq = platक्रमm_get_irq_byname(pdev, "uart-tx");
		अगर (irq < 0)
			वापस irq;

		mvuart->irq[UART_TX_IRQ] = irq;
	पूर्ण

	/* UART Soft Reset*/
	ग_लिखोl(CTRL_SOFT_RST, port->membase + UART_CTRL(port));
	udelay(1);
	ग_लिखोl(0, port->membase + UART_CTRL(port));

	वापस uart_add_one_port(&mvebu_uart_driver, port);
पूर्ण

अटल काष्ठा mvebu_uart_driver_data uart_std_driver_data = अणु
	.is_ext = false,
	.regs.rbr = UART_STD_RBR,
	.regs.tsh = UART_STD_TSH,
	.regs.ctrl = UART_STD_CTRL1,
	.regs.पूर्णांकr = UART_STD_CTRL2,
	.flags.ctrl_tx_rdy_पूर्णांक = CTRL_STD_TX_RDY_INT,
	.flags.ctrl_rx_rdy_पूर्णांक = CTRL_STD_RX_RDY_INT,
	.flags.stat_tx_rdy = STAT_STD_TX_RDY,
	.flags.stat_rx_rdy = STAT_STD_RX_RDY,
पूर्ण;

अटल काष्ठा mvebu_uart_driver_data uart_ext_driver_data = अणु
	.is_ext = true,
	.regs.rbr = UART_EXT_RBR,
	.regs.tsh = UART_EXT_TSH,
	.regs.ctrl = UART_EXT_CTRL1,
	.regs.पूर्णांकr = UART_EXT_CTRL2,
	.flags.ctrl_tx_rdy_पूर्णांक = CTRL_EXT_TX_RDY_INT,
	.flags.ctrl_rx_rdy_पूर्णांक = CTRL_EXT_RX_RDY_INT,
	.flags.stat_tx_rdy = STAT_EXT_TX_RDY,
	.flags.stat_rx_rdy = STAT_EXT_RX_RDY,
पूर्ण;

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id mvebu_uart_of_match[] = अणु
	अणु
		.compatible = "marvell,armada-3700-uart",
		.data = (व्योम *)&uart_std_driver_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-3700-uart-ext",
		.data = (व्योम *)&uart_ext_driver_data,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver mvebu_uart_platक्रमm_driver = अणु
	.probe	= mvebu_uart_probe,
	.driver	= अणु
		.name  = "mvebu-uart",
		.of_match_table = of_match_ptr(mvebu_uart_of_match),
		.suppress_bind_attrs = true,
#अगर defined(CONFIG_PM)
		.pm	= &mvebu_uart_pm_ops,
#पूर्ण_अगर /* CONFIG_PM */
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mvebu_uart_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&mvebu_uart_driver);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&mvebu_uart_platक्रमm_driver);
	अगर (ret)
		uart_unरेजिस्टर_driver(&mvebu_uart_driver);

	वापस ret;
पूर्ण
arch_initcall(mvebu_uart_init);
