<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Based on drivers/अक्षर/serial.c, by Linus Torvalds, Theoकरोre Ts'o.
 *
 * Copyright (C) 2004 Infineon IFAP DC COM CPE
 * Copyright (C) 2007 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2007 John Crispin <john@phrozen.org>
 * Copyright (C) 2010 Thomas Langer, <thomas.langer@lantiq.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/lantiq.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

#घोषणा PORT_LTQ_ASC		111
#घोषणा MAXPORTS		2
#घोषणा UART_DUMMY_UER_RX	1
#घोषणा DRVNAME			"lantiq,asc"
#अगर_घोषित __BIG_ENDIAN
#घोषणा LTQ_ASC_TBUF		(0x0020 + 3)
#घोषणा LTQ_ASC_RBUF		(0x0024 + 3)
#अन्यथा
#घोषणा LTQ_ASC_TBUF		0x0020
#घोषणा LTQ_ASC_RBUF		0x0024
#पूर्ण_अगर
#घोषणा LTQ_ASC_FSTAT		0x0048
#घोषणा LTQ_ASC_WHBSTATE	0x0018
#घोषणा LTQ_ASC_STATE		0x0014
#घोषणा LTQ_ASC_IRNCR		0x00F8
#घोषणा LTQ_ASC_CLC		0x0000
#घोषणा LTQ_ASC_ID		0x0008
#घोषणा LTQ_ASC_PISEL		0x0004
#घोषणा LTQ_ASC_TXFCON		0x0044
#घोषणा LTQ_ASC_RXFCON		0x0040
#घोषणा LTQ_ASC_CON		0x0010
#घोषणा LTQ_ASC_BG		0x0050
#घोषणा LTQ_ASC_IRNREN		0x00F4

#घोषणा ASC_IRNREN_TX		0x1
#घोषणा ASC_IRNREN_RX		0x2
#घोषणा ASC_IRNREN_ERR		0x4
#घोषणा ASC_IRNREN_TX_BUF	0x8
#घोषणा ASC_IRNCR_TIR		0x1
#घोषणा ASC_IRNCR_RIR		0x2
#घोषणा ASC_IRNCR_EIR		0x4
#घोषणा ASC_IRNCR_MASK		GENMASK(2, 0)

#घोषणा ASCOPT_CSIZE		0x3
#घोषणा TXFIFO_FL		1
#घोषणा RXFIFO_FL		1
#घोषणा ASCCLC_DISS		0x2
#घोषणा ASCCLC_RMCMASK		0x0000FF00
#घोषणा ASCCLC_RMCOFFSET	8
#घोषणा ASCCON_M_8ASYNC		0x0
#घोषणा ASCCON_M_7ASYNC		0x2
#घोषणा ASCCON_ODD		0x00000020
#घोषणा ASCCON_STP		0x00000080
#घोषणा ASCCON_BRS		0x00000100
#घोषणा ASCCON_FDE		0x00000200
#घोषणा ASCCON_R		0x00008000
#घोषणा ASCCON_FEN		0x00020000
#घोषणा ASCCON_ROEN		0x00080000
#घोषणा ASCCON_TOEN		0x00100000
#घोषणा ASCSTATE_PE		0x00010000
#घोषणा ASCSTATE_FE		0x00020000
#घोषणा ASCSTATE_ROE		0x00080000
#घोषणा ASCSTATE_ANY		(ASCSTATE_ROE|ASCSTATE_PE|ASCSTATE_FE)
#घोषणा ASCWHBSTATE_CLRREN	0x00000001
#घोषणा ASCWHBSTATE_SETREN	0x00000002
#घोषणा ASCWHBSTATE_CLRPE	0x00000004
#घोषणा ASCWHBSTATE_CLRFE	0x00000008
#घोषणा ASCWHBSTATE_CLRROE	0x00000020
#घोषणा ASCTXFCON_TXFEN		0x0001
#घोषणा ASCTXFCON_TXFFLU	0x0002
#घोषणा ASCTXFCON_TXFITLMASK	0x3F00
#घोषणा ASCTXFCON_TXFITLOFF	8
#घोषणा ASCRXFCON_RXFEN		0x0001
#घोषणा ASCRXFCON_RXFFLU	0x0002
#घोषणा ASCRXFCON_RXFITLMASK	0x3F00
#घोषणा ASCRXFCON_RXFITLOFF	8
#घोषणा ASCFSTAT_RXFFLMASK	0x003F
#घोषणा ASCFSTAT_TXFFLMASK	0x3F00
#घोषणा ASCFSTAT_TXFREEMASK	0x3F000000
#घोषणा ASCFSTAT_TXFREखातापूर्णF	24

