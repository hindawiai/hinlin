<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/****************************************************************************/

/*
 *	mcf.c -- Freescale ColdFire UART driver
 *
 *	(C) Copyright 2003-2007, Greg Ungerer <gerg@uclinux.org>
 */

/****************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/console.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/mcfuart.h>
#समावेश <यंत्र/nettel.h>

/****************************************************************************/

/*
 *	Some boards implement the DTR/DCD lines using GPIO lines, most
 *	करोn't. Dummy out the access macros for those that don't. Those
 *	that करो should define these macros somewhere in there board
 *	specअगरic inlude files.
 */
#अगर !defined(mcf_getppdcd)
#घोषणा	mcf_getppdcd(p)		(1)
#पूर्ण_अगर
#अगर !defined(mcf_getppdtr)
#घोषणा	mcf_getppdtr(p)		(1)
#पूर्ण_अगर
#अगर !defined(mcf_setppdtr)
#घोषणा	mcf_setppdtr(p, v)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/****************************************************************************/

/*
 *	Local per-uart काष्ठाure.
 */
काष्ठा mcf_uart अणु
	काष्ठा uart_port	port;
	अचिन्हित पूर्णांक		sigs;		/* Local copy of line sigs */
	अचिन्हित अक्षर		imr;		/* Local IMR mirror */
पूर्ण;

/****************************************************************************/

अटल अचिन्हित पूर्णांक mcf_tx_empty(काष्ठा uart_port *port)
अणु
	वापस (पढ़ोb(port->membase + MCFUART_USR) & MCFUART_USR_TXEMPTY) ?
		TIOCSER_TEMT : 0;
पूर्ण

/****************************************************************************/

अटल अचिन्हित पूर्णांक mcf_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा mcf_uart *pp = container_of(port, काष्ठा mcf_uart, port);
	अचिन्हित पूर्णांक sigs;

	sigs = (पढ़ोb(port->membase + MCFUART_UIPR) & MCFUART_UIPR_CTS) ?
		0 : TIOCM_CTS;
	sigs |= (pp->sigs & TIOCM_RTS);
	sigs |= (mcf_getppdcd(port->line) ? TIOCM_CD : 0);
	sigs |= (mcf_getppdtr(port->line) ? TIOCM_DTR : 0);

	वापस sigs;
पूर्ण

/****************************************************************************/

अटल व्योम mcf_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक sigs)
अणु
	काष्ठा mcf_uart *pp = container_of(port, काष्ठा mcf_uart, port);

	pp->sigs = sigs;
	mcf_setppdtr(port->line, (sigs & TIOCM_DTR));
	अगर (sigs & TIOCM_RTS)
		ग_लिखोb(MCFUART_UOP_RTS, port->membase + MCFUART_UOP1);
	अन्यथा
		ग_लिखोb(MCFUART_UOP_RTS, port->membase + MCFUART_UOP0);
पूर्ण

/****************************************************************************/

अटल व्योम mcf_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा mcf_uart *pp = container_of(port, काष्ठा mcf_uart, port);

	अगर (port->rs485.flags & SER_RS485_ENABLED) अणु
		/* Enable Transmitter */
		ग_लिखोb(MCFUART_UCR_TXENABLE, port->membase + MCFUART_UCR);
		/* Manually निश्चित RTS */
		ग_लिखोb(MCFUART_UOP_RTS, port->membase + MCFUART_UOP1);
	पूर्ण
	pp->imr |= MCFUART_UIR_TXREADY;
	ग_लिखोb(pp->imr, port->membase + MCFUART_UIMR);
पूर्ण

/****************************************************************************/

अटल व्योम mcf_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा mcf_uart *pp = container_of(port, काष्ठा mcf_uart, port);

	pp->imr &= ~MCFUART_UIR_TXREADY;
	ग_लिखोb(pp->imr, port->membase + MCFUART_UIMR);
पूर्ण

/****************************************************************************/

