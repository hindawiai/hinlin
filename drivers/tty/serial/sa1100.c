<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Driver क्रम SA11x0 serial ports
 *
 *  Based on drivers/अक्षर/serial.c, by Linus Torvalds, Theoकरोre Ts'o.
 *
 *  Copyright (C) 2000 Deep Blue Solutions Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/platक्रमm_data/sa11x0-serial.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/irq.h>
#समावेश <mach/hardware.h>
#समावेश <mach/irqs.h>

#समावेश "serial_mctrl_gpio.h"

/* We've been asचिन्हित a range on the "Low-density serial ports" major */
#घोषणा SERIAL_SA1100_MAJOR	204
#घोषणा MINOR_START		5

#घोषणा NR_PORTS		3

#घोषणा SA1100_ISR_PASS_LIMIT	256

/*
 * Convert from ignore_status_mask or पढ़ो_status_mask to UTSR[01]
 */
#घोषणा SM_TO_UTSR0(x)	((x) & 0xff)
#घोषणा SM_TO_UTSR1(x)	((x) >> 8)
#घोषणा UTSR0_TO_SM(x)	((x))
#घोषणा UTSR1_TO_SM(x)	((x) << 8)

#घोषणा UART_GET_UTCR0(sport)	__raw_पढ़ोl((sport)->port.membase + UTCR0)
#घोषणा UART_GET_UTCR1(sport)	__raw_पढ़ोl((sport)->port.membase + UTCR1)
#घोषणा UART_GET_UTCR2(sport)	__raw_पढ़ोl((sport)->port.membase + UTCR2)
#घोषणा UART_GET_UTCR3(sport)	__raw_पढ़ोl((sport)->port.membase + UTCR3)
#घोषणा UART_GET_UTSR0(sport)	__raw_पढ़ोl((sport)->port.membase + UTSR0)
#घोषणा UART_GET_UTSR1(sport)	__raw_पढ़ोl((sport)->port.membase + UTSR1)
#घोषणा UART_GET_CHAR(sport)	__raw_पढ़ोl((sport)->port.membase + UTDR)

#घोषणा UART_PUT_UTCR0(sport,v)	__raw_ग_लिखोl((v),(sport)->port.membase + UTCR0)
#घोषणा UART_PUT_UTCR1(sport,v)	__raw_ग_लिखोl((v),(sport)->port.membase + UTCR1)
#घोषणा UART_PUT_UTCR2(sport,v)	__raw_ग_लिखोl((v),(sport)->port.membase + UTCR2)
#घोषणा UART_PUT_UTCR3(sport,v)	__raw_ग_लिखोl((v),(sport)->port.membase + UTCR3)
#घोषणा UART_PUT_UTSR0(sport,v)	__raw_ग_लिखोl((v),(sport)->port.membase + UTSR0)
#घोषणा UART_PUT_UTSR1(sport,v)	__raw_ग_लिखोl((v),(sport)->port.membase + UTSR1)
#घोषणा UART_PUT_CHAR(sport,v)	__raw_ग_लिखोl((v),(sport)->port.membase + UTDR)

/*
 * This is the size of our serial port रेजिस्टर set.
 */
#घोषणा UART_PORT_SIZE	0x24

/*
 * This determines how often we check the modem status संकेतs
 * क्रम any change.  They generally aren't connected to an IRQ
 * so we have to poll them.  We also check immediately beक्रमe
 * filling the TX fअगरo inहाल CTS has been dropped.
 */
#घोषणा MCTRL_TIMEOUT	(250*HZ/1000)

काष्ठा sa1100_port अणु
	काष्ठा uart_port	port;
	काष्ठा समयr_list	समयr;
	अचिन्हित पूर्णांक		old_status;
	काष्ठा mctrl_gpios	*gpios;
पूर्ण;

/*
 * Handle any change of modem status संकेत since we were last called.
 */
