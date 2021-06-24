<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम msm7k serial device and console
 *
 * Copyright (C) 2007 Google, Inc.
 * Author: Robert Love <rlove@google.com>
 * Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/atomic.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/रुको.h>

#घोषणा UART_MR1			0x0000

#घोषणा UART_MR1_AUTO_RFR_LEVEL0	0x3F
#घोषणा UART_MR1_AUTO_RFR_LEVEL1	0x3FF00
#घोषणा UART_DM_MR1_AUTO_RFR_LEVEL1	0xFFFFFF00
#घोषणा UART_MR1_RX_RDY_CTL		BIT(7)
#घोषणा UART_MR1_CTS_CTL		BIT(6)

#घोषणा UART_MR2			0x0004
#घोषणा UART_MR2_ERROR_MODE		BIT(6)
#घोषणा UART_MR2_BITS_PER_CHAR		0x30
#घोषणा UART_MR2_BITS_PER_CHAR_5	(0x0 << 4)
#घोषणा UART_MR2_BITS_PER_CHAR_6	(0x1 << 4)
#घोषणा UART_MR2_BITS_PER_CHAR_7	(0x2 << 4)
#घोषणा UART_MR2_BITS_PER_CHAR_8	(0x3 << 4)
#घोषणा UART_MR2_STOP_BIT_LEN_ONE	(0x1 << 2)
#घोषणा UART_MR2_STOP_BIT_LEN_TWO	(0x3 << 2)
#घोषणा UART_MR2_PARITY_MODE_NONE	0x0
#घोषणा UART_MR2_PARITY_MODE_ODD	0x1
#घोषणा UART_MR2_PARITY_MODE_EVEN	0x2
#घोषणा UART_MR2_PARITY_MODE_SPACE	0x3
#घोषणा UART_MR2_PARITY_MODE		0x3

#घोषणा UART_CSR			0x0008

#घोषणा UART_TF				0x000C
#घोषणा UARTDM_TF			0x0070

#घोषणा UART_CR				0x0010
#घोषणा UART_CR_CMD_शून्य		(0 << 4)
#घोषणा UART_CR_CMD_RESET_RX		(1 << 4)
#घोषणा UART_CR_CMD_RESET_TX		(2 << 4)
#घोषणा UART_CR_CMD_RESET_ERR		(3 << 4)
#घोषणा UART_CR_CMD_RESET_BREAK_INT	(4 << 4)
#घोषणा UART_CR_CMD_START_BREAK		(5 << 4)
#घोषणा UART_CR_CMD_STOP_BREAK		(6 << 4)
#घोषणा UART_CR_CMD_RESET_CTS		(7 << 4)
#घोषणा UART_CR_CMD_RESET_STALE_INT	(8 << 4)
#घोषणा UART_CR_CMD_PACKET_MODE		(9 << 4)
#घोषणा UART_CR_CMD_MODE_RESET		(12 << 4)
#घोषणा UART_CR_CMD_SET_RFR		(13 << 4)
#घोषणा UART_CR_CMD_RESET_RFR		(14 << 4)
#घोषणा UART_CR_CMD_PROTECTION_EN	(16 << 4)
#घोषणा UART_CR_CMD_STALE_EVENT_DISABLE	(6 << 8)
#घोषणा UART_CR_CMD_STALE_EVENT_ENABLE	(80 << 4)
#घोषणा UART_CR_CMD_FORCE_STALE		(4 << 8)
#घोषणा UART_CR_CMD_RESET_TX_READY	(3 << 8)
#घोषणा UART_CR_TX_DISABLE		BIT(3)
#घोषणा UART_CR_TX_ENABLE		BIT(2)
#घोषणा UART_CR_RX_DISABLE		BIT(1)
#घोषणा UART_CR_RX_ENABLE		BIT(0)
#घोषणा UART_CR_CMD_RESET_RXBREAK_START	((1 << 11) | (2 << 4))

#घोषणा UART_IMR			0x0014
#घोषणा UART_IMR_TXLEV			BIT(0)
#घोषणा UART_IMR_RXSTALE		BIT(3)
#घोषणा UART_IMR_RXLEV			BIT(4)
#घोषणा UART_IMR_DELTA_CTS		BIT(5)
#घोषणा UART_IMR_CURRENT_CTS		BIT(6)
#घोषणा UART_IMR_RXBREAK_START		BIT(10)

#घोषणा UART_IPR_RXSTALE_LAST		0x20
#घोषणा UART_IPR_STALE_LSB		0x1F
#घोषणा UART_IPR_STALE_TIMEOUT_MSB	0x3FF80
#घोषणा UART_DM_IPR_STALE_TIMEOUT_MSB	0xFFFFFF80

#घोषणा UART_IPR			0x0018
#घोषणा UART_TFWR			0x001C
#घोषणा UART_RFWR			0x0020
#घोषणा UART_HCR			0x0024

#घोषणा UART_MREG			0x0028
#घोषणा UART_NREG			0x002C
#घोषणा UART_DREG			0x0030
#घोषणा UART_MNDREG			0x0034
#घोषणा UART_IRDA			0x0038
#घोषणा UART_MISR_MODE			0x0040
#घोषणा UART_MISR_RESET			0x0044
#घोषणा UART_MISR_EXPORT		0x0048
#घोषणा UART_MISR_VAL			0x004C
#घोषणा UART_TEST_CTRL			0x0050

#घोषणा UART_SR				0x0008
#घोषणा UART_SR_HUNT_CHAR		BIT(7)
#घोषणा UART_SR_RX_BREAK		BIT(6)
#घोषणा UART_SR_PAR_FRAME_ERR		BIT(5)
#घोषणा UART_SR_OVERRUN			BIT(4)
#घोषणा UART_SR_TX_EMPTY		BIT(3)
#घोषणा UART_SR_TX_READY		BIT(2)
#घोषणा UART_SR_RX_FULL			BIT(1)
#घोषणा UART_SR_RX_READY		BIT(0)

#घोषणा UART_RF				0x000C
#घोषणा UARTDM_RF			0x0070
#घोषणा UART_MISR			0x0010
#घोषणा UART_ISR			0x0014
#घोषणा UART_ISR_TX_READY		BIT(7)

#घोषणा UARTDM_RXFS			0x50
#घोषणा UARTDM_RXFS_BUF_SHIFT		0x7
#घोषणा UARTDM_RXFS_BUF_MASK		0x7

#घोषणा UARTDM_DMEN			0x3C
#घोषणा UARTDM_DMEN_RX_SC_ENABLE	BIT(5)
#घोषणा UARTDM_DMEN_TX_SC_ENABLE	BIT(4)

#घोषणा UARTDM_DMEN_TX_BAM_ENABLE	BIT(2)	/* UARTDM_1P4 */
#घोषणा UARTDM_DMEN_TX_DM_ENABLE	BIT(0)	/* < UARTDM_1P4 */

#घोषणा UARTDM_DMEN_RX_BAM_ENABLE	BIT(3)	/* UARTDM_1P4 */
#घोषणा UARTDM_DMEN_RX_DM_ENABLE	BIT(1)	/* < UARTDM_1P4 */

#घोषणा UARTDM_DMRX			0x34
#घोषणा UARTDM_NCF_TX			0x40
#घोषणा UARTDM_RX_TOTAL_SNAP		0x38

#घोषणा UARTDM_BURST_SIZE		16   /* in bytes */
#घोषणा UARTDM_TX_AIGN(x)		((x) & ~0x3) /* valid क्रम > 1p3 */
#घोषणा UARTDM_TX_MAX			256   /* in bytes, valid क्रम <= 1p3 */
#घोषणा UARTDM_RX_SIZE			(UART_XMIT_SIZE / 4)

क्रमागत अणु
	UARTDM_1P1 = 1,
	UARTDM_1P2,
	UARTDM_1P3,
	UARTDM_1P4,
पूर्ण;

काष्ठा msm_dma अणु
	काष्ठा dma_chan		*chan;
	क्रमागत dma_data_direction dir;
	dma_addr_t		phys;
	अचिन्हित अक्षर		*virt;
	dma_cookie_t		cookie;
	u32			enable_bit;
	अचिन्हित पूर्णांक		count;
	काष्ठा dma_async_tx_descriptor	*desc;
पूर्ण;

काष्ठा msm_port अणु
	काष्ठा uart_port	uart;
	अक्षर			name[16];
	काष्ठा clk		*clk;
	काष्ठा clk		*pclk;
	अचिन्हित पूर्णांक		imr;
	पूर्णांक			is_uartdm;
	अचिन्हित पूर्णांक		old_snap_state;
	bool			अवरोध_detected;
	काष्ठा msm_dma		tx_dma;
	काष्ठा msm_dma		rx_dma;
