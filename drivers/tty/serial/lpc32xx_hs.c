<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * High Speed Serial Ports on NXP LPC32xx SoC
 *
 * Authors: Kevin Wells <kevin.wells@nxp.com>
 *          Roland Stigge <stigge@antcom.de>
 *
 * Copyright (C) 2010 NXP Semiconductors
 * Copyright (C) 2012 Roland Stigge
 */

#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/nmi.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/sizes.h>
#समावेश <linux/soc/nxp/lpc32xx-misc.h>

/*
 * High Speed UART रेजिस्टर offsets
 */
#घोषणा LPC32XX_HSUART_FIFO(x)			((x) + 0x00)
#घोषणा LPC32XX_HSUART_LEVEL(x)			((x) + 0x04)
#घोषणा LPC32XX_HSUART_IIR(x)			((x) + 0x08)
#घोषणा LPC32XX_HSUART_CTRL(x)			((x) + 0x0C)
#घोषणा LPC32XX_HSUART_RATE(x)			((x) + 0x10)

#घोषणा LPC32XX_HSU_BREAK_DATA			(1 << 10)
#घोषणा LPC32XX_HSU_ERROR_DATA			(1 << 9)
#घोषणा LPC32XX_HSU_RX_EMPTY			(1 << 8)

#घोषणा LPC32XX_HSU_TX_LEV(n)			(((n) >> 8) & 0xFF)
#घोषणा LPC32XX_HSU_RX_LEV(n)			((n) & 0xFF)

#घोषणा LPC32XX_HSU_TX_INT_SET			(1 << 6)
#घोषणा LPC32XX_HSU_RX_OE_INT			(1 << 5)
#घोषणा LPC32XX_HSU_BRK_INT			(1 << 4)
#घोषणा LPC32XX_HSU_FE_INT			(1 << 3)
#घोषणा LPC32XX_HSU_RX_TIMEOUT_INT		(1 << 2)
#घोषणा LPC32XX_HSU_RX_TRIG_INT			(1 << 1)
#घोषणा LPC32XX_HSU_TX_INT			(1 << 0)

#घोषणा LPC32XX_HSU_HRTS_INV			(1 << 21)
#घोषणा LPC32XX_HSU_HRTS_TRIG_8B		(0x0 << 19)
#घोषणा LPC32XX_HSU_HRTS_TRIG_16B		(0x1 << 19)
#घोषणा LPC32XX_HSU_HRTS_TRIG_32B		(0x2 << 19)
#घोषणा LPC32XX_HSU_HRTS_TRIG_48B		(0x3 << 19)
#घोषणा LPC32XX_HSU_HRTS_EN			(1 << 18)
#घोषणा LPC32XX_HSU_TMO_DISABLED		(0x0 << 16)
#घोषणा LPC32XX_HSU_TMO_INACT_4B		(0x1 << 16)
#घोषणा LPC32XX_HSU_TMO_INACT_8B		(0x2 << 16)
#घोषणा LPC32XX_HSU_TMO_INACT_16B		(0x3 << 16)
#घोषणा LPC32XX_HSU_HCTS_INV			(1 << 15)
#घोषणा LPC32XX_HSU_HCTS_EN			(1 << 14)
#घोषणा LPC32XX_HSU_OFFSET(n)			((n) << 9)
#घोषणा LPC32XX_HSU_BREAK			(1 << 8)
#घोषणा LPC32XX_HSU_ERR_INT_EN			(1 << 7)
#घोषणा LPC32XX_HSU_RX_INT_EN			(1 << 6)
#घोषणा LPC32XX_HSU_TX_INT_EN			(1 << 5)
#घोषणा LPC32XX_HSU_RX_TL1B			(0x0 << 2)
#घोषणा LPC32XX_HSU_RX_TL4B			(0x1 << 2)
#घोषणा LPC32XX_HSU_RX_TL8B			(0x2 << 2)
#घोषणा LPC32XX_HSU_RX_TL16B			(0x3 << 2)
#घोषणा LPC32XX_HSU_RX_TL32B			(0x4 << 2)
#घोषणा LPC32XX_HSU_RX_TL48B			(0x5 << 2)
#घोषणा LPC32XX_HSU_TX_TLEMPTY			(0x0 << 0)
#घोषणा LPC32XX_HSU_TX_TL0B			(0x0 << 0)
#घोषणा LPC32XX_HSU_TX_TL4B			(0x1 << 0)
#घोषणा LPC32XX_HSU_TX_TL8B			(0x2 << 0)
#घोषणा LPC32XX_HSU_TX_TL16B			(0x3 << 0)

