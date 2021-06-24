<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * altera_uart.c -- Altera UART driver
 *
 * Based on mcf.c -- Freescale ColdFire UART driver
 *
 * (C) Copyright 2003-2007, Greg Ungerer <gerg@snapgear.com>
 * (C) Copyright 2008, Thomas Chou <thomas@wytron.com.tw>
 * (C) Copyright 2010, Tobias Klauser <tklauser@distanz.ch>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/console.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/पन.स>
#समावेश <linux/altera_uart.h>

#घोषणा DRV_NAME "altera_uart"
#घोषणा SERIAL_ALTERA_MAJOR 204
#घोषणा SERIAL_ALTERA_MINOR 213

/*
 * Altera UART रेजिस्टर definitions according to the Nios UART datasheet:
 * http://www.altera.com/literature/ds/ds_nios_uart.pdf
 */

#घोषणा ALTERA_UART_SIZE		32

#घोषणा ALTERA_UART_RXDATA_REG		0
#घोषणा ALTERA_UART_TXDATA_REG		4
#घोषणा ALTERA_UART_STATUS_REG		8
#घोषणा ALTERA_UART_CONTROL_REG		12
#घोषणा ALTERA_UART_DIVISOR_REG		16
#घोषणा ALTERA_UART_EOP_REG		20

#घोषणा ALTERA_UART_STATUS_PE_MSK	0x0001	/* parity error */
#घोषणा ALTERA_UART_STATUS_FE_MSK	0x0002	/* framing error */
#घोषणा ALTERA_UART_STATUS_BRK_MSK	0x0004	/* अवरोध */
#घोषणा ALTERA_UART_STATUS_ROE_MSK	0x0008	/* RX overrun error */
#घोषणा ALTERA_UART_STATUS_TOE_MSK	0x0010	/* TX overrun error */
#घोषणा ALTERA_UART_STATUS_TMT_MSK	0x0020	/* TX shअगरt रेजिस्टर state */
#घोषणा ALTERA_UART_STATUS_TRDY_MSK	0x0040	/* TX पढ़ोy */
#घोषणा ALTERA_UART_STATUS_RRDY_MSK	0x0080	/* RX पढ़ोy */
#घोषणा ALTERA_UART_STATUS_E_MSK	0x0100	/* exception condition */
#घोषणा ALTERA_UART_STATUS_DCTS_MSK	0x0400	/* CTS logic-level change */
#घोषणा ALTERA_UART_STATUS_CTS_MSK	0x0800	/* CTS logic state */
#घोषणा ALTERA_UART_STATUS_EOP_MSK	0x1000	/* EOP written/पढ़ो */

						/* Enable पूर्णांकerrupt on... */
#घोषणा ALTERA_UART_CONTROL_PE_MSK	0x0001	/* ...parity error */
#घोषणा ALTERA_UART_CONTROL_FE_MSK	0x0002	/* ...framing error */
#घोषणा ALTERA_UART_CONTROL_BRK_MSK	0x0004	/* ...अवरोध */
#घोषणा ALTERA_UART_CONTROL_ROE_MSK	0x0008	/* ...RX overrun */
#घोषणा ALTERA_UART_CONTROL_TOE_MSK	0x0010	/* ...TX overrun */
#घोषणा ALTERA_UART_CONTROL_TMT_MSK	0x0020	/* ...TX shअगरt रेजिस्टर empty */
#घोषणा ALTERA_UART_CONTROL_TRDY_MSK	0x0040	/* ...TX पढ़ोy */
#घोषणा ALTERA_UART_CONTROL_RRDY_MSK	0x0080	/* ...RX पढ़ोy */
#घोषणा ALTERA_UART_CONTROL_E_MSK	0x0100	/* ...exception*/

#घोषणा ALTERA_UART_CONTROL_TRBK_MSK	0x0200	/* TX अवरोध */
#घोषणा ALTERA_UART_CONTROL_DCTS_MSK	0x0400	/* Interrupt on CTS change */
#घोषणा ALTERA_UART_CONTROL_RTS_MSK	0x0800	/* RTS संकेत */
#घोषणा ALTERA_UART_CONTROL_EOP_MSK	0x1000	/* Interrupt on EOP */

/*
 * Local per-uart काष्ठाure.
 */
