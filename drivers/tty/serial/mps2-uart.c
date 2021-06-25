<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MPS2 UART driver
 *
 * Copyright (C) 2015 ARM Limited
 *
 * Author: Vladimir Murzin <vladimir.murzin@arm.com>
 *
 * TODO: support क्रम SysRq
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/types.h>
#समावेश <linux/idr.h>

#घोषणा SERIAL_NAME	"ttyMPS"
#घोषणा DRIVER_NAME	"mps2-uart"
#घोषणा MAKE_NAME(x)	(DRIVER_NAME # x)

#घोषणा UARTn_DATA				0x00

#घोषणा UARTn_STATE				0x04
#घोषणा UARTn_STATE_TX_FULL			BIT(0)
#घोषणा UARTn_STATE_RX_FULL			BIT(1)
#घोषणा UARTn_STATE_TX_OVERRUN			BIT(2)
#घोषणा UARTn_STATE_RX_OVERRUN			BIT(3)

#घोषणा UARTn_CTRL				0x08
#घोषणा UARTn_CTRL_TX_ENABLE			BIT(0)
#घोषणा UARTn_CTRL_RX_ENABLE			BIT(1)
#घोषणा UARTn_CTRL_TX_INT_ENABLE		BIT(2)
#घोषणा UARTn_CTRL_RX_INT_ENABLE		BIT(3)
#घोषणा UARTn_CTRL_TX_OVERRUN_INT_ENABLE	BIT(4)
#घोषणा UARTn_CTRL_RX_OVERRUN_INT_ENABLE	BIT(5)

#घोषणा UARTn_INT				0x0c
#घोषणा UARTn_INT_TX				BIT(0)
#घोषणा UARTn_INT_RX				BIT(1)
#घोषणा UARTn_INT_TX_OVERRUN			BIT(2)
#घोषणा UARTn_INT_RX_OVERRUN			BIT(3)

#घोषणा UARTn_BAUDDIV				0x10
#घोषणा UARTn_BAUDDIV_MASK			GENMASK(20, 0)

/*
 * Helpers to make typical enable/disable operations more पढ़ोable.
 */
#घोषणा UARTn_CTRL_TX_GRP	(UARTn_CTRL_TX_ENABLE		 |\
				 UARTn_CTRL_TX_INT_ENABLE	 |\
				 UARTn_CTRL_TX_OVERRUN_INT_ENABLE)

#घोषणा UARTn_CTRL_RX_GRP	(UARTn_CTRL_RX_ENABLE		 |\
				 UARTn_CTRL_RX_INT_ENABLE	 |\
				 UARTn_CTRL_RX_OVERRUN_INT_ENABLE)

#घोषणा MPS2_MAX_PORTS		3

#घोषणा UART_PORT_COMBINED_IRQ	BIT(0)

काष्ठा mps2_uart_port अणु
	काष्ठा uart_port port;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक tx_irq;
	अचिन्हित पूर्णांक rx_irq;
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल अंतरभूत काष्ठा mps2_uart_port *to_mps2_port(काष्ठा uart_port *port)
अणु
	वापस container_of(port, काष्ठा mps2_uart_port, port);
पूर्ण

अटल व्योम mps2_uart_ग_लिखो8(काष्ठा uart_port *port, u8 val, अचिन्हित पूर्णांक off)
अणु
	काष्ठा mps2_uart_port *mps_port = to_mps2_port(port);

	ग_लिखोb(val, mps_port->port.membase + off);
पूर्ण

अटल u8 mps2_uart_पढ़ो8(काष्ठा uart_port *port, अचिन्हित पूर्णांक off)
अणु
	काष्ठा mps2_uart_port *mps_port = to_mps2_port(port);

	वापस पढ़ोb(mps_port->port.membase + off);
पूर्ण

अटल व्योम mps2_uart_ग_लिखो32(काष्ठा uart_port *port, u32 val, अचिन्हित पूर्णांक off)
अणु
	काष्ठा mps2_uart_port *mps_port = to_mps2_port(port);

	ग_लिखोl_relaxed(val, mps_port->port.membase + off);
पूर्ण

अटल अचिन्हित पूर्णांक mps2_uart_tx_empty(काष्ठा uart_port *port)
अणु
	u8 status = mps2_uart_पढ़ो8(port, UARTn_STATE);

	वापस (status & UARTn_STATE_TX_FULL) ? 0 : TIOCSER_TEMT;
