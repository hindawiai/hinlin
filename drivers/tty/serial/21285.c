<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the serial port on the 21285 StrongArm-110 core logic chip.
 *
 * Based on drivers/अक्षर/serial.c
 */
#समावेश <linux/module.h>
#समावेश <linux/tty.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/device.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/hardware/dec21285.h>
#समावेश <mach/hardware.h>

#घोषणा BAUD_BASE		(mem_fclk_21285/64)

#घोषणा SERIAL_21285_NAME	"ttyFB"
#घोषणा SERIAL_21285_MAJOR	204
#घोषणा SERIAL_21285_MINOR	4

#घोषणा RXSTAT_DUMMY_READ	0x80000000
#घोषणा RXSTAT_FRAME		(1 << 0)
#घोषणा RXSTAT_PARITY		(1 << 1)
#घोषणा RXSTAT_OVERRUN		(1 << 2)
#घोषणा RXSTAT_ANYERR		(RXSTAT_FRAME|RXSTAT_PARITY|RXSTAT_OVERRUN)

#घोषणा H_UBRLCR_BREAK		(1 << 0)
#घोषणा H_UBRLCR_PARENB		(1 << 1)
#घोषणा H_UBRLCR_PAREVN		(1 << 2)
#घोषणा H_UBRLCR_STOPB		(1 << 3)
#घोषणा H_UBRLCR_FIFO		(1 << 4)

अटल स्थिर अक्षर serial21285_name[] = "Footbridge UART";

/*
 * We only need 2 bits of data, so instead of creating a whole काष्ठाure क्रम
 * this, use bits of the निजी_data poपूर्णांकer of the uart port काष्ठाure.
 */
#घोषणा tx_enabled_bit	0
#घोषणा rx_enabled_bit	1

अटल bool is_enabled(काष्ठा uart_port *port, पूर्णांक bit)
अणु
	अचिन्हित दीर्घ *निजी_data = (अचिन्हित दीर्घ *)&port->निजी_data;

	अगर (test_bit(bit, निजी_data))
		वापस true;
	वापस false;
पूर्ण

अटल व्योम enable(काष्ठा uart_port *port, पूर्णांक bit)
अणु
	अचिन्हित दीर्घ *निजी_data = (अचिन्हित दीर्घ *)&port->निजी_data;

	set_bit(bit, निजी_data);
पूर्ण

अटल व्योम disable(काष्ठा uart_port *port, पूर्णांक bit)
अणु
	अचिन्हित दीर्घ *निजी_data = (अचिन्हित दीर्घ *)&port->निजी_data;

	clear_bit(bit, निजी_data);
पूर्ण

#घोषणा is_tx_enabled(port)	is_enabled(port, tx_enabled_bit)
#घोषणा tx_enable(port)		enable(port, tx_enabled_bit)
#घोषणा tx_disable(port)	disable(port, tx_enabled_bit)

#घोषणा is_rx_enabled(port)	is_enabled(port, rx_enabled_bit)
#घोषणा rx_enable(port)		enable(port, rx_enabled_bit)
#घोषणा rx_disable(port)	disable(port, rx_enabled_bit)

/*
 * The करोcumented expression क्रम selecting the भागisor is:
 *  BAUD_BASE / baud - 1
 * However, typically BAUD_BASE is not भागisible by baud, so
 * we want to select the भागisor that gives us the minimum
 * error.  Thereक्रमe, we want:
 *  पूर्णांक(BAUD_BASE / baud - 0.5) ->
 *  पूर्णांक(BAUD_BASE / baud - (baud >> 1) / baud) ->
 *  पूर्णांक((BAUD_BASE - (baud >> 1)) / baud)
 */

अटल व्योम serial21285_stop_tx(काष्ठा uart_port *port)
अणु
	अगर (is_tx_enabled(port)) अणु
		disable_irq_nosync(IRQ_CONTX);
		tx_disable(port);
	पूर्ण
पूर्ण

अटल व्योम serial21285_start_tx(काष्ठा uart_port *port)
अणु
	अगर (!is_tx_enabled(port)) अणु
		enable_irq(IRQ_CONTX);
		tx_enable(port);
	पूर्ण
पूर्ण

