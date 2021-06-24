<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2012-2015 Spपढ़ोtrum Communications Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dma/sprd-dma.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

/* device name */
#घोषणा UART_NR_MAX		8
#घोषणा SPRD_TTY_NAME		"ttyS"
#घोषणा SPRD_FIFO_SIZE		128
#घोषणा SPRD_DEF_RATE		26000000
#घोषणा SPRD_BAUD_IO_LIMIT	3000000
#घोषणा SPRD_TIMEOUT		256000

/* the offset of serial रेजिस्टरs and BITs क्रम them */
/* data रेजिस्टरs */
#घोषणा SPRD_TXD		0x0000
#घोषणा SPRD_RXD		0x0004

/* line status रेजिस्टर and its BITs  */
#घोषणा SPRD_LSR		0x0008
#घोषणा SPRD_LSR_OE		BIT(4)
#घोषणा SPRD_LSR_FE		BIT(3)
#घोषणा SPRD_LSR_PE		BIT(2)
#घोषणा SPRD_LSR_BI		BIT(7)
#घोषणा SPRD_LSR_TX_OVER	BIT(15)

/* data number in TX and RX fअगरo */
#घोषणा SPRD_STS1		0x000C
#घोषणा SPRD_RX_FIFO_CNT_MASK	GENMASK(7, 0)
#घोषणा SPRD_TX_FIFO_CNT_MASK	GENMASK(15, 8)

/* पूर्णांकerrupt enable रेजिस्टर and its BITs */
#घोषणा SPRD_IEN		0x0010
#घोषणा SPRD_IEN_RX_FULL	BIT(0)
#घोषणा SPRD_IEN_TX_EMPTY	BIT(1)
#घोषणा SPRD_IEN_BREAK_DETECT	BIT(7)
#घोषणा SPRD_IEN_TIMEOUT	BIT(13)

/* पूर्णांकerrupt clear रेजिस्टर */
#घोषणा SPRD_ICLR		0x0014
#घोषणा SPRD_ICLR_TIMEOUT	BIT(13)

/* line control रेजिस्टर */
#घोषणा SPRD_LCR		0x0018
#घोषणा SPRD_LCR_STOP_1BIT	0x10
#घोषणा SPRD_LCR_STOP_2BIT	0x30
#घोषणा SPRD_LCR_DATA_LEN	(BIT(2) | BIT(3))
#घोषणा SPRD_LCR_DATA_LEN5	0x0
#घोषणा SPRD_LCR_DATA_LEN6	0x4
#घोषणा SPRD_LCR_DATA_LEN7	0x8
#घोषणा SPRD_LCR_DATA_LEN8	0xc
#घोषणा SPRD_LCR_PARITY		(BIT(0) | BIT(1))
#घोषणा SPRD_LCR_PARITY_EN	0x2
#घोषणा SPRD_LCR_EVEN_PAR	0x0
#घोषणा SPRD_LCR_ODD_PAR	0x1

/* control रेजिस्टर 1 */
#घोषणा SPRD_CTL1		0x001C
#घोषणा SPRD_DMA_EN		BIT(15)
#घोषणा SPRD_LOOPBACK_EN	BIT(14)
#घोषणा RX_HW_FLOW_CTL_THLD	BIT(6)
#घोषणा RX_HW_FLOW_CTL_EN	BIT(7)
#घोषणा TX_HW_FLOW_CTL_EN	BIT(8)
#घोषणा RX_TOUT_THLD_DEF	0x3E00
#घोषणा RX_HFC_THLD_DEF		0x40

/* fअगरo threshold रेजिस्टर */
#घोषणा SPRD_CTL2		0x0020
#घोषणा THLD_TX_EMPTY		0x40
#घोषणा THLD_TX_EMPTY_SHIFT	8
#घोषणा THLD_RX_FULL		0x40
#घोषणा THLD_RX_FULL_MASK	GENMASK(6, 0)

/* config baud rate रेजिस्टर */
#घोषणा SPRD_CLKD0		0x0024
#घोषणा SPRD_CLKD0_MASK		GENMASK(15, 0)
#घोषणा SPRD_CLKD1		0x0028
#घोषणा SPRD_CLKD1_MASK		GENMASK(20, 16)
#घोषणा SPRD_CLKD1_SHIFT	16

/* पूर्णांकerrupt mask status रेजिस्टर */
#घोषणा SPRD_IMSR		0x002C
#घोषणा SPRD_IMSR_RX_FIFO_FULL	BIT(0)
#घोषणा SPRD_IMSR_TX_FIFO_EMPTY	BIT(1)
#घोषणा SPRD_IMSR_BREAK_DETECT	BIT(7)
#घोषणा SPRD_IMSR_TIMEOUT	BIT(13)
#घोषणा SPRD_DEFAULT_SOURCE_CLK	26000000

#घोषणा SPRD_RX_DMA_STEP	1
#घोषणा SPRD_RX_FIFO_FULL	1
#घोषणा SPRD_TX_FIFO_FULL	0x20
#घोषणा SPRD_UART_RX_SIZE	(UART_XMIT_SIZE / 4)

काष्ठा sprd_uart_dma अणु
	काष्ठा dma_chan *chn;
	अचिन्हित अक्षर *virt;
	dma_addr_t phys_addr;
	dma_cookie_t cookie;
	u32 trans_len;
	bool enable;
पूर्ण;

काष्ठा sprd_uart_port अणु
	काष्ठा uart_port port;
	अक्षर name[16];
	काष्ठा clk *clk;
	काष्ठा sprd_uart_dma tx_dma;
	काष्ठा sprd_uart_dma rx_dma;
	dma_addr_t pos;
	अचिन्हित अक्षर *rx_buf_tail;
