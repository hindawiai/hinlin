<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// spi-uniphier.c - Socionext UniPhier SPI controller driver
// Copyright 2012      Panasonic Corporation
// Copyright 2016-2018 Socionext Inc.

#समावेश <linux/kernel.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा SSI_TIMEOUT_MS		2000
#घोषणा SSI_POLL_TIMEOUT_US	200
#घोषणा SSI_MAX_CLK_DIVIDER	254
#घोषणा SSI_MIN_CLK_DIVIDER	4

काष्ठा uniphier_spi_priv अणु
	व्योम __iomem *base;
	dma_addr_t base_dma_addr;
	काष्ठा clk *clk;
	काष्ठा spi_master *master;
	काष्ठा completion xfer_करोne;

	पूर्णांक error;
	अचिन्हित पूर्णांक tx_bytes;
	अचिन्हित पूर्णांक rx_bytes;
	स्थिर u8 *tx_buf;
	u8 *rx_buf;
	atomic_t dma_busy;

	bool is_save_param;
	u8 bits_per_word;
	u16 mode;
	u32 speed_hz;
पूर्ण;

#घोषणा SSI_CTL			0x00
#घोषणा   SSI_CTL_EN		BIT(0)

#घोषणा SSI_CKS			0x04
#घोषणा   SSI_CKS_CKRAT_MASK	GENMASK(7, 0)
#घोषणा   SSI_CKS_CKPHS		BIT(14)
#घोषणा   SSI_CKS_CKINIT	BIT(13)
#घोषणा   SSI_CKS_CKDLY		BIT(12)

#घोषणा SSI_TXWDS		0x08
#घोषणा   SSI_TXWDS_WDLEN_MASK	GENMASK(13, 8)
#घोषणा   SSI_TXWDS_TDTF_MASK	GENMASK(7, 6)
#घोषणा   SSI_TXWDS_DTLEN_MASK	GENMASK(5, 0)

#घोषणा SSI_RXWDS		0x0c
#घोषणा   SSI_RXWDS_DTLEN_MASK	GENMASK(5, 0)

#घोषणा SSI_FPS			0x10
#घोषणा   SSI_FPS_FSPOL		BIT(15)
#घोषणा   SSI_FPS_FSTRT		BIT(14)

#घोषणा SSI_SR			0x14
#घोषणा   SSI_SR_BUSY		BIT(7)
#घोषणा   SSI_SR_RNE		BIT(0)

#घोषणा SSI_IE			0x18
#घोषणा   SSI_IE_TCIE		BIT(4)
#घोषणा   SSI_IE_RCIE		BIT(3)
#घोषणा   SSI_IE_TXRE		BIT(2)
#घोषणा   SSI_IE_RXRE		BIT(1)
#घोषणा   SSI_IE_RORIE		BIT(0)
#घोषणा   SSI_IE_ALL_MASK	GENMASK(4, 0)

#घोषणा SSI_IS			0x1c
#घोषणा   SSI_IS_RXRS		BIT(9)
#घोषणा   SSI_IS_RCID		BIT(3)
#घोषणा   SSI_IS_RORID		BIT(0)

#घोषणा SSI_IC			0x1c
#घोषणा   SSI_IC_TCIC		BIT(4)
#घोषणा   SSI_IC_RCIC		BIT(3)
#घोषणा   SSI_IC_RORIC		BIT(0)

#घोषणा SSI_FC			0x20
#घोषणा   SSI_FC_TXFFL		BIT(12)
#घोषणा   SSI_FC_TXFTH_MASK	GENMASK(11, 8)
#घोषणा   SSI_FC_RXFFL		BIT(4)
#घोषणा   SSI_FC_RXFTH_MASK	GENMASK(3, 0)

#घोषणा SSI_TXDR		0x24
#घोषणा SSI_RXDR		0x24

#घोषणा SSI_FIFO_DEPTH		8U
#घोषणा SSI_FIFO_BURST_NUM	1

#घोषणा SSI_DMA_RX_BUSY		BIT(1)
#घोषणा SSI_DMA_TX_BUSY		BIT(0)

अटल अंतरभूत अचिन्हित पूर्णांक bytes_per_word(अचिन्हित पूर्णांक bits)
अणु
	वापस bits <= 8 ? 1 : (bits <= 16 ? 2 : 4);
पूर्ण

