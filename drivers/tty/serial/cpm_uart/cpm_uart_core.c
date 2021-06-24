<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Driver क्रम CPM (SCC/SMC) serial ports; core driver
 *
 *  Based on arch/ppc/cpm2_io/uart.c by Dan Malek
 *  Based on ppc8xx.c by Thomas Gleixner
 *  Based on drivers/serial/amba.c by Russell King
 *
 *  Maपूर्णांकainer: Kumar Gala (galak@kernel.crashing.org) (CPM2)
 *              Pantelis Antoniou (panto@पूर्णांकracom.gr) (CPM1)
 *
 *  Copyright (C) 2004, 2007 Freescale Semiconductor, Inc.
 *            (C) 2004 Intracom, S.A.
 *            (C) 2005-2006 MontaVista Software, Inc.
 *		Vitaly Bordug <vbordug@ru.mvista.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/console.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/device.h>
#समावेश <linux/memblock.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/fs_uart_pd.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/clk.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/fs_pd.h>
#समावेश <यंत्र/udbg.h>

#समावेश <linux/serial_core.h>
#समावेश <linux/kernel.h>

#समावेश "cpm_uart.h"


/**************************************************************/

अटल पूर्णांक  cpm_uart_tx_pump(काष्ठा uart_port *port);
अटल व्योम cpm_uart_init_smc(काष्ठा uart_cpm_port *pinfo);
अटल व्योम cpm_uart_init_scc(काष्ठा uart_cpm_port *pinfo);
अटल व्योम cpm_uart_initbd(काष्ठा uart_cpm_port *pinfo);

/**************************************************************/

#घोषणा HW_BUF_SPD_THRESHOLD    2400

/*
 * Check, अगर transmit buffers are processed
*/
अटल अचिन्हित पूर्णांक cpm_uart_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा uart_cpm_port *pinfo =
		container_of(port, काष्ठा uart_cpm_port, port);
	cbd_t __iomem *bdp = pinfo->tx_bd_base;
	पूर्णांक ret = 0;

	जबतक (1) अणु
		अगर (in_be16(&bdp->cbd_sc) & BD_SC_READY)
			अवरोध;

		अगर (in_be16(&bdp->cbd_sc) & BD_SC_WRAP) अणु
			ret = TIOCSER_TEMT;
			अवरोध;
		पूर्ण
		bdp++;
	पूर्ण

	pr_debug("CPM uart[%d]:tx_empty: %d\n", port->line, ret);

	वापस ret;
पूर्ण

अटल व्योम cpm_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा uart_cpm_port *pinfo =
		container_of(port, काष्ठा uart_cpm_port, port);

	अगर (pinfo->gpios[GPIO_RTS])
		gpiod_set_value(pinfo->gpios[GPIO_RTS], !(mctrl & TIOCM_RTS));

	अगर (pinfo->gpios[GPIO_DTR])
		gpiod_set_value(pinfo->gpios[GPIO_DTR], !(mctrl & TIOCM_DTR));
पूर्ण

अटल अचिन्हित पूर्णांक cpm_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा uart_cpm_port *pinfo =
		container_of(port, काष्ठा uart_cpm_port, port);
	अचिन्हित पूर्णांक mctrl = TIOCM_CTS | TIOCM_DSR | TIOCM_CAR;

	अगर (pinfo->gpios[GPIO_CTS]) अणु
		अगर (gpiod_get_value(pinfo->gpios[GPIO_CTS]))
			mctrl &= ~TIOCM_CTS;
	पूर्ण

	अगर (pinfo->gpios[GPIO_DSR]) अणु
		अगर (gpiod_get_value(pinfo->gpios[GPIO_DSR]))
			mctrl &= ~TIOCM_DSR;
	पूर्ण

	अगर (pinfo->gpios[GPIO_DCD]) अणु
		अगर (gpiod_get_value(pinfo->gpios[GPIO_DCD]))
			mctrl &= ~TIOCM_CAR;
	पूर्ण

	अगर (pinfo->gpios[GPIO_RI]) अणु
		अगर (!gpiod_get_value(pinfo->gpios[GPIO_RI]))
			mctrl |= TIOCM_RNG;
	पूर्ण

	वापस mctrl;
पूर्ण

/*
 * Stop transmitter
 */
अटल व्योम cpm_uart_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_cpm_port *pinfo =
		container_of(port, काष्ठा uart_cpm_port, port);
	smc_t __iomem *smcp = pinfo->smcp;
	scc_t __iomem *sccp = pinfo->sccp;

	pr_debug("CPM uart[%d]:stop tx\n", port->line);

	अगर (IS_SMC(pinfo))
		clrbits8(&smcp->smc_smcm, SMCM_TX);
	अन्यथा
		clrbits16(&sccp->scc_sccm, UART_SCCM_TX);
पूर्ण

/*
 * Start transmitter
 */
अटल व्योम cpm_uart_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_cpm_port *pinfo =
		container_of(port, काष्ठा uart_cpm_port, port);
	smc_t __iomem *smcp = pinfo->smcp;
	scc_t __iomem *sccp = pinfo->sccp;

	pr_debug("CPM uart[%d]:start tx\n", port->line);

	अगर (IS_SMC(pinfo)) अणु
		अगर (in_8(&smcp->smc_smcm) & SMCM_TX)
			वापस;
	पूर्ण अन्यथा अणु
		अगर (in_be16(&sccp->scc_sccm) & UART_SCCM_TX)
			वापस;
	पूर्ण

	अगर (cpm_uart_tx_pump(port) != 0) अणु
		अगर (IS_SMC(pinfo)) अणु
			setbits8(&smcp->smc_smcm, SMCM_TX);
		पूर्ण अन्यथा अणु
			setbits16(&sccp->scc_sccm, UART_SCCM_TX);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Stop receiver
 */
अटल व्योम cpm_uart_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_cpm_port *pinfo =
		container_of(port, काष्ठा uart_cpm_port, port);
	smc_t __iomem *smcp = pinfo->smcp;
	scc_t __iomem *sccp = pinfo->sccp;

	pr_debug("CPM uart[%d]:stop rx\n", port->line);

	अगर (IS_SMC(pinfo))
		clrbits8(&smcp->smc_smcm, SMCM_RX);
	अन्यथा
		clrbits16(&sccp->scc_sccm, UART_SCCM_RX);
पूर्ण

/*
 * Generate a अवरोध.
 */
अटल व्योम cpm_uart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा uart_cpm_port *pinfo =
		container_of(port, काष्ठा uart_cpm_port, port);

	pr_debug("CPM uart[%d]:break ctrl, break_state: %d\n", port->line,
		अवरोध_state);

	अगर (अवरोध_state)
		cpm_line_cr_cmd(pinfo, CPM_CR_STOP_TX);
	अन्यथा
		cpm_line_cr_cmd(pinfo, CPM_CR_RESTART_TX);
पूर्ण

/*
 * Transmit अक्षरacters, refill buffer descriptor, अगर possible
 */
