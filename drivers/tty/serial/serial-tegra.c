<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * serial_tegra.c
 *
 * High-speed serial driver क्रम NVIDIA Tegra SoCs
 *
 * Copyright (c) 2012-2019, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/termios.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

#घोषणा TEGRA_UART_TYPE				"TEGRA_UART"
#घोषणा TX_EMPTY_STATUS				(UART_LSR_TEMT | UART_LSR_THRE)
#घोषणा BYTES_TO_ALIGN(x)			((अचिन्हित दीर्घ)(x) & 0x3)

#घोषणा TEGRA_UART_RX_DMA_BUFFER_SIZE		4096
#घोषणा TEGRA_UART_LSR_TXFIFO_FULL		0x100
#घोषणा TEGRA_UART_IER_EORD			0x20
#घोषणा TEGRA_UART_MCR_RTS_EN			0x40
#घोषणा TEGRA_UART_MCR_CTS_EN			0x20
#घोषणा TEGRA_UART_LSR_ANY			(UART_LSR_OE | UART_LSR_BI | \
						UART_LSR_PE | UART_LSR_FE)
#घोषणा TEGRA_UART_IRDA_CSR			0x08
#घोषणा TEGRA_UART_SIR_ENABLED			0x80

#घोषणा TEGRA_UART_TX_PIO			1
#घोषणा TEGRA_UART_TX_DMA			2
#घोषणा TEGRA_UART_MIN_DMA			16
#घोषणा TEGRA_UART_FIFO_SIZE			32

/*
 * Tx fअगरo trigger level setting in tegra uart is in
 * reverse way then conventional uart.
 */
#घोषणा TEGRA_UART_TX_TRIG_16B			0x00
#घोषणा TEGRA_UART_TX_TRIG_8B			0x10
#घोषणा TEGRA_UART_TX_TRIG_4B			0x20
#घोषणा TEGRA_UART_TX_TRIG_1B			0x30

#घोषणा TEGRA_UART_MAXIMUM			8

/* Default UART setting when started: 115200 no parity, stop, 8 data bits */
#घोषणा TEGRA_UART_DEFAULT_BAUD			115200
#घोषणा TEGRA_UART_DEFAULT_LSR			UART_LCR_WLEN8

/* Tx transfer mode */
#घोषणा TEGRA_TX_PIO				1
#घोषणा TEGRA_TX_DMA				2

#घोषणा TEGRA_UART_FCR_IIR_FIFO_EN		0x40

/**
 * काष्ठा tegra_uart_chip_data: SOC specअगरic data.
 *
 * @tx_fअगरo_full_status: Status flag available क्रम checking tx fअगरo full.
 * @allow_txfअगरo_reset_fअगरo_mode: allow_tx fअगरo reset with fअगरo mode or not.
 *			Tegra30 करोes not allow this.
 * @support_clk_src_भाग: Clock source support the घड़ी भागider.
 * @fअगरo_mode_enable_status: Is FIFO mode enabled?
 * @uart_max_port: Maximum number of UART ports
 * @max_dma_burst_bytes: Maximum size of DMA bursts
 * @error_tolerance_low_range: Lowest number in the error tolerance range
 * @error_tolerance_high_range: Highest number in the error tolerance range
 */
काष्ठा tegra_uart_chip_data अणु
	bool	tx_fअगरo_full_status;
	bool	allow_txfअगरo_reset_fअगरo_mode;
	bool	support_clk_src_भाग;
	bool	fअगरo_mode_enable_status;
	पूर्णांक	uart_max_port;
	पूर्णांक	max_dma_burst_bytes;
	पूर्णांक	error_tolerance_low_range;
	पूर्णांक	error_tolerance_high_range;
पूर्ण;

काष्ठा tegra_baud_tolerance अणु
	u32 lower_range_baud;
	u32 upper_range_baud;
	s32 tolerance;
पूर्ण;

काष्ठा tegra_uart_port अणु
	काष्ठा uart_port			uport;
	स्थिर काष्ठा tegra_uart_chip_data	*cdata;

	काष्ठा clk				*uart_clk;
	काष्ठा reset_control			*rst;
	अचिन्हित पूर्णांक				current_baud;

	/* Register shaकरोw */
	अचिन्हित दीर्घ				fcr_shaकरोw;
	अचिन्हित दीर्घ				mcr_shaकरोw;
	अचिन्हित दीर्घ				lcr_shaकरोw;
	अचिन्हित दीर्घ				ier_shaकरोw;
	bool					rts_active;

	पूर्णांक					tx_in_progress;
	अचिन्हित पूर्णांक				tx_bytes;

	bool					enable_modem_पूर्णांकerrupt;

	bool					rx_समयout;
	पूर्णांक					rx_in_progress;
	पूर्णांक					symb_bit;

	काष्ठा dma_chan				*rx_dma_chan;
	काष्ठा dma_chan				*tx_dma_chan;
	dma_addr_t				rx_dma_buf_phys;
	dma_addr_t				tx_dma_buf_phys;
	अचिन्हित अक्षर				*rx_dma_buf_virt;
	अचिन्हित अक्षर				*tx_dma_buf_virt;
	काष्ठा dma_async_tx_descriptor		*tx_dma_desc;
	काष्ठा dma_async_tx_descriptor		*rx_dma_desc;
	dma_cookie_t				tx_cookie;
	dma_cookie_t				rx_cookie;
	अचिन्हित पूर्णांक				tx_bytes_requested;
	अचिन्हित पूर्णांक				rx_bytes_requested;
	काष्ठा tegra_baud_tolerance		*baud_tolerance;
	पूर्णांक					n_adjustable_baud_rates;
	पूर्णांक					required_rate;
	पूर्णांक					configured_rate;
	bool					use_rx_pio;
	bool					use_tx_pio;
	bool					rx_dma_active;
पूर्ण;

अटल व्योम tegra_uart_start_next_tx(काष्ठा tegra_uart_port *tup);
अटल पूर्णांक tegra_uart_start_rx_dma(काष्ठा tegra_uart_port *tup);
अटल व्योम tegra_uart_dma_channel_मुक्त(काष्ठा tegra_uart_port *tup,
					bool dma_to_memory);

अटल अंतरभूत अचिन्हित दीर्घ tegra_uart_पढ़ो(काष्ठा tegra_uart_port *tup,
		अचिन्हित दीर्घ reg)
अणु
	वापस पढ़ोl(tup->uport.membase + (reg << tup->uport.regshअगरt));
पूर्ण

अटल अंतरभूत व्योम tegra_uart_ग_लिखो(काष्ठा tegra_uart_port *tup, अचिन्हित val,
	अचिन्हित दीर्घ reg)
अणु
	ग_लिखोl(val, tup->uport.membase + (reg << tup->uport.regshअगरt));
पूर्ण

अटल अंतरभूत काष्ठा tegra_uart_port *to_tegra_uport(काष्ठा uart_port *u)
अणु
	वापस container_of(u, काष्ठा tegra_uart_port, uport);
पूर्ण

अटल अचिन्हित पूर्णांक tegra_uart_get_mctrl(काष्ठा uart_port *u)
अणु
	काष्ठा tegra_uart_port *tup = to_tegra_uport(u);

	/*
	 * RI - Ring detector is active
	 * CD/DCD/CAR - Carrier detect is always active. For some reason
	 *	linux has dअगरferent names क्रम carrier detect.
	 * DSR - Data Set पढ़ोy is active as the hardware करोesn't support it.
	 *	Don't know अगर the linux support this yet?
	 * CTS - Clear to send. Always set to active, as the hardware handles
	 *	CTS स्वतःmatically.
	 */
	अगर (tup->enable_modem_पूर्णांकerrupt)
		वापस TIOCM_RI | TIOCM_CD | TIOCM_DSR | TIOCM_CTS;
	वापस TIOCM_CTS;
पूर्ण

अटल व्योम set_rts(काष्ठा tegra_uart_port *tup, bool active)
अणु
	अचिन्हित दीर्घ mcr;

	mcr = tup->mcr_shaकरोw;
	अगर (active)
		mcr |= TEGRA_UART_MCR_RTS_EN;
	अन्यथा
		mcr &= ~TEGRA_UART_MCR_RTS_EN;
	अगर (mcr != tup->mcr_shaकरोw) अणु
		tegra_uart_ग_लिखो(tup, mcr, UART_MCR);
		tup->mcr_shaकरोw = mcr;
	पूर्ण
पूर्ण

