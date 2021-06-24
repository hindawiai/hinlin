<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * 8250-core based driver क्रम the OMAP पूर्णांकernal UART
 *
 * based on omap-serial.c, Copyright (C) 2010 Texas Instruments.
 *
 * Copyright (C) 2014 Sebastian Andrzej Siewior
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/console.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/sys_soc.h>

#समावेश "8250.h"

#घोषणा DEFAULT_CLK_SPEED	48000000

#घोषणा UART_ERRATA_i202_MDR1_ACCESS	(1 << 0)
#घोषणा OMAP_UART_WER_HAS_TX_WAKEUP	(1 << 1)
#घोषणा OMAP_DMA_TX_KICK		(1 << 2)
/*
 * See Advisory 21 in AM437x errata SPRZ408B, updated April 2015.
 * The same errata is applicable to AM335x and DRA7x processors too.
 */
#घोषणा UART_ERRATA_CLOCK_DISABLE	(1 << 3)
#घोषणा	UART_HAS_EFR2			BIT(4)
#घोषणा UART_HAS_RHR_IT_DIS		BIT(5)

#घोषणा OMAP_UART_FCR_RX_TRIG		6
#घोषणा OMAP_UART_FCR_TX_TRIG		4

/* SCR रेजिस्टर biपंचांगasks */
#घोषणा OMAP_UART_SCR_RX_TRIG_GRANU1_MASK	(1 << 7)
#घोषणा OMAP_UART_SCR_TX_TRIG_GRANU1_MASK	(1 << 6)
#घोषणा OMAP_UART_SCR_TX_EMPTY			(1 << 3)
#घोषणा OMAP_UART_SCR_DMAMODE_MASK		(3 << 1)
#घोषणा OMAP_UART_SCR_DMAMODE_1			(1 << 1)
#घोषणा OMAP_UART_SCR_DMAMODE_CTL		(1 << 0)

/* MVR रेजिस्टर biपंचांगasks */
#घोषणा OMAP_UART_MVR_SCHEME_SHIFT	30
#घोषणा OMAP_UART_LEGACY_MVR_MAJ_MASK	0xf0
#घोषणा OMAP_UART_LEGACY_MVR_MAJ_SHIFT	4
#घोषणा OMAP_UART_LEGACY_MVR_MIN_MASK	0x0f
#घोषणा OMAP_UART_MVR_MAJ_MASK		0x700
#घोषणा OMAP_UART_MVR_MAJ_SHIFT		8
#घोषणा OMAP_UART_MVR_MIN_MASK		0x3f

/* SYSC रेजिस्टर biपंचांगasks */
#घोषणा OMAP_UART_SYSC_SOFTRESET	(1 << 1)

/* SYSS रेजिस्टर biपंचांगasks */
#घोषणा OMAP_UART_SYSS_RESETDONE	(1 << 0)

#घोषणा UART_TI752_TLR_TX	0
#घोषणा UART_TI752_TLR_RX	4

#घोषणा TRIGGER_TLR_MASK(x)	((x & 0x3c) >> 2)
#घोषणा TRIGGER_FCR_MASK(x)	(x & 3)

/* Enable XON/XOFF flow control on output */
#घोषणा OMAP_UART_SW_TX		0x08
/* Enable XON/XOFF flow control on input */
#घोषणा OMAP_UART_SW_RX		0x02

#घोषणा OMAP_UART_WER_MOD_WKUP	0x7f
#घोषणा OMAP_UART_TX_WAKEUP_EN	(1 << 7)

#घोषणा TX_TRIGGER	1
#घोषणा RX_TRIGGER	48

#घोषणा OMAP_UART_TCR_RESTORE(x)	((x / 4) << 4)
#घोषणा OMAP_UART_TCR_HALT(x)		((x / 4) << 0)

#घोषणा UART_BUILD_REVISION(x, y)	(((x) << 8) | (y))

#घोषणा OMAP_UART_REV_46 0x0406
#घोषणा OMAP_UART_REV_52 0x0502
#घोषणा OMAP_UART_REV_63 0x0603

/* Interrupt Enable Register 2 */
#घोषणा UART_OMAP_IER2			0x1B
#घोषणा UART_OMAP_IER2_RHR_IT_DIS	BIT(2)

/* Enhanced features रेजिस्टर 2 */
#घोषणा UART_OMAP_EFR2			0x23
#घोषणा UART_OMAP_EFR2_TIMEOUT_BEHAVE	BIT(6)

काष्ठा omap8250_priv अणु
	पूर्णांक line;
	u8 habit;
	u8 mdr1;
	u8 efr;
	u8 scr;
	u8 wer;
	u8 xon;
	u8 xoff;
	u8 delayed_restore;
	u16 quot;

	u8 tx_trigger;
	u8 rx_trigger;
	bool is_suspending;
	पूर्णांक wakeirq;
	पूर्णांक wakeups_enabled;
	u32 latency;
	u32 calc_latency;
	काष्ठा pm_qos_request pm_qos_request;
	काष्ठा work_काष्ठा qos_work;
	काष्ठा uart_8250_dma omap8250_dma;
	spinlock_t rx_dma_lock;
	bool rx_dma_broken;
	bool throttled;
पूर्ण;

काष्ठा omap8250_dma_params अणु
	u32 rx_size;
	u8 rx_trigger;
	u8 tx_trigger;
पूर्ण;

काष्ठा omap8250_platdata अणु
	काष्ठा omap8250_dma_params *dma_params;
	u8 habit;
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_8250_DMA
अटल व्योम omap_8250_rx_dma_flush(काष्ठा uart_8250_port *p);
#अन्यथा
अटल अंतरभूत व्योम omap_8250_rx_dma_flush(काष्ठा uart_8250_port *p) अणु पूर्ण
#पूर्ण_अगर

अटल u32 uart_पढ़ो(काष्ठा uart_8250_port *up, u32 reg)
अणु
	वापस पढ़ोl(up->port.membase + (reg << up->port.regshअगरt));
पूर्ण

अटल व्योम omap8250_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	काष्ठा omap8250_priv *priv = up->port.निजी_data;
	u8 lcr;

	serial8250_करो_set_mctrl(port, mctrl);

	अगर (!mctrl_gpio_to_gpiod(up->gpios, UART_GPIO_RTS)) अणु
		/*
		 * Turn off स्वतःRTS अगर RTS is lowered and restore स्वतःRTS
		 * setting अगर RTS is उठाओd
		 */
		lcr = serial_in(up, UART_LCR);
		serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
		अगर ((mctrl & TIOCM_RTS) && (port->status & UPSTAT_AUTORTS))
			priv->efr |= UART_EFR_RTS;
		अन्यथा
			priv->efr &= ~UART_EFR_RTS;
		serial_out(up, UART_EFR, priv->efr);
		serial_out(up, UART_LCR, lcr);
	पूर्ण
पूर्ण

/*
 * Work Around क्रम Errata i202 (2430, 3430, 3630, 4430 and 4460)
 * The access to uart रेजिस्टर after MDR1 Access
 * causes UART to corrupt data.
 *
 * Need a delay =
 * 5 L4 घड़ी cycles + 5 UART functional घड़ी cycle (@48MHz = ~0.2uS)
 * give 10 बार as much
 */
अटल व्योम omap_8250_mdr1_errataset(काष्ठा uart_8250_port *up,
				     काष्ठा omap8250_priv *priv)