अटल व्योम serial21285_stop_rx(काष्ठा uart_port *port)
अणु
	अगर (is_rx_enabled(port)) अणु
		disable_irq_nosync(IRQ_CONRX);
		rx_disable(port);
	पूर्ण
पूर्ण

अटल irqवापस_t serial21285_rx_अक्षरs(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	अचिन्हित पूर्णांक status, ch, flag, rxs, max_count = 256;

	status = *CSR_UARTFLG;
	जबतक (!(status & 0x10) && max_count--) अणु
		ch = *CSR_UARTDR;
		flag = TTY_NORMAL;
		port->icount.rx++;

		rxs = *CSR_RXSTAT | RXSTAT_DUMMY_READ;
		अगर (unlikely(rxs & RXSTAT_ANYERR)) अणु
			अगर (rxs & RXSTAT_PARITY)
				port->icount.parity++;
			अन्यथा अगर (rxs & RXSTAT_FRAME)
				port->icount.frame++;
			अगर (rxs & RXSTAT_OVERRUN)
				port->icount.overrun++;

			rxs &= port->पढ़ो_status_mask;

			अगर (rxs & RXSTAT_PARITY)
				flag = TTY_PARITY;
			अन्यथा अगर (rxs & RXSTAT_FRAME)
				flag = TTY_FRAME;
		पूर्ण

		uart_insert_अक्षर(port, rxs, RXSTAT_OVERRUN, ch, flag);

		status = *CSR_UARTFLG;
	पूर्ण
	tty_flip_buffer_push(&port->state->port);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t serial21285_tx_अक्षरs(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	पूर्णांक count = 256;

	अगर (port->x_अक्षर) अणु
		*CSR_UARTDR = port->x_अक्षर;
		port->icount.tx++;
		port->x_अक्षर = 0;
		जाओ out;
	पूर्ण
	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		serial21285_stop_tx(port);
		जाओ out;
	पूर्ण

	करो अणु
		*CSR_UARTDR = xmit->buf[xmit->tail];
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण जबतक (--count > 0 && !(*CSR_UARTFLG & 0x20));

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (uart_circ_empty(xmit))
		serial21285_stop_tx(port);

 out:
	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक serial21285_tx_empty(काष्ठा uart_port *port)
अणु
	वापस (*CSR_UARTFLG & 8) ? 0 : TIOCSER_TEMT;
पूर्ण

/* no modem control lines */
अटल अचिन्हित पूर्णांक serial21285_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस TIOCM_CAR | TIOCM_DSR | TIOCM_CTS;
पूर्ण

अटल व्योम serial21285_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
पूर्ण

अटल व्योम serial21285_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक h_lcr;

	spin_lock_irqsave(&port->lock, flags);
	h_lcr = *CSR_H_UBRLCR;
	अगर (अवरोध_state)
		h_lcr |= H_UBRLCR_BREAK;
	अन्यथा
		h_lcr &= ~H_UBRLCR_BREAK;
	*CSR_H_UBRLCR = h_lcr;
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल पूर्णांक serial21285_startup(काष्ठा uart_port *port)
अणु
	पूर्णांक ret;

	tx_enable(port);
	rx_enable(port);

	ret = request_irq(IRQ_CONRX, serial21285_rx_अक्षरs, 0,
			  serial21285_name, port);
	अगर (ret == 0) अणु
		ret = request_irq(IRQ_CONTX, serial21285_tx_अक्षरs, 0,
				  serial21285_name, port);
		अगर (ret)
			मुक्त_irq(IRQ_CONRX, port);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम serial21285_shutकरोwn(काष्ठा uart_port *port)
अणु
	मुक्त_irq(IRQ_CONTX, port);
	मुक्त_irq(IRQ_CONRX, port);
पूर्ण

अटल व्योम
serial21285_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
			काष्ठा ktermios *old)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, quot, h_lcr, b;

	/*
	 * We करोn't support modem control lines.
	 */
	termios->c_cflag &= ~(HUPCL | CRTSCTS | CMSPAR);
	termios->c_cflag |= CLOCAL;

	/*
	 * We करोn't support BREAK अक्षरacter recognition.
	 */
	termios->c_अगरlag &= ~(IGNBRK | BRKINT);

	/*
	 * Ask the core to calculate the भागisor क्रम us.
	 */
	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk/16); 
	quot = uart_get_भागisor(port, baud);
	b = port->uartclk / (16 * quot);
	tty_termios_encode_baud_rate(termios, b, b);

	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		h_lcr = 0x00;
		अवरोध;
	हाल CS6:
		h_lcr = 0x20;
		अवरोध;
	हाल CS7:
		h_lcr = 0x40;
		अवरोध;
	शेष: /* CS8 */
		h_lcr = 0x60;
		अवरोध;
	पूर्ण

	अगर (termios->c_cflag & CSTOPB)
		h_lcr |= H_UBRLCR_STOPB;
	अगर (termios->c_cflag & PARENB) अणु
		h_lcr |= H_UBRLCR_PARENB;
		अगर (!(termios->c_cflag & PARODD))
			h_lcr |= H_UBRLCR_PAREVN;
	पूर्ण

	अगर (port->fअगरosize)
		h_lcr |= H_UBRLCR_FIFO;

	spin_lock_irqsave(&port->lock, flags);

	/*
	 * Update the per-port समयout.
	 */
	uart_update_समयout(port, termios->c_cflag, baud);

	/*
	 * Which अक्षरacter status flags are we पूर्णांकerested in?
	 */
	port->पढ़ो_status_mask = RXSTAT_OVERRUN;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= RXSTAT_FRAME | RXSTAT_PARITY;

	/*
	 * Which अक्षरacter status flags should we ignore?
	 */
	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= RXSTAT_FRAME | RXSTAT_PARITY;
	अगर (termios->c_अगरlag & IGNBRK && termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= RXSTAT_OVERRUN;

	/*
	 * Ignore all अक्षरacters अगर CREAD is not set.
	 */
	अगर ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= RXSTAT_DUMMY_READ;

	quot -= 1;

	*CSR_UARTCON = 0;
	*CSR_L_UBRLCR = quot & 0xff;
	*CSR_M_UBRLCR = (quot >> 8) & 0x0f;
	*CSR_H_UBRLCR = h_lcr;
	*CSR_UARTCON = 1;

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *serial21285_type(काष्ठा uart_port *port)
अणु
	वापस port->type == PORT_21285 ? "DC21285" : शून्य;
पूर्ण

अटल व्योम serial21285_release_port(काष्ठा uart_port *port)
अणु
	release_mem_region(port->mapbase, 32);
पूर्ण

अटल पूर्णांक serial21285_request_port(काष्ठा uart_port *port)
अणु
	वापस request_mem_region(port->mapbase, 32, serial21285_name)
			 != शून्य ? 0 : -EBUSY;
पूर्ण

अटल व्योम serial21285_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE && serial21285_request_port(port) == 0)
		port->type = PORT_21285;
