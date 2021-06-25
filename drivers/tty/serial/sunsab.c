<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* sunsab.c: ASYNC Driver क्रम the SIEMENS SAB82532 DUSCC.
 *
 * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)
 * Copyright (C) 2002, 2006  David S. Miller (davem@davemloft.net)
 *
 * Rewrote buffer handling to use CIRC(Circular Buffer) macros.
 *   Maxim Krasnyanskiy <maxk@qualcomm.com>
 *
 * Fixed to use tty_get_baud_rate, and to allow क्रम arbitrary baud
 * rates to be programmed पूर्णांकo the UART.  Also eliminated a lot of
 * duplicated code in the console setup.
 *   Theoकरोre Ts'o <tytso@mit.edu>, 2001-Oct-12
 *
 * Ported to new 2.5.x UART layer.
 *   David S. Miller <davem@davemloft.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
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
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/setup.h>

#समावेश <linux/serial_core.h>
#समावेश <linux/sunserialcore.h>

#समावेश "sunsab.h"

काष्ठा uart_sunsab_port अणु
	काष्ठा uart_port		port;		/* Generic UART port	*/
	जोड़ sab82532_async_regs	__iomem *regs;	/* Chip रेजिस्टरs	*/
	अचिन्हित दीर्घ			irqflags;	/* IRQ state flags	*/
	पूर्णांक				dsr;		/* Current DSR state	*/
	अचिन्हित पूर्णांक			cec_समयout;	/* Chip poll समयout... */
	अचिन्हित पूर्णांक			tec_समयout;	/* likewise		*/
	अचिन्हित अक्षर			पूर्णांकerrupt_mask0;/* ISR0 masking		*/
	अचिन्हित अक्षर			पूर्णांकerrupt_mask1;/* ISR1 masking		*/
	अचिन्हित अक्षर			pvr_dtr_bit;	/* Which PVR bit is DTR */
	अचिन्हित अक्षर			pvr_dsr_bit;	/* Which PVR bit is DSR */
	अचिन्हित पूर्णांक			gis_shअगरt;
	पूर्णांक				type;		/* SAB82532 version	*/

	/* Setting configuration bits जबतक the transmitter is active
	 * can cause garbage अक्षरacters to get emitted by the chip.
	 * Thereक्रमe, we cache such ग_लिखोs here and करो the real रेजिस्टर
	 * ग_लिखो the next समय the transmitter becomes idle.
	 */
	अचिन्हित पूर्णांक			cached_ebrg;
	अचिन्हित अक्षर			cached_mode;
	अचिन्हित अक्षर			cached_pvr;
	अचिन्हित अक्षर			cached_dafo;
पूर्ण;

/*
 * This assumes you have a 29.4912 MHz घड़ी क्रम your UART.
 */
#घोषणा SAB_BASE_BAUD ( 29491200 / 16 )

अटल अक्षर *sab82532_version[16] = अणु
	"V1.0", "V2.0", "V3.2", "V(0x03)",
	"V(0x04)", "V(0x05)", "V(0x06)", "V(0x07)",
	"V(0x08)", "V(0x09)", "V(0x0a)", "V(0x0b)",
	"V(0x0c)", "V(0x0d)", "V(0x0e)", "V(0x0f)"
पूर्ण;

#घोषणा SAB82532_MAX_TEC_TIMEOUT 200000	/* 1 अक्षरacter समय (at 50 baud) */
#घोषणा SAB82532_MAX_CEC_TIMEOUT  50000	/* 2.5 TX CLKs (at 50 baud) */

#घोषणा SAB82532_RECV_FIFO_SIZE	32      /* Standard async fअगरo sizes */
#घोषणा SAB82532_XMIT_FIFO_SIZE	32

अटल __अंतरभूत__ व्योम sunsab_tec_रुको(काष्ठा uart_sunsab_port *up)
अणु
	पूर्णांक समयout = up->tec_समयout;

	जबतक ((पढ़ोb(&up->regs->r.star) & SAB82532_STAR_TEC) && --समयout)
		udelay(1);
पूर्ण

अटल __अंतरभूत__ व्योम sunsab_cec_रुको(काष्ठा uart_sunsab_port *up)
अणु
	पूर्णांक समयout = up->cec_समयout;

	जबतक ((पढ़ोb(&up->regs->r.star) & SAB82532_STAR_CEC) && --समयout)
		udelay(1);
पूर्ण

अटल काष्ठा tty_port *
receive_अक्षरs(काष्ठा uart_sunsab_port *up,
	      जोड़ sab82532_irq_status *stat)
