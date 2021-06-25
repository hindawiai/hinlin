<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Derived from many drivers using generic_serial पूर्णांकerface.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 *
 *  Serial driver क्रम BCM63xx पूर्णांकegrated UART.
 *
 * Hardware flow control was _not_ tested since I only have RX/TX on
 * my board.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/console.h>
#समावेश <linux/clk.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_bcm63xx.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

#घोषणा BCM63XX_NR_UARTS	2

अटल काष्ठा uart_port ports[BCM63XX_NR_UARTS];

/*
 * rx पूर्णांकerrupt mask / stat
 *
 * mask:
 *  - rx fअगरo full
 *  - rx fअगरo above threshold
 *  - rx fअगरo not empty क्रम too दीर्घ
 */
#घोषणा UART_RX_INT_MASK	(UART_IR_MASK(UART_IR_RXOVER) |		\
				UART_IR_MASK(UART_IR_RXTHRESH) |	\
				UART_IR_MASK(UART_IR_RXTIMEOUT))

#घोषणा UART_RX_INT_STAT	(UART_IR_STAT(UART_IR_RXOVER) |		\
				UART_IR_STAT(UART_IR_RXTHRESH) |	\
				UART_IR_STAT(UART_IR_RXTIMEOUT))

/*
 * tx पूर्णांकerrupt mask / stat
 *
 * mask:
 * - tx fअगरo empty
 * - tx fअगरo below threshold
 */
#घोषणा UART_TX_INT_MASK	(UART_IR_MASK(UART_IR_TXEMPTY) |	\
				UART_IR_MASK(UART_IR_TXTRESH))

#घोषणा UART_TX_INT_STAT	(UART_IR_STAT(UART_IR_TXEMPTY) |	\
				UART_IR_STAT(UART_IR_TXTRESH))

/*
 * बाह्यal input पूर्णांकerrupt
 *
 * mask: any edge on CTS, DCD
 */
#घोषणा UART_EXTINP_INT_MASK	(UART_EXTINP_IRMASK(UART_EXTINP_IR_CTS) | \
				 UART_EXTINP_IRMASK(UART_EXTINP_IR_DCD))

/*
 * handy uart रेजिस्टर accessor
 */
अटल अंतरभूत अचिन्हित पूर्णांक bcm_uart_पढ़ोl(काष्ठा uart_port *port,
					 अचिन्हित पूर्णांक offset)
अणु
	वापस __raw_पढ़ोl(port->membase + offset);
पूर्ण

अटल अंतरभूत व्योम bcm_uart_ग_लिखोl(काष्ठा uart_port *port,
				  अचिन्हित पूर्णांक value, अचिन्हित पूर्णांक offset)
अणु
	__raw_ग_लिखोl(value, port->membase + offset);
पूर्ण

/*
 * serial core request to check अगर uart tx fअगरo is empty
 */