अटल व्योम sa1100_mctrl_check(काष्ठा sa1100_port *sport)
अणु
	अचिन्हित पूर्णांक status, changed;

	status = sport->port.ops->get_mctrl(&sport->port);
	changed = status ^ sport->old_status;

	अगर (changed == 0)
		वापस;

	sport->old_status = status;

	अगर (changed & TIOCM_RI)
		sport->port.icount.rng++;
	अगर (changed & TIOCM_DSR)
		sport->port.icount.dsr++;
	अगर (changed & TIOCM_CAR)
		uart_handle_dcd_change(&sport->port, status & TIOCM_CAR);
	अगर (changed & TIOCM_CTS)
		uart_handle_cts_change(&sport->port, status & TIOCM_CTS);

	wake_up_पूर्णांकerruptible(&sport->port.state->port.delta_msr_रुको);
पूर्ण

/*
 * This is our per-port समयout handler, क्रम checking the
 * modem status संकेतs.
 */
अटल व्योम sa1100_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा sa1100_port *sport = from_समयr(sport, t, समयr);
	अचिन्हित दीर्घ flags;

	अगर (sport->port.state) अणु
		spin_lock_irqsave(&sport->port.lock, flags);
		sa1100_mctrl_check(sport);
		spin_unlock_irqrestore(&sport->port.lock, flags);

		mod_समयr(&sport->समयr, jअगरfies + MCTRL_TIMEOUT);
	पूर्ण
पूर्ण

/*
 * पूर्णांकerrupts disabled on entry
 */
अटल व्योम sa1100_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);
	u32 utcr3;

	utcr3 = UART_GET_UTCR3(sport);
	UART_PUT_UTCR3(sport, utcr3 & ~UTCR3_TIE);
	sport->port.पढ़ो_status_mask &= ~UTSR0_TO_SM(UTSR0_TFS);
पूर्ण

/*
 * port locked and पूर्णांकerrupts disabled
 */
अटल व्योम sa1100_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);
	u32 utcr3;

	utcr3 = UART_GET_UTCR3(sport);
	sport->port.पढ़ो_status_mask |= UTSR0_TO_SM(UTSR0_TFS);
	UART_PUT_UTCR3(sport, utcr3 | UTCR3_TIE);
पूर्ण

/*
 * Interrupts enabled
 */
अटल व्योम sa1100_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);
	u32 utcr3;

	utcr3 = UART_GET_UTCR3(sport);
	UART_PUT_UTCR3(sport, utcr3 & ~UTCR3_RIE);
पूर्ण

/*
 * Set the modem control समयr to fire immediately.
 */
अटल व्योम sa1100_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);

	mod_समयr(&sport->समयr, jअगरfies);

	mctrl_gpio_enable_ms(sport->gpios);
पूर्ण

अटल व्योम
sa1100_rx_अक्षरs(काष्ठा sa1100_port *sport)
अणु
	अचिन्हित पूर्णांक status, ch, flg;

	status = UTSR1_TO_SM(UART_GET_UTSR1(sport)) |
		 UTSR0_TO_SM(UART_GET_UTSR0(sport));
	जबतक (status & UTSR1_TO_SM(UTSR1_RNE)) अणु
		ch = UART_GET_CHAR(sport);

		sport->port.icount.rx++;

		flg = TTY_NORMAL;

		/*
		 * note that the error handling code is
		 * out of the मुख्य execution path
		 */
		अगर (status & UTSR1_TO_SM(UTSR1_PRE | UTSR1_FRE | UTSR1_ROR)) अणु
			अगर (status & UTSR1_TO_SM(UTSR1_PRE))
				sport->port.icount.parity++;
			अन्यथा अगर (status & UTSR1_TO_SM(UTSR1_FRE))
				sport->port.icount.frame++;
			अगर (status & UTSR1_TO_SM(UTSR1_ROR))
				sport->port.icount.overrun++;

			status &= sport->port.पढ़ो_status_mask;

			अगर (status & UTSR1_TO_SM(UTSR1_PRE))
				flg = TTY_PARITY;
			अन्यथा अगर (status & UTSR1_TO_SM(UTSR1_FRE))
				flg = TTY_FRAME;

			sport->port.sysrq = 0;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(&sport->port, ch))
			जाओ ignore_अक्षर;

		uart_insert_अक्षर(&sport->port, status, UTSR1_TO_SM(UTSR1_ROR), ch, flg);

	ignore_अक्षर:
		status = UTSR1_TO_SM(UART_GET_UTSR1(sport)) |
			 UTSR0_TO_SM(UART_GET_UTSR0(sport));
	पूर्ण

	tty_flip_buffer_push(&sport->port.state->port);
