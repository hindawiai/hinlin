<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Driver core क्रम serial ports
 *
 *  Based on drivers/अक्षर/serial.c, by Linus Torvalds, Theoकरोre Ts'o.
 *
 *  Copyright 1999 ARM Limited
 *  Copyright (C) 2000-2001 Deep Blue Solutions Ltd.
 */
#समावेश <linux/module.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/device.h>
#समावेश <linux/serial.h> /* क्रम serial_state and serial_icounter_काष्ठा */
#समावेश <linux/serial_core.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/security.h>

#समावेश <linux/irq.h>
#समावेश <linux/uaccess.h>

/*
 * This is used to lock changes in serial line configuration.
 */
अटल DEFINE_MUTEX(port_mutex);

/*
 * lockdep: port->lock is initialized in two places, but we
 *          want only one lock-class:
 */
अटल काष्ठा lock_class_key port_lock_key;

#घोषणा HIGH_BITS_OFFSET	((माप(दीर्घ)-माप(पूर्णांक))*8)

अटल व्योम uart_change_speed(काष्ठा tty_काष्ठा *tty, काष्ठा uart_state *state,
					काष्ठा ktermios *old_termios);
अटल व्योम uart_रुको_until_sent(काष्ठा tty_काष्ठा *tty, पूर्णांक समयout);
अटल व्योम uart_change_pm(काष्ठा uart_state *state,
			   क्रमागत uart_pm_state pm_state);

अटल व्योम uart_port_shutकरोwn(काष्ठा tty_port *port);

अटल पूर्णांक uart_dcd_enabled(काष्ठा uart_port *uport)
अणु
	वापस !!(uport->status & UPSTAT_DCD_ENABLE);
पूर्ण

अटल अंतरभूत काष्ठा uart_port *uart_port_ref(काष्ठा uart_state *state)
अणु
	अगर (atomic_add_unless(&state->refcount, 1, 0))
		वापस state->uart_port;
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम uart_port_deref(काष्ठा uart_port *uport)
अणु
	अगर (atomic_dec_and_test(&uport->state->refcount))
		wake_up(&uport->state->हटाओ_रुको);
पूर्ण

#घोषणा uart_port_lock(state, flags)					\
	(अणु								\
		काष्ठा uart_port *__uport = uart_port_ref(state);	\
		अगर (__uport)						\
			spin_lock_irqsave(&__uport->lock, flags);	\
		__uport;						\
	पूर्ण)

#घोषणा uart_port_unlock(uport, flags)					\
	(अणु								\
		काष्ठा uart_port *__uport = uport;			\
		अगर (__uport) अणु						\
			spin_unlock_irqrestore(&__uport->lock, flags);	\
			uart_port_deref(__uport);			\
		पूर्ण							\
	पूर्ण)

अटल अंतरभूत काष्ठा uart_port *uart_port_check(काष्ठा uart_state *state)
अणु
	lockdep_निश्चित_held(&state->port.mutex);
	वापस state->uart_port;
पूर्ण

/*
 * This routine is used by the पूर्णांकerrupt handler to schedule processing in
 * the software पूर्णांकerrupt portion of the driver.
 */
व्योम uart_ग_लिखो_wakeup(काष्ठा uart_port *port)
अणु
	काष्ठा uart_state *state = port->state;
	/*
	 * This means you called this function _after_ the port was
	 * बंदd.  No cookie क्रम you.
	 */
	BUG_ON(!state);
	tty_port_tty_wakeup(&state->port);
पूर्ण

