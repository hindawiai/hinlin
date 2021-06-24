<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Driver क्रम AMBA serial ports
 *
 *  Based on drivers/अक्षर/serial.c, by Linus Torvalds, Theoकरोre Ts'o.
 *
 *  Copyright 1999 ARM Limited
 *  Copyright (C) 2000 Deep Blue Solutions Ltd.
 *
 * This is a generic driver क्रम ARM AMBA-type serial ports.  They
 * have a lot of 16550-like features, but are not रेजिस्टर compatible.
 * Note that although they करो have CTS, DCD and DSR inमाला_दो, they करो
 * not have an RI input, nor करो they have DTR or RTS outमाला_दो.  If
 * required, these have to be supplied via some other means (eg, GPIO)
 * and hooked पूर्णांकo this driver.
 */

#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/device.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/amba/serial.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#घोषणा UART_NR		8

#घोषणा SERIAL_AMBA_MAJOR	204
#घोषणा SERIAL_AMBA_MINOR	16
#घोषणा SERIAL_AMBA_NR		UART_NR

#घोषणा AMBA_ISR_PASS_LIMIT	256

#घोषणा UART_RX_DATA(s)		(((s) & UART01x_FR_RXFE) == 0)
#घोषणा UART_TX_READY(s)	(((s) & UART01x_FR_TXFF) == 0)

#घोषणा UART_DUMMY_RSR_RX	256
#घोषणा UART_PORT_SIZE		64

/*
 * We wrap our port काष्ठाure around the generic uart_port.
 */
काष्ठा uart_amba_port अणु
	काष्ठा uart_port	port;
	काष्ठा clk		*clk;
	काष्ठा amba_device	*dev;
	काष्ठा amba_pl010_data	*data;
	अचिन्हित पूर्णांक		old_status;
पूर्ण;

अटल व्योम pl010_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
		container_of(port, काष्ठा uart_amba_port, port);
	अचिन्हित पूर्णांक cr;

	cr = पढ़ोb(uap->port.membase + UART010_CR);
	cr &= ~UART010_CR_TIE;
	ग_लिखोl(cr, uap->port.membase + UART010_CR);
पूर्ण

अटल व्योम pl010_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
		container_of(port, काष्ठा uart_amba_port, port);
	अचिन्हित पूर्णांक cr;

	cr = पढ़ोb(uap->port.membase + UART010_CR);
	cr |= UART010_CR_TIE;
	ग_लिखोl(cr, uap->port.membase + UART010_CR);
पूर्ण

अटल व्योम pl010_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
		container_of(port, काष्ठा uart_amba_port, port);
	अचिन्हित पूर्णांक cr;

	cr = पढ़ोb(uap->port.membase + UART010_CR);
	cr &= ~(UART010_CR_RIE | UART010_CR_RTIE);
	ग_लिखोl(cr, uap->port.membase + UART010_CR);
पूर्ण

अटल व्योम pl010_disable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap = (काष्ठा uart_amba_port *)port;
	अचिन्हित पूर्णांक cr;

	cr = पढ़ोb(uap->port.membase + UART010_CR);
	cr &= ~UART010_CR_MSIE;
	ग_लिखोl(cr, uap->port.membase + UART010_CR);
पूर्ण

अटल व्योम pl010_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
		container_of(port, काष्ठा uart_amba_port, port);
	अचिन्हित पूर्णांक cr;

	cr = पढ़ोb(uap->port.membase + UART010_CR);
	cr |= UART010_CR_MSIE;
	ग_लिखोl(cr, uap->port.membase + UART010_CR);
पूर्ण

