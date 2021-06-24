<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* sunhv.c: Serial driver क्रम SUN4V hypervisor console.
 *
 * Copyright (C) 2006, 2007 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/major.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/serial.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/console.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/spitfire.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/setup.h>

#समावेश <linux/serial_core.h>
#समावेश <linux/sunserialcore.h>

#घोषणा CON_BREAK	((दीर्घ)-1)
#घोषणा CON_HUP		((दीर्घ)-2)

#घोषणा IGNORE_BREAK	0x1
#घोषणा IGNORE_ALL	0x2

अटल अक्षर *con_ग_लिखो_page;
अटल अक्षर *con_पढ़ो_page;

अटल पूर्णांक hung_up = 0;

अटल व्योम transmit_अक्षरs_अक्षर_दो(काष्ठा uart_port *port, काष्ठा circ_buf *xmit)
अणु
	जबतक (!uart_circ_empty(xmit)) अणु
		दीर्घ status = sun4v_con_अक्षर_दो(xmit->buf[xmit->tail]);

		अगर (status != HV_EOK)
			अवरोध;

		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
	पूर्ण
पूर्ण

अटल व्योम transmit_अक्षरs_ग_लिखो(काष्ठा uart_port *port, काष्ठा circ_buf *xmit)
अणु
	जबतक (!uart_circ_empty(xmit)) अणु
		अचिन्हित दीर्घ ra = __pa(xmit->buf + xmit->tail);
		अचिन्हित दीर्घ len, status, sent;

		len = CIRC_CNT_TO_END(xmit->head, xmit->tail,
				      UART_XMIT_SIZE);
		status = sun4v_con_ग_लिखो(ra, len, &sent);
		अगर (status != HV_EOK)
			अवरोध;
		xmit->tail = (xmit->tail + sent) & (UART_XMIT_SIZE - 1);
		port->icount.tx += sent;
	पूर्ण
पूर्ण

अटल पूर्णांक receive_अक्षरs_अक्षर_लो(काष्ठा uart_port *port)
अणु
	पूर्णांक saw_console_brk = 0;
	पूर्णांक limit = 10000;

	जबतक (limit-- > 0) अणु
		दीर्घ status;
		दीर्घ c = sun4v_con_अक्षर_लो(&status);

		अगर (status == HV_EWOULDBLOCK)
			अवरोध;

		अगर (c == CON_BREAK) अणु
			अगर (uart_handle_अवरोध(port))
				जारी;
			saw_console_brk = 1;
			c = 0;
		पूर्ण

		अगर (c == CON_HUP) अणु
			hung_up = 1;
			uart_handle_dcd_change(port, 0);
		पूर्ण अन्यथा अगर (hung_up) अणु
			hung_up = 0;
			uart_handle_dcd_change(port, 1);
		पूर्ण

		अगर (port->state == शून्य) अणु
			uart_handle_sysrq_अक्षर(port, c);
			जारी;
		पूर्ण

		port->icount.rx++;

		अगर (uart_handle_sysrq_अक्षर(port, c))
			जारी;

		tty_insert_flip_अक्षर(&port->state->port, c, TTY_NORMAL);
	पूर्ण

	वापस saw_console_brk;
पूर्ण

