<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ARC On-Chip(fpga) UART Driver
 *
 * Copyright (C) 2010-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * vineetg: July 10th 2012
 *  -Decoupled the driver from arch/arc
 *    +Using platक्रमm_get_resource() क्रम irq/membase (thx to bfin_uart.c)
 *    +Using early_platक्रमm_xxx() क्रम early console (thx to mach-shmobile/xxx)
 *
 * Vineetg: Aug 21st 2010
 *  -Is uart_tx_stopped() not करोne in tty ग_लिखो path as it has alपढ़ोy been
 *   taken care of, in serial core
 *
 * Vineetg: Aug 18th 2010
 *  -New Serial Core based ARC UART driver
 *  -Derived largely from blackfin driver albiet with some major tweaks
 *
 * TODO:
 *  -check अगर sysreq works
 */

#समावेश <linux/module.h>
#समावेश <linux/serial.h>
#समावेश <linux/console.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>

/*************************************
 * ARC UART Hardware Specs
 ************************************/
#घोषणा ARC_UART_TX_FIFO_SIZE  1

/*
 * UART Register set (this is not a Standards Compliant IP)
 * Also each reg is Word aligned, but only 8 bits wide
 */
#घोषणा R_ID0	0
#घोषणा R_ID1	4
#घोषणा R_ID2	8
#घोषणा R_ID3	12
#घोषणा R_DATA	16
#घोषणा R_STS	20
#घोषणा R_BAUDL	24
#घोषणा R_BAUDH	28

/* Bits क्रम UART Status Reg (R/W) */
#घोषणा RXIENB  0x04	/* Receive Interrupt Enable */
#घोषणा TXIENB  0x40	/* Transmit Interrupt Enable */

#घोषणा RXEMPTY 0x20	/* Receive FIFO Empty: No अक्षर receivede */
#घोषणा TXEMPTY 0x80	/* Transmit FIFO Empty, thus अक्षर can be written पूर्णांकo */

#घोषणा RXFULL  0x08	/* Receive FIFO full */
#घोषणा RXFULL1 0x10	/* Receive FIFO has space क्रम 1 अक्षर (tot space=4) */

#घोषणा RXFERR  0x01	/* Frame Error: Stop Bit not detected */
#घोषणा RXOERR  0x02	/* OverFlow Err: Char recv but RXFULL still set */

/* Uart bit fiddling helpers: lowest level */
#घोषणा RBASE(port, reg)      (port->membase + reg)
#घोषणा UART_REG_SET(u, r, v) ग_लिखोb((v), RBASE(u, r))
#घोषणा UART_REG_GET(u, r)    पढ़ोb(RBASE(u, r))

#घोषणा UART_REG_OR(u, r, v)  UART_REG_SET(u, r, UART_REG_GET(u, r) | (v))
#घोषणा UART_REG_CLR(u, r, v) UART_REG_SET(u, r, UART_REG_GET(u, r) & ~(v))

/* Uart bit fiddling helpers: API level */
#घोषणा UART_SET_DATA(uart, val)   UART_REG_SET(uart, R_DATA, val)
#घोषणा UART_GET_DATA(uart)        UART_REG_GET(uart, R_DATA)

#घोषणा UART_SET_BAUDH(uart, val)  UART_REG_SET(uart, R_BAUDH, val)
#घोषणा UART_SET_BAUDL(uart, val)  UART_REG_SET(uart, R_BAUDL, val)

#घोषणा UART_CLR_STATUS(uart, val) UART_REG_CLR(uart, R_STS, val)
#घोषणा UART_GET_STATUS(uart)      UART_REG_GET(uart, R_STS)

#घोषणा UART_ALL_IRQ_DISABLE(uart) UART_REG_CLR(uart, R_STS, RXIENB|TXIENB)
#घोषणा UART_RX_IRQ_DISABLE(uart)  UART_REG_CLR(uart, R_STS, RXIENB)
#घोषणा UART_TX_IRQ_DISABLE(uart)  UART_REG_CLR(uart, R_STS, TXIENB)

