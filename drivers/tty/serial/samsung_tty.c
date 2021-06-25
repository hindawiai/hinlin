<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver core क्रम Samsung SoC onboard UARTs.
 *
 * Ben Dooks, Copyright (c) 2003-2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 */

/* Note on 2410 error handling
 *
 * The s3c2410 manual has a love/hate affair with the contents of the
 * UERSTAT रेजिस्टर in the UART blocks, and keeps marking some of the
 * error bits as reserved. Having checked with the s3c2410x01,
 * it copes with BREAKs properly, so I am happy to ignore the RESERVED
 * feature from the latter versions of the manual.
 *
 * If it becomes aparrent that latter versions of the 2410 हटाओ these
 * bits, then action will have to be taken to dअगरferentiate the versions
 * and change the policy on BREAK
 *
 * BJD, 04-Nov-2004
 */

#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/console.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/irq.h>

/* UART name and device definitions */

#घोषणा S3C24XX_SERIAL_NAME	"ttySAC"
#घोषणा S3C24XX_SERIAL_MAJOR	204
#घोषणा S3C24XX_SERIAL_MINOR	64

#घोषणा S3C24XX_TX_PIO			1
#घोषणा S3C24XX_TX_DMA			2
#घोषणा S3C24XX_RX_PIO			1
#घोषणा S3C24XX_RX_DMA			2

/* flag to ignore all अक्षरacters coming in */
#घोषणा RXSTAT_DUMMY_READ (0x10000000)

क्रमागत s3c24xx_port_type अणु
	TYPE_S3C24XX,
	TYPE_S3C6400,
	TYPE_APPLE_S5L,
पूर्ण;

काष्ठा s3c24xx_uart_info अणु
	अक्षर			*name;
	क्रमागत s3c24xx_port_type	type;
	अचिन्हित पूर्णांक		port_type;
	अचिन्हित पूर्णांक		fअगरosize;
	अचिन्हित दीर्घ		rx_fअगरomask;
	अचिन्हित दीर्घ		rx_fअगरoshअगरt;
	अचिन्हित दीर्घ		rx_fअगरofull;
	अचिन्हित दीर्घ		tx_fअगरomask;
	अचिन्हित दीर्घ		tx_fअगरoshअगरt;
	अचिन्हित दीर्घ		tx_fअगरofull;
	अचिन्हित पूर्णांक		def_clk_sel;
	अचिन्हित दीर्घ		num_clks;
	अचिन्हित दीर्घ		clksel_mask;
	अचिन्हित दीर्घ		clksel_shअगरt;
	अचिन्हित दीर्घ		ucon_mask;

	/* uart port features */

	अचिन्हित पूर्णांक		has_भागslot:1;
पूर्ण;

काष्ठा s3c24xx_serial_drv_data अणु
	काष्ठा s3c24xx_uart_info	*info;
	काष्ठा s3c2410_uartcfg		*def_cfg;
	अचिन्हित पूर्णांक			fअगरosize[CONFIG_SERIAL_SAMSUNG_UARTS];
पूर्ण;

काष्ठा s3c24xx_uart_dma अणु
	अचिन्हित पूर्णांक			rx_chan_id;
	अचिन्हित पूर्णांक			tx_chan_id;

	काष्ठा dma_slave_config		rx_conf;
	काष्ठा dma_slave_config		tx_conf;

	काष्ठा dma_chan			*rx_chan;
	काष्ठा dma_chan			*tx_chan;

	dma_addr_t			rx_addr;
	dma_addr_t			tx_addr;

	dma_cookie_t			rx_cookie;
	dma_cookie_t			tx_cookie;

	अक्षर				*rx_buf;

	dma_addr_t			tx_transfer_addr;

	माप_प्रकार				rx_size;
	माप_प्रकार				tx_size;

	काष्ठा dma_async_tx_descriptor	*tx_desc;
	काष्ठा dma_async_tx_descriptor	*rx_desc;

	पूर्णांक				tx_bytes_requested;
	पूर्णांक				rx_bytes_requested;
पूर्ण;

काष्ठा s3c24xx_uart_port अणु
	अचिन्हित अक्षर			rx_claimed;
	अचिन्हित अक्षर			tx_claimed;
	अचिन्हित अक्षर			rx_enabled;
	अचिन्हित अक्षर			tx_enabled;
	अचिन्हित पूर्णांक			pm_level;
	अचिन्हित दीर्घ			baudclk_rate;
	अचिन्हित पूर्णांक			min_dma_size;

	अचिन्हित पूर्णांक			rx_irq;
	अचिन्हित पूर्णांक			tx_irq;

	अचिन्हित पूर्णांक			tx_in_progress;
	अचिन्हित पूर्णांक			tx_mode;
	अचिन्हित पूर्णांक			rx_mode;

	काष्ठा s3c24xx_uart_info	*info;
	काष्ठा clk			*clk;
	काष्ठा clk			*baudclk;
	काष्ठा uart_port		port;
	काष्ठा s3c24xx_serial_drv_data	*drv_data;

	/* reference to platक्रमm data */
	काष्ठा s3c2410_uartcfg		*cfg;

	काष्ठा s3c24xx_uart_dma		*dma;

#अगर_घोषित CONFIG_ARM_S3C24XX_CPUFREQ
	काष्ठा notअगरier_block		freq_transition;
#पूर्ण_अगर
पूर्ण;

अटल व्योम s3c24xx_serial_tx_अक्षरs(काष्ठा s3c24xx_uart_port *ourport);

/* conversion functions */

#घोषणा s3c24xx_dev_to_port(__dev) dev_get_drvdata(__dev)

/* रेजिस्टर access controls */

#घोषणा portaddr(port, reg) ((port)->membase + (reg))
#घोषणा portaddrl(port, reg) \
	((अचिन्हित दीर्घ *)(अचिन्हित दीर्घ)((port)->membase + (reg)))

अटल u32 rd_reg(काष्ठा uart_port *port, u32 reg)
अणु
	चयन (port->iotype) अणु
	हाल UPIO_MEM:
		वापस पढ़ोb_relaxed(portaddr(port, reg));
	हाल UPIO_MEM32:
		वापस पढ़ोl_relaxed(portaddr(port, reg));
	शेष:
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा rd_regl(port, reg) (पढ़ोl_relaxed(portaddr(port, reg)))

अटल व्योम wr_reg(काष्ठा uart_port *port, u32 reg, u32 val)
अणु
	चयन (port->iotype) अणु
	हाल UPIO_MEM:
		ग_लिखोb_relaxed(val, portaddr(port, reg));
		अवरोध;
	हाल UPIO_MEM32:
		ग_लिखोl_relaxed(val, portaddr(port, reg));
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा wr_regl(port, reg, val) ग_लिखोl_relaxed(val, portaddr(port, reg))

/* Byte-order aware bit setting/clearing functions. */

अटल अंतरभूत व्योम s3c24xx_set_bit(काष्ठा uart_port *port, पूर्णांक idx,
				   अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	local_irq_save(flags);
	val = rd_regl(port, reg);
	val |= (1 << idx);
	wr_regl(port, reg, val);
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम s3c24xx_clear_bit(काष्ठा uart_port *port, पूर्णांक idx,
				     अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	local_irq_save(flags);
	val = rd_regl(port, reg);
	val &= ~(1 << idx);
	wr_regl(port, reg, val);
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत काष्ठा s3c24xx_uart_port *to_ourport(काष्ठा uart_port *port)
अणु
	वापस container_of(port, काष्ठा s3c24xx_uart_port, port);
पूर्ण

/* translate a port to the device name */

अटल अंतरभूत स्थिर अक्षर *s3c24xx_serial_portname(काष्ठा uart_port *port)
अणु
	वापस to_platक्रमm_device(port->dev)->name;
पूर्ण

अटल पूर्णांक s3c24xx_serial_txempty_nofअगरo(काष्ठा uart_port *port)
अणु
	वापस rd_regl(port, S3C2410_UTRSTAT) & S3C2410_UTRSTAT_TXE;
पूर्ण

अटल व्योम s3c24xx_serial_rx_enable(काष्ठा uart_port *port)
अणु
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ucon, ufcon;
	पूर्णांक count = 10000;

	spin_lock_irqsave(&port->lock, flags);

	जबतक (--count && !s3c24xx_serial_txempty_nofअगरo(port))
		udelay(100);

	ufcon = rd_regl(port, S3C2410_UFCON);
	ufcon |= S3C2410_UFCON_RESETRX;
	wr_regl(port, S3C2410_UFCON, ufcon);

	ucon = rd_regl(port, S3C2410_UCON);
	ucon |= S3C2410_UCON_RXIRQMODE;
	wr_regl(port, S3C2410_UCON, ucon);

	ourport->rx_enabled = 1;
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम s3c24xx_serial_rx_disable(काष्ठा uart_port *port)
अणु
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ucon;

	spin_lock_irqsave(&port->lock, flags);

	ucon = rd_regl(port, S3C2410_UCON);
	ucon &= ~S3C2410_UCON_RXIRQMODE;
	wr_regl(port, S3C2410_UCON, ucon);

	ourport->rx_enabled = 0;
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम s3c24xx_serial_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);
	काष्ठा s3c24xx_uart_dma *dma = ourport->dma;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	काष्ठा dma_tx_state state;
	पूर्णांक count;

	अगर (!ourport->tx_enabled)
		वापस;

	चयन (ourport->info->type) अणु
	हाल TYPE_S3C6400:
		s3c24xx_set_bit(port, S3C64XX_UINTM_TXD, S3C64XX_UINTM);
		अवरोध;
	हाल TYPE_APPLE_S5L:
		s3c24xx_clear_bit(port, APPLE_S5L_UCON_TXTHRESH_ENA, S3C2410_UCON);
		अवरोध;
	शेष:
		disable_irq_nosync(ourport->tx_irq);
		अवरोध;
	पूर्ण

	अगर (dma && dma->tx_chan && ourport->tx_in_progress == S3C24XX_TX_DMA) अणु
		dmaengine_छोड़ो(dma->tx_chan);
		dmaengine_tx_status(dma->tx_chan, dma->tx_cookie, &state);
		dmaengine_terminate_all(dma->tx_chan);
		dma_sync_single_क्रम_cpu(ourport->port.dev,
			dma->tx_transfer_addr, dma->tx_size, DMA_TO_DEVICE);
		async_tx_ack(dma->tx_desc);
		count = dma->tx_bytes_requested - state.residue;
		xmit->tail = (xmit->tail + count) & (UART_XMIT_SIZE - 1);
		port->icount.tx += count;
	पूर्ण

	ourport->tx_enabled = 0;
	ourport->tx_in_progress = 0;

	अगर (port->flags & UPF_CONS_FLOW)
		s3c24xx_serial_rx_enable(port);

	ourport->tx_mode = 0;
पूर्ण

अटल व्योम s3c24xx_serial_start_next_tx(काष्ठा s3c24xx_uart_port *ourport);

अटल व्योम s3c24xx_serial_tx_dma_complete(व्योम *args)
अणु
	काष्ठा s3c24xx_uart_port *ourport = args;
	काष्ठा uart_port *port = &ourport->port;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	काष्ठा s3c24xx_uart_dma *dma = ourport->dma;
	काष्ठा dma_tx_state state;
	अचिन्हित दीर्घ flags;
	पूर्णांक count;

	dmaengine_tx_status(dma->tx_chan, dma->tx_cookie, &state);
	count = dma->tx_bytes_requested - state.residue;
	async_tx_ack(dma->tx_desc);

	dma_sync_single_क्रम_cpu(ourport->port.dev, dma->tx_transfer_addr,
				dma->tx_size, DMA_TO_DEVICE);

	spin_lock_irqsave(&port->lock, flags);

	xmit->tail = (xmit->tail + count) & (UART_XMIT_SIZE - 1);
	port->icount.tx += count;
	ourport->tx_in_progress = 0;

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	s3c24xx_serial_start_next_tx(ourport);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम enable_tx_dma(काष्ठा s3c24xx_uart_port *ourport)
अणु
	काष्ठा uart_port *port = &ourport->port;
	u32 ucon;

	/* Mask Tx पूर्णांकerrupt */
	चयन (ourport->info->type) अणु
	हाल TYPE_S3C6400:
		s3c24xx_set_bit(port, S3C64XX_UINTM_TXD, S3C64XX_UINTM);
		अवरोध;
	हाल TYPE_APPLE_S5L:
		WARN_ON(1); // No DMA
		अवरोध;
	शेष:
		disable_irq_nosync(ourport->tx_irq);
		अवरोध;
	पूर्ण

	/* Enable tx dma mode */
	ucon = rd_regl(port, S3C2410_UCON);
	ucon &= ~(S3C64XX_UCON_TXBURST_MASK | S3C64XX_UCON_TXMODE_MASK);
	ucon |= (dma_get_cache_alignment() >= 16) ?
		S3C64XX_UCON_TXBURST_16 : S3C64XX_UCON_TXBURST_1;
	ucon |= S3C64XX_UCON_TXMODE_DMA;
	wr_regl(port,  S3C2410_UCON, ucon);

	ourport->tx_mode = S3C24XX_TX_DMA;
पूर्ण

अटल व्योम enable_tx_pio(काष्ठा s3c24xx_uart_port *ourport)
अणु
	काष्ठा uart_port *port = &ourport->port;
	u32 ucon, ufcon;

	/* Set ufcon txtrig */
	ourport->tx_in_progress = S3C24XX_TX_PIO;
	ufcon = rd_regl(port, S3C2410_UFCON);
	wr_regl(port,  S3C2410_UFCON, ufcon);

	/* Enable tx pio mode */
	ucon = rd_regl(port, S3C2410_UCON);
	ucon &= ~(S3C64XX_UCON_TXMODE_MASK);
	ucon |= S3C64XX_UCON_TXMODE_CPU;
	wr_regl(port,  S3C2410_UCON, ucon);

	/* Unmask Tx पूर्णांकerrupt */
	चयन (ourport->info->type) अणु
	हाल TYPE_S3C6400:
		s3c24xx_clear_bit(port, S3C64XX_UINTM_TXD,
				  S3C64XX_UINTM);
		अवरोध;
	हाल TYPE_APPLE_S5L:
		ucon |= APPLE_S5L_UCON_TXTHRESH_ENA_MSK;
		wr_regl(port, S3C2410_UCON, ucon);
		अवरोध;
	शेष:
		enable_irq(ourport->tx_irq);
		अवरोध;
	पूर्ण

	ourport->tx_mode = S3C24XX_TX_PIO;

	/*
	 * The Apple version only has edge triggered TX IRQs, so we need
	 * to kick off the process by sending some अक्षरacters here.
	 */
	अगर (ourport->info->type == TYPE_APPLE_S5L)
		s3c24xx_serial_tx_अक्षरs(ourport);
पूर्ण

अटल व्योम s3c24xx_serial_start_tx_pio(काष्ठा s3c24xx_uart_port *ourport)
अणु
	अगर (ourport->tx_mode != S3C24XX_TX_PIO)
		enable_tx_pio(ourport);
पूर्ण

अटल पूर्णांक s3c24xx_serial_start_tx_dma(काष्ठा s3c24xx_uart_port *ourport,
				      अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_port *port = &ourport->port;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	काष्ठा s3c24xx_uart_dma *dma = ourport->dma;

	अगर (ourport->tx_mode != S3C24XX_TX_DMA)
		enable_tx_dma(ourport);

	dma->tx_size = count & ~(dma_get_cache_alignment() - 1);
	dma->tx_transfer_addr = dma->tx_addr + xmit->tail;

	dma_sync_single_क्रम_device(ourport->port.dev, dma->tx_transfer_addr,
				dma->tx_size, DMA_TO_DEVICE);

	dma->tx_desc = dmaengine_prep_slave_single(dma->tx_chan,
				dma->tx_transfer_addr, dma->tx_size,
				DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT);
	अगर (!dma->tx_desc) अणु
		dev_err(ourport->port.dev, "Unable to get desc for Tx\n");
		वापस -EIO;
	पूर्ण

	dma->tx_desc->callback = s3c24xx_serial_tx_dma_complete;
	dma->tx_desc->callback_param = ourport;
	dma->tx_bytes_requested = dma->tx_size;

	ourport->tx_in_progress = S3C24XX_TX_DMA;
	dma->tx_cookie = dmaengine_submit(dma->tx_desc);
	dma_async_issue_pending(dma->tx_chan);
	वापस 0;
पूर्ण

अटल व्योम s3c24xx_serial_start_next_tx(काष्ठा s3c24xx_uart_port *ourport)
अणु
	काष्ठा uart_port *port = &ourport->port;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित दीर्घ count;

	/* Get data size up to the end of buffer */
	count = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);

	अगर (!count) अणु
		s3c24xx_serial_stop_tx(port);
		वापस;
	पूर्ण

	अगर (!ourport->dma || !ourport->dma->tx_chan ||
	    count < ourport->min_dma_size ||
	    xmit->tail & (dma_get_cache_alignment() - 1))
		s3c24xx_serial_start_tx_pio(ourport);
	अन्यथा
		s3c24xx_serial_start_tx_dma(ourport, count);
पूर्ण

अटल व्योम s3c24xx_serial_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);
	काष्ठा circ_buf *xmit = &port->state->xmit;

	अगर (!ourport->tx_enabled) अणु
		अगर (port->flags & UPF_CONS_FLOW)
			s3c24xx_serial_rx_disable(port);

		ourport->tx_enabled = 1;
		अगर (!ourport->dma || !ourport->dma->tx_chan)
			s3c24xx_serial_start_tx_pio(ourport);
	पूर्ण

	अगर (ourport->dma && ourport->dma->tx_chan) अणु
		अगर (!uart_circ_empty(xmit) && !ourport->tx_in_progress)
			s3c24xx_serial_start_next_tx(ourport);
	पूर्ण