अटल व्योम mcf_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा mcf_uart *pp = container_of(port, काष्ठा mcf_uart, port);

	pp->imr &= ~MCFUART_UIR_RXREADY;
	ग_लिखोb(pp->imr, port->membase + MCFUART_UIMR);
पूर्ण

/****************************************************************************/

अटल व्योम mcf_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	अगर (अवरोध_state == -1)
		ग_लिखोb(MCFUART_UCR_CMDBREAKSTART, port->membase + MCFUART_UCR);
	अन्यथा
		ग_लिखोb(MCFUART_UCR_CMDBREAKSTOP, port->membase + MCFUART_UCR);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/****************************************************************************/

अटल पूर्णांक mcf_startup(काष्ठा uart_port *port)
अणु
	काष्ठा mcf_uart *pp = container_of(port, काष्ठा mcf_uart, port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	/* Reset UART, get it पूर्णांकo known state... */
	ग_लिखोb(MCFUART_UCR_CMDRESETRX, port->membase + MCFUART_UCR);
	ग_लिखोb(MCFUART_UCR_CMDRESETTX, port->membase + MCFUART_UCR);

	/* Enable the UART transmitter and receiver */
	ग_लिखोb(MCFUART_UCR_RXENABLE | MCFUART_UCR_TXENABLE,
		port->membase + MCFUART_UCR);

	/* Enable RX पूर्णांकerrupts now */
	pp->imr = MCFUART_UIR_RXREADY;
	ग_लिखोb(pp->imr, port->membase + MCFUART_UIMR);

	spin_unlock_irqrestore(&port->lock, flags);

	वापस 0;
पूर्ण

/****************************************************************************/

अटल व्योम mcf_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा mcf_uart *pp = container_of(port, काष्ठा mcf_uart, port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	/* Disable all पूर्णांकerrupts now */
	pp->imr = 0;
	ग_लिखोb(pp->imr, port->membase + MCFUART_UIMR);

	/* Disable UART transmitter and receiver */
	ग_लिखोb(MCFUART_UCR_CMDRESETRX, port->membase + MCFUART_UCR);
	ग_लिखोb(MCFUART_UCR_CMDRESETTX, port->membase + MCFUART_UCR);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/****************************************************************************/

अटल व्योम mcf_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
	काष्ठा ktermios *old)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, baudclk;
#अगर defined(CONFIG_M5272)
	अचिन्हित पूर्णांक baudfr;
#पूर्ण_अगर
	अचिन्हित अक्षर mr1, mr2;

	baud = uart_get_baud_rate(port, termios, old, 0, 230400);
#अगर defined(CONFIG_M5272)
	baudclk = (MCF_BUSCLK / baud) / 32;
	baudfr = (((MCF_BUSCLK / baud) + 1) / 2) % 16;
#अन्यथा
	baudclk = ((MCF_BUSCLK / baud) + 16) / 32;
#पूर्ण_अगर

	mr1 = MCFUART_MR1_RXIRQRDY | MCFUART_MR1_RXERRCHAR;
	mr2 = 0;

	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5: mr1 |= MCFUART_MR1_CS5; अवरोध;
	हाल CS6: mr1 |= MCFUART_MR1_CS6; अवरोध;
	हाल CS7: mr1 |= MCFUART_MR1_CS7; अवरोध;
	हाल CS8:
	शेष:  mr1 |= MCFUART_MR1_CS8; अवरोध;
	पूर्ण

	अगर (termios->c_cflag & PARENB) अणु
		अगर (termios->c_cflag & CMSPAR) अणु
			अगर (termios->c_cflag & PARODD)
				mr1 |= MCFUART_MR1_PARITYMARK;
			अन्यथा
				mr1 |= MCFUART_MR1_PARITYSPACE;
		पूर्ण अन्यथा अणु
			अगर (termios->c_cflag & PARODD)
				mr1 |= MCFUART_MR1_PARITYODD;
			अन्यथा
				mr1 |= MCFUART_MR1_PARITYEVEN;
		पूर्ण
	पूर्ण अन्यथा अणु
		mr1 |= MCFUART_MR1_PARITYNONE;
	पूर्ण

	/*
	 * FIXME: port->पढ़ो_status_mask and port->ignore_status_mask
	 * need to be initialized based on termios settings क्रम
	 * INPCK, IGNBRK, IGNPAR, PARMRK, BRKINT
	 */

	अगर (termios->c_cflag & CSTOPB)
		mr2 |= MCFUART_MR2_STOP2;
	अन्यथा
		mr2 |= MCFUART_MR2_STOP1;

	अगर (termios->c_cflag & CRTSCTS) अणु
		mr1 |= MCFUART_MR1_RXRTS;
		mr2 |= MCFUART_MR2_TXCTS;
	पूर्ण

	spin_lock_irqsave(&port->lock, flags);
	अगर (port->rs485.flags & SER_RS485_ENABLED) अणु
		dev_dbg(port->dev, "Setting UART to RS485\n");
		mr2 |= MCFUART_MR2_TXRTS;
	पूर्ण

	uart_update_समयout(port, termios->c_cflag, baud);
	ग_लिखोb(MCFUART_UCR_CMDRESETRX, port->membase + MCFUART_UCR);
	ग_लिखोb(MCFUART_UCR_CMDRESETTX, port->membase + MCFUART_UCR);
	ग_लिखोb(MCFUART_UCR_CMDRESETMRPTR, port->membase + MCFUART_UCR);
	ग_लिखोb(mr1, port->membase + MCFUART_UMR);
	ग_लिखोb(mr2, port->membase + MCFUART_UMR);
	ग_लिखोb((baudclk & 0xff00) >> 8, port->membase + MCFUART_UBG1);
	ग_लिखोb((baudclk & 0xff), port->membase + MCFUART_UBG2);
#अगर defined(CONFIG_M5272)
	ग_लिखोb((baudfr & 0x0f), port->membase + MCFUART_UFPD);
#पूर्ण_अगर
	ग_लिखोb(MCFUART_UCSR_RXCLKTIMER | MCFUART_UCSR_TXCLKTIMER,
		port->membase + MCFUART_UCSR);
	ग_लिखोb(MCFUART_UCR_RXENABLE | MCFUART_UCR_TXENABLE,
		port->membase + MCFUART_UCR);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/****************************************************************************/

अटल व्योम mcf_rx_अक्षरs(काष्ठा mcf_uart *pp)
अणु
	काष्ठा uart_port *port = &pp->port;
	अचिन्हित अक्षर status, ch, flag;

	जबतक ((status = पढ़ोb(port->membase + MCFUART_USR)) & MCFUART_USR_RXREADY) अणु
		ch = पढ़ोb(port->membase + MCFUART_URB);
		flag = TTY_NORMAL;
		port->icount.rx++;

		अगर (status & MCFUART_USR_RXERR) अणु
			ग_लिखोb(MCFUART_UCR_CMDRESETERR,
				port->membase + MCFUART_UCR);

			अगर (status & MCFUART_USR_RXBREAK) अणु
				port->icount.brk++;
				अगर (uart_handle_अवरोध(port))
					जारी;
			पूर्ण अन्यथा अगर (status & MCFUART_USR_RXPARITY) अणु
				port->icount.parity++;
			पूर्ण अन्यथा अगर (status & MCFUART_USR_RXOVERRUN) अणु
				port->icount.overrun++;
			पूर्ण अन्यथा अगर (status & MCFUART_USR_RXFRAMING) अणु
				port->icount.frame++;
			पूर्ण

			status &= port->पढ़ो_status_mask;

			अगर (status & MCFUART_USR_RXBREAK)
				flag = TTY_BREAK;
			अन्यथा अगर (status & MCFUART_USR_RXPARITY)
				flag = TTY_PARITY;
			अन्यथा अगर (status & MCFUART_USR_RXFRAMING)
				flag = TTY_FRAME;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(port, ch))
			जारी;
		uart_insert_अक्षर(port, status, MCFUART_USR_RXOVERRUN, ch, flag);
	पूर्ण

	tty_flip_buffer_push(&port->state->port);
