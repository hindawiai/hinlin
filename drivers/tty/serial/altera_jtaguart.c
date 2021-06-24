<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * altera_jtaguart.c -- Altera JTAG UART driver
 *
 * Based on mcf.c -- Freescale ColdFire UART driver
 *
 * (C) Copyright 2003-2007, Greg Ungerer <gerg@snapgear.com>
 * (C) Copyright 2008, Thomas Chou <thomas@wytron.com.tw>
 * (C) Copyright 2010, Tobias Klauser <tklauser@distanz.ch>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/console.h>
#समावेश <linux/of.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/altera_jtaguart.h>

#घोषणा DRV_NAME "altera_jtaguart"

/*
 * Altera JTAG UART रेजिस्टर definitions according to the Altera JTAG UART
 * datasheet: https://www.altera.com/literature/hb/nios2/n2cpu_nii51009.pdf
 */

#घोषणा ALTERA_JTAGUART_SIZE			8

#घोषणा ALTERA_JTAGUART_DATA_REG		0

#घोषणा ALTERA_JTAGUART_DATA_DATA_MSK		0x000000FF
#घोषणा ALTERA_JTAGUART_DATA_RVALID_MSK		0x00008000
#घोषणा ALTERA_JTAGUART_DATA_RAVAIL_MSK		0xFFFF0000
#घोषणा ALTERA_JTAGUART_DATA_RAVAIL_OFF		16

#घोषणा ALTERA_JTAGUART_CONTROL_REG		4

#घोषणा ALTERA_JTAGUART_CONTROL_RE_MSK		0x00000001
#घोषणा ALTERA_JTAGUART_CONTROL_WE_MSK		0x00000002
#घोषणा ALTERA_JTAGUART_CONTROL_RI_MSK		0x00000100
#घोषणा ALTERA_JTAGUART_CONTROL_RI_OFF		8
#घोषणा ALTERA_JTAGUART_CONTROL_WI_MSK		0x00000200
#घोषणा ALTERA_JTAGUART_CONTROL_AC_MSK		0x00000400
#घोषणा ALTERA_JTAGUART_CONTROL_WSPACE_MSK	0xFFFF0000
#घोषणा ALTERA_JTAGUART_CONTROL_WSPACE_OFF	16

/*
 * Local per-uart काष्ठाure.
 */
काष्ठा altera_jtaguart अणु
	काष्ठा uart_port port;
	अचिन्हित पूर्णांक sigs;	/* Local copy of line sigs */
	अचिन्हित दीर्घ imr;	/* Local IMR mirror */
पूर्ण;

अटल अचिन्हित पूर्णांक altera_jtaguart_tx_empty(काष्ठा uart_port *port)
अणु
	वापस (पढ़ोl(port->membase + ALTERA_JTAGUART_CONTROL_REG) &
		ALTERA_JTAGUART_CONTROL_WSPACE_MSK) ? TIOCSER_TEMT : 0;
पूर्ण

अटल अचिन्हित पूर्णांक altera_jtaguart_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस TIOCM_CAR | TIOCM_DSR | TIOCM_CTS;
पूर्ण

अटल व्योम altera_jtaguart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक sigs)
अणु
पूर्ण

अटल व्योम altera_jtaguart_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा altera_jtaguart *pp =
	    container_of(port, काष्ठा altera_jtaguart, port);

	pp->imr |= ALTERA_JTAGUART_CONTROL_WE_MSK;
	ग_लिखोl(pp->imr, port->membase + ALTERA_JTAGUART_CONTROL_REG);
पूर्ण

अटल व्योम altera_jtaguart_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा altera_jtaguart *pp =
	    container_of(port, काष्ठा altera_jtaguart, port);

	pp->imr &= ~ALTERA_JTAGUART_CONTROL_WE_MSK;
	ग_लिखोl(pp->imr, port->membase + ALTERA_JTAGUART_CONTROL_REG);
