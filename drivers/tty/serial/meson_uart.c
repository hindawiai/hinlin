<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Based on meson_uart.c, by AMLOGIC, INC.
 *
 * Copyright (C) 2014 Carlo Caione <carlo@caione.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

/* Register offsets */
#घोषणा AML_UART_WFIFO			0x00
#घोषणा AML_UART_RFIFO			0x04
#घोषणा AML_UART_CONTROL		0x08
#घोषणा AML_UART_STATUS			0x0c
#घोषणा AML_UART_MISC			0x10
#घोषणा AML_UART_REG5			0x14

/* AML_UART_CONTROL bits */
#घोषणा AML_UART_TX_EN			BIT(12)
#घोषणा AML_UART_RX_EN			BIT(13)
#घोषणा AML_UART_TWO_WIRE_EN		BIT(15)
#घोषणा AML_UART_STOP_BIT_LEN_MASK	(0x03 << 16)
#घोषणा AML_UART_STOP_BIT_1SB		(0x00 << 16)
#घोषणा AML_UART_STOP_BIT_2SB		(0x01 << 16)
#घोषणा AML_UART_PARITY_TYPE		BIT(18)
#घोषणा AML_UART_PARITY_EN		BIT(19)
#घोषणा AML_UART_TX_RST			BIT(22)
#घोषणा AML_UART_RX_RST			BIT(23)
#घोषणा AML_UART_CLEAR_ERR		BIT(24)
#घोषणा AML_UART_RX_INT_EN		BIT(27)
#घोषणा AML_UART_TX_INT_EN		BIT(28)
#घोषणा AML_UART_DATA_LEN_MASK		(0x03 << 20)
#घोषणा AML_UART_DATA_LEN_8BIT		(0x00 << 20)
#घोषणा AML_UART_DATA_LEN_7BIT		(0x01 << 20)
#घोषणा AML_UART_DATA_LEN_6BIT		(0x02 << 20)
#घोषणा AML_UART_DATA_LEN_5BIT		(0x03 << 20)

/* AML_UART_STATUS bits */
#घोषणा AML_UART_PARITY_ERR		BIT(16)
#घोषणा AML_UART_FRAME_ERR		BIT(17)
#घोषणा AML_UART_TX_FIFO_WERR		BIT(18)
#घोषणा AML_UART_RX_EMPTY		BIT(20)
#घोषणा AML_UART_TX_FULL		BIT(21)
#घोषणा AML_UART_TX_EMPTY		BIT(22)
#घोषणा AML_UART_XMIT_BUSY		BIT(25)
#घोषणा AML_UART_ERR			(AML_UART_PARITY_ERR | \
					 AML_UART_FRAME_ERR  | \
					 AML_UART_TX_FIFO_WERR)

/* AML_UART_MISC bits */
#घोषणा AML_UART_XMIT_IRQ(c)		(((c) & 0xff) << 8)
#घोषणा AML_UART_RECV_IRQ(c)		((c) & 0xff)

/* AML_UART_REG5 bits */
#घोषणा AML_UART_BAUD_MASK		0x7fffff
#घोषणा AML_UART_BAUD_USE		BIT(23)
#घोषणा AML_UART_BAUD_XTAL		BIT(24)

#घोषणा AML_UART_PORT_NUM		12
#घोषणा AML_UART_PORT_OFFSET		6
#घोषणा AML_UART_DEV_NAME		"ttyAML"

#घोषणा AML_UART_POLL_USEC		5
#घोषणा AML_UART_TIMEOUT_USEC		10000

अटल काष्ठा uart_driver meson_uart_driver;

अटल काष्ठा uart_port *meson_ports[AML_UART_PORT_NUM];

अटल व्योम meson_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
पूर्ण

अटल अचिन्हित पूर्णांक meson_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस TIOCM_CTS;
पूर्ण

अटल अचिन्हित पूर्णांक meson_uart_tx_empty(काष्ठा uart_port *port)
अणु
	u32 val;

	val = पढ़ोl(port->membase + AML_UART_STATUS);
	val &= (AML_UART_TX_EMPTY | AML_UART_XMIT_BUSY);
	वापस (val == AML_UART_TX_EMPTY) ? TIOCSER_TEMT : 0;