काष्ठा altera_uart अणु
	काष्ठा uart_port port;
	काष्ठा समयr_list पंचांगr;
	अचिन्हित पूर्णांक sigs;	/* Local copy of line sigs */
	अचिन्हित लघु imr;	/* Local IMR mirror */
पूर्ण;

अटल u32 altera_uart_पढ़ोl(काष्ठा uart_port *port, पूर्णांक reg)
अणु
	वापस पढ़ोl(port->membase + (reg << port->regshअगरt));
पूर्ण

अटल व्योम altera_uart_ग_लिखोl(काष्ठा uart_port *port, u32 dat, पूर्णांक reg)
अणु
	ग_लिखोl(dat, port->membase + (reg << port->regshअगरt));
पूर्ण

अटल अचिन्हित पूर्णांक altera_uart_tx_empty(काष्ठा uart_port *port)
अणु
	वापस (altera_uart_पढ़ोl(port, ALTERA_UART_STATUS_REG) &
		ALTERA_UART_STATUS_TMT_MSK) ? TIOCSER_TEMT : 0;
पूर्ण

अटल अचिन्हित पूर्णांक altera_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा altera_uart *pp = container_of(port, काष्ठा altera_uart, port);
	अचिन्हित पूर्णांक sigs;

	sigs = (altera_uart_पढ़ोl(port, ALTERA_UART_STATUS_REG) &
	     ALTERA_UART_STATUS_CTS_MSK) ? TIOCM_CTS : 0;
	sigs |= (pp->sigs & TIOCM_RTS);

	वापस sigs;
पूर्ण

अटल व्योम altera_uart_update_ctrl_reg(काष्ठा altera_uart *pp)
अणु
	अचिन्हित लघु imr = pp->imr;

	/*
	 * If the device करोesn't have an irq, ensure that the irq bits are
	 * masked out to keep the irq line inactive.
	 */
	अगर (!pp->port.irq)
		imr &= ALTERA_UART_CONTROL_TRBK_MSK | ALTERA_UART_CONTROL_RTS_MSK;

	altera_uart_ग_लिखोl(&pp->port, imr, ALTERA_UART_CONTROL_REG);
पूर्ण

अटल व्योम altera_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक sigs)
अणु
	काष्ठा altera_uart *pp = container_of(port, काष्ठा altera_uart, port);

	pp->sigs = sigs;
	अगर (sigs & TIOCM_RTS)
		pp->imr |= ALTERA_UART_CONTROL_RTS_MSK;
	अन्यथा
		pp->imr &= ~ALTERA_UART_CONTROL_RTS_MSK;
	altera_uart_update_ctrl_reg(pp);
पूर्ण

अटल व्योम altera_uart_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा altera_uart *pp = container_of(port, काष्ठा altera_uart, port);

	pp->imr |= ALTERA_UART_CONTROL_TRDY_MSK;
	altera_uart_update_ctrl_reg(pp);
पूर्ण

अटल व्योम altera_uart_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा altera_uart *pp = container_of(port, काष्ठा altera_uart, port);

	pp->imr &= ~ALTERA_UART_CONTROL_TRDY_MSK;
	altera_uart_update_ctrl_reg(pp);
पूर्ण

अटल व्योम altera_uart_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा altera_uart *pp = container_of(port, काष्ठा altera_uart, port);

	pp->imr &= ~ALTERA_UART_CONTROL_RRDY_MSK;
	altera_uart_update_ctrl_reg(pp);
पूर्ण

