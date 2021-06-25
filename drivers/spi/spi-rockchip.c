<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, Fuzhou Rockchip Electronics Co., Ltd
 * Author: Addy Ke <addy.ke@rock-chips.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/scatterlist.h>

#घोषणा DRIVER_NAME "rockchip-spi"

#घोषणा ROCKCHIP_SPI_CLR_BITS(reg, bits) \
		ग_लिखोl_relaxed(पढ़ोl_relaxed(reg) & ~(bits), reg)
#घोषणा ROCKCHIP_SPI_SET_BITS(reg, bits) \
		ग_लिखोl_relaxed(पढ़ोl_relaxed(reg) | (bits), reg)

/* SPI रेजिस्टर offsets */
#घोषणा ROCKCHIP_SPI_CTRLR0			0x0000
#घोषणा ROCKCHIP_SPI_CTRLR1			0x0004
#घोषणा ROCKCHIP_SPI_SSIENR			0x0008
#घोषणा ROCKCHIP_SPI_SER			0x000c
#घोषणा ROCKCHIP_SPI_BAUDR			0x0010
#घोषणा ROCKCHIP_SPI_TXFTLR			0x0014
#घोषणा ROCKCHIP_SPI_RXFTLR			0x0018
#घोषणा ROCKCHIP_SPI_TXFLR			0x001c
#घोषणा ROCKCHIP_SPI_RXFLR			0x0020
#घोषणा ROCKCHIP_SPI_SR				0x0024
#घोषणा ROCKCHIP_SPI_IPR			0x0028
#घोषणा ROCKCHIP_SPI_IMR			0x002c
#घोषणा ROCKCHIP_SPI_ISR			0x0030
#घोषणा ROCKCHIP_SPI_RISR			0x0034
#घोषणा ROCKCHIP_SPI_ICR			0x0038
#घोषणा ROCKCHIP_SPI_DMACR			0x003c
#घोषणा ROCKCHIP_SPI_DMATDLR			0x0040
#घोषणा ROCKCHIP_SPI_DMARDLR			0x0044
#घोषणा ROCKCHIP_SPI_VERSION			0x0048
#घोषणा ROCKCHIP_SPI_TXDR			0x0400
#घोषणा ROCKCHIP_SPI_RXDR			0x0800

/* Bit fields in CTRLR0 */
#घोषणा CR0_DFS_OFFSET				0
#घोषणा CR0_DFS_4BIT				0x0
#घोषणा CR0_DFS_8BIT				0x1
#घोषणा CR0_DFS_16BIT				0x2

#घोषणा CR0_CFS_OFFSET				2

#घोषणा CR0_SCPH_OFFSET				6

#घोषणा CR0_SCPOL_OFFSET			7

#घोषणा CR0_CSM_OFFSET				8
#घोषणा CR0_CSM_KEEP				0x0
/* ss_n be high क्रम half sclk_out cycles */
#घोषणा CR0_CSM_HALF				0X1
/* ss_n be high क्रम one sclk_out cycle */
#घोषणा CR0_CSM_ONE					0x2

/* ss_n to sclk_out delay */
#घोषणा CR0_SSD_OFFSET				10
/*
 * The period between ss_n active and
 * sclk_out active is half sclk_out cycles
 */
#घोषणा CR0_SSD_HALF				0x0
/*
 * The period between ss_n active and
 * sclk_out active is one sclk_out cycle
 */
#घोषणा CR0_SSD_ONE					0x1

#घोषणा CR0_EM_OFFSET				11
#घोषणा CR0_EM_LITTLE				0x0
#घोषणा CR0_EM_BIG					0x1

#घोषणा CR0_FBM_OFFSET				12
#घोषणा CR0_FBM_MSB					0x0
#घोषणा CR0_FBM_LSB					0x1

#घोषणा CR0_BHT_OFFSET				13
#घोषणा CR0_BHT_16BIT				0x0
#घोषणा CR0_BHT_8BIT				0x1

#घोषणा CR0_RSD_OFFSET				14
#घोषणा CR0_RSD_MAX				0x3

#घोषणा CR0_FRF_OFFSET				16
#घोषणा CR0_FRF_SPI					0x0
#घोषणा CR0_FRF_SSP					0x1
#घोषणा CR0_FRF_MICROWIRE			0x2

#घोषणा CR0_XFM_OFFSET				18
#घोषणा CR0_XFM_MASK				(0x03 << SPI_XFM_OFFSET)
#घोषणा CR0_XFM_TR					0x0
#घोषणा CR0_XFM_TO					0x1
#घोषणा CR0_XFM_RO					0x2

