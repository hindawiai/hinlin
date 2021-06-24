<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Socionext Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

#घोषणा USIO_NAME		"mlb-usio-uart"
#घोषणा USIO_UART_DEV_NAME	"ttyUSI"

अटल काष्ठा uart_port mlb_usio_ports[CONFIG_SERIAL_MILBEAUT_USIO_PORTS];

#घोषणा RX	0
#घोषणा TX	1
अटल पूर्णांक mlb_usio_irq[CONFIG_SERIAL_MILBEAUT_USIO_PORTS][2];

#घोषणा MLB_USIO_REG_SMR		0
#घोषणा MLB_USIO_REG_SCR		1
#घोषणा MLB_USIO_REG_ESCR		2
#घोषणा MLB_USIO_REG_SSR		3
#घोषणा MLB_USIO_REG_DR			4
#घोषणा MLB_USIO_REG_BGR		6
#घोषणा MLB_USIO_REG_FCR		12
#घोषणा MLB_USIO_REG_FBYTE		14

#घोषणा MLB_USIO_SMR_SOE		BIT(0)
#घोषणा MLB_USIO_SMR_SBL		BIT(3)
#घोषणा MLB_USIO_SCR_TXE		BIT(0)
#घोषणा MLB_USIO_SCR_RXE		BIT(1)
#घोषणा MLB_USIO_SCR_TBIE		BIT(2)
#घोषणा MLB_USIO_SCR_TIE		BIT(3)
#घोषणा MLB_USIO_SCR_RIE		BIT(4)
#घोषणा MLB_USIO_SCR_UPCL		BIT(7)
#घोषणा MLB_USIO_ESCR_L_8BIT		0
#घोषणा MLB_USIO_ESCR_L_5BIT		1
#घोषणा MLB_USIO_ESCR_L_6BIT		2
#घोषणा MLB_USIO_ESCR_L_7BIT		3
#घोषणा MLB_USIO_ESCR_P			BIT(3)
#घोषणा MLB_USIO_ESCR_PEN		BIT(4)
#घोषणा MLB_USIO_ESCR_FLWEN		BIT(7)
#घोषणा MLB_USIO_SSR_TBI		BIT(0)
#घोषणा MLB_USIO_SSR_TDRE		BIT(1)
#घोषणा MLB_USIO_SSR_RDRF		BIT(2)
#घोषणा MLB_USIO_SSR_ORE		BIT(3)
#घोषणा MLB_USIO_SSR_FRE		BIT(4)
#घोषणा MLB_USIO_SSR_PE			BIT(5)
#घोषणा MLB_USIO_SSR_REC		BIT(7)
#घोषणा MLB_USIO_SSR_BRK		BIT(8)
#घोषणा MLB_USIO_FCR_FE1		BIT(0)
#घोषणा MLB_USIO_FCR_FE2		BIT(1)
#घोषणा MLB_USIO_FCR_FCL1		BIT(2)
#घोषणा MLB_USIO_FCR_FCL2		BIT(3)
#घोषणा MLB_USIO_FCR_FSET		BIT(4)
#घोषणा MLB_USIO_FCR_FTIE		BIT(9)
#घोषणा MLB_USIO_FCR_FDRQ		BIT(10)
#घोषणा MLB_USIO_FCR_FRIIE		BIT(11)

अटल व्योम mlb_usio_stop_tx(काष्ठा uart_port *port)
अणु
	ग_लिखोw(पढ़ोw(port->membase + MLB_USIO_REG_FCR) & ~MLB_USIO_FCR_FTIE,
	       port->membase + MLB_USIO_REG_FCR);
	ग_लिखोb(पढ़ोb(port->membase + MLB_USIO_REG_SCR) & ~MLB_USIO_SCR_TBIE,
	       port->membase + MLB_USIO_REG_SCR);
पूर्ण

