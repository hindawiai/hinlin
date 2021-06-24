<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* sunzilog.c: Zilog serial driver क्रम Sparc प्रणालीs.
 *
 * Driver क्रम Zilog serial chips found on Sun workstations and
 * servers.  This driver could actually be made more generic.
 *
 * This is based on the old drivers/sbus/अक्षर/zs.c code.  A lot
 * of code has been simply moved over directly from there but
 * much has been rewritten.  Credits thereक्रमe go out to Eddie
 * C. Dost, Pete Zaitcev, Ted Ts'o and Alex Buell क्रम their
 * work there.
 *
 * Copyright (C) 2002, 2006, 2007 David S. Miller (davem@davemloft.net)
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
#अगर_घोषित CONFIG_SERIO
#समावेश <linux/serपन.स>
#पूर्ण_अगर
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/setup.h>

#समावेश <linux/serial_core.h>
#समावेश <linux/sunserialcore.h>

#समावेश "sunzilog.h"

/* On 32-bit sparcs we need to delay after रेजिस्टर accesses
 * to accommodate sun4 प्रणालीs, but we करो not need to flush ग_लिखोs.
 * On 64-bit sparc we only need to flush single ग_लिखोs to ensure
 * completion.
 */
#अगर_अघोषित CONFIG_SPARC64
#घोषणा ZSDELAY()		udelay(5)
#घोषणा ZSDELAY_LONG()		udelay(20)
#घोषणा ZS_WSYNC(channel)	करो अणु पूर्ण जबतक (0)
#अन्यथा
#घोषणा ZSDELAY()
#घोषणा ZSDELAY_LONG()
#घोषणा ZS_WSYNC(__channel) \
	पढ़ोb(&((__channel)->control))
#पूर्ण_अगर

#घोषणा ZS_CLOCK		4915200 /* Zilog input घड़ी rate. */
#घोषणा ZS_CLOCK_DIVISOR	16      /* Divisor this driver uses. */

/*
 * We wrap our port काष्ठाure around the generic uart_port.
 */
काष्ठा uart_sunzilog_port अणु
	काष्ठा uart_port		port;

	/* IRQ servicing chain.  */
	काष्ठा uart_sunzilog_port	*next;

	/* Current values of Zilog ग_लिखो रेजिस्टरs.  */
	अचिन्हित अक्षर			curregs[NUM_ZSREGS];

	अचिन्हित पूर्णांक			flags;
#घोषणा SUNZILOG_FLAG_CONS_KEYB		0x00000001
#घोषणा SUNZILOG_FLAG_CONS_MOUSE	0x00000002
#घोषणा SUNZILOG_FLAG_IS_CONS		0x00000004
#घोषणा SUNZILOG_FLAG_IS_KGDB		0x00000008
#घोषणा SUNZILOG_FLAG_MODEM_STATUS	0x00000010
#घोषणा SUNZILOG_FLAG_IS_CHANNEL_A	0x00000020
#घोषणा SUNZILOG_FLAG_REGS_HELD		0x00000040
#घोषणा SUNZILOG_FLAG_TX_STOPPED	0x00000080
#घोषणा SUNZILOG_FLAG_TX_ACTIVE		0x00000100
#घोषणा SUNZILOG_FLAG_ESCC		0x00000200
#घोषणा SUNZILOG_FLAG_ISR_HANDLER	0x00000400

	अचिन्हित पूर्णांक cflag;

	अचिन्हित अक्षर			parity_mask;
	अचिन्हित अक्षर			prev_status;

#अगर_घोषित CONFIG_SERIO
	काष्ठा serio			serio;
	पूर्णांक				serio_खोलो;
#पूर्ण_अगर
पूर्ण;

अटल व्योम sunzilog_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch);

#घोषणा ZILOG_CHANNEL_FROM_PORT(PORT)	((काष्ठा zilog_channel __iomem *)((PORT)->membase))
#घोषणा UART_ZILOG(PORT)		((काष्ठा uart_sunzilog_port *)(PORT))

#घोषणा ZS_IS_KEYB(UP)	((UP)->flags & SUNZILOG_FLAG_CONS_KEYB)
#घोषणा ZS_IS_MOUSE(UP)	((UP)->flags & SUNZILOG_FLAG_CONS_MOUSE)
#घोषणा ZS_IS_CONS(UP)	((UP)->flags & SUNZILOG_FLAG_IS_CONS)
#घोषणा ZS_IS_KGDB(UP)	((UP)->flags & SUNZILOG_FLAG_IS_KGDB)
#घोषणा ZS_WANTS_MODEM_STATUS(UP)	((UP)->flags & SUNZILOG_FLAG_MODEM_STATUS)
#घोषणा ZS_IS_CHANNEL_A(UP)	((UP)->flags & SUNZILOG_FLAG_IS_CHANNEL_A)
#घोषणा ZS_REGS_HELD(UP)	((UP)->flags & SUNZILOG_FLAG_REGS_HELD)
#घोषणा ZS_TX_STOPPED(UP)	((UP)->flags & SUNZILOG_FLAG_TX_STOPPED)
#घोषणा ZS_TX_ACTIVE(UP)	((UP)->flags & SUNZILOG_FLAG_TX_ACTIVE)

/* Reading and writing Zilog8530 रेजिस्टरs.  The delays are to make this
 * driver work on the Sun4 which needs a settling delay after each chip
 * रेजिस्टर access, other machines handle this in hardware via auxiliary
 * flip-flops which implement the settle समय we करो in software.
 *
 * The port lock must be held and local IRQs must be disabled
 * when अणुपढ़ो,ग_लिखोपूर्ण_zsreg is invoked.
 */
अटल अचिन्हित अक्षर पढ़ो_zsreg(काष्ठा zilog_channel __iomem *channel,
				अचिन्हित अक्षर reg)
अणु
	अचिन्हित अक्षर retval;

	ग_लिखोb(reg, &channel->control);
	ZSDELAY();
	retval = पढ़ोb(&channel->control);
	ZSDELAY();

	वापस retval;
पूर्ण

अटल व्योम ग_लिखो_zsreg(काष्ठा zilog_channel __iomem *channel,
			अचिन्हित अक्षर reg, अचिन्हित अक्षर value)
अणु
	ग_लिखोb(reg, &channel->control);
	ZSDELAY();
	ग_लिखोb(value, &channel->control);
	ZSDELAY();
पूर्ण