अटल व्योम set_dtr(काष्ठा tegra_uart_port *tup, bool active)
अणु
	अचिन्हित दीर्घ mcr;

	mcr = tup->mcr_shaकरोw;
	अगर (active)
		mcr |= UART_MCR_DTR;
	अन्यथा
		mcr &= ~UART_MCR_DTR;
	अगर (mcr != tup->mcr_shaकरोw) अणु
		tegra_uart_ग_लिखो(tup, mcr, UART_MCR);
		tup->mcr_shaकरोw = mcr;
	पूर्ण
पूर्ण

अटल व्योम set_loopbk(काष्ठा tegra_uart_port *tup, bool active)
अणु
	अचिन्हित दीर्घ mcr = tup->mcr_shaकरोw;

	अगर (active)
		mcr |= UART_MCR_LOOP;
	अन्यथा
		mcr &= ~UART_MCR_LOOP;

	अगर (mcr != tup->mcr_shaकरोw) अणु
		tegra_uart_ग_लिखो(tup, mcr, UART_MCR);
		tup->mcr_shaकरोw = mcr;
	पूर्ण
पूर्ण

अटल व्योम tegra_uart_set_mctrl(काष्ठा uart_port *u, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा tegra_uart_port *tup = to_tegra_uport(u);
	पूर्णांक enable;

	tup->rts_active = !!(mctrl & TIOCM_RTS);
	set_rts(tup, tup->rts_active);

	enable = !!(mctrl & TIOCM_DTR);
	set_dtr(tup, enable);

	enable = !!(mctrl & TIOCM_LOOP);
	set_loopbk(tup, enable);
पूर्ण

अटल व्योम tegra_uart_अवरोध_ctl(काष्ठा uart_port *u, पूर्णांक अवरोध_ctl)
अणु
	काष्ठा tegra_uart_port *tup = to_tegra_uport(u);
	अचिन्हित दीर्घ lcr;

	lcr = tup->lcr_shaकरोw;
	अगर (अवरोध_ctl)
		lcr |= UART_LCR_SBC;
	अन्यथा
		lcr &= ~UART_LCR_SBC;
	tegra_uart_ग_लिखो(tup, lcr, UART_LCR);
	tup->lcr_shaकरोw = lcr;
पूर्ण

/**
 * tegra_uart_रुको_cycle_समय: Wait क्रम N UART घड़ी periods
 *
 * @tup:	Tegra serial port data काष्ठाure.
 * @cycles:	Number of घड़ी periods to रुको.
 *
 * Tegra UARTs are घड़ीed at 16X the baud/bit rate and hence the UART
 * घड़ी speed is 16X the current baud rate.
 */
अटल व्योम tegra_uart_रुको_cycle_समय(काष्ठा tegra_uart_port *tup,
				       अचिन्हित पूर्णांक cycles)
अणु
	अगर (tup->current_baud)
		udelay(DIV_ROUND_UP(cycles * 1000000, tup->current_baud * 16));
पूर्ण

/* Wait क्रम a symbol-समय. */
अटल व्योम tegra_uart_रुको_sym_समय(काष्ठा tegra_uart_port *tup,
		अचिन्हित पूर्णांक syms)
अणु
	अगर (tup->current_baud)
		udelay(DIV_ROUND_UP(syms * tup->symb_bit * 1000000,
			tup->current_baud));
पूर्ण

अटल पूर्णांक tegra_uart_रुको_fअगरo_mode_enabled(काष्ठा tegra_uart_port *tup)
अणु
	अचिन्हित दीर्घ iir;
	अचिन्हित पूर्णांक पंचांगout = 100;

	करो अणु
		iir = tegra_uart_पढ़ो(tup, UART_IIR);
		अगर (iir & TEGRA_UART_FCR_IIR_FIFO_EN)
			वापस 0;
		udelay(1);
	पूर्ण जबतक (--पंचांगout);

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम tegra_uart_fअगरo_reset(काष्ठा tegra_uart_port *tup, u8 fcr_bits)
अणु
	अचिन्हित दीर्घ fcr = tup->fcr_shaकरोw;
	अचिन्हित पूर्णांक lsr, पंचांगout = 10000;

	अगर (tup->rts_active)
		set_rts(tup, false);

	अगर (tup->cdata->allow_txfअगरo_reset_fअगरo_mode) अणु
		fcr |= fcr_bits & (UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
		tegra_uart_ग_लिखो(tup, fcr, UART_FCR);
	पूर्ण अन्यथा अणु
		fcr &= ~UART_FCR_ENABLE_FIFO;
		tegra_uart_ग_लिखो(tup, fcr, UART_FCR);
		udelay(60);
		fcr |= fcr_bits & (UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
		tegra_uart_ग_लिखो(tup, fcr, UART_FCR);
		fcr |= UART_FCR_ENABLE_FIFO;
		tegra_uart_ग_लिखो(tup, fcr, UART_FCR);
		अगर (tup->cdata->fअगरo_mode_enable_status)
			tegra_uart_रुको_fअगरo_mode_enabled(tup);
	पूर्ण

	/* Dummy पढ़ो to ensure the ग_लिखो is posted */
	tegra_uart_पढ़ो(tup, UART_SCR);

	/*
	 * For all tegra devices (up to t210), there is a hardware issue that
	 * requires software to रुको क्रम 32 UART घड़ी periods क्रम the flush
	 * to propagate, otherwise data could be lost.
	 */
	tegra_uart_रुको_cycle_समय(tup, 32);

	करो अणु
		lsr = tegra_uart_पढ़ो(tup, UART_LSR);
		अगर ((lsr & UART_LSR_TEMT) && !(lsr & UART_LSR_DR))
			अवरोध;
		udelay(1);
	पूर्ण जबतक (--पंचांगout);

	अगर (tup->rts_active)
		set_rts(tup, true);
पूर्ण

अटल दीर्घ tegra_get_tolerance_rate(काष्ठा tegra_uart_port *tup,
				     अचिन्हित पूर्णांक baud, दीर्घ rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tup->n_adjustable_baud_rates; ++i) अणु
		अगर (baud >= tup->baud_tolerance[i].lower_range_baud &&
		    baud <= tup->baud_tolerance[i].upper_range_baud)
			वापस (rate + (rate *
				tup->baud_tolerance[i].tolerance) / 10000);
	पूर्ण

	वापस rate;
पूर्ण

अटल पूर्णांक tegra_check_rate_in_range(काष्ठा tegra_uart_port *tup)
अणु
	दीर्घ dअगरf;

	dअगरf = ((दीर्घ)(tup->configured_rate - tup->required_rate) * 10000)
		/ tup->required_rate;
	अगर (dअगरf < (tup->cdata->error_tolerance_low_range * 100) ||
	    dअगरf > (tup->cdata->error_tolerance_high_range * 100)) अणु
		dev_err(tup->uport.dev,
			"configured baud rate is out of range by %ld", dअगरf);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_set_baudrate(काष्ठा tegra_uart_port *tup, अचिन्हित पूर्णांक baud)
अणु
	अचिन्हित दीर्घ rate;
	अचिन्हित पूर्णांक भागisor;
	अचिन्हित दीर्घ lcr;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (tup->current_baud == baud)
		वापस 0;

	अगर (tup->cdata->support_clk_src_भाग) अणु
		rate = baud * 16;
		tup->required_rate = rate;

		अगर (tup->n_adjustable_baud_rates)
			rate = tegra_get_tolerance_rate(tup, baud, rate);

		ret = clk_set_rate(tup->uart_clk, rate);
		अगर (ret < 0) अणु
			dev_err(tup->uport.dev,
				"clk_set_rate() failed for rate %lu\n", rate);
			वापस ret;
		पूर्ण
		tup->configured_rate = clk_get_rate(tup->uart_clk);
		भागisor = 1;
		ret = tegra_check_rate_in_range(tup);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		rate = clk_get_rate(tup->uart_clk);
		भागisor = DIV_ROUND_CLOSEST(rate, baud * 16);
	पूर्ण

	spin_lock_irqsave(&tup->uport.lock, flags);
	lcr = tup->lcr_shaकरोw;
	lcr |= UART_LCR_DLAB;
	tegra_uart_ग_लिखो(tup, lcr, UART_LCR);

	tegra_uart_ग_लिखो(tup, भागisor & 0xFF, UART_TX);
	tegra_uart_ग_लिखो(tup, ((भागisor >> 8) & 0xFF), UART_IER);

	lcr &= ~UART_LCR_DLAB;
	tegra_uart_ग_लिखो(tup, lcr, UART_LCR);

	/* Dummy पढ़ो to ensure the ग_लिखो is posted */
	tegra_uart_पढ़ो(tup, UART_SCR);
	spin_unlock_irqrestore(&tup->uport.lock, flags);

	tup->current_baud = baud;

	/* रुको two अक्षरacter पूर्णांकervals at new rate */
	tegra_uart_रुको_sym_समय(tup, 2);
	वापस 0;
पूर्ण

अटल अक्षर tegra_uart_decode_rx_error(काष्ठा tegra_uart_port *tup,
			अचिन्हित दीर्घ lsr)
अणु
	अक्षर flag = TTY_NORMAL;

	अगर (unlikely(lsr & TEGRA_UART_LSR_ANY)) अणु
		अगर (lsr & UART_LSR_OE) अणु
			/* Overrrun error */
			flag = TTY_OVERRUN;
			tup->uport.icount.overrun++;
			dev_dbg(tup->uport.dev, "Got overrun errors\n");
		पूर्ण अन्यथा अगर (lsr & UART_LSR_PE) अणु
			/* Parity error */
			flag = TTY_PARITY;
			tup->uport.icount.parity++;
			dev_dbg(tup->uport.dev, "Got Parity errors\n");
		पूर्ण अन्यथा अगर (lsr & UART_LSR_FE) अणु
			flag = TTY_FRAME;
			tup->uport.icount.frame++;
			dev_dbg(tup->uport.dev, "Got frame errors\n");
		पूर्ण अन्यथा अगर (lsr & UART_LSR_BI) अणु
			/*
			 * Break error
			 * If FIFO पढ़ो error without any data, reset Rx FIFO
			 */
			अगर (!(lsr & UART_LSR_DR) && (lsr & UART_LSR_FIFOE))
				tegra_uart_fअगरo_reset(tup, UART_FCR_CLEAR_RCVR);
			अगर (tup->uport.ignore_status_mask & UART_LSR_BI)
				वापस TTY_BREAK;
			flag = TTY_BREAK;
			tup->uport.icount.brk++;
			dev_dbg(tup->uport.dev, "Got Break\n");
		पूर्ण
		uart_insert_अक्षर(&tup->uport, lsr, UART_LSR_OE, 0, flag);
	पूर्ण

	वापस flag;
पूर्ण

अटल पूर्णांक tegra_uart_request_port(काष्ठा uart_port *u)
अणु
	वापस 0;
पूर्ण

अटल व्योम tegra_uart_release_port(काष्ठा uart_port *u)
अणु
	/* Nothing to करो here */
पूर्ण

अटल व्योम tegra_uart_fill_tx_fअगरo(काष्ठा tegra_uart_port *tup, पूर्णांक max_bytes)
अणु
	काष्ठा circ_buf *xmit = &tup->uport.state->xmit;
	पूर्णांक i;

	क्रम (i = 0; i < max_bytes; i++) अणु
		BUG_ON(uart_circ_empty(xmit));
		अगर (tup->cdata->tx_fअगरo_full_status) अणु
			अचिन्हित दीर्घ lsr = tegra_uart_पढ़ो(tup, UART_LSR);
			अगर ((lsr & TEGRA_UART_LSR_TXFIFO_FULL))
				अवरोध;
		पूर्ण
		tegra_uart_ग_लिखो(tup, xmit->buf[xmit->tail], UART_TX);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		tup->uport.icount.tx++;
	पूर्ण
पूर्ण

अटल व्योम tegra_uart_start_pio_tx(काष्ठा tegra_uart_port *tup,
		अचिन्हित पूर्णांक bytes)
अणु
	अगर (bytes > TEGRA_UART_MIN_DMA)
		bytes = TEGRA_UART_MIN_DMA;

	tup->tx_in_progress = TEGRA_UART_TX_PIO;
	tup->tx_bytes = bytes;
	tup->ier_shaकरोw |= UART_IER_THRI;
	tegra_uart_ग_लिखो(tup, tup->ier_shaकरोw, UART_IER);
पूर्ण

अटल व्योम tegra_uart_tx_dma_complete(व्योम *args)
अणु
	काष्ठा tegra_uart_port *tup = args;
	काष्ठा circ_buf *xmit = &tup->uport.state->xmit;
	काष्ठा dma_tx_state state;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक count;

	dmaengine_tx_status(tup->tx_dma_chan, tup->tx_cookie, &state);
	count = tup->tx_bytes_requested - state.residue;
	async_tx_ack(tup->tx_dma_desc);
	spin_lock_irqsave(&tup->uport.lock, flags);
	xmit->tail = (xmit->tail + count) & (UART_XMIT_SIZE - 1);
	tup->tx_in_progress = 0;
	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&tup->uport);
	tegra_uart_start_next_tx(tup);
	spin_unlock_irqrestore(&tup->uport.lock, flags);
पूर्ण

अटल पूर्णांक tegra_uart_start_tx_dma(काष्ठा tegra_uart_port *tup,
		अचिन्हित दीर्घ count)
अणु
	काष्ठा circ_buf *xmit = &tup->uport.state->xmit;
	dma_addr_t tx_phys_addr;

	tup->tx_bytes = count & ~(0xF);
	tx_phys_addr = tup->tx_dma_buf_phys + xmit->tail;

	dma_sync_single_क्रम_device(tup->uport.dev, tx_phys_addr,
				   tup->tx_bytes, DMA_TO_DEVICE);

	tup->tx_dma_desc = dmaengine_prep_slave_single(tup->tx_dma_chan,
				tx_phys_addr, tup->tx_bytes, DMA_MEM_TO_DEV,
				DMA_PREP_INTERRUPT);
	अगर (!tup->tx_dma_desc) अणु
		dev_err(tup->uport.dev, "Not able to get desc for Tx\n");
		वापस -EIO;
	पूर्ण

	tup->tx_dma_desc->callback = tegra_uart_tx_dma_complete;
	tup->tx_dma_desc->callback_param = tup;
	tup->tx_in_progress = TEGRA_UART_TX_DMA;
	tup->tx_bytes_requested = tup->tx_bytes;
	tup->tx_cookie = dmaengine_submit(tup->tx_dma_desc);
	dma_async_issue_pending(tup->tx_dma_chan);
	वापस 0;
पूर्ण

अटल व्योम tegra_uart_start_next_tx(काष्ठा tegra_uart_port *tup)
अणु
	अचिन्हित दीर्घ tail;
	अचिन्हित दीर्घ count;
	काष्ठा circ_buf *xmit = &tup->uport.state->xmit;

	अगर (!tup->current_baud)
		वापस;

	tail = (अचिन्हित दीर्घ)&xmit->buf[xmit->tail];
	count = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);
	अगर (!count)
		वापस;

	अगर (tup->use_tx_pio || count < TEGRA_UART_MIN_DMA)
		tegra_uart_start_pio_tx(tup, count);
	अन्यथा अगर (BYTES_TO_ALIGN(tail) > 0)
		tegra_uart_start_pio_tx(tup, BYTES_TO_ALIGN(tail));
	अन्यथा
		tegra_uart_start_tx_dma(tup, count);
पूर्ण

/* Called by serial core driver with u->lock taken. */
अटल व्योम tegra_uart_start_tx(काष्ठा uart_port *u)
अणु
	काष्ठा tegra_uart_port *tup = to_tegra_uport(u);
	काष्ठा circ_buf *xmit = &u->state->xmit;

	अगर (!uart_circ_empty(xmit) && !tup->tx_in_progress)
		tegra_uart_start_next_tx(tup);
पूर्ण

अटल अचिन्हित पूर्णांक tegra_uart_tx_empty(काष्ठा uart_port *u)
अणु
	काष्ठा tegra_uart_port *tup = to_tegra_uport(u);
	अचिन्हित पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&u->lock, flags);
	अगर (!tup->tx_in_progress) अणु
		अचिन्हित दीर्घ lsr = tegra_uart_पढ़ो(tup, UART_LSR);
		अगर ((lsr & TX_EMPTY_STATUS) == TX_EMPTY_STATUS)
			ret = TIOCSER_TEMT;
	पूर्ण
	spin_unlock_irqrestore(&u->lock, flags);
	वापस ret;