अणु
	u8 समयout = 255;

	serial_out(up, UART_OMAP_MDR1, priv->mdr1);
	udelay(2);
	serial_out(up, UART_FCR, up->fcr | UART_FCR_CLEAR_XMIT |
			UART_FCR_CLEAR_RCVR);
	/*
	 * Wait क्रम FIFO to empty: when empty, RX_FIFO_E bit is 0 and
	 * TX_FIFO_E bit is 1.
	 */
	जबतक (UART_LSR_THRE != (serial_in(up, UART_LSR) &
				(UART_LSR_THRE | UART_LSR_DR))) अणु
		समयout--;
		अगर (!समयout) अणु
			/* Should *never* happen. we warn and carry on */
			dev_crit(up->port.dev, "Errata i202: timedout %x\n",
				 serial_in(up, UART_LSR));
			अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम omap_8250_get_भागisor(काष्ठा uart_port *port, अचिन्हित पूर्णांक baud,
				  काष्ठा omap8250_priv *priv)
अणु
	अचिन्हित पूर्णांक uartclk = port->uartclk;
	अचिन्हित पूर्णांक भाग_13, भाग_16;
	अचिन्हित पूर्णांक असल_d13, असल_d16;

	/*
	 * Old custom speed handling.
	 */
	अगर (baud == 38400 && (port->flags & UPF_SPD_MASK) == UPF_SPD_CUST) अणु
		priv->quot = port->custom_भागisor & UART_DIV_MAX;
		/*
		 * I assume that nobody is using this. But hey, अगर somebody
		 * would like to specअगरy the भागisor _and_ the mode then the
		 * driver is पढ़ोy and रुकोing क्रम it.
		 */
		अगर (port->custom_भागisor & (1 << 16))
			priv->mdr1 = UART_OMAP_MDR1_13X_MODE;
		अन्यथा
			priv->mdr1 = UART_OMAP_MDR1_16X_MODE;
		वापस;
	पूर्ण
	भाग_13 = DIV_ROUND_CLOSEST(uartclk, 13 * baud);
	भाग_16 = DIV_ROUND_CLOSEST(uartclk, 16 * baud);

	अगर (!भाग_13)
		भाग_13 = 1;
	अगर (!भाग_16)
		भाग_16 = 1;

	असल_d13 = असल(baud - uartclk / 13 / भाग_13);
	असल_d16 = असल(baud - uartclk / 16 / भाग_16);

	अगर (असल_d13 >= असल_d16) अणु
		priv->mdr1 = UART_OMAP_MDR1_16X_MODE;
		priv->quot = भाग_16;
	पूर्ण अन्यथा अणु
		priv->mdr1 = UART_OMAP_MDR1_13X_MODE;
		priv->quot = भाग_13;
	पूर्ण
पूर्ण

अटल व्योम omap8250_update_scr(काष्ठा uart_8250_port *up,
				काष्ठा omap8250_priv *priv)
अणु
	u8 old_scr;

	old_scr = serial_in(up, UART_OMAP_SCR);
	अगर (old_scr == priv->scr)
		वापस;

	/*
	 * The manual recommends not to enable the DMA mode selector in the SCR
	 * (instead of the FCR) रेजिस्टर _and_ selecting the DMA mode as one
	 * रेजिस्टर ग_लिखो because this may lead to malfunction.
	 */
	अगर (priv->scr & OMAP_UART_SCR_DMAMODE_MASK)
		serial_out(up, UART_OMAP_SCR,
			   priv->scr & ~OMAP_UART_SCR_DMAMODE_MASK);
	serial_out(up, UART_OMAP_SCR, priv->scr);
पूर्ण

अटल व्योम omap8250_update_mdr1(काष्ठा uart_8250_port *up,
				 काष्ठा omap8250_priv *priv)
अणु
	अगर (priv->habit & UART_ERRATA_i202_MDR1_ACCESS)
		omap_8250_mdr1_errataset(up, priv);
	अन्यथा
		serial_out(up, UART_OMAP_MDR1, priv->mdr1);
पूर्ण

अटल व्योम omap8250_restore_regs(काष्ठा uart_8250_port *up)
अणु
	काष्ठा omap8250_priv *priv = up->port.निजी_data;
	काष्ठा uart_8250_dma	*dma = up->dma;

	अगर (dma && dma->tx_running) अणु
		/*
		 * TCSANOW requests the change to occur immediately however अगर
		 * we have a TX-DMA operation in progress then it has been
		 * observed that it might stall and never complete. Thereक्रमe we
		 * delay DMA completes to prevent this hang from happen.
		 */
		priv->delayed_restore = 1;
		वापस;
	पूर्ण

	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	serial_out(up, UART_EFR, UART_EFR_ECB);

	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	serial8250_out_MCR(up, UART_MCR_TCRTLR);
	serial_out(up, UART_FCR, up->fcr);

	omap8250_update_scr(up, priv);

	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);

	serial_out(up, UART_TI752_TCR, OMAP_UART_TCR_RESTORE(16) |
			OMAP_UART_TCR_HALT(52));
	serial_out(up, UART_TI752_TLR,
		   TRIGGER_TLR_MASK(priv->tx_trigger) << UART_TI752_TLR_TX |
		   TRIGGER_TLR_MASK(priv->rx_trigger) << UART_TI752_TLR_RX);

	serial_out(up, UART_LCR, 0);

	/* drop TCR + TLR access, we setup XON/XOFF later */
	serial8250_out_MCR(up, up->mcr);
	serial_out(up, UART_IER, up->ier);

	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	serial_dl_ग_लिखो(up, priv->quot);

	serial_out(up, UART_EFR, priv->efr);

	/* Configure flow control */
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	serial_out(up, UART_XON1, priv->xon);
	serial_out(up, UART_XOFF1, priv->xoff);

	serial_out(up, UART_LCR, up->lcr);

	omap8250_update_mdr1(up, priv);

	up->port.ops->set_mctrl(&up->port, up->port.mctrl);
पूर्ण

/*
 * OMAP can use "CLK / (16 or 13) / div" क्रम baud rate. And then we have have
 * some dअगरferences in how we want to handle flow control.
 */