अटल व्योम lqasc_tx_अक्षरs(काष्ठा uart_port *port);
अटल काष्ठा ltq_uart_port *lqasc_port[MAXPORTS];
अटल काष्ठा uart_driver lqasc_reg;

काष्ठा ltq_soc_data अणु
	पूर्णांक	(*fetch_irq)(काष्ठा device *dev, काष्ठा ltq_uart_port *ltq_port);
	पूर्णांक	(*request_irq)(काष्ठा uart_port *port);
	व्योम	(*मुक्त_irq)(काष्ठा uart_port *port);
पूर्ण;

काष्ठा ltq_uart_port अणु
	काष्ठा uart_port	port;
	/* घड़ी used to derive भागider */
	काष्ठा clk		*freqclk;
	/* घड़ी gating of the ASC core */
	काष्ठा clk		*clk;
	अचिन्हित पूर्णांक		tx_irq;
	अचिन्हित पूर्णांक		rx_irq;
	अचिन्हित पूर्णांक		err_irq;
	अचिन्हित पूर्णांक		common_irq;
	spinlock_t		lock; /* exclusive access क्रम multi core */

	स्थिर काष्ठा ltq_soc_data	*soc;
पूर्ण;

अटल अंतरभूत व्योम asc_update_bits(u32 clear, u32 set, व्योम __iomem *reg)
अणु
	u32 पंचांगp = __raw_पढ़ोl(reg);

	__raw_ग_लिखोl((पंचांगp & ~clear) | set, reg);
पूर्ण

अटल अंतरभूत काष्ठा
ltq_uart_port *to_ltq_uart_port(काष्ठा uart_port *port)
अणु
	वापस container_of(port, काष्ठा ltq_uart_port, port);
पूर्ण

अटल व्योम
lqasc_stop_tx(काष्ठा uart_port *port)
अणु
	वापस;
पूर्ण

अटल व्योम
lqasc_start_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ltq_uart_port *ltq_port = to_ltq_uart_port(port);

	spin_lock_irqsave(&ltq_port->lock, flags);
	lqasc_tx_अक्षरs(port);
	spin_unlock_irqrestore(&ltq_port->lock, flags);
	वापस;
पूर्ण

अटल व्योम
lqasc_stop_rx(काष्ठा uart_port *port)
अणु
	__raw_ग_लिखोl(ASCWHBSTATE_CLRREN, port->membase + LTQ_ASC_WHBSTATE);
पूर्ण

अटल पूर्णांक
lqasc_rx_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा tty_port *tport = &port->state->port;
	अचिन्हित पूर्णांक ch = 0, rsr = 0, fअगरocnt;

	fअगरocnt = __raw_पढ़ोl(port->membase + LTQ_ASC_FSTAT) &
		  ASCFSTAT_RXFFLMASK;
	जबतक (fअगरocnt--) अणु
		u8 flag = TTY_NORMAL;
		ch = पढ़ोb(port->membase + LTQ_ASC_RBUF);
		rsr = (__raw_पढ़ोl(port->membase + LTQ_ASC_STATE)
			& ASCSTATE_ANY) | UART_DUMMY_UER_RX;
		tty_flip_buffer_push(tport);
		port->icount.rx++;

		/*
		 * Note that the error handling code is
		 * out of the मुख्य execution path
		 */
		अगर (rsr & ASCSTATE_ANY) अणु
			अगर (rsr & ASCSTATE_PE) अणु
				port->icount.parity++;
				asc_update_bits(0, ASCWHBSTATE_CLRPE,
					port->membase + LTQ_ASC_WHBSTATE);
			पूर्ण अन्यथा अगर (rsr & ASCSTATE_FE) अणु
				port->icount.frame++;
				asc_update_bits(0, ASCWHBSTATE_CLRFE,
					port->membase + LTQ_ASC_WHBSTATE);
			पूर्ण
			अगर (rsr & ASCSTATE_ROE) अणु
				port->icount.overrun++;
				asc_update_bits(0, ASCWHBSTATE_CLRROE,
					port->membase + LTQ_ASC_WHBSTATE);
			पूर्ण

			rsr &= port->पढ़ो_status_mask;

			अगर (rsr & ASCSTATE_PE)
				flag = TTY_PARITY;
			अन्यथा अगर (rsr & ASCSTATE_FE)
				flag = TTY_FRAME;
		पूर्ण

		अगर ((rsr & port->ignore_status_mask) == 0)
			tty_insert_flip_अक्षर(tport, ch, flag);

		अगर (rsr & ASCSTATE_ROE)
			/*
			 * Overrun is special, since it's reported
			 * immediately, and करोesn't affect the current
			 * अक्षरacter
			 */
			tty_insert_flip_अक्षर(tport, 0, TTY_OVERRUN);
	पूर्ण

	अगर (ch != 0)
		tty_flip_buffer_push(tport);

	वापस 0;
