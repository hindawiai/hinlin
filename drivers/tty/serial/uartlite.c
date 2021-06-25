<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * uartlite.c: Serial driver क्रम Xilinx uartlite serial controller
 *
 * Copyright (C) 2006 Peter Korsgaard <jacmet@sunsite.dk>
 * Copyright (C) 2007 Secret Lab Technologies Ltd.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/console.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/clk.h>

#घोषणा ULITE_NAME		"ttyUL"
#घोषणा ULITE_MAJOR		204
#घोषणा ULITE_MINOR		187
#घोषणा ULITE_NR_UARTS		CONFIG_SERIAL_UARTLITE_NR_UARTS

/* ---------------------------------------------------------------------
 * Register definitions
 *
 * For रेजिस्टर details see datasheet:
 * https://www.xilinx.com/support/करोcumentation/ip_करोcumentation/opb_uartlite.pdf
 */

#घोषणा ULITE_RX		0x00
#घोषणा ULITE_TX		0x04
#घोषणा ULITE_STATUS		0x08
#घोषणा ULITE_CONTROL		0x0c

#घोषणा ULITE_REGION		16

#घोषणा ULITE_STATUS_RXVALID	0x01
#घोषणा ULITE_STATUS_RXFULL	0x02
#घोषणा ULITE_STATUS_TXEMPTY	0x04
#घोषणा ULITE_STATUS_TXFULL	0x08
#घोषणा ULITE_STATUS_IE		0x10
#घोषणा ULITE_STATUS_OVERRUN	0x20
#घोषणा ULITE_STATUS_FRAME	0x40
#घोषणा ULITE_STATUS_PARITY	0x80

#घोषणा ULITE_CONTROL_RST_TX	0x01
#घोषणा ULITE_CONTROL_RST_RX	0x02
#घोषणा ULITE_CONTROL_IE	0x10

/* Static poपूर्णांकer to console port */
#अगर_घोषित CONFIG_SERIAL_UARTLITE_CONSOLE
अटल काष्ठा uart_port *console_port;
#पूर्ण_अगर

काष्ठा uartlite_data अणु
	स्थिर काष्ठा uartlite_reg_ops *reg_ops;
	काष्ठा clk *clk;
पूर्ण;

काष्ठा uartlite_reg_ops अणु
	u32 (*in)(व्योम __iomem *addr);
	व्योम (*out)(u32 val, व्योम __iomem *addr);
पूर्ण;

अटल u32 uartlite_inbe32(व्योम __iomem *addr)
अणु
	वापस ioपढ़ो32be(addr);
पूर्ण

अटल व्योम uartlite_outbe32(u32 val, व्योम __iomem *addr)
अणु
	ioग_लिखो32be(val, addr);
पूर्ण

अटल स्थिर काष्ठा uartlite_reg_ops uartlite_be = अणु
	.in = uartlite_inbe32,
	.out = uartlite_outbe32,
पूर्ण;

अटल u32 uartlite_inle32(व्योम __iomem *addr)
अणु
	वापस ioपढ़ो32(addr);
पूर्ण

अटल व्योम uartlite_outle32(u32 val, व्योम __iomem *addr)
अणु
	ioग_लिखो32(val, addr);
पूर्ण

अटल स्थिर काष्ठा uartlite_reg_ops uartlite_le = अणु
	.in = uartlite_inle32,
	.out = uartlite_outle32,
पूर्ण;

अटल अंतरभूत u32 uart_in32(u32 offset, काष्ठा uart_port *port)
अणु
	काष्ठा uartlite_data *pdata = port->निजी_data;

	वापस pdata->reg_ops->in(port->membase + offset);
पूर्ण

अटल अंतरभूत व्योम uart_out32(u32 val, u32 offset, काष्ठा uart_port *port)
अणु
	काष्ठा uartlite_data *pdata = port->निजी_data;

	pdata->reg_ops->out(val, port->membase + offset);