अटल व्योम pl010_rx_अक्षरs(काष्ठा uart_amba_port *uap)
अणु
	अचिन्हित पूर्णांक status, ch, flag, rsr, max_count = 256;

	status = पढ़ोb(uap->port.membase + UART01x_FR);
	जबतक (UART_RX_DATA(status) && max_count--) अणु
		ch = पढ़ोb(uap->port.membase + UART01x_DR);
		flag = TTY_NORMAL;

		uap->port.icount.rx++;

		/*
		 * Note that the error handling code is
		 * out of the मुख्य execution path
		 */
		rsr = पढ़ोb(uap->port.membase + UART01x_RSR) | UART_DUMMY_RSR_RX;
		अगर (unlikely(rsr & UART01x_RSR_ANY)) अणु
			ग_लिखोl(0, uap->port.membase + UART01x_ECR);

			अगर (rsr & UART01x_RSR_BE) अणु
				rsr &= ~(UART01x_RSR_FE | UART01x_RSR_PE);
				uap->port.icount.brk++;
				अगर (uart_handle_अवरोध(&uap->port))
					जाओ ignore_अक्षर;
			पूर्ण अन्यथा अगर (rsr & UART01x_RSR_PE)
				uap->port.icount.parity++;
			अन्यथा अगर (rsr & UART01x_RSR_FE)
				uap->port.icount.frame++;
			अगर (rsr & UART01x_RSR_OE)
				uap->port.icount.overrun++;

			rsr &= uap->port.पढ़ो_status_mask;

			अगर (rsr & UART01x_RSR_BE)
				flag = TTY_BREAK;
			अन्यथा अगर (rsr & UART01x_RSR_PE)
				flag = TTY_PARITY;
			अन्यथा अगर (rsr & UART01x_RSR_FE)
				flag = TTY_FRAME;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(&uap->port, ch))
			जाओ ignore_अक्षर;

		uart_insert_अक्षर(&uap->port, rsr, UART01x_RSR_OE, ch, flag);

	ignore_अक्षर:
		status = पढ़ोb(uap->port.membase + UART01x_FR);
	पूर्ण
	tty_flip_buffer_push(&uap->port.state->port);
पूर्ण

अटल व्योम pl010_tx_अक्षरs(काष्ठा uart_amba_port *uap)
अणु
	काष्ठा circ_buf *xmit = &uap->port.state->xmit;
	पूर्णांक count;

	अगर (uap->port.x_अक्षर) अणु
		ग_लिखोl(uap->port.x_अक्षर, uap->port.membase + UART01x_DR);
		uap->port.icount.tx++;
		uap->port.x_अक्षर = 0;
		वापस;
	पूर्ण
	अगर (uart_circ_empty(xmit) || uart_tx_stopped(&uap->port)) अणु
		pl010_stop_tx(&uap->port);
		वापस;
	पूर्ण

	count = uap->port.fअगरosize >> 1;
	करो अणु
		ग_लिखोl(xmit->buf[xmit->tail], uap->port.membase + UART01x_DR);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		uap->port.icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण जबतक (--count > 0);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&uap->port);

	अगर (uart_circ_empty(xmit))
		pl010_stop_tx(&uap->port);
पूर्ण

अटल व्योम pl010_modem_status(काष्ठा uart_amba_port *uap)
अणु
	अचिन्हित पूर्णांक status, delta;

	ग_लिखोl(0, uap->port.membase + UART010_ICR);

	status = पढ़ोb(uap->port.membase + UART01x_FR) & UART01x_FR_MODEM_ANY;

	delta = status ^ uap->old_status;
	uap->old_status = status;

	अगर (!delta)
		वापस;

	अगर (delta & UART01x_FR_DCD)
		uart_handle_dcd_change(&uap->port, status & UART01x_FR_DCD);

	अगर (delta & UART01x_FR_DSR)
		uap->port.icount.dsr++;

	अगर (delta & UART01x_FR_CTS)
		uart_handle_cts_change(&uap->port, status & UART01x_FR_CTS);

	wake_up_पूर्णांकerruptible(&uap->port.state->port.delta_msr_रुको);
पूर्ण