पूर्ण

अटल व्योम tegra_uart_stop_tx(काष्ठा uart_port *u)
अणु
	काष्ठा tegra_uart_port *tup = to_tegra_uport(u);
	काष्ठा circ_buf *xmit = &tup->uport.state->xmit;
	काष्ठा dma_tx_state state;
	अचिन्हित पूर्णांक count;

	अगर (tup->tx_in_progress != TEGRA_UART_TX_DMA)
		वापस;

	dmaengine_terminate_all(tup->tx_dma_chan);
	dmaengine_tx_status(tup->tx_dma_chan, tup->tx_cookie, &state);
	count = tup->tx_bytes_requested - state.residue;
	async_tx_ack(tup->tx_dma_desc);
	xmit->tail = (xmit->tail + count) & (UART_XMIT_SIZE - 1);
	tup->tx_in_progress = 0;
पूर्ण

अटल व्योम tegra_uart_handle_tx_pio(काष्ठा tegra_uart_port *tup)
अणु
	काष्ठा circ_buf *xmit = &tup->uport.state->xmit;

	tegra_uart_fill_tx_fअगरo(tup, tup->tx_bytes);
	tup->tx_in_progress = 0;
	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&tup->uport);
	tegra_uart_start_next_tx(tup);
पूर्ण