पूर्ण

अटल व्योम altera_jtaguart_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा altera_jtaguart *pp =
	    container_of(port, काष्ठा altera_jtaguart, port);

	pp->imr &= ~ALTERA_JTAGUART_CONTROL_RE_MSK;
	ग_लिखोl(pp->imr, port->membase + ALTERA_JTAGUART_CONTROL_REG);
पूर्ण

अटल व्योम altera_jtaguart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
पूर्ण

अटल व्योम altera_jtaguart_set_termios(काष्ठा uart_port *port,
					काष्ठा ktermios *termios,
					काष्ठा ktermios *old)
अणु
	/* Just copy the old termios settings back */
	अगर (old)
		tty_termios_copy_hw(termios, old);
पूर्ण

अटल व्योम altera_jtaguart_rx_अक्षरs(काष्ठा altera_jtaguart *pp)
अणु
	काष्ठा uart_port *port = &pp->port;
	अचिन्हित अक्षर ch, flag;
	अचिन्हित दीर्घ status;

	जबतक ((status = पढ़ोl(port->membase + ALTERA_JTAGUART_DATA_REG)) &
	       ALTERA_JTAGUART_DATA_RVALID_MSK) अणु
		ch = status & ALTERA_JTAGUART_DATA_DATA_MSK;
		flag = TTY_NORMAL;
		port->icount.rx++;

		अगर (uart_handle_sysrq_अक्षर(port, ch))
			जारी;
		uart_insert_अक्षर(port, 0, 0, ch, flag);
	पूर्ण

	tty_flip_buffer_push(&port->state->port);
पूर्ण

अटल व्योम altera_jtaguart_tx_अक्षरs(काष्ठा altera_jtaguart *pp)
अणु
	काष्ठा uart_port *port = &pp->port;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित पूर्णांक pending, count;

	अगर (port->x_अक्षर) अणु
		/* Send special अक्षर - probably flow control */
		ग_लिखोl(port->x_अक्षर, port->membase + ALTERA_JTAGUART_DATA_REG);
		port->x_अक्षर = 0;
		port->icount.tx++;
		वापस;
	पूर्ण

	pending = uart_circ_अक्षरs_pending(xmit);
	अगर (pending > 0) अणु
		count = (पढ़ोl(port->membase + ALTERA_JTAGUART_CONTROL_REG) &
				ALTERA_JTAGUART_CONTROL_WSPACE_MSK) >>
			ALTERA_JTAGUART_CONTROL_WSPACE_OFF;
		अगर (count > pending)
			count = pending;
		अगर (count > 0) अणु
			pending -= count;
			जबतक (count--) अणु
				ग_लिखोl(xmit->buf[xmit->tail],
				       port->membase + ALTERA_JTAGUART_DATA_REG);
				xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
				port->icount.tx++;
			पूर्ण
			अगर (pending < WAKEUP_CHARS)
				uart_ग_लिखो_wakeup(port);
		पूर्ण
	पूर्ण

	अगर (pending == 0) अणु
		pp->imr &= ~ALTERA_JTAGUART_CONTROL_WE_MSK;
		ग_लिखोl(pp->imr, port->membase + ALTERA_JTAGUART_CONTROL_REG);
	पूर्ण
पूर्ण

अटल irqवापस_t altera_jtaguart_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा uart_port *port = data;
	काष्ठा altera_jtaguart *pp =
	    container_of(port, काष्ठा altera_jtaguart, port);
	अचिन्हित पूर्णांक isr;

	isr = (पढ़ोl(port->membase + ALTERA_JTAGUART_CONTROL_REG) >>
	       ALTERA_JTAGUART_CONTROL_RI_OFF) & pp->imr;

	spin_lock(&port->lock);

	अगर (isr & ALTERA_JTAGUART_CONTROL_RE_MSK)
		altera_jtaguart_rx_अक्षरs(pp);
	अगर (isr & ALTERA_JTAGUART_CONTROL_WE_MSK)
		altera_jtaguart_tx_अक्षरs(pp);

	spin_unlock(&port->lock);

	वापस IRQ_RETVAL(isr);