पूर्ण

अटल व्योम sa1100_tx_अक्षरs(काष्ठा sa1100_port *sport)
अणु
	काष्ठा circ_buf *xmit = &sport->port.state->xmit;

	अगर (sport->port.x_अक्षर) अणु
		UART_PUT_CHAR(sport, sport->port.x_अक्षर);
		sport->port.icount.tx++;
		sport->port.x_अक्षर = 0;
		वापस;
	पूर्ण

	/*
	 * Check the modem control lines beक्रमe
	 * transmitting anything.
	 */
	sa1100_mctrl_check(sport);

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(&sport->port)) अणु
		sa1100_stop_tx(&sport->port);
		वापस;
	पूर्ण

	/*
	 * Tried using FIFO (not checking TNF) क्रम fअगरo fill:
	 * still had the '4 bytes repeated' problem.
	 */
	जबतक (UART_GET_UTSR1(sport) & UTSR1_TNF) अणु
		UART_PUT_CHAR(sport, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		sport->port.icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&sport->port);

	अगर (uart_circ_empty(xmit))
		sa1100_stop_tx(&sport->port);
पूर्ण

अटल irqवापस_t sa1100_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sa1100_port *sport = dev_id;
	अचिन्हित पूर्णांक status, pass_counter = 0;

	spin_lock(&sport->port.lock);
	status = UART_GET_UTSR0(sport);
	status &= SM_TO_UTSR0(sport->port.पढ़ो_status_mask) | ~UTSR0_TFS;
	करो अणु
		अगर (status & (UTSR0_RFS | UTSR0_RID)) अणु
			/* Clear the receiver idle bit, अगर set */
			अगर (status & UTSR0_RID)
				UART_PUT_UTSR0(sport, UTSR0_RID);
			sa1100_rx_अक्षरs(sport);
		पूर्ण

		/* Clear the relevant अवरोध bits */
		अगर (status & (UTSR0_RBB | UTSR0_REB))
			UART_PUT_UTSR0(sport, status & (UTSR0_RBB | UTSR0_REB));

		अगर (status & UTSR0_RBB)
			sport->port.icount.brk++;

		अगर (status & UTSR0_REB)
			uart_handle_अवरोध(&sport->port);

		अगर (status & UTSR0_TFS)
			sa1100_tx_अक्षरs(sport);
		अगर (pass_counter++ > SA1100_ISR_PASS_LIMIT)
			अवरोध;
		status = UART_GET_UTSR0(sport);
		status &= SM_TO_UTSR0(sport->port.पढ़ो_status_mask) |
			  ~UTSR0_TFS;
	पूर्ण जबतक (status & (UTSR0_TFS | UTSR0_RFS | UTSR0_RID));
	spin_unlock(&sport->port.lock);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Return TIOCSER_TEMT when transmitter is not busy.
 */
अटल अचिन्हित पूर्णांक sa1100_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);

	वापस UART_GET_UTSR1(sport) & UTSR1_TBY ? 0 : TIOCSER_TEMT;
पूर्ण

अटल अचिन्हित पूर्णांक sa1100_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);
	पूर्णांक ret = TIOCM_CTS | TIOCM_DSR | TIOCM_CAR;

	mctrl_gpio_get(sport->gpios, &ret);

	वापस ret;
पूर्ण