अटल अचिन्हित पूर्णांक bcm_uart_tx_empty(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक val;

	val = bcm_uart_पढ़ोl(port, UART_IR_REG);
	वापस (val & UART_IR_STAT(UART_IR_TXEMPTY)) ? 1 : 0;
पूर्ण

/*
 * serial core request to set RTS and DTR pin state and loopback mode
 */
अटल व्योम bcm_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	अचिन्हित पूर्णांक val;

	val = bcm_uart_पढ़ोl(port, UART_MCTL_REG);
	val &= ~(UART_MCTL_DTR_MASK | UART_MCTL_RTS_MASK);
	/* invert of written value is reflected on the pin */
	अगर (!(mctrl & TIOCM_DTR))
		val |= UART_MCTL_DTR_MASK;
	अगर (!(mctrl & TIOCM_RTS))
		val |= UART_MCTL_RTS_MASK;
	bcm_uart_ग_लिखोl(port, val, UART_MCTL_REG);

	val = bcm_uart_पढ़ोl(port, UART_CTL_REG);
	अगर (mctrl & TIOCM_LOOP)
		val |= UART_CTL_LOOPBACK_MASK;
	अन्यथा
		val &= ~UART_CTL_LOOPBACK_MASK;
	bcm_uart_ग_लिखोl(port, val, UART_CTL_REG);
पूर्ण

/*
 * serial core request to वापस RI, CTS, DCD and DSR pin state
 */
अटल अचिन्हित पूर्णांक bcm_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक val, mctrl;

	mctrl = 0;
	val = bcm_uart_पढ़ोl(port, UART_EXTINP_REG);
	अगर (val & UART_EXTINP_RI_MASK)
		mctrl |= TIOCM_RI;
	अगर (val & UART_EXTINP_CTS_MASK)
		mctrl |= TIOCM_CTS;
	अगर (val & UART_EXTINP_DCD_MASK)
		mctrl |= TIOCM_CD;
	अगर (val & UART_EXTINP_DSR_MASK)
		mctrl |= TIOCM_DSR;
	वापस mctrl;
पूर्ण

/*
 * serial core request to disable tx ASAP (used क्रम flow control)
 */
अटल व्योम bcm_uart_stop_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक val;

	val = bcm_uart_पढ़ोl(port, UART_CTL_REG);
	val &= ~(UART_CTL_TXEN_MASK);
	bcm_uart_ग_लिखोl(port, val, UART_CTL_REG);

	val = bcm_uart_पढ़ोl(port, UART_IR_REG);
	val &= ~UART_TX_INT_MASK;
	bcm_uart_ग_लिखोl(port, val, UART_IR_REG);
पूर्ण

/*
 * serial core request to (re)enable tx
 */
अटल व्योम bcm_uart_start_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक val;

	val = bcm_uart_पढ़ोl(port, UART_IR_REG);
	val |= UART_TX_INT_MASK;
	bcm_uart_ग_लिखोl(port, val, UART_IR_REG);

	val = bcm_uart_पढ़ोl(port, UART_CTL_REG);
	val |= UART_CTL_TXEN_MASK;
	bcm_uart_ग_लिखोl(port, val, UART_CTL_REG);
पूर्ण

/*
 * serial core request to stop rx, called beक्रमe port shutकरोwn
 */
अटल व्योम bcm_uart_stop_rx(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक val;

	val = bcm_uart_पढ़ोl(port, UART_IR_REG);
	val &= ~UART_RX_INT_MASK;
	bcm_uart_ग_लिखोl(port, val, UART_IR_REG);
पूर्ण

/*
 * serial core request to enable modem status पूर्णांकerrupt reporting
 */
अटल व्योम bcm_uart_enable_ms(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक val;

	val = bcm_uart_पढ़ोl(port, UART_IR_REG);
	val |= UART_IR_MASK(UART_IR_EXTIP);
	bcm_uart_ग_लिखोl(port, val, UART_IR_REG);
पूर्ण

/*
 * serial core request to start/stop emitting अवरोध अक्षर
 */
अटल व्योम bcm_uart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक ctl)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(&port->lock, flags);

	val = bcm_uart_पढ़ोl(port, UART_CTL_REG);
	अगर (ctl)
		val |= UART_CTL_XMITBRK_MASK;
	अन्यथा
		val &= ~UART_CTL_XMITBRK_MASK;
	bcm_uart_ग_लिखोl(port, val, UART_CTL_REG);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/*
 * वापस port type in string क्रमmat
 */
अटल स्थिर अक्षर *bcm_uart_type(काष्ठा uart_port *port)
अणु
	वापस (port->type == PORT_BCM63XX) ? "bcm63xx_uart" : शून्य;
पूर्ण

/*
 * पढ़ो all अक्षरs in rx fअगरo and send them to core
 */
अटल व्योम bcm_uart_करो_rx(काष्ठा uart_port *port)
अणु
	काष्ठा tty_port *tty_port = &port->state->port;
	अचिन्हित पूर्णांक max_count;

	/* limit number of अक्षर पढ़ो in पूर्णांकerrupt, should not be
	 * higher than fअगरo size anyway since we're much faster than
	 * serial port */
	max_count = 32;
	करो अणु
		अचिन्हित पूर्णांक iestat, c, cstat;
		अक्षर flag;

		/* get overrun/fअगरo empty inक्रमmation from ier
		 * रेजिस्टर */
		iestat = bcm_uart_पढ़ोl(port, UART_IR_REG);

		अगर (unlikely(iestat & UART_IR_STAT(UART_IR_RXOVER))) अणु
			अचिन्हित पूर्णांक val;

			/* fअगरo reset is required to clear
			 * पूर्णांकerrupt */
			val = bcm_uart_पढ़ोl(port, UART_CTL_REG);
			val |= UART_CTL_RSTRXFIFO_MASK;
			bcm_uart_ग_लिखोl(port, val, UART_CTL_REG);

			port->icount.overrun++;
			tty_insert_flip_अक्षर(tty_port, 0, TTY_OVERRUN);
		पूर्ण

		अगर (!(iestat & UART_IR_STAT(UART_IR_RXNOTEMPTY)))
			अवरोध;

		cstat = c = bcm_uart_पढ़ोl(port, UART_FIFO_REG);
		port->icount.rx++;
		flag = TTY_NORMAL;
		c &= 0xff;

		अगर (unlikely((cstat & UART_FIFO_ANYERR_MASK))) अणु
			/* करो stats first */
			अगर (cstat & UART_FIFO_BRKDET_MASK) अणु
				port->icount.brk++;
				अगर (uart_handle_अवरोध(port))
					जारी;
			पूर्ण

			अगर (cstat & UART_FIFO_PARERR_MASK)
				port->icount.parity++;
			अगर (cstat & UART_FIFO_FRAMEERR_MASK)
				port->icount.frame++;

			/* update flag wrt पढ़ो_status_mask */
			cstat &= port->पढ़ो_status_mask;
			अगर (cstat & UART_FIFO_BRKDET_MASK)
				flag = TTY_BREAK;
			अगर (cstat & UART_FIFO_FRAMEERR_MASK)
				flag = TTY_FRAME;
			अगर (cstat & UART_FIFO_PARERR_MASK)
				flag = TTY_PARITY;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(port, c))
			जारी;


		अगर ((cstat & port->ignore_status_mask) == 0)
			tty_insert_flip_अक्षर(tty_port, c, flag);

	पूर्ण जबतक (--max_count);

	tty_flip_buffer_push(tty_port);
पूर्ण

/*
 * fill tx fअगरo with अक्षरs to send, stop when fअगरo is about to be full
 * or when all अक्षरs have been sent.
 */
अटल व्योम bcm_uart_करो_tx(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit;
	अचिन्हित पूर्णांक val, max_count;

	अगर (port->x_अक्षर) अणु
		bcm_uart_ग_लिखोl(port, port->x_अक्षर, UART_FIFO_REG);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (uart_tx_stopped(port)) अणु
		bcm_uart_stop_tx(port);
		वापस;
	पूर्ण

	xmit = &port->state->xmit;
	अगर (uart_circ_empty(xmit))
		जाओ txq_empty;

	val = bcm_uart_पढ़ोl(port, UART_MCTL_REG);
	val = (val & UART_MCTL_TXFIFOFILL_MASK) >> UART_MCTL_TXFIFOFILL_SHIFT;
	max_count = port->fअगरosize - val;

	जबतक (max_count--) अणु
		अचिन्हित पूर्णांक c;

		c = xmit->buf[xmit->tail];
		bcm_uart_ग_लिखोl(port, c, UART_FIFO_REG);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (uart_circ_empty(xmit))
		जाओ txq_empty;
	वापस;

txq_empty:
	/* nothing to send, disable transmit पूर्णांकerrupt */
	val = bcm_uart_पढ़ोl(port, UART_IR_REG);
	val &= ~UART_TX_INT_MASK;
	bcm_uart_ग_लिखोl(port, val, UART_IR_REG);
	वापस;
पूर्ण

/*
 * process uart पूर्णांकerrupt
 */
अटल irqवापस_t bcm_uart_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port;
	अचिन्हित पूर्णांक irqstat;

	port = dev_id;
	spin_lock(&port->lock);

	irqstat = bcm_uart_पढ़ोl(port, UART_IR_REG);
	अगर (irqstat & UART_RX_INT_STAT)
		bcm_uart_करो_rx(port);

	अगर (irqstat & UART_TX_INT_STAT)
		bcm_uart_करो_tx(port);

	अगर (irqstat & UART_IR_MASK(UART_IR_EXTIP)) अणु
		अचिन्हित पूर्णांक estat;

		estat = bcm_uart_पढ़ोl(port, UART_EXTINP_REG);
		अगर (estat & UART_EXTINP_IRSTAT(UART_EXTINP_IR_CTS))
			uart_handle_cts_change(port,
					       estat & UART_EXTINP_CTS_MASK);
		अगर (estat & UART_EXTINP_IRSTAT(UART_EXTINP_IR_DCD))
			uart_handle_dcd_change(port,
					       estat & UART_EXTINP_DCD_MASK);
	पूर्ण

	spin_unlock(&port->lock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * enable rx & tx operation on uart
 */
अटल व्योम bcm_uart_enable(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक val;

	val = bcm_uart_पढ़ोl(port, UART_CTL_REG);
	val |= (UART_CTL_BRGEN_MASK | UART_CTL_TXEN_MASK | UART_CTL_RXEN_MASK);
	bcm_uart_ग_लिखोl(port, val, UART_CTL_REG);
पूर्ण

/*
 * disable rx & tx operation on uart
 */
अटल व्योम bcm_uart_disable(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक val;

	val = bcm_uart_पढ़ोl(port, UART_CTL_REG);
	val &= ~(UART_CTL_BRGEN_MASK | UART_CTL_TXEN_MASK |
		 UART_CTL_RXEN_MASK);
	bcm_uart_ग_लिखोl(port, val, UART_CTL_REG);
पूर्ण

/*
 * clear all unपढ़ो data in rx fअगरo and unsent data in tx fअगरo
 */
अटल व्योम bcm_uart_flush(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक val;

	/* empty rx and tx fअगरo */
	val = bcm_uart_पढ़ोl(port, UART_CTL_REG);
	val |= UART_CTL_RSTRXFIFO_MASK | UART_CTL_RSTTXFIFO_MASK;
	bcm_uart_ग_लिखोl(port, val, UART_CTL_REG);

	/* पढ़ो any pending अक्षर to make sure all irq status are
	 * cleared */
	(व्योम)bcm_uart_पढ़ोl(port, UART_FIFO_REG);
पूर्ण

/*
 * serial core request to initialize uart and start rx operation
 */
अटल पूर्णांक bcm_uart_startup(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* mask all irq and flush port */
	bcm_uart_disable(port);
	bcm_uart_ग_लिखोl(port, 0, UART_IR_REG);
	bcm_uart_flush(port);

	/* clear any pending बाह्यal input पूर्णांकerrupt */
	(व्योम)bcm_uart_पढ़ोl(port, UART_EXTINP_REG);

	/* set rx/tx fअगरo thresh to fअगरo half size */
	val = bcm_uart_पढ़ोl(port, UART_MCTL_REG);
	val &= ~(UART_MCTL_RXFIFOTHRESH_MASK | UART_MCTL_TXFIFOTHRESH_MASK);
	val |= (port->fअगरosize / 2) << UART_MCTL_RXFIFOTHRESH_SHIFT;
	val |= (port->fअगरosize / 2) << UART_MCTL_TXFIFOTHRESH_SHIFT;
	bcm_uart_ग_लिखोl(port, val, UART_MCTL_REG);

	/* set rx fअगरo समयout to 1 अक्षर समय */
	val = bcm_uart_पढ़ोl(port, UART_CTL_REG);
	val &= ~UART_CTL_RXTMOUTCNT_MASK;
	val |= 1 << UART_CTL_RXTMOUTCNT_SHIFT;
	bcm_uart_ग_लिखोl(port, val, UART_CTL_REG);

	/* report any edge on dcd and cts */
	val = UART_EXTINP_INT_MASK;
	val |= UART_EXTINP_DCD_NOSENSE_MASK;
	val |= UART_EXTINP_CTS_NOSENSE_MASK;
	bcm_uart_ग_लिखोl(port, val, UART_EXTINP_REG);

	/* रेजिस्टर irq and enable rx पूर्णांकerrupts */
	ret = request_irq(port->irq, bcm_uart_पूर्णांकerrupt, 0,
			  dev_name(port->dev), port);
	अगर (ret)
		वापस ret;
	bcm_uart_ग_लिखोl(port, UART_RX_INT_MASK, UART_IR_REG);
	bcm_uart_enable(port);
	वापस 0;
पूर्ण

/*
 * serial core request to flush & disable uart
 */
अटल व्योम bcm_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	bcm_uart_ग_लिखोl(port, 0, UART_IR_REG);
	spin_unlock_irqrestore(&port->lock, flags);

	bcm_uart_disable(port);
	bcm_uart_flush(port);
	मुक्त_irq(port->irq, port);
पूर्ण

/*
 * serial core request to change current uart setting
 */
अटल व्योम bcm_uart_set_termios(काष्ठा uart_port *port,
				 काष्ठा ktermios *new,
				 काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक ctl, baud, quot, ier;
	अचिन्हित दीर्घ flags;
	पूर्णांक tries;

	spin_lock_irqsave(&port->lock, flags);

	/* Drain the hot tub fully beक्रमe we घातer it off क्रम the wपूर्णांकer. */
	क्रम (tries = 3; !bcm_uart_tx_empty(port) && tries; tries--)
		mdelay(10);

	/* disable uart जबतक changing speed */
	bcm_uart_disable(port);
	bcm_uart_flush(port);

	/* update Control रेजिस्टर */
	ctl = bcm_uart_पढ़ोl(port, UART_CTL_REG);
	ctl &= ~UART_CTL_BITSPERSYM_MASK;

	चयन (new->c_cflag & CSIZE) अणु
	हाल CS5:
		ctl |= (0 << UART_CTL_BITSPERSYM_SHIFT);
		अवरोध;
	हाल CS6:
		ctl |= (1 << UART_CTL_BITSPERSYM_SHIFT);
		अवरोध;
	हाल CS7:
		ctl |= (2 << UART_CTL_BITSPERSYM_SHIFT);
		अवरोध;
	शेष:
		ctl |= (3 << UART_CTL_BITSPERSYM_SHIFT);
		अवरोध;
	पूर्ण

	ctl &= ~UART_CTL_STOPBITS_MASK;
	अगर (new->c_cflag & CSTOPB)
		ctl |= UART_CTL_STOPBITS_2;
	अन्यथा
		ctl |= UART_CTL_STOPBITS_1;

	ctl &= ~(UART_CTL_RXPAREN_MASK | UART_CTL_TXPAREN_MASK);
	अगर (new->c_cflag & PARENB)
		ctl |= (UART_CTL_RXPAREN_MASK | UART_CTL_TXPAREN_MASK);
	ctl &= ~(UART_CTL_RXPAREVEN_MASK | UART_CTL_TXPAREVEN_MASK);
	अगर (new->c_cflag & PARODD)
		ctl |= (UART_CTL_RXPAREVEN_MASK | UART_CTL_TXPAREVEN_MASK);
	bcm_uart_ग_लिखोl(port, ctl, UART_CTL_REG);

	/* update Baudword रेजिस्टर */
	baud = uart_get_baud_rate(port, new, old, 0, port->uartclk / 16);
	quot = uart_get_भागisor(port, baud) - 1;
	bcm_uart_ग_लिखोl(port, quot, UART_BAUD_REG);

	/* update Interrupt रेजिस्टर */
	ier = bcm_uart_पढ़ोl(port, UART_IR_REG);

	ier &= ~UART_IR_MASK(UART_IR_EXTIP);
	अगर (UART_ENABLE_MS(port, new->c_cflag))
		ier |= UART_IR_MASK(UART_IR_EXTIP);

	bcm_uart_ग_लिखोl(port, ier, UART_IR_REG);

	/* update पढ़ो/ignore mask */
	port->पढ़ो_status_mask = UART_FIFO_VALID_MASK;
	अगर (new->c_अगरlag & INPCK) अणु
		port->पढ़ो_status_mask |= UART_FIFO_FRAMEERR_MASK;
		port->पढ़ो_status_mask |= UART_FIFO_PARERR_MASK;
	पूर्ण
	अगर (new->c_अगरlag & (IGNBRK | BRKINT))
		port->पढ़ो_status_mask |= UART_FIFO_BRKDET_MASK;

	port->ignore_status_mask = 0;
	अगर (new->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= UART_FIFO_PARERR_MASK;
	अगर (new->c_अगरlag & IGNBRK)
		port->ignore_status_mask |= UART_FIFO_BRKDET_MASK;
	अगर (!(new->c_cflag & CREAD))
		port->ignore_status_mask |= UART_FIFO_VALID_MASK;

	uart_update_समयout(port, new->c_cflag, baud);
	bcm_uart_enable(port);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/*
 * serial core request to claim uart iomem
 */
अटल पूर्णांक bcm_uart_request_port(काष्ठा uart_port *port)
अणु
	/* UARTs always present */
	वापस 0;
पूर्ण

/*
 * serial core request to release uart iomem
 */
अटल व्योम bcm_uart_release_port(काष्ठा uart_port *port)
अणु
	/* Nothing to release ... */
पूर्ण

/*
 * serial core request to करो any port required स्वतःconfiguration
 */
अटल व्योम bcm_uart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE) अणु
		अगर (bcm_uart_request_port(port))
			वापस;
		port->type = PORT_BCM63XX;
	पूर्ण
पूर्ण

/*
 * serial core request to check that port inक्रमmation in serinfo are
 * suitable
 */
अटल पूर्णांक bcm_uart_verअगरy_port(काष्ठा uart_port *port,
				काष्ठा serial_काष्ठा *serinfo)
अणु
	अगर (port->type != PORT_BCM63XX)
		वापस -EINVAL;
	अगर (port->irq != serinfo->irq)
		वापस -EINVAL;
	अगर (port->iotype != serinfo->io_type)
		वापस -EINVAL;
	अगर (port->mapbase != (अचिन्हित दीर्घ)serinfo->iomem_base)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/* serial core callbacks */
अटल स्थिर काष्ठा uart_ops bcm_uart_ops = अणु
	.tx_empty	= bcm_uart_tx_empty,
	.get_mctrl	= bcm_uart_get_mctrl,
	.set_mctrl	= bcm_uart_set_mctrl,
	.start_tx	= bcm_uart_start_tx,
	.stop_tx	= bcm_uart_stop_tx,
	.stop_rx	= bcm_uart_stop_rx,
	.enable_ms	= bcm_uart_enable_ms,
	.अवरोध_ctl	= bcm_uart_अवरोध_ctl,
	.startup	= bcm_uart_startup,
	.shutकरोwn	= bcm_uart_shutकरोwn,
	.set_termios	= bcm_uart_set_termios,
	.type		= bcm_uart_type,
	.release_port	= bcm_uart_release_port,
	.request_port	= bcm_uart_request_port,
	.config_port	= bcm_uart_config_port,
	.verअगरy_port	= bcm_uart_verअगरy_port,
पूर्ण;



#अगर_घोषित CONFIG_SERIAL_BCM63XX_CONSOLE
अटल व्योम रुको_क्रम_xmitr(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक पंचांगout;

	/* Wait up to 10ms क्रम the अक्षरacter(s) to be sent. */
	पंचांगout = 10000;
	जबतक (--पंचांगout) अणु
		अचिन्हित पूर्णांक val;

		val = bcm_uart_पढ़ोl(port, UART_IR_REG);
		अगर (val & UART_IR_STAT(UART_IR_TXEMPTY))
			अवरोध;
		udelay(1);
	पूर्ण

	/* Wait up to 1s क्रम flow control अगर necessary */
	अगर (port->flags & UPF_CONS_FLOW) अणु
		पंचांगout = 1000000;
		जबतक (--पंचांगout) अणु
			अचिन्हित पूर्णांक val;

			val = bcm_uart_पढ़ोl(port, UART_EXTINP_REG);
			अगर (val & UART_EXTINP_CTS_MASK)
				अवरोध;
			udelay(1);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * output given अक्षर
 */
अटल व्योम bcm_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	रुको_क्रम_xmitr(port);
	bcm_uart_ग_लिखोl(port, ch, UART_FIFO_REG);
पूर्ण

/*
 * console core request to output given string
 */
अटल व्योम bcm_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
			      अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_port *port;
	अचिन्हित दीर्घ flags;
	पूर्णांक locked;

	port = &ports[co->index];

	local_irq_save(flags);
	अगर (port->sysrq) अणु
		/* bcm_uart_पूर्णांकerrupt() alपढ़ोy took the lock */
		locked = 0;
	पूर्ण अन्यथा अगर (oops_in_progress) अणु
		locked = spin_trylock(&port->lock);
	पूर्ण अन्यथा अणु
		spin_lock(&port->lock);
		locked = 1;
	पूर्ण

	/* call helper to deal with \ल\न */
	uart_console_ग_लिखो(port, s, count, bcm_console_अक्षर_दो);

	/* and रुको क्रम अक्षर to be transmitted */
	रुको_क्रम_xmitr(port);

	अगर (locked)
		spin_unlock(&port->lock);
	local_irq_restore(flags);
पूर्ण

/*
 * console core request to setup given console, find matching uart
 * port and setup it.
 */
अटल पूर्णांक bcm_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (co->index < 0 || co->index >= BCM63XX_NR_UARTS)
		वापस -EINVAL;
	port = &ports[co->index];
	अगर (!port->membase)
		वापस -ENODEV;
	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver bcm_uart_driver;

अटल काष्ठा console bcm63xx_console = अणु
	.name		= "ttyS",
	.ग_लिखो		= bcm_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= bcm_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &bcm_uart_driver,
पूर्ण;

अटल पूर्णांक __init bcm63xx_console_init(व्योम)
अणु
	रेजिस्टर_console(&bcm63xx_console);
	वापस 0;
पूर्ण

console_initcall(bcm63xx_console_init);

अटल व्योम bcm_early_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	uart_console_ग_लिखो(&dev->port, s, n, bcm_console_अक्षर_दो);
	रुको_क्रम_xmitr(&dev->port);
पूर्ण

अटल पूर्णांक __init bcm_early_console_setup(काष्ठा earlycon_device *device,
					  स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->con->ग_लिखो = bcm_early_ग_लिखो;
	वापस 0;
पूर्ण

OF_EARLYCON_DECLARE(bcm63xx_uart, "brcm,bcm6345-uart", bcm_early_console_setup);

#घोषणा BCM63XX_CONSOLE	(&bcm63xx_console)
#अन्यथा
#घोषणा BCM63XX_CONSOLE	शून्य
#पूर्ण_अगर /* CONFIG_SERIAL_BCM63XX_CONSOLE */

अटल काष्ठा uart_driver bcm_uart_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "bcm63xx_uart",
	.dev_name	= "ttyS",
	.major		= TTY_MAJOR,
	.minor		= 64,
	.nr		= BCM63XX_NR_UARTS,
	.cons		= BCM63XX_CONSOLE,
पूर्ण;

/*
 * platक्रमm driver probe/हटाओ callback
 */
अटल पूर्णांक bcm_uart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res_mem, *res_irq;
	काष्ठा uart_port *port;
	काष्ठा clk *clk;
	पूर्णांक ret;

	अगर (pdev->dev.of_node) अणु
		pdev->id = of_alias_get_id(pdev->dev.of_node, "serial");

		अगर (pdev->id < 0)
			pdev->id = of_alias_get_id(pdev->dev.of_node, "uart");
	पूर्ण

	अगर (pdev->id < 0 || pdev->id >= BCM63XX_NR_UARTS)
		वापस -EINVAL;

	port = &ports[pdev->id];
	अगर (port->membase)
		वापस -EBUSY;
	स_रखो(port, 0, माप(*port));

	res_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res_mem)
		वापस -ENODEV;

	port->mapbase = res_mem->start;
	port->membase = devm_ioremap_resource(&pdev->dev, res_mem);
	अगर (IS_ERR(port->membase))
		वापस PTR_ERR(port->membase);

	res_irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res_irq)
		वापस -ENODEV;

	clk = clk_get(&pdev->dev, "refclk");
	अगर (IS_ERR(clk) && pdev->dev.of_node)
		clk = of_clk_get(pdev->dev.of_node, 0);

	अगर (IS_ERR(clk))
		वापस -ENODEV;

	port->iotype = UPIO_MEM;
	port->irq = res_irq->start;
	port->ops = &bcm_uart_ops;
	port->flags = UPF_BOOT_AUTOCONF;
	port->dev = &pdev->dev;
	port->fअगरosize = 16;
	port->uartclk = clk_get_rate(clk) / 2;
	port->line = pdev->id;
	port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_BCM63XX_CONSOLE);
	clk_put(clk);

	ret = uart_add_one_port(&bcm_uart_driver, port);
	अगर (ret) अणु
		ports[pdev->id].membase = शून्य;
		वापस ret;
	पूर्ण
	platक्रमm_set_drvdata(pdev, port);
	वापस 0;
पूर्ण

अटल पूर्णांक bcm_uart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port;

	port = platक्रमm_get_drvdata(pdev);
	uart_हटाओ_one_port(&bcm_uart_driver, port);
	/* mark port as मुक्त */
	ports[pdev->id].membase = शून्य;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm63xx_of_match[] = अणु
	अणु .compatible = "brcm,bcm6345-uart" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm63xx_of_match);

/*
 * platक्रमm driver stuff
 */
अटल काष्ठा platक्रमm_driver bcm_uart_platक्रमm_driver = अणु
	.probe	= bcm_uart_probe,
	.हटाओ	= bcm_uart_हटाओ,
	.driver	= अणु
		.name  = "bcm63xx_uart",
		.of_match_table = bcm63xx_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init bcm_uart_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&bcm_uart_driver);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&bcm_uart_platक्रमm_driver);
	अगर (ret)
		uart_unरेजिस्टर_driver(&bcm_uart_driver);

	वापस ret;
पूर्ण

अटल व्योम __निकास bcm_uart_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&bcm_uart_platक्रमm_driver);
	uart_unरेजिस्टर_driver(&bcm_uart_driver);
पूर्ण

module_init(bcm_uart_init);
module_निकास(bcm_uart_निकास);

MODULE_AUTHOR("Maxime Bizon <mbizon@freebox.fr>");
MODULE_DESCRIPTION("Broadcom 63xx integrated uart driver");
MODULE_LICENSE("GPL");
