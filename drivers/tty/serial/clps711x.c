<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Driver क्रम CLPS711x serial ports
 *
 *  Based on drivers/अक्षर/serial.c, by Linus Torvalds, Theoकरोre Ts'o.
 *
 *  Copyright 1999 ARM Limited
 *  Copyright (C) 2000 Deep Blue Solutions Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/console.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/ioport.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/clps711x.h>

#समावेश "serial_mctrl_gpio.h"

#घोषणा UART_CLPS711X_DEVNAME	"ttyCL"
#घोषणा UART_CLPS711X_NR	2
#घोषणा UART_CLPS711X_MAJOR	204
#घोषणा UART_CLPS711X_MINOR	40

#घोषणा UARTDR_OFFSET		(0x00)
#घोषणा UBRLCR_OFFSET		(0x40)

#घोषणा UARTDR_FRMERR		(1 << 8)
#घोषणा UARTDR_PARERR		(1 << 9)
#घोषणा UARTDR_OVERR		(1 << 10)

#घोषणा UBRLCR_BAUD_MASK	((1 << 12) - 1)
#घोषणा UBRLCR_BREAK		(1 << 12)
#घोषणा UBRLCR_PRTEN		(1 << 13)
#घोषणा UBRLCR_EVENPRT		(1 << 14)
#घोषणा UBRLCR_XSTOP		(1 << 15)
#घोषणा UBRLCR_FIFOEN		(1 << 16)
#घोषणा UBRLCR_WRDLEN5		(0 << 17)
#घोषणा UBRLCR_WRDLEN6		(1 << 17)
#घोषणा UBRLCR_WRDLEN7		(2 << 17)
#घोषणा UBRLCR_WRDLEN8		(3 << 17)
#घोषणा UBRLCR_WRDLEN_MASK	(3 << 17)

काष्ठा clps711x_port अणु
	काष्ठा uart_port	port;
	अचिन्हित पूर्णांक		tx_enabled;
	पूर्णांक			rx_irq;
	काष्ठा regmap		*syscon;
	काष्ठा mctrl_gpios	*gpios;
पूर्ण;

अटल काष्ठा uart_driver clps711x_uart = अणु
	.owner		= THIS_MODULE,
	.driver_name	= UART_CLPS711X_DEVNAME,
	.dev_name	= UART_CLPS711X_DEVNAME,
	.major		= UART_CLPS711X_MAJOR,
	.minor		= UART_CLPS711X_MINOR,
	.nr		= UART_CLPS711X_NR,
पूर्ण;

अटल व्योम uart_clps711x_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा clps711x_port *s = dev_get_drvdata(port->dev);

	अगर (s->tx_enabled) अणु
		disable_irq(port->irq);
		s->tx_enabled = 0;
	पूर्ण
पूर्ण

अटल व्योम uart_clps711x_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा clps711x_port *s = dev_get_drvdata(port->dev);

	अगर (!s->tx_enabled) अणु
		s->tx_enabled = 1;
		enable_irq(port->irq);
	पूर्ण
पूर्ण