#घोषणा LPC32XX_MAIN_OSC_FREQ			13000000

#घोषणा MODNAME "lpc32xx_hsuart"

काष्ठा lpc32xx_hsuart_port अणु
	काष्ठा uart_port port;
पूर्ण;

#घोषणा FIFO_READ_LIMIT 128
#घोषणा MAX_PORTS 3
#घोषणा LPC32XX_TTY_NAME "ttyTX"
अटल काष्ठा lpc32xx_hsuart_port lpc32xx_hs_ports[MAX_PORTS];

#अगर_घोषित CONFIG_SERIAL_HS_LPC32XX_CONSOLE
अटल व्योम रुको_क्रम_xmit_empty(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक समयout = 10000;

	करो अणु
		अगर (LPC32XX_HSU_TX_LEV(पढ़ोl(LPC32XX_HSUART_LEVEL(
							port->membase))) == 0)
			अवरोध;
		अगर (--समयout == 0)
			अवरोध;
		udelay(1);
	पूर्ण जबतक (1);
पूर्ण

अटल व्योम रुको_क्रम_xmit_पढ़ोy(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक समयout = 10000;

	जबतक (1) अणु
		अगर (LPC32XX_HSU_TX_LEV(पढ़ोl(LPC32XX_HSUART_LEVEL(
							port->membase))) < 32)
			अवरोध;
		अगर (--समयout == 0)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम lpc32xx_hsuart_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	रुको_क्रम_xmit_पढ़ोy(port);
	ग_लिखोl((u32)ch, LPC32XX_HSUART_FIFO(port->membase));
पूर्ण

अटल व्योम lpc32xx_hsuart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
					 अचिन्हित पूर्णांक count)
अणु
	काष्ठा lpc32xx_hsuart_port *up = &lpc32xx_hs_ports[co->index];
	अचिन्हित दीर्घ flags;
	पूर्णांक locked = 1;

	touch_nmi_watchकरोg();
	local_irq_save(flags);
	अगर (up->port.sysrq)
		locked = 0;
	अन्यथा अगर (oops_in_progress)
		locked = spin_trylock(&up->port.lock);
	अन्यथा
		spin_lock(&up->port.lock);

	uart_console_ग_लिखो(&up->port, s, count, lpc32xx_hsuart_console_अक्षर_दो);
	रुको_क्रम_xmit_empty(&up->port);

	अगर (locked)
		spin_unlock(&up->port.lock);
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक __init lpc32xx_hsuart_console_setup(काष्ठा console *co,
					       अक्षर *options)
अणु
	काष्ठा uart_port *port;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (co->index >= MAX_PORTS)
		co->index = 0;

	port = &lpc32xx_hs_ports[co->index].port;
	अगर (!port->membase)
		वापस -ENODEV;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	lpc32xx_loopback_set(port->mapbase, 0); /* get out of loopback mode */

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver lpc32xx_hsuart_reg;
अटल काष्ठा console lpc32xx_hsuart_console = अणु
	.name		= LPC32XX_TTY_NAME,
	.ग_लिखो		= lpc32xx_hsuart_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= lpc32xx_hsuart_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &lpc32xx_hsuart_reg,
पूर्ण;

अटल पूर्णांक __init lpc32xx_hsuart_console_init(व्योम)
अणु
	रेजिस्टर_console(&lpc32xx_hsuart_console);
	वापस 0;
पूर्ण
console_initcall(lpc32xx_hsuart_console_init);

#घोषणा LPC32XX_HSUART_CONSOLE (&lpc32xx_hsuart_console)
#अन्यथा
#घोषणा LPC32XX_HSUART_CONSOLE शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver lpc32xx_hs_reg = अणु
	.owner		= THIS_MODULE,
	.driver_name	= MODNAME,
	.dev_name	= LPC32XX_TTY_NAME,
	.nr		= MAX_PORTS,
	.cons		= LPC32XX_HSUART_CONSOLE,
पूर्ण;
अटल पूर्णांक uarts_रेजिस्टरed;

अटल अचिन्हित पूर्णांक __serial_get_घड़ी_भाग(अचिन्हित दीर्घ uartclk,
					   अचिन्हित दीर्घ rate)
अणु
	u32 भाग, goodrate, hsu_rate, l_hsu_rate, comprate;
	u32 rate_dअगरf;

	/* Find the बंदst भागider to get the desired घड़ी rate */
	भाग = uartclk / rate;
	goodrate = hsu_rate = (भाग / 14) - 1;
	अगर (hsu_rate != 0)
		hsu_rate--;

	/* Tweak भागider */
	l_hsu_rate = hsu_rate + 3;
	rate_dअगरf = 0xFFFFFFFF;

	जबतक (hsu_rate < l_hsu_rate) अणु
		comprate = uartclk / ((hsu_rate + 1) * 14);
		अगर (असल(comprate - rate) < rate_dअगरf) अणु
			goodrate = hsu_rate;
			rate_dअगरf = असल(comprate - rate);
		पूर्ण

		hsu_rate++;
	पूर्ण
	अगर (hsu_rate > 0xFF)
		hsu_rate = 0xFF;

	वापस goodrate;
पूर्ण

अटल व्योम __serial_uart_flush(काष्ठा uart_port *port)
अणु
	पूर्णांक cnt = 0;

	जबतक ((पढ़ोl(LPC32XX_HSUART_LEVEL(port->membase)) > 0) &&
	       (cnt++ < FIFO_READ_LIMIT))
		पढ़ोl(LPC32XX_HSUART_FIFO(port->membase));
पूर्ण

अटल व्योम __serial_lpc32xx_rx(काष्ठा uart_port *port)
अणु
	काष्ठा tty_port *tport = &port->state->port;
	अचिन्हित पूर्णांक पंचांगp, flag;

	/* Read data from FIFO and push पूर्णांकo terminal */
	पंचांगp = पढ़ोl(LPC32XX_HSUART_FIFO(port->membase));
	जबतक (!(पंचांगp & LPC32XX_HSU_RX_EMPTY)) अणु
		flag = TTY_NORMAL;
		port->icount.rx++;

		अगर (पंचांगp & LPC32XX_HSU_ERROR_DATA) अणु
			/* Framing error */
			ग_लिखोl(LPC32XX_HSU_FE_INT,
			       LPC32XX_HSUART_IIR(port->membase));
			port->icount.frame++;
			flag = TTY_FRAME;
			tty_insert_flip_अक्षर(tport, 0, TTY_FRAME);
		पूर्ण

		tty_insert_flip_अक्षर(tport, (पंचांगp & 0xFF), flag);

		पंचांगp = पढ़ोl(LPC32XX_HSUART_FIFO(port->membase));
	पूर्ण

	tty_flip_buffer_push(tport);
पूर्ण

अटल व्योम __serial_lpc32xx_tx(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित पूर्णांक पंचांगp;

	अगर (port->x_अक्षर) अणु
		ग_लिखोl((u32)port->x_अक्षर, LPC32XX_HSUART_FIFO(port->membase));
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port))
		जाओ निकास_tx;

	/* Transfer data */
	जबतक (LPC32XX_HSU_TX_LEV(पढ़ोl(
		LPC32XX_HSUART_LEVEL(port->membase))) < 64) अणु
		ग_लिखोl((u32) xmit->buf[xmit->tail],
		       LPC32XX_HSUART_FIFO(port->membase));
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

