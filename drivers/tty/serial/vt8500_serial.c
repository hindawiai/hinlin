<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2010 Alexey Charkov <alअक्षरk@gmail.com>
 *
 * Based on msm_serial.c, which is:
 * Copyright (C) 2007 Google, Inc.
 * Author: Robert Love <rlove@google.com>
 */

#समावेश <linux/hrसमयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/err.h>

/*
 * UART Register offsets
 */

#घोषणा VT8500_URTDR		0x0000	/* Transmit data */
#घोषणा VT8500_URRDR		0x0004	/* Receive data */
#घोषणा VT8500_URDIV		0x0008	/* Clock/Baud rate भागisor */
#घोषणा VT8500_URLCR		0x000C	/* Line control */
#घोषणा VT8500_URICR		0x0010	/* IrDA control */
#घोषणा VT8500_URIER		0x0014	/* Interrupt enable */
#घोषणा VT8500_URISR		0x0018	/* Interrupt status */
#घोषणा VT8500_URUSR		0x001c	/* UART status */
#घोषणा VT8500_URFCR		0x0020	/* FIFO control */
#घोषणा VT8500_URFIDX		0x0024	/* FIFO index */
#घोषणा VT8500_URBKR		0x0028	/* Break संकेत count */
#घोषणा VT8500_URTOD		0x002c	/* Time out भागisor */
#घोषणा VT8500_TXFIFO		0x1000	/* Transmit FIFO (16x8) */
#घोषणा VT8500_RXFIFO		0x1020	/* Receive FIFO (16x10) */

/*
 * Interrupt enable and status bits
 */

#घोषणा TXDE	(1 << 0)	/* Tx Data empty */
#घोषणा RXDF	(1 << 1)	/* Rx Data full */
#घोषणा TXFAE	(1 << 2)	/* Tx FIFO almost empty */
#घोषणा TXFE	(1 << 3)	/* Tx FIFO empty */
#घोषणा RXFAF	(1 << 4)	/* Rx FIFO almost full */
#घोषणा RXFF	(1 << 5)	/* Rx FIFO full */
#घोषणा TXUDR	(1 << 6)	/* Tx underrun */
#घोषणा RXOVER	(1 << 7)	/* Rx overrun */
#घोषणा PER	(1 << 8)	/* Parity error */
#घोषणा FER	(1 << 9)	/* Frame error */
#घोषणा TCTS	(1 << 10)	/* Toggle of CTS */
#घोषणा RXTOUT	(1 << 11)	/* Rx समयout */
#घोषणा BKDONE	(1 << 12)	/* Break संकेत करोne */
#घोषणा ERR	(1 << 13)	/* AHB error response */

#घोषणा RX_FIFO_INTS	(RXFAF | RXFF | RXOVER | PER | FER | RXTOUT)
#घोषणा TX_FIFO_INTS	(TXFAE | TXFE | TXUDR)

/*
 * Line control bits
 */

#घोषणा VT8500_TXEN	(1 << 0)	/* Enable transmit logic */
#घोषणा VT8500_RXEN	(1 << 1)	/* Enable receive logic */
#घोषणा VT8500_CS8	(1 << 2)	/* 8-bit data length (vs. 7-bit) */
#घोषणा VT8500_CSTOPB	(1 << 3)	/* 2 stop bits (vs. 1) */
#घोषणा VT8500_PARENB	(1 << 4)	/* Enable parity */
#घोषणा VT8500_PARODD	(1 << 5)	/* Odd parity (vs. even) */
#घोषणा VT8500_RTS	(1 << 6)	/* Ready to send */
#घोषणा VT8500_LOOPBK	(1 << 7)	/* Enable पूर्णांकernal loopback */
#घोषणा VT8500_DMA	(1 << 8)	/* Enable DMA mode (needs FIFO) */
#घोषणा VT8500_BREAK	(1 << 9)	/* Initiate अवरोध संकेत */
#घोषणा VT8500_PSLVERR	(1 << 10)	/* APB error upon empty RX FIFO पढ़ो */
#घोषणा VT8500_SWRTSCTS	(1 << 11)	/* Software-controlled RTS/CTS */

/*
 * Capability flags (driver-पूर्णांकernal)
 */

#घोषणा VT8500_HAS_SWRTSCTS_SWITCH	(1 << 1)

