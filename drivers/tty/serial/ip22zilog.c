<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Zilog serial chips found on SGI workstations and
 * servers.  This driver could actually be made more generic.
 *
 * This is based on the drivers/serial/sunzilog.c code as of 2.6.0-test7 and the
 * old drivers/sgi/अक्षर/sgiserial.c code which itself is based of the original
 * drivers/sbus/अक्षर/zs.c code.  A lot of code has been simply moved over
 * directly from there but much has been rewritten.  Credits thereक्रमe go out
 * to David S. Miller, Eddie C. Dost, Pete Zaitcev, Ted Ts'o and Alex Buell
 * क्रम their work there.
 *
 *  Copyright (C) 2002 Ralf Baechle (ralf@linux-mips.org)
 *  Copyright (C) 2002 David S. Miller (davem@redhat.com)
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/major.h>
#समावेश <linux/माला.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/serial.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/console.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/sgialib.h>
#समावेश <यंत्र/sgi/ioc.h>
#समावेश <यंत्र/sgi/hpc3.h>
#समावेश <यंत्र/sgi/ip22.h>

#समावेश <linux/serial_core.h>

#समावेश "ip22zilog.h"

/*
 * On IP22 we need to delay after रेजिस्टर accesses but we करो not need to
 * flush ग_लिखोs.
 */
#घोषणा ZSDELAY()		udelay(5)
#घोषणा ZSDELAY_LONG()		udelay(20)
#घोषणा ZS_WSYNC(channel)	करो अणु पूर्ण जबतक (0)

#घोषणा NUM_IP22ZILOG		1
#घोषणा NUM_CHANNELS		(NUM_IP22ZILOG * 2)

#घोषणा ZS_CLOCK		3672000	/* Zilog input घड़ी rate. */
#घोषणा ZS_CLOCK_DIVISOR	16      /* Divisor this driver uses. */

/*
 * We wrap our port काष्ठाure around the generic uart_port.
 */
काष्ठा uart_ip22zilog_port अणु
	काष्ठा uart_port		port;

	/* IRQ servicing chain.  */
	काष्ठा uart_ip22zilog_port	*next;

	/* Current values of Zilog ग_लिखो रेजिस्टरs.  */
	अचिन्हित अक्षर			curregs[NUM_ZSREGS];

	अचिन्हित पूर्णांक			flags;
#घोषणा IP22ZILOG_FLAG_IS_CONS		0x00000004
#घोषणा IP22ZILOG_FLAG_IS_KGDB		0x00000008
#घोषणा IP22ZILOG_FLAG_MODEM_STATUS	0x00000010
#घोषणा IP22ZILOG_FLAG_IS_CHANNEL_A	0x00000020
#घोषणा IP22ZILOG_FLAG_REGS_HELD	0x00000040
#घोषणा IP22ZILOG_FLAG_TX_STOPPED	0x00000080
#घोषणा IP22ZILOG_FLAG_TX_ACTIVE	0x00000100
#घोषणा IP22ZILOG_FLAG_RESET_DONE	0x00000200

	अचिन्हित पूर्णांक			tty_अवरोध;

	अचिन्हित अक्षर			parity_mask;
	अचिन्हित अक्षर			prev_status;
पूर्ण;

#घोषणा ZILOG_CHANNEL_FROM_PORT(PORT)	((काष्ठा zilog_channel *)((PORT)->membase))
#घोषणा UART_ZILOG(PORT)		((काष्ठा uart_ip22zilog_port *)(PORT))
#घोषणा IP22ZILOG_GET_CURR_REG(PORT, REGNUM)		\
	(UART_ZILOG(PORT)->curregs[REGNUM])
#घोषणा IP22ZILOG_SET_CURR_REG(PORT, REGNUM, REGVAL)	\
	((UART_ZILOG(PORT)->curregs[REGNUM]) = (REGVAL))
#घोषणा ZS_IS_CONS(UP)	((UP)->flags & IP22ZILOG_FLAG_IS_CONS)
#घोषणा ZS_IS_KGDB(UP)	((UP)->flags & IP22ZILOG_FLAG_IS_KGDB)
#घोषणा ZS_WANTS_MODEM_STATUS(UP)	((UP)->flags & IP22ZILOG_FLAG_MODEM_STATUS)
#घोषणा ZS_IS_CHANNEL_A(UP)	((UP)->flags & IP22ZILOG_FLAG_IS_CHANNEL_A)
#घोषणा ZS_REGS_HELD(UP)	((UP)->flags & IP22ZILOG_FLAG_REGS_HELD)
#घोषणा ZS_TX_STOPPED(UP)	((UP)->flags & IP22ZILOG_FLAG_TX_STOPPED)
#घोषणा ZS_TX_ACTIVE(UP)	((UP)->flags & IP22ZILOG_FLAG_TX_ACTIVE)

/* Reading and writing Zilog8530 रेजिस्टरs.  The delays are to make this
 * driver work on the IP22 which needs a settling delay after each chip
 * रेजिस्टर access, other machines handle this in hardware via auxiliary
 * flip-flops which implement the settle समय we करो in software.
 *
 * The port lock must be held and local IRQs must be disabled
 * when अणुपढ़ो,ग_लिखोपूर्ण_zsreg is invoked.
 */
अटल अचिन्हित अक्षर पढ़ो_zsreg(काष्ठा zilog_channel *channel,
				अचिन्हित अक्षर reg)
अणु
	अचिन्हित अक्षर retval;

	ग_लिखोb(reg, &channel->control);
	ZSDELAY();
	retval = पढ़ोb(&channel->control);
	ZSDELAY();

	वापस retval;
पूर्ण

अटल व्योम ग_लिखो_zsreg(काष्ठा zilog_channel *channel,
			अचिन्हित अक्षर reg, अचिन्हित अक्षर value)
अणु
	ग_लिखोb(reg, &channel->control);
	ZSDELAY();
	ग_लिखोb(value, &channel->control);
	ZSDELAY();