निकास_tx:
	अगर (uart_circ_empty(xmit)) अणु
		पंचांगp = पढ़ोl(LPC32XX_HSUART_CTRL(port->membase));
		पंचांगp &= ~LPC32XX_HSU_TX_INT_EN;
		ग_लिखोl(पंचांगp, LPC32XX_HSUART_CTRL(port->membase));
	पूर्ण
पूर्ण

अटल irqवापस_t serial_lpc32xx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	काष्ठा tty_port *tport = &port->state->port;
	u32 status;

	spin_lock(&port->lock);

	/* Read UART status and clear latched पूर्णांकerrupts */
	status = पढ़ोl(LPC32XX_HSUART_IIR(port->membase));

	अगर (status & LPC32XX_HSU_BRK_INT) अणु
		/* Break received */
		ग_लिखोl(LPC32XX_HSU_BRK_INT, LPC32XX_HSUART_IIR(port->membase));
		port->icount.brk++;
		uart_handle_अवरोध(port);
	पूर्ण

	/* Framing error */
	अगर (status & LPC32XX_HSU_FE_INT)
		ग_लिखोl(LPC32XX_HSU_FE_INT, LPC32XX_HSUART_IIR(port->membase));

	अगर (status & LPC32XX_HSU_RX_OE_INT) अणु
		/* Receive FIFO overrun */
		ग_लिखोl(LPC32XX_HSU_RX_OE_INT,
		       LPC32XX_HSUART_IIR(port->membase));
		port->icount.overrun++;
		tty_insert_flip_अक्षर(tport, 0, TTY_OVERRUN);
		tty_schedule_flip(tport);
	पूर्ण

	/* Data received? */
	अगर (status & (LPC32XX_HSU_RX_TIMEOUT_INT | LPC32XX_HSU_RX_TRIG_INT))
		__serial_lpc32xx_rx(port);

	/* Transmit data request? */
	अगर ((status & LPC32XX_HSU_TX_INT) && (!uart_tx_stopped(port))) अणु
		ग_लिखोl(LPC32XX_HSU_TX_INT, LPC32XX_HSUART_IIR(port->membase));
		__serial_lpc32xx_tx(port);
	पूर्ण

	spin_unlock(&port->lock);

	वापस IRQ_HANDLED;