अटल व्योम tegra_uart_handle_rx_pio(काष्ठा tegra_uart_port *tup,
		काष्ठा tty_port *port)
अणु
	करो अणु
		अक्षर flag = TTY_NORMAL;
		अचिन्हित दीर्घ lsr = 0;
		अचिन्हित अक्षर ch;

		lsr = tegra_uart_पढ़ो(tup, UART_LSR);
		अगर (!(lsr & UART_LSR_DR))
			अवरोध;

		flag = tegra_uart_decode_rx_error(tup, lsr);
		अगर (flag != TTY_NORMAL)
			जारी;

		ch = (अचिन्हित अक्षर) tegra_uart_पढ़ो(tup, UART_RX);
		tup->uport.icount.rx++;

		अगर (uart_handle_sysrq_अक्षर(&tup->uport, ch))
			जारी;

		अगर (tup->uport.ignore_status_mask & UART_LSR_DR)
			जारी;

		tty_insert_flip_अक्षर(port, ch, flag);
	पूर्ण जबतक (1);
पूर्ण

अटल व्योम tegra_uart_copy_rx_to_tty(काष्ठा tegra_uart_port *tup,
				      काष्ठा tty_port *port,
				      अचिन्हित पूर्णांक count)
अणु
	पूर्णांक copied;

	/* If count is zero, then there is no data to be copied */
	अगर (!count)
		वापस;

	tup->uport.icount.rx += count;

	अगर (tup->uport.ignore_status_mask & UART_LSR_DR)
		वापस;

	dma_sync_single_क्रम_cpu(tup->uport.dev, tup->rx_dma_buf_phys,
				count, DMA_FROM_DEVICE);
	copied = tty_insert_flip_string(port,
			((अचिन्हित अक्षर *)(tup->rx_dma_buf_virt)), count);
	अगर (copied != count) अणु
		WARN_ON(1);
		dev_err(tup->uport.dev, "RxData copy to tty layer failed\n");
	पूर्ण
	dma_sync_single_क्रम_device(tup->uport.dev, tup->rx_dma_buf_phys,
				   count, DMA_TO_DEVICE);
पूर्ण

अटल व्योम करो_handle_rx_pio(काष्ठा tegra_uart_port *tup)
अणु
	काष्ठा tty_काष्ठा *tty = tty_port_tty_get(&tup->uport.state->port);
	काष्ठा tty_port *port = &tup->uport.state->port;

	tegra_uart_handle_rx_pio(tup, port);
	अगर (tty) अणु
		tty_flip_buffer_push(port);
		tty_kref_put(tty);
	पूर्ण
पूर्ण

अटल व्योम tegra_uart_rx_buffer_push(काष्ठा tegra_uart_port *tup,
				      अचिन्हित पूर्णांक residue)
अणु
	काष्ठा tty_port *port = &tup->uport.state->port;
	अचिन्हित पूर्णांक count;

	async_tx_ack(tup->rx_dma_desc);
	count = tup->rx_bytes_requested - residue;

	/* If we are here, DMA is stopped */
	tegra_uart_copy_rx_to_tty(tup, port, count);

	करो_handle_rx_pio(tup);
पूर्ण

अटल व्योम tegra_uart_rx_dma_complete(व्योम *args)
अणु
	काष्ठा tegra_uart_port *tup = args;
	काष्ठा uart_port *u = &tup->uport;
	अचिन्हित दीर्घ flags;
	काष्ठा dma_tx_state state;
	क्रमागत dma_status status;

	spin_lock_irqsave(&u->lock, flags);

	status = dmaengine_tx_status(tup->rx_dma_chan, tup->rx_cookie, &state);

	अगर (status == DMA_IN_PROGRESS) अणु
		dev_dbg(tup->uport.dev, "RX DMA is in progress\n");
		जाओ करोne;
	पूर्ण

	/* Deactivate flow control to stop sender */
	अगर (tup->rts_active)
		set_rts(tup, false);

	tup->rx_dma_active = false;
	tegra_uart_rx_buffer_push(tup, 0);
	tegra_uart_start_rx_dma(tup);

	/* Activate flow control to start transfer */
	अगर (tup->rts_active)
		set_rts(tup, true);

करोne:
	spin_unlock_irqrestore(&u->lock, flags);
पूर्ण

अटल व्योम tegra_uart_terminate_rx_dma(काष्ठा tegra_uart_port *tup)
अणु
	काष्ठा dma_tx_state state;

	अगर (!tup->rx_dma_active) अणु
		करो_handle_rx_pio(tup);
		वापस;
	पूर्ण

	dmaengine_terminate_all(tup->rx_dma_chan);
	dmaengine_tx_status(tup->rx_dma_chan, tup->rx_cookie, &state);

	tegra_uart_rx_buffer_push(tup, state.residue);
	tup->rx_dma_active = false;
पूर्ण

अटल व्योम tegra_uart_handle_rx_dma(काष्ठा tegra_uart_port *tup)
अणु
	/* Deactivate flow control to stop sender */
	अगर (tup->rts_active)
		set_rts(tup, false);

	tegra_uart_terminate_rx_dma(tup);

	अगर (tup->rts_active)
		set_rts(tup, true);
पूर्ण

अटल पूर्णांक tegra_uart_start_rx_dma(काष्ठा tegra_uart_port *tup)
अणु
	अचिन्हित पूर्णांक count = TEGRA_UART_RX_DMA_BUFFER_SIZE;

	अगर (tup->rx_dma_active)
		वापस 0;

	tup->rx_dma_desc = dmaengine_prep_slave_single(tup->rx_dma_chan,
				tup->rx_dma_buf_phys, count, DMA_DEV_TO_MEM,
				DMA_PREP_INTERRUPT);
	अगर (!tup->rx_dma_desc) अणु
		dev_err(tup->uport.dev, "Not able to get desc for Rx\n");
		वापस -EIO;
	पूर्ण

	tup->rx_dma_active = true;
	tup->rx_dma_desc->callback = tegra_uart_rx_dma_complete;
	tup->rx_dma_desc->callback_param = tup;
	tup->rx_bytes_requested = count;
	tup->rx_cookie = dmaengine_submit(tup->rx_dma_desc);
	dma_async_issue_pending(tup->rx_dma_chan);
	वापस 0;
पूर्ण

अटल व्योम tegra_uart_handle_modem_संकेत_change(काष्ठा uart_port *u)
अणु
	काष्ठा tegra_uart_port *tup = to_tegra_uport(u);
	अचिन्हित दीर्घ msr;

	msr = tegra_uart_पढ़ो(tup, UART_MSR);
	अगर (!(msr & UART_MSR_ANY_DELTA))
		वापस;

	अगर (msr & UART_MSR_TERI)
		tup->uport.icount.rng++;
	अगर (msr & UART_MSR_DDSR)
		tup->uport.icount.dsr++;
	/* We may only get DDCD when HW init and reset */
	अगर (msr & UART_MSR_DDCD)
		uart_handle_dcd_change(&tup->uport, msr & UART_MSR_DCD);
	/* Will start/stop_tx accordingly */
	अगर (msr & UART_MSR_DCTS)
		uart_handle_cts_change(&tup->uport, msr & UART_MSR_CTS);
पूर्ण