पूर्ण

अटल काष्ठा uart_port ulite_ports[ULITE_NR_UARTS];

/* ---------------------------------------------------------------------
 * Core UART driver operations
 */

अटल पूर्णांक ulite_receive(काष्ठा uart_port *port, पूर्णांक stat)
अणु
	काष्ठा tty_port *tport = &port->state->port;
	अचिन्हित अक्षर ch = 0;
	अक्षर flag = TTY_NORMAL;

	अगर ((stat & (ULITE_STATUS_RXVALID | ULITE_STATUS_OVERRUN
		     | ULITE_STATUS_FRAME)) == 0)
		वापस 0;

	/* stats */
	अगर (stat & ULITE_STATUS_RXVALID) अणु
		port->icount.rx++;
		ch = uart_in32(ULITE_RX, port);

		अगर (stat & ULITE_STATUS_PARITY)
			port->icount.parity++;
	पूर्ण

	अगर (stat & ULITE_STATUS_OVERRUN)
		port->icount.overrun++;

	अगर (stat & ULITE_STATUS_FRAME)
		port->icount.frame++;


	/* drop byte with parity error अगर IGNPAR specअगरiced */
	अगर (stat & port->ignore_status_mask & ULITE_STATUS_PARITY)
		stat &= ~ULITE_STATUS_RXVALID;

	stat &= port->पढ़ो_status_mask;

	अगर (stat & ULITE_STATUS_PARITY)
		flag = TTY_PARITY;


	stat &= ~port->ignore_status_mask;

	अगर (stat & ULITE_STATUS_RXVALID)
		tty_insert_flip_अक्षर(tport, ch, flag);

	अगर (stat & ULITE_STATUS_FRAME)
		tty_insert_flip_अक्षर(tport, 0, TTY_FRAME);

	अगर (stat & ULITE_STATUS_OVERRUN)
		tty_insert_flip_अक्षर(tport, 0, TTY_OVERRUN);

	वापस 1;
पूर्ण

अटल पूर्णांक ulite_transmit(काष्ठा uart_port *port, पूर्णांक stat)
अणु
	काष्ठा circ_buf *xmit  = &port->state->xmit;

	अगर (stat & ULITE_STATUS_TXFULL)
		वापस 0;

	अगर (port->x_अक्षर) अणु
		uart_out32(port->x_अक्षर, ULITE_TX, port);
		port->x_अक्षर = 0;
		port->icount.tx++;
		वापस 1;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port))
		वापस 0;

	uart_out32(xmit->buf[xmit->tail], ULITE_TX, port);
	xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE-1);
	port->icount.tx++;

	/* wake up */
	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	वापस 1;
पूर्ण

अटल irqवापस_t ulite_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	पूर्णांक stat, busy, n = 0;
	अचिन्हित दीर्घ flags;

	करो अणु
		spin_lock_irqsave(&port->lock, flags);
		stat = uart_in32(ULITE_STATUS, port);
		busy  = ulite_receive(port, stat);
		busy |= ulite_transmit(port, stat);
		spin_unlock_irqrestore(&port->lock, flags);
		n++;
	पूर्ण जबतक (busy);

	/* work करोne? */
	अगर (n > 1) अणु
		tty_flip_buffer_push(&port->state->port);
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अणु
		वापस IRQ_NONE;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक ulite_tx_empty(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ret;

	spin_lock_irqsave(&port->lock, flags);
	ret = uart_in32(ULITE_STATUS, port);
	spin_unlock_irqrestore(&port->lock, flags);

	वापस ret & ULITE_STATUS_TXEMPTY ? TIOCSER_TEMT : 0;
पूर्ण

अटल अचिन्हित पूर्णांक ulite_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस TIOCM_CTS | TIOCM_DSR | TIOCM_CAR;
पूर्ण

अटल व्योम ulite_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	/* N/A */
पूर्ण

अटल व्योम ulite_stop_tx(काष्ठा uart_port *port)
अणु
	/* N/A */
पूर्ण

अटल व्योम ulite_start_tx(काष्ठा uart_port *port)
अणु
	ulite_transmit(port, uart_in32(ULITE_STATUS, port));
पूर्ण

अटल व्योम ulite_stop_rx(काष्ठा uart_port *port)
अणु
	/* करोn't क्रमward any more data (like !CREAD) */
	port->ignore_status_mask = ULITE_STATUS_RXVALID | ULITE_STATUS_PARITY
		| ULITE_STATUS_FRAME | ULITE_STATUS_OVERRUN;
पूर्ण

अटल व्योम ulite_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक ctl)
अणु
	/* N/A */
