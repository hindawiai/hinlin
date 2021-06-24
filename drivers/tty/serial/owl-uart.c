<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Actions Semi Owl family serial console
 *
 * Copyright 2013 Actions Semi Inc.
 * Author: Actions Semi, Inc.
 *
 * Copyright (c) 2016-2017 Andreas Fथअrber
 */

#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

#घोषणा OWL_UART_PORT_NUM 7
#घोषणा OWL_UART_DEV_NAME "ttyOWL"

#घोषणा OWL_UART_CTL	0x000
#घोषणा OWL_UART_RXDAT	0x004
#घोषणा OWL_UART_TXDAT	0x008
#घोषणा OWL_UART_STAT	0x00c

#घोषणा OWL_UART_CTL_DWLS_MASK		GENMASK(1, 0)
#घोषणा OWL_UART_CTL_DWLS_5BITS		(0x0 << 0)
#घोषणा OWL_UART_CTL_DWLS_6BITS		(0x1 << 0)
#घोषणा OWL_UART_CTL_DWLS_7BITS		(0x2 << 0)
#घोषणा OWL_UART_CTL_DWLS_8BITS		(0x3 << 0)
#घोषणा OWL_UART_CTL_STPS_2BITS		BIT(2)
#घोषणा OWL_UART_CTL_PRS_MASK		GENMASK(6, 4)
#घोषणा OWL_UART_CTL_PRS_NONE		(0x0 << 4)
#घोषणा OWL_UART_CTL_PRS_ODD		(0x4 << 4)
#घोषणा OWL_UART_CTL_PRS_MARK		(0x5 << 4)
#घोषणा OWL_UART_CTL_PRS_EVEN		(0x6 << 4)
#घोषणा OWL_UART_CTL_PRS_SPACE		(0x7 << 4)
#घोषणा OWL_UART_CTL_AFE		BIT(12)
#घोषणा OWL_UART_CTL_TRFS_TX		BIT(14)
#घोषणा OWL_UART_CTL_EN			BIT(15)
#घोषणा OWL_UART_CTL_RXDE		BIT(16)
#घोषणा OWL_UART_CTL_TXDE		BIT(17)
#घोषणा OWL_UART_CTL_RXIE		BIT(18)
#घोषणा OWL_UART_CTL_TXIE		BIT(19)
#घोषणा OWL_UART_CTL_LBEN		BIT(20)

#घोषणा OWL_UART_STAT_RIP		BIT(0)
#घोषणा OWL_UART_STAT_TIP		BIT(1)
#घोषणा OWL_UART_STAT_RXER		BIT(2)
#घोषणा OWL_UART_STAT_TFER		BIT(3)
#घोषणा OWL_UART_STAT_RXST		BIT(4)
#घोषणा OWL_UART_STAT_RFEM		BIT(5)
#घोषणा OWL_UART_STAT_TFFU		BIT(6)
#घोषणा OWL_UART_STAT_CTSS		BIT(7)
#घोषणा OWL_UART_STAT_RTSS		BIT(8)
#घोषणा OWL_UART_STAT_TFES		BIT(10)
#घोषणा OWL_UART_STAT_TRFL_MASK		GENMASK(16, 11)
#घोषणा OWL_UART_STAT_UTBB		BIT(17)

#घोषणा OWL_UART_POLL_USEC		5
#घोषणा OWL_UART_TIMEOUT_USEC		10000

अटल काष्ठा uart_driver owl_uart_driver;

काष्ठा owl_uart_info अणु
	अचिन्हित पूर्णांक tx_fअगरosize;
पूर्ण;

काष्ठा owl_uart_port अणु
	काष्ठा uart_port port;
	काष्ठा clk *clk;
पूर्ण;

#घोषणा to_owl_uart_port(prt) container_of(prt, काष्ठा owl_uart_port, prt)

अटल काष्ठा owl_uart_port *owl_uart_ports[OWL_UART_PORT_NUM];