अटल व्योम sa1100_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);

	mctrl_gpio_set(sport->gpios, mctrl);
पूर्ण

/*
 * Interrupts always disabled.
 */
अटल व्योम sa1100_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक utcr3;

	spin_lock_irqsave(&sport->port.lock, flags);
	utcr3 = UART_GET_UTCR3(sport);
	अगर (अवरोध_state == -1)
		utcr3 |= UTCR3_BRK;
	अन्यथा
		utcr3 &= ~UTCR3_BRK;
	UART_PUT_UTCR3(sport, utcr3);
	spin_unlock_irqrestore(&sport->port.lock, flags);
पूर्ण

अटल पूर्णांक sa1100_startup(काष्ठा uart_port *port)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);
	पूर्णांक retval;

	/*
	 * Allocate the IRQ
	 */
	retval = request_irq(sport->port.irq, sa1100_पूर्णांक, 0,
			     "sa11x0-uart", sport);
	अगर (retval)
		वापस retval;

	/*
	 * Finally, clear and enable पूर्णांकerrupts
	 */
	UART_PUT_UTSR0(sport, -1);
	UART_PUT_UTCR3(sport, UTCR3_RXE | UTCR3_TXE | UTCR3_RIE);

	/*
	 * Enable modem status पूर्णांकerrupts
	 */
	spin_lock_irq(&sport->port.lock);
	sa1100_enable_ms(&sport->port);
	spin_unlock_irq(&sport->port.lock);

	वापस 0;
पूर्ण

अटल व्योम sa1100_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);

	/*
	 * Stop our समयr.
	 */
	del_समयr_sync(&sport->समयr);

	/*
	 * Free the पूर्णांकerrupt
	 */
	मुक्त_irq(sport->port.irq, sport);

	/*
	 * Disable all पूर्णांकerrupts, port and अवरोध condition.
	 */
	UART_PUT_UTCR3(sport, 0);
पूर्ण

अटल व्योम
sa1100_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		   काष्ठा ktermios *old)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक utcr0, old_utcr3, baud, quot;
	अचिन्हित पूर्णांक old_csize = old ? old->c_cflag & CSIZE : CS8;

	/*
	 * We only support CS7 and CS8.
	 */
	जबतक ((termios->c_cflag & CSIZE) != CS7 &&
	       (termios->c_cflag & CSIZE) != CS8) अणु
		termios->c_cflag &= ~CSIZE;
		termios->c_cflag |= old_csize;
		old_csize = CS8;
	पूर्ण

	अगर ((termios->c_cflag & CSIZE) == CS8)
		utcr0 = UTCR0_DSS;
	अन्यथा
		utcr0 = 0;

	अगर (termios->c_cflag & CSTOPB)
		utcr0 |= UTCR0_SBS;
	अगर (termios->c_cflag & PARENB) अणु
		utcr0 |= UTCR0_PE;
		अगर (!(termios->c_cflag & PARODD))
			utcr0 |= UTCR0_OES;
	पूर्ण

	/*
	 * Ask the core to calculate the भागisor क्रम us.
	 */
	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk/16); 
	quot = uart_get_भागisor(port, baud);

	spin_lock_irqsave(&sport->port.lock, flags);

	sport->port.पढ़ो_status_mask &= UTSR0_TO_SM(UTSR0_TFS);
	sport->port.पढ़ो_status_mask |= UTSR1_TO_SM(UTSR1_ROR);
	अगर (termios->c_अगरlag & INPCK)
		sport->port.पढ़ो_status_mask |=
				UTSR1_TO_SM(UTSR1_FRE | UTSR1_PRE);
	अगर (termios->c_अगरlag & (BRKINT | PARMRK))
		sport->port.पढ़ो_status_mask |=
				UTSR0_TO_SM(UTSR0_RBB | UTSR0_REB);

	/*
	 * Characters to ignore
	 */
	sport->port.ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		sport->port.ignore_status_mask |=
				UTSR1_TO_SM(UTSR1_FRE | UTSR1_PRE);
	अगर (termios->c_अगरlag & IGNBRK) अणु
		sport->port.ignore_status_mask |=
				UTSR0_TO_SM(UTSR0_RBB | UTSR0_REB);
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			sport->port.ignore_status_mask |=
				UTSR1_TO_SM(UTSR1_ROR);
	पूर्ण

	del_समयr_sync(&sport->समयr);

	/*
	 * Update the per-port समयout.
	 */
	uart_update_समयout(port, termios->c_cflag, baud);

	/*
	 * disable पूर्णांकerrupts and drain transmitter
	 */
	old_utcr3 = UART_GET_UTCR3(sport);
	UART_PUT_UTCR3(sport, old_utcr3 & ~(UTCR3_RIE | UTCR3_TIE));

	जबतक (UART_GET_UTSR1(sport) & UTSR1_TBY)
		barrier();

	/* then, disable everything */
	UART_PUT_UTCR3(sport, 0);

	/* set the parity, stop bits and data size */
	UART_PUT_UTCR0(sport, utcr0);

	/* set the baud rate */
	quot -= 1;
	UART_PUT_UTCR1(sport, ((quot & 0xf00) >> 8));
	UART_PUT_UTCR2(sport, (quot & 0xff));

	UART_PUT_UTSR0(sport, -1);

	UART_PUT_UTCR3(sport, old_utcr3);

	अगर (UART_ENABLE_MS(&sport->port, termios->c_cflag))
		sa1100_enable_ms(&sport->port);

	spin_unlock_irqrestore(&sport->port.lock, flags);
