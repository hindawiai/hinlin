<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम PowerMac Z85c30 based ESCC cell found in the
 * "macio" ASICs of various PowerMac models
 * 
 * Copyright (C) 2003 Ben. Herrenschmidt (benh@kernel.crashing.org)
 *
 * Derived from drivers/macपूर्णांकosh/macserial.c by Paul Mackerras
 * and drivers/serial/sunzilog.c by David S. Miller
 *
 * Hrm... actually, I ripped most of sunzilog (Thanks David !) and
 * adapted special tweaks needed क्रम us. I करोn't think it's worth
 * merging back those though. The DMA code still has to get in
 * and once करोne, I expect that driver to reमुख्य fairly stable in
 * the दीर्घ term, unless we change the driver model again...
 *
 * 2004-08-06 Harald Welte <laक्रमge@gnumonks.org>
 *	- Enable BREAK पूर्णांकerrupt
 *	- Add support क्रम sysreq
 *
 * TODO:   - Add DMA support
 *         - Defer port shutकरोwn to a few seconds after बंद
 *         - maybe put something right पूर्णांकo uap->clk_भागisor
 */

#अघोषित DEBUG
#अघोषित DEBUG_HARD
#अघोषित USE_CTRL_O_SYSRQ

#समावेश <linux/module.h>
#समावेश <linux/tty.h>

#समावेश <linux/tty_flip.h>
#समावेश <linux/major.h>
#समावेश <linux/माला.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>
#समावेश <linux/bitops.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

#अगर_घोषित CONFIG_PPC_PMAC
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/dbdma.h>
#समावेश <यंत्र/macपन.स>
#अन्यथा
#समावेश <linux/platक्रमm_device.h>
#घोषणा of_machine_is_compatible(x) (0)
#पूर्ण_अगर

#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>

#समावेश "pmac_zilog.h"

/* Not yet implemented */
#अघोषित HAS_DBDMA

अटल अक्षर version[] __initdata = "pmac_zilog: 0.6 (Benjamin Herrenschmidt <benh@kernel.crashing.org>)";
MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("Driver for the Mac and PowerMac serial ports.");
MODULE_LICENSE("GPL");

#अगर_घोषित CONFIG_SERIAL_PMACZILOG_TTYS
#घोषणा PMACZILOG_MAJOR		TTY_MAJOR
#घोषणा PMACZILOG_MINOR		64
#घोषणा PMACZILOG_NAME		"ttyS"
#अन्यथा
#घोषणा PMACZILOG_MAJOR		204
#घोषणा PMACZILOG_MINOR		192
#घोषणा PMACZILOG_NAME		"ttyPZ"
#पूर्ण_अगर

#घोषणा pmz_debug(fmt, arg...)	pr_debug("ttyPZ%d: " fmt, uap->port.line, ## arg)
#घोषणा pmz_error(fmt, arg...)	pr_err("ttyPZ%d: " fmt, uap->port.line, ## arg)
#घोषणा pmz_info(fmt, arg...)	pr_info("ttyPZ%d: " fmt, uap->port.line, ## arg)

/*
 * For the sake of early serial console, we can करो a pre-probe
 * (optional) of the ports at rather early boot समय.
 */
अटल काष्ठा uart_pmac_port	pmz_ports[MAX_ZS_PORTS];
अटल पूर्णांक			pmz_ports_count;

अटल काष्ठा uart_driver pmz_uart_reg = अणु
	.owner		=	THIS_MODULE,
	.driver_name	=	PMACZILOG_NAME,
	.dev_name	=	PMACZILOG_NAME,
	.major		=	PMACZILOG_MAJOR,
	.minor		=	PMACZILOG_MINOR,
पूर्ण;


/* 
 * Load all रेजिस्टरs to reprogram the port
 * This function must only be called when the TX is not busy.  The UART
 * port lock must be held and local पूर्णांकerrupts disabled.
 */
अटल व्योम pmz_load_zsregs(काष्ठा uart_pmac_port *uap, u8 *regs)
अणु
	पूर्णांक i;

	/* Let pending transmits finish.  */
	क्रम (i = 0; i < 1000; i++) अणु
		अचिन्हित अक्षर stat = पढ़ो_zsreg(uap, R1);
		अगर (stat & ALL_SNT)
			अवरोध;
		udelay(100);
	पूर्ण

	ZS_CLEARERR(uap);
	zssync(uap);
	ZS_CLEARFIFO(uap);
	zssync(uap);
	ZS_CLEARERR(uap);

	/* Disable all पूर्णांकerrupts.  */
	ग_लिखो_zsreg(uap, R1,
		    regs[R1] & ~(RxINT_MASK | TxINT_ENAB | EXT_INT_ENAB));

	/* Set parity, sync config, stop bits, and घड़ी भागisor.  */
	ग_लिखो_zsreg(uap, R4, regs[R4]);

	/* Set misc. TX/RX control bits.  */
	ग_लिखो_zsreg(uap, R10, regs[R10]);

	/* Set TX/RX controls sans the enable bits.  */
	ग_लिखो_zsreg(uap, R3, regs[R3] & ~RxENABLE);
	ग_लिखो_zsreg(uap, R5, regs[R5] & ~TxENABLE);

	/* now set R7 "prime" on ESCC */
	ग_लिखो_zsreg(uap, R15, regs[R15] | EN85C30);
	ग_लिखो_zsreg(uap, R7, regs[R7P]);

	/* make sure we use R7 "non-prime" on ESCC */
	ग_लिखो_zsreg(uap, R15, regs[R15] & ~EN85C30);

	/* Synchronous mode config.  */
	ग_लिखो_zsreg(uap, R6, regs[R6]);
	ग_लिखो_zsreg(uap, R7, regs[R7]);

	/* Disable baud generator.  */
	ग_लिखो_zsreg(uap, R14, regs[R14] & ~BRENAB);

	/* Clock mode control.  */
	ग_लिखो_zsreg(uap, R11, regs[R11]);

	/* Lower and upper byte of baud rate generator भागisor.  */
	ग_लिखो_zsreg(uap, R12, regs[R12]);
	ग_लिखो_zsreg(uap, R13, regs[R13]);
	
	/* Now reग_लिखो R14, with BRENAB (अगर set).  */
	ग_लिखो_zsreg(uap, R14, regs[R14]);

	/* Reset बाह्यal status पूर्णांकerrupts.  */
	ग_लिखो_zsreg(uap, R0, RES_EXT_INT);
	ग_लिखो_zsreg(uap, R0, RES_EXT_INT);

	/* Reग_लिखो R3/R5, this समय without enables masked.  */
	ग_लिखो_zsreg(uap, R3, regs[R3]);
	ग_लिखो_zsreg(uap, R5, regs[R5]);

	/* Reग_लिखो R1, this समय without IRQ enabled masked.  */
	ग_लिखो_zsreg(uap, R1, regs[R1]);

	/* Enable पूर्णांकerrupts */
	ग_लिखो_zsreg(uap, R9, regs[R9]);
पूर्ण

/* 
 * We करो like sunzilog to aव्योम disrupting pending Tx
 * Reprogram the Zilog channel HW रेजिस्टरs with the copies found in the
 * software state काष्ठा.  If the transmitter is busy, we defer this update
 * until the next TX complete पूर्णांकerrupt.  Else, we करो it right now.
 *
 * The UART port lock must be held and local पूर्णांकerrupts disabled.
 */
अटल व्योम pmz_maybe_update_regs(काष्ठा uart_pmac_port *uap)
अणु
	अगर (!ZS_REGS_HELD(uap)) अणु
		अगर (ZS_TX_ACTIVE(uap)) अणु
			uap->flags |= PMACZILOG_FLAG_REGS_HELD;
		पूर्ण अन्यथा अणु
			pmz_debug("pmz: maybe_update_regs: updating\n");
			pmz_load_zsregs(uap, uap->curregs);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pmz_पूर्णांकerrupt_control(काष्ठा uart_pmac_port *uap, पूर्णांक enable)
अणु
	अगर (enable) अणु
		uap->curregs[1] |= INT_ALL_Rx | TxINT_ENAB;
		अगर (!ZS_IS_EXTCLK(uap))
			uap->curregs[1] |= EXT_INT_ENAB;
	पूर्ण अन्यथा अणु
		uap->curregs[1] &= ~(EXT_INT_ENAB | TxINT_ENAB | RxINT_MASK);
	पूर्ण
	ग_लिखो_zsreg(uap, R1, uap->curregs[1]);
पूर्ण

अटल bool pmz_receive_अक्षरs(काष्ठा uart_pmac_port *uap)
	__must_hold(&uap->port.lock)
अणु
	काष्ठा tty_port *port;
	अचिन्हित अक्षर ch, r1, drop, flag;
	पूर्णांक loops = 0;

	/* Sanity check, make sure the old bug is no दीर्घer happening */
	अगर (uap->port.state == शून्य) अणु
		WARN_ON(1);
		(व्योम)पढ़ो_zsdata(uap);
		वापस false;
	पूर्ण
	port = &uap->port.state->port;

	जबतक (1) अणु
		drop = 0;

		r1 = पढ़ो_zsreg(uap, R1);
		ch = पढ़ो_zsdata(uap);

		अगर (r1 & (PAR_ERR | Rx_OVR | CRC_ERR)) अणु
			ग_लिखो_zsreg(uap, R0, ERR_RES);
			zssync(uap);
		पूर्ण

		ch &= uap->parity_mask;
		अगर (ch == 0 && uap->flags & PMACZILOG_FLAG_BREAK) अणु
			uap->flags &= ~PMACZILOG_FLAG_BREAK;
		पूर्ण