अटल irqवापस_t pl010_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_amba_port *uap = dev_id;
	अचिन्हित पूर्णांक status, pass_counter = AMBA_ISR_PASS_LIMIT;
	पूर्णांक handled = 0;

	spin_lock(&uap->port.lock);

	status = पढ़ोb(uap->port.membase + UART010_IIR);
	अगर (status) अणु
		करो अणु
			अगर (status & (UART010_IIR_RTIS | UART010_IIR_RIS))
				pl010_rx_अक्षरs(uap);
			अगर (status & UART010_IIR_MIS)
				pl010_modem_status(uap);
			अगर (status & UART010_IIR_TIS)
				pl010_tx_अक्षरs(uap);

			अगर (pass_counter-- == 0)
				अवरोध;

			status = पढ़ोb(uap->port.membase + UART010_IIR);
		पूर्ण जबतक (status & (UART010_IIR_RTIS | UART010_IIR_RIS |
				   UART010_IIR_TIS));
		handled = 1;
	पूर्ण

	spin_unlock(&uap->port.lock);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल अचिन्हित पूर्णांक pl010_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
		container_of(port, काष्ठा uart_amba_port, port);
	अचिन्हित पूर्णांक status = पढ़ोb(uap->port.membase + UART01x_FR);
	वापस status & UART01x_FR_BUSY ? 0 : TIOCSER_TEMT;
पूर्ण

अटल अचिन्हित पूर्णांक pl010_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
		container_of(port, काष्ठा uart_amba_port, port);
	अचिन्हित पूर्णांक result = 0;
	अचिन्हित पूर्णांक status;

	status = पढ़ोb(uap->port.membase + UART01x_FR);
	अगर (status & UART01x_FR_DCD)
		result |= TIOCM_CAR;
	अगर (status & UART01x_FR_DSR)
		result |= TIOCM_DSR;
	अगर (status & UART01x_FR_CTS)
		result |= TIOCM_CTS;

	वापस result;
पूर्ण

अटल व्योम pl010_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा uart_amba_port *uap =
		container_of(port, काष्ठा uart_amba_port, port);

	अगर (uap->data)
		uap->data->set_mctrl(uap->dev, uap->port.membase, mctrl);
पूर्ण

