<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Cadence UART driver (found in Xilinx Zynq)
 *
 * 2011 - 2014 (C) Xilinx Inc.
 *
 * This driver has originally been pushed by Xilinx using a Zynq-bअक्रमing. This
 * still shows in the naming of this file, the kconfig symbols and some symbols
 * in the code.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial.h>
#समावेश <linux/console.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/clk.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/iopoll.h>

#घोषणा CDNS_UART_TTY_NAME	"ttyPS"
#घोषणा CDNS_UART_NAME		"xuartps"
#घोषणा CDNS_UART_MAJOR		0	/* use dynamic node allocation */
#घोषणा CDNS_UART_MINOR		0	/* works best with devपंचांगpfs */
#घोषणा CDNS_UART_NR_PORTS	16
#घोषणा CDNS_UART_FIFO_SIZE	64	/* FIFO size */
#घोषणा CDNS_UART_REGISTER_SPACE	0x1000
#घोषणा TX_TIMEOUT		500000

/* Rx Trigger level */
अटल पूर्णांक rx_trigger_level = 56;
module_param(rx_trigger_level, uपूर्णांक, 0444);
MODULE_PARM_DESC(rx_trigger_level, "Rx trigger level, 1-63 bytes");

/* Rx Timeout */
अटल पूर्णांक rx_समयout = 10;
module_param(rx_समयout, uपूर्णांक, 0444);
MODULE_PARM_DESC(rx_समयout, "Rx timeout, 1-255");

/* Register offsets क्रम the UART. */
#घोषणा CDNS_UART_CR		0x00  /* Control Register */
#घोषणा CDNS_UART_MR		0x04  /* Mode Register */
#घोषणा CDNS_UART_IER		0x08  /* Interrupt Enable */
#घोषणा CDNS_UART_IDR		0x0C  /* Interrupt Disable */
#घोषणा CDNS_UART_IMR		0x10  /* Interrupt Mask */
#घोषणा CDNS_UART_ISR		0x14  /* Interrupt Status */
#घोषणा CDNS_UART_BAUDGEN	0x18  /* Baud Rate Generator */
#घोषणा CDNS_UART_RXTOUT	0x1C  /* RX Timeout */
#घोषणा CDNS_UART_RXWM		0x20  /* RX FIFO Trigger Level */
#घोषणा CDNS_UART_MODEMCR	0x24  /* Modem Control */
#घोषणा CDNS_UART_MODEMSR	0x28  /* Modem Status */
#घोषणा CDNS_UART_SR		0x2C  /* Channel Status */
#घोषणा CDNS_UART_FIFO		0x30  /* FIFO */
#घोषणा CDNS_UART_BAUDDIV	0x34  /* Baud Rate Divider */
#घोषणा CDNS_UART_FLOWDEL	0x38  /* Flow Delay */
#घोषणा CDNS_UART_IRRX_PWIDTH	0x3C  /* IR Min Received Pulse Width */
#घोषणा CDNS_UART_IRTX_PWIDTH	0x40  /* IR Transmitted pulse Width */
#घोषणा CDNS_UART_TXWM		0x44  /* TX FIFO Trigger Level */
#घोषणा CDNS_UART_RXBS		0x48  /* RX FIFO byte status रेजिस्टर */

/* Control Register Bit Definitions */
#घोषणा CDNS_UART_CR_STOPBRK	0x00000100  /* Stop TX अवरोध */
#घोषणा CDNS_UART_CR_STARTBRK	0x00000080  /* Set TX अवरोध */
#घोषणा CDNS_UART_CR_TX_DIS	0x00000020  /* TX disabled. */
#घोषणा CDNS_UART_CR_TX_EN	0x00000010  /* TX enabled */
#घोषणा CDNS_UART_CR_RX_DIS	0x00000008  /* RX disabled. */
#घोषणा CDNS_UART_CR_RX_EN	0x00000004  /* RX enabled */
#घोषणा CDNS_UART_CR_TXRST	0x00000002  /* TX logic reset */
#घोषणा CDNS_UART_CR_RXRST	0x00000001  /* RX logic reset */
#घोषणा CDNS_UART_CR_RST_TO	0x00000040  /* Restart Timeout Counter */
#घोषणा CDNS_UART_RXBS_PARITY    0x00000001 /* Parity error status */
#घोषणा CDNS_UART_RXBS_FRAMING   0x00000002 /* Framing error status */
#घोषणा CDNS_UART_RXBS_BRK       0x00000004 /* Overrun error status */

/*
 * Mode Register:
 * The mode रेजिस्टर (MR) defines the mode of transfer as well as the data
 * क्रमmat. If this रेजिस्टर is modअगरied during transmission or reception,
 * data validity cannot be guaranteed.
 */
#घोषणा CDNS_UART_MR_CLKSEL		0x00000001  /* Pre-scalar selection */
#घोषणा CDNS_UART_MR_CHMODE_L_LOOP	0x00000200  /* Local loop back mode */
#घोषणा CDNS_UART_MR_CHMODE_NORM	0x00000000  /* Normal mode */
#घोषणा CDNS_UART_MR_CHMODE_MASK	0x00000300  /* Mask क्रम mode bits */

#घोषणा CDNS_UART_MR_STOPMODE_2_BIT	0x00000080  /* 2 stop bits */
#घोषणा CDNS_UART_MR_STOPMODE_1_BIT	0x00000000  /* 1 stop bit */

#घोषणा CDNS_UART_MR_PARITY_NONE	0x00000020  /* No parity mode */
#घोषणा CDNS_UART_MR_PARITY_MARK	0x00000018  /* Mark parity mode */
#घोषणा CDNS_UART_MR_PARITY_SPACE	0x00000010  /* Space parity mode */
#घोषणा CDNS_UART_MR_PARITY_ODD		0x00000008  /* Odd parity mode */
#घोषणा CDNS_UART_MR_PARITY_EVEN	0x00000000  /* Even parity mode */

#घोषणा CDNS_UART_MR_CHARLEN_6_BIT	0x00000006  /* 6 bits data */
#घोषणा CDNS_UART_MR_CHARLEN_7_BIT	0x00000004  /* 7 bits data */
#घोषणा CDNS_UART_MR_CHARLEN_8_BIT	0x00000000  /* 8 bits data */

/*
 * Interrupt Registers:
 * Interrupt control logic uses the पूर्णांकerrupt enable रेजिस्टर (IER) and the
 * पूर्णांकerrupt disable रेजिस्टर (IDR) to set the value of the bits in the
 * पूर्णांकerrupt mask रेजिस्टर (IMR). The IMR determines whether to pass an
 * पूर्णांकerrupt to the पूर्णांकerrupt status रेजिस्टर (ISR).
 * Writing a 1 to IER Enables an पूर्णांकerrupt, writing a 1 to IDR disables an
 * पूर्णांकerrupt. IMR and ISR are पढ़ो only, and IER and IDR are ग_लिखो only.
 * Reading either IER or IDR वापसs 0x00.
 * All four रेजिस्टरs have the same bit definitions.
 */
#घोषणा CDNS_UART_IXR_TOUT	0x00000100 /* RX Timeout error पूर्णांकerrupt */
#घोषणा CDNS_UART_IXR_PARITY	0x00000080 /* Parity error पूर्णांकerrupt */
#घोषणा CDNS_UART_IXR_FRAMING	0x00000040 /* Framing error पूर्णांकerrupt */
#घोषणा CDNS_UART_IXR_OVERRUN	0x00000020 /* Overrun error पूर्णांकerrupt */
#घोषणा CDNS_UART_IXR_TXFULL	0x00000010 /* TX FIFO Full पूर्णांकerrupt */
#घोषणा CDNS_UART_IXR_TXEMPTY	0x00000008 /* TX FIFO empty पूर्णांकerrupt */
#घोषणा CDNS_UART_ISR_RXEMPTY	0x00000002 /* RX FIFO empty पूर्णांकerrupt */
#घोषणा CDNS_UART_IXR_RXTRIG	0x00000001 /* RX FIFO trigger पूर्णांकerrupt */
#घोषणा CDNS_UART_IXR_RXFULL	0x00000004 /* RX FIFO full पूर्णांकerrupt. */
#घोषणा CDNS_UART_IXR_RXEMPTY	0x00000002 /* RX FIFO empty पूर्णांकerrupt. */
#घोषणा CDNS_UART_IXR_RXMASK	0x000021e7 /* Valid RX bit mask */

	/*
	 * Do not enable parity error पूर्णांकerrupt क्रम the following
	 * reason: When parity error पूर्णांकerrupt is enabled, each Rx
	 * parity error always results in 2 events. The first one
	 * being parity error पूर्णांकerrupt and the second one with a
	 * proper Rx पूर्णांकerrupt with the incoming data.  Disabling
	 * parity error पूर्णांकerrupt ensures better handling of parity
	 * error events. With this change, क्रम a parity error हाल, we
	 * get a Rx पूर्णांकerrupt with parity error set in ISR रेजिस्टर
	 * and we still handle parity errors in the desired way.
	 */