पूर्ण

/*
 * verअगरy the new serial_काष्ठा (क्रम TIOCSSERIAL).
 */
अटल पूर्णांक serial21285_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	पूर्णांक ret = 0;
	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_21285)
		ret = -EINVAL;
	अगर (ser->irq <= 0)
		ret = -EINVAL;
	अगर (ser->baud_base != port->uartclk / 16)
		ret = -EINVAL;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा uart_ops serial21285_ops = अणु
	.tx_empty	= serial21285_tx_empty,
	.get_mctrl	= serial21285_get_mctrl,
	.set_mctrl	= serial21285_set_mctrl,
	.stop_tx	= serial21285_stop_tx,
	.start_tx	= serial21285_start_tx,
	.stop_rx	= serial21285_stop_rx,
	.अवरोध_ctl	= serial21285_अवरोध_ctl,
	.startup	= serial21285_startup,
	.shutकरोwn	= serial21285_shutकरोwn,
	.set_termios	= serial21285_set_termios,
	.type		= serial21285_type,
	.release_port	= serial21285_release_port,
	.request_port	= serial21285_request_port,
	.config_port	= serial21285_config_port,
	.verअगरy_port	= serial21285_verअगरy_port,
पूर्ण;

अटल काष्ठा uart_port serial21285_port = अणु
	.mapbase	= 0x42000160,
	.iotype		= UPIO_MEM,
	.irq		= 0,
	.fअगरosize	= 16,
	.ops		= &serial21285_ops,
	.flags		= UPF_BOOT_AUTOCONF,