#अगर defined(CONFIG_MAGIC_SYSRQ) && defined(CONFIG_SERIAL_CORE_CONSOLE)
#अगर_घोषित USE_CTRL_O_SYSRQ
		/* Handle the SysRq ^O Hack */
		अगर (ch == '\x0f') अणु
			uap->port.sysrq = jअगरfies + HZ*5;
			जाओ next_अक्षर;
		पूर्ण
#पूर्ण_अगर /* USE_CTRL_O_SYSRQ */
		अगर (uap->port.sysrq) अणु
			पूर्णांक swallow;
			spin_unlock(&uap->port.lock);
			swallow = uart_handle_sysrq_अक्षर(&uap->port, ch);
			spin_lock(&uap->port.lock);
			अगर (swallow)
				जाओ next_अक्षर;
		पूर्ण
#पूर्ण_अगर /* CONFIG_MAGIC_SYSRQ && CONFIG_SERIAL_CORE_CONSOLE */

		/* A real serial line, record the अक्षरacter and status.  */
		अगर (drop)
			जाओ next_अक्षर;

		flag = TTY_NORMAL;
		uap->port.icount.rx++;

		अगर (r1 & (PAR_ERR | Rx_OVR | CRC_ERR | BRK_ABRT)) अणु
			अगर (r1 & BRK_ABRT) अणु
				pmz_debug("pmz: got break !\n");
				r1 &= ~(PAR_ERR | CRC_ERR);
				uap->port.icount.brk++;
				अगर (uart_handle_अवरोध(&uap->port))
					जाओ next_अक्षर;
			पूर्ण
			अन्यथा अगर (r1 & PAR_ERR)
				uap->port.icount.parity++;
			अन्यथा अगर (r1 & CRC_ERR)
				uap->port.icount.frame++;
			अगर (r1 & Rx_OVR)
				uap->port.icount.overrun++;
			r1 &= uap->port.पढ़ो_status_mask;
			अगर (r1 & BRK_ABRT)
				flag = TTY_BREAK;
			अन्यथा अगर (r1 & PAR_ERR)
				flag = TTY_PARITY;
			अन्यथा अगर (r1 & CRC_ERR)
				flag = TTY_FRAME;
		पूर्ण

		अगर (uap->port.ignore_status_mask == 0xff ||
		    (r1 & uap->port.ignore_status_mask) == 0) अणु
			tty_insert_flip_अक्षर(port, ch, flag);
		पूर्ण
		अगर (r1 & Rx_OVR)
			tty_insert_flip_अक्षर(port, 0, TTY_OVERRUN);
	next_अक्षर:
		/* We can get stuck in an infinite loop getting अक्षर 0 when the
		 * line is in a wrong HW state, we अवरोध that here.
		 * When that happens, I disable the receive side of the driver.
		 * Note that what I've been experiencing is a real irq loop where
		 * I'm getting flooded regardless of the actual port speed.
		 * Something strange is going on with the HW
		 */
		अगर ((++loops) > 1000)
			जाओ flood;
		ch = पढ़ो_zsreg(uap, R0);
		अगर (!(ch & Rx_CH_AV))
			अवरोध;
	पूर्ण

	वापस true;
 flood:
	pmz_पूर्णांकerrupt_control(uap, 0);
	pmz_error("pmz: rx irq flood !\n");
	वापस true;
पूर्ण

अटल व्योम pmz_status_handle(काष्ठा uart_pmac_port *uap)
अणु
	अचिन्हित अक्षर status;

	status = पढ़ो_zsreg(uap, R0);
	ग_लिखो_zsreg(uap, R0, RES_EXT_INT);
	zssync(uap);

	अगर (ZS_IS_OPEN(uap) && ZS_WANTS_MODEM_STATUS(uap)) अणु
		अगर (status & SYNC_HUNT)
			uap->port.icount.dsr++;

		/* The Zilog just gives us an पूर्णांकerrupt when DCD/CTS/etc. change.
		 * But it करोes not tell us which bit has changed, we have to keep
		 * track of this ourselves.
		 * The CTS input is inverted क्रम some reason.  -- paulus
		 */
		अगर ((status ^ uap->prev_status) & DCD)
			uart_handle_dcd_change(&uap->port,
					       (status & DCD));
		अगर ((status ^ uap->prev_status) & CTS)
			uart_handle_cts_change(&uap->port,
					       !(status & CTS));

		wake_up_पूर्णांकerruptible(&uap->port.state->port.delta_msr_रुको);
	पूर्ण

	अगर (status & BRK_ABRT)
		uap->flags |= PMACZILOG_FLAG_BREAK;

	uap->prev_status = status;
पूर्ण

अटल व्योम pmz_transmit_अक्षरs(काष्ठा uart_pmac_port *uap)
अणु
	काष्ठा circ_buf *xmit;

	अगर (ZS_IS_CONS(uap)) अणु
		अचिन्हित अक्षर status = पढ़ो_zsreg(uap, R0);

		/* TX still busy?  Just रुको क्रम the next TX करोne पूर्णांकerrupt.
		 *
		 * It can occur because of how we करो serial console ग_लिखोs.  It would
		 * be nice to transmit console ग_लिखोs just like we normally would क्रम
		 * a TTY line. (ie. buffered and TX पूर्णांकerrupt driven).  That is not
		 * easy because console ग_लिखोs cannot sleep.  One solution might be
		 * to poll on enough port->xmit space becoming मुक्त.  -DaveM
		 */
		अगर (!(status & Tx_BUF_EMP))
			वापस;
	पूर्ण

	uap->flags &= ~PMACZILOG_FLAG_TX_ACTIVE;

	अगर (ZS_REGS_HELD(uap)) अणु
		pmz_load_zsregs(uap, uap->curregs);
		uap->flags &= ~PMACZILOG_FLAG_REGS_HELD;
	पूर्ण

	अगर (ZS_TX_STOPPED(uap)) अणु
		uap->flags &= ~PMACZILOG_FLAG_TX_STOPPED;
		जाओ ack_tx_पूर्णांक;
	पूर्ण

	/* Under some circumstances, we see पूर्णांकerrupts reported क्रम
	 * a बंदd channel. The पूर्णांकerrupt mask in R1 is clear, but
	 * R3 still संकेतs the पूर्णांकerrupts and we see them when taking
	 * an पूर्णांकerrupt क्रम the other channel (this could be a qemu
	 * bug but since the ESCC करोc करोesn't specअगरy precsiely whether
	 * R3 पूर्णांकerrup status bits are masked by R1 पूर्णांकerrupt enable
	 * bits, better safe than sorry). --BenH.
	 */
	अगर (!ZS_IS_OPEN(uap))
		जाओ ack_tx_पूर्णांक;

	अगर (uap->port.x_अक्षर) अणु
		uap->flags |= PMACZILOG_FLAG_TX_ACTIVE;
		ग_लिखो_zsdata(uap, uap->port.x_अक्षर);
		zssync(uap);
		uap->port.icount.tx++;
		uap->port.x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (uap->port.state == शून्य)
		जाओ ack_tx_पूर्णांक;
	xmit = &uap->port.state->xmit;
	अगर (uart_circ_empty(xmit)) अणु
		uart_ग_लिखो_wakeup(&uap->port);
		जाओ ack_tx_पूर्णांक;
	पूर्ण
	अगर (uart_tx_stopped(&uap->port))
		जाओ ack_tx_पूर्णांक;

	uap->flags |= PMACZILOG_FLAG_TX_ACTIVE;
	ग_लिखो_zsdata(uap, xmit->buf[xmit->tail]);
	zssync(uap);

	xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
	uap->port.icount.tx++;

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&uap->port);

	वापस;

ack_tx_पूर्णांक:
	ग_लिखो_zsreg(uap, R0, RES_Tx_P);
	zssync(uap);
पूर्ण

/* Hrm... we रेजिस्टर that twice, fixme later.... */
अटल irqवापस_t pmz_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_pmac_port *uap = dev_id;
	काष्ठा uart_pmac_port *uap_a;
	काष्ठा uart_pmac_port *uap_b;
	पूर्णांक rc = IRQ_NONE;
	bool push;
	u8 r3;

	uap_a = pmz_get_port_A(uap);
	uap_b = uap_a->mate;

	spin_lock(&uap_a->port.lock);
	r3 = पढ़ो_zsreg(uap_a, R3);

#अगर_घोषित DEBUG_HARD
	pmz_debug("irq, r3: %x\n", r3);
#पूर्ण_अगर
	/* Channel A */
	push = false;
	अगर (r3 & (CHAEXT | CHATxIP | CHARxIP)) अणु
		अगर (!ZS_IS_OPEN(uap_a)) अणु
			pmz_debug("ChanA interrupt while not open !\n");
			जाओ skip_a;
		पूर्ण
		ग_लिखो_zsreg(uap_a, R0, RES_H_IUS);
		zssync(uap_a);		
		अगर (r3 & CHAEXT)
			pmz_status_handle(uap_a);
		अगर (r3 & CHARxIP)
			push = pmz_receive_अक्षरs(uap_a);
		अगर (r3 & CHATxIP)
			pmz_transmit_अक्षरs(uap_a);
		rc = IRQ_HANDLED;
	पूर्ण
 skip_a:
	spin_unlock(&uap_a->port.lock);
	अगर (push)
		tty_flip_buffer_push(&uap->port.state->port);

	अगर (!uap_b)
		जाओ out;

	spin_lock(&uap_b->port.lock);
	push = false;
	अगर (r3 & (CHBEXT | CHBTxIP | CHBRxIP)) अणु
		अगर (!ZS_IS_OPEN(uap_b)) अणु
			pmz_debug("ChanB interrupt while not open !\n");
			जाओ skip_b;
		पूर्ण
		ग_लिखो_zsreg(uap_b, R0, RES_H_IUS);
		zssync(uap_b);
		अगर (r3 & CHBEXT)
			pmz_status_handle(uap_b);
		अगर (r3 & CHBRxIP)
			push = pmz_receive_अक्षरs(uap_b);
		अगर (r3 & CHBTxIP)
			pmz_transmit_अक्षरs(uap_b);
		rc = IRQ_HANDLED;
	पूर्ण
 skip_b:
	spin_unlock(&uap_b->port.lock);
	अगर (push)
		tty_flip_buffer_push(&uap->port.state->port);

 out:
	वापस rc;
