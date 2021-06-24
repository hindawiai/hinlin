<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	Support क्रम the asynchronous serial पूर्णांकerface (DUART) included
 *	in the BCM1250 and derived System-On-a-Chip (SOC) devices.
 *
 *	Copyright (c) 2007  Maciej W. Rozycki
 *
 *	Derived from drivers/अक्षर/sb1250_duart.c क्रम which the following
 *	copyright applies:
 *
 *	Copyright (c) 2000, 2001, 2002, 2003, 2004  Broadcom Corporation
 *
 *	References:
 *
 *	"BCM1250/BCM1125/BCM1125H User Manual", Broadcom Corporation
 */

#समावेश <linux/compiler.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/major.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/types.h>

#समावेश <linux/refcount.h>
#समावेश <यंत्र/पन.स>

#समावेश <यंत्र/sibyte/sb1250.h>
#समावेश <यंत्र/sibyte/sb1250_uart.h>
#समावेश <यंत्र/sibyte/swarm.h>


#अगर defined(CONFIG_SIBYTE_BCM1x55) || defined(CONFIG_SIBYTE_BCM1x80)
#समावेश <यंत्र/sibyte/bcm1480_regs.h>
#समावेश <यंत्र/sibyte/bcm1480_पूर्णांक.h>

#घोषणा SBD_CHANREGS(line)	A_BCM1480_DUART_CHANREG((line), 0)
#घोषणा SBD_CTRLREGS(line)	A_BCM1480_DUART_CTRLREG((line), 0)
#घोषणा SBD_INT(line)		(K_BCM1480_INT_UART_0 + (line))

#घोषणा DUART_CHANREG_SPACING	BCM1480_DUART_CHANREG_SPACING

#घोषणा R_DUART_IMRREG(line)	R_BCM1480_DUART_IMRREG(line)
#घोषणा R_DUART_INCHREG(line)	R_BCM1480_DUART_INCHREG(line)
#घोषणा R_DUART_ISRREG(line)	R_BCM1480_DUART_ISRREG(line)

#या_अगर defined(CONFIG_SIBYTE_SB1250) || defined(CONFIG_SIBYTE_BCM112X)
#समावेश <यंत्र/sibyte/sb1250_regs.h>
#समावेश <यंत्र/sibyte/sb1250_पूर्णांक.h>

#घोषणा SBD_CHANREGS(line)	A_DUART_CHANREG((line), 0)
#घोषणा SBD_CTRLREGS(line)	A_DUART_CTRLREG(0)
#घोषणा SBD_INT(line)		(K_INT_UART_0 + (line))

#अन्यथा
#त्रुटि invalid SB1250 UART configuration

#पूर्ण_अगर


MODULE_AUTHOR("Maciej W. Rozycki <macro@linux-mips.org>");
MODULE_DESCRIPTION("BCM1xxx on-chip DUART serial driver");
MODULE_LICENSE("GPL");


#घोषणा DUART_MAX_CHIP 2
#घोषणा DUART_MAX_SIDE 2

/*
 * Per-port state.
 */
काष्ठा sbd_port अणु
	काष्ठा sbd_duart	*duart;
	काष्ठा uart_port	port;
	अचिन्हित अक्षर __iomem	*memctrl;
	पूर्णांक			tx_stopped;
	पूर्णांक			initialised;
पूर्ण;

/*
 * Per-DUART state क्रम the shared रेजिस्टर space.
 */
काष्ठा sbd_duart अणु
	काष्ठा sbd_port		sport[2];
	अचिन्हित दीर्घ		mapctrl;
	refcount_t		map_guard;
पूर्ण;

#घोषणा to_sport(uport) container_of(uport, काष्ठा sbd_port, port)

अटल काष्ठा sbd_duart sbd_duarts[DUART_MAX_CHIP];


/*
 * Reading and writing SB1250 DUART रेजिस्टरs.
 *
 * There are three रेजिस्टर spaces: two per-channel ones and
 * a shared one.  We have to define accessors appropriately.
 * All रेजिस्टरs are 64-bit and all but the Baud Rate Clock
 * रेजिस्टरs only define 8 least signअगरicant bits.  There is
 * also a workaround to take पूर्णांकo account.  Raw accessors use
 * the full रेजिस्टर width, but cooked ones truncate it
 * पूर्णांकentionally so that the rest of the driver करोes not care.
 */
अटल u64 __पढ़ो_sbdchn(काष्ठा sbd_port *sport, पूर्णांक reg)
अणु
	व्योम __iomem *csr = sport->port.membase + reg;

	वापस __raw_पढ़ोq(csr);
पूर्ण

अटल u64 __पढ़ो_sbdshr(काष्ठा sbd_port *sport, पूर्णांक reg)
अणु
	व्योम __iomem *csr = sport->memctrl + reg;

	वापस __raw_पढ़ोq(csr);
पूर्ण

