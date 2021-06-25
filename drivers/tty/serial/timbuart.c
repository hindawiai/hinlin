<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * timbuart.c timberdale FPGA UART driver
 * Copyright (c) 2009 Intel Corporation
 */

/* Supports:
 * Timberdale FPGA UART
 */

#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश "timbuart.h"

काष्ठा timbuart_port अणु
	काष्ठा uart_port	port;
	काष्ठा tasklet_काष्ठा	tasklet;
	पूर्णांक			usedma;
	u32			last_ier;
	काष्ठा platक्रमm_device  *dev;
पूर्ण;

अटल पूर्णांक baudrates[] = अणु9600, 19200, 38400, 57600, 115200, 230400, 460800,
	921600, 1843200, 3250000पूर्ण;

अटल व्योम timbuart_mctrl_check(काष्ठा uart_port *port, u32 isr, u32 *ier);

अटल irqवापस_t timbuart_handleपूर्णांकerrupt(पूर्णांक irq, व्योम *devid);

अटल व्योम timbuart_stop_rx(काष्ठा uart_port *port)
अणु
	/* spin lock held by upper layer, disable all RX पूर्णांकerrupts */
	u32 ier = ioपढ़ो32(port->membase + TIMBUART_IER) & ~RXFLAGS;
	ioग_लिखो32(ier, port->membase + TIMBUART_IER);
पूर्ण

अटल व्योम timbuart_stop_tx(काष्ठा uart_port *port)
अणु
	/* spinlock held by upper layer, disable TX पूर्णांकerrupt */
	u32 ier = ioपढ़ो32(port->membase + TIMBUART_IER) & ~TXBAE;
	ioग_लिखो32(ier, port->membase + TIMBUART_IER);
पूर्ण

अटल व्योम timbuart_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा timbuart_port *uart =
		container_of(port, काष्ठा timbuart_port, port);

	/* करो not transfer anything here -> fire off the tasklet */
	tasklet_schedule(&uart->tasklet);
पूर्ण

अटल अचिन्हित पूर्णांक timbuart_tx_empty(काष्ठा uart_port *port)
अणु
	u32 isr = ioपढ़ो32(port->membase + TIMBUART_ISR);

	वापस (isr & TXBE) ? TIOCSER_TEMT : 0;
पूर्ण

अटल व्योम timbuart_flush_buffer(काष्ठा uart_port *port)
अणु
	अगर (!timbuart_tx_empty(port)) अणु
		u8 ctl = ioपढ़ो8(port->membase + TIMBUART_CTRL) |
			TIMBUART_CTRL_FLSHTX;

		ioग_लिखो8(ctl, port->membase + TIMBUART_CTRL);
		ioग_लिखो32(TXBF, port->membase + TIMBUART_ISR);
	पूर्ण
पूर्ण

अटल व्योम timbuart_rx_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा tty_port *tport = &port->state->port;

	जबतक (ioपढ़ो32(port->membase + TIMBUART_ISR) & RXDP) अणु
		u8 ch = ioपढ़ो8(port->membase + TIMBUART_RXFIFO);
		port->icount.rx++;
		tty_insert_flip_अक्षर(tport, ch, TTY_NORMAL);
	पूर्ण

	tty_flip_buffer_push(tport);

	dev_dbg(port->dev, "%s - total read %d bytes\n",
		__func__, port->icount.rx);
पूर्ण

अटल व्योम timbuart_tx_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;

	जबतक (!(ioपढ़ो32(port->membase + TIMBUART_ISR) & TXBF) &&
		!uart_circ_empty(xmit)) अणु
		ioग_लिखो8(xmit->buf[xmit->tail],
			port->membase + TIMBUART_TXFIFO);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
	पूर्ण

	dev_dbg(port->dev,
		"%s - total written %d bytes, CTL: %x, RTS: %x, baud: %x\n",
		 __func__,
		port->icount.tx,
		ioपढ़ो8(port->membase + TIMBUART_CTRL),
		port->mctrl & TIOCM_RTS,
		ioपढ़ो8(port->membase + TIMBUART_BAUDRATE));
पूर्ण

