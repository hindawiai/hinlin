<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Based on drivers/serial/8250.c by Russell King.
 *
 *  Author:	Nicolas Pitre
 *  Created:	Feb 20, 2003
 *  Copyright:	(C) 2003 Monta Vista Software, Inc.
 *
 * Note 1: This driver is made separate from the alपढ़ोy too overloaded
 * 8250.c because it needs some kirks of its own and that'll make it
 * easier to add DMA support.
 *
 * Note 2: I'm too sick of device allocation policies क्रम serial ports.
 * If someone अन्यथा wants to request an "official" allocation of major/minor
 * क्रम this driver please be my guest.  And करोn't क्रमget that new hardware
 * to come from Intel might have more than 3 or 4 of those UARTs.  Let's
 * hope क्रम a better port registration and dynamic device allocation scheme
 * with the serial core मुख्यtainer satisfaction to appear soon.
 */


#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#घोषणा PXA_NAME_LEN		8

काष्ठा uart_pxa_port अणु
	काष्ठा uart_port        port;
	अचिन्हित अक्षर           ier;
	अचिन्हित अक्षर           lcr;
	अचिन्हित अक्षर           mcr;
	अचिन्हित पूर्णांक            lsr_अवरोध_flag;
	काष्ठा clk		*clk;
	अक्षर			name[PXA_NAME_LEN];
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक serial_in(काष्ठा uart_pxa_port *up, पूर्णांक offset)
अणु
	offset <<= 2;
	वापस पढ़ोl(up->port.membase + offset);
पूर्ण

अटल अंतरभूत व्योम serial_out(काष्ठा uart_pxa_port *up, पूर्णांक offset, पूर्णांक value)
अणु
	offset <<= 2;
	ग_लिखोl(value, up->port.membase + offset);
पूर्ण

अटल व्योम serial_pxa_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;

	up->ier |= UART_IER_MSI;
	serial_out(up, UART_IER, up->ier);
पूर्ण

अटल व्योम serial_pxa_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;

	अगर (up->ier & UART_IER_THRI) अणु
		up->ier &= ~UART_IER_THRI;
		serial_out(up, UART_IER, up->ier);
	पूर्ण
पूर्ण

अटल व्योम serial_pxa_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;

	up->ier &= ~UART_IER_RLSI;
	up->port.पढ़ो_status_mask &= ~UART_LSR_DR;
	serial_out(up, UART_IER, up->ier);
पूर्ण

अटल अंतरभूत व्योम receive_अक्षरs(काष्ठा uart_pxa_port *up, पूर्णांक *status)
अणु
	अचिन्हित पूर्णांक ch, flag;
	पूर्णांक max_count = 256;

	करो अणु
		/* work around Errata #20 according to
		 * Intel(R) PXA27x Processor Family
		 * Specअगरication Update (May 2005)
		 *
		 * Step 2
		 * Disable the Reciever Time Out Interrupt via IER[RTOEI]
		 */
		up->ier &= ~UART_IER_RTOIE;
		serial_out(up, UART_IER, up->ier);

		ch = serial_in(up, UART_RX);
		flag = TTY_NORMAL;
		up->port.icount.rx++;

		अगर (unlikely(*status & (UART_LSR_BI | UART_LSR_PE |
				       UART_LSR_FE | UART_LSR_OE))) अणु
			/*
			 * For statistics only
			 */
			अगर (*status & UART_LSR_BI) अणु
				*status &= ~(UART_LSR_FE | UART_LSR_PE);
				up->port.icount.brk++;
				/*
				 * We करो the SysRQ and SAK checking
				 * here because otherwise the अवरोध
				 * may get masked by ignore_status_mask
				 * or पढ़ो_status_mask.
				 */
				अगर (uart_handle_अवरोध(&up->port))
					जाओ ignore_अक्षर;
			पूर्ण अन्यथा अगर (*status & UART_LSR_PE)
				up->port.icount.parity++;
			अन्यथा अगर (*status & UART_LSR_FE)
				up->port.icount.frame++;
			अगर (*status & UART_LSR_OE)
				up->port.icount.overrun++;

			/*
			 * Mask off conditions which should be ignored.
			 */
			*status &= up->port.पढ़ो_status_mask;