अटल व्योम __ग_लिखो_sbdchn(काष्ठा sbd_port *sport, पूर्णांक reg, u64 value)
अणु
	व्योम __iomem *csr = sport->port.membase + reg;

	__raw_ग_लिखोq(value, csr);
पूर्ण

अटल व्योम __ग_लिखो_sbdshr(काष्ठा sbd_port *sport, पूर्णांक reg, u64 value)
अणु
	व्योम __iomem *csr = sport->memctrl + reg;

	__raw_ग_लिखोq(value, csr);
पूर्ण

/*
 * In bug 1956, we get glitches that can mess up uart रेजिस्टरs.  This
 * "read-mode-reg after any register access" is an accepted workaround.
 */
अटल व्योम __war_sbd1956(काष्ठा sbd_port *sport)
अणु
	__पढ़ो_sbdchn(sport, R_DUART_MODE_REG_1);
	__पढ़ो_sbdchn(sport, R_DUART_MODE_REG_2);
पूर्ण

अटल अचिन्हित अक्षर पढ़ो_sbdchn(काष्ठा sbd_port *sport, पूर्णांक reg)
अणु
	अचिन्हित अक्षर retval;

	retval = __पढ़ो_sbdchn(sport, reg);
	अगर (IS_ENABLED(CONFIG_SB1_PASS_2_WORKAROUNDS))
		__war_sbd1956(sport);
	वापस retval;
पूर्ण

अटल अचिन्हित अक्षर पढ़ो_sbdshr(काष्ठा sbd_port *sport, पूर्णांक reg)
अणु
	अचिन्हित अक्षर retval;

	retval = __पढ़ो_sbdshr(sport, reg);
	अगर (IS_ENABLED(CONFIG_SB1_PASS_2_WORKAROUNDS))
		__war_sbd1956(sport);
	वापस retval;
पूर्ण