अटल व्योम cpm_uart_पूर्णांक_tx(काष्ठा uart_port *port)
अणु
	pr_debug("CPM uart[%d]:TX INT\n", port->line);

	cpm_uart_tx_pump(port);
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
अटल पूर्णांक serial_polled;
#पूर्ण_अगर

/*
 * Receive अक्षरacters
 */
अटल व्योम cpm_uart_पूर्णांक_rx(काष्ठा uart_port *port)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर ch;
	u8 *cp;
	काष्ठा tty_port *tport = &port->state->port;
	काष्ठा uart_cpm_port *pinfo =
		container_of(port, काष्ठा uart_cpm_port, port);
	cbd_t __iomem *bdp;
	u16 status;
	अचिन्हित पूर्णांक flg;

	pr_debug("CPM uart[%d]:RX INT\n", port->line);

	/* Just loop through the बंदd BDs and copy the अक्षरacters पूर्णांकo
	 * the buffer.
	 */
	bdp = pinfo->rx_cur;
	क्रम (;;) अणु
#अगर_घोषित CONFIG_CONSOLE_POLL
		अगर (unlikely(serial_polled)) अणु
			serial_polled = 0;
			वापस;
		पूर्ण
#पूर्ण_अगर
		/* get status */
		status = in_be16(&bdp->cbd_sc);
		/* If this one is empty, वापस happy */
		अगर (status & BD_SC_EMPTY)
			अवरोध;

		/* get number of अक्षरacters, and check spce in flip-buffer */
		i = in_be16(&bdp->cbd_datlen);

		/* If we have not enough room in tty flip buffer, then we try
		 * later, which will be the next rx-पूर्णांकerrupt or a समयout
		 */
		अगर (tty_buffer_request_room(tport, i) < i) अणु
			prपूर्णांकk(KERN_WARNING "No room in flip buffer\n");
			वापस;
		पूर्ण

		/* get poपूर्णांकer */
		cp = cpm2cpu_addr(in_be32(&bdp->cbd_bufaddr), pinfo);

		/* loop through the buffer */
		जबतक (i-- > 0) अणु
			ch = *cp++;
			port->icount.rx++;
			flg = TTY_NORMAL;

			अगर (status &
			    (BD_SC_BR | BD_SC_FR | BD_SC_PR | BD_SC_OV))
				जाओ handle_error;
			अगर (uart_handle_sysrq_अक्षर(port, ch))
				जारी;
#अगर_घोषित CONFIG_CONSOLE_POLL
			अगर (unlikely(serial_polled)) अणु
				serial_polled = 0;
				वापस;
			पूर्ण
#पूर्ण_अगर
		      error_वापस:
			tty_insert_flip_अक्षर(tport, ch, flg);

		पूर्ण		/* End जबतक (i--) */

		/* This BD is पढ़ोy to be used again. Clear status. get next */
		clrbits16(&bdp->cbd_sc, BD_SC_BR | BD_SC_FR | BD_SC_PR |
		                        BD_SC_OV | BD_SC_ID);
		setbits16(&bdp->cbd_sc, BD_SC_EMPTY);

		अगर (in_be16(&bdp->cbd_sc) & BD_SC_WRAP)
			bdp = pinfo->rx_bd_base;
		अन्यथा
			bdp++;

	पूर्ण /* End क्रम (;;) */

	/* Write back buffer poपूर्णांकer */
	pinfo->rx_cur = bdp;

	/* activate BH processing */
	tty_flip_buffer_push(tport);

	वापस;

	/* Error processing */

      handle_error:
	/* Statistics */
	अगर (status & BD_SC_BR)
		port->icount.brk++;
	अगर (status & BD_SC_PR)
		port->icount.parity++;
	अगर (status & BD_SC_FR)
		port->icount.frame++;
	अगर (status & BD_SC_OV)
		port->icount.overrun++;

	/* Mask out ignored conditions */
	status &= port->पढ़ो_status_mask;

	/* Handle the reमुख्यing ones */
	अगर (status & BD_SC_BR)
		flg = TTY_BREAK;
	अन्यथा अगर (status & BD_SC_PR)
		flg = TTY_PARITY;
	अन्यथा अगर (status & BD_SC_FR)
		flg = TTY_FRAME;

	/* overrun करोes not affect the current अक्षरacter ! */
	अगर (status & BD_SC_OV) अणु
		ch = 0;
		flg = TTY_OVERRUN;
		/* We skip this buffer */
		/* CHECK: Is really nothing senseful there */
		/* ASSUMPTION: it contains nothing valid */
		i = 0;
	पूर्ण
	port->sysrq = 0;
	जाओ error_वापस;
पूर्ण

/*
 * Asynchron mode पूर्णांकerrupt handler
 */
अटल irqवापस_t cpm_uart_पूर्णांक(पूर्णांक irq, व्योम *data)
अणु
	u8 events;
	काष्ठा uart_port *port = data;
	काष्ठा uart_cpm_port *pinfo = (काष्ठा uart_cpm_port *)port;
	smc_t __iomem *smcp = pinfo->smcp;
	scc_t __iomem *sccp = pinfo->sccp;

	pr_debug("CPM uart[%d]:IRQ\n", port->line);

	अगर (IS_SMC(pinfo)) अणु
		events = in_8(&smcp->smc_smce);
		out_8(&smcp->smc_smce, events);
		अगर (events & SMCM_BRKE)
			uart_handle_अवरोध(port);
		अगर (events & SMCM_RX)
			cpm_uart_पूर्णांक_rx(port);
		अगर (events & SMCM_TX)
			cpm_uart_पूर्णांक_tx(port);
	पूर्ण अन्यथा अणु
		events = in_be16(&sccp->scc_scce);
		out_be16(&sccp->scc_scce, events);
		अगर (events & UART_SCCM_BRKE)
			uart_handle_अवरोध(port);
		अगर (events & UART_SCCM_RX)
			cpm_uart_पूर्णांक_rx(port);
		अगर (events & UART_SCCM_TX)
			cpm_uart_पूर्णांक_tx(port);
	पूर्ण
	वापस (events) ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक cpm_uart_startup(काष्ठा uart_port *port)
