<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम OMAP-UART controller.
 * Based on drivers/serial/8250.c
 *
 * Copyright (C) 2010 Texas Instruments.
 *
 * Authors:
 *	Govindraj R	<govindraj.raja@ti.com>
 *	Thara Gopinath	<thara@ti.com>
 *
 * Note: This driver is made separate from 8250 driver as we cannot
 * over load 8250 driver with omap platक्रमm specअगरic configuration क्रम
 * features like DMA, it makes easier to implement features like DMA and
 * hardware flow control and software flow control configuration with
 * this driver as required क्रम the omap-platक्रमm.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/irq.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/platक्रमm_data/serial-omap.h>

#घोषणा OMAP_MAX_HSUART_PORTS	10

#घोषणा UART_BUILD_REVISION(x, y)	(((x) << 8) | (y))

#घोषणा OMAP_UART_REV_42 0x0402
#घोषणा OMAP_UART_REV_46 0x0406
#घोषणा OMAP_UART_REV_52 0x0502
#घोषणा OMAP_UART_REV_63 0x0603

#घोषणा OMAP_UART_TX_WAKEUP_EN		BIT(7)

/* Feature flags */
#घोषणा OMAP_UART_WER_HAS_TX_WAKEUP	BIT(0)

#घोषणा UART_ERRATA_i202_MDR1_ACCESS	BIT(0)
#घोषणा UART_ERRATA_i291_DMA_FORCEIDLE	BIT(1)

#घोषणा DEFAULT_CLK_SPEED 48000000 /* 48Mhz */

/* SCR रेजिस्टर biपंचांगasks */
#घोषणा OMAP_UART_SCR_RX_TRIG_GRANU1_MASK		(1 << 7)
#घोषणा OMAP_UART_SCR_TX_TRIG_GRANU1_MASK		(1 << 6)
#घोषणा OMAP_UART_SCR_TX_EMPTY			(1 << 3)

/* FCR रेजिस्टर biपंचांगasks */
#घोषणा OMAP_UART_FCR_RX_FIFO_TRIG_MASK			(0x3 << 6)
#घोषणा OMAP_UART_FCR_TX_FIFO_TRIG_MASK			(0x3 << 4)

/* MVR रेजिस्टर biपंचांगasks */
#घोषणा OMAP_UART_MVR_SCHEME_SHIFT	30

#घोषणा OMAP_UART_LEGACY_MVR_MAJ_MASK	0xf0
#घोषणा OMAP_UART_LEGACY_MVR_MAJ_SHIFT	4
#घोषणा OMAP_UART_LEGACY_MVR_MIN_MASK	0x0f

#घोषणा OMAP_UART_MVR_MAJ_MASK		0x700
#घोषणा OMAP_UART_MVR_MAJ_SHIFT		8
#घोषणा OMAP_UART_MVR_MIN_MASK		0x3f

#घोषणा OMAP_UART_DMA_CH_FREE	-1

#घोषणा MSR_SAVE_FLAGS		UART_MSR_ANY_DELTA
#घोषणा OMAP_MODE13X_SPEED	230400

/* WER = 0x7F
 * Enable module level wakeup in WER reg
 */
#घोषणा OMAP_UART_WER_MOD_WKUP	0x7F

/* Enable XON/XOFF flow control on output */
#घोषणा OMAP_UART_SW_TX		0x08

/* Enable XON/XOFF flow control on input */
#घोषणा OMAP_UART_SW_RX		0x02

#घोषणा OMAP_UART_SW_CLR	0xF0

#घोषणा OMAP_UART_TCR_TRIG	0x0F

काष्ठा uart_omap_dma अणु
	u8			uart_dma_tx;
	u8			uart_dma_rx;
	पूर्णांक			rx_dma_channel;
	पूर्णांक			tx_dma_channel;
	dma_addr_t		rx_buf_dma_phys;
	dma_addr_t		tx_buf_dma_phys;
	अचिन्हित पूर्णांक		uart_base;
	/*
	 * Buffer क्रम rx dma. It is not required क्रम tx because the buffer
	 * comes from port काष्ठाure.
	 */
	अचिन्हित अक्षर		*rx_buf;
	अचिन्हित पूर्णांक		prev_rx_dma_pos;
	पूर्णांक			tx_buf_size;
	पूर्णांक			tx_dma_used;
	पूर्णांक			rx_dma_used;
	spinlock_t		tx_lock;
	spinlock_t		rx_lock;
	/* समयr to poll activity on rx dma */
	काष्ठा समयr_list	rx_समयr;
	अचिन्हित पूर्णांक		rx_buf_size;
	अचिन्हित पूर्णांक		rx_poll_rate;
	अचिन्हित पूर्णांक		rx_समयout;
पूर्ण;

काष्ठा uart_omap_port अणु
	काष्ठा uart_port	port;
	काष्ठा uart_omap_dma	uart_dma;
	काष्ठा device		*dev;
	पूर्णांक			wakeirq;

	अचिन्हित अक्षर		ier;
	अचिन्हित अक्षर		lcr;
	अचिन्हित अक्षर		mcr;
	अचिन्हित अक्षर		fcr;
	अचिन्हित अक्षर		efr;
	अचिन्हित अक्षर		dll;
	अचिन्हित अक्षर		dlh;
	अचिन्हित अक्षर		mdr1;
	अचिन्हित अक्षर		scr;
	अचिन्हित अक्षर		wer;

	पूर्णांक			use_dma;
	/*
	 * Some bits in रेजिस्टरs are cleared on a पढ़ो, so they must
	 * be saved whenever the रेजिस्टर is पढ़ो, but the bits will not
	 * be immediately processed.
	 */
	अचिन्हित पूर्णांक		lsr_अवरोध_flag;
	अचिन्हित अक्षर		msr_saved_flags;
	अक्षर			name[20];
	अचिन्हित दीर्घ		port_activity;
	पूर्णांक			context_loss_cnt;
	u32			errata;
	u32			features;

	काष्ठा gpio_desc	*rts_gpiod;

	काष्ठा pm_qos_request	pm_qos_request;
	u32			latency;
	u32			calc_latency;
	काष्ठा work_काष्ठा	qos_work;
	bool			is_suspending;

	अचिन्हित पूर्णांक		rs485_tx_filter_count;
पूर्ण;

#घोषणा to_uart_omap_port(p) ((container_of((p), काष्ठा uart_omap_port, port)))

अटल काष्ठा uart_omap_port *ui[OMAP_MAX_HSUART_PORTS];

/* Forward declaration of functions */
अटल व्योम serial_omap_mdr1_errataset(काष्ठा uart_omap_port *up, u8 mdr1);

अटल अंतरभूत अचिन्हित पूर्णांक serial_in(काष्ठा uart_omap_port *up, पूर्णांक offset)
अणु
	offset <<= up->port.regshअगरt;
	वापस पढ़ोw(up->port.membase + offset);
पूर्ण

अटल अंतरभूत व्योम serial_out(काष्ठा uart_omap_port *up, पूर्णांक offset, पूर्णांक value)
अणु
	offset <<= up->port.regshअगरt;
	ग_लिखोw(value, up->port.membase + offset);
पूर्ण

अटल अंतरभूत व्योम serial_omap_clear_fअगरos(काष्ठा uart_omap_port *up)
अणु
	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO);
	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO |
		       UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
	serial_out(up, UART_FCR, 0);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक serial_omap_get_context_loss_count(काष्ठा uart_omap_port *up)
अणु
	काष्ठा omap_uart_port_info *pdata = dev_get_platdata(up->dev);

	अगर (!pdata || !pdata->get_context_loss_count)
		वापस -EINVAL;

	वापस pdata->get_context_loss_count(up->dev);
पूर्ण

/* REVISIT: Remove this when omap3 boots in device tree only mode */
अटल व्योम serial_omap_enable_wakeup(काष्ठा uart_omap_port *up, bool enable)
अणु
	काष्ठा omap_uart_port_info *pdata = dev_get_platdata(up->dev);

	अगर (!pdata || !pdata->enable_wakeup)
		वापस;

	pdata->enable_wakeup(up->dev, enable);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