पूर्ण

अटल व्योम
lqasc_tx_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अगर (uart_tx_stopped(port)) अणु
		lqasc_stop_tx(port);
		वापस;
	पूर्ण

	जबतक (((__raw_पढ़ोl(port->membase + LTQ_ASC_FSTAT) &
		ASCFSTAT_TXFREEMASK) >> ASCFSTAT_TXFREखातापूर्णF) != 0) अणु
		अगर (port->x_अक्षर) अणु
			ग_लिखोb(port->x_अक्षर, port->membase + LTQ_ASC_TBUF);
			port->icount.tx++;
			port->x_अक्षर = 0;
			जारी;
		पूर्ण

		अगर (uart_circ_empty(xmit))
			अवरोध;

		ग_लिखोb(port->state->xmit.buf[port->state->xmit.tail],
			port->membase + LTQ_ASC_TBUF);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);
पूर्ण

अटल irqवापस_t
lqasc_tx_पूर्णांक(पूर्णांक irq, व्योम *_port)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा uart_port *port = (काष्ठा uart_port *)_port;
	काष्ठा ltq_uart_port *ltq_port = to_ltq_uart_port(port);

	spin_lock_irqsave(&ltq_port->lock, flags);
	__raw_ग_लिखोl(ASC_IRNCR_TIR, port->membase + LTQ_ASC_IRNCR);
	spin_unlock_irqrestore(&ltq_port->lock, flags);
	lqasc_start_tx(port);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