अणु
	पूर्णांक retval;
	काष्ठा uart_cpm_port *pinfo =
		container_of(port, काष्ठा uart_cpm_port, port);

	pr_debug("CPM uart[%d]:startup\n", port->line);

	/* If the port is not the console, make sure rx is disabled. */
	अगर (!(pinfo->flags & FLAG_CONSOLE)) अणु
		/* Disable UART rx */
		अगर (IS_SMC(pinfo)) अणु
			clrbits16(&pinfo->smcp->smc_smcmr, SMCMR_REN);
			clrbits8(&pinfo->smcp->smc_smcm, SMCM_RX);
		पूर्ण अन्यथा अणु
			clrbits32(&pinfo->sccp->scc_gsmrl, SCC_GSMRL_ENR);
			clrbits16(&pinfo->sccp->scc_sccm, UART_SCCM_RX);
		पूर्ण
		cpm_uart_initbd(pinfo);
		अगर (IS_SMC(pinfo)) अणु
			out_be32(&pinfo->smcup->smc_rstate, 0);
			out_be32(&pinfo->smcup->smc_tstate, 0);
			out_be16(&pinfo->smcup->smc_rbptr,
				 in_be16(&pinfo->smcup->smc_rbase));
			out_be16(&pinfo->smcup->smc_tbptr,
				 in_be16(&pinfo->smcup->smc_tbase));
		पूर्ण अन्यथा अणु
			cpm_line_cr_cmd(pinfo, CPM_CR_INIT_TRX);
		पूर्ण
	पूर्ण
	/* Install पूर्णांकerrupt handler. */
	retval = request_irq(port->irq, cpm_uart_पूर्णांक, 0, "cpm_uart", port);
	अगर (retval)
		वापस retval;

	/* Startup rx-पूर्णांक */
	अगर (IS_SMC(pinfo)) अणु
		setbits8(&pinfo->smcp->smc_smcm, SMCM_RX);
		setbits16(&pinfo->smcp->smc_smcmr, (SMCMR_REN | SMCMR_TEN));
	पूर्ण अन्यथा अणु
		setbits16(&pinfo->sccp->scc_sccm, UART_SCCM_RX);
		setbits32(&pinfo->sccp->scc_gsmrl, (SCC_GSMRL_ENR | SCC_GSMRL_ENT));
	पूर्ण

	वापस 0;
पूर्ण

अंतरभूत व्योम cpm_uart_रुको_until_send(काष्ठा uart_cpm_port *pinfo)
अणु
	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule_समयout(pinfo->रुको_closing);
पूर्ण

/*
 * Shutकरोwn the uart
 */
अटल व्योम cpm_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा uart_cpm_port *pinfo =
		container_of(port, काष्ठा uart_cpm_port, port);

	pr_debug("CPM uart[%d]:shutdown\n", port->line);

	/* मुक्त पूर्णांकerrupt handler */
	मुक्त_irq(port->irq, port);

	/* If the port is not the console, disable Rx and Tx. */
	अगर (!(pinfo->flags & FLAG_CONSOLE)) अणु
		/* Wait क्रम all the BDs marked sent */
		जबतक(!cpm_uart_tx_empty(port)) अणु
			set_current_state(TASK_UNINTERRUPTIBLE);
			schedule_समयout(2);
		पूर्ण

		अगर (pinfo->रुको_closing)
			cpm_uart_रुको_until_send(pinfo);

		/* Stop uarts */
		अगर (IS_SMC(pinfo)) अणु
			smc_t __iomem *smcp = pinfo->smcp;
			clrbits16(&smcp->smc_smcmr, SMCMR_REN | SMCMR_TEN);
			clrbits8(&smcp->smc_smcm, SMCM_RX | SMCM_TX);
		पूर्ण अन्यथा अणु
			scc_t __iomem *sccp = pinfo->sccp;
			clrbits32(&sccp->scc_gsmrl, SCC_GSMRL_ENR | SCC_GSMRL_ENT);
			clrbits16(&sccp->scc_sccm, UART_SCCM_TX | UART_SCCM_RX);
		पूर्ण

		/* Shut them really करोwn and reinit buffer descriptors */
		अगर (IS_SMC(pinfo)) अणु
			out_be16(&pinfo->smcup->smc_brkcr, 0);
			cpm_line_cr_cmd(pinfo, CPM_CR_STOP_TX);
		पूर्ण अन्यथा अणु
			out_be16(&pinfo->sccup->scc_brkcr, 0);
			cpm_line_cr_cmd(pinfo, CPM_CR_GRA_STOP_TX);
		पूर्ण

		cpm_uart_initbd(pinfo);
	पूर्ण
पूर्ण

अटल व्योम cpm_uart_set_termios(काष्ठा uart_port *port,
                                 काष्ठा ktermios *termios,
                                 काष्ठा ktermios *old)
अणु
	पूर्णांक baud;
	अचिन्हित दीर्घ flags;
	u16 cval, scval, prev_mode;
	पूर्णांक bits, sbits;
	काष्ठा uart_cpm_port *pinfo =
		container_of(port, काष्ठा uart_cpm_port, port);
	smc_t __iomem *smcp = pinfo->smcp;
	scc_t __iomem *sccp = pinfo->sccp;
	पूर्णांक maxidl;

	pr_debug("CPM uart[%d]:set_termios\n", port->line);

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk / 16);
	अगर (baud < HW_BUF_SPD_THRESHOLD || port->flags & UPF_LOW_LATENCY)
		pinfo->rx_fअगरosize = 1;
	अन्यथा
		pinfo->rx_fअगरosize = RX_BUF_SIZE;

	/* MAXIDL is the समयout after which a receive buffer is बंदd
	 * when not full अगर no more अक्षरacters are received.
	 * We calculate it from the baudrate so that the duration is
	 * always the same at standard rates: about 4ms.
	 */
	maxidl = baud / 2400;
	अगर (maxidl < 1)
		maxidl = 1;
	अगर (maxidl > 0x10)
		maxidl = 0x10;

	/* Character length programmed पूर्णांकo the mode रेजिस्टर is the
	 * sum of: 1 start bit, number of data bits, 0 or 1 parity bit,
	 * 1 or 2 stop bits, minus 1.
	 * The value 'bits' counts this क्रम us.
	 */
	cval = 0;
	scval = 0;

	/* byte size */
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		bits = 5;
		अवरोध;
	हाल CS6:
		bits = 6;
		अवरोध;
	हाल CS7:
		bits = 7;
		अवरोध;
	हाल CS8:
		bits = 8;
		अवरोध;
		/* Never happens, but GCC is too dumb to figure it out */
	शेष:
		bits = 8;
		अवरोध;
	पूर्ण
	sbits = bits - 5;

	अगर (termios->c_cflag & CSTOPB) अणु
		cval |= SMCMR_SL;	/* Two stops */
		scval |= SCU_PSMR_SL;
		bits++;
	पूर्ण

	अगर (termios->c_cflag & PARENB) अणु
		cval |= SMCMR_PEN;
		scval |= SCU_PSMR_PEN;
		bits++;
		अगर (!(termios->c_cflag & PARODD)) अणु
			cval |= SMCMR_PM_EVEN;
			scval |= (SCU_PSMR_REVP | SCU_PSMR_TEVP);
		पूर्ण
	पूर्ण

	/*
	 * Update the समयout
	 */
	uart_update_समयout(port, termios->c_cflag, baud);

	/*
	 * Set up parity check flag
	 */
	port->पढ़ो_status_mask = (BD_SC_EMPTY | BD_SC_OV);
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= BD_SC_FR | BD_SC_PR;
	अगर ((termios->c_अगरlag & BRKINT) || (termios->c_अगरlag & PARMRK))
		port->पढ़ो_status_mask |= BD_SC_BR;

	/*
	 * Characters to ignore
	 */
	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= BD_SC_PR | BD_SC_FR;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		port->ignore_status_mask |= BD_SC_BR;
		/*
		 * If we're ignore parity and अवरोध indicators, ignore
		 * overruns too.  (For real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			port->ignore_status_mask |= BD_SC_OV;
	पूर्ण
	/*
	 * !!! ignore all अक्षरacters अगर CREAD is not set
	 */
	अगर ((termios->c_cflag & CREAD) == 0)
		port->पढ़ो_status_mask &= ~BD_SC_EMPTY;

	spin_lock_irqsave(&port->lock, flags);

	/* Start bit has not been added (so करोn't, because we would just
	 * subtract it later), and we need to add one क्रम the number of
	 * stops bits (there is always at least one).
	 */
	bits++;
	अगर (IS_SMC(pinfo)) अणु
		/*
		 * MRBLR can be changed जबतक an SMC/SCC is operating only
		 * अगर it is करोne in a single bus cycle with one 16-bit move
		 * (not two 8-bit bus cycles back-to-back). This occurs when
		 * the cp shअगरts control to the next RxBD, so the change करोes
		 * not take effect immediately. To guarantee the exact RxBD
		 * on which the change occurs, change MRBLR only जबतक the
		 * SMC/SCC receiver is disabled.
		 */
		out_be16(&pinfo->smcup->smc_mrblr, pinfo->rx_fअगरosize);
		out_be16(&pinfo->smcup->smc_maxidl, maxidl);

		/* Set the mode रेजिस्टर.  We want to keep a copy of the
		 * enables, because we want to put them back अगर they were
		 * present.
		 */
		prev_mode = in_be16(&smcp->smc_smcmr) & (SMCMR_REN | SMCMR_TEN);
		/* Output in *one* operation, so we करोn't पूर्णांकerrupt RX/TX अगर they
		 * were alपढ़ोy enabled. */
		out_be16(&smcp->smc_smcmr, smcr_mk_clen(bits) | cval |
		    SMCMR_SM_UART | prev_mode);
	पूर्ण अन्यथा अणु
		out_be16(&pinfo->sccup->scc_genscc.scc_mrblr, pinfo->rx_fअगरosize);
		out_be16(&pinfo->sccup->scc_maxidl, maxidl);
		out_be16(&sccp->scc_psmr, (sbits << 12) | scval);
	पूर्ण

	अगर (pinfo->clk)
		clk_set_rate(pinfo->clk, baud);
	अन्यथा
		cpm_set_brg(pinfo->brg - 1, baud);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *cpm_uart_type(काष्ठा uart_port *port)