पूर्ण

अटल स्थिर अक्षर *sa1100_type(काष्ठा uart_port *port)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);

	वापस sport->port.type == PORT_SA1100 ? "SA1100" : शून्य;
पूर्ण

/*
 * Release the memory region(s) being used by 'port'.
 */
अटल व्योम sa1100_release_port(काष्ठा uart_port *port)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);

	release_mem_region(sport->port.mapbase, UART_PORT_SIZE);
पूर्ण

/*
 * Request the memory region(s) being used by 'port'.
 */
अटल पूर्णांक sa1100_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);

	वापस request_mem_region(sport->port.mapbase, UART_PORT_SIZE,
			"sa11x0-uart") != शून्य ? 0 : -EBUSY;
पूर्ण

/*
 * Configure/स्वतःconfigure the port.
 */
अटल व्योम sa1100_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);

	अगर (flags & UART_CONFIG_TYPE &&
	    sa1100_request_port(&sport->port) == 0)
		sport->port.type = PORT_SA1100;
पूर्ण

/*
 * Verअगरy the new serial_काष्ठा (क्रम TIOCSSERIAL).
 * The only change we allow are to the flags and type, and
 * even then only between PORT_SA1100 and PORT_UNKNOWN
 */
अटल पूर्णांक
sa1100_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);
	पूर्णांक ret = 0;

	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_SA1100)
		ret = -EINVAL;
	अगर (sport->port.irq != ser->irq)
		ret = -EINVAL;
	अगर (ser->io_type != SERIAL_IO_MEM)
		ret = -EINVAL;
	अगर (sport->port.uartclk / 16 != ser->baud_base)
		ret = -EINVAL;
	अगर ((व्योम *)sport->port.mapbase != ser->iomem_base)
		ret = -EINVAL;
	अगर (sport->port.iobase != ser->port)
		ret = -EINVAL;
	अगर (ser->hub6 != 0)
		ret = -EINVAL;
	वापस ret;
पूर्ण