पूर्ण

अटल व्योम meson_uart_stop_tx(काष्ठा uart_port *port)
अणु
	u32 val;

	val = पढ़ोl(port->membase + AML_UART_CONTROL);
	val &= ~AML_UART_TX_INT_EN;
	ग_लिखोl(val, port->membase + AML_UART_CONTROL);
पूर्ण

अटल व्योम meson_uart_stop_rx(काष्ठा uart_port *port)
अणु
	u32 val;

	val = पढ़ोl(port->membase + AML_UART_CONTROL);
	val &= ~AML_UART_RX_EN;
	ग_लिखोl(val, port->membase + AML_UART_CONTROL);
पूर्ण

अटल व्योम meson_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	मुक्त_irq(port->irq, port);

	spin_lock_irqsave(&port->lock, flags);

	val = पढ़ोl(port->membase + AML_UART_CONTROL);
	val &= ~AML_UART_RX_EN;
	val &= ~(AML_UART_RX_INT_EN | AML_UART_TX_INT_EN);
	ग_लिखोl(val, port->membase + AML_UART_CONTROL);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम meson_uart_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित पूर्णांक ch;
	u32 val;

	अगर (uart_tx_stopped(port)) अणु
		meson_uart_stop_tx(port);
		वापस;
	पूर्ण

	जबतक (!(पढ़ोl(port->membase + AML_UART_STATUS) & AML_UART_TX_FULL)) अणु
		अगर (port->x_अक्षर) अणु
			ग_लिखोl(port->x_अक्षर, port->membase + AML_UART_WFIFO);
			port->icount.tx++;
			port->x_अक्षर = 0;
			जारी;
		पूर्ण

		अगर (uart_circ_empty(xmit))
			अवरोध;

		ch = xmit->buf[xmit->tail];
		ग_लिखोl(ch, port->membase + AML_UART_WFIFO);
		xmit->tail = (xmit->tail+1) & (SERIAL_XMIT_SIZE - 1);
		port->icount.tx++;
	पूर्ण

	अगर (!uart_circ_empty(xmit)) अणु
		val = पढ़ोl(port->membase + AML_UART_CONTROL);
		val |= AML_UART_TX_INT_EN;
		ग_लिखोl(val, port->membase + AML_UART_CONTROL);
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);
पूर्ण

अटल व्योम meson_receive_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा tty_port *tport = &port->state->port;
	अक्षर flag;
	u32 ostatus, status, ch, mode;

	करो अणु
		flag = TTY_NORMAL;
		port->icount.rx++;
		ostatus = status = पढ़ोl(port->membase + AML_UART_STATUS);

		अगर (status & AML_UART_ERR) अणु
			अगर (status & AML_UART_TX_FIFO_WERR)
				port->icount.overrun++;
			अन्यथा अगर (status & AML_UART_FRAME_ERR)
				port->icount.frame++;
			अन्यथा अगर (status & AML_UART_PARITY_ERR)
				port->icount.frame++;

			mode = पढ़ोl(port->membase + AML_UART_CONTROL);
			mode |= AML_UART_CLEAR_ERR;
			ग_लिखोl(mode, port->membase + AML_UART_CONTROL);

			/* It करोesn't clear to 0 स्वतःmatically */
			mode &= ~AML_UART_CLEAR_ERR;
			ग_लिखोl(mode, port->membase + AML_UART_CONTROL);

			status &= port->पढ़ो_status_mask;
			अगर (status & AML_UART_FRAME_ERR)
				flag = TTY_FRAME;
			अन्यथा अगर (status & AML_UART_PARITY_ERR)
				flag = TTY_PARITY;
		पूर्ण

		ch = पढ़ोl(port->membase + AML_UART_RFIFO);
		ch &= 0xff;

		अगर ((ostatus & AML_UART_FRAME_ERR) && (ch == 0)) अणु
			port->icount.brk++;
			flag = TTY_BREAK;
			अगर (uart_handle_अवरोध(port))
				जारी;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(port, ch))
			जारी;

		अगर ((status & port->ignore_status_mask) == 0)
			tty_insert_flip_अक्षर(tport, ch, flag);

		अगर (status & AML_UART_TX_FIFO_WERR)
			tty_insert_flip_अक्षर(tport, 0, TTY_OVERRUN);

	पूर्ण जबतक (!(पढ़ोl(port->membase + AML_UART_STATUS) & AML_UART_RX_EMPTY));

	tty_flip_buffer_push(tport);