पूर्ण;

अटल काष्ठा sprd_uart_port *sprd_port[UART_NR_MAX];
अटल पूर्णांक sprd_ports_num;

अटल पूर्णांक sprd_start_dma_rx(काष्ठा uart_port *port);
अटल पूर्णांक sprd_tx_dma_config(काष्ठा uart_port *port);

अटल अंतरभूत अचिन्हित पूर्णांक serial_in(काष्ठा uart_port *port,
				     अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl_relaxed(port->membase + offset);
पूर्ण

अटल अंतरभूत व्योम serial_out(काष्ठा uart_port *port, अचिन्हित पूर्णांक offset,
			      पूर्णांक value)
अणु
	ग_लिखोl_relaxed(value, port->membase + offset);
पूर्ण

अटल अचिन्हित पूर्णांक sprd_tx_empty(काष्ठा uart_port *port)
अणु
	अगर (serial_in(port, SPRD_STS1) & SPRD_TX_FIFO_CNT_MASK)
		वापस 0;
	अन्यथा
		वापस TIOCSER_TEMT;
पूर्ण

अटल अचिन्हित पूर्णांक sprd_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस TIOCM_DSR | TIOCM_CTS;
पूर्ण

अटल व्योम sprd_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	u32 val = serial_in(port, SPRD_CTL1);

	अगर (mctrl & TIOCM_LOOP)
		val |= SPRD_LOOPBACK_EN;
	अन्यथा
		val &= ~SPRD_LOOPBACK_EN;

	serial_out(port, SPRD_CTL1, val);
पूर्ण

अटल व्योम sprd_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा sprd_uart_port *sp =
		container_of(port, काष्ठा sprd_uart_port, port);
	अचिन्हित पूर्णांक ien, iclr;

	अगर (sp->rx_dma.enable)
		dmaengine_terminate_all(sp->rx_dma.chn);

	iclr = serial_in(port, SPRD_ICLR);
	ien = serial_in(port, SPRD_IEN);

	ien &= ~(SPRD_IEN_RX_FULL | SPRD_IEN_BREAK_DETECT);
	iclr |= SPRD_IEN_RX_FULL | SPRD_IEN_BREAK_DETECT;

	serial_out(port, SPRD_IEN, ien);
	serial_out(port, SPRD_ICLR, iclr);
पूर्ण

अटल व्योम sprd_uart_dma_enable(काष्ठा uart_port *port, bool enable)
अणु
	u32 val = serial_in(port, SPRD_CTL1);

	अगर (enable)
		val |= SPRD_DMA_EN;
	अन्यथा
		val &= ~SPRD_DMA_EN;

	serial_out(port, SPRD_CTL1, val);
पूर्ण

अटल व्योम sprd_stop_tx_dma(काष्ठा uart_port *port)
अणु
	काष्ठा sprd_uart_port *sp =
		container_of(port, काष्ठा sprd_uart_port, port);
	काष्ठा circ_buf *xmit = &port->state->xmit;
	काष्ठा dma_tx_state state;
	u32 trans_len;

	dmaengine_छोड़ो(sp->tx_dma.chn);

	dmaengine_tx_status(sp->tx_dma.chn, sp->tx_dma.cookie, &state);
	अगर (state.residue) अणु
		trans_len = state.residue - sp->tx_dma.phys_addr;
		xmit->tail = (xmit->tail + trans_len) & (UART_XMIT_SIZE - 1);
		port->icount.tx += trans_len;
		dma_unmap_single(port->dev, sp->tx_dma.phys_addr,
				 sp->tx_dma.trans_len, DMA_TO_DEVICE);
	पूर्ण

	dmaengine_terminate_all(sp->tx_dma.chn);
	sp->tx_dma.trans_len = 0;
पूर्ण

अटल पूर्णांक sprd_tx_buf_remap(काष्ठा uart_port *port)
अणु
	काष्ठा sprd_uart_port *sp =
		container_of(port, काष्ठा sprd_uart_port, port);
	काष्ठा circ_buf *xmit = &port->state->xmit;

	sp->tx_dma.trans_len =
		CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);

	sp->tx_dma.phys_addr = dma_map_single(port->dev,
					      (व्योम *)&(xmit->buf[xmit->tail]),
					      sp->tx_dma.trans_len,
					      DMA_TO_DEVICE);
	वापस dma_mapping_error(port->dev, sp->tx_dma.phys_addr);
पूर्ण

अटल व्योम sprd_complete_tx_dma(व्योम *data)
अणु
	काष्ठा uart_port *port = (काष्ठा uart_port *)data;
	काष्ठा sprd_uart_port *sp =
		container_of(port, काष्ठा sprd_uart_port, port);
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	dma_unmap_single(port->dev, sp->tx_dma.phys_addr,
			 sp->tx_dma.trans_len, DMA_TO_DEVICE);

	xmit->tail = (xmit->tail + sp->tx_dma.trans_len) & (UART_XMIT_SIZE - 1);
	port->icount.tx += sp->tx_dma.trans_len;

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (uart_circ_empty(xmit) || sprd_tx_buf_remap(port) ||
	    sprd_tx_dma_config(port))
		sp->tx_dma.trans_len = 0;

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल पूर्णांक sprd_uart_dma_submit(काष्ठा uart_port *port,
				काष्ठा sprd_uart_dma *ud, u32 trans_len,
				क्रमागत dma_transfer_direction direction,
				dma_async_tx_callback callback)