#घोषणा CDNS_UART_RX_IRQS	(CDNS_UART_IXR_FRAMING | \
				 CDNS_UART_IXR_OVERRUN | \
				 CDNS_UART_IXR_RXTRIG |	 \
				 CDNS_UART_IXR_TOUT)

/* Goes in पढ़ो_status_mask क्रम अवरोध detection as the HW करोesn't करो it*/
#घोषणा CDNS_UART_IXR_BRK	0x00002000

#घोषणा CDNS_UART_RXBS_SUPPORT BIT(1)
/*
 * Modem Control रेजिस्टर:
 * The पढ़ो/ग_लिखो Modem Control रेजिस्टर controls the पूर्णांकerface with the modem
 * or data set, or a peripheral device emulating a modem.
 */
#घोषणा CDNS_UART_MODEMCR_FCM	0x00000020 /* Automatic flow control mode */
#घोषणा CDNS_UART_MODEMCR_RTS	0x00000002 /* Request to send output control */
#घोषणा CDNS_UART_MODEMCR_DTR	0x00000001 /* Data Terminal Ready */

/*
 * Modem Status रेजिस्टर:
 * The पढ़ो/ग_लिखो Modem Status रेजिस्टर reports the पूर्णांकerface with the modem
 * or data set, or a peripheral device emulating a modem.
 */
#घोषणा CDNS_UART_MODEMSR_DCD	BIT(7) /* Data Carrier Detect */
#घोषणा CDNS_UART_MODEMSR_RI	BIT(6) /* Ting Indicator */
#घोषणा CDNS_UART_MODEMSR_DSR	BIT(5) /* Data Set Ready */
#घोषणा CDNS_UART_MODEMSR_CTS	BIT(4) /* Clear To Send */

/*
 * Channel Status Register:
 * The channel status रेजिस्टर (CSR) is provided to enable the control logic
 * to monitor the status of bits in the channel पूर्णांकerrupt status रेजिस्टर,
 * even अगर these are masked out by the पूर्णांकerrupt mask रेजिस्टर.
 */
#घोषणा CDNS_UART_SR_RXEMPTY	0x00000002 /* RX FIFO empty */
#घोषणा CDNS_UART_SR_TXEMPTY	0x00000008 /* TX FIFO empty */
#घोषणा CDNS_UART_SR_TXFULL	0x00000010 /* TX FIFO full */
#घोषणा CDNS_UART_SR_RXTRIG	0x00000001 /* Rx Trigger */
#घोषणा CDNS_UART_SR_TACTIVE	0x00000800 /* TX state machine active */

/* baud भागiders min/max values */
#घोषणा CDNS_UART_BDIV_MIN	4
#घोषणा CDNS_UART_BDIV_MAX	255
#घोषणा CDNS_UART_CD_MAX	65535
#घोषणा UART_AUTOSUSPEND_TIMEOUT	3000

/**
 * काष्ठा cdns_uart - device data
 * @port:		Poपूर्णांकer to the UART port
 * @uartclk:		Reference घड़ी
 * @pclk:		APB घड़ी
 * @cdns_uart_driver:	Poपूर्णांकer to UART driver
 * @baud:		Current baud rate
 * @clk_rate_change_nb:	Notअगरier block क्रम घड़ी changes
 * @quirks:		Flags क्रम RXBS support.
 * @cts_override:	Modem control state override
 */
काष्ठा cdns_uart अणु
	काष्ठा uart_port	*port;
	काष्ठा clk		*uartclk;
	काष्ठा clk		*pclk;
	काष्ठा uart_driver	*cdns_uart_driver;
	अचिन्हित पूर्णांक		baud;
	काष्ठा notअगरier_block	clk_rate_change_nb;
	u32			quirks;
	bool cts_override;
पूर्ण;
काष्ठा cdns_platक्रमm_data अणु
	u32 quirks;
पूर्ण;
#घोषणा to_cdns_uart(_nb) container_of(_nb, काष्ठा cdns_uart, \
		clk_rate_change_nb)

/**
 * cdns_uart_handle_rx - Handle the received bytes aदीर्घ with Rx errors.
 * @dev_id: Id of the UART port
 * @isrstatus: The पूर्णांकerrupt status रेजिस्टर value as पढ़ो
 * Return: None
 */
अटल व्योम cdns_uart_handle_rx(व्योम *dev_id, अचिन्हित पूर्णांक isrstatus)
अणु
	काष्ठा uart_port *port = (काष्ठा uart_port *)dev_id;
	काष्ठा cdns_uart *cdns_uart = port->निजी_data;
	अचिन्हित पूर्णांक data;
	अचिन्हित पूर्णांक rxbs_status = 0;
	अचिन्हित पूर्णांक status_mask;
	अचिन्हित पूर्णांक framerrprocessed = 0;
	अक्षर status = TTY_NORMAL;
	bool is_rxbs_support;

	is_rxbs_support = cdns_uart->quirks & CDNS_UART_RXBS_SUPPORT;

	जबतक ((पढ़ोl(port->membase + CDNS_UART_SR) &
		CDNS_UART_SR_RXEMPTY) != CDNS_UART_SR_RXEMPTY) अणु
		अगर (is_rxbs_support)
			rxbs_status = पढ़ोl(port->membase + CDNS_UART_RXBS);
		data = पढ़ोl(port->membase + CDNS_UART_FIFO);
		port->icount.rx++;
		/*
		 * There is no hardware अवरोध detection in Zynq, so we पूर्णांकerpret
		 * framing error with all-zeros data as a अवरोध sequence.
		 * Most of the समय, there's another non-zero byte at the
		 * end of the sequence.
		 */
		अगर (!is_rxbs_support && (isrstatus & CDNS_UART_IXR_FRAMING)) अणु
			अगर (!data) अणु
				port->पढ़ो_status_mask |= CDNS_UART_IXR_BRK;
				framerrprocessed = 1;
				जारी;
			पूर्ण
		पूर्ण
		अगर (is_rxbs_support && (rxbs_status & CDNS_UART_RXBS_BRK)) अणु
			port->icount.brk++;
			status = TTY_BREAK;
			अगर (uart_handle_अवरोध(port))
				जारी;
		पूर्ण

		isrstatus &= port->पढ़ो_status_mask;
		isrstatus &= ~port->ignore_status_mask;
		status_mask = port->पढ़ो_status_mask;
		status_mask &= ~port->ignore_status_mask;

		अगर (data &&
		    (port->पढ़ो_status_mask & CDNS_UART_IXR_BRK)) अणु
			port->पढ़ो_status_mask &= ~CDNS_UART_IXR_BRK;
			port->icount.brk++;
			अगर (uart_handle_अवरोध(port))
				जारी;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(port, data))
			जारी;

		अगर (is_rxbs_support) अणु
			अगर ((rxbs_status & CDNS_UART_RXBS_PARITY)
			    && (status_mask & CDNS_UART_IXR_PARITY)) अणु
				port->icount.parity++;
				status = TTY_PARITY;
			पूर्ण
			अगर ((rxbs_status & CDNS_UART_RXBS_FRAMING)
			    && (status_mask & CDNS_UART_IXR_PARITY)) अणु
				port->icount.frame++;
				status = TTY_FRAME;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (isrstatus & CDNS_UART_IXR_PARITY) अणु
				port->icount.parity++;
				status = TTY_PARITY;
			पूर्ण
			अगर ((isrstatus & CDNS_UART_IXR_FRAMING) &&
			    !framerrprocessed) अणु
				port->icount.frame++;
				status = TTY_FRAME;
			पूर्ण
		पूर्ण
		अगर (isrstatus & CDNS_UART_IXR_OVERRUN) अणु
			port->icount.overrun++;
			tty_insert_flip_अक्षर(&port->state->port, 0,
					     TTY_OVERRUN);
		पूर्ण
		tty_insert_flip_अक्षर(&port->state->port, data, status);
		isrstatus = 0;
	पूर्ण

	tty_flip_buffer_push(&port->state->port);
पूर्ण

/**
 * cdns_uart_handle_tx - Handle the bytes to be Txed.
 * @dev_id: Id of the UART port
 * Return: None
 */
