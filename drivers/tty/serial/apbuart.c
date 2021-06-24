<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Driver क्रम GRLIB serial ports (APBUART)
 *
 *  Based on linux/drivers/serial/amba.c
 *
 *  Copyright (C) 2000 Deep Blue Solutions Ltd.
 *  Copyright (C) 2003 Konrad Eisele <eiselekd@web.de>
 *  Copyright (C) 2006 Daniel Hellstrom <daniel@gaisler.com>, Aeroflex Gaisler AB
 *  Copyright (C) 2008 Gilead Kutnick <kutnickg@zin-tech.com>
 *  Copyright (C) 2009 Kristoffer Glembo <kristoffer@gaisler.com>, Aeroflex Gaisler AB
 */

#समावेश <linux/module.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/console.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/serial_core.h>
#समावेश <यंत्र/irq.h>

#समावेश "apbuart.h"

#घोषणा SERIAL_APBUART_MAJOR	TTY_MAJOR
#घोषणा SERIAL_APBUART_MINOR	64
#घोषणा UART_DUMMY_RSR_RX	0x8000	/* क्रम ignore all पढ़ो */

अटल व्योम apbuart_tx_अक्षरs(काष्ठा uart_port *port);

अटल व्योम apbuart_stop_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक cr;

	cr = UART_GET_CTRL(port);
	cr &= ~UART_CTRL_TI;
	UART_PUT_CTRL(port, cr);
पूर्ण

अटल व्योम apbuart_start_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक cr;

	cr = UART_GET_CTRL(port);
	cr |= UART_CTRL_TI;
	UART_PUT_CTRL(port, cr);

	अगर (UART_GET_STATUS(port) & UART_STATUS_THE)
		apbuart_tx_अक्षरs(port);
पूर्ण