अटल अंतरभूत व्योम uniphier_spi_irq_enable(काष्ठा uniphier_spi_priv *priv,
					   u32 mask)
अणु
	u32 val;

	val = पढ़ोl(priv->base + SSI_IE);
	val |= mask;
	ग_लिखोl(val, priv->base + SSI_IE);
पूर्ण

अटल अंतरभूत व्योम uniphier_spi_irq_disable(काष्ठा uniphier_spi_priv *priv,
					    u32 mask)
अणु
	u32 val;

	val = पढ़ोl(priv->base + SSI_IE);
	val &= ~mask;
	ग_लिखोl(val, priv->base + SSI_IE);
पूर्ण

अटल व्योम uniphier_spi_set_mode(काष्ठा spi_device *spi)
अणु
	काष्ठा uniphier_spi_priv *priv = spi_master_get_devdata(spi->master);
	u32 val1, val2;

	/*
	 * घड़ी setting
	 * CKPHS    capture timing. 0:rising edge, 1:falling edge
	 * CKINIT   घड़ी initial level. 0:low, 1:high
	 * CKDLY    घड़ी delay. 0:no delay, 1:delay depending on FSTRT
	 *          (FSTRT=0: 1 घड़ी, FSTRT=1: 0.5 घड़ी)
	 *
	 * frame setting
	 * FSPOL    frame संकेत porarity. 0: low, 1: high
	 * FSTRT    start frame timing
	 *          0: rising edge of घड़ी, 1: falling edge of घड़ी
	 */
	चयन (spi->mode & (SPI_CPOL | SPI_CPHA)) अणु
	हाल SPI_MODE_0:
		/* CKPHS=1, CKINIT=0, CKDLY=1, FSTRT=0 */
		val1 = SSI_CKS_CKPHS | SSI_CKS_CKDLY;
		val2 = 0;
		अवरोध;
	हाल SPI_MODE_1:
		/* CKPHS=0, CKINIT=0, CKDLY=0, FSTRT=1 */
		val1 = 0;
		val2 = SSI_FPS_FSTRT;
		अवरोध;
	हाल SPI_MODE_2:
		/* CKPHS=0, CKINIT=1, CKDLY=1, FSTRT=1 */
		val1 = SSI_CKS_CKINIT | SSI_CKS_CKDLY;
		val2 = SSI_FPS_FSTRT;
		अवरोध;
	हाल SPI_MODE_3:
		/* CKPHS=1, CKINIT=1, CKDLY=0, FSTRT=0 */
		val1 = SSI_CKS_CKPHS | SSI_CKS_CKINIT;
		val2 = 0;
		अवरोध;
	पूर्ण

	अगर (!(spi->mode & SPI_CS_HIGH))
		val2 |= SSI_FPS_FSPOL;

	ग_लिखोl(val1, priv->base + SSI_CKS);
	ग_लिखोl(val2, priv->base + SSI_FPS);

	val1 = 0;
	अगर (spi->mode & SPI_LSB_FIRST)
		val1 |= FIELD_PREP(SSI_TXWDS_TDTF_MASK, 1);
	ग_लिखोl(val1, priv->base + SSI_TXWDS);
	ग_लिखोl(val1, priv->base + SSI_RXWDS);
पूर्ण

अटल व्योम uniphier_spi_set_transfer_size(काष्ठा spi_device *spi, पूर्णांक size)
अणु
	काष्ठा uniphier_spi_priv *priv = spi_master_get_devdata(spi->master);
	u32 val;

	val = पढ़ोl(priv->base + SSI_TXWDS);
	val &= ~(SSI_TXWDS_WDLEN_MASK | SSI_TXWDS_DTLEN_MASK);
	val |= FIELD_PREP(SSI_TXWDS_WDLEN_MASK, size);
	val |= FIELD_PREP(SSI_TXWDS_DTLEN_MASK, size);
	ग_लिखोl(val, priv->base + SSI_TXWDS);

	val = पढ़ोl(priv->base + SSI_RXWDS);
	val &= ~SSI_RXWDS_DTLEN_MASK;
	val |= FIELD_PREP(SSI_RXWDS_DTLEN_MASK, size);
	ग_लिखोl(val, priv->base + SSI_RXWDS);
पूर्ण

अटल व्योम uniphier_spi_set_baudrate(काष्ठा spi_device *spi,
				      अचिन्हित पूर्णांक speed)