पूर्ण

अटल व्योम altera_jtaguart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	port->type = PORT_ALTERA_JTAGUART;

	/* Clear mask, so no surprise पूर्णांकerrupts. */
	ग_लिखोl(0, port->membase + ALTERA_JTAGUART_CONTROL_REG);
पूर्ण

अटल पूर्णांक altera_jtaguart_startup(काष्ठा uart_port *port)
अणु
	काष्ठा altera_jtaguart *pp =
	    container_of(port, काष्ठा altera_jtaguart, port);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = request_irq(port->irq, altera_jtaguart_पूर्णांकerrupt, 0,
			DRV_NAME, port);
	अगर (ret) अणु
		pr_err(DRV_NAME ": unable to attach Altera JTAG UART %d "
		       "interrupt vector=%d\n", port->line, port->irq);
		वापस ret;
	पूर्ण

	spin_lock_irqsave(&port->lock, flags);

	/* Enable RX पूर्णांकerrupts now */
	pp->imr = ALTERA_JTAGUART_CONTROL_RE_MSK;
	ग_लिखोl(pp->imr, port->membase + ALTERA_JTAGUART_CONTROL_REG);

	spin_unlock_irqrestore(&port->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम altera_jtaguart_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा altera_jtaguart *pp =
	    container_of(port, काष्ठा altera_jtaguart, port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	/* Disable all पूर्णांकerrupts now */
	pp->imr = 0;
	ग_लिखोl(pp->imr, port->membase + ALTERA_JTAGUART_CONTROL_REG);

	spin_unlock_irqrestore(&port->lock, flags);

	मुक्त_irq(port->irq, port);
पूर्ण

अटल स्थिर अक्षर *altera_jtaguart_type(काष्ठा uart_port *port)
अणु
	वापस (port->type == PORT_ALTERA_JTAGUART) ? "Altera JTAG UART" : शून्य;
पूर्ण

अटल पूर्णांक altera_jtaguart_request_port(काष्ठा uart_port *port)
अणु
	/* UARTs always present */
	वापस 0;
पूर्ण

अटल व्योम altera_jtaguart_release_port(काष्ठा uart_port *port)
अणु
	/* Nothing to release... */
पूर्ण

अटल पूर्णांक altera_jtaguart_verअगरy_port(काष्ठा uart_port *port,
				       काष्ठा serial_काष्ठा *ser)
अणु
	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_ALTERA_JTAGUART)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 *	Define the basic serial functions we support.
 */
अटल स्थिर काष्ठा uart_ops altera_jtaguart_ops = अणु
	.tx_empty	= altera_jtaguart_tx_empty,
	.get_mctrl	= altera_jtaguart_get_mctrl,
	.set_mctrl	= altera_jtaguart_set_mctrl,
	.start_tx	= altera_jtaguart_start_tx,
	.stop_tx	= altera_jtaguart_stop_tx,
	.stop_rx	= altera_jtaguart_stop_rx,
	.अवरोध_ctl	= altera_jtaguart_अवरोध_ctl,
	.startup	= altera_jtaguart_startup,
	.shutकरोwn	= altera_jtaguart_shutकरोwn,
	.set_termios	= altera_jtaguart_set_termios,
	.type		= altera_jtaguart_type,
	.request_port	= altera_jtaguart_request_port,
	.release_port	= altera_jtaguart_release_port,
	.config_port	= altera_jtaguart_config_port,
	.verअगरy_port	= altera_jtaguart_verअगरy_port,
पूर्ण;

#घोषणा ALTERA_JTAGUART_MAXPORTS 1
अटल काष्ठा altera_jtaguart altera_jtaguart_ports[ALTERA_JTAGUART_MAXPORTS];

#अगर defined(CONFIG_SERIAL_ALTERA_JTAGUART_CONSOLE)

#अगर defined(CONFIG_SERIAL_ALTERA_JTAGUART_CONSOLE_BYPASS)
अटल व्योम altera_jtaguart_console_अ_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	अचिन्हित दीर्घ status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	जबतक (((status = पढ़ोl(port->membase + ALTERA_JTAGUART_CONTROL_REG)) &
		ALTERA_JTAGUART_CONTROL_WSPACE_MSK) == 0) अणु
		अगर ((status & ALTERA_JTAGUART_CONTROL_AC_MSK) == 0) अणु
			spin_unlock_irqrestore(&port->lock, flags);
			वापस;	/* no connection activity */
		पूर्ण
		spin_unlock_irqrestore(&port->lock, flags);
		cpu_relax();
		spin_lock_irqsave(&port->lock, flags);
	पूर्ण
	ग_लिखोl(c, port->membase + ALTERA_JTAGUART_DATA_REG);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण
#अन्यथा
अटल व्योम altera_jtaguart_console_अ_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	जबतक ((पढ़ोl(port->membase + ALTERA_JTAGUART_CONTROL_REG) &
		ALTERA_JTAGUART_CONTROL_WSPACE_MSK) == 0) अणु
		spin_unlock_irqrestore(&port->lock, flags);
		cpu_relax();
		spin_lock_irqsave(&port->lock, flags);
	पूर्ण
	ग_लिखोl(c, port->membase + ALTERA_JTAGUART_DATA_REG);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण
#पूर्ण_अगर

अटल व्योम altera_jtaguart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
					  अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_port *port = &(altera_jtaguart_ports + co->index)->port;

	uart_console_ग_लिखो(port, s, count, altera_jtaguart_console_अ_दो);
पूर्ण

अटल पूर्णांक __init altera_jtaguart_console_setup(काष्ठा console *co,
						अक्षर *options)
अणु
	काष्ठा uart_port *port;

	अगर (co->index < 0 || co->index >= ALTERA_JTAGUART_MAXPORTS)
		वापस -EINVAL;
	port = &altera_jtaguart_ports[co->index].port;
	अगर (port->membase == शून्य)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल काष्ठा uart_driver altera_jtaguart_driver;

अटल काष्ठा console altera_jtaguart_console = अणु
	.name	= "ttyJ",
	.ग_लिखो	= altera_jtaguart_console_ग_लिखो,
	.device	= uart_console_device,
	.setup	= altera_jtaguart_console_setup,
	.flags	= CON_PRINTBUFFER,
	.index	= -1,
	.data	= &altera_jtaguart_driver,
पूर्ण;

अटल पूर्णांक __init altera_jtaguart_console_init(व्योम)
अणु
	रेजिस्टर_console(&altera_jtaguart_console);
	वापस 0;
पूर्ण

console_initcall(altera_jtaguart_console_init);

#घोषणा	ALTERA_JTAGUART_CONSOLE	(&altera_jtaguart_console)

अटल व्योम altera_jtaguart_earlycon_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
					   अचिन्हित पूर्णांक count)