अटल व्योम omap_8250_set_termios(काष्ठा uart_port *port,
				  काष्ठा ktermios *termios,
				  काष्ठा ktermios *old)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	काष्ठा omap8250_priv *priv = up->port.निजी_data;
	अचिन्हित अक्षर cval = 0;
	अचिन्हित पूर्णांक baud;

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
	अगर (termios->c_cflag & CMSPAR)
		cval |= UART_LCR_SPAR;

	/*
	 * Ask the core to calculate the भागisor क्रम us.
	 */
	baud = uart_get_baud_rate(port, termios, old,
				  port->uartclk / 16 / UART_DIV_MAX,
				  port->uartclk / 13);
	omap_8250_get_भागisor(port, baud, priv);

	/*
	 * Ok, we're now changing the port state. Do it with
	 * पूर्णांकerrupts disabled.
	 */
	pm_runसमय_get_sync(port->dev);
	spin_lock_irq(&port->lock);

	/*
	 * Update the per-port समयout.
	 */
	uart_update_समयout(port, termios->c_cflag, baud);

	up->port.पढ़ो_status_mask = UART_LSR_OE | UART_LSR_THRE | UART_LSR_DR;
	अगर (termios->c_अगरlag & INPCK)
		up->port.पढ़ो_status_mask |= UART_LSR_FE | UART_LSR_PE;
	अगर (termios->c_अगरlag & (IGNBRK | PARMRK))
		up->port.पढ़ो_status_mask |= UART_LSR_BI;

	/*
	 * Characters to ignore
	 */
	up->port.ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		up->port.ignore_status_mask |= UART_LSR_PE | UART_LSR_FE;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		up->port.ignore_status_mask |= UART_LSR_BI;
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			up->port.ignore_status_mask |= UART_LSR_OE;
	पूर्ण

	/*
	 * ignore all अक्षरacters अगर CREAD is not set
	 */
	अगर ((termios->c_cflag & CREAD) == 0)
		up->port.ignore_status_mask |= UART_LSR_DR;

	/*
	 * Modem status पूर्णांकerrupts
	 */
	up->ier &= ~UART_IER_MSI;
	अगर (UART_ENABLE_MS(&up->port, termios->c_cflag))
		up->ier |= UART_IER_MSI;

	up->lcr = cval;
	/* Up to here it was mostly serial8250_करो_set_termios() */

	/*
	 * We enable TRIG_GRANU क्रम RX and TX and additionally we set
	 * SCR_TX_EMPTY bit. The result is the following:
	 * - RX_TRIGGER amount of bytes in the FIFO will cause an पूर्णांकerrupt.
	 * - less than RX_TRIGGER number of bytes will also cause an पूर्णांकerrupt
	 *   once the UART decides that there no new bytes arriving.
	 * - Once THRE is enabled, the पूर्णांकerrupt will be fired once the FIFO is
	 *   empty - the trigger level is ignored here.
	 *
	 * Once DMA is enabled:
	 * - UART will निश्चित the TX DMA line once there is room क्रम TX_TRIGGER
	 *   bytes in the TX FIFO. On each निश्चित the DMA engine will move
	 *   TX_TRIGGER bytes पूर्णांकo the FIFO.
	 * - UART will निश्चित the RX DMA line once there are RX_TRIGGER bytes in
	 *   the FIFO and move RX_TRIGGER bytes.
	 * This is because threshold and trigger values are the same.
	 */
	up->fcr = UART_FCR_ENABLE_FIFO;
	up->fcr |= TRIGGER_FCR_MASK(priv->tx_trigger) << OMAP_UART_FCR_TX_TRIG;
	up->fcr |= TRIGGER_FCR_MASK(priv->rx_trigger) << OMAP_UART_FCR_RX_TRIG;

	priv->scr = OMAP_UART_SCR_RX_TRIG_GRANU1_MASK | OMAP_UART_SCR_TX_EMPTY |
		OMAP_UART_SCR_TX_TRIG_GRANU1_MASK;

	अगर (up->dma)
		priv->scr |= OMAP_UART_SCR_DMAMODE_1 |
			OMAP_UART_SCR_DMAMODE_CTL;

	priv->xon = termios->c_cc[VSTART];
	priv->xoff = termios->c_cc[VSTOP];

	priv->efr = 0;
	up->port.status &= ~(UPSTAT_AUTOCTS | UPSTAT_AUTORTS | UPSTAT_AUTOXOFF);

	अगर (termios->c_cflag & CRTSCTS && up->port.flags & UPF_HARD_FLOW &&
	    !mctrl_gpio_to_gpiod(up->gpios, UART_GPIO_RTS) &&
	    !mctrl_gpio_to_gpiod(up->gpios, UART_GPIO_CTS)) अणु
		/* Enable AUTOCTS (स्वतःRTS is enabled when RTS is उठाओd) */
		up->port.status |= UPSTAT_AUTOCTS | UPSTAT_AUTORTS;
		priv->efr |= UART_EFR_CTS;
	पूर्ण अन्यथा	अगर (up->port.flags & UPF_SOFT_FLOW) अणु
		/*
		 * OMAP rx s/w flow control is borked; the transmitter reमुख्यs
		 * stuck off even अगर rx flow control is subsequently disabled
		 */

		/*
		 * IXOFF Flag:
		 * Enable XON/XOFF flow control on output.
		 * Transmit XON1, XOFF1
		 */
		अगर (termios->c_अगरlag & IXOFF) अणु
			up->port.status |= UPSTAT_AUTOXOFF;
			priv->efr |= OMAP_UART_SW_TX;
		पूर्ण
	पूर्ण
	omap8250_restore_regs(up);

	spin_unlock_irq(&up->port.lock);
	pm_runसमय_mark_last_busy(port->dev);
	pm_runसमय_put_स्वतःsuspend(port->dev);

	/* calculate wakeup latency स्थिरraपूर्णांक */
	priv->calc_latency = USEC_PER_SEC * 64 * 8 / baud;
	priv->latency = priv->calc_latency;

	schedule_work(&priv->qos_work);

	/* Don't reग_लिखो B0 */
	अगर (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);
पूर्ण

/* same as 8250 except that we may have extra flow bits set in EFR */
अटल व्योम omap_8250_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
			 अचिन्हित पूर्णांक oldstate)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	u8 efr;

	pm_runसमय_get_sync(port->dev);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	efr = serial_in(up, UART_EFR);
	serial_out(up, UART_EFR, efr | UART_EFR_ECB);
	serial_out(up, UART_LCR, 0);

	serial_out(up, UART_IER, (state != 0) ? UART_IERX_SLEEP : 0);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	serial_out(up, UART_EFR, efr);
	serial_out(up, UART_LCR, 0);

	pm_runसमय_mark_last_busy(port->dev);
	pm_runसमय_put_स्वतःsuspend(port->dev);
पूर्ण

अटल व्योम omap_serial_fill_features_erratas(काष्ठा uart_8250_port *up,
					      काष्ठा omap8250_priv *priv)
अणु
	स्थिर काष्ठा soc_device_attribute k3_soc_devices[] = अणु
		अणु .family = "AM65X",  पूर्ण,
		अणु .family = "J721E", .revision = "SR1.0" पूर्ण,
		अणु /* sentinel */ पूर्ण
	पूर्ण;
	u32 mvr, scheme;
	u16 revision, major, minor;

	mvr = uart_पढ़ो(up, UART_OMAP_MVER);

	/* Check revision रेजिस्टर scheme */
	scheme = mvr >> OMAP_UART_MVR_SCHEME_SHIFT;

	चयन (scheme) अणु
	हाल 0: /* Legacy Scheme: OMAP2/3 */
		/* MINOR_REV[0:4], MAJOR_REV[4:7] */
		major = (mvr & OMAP_UART_LEGACY_MVR_MAJ_MASK) >>
			OMAP_UART_LEGACY_MVR_MAJ_SHIFT;
		minor = (mvr & OMAP_UART_LEGACY_MVR_MIN_MASK);
		अवरोध;
	हाल 1:
		/* New Scheme: OMAP4+ */
		/* MINOR_REV[0:5], MAJOR_REV[8:10] */
		major = (mvr & OMAP_UART_MVR_MAJ_MASK) >>
			OMAP_UART_MVR_MAJ_SHIFT;
		minor = (mvr & OMAP_UART_MVR_MIN_MASK);
		अवरोध;
	शेष:
		dev_warn(up->port.dev,
			 "Unknown revision, defaulting to highest\n");
		/* highest possible revision */
		major = 0xff;
		minor = 0xff;
	पूर्ण
	/* normalize revision क्रम the driver */
	revision = UART_BUILD_REVISION(major, minor);

	चयन (revision) अणु
	हाल OMAP_UART_REV_46:
		priv->habit |= UART_ERRATA_i202_MDR1_ACCESS;
		अवरोध;
	हाल OMAP_UART_REV_52:
		priv->habit |= UART_ERRATA_i202_MDR1_ACCESS |
				OMAP_UART_WER_HAS_TX_WAKEUP;
		अवरोध;
	हाल OMAP_UART_REV_63:
		priv->habit |= UART_ERRATA_i202_MDR1_ACCESS |
			OMAP_UART_WER_HAS_TX_WAKEUP;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * AM65x SR1.0, AM65x SR2.0 and J721e SR1.0 करोn't
	 * करोn't have RHR_IT_DIS bit in IER2 रेजिस्टर. So drop to flag
	 * to enable errata workaround.
	 */
	अगर (soc_device_match(k3_soc_devices))
		priv->habit &= ~UART_HAS_RHR_IT_DIS;