अणु
	काष्ठा tty_port *port = शून्य;
	अचिन्हित अक्षर buf[32];
	पूर्णांक saw_console_brk = 0;
	पूर्णांक मुक्त_fअगरo = 0;
	पूर्णांक count = 0;
	पूर्णांक i;

	अगर (up->port.state != शून्य)		/* Unखोलोed serial console */
		port = &up->port.state->port;

	/* Read number of BYTES (Character + Status) available. */
	अगर (stat->sreg.isr0 & SAB82532_ISR0_RPF) अणु
		count = SAB82532_RECV_FIFO_SIZE;
		मुक्त_fअगरo++;
	पूर्ण

	अगर (stat->sreg.isr0 & SAB82532_ISR0_TCD) अणु
		count = पढ़ोb(&up->regs->r.rbcl) & (SAB82532_RECV_FIFO_SIZE - 1);
		मुक्त_fअगरo++;
	पूर्ण

	/* Issue a FIFO पढ़ो command in हाल we where idle. */
	अगर (stat->sreg.isr0 & SAB82532_ISR0_TIME) अणु
		sunsab_cec_रुको(up);
		ग_लिखोb(SAB82532_CMDR_RFRD, &up->regs->w.cmdr);
		वापस port;
	पूर्ण

	अगर (stat->sreg.isr0 & SAB82532_ISR0_RFO)
		मुक्त_fअगरo++;

	/* Read the FIFO. */
	क्रम (i = 0; i < count; i++)
		buf[i] = पढ़ोb(&up->regs->r.rfअगरo[i]);

	/* Issue Receive Message Complete command. */
	अगर (मुक्त_fअगरo) अणु
		sunsab_cec_रुको(up);
		ग_लिखोb(SAB82532_CMDR_RMC, &up->regs->w.cmdr);
	पूर्ण

	/* Count may be zero क्रम BRK, so we check क्रम it here */
	अगर ((stat->sreg.isr1 & SAB82532_ISR1_BRK) &&
	    (up->port.line == up->port.cons->index))
		saw_console_brk = 1;

	अगर (count == 0) अणु
		अगर (unlikely(stat->sreg.isr1 & SAB82532_ISR1_BRK)) अणु
			stat->sreg.isr0 &= ~(SAB82532_ISR0_PERR |
					     SAB82532_ISR0_FERR);
			up->port.icount.brk++;
			uart_handle_अवरोध(&up->port);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		अचिन्हित अक्षर ch = buf[i], flag;

		flag = TTY_NORMAL;
		up->port.icount.rx++;

		अगर (unlikely(stat->sreg.isr0 & (SAB82532_ISR0_PERR |
						SAB82532_ISR0_FERR |
						SAB82532_ISR0_RFO)) ||
		    unlikely(stat->sreg.isr1 & SAB82532_ISR1_BRK)) अणु
			/*
			 * For statistics only
			 */
			अगर (stat->sreg.isr1 & SAB82532_ISR1_BRK) अणु
				stat->sreg.isr0 &= ~(SAB82532_ISR0_PERR |
						     SAB82532_ISR0_FERR);
				up->port.icount.brk++;
				/*
				 * We करो the SysRQ and SAK checking
				 * here because otherwise the अवरोध
				 * may get masked by ignore_status_mask
				 * or पढ़ो_status_mask.
				 */
				अगर (uart_handle_अवरोध(&up->port))
					जारी;
			पूर्ण अन्यथा अगर (stat->sreg.isr0 & SAB82532_ISR0_PERR)
				up->port.icount.parity++;
			अन्यथा अगर (stat->sreg.isr0 & SAB82532_ISR0_FERR)
				up->port.icount.frame++;
			अगर (stat->sreg.isr0 & SAB82532_ISR0_RFO)
				up->port.icount.overrun++;

			/*
			 * Mask off conditions which should be ingored.
			 */
			stat->sreg.isr0 &= (up->port.पढ़ो_status_mask & 0xff);
			stat->sreg.isr1 &= ((up->port.पढ़ो_status_mask >> 8) & 0xff);

			अगर (stat->sreg.isr1 & SAB82532_ISR1_BRK) अणु
				flag = TTY_BREAK;
			पूर्ण अन्यथा अगर (stat->sreg.isr0 & SAB82532_ISR0_PERR)
				flag = TTY_PARITY;
			अन्यथा अगर (stat->sreg.isr0 & SAB82532_ISR0_FERR)
				flag = TTY_FRAME;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(&up->port, ch) || !port)
			जारी;

		अगर ((stat->sreg.isr0 & (up->port.ignore_status_mask & 0xff)) == 0 &&
		    (stat->sreg.isr1 & ((up->port.ignore_status_mask >> 8) & 0xff)) == 0)
			tty_insert_flip_अक्षर(port, ch, flag);
		अगर (stat->sreg.isr0 & SAB82532_ISR0_RFO)
			tty_insert_flip_अक्षर(port, 0, TTY_OVERRUN);
	पूर्ण

	अगर (saw_console_brk)
		sun_करो_अवरोध();

	वापस port;
पूर्ण

अटल व्योम sunsab_stop_tx(काष्ठा uart_port *);
अटल व्योम sunsab_tx_idle(काष्ठा uart_sunsab_port *);

अटल व्योम transmit_अक्षरs(काष्ठा uart_sunsab_port *up,
			   जोड़ sab82532_irq_status *stat)
अणु
	काष्ठा circ_buf *xmit = &up->port.state->xmit;
	पूर्णांक i;

	अगर (stat->sreg.isr1 & SAB82532_ISR1_ALLS) अणु
		up->पूर्णांकerrupt_mask1 |= SAB82532_IMR1_ALLS;
		ग_लिखोb(up->पूर्णांकerrupt_mask1, &up->regs->w.imr1);
		set_bit(SAB82532_ALLS, &up->irqflags);
	पूर्ण

#अगर 0 /* bde@nwlink.com says this check causes problems */
	अगर (!(stat->sreg.isr1 & SAB82532_ISR1_XPR))
		वापस;