अणु
	काष्ठा dma_async_tx_descriptor *dma_des;
	अचिन्हित दीर्घ flags;

	flags = SPRD_DMA_FLAGS(SPRD_DMA_CHN_MODE_NONE,
			       SPRD_DMA_NO_TRG,
			       SPRD_DMA_FRAG_REQ,
			       SPRD_DMA_TRANS_INT);

	dma_des = dmaengine_prep_slave_single(ud->chn, ud->phys_addr, trans_len,
					      direction, flags);
	अगर (!dma_des)
		वापस -ENODEV;

	dma_des->callback = callback;
	dma_des->callback_param = port;

	ud->cookie = dmaengine_submit(dma_des);
	अगर (dma_submit_error(ud->cookie))
		वापस dma_submit_error(ud->cookie);

	dma_async_issue_pending(ud->chn);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_tx_dma_config(काष्ठा uart_port *port)
अणु
	काष्ठा sprd_uart_port *sp =
		container_of(port, काष्ठा sprd_uart_port, port);
	u32 burst = sp->tx_dma.trans_len > SPRD_TX_FIFO_FULL ?
		SPRD_TX_FIFO_FULL : sp->tx_dma.trans_len;
	पूर्णांक ret;
	काष्ठा dma_slave_config cfg = अणु
		.dst_addr = port->mapbase + SPRD_TXD,
		.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE,
		.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE,
		.src_maxburst = burst,
	पूर्ण;

	ret = dmaengine_slave_config(sp->tx_dma.chn, &cfg);
	अगर (ret < 0)
		वापस ret;

	वापस sprd_uart_dma_submit(port, &sp->tx_dma, sp->tx_dma.trans_len,
				    DMA_MEM_TO_DEV, sprd_complete_tx_dma);
पूर्ण

अटल व्योम sprd_start_tx_dma(काष्ठा uart_port *port)
अणु
	काष्ठा sprd_uart_port *sp =
		container_of(port, काष्ठा sprd_uart_port, port);
	काष्ठा circ_buf *xmit = &port->state->xmit;

	अगर (port->x_अक्षर) अणु
		serial_out(port, SPRD_TXD, port->x_अक्षर);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		sprd_stop_tx_dma(port);
		वापस;
	पूर्ण

	अगर (sp->tx_dma.trans_len)
		वापस;

	अगर (sprd_tx_buf_remap(port) || sprd_tx_dma_config(port))
		sp->tx_dma.trans_len = 0;
पूर्ण

अटल व्योम sprd_rx_full_thld(काष्ठा uart_port *port, u32 thld)
अणु
	u32 val = serial_in(port, SPRD_CTL2);

	val &= ~THLD_RX_FULL_MASK;
	val |= thld & THLD_RX_FULL_MASK;
	serial_out(port, SPRD_CTL2, val);
पूर्ण

अटल पूर्णांक sprd_rx_alloc_buf(काष्ठा sprd_uart_port *sp)
अणु
	sp->rx_dma.virt = dma_alloc_coherent(sp->port.dev, SPRD_UART_RX_SIZE,
					     &sp->rx_dma.phys_addr, GFP_KERNEL);
	अगर (!sp->rx_dma.virt)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम sprd_rx_मुक्त_buf(काष्ठा sprd_uart_port *sp)
अणु
	अगर (sp->rx_dma.virt)
		dma_मुक्त_coherent(sp->port.dev, SPRD_UART_RX_SIZE,
				  sp->rx_dma.virt, sp->rx_dma.phys_addr);

पूर्ण

अटल पूर्णांक sprd_rx_dma_config(काष्ठा uart_port *port, u32 burst)
अणु
	काष्ठा sprd_uart_port *sp =
		container_of(port, काष्ठा sprd_uart_port, port);
	काष्ठा dma_slave_config cfg = अणु
		.src_addr = port->mapbase + SPRD_RXD,
		.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE,
		.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE,
		.src_maxburst = burst,
	पूर्ण;

	वापस dmaengine_slave_config(sp->rx_dma.chn, &cfg);
पूर्ण

अटल व्योम sprd_uart_dma_rx(काष्ठा uart_port *port)
अणु
	काष्ठा sprd_uart_port *sp =
		container_of(port, काष्ठा sprd_uart_port, port);
	काष्ठा tty_port *tty = &port->state->port;

	port->icount.rx += sp->rx_dma.trans_len;
	tty_insert_flip_string(tty, sp->rx_buf_tail, sp->rx_dma.trans_len);
	tty_flip_buffer_push(tty);
पूर्ण

अटल व्योम sprd_uart_dma_irq(काष्ठा uart_port *port)
अणु
	काष्ठा sprd_uart_port *sp =
		container_of(port, काष्ठा sprd_uart_port, port);
	काष्ठा dma_tx_state state;
	क्रमागत dma_status status;

	status = dmaengine_tx_status(sp->rx_dma.chn,
				     sp->rx_dma.cookie, &state);
	अगर (status == DMA_ERROR)
		sprd_stop_rx(port);

	अगर (!state.residue && sp->pos == sp->rx_dma.phys_addr)
		वापस;

	अगर (!state.residue) अणु
		sp->rx_dma.trans_len = SPRD_UART_RX_SIZE +
			sp->rx_dma.phys_addr - sp->pos;
		sp->pos = sp->rx_dma.phys_addr;
	पूर्ण अन्यथा अणु
		sp->rx_dma.trans_len = state.residue - sp->pos;
		sp->pos = state.residue;
	पूर्ण

	sprd_uart_dma_rx(port);
	sp->rx_buf_tail += sp->rx_dma.trans_len;