अटल काष्ठा uart_ops sa1100_pops = अणु
	.tx_empty	= sa1100_tx_empty,
	.set_mctrl	= sa1100_set_mctrl,
	.get_mctrl	= sa1100_get_mctrl,
	.stop_tx	= sa1100_stop_tx,
	.start_tx	= sa1100_start_tx,
	.stop_rx	= sa1100_stop_rx,
	.enable_ms	= sa1100_enable_ms,
	.अवरोध_ctl	= sa1100_अवरोध_ctl,
	.startup	= sa1100_startup,
	.shutकरोwn	= sa1100_shutकरोwn,
	.set_termios	= sa1100_set_termios,
	.type		= sa1100_type,
	.release_port	= sa1100_release_port,
	.request_port	= sa1100_request_port,
	.config_port	= sa1100_config_port,
	.verअगरy_port	= sa1100_verअगरy_port,
पूर्ण;

अटल काष्ठा sa1100_port sa1100_ports[NR_PORTS];

/*
 * Setup the SA1100 serial ports.  Note that we करोn't include the IrDA
 * port here since we have our own SIR/FIR driver (see drivers/net/irda)
 *
 * Note also that we support "console=ttySAx" where "x" is either 0 or 1.
 * Which serial port this ends up being depends on the machine you're
 * running this kernel on.  I'm not convinced that this is a good idea,
 * but that's the way it traditionally works.
 *
 * Note that NanoEngine UART3 becomes UART2, and UART2 is no दीर्घer
 * used here.
 */
अटल व्योम __init sa1100_init_ports(व्योम)
अणु
	अटल पूर्णांक first = 1;
	पूर्णांक i;

	अगर (!first)
		वापस;
	first = 0;

	क्रम (i = 0; i < NR_PORTS; i++) अणु
		sa1100_ports[i].port.uartclk   = 3686400;
		sa1100_ports[i].port.ops       = &sa1100_pops;
		sa1100_ports[i].port.fअगरosize  = 8;
		sa1100_ports[i].port.line      = i;
		sa1100_ports[i].port.iotype    = UPIO_MEM;
		समयr_setup(&sa1100_ports[i].समयr, sa1100_समयout, 0);
	पूर्ण

	/*
	 * make transmit lines outमाला_दो, so that when the port
	 * is बंदd, the output is in the MARK state.
	 */
	PPDR |= PPC_TXD1 | PPC_TXD3;
	PPSR |= PPC_TXD1 | PPC_TXD3;
पूर्ण

व्योम sa1100_रेजिस्टर_uart_fns(काष्ठा sa1100_port_fns *fns)
अणु
	अगर (fns->get_mctrl)
		sa1100_pops.get_mctrl = fns->get_mctrl;
	अगर (fns->set_mctrl)
		sa1100_pops.set_mctrl = fns->set_mctrl;

	sa1100_pops.pm       = fns->pm;
	/*
	 * FIXME: fns->set_wake is unused - this should be called from
	 * the suspend() callback अगर device_may_wakeup(dev)) is set.
	 */
पूर्ण

व्योम __init sa1100_रेजिस्टर_uart(पूर्णांक idx, पूर्णांक port)
अणु
	अगर (idx >= NR_PORTS) अणु
		prपूर्णांकk(KERN_ERR "%s: bad index number %d\n", __func__, idx);
		वापस;
	पूर्ण

	चयन (port) अणु
	हाल 1:
		sa1100_ports[idx].port.membase = (व्योम __iomem *)&Ser1UTCR0;
		sa1100_ports[idx].port.mapbase = _Ser1UTCR0;
		sa1100_ports[idx].port.irq     = IRQ_Ser1UART;
		sa1100_ports[idx].port.flags   = UPF_BOOT_AUTOCONF;
		अवरोध;

	हाल 2:
		sa1100_ports[idx].port.membase = (व्योम __iomem *)&Ser2UTCR0;
		sa1100_ports[idx].port.mapbase = _Ser2UTCR0;
		sa1100_ports[idx].port.irq     = IRQ_Ser2ICP;
		sa1100_ports[idx].port.flags   = UPF_BOOT_AUTOCONF;
		अवरोध;

	हाल 3:
		sa1100_ports[idx].port.membase = (व्योम __iomem *)&Ser3UTCR0;
		sa1100_ports[idx].port.mapbase = _Ser3UTCR0;
		sa1100_ports[idx].port.irq     = IRQ_Ser3UART;
		sa1100_ports[idx].port.flags   = UPF_BOOT_AUTOCONF;
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR "%s: bad port number %d\n", __func__, port);
	पूर्ण