पूर्ण

अटल व्योम mps2_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
पूर्ण

अटल अचिन्हित पूर्णांक mps2_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस TIOCM_CAR | TIOCM_CTS | TIOCM_DSR;
पूर्ण

अटल व्योम mps2_uart_stop_tx(काष्ठा uart_port *port)
अणु
	u8 control = mps2_uart_पढ़ो8(port, UARTn_CTRL);

	control &= ~UARTn_CTRL_TX_INT_ENABLE;

	mps2_uart_ग_लिखो8(port, control, UARTn_CTRL);
पूर्ण

अटल व्योम mps2_uart_tx_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;

	जबतक (!(mps2_uart_पढ़ो8(port, UARTn_STATE) & UARTn_STATE_TX_FULL)) अणु
		अगर (port->x_अक्षर) अणु
			mps2_uart_ग_लिखो8(port, port->x_अक्षर, UARTn_DATA);
			port->x_अक्षर = 0;
			port->icount.tx++;
			जारी;
		पूर्ण

		अगर (uart_circ_empty(xmit) || uart_tx_stopped(port))
			अवरोध;

		mps2_uart_ग_लिखो8(port, xmit->buf[xmit->tail], UARTn_DATA);
		xmit->tail = (xmit->tail + 1) % UART_XMIT_SIZE;
		port->icount.tx++;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (uart_circ_empty(xmit))
		mps2_uart_stop_tx(port);
पूर्ण

अटल व्योम mps2_uart_start_tx(काष्ठा uart_port *port)
अणु
	u8 control = mps2_uart_पढ़ो8(port, UARTn_CTRL);

	control |= UARTn_CTRL_TX_INT_ENABLE;

	mps2_uart_ग_लिखो8(port, control, UARTn_CTRL);

	/*
	 * We've just unmasked the TX IRQ and now slow-starting via
	 * polling; अगर there is enough data to fill up the पूर्णांकernal
	 * ग_लिखो buffer in one go, the TX IRQ should निश्चित, at which
	 * poपूर्णांक we चयन to fully पूर्णांकerrupt-driven TX.
	 */

	mps2_uart_tx_अक्षरs(port);
पूर्ण

अटल व्योम mps2_uart_stop_rx(काष्ठा uart_port *port)
अणु
	u8 control = mps2_uart_पढ़ो8(port, UARTn_CTRL);

	control &= ~UARTn_CTRL_RX_GRP;

	mps2_uart_ग_लिखो8(port, control, UARTn_CTRL);
पूर्ण

अटल व्योम mps2_uart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक ctl)
अणु
पूर्ण

अटल व्योम mps2_uart_rx_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा tty_port *tport = &port->state->port;

	जबतक (mps2_uart_पढ़ो8(port, UARTn_STATE) & UARTn_STATE_RX_FULL) अणु
		u8 rxdata = mps2_uart_पढ़ो8(port, UARTn_DATA);

		port->icount.rx++;
		tty_insert_flip_अक्षर(&port->state->port, rxdata, TTY_NORMAL);
	पूर्ण

	tty_flip_buffer_push(tport);
पूर्ण