अणु
	काष्ठा earlycon_device *dev = co->data;

	uart_console_ग_लिखो(&dev->port, s, count, altera_jtaguart_console_अ_दो);
पूर्ण

अटल पूर्णांक __init altera_jtaguart_earlycon_setup(काष्ठा earlycon_device *dev,
						 स्थिर अक्षर *options)
अणु
	अगर (!dev->port.membase)
		वापस -ENODEV;

	dev->con->ग_लिखो = altera_jtaguart_earlycon_ग_लिखो;
	वापस 0;
पूर्ण

OF_EARLYCON_DECLARE(juart, "altr,juart-1.0", altera_jtaguart_earlycon_setup);

#अन्यथा

#घोषणा	ALTERA_JTAGUART_CONSOLE	शून्य

#पूर्ण_अगर /* CONFIG_SERIAL_ALTERA_JTAGUART_CONSOLE */

अटल काष्ठा uart_driver altera_jtaguart_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "altera_jtaguart",
	.dev_name	= "ttyJ",
	.major		= ALTERA_JTAGUART_MAJOR,
	.minor		= ALTERA_JTAGUART_MINOR,
	.nr		= ALTERA_JTAGUART_MAXPORTS,
	.cons		= ALTERA_JTAGUART_CONSOLE,
पूर्ण;