अटल irqवापस_t tegra_uart_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_uart_port *tup = data;
	काष्ठा uart_port *u = &tup->uport;
	अचिन्हित दीर्घ iir;
	अचिन्हित दीर्घ ier;
	bool is_rx_start = false;
	bool is_rx_पूर्णांक = false;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&u->lock, flags);
	जबतक (1) अणु
		iir = tegra_uart_पढ़ो(tup, UART_IIR);
		अगर (iir & UART_IIR_NO_INT) अणु
			अगर (!tup->use_rx_pio && is_rx_पूर्णांक) अणु
				tegra_uart_handle_rx_dma(tup);
				अगर (tup->rx_in_progress) अणु
					ier = tup->ier_shaकरोw;
					ier |= (UART_IER_RLSI | UART_IER_RTOIE |
						TEGRA_UART_IER_EORD | UART_IER_RDI);
					tup->ier_shaकरोw = ier;
					tegra_uart_ग_लिखो(tup, ier, UART_IER);
				पूर्ण
			पूर्ण अन्यथा अगर (is_rx_start) अणु
				tegra_uart_start_rx_dma(tup);
			पूर्ण
			spin_unlock_irqrestore(&u->lock, flags);
			वापस IRQ_HANDLED;
		पूर्ण

		चयन ((iir >> 1) & 0x7) अणु
		हाल 0: /* Modem संकेत change पूर्णांकerrupt */
			tegra_uart_handle_modem_संकेत_change(u);
			अवरोध;

		हाल 1: /* Transmit पूर्णांकerrupt only triggered when using PIO */
			tup->ier_shaकरोw &= ~UART_IER_THRI;
			tegra_uart_ग_लिखो(tup, tup->ier_shaकरोw, UART_IER);
			tegra_uart_handle_tx_pio(tup);
			अवरोध;

		हाल 4: /* End of data */
		हाल 6: /* Rx समयout */
			अगर (!tup->use_rx_pio) अणु
				is_rx_पूर्णांक = tup->rx_in_progress;
				/* Disable Rx पूर्णांकerrupts */
				ier = tup->ier_shaकरोw;
				ier &= ~(UART_IER_RDI | UART_IER_RLSI |
					UART_IER_RTOIE | TEGRA_UART_IER_EORD);
				tup->ier_shaकरोw = ier;
				tegra_uart_ग_लिखो(tup, ier, UART_IER);
				अवरोध;
			पूर्ण
			fallthrough;
		हाल 2: /* Receive */
			अगर (!tup->use_rx_pio) अणु
				is_rx_start = tup->rx_in_progress;
				tup->ier_shaकरोw  &= ~UART_IER_RDI;
				tegra_uart_ग_लिखो(tup, tup->ier_shaकरोw,
						 UART_IER);
			पूर्ण अन्यथा अणु
				करो_handle_rx_pio(tup);
			पूर्ण
			अवरोध;

		हाल 3: /* Receive error */
			tegra_uart_decode_rx_error(tup,
					tegra_uart_पढ़ो(tup, UART_LSR));
			अवरोध;

		हाल 5: /* अवरोध nothing to handle */
		हाल 7: /* अवरोध nothing to handle */
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम tegra_uart_stop_rx(काष्ठा uart_port *u)
अणु
	काष्ठा tegra_uart_port *tup = to_tegra_uport(u);
	काष्ठा tty_port *port = &tup->uport.state->port;
	अचिन्हित दीर्घ ier;

	अगर (tup->rts_active)
		set_rts(tup, false);

	अगर (!tup->rx_in_progress)
		वापस;

	tegra_uart_रुको_sym_समय(tup, 1); /* रुको one अक्षरacter पूर्णांकerval */

	ier = tup->ier_shaकरोw;
	ier &= ~(UART_IER_RDI | UART_IER_RLSI | UART_IER_RTOIE |
					TEGRA_UART_IER_EORD);
	tup->ier_shaकरोw = ier;
	tegra_uart_ग_लिखो(tup, ier, UART_IER);
	tup->rx_in_progress = 0;

	अगर (!tup->use_rx_pio)
		tegra_uart_terminate_rx_dma(tup);
	अन्यथा
		tegra_uart_handle_rx_pio(tup, port);
पूर्ण

अटल व्योम tegra_uart_hw_deinit(काष्ठा tegra_uart_port *tup)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ अक्षर_समय = DIV_ROUND_UP(10000000, tup->current_baud);
	अचिन्हित दीर्घ fअगरo_empty_समय = tup->uport.fअगरosize * अक्षर_समय;
	अचिन्हित दीर्घ रुको_समय;
	अचिन्हित दीर्घ lsr;
	अचिन्हित दीर्घ msr;
	अचिन्हित दीर्घ mcr;

	/* Disable पूर्णांकerrupts */
	tegra_uart_ग_लिखो(tup, 0, UART_IER);

	lsr = tegra_uart_पढ़ो(tup, UART_LSR);
	अगर ((lsr & UART_LSR_TEMT) != UART_LSR_TEMT) अणु
		msr = tegra_uart_पढ़ो(tup, UART_MSR);
		mcr = tegra_uart_पढ़ो(tup, UART_MCR);
		अगर ((mcr & TEGRA_UART_MCR_CTS_EN) && (msr & UART_MSR_CTS))
			dev_err(tup->uport.dev,
				"Tx Fifo not empty, CTS disabled, waiting\n");

		/* Wait क्रम Tx fअगरo to be empty */
		जबतक ((lsr & UART_LSR_TEMT) != UART_LSR_TEMT) अणु
			रुको_समय = min(fअगरo_empty_समय, 100lu);
			udelay(रुको_समय);
			fअगरo_empty_समय -= रुको_समय;
			अगर (!fअगरo_empty_समय) अणु
				msr = tegra_uart_पढ़ो(tup, UART_MSR);
				mcr = tegra_uart_पढ़ो(tup, UART_MCR);
				अगर ((mcr & TEGRA_UART_MCR_CTS_EN) &&
					(msr & UART_MSR_CTS))
					dev_err(tup->uport.dev,
						"Slave not ready\n");
				अवरोध;
			पूर्ण
			lsr = tegra_uart_पढ़ो(tup, UART_LSR);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&tup->uport.lock, flags);
	/* Reset the Rx and Tx FIFOs */
	tegra_uart_fअगरo_reset(tup, UART_FCR_CLEAR_XMIT | UART_FCR_CLEAR_RCVR);
	tup->current_baud = 0;
	spin_unlock_irqrestore(&tup->uport.lock, flags);

	tup->rx_in_progress = 0;
	tup->tx_in_progress = 0;

	अगर (!tup->use_rx_pio)
		tegra_uart_dma_channel_मुक्त(tup, true);
	अगर (!tup->use_tx_pio)
		tegra_uart_dma_channel_मुक्त(tup, false);

	clk_disable_unprepare(tup->uart_clk);
पूर्ण