अटल व्योम timbuart_handle_tx_port(काष्ठा uart_port *port, u32 isr, u32 *ier)
अणु
	काष्ठा timbuart_port *uart =
		container_of(port, काष्ठा timbuart_port, port);
	काष्ठा circ_buf *xmit = &port->state->xmit;

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port))
		वापस;

	अगर (port->x_अक्षर)
		वापस;

	अगर (isr & TXFLAGS) अणु
		timbuart_tx_अक्षरs(port);
		/* clear all TX पूर्णांकerrupts */
		ioग_लिखो32(TXFLAGS, port->membase + TIMBUART_ISR);

		अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
			uart_ग_लिखो_wakeup(port);
	पूर्ण अन्यथा
		/* Re-enable any tx पूर्णांकerrupt */
		*ier |= uart->last_ier & TXFLAGS;

	/* enable पूर्णांकerrupts अगर there are अक्षरs in the transmit buffer,
	 * Or अगर we delivered some bytes and want the almost empty पूर्णांकerrupt
	 * we wake up the upper layer later when we got the पूर्णांकerrupt
	 * to give it some समय to go out...
	 */
	अगर (!uart_circ_empty(xmit))
		*ier |= TXBAE;

	dev_dbg(port->dev, "%s - leaving\n", __func__);
पूर्ण

अटल व्योम timbuart_handle_rx_port(काष्ठा uart_port *port, u32 isr, u32 *ier)
अणु
	अगर (isr & RXFLAGS) अणु
		/* Some RX status is set */
		अगर (isr & RXBF) अणु
			u8 ctl = ioपढ़ो8(port->membase + TIMBUART_CTRL) |
				TIMBUART_CTRL_FLSHRX;
			ioग_लिखो8(ctl, port->membase + TIMBUART_CTRL);
			port->icount.overrun++;
		पूर्ण अन्यथा अगर (isr & (RXDP))
			timbuart_rx_अक्षरs(port);

		/* ack all RX पूर्णांकerrupts */
		ioग_लिखो32(RXFLAGS, port->membase + TIMBUART_ISR);
	पूर्ण

	/* always have the RX पूर्णांकerrupts enabled */
	*ier |= RXBAF | RXBF | RXTT;

	dev_dbg(port->dev, "%s - leaving\n", __func__);
पूर्ण

अटल व्योम timbuart_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा timbuart_port *uart = from_tasklet(uart, t, tasklet);
	u32 isr, ier = 0;

	spin_lock(&uart->port.lock);

	isr = ioपढ़ो32(uart->port.membase + TIMBUART_ISR);
	dev_dbg(uart->port.dev, "%s ISR: %x\n", __func__, isr);

	अगर (!uart->usedma)
		timbuart_handle_tx_port(&uart->port, isr, &ier);

	timbuart_mctrl_check(&uart->port, isr, &ier);

	अगर (!uart->usedma)
		timbuart_handle_rx_port(&uart->port, isr, &ier);

	ioग_लिखो32(ier, uart->port.membase + TIMBUART_IER);

	spin_unlock(&uart->port.lock);
	dev_dbg(uart->port.dev, "%s leaving\n", __func__);
पूर्ण

अटल अचिन्हित पूर्णांक timbuart_get_mctrl(काष्ठा uart_port *port)
अणु
	u8 cts = ioपढ़ो8(port->membase + TIMBUART_CTRL);
	dev_dbg(port->dev, "%s - cts %x\n", __func__, cts);

	अगर (cts & TIMBUART_CTRL_CTS)
		वापस TIOCM_CTS | TIOCM_DSR | TIOCM_CAR;
	अन्यथा
		वापस TIOCM_DSR | TIOCM_CAR;
पूर्ण

अटल व्योम timbuart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	dev_dbg(port->dev, "%s - %x\n", __func__, mctrl);

	अगर (mctrl & TIOCM_RTS)
		ioग_लिखो8(TIMBUART_CTRL_RTS, port->membase + TIMBUART_CTRL);
	अन्यथा
		ioग_लिखो8(0, port->membase + TIMBUART_CTRL);
पूर्ण

अटल व्योम timbuart_mctrl_check(काष्ठा uart_port *port, u32 isr, u32 *ier)
अणु
	अचिन्हित पूर्णांक cts;

	अगर (isr & CTS_DELTA) अणु
		/* ack */
		ioग_लिखो32(CTS_DELTA, port->membase + TIMBUART_ISR);
		cts = timbuart_get_mctrl(port);
		uart_handle_cts_change(port, cts & TIOCM_CTS);
		wake_up_पूर्णांकerruptible(&port->state->port.delta_msr_रुको);
	पूर्ण

	*ier |= CTS_DELTA;