अटल व्योम altera_uart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा altera_uart *pp = container_of(port, काष्ठा altera_uart, port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	अगर (अवरोध_state == -1)
		pp->imr |= ALTERA_UART_CONTROL_TRBK_MSK;
	अन्यथा
		pp->imr &= ~ALTERA_UART_CONTROL_TRBK_MSK;
	altera_uart_update_ctrl_reg(pp);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम altera_uart_set_termios(काष्ठा uart_port *port,
				    काष्ठा ktermios *termios,
				    काष्ठा ktermios *old)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, baudclk;

	baud = uart_get_baud_rate(port, termios, old, 0, 4000000);
	baudclk = port->uartclk / baud;

	अगर (old)
		tty_termios_copy_hw(termios, old);
	tty_termios_encode_baud_rate(termios, baud, baud);

	spin_lock_irqsave(&port->lock, flags);
	uart_update_समयout(port, termios->c_cflag, baud);
	altera_uart_ग_लिखोl(port, baudclk, ALTERA_UART_DIVISOR_REG);
	spin_unlock_irqrestore(&port->lock, flags);

	/*
	 * FIXME: port->पढ़ो_status_mask and port->ignore_status_mask
	 * need to be initialized based on termios settings क्रम
	 * INPCK, IGNBRK, IGNPAR, PARMRK, BRKINT
	 */
पूर्ण

अटल व्योम altera_uart_rx_अक्षरs(काष्ठा altera_uart *pp)
अणु
	काष्ठा uart_port *port = &pp->port;
	अचिन्हित अक्षर ch, flag;
	अचिन्हित लघु status;

	जबतक ((status = altera_uart_पढ़ोl(port, ALTERA_UART_STATUS_REG)) &
	       ALTERA_UART_STATUS_RRDY_MSK) अणु
		ch = altera_uart_पढ़ोl(port, ALTERA_UART_RXDATA_REG);
		flag = TTY_NORMAL;
		port->icount.rx++;

		अगर (status & ALTERA_UART_STATUS_E_MSK) अणु
			altera_uart_ग_लिखोl(port, status,
					   ALTERA_UART_STATUS_REG);

			अगर (status & ALTERA_UART_STATUS_BRK_MSK) अणु
				port->icount.brk++;
				अगर (uart_handle_अवरोध(port))
					जारी;
			पूर्ण अन्यथा अगर (status & ALTERA_UART_STATUS_PE_MSK) अणु
				port->icount.parity++;
			पूर्ण अन्यथा अगर (status & ALTERA_UART_STATUS_ROE_MSK) अणु
				port->icount.overrun++;
			पूर्ण अन्यथा अगर (status & ALTERA_UART_STATUS_FE_MSK) अणु
				port->icount.frame++;
			पूर्ण

			status &= port->पढ़ो_status_mask;

			अगर (status & ALTERA_UART_STATUS_BRK_MSK)
				flag = TTY_BREAK;
			अन्यथा अगर (status & ALTERA_UART_STATUS_PE_MSK)
				flag = TTY_PARITY;
			अन्यथा अगर (status & ALTERA_UART_STATUS_FE_MSK)
				flag = TTY_FRAME;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(port, ch))
			जारी;
		uart_insert_अक्षर(port, status, ALTERA_UART_STATUS_ROE_MSK, ch,
				 flag);
	पूर्ण

	tty_flip_buffer_push(&port->state->port);
पूर्ण

अटल व्योम altera_uart_tx_अक्षरs(काष्ठा altera_uart *pp)
अणु
	काष्ठा uart_port *port = &pp->port;
	काष्ठा circ_buf *xmit = &port->state->xmit;

	अगर (port->x_अक्षर) अणु
		/* Send special अक्षर - probably flow control */
		altera_uart_ग_लिखोl(port, port->x_अक्षर, ALTERA_UART_TXDATA_REG);
		port->x_अक्षर = 0;
		port->icount.tx++;
		वापस;
	पूर्ण

	जबतक (altera_uart_पढ़ोl(port, ALTERA_UART_STATUS_REG) &
	       ALTERA_UART_STATUS_TRDY_MSK) अणु
		अगर (xmit->head == xmit->tail)
			अवरोध;
		altera_uart_ग_लिखोl(port, xmit->buf[xmit->tail],
		       ALTERA_UART_TXDATA_REG);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (xmit->head == xmit->tail) अणु
		pp->imr &= ~ALTERA_UART_CONTROL_TRDY_MSK;
		altera_uart_update_ctrl_reg(pp);
	पूर्ण
पूर्ण

अटल irqवापस_t altera_uart_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा uart_port *port = data;
	काष्ठा altera_uart *pp = container_of(port, काष्ठा altera_uart, port);
	अचिन्हित पूर्णांक isr;

	isr = altera_uart_पढ़ोl(port, ALTERA_UART_STATUS_REG) & pp->imr;

	spin_lock(&port->lock);
	अगर (isr & ALTERA_UART_STATUS_RRDY_MSK)
		altera_uart_rx_अक्षरs(pp);
	अगर (isr & ALTERA_UART_STATUS_TRDY_MSK)
		altera_uart_tx_अक्षरs(pp);
	spin_unlock(&port->lock);

	वापस IRQ_RETVAL(isr);