पूर्ण

/*
 * Peek the status रेजिस्टर, lock not held by caller
 */
अटल अंतरभूत u8 pmz_peek_status(काष्ठा uart_pmac_port *uap)
अणु
	अचिन्हित दीर्घ flags;
	u8 status;
	
	spin_lock_irqsave(&uap->port.lock, flags);
	status = पढ़ो_zsreg(uap, R0);
	spin_unlock_irqrestore(&uap->port.lock, flags);

	वापस status;
पूर्ण

/* 
 * Check अगर transmitter is empty
 * The port lock is not held.
 */
अटल अचिन्हित पूर्णांक pmz_tx_empty(काष्ठा uart_port *port)
अणु
	अचिन्हित अक्षर status;

	status = pmz_peek_status(to_pmz(port));
	अगर (status & Tx_BUF_EMP)
		वापस TIOCSER_TEMT;
	वापस 0;
पूर्ण

/* 
 * Set Modem Control (RTS & DTR) bits
 * The port lock is held and पूर्णांकerrupts are disabled.
 * Note: Shall we really filter out RTS on बाह्यal ports or
 * should that be dealt at higher level only ?
 */
अटल व्योम pmz_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा uart_pmac_port *uap = to_pmz(port);
	अचिन्हित अक्षर set_bits, clear_bits;

        /* Do nothing क्रम irda क्रम now... */
	अगर (ZS_IS_IRDA(uap))
		वापस;
	/* We get called during boot with a port not up yet */
	अगर (!(ZS_IS_OPEN(uap) || ZS_IS_CONS(uap)))
		वापस;

	set_bits = clear_bits = 0;

	अगर (ZS_IS_INTMODEM(uap)) अणु
		अगर (mctrl & TIOCM_RTS)
			set_bits |= RTS;
		अन्यथा
			clear_bits |= RTS;
	पूर्ण
	अगर (mctrl & TIOCM_DTR)
		set_bits |= DTR;
	अन्यथा
		clear_bits |= DTR;

	/* NOTE: Not subject to 'transmitter active' rule.  */ 
	uap->curregs[R5] |= set_bits;
	uap->curregs[R5] &= ~clear_bits;

	ग_लिखो_zsreg(uap, R5, uap->curregs[R5]);
	pmz_debug("pmz_set_mctrl: set bits: %x, clear bits: %x -> %x\n",
		  set_bits, clear_bits, uap->curregs[R5]);
	zssync(uap);
पूर्ण

/* 
 * Get Modem Control bits (only the input ones, the core will
 * or that with a cached value of the control ones)
 * The port lock is held and पूर्णांकerrupts are disabled.
 */
अटल अचिन्हित पूर्णांक pmz_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pmac_port *uap = to_pmz(port);
	अचिन्हित अक्षर status;
	अचिन्हित पूर्णांक ret;

	status = पढ़ो_zsreg(uap, R0);

	ret = 0;
	अगर (status & DCD)
		ret |= TIOCM_CAR;
	अगर (status & SYNC_HUNT)
		ret |= TIOCM_DSR;
	अगर (!(status & CTS))
		ret |= TIOCM_CTS;

	वापस ret;
पूर्ण

/* 
 * Stop TX side. Dealt like sunzilog at next Tx पूर्णांकerrupt,
 * though क्रम DMA, we will have to करो a bit more.
 * The port lock is held and पूर्णांकerrupts are disabled.
 */
अटल व्योम pmz_stop_tx(काष्ठा uart_port *port)
अणु
	to_pmz(port)->flags |= PMACZILOG_FLAG_TX_STOPPED;
पूर्ण

/* 
 * Kick the Tx side.
 * The port lock is held and पूर्णांकerrupts are disabled.
 */
अटल व्योम pmz_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pmac_port *uap = to_pmz(port);
	अचिन्हित अक्षर status;

	pmz_debug("pmz: start_tx()\n");

	uap->flags |= PMACZILOG_FLAG_TX_ACTIVE;
	uap->flags &= ~PMACZILOG_FLAG_TX_STOPPED;

	status = पढ़ो_zsreg(uap, R0);

	/* TX busy?  Just रुको क्रम the TX करोne पूर्णांकerrupt.  */
	अगर (!(status & Tx_BUF_EMP))
		वापस;

	/* Send the first अक्षरacter to jump-start the TX करोne
	 * IRQ sending engine.
	 */
	अगर (port->x_अक्षर) अणु
		ग_लिखो_zsdata(uap, port->x_अक्षर);
		zssync(uap);
		port->icount.tx++;
		port->x_अक्षर = 0;
	पूर्ण अन्यथा अणु
		काष्ठा circ_buf *xmit = &port->state->xmit;

		अगर (uart_circ_empty(xmit))
			जाओ out;
		ग_लिखो_zsdata(uap, xmit->buf[xmit->tail]);
		zssync(uap);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;

		अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
			uart_ग_लिखो_wakeup(&uap->port);
	पूर्ण
 out:
	pmz_debug("pmz: start_tx() done.\n");
पूर्ण

/* 
 * Stop Rx side, basically disable emitting of
 * Rx पूर्णांकerrupts on the port. We करोn't disable the rx
 * side of the chip proper though
 * The port lock is held.
 */
अटल व्योम pmz_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pmac_port *uap = to_pmz(port);

	pmz_debug("pmz: stop_rx()()\n");

	/* Disable all RX पूर्णांकerrupts.  */
	uap->curregs[R1] &= ~RxINT_MASK;
	pmz_maybe_update_regs(uap);

	pmz_debug("pmz: stop_rx() done.\n");
पूर्ण

/* 
 * Enable modem status change पूर्णांकerrupts
 * The port lock is held.
 */
अटल व्योम pmz_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pmac_port *uap = to_pmz(port);
	अचिन्हित अक्षर new_reg;

	अगर (ZS_IS_IRDA(uap))
		वापस;
	new_reg = uap->curregs[R15] | (DCDIE | SYNCIE | CTSIE);
	अगर (new_reg != uap->curregs[R15]) अणु
		uap->curregs[R15] = new_reg;

		/* NOTE: Not subject to 'transmitter active' rule. */
		ग_लिखो_zsreg(uap, R15, uap->curregs[R15]);
	पूर्ण
पूर्ण

/* 
 * Control अवरोध state emission
 * The port lock is not held.
 */
अटल व्योम pmz_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा uart_pmac_port *uap = to_pmz(port);
	अचिन्हित अक्षर set_bits, clear_bits, new_reg;
	अचिन्हित दीर्घ flags;

	set_bits = clear_bits = 0;

	अगर (अवरोध_state)
		set_bits |= SND_BRK;
	अन्यथा
		clear_bits |= SND_BRK;

	spin_lock_irqsave(&port->lock, flags);

	new_reg = (uap->curregs[R5] | set_bits) & ~clear_bits;
	अगर (new_reg != uap->curregs[R5]) अणु
		uap->curregs[R5] = new_reg;
		ग_लिखो_zsreg(uap, R5, uap->curregs[R5]);
	पूर्ण

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

#अगर_घोषित CONFIG_PPC_PMAC

/*
 * Turn घातer on or off to the SCC and associated stuff
 * (port drivers, modem, IR port, etc.)
 * Returns the number of milliseconds we should रुको beक्रमe
 * trying to use the port.
 */
अटल पूर्णांक pmz_set_scc_घातer(काष्ठा uart_pmac_port *uap, पूर्णांक state)
अणु
	पूर्णांक delay = 0;
	पूर्णांक rc;

	अगर (state) अणु
		rc = pmac_call_feature(
			PMAC_FTR_SCC_ENABLE, uap->node, uap->port_type, 1);
		pmz_debug("port power on result: %d\n", rc);
		अगर (ZS_IS_INTMODEM(uap)) अणु
			rc = pmac_call_feature(
				PMAC_FTR_MODEM_ENABLE, uap->node, 0, 1);
			delay = 2500;	/* रुको क्रम 2.5s beक्रमe using */
			pmz_debug("modem power result: %d\n", rc);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* TODO: Make that depend on a समयr, करोn't घातer करोwn
		 * immediately
		 */
		अगर (ZS_IS_INTMODEM(uap)) अणु
			rc = pmac_call_feature(
				PMAC_FTR_MODEM_ENABLE, uap->node, 0, 0);
			pmz_debug("port power off result: %d\n", rc);
		पूर्ण
		pmac_call_feature(PMAC_FTR_SCC_ENABLE, uap->node, uap->port_type, 0);
	पूर्ण
	वापस delay;
पूर्ण

#अन्यथा

अटल पूर्णांक pmz_set_scc_घातer(काष्ठा uart_pmac_port *uap, पूर्णांक state)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !CONFIG_PPC_PMAC */

