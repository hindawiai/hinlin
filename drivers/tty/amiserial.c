<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Serial driver क्रम the amiga builtin port.
 *
 * This code was created by taking serial.c version 4.30 from kernel
 * release 2.3.22, replacing all hardware related stuff with the
 * corresponding amiga hardware actions, and removing all irrelevant
 * code. As a consequence, it uses many of the स्थिरants and names
 * associated with the रेजिस्टरs and bits of 16550 compatible UARTS -
 * but only to keep track of status, etc in the state variables. It
 * was करोne this was to make it easier to keep the code in line with
 * (non hardware specअगरic) changes to serial.c.
 *
 * The port is रेजिस्टरed with the tty driver as minor device 64, and
 * thereक्रमe other ports should should only use 65 upwards.
 *
 * Riअक्षरd Lucock 28/12/99
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  Copyright (C) 1992, 1993, 1994, 1995, 1996, 1997, 
 * 		1998, 1999  Theoकरोre Ts'o
 *
 */

#समावेश <linux/delay.h>

/* Set of debugging defines */

#अघोषित SERIAL_DEBUG_INTR
#अघोषित SERIAL_DEBUG_OPEN
#अघोषित SERIAL_DEBUG_FLOW
#अघोषित SERIAL_DEBUG_RS_WAIT_UNTIL_SENT

/* Sanity checks */

#अगर defined(MODULE) && defined(SERIAL_DEBUG_MCOUNT)
#घोषणा DBG_CNT(s) prपूर्णांकk("(%s): [%x] refc=%d, serc=%d, ttyc=%d -> %s\n", \
 tty->name, (info->tport.flags), serial_driver->refcount,info->count,tty->count,s)
#अन्यथा
#घोषणा DBG_CNT(s)
#पूर्ण_अगर

/*
 * End of serial driver configuration section.
 */

#समावेश <linux/module.h>

#समावेश <linux/types.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_reg.h>
अटल अक्षर *serial_version = "4.30";

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/console.h>
#समावेश <linux/major.h>
#समावेश <linux/माला.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mm.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/setup.h>


#समावेश <यंत्र/irq.h>

#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>

काष्ठा serial_state अणु
	काष्ठा tty_port		tport;
	काष्ठा circ_buf		xmit;
	काष्ठा async_icount	icount;

	अचिन्हित दीर्घ		port;
	पूर्णांक			baud_base;
	पूर्णांक			xmit_fअगरo_size;
	पूर्णांक			custom_भागisor;
	पूर्णांक			पढ़ो_status_mask;
	पूर्णांक			ignore_status_mask;
	पूर्णांक			समयout;
	पूर्णांक			quot;
	पूर्णांक			IER; 	/* Interrupt Enable Register */
	पूर्णांक			MCR; 	/* Modem control रेजिस्टर */
	पूर्णांक			x_अक्षर;	/* xon/xoff अक्षरacter */
पूर्ण;

#घोषणा custom amiga_custom
अटल अक्षर *serial_name = "Amiga-builtin serial driver";

अटल काष्ठा tty_driver *serial_driver;

/* number of अक्षरacters left in xmit buffer beक्रमe we ask क्रम more */
#घोषणा WAKEUP_CHARS 256

अटल अचिन्हित अक्षर current_ctl_bits;

अटल व्योम change_speed(काष्ठा tty_काष्ठा *tty, काष्ठा serial_state *info,
		काष्ठा ktermios *old);
अटल व्योम rs_रुको_until_sent(काष्ठा tty_काष्ठा *tty, पूर्णांक समयout);


अटल काष्ठा serial_state rs_table[1];

#घोषणा NR_PORTS ARRAY_SIZE(rs_table)

#समावेश <linux/uaccess.h>

#घोषणा serial_isroot()	(capable(CAP_SYS_ADMIN))

/* some serial hardware definitions */
#घोषणा SDR_OVRUN   (1<<15)
#घोषणा SDR_RBF     (1<<14)
#घोषणा SDR_TBE     (1<<13)
#घोषणा SDR_TSRE    (1<<12)

#घोषणा SERPER_PARENB    (1<<15)

#घोषणा AC_SETCLR   (1<<15)
#घोषणा AC_UARTBRK  (1<<11)

#घोषणा SER_DTR     (1<<7)
#घोषणा SER_RTS     (1<<6)
#घोषणा SER_DCD     (1<<5)
#घोषणा SER_CTS     (1<<4)
#घोषणा SER_DSR     (1<<3)

अटल __अंतरभूत__ व्योम rtsdtr_ctrl(पूर्णांक bits)
अणु
    ciab.pra = ((bits & (SER_RTS | SER_DTR)) ^ (SER_RTS | SER_DTR)) | (ciab.pra & ~(SER_RTS | SER_DTR));
पूर्ण

/*
 * ------------------------------------------------------------
 * rs_stop() and rs_start()
 *
 * This routines are called beक्रमe setting or resetting tty->stopped.
 * They enable or disable transmitter पूर्णांकerrupts, as necessary.
 * ------------------------------------------------------------
 */
