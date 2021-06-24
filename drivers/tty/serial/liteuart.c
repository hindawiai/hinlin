<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * LiteUART serial controller (LiteX) Driver
 *
 * Copyright (C) 2019-2020 Anपंचांगicro <www.anपंचांगicro.com>
 */

#समावेश <linux/console.h>
#समावेश <linux/litex.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/xarray.h>

/*
 * CSRs definitions (base address offsets + width)
 *
 * The definitions below are true क्रम LiteX SoC configured क्रम 8-bit CSR Bus,
 * 32-bit aligned.
 *
 * Supporting other configurations might require new definitions or a more
 * generic way of indexing the LiteX CSRs.
 *
 * For more details on how CSRs are defined and handled in LiteX, see comments
 * in the LiteX SoC Driver: drivers/soc/litex/litex_soc_ctrl.c
 */
#घोषणा OFF_RXTX	0x00
#घोषणा OFF_TXFULL	0x04
#घोषणा OFF_RXEMPTY	0x08
#घोषणा OFF_EV_STATUS	0x0c
#घोषणा OFF_EV_PENDING	0x10
#घोषणा OFF_EV_ENABLE	0x14

/* events */
#घोषणा EV_TX		0x1
#घोषणा EV_RX		0x2

काष्ठा liteuart_port अणु
	काष्ठा uart_port port;
	काष्ठा समयr_list समयr;
	u32 id;
पूर्ण;

#घोषणा to_liteuart_port(port)	container_of(port, काष्ठा liteuart_port, port)

अटल DEFINE_XARRAY_FLAGS(liteuart_array, XA_FLAGS_ALLOC);

#अगर_घोषित CONFIG_SERIAL_LITEUART_CONSOLE
अटल काष्ठा console liteuart_console;
#पूर्ण_अगर

अटल काष्ठा uart_driver liteuart_driver = अणु
	.owner = THIS_MODULE,
	.driver_name = "liteuart",
	.dev_name = "ttyLXU",
	.major = 0,
	.minor = 0,
	.nr = CONFIG_SERIAL_LITEUART_MAX_PORTS,
#अगर_घोषित CONFIG_SERIAL_LITEUART_CONSOLE
	.cons = &liteuart_console,
#पूर्ण_अगर
पूर्ण;

अटल व्योम liteuart_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा liteuart_port *uart = from_समयr(uart, t, समयr);
	काष्ठा uart_port *port = &uart->port;
	अचिन्हित अक्षर __iomem *membase = port->membase;
	अचिन्हित पूर्णांक flg = TTY_NORMAL;
	पूर्णांक ch;
	अचिन्हित दीर्घ status;

	जबतक ((status = !litex_पढ़ो8(membase + OFF_RXEMPTY)) == 1) अणु
		ch = litex_पढ़ो8(membase + OFF_RXTX);
		port->icount.rx++;

		/* necessary क्रम RXEMPTY to refresh its value */
		litex_ग_लिखो8(membase + OFF_EV_PENDING, EV_TX | EV_RX);

		/* no overflow bits in status */
		अगर (!(uart_handle_sysrq_अक्षर(port, ch)))
			uart_insert_अक्षर(port, status, 0, ch, flg);

		tty_flip_buffer_push(&port->state->port);
	पूर्ण

	mod_समयr(&uart->समयr, jअगरfies + uart_poll_समयout(port));
पूर्ण

अटल व्योम liteuart_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	जबतक (litex_पढ़ो8(port->membase + OFF_TXFULL))
		cpu_relax();

	litex_ग_लिखो8(port->membase + OFF_RXTX, ch);
पूर्ण

अटल अचिन्हित पूर्णांक liteuart_tx_empty(काष्ठा uart_port *port)
अणु
	/* not really tx empty, just checking अगर tx is not full */
	अगर (!litex_पढ़ो8(port->membase + OFF_TXFULL))
		वापस TIOCSER_TEMT;

	वापस 0;
पूर्ण

अटल व्योम liteuart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	/* modem control रेजिस्टर is not present in LiteUART */
पूर्ण

