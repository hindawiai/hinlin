<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dz.c: Serial port driver क्रम DECstations equipped
 *       with the DZ chipset.
 *
 * Copyright (C) 1998 Olivier A. D. Lebaillअगर
 *
 * Email: olivier.lebaillअगर@अगरrsys.com
 *
 * Copyright (C) 2004, 2006, 2007  Maciej W. Rozycki
 *
 * [31-AUG-98] triemer
 * Changed IRQ to use Harald's dec पूर्णांकernals पूर्णांकerrupts.h
 * हटाओd base_addr code - moving address assignment to setup.c
 * Changed name of dz_init to rs_init to be consistent with tc code
 * [13-NOV-98] triemer fixed code to receive अक्षरacters
 *    after patches by harald to irq code.
 * [09-JAN-99] triemer minor fix क्रम schedule - due to removal of समयout
 *            field from "current" - somewhere between 2.1.121 and 2.1.131
 Qua Jun 27 15:02:26 BRT 2001
 * [27-JUN-2001] Arnalकरो Carvalho de Melo <acme@conectiva.com.br> - cleanups
 *
 * Parts (C) 1999 David Airlie, airlied@linux.ie
 * [07-SEP-99] Bugfixes
 *
 * [06-Jan-2002] Russell King <rmk@arm.linux.org.uk>
 * Converted to new serial core
 */

#अघोषित DEBUG_DZ

#समावेश <linux/bitops.h>
#समावेश <linux/compiler.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/major.h>
#समावेश <linux/module.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/पन.स>

#समावेश <यंत्र/dec/पूर्णांकerrupts.h>
#समावेश <यंत्र/dec/kn01.h>
#समावेश <यंत्र/dec/kn02.h>
#समावेश <यंत्र/dec/machtype.h>
#समावेश <यंत्र/dec/prom.h>
#समावेश <यंत्र/dec/प्रणाली.h>

#समावेश "dz.h"


MODULE_DESCRIPTION("DECstation DZ serial driver");
MODULE_LICENSE("GPL");


अटल अक्षर dz_name[] __initdata = "DECstation DZ serial driver version ";
अटल अक्षर dz_version[] __initdata = "1.04";

काष्ठा dz_port अणु
	काष्ठा dz_mux		*mux;
	काष्ठा uart_port	port;
	अचिन्हित पूर्णांक		cflag;
पूर्ण;

काष्ठा dz_mux अणु
	काष्ठा dz_port		dport[DZ_NB_PORT];
	atomic_t		map_guard;
	atomic_t		irq_guard;
	पूर्णांक			initialised;
पूर्ण;

अटल काष्ठा dz_mux dz_mux;

अटल अंतरभूत काष्ठा dz_port *to_dport(काष्ठा uart_port *uport)
अणु
	वापस container_of(uport, काष्ठा dz_port, port);
पूर्ण

/*
 * ------------------------------------------------------------
 * dz_in () and dz_out ()
 *
 * These routines are used to access the रेजिस्टरs of the DZ
 * chip, hiding relocation dअगरferences between implementation.
 * ------------------------------------------------------------
 */

अटल u16 dz_in(काष्ठा dz_port *dport, अचिन्हित offset)
अणु
	व्योम __iomem *addr = dport->port.membase + offset;

	वापस पढ़ोw(addr);
पूर्ण

अटल व्योम dz_out(काष्ठा dz_port *dport, अचिन्हित offset, u16 value)
अणु
	व्योम __iomem *addr = dport->port.membase + offset;

	ग_लिखोw(value, addr);
पूर्ण

/*
 * ------------------------------------------------------------
 * rs_stop () and rs_start ()
 *
 * These routines are called beक्रमe setting or resetting
 * tty->stopped. They enable or disable transmitter पूर्णांकerrupts,
 * as necessary.
 * ------------------------------------------------------------
 */

अटल व्योम dz_stop_tx(काष्ठा uart_port *uport)
अणु
	काष्ठा dz_port *dport = to_dport(uport);
	u16 पंचांगp, mask = 1 << dport->port.line;

	पंचांगp = dz_in(dport, DZ_TCR);	/* पढ़ो the TX flag */
	पंचांगp &= ~mask;			/* clear the TX flag */
	dz_out(dport, DZ_TCR, पंचांगp);