अटल व्योम sunzilog_clear_fअगरo(काष्ठा zilog_channel __iomem *channel)
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
अटल पूर्णांक __load_zsregs(काष्ठा zilog_channel __iomem *channel, अचिन्हित अक्षर *regs)
अणु
	पूर्णांक i;
	पूर्णांक escc;
	अचिन्हित अक्षर r15;

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

	sunzilog_clear_fअगरo(channel);

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
	ग_लिखो_zsreg(channel, R15, (regs[R15] | WR7pEN) & ~FIFOEN);

	/* ESCC Extension Register */
	r15 = पढ़ो_zsreg(channel, R15);
	अगर (r15 & 0x01)	अणु
		ग_लिखो_zsreg(channel, R7,  regs[R7p]);

		/* External status पूर्णांकerrupt and FIFO control.  */
		ग_लिखो_zsreg(channel, R15, regs[R15] & ~WR7pEN);
		escc = 1;
	पूर्ण अन्यथा अणु
		 /* Clear FIFO bit हाल it is an issue */
		regs[R15] &= ~FIFOEN;
		escc = 0;
	पूर्ण

	/* Reset बाह्यal status पूर्णांकerrupts.  */
	ग_लिखो_zsreg(channel, R0, RES_EXT_INT); /* First Latch  */
	ग_लिखो_zsreg(channel, R0, RES_EXT_INT); /* Second Latch */

	/* Reग_लिखो R3/R5, this समय without enables masked.  */
	ग_लिखो_zsreg(channel, R3, regs[R3]);
	ग_लिखो_zsreg(channel, R5, regs[R5]);

	/* Reग_लिखो R1, this समय without IRQ enabled masked.  */
	ग_लिखो_zsreg(channel, R1, regs[R1]);

	वापस escc;
पूर्ण

/* Reprogram the Zilog channel HW रेजिस्टरs with the copies found in the
 * software state काष्ठा.  If the transmitter is busy, we defer this update
 * until the next TX complete पूर्णांकerrupt.  Else, we करो it right now.
 *
 * The UART port lock must be held and local पूर्णांकerrupts disabled.
 */
अटल व्योम sunzilog_maybe_update_regs(काष्ठा uart_sunzilog_port *up,
				       काष्ठा zilog_channel __iomem *channel)
अणु
	अगर (!ZS_REGS_HELD(up)) अणु
		अगर (ZS_TX_ACTIVE(up)) अणु
			up->flags |= SUNZILOG_FLAG_REGS_HELD;
		पूर्ण अन्यथा अणु
			__load_zsregs(channel, up->curregs);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sunzilog_change_mouse_baud(काष्ठा uart_sunzilog_port *up)
अणु
	अचिन्हित पूर्णांक cur_cflag = up->cflag;
	पूर्णांक brg, new_baud;

	up->cflag &= ~CBAUD;
	up->cflag |= suncore_mouse_baud_cflag_next(cur_cflag, &new_baud);

	brg = BPS_TO_BRG(new_baud, ZS_CLOCK / ZS_CLOCK_DIVISOR);
	up->curregs[R12] = (brg & 0xff);
	up->curregs[R13] = (brg >> 8) & 0xff;
	sunzilog_maybe_update_regs(up, ZILOG_CHANNEL_FROM_PORT(&up->port));
पूर्ण

अटल व्योम sunzilog_kbdms_receive_अक्षरs(काष्ठा uart_sunzilog_port *up,
					 अचिन्हित अक्षर ch, पूर्णांक is_अवरोध)
अणु
	अगर (ZS_IS_KEYB(up)) अणु
		/* Stop-A is handled by drivers/अक्षर/keyboard.c now. */
#अगर_घोषित CONFIG_SERIO
		अगर (up->serio_खोलो)
			serio_पूर्णांकerrupt(&up->serio, ch, 0);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (ZS_IS_MOUSE(up)) अणु
		पूर्णांक ret = suncore_mouse_baud_detection(ch, is_अवरोध);

		चयन (ret) अणु
		हाल 2:
			sunzilog_change_mouse_baud(up);
			fallthrough;
		हाल 1:
			अवरोध;

		हाल 0:
#अगर_घोषित CONFIG_SERIO
			अगर (up->serio_खोलो)
				serio_पूर्णांकerrupt(&up->serio, ch, 0);
#पूर्ण_अगर
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा tty_port *
sunzilog_receive_अक्षरs(काष्ठा uart_sunzilog_port *up,
		       काष्ठा zilog_channel __iomem *channel)
अणु
	काष्ठा tty_port *port = शून्य;
	अचिन्हित अक्षर ch, r1, flag;

	अगर (up->port.state != शून्य)		/* Unखोलोed serial console */
		port = &up->port.state->port;

	क्रम (;;) अणु

		r1 = पढ़ो_zsreg(channel, R1);
		अगर (r1 & (PAR_ERR | Rx_OVR | CRC_ERR)) अणु
			ग_लिखोb(ERR_RES, &channel->control);
			ZSDELAY();
			ZS_WSYNC(channel);
		पूर्ण

		ch = पढ़ोb(&channel->control);
		ZSDELAY();

		/* This funny hack depends upon BRK_ABRT not पूर्णांकerfering
		 * with the other bits we care about in R1.
		 */
		अगर (ch & BRK_ABRT)
			r1 |= BRK_ABRT;

		अगर (!(ch & Rx_CH_AV))
			अवरोध;

		ch = पढ़ोb(&channel->data);
		ZSDELAY();

		ch &= up->parity_mask;

		अगर (unlikely(ZS_IS_KEYB(up)) || unlikely(ZS_IS_MOUSE(up))) अणु
			sunzilog_kbdms_receive_अक्षरs(up, ch, 0);
			जारी;
		पूर्ण

		/* A real serial line, record the अक्षरacter and status.  */
		flag = TTY_NORMAL;
		up->port.icount.rx++;
		अगर (r1 & (BRK_ABRT | PAR_ERR | Rx_OVR | CRC_ERR)) अणु
			अगर (r1 & BRK_ABRT) अणु
				r1 &= ~(PAR_ERR | CRC_ERR);
				up->port.icount.brk++;
				अगर (uart_handle_अवरोध(&up->port))
					जारी;
			पूर्ण
			अन्यथा अगर (r1 & PAR_ERR)
				up->port.icount.parity++;
			अन्यथा अगर (r1 & CRC_ERR)
				up->port.icount.frame++;
			अगर (r1 & Rx_OVR)
				up->port.icount.overrun++;
			r1 &= up->port.पढ़ो_status_mask;
			अगर (r1 & BRK_ABRT)
				flag = TTY_BREAK;
			अन्यथा अगर (r1 & PAR_ERR)
				flag = TTY_PARITY;
			अन्यथा अगर (r1 & CRC_ERR)
				flag = TTY_FRAME;
		पूर्ण
		अगर (uart_handle_sysrq_अक्षर(&up->port, ch) || !port)
			जारी;

		अगर (up->port.ignore_status_mask == 0xff ||
		    (r1 & up->port.ignore_status_mask) == 0) अणु
		    	tty_insert_flip_अक्षर(port, ch, flag);
		पूर्ण
		अगर (r1 & Rx_OVR)
			tty_insert_flip_अक्षर(port, 0, TTY_OVERRUN);
	पूर्ण

	वापस port;