अटल व्योम cdns_uart_handle_tx(व्योम *dev_id)
अणु
	काष्ठा uart_port *port = (काष्ठा uart_port *)dev_id;
	अचिन्हित पूर्णांक numbytes;

	अगर (uart_circ_empty(&port->state->xmit)) अणु
		ग_लिखोl(CDNS_UART_IXR_TXEMPTY, port->membase + CDNS_UART_IDR);
	पूर्ण अन्यथा अणु
		numbytes = port->fअगरosize;
		जबतक (numbytes && !uart_circ_empty(&port->state->xmit) &&
		       !(पढ़ोl(port->membase + CDNS_UART_SR) &
						CDNS_UART_SR_TXFULL)) अणु
			/*
			 * Get the data from the UART circular buffer
			 * and ग_लिखो it to the cdns_uart's TX_FIFO
			 * रेजिस्टर.
			 */
			ग_लिखोl(
				port->state->xmit.buf[port->state->xmit.tail],
					port->membase + CDNS_UART_FIFO);

			port->icount.tx++;

			/*
			 * Adjust the tail of the UART buffer and wrap
			 * the buffer अगर it reaches limit.
			 */
			port->state->xmit.tail =
				(port->state->xmit.tail + 1) &
					(UART_XMIT_SIZE - 1);

			numbytes--;
		पूर्ण

		अगर (uart_circ_अक्षरs_pending(
				&port->state->xmit) < WAKEUP_CHARS)
			uart_ग_लिखो_wakeup(port);
	पूर्ण
पूर्ण

/**
 * cdns_uart_isr - Interrupt handler
 * @irq: Irq number
 * @dev_id: Id of the port
 *
 * Return: IRQHANDLED
 */
अटल irqवापस_t cdns_uart_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = (काष्ठा uart_port *)dev_id;
	अचिन्हित पूर्णांक isrstatus;

	spin_lock(&port->lock);

	/* Read the पूर्णांकerrupt status रेजिस्टर to determine which
	 * पूर्णांकerrupt(s) is/are active and clear them.
	 */
	isrstatus = पढ़ोl(port->membase + CDNS_UART_ISR);
	ग_लिखोl(isrstatus, port->membase + CDNS_UART_ISR);

	अगर (isrstatus & CDNS_UART_IXR_TXEMPTY) अणु
		cdns_uart_handle_tx(dev_id);
		isrstatus &= ~CDNS_UART_IXR_TXEMPTY;
	पूर्ण

	/*
	 * Skip RX processing अगर RX is disabled as RXEMPTY will never be set
	 * as पढ़ो bytes will not be हटाओd from the FIFO.
	 */
	अगर (isrstatus & CDNS_UART_IXR_RXMASK &&
	    !(पढ़ोl(port->membase + CDNS_UART_CR) & CDNS_UART_CR_RX_DIS))
		cdns_uart_handle_rx(dev_id, isrstatus);

	spin_unlock(&port->lock);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * cdns_uart_calc_baud_भागs - Calculate baud rate भागisors
 * @clk: UART module input घड़ी
 * @baud: Desired baud rate
 * @rbभाग: BDIV value (वापस value)
 * @rcd: CD value (वापस value)
 * @भाग8: Value क्रम clk_sel bit in mod (वापस value)
 * Return: baud rate, requested baud when possible, or actual baud when there
 *	was too much error, zero अगर no valid भागisors are found.
 *
 * Formula to obtain baud rate is
 *	baud_tx/rx rate = clk/CD * (BDIV + 1)
 *	input_clk = (Uart User Defined Clock or Apb Clock)
 *		depends on UCLKEN in MR Reg
 *	clk = input_clk or input_clk/8;
 *		depends on CLKS in MR reg
 *	CD and BDIV depends on values in
 *			baud rate generate रेजिस्टर
 *			baud rate घड़ी भागisor रेजिस्टर
 */
अटल अचिन्हित पूर्णांक cdns_uart_calc_baud_भागs(अचिन्हित पूर्णांक clk,
		अचिन्हित पूर्णांक baud, u32 *rbभाग, u32 *rcd, पूर्णांक *भाग8)
अणु
	u32 cd, bभाग;
	अचिन्हित पूर्णांक calc_baud;
	अचिन्हित पूर्णांक bestbaud = 0;
	अचिन्हित पूर्णांक bauderror;
	अचिन्हित पूर्णांक besterror = ~0;

	अगर (baud < clk / ((CDNS_UART_BDIV_MAX + 1) * CDNS_UART_CD_MAX)) अणु
		*भाग8 = 1;
		clk /= 8;
	पूर्ण अन्यथा अणु
		*भाग8 = 0;
	पूर्ण

	क्रम (bभाग = CDNS_UART_BDIV_MIN; bभाग <= CDNS_UART_BDIV_MAX; bभाग++) अणु
		cd = DIV_ROUND_CLOSEST(clk, baud * (bभाग + 1));
		अगर (cd < 1 || cd > CDNS_UART_CD_MAX)
			जारी;

		calc_baud = clk / (cd * (bभाग + 1));

		अगर (baud > calc_baud)
			bauderror = baud - calc_baud;
		अन्यथा
			bauderror = calc_baud - baud;

		अगर (besterror > bauderror) अणु
			*rbभाग = bभाग;
			*rcd = cd;
			bestbaud = calc_baud;
			besterror = bauderror;
		पूर्ण
	पूर्ण
	/* use the values when percent error is acceptable */
	अगर (((besterror * 100) / baud) < 3)
		bestbaud = baud;

	वापस bestbaud;
पूर्ण

/**
 * cdns_uart_set_baud_rate - Calculate and set the baud rate
 * @port: Handle to the uart port काष्ठाure
 * @baud: Baud rate to set
 * Return: baud rate, requested baud when possible, or actual baud when there
 *	   was too much error, zero अगर no valid भागisors are found.
 */
अटल अचिन्हित पूर्णांक cdns_uart_set_baud_rate(काष्ठा uart_port *port,
		अचिन्हित पूर्णांक baud)
अणु
	अचिन्हित पूर्णांक calc_baud;
	u32 cd = 0, bभाग = 0;
	u32 mreg;
	पूर्णांक भाग8;
	काष्ठा cdns_uart *cdns_uart = port->निजी_data;

	calc_baud = cdns_uart_calc_baud_भागs(port->uartclk, baud, &bभाग, &cd,
			&भाग8);

	/* Write new भागisors to hardware */
	mreg = पढ़ोl(port->membase + CDNS_UART_MR);
	अगर (भाग8)
		mreg |= CDNS_UART_MR_CLKSEL;
	अन्यथा
		mreg &= ~CDNS_UART_MR_CLKSEL;
	ग_लिखोl(mreg, port->membase + CDNS_UART_MR);
	ग_लिखोl(cd, port->membase + CDNS_UART_BAUDGEN);
	ग_लिखोl(bभाग, port->membase + CDNS_UART_BAUDDIV);
	cdns_uart->baud = baud;

	वापस calc_baud;
पूर्ण

#अगर_घोषित CONFIG_COMMON_CLK
/**
 * cdns_uart_clk_notitअगरer_cb - Clock notअगरier callback
 * @nb:		Notअगरier block
 * @event:	Notअगरy event
 * @data:	Notअगरier data
 * Return:	NOTIFY_OK or NOTIFY_DONE on success, NOTIFY_BAD on error.
 */
अटल पूर्णांक cdns_uart_clk_notअगरier_cb(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ event, व्योम *data)
अणु
	u32 ctrl_reg;
	काष्ठा uart_port *port;
	पूर्णांक locked = 0;
	काष्ठा clk_notअगरier_data *ndata = data;
	अचिन्हित दीर्घ flags = 0;
	काष्ठा cdns_uart *cdns_uart = to_cdns_uart(nb);

	port = cdns_uart->port;
	अगर (port->suspended)
		वापस NOTIFY_OK;

	चयन (event) अणु
	हाल PRE_RATE_CHANGE:
	अणु
		u32 bभाग, cd;
		पूर्णांक भाग8;

		/*
		 * Find out अगर current baud-rate can be achieved with new घड़ी
		 * frequency.
		 */
		अगर (!cdns_uart_calc_baud_भागs(ndata->new_rate, cdns_uart->baud,
					&bभाग, &cd, &भाग8)) अणु
			dev_warn(port->dev, "clock rate change rejected\n");
			वापस NOTIFY_BAD;
		पूर्ण

		spin_lock_irqsave(&cdns_uart->port->lock, flags);

		/* Disable the TX and RX to set baud rate */
		ctrl_reg = पढ़ोl(port->membase + CDNS_UART_CR);
		ctrl_reg |= CDNS_UART_CR_TX_DIS | CDNS_UART_CR_RX_DIS;
		ग_लिखोl(ctrl_reg, port->membase + CDNS_UART_CR);

		spin_unlock_irqrestore(&cdns_uart->port->lock, flags);

		वापस NOTIFY_OK;
	पूर्ण
	हाल POST_RATE_CHANGE:
		/*
		 * Set clk भागiders to generate correct baud with new घड़ी
		 * frequency.
		 */

		spin_lock_irqsave(&cdns_uart->port->lock, flags);

		locked = 1;
		port->uartclk = ndata->new_rate;

		cdns_uart->baud = cdns_uart_set_baud_rate(cdns_uart->port,
				cdns_uart->baud);
		fallthrough;
	हाल ABORT_RATE_CHANGE:
		अगर (!locked)
			spin_lock_irqsave(&cdns_uart->port->lock, flags);

		/* Set TX/RX Reset */
		ctrl_reg = पढ़ोl(port->membase + CDNS_UART_CR);
		ctrl_reg |= CDNS_UART_CR_TXRST | CDNS_UART_CR_RXRST;
		ग_लिखोl(ctrl_reg, port->membase + CDNS_UART_CR);

		जबतक (पढ़ोl(port->membase + CDNS_UART_CR) &
				(CDNS_UART_CR_TXRST | CDNS_UART_CR_RXRST))
			cpu_relax();

		/*
		 * Clear the RX disable and TX disable bits and then set the TX
		 * enable bit and RX enable bit to enable the transmitter and
		 * receiver.
		 */
		ग_लिखोl(rx_समयout, port->membase + CDNS_UART_RXTOUT);
		ctrl_reg = पढ़ोl(port->membase + CDNS_UART_CR);
		ctrl_reg &= ~(CDNS_UART_CR_TX_DIS | CDNS_UART_CR_RX_DIS);
		ctrl_reg |= CDNS_UART_CR_TX_EN | CDNS_UART_CR_RX_EN;
		ग_लिखोl(ctrl_reg, port->membase + CDNS_UART_CR);

		spin_unlock_irqrestore(&cdns_uart->port->lock, flags);

		वापस NOTIFY_OK;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/**
 * cdns_uart_start_tx -  Start transmitting bytes
 * @port: Handle to the uart port काष्ठाure
 */