पूर्ण;

#घोषणा UART_TO_MSM(uart_port)	container_of(uart_port, काष्ठा msm_port, uart)

अटल
व्योम msm_ग_लिखो(काष्ठा uart_port *port, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक off)
अणु
	ग_लिखोl_relaxed(val, port->membase + off);
पूर्ण

अटल
अचिन्हित पूर्णांक msm_पढ़ो(काष्ठा uart_port *port, अचिन्हित पूर्णांक off)
अणु
	वापस पढ़ोl_relaxed(port->membase + off);
पूर्ण

/*
 * Setup the MND रेजिस्टरs to use the TCXO घड़ी.
 */
अटल व्योम msm_serial_set_mnd_regs_tcxo(काष्ठा uart_port *port)
अणु
	msm_ग_लिखो(port, 0x06, UART_MREG);
	msm_ग_लिखो(port, 0xF1, UART_NREG);
	msm_ग_लिखो(port, 0x0F, UART_DREG);
	msm_ग_लिखो(port, 0x1A, UART_MNDREG);
	port->uartclk = 1843200;
पूर्ण

/*
 * Setup the MND रेजिस्टरs to use the TCXO घड़ी भागided by 4.
 */
अटल व्योम msm_serial_set_mnd_regs_tcxoby4(काष्ठा uart_port *port)
अणु
	msm_ग_लिखो(port, 0x18, UART_MREG);
	msm_ग_लिखो(port, 0xF6, UART_NREG);
	msm_ग_लिखो(port, 0x0F, UART_DREG);
	msm_ग_लिखो(port, 0x0A, UART_MNDREG);
	port->uartclk = 1843200;
पूर्ण

अटल व्योम msm_serial_set_mnd_regs(काष्ठा uart_port *port)
अणु
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);

	/*
	 * These रेजिस्टरs करोn't exist so we change the clk input rate
	 * on uartdm hardware instead
	 */
	अगर (msm_port->is_uartdm)
		वापस;

	अगर (port->uartclk == 19200000)
		msm_serial_set_mnd_regs_tcxo(port);
	अन्यथा अगर (port->uartclk == 4800000)
		msm_serial_set_mnd_regs_tcxoby4(port);
पूर्ण

अटल व्योम msm_handle_tx(काष्ठा uart_port *port);
अटल व्योम msm_start_rx_dma(काष्ठा msm_port *msm_port);

अटल व्योम msm_stop_dma(काष्ठा uart_port *port, काष्ठा msm_dma *dma)
अणु
	काष्ठा device *dev = port->dev;
	अचिन्हित पूर्णांक mapped;
	u32 val;

	mapped = dma->count;
	dma->count = 0;

	dmaengine_terminate_all(dma->chan);

	/*
	 * DMA Stall happens अगर enqueue and flush command happens concurrently.
	 * For example beक्रमe changing the baud rate/protocol configuration and
	 * sending flush command to ADM, disable the channel of UARTDM.
	 * Note: should not reset the receiver here immediately as it is not
	 * suggested to करो disable/reset or reset/disable at the same समय.
	 */
	val = msm_पढ़ो(port, UARTDM_DMEN);
	val &= ~dma->enable_bit;
	msm_ग_लिखो(port, val, UARTDM_DMEN);

	अगर (mapped)
		dma_unmap_single(dev, dma->phys, mapped, dma->dir);
पूर्ण

अटल व्योम msm_release_dma(काष्ठा msm_port *msm_port)
अणु
	काष्ठा msm_dma *dma;

	dma = &msm_port->tx_dma;
	अगर (dma->chan) अणु
		msm_stop_dma(&msm_port->uart, dma);
		dma_release_channel(dma->chan);
	पूर्ण

	स_रखो(dma, 0, माप(*dma));

	dma = &msm_port->rx_dma;
	अगर (dma->chan) अणु
		msm_stop_dma(&msm_port->uart, dma);
		dma_release_channel(dma->chan);
		kमुक्त(dma->virt);
	पूर्ण

	स_रखो(dma, 0, माप(*dma));
पूर्ण

अटल व्योम msm_request_tx_dma(काष्ठा msm_port *msm_port, resource_माप_प्रकार base)
अणु
	काष्ठा device *dev = msm_port->uart.dev;
	काष्ठा dma_slave_config conf;
	काष्ठा msm_dma *dma;
	u32 crci = 0;
	पूर्णांक ret;

	dma = &msm_port->tx_dma;

	/* allocate DMA resources, अगर available */
	dma->chan = dma_request_chan(dev, "tx");
	अगर (IS_ERR(dma->chan))
		जाओ no_tx;

	of_property_पढ़ो_u32(dev->of_node, "qcom,tx-crci", &crci);

	स_रखो(&conf, 0, माप(conf));
	conf.direction = DMA_MEM_TO_DEV;
	conf.device_fc = true;
	conf.dst_addr = base + UARTDM_TF;
	conf.dst_maxburst = UARTDM_BURST_SIZE;
	conf.slave_id = crci;

	ret = dmaengine_slave_config(dma->chan, &conf);
	अगर (ret)
		जाओ rel_tx;

	dma->dir = DMA_TO_DEVICE;

	अगर (msm_port->is_uartdm < UARTDM_1P4)
		dma->enable_bit = UARTDM_DMEN_TX_DM_ENABLE;
	अन्यथा
		dma->enable_bit = UARTDM_DMEN_TX_BAM_ENABLE;

	वापस;

rel_tx:
	dma_release_channel(dma->chan);
no_tx:
	स_रखो(dma, 0, माप(*dma));
पूर्ण

अटल व्योम msm_request_rx_dma(काष्ठा msm_port *msm_port, resource_माप_प्रकार base)
अणु
	काष्ठा device *dev = msm_port->uart.dev;
	काष्ठा dma_slave_config conf;
	काष्ठा msm_dma *dma;
	u32 crci = 0;
	पूर्णांक ret;

	dma = &msm_port->rx_dma;

	/* allocate DMA resources, अगर available */
	dma->chan = dma_request_chan(dev, "rx");
	अगर (IS_ERR(dma->chan))
		जाओ no_rx;

	of_property_पढ़ो_u32(dev->of_node, "qcom,rx-crci", &crci);

	dma->virt = kzalloc(UARTDM_RX_SIZE, GFP_KERNEL);
	अगर (!dma->virt)
		जाओ rel_rx;

	स_रखो(&conf, 0, माप(conf));
	conf.direction = DMA_DEV_TO_MEM;
	conf.device_fc = true;
	conf.src_addr = base + UARTDM_RF;
	conf.src_maxburst = UARTDM_BURST_SIZE;
	conf.slave_id = crci;

	ret = dmaengine_slave_config(dma->chan, &conf);
	अगर (ret)
		जाओ err;

	dma->dir = DMA_FROM_DEVICE;

	अगर (msm_port->is_uartdm < UARTDM_1P4)
		dma->enable_bit = UARTDM_DMEN_RX_DM_ENABLE;
	अन्यथा
		dma->enable_bit = UARTDM_DMEN_RX_BAM_ENABLE;

	वापस;
err:
	kमुक्त(dma->virt);
rel_rx:
	dma_release_channel(dma->chan);
no_rx:
	स_रखो(dma, 0, माप(*dma));
पूर्ण

अटल अंतरभूत व्योम msm_रुको_क्रम_xmitr(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक समयout = 500000;

	जबतक (!(msm_पढ़ो(port, UART_SR) & UART_SR_TX_EMPTY)) अणु
		अगर (msm_पढ़ो(port, UART_ISR) & UART_ISR_TX_READY)
			अवरोध;
		udelay(1);
		अगर (!समयout--)
			अवरोध;
	पूर्ण
	msm_ग_लिखो(port, UART_CR_CMD_RESET_TX_READY, UART_CR);
पूर्ण

अटल व्योम msm_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);

	msm_port->imr &= ~UART_IMR_TXLEV;
	msm_ग_लिखो(port, msm_port->imr, UART_IMR);
पूर्ण

अटल व्योम msm_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);
	काष्ठा msm_dma *dma = &msm_port->tx_dma;

	/* Alपढ़ोy started in DMA mode */
	अगर (dma->count)
		वापस;

	msm_port->imr |= UART_IMR_TXLEV;
	msm_ग_लिखो(port, msm_port->imr, UART_IMR);
पूर्ण