/*
 * Calculate the असलolute dअगरference between the desired and actual baud
 * rate क्रम the given mode.
 */
अटल अंतरभूत पूर्णांक calculate_baud_असल_dअगरf(काष्ठा uart_port *port,
				अचिन्हित पूर्णांक baud, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक n = port->uartclk / (mode * baud);
	पूर्णांक असल_dअगरf;

	अगर (n == 0)
		n = 1;

	असल_dअगरf = baud - (port->uartclk / (mode * n));
	अगर (असल_dअगरf < 0)
		असल_dअगरf = -असल_dअगरf;

	वापस असल_dअगरf;
पूर्ण

/*
 * serial_omap_baud_is_mode16 - check अगर baud rate is MODE16X
 * @port: uart port info
 * @baud: baudrate क्रम which mode needs to be determined
 *
 * Returns true अगर baud rate is MODE16X and false अगर MODE13X
 * Original table in OMAP TRM named "UART Mode Baud Rates, Divisor Values,
 * and Error Rates" determines modes not क्रम all common baud rates.
 * E.g. क्रम 1000000 baud rate mode must be 16x, but according to that
 * table it's determined as 13x.
 */
अटल bool
serial_omap_baud_is_mode16(काष्ठा uart_port *port, अचिन्हित पूर्णांक baud)
अणु
	पूर्णांक असल_dअगरf_13 = calculate_baud_असल_dअगरf(port, baud, 13);
	पूर्णांक असल_dअगरf_16 = calculate_baud_असल_dअगरf(port, baud, 16);

	वापस (असल_dअगरf_13 >= असल_dअगरf_16);
पूर्ण

/*
 * serial_omap_get_भागisor - calculate भागisor value
 * @port: uart port info
 * @baud: baudrate क्रम which भागisor needs to be calculated.
 */
अटल अचिन्हित पूर्णांक
serial_omap_get_भागisor(काष्ठा uart_port *port, अचिन्हित पूर्णांक baud)
अणु
	अचिन्हित पूर्णांक mode;

	अगर (!serial_omap_baud_is_mode16(port, baud))
		mode = 13;
	अन्यथा
		mode = 16;
	वापस port->uartclk/(mode * baud);
पूर्ण

अटल व्योम serial_omap_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);

	dev_dbg(up->port.dev, "serial_omap_enable_ms+%d\n", up->port.line);

	pm_runसमय_get_sync(up->dev);
	up->ier |= UART_IER_MSI;
	serial_out(up, UART_IER, up->ier);
	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
पूर्ण

अटल व्योम serial_omap_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);
	पूर्णांक res;

	pm_runसमय_get_sync(up->dev);

	/* Handle RS-485 */
	अगर (port->rs485.flags & SER_RS485_ENABLED) अणु
		अगर (up->scr & OMAP_UART_SCR_TX_EMPTY) अणु
			/* THR पूर्णांकerrupt is fired when both TX FIFO and TX
			 * shअगरt रेजिस्टर are empty. This means there's nothing
			 * left to transmit now, so make sure the THR पूर्णांकerrupt
			 * is fired when TX FIFO is below the trigger level,
			 * disable THR पूर्णांकerrupts and toggle the RS-485 GPIO
			 * data direction pin अगर needed.
			 */
			up->scr &= ~OMAP_UART_SCR_TX_EMPTY;
			serial_out(up, UART_OMAP_SCR, up->scr);
			res = (port->rs485.flags & SER_RS485_RTS_AFTER_SEND) ?
				1 : 0;
			अगर (up->rts_gpiod &&
			    gpiod_get_value(up->rts_gpiod) != res) अणु
				अगर (port->rs485.delay_rts_after_send > 0)
					mdelay(
					port->rs485.delay_rts_after_send);
				gpiod_set_value(up->rts_gpiod, res);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* We're asked to stop, but there's still stuff in the
			 * UART FIFO, so make sure the THR पूर्णांकerrupt is fired
			 * when both TX FIFO and TX shअगरt रेजिस्टर are empty.
			 * The next THR पूर्णांकerrupt (अगर no transmission is started
			 * in the meanसमय) will indicate the end of a
			 * transmission. Thereक्रमe we _करोn't_ disable THR
			 * पूर्णांकerrupts in this situation.
			 */
			up->scr |= OMAP_UART_SCR_TX_EMPTY;
			serial_out(up, UART_OMAP_SCR, up->scr);
			वापस;
		पूर्ण
	पूर्ण

	अगर (up->ier & UART_IER_THRI) अणु
		up->ier &= ~UART_IER_THRI;
		serial_out(up, UART_IER, up->ier);
	पूर्ण

	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
पूर्ण

अटल व्योम serial_omap_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);

	pm_runसमय_get_sync(up->dev);
	up->ier &= ~(UART_IER_RLSI | UART_IER_RDI);
	up->port.पढ़ो_status_mask &= ~UART_LSR_DR;
	serial_out(up, UART_IER, up->ier);
	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
पूर्ण

अटल व्योम transmit_अक्षरs(काष्ठा uart_omap_port *up, अचिन्हित पूर्णांक lsr)
अणु
	काष्ठा circ_buf *xmit = &up->port.state->xmit;
	पूर्णांक count;

	अगर (up->port.x_अक्षर) अणु
		serial_out(up, UART_TX, up->port.x_अक्षर);
		up->port.icount.tx++;
		up->port.x_अक्षर = 0;
		अगर ((up->port.rs485.flags & SER_RS485_ENABLED) &&
		    !(up->port.rs485.flags & SER_RS485_RX_DURING_TX))
			up->rs485_tx_filter_count++;

		वापस;
	पूर्ण
	अगर (uart_circ_empty(xmit) || uart_tx_stopped(&up->port)) अणु
		serial_omap_stop_tx(&up->port);
		वापस;
	पूर्ण
	count = up->port.fअगरosize / 4;
	करो अणु
		serial_out(up, UART_TX, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		up->port.icount.tx++;
		अगर ((up->port.rs485.flags & SER_RS485_ENABLED) &&
		    !(up->port.rs485.flags & SER_RS485_RX_DURING_TX))
			up->rs485_tx_filter_count++;

		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण जबतक (--count > 0);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&up->port);

	अगर (uart_circ_empty(xmit))
		serial_omap_stop_tx(&up->port);
पूर्ण

अटल अंतरभूत व्योम serial_omap_enable_ier_thri(काष्ठा uart_omap_port *up)
अणु
	अगर (!(up->ier & UART_IER_THRI)) अणु
		up->ier |= UART_IER_THRI;
		serial_out(up, UART_IER, up->ier);
	पूर्ण
पूर्ण

अटल व्योम serial_omap_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);
	पूर्णांक res;

	pm_runसमय_get_sync(up->dev);

	/* Handle RS-485 */
	अगर (port->rs485.flags & SER_RS485_ENABLED) अणु
		/* Fire THR पूर्णांकerrupts when FIFO is below trigger level */
		up->scr &= ~OMAP_UART_SCR_TX_EMPTY;
		serial_out(up, UART_OMAP_SCR, up->scr);

		/* अगर rts not alपढ़ोy enabled */
		res = (port->rs485.flags & SER_RS485_RTS_ON_SEND) ? 1 : 0;
		अगर (up->rts_gpiod && gpiod_get_value(up->rts_gpiod) != res) अणु
			gpiod_set_value(up->rts_gpiod, res);
			अगर (port->rs485.delay_rts_beक्रमe_send > 0)
				mdelay(port->rs485.delay_rts_beक्रमe_send);
		पूर्ण
	पूर्ण

	अगर ((port->rs485.flags & SER_RS485_ENABLED) &&
	    !(port->rs485.flags & SER_RS485_RX_DURING_TX))
		up->rs485_tx_filter_count = 0;

	serial_omap_enable_ier_thri(up);
	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
पूर्ण