अटल व्योम cdns_uart_start_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक status;

	अगर (uart_tx_stopped(port))
		वापस;

	/*
	 * Set the TX enable bit and clear the TX disable bit to enable the
	 * transmitter.
	 */
	status = पढ़ोl(port->membase + CDNS_UART_CR);
	status &= ~CDNS_UART_CR_TX_DIS;
	status |= CDNS_UART_CR_TX_EN;
	ग_लिखोl(status, port->membase + CDNS_UART_CR);

	अगर (uart_circ_empty(&port->state->xmit))
		वापस;

	cdns_uart_handle_tx(port);

	ग_लिखोl(CDNS_UART_IXR_TXEMPTY, port->membase + CDNS_UART_ISR);
	/* Enable the TX Empty पूर्णांकerrupt */
	ग_लिखोl(CDNS_UART_IXR_TXEMPTY, port->membase + CDNS_UART_IER);
पूर्ण

/**
 * cdns_uart_stop_tx - Stop TX
 * @port: Handle to the uart port काष्ठाure
 */
अटल व्योम cdns_uart_stop_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक regval;

	regval = पढ़ोl(port->membase + CDNS_UART_CR);
	regval |= CDNS_UART_CR_TX_DIS;
	/* Disable the transmitter */
	ग_लिखोl(regval, port->membase + CDNS_UART_CR);
पूर्ण

/**
 * cdns_uart_stop_rx - Stop RX
 * @port: Handle to the uart port काष्ठाure
 */