#अगर_घोषित CONFIG_SERIAL_PXA_CONSOLE
			अगर (up->port.line == up->port.cons->index) अणु
				/* Recover the अवरोध flag from console xmit */
				*status |= up->lsr_अवरोध_flag;
				up->lsr_अवरोध_flag = 0;
			पूर्ण
#पूर्ण_अगर
			अगर (*status & UART_LSR_BI) अणु
				flag = TTY_BREAK;
			पूर्ण अन्यथा अगर (*status & UART_LSR_PE)
				flag = TTY_PARITY;
			अन्यथा अगर (*status & UART_LSR_FE)
				flag = TTY_FRAME;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(&up->port, ch))
			जाओ ignore_अक्षर;

		uart_insert_अक्षर(&up->port, *status, UART_LSR_OE, ch, flag);

	ignore_अक्षर:
		*status = serial_in(up, UART_LSR);
	पूर्ण जबतक ((*status & UART_LSR_DR) && (max_count-- > 0));
	tty_flip_buffer_push(&up->port.state->port);

	/* work around Errata #20 according to
	 * Intel(R) PXA27x Processor Family
	 * Specअगरication Update (May 2005)
	 *
	 * Step 6:
	 * No more data in FIFO: Re-enable RTO पूर्णांकerrupt via IER[RTOIE]
	 */
	up->ier |= UART_IER_RTOIE;
	serial_out(up, UART_IER, up->ier);
पूर्ण

अटल व्योम transmit_अक्षरs(काष्ठा uart_pxa_port *up)
अणु
	काष्ठा circ_buf *xmit = &up->port.state->xmit;
	पूर्णांक count;

	अगर (up->port.x_अक्षर) अणु
		serial_out(up, UART_TX, up->port.x_अक्षर);
		up->port.icount.tx++;
		up->port.x_अक्षर = 0;
		वापस;
	पूर्ण
	अगर (uart_circ_empty(xmit) || uart_tx_stopped(&up->port)) अणु
		serial_pxa_stop_tx(&up->port);
		वापस;
	पूर्ण

	count = up->port.fअगरosize / 2;
	करो अणु
		serial_out(up, UART_TX, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		up->port.icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण जबतक (--count > 0);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&up->port);


	अगर (uart_circ_empty(xmit))
		serial_pxa_stop_tx(&up->port);
पूर्ण

अटल व्योम serial_pxa_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;

	अगर (!(up->ier & UART_IER_THRI)) अणु
		up->ier |= UART_IER_THRI;
		serial_out(up, UART_IER, up->ier);
	पूर्ण
पूर्ण

/* should hold up->port.lock */
अटल अंतरभूत व्योम check_modem_status(काष्ठा uart_pxa_port *up)
अणु
	पूर्णांक status;

	status = serial_in(up, UART_MSR);

	अगर ((status & UART_MSR_ANY_DELTA) == 0)
		वापस;

	अगर (status & UART_MSR_TERI)
		up->port.icount.rng++;
	अगर (status & UART_MSR_DDSR)
		up->port.icount.dsr++;
	अगर (status & UART_MSR_DDCD)
		uart_handle_dcd_change(&up->port, status & UART_MSR_DCD);
	अगर (status & UART_MSR_DCTS)
		uart_handle_cts_change(&up->port, status & UART_MSR_CTS);

	wake_up_पूर्णांकerruptible(&up->port.state->port.delta_msr_रुको);
पूर्ण

/*
 * This handles the पूर्णांकerrupt from one port.
 */