पूर्ण

अटल व्योम s3c24xx_uart_copy_rx_to_tty(काष्ठा s3c24xx_uart_port *ourport,
		काष्ठा tty_port *tty, पूर्णांक count)
अणु
	काष्ठा s3c24xx_uart_dma *dma = ourport->dma;
	पूर्णांक copied;

	अगर (!count)
		वापस;

	dma_sync_single_क्रम_cpu(ourport->port.dev, dma->rx_addr,
				dma->rx_size, DMA_FROM_DEVICE);

	ourport->port.icount.rx += count;
	अगर (!tty) अणु
		dev_err(ourport->port.dev, "No tty port\n");
		वापस;
	पूर्ण
	copied = tty_insert_flip_string(tty,
			((अचिन्हित अक्षर *)(ourport->dma->rx_buf)), count);
	अगर (copied != count) अणु
		WARN_ON(1);
		dev_err(ourport->port.dev, "RxData copy to tty layer failed\n");
	पूर्ण
पूर्ण

अटल व्योम s3c24xx_serial_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);
	काष्ठा s3c24xx_uart_dma *dma = ourport->dma;
	काष्ठा tty_port *t = &port->state->port;
	काष्ठा dma_tx_state state;
	क्रमागत dma_status dma_status;
	अचिन्हित पूर्णांक received;

	अगर (ourport->rx_enabled) अणु
		dev_dbg(port->dev, "stopping rx\n");
		चयन (ourport->info->type) अणु
		हाल TYPE_S3C6400:
			s3c24xx_set_bit(port, S3C64XX_UINTM_RXD,
					S3C64XX_UINTM);
			अवरोध;
		हाल TYPE_APPLE_S5L:
			s3c24xx_clear_bit(port, APPLE_S5L_UCON_RXTHRESH_ENA, S3C2410_UCON);
			s3c24xx_clear_bit(port, APPLE_S5L_UCON_RXTO_ENA, S3C2410_UCON);
			अवरोध;
		शेष:
			disable_irq_nosync(ourport->rx_irq);
			अवरोध;
		पूर्ण
		ourport->rx_enabled = 0;
	पूर्ण
	अगर (dma && dma->rx_chan) अणु
		dmaengine_छोड़ो(dma->tx_chan);
		dma_status = dmaengine_tx_status(dma->rx_chan,
				dma->rx_cookie, &state);
		अगर (dma_status == DMA_IN_PROGRESS ||
			dma_status == DMA_PAUSED) अणु
			received = dma->rx_bytes_requested - state.residue;
			dmaengine_terminate_all(dma->rx_chan);
			s3c24xx_uart_copy_rx_to_tty(ourport, t, received);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा s3c24xx_uart_info
	*s3c24xx_port_to_info(काष्ठा uart_port *port)
अणु
	वापस to_ourport(port)->info;
पूर्ण

अटल अंतरभूत काष्ठा s3c2410_uartcfg
	*s3c24xx_port_to_cfg(काष्ठा uart_port *port)
अणु
	काष्ठा s3c24xx_uart_port *ourport;

	अगर (port->dev == शून्य)
		वापस शून्य;

	ourport = container_of(port, काष्ठा s3c24xx_uart_port, port);
	वापस ourport->cfg;
पूर्ण

अटल पूर्णांक s3c24xx_serial_rx_fअगरocnt(काष्ठा s3c24xx_uart_port *ourport,
				     अचिन्हित दीर्घ uख_स्थिति)
अणु
	काष्ठा s3c24xx_uart_info *info = ourport->info;

	अगर (uख_स्थिति & info->rx_fअगरofull)
		वापस ourport->port.fअगरosize;

	वापस (uख_स्थिति & info->rx_fअगरomask) >> info->rx_fअगरoshअगरt;
पूर्ण

अटल व्योम s3c64xx_start_rx_dma(काष्ठा s3c24xx_uart_port *ourport);
अटल व्योम s3c24xx_serial_rx_dma_complete(व्योम *args)
अणु
	काष्ठा s3c24xx_uart_port *ourport = args;
	काष्ठा uart_port *port = &ourport->port;

	काष्ठा s3c24xx_uart_dma *dma = ourport->dma;
	काष्ठा tty_port *t = &port->state->port;
	काष्ठा tty_काष्ठा *tty = tty_port_tty_get(&ourport->port.state->port);

	काष्ठा dma_tx_state state;
	अचिन्हित दीर्घ flags;
	पूर्णांक received;

	dmaengine_tx_status(dma->rx_chan,  dma->rx_cookie, &state);
	received  = dma->rx_bytes_requested - state.residue;
	async_tx_ack(dma->rx_desc);

	spin_lock_irqsave(&port->lock, flags);

	अगर (received)
		s3c24xx_uart_copy_rx_to_tty(ourport, t, received);

	अगर (tty) अणु
		tty_flip_buffer_push(t);
		tty_kref_put(tty);
	पूर्ण

	s3c64xx_start_rx_dma(ourport);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम s3c64xx_start_rx_dma(काष्ठा s3c24xx_uart_port *ourport)
अणु
	काष्ठा s3c24xx_uart_dma *dma = ourport->dma;

	dma_sync_single_क्रम_device(ourport->port.dev, dma->rx_addr,
				dma->rx_size, DMA_FROM_DEVICE);

	dma->rx_desc = dmaengine_prep_slave_single(dma->rx_chan,
				dma->rx_addr, dma->rx_size, DMA_DEV_TO_MEM,
				DMA_PREP_INTERRUPT);
	अगर (!dma->rx_desc) अणु
		dev_err(ourport->port.dev, "Unable to get desc for Rx\n");
		वापस;
	पूर्ण

	dma->rx_desc->callback = s3c24xx_serial_rx_dma_complete;
	dma->rx_desc->callback_param = ourport;
	dma->rx_bytes_requested = dma->rx_size;

	dma->rx_cookie = dmaengine_submit(dma->rx_desc);
	dma_async_issue_pending(dma->rx_chan);
पूर्ण

/* ? - where has parity gone?? */
#घोषणा S3C2410_UERSTAT_PARITY (0x1000)

अटल व्योम enable_rx_dma(काष्ठा s3c24xx_uart_port *ourport)
अणु
	काष्ठा uart_port *port = &ourport->port;
	अचिन्हित पूर्णांक ucon;

	/* set Rx mode to DMA mode */
	ucon = rd_regl(port, S3C2410_UCON);
	ucon &= ~(S3C64XX_UCON_RXBURST_MASK |
			S3C64XX_UCON_TIMEOUT_MASK |
			S3C64XX_UCON_EMPTYINT_EN |
			S3C64XX_UCON_DMASUS_EN |
			S3C64XX_UCON_TIMEOUT_EN |
			S3C64XX_UCON_RXMODE_MASK);
	ucon |= S3C64XX_UCON_RXBURST_16 |
			0xf << S3C64XX_UCON_TIMEOUT_SHIFT |
			S3C64XX_UCON_EMPTYINT_EN |
			S3C64XX_UCON_TIMEOUT_EN |
			S3C64XX_UCON_RXMODE_DMA;
	wr_regl(port, S3C2410_UCON, ucon);

	ourport->rx_mode = S3C24XX_RX_DMA;
पूर्ण

अटल व्योम enable_rx_pio(काष्ठा s3c24xx_uart_port *ourport)
अणु
	काष्ठा uart_port *port = &ourport->port;
	अचिन्हित पूर्णांक ucon;

	/* set Rx mode to DMA mode */
	ucon = rd_regl(port, S3C2410_UCON);
	ucon &= ~S3C64XX_UCON_RXMODE_MASK;
	ucon |= S3C64XX_UCON_RXMODE_CPU;

	/* Apple types use these bits क्रम IRQ masks */
	अगर (ourport->info->type != TYPE_APPLE_S5L) अणु
		ucon &= ~(S3C64XX_UCON_TIMEOUT_MASK |
				S3C64XX_UCON_EMPTYINT_EN |
				S3C64XX_UCON_DMASUS_EN |
				S3C64XX_UCON_TIMEOUT_EN);
		ucon |= 0xf << S3C64XX_UCON_TIMEOUT_SHIFT |
				S3C64XX_UCON_TIMEOUT_EN;
	पूर्ण
	wr_regl(port, S3C2410_UCON, ucon);

	ourport->rx_mode = S3C24XX_RX_PIO;
पूर्ण

अटल व्योम s3c24xx_serial_rx_drain_fअगरo(काष्ठा s3c24xx_uart_port *ourport);