अटल व्योम cdns_uart_stop_rx(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक regval;

	/* Disable RX IRQs */
	ग_लिखोl(CDNS_UART_RX_IRQS, port->membase + CDNS_UART_IDR);

	/* Disable the receiver */
	regval = पढ़ोl(port->membase + CDNS_UART_CR);
	regval |= CDNS_UART_CR_RX_DIS;
	ग_लिखोl(regval, port->membase + CDNS_UART_CR);
पूर्ण

/**
 * cdns_uart_tx_empty -  Check whether TX is empty
 * @port: Handle to the uart port काष्ठाure
 *
 * Return: TIOCSER_TEMT on success, 0 otherwise
 */
अटल अचिन्हित पूर्णांक cdns_uart_tx_empty(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक status;

	status = पढ़ोl(port->membase + CDNS_UART_SR) &
		       (CDNS_UART_SR_TXEMPTY | CDNS_UART_SR_TACTIVE);
	वापस (status == CDNS_UART_SR_TXEMPTY) ? TIOCSER_TEMT : 0;
पूर्ण

/**
 * cdns_uart_अवरोध_ctl - Based on the input ctl we have to start or stop
 *			transmitting अक्षर अवरोधs
 * @port: Handle to the uart port काष्ठाure
 * @ctl: Value based on which start or stop decision is taken
 */
अटल व्योम cdns_uart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक ctl)
अणु
	अचिन्हित पूर्णांक status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	status = पढ़ोl(port->membase + CDNS_UART_CR);

	अगर (ctl == -1)
		ग_लिखोl(CDNS_UART_CR_STARTBRK | status,
				port->membase + CDNS_UART_CR);
	अन्यथा अणु
		अगर ((status & CDNS_UART_CR_STOPBRK) == 0)
			ग_लिखोl(CDNS_UART_CR_STOPBRK | status,
					port->membase + CDNS_UART_CR);
	पूर्ण
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/**
 * cdns_uart_set_termios - termios operations, handling data length, parity,
 *				stop bits, flow control, baud rate
 * @port: Handle to the uart port काष्ठाure
 * @termios: Handle to the input termios काष्ठाure
 * @old: Values of the previously saved termios काष्ठाure
 */
अटल व्योम cdns_uart_set_termios(काष्ठा uart_port *port,
				काष्ठा ktermios *termios, काष्ठा ktermios *old)
अणु
	u32 cval = 0;
	अचिन्हित पूर्णांक baud, minbaud, maxbaud;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ctrl_reg, mode_reg;

	spin_lock_irqsave(&port->lock, flags);

	/* Disable the TX and RX to set baud rate */
	ctrl_reg = पढ़ोl(port->membase + CDNS_UART_CR);
	ctrl_reg |= CDNS_UART_CR_TX_DIS | CDNS_UART_CR_RX_DIS;
	ग_लिखोl(ctrl_reg, port->membase + CDNS_UART_CR);

	/*
	 * Min baud rate = 6bps and Max Baud Rate is 10Mbps क्रम 100Mhz clk
	 * min and max baud should be calculated here based on port->uartclk.
	 * this way we get a valid baud and can safely call set_baud()
	 */
	minbaud = port->uartclk /
			((CDNS_UART_BDIV_MAX + 1) * CDNS_UART_CD_MAX * 8);
	maxbaud = port->uartclk / (CDNS_UART_BDIV_MIN + 1);
	baud = uart_get_baud_rate(port, termios, old, minbaud, maxbaud);
	baud = cdns_uart_set_baud_rate(port, baud);
	अगर (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);

	/* Update the per-port समयout. */
	uart_update_समयout(port, termios->c_cflag, baud);

	/* Set TX/RX Reset */
	ctrl_reg = पढ़ोl(port->membase + CDNS_UART_CR);
	ctrl_reg |= CDNS_UART_CR_TXRST | CDNS_UART_CR_RXRST;
	ग_लिखोl(ctrl_reg, port->membase + CDNS_UART_CR);

	जबतक (पढ़ोl(port->membase + CDNS_UART_CR) &
		(CDNS_UART_CR_TXRST | CDNS_UART_CR_RXRST))
		cpu_relax();

	/*
	 * Clear the RX disable and TX disable bits and then set the TX enable
	 * bit and RX enable bit to enable the transmitter and receiver.
	 */
	ctrl_reg = पढ़ोl(port->membase + CDNS_UART_CR);
	ctrl_reg &= ~(CDNS_UART_CR_TX_DIS | CDNS_UART_CR_RX_DIS);
	ctrl_reg |= CDNS_UART_CR_TX_EN | CDNS_UART_CR_RX_EN;
	ग_लिखोl(ctrl_reg, port->membase + CDNS_UART_CR);

	ग_लिखोl(rx_समयout, port->membase + CDNS_UART_RXTOUT);

	port->पढ़ो_status_mask = CDNS_UART_IXR_TXEMPTY | CDNS_UART_IXR_RXTRIG |
			CDNS_UART_IXR_OVERRUN | CDNS_UART_IXR_TOUT;
	port->ignore_status_mask = 0;

	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= CDNS_UART_IXR_PARITY |
		CDNS_UART_IXR_FRAMING;

	अगर (termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= CDNS_UART_IXR_PARITY |
			CDNS_UART_IXR_FRAMING | CDNS_UART_IXR_OVERRUN;

	/* ignore all अक्षरacters अगर CREAD is not set */
	अगर ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= CDNS_UART_IXR_RXTRIG |
			CDNS_UART_IXR_TOUT | CDNS_UART_IXR_PARITY |
			CDNS_UART_IXR_FRAMING | CDNS_UART_IXR_OVERRUN;

	mode_reg = पढ़ोl(port->membase + CDNS_UART_MR);

	/* Handling Data Size */
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS6:
		cval |= CDNS_UART_MR_CHARLEN_6_BIT;
		अवरोध;
	हाल CS7:
		cval |= CDNS_UART_MR_CHARLEN_7_BIT;
		अवरोध;
	शेष:
	हाल CS8:
		cval |= CDNS_UART_MR_CHARLEN_8_BIT;
		termios->c_cflag &= ~CSIZE;
		termios->c_cflag |= CS8;
		अवरोध;
	पूर्ण

	/* Handling Parity and Stop Bits length */
	अगर (termios->c_cflag & CSTOPB)
		cval |= CDNS_UART_MR_STOPMODE_2_BIT; /* 2 STOP bits */
	अन्यथा
		cval |= CDNS_UART_MR_STOPMODE_1_BIT; /* 1 STOP bit */

	अगर (termios->c_cflag & PARENB) अणु
		/* Mark or Space parity */
		अगर (termios->c_cflag & CMSPAR) अणु
			अगर (termios->c_cflag & PARODD)
				cval |= CDNS_UART_MR_PARITY_MARK;
			अन्यथा
				cval |= CDNS_UART_MR_PARITY_SPACE;
		पूर्ण अन्यथा अणु
			अगर (termios->c_cflag & PARODD)
				cval |= CDNS_UART_MR_PARITY_ODD;
			अन्यथा
				cval |= CDNS_UART_MR_PARITY_EVEN;
		पूर्ण
	पूर्ण अन्यथा अणु
		cval |= CDNS_UART_MR_PARITY_NONE;
	पूर्ण
	cval |= mode_reg & 1;
	ग_लिखोl(cval, port->membase + CDNS_UART_MR);

	cval = पढ़ोl(port->membase + CDNS_UART_MODEMCR);
	अगर (termios->c_cflag & CRTSCTS)
		cval |= CDNS_UART_MODEMCR_FCM;
	अन्यथा
		cval &= ~CDNS_UART_MODEMCR_FCM;
	ग_लिखोl(cval, port->membase + CDNS_UART_MODEMCR);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/**
 * cdns_uart_startup - Called when an application खोलोs a cdns_uart port
 * @port: Handle to the uart port काष्ठाure
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise
 */
अटल पूर्णांक cdns_uart_startup(काष्ठा uart_port *port)
अणु
	काष्ठा cdns_uart *cdns_uart = port->निजी_data;
	bool is_brk_support;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक status = 0;

	is_brk_support = cdns_uart->quirks & CDNS_UART_RXBS_SUPPORT;

	spin_lock_irqsave(&port->lock, flags);

	/* Disable the TX and RX */
	ग_लिखोl(CDNS_UART_CR_TX_DIS | CDNS_UART_CR_RX_DIS,
			port->membase + CDNS_UART_CR);

	/* Set the Control Register with TX/RX Enable, TX/RX Reset,
	 * no अवरोध अक्षरs.
	 */
	ग_लिखोl(CDNS_UART_CR_TXRST | CDNS_UART_CR_RXRST,
			port->membase + CDNS_UART_CR);

	जबतक (पढ़ोl(port->membase + CDNS_UART_CR) &
		(CDNS_UART_CR_TXRST | CDNS_UART_CR_RXRST))
		cpu_relax();

	/*
	 * Clear the RX disable bit and then set the RX enable bit to enable
	 * the receiver.
	 */
	status = पढ़ोl(port->membase + CDNS_UART_CR);
	status &= ~CDNS_UART_CR_RX_DIS;
	status |= CDNS_UART_CR_RX_EN;
	ग_लिखोl(status, port->membase + CDNS_UART_CR);

	/* Set the Mode Register with normal mode,8 data bits,1 stop bit,
	 * no parity.
	 */
	ग_लिखोl(CDNS_UART_MR_CHMODE_NORM | CDNS_UART_MR_STOPMODE_1_BIT
		| CDNS_UART_MR_PARITY_NONE | CDNS_UART_MR_CHARLEN_8_BIT,
		port->membase + CDNS_UART_MR);

	/*
	 * Set the RX FIFO Trigger level to use most of the FIFO, but it
	 * can be tuned with a module parameter
	 */
	ग_लिखोl(rx_trigger_level, port->membase + CDNS_UART_RXWM);

	/*
	 * Receive Timeout रेजिस्टर is enabled but it
	 * can be tuned with a module parameter
	 */
	ग_लिखोl(rx_समयout, port->membase + CDNS_UART_RXTOUT);

	/* Clear out any pending पूर्णांकerrupts beक्रमe enabling them */
	ग_लिखोl(पढ़ोl(port->membase + CDNS_UART_ISR),
			port->membase + CDNS_UART_ISR);

	spin_unlock_irqrestore(&port->lock, flags);

	ret = request_irq(port->irq, cdns_uart_isr, 0, CDNS_UART_NAME, port);
	अगर (ret) अणु
		dev_err(port->dev, "request_irq '%d' failed with %d\n",
			port->irq, ret);
		वापस ret;
	पूर्ण

	/* Set the Interrupt Registers with desired पूर्णांकerrupts */
	अगर (is_brk_support)
		ग_लिखोl(CDNS_UART_RX_IRQS | CDNS_UART_IXR_BRK,
					port->membase + CDNS_UART_IER);
	अन्यथा
		ग_लिखोl(CDNS_UART_RX_IRQS, port->membase + CDNS_UART_IER);

	वापस 0;
पूर्ण

/**
 * cdns_uart_shutकरोwn - Called when an application बंदs a cdns_uart port
 * @port: Handle to the uart port काष्ठाure
 */
अटल व्योम cdns_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	पूर्णांक status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	/* Disable पूर्णांकerrupts */
	status = पढ़ोl(port->membase + CDNS_UART_IMR);
	ग_लिखोl(status, port->membase + CDNS_UART_IDR);
	ग_लिखोl(0xffffffff, port->membase + CDNS_UART_ISR);

	/* Disable the TX and RX */
	ग_लिखोl(CDNS_UART_CR_TX_DIS | CDNS_UART_CR_RX_DIS,
			port->membase + CDNS_UART_CR);

	spin_unlock_irqrestore(&port->lock, flags);

	मुक्त_irq(port->irq, port);
पूर्ण

/**
 * cdns_uart_type - Set UART type to cdns_uart port
 * @port: Handle to the uart port काष्ठाure
 *
 * Return: string on success, शून्य otherwise
 */
अटल स्थिर अक्षर *cdns_uart_type(काष्ठा uart_port *port)
अणु
	वापस port->type == PORT_XUARTPS ? CDNS_UART_NAME : शून्य;
पूर्ण

/**
 * cdns_uart_verअगरy_port - Verअगरy the port params
 * @port: Handle to the uart port काष्ठाure
 * @ser: Handle to the काष्ठाure whose members are compared
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise.
 */
अटल पूर्णांक cdns_uart_verअगरy_port(काष्ठा uart_port *port,
					काष्ठा serial_काष्ठा *ser)
अणु
	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_XUARTPS)
		वापस -EINVAL;
	अगर (port->irq != ser->irq)
		वापस -EINVAL;
	अगर (ser->io_type != UPIO_MEM)
		वापस -EINVAL;
	अगर (port->iobase != ser->port)
		वापस -EINVAL;
	अगर (ser->hub6 != 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/**
 * cdns_uart_request_port - Claim the memory region attached to cdns_uart port,
 *				called when the driver adds a cdns_uart port via
 *				uart_add_one_port()
 * @port: Handle to the uart port काष्ठाure
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise.
 */
अटल पूर्णांक cdns_uart_request_port(काष्ठा uart_port *port)
अणु
	अगर (!request_mem_region(port->mapbase, CDNS_UART_REGISTER_SPACE,
					 CDNS_UART_NAME)) अणु
		वापस -ENOMEM;
	पूर्ण

	port->membase = ioremap(port->mapbase, CDNS_UART_REGISTER_SPACE);
	अगर (!port->membase) अणु
		dev_err(port->dev, "Unable to map registers\n");
		release_mem_region(port->mapbase, CDNS_UART_REGISTER_SPACE);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * cdns_uart_release_port - Release UART port
 * @port: Handle to the uart port काष्ठाure
 *
 * Release the memory region attached to a cdns_uart port. Called when the
 * driver हटाओs a cdns_uart port via uart_हटाओ_one_port().
 */
अटल व्योम cdns_uart_release_port(काष्ठा uart_port *port)
अणु
	release_mem_region(port->mapbase, CDNS_UART_REGISTER_SPACE);
	iounmap(port->membase);
	port->membase = शून्य;
पूर्ण

/**
 * cdns_uart_config_port - Configure UART port
 * @port: Handle to the uart port काष्ठाure
 * @flags: If any
 */
अटल व्योम cdns_uart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE && cdns_uart_request_port(port) == 0)
		port->type = PORT_XUARTPS;
पूर्ण

/**
 * cdns_uart_get_mctrl - Get the modem control state
 * @port: Handle to the uart port काष्ठाure
 *
 * Return: the modem control state
 */
अटल अचिन्हित पूर्णांक cdns_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	u32 val;
	अचिन्हित पूर्णांक mctrl = 0;
	काष्ठा cdns_uart *cdns_uart_data = port->निजी_data;

	अगर (cdns_uart_data->cts_override)
		वापस TIOCM_CTS | TIOCM_DSR | TIOCM_CAR;

	val = पढ़ोl(port->membase + CDNS_UART_MODEMSR);
	अगर (val & CDNS_UART_MODEMSR_CTS)
		mctrl |= TIOCM_CTS;
	अगर (val & CDNS_UART_MODEMSR_DSR)
		mctrl |= TIOCM_DSR;
	अगर (val & CDNS_UART_MODEMSR_RI)
		mctrl |= TIOCM_RNG;
	अगर (val & CDNS_UART_MODEMSR_DCD)
		mctrl |= TIOCM_CAR;

	वापस mctrl;
पूर्ण

अटल व्योम cdns_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	u32 val;
	u32 mode_reg;
	काष्ठा cdns_uart *cdns_uart_data = port->निजी_data;

	अगर (cdns_uart_data->cts_override)
		वापस;

	val = पढ़ोl(port->membase + CDNS_UART_MODEMCR);
	mode_reg = पढ़ोl(port->membase + CDNS_UART_MR);

	val &= ~(CDNS_UART_MODEMCR_RTS | CDNS_UART_MODEMCR_DTR);
	mode_reg &= ~CDNS_UART_MR_CHMODE_MASK;

	अगर (mctrl & TIOCM_RTS)
		val |= CDNS_UART_MODEMCR_RTS;
	अगर (mctrl & TIOCM_DTR)
		val |= CDNS_UART_MODEMCR_DTR;
	अगर (mctrl & TIOCM_LOOP)
		mode_reg |= CDNS_UART_MR_CHMODE_L_LOOP;
	अन्यथा
		mode_reg |= CDNS_UART_MR_CHMODE_NORM;

	ग_लिखोl(val, port->membase + CDNS_UART_MODEMCR);
	ग_लिखोl(mode_reg, port->membase + CDNS_UART_MR);
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
अटल पूर्णांक cdns_uart_poll_get_अक्षर(काष्ठा uart_port *port)
अणु
	पूर्णांक c;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	/* Check अगर FIFO is empty */
	अगर (पढ़ोl(port->membase + CDNS_UART_SR) & CDNS_UART_SR_RXEMPTY)
		c = NO_POLL_CHAR;
	अन्यथा /* Read a अक्षरacter */
		c = (अचिन्हित अक्षर) पढ़ोl(port->membase + CDNS_UART_FIFO);

	spin_unlock_irqrestore(&port->lock, flags);

	वापस c;
पूर्ण

अटल व्योम cdns_uart_poll_put_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर c)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	/* Wait until FIFO is empty */
	जबतक (!(पढ़ोl(port->membase + CDNS_UART_SR) & CDNS_UART_SR_TXEMPTY))
		cpu_relax();

	/* Write a अक्षरacter */
	ग_लिखोl(c, port->membase + CDNS_UART_FIFO);

	/* Wait until FIFO is empty */
	जबतक (!(पढ़ोl(port->membase + CDNS_UART_SR) & CDNS_UART_SR_TXEMPTY))
		cpu_relax();

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण
#पूर्ण_अगर