पूर्ण

अटल व्योम sprd_complete_rx_dma(व्योम *data)
अणु
	काष्ठा uart_port *port = (काष्ठा uart_port *)data;
	काष्ठा sprd_uart_port *sp =
		container_of(port, काष्ठा sprd_uart_port, port);
	काष्ठा dma_tx_state state;
	क्रमागत dma_status status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	status = dmaengine_tx_status(sp->rx_dma.chn,
				     sp->rx_dma.cookie, &state);
	अगर (status != DMA_COMPLETE) अणु
		sprd_stop_rx(port);
		spin_unlock_irqrestore(&port->lock, flags);
		वापस;
	पूर्ण

	अगर (sp->pos != sp->rx_dma.phys_addr) अणु
		sp->rx_dma.trans_len =  SPRD_UART_RX_SIZE +
			sp->rx_dma.phys_addr - sp->pos;
		sprd_uart_dma_rx(port);
		sp->rx_buf_tail += sp->rx_dma.trans_len;
	पूर्ण

	अगर (sprd_start_dma_rx(port))
		sprd_stop_rx(port);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल पूर्णांक sprd_start_dma_rx(काष्ठा uart_port *port)
अणु
	काष्ठा sprd_uart_port *sp =
		container_of(port, काष्ठा sprd_uart_port, port);
	पूर्णांक ret;

	अगर (!sp->rx_dma.enable)
		वापस 0;

	sp->pos = sp->rx_dma.phys_addr;
	sp->rx_buf_tail = sp->rx_dma.virt;
	sprd_rx_full_thld(port, SPRD_RX_FIFO_FULL);
	ret = sprd_rx_dma_config(port, SPRD_RX_DMA_STEP);
	अगर (ret)
		वापस ret;

	वापस sprd_uart_dma_submit(port, &sp->rx_dma, SPRD_UART_RX_SIZE,
				    DMA_DEV_TO_MEM, sprd_complete_rx_dma);
पूर्ण

अटल व्योम sprd_release_dma(काष्ठा uart_port *port)
अणु
	काष्ठा sprd_uart_port *sp =
		container_of(port, काष्ठा sprd_uart_port, port);

	sprd_uart_dma_enable(port, false);

	अगर (sp->rx_dma.enable)
		dma_release_channel(sp->rx_dma.chn);

	अगर (sp->tx_dma.enable)
		dma_release_channel(sp->tx_dma.chn);

	sp->tx_dma.enable = false;
	sp->rx_dma.enable = false;
पूर्ण

अटल व्योम sprd_request_dma(काष्ठा uart_port *port)
अणु
	काष्ठा sprd_uart_port *sp =
		container_of(port, काष्ठा sprd_uart_port, port);

	sp->tx_dma.enable = true;
	sp->rx_dma.enable = true;

	sp->tx_dma.chn = dma_request_chan(port->dev, "tx");
	अगर (IS_ERR(sp->tx_dma.chn)) अणु
		dev_err(port->dev, "request TX DMA channel failed, ret = %ld\n",
			PTR_ERR(sp->tx_dma.chn));
		sp->tx_dma.enable = false;
	पूर्ण

	sp->rx_dma.chn = dma_request_chan(port->dev, "rx");
	अगर (IS_ERR(sp->rx_dma.chn)) अणु
		dev_err(port->dev, "request RX DMA channel failed, ret = %ld\n",
			PTR_ERR(sp->rx_dma.chn));
		sp->rx_dma.enable = false;
	पूर्ण
पूर्ण

अटल व्योम sprd_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा sprd_uart_port *sp = container_of(port, काष्ठा sprd_uart_port,
						 port);
	अचिन्हित पूर्णांक ien, iclr;

	अगर (sp->tx_dma.enable) अणु
		sprd_stop_tx_dma(port);
		वापस;
	पूर्ण

	iclr = serial_in(port, SPRD_ICLR);
	ien = serial_in(port, SPRD_IEN);

	iclr |= SPRD_IEN_TX_EMPTY;
	ien &= ~SPRD_IEN_TX_EMPTY;

	serial_out(port, SPRD_IEN, ien);
	serial_out(port, SPRD_ICLR, iclr);
पूर्ण

अटल व्योम sprd_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा sprd_uart_port *sp = container_of(port, काष्ठा sprd_uart_port,
						 port);
	अचिन्हित पूर्णांक ien;

	अगर (sp->tx_dma.enable) अणु
		sprd_start_tx_dma(port);
		वापस;
	पूर्ण

	ien = serial_in(port, SPRD_IEN);
	अगर (!(ien & SPRD_IEN_TX_EMPTY)) अणु
		ien |= SPRD_IEN_TX_EMPTY;
		serial_out(port, SPRD_IEN, ien);
	पूर्ण
पूर्ण

/* The Sprd serial करोes not support this function. */
अटल व्योम sprd_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	/* nothing to करो */
पूर्ण

अटल पूर्णांक handle_lsr_errors(काष्ठा uart_port *port,
			     अचिन्हित पूर्णांक *flag,
			     अचिन्हित पूर्णांक *lsr)