lqasc_err_पूर्णांक(पूर्णांक irq, व्योम *_port)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा uart_port *port = (काष्ठा uart_port *)_port;
	काष्ठा ltq_uart_port *ltq_port = to_ltq_uart_port(port);

	spin_lock_irqsave(&ltq_port->lock, flags);
	/* clear any pending पूर्णांकerrupts */
	asc_update_bits(0, ASCWHBSTATE_CLRPE | ASCWHBSTATE_CLRFE |
		ASCWHBSTATE_CLRROE, port->membase + LTQ_ASC_WHBSTATE);
	spin_unlock_irqrestore(&ltq_port->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
lqasc_rx_पूर्णांक(पूर्णांक irq, व्योम *_port)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा uart_port *port = (काष्ठा uart_port *)_port;
	काष्ठा ltq_uart_port *ltq_port = to_ltq_uart_port(port);

	spin_lock_irqsave(&ltq_port->lock, flags);
	__raw_ग_लिखोl(ASC_IRNCR_RIR, port->membase + LTQ_ASC_IRNCR);
	lqasc_rx_अक्षरs(port);
	spin_unlock_irqrestore(&ltq_port->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t lqasc_irq(पूर्णांक irq, व्योम *p)
अणु
	अचिन्हित दीर्घ flags;
	u32 stat;
	काष्ठा uart_port *port = p;
	काष्ठा ltq_uart_port *ltq_port = to_ltq_uart_port(port);

	spin_lock_irqsave(&ltq_port->lock, flags);
	stat = पढ़ोl(port->membase + LTQ_ASC_IRNCR);
	spin_unlock_irqrestore(&ltq_port->lock, flags);
	अगर (!(stat & ASC_IRNCR_MASK))
		वापस IRQ_NONE;

	अगर (stat & ASC_IRNCR_TIR)
		lqasc_tx_पूर्णांक(irq, p);

	अगर (stat & ASC_IRNCR_RIR)
		lqasc_rx_पूर्णांक(irq, p);

	अगर (stat & ASC_IRNCR_EIR)
		lqasc_err_पूर्णांक(irq, p);

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक
lqasc_tx_empty(काष्ठा uart_port *port)
अणु
	पूर्णांक status;
	status = __raw_पढ़ोl(port->membase + LTQ_ASC_FSTAT) &
		 ASCFSTAT_TXFFLMASK;
	वापस status ? 0 : TIOCSER_TEMT;
पूर्ण

अटल अचिन्हित पूर्णांक
lqasc_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस TIOCM_CTS | TIOCM_CAR | TIOCM_DSR;
पूर्ण

अटल व्योम
lqasc_set_mctrl(काष्ठा uart_port *port, u_पूर्णांक mctrl)
अणु
पूर्ण

अटल व्योम
lqasc_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
पूर्ण

अटल पूर्णांक
lqasc_startup(काष्ठा uart_port *port)
अणु
	काष्ठा ltq_uart_port *ltq_port = to_ltq_uart_port(port);
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	अगर (!IS_ERR(ltq_port->clk))
		clk_prepare_enable(ltq_port->clk);
	port->uartclk = clk_get_rate(ltq_port->freqclk);

	spin_lock_irqsave(&ltq_port->lock, flags);
	asc_update_bits(ASCCLC_DISS | ASCCLC_RMCMASK, (1 << ASCCLC_RMCOFFSET),
		port->membase + LTQ_ASC_CLC);

	__raw_ग_लिखोl(0, port->membase + LTQ_ASC_PISEL);
	__raw_ग_लिखोl(
		((TXFIFO_FL << ASCTXFCON_TXFITLOFF) & ASCTXFCON_TXFITLMASK) |
		ASCTXFCON_TXFEN | ASCTXFCON_TXFFLU,
		port->membase + LTQ_ASC_TXFCON);
	__raw_ग_लिखोl(
		((RXFIFO_FL << ASCRXFCON_RXFITLOFF) & ASCRXFCON_RXFITLMASK)
		| ASCRXFCON_RXFEN | ASCRXFCON_RXFFLU,
		port->membase + LTQ_ASC_RXFCON);
	/* make sure other settings are written to hardware beक्रमe
	 * setting enable bits
	 */
	wmb();
	asc_update_bits(0, ASCCON_M_8ASYNC | ASCCON_FEN | ASCCON_TOEN |
		ASCCON_ROEN, port->membase + LTQ_ASC_CON);

	spin_unlock_irqrestore(&ltq_port->lock, flags);

	retval = ltq_port->soc->request_irq(port);
	अगर (retval)
		वापस retval;

	__raw_ग_लिखोl(ASC_IRNREN_RX | ASC_IRNREN_ERR | ASC_IRNREN_TX,
		port->membase + LTQ_ASC_IRNREN);
	वापस retval;
पूर्ण

अटल व्योम
lqasc_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा ltq_uart_port *ltq_port = to_ltq_uart_port(port);
	अचिन्हित दीर्घ flags;

	ltq_port->soc->मुक्त_irq(port);

	spin_lock_irqsave(&ltq_port->lock, flags);
	__raw_ग_लिखोl(0, port->membase + LTQ_ASC_CON);
	asc_update_bits(ASCRXFCON_RXFEN, ASCRXFCON_RXFFLU,
		port->membase + LTQ_ASC_RXFCON);
	asc_update_bits(ASCTXFCON_TXFEN, ASCTXFCON_TXFFLU,
		port->membase + LTQ_ASC_TXFCON);
	spin_unlock_irqrestore(&ltq_port->lock, flags);
	अगर (!IS_ERR(ltq_port->clk))
		clk_disable_unprepare(ltq_port->clk);
पूर्ण

अटल व्योम
lqasc_set_termios(काष्ठा uart_port *port,
	काष्ठा ktermios *new, काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक cflag;
	अचिन्हित पूर्णांक अगरlag;
	अचिन्हित पूर्णांक भागisor;
	अचिन्हित पूर्णांक baud;
	अचिन्हित पूर्णांक con = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा ltq_uart_port *ltq_port = to_ltq_uart_port(port);

	cflag = new->c_cflag;
	अगरlag = new->c_अगरlag;

	चयन (cflag & CSIZE) अणु
	हाल CS7:
		con = ASCCON_M_7ASYNC;
		अवरोध;

	हाल CS5:
	हाल CS6:
	शेष:
		new->c_cflag &= ~ CSIZE;
		new->c_cflag |= CS8;
		con = ASCCON_M_8ASYNC;
		अवरोध;
	पूर्ण

	cflag &= ~CMSPAR; /* Mark/Space parity is not supported */

	अगर (cflag & CSTOPB)
		con |= ASCCON_STP;

	अगर (cflag & PARENB) अणु
		अगर (!(cflag & PARODD))
			con &= ~ASCCON_ODD;
		अन्यथा
			con |= ASCCON_ODD;
	पूर्ण

	port->पढ़ो_status_mask = ASCSTATE_ROE;
	अगर (अगरlag & INPCK)
		port->पढ़ो_status_mask |= ASCSTATE_FE | ASCSTATE_PE;

	port->ignore_status_mask = 0;
	अगर (अगरlag & IGNPAR)
		port->ignore_status_mask |= ASCSTATE_FE | ASCSTATE_PE;

	अगर (अगरlag & IGNBRK) अणु
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (अगरlag & IGNPAR)
			port->ignore_status_mask |= ASCSTATE_ROE;
	पूर्ण

	अगर ((cflag & CREAD) == 0)
		port->ignore_status_mask |= UART_DUMMY_UER_RX;

	/* set error संकेतs  - framing, parity  and overrun, enable receiver */
	con |= ASCCON_FEN | ASCCON_TOEN | ASCCON_ROEN;

	spin_lock_irqsave(&ltq_port->lock, flags);

	/* set up CON */
	asc_update_bits(0, con, port->membase + LTQ_ASC_CON);

	/* Set baud rate - take a भागider of 2 पूर्णांकo account */
	baud = uart_get_baud_rate(port, new, old, 0, port->uartclk / 16);
	भागisor = uart_get_भागisor(port, baud);
	भागisor = भागisor / 2 - 1;

	/* disable the baudrate generator */
	asc_update_bits(ASCCON_R, 0, port->membase + LTQ_ASC_CON);

	/* make sure the fractional भागider is off */
	asc_update_bits(ASCCON_FDE, 0, port->membase + LTQ_ASC_CON);

	/* set up to use भागisor of 2 */
	asc_update_bits(ASCCON_BRS, 0, port->membase + LTQ_ASC_CON);

	/* now we can ग_लिखो the new baudrate पूर्णांकo the रेजिस्टर */
	__raw_ग_लिखोl(भागisor, port->membase + LTQ_ASC_BG);

	/* turn the baudrate generator back on */
	asc_update_bits(0, ASCCON_R, port->membase + LTQ_ASC_CON);

	/* enable rx */
	__raw_ग_लिखोl(ASCWHBSTATE_SETREN, port->membase + LTQ_ASC_WHBSTATE);

	spin_unlock_irqrestore(&ltq_port->lock, flags);

	/* Don't reग_लिखो B0 */
	अगर (tty_termios_baud_rate(new))
		tty_termios_encode_baud_rate(new, baud, baud);

	uart_update_समयout(port, cflag, baud);
पूर्ण

अटल स्थिर अक्षर*
lqasc_type(काष्ठा uart_port *port)
अणु
	अगर (port->type == PORT_LTQ_ASC)
		वापस DRVNAME;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल व्योम
lqasc_release_port(काष्ठा uart_port *port)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(port->dev);

	अगर (port->flags & UPF_IOREMAP) अणु
		devm_iounmap(&pdev->dev, port->membase);
		port->membase = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक
lqasc_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(port->dev);
	काष्ठा resource *res;
	पूर्णांक size;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "cannot obtain I/O memory region");
		वापस -ENODEV;
	पूर्ण
	size = resource_size(res);

	res = devm_request_mem_region(&pdev->dev, res->start,
		size, dev_name(&pdev->dev));
	अगर (!res) अणु
		dev_err(&pdev->dev, "cannot request I/O memory region");
		वापस -EBUSY;
	पूर्ण

	अगर (port->flags & UPF_IOREMAP) अणु
		port->membase = devm_ioremap(&pdev->dev,
			port->mapbase, size);
		अगर (port->membase == शून्य)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
lqasc_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE) अणु
		port->type = PORT_LTQ_ASC;
		lqasc_request_port(port);
	पूर्ण
पूर्ण

अटल पूर्णांक
lqasc_verअगरy_port(काष्ठा uart_port *port,
	काष्ठा serial_काष्ठा *ser)
अणु
	पूर्णांक ret = 0;
	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_LTQ_ASC)
		ret = -EINVAL;
	अगर (ser->irq < 0 || ser->irq >= NR_IRQS)
		ret = -EINVAL;
	अगर (ser->baud_base < 9600)
		ret = -EINVAL;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा uart_ops lqasc_pops = अणु
	.tx_empty =	lqasc_tx_empty,
	.set_mctrl =	lqasc_set_mctrl,
	.get_mctrl =	lqasc_get_mctrl,
	.stop_tx =	lqasc_stop_tx,
	.start_tx =	lqasc_start_tx,
	.stop_rx =	lqasc_stop_rx,
	.अवरोध_ctl =	lqasc_अवरोध_ctl,
	.startup =	lqasc_startup,
	.shutकरोwn =	lqasc_shutकरोwn,
	.set_termios =	lqasc_set_termios,
	.type =		lqasc_type,
	.release_port =	lqasc_release_port,
	.request_port =	lqasc_request_port,
	.config_port =	lqasc_config_port,
	.verअगरy_port =	lqasc_verअगरy_port,
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_LANTIQ_CONSOLE
अटल व्योम
lqasc_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	पूर्णांक fअगरoमुक्त;

	अगर (!port->membase)
		वापस;

	करो अणु
		fअगरoमुक्त = (__raw_पढ़ोl(port->membase + LTQ_ASC_FSTAT)
			& ASCFSTAT_TXFREEMASK) >> ASCFSTAT_TXFREखातापूर्णF;
	पूर्ण जबतक (fअगरoमुक्त == 0);
	ग_लिखोb(ch, port->membase + LTQ_ASC_TBUF);