अटल पूर्णांक receive_अक्षरs_पढ़ो(काष्ठा uart_port *port)
अणु
	अटल पूर्णांक saw_console_brk;
	पूर्णांक limit = 10000;

	जबतक (limit-- > 0) अणु
		अचिन्हित दीर्घ ra = __pa(con_पढ़ो_page);
		अचिन्हित दीर्घ bytes_पढ़ो, i;
		दीर्घ stat = sun4v_con_पढ़ो(ra, PAGE_SIZE, &bytes_पढ़ो);

		अगर (stat != HV_EOK) अणु
			bytes_पढ़ो = 0;

			अगर (stat == CON_BREAK) अणु
				अगर (saw_console_brk)
					sun_करो_अवरोध();

				अगर (uart_handle_अवरोध(port))
					जारी;
				saw_console_brk = 1;
				*con_पढ़ो_page = 0;
				bytes_पढ़ो = 1;
			पूर्ण अन्यथा अगर (stat == CON_HUP) अणु
				hung_up = 1;
				uart_handle_dcd_change(port, 0);
				जारी;
			पूर्ण अन्यथा अणु
				/* HV_EWOULDBLOCK, etc.  */
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (hung_up) अणु
			hung_up = 0;
			uart_handle_dcd_change(port, 1);
		पूर्ण

		अगर (port->sysrq != 0 &&  *con_पढ़ो_page) अणु
			क्रम (i = 0; i < bytes_पढ़ो; i++)
				uart_handle_sysrq_अक्षर(port, con_पढ़ो_page[i]);
			saw_console_brk = 0;
		पूर्ण

		अगर (port->state == शून्य)
			जारी;

		port->icount.rx += bytes_पढ़ो;

		tty_insert_flip_string(&port->state->port, con_पढ़ो_page,
				bytes_पढ़ो);
	पूर्ण

	वापस saw_console_brk;
पूर्ण

काष्ठा sunhv_ops अणु
	व्योम (*transmit_अक्षरs)(काष्ठा uart_port *port, काष्ठा circ_buf *xmit);
	पूर्णांक (*receive_अक्षरs)(काष्ठा uart_port *port);
पूर्ण;

अटल स्थिर काष्ठा sunhv_ops byअक्षर_ops = अणु
	.transmit_अक्षरs = transmit_अक्षरs_अक्षर_दो,
	.receive_अक्षरs = receive_अक्षरs_अक्षर_लो,
पूर्ण;

अटल स्थिर काष्ठा sunhv_ops byग_लिखो_ops = अणु
	.transmit_अक्षरs = transmit_अक्षरs_ग_लिखो,
	.receive_अक्षरs = receive_अक्षरs_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा sunhv_ops *sunhv_ops = &byअक्षर_ops;

अटल काष्ठा tty_port *receive_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा tty_port *tport = शून्य;

	अगर (port->state != शून्य)		/* Unखोलोed serial console */
		tport = &port->state->port;

	अगर (sunhv_ops->receive_अक्षरs(port))
		sun_करो_अवरोध();

	वापस tport;
पूर्ण

अटल व्योम transmit_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit;

	अगर (!port->state)
		वापस;

	xmit = &port->state->xmit;
	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port))
		वापस;

	sunhv_ops->transmit_अक्षरs(port, xmit);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);
पूर्ण

अटल irqवापस_t sunhv_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	काष्ठा tty_port *tport;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	tport = receive_अक्षरs(port);
	transmit_अक्षरs(port);
	spin_unlock_irqrestore(&port->lock, flags);

	अगर (tport)
		tty_flip_buffer_push(tport);

	वापस IRQ_HANDLED;
पूर्ण

/* port->lock is not held.  */
अटल अचिन्हित पूर्णांक sunhv_tx_empty(काष्ठा uart_port *port)
अणु
	/* Transmitter is always empty क्रम us.  If the circ buffer
	 * is non-empty or there is an x_अक्षर pending, our caller
	 * will करो the right thing and ignore what we वापस here.
	 */
	वापस TIOCSER_TEMT;
पूर्ण

/* port->lock held by caller.  */
अटल व्योम sunhv_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	वापस;
पूर्ण

/* port->lock is held by caller and पूर्णांकerrupts are disabled.  */
अटल अचिन्हित पूर्णांक sunhv_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस TIOCM_DSR | TIOCM_CAR | TIOCM_CTS;
पूर्ण

/* port->lock held by caller.  */
अटल व्योम sunhv_stop_tx(काष्ठा uart_port *port)
अणु
	वापस;
पूर्ण