#पूर्ण_अगर

	अगर (!(पढ़ोb(&up->regs->r.star) & SAB82532_STAR_XFW))
		वापस;

	set_bit(SAB82532_XPR, &up->irqflags);
	sunsab_tx_idle(up);

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(&up->port)) अणु
		up->पूर्णांकerrupt_mask1 |= SAB82532_IMR1_XPR;
		ग_लिखोb(up->पूर्णांकerrupt_mask1, &up->regs->w.imr1);
		वापस;
	पूर्ण

	up->पूर्णांकerrupt_mask1 &= ~(SAB82532_IMR1_ALLS|SAB82532_IMR1_XPR);
	ग_लिखोb(up->पूर्णांकerrupt_mask1, &up->regs->w.imr1);
	clear_bit(SAB82532_ALLS, &up->irqflags);

	/* Stuff 32 bytes पूर्णांकo Transmit FIFO. */
	clear_bit(SAB82532_XPR, &up->irqflags);
	क्रम (i = 0; i < up->port.fअगरosize; i++) अणु
		ग_लिखोb(xmit->buf[xmit->tail],
		       &up->regs->w.xfअगरo[i]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		up->port.icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण

	/* Issue a Transmit Frame command. */
	sunsab_cec_रुको(up);
	ग_लिखोb(SAB82532_CMDR_XF, &up->regs->w.cmdr);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&up->port);

	अगर (uart_circ_empty(xmit))
		sunsab_stop_tx(&up->port);
पूर्ण

अटल व्योम check_status(काष्ठा uart_sunsab_port *up,
			 जोड़ sab82532_irq_status *stat)
अणु
	अगर (stat->sreg.isr0 & SAB82532_ISR0_CDSC)
		uart_handle_dcd_change(&up->port,
				       !(पढ़ोb(&up->regs->r.vstr) & SAB82532_VSTR_CD));

	अगर (stat->sreg.isr1 & SAB82532_ISR1_CSC)
		uart_handle_cts_change(&up->port,
				       (पढ़ोb(&up->regs->r.star) & SAB82532_STAR_CTS));

	अगर ((पढ़ोb(&up->regs->r.pvr) & up->pvr_dsr_bit) ^ up->dsr) अणु
		up->dsr = (पढ़ोb(&up->regs->r.pvr) & up->pvr_dsr_bit) ? 0 : 1;
		up->port.icount.dsr++;
	पूर्ण

	wake_up_पूर्णांकerruptible(&up->port.state->port.delta_msr_रुको);
पूर्ण

अटल irqवापस_t sunsab_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_sunsab_port *up = dev_id;
	काष्ठा tty_port *port = शून्य;
	जोड़ sab82532_irq_status status;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर gis;

	spin_lock_irqsave(&up->port.lock, flags);

	status.stat = 0;
	gis = पढ़ोb(&up->regs->r.gis) >> up->gis_shअगरt;
	अगर (gis & 1)
		status.sreg.isr0 = पढ़ोb(&up->regs->r.isr0);
	अगर (gis & 2)
		status.sreg.isr1 = पढ़ोb(&up->regs->r.isr1);

	अगर (status.stat) अणु
		अगर ((status.sreg.isr0 & (SAB82532_ISR0_TCD | SAB82532_ISR0_TIME |
					 SAB82532_ISR0_RFO | SAB82532_ISR0_RPF)) ||
		    (status.sreg.isr1 & SAB82532_ISR1_BRK))
			port = receive_अक्षरs(up, &status);
		अगर ((status.sreg.isr0 & SAB82532_ISR0_CDSC) ||
		    (status.sreg.isr1 & SAB82532_ISR1_CSC))
			check_status(up, &status);
		अगर (status.sreg.isr1 & (SAB82532_ISR1_ALLS | SAB82532_ISR1_XPR))
			transmit_अक्षरs(up, &status);
	पूर्ण

	spin_unlock_irqrestore(&up->port.lock, flags);

	अगर (port)
		tty_flip_buffer_push(port);

	वापस IRQ_HANDLED;
पूर्ण

/* port->lock is not held.  */
अटल अचिन्हित पूर्णांक sunsab_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunsab_port *up =
		container_of(port, काष्ठा uart_sunsab_port, port);
	पूर्णांक ret;

	/* Do not need a lock क्रम a state test like this.  */
	अगर (test_bit(SAB82532_ALLS, &up->irqflags))
		ret = TIOCSER_TEMT;
	अन्यथा
		ret = 0;

	वापस ret;
पूर्ण

/* port->lock held by caller.  */
अटल व्योम sunsab_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा uart_sunsab_port *up =
		container_of(port, काष्ठा uart_sunsab_port, port);

	अगर (mctrl & TIOCM_RTS) अणु
		up->cached_mode &= ~SAB82532_MODE_FRTS;
		up->cached_mode |= SAB82532_MODE_RTS;
	पूर्ण अन्यथा अणु
		up->cached_mode |= (SAB82532_MODE_FRTS |
				    SAB82532_MODE_RTS);
	पूर्ण
	अगर (mctrl & TIOCM_DTR) अणु
		up->cached_pvr &= ~(up->pvr_dtr_bit);
	पूर्ण अन्यथा अणु
		up->cached_pvr |= up->pvr_dtr_bit;
	पूर्ण

	set_bit(SAB82532_REGS_PENDING, &up->irqflags);
	अगर (test_bit(SAB82532_XPR, &up->irqflags))
		sunsab_tx_idle(up);
पूर्ण

/* port->lock is held by caller and पूर्णांकerrupts are disabled.  */
अटल अचिन्हित पूर्णांक sunsab_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunsab_port *up =
		container_of(port, काष्ठा uart_sunsab_port, port);
	अचिन्हित अक्षर val;
	अचिन्हित पूर्णांक result;

	result = 0;

	val = पढ़ोb(&up->regs->r.pvr);
	result |= (val & up->pvr_dsr_bit) ? 0 : TIOCM_DSR;

	val = पढ़ोb(&up->regs->r.vstr);
	result |= (val & SAB82532_VSTR_CD) ? 0 : TIOCM_CAR;

	val = पढ़ोb(&up->regs->r.star);
	result |= (val & SAB82532_STAR_CTS) ? TIOCM_CTS : 0;

	वापस result;