अटल पूर्णांक tegra_uart_hw_init(काष्ठा tegra_uart_port *tup)
अणु
	पूर्णांक ret;

	tup->fcr_shaकरोw = 0;
	tup->mcr_shaकरोw = 0;
	tup->lcr_shaकरोw = 0;
	tup->ier_shaकरोw = 0;
	tup->current_baud = 0;

	clk_prepare_enable(tup->uart_clk);

	/* Reset the UART controller to clear all previous status.*/
	reset_control_निश्चित(tup->rst);
	udelay(10);
	reset_control_deनिश्चित(tup->rst);

	tup->rx_in_progress = 0;
	tup->tx_in_progress = 0;

	/*
	 * Set the trigger level
	 *
	 * For PIO mode:
	 *
	 * For receive, this will पूर्णांकerrupt the CPU after that many number of
	 * bytes are received, क्रम the reमुख्यing bytes the receive समयout
	 * पूर्णांकerrupt is received. Rx high watermark is set to 4.
	 *
	 * For transmit, अगर the trasnmit पूर्णांकerrupt is enabled, this will
	 * पूर्णांकerrupt the CPU when the number of entries in the FIFO reaches the
	 * low watermark. Tx low watermark is set to 16 bytes.
	 *
	 * For DMA mode:
	 *
	 * Set the Tx trigger to 16. This should match the DMA burst size that
	 * programmed in the DMA रेजिस्टरs.
	 */
	tup->fcr_shaकरोw = UART_FCR_ENABLE_FIFO;

	अगर (tup->use_rx_pio) अणु
		tup->fcr_shaकरोw |= UART_FCR_R_TRIG_11;
	पूर्ण अन्यथा अणु
		अगर (tup->cdata->max_dma_burst_bytes == 8)
			tup->fcr_shaकरोw |= UART_FCR_R_TRIG_10;
		अन्यथा
			tup->fcr_shaकरोw |= UART_FCR_R_TRIG_01;
	पूर्ण

	tup->fcr_shaकरोw |= TEGRA_UART_TX_TRIG_16B;
	tegra_uart_ग_लिखो(tup, tup->fcr_shaकरोw, UART_FCR);

	/* Dummy पढ़ो to ensure the ग_लिखो is posted */
	tegra_uart_पढ़ो(tup, UART_SCR);

	अगर (tup->cdata->fअगरo_mode_enable_status) अणु
		ret = tegra_uart_रुको_fअगरo_mode_enabled(tup);
		dev_err(tup->uport.dev, "FIFO mode not enabled\n");
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		/*
		 * For all tegra devices (up to t210), there is a hardware
		 * issue that requires software to रुको क्रम 3 UART घड़ी
		 * periods after enabling the TX fअगरo, otherwise data could
		 * be lost.
		 */
		tegra_uart_रुको_cycle_समय(tup, 3);
	पूर्ण

	/*
	 * Initialize the UART with शेष configuration
	 * (115200, N, 8, 1) so that the receive DMA buffer may be
	 * enqueued
	 */
	ret = tegra_set_baudrate(tup, TEGRA_UART_DEFAULT_BAUD);
	अगर (ret < 0) अणु
		dev_err(tup->uport.dev, "Failed to set baud rate\n");
		वापस ret;
	पूर्ण
	अगर (!tup->use_rx_pio) अणु
		tup->lcr_shaकरोw = TEGRA_UART_DEFAULT_LSR;
		tup->fcr_shaकरोw |= UART_FCR_DMA_SELECT;
		tegra_uart_ग_लिखो(tup, tup->fcr_shaकरोw, UART_FCR);
	पूर्ण अन्यथा अणु
		tegra_uart_ग_लिखो(tup, tup->fcr_shaकरोw, UART_FCR);
	पूर्ण
	tup->rx_in_progress = 1;

	/*
	 * Enable IE_RXS क्रम the receive status पूर्णांकerrupts like line errros.
	 * Enable IE_RX_TIMEOUT to get the bytes which cannot be DMA'd.
	 *
	 * EORD is dअगरferent पूर्णांकerrupt than RX_TIMEOUT - RX_TIMEOUT occurs when
	 * the DATA is sitting in the FIFO and couldn't be transferred to the
	 * DMA as the DMA size alignment (4 bytes) is not met. EORD will be
	 * triggered when there is a छोड़ो of the incomming data stream क्रम 4
	 * अक्षरacters दीर्घ.
	 *
	 * For छोड़ोs in the data which is not aligned to 4 bytes, we get
	 * both the EORD as well as RX_TIMEOUT - SW sees RX_TIMEOUT first
	 * then the EORD.
	 */
	tup->ier_shaकरोw = UART_IER_RLSI | UART_IER_RTOIE | UART_IER_RDI;

	/*
	 * If using DMA mode, enable EORD पूर्णांकerrupt to notअगरy about RX
	 * completion.
	 */
	अगर (!tup->use_rx_pio)
		tup->ier_shaकरोw |= TEGRA_UART_IER_EORD;

	tegra_uart_ग_लिखो(tup, tup->ier_shaकरोw, UART_IER);
	वापस 0;
पूर्ण

अटल व्योम tegra_uart_dma_channel_मुक्त(काष्ठा tegra_uart_port *tup,
		bool dma_to_memory)
अणु
	अगर (dma_to_memory) अणु
		dmaengine_terminate_all(tup->rx_dma_chan);
		dma_release_channel(tup->rx_dma_chan);
		dma_मुक्त_coherent(tup->uport.dev, TEGRA_UART_RX_DMA_BUFFER_SIZE,
				tup->rx_dma_buf_virt, tup->rx_dma_buf_phys);
		tup->rx_dma_chan = शून्य;
		tup->rx_dma_buf_phys = 0;
		tup->rx_dma_buf_virt = शून्य;
	पूर्ण अन्यथा अणु
		dmaengine_terminate_all(tup->tx_dma_chan);
		dma_release_channel(tup->tx_dma_chan);
		dma_unmap_single(tup->uport.dev, tup->tx_dma_buf_phys,
			UART_XMIT_SIZE, DMA_TO_DEVICE);
		tup->tx_dma_chan = शून्य;
		tup->tx_dma_buf_phys = 0;
		tup->tx_dma_buf_virt = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_uart_dma_channel_allocate(काष्ठा tegra_uart_port *tup,
			bool dma_to_memory)