अणु
	काष्ठा uniphier_spi_priv *priv = spi_master_get_devdata(spi->master);
	u32 val, ckभाग;

	/*
	 * the supported rates are even numbers from 4 to 254. (4,6,8...254)
	 * round up as we look क्रम equal or less speed
	 */
	ckभाग = DIV_ROUND_UP(clk_get_rate(priv->clk), speed);
	ckभाग = round_up(ckभाग, 2);

	val = पढ़ोl(priv->base + SSI_CKS);
	val &= ~SSI_CKS_CKRAT_MASK;
	val |= ckभाग & SSI_CKS_CKRAT_MASK;
	ग_लिखोl(val, priv->base + SSI_CKS);
पूर्ण

अटल व्योम uniphier_spi_setup_transfer(काष्ठा spi_device *spi,
				       काष्ठा spi_transfer *t)
अणु
	काष्ठा uniphier_spi_priv *priv = spi_master_get_devdata(spi->master);
	u32 val;

	priv->error = 0;
	priv->tx_buf = t->tx_buf;
	priv->rx_buf = t->rx_buf;
	priv->tx_bytes = priv->rx_bytes = t->len;

	अगर (!priv->is_save_param || priv->mode != spi->mode) अणु
		uniphier_spi_set_mode(spi);
		priv->mode = spi->mode;
		priv->is_save_param = false;
	पूर्ण

	अगर (!priv->is_save_param || priv->bits_per_word != t->bits_per_word) अणु
		uniphier_spi_set_transfer_size(spi, t->bits_per_word);
		priv->bits_per_word = t->bits_per_word;
	पूर्ण

	अगर (!priv->is_save_param || priv->speed_hz != t->speed_hz) अणु
		uniphier_spi_set_baudrate(spi, t->speed_hz);
		priv->speed_hz = t->speed_hz;
	पूर्ण

	priv->is_save_param = true;

	/* reset FIFOs */
	val = SSI_FC_TXFFL | SSI_FC_RXFFL;
	ग_लिखोl(val, priv->base + SSI_FC);
पूर्ण

अटल व्योम uniphier_spi_send(काष्ठा uniphier_spi_priv *priv)
अणु
	पूर्णांक wsize;
	u32 val = 0;

	wsize = min(bytes_per_word(priv->bits_per_word), priv->tx_bytes);
	priv->tx_bytes -= wsize;

	अगर (priv->tx_buf) अणु
		चयन (wsize) अणु
		हाल 1:
			val = *priv->tx_buf;
			अवरोध;
		हाल 2:
			val = get_unaligned_le16(priv->tx_buf);
			अवरोध;
		हाल 4:
			val = get_unaligned_le32(priv->tx_buf);
			अवरोध;
		पूर्ण

		priv->tx_buf += wsize;
	पूर्ण

	ग_लिखोl(val, priv->base + SSI_TXDR);
पूर्ण

अटल व्योम uniphier_spi_recv(काष्ठा uniphier_spi_priv *priv)
अणु
	पूर्णांक rsize;
	u32 val;

	rsize = min(bytes_per_word(priv->bits_per_word), priv->rx_bytes);
	priv->rx_bytes -= rsize;

	val = पढ़ोl(priv->base + SSI_RXDR);

	अगर (priv->rx_buf) अणु
		चयन (rsize) अणु
		हाल 1:
			*priv->rx_buf = val;
			अवरोध;
		हाल 2:
			put_unaligned_le16(val, priv->rx_buf);
			अवरोध;
		हाल 4:
			put_unaligned_le32(val, priv->rx_buf);
			अवरोध;
		पूर्ण

		priv->rx_buf += rsize;
	पूर्ण
पूर्ण

अटल व्योम uniphier_spi_set_fअगरo_threshold(काष्ठा uniphier_spi_priv *priv,
					    अचिन्हित पूर्णांक threshold)
अणु
	u32 val;

	val = पढ़ोl(priv->base + SSI_FC);
	val &= ~(SSI_FC_TXFTH_MASK | SSI_FC_RXFTH_MASK);
	val |= FIELD_PREP(SSI_FC_TXFTH_MASK, SSI_FIFO_DEPTH - threshold);
	val |= FIELD_PREP(SSI_FC_RXFTH_MASK, threshold);
	ग_लिखोl(val, priv->base + SSI_FC);