#घोषणा VT8500_RECOMMENDED_CLK		12000000
#घोषणा VT8500_OVERSAMPLING_DIVISOR	13
#घोषणा VT8500_MAX_PORTS	6

काष्ठा vt8500_port अणु
	काष्ठा uart_port	uart;
	अक्षर			name[16];
	काष्ठा clk		*clk;
	अचिन्हित पूर्णांक		clk_preभागisor;
	अचिन्हित पूर्णांक		ier;
	अचिन्हित पूर्णांक		vt8500_uart_flags;
पूर्ण;

/*
 * we use this variable to keep track of which ports
 * have been allocated as we can't use pdev->id in
 * devicetree
 */
अटल DECLARE_BITMAP(vt8500_ports_in_use, VT8500_MAX_PORTS);

अटल अंतरभूत व्योम vt8500_ग_लिखो(काष्ठा uart_port *port, अचिन्हित पूर्णांक val,
			     अचिन्हित पूर्णांक off)
अणु
	ग_लिखोl(val, port->membase + off);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक vt8500_पढ़ो(काष्ठा uart_port *port, अचिन्हित पूर्णांक off)
अणु
	वापस पढ़ोl(port->membase + off);
पूर्ण

अटल व्योम vt8500_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा vt8500_port *vt8500_port = container_of(port,
						       काष्ठा vt8500_port,
						       uart);

	vt8500_port->ier &= ~TX_FIFO_INTS;
	vt8500_ग_लिखो(port, vt8500_port->ier, VT8500_URIER);
पूर्ण

अटल व्योम vt8500_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा vt8500_port *vt8500_port = container_of(port,
						       काष्ठा vt8500_port,
						       uart);

	vt8500_port->ier &= ~RX_FIFO_INTS;
	vt8500_ग_लिखो(port, vt8500_port->ier, VT8500_URIER);
पूर्ण

अटल व्योम vt8500_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा vt8500_port *vt8500_port = container_of(port,
						       काष्ठा vt8500_port,
						       uart);

	vt8500_port->ier |= TCTS;
	vt8500_ग_लिखो(port, vt8500_port->ier, VT8500_URIER);
पूर्ण

अटल व्योम handle_rx(काष्ठा uart_port *port)
अणु
	काष्ठा tty_port *tport = &port->state->port;

	/*
	 * Handle overrun
	 */
	अगर ((vt8500_पढ़ो(port, VT8500_URISR) & RXOVER)) अणु
		port->icount.overrun++;
		tty_insert_flip_अक्षर(tport, 0, TTY_OVERRUN);
	पूर्ण

	/* and now the मुख्य RX loop */
	जबतक (vt8500_पढ़ो(port, VT8500_URFIDX) & 0x1f00) अणु
		अचिन्हित पूर्णांक c;
		अक्षर flag = TTY_NORMAL;

		c = पढ़ोw(port->membase + VT8500_RXFIFO) & 0x3ff;

		/* Mask conditions we're ignorning. */
		c &= ~port->पढ़ो_status_mask;

		अगर (c & FER) अणु
			port->icount.frame++;
			flag = TTY_FRAME;
		पूर्ण अन्यथा अगर (c & PER) अणु
			port->icount.parity++;
			flag = TTY_PARITY;
		पूर्ण
		port->icount.rx++;

		अगर (!uart_handle_sysrq_अक्षर(port, c))
			tty_insert_flip_अक्षर(tport, c, flag);
	पूर्ण

	tty_flip_buffer_push(tport);
पूर्ण

