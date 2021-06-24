<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Atheros AR933X SoC built-in UART driver
 *
 *  Copyright (C) 2011 Gabor Juhos <juhosg@खोलोwrt.org>
 *
 *  Based on drivers/अक्षर/serial.c, by Linus Torvalds, Theoकरोre Ts'o.
 */

#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/clk.h>

#समावेश <यंत्र/भाग64.h>

#समावेश <यंत्र/mach-ath79/ar933x_uart.h>

#समावेश "serial_mctrl_gpio.h"

#घोषणा DRIVER_NAME "ar933x-uart"

#घोषणा AR933X_UART_MAX_SCALE	0xff
#घोषणा AR933X_UART_MAX_STEP	0xffff

#घोषणा AR933X_UART_MIN_BAUD	300
#घोषणा AR933X_UART_MAX_BAUD	3000000

#घोषणा AR933X_DUMMY_STATUS_RD	0x01

अटल काष्ठा uart_driver ar933x_uart_driver;

काष्ठा ar933x_uart_port अणु
	काष्ठा uart_port	port;
	अचिन्हित पूर्णांक		ier;	/* shaकरोw Interrupt Enable Register */
	अचिन्हित पूर्णांक		min_baud;
	अचिन्हित पूर्णांक		max_baud;
	काष्ठा clk		*clk;
	काष्ठा mctrl_gpios	*gpios;
	काष्ठा gpio_desc	*rts_gpiod;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक ar933x_uart_पढ़ो(काष्ठा ar933x_uart_port *up,
					    पूर्णांक offset)
अणु
	वापस पढ़ोl(up->port.membase + offset);
पूर्ण

अटल अंतरभूत व्योम ar933x_uart_ग_लिखो(काष्ठा ar933x_uart_port *up,
				     पूर्णांक offset, अचिन्हित पूर्णांक value)
अणु
	ग_लिखोl(value, up->port.membase + offset);
पूर्ण