अटल व्योम rs_stop(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा serial_state *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (info->IER & UART_IER_THRI) अणु
		info->IER &= ~UART_IER_THRI;
		/* disable Tx पूर्णांकerrupt and हटाओ any pending पूर्णांकerrupts */
		custom.पूर्णांकena = IF_TBE;
		mb();
		custom.पूर्णांकreq = IF_TBE;
		mb();
	पूर्ण
	local_irq_restore(flags);
पूर्ण

अटल व्योम rs_start(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा serial_state *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (info->xmit.head != info->xmit.tail
	    && info->xmit.buf
	    && !(info->IER & UART_IER_THRI)) अणु
		info->IER |= UART_IER_THRI;
		custom.पूर्णांकena = IF_SETCLR | IF_TBE;
		mb();
		/* set a pending Tx Interrupt, transmitter should restart now */
		custom.पूर्णांकreq = IF_SETCLR | IF_TBE;
		mb();
	पूर्ण
	local_irq_restore(flags);
पूर्ण

/*
 * ----------------------------------------------------------------------
 *
 * Here starts the पूर्णांकerrupt handling routines.  All of the following
 * subroutines are declared as अंतरभूत and are folded पूर्णांकo
 * rs_पूर्णांकerrupt().  They were separated out क्रम पढ़ोability's sake.
 *
 * Note: rs_पूर्णांकerrupt() is a "fast" पूर्णांकerrupt, which means that it
 * runs with पूर्णांकerrupts turned off.  People who may want to modअगरy
 * rs_पूर्णांकerrupt() should try to keep the पूर्णांकerrupt handler as fast as
 * possible.  After you are करोne making modअगरications, it is not a bad
 * idea to करो:
 * 
 * gcc -S -DKERNEL -Wall -Wstrict-prototypes -O6 -fomit-frame-poपूर्णांकer serial.c
 *
 * and look at the resulting assemble code in serial.s.
 *
 * 				- Ted Ts'o (tytso@mit.edu), 7-Mar-93
 * -----------------------------------------------------------------------
 */

अटल व्योम receive_अक्षरs(काष्ठा serial_state *info)
अणु
        पूर्णांक status;
	पूर्णांक serdatr;
	अचिन्हित अक्षर ch, flag;
	काष्ठा	async_icount *icount;
	पूर्णांक oe = 0;

	icount = &info->icount;

	status = UART_LSR_DR; /* We obviously have a अक्षरacter! */
	serdatr = custom.serdatr;
	mb();
	custom.पूर्णांकreq = IF_RBF;
	mb();

	अगर((serdatr & 0x1ff) == 0)
	    status |= UART_LSR_BI;
	अगर(serdatr & SDR_OVRUN)
	    status |= UART_LSR_OE;

	ch = serdatr & 0xff;
	icount->rx++;

#अगर_घोषित SERIAL_DEBUG_INTR
	prपूर्णांकk("DR%02x:%02x...", ch, status);
#पूर्ण_अगर
	flag = TTY_NORMAL;

	/*
	 * We करोn't handle parity or frame errors - but I have left
	 * the code in, since I'm not sure that the errors can't be
	 * detected.
	 */

	अगर (status & (UART_LSR_BI | UART_LSR_PE |
		      UART_LSR_FE | UART_LSR_OE)) अणु
	  /*
	   * For statistics only
	   */
	  अगर (status & UART_LSR_BI) अणु
	    status &= ~(UART_LSR_FE | UART_LSR_PE);
	    icount->brk++;
	  पूर्ण अन्यथा अगर (status & UART_LSR_PE)
	    icount->parity++;
	  अन्यथा अगर (status & UART_LSR_FE)
	    icount->frame++;
	  अगर (status & UART_LSR_OE)
	    icount->overrun++;

	  /*
	   * Now check to see अगर अक्षरacter should be
	   * ignored, and mask off conditions which
	   * should be ignored.
	   */
	  अगर (status & info->ignore_status_mask)
	    जाओ out;

	  status &= info->पढ़ो_status_mask;

	  अगर (status & (UART_LSR_BI)) अणु
#अगर_घोषित SERIAL_DEBUG_INTR
	    prपूर्णांकk("handling break....");
#पूर्ण_अगर
	    flag = TTY_BREAK;
	    अगर (info->tport.flags & ASYNC_SAK)
	      करो_SAK(info->tport.tty);
	  पूर्ण अन्यथा अगर (status & UART_LSR_PE)
	    flag = TTY_PARITY;
	  अन्यथा अगर (status & UART_LSR_FE)
	    flag = TTY_FRAME;
	  अगर (status & UART_LSR_OE) अणु
	    /*
	     * Overrun is special, since it's
	     * reported immediately, and करोesn't
	     * affect the current अक्षरacter
	     */
	     oe = 1;
	  पूर्ण
	पूर्ण
	tty_insert_flip_अक्षर(&info->tport, ch, flag);
	अगर (oe == 1)
		tty_insert_flip_अक्षर(&info->tport, 0, TTY_OVERRUN);
	tty_flip_buffer_push(&info->tport);
out:
	वापस;
पूर्ण

अटल व्योम transmit_अक्षरs(काष्ठा serial_state *info)
अणु
	custom.पूर्णांकreq = IF_TBE;
	mb();
	अगर (info->x_अक्षर) अणु
	        custom.serdat = info->x_अक्षर | 0x100;
		mb();
		info->icount.tx++;
		info->x_अक्षर = 0;
		वापस;
	पूर्ण
	अगर (info->xmit.head == info->xmit.tail
	    || info->tport.tty->stopped
	    || info->tport.tty->hw_stopped) अणु
		info->IER &= ~UART_IER_THRI;
	        custom.पूर्णांकena = IF_TBE;
		mb();
		वापस;
	पूर्ण

	custom.serdat = info->xmit.buf[info->xmit.tail++] | 0x100;
	mb();
	info->xmit.tail = info->xmit.tail & (SERIAL_XMIT_SIZE-1);
	info->icount.tx++;

	अगर (CIRC_CNT(info->xmit.head,
		     info->xmit.tail,
		     SERIAL_XMIT_SIZE) < WAKEUP_CHARS)
		tty_wakeup(info->tport.tty);

#अगर_घोषित SERIAL_DEBUG_INTR
	prपूर्णांकk("THRE...");
#पूर्ण_अगर
	अगर (info->xmit.head == info->xmit.tail) अणु
	        custom.पूर्णांकena = IF_TBE;
		mb();
		info->IER &= ~UART_IER_THRI;
	पूर्ण
पूर्ण

अटल व्योम check_modem_status(काष्ठा serial_state *info)
अणु
	काष्ठा tty_port *port = &info->tport;
	अचिन्हित अक्षर status = ciab.pra & (SER_DCD | SER_CTS | SER_DSR);
	अचिन्हित अक्षर dstatus;
	काष्ठा	async_icount *icount;

	/* Determine bits that have changed */
	dstatus = status ^ current_ctl_bits;
	current_ctl_bits = status;

	अगर (dstatus) अणु
		icount = &info->icount;
		/* update input line counters */
		अगर (dstatus & SER_DSR)
			icount->dsr++;
		अगर (dstatus & SER_DCD) अणु
			icount->dcd++;
		पूर्ण
		अगर (dstatus & SER_CTS)
			icount->cts++;
		wake_up_पूर्णांकerruptible(&port->delta_msr_रुको);
	पूर्ण

	अगर (tty_port_check_carrier(port) && (dstatus & SER_DCD)) अणु
#अगर (defined(SERIAL_DEBUG_OPEN) || defined(SERIAL_DEBUG_INTR))
		prपूर्णांकk("ttyS%d CD now %s...", info->line,
		       (!(status & SER_DCD)) ? "on" : "off");
#पूर्ण_अगर
		अगर (!(status & SER_DCD))
			wake_up_पूर्णांकerruptible(&port->खोलो_रुको);
		अन्यथा अणु
#अगर_घोषित SERIAL_DEBUG_OPEN
			prपूर्णांकk("doing serial hangup...");
#पूर्ण_अगर
			अगर (port->tty)
				tty_hangup(port->tty);
		पूर्ण
	पूर्ण
	अगर (tty_port_cts_enabled(port)) अणु
		अगर (port->tty->hw_stopped) अणु
			अगर (!(status & SER_CTS)) अणु
#अगर (defined(SERIAL_DEBUG_INTR) || defined(SERIAL_DEBUG_FLOW))
				prपूर्णांकk("CTS tx start...");
#पूर्ण_अगर
				port->tty->hw_stopped = 0;
				info->IER |= UART_IER_THRI;
				custom.पूर्णांकena = IF_SETCLR | IF_TBE;
				mb();
				/* set a pending Tx Interrupt, transmitter should restart now */
				custom.पूर्णांकreq = IF_SETCLR | IF_TBE;
				mb();
				tty_wakeup(port->tty);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((status & SER_CTS)) अणु
#अगर (defined(SERIAL_DEBUG_INTR) || defined(SERIAL_DEBUG_FLOW))
				prपूर्णांकk("CTS tx stop...");
#पूर्ण_अगर
				port->tty->hw_stopped = 1;
				info->IER &= ~UART_IER_THRI;
				/* disable Tx पूर्णांकerrupt and हटाओ any pending पूर्णांकerrupts */
				custom.पूर्णांकena = IF_TBE;
				mb();
				custom.पूर्णांकreq = IF_TBE;
				mb();
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t ser_vbl_पूर्णांक( पूर्णांक irq, व्योम *data)
अणु
        /* vbl is just a periodic पूर्णांकerrupt we tie पूर्णांकo to update modem status */
	काष्ठा serial_state *info = data;
	/*
	 * TBD - is it better to unरेजिस्टर from this पूर्णांकerrupt or to
	 * ignore it अगर MSI is clear ?
	 */
	अगर(info->IER & UART_IER_MSI)
	  check_modem_status(info);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ser_rx_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा serial_state *info = dev_id;

#अगर_घोषित SERIAL_DEBUG_INTR
	prपूर्णांकk("ser_rx_int...");
#पूर्ण_अगर

	अगर (!info->tport.tty)
		वापस IRQ_NONE;

	receive_अक्षरs(info);
#अगर_घोषित SERIAL_DEBUG_INTR
	prपूर्णांकk("end.\n");
#पूर्ण_अगर
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ser_tx_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा serial_state *info = dev_id;

	अगर (custom.serdatr & SDR_TBE) अणु
#अगर_घोषित SERIAL_DEBUG_INTR
	  prपूर्णांकk("ser_tx_int...");
#पूर्ण_अगर

	  अगर (!info->tport.tty)
		वापस IRQ_NONE;

	  transmit_अक्षरs(info);
#अगर_घोषित SERIAL_DEBUG_INTR
	  prपूर्णांकk("end.\n");
#पूर्ण_अगर
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/*
 * -------------------------------------------------------------------
 * Here ends the serial पूर्णांकerrupt routines.
 * -------------------------------------------------------------------
 */

/*
 * ---------------------------------------------------------------
 * Low level utility subroutines क्रम the serial driver:  routines to
 * figure out the appropriate समयout क्रम an पूर्णांकerrupt chain, routines
 * to initialize and startup a serial port, and routines to shutकरोwn a
 * serial port.  Useful stuff like that.
 * ---------------------------------------------------------------
 */

अटल पूर्णांक startup(काष्ठा tty_काष्ठा *tty, काष्ठा serial_state *info)
अणु
	काष्ठा tty_port *port = &info->tport;
	अचिन्हित दीर्घ flags;
	पूर्णांक	retval=0;
	अचिन्हित दीर्घ page;

	page = get_zeroed_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	local_irq_save(flags);

	अगर (tty_port_initialized(port)) अणु
		मुक्त_page(page);
		जाओ errout;
	पूर्ण

	अगर (info->xmit.buf)
		मुक्त_page(page);
	अन्यथा
		info->xmit.buf = (अचिन्हित अक्षर *) page;

#अगर_घोषित SERIAL_DEBUG_OPEN
	prपूर्णांकk("starting up ttys%d ...", info->line);
#पूर्ण_अगर

	/* Clear anything in the input buffer */

	custom.पूर्णांकreq = IF_RBF;
	mb();

	retval = request_irq(IRQ_AMIGA_VERTB, ser_vbl_पूर्णांक, 0, "serial status", info);
	अगर (retval) अणु
	  अगर (serial_isroot()) अणु
	      set_bit(TTY_IO_ERROR, &tty->flags);
	    retval = 0;
	  पूर्ण
	  जाओ errout;
	पूर्ण

	/* enable both Rx and Tx पूर्णांकerrupts */
	custom.पूर्णांकena = IF_SETCLR | IF_RBF | IF_TBE;
	mb();
	info->IER = UART_IER_MSI;

	/* remember current state of the DCD and CTS bits */
	current_ctl_bits = ciab.pra & (SER_DCD | SER_CTS | SER_DSR);

	info->MCR = 0;
	अगर (C_BAUD(tty))
	  info->MCR = SER_DTR | SER_RTS;
	rtsdtr_ctrl(info->MCR);

	clear_bit(TTY_IO_ERROR, &tty->flags);
	info->xmit.head = info->xmit.tail = 0;

	/*
	 * and set the speed of the serial port
	 */
	change_speed(tty, info, शून्य);

	tty_port_set_initialized(port, 1);
	local_irq_restore(flags);
	वापस 0;

errout:
	local_irq_restore(flags);
	वापस retval;
पूर्ण

/*
 * This routine will shutकरोwn a serial port; पूर्णांकerrupts are disabled, and
 * DTR is dropped अगर the hangup on बंद termio flag is on.
 */
अटल व्योम shutकरोwn(काष्ठा tty_काष्ठा *tty, काष्ठा serial_state *info)
अणु
	अचिन्हित दीर्घ	flags;
	काष्ठा serial_state *state;

	अगर (!tty_port_initialized(&info->tport))
		वापस;

	state = info;

#अगर_घोषित SERIAL_DEBUG_OPEN
	prपूर्णांकk("Shutting down serial port %d ....\n", info->line);
#पूर्ण_अगर

	local_irq_save(flags); /* Disable पूर्णांकerrupts */

	/*
	 * clear delta_msr_रुको queue to aव्योम mem leaks: we may मुक्त the irq
	 * here so the queue might never be waken up
	 */
	wake_up_पूर्णांकerruptible(&info->tport.delta_msr_रुको);

	/*
	 * Free the IRQ, अगर necessary
	 */
	मुक्त_irq(IRQ_AMIGA_VERTB, info);

	अगर (info->xmit.buf) अणु
		मुक्त_page((अचिन्हित दीर्घ) info->xmit.buf);
		info->xmit.buf = शून्य;
	पूर्ण

	info->IER = 0;
	custom.पूर्णांकena = IF_RBF | IF_TBE;
	mb();

	/* disable अवरोध condition */
	custom.adkcon = AC_UARTBRK;
	mb();

	अगर (C_HUPCL(tty))
		info->MCR &= ~(SER_DTR|SER_RTS);
	rtsdtr_ctrl(info->MCR);

	set_bit(TTY_IO_ERROR, &tty->flags);

	tty_port_set_initialized(&info->tport, 0);
	local_irq_restore(flags);
पूर्ण


/*
 * This routine is called to set the UART भागisor रेजिस्टरs to match
 * the specअगरied baud rate क्रम a serial port.
 */
अटल व्योम change_speed(काष्ठा tty_काष्ठा *tty, काष्ठा serial_state *info,
			 काष्ठा ktermios *old_termios)
अणु
	काष्ठा tty_port *port = &info->tport;
	पूर्णांक	quot = 0, baud_base, baud;
	अचिन्हित cflag, cval = 0;
	पूर्णांक	bits;
	अचिन्हित दीर्घ	flags;

	cflag = tty->termios.c_cflag;

	/* Byte size is always 8 bits plus parity bit अगर requested */

	cval = 3; bits = 10;
	अगर (cflag & CSTOPB) अणु
		cval |= 0x04;
		bits++;
	पूर्ण
	अगर (cflag & PARENB) अणु
		cval |= UART_LCR_PARITY;
		bits++;
	पूर्ण
	अगर (!(cflag & PARODD))
		cval |= UART_LCR_EPAR;
#अगर_घोषित CMSPAR
	अगर (cflag & CMSPAR)
		cval |= UART_LCR_SPAR;
#पूर्ण_अगर

	/* Determine भागisor based on baud rate */
	baud = tty_get_baud_rate(tty);
	अगर (!baud)
		baud = 9600;	/* B0 transition handled in rs_set_termios */
	baud_base = info->baud_base;
	अगर (baud == 38400 && (port->flags & ASYNC_SPD_MASK) == ASYNC_SPD_CUST)
		quot = info->custom_भागisor;
	अन्यथा अणु
		अगर (baud == 134)
			/* Special हाल since 134 is really 134.5 */
			quot = (2*baud_base / 269);
		अन्यथा अगर (baud)
			quot = baud_base / baud;
	पूर्ण
	/* If the quotient is zero refuse the change */
	अगर (!quot && old_termios) अणु
		/* FIXME: Will need updating क्रम new tty in the end */
		tty->termios.c_cflag &= ~CBAUD;
		tty->termios.c_cflag |= (old_termios->c_cflag & CBAUD);
		baud = tty_get_baud_rate(tty);
		अगर (!baud)
			baud = 9600;
		अगर (baud == 38400 &&
		    (port->flags & ASYNC_SPD_MASK) == ASYNC_SPD_CUST)
			quot = info->custom_भागisor;
		अन्यथा अणु
			अगर (baud == 134)
				/* Special हाल since 134 is really 134.5 */
				quot = (2*baud_base / 269);
			अन्यथा अगर (baud)
				quot = baud_base / baud;
		पूर्ण
	पूर्ण
	/* As a last resort, अगर the quotient is zero, शेष to 9600 bps */
	अगर (!quot)
		quot = baud_base / 9600;
	info->quot = quot;
	info->समयout = ((info->xmit_fअगरo_size*HZ*bits*quot) / baud_base);
	info->समयout += HZ/50;		/* Add .02 seconds of slop */

	/* CTS flow control flag and modem status पूर्णांकerrupts */
	info->IER &= ~UART_IER_MSI;
	अगर (port->flags & ASYNC_HARDPPS_CD)
		info->IER |= UART_IER_MSI;
	tty_port_set_cts_flow(port, cflag & CRTSCTS);
	अगर (cflag & CRTSCTS)
		info->IER |= UART_IER_MSI;
	tty_port_set_check_carrier(port, ~cflag & CLOCAL);
	अगर (~cflag & CLOCAL)
		info->IER |= UART_IER_MSI;
	/* TBD:
	 * Does clearing IER_MSI imply that we should disable the VBL पूर्णांकerrupt ?
	 */

	/*
	 * Set up parity check flag
	 */

	info->पढ़ो_status_mask = UART_LSR_OE | UART_LSR_DR;
	अगर (I_INPCK(tty))
		info->पढ़ो_status_mask |= UART_LSR_FE | UART_LSR_PE;
	अगर (I_BRKINT(tty) || I_PARMRK(tty))
		info->पढ़ो_status_mask |= UART_LSR_BI;

	/*
	 * Characters to ignore
	 */
	info->ignore_status_mask = 0;
	अगर (I_IGNPAR(tty))
		info->ignore_status_mask |= UART_LSR_PE | UART_LSR_FE;
	अगर (I_IGNBRK(tty)) अणु
		info->ignore_status_mask |= UART_LSR_BI;
		/*
		 * If we're ignore parity and अवरोध indicators, ignore 
		 * overruns too.  (For real raw support).
		 */
		अगर (I_IGNPAR(tty))
			info->ignore_status_mask |= UART_LSR_OE;
	पूर्ण
	/*
	 * !!! ignore all अक्षरacters अगर CREAD is not set
	 */
	अगर ((cflag & CREAD) == 0)
		info->ignore_status_mask |= UART_LSR_DR;
	local_irq_save(flags);

	अणु
	  लघु serper;

	/* Set up the baud rate */
	  serper = quot - 1;

	/* Enable or disable parity bit */

	अगर(cval & UART_LCR_PARITY)
	  serper |= (SERPER_PARENB);

	custom.serper = serper;
	mb();
	पूर्ण

	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक rs_put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch)
अणु
	काष्ठा serial_state *info;
	अचिन्हित दीर्घ flags;

	info = tty->driver_data;

	अगर (!info->xmit.buf)
		वापस 0;

	local_irq_save(flags);
	अगर (CIRC_SPACE(info->xmit.head,
		       info->xmit.tail,
		       SERIAL_XMIT_SIZE) == 0) अणु
		local_irq_restore(flags);
		वापस 0;
	पूर्ण

	info->xmit.buf[info->xmit.head++] = ch;
	info->xmit.head &= SERIAL_XMIT_SIZE-1;
	local_irq_restore(flags);
	वापस 1;
पूर्ण

अटल व्योम rs_flush_अक्षरs(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा serial_state *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (info->xmit.head == info->xmit.tail
	    || tty->stopped
	    || tty->hw_stopped
	    || !info->xmit.buf)
		वापस;

	local_irq_save(flags);
	info->IER |= UART_IER_THRI;
	custom.पूर्णांकena = IF_SETCLR | IF_TBE;
	mb();
	/* set a pending Tx Interrupt, transmitter should restart now */
	custom.पूर्णांकreq = IF_SETCLR | IF_TBE;
	mb();
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक rs_ग_लिखो(काष्ठा tty_काष्ठा * tty, स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक	c, ret = 0;
	काष्ठा serial_state *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (!info->xmit.buf)
		वापस 0;

	local_irq_save(flags);
	जबतक (1) अणु
		c = CIRC_SPACE_TO_END(info->xmit.head,
				      info->xmit.tail,
				      SERIAL_XMIT_SIZE);
		अगर (count < c)
			c = count;
		अगर (c <= 0) अणु
			अवरोध;
		पूर्ण
		स_नकल(info->xmit.buf + info->xmit.head, buf, c);
		info->xmit.head = ((info->xmit.head + c) &
				   (SERIAL_XMIT_SIZE-1));
		buf += c;
		count -= c;
		ret += c;
	पूर्ण
	local_irq_restore(flags);

	अगर (info->xmit.head != info->xmit.tail
	    && !tty->stopped
	    && !tty->hw_stopped
	    && !(info->IER & UART_IER_THRI)) अणु
		info->IER |= UART_IER_THRI;
		local_irq_disable();
		custom.पूर्णांकena = IF_SETCLR | IF_TBE;
		mb();
		/* set a pending Tx Interrupt, transmitter should restart now */
		custom.पूर्णांकreq = IF_SETCLR | IF_TBE;
		mb();
		local_irq_restore(flags);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक rs_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा serial_state *info = tty->driver_data;

	वापस CIRC_SPACE(info->xmit.head, info->xmit.tail, SERIAL_XMIT_SIZE);
पूर्ण

अटल पूर्णांक rs_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा serial_state *info = tty->driver_data;

	वापस CIRC_CNT(info->xmit.head, info->xmit.tail, SERIAL_XMIT_SIZE);
पूर्ण

अटल व्योम rs_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा serial_state *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	info->xmit.head = info->xmit.tail = 0;
	local_irq_restore(flags);
	tty_wakeup(tty);
पूर्ण

/*
 * This function is used to send a high-priority XON/XOFF अक्षरacter to
 * the device
 */
अटल व्योम rs_send_xअक्षर(काष्ठा tty_काष्ठा *tty, अक्षर ch)
अणु
	काष्ठा serial_state *info = tty->driver_data;
        अचिन्हित दीर्घ flags;

	info->x_अक्षर = ch;
	अगर (ch) अणु
		/* Make sure transmit पूर्णांकerrupts are on */

	        /* Check this ! */
	        local_irq_save(flags);
		अगर(!(custom.पूर्णांकenar & IF_TBE)) अणु
		    custom.पूर्णांकena = IF_SETCLR | IF_TBE;
		    mb();
		    /* set a pending Tx Interrupt, transmitter should restart now */
		    custom.पूर्णांकreq = IF_SETCLR | IF_TBE;
		    mb();
		पूर्ण
		local_irq_restore(flags);

		info->IER |= UART_IER_THRI;
	पूर्ण
पूर्ण

/*
 * ------------------------------------------------------------
 * rs_throttle()
 * 
 * This routine is called by the upper-layer tty layer to संकेत that
 * incoming अक्षरacters should be throttled.
 * ------------------------------------------------------------
 */
अटल व्योम rs_throttle(काष्ठा tty_काष्ठा * tty)
अणु
	काष्ठा serial_state *info = tty->driver_data;
	अचिन्हित दीर्घ flags;
#अगर_घोषित SERIAL_DEBUG_THROTTLE
	prपूर्णांकk("throttle %s ....\n", tty_name(tty));
#पूर्ण_अगर

	अगर (I_IXOFF(tty))
		rs_send_xअक्षर(tty, STOP_CHAR(tty));

	अगर (C_CRTSCTS(tty))
		info->MCR &= ~SER_RTS;

	local_irq_save(flags);
	rtsdtr_ctrl(info->MCR);
	local_irq_restore(flags);
पूर्ण

अटल व्योम rs_unthrottle(काष्ठा tty_काष्ठा * tty)
अणु
	काष्ठा serial_state *info = tty->driver_data;
	अचिन्हित दीर्घ flags;
#अगर_घोषित SERIAL_DEBUG_THROTTLE
	prपूर्णांकk("unthrottle %s ....\n", tty_name(tty));
#पूर्ण_अगर

	अगर (I_IXOFF(tty)) अणु
		अगर (info->x_अक्षर)
			info->x_अक्षर = 0;
		अन्यथा
			rs_send_xअक्षर(tty, START_CHAR(tty));
	पूर्ण
	अगर (C_CRTSCTS(tty))
		info->MCR |= SER_RTS;
	local_irq_save(flags);
	rtsdtr_ctrl(info->MCR);
	local_irq_restore(flags);
पूर्ण

/*
 * ------------------------------------------------------------
 * rs_ioctl() and मित्रs
 * ------------------------------------------------------------
 */

अटल पूर्णांक get_serial_info(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा serial_state *state = tty->driver_data;
	अचिन्हित पूर्णांक बंद_delay, closing_रुको;

	tty_lock(tty);
	बंद_delay = jअगरfies_to_msecs(state->tport.बंद_delay) / 10;
	closing_रुको = state->tport.closing_रुको;
	अगर (closing_रुको != ASYNC_CLOSING_WAIT_NONE)
		closing_रुको = jअगरfies_to_msecs(closing_रुको) / 10;

	ss->line = tty->index;
	ss->port = state->port;
	ss->flags = state->tport.flags;
	ss->xmit_fअगरo_size = state->xmit_fअगरo_size;
	ss->baud_base = state->baud_base;
	ss->बंद_delay = बंद_delay;
	ss->closing_रुको = closing_रुको;
	ss->custom_भागisor = state->custom_भागisor;
	tty_unlock(tty);
	वापस 0;
पूर्ण

अटल पूर्णांक set_serial_info(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा serial_state *state = tty->driver_data;
	काष्ठा tty_port *port = &state->tport;
	bool change_spd;
	पूर्णांक 			retval = 0;
	अचिन्हित पूर्णांक बंद_delay, closing_रुको;

	tty_lock(tty);
	change_spd = ((ss->flags ^ port->flags) & ASYNC_SPD_MASK) ||
		ss->custom_भागisor != state->custom_भागisor;
	अगर (ss->irq || ss->port != state->port ||
			ss->xmit_fअगरo_size != state->xmit_fअगरo_size) अणु
		tty_unlock(tty);
		वापस -EINVAL;
	पूर्ण

	बंद_delay = msecs_to_jअगरfies(ss->बंद_delay * 10);
	closing_रुको = ss->closing_रुको;
	अगर (closing_रुको != ASYNC_CLOSING_WAIT_NONE)
		closing_रुको = msecs_to_jअगरfies(closing_रुको * 10);

	अगर (!serial_isroot()) अणु
		अगर ((ss->baud_base != state->baud_base) ||
		    (बंद_delay != port->बंद_delay) ||
		    (closing_रुको != port->closing_रुको) ||
		    (ss->xmit_fअगरo_size != state->xmit_fअगरo_size) ||
		    ((ss->flags & ~ASYNC_USR_MASK) !=
		     (port->flags & ~ASYNC_USR_MASK))) अणु
			tty_unlock(tty);
			वापस -EPERM;
		पूर्ण
		port->flags = ((port->flags & ~ASYNC_USR_MASK) |
			       (ss->flags & ASYNC_USR_MASK));
		state->custom_भागisor = ss->custom_भागisor;
		जाओ check_and_निकास;
	पूर्ण

	अगर (ss->baud_base < 9600) अणु
		tty_unlock(tty);
		वापस -EINVAL;
	पूर्ण

	/*
	 * OK, past this poपूर्णांक, all the error checking has been करोne.
	 * At this poपूर्णांक, we start making changes.....
	 */

	state->baud_base = ss->baud_base;
	port->flags = ((port->flags & ~ASYNC_FLAGS) |
			(ss->flags & ASYNC_FLAGS));
	state->custom_भागisor = ss->custom_भागisor;
	port->बंद_delay = बंद_delay;
	port->closing_रुको = closing_रुको;

check_and_निकास:
	अगर (tty_port_initialized(port)) अणु
		अगर (change_spd) अणु
			/* warn about deprecation unless clearing */
			अगर (ss->flags & ASYNC_SPD_MASK)
				dev_warn_ratelimited(tty->dev, "use of SPD flags is deprecated\n");
			change_speed(tty, state, शून्य);
		पूर्ण
	पूर्ण अन्यथा
		retval = startup(tty, state);
	tty_unlock(tty);
	वापस retval;
पूर्ण

/*
 * get_lsr_info - get line status रेजिस्टर info
 *
 * Purpose: Let user call ioctl() to get info when the UART physically
 * 	    is emptied.  On bus types like RS485, the transmitter must
 * 	    release the bus after transmitting. This must be करोne when
 * 	    the transmit shअगरt रेजिस्टर is empty, not be करोne when the
 * 	    transmit holding रेजिस्टर is empty.  This functionality
 * 	    allows an RS485 driver to be written in user space. 
 */
अटल पूर्णांक get_lsr_info(काष्ठा serial_state *info, अचिन्हित पूर्णांक __user *value)
अणु
	अचिन्हित अक्षर status;
	अचिन्हित पूर्णांक result;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	status = custom.serdatr;
	mb();
	local_irq_restore(flags);
	result = ((status & SDR_TSRE) ? TIOCSER_TEMT : 0);
	अगर (copy_to_user(value, &result, माप(पूर्णांक)))
		वापस -EFAULT;
	वापस 0;
पूर्ण


अटल पूर्णांक rs_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा serial_state *info = tty->driver_data;
	अचिन्हित अक्षर control, status;
	अचिन्हित दीर्घ flags;

	अगर (tty_io_error(tty))
		वापस -EIO;

	control = info->MCR;
	local_irq_save(flags);
	status = ciab.pra;
	local_irq_restore(flags);
	वापस    ((control & SER_RTS) ? TIOCM_RTS : 0)
		| ((control & SER_DTR) ? TIOCM_DTR : 0)
		| (!(status  & SER_DCD) ? TIOCM_CAR : 0)
		| (!(status  & SER_DSR) ? TIOCM_DSR : 0)
		| (!(status  & SER_CTS) ? TIOCM_CTS : 0);
पूर्ण

अटल पूर्णांक rs_tiocmset(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक set,
						अचिन्हित पूर्णांक clear)
अणु
	काष्ठा serial_state *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (tty_io_error(tty))
		वापस -EIO;

	local_irq_save(flags);
	अगर (set & TIOCM_RTS)
		info->MCR |= SER_RTS;
	अगर (set & TIOCM_DTR)
		info->MCR |= SER_DTR;
	अगर (clear & TIOCM_RTS)
		info->MCR &= ~SER_RTS;
	अगर (clear & TIOCM_DTR)
		info->MCR &= ~SER_DTR;
	rtsdtr_ctrl(info->MCR);
	local_irq_restore(flags);
	वापस 0;
पूर्ण

/*
 * rs_अवरोध() --- routine which turns the अवरोध handling on or off
 */
अटल पूर्णांक rs_अवरोध(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (अवरोध_state == -1)
	  custom.adkcon = AC_SETCLR | AC_UARTBRK;
	अन्यथा
	  custom.adkcon = AC_UARTBRK;
	mb();
	local_irq_restore(flags);
	वापस 0;
पूर्ण

/*
 * Get counter of input serial line पूर्णांकerrupts (DCD,RI,DSR,CTS)
 * Return: ग_लिखो counters to the user passed counter काष्ठा
 * NB: both 1->0 and 0->1 transitions are counted except क्रम
 *     RI where only 0->1 is counted.
 */
अटल पूर्णांक rs_get_icount(काष्ठा tty_काष्ठा *tty,
				काष्ठा serial_icounter_काष्ठा *icount)
अणु
	काष्ठा serial_state *info = tty->driver_data;
	काष्ठा async_icount cnow;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	cnow = info->icount;
	local_irq_restore(flags);
	icount->cts = cnow.cts;
	icount->dsr = cnow.dsr;
	icount->rng = cnow.rng;
	icount->dcd = cnow.dcd;
	icount->rx = cnow.rx;
	icount->tx = cnow.tx;
	icount->frame = cnow.frame;
	icount->overrun = cnow.overrun;
	icount->parity = cnow.parity;
	icount->brk = cnow.brk;
	icount->buf_overrun = cnow.buf_overrun;

	वापस 0;
पूर्ण

अटल पूर्णांक rs_ioctl(काष्ठा tty_काष्ठा *tty,
		    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा serial_state *info = tty->driver_data;
	काष्ठा async_icount cprev, cnow;	/* kernel counter temps */
	व्योम __user *argp = (व्योम __user *)arg;
	अचिन्हित दीर्घ flags;
	DEFINE_WAIT(रुको);
	पूर्णांक ret;

	अगर ((cmd != TIOCSERCONFIG) &&
	    (cmd != TIOCMIWAIT) && (cmd != TIOCGICOUNT)) अणु
		अगर (tty_io_error(tty))
		    वापस -EIO;
	पूर्ण

	चयन (cmd) अणु
		हाल TIOCSERCONFIG:
			वापस 0;

		हाल TIOCSERGETLSR: /* Get line status रेजिस्टर */
			वापस get_lsr_info(info, argp);

		/*
		 * Wait क्रम any of the 4 modem inमाला_दो (DCD,RI,DSR,CTS) to change
		 * - mask passed in arg क्रम lines of पूर्णांकerest
 		 *   (use |'ed TIOCM_RNG/DSR/CD/CTS क्रम masking)
		 * Caller should use TIOCGICOUNT to see which one it was
		 */
		हाल TIOCMIWAIT:
			local_irq_save(flags);
			/* note the counters on entry */
			cprev = info->icount;
			local_irq_restore(flags);
			जबतक (1) अणु
				prepare_to_रुको(&info->tport.delta_msr_रुको,
						&रुको, TASK_INTERRUPTIBLE);
				local_irq_save(flags);
				cnow = info->icount; /* atomic copy */
				local_irq_restore(flags);
				अगर (cnow.rng == cprev.rng && cnow.dsr == cprev.dsr && 
				    cnow.dcd == cprev.dcd && cnow.cts == cprev.cts) अणु
					ret = -EIO; /* no change => error */
					अवरोध;
				पूर्ण
				अगर ( ((arg & TIOCM_RNG) && (cnow.rng != cprev.rng)) ||
				     ((arg & TIOCM_DSR) && (cnow.dsr != cprev.dsr)) ||
				     ((arg & TIOCM_CD)  && (cnow.dcd != cprev.dcd)) ||
				     ((arg & TIOCM_CTS) && (cnow.cts != cprev.cts)) ) अणु
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
			finish_रुको(&info->tport.delta_msr_रुको, &रुको);
			वापस ret;

		शेष:
			वापस -ENOIOCTLCMD;
		पूर्ण
	वापस 0;
पूर्ण

अटल व्योम rs_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old_termios)
अणु
	काष्ठा serial_state *info = tty->driver_data;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक cflag = tty->termios.c_cflag;

	change_speed(tty, info, old_termios);

	/* Handle transition to B0 status */
	अगर ((old_termios->c_cflag & CBAUD) && !(cflag & CBAUD)) अणु
		info->MCR &= ~(SER_DTR|SER_RTS);
		local_irq_save(flags);
		rtsdtr_ctrl(info->MCR);
		local_irq_restore(flags);
	पूर्ण

	/* Handle transition away from B0 status */
	अगर (!(old_termios->c_cflag & CBAUD) && (cflag & CBAUD)) अणु
		info->MCR |= SER_DTR;
		अगर (!C_CRTSCTS(tty) || !tty_throttled(tty))
			info->MCR |= SER_RTS;
		local_irq_save(flags);
		rtsdtr_ctrl(info->MCR);
		local_irq_restore(flags);
	पूर्ण

	/* Handle turning off CRTSCTS */
	अगर ((old_termios->c_cflag & CRTSCTS) && !C_CRTSCTS(tty)) अणु
		tty->hw_stopped = 0;
		rs_start(tty);
	पूर्ण

#अगर 0
	/*
	 * No need to wake up processes in खोलो रुको, since they
	 * sample the CLOCAL flag once, and करोn't recheck it.
	 * XXX  It's not clear whether the current behavior is correct
	 * or not.  Hence, this may change.....
	 */
	अगर (!(old_termios->c_cflag & CLOCAL) && C_CLOCAL(tty))
		wake_up_पूर्णांकerruptible(&info->खोलो_रुको);
#पूर्ण_अगर
पूर्ण

/*
 * ------------------------------------------------------------
 * rs_बंद()
 * 
 * This routine is called when the serial port माला_लो बंदd.  First, we
 * रुको क्रम the last reमुख्यing data to be sent.  Then, we unlink its
 * async काष्ठाure from the पूर्णांकerrupt chain अगर necessary, and we मुक्त
 * that IRQ अगर nothing is left in the chain.
 * ------------------------------------------------------------
 */
अटल व्योम rs_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file * filp)
अणु
	काष्ठा serial_state *state = tty->driver_data;
	काष्ठा tty_port *port = &state->tport;

	अगर (tty_port_बंद_start(port, tty, filp) == 0)
		वापस;

	/*
	 * At this poपूर्णांक we stop accepting input.  To करो this, we
	 * disable the receive line status पूर्णांकerrupts, and tell the
	 * पूर्णांकerrupt driver to stop checking the data पढ़ोy bit in the
	 * line status रेजिस्टर.
	 */
	state->पढ़ो_status_mask &= ~UART_LSR_DR;
	अगर (tty_port_initialized(port)) अणु
	        /* disable receive पूर्णांकerrupts */
	        custom.पूर्णांकena = IF_RBF;
		mb();
		/* clear any pending receive पूर्णांकerrupt */
		custom.पूर्णांकreq = IF_RBF;
		mb();

		/*
		 * Beक्रमe we drop DTR, make sure the UART transmitter
		 * has completely drained; this is especially
		 * important अगर there is a transmit FIFO!
		 */
		rs_रुको_until_sent(tty, state->समयout);
	पूर्ण
	shutकरोwn(tty, state);
	rs_flush_buffer(tty);
		
	tty_ldisc_flush(tty);
	port->tty = शून्य;

	tty_port_बंद_end(port, tty);
पूर्ण

/*
 * rs_रुको_until_sent() --- रुको until the transmitter is empty
 */
अटल व्योम rs_रुको_until_sent(काष्ठा tty_काष्ठा *tty, पूर्णांक समयout)
अणु
	काष्ठा serial_state *info = tty->driver_data;
	अचिन्हित दीर्घ orig_jअगरfies, अक्षर_समय;
	पूर्णांक lsr;

	अगर (info->xmit_fअगरo_size == 0)
		वापस; /* Just in हाल.... */

	orig_jअगरfies = jअगरfies;

	/*
	 * Set the check पूर्णांकerval to be 1/5 of the estimated समय to
	 * send a single अक्षरacter, and make it at least 1.  The check
	 * पूर्णांकerval should also be less than the समयout.
	 * 
	 * Note: we have to use pretty tight timings here to satisfy
	 * the NIST-PCTS.
	 */
	अक्षर_समय = (info->समयout - HZ/50) / info->xmit_fअगरo_size;
	अक्षर_समय = अक्षर_समय / 5;
	अगर (अक्षर_समय == 0)
		अक्षर_समय = 1;
	अगर (समयout)
	  अक्षर_समय = min_t(अचिन्हित दीर्घ, अक्षर_समय, समयout);
	/*
	 * If the transmitter hasn't cleared in twice the approximate
	 * amount of समय to send the entire FIFO, it probably won't
	 * ever clear.  This assumes the UART isn't करोing flow
	 * control, which is currently the हाल.  Hence, अगर it ever
	 * takes दीर्घer than info->समयout, this is probably due to a
	 * UART bug of some kind.  So, we clamp the समयout parameter at
	 * 2*info->समयout.
	 */
	अगर (!समयout || समयout > 2*info->समयout)
		समयout = 2*info->समयout;
#अगर_घोषित SERIAL_DEBUG_RS_WAIT_UNTIL_SENT
	prपूर्णांकk("In rs_wait_until_sent(%d) check=%lu...", समयout, अक्षर_समय);
	prपूर्णांकk("jiff=%lu...", jअगरfies);
#पूर्ण_अगर
	जबतक(!((lsr = custom.serdatr) & SDR_TSRE)) अणु
#अगर_घोषित SERIAL_DEBUG_RS_WAIT_UNTIL_SENT
		prपूर्णांकk("serdatr = %d (jiff=%lu)...", lsr, jअगरfies);
#पूर्ण_अगर
		msleep_पूर्णांकerruptible(jअगरfies_to_msecs(अक्षर_समय));
		अगर (संकेत_pending(current))
			अवरोध;
		अगर (समयout && समय_after(jअगरfies, orig_jअगरfies + समयout))
			अवरोध;
	पूर्ण
	__set_current_state(TASK_RUNNING);

#अगर_घोषित SERIAL_DEBUG_RS_WAIT_UNTIL_SENT
	prपूर्णांकk("lsr = %d (jiff=%lu)...done\n", lsr, jअगरfies);
#पूर्ण_अगर
पूर्ण

/*
 * rs_hangup() --- called by tty_hangup() when a hangup is संकेतed.
 */
अटल व्योम rs_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा serial_state *info = tty->driver_data;

	rs_flush_buffer(tty);
	shutकरोwn(tty, info);
	info->tport.count = 0;
	tty_port_set_active(&info->tport, 0);
	info->tport.tty = शून्य;
	wake_up_पूर्णांकerruptible(&info->tport.खोलो_रुको);
पूर्ण

/*
 * This routine is called whenever a serial port is खोलोed.  It
 * enables पूर्णांकerrupts क्रम a serial port, linking in its async काष्ठाure पूर्णांकo
 * the IRQ chain.   It also perक्रमms the serial-specअगरic
 * initialization क्रम the tty काष्ठाure.
 */
अटल पूर्णांक rs_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file * filp)
अणु
	काष्ठा serial_state *info = rs_table + tty->index;
	काष्ठा tty_port *port = &info->tport;
	पूर्णांक retval;

	port->count++;
	port->tty = tty;
	tty->driver_data = info;
	tty->port = port;

	retval = startup(tty, info);
	अगर (retval) अणु
		वापस retval;
	पूर्ण

	वापस tty_port_block_til_पढ़ोy(port, tty, filp);
पूर्ण

/*
 * /proc fs routines....
 */

अटल अंतरभूत व्योम line_info(काष्ठा seq_file *m, पूर्णांक line,
		काष्ठा serial_state *state)
अणु
	अक्षर	stat_buf[30], control, status;
	अचिन्हित दीर्घ flags;

	seq_म_लिखो(m, "%d: uart:amiga_builtin", line);

	local_irq_save(flags);
	status = ciab.pra;
	control = tty_port_initialized(&state->tport) ? state->MCR : status;
	local_irq_restore(flags);

	stat_buf[0] = 0;
	stat_buf[1] = 0;
	अगर(!(control & SER_RTS))
		म_जोड़ो(stat_buf, "|RTS");
	अगर(!(status & SER_CTS))
		म_जोड़ो(stat_buf, "|CTS");
	अगर(!(control & SER_DTR))
		म_जोड़ो(stat_buf, "|DTR");
	अगर(!(status & SER_DSR))
		म_जोड़ो(stat_buf, "|DSR");
	अगर(!(status & SER_DCD))
		म_जोड़ो(stat_buf, "|CD");

	अगर (state->quot)
		seq_म_लिखो(m, " baud:%d", state->baud_base / state->quot);

	seq_म_लिखो(m, " tx:%d rx:%d", state->icount.tx, state->icount.rx);

	अगर (state->icount.frame)
		seq_म_लिखो(m, " fe:%d", state->icount.frame);

	अगर (state->icount.parity)
		seq_म_लिखो(m, " pe:%d", state->icount.parity);

	अगर (state->icount.brk)
		seq_म_लिखो(m, " brk:%d", state->icount.brk);

	अगर (state->icount.overrun)
		seq_म_लिखो(m, " oe:%d", state->icount.overrun);

	/*
	 * Last thing is the RS-232 status lines
	 */
	seq_म_लिखो(m, " %s\n", stat_buf+1);
पूर्ण

अटल पूर्णांक rs_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "serinfo:1.0 driver:%s\n", serial_version);
	line_info(m, 0, &rs_table[0]);
	वापस 0;
पूर्ण

/*
 * ---------------------------------------------------------------------
 * rs_init() and मित्रs
 *
 * rs_init() is called at boot-समय to initialize the serial driver.
 * ---------------------------------------------------------------------
 */

/*
 * This routine prपूर्णांकs out the appropriate serial driver version
 * number, and identअगरies which options were configured पूर्णांकo this
 * driver.
 */
अटल व्योम show_serial_version(व्योम)
अणु
 	prपूर्णांकk(KERN_INFO "%s version %s\n", serial_name, serial_version);
पूर्ण


अटल स्थिर काष्ठा tty_operations serial_ops = अणु
	.खोलो = rs_खोलो,
	.बंद = rs_बंद,
	.ग_लिखो = rs_ग_लिखो,
	.put_अक्षर = rs_put_अक्षर,
	.flush_अक्षरs = rs_flush_अक्षरs,
	.ग_लिखो_room = rs_ग_लिखो_room,
	.अक्षरs_in_buffer = rs_अक्षरs_in_buffer,
	.flush_buffer = rs_flush_buffer,
	.ioctl = rs_ioctl,
	.throttle = rs_throttle,
	.unthrottle = rs_unthrottle,
	.set_termios = rs_set_termios,
	.stop = rs_stop,
	.start = rs_start,
	.hangup = rs_hangup,
	.अवरोध_ctl = rs_अवरोध,
	.send_xअक्षर = rs_send_xअक्षर,
	.रुको_until_sent = rs_रुको_until_sent,
	.tiocmget = rs_tiocmget,
	.tiocmset = rs_tiocmset,
	.get_icount = rs_get_icount,
	.set_serial = set_serial_info,
	.get_serial = get_serial_info,
	.proc_show = rs_proc_show,
पूर्ण;

अटल पूर्णांक amiga_carrier_उठाओd(काष्ठा tty_port *port)
अणु
	वापस !(ciab.pra & SER_DCD);
पूर्ण

अटल व्योम amiga_dtr_rts(काष्ठा tty_port *port, पूर्णांक उठाओ)
अणु
	काष्ठा serial_state *info = container_of(port, काष्ठा serial_state,
			tport);
	अचिन्हित दीर्घ flags;

	अगर (उठाओ)
		info->MCR |= SER_DTR|SER_RTS;
	अन्यथा
		info->MCR &= ~(SER_DTR|SER_RTS);

	local_irq_save(flags);
	rtsdtr_ctrl(info->MCR);
	local_irq_restore(flags);
पूर्ण

अटल स्थिर काष्ठा tty_port_operations amiga_port_ops = अणु
	.carrier_उठाओd = amiga_carrier_उठाओd,
	.dtr_rts = amiga_dtr_rts,
पूर्ण;

/*
 * The serial driver boot-समय initialization code!
 */
अटल पूर्णांक __init amiga_serial_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा serial_state * state;
	पूर्णांक error;

	serial_driver = alloc_tty_driver(NR_PORTS);
	अगर (!serial_driver)
		वापस -ENOMEM;

	show_serial_version();

	/* Initialize the tty_driver काष्ठाure */

	serial_driver->driver_name = "amiserial";
	serial_driver->name = "ttyS";
	serial_driver->major = TTY_MAJOR;
	serial_driver->minor_start = 64;
	serial_driver->type = TTY_DRIVER_TYPE_SERIAL;
	serial_driver->subtype = SERIAL_TYPE_NORMAL;
	serial_driver->init_termios = tty_std_termios;
	serial_driver->init_termios.c_cflag =
		B9600 | CS8 | CREAD | HUPCL | CLOCAL;
	serial_driver->flags = TTY_DRIVER_REAL_RAW;
	tty_set_operations(serial_driver, &serial_ops);

	state = rs_table;
	state->port = (पूर्णांक)&custom.serdatr; /* Just to give it a value */
	state->custom_भागisor = 0;
	state->icount.cts = state->icount.dsr = 
	  state->icount.rng = state->icount.dcd = 0;
	state->icount.rx = state->icount.tx = 0;
	state->icount.frame = state->icount.parity = 0;
	state->icount.overrun = state->icount.brk = 0;
	tty_port_init(&state->tport);
	state->tport.ops = &amiga_port_ops;
	tty_port_link_device(&state->tport, serial_driver, 0);

	error = tty_रेजिस्टर_driver(serial_driver);
	अगर (error)
		जाओ fail_put_tty_driver;

	prपूर्णांकk(KERN_INFO "ttyS0 is the amiga builtin serial port\n");

	/* Hardware set up */

	state->baud_base = amiga_colorघड़ी;
	state->xmit_fअगरo_size = 1;

	/* set ISRs, and then disable the rx पूर्णांकerrupts */
	error = request_irq(IRQ_AMIGA_TBE, ser_tx_पूर्णांक, 0, "serial TX", state);
	अगर (error)
		जाओ fail_unरेजिस्टर;

	error = request_irq(IRQ_AMIGA_RBF, ser_rx_पूर्णांक, 0,
			    "serial RX", state);
	अगर (error)
		जाओ fail_मुक्त_irq;

	local_irq_save(flags);

	/* turn off Rx and Tx पूर्णांकerrupts */
	custom.पूर्णांकena = IF_RBF | IF_TBE;
	mb();

	/* clear any pending पूर्णांकerrupt */
	custom.पूर्णांकreq = IF_RBF | IF_TBE;
	mb();

	local_irq_restore(flags);

	/*
	 * set the appropriate directions क्रम the modem control flags,
	 * and clear RTS and DTR
	 */
	ciab.ddra |= (SER_DTR | SER_RTS);   /* outमाला_दो */
	ciab.ddra &= ~(SER_DCD | SER_CTS | SER_DSR);  /* inमाला_दो */

	platक्रमm_set_drvdata(pdev, state);

	वापस 0;

fail_मुक्त_irq:
	मुक्त_irq(IRQ_AMIGA_TBE, state);
fail_unरेजिस्टर:
	tty_unरेजिस्टर_driver(serial_driver);
fail_put_tty_driver:
	tty_port_destroy(&state->tport);
	put_tty_driver(serial_driver);
	वापस error;
पूर्ण

अटल पूर्णांक __निकास amiga_serial_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा serial_state *state = platक्रमm_get_drvdata(pdev);

	/* prपूर्णांकk("Unloading %s: version %s\n", serial_name, serial_version); */
	tty_unरेजिस्टर_driver(serial_driver);
	put_tty_driver(serial_driver);
	tty_port_destroy(&state->tport);

	मुक्त_irq(IRQ_AMIGA_TBE, state);
	मुक्त_irq(IRQ_AMIGA_RBF, state);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver amiga_serial_driver = अणु
	.हटाओ = __निकास_p(amiga_serial_हटाओ),
	.driver   = अणु
		.name	= "amiga-serial",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(amiga_serial_driver, amiga_serial_probe);


#अगर defined(CONFIG_SERIAL_CONSOLE) && !defined(MODULE)

/*
 * ------------------------------------------------------------
 * Serial console driver
 * ------------------------------------------------------------
 */

अटल व्योम amiga_serial_अ_दो(अक्षर c)
अणु
	custom.serdat = (अचिन्हित अक्षर)c | 0x100;
	जबतक (!(custom.serdatr & 0x2000))
		barrier();
पूर्ण

/*
 *	Prपूर्णांक a string to the serial port trying not to disturb
 *	any possible real use of the port...
 *
 *	The console must be locked when we get here.
 */
अटल व्योम serial_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				अचिन्हित count)
अणु
	अचिन्हित लघु पूर्णांकena = custom.पूर्णांकenar;

	custom.पूर्णांकena = IF_TBE;

	जबतक (count--) अणु
		अगर (*s == '\n')
			amiga_serial_अ_दो('\r');
		amiga_serial_अ_दो(*s++);
	पूर्ण

	custom.पूर्णांकena = IF_SETCLR | (पूर्णांकena & IF_TBE);
पूर्ण

अटल काष्ठा tty_driver *serial_console_device(काष्ठा console *c, पूर्णांक *index)
अणु
	*index = 0;
	वापस serial_driver;
पूर्ण

अटल काष्ठा console sercons = अणु
	.name =		"ttyS",
	.ग_लिखो =	serial_console_ग_लिखो,
	.device =	serial_console_device,
	.flags =	CON_PRINTBUFFER,
	.index =	-1,
पूर्ण;

/*
 *	Register console.
 */
अटल पूर्णांक __init amiserial_console_init(व्योम)
अणु
	अगर (!MACH_IS_AMIGA)
		वापस -ENODEV;

	रेजिस्टर_console(&sercons);
	वापस 0;
पूर्ण
console_initcall(amiserial_console_init);

#पूर्ण_अगर /* CONFIG_SERIAL_CONSOLE && !MODULE */

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:amiga-serial");
