<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Driver क्रम Conexant Digicolor serial ports (USART)
 *
 * Author: Baruch Siach <baruch@tkos.co.il>
 *
 * Copyright (C) 2014 Paraकरोx Innovation Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/console.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>

#घोषणा UA_ENABLE			0x00
#घोषणा UA_ENABLE_ENABLE		BIT(0)

#घोषणा UA_CONTROL			0x01
#घोषणा UA_CONTROL_RX_ENABLE		BIT(0)
#घोषणा UA_CONTROL_TX_ENABLE		BIT(1)
#घोषणा UA_CONTROL_SOFT_RESET		BIT(2)

#घोषणा UA_STATUS			0x02
#घोषणा UA_STATUS_PARITY_ERR		BIT(0)
#घोषणा UA_STATUS_FRAME_ERR		BIT(1)
#घोषणा UA_STATUS_OVERRUN_ERR		BIT(2)
#घोषणा UA_STATUS_TX_READY		BIT(6)

#घोषणा UA_CONFIG			0x03
#घोषणा UA_CONFIG_CHAR_LEN		BIT(0)
#घोषणा UA_CONFIG_STOP_BITS		BIT(1)
#घोषणा UA_CONFIG_PARITY		BIT(2)
#घोषणा UA_CONFIG_ODD_PARITY		BIT(4)

#घोषणा UA_EMI_REC			0x04

#घोषणा UA_HBAUD_LO			0x08
#घोषणा UA_HBAUD_HI			0x09

#घोषणा UA_STATUS_FIFO			0x0a
#घोषणा UA_STATUS_FIFO_RX_EMPTY		BIT(2)
#घोषणा UA_STATUS_FIFO_RX_INT_ALMOST	BIT(3)
#घोषणा UA_STATUS_FIFO_TX_FULL		BIT(4)
#घोषणा UA_STATUS_FIFO_TX_INT_ALMOST	BIT(7)

#घोषणा UA_CONFIG_FIFO			0x0b
#घोषणा UA_CONFIG_FIFO_RX_THRESH	7
#घोषणा UA_CONFIG_FIFO_RX_FIFO_MODE	BIT(3)
#घोषणा UA_CONFIG_FIFO_TX_FIFO_MODE	BIT(7)

#घोषणा UA_INTFLAG_CLEAR		0x1c
#घोषणा UA_INTFLAG_SET			0x1d
#घोषणा UA_INT_ENABLE			0x1e
#घोषणा UA_INT_STATUS			0x1f

#घोषणा UA_INT_TX			BIT(0)
#घोषणा UA_INT_RX			BIT(1)

#घोषणा DIGICOLOR_USART_NR		3

/*
 * We use the 16 bytes hardware FIFO to buffer Rx traffic. Rx पूर्णांकerrupt is
 * only produced when the FIFO is filled more than a certain configurable
 * threshold. Unक्रमtunately, there is no way to set this threshold below half
 * FIFO. This means that we must periodically poll the FIFO status रेजिस्टर to
 * see whether there are रुकोing Rx bytes.
 */

काष्ठा digicolor_port अणु
	काष्ठा uart_port port;
	काष्ठा delayed_work rx_poll_work;
पूर्ण;

अटल काष्ठा uart_port *digicolor_ports[DIGICOLOR_USART_NR];

अटल bool digicolor_uart_tx_full(काष्ठा uart_port *port)
अणु
	वापस !!(पढ़ोb_relaxed(port->membase + UA_STATUS_FIFO) &
		  UA_STATUS_FIFO_TX_FULL);
पूर्ण

अटल bool digicolor_uart_rx_empty(काष्ठा uart_port *port)
अणु
	वापस !!(पढ़ोb_relaxed(port->membase + UA_STATUS_FIFO) &
		  UA_STATUS_FIFO_RX_EMPTY);
पूर्ण