अटल पूर्णांक altera_jtaguart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा altera_jtaguart_platक्रमm_uart *platp =
			dev_get_platdata(&pdev->dev);
	काष्ठा uart_port *port;
	काष्ठा resource *res_irq, *res_mem;
	पूर्णांक i = pdev->id;

	/* -1 emphasizes that the platक्रमm must have one port, no .N suffix */
	अगर (i == -1)
		i = 0;

	अगर (i >= ALTERA_JTAGUART_MAXPORTS)
		वापस -EINVAL;

	port = &altera_jtaguart_ports[i].port;

	res_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res_mem)
		port->mapbase = res_mem->start;
	अन्यथा अगर (platp)
		port->mapbase = platp->mapbase;
	अन्यथा
		वापस -ENODEV;

	res_irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (res_irq)
		port->irq = res_irq->start;
	अन्यथा अगर (platp)
		port->irq = platp->irq;
	अन्यथा
		वापस -ENODEV;

	port->membase = ioremap(port->mapbase, ALTERA_JTAGUART_SIZE);
	अगर (!port->membase)
		वापस -ENOMEM;

	port->line = i;
	port->type = PORT_ALTERA_JTAGUART;
	port->iotype = SERIAL_IO_MEM;
	port->ops = &altera_jtaguart_ops;
	port->flags = UPF_BOOT_AUTOCONF;
	port->dev = &pdev->dev;

	uart_add_one_port(&altera_jtaguart_driver, port);

	वापस 0;
पूर्ण

अटल पूर्णांक altera_jtaguart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port;
	पूर्णांक i = pdev->id;

	अगर (i == -1)
		i = 0;

	port = &altera_jtaguart_ports[i].port;
	uart_हटाओ_one_port(&altera_jtaguart_driver, port);
	iounmap(port->membase);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id altera_jtaguart_match[] = अणु
	अणु .compatible = "ALTR,juart-1.0", पूर्ण,
	अणु .compatible = "altr,juart-1.0", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, altera_jtaguart_match);
#पूर्ण_अगर /* CONFIG_OF */

अटल काष्ठा platक्रमm_driver altera_jtaguart_platक्रमm_driver = अणु
	.probe	= altera_jtaguart_probe,
	.हटाओ	= altera_jtaguart_हटाओ,
	.driver	= अणु
		.name		= DRV_NAME,
		.of_match_table	= of_match_ptr(altera_jtaguart_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init altera_jtaguart_init(व्योम)
अणु
	पूर्णांक rc;

	rc = uart_रेजिस्टर_driver(&altera_jtaguart_driver);
	अगर (rc)
		वापस rc;
	rc = platक्रमm_driver_रेजिस्टर(&altera_jtaguart_platक्रमm_driver);
	अगर (rc)
		uart_unरेजिस्टर_driver(&altera_jtaguart_driver);
	वापस rc;
पूर्ण

अटल व्योम __निकास altera_jtaguart_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&altera_jtaguart_platक्रमm_driver);
	uart_unरेजिस्टर_driver(&altera_jtaguart_driver);
पूर्ण

module_init(altera_jtaguart_init);
module_निकास(altera_jtaguart_निकास);

MODULE_DESCRIPTION("Altera JTAG UART driver");
MODULE_AUTHOR("Thomas Chou <thomas@wytron.com.tw>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