अटल irqवापस_t s3c24xx_serial_rx_अक्षरs_dma(व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक utrstat, received;
	काष्ठा s3c24xx_uart_port *ourport = dev_id;
	काष्ठा uart_port *port = &ourport->port;
	काष्ठा s3c24xx_uart_dma *dma = ourport->dma;
	काष्ठा tty_काष्ठा *tty = tty_port_tty_get(&ourport->port.state->port);
	काष्ठा tty_port *t = &port->state->port;
	काष्ठा dma_tx_state state;

	utrstat = rd_regl(port, S3C2410_UTRSTAT);
	rd_regl(port, S3C2410_UFSTAT);

	spin_lock(&port->lock);

	अगर (!(utrstat & S3C2410_UTRSTAT_TIMEOUT)) अणु
		s3c64xx_start_rx_dma(ourport);
		अगर (ourport->rx_mode == S3C24XX_RX_PIO)
			enable_rx_dma(ourport);
		जाओ finish;
	पूर्ण

	अगर (ourport->rx_mode == S3C24XX_RX_DMA) अणु
		dmaengine_छोड़ो(dma->rx_chan);
		dmaengine_tx_status(dma->rx_chan, dma->rx_cookie, &state);
		dmaengine_terminate_all(dma->rx_chan);
		received = dma->rx_bytes_requested - state.residue;
		s3c24xx_uart_copy_rx_to_tty(ourport, t, received);

		enable_rx_pio(ourport);
	पूर्ण

	s3c24xx_serial_rx_drain_fअगरo(ourport);

	अगर (tty) अणु
		tty_flip_buffer_push(t);
		tty_kref_put(tty);
	पूर्ण

	wr_regl(port, S3C2410_UTRSTAT, S3C2410_UTRSTAT_TIMEOUT);

finish:
	spin_unlock(&port->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम s3c24xx_serial_rx_drain_fअगरo(काष्ठा s3c24xx_uart_port *ourport)
अणु
	काष्ठा uart_port *port = &ourport->port;
	अचिन्हित पूर्णांक ufcon, ch, flag, uख_स्थिति, uerstat;
	अचिन्हित पूर्णांक fअगरocnt = 0;
	पूर्णांक max_count = port->fअगरosize;

	जबतक (max_count-- > 0) अणु
		/*
		 * Receive all अक्षरacters known to be in FIFO
		 * beक्रमe पढ़ोing FIFO level again
		 */
		अगर (fअगरocnt == 0) अणु
			uख_स्थिति = rd_regl(port, S3C2410_UFSTAT);
			fअगरocnt = s3c24xx_serial_rx_fअगरocnt(ourport, uख_स्थिति);
			अगर (fअगरocnt == 0)
				अवरोध;
		पूर्ण
		fअगरocnt--;

		uerstat = rd_regl(port, S3C2410_UERSTAT);
		ch = rd_reg(port, S3C2410_URXH);

		अगर (port->flags & UPF_CONS_FLOW) अणु
			पूर्णांक txe = s3c24xx_serial_txempty_nofअगरo(port);

			अगर (ourport->rx_enabled) अणु
				अगर (!txe) अणु
					ourport->rx_enabled = 0;
					जारी;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (txe) अणु
					ufcon = rd_regl(port, S3C2410_UFCON);
					ufcon |= S3C2410_UFCON_RESETRX;
					wr_regl(port, S3C2410_UFCON, ufcon);
					ourport->rx_enabled = 1;
					वापस;
				पूर्ण
				जारी;
			पूर्ण
		पूर्ण

		/* insert the अक्षरacter पूर्णांकo the buffer */

		flag = TTY_NORMAL;
		port->icount.rx++;

		अगर (unlikely(uerstat & S3C2410_UERSTAT_ANY)) अणु
			dev_dbg(port->dev,
				"rxerr: port ch=0x%02x, rxs=0x%08x\n",
				ch, uerstat);

			/* check क्रम अवरोध */
			अगर (uerstat & S3C2410_UERSTAT_BREAK) अणु
				dev_dbg(port->dev, "break!\n");
				port->icount.brk++;
				अगर (uart_handle_अवरोध(port))
					जारी; /* Ignore अक्षरacter */
			पूर्ण

			अगर (uerstat & S3C2410_UERSTAT_FRAME)
				port->icount.frame++;
			अगर (uerstat & S3C2410_UERSTAT_OVERRUN)
				port->icount.overrun++;

			uerstat &= port->पढ़ो_status_mask;

			अगर (uerstat & S3C2410_UERSTAT_BREAK)
				flag = TTY_BREAK;
			अन्यथा अगर (uerstat & S3C2410_UERSTAT_PARITY)
				flag = TTY_PARITY;
			अन्यथा अगर (uerstat & (S3C2410_UERSTAT_FRAME |
					    S3C2410_UERSTAT_OVERRUN))
				flag = TTY_FRAME;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(port, ch))
			जारी; /* Ignore अक्षरacter */

		uart_insert_अक्षर(port, uerstat, S3C2410_UERSTAT_OVERRUN,
				 ch, flag);
	पूर्ण

	tty_flip_buffer_push(&port->state->port);
पूर्ण

अटल irqवापस_t s3c24xx_serial_rx_अक्षरs_pio(व्योम *dev_id)
अणु
	काष्ठा s3c24xx_uart_port *ourport = dev_id;
	काष्ठा uart_port *port = &ourport->port;

	spin_lock(&port->lock);
	s3c24xx_serial_rx_drain_fअगरo(ourport);
	spin_unlock(&port->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t s3c24xx_serial_rx_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा s3c24xx_uart_port *ourport = dev_id;

	अगर (ourport->dma && ourport->dma->rx_chan)
		वापस s3c24xx_serial_rx_अक्षरs_dma(dev_id);
	वापस s3c24xx_serial_rx_अक्षरs_pio(dev_id);
पूर्ण

अटल व्योम s3c24xx_serial_tx_अक्षरs(काष्ठा s3c24xx_uart_port *ourport)
अणु
	काष्ठा uart_port *port = &ourport->port;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	पूर्णांक count, dma_count = 0;

	count = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);

	अगर (ourport->dma && ourport->dma->tx_chan &&
	    count >= ourport->min_dma_size) अणु
		पूर्णांक align = dma_get_cache_alignment() -
			(xmit->tail & (dma_get_cache_alignment() - 1));
		अगर (count - align >= ourport->min_dma_size) अणु
			dma_count = count - align;
			count = align;
		पूर्ण
	पूर्ण

	अगर (port->x_अक्षर) अणु
		wr_reg(port, S3C2410_UTXH, port->x_अक्षर);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण

	/* अगर there isn't anything more to transmit, or the uart is now
	 * stopped, disable the uart and निकास
	 */

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		s3c24xx_serial_stop_tx(port);
		वापस;
	पूर्ण

	/* try and drain the buffer... */

	अगर (count > port->fअगरosize) अणु
		count = port->fअगरosize;
		dma_count = 0;
	पूर्ण

	जबतक (!uart_circ_empty(xmit) && count > 0) अणु
		अगर (rd_regl(port, S3C2410_UFSTAT) & ourport->info->tx_fअगरofull)
			अवरोध;

		wr_reg(port, S3C2410_UTXH, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		count--;
	पूर्ण

	अगर (!count && dma_count) अणु
		s3c24xx_serial_start_tx_dma(ourport, dma_count);
		वापस;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS) अणु
		spin_unlock(&port->lock);
		uart_ग_लिखो_wakeup(port);
		spin_lock(&port->lock);
	पूर्ण

	अगर (uart_circ_empty(xmit))
		s3c24xx_serial_stop_tx(port);
पूर्ण

अटल irqवापस_t s3c24xx_serial_tx_irq(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा s3c24xx_uart_port *ourport = id;
	काष्ठा uart_port *port = &ourport->port;

	spin_lock(&port->lock);

	s3c24xx_serial_tx_अक्षरs(ourport);

	spin_unlock(&port->lock);
	वापस IRQ_HANDLED;
पूर्ण

/* पूर्णांकerrupt handler क्रम s3c64xx and later SoC's.*/
अटल irqवापस_t s3c64xx_serial_handle_irq(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा s3c24xx_uart_port *ourport = id;
	काष्ठा uart_port *port = &ourport->port;
	अचिन्हित पूर्णांक pend = rd_regl(port, S3C64XX_UINTP);
	irqवापस_t ret = IRQ_HANDLED;

	अगर (pend & S3C64XX_UINTM_RXD_MSK) अणु
		ret = s3c24xx_serial_rx_irq(irq, id);
		wr_regl(port, S3C64XX_UINTP, S3C64XX_UINTM_RXD_MSK);
	पूर्ण
	अगर (pend & S3C64XX_UINTM_TXD_MSK) अणु
		ret = s3c24xx_serial_tx_irq(irq, id);
		wr_regl(port, S3C64XX_UINTP, S3C64XX_UINTM_TXD_MSK);
	पूर्ण
	वापस ret;
पूर्ण

/* पूर्णांकerrupt handler क्रम Apple SoC's.*/
अटल irqवापस_t apple_serial_handle_irq(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा s3c24xx_uart_port *ourport = id;
	काष्ठा uart_port *port = &ourport->port;
	अचिन्हित पूर्णांक pend = rd_regl(port, S3C2410_UTRSTAT);
	irqवापस_t ret = IRQ_NONE;

	अगर (pend & (APPLE_S5L_UTRSTAT_RXTHRESH | APPLE_S5L_UTRSTAT_RXTO)) अणु
		wr_regl(port, S3C2410_UTRSTAT,
			APPLE_S5L_UTRSTAT_RXTHRESH | APPLE_S5L_UTRSTAT_RXTO);
		ret = s3c24xx_serial_rx_irq(irq, id);
	पूर्ण
	अगर (pend & APPLE_S5L_UTRSTAT_TXTHRESH) अणु
		wr_regl(port, S3C2410_UTRSTAT, APPLE_S5L_UTRSTAT_TXTHRESH);
		ret = s3c24xx_serial_tx_irq(irq, id);
	पूर्ण

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक s3c24xx_serial_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा s3c24xx_uart_info *info = s3c24xx_port_to_info(port);
	अचिन्हित दीर्घ uख_स्थिति = rd_regl(port, S3C2410_UFSTAT);
	अचिन्हित दीर्घ ufcon = rd_regl(port, S3C2410_UFCON);

	अगर (ufcon & S3C2410_UFCON_FIFOMODE) अणु
		अगर ((uख_स्थिति & info->tx_fअगरomask) != 0 ||
		    (uख_स्थिति & info->tx_fअगरofull))
			वापस 0;

		वापस 1;
	पूर्ण

	वापस s3c24xx_serial_txempty_nofअगरo(port);
पूर्ण

/* no modem control lines */
अटल अचिन्हित पूर्णांक s3c24xx_serial_get_mctrl(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक umstat = rd_reg(port, S3C2410_UMSTAT);

	अगर (umstat & S3C2410_UMSTAT_CTS)
		वापस TIOCM_CAR | TIOCM_DSR | TIOCM_CTS;
	अन्यथा
		वापस TIOCM_CAR | TIOCM_DSR;
पूर्ण

अटल व्योम s3c24xx_serial_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	अचिन्हित पूर्णांक umcon = rd_regl(port, S3C2410_UMCON);

	अगर (mctrl & TIOCM_RTS)
		umcon |= S3C2410_UMCOM_RTS_LOW;
	अन्यथा
		umcon &= ~S3C2410_UMCOM_RTS_LOW;

	wr_regl(port, S3C2410_UMCON, umcon);
पूर्ण

अटल व्योम s3c24xx_serial_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ucon;

	spin_lock_irqsave(&port->lock, flags);

	ucon = rd_regl(port, S3C2410_UCON);

	अगर (अवरोध_state)
		ucon |= S3C2410_UCON_SBREAK;
	अन्यथा
		ucon &= ~S3C2410_UCON_SBREAK;

	wr_regl(port, S3C2410_UCON, ucon);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल पूर्णांक s3c24xx_serial_request_dma(काष्ठा s3c24xx_uart_port *p)
अणु
	काष्ठा s3c24xx_uart_dma	*dma = p->dma;
	काष्ठा dma_slave_caps dma_caps;
	स्थिर अक्षर *reason = शून्य;
	पूर्णांक ret;

	/* Default slave configuration parameters */
	dma->rx_conf.direction		= DMA_DEV_TO_MEM;
	dma->rx_conf.src_addr_width	= DMA_SLAVE_BUSWIDTH_1_BYTE;
	dma->rx_conf.src_addr		= p->port.mapbase + S3C2410_URXH;
	dma->rx_conf.src_maxburst	= 1;

	dma->tx_conf.direction		= DMA_MEM_TO_DEV;
	dma->tx_conf.dst_addr_width	= DMA_SLAVE_BUSWIDTH_1_BYTE;
	dma->tx_conf.dst_addr		= p->port.mapbase + S3C2410_UTXH;
	dma->tx_conf.dst_maxburst	= 1;

	dma->rx_chan = dma_request_chan(p->port.dev, "rx");

	अगर (IS_ERR(dma->rx_chan)) अणु
		reason = "DMA RX channel request failed";
		ret = PTR_ERR(dma->rx_chan);
		जाओ err_warn;
	पूर्ण

	ret = dma_get_slave_caps(dma->rx_chan, &dma_caps);
	अगर (ret < 0 ||
	    dma_caps.residue_granularity < DMA_RESIDUE_GRANULARITY_BURST) अणु
		reason = "insufficient DMA RX engine capabilities";
		ret = -EOPNOTSUPP;
		जाओ err_release_rx;
	पूर्ण

	dmaengine_slave_config(dma->rx_chan, &dma->rx_conf);

	dma->tx_chan = dma_request_chan(p->port.dev, "tx");
	अगर (IS_ERR(dma->tx_chan)) अणु
		reason = "DMA TX channel request failed";
		ret = PTR_ERR(dma->tx_chan);
		जाओ err_release_rx;
	पूर्ण

	ret = dma_get_slave_caps(dma->tx_chan, &dma_caps);
	अगर (ret < 0 ||
	    dma_caps.residue_granularity < DMA_RESIDUE_GRANULARITY_BURST) अणु
		reason = "insufficient DMA TX engine capabilities";
		ret = -EOPNOTSUPP;
		जाओ err_release_tx;
	पूर्ण

	dmaengine_slave_config(dma->tx_chan, &dma->tx_conf);

	/* RX buffer */
	dma->rx_size = PAGE_SIZE;

	dma->rx_buf = kदो_स्मृति(dma->rx_size, GFP_KERNEL);
	अगर (!dma->rx_buf) अणु
		ret = -ENOMEM;
		जाओ err_release_tx;
	पूर्ण

	dma->rx_addr = dma_map_single(p->port.dev, dma->rx_buf,
				dma->rx_size, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(p->port.dev, dma->rx_addr)) अणु
		reason = "DMA mapping error for RX buffer";
		ret = -EIO;
		जाओ err_मुक्त_rx;
	पूर्ण

	/* TX buffer */
	dma->tx_addr = dma_map_single(p->port.dev, p->port.state->xmit.buf,
				UART_XMIT_SIZE, DMA_TO_DEVICE);
	अगर (dma_mapping_error(p->port.dev, dma->tx_addr)) अणु
		reason = "DMA mapping error for TX buffer";
		ret = -EIO;
		जाओ err_unmap_rx;
	पूर्ण

	वापस 0;

err_unmap_rx:
	dma_unmap_single(p->port.dev, dma->rx_addr, dma->rx_size,
			 DMA_FROM_DEVICE);
err_मुक्त_rx:
	kमुक्त(dma->rx_buf);
err_release_tx:
	dma_release_channel(dma->tx_chan);
err_release_rx:
	dma_release_channel(dma->rx_chan);
err_warn:
	अगर (reason)
		dev_warn(p->port.dev, "%s, DMA will not be used\n", reason);
	वापस ret;
पूर्ण

अटल व्योम s3c24xx_serial_release_dma(काष्ठा s3c24xx_uart_port *p)
अणु
	काष्ठा s3c24xx_uart_dma	*dma = p->dma;

	अगर (dma->rx_chan) अणु
		dmaengine_terminate_all(dma->rx_chan);
		dma_unmap_single(p->port.dev, dma->rx_addr,
				dma->rx_size, DMA_FROM_DEVICE);
		kमुक्त(dma->rx_buf);
		dma_release_channel(dma->rx_chan);
		dma->rx_chan = शून्य;
	पूर्ण

	अगर (dma->tx_chan) अणु
		dmaengine_terminate_all(dma->tx_chan);
		dma_unmap_single(p->port.dev, dma->tx_addr,
				UART_XMIT_SIZE, DMA_TO_DEVICE);
		dma_release_channel(dma->tx_chan);
		dma->tx_chan = शून्य;
	पूर्ण
पूर्ण

अटल व्योम s3c24xx_serial_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);

	अगर (ourport->tx_claimed) अणु
		मुक्त_irq(ourport->tx_irq, ourport);
		ourport->tx_enabled = 0;
		ourport->tx_claimed = 0;
		ourport->tx_mode = 0;
	पूर्ण

	अगर (ourport->rx_claimed) अणु
		मुक्त_irq(ourport->rx_irq, ourport);
		ourport->rx_claimed = 0;
		ourport->rx_enabled = 0;
	पूर्ण

	अगर (ourport->dma)
		s3c24xx_serial_release_dma(ourport);

	ourport->tx_in_progress = 0;
पूर्ण

अटल व्योम s3c64xx_serial_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);

	ourport->tx_enabled = 0;
	ourport->tx_mode = 0;
	ourport->rx_enabled = 0;

	मुक्त_irq(port->irq, ourport);

	wr_regl(port, S3C64XX_UINTP, 0xf);
	wr_regl(port, S3C64XX_UINTM, 0xf);

	अगर (ourport->dma)
		s3c24xx_serial_release_dma(ourport);

	ourport->tx_in_progress = 0;
पूर्ण

अटल व्योम apple_s5l_serial_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);

	अचिन्हित पूर्णांक ucon;

	ucon = rd_regl(port, S3C2410_UCON);
	ucon &= ~(APPLE_S5L_UCON_TXTHRESH_ENA_MSK |
		  APPLE_S5L_UCON_RXTHRESH_ENA_MSK |
		  APPLE_S5L_UCON_RXTO_ENA_MSK);
	wr_regl(port, S3C2410_UCON, ucon);

	wr_regl(port, S3C2410_UTRSTAT, APPLE_S5L_UTRSTAT_ALL_FLAGS);

	मुक्त_irq(port->irq, ourport);

	ourport->tx_enabled = 0;
	ourport->tx_mode = 0;
	ourport->rx_enabled = 0;

	अगर (ourport->dma)
		s3c24xx_serial_release_dma(ourport);

	ourport->tx_in_progress = 0;
पूर्ण

अटल पूर्णांक s3c24xx_serial_startup(काष्ठा uart_port *port)
अणु
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);
	पूर्णांक ret;

	ourport->rx_enabled = 1;

	ret = request_irq(ourport->rx_irq, s3c24xx_serial_rx_irq, 0,
			  s3c24xx_serial_portname(port), ourport);

	अगर (ret != 0) अणु
		dev_err(port->dev, "cannot get irq %d\n", ourport->rx_irq);
		वापस ret;
	पूर्ण

	ourport->rx_claimed = 1;

	dev_dbg(port->dev, "requesting tx irq...\n");

	ourport->tx_enabled = 1;

	ret = request_irq(ourport->tx_irq, s3c24xx_serial_tx_irq, 0,
			  s3c24xx_serial_portname(port), ourport);

	अगर (ret) अणु
		dev_err(port->dev, "cannot get irq %d\n", ourport->tx_irq);
		जाओ err;
	पूर्ण

	ourport->tx_claimed = 1;

	/* the port reset code should have करोne the correct
	 * रेजिस्टर setup क्रम the port controls
	 */

	वापस ret;

err:
	s3c24xx_serial_shutकरोwn(port);
	वापस ret;
पूर्ण

अटल पूर्णांक s3c64xx_serial_startup(काष्ठा uart_port *port)
अणु
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ufcon;
	पूर्णांक ret;

	wr_regl(port, S3C64XX_UINTM, 0xf);
	अगर (ourport->dma) अणु
		ret = s3c24xx_serial_request_dma(ourport);
		अगर (ret < 0) अणु
			devm_kमुक्त(port->dev, ourport->dma);
			ourport->dma = शून्य;
		पूर्ण
	पूर्ण

	ret = request_irq(port->irq, s3c64xx_serial_handle_irq, IRQF_SHARED,
			  s3c24xx_serial_portname(port), ourport);
	अगर (ret) अणु
		dev_err(port->dev, "cannot get irq %d\n", port->irq);
		वापस ret;
	पूर्ण

	/* For compatibility with s3c24xx Soc's */
	ourport->rx_enabled = 1;
	ourport->tx_enabled = 0;

	spin_lock_irqsave(&port->lock, flags);

	ufcon = rd_regl(port, S3C2410_UFCON);
	ufcon |= S3C2410_UFCON_RESETRX | S5PV210_UFCON_RXTRIG8;
	अगर (!uart_console(port))
		ufcon |= S3C2410_UFCON_RESETTX;
	wr_regl(port, S3C2410_UFCON, ufcon);

	enable_rx_pio(ourport);

	spin_unlock_irqrestore(&port->lock, flags);

	/* Enable Rx Interrupt */
	s3c24xx_clear_bit(port, S3C64XX_UINTM_RXD, S3C64XX_UINTM);

	वापस ret;
पूर्ण

अटल पूर्णांक apple_s5l_serial_startup(काष्ठा uart_port *port)
अणु
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ufcon;
	पूर्णांक ret;

	wr_regl(port, S3C2410_UTRSTAT, APPLE_S5L_UTRSTAT_ALL_FLAGS);

	ret = request_irq(port->irq, apple_serial_handle_irq, 0,
			  s3c24xx_serial_portname(port), ourport);
	अगर (ret) अणु
		dev_err(port->dev, "cannot get irq %d\n", port->irq);
		वापस ret;
	पूर्ण

	/* For compatibility with s3c24xx Soc's */
	ourport->rx_enabled = 1;
	ourport->tx_enabled = 0;

	spin_lock_irqsave(&port->lock, flags);

	ufcon = rd_regl(port, S3C2410_UFCON);
	ufcon |= S3C2410_UFCON_RESETRX | S5PV210_UFCON_RXTRIG8;
	अगर (!uart_console(port))
		ufcon |= S3C2410_UFCON_RESETTX;
	wr_regl(port, S3C2410_UFCON, ufcon);

	enable_rx_pio(ourport);

	spin_unlock_irqrestore(&port->lock, flags);

	/* Enable Rx Interrupt */
	s3c24xx_set_bit(port, APPLE_S5L_UCON_RXTHRESH_ENA, S3C2410_UCON);
	s3c24xx_set_bit(port, APPLE_S5L_UCON_RXTO_ENA, S3C2410_UCON);

	वापस ret;
पूर्ण

/* घातer घातer management control */

अटल व्योम s3c24xx_serial_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक level,
			      अचिन्हित पूर्णांक old)