#घोषणा CR0_OPM_OFFSET				20
#घोषणा CR0_OPM_MASTER				0x0
#घोषणा CR0_OPM_SLAVE				0x1

#घोषणा CR0_MTM_OFFSET				0x21

/* Bit fields in SER, 2bit */
#घोषणा SER_MASK					0x3

/* Bit fields in BAUDR */
#घोषणा BAUDR_SCKDV_MIN				2
#घोषणा BAUDR_SCKDV_MAX				65534

/* Bit fields in SR, 5bit */
#घोषणा SR_MASK						0x1f
#घोषणा SR_BUSY						(1 << 0)
#घोषणा SR_TF_FULL					(1 << 1)
#घोषणा SR_TF_EMPTY					(1 << 2)
#घोषणा SR_RF_EMPTY					(1 << 3)
#घोषणा SR_RF_FULL					(1 << 4)

/* Bit fields in ISR, IMR, ISR, RISR, 5bit */
#घोषणा INT_MASK					0x1f
#घोषणा INT_TF_EMPTY				(1 << 0)
#घोषणा INT_TF_OVERFLOW				(1 << 1)
#घोषणा INT_RF_UNDERFLOW			(1 << 2)
#घोषणा INT_RF_OVERFLOW				(1 << 3)
#घोषणा INT_RF_FULL					(1 << 4)

/* Bit fields in ICR, 4bit */
#घोषणा ICR_MASK					0x0f
#घोषणा ICR_ALL						(1 << 0)
#घोषणा ICR_RF_UNDERFLOW			(1 << 1)
#घोषणा ICR_RF_OVERFLOW				(1 << 2)
#घोषणा ICR_TF_OVERFLOW				(1 << 3)

/* Bit fields in DMACR */
#घोषणा RF_DMA_EN					(1 << 0)
#घोषणा TF_DMA_EN					(1 << 1)

/* Driver state flags */
#घोषणा RXDMA					(1 << 0)
#घोषणा TXDMA					(1 << 1)

/* sclk_out: spi master पूर्णांकernal logic in rk3x can support 50Mhz */
#घोषणा MAX_SCLK_OUT				50000000U

/*
 * SPI_CTRLR1 is 16-bits, so we should support lengths of 0xffff + 1. However,
 * the controller seems to hang when given 0x10000, so stick with this क्रम now.
 */
#घोषणा ROCKCHIP_SPI_MAX_TRANLEN		0xffff

#घोषणा ROCKCHIP_SPI_MAX_CS_NUM			2
#घोषणा ROCKCHIP_SPI_VER2_TYPE1			0x05EC0002
#घोषणा ROCKCHIP_SPI_VER2_TYPE2			0x00110002

#घोषणा ROCKCHIP_AUTOSUSPEND_TIMEOUT		2000

काष्ठा rockchip_spi अणु
	काष्ठा device *dev;

	काष्ठा clk *spiclk;
	काष्ठा clk *apb_pclk;

	व्योम __iomem *regs;
	dma_addr_t dma_addr_rx;
	dma_addr_t dma_addr_tx;

	स्थिर व्योम *tx;
	व्योम *rx;
	अचिन्हित पूर्णांक tx_left;
	अचिन्हित पूर्णांक rx_left;

	atomic_t state;

	/*depth of the FIFO buffer */
	u32 fअगरo_len;
	/* frequency of spiclk */
	u32 freq;

	u8 n_bytes;
	u8 rsd;

	bool cs_निश्चितed[ROCKCHIP_SPI_MAX_CS_NUM];

	bool slave_पात;
पूर्ण;

अटल अंतरभूत व्योम spi_enable_chip(काष्ठा rockchip_spi *rs, bool enable)
अणु
	ग_लिखोl_relaxed((enable ? 1U : 0U), rs->regs + ROCKCHIP_SPI_SSIENR);
पूर्ण

अटल अंतरभूत व्योम रुको_क्रम_idle(काष्ठा rockchip_spi *rs)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(5);

	करो अणु
		अगर (!(पढ़ोl_relaxed(rs->regs + ROCKCHIP_SPI_SR) & SR_BUSY))
			वापस;
	पूर्ण जबतक (!समय_after(jअगरfies, समयout));

	dev_warn(rs->dev, "spi controller is in busy state!\n");
पूर्ण

अटल u32 get_fअगरo_len(काष्ठा rockchip_spi *rs)
अणु
	u32 ver;

	ver = पढ़ोl_relaxed(rs->regs + ROCKCHIP_SPI_VERSION);

	चयन (ver) अणु
	हाल ROCKCHIP_SPI_VER2_TYPE1:
	हाल ROCKCHIP_SPI_VER2_TYPE2:
		वापस 64;
	शेष:
		वापस 32;
	पूर्ण