अटल व्योम serial_omap_throttle(काष्ठा uart_port *port)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);
	अचिन्हित दीर्घ flags;

	pm_runसमय_get_sync(up->dev);
	spin_lock_irqsave(&up->port.lock, flags);
	up->ier &= ~(UART_IER_RLSI | UART_IER_RDI);
	serial_out(up, UART_IER, up->ier);
	spin_unlock_irqrestore(&up->port.lock, flags);
	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
पूर्ण

अटल व्योम serial_omap_unthrottle(काष्ठा uart_port *port)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);
	अचिन्हित दीर्घ flags;

	pm_runसमय_get_sync(up->dev);
	spin_lock_irqsave(&up->port.lock, flags);
	up->ier |= UART_IER_RLSI | UART_IER_RDI;
	serial_out(up, UART_IER, up->ier);
	spin_unlock_irqrestore(&up->port.lock, flags);
	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
पूर्ण

अटल अचिन्हित पूर्णांक check_modem_status(काष्ठा uart_omap_port *up)
अणु
	अचिन्हित पूर्णांक status;

	status = serial_in(up, UART_MSR);
	status |= up->msr_saved_flags;
	up->msr_saved_flags = 0;
	अगर ((status & UART_MSR_ANY_DELTA) == 0)
		वापस status;

	अगर (status & UART_MSR_ANY_DELTA && up->ier & UART_IER_MSI &&
	    up->port.state != शून्य) अणु
		अगर (status & UART_MSR_TERI)
			up->port.icount.rng++;
		अगर (status & UART_MSR_DDSR)
			up->port.icount.dsr++;
		अगर (status & UART_MSR_DDCD)
			uart_handle_dcd_change
				(&up->port, status & UART_MSR_DCD);
		अगर (status & UART_MSR_DCTS)
			uart_handle_cts_change
				(&up->port, status & UART_MSR_CTS);
		wake_up_पूर्णांकerruptible(&up->port.state->port.delta_msr_रुको);
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम serial_omap_rlsi(काष्ठा uart_omap_port *up, अचिन्हित पूर्णांक lsr)
अणु
	अचिन्हित पूर्णांक flag;

	/*
	 * Read one data अक्षरacter out to aव्योम stalling the receiver according
	 * to the table 23-246 of the omap4 TRM.
	 */
	अगर (likely(lsr & UART_LSR_DR)) अणु
		serial_in(up, UART_RX);
		अगर ((up->port.rs485.flags & SER_RS485_ENABLED) &&
		    !(up->port.rs485.flags & SER_RS485_RX_DURING_TX) &&
		    up->rs485_tx_filter_count)
			up->rs485_tx_filter_count--;
	पूर्ण

	up->port.icount.rx++;
	flag = TTY_NORMAL;

	अगर (lsr & UART_LSR_BI) अणु
		flag = TTY_BREAK;
		lsr &= ~(UART_LSR_FE | UART_LSR_PE);
		up->port.icount.brk++;
		/*
		 * We करो the SysRQ and SAK checking
		 * here because otherwise the अवरोध
		 * may get masked by ignore_status_mask
		 * or पढ़ो_status_mask.
		 */
		अगर (uart_handle_अवरोध(&up->port))
			वापस;

	पूर्ण

	अगर (lsr & UART_LSR_PE) अणु
		flag = TTY_PARITY;
		up->port.icount.parity++;
	पूर्ण

	अगर (lsr & UART_LSR_FE) अणु
		flag = TTY_FRAME;
		up->port.icount.frame++;
	पूर्ण

	अगर (lsr & UART_LSR_OE)
		up->port.icount.overrun++;

#अगर_घोषित CONFIG_SERIAL_OMAP_CONSOLE
	अगर (up->port.line == up->port.cons->index) अणु
		/* Recover the अवरोध flag from console xmit */
		lsr |= up->lsr_अवरोध_flag;
	पूर्ण
#पूर्ण_अगर
	uart_insert_अक्षर(&up->port, lsr, UART_LSR_OE, 0, flag);
पूर्ण

अटल व्योम serial_omap_rdi(काष्ठा uart_omap_port *up, अचिन्हित पूर्णांक lsr)
अणु
	अचिन्हित अक्षर ch = 0;
	अचिन्हित पूर्णांक flag;

	अगर (!(lsr & UART_LSR_DR))
		वापस;

	ch = serial_in(up, UART_RX);
	अगर ((up->port.rs485.flags & SER_RS485_ENABLED) &&
	    !(up->port.rs485.flags & SER_RS485_RX_DURING_TX) &&
	    up->rs485_tx_filter_count) अणु
		up->rs485_tx_filter_count--;
		वापस;
	पूर्ण

	flag = TTY_NORMAL;
	up->port.icount.rx++;

	अगर (uart_handle_sysrq_अक्षर(&up->port, ch))
		वापस;

	uart_insert_अक्षर(&up->port, lsr, UART_LSR_OE, ch, flag);
पूर्ण

/**
 * serial_omap_irq() - This handles the पूर्णांकerrupt from one port
 * @irq: uart port irq number
 * @dev_id: uart port info
 */
अटल irqवापस_t serial_omap_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_omap_port *up = dev_id;
	अचिन्हित पूर्णांक iir, lsr;
	अचिन्हित पूर्णांक type;
	irqवापस_t ret = IRQ_NONE;
	पूर्णांक max_count = 256;

	spin_lock(&up->port.lock);
	pm_runसमय_get_sync(up->dev);

	करो अणु
		iir = serial_in(up, UART_IIR);
		अगर (iir & UART_IIR_NO_INT)
			अवरोध;

		ret = IRQ_HANDLED;
		lsr = serial_in(up, UART_LSR);

		/* extract IRQ type from IIR रेजिस्टर */
		type = iir & 0x3e;

		चयन (type) अणु
		हाल UART_IIR_MSI:
			check_modem_status(up);
			अवरोध;
		हाल UART_IIR_THRI:
			transmit_अक्षरs(up, lsr);
			अवरोध;
		हाल UART_IIR_RX_TIMEOUT:
		हाल UART_IIR_RDI:
			serial_omap_rdi(up, lsr);
			अवरोध;
		हाल UART_IIR_RLSI:
			serial_omap_rlsi(up, lsr);
			अवरोध;
		हाल UART_IIR_CTS_RTS_DSR:
			/* simply try again */
			अवरोध;
		हाल UART_IIR_XOFF:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण जबतक (max_count--);

	spin_unlock(&up->port.lock);

	tty_flip_buffer_push(&up->port.state->port);

	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
	up->port_activity = jअगरfies;

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक serial_omap_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित पूर्णांक ret = 0;

	pm_runसमय_get_sync(up->dev);
	dev_dbg(up->port.dev, "serial_omap_tx_empty+%d\n", up->port.line);
	spin_lock_irqsave(&up->port.lock, flags);
	ret = serial_in(up, UART_LSR) & UART_LSR_TEMT ? TIOCSER_TEMT : 0;
	spin_unlock_irqrestore(&up->port.lock, flags);
	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक serial_omap_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक ret = 0;

	pm_runसमय_get_sync(up->dev);
	status = check_modem_status(up);
	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);

	dev_dbg(up->port.dev, "serial_omap_get_mctrl+%d\n", up->port.line);

	अगर (status & UART_MSR_DCD)
		ret |= TIOCM_CAR;
	अगर (status & UART_MSR_RI)
		ret |= TIOCM_RNG;
	अगर (status & UART_MSR_DSR)
		ret |= TIOCM_DSR;
	अगर (status & UART_MSR_CTS)
		ret |= TIOCM_CTS;
	वापस ret;
पूर्ण