पूर्ण

अटल व्योम lqasc_serial_port_ग_लिखो(काष्ठा uart_port *port, स्थिर अक्षर *s,
				    u_पूर्णांक count)
अणु
	uart_console_ग_लिखो(port, s, count, lqasc_console_अक्षर_दो);
पूर्ण

अटल व्योम
lqasc_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, u_पूर्णांक count)
अणु
	काष्ठा ltq_uart_port *ltq_port;
	अचिन्हित दीर्घ flags;

	अगर (co->index >= MAXPORTS)
		वापस;

	ltq_port = lqasc_port[co->index];
	अगर (!ltq_port)
		वापस;

	spin_lock_irqsave(&ltq_port->lock, flags);
	lqasc_serial_port_ग_लिखो(&ltq_port->port, s, count);
	spin_unlock_irqrestore(&ltq_port->lock, flags);
पूर्ण

अटल पूर्णांक __init
lqasc_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा ltq_uart_port *ltq_port;
	काष्ठा uart_port *port;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (co->index >= MAXPORTS)
		वापस -ENODEV;

	ltq_port = lqasc_port[co->index];
	अगर (!ltq_port)
		वापस -ENODEV;

	port = &ltq_port->port;

	अगर (!IS_ERR(ltq_port->clk))
		clk_prepare_enable(ltq_port->clk);

	port->uartclk = clk_get_rate(ltq_port->freqclk);

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा console lqasc_console = अणु
	.name =		"ttyLTQ",
	.ग_लिखो =	lqasc_console_ग_लिखो,
	.device =	uart_console_device,
	.setup =	lqasc_console_setup,
	.flags =	CON_PRINTBUFFER,
	.index =	-1,
	.data =		&lqasc_reg,