अटल irqवापस_t mps2_uart_rxirq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा uart_port *port = data;
	u8 irqflag = mps2_uart_पढ़ो8(port, UARTn_INT);

	अगर (unlikely(!(irqflag & UARTn_INT_RX)))
		वापस IRQ_NONE;

	spin_lock(&port->lock);

	mps2_uart_ग_लिखो8(port, UARTn_INT_RX, UARTn_INT);
	mps2_uart_rx_अक्षरs(port);

	spin_unlock(&port->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mps2_uart_txirq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा uart_port *port = data;
	u8 irqflag = mps2_uart_पढ़ो8(port, UARTn_INT);

	अगर (unlikely(!(irqflag & UARTn_INT_TX)))
		वापस IRQ_NONE;

	spin_lock(&port->lock);

	mps2_uart_ग_लिखो8(port, UARTn_INT_TX, UARTn_INT);
	mps2_uart_tx_अक्षरs(port);

	spin_unlock(&port->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mps2_uart_oerrirq(पूर्णांक irq, व्योम *data)
अणु
	irqवापस_t handled = IRQ_NONE;
	काष्ठा uart_port *port = data;
	u8 irqflag = mps2_uart_पढ़ो8(port, UARTn_INT);

	spin_lock(&port->lock);

	अगर (irqflag & UARTn_INT_RX_OVERRUN) अणु
		काष्ठा tty_port *tport = &port->state->port;

		mps2_uart_ग_लिखो8(port, UARTn_INT_RX_OVERRUN, UARTn_INT);
		port->icount.overrun++;
		tty_insert_flip_अक्षर(tport, 0, TTY_OVERRUN);
		tty_flip_buffer_push(tport);
		handled = IRQ_HANDLED;
	पूर्ण

	/*
	 * It's never been seen in practice and it never *should* happen since
	 * we check अगर there is enough room in TX buffer beक्रमe sending data.
	 * So we keep this check in हाल something suspicious has happened.
	 */
	अगर (irqflag & UARTn_INT_TX_OVERRUN) अणु
		mps2_uart_ग_लिखो8(port, UARTn_INT_TX_OVERRUN, UARTn_INT);
		handled = IRQ_HANDLED;
	पूर्ण

	spin_unlock(&port->lock);

	वापस handled;
पूर्ण

अटल irqवापस_t mps2_uart_combinedirq(पूर्णांक irq, व्योम *data)
अणु
	अगर (mps2_uart_rxirq(irq, data) == IRQ_HANDLED)
		वापस IRQ_HANDLED;

	अगर (mps2_uart_txirq(irq, data) == IRQ_HANDLED)
		वापस IRQ_HANDLED;

	अगर (mps2_uart_oerrirq(irq, data) == IRQ_HANDLED)
		वापस IRQ_HANDLED;

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक mps2_uart_startup(काष्ठा uart_port *port)
अणु
	काष्ठा mps2_uart_port *mps_port = to_mps2_port(port);
	u8 control = mps2_uart_पढ़ो8(port, UARTn_CTRL);
	पूर्णांक ret;

	control &= ~(UARTn_CTRL_RX_GRP | UARTn_CTRL_TX_GRP);

	mps2_uart_ग_लिखो8(port, control, UARTn_CTRL);

	अगर (mps_port->flags & UART_PORT_COMBINED_IRQ) अणु
		ret = request_irq(port->irq, mps2_uart_combinedirq, 0,
				  MAKE_NAME(-combined), mps_port);

		अगर (ret) अणु
			dev_err(port->dev, "failed to register combinedirq (%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = request_irq(port->irq, mps2_uart_oerrirq, IRQF_SHARED,
				  MAKE_NAME(-overrun), mps_port);

		अगर (ret) अणु
			dev_err(port->dev, "failed to register oerrirq (%d)\n", ret);
			वापस ret;
		पूर्ण

		ret = request_irq(mps_port->rx_irq, mps2_uart_rxirq, 0,
				  MAKE_NAME(-rx), mps_port);
		अगर (ret) अणु
			dev_err(port->dev, "failed to register rxirq (%d)\n", ret);
			जाओ err_मुक्त_oerrirq;
		पूर्ण

		ret = request_irq(mps_port->tx_irq, mps2_uart_txirq, 0,
				  MAKE_NAME(-tx), mps_port);
		अगर (ret) अणु
			dev_err(port->dev, "failed to register txirq (%d)\n", ret);
			जाओ err_मुक्त_rxirq;
		पूर्ण

	पूर्ण

	control |= UARTn_CTRL_RX_GRP | UARTn_CTRL_TX_GRP;

	mps2_uart_ग_लिखो8(port, control, UARTn_CTRL);

	वापस 0;

err_मुक्त_rxirq:
	मुक्त_irq(mps_port->rx_irq, mps_port);
err_मुक्त_oerrirq:
	मुक्त_irq(port->irq, mps_port);

	वापस ret;
पूर्ण

अटल व्योम mps2_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा mps2_uart_port *mps_port = to_mps2_port(port);
	u8 control = mps2_uart_पढ़ो8(port, UARTn_CTRL);

	control &= ~(UARTn_CTRL_RX_GRP | UARTn_CTRL_TX_GRP);

	mps2_uart_ग_लिखो8(port, control, UARTn_CTRL);

	अगर (!(mps_port->flags & UART_PORT_COMBINED_IRQ)) अणु
		मुक्त_irq(mps_port->rx_irq, mps_port);
		मुक्त_irq(mps_port->tx_irq, mps_port);
	पूर्ण

	मुक्त_irq(port->irq, mps_port);
पूर्ण

अटल व्योम
mps2_uart_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		      काष्ठा ktermios *old)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, baudभाग;

	termios->c_cflag &= ~(CRTSCTS | CMSPAR);
	termios->c_cflag &= ~CSIZE;
	termios->c_cflag |= CS8;
	termios->c_cflag &= ~PARENB;
	termios->c_cflag &= ~CSTOPB;

	baud = uart_get_baud_rate(port, termios, old,
			DIV_ROUND_CLOSEST(port->uartclk, UARTn_BAUDDIV_MASK),
			DIV_ROUND_CLOSEST(port->uartclk, 16));

	baudभाग = DIV_ROUND_CLOSEST(port->uartclk, baud);

	spin_lock_irqsave(&port->lock, flags);

	uart_update_समयout(port, termios->c_cflag, baud);
	mps2_uart_ग_लिखो32(port, baudभाग, UARTn_BAUDDIV);

	spin_unlock_irqrestore(&port->lock, flags);

	अगर (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);
पूर्ण

अटल स्थिर अक्षर *mps2_uart_type(काष्ठा uart_port *port)
अणु
	वापस (port->type == PORT_MPS2UART) ? DRIVER_NAME : शून्य;
पूर्ण

अटल व्योम mps2_uart_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक mps2_uart_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम mps2_uart_config_port(काष्ठा uart_port *port, पूर्णांक type)
अणु
	अगर (type & UART_CONFIG_TYPE && !mps2_uart_request_port(port))
		port->type = PORT_MPS2UART;
पूर्ण

अटल पूर्णांक mps2_uart_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *serinfo)
अणु
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा uart_ops mps2_uart_pops = अणु
	.tx_empty = mps2_uart_tx_empty,
	.set_mctrl = mps2_uart_set_mctrl,
	.get_mctrl = mps2_uart_get_mctrl,
	.stop_tx = mps2_uart_stop_tx,
	.start_tx = mps2_uart_start_tx,
	.stop_rx = mps2_uart_stop_rx,
	.अवरोध_ctl = mps2_uart_अवरोध_ctl,
	.startup = mps2_uart_startup,
	.shutकरोwn = mps2_uart_shutकरोwn,
	.set_termios = mps2_uart_set_termios,
	.type = mps2_uart_type,
	.release_port = mps2_uart_release_port,
	.request_port = mps2_uart_request_port,
	.config_port = mps2_uart_config_port,
	.verअगरy_port = mps2_uart_verअगरy_port,