अटल व्योम cdns_uart_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
		   अचिन्हित पूर्णांक oldstate)
अणु
	चयन (state) अणु
	हाल UART_PM_STATE_OFF:
		pm_runसमय_mark_last_busy(port->dev);
		pm_runसमय_put_स्वतःsuspend(port->dev);
		अवरोध;
	शेष:
		pm_runसमय_get_sync(port->dev);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा uart_ops cdns_uart_ops = अणु
	.set_mctrl	= cdns_uart_set_mctrl,
	.get_mctrl	= cdns_uart_get_mctrl,
	.start_tx	= cdns_uart_start_tx,
	.stop_tx	= cdns_uart_stop_tx,
	.stop_rx	= cdns_uart_stop_rx,
	.tx_empty	= cdns_uart_tx_empty,
	.अवरोध_ctl	= cdns_uart_अवरोध_ctl,
	.set_termios	= cdns_uart_set_termios,
	.startup	= cdns_uart_startup,
	.shutकरोwn	= cdns_uart_shutकरोwn,
	.pm		= cdns_uart_pm,
	.type		= cdns_uart_type,
	.verअगरy_port	= cdns_uart_verअगरy_port,
	.request_port	= cdns_uart_request_port,
	.release_port	= cdns_uart_release_port,
	.config_port	= cdns_uart_config_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर	= cdns_uart_poll_get_अक्षर,
	.poll_put_अक्षर	= cdns_uart_poll_put_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा uart_driver cdns_uart_uart_driver;

#अगर_घोषित CONFIG_SERIAL_XILINX_PS_UART_CONSOLE
/**
 * cdns_uart_console_अक्षर_दो - ग_लिखो the अक्षरacter to the FIFO buffer
 * @port: Handle to the uart port काष्ठाure
 * @ch: Character to be written
 */
अटल व्योम cdns_uart_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	जबतक (पढ़ोl(port->membase + CDNS_UART_SR) & CDNS_UART_SR_TXFULL)
		cpu_relax();
	ग_लिखोl(ch, port->membase + CDNS_UART_FIFO);
पूर्ण

अटल व्योम cdns_early_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s,
				    अचिन्हित n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	uart_console_ग_लिखो(&dev->port, s, n, cdns_uart_console_अक्षर_दो);
पूर्ण

अटल पूर्णांक __init cdns_early_console_setup(काष्ठा earlycon_device *device,
					   स्थिर अक्षर *opt)
अणु
	काष्ठा uart_port *port = &device->port;

	अगर (!port->membase)
		वापस -ENODEV;

	/* initialise control रेजिस्टर */
	ग_लिखोl(CDNS_UART_CR_TX_EN|CDNS_UART_CR_TXRST|CDNS_UART_CR_RXRST,
	       port->membase + CDNS_UART_CR);

	/* only set baud अगर specअगरied on command line - otherwise
	 * assume it has been initialized by a boot loader.
	 */
	अगर (port->uartclk && device->baud) अणु
		u32 cd = 0, bभाग = 0;
		u32 mr;
		पूर्णांक भाग8;

		cdns_uart_calc_baud_भागs(port->uartclk, device->baud,
					 &bभाग, &cd, &भाग8);
		mr = CDNS_UART_MR_PARITY_NONE;
		अगर (भाग8)
			mr |= CDNS_UART_MR_CLKSEL;

		ग_लिखोl(mr,   port->membase + CDNS_UART_MR);
		ग_लिखोl(cd,   port->membase + CDNS_UART_BAUDGEN);
		ग_लिखोl(bभाग, port->membase + CDNS_UART_BAUDDIV);
	पूर्ण

	device->con->ग_लिखो = cdns_early_ग_लिखो;

	वापस 0;
पूर्ण
OF_EARLYCON_DECLARE(cdns, "xlnx,xuartps", cdns_early_console_setup);
OF_EARLYCON_DECLARE(cdns, "cdns,uart-r1p8", cdns_early_console_setup);
OF_EARLYCON_DECLARE(cdns, "cdns,uart-r1p12", cdns_early_console_setup);
OF_EARLYCON_DECLARE(cdns, "xlnx,zynqmp-uart", cdns_early_console_setup);


/* Static poपूर्णांकer to console port */
अटल काष्ठा uart_port *console_port;

/**
 * cdns_uart_console_ग_लिखो - perक्रमm ग_लिखो operation
 * @co: Console handle
 * @s: Poपूर्णांकer to अक्षरacter array
 * @count: No of अक्षरacters
 */
अटल व्योम cdns_uart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_port *port = console_port;
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित पूर्णांक imr, ctrl;
	पूर्णांक locked = 1;

	अगर (port->sysrq)
		locked = 0;
	अन्यथा अगर (oops_in_progress)
		locked = spin_trylock_irqsave(&port->lock, flags);
	अन्यथा
		spin_lock_irqsave(&port->lock, flags);

	/* save and disable पूर्णांकerrupt */
	imr = पढ़ोl(port->membase + CDNS_UART_IMR);
	ग_लिखोl(imr, port->membase + CDNS_UART_IDR);

	/*
	 * Make sure that the tx part is enabled. Set the TX enable bit and
	 * clear the TX disable bit to enable the transmitter.
	 */
	ctrl = पढ़ोl(port->membase + CDNS_UART_CR);
	ctrl &= ~CDNS_UART_CR_TX_DIS;
	ctrl |= CDNS_UART_CR_TX_EN;
	ग_लिखोl(ctrl, port->membase + CDNS_UART_CR);

	uart_console_ग_लिखो(port, s, count, cdns_uart_console_अक्षर_दो);
	जबतक (cdns_uart_tx_empty(port) != TIOCSER_TEMT)
		cpu_relax();

	/* restore पूर्णांकerrupt state */
	ग_लिखोl(imr, port->membase + CDNS_UART_IER);

	अगर (locked)
		spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/**
 * cdns_uart_console_setup - Initialize the uart to शेष config
 * @co: Console handle
 * @options: Initial settings of uart
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise.
 */