पूर्ण

अटल पूर्णांक ulite_startup(काष्ठा uart_port *port)
अणु
	काष्ठा uartlite_data *pdata = port->निजी_data;
	पूर्णांक ret;

	ret = clk_enable(pdata->clk);
	अगर (ret) अणु
		dev_err(port->dev, "Failed to enable clock\n");
		वापस ret;
	पूर्ण

	ret = request_irq(port->irq, ulite_isr, IRQF_SHARED | IRQF_TRIGGER_RISING,
			  "uartlite", port);
	अगर (ret)
		वापस ret;

	uart_out32(ULITE_CONTROL_RST_RX | ULITE_CONTROL_RST_TX,
		ULITE_CONTROL, port);
	uart_out32(ULITE_CONTROL_IE, ULITE_CONTROL, port);

	वापस 0;
पूर्ण

अटल व्योम ulite_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा uartlite_data *pdata = port->निजी_data;

	uart_out32(0, ULITE_CONTROL, port);
	uart_in32(ULITE_CONTROL, port); /* dummy */
	मुक्त_irq(port->irq, port);
	clk_disable(pdata->clk);
पूर्ण

अटल व्योम ulite_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
			      काष्ठा ktermios *old)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud;

	spin_lock_irqsave(&port->lock, flags);

	port->पढ़ो_status_mask = ULITE_STATUS_RXVALID | ULITE_STATUS_OVERRUN
		| ULITE_STATUS_TXFULL;

	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |=
			ULITE_STATUS_PARITY | ULITE_STATUS_FRAME;

	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= ULITE_STATUS_PARITY
			| ULITE_STATUS_FRAME | ULITE_STATUS_OVERRUN;

	/* ignore all अक्षरacters अगर CREAD is not set */
	अगर ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |=
			ULITE_STATUS_RXVALID | ULITE_STATUS_PARITY
			| ULITE_STATUS_FRAME | ULITE_STATUS_OVERRUN;

	/* update समयout */
	baud = uart_get_baud_rate(port, termios, old, 0, 460800);
	uart_update_समयout(port, termios->c_cflag, baud);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *ulite_type(काष्ठा uart_port *port)
अणु
	वापस port->type == PORT_UARTLITE ? "uartlite" : शून्य;
पूर्ण

अटल व्योम ulite_release_port(काष्ठा uart_port *port)
अणु
	release_mem_region(port->mapbase, ULITE_REGION);
	iounmap(port->membase);
	port->membase = शून्य;
पूर्ण

अटल पूर्णांक ulite_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा uartlite_data *pdata = port->निजी_data;
	पूर्णांक ret;

	pr_debug("ulite console: port=%p; port->mapbase=%llx\n",
		 port, (अचिन्हित दीर्घ दीर्घ) port->mapbase);

	अगर (!request_mem_region(port->mapbase, ULITE_REGION, "uartlite")) अणु
		dev_err(port->dev, "Memory region busy\n");
		वापस -EBUSY;
	पूर्ण

	port->membase = ioremap(port->mapbase, ULITE_REGION);
	अगर (!port->membase) अणु
		dev_err(port->dev, "Unable to map registers\n");
		release_mem_region(port->mapbase, ULITE_REGION);
		वापस -EBUSY;
	पूर्ण

	pdata->reg_ops = &uartlite_be;
	ret = uart_in32(ULITE_CONTROL, port);
	uart_out32(ULITE_CONTROL_RST_TX, ULITE_CONTROL, port);
	ret = uart_in32(ULITE_STATUS, port);
	/* Endianess detection */
	अगर ((ret & ULITE_STATUS_TXEMPTY) != ULITE_STATUS_TXEMPTY)
		pdata->reg_ops = &uartlite_le;

	वापस 0;