/*
 * FixZeroBug....Works around a bug in the SCC receiving channel.
 * Inspired from Darwin code, 15 Sept. 2000  -DanM
 *
 * The following sequence prevents a problem that is seen with O'Hare ASICs
 * (most versions -- also with some Heathrow and Hydra ASICs) where a zero
 * at the input to the receiver becomes 'stuck' and locks up the receiver.
 * This problem can occur as a result of a zero bit at the receiver input
 * coincident with any of the following events:
 *
 *	The SCC is initialized (hardware or software).
 *	A framing error is detected.
 *	The घड़ीing option changes from synchronous or X1 asynchronous
 *		घड़ीing to X16, X32, or X64 asynchronous घड़ीing.
 *	The decoding mode is changed among NRZ, NRZI, FM0, or FM1.
 *
 * This workaround attempts to recover from the lockup condition by placing
 * the SCC in synchronous loopback mode with a fast घड़ी beक्रमe programming
 * any of the asynchronous modes.
 */
अटल व्योम pmz_fix_zero_bug_scc(काष्ठा uart_pmac_port *uap)
अणु
	ग_लिखो_zsreg(uap, 9, ZS_IS_CHANNEL_A(uap) ? CHRA : CHRB);
	zssync(uap);
	udelay(10);
	ग_लिखो_zsreg(uap, 9, (ZS_IS_CHANNEL_A(uap) ? CHRA : CHRB) | NV);
	zssync(uap);

	ग_लिखो_zsreg(uap, 4, X1CLK | MONSYNC);
	ग_लिखो_zsreg(uap, 3, Rx8);
	ग_लिखो_zsreg(uap, 5, Tx8 | RTS);
	ग_लिखो_zsreg(uap, 9, NV);	/* Didn't we alपढ़ोy करो this? */
	ग_लिखो_zsreg(uap, 11, RCBR | TCBR);
	ग_लिखो_zsreg(uap, 12, 0);
	ग_लिखो_zsreg(uap, 13, 0);
	ग_लिखो_zsreg(uap, 14, (LOOPBAK | BRSRC));
	ग_लिखो_zsreg(uap, 14, (LOOPBAK | BRSRC | BRENAB));
	ग_लिखो_zsreg(uap, 3, Rx8 | RxENABLE);
	ग_लिखो_zsreg(uap, 0, RES_EXT_INT);
	ग_लिखो_zsreg(uap, 0, RES_EXT_INT);
	ग_लिखो_zsreg(uap, 0, RES_EXT_INT);	/* to समाप्त some समय */

	/* The channel should be OK now, but it is probably receiving
	 * loopback garbage.
	 * Switch to asynchronous mode, disable the receiver,
	 * and discard everything in the receive buffer.
	 */
	ग_लिखो_zsreg(uap, 9, NV);
	ग_लिखो_zsreg(uap, 4, X16CLK | SB_MASK);
	ग_लिखो_zsreg(uap, 3, Rx8);

	जबतक (पढ़ो_zsreg(uap, 0) & Rx_CH_AV) अणु
		(व्योम)पढ़ो_zsreg(uap, 8);
		ग_लिखो_zsreg(uap, 0, RES_EXT_INT);
		ग_लिखो_zsreg(uap, 0, ERR_RES);
	पूर्ण
पूर्ण

/*
 * Real startup routine, घातers up the hardware and sets up
 * the SCC. Returns a delay in ms where you need to रुको beक्रमe
 * actually using the port, this is typically the पूर्णांकernal modem
 * घातerup delay. This routine expect the lock to be taken.
 */
अटल पूर्णांक __pmz_startup(काष्ठा uart_pmac_port *uap)
अणु
	पूर्णांक pwr_delay = 0;

	स_रखो(&uap->curregs, 0, माप(uap->curregs));

	/* Power up the SCC & underlying hardware (modem/irda) */
	pwr_delay = pmz_set_scc_घातer(uap, 1);

	/* Nice buggy HW ... */
	pmz_fix_zero_bug_scc(uap);

	/* Reset the channel */
	uap->curregs[R9] = 0;
	ग_लिखो_zsreg(uap, 9, ZS_IS_CHANNEL_A(uap) ? CHRA : CHRB);
	zssync(uap);
	udelay(10);
	ग_लिखो_zsreg(uap, 9, 0);
	zssync(uap);

	/* Clear the पूर्णांकerrupt रेजिस्टरs */
	ग_लिखो_zsreg(uap, R1, 0);
	ग_लिखो_zsreg(uap, R0, ERR_RES);
	ग_लिखो_zsreg(uap, R0, ERR_RES);
	ग_लिखो_zsreg(uap, R0, RES_H_IUS);
	ग_लिखो_zsreg(uap, R0, RES_H_IUS);

	/* Setup some valid baud rate */
	uap->curregs[R4] = X16CLK | SB1;
	uap->curregs[R3] = Rx8;
	uap->curregs[R5] = Tx8 | RTS;
	अगर (!ZS_IS_IRDA(uap))
		uap->curregs[R5] |= DTR;
	uap->curregs[R12] = 0;
	uap->curregs[R13] = 0;
	uap->curregs[R14] = BRENAB;

	/* Clear handshaking, enable BREAK पूर्णांकerrupts */
	uap->curregs[R15] = BRKIE;

	/* Master पूर्णांकerrupt enable */
	uap->curregs[R9] |= NV | MIE;

	pmz_load_zsregs(uap, uap->curregs);

	/* Enable receiver and transmitter.  */
	ग_लिखो_zsreg(uap, R3, uap->curregs[R3] |= RxENABLE);
	ग_लिखो_zsreg(uap, R5, uap->curregs[R5] |= TxENABLE);

	/* Remember status क्रम DCD/CTS changes */
	uap->prev_status = पढ़ो_zsreg(uap, R0);

	वापस pwr_delay;
पूर्ण

अटल व्योम pmz_irda_reset(काष्ठा uart_pmac_port *uap)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&uap->port.lock, flags);
	uap->curregs[R5] |= DTR;
	ग_लिखो_zsreg(uap, R5, uap->curregs[R5]);
	zssync(uap);
	spin_unlock_irqrestore(&uap->port.lock, flags);
	msleep(110);

	spin_lock_irqsave(&uap->port.lock, flags);
	uap->curregs[R5] &= ~DTR;
	ग_लिखो_zsreg(uap, R5, uap->curregs[R5]);
	zssync(uap);
	spin_unlock_irqrestore(&uap->port.lock, flags);
	msleep(10);
पूर्ण

/*
 * This is the "normal" startup routine, using the above one
 * wrapped with the lock and करोing a schedule delay
 */