पूर्ण

अटल व्योम ip22zilog_clear_fअगरo(काष्ठा zilog_channel *channel)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 32; i++) अणु
		अचिन्हित अक्षर regval;

		regval = पढ़ोb(&channel->control);
		ZSDELAY();
		अगर (regval & Rx_CH_AV)
			अवरोध;

		regval = पढ़ो_zsreg(channel, R1);
		पढ़ोb(&channel->data);
		ZSDELAY();

		अगर (regval & (PAR_ERR | Rx_OVR | CRC_ERR)) अणु
			ग_लिखोb(ERR_RES, &channel->control);
			ZSDELAY();
			ZS_WSYNC(channel);
		पूर्ण
	पूर्ण
पूर्ण

/* This function must only be called when the TX is not busy.  The UART
 * port lock must be held and local पूर्णांकerrupts disabled.
 */
अटल व्योम __load_zsregs(काष्ठा zilog_channel *channel, अचिन्हित अक्षर *regs)
अणु
	पूर्णांक i;

	/* Let pending transmits finish.  */
	क्रम (i = 0; i < 1000; i++) अणु
		अचिन्हित अक्षर stat = पढ़ो_zsreg(channel, R1);
		अगर (stat & ALL_SNT)
			अवरोध;
		udelay(100);
	पूर्ण

	ग_लिखोb(ERR_RES, &channel->control);
	ZSDELAY();
	ZS_WSYNC(channel);

	ip22zilog_clear_fअगरo(channel);

	/* Disable all पूर्णांकerrupts.  */
	ग_लिखो_zsreg(channel, R1,
		    regs[R1] & ~(RxINT_MASK | TxINT_ENAB | EXT_INT_ENAB));

	/* Set parity, sync config, stop bits, and घड़ी भागisor.  */
	ग_लिखो_zsreg(channel, R4, regs[R4]);

	/* Set misc. TX/RX control bits.  */
	ग_लिखो_zsreg(channel, R10, regs[R10]);

	/* Set TX/RX controls sans the enable bits.  */
	ग_लिखो_zsreg(channel, R3, regs[R3] & ~RxENAB);
	ग_लिखो_zsreg(channel, R5, regs[R5] & ~TxENAB);

	/* Synchronous mode config.  */
	ग_लिखो_zsreg(channel, R6, regs[R6]);
	ग_लिखो_zsreg(channel, R7, regs[R7]);

	/* Don't mess with the पूर्णांकerrupt vector (R2, unused by us) and
	 * master पूर्णांकerrupt control (R9).  We make sure this is setup
	 * properly at probe समय then never touch it again.
	 */

	/* Disable baud generator.  */
	ग_लिखो_zsreg(channel, R14, regs[R14] & ~BRENAB);

	/* Clock mode control.  */
	ग_लिखो_zsreg(channel, R11, regs[R11]);

	/* Lower and upper byte of baud rate generator भागisor.  */
	ग_लिखो_zsreg(channel, R12, regs[R12]);
	ग_लिखो_zsreg(channel, R13, regs[R13]);

	/* Now reग_लिखो R14, with BRENAB (अगर set).  */
	ग_लिखो_zsreg(channel, R14, regs[R14]);

	/* External status पूर्णांकerrupt control.  */
	ग_लिखो_zsreg(channel, R15, regs[R15]);

	/* Reset बाह्यal status पूर्णांकerrupts.  */
	ग_लिखो_zsreg(channel, R0, RES_EXT_INT);
	ग_लिखो_zsreg(channel, R0, RES_EXT_INT);

	/* Reग_लिखो R3/R5, this समय without enables masked.  */
	ग_लिखो_zsreg(channel, R3, regs[R3]);
	ग_लिखो_zsreg(channel, R5, regs[R5]);

	/* Reग_लिखो R1, this समय without IRQ enabled masked.  */
	ग_लिखो_zsreg(channel, R1, regs[R1]);
पूर्ण

/* Reprogram the Zilog channel HW रेजिस्टरs with the copies found in the
 * software state काष्ठा.  If the transmitter is busy, we defer this update
 * until the next TX complete पूर्णांकerrupt.  Else, we करो it right now.
 *
 * The UART port lock must be held and local पूर्णांकerrupts disabled.
 */
अटल व्योम ip22zilog_maybe_update_regs(काष्ठा uart_ip22zilog_port *up,
				       काष्ठा zilog_channel *channel)
अणु
	अगर (!ZS_REGS_HELD(up)) अणु
		अगर (ZS_TX_ACTIVE(up)) अणु
			up->flags |= IP22ZILOG_FLAG_REGS_HELD;
		पूर्ण अन्यथा अणु
			__load_zsregs(channel, up->curregs);
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा Rx_BRK 0x0100                   /* BREAK event software flag.  */
#घोषणा Rx_SYS 0x0200                   /* SysRq event software flag.  */

अटल bool ip22zilog_receive_अक्षरs(काष्ठा uart_ip22zilog_port *up,
						  काष्ठा zilog_channel *channel)