पूर्ण

अटल व्योम dz_start_tx(काष्ठा uart_port *uport)
अणु
	काष्ठा dz_port *dport = to_dport(uport);
	u16 पंचांगp, mask = 1 << dport->port.line;

	पंचांगp = dz_in(dport, DZ_TCR);	/* पढ़ो the TX flag */
	पंचांगp |= mask;			/* set the TX flag */
	dz_out(dport, DZ_TCR, पंचांगp);
पूर्ण

अटल व्योम dz_stop_rx(काष्ठा uart_port *uport)
अणु
	काष्ठा dz_port *dport = to_dport(uport);

	dport->cflag &= ~DZ_RXENAB;
	dz_out(dport, DZ_LPR, dport->cflag);
पूर्ण

/*
 * ------------------------------------------------------------
 *
 * Here start the पूर्णांकerrupt handling routines.  All of the following
 * subroutines are declared as अंतरभूत and are folded पूर्णांकo
 * dz_पूर्णांकerrupt.  They were separated out क्रम पढ़ोability's sake.
 *
 * Note: dz_पूर्णांकerrupt() is a "fast" पूर्णांकerrupt, which means that it
 * runs with पूर्णांकerrupts turned off.  People who may want to modअगरy
 * dz_पूर्णांकerrupt() should try to keep the पूर्णांकerrupt handler as fast as
 * possible.  After you are करोne making modअगरications, it is not a bad
 * idea to करो:
 *
 *	make drivers/serial/dz.s
 *
 * and look at the resulting assemble code in dz.s.
 *
 * ------------------------------------------------------------
 */

/*
 * ------------------------------------------------------------
 * receive_अक्षर ()
 *
 * This routine deals with inमाला_दो from any lines.
 * ------------------------------------------------------------
 */
अटल अंतरभूत व्योम dz_receive_अक्षरs(काष्ठा dz_mux *mux)
अणु
	काष्ठा uart_port *uport;
	काष्ठा dz_port *dport = &mux->dport[0];
	काष्ठा uart_icount *icount;
	पूर्णांक lines_rx[DZ_NB_PORT] = अणु [0 ... DZ_NB_PORT - 1] = 0 पूर्ण;
	अचिन्हित अक्षर ch, flag;
	u16 status;
	पूर्णांक i;

	जबतक ((status = dz_in(dport, DZ_RBUF)) & DZ_DVAL) अणु
		dport = &mux->dport[LINE(status)];
		uport = &dport->port;

		ch = UCHAR(status);		/* grab the अक्षर */
		flag = TTY_NORMAL;

		icount = &uport->icount;
		icount->rx++;

		अगर (unlikely(status & (DZ_OERR | DZ_FERR | DZ_PERR))) अणु

			/*
			 * There is no separate BREAK status bit, so treat
			 * null अक्षरacters with framing errors as BREAKs;
			 * normally, otherwise.  For this move the Framing
			 * Error bit to a simulated BREAK bit.
			 */
			अगर (!ch) अणु
				status |= (status & DZ_FERR) >>
					  (ffs(DZ_FERR) - ffs(DZ_BREAK));
				status &= ~DZ_FERR;
			पूर्ण

			/* Handle SysRq/SAK & keep track of the statistics. */
			अगर (status & DZ_BREAK) अणु
				icount->brk++;
				अगर (uart_handle_अवरोध(uport))
					जारी;
			पूर्ण अन्यथा अगर (status & DZ_FERR)
				icount->frame++;
			अन्यथा अगर (status & DZ_PERR)
				icount->parity++;
			अगर (status & DZ_OERR)
				icount->overrun++;

			status &= uport->पढ़ो_status_mask;
			अगर (status & DZ_BREAK)
				flag = TTY_BREAK;
			अन्यथा अगर (status & DZ_FERR)
				flag = TTY_FRAME;
			अन्यथा अगर (status & DZ_PERR)
				flag = TTY_PARITY;

		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(uport, ch))
			जारी;

		uart_insert_अक्षर(uport, status, DZ_OERR, ch, flag);
		lines_rx[LINE(status)] = 1;
	पूर्ण
	क्रम (i = 0; i < DZ_NB_PORT; i++)
		अगर (lines_rx[i])
			tty_flip_buffer_push(&mux->dport[i].port.state->port);