पूर्ण

अटल व्योम sunzilog_status_handle(काष्ठा uart_sunzilog_port *up,
				   काष्ठा zilog_channel __iomem *channel)
अणु
	अचिन्हित अक्षर status;

	status = पढ़ोb(&channel->control);
	ZSDELAY();

	ग_लिखोb(RES_EXT_INT, &channel->control);
	ZSDELAY();
	ZS_WSYNC(channel);

	अगर (status & BRK_ABRT) अणु
		अगर (ZS_IS_MOUSE(up))
			sunzilog_kbdms_receive_अक्षरs(up, 0, 1);
		अगर (ZS_IS_CONS(up)) अणु
			/* Wait क्रम BREAK to deनिश्चित to aव्योम potentially
			 * confusing the PROM.
			 */
			जबतक (1) अणु
				status = पढ़ोb(&channel->control);
				ZSDELAY();
				अगर (!(status & BRK_ABRT))
					अवरोध;
			पूर्ण
			sun_करो_अवरोध();
			वापस;
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

अटल व्योम sunzilog_transmit_अक्षरs(काष्ठा uart_sunzilog_port *up,
				    काष्ठा zilog_channel __iomem *channel)
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

	up->flags &= ~SUNZILOG_FLAG_TX_ACTIVE;

	अगर (ZS_REGS_HELD(up)) अणु
		__load_zsregs(channel, up->curregs);
		up->flags &= ~SUNZILOG_FLAG_REGS_HELD;
	पूर्ण

	अगर (ZS_TX_STOPPED(up)) अणु
		up->flags &= ~SUNZILOG_FLAG_TX_STOPPED;
		जाओ ack_tx_पूर्णांक;
	पूर्ण

	अगर (up->port.x_अक्षर) अणु
		up->flags |= SUNZILOG_FLAG_TX_ACTIVE;
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

	up->flags |= SUNZILOG_FLAG_TX_ACTIVE;
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

अटल irqवापस_t sunzilog_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_sunzilog_port *up = dev_id;

	जबतक (up) अणु
		काष्ठा zilog_channel __iomem *channel
			= ZILOG_CHANNEL_FROM_PORT(&up->port);
		काष्ठा tty_port *port;
		अचिन्हित अक्षर r3;

		spin_lock(&up->port.lock);
		r3 = पढ़ो_zsreg(channel, R3);

		/* Channel A */
		port = शून्य;
		अगर (r3 & (CHAEXT | CHATxIP | CHARxIP)) अणु
			ग_लिखोb(RES_H_IUS, &channel->control);
			ZSDELAY();
			ZS_WSYNC(channel);

			अगर (r3 & CHARxIP)
				port = sunzilog_receive_अक्षरs(up, channel);
			अगर (r3 & CHAEXT)
				sunzilog_status_handle(up, channel);
			अगर (r3 & CHATxIP)
				sunzilog_transmit_अक्षरs(up, channel);
		पूर्ण
		spin_unlock(&up->port.lock);

		अगर (port)
			tty_flip_buffer_push(port);

		/* Channel B */
		up = up->next;
		channel = ZILOG_CHANNEL_FROM_PORT(&up->port);

		spin_lock(&up->port.lock);
		port = शून्य;
		अगर (r3 & (CHBEXT | CHBTxIP | CHBRxIP)) अणु
			ग_लिखोb(RES_H_IUS, &channel->control);
			ZSDELAY();
			ZS_WSYNC(channel);

			अगर (r3 & CHBRxIP)
				port = sunzilog_receive_अक्षरs(up, channel);
			अगर (r3 & CHBEXT)
				sunzilog_status_handle(up, channel);
			अगर (r3 & CHBTxIP)
				sunzilog_transmit_अक्षरs(up, channel);
		पूर्ण
		spin_unlock(&up->port.lock);

		अगर (port)
			tty_flip_buffer_push(port);

		up = up->next;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* A convenient way to quickly get R0 status.  The caller must _not_ hold the
 * port lock, it is acquired here.
 */
अटल __अंतरभूत__ अचिन्हित अक्षर sunzilog_पढ़ो_channel_status(काष्ठा uart_port *port)
अणु
	काष्ठा zilog_channel __iomem *channel;
	अचिन्हित अक्षर status;

	channel = ZILOG_CHANNEL_FROM_PORT(port);
	status = पढ़ोb(&channel->control);
	ZSDELAY();

	वापस status;
पूर्ण