अटल अंतरभूत व्योम ar933x_uart_rmw(काष्ठा ar933x_uart_port *up,
				  अचिन्हित पूर्णांक offset,
				  अचिन्हित पूर्णांक mask,
				  अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक t;

	t = ar933x_uart_पढ़ो(up, offset);
	t &= ~mask;
	t |= val;
	ar933x_uart_ग_लिखो(up, offset, t);
पूर्ण

अटल अंतरभूत व्योम ar933x_uart_rmw_set(काष्ठा ar933x_uart_port *up,
				       अचिन्हित पूर्णांक offset,
				       अचिन्हित पूर्णांक val)
अणु
	ar933x_uart_rmw(up, offset, 0, val);
पूर्ण

अटल अंतरभूत व्योम ar933x_uart_rmw_clear(काष्ठा ar933x_uart_port *up,
					 अचिन्हित पूर्णांक offset,
					 अचिन्हित पूर्णांक val)
अणु
	ar933x_uart_rmw(up, offset, val, 0);
पूर्ण

अटल अंतरभूत व्योम ar933x_uart_start_tx_पूर्णांकerrupt(काष्ठा ar933x_uart_port *up)
अणु
	up->ier |= AR933X_UART_INT_TX_EMPTY;
	ar933x_uart_ग_लिखो(up, AR933X_UART_INT_EN_REG, up->ier);
पूर्ण

अटल अंतरभूत व्योम ar933x_uart_stop_tx_पूर्णांकerrupt(काष्ठा ar933x_uart_port *up)
अणु
	up->ier &= ~AR933X_UART_INT_TX_EMPTY;
	ar933x_uart_ग_लिखो(up, AR933X_UART_INT_EN_REG, up->ier);
पूर्ण

अटल अंतरभूत व्योम ar933x_uart_start_rx_पूर्णांकerrupt(काष्ठा ar933x_uart_port *up)
अणु
	up->ier |= AR933X_UART_INT_RX_VALID;
	ar933x_uart_ग_लिखो(up, AR933X_UART_INT_EN_REG, up->ier);
पूर्ण

अटल अंतरभूत व्योम ar933x_uart_stop_rx_पूर्णांकerrupt(काष्ठा ar933x_uart_port *up)
अणु
	up->ier &= ~AR933X_UART_INT_RX_VALID;
	ar933x_uart_ग_लिखो(up, AR933X_UART_INT_EN_REG, up->ier);
पूर्ण

अटल अंतरभूत व्योम ar933x_uart_अ_दो(काष्ठा ar933x_uart_port *up, पूर्णांक ch)
अणु
	अचिन्हित पूर्णांक rdata;

	rdata = ch & AR933X_UART_DATA_TX_RX_MASK;
	rdata |= AR933X_UART_DATA_TX_CSR;
	ar933x_uart_ग_लिखो(up, AR933X_UART_DATA_REG, rdata);
पूर्ण

अटल अचिन्हित पूर्णांक ar933x_uart_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा ar933x_uart_port *up =
		container_of(port, काष्ठा ar933x_uart_port, port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक rdata;

	spin_lock_irqsave(&up->port.lock, flags);
	rdata = ar933x_uart_पढ़ो(up, AR933X_UART_DATA_REG);
	spin_unlock_irqrestore(&up->port.lock, flags);

	वापस (rdata & AR933X_UART_DATA_TX_CSR) ? 0 : TIOCSER_TEMT;
पूर्ण

अटल अचिन्हित पूर्णांक ar933x_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा ar933x_uart_port *up =
		container_of(port, काष्ठा ar933x_uart_port, port);
	पूर्णांक ret = TIOCM_CTS | TIOCM_DSR | TIOCM_CAR;

	mctrl_gpio_get(up->gpios, &ret);

	वापस ret;
पूर्ण

अटल व्योम ar933x_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा ar933x_uart_port *up =
		container_of(port, काष्ठा ar933x_uart_port, port);

	mctrl_gpio_set(up->gpios, mctrl);
पूर्ण

अटल व्योम ar933x_uart_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा ar933x_uart_port *up =
		container_of(port, काष्ठा ar933x_uart_port, port);

	ar933x_uart_start_tx_पूर्णांकerrupt(up);
पूर्ण

अटल व्योम ar933x_uart_रुको_tx_complete(काष्ठा ar933x_uart_port *up)
अणु
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक समयout = 60000;

	/* Wait up to 60ms क्रम the अक्षरacter(s) to be sent. */
	करो अणु
		status = ar933x_uart_पढ़ो(up, AR933X_UART_CS_REG);
		अगर (--समयout == 0)
			अवरोध;
		udelay(1);
	पूर्ण जबतक (status & AR933X_UART_CS_TX_BUSY);

	अगर (समयout == 0)
		dev_err(up->port.dev, "waiting for TX timed out\n");
पूर्ण

अटल व्योम ar933x_uart_rx_flush(काष्ठा ar933x_uart_port *up)
अणु
	अचिन्हित पूर्णांक status;

	/* clear RX_VALID पूर्णांकerrupt */
	ar933x_uart_ग_लिखो(up, AR933X_UART_INT_REG, AR933X_UART_INT_RX_VALID);

	/* हटाओ अक्षरacters from the RX FIFO */
	करो अणु
		ar933x_uart_ग_लिखो(up, AR933X_UART_DATA_REG, AR933X_UART_DATA_RX_CSR);
		status = ar933x_uart_पढ़ो(up, AR933X_UART_DATA_REG);
	पूर्ण जबतक (status & AR933X_UART_DATA_RX_CSR);
पूर्ण

अटल व्योम ar933x_uart_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा ar933x_uart_port *up =
		container_of(port, काष्ठा ar933x_uart_port, port);

	ar933x_uart_stop_tx_पूर्णांकerrupt(up);
पूर्ण

अटल व्योम ar933x_uart_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा ar933x_uart_port *up =
		container_of(port, काष्ठा ar933x_uart_port, port);

	ar933x_uart_stop_rx_पूर्णांकerrupt(up);
पूर्ण

अटल व्योम ar933x_uart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा ar933x_uart_port *up =
		container_of(port, काष्ठा ar933x_uart_port, port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&up->port.lock, flags);
	अगर (अवरोध_state == -1)
		ar933x_uart_rmw_set(up, AR933X_UART_CS_REG,
				    AR933X_UART_CS_TX_BREAK);
	अन्यथा
		ar933x_uart_rmw_clear(up, AR933X_UART_CS_REG,
				      AR933X_UART_CS_TX_BREAK);
	spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

/*
 * baudrate = (clk / (scale + 1)) * (step * (1 / 2^17))
 */
अटल अचिन्हित दीर्घ ar933x_uart_get_baud(अचिन्हित पूर्णांक clk,
					  अचिन्हित पूर्णांक scale,
					  अचिन्हित पूर्णांक step)
अणु
	u64 t;
	u32 भाग;

	भाग = (2 << 16) * (scale + 1);
	t = clk;
	t *= step;
	t += (भाग / 2);
	करो_भाग(t, भाग);

	वापस t;
पूर्ण

अटल व्योम ar933x_uart_get_scale_step(अचिन्हित पूर्णांक clk,
				       अचिन्हित पूर्णांक baud,
				       अचिन्हित पूर्णांक *scale,
				       अचिन्हित पूर्णांक *step)
अणु
	अचिन्हित पूर्णांक tscale;
	दीर्घ min_dअगरf;

	*scale = 0;
	*step = 0;

	min_dअगरf = baud;
	क्रम (tscale = 0; tscale < AR933X_UART_MAX_SCALE; tscale++) अणु
		u64 tstep;
		पूर्णांक dअगरf;

		tstep = baud * (tscale + 1);
		tstep *= (2 << 16);
		करो_भाग(tstep, clk);

		अगर (tstep > AR933X_UART_MAX_STEP)
			अवरोध;

		dअगरf = असल(ar933x_uart_get_baud(clk, tscale, tstep) - baud);
		अगर (dअगरf < min_dअगरf) अणु
			min_dअगरf = dअगरf;
			*scale = tscale;
			*step = tstep;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ar933x_uart_set_termios(काष्ठा uart_port *port,
				    काष्ठा ktermios *new,
				    काष्ठा ktermios *old)
अणु
	काष्ठा ar933x_uart_port *up =
		container_of(port, काष्ठा ar933x_uart_port, port);
	अचिन्हित पूर्णांक cs;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, scale, step;

	/* Only CS8 is supported */
	new->c_cflag &= ~CSIZE;
	new->c_cflag |= CS8;

	/* Only one stop bit is supported */
	new->c_cflag &= ~CSTOPB;

	cs = 0;
	अगर (new->c_cflag & PARENB) अणु
		अगर (!(new->c_cflag & PARODD))
			cs |= AR933X_UART_CS_PARITY_EVEN;
		अन्यथा
			cs |= AR933X_UART_CS_PARITY_ODD;
	पूर्ण अन्यथा अणु
		cs |= AR933X_UART_CS_PARITY_NONE;
	पूर्ण

	/* Mark/space parity is not supported */
	new->c_cflag &= ~CMSPAR;

	baud = uart_get_baud_rate(port, new, old, up->min_baud, up->max_baud);
	ar933x_uart_get_scale_step(port->uartclk, baud, &scale, &step);

	/*
	 * Ok, we're now changing the port state. Do it with
	 * पूर्णांकerrupts disabled.
	 */
	spin_lock_irqsave(&up->port.lock, flags);

	/* disable the UART */
	ar933x_uart_rmw_clear(up, AR933X_UART_CS_REG,
		      AR933X_UART_CS_IF_MODE_M << AR933X_UART_CS_IF_MODE_S);

	/* Update the per-port समयout. */
	uart_update_समयout(port, new->c_cflag, baud);

	up->port.ignore_status_mask = 0;

	/* ignore all अक्षरacters अगर CREAD is not set */
	अगर ((new->c_cflag & CREAD) == 0)
		up->port.ignore_status_mask |= AR933X_DUMMY_STATUS_RD;

	ar933x_uart_ग_लिखो(up, AR933X_UART_CLOCK_REG,
			  scale << AR933X_UART_CLOCK_SCALE_S | step);

	/* setup configuration रेजिस्टर */
	ar933x_uart_rmw(up, AR933X_UART_CS_REG, AR933X_UART_CS_PARITY_M, cs);

	/* enable host पूर्णांकerrupt */
	ar933x_uart_rmw_set(up, AR933X_UART_CS_REG,
			    AR933X_UART_CS_HOST_INT_EN);

	/* enable RX and TX पढ़ोy overide */
	ar933x_uart_rmw_set(up, AR933X_UART_CS_REG,
		AR933X_UART_CS_TX_READY_ORIDE | AR933X_UART_CS_RX_READY_ORIDE);

	/* reenable the UART */
	ar933x_uart_rmw(up, AR933X_UART_CS_REG,
			AR933X_UART_CS_IF_MODE_M << AR933X_UART_CS_IF_MODE_S,
			AR933X_UART_CS_IF_MODE_DCE << AR933X_UART_CS_IF_MODE_S);

	spin_unlock_irqrestore(&up->port.lock, flags);

	अगर (tty_termios_baud_rate(new))
		tty_termios_encode_baud_rate(new, baud, baud);
पूर्ण

अटल व्योम ar933x_uart_rx_अक्षरs(काष्ठा ar933x_uart_port *up)
अणु
	काष्ठा tty_port *port = &up->port.state->port;
	पूर्णांक max_count = 256;

	करो अणु
		अचिन्हित पूर्णांक rdata;
		अचिन्हित अक्षर ch;

		rdata = ar933x_uart_पढ़ो(up, AR933X_UART_DATA_REG);
		अगर ((rdata & AR933X_UART_DATA_RX_CSR) == 0)
			अवरोध;

		/* हटाओ the अक्षरacter from the FIFO */
		ar933x_uart_ग_लिखो(up, AR933X_UART_DATA_REG,
				  AR933X_UART_DATA_RX_CSR);

		up->port.icount.rx++;
		ch = rdata & AR933X_UART_DATA_TX_RX_MASK;

		अगर (uart_handle_sysrq_अक्षर(&up->port, ch))
			जारी;

		अगर ((up->port.ignore_status_mask & AR933X_DUMMY_STATUS_RD) == 0)
			tty_insert_flip_अक्षर(port, ch, TTY_NORMAL);
	पूर्ण जबतक (max_count-- > 0);

	tty_flip_buffer_push(port);
पूर्ण

अटल व्योम ar933x_uart_tx_अक्षरs(काष्ठा ar933x_uart_port *up)
अणु
	काष्ठा circ_buf *xmit = &up->port.state->xmit;
	काष्ठा serial_rs485 *rs485conf = &up->port.rs485;
	पूर्णांक count;
	bool half_duplex_send = false;

	अगर (uart_tx_stopped(&up->port))
		वापस;

	अगर ((rs485conf->flags & SER_RS485_ENABLED) &&
	    (up->port.x_अक्षर || !uart_circ_empty(xmit))) अणु
		ar933x_uart_stop_rx_पूर्णांकerrupt(up);
		gpiod_set_value(up->rts_gpiod, !!(rs485conf->flags & SER_RS485_RTS_ON_SEND));
		half_duplex_send = true;
	पूर्ण

	count = up->port.fअगरosize;
	करो अणु
		अचिन्हित पूर्णांक rdata;

		rdata = ar933x_uart_पढ़ो(up, AR933X_UART_DATA_REG);
		अगर ((rdata & AR933X_UART_DATA_TX_CSR) == 0)
			अवरोध;

		अगर (up->port.x_अक्षर) अणु
			ar933x_uart_अ_दो(up, up->port.x_अक्षर);
			up->port.icount.tx++;
			up->port.x_अक्षर = 0;
			जारी;
		पूर्ण

		अगर (uart_circ_empty(xmit))
			अवरोध;

		ar933x_uart_अ_दो(up, xmit->buf[xmit->tail]);

		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		up->port.icount.tx++;
	पूर्ण जबतक (--count > 0);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&up->port);

	अगर (!uart_circ_empty(xmit)) अणु
		ar933x_uart_start_tx_पूर्णांकerrupt(up);
	पूर्ण अन्यथा अगर (half_duplex_send) अणु
		ar933x_uart_रुको_tx_complete(up);
		ar933x_uart_rx_flush(up);
		ar933x_uart_start_rx_पूर्णांकerrupt(up);
		gpiod_set_value(up->rts_gpiod, !!(rs485conf->flags & SER_RS485_RTS_AFTER_SEND));
	पूर्ण
पूर्ण

अटल irqवापस_t ar933x_uart_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ar933x_uart_port *up = dev_id;
	अचिन्हित पूर्णांक status;

	status = ar933x_uart_पढ़ो(up, AR933X_UART_CS_REG);
	अगर ((status & AR933X_UART_CS_HOST_INT) == 0)
		वापस IRQ_NONE;

	spin_lock(&up->port.lock);

	status = ar933x_uart_पढ़ो(up, AR933X_UART_INT_REG);
	status &= ar933x_uart_पढ़ो(up, AR933X_UART_INT_EN_REG);

	अगर (status & AR933X_UART_INT_RX_VALID) अणु
		ar933x_uart_ग_लिखो(up, AR933X_UART_INT_REG,
				  AR933X_UART_INT_RX_VALID);
		ar933x_uart_rx_अक्षरs(up);
	पूर्ण

	अगर (status & AR933X_UART_INT_TX_EMPTY) अणु
		ar933x_uart_ग_लिखो(up, AR933X_UART_INT_REG,
				  AR933X_UART_INT_TX_EMPTY);
		ar933x_uart_stop_tx_पूर्णांकerrupt(up);
		ar933x_uart_tx_अक्षरs(up);
	पूर्ण

	spin_unlock(&up->port.lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ar933x_uart_startup(काष्ठा uart_port *port)
अणु
	काष्ठा ar933x_uart_port *up =
		container_of(port, काष्ठा ar933x_uart_port, port);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = request_irq(up->port.irq, ar933x_uart_पूर्णांकerrupt,
			  up->port.irqflags, dev_name(up->port.dev), up);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&up->port.lock, flags);

	/* Enable HOST पूर्णांकerrupts */
	ar933x_uart_rmw_set(up, AR933X_UART_CS_REG,
			    AR933X_UART_CS_HOST_INT_EN);

	/* enable RX and TX पढ़ोy overide */
	ar933x_uart_rmw_set(up, AR933X_UART_CS_REG,
		AR933X_UART_CS_TX_READY_ORIDE | AR933X_UART_CS_RX_READY_ORIDE);

	/* Enable RX पूर्णांकerrupts */
	ar933x_uart_start_rx_पूर्णांकerrupt(up);

	spin_unlock_irqrestore(&up->port.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम ar933x_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा ar933x_uart_port *up =
		container_of(port, काष्ठा ar933x_uart_port, port);

	/* Disable all पूर्णांकerrupts */
	up->ier = 0;
	ar933x_uart_ग_लिखो(up, AR933X_UART_INT_EN_REG, up->ier);

	/* Disable अवरोध condition */
	ar933x_uart_rmw_clear(up, AR933X_UART_CS_REG,
			      AR933X_UART_CS_TX_BREAK);

	मुक्त_irq(up->port.irq, up);
पूर्ण

अटल स्थिर अक्षर *ar933x_uart_type(काष्ठा uart_port *port)
अणु
	वापस (port->type == PORT_AR933X) ? "AR933X UART" : शून्य;
पूर्ण

अटल व्योम ar933x_uart_release_port(काष्ठा uart_port *port)
अणु
	/* Nothing to release ... */
पूर्ण

अटल पूर्णांक ar933x_uart_request_port(काष्ठा uart_port *port)
अणु
	/* UARTs always present */
	वापस 0;
पूर्ण

अटल व्योम ar933x_uart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE)
		port->type = PORT_AR933X;
पूर्ण

अटल पूर्णांक ar933x_uart_verअगरy_port(काष्ठा uart_port *port,
				   काष्ठा serial_काष्ठा *ser)
अणु
	काष्ठा ar933x_uart_port *up =
		container_of(port, काष्ठा ar933x_uart_port, port);

	अगर (ser->type != PORT_UNKNOWN &&
	    ser->type != PORT_AR933X)
		वापस -EINVAL;

	अगर (ser->irq < 0 || ser->irq >= NR_IRQS)
		वापस -EINVAL;

	अगर (ser->baud_base < up->min_baud ||
	    ser->baud_base > up->max_baud)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uart_ops ar933x_uart_ops = अणु
	.tx_empty	= ar933x_uart_tx_empty,
	.set_mctrl	= ar933x_uart_set_mctrl,
	.get_mctrl	= ar933x_uart_get_mctrl,
	.stop_tx	= ar933x_uart_stop_tx,
	.start_tx	= ar933x_uart_start_tx,
	.stop_rx	= ar933x_uart_stop_rx,
	.अवरोध_ctl	= ar933x_uart_अवरोध_ctl,
	.startup	= ar933x_uart_startup,
	.shutकरोwn	= ar933x_uart_shutकरोwn,
	.set_termios	= ar933x_uart_set_termios,
	.type		= ar933x_uart_type,
	.release_port	= ar933x_uart_release_port,
	.request_port	= ar933x_uart_request_port,
	.config_port	= ar933x_uart_config_port,
	.verअगरy_port	= ar933x_uart_verअगरy_port,
पूर्ण;

अटल पूर्णांक ar933x_config_rs485(काष्ठा uart_port *port,
				काष्ठा serial_rs485 *rs485conf)
अणु
	काष्ठा ar933x_uart_port *up =
		container_of(port, काष्ठा ar933x_uart_port, port);

	अगर ((rs485conf->flags & SER_RS485_ENABLED) &&
	    !up->rts_gpiod) अणु
		dev_err(port->dev, "RS485 needs rts-gpio\n");
		वापस 1;
	पूर्ण
	port->rs485 = *rs485conf;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SERIAL_AR933X_CONSOLE
अटल काष्ठा ar933x_uart_port *
ar933x_console_ports[CONFIG_SERIAL_AR933X_NR_UARTS];

अटल व्योम ar933x_uart_रुको_xmitr(काष्ठा ar933x_uart_port *up)
अणु
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक समयout = 60000;

	/* Wait up to 60ms क्रम the अक्षरacter(s) to be sent. */
	करो अणु
		status = ar933x_uart_पढ़ो(up, AR933X_UART_DATA_REG);
		अगर (--समयout == 0)
			अवरोध;
		udelay(1);
	पूर्ण जबतक ((status & AR933X_UART_DATA_TX_CSR) == 0);
पूर्ण

अटल व्योम ar933x_uart_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा ar933x_uart_port *up =
		container_of(port, काष्ठा ar933x_uart_port, port);

	ar933x_uart_रुको_xmitr(up);
	ar933x_uart_अ_दो(up, ch);
पूर्ण

अटल व्योम ar933x_uart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				      अचिन्हित पूर्णांक count)
अणु
	काष्ठा ar933x_uart_port *up = ar933x_console_ports[co->index];
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक पूर्णांक_en;
	पूर्णांक locked = 1;

	local_irq_save(flags);

	अगर (up->port.sysrq)
		locked = 0;
	अन्यथा अगर (oops_in_progress)
		locked = spin_trylock(&up->port.lock);
	अन्यथा
		spin_lock(&up->port.lock);

	/*
	 * First save the IER then disable the पूर्णांकerrupts
	 */
	पूर्णांक_en = ar933x_uart_पढ़ो(up, AR933X_UART_INT_EN_REG);
	ar933x_uart_ग_लिखो(up, AR933X_UART_INT_EN_REG, 0);

	uart_console_ग_लिखो(&up->port, s, count, ar933x_uart_console_अक्षर_दो);

	/*
	 * Finally, रुको क्रम transmitter to become empty
	 * and restore the IER
	 */
	ar933x_uart_रुको_xmitr(up);
	ar933x_uart_ग_लिखो(up, AR933X_UART_INT_EN_REG, पूर्णांक_en);

	ar933x_uart_ग_लिखो(up, AR933X_UART_INT_REG, AR933X_UART_INT_ALLINTS);

	अगर (locked)
		spin_unlock(&up->port.lock);

	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक ar933x_uart_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा ar933x_uart_port *up;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (co->index < 0 || co->index >= CONFIG_SERIAL_AR933X_NR_UARTS)
		वापस -EINVAL;

	up = ar933x_console_ports[co->index];
	अगर (!up)
		वापस -ENODEV;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(&up->port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा console ar933x_uart_console = अणु
	.name		= "ttyATH",
	.ग_लिखो		= ar933x_uart_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= ar933x_uart_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &ar933x_uart_driver,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SERIAL_AR933X_CONSOLE */

अटल काष्ठा uart_driver ar933x_uart_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= DRIVER_NAME,
	.dev_name	= "ttyATH",
	.nr		= CONFIG_SERIAL_AR933X_NR_UARTS,
	.cons		= शून्य, /* filled in runसमय */
पूर्ण;

अटल पूर्णांक ar933x_uart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ar933x_uart_port *up;
	काष्ठा uart_port *port;
	काष्ठा resource *mem_res;
	काष्ठा resource *irq_res;
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक baud;
	पूर्णांक id;
	पूर्णांक ret;

	np = pdev->dev.of_node;
	अगर (IS_ENABLED(CONFIG_OF) && np) अणु
		id = of_alias_get_id(np, "serial");
		अगर (id < 0) अणु
			dev_err(&pdev->dev, "unable to get alias id, err=%d\n",
				id);
			वापस id;
		पूर्ण
	पूर्ण अन्यथा अणु
		id = pdev->id;
		अगर (id == -1)
			id = 0;
	पूर्ण

	अगर (id >= CONFIG_SERIAL_AR933X_NR_UARTS)
		वापस -EINVAL;

	irq_res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!irq_res) अणु
		dev_err(&pdev->dev, "no IRQ resource\n");
		वापस -EINVAL;
	पूर्ण

	up = devm_kzalloc(&pdev->dev, माप(काष्ठा ar933x_uart_port),
			  GFP_KERNEL);
	अगर (!up)
		वापस -ENOMEM;

	up->clk = devm_clk_get(&pdev->dev, "uart");
	अगर (IS_ERR(up->clk)) अणु
		dev_err(&pdev->dev, "unable to get UART clock\n");
		वापस PTR_ERR(up->clk);
	पूर्ण

	port = &up->port;

	mem_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	port->membase = devm_ioremap_resource(&pdev->dev, mem_res);
	अगर (IS_ERR(port->membase))
		वापस PTR_ERR(port->membase);

	ret = clk_prepare_enable(up->clk);
	अगर (ret)
		वापस ret;

	port->uartclk = clk_get_rate(up->clk);
	अगर (!port->uartclk) अणु
		ret = -EINVAL;
		जाओ err_disable_clk;
	पूर्ण

	port->mapbase = mem_res->start;
	port->line = id;
	port->irq = irq_res->start;
	port->dev = &pdev->dev;
	port->type = PORT_AR933X;
	port->iotype = UPIO_MEM32;

	port->regshअगरt = 2;
	port->fअगरosize = AR933X_UART_FIFO_SIZE;
	port->ops = &ar933x_uart_ops;
	port->rs485_config = ar933x_config_rs485;

	baud = ar933x_uart_get_baud(port->uartclk, AR933X_UART_MAX_SCALE, 1);
	up->min_baud = max_t(अचिन्हित पूर्णांक, baud, AR933X_UART_MIN_BAUD);

	baud = ar933x_uart_get_baud(port->uartclk, 0, AR933X_UART_MAX_STEP);
	up->max_baud = min_t(अचिन्हित पूर्णांक, baud, AR933X_UART_MAX_BAUD);

	ret = uart_get_rs485_mode(port);
	अगर (ret)
		जाओ err_disable_clk;

	up->gpios = mctrl_gpio_init(port, 0);
	अगर (IS_ERR(up->gpios) && PTR_ERR(up->gpios) != -ENOSYS) अणु
		ret = PTR_ERR(up->gpios);
		जाओ err_disable_clk;
	पूर्ण

	up->rts_gpiod = mctrl_gpio_to_gpiod(up->gpios, UART_GPIO_RTS);

	अगर ((port->rs485.flags & SER_RS485_ENABLED) &&
	    !up->rts_gpiod) अणु
		dev_err(&pdev->dev, "lacking rts-gpio, disabling RS485\n");
		port->rs485.flags &= ~SER_RS485_ENABLED;
	पूर्ण