अटल व्योम msm_reset_dm_count(काष्ठा uart_port *port, पूर्णांक count)
अणु
	msm_रुको_क्रम_xmitr(port);
	msm_ग_लिखो(port, count, UARTDM_NCF_TX);
	msm_पढ़ो(port, UARTDM_NCF_TX);
पूर्ण

अटल व्योम msm_complete_tx_dma(व्योम *args)
अणु
	काष्ठा msm_port *msm_port = args;
	काष्ठा uart_port *port = &msm_port->uart;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	काष्ठा msm_dma *dma = &msm_port->tx_dma;
	काष्ठा dma_tx_state state;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक count;
	u32 val;

	spin_lock_irqsave(&port->lock, flags);

	/* Alपढ़ोy stopped */
	अगर (!dma->count)
		जाओ करोne;

	dmaengine_tx_status(dma->chan, dma->cookie, &state);

	dma_unmap_single(port->dev, dma->phys, dma->count, dma->dir);

	val = msm_पढ़ो(port, UARTDM_DMEN);
	val &= ~dma->enable_bit;
	msm_ग_लिखो(port, val, UARTDM_DMEN);

	अगर (msm_port->is_uartdm > UARTDM_1P3) अणु
		msm_ग_लिखो(port, UART_CR_CMD_RESET_TX, UART_CR);
		msm_ग_लिखो(port, UART_CR_TX_ENABLE, UART_CR);
	पूर्ण

	count = dma->count - state.residue;
	port->icount.tx += count;
	dma->count = 0;

	xmit->tail += count;
	xmit->tail &= UART_XMIT_SIZE - 1;

	/* Restore "Tx FIFO below watermark" पूर्णांकerrupt */
	msm_port->imr |= UART_IMR_TXLEV;
	msm_ग_लिखो(port, msm_port->imr, UART_IMR);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	msm_handle_tx(port);
करोne:
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल पूर्णांक msm_handle_tx_dma(काष्ठा msm_port *msm_port, अचिन्हित पूर्णांक count)
अणु
	काष्ठा circ_buf *xmit = &msm_port->uart.state->xmit;
	काष्ठा uart_port *port = &msm_port->uart;
	काष्ठा msm_dma *dma = &msm_port->tx_dma;
	व्योम *cpu_addr;
	पूर्णांक ret;
	u32 val;

	cpu_addr = &xmit->buf[xmit->tail];

	dma->phys = dma_map_single(port->dev, cpu_addr, count, dma->dir);
	ret = dma_mapping_error(port->dev, dma->phys);
	अगर (ret)
		वापस ret;

	dma->desc = dmaengine_prep_slave_single(dma->chan, dma->phys,
						count, DMA_MEM_TO_DEV,
						DMA_PREP_INTERRUPT |
						DMA_PREP_FENCE);
	अगर (!dma->desc) अणु
		ret = -EIO;
		जाओ unmap;
	पूर्ण

	dma->desc->callback = msm_complete_tx_dma;
	dma->desc->callback_param = msm_port;

	dma->cookie = dmaengine_submit(dma->desc);
	ret = dma_submit_error(dma->cookie);
	अगर (ret)
		जाओ unmap;

	/*
	 * Using DMA complete क्रम Tx FIFO reload, no need क्रम
	 * "Tx FIFO below watermark" one, disable it
	 */
	msm_port->imr &= ~UART_IMR_TXLEV;
	msm_ग_लिखो(port, msm_port->imr, UART_IMR);

	dma->count = count;

	val = msm_पढ़ो(port, UARTDM_DMEN);
	val |= dma->enable_bit;

	अगर (msm_port->is_uartdm < UARTDM_1P4)
		msm_ग_लिखो(port, val, UARTDM_DMEN);

	msm_reset_dm_count(port, count);

	अगर (msm_port->is_uartdm > UARTDM_1P3)
		msm_ग_लिखो(port, val, UARTDM_DMEN);

	dma_async_issue_pending(dma->chan);
	वापस 0;
unmap:
	dma_unmap_single(port->dev, dma->phys, count, dma->dir);
	वापस ret;
पूर्ण

अटल व्योम msm_complete_rx_dma(व्योम *args)
अणु
	काष्ठा msm_port *msm_port = args;
	काष्ठा uart_port *port = &msm_port->uart;
	काष्ठा tty_port *tport = &port->state->port;
	काष्ठा msm_dma *dma = &msm_port->rx_dma;
	पूर्णांक count = 0, i, sysrq;
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&port->lock, flags);

	/* Alपढ़ोy stopped */
	अगर (!dma->count)
		जाओ करोne;

	val = msm_पढ़ो(port, UARTDM_DMEN);
	val &= ~dma->enable_bit;
	msm_ग_लिखो(port, val, UARTDM_DMEN);

	अगर (msm_पढ़ो(port, UART_SR) & UART_SR_OVERRUN) अणु
		port->icount.overrun++;
		tty_insert_flip_अक्षर(tport, 0, TTY_OVERRUN);
		msm_ग_लिखो(port, UART_CR_CMD_RESET_ERR, UART_CR);
	पूर्ण

	count = msm_पढ़ो(port, UARTDM_RX_TOTAL_SNAP);

	port->icount.rx += count;

	dma->count = 0;

	dma_unmap_single(port->dev, dma->phys, UARTDM_RX_SIZE, dma->dir);

	क्रम (i = 0; i < count; i++) अणु
		अक्षर flag = TTY_NORMAL;

		अगर (msm_port->अवरोध_detected && dma->virt[i] == 0) अणु
			port->icount.brk++;
			flag = TTY_BREAK;
			msm_port->अवरोध_detected = false;
			अगर (uart_handle_अवरोध(port))
				जारी;
		पूर्ण

		अगर (!(port->पढ़ो_status_mask & UART_SR_RX_BREAK))
			flag = TTY_NORMAL;

		spin_unlock_irqrestore(&port->lock, flags);
		sysrq = uart_handle_sysrq_अक्षर(port, dma->virt[i]);
		spin_lock_irqsave(&port->lock, flags);
		अगर (!sysrq)
			tty_insert_flip_अक्षर(tport, dma->virt[i], flag);
	पूर्ण

	msm_start_rx_dma(msm_port);
करोne:
	spin_unlock_irqrestore(&port->lock, flags);

	अगर (count)
		tty_flip_buffer_push(tport);
पूर्ण

अटल व्योम msm_start_rx_dma(काष्ठा msm_port *msm_port)
अणु
	काष्ठा msm_dma *dma = &msm_port->rx_dma;
	काष्ठा uart_port *uart = &msm_port->uart;
	u32 val;
	पूर्णांक ret;

	अगर (!dma->chan)
		वापस;

	dma->phys = dma_map_single(uart->dev, dma->virt,
				   UARTDM_RX_SIZE, dma->dir);
	ret = dma_mapping_error(uart->dev, dma->phys);
	अगर (ret)
		जाओ sw_mode;

	dma->desc = dmaengine_prep_slave_single(dma->chan, dma->phys,
						UARTDM_RX_SIZE, DMA_DEV_TO_MEM,
						DMA_PREP_INTERRUPT);
	अगर (!dma->desc)
		जाओ unmap;

	dma->desc->callback = msm_complete_rx_dma;
	dma->desc->callback_param = msm_port;

	dma->cookie = dmaengine_submit(dma->desc);
	ret = dma_submit_error(dma->cookie);
	अगर (ret)
		जाओ unmap;
	/*
	 * Using DMA क्रम FIFO off-load, no need क्रम "Rx FIFO over
	 * watermark" or "stale" पूर्णांकerrupts, disable them
	 */
	msm_port->imr &= ~(UART_IMR_RXLEV | UART_IMR_RXSTALE);

	/*
	 * Well, when DMA is ADM3 engine(implied by <= UARTDM v1.3),
	 * we need RXSTALE to flush input DMA fअगरo to memory
	 */
	अगर (msm_port->is_uartdm < UARTDM_1P4)
		msm_port->imr |= UART_IMR_RXSTALE;

	msm_ग_लिखो(uart, msm_port->imr, UART_IMR);

	dma->count = UARTDM_RX_SIZE;

	dma_async_issue_pending(dma->chan);

	msm_ग_लिखो(uart, UART_CR_CMD_RESET_STALE_INT, UART_CR);
	msm_ग_लिखो(uart, UART_CR_CMD_STALE_EVENT_ENABLE, UART_CR);

	val = msm_पढ़ो(uart, UARTDM_DMEN);
	val |= dma->enable_bit;

	अगर (msm_port->is_uartdm < UARTDM_1P4)
		msm_ग_लिखो(uart, val, UARTDM_DMEN);

	msm_ग_लिखो(uart, UARTDM_RX_SIZE, UARTDM_DMRX);

	अगर (msm_port->is_uartdm > UARTDM_1P3)
		msm_ग_लिखो(uart, val, UARTDM_DMEN);

	वापस;