अटल पूर्णांक pmz_startup(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pmac_port *uap = to_pmz(port);
	अचिन्हित दीर्घ flags;
	पूर्णांक pwr_delay = 0;

	pmz_debug("pmz: startup()\n");

	uap->flags |= PMACZILOG_FLAG_IS_OPEN;

	/* A console is never घातered करोwn. Else, घातer up and
	 * initialize the chip
	 */
	अगर (!ZS_IS_CONS(uap)) अणु
		spin_lock_irqsave(&port->lock, flags);
		pwr_delay = __pmz_startup(uap);
		spin_unlock_irqrestore(&port->lock, flags);
	पूर्ण	
	प्र_लिखो(uap->irq_name, PMACZILOG_NAME"%d", uap->port.line);
	अगर (request_irq(uap->port.irq, pmz_पूर्णांकerrupt, IRQF_SHARED,
			uap->irq_name, uap)) अणु
		pmz_error("Unable to register zs interrupt handler.\n");
		pmz_set_scc_घातer(uap, 0);
		वापस -ENXIO;
	पूर्ण

	/* Right now, we deal with delay by blocking here, I'll be
	 * smarter later on
	 */
	अगर (pwr_delay != 0) अणु
		pmz_debug("pmz: delaying %d ms\n", pwr_delay);
		msleep(pwr_delay);
	पूर्ण

	/* IrDA reset is करोne now */
	अगर (ZS_IS_IRDA(uap))
		pmz_irda_reset(uap);

	/* Enable पूर्णांकerrupt requests क्रम the channel */
	spin_lock_irqsave(&port->lock, flags);
	pmz_पूर्णांकerrupt_control(uap, 1);
	spin_unlock_irqrestore(&port->lock, flags);

	pmz_debug("pmz: startup() done.\n");

	वापस 0;
पूर्ण

अटल व्योम pmz_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pmac_port *uap = to_pmz(port);
	अचिन्हित दीर्घ flags;

	pmz_debug("pmz: shutdown()\n");

	spin_lock_irqsave(&port->lock, flags);

	/* Disable पूर्णांकerrupt requests क्रम the channel */
	pmz_पूर्णांकerrupt_control(uap, 0);

	अगर (!ZS_IS_CONS(uap)) अणु
		/* Disable receiver and transmitter */
		uap->curregs[R3] &= ~RxENABLE;
		uap->curregs[R5] &= ~TxENABLE;

		/* Disable अवरोध निश्चितion */
		uap->curregs[R5] &= ~SND_BRK;
		pmz_maybe_update_regs(uap);
	पूर्ण

	spin_unlock_irqrestore(&port->lock, flags);

	/* Release पूर्णांकerrupt handler */
	मुक्त_irq(uap->port.irq, uap);

	spin_lock_irqsave(&port->lock, flags);

	uap->flags &= ~PMACZILOG_FLAG_IS_OPEN;

	अगर (!ZS_IS_CONS(uap))
		pmz_set_scc_घातer(uap, 0);	/* Shut the chip करोwn */

	spin_unlock_irqrestore(&port->lock, flags);

	pmz_debug("pmz: shutdown() done.\n");
पूर्ण

/* Shared by TTY driver and serial console setup.  The port lock is held
 * and local पूर्णांकerrupts are disabled.
 */
अटल व्योम pmz_convert_to_zs(काष्ठा uart_pmac_port *uap, अचिन्हित पूर्णांक cflag,
			      अचिन्हित पूर्णांक अगरlag, अचिन्हित दीर्घ baud)
अणु
	पूर्णांक brg;

	/* Switch to बाह्यal घड़ीing क्रम IrDA high घड़ी rates. That
	 * code could be re-used क्रम Midi पूर्णांकerfaces with dअगरferent
	 * multipliers
	 */
	अगर (baud >= 115200 && ZS_IS_IRDA(uap)) अणु
		uap->curregs[R4] = X1CLK;
		uap->curregs[R11] = RCTRxCP | TCTRxCP;
		uap->curregs[R14] = 0; /* BRG off */
		uap->curregs[R12] = 0;
		uap->curregs[R13] = 0;
		uap->flags |= PMACZILOG_FLAG_IS_EXTCLK;
	पूर्ण अन्यथा अणु
		चयन (baud) अणु
		हाल ZS_CLOCK/16:	/* 230400 */
			uap->curregs[R4] = X16CLK;
			uap->curregs[R11] = 0;
			uap->curregs[R14] = 0;
			अवरोध;
		हाल ZS_CLOCK/32:	/* 115200 */
			uap->curregs[R4] = X32CLK;
			uap->curregs[R11] = 0;
			uap->curregs[R14] = 0;
			अवरोध;
		शेष:
			uap->curregs[R4] = X16CLK;
			uap->curregs[R11] = TCBR | RCBR;
			brg = BPS_TO_BRG(baud, ZS_CLOCK / 16);
			uap->curregs[R12] = (brg & 255);
			uap->curregs[R13] = ((brg >> 8) & 255);
			uap->curregs[R14] = BRENAB;
		पूर्ण
		uap->flags &= ~PMACZILOG_FLAG_IS_EXTCLK;
	पूर्ण

	/* Character size, stop bits, and parity. */
	uap->curregs[3] &= ~RxN_MASK;
	uap->curregs[5] &= ~TxN_MASK;

	चयन (cflag & CSIZE) अणु
	हाल CS5:
		uap->curregs[3] |= Rx5;
		uap->curregs[5] |= Tx5;
		uap->parity_mask = 0x1f;
		अवरोध;
	हाल CS6:
		uap->curregs[3] |= Rx6;
		uap->curregs[5] |= Tx6;
		uap->parity_mask = 0x3f;
		अवरोध;
	हाल CS7:
		uap->curregs[3] |= Rx7;
		uap->curregs[5] |= Tx7;
		uap->parity_mask = 0x7f;
		अवरोध;
	हाल CS8:
	शेष:
		uap->curregs[3] |= Rx8;
		uap->curregs[5] |= Tx8;
		uap->parity_mask = 0xff;
		अवरोध;
	पूर्ण
	uap->curregs[4] &= ~(SB_MASK);
	अगर (cflag & CSTOPB)
		uap->curregs[4] |= SB2;
	अन्यथा
		uap->curregs[4] |= SB1;
	अगर (cflag & PARENB)
		uap->curregs[4] |= PAR_ENAB;
	अन्यथा
		uap->curregs[4] &= ~PAR_ENAB;
	अगर (!(cflag & PARODD))
		uap->curregs[4] |= PAR_EVEN;
	अन्यथा
		uap->curregs[4] &= ~PAR_EVEN;

	uap->port.पढ़ो_status_mask = Rx_OVR;
	अगर (अगरlag & INPCK)
		uap->port.पढ़ो_status_mask |= CRC_ERR | PAR_ERR;
	अगर (अगरlag & (IGNBRK | BRKINT | PARMRK))
		uap->port.पढ़ो_status_mask |= BRK_ABRT;

	uap->port.ignore_status_mask = 0;
	अगर (अगरlag & IGNPAR)
		uap->port.ignore_status_mask |= CRC_ERR | PAR_ERR;
	अगर (अगरlag & IGNBRK) अणु
		uap->port.ignore_status_mask |= BRK_ABRT;
		अगर (अगरlag & IGNPAR)
			uap->port.ignore_status_mask |= Rx_OVR;
	पूर्ण

	अगर ((cflag & CREAD) == 0)
		uap->port.ignore_status_mask = 0xff;
पूर्ण


/*
 * Set the irda codec on the imac to the specअगरied baud rate.
 */
अटल व्योम pmz_irda_setup(काष्ठा uart_pmac_port *uap, अचिन्हित दीर्घ *baud)
अणु
	u8 cmdbyte;
	पूर्णांक t, version;

	चयन (*baud) अणु
	/* SIR modes */
	हाल 2400:
		cmdbyte = 0x53;
		अवरोध;
	हाल 4800:
		cmdbyte = 0x52;
		अवरोध;
	हाल 9600:
		cmdbyte = 0x51;
		अवरोध;
	हाल 19200:
		cmdbyte = 0x50;
		अवरोध;
	हाल 38400:
		cmdbyte = 0x4f;
		अवरोध;
	हाल 57600:
		cmdbyte = 0x4e;
		अवरोध;
	हाल 115200:
		cmdbyte = 0x4d;
		अवरोध;
	/* The FIR modes aren't really supported at this poपूर्णांक, how
	 * करो we select the speed ? via the FCR on KeyLargo ?
	 */
	हाल 1152000:
		cmdbyte = 0;
		अवरोध;
	हाल 4000000:
		cmdbyte = 0;
		अवरोध;
	शेष: /* 9600 */
		cmdbyte = 0x51;
		*baud = 9600;
		अवरोध;
	पूर्ण

	/* Wait क्रम transmitter to drain */
	t = 10000;
	जबतक ((पढ़ो_zsreg(uap, R0) & Tx_BUF_EMP) == 0
	       || (पढ़ो_zsreg(uap, R1) & ALL_SNT) == 0) अणु
		अगर (--t <= 0) अणु
			pmz_error("transmitter didn't drain\n");
			वापस;
		पूर्ण
		udelay(10);
	पूर्ण

	/* Drain the receiver too */
	t = 100;
	(व्योम)पढ़ो_zsdata(uap);
	(व्योम)पढ़ो_zsdata(uap);
	(व्योम)पढ़ो_zsdata(uap);
	mdelay(10);
	जबतक (पढ़ो_zsreg(uap, R0) & Rx_CH_AV) अणु
		पढ़ो_zsdata(uap);
		mdelay(10);
		अगर (--t <= 0) अणु
			pmz_error("receiver didn't drain\n");
			वापस;
		पूर्ण
	पूर्ण

	/* Switch to command mode */
	uap->curregs[R5] |= DTR;
	ग_लिखो_zsreg(uap, R5, uap->curregs[R5]);
	zssync(uap);
	mdelay(1);

	/* Switch SCC to 19200 */
	pmz_convert_to_zs(uap, CS8, 0, 19200);		
	pmz_load_zsregs(uap, uap->curregs);
	mdelay(1);

	/* Write get_version command byte */
	ग_लिखो_zsdata(uap, 1);
	t = 5000;
	जबतक ((पढ़ो_zsreg(uap, R0) & Rx_CH_AV) == 0) अणु
		अगर (--t <= 0) अणु
			pmz_error("irda_setup timed out on get_version byte\n");
			जाओ out;
		पूर्ण
		udelay(10);
	पूर्ण
	version = पढ़ो_zsdata(uap);

	अगर (version < 4) अणु
		pmz_info("IrDA: dongle version %d not supported\n", version);
		जाओ out;
	पूर्ण

	/* Send speed mode */
	ग_लिखो_zsdata(uap, cmdbyte);
	t = 5000;
	जबतक ((पढ़ो_zsreg(uap, R0) & Rx_CH_AV) == 0) अणु
		अगर (--t <= 0) अणु
			pmz_error("irda_setup timed out on speed mode byte\n");
			जाओ out;
		पूर्ण
		udelay(10);
	पूर्ण
	t = पढ़ो_zsdata(uap);
	अगर (t != cmdbyte)
		pmz_error("irda_setup speed mode byte = %x (%x)\n", t, cmdbyte);

	pmz_info("IrDA setup for %ld bps, dongle version: %d\n",
		 *baud, version);

	(व्योम)पढ़ो_zsdata(uap);
	(व्योम)पढ़ो_zsdata(uap);
	(व्योम)पढ़ो_zsdata(uap);

 out:
	/* Switch back to data mode */
	uap->curregs[R5] &= ~DTR;
	ग_लिखो_zsreg(uap, R5, uap->curregs[R5]);
	zssync(uap);

	(व्योम)पढ़ो_zsdata(uap);
	(व्योम)पढ़ो_zsdata(uap);
	(व्योम)पढ़ो_zsdata(uap);
पूर्ण


अटल व्योम __pmz_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
			      काष्ठा ktermios *old)