पूर्ण

/* port->lock is not held.  */
अटल अचिन्हित पूर्णांक serial_lpc32xx_tx_empty(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक ret = 0;

	अगर (LPC32XX_HSU_TX_LEV(पढ़ोl(LPC32XX_HSUART_LEVEL(port->membase))) == 0)
		ret = TIOCSER_TEMT;

	वापस ret;
पूर्ण

/* port->lock held by caller.  */
अटल व्योम serial_lpc32xx_set_mctrl(काष्ठा uart_port *port,
				     अचिन्हित पूर्णांक mctrl)
अणु
	/* No संकेतs are supported on HS UARTs */
पूर्ण

/* port->lock is held by caller and पूर्णांकerrupts are disabled.  */
अटल अचिन्हित पूर्णांक serial_lpc32xx_get_mctrl(काष्ठा uart_port *port)
अणु
	/* No संकेतs are supported on HS UARTs */
	वापस TIOCM_CAR | TIOCM_DSR | TIOCM_CTS;
पूर्ण

/* port->lock held by caller.  */
अटल व्योम serial_lpc32xx_stop_tx(काष्ठा uart_port *port)
अणु
	u32 पंचांगp;

	पंचांगp = पढ़ोl(LPC32XX_HSUART_CTRL(port->membase));
	पंचांगp &= ~LPC32XX_HSU_TX_INT_EN;
	ग_लिखोl(पंचांगp, LPC32XX_HSUART_CTRL(port->membase));
पूर्ण

/* port->lock held by caller.  */
अटल व्योम serial_lpc32xx_start_tx(काष्ठा uart_port *port)
अणु
	u32 पंचांगp;

	__serial_lpc32xx_tx(port);
	पंचांगp = पढ़ोl(LPC32XX_HSUART_CTRL(port->membase));
	पंचांगp |= LPC32XX_HSU_TX_INT_EN;
	ग_लिखोl(पंचांगp, LPC32XX_HSUART_CTRL(port->membase));
पूर्ण

/* port->lock held by caller.  */
अटल व्योम serial_lpc32xx_stop_rx(काष्ठा uart_port *port)
अणु
	u32 पंचांगp;

	पंचांगp = पढ़ोl(LPC32XX_HSUART_CTRL(port->membase));
	पंचांगp &= ~(LPC32XX_HSU_RX_INT_EN | LPC32XX_HSU_ERR_INT_EN);
	ग_लिखोl(पंचांगp, LPC32XX_HSUART_CTRL(port->membase));

	ग_लिखोl((LPC32XX_HSU_BRK_INT | LPC32XX_HSU_RX_OE_INT |
		LPC32XX_HSU_FE_INT), LPC32XX_HSUART_IIR(port->membase));
पूर्ण

/* port->lock is not held.  */
अटल व्योम serial_lpc32xx_अवरोध_ctl(काष्ठा uart_port *port,
				     पूर्णांक अवरोध_state)
अणु
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	spin_lock_irqsave(&port->lock, flags);
	पंचांगp = पढ़ोl(LPC32XX_HSUART_CTRL(port->membase));
	अगर (अवरोध_state != 0)
		पंचांगp |= LPC32XX_HSU_BREAK;
	अन्यथा
		पंचांगp &= ~LPC32XX_HSU_BREAK;
	ग_लिखोl(पंचांगp, LPC32XX_HSUART_CTRL(port->membase));
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/* port->lock is not held.  */
अटल पूर्णांक serial_lpc32xx_startup(काष्ठा uart_port *port)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	spin_lock_irqsave(&port->lock, flags);

	__serial_uart_flush(port);

	ग_लिखोl((LPC32XX_HSU_TX_INT | LPC32XX_HSU_FE_INT |
		LPC32XX_HSU_BRK_INT | LPC32XX_HSU_RX_OE_INT),
	       LPC32XX_HSUART_IIR(port->membase));

	ग_लिखोl(0xFF, LPC32XX_HSUART_RATE(port->membase));

	/*
	 * Set receiver समयout, HSU offset of 20, no अवरोध, no पूर्णांकerrupts,
	 * and शेष FIFO trigger levels
	 */
	पंचांगp = LPC32XX_HSU_TX_TL8B | LPC32XX_HSU_RX_TL32B |
		LPC32XX_HSU_OFFSET(20) | LPC32XX_HSU_TMO_INACT_4B;
	ग_लिखोl(पंचांगp, LPC32XX_HSUART_CTRL(port->membase));

	lpc32xx_loopback_set(port->mapbase, 0); /* get out of loopback mode */

	spin_unlock_irqrestore(&port->lock, flags);

	retval = request_irq(port->irq, serial_lpc32xx_पूर्णांकerrupt,
			     0, MODNAME, port);
	अगर (!retval)
		ग_लिखोl((पंचांगp | LPC32XX_HSU_RX_INT_EN | LPC32XX_HSU_ERR_INT_EN),
		       LPC32XX_HSUART_CTRL(port->membase));

	वापस retval;
पूर्ण

/* port->lock is not held.  */
अटल व्योम serial_lpc32xx_shutकरोwn(काष्ठा uart_port *port)
अणु
	u32 पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	पंचांगp = LPC32XX_HSU_TX_TL8B | LPC32XX_HSU_RX_TL32B |
		LPC32XX_HSU_OFFSET(20) | LPC32XX_HSU_TMO_INACT_4B;
	ग_लिखोl(पंचांगp, LPC32XX_HSUART_CTRL(port->membase));

	lpc32xx_loopback_set(port->mapbase, 1); /* go to loopback mode */

	spin_unlock_irqrestore(&port->lock, flags);

	मुक्त_irq(port->irq, port);
पूर्ण

/* port->lock is not held.  */
अटल व्योम serial_lpc32xx_set_termios(काष्ठा uart_port *port,
				       काष्ठा ktermios *termios,
				       काष्ठा ktermios *old)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, quot;
	u32 पंचांगp;

	/* Always 8-bit, no parity, 1 stop bit */
	termios->c_cflag &= ~(CSIZE | CSTOPB | PARENB | PARODD);
	termios->c_cflag |= CS8;

	termios->c_cflag &= ~(HUPCL | CMSPAR | CLOCAL | CRTSCTS);

	baud = uart_get_baud_rate(port, termios, old, 0,
				  port->uartclk / 14);

	quot = __serial_get_घड़ी_भाग(port->uartclk, baud);

	spin_lock_irqsave(&port->lock, flags);

	/* Ignore अक्षरacters? */
	पंचांगp = पढ़ोl(LPC32XX_HSUART_CTRL(port->membase));
	अगर ((termios->c_cflag & CREAD) == 0)
		पंचांगp &= ~(LPC32XX_HSU_RX_INT_EN | LPC32XX_HSU_ERR_INT_EN);
	अन्यथा
		पंचांगp |= LPC32XX_HSU_RX_INT_EN | LPC32XX_HSU_ERR_INT_EN;
	ग_लिखोl(पंचांगp, LPC32XX_HSUART_CTRL(port->membase));

	ग_लिखोl(quot, LPC32XX_HSUART_RATE(port->membase));

	uart_update_समयout(port, termios->c_cflag, baud);

	spin_unlock_irqrestore(&port->lock, flags);

	/* Don't reग_लिखो B0 */
	अगर (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);
पूर्ण

अटल स्थिर अक्षर *serial_lpc32xx_type(काष्ठा uart_port *port)
अणु
	वापस MODNAME;
पूर्ण

अटल व्योम serial_lpc32xx_release_port(काष्ठा uart_port *port)
अणु
	अगर ((port->iotype == UPIO_MEM32) && (port->mapbase)) अणु
		अगर (port->flags & UPF_IOREMAP) अणु
			iounmap(port->membase);
			port->membase = शून्य;
		पूर्ण

		release_mem_region(port->mapbase, SZ_4K);
	पूर्ण
पूर्ण

अटल पूर्णांक serial_lpc32xx_request_port(काष्ठा uart_port *port)
अणु
	पूर्णांक ret = -ENODEV;

	अगर ((port->iotype == UPIO_MEM32) && (port->mapbase)) अणु
		ret = 0;

		अगर (!request_mem_region(port->mapbase, SZ_4K, MODNAME))
			ret = -EBUSY;
		अन्यथा अगर (port->flags & UPF_IOREMAP) अणु
			port->membase = ioremap(port->mapbase, SZ_4K);
			अगर (!port->membase) अणु
				release_mem_region(port->mapbase, SZ_4K);
				ret = -ENOMEM;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम serial_lpc32xx_config_port(काष्ठा uart_port *port, पूर्णांक uflags)
अणु
	पूर्णांक ret;

	ret = serial_lpc32xx_request_port(port);
	अगर (ret < 0)
		वापस;
	port->type = PORT_UART00;
	port->fअगरosize = 64;

	__serial_uart_flush(port);

	ग_लिखोl((LPC32XX_HSU_TX_INT | LPC32XX_HSU_FE_INT |
		LPC32XX_HSU_BRK_INT | LPC32XX_HSU_RX_OE_INT),
	       LPC32XX_HSUART_IIR(port->membase));

	ग_लिखोl(0xFF, LPC32XX_HSUART_RATE(port->membase));

	/* Set receiver समयout, HSU offset of 20, no अवरोध, no पूर्णांकerrupts,
	   and शेष FIFO trigger levels */
	ग_लिखोl(LPC32XX_HSU_TX_TL8B | LPC32XX_HSU_RX_TL32B |
	       LPC32XX_HSU_OFFSET(20) | LPC32XX_HSU_TMO_INACT_4B,
	       LPC32XX_HSUART_CTRL(port->membase));
पूर्ण

अटल पूर्णांक serial_lpc32xx_verअगरy_port(काष्ठा uart_port *port,
				      काष्ठा serial_काष्ठा *ser)
अणु
	पूर्णांक ret = 0;

	अगर (ser->type != PORT_UART00)
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा uart_ops serial_lpc32xx_pops = अणु
	.tx_empty	= serial_lpc32xx_tx_empty,
	.set_mctrl	= serial_lpc32xx_set_mctrl,
	.get_mctrl	= serial_lpc32xx_get_mctrl,
	.stop_tx	= serial_lpc32xx_stop_tx,
	.start_tx	= serial_lpc32xx_start_tx,
	.stop_rx	= serial_lpc32xx_stop_rx,
	.अवरोध_ctl	= serial_lpc32xx_अवरोध_ctl,
	.startup	= serial_lpc32xx_startup,
	.shutकरोwn	= serial_lpc32xx_shutकरोwn,
	.set_termios	= serial_lpc32xx_set_termios,
	.type		= serial_lpc32xx_type,
	.release_port	= serial_lpc32xx_release_port,
	.request_port	= serial_lpc32xx_request_port,
	.config_port	= serial_lpc32xx_config_port,
	.verअगरy_port	= serial_lpc32xx_verअगरy_port,
पूर्ण;

/*
 * Register a set of serial devices attached to a platक्रमm device
 */
अटल पूर्णांक serial_hs_lpc32xx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc32xx_hsuart_port *p = &lpc32xx_hs_ports[uarts_रेजिस्टरed];
	पूर्णांक ret = 0;
	काष्ठा resource *res;

	अगर (uarts_रेजिस्टरed >= MAX_PORTS) अणु
		dev_err(&pdev->dev,
			"Error: Number of possible ports exceeded (%d)!\n",
			uarts_रेजिस्टरed + 1);
		वापस -ENXIO;
	पूर्ण

	स_रखो(p, 0, माप(*p));

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev,
			"Error getting mem resource for HS UART port %d\n",
			uarts_रेजिस्टरed);
		वापस -ENXIO;
	पूर्ण
	p->port.mapbase = res->start;
	p->port.membase = शून्य;

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		वापस ret;
	p->port.irq = ret;

	p->port.iotype = UPIO_MEM32;
	p->port.uartclk = LPC32XX_MAIN_OSC_FREQ;
	p->port.regshअगरt = 2;
	p->port.flags = UPF_BOOT_AUTOCONF | UPF_FIXED_PORT | UPF_IOREMAP;
	p->port.dev = &pdev->dev;
	p->port.ops = &serial_lpc32xx_pops;
	p->port.line = uarts_रेजिस्टरed++;
	spin_lock_init(&p->port.lock);

	/* send port to loopback mode by शेष */
	lpc32xx_loopback_set(p->port.mapbase, 1);

	ret = uart_add_one_port(&lpc32xx_hs_reg, &p->port);

	platक्रमm_set_drvdata(pdev, p);

	वापस ret;