अटल व्योम ग_लिखो_sbdchn(काष्ठा sbd_port *sport, पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	__ग_लिखो_sbdchn(sport, reg, value);
	अगर (IS_ENABLED(CONFIG_SB1_PASS_2_WORKAROUNDS))
		__war_sbd1956(sport);
पूर्ण

अटल व्योम ग_लिखो_sbdshr(काष्ठा sbd_port *sport, पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	__ग_लिखो_sbdshr(sport, reg, value);
	अगर (IS_ENABLED(CONFIG_SB1_PASS_2_WORKAROUNDS))
		__war_sbd1956(sport);
पूर्ण


अटल पूर्णांक sbd_receive_पढ़ोy(काष्ठा sbd_port *sport)
अणु
	वापस पढ़ो_sbdchn(sport, R_DUART_STATUS) & M_DUART_RX_RDY;
पूर्ण

अटल पूर्णांक sbd_receive_drain(काष्ठा sbd_port *sport)
अणु
	पूर्णांक loops = 10000;

	जबतक (sbd_receive_पढ़ोy(sport) && --loops)
		पढ़ो_sbdchn(sport, R_DUART_RX_HOLD);
	वापस loops;
पूर्ण

अटल पूर्णांक __maybe_unused sbd_transmit_पढ़ोy(काष्ठा sbd_port *sport)
अणु
	वापस पढ़ो_sbdchn(sport, R_DUART_STATUS) & M_DUART_TX_RDY;
पूर्ण

अटल पूर्णांक __maybe_unused sbd_transmit_drain(काष्ठा sbd_port *sport)
अणु
	पूर्णांक loops = 10000;

	जबतक (!sbd_transmit_पढ़ोy(sport) && --loops)
		udelay(2);
	वापस loops;
पूर्ण

अटल पूर्णांक sbd_transmit_empty(काष्ठा sbd_port *sport)
अणु
	वापस पढ़ो_sbdchn(sport, R_DUART_STATUS) & M_DUART_TX_EMT;
पूर्ण

अटल पूर्णांक sbd_line_drain(काष्ठा sbd_port *sport)
अणु
	पूर्णांक loops = 10000;

	जबतक (!sbd_transmit_empty(sport) && --loops)
		udelay(2);
	वापस loops;
पूर्ण


अटल अचिन्हित पूर्णांक sbd_tx_empty(काष्ठा uart_port *uport)
अणु
	काष्ठा sbd_port *sport = to_sport(uport);

	वापस sbd_transmit_empty(sport) ? TIOCSER_TEMT : 0;
पूर्ण

अटल अचिन्हित पूर्णांक sbd_get_mctrl(काष्ठा uart_port *uport)
अणु
	काष्ठा sbd_port *sport = to_sport(uport);
	अचिन्हित पूर्णांक mctrl, status;

	status = पढ़ो_sbdshr(sport, R_DUART_IN_PORT);
	status >>= (uport->line) % 2;
	mctrl = (!(status & M_DUART_IN_PIN0_VAL) ? TIOCM_CTS : 0) |
		(!(status & M_DUART_IN_PIN4_VAL) ? TIOCM_CAR : 0) |
		(!(status & M_DUART_RIN0_PIN) ? TIOCM_RNG : 0) |
		(!(status & M_DUART_IN_PIN2_VAL) ? TIOCM_DSR : 0);
	वापस mctrl;
पूर्ण

अटल व्योम sbd_set_mctrl(काष्ठा uart_port *uport, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा sbd_port *sport = to_sport(uport);
	अचिन्हित पूर्णांक clr = 0, set = 0, mode2;

	अगर (mctrl & TIOCM_DTR)
		set |= M_DUART_SET_OPR2;
	अन्यथा
		clr |= M_DUART_CLR_OPR2;
	अगर (mctrl & TIOCM_RTS)
		set |= M_DUART_SET_OPR0;
	अन्यथा
		clr |= M_DUART_CLR_OPR0;
	clr <<= (uport->line) % 2;
	set <<= (uport->line) % 2;

	mode2 = पढ़ो_sbdchn(sport, R_DUART_MODE_REG_2);
	mode2 &= ~M_DUART_CHAN_MODE;
	अगर (mctrl & TIOCM_LOOP)
		mode2 |= V_DUART_CHAN_MODE_LCL_LOOP;
	अन्यथा
		mode2 |= V_DUART_CHAN_MODE_NORMAL;

	ग_लिखो_sbdshr(sport, R_DUART_CLEAR_OPR, clr);
	ग_लिखो_sbdshr(sport, R_DUART_SET_OPR, set);
	ग_लिखो_sbdchn(sport, R_DUART_MODE_REG_2, mode2);
पूर्ण

अटल व्योम sbd_stop_tx(काष्ठा uart_port *uport)
अणु
	काष्ठा sbd_port *sport = to_sport(uport);

	ग_लिखो_sbdchn(sport, R_DUART_CMD, M_DUART_TX_DIS);
	sport->tx_stopped = 1;
पूर्ण;

अटल व्योम sbd_start_tx(काष्ठा uart_port *uport)
अणु
	काष्ठा sbd_port *sport = to_sport(uport);
	अचिन्हित पूर्णांक mask;

	/* Enable tx पूर्णांकerrupts.  */
	mask = पढ़ो_sbdshr(sport, R_DUART_IMRREG((uport->line) % 2));
	mask |= M_DUART_IMR_TX;
	ग_लिखो_sbdshr(sport, R_DUART_IMRREG((uport->line) % 2), mask);

	/* Go!, go!, go!...  */
	ग_लिखो_sbdchn(sport, R_DUART_CMD, M_DUART_TX_EN);
	sport->tx_stopped = 0;
पूर्ण;

अटल व्योम sbd_stop_rx(काष्ठा uart_port *uport)
अणु
	काष्ठा sbd_port *sport = to_sport(uport);

	ग_लिखो_sbdshr(sport, R_DUART_IMRREG((uport->line) % 2), 0);
पूर्ण;

अटल व्योम sbd_enable_ms(काष्ठा uart_port *uport)
अणु
	काष्ठा sbd_port *sport = to_sport(uport);

	ग_लिखो_sbdchn(sport, R_DUART_AUXCTL_X,
		     M_DUART_CIN_CHNG_ENA | M_DUART_CTS_CHNG_ENA);
पूर्ण

अटल व्योम sbd_अवरोध_ctl(काष्ठा uart_port *uport, पूर्णांक अवरोध_state)
अणु
	काष्ठा sbd_port *sport = to_sport(uport);

	अगर (अवरोध_state == -1)
		ग_लिखो_sbdchn(sport, R_DUART_CMD, V_DUART_MISC_CMD_START_BREAK);
	अन्यथा
		ग_लिखो_sbdchn(sport, R_DUART_CMD, V_DUART_MISC_CMD_STOP_BREAK);
पूर्ण


अटल व्योम sbd_receive_अक्षरs(काष्ठा sbd_port *sport)
अणु
	काष्ठा uart_port *uport = &sport->port;
	काष्ठा uart_icount *icount;
	अचिन्हित पूर्णांक status, ch, flag;
	पूर्णांक count;

	क्रम (count = 16; count; count--) अणु
		status = पढ़ो_sbdchn(sport, R_DUART_STATUS);
		अगर (!(status & M_DUART_RX_RDY))
			अवरोध;

		ch = पढ़ो_sbdchn(sport, R_DUART_RX_HOLD);

		flag = TTY_NORMAL;

		icount = &uport->icount;
		icount->rx++;

		अगर (unlikely(status &
			     (M_DUART_RCVD_BRK | M_DUART_FRM_ERR |
			      M_DUART_PARITY_ERR | M_DUART_OVRUN_ERR))) अणु
			अगर (status & M_DUART_RCVD_BRK) अणु
				icount->brk++;
				अगर (uart_handle_अवरोध(uport))
					जारी;
			पूर्ण अन्यथा अगर (status & M_DUART_FRM_ERR)
				icount->frame++;
			अन्यथा अगर (status & M_DUART_PARITY_ERR)
				icount->parity++;
			अगर (status & M_DUART_OVRUN_ERR)
				icount->overrun++;

			status &= uport->पढ़ो_status_mask;
			अगर (status & M_DUART_RCVD_BRK)
				flag = TTY_BREAK;
			अन्यथा अगर (status & M_DUART_FRM_ERR)
				flag = TTY_FRAME;
			अन्यथा अगर (status & M_DUART_PARITY_ERR)
				flag = TTY_PARITY;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(uport, ch))
			जारी;

		uart_insert_अक्षर(uport, status, M_DUART_OVRUN_ERR, ch, flag);
	पूर्ण

	tty_flip_buffer_push(&uport->state->port);
पूर्ण

अटल व्योम sbd_transmit_अक्षरs(काष्ठा sbd_port *sport)
अणु
	काष्ठा uart_port *uport = &sport->port;
	काष्ठा circ_buf *xmit = &sport->port.state->xmit;
	अचिन्हित पूर्णांक mask;
	पूर्णांक stop_tx;

	/* XON/XOFF अक्षरs.  */
	अगर (sport->port.x_अक्षर) अणु
		ग_लिखो_sbdchn(sport, R_DUART_TX_HOLD, sport->port.x_अक्षर);
		sport->port.icount.tx++;
		sport->port.x_अक्षर = 0;
		वापस;
	पूर्ण

	/* If nothing to करो or stopped or hardware stopped.  */
	stop_tx = (uart_circ_empty(xmit) || uart_tx_stopped(&sport->port));

	/* Send अक्षर.  */
	अगर (!stop_tx) अणु
		ग_लिखो_sbdchn(sport, R_DUART_TX_HOLD, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		sport->port.icount.tx++;

		अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
			uart_ग_लिखो_wakeup(&sport->port);
	पूर्ण

	/* Are we are करोne?  */
	अगर (stop_tx || uart_circ_empty(xmit)) अणु
		/* Disable tx पूर्णांकerrupts.  */
		mask = पढ़ो_sbdshr(sport, R_DUART_IMRREG((uport->line) % 2));
		mask &= ~M_DUART_IMR_TX;
		ग_लिखो_sbdshr(sport, R_DUART_IMRREG((uport->line) % 2), mask);
	पूर्ण
पूर्ण

अटल व्योम sbd_status_handle(काष्ठा sbd_port *sport)
अणु
	काष्ठा uart_port *uport = &sport->port;
	अचिन्हित पूर्णांक delta;

	delta = पढ़ो_sbdshr(sport, R_DUART_INCHREG((uport->line) % 2));
	delta >>= (uport->line) % 2;

	अगर (delta & (M_DUART_IN_PIN0_VAL << S_DUART_IN_PIN_CHNG))
		uart_handle_cts_change(uport, !(delta & M_DUART_IN_PIN0_VAL));

	अगर (delta & (M_DUART_IN_PIN2_VAL << S_DUART_IN_PIN_CHNG))
		uport->icount.dsr++;

	अगर (delta & ((M_DUART_IN_PIN2_VAL | M_DUART_IN_PIN0_VAL) <<
		     S_DUART_IN_PIN_CHNG))
		wake_up_पूर्णांकerruptible(&uport->state->port.delta_msr_रुको);
पूर्ण

अटल irqवापस_t sbd_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sbd_port *sport = dev_id;
	काष्ठा uart_port *uport = &sport->port;
	irqवापस_t status = IRQ_NONE;
	अचिन्हित पूर्णांक पूर्णांकstat;
	पूर्णांक count;

	क्रम (count = 16; count; count--) अणु
		पूर्णांकstat = पढ़ो_sbdshr(sport,
				      R_DUART_ISRREG((uport->line) % 2));
		पूर्णांकstat &= पढ़ो_sbdshr(sport,
				       R_DUART_IMRREG((uport->line) % 2));
		पूर्णांकstat &= M_DUART_ISR_ALL;
		अगर (!पूर्णांकstat)
			अवरोध;

		अगर (पूर्णांकstat & M_DUART_ISR_RX)
			sbd_receive_अक्षरs(sport);
		अगर (पूर्णांकstat & M_DUART_ISR_IN)
			sbd_status_handle(sport);
		अगर (पूर्णांकstat & M_DUART_ISR_TX)
			sbd_transmit_अक्षरs(sport);

		status = IRQ_HANDLED;
	पूर्ण

	वापस status;
पूर्ण


अटल पूर्णांक sbd_startup(काष्ठा uart_port *uport)
अणु
	काष्ठा sbd_port *sport = to_sport(uport);
	अचिन्हित पूर्णांक mode1;
	पूर्णांक ret;

	ret = request_irq(sport->port.irq, sbd_पूर्णांकerrupt,
			  IRQF_SHARED, "sb1250-duart", sport);
	अगर (ret)
		वापस ret;

	/* Clear the receive FIFO.  */
	sbd_receive_drain(sport);

	/* Clear the पूर्णांकerrupt रेजिस्टरs.  */
	ग_लिखो_sbdchn(sport, R_DUART_CMD, V_DUART_MISC_CMD_RESET_BREAK_INT);
	पढ़ो_sbdshr(sport, R_DUART_INCHREG((uport->line) % 2));

	/* Set rx/tx पूर्णांकerrupt to FIFO available.  */
	mode1 = पढ़ो_sbdchn(sport, R_DUART_MODE_REG_1);
	mode1 &= ~(M_DUART_RX_IRQ_SEL_RXFULL | M_DUART_TX_IRQ_SEL_TXEMPT);
	ग_लिखो_sbdchn(sport, R_DUART_MODE_REG_1, mode1);

	/* Disable tx, enable rx.  */
	ग_लिखो_sbdchn(sport, R_DUART_CMD, M_DUART_TX_DIS | M_DUART_RX_EN);
	sport->tx_stopped = 1;

	/* Enable पूर्णांकerrupts.  */
	ग_लिखो_sbdshr(sport, R_DUART_IMRREG((uport->line) % 2),
		     M_DUART_IMR_IN | M_DUART_IMR_RX);

	वापस 0;
पूर्ण

अटल व्योम sbd_shutकरोwn(काष्ठा uart_port *uport)
अणु
	काष्ठा sbd_port *sport = to_sport(uport);

	ग_लिखो_sbdchn(sport, R_DUART_CMD, M_DUART_TX_DIS | M_DUART_RX_DIS);
	sport->tx_stopped = 1;
	मुक्त_irq(sport->port.irq, sport);
पूर्ण


अटल व्योम sbd_init_port(काष्ठा sbd_port *sport)
अणु
	काष्ठा uart_port *uport = &sport->port;

	अगर (sport->initialised)
		वापस;

	/* There is no DUART reset feature, so just set some sane शेषs.  */
	ग_लिखो_sbdchn(sport, R_DUART_CMD, V_DUART_MISC_CMD_RESET_TX);
	ग_लिखो_sbdchn(sport, R_DUART_CMD, V_DUART_MISC_CMD_RESET_RX);
	ग_लिखो_sbdchn(sport, R_DUART_MODE_REG_1, V_DUART_BITS_PER_CHAR_8);
	ग_लिखो_sbdchn(sport, R_DUART_MODE_REG_2, 0);
	ग_लिखो_sbdchn(sport, R_DUART_FULL_CTL,
		     V_DUART_INT_TIME(0) | V_DUART_SIG_FULL(15));
	ग_लिखो_sbdchn(sport, R_DUART_OPCR_X, 0);
	ग_लिखो_sbdchn(sport, R_DUART_AUXCTL_X, 0);
	ग_लिखो_sbdshr(sport, R_DUART_IMRREG((uport->line) % 2), 0);

	sport->initialised = 1;
पूर्ण

अटल व्योम sbd_set_termios(काष्ठा uart_port *uport, काष्ठा ktermios *termios,
			    काष्ठा ktermios *old_termios)
अणु
	काष्ठा sbd_port *sport = to_sport(uport);
	अचिन्हित पूर्णांक mode1 = 0, mode2 = 0, aux = 0;
	अचिन्हित पूर्णांक mode1mask = 0, mode2mask = 0, auxmask = 0;
	अचिन्हित पूर्णांक oldmode1, oldmode2, oldaux;
	अचिन्हित पूर्णांक baud, brg;
	अचिन्हित पूर्णांक command;

	mode1mask |= ~(M_DUART_PARITY_MODE | M_DUART_PARITY_TYPE_ODD |
		       M_DUART_BITS_PER_CHAR);
	mode2mask |= ~M_DUART_STOP_BIT_LEN_2;
	auxmask |= ~M_DUART_CTS_CHNG_ENA;

	/* Byte size.  */
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
	हाल CS6:
		/* Unsupported, leave unchanged.  */
		mode1mask |= M_DUART_PARITY_MODE;
		अवरोध;
	हाल CS7:
		mode1 |= V_DUART_BITS_PER_CHAR_7;
		अवरोध;
	हाल CS8:
	शेष:
		mode1 |= V_DUART_BITS_PER_CHAR_8;
		अवरोध;
	पूर्ण

	/* Parity and stop bits.  */
	अगर (termios->c_cflag & CSTOPB)
		mode2 |= M_DUART_STOP_BIT_LEN_2;
	अन्यथा
		mode2 |= M_DUART_STOP_BIT_LEN_1;
	अगर (termios->c_cflag & PARENB)
		mode1 |= V_DUART_PARITY_MODE_ADD;
	अन्यथा
		mode1 |= V_DUART_PARITY_MODE_NONE;
	अगर (termios->c_cflag & PARODD)
		mode1 |= M_DUART_PARITY_TYPE_ODD;
	अन्यथा
		mode1 |= M_DUART_PARITY_TYPE_EVEN;

	baud = uart_get_baud_rate(uport, termios, old_termios, 1200, 5000000);
	brg = V_DUART_BAUD_RATE(baud);
	/* The actual lower bound is 1221bps, so compensate.  */
	अगर (brg > M_DUART_CLK_COUNTER)
		brg = M_DUART_CLK_COUNTER;

	uart_update_समयout(uport, termios->c_cflag, baud);

	uport->पढ़ो_status_mask = M_DUART_OVRUN_ERR;
	अगर (termios->c_अगरlag & INPCK)
		uport->पढ़ो_status_mask |= M_DUART_FRM_ERR |
					   M_DUART_PARITY_ERR;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		uport->पढ़ो_status_mask |= M_DUART_RCVD_BRK;

	uport->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		uport->ignore_status_mask |= M_DUART_FRM_ERR |
					     M_DUART_PARITY_ERR;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		uport->ignore_status_mask |= M_DUART_RCVD_BRK;
		अगर (termios->c_अगरlag & IGNPAR)
			uport->ignore_status_mask |= M_DUART_OVRUN_ERR;
	पूर्ण

	अगर (termios->c_cflag & CREAD)
		command = M_DUART_RX_EN;
	अन्यथा
		command = M_DUART_RX_DIS;

	अगर (termios->c_cflag & CRTSCTS)
		aux |= M_DUART_CTS_CHNG_ENA;
	अन्यथा
		aux &= ~M_DUART_CTS_CHNG_ENA;

	spin_lock(&uport->lock);

	अगर (sport->tx_stopped)
		command |= M_DUART_TX_DIS;
	अन्यथा
		command |= M_DUART_TX_EN;

	oldmode1 = पढ़ो_sbdchn(sport, R_DUART_MODE_REG_1) & mode1mask;
	oldmode2 = पढ़ो_sbdchn(sport, R_DUART_MODE_REG_2) & mode2mask;
	oldaux = पढ़ो_sbdchn(sport, R_DUART_AUXCTL_X) & auxmask;

	अगर (!sport->tx_stopped)
		sbd_line_drain(sport);
	ग_लिखो_sbdchn(sport, R_DUART_CMD, M_DUART_TX_DIS | M_DUART_RX_DIS);

	ग_लिखो_sbdchn(sport, R_DUART_MODE_REG_1, mode1 | oldmode1);
	ग_लिखो_sbdchn(sport, R_DUART_MODE_REG_2, mode2 | oldmode2);
	ग_लिखो_sbdchn(sport, R_DUART_CLK_SEL, brg);
	ग_लिखो_sbdchn(sport, R_DUART_AUXCTL_X, aux | oldaux);

	ग_लिखो_sbdchn(sport, R_DUART_CMD, command);

	spin_unlock(&uport->lock);
पूर्ण


अटल स्थिर अक्षर *sbd_type(काष्ठा uart_port *uport)
अणु
	वापस "SB1250 DUART";
पूर्ण

अटल व्योम sbd_release_port(काष्ठा uart_port *uport)
अणु
	काष्ठा sbd_port *sport = to_sport(uport);
	काष्ठा sbd_duart *duart = sport->duart;

	iounmap(sport->memctrl);
	sport->memctrl = शून्य;
	iounmap(uport->membase);
	uport->membase = शून्य;

	अगर(refcount_dec_and_test(&duart->map_guard))
		release_mem_region(duart->mapctrl, DUART_CHANREG_SPACING);
	release_mem_region(uport->mapbase, DUART_CHANREG_SPACING);
पूर्ण

अटल पूर्णांक sbd_map_port(काष्ठा uart_port *uport)
अणु
	स्थिर अक्षर *err = KERN_ERR "sbd: Cannot map MMIO\n";
	काष्ठा sbd_port *sport = to_sport(uport);
	काष्ठा sbd_duart *duart = sport->duart;

	अगर (!uport->membase)
		uport->membase = ioremap(uport->mapbase,
						 DUART_CHANREG_SPACING);
	अगर (!uport->membase) अणु
		prपूर्णांकk(err);
		वापस -ENOMEM;
	पूर्ण

	अगर (!sport->memctrl)
		sport->memctrl = ioremap(duart->mapctrl,
						 DUART_CHANREG_SPACING);
	अगर (!sport->memctrl) अणु
		prपूर्णांकk(err);
		iounmap(uport->membase);
		uport->membase = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sbd_request_port(काष्ठा uart_port *uport)
अणु
	स्थिर अक्षर *err = KERN_ERR "sbd: Unable to reserve MMIO resource\n";
	काष्ठा sbd_duart *duart = to_sport(uport)->duart;
	पूर्णांक ret = 0;

	अगर (!request_mem_region(uport->mapbase, DUART_CHANREG_SPACING,
				"sb1250-duart")) अणु
		prपूर्णांकk(err);
		वापस -EBUSY;
	पूर्ण
	refcount_inc(&duart->map_guard);
	अगर (refcount_पढ़ो(&duart->map_guard) == 1) अणु
		अगर (!request_mem_region(duart->mapctrl, DUART_CHANREG_SPACING,
					"sb1250-duart")) अणु
			refcount_dec(&duart->map_guard);
			prपूर्णांकk(err);
			ret = -EBUSY;
		पूर्ण
	पूर्ण
	अगर (!ret) अणु
		ret = sbd_map_port(uport);
		अगर (ret) अणु
			अगर (refcount_dec_and_test(&duart->map_guard))
				release_mem_region(duart->mapctrl,
						   DUART_CHANREG_SPACING);
		पूर्ण
	पूर्ण
	अगर (ret) अणु
		release_mem_region(uport->mapbase, DUART_CHANREG_SPACING);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sbd_config_port(काष्ठा uart_port *uport, पूर्णांक flags)
अणु
	काष्ठा sbd_port *sport = to_sport(uport);

	अगर (flags & UART_CONFIG_TYPE) अणु
		अगर (sbd_request_port(uport))
			वापस;

		uport->type = PORT_SB1250_DUART;

		sbd_init_port(sport);
	पूर्ण
पूर्ण

अटल पूर्णांक sbd_verअगरy_port(काष्ठा uart_port *uport, काष्ठा serial_काष्ठा *ser)
अणु
	पूर्णांक ret = 0;

	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_SB1250_DUART)
		ret = -EINVAL;
	अगर (ser->irq != uport->irq)
		ret = -EINVAL;
	अगर (ser->baud_base != uport->uartclk / 16)
		ret = -EINVAL;
	वापस ret;
पूर्ण


अटल स्थिर काष्ठा uart_ops sbd_ops = अणु
	.tx_empty	= sbd_tx_empty,
	.set_mctrl	= sbd_set_mctrl,
	.get_mctrl	= sbd_get_mctrl,
	.stop_tx	= sbd_stop_tx,
	.start_tx	= sbd_start_tx,
	.stop_rx	= sbd_stop_rx,
	.enable_ms	= sbd_enable_ms,
	.अवरोध_ctl	= sbd_अवरोध_ctl,
	.startup	= sbd_startup,
	.shutकरोwn	= sbd_shutकरोwn,
	.set_termios	= sbd_set_termios,
	.type		= sbd_type,
	.release_port	= sbd_release_port,
	.request_port	= sbd_request_port,
	.config_port	= sbd_config_port,
	.verअगरy_port	= sbd_verअगरy_port,
पूर्ण;

/* Initialize SB1250 DUART port काष्ठाures.  */
अटल व्योम __init sbd_probe_duarts(व्योम)
अणु
	अटल पूर्णांक probed;
	पूर्णांक chip, side;
	पूर्णांक max_lines, line;

	अगर (probed)
		वापस;

	/* Set the number of available units based on the SOC type.  */
	चयन (soc_type) अणु
	हाल K_SYS_SOC_TYPE_BCM1x55:
	हाल K_SYS_SOC_TYPE_BCM1x80:
		max_lines = 4;
		अवरोध;
	शेष:
		/* Assume at least two serial ports at the normal address.  */
		max_lines = 2;
		अवरोध;
	पूर्ण

	probed = 1;

	क्रम (chip = 0, line = 0; chip < DUART_MAX_CHIP && line < max_lines;
	     chip++) अणु
		sbd_duarts[chip].mapctrl = SBD_CTRLREGS(line);

		क्रम (side = 0; side < DUART_MAX_SIDE && line < max_lines;
		     side++, line++) अणु
			काष्ठा sbd_port *sport = &sbd_duarts[chip].sport[side];
			काष्ठा uart_port *uport = &sport->port;

			sport->duart	= &sbd_duarts[chip];

			uport->irq	= SBD_INT(line);
			uport->uartclk	= 100000000 / 20 * 16;
			uport->fअगरosize	= 16;
			uport->iotype	= UPIO_MEM;
			uport->flags	= UPF_BOOT_AUTOCONF;
			uport->ops	= &sbd_ops;
			uport->line	= line;
			uport->mapbase	= SBD_CHANREGS(line);
			uport->has_sysrq = IS_ENABLED(CONFIG_SERIAL_SB1250_DUART_CONSOLE);
		पूर्ण
	पूर्ण
पूर्ण


#अगर_घोषित CONFIG_SERIAL_SB1250_DUART_CONSOLE
/*
 * Serial console stuff.  Very basic, polling driver क्रम करोing serial
 * console output.  The console_lock is held by the caller, so we
 * shouldn't be पूर्णांकerrupted क्रम more console activity.
 */
अटल व्योम sbd_console_अक्षर_दो(काष्ठा uart_port *uport, पूर्णांक ch)
अणु
	काष्ठा sbd_port *sport = to_sport(uport);

	sbd_transmit_drain(sport);
	ग_लिखो_sbdchn(sport, R_DUART_TX_HOLD, ch);
पूर्ण

अटल व्योम sbd_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
			      अचिन्हित पूर्णांक count)
अणु
	पूर्णांक chip = co->index / DUART_MAX_SIDE;
	पूर्णांक side = co->index % DUART_MAX_SIDE;
	काष्ठा sbd_port *sport = &sbd_duarts[chip].sport[side];
	काष्ठा uart_port *uport = &sport->port;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक mask;

	/* Disable transmit पूर्णांकerrupts and enable the transmitter. */
	spin_lock_irqsave(&uport->lock, flags);
	mask = पढ़ो_sbdshr(sport, R_DUART_IMRREG((uport->line) % 2));
	ग_लिखो_sbdshr(sport, R_DUART_IMRREG((uport->line) % 2),
		     mask & ~M_DUART_IMR_TX);
	ग_लिखो_sbdchn(sport, R_DUART_CMD, M_DUART_TX_EN);
	spin_unlock_irqrestore(&uport->lock, flags);

	uart_console_ग_लिखो(&sport->port, s, count, sbd_console_अक्षर_दो);

	/* Restore transmit पूर्णांकerrupts and the transmitter enable. */
	spin_lock_irqsave(&uport->lock, flags);
	sbd_line_drain(sport);
	अगर (sport->tx_stopped)
		ग_लिखो_sbdchn(sport, R_DUART_CMD, M_DUART_TX_DIS);
	ग_लिखो_sbdshr(sport, R_DUART_IMRREG((uport->line) % 2), mask);
	spin_unlock_irqrestore(&uport->lock, flags);
पूर्ण

अटल पूर्णांक __init sbd_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	पूर्णांक chip = co->index / DUART_MAX_SIDE;
	पूर्णांक side = co->index % DUART_MAX_SIDE;
	काष्ठा sbd_port *sport = &sbd_duarts[chip].sport[side];
	काष्ठा uart_port *uport = &sport->port;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	पूर्णांक ret;

	अगर (!sport->duart)
		वापस -ENXIO;

	ret = sbd_map_port(uport);
	अगर (ret)
		वापस ret;

	sbd_init_port(sport);

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	वापस uart_set_options(uport, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver sbd_reg;
अटल काष्ठा console sbd_console = अणु
	.name	= "duart",
	.ग_लिखो	= sbd_console_ग_लिखो,
	.device	= uart_console_device,
	.setup	= sbd_console_setup,
	.flags	= CON_PRINTBUFFER,
	.index	= -1,
	.data	= &sbd_reg
पूर्ण;

अटल पूर्णांक __init sbd_serial_console_init(व्योम)
अणु
	sbd_probe_duarts();
	रेजिस्टर_console(&sbd_console);

	वापस 0;
पूर्ण

console_initcall(sbd_serial_console_init);

#घोषणा SERIAL_SB1250_DUART_CONSOLE	&sbd_console
#अन्यथा
#घोषणा SERIAL_SB1250_DUART_CONSOLE	शून्य
#पूर्ण_अगर /* CONFIG_SERIAL_SB1250_DUART_CONSOLE */


अटल काष्ठा uart_driver sbd_reg = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "sb1250_duart",
	.dev_name	= "duart",
	.major		= TTY_MAJOR,
	.minor		= SB1250_DUART_MINOR_BASE,
	.nr		= DUART_MAX_CHIP * DUART_MAX_SIDE,
	.cons		= SERIAL_SB1250_DUART_CONSOLE,
पूर्ण;

/* Set up the driver and रेजिस्टर it.  */
अटल पूर्णांक __init sbd_init(व्योम)
अणु
	पूर्णांक i, ret;

	sbd_probe_duarts();

	ret = uart_रेजिस्टर_driver(&sbd_reg);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < DUART_MAX_CHIP * DUART_MAX_SIDE; i++) अणु
		काष्ठा sbd_duart *duart = &sbd_duarts[i / DUART_MAX_SIDE];
		काष्ठा sbd_port *sport = &duart->sport[i % DUART_MAX_SIDE];
		काष्ठा uart_port *uport = &sport->port;

		अगर (sport->duart)
			uart_add_one_port(&sbd_reg, uport);
	पूर्ण

	वापस 0;
पूर्ण

/* Unload the driver.  Unरेजिस्टर stuff, get पढ़ोy to go away.  */
अटल व्योम __निकास sbd_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = DUART_MAX_CHIP * DUART_MAX_SIDE - 1; i >= 0; i--) अणु
		काष्ठा sbd_duart *duart = &sbd_duarts[i / DUART_MAX_SIDE];
		काष्ठा sbd_port *sport = &duart->sport[i % DUART_MAX_SIDE];
		काष्ठा uart_port *uport = &sport->port;

		अगर (sport->duart)
			uart_हटाओ_one_port(&sbd_reg, uport);
	पूर्ण

	uart_unरेजिस्टर_driver(&sbd_reg);
पूर्ण

module_init(sbd_init);
module_निकास(sbd_निकास);