अणु
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);
	पूर्णांक समयout = 10000;

	ourport->pm_level = level;

	चयन (level) अणु
	हाल 3:
		जबतक (--समयout && !s3c24xx_serial_txempty_nofअगरo(port))
			udelay(100);

		अगर (!IS_ERR(ourport->baudclk))
			clk_disable_unprepare(ourport->baudclk);

		clk_disable_unprepare(ourport->clk);
		अवरोध;

	हाल 0:
		clk_prepare_enable(ourport->clk);

		अगर (!IS_ERR(ourport->baudclk))
			clk_prepare_enable(ourport->baudclk);

		अवरोध;
	शेष:
		dev_err(port->dev, "s3c24xx_serial: unknown pm %d\n", level);
	पूर्ण
पूर्ण

/* baud rate calculation
 *
 * The UARTs on the S3C2410/S3C2440 can take their घड़ीs from a number
 * of dअगरferent sources, including the peripheral घड़ी ("pclk") and an
 * बाह्यal घड़ी ("uclk"). The S3C2440 also adds the core घड़ी ("fclk")
 * with a programmable extra भागisor.
 *
 * The following code goes through the घड़ी sources, and calculates the
 * baud घड़ीs (and the resultant actual baud rates) and then tries to
 * pick the बंदst one and select that.
 *
 */

#घोषणा MAX_CLK_NAME_LENGTH 15

अटल अंतरभूत पूर्णांक s3c24xx_serial_माला_लोource(काष्ठा uart_port *port)
अणु
	काष्ठा s3c24xx_uart_info *info = s3c24xx_port_to_info(port);
	अचिन्हित पूर्णांक ucon;

	अगर (info->num_clks == 1)
		वापस 0;

	ucon = rd_regl(port, S3C2410_UCON);
	ucon &= info->clksel_mask;
	वापस ucon >> info->clksel_shअगरt;
पूर्ण

अटल व्योम s3c24xx_serial_setsource(काष्ठा uart_port *port,
			अचिन्हित पूर्णांक clk_sel)
अणु
	काष्ठा s3c24xx_uart_info *info = s3c24xx_port_to_info(port);
	अचिन्हित पूर्णांक ucon;

	अगर (info->num_clks == 1)
		वापस;

	ucon = rd_regl(port, S3C2410_UCON);
	अगर ((ucon & info->clksel_mask) >> info->clksel_shअगरt == clk_sel)
		वापस;

	ucon &= ~info->clksel_mask;
	ucon |= clk_sel << info->clksel_shअगरt;
	wr_regl(port, S3C2410_UCON, ucon);
पूर्ण

अटल अचिन्हित पूर्णांक s3c24xx_serial_अ_लोlk(काष्ठा s3c24xx_uart_port *ourport,
			अचिन्हित पूर्णांक req_baud, काष्ठा clk **best_clk,
			अचिन्हित पूर्णांक *clk_num)
अणु
	काष्ठा s3c24xx_uart_info *info = ourport->info;
	काष्ठा clk *clk;
	अचिन्हित दीर्घ rate;
	अचिन्हित पूर्णांक cnt, baud, quot, best_quot = 0;
	अक्षर clkname[MAX_CLK_NAME_LENGTH];
	पूर्णांक calc_deviation, deviation = (1 << 30) - 1;

	क्रम (cnt = 0; cnt < info->num_clks; cnt++) अणु
		/* Keep selected घड़ी अगर provided */
		अगर (ourport->cfg->clk_sel &&
			!(ourport->cfg->clk_sel & (1 << cnt)))
			जारी;

		प्र_लिखो(clkname, "clk_uart_baud%d", cnt);
		clk = clk_get(ourport->port.dev, clkname);
		अगर (IS_ERR(clk))
			जारी;

		rate = clk_get_rate(clk);
		अगर (!rate)
			जारी;

		अगर (ourport->info->has_भागslot) अणु
			अचिन्हित दीर्घ भाग = rate / req_baud;

			/* The UDIVSLOT रेजिस्टर on the newer UARTs allows us to
			 * get a भागisor adjusपंचांगent of 1/16th on the baud घड़ी.
			 *
			 * We करोn't keep the UDIVSLOT value (the 16ths we
			 * calculated by not multiplying the baud by 16) as it
			 * is easy enough to recalculate.
			 */

			quot = भाग / 16;
			baud = rate / भाग;
		पूर्ण अन्यथा अणु
			quot = (rate + (8 * req_baud)) / (16 * req_baud);
			baud = rate / (quot * 16);
		पूर्ण
		quot--;

		calc_deviation = req_baud - baud;
		अगर (calc_deviation < 0)
			calc_deviation = -calc_deviation;

		अगर (calc_deviation < deviation) अणु
			*best_clk = clk;
			best_quot = quot;
			*clk_num = cnt;
			deviation = calc_deviation;
		पूर्ण
	पूर्ण

	वापस best_quot;
पूर्ण

/* uभागslot_table[]
 *
 * This table takes the fractional value of the baud भागisor and gives
 * the recommended setting क्रम the UDIVSLOT रेजिस्टर.
 */
अटल u16 uभागslot_table[16] = अणु
	[0] = 0x0000,
	[1] = 0x0080,
	[2] = 0x0808,
	[3] = 0x0888,
	[4] = 0x2222,
	[5] = 0x4924,
	[6] = 0x4A52,
	[7] = 0x54AA,
	[8] = 0x5555,
	[9] = 0xD555,
	[10] = 0xD5D5,
	[11] = 0xDDD5,
	[12] = 0xDDDD,
	[13] = 0xDFDD,
	[14] = 0xDFDF,
	[15] = 0xFFDF,
पूर्ण;

अटल व्योम s3c24xx_serial_set_termios(काष्ठा uart_port *port,
				       काष्ठा ktermios *termios,
				       काष्ठा ktermios *old)