पूर्ण

अटल व्योम omap8250_uart_qos_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा omap8250_priv *priv;

	priv = container_of(work, काष्ठा omap8250_priv, qos_work);
	cpu_latency_qos_update_request(&priv->pm_qos_request, priv->latency);
पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250_DMA
अटल पूर्णांक omap_8250_dma_handle_irq(काष्ठा uart_port *port);
#पूर्ण_अगर

अटल irqवापस_t omap8250_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	अचिन्हित पूर्णांक iir;
	पूर्णांक ret;

#अगर_घोषित CONFIG_SERIAL_8250_DMA
	अगर (up->dma) अणु
		ret = omap_8250_dma_handle_irq(port);
		वापस IRQ_RETVAL(ret);
	पूर्ण
#पूर्ण_अगर

	serial8250_rpm_get(up);
	iir = serial_port_in(port, UART_IIR);
	ret = serial8250_handle_irq(port, iir);
	serial8250_rpm_put(up);

	वापस IRQ_RETVAL(ret);
पूर्ण

अटल पूर्णांक omap_8250_startup(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	काष्ठा omap8250_priv *priv = port->निजी_data;
	पूर्णांक ret;

	अगर (priv->wakeirq) अणु
		ret = dev_pm_set_dedicated_wake_irq(port->dev, priv->wakeirq);
		अगर (ret)
			वापस ret;
	पूर्ण

	pm_runसमय_get_sync(port->dev);

	up->mcr = 0;
	serial_out(up, UART_FCR, UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);

	serial_out(up, UART_LCR, UART_LCR_WLEN8);

	up->lsr_saved_flags = 0;
	up->msr_saved_flags = 0;

	/* Disable DMA क्रम console UART */
	अगर (uart_console(port))
		up->dma = शून्य;

	अगर (up->dma) अणु
		ret = serial8250_request_dma(up);
		अगर (ret) अणु
			dev_warn_ratelimited(port->dev,
					     "failed to request DMA\n");
			up->dma = शून्य;
		पूर्ण
	पूर्ण

	ret = request_irq(port->irq, omap8250_irq, IRQF_SHARED,
			  dev_name(port->dev), port);
	अगर (ret < 0)
		जाओ err;

	up->ier = UART_IER_RLSI | UART_IER_RDI;
	serial_out(up, UART_IER, up->ier);

#अगर_घोषित CONFIG_PM
	up->capabilities |= UART_CAP_RPM;
#पूर्ण_अगर

	/* Enable module level wake up */
	priv->wer = OMAP_UART_WER_MOD_WKUP;
	अगर (priv->habit & OMAP_UART_WER_HAS_TX_WAKEUP)
		priv->wer |= OMAP_UART_TX_WAKEUP_EN;
	serial_out(up, UART_OMAP_WER, priv->wer);

	अगर (up->dma && !(priv->habit & UART_HAS_EFR2))
		up->dma->rx_dma(up);

	pm_runसमय_mark_last_busy(port->dev);
	pm_runसमय_put_स्वतःsuspend(port->dev);
	वापस 0;
err:
	pm_runसमय_mark_last_busy(port->dev);
	pm_runसमय_put_स्वतःsuspend(port->dev);
	dev_pm_clear_wake_irq(port->dev);
	वापस ret;
पूर्ण

अटल व्योम omap_8250_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	काष्ठा omap8250_priv *priv = port->निजी_data;

	flush_work(&priv->qos_work);
	अगर (up->dma)
		omap_8250_rx_dma_flush(up);

	pm_runसमय_get_sync(port->dev);

	serial_out(up, UART_OMAP_WER, 0);
	अगर (priv->habit & UART_HAS_EFR2)
		serial_out(up, UART_OMAP_EFR2, 0x0);

	up->ier = 0;
	serial_out(up, UART_IER, 0);

	अगर (up->dma)
		serial8250_release_dma(up);

	/*
	 * Disable अवरोध condition and FIFOs
	 */
	अगर (up->lcr & UART_LCR_SBC)
		serial_out(up, UART_LCR, up->lcr & ~UART_LCR_SBC);
	serial_out(up, UART_FCR, UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);

	pm_runसमय_mark_last_busy(port->dev);
	pm_runसमय_put_स्वतःsuspend(port->dev);
	मुक्त_irq(port->irq, port);
	dev_pm_clear_wake_irq(port->dev);
पूर्ण

अटल व्योम omap_8250_throttle(काष्ठा uart_port *port)
अणु
	काष्ठा omap8250_priv *priv = port->निजी_data;
	अचिन्हित दीर्घ flags;

	pm_runसमय_get_sync(port->dev);

	spin_lock_irqsave(&port->lock, flags);
	port->ops->stop_rx(port);
	priv->throttled = true;
	spin_unlock_irqrestore(&port->lock, flags);

	pm_runसमय_mark_last_busy(port->dev);
	pm_runसमय_put_स्वतःsuspend(port->dev);
पूर्ण

अटल व्योम omap_8250_unthrottle(काष्ठा uart_port *port)
अणु
	काष्ठा omap8250_priv *priv = port->निजी_data;
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	अचिन्हित दीर्घ flags;

	pm_runसमय_get_sync(port->dev);

	spin_lock_irqsave(&port->lock, flags);
	priv->throttled = false;
	अगर (up->dma)
		up->dma->rx_dma(up);
	up->ier |= UART_IER_RLSI | UART_IER_RDI;
	port->पढ़ो_status_mask |= UART_LSR_DR;
	serial_out(up, UART_IER, up->ier);
	spin_unlock_irqrestore(&port->lock, flags);

	pm_runसमय_mark_last_busy(port->dev);
	pm_runसमय_put_स्वतःsuspend(port->dev);
पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250_DMA
अटल पूर्णांक omap_8250_rx_dma(काष्ठा uart_8250_port *p);

/* Must be called जबतक priv->rx_dma_lock is held */
अटल व्योम __dma_rx_करो_complete(काष्ठा uart_8250_port *p)
अणु
	काष्ठा uart_8250_dma    *dma = p->dma;
	काष्ठा tty_port         *tty_port = &p->port.state->port;
	काष्ठा omap8250_priv	*priv = p->port.निजी_data;
	काष्ठा dma_chan		*rxchan = dma->rxchan;
	dma_cookie_t		cookie;
	काष्ठा dma_tx_state     state;
	पूर्णांक                     count;
	पूर्णांक			ret;
	u32			reg;

	अगर (!dma->rx_running)
		जाओ out;

	cookie = dma->rx_cookie;
	dma->rx_running = 0;

	/* Re-enable RX FIFO पूर्णांकerrupt now that transfer is complete */
	अगर (priv->habit & UART_HAS_RHR_IT_DIS) अणु
		reg = serial_in(p, UART_OMAP_IER2);
		reg &= ~UART_OMAP_IER2_RHR_IT_DIS;
		serial_out(p, UART_OMAP_IER2, UART_OMAP_IER2_RHR_IT_DIS);
	पूर्ण

	dmaengine_tx_status(rxchan, cookie, &state);

	count = dma->rx_size - state.residue + state.in_flight_bytes;
	अगर (count < dma->rx_size) अणु
		dmaengine_terminate_async(rxchan);

		/*
		 * Poll क्रम tearकरोwn to complete which guarantees in
		 * flight data is drained.
		 */
		अगर (state.in_flight_bytes) अणु
			पूर्णांक poll_count = 25;

			जबतक (dmaengine_tx_status(rxchan, cookie, शून्य) &&
			       poll_count--)
				cpu_relax();

			अगर (!poll_count)
				dev_err(p->port.dev, "teardown incomplete\n");
		पूर्ण
	पूर्ण
	अगर (!count)
		जाओ out;
	ret = tty_insert_flip_string(tty_port, dma->rx_buf, count);

	p->port.icount.rx += ret;
	p->port.icount.buf_overrun += count - ret;
out:

	tty_flip_buffer_push(tty_port);
पूर्ण

अटल व्योम __dma_rx_complete(व्योम *param)
अणु
	काष्ठा uart_8250_port *p = param;
	काष्ठा omap8250_priv *priv = p->port.निजी_data;
	काष्ठा uart_8250_dma *dma = p->dma;
	काष्ठा dma_tx_state     state;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&p->port.lock, flags);

	/*
	 * If the tx status is not DMA_COMPLETE, then this is a delayed
	 * completion callback. A previous RX समयout flush would have
	 * alपढ़ोy pushed the data, so निकास.
	 */
	अगर (dmaengine_tx_status(dma->rxchan, dma->rx_cookie, &state) !=
			DMA_COMPLETE) अणु
		spin_unlock_irqrestore(&p->port.lock, flags);
		वापस;
	पूर्ण
	__dma_rx_करो_complete(p);
	अगर (!priv->throttled) अणु
		p->ier |= UART_IER_RLSI | UART_IER_RDI;
		serial_out(p, UART_IER, p->ier);
		अगर (!(priv->habit & UART_HAS_EFR2))
			omap_8250_rx_dma(p);
	पूर्ण

	spin_unlock_irqrestore(&p->port.lock, flags);