अटल अंतरभूत व्योम owl_uart_ग_लिखो(काष्ठा uart_port *port, u32 val, अचिन्हित पूर्णांक off)
अणु
	ग_लिखोl(val, port->membase + off);
पूर्ण

अटल अंतरभूत u32 owl_uart_पढ़ो(काष्ठा uart_port *port, अचिन्हित पूर्णांक off)
अणु
	वापस पढ़ोl(port->membase + off);
पूर्ण

अटल व्योम owl_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	u32 ctl;

	ctl = owl_uart_पढ़ो(port, OWL_UART_CTL);

	अगर (mctrl & TIOCM_LOOP)
		ctl |= OWL_UART_CTL_LBEN;
	अन्यथा
		ctl &= ~OWL_UART_CTL_LBEN;

	owl_uart_ग_लिखो(port, ctl, OWL_UART_CTL);
पूर्ण

अटल अचिन्हित पूर्णांक owl_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक mctrl = TIOCM_CAR | TIOCM_DSR;
	u32 stat, ctl;

	ctl = owl_uart_पढ़ो(port, OWL_UART_CTL);
	stat = owl_uart_पढ़ो(port, OWL_UART_STAT);
	अगर (stat & OWL_UART_STAT_RTSS)
		mctrl |= TIOCM_RTS;
	अगर ((stat & OWL_UART_STAT_CTSS) || !(ctl & OWL_UART_CTL_AFE))
		mctrl |= TIOCM_CTS;
	वापस mctrl;
पूर्ण