पूर्ण

/****************************************************************************/

अटल व्योम mcf_tx_अक्षरs(काष्ठा mcf_uart *pp)
अणु
	काष्ठा uart_port *port = &pp->port;
	काष्ठा circ_buf *xmit = &port->state->xmit;

	अगर (port->x_अक्षर) अणु
		/* Send special अक्षर - probably flow control */
		ग_लिखोb(port->x_अक्षर, port->membase + MCFUART_UTB);
		port->x_अक्षर = 0;
		port->icount.tx++;
		वापस;
	पूर्ण

	जबतक (पढ़ोb(port->membase + MCFUART_USR) & MCFUART_USR_TXREADY) अणु
		अगर (xmit->head == xmit->tail)
			अवरोध;
		ग_लिखोb(xmit->buf[xmit->tail], port->membase + MCFUART_UTB);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE -1);
		port->icount.tx++;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (xmit->head == xmit->tail) अणु
		pp->imr &= ~MCFUART_UIR_TXREADY;
		ग_लिखोb(pp->imr, port->membase + MCFUART_UIMR);
		/* Disable TX to negate RTS स्वतःmatically */
		अगर (port->rs485.flags & SER_RS485_ENABLED)
			ग_लिखोb(MCFUART_UCR_TXDISABLE,
				port->membase + MCFUART_UCR);
	पूर्ण