अटल व्योम pl010_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा uart_amba_port *uap =
		container_of(port, काष्ठा uart_amba_port, port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक lcr_h;

	spin_lock_irqsave(&uap->port.lock, flags);
	lcr_h = पढ़ोb(uap->port.membase + UART010_LCRH);
	अगर (अवरोध_state == -1)
		lcr_h |= UART01x_LCRH_BRK;
	अन्यथा
		lcr_h &= ~UART01x_LCRH_BRK;
	ग_लिखोl(lcr_h, uap->port.membase + UART010_LCRH);
	spin_unlock_irqrestore(&uap->port.lock, flags);
पूर्ण

अटल पूर्णांक pl010_startup(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
		container_of(port, काष्ठा uart_amba_port, port);
	पूर्णांक retval;

	/*
	 * Try to enable the घड़ी producer.
	 */
	retval = clk_prepare_enable(uap->clk);
	अगर (retval)
		जाओ out;

	uap->port.uartclk = clk_get_rate(uap->clk);

	/*
	 * Allocate the IRQ
	 */
	retval = request_irq(uap->port.irq, pl010_पूर्णांक, 0, "uart-pl010", uap);
	अगर (retval)
		जाओ clk_dis;

	/*
	 * initialise the old status of the modem संकेतs
	 */
	uap->old_status = पढ़ोb(uap->port.membase + UART01x_FR) & UART01x_FR_MODEM_ANY;

	/*
	 * Finally, enable पूर्णांकerrupts
	 */
	ग_लिखोl(UART01x_CR_UARTEN | UART010_CR_RIE | UART010_CR_RTIE,
	       uap->port.membase + UART010_CR);

	वापस 0;

 clk_dis:
	clk_disable_unprepare(uap->clk);
 out:
	वापस retval;
पूर्ण

अटल व्योम pl010_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
		container_of(port, काष्ठा uart_amba_port, port);

	/*
	 * Free the पूर्णांकerrupt
	 */
	मुक्त_irq(uap->port.irq, uap);

	/*
	 * disable all पूर्णांकerrupts, disable the port
	 */
	ग_लिखोl(0, uap->port.membase + UART010_CR);

	/* disable अवरोध condition and fअगरos */
	ग_लिखोl(पढ़ोb(uap->port.membase + UART010_LCRH) &
		~(UART01x_LCRH_BRK | UART01x_LCRH_FEN),
	       uap->port.membase + UART010_LCRH);

	/*
	 * Shut करोwn the घड़ी producer
	 */
	clk_disable_unprepare(uap->clk);
पूर्ण

अटल व्योम
pl010_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		     काष्ठा ktermios *old)
अणु
	काष्ठा uart_amba_port *uap =
		container_of(port, काष्ठा uart_amba_port, port);
	अचिन्हित पूर्णांक lcr_h, old_cr;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, quot;

	/*
	 * Ask the core to calculate the भागisor क्रम us.
	 */
	baud = uart_get_baud_rate(port, termios, old, 0, uap->port.uartclk/16); 
	quot = uart_get_भागisor(port, baud);

	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		lcr_h = UART01x_LCRH_WLEN_5;
		अवरोध;
	हाल CS6:
		lcr_h = UART01x_LCRH_WLEN_6;
		अवरोध;
	हाल CS7:
		lcr_h = UART01x_LCRH_WLEN_7;
		अवरोध;
	शेष: // CS8
		lcr_h = UART01x_LCRH_WLEN_8;
		अवरोध;
	पूर्ण
	अगर (termios->c_cflag & CSTOPB)
		lcr_h |= UART01x_LCRH_STP2;
	अगर (termios->c_cflag & PARENB) अणु
		lcr_h |= UART01x_LCRH_PEN;
		अगर (!(termios->c_cflag & PARODD))
			lcr_h |= UART01x_LCRH_EPS;
	पूर्ण
	अगर (uap->port.fअगरosize > 1)
		lcr_h |= UART01x_LCRH_FEN;

	spin_lock_irqsave(&uap->port.lock, flags);

	/*
	 * Update the per-port समयout.
	 */
	uart_update_समयout(port, termios->c_cflag, baud);

	uap->port.पढ़ो_status_mask = UART01x_RSR_OE;
	अगर (termios->c_अगरlag & INPCK)
		uap->port.पढ़ो_status_mask |= UART01x_RSR_FE | UART01x_RSR_PE;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		uap->port.पढ़ो_status_mask |= UART01x_RSR_BE;

	/*
	 * Characters to ignore
	 */
	uap->port.ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		uap->port.ignore_status_mask |= UART01x_RSR_FE | UART01x_RSR_PE;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		uap->port.ignore_status_mask |= UART01x_RSR_BE;
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			uap->port.ignore_status_mask |= UART01x_RSR_OE;
	पूर्ण

	/*
	 * Ignore all अक्षरacters अगर CREAD is not set.
	 */
	अगर ((termios->c_cflag & CREAD) == 0)
		uap->port.ignore_status_mask |= UART_DUMMY_RSR_RX;

	/* first, disable everything */
	old_cr = पढ़ोb(uap->port.membase + UART010_CR) & ~UART010_CR_MSIE;

	अगर (UART_ENABLE_MS(port, termios->c_cflag))
		old_cr |= UART010_CR_MSIE;

	ग_लिखोl(0, uap->port.membase + UART010_CR);

	/* Set baud rate */
	quot -= 1;
	ग_लिखोl((quot & 0xf00) >> 8, uap->port.membase + UART010_LCRM);
	ग_लिखोl(quot & 0xff, uap->port.membase + UART010_LCRL);

	/*
	 * ----------v----------v----------v----------v-----
	 * NOTE: MUST BE WRITTEN AFTER UARTLCR_M & UARTLCR_L
	 * ----------^----------^----------^----------^-----
	 */
	ग_लिखोl(lcr_h, uap->port.membase + UART010_LCRH);
	ग_लिखोl(old_cr, uap->port.membase + UART010_CR);

	spin_unlock_irqrestore(&uap->port.lock, flags);
पूर्ण

अटल व्योम pl010_set_ldisc(काष्ठा uart_port *port, काष्ठा ktermios *termios)
अणु
	अगर (termios->c_line == N_PPS) अणु
		port->flags |= UPF_HARDPPS_CD;
		spin_lock_irq(&port->lock);
		pl010_enable_ms(port);
		spin_unlock_irq(&port->lock);
	पूर्ण अन्यथा अणु
		port->flags &= ~UPF_HARDPPS_CD;
		अगर (!UART_ENABLE_MS(port, termios->c_cflag)) अणु
			spin_lock_irq(&port->lock);
			pl010_disable_ms(port);
			spin_unlock_irq(&port->lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *pl010_type(काष्ठा uart_port *port)
अणु
	वापस port->type == PORT_AMBA ? "AMBA" : शून्य;
पूर्ण

/*
 * Release the memory region(s) being used by 'port'
 */
अटल व्योम pl010_release_port(काष्ठा uart_port *port)
अणु
	release_mem_region(port->mapbase, UART_PORT_SIZE);
पूर्ण

/*
 * Request the memory region(s) being used by 'port'
 */
अटल पूर्णांक pl010_request_port(काष्ठा uart_port *port)
अणु
	वापस request_mem_region(port->mapbase, UART_PORT_SIZE, "uart-pl010")
			!= शून्य ? 0 : -EBUSY;
पूर्ण

/*
 * Configure/स्वतःconfigure the port.
 */
अटल व्योम pl010_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE) अणु
		port->type = PORT_AMBA;
		pl010_request_port(port);
	पूर्ण
पूर्ण

/*
 * verअगरy the new serial_काष्ठा (क्रम TIOCSSERIAL).
 */
अटल पूर्णांक pl010_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	पूर्णांक ret = 0;
	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_AMBA)
		ret = -EINVAL;
	अगर (ser->irq < 0 || ser->irq >= nr_irqs)
		ret = -EINVAL;
	अगर (ser->baud_base < 9600)
		ret = -EINVAL;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा uart_ops amba_pl010_pops = अणु
	.tx_empty	= pl010_tx_empty,
	.set_mctrl	= pl010_set_mctrl,
	.get_mctrl	= pl010_get_mctrl,
	.stop_tx	= pl010_stop_tx,
	.start_tx	= pl010_start_tx,
	.stop_rx	= pl010_stop_rx,
	.enable_ms	= pl010_enable_ms,
	.अवरोध_ctl	= pl010_अवरोध_ctl,
	.startup	= pl010_startup,
	.shutकरोwn	= pl010_shutकरोwn,
	.set_termios	= pl010_set_termios,
	.set_ldisc	= pl010_set_ldisc,
	.type		= pl010_type,
	.release_port	= pl010_release_port,
	.request_port	= pl010_request_port,
	.config_port	= pl010_config_port,
	.verअगरy_port	= pl010_verअगरy_port,