अटल अचिन्हित पूर्णांक owl_uart_tx_empty(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;
	अचिन्हित पूर्णांक ret;

	spin_lock_irqsave(&port->lock, flags);

	val = owl_uart_पढ़ो(port, OWL_UART_STAT);
	ret = (val & OWL_UART_STAT_TFES) ? TIOCSER_TEMT : 0;

	spin_unlock_irqrestore(&port->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम owl_uart_stop_rx(काष्ठा uart_port *port)
अणु
	u32 val;

	val = owl_uart_पढ़ो(port, OWL_UART_CTL);
	val &= ~(OWL_UART_CTL_RXIE | OWL_UART_CTL_RXDE);
	owl_uart_ग_लिखो(port, val, OWL_UART_CTL);

	val = owl_uart_पढ़ो(port, OWL_UART_STAT);
	val |= OWL_UART_STAT_RIP;
	owl_uart_ग_लिखो(port, val, OWL_UART_STAT);
पूर्ण

अटल व्योम owl_uart_stop_tx(काष्ठा uart_port *port)
अणु
	u32 val;

	val = owl_uart_पढ़ो(port, OWL_UART_CTL);
	val &= ~(OWL_UART_CTL_TXIE | OWL_UART_CTL_TXDE);
	owl_uart_ग_लिखो(port, val, OWL_UART_CTL);

	val = owl_uart_पढ़ो(port, OWL_UART_STAT);
	val |= OWL_UART_STAT_TIP;
	owl_uart_ग_लिखो(port, val, OWL_UART_STAT);
पूर्ण

अटल व्योम owl_uart_start_tx(काष्ठा uart_port *port)
अणु
	u32 val;

	अगर (uart_tx_stopped(port)) अणु
		owl_uart_stop_tx(port);
		वापस;
	पूर्ण

	val = owl_uart_पढ़ो(port, OWL_UART_STAT);
	val |= OWL_UART_STAT_TIP;
	owl_uart_ग_लिखो(port, val, OWL_UART_STAT);

	val = owl_uart_पढ़ो(port, OWL_UART_CTL);
	val |= OWL_UART_CTL_TXIE;
	owl_uart_ग_लिखो(port, val, OWL_UART_CTL);
पूर्ण

अटल व्योम owl_uart_send_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित पूर्णांक ch;

	अगर (uart_tx_stopped(port))
		वापस;

	अगर (port->x_अक्षर) अणु
		जबतक (!(owl_uart_पढ़ो(port, OWL_UART_STAT) & OWL_UART_STAT_TFFU))
			cpu_relax();
		owl_uart_ग_लिखो(port, port->x_अक्षर, OWL_UART_TXDAT);
		port->icount.tx++;
		port->x_अक्षर = 0;
	पूर्ण

	जबतक (!(owl_uart_पढ़ो(port, OWL_UART_STAT) & OWL_UART_STAT_TFFU)) अणु
		अगर (uart_circ_empty(xmit))
			अवरोध;

		ch = xmit->buf[xmit->tail];
		owl_uart_ग_लिखो(port, ch, OWL_UART_TXDAT);
		xmit->tail = (xmit->tail + 1) & (SERIAL_XMIT_SIZE - 1);
		port->icount.tx++;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (uart_circ_empty(xmit))
		owl_uart_stop_tx(port);
पूर्ण

अटल व्योम owl_uart_receive_अक्षरs(काष्ठा uart_port *port)
अणु
	u32 stat, val;

	val = owl_uart_पढ़ो(port, OWL_UART_CTL);
	val &= ~OWL_UART_CTL_TRFS_TX;
	owl_uart_ग_लिखो(port, val, OWL_UART_CTL);

	stat = owl_uart_पढ़ो(port, OWL_UART_STAT);
	जबतक (!(stat & OWL_UART_STAT_RFEM)) अणु
		अक्षर flag = TTY_NORMAL;

		अगर (stat & OWL_UART_STAT_RXER)
			port->icount.overrun++;

		अगर (stat & OWL_UART_STAT_RXST) अणु
			/* We are not able to distinguish the error type. */
			port->icount.brk++;
			port->icount.frame++;

			stat &= port->पढ़ो_status_mask;
			अगर (stat & OWL_UART_STAT_RXST)
				flag = TTY_PARITY;
		पूर्ण अन्यथा
			port->icount.rx++;

		val = owl_uart_पढ़ो(port, OWL_UART_RXDAT);
		val &= 0xff;

		अगर ((stat & port->ignore_status_mask) == 0)
			tty_insert_flip_अक्षर(&port->state->port, val, flag);

		stat = owl_uart_पढ़ो(port, OWL_UART_STAT);
	पूर्ण

	tty_flip_buffer_push(&port->state->port);
पूर्ण

अटल irqवापस_t owl_uart_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	अचिन्हित दीर्घ flags;
	u32 stat;

	spin_lock_irqsave(&port->lock, flags);

	stat = owl_uart_पढ़ो(port, OWL_UART_STAT);

	अगर (stat & OWL_UART_STAT_RIP)
		owl_uart_receive_अक्षरs(port);

	अगर (stat & OWL_UART_STAT_TIP)
		owl_uart_send_अक्षरs(port);

	stat = owl_uart_पढ़ो(port, OWL_UART_STAT);
	stat |= OWL_UART_STAT_RIP | OWL_UART_STAT_TIP;
	owl_uart_ग_लिखो(port, stat, OWL_UART_STAT);

	spin_unlock_irqrestore(&port->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम owl_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	u32 val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	val = owl_uart_पढ़ो(port, OWL_UART_CTL);
	val &= ~(OWL_UART_CTL_TXIE | OWL_UART_CTL_RXIE
		| OWL_UART_CTL_TXDE | OWL_UART_CTL_RXDE | OWL_UART_CTL_EN);
	owl_uart_ग_लिखो(port, val, OWL_UART_CTL);

	spin_unlock_irqrestore(&port->lock, flags);

	मुक्त_irq(port->irq, port);
पूर्ण

अटल पूर्णांक owl_uart_startup(काष्ठा uart_port *port)
अणु
	u32 val;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = request_irq(port->irq, owl_uart_irq, IRQF_TRIGGER_HIGH,
			"owl-uart", port);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&port->lock, flags);

	val = owl_uart_पढ़ो(port, OWL_UART_STAT);
	val |= OWL_UART_STAT_RIP | OWL_UART_STAT_TIP
		| OWL_UART_STAT_RXER | OWL_UART_STAT_TFER | OWL_UART_STAT_RXST;
	owl_uart_ग_लिखो(port, val, OWL_UART_STAT);

	val = owl_uart_पढ़ो(port, OWL_UART_CTL);
	val |= OWL_UART_CTL_RXIE | OWL_UART_CTL_TXIE;
	val |= OWL_UART_CTL_EN;
	owl_uart_ग_लिखो(port, val, OWL_UART_CTL);

	spin_unlock_irqrestore(&port->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम owl_uart_change_baudrate(काष्ठा owl_uart_port *owl_port,
				     अचिन्हित दीर्घ baud)
अणु
	clk_set_rate(owl_port->clk, baud * 8);
पूर्ण

अटल व्योम owl_uart_set_termios(काष्ठा uart_port *port,
				 काष्ठा ktermios *termios,
				 काष्ठा ktermios *old)
अणु
	काष्ठा owl_uart_port *owl_port = to_owl_uart_port(port);
	अचिन्हित पूर्णांक baud;
	u32 ctl;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	ctl = owl_uart_पढ़ो(port, OWL_UART_CTL);

	ctl &= ~OWL_UART_CTL_DWLS_MASK;
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		ctl |= OWL_UART_CTL_DWLS_5BITS;
		अवरोध;
	हाल CS6:
		ctl |= OWL_UART_CTL_DWLS_6BITS;
		अवरोध;
	हाल CS7:
		ctl |= OWL_UART_CTL_DWLS_7BITS;
		अवरोध;
	हाल CS8:
	शेष:
		ctl |= OWL_UART_CTL_DWLS_8BITS;
		अवरोध;
	पूर्ण

	अगर (termios->c_cflag & CSTOPB)
		ctl |= OWL_UART_CTL_STPS_2BITS;
	अन्यथा
		ctl &= ~OWL_UART_CTL_STPS_2BITS;

	ctl &= ~OWL_UART_CTL_PRS_MASK;
	अगर (termios->c_cflag & PARENB) अणु
		अगर (termios->c_cflag & CMSPAR) अणु
			अगर (termios->c_cflag & PARODD)
				ctl |= OWL_UART_CTL_PRS_MARK;
			अन्यथा
				ctl |= OWL_UART_CTL_PRS_SPACE;
		पूर्ण अन्यथा अगर (termios->c_cflag & PARODD)
			ctl |= OWL_UART_CTL_PRS_ODD;
		अन्यथा
			ctl |= OWL_UART_CTL_PRS_EVEN;
	पूर्ण अन्यथा
		ctl |= OWL_UART_CTL_PRS_NONE;

	अगर (termios->c_cflag & CRTSCTS)
		ctl |= OWL_UART_CTL_AFE;
	अन्यथा
		ctl &= ~OWL_UART_CTL_AFE;

	owl_uart_ग_लिखो(port, ctl, OWL_UART_CTL);

	baud = uart_get_baud_rate(port, termios, old, 9600, 3200000);
	owl_uart_change_baudrate(owl_port, baud);

	/* Don't reग_लिखो B0 */
	अगर (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);

	port->पढ़ो_status_mask |= OWL_UART_STAT_RXER;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= OWL_UART_STAT_RXST;

	uart_update_समयout(port, termios->c_cflag, baud);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम owl_uart_release_port(काष्ठा uart_port *port)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(port->dev);
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस;

	अगर (port->flags & UPF_IOREMAP) अणु
		devm_release_mem_region(port->dev, port->mapbase,
			resource_size(res));
		devm_iounmap(port->dev, port->membase);
		port->membase = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक owl_uart_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(port->dev);
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENXIO;

	अगर (!devm_request_mem_region(port->dev, port->mapbase,
			resource_size(res), dev_name(port->dev)))
		वापस -EBUSY;

	अगर (port->flags & UPF_IOREMAP) अणु
		port->membase = devm_ioremap(port->dev, port->mapbase,
				resource_size(res));
		अगर (!port->membase)
			वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *owl_uart_type(काष्ठा uart_port *port)
अणु
	वापस (port->type == PORT_OWL) ? "owl-uart" : शून्य;
पूर्ण

अटल पूर्णांक owl_uart_verअगरy_port(काष्ठा uart_port *port,
				काष्ठा serial_काष्ठा *ser)
अणु
	अगर (port->type != PORT_OWL)
		वापस -EINVAL;

	अगर (port->irq != ser->irq)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम owl_uart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE) अणु
		port->type = PORT_OWL;
		owl_uart_request_port(port);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL

अटल पूर्णांक owl_uart_poll_get_अक्षर(काष्ठा uart_port *port)
अणु
	अगर (owl_uart_पढ़ो(port, OWL_UART_STAT) & OWL_UART_STAT_RFEM)
		वापस NO_POLL_CHAR;

	वापस owl_uart_पढ़ो(port, OWL_UART_RXDAT);
पूर्ण

अटल व्योम owl_uart_poll_put_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर ch)
अणु
	u32 reg;
	पूर्णांक ret;

	/* Wait जबतक FIFO is full or समयout */
	ret = पढ़ोl_poll_समयout_atomic(port->membase + OWL_UART_STAT, reg,
					!(reg & OWL_UART_STAT_TFFU),
					OWL_UART_POLL_USEC,
					OWL_UART_TIMEOUT_USEC);
	अगर (ret == -ETIMEDOUT) अणु
		dev_err(port->dev, "Timeout waiting while UART TX FULL\n");
		वापस;
	पूर्ण

	owl_uart_ग_लिखो(port, ch, OWL_UART_TXDAT);
पूर्ण

#पूर्ण_अगर /* CONFIG_CONSOLE_POLL */

अटल स्थिर काष्ठा uart_ops owl_uart_ops = अणु
	.set_mctrl = owl_uart_set_mctrl,
	.get_mctrl = owl_uart_get_mctrl,
	.tx_empty = owl_uart_tx_empty,
	.start_tx = owl_uart_start_tx,
	.stop_rx = owl_uart_stop_rx,
	.stop_tx = owl_uart_stop_tx,
	.startup = owl_uart_startup,
	.shutकरोwn = owl_uart_shutकरोwn,
	.set_termios = owl_uart_set_termios,
	.type = owl_uart_type,
	.config_port = owl_uart_config_port,
	.request_port = owl_uart_request_port,
	.release_port = owl_uart_release_port,
	.verअगरy_port = owl_uart_verअगरy_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर = owl_uart_poll_get_अक्षर,
	.poll_put_अक्षर = owl_uart_poll_put_अक्षर,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_OWL_CONSOLE

अटल व्योम owl_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	अगर (!port->membase)
		वापस;

	जबतक (owl_uart_पढ़ो(port, OWL_UART_STAT) & OWL_UART_STAT_TFFU)
		cpu_relax();

	owl_uart_ग_लिखो(port, ch, OWL_UART_TXDAT);
पूर्ण

अटल व्योम owl_uart_port_ग_लिखो(काष्ठा uart_port *port, स्थिर अक्षर *s,
				u_पूर्णांक count)
अणु
	u32 old_ctl, val;
	अचिन्हित दीर्घ flags;
	पूर्णांक locked;

	local_irq_save(flags);

	अगर (port->sysrq)
		locked = 0;
	अन्यथा अगर (oops_in_progress)
		locked = spin_trylock(&port->lock);
	अन्यथा अणु
		spin_lock(&port->lock);
		locked = 1;
	पूर्ण

	old_ctl = owl_uart_पढ़ो(port, OWL_UART_CTL);
	val = old_ctl | OWL_UART_CTL_TRFS_TX;
	/* disable IRQ */
	val &= ~(OWL_UART_CTL_RXIE | OWL_UART_CTL_TXIE);
	owl_uart_ग_लिखो(port, val, OWL_UART_CTL);

	uart_console_ग_लिखो(port, s, count, owl_console_अक्षर_दो);

	/* रुको until all contents have been sent out */
	जबतक (owl_uart_पढ़ो(port, OWL_UART_STAT) & OWL_UART_STAT_TRFL_MASK)
		cpu_relax();

	/* clear IRQ pending */
	val = owl_uart_पढ़ो(port, OWL_UART_STAT);
	val |= OWL_UART_STAT_TIP | OWL_UART_STAT_RIP;
	owl_uart_ग_लिखो(port, val, OWL_UART_STAT);

	owl_uart_ग_लिखो(port, old_ctl, OWL_UART_CTL);

	अगर (locked)
		spin_unlock(&port->lock);

	local_irq_restore(flags);
पूर्ण

अटल व्योम owl_uart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				   u_पूर्णांक count)
अणु
	काष्ठा owl_uart_port *owl_port;

	owl_port = owl_uart_ports[co->index];
	अगर (!owl_port)
		वापस;

	owl_uart_port_ग_लिखो(&owl_port->port, s, count);