पूर्ण

अटल irqवापस_t meson_uart_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = (काष्ठा uart_port *)dev_id;

	spin_lock(&port->lock);

	अगर (!(पढ़ोl(port->membase + AML_UART_STATUS) & AML_UART_RX_EMPTY))
		meson_receive_अक्षरs(port);

	अगर (!(पढ़ोl(port->membase + AML_UART_STATUS) & AML_UART_TX_FULL)) अणु
		अगर (पढ़ोl(port->membase + AML_UART_CONTROL) & AML_UART_TX_INT_EN)
			meson_uart_start_tx(port);
	पूर्ण

	spin_unlock(&port->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर अक्षर *meson_uart_type(काष्ठा uart_port *port)
अणु
	वापस (port->type == PORT_MESON) ? "meson_uart" : शून्य;
पूर्ण

अटल व्योम meson_uart_reset(काष्ठा uart_port *port)
अणु
	u32 val;

	val = पढ़ोl(port->membase + AML_UART_CONTROL);
	val |= (AML_UART_RX_RST | AML_UART_TX_RST | AML_UART_CLEAR_ERR);
	ग_लिखोl(val, port->membase + AML_UART_CONTROL);

	val &= ~(AML_UART_RX_RST | AML_UART_TX_RST | AML_UART_CLEAR_ERR);
	ग_लिखोl(val, port->membase + AML_UART_CONTROL);
पूर्ण

अटल पूर्णांक meson_uart_startup(काष्ठा uart_port *port)
अणु
	u32 val;
	पूर्णांक ret = 0;

	val = पढ़ोl(port->membase + AML_UART_CONTROL);
	val |= AML_UART_CLEAR_ERR;
	ग_लिखोl(val, port->membase + AML_UART_CONTROL);
	val &= ~AML_UART_CLEAR_ERR;
	ग_लिखोl(val, port->membase + AML_UART_CONTROL);

	val |= (AML_UART_RX_EN | AML_UART_TX_EN);
	ग_लिखोl(val, port->membase + AML_UART_CONTROL);

	val |= (AML_UART_RX_INT_EN | AML_UART_TX_INT_EN);
	ग_लिखोl(val, port->membase + AML_UART_CONTROL);

	val = (AML_UART_RECV_IRQ(1) | AML_UART_XMIT_IRQ(port->fअगरosize / 2));
	ग_लिखोl(val, port->membase + AML_UART_MISC);

	ret = request_irq(port->irq, meson_uart_पूर्णांकerrupt, 0,
			  port->name, port);

	वापस ret;
पूर्ण

अटल व्योम meson_uart_change_speed(काष्ठा uart_port *port, अचिन्हित दीर्घ baud)
अणु
	u32 val;

	जबतक (!meson_uart_tx_empty(port))
		cpu_relax();

	अगर (port->uartclk == 24000000) अणु
		val = ((port->uartclk / 3) / baud) - 1;
		val |= AML_UART_BAUD_XTAL;
	पूर्ण अन्यथा अणु
		val = ((port->uartclk * 10 / (baud * 4) + 5) / 10) - 1;
	पूर्ण
	val |= AML_UART_BAUD_USE;
	ग_लिखोl(val, port->membase + AML_UART_REG5);
पूर्ण

अटल व्योम meson_uart_set_termios(काष्ठा uart_port *port,
				   काष्ठा ktermios *termios,
				   काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक cflags, अगरlags, baud;
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&port->lock, flags);

	cflags = termios->c_cflag;
	अगरlags = termios->c_अगरlag;

	val = पढ़ोl(port->membase + AML_UART_CONTROL);

	val &= ~AML_UART_DATA_LEN_MASK;
	चयन (cflags & CSIZE) अणु
	हाल CS8:
		val |= AML_UART_DATA_LEN_8BIT;
		अवरोध;
	हाल CS7:
		val |= AML_UART_DATA_LEN_7BIT;
		अवरोध;
	हाल CS6:
		val |= AML_UART_DATA_LEN_6BIT;
		अवरोध;
	हाल CS5:
		val |= AML_UART_DATA_LEN_5BIT;
		अवरोध;
	पूर्ण

	अगर (cflags & PARENB)
		val |= AML_UART_PARITY_EN;
	अन्यथा
		val &= ~AML_UART_PARITY_EN;

	अगर (cflags & PARODD)
		val |= AML_UART_PARITY_TYPE;
	अन्यथा
		val &= ~AML_UART_PARITY_TYPE;

	val &= ~AML_UART_STOP_BIT_LEN_MASK;
	अगर (cflags & CSTOPB)
		val |= AML_UART_STOP_BIT_2SB;
	अन्यथा
		val |= AML_UART_STOP_BIT_1SB;

	अगर (cflags & CRTSCTS)
		val &= ~AML_UART_TWO_WIRE_EN;
	अन्यथा
		val |= AML_UART_TWO_WIRE_EN;

	ग_लिखोl(val, port->membase + AML_UART_CONTROL);

	baud = uart_get_baud_rate(port, termios, old, 50, 4000000);
	meson_uart_change_speed(port, baud);

	port->पढ़ो_status_mask = AML_UART_TX_FIFO_WERR;
	अगर (अगरlags & INPCK)
		port->पढ़ो_status_mask |= AML_UART_PARITY_ERR |
					  AML_UART_FRAME_ERR;

	port->ignore_status_mask = 0;
	अगर (अगरlags & IGNPAR)
		port->ignore_status_mask |= AML_UART_PARITY_ERR |
					    AML_UART_FRAME_ERR;

	uart_update_समयout(port, termios->c_cflag, baud);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल पूर्णांक meson_uart_verअगरy_port(काष्ठा uart_port *port,
				  काष्ठा serial_काष्ठा *ser)
अणु
	पूर्णांक ret = 0;

	अगर (port->type != PORT_MESON)
		ret = -EINVAL;
	अगर (port->irq != ser->irq)
		ret = -EINVAL;
	अगर (ser->baud_base < 9600)
		ret = -EINVAL;
	वापस ret;
पूर्ण

अटल व्योम meson_uart_release_port(काष्ठा uart_port *port)
अणु
	devm_iounmap(port->dev, port->membase);
	port->membase = शून्य;
	devm_release_mem_region(port->dev, port->mapbase, port->mapsize);
पूर्ण

अटल पूर्णांक meson_uart_request_port(काष्ठा uart_port *port)
अणु
	अगर (!devm_request_mem_region(port->dev, port->mapbase, port->mapsize,
				     dev_name(port->dev))) अणु
		dev_err(port->dev, "Memory region busy\n");
		वापस -EBUSY;
	पूर्ण

	port->membase = devm_ioremap(port->dev, port->mapbase,
					     port->mapsize);
	अगर (!port->membase)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम meson_uart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE) अणु
		port->type = PORT_MESON;
		meson_uart_request_port(port);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