पूर्ण;

अटल काष्ठा uart_amba_port *amba_ports[UART_NR];

#अगर_घोषित CONFIG_SERIAL_AMBA_PL010_CONSOLE

अटल व्योम pl010_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा uart_amba_port *uap =
		container_of(port, काष्ठा uart_amba_port, port);
	अचिन्हित पूर्णांक status;

	करो अणु
		status = पढ़ोb(uap->port.membase + UART01x_FR);
		barrier();
	पूर्ण जबतक (!UART_TX_READY(status));
	ग_लिखोl(ch, uap->port.membase + UART01x_DR);
पूर्ण

अटल व्योम
pl010_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_amba_port *uap = amba_ports[co->index];
	अचिन्हित पूर्णांक status, old_cr;

	clk_enable(uap->clk);

	/*
	 *	First save the CR then disable the पूर्णांकerrupts
	 */
	old_cr = पढ़ोb(uap->port.membase + UART010_CR);
	ग_लिखोl(UART01x_CR_UARTEN, uap->port.membase + UART010_CR);

	uart_console_ग_लिखो(&uap->port, s, count, pl010_console_अक्षर_दो);

	/*
	 *	Finally, रुको क्रम transmitter to become empty
	 *	and restore the TCR
	 */
	करो अणु
		status = पढ़ोb(uap->port.membase + UART01x_FR);
		barrier();
	पूर्ण जबतक (status & UART01x_FR_BUSY);
	ग_लिखोl(old_cr, uap->port.membase + UART010_CR);

	clk_disable(uap->clk);