अणु
	काष्ठा uart_pmac_port *uap = to_pmz(port);
	अचिन्हित दीर्घ baud;

	pmz_debug("pmz: set_termios()\n");

	स_नकल(&uap->termios_cache, termios, माप(काष्ठा ktermios));

	/* XXX Check which revs of machines actually allow 1 and 4Mb speeds
	 * on the IR करोngle. Note that the IRTTY driver currently करोesn't know
	 * about the FIR mode and high speed modes. So these are unused. For
	 * implementing proper support क्रम these, we should probably add some
	 * DMA as well, at least on the Rx side, which isn't a simple thing
	 * at this poपूर्णांक.
	 */
	अगर (ZS_IS_IRDA(uap)) अणु
		/* Calc baud rate */
		baud = uart_get_baud_rate(port, termios, old, 1200, 4000000);
		pmz_debug("pmz: switch IRDA to %ld bauds\n", baud);
		/* Cet the irda codec to the right rate */
		pmz_irda_setup(uap, &baud);
		/* Set final baud rate */
		pmz_convert_to_zs(uap, termios->c_cflag, termios->c_अगरlag, baud);
		pmz_load_zsregs(uap, uap->curregs);
		zssync(uap);
	पूर्ण अन्यथा अणु
		baud = uart_get_baud_rate(port, termios, old, 1200, 230400);
		pmz_convert_to_zs(uap, termios->c_cflag, termios->c_अगरlag, baud);
		/* Make sure modem status पूर्णांकerrupts are correctly configured */
		अगर (UART_ENABLE_MS(&uap->port, termios->c_cflag)) अणु
			uap->curregs[R15] |= DCDIE | SYNCIE | CTSIE;
			uap->flags |= PMACZILOG_FLAG_MODEM_STATUS;
		पूर्ण अन्यथा अणु
			uap->curregs[R15] &= ~(DCDIE | SYNCIE | CTSIE);
			uap->flags &= ~PMACZILOG_FLAG_MODEM_STATUS;
		पूर्ण

		/* Load रेजिस्टरs to the chip */
		pmz_maybe_update_regs(uap);
	पूर्ण
	uart_update_समयout(port, termios->c_cflag, baud);

	pmz_debug("pmz: set_termios() done.\n");
पूर्ण

/* The port lock is not held.  */
अटल व्योम pmz_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
			    काष्ठा ktermios *old)
अणु
	काष्ठा uart_pmac_port *uap = to_pmz(port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);	

	/* Disable IRQs on the port */
	pmz_पूर्णांकerrupt_control(uap, 0);

	/* Setup new port configuration */
	__pmz_set_termios(port, termios, old);

	/* Re-enable IRQs on the port */
	अगर (ZS_IS_OPEN(uap))
		pmz_पूर्णांकerrupt_control(uap, 1);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *pmz_type(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pmac_port *uap = to_pmz(port);

	अगर (ZS_IS_IRDA(uap))
		वापस "Z85c30 ESCC - Infrared port";
	अन्यथा अगर (ZS_IS_INTMODEM(uap))
		वापस "Z85c30 ESCC - Internal modem";
	वापस "Z85c30 ESCC - Serial port";
पूर्ण

/* We करो not request/release mappings of the रेजिस्टरs here, this
 * happens at early serial probe समय.
 */
अटल व्योम pmz_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक pmz_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

/* These करो not need to करो anything पूर्णांकeresting either.  */
अटल व्योम pmz_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
पूर्ण

/* We करो not support letting the user mess with the भागisor, IRQ, etc. */
अटल पूर्णांक pmz_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL

अटल पूर्णांक pmz_poll_get_अक्षर(काष्ठा uart_port *port)
अणु
	काष्ठा uart_pmac_port *uap =
		container_of(port, काष्ठा uart_pmac_port, port);
	पूर्णांक tries = 2;

	जबतक (tries) अणु
		अगर ((पढ़ो_zsreg(uap, R0) & Rx_CH_AV) != 0)
			वापस पढ़ो_zsdata(uap);
		अगर (tries--)
			udelay(5);
	पूर्ण

	वापस NO_POLL_CHAR;
पूर्ण

अटल व्योम pmz_poll_put_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर c)
अणु
	काष्ठा uart_pmac_port *uap =
		container_of(port, काष्ठा uart_pmac_port, port);

	/* Wait क्रम the transmit buffer to empty. */
	जबतक ((पढ़ो_zsreg(uap, R0) & Tx_BUF_EMP) == 0)
		udelay(5);
	ग_लिखो_zsdata(uap, c);
पूर्ण

#पूर्ण_अगर /* CONFIG_CONSOLE_POLL */

अटल स्थिर काष्ठा uart_ops pmz_pops = अणु
	.tx_empty	=	pmz_tx_empty,
	.set_mctrl	=	pmz_set_mctrl,
	.get_mctrl	=	pmz_get_mctrl,
	.stop_tx	=	pmz_stop_tx,
	.start_tx	=	pmz_start_tx,
	.stop_rx	=	pmz_stop_rx,
	.enable_ms	=	pmz_enable_ms,
	.अवरोध_ctl	=	pmz_अवरोध_ctl,
	.startup	=	pmz_startup,
	.shutकरोwn	=	pmz_shutकरोwn,
	.set_termios	=	pmz_set_termios,
	.type		=	pmz_type,
	.release_port	=	pmz_release_port,
	.request_port	=	pmz_request_port,
	.config_port	=	pmz_config_port,
	.verअगरy_port	=	pmz_verअगरy_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर	=	pmz_poll_get_अक्षर,
	.poll_put_अक्षर	=	pmz_poll_put_अक्षर,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_PPC_PMAC

/*
 * Setup one port काष्ठाure after probing, HW is करोwn at this poपूर्णांक,
 * Unlike sunzilog, we करोn't need to pre-init the spinlock as we don't
 * रेजिस्टर our console beक्रमe uart_add_one_port() is called
 */
अटल पूर्णांक __init pmz_init_port(काष्ठा uart_pmac_port *uap)
अणु
	काष्ठा device_node *np = uap->node;
	स्थिर अक्षर *conn;
	स्थिर काष्ठा slot_names_prop अणु
		पूर्णांक	count;
		अक्षर	name[1];
	पूर्ण *slots;
	पूर्णांक len;
	काष्ठा resource r_ports, r_rxdma, r_txdma;

	/*
	 * Request & map chip रेजिस्टरs
	 */
	अगर (of_address_to_resource(np, 0, &r_ports))
		वापस -ENODEV;
	uap->port.mapbase = r_ports.start;
	uap->port.membase = ioremap(uap->port.mapbase, 0x1000);

	uap->control_reg = uap->port.membase;
	uap->data_reg = uap->control_reg + 0x10;
	
	/*
	 * Request & map DBDMA रेजिस्टरs
	 */
#अगर_घोषित HAS_DBDMA
	अगर (of_address_to_resource(np, 1, &r_txdma) == 0 &&
	    of_address_to_resource(np, 2, &r_rxdma) == 0)
		uap->flags |= PMACZILOG_FLAG_HAS_DMA;
#अन्यथा
	स_रखो(&r_txdma, 0, माप(काष्ठा resource));
	स_रखो(&r_rxdma, 0, माप(काष्ठा resource));
#पूर्ण_अगर	
	अगर (ZS_HAS_DMA(uap)) अणु
		uap->tx_dma_regs = ioremap(r_txdma.start, 0x100);
		अगर (uap->tx_dma_regs == शून्य) अणु	
			uap->flags &= ~PMACZILOG_FLAG_HAS_DMA;
			जाओ no_dma;
		पूर्ण
		uap->rx_dma_regs = ioremap(r_rxdma.start, 0x100);
		अगर (uap->rx_dma_regs == शून्य) अणु	
			iounmap(uap->tx_dma_regs);
			uap->tx_dma_regs = शून्य;
			uap->flags &= ~PMACZILOG_FLAG_HAS_DMA;
			जाओ no_dma;
		पूर्ण
		uap->tx_dma_irq = irq_of_parse_and_map(np, 1);
		uap->rx_dma_irq = irq_of_parse_and_map(np, 2);
	पूर्ण
no_dma:

	/*
	 * Detect port type
	 */
	अगर (of_device_is_compatible(np, "cobalt"))
		uap->flags |= PMACZILOG_FLAG_IS_INTMODEM;
	conn = of_get_property(np, "AAPL,connector", &len);
	अगर (conn && (म_भेद(conn, "infrared") == 0))
		uap->flags |= PMACZILOG_FLAG_IS_IRDA;
	uap->port_type = PMAC_SCC_ASYNC;
	/* 1999 Powerbook G3 has slot-names property instead */
	slots = of_get_property(np, "slot-names", &len);
	अगर (slots && slots->count > 0) अणु
		अगर (म_भेद(slots->name, "IrDA") == 0)
			uap->flags |= PMACZILOG_FLAG_IS_IRDA;
		अन्यथा अगर (म_भेद(slots->name, "Modem") == 0)
			uap->flags |= PMACZILOG_FLAG_IS_INTMODEM;
	पूर्ण
	अगर (ZS_IS_IRDA(uap))
		uap->port_type = PMAC_SCC_IRDA;
	अगर (ZS_IS_INTMODEM(uap)) अणु
		काष्ठा device_node* i2c_modem =
			of_find_node_by_name(शून्य, "i2c-modem");
		अगर (i2c_modem) अणु
			स्थिर अक्षर* mid =
				of_get_property(i2c_modem, "modem-id", शून्य);
			अगर (mid) चयन(*mid) अणु
			हाल 0x04 :
			हाल 0x05 :
			हाल 0x07 :
			हाल 0x08 :
			हाल 0x0b :
			हाल 0x0c :
				uap->port_type = PMAC_SCC_I2S1;
			पूर्ण
			prपूर्णांकk(KERN_INFO "pmac_zilog: i2c-modem detected, id: %d\n",
				mid ? (*mid) : 0);
			of_node_put(i2c_modem);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_INFO "pmac_zilog: serial modem detected\n");
		पूर्ण
	पूर्ण

	/*
	 * Init reमुख्यing bits of "port" काष्ठाure
	 */
	uap->port.iotype = UPIO_MEM;
	uap->port.irq = irq_of_parse_and_map(np, 0);
	uap->port.uartclk = ZS_CLOCK;
	uap->port.fअगरosize = 1;
	uap->port.ops = &pmz_pops;
	uap->port.type = PORT_PMAC_ZILOG;
	uap->port.flags = 0;

	/*
	 * Fixup क्रम the port on Gatwick क्रम which the device-tree has
	 * missing पूर्णांकerrupts. Normally, the macio_dev would contain
	 * fixed up पूर्णांकerrupt info, but we use the device-tree directly
	 * here due to early probing so we need the fixup too.
	 */
	अगर (uap->port.irq == 0 &&
	    np->parent && np->parent->parent &&
	    of_device_is_compatible(np->parent->parent, "gatwick")) अणु
		/* IRQs on gatwick are offset by 64 */
		uap->port.irq = irq_create_mapping(शून्य, 64 + 15);
		uap->tx_dma_irq = irq_create_mapping(शून्य, 64 + 4);
		uap->rx_dma_irq = irq_create_mapping(शून्य, 64 + 5);
	पूर्ण

	/* Setup some valid baud rate inक्रमmation in the रेजिस्टर
	 * shaकरोws so we करोn't ग_लिखो crap there beक्रमe baud rate is
	 * first initialized.
	 */
	pmz_convert_to_zs(uap, CS8, 0, 9600);

	वापस 0;