अटल अचिन्हित पूर्णांक liteuart_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस TIOCM_CTS | TIOCM_DSR | TIOCM_CAR;
पूर्ण

अटल व्योम liteuart_stop_tx(काष्ठा uart_port *port)
अणु
पूर्ण

अटल व्योम liteuart_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित अक्षर ch;

	अगर (unlikely(port->x_अक्षर)) अणु
		litex_ग_लिखो8(port->membase + OFF_RXTX, port->x_अक्षर);
		port->icount.tx++;
		port->x_अक्षर = 0;
	पूर्ण अन्यथा अगर (!uart_circ_empty(xmit)) अणु
		जबतक (xmit->head != xmit->tail) अणु
			ch = xmit->buf[xmit->tail];
			xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
			port->icount.tx++;
			liteuart_अक्षर_दो(port, ch);
		पूर्ण
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);
पूर्ण

अटल व्योम liteuart_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा liteuart_port *uart = to_liteuart_port(port);

	/* just delete समयr */
	del_समयr(&uart->समयr);
पूर्ण

अटल व्योम liteuart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	/* LiteUART करोesn't support sending अवरोध संकेत */
पूर्ण

अटल पूर्णांक liteuart_startup(काष्ठा uart_port *port)
अणु
	काष्ठा liteuart_port *uart = to_liteuart_port(port);

	/* disable events */
	litex_ग_लिखो8(port->membase + OFF_EV_ENABLE, 0);

	/* prepare समयr क्रम polling */
	समयr_setup(&uart->समयr, liteuart_समयr, 0);
	mod_समयr(&uart->समयr, jअगरfies + uart_poll_समयout(port));

	वापस 0;
पूर्ण

अटल व्योम liteuart_shutकरोwn(काष्ठा uart_port *port)
अणु
पूर्ण

अटल व्योम liteuart_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *new,
				 काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक baud;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	/* update baudrate */
	baud = uart_get_baud_rate(port, new, old, 0, 460800);
	uart_update_समयout(port, new->c_cflag, baud);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *liteuart_type(काष्ठा uart_port *port)
अणु
	वापस "liteuart";
पूर्ण

अटल व्योम liteuart_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक liteuart_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम liteuart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	/*
	 * Driver core क्रम serial ports क्रमces a non-zero value क्रम port type.
	 * Write an arbitrary value here to accommodate the serial core driver,
	 * as ID part of UAPI is redundant.
	 */
	port->type = 1;
पूर्ण

अटल पूर्णांक liteuart_verअगरy_port(काष्ठा uart_port *port,
				काष्ठा serial_काष्ठा *ser)
अणु
	अगर (port->type != PORT_UNKNOWN && ser->type != 1)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uart_ops liteuart_ops = अणु
	.tx_empty	= liteuart_tx_empty,
	.set_mctrl	= liteuart_set_mctrl,
	.get_mctrl	= liteuart_get_mctrl,
	.stop_tx	= liteuart_stop_tx,
	.start_tx	= liteuart_start_tx,
	.stop_rx	= liteuart_stop_rx,
	.अवरोध_ctl	= liteuart_अवरोध_ctl,
	.startup	= liteuart_startup,
	.shutकरोwn	= liteuart_shutकरोwn,
	.set_termios	= liteuart_set_termios,
	.type		= liteuart_type,
	.release_port	= liteuart_release_port,
	.request_port	= liteuart_request_port,
	.config_port	= liteuart_config_port,
	.verअगरy_port	= liteuart_verअगरy_port,
पूर्ण;