अणु
	pr_debug("CPM uart[%d]:uart_type\n", port->line);

	वापस port->type == PORT_CPM ? "CPM UART" : शून्य;
पूर्ण

/*
 * verअगरy the new serial_काष्ठा (क्रम TIOCSSERIAL).
 */
अटल पूर्णांक cpm_uart_verअगरy_port(काष्ठा uart_port *port,
				काष्ठा serial_काष्ठा *ser)
अणु
	पूर्णांक ret = 0;

	pr_debug("CPM uart[%d]:verify_port\n", port->line);

	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_CPM)
		ret = -EINVAL;
	अगर (ser->irq < 0 || ser->irq >= nr_irqs)
		ret = -EINVAL;
	अगर (ser->baud_base < 9600)
		ret = -EINVAL;
	वापस ret;
पूर्ण

/*
 * Transmit अक्षरacters, refill buffer descriptor, अगर possible
 */
अटल पूर्णांक cpm_uart_tx_pump(काष्ठा uart_port *port)
अणु
	cbd_t __iomem *bdp;
	u8 *p;
	पूर्णांक count;
	काष्ठा uart_cpm_port *pinfo =
		container_of(port, काष्ठा uart_cpm_port, port);
	काष्ठा circ_buf *xmit = &port->state->xmit;

	/* Handle xon/xoff */
	अगर (port->x_अक्षर) अणु
		/* Pick next descriptor and fill from buffer */
		bdp = pinfo->tx_cur;

		p = cpm2cpu_addr(in_be32(&bdp->cbd_bufaddr), pinfo);

		*p++ = port->x_अक्षर;

		out_be16(&bdp->cbd_datlen, 1);
		setbits16(&bdp->cbd_sc, BD_SC_READY);
		/* Get next BD. */
		अगर (in_be16(&bdp->cbd_sc) & BD_SC_WRAP)
			bdp = pinfo->tx_bd_base;
		अन्यथा
			bdp++;
		pinfo->tx_cur = bdp;

		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस 1;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		cpm_uart_stop_tx(port);
		वापस 0;
	पूर्ण

	/* Pick next descriptor and fill from buffer */
	bdp = pinfo->tx_cur;

	जबतक (!(in_be16(&bdp->cbd_sc) & BD_SC_READY) &&
	       xmit->tail != xmit->head) अणु
		count = 0;
		p = cpm2cpu_addr(in_be32(&bdp->cbd_bufaddr), pinfo);
		जबतक (count < pinfo->tx_fअगरosize) अणु
			*p++ = xmit->buf[xmit->tail];
			xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
			port->icount.tx++;
			count++;
			अगर (xmit->head == xmit->tail)
				अवरोध;
		पूर्ण
		out_be16(&bdp->cbd_datlen, count);
		setbits16(&bdp->cbd_sc, BD_SC_READY);
		/* Get next BD. */
		अगर (in_be16(&bdp->cbd_sc) & BD_SC_WRAP)
			bdp = pinfo->tx_bd_base;
		अन्यथा
			bdp++;
	पूर्ण
	pinfo->tx_cur = bdp;

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (uart_circ_empty(xmit)) अणु
		cpm_uart_stop_tx(port);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * init buffer descriptors
 */
अटल व्योम cpm_uart_initbd(काष्ठा uart_cpm_port *pinfo)
अणु
	पूर्णांक i;
	u8 *mem_addr;
	cbd_t __iomem *bdp;

	pr_debug("CPM uart[%d]:initbd\n", pinfo->port.line);

	/* Set the physical address of the host memory
	 * buffers in the buffer descriptors, and the
	 * भव address क्रम us to work with.
	 */
	mem_addr = pinfo->mem_addr;
	bdp = pinfo->rx_cur = pinfo->rx_bd_base;
	क्रम (i = 0; i < (pinfo->rx_nrfअगरos - 1); i++, bdp++) अणु
		out_be32(&bdp->cbd_bufaddr, cpu2cpm_addr(mem_addr, pinfo));
		out_be16(&bdp->cbd_sc, BD_SC_EMPTY | BD_SC_INTRPT);
		mem_addr += pinfo->rx_fअगरosize;
	पूर्ण

	out_be32(&bdp->cbd_bufaddr, cpu2cpm_addr(mem_addr, pinfo));
	out_be16(&bdp->cbd_sc, BD_SC_WRAP | BD_SC_EMPTY | BD_SC_INTRPT);

	/* Set the physical address of the host memory
	 * buffers in the buffer descriptors, and the
	 * भव address क्रम us to work with.
	 */
	mem_addr = pinfo->mem_addr + L1_CACHE_ALIGN(pinfo->rx_nrfअगरos * pinfo->rx_fअगरosize);
	bdp = pinfo->tx_cur = pinfo->tx_bd_base;
	क्रम (i = 0; i < (pinfo->tx_nrfअगरos - 1); i++, bdp++) अणु
		out_be32(&bdp->cbd_bufaddr, cpu2cpm_addr(mem_addr, pinfo));
		out_be16(&bdp->cbd_sc, BD_SC_INTRPT);
		mem_addr += pinfo->tx_fअगरosize;
	पूर्ण

	out_be32(&bdp->cbd_bufaddr, cpu2cpm_addr(mem_addr, pinfo));
	out_be16(&bdp->cbd_sc, BD_SC_WRAP | BD_SC_INTRPT);