पूर्ण

/* port->lock held by caller.  */
अटल व्योम sunsab_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunsab_port *up =
		container_of(port, काष्ठा uart_sunsab_port, port);

	up->पूर्णांकerrupt_mask1 |= SAB82532_IMR1_XPR;
	ग_लिखोb(up->पूर्णांकerrupt_mask1, &up->regs->w.imr1);
पूर्ण

/* port->lock held by caller.  */
अटल व्योम sunsab_tx_idle(काष्ठा uart_sunsab_port *up)
अणु
	अगर (test_bit(SAB82532_REGS_PENDING, &up->irqflags)) अणु
		u8 पंचांगp;

		clear_bit(SAB82532_REGS_PENDING, &up->irqflags);
		ग_लिखोb(up->cached_mode, &up->regs->rw.mode);
		ग_लिखोb(up->cached_pvr, &up->regs->rw.pvr);
		ग_लिखोb(up->cached_dafo, &up->regs->w.dafo);

		ग_लिखोb(up->cached_ebrg & 0xff, &up->regs->w.bgr);
		पंचांगp = पढ़ोb(&up->regs->rw.ccr2);
		पंचांगp &= ~0xc0;
		पंचांगp |= (up->cached_ebrg >> 2) & 0xc0;
		ग_लिखोb(पंचांगp, &up->regs->rw.ccr2);
	पूर्ण
पूर्ण

