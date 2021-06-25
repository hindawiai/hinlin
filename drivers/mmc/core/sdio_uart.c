<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SDIO UART/GPS driver
 *
 * Based on drivers/serial/8250.c and drivers/serial/serial_core.c
 * by Russell King.
 *
 * Author:	Nicolas Pitre
 * Created:	June 15, 2007
 * Copyright:	MontaVista Software, Inc.
 */

/*
 * Note: Although this driver assumes a 16550A-like UART implementation,
 * it is not possible to leverage the common 8250/16550 driver, nor the
 * core UART infraकाष्ठाure, as they assumes direct access to the hardware
 * रेजिस्टरs, often under a spinlock.  This is not possible in the SDIO
 * context as SDIO access functions must be able to sleep.
 *
 * Because we need to lock the SDIO host to ensure an exclusive access to
 * the card, we simply rely on that lock to also prevent and serialize
 * concurrent access to the same port.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/mutex.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/slab.h>

#समावेश <linux/mmc/core.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/sdio_ids.h>


#घोषणा UART_NR		8	/* Number of UARTs this driver can handle */


#घोषणा FIFO_SIZE	PAGE_SIZE
#घोषणा WAKEUP_CHARS	256

काष्ठा uart_icount अणु
	__u32	cts;
	__u32	dsr;
	__u32	rng;
	__u32	dcd;
	__u32	rx;
	__u32	tx;
	__u32	frame;
	__u32	overrun;
	__u32	parity;
	__u32	brk;
पूर्ण;

काष्ठा sdio_uart_port अणु
	काष्ठा tty_port		port;
	अचिन्हित पूर्णांक		index;
	काष्ठा sdio_func	*func;
	काष्ठा mutex		func_lock;
	काष्ठा task_काष्ठा	*in_sdio_uart_irq;
	अचिन्हित पूर्णांक		regs_offset;
	काष्ठा kfअगरo		xmit_fअगरo;
	spinlock_t		ग_लिखो_lock;
	काष्ठा uart_icount	icount;
	अचिन्हित पूर्णांक		uartclk;
	अचिन्हित पूर्णांक		mctrl;
	अचिन्हित पूर्णांक		rx_mctrl;
	अचिन्हित पूर्णांक		पढ़ो_status_mask;
	अचिन्हित पूर्णांक		ignore_status_mask;
	अचिन्हित अक्षर		x_अक्षर;
	अचिन्हित अक्षर           ier;
	अचिन्हित अक्षर           lcr;
पूर्ण;

अटल काष्ठा sdio_uart_port *sdio_uart_table[UART_NR];
अटल DEFINE_SPINLOCK(sdio_uart_table_lock);

अटल पूर्णांक sdio_uart_add_port(काष्ठा sdio_uart_port *port)
अणु
	पूर्णांक index, ret = -EBUSY;

	mutex_init(&port->func_lock);
	spin_lock_init(&port->ग_लिखो_lock);
	अगर (kfअगरo_alloc(&port->xmit_fअगरo, FIFO_SIZE, GFP_KERNEL))
		वापस -ENOMEM;

	spin_lock(&sdio_uart_table_lock);
	क्रम (index = 0; index < UART_NR; index++) अणु
		अगर (!sdio_uart_table[index]) अणु
			port->index = index;
			sdio_uart_table[index] = port;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&sdio_uart_table_lock);

	वापस ret;
पूर्ण

अटल काष्ठा sdio_uart_port *sdio_uart_port_get(अचिन्हित index)
अणु
	काष्ठा sdio_uart_port *port;

	अगर (index >= UART_NR)
		वापस शून्य;

	spin_lock(&sdio_uart_table_lock);
	port = sdio_uart_table[index];
	अगर (port)
		tty_port_get(&port->port);
	spin_unlock(&sdio_uart_table_lock);

	वापस port;
पूर्ण

अटल व्योम sdio_uart_port_put(काष्ठा sdio_uart_port *port)
अणु
	tty_port_put(&port->port);
पूर्ण

अटल व्योम sdio_uart_port_हटाओ(काष्ठा sdio_uart_port *port)
अणु
	काष्ठा sdio_func *func;

	spin_lock(&sdio_uart_table_lock);
	sdio_uart_table[port->index] = शून्य;
	spin_unlock(&sdio_uart_table_lock);

	/*
	 * We're समाप्तing a port that potentially still is in use by
	 * the tty layer. Be careful to prevent any further access
	 * to the SDIO function and arrange क्रम the tty layer to
	 * give up on that port ASAP.
	 * Beware: the lock ordering is critical.
	 */
	mutex_lock(&port->port.mutex);
	mutex_lock(&port->func_lock);
	func = port->func;
	sdio_claim_host(func);
	port->func = शून्य;
	mutex_unlock(&port->func_lock);
	/* tty_hangup is async so is this safe as is ?? */
	tty_port_tty_hangup(&port->port, false);
	mutex_unlock(&port->port.mutex);
	sdio_release_irq(func);
	sdio_disable_func(func);
	sdio_release_host(func);

	sdio_uart_port_put(port);
पूर्ण