#घोषणा UART_ALL_IRQ_ENABLE(uart)  UART_REG_OR(uart, R_STS, RXIENB|TXIENB)
#घोषणा UART_RX_IRQ_ENABLE(uart)   UART_REG_OR(uart, R_STS, RXIENB)
#घोषणा UART_TX_IRQ_ENABLE(uart)   UART_REG_OR(uart, R_STS, TXIENB)

#घोषणा ARC_SERIAL_DEV_NAME	"ttyARC"

काष्ठा arc_uart_port अणु
	काष्ठा uart_port port;
	अचिन्हित दीर्घ baud;
पूर्ण;

#घोषणा to_arc_port(uport)  container_of(uport, काष्ठा arc_uart_port, port)

अटल काष्ठा arc_uart_port arc_uart_ports[CONFIG_SERIAL_ARC_NR_PORTS];

#अगर_घोषित CONFIG_SERIAL_ARC_CONSOLE
अटल काष्ठा console arc_console;
#पूर्ण_अगर

#घोषणा DRIVER_NAME	"arc-uart"

अटल काष्ठा uart_driver arc_uart_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= DRIVER_NAME,
	.dev_name	= ARC_SERIAL_DEV_NAME,
	.major		= 0,
	.minor		= 0,
	.nr		= CONFIG_SERIAL_ARC_NR_PORTS,
#अगर_घोषित CONFIG_SERIAL_ARC_CONSOLE
	.cons		= &arc_console,
#पूर्ण_अगर
पूर्ण;

अटल व्योम arc_serial_stop_rx(काष्ठा uart_port *port)
अणु
	UART_RX_IRQ_DISABLE(port);
पूर्ण

अटल व्योम arc_serial_stop_tx(काष्ठा uart_port *port)
अणु
	जबतक (!(UART_GET_STATUS(port) & TXEMPTY))
		cpu_relax();

	UART_TX_IRQ_DISABLE(port);
पूर्ण

/*
 * Return TIOCSER_TEMT when transmitter is not busy.
 */