unmap:
	dma_unmap_single(uart->dev, dma->phys, UARTDM_RX_SIZE, dma->dir);

sw_mode:
	/*
	 * Switch from DMA to SW/FIFO mode. After clearing Rx BAM (UARTDM_DMEN),
	 * receiver must be reset.
	 */
	msm_ग_लिखो(uart, UART_CR_CMD_RESET_RX, UART_CR);
	msm_ग_लिखो(uart, UART_CR_RX_ENABLE, UART_CR);

	msm_ग_लिखो(uart, UART_CR_CMD_RESET_STALE_INT, UART_CR);
	msm_ग_लिखो(uart, 0xFFFFFF, UARTDM_DMRX);
	msm_ग_लिखो(uart, UART_CR_CMD_STALE_EVENT_ENABLE, UART_CR);

	/* Re-enable RX पूर्णांकerrupts */
	msm_port->imr |= (UART_IMR_RXLEV | UART_IMR_RXSTALE);
	msm_ग_लिखो(uart, msm_port->imr, UART_IMR);
पूर्ण

अटल व्योम msm_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);
	काष्ठा msm_dma *dma = &msm_port->rx_dma;

	msm_port->imr &= ~(UART_IMR_RXLEV | UART_IMR_RXSTALE);
	msm_ग_लिखो(port, msm_port->imr, UART_IMR);

	अगर (dma->chan)
		msm_stop_dma(port, dma);
पूर्ण

अटल व्योम msm_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);

	msm_port->imr |= UART_IMR_DELTA_CTS;
	msm_ग_लिखो(port, msm_port->imr, UART_IMR);
पूर्ण

अटल व्योम msm_handle_rx_dm(काष्ठा uart_port *port, अचिन्हित पूर्णांक misr)
	__must_hold(&port->lock)
अणु
	काष्ठा tty_port *tport = &port->state->port;
	अचिन्हित पूर्णांक sr;
	पूर्णांक count = 0;
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);

	अगर ((msm_पढ़ो(port, UART_SR) & UART_SR_OVERRUN)) अणु
		port->icount.overrun++;
		tty_insert_flip_अक्षर(tport, 0, TTY_OVERRUN);
		msm_ग_लिखो(port, UART_CR_CMD_RESET_ERR, UART_CR);
	पूर्ण

	अगर (misr & UART_IMR_RXSTALE) अणु
		count = msm_पढ़ो(port, UARTDM_RX_TOTAL_SNAP) -
			msm_port->old_snap_state;
		msm_port->old_snap_state = 0;
	पूर्ण अन्यथा अणु
		count = 4 * (msm_पढ़ो(port, UART_RFWR));
		msm_port->old_snap_state += count;
	पूर्ण

	/* TODO: Precise error reporting */

	port->icount.rx += count;

	जबतक (count > 0) अणु
		अचिन्हित अक्षर buf[4];
		पूर्णांक sysrq, r_count, i;

		sr = msm_पढ़ो(port, UART_SR);
		अगर ((sr & UART_SR_RX_READY) == 0) अणु
			msm_port->old_snap_state -= count;
			अवरोध;
		पूर्ण

		ioपढ़ो32_rep(port->membase + UARTDM_RF, buf, 1);
		r_count = min_t(पूर्णांक, count, माप(buf));

		क्रम (i = 0; i < r_count; i++) अणु
			अक्षर flag = TTY_NORMAL;

			अगर (msm_port->अवरोध_detected && buf[i] == 0) अणु
				port->icount.brk++;
				flag = TTY_BREAK;
				msm_port->अवरोध_detected = false;
				अगर (uart_handle_अवरोध(port))
					जारी;
			पूर्ण

			अगर (!(port->पढ़ो_status_mask & UART_SR_RX_BREAK))
				flag = TTY_NORMAL;

			spin_unlock(&port->lock);
			sysrq = uart_handle_sysrq_अक्षर(port, buf[i]);
			spin_lock(&port->lock);
			अगर (!sysrq)
				tty_insert_flip_अक्षर(tport, buf[i], flag);
		पूर्ण
		count -= r_count;
	पूर्ण

	tty_flip_buffer_push(tport);

	अगर (misr & (UART_IMR_RXSTALE))
		msm_ग_लिखो(port, UART_CR_CMD_RESET_STALE_INT, UART_CR);
	msm_ग_लिखो(port, 0xFFFFFF, UARTDM_DMRX);
	msm_ग_लिखो(port, UART_CR_CMD_STALE_EVENT_ENABLE, UART_CR);

	/* Try to use DMA */
	msm_start_rx_dma(msm_port);
पूर्ण

अटल व्योम msm_handle_rx(काष्ठा uart_port *port)
	__must_hold(&port->lock)
अणु
	काष्ठा tty_port *tport = &port->state->port;
	अचिन्हित पूर्णांक sr;

	/*
	 * Handle overrun. My understanding of the hardware is that overrun
	 * is not tied to the RX buffer, so we handle the हाल out of band.
	 */
	अगर ((msm_पढ़ो(port, UART_SR) & UART_SR_OVERRUN)) अणु
		port->icount.overrun++;
		tty_insert_flip_अक्षर(tport, 0, TTY_OVERRUN);
		msm_ग_लिखो(port, UART_CR_CMD_RESET_ERR, UART_CR);
	पूर्ण

	/* and now the मुख्य RX loop */
	जबतक ((sr = msm_पढ़ो(port, UART_SR)) & UART_SR_RX_READY) अणु
		अचिन्हित पूर्णांक c;
		अक्षर flag = TTY_NORMAL;
		पूर्णांक sysrq;

		c = msm_पढ़ो(port, UART_RF);

		अगर (sr & UART_SR_RX_BREAK) अणु
			port->icount.brk++;
			अगर (uart_handle_अवरोध(port))
				जारी;
		पूर्ण अन्यथा अगर (sr & UART_SR_PAR_FRAME_ERR) अणु
			port->icount.frame++;
		पूर्ण अन्यथा अणु
			port->icount.rx++;
		पूर्ण

		/* Mask conditions we're ignorning. */
		sr &= port->पढ़ो_status_mask;

		अगर (sr & UART_SR_RX_BREAK)
			flag = TTY_BREAK;
		अन्यथा अगर (sr & UART_SR_PAR_FRAME_ERR)
			flag = TTY_FRAME;

		spin_unlock(&port->lock);
		sysrq = uart_handle_sysrq_अक्षर(port, c);
		spin_lock(&port->lock);
		अगर (!sysrq)
			tty_insert_flip_अक्षर(tport, c, flag);
	पूर्ण

	tty_flip_buffer_push(tport);
पूर्ण

अटल व्योम msm_handle_tx_pio(काष्ठा uart_port *port, अचिन्हित पूर्णांक tx_count)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);
	अचिन्हित पूर्णांक num_अक्षरs;
	अचिन्हित पूर्णांक tf_poपूर्णांकer = 0;
	व्योम __iomem *tf;

	अगर (msm_port->is_uartdm)
		tf = port->membase + UARTDM_TF;
	अन्यथा
		tf = port->membase + UART_TF;

	अगर (tx_count && msm_port->is_uartdm)
		msm_reset_dm_count(port, tx_count);

	जबतक (tf_poपूर्णांकer < tx_count) अणु
		पूर्णांक i;
		अक्षर buf[4] = अणु 0 पूर्ण;

		अगर (!(msm_पढ़ो(port, UART_SR) & UART_SR_TX_READY))
			अवरोध;

		अगर (msm_port->is_uartdm)
			num_अक्षरs = min(tx_count - tf_poपूर्णांकer,
					(अचिन्हित पूर्णांक)माप(buf));
		अन्यथा
			num_अक्षरs = 1;

		क्रम (i = 0; i < num_अक्षरs; i++) अणु
			buf[i] = xmit->buf[xmit->tail + i];
			port->icount.tx++;
		पूर्ण

		ioग_लिखो32_rep(tf, buf, 1);
		xmit->tail = (xmit->tail + num_अक्षरs) & (UART_XMIT_SIZE - 1);
		tf_poपूर्णांकer += num_अक्षरs;
	पूर्ण

	/* disable tx पूर्णांकerrupts अगर nothing more to send */
	अगर (uart_circ_empty(xmit))
		msm_stop_tx(port);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);
पूर्ण