अणु
	पूर्णांक ret = 0;

	/* statistics */
	अगर (*lsr & SPRD_LSR_BI) अणु
		*lsr &= ~(SPRD_LSR_FE | SPRD_LSR_PE);
		port->icount.brk++;
		ret = uart_handle_अवरोध(port);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (*lsr & SPRD_LSR_PE)
		port->icount.parity++;
	अन्यथा अगर (*lsr & SPRD_LSR_FE)
		port->icount.frame++;
	अगर (*lsr & SPRD_LSR_OE)
		port->icount.overrun++;

	/* mask off conditions which should be ignored */
	*lsr &= port->पढ़ो_status_mask;
	अगर (*lsr & SPRD_LSR_BI)
		*flag = TTY_BREAK;
	अन्यथा अगर (*lsr & SPRD_LSR_PE)
		*flag = TTY_PARITY;
	अन्यथा अगर (*lsr & SPRD_LSR_FE)
		*flag = TTY_FRAME;

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम sprd_rx(काष्ठा uart_port *port)
अणु
	काष्ठा sprd_uart_port *sp = container_of(port, काष्ठा sprd_uart_port,
						 port);
	काष्ठा tty_port *tty = &port->state->port;
	अचिन्हित पूर्णांक ch, flag, lsr, max_count = SPRD_TIMEOUT;

	अगर (sp->rx_dma.enable) अणु
		sprd_uart_dma_irq(port);
		वापस;
	पूर्ण

	जबतक ((serial_in(port, SPRD_STS1) & SPRD_RX_FIFO_CNT_MASK) &&
	       max_count--) अणु
		lsr = serial_in(port, SPRD_LSR);
		ch = serial_in(port, SPRD_RXD);
		flag = TTY_NORMAL;
		port->icount.rx++;

		अगर (lsr & (SPRD_LSR_BI | SPRD_LSR_PE |
			   SPRD_LSR_FE | SPRD_LSR_OE))
			अगर (handle_lsr_errors(port, &flag, &lsr))
				जारी;
		अगर (uart_handle_sysrq_अक्षर(port, ch))
			जारी;

		uart_insert_अक्षर(port, lsr, SPRD_LSR_OE, ch, flag);
	पूर्ण

	tty_flip_buffer_push(tty);
पूर्ण