अटल अचिन्हित पूर्णांक arc_serial_tx_empty(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक stat;

	stat = UART_GET_STATUS(port);
	अगर (stat & TXEMPTY)
		वापस TIOCSER_TEMT;

	वापस 0;
पूर्ण

/*
 * Driver पूर्णांकernal routine, used by both tty(serial core) as well as tx-isr
 *  -Called under spinlock in either हालs
 *  -also tty->stopped has alपढ़ोy been checked
 *     = by uart_start( ) beक्रमe calling us
 *     = tx_ist checks that too beक्रमe calling
 */
अटल व्योम arc_serial_tx_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	पूर्णांक sent = 0;
	अचिन्हित अक्षर ch;

	अगर (unlikely(port->x_अक्षर)) अणु
		UART_SET_DATA(port, port->x_अक्षर);
		port->icount.tx++;
		port->x_अक्षर = 0;
		sent = 1;
	पूर्ण अन्यथा अगर (!uart_circ_empty(xmit)) अणु
		ch = xmit->buf[xmit->tail];
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		जबतक (!(UART_GET_STATUS(port) & TXEMPTY))
			cpu_relax();
		UART_SET_DATA(port, ch);
		sent = 1;
	पूर्ण

	/*
	 * If num अक्षरs in xmit buffer are too few, ask tty layer क्रम more.
	 * By Hard ISR to schedule processing in software पूर्णांकerrupt part
	 */
	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (sent)
		UART_TX_IRQ_ENABLE(port);
पूर्ण

/*
 * port is locked and पूर्णांकerrupts are disabled
 * uart_start( ) calls us under the port spinlock irqsave
 */
अटल व्योम arc_serial_start_tx(काष्ठा uart_port *port)
अणु
	arc_serial_tx_अक्षरs(port);
पूर्ण

अटल व्योम arc_serial_rx_अक्षरs(काष्ठा uart_port *port, अचिन्हित पूर्णांक status)
अणु
	अचिन्हित पूर्णांक ch, flg = 0;

	/*
	 * UART has 4 deep RX-FIFO. Driver's recongnition of this fact
	 * is very subtle. Here's how ...
	 * Upon getting a RX-Intr, such that RX-EMPTY=0, meaning data available,
	 * driver पढ़ोs the DATA Reg and keeps करोing that in a loop, until
	 * RX-EMPTY=1. Multiple अक्षरs being avail, with a single Interrupt,
	 * beक्रमe RX-EMPTY=0, implies some sort of buffering going on in the
	 * controller, which is indeed the Rx-FIFO.
	 */
	करो अणु
		/*
		 * This could be an Rx Intr क्रम err (no data),
		 * so check err and clear that Intr first
		 */
		अगर (unlikely(status & (RXOERR | RXFERR))) अणु
			अगर (status & RXOERR) अणु
				port->icount.overrun++;
				flg = TTY_OVERRUN;
				UART_CLR_STATUS(port, RXOERR);
			पूर्ण

			अगर (status & RXFERR) अणु
				port->icount.frame++;
				flg = TTY_FRAME;
				UART_CLR_STATUS(port, RXFERR);
			पूर्ण
		पूर्ण अन्यथा
			flg = TTY_NORMAL;

		अगर (status & RXEMPTY)
			जारी;

		ch = UART_GET_DATA(port);
		port->icount.rx++;

		अगर (!(uart_handle_sysrq_अक्षर(port, ch)))
			uart_insert_अक्षर(port, status, RXOERR, ch, flg);

		tty_flip_buffer_push(&port->state->port);
	पूर्ण जबतक (!((status = UART_GET_STATUS(port)) & RXEMPTY));
पूर्ण

/*
 * A note on the Interrupt handling state machine of this driver
 *
 * kernel prपूर्णांकk ग_लिखोs funnel thru the console driver framework and in order
 * to keep things simple as well as efficient, it ग_लिखोs to UART in polled
 * mode, in one shot, and निकासs.
 *
 * OTOH, Userland output (via tty layer), uses पूर्णांकerrupt based ग_लिखोs as there
 * can be undeterministic delay between अक्षर ग_लिखोs.
 *
 * Thus Rx-पूर्णांकerrupts are always enabled, जबतक tx-पूर्णांकerrupts are by शेष
 * disabled.
 *
 * When tty has some data to send out, serial core calls driver's start_tx
 * which
 *   -checks-अगर-tty-buffer-has-अक्षर-to-send
 *   -ग_लिखोs-data-to-uart
 *   -enable-tx-पूर्णांकr
 *
 * Once data bits are pushed out, controller उठाओs the Tx-room-avail-Interrupt.
 * The first thing Tx ISR करोes is disable further Tx पूर्णांकerrupts (as this could
 * be the last अक्षर to send, beक्रमe settling करोwn पूर्णांकo the quiet polled mode).
 * It then calls the exact routine used by tty layer ग_लिखो to send out any
 * more अक्षर in tty buffer. In हाल of sending, it re-enables Tx-पूर्णांकr. In हाल
 * of no data, it reमुख्यs disabled.
 * This is how the transmit state machine is dynamically चयनed on/off
 */

अटल irqवापस_t arc_serial_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	अचिन्हित पूर्णांक status;

	status = UART_GET_STATUS(port);

	/*
	 * Single IRQ क्रम both Rx (data available) Tx (room available) Interrupt
	 * notअगरications from the UART Controller.
	 * To demultiplex between the two, we check the relevant bits
	 */
	अगर (status & RXIENB) अणु

		/* alपढ़ोy in ISR, no need of xx_irqsave */
		spin_lock(&port->lock);
		arc_serial_rx_अक्षरs(port, status);
		spin_unlock(&port->lock);
	पूर्ण

	अगर ((status & TXIENB) && (status & TXEMPTY)) अणु

		/* Unconditionally disable further Tx-Interrupts.
		 * will be enabled by tx_अक्षरs() अगर needed.
		 */
		UART_TX_IRQ_DISABLE(port);

		spin_lock(&port->lock);

		अगर (!uart_tx_stopped(port))
			arc_serial_tx_अक्षरs(port);

		spin_unlock(&port->lock);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक arc_serial_get_mctrl(काष्ठा uart_port *port)
अणु
	/*
	 * Pretend we have a Modem status reg and following bits are
	 *  always set, to satअगरy the serial core state machine
	 *  (DSR) Data Set Ready
	 *  (CTS) Clear To Send
	 *  (CAR) Carrier Detect
	 */
	वापस TIOCM_CTS | TIOCM_DSR | TIOCM_CAR;
पूर्ण

अटल व्योम arc_serial_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	/* MCR not present */
पूर्ण

अटल व्योम arc_serial_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	/* ARC UART करोesn't support sending Break संकेत */
पूर्ण

अटल पूर्णांक arc_serial_startup(काष्ठा uart_port *port)
अणु
	/* Beक्रमe we hook up the ISR, Disable all UART Interrupts */
	UART_ALL_IRQ_DISABLE(port);

	अगर (request_irq(port->irq, arc_serial_isr, 0, "arc uart rx-tx", port)) अणु
		dev_warn(port->dev, "Unable to attach ARC UART intr\n");
		वापस -EBUSY;
	पूर्ण

	UART_RX_IRQ_ENABLE(port); /* Only Rx IRQ enabled to begin with */

	वापस 0;
पूर्ण

/* This is not really needed */
अटल व्योम arc_serial_shutकरोwn(काष्ठा uart_port *port)
अणु
	मुक्त_irq(port->irq, port);
पूर्ण

अटल व्योम
arc_serial_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *new,
		       काष्ठा ktermios *old)