अटल अंतरभूत irqवापस_t serial_pxa_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_pxa_port *up = dev_id;
	अचिन्हित पूर्णांक iir, lsr;

	iir = serial_in(up, UART_IIR);
	अगर (iir & UART_IIR_NO_INT)
		वापस IRQ_NONE;
	spin_lock(&up->port.lock);
	lsr = serial_in(up, UART_LSR);
	अगर (lsr & UART_LSR_DR)
		receive_अक्षरs(up, &lsr);
	check_modem_status(up);
	अगर (lsr & UART_LSR_THRE)
		transmit_अक्षरs(up);
	spin_unlock(&up->port.lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक serial_pxa_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ret;

	spin_lock_irqsave(&up->port.lock, flags);
	ret = serial_in(up, UART_LSR) & UART_LSR_TEMT ? TIOCSER_TEMT : 0;
	spin_unlock_irqrestore(&up->port.lock, flags);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक serial_pxa_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;
	अचिन्हित अक्षर status;
	अचिन्हित पूर्णांक ret;

	status = serial_in(up, UART_MSR);

	ret = 0;
	अगर (status & UART_MSR_DCD)
		ret |= TIOCM_CAR;
	अगर (status & UART_MSR_RI)
		ret |= TIOCM_RNG;
	अगर (status & UART_MSR_DSR)
		ret |= TIOCM_DSR;
	अगर (status & UART_MSR_CTS)
		ret |= TIOCM_CTS;
	वापस ret;
पूर्ण

अटल व्योम serial_pxa_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;
	अचिन्हित अक्षर mcr = 0;

	अगर (mctrl & TIOCM_RTS)
		mcr |= UART_MCR_RTS;
	अगर (mctrl & TIOCM_DTR)
		mcr |= UART_MCR_DTR;
	अगर (mctrl & TIOCM_OUT1)
		mcr |= UART_MCR_OUT1;
	अगर (mctrl & TIOCM_OUT2)
		mcr |= UART_MCR_OUT2;
	अगर (mctrl & TIOCM_LOOP)
		mcr |= UART_MCR_LOOP;

	mcr |= up->mcr;

	serial_out(up, UART_MCR, mcr);
पूर्ण

अटल व्योम serial_pxa_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&up->port.lock, flags);
	अगर (अवरोध_state == -1)
		up->lcr |= UART_LCR_SBC;
	अन्यथा
		up->lcr &= ~UART_LCR_SBC;
	serial_out(up, UART_LCR, up->lcr);
	spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

अटल पूर्णांक serial_pxa_startup(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	अगर (port->line == 3) /* HWUART */
		up->mcr |= UART_MCR_AFE;
	अन्यथा
		up->mcr = 0;

	up->port.uartclk = clk_get_rate(up->clk);

	/*
	 * Allocate the IRQ
	 */
	retval = request_irq(up->port.irq, serial_pxa_irq, 0, up->name, up);
	अगर (retval)
		वापस retval;

	/*
	 * Clear the FIFO buffers and disable them.
	 * (they will be reenabled in set_termios())
	 */
	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO);
	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO |
			UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
	serial_out(up, UART_FCR, 0);

	/*
	 * Clear the पूर्णांकerrupt रेजिस्टरs.
	 */
	(व्योम) serial_in(up, UART_LSR);
	(व्योम) serial_in(up, UART_RX);
	(व्योम) serial_in(up, UART_IIR);
	(व्योम) serial_in(up, UART_MSR);

	/*
	 * Now, initialize the UART
	 */
	serial_out(up, UART_LCR, UART_LCR_WLEN8);

	spin_lock_irqsave(&up->port.lock, flags);
	up->port.mctrl |= TIOCM_OUT2;
	serial_pxa_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);

	/*
	 * Finally, enable पूर्णांकerrupts.  Note: Modem status पूर्णांकerrupts
	 * are set via set_termios(), which will be occurring imminently
	 * anyway, so we करोn't enable them here.
	 */
	up->ier = UART_IER_RLSI | UART_IER_RDI | UART_IER_RTOIE | UART_IER_UUE;
	serial_out(up, UART_IER, up->ier);

	/*
	 * And clear the पूर्णांकerrupt रेजिस्टरs again क्रम luck.
	 */
	(व्योम) serial_in(up, UART_LSR);
	(व्योम) serial_in(up, UART_RX);
	(व्योम) serial_in(up, UART_IIR);
	(व्योम) serial_in(up, UART_MSR);

	वापस 0;
पूर्ण