/*
 * Console polling routines क्रम writing and पढ़ोing from the uart जबतक
 * in an पूर्णांकerrupt or debug context (i.e. kgdb).
 */

अटल पूर्णांक meson_uart_poll_get_अक्षर(काष्ठा uart_port *port)
अणु
	u32 c;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	अगर (पढ़ोl(port->membase + AML_UART_STATUS) & AML_UART_RX_EMPTY)
		c = NO_POLL_CHAR;
	अन्यथा
		c = पढ़ोl(port->membase + AML_UART_RFIFO);

	spin_unlock_irqrestore(&port->lock, flags);

	वापस c;
पूर्ण

अटल व्योम meson_uart_poll_put_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर c)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg;
	पूर्णांक ret;

	spin_lock_irqsave(&port->lock, flags);

	/* Wait until FIFO is empty or समयout */
	ret = पढ़ोl_poll_समयout_atomic(port->membase + AML_UART_STATUS, reg,
					reg & AML_UART_TX_EMPTY,
					AML_UART_POLL_USEC,
					AML_UART_TIMEOUT_USEC);
	अगर (ret == -ETIMEDOUT) अणु
		dev_err(port->dev, "Timeout waiting for UART TX EMPTY\n");
		जाओ out;
	पूर्ण

	/* Write the अक्षरacter */
	ग_लिखोl(c, port->membase + AML_UART_WFIFO);

	/* Wait until FIFO is empty or समयout */
	ret = पढ़ोl_poll_समयout_atomic(port->membase + AML_UART_STATUS, reg,
					reg & AML_UART_TX_EMPTY,
					AML_UART_POLL_USEC,
					AML_UART_TIMEOUT_USEC);
	अगर (ret == -ETIMEDOUT)
		dev_err(port->dev, "Timeout waiting for UART TX EMPTY\n");