अणु
	काष्ठा s3c2410_uartcfg *cfg = s3c24xx_port_to_cfg(port);
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);
	काष्ठा clk *clk = ERR_PTR(-EINVAL);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, quot, clk_sel = 0;
	अचिन्हित पूर्णांक ulcon;
	अचिन्हित पूर्णांक umcon;
	अचिन्हित पूर्णांक uभागslot = 0;

	/*
	 * We करोn't support modem control lines.
	 */
	termios->c_cflag &= ~(HUPCL | CMSPAR);
	termios->c_cflag |= CLOCAL;

	/*
	 * Ask the core to calculate the भागisor क्रम us.
	 */

	baud = uart_get_baud_rate(port, termios, old, 0, 3000000);
	quot = s3c24xx_serial_अ_लोlk(ourport, baud, &clk, &clk_sel);
	अगर (baud == 38400 && (port->flags & UPF_SPD_MASK) == UPF_SPD_CUST)
		quot = port->custom_भागisor;
	अगर (IS_ERR(clk))
		वापस;

	/* check to see अगर we need  to change घड़ी source */

	अगर (ourport->baudclk != clk) अणु
		clk_prepare_enable(clk);

		s3c24xx_serial_setsource(port, clk_sel);

		अगर (!IS_ERR(ourport->baudclk)) अणु
			clk_disable_unprepare(ourport->baudclk);
			ourport->baudclk = ERR_PTR(-EINVAL);
		पूर्ण

		ourport->baudclk = clk;
		ourport->baudclk_rate = clk ? clk_get_rate(clk) : 0;
	पूर्ण

	अगर (ourport->info->has_भागslot) अणु
		अचिन्हित पूर्णांक भाग = ourport->baudclk_rate / baud;

		अगर (cfg->has_fracval) अणु
			uभागslot = (भाग & 15);
			dev_dbg(port->dev, "fracval = %04x\n", uभागslot);
		पूर्ण अन्यथा अणु
			uभागslot = uभागslot_table[भाग & 15];
			dev_dbg(port->dev, "udivslot = %04x (div %d)\n",
				uभागslot, भाग & 15);
		पूर्ण
	पूर्ण

	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		dev_dbg(port->dev, "config: 5bits/char\n");
		ulcon = S3C2410_LCON_CS5;
		अवरोध;
	हाल CS6:
		dev_dbg(port->dev, "config: 6bits/char\n");
		ulcon = S3C2410_LCON_CS6;
		अवरोध;
	हाल CS7:
		dev_dbg(port->dev, "config: 7bits/char\n");
		ulcon = S3C2410_LCON_CS7;
		अवरोध;
	हाल CS8:
	शेष:
		dev_dbg(port->dev, "config: 8bits/char\n");
		ulcon = S3C2410_LCON_CS8;
		अवरोध;
	पूर्ण

	/* preserve original lcon IR settings */
	ulcon |= (cfg->ulcon & S3C2410_LCON_IRM);

	अगर (termios->c_cflag & CSTOPB)
		ulcon |= S3C2410_LCON_STOPB;

	अगर (termios->c_cflag & PARENB) अणु
		अगर (termios->c_cflag & PARODD)
			ulcon |= S3C2410_LCON_PODD;
		अन्यथा
			ulcon |= S3C2410_LCON_PEVEN;
	पूर्ण अन्यथा अणु
		ulcon |= S3C2410_LCON_PNONE;
	पूर्ण

	spin_lock_irqsave(&port->lock, flags);

	dev_dbg(port->dev,
		"setting ulcon to %08x, brddiv to %d, udivslot %08x\n",
		ulcon, quot, uभागslot);

	wr_regl(port, S3C2410_ULCON, ulcon);
	wr_regl(port, S3C2410_UBRDIV, quot);

	port->status &= ~UPSTAT_AUTOCTS;

	umcon = rd_regl(port, S3C2410_UMCON);
	अगर (termios->c_cflag & CRTSCTS) अणु
		umcon |= S3C2410_UMCOM_AFC;
		/* Disable RTS when RX FIFO contains 63 bytes */
		umcon &= ~S3C2412_UMCON_AFC_8;
		port->status = UPSTAT_AUTOCTS;
	पूर्ण अन्यथा अणु
		umcon &= ~S3C2410_UMCOM_AFC;
	पूर्ण
	wr_regl(port, S3C2410_UMCON, umcon);

	अगर (ourport->info->has_भागslot)
		wr_regl(port, S3C2443_DIVSLOT, uभागslot);

	dev_dbg(port->dev,
		"uart: ulcon = 0x%08x, ucon = 0x%08x, ufcon = 0x%08x\n",
		rd_regl(port, S3C2410_ULCON),
		rd_regl(port, S3C2410_UCON),
		rd_regl(port, S3C2410_UFCON));

	/*
	 * Update the per-port समयout.
	 */
	uart_update_समयout(port, termios->c_cflag, baud);

	/*
	 * Which अक्षरacter status flags are we पूर्णांकerested in?
	 */
	port->पढ़ो_status_mask = S3C2410_UERSTAT_OVERRUN;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= S3C2410_UERSTAT_FRAME |
			S3C2410_UERSTAT_PARITY;
	/*
	 * Which अक्षरacter status flags should we ignore?
	 */
	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= S3C2410_UERSTAT_OVERRUN;
	अगर (termios->c_अगरlag & IGNBRK && termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= S3C2410_UERSTAT_FRAME;

	/*
	 * Ignore all अक्षरacters अगर CREAD is not set.
	 */
	अगर ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= RXSTAT_DUMMY_READ;

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *s3c24xx_serial_type(काष्ठा uart_port *port)
अणु
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);

	चयन (ourport->info->type) अणु
	हाल TYPE_S3C24XX:
		वापस "S3C24XX";
	हाल TYPE_S3C6400:
		वापस "S3C6400/10";
	हाल TYPE_APPLE_S5L:
		वापस "APPLE S5L";
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम s3c24xx_serial_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	काष्ठा s3c24xx_uart_info *info = s3c24xx_port_to_info(port);

	अगर (flags & UART_CONFIG_TYPE)
		port->type = info->port_type;
पूर्ण

/*
 * verअगरy the new serial_काष्ठा (क्रम TIOCSSERIAL).
 */
अटल पूर्णांक
s3c24xx_serial_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	काष्ठा s3c24xx_uart_info *info = s3c24xx_port_to_info(port);

	अगर (ser->type != PORT_UNKNOWN && ser->type != info->port_type)
		वापस -EINVAL;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SERIAL_SAMSUNG_CONSOLE

अटल काष्ठा console s3c24xx_serial_console;

अटल पूर्णांक __init s3c24xx_serial_console_init(व्योम)
अणु
	रेजिस्टर_console(&s3c24xx_serial_console);
	वापस 0;
पूर्ण
console_initcall(s3c24xx_serial_console_init);

#घोषणा S3C24XX_SERIAL_CONSOLE &s3c24xx_serial_console
#अन्यथा
#घोषणा S3C24XX_SERIAL_CONSOLE शून्य
#पूर्ण_अगर

#अगर defined(CONFIG_SERIAL_SAMSUNG_CONSOLE) && defined(CONFIG_CONSOLE_POLL)
अटल पूर्णांक s3c24xx_serial_get_poll_अक्षर(काष्ठा uart_port *port);
अटल व्योम s3c24xx_serial_put_poll_अक्षर(काष्ठा uart_port *port,
			 अचिन्हित अक्षर c);
#पूर्ण_अगर

अटल स्थिर काष्ठा uart_ops s3c24xx_serial_ops = अणु
	.pm		= s3c24xx_serial_pm,
	.tx_empty	= s3c24xx_serial_tx_empty,
	.get_mctrl	= s3c24xx_serial_get_mctrl,
	.set_mctrl	= s3c24xx_serial_set_mctrl,
	.stop_tx	= s3c24xx_serial_stop_tx,
	.start_tx	= s3c24xx_serial_start_tx,
	.stop_rx	= s3c24xx_serial_stop_rx,
	.अवरोध_ctl	= s3c24xx_serial_अवरोध_ctl,
	.startup	= s3c24xx_serial_startup,
	.shutकरोwn	= s3c24xx_serial_shutकरोwn,
	.set_termios	= s3c24xx_serial_set_termios,
	.type		= s3c24xx_serial_type,
	.config_port	= s3c24xx_serial_config_port,
	.verअगरy_port	= s3c24xx_serial_verअगरy_port,
#अगर defined(CONFIG_SERIAL_SAMSUNG_CONSOLE) && defined(CONFIG_CONSOLE_POLL)
	.poll_get_अक्षर = s3c24xx_serial_get_poll_अक्षर,
	.poll_put_अक्षर = s3c24xx_serial_put_poll_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा uart_ops s3c64xx_serial_ops = अणु
	.pm		= s3c24xx_serial_pm,
	.tx_empty	= s3c24xx_serial_tx_empty,
	.get_mctrl	= s3c24xx_serial_get_mctrl,
	.set_mctrl	= s3c24xx_serial_set_mctrl,
	.stop_tx	= s3c24xx_serial_stop_tx,
	.start_tx	= s3c24xx_serial_start_tx,
	.stop_rx	= s3c24xx_serial_stop_rx,
	.अवरोध_ctl	= s3c24xx_serial_अवरोध_ctl,
	.startup	= s3c64xx_serial_startup,
	.shutकरोwn	= s3c64xx_serial_shutकरोwn,
	.set_termios	= s3c24xx_serial_set_termios,
	.type		= s3c24xx_serial_type,
	.config_port	= s3c24xx_serial_config_port,
	.verअगरy_port	= s3c24xx_serial_verअगरy_port,
#अगर defined(CONFIG_SERIAL_SAMSUNG_CONSOLE) && defined(CONFIG_CONSOLE_POLL)
	.poll_get_अक्षर = s3c24xx_serial_get_poll_अक्षर,
	.poll_put_अक्षर = s3c24xx_serial_put_poll_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा uart_ops apple_s5l_serial_ops = अणु
	.pm		= s3c24xx_serial_pm,
	.tx_empty	= s3c24xx_serial_tx_empty,
	.get_mctrl	= s3c24xx_serial_get_mctrl,
	.set_mctrl	= s3c24xx_serial_set_mctrl,
	.stop_tx	= s3c24xx_serial_stop_tx,
	.start_tx	= s3c24xx_serial_start_tx,
	.stop_rx	= s3c24xx_serial_stop_rx,
	.अवरोध_ctl	= s3c24xx_serial_अवरोध_ctl,
	.startup	= apple_s5l_serial_startup,
	.shutकरोwn	= apple_s5l_serial_shutकरोwn,
	.set_termios	= s3c24xx_serial_set_termios,
	.type		= s3c24xx_serial_type,
	.config_port	= s3c24xx_serial_config_port,
	.verअगरy_port	= s3c24xx_serial_verअगरy_port,
#अगर defined(CONFIG_SERIAL_SAMSUNG_CONSOLE) && defined(CONFIG_CONSOLE_POLL)
	.poll_get_अक्षर = s3c24xx_serial_get_poll_अक्षर,
	.poll_put_अक्षर = s3c24xx_serial_put_poll_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा uart_driver s3c24xx_uart_drv = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "s3c2410_serial",
	.nr		= CONFIG_SERIAL_SAMSUNG_UARTS,
	.cons		= S3C24XX_SERIAL_CONSOLE,
	.dev_name	= S3C24XX_SERIAL_NAME,
	.major		= S3C24XX_SERIAL_MAJOR,
	.minor		= S3C24XX_SERIAL_MINOR,
पूर्ण;

#घोषणा __PORT_LOCK_UNLOCKED(i) \
	__SPIN_LOCK_UNLOCKED(s3c24xx_serial_ports[i].port.lock)
अटल काष्ठा s3c24xx_uart_port
s3c24xx_serial_ports[CONFIG_SERIAL_SAMSUNG_UARTS] = अणु
	[0] = अणु
		.port = अणु
			.lock		= __PORT_LOCK_UNLOCKED(0),
			.iotype		= UPIO_MEM,
			.uartclk	= 0,
			.fअगरosize	= 16,
			.ops		= &s3c24xx_serial_ops,
			.flags		= UPF_BOOT_AUTOCONF,
			.line		= 0,
		पूर्ण
	पूर्ण,
	[1] = अणु
		.port = अणु
			.lock		= __PORT_LOCK_UNLOCKED(1),
			.iotype		= UPIO_MEM,
			.uartclk	= 0,
			.fअगरosize	= 16,
			.ops		= &s3c24xx_serial_ops,
			.flags		= UPF_BOOT_AUTOCONF,
			.line		= 1,
		पूर्ण
	पूर्ण,
#अगर CONFIG_SERIAL_SAMSUNG_UARTS > 2
	[2] = अणु
		.port = अणु
			.lock		= __PORT_LOCK_UNLOCKED(2),
			.iotype		= UPIO_MEM,
			.uartclk	= 0,
			.fअगरosize	= 16,
			.ops		= &s3c24xx_serial_ops,
			.flags		= UPF_BOOT_AUTOCONF,
			.line		= 2,
		पूर्ण
	पूर्ण,
#पूर्ण_अगर
#अगर CONFIG_SERIAL_SAMSUNG_UARTS > 3
	[3] = अणु
		.port = अणु
			.lock		= __PORT_LOCK_UNLOCKED(3),
			.iotype		= UPIO_MEM,
			.uartclk	= 0,
			.fअगरosize	= 16,
			.ops		= &s3c24xx_serial_ops,
			.flags		= UPF_BOOT_AUTOCONF,
			.line		= 3,
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण;
#अघोषित __PORT_LOCK_UNLOCKED

/* s3c24xx_serial_resetport
 *
 * reset the fअगरos and other the settings.
 */

अटल व्योम s3c24xx_serial_resetport(काष्ठा uart_port *port,
				   काष्ठा s3c2410_uartcfg *cfg)
अणु
	काष्ठा s3c24xx_uart_info *info = s3c24xx_port_to_info(port);
	अचिन्हित दीर्घ ucon = rd_regl(port, S3C2410_UCON);

	ucon &= (info->clksel_mask | info->ucon_mask);
	wr_regl(port, S3C2410_UCON, ucon | cfg->ucon);

	/* reset both fअगरos */
	wr_regl(port, S3C2410_UFCON, cfg->ufcon | S3C2410_UFCON_RESETBOTH);
	wr_regl(port, S3C2410_UFCON, cfg->ufcon);

	/* some delay is required after fअगरo reset */
	udelay(1);
पूर्ण

#अगर_घोषित CONFIG_ARM_S3C24XX_CPUFREQ