/* port->lock held by caller.  */
अटल व्योम sunhv_start_tx(काष्ठा uart_port *port)
अणु
	transmit_अक्षरs(port);
पूर्ण

/* port->lock is not held.  */
अटल व्योम sunhv_send_xअक्षर(काष्ठा uart_port *port, अक्षर ch)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक limit = 10000;

	अगर (ch == __DISABLED_CHAR)
		वापस;

	spin_lock_irqsave(&port->lock, flags);

	जबतक (limit-- > 0) अणु
		दीर्घ status = sun4v_con_अक्षर_दो(ch);
		अगर (status == HV_EOK)
			अवरोध;
		udelay(1);
	पूर्ण

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/* port->lock held by caller.  */
अटल व्योम sunhv_stop_rx(काष्ठा uart_port *port)
अणु
पूर्ण

/* port->lock is not held.  */
अटल व्योम sunhv_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	अगर (अवरोध_state) अणु
		अचिन्हित दीर्घ flags;
		पूर्णांक limit = 10000;

		spin_lock_irqsave(&port->lock, flags);

		जबतक (limit-- > 0) अणु
			दीर्घ status = sun4v_con_अक्षर_दो(CON_BREAK);
			अगर (status == HV_EOK)
				अवरोध;
			udelay(1);
		पूर्ण

		spin_unlock_irqrestore(&port->lock, flags);
	पूर्ण
पूर्ण