अटल अंतरभूत व्योम sprd_tx(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	पूर्णांक count;

	अगर (port->x_अक्षर) अणु
		serial_out(port, SPRD_TXD, port->x_अक्षर);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		sprd_stop_tx(port);
		वापस;
	पूर्ण

	count = THLD_TX_EMPTY;
	करो अणु
		serial_out(port, SPRD_TXD, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण जबतक (--count > 0);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (uart_circ_empty(xmit))
		sprd_stop_tx(port);
पूर्ण

/* this handles the पूर्णांकerrupt from one port */
अटल irqवापस_t sprd_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	अचिन्हित पूर्णांक ims;

	spin_lock(&port->lock);

	ims = serial_in(port, SPRD_IMSR);

	अगर (!ims) अणु
		spin_unlock(&port->lock);
		वापस IRQ_NONE;
	पूर्ण

	अगर (ims & SPRD_IMSR_TIMEOUT)
		serial_out(port, SPRD_ICLR, SPRD_ICLR_TIMEOUT);

	अगर (ims & SPRD_IMSR_BREAK_DETECT)
		serial_out(port, SPRD_ICLR, SPRD_IMSR_BREAK_DETECT);

	अगर (ims & (SPRD_IMSR_RX_FIFO_FULL | SPRD_IMSR_BREAK_DETECT |
		   SPRD_IMSR_TIMEOUT))
		sprd_rx(port);

	अगर (ims & SPRD_IMSR_TX_FIFO_EMPTY)
		sprd_tx(port);

	spin_unlock(&port->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sprd_uart_dma_startup(काष्ठा uart_port *port,
				  काष्ठा sprd_uart_port *sp)
अणु
	पूर्णांक ret;

	sprd_request_dma(port);
	अगर (!(sp->rx_dma.enable || sp->tx_dma.enable))
		वापस;

	ret = sprd_start_dma_rx(port);
	अगर (ret) अणु
		sp->rx_dma.enable = false;
		dma_release_channel(sp->rx_dma.chn);
		dev_warn(port->dev, "fail to start RX dma mode\n");
	पूर्ण

	sprd_uart_dma_enable(port, true);
पूर्ण

अटल पूर्णांक sprd_startup(काष्ठा uart_port *port)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक ien, fc;
	अचिन्हित पूर्णांक समयout;
	काष्ठा sprd_uart_port *sp;
	अचिन्हित दीर्घ flags;

	serial_out(port, SPRD_CTL2,
		   THLD_TX_EMPTY << THLD_TX_EMPTY_SHIFT | THLD_RX_FULL);

	/* clear rx fअगरo */
	समयout = SPRD_TIMEOUT;
	जबतक (समयout-- && serial_in(port, SPRD_STS1) & SPRD_RX_FIFO_CNT_MASK)
		serial_in(port, SPRD_RXD);

	/* clear tx fअगरo */
	समयout = SPRD_TIMEOUT;
	जबतक (समयout-- && serial_in(port, SPRD_STS1) & SPRD_TX_FIFO_CNT_MASK)
		cpu_relax();

	/* clear पूर्णांकerrupt */
	serial_out(port, SPRD_IEN, 0);
	serial_out(port, SPRD_ICLR, ~0);

	/* allocate irq */
	sp = container_of(port, काष्ठा sprd_uart_port, port);
	snम_लिखो(sp->name, माप(sp->name), "sprd_serial%d", port->line);

	sprd_uart_dma_startup(port, sp);

	ret = devm_request_irq(port->dev, port->irq, sprd_handle_irq,
			       IRQF_SHARED, sp->name, port);
	अगर (ret) अणु
		dev_err(port->dev, "fail to request serial irq %d, ret=%d\n",
			port->irq, ret);
		वापस ret;
	पूर्ण
	fc = serial_in(port, SPRD_CTL1);
	fc |= RX_TOUT_THLD_DEF | RX_HFC_THLD_DEF;
	serial_out(port, SPRD_CTL1, fc);

	/* enable पूर्णांकerrupt */
	spin_lock_irqsave(&port->lock, flags);
	ien = serial_in(port, SPRD_IEN);
	ien |= SPRD_IEN_BREAK_DETECT | SPRD_IEN_TIMEOUT;
	अगर (!sp->rx_dma.enable)
		ien |= SPRD_IEN_RX_FULL;
	serial_out(port, SPRD_IEN, ien);
	spin_unlock_irqrestore(&port->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम sprd_shutकरोwn(काष्ठा uart_port *port)
अणु
	sprd_release_dma(port);
	serial_out(port, SPRD_IEN, 0);
	serial_out(port, SPRD_ICLR, ~0);
	devm_मुक्त_irq(port->dev, port->irq, port);
पूर्ण

अटल व्योम sprd_set_termios(काष्ठा uart_port *port,
			     काष्ठा ktermios *termios,
			     काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक baud, quot;
	अचिन्हित पूर्णांक lcr = 0, fc;
	अचिन्हित दीर्घ flags;

	/* ask the core to calculate the भागisor क्रम us */
	baud = uart_get_baud_rate(port, termios, old, 0, SPRD_BAUD_IO_LIMIT);

	quot = port->uartclk / baud;

	/* set data length */
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		lcr |= SPRD_LCR_DATA_LEN5;
		अवरोध;
	हाल CS6:
		lcr |= SPRD_LCR_DATA_LEN6;
		अवरोध;
	हाल CS7:
		lcr |= SPRD_LCR_DATA_LEN7;
		अवरोध;
	हाल CS8:
	शेष:
		lcr |= SPRD_LCR_DATA_LEN8;
		अवरोध;
	पूर्ण

	/* calculate stop bits */
	lcr &= ~(SPRD_LCR_STOP_1BIT | SPRD_LCR_STOP_2BIT);
	अगर (termios->c_cflag & CSTOPB)
		lcr |= SPRD_LCR_STOP_2BIT;
	अन्यथा
		lcr |= SPRD_LCR_STOP_1BIT;

	/* calculate parity */
	lcr &= ~SPRD_LCR_PARITY;
	termios->c_cflag &= ~CMSPAR;	/* no support mark/space */
	अगर (termios->c_cflag & PARENB) अणु
		lcr |= SPRD_LCR_PARITY_EN;
		अगर (termios->c_cflag & PARODD)
			lcr |= SPRD_LCR_ODD_PAR;
		अन्यथा
			lcr |= SPRD_LCR_EVEN_PAR;
	पूर्ण

	spin_lock_irqsave(&port->lock, flags);

	/* update the per-port समयout */
	uart_update_समयout(port, termios->c_cflag, baud);

	port->पढ़ो_status_mask = SPRD_LSR_OE;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= SPRD_LSR_FE | SPRD_LSR_PE;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		port->पढ़ो_status_mask |= SPRD_LSR_BI;

	/* अक्षरacters to ignore */
	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= SPRD_LSR_PE | SPRD_LSR_FE;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		port->ignore_status_mask |= SPRD_LSR_BI;
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			port->ignore_status_mask |= SPRD_LSR_OE;
	पूर्ण

	/* flow control */
	fc = serial_in(port, SPRD_CTL1);
	fc &= ~(RX_HW_FLOW_CTL_THLD | RX_HW_FLOW_CTL_EN | TX_HW_FLOW_CTL_EN);
	अगर (termios->c_cflag & CRTSCTS) अणु
		fc |= RX_HW_FLOW_CTL_THLD;
		fc |= RX_HW_FLOW_CTL_EN;
		fc |= TX_HW_FLOW_CTL_EN;
	पूर्ण

	/* घड़ी भागider bit0~bit15 */
	serial_out(port, SPRD_CLKD0, quot & SPRD_CLKD0_MASK);

	/* घड़ी भागider bit16~bit20 */
	serial_out(port, SPRD_CLKD1,
		   (quot & SPRD_CLKD1_MASK) >> SPRD_CLKD1_SHIFT);
	serial_out(port, SPRD_LCR, lcr);
	fc |= RX_TOUT_THLD_DEF | RX_HFC_THLD_DEF;
	serial_out(port, SPRD_CTL1, fc);

	spin_unlock_irqrestore(&port->lock, flags);

	/* Don't reग_लिखो B0 */
	अगर (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);
पूर्ण

अटल स्थिर अक्षर *sprd_type(काष्ठा uart_port *port)
अणु
	वापस "SPX";
पूर्ण

अटल व्योम sprd_release_port(काष्ठा uart_port *port)
अणु
	/* nothing to करो */
पूर्ण

अटल पूर्णांक sprd_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम sprd_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE)
		port->type = PORT_SPRD;
पूर्ण

अटल पूर्णांक sprd_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	अगर (ser->type != PORT_SPRD)
		वापस -EINVAL;
	अगर (port->irq != ser->irq)
		वापस -EINVAL;
	अगर (port->iotype != ser->io_type)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम sprd_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
		अचिन्हित पूर्णांक oldstate)
अणु
	काष्ठा sprd_uart_port *sup =
		container_of(port, काष्ठा sprd_uart_port, port);

	चयन (state) अणु
	हाल UART_PM_STATE_ON:
		clk_prepare_enable(sup->clk);
		अवरोध;
	हाल UART_PM_STATE_OFF:
		clk_disable_unprepare(sup->clk);
		अवरोध;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
अटल पूर्णांक sprd_poll_init(काष्ठा uart_port *port)
अणु
	अगर (port->state->pm_state != UART_PM_STATE_ON) अणु
		sprd_pm(port, UART_PM_STATE_ON, 0);
		port->state->pm_state = UART_PM_STATE_ON;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_poll_get_अक्षर(काष्ठा uart_port *port)
अणु
	जबतक (!(serial_in(port, SPRD_STS1) & SPRD_RX_FIFO_CNT_MASK))
		cpu_relax();

	वापस serial_in(port, SPRD_RXD);
पूर्ण

अटल व्योम sprd_poll_put_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर ch)
अणु
	जबतक (serial_in(port, SPRD_STS1) & SPRD_TX_FIFO_CNT_MASK)
		cpu_relax();

	serial_out(port, SPRD_TXD, ch);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा uart_ops serial_sprd_ops = अणु
	.tx_empty = sprd_tx_empty,
	.get_mctrl = sprd_get_mctrl,
	.set_mctrl = sprd_set_mctrl,
	.stop_tx = sprd_stop_tx,
	.start_tx = sprd_start_tx,
	.stop_rx = sprd_stop_rx,
	.अवरोध_ctl = sprd_अवरोध_ctl,
	.startup = sprd_startup,
	.shutकरोwn = sprd_shutकरोwn,
	.set_termios = sprd_set_termios,
	.type = sprd_type,
	.release_port = sprd_release_port,
	.request_port = sprd_request_port,
	.config_port = sprd_config_port,
	.verअगरy_port = sprd_verअगरy_port,
	.pm = sprd_pm,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_init	= sprd_poll_init,
	.poll_get_अक्षर	= sprd_poll_get_अक्षर,
	.poll_put_अक्षर	= sprd_poll_put_अक्षर,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_SPRD_CONSOLE
अटल व्योम रुको_क्रम_xmitr(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक status, पंचांगout = 10000;

	/* रुको up to 10ms क्रम the अक्षरacter(s) to be sent */
	करो अणु
		status = serial_in(port, SPRD_STS1);
		अगर (--पंचांगout == 0)
			अवरोध;
		udelay(1);
	पूर्ण जबतक (status & SPRD_TX_FIFO_CNT_MASK);
पूर्ण

अटल व्योम sprd_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	रुको_क्रम_xmitr(port);
	serial_out(port, SPRD_TXD, ch);
पूर्ण

अटल व्योम sprd_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
			       अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_port *port = &sprd_port[co->index]->port;
	पूर्णांक locked = 1;
	अचिन्हित दीर्घ flags;

	अगर (port->sysrq)
		locked = 0;
	अन्यथा अगर (oops_in_progress)
		locked = spin_trylock_irqsave(&port->lock, flags);
	अन्यथा
		spin_lock_irqsave(&port->lock, flags);

	uart_console_ग_लिखो(port, s, count, sprd_console_अक्षर_दो);

	/* रुको क्रम transmitter to become empty */
	रुको_क्रम_xmitr(port);

	अगर (locked)
		spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल पूर्णांक sprd_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा sprd_uart_port *sprd_uart_port;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (co->index >= UART_NR_MAX || co->index < 0)
		co->index = 0;

	sprd_uart_port = sprd_port[co->index];
	अगर (!sprd_uart_port || !sprd_uart_port->port.membase) अणु
		pr_info("serial port %d not yet initialized\n", co->index);
		वापस -ENODEV;
	पूर्ण

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(&sprd_uart_port->port, co, baud,
				parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver sprd_uart_driver;
अटल काष्ठा console sprd_console = अणु
	.name = SPRD_TTY_NAME,
	.ग_लिखो = sprd_console_ग_लिखो,
	.device = uart_console_device,
	.setup = sprd_console_setup,
	.flags = CON_PRINTBUFFER,
	.index = -1,
	.data = &sprd_uart_driver,
पूर्ण;

अटल पूर्णांक __init sprd_serial_console_init(व्योम)
अणु
	रेजिस्टर_console(&sprd_console);
	वापस 0;
पूर्ण
console_initcall(sprd_serial_console_init);

#घोषणा SPRD_CONSOLE	(&sprd_console)

/* Support क्रम earlycon */
अटल व्योम sprd_अ_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	अचिन्हित पूर्णांक समयout = SPRD_TIMEOUT;

	जबतक (समयout-- &&
	       !(पढ़ोl(port->membase + SPRD_LSR) & SPRD_LSR_TX_OVER))
		cpu_relax();

	ग_लिखोb(c, port->membase + SPRD_TXD);
पूर्ण

अटल व्योम sprd_early_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित पूर्णांक n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	uart_console_ग_लिखो(&dev->port, s, n, sprd_अ_दो);
पूर्ण

अटल पूर्णांक __init sprd_early_console_setup(काष्ठा earlycon_device *device,
					   स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->con->ग_लिखो = sprd_early_ग_लिखो;
	वापस 0;
पूर्ण
OF_EARLYCON_DECLARE(sprd_serial, "sprd,sc9836-uart",
		    sprd_early_console_setup);

#अन्यथा /* !CONFIG_SERIAL_SPRD_CONSOLE */
#घोषणा SPRD_CONSOLE		शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver sprd_uart_driver = अणु
	.owner = THIS_MODULE,
	.driver_name = "sprd_serial",
	.dev_name = SPRD_TTY_NAME,
	.major = 0,
	.minor = 0,
	.nr = UART_NR_MAX,
	.cons = SPRD_CONSOLE,
पूर्ण;

अटल पूर्णांक sprd_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा sprd_uart_port *sup = platक्रमm_get_drvdata(dev);

	अगर (sup) अणु
		uart_हटाओ_one_port(&sprd_uart_driver, &sup->port);
		sprd_port[sup->port.line] = शून्य;
		sprd_rx_मुक्त_buf(sup);
		sprd_ports_num--;
	पूर्ण

	अगर (!sprd_ports_num)
		uart_unरेजिस्टर_driver(&sprd_uart_driver);

	वापस 0;
पूर्ण

अटल bool sprd_uart_is_console(काष्ठा uart_port *uport)
अणु
	काष्ठा console *cons = sprd_uart_driver.cons;

	अगर ((cons && cons->index >= 0 && cons->index == uport->line) ||
	    of_console_check(uport->dev->of_node, SPRD_TTY_NAME, uport->line))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक sprd_clk_init(काष्ठा uart_port *uport)
अणु
	काष्ठा clk *clk_uart, *clk_parent;
	काष्ठा sprd_uart_port *u = sprd_port[uport->line];

	clk_uart = devm_clk_get(uport->dev, "uart");
	अगर (IS_ERR(clk_uart)) अणु
		dev_warn(uport->dev, "uart%d can't get uart clock\n",
			 uport->line);
		clk_uart = शून्य;
	पूर्ण

	clk_parent = devm_clk_get(uport->dev, "source");
	अगर (IS_ERR(clk_parent)) अणु
		dev_warn(uport->dev, "uart%d can't get source clock\n",
			 uport->line);
		clk_parent = शून्य;
	पूर्ण

	अगर (!clk_uart || clk_set_parent(clk_uart, clk_parent))
		uport->uartclk = SPRD_DEFAULT_SOURCE_CLK;
	अन्यथा
		uport->uartclk = clk_get_rate(clk_uart);

	u->clk = devm_clk_get(uport->dev, "enable");
	अगर (IS_ERR(u->clk)) अणु
		अगर (PTR_ERR(u->clk) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		dev_warn(uport->dev, "uart%d can't get enable clock\n",
			uport->line);

		/* To keep console alive even अगर the error occurred */
		अगर (!sprd_uart_is_console(uport))
			वापस PTR_ERR(u->clk);

		u->clk = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा uart_port *up;
	पूर्णांक irq;
	पूर्णांक index;
	पूर्णांक ret;

	index = of_alias_get_id(pdev->dev.of_node, "serial");
	अगर (index < 0 || index >= ARRAY_SIZE(sprd_port)) अणु
		dev_err(&pdev->dev, "got a wrong serial alias id %d\n", index);
		वापस -EINVAL;
	पूर्ण

	sprd_port[index] = devm_kzalloc(&pdev->dev, माप(*sprd_port[index]),
					GFP_KERNEL);
	अगर (!sprd_port[index])
		वापस -ENOMEM;

	up = &sprd_port[index]->port;
	up->dev = &pdev->dev;
	up->line = index;
	up->type = PORT_SPRD;
	up->iotype = UPIO_MEM;
	up->uartclk = SPRD_DEF_RATE;
	up->fअगरosize = SPRD_FIFO_SIZE;
	up->ops = &serial_sprd_ops;
	up->flags = UPF_BOOT_AUTOCONF;
	up->has_sysrq = IS_ENABLED(CONFIG_SERIAL_SPRD_CONSOLE);

	ret = sprd_clk_init(up);
	अगर (ret)
		वापस ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	up->membase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(up->membase))
		वापस PTR_ERR(up->membase);

	up->mapbase = res->start;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	up->irq = irq;

	/*
	 * Allocate one dma buffer to prepare क्रम receive transfer, in हाल
	 * memory allocation failure at runसमय.
	 */
	ret = sprd_rx_alloc_buf(sprd_port[index]);
	अगर (ret)
		वापस ret;

	अगर (!sprd_ports_num) अणु
		ret = uart_रेजिस्टर_driver(&sprd_uart_driver);
		अगर (ret < 0) अणु
			pr_err("Failed to register SPRD-UART driver\n");
			वापस ret;
		पूर्ण
	पूर्ण
	sprd_ports_num++;

	ret = uart_add_one_port(&sprd_uart_driver, up);
	अगर (ret)
		sprd_हटाओ(pdev);

	platक्रमm_set_drvdata(pdev, up);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sprd_suspend(काष्ठा device *dev)
अणु
	काष्ठा sprd_uart_port *sup = dev_get_drvdata(dev);

	uart_suspend_port(&sprd_uart_driver, &sup->port);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_resume(काष्ठा device *dev)
अणु
	काष्ठा sprd_uart_port *sup = dev_get_drvdata(dev);

	uart_resume_port(&sprd_uart_driver, &sup->port);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sprd_pm_ops, sprd_suspend, sprd_resume);

अटल स्थिर काष्ठा of_device_id serial_ids[] = अणु
	अणु.compatible = "sprd,sc9836-uart",पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, serial_ids);

अटल काष्ठा platक्रमm_driver sprd_platक्रमm_driver = अणु
	.probe		= sprd_probe,
	.हटाओ		= sprd_हटाओ,
	.driver		= अणु
		.name	= "sprd_serial",
		.of_match_table = of_match_ptr(serial_ids),
		.pm	= &sprd_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sprd_platक्रमm_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Spreadtrum SoC serial driver series");