अटल irqवापस_t uart_clps711x_पूर्णांक_rx(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	काष्ठा clps711x_port *s = dev_get_drvdata(port->dev);
	अचिन्हित पूर्णांक status, flg;
	u16 ch;

	क्रम (;;) अणु
		u32 sysflg = 0;

		regmap_पढ़ो(s->syscon, SYSFLG_OFFSET, &sysflg);
		अगर (sysflg & SYSFLG_URXFE)
			अवरोध;

		ch = पढ़ोw(port->membase + UARTDR_OFFSET);
		status = ch & (UARTDR_FRMERR | UARTDR_PARERR | UARTDR_OVERR);
		ch &= 0xff;

		port->icount.rx++;
		flg = TTY_NORMAL;

		अगर (unlikely(status)) अणु
			अगर (status & UARTDR_PARERR)
				port->icount.parity++;
			अन्यथा अगर (status & UARTDR_FRMERR)
				port->icount.frame++;
			अन्यथा अगर (status & UARTDR_OVERR)
				port->icount.overrun++;

			status &= port->पढ़ो_status_mask;

			अगर (status & UARTDR_PARERR)
				flg = TTY_PARITY;
			अन्यथा अगर (status & UARTDR_FRMERR)
				flg = TTY_FRAME;
			अन्यथा अगर (status & UARTDR_OVERR)
				flg = TTY_OVERRUN;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(port, ch))
			जारी;

		अगर (status & port->ignore_status_mask)
			जारी;

		uart_insert_अक्षर(port, status, UARTDR_OVERR, ch, flg);
	पूर्ण

	tty_flip_buffer_push(&port->state->port);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t uart_clps711x_पूर्णांक_tx(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	काष्ठा clps711x_port *s = dev_get_drvdata(port->dev);
	काष्ठा circ_buf *xmit = &port->state->xmit;

	अगर (port->x_अक्षर) अणु
		ग_लिखोw(port->x_अक्षर, port->membase + UARTDR_OFFSET);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		अगर (s->tx_enabled) अणु
			disable_irq_nosync(port->irq);
			s->tx_enabled = 0;
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण

	जबतक (!uart_circ_empty(xmit)) अणु
		u32 sysflg = 0;

		ग_लिखोw(xmit->buf[xmit->tail], port->membase + UARTDR_OFFSET);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;

		regmap_पढ़ो(s->syscon, SYSFLG_OFFSET, &sysflg);
		अगर (sysflg & SYSFLG_UTXFF)
			अवरोध;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक uart_clps711x_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा clps711x_port *s = dev_get_drvdata(port->dev);
	u32 sysflg = 0;

	regmap_पढ़ो(s->syscon, SYSFLG_OFFSET, &sysflg);

	वापस (sysflg & SYSFLG_UBUSY) ? 0 : TIOCSER_TEMT;
पूर्ण

अटल अचिन्हित पूर्णांक uart_clps711x_get_mctrl(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक result = TIOCM_DSR | TIOCM_CTS | TIOCM_CAR;
	काष्ठा clps711x_port *s = dev_get_drvdata(port->dev);

	वापस mctrl_gpio_get(s->gpios, &result);
पूर्ण

अटल व्योम uart_clps711x_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा clps711x_port *s = dev_get_drvdata(port->dev);

	mctrl_gpio_set(s->gpios, mctrl);
पूर्ण

अटल व्योम uart_clps711x_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	अचिन्हित पूर्णांक ubrlcr;

	ubrlcr = पढ़ोl(port->membase + UBRLCR_OFFSET);
	अगर (अवरोध_state)
		ubrlcr |= UBRLCR_BREAK;
	अन्यथा
		ubrlcr &= ~UBRLCR_BREAK;
	ग_लिखोl(ubrlcr, port->membase + UBRLCR_OFFSET);
पूर्ण

अटल व्योम uart_clps711x_set_ldisc(काष्ठा uart_port *port,
				    काष्ठा ktermios *termios)
अणु
	अगर (!port->line) अणु
		काष्ठा clps711x_port *s = dev_get_drvdata(port->dev);

		regmap_update_bits(s->syscon, SYSCON_OFFSET, SYSCON1_SIREN,
				   (termios->c_line == N_IRDA) ? SYSCON1_SIREN : 0);
	पूर्ण
पूर्ण

अटल पूर्णांक uart_clps711x_startup(काष्ठा uart_port *port)
अणु
	काष्ठा clps711x_port *s = dev_get_drvdata(port->dev);

	/* Disable अवरोध */
	ग_लिखोl(पढ़ोl(port->membase + UBRLCR_OFFSET) & ~UBRLCR_BREAK,
	       port->membase + UBRLCR_OFFSET);

	/* Enable the port */
	वापस regmap_update_bits(s->syscon, SYSCON_OFFSET,
				  SYSCON_UARTEN, SYSCON_UARTEN);
पूर्ण

अटल व्योम uart_clps711x_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा clps711x_port *s = dev_get_drvdata(port->dev);

	/* Disable the port */
	regmap_update_bits(s->syscon, SYSCON_OFFSET, SYSCON_UARTEN, 0);
पूर्ण

अटल व्योम uart_clps711x_set_termios(काष्ठा uart_port *port,
				      काष्ठा ktermios *termios,
				      काष्ठा ktermios *old)
अणु
	u32 ubrlcr;
	अचिन्हित पूर्णांक baud, quot;

	/* Mask termios capabilities we करोn't support */
	termios->c_cflag &= ~CMSPAR;
	termios->c_अगरlag &= ~(BRKINT | IGNBRK);

	/* Ask the core to calculate the भागisor क्रम us */
	baud = uart_get_baud_rate(port, termios, old, port->uartclk / 4096,
						      port->uartclk / 16);
	quot = uart_get_भागisor(port, baud);

	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		ubrlcr = UBRLCR_WRDLEN5;
		अवरोध;
	हाल CS6:
		ubrlcr = UBRLCR_WRDLEN6;
		अवरोध;
	हाल CS7:
		ubrlcr = UBRLCR_WRDLEN7;
		अवरोध;
	हाल CS8:
	शेष:
		ubrlcr = UBRLCR_WRDLEN8;
		अवरोध;
	पूर्ण

	अगर (termios->c_cflag & CSTOPB)
		ubrlcr |= UBRLCR_XSTOP;

	अगर (termios->c_cflag & PARENB) अणु
		ubrlcr |= UBRLCR_PRTEN;
		अगर (!(termios->c_cflag & PARODD))
			ubrlcr |= UBRLCR_EVENPRT;
	पूर्ण

	/* Enable FIFO */
	ubrlcr |= UBRLCR_FIFOEN;

	/* Set पढ़ो status mask */
	port->पढ़ो_status_mask = UARTDR_OVERR;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= UARTDR_PARERR | UARTDR_FRMERR;

	/* Set status ignore mask */
	port->ignore_status_mask = 0;
	अगर (!(termios->c_cflag & CREAD))
		port->ignore_status_mask |= UARTDR_OVERR | UARTDR_PARERR |
					    UARTDR_FRMERR;

	uart_update_समयout(port, termios->c_cflag, baud);

	ग_लिखोl(ubrlcr | (quot - 1), port->membase + UBRLCR_OFFSET);
पूर्ण

अटल स्थिर अक्षर *uart_clps711x_type(काष्ठा uart_port *port)
अणु
	वापस (port->type == PORT_CLPS711X) ? "CLPS711X" : शून्य;
पूर्ण

अटल व्योम uart_clps711x_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE)
		port->type = PORT_CLPS711X;
पूर्ण

अटल व्योम uart_clps711x_nop_व्योम(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक uart_clps711x_nop_पूर्णांक(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uart_ops uart_clps711x_ops = अणु
	.tx_empty	= uart_clps711x_tx_empty,
	.set_mctrl	= uart_clps711x_set_mctrl,
	.get_mctrl	= uart_clps711x_get_mctrl,
	.stop_tx	= uart_clps711x_stop_tx,
	.start_tx	= uart_clps711x_start_tx,
	.stop_rx	= uart_clps711x_nop_व्योम,
	.अवरोध_ctl	= uart_clps711x_अवरोध_ctl,
	.set_ldisc	= uart_clps711x_set_ldisc,
	.startup	= uart_clps711x_startup,
	.shutकरोwn	= uart_clps711x_shutकरोwn,
	.set_termios	= uart_clps711x_set_termios,
	.type		= uart_clps711x_type,
	.config_port	= uart_clps711x_config_port,
	.release_port	= uart_clps711x_nop_व्योम,
	.request_port	= uart_clps711x_nop_पूर्णांक,
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_CLPS711X_CONSOLE
अटल व्योम uart_clps711x_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा clps711x_port *s = dev_get_drvdata(port->dev);
	u32 sysflg = 0;

	/* Wait क्रम FIFO is not full */
	करो अणु
		regmap_पढ़ो(s->syscon, SYSFLG_OFFSET, &sysflg);
	पूर्ण जबतक (sysflg & SYSFLG_UTXFF);

	ग_लिखोw(ch, port->membase + UARTDR_OFFSET);
पूर्ण

अटल व्योम uart_clps711x_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *c,
					अचिन्हित n)
अणु
	काष्ठा uart_port *port = clps711x_uart.state[co->index].uart_port;
	काष्ठा clps711x_port *s = dev_get_drvdata(port->dev);
	u32 sysflg = 0;

	uart_console_ग_लिखो(port, c, n, uart_clps711x_console_अक्षर_दो);

	/* Wait क्रम transmitter to become empty */
	करो अणु
		regmap_पढ़ो(s->syscon, SYSFLG_OFFSET, &sysflg);
	पूर्ण जबतक (sysflg & SYSFLG_UBUSY);
पूर्ण

अटल पूर्णांक uart_clps711x_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	पूर्णांक baud = 38400, bits = 8, parity = 'n', flow = 'n';
	पूर्णांक ret, index = co->index;
	काष्ठा clps711x_port *s;
	काष्ठा uart_port *port;
	अचिन्हित पूर्णांक quot;
	u32 ubrlcr;

	अगर (index < 0 || index >= UART_CLPS711X_NR)
		वापस -EINVAL;

	port = clps711x_uart.state[index].uart_port;
	अगर (!port)
		वापस -ENODEV;

	s = dev_get_drvdata(port->dev);

	अगर (!options) अणु
		u32 syscon = 0;

		regmap_पढ़ो(s->syscon, SYSCON_OFFSET, &syscon);
		अगर (syscon & SYSCON_UARTEN) अणु
			ubrlcr = पढ़ोl(port->membase + UBRLCR_OFFSET);

			अगर (ubrlcr & UBRLCR_PRTEN) अणु
				अगर (ubrlcr & UBRLCR_EVENPRT)
					parity = 'e';
				अन्यथा
					parity = 'o';
			पूर्ण

			अगर ((ubrlcr & UBRLCR_WRDLEN_MASK) == UBRLCR_WRDLEN7)
				bits = 7;

			quot = ubrlcr & UBRLCR_BAUD_MASK;
			baud = port->uartclk / (16 * (quot + 1));
		पूर्ण
	पूर्ण अन्यथा
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	ret = uart_set_options(port, co, baud, parity, bits, flow);
	अगर (ret)
		वापस ret;

	वापस regmap_update_bits(s->syscon, SYSCON_OFFSET,
				  SYSCON_UARTEN, SYSCON_UARTEN);
पूर्ण

अटल काष्ठा console clps711x_console = अणु
	.name	= UART_CLPS711X_DEVNAME,
	.device	= uart_console_device,
	.ग_लिखो	= uart_clps711x_console_ग_लिखो,
	.setup	= uart_clps711x_console_setup,
	.flags	= CON_PRINTBUFFER,
	.index	= -1,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक uart_clps711x_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा clps711x_port *s;
	काष्ठा resource *res;
	काष्ठा clk *uart_clk;
	पूर्णांक irq, ret;

	s = devm_kzalloc(&pdev->dev, माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	uart_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(uart_clk))
		वापस PTR_ERR(uart_clk);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	s->port.membase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(s->port.membase))
		वापस PTR_ERR(s->port.membase);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	s->port.irq = irq;

	s->rx_irq = platक्रमm_get_irq(pdev, 1);
	अगर (s->rx_irq < 0)
		वापस s->rx_irq;

	s->syscon = syscon_regmap_lookup_by_phandle(np, "syscon");
	अगर (IS_ERR(s->syscon))
		वापस PTR_ERR(s->syscon);

	s->port.line		= of_alias_get_id(np, "serial");
	s->port.dev		= &pdev->dev;
	s->port.iotype		= UPIO_MEM32;
	s->port.mapbase		= res->start;
	s->port.type		= PORT_CLPS711X;
	s->port.fअगरosize	= 16;
	s->port.has_sysrq	= IS_ENABLED(CONFIG_SERIAL_CLPS711X_CONSOLE);
	s->port.flags		= UPF_SKIP_TEST | UPF_FIXED_TYPE;
	s->port.uartclk		= clk_get_rate(uart_clk);
	s->port.ops		= &uart_clps711x_ops;

	platक्रमm_set_drvdata(pdev, s);

	s->gpios = mctrl_gpio_init_noस्वतः(&pdev->dev, 0);
	अगर (IS_ERR(s->gpios))
	    वापस PTR_ERR(s->gpios);

	ret = uart_add_one_port(&clps711x_uart, &s->port);
	अगर (ret)
		वापस ret;

	/* Disable port */
	अगर (!uart_console(&s->port))
		regmap_update_bits(s->syscon, SYSCON_OFFSET, SYSCON_UARTEN, 0);

	s->tx_enabled = 1;

	ret = devm_request_irq(&pdev->dev, s->port.irq, uart_clps711x_पूर्णांक_tx, 0,
			       dev_name(&pdev->dev), &s->port);
	अगर (ret) अणु
		uart_हटाओ_one_port(&clps711x_uart, &s->port);
		वापस ret;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, s->rx_irq, uart_clps711x_पूर्णांक_rx, 0,
			       dev_name(&pdev->dev), &s->port);
	अगर (ret)
		uart_हटाओ_one_port(&clps711x_uart, &s->port);

	वापस ret;