अटल व्योम serial_omap_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);
	अचिन्हित अक्षर mcr = 0, old_mcr, lcr;

	dev_dbg(up->port.dev, "serial_omap_set_mctrl+%d\n", up->port.line);
	अगर (mctrl & TIOCM_RTS)
		mcr |= UART_MCR_RTS;
	अगर (mctrl & TIOCM_DTR)
		mcr |= UART_MCR_DTR;
	अगर (mctrl & TIOCM_OUT1)
		mcr |= UART_MCR_OUT1;
	अगर (mctrl & TIOCM_OUT2)
		mcr |= UART_MCR_OUT2;
	अगर (mctrl & TIOCM_LOOP)
		mcr |= UART_MCR_LOOP;

	pm_runसमय_get_sync(up->dev);
	old_mcr = serial_in(up, UART_MCR);
	old_mcr &= ~(UART_MCR_LOOP | UART_MCR_OUT2 | UART_MCR_OUT1 |
		     UART_MCR_DTR | UART_MCR_RTS);
	up->mcr = old_mcr | mcr;
	serial_out(up, UART_MCR, up->mcr);

	/* Turn off स्वतःRTS अगर RTS is lowered; restore स्वतःRTS अगर RTS उठाओd */
	lcr = serial_in(up, UART_LCR);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	अगर ((mctrl & TIOCM_RTS) && (port->status & UPSTAT_AUTORTS))
		up->efr |= UART_EFR_RTS;
	अन्यथा
		up->efr &= ~UART_EFR_RTS;
	serial_out(up, UART_EFR, up->efr);
	serial_out(up, UART_LCR, lcr);

	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
पूर्ण

अटल व्योम serial_omap_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);
	अचिन्हित दीर्घ flags = 0;

	dev_dbg(up->port.dev, "serial_omap_break_ctl+%d\n", up->port.line);
	pm_runसमय_get_sync(up->dev);
	spin_lock_irqsave(&up->port.lock, flags);
	अगर (अवरोध_state == -1)
		up->lcr |= UART_LCR_SBC;
	अन्यथा
		up->lcr &= ~UART_LCR_SBC;
	serial_out(up, UART_LCR, up->lcr);
	spin_unlock_irqrestore(&up->port.lock, flags);
	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
पूर्ण

अटल पूर्णांक serial_omap_startup(काष्ठा uart_port *port)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक retval;

	/*
	 * Allocate the IRQ
	 */
	retval = request_irq(up->port.irq, serial_omap_irq, up->port.irqflags,
				up->name, up);
	अगर (retval)
		वापस retval;

	/* Optional wake-up IRQ */
	अगर (up->wakeirq) अणु
		retval = dev_pm_set_dedicated_wake_irq(up->dev, up->wakeirq);
		अगर (retval) अणु
			मुक्त_irq(up->port.irq, up);
			वापस retval;
		पूर्ण
	पूर्ण

	dev_dbg(up->port.dev, "serial_omap_startup+%d\n", up->port.line);

	pm_runसमय_get_sync(up->dev);
	/*
	 * Clear the FIFO buffers and disable them.
	 * (they will be reenabled in set_termios())
	 */
	serial_omap_clear_fअगरos(up);

	/*
	 * Clear the पूर्णांकerrupt रेजिस्टरs.
	 */
	(व्योम) serial_in(up, UART_LSR);
	अगर (serial_in(up, UART_LSR) & UART_LSR_DR)
		(व्योम) serial_in(up, UART_RX);
	(व्योम) serial_in(up, UART_IIR);
	(व्योम) serial_in(up, UART_MSR);

	/*
	 * Now, initialize the UART
	 */
	serial_out(up, UART_LCR, UART_LCR_WLEN8);
	spin_lock_irqsave(&up->port.lock, flags);
	/*
	 * Most PC uarts need OUT2 उठाओd to enable पूर्णांकerrupts.
	 */
	up->port.mctrl |= TIOCM_OUT2;
	serial_omap_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);

	up->msr_saved_flags = 0;
	/*
	 * Finally, enable पूर्णांकerrupts. Note: Modem status पूर्णांकerrupts
	 * are set via set_termios(), which will be occurring imminently
	 * anyway, so we करोn't enable them here.
	 */
	up->ier = UART_IER_RLSI | UART_IER_RDI;
	serial_out(up, UART_IER, up->ier);

	/* Enable module level wake up */
	up->wer = OMAP_UART_WER_MOD_WKUP;
	अगर (up->features & OMAP_UART_WER_HAS_TX_WAKEUP)
		up->wer |= OMAP_UART_TX_WAKEUP_EN;

	serial_out(up, UART_OMAP_WER, up->wer);

	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
	up->port_activity = jअगरfies;
	वापस 0;
पूर्ण

अटल व्योम serial_omap_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);
	अचिन्हित दीर्घ flags = 0;

	dev_dbg(up->port.dev, "serial_omap_shutdown+%d\n", up->port.line);

	pm_runसमय_get_sync(up->dev);
	/*
	 * Disable पूर्णांकerrupts from this port
	 */
	up->ier = 0;
	serial_out(up, UART_IER, 0);

	spin_lock_irqsave(&up->port.lock, flags);
	up->port.mctrl &= ~TIOCM_OUT2;
	serial_omap_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);

	/*
	 * Disable अवरोध condition and FIFOs
	 */
	serial_out(up, UART_LCR, serial_in(up, UART_LCR) & ~UART_LCR_SBC);
	serial_omap_clear_fअगरos(up);

	/*
	 * Read data port to reset things, and then मुक्त the irq
	 */
	अगर (serial_in(up, UART_LSR) & UART_LSR_DR)
		(व्योम) serial_in(up, UART_RX);

	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
	मुक्त_irq(up->port.irq, up);
	dev_pm_clear_wake_irq(up->dev);
पूर्ण

अटल व्योम serial_omap_uart_qos_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा uart_omap_port *up = container_of(work, काष्ठा uart_omap_port,
						qos_work);

	cpu_latency_qos_update_request(&up->pm_qos_request, up->latency);
पूर्ण