पूर्ण


#अगर_घोषित CONFIG_SERIAL_SA1100_CONSOLE
अटल व्योम sa1100_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा sa1100_port *sport =
		container_of(port, काष्ठा sa1100_port, port);

	जबतक (!(UART_GET_UTSR1(sport) & UTSR1_TNF))
		barrier();
	UART_PUT_CHAR(sport, ch);
पूर्ण

/*
 * Interrupts are disabled on entering
 */
अटल व्योम
sa1100_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा sa1100_port *sport = &sa1100_ports[co->index];
	अचिन्हित पूर्णांक old_utcr3, status;

	/*
	 *	First, save UTCR3 and then disable पूर्णांकerrupts
	 */
	old_utcr3 = UART_GET_UTCR3(sport);
	UART_PUT_UTCR3(sport, (old_utcr3 & ~(UTCR3_RIE | UTCR3_TIE)) |
				UTCR3_TXE);

	uart_console_ग_लिखो(&sport->port, s, count, sa1100_console_अक्षर_दो);

	/*
	 *	Finally, रुको क्रम transmitter to become empty
	 *	and restore UTCR3
	 */
	करो अणु
		status = UART_GET_UTSR1(sport);
	पूर्ण जबतक (status & UTSR1_TBY);
	UART_PUT_UTCR3(sport, old_utcr3);
पूर्ण

/*
 * If the port was alपढ़ोy initialised (eg, by a boot loader),
 * try to determine the current setup.
 */
अटल व्योम __init
sa1100_console_get_options(काष्ठा sa1100_port *sport, पूर्णांक *baud,
			   पूर्णांक *parity, पूर्णांक *bits)
अणु
	अचिन्हित पूर्णांक utcr3;

	utcr3 = UART_GET_UTCR3(sport) & (UTCR3_RXE | UTCR3_TXE);
	अगर (utcr3 == (UTCR3_RXE | UTCR3_TXE)) अणु
		/* ok, the port was enabled */
		अचिन्हित पूर्णांक utcr0, quot;

		utcr0 = UART_GET_UTCR0(sport);

		*parity = 'n';
		अगर (utcr0 & UTCR0_PE) अणु
			अगर (utcr0 & UTCR0_OES)
				*parity = 'e';
			अन्यथा
				*parity = 'o';
		पूर्ण

		अगर (utcr0 & UTCR0_DSS)
			*bits = 8;
		अन्यथा
			*bits = 7;

		quot = UART_GET_UTCR2(sport) | UART_GET_UTCR1(sport) << 8;
		quot &= 0xfff;
		*baud = sport->port.uartclk / (16 * (quot + 1));
	पूर्ण
पूर्ण