पूर्ण

/****************************************************************************/

अटल irqवापस_t mcf_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा uart_port *port = data;
	काष्ठा mcf_uart *pp = container_of(port, काष्ठा mcf_uart, port);
	अचिन्हित पूर्णांक isr;
	irqवापस_t ret = IRQ_NONE;

	isr = पढ़ोb(port->membase + MCFUART_UISR) & pp->imr;

	spin_lock(&port->lock);
	अगर (isr & MCFUART_UIR_RXREADY) अणु
		mcf_rx_अक्षरs(pp);
		ret = IRQ_HANDLED;
	पूर्ण
	अगर (isr & MCFUART_UIR_TXREADY) अणु
		mcf_tx_अक्षरs(pp);
		ret = IRQ_HANDLED;
	पूर्ण
	spin_unlock(&port->lock);

	वापस ret;
पूर्ण

/****************************************************************************/

अटल व्योम mcf_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	port->type = PORT_MCF;
	port->fअगरosize = MCFUART_TXFIFOSIZE;

	/* Clear mask, so no surprise पूर्णांकerrupts. */
	ग_लिखोb(0, port->membase + MCFUART_UIMR);

	अगर (request_irq(port->irq, mcf_पूर्णांकerrupt, 0, "UART", port))
		prपूर्णांकk(KERN_ERR "MCF: unable to attach ColdFire UART %d "
			"interrupt vector=%d\n", port->line, port->irq);
पूर्ण

/****************************************************************************/

अटल स्थिर अक्षर *mcf_type(काष्ठा uart_port *port)
अणु
	वापस (port->type == PORT_MCF) ? "ColdFire UART" : शून्य;
पूर्ण

/****************************************************************************/

अटल पूर्णांक mcf_request_port(काष्ठा uart_port *port)
अणु
	/* UARTs always present */
	वापस 0;
पूर्ण

/****************************************************************************/

अटल व्योम mcf_release_port(काष्ठा uart_port *port)
अणु
	/* Nothing to release... */
पूर्ण

/****************************************************************************/

अटल पूर्णांक mcf_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	अगर ((ser->type != PORT_UNKNOWN) && (ser->type != PORT_MCF))
		वापस -EINVAL;
	वापस 0;
पूर्ण

/****************************************************************************/