अटल व्योम
serial_omap_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
			काष्ठा ktermios *old)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);
	अचिन्हित अक्षर cval = 0;
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित पूर्णांक baud, quot;

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

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk/13);
	quot = serial_omap_get_भागisor(port, baud);

	/* calculate wakeup latency स्थिरraपूर्णांक */
	up->calc_latency = (USEC_PER_SEC * up->port.fअगरosize) / (baud / 8);
	up->latency = up->calc_latency;
	schedule_work(&up->qos_work);

	up->dll = quot & 0xff;
	up->dlh = quot >> 8;
	up->mdr1 = UART_OMAP_MDR1_DISABLE;

	up->fcr = UART_FCR_R_TRIG_01 | UART_FCR_T_TRIG_01 |
			UART_FCR_ENABLE_FIFO;

	/*
	 * Ok, we're now changing the port state. Do it with
	 * पूर्णांकerrupts disabled.
	 */
	pm_runसमय_get_sync(up->dev);
	spin_lock_irqsave(&up->port.lock, flags);

	/*
	 * Update the per-port समयout.
	 */
	uart_update_समयout(port, termios->c_cflag, baud);

	up->port.पढ़ो_status_mask = UART_LSR_OE | UART_LSR_THRE | UART_LSR_DR;
	अगर (termios->c_अगरlag & INPCK)
		up->port.पढ़ो_status_mask |= UART_LSR_FE | UART_LSR_PE;
	अगर (termios->c_अगरlag & (BRKINT | PARMRK))
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
	serial_out(up, UART_IER, up->ier);
	serial_out(up, UART_LCR, cval);		/* reset DLAB */
	up->lcr = cval;
	up->scr = 0;

	/* FIFOs and DMA Settings */

	/* FCR can be changed only when the
	 * baud घड़ी is not running
	 * DLL_REG and DLH_REG set to 0.
	 */
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	serial_out(up, UART_DLL, 0);
	serial_out(up, UART_DLM, 0);
	serial_out(up, UART_LCR, 0);

	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);

	up->efr = serial_in(up, UART_EFR) & ~UART_EFR_ECB;
	up->efr &= ~UART_EFR_SCD;
	serial_out(up, UART_EFR, up->efr | UART_EFR_ECB);

	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	up->mcr = serial_in(up, UART_MCR) & ~UART_MCR_TCRTLR;
	serial_out(up, UART_MCR, up->mcr | UART_MCR_TCRTLR);
	/* FIFO ENABLE, DMA MODE */

	up->scr |= OMAP_UART_SCR_RX_TRIG_GRANU1_MASK;
	/*
	 * NOTE: Setting OMAP_UART_SCR_RX_TRIG_GRANU1_MASK
	 * sets Enables the granularity of 1 क्रम TRIGGER RX
	 * level. Aदीर्घ with setting RX FIFO trigger level
	 * to 1 (as noted below, 16 अक्षरacters) and TLR[3:0]
	 * to zero this will result RX FIFO threshold level
	 * to 1 अक्षरacter, instead of 16 as noted in comment
	 * below.
	 */

	/* Set receive FIFO threshold to 16 अक्षरacters and
	 * transmit FIFO threshold to 32 spaces
	 */
	up->fcr &= ~OMAP_UART_FCR_RX_FIFO_TRIG_MASK;
	up->fcr &= ~OMAP_UART_FCR_TX_FIFO_TRIG_MASK;
	up->fcr |= UART_FCR6_R_TRIGGER_16 | UART_FCR6_T_TRIGGER_24 |
		UART_FCR_ENABLE_FIFO;

	serial_out(up, UART_FCR, up->fcr);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);

	serial_out(up, UART_OMAP_SCR, up->scr);

	/* Reset UART_MCR_TCRTLR: this must be करोne with the EFR_ECB bit set */
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	serial_out(up, UART_MCR, up->mcr);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	serial_out(up, UART_EFR, up->efr);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);

	/* Protocol, Baud Rate, and Interrupt Settings */

	अगर (up->errata & UART_ERRATA_i202_MDR1_ACCESS)
		serial_omap_mdr1_errataset(up, up->mdr1);
	अन्यथा
		serial_out(up, UART_OMAP_MDR1, up->mdr1);

	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	serial_out(up, UART_EFR, up->efr | UART_EFR_ECB);

	serial_out(up, UART_LCR, 0);
	serial_out(up, UART_IER, 0);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);

	serial_out(up, UART_DLL, up->dll);	/* LS of भागisor */
	serial_out(up, UART_DLM, up->dlh);	/* MS of भागisor */

	serial_out(up, UART_LCR, 0);
	serial_out(up, UART_IER, up->ier);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);

	serial_out(up, UART_EFR, up->efr);
	serial_out(up, UART_LCR, cval);

	अगर (!serial_omap_baud_is_mode16(port, baud))
		up->mdr1 = UART_OMAP_MDR1_13X_MODE;
	अन्यथा
		up->mdr1 = UART_OMAP_MDR1_16X_MODE;

	अगर (up->errata & UART_ERRATA_i202_MDR1_ACCESS)
		serial_omap_mdr1_errataset(up, up->mdr1);
	अन्यथा
		serial_out(up, UART_OMAP_MDR1, up->mdr1);

	/* Configure flow control */
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);

	/* XON1/XOFF1 accessible mode B, TCRTLR=0, ECB=0 */
	serial_out(up, UART_XON1, termios->c_cc[VSTART]);
	serial_out(up, UART_XOFF1, termios->c_cc[VSTOP]);

	/* Enable access to TCR/TLR */
	serial_out(up, UART_EFR, up->efr | UART_EFR_ECB);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	serial_out(up, UART_MCR, up->mcr | UART_MCR_TCRTLR);

	serial_out(up, UART_TI752_TCR, OMAP_UART_TCR_TRIG);

	up->port.status &= ~(UPSTAT_AUTOCTS | UPSTAT_AUTORTS | UPSTAT_AUTOXOFF);

	अगर (termios->c_cflag & CRTSCTS && up->port.flags & UPF_HARD_FLOW) अणु
		/* Enable AUTOCTS (स्वतःRTS is enabled when RTS is उठाओd) */
		up->port.status |= UPSTAT_AUTOCTS | UPSTAT_AUTORTS;
		up->efr |= UART_EFR_CTS;
	पूर्ण अन्यथा अणु
		/* Disable AUTORTS and AUTOCTS */
		up->efr &= ~(UART_EFR_CTS | UART_EFR_RTS);
	पूर्ण

	अगर (up->port.flags & UPF_SOFT_FLOW) अणु
		/* clear SW control mode bits */
		up->efr &= OMAP_UART_SW_CLR;

		/*
		 * IXON Flag:
		 * Enable XON/XOFF flow control on input.
		 * Receiver compares XON1, XOFF1.
		 */
		अगर (termios->c_अगरlag & IXON)
			up->efr |= OMAP_UART_SW_RX;

		/*
		 * IXOFF Flag:
		 * Enable XON/XOFF flow control on output.
		 * Transmit XON1, XOFF1
		 */
		अगर (termios->c_अगरlag & IXOFF) अणु
			up->port.status |= UPSTAT_AUTOXOFF;
			up->efr |= OMAP_UART_SW_TX;
		पूर्ण

		/*
		 * IXANY Flag:
		 * Enable any अक्षरacter to restart output.
		 * Operation resumes after receiving any
		 * अक्षरacter after recognition of the XOFF अक्षरacter
		 */
		अगर (termios->c_अगरlag & IXANY)
			up->mcr |= UART_MCR_XOन_अंकY;
		अन्यथा
			up->mcr &= ~UART_MCR_XOन_अंकY;
	पूर्ण
	serial_out(up, UART_MCR, up->mcr);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	serial_out(up, UART_EFR, up->efr);
	serial_out(up, UART_LCR, up->lcr);

	serial_omap_set_mctrl(&up->port, up->port.mctrl);

	spin_unlock_irqrestore(&up->port.lock, flags);
	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
	dev_dbg(up->port.dev, "serial_omap_set_termios+%d\n", up->port.line);
पूर्ण

अटल व्योम
serial_omap_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
	       अचिन्हित पूर्णांक oldstate)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);
	अचिन्हित अक्षर efr;

	dev_dbg(up->port.dev, "serial_omap_pm+%d\n", up->port.line);

	pm_runसमय_get_sync(up->dev);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	efr = serial_in(up, UART_EFR);
	serial_out(up, UART_EFR, efr | UART_EFR_ECB);
	serial_out(up, UART_LCR, 0);

	serial_out(up, UART_IER, (state != 0) ? UART_IERX_SLEEP : 0);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	serial_out(up, UART_EFR, efr);
	serial_out(up, UART_LCR, 0);

	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
पूर्ण

अटल व्योम serial_omap_release_port(काष्ठा uart_port *port)
अणु
	dev_dbg(port->dev, "serial_omap_release_port+\n");
पूर्ण

अटल पूर्णांक serial_omap_request_port(काष्ठा uart_port *port)
अणु
	dev_dbg(port->dev, "serial_omap_request_port+\n");
	वापस 0;
पूर्ण

अटल व्योम serial_omap_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);

	dev_dbg(up->port.dev, "serial_omap_config_port+%d\n",
							up->port.line);
	up->port.type = PORT_OMAP;
	up->port.flags |= UPF_SOFT_FLOW | UPF_HARD_FLOW;
पूर्ण

अटल पूर्णांक
serial_omap_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	/* we करोn't want the core code to modअगरy any port params */
	dev_dbg(port->dev, "serial_omap_verify_port+\n");
	वापस -EINVAL;
पूर्ण

अटल स्थिर अक्षर *
serial_omap_type(काष्ठा uart_port *port)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);

	dev_dbg(up->port.dev, "serial_omap_type+%d\n", up->port.line);
	वापस up->name;
पूर्ण

#घोषणा BOTH_EMPTY (UART_LSR_TEMT | UART_LSR_THRE)

अटल व्योम __maybe_unused रुको_क्रम_xmitr(काष्ठा uart_omap_port *up)
अणु
	अचिन्हित पूर्णांक status, पंचांगout = 10000;

	/* Wait up to 10ms क्रम the अक्षरacter(s) to be sent. */
	करो अणु
		status = serial_in(up, UART_LSR);

		अगर (status & UART_LSR_BI)
			up->lsr_अवरोध_flag = UART_LSR_BI;

		अगर (--पंचांगout == 0)
			अवरोध;
		udelay(1);
	पूर्ण जबतक ((status & BOTH_EMPTY) != BOTH_EMPTY);

	/* Wait up to 1s क्रम flow control अगर necessary */
	अगर (up->port.flags & UPF_CONS_FLOW) अणु
		पंचांगout = 1000000;
		क्रम (पंचांगout = 1000000; पंचांगout; पंचांगout--) अणु
			अचिन्हित पूर्णांक msr = serial_in(up, UART_MSR);

			up->msr_saved_flags |= msr & MSR_SAVE_FLAGS;
			अगर (msr & UART_MSR_CTS)
				अवरोध;

			udelay(1);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL

अटल व्योम serial_omap_poll_put_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर ch)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);

	pm_runसमय_get_sync(up->dev);
	रुको_क्रम_xmitr(up);
	serial_out(up, UART_TX, ch);
	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
पूर्ण

अटल पूर्णांक serial_omap_poll_get_अक्षर(काष्ठा uart_port *port)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);
	अचिन्हित पूर्णांक status;

	pm_runसमय_get_sync(up->dev);
	status = serial_in(up, UART_LSR);
	अगर (!(status & UART_LSR_DR)) अणु
		status = NO_POLL_CHAR;
		जाओ out;
	पूर्ण

	status = serial_in(up, UART_RX);

out:
	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);

	वापस status;
पूर्ण

#पूर्ण_अगर /* CONFIG_CONSOLE_POLL */

#अगर_घोषित CONFIG_SERIAL_OMAP_CONSOLE

#अगर_घोषित CONFIG_SERIAL_EARLYCON
अटल अचिन्हित पूर्णांक omap_serial_early_in(काष्ठा uart_port *port, पूर्णांक offset)
अणु
	offset <<= port->regshअगरt;
	वापस पढ़ोw(port->membase + offset);
पूर्ण

अटल व्योम omap_serial_early_out(काष्ठा uart_port *port, पूर्णांक offset,
				  पूर्णांक value)
अणु
	offset <<= port->regshअगरt;
	ग_लिखोw(value, port->membase + offset);
पूर्ण

अटल व्योम omap_serial_early_अ_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	अचिन्हित पूर्णांक status;

	क्रम (;;) अणु
		status = omap_serial_early_in(port, UART_LSR);
		अगर ((status & BOTH_EMPTY) == BOTH_EMPTY)
			अवरोध;
		cpu_relax();
	पूर्ण
	omap_serial_early_out(port, UART_TX, c);
पूर्ण

अटल व्योम early_omap_serial_ग_लिखो(काष्ठा console *console, स्थिर अक्षर *s,
				    अचिन्हित पूर्णांक count)
अणु
	काष्ठा earlycon_device *device = console->data;
	काष्ठा uart_port *port = &device->port;

	uart_console_ग_लिखो(port, s, count, omap_serial_early_अ_दो);
पूर्ण

अटल पूर्णांक __init early_omap_serial_setup(काष्ठा earlycon_device *device,
					  स्थिर अक्षर *options)
अणु
	काष्ठा uart_port *port = &device->port;

	अगर (!(device->port.membase || device->port.iobase))
		वापस -ENODEV;

	port->regshअगरt = 2;
	device->con->ग_लिखो = early_omap_serial_ग_लिखो;
	वापस 0;
पूर्ण

OF_EARLYCON_DECLARE(omapserial, "ti,omap2-uart", early_omap_serial_setup);
OF_EARLYCON_DECLARE(omapserial, "ti,omap3-uart", early_omap_serial_setup);
OF_EARLYCON_DECLARE(omapserial, "ti,omap4-uart", early_omap_serial_setup);
#पूर्ण_अगर /* CONFIG_SERIAL_EARLYCON */

अटल काष्ठा uart_omap_port *serial_omap_console_ports[OMAP_MAX_HSUART_PORTS];

अटल काष्ठा uart_driver serial_omap_reg;

अटल व्योम serial_omap_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);

	रुको_क्रम_xmitr(up);
	serial_out(up, UART_TX, ch);
पूर्ण