पूर्ण;

अटल पूर्णांक __init
lqasc_console_init(व्योम)
अणु
	रेजिस्टर_console(&lqasc_console);
	वापस 0;
पूर्ण
console_initcall(lqasc_console_init);

अटल व्योम lqasc_serial_early_console_ग_लिखो(काष्ठा console *co,
					     स्थिर अक्षर *s,
					     u_पूर्णांक count)
अणु
	काष्ठा earlycon_device *dev = co->data;

	lqasc_serial_port_ग_लिखो(&dev->port, s, count);
पूर्ण

अटल पूर्णांक __init
lqasc_serial_early_console_setup(काष्ठा earlycon_device *device,
				 स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->con->ग_लिखो = lqasc_serial_early_console_ग_लिखो;
	वापस 0;
पूर्ण
OF_EARLYCON_DECLARE(lantiq, "lantiq,asc", lqasc_serial_early_console_setup);
OF_EARLYCON_DECLARE(lantiq, "intel,lgm-asc", lqasc_serial_early_console_setup);

#घोषणा LANTIQ_SERIAL_CONSOLE	(&lqasc_console)

#अन्यथा

#घोषणा LANTIQ_SERIAL_CONSOLE	शून्य

#पूर्ण_अगर /* CONFIG_SERIAL_LANTIQ_CONSOLE */

अटल काष्ठा uart_driver lqasc_reg = अणु
	.owner =	THIS_MODULE,
	.driver_name =	DRVNAME,
	.dev_name =	"ttyLTQ",
	.major =	0,
	.minor =	0,
	.nr =		MAXPORTS,
	.cons =		LANTIQ_SERIAL_CONSOLE,
पूर्ण;

अटल पूर्णांक fetch_irq_lantiq(काष्ठा device *dev, काष्ठा ltq_uart_port *ltq_port)
अणु
	काष्ठा uart_port *port = &ltq_port->port;
	काष्ठा resource irqres[3];
	पूर्णांक ret;

	ret = of_irq_to_resource_table(dev->of_node, irqres, 3);
	अगर (ret != 3) अणु
		dev_err(dev,
			"failed to get IRQs for serial port\n");
		वापस -ENODEV;
	पूर्ण
	ltq_port->tx_irq = irqres[0].start;
	ltq_port->rx_irq = irqres[1].start;
	ltq_port->err_irq = irqres[2].start;
	port->irq = irqres[0].start;

	वापस 0;
पूर्ण

अटल पूर्णांक request_irq_lantiq(काष्ठा uart_port *port)
अणु
	काष्ठा ltq_uart_port *ltq_port = to_ltq_uart_port(port);
	पूर्णांक retval;

	retval = request_irq(ltq_port->tx_irq, lqasc_tx_पूर्णांक,
			     0, "asc_tx", port);
	अगर (retval) अणु
		dev_err(port->dev, "failed to request asc_tx\n");
		वापस retval;
	पूर्ण

	retval = request_irq(ltq_port->rx_irq, lqasc_rx_पूर्णांक,
			     0, "asc_rx", port);
	अगर (retval) अणु
		dev_err(port->dev, "failed to request asc_rx\n");
		जाओ err1;
	पूर्ण

	retval = request_irq(ltq_port->err_irq, lqasc_err_पूर्णांक,
			     0, "asc_err", port);
	अगर (retval) अणु
		dev_err(port->dev, "failed to request asc_err\n");
		जाओ err2;
	पूर्ण
	वापस 0;

err2:
	मुक्त_irq(ltq_port->rx_irq, port);
err1:
	मुक्त_irq(ltq_port->tx_irq, port);
	वापस retval;
पूर्ण

अटल व्योम मुक्त_irq_lantiq(काष्ठा uart_port *port)
अणु
	काष्ठा ltq_uart_port *ltq_port = to_ltq_uart_port(port);

	मुक्त_irq(ltq_port->tx_irq, port);
	मुक्त_irq(ltq_port->rx_irq, port);
	मुक्त_irq(ltq_port->err_irq, port);
पूर्ण

अटल पूर्णांक fetch_irq_पूर्णांकel(काष्ठा device *dev, काष्ठा ltq_uart_port *ltq_port)
अणु
	काष्ठा uart_port *port = &ltq_port->port;
	पूर्णांक ret;

	ret = of_irq_get(dev->of_node, 0);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to fetch IRQ for serial port\n");
		वापस ret;
	पूर्ण
	ltq_port->common_irq = ret;
	port->irq = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक request_irq_पूर्णांकel(काष्ठा uart_port *port)
अणु
	काष्ठा ltq_uart_port *ltq_port = to_ltq_uart_port(port);
	पूर्णांक retval;

	retval = request_irq(ltq_port->common_irq, lqasc_irq, 0,
			     "asc_irq", port);
	अगर (retval)
		dev_err(port->dev, "failed to request asc_irq\n");

	वापस retval;
पूर्ण

अटल व्योम मुक्त_irq_पूर्णांकel(काष्ठा uart_port *port)
अणु
	काष्ठा ltq_uart_port *ltq_port = to_ltq_uart_port(port);

	मुक्त_irq(ltq_port->common_irq, port);
पूर्ण

अटल पूर्णांक lqasc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा ltq_uart_port *ltq_port;
	काष्ठा uart_port *port;
	काष्ठा resource *mmres;
	पूर्णांक line;
	पूर्णांक ret;

	mmres = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!mmres) अणु
		dev_err(&pdev->dev,
			"failed to get memory for serial port\n");
		वापस -ENODEV;
	पूर्ण

	ltq_port = devm_kzalloc(&pdev->dev, माप(काष्ठा ltq_uart_port),
				GFP_KERNEL);
	अगर (!ltq_port)
		वापस -ENOMEM;

	port = &ltq_port->port;

	ltq_port->soc = of_device_get_match_data(&pdev->dev);
	ret = ltq_port->soc->fetch_irq(&pdev->dev, ltq_port);
	अगर (ret)
		वापस ret;

	/* get serial id */
	line = of_alias_get_id(node, "serial");
	अगर (line < 0) अणु
		अगर (IS_ENABLED(CONFIG_LANTIQ)) अणु
			अगर (mmres->start == CPHYSADDR(LTQ_EARLY_ASC))
				line = 0;
			अन्यथा
				line = 1;
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "failed to get alias id, errno %d\n",
				line);
			वापस line;
		पूर्ण
	पूर्ण

	अगर (lqasc_port[line]) अणु
		dev_err(&pdev->dev, "port %d already allocated\n", line);
		वापस -EBUSY;
	पूर्ण

	port->iotype	= SERIAL_IO_MEM;
	port->flags	= UPF_BOOT_AUTOCONF | UPF_IOREMAP;
	port->ops	= &lqasc_pops;
	port->fअगरosize	= 16;
	port->type	= PORT_LTQ_ASC;
	port->line	= line;
	port->dev	= &pdev->dev;
	/* unused, just to be backward-compatible */
	port->mapbase	= mmres->start;

	अगर (IS_ENABLED(CONFIG_LANTIQ) && !IS_ENABLED(CONFIG_COMMON_CLK))
		ltq_port->freqclk = clk_get_fpi();
	अन्यथा
		ltq_port->freqclk = devm_clk_get(&pdev->dev, "freq");


	अगर (IS_ERR(ltq_port->freqclk)) अणु
		pr_err("failed to get fpi clk\n");
		वापस -ENOENT;
	पूर्ण

	/* not all asc ports have घड़ी gates, lets ignore the वापस code */
	अगर (IS_ENABLED(CONFIG_LANTIQ) && !IS_ENABLED(CONFIG_COMMON_CLK))
		ltq_port->clk = clk_get(&pdev->dev, शून्य);
	अन्यथा
		ltq_port->clk = devm_clk_get(&pdev->dev, "asc");

	spin_lock_init(&ltq_port->lock);
	lqasc_port[line] = ltq_port;
	platक्रमm_set_drvdata(pdev, ltq_port);

	ret = uart_add_one_port(&lqasc_reg, port);

	वापस ret;