#अगर_घोषित CONFIG_SERIAL_AR933X_CONSOLE
	ar933x_console_ports[up->port.line] = up;
#पूर्ण_अगर

	ret = uart_add_one_port(&ar933x_uart_driver, &up->port);
	अगर (ret)
		जाओ err_disable_clk;

	platक्रमm_set_drvdata(pdev, up);
	वापस 0;

err_disable_clk:
	clk_disable_unprepare(up->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक ar933x_uart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ar933x_uart_port *up;

	up = platक्रमm_get_drvdata(pdev);

	अगर (up) अणु
		uart_हटाओ_one_port(&ar933x_uart_driver, &up->port);
		clk_disable_unprepare(up->clk);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ar933x_uart_of_ids[] = अणु
	अणु .compatible = "qca,ar9330-uart" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ar933x_uart_of_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver ar933x_uart_platक्रमm_driver = अणु
	.probe		= ar933x_uart_probe,
	.हटाओ		= ar933x_uart_हटाओ,
	.driver		= अणु
		.name		= DRIVER_NAME,
		.of_match_table = of_match_ptr(ar933x_uart_of_ids),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ar933x_uart_init(व्योम)
अणु
	पूर्णांक ret;

#अगर_घोषित CONFIG_SERIAL_AR933X_CONSOLE
	ar933x_uart_driver.cons = &ar933x_uart_console;
#पूर्ण_अगर

	ret = uart_रेजिस्टर_driver(&ar933x_uart_driver);
	अगर (ret)
		जाओ err_out;

	ret = platक्रमm_driver_रेजिस्टर(&ar933x_uart_platक्रमm_driver);
	अगर (ret)
		जाओ err_unरेजिस्टर_uart_driver;

	वापस 0;

err_unरेजिस्टर_uart_driver:
	uart_unरेजिस्टर_driver(&ar933x_uart_driver);
err_out:
	वापस ret;
पूर्ण

अटल व्योम __निकास ar933x_uart_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ar933x_uart_platक्रमm_driver);
	uart_unरेजिस्टर_driver(&ar933x_uart_driver);
पूर्ण

module_init(ar933x_uart_init);
module_निकास(ar933x_uart_निकास);

MODULE_DESCRIPTION("Atheros AR933X UART driver");
MODULE_AUTHOR("Gabor Juhos <juhosg@openwrt.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRIVER_NAME);