पूर्ण

अटल व्योम omap_8250_rx_dma_flush(काष्ठा uart_8250_port *p)
अणु
	काष्ठा omap8250_priv	*priv = p->port.निजी_data;
	काष्ठा uart_8250_dma	*dma = p->dma;
	काष्ठा dma_tx_state     state;
	अचिन्हित दीर्घ		flags;
	पूर्णांक ret;

	spin_lock_irqsave(&priv->rx_dma_lock, flags);

	अगर (!dma->rx_running) अणु
		spin_unlock_irqrestore(&priv->rx_dma_lock, flags);
		वापस;
	पूर्ण

	ret = dmaengine_tx_status(dma->rxchan, dma->rx_cookie, &state);
	अगर (ret == DMA_IN_PROGRESS) अणु
		ret = dmaengine_छोड़ो(dma->rxchan);
		अगर (WARN_ON_ONCE(ret))
			priv->rx_dma_broken = true;
	पूर्ण
	__dma_rx_करो_complete(p);
	spin_unlock_irqrestore(&priv->rx_dma_lock, flags);
पूर्ण

अटल पूर्णांक omap_8250_rx_dma(काष्ठा uart_8250_port *p)
अणु
	काष्ठा omap8250_priv		*priv = p->port.निजी_data;
	काष्ठा uart_8250_dma            *dma = p->dma;
	पूर्णांक				err = 0;
	काष्ठा dma_async_tx_descriptor  *desc;
	अचिन्हित दीर्घ			flags;
	u32				reg;

	अगर (priv->rx_dma_broken)
		वापस -EINVAL;

	spin_lock_irqsave(&priv->rx_dma_lock, flags);

	अगर (dma->rx_running) अणु
		क्रमागत dma_status state;

		state = dmaengine_tx_status(dma->rxchan, dma->rx_cookie, शून्य);
		अगर (state == DMA_COMPLETE) अणु
			/*
			 * Disable RX पूर्णांकerrupts to allow RX DMA completion
			 * callback to run.
			 */
			p->ier &= ~(UART_IER_RLSI | UART_IER_RDI);
			serial_out(p, UART_IER, p->ier);
		पूर्ण
		जाओ out;
	पूर्ण

	desc = dmaengine_prep_slave_single(dma->rxchan, dma->rx_addr,
					   dma->rx_size, DMA_DEV_TO_MEM,
					   DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	dma->rx_running = 1;
	desc->callback = __dma_rx_complete;
	desc->callback_param = p;

	dma->rx_cookie = dmaengine_submit(desc);

	/*
	 * Disable RX FIFO पूर्णांकerrupt जबतक RX DMA is enabled, अन्यथा
	 * spurious पूर्णांकerrupt may be उठाओd when data is in the RX FIFO
	 * but is yet to be drained by DMA.
	 */
	अगर (priv->habit & UART_HAS_RHR_IT_DIS) अणु
		reg = serial_in(p, UART_OMAP_IER2);
		reg |= UART_OMAP_IER2_RHR_IT_DIS;
		serial_out(p, UART_OMAP_IER2, UART_OMAP_IER2_RHR_IT_DIS);
	पूर्ण

	dma_async_issue_pending(dma->rxchan);
out:
	spin_unlock_irqrestore(&priv->rx_dma_lock, flags);
	वापस err;
पूर्ण

अटल पूर्णांक omap_8250_tx_dma(काष्ठा uart_8250_port *p);

अटल व्योम omap_8250_dma_tx_complete(व्योम *param)
अणु
	काष्ठा uart_8250_port	*p = param;
	काष्ठा uart_8250_dma	*dma = p->dma;
	काष्ठा circ_buf		*xmit = &p->port.state->xmit;
	अचिन्हित दीर्घ		flags;
	bool			en_thri = false;
	काष्ठा omap8250_priv	*priv = p->port.निजी_data;

	dma_sync_single_क्रम_cpu(dma->txchan->device->dev, dma->tx_addr,
				UART_XMIT_SIZE, DMA_TO_DEVICE);

	spin_lock_irqsave(&p->port.lock, flags);

	dma->tx_running = 0;

	xmit->tail += dma->tx_size;
	xmit->tail &= UART_XMIT_SIZE - 1;
	p->port.icount.tx += dma->tx_size;

	अगर (priv->delayed_restore) अणु
		priv->delayed_restore = 0;
		omap8250_restore_regs(p);
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&p->port);

	अगर (!uart_circ_empty(xmit) && !uart_tx_stopped(&p->port)) अणु
		पूर्णांक ret;

		ret = omap_8250_tx_dma(p);
		अगर (ret)
			en_thri = true;
	पूर्ण अन्यथा अगर (p->capabilities & UART_CAP_RPM) अणु
		en_thri = true;
	पूर्ण

	अगर (en_thri) अणु
		dma->tx_err = 1;
		serial8250_set_THRI(p);
	पूर्ण

	spin_unlock_irqrestore(&p->port.lock, flags);
पूर्ण