अटल व्योम mlb_usio_tx_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	पूर्णांक count;

	ग_लिखोw(पढ़ोw(port->membase + MLB_USIO_REG_FCR) & ~MLB_USIO_FCR_FTIE,
	       port->membase + MLB_USIO_REG_FCR);
	ग_लिखोb(पढ़ोb(port->membase + MLB_USIO_REG_SCR) &
	       ~(MLB_USIO_SCR_TIE | MLB_USIO_SCR_TBIE),
	       port->membase + MLB_USIO_REG_SCR);

	अगर (port->x_अक्षर) अणु
		ग_लिखोw(port->x_अक्षर, port->membase + MLB_USIO_REG_DR);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण
	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		mlb_usio_stop_tx(port);
		वापस;
	पूर्ण

	count = port->fअगरosize -
		(पढ़ोw(port->membase + MLB_USIO_REG_FBYTE) & 0xff);

	करो अणु
		ग_लिखोw(xmit->buf[xmit->tail], port->membase + MLB_USIO_REG_DR);

		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;

	पूर्ण जबतक (--count > 0);

	ग_लिखोw(पढ़ोw(port->membase + MLB_USIO_REG_FCR) & ~MLB_USIO_FCR_FDRQ,
	       port->membase + MLB_USIO_REG_FCR);

	ग_लिखोb(पढ़ोb(port->membase + MLB_USIO_REG_SCR) | MLB_USIO_SCR_TBIE,
	       port->membase + MLB_USIO_REG_SCR);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (uart_circ_empty(xmit))
		mlb_usio_stop_tx(port);
पूर्ण

अटल व्योम mlb_usio_start_tx(काष्ठा uart_port *port)
अणु
	u16 fcr = पढ़ोw(port->membase + MLB_USIO_REG_FCR);

	ग_लिखोw(fcr | MLB_USIO_FCR_FTIE, port->membase + MLB_USIO_REG_FCR);
	अगर (!(fcr & MLB_USIO_FCR_FDRQ))
		वापस;

	ग_लिखोb(पढ़ोb(port->membase + MLB_USIO_REG_SCR) | MLB_USIO_SCR_TBIE,
	       port->membase + MLB_USIO_REG_SCR);

	अगर (पढ़ोb(port->membase + MLB_USIO_REG_SSR) & MLB_USIO_SSR_TBI)
		mlb_usio_tx_अक्षरs(port);
पूर्ण

अटल व्योम mlb_usio_stop_rx(काष्ठा uart_port *port)
अणु
	ग_लिखोb(पढ़ोb(port->membase + MLB_USIO_REG_SCR) & ~MLB_USIO_SCR_RIE,
	       port->membase + MLB_USIO_REG_SCR);
पूर्ण

अटल व्योम mlb_usio_enable_ms(काष्ठा uart_port *port)
अणु
	ग_लिखोb(पढ़ोb(port->membase + MLB_USIO_REG_SCR) |
	       MLB_USIO_SCR_RIE | MLB_USIO_SCR_RXE,
	       port->membase + MLB_USIO_REG_SCR);
पूर्ण