अटल पूर्णांक liteuart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा liteuart_port *uart;
	काष्ठा uart_port *port;
	काष्ठा xa_limit limit;
	पूर्णांक dev_id, ret;

	/* look क्रम aliases; स्वतः-क्रमागतerate क्रम मुक्त index अगर not found */
	dev_id = of_alias_get_id(pdev->dev.of_node, "serial");
	अगर (dev_id < 0)
		limit = XA_LIMIT(0, CONFIG_SERIAL_LITEUART_MAX_PORTS);
	अन्यथा
		limit = XA_LIMIT(dev_id, dev_id);

	uart = devm_kzalloc(&pdev->dev, माप(काष्ठा liteuart_port), GFP_KERNEL);
	अगर (!uart)
		वापस -ENOMEM;

	ret = xa_alloc(&liteuart_array, &dev_id, uart, limit, GFP_KERNEL);
	अगर (ret)
		वापस ret;

	uart->id = dev_id;
	port = &uart->port;

	/* get membase */
	port->membase = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, शून्य);
	अगर (IS_ERR(port->membase))
		वापस PTR_ERR(port->membase);

	/* values not from device tree */
	port->dev = &pdev->dev;
	port->iotype = UPIO_MEM;
	port->flags = UPF_BOOT_AUTOCONF;
	port->ops = &liteuart_ops;
	port->regshअगरt = 2;
	port->fअगरosize = 16;
	port->iobase = 1;
	port->type = PORT_UNKNOWN;
	port->line = dev_id;
	spin_lock_init(&port->lock);

	वापस uart_add_one_port(&liteuart_driver, &uart->port);
पूर्ण

अटल पूर्णांक liteuart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port = platक्रमm_get_drvdata(pdev);
	काष्ठा liteuart_port *uart = to_liteuart_port(port);

	xa_erase(&liteuart_array, uart->id);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id liteuart_of_match[] = अणु
	अणु .compatible = "litex,liteuart" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, liteuart_of_match);

अटल काष्ठा platक्रमm_driver liteuart_platक्रमm_driver = अणु
	.probe = liteuart_probe,
	.हटाओ = liteuart_हटाओ,
	.driver = अणु
		.name = "liteuart",
		.of_match_table = liteuart_of_match,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_LITEUART_CONSOLE

अटल व्योम liteuart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
	अचिन्हित पूर्णांक count)
अणु
	काष्ठा liteuart_port *uart;
	काष्ठा uart_port *port;
	अचिन्हित दीर्घ flags;

	uart = (काष्ठा liteuart_port *)xa_load(&liteuart_array, co->index);
	port = &uart->port;

	spin_lock_irqsave(&port->lock, flags);
	uart_console_ग_लिखो(port, s, count, liteuart_अक्षर_दो);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल पूर्णांक liteuart_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा liteuart_port *uart;
	काष्ठा uart_port *port;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	uart = (काष्ठा liteuart_port *)xa_load(&liteuart_array, co->index);
	अगर (!uart)
		वापस -ENODEV;

	port = &uart->port;
	अगर (!port->membase)
		वापस -ENODEV;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा console liteuart_console = अणु
	.name = "liteuart",
	.ग_लिखो = liteuart_console_ग_लिखो,
	.device = uart_console_device,
	.setup = liteuart_console_setup,
	.flags = CON_PRINTBUFFER,
	.index = -1,
	.data = &liteuart_driver,
पूर्ण;

अटल पूर्णांक __init liteuart_console_init(व्योम)
अणु
	रेजिस्टर_console(&liteuart_console);

	वापस 0;
पूर्ण
console_initcall(liteuart_console_init);
#पूर्ण_अगर /* CONFIG_SERIAL_LITEUART_CONSOLE */

अटल पूर्णांक __init liteuart_init(व्योम)
अणु
	पूर्णांक res;

	res = uart_रेजिस्टर_driver(&liteuart_driver);
	अगर (res)
		वापस res;

	res = platक्रमm_driver_रेजिस्टर(&liteuart_platक्रमm_driver);
	अगर (res) अणु
		uart_unरेजिस्टर_driver(&liteuart_driver);
		वापस res;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास liteuart_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&liteuart_platक्रमm_driver);
	uart_unरेजिस्टर_driver(&liteuart_driver);
पूर्ण

module_init(liteuart_init);
module_निकास(liteuart_निकास);

MODULE_AUTHOR("Antmicro <www.antmicro.com>");
MODULE_DESCRIPTION("LiteUART serial driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform: liteuart");