पूर्ण

/*
 * ------------------------------------------------------------
 * transmit_अक्षर ()
 *
 * This routine deals with outमाला_दो to any lines.
 * ------------------------------------------------------------
 */
अटल अंतरभूत व्योम dz_transmit_अक्षरs(काष्ठा dz_mux *mux)
अणु
	काष्ठा dz_port *dport = &mux->dport[0];
	काष्ठा circ_buf *xmit;
	अचिन्हित अक्षर पंचांगp;
	u16 status;

	status = dz_in(dport, DZ_CSR);
	dport = &mux->dport[LINE(status)];
	xmit = &dport->port.state->xmit;

	अगर (dport->port.x_अक्षर) अणु		/* XON/XOFF अक्षरs */
		dz_out(dport, DZ_TDR, dport->port.x_अक्षर);
		dport->port.icount.tx++;
		dport->port.x_अक्षर = 0;
		वापस;
	पूर्ण
	/* If nothing to करो or stopped or hardware stopped. */
	अगर (uart_circ_empty(xmit) || uart_tx_stopped(&dport->port)) अणु
		spin_lock(&dport->port.lock);
		dz_stop_tx(&dport->port);
		spin_unlock(&dport->port.lock);
		वापस;
	पूर्ण

	/*
	 * If something to करो... (remember the dz has no output fअगरo,
	 * so we go one अक्षर at a समय) :-<
	 */
	पंचांगp = xmit->buf[xmit->tail];
	xmit->tail = (xmit->tail + 1) & (DZ_XMIT_SIZE - 1);
	dz_out(dport, DZ_TDR, पंचांगp);
	dport->port.icount.tx++;

	अगर (uart_circ_अक्षरs_pending(xmit) < DZ_WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&dport->port);

	/* Are we are करोne. */
	अगर (uart_circ_empty(xmit)) अणु
		spin_lock(&dport->port.lock);
		dz_stop_tx(&dport->port);
		spin_unlock(&dport->port.lock);
	पूर्ण
पूर्ण

/*
 * ------------------------------------------------------------
 * check_modem_status()
 *
 * DS 3100 & 5100: Only valid क्रम the MODEM line, duh!
 * DS 5000/200: Valid क्रम the MODEM and PRINTER line.
 * ------------------------------------------------------------
 */
अटल अंतरभूत व्योम check_modem_status(काष्ठा dz_port *dport)
अणु
	/*
	 * FIXME:
	 * 1. No status change पूर्णांकerrupt; use a समयr.
	 * 2. Handle the 3100/5000 as appropriate. --macro
	 */
	u16 status;

	/* If not the modem line just वापस.  */
	अगर (dport->port.line != DZ_MODEM)
		वापस;

	status = dz_in(dport, DZ_MSR);

	/* it's easy, since DSR2 is the only bit in the रेजिस्टर */
	अगर (status)
		dport->port.icount.dsr++;
पूर्ण

/*
 * ------------------------------------------------------------
 * dz_पूर्णांकerrupt ()
 *
 * this is the मुख्य पूर्णांकerrupt routine क्रम the DZ chip.
 * It deals with the multiple ports.
 * ------------------------------------------------------------
 */
अटल irqवापस_t dz_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dz_mux *mux = dev_id;
	काष्ठा dz_port *dport = &mux->dport[0];
	u16 status;

	/* get the reason why we just got an irq */
	status = dz_in(dport, DZ_CSR);

	अगर ((status & (DZ_RDONE | DZ_RIE)) == (DZ_RDONE | DZ_RIE))
		dz_receive_अक्षरs(mux);

	अगर ((status & (DZ_TRDY | DZ_TIE)) == (DZ_TRDY | DZ_TIE))
		dz_transmit_अक्षरs(mux);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * -------------------------------------------------------------------
 * Here ends the DZ पूर्णांकerrupt routines.
 * -------------------------------------------------------------------
 */