/* The port lock is not held.  */
अटल अचिन्हित पूर्णांक sunzilog_tx_empty(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर status;
	अचिन्हित पूर्णांक ret;

	spin_lock_irqsave(&port->lock, flags);

	status = sunzilog_पढ़ो_channel_status(port);

	spin_unlock_irqrestore(&port->lock, flags);

	अगर (status & Tx_BUF_EMP)
		ret = TIOCSER_TEMT;
	अन्यथा
		ret = 0;

	वापस ret;
पूर्ण

/* The port lock is held and पूर्णांकerrupts are disabled.  */
अटल अचिन्हित पूर्णांक sunzilog_get_mctrl(काष्ठा uart_port *port)
अणु
	अचिन्हित अक्षर status;
	अचिन्हित पूर्णांक ret;

	status = sunzilog_पढ़ो_channel_status(port);

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
अटल व्योम sunzilog_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा uart_sunzilog_port *up =
		container_of(port, काष्ठा uart_sunzilog_port, port);
	काष्ठा zilog_channel __iomem *channel = ZILOG_CHANNEL_FROM_PORT(port);
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
अटल व्योम sunzilog_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunzilog_port *up =
		container_of(port, काष्ठा uart_sunzilog_port, port);

	up->flags |= SUNZILOG_FLAG_TX_STOPPED;
पूर्ण

/* The port lock is held and पूर्णांकerrupts are disabled.  */
अटल व्योम sunzilog_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunzilog_port *up =
		container_of(port, काष्ठा uart_sunzilog_port, port);
	काष्ठा zilog_channel __iomem *channel = ZILOG_CHANNEL_FROM_PORT(port);
	अचिन्हित अक्षर status;

	up->flags |= SUNZILOG_FLAG_TX_ACTIVE;
	up->flags &= ~SUNZILOG_FLAG_TX_STOPPED;

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

/* The port lock is held.  */
अटल व्योम sunzilog_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunzilog_port *up = UART_ZILOG(port);
	काष्ठा zilog_channel __iomem *channel;

	अगर (ZS_IS_CONS(up))
		वापस;

	channel = ZILOG_CHANNEL_FROM_PORT(port);

	/* Disable all RX पूर्णांकerrupts.  */
	up->curregs[R1] &= ~RxINT_MASK;
	sunzilog_maybe_update_regs(up, channel);
पूर्ण

/* The port lock is held.  */
अटल व्योम sunzilog_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunzilog_port *up =
		container_of(port, काष्ठा uart_sunzilog_port, port);
	काष्ठा zilog_channel __iomem *channel = ZILOG_CHANNEL_FROM_PORT(port);
	अचिन्हित अक्षर new_reg;

	new_reg = up->curregs[R15] | (DCDIE | SYNCIE | CTSIE);
	अगर (new_reg != up->curregs[R15]) अणु
		up->curregs[R15] = new_reg;

		/* NOTE: Not subject to 'transmitter active' rule.  */ 
		ग_लिखो_zsreg(channel, R15, up->curregs[R15] & ~WR7pEN);
	पूर्ण
पूर्ण

/* The port lock is not held.  */
अटल व्योम sunzilog_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा uart_sunzilog_port *up =
		container_of(port, काष्ठा uart_sunzilog_port, port);
	काष्ठा zilog_channel __iomem *channel = ZILOG_CHANNEL_FROM_PORT(port);
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

अटल व्योम __sunzilog_startup(काष्ठा uart_sunzilog_port *up)
अणु
	काष्ठा zilog_channel __iomem *channel;

	channel = ZILOG_CHANNEL_FROM_PORT(&up->port);
	up->prev_status = पढ़ोb(&channel->control);

	/* Enable receiver and transmitter.  */
	up->curregs[R3] |= RxENAB;
	up->curregs[R5] |= TxENAB;

	up->curregs[R1] |= EXT_INT_ENAB | INT_ALL_Rx | TxINT_ENAB;
	sunzilog_maybe_update_regs(up, channel);
पूर्ण

अटल पूर्णांक sunzilog_startup(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunzilog_port *up = UART_ZILOG(port);
	अचिन्हित दीर्घ flags;

	अगर (ZS_IS_CONS(up))
		वापस 0;

	spin_lock_irqsave(&port->lock, flags);
	__sunzilog_startup(up);
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
अटल व्योम sunzilog_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunzilog_port *up = UART_ZILOG(port);
	काष्ठा zilog_channel __iomem *channel;
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
	sunzilog_maybe_update_regs(up, channel);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/* Shared by TTY driver and serial console setup.  The port lock is held
 * and local पूर्णांकerrupts are disabled.
 */
अटल व्योम
sunzilog_convert_to_zs(काष्ठा uart_sunzilog_port *up, अचिन्हित पूर्णांक cflag,
		       अचिन्हित पूर्णांक अगरlag, पूर्णांक brg)
अणु

	up->curregs[R10] = NRZ;
	up->curregs[R11] = TCBR | RCBR;

	/* Program BAUD and घड़ी source. */
	up->curregs[R4] &= ~XCLK_MASK;
	up->curregs[R4] |= X16CLK;
	up->curregs[R12] = brg & 0xff;
	up->curregs[R13] = (brg >> 8) & 0xff;
	up->curregs[R14] = BRSRC | BRENAB;

	/* Character size, stop bits, and parity. */
	up->curregs[R3] &= ~RxN_MASK;
	up->curregs[R5] &= ~TxN_MASK;
	चयन (cflag & CSIZE) अणु
	हाल CS5:
		up->curregs[R3] |= Rx5;
		up->curregs[R5] |= Tx5;
		up->parity_mask = 0x1f;
		अवरोध;
	हाल CS6:
		up->curregs[R3] |= Rx6;
		up->curregs[R5] |= Tx6;
		up->parity_mask = 0x3f;
		अवरोध;
	हाल CS7:
		up->curregs[R3] |= Rx7;
		up->curregs[R5] |= Tx7;
		up->parity_mask = 0x7f;
		अवरोध;
	हाल CS8:
	शेष:
		up->curregs[R3] |= Rx8;
		up->curregs[R5] |= Tx8;
		up->parity_mask = 0xff;
		अवरोध;
	पूर्ण
	up->curregs[R4] &= ~0x0c;
	अगर (cflag & CSTOPB)
		up->curregs[R4] |= SB2;
	अन्यथा
		up->curregs[R4] |= SB1;
	अगर (cflag & PARENB)
		up->curregs[R4] |= PAR_ENAB;
	अन्यथा
		up->curregs[R4] &= ~PAR_ENAB;
	अगर (!(cflag & PARODD))
		up->curregs[R4] |= PAR_EVEN;
	अन्यथा
		up->curregs[R4] &= ~PAR_EVEN;

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
sunzilog_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		     काष्ठा ktermios *old)
अणु
	काष्ठा uart_sunzilog_port *up =
		container_of(port, काष्ठा uart_sunzilog_port, port);
	अचिन्हित दीर्घ flags;
	पूर्णांक baud, brg;

	baud = uart_get_baud_rate(port, termios, old, 1200, 76800);

	spin_lock_irqsave(&up->port.lock, flags);

	brg = BPS_TO_BRG(baud, ZS_CLOCK / ZS_CLOCK_DIVISOR);

	sunzilog_convert_to_zs(up, termios->c_cflag, termios->c_अगरlag, brg);

	अगर (UART_ENABLE_MS(&up->port, termios->c_cflag))
		up->flags |= SUNZILOG_FLAG_MODEM_STATUS;
	अन्यथा
		up->flags &= ~SUNZILOG_FLAG_MODEM_STATUS;

	up->cflag = termios->c_cflag;

	sunzilog_maybe_update_regs(up, ZILOG_CHANNEL_FROM_PORT(port));

	uart_update_समयout(port, termios->c_cflag, baud);

	spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

अटल स्थिर अक्षर *sunzilog_type(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunzilog_port *up = UART_ZILOG(port);

	वापस (up->flags & SUNZILOG_FLAG_ESCC) ? "zs (ESCC)" : "zs";
पूर्ण

/* We करो not request/release mappings of the रेजिस्टरs here, this
 * happens at early serial probe समय.
 */
अटल व्योम sunzilog_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक sunzilog_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

/* These करो not need to करो anything पूर्णांकeresting either.  */
अटल व्योम sunzilog_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
पूर्ण

/* We करो not support letting the user mess with the भागisor, IRQ, etc. */
अटल पूर्णांक sunzilog_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
अटल पूर्णांक sunzilog_get_poll_अक्षर(काष्ठा uart_port *port)
अणु
	अचिन्हित अक्षर ch, r1;
	काष्ठा uart_sunzilog_port *up =
		container_of(port, काष्ठा uart_sunzilog_port, port);
	काष्ठा zilog_channel __iomem *channel
		= ZILOG_CHANNEL_FROM_PORT(&up->port);


	r1 = पढ़ो_zsreg(channel, R1);
	अगर (r1 & (PAR_ERR | Rx_OVR | CRC_ERR)) अणु
		ग_लिखोb(ERR_RES, &channel->control);
		ZSDELAY();
		ZS_WSYNC(channel);
	पूर्ण

	ch = पढ़ोb(&channel->control);
	ZSDELAY();

	/* This funny hack depends upon BRK_ABRT not पूर्णांकerfering
	 * with the other bits we care about in R1.
	 */
	अगर (ch & BRK_ABRT)
		r1 |= BRK_ABRT;

	अगर (!(ch & Rx_CH_AV))
		वापस NO_POLL_CHAR;

	ch = पढ़ोb(&channel->data);
	ZSDELAY();

	ch &= up->parity_mask;
	वापस ch;
पूर्ण

अटल व्योम sunzilog_put_poll_अक्षर(काष्ठा uart_port *port,
			अचिन्हित अक्षर ch)
अणु
	काष्ठा uart_sunzilog_port *up =
		container_of(port, काष्ठा uart_sunzilog_port, port);

	sunzilog_अक्षर_दो(&up->port, ch);
पूर्ण
#पूर्ण_अगर /* CONFIG_CONSOLE_POLL */

अटल स्थिर काष्ठा uart_ops sunzilog_pops = अणु
	.tx_empty	=	sunzilog_tx_empty,
	.set_mctrl	=	sunzilog_set_mctrl,
	.get_mctrl	=	sunzilog_get_mctrl,
	.stop_tx	=	sunzilog_stop_tx,
	.start_tx	=	sunzilog_start_tx,
	.stop_rx	=	sunzilog_stop_rx,
	.enable_ms	=	sunzilog_enable_ms,
	.अवरोध_ctl	=	sunzilog_अवरोध_ctl,
	.startup	=	sunzilog_startup,
	.shutकरोwn	=	sunzilog_shutकरोwn,
	.set_termios	=	sunzilog_set_termios,
	.type		=	sunzilog_type,
	.release_port	=	sunzilog_release_port,
	.request_port	=	sunzilog_request_port,
	.config_port	=	sunzilog_config_port,
	.verअगरy_port	=	sunzilog_verअगरy_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर	=	sunzilog_get_poll_अक्षर,
	.poll_put_अक्षर	=	sunzilog_put_poll_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक uart_chip_count;
अटल काष्ठा uart_sunzilog_port *sunzilog_port_table;
अटल काष्ठा zilog_layout __iomem **sunzilog_chip_regs;

अटल काष्ठा uart_sunzilog_port *sunzilog_irq_chain;

अटल काष्ठा uart_driver sunzilog_reg = अणु
	.owner		=	THIS_MODULE,
	.driver_name	=	"sunzilog",
	.dev_name	=	"ttyS",
	.major		=	TTY_MAJOR,
पूर्ण;

अटल पूर्णांक __init sunzilog_alloc_tables(पूर्णांक num_sunzilog)
अणु
	काष्ठा uart_sunzilog_port *up;
	अचिन्हित दीर्घ size;
	पूर्णांक num_channels = num_sunzilog * 2;
	पूर्णांक i;

	size = num_channels * माप(काष्ठा uart_sunzilog_port);
	sunzilog_port_table = kzalloc(size, GFP_KERNEL);
	अगर (!sunzilog_port_table)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_channels; i++) अणु
		up = &sunzilog_port_table[i];

		spin_lock_init(&up->port.lock);

		अगर (i == 0)
			sunzilog_irq_chain = up;

		अगर (i < num_channels - 1)
			up->next = up + 1;
		अन्यथा
			up->next = शून्य;
	पूर्ण

	size = num_sunzilog * माप(काष्ठा zilog_layout __iomem *);
	sunzilog_chip_regs = kzalloc(size, GFP_KERNEL);
	अगर (!sunzilog_chip_regs) अणु
		kमुक्त(sunzilog_port_table);
		sunzilog_irq_chain = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sunzilog_मुक्त_tables(व्योम)
अणु
	kमुक्त(sunzilog_port_table);
	sunzilog_irq_chain = शून्य;
	kमुक्त(sunzilog_chip_regs);
पूर्ण

#घोषणा ZS_PUT_अक्षर_उच्च_DELAY	2000	/* 10 ms */

अटल व्योम sunzilog_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा zilog_channel __iomem *channel = ZILOG_CHANNEL_FROM_PORT(port);
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

#अगर_घोषित CONFIG_SERIO

अटल DEFINE_SPINLOCK(sunzilog_serio_lock);

अटल पूर्णांक sunzilog_serio_ग_लिखो(काष्ठा serio *serio, अचिन्हित अक्षर ch)
अणु
	काष्ठा uart_sunzilog_port *up = serio->port_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sunzilog_serio_lock, flags);

	sunzilog_अक्षर_दो(&up->port, ch);

	spin_unlock_irqrestore(&sunzilog_serio_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sunzilog_serio_खोलो(काष्ठा serio *serio)
अणु
	काष्ठा uart_sunzilog_port *up = serio->port_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&sunzilog_serio_lock, flags);
	अगर (!up->serio_खोलो) अणु
		up->serio_खोलो = 1;
		ret = 0;
	पूर्ण अन्यथा
		ret = -EBUSY;
	spin_unlock_irqrestore(&sunzilog_serio_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम sunzilog_serio_बंद(काष्ठा serio *serio)
अणु
	काष्ठा uart_sunzilog_port *up = serio->port_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sunzilog_serio_lock, flags);
	up->serio_खोलो = 0;
	spin_unlock_irqrestore(&sunzilog_serio_lock, flags);