अटल व्योम mlb_usio_rx_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा tty_port *ttyport = &port->state->port;
	अचिन्हित दीर्घ flag = 0;
	अक्षर ch = 0;
	u8 status;
	पूर्णांक max_count = 2;

	जबतक (max_count--) अणु
		status = पढ़ोb(port->membase + MLB_USIO_REG_SSR);

		अगर (!(status & MLB_USIO_SSR_RDRF))
			अवरोध;

		अगर (!(status & (MLB_USIO_SSR_ORE | MLB_USIO_SSR_FRE |
				MLB_USIO_SSR_PE))) अणु
			ch = पढ़ोw(port->membase + MLB_USIO_REG_DR);
			flag = TTY_NORMAL;
			port->icount.rx++;
			अगर (uart_handle_sysrq_अक्षर(port, ch))
				जारी;
			uart_insert_अक्षर(port, status, MLB_USIO_SSR_ORE,
					 ch, flag);
			जारी;
		पूर्ण
		अगर (status & MLB_USIO_SSR_PE)
			port->icount.parity++;
		अगर (status & MLB_USIO_SSR_ORE)
			port->icount.overrun++;
		status &= port->पढ़ो_status_mask;
		अगर (status & MLB_USIO_SSR_BRK) अणु
			flag = TTY_BREAK;
			ch = 0;
		पूर्ण अन्यथा
			अगर (status & MLB_USIO_SSR_PE) अणु
				flag = TTY_PARITY;
				ch = 0;
			पूर्ण अन्यथा
				अगर (status & MLB_USIO_SSR_FRE) अणु
					flag = TTY_FRAME;
					ch = 0;
				पूर्ण
		अगर (flag)
			uart_insert_अक्षर(port, status, MLB_USIO_SSR_ORE,
					 ch, flag);

		ग_लिखोb(पढ़ोb(port->membase + MLB_USIO_REG_SSR) |
				MLB_USIO_SSR_REC,
				port->membase + MLB_USIO_REG_SSR);

		max_count = पढ़ोw(port->membase + MLB_USIO_REG_FBYTE) >> 8;
		ग_लिखोw(पढ़ोw(port->membase + MLB_USIO_REG_FCR) |
		       MLB_USIO_FCR_FE2 | MLB_USIO_FCR_FRIIE,
		port->membase + MLB_USIO_REG_FCR);
	पूर्ण

	tty_flip_buffer_push(ttyport);
पूर्ण

