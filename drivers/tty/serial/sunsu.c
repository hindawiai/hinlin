<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * su.c: Small serial driver क्रम keyboard/mouse पूर्णांकerface on sparc32/PCI
 *
 * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)
 * Copyright (C) 1998-1999  Pete Zaitcev   (zaitcev@yahoo.com)
 *
 * This is मुख्यly a variation of 8250.c, credits go to authors mentioned
 * therein.  In fact this driver should be merged पूर्णांकo the generic 8250.c
 * infraकाष्ठाure perhaps using a 8250_sparc.c module.
 *
 * Fixed to use tty_get_baud_rate().
 *   Theoकरोre Ts'o <tytso@mit.edu>, 2001-Oct-12
 *
 * Converted to new 2.5.x UART layer.
 *   David S. Miller (davem@davemloft.net), 2002-Jul-29
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/major.h>
#समावेश <linux/माला.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/ioport.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/serial.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/console.h>
#समावेश <linux/slab.h>
#अगर_घोषित CONFIG_SERIO
#समावेश <linux/serपन.स>
#पूर्ण_अगर
#समावेश <linux/serial_reg.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/setup.h>

#समावेश <linux/serial_core.h>
#समावेश <linux/sunserialcore.h>

/* We are on a NS PC87303 घड़ीed with 24.0 MHz, which results
 * in a UART घड़ी of 1.8462 MHz.
 */
#घोषणा SU_BASE_BAUD	(1846200 / 16)

क्रमागत su_type अणु SU_PORT_NONE, SU_PORT_MS, SU_PORT_KBD, SU_PORT_PORT पूर्ण;
अटल अक्षर *su_typev[] = अणु "su(???)", "su(mouse)", "su(kbd)", "su(serial)" पूर्ण;

काष्ठा serial_uart_config अणु
	अक्षर	*name;
	पूर्णांक	dfl_xmit_fअगरo_size;
	पूर्णांक	flags;
पूर्ण;

/*
 * Here we define the शेष xmit fअगरo size used क्रम each type of UART.
 */
अटल स्थिर काष्ठा serial_uart_config uart_config[] = अणु
	अणु "unknown",	1,	0 पूर्ण,
	अणु "8250",	1,	0 पूर्ण,
	अणु "16450",	1,	0 पूर्ण,
	अणु "16550",	1,	0 पूर्ण,
	अणु "16550A",	16,	UART_CLEAR_FIFO | UART_USE_FIFO पूर्ण,
	अणु "Cirrus",	1, 	0 पूर्ण,
	अणु "ST16650",	1,	UART_CLEAR_FIFO | UART_STARTECH पूर्ण,
	अणु "ST16650V2",	32,	UART_CLEAR_FIFO | UART_USE_FIFO | UART_STARTECH पूर्ण,
	अणु "TI16750",	64,	UART_CLEAR_FIFO | UART_USE_FIFO पूर्ण,
	अणु "Startech",	1,	0 पूर्ण,
	अणु "16C950/954",	128,	UART_CLEAR_FIFO | UART_USE_FIFO पूर्ण,
	अणु "ST16654",	64,	UART_CLEAR_FIFO | UART_USE_FIFO | UART_STARTECH पूर्ण,
	अणु "XR16850",	128,	UART_CLEAR_FIFO | UART_USE_FIFO | UART_STARTECH पूर्ण,
	अणु "RSA",	2048,	UART_CLEAR_FIFO | UART_USE_FIFO पूर्ण
पूर्ण;

काष्ठा uart_sunsu_port अणु
	काष्ठा uart_port	port;
	अचिन्हित अक्षर		acr;
	अचिन्हित अक्षर		ier;
	अचिन्हित लघु		rev;
	अचिन्हित अक्षर		lcr;
	अचिन्हित पूर्णांक		lsr_अवरोध_flag;
	अचिन्हित पूर्णांक		cflag;

	/* Probing inक्रमmation.  */
	क्रमागत su_type		su_type;
	अचिन्हित पूर्णांक		type_probed;	/* XXX Stupid */
	अचिन्हित दीर्घ		reg_size;

#अगर_घोषित CONFIG_SERIO
	काष्ठा serio		serio;
	पूर्णांक			serio_खोलो;
#पूर्ण_अगर
पूर्ण;

अटल अचिन्हित पूर्णांक serial_in(काष्ठा uart_sunsu_port *up, पूर्णांक offset)
अणु
	offset <<= up->port.regshअगरt;

	चयन (up->port.iotype) अणु
	हाल UPIO_HUB6:
		outb(up->port.hub6 - 1 + offset, up->port.iobase);
		वापस inb(up->port.iobase + 1);

	हाल UPIO_MEM:
		वापस पढ़ोb(up->port.membase + offset);

	शेष:
		वापस inb(up->port.iobase + offset);
	पूर्ण
पूर्ण

अटल व्योम serial_out(काष्ठा uart_sunsu_port *up, पूर्णांक offset, पूर्णांक value)
अणु
#अगर_अघोषित CONFIG_SPARC64
	/*
	 * MrCoffee has weird schematics: IRQ4 & P10(?) pins of SuperIO are
	 * connected with a gate then go to SlavIO. When IRQ4 goes tristated
	 * gate outमाला_दो a logical one. Since we use level triggered पूर्णांकerrupts
	 * we have lockup and watchकरोg reset. We cannot mask IRQ because
	 * keyboard shares IRQ with us (Word has it as Bob Smelik's design).
	 * This problem is similar to what Alpha people suffer, see serial.c.
	 */
	अगर (offset == UART_MCR)
		value |= UART_MCR_OUT2;
#पूर्ण_अगर
	offset <<= up->port.regshअगरt;

	चयन (up->port.iotype) अणु
	हाल UPIO_HUB6:
		outb(up->port.hub6 - 1 + offset, up->port.iobase);
		outb(value, up->port.iobase + 1);
		अवरोध;

	हाल UPIO_MEM:
		ग_लिखोb(value, up->port.membase + offset);
		अवरोध;

	शेष:
		outb(value, up->port.iobase + offset);
	पूर्ण
पूर्ण

/*
 * We used to support using छोड़ो I/O क्रम certain machines.  We
 * haven't supported this for a while, but just in case it's badly
 * needed क्रम certain old 386 machines, I've left these #define's
 * in....
 */
#घोषणा serial_inp(up, offset)		serial_in(up, offset)
#घोषणा serial_outp(up, offset, value)	serial_out(up, offset, value)


/*
 * For the 16C950
 */
अटल व्योम serial_icr_ग_लिखो(काष्ठा uart_sunsu_port *up, पूर्णांक offset, पूर्णांक value)
अणु
	serial_out(up, UART_SCR, offset);
	serial_out(up, UART_ICR, value);
पूर्ण