पूर्ण

#पूर्ण_अगर /* CONFIG_SERIO */

#अगर_घोषित CONFIG_SERIAL_SUNZILOG_CONSOLE
अटल व्योम
sunzilog_console_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_sunzilog_port *up = &sunzilog_port_table[con->index];
	अचिन्हित दीर्घ flags;
	पूर्णांक locked = 1;

	अगर (up->port.sysrq || oops_in_progress)
		locked = spin_trylock_irqsave(&up->port.lock, flags);
	अन्यथा
		spin_lock_irqsave(&up->port.lock, flags);

	uart_console_ग_लिखो(&up->port, s, count, sunzilog_अक्षर_दो);
	udelay(2);

	अगर (locked)
		spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

अटल पूर्णांक __init sunzilog_console_setup(काष्ठा console *con, अक्षर *options)
अणु
	काष्ठा uart_sunzilog_port *up = &sunzilog_port_table[con->index];
	अचिन्हित दीर्घ flags;
	पूर्णांक baud, brg;

	अगर (up->port.type != PORT_SUNZILOG)
		वापस -EINVAL;

	prपूर्णांकk(KERN_INFO "Console: ttyS%d (SunZilog zs%d)\n",
	       (sunzilog_reg.minor - 64) + con->index, con->index);

	/* Get firmware console settings.  */
	sunserial_console_termios(con, up->port.dev->of_node);

	/* Firmware console speed is limited to 150-->38400 baud so
	 * this hackish cflag thing is OK.
	 */
	चयन (con->cflag & CBAUD) अणु
	हाल B150: baud = 150; अवरोध;
	हाल B300: baud = 300; अवरोध;
	हाल B600: baud = 600; अवरोध;
	हाल B1200: baud = 1200; अवरोध;
	हाल B2400: baud = 2400; अवरोध;
	हाल B4800: baud = 4800; अवरोध;
	शेष: हाल B9600: baud = 9600; अवरोध;
	हाल B19200: baud = 19200; अवरोध;
	हाल B38400: baud = 38400; अवरोध;
	पूर्ण

	brg = BPS_TO_BRG(baud, ZS_CLOCK / ZS_CLOCK_DIVISOR);

	spin_lock_irqsave(&up->port.lock, flags);

	up->curregs[R15] |= BRKIE;
	sunzilog_convert_to_zs(up, con->cflag, 0, brg);

	sunzilog_set_mctrl(&up->port, TIOCM_DTR | TIOCM_RTS);
	__sunzilog_startup(up);

	spin_unlock_irqrestore(&up->port.lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा console sunzilog_console_ops = अणु
	.name	=	"ttyS",
	.ग_लिखो	=	sunzilog_console_ग_लिखो,
	.device	=	uart_console_device,
	.setup	=	sunzilog_console_setup,
	.flags	=	CON_PRINTBUFFER,
	.index	=	-1,
	.data   =	&sunzilog_reg,
पूर्ण;

अटल अंतरभूत काष्ठा console *SUNZILOG_CONSOLE(व्योम)
अणु
	वापस &sunzilog_console_ops;
पूर्ण

#अन्यथा
#घोषणा SUNZILOG_CONSOLE()	(शून्य)
#पूर्ण_अगर

अटल व्योम sunzilog_init_kbdms(काष्ठा uart_sunzilog_port *up)
अणु
	पूर्णांक baud, brg;

	अगर (up->flags & SUNZILOG_FLAG_CONS_KEYB) अणु
		up->cflag = B1200 | CS8 | CLOCAL | CREAD;
		baud = 1200;
	पूर्ण अन्यथा अणु
		up->cflag = B4800 | CS8 | CLOCAL | CREAD;
		baud = 4800;
	पूर्ण

	up->curregs[R15] |= BRKIE;
	brg = BPS_TO_BRG(baud, ZS_CLOCK / ZS_CLOCK_DIVISOR);
	sunzilog_convert_to_zs(up, up->cflag, 0, brg);
	sunzilog_set_mctrl(&up->port, TIOCM_DTR | TIOCM_RTS);
	__sunzilog_startup(up);
पूर्ण

#अगर_घोषित CONFIG_SERIO
अटल व्योम sunzilog_रेजिस्टर_serio(काष्ठा uart_sunzilog_port *up)
अणु
	काष्ठा serio *serio = &up->serio;

	serio->port_data = up;

	serio->id.type = SERIO_RS232;
	अगर (up->flags & SUNZILOG_FLAG_CONS_KEYB) अणु
		serio->id.proto = SERIO_SUNKBD;
		strlcpy(serio->name, "zskbd", माप(serio->name));
	पूर्ण अन्यथा अणु
		serio->id.proto = SERIO_SUN;
		serio->id.extra = 1;
		strlcpy(serio->name, "zsms", माप(serio->name));
	पूर्ण
	strlcpy(serio->phys,
		((up->flags & SUNZILOG_FLAG_CONS_KEYB) ?
		 "zs/serio0" : "zs/serio1"),
		माप(serio->phys));

	serio->ग_लिखो = sunzilog_serio_ग_लिखो;
	serio->खोलो = sunzilog_serio_खोलो;
	serio->बंद = sunzilog_serio_बंद;
	serio->dev.parent = up->port.dev;

	serio_रेजिस्टर_port(serio);
पूर्ण
#पूर्ण_अगर

अटल व्योम sunzilog_init_hw(काष्ठा uart_sunzilog_port *up)
अणु
	काष्ठा zilog_channel __iomem *channel;
	अचिन्हित दीर्घ flags;
	पूर्णांक baud, brg;

	channel = ZILOG_CHANNEL_FROM_PORT(&up->port);

	spin_lock_irqsave(&up->port.lock, flags);
	अगर (ZS_IS_CHANNEL_A(up)) अणु
		ग_लिखो_zsreg(channel, R9, FHWRES);
		ZSDELAY_LONG();
		(व्योम) पढ़ो_zsreg(channel, R0);
	पूर्ण

	अगर (up->flags & (SUNZILOG_FLAG_CONS_KEYB |
			 SUNZILOG_FLAG_CONS_MOUSE)) अणु
		up->curregs[R1] = EXT_INT_ENAB | INT_ALL_Rx | TxINT_ENAB;
		up->curregs[R4] = PAR_EVEN | X16CLK | SB1;
		up->curregs[R3] = RxENAB | Rx8;
		up->curregs[R5] = TxENAB | Tx8;
		up->curregs[R6] = 0x00; /* SDLC Address */
		up->curregs[R7] = 0x7E; /* SDLC Flag    */
		up->curregs[R9] = NV;
		up->curregs[R7p] = 0x00;
		sunzilog_init_kbdms(up);
		/* Only enable पूर्णांकerrupts अगर an ISR handler available */
		अगर (up->flags & SUNZILOG_FLAG_ISR_HANDLER)
			up->curregs[R9] |= MIE;
		ग_लिखो_zsreg(channel, R9, up->curregs[R9]);
	पूर्ण अन्यथा अणु
		/* Normal serial TTY. */
		up->parity_mask = 0xff;
		up->curregs[R1] = EXT_INT_ENAB | INT_ALL_Rx | TxINT_ENAB;
		up->curregs[R4] = PAR_EVEN | X16CLK | SB1;
		up->curregs[R3] = RxENAB | Rx8;
		up->curregs[R5] = TxENAB | Tx8;
		up->curregs[R6] = 0x00; /* SDLC Address */
		up->curregs[R7] = 0x7E; /* SDLC Flag    */
		up->curregs[R9] = NV;
		up->curregs[R10] = NRZ;
		up->curregs[R11] = TCBR | RCBR;
		baud = 9600;
		brg = BPS_TO_BRG(baud, ZS_CLOCK / ZS_CLOCK_DIVISOR);
		up->curregs[R12] = (brg & 0xff);
		up->curregs[R13] = (brg >> 8) & 0xff;
		up->curregs[R14] = BRSRC | BRENAB;
		up->curregs[R15] = FIFOEN; /* Use FIFO अगर on ESCC */
		up->curregs[R7p] = TxFIFO_LVL | RxFIFO_LVL;
		अगर (__load_zsregs(channel, up->curregs)) अणु
			up->flags |= SUNZILOG_FLAG_ESCC;
		पूर्ण
		/* Only enable पूर्णांकerrupts अगर an ISR handler available */
		अगर (up->flags & SUNZILOG_FLAG_ISR_HANDLER)
			up->curregs[R9] |= MIE;
		ग_लिखो_zsreg(channel, R9, up->curregs[R9]);
	पूर्ण

	spin_unlock_irqrestore(&up->port.lock, flags);

#अगर_घोषित CONFIG_SERIO
	अगर (up->flags & (SUNZILOG_FLAG_CONS_KEYB |
			 SUNZILOG_FLAG_CONS_MOUSE))
		sunzilog_रेजिस्टर_serio(up);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक zilog_irq;

अटल पूर्णांक zs_probe(काष्ठा platक्रमm_device *op)
अणु
	अटल पूर्णांक kbm_inst, uart_inst;
	पूर्णांक inst;
	काष्ठा uart_sunzilog_port *up;
	काष्ठा zilog_layout __iomem *rp;
	पूर्णांक keyboard_mouse = 0;
	पूर्णांक err;

	अगर (of_find_property(op->dev.of_node, "keyboard", शून्य))
		keyboard_mouse = 1;

	/* uarts must come beक्रमe keyboards/mice */
	अगर (keyboard_mouse)
		inst = uart_chip_count + kbm_inst;
	अन्यथा
		inst = uart_inst;

	sunzilog_chip_regs[inst] = of_ioremap(&op->resource[0], 0,
					      माप(काष्ठा zilog_layout),
					      "zs");
	अगर (!sunzilog_chip_regs[inst])
		वापस -ENOMEM;

	rp = sunzilog_chip_regs[inst];

	अगर (!zilog_irq)
		zilog_irq = op->archdata.irqs[0];

	up = &sunzilog_port_table[inst * 2];

	/* Channel A */
	up[0].port.mapbase = op->resource[0].start + 0x00;
	up[0].port.membase = (व्योम __iomem *) &rp->channelA;
	up[0].port.iotype = UPIO_MEM;
	up[0].port.irq = op->archdata.irqs[0];
	up[0].port.uartclk = ZS_CLOCK;
	up[0].port.fअगरosize = 1;
	up[0].port.ops = &sunzilog_pops;
	up[0].port.type = PORT_SUNZILOG;
	up[0].port.flags = 0;
	up[0].port.line = (inst * 2) + 0;
	up[0].port.dev = &op->dev;
	up[0].flags |= SUNZILOG_FLAG_IS_CHANNEL_A;
	up[0].port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_SUNZILOG_CONSOLE);
	अगर (keyboard_mouse)
		up[0].flags |= SUNZILOG_FLAG_CONS_KEYB;
	sunzilog_init_hw(&up[0]);

	/* Channel B */
	up[1].port.mapbase = op->resource[0].start + 0x04;
	up[1].port.membase = (व्योम __iomem *) &rp->channelB;
	up[1].port.iotype = UPIO_MEM;
	up[1].port.irq = op->archdata.irqs[0];
	up[1].port.uartclk = ZS_CLOCK;
	up[1].port.fअगरosize = 1;
	up[1].port.ops = &sunzilog_pops;
	up[1].port.type = PORT_SUNZILOG;
	up[1].port.flags = 0;
	up[1].port.line = (inst * 2) + 1;
	up[1].port.dev = &op->dev;
	up[1].flags |= 0;
	up[1].port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_SUNZILOG_CONSOLE);
	अगर (keyboard_mouse)
		up[1].flags |= SUNZILOG_FLAG_CONS_MOUSE;
	sunzilog_init_hw(&up[1]);

	अगर (!keyboard_mouse) अणु
		अगर (sunserial_console_match(SUNZILOG_CONSOLE(), op->dev.of_node,
					    &sunzilog_reg, up[0].port.line,
					    false))
			up->flags |= SUNZILOG_FLAG_IS_CONS;
		err = uart_add_one_port(&sunzilog_reg, &up[0].port);
		अगर (err) अणु
			of_iounmap(&op->resource[0],
				   rp, माप(काष्ठा zilog_layout));
			वापस err;
		पूर्ण
		अगर (sunserial_console_match(SUNZILOG_CONSOLE(), op->dev.of_node,
					    &sunzilog_reg, up[1].port.line,
					    false))
			up->flags |= SUNZILOG_FLAG_IS_CONS;
		err = uart_add_one_port(&sunzilog_reg, &up[1].port);
		अगर (err) अणु
			uart_हटाओ_one_port(&sunzilog_reg, &up[0].port);
			of_iounmap(&op->resource[0],
				   rp, माप(काष्ठा zilog_layout));
			वापस err;
		पूर्ण
		uart_inst++;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "%s: Keyboard at MMIO 0x%llx (irq = %d) "
		       "is a %s\n",
		       dev_name(&op->dev),
		       (अचिन्हित दीर्घ दीर्घ) up[0].port.mapbase,
		       op->archdata.irqs[0], sunzilog_type(&up[0].port));
		prपूर्णांकk(KERN_INFO "%s: Mouse at MMIO 0x%llx (irq = %d) "
		       "is a %s\n",
		       dev_name(&op->dev),
		       (अचिन्हित दीर्घ दीर्घ) up[1].port.mapbase,
		       op->archdata.irqs[0], sunzilog_type(&up[1].port));
		kbm_inst++;
	पूर्ण

	platक्रमm_set_drvdata(op, &up[0]);

	वापस 0;