अटल व्योम msm_handle_tx(काष्ठा uart_port *port)
अणु
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);
	काष्ठा circ_buf *xmit = &msm_port->uart.state->xmit;
	काष्ठा msm_dma *dma = &msm_port->tx_dma;
	अचिन्हित पूर्णांक pio_count, dma_count, dma_min;
	अक्षर buf[4] = अणु 0 पूर्ण;
	व्योम __iomem *tf;
	पूर्णांक err = 0;

	अगर (port->x_अक्षर) अणु
		अगर (msm_port->is_uartdm)
			tf = port->membase + UARTDM_TF;
		अन्यथा
			tf = port->membase + UART_TF;

		buf[0] = port->x_अक्षर;

		अगर (msm_port->is_uartdm)
			msm_reset_dm_count(port, 1);

		ioग_लिखो32_rep(tf, buf, 1);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		msm_stop_tx(port);
		वापस;
	पूर्ण

	pio_count = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);
	dma_count = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);

	dma_min = 1;	/* Always DMA */
	अगर (msm_port->is_uartdm > UARTDM_1P3) अणु
		dma_count = UARTDM_TX_AIGN(dma_count);
		dma_min = UARTDM_BURST_SIZE;
	पूर्ण अन्यथा अणु
		अगर (dma_count > UARTDM_TX_MAX)
			dma_count = UARTDM_TX_MAX;
	पूर्ण

	अगर (pio_count > port->fअगरosize)
		pio_count = port->fअगरosize;

	अगर (!dma->chan || dma_count < dma_min)
		msm_handle_tx_pio(port, pio_count);
	अन्यथा
		err = msm_handle_tx_dma(msm_port, dma_count);

	अगर (err)	/* fall back to PIO mode */
		msm_handle_tx_pio(port, pio_count);
पूर्ण

अटल व्योम msm_handle_delta_cts(काष्ठा uart_port *port)
अणु
	msm_ग_लिखो(port, UART_CR_CMD_RESET_CTS, UART_CR);
	port->icount.cts++;
	wake_up_पूर्णांकerruptible(&port->state->port.delta_msr_रुको);
पूर्ण

अटल irqवापस_t msm_uart_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);
	काष्ठा msm_dma *dma = &msm_port->rx_dma;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक misr;
	u32 val;

	spin_lock_irqsave(&port->lock, flags);
	misr = msm_पढ़ो(port, UART_MISR);
	msm_ग_लिखो(port, 0, UART_IMR); /* disable पूर्णांकerrupt */

	अगर (misr & UART_IMR_RXBREAK_START) अणु
		msm_port->अवरोध_detected = true;
		msm_ग_लिखो(port, UART_CR_CMD_RESET_RXBREAK_START, UART_CR);
	पूर्ण

	अगर (misr & (UART_IMR_RXLEV | UART_IMR_RXSTALE)) अणु
		अगर (dma->count) अणु
			val = UART_CR_CMD_STALE_EVENT_DISABLE;
			msm_ग_लिखो(port, val, UART_CR);
			val = UART_CR_CMD_RESET_STALE_INT;
			msm_ग_लिखो(port, val, UART_CR);
			/*
			 * Flush DMA input fअगरo to memory, this will also
			 * trigger DMA RX completion
			 */
			dmaengine_terminate_all(dma->chan);
		पूर्ण अन्यथा अगर (msm_port->is_uartdm) अणु
			msm_handle_rx_dm(port, misr);
		पूर्ण अन्यथा अणु
			msm_handle_rx(port);
		पूर्ण
	पूर्ण
	अगर (misr & UART_IMR_TXLEV)
		msm_handle_tx(port);
	अगर (misr & UART_IMR_DELTA_CTS)
		msm_handle_delta_cts(port);

	msm_ग_लिखो(port, msm_port->imr, UART_IMR); /* restore पूर्णांकerrupt */
	spin_unlock_irqrestore(&port->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक msm_tx_empty(काष्ठा uart_port *port)
अणु
	वापस (msm_पढ़ो(port, UART_SR) & UART_SR_TX_EMPTY) ? TIOCSER_TEMT : 0;
पूर्ण

अटल अचिन्हित पूर्णांक msm_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस TIOCM_CAR | TIOCM_CTS | TIOCM_DSR | TIOCM_RTS;
पूर्ण

अटल व्योम msm_reset(काष्ठा uart_port *port)
अणु
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);
	अचिन्हित पूर्णांक mr;

	/* reset everything */
	msm_ग_लिखो(port, UART_CR_CMD_RESET_RX, UART_CR);
	msm_ग_लिखो(port, UART_CR_CMD_RESET_TX, UART_CR);
	msm_ग_लिखो(port, UART_CR_CMD_RESET_ERR, UART_CR);
	msm_ग_लिखो(port, UART_CR_CMD_RESET_BREAK_INT, UART_CR);
	msm_ग_लिखो(port, UART_CR_CMD_RESET_CTS, UART_CR);
	msm_ग_लिखो(port, UART_CR_CMD_RESET_RFR, UART_CR);
	mr = msm_पढ़ो(port, UART_MR1);
	mr &= ~UART_MR1_RX_RDY_CTL;
	msm_ग_लिखो(port, mr, UART_MR1);

	/* Disable DM modes */
	अगर (msm_port->is_uartdm)
		msm_ग_लिखो(port, 0, UARTDM_DMEN);
पूर्ण

अटल व्योम msm_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	अचिन्हित पूर्णांक mr;

	mr = msm_पढ़ो(port, UART_MR1);

	अगर (!(mctrl & TIOCM_RTS)) अणु
		mr &= ~UART_MR1_RX_RDY_CTL;
		msm_ग_लिखो(port, mr, UART_MR1);
		msm_ग_लिखो(port, UART_CR_CMD_RESET_RFR, UART_CR);
	पूर्ण अन्यथा अणु
		mr |= UART_MR1_RX_RDY_CTL;
		msm_ग_लिखो(port, mr, UART_MR1);
	पूर्ण
पूर्ण

अटल व्योम msm_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_ctl)
अणु
	अगर (अवरोध_ctl)
		msm_ग_लिखो(port, UART_CR_CMD_START_BREAK, UART_CR);
	अन्यथा
		msm_ग_लिखो(port, UART_CR_CMD_STOP_BREAK, UART_CR);
पूर्ण

काष्ठा msm_baud_map अणु
	u16	भागisor;
	u8	code;
	u8	rxstale;
पूर्ण;

अटल स्थिर काष्ठा msm_baud_map *
msm_find_best_baud(काष्ठा uart_port *port, अचिन्हित पूर्णांक baud,
		   अचिन्हित दीर्घ *rate)
अणु
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);
	अचिन्हित पूर्णांक भागisor, result;
	अचिन्हित दीर्घ target, old, best_rate = 0, dअगरf, best_dअगरf = अच_दीर्घ_उच्च;
	स्थिर काष्ठा msm_baud_map *entry, *end, *best;
	अटल स्थिर काष्ठा msm_baud_map table[] = अणु
		अणु    1, 0xff, 31 पूर्ण,
		अणु    2, 0xee, 16 पूर्ण,
		अणु    3, 0xdd,  8 पूर्ण,
		अणु    4, 0xcc,  6 पूर्ण,
		अणु    6, 0xbb,  6 पूर्ण,
		अणु    8, 0xaa,  6 पूर्ण,
		अणु   12, 0x99,  6 पूर्ण,
		अणु   16, 0x88,  1 पूर्ण,
		अणु   24, 0x77,  1 पूर्ण,
		अणु   32, 0x66,  1 पूर्ण,
		अणु   48, 0x55,  1 पूर्ण,
		अणु   96, 0x44,  1 पूर्ण,
		अणु  192, 0x33,  1 पूर्ण,
		अणु  384, 0x22,  1 पूर्ण,
		अणु  768, 0x11,  1 पूर्ण,
		अणु 1536, 0x00,  1 पूर्ण,
	पूर्ण;

	best = table; /* Default to smallest भागider */
	target = clk_round_rate(msm_port->clk, 16 * baud);
	भागisor = DIV_ROUND_CLOSEST(target, 16 * baud);

	end = table + ARRAY_SIZE(table);
	entry = table;
	जबतक (entry < end) अणु
		अगर (entry->भागisor <= भागisor) अणु
			result = target / entry->भागisor / 16;
			dअगरf = असल(result - baud);

			/* Keep track of best entry */
			अगर (dअगरf < best_dअगरf) अणु
				best_dअगरf = dअगरf;
				best = entry;
				best_rate = target;
			पूर्ण

			अगर (result == baud)
				अवरोध;
		पूर्ण अन्यथा अगर (entry->भागisor > भागisor) अणु
			old = target;
			target = clk_round_rate(msm_port->clk, old + 1);
			/*
			 * The rate didn't get any faster so we can't करो
			 * better at भागiding it करोwn
			 */
			अगर (target == old)
				अवरोध;

			/* Start the भागisor search over at this new rate */
			entry = table;
			भागisor = DIV_ROUND_CLOSEST(target, 16 * baud);
			जारी;
		पूर्ण
		entry++;
	पूर्ण

	*rate = best_rate;
	वापस best;