अणु
	काष्ठा arc_uart_port *uart = to_arc_port(port);
	अचिन्हित पूर्णांक baud, uartl, uarth, hw_val;
	अचिन्हित दीर्घ flags;

	/*
	 * Use the generic handler so that any specially encoded baud rates
	 * such as SPD_xx flags or "%B0" can be handled
	 * Max Baud I suppose will not be more than current 115K * 4
	 * Formula क्रम ARC UART is: hw-val = ((CLK/(BAUD*4)) -1)
	 * spपढ़ो over two 8-bit रेजिस्टरs
	 */
	baud = uart_get_baud_rate(port, new, old, 0, 460800);

	hw_val = port->uartclk / (uart->baud * 4) - 1;
	uartl = hw_val & 0xFF;
	uarth = (hw_val >> 8) & 0xFF;

	spin_lock_irqsave(&port->lock, flags);

	UART_ALL_IRQ_DISABLE(port);

	UART_SET_BAUDL(port, uartl);
	UART_SET_BAUDH(port, uarth);

	UART_RX_IRQ_ENABLE(port);

	/*
	 * UART करोesn't support Parity/Hardware Flow Control;
	 * Only supports 8N1 अक्षरacter size
	 */
	new->c_cflag &= ~(CMSPAR|CRTSCTS|CSIZE);
	new->c_cflag |= CS8;

	अगर (old)
		tty_termios_copy_hw(new, old);

	/* Don't reग_लिखो B0 */
	अगर (tty_termios_baud_rate(new))
		tty_termios_encode_baud_rate(new, baud, baud);

	uart_update_समयout(port, new->c_cflag, baud);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *arc_serial_type(काष्ठा uart_port *port)
अणु
	वापस port->type == PORT_ARC ? DRIVER_NAME : शून्य;
पूर्ण