अटल व्योम
serial_omap_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
		अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_omap_port *up = serial_omap_console_ports[co->index];
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ier;
	पूर्णांक locked = 1;

	pm_runसमय_get_sync(up->dev);

	local_irq_save(flags);
	अगर (up->port.sysrq)
		locked = 0;
	अन्यथा अगर (oops_in_progress)
		locked = spin_trylock(&up->port.lock);
	अन्यथा
		spin_lock(&up->port.lock);

	/*
	 * First save the IER then disable the पूर्णांकerrupts
	 */
	ier = serial_in(up, UART_IER);
	serial_out(up, UART_IER, 0);

	uart_console_ग_लिखो(&up->port, s, count, serial_omap_console_अक्षर_दो);

	/*
	 * Finally, रुको क्रम transmitter to become empty
	 * and restore the IER
	 */
	रुको_क्रम_xmitr(up);
	serial_out(up, UART_IER, ier);
	/*
	 * The receive handling will happen properly because the
	 * receive पढ़ोy bit will still be set; it is not cleared
	 * on पढ़ो.  However, modem control will not, we must
	 * call it अगर we have saved something in the saved flags
	 * जबतक processing with पूर्णांकerrupts off.
	 */
	अगर (up->msr_saved_flags)
		check_modem_status(up);

	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
	अगर (locked)
		spin_unlock(&up->port.lock);
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक __init
serial_omap_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_omap_port *up;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (serial_omap_console_ports[co->index] == शून्य)
		वापस -ENODEV;
	up = serial_omap_console_ports[co->index];

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(&up->port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा console serial_omap_console = अणु
	.name		= OMAP_SERIAL_NAME,
	.ग_लिखो		= serial_omap_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= serial_omap_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &serial_omap_reg,
पूर्ण;

अटल व्योम serial_omap_add_console_port(काष्ठा uart_omap_port *up)
अणु
	serial_omap_console_ports[up->port.line] = up;
पूर्ण

#घोषणा OMAP_CONSOLE	(&serial_omap_console)

#अन्यथा

#घोषणा OMAP_CONSOLE	शून्य

अटल अंतरभूत व्योम serial_omap_add_console_port(काष्ठा uart_omap_port *up)
अणुपूर्ण

#पूर्ण_अगर

/* Enable or disable the rs485 support */
अटल पूर्णांक
serial_omap_config_rs485(काष्ठा uart_port *port, काष्ठा serial_rs485 *rs485)
अणु
	काष्ठा uart_omap_port *up = to_uart_omap_port(port);
	अचिन्हित पूर्णांक mode;
	पूर्णांक val;

	pm_runसमय_get_sync(up->dev);

	/* Disable पूर्णांकerrupts from this port */
	mode = up->ier;
	up->ier = 0;
	serial_out(up, UART_IER, 0);

	/* Clamp the delays to [0, 100ms] */
	rs485->delay_rts_beक्रमe_send = min(rs485->delay_rts_beक्रमe_send, 100U);
	rs485->delay_rts_after_send  = min(rs485->delay_rts_after_send, 100U);

	/* store new config */
	port->rs485 = *rs485;

	अगर (up->rts_gpiod) अणु
		/* enable / disable rts */
		val = (port->rs485.flags & SER_RS485_ENABLED) ?
			SER_RS485_RTS_AFTER_SEND : SER_RS485_RTS_ON_SEND;
		val = (port->rs485.flags & val) ? 1 : 0;
		gpiod_set_value(up->rts_gpiod, val);
	पूर्ण

	/* Enable पूर्णांकerrupts */
	up->ier = mode;
	serial_out(up, UART_IER, up->ier);

	/* If RS-485 is disabled, make sure the THR पूर्णांकerrupt is fired when
	 * TX FIFO is below the trigger level.
	 */
	अगर (!(port->rs485.flags & SER_RS485_ENABLED) &&
	    (up->scr & OMAP_UART_SCR_TX_EMPTY)) अणु
		up->scr &= ~OMAP_UART_SCR_TX_EMPTY;
		serial_out(up, UART_OMAP_SCR, up->scr);
	पूर्ण

	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uart_ops serial_omap_pops = अणु
	.tx_empty	= serial_omap_tx_empty,
	.set_mctrl	= serial_omap_set_mctrl,
	.get_mctrl	= serial_omap_get_mctrl,
	.stop_tx	= serial_omap_stop_tx,
	.start_tx	= serial_omap_start_tx,
	.throttle	= serial_omap_throttle,
	.unthrottle	= serial_omap_unthrottle,
	.stop_rx	= serial_omap_stop_rx,
	.enable_ms	= serial_omap_enable_ms,
	.अवरोध_ctl	= serial_omap_अवरोध_ctl,
	.startup	= serial_omap_startup,
	.shutकरोwn	= serial_omap_shutकरोwn,
	.set_termios	= serial_omap_set_termios,
	.pm		= serial_omap_pm,
	.type		= serial_omap_type,
	.release_port	= serial_omap_release_port,
	.request_port	= serial_omap_request_port,
	.config_port	= serial_omap_config_port,
	.verअगरy_port	= serial_omap_verअगरy_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_put_अक्षर  = serial_omap_poll_put_अक्षर,
	.poll_get_अक्षर  = serial_omap_poll_get_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा uart_driver serial_omap_reg = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "OMAP-SERIAL",
	.dev_name	= OMAP_SERIAL_NAME,
	.nr		= OMAP_MAX_HSUART_PORTS,
	.cons		= OMAP_CONSOLE,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक serial_omap_prepare(काष्ठा device *dev)
अणु
	काष्ठा uart_omap_port *up = dev_get_drvdata(dev);

	up->is_suspending = true;

	वापस 0;
पूर्ण

अटल व्योम serial_omap_complete(काष्ठा device *dev)
अणु
	काष्ठा uart_omap_port *up = dev_get_drvdata(dev);

	up->is_suspending = false;
पूर्ण

अटल पूर्णांक serial_omap_suspend(काष्ठा device *dev)
अणु
	काष्ठा uart_omap_port *up = dev_get_drvdata(dev);

	uart_suspend_port(&serial_omap_reg, &up->port);
	flush_work(&up->qos_work);

	अगर (device_may_wakeup(dev))
		serial_omap_enable_wakeup(up, true);
	अन्यथा
		serial_omap_enable_wakeup(up, false);

	वापस 0;
पूर्ण

अटल पूर्णांक serial_omap_resume(काष्ठा device *dev)
अणु
	काष्ठा uart_omap_port *up = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		serial_omap_enable_wakeup(up, false);

	uart_resume_port(&serial_omap_reg, &up->port);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा serial_omap_prepare शून्य
#घोषणा serial_omap_complete शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल व्योम omap_serial_fill_features_erratas(काष्ठा uart_omap_port *up)
अणु
	u32 mvr, scheme;
	u16 revision, major, minor;

	mvr = पढ़ोl(up->port.membase + (UART_OMAP_MVER << up->port.regshअगरt));

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
		dev_warn(up->dev,
			"Unknown %s revision, defaulting to highest\n",
			up->name);
		/* highest possible revision */
		major = 0xff;
		minor = 0xff;
	पूर्ण

	/* normalize revision क्रम the driver */
	revision = UART_BUILD_REVISION(major, minor);

	चयन (revision) अणु
	हाल OMAP_UART_REV_46:
		up->errata |= (UART_ERRATA_i202_MDR1_ACCESS |
				UART_ERRATA_i291_DMA_FORCEIDLE);
		अवरोध;
	हाल OMAP_UART_REV_52:
		up->errata |= (UART_ERRATA_i202_MDR1_ACCESS |
				UART_ERRATA_i291_DMA_FORCEIDLE);
		up->features |= OMAP_UART_WER_HAS_TX_WAKEUP;
		अवरोध;
	हाल OMAP_UART_REV_63:
		up->errata |= UART_ERRATA_i202_MDR1_ACCESS;
		up->features |= OMAP_UART_WER_HAS_TX_WAKEUP;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा omap_uart_port_info *of_get_uart_port_info(काष्ठा device *dev)
अणु
	काष्ठा omap_uart_port_info *omap_up_info;

	omap_up_info = devm_kzalloc(dev, माप(*omap_up_info), GFP_KERNEL);
	अगर (!omap_up_info)
		वापस शून्य; /* out of memory */

	of_property_पढ़ो_u32(dev->of_node, "clock-frequency",
					 &omap_up_info->uartclk);

	omap_up_info->flags = UPF_BOOT_AUTOCONF;

	वापस omap_up_info;
पूर्ण

अटल पूर्णांक serial_omap_probe_rs485(काष्ठा uart_omap_port *up,
				   काष्ठा device *dev)
अणु
	काष्ठा serial_rs485 *rs485conf = &up->port.rs485;
	काष्ठा device_node *np = dev->of_node;
	क्रमागत gpiod_flags gflags;
	पूर्णांक ret;

	rs485conf->flags = 0;
	up->rts_gpiod = शून्य;

	अगर (!np)
		वापस 0;

	ret = uart_get_rs485_mode(&up->port);
	अगर (ret)
		वापस ret;

	अगर (of_property_पढ़ो_bool(np, "rs485-rts-active-high")) अणु
		rs485conf->flags |= SER_RS485_RTS_ON_SEND;
		rs485conf->flags &= ~SER_RS485_RTS_AFTER_SEND;
	पूर्ण अन्यथा अणु
		rs485conf->flags &= ~SER_RS485_RTS_ON_SEND;
		rs485conf->flags |= SER_RS485_RTS_AFTER_SEND;
	पूर्ण

	/* check क्रम tx enable gpio */
	gflags = rs485conf->flags & SER_RS485_RTS_AFTER_SEND ?
		GPIOD_OUT_HIGH : GPIOD_OUT_LOW;
	up->rts_gpiod = devm_gpiod_get_optional(dev, "rts", gflags);
	अगर (IS_ERR(up->rts_gpiod)) अणु
		ret = PTR_ERR(up->rts_gpiod);
	        अगर (ret == -EPROBE_DEFER)
			वापस ret;
		/*
		 * FIXME: the code historically ignored any other error than
		 * -EPROBE_DEFER and just went on without GPIO.
		 */
		up->rts_gpiod = शून्य;
	पूर्ण अन्यथा अणु
		gpiod_set_consumer_name(up->rts_gpiod, "omap-serial");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक serial_omap_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_uart_port_info *omap_up_info = dev_get_platdata(&pdev->dev);
	काष्ठा uart_omap_port *up;
	काष्ठा resource *mem;
	व्योम __iomem *base;
	पूर्णांक uartirq = 0;
	पूर्णांक wakeirq = 0;
	पूर्णांक ret;

	/* The optional wakeirq may be specअगरied in the board dts file */
	अगर (pdev->dev.of_node) अणु
		uartirq = irq_of_parse_and_map(pdev->dev.of_node, 0);
		अगर (!uartirq)
			वापस -EPROBE_DEFER;
		wakeirq = irq_of_parse_and_map(pdev->dev.of_node, 1);
		omap_up_info = of_get_uart_port_info(&pdev->dev);
		pdev->dev.platक्रमm_data = omap_up_info;
	पूर्ण अन्यथा अणु
		uartirq = platक्रमm_get_irq(pdev, 0);
		अगर (uartirq < 0)
			वापस -EPROBE_DEFER;
	पूर्ण

	up = devm_kzalloc(&pdev->dev, माप(*up), GFP_KERNEL);
	अगर (!up)
		वापस -ENOMEM;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	up->dev = &pdev->dev;
	up->port.dev = &pdev->dev;
	up->port.type = PORT_OMAP;
	up->port.iotype = UPIO_MEM;
	up->port.irq = uartirq;
	up->port.regshअगरt = 2;
	up->port.fअगरosize = 64;
	up->port.ops = &serial_omap_pops;
	up->port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_OMAP_CONSOLE);

	अगर (pdev->dev.of_node)
		ret = of_alias_get_id(pdev->dev.of_node, "serial");
	अन्यथा
		ret = pdev->id;

	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to get alias/pdev id, errno %d\n",
			ret);
		जाओ err_port_line;
	पूर्ण
	up->port.line = ret;

	अगर (up->port.line >= OMAP_MAX_HSUART_PORTS) अणु
		dev_err(&pdev->dev, "uart ID %d >  MAX %d.\n", up->port.line,
			OMAP_MAX_HSUART_PORTS);
		ret = -ENXIO;
		जाओ err_port_line;
	पूर्ण

	up->wakeirq = wakeirq;
	अगर (!up->wakeirq)
		dev_info(up->port.dev, "no wakeirq for uart%d\n",
			 up->port.line);

	ret = serial_omap_probe_rs485(up, &pdev->dev);
	अगर (ret < 0)
		जाओ err_rs485;

	प्र_लिखो(up->name, "OMAP UART%d", up->port.line);
	up->port.mapbase = mem->start;
	up->port.membase = base;
	up->port.flags = omap_up_info->flags;
	up->port.uartclk = omap_up_info->uartclk;
	up->port.rs485_config = serial_omap_config_rs485;
	अगर (!up->port.uartclk) अणु
		up->port.uartclk = DEFAULT_CLK_SPEED;
		dev_warn(&pdev->dev,
			 "No clock speed specified: using default: %d\n",
			 DEFAULT_CLK_SPEED);
	पूर्ण

	up->latency = PM_QOS_CPU_LATENCY_DEFAULT_VALUE;
	up->calc_latency = PM_QOS_CPU_LATENCY_DEFAULT_VALUE;
	cpu_latency_qos_add_request(&up->pm_qos_request, up->latency);
	INIT_WORK(&up->qos_work, serial_omap_uart_qos_work);

	platक्रमm_set_drvdata(pdev, up);
	अगर (omap_up_info->स्वतःsuspend_समयout == 0)
		omap_up_info->स्वतःsuspend_समयout = -1;

	device_init_wakeup(up->dev, true);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev,
			omap_up_info->स्वतःsuspend_समयout);

	pm_runसमय_irq_safe(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	pm_runसमय_get_sync(&pdev->dev);

	omap_serial_fill_features_erratas(up);

	ui[up->port.line] = up;
	serial_omap_add_console_port(up);

	ret = uart_add_one_port(&serial_omap_reg, &up->port);
	अगर (ret != 0)
		जाओ err_add_port;

	pm_runसमय_mark_last_busy(up->dev);
	pm_runसमय_put_स्वतःsuspend(up->dev);
	वापस 0;

err_add_port:
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	cpu_latency_qos_हटाओ_request(&up->pm_qos_request);
	device_init_wakeup(up->dev, false);
err_rs485:
err_port_line:
	वापस ret;
पूर्ण

अटल पूर्णांक serial_omap_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा uart_omap_port *up = platक्रमm_get_drvdata(dev);

	pm_runसमय_get_sync(up->dev);

	uart_हटाओ_one_port(&serial_omap_reg, &up->port);

	pm_runसमय_करोnt_use_स्वतःsuspend(up->dev);
	pm_runसमय_put_sync(up->dev);
	pm_runसमय_disable(up->dev);
	cpu_latency_qos_हटाओ_request(&up->pm_qos_request);
	device_init_wakeup(&dev->dev, false);

	वापस 0;
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
अटल व्योम serial_omap_mdr1_errataset(काष्ठा uart_omap_port *up, u8 mdr1)
अणु
	u8 समयout = 255;

	serial_out(up, UART_OMAP_MDR1, mdr1);
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
			dev_crit(up->dev, "Errata i202: timedout %x\n",
						serial_in(up, UART_LSR));
			अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम serial_omap_restore_context(काष्ठा uart_omap_port *up)
अणु
	अगर (up->errata & UART_ERRATA_i202_MDR1_ACCESS)
		serial_omap_mdr1_errataset(up, UART_OMAP_MDR1_DISABLE);
	अन्यथा
		serial_out(up, UART_OMAP_MDR1, UART_OMAP_MDR1_DISABLE);

	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B); /* Config B mode */
	serial_out(up, UART_EFR, UART_EFR_ECB);
	serial_out(up, UART_LCR, 0x0); /* Operational mode */
	serial_out(up, UART_IER, 0x0);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B); /* Config B mode */
	serial_out(up, UART_DLL, up->dll);
	serial_out(up, UART_DLM, up->dlh);
	serial_out(up, UART_LCR, 0x0); /* Operational mode */
	serial_out(up, UART_IER, up->ier);
	serial_out(up, UART_FCR, up->fcr);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	serial_out(up, UART_MCR, up->mcr);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B); /* Config B mode */
	serial_out(up, UART_OMAP_SCR, up->scr);
	serial_out(up, UART_EFR, up->efr);
	serial_out(up, UART_LCR, up->lcr);
	अगर (up->errata & UART_ERRATA_i202_MDR1_ACCESS)
		serial_omap_mdr1_errataset(up, up->mdr1);
	अन्यथा
		serial_out(up, UART_OMAP_MDR1, up->mdr1);
	serial_out(up, UART_OMAP_WER, up->wer);