अणु
	अचिन्हित अक्षर ch, flag;
	अचिन्हित पूर्णांक r1;
	bool push = up->port.state != शून्य;

	क्रम (;;) अणु
		ch = पढ़ोb(&channel->control);
		ZSDELAY();
		अगर (!(ch & Rx_CH_AV))
			अवरोध;

		r1 = पढ़ो_zsreg(channel, R1);
		अगर (r1 & (PAR_ERR | Rx_OVR | CRC_ERR)) अणु
			ग_लिखोb(ERR_RES, &channel->control);
			ZSDELAY();
			ZS_WSYNC(channel);
		पूर्ण

		ch = पढ़ोb(&channel->data);
		ZSDELAY();

		ch &= up->parity_mask;

		/* Handle the null अक्षर got when BREAK is हटाओd.  */
		अगर (!ch)
			r1 |= up->tty_अवरोध;

		/* A real serial line, record the अक्षरacter and status.  */
		flag = TTY_NORMAL;
		up->port.icount.rx++;
		अगर (r1 & (PAR_ERR | Rx_OVR | CRC_ERR | Rx_SYS | Rx_BRK)) अणु
			up->tty_अवरोध = 0;

			अगर (r1 & (Rx_SYS | Rx_BRK)) अणु
				up->port.icount.brk++;
				अगर (r1 & Rx_SYS)
					जारी;
				r1 &= ~(PAR_ERR | CRC_ERR);
			पूर्ण
			अन्यथा अगर (r1 & PAR_ERR)
				up->port.icount.parity++;
			अन्यथा अगर (r1 & CRC_ERR)
				up->port.icount.frame++;
			अगर (r1 & Rx_OVR)
				up->port.icount.overrun++;
			r1 &= up->port.पढ़ो_status_mask;
			अगर (r1 & Rx_BRK)
				flag = TTY_BREAK;
			अन्यथा अगर (r1 & PAR_ERR)
				flag = TTY_PARITY;
			अन्यथा अगर (r1 & CRC_ERR)
				flag = TTY_FRAME;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(&up->port, ch))
			जारी;

		अगर (push)
			uart_insert_अक्षर(&up->port, r1, Rx_OVR, ch, flag);
	पूर्ण
	वापस push;
पूर्ण

अटल व्योम ip22zilog_status_handle(काष्ठा uart_ip22zilog_port *up,
				   काष्ठा zilog_channel *channel)
अणु
	अचिन्हित अक्षर status;

	status = पढ़ोb(&channel->control);
	ZSDELAY();

	ग_लिखोb(RES_EXT_INT, &channel->control);
	ZSDELAY();
	ZS_WSYNC(channel);

	अगर (up->curregs[R15] & BRKIE) अणु
		अगर ((status & BRK_ABRT) && !(up->prev_status & BRK_ABRT)) अणु
			अगर (uart_handle_अवरोध(&up->port))
				up->tty_अवरोध = Rx_SYS;
			अन्यथा
				up->tty_अवरोध = Rx_BRK;
		पूर्ण
	पूर्ण

	अगर (ZS_WANTS_MODEM_STATUS(up)) अणु
		अगर (status & SYNC)
			up->port.icount.dsr++;

		/* The Zilog just gives us an पूर्णांकerrupt when DCD/CTS/etc. change.
		 * But it करोes not tell us which bit has changed, we have to keep
		 * track of this ourselves.
		 */
		अगर ((status ^ up->prev_status) ^ DCD)
			uart_handle_dcd_change(&up->port,
					       (status & DCD));
		अगर ((status ^ up->prev_status) ^ CTS)
			uart_handle_cts_change(&up->port,
					       (status & CTS));

		wake_up_पूर्णांकerruptible(&up->port.state->port.delta_msr_रुको);
	पूर्ण

	up->prev_status = status;
पूर्ण

अटल व्योम ip22zilog_transmit_अक्षरs(काष्ठा uart_ip22zilog_port *up,
				    काष्ठा zilog_channel *channel)
अणु
	काष्ठा circ_buf *xmit;

	अगर (ZS_IS_CONS(up)) अणु
		अचिन्हित अक्षर status = पढ़ोb(&channel->control);
		ZSDELAY();

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

	up->flags &= ~IP22ZILOG_FLAG_TX_ACTIVE;

	अगर (ZS_REGS_HELD(up)) अणु
		__load_zsregs(channel, up->curregs);
		up->flags &= ~IP22ZILOG_FLAG_REGS_HELD;
	पूर्ण

	अगर (ZS_TX_STOPPED(up)) अणु
		up->flags &= ~IP22ZILOG_FLAG_TX_STOPPED;
		जाओ ack_tx_पूर्णांक;
	पूर्ण

	अगर (up->port.x_अक्षर) अणु
		up->flags |= IP22ZILOG_FLAG_TX_ACTIVE;
		ग_लिखोb(up->port.x_अक्षर, &channel->data);
		ZSDELAY();
		ZS_WSYNC(channel);

		up->port.icount.tx++;
		up->port.x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (up->port.state == शून्य)
		जाओ ack_tx_पूर्णांक;
	xmit = &up->port.state->xmit;
	अगर (uart_circ_empty(xmit))
		जाओ ack_tx_पूर्णांक;
	अगर (uart_tx_stopped(&up->port))
		जाओ ack_tx_पूर्णांक;

	up->flags |= IP22ZILOG_FLAG_TX_ACTIVE;
	ग_लिखोb(xmit->buf[xmit->tail], &channel->data);
	ZSDELAY();
	ZS_WSYNC(channel);

	xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
	up->port.icount.tx++;

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&up->port);

	वापस;

ack_tx_पूर्णांक:
	ग_लिखोb(RES_Tx_P, &channel->control);
	ZSDELAY();
	ZS_WSYNC(channel);
पूर्ण