पूर्ण

अटल व्योम zs_हटाओ_one(काष्ठा uart_sunzilog_port *up)
अणु
	अगर (ZS_IS_KEYB(up) || ZS_IS_MOUSE(up)) अणु
#अगर_घोषित CONFIG_SERIO
		serio_unरेजिस्टर_port(&up->serio);
#पूर्ण_अगर
	पूर्ण अन्यथा
		uart_हटाओ_one_port(&sunzilog_reg, &up->port);
पूर्ण

अटल पूर्णांक zs_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा uart_sunzilog_port *up = platक्रमm_get_drvdata(op);
	काष्ठा zilog_layout __iomem *regs;

	zs_हटाओ_one(&up[0]);
	zs_हटाओ_one(&up[1]);

	regs = sunzilog_chip_regs[up[0].port.line / 2];
	of_iounmap(&op->resource[0], regs, माप(काष्ठा zilog_layout));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id zs_match[] = अणु
	अणु
		.name = "zs",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, zs_match);

अटल काष्ठा platक्रमm_driver zs_driver = अणु
	.driver = अणु
		.name = "zs",
		.of_match_table = zs_match,
	पूर्ण,
	.probe		= zs_probe,
	.हटाओ		= zs_हटाओ,
पूर्ण;

अटल पूर्णांक __init sunzilog_init(व्योम)
अणु
	काष्ठा device_node *dp;
	पूर्णांक err;
	पूर्णांक num_keybms = 0;
	पूर्णांक num_sunzilog = 0;

	क्रम_each_node_by_name(dp, "zs") अणु
		num_sunzilog++;
		अगर (of_find_property(dp, "keyboard", शून्य))
			num_keybms++;
	पूर्ण

	अगर (num_sunzilog) अणु
		err = sunzilog_alloc_tables(num_sunzilog);
		अगर (err)
			जाओ out;

		uart_chip_count = num_sunzilog - num_keybms;

		err = sunserial_रेजिस्टर_minors(&sunzilog_reg,
						uart_chip_count * 2);
		अगर (err)
			जाओ out_मुक्त_tables;
	पूर्ण

	err = platक्रमm_driver_रेजिस्टर(&zs_driver);
	अगर (err)
		जाओ out_unरेजिस्टर_uart;

	अगर (zilog_irq) अणु
		काष्ठा uart_sunzilog_port *up = sunzilog_irq_chain;
		err = request_irq(zilog_irq, sunzilog_पूर्णांकerrupt, IRQF_SHARED,
				  "zs", sunzilog_irq_chain);
		अगर (err)
			जाओ out_unरेजिस्टर_driver;

		/* Enable Interrupts */
		जबतक (up) अणु
			काष्ठा zilog_channel __iomem *channel;

			/* prपूर्णांकk (KERN_INFO "Enable IRQ for ZILOG Hardware %p\n", up); */
			channel          = ZILOG_CHANNEL_FROM_PORT(&up->port);
			up->flags       |= SUNZILOG_FLAG_ISR_HANDLER;
			up->curregs[R9] |= MIE;
			ग_लिखो_zsreg(channel, R9, up->curregs[R9]);
			up = up->next;
		पूर्ण
	पूर्ण