पूर्ण

अटल व्योम altera_uart_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा altera_uart *pp = from_समयr(pp, t, पंचांगr);
	काष्ठा uart_port *port = &pp->port;

	altera_uart_पूर्णांकerrupt(0, port);
	mod_समयr(&pp->पंचांगr, jअगरfies + uart_poll_समयout(port));
पूर्ण

अटल व्योम altera_uart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	port->type = PORT_ALTERA_UART;

	/* Clear mask, so no surprise पूर्णांकerrupts. */
	altera_uart_ग_लिखोl(port, 0, ALTERA_UART_CONTROL_REG);
	/* Clear status रेजिस्टर */
	altera_uart_ग_लिखोl(port, 0, ALTERA_UART_STATUS_REG);
पूर्ण

अटल पूर्णांक altera_uart_startup(काष्ठा uart_port *port)
अणु
	काष्ठा altera_uart *pp = container_of(port, काष्ठा altera_uart, port);
	अचिन्हित दीर्घ flags;

	अगर (!port->irq) अणु
		समयr_setup(&pp->पंचांगr, altera_uart_समयr, 0);
		mod_समयr(&pp->पंचांगr, jअगरfies + uart_poll_समयout(port));
	पूर्ण अन्यथा अणु
		पूर्णांक ret;

		ret = request_irq(port->irq, altera_uart_पूर्णांकerrupt, 0,
				DRV_NAME, port);
		अगर (ret) अणु
			pr_err(DRV_NAME ": unable to attach Altera UART %d "
			       "interrupt vector=%d\n", port->line, port->irq);
			वापस ret;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&port->lock, flags);

	/* Enable RX पूर्णांकerrupts now */
	pp->imr = ALTERA_UART_CONTROL_RRDY_MSK;
	altera_uart_update_ctrl_reg(pp);

	spin_unlock_irqrestore(&port->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम altera_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा altera_uart *pp = container_of(port, काष्ठा altera_uart, port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	/* Disable all पूर्णांकerrupts now */
	pp->imr = 0;
	altera_uart_update_ctrl_reg(pp);

	spin_unlock_irqrestore(&port->lock, flags);

	अगर (port->irq)
		मुक्त_irq(port->irq, port);
	अन्यथा
		del_समयr_sync(&pp->पंचांगr);
पूर्ण

अटल स्थिर अक्षर *altera_uart_type(काष्ठा uart_port *port)
अणु
	वापस (port->type == PORT_ALTERA_UART) ? "Altera UART" : शून्य;
पूर्ण

अटल पूर्णांक altera_uart_request_port(काष्ठा uart_port *port)
अणु
	/* UARTs always present */
	वापस 0;
पूर्ण

अटल व्योम altera_uart_release_port(काष्ठा uart_port *port)
अणु
	/* Nothing to release... */
पूर्ण

अटल पूर्णांक altera_uart_verअगरy_port(काष्ठा uart_port *port,
				   काष्ठा serial_काष्ठा *ser)
अणु
	अगर ((ser->type != PORT_UNKNOWN) && (ser->type != PORT_ALTERA_UART))
		वापस -EINVAL;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
अटल पूर्णांक altera_uart_poll_get_अक्षर(काष्ठा uart_port *port)
अणु
	जबतक (!(altera_uart_पढ़ोl(port, ALTERA_UART_STATUS_REG) &
		 ALTERA_UART_STATUS_RRDY_MSK))
		cpu_relax();

	वापस altera_uart_पढ़ोl(port, ALTERA_UART_RXDATA_REG);
पूर्ण

अटल व्योम altera_uart_poll_put_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर c)
अणु
	जबतक (!(altera_uart_पढ़ोl(port, ALTERA_UART_STATUS_REG) &
		 ALTERA_UART_STATUS_TRDY_MSK))
		cpu_relax();

	altera_uart_ग_लिखोl(port, c, ALTERA_UART_TXDATA_REG);
पूर्ण
#पूर्ण_अगर

/*
 *	Define the basic serial functions we support.
 */
अटल स्थिर काष्ठा uart_ops altera_uart_ops = अणु
	.tx_empty	= altera_uart_tx_empty,
	.get_mctrl	= altera_uart_get_mctrl,
	.set_mctrl	= altera_uart_set_mctrl,
	.start_tx	= altera_uart_start_tx,
	.stop_tx	= altera_uart_stop_tx,
	.stop_rx	= altera_uart_stop_rx,
	.अवरोध_ctl	= altera_uart_अवरोध_ctl,
	.startup	= altera_uart_startup,
	.shutकरोwn	= altera_uart_shutकरोwn,
	.set_termios	= altera_uart_set_termios,
	.type		= altera_uart_type,
	.request_port	= altera_uart_request_port,
	.release_port	= altera_uart_release_port,
	.config_port	= altera_uart_config_port,
	.verअगरy_port	= altera_uart_verअगरy_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर	= altera_uart_poll_get_अक्षर,
	.poll_put_अक्षर	= altera_uart_poll_put_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा altera_uart altera_uart_ports[CONFIG_SERIAL_ALTERA_UART_MAXPORTS];

#अगर defined(CONFIG_SERIAL_ALTERA_UART_CONSOLE)

अटल व्योम altera_uart_console_अ_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	जबतक (!(altera_uart_पढ़ोl(port, ALTERA_UART_STATUS_REG) &
		 ALTERA_UART_STATUS_TRDY_MSK))
		cpu_relax();

	altera_uart_ग_लिखोl(port, c, ALTERA_UART_TXDATA_REG);
पूर्ण

अटल व्योम altera_uart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				      अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_port *port = &(altera_uart_ports + co->index)->port;

	uart_console_ग_लिखो(port, s, count, altera_uart_console_अ_दो);
पूर्ण

अटल पूर्णांक __init altera_uart_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port;
	पूर्णांक baud = CONFIG_SERIAL_ALTERA_UART_BAUDRATE;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (co->index < 0 || co->index >= CONFIG_SERIAL_ALTERA_UART_MAXPORTS)
		वापस -EINVAL;
	port = &altera_uart_ports[co->index].port;
	अगर (!port->membase)
		वापस -ENODEV;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver altera_uart_driver;

अटल काष्ठा console altera_uart_console = अणु
	.name	= "ttyAL",
	.ग_लिखो	= altera_uart_console_ग_लिखो,
	.device	= uart_console_device,
	.setup	= altera_uart_console_setup,
	.flags	= CON_PRINTBUFFER,
	.index	= -1,
	.data	= &altera_uart_driver,
पूर्ण;

अटल पूर्णांक __init altera_uart_console_init(व्योम)
अणु
	रेजिस्टर_console(&altera_uart_console);
	वापस 0;
पूर्ण

console_initcall(altera_uart_console_init);

#घोषणा	ALTERA_UART_CONSOLE	(&altera_uart_console)

अटल व्योम altera_uart_earlycon_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				       अचिन्हित पूर्णांक count)
अणु
	काष्ठा earlycon_device *dev = co->data;

	uart_console_ग_लिखो(&dev->port, s, count, altera_uart_console_अ_दो);