अटल irqवापस_t ip22zilog_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_ip22zilog_port *up = dev_id;

	जबतक (up) अणु
		काष्ठा zilog_channel *channel
			= ZILOG_CHANNEL_FROM_PORT(&up->port);
		अचिन्हित अक्षर r3;
		bool push = false;

		spin_lock(&up->port.lock);
		r3 = पढ़ो_zsreg(channel, R3);

		/* Channel A */
		अगर (r3 & (CHAEXT | CHATxIP | CHARxIP)) अणु
			ग_लिखोb(RES_H_IUS, &channel->control);
			ZSDELAY();
			ZS_WSYNC(channel);

			अगर (r3 & CHARxIP)
				push = ip22zilog_receive_अक्षरs(up, channel);
			अगर (r3 & CHAEXT)
				ip22zilog_status_handle(up, channel);
			अगर (r3 & CHATxIP)
				ip22zilog_transmit_अक्षरs(up, channel);
		पूर्ण
		spin_unlock(&up->port.lock);

		अगर (push)
			tty_flip_buffer_push(&up->port.state->port);

		/* Channel B */
		up = up->next;
		channel = ZILOG_CHANNEL_FROM_PORT(&up->port);
		push = false;

		spin_lock(&up->port.lock);
		अगर (r3 & (CHBEXT | CHBTxIP | CHBRxIP)) अणु
			ग_लिखोb(RES_H_IUS, &channel->control);
			ZSDELAY();
			ZS_WSYNC(channel);

			अगर (r3 & CHBRxIP)
				push = ip22zilog_receive_अक्षरs(up, channel);
			अगर (r3 & CHBEXT)
				ip22zilog_status_handle(up, channel);
			अगर (r3 & CHBTxIP)
				ip22zilog_transmit_अक्षरs(up, channel);
		पूर्ण
		spin_unlock(&up->port.lock);

		अगर (push)
			tty_flip_buffer_push(&up->port.state->port);

		up = up->next;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* A convenient way to quickly get R0 status.  The caller must _not_ hold the
 * port lock, it is acquired here.
 */
अटल __अंतरभूत__ अचिन्हित अक्षर ip22zilog_पढ़ो_channel_status(काष्ठा uart_port *port)
अणु
	काष्ठा zilog_channel *channel;
	अचिन्हित अक्षर status;

	channel = ZILOG_CHANNEL_FROM_PORT(port);
	status = पढ़ोb(&channel->control);
	ZSDELAY();

	वापस status;
पूर्ण