अणु
	काष्ठा dma_chan *dma_chan;
	अचिन्हित अक्षर *dma_buf;
	dma_addr_t dma_phys;
	पूर्णांक ret;
	काष्ठा dma_slave_config dma_sconfig;

	dma_chan = dma_request_chan(tup->uport.dev, dma_to_memory ? "rx" : "tx");
	अगर (IS_ERR(dma_chan)) अणु
		ret = PTR_ERR(dma_chan);
		dev_err(tup->uport.dev,
			"DMA channel alloc failed: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (dma_to_memory) अणु
		dma_buf = dma_alloc_coherent(tup->uport.dev,
				TEGRA_UART_RX_DMA_BUFFER_SIZE,
				 &dma_phys, GFP_KERNEL);
		अगर (!dma_buf) अणु
			dev_err(tup->uport.dev,
				"Not able to allocate the dma buffer\n");
			dma_release_channel(dma_chan);
			वापस -ENOMEM;
		पूर्ण
		dma_sync_single_क्रम_device(tup->uport.dev, dma_phys,
					   TEGRA_UART_RX_DMA_BUFFER_SIZE,
					   DMA_TO_DEVICE);
		dma_sconfig.src_addr = tup->uport.mapbase;
		dma_sconfig.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
		dma_sconfig.src_maxburst = tup->cdata->max_dma_burst_bytes;
		tup->rx_dma_chan = dma_chan;
		tup->rx_dma_buf_virt = dma_buf;
		tup->rx_dma_buf_phys = dma_phys;
	पूर्ण अन्यथा अणु
		dma_phys = dma_map_single(tup->uport.dev,
			tup->uport.state->xmit.buf, UART_XMIT_SIZE,
			DMA_TO_DEVICE);
		अगर (dma_mapping_error(tup->uport.dev, dma_phys)) अणु
			dev_err(tup->uport.dev, "dma_map_single tx failed\n");
			dma_release_channel(dma_chan);
			वापस -ENOMEM;
		पूर्ण
		dma_buf = tup->uport.state->xmit.buf;
		dma_sconfig.dst_addr = tup->uport.mapbase;
		dma_sconfig.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
		dma_sconfig.dst_maxburst = 16;
		tup->tx_dma_chan = dma_chan;
		tup->tx_dma_buf_virt = dma_buf;
		tup->tx_dma_buf_phys = dma_phys;
	पूर्ण

	ret = dmaengine_slave_config(dma_chan, &dma_sconfig);
	अगर (ret < 0) अणु
		dev_err(tup->uport.dev,
			"Dma slave config failed, err = %d\n", ret);
		tegra_uart_dma_channel_मुक्त(tup, dma_to_memory);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_uart_startup(काष्ठा uart_port *u)
अणु
	काष्ठा tegra_uart_port *tup = to_tegra_uport(u);
	पूर्णांक ret;

	अगर (!tup->use_tx_pio) अणु
		ret = tegra_uart_dma_channel_allocate(tup, false);
		अगर (ret < 0) अणु
			dev_err(u->dev, "Tx Dma allocation failed, err = %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!tup->use_rx_pio) अणु
		ret = tegra_uart_dma_channel_allocate(tup, true);
		अगर (ret < 0) अणु
			dev_err(u->dev, "Rx Dma allocation failed, err = %d\n",
				ret);
			जाओ fail_rx_dma;
		पूर्ण
	पूर्ण

	ret = tegra_uart_hw_init(tup);
	अगर (ret < 0) अणु
		dev_err(u->dev, "Uart HW init failed, err = %d\n", ret);
		जाओ fail_hw_init;
	पूर्ण

	ret = request_irq(u->irq, tegra_uart_isr, 0,
				dev_name(u->dev), tup);
	अगर (ret < 0) अणु
		dev_err(u->dev, "Failed to register ISR for IRQ %d\n", u->irq);
		जाओ fail_hw_init;
	पूर्ण
	वापस 0;

fail_hw_init:
	अगर (!tup->use_rx_pio)
		tegra_uart_dma_channel_मुक्त(tup, true);
fail_rx_dma:
	अगर (!tup->use_tx_pio)
		tegra_uart_dma_channel_मुक्त(tup, false);
	वापस ret;
पूर्ण

/*
 * Flush any TX data submitted क्रम DMA and PIO. Called when the
 * TX circular buffer is reset.
 */
अटल व्योम tegra_uart_flush_buffer(काष्ठा uart_port *u)
अणु
	काष्ठा tegra_uart_port *tup = to_tegra_uport(u);

	tup->tx_bytes = 0;
	अगर (tup->tx_dma_chan)
		dmaengine_terminate_all(tup->tx_dma_chan);
पूर्ण

अटल व्योम tegra_uart_shutकरोwn(काष्ठा uart_port *u)
अणु
	काष्ठा tegra_uart_port *tup = to_tegra_uport(u);

	tegra_uart_hw_deinit(tup);
	मुक्त_irq(u->irq, tup);
पूर्ण

अटल व्योम tegra_uart_enable_ms(काष्ठा uart_port *u)
अणु
	काष्ठा tegra_uart_port *tup = to_tegra_uport(u);

	अगर (tup->enable_modem_पूर्णांकerrupt) अणु
		tup->ier_shaकरोw |= UART_IER_MSI;
		tegra_uart_ग_लिखो(tup, tup->ier_shaकरोw, UART_IER);
	पूर्ण
पूर्ण

अटल व्योम tegra_uart_set_termios(काष्ठा uart_port *u,
		काष्ठा ktermios *termios, काष्ठा ktermios *oldtermios)
अणु
	काष्ठा tegra_uart_port *tup = to_tegra_uport(u);
	अचिन्हित पूर्णांक baud;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक lcr;
	पूर्णांक symb_bit = 1;
	काष्ठा clk *parent_clk = clk_get_parent(tup->uart_clk);
	अचिन्हित दीर्घ parent_clk_rate = clk_get_rate(parent_clk);
	पूर्णांक max_भागider = (tup->cdata->support_clk_src_भाग) ? 0x7FFF : 0xFFFF;
	पूर्णांक ret;

	max_भागider *= 16;
	spin_lock_irqsave(&u->lock, flags);

	/* Changing configuration, it is safe to stop any rx now */
	अगर (tup->rts_active)
		set_rts(tup, false);

	/* Clear all पूर्णांकerrupts as configuration is going to be changed */
	tegra_uart_ग_लिखो(tup, tup->ier_shaकरोw | UART_IER_RDI, UART_IER);
	tegra_uart_पढ़ो(tup, UART_IER);
	tegra_uart_ग_लिखो(tup, 0, UART_IER);
	tegra_uart_पढ़ो(tup, UART_IER);

	/* Parity */
	lcr = tup->lcr_shaकरोw;
	lcr &= ~UART_LCR_PARITY;

	/* CMSPAR isn't supported by this driver */
	termios->c_cflag &= ~CMSPAR;

	अगर ((termios->c_cflag & PARENB) == PARENB) अणु
		symb_bit++;
		अगर (termios->c_cflag & PARODD) अणु
			lcr |= UART_LCR_PARITY;
			lcr &= ~UART_LCR_EPAR;
			lcr &= ~UART_LCR_SPAR;
		पूर्ण अन्यथा अणु
			lcr |= UART_LCR_PARITY;
			lcr |= UART_LCR_EPAR;
			lcr &= ~UART_LCR_SPAR;
		पूर्ण
	पूर्ण

	lcr &= ~UART_LCR_WLEN8;
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		lcr |= UART_LCR_WLEN5;
		symb_bit += 5;
		अवरोध;
	हाल CS6:
		lcr |= UART_LCR_WLEN6;
		symb_bit += 6;
		अवरोध;
	हाल CS7:
		lcr |= UART_LCR_WLEN7;
		symb_bit += 7;
		अवरोध;
	शेष:
		lcr |= UART_LCR_WLEN8;
		symb_bit += 8;
		अवरोध;
	पूर्ण

	/* Stop bits */
	अगर (termios->c_cflag & CSTOPB) अणु
		lcr |= UART_LCR_STOP;
		symb_bit += 2;
	पूर्ण अन्यथा अणु
		lcr &= ~UART_LCR_STOP;
		symb_bit++;
	पूर्ण

	tegra_uart_ग_लिखो(tup, lcr, UART_LCR);
	tup->lcr_shaकरोw = lcr;
	tup->symb_bit = symb_bit;

	/* Baud rate. */
	baud = uart_get_baud_rate(u, termios, oldtermios,
			parent_clk_rate/max_भागider,
			parent_clk_rate/16);
	spin_unlock_irqrestore(&u->lock, flags);
	ret = tegra_set_baudrate(tup, baud);
	अगर (ret < 0) अणु
		dev_err(tup->uport.dev, "Failed to set baud rate\n");
		वापस;
	पूर्ण
	अगर (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);
	spin_lock_irqsave(&u->lock, flags);

	/* Flow control */
	अगर (termios->c_cflag & CRTSCTS)	अणु
		tup->mcr_shaकरोw |= TEGRA_UART_MCR_CTS_EN;
		tup->mcr_shaकरोw &= ~TEGRA_UART_MCR_RTS_EN;
		tegra_uart_ग_लिखो(tup, tup->mcr_shaकरोw, UART_MCR);
		/* अगर top layer has asked to set rts active then करो so here */
		अगर (tup->rts_active)
			set_rts(tup, true);
	पूर्ण अन्यथा अणु
		tup->mcr_shaकरोw &= ~TEGRA_UART_MCR_CTS_EN;
		tup->mcr_shaकरोw &= ~TEGRA_UART_MCR_RTS_EN;
		tegra_uart_ग_लिखो(tup, tup->mcr_shaकरोw, UART_MCR);
	पूर्ण

	/* update the port समयout based on new settings */
	uart_update_समयout(u, termios->c_cflag, baud);

	/* Make sure all ग_लिखोs have completed */
	tegra_uart_पढ़ो(tup, UART_IER);

	/* Re-enable पूर्णांकerrupt */
	tegra_uart_ग_लिखो(tup, tup->ier_shaकरोw, UART_IER);
	tegra_uart_पढ़ो(tup, UART_IER);

	tup->uport.ignore_status_mask = 0;
	/* Ignore all अक्षरacters अगर CREAD is not set */
	अगर ((termios->c_cflag & CREAD) == 0)
		tup->uport.ignore_status_mask |= UART_LSR_DR;
	अगर (termios->c_अगरlag & IGNBRK)
		tup->uport.ignore_status_mask |= UART_LSR_BI;

	spin_unlock_irqrestore(&u->lock, flags);
पूर्ण

अटल स्थिर अक्षर *tegra_uart_type(काष्ठा uart_port *u)
अणु
	वापस TEGRA_UART_TYPE;
पूर्ण

अटल स्थिर काष्ठा uart_ops tegra_uart_ops = अणु
	.tx_empty	= tegra_uart_tx_empty,
	.set_mctrl	= tegra_uart_set_mctrl,
	.get_mctrl	= tegra_uart_get_mctrl,
	.stop_tx	= tegra_uart_stop_tx,
	.start_tx	= tegra_uart_start_tx,
	.stop_rx	= tegra_uart_stop_rx,
	.flush_buffer	= tegra_uart_flush_buffer,
	.enable_ms	= tegra_uart_enable_ms,
	.अवरोध_ctl	= tegra_uart_अवरोध_ctl,
	.startup	= tegra_uart_startup,
	.shutकरोwn	= tegra_uart_shutकरोwn,
	.set_termios	= tegra_uart_set_termios,
	.type		= tegra_uart_type,
	.request_port	= tegra_uart_request_port,
	.release_port	= tegra_uart_release_port,
पूर्ण;

अटल काष्ठा uart_driver tegra_uart_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "tegra_hsuart",
	.dev_name	= "ttyTHS",
	.cons		= शून्य,
	.nr		= TEGRA_UART_MAXIMUM,
पूर्ण;

अटल पूर्णांक tegra_uart_parse_dt(काष्ठा platक्रमm_device *pdev,
	काष्ठा tegra_uart_port *tup)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक port;
	पूर्णांक ret;
	पूर्णांक index;
	u32 pval;
	पूर्णांक count;
	पूर्णांक n_entries;

	port = of_alias_get_id(np, "serial");
	अगर (port < 0) अणु
		dev_err(&pdev->dev, "failed to get alias id, errno %d\n", port);
		वापस port;
	पूर्ण
	tup->uport.line = port;

	tup->enable_modem_पूर्णांकerrupt = of_property_पढ़ो_bool(np,
					"nvidia,enable-modem-interrupt");

	index = of_property_match_string(np, "dma-names", "rx");
	अगर (index < 0) अणु
		tup->use_rx_pio = true;
		dev_info(&pdev->dev, "RX in PIO mode\n");
	पूर्ण
	index = of_property_match_string(np, "dma-names", "tx");
	अगर (index < 0) अणु
		tup->use_tx_pio = true;
		dev_info(&pdev->dev, "TX in PIO mode\n");
	पूर्ण

	n_entries = of_property_count_u32_elems(np, "nvidia,adjust-baud-rates");
	अगर (n_entries > 0) अणु
		tup->n_adjustable_baud_rates = n_entries / 3;
		tup->baud_tolerance =
		devm_kzalloc(&pdev->dev, (tup->n_adjustable_baud_rates) *
			     माप(*tup->baud_tolerance), GFP_KERNEL);
		अगर (!tup->baud_tolerance)
			वापस -ENOMEM;
		क्रम (count = 0, index = 0; count < n_entries; count += 3,
		     index++) अणु
			ret =
			of_property_पढ़ो_u32_index(np,
						   "nvidia,adjust-baud-rates",
						   count, &pval);
			अगर (!ret)
				tup->baud_tolerance[index].lower_range_baud =
				pval;
			ret =
			of_property_पढ़ो_u32_index(np,
						   "nvidia,adjust-baud-rates",
						   count + 1, &pval);
			अगर (!ret)
				tup->baud_tolerance[index].upper_range_baud =
				pval;
			ret =
			of_property_पढ़ो_u32_index(np,
						   "nvidia,adjust-baud-rates",
						   count + 2, &pval);
			अगर (!ret)
				tup->baud_tolerance[index].tolerance =
				(s32)pval;
		पूर्ण
	पूर्ण अन्यथा अणु
		tup->n_adjustable_baud_rates = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा tegra_uart_chip_data tegra20_uart_chip_data = अणु
	.tx_fअगरo_full_status		= false,
	.allow_txfअगरo_reset_fअगरo_mode	= true,
	.support_clk_src_भाग		= false,
	.fअगरo_mode_enable_status	= false,
	.uart_max_port			= 5,
	.max_dma_burst_bytes		= 4,
	.error_tolerance_low_range	= 0,
	.error_tolerance_high_range	= 4,
पूर्ण;

अटल काष्ठा tegra_uart_chip_data tegra30_uart_chip_data = अणु
	.tx_fअगरo_full_status		= true,
	.allow_txfअगरo_reset_fअगरo_mode	= false,
	.support_clk_src_भाग		= true,
	.fअगरo_mode_enable_status	= false,
	.uart_max_port			= 5,
	.max_dma_burst_bytes		= 4,
	.error_tolerance_low_range	= 0,
	.error_tolerance_high_range	= 4,
पूर्ण;

अटल काष्ठा tegra_uart_chip_data tegra186_uart_chip_data = अणु
	.tx_fअगरo_full_status		= true,
	.allow_txfअगरo_reset_fअगरo_mode	= false,
	.support_clk_src_भाग		= true,
	.fअगरo_mode_enable_status	= true,
	.uart_max_port			= 8,
	.max_dma_burst_bytes		= 8,
	.error_tolerance_low_range	= 0,
	.error_tolerance_high_range	= 4,
पूर्ण;

अटल काष्ठा tegra_uart_chip_data tegra194_uart_chip_data = अणु
	.tx_fअगरo_full_status		= true,
	.allow_txfअगरo_reset_fअगरo_mode	= false,
	.support_clk_src_भाग		= true,
	.fअगरo_mode_enable_status	= true,
	.uart_max_port			= 8,
	.max_dma_burst_bytes		= 8,
	.error_tolerance_low_range	= -2,
	.error_tolerance_high_range	= 2,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_uart_of_match[] = अणु
	अणु
		.compatible	= "nvidia,tegra30-hsuart",
		.data		= &tegra30_uart_chip_data,
	पूर्ण, अणु
		.compatible	= "nvidia,tegra20-hsuart",
		.data		= &tegra20_uart_chip_data,
	पूर्ण, अणु
		.compatible     = "nvidia,tegra186-hsuart",
		.data		= &tegra186_uart_chip_data,
	पूर्ण, अणु
		.compatible     = "nvidia,tegra194-hsuart",
		.data		= &tegra194_uart_chip_data,
	पूर्ण, अणु
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_uart_of_match);

अटल पूर्णांक tegra_uart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_uart_port *tup;
	काष्ठा uart_port *u;
	काष्ठा resource *resource;
	पूर्णांक ret;
	स्थिर काष्ठा tegra_uart_chip_data *cdata;
	स्थिर काष्ठा of_device_id *match;

	match = of_match_device(tegra_uart_of_match, &pdev->dev);
	अगर (!match) अणु
		dev_err(&pdev->dev, "Error: No device match found\n");
		वापस -ENODEV;
	पूर्ण
	cdata = match->data;

	tup = devm_kzalloc(&pdev->dev, माप(*tup), GFP_KERNEL);
	अगर (!tup) अणु
		dev_err(&pdev->dev, "Failed to allocate memory for tup\n");
		वापस -ENOMEM;
	पूर्ण

	ret = tegra_uart_parse_dt(pdev, tup);
	अगर (ret < 0)
		वापस ret;

	u = &tup->uport;
	u->dev = &pdev->dev;
	u->ops = &tegra_uart_ops;
	u->type = PORT_TEGRA;
	u->fअगरosize = 32;
	tup->cdata = cdata;

	platक्रमm_set_drvdata(pdev, tup);
	resource = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!resource) अणु
		dev_err(&pdev->dev, "No IO memory resource\n");
		वापस -ENODEV;
	पूर्ण

	u->mapbase = resource->start;
	u->membase = devm_ioremap_resource(&pdev->dev, resource);
	अगर (IS_ERR(u->membase))
		वापस PTR_ERR(u->membase);

	tup->uart_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(tup->uart_clk)) अणु
		dev_err(&pdev->dev, "Couldn't get the clock\n");
		वापस PTR_ERR(tup->uart_clk);
	पूर्ण

	tup->rst = devm_reset_control_get_exclusive(&pdev->dev, "serial");
	अगर (IS_ERR(tup->rst)) अणु
		dev_err(&pdev->dev, "Couldn't get the reset\n");
		वापस PTR_ERR(tup->rst);
	पूर्ण

	u->iotype = UPIO_MEM32;
	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		वापस ret;
	u->irq = ret;
	u->regshअगरt = 2;
	ret = uart_add_one_port(&tegra_uart_driver, u);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to add uart port, err %d\n", ret);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_uart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_uart_port *tup = platक्रमm_get_drvdata(pdev);
	काष्ठा uart_port *u = &tup->uport;

	uart_हटाओ_one_port(&tegra_uart_driver, u);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tegra_uart_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_uart_port *tup = dev_get_drvdata(dev);
	काष्ठा uart_port *u = &tup->uport;

	वापस uart_suspend_port(&tegra_uart_driver, u);