पूर्ण

अटल व्योम ulite_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (!ulite_request_port(port))
		port->type = PORT_UARTLITE;
पूर्ण

अटल पूर्णांक ulite_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	/* we करोn't want the core code to modअगरy any port params */
	वापस -EINVAL;
पूर्ण

अटल व्योम ulite_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
		     अचिन्हित पूर्णांक oldstate)
अणु
	काष्ठा uartlite_data *pdata = port->निजी_data;

	अगर (!state)
		clk_enable(pdata->clk);
	अन्यथा
		clk_disable(pdata->clk);
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
अटल पूर्णांक ulite_get_poll_अक्षर(काष्ठा uart_port *port)
अणु
	अगर (!(uart_in32(ULITE_STATUS, port) & ULITE_STATUS_RXVALID))
		वापस NO_POLL_CHAR;

	वापस uart_in32(ULITE_RX, port);
पूर्ण

अटल व्योम ulite_put_poll_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर ch)
अणु
	जबतक (uart_in32(ULITE_STATUS, port) & ULITE_STATUS_TXFULL)
		cpu_relax();

	/* ग_लिखो अक्षर to device */
	uart_out32(ch, ULITE_TX, port);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा uart_ops ulite_ops = अणु
	.tx_empty	= ulite_tx_empty,
	.set_mctrl	= ulite_set_mctrl,
	.get_mctrl	= ulite_get_mctrl,
	.stop_tx	= ulite_stop_tx,
	.start_tx	= ulite_start_tx,
	.stop_rx	= ulite_stop_rx,
	.अवरोध_ctl	= ulite_अवरोध_ctl,
	.startup	= ulite_startup,
	.shutकरोwn	= ulite_shutकरोwn,
	.set_termios	= ulite_set_termios,
	.type		= ulite_type,
	.release_port	= ulite_release_port,
	.request_port	= ulite_request_port,
	.config_port	= ulite_config_port,
	.verअगरy_port	= ulite_verअगरy_port,
	.pm		= ulite_pm,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर	= ulite_get_poll_अक्षर,
	.poll_put_अक्षर	= ulite_put_poll_अक्षर,
#पूर्ण_अगर
पूर्ण;

/* ---------------------------------------------------------------------
 * Console driver operations
 */

#अगर_घोषित CONFIG_SERIAL_UARTLITE_CONSOLE
अटल व्योम ulite_console_रुको_tx(काष्ठा uart_port *port)
अणु
	u8 val;
	अचिन्हित दीर्घ समयout;

	/*
	 * Spin रुकोing क्रम TX fअगरo to have space available.
	 * When using the Microblaze Debug Module this can take up to 1s
	 */
	समयout = jअगरfies + msecs_to_jअगरfies(1000);
	जबतक (1) अणु
		val = uart_in32(ULITE_STATUS, port);
		अगर ((val & ULITE_STATUS_TXFULL) == 0)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_warn(port->dev,
				 "timeout waiting for TX buffer empty\n");
			अवरोध;
		पूर्ण
		cpu_relax();
	पूर्ण
पूर्ण

अटल व्योम ulite_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	ulite_console_रुको_tx(port);
	uart_out32(ch, ULITE_TX, port);
पूर्ण