/* The port lock is not held.  */
अटल अचिन्हित पूर्णांक ip22zilog_tx_empty(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर status;
	अचिन्हित पूर्णांक ret;

	spin_lock_irqsave(&port->lock, flags);

	status = ip22zilog_पढ़ो_channel_status(port);

	spin_unlock_irqrestore(&port->lock, flags);

	अगर (status & Tx_BUF_EMP)
		ret = TIOCSER_TEMT;
	अन्यथा
		ret = 0;

	वापस ret;
पूर्ण

/* The port lock is held and पूर्णांकerrupts are disabled.  */
अटल अचिन्हित पूर्णांक ip22zilog_get_mctrl(काष्ठा uart_port *port)
अणु
	अचिन्हित अक्षर status;
	अचिन्हित पूर्णांक ret;

	status = ip22zilog_पढ़ो_channel_status(port);

	ret = 0;
	अगर (status & DCD)
		ret |= TIOCM_CAR;
	अगर (status & SYNC)
		ret |= TIOCM_DSR;
	अगर (status & CTS)
		ret |= TIOCM_CTS;

	वापस ret;
पूर्ण

/* The port lock is held and पूर्णांकerrupts are disabled.  */
अटल व्योम ip22zilog_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा uart_ip22zilog_port *up =
		container_of(port, काष्ठा uart_ip22zilog_port, port);
	काष्ठा zilog_channel *channel = ZILOG_CHANNEL_FROM_PORT(port);
	अचिन्हित अक्षर set_bits, clear_bits;

	set_bits = clear_bits = 0;

	अगर (mctrl & TIOCM_RTS)
		set_bits |= RTS;
	अन्यथा
		clear_bits |= RTS;
	अगर (mctrl & TIOCM_DTR)
		set_bits |= DTR;
	अन्यथा
		clear_bits |= DTR;

	/* NOTE: Not subject to 'transmitter active' rule.  */
	up->curregs[R5] |= set_bits;
	up->curregs[R5] &= ~clear_bits;
	ग_लिखो_zsreg(channel, R5, up->curregs[R5]);
पूर्ण

/* The port lock is held and पूर्णांकerrupts are disabled.  */
अटल व्योम ip22zilog_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_ip22zilog_port *up =
		container_of(port, काष्ठा uart_ip22zilog_port, port);

	up->flags |= IP22ZILOG_FLAG_TX_STOPPED;
पूर्ण

/* The port lock is held and पूर्णांकerrupts are disabled.  */
अटल व्योम ip22zilog_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_ip22zilog_port *up =
		container_of(port, काष्ठा uart_ip22zilog_port, port);
	काष्ठा zilog_channel *channel = ZILOG_CHANNEL_FROM_PORT(port);
	अचिन्हित अक्षर status;

	up->flags |= IP22ZILOG_FLAG_TX_ACTIVE;
	up->flags &= ~IP22ZILOG_FLAG_TX_STOPPED;

	status = पढ़ोb(&channel->control);
	ZSDELAY();

	/* TX busy?  Just रुको क्रम the TX करोne पूर्णांकerrupt.  */
	अगर (!(status & Tx_BUF_EMP))
		वापस;

	/* Send the first अक्षरacter to jump-start the TX करोne
	 * IRQ sending engine.
	 */
	अगर (port->x_अक्षर) अणु
		ग_लिखोb(port->x_अक्षर, &channel->data);
		ZSDELAY();
		ZS_WSYNC(channel);

		port->icount.tx++;
		port->x_अक्षर = 0;
	पूर्ण अन्यथा अणु
		काष्ठा circ_buf *xmit = &port->state->xmit;

		अगर (uart_circ_empty(xmit))
			वापस;
		ग_लिखोb(xmit->buf[xmit->tail], &channel->data);
		ZSDELAY();
		ZS_WSYNC(channel);

		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;

		अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
			uart_ग_लिखो_wakeup(&up->port);
	पूर्ण
पूर्ण

/* The port lock is held and पूर्णांकerrupts are disabled.  */
अटल व्योम ip22zilog_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_ip22zilog_port *up = UART_ZILOG(port);
	काष्ठा zilog_channel *channel;

	अगर (ZS_IS_CONS(up))
		वापस;

	channel = ZILOG_CHANNEL_FROM_PORT(port);

	/* Disable all RX पूर्णांकerrupts.  */
	up->curregs[R1] &= ~RxINT_MASK;
	ip22zilog_maybe_update_regs(up, channel);
पूर्ण

/* The port lock is held.  */
अटल व्योम ip22zilog_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा uart_ip22zilog_port *up =
		container_of(port, काष्ठा uart_ip22zilog_port, port);
	काष्ठा zilog_channel *channel = ZILOG_CHANNEL_FROM_PORT(port);
	अचिन्हित अक्षर new_reg;

	new_reg = up->curregs[R15] | (DCDIE | SYNCIE | CTSIE);
	अगर (new_reg != up->curregs[R15]) अणु
		up->curregs[R15] = new_reg;

		/* NOTE: Not subject to 'transmitter active' rule.  */
		ग_लिखो_zsreg(channel, R15, up->curregs[R15]);
	पूर्ण
पूर्ण

/* The port lock is not held.  */
अटल व्योम ip22zilog_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा uart_ip22zilog_port *up =
		container_of(port, काष्ठा uart_ip22zilog_port, port);
	काष्ठा zilog_channel *channel = ZILOG_CHANNEL_FROM_PORT(port);
	अचिन्हित अक्षर set_bits, clear_bits, new_reg;
	अचिन्हित दीर्घ flags;

	set_bits = clear_bits = 0;

	अगर (अवरोध_state)
		set_bits |= SND_BRK;
	अन्यथा
		clear_bits |= SND_BRK;

	spin_lock_irqsave(&port->lock, flags);

	new_reg = (up->curregs[R5] | set_bits) & ~clear_bits;
	अगर (new_reg != up->curregs[R5]) अणु
		up->curregs[R5] = new_reg;

		/* NOTE: Not subject to 'transmitter active' rule.  */
		ग_लिखो_zsreg(channel, R5, up->curregs[R5]);
	पूर्ण

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम __ip22zilog_reset(काष्ठा uart_ip22zilog_port *up)
अणु
	काष्ठा zilog_channel *channel;
	पूर्णांक i;

	अगर (up->flags & IP22ZILOG_FLAG_RESET_DONE)
		वापस;

	/* Let pending transmits finish.  */
	channel = ZILOG_CHANNEL_FROM_PORT(&up->port);
	क्रम (i = 0; i < 1000; i++) अणु
		अचिन्हित अक्षर stat = पढ़ो_zsreg(channel, R1);
		अगर (stat & ALL_SNT)
			अवरोध;
		udelay(100);
	पूर्ण

	अगर (!ZS_IS_CHANNEL_A(up)) अणु
		up++;
		channel = ZILOG_CHANNEL_FROM_PORT(&up->port);
	पूर्ण
	ग_लिखो_zsreg(channel, R9, FHWRES);
	ZSDELAY_LONG();
	(व्योम) पढ़ो_zsreg(channel, R0);

	up->flags |= IP22ZILOG_FLAG_RESET_DONE;
	up->next->flags |= IP22ZILOG_FLAG_RESET_DONE;
पूर्ण

अटल व्योम __ip22zilog_startup(काष्ठा uart_ip22zilog_port *up)
अणु
	काष्ठा zilog_channel *channel;

	channel = ZILOG_CHANNEL_FROM_PORT(&up->port);

	__ip22zilog_reset(up);

	__load_zsregs(channel, up->curregs);
	/* set master पूर्णांकerrupt enable */
	ग_लिखो_zsreg(channel, R9, up->curregs[R9]);
	up->prev_status = पढ़ोb(&channel->control);

	/* Enable receiver and transmitter.  */
	up->curregs[R3] |= RxENAB;
	up->curregs[R5] |= TxENAB;

	up->curregs[R1] |= EXT_INT_ENAB | INT_ALL_Rx | TxINT_ENAB;
	ip22zilog_maybe_update_regs(up, channel);
पूर्ण

अटल पूर्णांक ip22zilog_startup(काष्ठा uart_port *port)
अणु
	काष्ठा uart_ip22zilog_port *up = UART_ZILOG(port);
	अचिन्हित दीर्घ flags;

	अगर (ZS_IS_CONS(up))
		वापस 0;

	spin_lock_irqsave(&port->lock, flags);
	__ip22zilog_startup(up);
	spin_unlock_irqrestore(&port->lock, flags);
	वापस 0;
पूर्ण

/*
 * The test क्रम ZS_IS_CONS is explained by the following e-mail:
 *****
 * From: Russell King <rmk@arm.linux.org.uk>
 * Date: Sun, 8 Dec 2002 10:18:38 +0000
 *
 * On Sun, Dec 08, 2002 at 02:43:36AM -0500, Pete Zaitcev wrote:
 * > I boot my 2.5 boxes using "console=ttyS0,9600" argument,
 * > and I noticed that something is not right with reference
 * > counting in this हाल. It seems that when the console
 * > is खोलो by kernel initially, this is not accounted
 * > as an खोलो, and uart_startup is not called.
 *
 * That is correct.  We are unable to call uart_startup when the serial
 * console is initialised because it may need to allocate memory (as
 * request_irq करोes) and the memory allocators may not have been
 * initialised.
 *
 * 1. initialise the port पूर्णांकo a state where it can send अक्षरacters in the
 *    console ग_लिखो method.
 *
 * 2. करोn't करो the actual hardware shutकरोwn in your shutकरोwn() method (but
 *    करो the normal software shutकरोwn - ie, मुक्त irqs etc)
 *****
 */
अटल व्योम ip22zilog_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा uart_ip22zilog_port *up = UART_ZILOG(port);
	काष्ठा zilog_channel *channel;
	अचिन्हित दीर्घ flags;

	अगर (ZS_IS_CONS(up))
		वापस;

	spin_lock_irqsave(&port->lock, flags);

	channel = ZILOG_CHANNEL_FROM_PORT(port);

	/* Disable receiver and transmitter.  */
	up->curregs[R3] &= ~RxENAB;
	up->curregs[R5] &= ~TxENAB;

	/* Disable all पूर्णांकerrupts and BRK निश्चितion.  */
	up->curregs[R1] &= ~(EXT_INT_ENAB | TxINT_ENAB | RxINT_MASK);
	up->curregs[R5] &= ~SND_BRK;
	ip22zilog_maybe_update_regs(up, channel);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/* Shared by TTY driver and serial console setup.  The port lock is held
 * and local पूर्णांकerrupts are disabled.
 */
अटल व्योम
ip22zilog_convert_to_zs(काष्ठा uart_ip22zilog_port *up, अचिन्हित पूर्णांक cflag,
		       अचिन्हित पूर्णांक अगरlag, पूर्णांक brg)
अणु

	up->curregs[R10] = NRZ;
	up->curregs[R11] = TCBR | RCBR;

	/* Program BAUD and घड़ी source. */
	up->curregs[R4] &= ~XCLK_MASK;
	up->curregs[R4] |= X16CLK;
	up->curregs[R12] = brg & 0xff;
	up->curregs[R13] = (brg >> 8) & 0xff;
	up->curregs[R14] = BRENAB;

	/* Character size, stop bits, and parity. */
	up->curregs[3] &= ~RxN_MASK;
	up->curregs[5] &= ~TxN_MASK;
	चयन (cflag & CSIZE) अणु
	हाल CS5:
		up->curregs[3] |= Rx5;
		up->curregs[5] |= Tx5;
		up->parity_mask = 0x1f;
		अवरोध;
	हाल CS6:
		up->curregs[3] |= Rx6;
		up->curregs[5] |= Tx6;
		up->parity_mask = 0x3f;
		अवरोध;
	हाल CS7:
		up->curregs[3] |= Rx7;
		up->curregs[5] |= Tx7;
		up->parity_mask = 0x7f;
		अवरोध;
	हाल CS8:
	शेष:
		up->curregs[3] |= Rx8;
		up->curregs[5] |= Tx8;
		up->parity_mask = 0xff;
		अवरोध;
	पूर्ण
	up->curregs[4] &= ~0x0c;
	अगर (cflag & CSTOPB)
		up->curregs[4] |= SB2;
	अन्यथा
		up->curregs[4] |= SB1;
	अगर (cflag & PARENB)
		up->curregs[4] |= PAR_ENAB;
	अन्यथा
		up->curregs[4] &= ~PAR_ENAB;
	अगर (!(cflag & PARODD))
		up->curregs[4] |= PAR_EVEN;
	अन्यथा
		up->curregs[4] &= ~PAR_EVEN;

	up->port.पढ़ो_status_mask = Rx_OVR;
	अगर (अगरlag & INPCK)
		up->port.पढ़ो_status_mask |= CRC_ERR | PAR_ERR;
	अगर (अगरlag & (IGNBRK | BRKINT | PARMRK))
		up->port.पढ़ो_status_mask |= BRK_ABRT;

	up->port.ignore_status_mask = 0;
	अगर (अगरlag & IGNPAR)
		up->port.ignore_status_mask |= CRC_ERR | PAR_ERR;
	अगर (अगरlag & IGNBRK) अणु
		up->port.ignore_status_mask |= BRK_ABRT;
		अगर (अगरlag & IGNPAR)
			up->port.ignore_status_mask |= Rx_OVR;
	पूर्ण

	अगर ((cflag & CREAD) == 0)
		up->port.ignore_status_mask = 0xff;
पूर्ण

/* The port lock is not held.  */
अटल व्योम
ip22zilog_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		      काष्ठा ktermios *old)
अणु
	काष्ठा uart_ip22zilog_port *up =
		container_of(port, काष्ठा uart_ip22zilog_port, port);
	अचिन्हित दीर्घ flags;
	पूर्णांक baud, brg;

	baud = uart_get_baud_rate(port, termios, old, 1200, 76800);

	spin_lock_irqsave(&up->port.lock, flags);

	brg = BPS_TO_BRG(baud, ZS_CLOCK / ZS_CLOCK_DIVISOR);

	ip22zilog_convert_to_zs(up, termios->c_cflag, termios->c_अगरlag, brg);

	अगर (UART_ENABLE_MS(&up->port, termios->c_cflag))
		up->flags |= IP22ZILOG_FLAG_MODEM_STATUS;
	अन्यथा
		up->flags &= ~IP22ZILOG_FLAG_MODEM_STATUS;

	ip22zilog_maybe_update_regs(up, ZILOG_CHANNEL_FROM_PORT(port));
	uart_update_समयout(port, termios->c_cflag, baud);

	spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