पूर्ण

अटल व्योम uniphier_spi_fill_tx_fअगरo(काष्ठा uniphier_spi_priv *priv)
अणु
	अचिन्हित पूर्णांक fअगरo_threshold, fill_words;
	अचिन्हित पूर्णांक bpw = bytes_per_word(priv->bits_per_word);

	fअगरo_threshold = DIV_ROUND_UP(priv->rx_bytes, bpw);
	fअगरo_threshold = min(fअगरo_threshold, SSI_FIFO_DEPTH);

	uniphier_spi_set_fअगरo_threshold(priv, fअगरo_threshold);

	fill_words = fअगरo_threshold -
		DIV_ROUND_UP(priv->rx_bytes - priv->tx_bytes, bpw);

	जबतक (fill_words--)
		uniphier_spi_send(priv);
पूर्ण

अटल व्योम uniphier_spi_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा uniphier_spi_priv *priv = spi_master_get_devdata(spi->master);
	u32 val;

	val = पढ़ोl(priv->base + SSI_FPS);

	अगर (enable)
		val |= SSI_FPS_FSPOL;
	अन्यथा
		val &= ~SSI_FPS_FSPOL;

	ग_लिखोl(val, priv->base + SSI_FPS);
पूर्ण

अटल bool uniphier_spi_can_dma(काष्ठा spi_master *master,
				 काष्ठा spi_device *spi,
				 काष्ठा spi_transfer *t)
अणु
	काष्ठा uniphier_spi_priv *priv = spi_master_get_devdata(master);
	अचिन्हित पूर्णांक bpw = bytes_per_word(priv->bits_per_word);

	अगर ((!master->dma_tx && !master->dma_rx)
	    || (!master->dma_tx && t->tx_buf)
	    || (!master->dma_rx && t->rx_buf))
		वापस false;

	वापस DIV_ROUND_UP(t->len, bpw) > SSI_FIFO_DEPTH;
पूर्ण

अटल व्योम uniphier_spi_dma_rxcb(व्योम *data)
अणु
	काष्ठा spi_master *master = data;
	काष्ठा uniphier_spi_priv *priv = spi_master_get_devdata(master);
	पूर्णांक state = atomic_fetch_andnot(SSI_DMA_RX_BUSY, &priv->dma_busy);

	uniphier_spi_irq_disable(priv, SSI_IE_RXRE);

	अगर (!(state & SSI_DMA_TX_BUSY))
		spi_finalize_current_transfer(master);
पूर्ण

अटल व्योम uniphier_spi_dma_txcb(व्योम *data)
अणु
	काष्ठा spi_master *master = data;
	काष्ठा uniphier_spi_priv *priv = spi_master_get_devdata(master);
	पूर्णांक state = atomic_fetch_andnot(SSI_DMA_TX_BUSY, &priv->dma_busy);

	uniphier_spi_irq_disable(priv, SSI_IE_TXRE);

	अगर (!(state & SSI_DMA_RX_BUSY))
		spi_finalize_current_transfer(master);
पूर्ण

अटल पूर्णांक uniphier_spi_transfer_one_dma(काष्ठा spi_master *master,
					 काष्ठा spi_device *spi,
					 काष्ठा spi_transfer *t)