पूर्ण

अटल व्योम cpm_uart_init_scc(काष्ठा uart_cpm_port *pinfo)
अणु
	scc_t __iomem *scp;
	scc_uart_t __iomem *sup;

	pr_debug("CPM uart[%d]:init_scc\n", pinfo->port.line);

	scp = pinfo->sccp;
	sup = pinfo->sccup;

	/* Store address */
	out_be16(&pinfo->sccup->scc_genscc.scc_rbase,
	         (u8 __iomem *)pinfo->rx_bd_base - DPRAM_BASE);
	out_be16(&pinfo->sccup->scc_genscc.scc_tbase,
	         (u8 __iomem *)pinfo->tx_bd_base - DPRAM_BASE);

	/* Set up the uart parameters in the
	 * parameter ram.
	 */

	cpm_set_scc_fcr(sup);

	out_be16(&sup->scc_genscc.scc_mrblr, pinfo->rx_fअगरosize);
	out_be16(&sup->scc_maxidl, 0x10);
	out_be16(&sup->scc_brkcr, 1);
	out_be16(&sup->scc_parec, 0);
	out_be16(&sup->scc_frmec, 0);
	out_be16(&sup->scc_nosec, 0);
	out_be16(&sup->scc_brkec, 0);
	out_be16(&sup->scc_uaddr1, 0);
	out_be16(&sup->scc_uaddr2, 0);
	out_be16(&sup->scc_toseq, 0);
	out_be16(&sup->scc_अक्षर1, 0x8000);
	out_be16(&sup->scc_अक्षर2, 0x8000);
	out_be16(&sup->scc_अक्षर3, 0x8000);
	out_be16(&sup->scc_अक्षर4, 0x8000);
	out_be16(&sup->scc_अक्षर5, 0x8000);
	out_be16(&sup->scc_अक्षर6, 0x8000);
	out_be16(&sup->scc_अक्षर7, 0x8000);
	out_be16(&sup->scc_अक्षर8, 0x8000);
	out_be16(&sup->scc_rccm, 0xc0ff);

	/* Send the CPM an initialize command.
	 */
	cpm_line_cr_cmd(pinfo, CPM_CR_INIT_TRX);

	/* Set UART mode, 8 bit, no parity, one stop.
	 * Enable receive and transmit.
	 */
	out_be32(&scp->scc_gsmrh, 0);
	out_be32(&scp->scc_gsmrl,
	         SCC_GSMRL_MODE_UART | SCC_GSMRL_TDCR_16 | SCC_GSMRL_RDCR_16);

	/* Enable rx पूर्णांकerrupts  and clear all pending events.  */
	out_be16(&scp->scc_sccm, 0);
	out_be16(&scp->scc_scce, 0xffff);
	out_be16(&scp->scc_dsr, 0x7e7e);
	out_be16(&scp->scc_psmr, 0x3000);

	setbits32(&scp->scc_gsmrl, SCC_GSMRL_ENR | SCC_GSMRL_ENT);
पूर्ण

अटल व्योम cpm_uart_init_smc(काष्ठा uart_cpm_port *pinfo)
अणु
	smc_t __iomem *sp;
	smc_uart_t __iomem *up;

	pr_debug("CPM uart[%d]:init_smc\n", pinfo->port.line);

	sp = pinfo->smcp;
	up = pinfo->smcup;

	/* Store address */
	out_be16(&pinfo->smcup->smc_rbase,
	         (u8 __iomem *)pinfo->rx_bd_base - DPRAM_BASE);
	out_be16(&pinfo->smcup->smc_tbase,
	         (u8 __iomem *)pinfo->tx_bd_base - DPRAM_BASE);

/*
 *  In हाल SMC is being relocated...
 */
	out_be16(&up->smc_rbptr, in_be16(&pinfo->smcup->smc_rbase));
	out_be16(&up->smc_tbptr, in_be16(&pinfo->smcup->smc_tbase));
	out_be32(&up->smc_rstate, 0);
	out_be32(&up->smc_tstate, 0);
	out_be16(&up->smc_brkcr, 1);              /* number of अवरोध अक्षरs */
	out_be16(&up->smc_brkec, 0);

	/* Set up the uart parameters in the
	 * parameter ram.
	 */
	cpm_set_smc_fcr(up);

	/* Using idle अक्षरacter समय requires some additional tuning.  */
	out_be16(&up->smc_mrblr, pinfo->rx_fअगरosize);
	out_be16(&up->smc_maxidl, 0x10);
	out_be16(&up->smc_brklen, 0);
	out_be16(&up->smc_brkec, 0);
	out_be16(&up->smc_brkcr, 1);

	/* Set UART mode, 8 bit, no parity, one stop.
	 * Enable receive and transmit.
	 */
	out_be16(&sp->smc_smcmr, smcr_mk_clen(9) | SMCMR_SM_UART);

	/* Enable only rx पूर्णांकerrupts clear all pending events. */
	out_8(&sp->smc_smcm, 0);
	out_8(&sp->smc_smce, 0xff);

	setbits16(&sp->smc_smcmr, SMCMR_REN | SMCMR_TEN);
पूर्ण

/*
 * Initialize port. This is called from early_console stuff
 * so we have to be careful here !
 */
अटल पूर्णांक cpm_uart_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा uart_cpm_port *pinfo =
		container_of(port, काष्ठा uart_cpm_port, port);
	पूर्णांक ret;

	pr_debug("CPM uart[%d]:request port\n", port->line);

	अगर (pinfo->flags & FLAG_CONSOLE)
		वापस 0;

	अगर (IS_SMC(pinfo)) अणु
		clrbits8(&pinfo->smcp->smc_smcm, SMCM_RX | SMCM_TX);
		clrbits16(&pinfo->smcp->smc_smcmr, SMCMR_REN | SMCMR_TEN);
	पूर्ण अन्यथा अणु
		clrbits16(&pinfo->sccp->scc_sccm, UART_SCCM_TX | UART_SCCM_RX);
		clrbits32(&pinfo->sccp->scc_gsmrl, SCC_GSMRL_ENR | SCC_GSMRL_ENT);
	पूर्ण

	ret = cpm_uart_allocbuf(pinfo, 0);

	अगर (ret)
		वापस ret;

	cpm_uart_initbd(pinfo);
	अगर (IS_SMC(pinfo))
		cpm_uart_init_smc(pinfo);
	अन्यथा
		cpm_uart_init_scc(pinfo);

	वापस 0;