/* Enable or disable the RS485 support */
अटल पूर्णांक mcf_config_rs485(काष्ठा uart_port *port, काष्ठा serial_rs485 *rs485)
अणु
	अचिन्हित अक्षर mr1, mr2;

	/* Get mode रेजिस्टरs */
	mr1 = पढ़ोb(port->membase + MCFUART_UMR);
	mr2 = पढ़ोb(port->membase + MCFUART_UMR);
	अगर (rs485->flags & SER_RS485_ENABLED) अणु
		dev_dbg(port->dev, "Setting UART to RS485\n");
		/* Automatically negate RTS after TX completes */
		mr2 |= MCFUART_MR2_TXRTS;
	पूर्ण अन्यथा अणु
		dev_dbg(port->dev, "Setting UART to RS232\n");
		mr2 &= ~MCFUART_MR2_TXRTS;
	पूर्ण
	ग_लिखोb(mr1, port->membase + MCFUART_UMR);
	ग_लिखोb(mr2, port->membase + MCFUART_UMR);
	port->rs485 = *rs485;

	वापस 0;
पूर्ण

/****************************************************************************/

/*
 *	Define the basic serial functions we support.
 */
अटल स्थिर काष्ठा uart_ops mcf_uart_ops = अणु
	.tx_empty	= mcf_tx_empty,
	.get_mctrl	= mcf_get_mctrl,
	.set_mctrl	= mcf_set_mctrl,
	.start_tx	= mcf_start_tx,
	.stop_tx	= mcf_stop_tx,
	.stop_rx	= mcf_stop_rx,
	.अवरोध_ctl	= mcf_अवरोध_ctl,
	.startup	= mcf_startup,
	.shutकरोwn	= mcf_shutकरोwn,
	.set_termios	= mcf_set_termios,
	.type		= mcf_type,
	.request_port	= mcf_request_port,
	.release_port	= mcf_release_port,
	.config_port	= mcf_config_port,
	.verअगरy_port	= mcf_verअगरy_port,
पूर्ण;

अटल काष्ठा mcf_uart mcf_ports[4];

#घोषणा	MCF_MAXPORTS	ARRAY_SIZE(mcf_ports)

/****************************************************************************/
#अगर defined(CONFIG_SERIAL_MCF_CONSOLE)
/****************************************************************************/

पूर्णांक __init early_mcf_setup(काष्ठा mcf_platक्रमm_uart *platp)
अणु
	काष्ठा uart_port *port;
	पूर्णांक i;

	क्रम (i = 0; ((i < MCF_MAXPORTS) && (platp[i].mapbase)); i++) अणु
		port = &mcf_ports[i].port;

		port->line = i;
		port->type = PORT_MCF;
		port->mapbase = platp[i].mapbase;
		port->membase = (platp[i].membase) ? platp[i].membase :
			(अचिन्हित अक्षर __iomem *) port->mapbase;
		port->iotype = SERIAL_IO_MEM;
		port->irq = platp[i].irq;
		port->uartclk = MCF_BUSCLK;
		port->flags = UPF_BOOT_AUTOCONF;
		port->rs485_config = mcf_config_rs485;
		port->ops = &mcf_uart_ops;
	पूर्ण

	वापस 0;
पूर्ण

/****************************************************************************/

अटल व्योम mcf_console_अ_दो(काष्ठा console *co, स्थिर अक्षर c)
अणु
	काष्ठा uart_port *port = &(mcf_ports + co->index)->port;
	पूर्णांक i;

	क्रम (i = 0; (i < 0x10000); i++) अणु
		अगर (पढ़ोb(port->membase + MCFUART_USR) & MCFUART_USR_TXREADY)
			अवरोध;
	पूर्ण
	ग_लिखोb(c, port->membase + MCFUART_UTB);
	क्रम (i = 0; (i < 0x10000); i++) अणु
		अगर (पढ़ोb(port->membase + MCFUART_USR) & MCFUART_USR_TXREADY)
			अवरोध;
	पूर्ण
पूर्ण

/****************************************************************************/

अटल व्योम mcf_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	क्रम (; (count); count--, s++) अणु
		mcf_console_अ_दो(co, *s);
		अगर (*s == '\n')
			mcf_console_अ_दो(co, '\r');
	पूर्ण
पूर्ण

/****************************************************************************/

अटल पूर्णांक __init mcf_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port;
	पूर्णांक baud = CONFIG_SERIAL_MCF_BAUDRATE;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर ((co->index < 0) || (co->index >= MCF_MAXPORTS))
		co->index = 0;
	port = &mcf_ports[co->index].port;
	अगर (port->membase == 0)
		वापस -ENODEV;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