अटल पूर्णांक __init
sa1100_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा sa1100_port *sport;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	/*
	 * Check whether an invalid uart number has been specअगरied, and
	 * अगर so, search क्रम the first available port that करोes have
	 * console support.
	 */
	अगर (co->index == -1 || co->index >= NR_PORTS)
		co->index = 0;
	sport = &sa1100_ports[co->index];

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	अन्यथा
		sa1100_console_get_options(sport, &baud, &parity, &bits);

	वापस uart_set_options(&sport->port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver sa1100_reg;
अटल काष्ठा console sa1100_console = अणु
	.name		= "ttySA",
	.ग_लिखो		= sa1100_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= sa1100_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &sa1100_reg,
पूर्ण;

अटल पूर्णांक __init sa1100_rs_console_init(व्योम)
अणु
	sa1100_init_ports();
	रेजिस्टर_console(&sa1100_console);
	वापस 0;
पूर्ण
console_initcall(sa1100_rs_console_init);

#घोषणा SA1100_CONSOLE	&sa1100_console
#अन्यथा
#घोषणा SA1100_CONSOLE	शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver sa1100_reg = अणु
	.owner			= THIS_MODULE,
	.driver_name		= "ttySA",
	.dev_name		= "ttySA",
	.major			= SERIAL_SA1100_MAJOR,
	.minor			= MINOR_START,
	.nr			= NR_PORTS,
	.cons			= SA1100_CONSOLE,
पूर्ण;

अटल पूर्णांक sa1100_serial_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा sa1100_port *sport = platक्रमm_get_drvdata(dev);

	अगर (sport)
		uart_suspend_port(&sa1100_reg, &sport->port);

	वापस 0;
पूर्ण

अटल पूर्णांक sa1100_serial_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा sa1100_port *sport = platक्रमm_get_drvdata(dev);

	अगर (sport)
		uart_resume_port(&sa1100_reg, &sport->port);

	वापस 0;
पूर्ण

अटल पूर्णांक sa1100_serial_add_one_port(काष्ठा sa1100_port *sport, काष्ठा platक्रमm_device *dev)
अणु
	sport->port.dev = &dev->dev;
	sport->port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_SA1100_CONSOLE);

	// mctrl_gpio_init() requires that the GPIO driver supports पूर्णांकerrupts,
	// but we need to support GPIO drivers क्रम hardware that has no such
	// पूर्णांकerrupts.  Use mctrl_gpio_init_noस्वतः() instead.
	sport->gpios = mctrl_gpio_init_noस्वतः(sport->port.dev, 0);
	अगर (IS_ERR(sport->gpios)) अणु
		पूर्णांक err = PTR_ERR(sport->gpios);

		dev_err(sport->port.dev, "failed to get mctrl gpios: %d\n",
			err);

		अगर (err == -EPROBE_DEFER)
			वापस err;

		sport->gpios = शून्य;
	पूर्ण

	platक्रमm_set_drvdata(dev, sport);

	वापस uart_add_one_port(&sa1100_reg, &sport->port);
पूर्ण

अटल पूर्णांक sa1100_serial_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा resource *res;
	पूर्णांक i;

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EINVAL;

	क्रम (i = 0; i < NR_PORTS; i++)
		अगर (sa1100_ports[i].port.mapbase == res->start)
			अवरोध;
	अगर (i == NR_PORTS)
		वापस -ENODEV;

	sa1100_serial_add_one_port(&sa1100_ports[i], dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sa1100_serial_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sa1100_port *sport = platक्रमm_get_drvdata(pdev);

	अगर (sport)
		uart_हटाओ_one_port(&sa1100_reg, &sport->port);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sa11x0_serial_driver = अणु
	.probe		= sa1100_serial_probe,
	.हटाओ		= sa1100_serial_हटाओ,
	.suspend	= sa1100_serial_suspend,
	.resume		= sa1100_serial_resume,
	.driver		= अणु
		.name	= "sa11x0-uart",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sa1100_serial_init(व्योम)
अणु
	पूर्णांक ret;

	prपूर्णांकk(KERN_INFO "Serial: SA11x0 driver\n");

	sa1100_init_ports();

	ret = uart_रेजिस्टर_driver(&sa1100_reg);
	अगर (ret == 0) अणु
		ret = platक्रमm_driver_रेजिस्टर(&sa11x0_serial_driver);
		अगर (ret)
			uart_unरेजिस्टर_driver(&sa1100_reg);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास sa1100_serial_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sa11x0_serial_driver);
	uart_unरेजिस्टर_driver(&sa1100_reg);
पूर्ण

module_init(sa1100_serial_init);
module_निकास(sa1100_serial_निकास);

MODULE_AUTHOR("Deep Blue Solutions Ltd");
MODULE_DESCRIPTION("SA1100 generic serial port driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CHARDEV_MAJOR(SERIAL_SA1100_MAJOR);
MODULE_ALIAS("platform:sa11x0-uart");