पूर्ण

अटल व्योम __init
pl010_console_get_options(काष्ठा uart_amba_port *uap, पूर्णांक *baud,
			     पूर्णांक *parity, पूर्णांक *bits)
अणु
	अगर (पढ़ोb(uap->port.membase + UART010_CR) & UART01x_CR_UARTEN) अणु
		अचिन्हित पूर्णांक lcr_h, quot;
		lcr_h = पढ़ोb(uap->port.membase + UART010_LCRH);

		*parity = 'n';
		अगर (lcr_h & UART01x_LCRH_PEN) अणु
			अगर (lcr_h & UART01x_LCRH_EPS)
				*parity = 'e';
			अन्यथा
				*parity = 'o';
		पूर्ण

		अगर ((lcr_h & 0x60) == UART01x_LCRH_WLEN_7)
			*bits = 7;
		अन्यथा
			*bits = 8;

		quot = पढ़ोb(uap->port.membase + UART010_LCRL) |
		       पढ़ोb(uap->port.membase + UART010_LCRM) << 8;
		*baud = uap->port.uartclk / (16 * (quot + 1));
	पूर्ण
पूर्ण

अटल पूर्णांक __init pl010_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_amba_port *uap;
	पूर्णांक baud = 38400;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	पूर्णांक ret;

	/*
	 * Check whether an invalid uart number has been specअगरied, and
	 * अगर so, search क्रम the first available port that करोes have
	 * console support.
	 */
	अगर (co->index >= UART_NR)
		co->index = 0;
	uap = amba_ports[co->index];
	अगर (!uap)
		वापस -ENODEV;

	ret = clk_prepare(uap->clk);
	अगर (ret)
		वापस ret;

	uap->port.uartclk = clk_get_rate(uap->clk);

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	अन्यथा
		pl010_console_get_options(uap, &baud, &parity, &bits);

	वापस uart_set_options(&uap->port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver amba_reg;
अटल काष्ठा console amba_console = अणु
	.name		= "ttyAM",
	.ग_लिखो		= pl010_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= pl010_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &amba_reg,
पूर्ण;

#घोषणा AMBA_CONSOLE	&amba_console
#अन्यथा
#घोषणा AMBA_CONSOLE	शून्य
#पूर्ण_अगर

अटल DEFINE_MUTEX(amba_reg_lock);
अटल काष्ठा uart_driver amba_reg = अणु
	.owner			= THIS_MODULE,
	.driver_name		= "ttyAM",
	.dev_name		= "ttyAM",
	.major			= SERIAL_AMBA_MAJOR,
	.minor			= SERIAL_AMBA_MINOR,
	.nr			= UART_NR,
	.cons			= AMBA_CONSOLE,
पूर्ण;

अटल पूर्णांक pl010_probe(काष्ठा amba_device *dev, स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा uart_amba_port *uap;
	व्योम __iomem *base;
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(amba_ports); i++)
		अगर (amba_ports[i] == शून्य)
			अवरोध;

	अगर (i == ARRAY_SIZE(amba_ports))
		वापस -EBUSY;

	uap = devm_kzalloc(&dev->dev, माप(काष्ठा uart_amba_port),
			   GFP_KERNEL);
	अगर (!uap)
		वापस -ENOMEM;

	base = devm_ioremap(&dev->dev, dev->res.start,
			    resource_size(&dev->res));
	अगर (!base)
		वापस -ENOMEM;

	uap->clk = devm_clk_get(&dev->dev, शून्य);
	अगर (IS_ERR(uap->clk))
		वापस PTR_ERR(uap->clk);

	uap->port.dev = &dev->dev;
	uap->port.mapbase = dev->res.start;
	uap->port.membase = base;
	uap->port.iotype = UPIO_MEM;
	uap->port.irq = dev->irq[0];
	uap->port.fअगरosize = 16;
	uap->port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_AMBA_PL010_CONSOLE);
	uap->port.ops = &amba_pl010_pops;
	uap->port.flags = UPF_BOOT_AUTOCONF;
	uap->port.line = i;
	uap->dev = dev;
	uap->data = dev_get_platdata(&dev->dev);

	amba_ports[i] = uap;

	amba_set_drvdata(dev, uap);

	mutex_lock(&amba_reg_lock);
	अगर (!amba_reg.state) अणु
		ret = uart_रेजिस्टर_driver(&amba_reg);
		अगर (ret < 0) अणु
			mutex_unlock(&amba_reg_lock);
			dev_err(uap->port.dev,
				"Failed to register AMBA-PL010 driver\n");
			वापस ret;
		पूर्ण
	पूर्ण
	mutex_unlock(&amba_reg_lock);

	ret = uart_add_one_port(&amba_reg, &uap->port);
	अगर (ret)
		amba_ports[i] = शून्य;

	वापस ret;