अटल अचिन्हित पूर्णांक dz_get_mctrl(काष्ठा uart_port *uport)
अणु
	/*
	 * FIXME: Handle the 3100/5000 as appropriate. --macro
	 */
	काष्ठा dz_port *dport = to_dport(uport);
	अचिन्हित पूर्णांक mctrl = TIOCM_CAR | TIOCM_DSR | TIOCM_CTS;

	अगर (dport->port.line == DZ_MODEM) अणु
		अगर (dz_in(dport, DZ_MSR) & DZ_MODEM_DSR)
			mctrl &= ~TIOCM_DSR;
	पूर्ण

	वापस mctrl;
पूर्ण

अटल व्योम dz_set_mctrl(काष्ठा uart_port *uport, अचिन्हित पूर्णांक mctrl)
अणु
	/*
	 * FIXME: Handle the 3100/5000 as appropriate. --macro
	 */
	काष्ठा dz_port *dport = to_dport(uport);
	u16 पंचांगp;

	अगर (dport->port.line == DZ_MODEM) अणु
		पंचांगp = dz_in(dport, DZ_TCR);
		अगर (mctrl & TIOCM_DTR)
			पंचांगp &= ~DZ_MODEM_DTR;
		अन्यथा
			पंचांगp |= DZ_MODEM_DTR;
		dz_out(dport, DZ_TCR, पंचांगp);
	पूर्ण
पूर्ण

/*
 * -------------------------------------------------------------------
 * startup ()
 *
 * various initialization tasks
 * -------------------------------------------------------------------
 */
अटल पूर्णांक dz_startup(काष्ठा uart_port *uport)
अणु
	काष्ठा dz_port *dport = to_dport(uport);
	काष्ठा dz_mux *mux = dport->mux;
	अचिन्हित दीर्घ flags;
	पूर्णांक irq_guard;
	पूर्णांक ret;
	u16 पंचांगp;

	irq_guard = atomic_add_वापस(1, &mux->irq_guard);
	अगर (irq_guard != 1)
		वापस 0;

	ret = request_irq(dport->port.irq, dz_पूर्णांकerrupt,
			  IRQF_SHARED, "dz", mux);
	अगर (ret) अणु
		atomic_add(-1, &mux->irq_guard);
		prपूर्णांकk(KERN_ERR "dz: Cannot get IRQ %d!\n", dport->port.irq);
		वापस ret;
	पूर्ण

	spin_lock_irqsave(&dport->port.lock, flags);

	/* Enable पूर्णांकerrupts.  */
	पंचांगp = dz_in(dport, DZ_CSR);
	पंचांगp |= DZ_RIE | DZ_TIE;
	dz_out(dport, DZ_CSR, पंचांगp);

	spin_unlock_irqrestore(&dport->port.lock, flags);

	वापस 0;
पूर्ण

/*
 * -------------------------------------------------------------------
 * shutकरोwn ()
 *
 * This routine will shutकरोwn a serial port; पूर्णांकerrupts are disabled, and
 * DTR is dropped अगर the hangup on बंद termio flag is on.
 * -------------------------------------------------------------------
 */
अटल व्योम dz_shutकरोwn(काष्ठा uart_port *uport)
अणु
	काष्ठा dz_port *dport = to_dport(uport);
	काष्ठा dz_mux *mux = dport->mux;
	अचिन्हित दीर्घ flags;
	पूर्णांक irq_guard;
	u16 पंचांगp;

	spin_lock_irqsave(&dport->port.lock, flags);
	dz_stop_tx(&dport->port);
	spin_unlock_irqrestore(&dport->port.lock, flags);

	irq_guard = atomic_add_वापस(-1, &mux->irq_guard);
	अगर (!irq_guard) अणु
		/* Disable पूर्णांकerrupts.  */
		पंचांगp = dz_in(dport, DZ_CSR);
		पंचांगp &= ~(DZ_RIE | DZ_TIE);
		dz_out(dport, DZ_CSR, पंचांगp);

		मुक्त_irq(dport->port.irq, mux);
	पूर्ण