पूर्ण

/*
 * Remove serial ports रेजिस्टरed against a platक्रमm device.
 */
अटल पूर्णांक serial_hs_lpc32xx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc32xx_hsuart_port *p = platक्रमm_get_drvdata(pdev);

	uart_हटाओ_one_port(&lpc32xx_hs_reg, &p->port);

	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_PM
अटल पूर्णांक serial_hs_lpc32xx_suspend(काष्ठा platक्रमm_device *pdev,
				     pm_message_t state)
अणु
	काष्ठा lpc32xx_hsuart_port *p = platक्रमm_get_drvdata(pdev);

	uart_suspend_port(&lpc32xx_hs_reg, &p->port);

	वापस 0;
पूर्ण

अटल पूर्णांक serial_hs_lpc32xx_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc32xx_hsuart_port *p = platक्रमm_get_drvdata(pdev);

	uart_resume_port(&lpc32xx_hs_reg, &p->port);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा serial_hs_lpc32xx_suspend	शून्य
#घोषणा serial_hs_lpc32xx_resume	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id serial_hs_lpc32xx_dt_ids[] = अणु
	अणु .compatible = "nxp,lpc3220-hsuart" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, serial_hs_lpc32xx_dt_ids);

अटल काष्ठा platक्रमm_driver serial_hs_lpc32xx_driver = अणु
	.probe		= serial_hs_lpc32xx_probe,
	.हटाओ		= serial_hs_lpc32xx_हटाओ,
	.suspend	= serial_hs_lpc32xx_suspend,
	.resume		= serial_hs_lpc32xx_resume,
	.driver		= अणु
		.name	= MODNAME,
		.of_match_table	= serial_hs_lpc32xx_dt_ids,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init lpc32xx_hsuart_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&lpc32xx_hs_reg);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&serial_hs_lpc32xx_driver);
	अगर (ret)
		uart_unरेजिस्टर_driver(&lpc32xx_hs_reg);

	वापस ret;
पूर्ण

अटल व्योम __निकास lpc32xx_hsuart_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&serial_hs_lpc32xx_driver);
	uart_unरेजिस्टर_driver(&lpc32xx_hs_reg);
पूर्ण

module_init(lpc32xx_hsuart_init);
module_निकास(lpc32xx_hsuart_निकास);

MODULE_AUTHOR("Kevin Wells <kevin.wells@nxp.com>");
MODULE_AUTHOR("Roland Stigge <stigge@antcom.de>");
MODULE_DESCRIPTION("NXP LPC32XX High Speed UART driver");
MODULE_LICENSE("GPL");