/* port->lock held by caller.  */
अटल व्योम sunsab_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunsab_port *up =
		container_of(port, काष्ठा uart_sunsab_port, port);
	काष्ठा circ_buf *xmit = &up->port.state->xmit;
	पूर्णांक i;

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port))
		वापस;

	up->पूर्णांकerrupt_mask1 &= ~(SAB82532_IMR1_ALLS|SAB82532_IMR1_XPR);
	ग_लिखोb(up->पूर्णांकerrupt_mask1, &up->regs->w.imr1);
	
	अगर (!test_bit(SAB82532_XPR, &up->irqflags))
		वापस;

	clear_bit(SAB82532_ALLS, &up->irqflags);
	clear_bit(SAB82532_XPR, &up->irqflags);

	क्रम (i = 0; i < up->port.fअगरosize; i++) अणु
		ग_लिखोb(xmit->buf[xmit->tail],
		       &up->regs->w.xfअगरo[i]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		up->port.icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण

	/* Issue a Transmit Frame command.  */
	sunsab_cec_रुको(up);
	ग_लिखोb(SAB82532_CMDR_XF, &up->regs->w.cmdr);
पूर्ण

/* port->lock is not held.  */
अटल व्योम sunsab_send_xअक्षर(काष्ठा uart_port *port, अक्षर ch)
अणु
	काष्ठा uart_sunsab_port *up =
		container_of(port, काष्ठा uart_sunsab_port, port);
	अचिन्हित दीर्घ flags;

	अगर (ch == __DISABLED_CHAR)
		वापस;

	spin_lock_irqsave(&up->port.lock, flags);

	sunsab_tec_रुको(up);
	ग_लिखोb(ch, &up->regs->w.tic);

	spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

/* port->lock held by caller.  */
अटल व्योम sunsab_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunsab_port *up =
		container_of(port, काष्ठा uart_sunsab_port, port);

	up->पूर्णांकerrupt_mask0 |= SAB82532_IMR0_TCD;
	ग_लिखोb(up->पूर्णांकerrupt_mask1, &up->regs->w.imr0);
पूर्ण

/* port->lock is not held.  */
अटल व्योम sunsab_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा uart_sunsab_port *up =
		container_of(port, काष्ठा uart_sunsab_port, port);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर val;

	spin_lock_irqsave(&up->port.lock, flags);

	val = up->cached_dafo;
	अगर (अवरोध_state)
		val |= SAB82532_DAFO_XBRK;
	अन्यथा
		val &= ~SAB82532_DAFO_XBRK;
	up->cached_dafo = val;

	set_bit(SAB82532_REGS_PENDING, &up->irqflags);
	अगर (test_bit(SAB82532_XPR, &up->irqflags))
		sunsab_tx_idle(up);

	spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

/* port->lock is not held.  */
अटल पूर्णांक sunsab_startup(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunsab_port *up =
		container_of(port, काष्ठा uart_sunsab_port, port);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर पंचांगp;
	पूर्णांक err = request_irq(up->port.irq, sunsab_पूर्णांकerrupt,
			      IRQF_SHARED, "sab", up);
	अगर (err)
		वापस err;

	spin_lock_irqsave(&up->port.lock, flags);

	/*
	 * Wait क्रम any commands or immediate अक्षरacters
	 */
	sunsab_cec_रुको(up);
	sunsab_tec_रुको(up);

	/*
	 * Clear the FIFO buffers.
	 */
	ग_लिखोb(SAB82532_CMDR_RRES, &up->regs->w.cmdr);
	sunsab_cec_रुको(up);
	ग_लिखोb(SAB82532_CMDR_XRES, &up->regs->w.cmdr);

	/*
	 * Clear the पूर्णांकerrupt रेजिस्टरs.
	 */
	(व्योम) पढ़ोb(&up->regs->r.isr0);
	(व्योम) पढ़ोb(&up->regs->r.isr1);

	/*
	 * Now, initialize the UART 
	 */
	ग_लिखोb(0, &up->regs->w.ccr0);				/* घातer-करोwn */
	ग_लिखोb(SAB82532_CCR0_MCE | SAB82532_CCR0_SC_NRZ |
	       SAB82532_CCR0_SM_ASYNC, &up->regs->w.ccr0);
	ग_लिखोb(SAB82532_CCR1_ODS | SAB82532_CCR1_BCR | 7, &up->regs->w.ccr1);
	ग_लिखोb(SAB82532_CCR2_BDF | SAB82532_CCR2_SSEL |
	       SAB82532_CCR2_TOE, &up->regs->w.ccr2);
	ग_लिखोb(0, &up->regs->w.ccr3);
	ग_लिखोb(SAB82532_CCR4_MCK4 | SAB82532_CCR4_EBRG, &up->regs->w.ccr4);
	up->cached_mode = (SAB82532_MODE_RTS | SAB82532_MODE_FCTS |
			   SAB82532_MODE_RAC);
	ग_लिखोb(up->cached_mode, &up->regs->w.mode);
	ग_लिखोb(SAB82532_RFC_DPS|SAB82532_RFC_RFTH_32, &up->regs->w.rfc);
	
	पंचांगp = पढ़ोb(&up->regs->rw.ccr0);
	पंचांगp |= SAB82532_CCR0_PU;	/* घातer-up */
	ग_लिखोb(पंचांगp, &up->regs->rw.ccr0);

	/*
	 * Finally, enable पूर्णांकerrupts
	 */
	up->पूर्णांकerrupt_mask0 = (SAB82532_IMR0_PERR | SAB82532_IMR0_FERR |
			       SAB82532_IMR0_PLLA);
	ग_लिखोb(up->पूर्णांकerrupt_mask0, &up->regs->w.imr0);
	up->पूर्णांकerrupt_mask1 = (SAB82532_IMR1_BRKT | SAB82532_IMR1_ALLS |
			       SAB82532_IMR1_XOFF | SAB82532_IMR1_TIN |
			       SAB82532_IMR1_CSC | SAB82532_IMR1_XON |
			       SAB82532_IMR1_XPR);
	ग_लिखोb(up->पूर्णांकerrupt_mask1, &up->regs->w.imr1);
	set_bit(SAB82532_ALLS, &up->irqflags);
	set_bit(SAB82532_XPR, &up->irqflags);

	spin_unlock_irqrestore(&up->port.lock, flags);

	वापस 0;
पूर्ण

/* port->lock is not held.  */
अटल व्योम sunsab_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunsab_port *up =
		container_of(port, काष्ठा uart_sunsab_port, port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&up->port.lock, flags);

	/* Disable Interrupts */
	up->पूर्णांकerrupt_mask0 = 0xff;
	ग_लिखोb(up->पूर्णांकerrupt_mask0, &up->regs->w.imr0);
	up->पूर्णांकerrupt_mask1 = 0xff;
	ग_लिखोb(up->पूर्णांकerrupt_mask1, &up->regs->w.imr1);

	/* Disable अवरोध condition */
	up->cached_dafo = पढ़ोb(&up->regs->rw.dafo);
	up->cached_dafo &= ~SAB82532_DAFO_XBRK;
	ग_लिखोb(up->cached_dafo, &up->regs->rw.dafo);

	/* Disable Receiver */	
	up->cached_mode &= ~SAB82532_MODE_RAC;
	ग_लिखोb(up->cached_mode, &up->regs->rw.mode);

	/*
	 * XXX FIXME
	 *
	 * If the chip is घातered करोwn here the प्रणाली hangs/crashes during
	 * reboot or shutकरोwn.  This needs to be investigated further,
	 * similar behaviour occurs in 2.4 when the driver is configured
	 * as a module only.  One hपूर्णांक may be that data is someबार
	 * transmitted at 9600 baud during shutकरोwn (regardless of the
	 * speed the chip was configured क्रम when the port was खोलो).
	 */
#अगर 0
	/* Power Down */	
	पंचांगp = पढ़ोb(&up->regs->rw.ccr0);
	पंचांगp &= ~SAB82532_CCR0_PU;
	ग_लिखोb(पंचांगp, &up->regs->rw.ccr0);
#पूर्ण_अगर

	spin_unlock_irqrestore(&up->port.lock, flags);
	मुक्त_irq(up->port.irq, up);
पूर्ण

/*
 * This is used to figure out the भागisor speeds.
 *
 * The क्रमmula is:    Baud = SAB_BASE_BAUD / ((N + 1) * (1 << M)),
 *
 * with               0 <= N < 64 and 0 <= M < 16
 */

अटल व्योम calc_ebrg(पूर्णांक baud, पूर्णांक *n_ret, पूर्णांक *m_ret)
अणु
	पूर्णांक	n, m;

	अगर (baud == 0) अणु
		*n_ret = 0;
		*m_ret = 0;
		वापस;
	पूर्ण
     
	/*
	 * We scale numbers by 10 so that we get better accuracy
	 * without having to use भग्नing poपूर्णांक.  Here we increment m
	 * until n is within the valid range.
	 */
	n = (SAB_BASE_BAUD * 10) / baud;
	m = 0;
	जबतक (n >= 640) अणु
		n = n / 2;
		m++;
	पूर्ण
	n = (n+5) / 10;
	/*
	 * We try very hard to aव्योम speeds with M == 0 since they may
	 * not work correctly क्रम XTAL frequences above 10 MHz.
	 */
	अगर ((m == 0) && ((n & 1) == 0)) अणु
		n = n / 2;
		m++;
	पूर्ण
	*n_ret = n - 1;
	*m_ret = m;
पूर्ण

/* Internal routine, port->lock is held and local पूर्णांकerrupts are disabled.  */
अटल व्योम sunsab_convert_to_sab(काष्ठा uart_sunsab_port *up, अचिन्हित पूर्णांक cflag,
				  अचिन्हित पूर्णांक अगरlag, अचिन्हित पूर्णांक baud,
				  अचिन्हित पूर्णांक quot)
अणु
	अचिन्हित अक्षर dafo;
	पूर्णांक bits, n, m;

	/* Byte size and parity */
	चयन (cflag & CSIZE) अणु
	      हाल CS5: dafo = SAB82532_DAFO_CHL5; bits = 7; अवरोध;
	      हाल CS6: dafo = SAB82532_DAFO_CHL6; bits = 8; अवरोध;
	      हाल CS7: dafo = SAB82532_DAFO_CHL7; bits = 9; अवरोध;
	      हाल CS8: dafo = SAB82532_DAFO_CHL8; bits = 10; अवरोध;
	      /* Never happens, but GCC is too dumb to figure it out */
	      शेष:  dafo = SAB82532_DAFO_CHL5; bits = 7; अवरोध;
	पूर्ण

	अगर (cflag & CSTOPB) अणु
		dafo |= SAB82532_DAFO_STOP;
		bits++;
	पूर्ण

	अगर (cflag & PARENB) अणु
		dafo |= SAB82532_DAFO_PARE;
		bits++;
	पूर्ण

	अगर (cflag & PARODD) अणु
		dafo |= SAB82532_DAFO_PAR_ODD;
	पूर्ण अन्यथा अणु
		dafo |= SAB82532_DAFO_PAR_EVEN;
	पूर्ण
	up->cached_dafo = dafo;

	calc_ebrg(baud, &n, &m);

	up->cached_ebrg = n | (m << 6);

	up->tec_समयout = (10 * 1000000) / baud;
	up->cec_समयout = up->tec_समयout >> 2;

	/* CTS flow control flags */
	/* We encode पढ़ो_status_mask and ignore_status_mask like so:
	 *
	 * ---------------------
	 * | ... | ISR1 | ISR0 |
	 * ---------------------
	 *  ..    15   8 7    0
	 */

	up->port.पढ़ो_status_mask = (SAB82532_ISR0_TCD | SAB82532_ISR0_TIME |
				     SAB82532_ISR0_RFO | SAB82532_ISR0_RPF |
				     SAB82532_ISR0_CDSC);
	up->port.पढ़ो_status_mask |= (SAB82532_ISR1_CSC |
				      SAB82532_ISR1_ALLS |
				      SAB82532_ISR1_XPR) << 8;
	अगर (अगरlag & INPCK)
		up->port.पढ़ो_status_mask |= (SAB82532_ISR0_PERR |
					      SAB82532_ISR0_FERR);
	अगर (अगरlag & (IGNBRK | BRKINT | PARMRK))
		up->port.पढ़ो_status_mask |= (SAB82532_ISR1_BRK << 8);

	/*
	 * Characteres to ignore
	 */
	up->port.ignore_status_mask = 0;
	अगर (अगरlag & IGNPAR)
		up->port.ignore_status_mask |= (SAB82532_ISR0_PERR |
						SAB82532_ISR0_FERR);
	अगर (अगरlag & IGNBRK) अणु
		up->port.ignore_status_mask |= (SAB82532_ISR1_BRK << 8);
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (अगरlag & IGNPAR)
			up->port.ignore_status_mask |= SAB82532_ISR0_RFO;
	पूर्ण

	/*
	 * ignore all अक्षरacters अगर CREAD is not set
	 */
	अगर ((cflag & CREAD) == 0)
		up->port.ignore_status_mask |= (SAB82532_ISR0_RPF |
						SAB82532_ISR0_TCD);

	uart_update_समयout(&up->port, cflag,
			    (up->port.uartclk / (16 * quot)));

	/* Now schedule a रेजिस्टर update when the chip's
	 * transmitter is idle.
	 */
	up->cached_mode |= SAB82532_MODE_RAC;
	set_bit(SAB82532_REGS_PENDING, &up->irqflags);
	अगर (test_bit(SAB82532_XPR, &up->irqflags))
		sunsab_tx_idle(up);
पूर्ण

/* port->lock is not held.  */
अटल व्योम sunsab_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
			       काष्ठा ktermios *old)
अणु
	काष्ठा uart_sunsab_port *up =
		container_of(port, काष्ठा uart_sunsab_port, port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud = uart_get_baud_rate(port, termios, old, 0, 4000000);
	अचिन्हित पूर्णांक quot = uart_get_भागisor(port, baud);

	spin_lock_irqsave(&up->port.lock, flags);
	sunsab_convert_to_sab(up, termios->c_cflag, termios->c_अगरlag, baud, quot);
	spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

अटल स्थिर अक्षर *sunsab_type(काष्ठा uart_port *port)
अणु
	काष्ठा uart_sunsab_port *up = (व्योम *)port;
	अटल अक्षर buf[36];
	
	प्र_लिखो(buf, "SAB82532 %s", sab82532_version[up->type]);
	वापस buf;
पूर्ण

अटल व्योम sunsab_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक sunsab_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम sunsab_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
पूर्ण

अटल पूर्णांक sunsab_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा uart_ops sunsab_pops = अणु
	.tx_empty	= sunsab_tx_empty,
	.set_mctrl	= sunsab_set_mctrl,
	.get_mctrl	= sunsab_get_mctrl,
	.stop_tx	= sunsab_stop_tx,
	.start_tx	= sunsab_start_tx,
	.send_xअक्षर	= sunsab_send_xअक्षर,
	.stop_rx	= sunsab_stop_rx,
	.अवरोध_ctl	= sunsab_अवरोध_ctl,
	.startup	= sunsab_startup,
	.shutकरोwn	= sunsab_shutकरोwn,
	.set_termios	= sunsab_set_termios,
	.type		= sunsab_type,
	.release_port	= sunsab_release_port,
	.request_port	= sunsab_request_port,
	.config_port	= sunsab_config_port,
	.verअगरy_port	= sunsab_verअगरy_port,
पूर्ण;

अटल काष्ठा uart_driver sunsab_reg = अणु
	.owner			= THIS_MODULE,
	.driver_name		= "sunsab",
	.dev_name		= "ttyS",
	.major			= TTY_MAJOR,
पूर्ण;

अटल काष्ठा uart_sunsab_port *sunsab_ports;

#अगर_घोषित CONFIG_SERIAL_SUNSAB_CONSOLE

अटल व्योम sunsab_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	काष्ठा uart_sunsab_port *up =
		container_of(port, काष्ठा uart_sunsab_port, port);

	sunsab_tec_रुको(up);
	ग_लिखोb(c, &up->regs->w.tic);
पूर्ण

अटल व्योम sunsab_console_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित n)
अणु
	काष्ठा uart_sunsab_port *up = &sunsab_ports[con->index];
	अचिन्हित दीर्घ flags;
	पूर्णांक locked = 1;

	अगर (up->port.sysrq || oops_in_progress)
		locked = spin_trylock_irqsave(&up->port.lock, flags);
	अन्यथा
		spin_lock_irqsave(&up->port.lock, flags);

	uart_console_ग_लिखो(&up->port, s, n, sunsab_console_अक्षर_दो);
	sunsab_tec_रुको(up);

	अगर (locked)
		spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

अटल पूर्णांक sunsab_console_setup(काष्ठा console *con, अक्षर *options)
अणु
	काष्ठा uart_sunsab_port *up = &sunsab_ports[con->index];
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, quot;

	/*
	 * The console framework calls us क्रम each and every port
	 * रेजिस्टरed. Defer the console setup until the requested
	 * port has been properly discovered. A bit of a hack,
	 * though...
	 */
	अगर (up->port.type != PORT_SUNSAB)
		वापस -EINVAL;

	prपूर्णांकk("Console: ttyS%d (SAB82532)\n",
	       (sunsab_reg.minor - 64) + con->index);

	sunserial_console_termios(con, up->port.dev->of_node);

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
	हाल B57600: baud = 57600; अवरोध;
	हाल B115200: baud = 115200; अवरोध;
	हाल B230400: baud = 230400; अवरोध;
	हाल B460800: baud = 460800; अवरोध;
	पूर्ण

	/*
	 * Temporary fix.
	 */
	spin_lock_init(&up->port.lock);

	/*
	 * Initialize the hardware
	 */
	sunsab_startup(&up->port);

	spin_lock_irqsave(&up->port.lock, flags);

	/*
	 * Finally, enable पूर्णांकerrupts
	 */
	up->पूर्णांकerrupt_mask0 = SAB82532_IMR0_PERR | SAB82532_IMR0_FERR |
				SAB82532_IMR0_PLLA | SAB82532_IMR0_CDSC;
	ग_लिखोb(up->पूर्णांकerrupt_mask0, &up->regs->w.imr0);
	up->पूर्णांकerrupt_mask1 = SAB82532_IMR1_BRKT | SAB82532_IMR1_ALLS |
				SAB82532_IMR1_XOFF | SAB82532_IMR1_TIN |
				SAB82532_IMR1_CSC | SAB82532_IMR1_XON |
				SAB82532_IMR1_XPR;
	ग_लिखोb(up->पूर्णांकerrupt_mask1, &up->regs->w.imr1);

	quot = uart_get_भागisor(&up->port, baud);
	sunsab_convert_to_sab(up, con->cflag, 0, baud, quot);
	sunsab_set_mctrl(&up->port, TIOCM_DTR | TIOCM_RTS);

	spin_unlock_irqrestore(&up->port.lock, flags);
	
	वापस 0;
पूर्ण

अटल काष्ठा console sunsab_console = अणु
	.name	=	"ttyS",
	.ग_लिखो	=	sunsab_console_ग_लिखो,
	.device	=	uart_console_device,
	.setup	=	sunsab_console_setup,
	.flags	=	CON_PRINTBUFFER,
	.index	=	-1,
	.data	=	&sunsab_reg,
पूर्ण;

अटल अंतरभूत काष्ठा console *SUNSAB_CONSOLE(व्योम)
अणु
	वापस &sunsab_console;
पूर्ण
#अन्यथा
#घोषणा SUNSAB_CONSOLE()	(शून्य)
#घोषणा sunsab_console_init()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल पूर्णांक sunsab_init_one(काष्ठा uart_sunsab_port *up,
				     काष्ठा platक्रमm_device *op,
				     अचिन्हित दीर्घ offset,
				     पूर्णांक line)