अटल पूर्णांक omap_8250_tx_dma(काष्ठा uart_8250_port *p)
अणु
	काष्ठा uart_8250_dma		*dma = p->dma;
	काष्ठा omap8250_priv		*priv = p->port.निजी_data;
	काष्ठा circ_buf			*xmit = &p->port.state->xmit;
	काष्ठा dma_async_tx_descriptor	*desc;
	अचिन्हित पूर्णांक	skip_byte = 0;
	पूर्णांक ret;

	अगर (dma->tx_running)
		वापस 0;
	अगर (uart_tx_stopped(&p->port) || uart_circ_empty(xmit)) अणु

		/*
		 * Even अगर no data, we need to वापस an error क्रम the two हालs
		 * below so serial8250_tx_अक्षरs() is invoked and properly clears
		 * THRI and/or runसमय suspend.
		 */
		अगर (dma->tx_err || p->capabilities & UART_CAP_RPM) अणु
			ret = -EBUSY;
			जाओ err;
		पूर्ण
		serial8250_clear_THRI(p);
		वापस 0;
	पूर्ण

	dma->tx_size = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);
	अगर (priv->habit & OMAP_DMA_TX_KICK) अणु
		u8 tx_lvl;

		/*
		 * We need to put the first byte पूर्णांकo the FIFO in order to start
		 * the DMA transfer. For transfers smaller than four bytes we
		 * करोn't bother करोing DMA at all. It seem not matter अगर there
		 * are still bytes in the FIFO from the last transfer (in हाल
		 * we got here directly from omap_8250_dma_tx_complete()). Bytes
		 * leaving the FIFO seem not to trigger the DMA transfer. It is
		 * really the byte that we put पूर्णांकo the FIFO.
		 * If the FIFO is alपढ़ोy full then we most likely got here from
		 * omap_8250_dma_tx_complete(). And this means the DMA engine
		 * just completed its work. We करोn't have to रुको the complete
		 * 86us at 115200,8n1 but around 60us (not to mention lower
		 * baudrates). So in that हाल we take the पूर्णांकerrupt and try
		 * again with an empty FIFO.
		 */
		tx_lvl = serial_in(p, UART_OMAP_TX_LVL);
		अगर (tx_lvl == p->tx_loadsz) अणु
			ret = -EBUSY;
			जाओ err;
		पूर्ण
		अगर (dma->tx_size < 4) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		skip_byte = 1;
	पूर्ण

	desc = dmaengine_prep_slave_single(dma->txchan,
			dma->tx_addr + xmit->tail + skip_byte,
			dma->tx_size - skip_byte, DMA_MEM_TO_DEV,
			DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc) अणु
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	dma->tx_running = 1;

	desc->callback = omap_8250_dma_tx_complete;
	desc->callback_param = p;

	dma->tx_cookie = dmaengine_submit(desc);

	dma_sync_single_क्रम_device(dma->txchan->device->dev, dma->tx_addr,
				   UART_XMIT_SIZE, DMA_TO_DEVICE);

	dma_async_issue_pending(dma->txchan);
	अगर (dma->tx_err)
		dma->tx_err = 0;

	serial8250_clear_THRI(p);
	अगर (skip_byte)
		serial_out(p, UART_TX, xmit->buf[xmit->tail]);
	वापस 0;
err:
	dma->tx_err = 1;
	वापस ret;
पूर्ण

अटल bool handle_rx_dma(काष्ठा uart_8250_port *up, अचिन्हित पूर्णांक iir)
अणु
	चयन (iir & 0x3f) अणु
	हाल UART_IIR_RLSI:
	हाल UART_IIR_RX_TIMEOUT:
	हाल UART_IIR_RDI:
		omap_8250_rx_dma_flush(up);
		वापस true;
	पूर्ण
	वापस omap_8250_rx_dma(up);
पूर्ण

अटल अचिन्हित अक्षर omap_8250_handle_rx_dma(काष्ठा uart_8250_port *up,
					     u8 iir, अचिन्हित अक्षर status)
अणु
	अगर ((status & (UART_LSR_DR | UART_LSR_BI)) &&
	    (iir & UART_IIR_RDI)) अणु
		अगर (handle_rx_dma(up, iir)) अणु
			status = serial8250_rx_अक्षरs(up, status);
			omap_8250_rx_dma(up);
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम am654_8250_handle_rx_dma(काष्ठा uart_8250_port *up, u8 iir,
				     अचिन्हित अक्षर status)
अणु
	/*
	 * Queue a new transfer अगर FIFO has data.
	 */
	अगर ((status & (UART_LSR_DR | UART_LSR_BI)) &&
	    (up->ier & UART_IER_RDI)) अणु
		omap_8250_rx_dma(up);
		serial_out(up, UART_OMAP_EFR2, UART_OMAP_EFR2_TIMEOUT_BEHAVE);
	पूर्ण अन्यथा अगर ((iir & 0x3f) == UART_IIR_RX_TIMEOUT) अणु
		/*
		 * Disable RX समयout, पढ़ो IIR to clear
		 * current समयout condition, clear EFR2 to
		 * periodic समयouts, re-enable पूर्णांकerrupts.
		 */
		up->ier &= ~(UART_IER_RLSI | UART_IER_RDI);
		serial_out(up, UART_IER, up->ier);
		omap_8250_rx_dma_flush(up);
		serial_in(up, UART_IIR);
		serial_out(up, UART_OMAP_EFR2, 0x0);
		up->ier |= UART_IER_RLSI | UART_IER_RDI;
		serial_out(up, UART_IER, up->ier);
	पूर्ण
पूर्ण

/*
 * This is mostly serial8250_handle_irq(). We have a slightly dअगरferent DMA
 * hoook क्रम RX/TX and need dअगरferent logic क्रम them in the ISR. Thereक्रमe we
 * use the शेष routine in the non-DMA हाल and this one क्रम with DMA.
 */
अटल पूर्णांक omap_8250_dma_handle_irq(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	काष्ठा omap8250_priv *priv = up->port.निजी_data;
	अचिन्हित अक्षर status;
	u8 iir;

	serial8250_rpm_get(up);

	iir = serial_port_in(port, UART_IIR);
	अगर (iir & UART_IIR_NO_INT) अणु
		serial8250_rpm_put(up);
		वापस IRQ_HANDLED;
	पूर्ण

	spin_lock(&port->lock);

	status = serial_port_in(port, UART_LSR);

	अगर (priv->habit & UART_HAS_EFR2)
		am654_8250_handle_rx_dma(up, iir, status);
	अन्यथा
		status = omap_8250_handle_rx_dma(up, iir, status);

	serial8250_modem_status(up);
	अगर (status & UART_LSR_THRE && up->dma->tx_err) अणु
		अगर (uart_tx_stopped(&up->port) ||
		    uart_circ_empty(&up->port.state->xmit)) अणु
			up->dma->tx_err = 0;
			serial8250_tx_अक्षरs(up);
		पूर्ण अन्यथा  अणु
			/*
			 * try again due to an earlier failer which
			 * might have been resolved by now.
			 */
			अगर (omap_8250_tx_dma(up))
				serial8250_tx_अक्षरs(up);
		पूर्ण
	पूर्ण

	uart_unlock_and_check_sysrq(port);

	serial8250_rpm_put(up);
	वापस 1;
पूर्ण

अटल bool the_no_dma_filter_fn(काष्ठा dma_chan *chan, व्योम *param)
अणु
	वापस false;
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक omap_8250_rx_dma(काष्ठा uart_8250_port *p)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक omap8250_no_handle_irq(काष्ठा uart_port *port)
अणु
	/* IRQ has not been requested but handling irq? */
	WARN_ONCE(1, "Unexpected irq handling before port startup\n");
	वापस 0;
पूर्ण

अटल काष्ठा omap8250_dma_params am654_dma = अणु
	.rx_size = SZ_2K,
	.rx_trigger = 1,
	.tx_trigger = TX_TRIGGER,
पूर्ण;

अटल काष्ठा omap8250_dma_params am33xx_dma = अणु
	.rx_size = RX_TRIGGER,
	.rx_trigger = RX_TRIGGER,
	.tx_trigger = TX_TRIGGER,
पूर्ण;

अटल काष्ठा omap8250_platdata am654_platdata = अणु
	.dma_params	= &am654_dma,
	.habit		= UART_HAS_EFR2 | UART_HAS_RHR_IT_DIS,
पूर्ण;

अटल काष्ठा omap8250_platdata am33xx_platdata = अणु
	.dma_params	= &am33xx_dma,
	.habit		= OMAP_DMA_TX_KICK | UART_ERRATA_CLOCK_DISABLE,
पूर्ण;

अटल काष्ठा omap8250_platdata omap4_platdata = अणु
	.dma_params	= &am33xx_dma,
	.habit		= UART_ERRATA_CLOCK_DISABLE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap8250_dt_ids[] = अणु
	अणु .compatible = "ti,am654-uart", .data = &am654_platdata, पूर्ण,
	अणु .compatible = "ti,omap2-uart" पूर्ण,
	अणु .compatible = "ti,omap3-uart" पूर्ण,
	अणु .compatible = "ti,omap4-uart", .data = &omap4_platdata, पूर्ण,
	अणु .compatible = "ti,am3352-uart", .data = &am33xx_platdata, पूर्ण,
	अणु .compatible = "ti,am4372-uart", .data = &am33xx_platdata, पूर्ण,
	अणु .compatible = "ti,dra742-uart", .data = &omap4_platdata, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap8250_dt_ids);