अणु
	काष्ठा uniphier_spi_priv *priv = spi_master_get_devdata(master);
	काष्ठा dma_async_tx_descriptor *rxdesc = शून्य, *txdesc = शून्य;
	पूर्णांक buswidth;

	atomic_set(&priv->dma_busy, 0);

	uniphier_spi_set_fअगरo_threshold(priv, SSI_FIFO_BURST_NUM);

	अगर (priv->bits_per_word <= 8)
		buswidth = DMA_SLAVE_BUSWIDTH_1_BYTE;
	अन्यथा अगर (priv->bits_per_word <= 16)
		buswidth = DMA_SLAVE_BUSWIDTH_2_BYTES;
	अन्यथा
		buswidth = DMA_SLAVE_BUSWIDTH_4_BYTES;

	अगर (priv->rx_buf) अणु
		काष्ठा dma_slave_config rxconf = अणु
			.direction = DMA_DEV_TO_MEM,
			.src_addr = priv->base_dma_addr + SSI_RXDR,
			.src_addr_width = buswidth,
			.src_maxburst = SSI_FIFO_BURST_NUM,
		पूर्ण;

		dmaengine_slave_config(master->dma_rx, &rxconf);

		rxdesc = dmaengine_prep_slave_sg(
			master->dma_rx,
			t->rx_sg.sgl, t->rx_sg.nents,
			DMA_DEV_TO_MEM, DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		अगर (!rxdesc)
			जाओ out_err_prep;

		rxdesc->callback = uniphier_spi_dma_rxcb;
		rxdesc->callback_param = master;

		uniphier_spi_irq_enable(priv, SSI_IE_RXRE);
		atomic_or(SSI_DMA_RX_BUSY, &priv->dma_busy);

		dmaengine_submit(rxdesc);
		dma_async_issue_pending(master->dma_rx);
	पूर्ण

	अगर (priv->tx_buf) अणु
		काष्ठा dma_slave_config txconf = अणु
			.direction = DMA_MEM_TO_DEV,
			.dst_addr = priv->base_dma_addr + SSI_TXDR,
			.dst_addr_width = buswidth,
			.dst_maxburst = SSI_FIFO_BURST_NUM,
		पूर्ण;

		dmaengine_slave_config(master->dma_tx, &txconf);

		txdesc = dmaengine_prep_slave_sg(
			master->dma_tx,
			t->tx_sg.sgl, t->tx_sg.nents,
			DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		अगर (!txdesc)
			जाओ out_err_prep;

		txdesc->callback = uniphier_spi_dma_txcb;
		txdesc->callback_param = master;

		uniphier_spi_irq_enable(priv, SSI_IE_TXRE);
		atomic_or(SSI_DMA_TX_BUSY, &priv->dma_busy);

		dmaengine_submit(txdesc);
		dma_async_issue_pending(master->dma_tx);
	पूर्ण

	/* संकेत that we need to रुको क्रम completion */
	वापस (priv->tx_buf || priv->rx_buf);

out_err_prep:
	अगर (rxdesc)
		dmaengine_terminate_sync(master->dma_rx);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक uniphier_spi_transfer_one_irq(काष्ठा spi_master *master,
					 काष्ठा spi_device *spi,
					 काष्ठा spi_transfer *t)
अणु
	काष्ठा uniphier_spi_priv *priv = spi_master_get_devdata(master);
	काष्ठा device *dev = master->dev.parent;
	अचिन्हित दीर्घ समय_left;

	reinit_completion(&priv->xfer_करोne);

	uniphier_spi_fill_tx_fअगरo(priv);

	uniphier_spi_irq_enable(priv, SSI_IE_RCIE | SSI_IE_RORIE);

	समय_left = रुको_क्रम_completion_समयout(&priv->xfer_करोne,
					msecs_to_jअगरfies(SSI_TIMEOUT_MS));

	uniphier_spi_irq_disable(priv, SSI_IE_RCIE | SSI_IE_RORIE);

	अगर (!समय_left) अणु
		dev_err(dev, "transfer timeout.\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस priv->error;
पूर्ण

अटल पूर्णांक uniphier_spi_transfer_one_poll(काष्ठा spi_master *master,
					  काष्ठा spi_device *spi,
					  काष्ठा spi_transfer *t)
अणु
	काष्ठा uniphier_spi_priv *priv = spi_master_get_devdata(master);
	पूर्णांक loop = SSI_POLL_TIMEOUT_US * 10;

	जबतक (priv->tx_bytes) अणु
		uniphier_spi_fill_tx_fअगरo(priv);

		जबतक ((priv->rx_bytes - priv->tx_bytes) > 0) अणु
			जबतक (!(पढ़ोl(priv->base + SSI_SR) & SSI_SR_RNE)
								&& loop--)
				ndelay(100);

			अगर (loop == -1)
				जाओ irq_transfer;

			uniphier_spi_recv(priv);
		पूर्ण
	पूर्ण

	वापस 0;

irq_transfer:
	वापस uniphier_spi_transfer_one_irq(master, spi, t);
पूर्ण

अटल पूर्णांक uniphier_spi_transfer_one(काष्ठा spi_master *master,
				     काष्ठा spi_device *spi,
				     काष्ठा spi_transfer *t)
अणु
	काष्ठा uniphier_spi_priv *priv = spi_master_get_devdata(master);
	अचिन्हित दीर्घ threshold;
	bool use_dma;

	/* Terminate and वापस success क्रम 0 byte length transfer */
	अगर (!t->len)
		वापस 0;

	uniphier_spi_setup_transfer(spi, t);

	use_dma = master->can_dma ? master->can_dma(master, spi, t) : false;
	अगर (use_dma)
		वापस uniphier_spi_transfer_one_dma(master, spi, t);

	/*
	 * If the transfer operation will take दीर्घer than
	 * SSI_POLL_TIMEOUT_US, it should use irq.
	 */
	threshold = DIV_ROUND_UP(SSI_POLL_TIMEOUT_US * priv->speed_hz,
					USEC_PER_SEC * BITS_PER_BYTE);
	अगर (t->len > threshold)
		वापस uniphier_spi_transfer_one_irq(master, spi, t);
	अन्यथा
		वापस uniphier_spi_transfer_one_poll(master, spi, t);
पूर्ण

अटल पूर्णांक uniphier_spi_prepare_transfer_hardware(काष्ठा spi_master *master)
अणु
	काष्ठा uniphier_spi_priv *priv = spi_master_get_devdata(master);

	ग_लिखोl(SSI_CTL_EN, priv->base + SSI_CTL);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_spi_unprepare_transfer_hardware(काष्ठा spi_master *master)
अणु
	काष्ठा uniphier_spi_priv *priv = spi_master_get_devdata(master);

	ग_लिखोl(0, priv->base + SSI_CTL);

	वापस 0;
पूर्ण

अटल व्योम uniphier_spi_handle_err(काष्ठा spi_master *master,
				    काष्ठा spi_message *msg)
अणु
	काष्ठा uniphier_spi_priv *priv = spi_master_get_devdata(master);
	u32 val;

	/* stop running spi transfer */
	ग_लिखोl(0, priv->base + SSI_CTL);

	/* reset FIFOs */
	val = SSI_FC_TXFFL | SSI_FC_RXFFL;
	ग_लिखोl(val, priv->base + SSI_FC);

	uniphier_spi_irq_disable(priv, SSI_IE_ALL_MASK);

	अगर (atomic_पढ़ो(&priv->dma_busy) & SSI_DMA_TX_BUSY) अणु
		dmaengine_terminate_async(master->dma_tx);
		atomic_andnot(SSI_DMA_TX_BUSY, &priv->dma_busy);
	पूर्ण

	अगर (atomic_पढ़ो(&priv->dma_busy) & SSI_DMA_RX_BUSY) अणु
		dmaengine_terminate_async(master->dma_rx);
		atomic_andnot(SSI_DMA_RX_BUSY, &priv->dma_busy);
	पूर्ण
पूर्ण

अटल irqवापस_t uniphier_spi_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uniphier_spi_priv *priv = dev_id;
	u32 val, stat;

	stat = पढ़ोl(priv->base + SSI_IS);
	val = SSI_IC_TCIC | SSI_IC_RCIC | SSI_IC_RORIC;
	ग_लिखोl(val, priv->base + SSI_IC);

	/* rx fअगरo overrun */
	अगर (stat & SSI_IS_RORID) अणु
		priv->error = -EIO;
		जाओ करोne;
	पूर्ण

	/* rx complete */
	अगर ((stat & SSI_IS_RCID) && (stat & SSI_IS_RXRS)) अणु
		जबतक ((पढ़ोl(priv->base + SSI_SR) & SSI_SR_RNE) &&
				(priv->rx_bytes - priv->tx_bytes) > 0)
			uniphier_spi_recv(priv);

		अगर ((पढ़ोl(priv->base + SSI_SR) & SSI_SR_RNE) ||
				(priv->rx_bytes != priv->tx_bytes)) अणु
			priv->error = -EIO;
			जाओ करोne;
		पूर्ण अन्यथा अगर (priv->rx_bytes == 0)
			जाओ करोne;

		/* next tx transfer */
		uniphier_spi_fill_tx_fअगरo(priv);

		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;

करोne:
	complete(&priv->xfer_करोne);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक uniphier_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uniphier_spi_priv *priv;
	काष्ठा spi_master *master;
	काष्ठा resource *res;
	काष्ठा dma_slave_caps caps;
	u32 dma_tx_burst = 0, dma_rx_burst = 0;
	अचिन्हित दीर्घ clk_rate;
	पूर्णांक irq;
	पूर्णांक ret;

	master = spi_alloc_master(&pdev->dev, माप(*priv));
	अगर (!master)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, master);

	priv = spi_master_get_devdata(master);
	priv->master = master;
	priv->is_save_param = false;

	priv->base = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &res);
	अगर (IS_ERR(priv->base)) अणु
		ret = PTR_ERR(priv->base);
		जाओ out_master_put;
	पूर्ण
	priv->base_dma_addr = res->start;

	priv->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		ret = PTR_ERR(priv->clk);
		जाओ out_master_put;
	पूर्ण

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		जाओ out_master_put;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ out_disable_clk;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, uniphier_spi_handler,
			       0, "uniphier-spi", priv);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request IRQ\n");
		जाओ out_disable_clk;
	पूर्ण

	init_completion(&priv->xfer_करोne);

	clk_rate = clk_get_rate(priv->clk);

	master->max_speed_hz = DIV_ROUND_UP(clk_rate, SSI_MIN_CLK_DIVIDER);
	master->min_speed_hz = DIV_ROUND_UP(clk_rate, SSI_MAX_CLK_DIVIDER);
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH | SPI_LSB_FIRST;
	master->dev.of_node = pdev->dev.of_node;
	master->bus_num = pdev->id;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(1, 32);

	master->set_cs = uniphier_spi_set_cs;
	master->transfer_one = uniphier_spi_transfer_one;
	master->prepare_transfer_hardware
				= uniphier_spi_prepare_transfer_hardware;
	master->unprepare_transfer_hardware
				= uniphier_spi_unprepare_transfer_hardware;
	master->handle_err = uniphier_spi_handle_err;
	master->can_dma = uniphier_spi_can_dma;

	master->num_chipselect = 1;
	master->flags = SPI_CONTROLLER_MUST_RX | SPI_CONTROLLER_MUST_TX;

	master->dma_tx = dma_request_chan(&pdev->dev, "tx");
	अगर (IS_ERR_OR_शून्य(master->dma_tx)) अणु
		अगर (PTR_ERR(master->dma_tx) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ out_disable_clk;
		पूर्ण
		master->dma_tx = शून्य;
		dma_tx_burst = पूर्णांक_उच्च;
	पूर्ण अन्यथा अणु
		ret = dma_get_slave_caps(master->dma_tx, &caps);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to get TX DMA capacities: %d\n",
				ret);
			जाओ out_disable_clk;
		पूर्ण
		dma_tx_burst = caps.max_burst;
	पूर्ण

	master->dma_rx = dma_request_chan(&pdev->dev, "rx");
	अगर (IS_ERR_OR_शून्य(master->dma_rx)) अणु
		अगर (PTR_ERR(master->dma_rx) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ out_disable_clk;
		पूर्ण
		master->dma_rx = शून्य;
		dma_rx_burst = पूर्णांक_उच्च;
	पूर्ण अन्यथा अणु
		ret = dma_get_slave_caps(master->dma_rx, &caps);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to get RX DMA capacities: %d\n",
				ret);
			जाओ out_disable_clk;
		पूर्ण
		dma_rx_burst = caps.max_burst;
	पूर्ण

	master->max_dma_len = min(dma_tx_burst, dma_rx_burst);

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret)
		जाओ out_disable_clk;

	वापस 0;

out_disable_clk:
	clk_disable_unprepare(priv->clk);

out_master_put:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uniphier_spi_priv *priv = platक्रमm_get_drvdata(pdev);

	अगर (priv->master->dma_tx)
		dma_release_channel(priv->master->dma_tx);
	अगर (priv->master->dma_rx)
		dma_release_channel(priv->master->dma_rx);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id uniphier_spi_match[] = अणु
	अणु .compatible = "socionext,uniphier-scssi" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_spi_match);

अटल काष्ठा platक्रमm_driver uniphier_spi_driver = अणु
	.probe = uniphier_spi_probe,
	.हटाओ = uniphier_spi_हटाओ,
	.driver = अणु
		.name = "uniphier-spi",
		.of_match_table = uniphier_spi_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_spi_driver);

MODULE_AUTHOR("Kunihiko Hayashi <hayashi.kunihiko@socionext.com>");
MODULE_AUTHOR("Keiji Hayashibara <hayashibara.keiji@socionext.com>");
MODULE_DESCRIPTION("Socionext UniPhier SPI controller driver");
MODULE_LICENSE("GPL v2");