अटल व्योम serial_pxa_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;
	अचिन्हित दीर्घ flags;

	मुक्त_irq(up->port.irq, up);

	/*
	 * Disable पूर्णांकerrupts from this port
	 */
	up->ier = 0;
	serial_out(up, UART_IER, 0);

	spin_lock_irqsave(&up->port.lock, flags);
	up->port.mctrl &= ~TIOCM_OUT2;
	serial_pxa_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);

	/*
	 * Disable अवरोध condition and FIFOs
	 */
	serial_out(up, UART_LCR, serial_in(up, UART_LCR) & ~UART_LCR_SBC);
	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO |
				  UART_FCR_CLEAR_RCVR |
				  UART_FCR_CLEAR_XMIT);
	serial_out(up, UART_FCR, 0);
पूर्ण

अटल व्योम
serial_pxa_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		       काष्ठा ktermios *old)
अणु
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;
	अचिन्हित अक्षर cval, fcr = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, quot;
	अचिन्हित पूर्णांक dll;

	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		cval = UART_LCR_WLEN5;
		अवरोध;
	हाल CS6:
		cval = UART_LCR_WLEN6;
		अवरोध;
	हाल CS7:
		cval = UART_LCR_WLEN7;
		अवरोध;
	शेष:
	हाल CS8:
		cval = UART_LCR_WLEN8;
		अवरोध;
	पूर्ण

	अगर (termios->c_cflag & CSTOPB)
		cval |= UART_LCR_STOP;
	अगर (termios->c_cflag & PARENB)
		cval |= UART_LCR_PARITY;
	अगर (!(termios->c_cflag & PARODD))
		cval |= UART_LCR_EPAR;

	/*
	 * Ask the core to calculate the भागisor क्रम us.
	 */
	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk/16);
	quot = uart_get_भागisor(port, baud);

	अगर ((up->port.uartclk / quot) < (2400 * 16))
		fcr = UART_FCR_ENABLE_FIFO | UART_FCR_PXAR1;
	अन्यथा अगर ((up->port.uartclk / quot) < (230400 * 16))
		fcr = UART_FCR_ENABLE_FIFO | UART_FCR_PXAR8;
	अन्यथा
		fcr = UART_FCR_ENABLE_FIFO | UART_FCR_PXAR32;

	/*
	 * Ok, we're now changing the port state.  Do it with
	 * पूर्णांकerrupts disabled.
	 */
	spin_lock_irqsave(&up->port.lock, flags);

	/*
	 * Ensure the port will be enabled.
	 * This is required especially क्रम serial console.
	 */
	up->ier |= UART_IER_UUE;

	/*
	 * Update the per-port समयout.
	 */
	uart_update_समयout(port, termios->c_cflag, baud);

	up->port.पढ़ो_status_mask = UART_LSR_OE | UART_LSR_THRE | UART_LSR_DR;
	अगर (termios->c_अगरlag & INPCK)
		up->port.पढ़ो_status_mask |= UART_LSR_FE | UART_LSR_PE;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		up->port.पढ़ो_status_mask |= UART_LSR_BI;

	/*
	 * Characters to ignore
	 */
	up->port.ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		up->port.ignore_status_mask |= UART_LSR_PE | UART_LSR_FE;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		up->port.ignore_status_mask |= UART_LSR_BI;
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			up->port.ignore_status_mask |= UART_LSR_OE;
	पूर्ण

	/*
	 * ignore all अक्षरacters अगर CREAD is not set
	 */
	अगर ((termios->c_cflag & CREAD) == 0)
		up->port.ignore_status_mask |= UART_LSR_DR;

	/*
	 * CTS flow control flag and modem status पूर्णांकerrupts
	 */
	up->ier &= ~UART_IER_MSI;
	अगर (UART_ENABLE_MS(&up->port, termios->c_cflag))
		up->ier |= UART_IER_MSI;

	serial_out(up, UART_IER, up->ier);

	अगर (termios->c_cflag & CRTSCTS)
		up->mcr |= UART_MCR_AFE;
	अन्यथा
		up->mcr &= ~UART_MCR_AFE;

	serial_out(up, UART_LCR, cval | UART_LCR_DLAB);	/* set DLAB */
	serial_out(up, UART_DLL, quot & 0xff);		/* LS of भागisor */

	/*
	 * work around Errata #75 according to Intel(R) PXA27x Processor Family
	 * Specअगरication Update (Nov 2005)
	 */
	dll = serial_in(up, UART_DLL);
	WARN_ON(dll != (quot & 0xff));

	serial_out(up, UART_DLM, quot >> 8);		/* MS of भागisor */
	serial_out(up, UART_LCR, cval);			/* reset DLAB */
	up->lcr = cval;					/* Save LCR */
	serial_pxa_set_mctrl(&up->port, up->port.mctrl);
	serial_out(up, UART_FCR, fcr);
	spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