अटल पूर्णांक omap8250_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा omap8250_priv *priv;
	स्थिर काष्ठा omap8250_platdata *pdata;
	काष्ठा uart_8250_port up;
	काष्ठा resource *regs;
	व्योम __iomem *membase;
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!regs) अणु
		dev_err(&pdev->dev, "missing registers\n");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	membase = devm_ioremap(&pdev->dev, regs->start,
				       resource_size(regs));
	अगर (!membase)
		वापस -ENODEV;

	स_रखो(&up, 0, माप(up));
	up.port.dev = &pdev->dev;
	up.port.mapbase = regs->start;
	up.port.membase = membase;
	up.port.irq = irq;
	/*
	 * It claims to be 16C750 compatible however it is a little dअगरferent.
	 * It has EFR and has no FCR7_64byte bit. The AFE (which it claims to
	 * have) is enabled via EFR instead of MCR. The type is set here 8250
	 * just to get things going. UNKNOWN करोes not work क्रम a few reasons and
	 * we करोn't need our own type since we don't use 8250's set_termios()
	 * or pm callback.
	 */
	up.port.type = PORT_8250;
	up.port.iotype = UPIO_MEM;
	up.port.flags = UPF_FIXED_PORT | UPF_FIXED_TYPE | UPF_SOFT_FLOW |
		UPF_HARD_FLOW;
	up.port.निजी_data = priv;

	up.port.regshअगरt = 2;
	up.port.fअगरosize = 64;
	up.tx_loadsz = 64;
	up.capabilities = UART_CAP_FIFO;
#अगर_घोषित CONFIG_PM
	/*
	 * Runसमय PM is mostly transparent. However to करो it right we need to a
	 * TX empty पूर्णांकerrupt beक्रमe we can put the device to स्वतः idle. So अगर
	 * PM is not enabled we करोn't add that flag and can spare that one extra
	 * पूर्णांकerrupt in the TX path.
	 */
	up.capabilities |= UART_CAP_RPM;
#पूर्ण_अगर
	up.port.set_termios = omap_8250_set_termios;
	up.port.set_mctrl = omap8250_set_mctrl;
	up.port.pm = omap_8250_pm;
	up.port.startup = omap_8250_startup;
	up.port.shutकरोwn = omap_8250_shutकरोwn;
	up.port.throttle = omap_8250_throttle;
	up.port.unthrottle = omap_8250_unthrottle;
	up.port.rs485_config = serial8250_em485_config;
	up.rs485_start_tx = serial8250_em485_start_tx;
	up.rs485_stop_tx = serial8250_em485_stop_tx;
	up.port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_8250_CONSOLE);

	ret = of_alias_get_id(np, "serial");
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to get alias\n");
		वापस ret;
	पूर्ण
	up.port.line = ret;

	अगर (of_property_पढ़ो_u32(np, "clock-frequency", &up.port.uartclk)) अणु
		काष्ठा clk *clk;

		clk = devm_clk_get(&pdev->dev, शून्य);
		अगर (IS_ERR(clk)) अणु
			अगर (PTR_ERR(clk) == -EPROBE_DEFER)
				वापस -EPROBE_DEFER;
		पूर्ण अन्यथा अणु
			up.port.uartclk = clk_get_rate(clk);
		पूर्ण
	पूर्ण

	priv->wakeirq = irq_of_parse_and_map(np, 1);

	pdata = of_device_get_match_data(&pdev->dev);
	अगर (pdata)
		priv->habit |= pdata->habit;

	अगर (!up.port.uartclk) अणु
		up.port.uartclk = DEFAULT_CLK_SPEED;
		dev_warn(&pdev->dev,
			 "No clock speed specified: using default: %d\n",
			 DEFAULT_CLK_SPEED);
	पूर्ण

	priv->latency = PM_QOS_CPU_LATENCY_DEFAULT_VALUE;
	priv->calc_latency = PM_QOS_CPU_LATENCY_DEFAULT_VALUE;
	cpu_latency_qos_add_request(&priv->pm_qos_request, priv->latency);
	INIT_WORK(&priv->qos_work, omap8250_uart_qos_work);

	spin_lock_init(&priv->rx_dma_lock);

	device_init_wakeup(&pdev->dev, true);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);

	/*
	 * Disable runसमय PM until स्वतःsuspend delay unless specअगरically
	 * enabled by the user via sysfs. This is the historic way to
	 * prevent an unsafe शेष policy with lossy अक्षरacters on wake-up.
	 * For serdev devices this is not needed, the policy can be managed by
	 * the serdev driver.
	 */
	अगर (!of_get_available_child_count(pdev->dev.of_node))
		pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, -1);

	pm_runसमय_irq_safe(&pdev->dev);

	pm_runसमय_get_sync(&pdev->dev);

	omap_serial_fill_features_erratas(&up, priv);
	up.port.handle_irq = omap8250_no_handle_irq;
	priv->rx_trigger = RX_TRIGGER;
	priv->tx_trigger = TX_TRIGGER;
#अगर_घोषित CONFIG_SERIAL_8250_DMA
	/*
	 * Oh DMA support. If there are no DMA properties in the DT then
	 * we will fall back to a generic DMA channel which करोes not
	 * really work here. To ensure that we करो not get a generic DMA
	 * channel asचिन्हित, we have the the_no_dma_filter_fn() here.
	 * To aव्योम "failed to request DMA" messages we check क्रम DMA
	 * properties in DT.
	 */
	ret = of_property_count_strings(np, "dma-names");
	अगर (ret == 2) अणु
		काष्ठा omap8250_dma_params *dma_params = शून्य;

		up.dma = &priv->omap8250_dma;
		up.dma->fn = the_no_dma_filter_fn;
		up.dma->tx_dma = omap_8250_tx_dma;
		up.dma->rx_dma = omap_8250_rx_dma;
		अगर (pdata)
			dma_params = pdata->dma_params;

		अगर (dma_params) अणु
			up.dma->rx_size = dma_params->rx_size;
			up.dma->rxconf.src_maxburst = dma_params->rx_trigger;
			up.dma->txconf.dst_maxburst = dma_params->tx_trigger;
			priv->rx_trigger = dma_params->rx_trigger;
			priv->tx_trigger = dma_params->tx_trigger;
		पूर्ण अन्यथा अणु
			up.dma->rx_size = RX_TRIGGER;
			up.dma->rxconf.src_maxburst = RX_TRIGGER;
			up.dma->txconf.dst_maxburst = TX_TRIGGER;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	ret = serial8250_रेजिस्टर_8250_port(&up);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "unable to register 8250 port\n");
		जाओ err;
	पूर्ण
	priv->line = ret;
	platक्रमm_set_drvdata(pdev, priv);
	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);
	वापस 0;
err:
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक omap8250_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap8250_priv *priv = platक्रमm_get_drvdata(pdev);

	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	serial8250_unरेजिस्टर_port(priv->line);
	cpu_latency_qos_हटाओ_request(&priv->pm_qos_request);
	device_init_wakeup(&pdev->dev, false);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक omap8250_prepare(काष्ठा device *dev)