पूर्ण

अटल पूर्णांक __init altera_uart_earlycon_setup(काष्ठा earlycon_device *dev,
					     स्थिर अक्षर *options)
अणु
	काष्ठा uart_port *port = &dev->port;

	अगर (!port->membase)
		वापस -ENODEV;

	/* Enable RX पूर्णांकerrupts now */
	altera_uart_ग_लिखोl(port, ALTERA_UART_CONTROL_RRDY_MSK,
			   ALTERA_UART_CONTROL_REG);

	अगर (dev->baud) अणु
		अचिन्हित पूर्णांक baudclk = port->uartclk / dev->baud;

		altera_uart_ग_लिखोl(port, baudclk, ALTERA_UART_DIVISOR_REG);
	पूर्ण

	dev->con->ग_लिखो = altera_uart_earlycon_ग_लिखो;
	वापस 0;
पूर्ण

OF_EARLYCON_DECLARE(uart, "altr,uart-1.0", altera_uart_earlycon_setup);

#अन्यथा

#घोषणा	ALTERA_UART_CONSOLE	शून्य

#पूर्ण_अगर /* CONFIG_SERIAL_ALTERA_UART_CONSOLE */

/*
 *	Define the altera_uart UART driver काष्ठाure.
 */
अटल काष्ठा uart_driver altera_uart_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= DRV_NAME,
	.dev_name	= "ttyAL",
	.major		= SERIAL_ALTERA_MAJOR,
	.minor		= SERIAL_ALTERA_MINOR,
	.nr		= CONFIG_SERIAL_ALTERA_UART_MAXPORTS,
	.cons		= ALTERA_UART_CONSOLE,