out:
	वापस err;

out_unरेजिस्टर_driver:
	platक्रमm_driver_unरेजिस्टर(&zs_driver);

out_unरेजिस्टर_uart:
	अगर (num_sunzilog) अणु
		sunserial_unरेजिस्टर_minors(&sunzilog_reg, num_sunzilog);
		sunzilog_reg.cons = शून्य;
	पूर्ण

out_मुक्त_tables:
	sunzilog_मुक्त_tables();
	जाओ out;
पूर्ण

अटल व्योम __निकास sunzilog_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&zs_driver);

	अगर (zilog_irq) अणु
		काष्ठा uart_sunzilog_port *up = sunzilog_irq_chain;

		/* Disable Interrupts */
		जबतक (up) अणु
			काष्ठा zilog_channel __iomem *channel;

			/* prपूर्णांकk (KERN_INFO "Disable IRQ for ZILOG Hardware %p\n", up); */
			channel          = ZILOG_CHANNEL_FROM_PORT(&up->port);
			up->flags       &= ~SUNZILOG_FLAG_ISR_HANDLER;
			up->curregs[R9] &= ~MIE;
			ग_लिखो_zsreg(channel, R9, up->curregs[R9]);
			up = up->next;
		पूर्ण

		मुक्त_irq(zilog_irq, sunzilog_irq_chain);
		zilog_irq = 0;
	पूर्ण

	अगर (sunzilog_reg.nr) अणु
		sunserial_unरेजिस्टर_minors(&sunzilog_reg, sunzilog_reg.nr);
		sunzilog_मुक्त_tables();
	पूर्ण
पूर्ण

module_init(sunzilog_init);
module_निकास(sunzilog_निकास);

MODULE_AUTHOR("David S. Miller");
MODULE_DESCRIPTION("Sun Zilog serial port driver");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