out:
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

#पूर्ण_अगर /* CONFIG_CONSOLE_POLL */

अटल स्थिर काष्ठा uart_ops meson_uart_ops = अणु
	.set_mctrl      = meson_uart_set_mctrl,
	.get_mctrl      = meson_uart_get_mctrl,
	.tx_empty	= meson_uart_tx_empty,
	.start_tx	= meson_uart_start_tx,
	.stop_tx	= meson_uart_stop_tx,
	.stop_rx	= meson_uart_stop_rx,
	.startup	= meson_uart_startup,
	.shutकरोwn	= meson_uart_shutकरोwn,
	.set_termios	= meson_uart_set_termios,
	.type		= meson_uart_type,
	.config_port	= meson_uart_config_port,
	.request_port	= meson_uart_request_port,
	.release_port	= meson_uart_release_port,
	.verअगरy_port	= meson_uart_verअगरy_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर	= meson_uart_poll_get_अक्षर,
	.poll_put_अक्षर	= meson_uart_poll_put_अक्षर,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_MESON_CONSOLE
अटल व्योम meson_uart_enable_tx_engine(काष्ठा uart_port *port)
अणु
	u32 val;

	val = पढ़ोl(port->membase + AML_UART_CONTROL);
	val |= AML_UART_TX_EN;
	ग_लिखोl(val, port->membase + AML_UART_CONTROL);
पूर्ण

अटल व्योम meson_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	अगर (!port->membase)
		वापस;

	जबतक (पढ़ोl(port->membase + AML_UART_STATUS) & AML_UART_TX_FULL)
		cpu_relax();
	ग_लिखोl(ch, port->membase + AML_UART_WFIFO);
पूर्ण

अटल व्योम meson_serial_port_ग_लिखो(काष्ठा uart_port *port, स्थिर अक्षर *s,
				    u_पूर्णांक count)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक locked;
	u32 val, पंचांगp;

	local_irq_save(flags);
	अगर (port->sysrq) अणु
		locked = 0;
	पूर्ण अन्यथा अगर (oops_in_progress) अणु
		locked = spin_trylock(&port->lock);
	पूर्ण अन्यथा अणु
		spin_lock(&port->lock);
		locked = 1;
	पूर्ण

	val = पढ़ोl(port->membase + AML_UART_CONTROL);
	पंचांगp = val & ~(AML_UART_TX_INT_EN | AML_UART_RX_INT_EN);
	ग_लिखोl(पंचांगp, port->membase + AML_UART_CONTROL);

	uart_console_ग_लिखो(port, s, count, meson_console_अक्षर_दो);
	ग_लिखोl(val, port->membase + AML_UART_CONTROL);

	अगर (locked)
		spin_unlock(&port->lock);
	local_irq_restore(flags);
पूर्ण

अटल व्योम meson_serial_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				       u_पूर्णांक count)
अणु
	काष्ठा uart_port *port;

	port = meson_ports[co->index];
	अगर (!port)
		वापस;

	meson_serial_port_ग_लिखो(port, s, count);
पूर्ण