पूर्ण;

अटल पूर्णांक altera_uart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा altera_uart_platक्रमm_uart *platp = dev_get_platdata(&pdev->dev);
	काष्ठा uart_port *port;
	काष्ठा resource *res_mem;
	काष्ठा resource *res_irq;
	पूर्णांक i = pdev->id;
	पूर्णांक ret;

	/* अगर id is -1 scan क्रम a मुक्त id and use that one */
	अगर (i == -1) अणु
		क्रम (i = 0; i < CONFIG_SERIAL_ALTERA_UART_MAXPORTS; i++)
			अगर (altera_uart_ports[i].port.mapbase == 0)
				अवरोध;
	पूर्ण

	अगर (i < 0 || i >= CONFIG_SERIAL_ALTERA_UART_MAXPORTS)
		वापस -EINVAL;

	port = &altera_uart_ports[i].port;

	res_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res_mem)
		port->mapbase = res_mem->start;
	अन्यथा अगर (platp)
		port->mapbase = platp->mapbase;
	अन्यथा
		वापस -EINVAL;

	res_irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (res_irq)
		port->irq = res_irq->start;
	अन्यथा अगर (platp)
		port->irq = platp->irq;

	/* Check platक्रमm data first so we can override device node data */
	अगर (platp)
		port->uartclk = platp->uartclk;
	अन्यथा अणु
		ret = of_property_पढ़ो_u32(pdev->dev.of_node, "clock-frequency",
					   &port->uartclk);
		अगर (ret)
			वापस ret;
	पूर्ण

	port->membase = ioremap(port->mapbase, ALTERA_UART_SIZE);
	अगर (!port->membase)
		वापस -ENOMEM;

	अगर (platp)
		port->regshअगरt = platp->bus_shअगरt;
	अन्यथा
		port->regshअगरt = 0;

	port->line = i;
	port->type = PORT_ALTERA_UART;
	port->iotype = SERIAL_IO_MEM;
	port->ops = &altera_uart_ops;
	port->flags = UPF_BOOT_AUTOCONF;
	port->dev = &pdev->dev;

	platक्रमm_set_drvdata(pdev, port);

	uart_add_one_port(&altera_uart_driver, port);

	वापस 0;
पूर्ण

अटल पूर्णांक altera_uart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port = platक्रमm_get_drvdata(pdev);

	अगर (port) अणु
		uart_हटाओ_one_port(&altera_uart_driver, port);
		port->mapbase = 0;
		iounmap(port->membase);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id altera_uart_match[] = अणु
	अणु .compatible = "ALTR,uart-1.0", पूर्ण,
	अणु .compatible = "altr,uart-1.0", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, altera_uart_match);
#पूर्ण_अगर /* CONFIG_OF */

अटल काष्ठा platक्रमm_driver altera_uart_platक्रमm_driver = अणु
	.probe	= altera_uart_probe,
	.हटाओ	= altera_uart_हटाओ,
	.driver	= अणु
		.name		= DRV_NAME,
		.of_match_table	= of_match_ptr(altera_uart_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init altera_uart_init(व्योम)
अणु
	पूर्णांक rc;

	rc = uart_रेजिस्टर_driver(&altera_uart_driver);
	अगर (rc)
		वापस rc;
	rc = platक्रमm_driver_रेजिस्टर(&altera_uart_platक्रमm_driver);
	अगर (rc)
		uart_unरेजिस्टर_driver(&altera_uart_driver);
	वापस rc;
पूर्ण

अटल व्योम __निकास altera_uart_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&altera_uart_platक्रमm_driver);
	uart_unरेजिस्टर_driver(&altera_uart_driver);
पूर्ण

module_init(altera_uart_init);
module_निकास(altera_uart_निकास);

MODULE_DESCRIPTION("Altera UART driver");
MODULE_AUTHOR("Thomas Chou <thomas@wytron.com.tw>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_ALIAS_CHARDEV_MAJOR(SERIAL_ALTERA_MAJOR);