अणु
	up->port.line = line;
	up->port.dev = &op->dev;

	up->port.mapbase = op->resource[0].start + offset;
	up->port.membase = of_ioremap(&op->resource[0], offset,
				      माप(जोड़ sab82532_async_regs),
				      "sab");
	अगर (!up->port.membase)
		वापस -ENOMEM;
	up->regs = (जोड़ sab82532_async_regs __iomem *) up->port.membase;

	up->port.irq = op->archdata.irqs[0];

	up->port.fअगरosize = SAB82532_XMIT_FIFO_SIZE;
	up->port.iotype = UPIO_MEM;
	up->port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_SUNSAB_CONSOLE);

	ग_लिखोb(SAB82532_IPC_IC_ACT_LOW, &up->regs->w.ipc);

	up->port.ops = &sunsab_pops;
	up->port.type = PORT_SUNSAB;
	up->port.uartclk = SAB_BASE_BAUD;

	up->type = पढ़ोb(&up->regs->r.vstr) & 0x0f;
	ग_लिखोb(~((1 << 1) | (1 << 2) | (1 << 4)), &up->regs->w.pcr);
	ग_लिखोb(0xff, &up->regs->w.pim);
	अगर ((up->port.line & 0x1) == 0) अणु
		up->pvr_dsr_bit = (1 << 0);
		up->pvr_dtr_bit = (1 << 1);
		up->gis_shअगरt = 2;
	पूर्ण अन्यथा अणु
		up->pvr_dsr_bit = (1 << 3);
		up->pvr_dtr_bit = (1 << 2);
		up->gis_shअगरt = 0;
	पूर्ण
	up->cached_pvr = (1 << 1) | (1 << 2) | (1 << 4);
	ग_लिखोb(up->cached_pvr, &up->regs->w.pvr);
	up->cached_mode = पढ़ोb(&up->regs->rw.mode);
	up->cached_mode |= SAB82532_MODE_FRTS;
	ग_लिखोb(up->cached_mode, &up->regs->rw.mode);
	up->cached_mode |= SAB82532_MODE_RTS;
	ग_लिखोb(up->cached_mode, &up->regs->rw.mode);

	up->tec_समयout = SAB82532_MAX_TEC_TIMEOUT;
	up->cec_समयout = SAB82532_MAX_CEC_TIMEOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक sab_probe(काष्ठा platक्रमm_device *op)