अटल व्योम ulite_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_port *port = console_port;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ier;
	पूर्णांक locked = 1;

	अगर (oops_in_progress) अणु
		locked = spin_trylock_irqsave(&port->lock, flags);
	पूर्ण अन्यथा
		spin_lock_irqsave(&port->lock, flags);

	/* save and disable पूर्णांकerrupt */
	ier = uart_in32(ULITE_STATUS, port) & ULITE_STATUS_IE;
	uart_out32(0, ULITE_CONTROL, port);

	uart_console_ग_लिखो(port, s, count, ulite_console_अक्षर_दो);

	ulite_console_रुको_tx(port);

	/* restore पूर्णांकerrupt state */
	अगर (ier)
		uart_out32(ULITE_CONTROL_IE, ULITE_CONTROL, port);

	अगर (locked)
		spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल पूर्णांक ulite_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';


	port = console_port;

	/* Has the device been initialized yet? */
	अगर (!port->mapbase) अणु
		pr_debug("console on ttyUL%i not present\n", co->index);
		वापस -ENODEV;
	पूर्ण

	/* not initialized yet? */
	अगर (!port->membase) अणु
		अगर (ulite_request_port(port))
			वापस -ENODEV;
	पूर्ण

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver ulite_uart_driver;

अटल काष्ठा console ulite_console = अणु
	.name	= ULITE_NAME,
	.ग_लिखो	= ulite_console_ग_लिखो,
	.device	= uart_console_device,
	.setup	= ulite_console_setup,
	.flags	= CON_PRINTBUFFER,
	.index	= -1, /* Specअगरied on the cmdline (e.g. console=ttyUL0 ) */
	.data	= &ulite_uart_driver,
पूर्ण;

अटल व्योम early_uartlite_अ_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	/*
	 * Limit how many बार we'll spin रुकोing क्रम TX FIFO status.
	 * This will prevent lockups अगर the base address is incorrectly
	 * set, or any other issue on the UARTLITE.
	 * This limit is pretty arbitrary, unless we are at about 10 baud
	 * we'll never समयout on a working UART.
	 */

	अचिन्हित retries = 1000000;
	/* पढ़ो status bit - 0x8 offset */
	जबतक (--retries && (पढ़ोl(port->membase + 8) & (1 << 3)))
		;

	/* Only attempt the ioग_लिखो अगर we didn't समयout */
	/* ग_लिखो to TX_FIFO - 0x4 offset */
	अगर (retries)
		ग_लिखोl(c & 0xff, port->membase + 4);
पूर्ण

अटल व्योम early_uartlite_ग_लिखो(काष्ठा console *console,
				 स्थिर अक्षर *s, अचिन्हित n)
अणु
	काष्ठा earlycon_device *device = console->data;
	uart_console_ग_लिखो(&device->port, s, n, early_uartlite_अ_दो);
पूर्ण

अटल पूर्णांक __init early_uartlite_setup(काष्ठा earlycon_device *device,
				       स्थिर अक्षर *options)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->con->ग_लिखो = early_uartlite_ग_लिखो;
	वापस 0;
पूर्ण
EARLYCON_DECLARE(uartlite, early_uartlite_setup);
OF_EARLYCON_DECLARE(uartlite_b, "xlnx,opb-uartlite-1.00.b", early_uartlite_setup);
OF_EARLYCON_DECLARE(uartlite_a, "xlnx,xps-uartlite-1.00.a", early_uartlite_setup);

#पूर्ण_अगर /* CONFIG_SERIAL_UARTLITE_CONSOLE */

अटल काष्ठा uart_driver ulite_uart_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "uartlite",
	.dev_name	= ULITE_NAME,
	.major		= ULITE_MAJOR,
	.minor		= ULITE_MINOR,
	.nr		= ULITE_NR_UARTS,
#अगर_घोषित CONFIG_SERIAL_UARTLITE_CONSOLE
	.cons		= &ulite_console,
#पूर्ण_अगर
पूर्ण;