पूर्ण

अटल व्योम timbuart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक ctl)
अणु
	/* N/A */
पूर्ण

अटल पूर्णांक timbuart_startup(काष्ठा uart_port *port)
अणु
	काष्ठा timbuart_port *uart =
		container_of(port, काष्ठा timbuart_port, port);

	dev_dbg(port->dev, "%s\n", __func__);

	ioग_लिखो8(TIMBUART_CTRL_FLSHRX, port->membase + TIMBUART_CTRL);
	ioग_लिखो32(0x1ff, port->membase + TIMBUART_ISR);
	/* Enable all but TX पूर्णांकerrupts */
	ioग_लिखो32(RXBAF | RXBF | RXTT | CTS_DELTA,
		port->membase + TIMBUART_IER);

	वापस request_irq(port->irq, timbuart_handleपूर्णांकerrupt, IRQF_SHARED,
		"timb-uart", uart);
पूर्ण

अटल व्योम timbuart_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा timbuart_port *uart =
		container_of(port, काष्ठा timbuart_port, port);
	dev_dbg(port->dev, "%s\n", __func__);
	मुक्त_irq(port->irq, uart);
	ioग_लिखो32(0, port->membase + TIMBUART_IER);

	timbuart_flush_buffer(port);
पूर्ण

अटल पूर्णांक get_bindex(पूर्णांक baud)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(baudrates); i++)
		अगर (baud <= baudrates[i])
			वापस i;

	वापस -1;
पूर्ण

अटल व्योम timbuart_set_termios(काष्ठा uart_port *port,
	काष्ठा ktermios *termios,
	काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक baud;
	लघु bindex;
	अचिन्हित दीर्घ flags;

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk / 16);
	bindex = get_bindex(baud);
	dev_dbg(port->dev, "%s - bindex %d\n", __func__, bindex);

	अगर (bindex < 0)
		bindex = 0;
	baud = baudrates[bindex];

	/* The serial layer calls पूर्णांकo this once with old = शून्य when setting
	   up initially */
	अगर (old)
		tty_termios_copy_hw(termios, old);
	tty_termios_encode_baud_rate(termios, baud, baud);

	spin_lock_irqsave(&port->lock, flags);
	ioग_लिखो8((u8)bindex, port->membase + TIMBUART_BAUDRATE);
	uart_update_समयout(port, termios->c_cflag, baud);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *timbuart_type(काष्ठा uart_port *port)
अणु
	वापस port->type == PORT_UNKNOWN ? "timbuart" : शून्य;
पूर्ण

/* We करो not request/release mappings of the रेजिस्टरs here,
 * currently it's करोne in the proble function.
 */
अटल व्योम timbuart_release_port(काष्ठा uart_port *port)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(port->dev);
	पूर्णांक size =
		resource_size(platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0));

	अगर (port->flags & UPF_IOREMAP) अणु
		iounmap(port->membase);
		port->membase = शून्य;
	पूर्ण

	release_mem_region(port->mapbase, size);
पूर्ण

अटल पूर्णांक timbuart_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(port->dev);
	पूर्णांक size =
		resource_size(platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0));

	अगर (!request_mem_region(port->mapbase, size, "timb-uart"))
		वापस -EBUSY;

	अगर (port->flags & UPF_IOREMAP) अणु
		port->membase = ioremap(port->mapbase, size);
		अगर (port->membase == शून्य) अणु
			release_mem_region(port->mapbase, size);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t timbuart_handleपूर्णांकerrupt(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा timbuart_port *uart = (काष्ठा timbuart_port *)devid;

	अगर (ioपढ़ो8(uart->port.membase + TIMBUART_IPR)) अणु
		uart->last_ier = ioपढ़ो32(uart->port.membase + TIMBUART_IER);

		/* disable पूर्णांकerrupts, the tasklet enables them again */
		ioग_लिखो32(0, uart->port.membase + TIMBUART_IER);

		/* fire off bottom half */
		tasklet_schedule(&uart->tasklet);

		वापस IRQ_HANDLED;
	पूर्ण अन्यथा
		वापस IRQ_NONE;
पूर्ण

/*
 * Configure/स्वतःconfigure the port.
 */
अटल व्योम timbuart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE) अणु
		port->type = PORT_TIMBUART;
		timbuart_request_port(port);
	पूर्ण