अणु
	अटल पूर्णांक inst;
	काष्ठा uart_sunsab_port *up;
	पूर्णांक err;

	up = &sunsab_ports[inst * 2];

	err = sunsab_init_one(&up[0], op,
			      0,
			      (inst * 2) + 0);
	अगर (err)
		जाओ out;

	err = sunsab_init_one(&up[1], op,
			      माप(जोड़ sab82532_async_regs),
			      (inst * 2) + 1);
	अगर (err)
		जाओ out1;

	sunserial_console_match(SUNSAB_CONSOLE(), op->dev.of_node,
				&sunsab_reg, up[0].port.line,
				false);

	sunserial_console_match(SUNSAB_CONSOLE(), op->dev.of_node,
				&sunsab_reg, up[1].port.line,
				false);

	err = uart_add_one_port(&sunsab_reg, &up[0].port);
	अगर (err)
		जाओ out2;

	err = uart_add_one_port(&sunsab_reg, &up[1].port);
	अगर (err)
		जाओ out3;

	platक्रमm_set_drvdata(op, &up[0]);

	inst++;

	वापस 0;

out3:
	uart_हटाओ_one_port(&sunsab_reg, &up[0].port);
out2:
	of_iounmap(&op->resource[0],
		   up[1].port.membase,
		   माप(जोड़ sab82532_async_regs));