अणु
	काष्ठा omap8250_priv *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस 0;
	priv->is_suspending = true;
	वापस 0;
पूर्ण

अटल व्योम omap8250_complete(काष्ठा device *dev)
अणु
	काष्ठा omap8250_priv *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस;
	priv->is_suspending = false;
पूर्ण

अटल पूर्णांक omap8250_suspend(काष्ठा device *dev)
अणु
	काष्ठा omap8250_priv *priv = dev_get_drvdata(dev);
	काष्ठा uart_8250_port *up = serial8250_get_port(priv->line);

	serial8250_suspend_port(priv->line);

	pm_runसमय_get_sync(dev);
	अगर (!device_may_wakeup(dev))
		priv->wer = 0;
	serial_out(up, UART_OMAP_WER, priv->wer);
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	flush_work(&priv->qos_work);
	वापस 0;
पूर्ण

अटल पूर्णांक omap8250_resume(काष्ठा device *dev)
अणु
	काष्ठा omap8250_priv *priv = dev_get_drvdata(dev);

	serial8250_resume_port(priv->line);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा omap8250_prepare शून्य
#घोषणा omap8250_complete शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक omap8250_lost_context(काष्ठा uart_8250_port *up)
अणु
	u32 val;

	val = serial_in(up, UART_OMAP_SCR);
	/*
	 * If we lose context, then SCR is set to its reset value of zero.
	 * After set_termios() we set bit 3 of SCR (TX_EMPTY_CTL_IT) to 1,
	 * among other bits, to never set the रेजिस्टर back to zero again.
	 */
	अगर (!val)
		वापस 1;
	वापस 0;
पूर्ण

/* TODO: in future, this should happen via API in drivers/reset/ */
अटल पूर्णांक omap8250_soft_reset(काष्ठा device *dev)
अणु
	काष्ठा omap8250_priv *priv = dev_get_drvdata(dev);
	काष्ठा uart_8250_port *up = serial8250_get_port(priv->line);
	पूर्णांक समयout = 100;
	पूर्णांक sysc;
	पूर्णांक syss;

	/*
	 * At least on omap4, unused uarts may not idle after reset without
	 * a basic scr dma configuration even with no dma in use. The
	 * module clkctrl status bits will be 1 instead of 3 blocking idle
	 * क्रम the whole घड़ीकरोमुख्य. The softreset below will clear scr,
	 * and we restore it on resume so this is safe to करो on all SoCs
	 * needing omap8250_soft_reset() quirk. Do it in two ग_लिखोs as
	 * recommended in the comment क्रम omap8250_update_scr().
	 */
	serial_out(up, UART_OMAP_SCR, OMAP_UART_SCR_DMAMODE_1);
	serial_out(up, UART_OMAP_SCR,
		   OMAP_UART_SCR_DMAMODE_1 | OMAP_UART_SCR_DMAMODE_CTL);

	sysc = serial_in(up, UART_OMAP_SYSC);

	/* softreset the UART */
	sysc |= OMAP_UART_SYSC_SOFTRESET;
	serial_out(up, UART_OMAP_SYSC, sysc);

	/* By experiments, 1us enough क्रम reset complete on AM335x */
	करो अणु
		udelay(1);
		syss = serial_in(up, UART_OMAP_SYSS);
	पूर्ण जबतक (--समयout && !(syss & OMAP_UART_SYSS_RESETDONE));

	अगर (!समयout) अणु
		dev_err(dev, "timed out waiting for reset done\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap8250_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा omap8250_priv *priv = dev_get_drvdata(dev);
	काष्ठा uart_8250_port *up;

	/* In हाल runसमय-pm tries this beक्रमe we are setup */
	अगर (!priv)
		वापस 0;

	up = serial8250_get_port(priv->line);
	/*
	 * When using 'no_console_suspend', the console UART must not be
	 * suspended. Since driver suspend is managed by runसमय suspend,
	 * preventing runसमय suspend (by वापसing error) will keep device
	 * active during suspend.
	 */
	अगर (priv->is_suspending && !console_suspend_enabled) अणु
		अगर (uart_console(&up->port))
			वापस -EBUSY;
	पूर्ण

	अगर (priv->habit & UART_ERRATA_CLOCK_DISABLE) अणु
		पूर्णांक ret;

		ret = omap8250_soft_reset(dev);
		अगर (ret)
			वापस ret;

		/* Restore to UART mode after reset (क्रम wakeup) */
		omap8250_update_mdr1(up, priv);
		/* Restore wakeup enable रेजिस्टर */
		serial_out(up, UART_OMAP_WER, priv->wer);
	पूर्ण

	अगर (up->dma && up->dma->rxchan)
		omap_8250_rx_dma_flush(up);

	priv->latency = PM_QOS_CPU_LATENCY_DEFAULT_VALUE;
	schedule_work(&priv->qos_work);

	वापस 0;
पूर्ण

अटल पूर्णांक omap8250_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा omap8250_priv *priv = dev_get_drvdata(dev);
	काष्ठा uart_8250_port *up;

	/* In हाल runसमय-pm tries this beक्रमe we are setup */
	अगर (!priv)
		वापस 0;

	up = serial8250_get_port(priv->line);

	अगर (omap8250_lost_context(up))
		omap8250_restore_regs(up);

	अगर (up->dma && up->dma->rxchan && !(priv->habit & UART_HAS_EFR2))
		omap_8250_rx_dma(up);

	priv->latency = priv->calc_latency;
	schedule_work(&priv->qos_work);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SERIAL_8250_OMAP_TTYO_FIXUP
अटल पूर्णांक __init omap8250_console_fixup(व्योम)
अणु
	अक्षर *omap_str;
	अक्षर *options;
	u8 idx;

	अगर (म_माला(boot_command_line, "console=ttyS"))
		/* user set a ttyS based name क्रम the console */
		वापस 0;

	omap_str = म_माला(boot_command_line, "console=ttyO");
	अगर (!omap_str)
		/* user did not set ttyO based console, so we करोn't care */
		वापस 0;

	omap_str += 12;
	अगर ('0' <= *omap_str && *omap_str <= '9')
		idx = *omap_str - '0';
	अन्यथा
		वापस 0;

	omap_str++;
	अगर (omap_str[0] == ',') अणु
		omap_str++;
		options = omap_str;
	पूर्ण अन्यथा अणु
		options = शून्य;
	पूर्ण

	add_preferred_console("ttyS", idx, options);
	pr_err("WARNING: Your 'console=ttyO%d' has been replaced by 'ttyS%d'\n",
	       idx, idx);
	pr_err("This ensures that you still see kernel messages. Please\n");
	pr_err("update your kernel commandline.\n");
	वापस 0;
पूर्ण
console_initcall(omap8250_console_fixup);
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops omap8250_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(omap8250_suspend, omap8250_resume)
	SET_RUNTIME_PM_OPS(omap8250_runसमय_suspend,
			   omap8250_runसमय_resume, शून्य)
	.prepare        = omap8250_prepare,
	.complete       = omap8250_complete,
पूर्ण;

अटल काष्ठा platक्रमm_driver omap8250_platक्रमm_driver = अणु
	.driver = अणु
		.name		= "omap8250",
		.pm		= &omap8250_dev_pm_ops,
		.of_match_table = omap8250_dt_ids,
	पूर्ण,
	.probe			= omap8250_probe,
	.हटाओ			= omap8250_हटाओ,
पूर्ण;
module_platक्रमm_driver(omap8250_platक्रमm_driver);

MODULE_AUTHOR("Sebastian Andrzej Siewior");
MODULE_DESCRIPTION("OMAP 8250 Driver");
MODULE_LICENSE("GPL v2");