पूर्ण

अटल पूर्णांक lqasc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port = platक्रमm_get_drvdata(pdev);

	वापस uart_हटाओ_one_port(&lqasc_reg, port);
पूर्ण

अटल स्थिर काष्ठा ltq_soc_data soc_data_lantiq = अणु
	.fetch_irq = fetch_irq_lantiq,
	.request_irq = request_irq_lantiq,
	.मुक्त_irq = मुक्त_irq_lantiq,
पूर्ण;

अटल स्थिर काष्ठा ltq_soc_data soc_data_पूर्णांकel = अणु
	.fetch_irq = fetch_irq_पूर्णांकel,
	.request_irq = request_irq_पूर्णांकel,
	.मुक्त_irq = मुक्त_irq_पूर्णांकel,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ltq_asc_match[] = अणु
	अणु .compatible = "lantiq,asc", .data = &soc_data_lantiq पूर्ण,
	अणु .compatible = "intel,lgm-asc", .data = &soc_data_पूर्णांकel पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ltq_asc_match);

अटल काष्ठा platक्रमm_driver lqasc_driver = अणु
	.probe		= lqasc_probe,
	.हटाओ		= lqasc_हटाओ,
	.driver		= अणु
		.name	= DRVNAME,
		.of_match_table = ltq_asc_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init
init_lqasc(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&lqasc_reg);
	अगर (ret != 0)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&lqasc_driver);
	अगर (ret != 0)
		uart_unरेजिस्टर_driver(&lqasc_reg);

	वापस ret;
पूर्ण

अटल व्योम __निकास निकास_lqasc(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&lqasc_driver);
	uart_unरेजिस्टर_driver(&lqasc_reg);
पूर्ण

module_init(init_lqasc);
module_निकास(निकास_lqasc);

MODULE_DESCRIPTION("Serial driver for Lantiq & Intel gateway SoCs");
MODULE_LICENSE("GPL v2");