पूर्ण

/*
 * -------------------------------------------------------------------
 * dz_tx_empty() -- get the transmitter empty status
 *
 * Purpose: Let user call ioctl() to get info when the UART physically
 *          is emptied.  On bus types like RS485, the transmitter must
 *          release the bus after transmitting. This must be करोne when
 *          the transmit shअगरt रेजिस्टर is empty, not be करोne when the
 *          transmit holding रेजिस्टर is empty.  This functionality
 *          allows an RS485 driver to be written in user space.
 * -------------------------------------------------------------------
 */
अटल अचिन्हित पूर्णांक dz_tx_empty(काष्ठा uart_port *uport)
अणु
	काष्ठा dz_port *dport = to_dport(uport);
	अचिन्हित लघु पंचांगp, mask = 1 << dport->port.line;

	पंचांगp = dz_in(dport, DZ_TCR);
	पंचांगp &= mask;

	वापस पंचांगp ? 0 : TIOCSER_TEMT;
पूर्ण

अटल व्योम dz_अवरोध_ctl(काष्ठा uart_port *uport, पूर्णांक अवरोध_state)
अणु
	/*
	 * FIXME: Can't access BREAK bits in TDR easily;
	 * reuse the code क्रम polled TX. --macro
	 */
	काष्ठा dz_port *dport = to_dport(uport);
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु पंचांगp, mask = 1 << dport->port.line;

	spin_lock_irqsave(&uport->lock, flags);
	पंचांगp = dz_in(dport, DZ_TCR);
	अगर (अवरोध_state)
		पंचांगp |= mask;
	अन्यथा
		पंचांगp &= ~mask;
	dz_out(dport, DZ_TCR, पंचांगp);
	spin_unlock_irqrestore(&uport->lock, flags);
पूर्ण

अटल पूर्णांक dz_encode_baud_rate(अचिन्हित पूर्णांक baud)
अणु
	चयन (baud) अणु
	हाल 50:
		वापस DZ_B50;
	हाल 75:
		वापस DZ_B75;
	हाल 110:
		वापस DZ_B110;
	हाल 134:
		वापस DZ_B134;
	हाल 150:
		वापस DZ_B150;
	हाल 300:
		वापस DZ_B300;
	हाल 600:
		वापस DZ_B600;
	हाल 1200:
		वापस DZ_B1200;
	हाल 1800:
		वापस DZ_B1800;
	हाल 2000:
		वापस DZ_B2000;
	हाल 2400:
		वापस DZ_B2400;
	हाल 3600:
		वापस DZ_B3600;
	हाल 4800:
		वापस DZ_B4800;
	हाल 7200:
		वापस DZ_B7200;
	हाल 9600:
		वापस DZ_B9600;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण


अटल व्योम dz_reset(काष्ठा dz_port *dport)
अणु
	काष्ठा dz_mux *mux = dport->mux;

	अगर (mux->initialised)
		वापस;

	dz_out(dport, DZ_CSR, DZ_CLR);
	जबतक (dz_in(dport, DZ_CSR) & DZ_CLR);
	iob();

	/* Enable scanning.  */
	dz_out(dport, DZ_CSR, DZ_MSE);

	mux->initialised = 1;
पूर्ण

अटल व्योम dz_set_termios(काष्ठा uart_port *uport, काष्ठा ktermios *termios,
			   काष्ठा ktermios *old_termios)