अटल व्योम digicolor_uart_stop_tx(काष्ठा uart_port *port)
अणु
	u8 पूर्णांक_enable = पढ़ोb_relaxed(port->membase + UA_INT_ENABLE);

	पूर्णांक_enable &= ~UA_INT_TX;
	ग_लिखोb_relaxed(पूर्णांक_enable, port->membase + UA_INT_ENABLE);
पूर्ण

अटल व्योम digicolor_uart_start_tx(काष्ठा uart_port *port)
अणु
	u8 पूर्णांक_enable = पढ़ोb_relaxed(port->membase + UA_INT_ENABLE);

	पूर्णांक_enable |= UA_INT_TX;
	ग_लिखोb_relaxed(पूर्णांक_enable, port->membase + UA_INT_ENABLE);
पूर्ण

अटल व्योम digicolor_uart_stop_rx(काष्ठा uart_port *port)
अणु
	u8 पूर्णांक_enable = पढ़ोb_relaxed(port->membase + UA_INT_ENABLE);

	पूर्णांक_enable &= ~UA_INT_RX;
	ग_लिखोb_relaxed(पूर्णांक_enable, port->membase + UA_INT_ENABLE);
पूर्ण

अटल व्योम digicolor_rx_poll(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा digicolor_port *dp =
		container_of(to_delayed_work(work),
			     काष्ठा digicolor_port, rx_poll_work);

	अगर (!digicolor_uart_rx_empty(&dp->port))
		/* क्रमce RX पूर्णांकerrupt */
		ग_लिखोb_relaxed(UA_INT_RX, dp->port.membase + UA_INTFLAG_SET);

	schedule_delayed_work(&dp->rx_poll_work, msecs_to_jअगरfies(100));
पूर्ण

अटल व्योम digicolor_uart_rx(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	जबतक (1) अणु
		u8 status, ch;
		अचिन्हित पूर्णांक ch_flag;

		अगर (digicolor_uart_rx_empty(port))
			अवरोध;

		ch = पढ़ोb_relaxed(port->membase + UA_EMI_REC);
		status = पढ़ोb_relaxed(port->membase + UA_STATUS);

		port->icount.rx++;
		ch_flag = TTY_NORMAL;

		अगर (status) अणु
			अगर (status & UA_STATUS_PARITY_ERR)
				port->icount.parity++;
			अन्यथा अगर (status & UA_STATUS_FRAME_ERR)
				port->icount.frame++;
			अन्यथा अगर (status & UA_STATUS_OVERRUN_ERR)
				port->icount.overrun++;

			status &= port->पढ़ो_status_mask;

			अगर (status & UA_STATUS_PARITY_ERR)
				ch_flag = TTY_PARITY;
			अन्यथा अगर (status & UA_STATUS_FRAME_ERR)
				ch_flag = TTY_FRAME;
			अन्यथा अगर (status & UA_STATUS_OVERRUN_ERR)
				ch_flag = TTY_OVERRUN;
		पूर्ण

		अगर (status & port->ignore_status_mask)
			जारी;

		uart_insert_अक्षर(port, status, UA_STATUS_OVERRUN_ERR, ch,
				 ch_flag);
	पूर्ण

	spin_unlock_irqrestore(&port->lock, flags);

	tty_flip_buffer_push(&port->state->port);
पूर्ण

अटल व्योम digicolor_uart_tx(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित दीर्घ flags;

	अगर (digicolor_uart_tx_full(port))
		वापस;

	spin_lock_irqsave(&port->lock, flags);

	अगर (port->x_अक्षर) अणु
		ग_लिखोb_relaxed(port->x_अक्षर, port->membase + UA_EMI_REC);
		port->icount.tx++;
		port->x_अक्षर = 0;
		जाओ out;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		digicolor_uart_stop_tx(port);
		जाओ out;
	पूर्ण

	जबतक (!uart_circ_empty(xmit)) अणु
		ग_लिखोb(xmit->buf[xmit->tail], port->membase + UA_EMI_REC);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;

		अगर (digicolor_uart_tx_full(port))
			अवरोध;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

out:
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल irqवापस_t digicolor_uart_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	u8 पूर्णांक_status = पढ़ोb_relaxed(port->membase + UA_INT_STATUS);

	ग_लिखोb_relaxed(UA_INT_RX | UA_INT_TX,
		       port->membase + UA_INTFLAG_CLEAR);

	अगर (पूर्णांक_status & UA_INT_RX)
		digicolor_uart_rx(port);
	अगर (पूर्णांक_status & UA_INT_TX)
		digicolor_uart_tx(port);

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक digicolor_uart_tx_empty(काष्ठा uart_port *port)
अणु
	u8 status = पढ़ोb_relaxed(port->membase + UA_STATUS);

	वापस (status & UA_STATUS_TX_READY) ? TIOCSER_TEMT : 0;
पूर्ण

अटल अचिन्हित पूर्णांक digicolor_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस TIOCM_CTS;
पूर्ण

अटल व्योम digicolor_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
पूर्ण

अटल व्योम digicolor_uart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक state)
अणु
पूर्ण

अटल पूर्णांक digicolor_uart_startup(काष्ठा uart_port *port)
अणु
	काष्ठा digicolor_port *dp =
		container_of(port, काष्ठा digicolor_port, port);

	ग_लिखोb_relaxed(UA_ENABLE_ENABLE, port->membase + UA_ENABLE);
	ग_लिखोb_relaxed(UA_CONTROL_SOFT_RESET, port->membase + UA_CONTROL);
	ग_लिखोb_relaxed(0, port->membase + UA_CONTROL);

	ग_लिखोb_relaxed(UA_CONFIG_FIFO_RX_FIFO_MODE
		       | UA_CONFIG_FIFO_TX_FIFO_MODE | UA_CONFIG_FIFO_RX_THRESH,
		       port->membase + UA_CONFIG_FIFO);
	ग_लिखोb_relaxed(UA_STATUS_FIFO_RX_INT_ALMOST,
		       port->membase + UA_STATUS_FIFO);
	ग_लिखोb_relaxed(UA_CONTROL_RX_ENABLE | UA_CONTROL_TX_ENABLE,
		       port->membase + UA_CONTROL);
	ग_लिखोb_relaxed(UA_INT_TX | UA_INT_RX,
		       port->membase + UA_INT_ENABLE);

	schedule_delayed_work(&dp->rx_poll_work, msecs_to_jअगरfies(100));

	वापस 0;
पूर्ण

अटल व्योम digicolor_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा digicolor_port *dp =
		container_of(port, काष्ठा digicolor_port, port);

	ग_लिखोb_relaxed(0, port->membase + UA_ENABLE);
	cancel_delayed_work_sync(&dp->rx_poll_work);
पूर्ण

अटल व्योम digicolor_uart_set_termios(काष्ठा uart_port *port,
				       काष्ठा ktermios *termios,
				       काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक baud, भागisor;
	u8 config = 0;
	अचिन्हित दीर्घ flags;

	/* Mask termios capabilities we करोn't support */
	termios->c_cflag &= ~CMSPAR;
	termios->c_अगरlag &= ~(BRKINT | IGNBRK);

	/* Limit baud rates so that we करोn't need the fractional भागider */
	baud = uart_get_baud_rate(port, termios, old,
				  port->uartclk / (0x10000*16),
				  port->uartclk / 256);
	भागisor = uart_get_भागisor(port, baud) - 1;

	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS7:
		अवरोध;
	हाल CS8:
	शेष:
		config |= UA_CONFIG_CHAR_LEN;
		अवरोध;
	पूर्ण

	अगर (termios->c_cflag & CSTOPB)
		config |= UA_CONFIG_STOP_BITS;

	अगर (termios->c_cflag & PARENB) अणु
		config |= UA_CONFIG_PARITY;
		अगर (termios->c_cflag & PARODD)
			config |= UA_CONFIG_ODD_PARITY;
	पूर्ण

	/* Set पढ़ो status mask */
	port->पढ़ो_status_mask = UA_STATUS_OVERRUN_ERR;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= UA_STATUS_PARITY_ERR
			| UA_STATUS_FRAME_ERR;

	/* Set status ignore mask */
	port->ignore_status_mask = 0;
	अगर (!(termios->c_cflag & CREAD))
		port->ignore_status_mask |= UA_STATUS_OVERRUN_ERR
			| UA_STATUS_PARITY_ERR | UA_STATUS_FRAME_ERR;

	spin_lock_irqsave(&port->lock, flags);

	uart_update_समयout(port, termios->c_cflag, baud);

	ग_लिखोb_relaxed(config, port->membase + UA_CONFIG);
	ग_लिखोb_relaxed(भागisor & 0xff, port->membase + UA_HBAUD_LO);
	ग_लिखोb_relaxed(भागisor >> 8, port->membase + UA_HBAUD_HI);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *digicolor_uart_type(काष्ठा uart_port *port)
अणु
	वापस (port->type == PORT_DIGICOLOR) ? "DIGICOLOR USART" : शून्य;
पूर्ण

अटल व्योम digicolor_uart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE)
		port->type = PORT_DIGICOLOR;
पूर्ण

अटल व्योम digicolor_uart_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक digicolor_uart_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uart_ops digicolor_uart_ops = अणु
	.tx_empty	= digicolor_uart_tx_empty,
	.set_mctrl	= digicolor_uart_set_mctrl,
	.get_mctrl	= digicolor_uart_get_mctrl,
	.stop_tx	= digicolor_uart_stop_tx,
	.start_tx	= digicolor_uart_start_tx,
	.stop_rx	= digicolor_uart_stop_rx,
	.अवरोध_ctl	= digicolor_uart_अवरोध_ctl,
	.startup	= digicolor_uart_startup,
	.shutकरोwn	= digicolor_uart_shutकरोwn,
	.set_termios	= digicolor_uart_set_termios,
	.type		= digicolor_uart_type,
	.config_port	= digicolor_uart_config_port,
	.release_port	= digicolor_uart_release_port,
	.request_port	= digicolor_uart_request_port,
पूर्ण;

अटल व्योम digicolor_uart_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	जबतक (digicolor_uart_tx_full(port))
		cpu_relax();

	ग_लिखोb_relaxed(ch, port->membase + UA_EMI_REC);
पूर्ण

अटल व्योम digicolor_uart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *c,
					 अचिन्हित n)
अणु
	काष्ठा uart_port *port = digicolor_ports[co->index];
	u8 status;
	अचिन्हित दीर्घ flags;
	पूर्णांक locked = 1;

	अगर (oops_in_progress)
		locked = spin_trylock_irqsave(&port->lock, flags);
	अन्यथा
		spin_lock_irqsave(&port->lock, flags);

	uart_console_ग_लिखो(port, c, n, digicolor_uart_console_अक्षर_दो);

	अगर (locked)
		spin_unlock_irqrestore(&port->lock, flags);

	/* Wait क्रम transmitter to become empty */
	करो अणु
		status = पढ़ोb_relaxed(port->membase + UA_STATUS);
	पूर्ण जबतक ((status & UA_STATUS_TX_READY) == 0);
पूर्ण

अटल पूर्णांक digicolor_uart_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	पूर्णांक baud = 115200, bits = 8, parity = 'n', flow = 'n';
	काष्ठा uart_port *port;

	अगर (co->index < 0 || co->index >= DIGICOLOR_USART_NR)
		वापस -EINVAL;

	port = digicolor_ports[co->index];
	अगर (!port)
		वापस -ENODEV;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा console digicolor_console = अणु
	.name	= "ttyS",
	.device	= uart_console_device,
	.ग_लिखो	= digicolor_uart_console_ग_लिखो,
	.setup	= digicolor_uart_console_setup,
	.flags	= CON_PRINTBUFFER,
	.index	= -1,
पूर्ण;

अटल काष्ठा uart_driver digicolor_uart = अणु
	.driver_name	= "digicolor-usart",
	.dev_name	= "ttyS",
	.nr		= DIGICOLOR_USART_NR,
पूर्ण;

अटल पूर्णांक digicolor_uart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक irq, ret, index;
	काष्ठा digicolor_port *dp;
	काष्ठा resource *res;
	काष्ठा clk *uart_clk;

	अगर (!np) अणु
		dev_err(&pdev->dev, "Missing device tree node\n");
		वापस -ENXIO;
	पूर्ण

	index = of_alias_get_id(np, "serial");
	अगर (index < 0 || index >= DIGICOLOR_USART_NR)
		वापस -EINVAL;

	dp = devm_kzalloc(&pdev->dev, माप(*dp), GFP_KERNEL);
	अगर (!dp)
		वापस -ENOMEM;

	uart_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(uart_clk))
		वापस PTR_ERR(uart_clk);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dp->port.mapbase = res->start;
	dp->port.membase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(dp->port.membase))
		वापस PTR_ERR(dp->port.membase);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	dp->port.irq = irq;

	dp->port.iotype = UPIO_MEM;
	dp->port.uartclk = clk_get_rate(uart_clk);
	dp->port.fअगरosize = 16;
	dp->port.dev = &pdev->dev;
	dp->port.ops = &digicolor_uart_ops;
	dp->port.line = index;
	dp->port.type = PORT_DIGICOLOR;
	spin_lock_init(&dp->port.lock);

	digicolor_ports[index] = &dp->port;
	platक्रमm_set_drvdata(pdev, &dp->port);

	INIT_DELAYED_WORK(&dp->rx_poll_work, digicolor_rx_poll);

	ret = devm_request_irq(&pdev->dev, dp->port.irq, digicolor_uart_पूर्णांक, 0,
			       dev_name(&pdev->dev), &dp->port);
	अगर (ret)
		वापस ret;

	वापस uart_add_one_port(&digicolor_uart, &dp->port);