पूर्ण

अटल पूर्णांक timbuart_verअगरy_port(काष्ठा uart_port *port,
	काष्ठा serial_काष्ठा *ser)
अणु
	/* we करोn't want the core code to modअगरy any port params */
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा uart_ops timbuart_ops = अणु
	.tx_empty = timbuart_tx_empty,
	.set_mctrl = timbuart_set_mctrl,
	.get_mctrl = timbuart_get_mctrl,
	.stop_tx = timbuart_stop_tx,
	.start_tx = timbuart_start_tx,
	.flush_buffer = timbuart_flush_buffer,
	.stop_rx = timbuart_stop_rx,
	.अवरोध_ctl = timbuart_अवरोध_ctl,
	.startup = timbuart_startup,
	.shutकरोwn = timbuart_shutकरोwn,
	.set_termios = timbuart_set_termios,
	.type = timbuart_type,
	.release_port = timbuart_release_port,
	.request_port = timbuart_request_port,
	.config_port = timbuart_config_port,
	.verअगरy_port = timbuart_verअगरy_port
पूर्ण;

अटल काष्ठा uart_driver timbuart_driver = अणु
	.owner = THIS_MODULE,
	.driver_name = "timberdale_uart",
	.dev_name = "ttyTU",
	.major = TIMBUART_MAJOR,
	.minor = TIMBUART_MINOR,
	.nr = 1
पूर्ण;

अटल पूर्णांक timbuart_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक err, irq;
	काष्ठा timbuart_port *uart;
	काष्ठा resource *iomem;

	dev_dbg(&dev->dev, "%s\n", __func__);

	uart = kzalloc(माप(*uart), GFP_KERNEL);
	अगर (!uart) अणु
		err = -EINVAL;
		जाओ err_mem;
	पूर्ण

	uart->usedma = 0;

	uart->port.uartclk = 3250000 * 16;
	uart->port.fअगरosize  = TIMBUART_FIFO_SIZE;
	uart->port.regshअगरt  = 2;
	uart->port.iotype  = UPIO_MEM;
	uart->port.ops = &timbuart_ops;
	uart->port.irq = 0;
	uart->port.flags = UPF_BOOT_AUTOCONF | UPF_IOREMAP;
	uart->port.line  = 0;
	uart->port.dev	= &dev->dev;

	iomem = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!iomem) अणु
		err = -ENOMEM;
		जाओ err_रेजिस्टर;
	पूर्ण
	uart->port.mapbase = iomem->start;
	uart->port.membase = शून्य;

	irq = platक्रमm_get_irq(dev, 0);
	अगर (irq < 0) अणु
		err = -EINVAL;
		जाओ err_रेजिस्टर;
	पूर्ण
	uart->port.irq = irq;

	tasklet_setup(&uart->tasklet, timbuart_tasklet);

	err = uart_रेजिस्टर_driver(&timbuart_driver);
	अगर (err)
		जाओ err_रेजिस्टर;

	err = uart_add_one_port(&timbuart_driver, &uart->port);
	अगर (err)
		जाओ err_add_port;

	platक्रमm_set_drvdata(dev, uart);

	वापस 0;

err_add_port:
	uart_unरेजिस्टर_driver(&timbuart_driver);
err_रेजिस्टर:
	kमुक्त(uart);
err_mem:
	prपूर्णांकk(KERN_ERR "timberdale: Failed to register Timberdale UART: %d\n",
		err);

	वापस err;
पूर्ण

अटल पूर्णांक timbuart_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा timbuart_port *uart = platक्रमm_get_drvdata(dev);

	tasklet_समाप्त(&uart->tasklet);
	uart_हटाओ_one_port(&timbuart_driver, &uart->port);
	uart_unरेजिस्टर_driver(&timbuart_driver);
	kमुक्त(uart);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver timbuart_platक्रमm_driver = अणु
	.driver = अणु
		.name	= "timb-uart",
	पूर्ण,
	.probe		= timbuart_probe,
	.हटाओ		= timbuart_हटाओ,
पूर्ण;

module_platक्रमm_driver(timbuart_platक्रमm_driver);

MODULE_DESCRIPTION("Timberdale UART driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:timb-uart");