#अगर 0 /* Unused currently */
अटल अचिन्हित पूर्णांक serial_icr_पढ़ो(काष्ठा uart_sunsu_port *up, पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक value;

	serial_icr_ग_लिखो(up, UART_ACR, up->acr | UART_ACR_ICRRD);
	serial_out(up, UART_SCR, offset);
	value = serial_in(up, UART_ICR);
	serial_icr_ग_लिखो(up, UART_ACR, up->acr);

	वापस value;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SERIAL_8250_RSA
/*
 * Attempts to turn on the RSA FIFO.  Returns zero on failure.
 * We set the port uart घड़ी rate अगर we succeed.
 */
अटल पूर्णांक __enable_rsa(काष्ठा uart_sunsu_port *up)
अणु
	अचिन्हित अक्षर mode;
	पूर्णांक result;

	mode = serial_inp(up, UART_RSA_MSR);
	result = mode & UART_RSA_MSR_FIFO;

	अगर (!result) अणु
		serial_outp(up, UART_RSA_MSR, mode | UART_RSA_MSR_FIFO);
		mode = serial_inp(up, UART_RSA_MSR);
		result = mode & UART_RSA_MSR_FIFO;
	पूर्ण

	अगर (result)
		up->port.uartclk = SERIAL_RSA_BAUD_BASE * 16;

	वापस result;
पूर्ण

अटल व्योम enable_rsa(काष्ठा uart_sunsu_port *up)
अणु
	अगर (up->port.type == PORT_RSA) अणु
		अगर (up->port.uartclk != SERIAL_RSA_BAUD_BASE * 16) अणु
			spin_lock_irq(&up->port.lock);
			__enable_rsa(up);
			spin_unlock_irq(&up->port.lock);
		पूर्ण
		अगर (up->port.uartclk == SERIAL_RSA_BAUD_BASE * 16)
			serial_outp(up, UART_RSA_FRR, 0);
	पूर्ण
पूर्ण

/*
 * Attempts to turn off the RSA FIFO.  Returns zero on failure.
 * It is unknown why पूर्णांकerrupts were disabled in here.  However,
 * the caller is expected to preserve this behaviour by grabbing
 * the spinlock beक्रमe calling this function.
 */
अटल व्योम disable_rsa(काष्ठा uart_sunsu_port *up)
अणु
	अचिन्हित अक्षर mode;
	पूर्णांक result;

	अगर (up->port.type == PORT_RSA &&
	    up->port.uartclk == SERIAL_RSA_BAUD_BASE * 16) अणु
		spin_lock_irq(&up->port.lock);

		mode = serial_inp(up, UART_RSA_MSR);
		result = !(mode & UART_RSA_MSR_FIFO);

		अगर (!result) अणु
			serial_outp(up, UART_RSA_MSR, mode & ~UART_RSA_MSR_FIFO);
			mode = serial_inp(up, UART_RSA_MSR);
			result = !(mode & UART_RSA_MSR_FIFO);
		पूर्ण

		अगर (result)
			up->port.uartclk = SERIAL_RSA_BAUD_BASE_LO * 16;
		spin_unlock_irq(&up->port.lock);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SERIAL_8250_RSA */

अटल अंतरभूत व्योम __stop_tx(काष्ठा uart_sunsu_port *p)
अणु
	अगर (p->ier & UART_IER_THRI) अणु
		p->ier &= ~UART_IER_THRI;
		serial_out(p, UART_IER, p->ier);
	पूर्ण
पूर्ण

अटल व्योम sunsu_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunsu_port *up =
		container_of(port, काष्ठा uart_sunsu_port, port);

	__stop_tx(up);

	/*
	 * We really want to stop the transmitter from sending.
	 */
	अगर (up->port.type == PORT_16C950) अणु
		up->acr |= UART_ACR_TXDIS;
		serial_icr_ग_लिखो(up, UART_ACR, up->acr);
	पूर्ण
पूर्ण

अटल व्योम sunsu_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunsu_port *up =
		container_of(port, काष्ठा uart_sunsu_port, port);

	अगर (!(up->ier & UART_IER_THRI)) अणु
		up->ier |= UART_IER_THRI;
		serial_out(up, UART_IER, up->ier);
	पूर्ण

	/*
	 * Re-enable the transmitter अगर we disabled it.
	 */
	अगर (up->port.type == PORT_16C950 && up->acr & UART_ACR_TXDIS) अणु
		up->acr &= ~UART_ACR_TXDIS;
		serial_icr_ग_लिखो(up, UART_ACR, up->acr);
	पूर्ण
पूर्ण

अटल व्योम sunsu_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunsu_port *up =
		container_of(port, काष्ठा uart_sunsu_port, port);

	up->ier &= ~UART_IER_RLSI;
	up->port.पढ़ो_status_mask &= ~UART_LSR_DR;
	serial_out(up, UART_IER, up->ier);
पूर्ण

अटल व्योम sunsu_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunsu_port *up =
		container_of(port, काष्ठा uart_sunsu_port, port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&up->port.lock, flags);
	up->ier |= UART_IER_MSI;
	serial_out(up, UART_IER, up->ier);
	spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

अटल व्योम
receive_अक्षरs(काष्ठा uart_sunsu_port *up, अचिन्हित अक्षर *status)
अणु
	काष्ठा tty_port *port = &up->port.state->port;
	अचिन्हित अक्षर ch, flag;
	पूर्णांक max_count = 256;
	पूर्णांक saw_console_brk = 0;

	करो अणु
		ch = serial_inp(up, UART_RX);
		flag = TTY_NORMAL;
		up->port.icount.rx++;

		अगर (unlikely(*status & (UART_LSR_BI | UART_LSR_PE |
				       UART_LSR_FE | UART_LSR_OE))) अणु
			/*
			 * For statistics only
			 */
			अगर (*status & UART_LSR_BI) अणु
				*status &= ~(UART_LSR_FE | UART_LSR_PE);
				up->port.icount.brk++;
				अगर (up->port.cons != शून्य &&
				    up->port.line == up->port.cons->index)
					saw_console_brk = 1;
				/*
				 * We करो the SysRQ and SAK checking
				 * here because otherwise the अवरोध
				 * may get masked by ignore_status_mask
				 * or पढ़ो_status_mask.
				 */
				अगर (uart_handle_अवरोध(&up->port))
					जाओ ignore_अक्षर;
			पूर्ण अन्यथा अगर (*status & UART_LSR_PE)
				up->port.icount.parity++;
			अन्यथा अगर (*status & UART_LSR_FE)
				up->port.icount.frame++;
			अगर (*status & UART_LSR_OE)
				up->port.icount.overrun++;

			/*
			 * Mask off conditions which should be ingored.
			 */
			*status &= up->port.पढ़ो_status_mask;

			अगर (up->port.cons != शून्य &&
			    up->port.line == up->port.cons->index) अणु
				/* Recover the अवरोध flag from console xmit */
				*status |= up->lsr_अवरोध_flag;
				up->lsr_अवरोध_flag = 0;
			पूर्ण

			अगर (*status & UART_LSR_BI) अणु
				flag = TTY_BREAK;
			पूर्ण अन्यथा अगर (*status & UART_LSR_PE)
				flag = TTY_PARITY;
			अन्यथा अगर (*status & UART_LSR_FE)
				flag = TTY_FRAME;
		पूर्ण
		अगर (uart_handle_sysrq_अक्षर(&up->port, ch))
			जाओ ignore_अक्षर;
		अगर ((*status & up->port.ignore_status_mask) == 0)
			tty_insert_flip_अक्षर(port, ch, flag);
		अगर (*status & UART_LSR_OE)
			/*
			 * Overrun is special, since it's reported
			 * immediately, and करोesn't affect the current
			 * अक्षरacter.
			 */
			 tty_insert_flip_अक्षर(port, 0, TTY_OVERRUN);
	ignore_अक्षर:
		*status = serial_inp(up, UART_LSR);
	पूर्ण जबतक ((*status & UART_LSR_DR) && (max_count-- > 0));

	अगर (saw_console_brk)
		sun_करो_अवरोध();
पूर्ण

अटल व्योम transmit_अक्षरs(काष्ठा uart_sunsu_port *up)
अणु
	काष्ठा circ_buf *xmit = &up->port.state->xmit;
	पूर्णांक count;

	अगर (up->port.x_अक्षर) अणु
		serial_outp(up, UART_TX, up->port.x_अक्षर);
		up->port.icount.tx++;
		up->port.x_अक्षर = 0;
		वापस;
	पूर्ण
	अगर (uart_tx_stopped(&up->port)) अणु
		sunsu_stop_tx(&up->port);
		वापस;
	पूर्ण
	अगर (uart_circ_empty(xmit)) अणु
		__stop_tx(up);
		वापस;
	पूर्ण

	count = up->port.fअगरosize;
	करो अणु
		serial_out(up, UART_TX, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		up->port.icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण जबतक (--count > 0);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&up->port);

	अगर (uart_circ_empty(xmit))
		__stop_tx(up);
पूर्ण

अटल व्योम check_modem_status(काष्ठा uart_sunsu_port *up)
अणु
	पूर्णांक status;

	status = serial_in(up, UART_MSR);

	अगर ((status & UART_MSR_ANY_DELTA) == 0)
		वापस;

	अगर (status & UART_MSR_TERI)
		up->port.icount.rng++;
	अगर (status & UART_MSR_DDSR)
		up->port.icount.dsr++;
	अगर (status & UART_MSR_DDCD)
		uart_handle_dcd_change(&up->port, status & UART_MSR_DCD);
	अगर (status & UART_MSR_DCTS)
		uart_handle_cts_change(&up->port, status & UART_MSR_CTS);

	wake_up_पूर्णांकerruptible(&up->port.state->port.delta_msr_रुको);
पूर्ण

अटल irqवापस_t sunsu_serial_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_sunsu_port *up = dev_id;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर status;

	spin_lock_irqsave(&up->port.lock, flags);

	करो अणु
		status = serial_inp(up, UART_LSR);
		अगर (status & UART_LSR_DR)
			receive_अक्षरs(up, &status);
		check_modem_status(up);
		अगर (status & UART_LSR_THRE)
			transmit_अक्षरs(up);

		tty_flip_buffer_push(&up->port.state->port);

	पूर्ण जबतक (!(serial_in(up, UART_IIR) & UART_IIR_NO_INT));

	spin_unlock_irqrestore(&up->port.lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

/* Separate पूर्णांकerrupt handling path क्रम keyboard/mouse ports.  */

अटल व्योम
sunsu_change_speed(काष्ठा uart_port *port, अचिन्हित पूर्णांक cflag,
		   अचिन्हित पूर्णांक अगरlag, अचिन्हित पूर्णांक quot);

अटल व्योम sunsu_change_mouse_baud(काष्ठा uart_sunsu_port *up)
अणु
	अचिन्हित पूर्णांक cur_cflag = up->cflag;
	पूर्णांक quot, new_baud;

	up->cflag &= ~CBAUD;
	up->cflag |= suncore_mouse_baud_cflag_next(cur_cflag, &new_baud);

	quot = up->port.uartclk / (16 * new_baud);

	sunsu_change_speed(&up->port, up->cflag, 0, quot);
पूर्ण

अटल व्योम receive_kbd_ms_अक्षरs(काष्ठा uart_sunsu_port *up, पूर्णांक is_अवरोध)
अणु
	करो अणु
		अचिन्हित अक्षर ch = serial_inp(up, UART_RX);

		/* Stop-A is handled by drivers/अक्षर/keyboard.c now. */
		अगर (up->su_type == SU_PORT_KBD) अणु
#अगर_घोषित CONFIG_SERIO
			serio_पूर्णांकerrupt(&up->serio, ch, 0);
#पूर्ण_अगर
		पूर्ण अन्यथा अगर (up->su_type == SU_PORT_MS) अणु
			पूर्णांक ret = suncore_mouse_baud_detection(ch, is_अवरोध);

			चयन (ret) अणु
			हाल 2:
				sunsu_change_mouse_baud(up);
				fallthrough;
			हाल 1:
				अवरोध;

			हाल 0:
#अगर_घोषित CONFIG_SERIO
				serio_पूर्णांकerrupt(&up->serio, ch, 0);
#पूर्ण_अगर
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (serial_in(up, UART_LSR) & UART_LSR_DR);
पूर्ण

अटल irqवापस_t sunsu_kbd_ms_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_sunsu_port *up = dev_id;

	अगर (!(serial_in(up, UART_IIR) & UART_IIR_NO_INT)) अणु
		अचिन्हित अक्षर status = serial_inp(up, UART_LSR);

		अगर ((status & UART_LSR_DR) || (status & UART_LSR_BI))
			receive_kbd_ms_अक्षरs(up, (status & UART_LSR_BI) != 0);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक sunsu_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunsu_port *up =
		container_of(port, काष्ठा uart_sunsu_port, port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ret;

	spin_lock_irqsave(&up->port.lock, flags);
	ret = serial_in(up, UART_LSR) & UART_LSR_TEMT ? TIOCSER_TEMT : 0;
	spin_unlock_irqrestore(&up->port.lock, flags);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक sunsu_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunsu_port *up =
		container_of(port, काष्ठा uart_sunsu_port, port);
	अचिन्हित अक्षर status;
	अचिन्हित पूर्णांक ret;

	status = serial_in(up, UART_MSR);

	ret = 0;
	अगर (status & UART_MSR_DCD)
		ret |= TIOCM_CAR;
	अगर (status & UART_MSR_RI)
		ret |= TIOCM_RNG;
	अगर (status & UART_MSR_DSR)
		ret |= TIOCM_DSR;
	अगर (status & UART_MSR_CTS)
		ret |= TIOCM_CTS;
	वापस ret;
पूर्ण

अटल व्योम sunsu_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा uart_sunsu_port *up =
		container_of(port, काष्ठा uart_sunsu_port, port);
	अचिन्हित अक्षर mcr = 0;

	अगर (mctrl & TIOCM_RTS)
		mcr |= UART_MCR_RTS;
	अगर (mctrl & TIOCM_DTR)
		mcr |= UART_MCR_DTR;
	अगर (mctrl & TIOCM_OUT1)
		mcr |= UART_MCR_OUT1;
	अगर (mctrl & TIOCM_OUT2)
		mcr |= UART_MCR_OUT2;
	अगर (mctrl & TIOCM_LOOP)
		mcr |= UART_MCR_LOOP;

	serial_out(up, UART_MCR, mcr);
पूर्ण

अटल व्योम sunsu_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा uart_sunsu_port *up =
		container_of(port, काष्ठा uart_sunsu_port, port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&up->port.lock, flags);
	अगर (अवरोध_state == -1)
		up->lcr |= UART_LCR_SBC;
	अन्यथा
		up->lcr &= ~UART_LCR_SBC;
	serial_out(up, UART_LCR, up->lcr);
	spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

अटल पूर्णांक sunsu_startup(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunsu_port *up =
		container_of(port, काष्ठा uart_sunsu_port, port);
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	अगर (up->port.type == PORT_16C950) अणु
		/* Wake up and initialize UART */
		up->acr = 0;
		serial_outp(up, UART_LCR, 0xBF);
		serial_outp(up, UART_EFR, UART_EFR_ECB);
		serial_outp(up, UART_IER, 0);
		serial_outp(up, UART_LCR, 0);
		serial_icr_ग_लिखो(up, UART_CSR, 0); /* Reset the UART */
		serial_outp(up, UART_LCR, 0xBF);
		serial_outp(up, UART_EFR, UART_EFR_ECB);
		serial_outp(up, UART_LCR, 0);
	पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250_RSA
	/*
	 * If this is an RSA port, see अगर we can kick it up to the
	 * higher speed घड़ी.
	 */
	enable_rsa(up);
#पूर्ण_अगर

	/*
	 * Clear the FIFO buffers and disable them.
	 * (they will be reenabled in set_termios())
	 */
	अगर (uart_config[up->port.type].flags & UART_CLEAR_FIFO) अणु
		serial_outp(up, UART_FCR, UART_FCR_ENABLE_FIFO);
		serial_outp(up, UART_FCR, UART_FCR_ENABLE_FIFO |
				UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
		serial_outp(up, UART_FCR, 0);
	पूर्ण

	/*
	 * Clear the पूर्णांकerrupt रेजिस्टरs.
	 */
	(व्योम) serial_inp(up, UART_LSR);
	(व्योम) serial_inp(up, UART_RX);
	(व्योम) serial_inp(up, UART_IIR);
	(व्योम) serial_inp(up, UART_MSR);

	/*
	 * At this poपूर्णांक, there's no way the LSR could still be 0xff;
	 * अगर it is, then bail out, because there's likely no UART
	 * here.
	 */
	अगर (!(up->port.flags & UPF_BUGGY_UART) &&
	    (serial_inp(up, UART_LSR) == 0xff)) अणु
		prपूर्णांकk("ttyS%d: LSR safety check engaged!\n", up->port.line);
		वापस -ENODEV;
	पूर्ण

	अगर (up->su_type != SU_PORT_PORT) अणु
		retval = request_irq(up->port.irq, sunsu_kbd_ms_पूर्णांकerrupt,
				     IRQF_SHARED, su_typev[up->su_type], up);
	पूर्ण अन्यथा अणु
		retval = request_irq(up->port.irq, sunsu_serial_पूर्णांकerrupt,
				     IRQF_SHARED, su_typev[up->su_type], up);
	पूर्ण
	अगर (retval) अणु
		prपूर्णांकk("su: Cannot register IRQ %d\n", up->port.irq);
		वापस retval;
	पूर्ण

	/*
	 * Now, initialize the UART
	 */
	serial_outp(up, UART_LCR, UART_LCR_WLEN8);

	spin_lock_irqsave(&up->port.lock, flags);

	up->port.mctrl |= TIOCM_OUT2;

	sunsu_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);

	/*
	 * Finally, enable पूर्णांकerrupts.  Note: Modem status पूर्णांकerrupts
	 * are set via set_termios(), which will be occurring imminently
	 * anyway, so we करोn't enable them here.
	 */
	up->ier = UART_IER_RLSI | UART_IER_RDI;
	serial_outp(up, UART_IER, up->ier);

	अगर (up->port.flags & UPF_FOURPORT) अणु
		अचिन्हित पूर्णांक icp;
		/*
		 * Enable पूर्णांकerrupts on the AST Fourport board
		 */
		icp = (up->port.iobase & 0xfe0) | 0x01f;
		outb_p(0x80, icp);
		(व्योम) inb_p(icp);
	पूर्ण

	/*
	 * And clear the पूर्णांकerrupt रेजिस्टरs again क्रम luck.
	 */
	(व्योम) serial_inp(up, UART_LSR);
	(व्योम) serial_inp(up, UART_RX);
	(व्योम) serial_inp(up, UART_IIR);
	(व्योम) serial_inp(up, UART_MSR);

	वापस 0;
पूर्ण

अटल व्योम sunsu_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunsu_port *up =
		container_of(port, काष्ठा uart_sunsu_port, port);
	अचिन्हित दीर्घ flags;

	/*
	 * Disable पूर्णांकerrupts from this port
	 */
	up->ier = 0;
	serial_outp(up, UART_IER, 0);

	spin_lock_irqsave(&up->port.lock, flags);
	अगर (up->port.flags & UPF_FOURPORT) अणु
		/* reset पूर्णांकerrupts on the AST Fourport board */
		inb((up->port.iobase & 0xfe0) | 0x1f);
		up->port.mctrl |= TIOCM_OUT1;
	पूर्ण अन्यथा
		up->port.mctrl &= ~TIOCM_OUT2;

	sunsu_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);

	/*
	 * Disable अवरोध condition and FIFOs
	 */
	serial_out(up, UART_LCR, serial_inp(up, UART_LCR) & ~UART_LCR_SBC);
	serial_outp(up, UART_FCR, UART_FCR_ENABLE_FIFO |
				  UART_FCR_CLEAR_RCVR |
				  UART_FCR_CLEAR_XMIT);
	serial_outp(up, UART_FCR, 0);

#अगर_घोषित CONFIG_SERIAL_8250_RSA
	/*
	 * Reset the RSA board back to 115kbps compat mode.
	 */
	disable_rsa(up);
#पूर्ण_अगर

	/*
	 * Read data port to reset things.
	 */
	(व्योम) serial_in(up, UART_RX);

	मुक्त_irq(up->port.irq, up);
पूर्ण

अटल व्योम
sunsu_change_speed(काष्ठा uart_port *port, अचिन्हित पूर्णांक cflag,
		   अचिन्हित पूर्णांक अगरlag, अचिन्हित पूर्णांक quot)
अणु
	काष्ठा uart_sunsu_port *up =
		container_of(port, काष्ठा uart_sunsu_port, port);
	अचिन्हित अक्षर cval, fcr = 0;
	अचिन्हित दीर्घ flags;

	चयन (cflag & CSIZE) अणु
	हाल CS5:
		cval = 0x00;
		अवरोध;
	हाल CS6:
		cval = 0x01;
		अवरोध;
	हाल CS7:
		cval = 0x02;
		अवरोध;
	शेष:
	हाल CS8:
		cval = 0x03;
		अवरोध;
	पूर्ण

	अगर (cflag & CSTOPB)
		cval |= 0x04;
	अगर (cflag & PARENB)
		cval |= UART_LCR_PARITY;
	अगर (!(cflag & PARODD))
		cval |= UART_LCR_EPAR;
#अगर_घोषित CMSPAR
	अगर (cflag & CMSPAR)
		cval |= UART_LCR_SPAR;
#पूर्ण_अगर

	/*
	 * Work around a bug in the Oxक्रमd Semiconductor 952 rev B
	 * chip which causes it to seriously miscalculate baud rates
	 * when DLL is 0.
	 */
	अगर ((quot & 0xff) == 0 && up->port.type == PORT_16C950 &&
	    up->rev == 0x5201)
		quot ++;

	अगर (uart_config[up->port.type].flags & UART_USE_FIFO) अणु
		अगर ((up->port.uartclk / quot) < (2400 * 16))
			fcr = UART_FCR_ENABLE_FIFO | UART_FCR_TRIGGER_1;
#अगर_घोषित CONFIG_SERIAL_8250_RSA
		अन्यथा अगर (up->port.type == PORT_RSA)
			fcr = UART_FCR_ENABLE_FIFO | UART_FCR_TRIGGER_14;
#पूर्ण_अगर
		अन्यथा
			fcr = UART_FCR_ENABLE_FIFO | UART_FCR_TRIGGER_8;
	पूर्ण
	अगर (up->port.type == PORT_16750)
		fcr |= UART_FCR7_64BYTE;

	/*
	 * Ok, we're now changing the port state.  Do it with
	 * पूर्णांकerrupts disabled.
	 */
	spin_lock_irqsave(&up->port.lock, flags);

	/*
	 * Update the per-port समयout.
	 */
	uart_update_समयout(port, cflag, (port->uartclk / (16 * quot)));

	up->port.पढ़ो_status_mask = UART_LSR_OE | UART_LSR_THRE | UART_LSR_DR;
	अगर (अगरlag & INPCK)
		up->port.पढ़ो_status_mask |= UART_LSR_FE | UART_LSR_PE;
	अगर (अगरlag & (IGNBRK | BRKINT | PARMRK))
		up->port.पढ़ो_status_mask |= UART_LSR_BI;

	/*
	 * Characteres to ignore
	 */
	up->port.ignore_status_mask = 0;
	अगर (अगरlag & IGNPAR)
		up->port.ignore_status_mask |= UART_LSR_PE | UART_LSR_FE;
	अगर (अगरlag & IGNBRK) अणु
		up->port.ignore_status_mask |= UART_LSR_BI;
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (अगरlag & IGNPAR)
			up->port.ignore_status_mask |= UART_LSR_OE;
	पूर्ण

	/*
	 * ignore all अक्षरacters अगर CREAD is not set
	 */
	अगर ((cflag & CREAD) == 0)
		up->port.ignore_status_mask |= UART_LSR_DR;

	/*
	 * CTS flow control flag and modem status पूर्णांकerrupts
	 */
	up->ier &= ~UART_IER_MSI;
	अगर (UART_ENABLE_MS(&up->port, cflag))
		up->ier |= UART_IER_MSI;

	serial_out(up, UART_IER, up->ier);

	अगर (uart_config[up->port.type].flags & UART_STARTECH) अणु
		serial_outp(up, UART_LCR, 0xBF);
		serial_outp(up, UART_EFR, cflag & CRTSCTS ? UART_EFR_CTS :0);
	पूर्ण
	serial_outp(up, UART_LCR, cval | UART_LCR_DLAB);/* set DLAB */
	serial_outp(up, UART_DLL, quot & 0xff);		/* LS of भागisor */
	serial_outp(up, UART_DLM, quot >> 8);		/* MS of भागisor */
	अगर (up->port.type == PORT_16750)
		serial_outp(up, UART_FCR, fcr);		/* set fcr */
	serial_outp(up, UART_LCR, cval);		/* reset DLAB */
	up->lcr = cval;					/* Save LCR */
	अगर (up->port.type != PORT_16750) अणु
		अगर (fcr & UART_FCR_ENABLE_FIFO) अणु
			/* emulated UARTs (Lucent Venus 167x) need two steps */
			serial_outp(up, UART_FCR, UART_FCR_ENABLE_FIFO);
		पूर्ण
		serial_outp(up, UART_FCR, fcr);		/* set fcr */
	पूर्ण

	up->cflag = cflag;

	spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

अटल व्योम
sunsu_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		  काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक baud, quot;

	/*
	 * Ask the core to calculate the भागisor क्रम us.
	 */
	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk/16); 
	quot = uart_get_भागisor(port, baud);

	sunsu_change_speed(port, termios->c_cflag, termios->c_अगरlag, quot);
पूर्ण

अटल व्योम sunsu_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक sunsu_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम sunsu_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	काष्ठा uart_sunsu_port *up =
		container_of(port, काष्ठा uart_sunsu_port, port);

	अगर (flags & UART_CONFIG_TYPE) अणु
		/*
		 * We are supposed to call स्वतःconfig here, but this requires
		 * splitting all the OBP probing crap from the UART probing.
		 * We'll करो it when we समाप्त sunsu.c altogether.
		 */
		port->type = up->type_probed;	/* XXX */
	पूर्ण
पूर्ण

अटल पूर्णांक
sunsu_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	वापस -EINVAL;
पूर्ण

अटल स्थिर अक्षर *
sunsu_type(काष्ठा uart_port *port)
अणु
	पूर्णांक type = port->type;

	अगर (type >= ARRAY_SIZE(uart_config))
		type = 0;
	वापस uart_config[type].name;
पूर्ण

अटल स्थिर काष्ठा uart_ops sunsu_pops = अणु
	.tx_empty	= sunsu_tx_empty,
	.set_mctrl	= sunsu_set_mctrl,
	.get_mctrl	= sunsu_get_mctrl,
	.stop_tx	= sunsu_stop_tx,
	.start_tx	= sunsu_start_tx,
	.stop_rx	= sunsu_stop_rx,
	.enable_ms	= sunsu_enable_ms,
	.अवरोध_ctl	= sunsu_अवरोध_ctl,
	.startup	= sunsu_startup,
	.shutकरोwn	= sunsu_shutकरोwn,
	.set_termios	= sunsu_set_termios,
	.type		= sunsu_type,
	.release_port	= sunsu_release_port,
	.request_port	= sunsu_request_port,
	.config_port	= sunsu_config_port,
	.verअगरy_port	= sunsu_verअगरy_port,
पूर्ण;

#घोषणा UART_NR	4

अटल काष्ठा uart_sunsu_port sunsu_ports[UART_NR];
अटल पूर्णांक nr_inst; /* Number of alपढ़ोy रेजिस्टरed ports */

#अगर_घोषित CONFIG_SERIO

अटल DEFINE_SPINLOCK(sunsu_serio_lock);

अटल पूर्णांक sunsu_serio_ग_लिखो(काष्ठा serio *serio, अचिन्हित अक्षर ch)
अणु
	काष्ठा uart_sunsu_port *up = serio->port_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक lsr;

	spin_lock_irqsave(&sunsu_serio_lock, flags);

	करो अणु
		lsr = serial_in(up, UART_LSR);
	पूर्ण जबतक (!(lsr & UART_LSR_THRE));

	/* Send the अक्षरacter out. */
	serial_out(up, UART_TX, ch);

	spin_unlock_irqrestore(&sunsu_serio_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sunsu_serio_खोलो(काष्ठा serio *serio)
अणु
	काष्ठा uart_sunsu_port *up = serio->port_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&sunsu_serio_lock, flags);
	अगर (!up->serio_खोलो) अणु
		up->serio_खोलो = 1;
		ret = 0;
	पूर्ण अन्यथा
		ret = -EBUSY;
	spin_unlock_irqrestore(&sunsu_serio_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम sunsu_serio_बंद(काष्ठा serio *serio)
अणु
	काष्ठा uart_sunsu_port *up = serio->port_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sunsu_serio_lock, flags);
	up->serio_खोलो = 0;
	spin_unlock_irqrestore(&sunsu_serio_lock, flags);
पूर्ण

#पूर्ण_अगर /* CONFIG_SERIO */

अटल व्योम sunsu_स्वतःconfig(काष्ठा uart_sunsu_port *up)
अणु
	अचिन्हित अक्षर status1, status2, scratch, scratch2, scratch3;
	अचिन्हित अक्षर save_lcr, save_mcr;
	अचिन्हित दीर्घ flags;

	अगर (up->su_type == SU_PORT_NONE)
		वापस;

	up->type_probed = PORT_UNKNOWN;
	up->port.iotype = UPIO_MEM;

	spin_lock_irqsave(&up->port.lock, flags);

	अगर (!(up->port.flags & UPF_BUGGY_UART)) अणु
		/*
		 * Do a simple existence test first; अगर we fail this, there's
		 * no poपूर्णांक trying anything अन्यथा.
		 *
		 * 0x80 is used as a nonsense port to prevent against false
		 * positives due to ISA bus भग्न.  The assumption is that
		 * 0x80 is a non-existent port; which should be safe since
		 * include/यंत्र/पन.स also makes this assumption.
		 */
		scratch = serial_inp(up, UART_IER);
		serial_outp(up, UART_IER, 0);
#अगर_घोषित __i386__
		outb(0xff, 0x080);
#पूर्ण_अगर
		scratch2 = serial_inp(up, UART_IER);
		serial_outp(up, UART_IER, 0x0f);
#अगर_घोषित __i386__
		outb(0, 0x080);
#पूर्ण_अगर
		scratch3 = serial_inp(up, UART_IER);
		serial_outp(up, UART_IER, scratch);
		अगर (scratch2 != 0 || scratch3 != 0x0F)
			जाओ out;	/* We failed; there's nothing here */
	पूर्ण

	save_mcr = serial_in(up, UART_MCR);
	save_lcr = serial_in(up, UART_LCR);

	/* 
	 * Check to see अगर a UART is really there.  Certain broken
	 * पूर्णांकernal modems based on the Rockwell chipset fail this
	 * test, because they apparently करोn't implement the loopback
	 * test mode.  So this test is skipped on the COM 1 through
	 * COM 4 ports.  This *should* be safe, since no board
	 * manufacturer would be stupid enough to design a board
	 * that conflicts with COM 1-4 --- we hope!
	 */
	अगर (!(up->port.flags & UPF_SKIP_TEST)) अणु
		serial_outp(up, UART_MCR, UART_MCR_LOOP | 0x0A);
		status1 = serial_inp(up, UART_MSR) & 0xF0;
		serial_outp(up, UART_MCR, save_mcr);
		अगर (status1 != 0x90)
			जाओ out;	/* We failed loopback test */
	पूर्ण
	serial_outp(up, UART_LCR, 0xBF);	/* set up क्रम StarTech test */
	serial_outp(up, UART_EFR, 0);		/* EFR is the same as FCR */
	serial_outp(up, UART_LCR, 0);
	serial_outp(up, UART_FCR, UART_FCR_ENABLE_FIFO);
	scratch = serial_in(up, UART_IIR) >> 6;
	चयन (scratch) अणु
		हाल 0:
			up->port.type = PORT_16450;
			अवरोध;
		हाल 1:
			up->port.type = PORT_UNKNOWN;
			अवरोध;
		हाल 2:
			up->port.type = PORT_16550;
			अवरोध;
		हाल 3:
			up->port.type = PORT_16550A;
			अवरोध;
	पूर्ण
	अगर (up->port.type == PORT_16550A) अणु
		/* Check क्रम Startech UART's */
		serial_outp(up, UART_LCR, UART_LCR_DLAB);
		अगर (serial_in(up, UART_EFR) == 0) अणु
			up->port.type = PORT_16650;
		पूर्ण अन्यथा अणु
			serial_outp(up, UART_LCR, 0xBF);
			अगर (serial_in(up, UART_EFR) == 0)
				up->port.type = PORT_16650V2;
		पूर्ण
	पूर्ण
	अगर (up->port.type == PORT_16550A) अणु
		/* Check क्रम TI 16750 */
		serial_outp(up, UART_LCR, save_lcr | UART_LCR_DLAB);
		serial_outp(up, UART_FCR,
			    UART_FCR_ENABLE_FIFO | UART_FCR7_64BYTE);
		scratch = serial_in(up, UART_IIR) >> 5;
		अगर (scratch == 7) अणु
			/*
			 * If this is a 16750, and not a cheap UART
			 * clone, then it should only go पूर्णांकo 64 byte
			 * mode अगर the UART_FCR7_64BYTE bit was set
			 * जबतक UART_LCR_DLAB was latched.
			 */
 			serial_outp(up, UART_FCR, UART_FCR_ENABLE_FIFO);
			serial_outp(up, UART_LCR, 0);
			serial_outp(up, UART_FCR,
				    UART_FCR_ENABLE_FIFO | UART_FCR7_64BYTE);
			scratch = serial_in(up, UART_IIR) >> 5;
			अगर (scratch == 6)
				up->port.type = PORT_16750;
		पूर्ण
		serial_outp(up, UART_FCR, UART_FCR_ENABLE_FIFO);
	पूर्ण
	serial_outp(up, UART_LCR, save_lcr);
	अगर (up->port.type == PORT_16450) अणु
		scratch = serial_in(up, UART_SCR);
		serial_outp(up, UART_SCR, 0xa5);
		status1 = serial_in(up, UART_SCR);
		serial_outp(up, UART_SCR, 0x5a);
		status2 = serial_in(up, UART_SCR);
		serial_outp(up, UART_SCR, scratch);

		अगर ((status1 != 0xa5) || (status2 != 0x5a))
			up->port.type = PORT_8250;
	पूर्ण

	up->port.fअगरosize = uart_config[up->port.type].dfl_xmit_fअगरo_size;

	अगर (up->port.type == PORT_UNKNOWN)
		जाओ out;
	up->type_probed = up->port.type;	/* XXX */

	/*
	 * Reset the UART.
	 */
#अगर_घोषित CONFIG_SERIAL_8250_RSA
	अगर (up->port.type == PORT_RSA)
		serial_outp(up, UART_RSA_FRR, 0);
#पूर्ण_अगर
	serial_outp(up, UART_MCR, save_mcr);
	serial_outp(up, UART_FCR, (UART_FCR_ENABLE_FIFO |
				     UART_FCR_CLEAR_RCVR |
				     UART_FCR_CLEAR_XMIT));
	serial_outp(up, UART_FCR, 0);
	(व्योम)serial_in(up, UART_RX);
	serial_outp(up, UART_IER, 0);

out:
	spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

अटल काष्ठा uart_driver sunsu_reg = अणु
	.owner			= THIS_MODULE,
	.driver_name		= "sunsu",
	.dev_name		= "ttyS",
	.major			= TTY_MAJOR,
पूर्ण;

अटल पूर्णांक sunsu_kbd_ms_init(काष्ठा uart_sunsu_port *up)
अणु
	पूर्णांक quot, baud;
#अगर_घोषित CONFIG_SERIO
	काष्ठा serio *serio;
#पूर्ण_अगर

	अगर (up->su_type == SU_PORT_KBD) अणु
		up->cflag = B1200 | CS8 | CLOCAL | CREAD;
		baud = 1200;
	पूर्ण अन्यथा अणु
		up->cflag = B4800 | CS8 | CLOCAL | CREAD;
		baud = 4800;
	पूर्ण
	quot = up->port.uartclk / (16 * baud);

	sunsu_स्वतःconfig(up);
	अगर (up->port.type == PORT_UNKNOWN)
		वापस -ENODEV;

	prपूर्णांकk("%pOF: %s port at %llx, irq %u\n",
	       up->port.dev->of_node,
	       (up->su_type == SU_PORT_KBD) ? "Keyboard" : "Mouse",
	       (अचिन्हित दीर्घ दीर्घ) up->port.mapbase,
	       up->port.irq);

#अगर_घोषित CONFIG_SERIO
	serio = &up->serio;
	serio->port_data = up;

	serio->id.type = SERIO_RS232;
	अगर (up->su_type == SU_PORT_KBD) अणु
		serio->id.proto = SERIO_SUNKBD;
		strlcpy(serio->name, "sukbd", माप(serio->name));
	पूर्ण अन्यथा अणु
		serio->id.proto = SERIO_SUN;
		serio->id.extra = 1;
		strlcpy(serio->name, "sums", माप(serio->name));
	पूर्ण
	strlcpy(serio->phys,
		(!(up->port.line & 1) ? "su/serio0" : "su/serio1"),
		माप(serio->phys));

	serio->ग_लिखो = sunsu_serio_ग_लिखो;
	serio->खोलो = sunsu_serio_खोलो;
	serio->बंद = sunsu_serio_बंद;
	serio->dev.parent = up->port.dev;

	serio_रेजिस्टर_port(serio);
#पूर्ण_अगर

	sunsu_change_speed(&up->port, up->cflag, 0, quot);

	sunsu_startup(&up->port);
	वापस 0;
पूर्ण

/*
 * ------------------------------------------------------------
 * Serial console driver
 * ------------------------------------------------------------
 */

#अगर_घोषित CONFIG_SERIAL_SUNSU_CONSOLE

#घोषणा BOTH_EMPTY (UART_LSR_TEMT | UART_LSR_THRE)

/*
 *	Wait क्रम transmitter & holding रेजिस्टर to empty
 */
अटल व्योम रुको_क्रम_xmitr(काष्ठा uart_sunsu_port *up)
अणु
	अचिन्हित पूर्णांक status, पंचांगout = 10000;

	/* Wait up to 10ms क्रम the अक्षरacter(s) to be sent. */
	करो अणु
		status = serial_in(up, UART_LSR);

		अगर (status & UART_LSR_BI)
			up->lsr_अवरोध_flag = UART_LSR_BI;

		अगर (--पंचांगout == 0)
			अवरोध;
		udelay(1);
	पूर्ण जबतक ((status & BOTH_EMPTY) != BOTH_EMPTY);

	/* Wait up to 1s क्रम flow control अगर necessary */
	अगर (up->port.flags & UPF_CONS_FLOW) अणु
		पंचांगout = 1000000;
		जबतक (--पंचांगout &&
		       ((serial_in(up, UART_MSR) & UART_MSR_CTS) == 0))
			udelay(1);
	पूर्ण
पूर्ण

अटल व्योम sunsu_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा uart_sunsu_port *up =
		container_of(port, काष्ठा uart_sunsu_port, port);

	रुको_क्रम_xmitr(up);
	serial_out(up, UART_TX, ch);
पूर्ण

/*
 *	Prपूर्णांक a string to the serial port trying not to disturb
 *	any possible real use of the port...
 */
अटल व्योम sunsu_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_sunsu_port *up = &sunsu_ports[co->index];
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ier;
	पूर्णांक locked = 1;

	अगर (up->port.sysrq || oops_in_progress)
		locked = spin_trylock_irqsave(&up->port.lock, flags);
	अन्यथा
		spin_lock_irqsave(&up->port.lock, flags);

	/*
	 *	First save the UER then disable the पूर्णांकerrupts
	 */
	ier = serial_in(up, UART_IER);
	serial_out(up, UART_IER, 0);

	uart_console_ग_लिखो(&up->port, s, count, sunsu_console_अक्षर_दो);

	/*
	 *	Finally, रुको क्रम transmitter to become empty
	 *	and restore the IER
	 */
	रुको_क्रम_xmitr(up);
	serial_out(up, UART_IER, ier);

	अगर (locked)
		spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

/*
 *	Setup initial baud/bits/parity. We करो two things here:
 *	- स्थिरruct a cflag setting क्रम the first su_खोलो()
 *	- initialize the serial port
 *	Return non-zero अगर we didn't find a serial port.
 */
अटल पूर्णांक __init sunsu_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	अटल काष्ठा ktermios dummy;
	काष्ठा ktermios termios;
	काष्ठा uart_port *port;

	prपूर्णांकk("Console: ttyS%d (SU)\n",
	       (sunsu_reg.minor - 64) + co->index);

	अगर (co->index > nr_inst)
		वापस -ENODEV;
	port = &sunsu_ports[co->index].port;

	/*
	 * Temporary fix.
	 */
	spin_lock_init(&port->lock);

	/* Get firmware console settings.  */
	sunserial_console_termios(co, port->dev->of_node);

	स_रखो(&termios, 0, माप(काष्ठा ktermios));
	termios.c_cflag = co->cflag;
	port->mctrl |= TIOCM_DTR;
	port->ops->set_termios(port, &termios, &dummy);

	वापस 0;
पूर्ण

अटल काष्ठा console sunsu_console = अणु
	.name	=	"ttyS",
	.ग_लिखो	=	sunsu_console_ग_लिखो,
	.device	=	uart_console_device,
	.setup	=	sunsu_console_setup,
	.flags	=	CON_PRINTBUFFER,
	.index	=	-1,
	.data	=	&sunsu_reg,
पूर्ण;

/*
 *	Register console.
 */

अटल अंतरभूत काष्ठा console *SUNSU_CONSOLE(व्योम)
अणु
	वापस &sunsu_console;
पूर्ण
#अन्यथा
#घोषणा SUNSU_CONSOLE()			(शून्य)
#घोषणा sunsu_serial_console_init()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल क्रमागत su_type su_get_type(काष्ठा device_node *dp)
अणु
	काष्ठा device_node *ap = of_find_node_by_path("/aliases");
	क्रमागत su_type rc = SU_PORT_PORT;

	अगर (ap) अणु
		स्थिर अक्षर *keyb = of_get_property(ap, "keyboard", शून्य);
		स्थिर अक्षर *ms = of_get_property(ap, "mouse", शून्य);
		काष्ठा device_node *match;

		अगर (keyb) अणु
			match = of_find_node_by_path(keyb);

			/*
			 * The poपूर्णांकer is used as an identअगरier not
			 * as a poपूर्णांकer, we can drop the refcount on
			 * the of__node immediately after getting it.
			 */
			of_node_put(match);

			अगर (dp == match) अणु
				rc = SU_PORT_KBD;
				जाओ out;
			पूर्ण
		पूर्ण
		अगर (ms) अणु
			match = of_find_node_by_path(ms);

			of_node_put(match);

			अगर (dp == match) अणु
				rc = SU_PORT_MS;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	of_node_put(ap);
	वापस rc;
पूर्ण

अटल पूर्णांक su_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा uart_sunsu_port *up;
	काष्ठा resource *rp;
	क्रमागत su_type type;
	bool ignore_line;
	पूर्णांक err;

	type = su_get_type(dp);
	अगर (type == SU_PORT_PORT) अणु
		अगर (nr_inst >= UART_NR)
			वापस -EINVAL;
		up = &sunsu_ports[nr_inst];
	पूर्ण अन्यथा अणु
		up = kzalloc(माप(*up), GFP_KERNEL);
		अगर (!up)
			वापस -ENOMEM;
	पूर्ण

	up->port.line = nr_inst;

	spin_lock_init(&up->port.lock);

	up->su_type = type;

	rp = &op->resource[0];
	up->port.mapbase = rp->start;
	up->reg_size = resource_size(rp);
	up->port.membase = of_ioremap(rp, 0, up->reg_size, "su");
	अगर (!up->port.membase) अणु
		अगर (type != SU_PORT_PORT)
			kमुक्त(up);
		वापस -ENOMEM;
	पूर्ण

	up->port.irq = op->archdata.irqs[0];

	up->port.dev = &op->dev;

	up->port.type = PORT_UNKNOWN;
	up->port.uartclk = (SU_BASE_BAUD * 16);
	up->port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_SUNSU_CONSOLE);

	err = 0;
	अगर (up->su_type == SU_PORT_KBD || up->su_type == SU_PORT_MS) अणु
		err = sunsu_kbd_ms_init(up);
		अगर (err) अणु
			of_iounmap(&op->resource[0],
				   up->port.membase, up->reg_size);
			kमुक्त(up);
			वापस err;
		पूर्ण
		platक्रमm_set_drvdata(op, up);

		nr_inst++;

		वापस 0;
	पूर्ण

	up->port.flags |= UPF_BOOT_AUTOCONF;

	sunsu_स्वतःconfig(up);

	err = -ENODEV;
	अगर (up->port.type == PORT_UNKNOWN)
		जाओ out_unmap;

	up->port.ops = &sunsu_pops;

	ignore_line = false;
	अगर (of_node_name_eq(dp, "rsc-console") ||
	    of_node_name_eq(dp, "lom-console"))
		ignore_line = true;

	sunserial_console_match(SUNSU_CONSOLE(), dp,
				&sunsu_reg, up->port.line,
				ignore_line);
	err = uart_add_one_port(&sunsu_reg, &up->port);
	अगर (err)
		जाओ out_unmap;

	platक्रमm_set_drvdata(op, up);

	nr_inst++;

	वापस 0;

out_unmap:
	of_iounmap(&op->resource[0], up->port.membase, up->reg_size);
	kमुक्त(up);
	वापस err;
पूर्ण

अटल पूर्णांक su_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा uart_sunsu_port *up = platक्रमm_get_drvdata(op);
	bool kbdms = false;

	अगर (up->su_type == SU_PORT_MS ||
	    up->su_type == SU_PORT_KBD)
		kbdms = true;

	अगर (kbdms) अणु
#अगर_घोषित CONFIG_SERIO
		serio_unरेजिस्टर_port(&up->serio);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (up->port.type != PORT_UNKNOWN)
		uart_हटाओ_one_port(&sunsu_reg, &up->port);

	अगर (up->port.membase)
		of_iounmap(&op->resource[0], up->port.membase, up->reg_size);

	अगर (kbdms)
		kमुक्त(up);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id su_match[] = अणु
	अणु
		.name = "su",
	पूर्ण,
	अणु
		.name = "su_pnp",
	पूर्ण,
	अणु
		.name = "serial",
		.compatible = "su",
	पूर्ण,
	अणु
		.type = "serial",
		.compatible = "su",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, su_match);