पूर्ण

अटल व्योम rockchip_spi_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा spi_controller *ctlr = spi->controller;
	काष्ठा rockchip_spi *rs = spi_controller_get_devdata(ctlr);
	bool cs_निश्चितed = !enable;

	/* Return immediately क्रम no-op */
	अगर (cs_निश्चितed == rs->cs_निश्चितed[spi->chip_select])
		वापस;

	अगर (cs_निश्चितed) अणु
		/* Keep things घातered as दीर्घ as CS is निश्चितed */
		pm_runसमय_get_sync(rs->dev);

		ROCKCHIP_SPI_SET_BITS(rs->regs + ROCKCHIP_SPI_SER,
				      BIT(spi->chip_select));
	पूर्ण अन्यथा अणु
		ROCKCHIP_SPI_CLR_BITS(rs->regs + ROCKCHIP_SPI_SER,
				      BIT(spi->chip_select));

		/* Drop reference from when we first निश्चितed CS */
		pm_runसमय_put(rs->dev);
	पूर्ण

	rs->cs_निश्चितed[spi->chip_select] = cs_निश्चितed;
पूर्ण

अटल व्योम rockchip_spi_handle_err(काष्ठा spi_controller *ctlr,
				    काष्ठा spi_message *msg)
अणु
	काष्ठा rockchip_spi *rs = spi_controller_get_devdata(ctlr);

	/* stop running spi transfer
	 * this also flushes both rx and tx fअगरos
	 */
	spi_enable_chip(rs, false);

	/* make sure all पूर्णांकerrupts are masked */
	ग_लिखोl_relaxed(0, rs->regs + ROCKCHIP_SPI_IMR);

	अगर (atomic_पढ़ो(&rs->state) & TXDMA)
		dmaengine_terminate_async(ctlr->dma_tx);

	अगर (atomic_पढ़ो(&rs->state) & RXDMA)
		dmaengine_terminate_async(ctlr->dma_rx);
पूर्ण

अटल व्योम rockchip_spi_pio_ग_लिखोr(काष्ठा rockchip_spi *rs)
अणु
	u32 tx_मुक्त = rs->fअगरo_len - पढ़ोl_relaxed(rs->regs + ROCKCHIP_SPI_TXFLR);
	u32 words = min(rs->tx_left, tx_मुक्त);

	rs->tx_left -= words;
	क्रम (; words; words--) अणु
		u32 txw;

		अगर (rs->n_bytes == 1)
			txw = *(u8 *)rs->tx;
		अन्यथा
			txw = *(u16 *)rs->tx;

		ग_लिखोl_relaxed(txw, rs->regs + ROCKCHIP_SPI_TXDR);
		rs->tx += rs->n_bytes;
	पूर्ण
पूर्ण

अटल व्योम rockchip_spi_pio_पढ़ोer(काष्ठा rockchip_spi *rs)
अणु
	u32 words = पढ़ोl_relaxed(rs->regs + ROCKCHIP_SPI_RXFLR);
	u32 rx_left = (rs->rx_left > words) ? rs->rx_left - words : 0;

	/* the hardware करोesn't allow us to change fअगरo threshold
	 * level जबतक spi is enabled, so instead make sure to leave
	 * enough words in the rx fअगरo to get the last पूर्णांकerrupt
	 * exactly when all words have been received
	 */
	अगर (rx_left) अणु
		u32 ftl = पढ़ोl_relaxed(rs->regs + ROCKCHIP_SPI_RXFTLR) + 1;

		अगर (rx_left < ftl) अणु
			rx_left = ftl;
			words = rs->rx_left - rx_left;
		पूर्ण
	पूर्ण

	rs->rx_left = rx_left;
	क्रम (; words; words--) अणु
		u32 rxw = पढ़ोl_relaxed(rs->regs + ROCKCHIP_SPI_RXDR);

		अगर (!rs->rx)
			जारी;

		अगर (rs->n_bytes == 1)
			*(u8 *)rs->rx = (u8)rxw;
		अन्यथा
			*(u16 *)rs->rx = (u16)rxw;
		rs->rx += rs->n_bytes;
	पूर्ण
पूर्ण