अटल पूर्णांक sdio_uart_claim_func(काष्ठा sdio_uart_port *port)
अणु
	mutex_lock(&port->func_lock);
	अगर (unlikely(!port->func)) अणु
		mutex_unlock(&port->func_lock);
		वापस -ENODEV;
	पूर्ण
	अगर (likely(port->in_sdio_uart_irq != current))
		sdio_claim_host(port->func);
	mutex_unlock(&port->func_lock);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sdio_uart_release_func(काष्ठा sdio_uart_port *port)
अणु
	अगर (likely(port->in_sdio_uart_irq != current))
		sdio_release_host(port->func);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक sdio_in(काष्ठा sdio_uart_port *port, पूर्णांक offset)
अणु
	अचिन्हित अक्षर c;
	c = sdio_पढ़ोb(port->func, port->regs_offset + offset, शून्य);
	वापस c;
पूर्ण

अटल अंतरभूत व्योम sdio_out(काष्ठा sdio_uart_port *port, पूर्णांक offset, पूर्णांक value)
अणु
	sdio_ग_लिखोb(port->func, value, port->regs_offset + offset, शून्य);
पूर्ण

अटल अचिन्हित पूर्णांक sdio_uart_get_mctrl(काष्ठा sdio_uart_port *port)
अणु
	अचिन्हित अक्षर status;
	अचिन्हित पूर्णांक ret;

	/* FIXME: What stops this losing the delta bits and अवरोधing
	   sdio_uart_check_modem_status ? */
	status = sdio_in(port, UART_MSR);

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

अटल व्योम sdio_uart_ग_लिखो_mctrl(काष्ठा sdio_uart_port *port,
				  अचिन्हित पूर्णांक mctrl)
अणु
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

	sdio_out(port, UART_MCR, mcr);
पूर्ण