पूर्ण

अटल पूर्णांक msm_set_baud_rate(काष्ठा uart_port *port, अचिन्हित पूर्णांक baud,
			     अचिन्हित दीर्घ *saved_flags)
अणु
	अचिन्हित पूर्णांक rxstale, watermark, mask;
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);
	स्थिर काष्ठा msm_baud_map *entry;
	अचिन्हित दीर्घ flags, rate;

	flags = *saved_flags;
	spin_unlock_irqrestore(&port->lock, flags);

	entry = msm_find_best_baud(port, baud, &rate);
	clk_set_rate(msm_port->clk, rate);
	baud = rate / 16 / entry->भागisor;

	spin_lock_irqsave(&port->lock, flags);
	*saved_flags = flags;
	port->uartclk = rate;

	msm_ग_लिखो(port, entry->code, UART_CSR);

	/* RX stale watermark */
	rxstale = entry->rxstale;
	watermark = UART_IPR_STALE_LSB & rxstale;
	अगर (msm_port->is_uartdm) अणु
		mask = UART_DM_IPR_STALE_TIMEOUT_MSB;
	पूर्ण अन्यथा अणु
		watermark |= UART_IPR_RXSTALE_LAST;
		mask = UART_IPR_STALE_TIMEOUT_MSB;
	पूर्ण

	watermark |= mask & (rxstale << 2);

	msm_ग_लिखो(port, watermark, UART_IPR);

	/* set RX watermark */
	watermark = (port->fअगरosize * 3) / 4;
	msm_ग_लिखो(port, watermark, UART_RFWR);

	/* set TX watermark */
	msm_ग_लिखो(port, 10, UART_TFWR);

	msm_ग_लिखो(port, UART_CR_CMD_PROTECTION_EN, UART_CR);
	msm_reset(port);

	/* Enable RX and TX */
	msm_ग_लिखो(port, UART_CR_TX_ENABLE | UART_CR_RX_ENABLE, UART_CR);

	/* turn on RX and CTS पूर्णांकerrupts */
	msm_port->imr = UART_IMR_RXLEV | UART_IMR_RXSTALE |
			UART_IMR_CURRENT_CTS | UART_IMR_RXBREAK_START;

	msm_ग_लिखो(port, msm_port->imr, UART_IMR);

	अगर (msm_port->is_uartdm) अणु
		msm_ग_लिखो(port, UART_CR_CMD_RESET_STALE_INT, UART_CR);
		msm_ग_लिखो(port, 0xFFFFFF, UARTDM_DMRX);
		msm_ग_लिखो(port, UART_CR_CMD_STALE_EVENT_ENABLE, UART_CR);
	पूर्ण

	वापस baud;
पूर्ण

अटल व्योम msm_init_घड़ी(काष्ठा uart_port *port)
अणु
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);

	clk_prepare_enable(msm_port->clk);
	clk_prepare_enable(msm_port->pclk);
	msm_serial_set_mnd_regs(port);
पूर्ण

अटल पूर्णांक msm_startup(काष्ठा uart_port *port)
अणु
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);
	अचिन्हित पूर्णांक data, rfr_level, mask;
	पूर्णांक ret;

	snम_लिखो(msm_port->name, माप(msm_port->name),
		 "msm_serial%d", port->line);

	msm_init_घड़ी(port);

	अगर (likely(port->fअगरosize > 12))
		rfr_level = port->fअगरosize - 12;
	अन्यथा
		rfr_level = port->fअगरosize;

	/* set स्वतःmatic RFR level */
	data = msm_पढ़ो(port, UART_MR1);

	अगर (msm_port->is_uartdm)
		mask = UART_DM_MR1_AUTO_RFR_LEVEL1;
	अन्यथा
		mask = UART_MR1_AUTO_RFR_LEVEL1;

	data &= ~mask;
	data &= ~UART_MR1_AUTO_RFR_LEVEL0;
	data |= mask & (rfr_level << 2);
	data |= UART_MR1_AUTO_RFR_LEVEL0 & rfr_level;
	msm_ग_लिखो(port, data, UART_MR1);

	अगर (msm_port->is_uartdm) अणु
		msm_request_tx_dma(msm_port, msm_port->uart.mapbase);
		msm_request_rx_dma(msm_port, msm_port->uart.mapbase);
	पूर्ण

	ret = request_irq(port->irq, msm_uart_irq, IRQF_TRIGGER_HIGH,
			  msm_port->name, port);
	अगर (unlikely(ret))
		जाओ err_irq;

	वापस 0;

err_irq:
	अगर (msm_port->is_uartdm)
		msm_release_dma(msm_port);

	clk_disable_unprepare(msm_port->pclk);
	clk_disable_unprepare(msm_port->clk);

	वापस ret;
पूर्ण

अटल व्योम msm_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);

	msm_port->imr = 0;
	msm_ग_लिखो(port, 0, UART_IMR); /* disable पूर्णांकerrupts */

	अगर (msm_port->is_uartdm)
		msm_release_dma(msm_port);

	clk_disable_unprepare(msm_port->clk);

	मुक्त_irq(port->irq, port);
पूर्ण

अटल व्योम msm_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
			    काष्ठा ktermios *old)
अणु
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);
	काष्ठा msm_dma *dma = &msm_port->rx_dma;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, mr;

	spin_lock_irqsave(&port->lock, flags);

	अगर (dma->chan) /* Terminate अगर any */
		msm_stop_dma(port, dma);

	/* calculate and set baud rate */
	baud = uart_get_baud_rate(port, termios, old, 300, 4000000);
	baud = msm_set_baud_rate(port, baud, &flags);
	अगर (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);

	/* calculate parity */
	mr = msm_पढ़ो(port, UART_MR2);
	mr &= ~UART_MR2_PARITY_MODE;
	अगर (termios->c_cflag & PARENB) अणु
		अगर (termios->c_cflag & PARODD)
			mr |= UART_MR2_PARITY_MODE_ODD;
		अन्यथा अगर (termios->c_cflag & CMSPAR)
			mr |= UART_MR2_PARITY_MODE_SPACE;
		अन्यथा
			mr |= UART_MR2_PARITY_MODE_EVEN;
	पूर्ण

	/* calculate bits per अक्षर */
	mr &= ~UART_MR2_BITS_PER_CHAR;
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		mr |= UART_MR2_BITS_PER_CHAR_5;
		अवरोध;
	हाल CS6:
		mr |= UART_MR2_BITS_PER_CHAR_6;
		अवरोध;
	हाल CS7:
		mr |= UART_MR2_BITS_PER_CHAR_7;
		अवरोध;
	हाल CS8:
	शेष:
		mr |= UART_MR2_BITS_PER_CHAR_8;
		अवरोध;
	पूर्ण

	/* calculate stop bits */
	mr &= ~(UART_MR2_STOP_BIT_LEN_ONE | UART_MR2_STOP_BIT_LEN_TWO);
	अगर (termios->c_cflag & CSTOPB)
		mr |= UART_MR2_STOP_BIT_LEN_TWO;
	अन्यथा
		mr |= UART_MR2_STOP_BIT_LEN_ONE;

	/* set parity, bits per अक्षर, and stop bit */
	msm_ग_लिखो(port, mr, UART_MR2);

	/* calculate and set hardware flow control */
	mr = msm_पढ़ो(port, UART_MR1);
	mr &= ~(UART_MR1_CTS_CTL | UART_MR1_RX_RDY_CTL);
	अगर (termios->c_cflag & CRTSCTS) अणु
		mr |= UART_MR1_CTS_CTL;
		mr |= UART_MR1_RX_RDY_CTL;
	पूर्ण
	msm_ग_लिखो(port, mr, UART_MR1);

	/* Configure status bits to ignore based on termio flags. */
	port->पढ़ो_status_mask = 0;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= UART_SR_PAR_FRAME_ERR;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		port->पढ़ो_status_mask |= UART_SR_RX_BREAK;

	uart_update_समयout(port, termios->c_cflag, baud);

	/* Try to use DMA */
	msm_start_rx_dma(msm_port);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *msm_type(काष्ठा uart_port *port)