अटल पूर्णांक s3c24xx_serial_cpufreq_transition(काष्ठा notअगरier_block *nb,
					     अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा s3c24xx_uart_port *port;
	काष्ठा uart_port *uport;

	port = container_of(nb, काष्ठा s3c24xx_uart_port, freq_transition);
	uport = &port->port;

	/* check to see अगर port is enabled */

	अगर (port->pm_level != 0)
		वापस 0;

	/* try and work out अगर the baudrate is changing, we can detect
	 * a change in rate, but we करो not have support क्रम detecting
	 * a disturbance in the घड़ी-rate over the change.
	 */

	अगर (IS_ERR(port->baudclk))
		जाओ निकास;

	अगर (port->baudclk_rate == clk_get_rate(port->baudclk))
		जाओ निकास;

	अगर (val == CPUFREQ_PRECHANGE) अणु
		/* we should really shut the port करोwn whilst the
		 * frequency change is in progress.
		 */

	पूर्ण अन्यथा अगर (val == CPUFREQ_POSTCHANGE) अणु
		काष्ठा ktermios *termios;
		काष्ठा tty_काष्ठा *tty;

		अगर (uport->state == शून्य)
			जाओ निकास;

		tty = uport->state->port.tty;

		अगर (tty == शून्य)
			जाओ निकास;

		termios = &tty->termios;

		अगर (termios == शून्य) अणु
			dev_warn(uport->dev, "%s: no termios?\n", __func__);
			जाओ निकास;
		पूर्ण

		s3c24xx_serial_set_termios(uport, termios, शून्य);
	पूर्ण

निकास:
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
s3c24xx_serial_cpufreq_रेजिस्टर(काष्ठा s3c24xx_uart_port *port)
अणु
	port->freq_transition.notअगरier_call = s3c24xx_serial_cpufreq_transition;

	वापस cpufreq_रेजिस्टर_notअगरier(&port->freq_transition,
					 CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण

अटल अंतरभूत व्योम
s3c24xx_serial_cpufreq_deरेजिस्टर(काष्ठा s3c24xx_uart_port *port)
अणु
	cpufreq_unरेजिस्टर_notअगरier(&port->freq_transition,
				    CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक
s3c24xx_serial_cpufreq_रेजिस्टर(काष्ठा s3c24xx_uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
s3c24xx_serial_cpufreq_deरेजिस्टर(काष्ठा s3c24xx_uart_port *port)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक s3c24xx_serial_enable_baudclk(काष्ठा s3c24xx_uart_port *ourport)
अणु
	काष्ठा device *dev = ourport->port.dev;
	काष्ठा s3c24xx_uart_info *info = ourport->info;
	अक्षर clk_name[MAX_CLK_NAME_LENGTH];
	अचिन्हित पूर्णांक clk_sel;
	काष्ठा clk *clk;
	पूर्णांक clk_num;
	पूर्णांक ret;

	clk_sel = ourport->cfg->clk_sel ? : info->def_clk_sel;
	क्रम (clk_num = 0; clk_num < info->num_clks; clk_num++) अणु
		अगर (!(clk_sel & (1 << clk_num)))
			जारी;

		प्र_लिखो(clk_name, "clk_uart_baud%d", clk_num);
		clk = clk_get(dev, clk_name);
		अगर (IS_ERR(clk))
			जारी;

		ret = clk_prepare_enable(clk);
		अगर (ret) अणु
			clk_put(clk);
			जारी;
		पूर्ण

		ourport->baudclk = clk;
		ourport->baudclk_rate = clk_get_rate(clk);
		s3c24xx_serial_setsource(&ourport->port, clk_num);

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* s3c24xx_serial_init_port
 *
 * initialise a single serial port from the platक्रमm device given
 */

अटल पूर्णांक s3c24xx_serial_init_port(काष्ठा s3c24xx_uart_port *ourport,
				    काष्ठा platक्रमm_device *platdev)
अणु
	काष्ठा uart_port *port = &ourport->port;
	काष्ठा s3c2410_uartcfg *cfg = ourport->cfg;
	काष्ठा resource *res;
	पूर्णांक ret;

	अगर (platdev == शून्य)
		वापस -ENODEV;

	अगर (port->mapbase != 0)
		वापस -EINVAL;

	/* setup info क्रम port */
	port->dev	= &platdev->dev;

	port->uartclk = 1;

	अगर (cfg->uart_flags & UPF_CONS_FLOW) अणु
		dev_dbg(port->dev, "enabling flow control\n");
		port->flags |= UPF_CONS_FLOW;
	पूर्ण

	/* sort our the physical and भव addresses क्रम each UART */

	res = platक्रमm_get_resource(platdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(port->dev, "failed to find memory resource for uart\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(port->dev, "resource %pR)\n", res);

	port->membase = devm_ioremap_resource(port->dev, res);
	अगर (IS_ERR(port->membase)) अणु
		dev_err(port->dev, "failed to remap controller address\n");
		वापस -EBUSY;
	पूर्ण

	port->mapbase = res->start;
	ret = platक्रमm_get_irq(platdev, 0);
	अगर (ret < 0) अणु
		port->irq = 0;
	पूर्ण अन्यथा अणु
		port->irq = ret;
		ourport->rx_irq = ret;
		ourport->tx_irq = ret + 1;
	पूर्ण

	चयन (ourport->info->type) अणु
	हाल TYPE_S3C24XX:
		ret = platक्रमm_get_irq(platdev, 1);
		अगर (ret > 0)
			ourport->tx_irq = ret;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * DMA is currently supported only on DT platक्रमms, अगर DMA properties
	 * are specअगरied.
	 */
	अगर (platdev->dev.of_node && of_find_property(platdev->dev.of_node,
						     "dmas", शून्य)) अणु
		ourport->dma = devm_kzalloc(port->dev,
					    माप(*ourport->dma),
					    GFP_KERNEL);
		अगर (!ourport->dma) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
	पूर्ण

	ourport->clk	= clk_get(&platdev->dev, "uart");
	अगर (IS_ERR(ourport->clk)) अणु
		pr_err("%s: Controller clock not found\n",
				dev_name(&platdev->dev));
		ret = PTR_ERR(ourport->clk);
		जाओ err;
	पूर्ण

	ret = clk_prepare_enable(ourport->clk);
	अगर (ret) अणु
		pr_err("uart: clock failed to prepare+enable: %d\n", ret);
		clk_put(ourport->clk);
		जाओ err;
	पूर्ण

	ret = s3c24xx_serial_enable_baudclk(ourport);
	अगर (ret)
		pr_warn("uart: failed to enable baudclk\n");

	/* Keep all पूर्णांकerrupts masked and cleared */
	चयन (ourport->info->type) अणु
	हाल TYPE_S3C6400:
		wr_regl(port, S3C64XX_UINTM, 0xf);
		wr_regl(port, S3C64XX_UINTP, 0xf);
		wr_regl(port, S3C64XX_UINTSP, 0xf);
		अवरोध;
	हाल TYPE_APPLE_S5L: अणु
		अचिन्हित पूर्णांक ucon;

		ucon = rd_regl(port, S3C2410_UCON);
		ucon &= ~(APPLE_S5L_UCON_TXTHRESH_ENA_MSK |
			APPLE_S5L_UCON_RXTHRESH_ENA_MSK |
			APPLE_S5L_UCON_RXTO_ENA_MSK);
		wr_regl(port, S3C2410_UCON, ucon);

		wr_regl(port, S3C2410_UTRSTAT, APPLE_S5L_UTRSTAT_ALL_FLAGS);
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	dev_dbg(port->dev, "port: map=%pa, mem=%p, irq=%d (%d,%d), clock=%u\n",
		&port->mapbase, port->membase, port->irq,
		ourport->rx_irq, ourport->tx_irq, port->uartclk);

	/* reset the fअगरos (and setup the uart) */
	s3c24xx_serial_resetport(port, cfg);

	वापस 0;

err:
	port->mapbase = 0;
	वापस ret;
पूर्ण

/* Device driver serial port probe */

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id s3c24xx_uart_dt_match[];
#पूर्ण_अगर

अटल पूर्णांक probe_index;

अटल अंतरभूत काष्ठा s3c24xx_serial_drv_data *
s3c24xx_get_driver_data(काष्ठा platक्रमm_device *pdev)
अणु
#अगर_घोषित CONFIG_OF
	अगर (pdev->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *match;

		match = of_match_node(s3c24xx_uart_dt_match, pdev->dev.of_node);
		वापस (काष्ठा s3c24xx_serial_drv_data *)match->data;
	पूर्ण
#पूर्ण_अगर
	वापस (काष्ठा s3c24xx_serial_drv_data *)
			platक्रमm_get_device_id(pdev)->driver_data;
पूर्ण

अटल पूर्णांक s3c24xx_serial_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा s3c24xx_uart_port *ourport;
	पूर्णांक index = probe_index;
	पूर्णांक ret, prop = 0;

	अगर (np) अणु
		ret = of_alias_get_id(np, "serial");
		अगर (ret >= 0)
			index = ret;
	पूर्ण

	अगर (index >= ARRAY_SIZE(s3c24xx_serial_ports)) अणु
		dev_err(&pdev->dev, "serial%d out of range\n", index);
		वापस -EINVAL;
	पूर्ण
	ourport = &s3c24xx_serial_ports[index];

	ourport->drv_data = s3c24xx_get_driver_data(pdev);
	अगर (!ourport->drv_data) अणु
		dev_err(&pdev->dev, "could not find driver data\n");
		वापस -ENODEV;
	पूर्ण

	ourport->baudclk = ERR_PTR(-EINVAL);
	ourport->info = ourport->drv_data->info;
	ourport->cfg = (dev_get_platdata(&pdev->dev)) ?
			dev_get_platdata(&pdev->dev) :
			ourport->drv_data->def_cfg;

	चयन (ourport->info->type) अणु
	हाल TYPE_S3C24XX:
		ourport->port.ops = &s3c24xx_serial_ops;
		अवरोध;
	हाल TYPE_S3C6400:
		ourport->port.ops = &s3c64xx_serial_ops;
		अवरोध;
	हाल TYPE_APPLE_S5L:
		ourport->port.ops = &apple_s5l_serial_ops;
		अवरोध;
	पूर्ण

	अगर (np) अणु
		of_property_पढ़ो_u32(np,
			"samsung,uart-fifosize", &ourport->port.fअगरosize);

		अगर (of_property_पढ़ो_u32(np, "reg-io-width", &prop) == 0) अणु
			चयन (prop) अणु
			हाल 1:
				ourport->port.iotype = UPIO_MEM;
				अवरोध;
			हाल 4:
				ourport->port.iotype = UPIO_MEM32;
				अवरोध;
			शेष:
				dev_warn(&pdev->dev, "unsupported reg-io-width (%d)\n",
						prop);
				ret = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ourport->drv_data->fअगरosize[index])
		ourport->port.fअगरosize = ourport->drv_data->fअगरosize[index];
	अन्यथा अगर (ourport->info->fअगरosize)
		ourport->port.fअगरosize = ourport->info->fअगरosize;
	ourport->port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_SAMSUNG_CONSOLE);

	/*
	 * DMA transfers must be aligned at least to cache line size,
	 * so find minimal transfer size suitable क्रम DMA mode
	 */
	ourport->min_dma_size = max_t(पूर्णांक, ourport->port.fअगरosize,
				    dma_get_cache_alignment());

	dev_dbg(&pdev->dev, "%s: initialising port %p...\n", __func__, ourport);

	ret = s3c24xx_serial_init_port(ourport, pdev);
	अगर (ret < 0)
		वापस ret;

	अगर (!s3c24xx_uart_drv.state) अणु
		ret = uart_रेजिस्टर_driver(&s3c24xx_uart_drv);
		अगर (ret < 0) अणु
			pr_err("Failed to register Samsung UART driver\n");
			वापस ret;
		पूर्ण
	पूर्ण

	dev_dbg(&pdev->dev, "%s: adding port\n", __func__);
	uart_add_one_port(&s3c24xx_uart_drv, &ourport->port);
	platक्रमm_set_drvdata(pdev, &ourport->port);

	/*
	 * Deactivate the घड़ी enabled in s3c24xx_serial_init_port here,
	 * so that a potential re-enablement through the pm-callback overlaps
	 * and keeps the घड़ी enabled in this हाल.
	 */
	clk_disable_unprepare(ourport->clk);
	अगर (!IS_ERR(ourport->baudclk))
		clk_disable_unprepare(ourport->baudclk);

	ret = s3c24xx_serial_cpufreq_रेजिस्टर(ourport);
	अगर (ret < 0)
		dev_err(&pdev->dev, "failed to add cpufreq notifier\n");

	probe_index++;

	वापस 0;
पूर्ण

अटल पूर्णांक s3c24xx_serial_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा uart_port *port = s3c24xx_dev_to_port(&dev->dev);

	अगर (port) अणु
		s3c24xx_serial_cpufreq_deरेजिस्टर(to_ourport(port));
		uart_हटाओ_one_port(&s3c24xx_uart_drv, port);
	पूर्ण

	uart_unरेजिस्टर_driver(&s3c24xx_uart_drv);

	वापस 0;
पूर्ण

/* UART घातer management code */
#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक s3c24xx_serial_suspend(काष्ठा device *dev)
अणु
	काष्ठा uart_port *port = s3c24xx_dev_to_port(dev);

	अगर (port)
		uart_suspend_port(&s3c24xx_uart_drv, port);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c24xx_serial_resume(काष्ठा device *dev)
अणु
	काष्ठा uart_port *port = s3c24xx_dev_to_port(dev);
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);

	अगर (port) अणु
		clk_prepare_enable(ourport->clk);
		अगर (!IS_ERR(ourport->baudclk))
			clk_prepare_enable(ourport->baudclk);
		s3c24xx_serial_resetport(port, s3c24xx_port_to_cfg(port));
		अगर (!IS_ERR(ourport->baudclk))
			clk_disable_unprepare(ourport->baudclk);
		clk_disable_unprepare(ourport->clk);

		uart_resume_port(&s3c24xx_uart_drv, port);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3c24xx_serial_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा uart_port *port = s3c24xx_dev_to_port(dev);
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);

	अगर (port) अणु
		/* restore IRQ mask */
		चयन (ourport->info->type) अणु
		हाल TYPE_S3C6400: अणु
			अचिन्हित पूर्णांक uपूर्णांकm = 0xf;

			अगर (ourport->tx_enabled)
				uपूर्णांकm &= ~S3C64XX_UINTM_TXD_MSK;
			अगर (ourport->rx_enabled)
				uपूर्णांकm &= ~S3C64XX_UINTM_RXD_MSK;
			clk_prepare_enable(ourport->clk);
			अगर (!IS_ERR(ourport->baudclk))
				clk_prepare_enable(ourport->baudclk);
			wr_regl(port, S3C64XX_UINTM, uपूर्णांकm);
			अगर (!IS_ERR(ourport->baudclk))
				clk_disable_unprepare(ourport->baudclk);
			clk_disable_unprepare(ourport->clk);
			अवरोध;
		पूर्ण
		हाल TYPE_APPLE_S5L: अणु
			अचिन्हित पूर्णांक ucon;
			पूर्णांक ret;

			ret = clk_prepare_enable(ourport->clk);
			अगर (ret) अणु
				dev_err(dev, "clk_enable clk failed: %d\n", ret);
				वापस ret;
			पूर्ण
			अगर (!IS_ERR(ourport->baudclk)) अणु
				ret = clk_prepare_enable(ourport->baudclk);
				अगर (ret) अणु
					dev_err(dev, "clk_enable baudclk failed: %d\n", ret);
					clk_disable_unprepare(ourport->clk);
					वापस ret;
				पूर्ण
			पूर्ण

			ucon = rd_regl(port, S3C2410_UCON);

			ucon &= ~(APPLE_S5L_UCON_TXTHRESH_ENA_MSK |
				  APPLE_S5L_UCON_RXTHRESH_ENA_MSK |
				  APPLE_S5L_UCON_RXTO_ENA_MSK);

			अगर (ourport->tx_enabled)
				ucon |= APPLE_S5L_UCON_TXTHRESH_ENA_MSK;
			अगर (ourport->rx_enabled)
				ucon |= APPLE_S5L_UCON_RXTHRESH_ENA_MSK |
					APPLE_S5L_UCON_RXTO_ENA_MSK;

			wr_regl(port, S3C2410_UCON, ucon);

			अगर (!IS_ERR(ourport->baudclk))
				clk_disable_unprepare(ourport->baudclk);
			clk_disable_unprepare(ourport->clk);
			अवरोध;
		पूर्ण
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops s3c24xx_serial_pm_ops = अणु
	.suspend = s3c24xx_serial_suspend,
	.resume = s3c24xx_serial_resume,
	.resume_noirq = s3c24xx_serial_resume_noirq,
पूर्ण;
#घोषणा SERIAL_SAMSUNG_PM_OPS	(&s3c24xx_serial_pm_ops)

#अन्यथा /* !CONFIG_PM_SLEEP */

#घोषणा SERIAL_SAMSUNG_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

/* Console code */

#अगर_घोषित CONFIG_SERIAL_SAMSUNG_CONSOLE

अटल काष्ठा uart_port *cons_uart;

अटल पूर्णांक
s3c24xx_serial_console_txrdy(काष्ठा uart_port *port, अचिन्हित पूर्णांक ufcon)
अणु
	काष्ठा s3c24xx_uart_info *info = s3c24xx_port_to_info(port);
	अचिन्हित दीर्घ uख_स्थिति, utrstat;

	अगर (ufcon & S3C2410_UFCON_FIFOMODE) अणु
		/* fअगरo mode - check amount of data in fअगरo रेजिस्टरs... */

		uख_स्थिति = rd_regl(port, S3C2410_UFSTAT);
		वापस (uख_स्थिति & info->tx_fअगरofull) ? 0 : 1;
	पूर्ण

	/* in non-fअगरo mode, we go and use the tx buffer empty */

	utrstat = rd_regl(port, S3C2410_UTRSTAT);
	वापस (utrstat & S3C2410_UTRSTAT_TXE) ? 1 : 0;
पूर्ण

अटल bool
s3c24xx_port_configured(अचिन्हित पूर्णांक ucon)
अणु
	/* consider the serial port configured अगर the tx/rx mode set */
	वापस (ucon & 0xf) != 0;
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
/*
 * Console polling routines क्रम writing and पढ़ोing from the uart जबतक
 * in an पूर्णांकerrupt or debug context.
 */

अटल पूर्णांक s3c24xx_serial_get_poll_अक्षर(काष्ठा uart_port *port)
अणु
	काष्ठा s3c24xx_uart_port *ourport = to_ourport(port);
	अचिन्हित पूर्णांक uख_स्थिति;

	uख_स्थिति = rd_regl(port, S3C2410_UFSTAT);
	अगर (s3c24xx_serial_rx_fअगरocnt(ourport, uख_स्थिति) == 0)
		वापस NO_POLL_CHAR;

	वापस rd_reg(port, S3C2410_URXH);
पूर्ण

अटल व्योम s3c24xx_serial_put_poll_अक्षर(काष्ठा uart_port *port,
		अचिन्हित अक्षर c)
अणु
	अचिन्हित पूर्णांक ufcon = rd_regl(port, S3C2410_UFCON);
	अचिन्हित पूर्णांक ucon = rd_regl(port, S3C2410_UCON);

	/* not possible to xmit on unconfigured port */
	अगर (!s3c24xx_port_configured(ucon))
		वापस;

	जबतक (!s3c24xx_serial_console_txrdy(port, ufcon))
		cpu_relax();
	wr_reg(port, S3C2410_UTXH, c);
पूर्ण

#पूर्ण_अगर /* CONFIG_CONSOLE_POLL */

अटल व्योम
s3c24xx_serial_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	अचिन्हित पूर्णांक ufcon = rd_regl(port, S3C2410_UFCON);

	जबतक (!s3c24xx_serial_console_txrdy(port, ufcon))
		cpu_relax();
	wr_reg(port, S3C2410_UTXH, ch);
पूर्ण

अटल व्योम
s3c24xx_serial_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
			     अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक ucon = rd_regl(cons_uart, S3C2410_UCON);

	/* not possible to xmit on unconfigured port */
	अगर (!s3c24xx_port_configured(ucon))
		वापस;

	uart_console_ग_लिखो(cons_uart, s, count, s3c24xx_serial_console_अक्षर_दो);
पूर्ण

अटल व्योम __init
s3c24xx_serial_get_options(काष्ठा uart_port *port, पूर्णांक *baud,
			   पूर्णांक *parity, पूर्णांक *bits)
अणु
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक ulcon;
	अचिन्हित पूर्णांक ucon;
	अचिन्हित पूर्णांक ubrभाग;
	अचिन्हित दीर्घ rate;
	अचिन्हित पूर्णांक clk_sel;
	अक्षर clk_name[MAX_CLK_NAME_LENGTH];

	ulcon  = rd_regl(port, S3C2410_ULCON);
	ucon   = rd_regl(port, S3C2410_UCON);
	ubrभाग = rd_regl(port, S3C2410_UBRDIV);

	अगर (s3c24xx_port_configured(ucon)) अणु
		चयन (ulcon & S3C2410_LCON_CSMASK) अणु
		हाल S3C2410_LCON_CS5:
			*bits = 5;
			अवरोध;
		हाल S3C2410_LCON_CS6:
			*bits = 6;
			अवरोध;
		हाल S3C2410_LCON_CS7:
			*bits = 7;
			अवरोध;
		हाल S3C2410_LCON_CS8:
		शेष:
			*bits = 8;
			अवरोध;
		पूर्ण

		चयन (ulcon & S3C2410_LCON_PMASK) अणु
		हाल S3C2410_LCON_PEVEN:
			*parity = 'e';
			अवरोध;

		हाल S3C2410_LCON_PODD:
			*parity = 'o';
			अवरोध;

		हाल S3C2410_LCON_PNONE:
		शेष:
			*parity = 'n';
		पूर्ण

		/* now calculate the baud rate */

		clk_sel = s3c24xx_serial_माला_लोource(port);
		प्र_लिखो(clk_name, "clk_uart_baud%d", clk_sel);

		clk = clk_get(port->dev, clk_name);
		अगर (!IS_ERR(clk))
			rate = clk_get_rate(clk);
		अन्यथा
			rate = 1;

		*baud = rate / (16 * (ubrभाग + 1));
		dev_dbg(port->dev, "calculated baud %d\n", *baud);
	पूर्ण
पूर्ण

अटल पूर्णांक __init
s3c24xx_serial_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	/* is this a valid port */

	अगर (co->index == -1 || co->index >= CONFIG_SERIAL_SAMSUNG_UARTS)
		co->index = 0;

	port = &s3c24xx_serial_ports[co->index].port;

	/* is the port configured? */

	अगर (port->mapbase == 0x0)
		वापस -ENODEV;

	cons_uart = port;

	/*
	 * Check whether an invalid uart number has been specअगरied, and
	 * अगर so, search क्रम the first available port that करोes have
	 * console support.
	 */
	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	अन्यथा
		s3c24xx_serial_get_options(port, &baud, &parity, &bits);

	dev_dbg(port->dev, "baud %d\n", baud);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा console s3c24xx_serial_console = अणु
	.name		= S3C24XX_SERIAL_NAME,
	.device		= uart_console_device,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.ग_लिखो		= s3c24xx_serial_console_ग_लिखो,
	.setup		= s3c24xx_serial_console_setup,
	.data		= &s3c24xx_uart_drv,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SERIAL_SAMSUNG_CONSOLE */

#अगर_घोषित CONFIG_CPU_S3C2410
अटल काष्ठा s3c24xx_serial_drv_data s3c2410_serial_drv_data = अणु
	.info = &(काष्ठा s3c24xx_uart_info) अणु
		.name		= "Samsung S3C2410 UART",
		.type		= TYPE_S3C24XX,
		.port_type	= PORT_S3C2410,
		.fअगरosize	= 16,
		.rx_fअगरomask	= S3C2410_UFSTAT_RXMASK,
		.rx_fअगरoshअगरt	= S3C2410_UFSTAT_RXSHIFT,
		.rx_fअगरofull	= S3C2410_UFSTAT_RXFULL,
		.tx_fअगरofull	= S3C2410_UFSTAT_TXFULL,
		.tx_fअगरomask	= S3C2410_UFSTAT_TXMASK,
		.tx_fअगरoshअगरt	= S3C2410_UFSTAT_TXSHIFT,
		.def_clk_sel	= S3C2410_UCON_CLKSEL0,
		.num_clks	= 2,
		.clksel_mask	= S3C2410_UCON_CLKMASK,
		.clksel_shअगरt	= S3C2410_UCON_CLKSHIFT,
	पूर्ण,
	.def_cfg = &(काष्ठा s3c2410_uartcfg) अणु
		.ucon		= S3C2410_UCON_DEFAULT,
		.ufcon		= S3C2410_UFCON_DEFAULT,
	पूर्ण,
पूर्ण;
#घोषणा S3C2410_SERIAL_DRV_DATA ((kernel_uदीर्घ_t)&s3c2410_serial_drv_data)
#अन्यथा
#घोषणा S3C2410_SERIAL_DRV_DATA (kernel_uदीर्घ_t)शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S3C2412
अटल काष्ठा s3c24xx_serial_drv_data s3c2412_serial_drv_data = अणु
	.info = &(काष्ठा s3c24xx_uart_info) अणु
		.name		= "Samsung S3C2412 UART",
		.type		= TYPE_S3C24XX,
		.port_type	= PORT_S3C2412,
		.fअगरosize	= 64,
		.has_भागslot	= 1,
		.rx_fअगरomask	= S3C2440_UFSTAT_RXMASK,
		.rx_fअगरoshअगरt	= S3C2440_UFSTAT_RXSHIFT,
		.rx_fअगरofull	= S3C2440_UFSTAT_RXFULL,
		.tx_fअगरofull	= S3C2440_UFSTAT_TXFULL,
		.tx_fअगरomask	= S3C2440_UFSTAT_TXMASK,
		.tx_fअगरoshअगरt	= S3C2440_UFSTAT_TXSHIFT,
		.def_clk_sel	= S3C2410_UCON_CLKSEL2,
		.num_clks	= 4,
		.clksel_mask	= S3C2412_UCON_CLKMASK,
		.clksel_shअगरt	= S3C2412_UCON_CLKSHIFT,
	पूर्ण,
	.def_cfg = &(काष्ठा s3c2410_uartcfg) अणु
		.ucon		= S3C2410_UCON_DEFAULT,
		.ufcon		= S3C2410_UFCON_DEFAULT,
	पूर्ण,
पूर्ण;
#घोषणा S3C2412_SERIAL_DRV_DATA ((kernel_uदीर्घ_t)&s3c2412_serial_drv_data)
#अन्यथा
#घोषणा S3C2412_SERIAL_DRV_DATA (kernel_uदीर्घ_t)शून्य
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_S3C2440) || defined(CONFIG_CPU_S3C2416) || \
	defined(CONFIG_CPU_S3C2443) || defined(CONFIG_CPU_S3C2442)
अटल काष्ठा s3c24xx_serial_drv_data s3c2440_serial_drv_data = अणु
	.info = &(काष्ठा s3c24xx_uart_info) अणु
		.name		= "Samsung S3C2440 UART",
		.type		= TYPE_S3C24XX,
		.port_type	= PORT_S3C2440,
		.fअगरosize	= 64,
		.has_भागslot	= 1,
		.rx_fअगरomask	= S3C2440_UFSTAT_RXMASK,
		.rx_fअगरoshअगरt	= S3C2440_UFSTAT_RXSHIFT,
		.rx_fअगरofull	= S3C2440_UFSTAT_RXFULL,
		.tx_fअगरofull	= S3C2440_UFSTAT_TXFULL,
		.tx_fअगरomask	= S3C2440_UFSTAT_TXMASK,
		.tx_fअगरoshअगरt	= S3C2440_UFSTAT_TXSHIFT,
		.def_clk_sel	= S3C2410_UCON_CLKSEL2,
		.num_clks	= 4,
		.clksel_mask	= S3C2412_UCON_CLKMASK,
		.clksel_shअगरt	= S3C2412_UCON_CLKSHIFT,
		.ucon_mask	= S3C2440_UCON0_DIVMASK,
	पूर्ण,
	.def_cfg = &(काष्ठा s3c2410_uartcfg) अणु
		.ucon		= S3C2410_UCON_DEFAULT,
		.ufcon		= S3C2410_UFCON_DEFAULT,
	पूर्ण,
पूर्ण;
#घोषणा S3C2440_SERIAL_DRV_DATA ((kernel_uदीर्घ_t)&s3c2440_serial_drv_data)
#अन्यथा
#घोषणा S3C2440_SERIAL_DRV_DATA (kernel_uदीर्घ_t)शून्य
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_S3C6400) || defined(CONFIG_CPU_S3C6410)
अटल काष्ठा s3c24xx_serial_drv_data s3c6400_serial_drv_data = अणु
	.info = &(काष्ठा s3c24xx_uart_info) अणु
		.name		= "Samsung S3C6400 UART",
		.type		= TYPE_S3C6400,
		.port_type	= PORT_S3C6400,
		.fअगरosize	= 64,
		.has_भागslot	= 1,
		.rx_fअगरomask	= S3C2440_UFSTAT_RXMASK,
		.rx_fअगरoshअगरt	= S3C2440_UFSTAT_RXSHIFT,
		.rx_fअगरofull	= S3C2440_UFSTAT_RXFULL,
		.tx_fअगरofull	= S3C2440_UFSTAT_TXFULL,
		.tx_fअगरomask	= S3C2440_UFSTAT_TXMASK,
		.tx_fअगरoshअगरt	= S3C2440_UFSTAT_TXSHIFT,
		.def_clk_sel	= S3C2410_UCON_CLKSEL2,
		.num_clks	= 4,
		.clksel_mask	= S3C6400_UCON_CLKMASK,
		.clksel_shअगरt	= S3C6400_UCON_CLKSHIFT,
	पूर्ण,
	.def_cfg = &(काष्ठा s3c2410_uartcfg) अणु
		.ucon		= S3C2410_UCON_DEFAULT,
		.ufcon		= S3C2410_UFCON_DEFAULT,
	पूर्ण,