पूर्ण;

अटल DEFINE_IDR(ports_idr);

#अगर_घोषित CONFIG_SERIAL_MPS2_UART_CONSOLE
अटल व्योम mps2_uart_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	जबतक (mps2_uart_पढ़ो8(port, UARTn_STATE) & UARTn_STATE_TX_FULL)
		cpu_relax();

	mps2_uart_ग_लिखो8(port, ch, UARTn_DATA);
पूर्ण

अटल व्योम mps2_uart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित पूर्णांक cnt)
अणु
	काष्ठा mps2_uart_port *mps_port = idr_find(&ports_idr, co->index);
	काष्ठा uart_port *port = &mps_port->port;

	uart_console_ग_लिखो(port, s, cnt, mps2_uart_console_अक्षर_दो);
पूर्ण

अटल पूर्णांक mps2_uart_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा mps2_uart_port *mps_port;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (co->index < 0 || co->index >= MPS2_MAX_PORTS)
		वापस -ENODEV;

	mps_port = idr_find(&ports_idr, co->index);

	अगर (!mps_port)
		वापस -ENODEV;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(&mps_port->port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver mps2_uart_driver;

अटल काष्ठा console mps2_uart_console = अणु
	.name = SERIAL_NAME,
	.device = uart_console_device,
	.ग_लिखो = mps2_uart_console_ग_लिखो,
	.setup = mps2_uart_console_setup,
	.flags = CON_PRINTBUFFER,
	.index = -1,
	.data = &mps2_uart_driver,
पूर्ण;

#घोषणा MPS2_SERIAL_CONSOLE (&mps2_uart_console)

अटल व्योम mps2_early_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	जबतक (पढ़ोb(port->membase + UARTn_STATE) & UARTn_STATE_TX_FULL)
		cpu_relax();

	ग_लिखोb((अचिन्हित अक्षर)ch, port->membase + UARTn_DATA);
पूर्ण

अटल व्योम mps2_early_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित पूर्णांक n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	uart_console_ग_लिखो(&dev->port, s, n, mps2_early_अक्षर_दो);
पूर्ण

अटल पूर्णांक __init mps2_early_console_setup(काष्ठा earlycon_device *device,
					   स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->con->ग_लिखो = mps2_early_ग_लिखो;

	वापस 0;
पूर्ण

OF_EARLYCON_DECLARE(mps2, "arm,mps2-uart", mps2_early_console_setup);

#अन्यथा
#घोषणा MPS2_SERIAL_CONSOLE शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver mps2_uart_driver = अणु
	.driver_name = DRIVER_NAME,
	.dev_name = SERIAL_NAME,
	.nr = MPS2_MAX_PORTS,
	.cons = MPS2_SERIAL_CONSOLE,
पूर्ण;

अटल पूर्णांक mps2_of_get_port(काष्ठा platक्रमm_device *pdev,
			    काष्ठा mps2_uart_port *mps_port)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक id;

	अगर (!np)
		वापस -ENODEV;

	id = of_alias_get_id(np, "serial");

	अगर (id < 0)
		id = idr_alloc_cyclic(&ports_idr, (व्योम *)mps_port, 0, MPS2_MAX_PORTS, GFP_KERNEL);
	अन्यथा
		id = idr_alloc(&ports_idr, (व्योम *)mps_port, id, MPS2_MAX_PORTS, GFP_KERNEL);

	अगर (id < 0)
		वापस id;

	/* Only combined irq is presesnt */
	अगर (platक्रमm_irq_count(pdev) == 1)
		mps_port->flags |= UART_PORT_COMBINED_IRQ;

	mps_port->port.line = id;

	वापस 0;
पूर्ण

अटल पूर्णांक mps2_init_port(काष्ठा platक्रमm_device *pdev,
			  काष्ठा mps2_uart_port *mps_port)
अणु
	काष्ठा resource *res;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mps_port->port.membase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mps_port->port.membase))
		वापस PTR_ERR(mps_port->port.membase);

	mps_port->port.mapbase = res->start;
	mps_port->port.mapsize = resource_size(res);
	mps_port->port.iotype = UPIO_MEM;
	mps_port->port.flags = UPF_BOOT_AUTOCONF;
	mps_port->port.fअगरosize = 1;
	mps_port->port.ops = &mps2_uart_pops;
	mps_port->port.dev = &pdev->dev;

	mps_port->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(mps_port->clk))
		वापस PTR_ERR(mps_port->clk);

	ret = clk_prepare_enable(mps_port->clk);
	अगर (ret)
		वापस ret;

	mps_port->port.uartclk = clk_get_rate(mps_port->clk);

	clk_disable_unprepare(mps_port->clk);


	अगर (mps_port->flags & UART_PORT_COMBINED_IRQ) अणु
		mps_port->port.irq = platक्रमm_get_irq(pdev, 0);
	पूर्ण अन्यथा अणु
		mps_port->rx_irq = platक्रमm_get_irq(pdev, 0);
		mps_port->tx_irq = platक्रमm_get_irq(pdev, 1);
		mps_port->port.irq = platक्रमm_get_irq(pdev, 2);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mps2_serial_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mps2_uart_port *mps_port;
	पूर्णांक ret;

	mps_port = devm_kzalloc(&pdev->dev, माप(काष्ठा mps2_uart_port), GFP_KERNEL);

        अगर (!mps_port)
                वापस -ENOMEM;

	ret = mps2_of_get_port(pdev, mps_port);
	अगर (ret)
		वापस ret;

	ret = mps2_init_port(pdev, mps_port);
	अगर (ret)
		वापस ret;

	ret = uart_add_one_port(&mps2_uart_driver, &mps_port->port);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, mps_port);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mps2_match[] = अणु
	अणु .compatible = "arm,mps2-uart", पूर्ण,
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver mps2_serial_driver = अणु
	.probe = mps2_serial_probe,

	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = of_match_ptr(mps2_match),
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mps2_uart_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&mps2_uart_driver);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&mps2_serial_driver);
	अगर (ret)
		uart_unरेजिस्टर_driver(&mps2_uart_driver);

	वापस ret;
पूर्ण
arch_initcall(mps2_uart_init);