अटल व्योम handle_tx(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;

	अगर (port->x_अक्षर) अणु
		ग_लिखोb(port->x_अक्षर, port->membase + VT8500_TXFIFO);
		port->icount.tx++;
		port->x_अक्षर = 0;
	पूर्ण
	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		vt8500_stop_tx(port);
		वापस;
	पूर्ण

	जबतक ((vt8500_पढ़ो(port, VT8500_URFIDX) & 0x1f) < 16) अणु
		अगर (uart_circ_empty(xmit))
			अवरोध;

		ग_लिखोb(xmit->buf[xmit->tail], port->membase + VT8500_TXFIFO);

		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (uart_circ_empty(xmit))
		vt8500_stop_tx(port);
पूर्ण

अटल व्योम vt8500_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा vt8500_port *vt8500_port = container_of(port,
						       काष्ठा vt8500_port,
						       uart);

	vt8500_port->ier &= ~TX_FIFO_INTS;
	vt8500_ग_लिखो(port, vt8500_port->ier, VT8500_URIER);
	handle_tx(port);
	vt8500_port->ier |= TX_FIFO_INTS;
	vt8500_ग_लिखो(port, vt8500_port->ier, VT8500_URIER);
पूर्ण

अटल व्योम handle_delta_cts(काष्ठा uart_port *port)
अणु
	port->icount.cts++;
	wake_up_पूर्णांकerruptible(&port->state->port.delta_msr_रुको);
पूर्ण

अटल irqवापस_t vt8500_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	अचिन्हित दीर्घ isr;

	spin_lock(&port->lock);
	isr = vt8500_पढ़ो(port, VT8500_URISR);

	/* Acknowledge active status bits */
	vt8500_ग_लिखो(port, isr, VT8500_URISR);

	अगर (isr & RX_FIFO_INTS)
		handle_rx(port);
	अगर (isr & TX_FIFO_INTS)
		handle_tx(port);
	अगर (isr & TCTS)
		handle_delta_cts(port);

	spin_unlock(&port->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक vt8500_tx_empty(काष्ठा uart_port *port)
अणु
	वापस (vt8500_पढ़ो(port, VT8500_URFIDX) & 0x1f) < 16 ?
						TIOCSER_TEMT : 0;
पूर्ण

अटल अचिन्हित पूर्णांक vt8500_get_mctrl(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक usr;

	usr = vt8500_पढ़ो(port, VT8500_URUSR);
	अगर (usr & (1 << 4))
		वापस TIOCM_CTS;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम vt8500_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	अचिन्हित पूर्णांक lcr = vt8500_पढ़ो(port, VT8500_URLCR);

	अगर (mctrl & TIOCM_RTS)
		lcr |= VT8500_RTS;
	अन्यथा
		lcr &= ~VT8500_RTS;

	vt8500_ग_लिखो(port, lcr, VT8500_URLCR);
पूर्ण

अटल व्योम vt8500_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_ctl)
अणु
	अगर (अवरोध_ctl)
		vt8500_ग_लिखो(port,
			     vt8500_पढ़ो(port, VT8500_URLCR) | VT8500_BREAK,
			     VT8500_URLCR);
पूर्ण

अटल पूर्णांक vt8500_set_baud_rate(काष्ठा uart_port *port, अचिन्हित पूर्णांक baud)
अणु
	काष्ठा vt8500_port *vt8500_port =
			container_of(port, काष्ठा vt8500_port, uart);
	अचिन्हित दीर्घ भाग;
	अचिन्हित पूर्णांक loops = 1000;

	भाग = ((vt8500_port->clk_preभागisor - 1) & 0xf) << 16;
	भाग |= (uart_get_भागisor(port, baud) - 1) & 0x3ff;

	/* Effective baud rate */
	baud = port->uartclk / 16 / ((भाग & 0x3ff) + 1);

	जबतक ((vt8500_पढ़ो(port, VT8500_URUSR) & (1 << 5)) && --loops)
		cpu_relax();

	vt8500_ग_लिखो(port, भाग, VT8500_URDIV);

	/* Break संकेत timing depends on baud rate, update accordingly */
	vt8500_ग_लिखो(port, mult_frac(baud, 4096, 1000000), VT8500_URBKR);

	वापस baud;
पूर्ण

अटल पूर्णांक vt8500_startup(काष्ठा uart_port *port)
अणु
	काष्ठा vt8500_port *vt8500_port =
			container_of(port, काष्ठा vt8500_port, uart);
	पूर्णांक ret;

	snम_लिखो(vt8500_port->name, माप(vt8500_port->name),
		 "vt8500_serial%d", port->line);

	ret = request_irq(port->irq, vt8500_irq, IRQF_TRIGGER_HIGH,
			  vt8500_port->name, port);
	अगर (unlikely(ret))
		वापस ret;

	vt8500_ग_लिखो(port, 0x03, VT8500_URLCR);	/* enable TX & RX */

	वापस 0;
पूर्ण

अटल व्योम vt8500_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा vt8500_port *vt8500_port =
			container_of(port, काष्ठा vt8500_port, uart);

	vt8500_port->ier = 0;

	/* disable पूर्णांकerrupts and FIFOs */
	vt8500_ग_लिखो(&vt8500_port->uart, 0, VT8500_URIER);
	vt8500_ग_लिखो(&vt8500_port->uart, 0x880, VT8500_URFCR);
	मुक्त_irq(port->irq, port);
पूर्ण

अटल व्योम vt8500_set_termios(काष्ठा uart_port *port,
			       काष्ठा ktermios *termios,
			       काष्ठा ktermios *old)
अणु
	काष्ठा vt8500_port *vt8500_port =
			container_of(port, काष्ठा vt8500_port, uart);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, lcr;
	अचिन्हित पूर्णांक loops = 1000;

	spin_lock_irqsave(&port->lock, flags);

	/* calculate and set baud rate */
	baud = uart_get_baud_rate(port, termios, old, 900, 921600);
	baud = vt8500_set_baud_rate(port, baud);
	अगर (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);

	/* calculate parity */
	lcr = vt8500_पढ़ो(&vt8500_port->uart, VT8500_URLCR);
	lcr &= ~(VT8500_PARENB | VT8500_PARODD);
	अगर (termios->c_cflag & PARENB) अणु
		lcr |= VT8500_PARENB;
		termios->c_cflag &= ~CMSPAR;
		अगर (termios->c_cflag & PARODD)
			lcr |= VT8500_PARODD;
	पूर्ण

	/* calculate bits per अक्षर */
	lcr &= ~VT8500_CS8;
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS7:
		अवरोध;
	हाल CS8:
	शेष:
		lcr |= VT8500_CS8;
		termios->c_cflag &= ~CSIZE;
		termios->c_cflag |= CS8;
		अवरोध;
	पूर्ण

	/* calculate stop bits */
	lcr &= ~VT8500_CSTOPB;
	अगर (termios->c_cflag & CSTOPB)
		lcr |= VT8500_CSTOPB;

	lcr &= ~VT8500_SWRTSCTS;
	अगर (vt8500_port->vt8500_uart_flags & VT8500_HAS_SWRTSCTS_SWITCH)
		lcr |= VT8500_SWRTSCTS;

	/* set parity, bits per अक्षर, and stop bit */
	vt8500_ग_लिखो(&vt8500_port->uart, lcr, VT8500_URLCR);

	/* Configure status bits to ignore based on termio flags. */
	port->पढ़ो_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		port->पढ़ो_status_mask = FER | PER;

	uart_update_समयout(port, termios->c_cflag, baud);

	/* Reset FIFOs */
	vt8500_ग_लिखो(&vt8500_port->uart, 0x88c, VT8500_URFCR);
	जबतक ((vt8500_पढ़ो(&vt8500_port->uart, VT8500_URFCR) & 0xc)
							&& --loops)
		cpu_relax();

	/* Every possible FIFO-related पूर्णांकerrupt */
	vt8500_port->ier = RX_FIFO_INTS | TX_FIFO_INTS;

	/*
	 * CTS flow control
	 */
	अगर (UART_ENABLE_MS(&vt8500_port->uart, termios->c_cflag))
		vt8500_port->ier |= TCTS;

	vt8500_ग_लिखो(&vt8500_port->uart, 0x881, VT8500_URFCR);
	vt8500_ग_लिखो(&vt8500_port->uart, vt8500_port->ier, VT8500_URIER);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *vt8500_type(काष्ठा uart_port *port)
अणु
	काष्ठा vt8500_port *vt8500_port =
			container_of(port, काष्ठा vt8500_port, uart);
	वापस vt8500_port->name;
पूर्ण

अटल व्योम vt8500_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक vt8500_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम vt8500_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	port->type = PORT_VT8500;
पूर्ण

अटल पूर्णांक vt8500_verअगरy_port(काष्ठा uart_port *port,
			      काष्ठा serial_काष्ठा *ser)
अणु
	अगर (unlikely(ser->type != PORT_UNKNOWN && ser->type != PORT_VT8500))
		वापस -EINVAL;
	अगर (unlikely(port->irq != ser->irq))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा vt8500_port *vt8500_uart_ports[VT8500_MAX_PORTS];
अटल काष्ठा uart_driver vt8500_uart_driver;

#अगर_घोषित CONFIG_SERIAL_VT8500_CONSOLE

अटल व्योम रुको_क्रम_xmitr(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक status, पंचांगout = 10000;

	/* Wait up to 10ms क्रम the अक्षरacter(s) to be sent. */
	करो अणु
		status = vt8500_पढ़ो(port, VT8500_URFIDX);

		अगर (--पंचांगout == 0)
			अवरोध;
		udelay(1);
	पूर्ण जबतक (status & 0x10);
पूर्ण

अटल व्योम vt8500_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	रुको_क्रम_xmitr(port);
	ग_लिखोb(c, port->membase + VT8500_TXFIFO);
पूर्ण

अटल व्योम vt8500_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
			      अचिन्हित पूर्णांक count)
अणु
	काष्ठा vt8500_port *vt8500_port = vt8500_uart_ports[co->index];
	अचिन्हित दीर्घ ier;

	BUG_ON(co->index < 0 || co->index >= vt8500_uart_driver.nr);

	ier = vt8500_पढ़ो(&vt8500_port->uart, VT8500_URIER);
	vt8500_ग_लिखो(&vt8500_port->uart, VT8500_URIER, 0);

	uart_console_ग_लिखो(&vt8500_port->uart, s, count,
			   vt8500_console_अक्षर_दो);

	/*
	 *	Finally, रुको क्रम transmitter to become empty
	 *	and चयन back to FIFO
	 */
	रुको_क्रम_xmitr(&vt8500_port->uart);
	vt8500_ग_लिखो(&vt8500_port->uart, VT8500_URIER, ier);
पूर्ण

अटल पूर्णांक __init vt8500_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा vt8500_port *vt8500_port;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (unlikely(co->index >= vt8500_uart_driver.nr || co->index < 0))
		वापस -ENXIO;

	vt8500_port = vt8500_uart_ports[co->index];

	अगर (!vt8500_port)
		वापस -ENODEV;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(&vt8500_port->uart,
				 co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा console vt8500_console = अणु
	.name = "ttyWMT",
	.ग_लिखो = vt8500_console_ग_लिखो,
	.device = uart_console_device,
	.setup = vt8500_console_setup,
	.flags = CON_PRINTBUFFER,
	.index = -1,
	.data = &vt8500_uart_driver,
पूर्ण;

#घोषणा VT8500_CONSOLE	(&vt8500_console)

#अन्यथा
#घोषणा VT8500_CONSOLE	शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_CONSOLE_POLL
अटल पूर्णांक vt8500_get_poll_अक्षर(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक status = vt8500_पढ़ो(port, VT8500_URFIDX);

	अगर (!(status & 0x1f00))
		वापस NO_POLL_CHAR;

	वापस vt8500_पढ़ो(port, VT8500_RXFIFO) & 0xff;
पूर्ण

अटल व्योम vt8500_put_poll_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर c)
अणु
	अचिन्हित पूर्णांक status, पंचांगout = 10000;

	करो अणु
		status = vt8500_पढ़ो(port, VT8500_URFIDX);

		अगर (--पंचांगout == 0)
			अवरोध;
		udelay(1);
	पूर्ण जबतक (status & 0x10);

	vt8500_ग_लिखो(port, c, VT8500_TXFIFO);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा uart_ops vt8500_uart_pops = अणु
	.tx_empty	= vt8500_tx_empty,
	.set_mctrl	= vt8500_set_mctrl,
	.get_mctrl	= vt8500_get_mctrl,
	.stop_tx	= vt8500_stop_tx,
	.start_tx	= vt8500_start_tx,
	.stop_rx	= vt8500_stop_rx,
	.enable_ms	= vt8500_enable_ms,
	.अवरोध_ctl	= vt8500_अवरोध_ctl,
	.startup	= vt8500_startup,
	.shutकरोwn	= vt8500_shutकरोwn,
	.set_termios	= vt8500_set_termios,
	.type		= vt8500_type,
	.release_port	= vt8500_release_port,
	.request_port	= vt8500_request_port,
	.config_port	= vt8500_config_port,
	.verअगरy_port	= vt8500_verअगरy_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर	= vt8500_get_poll_अक्षर,
	.poll_put_अक्षर	= vt8500_put_poll_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा uart_driver vt8500_uart_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "vt8500_serial",
	.dev_name	= "ttyWMT",
	.nr		= 6,
	.cons		= VT8500_CONSOLE,
पूर्ण;

अटल अचिन्हित पूर्णांक vt8500_flags; /* none required so far */
अटल अचिन्हित पूर्णांक wm8880_flags = VT8500_HAS_SWRTSCTS_SWITCH;

अटल स्थिर काष्ठा of_device_id wmt_dt_ids[] = अणु
	अणु .compatible = "via,vt8500-uart", .data = &vt8500_flagsपूर्ण,
	अणु .compatible = "wm,wm8880-uart", .data = &wm8880_flagsपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक vt8500_serial_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vt8500_port *vt8500_port;
	काष्ठा resource *mmres, *irqres;
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	स्थिर अचिन्हित पूर्णांक *flags;
	पूर्णांक ret;
	पूर्णांक port;

	match = of_match_device(wmt_dt_ids, &pdev->dev);
	अगर (!match)
		वापस -EINVAL;

	flags = match->data;

	mmres = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	irqres = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!mmres || !irqres)
		वापस -ENODEV;

	अगर (np) अणु
		port = of_alias_get_id(np, "serial");
		अगर (port >= VT8500_MAX_PORTS)
			port = -1;
	पूर्ण अन्यथा अणु
		port = -1;
	पूर्ण

	अगर (port < 0) अणु
		/* calculate the port id */
		port = find_first_zero_bit(vt8500_ports_in_use,
					   VT8500_MAX_PORTS);
	पूर्ण

	अगर (port >= VT8500_MAX_PORTS)
		वापस -ENODEV;

	/* reserve the port id */
	अगर (test_and_set_bit(port, vt8500_ports_in_use)) अणु
		/* port alपढ़ोy in use - shouldn't really happen */
		वापस -EBUSY;
	पूर्ण

	vt8500_port = devm_kzalloc(&pdev->dev, माप(काष्ठा vt8500_port),
				   GFP_KERNEL);
	अगर (!vt8500_port)
		वापस -ENOMEM;

	vt8500_port->uart.membase = devm_ioremap_resource(&pdev->dev, mmres);
	अगर (IS_ERR(vt8500_port->uart.membase))
		वापस PTR_ERR(vt8500_port->uart.membase);

	vt8500_port->clk = of_clk_get(pdev->dev.of_node, 0);
	अगर (IS_ERR(vt8500_port->clk)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		वापस  -EINVAL;
	पूर्ण

	ret = clk_prepare_enable(vt8500_port->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable clock\n");
		वापस ret;
	पूर्ण

	vt8500_port->vt8500_uart_flags = *flags;
	vt8500_port->clk_preभागisor = DIV_ROUND_CLOSEST(
					clk_get_rate(vt8500_port->clk),
					VT8500_RECOMMENDED_CLK
				      );
	vt8500_port->uart.type = PORT_VT8500;
	vt8500_port->uart.iotype = UPIO_MEM;
	vt8500_port->uart.mapbase = mmres->start;
	vt8500_port->uart.irq = irqres->start;
	vt8500_port->uart.fअगरosize = 16;
	vt8500_port->uart.ops = &vt8500_uart_pops;
	vt8500_port->uart.line = port;
	vt8500_port->uart.dev = &pdev->dev;
	vt8500_port->uart.flags = UPF_IOREMAP | UPF_BOOT_AUTOCONF;
	vt8500_port->uart.has_sysrq = IS_ENABLED(CONFIG_SERIAL_VT8500_CONSOLE);

	/* Serial core uses the magic "16" everywhere - adjust क्रम it */
	vt8500_port->uart.uartclk = 16 * clk_get_rate(vt8500_port->clk) /
					vt8500_port->clk_preभागisor /
					VT8500_OVERSAMPLING_DIVISOR;

	snम_लिखो(vt8500_port->name, माप(vt8500_port->name),
		 "VT8500 UART%d", pdev->id);

	vt8500_uart_ports[port] = vt8500_port;

	uart_add_one_port(&vt8500_uart_driver, &vt8500_port->uart);

	platक्रमm_set_drvdata(pdev, vt8500_port);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver vt8500_platक्रमm_driver = अणु
	.probe  = vt8500_serial_probe,
	.driver = अणु
		.name = "vt8500_serial",
		.of_match_table = wmt_dt_ids,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init vt8500_serial_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&vt8500_uart_driver);
	अगर (unlikely(ret))
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&vt8500_platक्रमm_driver);

	अगर (unlikely(ret))
		uart_unरेजिस्टर_driver(&vt8500_uart_driver);

	वापस ret;
पूर्ण
device_initcall(vt8500_serial_init);