अटल irqवापस_t rockchip_spi_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_controller *ctlr = dev_id;
	काष्ठा rockchip_spi *rs = spi_controller_get_devdata(ctlr);

	अगर (rs->tx_left)
		rockchip_spi_pio_ग_लिखोr(rs);

	rockchip_spi_pio_पढ़ोer(rs);
	अगर (!rs->rx_left) अणु
		spi_enable_chip(rs, false);
		ग_लिखोl_relaxed(0, rs->regs + ROCKCHIP_SPI_IMR);
		spi_finalize_current_transfer(ctlr);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rockchip_spi_prepare_irq(काष्ठा rockchip_spi *rs,
		काष्ठा spi_transfer *xfer)
अणु
	rs->tx = xfer->tx_buf;
	rs->rx = xfer->rx_buf;
	rs->tx_left = rs->tx ? xfer->len / rs->n_bytes : 0;
	rs->rx_left = xfer->len / rs->n_bytes;

	ग_लिखोl_relaxed(INT_RF_FULL, rs->regs + ROCKCHIP_SPI_IMR);
	spi_enable_chip(rs, true);

	अगर (rs->tx_left)
		rockchip_spi_pio_ग_लिखोr(rs);

	/* 1 means the transfer is in progress */
	वापस 1;
पूर्ण

अटल व्योम rockchip_spi_dma_rxcb(व्योम *data)
अणु
	काष्ठा spi_controller *ctlr = data;
	काष्ठा rockchip_spi *rs = spi_controller_get_devdata(ctlr);
	पूर्णांक state = atomic_fetch_andnot(RXDMA, &rs->state);

	अगर (state & TXDMA && !rs->slave_पात)
		वापस;

	spi_enable_chip(rs, false);
	spi_finalize_current_transfer(ctlr);
पूर्ण

अटल व्योम rockchip_spi_dma_txcb(व्योम *data)
अणु
	काष्ठा spi_controller *ctlr = data;
	काष्ठा rockchip_spi *rs = spi_controller_get_devdata(ctlr);
	पूर्णांक state = atomic_fetch_andnot(TXDMA, &rs->state);

	अगर (state & RXDMA && !rs->slave_पात)
		वापस;

	/* Wait until the FIFO data completely. */
	रुको_क्रम_idle(rs);

	spi_enable_chip(rs, false);
	spi_finalize_current_transfer(ctlr);
पूर्ण

अटल u32 rockchip_spi_calc_burst_size(u32 data_len)
अणु
	u32 i;

	/* burst size: 1, 2, 4, 8 */
	क्रम (i = 1; i < 8; i <<= 1) अणु
		अगर (data_len & i)
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक rockchip_spi_prepare_dma(काष्ठा rockchip_spi *rs,
		काष्ठा spi_controller *ctlr, काष्ठा spi_transfer *xfer)
अणु
	काष्ठा dma_async_tx_descriptor *rxdesc, *txdesc;

	atomic_set(&rs->state, 0);

	rxdesc = शून्य;
	अगर (xfer->rx_buf) अणु
		काष्ठा dma_slave_config rxconf = अणु
			.direction = DMA_DEV_TO_MEM,
			.src_addr = rs->dma_addr_rx,
			.src_addr_width = rs->n_bytes,
			.src_maxburst = rockchip_spi_calc_burst_size(xfer->len /
								     rs->n_bytes),
		पूर्ण;

		dmaengine_slave_config(ctlr->dma_rx, &rxconf);

		rxdesc = dmaengine_prep_slave_sg(
				ctlr->dma_rx,
				xfer->rx_sg.sgl, xfer->rx_sg.nents,
				DMA_DEV_TO_MEM, DMA_PREP_INTERRUPT);
		अगर (!rxdesc)
			वापस -EINVAL;

		rxdesc->callback = rockchip_spi_dma_rxcb;
		rxdesc->callback_param = ctlr;
	पूर्ण

	txdesc = शून्य;
	अगर (xfer->tx_buf) अणु
		काष्ठा dma_slave_config txconf = अणु
			.direction = DMA_MEM_TO_DEV,
			.dst_addr = rs->dma_addr_tx,
			.dst_addr_width = rs->n_bytes,
			.dst_maxburst = rs->fअगरo_len / 4,
		पूर्ण;

		dmaengine_slave_config(ctlr->dma_tx, &txconf);

		txdesc = dmaengine_prep_slave_sg(
				ctlr->dma_tx,
				xfer->tx_sg.sgl, xfer->tx_sg.nents,
				DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT);
		अगर (!txdesc) अणु
			अगर (rxdesc)
				dmaengine_terminate_sync(ctlr->dma_rx);
			वापस -EINVAL;
		पूर्ण

		txdesc->callback = rockchip_spi_dma_txcb;
		txdesc->callback_param = ctlr;
	पूर्ण

	/* rx must be started beक्रमe tx due to spi instinct */
	अगर (rxdesc) अणु
		atomic_or(RXDMA, &rs->state);
		dmaengine_submit(rxdesc);
		dma_async_issue_pending(ctlr->dma_rx);
	पूर्ण

	spi_enable_chip(rs, true);

	अगर (txdesc) अणु
		atomic_or(TXDMA, &rs->state);
		dmaengine_submit(txdesc);
		dma_async_issue_pending(ctlr->dma_tx);
	पूर्ण

	/* 1 means the transfer is in progress */
	वापस 1;