पूर्ण

अटल व्योम pl010_हटाओ(काष्ठा amba_device *dev)
अणु
	काष्ठा uart_amba_port *uap = amba_get_drvdata(dev);
	पूर्णांक i;
	bool busy = false;

	uart_हटाओ_one_port(&amba_reg, &uap->port);

	क्रम (i = 0; i < ARRAY_SIZE(amba_ports); i++)
		अगर (amba_ports[i] == uap)
			amba_ports[i] = शून्य;
		अन्यथा अगर (amba_ports[i])
			busy = true;

	अगर (!busy)
		uart_unरेजिस्टर_driver(&amba_reg);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pl010_suspend(काष्ठा device *dev)
अणु
	काष्ठा uart_amba_port *uap = dev_get_drvdata(dev);

	अगर (uap)
		uart_suspend_port(&amba_reg, &uap->port);

	वापस 0;
पूर्ण

अटल पूर्णांक pl010_resume(काष्ठा device *dev)
अणु
	काष्ठा uart_amba_port *uap = dev_get_drvdata(dev);

	अगर (uap)
		uart_resume_port(&amba_reg, &uap->port);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(pl010_dev_pm_ops, pl010_suspend, pl010_resume);

अटल स्थिर काष्ठा amba_id pl010_ids[] = अणु
	अणु
		.id	= 0x00041010,
		.mask	= 0x000fffff,
	पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, pl010_ids);

अटल काष्ठा amba_driver pl010_driver = अणु
	.drv = अणु
		.name	= "uart-pl010",
		.pm	= &pl010_dev_pm_ops,
	पूर्ण,
	.id_table	= pl010_ids,
	.probe		= pl010_probe,
	.हटाओ		= pl010_हटाओ,
पूर्ण;

अटल पूर्णांक __init pl010_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "Serial: AMBA driver\n");

	वापस  amba_driver_रेजिस्टर(&pl010_driver);
पूर्ण

अटल व्योम __निकास pl010_निकास(व्योम)
अणु
	amba_driver_unरेजिस्टर(&pl010_driver);
पूर्ण

module_init(pl010_init);
module_निकास(pl010_निकास);

MODULE_AUTHOR("ARM Ltd/Deep Blue Solutions Ltd");
MODULE_DESCRIPTION("ARM AMBA serial port driver");
MODULE_LICENSE("GPL");