पूर्ण;
#घोषणा S3C6400_SERIAL_DRV_DATA ((kernel_uदीर्घ_t)&s3c6400_serial_drv_data)
#अन्यथा
#घोषणा S3C6400_SERIAL_DRV_DATA (kernel_uदीर्घ_t)शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S5PV210
अटल काष्ठा s3c24xx_serial_drv_data s5pv210_serial_drv_data = अणु
	.info = &(काष्ठा s3c24xx_uart_info) अणु
		.name		= "Samsung S5PV210 UART",
		.type		= TYPE_S3C6400,
		.port_type	= PORT_S3C6400,
		.has_भागslot	= 1,
		.rx_fअगरomask	= S5PV210_UFSTAT_RXMASK,
		.rx_fअगरoshअगरt	= S5PV210_UFSTAT_RXSHIFT,
		.rx_fअगरofull	= S5PV210_UFSTAT_RXFULL,
		.tx_fअगरofull	= S5PV210_UFSTAT_TXFULL,
		.tx_fअगरomask	= S5PV210_UFSTAT_TXMASK,
		.tx_fअगरoshअगरt	= S5PV210_UFSTAT_TXSHIFT,
		.def_clk_sel	= S3C2410_UCON_CLKSEL0,
		.num_clks	= 2,
		.clksel_mask	= S5PV210_UCON_CLKMASK,
		.clksel_shअगरt	= S5PV210_UCON_CLKSHIFT,
	पूर्ण,
	.def_cfg = &(काष्ठा s3c2410_uartcfg) अणु
		.ucon		= S5PV210_UCON_DEFAULT,
		.ufcon		= S5PV210_UFCON_DEFAULT,
	पूर्ण,
	.fअगरosize = अणु 256, 64, 16, 16 पूर्ण,