पूर्ण

/*
 * Get rid of a port on module removal
 */
अटल व्योम pmz_dispose_port(काष्ठा uart_pmac_port *uap)
अणु
	काष्ठा device_node *np;

	np = uap->node;
	iounmap(uap->rx_dma_regs);
	iounmap(uap->tx_dma_regs);
	iounmap(uap->control_reg);
	uap->node = शून्य;
	of_node_put(np);
	स_रखो(uap, 0, माप(काष्ठा uart_pmac_port));
पूर्ण

/*
 * Called upon match with an escc node in the device-tree.
 */
अटल पूर्णांक pmz_attach(काष्ठा macio_dev *mdev, स्थिर काष्ठा of_device_id *match)
अणु
	काष्ठा uart_pmac_port *uap;
	पूर्णांक i;
	
	/* Iterate the pmz_ports array to find a matching entry
	 */
	क्रम (i = 0; i < MAX_ZS_PORTS; i++)
		अगर (pmz_ports[i].node == mdev->ofdev.dev.of_node)
			अवरोध;
	अगर (i >= MAX_ZS_PORTS)
		वापस -ENODEV;


	uap = &pmz_ports[i];
	uap->dev = mdev;
	uap->port.dev = &mdev->ofdev.dev;
	dev_set_drvdata(&mdev->ofdev.dev, uap);

	/* We still activate the port even when failing to request resources
	 * to work around bugs in ancient Apple device-trees
	 */
	अगर (macio_request_resources(uap->dev, "pmac_zilog"))
		prपूर्णांकk(KERN_WARNING "%pOFn: Failed to request resource"
		       ", port still active\n",
		       uap->node);
	अन्यथा
		uap->flags |= PMACZILOG_FLAG_RSRC_REQUESTED;

	वापस uart_add_one_port(&pmz_uart_reg, &uap->port);
पूर्ण

/*
 * That one should not be called, macio isn't really a hotswap device,
 * we करोn't expect one of those serial ports to go away...
 */
अटल पूर्णांक pmz_detach(काष्ठा macio_dev *mdev)
अणु
	काष्ठा uart_pmac_port	*uap = dev_get_drvdata(&mdev->ofdev.dev);
	
	अगर (!uap)
		वापस -ENODEV;

	uart_हटाओ_one_port(&pmz_uart_reg, &uap->port);

	अगर (uap->flags & PMACZILOG_FLAG_RSRC_REQUESTED) अणु
		macio_release_resources(uap->dev);
		uap->flags &= ~PMACZILOG_FLAG_RSRC_REQUESTED;
	पूर्ण
	dev_set_drvdata(&mdev->ofdev.dev, शून्य);
	uap->dev = शून्य;
	uap->port.dev = शून्य;
	
	वापस 0;
पूर्ण


अटल पूर्णांक pmz_suspend(काष्ठा macio_dev *mdev, pm_message_t pm_state)
अणु
	काष्ठा uart_pmac_port *uap = dev_get_drvdata(&mdev->ofdev.dev);

	अगर (uap == शून्य) अणु
		prपूर्णांकk("HRM... pmz_suspend with NULL uap\n");
		वापस 0;
	पूर्ण

	uart_suspend_port(&pmz_uart_reg, &uap->port);

	वापस 0;
पूर्ण


अटल पूर्णांक pmz_resume(काष्ठा macio_dev *mdev)
अणु
	काष्ठा uart_pmac_port *uap = dev_get_drvdata(&mdev->ofdev.dev);

	अगर (uap == शून्य)
		वापस 0;

	uart_resume_port(&pmz_uart_reg, &uap->port);

	वापस 0;
पूर्ण

/*
 * Probe all ports in the प्रणाली and build the ports array, we रेजिस्टर
 * with the serial layer later, so we get a proper काष्ठा device which
 * allows the tty to attach properly. This is later than it used to be
 * but the tty layer really wants it that way.
 */
अटल पूर्णांक __init pmz_probe(व्योम)
अणु
	काष्ठा device_node	*node_p, *node_a, *node_b, *np;
	पूर्णांक			count = 0;
	पूर्णांक			rc;

	/*
	 * Find all escc chips in the प्रणाली
	 */
	क्रम_each_node_by_name(node_p, "escc") अणु
		/*
		 * First get channel A/B node poपूर्णांकers
		 * 
		 * TODO: Add routines with proper locking to करो that...
		 */
		node_a = node_b = शून्य;
		क्रम_each_child_of_node(node_p, np) अणु
			अगर (of_node_name_prefix(np, "ch-a"))
				node_a = of_node_get(np);
			अन्यथा अगर (of_node_name_prefix(np, "ch-b"))
				node_b = of_node_get(np);
		पूर्ण
		अगर (!node_a && !node_b) अणु
			of_node_put(node_a);
			of_node_put(node_b);
			prपूर्णांकk(KERN_ERR "pmac_zilog: missing node %c for escc %pOF\n",
				(!node_a) ? 'a' : 'b', node_p);
			जारी;
		पूर्ण

		/*
		 * Fill basic fields in the port काष्ठाures
		 */
		अगर (node_b != शून्य) अणु
			pmz_ports[count].mate		= &pmz_ports[count+1];
			pmz_ports[count+1].mate		= &pmz_ports[count];
		पूर्ण
		pmz_ports[count].flags		= PMACZILOG_FLAG_IS_CHANNEL_A;
		pmz_ports[count].node		= node_a;
		pmz_ports[count+1].node		= node_b;
		pmz_ports[count].port.line	= count;
		pmz_ports[count+1].port.line	= count+1;

		/*
		 * Setup the ports क्रम real
		 */
		rc = pmz_init_port(&pmz_ports[count]);
		अगर (rc == 0 && node_b != शून्य)
			rc = pmz_init_port(&pmz_ports[count+1]);
		अगर (rc != 0) अणु
			of_node_put(node_a);
			of_node_put(node_b);
			स_रखो(&pmz_ports[count], 0, माप(काष्ठा uart_pmac_port));
			स_रखो(&pmz_ports[count+1], 0, माप(काष्ठा uart_pmac_port));
			जारी;
		पूर्ण
		count += 2;
	पूर्ण
	pmz_ports_count = count;

	वापस 0;
पूर्ण

#अन्यथा

/* On PCI PowerMacs, pmz_probe() करोes an explicit search of the OpenFirmware
 * tree to obtain the device_nodes needed to start the console beक्रमe the
 * macio driver. On Macs without OpenFirmware, global platक्रमm_devices take
 * the place of those device_nodes.
 */
बाह्य काष्ठा platक्रमm_device scc_a_pdev, scc_b_pdev;

अटल पूर्णांक __init pmz_init_port(काष्ठा uart_pmac_port *uap)
अणु
	काष्ठा resource *r_ports, *r_irq;

	r_ports = platक्रमm_get_resource(uap->pdev, IORESOURCE_MEM, 0);
	r_irq = platक्रमm_get_resource(uap->pdev, IORESOURCE_IRQ, 0);
	अगर (!r_ports || !r_irq)
		वापस -ENODEV;

	uap->port.mapbase  = r_ports->start;
	uap->port.membase  = (अचिन्हित अक्षर __iomem *) r_ports->start;
	uap->port.iotype   = UPIO_MEM;
	uap->port.irq      = r_irq->start;
	uap->port.uartclk  = ZS_CLOCK;
	uap->port.fअगरosize = 1;
	uap->port.ops      = &pmz_pops;
	uap->port.type     = PORT_PMAC_ZILOG;
	uap->port.flags    = 0;

	uap->control_reg   = uap->port.membase;
	uap->data_reg      = uap->control_reg + 4;
	uap->port_type     = 0;
	uap->port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_PMACZILOG_CONSOLE);

	pmz_convert_to_zs(uap, CS8, 0, 9600);

	वापस 0;
पूर्ण

अटल पूर्णांक __init pmz_probe(व्योम)
अणु
	पूर्णांक err;

	pmz_ports_count = 0;

	pmz_ports[0].port.line = 0;
	pmz_ports[0].flags     = PMACZILOG_FLAG_IS_CHANNEL_A;
	pmz_ports[0].pdev      = &scc_a_pdev;
	err = pmz_init_port(&pmz_ports[0]);
	अगर (err)
		वापस err;
	pmz_ports_count++;

	pmz_ports[0].mate      = &pmz_ports[1];
	pmz_ports[1].mate      = &pmz_ports[0];
	pmz_ports[1].port.line = 1;
	pmz_ports[1].flags     = 0;
	pmz_ports[1].pdev      = &scc_b_pdev;
	err = pmz_init_port(&pmz_ports[1]);
	अगर (err)
		वापस err;
	pmz_ports_count++;

	वापस 0;