अणु
	वापस "MSM";
पूर्ण

अटल व्योम msm_release_port(काष्ठा uart_port *port)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(port->dev);
	काष्ठा resource *uart_resource;
	resource_माप_प्रकार size;

	uart_resource = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (unlikely(!uart_resource))
		वापस;
	size = resource_size(uart_resource);

	release_mem_region(port->mapbase, size);
	iounmap(port->membase);
	port->membase = शून्य;
पूर्ण

अटल पूर्णांक msm_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(port->dev);
	काष्ठा resource *uart_resource;
	resource_माप_प्रकार size;
	पूर्णांक ret;

	uart_resource = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (unlikely(!uart_resource))
		वापस -ENXIO;

	size = resource_size(uart_resource);

	अगर (!request_mem_region(port->mapbase, size, "msm_serial"))
		वापस -EBUSY;

	port->membase = ioremap(port->mapbase, size);
	अगर (!port->membase) अणु
		ret = -EBUSY;
		जाओ fail_release_port;
	पूर्ण

	वापस 0;

fail_release_port:
	release_mem_region(port->mapbase, size);
	वापस ret;
पूर्ण

अटल व्योम msm_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	पूर्णांक ret;

	अगर (flags & UART_CONFIG_TYPE) अणु
		port->type = PORT_MSM;
		ret = msm_request_port(port);
		अगर (ret)
			वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक msm_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	अगर (unlikely(ser->type != PORT_UNKNOWN && ser->type != PORT_MSM))
		वापस -EINVAL;
	अगर (unlikely(port->irq != ser->irq))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम msm_घातer(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
		      अचिन्हित पूर्णांक oldstate)
अणु
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);

	चयन (state) अणु
	हाल 0:
		clk_prepare_enable(msm_port->clk);
		clk_prepare_enable(msm_port->pclk);
		अवरोध;
	हाल 3:
		clk_disable_unprepare(msm_port->clk);
		clk_disable_unprepare(msm_port->pclk);
		अवरोध;
	शेष:
		pr_err("msm_serial: Unknown PM state %d\n", state);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
अटल पूर्णांक msm_poll_get_अक्षर_single(काष्ठा uart_port *port)
अणु
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);
	अचिन्हित पूर्णांक rf_reg = msm_port->is_uartdm ? UARTDM_RF : UART_RF;

	अगर (!(msm_पढ़ो(port, UART_SR) & UART_SR_RX_READY))
		वापस NO_POLL_CHAR;

	वापस msm_पढ़ो(port, rf_reg) & 0xff;
पूर्ण

अटल पूर्णांक msm_poll_get_अक्षर_dm(काष्ठा uart_port *port)
अणु
	पूर्णांक c;
	अटल u32 slop;
	अटल पूर्णांक count;
	अचिन्हित अक्षर *sp = (अचिन्हित अक्षर *)&slop;

	/* Check अगर a previous पढ़ो had more than one अक्षर */
	अगर (count) अणु
		c = sp[माप(slop) - count];
		count--;
	/* Or अगर FIFO is empty */
	पूर्ण अन्यथा अगर (!(msm_पढ़ो(port, UART_SR) & UART_SR_RX_READY)) अणु
		/*
		 * If RX packing buffer has less than a word, क्रमce stale to
		 * push contents पूर्णांकo RX FIFO
		 */
		count = msm_पढ़ो(port, UARTDM_RXFS);
		count = (count >> UARTDM_RXFS_BUF_SHIFT) & UARTDM_RXFS_BUF_MASK;
		अगर (count) अणु
			msm_ग_लिखो(port, UART_CR_CMD_FORCE_STALE, UART_CR);
			slop = msm_पढ़ो(port, UARTDM_RF);
			c = sp[0];
			count--;
			msm_ग_लिखो(port, UART_CR_CMD_RESET_STALE_INT, UART_CR);
			msm_ग_लिखो(port, 0xFFFFFF, UARTDM_DMRX);
			msm_ग_लिखो(port, UART_CR_CMD_STALE_EVENT_ENABLE,
				  UART_CR);
		पूर्ण अन्यथा अणु
			c = NO_POLL_CHAR;
		पूर्ण
	/* FIFO has a word */
	पूर्ण अन्यथा अणु
		slop = msm_पढ़ो(port, UARTDM_RF);
		c = sp[0];
		count = माप(slop) - 1;
	पूर्ण

	वापस c;
पूर्ण

अटल पूर्णांक msm_poll_get_अक्षर(काष्ठा uart_port *port)
अणु
	u32 imr;
	पूर्णांक c;
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);

	/* Disable all पूर्णांकerrupts */
	imr = msm_पढ़ो(port, UART_IMR);
	msm_ग_लिखो(port, 0, UART_IMR);

	अगर (msm_port->is_uartdm)
		c = msm_poll_get_अक्षर_dm(port);
	अन्यथा
		c = msm_poll_get_अक्षर_single(port);

	/* Enable पूर्णांकerrupts */
	msm_ग_लिखो(port, imr, UART_IMR);

	वापस c;
पूर्ण

अटल व्योम msm_poll_put_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर c)
अणु
	u32 imr;
	काष्ठा msm_port *msm_port = UART_TO_MSM(port);

	/* Disable all पूर्णांकerrupts */
	imr = msm_पढ़ो(port, UART_IMR);
	msm_ग_लिखो(port, 0, UART_IMR);

	अगर (msm_port->is_uartdm)
		msm_reset_dm_count(port, 1);

	/* Wait until FIFO is empty */
	जबतक (!(msm_पढ़ो(port, UART_SR) & UART_SR_TX_READY))
		cpu_relax();

	/* Write a अक्षरacter */
	msm_ग_लिखो(port, c, msm_port->is_uartdm ? UARTDM_TF : UART_TF);

	/* Wait until FIFO is empty */
	जबतक (!(msm_पढ़ो(port, UART_SR) & UART_SR_TX_READY))
		cpu_relax();

	/* Enable पूर्णांकerrupts */
	msm_ग_लिखो(port, imr, UART_IMR);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा uart_ops msm_uart_pops = अणु
	.tx_empty = msm_tx_empty,
	.set_mctrl = msm_set_mctrl,
	.get_mctrl = msm_get_mctrl,
	.stop_tx = msm_stop_tx,
	.start_tx = msm_start_tx,
	.stop_rx = msm_stop_rx,
	.enable_ms = msm_enable_ms,
	.अवरोध_ctl = msm_अवरोध_ctl,
	.startup = msm_startup,
	.shutकरोwn = msm_shutकरोwn,
	.set_termios = msm_set_termios,
	.type = msm_type,
	.release_port = msm_release_port,
	.request_port = msm_request_port,
	.config_port = msm_config_port,
	.verअगरy_port = msm_verअगरy_port,
	.pm = msm_घातer,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर	= msm_poll_get_अक्षर,
	.poll_put_अक्षर	= msm_poll_put_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा msm_port msm_uart_ports[] = अणु
	अणु
		.uart = अणु
			.iotype = UPIO_MEM,
			.ops = &msm_uart_pops,
			.flags = UPF_BOOT_AUTOCONF,
			.fअगरosize = 64,
			.line = 0,
		पूर्ण,
	पूर्ण,
	अणु
		.uart = अणु
			.iotype = UPIO_MEM,
			.ops = &msm_uart_pops,
			.flags = UPF_BOOT_AUTOCONF,
			.fअगरosize = 64,
			.line = 1,
		पूर्ण,
	पूर्ण,
	अणु
		.uart = अणु
			.iotype = UPIO_MEM,
			.ops = &msm_uart_pops,
			.flags = UPF_BOOT_AUTOCONF,
			.fअगरosize = 64,
			.line = 2,
		पूर्ण,
	पूर्ण,
पूर्ण;

#घोषणा UART_NR	ARRAY_SIZE(msm_uart_ports)

अटल अंतरभूत काष्ठा uart_port *msm_get_port_from_line(अचिन्हित पूर्णांक line)
अणु
	वापस &msm_uart_ports[line].uart;
पूर्ण

#अगर_घोषित CONFIG_SERIAL_MSM_CONSOLE
अटल व्योम __msm_console_ग_लिखो(काष्ठा uart_port *port, स्थिर अक्षर *s,
				अचिन्हित पूर्णांक count, bool is_uartdm)