पूर्ण

अटल पूर्णांक rockchip_spi_config(काष्ठा rockchip_spi *rs,
		काष्ठा spi_device *spi, काष्ठा spi_transfer *xfer,
		bool use_dma, bool slave_mode)
अणु
	u32 cr0 = CR0_FRF_SPI  << CR0_FRF_OFFSET
		| CR0_BHT_8BIT << CR0_BHT_OFFSET
		| CR0_SSD_ONE  << CR0_SSD_OFFSET
		| CR0_EM_BIG   << CR0_EM_OFFSET;
	u32 cr1;
	u32 dmacr = 0;

	अगर (slave_mode)
		cr0 |= CR0_OPM_SLAVE << CR0_OPM_OFFSET;
	rs->slave_पात = false;

	cr0 |= rs->rsd << CR0_RSD_OFFSET;
	cr0 |= (spi->mode & 0x3U) << CR0_SCPH_OFFSET;
	अगर (spi->mode & SPI_LSB_FIRST)
		cr0 |= CR0_FBM_LSB << CR0_FBM_OFFSET;

	अगर (xfer->rx_buf && xfer->tx_buf)
		cr0 |= CR0_XFM_TR << CR0_XFM_OFFSET;
	अन्यथा अगर (xfer->rx_buf)
		cr0 |= CR0_XFM_RO << CR0_XFM_OFFSET;
	अन्यथा अगर (use_dma)
		cr0 |= CR0_XFM_TO << CR0_XFM_OFFSET;

	चयन (xfer->bits_per_word) अणु
	हाल 4:
		cr0 |= CR0_DFS_4BIT << CR0_DFS_OFFSET;
		cr1 = xfer->len - 1;
		अवरोध;
	हाल 8:
		cr0 |= CR0_DFS_8BIT << CR0_DFS_OFFSET;
		cr1 = xfer->len - 1;
		अवरोध;
	हाल 16:
		cr0 |= CR0_DFS_16BIT << CR0_DFS_OFFSET;
		cr1 = xfer->len / 2 - 1;
		अवरोध;
	शेष:
		/* we only whitelist 4, 8 and 16 bit words in
		 * ctlr->bits_per_word_mask, so this shouldn't
		 * happen
		 */
		dev_err(rs->dev, "unknown bits per word: %d\n",
			xfer->bits_per_word);
		वापस -EINVAL;
	पूर्ण

	अगर (use_dma) अणु
		अगर (xfer->tx_buf)
			dmacr |= TF_DMA_EN;
		अगर (xfer->rx_buf)
			dmacr |= RF_DMA_EN;
	पूर्ण

	ग_लिखोl_relaxed(cr0, rs->regs + ROCKCHIP_SPI_CTRLR0);
	ग_लिखोl_relaxed(cr1, rs->regs + ROCKCHIP_SPI_CTRLR1);

	/* unक्रमtunately setting the fअगरo threshold level to generate an
	 * पूर्णांकerrupt exactly when the fअगरo is full करोesn't seem to work,
	 * so we need the strict inequality here
	 */
	अगर (xfer->len < rs->fअगरo_len)
		ग_लिखोl_relaxed(xfer->len - 1, rs->regs + ROCKCHIP_SPI_RXFTLR);
	अन्यथा
		ग_लिखोl_relaxed(rs->fअगरo_len / 2 - 1, rs->regs + ROCKCHIP_SPI_RXFTLR);

	ग_लिखोl_relaxed(rs->fअगरo_len / 2, rs->regs + ROCKCHIP_SPI_DMATDLR);
	ग_लिखोl_relaxed(rockchip_spi_calc_burst_size(xfer->len / rs->n_bytes) - 1,
		       rs->regs + ROCKCHIP_SPI_DMARDLR);
	ग_लिखोl_relaxed(dmacr, rs->regs + ROCKCHIP_SPI_DMACR);

	/* the hardware only supports an even घड़ी भागisor, so
	 * round भागisor = spiclk / speed up to nearest even number
	 * so that the resulting speed is <= the requested speed
	 */
	ग_लिखोl_relaxed(2 * DIV_ROUND_UP(rs->freq, 2 * xfer->speed_hz),
			rs->regs + ROCKCHIP_SPI_BAUDR);

	वापस 0;