/* ---------------------------------------------------------------------
 * Port assignment functions (mapping devices to uart_port काष्ठाures)
 */

/** ulite_assign: रेजिस्टर a uartlite device with the driver
 *
 * @dev: poपूर्णांकer to device काष्ठाure
 * @id: requested id number.  Pass -1 क्रम स्वतःmatic port assignment
 * @base: base address of uartlite रेजिस्टरs
 * @irq: irq number क्रम uartlite
 * @pdata: निजी data क्रम uartlite
 *
 * Returns: 0 on success, <0 otherwise
 */
अटल पूर्णांक ulite_assign(काष्ठा device *dev, पूर्णांक id, u32 base, पूर्णांक irq,
			काष्ठा uartlite_data *pdata)
अणु
	काष्ठा uart_port *port;
	पूर्णांक rc;

	/* अगर id = -1; then scan क्रम a मुक्त id and use that */
	अगर (id < 0) अणु
		क्रम (id = 0; id < ULITE_NR_UARTS; id++)
			अगर (ulite_ports[id].mapbase == 0)
				अवरोध;
	पूर्ण
	अगर (id < 0 || id >= ULITE_NR_UARTS) अणु
		dev_err(dev, "%s%i too large\n", ULITE_NAME, id);
		वापस -EINVAL;
	पूर्ण

	अगर ((ulite_ports[id].mapbase) && (ulite_ports[id].mapbase != base)) अणु
		dev_err(dev, "cannot assign to %s%i; it is already in use\n",
			ULITE_NAME, id);
		वापस -EBUSY;
	पूर्ण

	port = &ulite_ports[id];

	spin_lock_init(&port->lock);
	port->fअगरosize = 16;
	port->regshअगरt = 2;
	port->iotype = UPIO_MEM;
	port->iobase = 1; /* mark port in use */
	port->mapbase = base;
	port->membase = शून्य;
	port->ops = &ulite_ops;
	port->irq = irq;
	port->flags = UPF_BOOT_AUTOCONF;
	port->dev = dev;
	port->type = PORT_UNKNOWN;
	port->line = id;
	port->निजी_data = pdata;

	dev_set_drvdata(dev, port);

#अगर_घोषित CONFIG_SERIAL_UARTLITE_CONSOLE
	/*
	 * If console hasn't been found yet try to assign this port
	 * because it is required to be asचिन्हित क्रम console setup function.
	 * If रेजिस्टर_console() करोn't assign value, then console_port poपूर्णांकer
	 * is cleanup.
	 */
	अगर (ulite_uart_driver.cons->index == -1)
		console_port = port;
#पूर्ण_अगर

	/* Register the port */
	rc = uart_add_one_port(&ulite_uart_driver, port);
	अगर (rc) अणु
		dev_err(dev, "uart_add_one_port() failed; err=%i\n", rc);
		port->mapbase = 0;
		dev_set_drvdata(dev, शून्य);
		वापस rc;
	पूर्ण

#अगर_घोषित CONFIG_SERIAL_UARTLITE_CONSOLE
	/* This is not port which is used क्रम console that's why clean it up */
	अगर (ulite_uart_driver.cons->index == -1)
		console_port = शून्य;
#पूर्ण_अगर

	वापस 0;
पूर्ण

/** ulite_release: रेजिस्टर a uartlite device with the driver
 *
 * @dev: poपूर्णांकer to device काष्ठाure
 */
अटल पूर्णांक ulite_release(काष्ठा device *dev)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(dev);
	पूर्णांक rc = 0;

	अगर (port) अणु
		rc = uart_हटाओ_one_port(&ulite_uart_driver, port);
		dev_set_drvdata(dev, शून्य);
		port->mapbase = 0;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ulite_suspend - Stop the device.
 *
 * @dev: handle to the device काष्ठाure.
 * Return: 0 always.
 */