पूर्ण

अटल व्योम cpm_uart_release_port(काष्ठा uart_port *port)
अणु
	काष्ठा uart_cpm_port *pinfo =
		container_of(port, काष्ठा uart_cpm_port, port);

	अगर (!(pinfo->flags & FLAG_CONSOLE))
		cpm_uart_मुक्तbuf(pinfo);
पूर्ण

/*
 * Configure/स्वतःconfigure the port.
 */
अटल व्योम cpm_uart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	pr_debug("CPM uart[%d]:config_port\n", port->line);

	अगर (flags & UART_CONFIG_TYPE) अणु
		port->type = PORT_CPM;
		cpm_uart_request_port(port);
	पूर्ण
पूर्ण

#अगर defined(CONFIG_CONSOLE_POLL) || defined(CONFIG_SERIAL_CPM_CONSOLE)
/*
 * Write a string to the serial port
 * Note that this is called with पूर्णांकerrupts alपढ़ोy disabled
 */
अटल व्योम cpm_uart_early_ग_लिखो(काष्ठा uart_cpm_port *pinfo,
		स्थिर अक्षर *string, u_पूर्णांक count, bool handle_linefeed)
अणु
	अचिन्हित पूर्णांक i;
	cbd_t __iomem *bdp, *bdbase;
	अचिन्हित अक्षर *cpm_outp_addr;

	/* Get the address of the host memory buffer.
	 */
	bdp = pinfo->tx_cur;
	bdbase = pinfo->tx_bd_base;

	/*
	 * Now, करो each अक्षरacter.  This is not as bad as it looks
	 * since this is a holding FIFO and not a transmitting FIFO.
	 * We could add the complनिकासy of filling the entire transmit
	 * buffer, but we would just रुको दीर्घer between accesses......
	 */
	क्रम (i = 0; i < count; i++, string++) अणु
		/* Wait क्रम transmitter fअगरo to empty.
		 * Ready indicates output is पढ़ोy, and xmt is करोing
		 * that, not that it is पढ़ोy क्रम us to send.
		 */
		जबतक ((in_be16(&bdp->cbd_sc) & BD_SC_READY) != 0)
			;

		/* Send the अक्षरacter out.
		 * If the buffer address is in the CPM DPRAM, करोn't
		 * convert it.
		 */
		cpm_outp_addr = cpm2cpu_addr(in_be32(&bdp->cbd_bufaddr),
					pinfo);
		*cpm_outp_addr = *string;

		out_be16(&bdp->cbd_datlen, 1);
		setbits16(&bdp->cbd_sc, BD_SC_READY);

		अगर (in_be16(&bdp->cbd_sc) & BD_SC_WRAP)
			bdp = bdbase;
		अन्यथा
			bdp++;

		/* अगर a LF, also करो CR... */
		अगर (handle_linefeed && *string == 10) अणु
			जबतक ((in_be16(&bdp->cbd_sc) & BD_SC_READY) != 0)
				;

			cpm_outp_addr = cpm2cpu_addr(in_be32(&bdp->cbd_bufaddr),
						pinfo);
			*cpm_outp_addr = 13;

			out_be16(&bdp->cbd_datlen, 1);
			setbits16(&bdp->cbd_sc, BD_SC_READY);

			अगर (in_be16(&bdp->cbd_sc) & BD_SC_WRAP)
				bdp = bdbase;
			अन्यथा
				bdp++;
		पूर्ण
	पूर्ण

	/*
	 * Finally, Wait क्रम transmitter & holding रेजिस्टर to empty
	 *  and restore the IER
	 */
	जबतक ((in_be16(&bdp->cbd_sc) & BD_SC_READY) != 0)
		;

	pinfo->tx_cur = bdp;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CONSOLE_POLL
/* Serial polling routines क्रम writing and पढ़ोing from the uart जबतक
 * in an पूर्णांकerrupt or debug context.
 */

#घोषणा GDB_BUF_SIZE	512	/* घातer of 2, please */

अटल अक्षर poll_buf[GDB_BUF_SIZE];
अटल अक्षर *pollp;
अटल पूर्णांक poll_अक्षरs;

अटल पूर्णांक poll_रुको_key(अक्षर *obuf, काष्ठा uart_cpm_port *pinfo)
अणु
	u_अक्षर		c, *cp;
	अस्थिर cbd_t	*bdp;
	पूर्णांक		i;

	/* Get the address of the host memory buffer.
	 */
	bdp = pinfo->rx_cur;
	अगर (bdp->cbd_sc & BD_SC_EMPTY)
		वापस NO_POLL_CHAR;

	/* If the buffer address is in the CPM DPRAM, करोn't
	 * convert it.
	 */
	cp = cpm2cpu_addr(bdp->cbd_bufaddr, pinfo);

	अगर (obuf) अणु
		i = c = bdp->cbd_datlen;
		जबतक (i-- > 0)
			*obuf++ = *cp++;
	पूर्ण अन्यथा
		c = *cp;
	bdp->cbd_sc &= ~(BD_SC_BR | BD_SC_FR | BD_SC_PR | BD_SC_OV | BD_SC_ID);
	bdp->cbd_sc |= BD_SC_EMPTY;

	अगर (bdp->cbd_sc & BD_SC_WRAP)
		bdp = pinfo->rx_bd_base;
	अन्यथा
		bdp++;
	pinfo->rx_cur = (cbd_t *)bdp;

	वापस (पूर्णांक)c;
पूर्ण

अटल पूर्णांक cpm_get_poll_अक्षर(काष्ठा uart_port *port)
अणु
	काष्ठा uart_cpm_port *pinfo =
		container_of(port, काष्ठा uart_cpm_port, port);

	अगर (!serial_polled) अणु
		serial_polled = 1;
		poll_अक्षरs = 0;
	पूर्ण
	अगर (poll_अक्षरs <= 0) अणु
		पूर्णांक ret = poll_रुको_key(poll_buf, pinfo);

		अगर (ret == NO_POLL_CHAR)
			वापस ret;
		poll_अक्षरs = ret;
		pollp = poll_buf;
	पूर्ण
	poll_अक्षरs--;
	वापस *pollp++;
पूर्ण

अटल व्योम cpm_put_poll_अक्षर(काष्ठा uart_port *port,
			 अचिन्हित अक्षर c)
अणु
	काष्ठा uart_cpm_port *pinfo =
		container_of(port, काष्ठा uart_cpm_port, port);
	अटल अक्षर ch[2];

	ch[0] = (अक्षर)c;
	cpm_uart_early_ग_लिखो(pinfo, ch, 1, false);
पूर्ण

अटल काष्ठा uart_port *udbg_port;

अटल व्योम udbg_cpm_अ_दो(अक्षर c)
अणु
	अगर (c == '\n')
		cpm_put_poll_अक्षर(udbg_port, '\r');
	cpm_put_poll_अक्षर(udbg_port, c);
पूर्ण