अटल व्योम uart_stop(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा uart_port *port;
	अचिन्हित दीर्घ flags;

	port = uart_port_lock(state, flags);
	अगर (port)
		port->ops->stop_tx(port);
	uart_port_unlock(port, flags);
पूर्ण

अटल व्योम __uart_start(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा uart_port *port = state->uart_port;

	अगर (port && !uart_tx_stopped(port))
		port->ops->start_tx(port);
पूर्ण

अटल व्योम uart_start(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा uart_port *port;
	अचिन्हित दीर्घ flags;

	port = uart_port_lock(state, flags);
	__uart_start(tty);
	uart_port_unlock(port, flags);
पूर्ण

अटल व्योम
uart_update_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक old;

	spin_lock_irqsave(&port->lock, flags);
	old = port->mctrl;
	port->mctrl = (old & ~clear) | set;
	अगर (old != port->mctrl)
		port->ops->set_mctrl(port, port->mctrl);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

#घोषणा uart_set_mctrl(port, set)	uart_update_mctrl(port, set, 0)
#घोषणा uart_clear_mctrl(port, clear)	uart_update_mctrl(port, 0, clear)

अटल व्योम uart_port_dtr_rts(काष्ठा uart_port *uport, पूर्णांक उठाओ)
अणु
	पूर्णांक rs485_on = uport->rs485_config &&
		(uport->rs485.flags & SER_RS485_ENABLED);
	पूर्णांक RTS_after_send = !!(uport->rs485.flags & SER_RS485_RTS_AFTER_SEND);

	अगर (उठाओ) अणु
		अगर (rs485_on && !RTS_after_send) अणु
			uart_set_mctrl(uport, TIOCM_DTR);
			uart_clear_mctrl(uport, TIOCM_RTS);
		पूर्ण अन्यथा अणु
			uart_set_mctrl(uport, TIOCM_DTR | TIOCM_RTS);
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक clear = TIOCM_DTR;

		clear |= (!rs485_on || !RTS_after_send) ? TIOCM_RTS : 0;
		uart_clear_mctrl(uport, clear);
	पूर्ण
पूर्ण

/*
 * Startup the port.  This will be called once per खोलो.  All calls
 * will be serialised by the per-port mutex.
 */
अटल पूर्णांक uart_port_startup(काष्ठा tty_काष्ठा *tty, काष्ठा uart_state *state,
		पूर्णांक init_hw)
अणु
	काष्ठा uart_port *uport = uart_port_check(state);
	अचिन्हित दीर्घ page;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक retval = 0;

	अगर (uport->type == PORT_UNKNOWN)
		वापस 1;

	/*
	 * Make sure the device is in D0 state.
	 */
	uart_change_pm(state, UART_PM_STATE_ON);

	/*
	 * Initialise and allocate the transmit and temporary
	 * buffer.
	 */
	page = get_zeroed_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	uart_port_lock(state, flags);
	अगर (!state->xmit.buf) अणु
		state->xmit.buf = (अचिन्हित अक्षर *) page;
		uart_circ_clear(&state->xmit);
		uart_port_unlock(uport, flags);
	पूर्ण अन्यथा अणु
		uart_port_unlock(uport, flags);
		/*
		 * Do not मुक्त() the page under the port lock, see
		 * uart_shutकरोwn().
		 */
		मुक्त_page(page);
	पूर्ण

	retval = uport->ops->startup(uport);
	अगर (retval == 0) अणु
		अगर (uart_console(uport) && uport->cons->cflag) अणु
			tty->termios.c_cflag = uport->cons->cflag;
			uport->cons->cflag = 0;
		पूर्ण
		/*
		 * Initialise the hardware port settings.
		 */
		uart_change_speed(tty, state, शून्य);

		/*
		 * Setup the RTS and DTR संकेतs once the
		 * port is खोलो and पढ़ोy to respond.
		 */
		अगर (init_hw && C_BAUD(tty))
			uart_port_dtr_rts(uport, 1);
	पूर्ण

	/*
	 * This is to allow setserial on this port. People may want to set
	 * port/irq/type and then reconfigure the port properly अगर it failed
	 * now.
	 */
	अगर (retval && capable(CAP_SYS_ADMIN))
		वापस 1;

	वापस retval;
पूर्ण

अटल पूर्णांक uart_startup(काष्ठा tty_काष्ठा *tty, काष्ठा uart_state *state,
		पूर्णांक init_hw)
अणु
	काष्ठा tty_port *port = &state->port;
	पूर्णांक retval;

	अगर (tty_port_initialized(port))
		वापस 0;

	retval = uart_port_startup(tty, state, init_hw);
	अगर (retval)
		set_bit(TTY_IO_ERROR, &tty->flags);

	वापस retval;
पूर्ण

/*
 * This routine will shutकरोwn a serial port; पूर्णांकerrupts are disabled, and
 * DTR is dropped अगर the hangup on बंद termio flag is on.  Calls to
 * uart_shutकरोwn are serialised by the per-port semaphore.
 *
 * uport == शून्य अगर uart_port has alपढ़ोy been हटाओd
 */
अटल व्योम uart_shutकरोwn(काष्ठा tty_काष्ठा *tty, काष्ठा uart_state *state)
अणु
	काष्ठा uart_port *uport = uart_port_check(state);
	काष्ठा tty_port *port = &state->port;
	अचिन्हित दीर्घ flags = 0;
	अक्षर *xmit_buf = शून्य;

	/*
	 * Set the TTY IO error marker
	 */
	अगर (tty)
		set_bit(TTY_IO_ERROR, &tty->flags);

	अगर (tty_port_initialized(port)) अणु
		tty_port_set_initialized(port, 0);

		/*
		 * Turn off DTR and RTS early.
		 */
		अगर (uport && uart_console(uport) && tty)
			uport->cons->cflag = tty->termios.c_cflag;

		अगर (!tty || C_HUPCL(tty))
			uart_port_dtr_rts(uport, 0);

		uart_port_shutकरोwn(port);
	पूर्ण

	/*
	 * It's possible क्रम shutकरोwn to be called after suspend अगर we get
	 * a DCD drop (hangup) at just the right समय.  Clear suspended bit so
	 * we करोn't try to resume a port that has been shutकरोwn.
	 */
	tty_port_set_suspended(port, 0);

	/*
	 * Do not मुक्त() the transmit buffer page under the port lock since
	 * this can create various circular locking scenarios. For instance,
	 * console driver may need to allocate/मुक्त a debug object, which
	 * can endup in prपूर्णांकk() recursion.
	 */
	uart_port_lock(state, flags);
	xmit_buf = state->xmit.buf;
	state->xmit.buf = शून्य;
	uart_port_unlock(uport, flags);

	अगर (xmit_buf)
		मुक्त_page((अचिन्हित दीर्घ)xmit_buf);
पूर्ण

/**
 *	uart_update_समयout - update per-port FIFO समयout.
 *	@port:  uart_port काष्ठाure describing the port
 *	@cflag: termios cflag value
 *	@baud:  speed of the port
 *
 *	Set the port FIFO समयout value.  The @cflag value should
 *	reflect the actual hardware settings.
 */
व्योम
uart_update_समयout(काष्ठा uart_port *port, अचिन्हित पूर्णांक cflag,
		    अचिन्हित पूर्णांक baud)
अणु
	अचिन्हित पूर्णांक bits;

	/* byte size and parity */
	चयन (cflag & CSIZE) अणु
	हाल CS5:
		bits = 7;
		अवरोध;
	हाल CS6:
		bits = 8;
		अवरोध;
	हाल CS7:
		bits = 9;
		अवरोध;
	शेष:
		bits = 10;
		अवरोध; /* CS8 */
	पूर्ण

	अगर (cflag & CSTOPB)
		bits++;
	अगर (cflag & PARENB)
		bits++;

	/*
	 * The total number of bits to be transmitted in the fअगरo.
	 */
	bits = bits * port->fअगरosize;

	/*
	 * Figure the समयout to send the above number of bits.
	 * Add .02 seconds of slop
	 */
	port->समयout = (HZ * bits) / baud + HZ/50;
पूर्ण

EXPORT_SYMBOL(uart_update_समयout);

/**
 *	uart_get_baud_rate - वापस baud rate क्रम a particular port
 *	@port: uart_port काष्ठाure describing the port in question.
 *	@termios: desired termios settings.
 *	@old: old termios (or शून्य)
 *	@min: minimum acceptable baud rate
 *	@max: maximum acceptable baud rate
 *
 *	Decode the termios काष्ठाure पूर्णांकo a numeric baud rate,
 *	taking account of the magic 38400 baud rate (with spd_*
 *	flags), and mapping the %B0 rate to 9600 baud.
 *
 *	If the new baud rate is invalid, try the old termios setting.
 *	If it's still invalid, we try 9600 baud.
 *
 *	Update the @termios काष्ठाure to reflect the baud rate
 *	we're actually going to be using. Don't करो this क्रम the हाल
 *	where B0 is requested ("hang up").
 */
अचिन्हित पूर्णांक
uart_get_baud_rate(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		   काष्ठा ktermios *old, अचिन्हित पूर्णांक min, अचिन्हित पूर्णांक max)
अणु
	अचिन्हित पूर्णांक try;
	अचिन्हित पूर्णांक baud;
	अचिन्हित पूर्णांक altbaud;
	पूर्णांक hung_up = 0;
	upf_t flags = port->flags & UPF_SPD_MASK;

	चयन (flags) अणु
	हाल UPF_SPD_HI:
		altbaud = 57600;
		अवरोध;
	हाल UPF_SPD_VHI:
		altbaud = 115200;
		अवरोध;
	हाल UPF_SPD_SHI:
		altbaud = 230400;
		अवरोध;
	हाल UPF_SPD_WARP:
		altbaud = 460800;
		अवरोध;
	शेष:
		altbaud = 38400;
		अवरोध;
	पूर्ण

	क्रम (try = 0; try < 2; try++) अणु
		baud = tty_termios_baud_rate(termios);

		/*
		 * The spd_hi, spd_vhi, spd_shi, spd_warp kludge...
		 * Die! Die! Die!
		 */
		अगर (try == 0 && baud == 38400)
			baud = altbaud;

		/*
		 * Special हाल: B0 rate.
		 */
		अगर (baud == 0) अणु
			hung_up = 1;
			baud = 9600;
		पूर्ण

		अगर (baud >= min && baud <= max)
			वापस baud;

		/*
		 * Oops, the quotient was zero.  Try again with
		 * the old baud rate अगर possible.
		 */
		termios->c_cflag &= ~CBAUD;
		अगर (old) अणु
			baud = tty_termios_baud_rate(old);
			अगर (!hung_up)
				tty_termios_encode_baud_rate(termios,
								baud, baud);
			old = शून्य;
			जारी;
		पूर्ण

		/*
		 * As a last resort, अगर the range cannot be met then clip to
		 * the nearest chip supported rate.
		 */
		अगर (!hung_up) अणु
			अगर (baud <= min)
				tty_termios_encode_baud_rate(termios,
							min + 1, min + 1);
			अन्यथा
				tty_termios_encode_baud_rate(termios,
							max - 1, max - 1);
		पूर्ण
	पूर्ण
	/* Should never happen */
	WARN_ON(1);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(uart_get_baud_rate);

/**
 *	uart_get_भागisor - वापस uart घड़ी भागisor
 *	@port: uart_port काष्ठाure describing the port.
 *	@baud: desired baud rate
 *
 *	Calculate the uart घड़ी भागisor क्रम the port.
 */
अचिन्हित पूर्णांक
uart_get_भागisor(काष्ठा uart_port *port, अचिन्हित पूर्णांक baud)
अणु
	अचिन्हित पूर्णांक quot;

	/*
	 * Old custom speed handling.
	 */
	अगर (baud == 38400 && (port->flags & UPF_SPD_MASK) == UPF_SPD_CUST)
		quot = port->custom_भागisor;
	अन्यथा
		quot = DIV_ROUND_CLOSEST(port->uartclk, 16 * baud);

	वापस quot;
पूर्ण

EXPORT_SYMBOL(uart_get_भागisor);

/* Caller holds port mutex */
अटल व्योम uart_change_speed(काष्ठा tty_काष्ठा *tty, काष्ठा uart_state *state,
					काष्ठा ktermios *old_termios)
अणु
	काष्ठा uart_port *uport = uart_port_check(state);
	काष्ठा ktermios *termios;
	पूर्णांक hw_stopped;

	/*
	 * If we have no tty, termios, or the port करोes not exist,
	 * then we can't set the parameters क्रम this port.
	 */
	अगर (!tty || uport->type == PORT_UNKNOWN)
		वापस;

	termios = &tty->termios;
	uport->ops->set_termios(uport, termios, old_termios);

	/*
	 * Set modem status enables based on termios cflag
	 */
	spin_lock_irq(&uport->lock);
	अगर (termios->c_cflag & CRTSCTS)
		uport->status |= UPSTAT_CTS_ENABLE;
	अन्यथा
		uport->status &= ~UPSTAT_CTS_ENABLE;

	अगर (termios->c_cflag & CLOCAL)
		uport->status &= ~UPSTAT_DCD_ENABLE;
	अन्यथा
		uport->status |= UPSTAT_DCD_ENABLE;

	/* reset sw-assisted CTS flow control based on (possibly) new mode */
	hw_stopped = uport->hw_stopped;
	uport->hw_stopped = uart_softcts_mode(uport) &&
				!(uport->ops->get_mctrl(uport) & TIOCM_CTS);
	अगर (uport->hw_stopped) अणु
		अगर (!hw_stopped)
			uport->ops->stop_tx(uport);
	पूर्ण अन्यथा अणु
		अगर (hw_stopped)
			__uart_start(tty);
	पूर्ण
	spin_unlock_irq(&uport->lock);
पूर्ण

अटल पूर्णांक uart_put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर c)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा uart_port *port;
	काष्ठा circ_buf *circ;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	circ = &state->xmit;
	port = uart_port_lock(state, flags);
	अगर (!circ->buf) अणु
		uart_port_unlock(port, flags);
		वापस 0;
	पूर्ण

	अगर (port && uart_circ_अक्षरs_मुक्त(circ) != 0) अणु
		circ->buf[circ->head] = c;
		circ->head = (circ->head + 1) & (UART_XMIT_SIZE - 1);
		ret = 1;
	पूर्ण
	uart_port_unlock(port, flags);
	वापस ret;
पूर्ण

अटल व्योम uart_flush_अक्षरs(काष्ठा tty_काष्ठा *tty)
अणु
	uart_start(tty);
पूर्ण

अटल पूर्णांक uart_ग_लिखो(काष्ठा tty_काष्ठा *tty,
					स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा uart_port *port;
	काष्ठा circ_buf *circ;
	अचिन्हित दीर्घ flags;
	पूर्णांक c, ret = 0;

	/*
	 * This means you called this function _after_ the port was
	 * बंदd.  No cookie क्रम you.
	 */
	अगर (!state) अणु
		WARN_ON(1);
		वापस -EL3HLT;
	पूर्ण

	port = uart_port_lock(state, flags);
	circ = &state->xmit;
	अगर (!circ->buf) अणु
		uart_port_unlock(port, flags);
		वापस 0;
	पूर्ण

	जबतक (port) अणु
		c = CIRC_SPACE_TO_END(circ->head, circ->tail, UART_XMIT_SIZE);
		अगर (count < c)
			c = count;
		अगर (c <= 0)
			अवरोध;
		स_नकल(circ->buf + circ->head, buf, c);
		circ->head = (circ->head + c) & (UART_XMIT_SIZE - 1);
		buf += c;
		count -= c;
		ret += c;
	पूर्ण

	__uart_start(tty);
	uart_port_unlock(port, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक uart_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा uart_port *port;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	port = uart_port_lock(state, flags);
	ret = uart_circ_अक्षरs_मुक्त(&state->xmit);
	uart_port_unlock(port, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक uart_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा uart_port *port;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	port = uart_port_lock(state, flags);
	ret = uart_circ_अक्षरs_pending(&state->xmit);
	uart_port_unlock(port, flags);
	वापस ret;
पूर्ण

अटल व्योम uart_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा uart_port *port;
	अचिन्हित दीर्घ flags;

	/*
	 * This means you called this function _after_ the port was
	 * बंदd.  No cookie क्रम you.
	 */
	अगर (!state) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	pr_debug("uart_flush_buffer(%d) called\n", tty->index);

	port = uart_port_lock(state, flags);
	अगर (!port)
		वापस;
	uart_circ_clear(&state->xmit);
	अगर (port->ops->flush_buffer)
		port->ops->flush_buffer(port);
	uart_port_unlock(port, flags);
	tty_port_tty_wakeup(&state->port);
पूर्ण

/*
 * This function is used to send a high-priority XON/XOFF अक्षरacter to
 * the device
 */
अटल व्योम uart_send_xअक्षर(काष्ठा tty_काष्ठा *tty, अक्षर ch)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा uart_port *port;
	अचिन्हित दीर्घ flags;

	port = uart_port_ref(state);
	अगर (!port)
		वापस;

	अगर (port->ops->send_xअक्षर)
		port->ops->send_xअक्षर(port, ch);
	अन्यथा अणु
		spin_lock_irqsave(&port->lock, flags);
		port->x_अक्षर = ch;
		अगर (ch)
			port->ops->start_tx(port);
		spin_unlock_irqrestore(&port->lock, flags);
	पूर्ण
	uart_port_deref(port);
पूर्ण

अटल व्योम uart_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	upstat_t mask = UPSTAT_SYNC_FIFO;
	काष्ठा uart_port *port;

	port = uart_port_ref(state);
	अगर (!port)
		वापस;

	अगर (I_IXOFF(tty))
		mask |= UPSTAT_AUTOXOFF;
	अगर (C_CRTSCTS(tty))
		mask |= UPSTAT_AUTORTS;

	अगर (port->status & mask) अणु
		port->ops->throttle(port);
		mask &= ~port->status;
	पूर्ण

	अगर (mask & UPSTAT_AUTORTS)
		uart_clear_mctrl(port, TIOCM_RTS);

	अगर (mask & UPSTAT_AUTOXOFF)
		uart_send_xअक्षर(tty, STOP_CHAR(tty));

	uart_port_deref(port);
पूर्ण

अटल व्योम uart_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	upstat_t mask = UPSTAT_SYNC_FIFO;
	काष्ठा uart_port *port;

	port = uart_port_ref(state);
	अगर (!port)
		वापस;

	अगर (I_IXOFF(tty))
		mask |= UPSTAT_AUTOXOFF;
	अगर (C_CRTSCTS(tty))
		mask |= UPSTAT_AUTORTS;

	अगर (port->status & mask) अणु
		port->ops->unthrottle(port);
		mask &= ~port->status;
	पूर्ण

	अगर (mask & UPSTAT_AUTORTS)
		uart_set_mctrl(port, TIOCM_RTS);

	अगर (mask & UPSTAT_AUTOXOFF)
		uart_send_xअक्षर(tty, START_CHAR(tty));

	uart_port_deref(port);
पूर्ण

अटल पूर्णांक uart_get_info(काष्ठा tty_port *port, काष्ठा serial_काष्ठा *retinfo)
अणु
	काष्ठा uart_state *state = container_of(port, काष्ठा uart_state, port);
	काष्ठा uart_port *uport;
	पूर्णांक ret = -ENODEV;

	/*
	 * Ensure the state we copy is consistent and no hardware changes
	 * occur as we go
	 */
	mutex_lock(&port->mutex);
	uport = uart_port_check(state);
	अगर (!uport)
		जाओ out;

	retinfo->type	    = uport->type;
	retinfo->line	    = uport->line;
	retinfo->port	    = uport->iobase;
	अगर (HIGH_BITS_OFFSET)
		retinfo->port_high = (दीर्घ) uport->iobase >> HIGH_BITS_OFFSET;
	retinfo->irq		    = uport->irq;
	retinfo->flags	    = (__क्रमce पूर्णांक)uport->flags;
	retinfo->xmit_fअगरo_size  = uport->fअगरosize;
	retinfo->baud_base	    = uport->uartclk / 16;
	retinfo->बंद_delay	    = jअगरfies_to_msecs(port->बंद_delay) / 10;
	retinfo->closing_रुको    = port->closing_रुको == ASYNC_CLOSING_WAIT_NONE ?
				ASYNC_CLOSING_WAIT_NONE :
				jअगरfies_to_msecs(port->closing_रुको) / 10;
	retinfo->custom_भागisor  = uport->custom_भागisor;
	retinfo->hub6	    = uport->hub6;
	retinfo->io_type         = uport->iotype;
	retinfo->iomem_reg_shअगरt = uport->regshअगरt;
	retinfo->iomem_base      = (व्योम *)(अचिन्हित दीर्घ)uport->mapbase;

	ret = 0;
out:
	mutex_unlock(&port->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक uart_get_info_user(काष्ठा tty_काष्ठा *tty,
			 काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा tty_port *port = &state->port;

	वापस uart_get_info(port, ss) < 0 ? -EIO : 0;
पूर्ण

अटल पूर्णांक uart_set_info(काष्ठा tty_काष्ठा *tty, काष्ठा tty_port *port,
			 काष्ठा uart_state *state,
			 काष्ठा serial_काष्ठा *new_info)
अणु
	काष्ठा uart_port *uport = uart_port_check(state);
	अचिन्हित दीर्घ new_port;
	अचिन्हित पूर्णांक change_irq, change_port, closing_रुको;
	अचिन्हित पूर्णांक old_custom_भागisor, बंद_delay;
	upf_t old_flags, new_flags;
	पूर्णांक retval = 0;

	अगर (!uport)
		वापस -EIO;

	new_port = new_info->port;
	अगर (HIGH_BITS_OFFSET)
		new_port += (अचिन्हित दीर्घ) new_info->port_high << HIGH_BITS_OFFSET;

	new_info->irq = irq_canonicalize(new_info->irq);
	बंद_delay = msecs_to_jअगरfies(new_info->बंद_delay * 10);
	closing_रुको = new_info->closing_रुको == ASYNC_CLOSING_WAIT_NONE ?
			ASYNC_CLOSING_WAIT_NONE :
			msecs_to_jअगरfies(new_info->closing_रुको * 10);


	change_irq  = !(uport->flags & UPF_FIXED_PORT)
		&& new_info->irq != uport->irq;

	/*
	 * Since changing the 'type' of the port changes its resource
	 * allocations, we should treat type changes the same as
	 * IO port changes.
	 */
	change_port = !(uport->flags & UPF_FIXED_PORT)
		&& (new_port != uport->iobase ||
		    (अचिन्हित दीर्घ)new_info->iomem_base != uport->mapbase ||
		    new_info->hub6 != uport->hub6 ||
		    new_info->io_type != uport->iotype ||
		    new_info->iomem_reg_shअगरt != uport->regshअगरt ||
		    new_info->type != uport->type);

	old_flags = uport->flags;
	new_flags = (__क्रमce upf_t)new_info->flags;
	old_custom_भागisor = uport->custom_भागisor;

	अगर (!capable(CAP_SYS_ADMIN)) अणु
		retval = -EPERM;
		अगर (change_irq || change_port ||
		    (new_info->baud_base != uport->uartclk / 16) ||
		    (बंद_delay != port->बंद_delay) ||
		    (closing_रुको != port->closing_रुको) ||
		    (new_info->xmit_fअगरo_size &&
		     new_info->xmit_fअगरo_size != uport->fअगरosize) ||
		    (((new_flags ^ old_flags) & ~UPF_USR_MASK) != 0))
			जाओ निकास;
		uport->flags = ((uport->flags & ~UPF_USR_MASK) |
			       (new_flags & UPF_USR_MASK));
		uport->custom_भागisor = new_info->custom_भागisor;
		जाओ check_and_निकास;
	पूर्ण

	अगर (change_irq || change_port) अणु
		retval = security_locked_करोwn(LOCKDOWN_TIOCSSERIAL);
		अगर (retval)
			जाओ निकास;
	पूर्ण

	/*
	 * Ask the low level driver to verअगरy the settings.
	 */
	अगर (uport->ops->verअगरy_port)
		retval = uport->ops->verअगरy_port(uport, new_info);

	अगर ((new_info->irq >= nr_irqs) || (new_info->irq < 0) ||
	    (new_info->baud_base < 9600))
		retval = -EINVAL;

	अगर (retval)
		जाओ निकास;

	अगर (change_port || change_irq) अणु
		retval = -EBUSY;

		/*
		 * Make sure that we are the sole user of this port.
		 */
		अगर (tty_port_users(port) > 1)
			जाओ निकास;

		/*
		 * We need to shutकरोwn the serial port at the old
		 * port/type/irq combination.
		 */
		uart_shutकरोwn(tty, state);
	पूर्ण

	अगर (change_port) अणु
		अचिन्हित दीर्घ old_iobase, old_mapbase;
		अचिन्हित पूर्णांक old_type, old_iotype, old_hub6, old_shअगरt;

		old_iobase = uport->iobase;
		old_mapbase = uport->mapbase;
		old_type = uport->type;
		old_hub6 = uport->hub6;
		old_iotype = uport->iotype;
		old_shअगरt = uport->regshअगरt;

		/*
		 * Free and release old regions
		 */
		अगर (old_type != PORT_UNKNOWN && uport->ops->release_port)
			uport->ops->release_port(uport);

		uport->iobase = new_port;
		uport->type = new_info->type;
		uport->hub6 = new_info->hub6;
		uport->iotype = new_info->io_type;
		uport->regshअगरt = new_info->iomem_reg_shअगरt;
		uport->mapbase = (अचिन्हित दीर्घ)new_info->iomem_base;

		/*
		 * Claim and map the new regions
		 */
		अगर (uport->type != PORT_UNKNOWN && uport->ops->request_port) अणु
			retval = uport->ops->request_port(uport);
		पूर्ण अन्यथा अणु
			/* Always success - Jean II */
			retval = 0;
		पूर्ण

		/*
		 * If we fail to request resources क्रम the
		 * new port, try to restore the old settings.
		 */
		अगर (retval) अणु
			uport->iobase = old_iobase;
			uport->type = old_type;
			uport->hub6 = old_hub6;
			uport->iotype = old_iotype;
			uport->regshअगरt = old_shअगरt;
			uport->mapbase = old_mapbase;

			अगर (old_type != PORT_UNKNOWN) अणु
				retval = uport->ops->request_port(uport);
				/*
				 * If we failed to restore the old settings,
				 * we fail like this.
				 */
				अगर (retval)
					uport->type = PORT_UNKNOWN;

				/*
				 * We failed anyway.
				 */
				retval = -EBUSY;
			पूर्ण

			/* Added to वापस the correct error -Ram Gupta */
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (change_irq)
		uport->irq      = new_info->irq;
	अगर (!(uport->flags & UPF_FIXED_PORT))
		uport->uartclk  = new_info->baud_base * 16;
	uport->flags            = (uport->flags & ~UPF_CHANGE_MASK) |
				 (new_flags & UPF_CHANGE_MASK);
	uport->custom_भागisor   = new_info->custom_भागisor;
	port->बंद_delay     = बंद_delay;
	port->closing_रुको    = closing_रुको;
	अगर (new_info->xmit_fअगरo_size)
		uport->fअगरosize = new_info->xmit_fअगरo_size;

 check_and_निकास:
	retval = 0;
	अगर (uport->type == PORT_UNKNOWN)
		जाओ निकास;
	अगर (tty_port_initialized(port)) अणु
		अगर (((old_flags ^ uport->flags) & UPF_SPD_MASK) ||
		    old_custom_भागisor != uport->custom_भागisor) अणु
			/*
			 * If they're setting up a custom भागisor or speed,
			 * instead of clearing it, then bitch about it.
			 */
			अगर (uport->flags & UPF_SPD_MASK) अणु
				dev_notice_ratelimited(uport->dev,
				       "%s sets custom speed on %s. This is deprecated.\n",
				      current->comm,
				      tty_name(port->tty));
			पूर्ण
			uart_change_speed(tty, state, शून्य);
		पूर्ण
	पूर्ण अन्यथा अणु
		retval = uart_startup(tty, state, 1);
		अगर (retval == 0)
			tty_port_set_initialized(port, true);
		अगर (retval > 0)
			retval = 0;
	पूर्ण
 निकास:
	वापस retval;
पूर्ण

अटल पूर्णांक uart_set_info_user(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा tty_port *port = &state->port;
	पूर्णांक retval;

	करोwn_ग_लिखो(&tty->termios_rwsem);
	/*
	 * This semaphore protects port->count.  It is also
	 * very useful to prevent खोलोs.  Also, take the
	 * port configuration semaphore to make sure that a
	 * module insertion/removal करोesn't change anything
	 * under us.
	 */
	mutex_lock(&port->mutex);
	retval = uart_set_info(tty, port, state, ss);
	mutex_unlock(&port->mutex);
	up_ग_लिखो(&tty->termios_rwsem);
	वापस retval;
पूर्ण

/**
 *	uart_get_lsr_info	-	get line status रेजिस्टर info
 *	@tty: tty associated with the UART
 *	@state: UART being queried
 *	@value: वापसed modem value
 */
अटल पूर्णांक uart_get_lsr_info(काष्ठा tty_काष्ठा *tty,
			काष्ठा uart_state *state, अचिन्हित पूर्णांक __user *value)
अणु
	काष्ठा uart_port *uport = uart_port_check(state);
	अचिन्हित पूर्णांक result;

	result = uport->ops->tx_empty(uport);

	/*
	 * If we're about to load something पूर्णांकo the transmit
	 * रेजिस्टर, we'll pretend the transmitter isn't empty to
	 * aव्योम a race condition (depending on when the transmit
	 * पूर्णांकerrupt happens).
	 */
	अगर (uport->x_अक्षर ||
	    ((uart_circ_अक्षरs_pending(&state->xmit) > 0) &&
	     !uart_tx_stopped(uport)))
		result &= ~TIOCSER_TEMT;

	वापस put_user(result, value);
पूर्ण

अटल पूर्णांक uart_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा tty_port *port = &state->port;
	काष्ठा uart_port *uport;
	पूर्णांक result = -EIO;

	mutex_lock(&port->mutex);
	uport = uart_port_check(state);
	अगर (!uport)
		जाओ out;

	अगर (!tty_io_error(tty)) अणु
		result = uport->mctrl;
		spin_lock_irq(&uport->lock);
		result |= uport->ops->get_mctrl(uport);
		spin_unlock_irq(&uport->lock);
	पूर्ण
out:
	mutex_unlock(&port->mutex);
	वापस result;
पूर्ण

अटल पूर्णांक
uart_tiocmset(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा tty_port *port = &state->port;
	काष्ठा uart_port *uport;
	पूर्णांक ret = -EIO;

	mutex_lock(&port->mutex);
	uport = uart_port_check(state);
	अगर (!uport)
		जाओ out;

	अगर (!tty_io_error(tty)) अणु
		uart_update_mctrl(uport, set, clear);
		ret = 0;
	पूर्ण
out:
	mutex_unlock(&port->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक uart_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा tty_port *port = &state->port;
	काष्ठा uart_port *uport;
	पूर्णांक ret = -EIO;

	mutex_lock(&port->mutex);
	uport = uart_port_check(state);
	अगर (!uport)
		जाओ out;

	अगर (uport->type != PORT_UNKNOWN && uport->ops->अवरोध_ctl)
		uport->ops->अवरोध_ctl(uport, अवरोध_state);
	ret = 0;
out:
	mutex_unlock(&port->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक uart_करो_स्वतःconfig(काष्ठा tty_काष्ठा *tty, काष्ठा uart_state *state)
अणु
	काष्ठा tty_port *port = &state->port;
	काष्ठा uart_port *uport;
	पूर्णांक flags, ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	/*
	 * Take the per-port semaphore.  This prevents count from
	 * changing, and hence any extra खोलोs of the port जबतक
	 * we're स्वतः-configuring.
	 */
	अगर (mutex_lock_पूर्णांकerruptible(&port->mutex))
		वापस -ERESTARTSYS;

	uport = uart_port_check(state);
	अगर (!uport) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	ret = -EBUSY;
	अगर (tty_port_users(port) == 1) अणु
		uart_shutकरोwn(tty, state);

		/*
		 * If we alपढ़ोy have a port type configured,
		 * we must release its resources.
		 */
		अगर (uport->type != PORT_UNKNOWN && uport->ops->release_port)
			uport->ops->release_port(uport);

		flags = UART_CONFIG_TYPE;
		अगर (uport->flags & UPF_AUTO_IRQ)
			flags |= UART_CONFIG_IRQ;

		/*
		 * This will claim the ports resources अगर
		 * a port is found.
		 */
		uport->ops->config_port(uport, flags);

		ret = uart_startup(tty, state, 1);
		अगर (ret == 0)
			tty_port_set_initialized(port, true);
		अगर (ret > 0)
			ret = 0;
	पूर्ण
out:
	mutex_unlock(&port->mutex);
	वापस ret;
पूर्ण

अटल व्योम uart_enable_ms(काष्ठा uart_port *uport)
अणु
	/*
	 * Force modem status पूर्णांकerrupts on
	 */
	अगर (uport->ops->enable_ms)
		uport->ops->enable_ms(uport);
पूर्ण

/*
 * Wait क्रम any of the 4 modem inमाला_दो (DCD,RI,DSR,CTS) to change
 * - mask passed in arg क्रम lines of पूर्णांकerest
 *   (use |'ed TIOCM_RNG/DSR/CD/CTS क्रम masking)
 * Caller should use TIOCGICOUNT to see which one it was
 *
 * FIXME: This wants extracting पूर्णांकo a common all driver implementation
 * of TIOCMWAIT using tty_port.
 */
अटल पूर्णांक uart_रुको_modem_status(काष्ठा uart_state *state, अचिन्हित दीर्घ arg)
अणु
	काष्ठा uart_port *uport;
	काष्ठा tty_port *port = &state->port;
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा uart_icount cprev, cnow;
	पूर्णांक ret;

	/*
	 * note the counters on entry
	 */
	uport = uart_port_ref(state);
	अगर (!uport)
		वापस -EIO;
	spin_lock_irq(&uport->lock);
	स_नकल(&cprev, &uport->icount, माप(काष्ठा uart_icount));
	uart_enable_ms(uport);
	spin_unlock_irq(&uport->lock);

	add_रुको_queue(&port->delta_msr_रुको, &रुको);
	क्रम (;;) अणु
		spin_lock_irq(&uport->lock);
		स_नकल(&cnow, &uport->icount, माप(काष्ठा uart_icount));
		spin_unlock_irq(&uport->lock);

		set_current_state(TASK_INTERRUPTIBLE);

		अगर (((arg & TIOCM_RNG) && (cnow.rng != cprev.rng)) ||
		    ((arg & TIOCM_DSR) && (cnow.dsr != cprev.dsr)) ||
		    ((arg & TIOCM_CD)  && (cnow.dcd != cprev.dcd)) ||
		    ((arg & TIOCM_CTS) && (cnow.cts != cprev.cts))) अणु
			ret = 0;
			अवरोध;
		पूर्ण

		schedule();

		/* see अगर a संकेत did it */
		अगर (संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		cprev = cnow;
	पूर्ण
	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&port->delta_msr_रुको, &रुको);
	uart_port_deref(uport);

	वापस ret;
पूर्ण

/*
 * Get counter of input serial line पूर्णांकerrupts (DCD,RI,DSR,CTS)
 * Return: ग_लिखो counters to the user passed counter काष्ठा
 * NB: both 1->0 and 0->1 transitions are counted except क्रम
 *     RI where only 0->1 is counted.
 */
अटल पूर्णांक uart_get_icount(काष्ठा tty_काष्ठा *tty,
			  काष्ठा serial_icounter_काष्ठा *icount)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा uart_icount cnow;
	काष्ठा uart_port *uport;

	uport = uart_port_ref(state);
	अगर (!uport)
		वापस -EIO;
	spin_lock_irq(&uport->lock);
	स_नकल(&cnow, &uport->icount, माप(काष्ठा uart_icount));
	spin_unlock_irq(&uport->lock);
	uart_port_deref(uport);

	icount->cts         = cnow.cts;
	icount->dsr         = cnow.dsr;
	icount->rng         = cnow.rng;
	icount->dcd         = cnow.dcd;
	icount->rx          = cnow.rx;
	icount->tx          = cnow.tx;
	icount->frame       = cnow.frame;
	icount->overrun     = cnow.overrun;
	icount->parity      = cnow.parity;
	icount->brk         = cnow.brk;
	icount->buf_overrun = cnow.buf_overrun;

	वापस 0;
पूर्ण

अटल पूर्णांक uart_get_rs485_config(काष्ठा uart_port *port,
			 काष्ठा serial_rs485 __user *rs485)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा serial_rs485 aux;

	spin_lock_irqsave(&port->lock, flags);
	aux = port->rs485;
	spin_unlock_irqrestore(&port->lock, flags);

	अगर (copy_to_user(rs485, &aux, माप(aux)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक uart_set_rs485_config(काष्ठा uart_port *port,
			 काष्ठा serial_rs485 __user *rs485_user)
अणु
	काष्ठा serial_rs485 rs485;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (!port->rs485_config)
		वापस -ENOTTY;

	अगर (copy_from_user(&rs485, rs485_user, माप(*rs485_user)))
		वापस -EFAULT;

	spin_lock_irqsave(&port->lock, flags);
	ret = port->rs485_config(port, &rs485);
	spin_unlock_irqrestore(&port->lock, flags);
	अगर (ret)
		वापस ret;

	अगर (copy_to_user(rs485_user, &port->rs485, माप(port->rs485)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक uart_get_iso7816_config(काष्ठा uart_port *port,
				   काष्ठा serial_iso7816 __user *iso7816)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा serial_iso7816 aux;

	अगर (!port->iso7816_config)
		वापस -ENOTTY;

	spin_lock_irqsave(&port->lock, flags);
	aux = port->iso7816;
	spin_unlock_irqrestore(&port->lock, flags);

	अगर (copy_to_user(iso7816, &aux, माप(aux)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक uart_set_iso7816_config(काष्ठा uart_port *port,
				   काष्ठा serial_iso7816 __user *iso7816_user)
अणु
	काष्ठा serial_iso7816 iso7816;
	पूर्णांक i, ret;
	अचिन्हित दीर्घ flags;

	अगर (!port->iso7816_config)
		वापस -ENOTTY;

	अगर (copy_from_user(&iso7816, iso7816_user, माप(*iso7816_user)))
		वापस -EFAULT;

	/*
	 * There are 5 words reserved क्रम future use. Check that userspace
	 * करोesn't put stuff in there to prevent अवरोधages in the future.
	 */
	क्रम (i = 0; i < 5; i++)
		अगर (iso7816.reserved[i])
			वापस -EINVAL;

	spin_lock_irqsave(&port->lock, flags);
	ret = port->iso7816_config(port, &iso7816);
	spin_unlock_irqrestore(&port->lock, flags);
	अगर (ret)
		वापस ret;

	अगर (copy_to_user(iso7816_user, &port->iso7816, माप(port->iso7816)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * Called via sys_ioctl.  We can use spin_lock_irq() here.
 */
अटल पूर्णांक
uart_ioctl(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा tty_port *port = &state->port;
	काष्ठा uart_port *uport;
	व्योम __user *uarg = (व्योम __user *)arg;
	पूर्णांक ret = -ENOIOCTLCMD;


	/*
	 * These ioctls करोn't rely on the hardware to be present.
	 */
	चयन (cmd) अणु
	हाल TIOCSERCONFIG:
		करोwn_ग_लिखो(&tty->termios_rwsem);
		ret = uart_करो_स्वतःconfig(tty, state);
		up_ग_लिखो(&tty->termios_rwsem);
		अवरोध;
	पूर्ण

	अगर (ret != -ENOIOCTLCMD)
		जाओ out;

	अगर (tty_io_error(tty)) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	/*
	 * The following should only be used when hardware is present.
	 */
	चयन (cmd) अणु
	हाल TIOCMIWAIT:
		ret = uart_रुको_modem_status(state, arg);
		अवरोध;
	पूर्ण

	अगर (ret != -ENOIOCTLCMD)
		जाओ out;

	mutex_lock(&port->mutex);
	uport = uart_port_check(state);

	अगर (!uport || tty_io_error(tty)) अणु
		ret = -EIO;
		जाओ out_up;
	पूर्ण

	/*
	 * All these rely on hardware being present and need to be
	 * रक्षित against the tty being hung up.
	 */

	चयन (cmd) अणु
	हाल TIOCSERGETLSR: /* Get line status रेजिस्टर */
		ret = uart_get_lsr_info(tty, state, uarg);
		अवरोध;

	हाल TIOCGRS485:
		ret = uart_get_rs485_config(uport, uarg);
		अवरोध;

	हाल TIOCSRS485:
		ret = uart_set_rs485_config(uport, uarg);
		अवरोध;

	हाल TIOCSISO7816:
		ret = uart_set_iso7816_config(state->uart_port, uarg);
		अवरोध;

	हाल TIOCGISO7816:
		ret = uart_get_iso7816_config(state->uart_port, uarg);
		अवरोध;
	शेष:
		अगर (uport->ops->ioctl)
			ret = uport->ops->ioctl(uport, cmd, arg);
		अवरोध;
	पूर्ण
out_up:
	mutex_unlock(&port->mutex);
out:
	वापस ret;
पूर्ण

अटल व्योम uart_set_ldisc(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा uart_port *uport;
	काष्ठा tty_port *port = &state->port;

	अगर (!tty_port_initialized(port))
		वापस;

	mutex_lock(&state->port.mutex);
	uport = uart_port_check(state);
	अगर (uport && uport->ops->set_ldisc)
		uport->ops->set_ldisc(uport, &tty->termios);
	mutex_unlock(&state->port.mutex);
पूर्ण

अटल व्योम uart_set_termios(काष्ठा tty_काष्ठा *tty,
						काष्ठा ktermios *old_termios)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा uart_port *uport;
	अचिन्हित पूर्णांक cflag = tty->termios.c_cflag;
	अचिन्हित पूर्णांक अगरlag_mask = IGNBRK|BRKINT|IGNPAR|PARMRK|INPCK;
	bool sw_changed = false;

	mutex_lock(&state->port.mutex);
	uport = uart_port_check(state);
	अगर (!uport)
		जाओ out;

	/*
	 * Drivers करोing software flow control also need to know
	 * about changes to these input settings.
	 */
	अगर (uport->flags & UPF_SOFT_FLOW) अणु
		अगरlag_mask |= IXANY|IXON|IXOFF;
		sw_changed =
		   tty->termios.c_cc[VSTART] != old_termios->c_cc[VSTART] ||
		   tty->termios.c_cc[VSTOP] != old_termios->c_cc[VSTOP];
	पूर्ण

	/*
	 * These are the bits that are used to setup various
	 * flags in the low level driver. We can ignore the Bfoo
	 * bits in c_cflag; c_[io]speed will always be set
	 * appropriately by set_termios() in tty_ioctl.c
	 */
	अगर ((cflag ^ old_termios->c_cflag) == 0 &&
	    tty->termios.c_ospeed == old_termios->c_ospeed &&
	    tty->termios.c_ispeed == old_termios->c_ispeed &&
	    ((tty->termios.c_अगरlag ^ old_termios->c_अगरlag) & अगरlag_mask) == 0 &&
	    !sw_changed) अणु
		जाओ out;
	पूर्ण

	uart_change_speed(tty, state, old_termios);
	/* reload cflag from termios; port driver may have overridden flags */
	cflag = tty->termios.c_cflag;

	/* Handle transition to B0 status */
	अगर ((old_termios->c_cflag & CBAUD) && !(cflag & CBAUD))
		uart_clear_mctrl(uport, TIOCM_RTS | TIOCM_DTR);
	/* Handle transition away from B0 status */
	अन्यथा अगर (!(old_termios->c_cflag & CBAUD) && (cflag & CBAUD)) अणु
		अचिन्हित पूर्णांक mask = TIOCM_DTR;

		अगर (!(cflag & CRTSCTS) || !tty_throttled(tty))
			mask |= TIOCM_RTS;
		uart_set_mctrl(uport, mask);
	पूर्ण
out:
	mutex_unlock(&state->port.mutex);
पूर्ण

/*
 * Calls to uart_बंद() are serialised via the tty_lock in
 *   drivers/tty/tty_io.c:tty_release()
 *   drivers/tty/tty_io.c:करो_tty_hangup()
 */
अटल व्योम uart_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा uart_state *state = tty->driver_data;

	अगर (!state) अणु
		काष्ठा uart_driver *drv = tty->driver->driver_state;
		काष्ठा tty_port *port;

		state = drv->state + tty->index;
		port = &state->port;
		spin_lock_irq(&port->lock);
		--port->count;
		spin_unlock_irq(&port->lock);
		वापस;
	पूर्ण

	pr_debug("uart_close(%d) called\n", tty->index);

	tty_port_बंद(tty->port, tty, filp);
पूर्ण

अटल व्योम uart_tty_port_shutकरोwn(काष्ठा tty_port *port)
अणु
	काष्ठा uart_state *state = container_of(port, काष्ठा uart_state, port);
	काष्ठा uart_port *uport = uart_port_check(state);

	/*
	 * At this poपूर्णांक, we stop accepting input.  To करो this, we
	 * disable the receive line status पूर्णांकerrupts.
	 */
	अगर (WARN(!uport, "detached port still initialized!\n"))
		वापस;

	spin_lock_irq(&uport->lock);
	uport->ops->stop_rx(uport);
	spin_unlock_irq(&uport->lock);

	uart_port_shutकरोwn(port);

	/*
	 * It's possible क्रम shutकरोwn to be called after suspend अगर we get
	 * a DCD drop (hangup) at just the right समय.  Clear suspended bit so
	 * we करोn't try to resume a port that has been shutकरोwn.
	 */
	tty_port_set_suspended(port, 0);

	uart_change_pm(state, UART_PM_STATE_OFF);

पूर्ण

अटल व्योम uart_रुको_until_sent(काष्ठा tty_काष्ठा *tty, पूर्णांक समयout)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा uart_port *port;
	अचिन्हित दीर्घ अक्षर_समय, expire;

	port = uart_port_ref(state);
	अगर (!port)
		वापस;

	अगर (port->type == PORT_UNKNOWN || port->fअगरosize == 0) अणु
		uart_port_deref(port);
		वापस;
	पूर्ण

	/*
	 * Set the check पूर्णांकerval to be 1/5 of the estimated समय to
	 * send a single अक्षरacter, and make it at least 1.  The check
	 * पूर्णांकerval should also be less than the समयout.
	 *
	 * Note: we have to use pretty tight timings here to satisfy
	 * the NIST-PCTS.
	 */
	अक्षर_समय = (port->समयout - HZ/50) / port->fअगरosize;
	अक्षर_समय = अक्षर_समय / 5;
	अगर (अक्षर_समय == 0)
		अक्षर_समय = 1;
	अगर (समयout && समयout < अक्षर_समय)
		अक्षर_समय = समयout;

	/*
	 * If the transmitter hasn't cleared in twice the approximate
	 * amount of समय to send the entire FIFO, it probably won't
	 * ever clear.  This assumes the UART isn't करोing flow
	 * control, which is currently the हाल.  Hence, अगर it ever
	 * takes दीर्घer than port->समयout, this is probably due to a
	 * UART bug of some kind.  So, we clamp the समयout parameter at
	 * 2*port->समयout.
	 */
	अगर (समयout == 0 || समयout > 2 * port->समयout)
		समयout = 2 * port->समयout;

	expire = jअगरfies + समयout;

	pr_debug("uart_wait_until_sent(%d), jiffies=%lu, expire=%lu...\n",
		port->line, jअगरfies, expire);

	/*
	 * Check whether the transmitter is empty every 'char_time'.
	 * 'timeout' / 'expire' give us the maximum amount of समय
	 * we रुको.
	 */
	जबतक (!port->ops->tx_empty(port)) अणु
		msleep_पूर्णांकerruptible(jअगरfies_to_msecs(अक्षर_समय));
		अगर (संकेत_pending(current))
			अवरोध;
		अगर (समय_after(jअगरfies, expire))
			अवरोध;
	पूर्ण
	uart_port_deref(port);
पूर्ण

/*
 * Calls to uart_hangup() are serialised by the tty_lock in
 *   drivers/tty/tty_io.c:करो_tty_hangup()
 * This runs from a workqueue and can sleep क्रम a _लघु_ समय only.
 */
अटल व्योम uart_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	काष्ठा tty_port *port = &state->port;
	काष्ठा uart_port *uport;
	अचिन्हित दीर्घ flags;

	pr_debug("uart_hangup(%d)\n", tty->index);

	mutex_lock(&port->mutex);
	uport = uart_port_check(state);
	WARN(!uport, "hangup of detached port!\n");

	अगर (tty_port_active(port)) अणु
		uart_flush_buffer(tty);
		uart_shutकरोwn(tty, state);
		spin_lock_irqsave(&port->lock, flags);
		port->count = 0;
		spin_unlock_irqrestore(&port->lock, flags);
		tty_port_set_active(port, 0);
		tty_port_tty_set(port, शून्य);
		अगर (uport && !uart_console(uport))
			uart_change_pm(state, UART_PM_STATE_OFF);
		wake_up_पूर्णांकerruptible(&port->खोलो_रुको);
		wake_up_पूर्णांकerruptible(&port->delta_msr_रुको);
	पूर्ण
	mutex_unlock(&port->mutex);
पूर्ण

/* uport == शून्य अगर uart_port has alपढ़ोy been हटाओd */
अटल व्योम uart_port_shutकरोwn(काष्ठा tty_port *port)
अणु
	काष्ठा uart_state *state = container_of(port, काष्ठा uart_state, port);
	काष्ठा uart_port *uport = uart_port_check(state);

	/*
	 * clear delta_msr_रुको queue to aव्योम mem leaks: we may मुक्त
	 * the irq here so the queue might never be woken up.  Note
	 * that we won't end up रुकोing on delta_msr_रुको again since
	 * any outstanding file descriptors should be poपूर्णांकing at
	 * hung_up_tty_fops now.
	 */
	wake_up_पूर्णांकerruptible(&port->delta_msr_रुको);

	/*
	 * Free the IRQ and disable the port.
	 */
	अगर (uport)
		uport->ops->shutकरोwn(uport);

	/*
	 * Ensure that the IRQ handler isn't running on another CPU.
	 */
	अगर (uport)
		synchronize_irq(uport->irq);
पूर्ण

अटल पूर्णांक uart_carrier_उठाओd(काष्ठा tty_port *port)
अणु
	काष्ठा uart_state *state = container_of(port, काष्ठा uart_state, port);
	काष्ठा uart_port *uport;
	पूर्णांक mctrl;

	uport = uart_port_ref(state);
	/*
	 * Should never observe uport == शून्य since checks क्रम hangup should
	 * पात the tty_port_block_til_पढ़ोy() loop beक्रमe checking क्रम carrier
	 * उठाओd -- but report carrier उठाओd अगर it करोes anyway so खोलो will
	 * जारी and not sleep
	 */
	अगर (WARN_ON(!uport))
		वापस 1;
	spin_lock_irq(&uport->lock);
	uart_enable_ms(uport);
	mctrl = uport->ops->get_mctrl(uport);
	spin_unlock_irq(&uport->lock);
	uart_port_deref(uport);
	अगर (mctrl & TIOCM_CAR)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम uart_dtr_rts(काष्ठा tty_port *port, पूर्णांक उठाओ)
अणु
	काष्ठा uart_state *state = container_of(port, काष्ठा uart_state, port);
	काष्ठा uart_port *uport;

	uport = uart_port_ref(state);
	अगर (!uport)
		वापस;
	uart_port_dtr_rts(uport, उठाओ);
	uart_port_deref(uport);
पूर्ण

अटल पूर्णांक uart_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा uart_driver *drv = driver->driver_state;
	काष्ठा uart_state *state = drv->state + tty->index;

	tty->driver_data = state;

	वापस tty_standard_install(driver, tty);
पूर्ण

/*
 * Calls to uart_खोलो are serialised by the tty_lock in
 *   drivers/tty/tty_io.c:tty_खोलो()
 * Note that अगर this fails, then uart_बंद() _will_ be called.
 *
 * In समय, we want to scrap the "opening nonpresent ports"
 * behaviour and implement an alternative way क्रम setserial
 * to set base addresses/ports/types.  This will allow us to
 * get rid of a certain amount of extra tests.
 */
अटल पूर्णांक uart_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा uart_state *state = tty->driver_data;
	पूर्णांक retval;

	retval = tty_port_खोलो(&state->port, tty, filp);
	अगर (retval > 0)
		retval = 0;

	वापस retval;
पूर्ण

अटल पूर्णांक uart_port_activate(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा uart_state *state = container_of(port, काष्ठा uart_state, port);
	काष्ठा uart_port *uport;
	पूर्णांक ret;

	uport = uart_port_check(state);
	अगर (!uport || uport->flags & UPF_DEAD)
		वापस -ENXIO;

	/*
	 * Start up the serial port.
	 */
	ret = uart_startup(tty, state, 0);
	अगर (ret > 0)
		tty_port_set_active(port, 1);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *uart_type(काष्ठा uart_port *port)
अणु
	स्थिर अक्षर *str = शून्य;

	अगर (port->ops->type)
		str = port->ops->type(port);

	अगर (!str)
		str = "unknown";

	वापस str;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

अटल व्योम uart_line_info(काष्ठा seq_file *m, काष्ठा uart_driver *drv, पूर्णांक i)
अणु
	काष्ठा uart_state *state = drv->state + i;
	काष्ठा tty_port *port = &state->port;
	क्रमागत uart_pm_state pm_state;
	काष्ठा uart_port *uport;
	अक्षर stat_buf[32];
	अचिन्हित पूर्णांक status;
	पूर्णांक mmio;

	mutex_lock(&port->mutex);
	uport = uart_port_check(state);
	अगर (!uport)
		जाओ out;

	mmio = uport->iotype >= UPIO_MEM;
	seq_म_लिखो(m, "%d: uart:%s %s%08llX irq:%d",
			uport->line, uart_type(uport),
			mmio ? "mmio:0x" : "port:",
			mmio ? (अचिन्हित दीर्घ दीर्घ)uport->mapbase
			     : (अचिन्हित दीर्घ दीर्घ)uport->iobase,
			uport->irq);

	अगर (uport->type == PORT_UNKNOWN) अणु
		seq_अ_दो(m, '\n');
		जाओ out;
	पूर्ण

	अगर (capable(CAP_SYS_ADMIN)) अणु
		pm_state = state->pm_state;
		अगर (pm_state != UART_PM_STATE_ON)
			uart_change_pm(state, UART_PM_STATE_ON);
		spin_lock_irq(&uport->lock);
		status = uport->ops->get_mctrl(uport);
		spin_unlock_irq(&uport->lock);
		अगर (pm_state != UART_PM_STATE_ON)
			uart_change_pm(state, pm_state);

		seq_म_लिखो(m, " tx:%d rx:%d",
				uport->icount.tx, uport->icount.rx);
		अगर (uport->icount.frame)
			seq_म_लिखो(m, " fe:%d",	uport->icount.frame);
		अगर (uport->icount.parity)
			seq_म_लिखो(m, " pe:%d",	uport->icount.parity);
		अगर (uport->icount.brk)
			seq_म_लिखो(m, " brk:%d", uport->icount.brk);
		अगर (uport->icount.overrun)
			seq_म_लिखो(m, " oe:%d", uport->icount.overrun);
		अगर (uport->icount.buf_overrun)
			seq_म_लिखो(m, " bo:%d", uport->icount.buf_overrun);

#घोषणा INFOBIT(bit, str) \
	अगर (uport->mctrl & (bit)) \
		म_जोड़न(stat_buf, (str), माप(stat_buf) - \
			म_माप(stat_buf) - 2)
#घोषणा STATBIT(bit, str) \
	अगर (status & (bit)) \
		म_जोड़न(stat_buf, (str), माप(stat_buf) - \
		       म_माप(stat_buf) - 2)

		stat_buf[0] = '\0';
		stat_buf[1] = '\0';
		INFOBIT(TIOCM_RTS, "|RTS");
		STATBIT(TIOCM_CTS, "|CTS");
		INFOBIT(TIOCM_DTR, "|DTR");
		STATBIT(TIOCM_DSR, "|DSR");
		STATBIT(TIOCM_CAR, "|CD");
		STATBIT(TIOCM_RNG, "|RI");
		अगर (stat_buf[0])
			stat_buf[0] = ' ';

		seq_माला_दो(m, stat_buf);
	पूर्ण
	seq_अ_दो(m, '\n');
#अघोषित STATBIT
#अघोषित INFOBIT
out:
	mutex_unlock(&port->mutex);
पूर्ण

अटल पूर्णांक uart_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा tty_driver *ttydrv = m->निजी;
	काष्ठा uart_driver *drv = ttydrv->driver_state;
	पूर्णांक i;

	seq_म_लिखो(m, "serinfo:1.0 driver%s%s revision:%s\n", "", "", "");
	क्रम (i = 0; i < drv->nr; i++)
		uart_line_info(m, drv, i);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool uart_console_enabled(काष्ठा uart_port *port)
अणु
	वापस uart_console(port) && (port->cons->flags & CON_ENABLED);
पूर्ण

अटल व्योम uart_port_spin_lock_init(काष्ठा uart_port *port)
अणु
	spin_lock_init(&port->lock);
	lockdep_set_class(&port->lock, &port_lock_key);
पूर्ण

#अगर defined(CONFIG_SERIAL_CORE_CONSOLE) || defined(CONFIG_CONSOLE_POLL)
/**
 *	uart_console_ग_लिखो - ग_लिखो a console message to a serial port
 *	@port: the port to ग_लिखो the message
 *	@s: array of अक्षरacters
 *	@count: number of अक्षरacters in string to ग_लिखो
 *	@अक्षर_दो: function to ग_लिखो अक्षरacter to port
 */
व्योम uart_console_ग_लिखो(काष्ठा uart_port *port, स्थिर अक्षर *s,
			अचिन्हित पूर्णांक count,
			व्योम (*अक्षर_दो)(काष्ठा uart_port *, पूर्णांक))
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++, s++) अणु
		अगर (*s == '\n')
			अक्षर_दो(port, '\r');
		अक्षर_दो(port, *s);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(uart_console_ग_लिखो);

/*
 *	Check whether an invalid uart number has been specअगरied, and
 *	अगर so, search क्रम the first available port that करोes have
 *	console support.
 */
काष्ठा uart_port * __init
uart_get_console(काष्ठा uart_port *ports, पूर्णांक nr, काष्ठा console *co)
अणु
	पूर्णांक idx = co->index;

	अगर (idx < 0 || idx >= nr || (ports[idx].iobase == 0 &&
				     ports[idx].membase == शून्य))
		क्रम (idx = 0; idx < nr; idx++)
			अगर (ports[idx].iobase != 0 ||
			    ports[idx].membase != शून्य)
				अवरोध;

	co->index = idx;

	वापस ports + idx;
पूर्ण

/**
 *	uart_parse_earlycon - Parse earlycon options
 *	@p:	  ptr to 2nd field (ie., just beyond '<name>,')
 *	@iotype:  ptr क्रम decoded iotype (out)
 *	@addr:    ptr क्रम decoded mapbase/iobase (out)
 *	@options: ptr क्रम <options> field; शून्य अगर not present (out)
 *
 *	Decodes earlycon kernel command line parameters of the क्रमm
 *	   earlycon=<name>,io|mmio|mmio16|mmio32|mmio32be|mmio32native,<addr>,<options>
 *	   console=<name>,io|mmio|mmio16|mmio32|mmio32be|mmio32native,<addr>,<options>
 *
 *	The optional क्रमm
 *
 *	   earlycon=<name>,0x<addr>,<options>
 *	   console=<name>,0x<addr>,<options>
 *
 *	is also accepted; the वापसed @iotype will be UPIO_MEM.
 *
 *	Returns 0 on success or -EINVAL on failure
 */
पूर्णांक uart_parse_earlycon(अक्षर *p, अचिन्हित अक्षर *iotype, resource_माप_प्रकार *addr,
			अक्षर **options)
अणु
	अगर (म_भेदन(p, "mmio,", 5) == 0) अणु
		*iotype = UPIO_MEM;
		p += 5;
	पूर्ण अन्यथा अगर (म_भेदन(p, "mmio16,", 7) == 0) अणु
		*iotype = UPIO_MEM16;
		p += 7;
	पूर्ण अन्यथा अगर (म_भेदन(p, "mmio32,", 7) == 0) अणु
		*iotype = UPIO_MEM32;
		p += 7;
	पूर्ण अन्यथा अगर (म_भेदन(p, "mmio32be,", 9) == 0) अणु
		*iotype = UPIO_MEM32BE;
		p += 9;
	पूर्ण अन्यथा अगर (म_भेदन(p, "mmio32native,", 13) == 0) अणु
		*iotype = IS_ENABLED(CONFIG_CPU_BIG_ENDIAN) ?
			UPIO_MEM32BE : UPIO_MEM32;
		p += 13;
	पूर्ण अन्यथा अगर (म_भेदन(p, "io,", 3) == 0) अणु
		*iotype = UPIO_PORT;
		p += 3;
	पूर्ण अन्यथा अगर (म_भेदन(p, "0x", 2) == 0) अणु
		*iotype = UPIO_MEM;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	/*
	 * Beक्रमe you replace it with kम_से_अदीर्घl(), think about options separator
	 * (',') it will not tolerate
	 */
	*addr = simple_म_से_अदीर्घl(p, शून्य, 0);
	p = म_अक्षर(p, ',');
	अगर (p)
		p++;

	*options = p;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(uart_parse_earlycon);

/**
 *	uart_parse_options - Parse serial port baud/parity/bits/flow control.
 *	@options: poपूर्णांकer to option string
 *	@baud: poपूर्णांकer to an 'int' variable क्रम the baud rate.
 *	@parity: poपूर्णांकer to an 'int' variable क्रम the parity.
 *	@bits: poपूर्णांकer to an 'int' variable क्रम the number of data bits.
 *	@flow: poपूर्णांकer to an 'int' variable क्रम the flow control अक्षरacter.
 *
 *	uart_parse_options decodes a string containing the serial console
 *	options.  The क्रमmat of the string is <baud><parity><bits><flow>,
 *	eg: 115200n8r
 */
व्योम
uart_parse_options(स्थिर अक्षर *options, पूर्णांक *baud, पूर्णांक *parity,
		   पूर्णांक *bits, पूर्णांक *flow)
अणु
	स्थिर अक्षर *s = options;

	*baud = simple_म_से_अदीर्घ(s, शून्य, 10);
	जबतक (*s >= '0' && *s <= '9')
		s++;
	अगर (*s)
		*parity = *s++;
	अगर (*s)
		*bits = *s++ - '0';
	अगर (*s)
		*flow = *s;
पूर्ण
EXPORT_SYMBOL_GPL(uart_parse_options);

/**
 *	uart_set_options - setup the serial console parameters
 *	@port: poपूर्णांकer to the serial ports uart_port काष्ठाure
 *	@co: console poपूर्णांकer
 *	@baud: baud rate
 *	@parity: parity अक्षरacter - 'n' (none), 'o' (odd), 'e' (even)
 *	@bits: number of data bits
 *	@flow: flow control अक्षरacter - 'r' (rts)
 */
पूर्णांक
uart_set_options(काष्ठा uart_port *port, काष्ठा console *co,
		 पूर्णांक baud, पूर्णांक parity, पूर्णांक bits, पूर्णांक flow)
अणु
	काष्ठा ktermios termios;
	अटल काष्ठा ktermios dummy;

	/*
	 * Ensure that the serial-console lock is initialised early.
	 *
	 * Note that the console-enabled check is needed because of kgdboc,
	 * which can end up calling uart_set_options() क्रम an alपढ़ोy enabled
	 * console via tty_find_polling_driver() and uart_poll_init().
	 */
	अगर (!uart_console_enabled(port) && !port->console_reinit)
		uart_port_spin_lock_init(port);

	स_रखो(&termios, 0, माप(काष्ठा ktermios));

	termios.c_cflag |= CREAD | HUPCL | CLOCAL;
	tty_termios_encode_baud_rate(&termios, baud, baud);

	अगर (bits == 7)
		termios.c_cflag |= CS7;
	अन्यथा
		termios.c_cflag |= CS8;

	चयन (parity) अणु
	हाल 'o': case 'O':
		termios.c_cflag |= PARODD;
		fallthrough;
	हाल 'e': case 'E':
		termios.c_cflag |= PARENB;
		अवरोध;
	पूर्ण

	अगर (flow == 'r')
		termios.c_cflag |= CRTSCTS;

	/*
	 * some uarts on other side करोn't support no flow control.
	 * So we set * DTR in host uart to make them happy
	 */
	port->mctrl |= TIOCM_DTR;

	port->ops->set_termios(port, &termios, &dummy);
	/*
	 * Allow the setting of the UART parameters with a शून्य console
	 * too:
	 */
	अगर (co)
		co->cflag = termios.c_cflag;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(uart_set_options);
#पूर्ण_अगर /* CONFIG_SERIAL_CORE_CONSOLE */

/**
 * uart_change_pm - set घातer state of the port
 *
 * @state: port descriptor
 * @pm_state: new state
 *
 * Locking: port->mutex has to be held
 */
अटल व्योम uart_change_pm(काष्ठा uart_state *state,
			   क्रमागत uart_pm_state pm_state)
अणु
	काष्ठा uart_port *port = uart_port_check(state);

	अगर (state->pm_state != pm_state) अणु
		अगर (port && port->ops->pm)
			port->ops->pm(port, pm_state, state->pm_state);
		state->pm_state = pm_state;
	पूर्ण
पूर्ण

काष्ठा uart_match अणु
	काष्ठा uart_port *port;
	काष्ठा uart_driver *driver;
पूर्ण;

अटल पूर्णांक serial_match_port(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा uart_match *match = data;
	काष्ठा tty_driver *tty_drv = match->driver->tty_driver;
	dev_t devt = MKDEV(tty_drv->major, tty_drv->minor_start) +
		match->port->line;

	वापस dev->devt == devt; /* Actually, only one tty per port */
पूर्ण

पूर्णांक uart_suspend_port(काष्ठा uart_driver *drv, काष्ठा uart_port *uport)
अणु
	काष्ठा uart_state *state = drv->state + uport->line;
	काष्ठा tty_port *port = &state->port;
	काष्ठा device *tty_dev;
	काष्ठा uart_match match = अणुuport, drvपूर्ण;

	mutex_lock(&port->mutex);

	tty_dev = device_find_child(uport->dev, &match, serial_match_port);
	अगर (tty_dev && device_may_wakeup(tty_dev)) अणु
		enable_irq_wake(uport->irq);
		put_device(tty_dev);
		mutex_unlock(&port->mutex);
		वापस 0;
	पूर्ण
	put_device(tty_dev);

	/* Nothing to करो अगर the console is not suspending */
	अगर (!console_suspend_enabled && uart_console(uport))
		जाओ unlock;

	uport->suspended = 1;

	अगर (tty_port_initialized(port)) अणु
		स्थिर काष्ठा uart_ops *ops = uport->ops;
		पूर्णांक tries;

		tty_port_set_suspended(port, 1);
		tty_port_set_initialized(port, 0);

		spin_lock_irq(&uport->lock);
		ops->stop_tx(uport);
		ops->set_mctrl(uport, 0);
		ops->stop_rx(uport);
		spin_unlock_irq(&uport->lock);

		/*
		 * Wait क्रम the transmitter to empty.
		 */
		क्रम (tries = 3; !ops->tx_empty(uport) && tries; tries--)
			msleep(10);
		अगर (!tries)
			dev_err(uport->dev, "%s: Unable to drain transmitter\n",
				uport->name);

		ops->shutकरोwn(uport);
	पूर्ण

	/*
	 * Disable the console device beक्रमe suspending.
	 */
	अगर (uart_console(uport))
		console_stop(uport->cons);

	uart_change_pm(state, UART_PM_STATE_OFF);
unlock:
	mutex_unlock(&port->mutex);

	वापस 0;
पूर्ण

पूर्णांक uart_resume_port(काष्ठा uart_driver *drv, काष्ठा uart_port *uport)
अणु
	काष्ठा uart_state *state = drv->state + uport->line;
	काष्ठा tty_port *port = &state->port;
	काष्ठा device *tty_dev;
	काष्ठा uart_match match = अणुuport, drvपूर्ण;
	काष्ठा ktermios termios;

	mutex_lock(&port->mutex);

	tty_dev = device_find_child(uport->dev, &match, serial_match_port);
	अगर (!uport->suspended && device_may_wakeup(tty_dev)) अणु
		अगर (irqd_is_wakeup_set(irq_get_irq_data((uport->irq))))
			disable_irq_wake(uport->irq);
		put_device(tty_dev);
		mutex_unlock(&port->mutex);
		वापस 0;
	पूर्ण
	put_device(tty_dev);
	uport->suspended = 0;

	/*
	 * Re-enable the console device after suspending.
	 */
	अगर (uart_console(uport)) अणु
		/*
		 * First try to use the console cflag setting.
		 */
		स_रखो(&termios, 0, माप(काष्ठा ktermios));
		termios.c_cflag = uport->cons->cflag;

		/*
		 * If that's unset, use the tty termios setting.
		 */
		अगर (port->tty && termios.c_cflag == 0)
			termios = port->tty->termios;

		अगर (console_suspend_enabled)
			uart_change_pm(state, UART_PM_STATE_ON);
		uport->ops->set_termios(uport, &termios, शून्य);
		अगर (console_suspend_enabled)
			console_start(uport->cons);
	पूर्ण

	अगर (tty_port_suspended(port)) अणु
		स्थिर काष्ठा uart_ops *ops = uport->ops;
		पूर्णांक ret;

		uart_change_pm(state, UART_PM_STATE_ON);
		spin_lock_irq(&uport->lock);
		ops->set_mctrl(uport, 0);
		spin_unlock_irq(&uport->lock);
		अगर (console_suspend_enabled || !uart_console(uport)) अणु
			/* Protected by port mutex क्रम now */
			काष्ठा tty_काष्ठा *tty = port->tty;

			ret = ops->startup(uport);
			अगर (ret == 0) अणु
				अगर (tty)
					uart_change_speed(tty, state, शून्य);
				spin_lock_irq(&uport->lock);
				ops->set_mctrl(uport, uport->mctrl);
				ops->start_tx(uport);
				spin_unlock_irq(&uport->lock);
				tty_port_set_initialized(port, 1);
			पूर्ण अन्यथा अणु
				/*
				 * Failed to resume - maybe hardware went away?
				 * Clear the "initialized" flag so we won't try
				 * to call the low level drivers shutकरोwn method.
				 */
				uart_shutकरोwn(tty, state);
			पूर्ण
		पूर्ण

		tty_port_set_suspended(port, 0);
	पूर्ण

	mutex_unlock(&port->mutex);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
uart_report_port(काष्ठा uart_driver *drv, काष्ठा uart_port *port)
अणु
	अक्षर address[64];

	चयन (port->iotype) अणु
	हाल UPIO_PORT:
		snम_लिखो(address, माप(address), "I/O 0x%lx", port->iobase);
		अवरोध;
	हाल UPIO_HUB6:
		snम_लिखो(address, माप(address),
			 "I/O 0x%lx offset 0x%x", port->iobase, port->hub6);
		अवरोध;
	हाल UPIO_MEM:
	हाल UPIO_MEM16:
	हाल UPIO_MEM32:
	हाल UPIO_MEM32BE:
	हाल UPIO_AU:
	हाल UPIO_TSI:
		snम_लिखो(address, माप(address),
			 "MMIO 0x%llx", (अचिन्हित दीर्घ दीर्घ)port->mapbase);
		अवरोध;
	शेष:
		strlcpy(address, "*unknown*", माप(address));
		अवरोध;
	पूर्ण

	pr_info("%s%s%s at %s (irq = %d, base_baud = %d) is a %s\n",
	       port->dev ? dev_name(port->dev) : "",
	       port->dev ? ": " : "",
	       port->name,
	       address, port->irq, port->uartclk / 16, uart_type(port));
पूर्ण

अटल व्योम
uart_configure_port(काष्ठा uart_driver *drv, काष्ठा uart_state *state,
		    काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक flags;

	/*
	 * If there isn't a port here, don't करो anything further.
	 */
	अगर (!port->iobase && !port->mapbase && !port->membase)
		वापस;

	/*
	 * Now करो the स्वतः configuration stuff.  Note that config_port
	 * is expected to claim the resources and map the port क्रम us.
	 */
	flags = 0;
	अगर (port->flags & UPF_AUTO_IRQ)
		flags |= UART_CONFIG_IRQ;
	अगर (port->flags & UPF_BOOT_AUTOCONF) अणु
		अगर (!(port->flags & UPF_FIXED_TYPE)) अणु
			port->type = PORT_UNKNOWN;
			flags |= UART_CONFIG_TYPE;
		पूर्ण
		port->ops->config_port(port, flags);
	पूर्ण

	अगर (port->type != PORT_UNKNOWN) अणु
		अचिन्हित दीर्घ flags;

		uart_report_port(drv, port);

		/* Power up port क्रम set_mctrl() */
		uart_change_pm(state, UART_PM_STATE_ON);

		/*
		 * Ensure that the modem control lines are de-activated.
		 * keep the DTR setting that is set in uart_set_options()
		 * We probably करोn't need a spinlock around this, but
		 */
		spin_lock_irqsave(&port->lock, flags);
		port->ops->set_mctrl(port, port->mctrl & TIOCM_DTR);
		spin_unlock_irqrestore(&port->lock, flags);

		/*
		 * If this driver supports console, and it hasn't been
		 * successfully रेजिस्टरed yet, try to re-रेजिस्टर it.
		 * It may be that the port was not available.
		 */
		अगर (port->cons && !(port->cons->flags & CON_ENABLED))
			रेजिस्टर_console(port->cons);

		/*
		 * Power करोwn all ports by शेष, except the
		 * console अगर we have one.
		 */
		अगर (!uart_console(port))
			uart_change_pm(state, UART_PM_STATE_OFF);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL

अटल पूर्णांक uart_poll_init(काष्ठा tty_driver *driver, पूर्णांक line, अक्षर *options)
अणु
	काष्ठा uart_driver *drv = driver->driver_state;
	काष्ठा uart_state *state = drv->state + line;
	काष्ठा tty_port *tport;
	काष्ठा uart_port *port;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	पूर्णांक ret = 0;

	tport = &state->port;
	mutex_lock(&tport->mutex);

	port = uart_port_check(state);
	अगर (!port || !(port->ops->poll_get_अक्षर && port->ops->poll_put_अक्षर)) अणु
		ret = -1;
		जाओ out;
	पूर्ण

	अगर (port->ops->poll_init) अणु
		/*
		 * We करोn't set initialized as we only initialized the hw,
		 * e.g. state->xmit is still uninitialized.
		 */
		अगर (!tty_port_initialized(tport))
			ret = port->ops->poll_init(port);
	पूर्ण

	अगर (!ret && options) अणु
		uart_parse_options(options, &baud, &parity, &bits, &flow);
		ret = uart_set_options(port, शून्य, baud, parity, bits, flow);
	पूर्ण
out:
	mutex_unlock(&tport->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक uart_poll_get_अक्षर(काष्ठा tty_driver *driver, पूर्णांक line)
अणु
	काष्ठा uart_driver *drv = driver->driver_state;
	काष्ठा uart_state *state = drv->state + line;
	काष्ठा uart_port *port;
	पूर्णांक ret = -1;

	port = uart_port_ref(state);
	अगर (port) अणु
		ret = port->ops->poll_get_अक्षर(port);
		uart_port_deref(port);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम uart_poll_put_अक्षर(काष्ठा tty_driver *driver, पूर्णांक line, अक्षर ch)
अणु
	काष्ठा uart_driver *drv = driver->driver_state;
	काष्ठा uart_state *state = drv->state + line;
	काष्ठा uart_port *port;

	port = uart_port_ref(state);
	अगर (!port)
		वापस;

	अगर (ch == '\n')
		port->ops->poll_put_अक्षर(port, '\r');
	port->ops->poll_put_अक्षर(port, ch);
	uart_port_deref(port);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा tty_operations uart_ops = अणु
	.install	= uart_install,
	.खोलो		= uart_खोलो,
	.बंद		= uart_बंद,
	.ग_लिखो		= uart_ग_लिखो,
	.put_अक्षर	= uart_put_अक्षर,
	.flush_अक्षरs	= uart_flush_अक्षरs,
	.ग_लिखो_room	= uart_ग_लिखो_room,
	.अक्षरs_in_buffer= uart_अक्षरs_in_buffer,
	.flush_buffer	= uart_flush_buffer,
	.ioctl		= uart_ioctl,
	.throttle	= uart_throttle,
	.unthrottle	= uart_unthrottle,
	.send_xअक्षर	= uart_send_xअक्षर,
	.set_termios	= uart_set_termios,
	.set_ldisc	= uart_set_ldisc,
	.stop		= uart_stop,
	.start		= uart_start,
	.hangup		= uart_hangup,
	.अवरोध_ctl	= uart_अवरोध_ctl,
	.रुको_until_sent= uart_रुको_until_sent,
#अगर_घोषित CONFIG_PROC_FS
	.proc_show	= uart_proc_show,
#पूर्ण_अगर
	.tiocmget	= uart_tiocmget,
	.tiocmset	= uart_tiocmset,
	.set_serial	= uart_set_info_user,
	.get_serial	= uart_get_info_user,
	.get_icount	= uart_get_icount,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_init	= uart_poll_init,
	.poll_get_अक्षर	= uart_poll_get_अक्षर,
	.poll_put_अक्षर	= uart_poll_put_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा tty_port_operations uart_port_ops = अणु
	.carrier_उठाओd = uart_carrier_उठाओd,
	.dtr_rts	= uart_dtr_rts,
	.activate	= uart_port_activate,
	.shutकरोwn	= uart_tty_port_shutकरोwn,
पूर्ण;

/**
 *	uart_रेजिस्टर_driver - रेजिस्टर a driver with the uart core layer
 *	@drv: low level driver काष्ठाure
 *
 *	Register a uart driver with the core driver.  We in turn रेजिस्टर
 *	with the tty layer, and initialise the core driver per-port state.
 *
 *	We have a proc file in /proc/tty/driver which is named after the
 *	normal driver.
 *
 *	drv->port should be शून्य, and the per-port काष्ठाures should be
 *	रेजिस्टरed using uart_add_one_port after this call has succeeded.
 */
पूर्णांक uart_रेजिस्टर_driver(काष्ठा uart_driver *drv)
अणु
	काष्ठा tty_driver *normal;
	पूर्णांक i, retval = -ENOMEM;

	BUG_ON(drv->state);

	/*
	 * Maybe we should be using a slab cache क्रम this, especially अगर
	 * we have a large number of ports to handle.
	 */
	drv->state = kसुस्मृति(drv->nr, माप(काष्ठा uart_state), GFP_KERNEL);
	अगर (!drv->state)
		जाओ out;

	normal = alloc_tty_driver(drv->nr);
	अगर (!normal)
		जाओ out_kमुक्त;

	drv->tty_driver = normal;

	normal->driver_name	= drv->driver_name;
	normal->name		= drv->dev_name;
	normal->major		= drv->major;
	normal->minor_start	= drv->minor;
	normal->type		= TTY_DRIVER_TYPE_SERIAL;
	normal->subtype		= SERIAL_TYPE_NORMAL;
	normal->init_termios	= tty_std_termios;
	normal->init_termios.c_cflag = B9600 | CS8 | CREAD | HUPCL | CLOCAL;
	normal->init_termios.c_ispeed = normal->init_termios.c_ospeed = 9600;
	normal->flags		= TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	normal->driver_state    = drv;
	tty_set_operations(normal, &uart_ops);

	/*
	 * Initialise the UART state(s).
	 */
	क्रम (i = 0; i < drv->nr; i++) अणु
		काष्ठा uart_state *state = drv->state + i;
		काष्ठा tty_port *port = &state->port;

		tty_port_init(port);
		port->ops = &uart_port_ops;
	पूर्ण

	retval = tty_रेजिस्टर_driver(normal);
	अगर (retval >= 0)
		वापस retval;

	क्रम (i = 0; i < drv->nr; i++)
		tty_port_destroy(&drv->state[i].port);
	put_tty_driver(normal);
out_kमुक्त:
	kमुक्त(drv->state);
out:
	वापस retval;
पूर्ण

/**
 *	uart_unरेजिस्टर_driver - हटाओ a driver from the uart core layer
 *	@drv: low level driver काष्ठाure
 *
 *	Remove all references to a driver from the core driver.  The low
 *	level driver must have हटाओd all its ports via the
 *	uart_हटाओ_one_port() अगर it रेजिस्टरed them with uart_add_one_port().
 *	(ie, drv->port == शून्य)
 */
व्योम uart_unरेजिस्टर_driver(काष्ठा uart_driver *drv)
अणु
	काष्ठा tty_driver *p = drv->tty_driver;
	अचिन्हित पूर्णांक i;

	tty_unरेजिस्टर_driver(p);
	put_tty_driver(p);
	क्रम (i = 0; i < drv->nr; i++)
		tty_port_destroy(&drv->state[i].port);
	kमुक्त(drv->state);
	drv->state = शून्य;
	drv->tty_driver = शून्य;
पूर्ण

काष्ठा tty_driver *uart_console_device(काष्ठा console *co, पूर्णांक *index)
अणु
	काष्ठा uart_driver *p = co->data;
	*index = co->index;
	वापस p->tty_driver;
पूर्ण
EXPORT_SYMBOL_GPL(uart_console_device);

अटल sमाप_प्रकार uartclk_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serial_काष्ठा पंचांगp;
	काष्ठा tty_port *port = dev_get_drvdata(dev);

	uart_get_info(port, &पंचांगp);
	वापस प्र_लिखो(buf, "%d\n", पंचांगp.baud_base * 16);
पूर्ण

अटल sमाप_प्रकार type_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serial_काष्ठा पंचांगp;
	काष्ठा tty_port *port = dev_get_drvdata(dev);

	uart_get_info(port, &पंचांगp);
	वापस प्र_लिखो(buf, "%d\n", पंचांगp.type);
पूर्ण

अटल sमाप_प्रकार line_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serial_काष्ठा पंचांगp;
	काष्ठा tty_port *port = dev_get_drvdata(dev);

	uart_get_info(port, &पंचांगp);
	वापस प्र_लिखो(buf, "%d\n", पंचांगp.line);
पूर्ण

अटल sमाप_प्रकार port_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serial_काष्ठा पंचांगp;
	काष्ठा tty_port *port = dev_get_drvdata(dev);
	अचिन्हित दीर्घ ioaddr;

	uart_get_info(port, &पंचांगp);
	ioaddr = पंचांगp.port;
	अगर (HIGH_BITS_OFFSET)
		ioaddr |= (अचिन्हित दीर्घ)पंचांगp.port_high << HIGH_BITS_OFFSET;
	वापस प्र_लिखो(buf, "0x%lX\n", ioaddr);
पूर्ण

अटल sमाप_प्रकार irq_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serial_काष्ठा पंचांगp;
	काष्ठा tty_port *port = dev_get_drvdata(dev);

	uart_get_info(port, &पंचांगp);
	वापस प्र_लिखो(buf, "%d\n", पंचांगp.irq);
पूर्ण

अटल sमाप_प्रकार flags_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serial_काष्ठा पंचांगp;
	काष्ठा tty_port *port = dev_get_drvdata(dev);

	uart_get_info(port, &पंचांगp);
	वापस प्र_लिखो(buf, "0x%X\n", पंचांगp.flags);
पूर्ण

अटल sमाप_प्रकार xmit_fअगरo_size_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serial_काष्ठा पंचांगp;
	काष्ठा tty_port *port = dev_get_drvdata(dev);

	uart_get_info(port, &पंचांगp);
	वापस प्र_लिखो(buf, "%d\n", पंचांगp.xmit_fअगरo_size);
पूर्ण

अटल sमाप_प्रकार बंद_delay_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serial_काष्ठा पंचांगp;
	काष्ठा tty_port *port = dev_get_drvdata(dev);

	uart_get_info(port, &पंचांगp);
	वापस प्र_लिखो(buf, "%d\n", पंचांगp.बंद_delay);
पूर्ण

अटल sमाप_प्रकार closing_रुको_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serial_काष्ठा पंचांगp;
	काष्ठा tty_port *port = dev_get_drvdata(dev);

	uart_get_info(port, &पंचांगp);
	वापस प्र_लिखो(buf, "%d\n", पंचांगp.closing_रुको);
पूर्ण

अटल sमाप_प्रकार custom_भागisor_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serial_काष्ठा पंचांगp;
	काष्ठा tty_port *port = dev_get_drvdata(dev);

	uart_get_info(port, &पंचांगp);
	वापस प्र_लिखो(buf, "%d\n", पंचांगp.custom_भागisor);
पूर्ण

अटल sमाप_प्रकार io_type_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serial_काष्ठा पंचांगp;
	काष्ठा tty_port *port = dev_get_drvdata(dev);

	uart_get_info(port, &पंचांगp);
	वापस प्र_लिखो(buf, "%d\n", पंचांगp.io_type);
पूर्ण

अटल sमाप_प्रकार iomem_base_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serial_काष्ठा पंचांगp;
	काष्ठा tty_port *port = dev_get_drvdata(dev);

	uart_get_info(port, &पंचांगp);
	वापस प्र_लिखो(buf, "0x%lX\n", (अचिन्हित दीर्घ)पंचांगp.iomem_base);
पूर्ण

अटल sमाप_प्रकार iomem_reg_shअगरt_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा serial_काष्ठा पंचांगp;
	काष्ठा tty_port *port = dev_get_drvdata(dev);

	uart_get_info(port, &पंचांगp);
	वापस प्र_लिखो(buf, "%d\n", पंचांगp.iomem_reg_shअगरt);
पूर्ण

अटल sमाप_प्रकार console_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tty_port *port = dev_get_drvdata(dev);
	काष्ठा uart_state *state = container_of(port, काष्ठा uart_state, port);
	काष्ठा uart_port *uport;
	bool console = false;

	mutex_lock(&port->mutex);
	uport = uart_port_check(state);
	अगर (uport)
		console = uart_console_enabled(uport);
	mutex_unlock(&port->mutex);

	वापस प्र_लिखो(buf, "%c\n", console ? 'Y' : 'N');
पूर्ण

अटल sमाप_प्रकार console_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा tty_port *port = dev_get_drvdata(dev);
	काष्ठा uart_state *state = container_of(port, काष्ठा uart_state, port);
	काष्ठा uart_port *uport;
	bool oldconsole, newconsole;
	पूर्णांक ret;

	ret = kstrtobool(buf, &newconsole);
	अगर (ret)
		वापस ret;

	mutex_lock(&port->mutex);
	uport = uart_port_check(state);
	अगर (uport) अणु
		oldconsole = uart_console_enabled(uport);
		अगर (oldconsole && !newconsole) अणु
			ret = unरेजिस्टर_console(uport->cons);
		पूर्ण अन्यथा अगर (!oldconsole && newconsole) अणु
			अगर (uart_console(uport)) अणु
				uport->console_reinit = 1;
				रेजिस्टर_console(uport->cons);
			पूर्ण अन्यथा अणु
				ret = -ENOENT;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -ENXIO;
	पूर्ण
	mutex_unlock(&port->mutex);

	वापस ret < 0 ? ret : count;
पूर्ण

अटल DEVICE_ATTR_RO(uartclk);
अटल DEVICE_ATTR_RO(type);
अटल DEVICE_ATTR_RO(line);
अटल DEVICE_ATTR_RO(port);
अटल DEVICE_ATTR_RO(irq);
अटल DEVICE_ATTR_RO(flags);
अटल DEVICE_ATTR_RO(xmit_fअगरo_size);
अटल DEVICE_ATTR_RO(बंद_delay);
अटल DEVICE_ATTR_RO(closing_रुको);
अटल DEVICE_ATTR_RO(custom_भागisor);
अटल DEVICE_ATTR_RO(io_type);
अटल DEVICE_ATTR_RO(iomem_base);
अटल DEVICE_ATTR_RO(iomem_reg_shअगरt);
अटल DEVICE_ATTR_RW(console);

अटल काष्ठा attribute *tty_dev_attrs[] = अणु
	&dev_attr_uartclk.attr,
	&dev_attr_type.attr,
	&dev_attr_line.attr,
	&dev_attr_port.attr,
	&dev_attr_irq.attr,
	&dev_attr_flags.attr,
	&dev_attr_xmit_fअगरo_size.attr,
	&dev_attr_बंद_delay.attr,
	&dev_attr_closing_रुको.attr,
	&dev_attr_custom_भागisor.attr,
	&dev_attr_io_type.attr,
	&dev_attr_iomem_base.attr,
	&dev_attr_iomem_reg_shअगरt.attr,
	&dev_attr_console.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group tty_dev_attr_group = अणु
	.attrs = tty_dev_attrs,
पूर्ण;

/**
 *	uart_add_one_port - attach a driver-defined port काष्ठाure
 *	@drv: poपूर्णांकer to the uart low level driver काष्ठाure क्रम this port
 *	@uport: uart port काष्ठाure to use क्रम this port.
 *
 *	Context: task context, might sleep
 *
 *	This allows the driver to रेजिस्टर its own uart_port काष्ठाure
 *	with the core driver.  The मुख्य purpose is to allow the low
 *	level uart drivers to expand uart_port, rather than having yet
 *	more levels of काष्ठाures.
 */
पूर्णांक uart_add_one_port(काष्ठा uart_driver *drv, काष्ठा uart_port *uport)
अणु
	काष्ठा uart_state *state;
	काष्ठा tty_port *port;
	पूर्णांक ret = 0;
	काष्ठा device *tty_dev;
	पूर्णांक num_groups;

	अगर (uport->line >= drv->nr)
		वापस -EINVAL;

	state = drv->state + uport->line;
	port = &state->port;

	mutex_lock(&port_mutex);
	mutex_lock(&port->mutex);
	अगर (state->uart_port) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Link the port to the driver state table and vice versa */
	atomic_set(&state->refcount, 1);
	init_रुकोqueue_head(&state->हटाओ_रुको);
	state->uart_port = uport;
	uport->state = state;

	state->pm_state = UART_PM_STATE_UNDEFINED;
	uport->cons = drv->cons;
	uport->minor = drv->tty_driver->minor_start + uport->line;
	uport->name = kaप्र_लिखो(GFP_KERNEL, "%s%d", drv->dev_name,
				drv->tty_driver->name_base + uport->line);
	अगर (!uport->name) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * If this port is in use as a console then the spinlock is alपढ़ोy
	 * initialised.
	 */
	अगर (!uart_console_enabled(uport))
		uart_port_spin_lock_init(uport);

	अगर (uport->cons && uport->dev)
		of_console_check(uport->dev->of_node, uport->cons->name, uport->line);

	tty_port_link_device(port, drv->tty_driver, uport->line);
	uart_configure_port(drv, state, uport);

	port->console = uart_console(uport);

	num_groups = 2;
	अगर (uport->attr_group)
		num_groups++;

	uport->tty_groups = kसुस्मृति(num_groups, माप(*uport->tty_groups),
				    GFP_KERNEL);
	अगर (!uport->tty_groups) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	uport->tty_groups[0] = &tty_dev_attr_group;
	अगर (uport->attr_group)
		uport->tty_groups[1] = uport->attr_group;

	/*
	 * Register the port whether it's detected or not.  This allows
	 * setserial to be used to alter this port's parameters.
	 */
	tty_dev = tty_port_रेजिस्टर_device_attr_serdev(port, drv->tty_driver,
			uport->line, uport->dev, port, uport->tty_groups);
	अगर (!IS_ERR(tty_dev)) अणु
		device_set_wakeup_capable(tty_dev, 1);
	पूर्ण अन्यथा अणु
		dev_err(uport->dev, "Cannot register tty device on line %d\n",
		       uport->line);
	पूर्ण

	/*
	 * Ensure UPF_DEAD is not set.
	 */
	uport->flags &= ~UPF_DEAD;

 out:
	mutex_unlock(&port->mutex);
	mutex_unlock(&port_mutex);

	वापस ret;
पूर्ण

/**
 *	uart_हटाओ_one_port - detach a driver defined port काष्ठाure
 *	@drv: poपूर्णांकer to the uart low level driver काष्ठाure क्रम this port
 *	@uport: uart port काष्ठाure क्रम this port
 *
 *	Context: task context, might sleep
 *
 *	This unhooks (and hangs up) the specअगरied port काष्ठाure from the
 *	core driver.  No further calls will be made to the low-level code
 *	क्रम this port.
 */
पूर्णांक uart_हटाओ_one_port(काष्ठा uart_driver *drv, काष्ठा uart_port *uport)
अणु
	काष्ठा uart_state *state = drv->state + uport->line;
	काष्ठा tty_port *port = &state->port;
	काष्ठा uart_port *uart_port;
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक ret = 0;

	mutex_lock(&port_mutex);

	/*
	 * Mark the port "dead" - this prevents any खोलोs from
	 * succeeding जबतक we shut करोwn the port.
	 */
	mutex_lock(&port->mutex);
	uart_port = uart_port_check(state);
	अगर (uart_port != uport)
		dev_alert(uport->dev, "Removing wrong port: %p != %p\n",
			  uart_port, uport);

	अगर (!uart_port) अणु
		mutex_unlock(&port->mutex);
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	uport->flags |= UPF_DEAD;
	mutex_unlock(&port->mutex);

	/*
	 * Remove the devices from the tty layer
	 */
	tty_port_unरेजिस्टर_device(port, drv->tty_driver, uport->line);

	tty = tty_port_tty_get(port);
	अगर (tty) अणु
		tty_vhangup(port->tty);
		tty_kref_put(tty);
	पूर्ण

	/*
	 * If the port is used as a console, unरेजिस्टर it
	 */
	अगर (uart_console(uport))
		unरेजिस्टर_console(uport->cons);

	/*
	 * Free the port IO and memory resources, अगर any.
	 */
	अगर (uport->type != PORT_UNKNOWN && uport->ops->release_port)
		uport->ops->release_port(uport);
	kमुक्त(uport->tty_groups);
	kमुक्त(uport->name);

	/*
	 * Indicate that there isn't a port here anymore.
	 */
	uport->type = PORT_UNKNOWN;

	mutex_lock(&port->mutex);
	WARN_ON(atomic_dec_वापस(&state->refcount) < 0);
	रुको_event(state->हटाओ_रुको, !atomic_पढ़ो(&state->refcount));
	state->uart_port = शून्य;
	mutex_unlock(&port->mutex);
out:
	mutex_unlock(&port_mutex);

	वापस ret;
पूर्ण

/*
 *	Are the two ports equivalent?
 */
पूर्णांक uart_match_port(काष्ठा uart_port *port1, काष्ठा uart_port *port2)
अणु
	अगर (port1->iotype != port2->iotype)
		वापस 0;

	चयन (port1->iotype) अणु
	हाल UPIO_PORT:
		वापस (port1->iobase == port2->iobase);
	हाल UPIO_HUB6:
		वापस (port1->iobase == port2->iobase) &&
		       (port1->hub6   == port2->hub6);
	हाल UPIO_MEM:
	हाल UPIO_MEM16:
	हाल UPIO_MEM32:
	हाल UPIO_MEM32BE:
	हाल UPIO_AU:
	हाल UPIO_TSI:
		वापस (port1->mapbase == port2->mapbase);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(uart_match_port);

/**
 *	uart_handle_dcd_change - handle a change of carrier detect state
 *	@uport: uart_port काष्ठाure क्रम the खोलो port
 *	@status: new carrier detect status, nonzero अगर active
 *
 *	Caller must hold uport->lock
 */
व्योम uart_handle_dcd_change(काष्ठा uart_port *uport, अचिन्हित पूर्णांक status)
अणु
	काष्ठा tty_port *port = &uport->state->port;
	काष्ठा tty_काष्ठा *tty = port->tty;
	काष्ठा tty_ldisc *ld;

	lockdep_निश्चित_held_once(&uport->lock);

	अगर (tty) अणु
		ld = tty_ldisc_ref(tty);
		अगर (ld) अणु
			अगर (ld->ops->dcd_change)
				ld->ops->dcd_change(tty, status);
			tty_ldisc_deref(ld);
		पूर्ण
	पूर्ण

	uport->icount.dcd++;

	अगर (uart_dcd_enabled(uport)) अणु
		अगर (status)
			wake_up_पूर्णांकerruptible(&port->खोलो_रुको);
		अन्यथा अगर (tty)
			tty_hangup(tty);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(uart_handle_dcd_change);

/**
 *	uart_handle_cts_change - handle a change of clear-to-send state
 *	@uport: uart_port काष्ठाure क्रम the खोलो port
 *	@status: new clear to send status, nonzero अगर active
 *
 *	Caller must hold uport->lock
 */
व्योम uart_handle_cts_change(काष्ठा uart_port *uport, अचिन्हित पूर्णांक status)
अणु
	lockdep_निश्चित_held_once(&uport->lock);

	uport->icount.cts++;

	अगर (uart_softcts_mode(uport)) अणु
		अगर (uport->hw_stopped) अणु
			अगर (status) अणु
				uport->hw_stopped = 0;
				uport->ops->start_tx(uport);
				uart_ग_लिखो_wakeup(uport);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!status) अणु
				uport->hw_stopped = 1;
				uport->ops->stop_tx(uport);
			पूर्ण
		पूर्ण

	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(uart_handle_cts_change);

/**
 * uart_insert_अक्षर - push a अक्षर to the uart layer
 *
 * User is responsible to call tty_flip_buffer_push when they are करोne with
 * insertion.
 *
 * @port: corresponding port
 * @status: state of the serial port RX buffer (LSR क्रम 8250)
 * @overrun: mask of overrun bits in @status
 * @ch: अक्षरacter to push
 * @flag: flag क्रम the अक्षरacter (see TTY_NORMAL and मित्रs)
 */
व्योम uart_insert_अक्षर(काष्ठा uart_port *port, अचिन्हित पूर्णांक status,
		 अचिन्हित पूर्णांक overrun, अचिन्हित पूर्णांक ch, अचिन्हित पूर्णांक flag)
अणु
	काष्ठा tty_port *tport = &port->state->port;

	अगर ((status & port->ignore_status_mask & ~overrun) == 0)
		अगर (tty_insert_flip_अक्षर(tport, ch, flag) == 0)
			++port->icount.buf_overrun;

	/*
	 * Overrun is special.  Since it's reported immediately,
	 * it करोesn't affect the current अक्षरacter.
	 */
	अगर (status & ~port->ignore_status_mask & overrun)
		अगर (tty_insert_flip_अक्षर(tport, 0, TTY_OVERRUN) == 0)
			++port->icount.buf_overrun;
पूर्ण
EXPORT_SYMBOL_GPL(uart_insert_अक्षर);

#अगर_घोषित CONFIG_MAGIC_SYSRQ_SERIAL
अटल स्थिर अक्षर sysrq_toggle_seq[] = CONFIG_MAGIC_SYSRQ_SERIAL_SEQUENCE;

अटल व्योम uart_sysrq_on(काष्ठा work_काष्ठा *w)
अणु
	पूर्णांक sysrq_toggle_seq_len = म_माप(sysrq_toggle_seq);

	sysrq_toggle_support(1);
	pr_info("SysRq is enabled by magic sequence '%*pE' on serial\n",
		sysrq_toggle_seq_len, sysrq_toggle_seq);
पूर्ण
अटल DECLARE_WORK(sysrq_enable_work, uart_sysrq_on);

/**
 *	uart_try_toggle_sysrq - Enables SysRq from serial line
 *	@port: uart_port काष्ठाure where अक्षर(s) after BREAK met
 *	@ch: new अक्षरacter in the sequence after received BREAK
 *
 *	Enables magic SysRq when the required sequence is met on port
 *	(see CONFIG_MAGIC_SYSRQ_SERIAL_SEQUENCE).
 *
 *	Returns false अगर @ch is out of enabling sequence and should be
 *	handled some other way, true अगर @ch was consumed.
 */
bool uart_try_toggle_sysrq(काष्ठा uart_port *port, अचिन्हित पूर्णांक ch)
अणु
	पूर्णांक sysrq_toggle_seq_len = म_माप(sysrq_toggle_seq);

	अगर (!sysrq_toggle_seq_len)
		वापस false;

	BUILD_BUG_ON(ARRAY_SIZE(sysrq_toggle_seq) >= U8_MAX);
	अगर (sysrq_toggle_seq[port->sysrq_seq] != ch) अणु
		port->sysrq_seq = 0;
		वापस false;
	पूर्ण

	अगर (++port->sysrq_seq < sysrq_toggle_seq_len) अणु
		port->sysrq = jअगरfies + SYSRQ_TIMEOUT;
		वापस true;
	पूर्ण

	schedule_work(&sysrq_enable_work);

	port->sysrq = 0;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(uart_try_toggle_sysrq);
#पूर्ण_अगर

EXPORT_SYMBOL(uart_ग_लिखो_wakeup);
EXPORT_SYMBOL(uart_रेजिस्टर_driver);
EXPORT_SYMBOL(uart_unरेजिस्टर_driver);
EXPORT_SYMBOL(uart_suspend_port);
EXPORT_SYMBOL(uart_resume_port);
EXPORT_SYMBOL(uart_add_one_port);
EXPORT_SYMBOL(uart_हटाओ_one_port);

/**
 * uart_get_rs485_mode() - retrieve rs485 properties क्रम given uart
 * @port: uart device's target port
 *
 * This function implements the device tree binding described in
 * Documentation/devicetree/bindings/serial/rs485.txt.
 */
पूर्णांक uart_get_rs485_mode(काष्ठा uart_port *port)
अणु
	काष्ठा serial_rs485 *rs485conf = &port->rs485;
	काष्ठा device *dev = port->dev;
	u32 rs485_delay[2];
	पूर्णांक ret;

	ret = device_property_पढ़ो_u32_array(dev, "rs485-rts-delay",
					     rs485_delay, 2);
	अगर (!ret) अणु
		rs485conf->delay_rts_beक्रमe_send = rs485_delay[0];
		rs485conf->delay_rts_after_send = rs485_delay[1];
	पूर्ण अन्यथा अणु
		rs485conf->delay_rts_beक्रमe_send = 0;
		rs485conf->delay_rts_after_send = 0;
	पूर्ण

	/*
	 * Clear full-duplex and enabled flags, set RTS polarity to active high
	 * to get to a defined state with the following properties:
	 */
	rs485conf->flags &= ~(SER_RS485_RX_DURING_TX | SER_RS485_ENABLED |
			      SER_RS485_TERMINATE_BUS |
			      SER_RS485_RTS_AFTER_SEND);
	rs485conf->flags |= SER_RS485_RTS_ON_SEND;

	अगर (device_property_पढ़ो_bool(dev, "rs485-rx-during-tx"))
		rs485conf->flags |= SER_RS485_RX_DURING_TX;

	अगर (device_property_पढ़ो_bool(dev, "linux,rs485-enabled-at-boot-time"))
		rs485conf->flags |= SER_RS485_ENABLED;

	अगर (device_property_पढ़ो_bool(dev, "rs485-rts-active-low")) अणु
		rs485conf->flags &= ~SER_RS485_RTS_ON_SEND;
		rs485conf->flags |= SER_RS485_RTS_AFTER_SEND;
	पूर्ण

	/*
	 * Disabling termination by शेष is the safe choice:  Else अगर many
	 * bus participants enable it, no communication is possible at all.
	 * Works fine क्रम लघु cables and users may enable क्रम दीर्घer cables.
	 */
	port->rs485_term_gpio = devm_gpiod_get_optional(dev, "rs485-term",
							GPIOD_OUT_LOW);
	अगर (IS_ERR(port->rs485_term_gpio)) अणु
		ret = PTR_ERR(port->rs485_term_gpio);
		port->rs485_term_gpio = शून्य;
		वापस dev_err_probe(dev, ret, "Cannot get rs485-term-gpios\n");
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(uart_get_rs485_mode);

MODULE_DESCRIPTION("Serial driver core");
MODULE_LICENSE("GPL");