पूर्ण

अटल पूर्णांक owl_uart_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा owl_uart_port *owl_port;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (co->index < 0 || co->index >= OWL_UART_PORT_NUM)
		वापस -EINVAL;

	owl_port = owl_uart_ports[co->index];
	अगर (!owl_port || !owl_port->port.membase)
		वापस -ENODEV;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(&owl_port->port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा console owl_uart_console = अणु
	.name = OWL_UART_DEV_NAME,
	.ग_लिखो = owl_uart_console_ग_लिखो,
	.device = uart_console_device,
	.setup = owl_uart_console_setup,
	.flags = CON_PRINTBUFFER,
	.index = -1,
	.data = &owl_uart_driver,
पूर्ण;

अटल पूर्णांक __init owl_uart_console_init(व्योम)
अणु
	रेजिस्टर_console(&owl_uart_console);

	वापस 0;
पूर्ण
console_initcall(owl_uart_console_init);

अटल व्योम owl_uart_early_console_ग_लिखो(काष्ठा console *co,
					 स्थिर अक्षर *s,
					 u_पूर्णांक count)
अणु
	काष्ठा earlycon_device *dev = co->data;

	owl_uart_port_ग_लिखो(&dev->port, s, count);
पूर्ण

अटल पूर्णांक __init
owl_uart_early_console_setup(काष्ठा earlycon_device *device, स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->con->ग_लिखो = owl_uart_early_console_ग_लिखो;

	वापस 0;
पूर्ण
OF_EARLYCON_DECLARE(owl, "actions,owl-uart",
		    owl_uart_early_console_setup);

#घोषणा OWL_UART_CONSOLE (&owl_uart_console)
#अन्यथा
#घोषणा OWL_UART_CONSOLE शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver owl_uart_driver = अणु
	.owner = THIS_MODULE,
	.driver_name = "owl-uart",
	.dev_name = OWL_UART_DEV_NAME,
	.nr = OWL_UART_PORT_NUM,
	.cons = OWL_UART_CONSOLE,
पूर्ण;

अटल स्थिर काष्ठा owl_uart_info owl_s500_info = अणु
	.tx_fअगरosize = 16,
पूर्ण;

अटल स्थिर काष्ठा owl_uart_info owl_s900_info = अणु
	.tx_fअगरosize = 32,
पूर्ण;

अटल स्थिर काष्ठा of_device_id owl_uart_dt_matches[] = अणु
	अणु .compatible = "actions,s500-uart", .data = &owl_s500_info पूर्ण,
	अणु .compatible = "actions,s900-uart", .data = &owl_s900_info पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, owl_uart_dt_matches);

अटल पूर्णांक owl_uart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा owl_uart_info *info = शून्य;
	काष्ठा resource *res_mem;
	काष्ठा owl_uart_port *owl_port;
	पूर्णांक ret, irq;

	अगर (pdev->dev.of_node) अणु
		pdev->id = of_alias_get_id(pdev->dev.of_node, "serial");
		match = of_match_node(owl_uart_dt_matches, pdev->dev.of_node);
		अगर (match)
			info = match->data;
	पूर्ण

	अगर (pdev->id < 0 || pdev->id >= OWL_UART_PORT_NUM) अणु
		dev_err(&pdev->dev, "id %d out of range\n", pdev->id);
		वापस -EINVAL;
	पूर्ण

	res_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res_mem) अणु
		dev_err(&pdev->dev, "could not get mem\n");
		वापस -ENODEV;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	अगर (owl_uart_ports[pdev->id]) अणु
		dev_err(&pdev->dev, "port %d already allocated\n", pdev->id);
		वापस -EBUSY;
	पूर्ण

	owl_port = devm_kzalloc(&pdev->dev, माप(*owl_port), GFP_KERNEL);
	अगर (!owl_port)
		वापस -ENOMEM;

	owl_port->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(owl_port->clk)) अणु
		dev_err(&pdev->dev, "could not get clk\n");
		वापस PTR_ERR(owl_port->clk);
	पूर्ण

	ret = clk_prepare_enable(owl_port->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not enable clk\n");
		वापस ret;
	पूर्ण

	owl_port->port.dev = &pdev->dev;
	owl_port->port.line = pdev->id;
	owl_port->port.type = PORT_OWL;
	owl_port->port.iotype = UPIO_MEM;
	owl_port->port.mapbase = res_mem->start;
	owl_port->port.irq = irq;
	owl_port->port.uartclk = clk_get_rate(owl_port->clk);
	अगर (owl_port->port.uartclk == 0) अणु
		dev_err(&pdev->dev, "clock rate is zero\n");
		वापस -EINVAL;
	पूर्ण
	owl_port->port.flags = UPF_BOOT_AUTOCONF | UPF_IOREMAP | UPF_LOW_LATENCY;
	owl_port->port.x_अक्षर = 0;
	owl_port->port.fअगरosize = (info) ? info->tx_fअगरosize : 16;
	owl_port->port.ops = &owl_uart_ops;

	owl_uart_ports[pdev->id] = owl_port;
	platक्रमm_set_drvdata(pdev, owl_port);

	ret = uart_add_one_port(&owl_uart_driver, &owl_port->port);
	अगर (ret)
		owl_uart_ports[pdev->id] = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक owl_uart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा owl_uart_port *owl_port = platक्रमm_get_drvdata(pdev);

	uart_हटाओ_one_port(&owl_uart_driver, &owl_port->port);
	owl_uart_ports[pdev->id] = शून्य;
	clk_disable_unprepare(owl_port->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver owl_uart_platक्रमm_driver = अणु
	.probe = owl_uart_probe,
	.हटाओ = owl_uart_हटाओ,
	.driver = अणु
		.name = "owl-uart",
		.of_match_table = owl_uart_dt_matches,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init owl_uart_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&owl_uart_driver);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&owl_uart_platक्रमm_driver);
	अगर (ret)
		uart_unरेजिस्टर_driver(&owl_uart_driver);

	वापस ret;
पूर्ण

अटल व्योम __निकास owl_uart_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&owl_uart_platक्रमm_driver);
	uart_unरेजिस्टर_driver(&owl_uart_driver);
पूर्ण

module_init(owl_uart_init);
module_निकास(owl_uart_निकास);

MODULE_LICENSE("GPL");