अटल पूर्णांक udbg_cpm_अ_लो_poll(व्योम)
अणु
	पूर्णांक c = cpm_get_poll_अक्षर(udbg_port);

	वापस c == NO_POLL_CHAR ? -1 : c;
पूर्ण

अटल पूर्णांक udbg_cpm_अ_लो(व्योम)
अणु
	पूर्णांक c;

	जबतक ((c = udbg_cpm_अ_लो_poll()) == -1)
		cpu_relax();
	वापस c;
पूर्ण

#पूर्ण_अगर /* CONFIG_CONSOLE_POLL */

अटल स्थिर काष्ठा uart_ops cpm_uart_pops = अणु
	.tx_empty	= cpm_uart_tx_empty,
	.set_mctrl	= cpm_uart_set_mctrl,
	.get_mctrl	= cpm_uart_get_mctrl,
	.stop_tx	= cpm_uart_stop_tx,
	.start_tx	= cpm_uart_start_tx,
	.stop_rx	= cpm_uart_stop_rx,
	.अवरोध_ctl	= cpm_uart_अवरोध_ctl,
	.startup	= cpm_uart_startup,
	.shutकरोwn	= cpm_uart_shutकरोwn,
	.set_termios	= cpm_uart_set_termios,
	.type		= cpm_uart_type,
	.release_port	= cpm_uart_release_port,
	.request_port	= cpm_uart_request_port,
	.config_port	= cpm_uart_config_port,
	.verअगरy_port	= cpm_uart_verअगरy_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर = cpm_get_poll_अक्षर,
	.poll_put_अक्षर = cpm_put_poll_अक्षर,
#पूर्ण_अगर
पूर्ण;

काष्ठा uart_cpm_port cpm_uart_ports[UART_NR];

अटल पूर्णांक cpm_uart_init_port(काष्ठा device_node *np,
                              काष्ठा uart_cpm_port *pinfo)
अणु
	स्थिर u32 *data;
	व्योम __iomem *mem, *pram;
	काष्ठा device *dev = pinfo->port.dev;
	पूर्णांक len;
	पूर्णांक ret;
	पूर्णांक i;

	data = of_get_property(np, "clock", शून्य);
	अगर (data) अणु
		काष्ठा clk *clk = clk_get(शून्य, (स्थिर अक्षर*)data);
		अगर (!IS_ERR(clk))
			pinfo->clk = clk;
	पूर्ण
	अगर (!pinfo->clk) अणु
		data = of_get_property(np, "fsl,cpm-brg", &len);
		अगर (!data || len != 4) अणु
			prपूर्णांकk(KERN_ERR "CPM UART %pOFn has no/invalid "
			                "fsl,cpm-brg property.\n", np);
			वापस -EINVAL;
		पूर्ण
		pinfo->brg = *data;
	पूर्ण

	data = of_get_property(np, "fsl,cpm-command", &len);
	अगर (!data || len != 4) अणु
		prपूर्णांकk(KERN_ERR "CPM UART %pOFn has no/invalid "
		                "fsl,cpm-command property.\n", np);
		वापस -EINVAL;
	पूर्ण
	pinfo->command = *data;

	mem = of_iomap(np, 0);
	अगर (!mem)
		वापस -ENOMEM;

	अगर (of_device_is_compatible(np, "fsl,cpm1-scc-uart") ||
	    of_device_is_compatible(np, "fsl,cpm2-scc-uart")) अणु
		pinfo->sccp = mem;
		pinfo->sccup = pram = cpm_uart_map_pram(pinfo, np);
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "fsl,cpm1-smc-uart") ||
	           of_device_is_compatible(np, "fsl,cpm2-smc-uart")) अणु
		pinfo->flags |= FLAG_SMC;
		pinfo->smcp = mem;
		pinfo->smcup = pram = cpm_uart_map_pram(pinfo, np);
	पूर्ण अन्यथा अणु
		ret = -ENODEV;
		जाओ out_mem;
	पूर्ण

	अगर (!pram) अणु
		ret = -ENOMEM;
		जाओ out_mem;
	पूर्ण

	pinfo->tx_nrfअगरos = TX_NUM_FIFO;
	pinfo->tx_fअगरosize = TX_BUF_SIZE;
	pinfo->rx_nrfअगरos = RX_NUM_FIFO;
	pinfo->rx_fअगरosize = RX_BUF_SIZE;

	pinfo->port.uartclk = ppc_proc_freq;
	pinfo->port.mapbase = (अचिन्हित दीर्घ)mem;
	pinfo->port.type = PORT_CPM;
	pinfo->port.ops = &cpm_uart_pops;
	pinfo->port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_CPM_CONSOLE);
	pinfo->port.iotype = UPIO_MEM;
	pinfo->port.fअगरosize = pinfo->tx_nrfअगरos * pinfo->tx_fअगरosize;
	spin_lock_init(&pinfo->port.lock);

	pinfo->port.irq = irq_of_parse_and_map(np, 0);
	अगर (pinfo->port.irq == NO_IRQ) अणु
		ret = -EINVAL;
		जाओ out_pram;
	पूर्ण

	क्रम (i = 0; i < NUM_GPIOS; i++) अणु
		काष्ठा gpio_desc *gpiod;

		pinfo->gpios[i] = शून्य;

		gpiod = devm_gpiod_get_index_optional(dev, शून्य, i, GPIOD_ASIS);

		अगर (IS_ERR(gpiod)) अणु
			ret = PTR_ERR(gpiod);
			जाओ out_irq;
		पूर्ण

		अगर (gpiod) अणु
			अगर (i == GPIO_RTS || i == GPIO_DTR)
				ret = gpiod_direction_output(gpiod, 0);
			अन्यथा
				ret = gpiod_direction_input(gpiod);
			अगर (ret) अणु
				pr_err("can't set direction for gpio #%d: %d\n",
					i, ret);
				जारी;
			पूर्ण
			pinfo->gpios[i] = gpiod;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_PPC_EARLY_DEBUG_CPM
#अगर_घोषित CONFIG_CONSOLE_POLL
	अगर (!udbg_port)
#पूर्ण_अगर
		udbg_अ_दो = शून्य;
#पूर्ण_अगर

	वापस cpm_uart_request_port(&pinfo->port);

out_irq:
	irq_dispose_mapping(pinfo->port.irq);
out_pram:
	cpm_uart_unmap_pram(pinfo, pram);
out_mem:
	iounmap(mem);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SERIAL_CPM_CONSOLE
/*
 *	Prपूर्णांक a string to the serial port trying not to disturb
 *	any possible real use of the port...
 *
 *	Note that this is called with पूर्णांकerrupts alपढ़ोy disabled
 */
अटल व्योम cpm_uart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				   u_पूर्णांक count)
अणु
	काष्ठा uart_cpm_port *pinfo = &cpm_uart_ports[co->index];
	अचिन्हित दीर्घ flags;
	पूर्णांक nolock = oops_in_progress;

	अगर (unlikely(nolock)) अणु
		local_irq_save(flags);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&pinfo->port.lock, flags);
	पूर्ण

	cpm_uart_early_ग_लिखो(pinfo, s, count, true);

	अगर (unlikely(nolock)) अणु
		local_irq_restore(flags);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&pinfo->port.lock, flags);
	पूर्ण