अटल स्थिर अक्षर *ip22zilog_type(काष्ठा uart_port *port)
अणु
	वापस "IP22-Zilog";
पूर्ण

/* We करो not request/release mappings of the रेजिस्टरs here, this
 * happens at early serial probe समय.
 */
अटल व्योम ip22zilog_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक ip22zilog_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

/* These करो not need to करो anything पूर्णांकeresting either.  */
अटल व्योम ip22zilog_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
पूर्ण

/* We करो not support letting the user mess with the भागisor, IRQ, etc. */
अटल पूर्णांक ip22zilog_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा uart_ops ip22zilog_pops = अणु
	.tx_empty	=	ip22zilog_tx_empty,
	.set_mctrl	=	ip22zilog_set_mctrl,
	.get_mctrl	=	ip22zilog_get_mctrl,
	.stop_tx	=	ip22zilog_stop_tx,
	.start_tx	=	ip22zilog_start_tx,
	.stop_rx	=	ip22zilog_stop_rx,
	.enable_ms	=	ip22zilog_enable_ms,
	.अवरोध_ctl	=	ip22zilog_अवरोध_ctl,
	.startup	=	ip22zilog_startup,
	.shutकरोwn	=	ip22zilog_shutकरोwn,
	.set_termios	=	ip22zilog_set_termios,
	.type		=	ip22zilog_type,
	.release_port	=	ip22zilog_release_port,
	.request_port	=	ip22zilog_request_port,
	.config_port	=	ip22zilog_config_port,
	.verअगरy_port	=	ip22zilog_verअगरy_port,