अणु
	पूर्णांक i;
	पूर्णांक num_newlines = 0;
	bool replaced = false;
	व्योम __iomem *tf;
	पूर्णांक locked = 1;

	अगर (is_uartdm)
		tf = port->membase + UARTDM_TF;
	अन्यथा
		tf = port->membase + UART_TF;

	/* Account क्रम newlines that will get a carriage वापस added */
	क्रम (i = 0; i < count; i++)
		अगर (s[i] == '\n')
			num_newlines++;
	count += num_newlines;

	अगर (port->sysrq)
		locked = 0;
	अन्यथा अगर (oops_in_progress)
		locked = spin_trylock(&port->lock);
	अन्यथा
		spin_lock(&port->lock);

	अगर (is_uartdm)
		msm_reset_dm_count(port, count);

	i = 0;
	जबतक (i < count) अणु
		पूर्णांक j;
		अचिन्हित पूर्णांक num_अक्षरs;
		अक्षर buf[4] = अणु 0 पूर्ण;

		अगर (is_uartdm)
			num_अक्षरs = min(count - i, (अचिन्हित पूर्णांक)माप(buf));
		अन्यथा
			num_अक्षरs = 1;

		क्रम (j = 0; j < num_अक्षरs; j++) अणु
			अक्षर c = *s;

			अगर (c == '\n' && !replaced) अणु
				buf[j] = '\r';
				j++;
				replaced = true;
			पूर्ण
			अगर (j < num_अक्षरs) अणु
				buf[j] = c;
				s++;
				replaced = false;
			पूर्ण
		पूर्ण

		जबतक (!(msm_पढ़ो(port, UART_SR) & UART_SR_TX_READY))
			cpu_relax();

		ioग_लिखो32_rep(tf, buf, 1);
		i += num_अक्षरs;
	पूर्ण

	अगर (locked)
		spin_unlock(&port->lock);
पूर्ण

अटल व्योम msm_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
			      अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_port *port;
	काष्ठा msm_port *msm_port;

	BUG_ON(co->index < 0 || co->index >= UART_NR);

	port = msm_get_port_from_line(co->index);
	msm_port = UART_TO_MSM(port);

	__msm_console_ग_लिखो(port, s, count, msm_port->is_uartdm);
पूर्ण

अटल पूर्णांक msm_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (unlikely(co->index >= UART_NR || co->index < 0))
		वापस -ENXIO;

	port = msm_get_port_from_line(co->index);

	अगर (unlikely(!port->membase))
		वापस -ENXIO;

	msm_init_घड़ी(port);

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	pr_info("msm_serial: console setup on port #%d\n", port->line);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल व्योम
msm_serial_early_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	__msm_console_ग_लिखो(&dev->port, s, n, false);
पूर्ण

अटल पूर्णांक __init
msm_serial_early_console_setup(काष्ठा earlycon_device *device, स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->con->ग_लिखो = msm_serial_early_ग_लिखो;
	वापस 0;
पूर्ण
OF_EARLYCON_DECLARE(msm_serial, "qcom,msm-uart",
		    msm_serial_early_console_setup);

अटल व्योम
msm_serial_early_ग_लिखो_dm(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	__msm_console_ग_लिखो(&dev->port, s, n, true);
पूर्ण

अटल पूर्णांक __init
msm_serial_early_console_setup_dm(काष्ठा earlycon_device *device,
				  स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->con->ग_लिखो = msm_serial_early_ग_लिखो_dm;
	वापस 0;
पूर्ण
OF_EARLYCON_DECLARE(msm_serial_dm, "qcom,msm-uartdm",
		    msm_serial_early_console_setup_dm);

अटल काष्ठा uart_driver msm_uart_driver;

अटल काष्ठा console msm_console = अणु
	.name = "ttyMSM",
	.ग_लिखो = msm_console_ग_लिखो,
	.device = uart_console_device,
	.setup = msm_console_setup,
	.flags = CON_PRINTBUFFER,
	.index = -1,
	.data = &msm_uart_driver,
पूर्ण;

#घोषणा MSM_CONSOLE	(&msm_console)

#अन्यथा
#घोषणा MSM_CONSOLE	शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver msm_uart_driver = अणु
	.owner = THIS_MODULE,
	.driver_name = "msm_serial",
	.dev_name = "ttyMSM",
	.nr = UART_NR,
	.cons = MSM_CONSOLE,
पूर्ण;

अटल atomic_t msm_uart_next_id = ATOMIC_INIT(0);

अटल स्थिर काष्ठा of_device_id msm_uartdm_table[] = अणु
	अणु .compatible = "qcom,msm-uartdm-v1.1", .data = (व्योम *)UARTDM_1P1 पूर्ण,
	अणु .compatible = "qcom,msm-uartdm-v1.2", .data = (व्योम *)UARTDM_1P2 पूर्ण,
	अणु .compatible = "qcom,msm-uartdm-v1.3", .data = (व्योम *)UARTDM_1P3 पूर्ण,
	अणु .compatible = "qcom,msm-uartdm-v1.4", .data = (व्योम *)UARTDM_1P4 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक msm_serial_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा msm_port *msm_port;
	काष्ठा resource *resource;
	काष्ठा uart_port *port;
	स्थिर काष्ठा of_device_id *id;
	पूर्णांक irq, line;

	अगर (pdev->dev.of_node)
		line = of_alias_get_id(pdev->dev.of_node, "serial");
	अन्यथा
		line = pdev->id;

	अगर (line < 0)
		line = atomic_inc_वापस(&msm_uart_next_id) - 1;

	अगर (unlikely(line < 0 || line >= UART_NR))
		वापस -ENXIO;

	dev_info(&pdev->dev, "msm_serial: detected port #%d\n", line);

	port = msm_get_port_from_line(line);
	port->dev = &pdev->dev;
	msm_port = UART_TO_MSM(port);

	id = of_match_device(msm_uartdm_table, &pdev->dev);
	अगर (id)
		msm_port->is_uartdm = (अचिन्हित दीर्घ)id->data;
	अन्यथा
		msm_port->is_uartdm = 0;

	msm_port->clk = devm_clk_get(&pdev->dev, "core");
	अगर (IS_ERR(msm_port->clk))
		वापस PTR_ERR(msm_port->clk);

	अगर (msm_port->is_uartdm) अणु
		msm_port->pclk = devm_clk_get(&pdev->dev, "iface");
		अगर (IS_ERR(msm_port->pclk))
			वापस PTR_ERR(msm_port->pclk);
	पूर्ण

	port->uartclk = clk_get_rate(msm_port->clk);
	dev_info(&pdev->dev, "uartclk = %d\n", port->uartclk);

	resource = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (unlikely(!resource))
		वापस -ENXIO;
	port->mapbase = resource->start;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (unlikely(irq < 0))
		वापस -ENXIO;
	port->irq = irq;
	port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_MSM_CONSOLE);

	platक्रमm_set_drvdata(pdev, port);

	वापस uart_add_one_port(&msm_uart_driver, port);
पूर्ण

अटल पूर्णांक msm_serial_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port = platक्रमm_get_drvdata(pdev);

	uart_हटाओ_one_port(&msm_uart_driver, port);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id msm_match_table[] = अणु
	अणु .compatible = "qcom,msm-uart" पूर्ण,
	अणु .compatible = "qcom,msm-uartdm" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, msm_match_table);

अटल पूर्णांक __maybe_unused msm_serial_suspend(काष्ठा device *dev)
अणु
	काष्ठा msm_port *port = dev_get_drvdata(dev);

	uart_suspend_port(&msm_uart_driver, &port->uart);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused msm_serial_resume(काष्ठा device *dev)
अणु
	काष्ठा msm_port *port = dev_get_drvdata(dev);

	uart_resume_port(&msm_uart_driver, &port->uart);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops msm_serial_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(msm_serial_suspend, msm_serial_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver msm_platक्रमm_driver = अणु
	.हटाओ = msm_serial_हटाओ,
	.probe = msm_serial_probe,
	.driver = अणु
		.name = "msm_serial",
		.pm = &msm_serial_dev_pm_ops,
		.of_match_table = msm_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init msm_serial_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&msm_uart_driver);
	अगर (unlikely(ret))
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&msm_platक्रमm_driver);
	अगर (unlikely(ret))
		uart_unरेजिस्टर_driver(&msm_uart_driver);

	pr_info("msm_serial: driver initialized\n");

	वापस ret;
पूर्ण

अटल व्योम __निकास msm_serial_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&msm_platक्रमm_driver);
	uart_unरेजिस्टर_driver(&msm_uart_driver);
पूर्ण

module_init(msm_serial_init);
module_निकास(msm_serial_निकास);

MODULE_AUTHOR("Robert Love <rlove@google.com>");
MODULE_DESCRIPTION("Driver for msm7x serial device");
MODULE_LICENSE("GPL");