अटल पूर्णांक cdns_uart_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port = console_port;

	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	अचिन्हित दीर्घ समय_out;

	अगर (!port->membase) अणु
		pr_debug("console on " CDNS_UART_TTY_NAME "%i not present\n",
			 co->index);
		वापस -ENODEV;
	पूर्ण

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	/* Wait क्रम tx_empty beक्रमe setting up the console */
	समय_out = jअगरfies + usecs_to_jअगरfies(TX_TIMEOUT);

	जबतक (समय_beक्रमe(jअगरfies, समय_out) &&
	       cdns_uart_tx_empty(port) != TIOCSER_TEMT)
		cpu_relax();

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा console cdns_uart_console = अणु
	.name	= CDNS_UART_TTY_NAME,
	.ग_लिखो	= cdns_uart_console_ग_लिखो,
	.device	= uart_console_device,
	.setup	= cdns_uart_console_setup,
	.flags	= CON_PRINTBUFFER,
	.index	= -1, /* Specअगरied on the cmdline (e.g. console=ttyPS ) */
	.data	= &cdns_uart_uart_driver,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SERIAL_XILINX_PS_UART_CONSOLE */

#अगर_घोषित CONFIG_PM_SLEEP
/**
 * cdns_uart_suspend - suspend event
 * @device: Poपूर्णांकer to the device काष्ठाure
 *
 * Return: 0
 */
अटल पूर्णांक cdns_uart_suspend(काष्ठा device *device)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(device);
	काष्ठा cdns_uart *cdns_uart = port->निजी_data;
	पूर्णांक may_wake;

	may_wake = device_may_wakeup(device);

	अगर (console_suspend_enabled && uart_console(port) && may_wake) अणु
		अचिन्हित दीर्घ flags = 0;

		spin_lock_irqsave(&port->lock, flags);
		/* Empty the receive FIFO 1st beक्रमe making changes */
		जबतक (!(पढ़ोl(port->membase + CDNS_UART_SR) &
					CDNS_UART_SR_RXEMPTY))
			पढ़ोl(port->membase + CDNS_UART_FIFO);
		/* set RX trigger level to 1 */
		ग_लिखोl(1, port->membase + CDNS_UART_RXWM);
		/* disable RX समयout पूर्णांकerrups */
		ग_लिखोl(CDNS_UART_IXR_TOUT, port->membase + CDNS_UART_IDR);
		spin_unlock_irqrestore(&port->lock, flags);
	पूर्ण

	/*
	 * Call the API provided in serial_core.c file which handles
	 * the suspend.
	 */
	वापस uart_suspend_port(cdns_uart->cdns_uart_driver, port);
पूर्ण

/**
 * cdns_uart_resume - Resume after a previous suspend
 * @device: Poपूर्णांकer to the device काष्ठाure
 *
 * Return: 0
 */
अटल पूर्णांक cdns_uart_resume(काष्ठा device *device)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(device);
	काष्ठा cdns_uart *cdns_uart = port->निजी_data;
	अचिन्हित दीर्घ flags = 0;
	u32 ctrl_reg;
	पूर्णांक may_wake;

	may_wake = device_may_wakeup(device);

	अगर (console_suspend_enabled && uart_console(port) && !may_wake) अणु
		clk_enable(cdns_uart->pclk);
		clk_enable(cdns_uart->uartclk);

		spin_lock_irqsave(&port->lock, flags);

		/* Set TX/RX Reset */
		ctrl_reg = पढ़ोl(port->membase + CDNS_UART_CR);
		ctrl_reg |= CDNS_UART_CR_TXRST | CDNS_UART_CR_RXRST;
		ग_लिखोl(ctrl_reg, port->membase + CDNS_UART_CR);
		जबतक (पढ़ोl(port->membase + CDNS_UART_CR) &
				(CDNS_UART_CR_TXRST | CDNS_UART_CR_RXRST))
			cpu_relax();

		/* restore rx समयout value */
		ग_लिखोl(rx_समयout, port->membase + CDNS_UART_RXTOUT);
		/* Enable Tx/Rx */
		ctrl_reg = पढ़ोl(port->membase + CDNS_UART_CR);
		ctrl_reg &= ~(CDNS_UART_CR_TX_DIS | CDNS_UART_CR_RX_DIS);
		ctrl_reg |= CDNS_UART_CR_TX_EN | CDNS_UART_CR_RX_EN;
		ग_लिखोl(ctrl_reg, port->membase + CDNS_UART_CR);

		clk_disable(cdns_uart->uartclk);
		clk_disable(cdns_uart->pclk);
		spin_unlock_irqrestore(&port->lock, flags);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&port->lock, flags);
		/* restore original rx trigger level */
		ग_लिखोl(rx_trigger_level, port->membase + CDNS_UART_RXWM);
		/* enable RX समयout पूर्णांकerrupt */
		ग_लिखोl(CDNS_UART_IXR_TOUT, port->membase + CDNS_UART_IER);
		spin_unlock_irqrestore(&port->lock, flags);
	पूर्ण

	वापस uart_resume_port(cdns_uart->cdns_uart_driver, port);
पूर्ण
#पूर्ण_अगर /* ! CONFIG_PM_SLEEP */
अटल पूर्णांक __maybe_unused cdns_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(dev);
	काष्ठा cdns_uart *cdns_uart = port->निजी_data;

	clk_disable(cdns_uart->uartclk);
	clk_disable(cdns_uart->pclk);
	वापस 0;
पूर्ण;

अटल पूर्णांक __maybe_unused cdns_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(dev);
	काष्ठा cdns_uart *cdns_uart = port->निजी_data;

	clk_enable(cdns_uart->pclk);
	clk_enable(cdns_uart->uartclk);
	वापस 0;
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops cdns_uart_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(cdns_uart_suspend, cdns_uart_resume)
	SET_RUNTIME_PM_OPS(cdns_runसमय_suspend,
			   cdns_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा cdns_platक्रमm_data zynqmp_uart_def = अणु
				.quirks = CDNS_UART_RXBS_SUPPORT, पूर्ण;

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id cdns_uart_of_match[] = अणु
	अणु .compatible = "xlnx,xuartps", पूर्ण,
	अणु .compatible = "cdns,uart-r1p8", पूर्ण,
	अणु .compatible = "cdns,uart-r1p12", .data = &zynqmp_uart_def पूर्ण,
	अणु .compatible = "xlnx,zynqmp-uart", .data = &zynqmp_uart_def पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cdns_uart_of_match);

/* Temporary variable क्रम storing number of instances */
अटल पूर्णांक instances;

/**
 * cdns_uart_probe - Platक्रमm driver probe
 * @pdev: Poपूर्णांकer to the platक्रमm device काष्ठाure
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise
 */