पूर्ण

अटल पूर्णांक uart_clps711x_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clps711x_port *s = platक्रमm_get_drvdata(pdev);

	वापस uart_हटाओ_one_port(&clps711x_uart, &s->port);
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused clps711x_uart_dt_ids[] = अणु
	अणु .compatible = "cirrus,ep7209-uart", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, clps711x_uart_dt_ids);

अटल काष्ठा platक्रमm_driver clps711x_uart_platक्रमm = अणु
	.driver = अणु
		.name		= "clps711x-uart",
		.of_match_table	= of_match_ptr(clps711x_uart_dt_ids),
	पूर्ण,
	.probe	= uart_clps711x_probe,
	.हटाओ	= uart_clps711x_हटाओ,
पूर्ण;

अटल पूर्णांक __init uart_clps711x_init(व्योम)
अणु
	पूर्णांक ret;

#अगर_घोषित CONFIG_SERIAL_CLPS711X_CONSOLE
	clps711x_uart.cons = &clps711x_console;
	clps711x_console.data = &clps711x_uart;
#पूर्ण_अगर

	ret = uart_रेजिस्टर_driver(&clps711x_uart);
	अगर (ret)
		वापस ret;

	वापस platक्रमm_driver_रेजिस्टर(&clps711x_uart_platक्रमm);
पूर्ण
module_init(uart_clps711x_init);

अटल व्योम __निकास uart_clps711x_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&clps711x_uart_platक्रमm);
	uart_unरेजिस्टर_driver(&clps711x_uart);
पूर्ण
module_निकास(uart_clps711x_निकास);

MODULE_AUTHOR("Deep Blue Solutions Ltd");
MODULE_DESCRIPTION("CLPS711X serial driver");
MODULE_LICENSE("GPL");