पूर्ण

अटल व्योम pmz_dispose_port(काष्ठा uart_pmac_port *uap)
अणु
	स_रखो(uap, 0, माप(काष्ठा uart_pmac_port));
पूर्ण

अटल पूर्णांक __init pmz_attach(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_pmac_port *uap;
	पूर्णांक i;

	/* Iterate the pmz_ports array to find a matching entry */
	क्रम (i = 0; i < pmz_ports_count; i++)
		अगर (pmz_ports[i].pdev == pdev)
			अवरोध;
	अगर (i >= pmz_ports_count)
		वापस -ENODEV;

	uap = &pmz_ports[i];
	uap->port.dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, uap);

	वापस uart_add_one_port(&pmz_uart_reg, &uap->port);
पूर्ण

अटल पूर्णांक __निकास pmz_detach(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_pmac_port *uap = platक्रमm_get_drvdata(pdev);

	अगर (!uap)
		वापस -ENODEV;

	uart_हटाओ_one_port(&pmz_uart_reg, &uap->port);

	uap->port.dev = शून्य;

	वापस 0;
पूर्ण

#पूर्ण_अगर /* !CONFIG_PPC_PMAC */

#अगर_घोषित CONFIG_SERIAL_PMACZILOG_CONSOLE

अटल व्योम pmz_console_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित पूर्णांक count);
अटल पूर्णांक __init pmz_console_setup(काष्ठा console *co, अक्षर *options);

अटल काष्ठा console pmz_console = अणु
	.name	=	PMACZILOG_NAME,
	.ग_लिखो	=	pmz_console_ग_लिखो,
	.device	=	uart_console_device,
	.setup	=	pmz_console_setup,
	.flags	=	CON_PRINTBUFFER,
	.index	=	-1,
	.data   =	&pmz_uart_reg,
पूर्ण;

#घोषणा PMACZILOG_CONSOLE	&pmz_console
#अन्यथा /* CONFIG_SERIAL_PMACZILOG_CONSOLE */
#घोषणा PMACZILOG_CONSOLE	(शून्य)
#पूर्ण_अगर /* CONFIG_SERIAL_PMACZILOG_CONSOLE */

/*
 * Register the driver, console driver and ports with the serial
 * core
 */
अटल पूर्णांक __init pmz_रेजिस्टर(व्योम)
अणु
	pmz_uart_reg.nr = pmz_ports_count;
	pmz_uart_reg.cons = PMACZILOG_CONSOLE;

	/*
	 * Register this driver with the serial core
	 */
	वापस uart_रेजिस्टर_driver(&pmz_uart_reg);
पूर्ण

#अगर_घोषित CONFIG_PPC_PMAC

अटल स्थिर काष्ठा of_device_id pmz_match[] =
अणु
	अणु
	.name		= "ch-a",
	पूर्ण,
	अणु
	.name		= "ch-b",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE (of, pmz_match);

अटल काष्ठा macio_driver pmz_driver = अणु
	.driver = अणु
		.name 		= "pmac_zilog",
		.owner		= THIS_MODULE,
		.of_match_table	= pmz_match,
	पूर्ण,
	.probe		= pmz_attach,
	.हटाओ		= pmz_detach,
	.suspend	= pmz_suspend,
	.resume		= pmz_resume,
पूर्ण;

#अन्यथा

अटल काष्ठा platक्रमm_driver pmz_driver = अणु
	.हटाओ		= __निकास_p(pmz_detach),
	.driver		= अणु
		.name		= "scc",
	पूर्ण,
पूर्ण;

#पूर्ण_अगर /* !CONFIG_PPC_PMAC */

अटल पूर्णांक __init init_pmz(व्योम)
अणु
	पूर्णांक rc, i;
	prपूर्णांकk(KERN_INFO "%s\n", version);

	/* 
	 * First, we need to करो a direct OF-based probe pass. We
	 * करो that because we want serial console up beक्रमe the
	 * macio stuffs calls us back, and since that makes it
	 * easier to pass the proper number of channels to
	 * uart_रेजिस्टर_driver()
	 */
	अगर (pmz_ports_count == 0)
		pmz_probe();

	/*
	 * Bail early अगर no port found
	 */
	अगर (pmz_ports_count == 0)
		वापस -ENODEV;

	/*
	 * Now we रेजिस्टर with the serial layer
	 */
	rc = pmz_रेजिस्टर();
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR 
			"pmac_zilog: Error registering serial device, disabling pmac_zilog.\n"
		 	"pmac_zilog: Did another serial driver already claim the minors?\n"); 
		/* effectively "pmz_unprobe()" */
		क्रम (i=0; i < pmz_ports_count; i++)
			pmz_dispose_port(&pmz_ports[i]);
		वापस rc;
	पूर्ण

	/*
	 * Then we रेजिस्टर the macio driver itself
	 */
#अगर_घोषित CONFIG_PPC_PMAC
	वापस macio_रेजिस्टर_driver(&pmz_driver);
#अन्यथा
	वापस platक्रमm_driver_probe(&pmz_driver, pmz_attach);
#पूर्ण_अगर
पूर्ण

अटल व्योम __निकास निकास_pmz(व्योम)
अणु
	पूर्णांक i;

#अगर_घोषित CONFIG_PPC_PMAC
	/* Get rid of macio-driver (detach from macio) */
	macio_unरेजिस्टर_driver(&pmz_driver);
#अन्यथा
	platक्रमm_driver_unरेजिस्टर(&pmz_driver);
#पूर्ण_अगर

	क्रम (i = 0; i < pmz_ports_count; i++) अणु
		काष्ठा uart_pmac_port *uport = &pmz_ports[i];
#अगर_घोषित CONFIG_PPC_PMAC
		अगर (uport->node != शून्य)
			pmz_dispose_port(uport);
#अन्यथा
		अगर (uport->pdev != शून्य)
			pmz_dispose_port(uport);
#पूर्ण_अगर
	पूर्ण
	/* Unरेजिस्टर UART driver */
	uart_unरेजिस्टर_driver(&pmz_uart_reg);
पूर्ण

#अगर_घोषित CONFIG_SERIAL_PMACZILOG_CONSOLE

अटल व्योम pmz_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा uart_pmac_port *uap =
		container_of(port, काष्ठा uart_pmac_port, port);

	/* Wait क्रम the transmit buffer to empty. */
	जबतक ((पढ़ो_zsreg(uap, R0) & Tx_BUF_EMP) == 0)
		udelay(5);
	ग_लिखो_zsdata(uap, ch);
पूर्ण

/*
 * Prपूर्णांक a string to the serial port trying not to disturb
 * any possible real use of the port...
 */
अटल व्योम pmz_console_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_pmac_port *uap = &pmz_ports[con->index];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&uap->port.lock, flags);

	/* Turn of पूर्णांकerrupts and enable the transmitter. */
	ग_लिखो_zsreg(uap, R1, uap->curregs[1] & ~TxINT_ENAB);
	ग_लिखो_zsreg(uap, R5, uap->curregs[5] | TxENABLE | RTS | DTR);

	uart_console_ग_लिखो(&uap->port, s, count, pmz_console_अक्षर_दो);

	/* Restore the values in the रेजिस्टरs. */
	ग_लिखो_zsreg(uap, R1, uap->curregs[1]);
	/* Don't disable the transmitter. */

	spin_unlock_irqrestore(&uap->port.lock, flags);
पूर्ण

/*
 * Setup the serial console
 */
अटल पूर्णांक __init pmz_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_pmac_port *uap;
	काष्ठा uart_port *port;
	पूर्णांक baud = 38400;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	अचिन्हित दीर्घ pwr_delay;

	/*
	 * XServe's शेष to 57600 bps
	 */
	अगर (of_machine_is_compatible("RackMac1,1")
	    || of_machine_is_compatible("RackMac1,2")
	    || of_machine_is_compatible("MacRISC4"))
		baud = 57600;

	/*
	 * Check whether an invalid uart number has been specअगरied, and
	 * अगर so, search क्रम the first available port that करोes have
	 * console support.
	 */
	अगर (co->index >= pmz_ports_count)
		co->index = 0;
	uap = &pmz_ports[co->index];
#अगर_घोषित CONFIG_PPC_PMAC
	अगर (uap->node == शून्य)
		वापस -ENODEV;
#अन्यथा
	अगर (uap->pdev == शून्य)
		वापस -ENODEV;
#पूर्ण_अगर
	port = &uap->port;

	/*
	 * Mark port as beeing a console
	 */
	uap->flags |= PMACZILOG_FLAG_IS_CONS;

	/*
	 * Temporary fix क्रम uart layer who didn't setup the spinlock yet
	 */
	spin_lock_init(&port->lock);

	/*
	 * Enable the hardware
	 */
	pwr_delay = __pmz_startup(uap);
	अगर (pwr_delay)
		mdelay(pwr_delay);
	
	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल पूर्णांक __init pmz_console_init(व्योम)
अणु
	/* Probe ports */
	pmz_probe();

	अगर (pmz_ports_count == 0)
		वापस -ENODEV;

	/* TODO: Autoprobe console based on OF */
	/* pmz_console.index = i; */
	रेजिस्टर_console(&pmz_console);

	वापस 0;

पूर्ण
console_initcall(pmz_console_init);
#पूर्ण_अगर /* CONFIG_SERIAL_PMACZILOG_CONSOLE */

module_init(init_pmz);
module_निकास(निकास_pmz);