पूर्ण

अटल पूर्णांक serial_omap_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा uart_omap_port *up = dev_get_drvdata(dev);

	अगर (!up)
		वापस -EINVAL;

	/*
	* When using 'no_console_suspend', the console UART must not be
	* suspended. Since driver suspend is managed by runसमय suspend,
	* preventing runसमय suspend (by वापसing error) will keep device
	* active during suspend.
	*/
	अगर (up->is_suspending && !console_suspend_enabled &&
	    uart_console(&up->port))
		वापस -EBUSY;

	up->context_loss_cnt = serial_omap_get_context_loss_count(up);

	serial_omap_enable_wakeup(up, true);

	up->latency = PM_QOS_CPU_LATENCY_DEFAULT_VALUE;
	schedule_work(&up->qos_work);

	वापस 0;
पूर्ण

अटल पूर्णांक serial_omap_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा uart_omap_port *up = dev_get_drvdata(dev);

	पूर्णांक loss_cnt = serial_omap_get_context_loss_count(up);

	serial_omap_enable_wakeup(up, false);

	अगर (loss_cnt < 0) अणु
		dev_dbg(dev, "serial_omap_get_context_loss_count failed : %d\n",
			loss_cnt);
		serial_omap_restore_context(up);
	पूर्ण अन्यथा अगर (up->context_loss_cnt != loss_cnt) अणु
		serial_omap_restore_context(up);
	पूर्ण
	up->latency = up->calc_latency;
	schedule_work(&up->qos_work);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops serial_omap_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(serial_omap_suspend, serial_omap_resume)
	SET_RUNTIME_PM_OPS(serial_omap_runसमय_suspend,
				serial_omap_runसमय_resume, शून्य)
	.prepare        = serial_omap_prepare,
	.complete       = serial_omap_complete,
पूर्ण;

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id omap_serial_of_match[] = अणु
	अणु .compatible = "ti,omap2-uart" पूर्ण,
	अणु .compatible = "ti,omap3-uart" पूर्ण,
	अणु .compatible = "ti,omap4-uart" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_serial_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver serial_omap_driver = अणु
	.probe          = serial_omap_probe,
	.हटाओ         = serial_omap_हटाओ,
	.driver		= अणु
		.name	= OMAP_SERIAL_DRIVER_NAME,
		.pm	= &serial_omap_dev_pm_ops,
		.of_match_table = of_match_ptr(omap_serial_of_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init serial_omap_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&serial_omap_reg);
	अगर (ret != 0)
		वापस ret;
	ret = platक्रमm_driver_रेजिस्टर(&serial_omap_driver);
	अगर (ret != 0)
		uart_unरेजिस्टर_driver(&serial_omap_reg);
	वापस ret;
पूर्ण

अटल व्योम __निकास serial_omap_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&serial_omap_driver);
	uart_unरेजिस्टर_driver(&serial_omap_reg);
पूर्ण

module_init(serial_omap_init);
module_निकास(serial_omap_निकास);

MODULE_DESCRIPTION("OMAP High Speed UART driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Texas Instruments Inc");