अटल काष्ठा platक्रमm_driver su_driver = अणु
	.driver = अणु
		.name = "su",
		.of_match_table = su_match,
	पूर्ण,
	.probe		= su_probe,
	.हटाओ		= su_हटाओ,
पूर्ण;

अटल पूर्णांक __init sunsu_init(व्योम)
अणु
	काष्ठा device_node *dp;
	पूर्णांक err;
	पूर्णांक num_uart = 0;

	क्रम_each_node_by_name(dp, "su") अणु
		अगर (su_get_type(dp) == SU_PORT_PORT)
			num_uart++;
	पूर्ण
	क्रम_each_node_by_name(dp, "su_pnp") अणु
		अगर (su_get_type(dp) == SU_PORT_PORT)
			num_uart++;
	पूर्ण
	क्रम_each_node_by_name(dp, "serial") अणु
		अगर (of_device_is_compatible(dp, "su")) अणु
			अगर (su_get_type(dp) == SU_PORT_PORT)
				num_uart++;
		पूर्ण
	पूर्ण
	क्रम_each_node_by_type(dp, "serial") अणु
		अगर (of_device_is_compatible(dp, "su")) अणु
			अगर (su_get_type(dp) == SU_PORT_PORT)
				num_uart++;
		पूर्ण
	पूर्ण

	अगर (num_uart) अणु
		err = sunserial_रेजिस्टर_minors(&sunsu_reg, num_uart);
		अगर (err)
			वापस err;
	पूर्ण

	err = platक्रमm_driver_रेजिस्टर(&su_driver);
	अगर (err && num_uart)
		sunserial_unरेजिस्टर_minors(&sunsu_reg, num_uart);

	वापस err;
पूर्ण

अटल व्योम __निकास sunsu_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&su_driver);
	अगर (sunsu_reg.nr)
		sunserial_unरेजिस्टर_minors(&sunsu_reg, sunsu_reg.nr);
पूर्ण

module_init(sunsu_init);
module_निकास(sunsu_निकास);

MODULE_AUTHOR("Eddie C. Dost, Peter Zaitcev, and David S. Miller");
MODULE_DESCRIPTION("Sun SU serial port driver");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