पूर्ण

अटल माप_प्रकार rockchip_spi_max_transfer_size(काष्ठा spi_device *spi)
अणु
	वापस ROCKCHIP_SPI_MAX_TRANLEN;
पूर्ण

अटल पूर्णांक rockchip_spi_slave_पात(काष्ठा spi_controller *ctlr)
अणु
	काष्ठा rockchip_spi *rs = spi_controller_get_devdata(ctlr);

	rs->slave_पात = true;
	spi_finalize_current_transfer(ctlr);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_spi_transfer_one(
		काष्ठा spi_controller *ctlr,
		काष्ठा spi_device *spi,
		काष्ठा spi_transfer *xfer)
अणु
	काष्ठा rockchip_spi *rs = spi_controller_get_devdata(ctlr);
	पूर्णांक ret;
	bool use_dma;

	WARN_ON(पढ़ोl_relaxed(rs->regs + ROCKCHIP_SPI_SSIENR) &&
		(पढ़ोl_relaxed(rs->regs + ROCKCHIP_SPI_SR) & SR_BUSY));

	अगर (!xfer->tx_buf && !xfer->rx_buf) अणु
		dev_err(rs->dev, "No buffer for transfer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (xfer->len > ROCKCHIP_SPI_MAX_TRANLEN) अणु
		dev_err(rs->dev, "Transfer is too long (%d)\n", xfer->len);
		वापस -EINVAL;
	पूर्ण

	rs->n_bytes = xfer->bits_per_word <= 8 ? 1 : 2;

	use_dma = ctlr->can_dma ? ctlr->can_dma(ctlr, spi, xfer) : false;

	ret = rockchip_spi_config(rs, spi, xfer, use_dma, ctlr->slave);
	अगर (ret)
		वापस ret;

	अगर (use_dma)
		वापस rockchip_spi_prepare_dma(rs, ctlr, xfer);

	वापस rockchip_spi_prepare_irq(rs, xfer);
पूर्ण

अटल bool rockchip_spi_can_dma(काष्ठा spi_controller *ctlr,
				 काष्ठा spi_device *spi,
				 काष्ठा spi_transfer *xfer)
अणु
	काष्ठा rockchip_spi *rs = spi_controller_get_devdata(ctlr);
	अचिन्हित पूर्णांक bytes_per_word = xfer->bits_per_word <= 8 ? 1 : 2;

	/* अगर the numbor of spi words to transfer is less than the fअगरo
	 * length we can just fill the fअगरo and रुको क्रम a single irq,
	 * so करोn't bother setting up dma
	 */
	वापस xfer->len / bytes_per_word >= rs->fअगरo_len;
पूर्ण

अटल पूर्णांक rockchip_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा rockchip_spi *rs;
	काष्ठा spi_controller *ctlr;
	काष्ठा resource *mem;
	काष्ठा device_node *np = pdev->dev.of_node;
	u32 rsd_nsecs;
	bool slave_mode;

	slave_mode = of_property_पढ़ो_bool(np, "spi-slave");

	अगर (slave_mode)
		ctlr = spi_alloc_slave(&pdev->dev,
				माप(काष्ठा rockchip_spi));
	अन्यथा
		ctlr = spi_alloc_master(&pdev->dev,
				माप(काष्ठा rockchip_spi));

	अगर (!ctlr)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ctlr);

	rs = spi_controller_get_devdata(ctlr);
	ctlr->slave = slave_mode;

	/* Get basic io resource and map it */
	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	rs->regs = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(rs->regs)) अणु
		ret =  PTR_ERR(rs->regs);
		जाओ err_put_ctlr;
	पूर्ण

	rs->apb_pclk = devm_clk_get(&pdev->dev, "apb_pclk");
	अगर (IS_ERR(rs->apb_pclk)) अणु
		dev_err(&pdev->dev, "Failed to get apb_pclk\n");
		ret = PTR_ERR(rs->apb_pclk);
		जाओ err_put_ctlr;
	पूर्ण

	rs->spiclk = devm_clk_get(&pdev->dev, "spiclk");
	अगर (IS_ERR(rs->spiclk)) अणु
		dev_err(&pdev->dev, "Failed to get spi_pclk\n");
		ret = PTR_ERR(rs->spiclk);
		जाओ err_put_ctlr;
	पूर्ण

	ret = clk_prepare_enable(rs->apb_pclk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to enable apb_pclk\n");
		जाओ err_put_ctlr;
	पूर्ण

	ret = clk_prepare_enable(rs->spiclk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to enable spi_clk\n");
		जाओ err_disable_apbclk;
	पूर्ण

	spi_enable_chip(rs, false);

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ err_disable_spiclk;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, ret, rockchip_spi_isr, शून्य,
			IRQF_ONESHOT, dev_name(&pdev->dev), ctlr);
	अगर (ret)
		जाओ err_disable_spiclk;

	rs->dev = &pdev->dev;
	rs->freq = clk_get_rate(rs->spiclk);

	अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "rx-sample-delay-ns",
				  &rsd_nsecs)) अणु
		/* rx sample delay is expressed in parent घड़ी cycles (max 3) */
		u32 rsd = DIV_ROUND_CLOSEST(rsd_nsecs * (rs->freq >> 8),
				1000000000 >> 8);
		अगर (!rsd) अणु
			dev_warn(rs->dev, "%u Hz are too slow to express %u ns delay\n",
					rs->freq, rsd_nsecs);
		पूर्ण अन्यथा अगर (rsd > CR0_RSD_MAX) अणु
			rsd = CR0_RSD_MAX;
			dev_warn(rs->dev, "%u Hz are too fast to express %u ns delay, clamping at %u ns\n",
					rs->freq, rsd_nsecs,
					CR0_RSD_MAX * 1000000000U / rs->freq);
		पूर्ण
		rs->rsd = rsd;
	पूर्ण

	rs->fअगरo_len = get_fअगरo_len(rs);
	अगर (!rs->fअगरo_len) अणु
		dev_err(&pdev->dev, "Failed to get fifo length\n");
		ret = -EINVAL;
		जाओ err_disable_spiclk;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, ROCKCHIP_AUTOSUSPEND_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ctlr->स्वतः_runसमय_pm = true;
	ctlr->bus_num = pdev->id;
	ctlr->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LOOP | SPI_LSB_FIRST;
	अगर (slave_mode) अणु
		ctlr->mode_bits |= SPI_NO_CS;
		ctlr->slave_पात = rockchip_spi_slave_पात;
	पूर्ण अन्यथा अणु
		ctlr->flags = SPI_MASTER_GPIO_SS;
		ctlr->max_native_cs = ROCKCHIP_SPI_MAX_CS_NUM;
		/*
		 * rk spi0 has two native cs, spi1..5 one cs only
		 * अगर num-cs is missing in the dts, शेष to 1
		 */
		अगर (of_property_पढ़ो_u16(np, "num-cs", &ctlr->num_chipselect))
			ctlr->num_chipselect = 1;
		ctlr->use_gpio_descriptors = true;
	पूर्ण
	ctlr->dev.of_node = pdev->dev.of_node;
	ctlr->bits_per_word_mask = SPI_BPW_MASK(16) | SPI_BPW_MASK(8) | SPI_BPW_MASK(4);
	ctlr->min_speed_hz = rs->freq / BAUDR_SCKDV_MAX;
	ctlr->max_speed_hz = min(rs->freq / BAUDR_SCKDV_MIN, MAX_SCLK_OUT);

	ctlr->set_cs = rockchip_spi_set_cs;
	ctlr->transfer_one = rockchip_spi_transfer_one;
	ctlr->max_transfer_size = rockchip_spi_max_transfer_size;
	ctlr->handle_err = rockchip_spi_handle_err;

	ctlr->dma_tx = dma_request_chan(rs->dev, "tx");
	अगर (IS_ERR(ctlr->dma_tx)) अणु
		/* Check tx to see अगर we need defer probing driver */
		अगर (PTR_ERR(ctlr->dma_tx) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ err_disable_pm_runसमय;
		पूर्ण
		dev_warn(rs->dev, "Failed to request TX DMA channel\n");
		ctlr->dma_tx = शून्य;
	पूर्ण

	ctlr->dma_rx = dma_request_chan(rs->dev, "rx");
	अगर (IS_ERR(ctlr->dma_rx)) अणु
		अगर (PTR_ERR(ctlr->dma_rx) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ err_मुक्त_dma_tx;
		पूर्ण
		dev_warn(rs->dev, "Failed to request RX DMA channel\n");
		ctlr->dma_rx = शून्य;
	पूर्ण

	अगर (ctlr->dma_tx && ctlr->dma_rx) अणु
		rs->dma_addr_tx = mem->start + ROCKCHIP_SPI_TXDR;
		rs->dma_addr_rx = mem->start + ROCKCHIP_SPI_RXDR;
		ctlr->can_dma = rockchip_spi_can_dma;
	पूर्ण

	ret = devm_spi_रेजिस्टर_controller(&pdev->dev, ctlr);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register controller\n");
		जाओ err_मुक्त_dma_rx;
	पूर्ण

	वापस 0;

err_मुक्त_dma_rx:
	अगर (ctlr->dma_rx)
		dma_release_channel(ctlr->dma_rx);
err_मुक्त_dma_tx:
	अगर (ctlr->dma_tx)
		dma_release_channel(ctlr->dma_tx);
err_disable_pm_runसमय:
	pm_runसमय_disable(&pdev->dev);
err_disable_spiclk:
	clk_disable_unprepare(rs->spiclk);
err_disable_apbclk:
	clk_disable_unprepare(rs->apb_pclk);
err_put_ctlr:
	spi_controller_put(ctlr);

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctlr = spi_controller_get(platक्रमm_get_drvdata(pdev));
	काष्ठा rockchip_spi *rs = spi_controller_get_devdata(ctlr);

	pm_runसमय_get_sync(&pdev->dev);

	clk_disable_unprepare(rs->spiclk);
	clk_disable_unprepare(rs->apb_pclk);

	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);

	अगर (ctlr->dma_tx)
		dma_release_channel(ctlr->dma_tx);
	अगर (ctlr->dma_rx)
		dma_release_channel(ctlr->dma_rx);

	spi_controller_put(ctlr);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rockchip_spi_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा spi_controller *ctlr = dev_get_drvdata(dev);

	ret = spi_controller_suspend(ctlr);
	अगर (ret < 0)
		वापस ret;

	ret = pm_runसमय_क्रमce_suspend(dev);
	अगर (ret < 0)
		वापस ret;

	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_spi_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा spi_controller *ctlr = dev_get_drvdata(dev);
	काष्ठा rockchip_spi *rs = spi_controller_get_devdata(ctlr);

	pinctrl_pm_select_शेष_state(dev);

	ret = pm_runसमय_क्रमce_resume(dev);
	अगर (ret < 0)
		वापस ret;

	ret = spi_controller_resume(ctlr);
	अगर (ret < 0) अणु
		clk_disable_unprepare(rs->spiclk);
		clk_disable_unprepare(rs->apb_pclk);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rockchip_spi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *ctlr = dev_get_drvdata(dev);
	काष्ठा rockchip_spi *rs = spi_controller_get_devdata(ctlr);

	clk_disable_unprepare(rs->spiclk);
	clk_disable_unprepare(rs->apb_pclk);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_spi_runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा spi_controller *ctlr = dev_get_drvdata(dev);
	काष्ठा rockchip_spi *rs = spi_controller_get_devdata(ctlr);

	ret = clk_prepare_enable(rs->apb_pclk);
	अगर (ret < 0)
		वापस ret;

	ret = clk_prepare_enable(rs->spiclk);
	अगर (ret < 0)
		clk_disable_unprepare(rs->apb_pclk);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops rockchip_spi_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rockchip_spi_suspend, rockchip_spi_resume)
	SET_RUNTIME_PM_OPS(rockchip_spi_runसमय_suspend,
			   rockchip_spi_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_spi_dt_match[] = अणु
	अणु .compatible = "rockchip,px30-spi", पूर्ण,
	अणु .compatible = "rockchip,rk3036-spi", पूर्ण,
	अणु .compatible = "rockchip,rk3066-spi", पूर्ण,
	अणु .compatible = "rockchip,rk3188-spi", पूर्ण,
	अणु .compatible = "rockchip,rk3228-spi", पूर्ण,
	अणु .compatible = "rockchip,rk3288-spi", पूर्ण,
	अणु .compatible = "rockchip,rk3308-spi", पूर्ण,
	अणु .compatible = "rockchip,rk3328-spi", पूर्ण,
	अणु .compatible = "rockchip,rk3368-spi", पूर्ण,
	अणु .compatible = "rockchip,rk3399-spi", पूर्ण,
	अणु .compatible = "rockchip,rv1108-spi", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rockchip_spi_dt_match);

अटल काष्ठा platक्रमm_driver rockchip_spi_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
		.pm = &rockchip_spi_pm,
		.of_match_table = of_match_ptr(rockchip_spi_dt_match),
	पूर्ण,
	.probe = rockchip_spi_probe,
	.हटाओ = rockchip_spi_हटाओ,
पूर्ण;

module_platक्रमm_driver(rockchip_spi_driver);

MODULE_AUTHOR("Addy Ke <addy.ke@rock-chips.com>");
MODULE_DESCRIPTION("ROCKCHIP SPI Controller Driver");
MODULE_LICENSE("GPL v2");