अटल व्योम arc_serial_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक arc_serial_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

/*
 * Verअगरy the new serial_काष्ठा (क्रम TIOCSSERIAL).
 */
अटल पूर्णांक
arc_serial_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	अगर (port->type != PORT_UNKNOWN && ser->type != PORT_ARC)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * Configure/स्वतःconfigure the port.
 */
अटल व्योम arc_serial_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE)
		port->type = PORT_ARC;
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL

अटल व्योम arc_serial_poll_अक्षर_दो(काष्ठा uart_port *port, अचिन्हित अक्षर chr)
अणु
	जबतक (!(UART_GET_STATUS(port) & TXEMPTY))
		cpu_relax();

	UART_SET_DATA(port, chr);
पूर्ण

अटल पूर्णांक arc_serial_poll_अक्षर_लो(काष्ठा uart_port *port)
अणु
	अचिन्हित अक्षर chr;

	जबतक (!(UART_GET_STATUS(port) & RXEMPTY))
		cpu_relax();

	chr = UART_GET_DATA(port);
	वापस chr;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा uart_ops arc_serial_pops = अणु
	.tx_empty	= arc_serial_tx_empty,
	.set_mctrl	= arc_serial_set_mctrl,
	.get_mctrl	= arc_serial_get_mctrl,
	.stop_tx	= arc_serial_stop_tx,
	.start_tx	= arc_serial_start_tx,
	.stop_rx	= arc_serial_stop_rx,
	.अवरोध_ctl	= arc_serial_अवरोध_ctl,
	.startup	= arc_serial_startup,
	.shutकरोwn	= arc_serial_shutकरोwn,
	.set_termios	= arc_serial_set_termios,
	.type		= arc_serial_type,
	.release_port	= arc_serial_release_port,
	.request_port	= arc_serial_request_port,
	.config_port	= arc_serial_config_port,
	.verअगरy_port	= arc_serial_verअगरy_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_put_अक्षर = arc_serial_poll_अक्षर_दो,
	.poll_get_अक्षर = arc_serial_poll_अक्षर_लो,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_ARC_CONSOLE

अटल पूर्णांक arc_serial_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (co->index < 0 || co->index >= CONFIG_SERIAL_ARC_NR_PORTS)
		वापस -ENODEV;

	/*
	 * The uart port backing the console (e.g. ttyARC1) might not have been
	 * init yet. If so, defer the console setup to after the port.
	 */
	port = &arc_uart_ports[co->index].port;
	अगर (!port->membase)
		वापस -ENODEV;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	/*
	 * Serial core will call port->ops->set_termios( )
	 * which will set the baud reg
	 */
	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल व्योम arc_serial_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	जबतक (!(UART_GET_STATUS(port) & TXEMPTY))
		cpu_relax();

	UART_SET_DATA(port, (अचिन्हित अक्षर)ch);
पूर्ण

/*
 * Interrupts are disabled on entering
 */
अटल व्योम arc_serial_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				     अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_port *port = &arc_uart_ports[co->index].port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	uart_console_ग_लिखो(port, s, count, arc_serial_console_अक्षर_दो);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल काष्ठा console arc_console = अणु
	.name	= ARC_SERIAL_DEV_NAME,
	.ग_लिखो	= arc_serial_console_ग_लिखो,
	.device	= uart_console_device,
	.setup	= arc_serial_console_setup,
	.flags	= CON_PRINTBUFFER,
	.index	= -1,
	.data	= &arc_uart_driver
पूर्ण;

अटल व्योम arc_early_serial_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s,
				   अचिन्हित पूर्णांक n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	uart_console_ग_लिखो(&dev->port, s, n, arc_serial_console_अक्षर_दो);
पूर्ण

अटल पूर्णांक __init arc_early_console_setup(काष्ठा earlycon_device *dev,
					  स्थिर अक्षर *opt)