पूर्ण


अटल पूर्णांक __init cpm_uart_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	पूर्णांक baud = 38400;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	पूर्णांक ret;
	काष्ठा uart_cpm_port *pinfo;
	काष्ठा uart_port *port;

	काष्ठा device_node *np;
	पूर्णांक i = 0;

	अगर (co->index >= UART_NR) अणु
		prपूर्णांकk(KERN_ERR "cpm_uart: console index %d too high\n",
		       co->index);
		वापस -ENODEV;
	पूर्ण

	क्रम_each_node_by_type(np, "serial") अणु
		अगर (!of_device_is_compatible(np, "fsl,cpm1-smc-uart") &&
		    !of_device_is_compatible(np, "fsl,cpm1-scc-uart") &&
		    !of_device_is_compatible(np, "fsl,cpm2-smc-uart") &&
		    !of_device_is_compatible(np, "fsl,cpm2-scc-uart"))
			जारी;

		अगर (i++ == co->index)
			अवरोध;
	पूर्ण

	अगर (!np)
		वापस -ENODEV;

	pinfo = &cpm_uart_ports[co->index];

	pinfo->flags |= FLAG_CONSOLE;
	port = &pinfo->port;

	ret = cpm_uart_init_port(np, pinfo);
	of_node_put(np);
	अगर (ret)
		वापस ret;

	अगर (options) अणु
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	पूर्ण अन्यथा अणु
		अगर ((baud = uart_baudrate()) == -1)
			baud = 9600;
	पूर्ण

	अगर (IS_SMC(pinfo)) अणु
		out_be16(&pinfo->smcup->smc_brkcr, 0);
		cpm_line_cr_cmd(pinfo, CPM_CR_STOP_TX);
		clrbits8(&pinfo->smcp->smc_smcm, SMCM_RX | SMCM_TX);
		clrbits16(&pinfo->smcp->smc_smcmr, SMCMR_REN | SMCMR_TEN);
	पूर्ण अन्यथा अणु
		out_be16(&pinfo->sccup->scc_brkcr, 0);
		cpm_line_cr_cmd(pinfo, CPM_CR_GRA_STOP_TX);
		clrbits16(&pinfo->sccp->scc_sccm, UART_SCCM_TX | UART_SCCM_RX);
		clrbits32(&pinfo->sccp->scc_gsmrl, SCC_GSMRL_ENR | SCC_GSMRL_ENT);
	पूर्ण

	ret = cpm_uart_allocbuf(pinfo, 1);

	अगर (ret)
		वापस ret;

	cpm_uart_initbd(pinfo);

	अगर (IS_SMC(pinfo))
		cpm_uart_init_smc(pinfo);
	अन्यथा
		cpm_uart_init_scc(pinfo);

	uart_set_options(port, co, baud, parity, bits, flow);
	cpm_line_cr_cmd(pinfo, CPM_CR_RESTART_TX);

#अगर_घोषित CONFIG_CONSOLE_POLL
	अगर (!udbg_port) अणु
		udbg_port = &pinfo->port;
		udbg_अ_दो = udbg_cpm_अ_दो;
		udbg_अ_लो = udbg_cpm_अ_लो;
		udbg_अ_लो_poll = udbg_cpm_अ_लो_poll;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल काष्ठा uart_driver cpm_reg;
अटल काष्ठा console cpm_scc_uart_console = अणु
	.name		= "ttyCPM",
	.ग_लिखो		= cpm_uart_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= cpm_uart_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &cpm_reg,
पूर्ण;

अटल पूर्णांक __init cpm_uart_console_init(व्योम)
अणु
	cpm_muram_init();
	रेजिस्टर_console(&cpm_scc_uart_console);
	वापस 0;
पूर्ण

console_initcall(cpm_uart_console_init);

#घोषणा CPM_UART_CONSOLE	&cpm_scc_uart_console
#अन्यथा
#घोषणा CPM_UART_CONSOLE	शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver cpm_reg = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "ttyCPM",
	.dev_name	= "ttyCPM",
	.major		= SERIAL_CPM_MAJOR,
	.minor		= SERIAL_CPM_MINOR,
	.cons		= CPM_UART_CONSOLE,
	.nr		= UART_NR,
पूर्ण;

अटल पूर्णांक probe_index;

अटल पूर्णांक cpm_uart_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	पूर्णांक index = probe_index++;
	काष्ठा uart_cpm_port *pinfo = &cpm_uart_ports[index];
	पूर्णांक ret;

	pinfo->port.line = index;

	अगर (index >= UART_NR)
		वापस -ENODEV;

	platक्रमm_set_drvdata(ofdev, pinfo);

	/* initialize the device poपूर्णांकer क्रम the port */
	pinfo->port.dev = &ofdev->dev;

	ret = cpm_uart_init_port(ofdev->dev.of_node, pinfo);
	अगर (ret)
		वापस ret;

	वापस uart_add_one_port(&cpm_reg, &pinfo->port);
पूर्ण

अटल पूर्णांक cpm_uart_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा uart_cpm_port *pinfo = platक्रमm_get_drvdata(ofdev);
	वापस uart_हटाओ_one_port(&cpm_reg, &pinfo->port);
पूर्ण

अटल स्थिर काष्ठा of_device_id cpm_uart_match[] = अणु
	अणु
		.compatible = "fsl,cpm1-smc-uart",
	पूर्ण,
	अणु
		.compatible = "fsl,cpm1-scc-uart",
	पूर्ण,
	अणु
		.compatible = "fsl,cpm2-smc-uart",
	पूर्ण,
	अणु
		.compatible = "fsl,cpm2-scc-uart",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cpm_uart_match);

अटल काष्ठा platक्रमm_driver cpm_uart_driver = अणु
	.driver = अणु
		.name = "cpm_uart",
		.of_match_table = cpm_uart_match,
	पूर्ण,
	.probe = cpm_uart_probe,
	.हटाओ = cpm_uart_हटाओ,
 पूर्ण;

अटल पूर्णांक __init cpm_uart_init(व्योम)
अणु
	पूर्णांक ret = uart_रेजिस्टर_driver(&cpm_reg);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&cpm_uart_driver);
	अगर (ret)
		uart_unरेजिस्टर_driver(&cpm_reg);

	वापस ret;
पूर्ण

अटल व्योम __निकास cpm_uart_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&cpm_uart_driver);
	uart_unरेजिस्टर_driver(&cpm_reg);
पूर्ण

module_init(cpm_uart_init);
module_निकास(cpm_uart_निकास);

MODULE_AUTHOR("Kumar Gala/Antoniou Pantelis");
MODULE_DESCRIPTION("CPM SCC/SMC port driver $Revision: 0.01 $");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CHARDEV(SERIAL_CPM_MAJOR, SERIAL_CPM_MINOR);