अटल व्योम apbuart_stop_rx(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक cr;

	cr = UART_GET_CTRL(port);
	cr &= ~(UART_CTRL_RI);
	UART_PUT_CTRL(port, cr);
पूर्ण

अटल व्योम apbuart_rx_अक्षरs(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक status, ch, rsr, flag;
	अचिन्हित पूर्णांक max_अक्षरs = port->fअगरosize;

	status = UART_GET_STATUS(port);

	जबतक (UART_RX_DATA(status) && (max_अक्षरs--)) अणु

		ch = UART_GET_CHAR(port);
		flag = TTY_NORMAL;

		port->icount.rx++;

		rsr = UART_GET_STATUS(port) | UART_DUMMY_RSR_RX;
		UART_PUT_STATUS(port, 0);
		अगर (rsr & UART_STATUS_ERR) अणु

			अगर (rsr & UART_STATUS_BR) अणु
				rsr &= ~(UART_STATUS_FE | UART_STATUS_PE);
				port->icount.brk++;
				अगर (uart_handle_अवरोध(port))
					जाओ ignore_अक्षर;
			पूर्ण अन्यथा अगर (rsr & UART_STATUS_PE) अणु
				port->icount.parity++;
			पूर्ण अन्यथा अगर (rsr & UART_STATUS_FE) अणु
				port->icount.frame++;
			पूर्ण
			अगर (rsr & UART_STATUS_OE)
				port->icount.overrun++;

			rsr &= port->पढ़ो_status_mask;

			अगर (rsr & UART_STATUS_PE)
				flag = TTY_PARITY;
			अन्यथा अगर (rsr & UART_STATUS_FE)
				flag = TTY_FRAME;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(port, ch))
			जाओ ignore_अक्षर;

		uart_insert_अक्षर(port, rsr, UART_STATUS_OE, ch, flag);


	      ignore_अक्षर:
		status = UART_GET_STATUS(port);
	पूर्ण

	tty_flip_buffer_push(&port->state->port);
पूर्ण

अटल व्योम apbuart_tx_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	पूर्णांक count;

	अगर (port->x_अक्षर) अणु
		UART_PUT_CHAR(port, port->x_अक्षर);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		apbuart_stop_tx(port);
		वापस;
	पूर्ण

	/* amba: fill FIFO */
	count = port->fअगरosize >> 1;
	करो अणु
		UART_PUT_CHAR(port, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण जबतक (--count > 0);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (uart_circ_empty(xmit))
		apbuart_stop_tx(port);
पूर्ण

अटल irqवापस_t apbuart_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	अचिन्हित पूर्णांक status;

	spin_lock(&port->lock);

	status = UART_GET_STATUS(port);
	अगर (status & UART_STATUS_DR)
		apbuart_rx_अक्षरs(port);
	अगर (status & UART_STATUS_THE)
		apbuart_tx_अक्षरs(port);

	spin_unlock(&port->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक apbuart_tx_empty(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक status = UART_GET_STATUS(port);
	वापस status & UART_STATUS_THE ? TIOCSER_TEMT : 0;
पूर्ण

अटल अचिन्हित पूर्णांक apbuart_get_mctrl(काष्ठा uart_port *port)
अणु
	/* The GRLIB APBUART handles flow control in hardware */
	वापस TIOCM_CAR | TIOCM_DSR | TIOCM_CTS;
पूर्ण

अटल व्योम apbuart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	/* The GRLIB APBUART handles flow control in hardware */
पूर्ण

अटल व्योम apbuart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	/* We करोn't support sending अवरोध */
पूर्ण

अटल पूर्णांक apbuart_startup(काष्ठा uart_port *port)
अणु
	पूर्णांक retval;
	अचिन्हित पूर्णांक cr;

	/* Allocate the IRQ */
	retval = request_irq(port->irq, apbuart_पूर्णांक, 0, "apbuart", port);
	अगर (retval)
		वापस retval;

	/* Finally, enable पूर्णांकerrupts */
	cr = UART_GET_CTRL(port);
	UART_PUT_CTRL(port,
		      cr | UART_CTRL_RE | UART_CTRL_TE |
		      UART_CTRL_RI | UART_CTRL_TI);

	वापस 0;
पूर्ण

अटल व्योम apbuart_shutकरोwn(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक cr;

	/* disable all पूर्णांकerrupts, disable the port */
	cr = UART_GET_CTRL(port);
	UART_PUT_CTRL(port,
		      cr & ~(UART_CTRL_RE | UART_CTRL_TE |
			     UART_CTRL_RI | UART_CTRL_TI));

	/* Free the पूर्णांकerrupt */
	मुक्त_irq(port->irq, port);
पूर्ण

अटल व्योम apbuart_set_termios(काष्ठा uart_port *port,
				काष्ठा ktermios *termios, काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक cr;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, quot;

	/* Ask the core to calculate the भागisor क्रम us. */
	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk / 16);
	अगर (baud == 0)
		panic("invalid baudrate %i\n", port->uartclk / 16);

	/* uart_get_भागisor calc a *16 uart freq, apbuart is *8 */
	quot = (uart_get_भागisor(port, baud)) * 2;
	cr = UART_GET_CTRL(port);
	cr &= ~(UART_CTRL_PE | UART_CTRL_PS);

	अगर (termios->c_cflag & PARENB) अणु
		cr |= UART_CTRL_PE;
		अगर ((termios->c_cflag & PARODD))
			cr |= UART_CTRL_PS;
	पूर्ण

	/* Enable flow control. */
	अगर (termios->c_cflag & CRTSCTS)
		cr |= UART_CTRL_FL;

	spin_lock_irqsave(&port->lock, flags);

	/* Update the per-port समयout. */
	uart_update_समयout(port, termios->c_cflag, baud);

	port->पढ़ो_status_mask = UART_STATUS_OE;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= UART_STATUS_FE | UART_STATUS_PE;

	/* Characters to ignore */
	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= UART_STATUS_FE | UART_STATUS_PE;

	/* Ignore all अक्षरacters अगर CREAD is not set. */
	अगर ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= UART_DUMMY_RSR_RX;

	/* Set baud rate */
	quot -= 1;
	UART_PUT_SCAL(port, quot);
	UART_PUT_CTRL(port, cr);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *apbuart_type(काष्ठा uart_port *port)
अणु
	वापस port->type == PORT_APBUART ? "GRLIB/APBUART" : शून्य;
पूर्ण

अटल व्योम apbuart_release_port(काष्ठा uart_port *port)
अणु
	release_mem_region(port->mapbase, 0x100);
पूर्ण

अटल पूर्णांक apbuart_request_port(काष्ठा uart_port *port)
अणु
	वापस request_mem_region(port->mapbase, 0x100, "grlib-apbuart")
	    != शून्य ? 0 : -EBUSY;
	वापस 0;
पूर्ण

/* Configure/स्वतःconfigure the port */
अटल व्योम apbuart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE) अणु
		port->type = PORT_APBUART;
		apbuart_request_port(port);
	पूर्ण
पूर्ण

/* Verअगरy the new serial_काष्ठा (क्रम TIOCSSERIAL) */
अटल पूर्णांक apbuart_verअगरy_port(काष्ठा uart_port *port,
			       काष्ठा serial_काष्ठा *ser)
अणु
	पूर्णांक ret = 0;
	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_APBUART)
		ret = -EINVAL;
	अगर (ser->irq < 0 || ser->irq >= NR_IRQS)
		ret = -EINVAL;
	अगर (ser->baud_base < 9600)
		ret = -EINVAL;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा uart_ops grlib_apbuart_ops = अणु
	.tx_empty = apbuart_tx_empty,
	.set_mctrl = apbuart_set_mctrl,
	.get_mctrl = apbuart_get_mctrl,
	.stop_tx = apbuart_stop_tx,
	.start_tx = apbuart_start_tx,
	.stop_rx = apbuart_stop_rx,
	.अवरोध_ctl = apbuart_अवरोध_ctl,
	.startup = apbuart_startup,
	.shutकरोwn = apbuart_shutकरोwn,
	.set_termios = apbuart_set_termios,
	.type = apbuart_type,
	.release_port = apbuart_release_port,
	.request_port = apbuart_request_port,
	.config_port = apbuart_config_port,
	.verअगरy_port = apbuart_verअगरy_port,
पूर्ण;

अटल काष्ठा uart_port grlib_apbuart_ports[UART_NR];
अटल काष्ठा device_node *grlib_apbuart_nodes[UART_NR];

अटल पूर्णांक apbuart_scan_fअगरo_size(काष्ठा uart_port *port, पूर्णांक portnumber)
अणु
	पूर्णांक ctrl, loop = 0;
	पूर्णांक status;
	पूर्णांक fअगरosize;
	अचिन्हित दीर्घ flags;

	ctrl = UART_GET_CTRL(port);

	/*
	 * Enable the transceiver and रुको क्रम it to be पढ़ोy to send data.
	 * Clear पूर्णांकerrupts so that this process will not be बाह्यally
	 * पूर्णांकerrupted in the middle (which can cause the transceiver to
	 * drain prematurely).
	 */

	local_irq_save(flags);

	UART_PUT_CTRL(port, ctrl | UART_CTRL_TE);

	जबतक (!UART_TX_READY(UART_GET_STATUS(port)))
		loop++;

	/*
	 * Disable the transceiver so data isn't actually sent during the
	 * actual test.
	 */

	UART_PUT_CTRL(port, ctrl & ~(UART_CTRL_TE));

	fअगरosize = 1;
	UART_PUT_CHAR(port, 0);

	/*
	 * So दीर्घ as transmitting a अक्षरacter increments the tranceivier FIFO
	 * length the FIFO must be at least that big. These bytes will
	 * स्वतःmatically drain off of the FIFO.
	 */

	status = UART_GET_STATUS(port);
	जबतक (((status >> 20) & 0x3F) == fअगरosize) अणु
		fअगरosize++;
		UART_PUT_CHAR(port, 0);
		status = UART_GET_STATUS(port);
	पूर्ण

	fअगरosize--;

	UART_PUT_CTRL(port, ctrl);
	local_irq_restore(flags);

	अगर (fअगरosize == 0)
		fअगरosize = 1;

	वापस fअगरosize;
पूर्ण

अटल व्योम apbuart_flush_fअगरo(काष्ठा uart_port *port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < port->fअगरosize; i++)
		UART_GET_CHAR(port);
पूर्ण


/* ======================================================================== */
/* Console driver, अगर enabled                                               */
/* ======================================================================== */

#अगर_घोषित CONFIG_SERIAL_GRLIB_GAISLER_APBUART_CONSOLE

अटल व्योम apbuart_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	अचिन्हित पूर्णांक status;
	करो अणु
		status = UART_GET_STATUS(port);
	पूर्ण जबतक (!UART_TX_READY(status));
	UART_PUT_CHAR(port, ch);
पूर्ण

अटल व्योम
apbuart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_port *port = &grlib_apbuart_ports[co->index];
	अचिन्हित पूर्णांक status, old_cr, new_cr;

	/* First save the CR then disable the पूर्णांकerrupts */
	old_cr = UART_GET_CTRL(port);
	new_cr = old_cr & ~(UART_CTRL_RI | UART_CTRL_TI);
	UART_PUT_CTRL(port, new_cr);

	uart_console_ग_लिखो(port, s, count, apbuart_console_अक्षर_दो);

	/*
	 *      Finally, रुको क्रम transmitter to become empty
	 *      and restore the TCR
	 */
	करो अणु
		status = UART_GET_STATUS(port);
	पूर्ण जबतक (!UART_TX_READY(status));
	UART_PUT_CTRL(port, old_cr);
पूर्ण

अटल व्योम __init
apbuart_console_get_options(काष्ठा uart_port *port, पूर्णांक *baud,
			    पूर्णांक *parity, पूर्णांक *bits)
अणु
	अगर (UART_GET_CTRL(port) & (UART_CTRL_RE | UART_CTRL_TE)) अणु

		अचिन्हित पूर्णांक quot, status;
		status = UART_GET_STATUS(port);

		*parity = 'n';
		अगर (status & UART_CTRL_PE) अणु
			अगर ((status & UART_CTRL_PS) == 0)
				*parity = 'e';
			अन्यथा
				*parity = 'o';
		पूर्ण

		*bits = 8;
		quot = UART_GET_SCAL(port) / 8;
		*baud = port->uartclk / (16 * (quot + 1));
	पूर्ण
पूर्ण

अटल पूर्णांक __init apbuart_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port;
	पूर्णांक baud = 38400;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	pr_debug("apbuart_console_setup co=%p, co->index=%i, options=%s\n",
		 co, co->index, options);

	/*
	 * Check whether an invalid uart number has been specअगरied, and
	 * अगर so, search क्रम the first available port that करोes have
	 * console support.
	 */
	अगर (co->index >= grlib_apbuart_port_nr)
		co->index = 0;

	port = &grlib_apbuart_ports[co->index];

	spin_lock_init(&port->lock);

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	अन्यथा
		apbuart_console_get_options(port, &baud, &parity, &bits);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver grlib_apbuart_driver;

अटल काष्ठा console grlib_apbuart_console = अणु
	.name = "ttyS",
	.ग_लिखो = apbuart_console_ग_लिखो,
	.device = uart_console_device,
	.setup = apbuart_console_setup,
	.flags = CON_PRINTBUFFER,
	.index = -1,
	.data = &grlib_apbuart_driver,
पूर्ण;


अटल पूर्णांक grlib_apbuart_configure(व्योम);

अटल पूर्णांक __init apbuart_console_init(व्योम)
अणु
	अगर (grlib_apbuart_configure())
		वापस -ENODEV;
	रेजिस्टर_console(&grlib_apbuart_console);
	वापस 0;
पूर्ण

console_initcall(apbuart_console_init);

#घोषणा APBUART_CONSOLE	(&grlib_apbuart_console)
#अन्यथा
#घोषणा APBUART_CONSOLE	शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver grlib_apbuart_driver = अणु
	.owner = THIS_MODULE,
	.driver_name = "serial",
	.dev_name = "ttyS",
	.major = SERIAL_APBUART_MAJOR,
	.minor = SERIAL_APBUART_MINOR,
	.nr = UART_NR,
	.cons = APBUART_CONSOLE,
पूर्ण;


/* ======================================================================== */
/* OF Platक्रमm Driver                                                       */
/* ======================================================================== */

अटल पूर्णांक apbuart_probe(काष्ठा platक्रमm_device *op)
अणु
	पूर्णांक i;
	काष्ठा uart_port *port = शून्य;

	क्रम (i = 0; i < grlib_apbuart_port_nr; i++) अणु
		अगर (op->dev.of_node == grlib_apbuart_nodes[i])
			अवरोध;
	पूर्ण

	port = &grlib_apbuart_ports[i];
	port->dev = &op->dev;
	port->irq = op->archdata.irqs[0];

	uart_add_one_port(&grlib_apbuart_driver, (काष्ठा uart_port *) port);

	apbuart_flush_fअगरo((काष्ठा uart_port *) port);

	prपूर्णांकk(KERN_INFO "grlib-apbuart at 0x%llx, irq %d\n",
	       (अचिन्हित दीर्घ दीर्घ) port->mapbase, port->irq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id apbuart_match[] = अणु
	अणु
	 .name = "GAISLER_APBUART",
	 पूर्ण,
	अणु
	 .name = "01_00c",
	 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, apbuart_match);

अटल काष्ठा platक्रमm_driver grlib_apbuart_of_driver = अणु
	.probe = apbuart_probe,
	.driver = अणु
		.name = "grlib-apbuart",
		.of_match_table = apbuart_match,
	पूर्ण,
पूर्ण;


अटल पूर्णांक __init grlib_apbuart_configure(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक line = 0;

	क्रम_each_matching_node(np, apbuart_match) अणु
		स्थिर पूर्णांक *ampopts;
		स्थिर u32 *freq_hz;
		स्थिर काष्ठा amba_prom_रेजिस्टरs *regs;
		काष्ठा uart_port *port;
		अचिन्हित दीर्घ addr;

		ampopts = of_get_property(np, "ampopts", शून्य);
		अगर (ampopts && (*ampopts == 0))
			जारी; /* Ignore अगर used by another OS instance */
		regs = of_get_property(np, "reg", शून्य);
		/* Frequency of APB Bus is frequency of UART */
		freq_hz = of_get_property(np, "freq", शून्य);

		अगर (!regs || !freq_hz || (*freq_hz == 0))
			जारी;

		grlib_apbuart_nodes[line] = np;

		addr = regs->phys_addr;

		port = &grlib_apbuart_ports[line];

		port->mapbase = addr;
		port->membase = ioremap(addr, माप(काष्ठा grlib_apbuart_regs_map));
		port->irq = 0;
		port->iotype = UPIO_MEM;
		port->ops = &grlib_apbuart_ops;
		port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_GRLIB_GAISLER_APBUART_CONSOLE);
		port->flags = UPF_BOOT_AUTOCONF;
		port->line = line;
		port->uartclk = *freq_hz;
		port->fअगरosize = apbuart_scan_fअगरo_size((काष्ठा uart_port *) port, line);
		line++;

		/* We support maximum UART_NR uarts ... */
		अगर (line == UART_NR)
			अवरोध;
	पूर्ण

	grlib_apbuart_driver.nr = grlib_apbuart_port_nr = line;
	वापस line ? 0 : -ENODEV;
पूर्ण

अटल पूर्णांक __init grlib_apbuart_init(व्योम)
अणु
	पूर्णांक ret;

	/* Find all APBUARTS in device the tree and initialize their ports */
	ret = grlib_apbuart_configure();
	अगर (ret)
		वापस ret;

	prपूर्णांकk(KERN_INFO "Serial: GRLIB APBUART driver\n");

	ret = uart_रेजिस्टर_driver(&grlib_apbuart_driver);

	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: uart_register_driver failed (%i)\n",
		       __खाता__, ret);
		वापस ret;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&grlib_apbuart_of_driver);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR
		       "%s: platform_driver_register failed (%i)\n",
		       __खाता__, ret);
		uart_unरेजिस्टर_driver(&grlib_apbuart_driver);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास grlib_apbuart_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < grlib_apbuart_port_nr; i++)
		uart_हटाओ_one_port(&grlib_apbuart_driver,
				     &grlib_apbuart_ports[i]);

	uart_unरेजिस्टर_driver(&grlib_apbuart_driver);
	platक्रमm_driver_unरेजिस्टर(&grlib_apbuart_of_driver);
पूर्ण

module_init(grlib_apbuart_init);
module_निकास(grlib_apbuart_निकास);

MODULE_AUTHOR("Aeroflex Gaisler AB");
MODULE_DESCRIPTION("GRLIB APBUART serial driver");
MODULE_VERSION("2.1");
MODULE_LICENSE("GPL");