अणु
	काष्ठा uart_port *port = &dev->port;
	अचिन्हित पूर्णांक l, h, hw_val;

	अगर (!dev->port.membase)
		वापस -ENODEV;

	hw_val = port->uartclk / (dev->baud * 4) - 1;
	l = hw_val & 0xFF;
	h = (hw_val >> 8) & 0xFF;

	UART_SET_BAUDL(port, l);
	UART_SET_BAUDH(port, h);

	dev->con->ग_लिखो = arc_early_serial_ग_लिखो;
	वापस 0;
पूर्ण
OF_EARLYCON_DECLARE(arc_uart, "snps,arc-uart", arc_early_console_setup);

#पूर्ण_अगर	/* CONFIG_SERIAL_ARC_CONSOLE */

अटल पूर्णांक arc_serial_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा arc_uart_port *uart;
	काष्ठा uart_port *port;
	पूर्णांक dev_id;
	u32 val;

	/* no device tree device */
	अगर (!np)
		वापस -ENODEV;

	dev_id = of_alias_get_id(np, "serial");
	अगर (dev_id < 0)
		dev_id = 0;

	अगर (dev_id >= ARRAY_SIZE(arc_uart_ports)) अणु
		dev_err(&pdev->dev, "serial%d out of range\n", dev_id);
		वापस -EINVAL;
	पूर्ण

	uart = &arc_uart_ports[dev_id];
	port = &uart->port;

	अगर (of_property_पढ़ो_u32(np, "clock-frequency", &val)) अणु
		dev_err(&pdev->dev, "clock-frequency property NOTset\n");
		वापस -EINVAL;
	पूर्ण
	port->uartclk = val;

	अगर (of_property_पढ़ो_u32(np, "current-speed", &val)) अणु
		dev_err(&pdev->dev, "current-speed property NOT set\n");
		वापस -EINVAL;
	पूर्ण
	uart->baud = val;

	port->membase = of_iomap(np, 0);
	अगर (!port->membase)
		/* No poपूर्णांक of dev_err since UART itself is hosed here */
		वापस -ENXIO;

	port->irq = irq_of_parse_and_map(np, 0);

	port->dev = &pdev->dev;
	port->iotype = UPIO_MEM;
	port->flags = UPF_BOOT_AUTOCONF;
	port->line = dev_id;
	port->ops = &arc_serial_pops;
	port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_ARC_CONSOLE);

	port->fअगरosize = ARC_UART_TX_FIFO_SIZE;

	/*
	 * uart_insert_अक्षर( ) uses it in decideding whether to ignore a
	 * अक्षर or not. Explicitly setting it here, हटाओs the subtelty
	 */
	port->ignore_status_mask = 0;

	वापस uart_add_one_port(&arc_uart_driver, &arc_uart_ports[dev_id].port);
पूर्ण

अटल पूर्णांक arc_serial_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	/* This will never be called */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id arc_uart_dt_ids[] = अणु
	अणु .compatible = "snps,arc-uart" पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, arc_uart_dt_ids);

अटल काष्ठा platक्रमm_driver arc_platक्रमm_driver = अणु
	.probe = arc_serial_probe,
	.हटाओ = arc_serial_हटाओ,
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table  = arc_uart_dt_ids,
	 पूर्ण,
पूर्ण;

अटल पूर्णांक __init arc_serial_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&arc_uart_driver);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&arc_platक्रमm_driver);
	अगर (ret)
		uart_unरेजिस्टर_driver(&arc_uart_driver);

	वापस ret;
पूर्ण

अटल व्योम __निकास arc_serial_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&arc_platक्रमm_driver);
	uart_unरेजिस्टर_driver(&arc_uart_driver);
पूर्ण

module_init(arc_serial_init);
module_निकास(arc_serial_निकास);

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_AUTHOR("Vineet Gupta");
MODULE_DESCRIPTION("ARC(Synopsys) On-Chip(fpga) serial driver");