अटल irqवापस_t mlb_usio_rx_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;

	spin_lock(&port->lock);
	mlb_usio_rx_अक्षरs(port);
	spin_unlock(&port->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mlb_usio_tx_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;

	spin_lock(&port->lock);
	अगर (पढ़ोb(port->membase + MLB_USIO_REG_SSR) & MLB_USIO_SSR_TBI)
		mlb_usio_tx_अक्षरs(port);
	spin_unlock(&port->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक mlb_usio_tx_empty(काष्ठा uart_port *port)
अणु
	वापस (पढ़ोb(port->membase + MLB_USIO_REG_SSR) & MLB_USIO_SSR_TBI) ?
		TIOCSER_TEMT : 0;
पूर्ण

अटल व्योम mlb_usio_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
पूर्ण

अटल अचिन्हित पूर्णांक mlb_usio_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस TIOCM_CAR | TIOCM_DSR | TIOCM_CTS;

पूर्ण

अटल व्योम mlb_usio_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
पूर्ण

अटल पूर्णांक mlb_usio_startup(काष्ठा uart_port *port)
अणु
	स्थिर अक्षर *portname = to_platक्रमm_device(port->dev)->name;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, index = port->line;
	अचिन्हित अक्षर  escr;

	ret = request_irq(mlb_usio_irq[index][RX], mlb_usio_rx_irq,
				0, portname, port);
	अगर (ret)
		वापस ret;
	ret = request_irq(mlb_usio_irq[index][TX], mlb_usio_tx_irq,
				0, portname, port);
	अगर (ret) अणु
		मुक्त_irq(mlb_usio_irq[index][RX], port);
		वापस ret;
	पूर्ण

	escr = पढ़ोb(port->membase + MLB_USIO_REG_ESCR);
	अगर (of_property_पढ़ो_bool(port->dev->of_node, "auto-flow-control"))
		escr |= MLB_USIO_ESCR_FLWEN;
	spin_lock_irqsave(&port->lock, flags);
	ग_लिखोb(0, port->membase + MLB_USIO_REG_SCR);
	ग_लिखोb(escr, port->membase + MLB_USIO_REG_ESCR);
	ग_लिखोb(MLB_USIO_SCR_UPCL, port->membase + MLB_USIO_REG_SCR);
	ग_लिखोb(MLB_USIO_SSR_REC, port->membase + MLB_USIO_REG_SSR);
	ग_लिखोw(0, port->membase + MLB_USIO_REG_FCR);
	ग_लिखोw(MLB_USIO_FCR_FCL1 | MLB_USIO_FCR_FCL2,
	       port->membase + MLB_USIO_REG_FCR);
	ग_लिखोw(MLB_USIO_FCR_FE1 | MLB_USIO_FCR_FE2 | MLB_USIO_FCR_FRIIE,
	       port->membase + MLB_USIO_REG_FCR);
	ग_लिखोw(0, port->membase + MLB_USIO_REG_FBYTE);
	ग_लिखोw(BIT(12), port->membase + MLB_USIO_REG_FBYTE);

	ग_लिखोb(MLB_USIO_SCR_TXE  | MLB_USIO_SCR_RIE | MLB_USIO_SCR_TBIE |
	       MLB_USIO_SCR_RXE, port->membase + MLB_USIO_REG_SCR);
	spin_unlock_irqrestore(&port->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम mlb_usio_shutकरोwn(काष्ठा uart_port *port)
अणु
	पूर्णांक index = port->line;

	मुक्त_irq(mlb_usio_irq[index][RX], port);
	मुक्त_irq(mlb_usio_irq[index][TX], port);
पूर्ण

अटल व्योम mlb_usio_set_termios(काष्ठा uart_port *port,
			काष्ठा ktermios *termios, काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक escr, smr = MLB_USIO_SMR_SOE;
	अचिन्हित दीर्घ flags, baud, quot;

	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		escr = MLB_USIO_ESCR_L_5BIT;
		अवरोध;
	हाल CS6:
		escr = MLB_USIO_ESCR_L_6BIT;
		अवरोध;
	हाल CS7:
		escr = MLB_USIO_ESCR_L_7BIT;
		अवरोध;
	हाल CS8:
	शेष:
		escr = MLB_USIO_ESCR_L_8BIT;
		अवरोध;
	पूर्ण

	अगर (termios->c_cflag & CSTOPB)
		smr |= MLB_USIO_SMR_SBL;

	अगर (termios->c_cflag & PARENB) अणु
		escr |= MLB_USIO_ESCR_PEN;
		अगर (termios->c_cflag & PARODD)
			escr |= MLB_USIO_ESCR_P;
	पूर्ण
	/* Set hard flow control */
	अगर (of_property_पढ़ो_bool(port->dev->of_node, "auto-flow-control") ||
			(termios->c_cflag & CRTSCTS))
		escr |= MLB_USIO_ESCR_FLWEN;

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk);
	अगर (baud > 1)
		quot = port->uartclk / baud - 1;
	अन्यथा
		quot = 0;

	spin_lock_irqsave(&port->lock, flags);
	uart_update_समयout(port, termios->c_cflag, baud);
	port->पढ़ो_status_mask = MLB_USIO_SSR_ORE | MLB_USIO_SSR_RDRF |
				 MLB_USIO_SSR_TDRE;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= MLB_USIO_SSR_FRE | MLB_USIO_SSR_PE;

	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= MLB_USIO_SSR_FRE | MLB_USIO_SSR_PE;
	अगर ((termios->c_अगरlag & IGNBRK) && (termios->c_अगरlag & IGNPAR))
		port->ignore_status_mask |= MLB_USIO_SSR_ORE;
	अगर ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= MLB_USIO_SSR_RDRF;

	ग_लिखोb(0, port->membase + MLB_USIO_REG_SCR);
	ग_लिखोb(MLB_USIO_SCR_UPCL, port->membase + MLB_USIO_REG_SCR);
	ग_लिखोb(MLB_USIO_SSR_REC, port->membase + MLB_USIO_REG_SSR);
	ग_लिखोw(0, port->membase + MLB_USIO_REG_FCR);
	ग_लिखोb(smr, port->membase + MLB_USIO_REG_SMR);
	ग_लिखोb(escr, port->membase + MLB_USIO_REG_ESCR);
	ग_लिखोw(quot, port->membase + MLB_USIO_REG_BGR);
	ग_लिखोw(0, port->membase + MLB_USIO_REG_FCR);
	ग_लिखोw(MLB_USIO_FCR_FCL1 | MLB_USIO_FCR_FCL2 | MLB_USIO_FCR_FE1 |
	       MLB_USIO_FCR_FE2 | MLB_USIO_FCR_FRIIE,
	       port->membase + MLB_USIO_REG_FCR);
	ग_लिखोw(0, port->membase + MLB_USIO_REG_FBYTE);
	ग_लिखोw(BIT(12), port->membase + MLB_USIO_REG_FBYTE);
	ग_लिखोb(MLB_USIO_SCR_RIE | MLB_USIO_SCR_RXE | MLB_USIO_SCR_TBIE |
	       MLB_USIO_SCR_TXE, port->membase + MLB_USIO_REG_SCR);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *mlb_usio_type(काष्ठा uart_port *port)
अणु
	वापस ((port->type == PORT_MLB_USIO) ? USIO_NAME : शून्य);
पूर्ण

अटल व्योम mlb_usio_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE)
		port->type = PORT_MLB_USIO;
पूर्ण

अटल स्थिर काष्ठा uart_ops mlb_usio_ops = अणु
	.tx_empty	= mlb_usio_tx_empty,
	.set_mctrl	= mlb_usio_set_mctrl,
	.get_mctrl	= mlb_usio_get_mctrl,
	.stop_tx	= mlb_usio_stop_tx,
	.start_tx	= mlb_usio_start_tx,
	.stop_rx	= mlb_usio_stop_rx,
	.enable_ms	= mlb_usio_enable_ms,
	.अवरोध_ctl	= mlb_usio_अवरोध_ctl,
	.startup	= mlb_usio_startup,
	.shutकरोwn	= mlb_usio_shutकरोwn,
	.set_termios	= mlb_usio_set_termios,
	.type		= mlb_usio_type,
	.config_port	= mlb_usio_config_port,
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_MILBEAUT_USIO_CONSOLE

अटल व्योम mlb_usio_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	जबतक (!(पढ़ोb(port->membase + MLB_USIO_REG_SSR) & MLB_USIO_SSR_TDRE))
		cpu_relax();

	ग_लिखोw(c, port->membase + MLB_USIO_REG_DR);
पूर्ण

अटल व्योम mlb_usio_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
			       अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_port *port = &mlb_usio_ports[co->index];

	uart_console_ग_लिखो(port, s, count, mlb_usio_console_अक्षर_दो);
पूर्ण

अटल पूर्णांक __init mlb_usio_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port;
	पूर्णांक baud = 115200;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	पूर्णांक bits = 8;

	अगर (co->index >= CONFIG_SERIAL_MILBEAUT_USIO_PORTS)
		वापस -ENODEV;

	port = &mlb_usio_ports[co->index];
	अगर (!port->membase)
		वापस -ENODEV;


	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	अगर (of_property_पढ़ो_bool(port->dev->of_node, "auto-flow-control"))
		flow = 'r';

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण


अटल काष्ठा uart_driver mlb_usio_uart_driver;
अटल काष्ठा console mlb_usio_console = अणु
	.name   = USIO_UART_DEV_NAME,
	.ग_लिखो  = mlb_usio_console_ग_लिखो,
	.device = uart_console_device,
	.setup  = mlb_usio_console_setup,
	.flags  = CON_PRINTBUFFER,
	.index  = -1,
	.data   = &mlb_usio_uart_driver,
पूर्ण;

अटल पूर्णांक __init mlb_usio_console_init(व्योम)
अणु
	रेजिस्टर_console(&mlb_usio_console);
	वापस 0;
पूर्ण
console_initcall(mlb_usio_console_init);


अटल व्योम mlb_usio_early_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
					u_पूर्णांक count)
अणु
	काष्ठा earlycon_device *dev = co->data;

	uart_console_ग_लिखो(&dev->port, s, count, mlb_usio_console_अक्षर_दो);
पूर्ण

अटल पूर्णांक __init mlb_usio_early_console_setup(काष्ठा earlycon_device *device,
						स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;
	device->con->ग_लिखो = mlb_usio_early_console_ग_लिखो;
	वापस 0;
पूर्ण

OF_EARLYCON_DECLARE(mlb_usio, "socionext,milbeaut-usio-uart",
			mlb_usio_early_console_setup);

#घोषणा USIO_CONSOLE	(&mlb_usio_console)
#अन्यथा
#घोषणा USIO_CONSOLE	शून्य
#पूर्ण_अगर

अटल काष्ठा  uart_driver mlb_usio_uart_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= USIO_NAME,
	.dev_name	= USIO_UART_DEV_NAME,
	.cons           = USIO_CONSOLE,
	.nr		= CONFIG_SERIAL_MILBEAUT_USIO_PORTS,
पूर्ण;

अटल पूर्णांक mlb_usio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk *clk = devm_clk_get(&pdev->dev, शून्य);
	काष्ठा uart_port *port;
	काष्ठा resource *res;
	पूर्णांक index = 0;
	पूर्णांक ret;

	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "Missing clock\n");
		वापस PTR_ERR(clk);
	पूर्ण
	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Clock enable failed: %d\n", ret);
		वापस ret;
	पूर्ण
	of_property_पढ़ो_u32(pdev->dev.of_node, "index", &index);
	port = &mlb_usio_ports[index];

	port->निजी_data = (व्योम *)clk;
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "Missing regs\n");
		ret = -ENODEV;
		जाओ failed;
	पूर्ण
	port->membase = devm_ioremap(&pdev->dev, res->start,
				resource_size(res));

	ret = platक्रमm_get_irq_byname(pdev, "rx");
	mlb_usio_irq[index][RX] = ret;

	ret = platक्रमm_get_irq_byname(pdev, "tx");
	mlb_usio_irq[index][TX] = ret;

	port->irq = mlb_usio_irq[index][RX];
	port->uartclk = clk_get_rate(clk);
	port->fअगरosize = 128;
	port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_MILBEAUT_USIO_CONSOLE);
	port->iotype = UPIO_MEM32;
	port->flags = UPF_BOOT_AUTOCONF | UPF_SPD_VHI;
	port->line = index;
	port->ops = &mlb_usio_ops;
	port->dev = &pdev->dev;

	ret = uart_add_one_port(&mlb_usio_uart_driver, port);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Adding port failed: %d\n", ret);
		जाओ failed;
	पूर्ण
	वापस 0;