/****************************************************************************/

अटल काष्ठा uart_driver mcf_driver;

अटल काष्ठा console mcf_console = अणु
	.name		= "ttyS",
	.ग_लिखो		= mcf_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= mcf_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &mcf_driver,
पूर्ण;

अटल पूर्णांक __init mcf_console_init(व्योम)
अणु
	रेजिस्टर_console(&mcf_console);
	वापस 0;
पूर्ण

console_initcall(mcf_console_init);

#घोषणा	MCF_CONSOLE	&mcf_console

/****************************************************************************/
#अन्यथा
/****************************************************************************/

#घोषणा	MCF_CONSOLE	शून्य

/****************************************************************************/
#पूर्ण_अगर /* CONFIG_SERIAL_MCF_CONSOLE */
/****************************************************************************/

/*
 *	Define the mcf UART driver काष्ठाure.
 */
अटल काष्ठा uart_driver mcf_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "mcf",
	.dev_name	= "ttyS",
	.major		= TTY_MAJOR,
	.minor		= 64,
	.nr		= MCF_MAXPORTS,
	.cons		= MCF_CONSOLE,
पूर्ण;

/****************************************************************************/

अटल पूर्णांक mcf_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mcf_platक्रमm_uart *platp = dev_get_platdata(&pdev->dev);
	काष्ठा uart_port *port;
	पूर्णांक i;

	क्रम (i = 0; ((i < MCF_MAXPORTS) && (platp[i].mapbase)); i++) अणु
		port = &mcf_ports[i].port;

		port->line = i;
		port->type = PORT_MCF;
		port->mapbase = platp[i].mapbase;
		port->membase = (platp[i].membase) ? platp[i].membase :
			(अचिन्हित अक्षर __iomem *) platp[i].mapbase;
		port->dev = &pdev->dev;
		port->iotype = SERIAL_IO_MEM;
		port->irq = platp[i].irq;
		port->uartclk = MCF_BUSCLK;
		port->ops = &mcf_uart_ops;
		port->flags = UPF_BOOT_AUTOCONF;
		port->rs485_config = mcf_config_rs485;
		port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_MCF_CONSOLE);

		uart_add_one_port(&mcf_driver, port);
	पूर्ण

	वापस 0;
पूर्ण

/****************************************************************************/

अटल पूर्णांक mcf_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port;
	पूर्णांक i;

	क्रम (i = 0; (i < MCF_MAXPORTS); i++) अणु
		port = &mcf_ports[i].port;
		अगर (port)
			uart_हटाओ_one_port(&mcf_driver, port);
	पूर्ण

	वापस 0;
पूर्ण

/****************************************************************************/

अटल काष्ठा platक्रमm_driver mcf_platक्रमm_driver = अणु
	.probe		= mcf_probe,
	.हटाओ		= mcf_हटाओ,
	.driver		= अणु
		.name	= "mcfuart",
	पूर्ण,
पूर्ण;

/****************************************************************************/

अटल पूर्णांक __init mcf_init(व्योम)
अणु
	पूर्णांक rc;

	prपूर्णांकk("ColdFire internal UART serial driver\n");

	rc = uart_रेजिस्टर_driver(&mcf_driver);
	अगर (rc)
		वापस rc;
	rc = platक्रमm_driver_रेजिस्टर(&mcf_platक्रमm_driver);
	अगर (rc) अणु
		uart_unरेजिस्टर_driver(&mcf_driver);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

/****************************************************************************/

अटल व्योम __निकास mcf_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mcf_platक्रमm_driver);
	uart_unरेजिस्टर_driver(&mcf_driver);
पूर्ण

/****************************************************************************/

module_init(mcf_init);
module_निकास(mcf_निकास);

MODULE_AUTHOR("Greg Ungerer <gerg@uclinux.org>");
MODULE_DESCRIPTION("Freescale ColdFire UART driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mcfuart");

/****************************************************************************/