पूर्ण

अटल पूर्णांक tegra_uart_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_uart_port *tup = dev_get_drvdata(dev);
	काष्ठा uart_port *u = &tup->uport;

	वापस uart_resume_port(&tegra_uart_driver, u);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops tegra_uart_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(tegra_uart_suspend, tegra_uart_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_uart_platक्रमm_driver = अणु
	.probe		= tegra_uart_probe,
	.हटाओ		= tegra_uart_हटाओ,
	.driver		= अणु
		.name	= "serial-tegra",
		.of_match_table = tegra_uart_of_match,
		.pm	= &tegra_uart_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init tegra_uart_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा device_node *node;
	स्थिर काष्ठा of_device_id *match = शून्य;
	स्थिर काष्ठा tegra_uart_chip_data *cdata = शून्य;

	node = of_find_matching_node(शून्य, tegra_uart_of_match);
	अगर (node)
		match = of_match_node(tegra_uart_of_match, node);
	अगर (match)
		cdata = match->data;
	अगर (cdata)
		tegra_uart_driver.nr = cdata->uart_max_port;

	ret = uart_रेजिस्टर_driver(&tegra_uart_driver);
	अगर (ret < 0) अणु
		pr_err("Could not register %s driver\n",
		       tegra_uart_driver.driver_name);
		वापस ret;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&tegra_uart_platक्रमm_driver);
	अगर (ret < 0) अणु
		pr_err("Uart platform driver register failed, e = %d\n", ret);
		uart_unरेजिस्टर_driver(&tegra_uart_driver);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास tegra_uart_निकास(व्योम)
अणु
	pr_info("Unloading tegra uart driver\n");
	platक्रमm_driver_unरेजिस्टर(&tegra_uart_platक्रमm_driver);
	uart_unरेजिस्टर_driver(&tegra_uart_driver);
पूर्ण

module_init(tegra_uart_init);
module_निकास(tegra_uart_निकास);

MODULE_ALIAS("platform:serial-tegra");
MODULE_DESCRIPTION("High speed UART driver for tegra chipset");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_LICENSE("GPL v2");