पूर्ण;
#घोषणा S5PV210_SERIAL_DRV_DATA ((kernel_uदीर्घ_t)&s5pv210_serial_drv_data)
#अन्यथा
#घोषणा S5PV210_SERIAL_DRV_DATA	(kernel_uदीर्घ_t)शून्य
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_EXYNOS)
#घोषणा EXYNOS_COMMON_SERIAL_DRV_DATA				\
	.info = &(काष्ठा s3c24xx_uart_info) अणु			\
		.name		= "Samsung Exynos UART",	\
		.type		= TYPE_S3C6400,			\
		.port_type	= PORT_S3C6400,			\
		.has_भागslot	= 1,				\
		.rx_fअगरomask	= S5PV210_UFSTAT_RXMASK,	\
		.rx_fअगरoshअगरt	= S5PV210_UFSTAT_RXSHIFT,	\
		.rx_fअगरofull	= S5PV210_UFSTAT_RXFULL,	\
		.tx_fअगरofull	= S5PV210_UFSTAT_TXFULL,	\
		.tx_fअगरomask	= S5PV210_UFSTAT_TXMASK,	\
		.tx_fअगरoshअगरt	= S5PV210_UFSTAT_TXSHIFT,	\
		.def_clk_sel	= S3C2410_UCON_CLKSEL0,		\
		.num_clks	= 1,				\
		.clksel_mask	= 0,				\
		.clksel_shअगरt	= 0,				\
	पूर्ण,							\
	.def_cfg = &(काष्ठा s3c2410_uartcfg) अणु			\
		.ucon		= S5PV210_UCON_DEFAULT,		\
		.ufcon		= S5PV210_UFCON_DEFAULT,	\
		.has_fracval	= 1,				\
	पूर्ण							\

अटल काष्ठा s3c24xx_serial_drv_data exynos4210_serial_drv_data = अणु
	EXYNOS_COMMON_SERIAL_DRV_DATA,
	.fअगरosize = अणु 256, 64, 16, 16 पूर्ण,
पूर्ण;

अटल काष्ठा s3c24xx_serial_drv_data exynos5433_serial_drv_data = अणु
	EXYNOS_COMMON_SERIAL_DRV_DATA,
	.fअगरosize = अणु 64, 256, 16, 256 पूर्ण,
पूर्ण;

#घोषणा EXYNOS4210_SERIAL_DRV_DATA ((kernel_uदीर्घ_t)&exynos4210_serial_drv_data)
#घोषणा EXYNOS5433_SERIAL_DRV_DATA ((kernel_uदीर्घ_t)&exynos5433_serial_drv_data)
#अन्यथा
#घोषणा EXYNOS4210_SERIAL_DRV_DATA (kernel_uदीर्घ_t)शून्य
#घोषणा EXYNOS5433_SERIAL_DRV_DATA (kernel_uदीर्घ_t)शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_APPLE
अटल काष्ठा s3c24xx_serial_drv_data s5l_serial_drv_data = अणु
	.info = &(काष्ठा s3c24xx_uart_info) अणु
		.name		= "Apple S5L UART",
		.type		= TYPE_APPLE_S5L,
		.port_type	= PORT_8250,
		.fअगरosize	= 16,
		.rx_fअगरomask	= S3C2410_UFSTAT_RXMASK,
		.rx_fअगरoshअगरt	= S3C2410_UFSTAT_RXSHIFT,
		.rx_fअगरofull	= S3C2410_UFSTAT_RXFULL,
		.tx_fअगरofull	= S3C2410_UFSTAT_TXFULL,
		.tx_fअगरomask	= S3C2410_UFSTAT_TXMASK,
		.tx_fअगरoshअगरt	= S3C2410_UFSTAT_TXSHIFT,
		.def_clk_sel	= S3C2410_UCON_CLKSEL0,
		.num_clks	= 1,
		.clksel_mask	= 0,
		.clksel_shअगरt	= 0,
	पूर्ण,
	.def_cfg = &(काष्ठा s3c2410_uartcfg) अणु
		.ucon		= APPLE_S5L_UCON_DEFAULT,
		.ufcon		= S3C2410_UFCON_DEFAULT,
	पूर्ण,
पूर्ण;
#घोषणा S5L_SERIAL_DRV_DATA ((kernel_uदीर्घ_t)&s5l_serial_drv_data)
#अन्यथा
#घोषणा S5L_SERIAL_DRV_DATA ((kernel_uदीर्घ_t)शून्य)
#पूर्ण_अगर

अटल स्थिर काष्ठा platक्रमm_device_id s3c24xx_serial_driver_ids[] = अणु
	अणु
		.name		= "s3c2410-uart",
		.driver_data	= S3C2410_SERIAL_DRV_DATA,
	पूर्ण, अणु
		.name		= "s3c2412-uart",
		.driver_data	= S3C2412_SERIAL_DRV_DATA,
	पूर्ण, अणु
		.name		= "s3c2440-uart",
		.driver_data	= S3C2440_SERIAL_DRV_DATA,
	पूर्ण, अणु
		.name		= "s3c6400-uart",
		.driver_data	= S3C6400_SERIAL_DRV_DATA,
	पूर्ण, अणु
		.name		= "s5pv210-uart",
		.driver_data	= S5PV210_SERIAL_DRV_DATA,
	पूर्ण, अणु
		.name		= "exynos4210-uart",
		.driver_data	= EXYNOS4210_SERIAL_DRV_DATA,
	पूर्ण, अणु
		.name		= "exynos5433-uart",
		.driver_data	= EXYNOS5433_SERIAL_DRV_DATA,
	पूर्ण, अणु
		.name		= "s5l-uart",
		.driver_data	= S5L_SERIAL_DRV_DATA,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, s3c24xx_serial_driver_ids);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id s3c24xx_uart_dt_match[] = अणु
	अणु .compatible = "samsung,s3c2410-uart",
		.data = (व्योम *)S3C2410_SERIAL_DRV_DATA पूर्ण,
	अणु .compatible = "samsung,s3c2412-uart",
		.data = (व्योम *)S3C2412_SERIAL_DRV_DATA पूर्ण,
	अणु .compatible = "samsung,s3c2440-uart",
		.data = (व्योम *)S3C2440_SERIAL_DRV_DATA पूर्ण,
	अणु .compatible = "samsung,s3c6400-uart",
		.data = (व्योम *)S3C6400_SERIAL_DRV_DATA पूर्ण,
	अणु .compatible = "samsung,s5pv210-uart",
		.data = (व्योम *)S5PV210_SERIAL_DRV_DATA पूर्ण,
	अणु .compatible = "samsung,exynos4210-uart",
		.data = (व्योम *)EXYNOS4210_SERIAL_DRV_DATA पूर्ण,
	अणु .compatible = "samsung,exynos5433-uart",
		.data = (व्योम *)EXYNOS5433_SERIAL_DRV_DATA पूर्ण,
	अणु .compatible = "apple,s5l-uart",
		.data = (व्योम *)S5L_SERIAL_DRV_DATA पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, s3c24xx_uart_dt_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver samsung_serial_driver = अणु
	.probe		= s3c24xx_serial_probe,
	.हटाओ		= s3c24xx_serial_हटाओ,
	.id_table	= s3c24xx_serial_driver_ids,
	.driver		= अणु
		.name	= "samsung-uart",
		.pm	= SERIAL_SAMSUNG_PM_OPS,
		.of_match_table	= of_match_ptr(s3c24xx_uart_dt_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(samsung_serial_driver);

#अगर_घोषित CONFIG_SERIAL_SAMSUNG_CONSOLE
/*
 * Early console.
 */

अटल व्योम wr_reg_barrier(काष्ठा uart_port *port, u32 reg, u32 val)
अणु
	चयन (port->iotype) अणु
	हाल UPIO_MEM:
		ग_लिखोb(val, portaddr(port, reg));
		अवरोध;
	हाल UPIO_MEM32:
		ग_लिखोl(val, portaddr(port, reg));
		अवरोध;
	पूर्ण
पूर्ण

काष्ठा samsung_early_console_data अणु
	u32 txfull_mask;
पूर्ण;

अटल व्योम samsung_early_busyuart(काष्ठा uart_port *port)
अणु
	जबतक (!(पढ़ोl(port->membase + S3C2410_UTRSTAT) & S3C2410_UTRSTAT_TXFE))
		;
पूर्ण

अटल व्योम samsung_early_busyuart_fअगरo(काष्ठा uart_port *port)
अणु
	काष्ठा samsung_early_console_data *data = port->निजी_data;

	जबतक (पढ़ोl(port->membase + S3C2410_UFSTAT) & data->txfull_mask)
		;
पूर्ण

अटल व्योम samsung_early_अ_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	अगर (पढ़ोl(port->membase + S3C2410_UFCON) & S3C2410_UFCON_FIFOMODE)
		samsung_early_busyuart_fअगरo(port);
	अन्यथा
		samsung_early_busyuart(port);

	wr_reg_barrier(port, S3C2410_UTXH, c);
पूर्ण

अटल व्योम samsung_early_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s,
				अचिन्हित पूर्णांक n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	uart_console_ग_लिखो(&dev->port, s, n, samsung_early_अ_दो);
पूर्ण

अटल पूर्णांक __init samsung_early_console_setup(काष्ठा earlycon_device *device,
					      स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->con->ग_लिखो = samsung_early_ग_लिखो;
	वापस 0;
पूर्ण

/* S3C2410 */
अटल काष्ठा samsung_early_console_data s3c2410_early_console_data = अणु
	.txfull_mask = S3C2410_UFSTAT_TXFULL,
पूर्ण;

अटल पूर्णांक __init s3c2410_early_console_setup(काष्ठा earlycon_device *device,
					      स्थिर अक्षर *opt)
अणु
	device->port.निजी_data = &s3c2410_early_console_data;
	वापस samsung_early_console_setup(device, opt);
पूर्ण

OF_EARLYCON_DECLARE(s3c2410, "samsung,s3c2410-uart",
			s3c2410_early_console_setup);

/* S3C2412, S3C2440, S3C64xx */
अटल काष्ठा samsung_early_console_data s3c2440_early_console_data = अणु
	.txfull_mask = S3C2440_UFSTAT_TXFULL,
पूर्ण;

अटल पूर्णांक __init s3c2440_early_console_setup(काष्ठा earlycon_device *device,
					      स्थिर अक्षर *opt)
अणु
	device->port.निजी_data = &s3c2440_early_console_data;
	वापस samsung_early_console_setup(device, opt);
पूर्ण

OF_EARLYCON_DECLARE(s3c2412, "samsung,s3c2412-uart",
			s3c2440_early_console_setup);
OF_EARLYCON_DECLARE(s3c2440, "samsung,s3c2440-uart",
			s3c2440_early_console_setup);
OF_EARLYCON_DECLARE(s3c6400, "samsung,s3c6400-uart",
			s3c2440_early_console_setup);

/* S5PV210, Exynos */
अटल काष्ठा samsung_early_console_data s5pv210_early_console_data = अणु
	.txfull_mask = S5PV210_UFSTAT_TXFULL,
पूर्ण;

अटल पूर्णांक __init s5pv210_early_console_setup(काष्ठा earlycon_device *device,
					      स्थिर अक्षर *opt)
अणु
	device->port.निजी_data = &s5pv210_early_console_data;
	वापस samsung_early_console_setup(device, opt);
पूर्ण

OF_EARLYCON_DECLARE(s5pv210, "samsung,s5pv210-uart",
			s5pv210_early_console_setup);
OF_EARLYCON_DECLARE(exynos4210, "samsung,exynos4210-uart",
			s5pv210_early_console_setup);

/* Apple S5L */
अटल पूर्णांक __init apple_s5l_early_console_setup(काष्ठा earlycon_device *device,
						स्थिर अक्षर *opt)
अणु
	/* Close enough to S3C2410 क्रम earlycon... */
	device->port.निजी_data = &s3c2410_early_console_data;

#अगर_घोषित CONFIG_ARM64
	/* ... but we need to override the existing fixmap entry as nGnRnE */
	__set_fixmap(FIX_EARLYCON_MEM_BASE, device->port.mapbase,
		     __pgprot(PROT_DEVICE_nGnRnE));
#पूर्ण_अगर
	वापस samsung_early_console_setup(device, opt);
पूर्ण

OF_EARLYCON_DECLARE(s5l, "apple,s5l-uart", apple_s5l_early_console_setup);
#पूर्ण_अगर

MODULE_ALIAS("platform:samsung-uart");
MODULE_DESCRIPTION("Samsung SoC Serial port driver");
MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_LICENSE("GPL v2");