अटल पूर्णांक cdns_uart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc, id, irq;
	काष्ठा uart_port *port;
	काष्ठा resource *res;
	काष्ठा cdns_uart *cdns_uart_data;
	स्थिर काष्ठा of_device_id *match;

	cdns_uart_data = devm_kzalloc(&pdev->dev, माप(*cdns_uart_data),
			GFP_KERNEL);
	अगर (!cdns_uart_data)
		वापस -ENOMEM;
	port = devm_kzalloc(&pdev->dev, माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	/* Look क्रम a serialN alias */
	id = of_alias_get_id(pdev->dev.of_node, "serial");
	अगर (id < 0)
		id = 0;

	अगर (id >= CDNS_UART_NR_PORTS) अणु
		dev_err(&pdev->dev, "Cannot get uart_port structure\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!cdns_uart_uart_driver.state) अणु
		cdns_uart_uart_driver.owner = THIS_MODULE;
		cdns_uart_uart_driver.driver_name = CDNS_UART_NAME;
		cdns_uart_uart_driver.dev_name = CDNS_UART_TTY_NAME;
		cdns_uart_uart_driver.major = CDNS_UART_MAJOR;
		cdns_uart_uart_driver.minor = CDNS_UART_MINOR;
		cdns_uart_uart_driver.nr = CDNS_UART_NR_PORTS;
#अगर_घोषित CONFIG_SERIAL_XILINX_PS_UART_CONSOLE
		cdns_uart_uart_driver.cons = &cdns_uart_console;
#पूर्ण_अगर

		rc = uart_रेजिस्टर_driver(&cdns_uart_uart_driver);
		अगर (rc < 0) अणु
			dev_err(&pdev->dev, "Failed to register driver\n");
			वापस rc;
		पूर्ण
	पूर्ण

	cdns_uart_data->cdns_uart_driver = &cdns_uart_uart_driver;

	match = of_match_node(cdns_uart_of_match, pdev->dev.of_node);
	अगर (match && match->data) अणु
		स्थिर काष्ठा cdns_platक्रमm_data *data = match->data;

		cdns_uart_data->quirks = data->quirks;
	पूर्ण

	cdns_uart_data->pclk = devm_clk_get(&pdev->dev, "pclk");
	अगर (PTR_ERR(cdns_uart_data->pclk) == -EPROBE_DEFER) अणु
		rc = PTR_ERR(cdns_uart_data->pclk);
		जाओ err_out_unरेजिस्टर_driver;
	पूर्ण

	अगर (IS_ERR(cdns_uart_data->pclk)) अणु
		cdns_uart_data->pclk = devm_clk_get(&pdev->dev, "aper_clk");
		अगर (IS_ERR(cdns_uart_data->pclk)) अणु
			rc = PTR_ERR(cdns_uart_data->pclk);
			जाओ err_out_unरेजिस्टर_driver;
		पूर्ण
		dev_err(&pdev->dev, "clock name 'aper_clk' is deprecated.\n");
	पूर्ण

	cdns_uart_data->uartclk = devm_clk_get(&pdev->dev, "uart_clk");
	अगर (PTR_ERR(cdns_uart_data->uartclk) == -EPROBE_DEFER) अणु
		rc = PTR_ERR(cdns_uart_data->uartclk);
		जाओ err_out_unरेजिस्टर_driver;
	पूर्ण

	अगर (IS_ERR(cdns_uart_data->uartclk)) अणु
		cdns_uart_data->uartclk = devm_clk_get(&pdev->dev, "ref_clk");
		अगर (IS_ERR(cdns_uart_data->uartclk)) अणु
			rc = PTR_ERR(cdns_uart_data->uartclk);
			जाओ err_out_unरेजिस्टर_driver;
		पूर्ण
		dev_err(&pdev->dev, "clock name 'ref_clk' is deprecated.\n");
	पूर्ण

	rc = clk_prepare_enable(cdns_uart_data->pclk);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Unable to enable pclk clock.\n");
		जाओ err_out_unरेजिस्टर_driver;
	पूर्ण
	rc = clk_prepare_enable(cdns_uart_data->uartclk);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Unable to enable device clock.\n");
		जाओ err_out_clk_dis_pclk;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		rc = -ENODEV;
		जाओ err_out_clk_disable;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0) अणु
		rc = -ENXIO;
		जाओ err_out_clk_disable;
	पूर्ण

#अगर_घोषित CONFIG_COMMON_CLK
	cdns_uart_data->clk_rate_change_nb.notअगरier_call =
			cdns_uart_clk_notअगरier_cb;
	अगर (clk_notअगरier_रेजिस्टर(cdns_uart_data->uartclk,
				&cdns_uart_data->clk_rate_change_nb))
		dev_warn(&pdev->dev, "Unable to register clock notifier.\n");
#पूर्ण_अगर

	/* At this poपूर्णांक, we've got an empty uart_port काष्ठा, initialize it */
	spin_lock_init(&port->lock);
	port->type	= PORT_UNKNOWN;
	port->iotype	= UPIO_MEM32;
	port->flags	= UPF_BOOT_AUTOCONF;
	port->ops	= &cdns_uart_ops;
	port->fअगरosize	= CDNS_UART_FIFO_SIZE;
	port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_XILINX_PS_UART_CONSOLE);
	port->line	= id;

	/*
	 * Register the port.
	 * This function also रेजिस्टरs this device with the tty layer
	 * and triggers invocation of the config_port() entry poपूर्णांक.
	 */
	port->mapbase = res->start;
	port->irq = irq;
	port->dev = &pdev->dev;
	port->uartclk = clk_get_rate(cdns_uart_data->uartclk);
	port->निजी_data = cdns_uart_data;
	cdns_uart_data->port = port;
	platक्रमm_set_drvdata(pdev, port);

	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, UART_AUTOSUSPEND_TIMEOUT);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	device_init_wakeup(port->dev, true);

#अगर_घोषित CONFIG_SERIAL_XILINX_PS_UART_CONSOLE
	/*
	 * If console hasn't been found yet try to assign this port
	 * because it is required to be asचिन्हित क्रम console setup function.
	 * If रेजिस्टर_console() करोn't assign value, then console_port poपूर्णांकer
	 * is cleanup.
	 */
	अगर (!console_port) अणु
		cdns_uart_console.index = id;
		console_port = port;
	पूर्ण
#पूर्ण_अगर

	rc = uart_add_one_port(&cdns_uart_uart_driver, port);
	अगर (rc) अणु
		dev_err(&pdev->dev,
			"uart_add_one_port() failed; err=%i\n", rc);
		जाओ err_out_pm_disable;
	पूर्ण

#अगर_घोषित CONFIG_SERIAL_XILINX_PS_UART_CONSOLE
	/* This is not port which is used क्रम console that's why clean it up */
	अगर (console_port == port &&
	    !(cdns_uart_uart_driver.cons->flags & CON_ENABLED)) अणु
		console_port = शून्य;
		cdns_uart_console.index = -1;
	पूर्ण
#पूर्ण_अगर

	cdns_uart_data->cts_override = of_property_पढ़ो_bool(pdev->dev.of_node,
							     "cts-override");

	instances++;

	वापस 0;

err_out_pm_disable:
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
#अगर_घोषित CONFIG_COMMON_CLK
	clk_notअगरier_unरेजिस्टर(cdns_uart_data->uartclk,
			&cdns_uart_data->clk_rate_change_nb);
#पूर्ण_अगर
err_out_clk_disable:
	clk_disable_unprepare(cdns_uart_data->uartclk);
err_out_clk_dis_pclk:
	clk_disable_unprepare(cdns_uart_data->pclk);
err_out_unरेजिस्टर_driver:
	अगर (!instances)
		uart_unरेजिस्टर_driver(cdns_uart_data->cdns_uart_driver);
	वापस rc;
पूर्ण

/**
 * cdns_uart_हटाओ - called when the platक्रमm driver is unरेजिस्टरed
 * @pdev: Poपूर्णांकer to the platक्रमm device काष्ठाure
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise
 */
अटल पूर्णांक cdns_uart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port = platक्रमm_get_drvdata(pdev);
	काष्ठा cdns_uart *cdns_uart_data = port->निजी_data;
	पूर्णांक rc;

	/* Remove the cdns_uart port from the serial core */
#अगर_घोषित CONFIG_COMMON_CLK
	clk_notअगरier_unरेजिस्टर(cdns_uart_data->uartclk,
			&cdns_uart_data->clk_rate_change_nb);
#पूर्ण_अगर
	rc = uart_हटाओ_one_port(cdns_uart_data->cdns_uart_driver, port);
	port->mapbase = 0;
	clk_disable_unprepare(cdns_uart_data->uartclk);
	clk_disable_unprepare(cdns_uart_data->pclk);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	device_init_wakeup(&pdev->dev, false);

#अगर_घोषित CONFIG_SERIAL_XILINX_PS_UART_CONSOLE
	अगर (console_port == port)
		console_port = शून्य;
#पूर्ण_अगर

	अगर (!--instances)
		uart_unरेजिस्टर_driver(cdns_uart_data->cdns_uart_driver);
	वापस rc;
पूर्ण

अटल काष्ठा platक्रमm_driver cdns_uart_platक्रमm_driver = अणु
	.probe   = cdns_uart_probe,
	.हटाओ  = cdns_uart_हटाओ,
	.driver  = अणु
		.name = CDNS_UART_NAME,
		.of_match_table = cdns_uart_of_match,
		.pm = &cdns_uart_dev_pm_ops,
		.suppress_bind_attrs = IS_BUILTIN(CONFIG_SERIAL_XILINX_PS_UART),
		पूर्ण,
पूर्ण;

अटल पूर्णांक __init cdns_uart_init(व्योम)
अणु
	/* Register the platक्रमm driver */
	वापस platक्रमm_driver_रेजिस्टर(&cdns_uart_platक्रमm_driver);
पूर्ण

अटल व्योम __निकास cdns_uart_निकास(व्योम)
अणु
	/* Unरेजिस्टर the platक्रमm driver */
	platक्रमm_driver_unरेजिस्टर(&cdns_uart_platक्रमm_driver);
पूर्ण

arch_initcall(cdns_uart_init);
module_निकास(cdns_uart_निकास);

MODULE_DESCRIPTION("Driver for Cadence UART");
MODULE_AUTHOR("Xilinx Inc.");
MODULE_LICENSE("GPL");