पूर्ण;

अटल काष्ठा uart_ip22zilog_port *ip22zilog_port_table;
अटल काष्ठा zilog_layout **ip22zilog_chip_regs;

अटल काष्ठा uart_ip22zilog_port *ip22zilog_irq_chain;
अटल पूर्णांक zilog_irq = -1;

अटल व्योम * __init alloc_one_table(अचिन्हित दीर्घ size)
अणु
	वापस kzalloc(size, GFP_KERNEL);
पूर्ण

अटल व्योम __init ip22zilog_alloc_tables(व्योम)
अणु
	ip22zilog_port_table = (काष्ठा uart_ip22zilog_port *)
		alloc_one_table(NUM_CHANNELS * माप(काष्ठा uart_ip22zilog_port));
	ip22zilog_chip_regs = (काष्ठा zilog_layout **)
		alloc_one_table(NUM_IP22ZILOG * माप(काष्ठा zilog_layout *));

	अगर (ip22zilog_port_table == शून्य || ip22zilog_chip_regs == शून्य) अणु
		panic("IP22-Zilog: Cannot allocate IP22-Zilog tables.");
	पूर्ण
पूर्ण

/* Get the address of the रेजिस्टरs क्रम IP22-Zilog instance CHIP.  */
अटल काष्ठा zilog_layout * __init get_zs(पूर्णांक chip)
अणु
	अचिन्हित दीर्घ base;

	अगर (chip < 0 || chip >= NUM_IP22ZILOG) अणु
		panic("IP22-Zilog: Illegal chip number %d in get_zs.", chip);
	पूर्ण

	/* Not probe-able, hard code it. */
	base = (अचिन्हित दीर्घ) &sgioc->uart;

	zilog_irq = SGI_SERIAL_IRQ;
	request_mem_region(base, 8, "IP22-Zilog");

	वापस (काष्ठा zilog_layout *) base;
पूर्ण

#घोषणा ZS_PUT_अक्षर_उच्च_DELAY	2000	/* 10 ms */

#अगर_घोषित CONFIG_SERIAL_IP22_ZILOG_CONSOLE
अटल व्योम ip22zilog_put_अक्षर(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा zilog_channel *channel = ZILOG_CHANNEL_FROM_PORT(port);
	पूर्णांक loops = ZS_PUT_अक्षर_उच्च_DELAY;

	/* This is a समयd polling loop so करो not चयन the explicit
	 * udelay with ZSDELAY as that is a NOP on some platक्रमms.  -DaveM
	 */
	करो अणु
		अचिन्हित अक्षर val = पढ़ोb(&channel->control);
		अगर (val & Tx_BUF_EMP) अणु
			ZSDELAY();
			अवरोध;
		पूर्ण
		udelay(5);
	पूर्ण जबतक (--loops);

	ग_लिखोb(ch, &channel->data);
	ZSDELAY();
	ZS_WSYNC(channel);
पूर्ण

अटल व्योम
ip22zilog_console_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_ip22zilog_port *up = &ip22zilog_port_table[con->index];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&up->port.lock, flags);
	uart_console_ग_लिखो(&up->port, s, count, ip22zilog_put_अक्षर);
	udelay(2);
	spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