अणु
	काष्ठा dz_port *dport = to_dport(uport);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक cflag, baud;
	पूर्णांक bflag;

	cflag = dport->port.line;

	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		cflag |= DZ_CS5;
		अवरोध;
	हाल CS6:
		cflag |= DZ_CS6;
		अवरोध;
	हाल CS7:
		cflag |= DZ_CS7;
		अवरोध;
	हाल CS8:
	शेष:
		cflag |= DZ_CS8;
	पूर्ण

	अगर (termios->c_cflag & CSTOPB)
		cflag |= DZ_CSTOPB;
	अगर (termios->c_cflag & PARENB)
		cflag |= DZ_PARENB;
	अगर (termios->c_cflag & PARODD)
		cflag |= DZ_PARODD;

	baud = uart_get_baud_rate(uport, termios, old_termios, 50, 9600);
	bflag = dz_encode_baud_rate(baud);
	अगर (bflag < 0)	अणु			/* Try to keep unchanged.  */
		baud = uart_get_baud_rate(uport, old_termios, शून्य, 50, 9600);
		bflag = dz_encode_baud_rate(baud);
		अगर (bflag < 0)	अणु		/* Resort to 9600.  */
			baud = 9600;
			bflag = DZ_B9600;
		पूर्ण
		tty_termios_encode_baud_rate(termios, baud, baud);
	पूर्ण
	cflag |= bflag;

	अगर (termios->c_cflag & CREAD)
		cflag |= DZ_RXENAB;

	spin_lock_irqsave(&dport->port.lock, flags);

	uart_update_समयout(uport, termios->c_cflag, baud);

	dz_out(dport, DZ_LPR, cflag);
	dport->cflag = cflag;

	/* setup accept flag */
	dport->port.पढ़ो_status_mask = DZ_OERR;
	अगर (termios->c_अगरlag & INPCK)
		dport->port.पढ़ो_status_mask |= DZ_FERR | DZ_PERR;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		dport->port.पढ़ो_status_mask |= DZ_BREAK;

	/* अक्षरacters to ignore */
	uport->ignore_status_mask = 0;
	अगर ((termios->c_अगरlag & (IGNPAR | IGNBRK)) == (IGNPAR | IGNBRK))
		dport->port.ignore_status_mask |= DZ_OERR;
	अगर (termios->c_अगरlag & IGNPAR)
		dport->port.ignore_status_mask |= DZ_FERR | DZ_PERR;
	अगर (termios->c_अगरlag & IGNBRK)
		dport->port.ignore_status_mask |= DZ_BREAK;

	spin_unlock_irqrestore(&dport->port.lock, flags);
पूर्ण

/*
 * Hack alert!
 * Required solely so that the initial PROM-based console
 * works undisturbed in parallel with this one.
 */
अटल व्योम dz_pm(काष्ठा uart_port *uport, अचिन्हित पूर्णांक state,
		  अचिन्हित पूर्णांक oldstate)
अणु
	काष्ठा dz_port *dport = to_dport(uport);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dport->port.lock, flags);
	अगर (state < 3)
		dz_start_tx(&dport->port);
	अन्यथा
		dz_stop_tx(&dport->port);
	spin_unlock_irqrestore(&dport->port.lock, flags);
पूर्ण


अटल स्थिर अक्षर *dz_type(काष्ठा uart_port *uport)
अणु
	वापस "DZ";
पूर्ण

अटल व्योम dz_release_port(काष्ठा uart_port *uport)
अणु
	काष्ठा dz_mux *mux = to_dport(uport)->mux;
	पूर्णांक map_guard;

	iounmap(uport->membase);
	uport->membase = शून्य;

	map_guard = atomic_add_वापस(-1, &mux->map_guard);
	अगर (!map_guard)
		release_mem_region(uport->mapbase, dec_kn_slot_size);
पूर्ण