अटल पूर्णांक meson_serial_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (co->index < 0 || co->index >= AML_UART_PORT_NUM)
		वापस -EINVAL;

	port = meson_ports[co->index];
	अगर (!port || !port->membase)
		वापस -ENODEV;

	meson_uart_enable_tx_engine(port);

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा console meson_serial_console = अणु
	.name		= AML_UART_DEV_NAME,
	.ग_लिखो		= meson_serial_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= meson_serial_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &meson_uart_driver,
पूर्ण;

अटल पूर्णांक __init meson_serial_console_init(व्योम)
अणु
	रेजिस्टर_console(&meson_serial_console);
	वापस 0;
पूर्ण

अटल व्योम meson_serial_early_console_ग_लिखो(काष्ठा console *co,
					     स्थिर अक्षर *s,
					     u_पूर्णांक count)
अणु
	काष्ठा earlycon_device *dev = co->data;

	meson_serial_port_ग_लिखो(&dev->port, s, count);
पूर्ण

अटल पूर्णांक __init
meson_serial_early_console_setup(काष्ठा earlycon_device *device, स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	meson_uart_enable_tx_engine(&device->port);
	device->con->ग_लिखो = meson_serial_early_console_ग_लिखो;
	वापस 0;
पूर्ण
/* Legacy bindings, should be हटाओd when no more used */
OF_EARLYCON_DECLARE(meson, "amlogic,meson-uart",
		    meson_serial_early_console_setup);
/* Stable bindings */
OF_EARLYCON_DECLARE(meson, "amlogic,meson-ao-uart",
		    meson_serial_early_console_setup);

#घोषणा MESON_SERIAL_CONSOLE	(&meson_serial_console)
#अन्यथा
अटल पूर्णांक __init meson_serial_console_init(व्योम) अणु
	वापस 0;
पूर्ण
#घोषणा MESON_SERIAL_CONSOLE	शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver meson_uart_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "meson_uart",
	.dev_name	= AML_UART_DEV_NAME,
	.nr		= AML_UART_PORT_NUM,
	.cons		= MESON_SERIAL_CONSOLE,
पूर्ण;

अटल अंतरभूत काष्ठा clk *meson_uart_probe_घड़ी(काष्ठा device *dev,
						 स्थिर अक्षर *id)
अणु
	काष्ठा clk *clk = शून्य;
	पूर्णांक ret;

	clk = devm_clk_get(dev, id);
	अगर (IS_ERR(clk))
		वापस clk;

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(dev, "couldn't enable clk\n");
		वापस ERR_PTR(ret);
	पूर्ण

	devm_add_action_or_reset(dev,
			(व्योम(*)(व्योम *))clk_disable_unprepare,
			clk);

	वापस clk;
पूर्ण

/*
 * This function माला_लो घड़ीs in the legacy non-stable DT bindings.
 * This code will be हटाओ once all the platक्रमms चयन to the
 * new DT bindings.
 */
अटल पूर्णांक meson_uart_probe_घड़ीs_legacy(काष्ठा platक्रमm_device *pdev,
					  काष्ठा uart_port *port)
अणु
	काष्ठा clk *clk = शून्य;

	clk = meson_uart_probe_घड़ी(&pdev->dev, शून्य);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	port->uartclk = clk_get_rate(clk);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_uart_probe_घड़ीs(काष्ठा platक्रमm_device *pdev,
				   काष्ठा uart_port *port)
अणु
	काष्ठा clk *clk_xtal = शून्य;
	काष्ठा clk *clk_pclk = शून्य;
	काष्ठा clk *clk_baud = शून्य;

	clk_pclk = meson_uart_probe_घड़ी(&pdev->dev, "pclk");
	अगर (IS_ERR(clk_pclk))
		वापस PTR_ERR(clk_pclk);

	clk_xtal = meson_uart_probe_घड़ी(&pdev->dev, "xtal");
	अगर (IS_ERR(clk_xtal))
		वापस PTR_ERR(clk_xtal);

	clk_baud = meson_uart_probe_घड़ी(&pdev->dev, "baud");
	अगर (IS_ERR(clk_baud))
		वापस PTR_ERR(clk_baud);

	port->uartclk = clk_get_rate(clk_baud);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_uart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res_mem, *res_irq;
	काष्ठा uart_port *port;
	पूर्णांक ret = 0;
	पूर्णांक id = -1;

	अगर (pdev->dev.of_node)
		pdev->id = of_alias_get_id(pdev->dev.of_node, "serial");

	अगर (pdev->id < 0) अणु
		क्रम (id = AML_UART_PORT_OFFSET; id < AML_UART_PORT_NUM; id++) अणु
			अगर (!meson_ports[id]) अणु
				pdev->id = id;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (pdev->id < 0 || pdev->id >= AML_UART_PORT_NUM)
		वापस -EINVAL;

	res_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res_mem)
		वापस -ENODEV;

	res_irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res_irq)
		वापस -ENODEV;

	अगर (meson_ports[pdev->id]) अणु
		dev_err(&pdev->dev, "port %d already allocated\n", pdev->id);
		वापस -EBUSY;
	पूर्ण

	port = devm_kzalloc(&pdev->dev, माप(काष्ठा uart_port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	/* Use legacy way until all platक्रमms चयन to new bindings */
	अगर (of_device_is_compatible(pdev->dev.of_node, "amlogic,meson-uart"))
		ret = meson_uart_probe_घड़ीs_legacy(pdev, port);
	अन्यथा
		ret = meson_uart_probe_घड़ीs(pdev, port);

	अगर (ret)
		वापस ret;

	port->iotype = UPIO_MEM;
	port->mapbase = res_mem->start;
	port->mapsize = resource_size(res_mem);
	port->irq = res_irq->start;
	port->flags = UPF_BOOT_AUTOCONF | UPF_LOW_LATENCY;
	port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_MESON_CONSOLE);
	port->dev = &pdev->dev;
	port->line = pdev->id;
	port->type = PORT_MESON;
	port->x_अक्षर = 0;
	port->ops = &meson_uart_ops;
	port->fअगरosize = 64;

	meson_ports[pdev->id] = port;
	platक्रमm_set_drvdata(pdev, port);

	/* reset port beक्रमe रेजिस्टरing (and possibly रेजिस्टरing console) */
	अगर (meson_uart_request_port(port) >= 0) अणु
		meson_uart_reset(port);
		meson_uart_release_port(port);
	पूर्ण

	ret = uart_add_one_port(&meson_uart_driver, port);
	अगर (ret)
		meson_ports[pdev->id] = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक meson_uart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port;

	port = platक्रमm_get_drvdata(pdev);
	uart_हटाओ_one_port(&meson_uart_driver, port);
	meson_ports[pdev->id] = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id meson_uart_dt_match[] = अणु
	/* Legacy bindings, should be हटाओd when no more used */
	अणु .compatible = "amlogic,meson-uart" पूर्ण,
	/* Stable bindings */
	अणु .compatible = "amlogic,meson6-uart" पूर्ण,
	अणु .compatible = "amlogic,meson8-uart" पूर्ण,
	अणु .compatible = "amlogic,meson8b-uart" पूर्ण,
	अणु .compatible = "amlogic,meson-gx-uart" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_uart_dt_match);

अटल  काष्ठा platक्रमm_driver meson_uart_platक्रमm_driver = अणु
	.probe		= meson_uart_probe,
	.हटाओ		= meson_uart_हटाओ,
	.driver		= अणु
		.name		= "meson_uart",
		.of_match_table	= meson_uart_dt_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init meson_uart_init(व्योम)
अणु
	पूर्णांक ret;

	ret = meson_serial_console_init();
	अगर (ret)
		वापस ret;
	
	ret = uart_रेजिस्टर_driver(&meson_uart_driver);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&meson_uart_platक्रमm_driver);
	अगर (ret)
		uart_unरेजिस्टर_driver(&meson_uart_driver);

	वापस ret;
पूर्ण

अटल व्योम __निकास meson_uart_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&meson_uart_platक्रमm_driver);
	uart_unरेजिस्टर_driver(&meson_uart_driver);
पूर्ण

module_init(meson_uart_init);
module_निकास(meson_uart_निकास);

MODULE_AUTHOR("Carlo Caione <carlo@caione.org>");
MODULE_DESCRIPTION("Amlogic Meson serial port driver");
MODULE_LICENSE("GPL v2");