अटल व्योम
serial_pxa_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
	      अचिन्हित पूर्णांक oldstate)
अणु
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;

	अगर (!state)
		clk_prepare_enable(up->clk);
	अन्यथा
		clk_disable_unprepare(up->clk);
पूर्ण

अटल व्योम serial_pxa_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक serial_pxa_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम serial_pxa_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;
	up->port.type = PORT_PXA;
पूर्ण

अटल पूर्णांक
serial_pxa_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	/* we करोn't want the core code to modअगरy any port params */
	वापस -EINVAL;
पूर्ण

अटल स्थिर अक्षर *
serial_pxa_type(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;
	वापस up->name;
पूर्ण

अटल काष्ठा uart_pxa_port *serial_pxa_ports[4];
अटल काष्ठा uart_driver serial_pxa_reg;

#अगर_घोषित CONFIG_SERIAL_PXA_CONSOLE

#घोषणा BOTH_EMPTY (UART_LSR_TEMT | UART_LSR_THRE)

/*
 *	Wait क्रम transmitter & holding रेजिस्टर to empty
 */
अटल व्योम रुको_क्रम_xmitr(काष्ठा uart_pxa_port *up)
अणु
	अचिन्हित पूर्णांक status, पंचांगout = 10000;

	/* Wait up to 10ms क्रम the अक्षरacter(s) to be sent. */
	करो अणु
		status = serial_in(up, UART_LSR);

		अगर (status & UART_LSR_BI)
			up->lsr_अवरोध_flag = UART_LSR_BI;

		अगर (--पंचांगout == 0)
			अवरोध;
		udelay(1);
	पूर्ण जबतक ((status & BOTH_EMPTY) != BOTH_EMPTY);

	/* Wait up to 1s क्रम flow control अगर necessary */
	अगर (up->port.flags & UPF_CONS_FLOW) अणु
		पंचांगout = 1000000;
		जबतक (--पंचांगout &&
		       ((serial_in(up, UART_MSR) & UART_MSR_CTS) == 0))
			udelay(1);
	पूर्ण
पूर्ण

अटल व्योम serial_pxa_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;

	रुको_क्रम_xmitr(up);
	serial_out(up, UART_TX, ch);
पूर्ण

/*
 * Prपूर्णांक a string to the serial port trying not to disturb
 * any possible real use of the port...
 *
 *	The console_lock must be held when we get here.
 */
अटल व्योम
serial_pxa_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_pxa_port *up = serial_pxa_ports[co->index];
	अचिन्हित पूर्णांक ier;
	अचिन्हित दीर्घ flags;
	पूर्णांक locked = 1;

	clk_enable(up->clk);
	local_irq_save(flags);
	अगर (up->port.sysrq)
		locked = 0;
	अन्यथा अगर (oops_in_progress)
		locked = spin_trylock(&up->port.lock);
	अन्यथा
		spin_lock(&up->port.lock);

	/*
	 *	First save the IER then disable the पूर्णांकerrupts
	 */
	ier = serial_in(up, UART_IER);
	serial_out(up, UART_IER, UART_IER_UUE);

	uart_console_ग_लिखो(&up->port, s, count, serial_pxa_console_अक्षर_दो);

	/*
	 *	Finally, रुको क्रम transmitter to become empty
	 *	and restore the IER
	 */
	रुको_क्रम_xmitr(up);
	serial_out(up, UART_IER, ier);

	अगर (locked)
		spin_unlock(&up->port.lock);
	local_irq_restore(flags);
	clk_disable(up->clk);

पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
/*
 * Console polling routines क्रम writing and पढ़ोing from the uart जबतक
 * in an पूर्णांकerrupt or debug context.
 */

अटल पूर्णांक serial_pxa_get_poll_अक्षर(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;
	अचिन्हित अक्षर lsr = serial_in(up, UART_LSR);

	जबतक (!(lsr & UART_LSR_DR))
		lsr = serial_in(up, UART_LSR);

	वापस serial_in(up, UART_RX);
पूर्ण


अटल व्योम serial_pxa_put_poll_अक्षर(काष्ठा uart_port *port,
			 अचिन्हित अक्षर c)
अणु
	अचिन्हित पूर्णांक ier;
	काष्ठा uart_pxa_port *up = (काष्ठा uart_pxa_port *)port;

	/*
	 *	First save the IER then disable the पूर्णांकerrupts
	 */
	ier = serial_in(up, UART_IER);
	serial_out(up, UART_IER, UART_IER_UUE);

	रुको_क्रम_xmitr(up);
	/*
	 *	Send the अक्षरacter out.
	 */
	serial_out(up, UART_TX, c);

	/*
	 *	Finally, रुको क्रम transmitter to become empty
	 *	and restore the IER
	 */
	रुको_क्रम_xmitr(up);
	serial_out(up, UART_IER, ier);
पूर्ण

#पूर्ण_अगर /* CONFIG_CONSOLE_POLL */

अटल पूर्णांक __init
serial_pxa_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_pxa_port *up;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (co->index == -1 || co->index >= serial_pxa_reg.nr)
		co->index = 0;
	up = serial_pxa_ports[co->index];
	अगर (!up)
		वापस -ENODEV;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(&up->port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा console serial_pxa_console = अणु
	.name		= "ttyS",
	.ग_लिखो		= serial_pxa_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= serial_pxa_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &serial_pxa_reg,
पूर्ण;

#घोषणा PXA_CONSOLE	&serial_pxa_console
#अन्यथा
#घोषणा PXA_CONSOLE	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा uart_ops serial_pxa_pops = अणु
	.tx_empty	= serial_pxa_tx_empty,
	.set_mctrl	= serial_pxa_set_mctrl,
	.get_mctrl	= serial_pxa_get_mctrl,
	.stop_tx	= serial_pxa_stop_tx,
	.start_tx	= serial_pxa_start_tx,
	.stop_rx	= serial_pxa_stop_rx,
	.enable_ms	= serial_pxa_enable_ms,
	.अवरोध_ctl	= serial_pxa_अवरोध_ctl,
	.startup	= serial_pxa_startup,
	.shutकरोwn	= serial_pxa_shutकरोwn,
	.set_termios	= serial_pxa_set_termios,
	.pm		= serial_pxa_pm,
	.type		= serial_pxa_type,
	.release_port	= serial_pxa_release_port,
	.request_port	= serial_pxa_request_port,
	.config_port	= serial_pxa_config_port,
	.verअगरy_port	= serial_pxa_verअगरy_port,
#अगर defined(CONFIG_CONSOLE_POLL) && defined(CONFIG_SERIAL_PXA_CONSOLE)
	.poll_get_अक्षर = serial_pxa_get_poll_अक्षर,
	.poll_put_अक्षर = serial_pxa_put_poll_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा uart_driver serial_pxa_reg = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "PXA serial",
	.dev_name	= "ttyS",
	.major		= TTY_MAJOR,
	.minor		= 64,
	.nr		= 4,
	.cons		= PXA_CONSOLE,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक serial_pxa_suspend(काष्ठा device *dev)
अणु
        काष्ठा uart_pxa_port *sport = dev_get_drvdata(dev);

        अगर (sport)
                uart_suspend_port(&serial_pxa_reg, &sport->port);

        वापस 0;
पूर्ण

अटल पूर्णांक serial_pxa_resume(काष्ठा device *dev)
अणु
        काष्ठा uart_pxa_port *sport = dev_get_drvdata(dev);

        अगर (sport)
                uart_resume_port(&serial_pxa_reg, &sport->port);

        वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops serial_pxa_pm_ops = अणु
	.suspend	= serial_pxa_suspend,
	.resume		= serial_pxa_resume,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id serial_pxa_dt_ids[] = अणु
	अणु .compatible = "mrvl,pxa-uart", पूर्ण,
	अणु .compatible = "mrvl,mmp-uart", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक serial_pxa_probe_dt(काष्ठा platक्रमm_device *pdev,
			       काष्ठा uart_pxa_port *sport)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;

	अगर (!np)
		वापस 1;

	ret = of_alias_get_id(np, "serial");
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to get alias id, errno %d\n", ret);
		वापस ret;
	पूर्ण
	sport->port.line = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक serial_pxa_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा uart_pxa_port *sport;
	काष्ठा resource *mmres, *irqres;
	पूर्णांक ret;

	mmres = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	irqres = platक्रमm_get_resource(dev, IORESOURCE_IRQ, 0);
	अगर (!mmres || !irqres)
		वापस -ENODEV;

	sport = kzalloc(माप(काष्ठा uart_pxa_port), GFP_KERNEL);
	अगर (!sport)
		वापस -ENOMEM;

	sport->clk = clk_get(&dev->dev, शून्य);
	अगर (IS_ERR(sport->clk)) अणु
		ret = PTR_ERR(sport->clk);
		जाओ err_मुक्त;
	पूर्ण

	ret = clk_prepare(sport->clk);
	अगर (ret) अणु
		clk_put(sport->clk);
		जाओ err_मुक्त;
	पूर्ण

	sport->port.type = PORT_PXA;
	sport->port.iotype = UPIO_MEM;
	sport->port.mapbase = mmres->start;
	sport->port.irq = irqres->start;
	sport->port.fअगरosize = 64;
	sport->port.ops = &serial_pxa_pops;
	sport->port.dev = &dev->dev;
	sport->port.flags = UPF_IOREMAP | UPF_BOOT_AUTOCONF;
	sport->port.uartclk = clk_get_rate(sport->clk);
	sport->port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_PXA_CONSOLE);

	ret = serial_pxa_probe_dt(dev, sport);
	अगर (ret > 0)
		sport->port.line = dev->id;
	अन्यथा अगर (ret < 0)
		जाओ err_clk;
	अगर (sport->port.line >= ARRAY_SIZE(serial_pxa_ports)) अणु
		dev_err(&dev->dev, "serial%d out of range\n", sport->port.line);
		ret = -EINVAL;
		जाओ err_clk;
	पूर्ण
	snम_लिखो(sport->name, PXA_NAME_LEN - 1, "UART%d", sport->port.line + 1);

	sport->port.membase = ioremap(mmres->start, resource_size(mmres));
	अगर (!sport->port.membase) अणु
		ret = -ENOMEM;
		जाओ err_clk;
	पूर्ण

	serial_pxa_ports[sport->port.line] = sport;

	uart_add_one_port(&serial_pxa_reg, &sport->port);
	platक्रमm_set_drvdata(dev, sport);

	वापस 0;

 err_clk:
	clk_unprepare(sport->clk);
	clk_put(sport->clk);
 err_मुक्त:
	kमुक्त(sport);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver serial_pxa_driver = अणु
        .probe          = serial_pxa_probe,

	.driver		= अणु
	        .name	= "pxa2xx-uart",
#अगर_घोषित CONFIG_PM
		.pm	= &serial_pxa_pm_ops,
#पूर्ण_अगर
		.suppress_bind_attrs = true,
		.of_match_table = serial_pxa_dt_ids,
	पूर्ण,
पूर्ण;


/* 8250 driver क्रम PXA serial ports should be used */
अटल पूर्णांक __init serial_pxa_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&serial_pxa_reg);
	अगर (ret != 0)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&serial_pxa_driver);
	अगर (ret != 0)
		uart_unरेजिस्टर_driver(&serial_pxa_reg);

	वापस ret;
पूर्ण
device_initcall(serial_pxa_init);