/* port->lock is not held.  */
अटल पूर्णांक sunhv_startup(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

/* port->lock is not held.  */
अटल व्योम sunhv_shutकरोwn(काष्ठा uart_port *port)
अणु
पूर्ण

/* port->lock is not held.  */
अटल व्योम sunhv_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
			      काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक baud = uart_get_baud_rate(port, termios, old, 0, 4000000);
	अचिन्हित पूर्णांक quot = uart_get_भागisor(port, baud);
	अचिन्हित पूर्णांक अगरlag, cflag;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	अगरlag = termios->c_अगरlag;
	cflag = termios->c_cflag;

	port->ignore_status_mask = 0;
	अगर (अगरlag & IGNBRK)
		port->ignore_status_mask |= IGNORE_BREAK;
	अगर ((cflag & CREAD) == 0)
		port->ignore_status_mask |= IGNORE_ALL;

	/* XXX */
	uart_update_समयout(port, cflag,
			    (port->uartclk / (16 * quot)));

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *sunhv_type(काष्ठा uart_port *port)
अणु
	वापस "SUN4V HCONS";
पूर्ण

अटल व्योम sunhv_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक sunhv_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम sunhv_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
पूर्ण

अटल पूर्णांक sunhv_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा uart_ops sunhv_pops = अणु
	.tx_empty	= sunhv_tx_empty,
	.set_mctrl	= sunhv_set_mctrl,
	.get_mctrl	= sunhv_get_mctrl,
	.stop_tx	= sunhv_stop_tx,
	.start_tx	= sunhv_start_tx,
	.send_xअक्षर	= sunhv_send_xअक्षर,
	.stop_rx	= sunhv_stop_rx,
	.अवरोध_ctl	= sunhv_अवरोध_ctl,
	.startup	= sunhv_startup,
	.shutकरोwn	= sunhv_shutकरोwn,
	.set_termios	= sunhv_set_termios,
	.type		= sunhv_type,
	.release_port	= sunhv_release_port,
	.request_port	= sunhv_request_port,
	.config_port	= sunhv_config_port,
	.verअगरy_port	= sunhv_verअगरy_port,
पूर्ण;

अटल काष्ठा uart_driver sunhv_reg = अणु
	.owner			= THIS_MODULE,
	.driver_name		= "sunhv",
	.dev_name		= "ttyHV",
	.major			= TTY_MAJOR,
पूर्ण;

अटल काष्ठा uart_port *sunhv_port;

व्योम sunhv_migrate_hvcons_irq(पूर्णांक cpu)
अणु
	/* Migrate hvcons irq to param cpu */
	irq_क्रमce_affinity(sunhv_port->irq, cpumask_of(cpu));
पूर्ण

/* Copy 's' पूर्णांकo the con_ग_लिखो_page, decoding "\n" पूर्णांकo
 * "\r\n" aदीर्घ the way.  We have to वापस two lengths
 * because the caller needs to know how much to advance
 * 's' and also how many bytes to output via con_ग_लिखो_page.
 */
अटल पूर्णांक fill_con_ग_लिखो_page(स्थिर अक्षर *s, अचिन्हित पूर्णांक n,
			       अचिन्हित दीर्घ *page_bytes)
अणु
	स्थिर अक्षर *orig_s = s;
	अक्षर *p = con_ग_लिखो_page;
	पूर्णांक left = PAGE_SIZE;

	जबतक (n--) अणु
		अगर (*s == '\n') अणु
			अगर (left < 2)
				अवरोध;
			*p++ = '\r';
			left--;
		पूर्ण अन्यथा अगर (left < 1)
			अवरोध;
		*p++ = *s++;
		left--;
	पूर्ण
	*page_bytes = p - con_ग_लिखो_page;
	वापस s - orig_s;
पूर्ण

अटल व्योम sunhv_console_ग_लिखो_paged(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित n)
अणु
	काष्ठा uart_port *port = sunhv_port;
	अचिन्हित दीर्घ flags;
	पूर्णांक locked = 1;

	अगर (port->sysrq || oops_in_progress)
		locked = spin_trylock_irqsave(&port->lock, flags);
	अन्यथा
		spin_lock_irqsave(&port->lock, flags);

	जबतक (n > 0) अणु
		अचिन्हित दीर्घ ra = __pa(con_ग_लिखो_page);
		अचिन्हित दीर्घ page_bytes;
		अचिन्हित पूर्णांक cpy = fill_con_ग_लिखो_page(s, n,
						       &page_bytes);

		n -= cpy;
		s += cpy;
		जबतक (page_bytes > 0) अणु
			अचिन्हित दीर्घ written;
			पूर्णांक limit = 1000000;

			जबतक (limit--) अणु
				अचिन्हित दीर्घ stat;

				stat = sun4v_con_ग_लिखो(ra, page_bytes,
						       &written);
				अगर (stat == HV_EOK)
					अवरोध;
				udelay(1);
			पूर्ण
			अगर (limit < 0)
				अवरोध;
			page_bytes -= written;
			ra += written;
		पूर्ण
	पूर्ण

	अगर (locked)
		spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल अंतरभूत व्योम sunhv_console_अक्षर_दो(काष्ठा uart_port *port, अक्षर c)
अणु
	पूर्णांक limit = 1000000;

	जबतक (limit-- > 0) अणु
		दीर्घ status = sun4v_con_अक्षर_दो(c);
		अगर (status == HV_EOK)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम sunhv_console_ग_लिखो_byअक्षर(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित n)
अणु
	काष्ठा uart_port *port = sunhv_port;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, locked = 1;

	अगर (port->sysrq || oops_in_progress)
		locked = spin_trylock_irqsave(&port->lock, flags);
	अन्यथा
		spin_lock_irqsave(&port->lock, flags);

	क्रम (i = 0; i < n; i++) अणु
		अगर (*s == '\n')
			sunhv_console_अक्षर_दो(port, '\r');
		sunhv_console_अक्षर_दो(port, *s++);
	पूर्ण

	अगर (locked)
		spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल काष्ठा console sunhv_console = अणु
	.name	=	"ttyHV",
	.ग_लिखो	=	sunhv_console_ग_लिखो_byअक्षर,
	.device	=	uart_console_device,
	.flags	=	CON_PRINTBUFFER,
	.index	=	-1,
	.data	=	&sunhv_reg,
पूर्ण;

अटल पूर्णांक hv_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा uart_port *port;
	अचिन्हित दीर्घ minor;
	पूर्णांक err;

	अगर (op->archdata.irqs[0] == 0xffffffff)
		वापस -ENODEV;

	port = kzalloc(माप(काष्ठा uart_port), GFP_KERNEL);
	अगर (unlikely(!port))
		वापस -ENOMEM;

	minor = 1;
	अगर (sun4v_hvapi_रेजिस्टर(HV_GRP_CORE, 1, &minor) == 0 &&
	    minor >= 1) अणु
		err = -ENOMEM;
		con_ग_लिखो_page = kzalloc(PAGE_SIZE, GFP_KERNEL);
		अगर (!con_ग_लिखो_page)
			जाओ out_मुक्त_port;

		con_पढ़ो_page = kzalloc(PAGE_SIZE, GFP_KERNEL);
		अगर (!con_पढ़ो_page)
			जाओ out_मुक्त_con_ग_लिखो_page;

		sunhv_console.ग_लिखो = sunhv_console_ग_लिखो_paged;
		sunhv_ops = &byग_लिखो_ops;
	पूर्ण

	sunhv_port = port;

	port->has_sysrq = 1;
	port->line = 0;
	port->ops = &sunhv_pops;
	port->type = PORT_SUNHV;
	port->uartclk = ( 29491200 / 16 ); /* arbitrary */

	port->membase = (अचिन्हित अक्षर __iomem *) __pa(port);

	port->irq = op->archdata.irqs[0];

	port->dev = &op->dev;

	err = sunserial_रेजिस्टर_minors(&sunhv_reg, 1);
	अगर (err)
		जाओ out_मुक्त_con_पढ़ो_page;

	sunserial_console_match(&sunhv_console, op->dev.of_node,
				&sunhv_reg, port->line, false);

	err = uart_add_one_port(&sunhv_reg, port);
	अगर (err)
		जाओ out_unरेजिस्टर_driver;

	err = request_irq(port->irq, sunhv_पूर्णांकerrupt, 0, "hvcons", port);
	अगर (err)
		जाओ out_हटाओ_port;

	platक्रमm_set_drvdata(op, port);

	वापस 0;

out_हटाओ_port:
	uart_हटाओ_one_port(&sunhv_reg, port);

out_unरेजिस्टर_driver:
	sunserial_unरेजिस्टर_minors(&sunhv_reg, 1);

out_मुक्त_con_पढ़ो_page:
	kमुक्त(con_पढ़ो_page);

out_मुक्त_con_ग_लिखो_page:
	kमुक्त(con_ग_लिखो_page);

out_मुक्त_port:
	kमुक्त(port);
	sunhv_port = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक hv_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा uart_port *port = platक्रमm_get_drvdata(dev);

	मुक्त_irq(port->irq, port);

	uart_हटाओ_one_port(&sunhv_reg, port);

	sunserial_unरेजिस्टर_minors(&sunhv_reg, 1);
	kमुक्त(con_पढ़ो_page);
	kमुक्त(con_ग_लिखो_page);
	kमुक्त(port);
	sunhv_port = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hv_match[] = अणु
	अणु
		.name = "console",
		.compatible = "qcn",
	पूर्ण,
	अणु
		.name = "console",
		.compatible = "SUNW,sun4v-console",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver hv_driver = अणु
	.driver = अणु
		.name = "hv",
		.of_match_table = hv_match,
	पूर्ण,
	.probe		= hv_probe,
	.हटाओ		= hv_हटाओ,
पूर्ण;

अटल पूर्णांक __init sunhv_init(व्योम)
अणु
	अगर (tlb_type != hypervisor)
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&hv_driver);
पूर्ण
device_initcall(sunhv_init);

#अगर 0 /* ...def MODULE ; never supported as such */
MODULE_AUTHOR("David S. Miller");
MODULE_DESCRIPTION("SUN4V Hypervisor console driver");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
#पूर्ण_अगर