out1:
	of_iounmap(&op->resource[0],
		   up[0].port.membase,
		   माप(जोड़ sab82532_async_regs));
out:
	वापस err;
पूर्ण

अटल पूर्णांक sab_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा uart_sunsab_port *up = platक्रमm_get_drvdata(op);

	uart_हटाओ_one_port(&sunsab_reg, &up[1].port);
	uart_हटाओ_one_port(&sunsab_reg, &up[0].port);
	of_iounmap(&op->resource[0],
		   up[1].port.membase,
		   माप(जोड़ sab82532_async_regs));
	of_iounmap(&op->resource[0],
		   up[0].port.membase,
		   माप(जोड़ sab82532_async_regs));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sab_match[] = अणु
	अणु
		.name = "se",
	पूर्ण,
	अणु
		.name = "serial",
		.compatible = "sab82532",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sab_match);

अटल काष्ठा platक्रमm_driver sab_driver = अणु
	.driver = अणु
		.name = "sab",
		.of_match_table = sab_match,
	पूर्ण,
	.probe		= sab_probe,
	.हटाओ		= sab_हटाओ,
पूर्ण;

अटल पूर्णांक __init sunsab_init(व्योम)
अणु
	काष्ठा device_node *dp;
	पूर्णांक err;
	पूर्णांक num_channels = 0;

	क्रम_each_node_by_name(dp, "se")
		num_channels += 2;
	क्रम_each_node_by_name(dp, "serial") अणु
		अगर (of_device_is_compatible(dp, "sab82532"))
			num_channels += 2;
	पूर्ण

	अगर (num_channels) अणु
		sunsab_ports = kसुस्मृति(num_channels,
				       माप(काष्ठा uart_sunsab_port),
				       GFP_KERNEL);
		अगर (!sunsab_ports)
			वापस -ENOMEM;

		err = sunserial_रेजिस्टर_minors(&sunsab_reg, num_channels);
		अगर (err) अणु
			kमुक्त(sunsab_ports);
			sunsab_ports = शून्य;

			वापस err;
		पूर्ण
	पूर्ण

	वापस platक्रमm_driver_रेजिस्टर(&sab_driver);
पूर्ण

अटल व्योम __निकास sunsab_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sab_driver);
	अगर (sunsab_reg.nr) अणु
		sunserial_unरेजिस्टर_minors(&sunsab_reg, sunsab_reg.nr);
	पूर्ण

	kमुक्त(sunsab_ports);
	sunsab_ports = शून्य;
पूर्ण

module_init(sunsab_init);
module_निकास(sunsab_निकास);

MODULE_AUTHOR("Eddie C. Dost and David S. Miller");
MODULE_DESCRIPTION("Sun SAB82532 serial port driver");
MODULE_LICENSE("GPL");