अटल पूर्णांक dz_map_port(काष्ठा uart_port *uport)
अणु
	अगर (!uport->membase)
		uport->membase = ioremap(uport->mapbase,
						 dec_kn_slot_size);
	अगर (!uport->membase) अणु
		prपूर्णांकk(KERN_ERR "dz: Cannot map MMIO\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dz_request_port(काष्ठा uart_port *uport)
अणु
	काष्ठा dz_mux *mux = to_dport(uport)->mux;
	पूर्णांक map_guard;
	पूर्णांक ret;

	map_guard = atomic_add_वापस(1, &mux->map_guard);
	अगर (map_guard == 1) अणु
		अगर (!request_mem_region(uport->mapbase, dec_kn_slot_size,
					"dz")) अणु
			atomic_add(-1, &mux->map_guard);
			prपूर्णांकk(KERN_ERR
			       "dz: Unable to reserve MMIO resource\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	ret = dz_map_port(uport);
	अगर (ret) अणु
		map_guard = atomic_add_वापस(-1, &mux->map_guard);
		अगर (!map_guard)
			release_mem_region(uport->mapbase, dec_kn_slot_size);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dz_config_port(काष्ठा uart_port *uport, पूर्णांक flags)
अणु
	काष्ठा dz_port *dport = to_dport(uport);

	अगर (flags & UART_CONFIG_TYPE) अणु
		अगर (dz_request_port(uport))
			वापस;

		uport->type = PORT_DZ;

		dz_reset(dport);
	पूर्ण
पूर्ण

/*
 * Verअगरy the new serial_काष्ठा (क्रम TIOCSSERIAL).
 */
अटल पूर्णांक dz_verअगरy_port(काष्ठा uart_port *uport, काष्ठा serial_काष्ठा *ser)
अणु
	पूर्णांक ret = 0;

	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_DZ)
		ret = -EINVAL;
	अगर (ser->irq != uport->irq)
		ret = -EINVAL;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा uart_ops dz_ops = अणु
	.tx_empty	= dz_tx_empty,
	.get_mctrl	= dz_get_mctrl,
	.set_mctrl	= dz_set_mctrl,
	.stop_tx	= dz_stop_tx,
	.start_tx	= dz_start_tx,
	.stop_rx	= dz_stop_rx,
	.अवरोध_ctl	= dz_अवरोध_ctl,
	.startup	= dz_startup,
	.shutकरोwn	= dz_shutकरोwn,
	.set_termios	= dz_set_termios,
	.pm		= dz_pm,
	.type		= dz_type,
	.release_port	= dz_release_port,
	.request_port	= dz_request_port,
	.config_port	= dz_config_port,
	.verअगरy_port	= dz_verअगरy_port,
पूर्ण;

अटल व्योम __init dz_init_ports(व्योम)
अणु
	अटल पूर्णांक first = 1;
	अचिन्हित दीर्घ base;
	पूर्णांक line;

	अगर (!first)
		वापस;
	first = 0;

	अगर (mips_machtype == MACH_DS23100 || mips_machtype == MACH_DS5100)
		base = dec_kn_slot_base + KN01_DZ11;
	अन्यथा
		base = dec_kn_slot_base + KN02_DZ11;

	क्रम (line = 0; line < DZ_NB_PORT; line++) अणु
		काष्ठा dz_port *dport = &dz_mux.dport[line];
		काष्ठा uart_port *uport = &dport->port;

		dport->mux	= &dz_mux;

		uport->irq	= dec_पूर्णांकerrupt[DEC_IRQ_DZ11];
		uport->fअगरosize	= 1;
		uport->iotype	= UPIO_MEM;
		uport->flags	= UPF_BOOT_AUTOCONF;
		uport->ops	= &dz_ops;
		uport->line	= line;
		uport->mapbase	= base;
		uport->has_sysrq = IS_ENABLED(CONFIG_SERIAL_DZ_CONSOLE);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SERIAL_DZ_CONSOLE
/*
 * -------------------------------------------------------------------
 * dz_console_अक्षर_दो() -- transmit a अक्षरacter
 *
 * Polled transmission.  This is tricky.  We need to mask transmit
 * पूर्णांकerrupts so that they करो not पूर्णांकerfere, enable the transmitter
 * क्रम the line requested and then रुको till the transmit scanner
 * requests data क्रम this line.  But it may request data क्रम another
 * line first, in which हाल we have to disable its transmitter and
 * repeat रुकोing till our line pops up.  Only then the अक्षरacter may
 * be transmitted.  Finally, the state of the transmitter mask is
 * restored.  Welcome to the world of PDP-11!
 * -------------------------------------------------------------------
 */
अटल व्योम dz_console_अक्षर_दो(काष्ठा uart_port *uport, पूर्णांक ch)
अणु
	काष्ठा dz_port *dport = to_dport(uport);
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु csr, tcr, trdy, mask;
	पूर्णांक loops = 10000;

	spin_lock_irqsave(&dport->port.lock, flags);
	csr = dz_in(dport, DZ_CSR);
	dz_out(dport, DZ_CSR, csr & ~DZ_TIE);
	tcr = dz_in(dport, DZ_TCR);
	tcr |= 1 << dport->port.line;
	mask = tcr;
	dz_out(dport, DZ_TCR, mask);
	iob();
	spin_unlock_irqrestore(&dport->port.lock, flags);

	करो अणु
		trdy = dz_in(dport, DZ_CSR);
		अगर (!(trdy & DZ_TRDY))
			जारी;
		trdy = (trdy & DZ_TLINE) >> 8;
		अगर (trdy == dport->port.line)
			अवरोध;
		mask &= ~(1 << trdy);
		dz_out(dport, DZ_TCR, mask);
		iob();
		udelay(2);
	पूर्ण जबतक (--loops);

	अगर (loops)				/* Cannot send otherwise. */
		dz_out(dport, DZ_TDR, ch);

	dz_out(dport, DZ_TCR, tcr);
	dz_out(dport, DZ_CSR, csr);
पूर्ण

/*
 * -------------------------------------------------------------------
 * dz_console_prपूर्णांक ()
 *
 * dz_console_prपूर्णांक is रेजिस्टरed क्रम prपूर्णांकk.
 * The console must be locked when we get here.
 * -------------------------------------------------------------------
 */
अटल व्योम dz_console_prपूर्णांक(काष्ठा console *co,
			     स्थिर अक्षर *str,
			     अचिन्हित पूर्णांक count)
अणु
	काष्ठा dz_port *dport = &dz_mux.dport[co->index];
#अगर_घोषित DEBUG_DZ
	prom_म_लिखो((अक्षर *) str);
#पूर्ण_अगर
	uart_console_ग_लिखो(&dport->port, str, count, dz_console_अक्षर_दो);
पूर्ण

अटल पूर्णांक __init dz_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा dz_port *dport = &dz_mux.dport[co->index];
	काष्ठा uart_port *uport = &dport->port;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	पूर्णांक ret;

	ret = dz_map_port(uport);
	अगर (ret)
		वापस ret;

	spin_lock_init(&dport->port.lock);	/* For dz_pm().  */

	dz_reset(dport);
	dz_pm(uport, 0, -1);

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(&dport->port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver dz_reg;
अटल काष्ठा console dz_console = अणु
	.name	= "ttyS",
	.ग_लिखो	= dz_console_prपूर्णांक,
	.device	= uart_console_device,
	.setup	= dz_console_setup,
	.flags	= CON_PRINTBUFFER,
	.index	= -1,
	.data	= &dz_reg,
पूर्ण;

अटल पूर्णांक __init dz_serial_console_init(व्योम)
अणु
	अगर (!IOASIC) अणु
		dz_init_ports();
		रेजिस्टर_console(&dz_console);
		वापस 0;
	पूर्ण अन्यथा
		वापस -ENXIO;
पूर्ण

console_initcall(dz_serial_console_init);

#घोषणा SERIAL_DZ_CONSOLE	&dz_console
#अन्यथा
#घोषणा SERIAL_DZ_CONSOLE	शून्य
#पूर्ण_अगर /* CONFIG_SERIAL_DZ_CONSOLE */

अटल काष्ठा uart_driver dz_reg = अणु
	.owner			= THIS_MODULE,
	.driver_name		= "serial",
	.dev_name		= "ttyS",
	.major			= TTY_MAJOR,
	.minor			= 64,
	.nr			= DZ_NB_PORT,
	.cons			= SERIAL_DZ_CONSOLE,
पूर्ण;

अटल पूर्णांक __init dz_init(व्योम)
अणु
	पूर्णांक ret, i;

	अगर (IOASIC)
		वापस -ENXIO;

	prपूर्णांकk("%s%s\n", dz_name, dz_version);

	dz_init_ports();

	ret = uart_रेजिस्टर_driver(&dz_reg);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < DZ_NB_PORT; i++)
		uart_add_one_port(&dz_reg, &dz_mux.dport[i].port);

	वापस 0;
पूर्ण

module_init(dz_init);