failed:
	clk_disable_unprepare(clk);

	वापस ret;
पूर्ण

अटल पूर्णांक mlb_usio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port = &mlb_usio_ports[pdev->id];
	काष्ठा clk *clk = port->निजी_data;

	uart_हटाओ_one_port(&mlb_usio_uart_driver, port);
	clk_disable_unprepare(clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mlb_usio_dt_ids[] = अणु
	अणु .compatible = "socionext,milbeaut-usio-uart" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mlb_usio_dt_ids);

अटल काष्ठा platक्रमm_driver mlb_usio_driver = अणु
	.probe          = mlb_usio_probe,
	.हटाओ         = mlb_usio_हटाओ,
	.driver         = अणु
		.name   = USIO_NAME,
		.of_match_table = mlb_usio_dt_ids,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mlb_usio_init(व्योम)
अणु
	पूर्णांक ret = uart_रेजिस्टर_driver(&mlb_usio_uart_driver);

	अगर (ret) अणु
		pr_err("%s: uart registration failed: %d\n", __func__, ret);
		वापस ret;
	पूर्ण
	ret = platक्रमm_driver_रेजिस्टर(&mlb_usio_driver);
	अगर (ret) अणु
		uart_unरेजिस्टर_driver(&mlb_usio_uart_driver);
		pr_err("%s: drv registration failed: %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास mlb_usio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mlb_usio_driver);
	uart_unरेजिस्टर_driver(&mlb_usio_uart_driver);
पूर्ण

module_init(mlb_usio_init);
module_निकास(mlb_usio_निकास);

MODULE_AUTHOR("SOCIONEXT");
MODULE_DESCRIPTION("MILBEAUT_USIO/UART Driver");
MODULE_LICENSE("GPL");