पूर्ण

अटल पूर्णांक digicolor_uart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port = platक्रमm_get_drvdata(pdev);

	uart_हटाओ_one_port(&digicolor_uart, port);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id digicolor_uart_dt_ids[] = अणु
	अणु .compatible = "cnxt,cx92755-usart", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, digicolor_uart_dt_ids);

अटल काष्ठा platक्रमm_driver digicolor_uart_platक्रमm = अणु
	.driver = अणु
		.name		= "digicolor-usart",
		.of_match_table	= of_match_ptr(digicolor_uart_dt_ids),
	पूर्ण,
	.probe	= digicolor_uart_probe,
	.हटाओ	= digicolor_uart_हटाओ,
पूर्ण;

अटल पूर्णांक __init digicolor_uart_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (IS_ENABLED(CONFIG_SERIAL_CONEXANT_DIGICOLOR_CONSOLE)) अणु
		digicolor_uart.cons = &digicolor_console;
		digicolor_console.data = &digicolor_uart;
	पूर्ण

	ret = uart_रेजिस्टर_driver(&digicolor_uart);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&digicolor_uart_platक्रमm);
	अगर (ret)
		uart_unरेजिस्टर_driver(&digicolor_uart);

	वापस ret;
पूर्ण
module_init(digicolor_uart_init);

अटल व्योम __निकास digicolor_uart_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&digicolor_uart_platक्रमm);
	uart_unरेजिस्टर_driver(&digicolor_uart);
पूर्ण
module_निकास(digicolor_uart_निकास);

MODULE_AUTHOR("Baruch Siach <baruch@tkos.co.il>");
MODULE_DESCRIPTION("Conexant Digicolor USART serial driver");
MODULE_LICENSE("GPL");