अटल पूर्णांक __init ip22zilog_console_setup(काष्ठा console *con, अक्षर *options)
अणु
	काष्ठा uart_ip22zilog_port *up = &ip22zilog_port_table[con->index];
	अचिन्हित दीर्घ flags;
	पूर्णांक baud = 9600, bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	up->flags |= IP22ZILOG_FLAG_IS_CONS;

	prपूर्णांकk(KERN_INFO "Console: ttyS%d (IP22-Zilog)\n", con->index);

	spin_lock_irqsave(&up->port.lock, flags);

	up->curregs[R15] |= BRKIE;

	__ip22zilog_startup(up);

	spin_unlock_irqrestore(&up->port.lock, flags);

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	वापस uart_set_options(&up->port, con, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver ip22zilog_reg;

अटल काष्ठा console ip22zilog_console = अणु
	.name	=	"ttyS",
	.ग_लिखो	=	ip22zilog_console_ग_लिखो,
	.device	=	uart_console_device,
	.setup	=	ip22zilog_console_setup,
	.flags	=	CON_PRINTBUFFER,
	.index	=	-1,
	.data	=	&ip22zilog_reg,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SERIAL_IP22_ZILOG_CONSOLE */

अटल काष्ठा uart_driver ip22zilog_reg = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "serial",
	.dev_name	= "ttyS",
	.major		= TTY_MAJOR,
	.minor		= 64,
	.nr		= NUM_CHANNELS,
#अगर_घोषित CONFIG_SERIAL_IP22_ZILOG_CONSOLE
	.cons		= &ip22zilog_console,
#पूर्ण_अगर
पूर्ण;

अटल व्योम __init ip22zilog_prepare(व्योम)
अणु
	अचिन्हित अक्षर sysrq_on = IS_ENABLED(CONFIG_SERIAL_IP22_ZILOG_CONSOLE);
	काष्ठा uart_ip22zilog_port *up;
	काष्ठा zilog_layout *rp;
	पूर्णांक channel, chip;

	/*
	 * Temporary fix.
	 */
	क्रम (channel = 0; channel < NUM_CHANNELS; channel++)
		spin_lock_init(&ip22zilog_port_table[channel].port.lock);

	ip22zilog_irq_chain = &ip22zilog_port_table[NUM_CHANNELS - 1];
        up = &ip22zilog_port_table[0];
	क्रम (channel = NUM_CHANNELS - 1 ; channel > 0; channel--)
		up[channel].next = &up[channel - 1];
	up[channel].next = शून्य;

	क्रम (chip = 0; chip < NUM_IP22ZILOG; chip++) अणु
		अगर (!ip22zilog_chip_regs[chip]) अणु
			ip22zilog_chip_regs[chip] = rp = get_zs(chip);

			up[(chip * 2) + 0].port.membase = (अक्षर *) &rp->channelB;
			up[(chip * 2) + 1].port.membase = (अक्षर *) &rp->channelA;

			/* In theory mapbase is the physical address ...  */
			up[(chip * 2) + 0].port.mapbase =
				(अचिन्हित दीर्घ) ioremap((अचिन्हित दीर्घ) &rp->channelB, 8);
			up[(chip * 2) + 1].port.mapbase =
				(अचिन्हित दीर्घ) ioremap((अचिन्हित दीर्घ) &rp->channelA, 8);
		पूर्ण

		/* Channel A */
		up[(chip * 2) + 0].port.iotype = UPIO_MEM;
		up[(chip * 2) + 0].port.irq = zilog_irq;
		up[(chip * 2) + 0].port.uartclk = ZS_CLOCK;
		up[(chip * 2) + 0].port.fअगरosize = 1;
		up[(chip * 2) + 0].port.has_sysrq = sysrq_on;
		up[(chip * 2) + 0].port.ops = &ip22zilog_pops;
		up[(chip * 2) + 0].port.type = PORT_IP22ZILOG;
		up[(chip * 2) + 0].port.flags = 0;
		up[(chip * 2) + 0].port.line = (chip * 2) + 0;
		up[(chip * 2) + 0].flags = 0;

		/* Channel B */
		up[(chip * 2) + 1].port.iotype = UPIO_MEM;
		up[(chip * 2) + 1].port.irq = zilog_irq;
		up[(chip * 2) + 1].port.uartclk = ZS_CLOCK;
		up[(chip * 2) + 1].port.fअगरosize = 1;
		up[(chip * 2) + 1].port.has_sysrq = sysrq_on;
		up[(chip * 2) + 1].port.ops = &ip22zilog_pops;
		up[(chip * 2) + 1].port.type = PORT_IP22ZILOG;
		up[(chip * 2) + 1].port.line = (chip * 2) + 1;
		up[(chip * 2) + 1].flags |= IP22ZILOG_FLAG_IS_CHANNEL_A;
	पूर्ण

	क्रम (channel = 0; channel < NUM_CHANNELS; channel++) अणु
		काष्ठा uart_ip22zilog_port *up = &ip22zilog_port_table[channel];
		पूर्णांक brg;

		/* Normal serial TTY. */
		up->parity_mask = 0xff;
		up->curregs[R1] = EXT_INT_ENAB | INT_ALL_Rx | TxINT_ENAB;
		up->curregs[R4] = PAR_EVEN | X16CLK | SB1;
		up->curregs[R3] = RxENAB | Rx8;
		up->curregs[R5] = TxENAB | Tx8;
		up->curregs[R9] = NV | MIE;
		up->curregs[R10] = NRZ;
		up->curregs[R11] = TCBR | RCBR;
		brg = BPS_TO_BRG(9600, ZS_CLOCK / ZS_CLOCK_DIVISOR);
		up->curregs[R12] = (brg & 0xff);
		up->curregs[R13] = (brg >> 8) & 0xff;
		up->curregs[R14] = BRENAB;
	पूर्ण
पूर्ण

अटल पूर्णांक __init ip22zilog_ports_init(व्योम)
अणु
	पूर्णांक ret;

	prपूर्णांकk(KERN_INFO "Serial: IP22 Zilog driver (%d chips).\n", NUM_IP22ZILOG);

	ip22zilog_prepare();

	अगर (request_irq(zilog_irq, ip22zilog_पूर्णांकerrupt, 0,
			"IP22-Zilog", ip22zilog_irq_chain)) अणु
		panic("IP22-Zilog: Unable to register zs interrupt handler.\n");
	पूर्ण

	ret = uart_रेजिस्टर_driver(&ip22zilog_reg);
	अगर (ret == 0) अणु
		पूर्णांक i;

		क्रम (i = 0; i < NUM_CHANNELS; i++) अणु
			काष्ठा uart_ip22zilog_port *up = &ip22zilog_port_table[i];

			uart_add_one_port(&ip22zilog_reg, &up->port);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __init ip22zilog_init(व्योम)
अणु
	/* IP22 Zilog setup is hard coded, no probing to करो.  */
	ip22zilog_alloc_tables();
	ip22zilog_ports_init();

	वापस 0;
पूर्ण

अटल व्योम __निकास ip22zilog_निकास(व्योम)
अणु
	पूर्णांक i;
	काष्ठा uart_ip22zilog_port *up;

	क्रम (i = 0; i < NUM_CHANNELS; i++) अणु
		up = &ip22zilog_port_table[i];

		uart_हटाओ_one_port(&ip22zilog_reg, &up->port);
	पूर्ण

	/* Free IO mem */
	up = &ip22zilog_port_table[0];
	क्रम (i = 0; i < NUM_IP22ZILOG; i++) अणु
		अगर (up[(i * 2) + 0].port.mapbase) अणु
		   iounmap((व्योम*)up[(i * 2) + 0].port.mapbase);
		   up[(i * 2) + 0].port.mapbase = 0;
		पूर्ण
		अगर (up[(i * 2) + 1].port.mapbase) अणु
			iounmap((व्योम*)up[(i * 2) + 1].port.mapbase);
			up[(i * 2) + 1].port.mapbase = 0;
		पूर्ण
	पूर्ण

	uart_unरेजिस्टर_driver(&ip22zilog_reg);
पूर्ण

module_init(ip22zilog_init);
module_निकास(ip22zilog_निकास);

/* David wrote it but I'm to blame क्रम the bugs ...  */
MODULE_AUTHOR("Ralf Baechle <ralf@linux-mips.org>");
MODULE_DESCRIPTION("SGI Zilog serial port driver");
MODULE_LICENSE("GPL");