पूर्ण;

अटल व्योम serial21285_setup_ports(व्योम)
अणु
	serial21285_port.uartclk = mem_fclk_21285 / 4;
पूर्ण

#अगर_घोषित CONFIG_SERIAL_21285_CONSOLE
अटल व्योम serial21285_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	जबतक (*CSR_UARTFLG & 0x20)
		barrier();
	*CSR_UARTDR = ch;
पूर्ण

अटल व्योम
serial21285_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
			  अचिन्हित पूर्णांक count)
अणु
	uart_console_ग_लिखो(&serial21285_port, s, count, serial21285_console_अक्षर_दो);
पूर्ण

अटल व्योम __init
serial21285_get_options(काष्ठा uart_port *port, पूर्णांक *baud,
			पूर्णांक *parity, पूर्णांक *bits)
अणु
	अगर (*CSR_UARTCON == 1) अणु
		अचिन्हित पूर्णांक पंचांगp;

		पंचांगp = *CSR_H_UBRLCR;
		चयन (पंचांगp & 0x60) अणु
		हाल 0x00:
			*bits = 5;
			अवरोध;
		हाल 0x20:
			*bits = 6;
			अवरोध;
		हाल 0x40:
			*bits = 7;
			अवरोध;
		शेष:
		हाल 0x60:
			*bits = 8;
			अवरोध;
		पूर्ण

		अगर (पंचांगp & H_UBRLCR_PARENB) अणु
			*parity = 'o';
			अगर (पंचांगp & H_UBRLCR_PAREVN)
				*parity = 'e';
		पूर्ण

		पंचांगp = *CSR_L_UBRLCR | (*CSR_M_UBRLCR << 8);

		*baud = port->uartclk / (16 * (पंचांगp + 1));
	पूर्ण
पूर्ण

अटल पूर्णांक __init serial21285_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port = &serial21285_port;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (machine_is_personal_server())
		baud = 57600;

	/*
	 * Check whether an invalid uart number has been specअगरied, and
	 * अगर so, search क्रम the first available port that करोes have
	 * console support.
	 */
	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	अन्यथा
		serial21285_get_options(port, &baud, &parity, &bits);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver serial21285_reg;

अटल काष्ठा console serial21285_console =
अणु
	.name		= SERIAL_21285_NAME,
	.ग_लिखो		= serial21285_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= serial21285_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &serial21285_reg,
पूर्ण;

अटल पूर्णांक __init rs285_console_init(व्योम)
अणु
	serial21285_setup_ports();
	रेजिस्टर_console(&serial21285_console);
	वापस 0;
पूर्ण
console_initcall(rs285_console_init);

#घोषणा SERIAL_21285_CONSOLE	&serial21285_console
#अन्यथा
#घोषणा SERIAL_21285_CONSOLE	शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver serial21285_reg = अणु
	.owner			= THIS_MODULE,
	.driver_name		= "ttyFB",
	.dev_name		= "ttyFB",
	.major			= SERIAL_21285_MAJOR,
	.minor			= SERIAL_21285_MINOR,
	.nr			= 1,
	.cons			= SERIAL_21285_CONSOLE,
पूर्ण;

अटल पूर्णांक __init serial21285_init(व्योम)
अणु
	पूर्णांक ret;

	prपूर्णांकk(KERN_INFO "Serial: 21285 driver\n");

	serial21285_setup_ports();

	ret = uart_रेजिस्टर_driver(&serial21285_reg);
	अगर (ret == 0)
		uart_add_one_port(&serial21285_reg, &serial21285_port);

	वापस ret;
पूर्ण

अटल व्योम __निकास serial21285_निकास(व्योम)
अणु
	uart_हटाओ_one_port(&serial21285_reg, &serial21285_port);
	uart_unरेजिस्टर_driver(&serial21285_reg);
पूर्ण

module_init(serial21285_init);
module_निकास(serial21285_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Intel Footbridge (21285) serial driver");
MODULE_ALIAS_CHARDEV(SERIAL_21285_MAJOR, SERIAL_21285_MINOR);