अटल अंतरभूत व्योम sdio_uart_update_mctrl(काष्ठा sdio_uart_port *port,
					  अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	अचिन्हित पूर्णांक old;

	old = port->mctrl;
	port->mctrl = (old & ~clear) | set;
	अगर (old != port->mctrl)
		sdio_uart_ग_लिखो_mctrl(port, port->mctrl);
पूर्ण

#घोषणा sdio_uart_set_mctrl(port, x)	sdio_uart_update_mctrl(port, x, 0)
#घोषणा sdio_uart_clear_mctrl(port, x)	sdio_uart_update_mctrl(port, 0, x)

अटल व्योम sdio_uart_change_speed(काष्ठा sdio_uart_port *port,
				   काष्ठा ktermios *termios,
				   काष्ठा ktermios *old)
अणु
	अचिन्हित अक्षर cval, fcr = 0;
	अचिन्हित पूर्णांक baud, quot;

	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		cval = UART_LCR_WLEN5;
		अवरोध;
	हाल CS6:
		cval = UART_LCR_WLEN6;
		अवरोध;
	हाल CS7:
		cval = UART_LCR_WLEN7;
		अवरोध;
	शेष:
	हाल CS8:
		cval = UART_LCR_WLEN8;
		अवरोध;
	पूर्ण

	अगर (termios->c_cflag & CSTOPB)
		cval |= UART_LCR_STOP;
	अगर (termios->c_cflag & PARENB)
		cval |= UART_LCR_PARITY;
	अगर (!(termios->c_cflag & PARODD))
		cval |= UART_LCR_EPAR;

	क्रम (;;) अणु
		baud = tty_termios_baud_rate(termios);
		अगर (baud == 0)
			baud = 9600;  /* Special हाल: B0 rate. */
		अगर (baud <= port->uartclk)
			अवरोध;
		/*
		 * Oops, the quotient was zero.  Try again with the old
		 * baud rate अगर possible, otherwise शेष to 9600.
		 */
		termios->c_cflag &= ~CBAUD;
		अगर (old) अणु
			termios->c_cflag |= old->c_cflag & CBAUD;
			old = शून्य;
		पूर्ण अन्यथा
			termios->c_cflag |= B9600;
	पूर्ण
	quot = (2 * port->uartclk + baud) / (2 * baud);

	अगर (baud < 2400)
		fcr = UART_FCR_ENABLE_FIFO | UART_FCR_TRIGGER_1;
	अन्यथा
		fcr = UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10;

	port->पढ़ो_status_mask = UART_LSR_OE | UART_LSR_THRE | UART_LSR_DR;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= UART_LSR_FE | UART_LSR_PE;
	अगर (termios->c_अगरlag & (BRKINT | PARMRK))
		port->पढ़ो_status_mask |= UART_LSR_BI;

	/*
	 * Characters to ignore
	 */
	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= UART_LSR_PE | UART_LSR_FE;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		port->ignore_status_mask |= UART_LSR_BI;
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			port->ignore_status_mask |= UART_LSR_OE;
	पूर्ण

	/*
	 * ignore all अक्षरacters अगर CREAD is not set
	 */
	अगर ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= UART_LSR_DR;

	/*
	 * CTS flow control flag and modem status पूर्णांकerrupts
	 */
	port->ier &= ~UART_IER_MSI;
	अगर ((termios->c_cflag & CRTSCTS) || !(termios->c_cflag & CLOCAL))
		port->ier |= UART_IER_MSI;

	port->lcr = cval;

	sdio_out(port, UART_IER, port->ier);
	sdio_out(port, UART_LCR, cval | UART_LCR_DLAB);
	sdio_out(port, UART_DLL, quot & 0xff);
	sdio_out(port, UART_DLM, quot >> 8);
	sdio_out(port, UART_LCR, cval);
	sdio_out(port, UART_FCR, fcr);

	sdio_uart_ग_लिखो_mctrl(port, port->mctrl);
पूर्ण

अटल व्योम sdio_uart_start_tx(काष्ठा sdio_uart_port *port)
अणु
	अगर (!(port->ier & UART_IER_THRI)) अणु
		port->ier |= UART_IER_THRI;
		sdio_out(port, UART_IER, port->ier);
	पूर्ण
पूर्ण

अटल व्योम sdio_uart_stop_tx(काष्ठा sdio_uart_port *port)
अणु
	अगर (port->ier & UART_IER_THRI) अणु
		port->ier &= ~UART_IER_THRI;
		sdio_out(port, UART_IER, port->ier);
	पूर्ण
पूर्ण

अटल व्योम sdio_uart_stop_rx(काष्ठा sdio_uart_port *port)
अणु
	port->ier &= ~UART_IER_RLSI;
	port->पढ़ो_status_mask &= ~UART_LSR_DR;
	sdio_out(port, UART_IER, port->ier);
पूर्ण

अटल व्योम sdio_uart_receive_अक्षरs(काष्ठा sdio_uart_port *port,
				    अचिन्हित पूर्णांक *status)
अणु
	अचिन्हित पूर्णांक ch, flag;
	पूर्णांक max_count = 256;

	करो अणु
		ch = sdio_in(port, UART_RX);
		flag = TTY_NORMAL;
		port->icount.rx++;

		अगर (unlikely(*status & (UART_LSR_BI | UART_LSR_PE |
					UART_LSR_FE | UART_LSR_OE))) अणु
			/*
			 * For statistics only
			 */
			अगर (*status & UART_LSR_BI) अणु
				*status &= ~(UART_LSR_FE | UART_LSR_PE);
				port->icount.brk++;
			पूर्ण अन्यथा अगर (*status & UART_LSR_PE)
				port->icount.parity++;
			अन्यथा अगर (*status & UART_LSR_FE)
				port->icount.frame++;
			अगर (*status & UART_LSR_OE)
				port->icount.overrun++;

			/*
			 * Mask off conditions which should be ignored.
			 */
			*status &= port->पढ़ो_status_mask;
			अगर (*status & UART_LSR_BI)
				flag = TTY_BREAK;
			अन्यथा अगर (*status & UART_LSR_PE)
				flag = TTY_PARITY;
			अन्यथा अगर (*status & UART_LSR_FE)
				flag = TTY_FRAME;
		पूर्ण

		अगर ((*status & port->ignore_status_mask & ~UART_LSR_OE) == 0)
			tty_insert_flip_अक्षर(&port->port, ch, flag);

		/*
		 * Overrun is special.  Since it's reported immediately,
		 * it करोesn't affect the current अक्षरacter.
		 */
		अगर (*status & ~port->ignore_status_mask & UART_LSR_OE)
			tty_insert_flip_अक्षर(&port->port, 0, TTY_OVERRUN);

		*status = sdio_in(port, UART_LSR);
	पूर्ण जबतक ((*status & UART_LSR_DR) && (max_count-- > 0));

	tty_flip_buffer_push(&port->port);
पूर्ण

अटल व्योम sdio_uart_transmit_अक्षरs(काष्ठा sdio_uart_port *port)
अणु
	काष्ठा kfअगरo *xmit = &port->xmit_fअगरo;
	पूर्णांक count;
	काष्ठा tty_काष्ठा *tty;
	u8 iobuf[16];
	पूर्णांक len;

	अगर (port->x_अक्षर) अणु
		sdio_out(port, UART_TX, port->x_अक्षर);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण

	tty = tty_port_tty_get(&port->port);

	अगर (tty == शून्य || !kfअगरo_len(xmit) ||
				tty->stopped || tty->hw_stopped) अणु
		sdio_uart_stop_tx(port);
		tty_kref_put(tty);
		वापस;
	पूर्ण

	len = kfअगरo_out_locked(xmit, iobuf, 16, &port->ग_लिखो_lock);
	क्रम (count = 0; count < len; count++) अणु
		sdio_out(port, UART_TX, iobuf[count]);
		port->icount.tx++;
	पूर्ण

	len = kfअगरo_len(xmit);
	अगर (len < WAKEUP_CHARS) अणु
		tty_wakeup(tty);
		अगर (len == 0)
			sdio_uart_stop_tx(port);
	पूर्ण
	tty_kref_put(tty);
पूर्ण

अटल व्योम sdio_uart_check_modem_status(काष्ठा sdio_uart_port *port)
अणु
	पूर्णांक status;
	काष्ठा tty_काष्ठा *tty;

	status = sdio_in(port, UART_MSR);

	अगर ((status & UART_MSR_ANY_DELTA) == 0)
		वापस;

	अगर (status & UART_MSR_TERI)
		port->icount.rng++;
	अगर (status & UART_MSR_DDSR)
		port->icount.dsr++;
	अगर (status & UART_MSR_DDCD) अणु
		port->icount.dcd++;
		/* DCD उठाओ - wake क्रम खोलो */
		अगर (status & UART_MSR_DCD)
			wake_up_पूर्णांकerruptible(&port->port.खोलो_रुको);
		अन्यथा अणु
			/* DCD drop - hang up अगर tty attached */
			tty_port_tty_hangup(&port->port, false);
		पूर्ण
	पूर्ण
	अगर (status & UART_MSR_DCTS) अणु
		port->icount.cts++;
		tty = tty_port_tty_get(&port->port);
		अगर (tty && C_CRTSCTS(tty)) अणु
			पूर्णांक cts = (status & UART_MSR_CTS);
			अगर (tty->hw_stopped) अणु
				अगर (cts) अणु
					tty->hw_stopped = 0;
					sdio_uart_start_tx(port);
					tty_wakeup(tty);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (!cts) अणु
					tty->hw_stopped = 1;
					sdio_uart_stop_tx(port);
				पूर्ण
			पूर्ण
		पूर्ण
		tty_kref_put(tty);
	पूर्ण
पूर्ण

/*
 * This handles the पूर्णांकerrupt from one port.
 */
अटल व्योम sdio_uart_irq(काष्ठा sdio_func *func)
अणु
	काष्ठा sdio_uart_port *port = sdio_get_drvdata(func);
	अचिन्हित पूर्णांक iir, lsr;

	/*
	 * In a few places sdio_uart_irq() is called directly instead of
	 * रुकोing क्रम the actual पूर्णांकerrupt to be उठाओd and the SDIO IRQ
	 * thपढ़ो scheduled in order to reduce latency.  However, some
	 * पूर्णांकeraction with the tty core may end up calling us back
	 * (serial echo, flow control, etc.) through those same places
	 * causing undesirable effects.  Let's stop the recursion here.
	 */
	अगर (unlikely(port->in_sdio_uart_irq == current))
		वापस;

	iir = sdio_in(port, UART_IIR);
	अगर (iir & UART_IIR_NO_INT)
		वापस;

	port->in_sdio_uart_irq = current;
	lsr = sdio_in(port, UART_LSR);
	अगर (lsr & UART_LSR_DR)
		sdio_uart_receive_अक्षरs(port, &lsr);
	sdio_uart_check_modem_status(port);
	अगर (lsr & UART_LSR_THRE)
		sdio_uart_transmit_अक्षरs(port);
	port->in_sdio_uart_irq = शून्य;
पूर्ण

अटल पूर्णांक uart_carrier_उठाओd(काष्ठा tty_port *tport)
अणु
	काष्ठा sdio_uart_port *port =
			container_of(tport, काष्ठा sdio_uart_port, port);
	अचिन्हित पूर्णांक ret = sdio_uart_claim_func(port);
	अगर (ret)	/* Missing hardware shouldn't block क्रम carrier */
		वापस 1;
	ret = sdio_uart_get_mctrl(port);
	sdio_uart_release_func(port);
	अगर (ret & TIOCM_CAR)
		वापस 1;
	वापस 0;
पूर्ण

/**
 *	uart_dtr_rts		-	 port helper to set uart संकेतs
 *	@tport: tty port to be updated
 *	@onoff: set to turn on DTR/RTS
 *
 *	Called by the tty port helpers when the modem संकेतs need to be
 *	adjusted during an खोलो, बंद and hangup.
 */

अटल व्योम uart_dtr_rts(काष्ठा tty_port *tport, पूर्णांक onoff)
अणु
	काष्ठा sdio_uart_port *port =
			container_of(tport, काष्ठा sdio_uart_port, port);
	पूर्णांक ret = sdio_uart_claim_func(port);
	अगर (ret)
		वापस;
	अगर (onoff == 0)
		sdio_uart_clear_mctrl(port, TIOCM_DTR | TIOCM_RTS);
	अन्यथा
		sdio_uart_set_mctrl(port, TIOCM_DTR | TIOCM_RTS);
	sdio_uart_release_func(port);
पूर्ण

/**
 *	sdio_uart_activate	-	start up hardware
 *	@tport: tty port to activate
 *	@tty: tty bound to this port
 *
 *	Activate a tty port. The port locking guarantees us this will be
 *	run exactly once per set of खोलोs, and अगर successful will see the
 *	shutकरोwn method run exactly once to match. Start up and shutकरोwn are
 *	रक्षित from each other by the पूर्णांकernal locking and will not run
 *	at the same समय even during a hangup event.
 *
 *	If we successfully start up the port we take an extra kref as we
 *	will keep it around until shutकरोwn when the kref is dropped.
 */

अटल पूर्णांक sdio_uart_activate(काष्ठा tty_port *tport, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा sdio_uart_port *port =
			container_of(tport, काष्ठा sdio_uart_port, port);
	पूर्णांक ret;

	/*
	 * Set the TTY IO error marker - we will only clear this
	 * once we have successfully खोलोed the port.
	 */
	set_bit(TTY_IO_ERROR, &tty->flags);

	kfअगरo_reset(&port->xmit_fअगरo);

	ret = sdio_uart_claim_func(port);
	अगर (ret)
		वापस ret;
	ret = sdio_enable_func(port->func);
	अगर (ret)
		जाओ err1;
	ret = sdio_claim_irq(port->func, sdio_uart_irq);
	अगर (ret)
		जाओ err2;

	/*
	 * Clear the FIFO buffers and disable them.
	 * (they will be reenabled in sdio_change_speed())
	 */
	sdio_out(port, UART_FCR, UART_FCR_ENABLE_FIFO);
	sdio_out(port, UART_FCR, UART_FCR_ENABLE_FIFO |
		       UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
	sdio_out(port, UART_FCR, 0);

	/*
	 * Clear the पूर्णांकerrupt रेजिस्टरs.
	 */
	(व्योम) sdio_in(port, UART_LSR);
	(व्योम) sdio_in(port, UART_RX);
	(व्योम) sdio_in(port, UART_IIR);
	(व्योम) sdio_in(port, UART_MSR);

	/*
	 * Now, initialize the UART
	 */
	sdio_out(port, UART_LCR, UART_LCR_WLEN8);

	port->ier = UART_IER_RLSI|UART_IER_RDI|UART_IER_RTOIE|UART_IER_UUE;
	port->mctrl = TIOCM_OUT2;

	sdio_uart_change_speed(port, &tty->termios, शून्य);

	अगर (C_BAUD(tty))
		sdio_uart_set_mctrl(port, TIOCM_RTS | TIOCM_DTR);

	अगर (C_CRTSCTS(tty))
		अगर (!(sdio_uart_get_mctrl(port) & TIOCM_CTS))
			tty->hw_stopped = 1;

	clear_bit(TTY_IO_ERROR, &tty->flags);

	/* Kick the IRQ handler once जबतक we're still holding the host lock */
	sdio_uart_irq(port->func);

	sdio_uart_release_func(port);
	वापस 0;

err2:
	sdio_disable_func(port->func);
err1:
	sdio_uart_release_func(port);
	वापस ret;
पूर्ण

/**
 *	sdio_uart_shutकरोwn	-	stop hardware
 *	@tport: tty port to shut करोwn
 *
 *	Deactivate a tty port. The port locking guarantees us this will be
 *	run only अगर a successful matching activate alपढ़ोy ran. The two are
 *	रक्षित from each other by the पूर्णांकernal locking and will not run
 *	at the same समय even during a hangup event.
 */

अटल व्योम sdio_uart_shutकरोwn(काष्ठा tty_port *tport)
अणु
	काष्ठा sdio_uart_port *port =
			container_of(tport, काष्ठा sdio_uart_port, port);
	पूर्णांक ret;

	ret = sdio_uart_claim_func(port);
	अगर (ret)
		वापस;

	sdio_uart_stop_rx(port);

	/* Disable पूर्णांकerrupts from this port */
	sdio_release_irq(port->func);
	port->ier = 0;
	sdio_out(port, UART_IER, 0);

	sdio_uart_clear_mctrl(port, TIOCM_OUT2);

	/* Disable अवरोध condition and FIFOs. */
	port->lcr &= ~UART_LCR_SBC;
	sdio_out(port, UART_LCR, port->lcr);
	sdio_out(port, UART_FCR, UART_FCR_ENABLE_FIFO |
				 UART_FCR_CLEAR_RCVR |
				 UART_FCR_CLEAR_XMIT);
	sdio_out(port, UART_FCR, 0);

	sdio_disable_func(port->func);

	sdio_uart_release_func(port);
पूर्ण

अटल व्योम sdio_uart_port_destroy(काष्ठा tty_port *tport)
अणु
	काष्ठा sdio_uart_port *port =
		container_of(tport, काष्ठा sdio_uart_port, port);
	kfअगरo_मुक्त(&port->xmit_fअगरo);
	kमुक्त(port);
पूर्ण

/**
 *	sdio_uart_install	-	install method
 *	@driver: the driver in use (sdio_uart in our हाल)
 *	@tty: the tty being bound
 *
 *	Look up and bind the tty and the driver together. Initialize
 *	any needed निजी data (in our हाल the termios)
 */

अटल पूर्णांक sdio_uart_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक idx = tty->index;
	काष्ठा sdio_uart_port *port = sdio_uart_port_get(idx);
	पूर्णांक ret = tty_standard_install(driver, tty);

	अगर (ret == 0)
		/* This is the ref sdio_uart_port get provided */
		tty->driver_data = port;
	अन्यथा
		sdio_uart_port_put(port);
	वापस ret;
पूर्ण

/**
 *	sdio_uart_cleanup	-	called on the last tty kref drop
 *	@tty: the tty being destroyed
 *
 *	Called asynchronously when the last reference to the tty is dropped.
 *	We cannot destroy the tty->driver_data port kref until this poपूर्णांक
 */

अटल व्योम sdio_uart_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा sdio_uart_port *port = tty->driver_data;
	tty->driver_data = शून्य;	/* Bug trap */
	sdio_uart_port_put(port);
पूर्ण

/*
 *	Open/बंद/hangup is now entirely boilerplate
 */

अटल पूर्णांक sdio_uart_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा sdio_uart_port *port = tty->driver_data;
	वापस tty_port_खोलो(&port->port, tty, filp);
पूर्ण

अटल व्योम sdio_uart_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file * filp)
अणु
	काष्ठा sdio_uart_port *port = tty->driver_data;
	tty_port_बंद(&port->port, tty, filp);
पूर्ण

अटल व्योम sdio_uart_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा sdio_uart_port *port = tty->driver_data;
	tty_port_hangup(&port->port);
पूर्ण

अटल पूर्णांक sdio_uart_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf,
			   पूर्णांक count)
अणु
	काष्ठा sdio_uart_port *port = tty->driver_data;
	पूर्णांक ret;

	अगर (!port->func)
		वापस -ENODEV;

	ret = kfअगरo_in_locked(&port->xmit_fअगरo, buf, count, &port->ग_लिखो_lock);
	अगर (!(port->ier & UART_IER_THRI)) अणु
		पूर्णांक err = sdio_uart_claim_func(port);
		अगर (!err) अणु
			sdio_uart_start_tx(port);
			sdio_uart_irq(port->func);
			sdio_uart_release_func(port);
		पूर्ण अन्यथा
			ret = err;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sdio_uart_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा sdio_uart_port *port = tty->driver_data;
	वापस FIFO_SIZE - kfअगरo_len(&port->xmit_fअगरo);
पूर्ण

अटल पूर्णांक sdio_uart_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा sdio_uart_port *port = tty->driver_data;
	वापस kfअगरo_len(&port->xmit_fअगरo);
पूर्ण

अटल व्योम sdio_uart_send_xअक्षर(काष्ठा tty_काष्ठा *tty, अक्षर ch)
अणु
	काष्ठा sdio_uart_port *port = tty->driver_data;

	port->x_अक्षर = ch;
	अगर (ch && !(port->ier & UART_IER_THRI)) अणु
		अगर (sdio_uart_claim_func(port) != 0)
			वापस;
		sdio_uart_start_tx(port);
		sdio_uart_irq(port->func);
		sdio_uart_release_func(port);
	पूर्ण
पूर्ण

अटल व्योम sdio_uart_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा sdio_uart_port *port = tty->driver_data;

	अगर (!I_IXOFF(tty) && !C_CRTSCTS(tty))
		वापस;

	अगर (sdio_uart_claim_func(port) != 0)
		वापस;

	अगर (I_IXOFF(tty)) अणु
		port->x_अक्षर = STOP_CHAR(tty);
		sdio_uart_start_tx(port);
	पूर्ण

	अगर (C_CRTSCTS(tty))
		sdio_uart_clear_mctrl(port, TIOCM_RTS);

	sdio_uart_irq(port->func);
	sdio_uart_release_func(port);
पूर्ण

अटल व्योम sdio_uart_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा sdio_uart_port *port = tty->driver_data;

	अगर (!I_IXOFF(tty) && !C_CRTSCTS(tty))
		वापस;

	अगर (sdio_uart_claim_func(port) != 0)
		वापस;

	अगर (I_IXOFF(tty)) अणु
		अगर (port->x_अक्षर) अणु
			port->x_अक्षर = 0;
		पूर्ण अन्यथा अणु
			port->x_अक्षर = START_CHAR(tty);
			sdio_uart_start_tx(port);
		पूर्ण
	पूर्ण

	अगर (C_CRTSCTS(tty))
		sdio_uart_set_mctrl(port, TIOCM_RTS);

	sdio_uart_irq(port->func);
	sdio_uart_release_func(port);
पूर्ण

अटल व्योम sdio_uart_set_termios(काष्ठा tty_काष्ठा *tty,
						काष्ठा ktermios *old_termios)
अणु
	काष्ठा sdio_uart_port *port = tty->driver_data;
	अचिन्हित पूर्णांक cflag = tty->termios.c_cflag;

	अगर (sdio_uart_claim_func(port) != 0)
		वापस;

	sdio_uart_change_speed(port, &tty->termios, old_termios);

	/* Handle transition to B0 status */
	अगर ((old_termios->c_cflag & CBAUD) && !(cflag & CBAUD))
		sdio_uart_clear_mctrl(port, TIOCM_RTS | TIOCM_DTR);

	/* Handle transition away from B0 status */
	अगर (!(old_termios->c_cflag & CBAUD) && (cflag & CBAUD)) अणु
		अचिन्हित पूर्णांक mask = TIOCM_DTR;
		अगर (!(cflag & CRTSCTS) || !tty_throttled(tty))
			mask |= TIOCM_RTS;
		sdio_uart_set_mctrl(port, mask);
	पूर्ण

	/* Handle turning off CRTSCTS */
	अगर ((old_termios->c_cflag & CRTSCTS) && !(cflag & CRTSCTS)) अणु
		tty->hw_stopped = 0;
		sdio_uart_start_tx(port);
	पूर्ण

	/* Handle turning on CRTSCTS */
	अगर (!(old_termios->c_cflag & CRTSCTS) && (cflag & CRTSCTS)) अणु
		अगर (!(sdio_uart_get_mctrl(port) & TIOCM_CTS)) अणु
			tty->hw_stopped = 1;
			sdio_uart_stop_tx(port);
		पूर्ण
	पूर्ण

	sdio_uart_release_func(port);
पूर्ण

अटल पूर्णांक sdio_uart_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा sdio_uart_port *port = tty->driver_data;
	पूर्णांक result;

	result = sdio_uart_claim_func(port);
	अगर (result != 0)
		वापस result;

	अगर (अवरोध_state == -1)
		port->lcr |= UART_LCR_SBC;
	अन्यथा
		port->lcr &= ~UART_LCR_SBC;
	sdio_out(port, UART_LCR, port->lcr);

	sdio_uart_release_func(port);
	वापस 0;
पूर्ण

अटल पूर्णांक sdio_uart_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा sdio_uart_port *port = tty->driver_data;
	पूर्णांक result;

	result = sdio_uart_claim_func(port);
	अगर (!result) अणु
		result = port->mctrl | sdio_uart_get_mctrl(port);
		sdio_uart_release_func(port);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक sdio_uart_tiocmset(काष्ठा tty_काष्ठा *tty,
			      अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा sdio_uart_port *port = tty->driver_data;
	पूर्णांक result;

	result = sdio_uart_claim_func(port);
	अगर (!result) अणु
		sdio_uart_update_mctrl(port, set, clear);
		sdio_uart_release_func(port);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक sdio_uart_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i;

	seq_म_लिखो(m, "serinfo:1.0 driver%s%s revision:%s\n",
		       "", "", "");
	क्रम (i = 0; i < UART_NR; i++) अणु
		काष्ठा sdio_uart_port *port = sdio_uart_port_get(i);
		अगर (port) अणु
			seq_म_लिखो(m, "%d: uart:SDIO", i);
			अगर (capable(CAP_SYS_ADMIN)) अणु
				seq_म_लिखो(m, " tx:%d rx:%d",
					      port->icount.tx, port->icount.rx);
				अगर (port->icount.frame)
					seq_म_लिखो(m, " fe:%d",
						      port->icount.frame);
				अगर (port->icount.parity)
					seq_म_लिखो(m, " pe:%d",
						      port->icount.parity);
				अगर (port->icount.brk)
					seq_म_लिखो(m, " brk:%d",
						      port->icount.brk);
				अगर (port->icount.overrun)
					seq_म_लिखो(m, " oe:%d",
						      port->icount.overrun);
				अगर (port->icount.cts)
					seq_म_लिखो(m, " cts:%d",
						      port->icount.cts);
				अगर (port->icount.dsr)
					seq_म_लिखो(m, " dsr:%d",
						      port->icount.dsr);
				अगर (port->icount.rng)
					seq_म_लिखो(m, " rng:%d",
						      port->icount.rng);
				अगर (port->icount.dcd)
					seq_म_लिखो(m, " dcd:%d",
						      port->icount.dcd);
			पूर्ण
			sdio_uart_port_put(port);
			seq_अ_दो(m, '\n');
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tty_port_operations sdio_uart_port_ops = अणु
	.dtr_rts = uart_dtr_rts,
	.carrier_उठाओd = uart_carrier_उठाओd,
	.shutकरोwn = sdio_uart_shutकरोwn,
	.activate = sdio_uart_activate,
	.deकाष्ठा = sdio_uart_port_destroy,
पूर्ण;

अटल स्थिर काष्ठा tty_operations sdio_uart_ops = अणु
	.खोलो			= sdio_uart_खोलो,
	.बंद			= sdio_uart_बंद,
	.ग_लिखो			= sdio_uart_ग_लिखो,
	.ग_लिखो_room		= sdio_uart_ग_लिखो_room,
	.अक्षरs_in_buffer	= sdio_uart_अक्षरs_in_buffer,
	.send_xअक्षर		= sdio_uart_send_xअक्षर,
	.throttle		= sdio_uart_throttle,
	.unthrottle		= sdio_uart_unthrottle,
	.set_termios		= sdio_uart_set_termios,
	.hangup			= sdio_uart_hangup,
	.अवरोध_ctl		= sdio_uart_अवरोध_ctl,
	.tiocmget		= sdio_uart_tiocmget,
	.tiocmset		= sdio_uart_tiocmset,
	.install		= sdio_uart_install,
	.cleanup		= sdio_uart_cleanup,
	.proc_show		= sdio_uart_proc_show,
पूर्ण;

अटल काष्ठा tty_driver *sdio_uart_tty_driver;

अटल पूर्णांक sdio_uart_probe(काष्ठा sdio_func *func,
			   स्थिर काष्ठा sdio_device_id *id)
अणु
	काष्ठा sdio_uart_port *port;
	पूर्णांक ret;

	port = kzalloc(माप(काष्ठा sdio_uart_port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	अगर (func->class == SDIO_CLASS_UART) अणु
		pr_warn("%s: need info on UART class basic setup\n",
			sdio_func_id(func));
		kमुक्त(port);
		वापस -ENOSYS;
	पूर्ण अन्यथा अगर (func->class == SDIO_CLASS_GPS) अणु
		/*
		 * We need tuple 0x91.  It contains SUBTPL_SIOREG
		 * and SUBTPL_RCVCAPS.
		 */
		काष्ठा sdio_func_tuple *tpl;
		क्रम (tpl = func->tuples; tpl; tpl = tpl->next) अणु
			अगर (tpl->code != 0x91)
				जारी;
			अगर (tpl->size < 10)
				जारी;
			अगर (tpl->data[1] == 0)  /* SUBTPL_SIOREG */
				अवरोध;
		पूर्ण
		अगर (!tpl) अणु
			pr_warn("%s: can't find tuple 0x91 subtuple 0 (SUBTPL_SIOREG) for GPS class\n",
				sdio_func_id(func));
			kमुक्त(port);
			वापस -EINVAL;
		पूर्ण
		pr_debug("%s: Register ID = 0x%02x, Exp ID = 0x%02x\n",
		       sdio_func_id(func), tpl->data[2], tpl->data[3]);
		port->regs_offset = (tpl->data[4] << 0) |
				    (tpl->data[5] << 8) |
				    (tpl->data[6] << 16);
		pr_debug("%s: regs offset = 0x%x\n",
		       sdio_func_id(func), port->regs_offset);
		port->uartclk = tpl->data[7] * 115200;
		अगर (port->uartclk == 0)
			port->uartclk = 115200;
		pr_debug("%s: clk %d baudcode %u 4800-div %u\n",
		       sdio_func_id(func), port->uartclk,
		       tpl->data[7], tpl->data[8] | (tpl->data[9] << 8));
	पूर्ण अन्यथा अणु
		kमुक्त(port);
		वापस -EINVAL;
	पूर्ण

	port->func = func;
	sdio_set_drvdata(func, port);
	tty_port_init(&port->port);
	port->port.ops = &sdio_uart_port_ops;

	ret = sdio_uart_add_port(port);
	अगर (ret) अणु
		kमुक्त(port);
	पूर्ण अन्यथा अणु
		काष्ठा device *dev;
		dev = tty_port_रेजिस्टर_device(&port->port,
				sdio_uart_tty_driver, port->index, &func->dev);
		अगर (IS_ERR(dev)) अणु
			sdio_uart_port_हटाओ(port);
			ret = PTR_ERR(dev);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sdio_uart_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा sdio_uart_port *port = sdio_get_drvdata(func);

	tty_unरेजिस्टर_device(sdio_uart_tty_driver, port->index);
	sdio_uart_port_हटाओ(port);
पूर्ण

अटल स्थिर काष्ठा sdio_device_id sdio_uart_ids[] = अणु
	अणु SDIO_DEVICE_CLASS(SDIO_CLASS_UART)		पूर्ण,
	अणु SDIO_DEVICE_CLASS(SDIO_CLASS_GPS)		पूर्ण,
	अणु /* end: all zeroes */				पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(sdio, sdio_uart_ids);

अटल काष्ठा sdio_driver sdio_uart_driver = अणु
	.probe		= sdio_uart_probe,
	.हटाओ		= sdio_uart_हटाओ,
	.name		= "sdio_uart",
	.id_table	= sdio_uart_ids,
पूर्ण;

अटल पूर्णांक __init sdio_uart_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा tty_driver *tty_drv;

	sdio_uart_tty_driver = tty_drv = alloc_tty_driver(UART_NR);
	अगर (!tty_drv)
		वापस -ENOMEM;

	tty_drv->driver_name = "sdio_uart";
	tty_drv->name =   "ttySDIO";
	tty_drv->major = 0;  /* dynamically allocated */
	tty_drv->minor_start = 0;
	tty_drv->type = TTY_DRIVER_TYPE_SERIAL;
	tty_drv->subtype = SERIAL_TYPE_NORMAL;
	tty_drv->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	tty_drv->init_termios = tty_std_termios;
	tty_drv->init_termios.c_cflag = B4800 | CS8 | CREAD | HUPCL | CLOCAL;
	tty_drv->init_termios.c_ispeed = 4800;
	tty_drv->init_termios.c_ospeed = 4800;
	tty_set_operations(tty_drv, &sdio_uart_ops);

	ret = tty_रेजिस्टर_driver(tty_drv);
	अगर (ret)
		जाओ err1;

	ret = sdio_रेजिस्टर_driver(&sdio_uart_driver);
	अगर (ret)
		जाओ err2;

	वापस 0;

err2:
	tty_unरेजिस्टर_driver(tty_drv);
err1:
	put_tty_driver(tty_drv);
	वापस ret;
पूर्ण

अटल व्योम __निकास sdio_uart_निकास(व्योम)
अणु
	sdio_unरेजिस्टर_driver(&sdio_uart_driver);
	tty_unरेजिस्टर_driver(sdio_uart_tty_driver);
	put_tty_driver(sdio_uart_tty_driver);
पूर्ण

module_init(sdio_uart_init);
module_निकास(sdio_uart_निकास);

MODULE_AUTHOR("Nicolas Pitre");
MODULE_LICENSE("GPL");