अटल पूर्णांक __maybe_unused ulite_suspend(काष्ठा device *dev)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(dev);

	अगर (port)
		uart_suspend_port(&ulite_uart_driver, port);

	वापस 0;
पूर्ण

/**
 * ulite_resume - Resume the device.
 *
 * @dev: handle to the device काष्ठाure.
 * Return: 0 on success, त्रुटि_सं otherwise.
 */
अटल पूर्णांक __maybe_unused ulite_resume(काष्ठा device *dev)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(dev);

	अगर (port)
		uart_resume_port(&ulite_uart_driver, port);

	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------
 * Platक्रमm bus binding
 */

अटल SIMPLE_DEV_PM_OPS(ulite_pm_ops, ulite_suspend, ulite_resume);

#अगर defined(CONFIG_OF)
/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id ulite_of_match[] = अणु
	अणु .compatible = "xlnx,opb-uartlite-1.00.b", पूर्ण,
	अणु .compatible = "xlnx,xps-uartlite-1.00.a", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ulite_of_match);
#पूर्ण_अगर /* CONFIG_OF */

अटल पूर्णांक ulite_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा uartlite_data *pdata;
	पूर्णांक irq, ret;
	पूर्णांक id = pdev->id;
#अगर_घोषित CONFIG_OF
	स्थिर __be32 *prop;

	prop = of_get_property(pdev->dev.of_node, "port-number", शून्य);
	अगर (prop)
		id = be32_to_cpup(prop);
#पूर्ण_अगर
	pdata = devm_kzalloc(&pdev->dev, माप(काष्ठा uartlite_data),
			     GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	pdata->clk = devm_clk_get(&pdev->dev, "s_axi_aclk");
	अगर (IS_ERR(pdata->clk)) अणु
		अगर (PTR_ERR(pdata->clk) != -ENOENT)
			वापस PTR_ERR(pdata->clk);

		/*
		 * Clock framework support is optional, जारी on
		 * anyways अगर we करोn't find a matching घड़ी.
		 */
		pdata->clk = शून्य;
	पूर्ण

	ret = clk_prepare_enable(pdata->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to prepare clock\n");
		वापस ret;
	पूर्ण

	अगर (!ulite_uart_driver.state) अणु
		dev_dbg(&pdev->dev, "uartlite: calling uart_register_driver()\n");
		ret = uart_रेजिस्टर_driver(&ulite_uart_driver);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "Failed to register driver\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = ulite_assign(&pdev->dev, id, res->start, irq, pdata);

	clk_disable(pdata->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक ulite_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(&pdev->dev);
	काष्ठा uartlite_data *pdata = port->निजी_data;

	clk_disable_unprepare(pdata->clk);
	वापस ulite_release(&pdev->dev);
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:uartlite");

अटल काष्ठा platक्रमm_driver ulite_platक्रमm_driver = अणु
	.probe = ulite_probe,
	.हटाओ = ulite_हटाओ,
	.driver = अणु
		.name  = "uartlite",
		.of_match_table = of_match_ptr(ulite_of_match),
		.pm = &ulite_pm_ops,
	पूर्ण,
पूर्ण;

/* ---------------------------------------------------------------------
 * Module setup/tearकरोwn
 */

अटल पूर्णांक __init ulite_init(व्योम)
अणु

	pr_debug("uartlite: calling platform_driver_register()\n");
	वापस platक्रमm_driver_रेजिस्टर(&ulite_platक्रमm_driver);
पूर्ण

अटल व्योम __निकास ulite_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ulite_platक्रमm_driver);
	अगर (ulite_uart_driver.state)
		uart_unरेजिस्टर_driver(&ulite_uart_driver);
पूर्ण

module_init(ulite_init);
module_निकास(ulite_निकास);

MODULE_AUTHOR("Peter Korsgaard <jacmet@sunsite.dk>");
MODULE_DESCRIPTION("Xilinx uartlite serial driver");
MODULE_LICENSE("GPL");
