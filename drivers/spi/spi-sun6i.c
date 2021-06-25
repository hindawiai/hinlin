<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012 - 2014 Allwinner Tech
 * Pan Nan <pannan@allwinnertech.com>
 *
 * Copyright (C) 2014 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/dmaengine.h>

#समावेश <linux/spi/spi.h>

#घोषणा SUN6I_AUTOSUSPEND_TIMEOUT	2000

#घोषणा SUN6I_FIFO_DEPTH		128
#घोषणा SUN8I_FIFO_DEPTH		64

#घोषणा SUN6I_GBL_CTL_REG		0x04
#घोषणा SUN6I_GBL_CTL_BUS_ENABLE		BIT(0)
#घोषणा SUN6I_GBL_CTL_MASTER			BIT(1)
#घोषणा SUN6I_GBL_CTL_TP			BIT(7)
#घोषणा SUN6I_GBL_CTL_RST			BIT(31)

#घोषणा SUN6I_TFR_CTL_REG		0x08
#घोषणा SUN6I_TFR_CTL_CPHA			BIT(0)
#घोषणा SUN6I_TFR_CTL_CPOL			BIT(1)
#घोषणा SUN6I_TFR_CTL_SPOL			BIT(2)
#घोषणा SUN6I_TFR_CTL_CS_MASK			0x30
#घोषणा SUN6I_TFR_CTL_CS(cs)			(((cs) << 4) & SUN6I_TFR_CTL_CS_MASK)
#घोषणा SUN6I_TFR_CTL_CS_MANUAL			BIT(6)
#घोषणा SUN6I_TFR_CTL_CS_LEVEL			BIT(7)
#घोषणा SUN6I_TFR_CTL_DHB			BIT(8)
#घोषणा SUN6I_TFR_CTL_FBS			BIT(12)
#घोषणा SUN6I_TFR_CTL_XCH			BIT(31)

#घोषणा SUN6I_INT_CTL_REG		0x10
#घोषणा SUN6I_INT_CTL_RF_RDY			BIT(0)
#घोषणा SUN6I_INT_CTL_TF_ERQ			BIT(4)
#घोषणा SUN6I_INT_CTL_RF_OVF			BIT(8)
#घोषणा SUN6I_INT_CTL_TC			BIT(12)

#घोषणा SUN6I_INT_STA_REG		0x14

#घोषणा SUN6I_FIFO_CTL_REG		0x18
#घोषणा SUN6I_FIFO_CTL_RF_RDY_TRIG_LEVEL_MASK	0xff
#घोषणा SUN6I_FIFO_CTL_RF_DRQ_EN		BIT(8)
#घोषणा SUN6I_FIFO_CTL_RF_RDY_TRIG_LEVEL_BITS	0
#घोषणा SUN6I_FIFO_CTL_RF_RST			BIT(15)
#घोषणा SUN6I_FIFO_CTL_TF_ERQ_TRIG_LEVEL_MASK	0xff
#घोषणा SUN6I_FIFO_CTL_TF_ERQ_TRIG_LEVEL_BITS	16
#घोषणा SUN6I_FIFO_CTL_TF_DRQ_EN		BIT(24)
#घोषणा SUN6I_FIFO_CTL_TF_RST			BIT(31)

#घोषणा SUN6I_FIFO_STA_REG		0x1c
#घोषणा SUN6I_FIFO_STA_RF_CNT_MASK		GENMASK(7, 0)
#घोषणा SUN6I_FIFO_STA_TF_CNT_MASK		GENMASK(23, 16)

#घोषणा SUN6I_CLK_CTL_REG		0x24
#घोषणा SUN6I_CLK_CTL_CDR2_MASK			0xff
#घोषणा SUN6I_CLK_CTL_CDR2(भाग)			(((भाग) & SUN6I_CLK_CTL_CDR2_MASK) << 0)
#घोषणा SUN6I_CLK_CTL_CDR1_MASK			0xf
#घोषणा SUN6I_CLK_CTL_CDR1(भाग)			(((भाग) & SUN6I_CLK_CTL_CDR1_MASK) << 8)
#घोषणा SUN6I_CLK_CTL_DRS			BIT(12)

#घोषणा SUN6I_MAX_XFER_SIZE		0xffffff

#घोषणा SUN6I_BURST_CNT_REG		0x30

#घोषणा SUN6I_XMIT_CNT_REG		0x34

#घोषणा SUN6I_BURST_CTL_CNT_REG		0x38

#घोषणा SUN6I_TXDATA_REG		0x200
#घोषणा SUN6I_RXDATA_REG		0x300

काष्ठा sun6i_spi अणु
	काष्ठा spi_master	*master;
	व्योम __iomem		*base_addr;
	dma_addr_t		dma_addr_rx;
	dma_addr_t		dma_addr_tx;
	काष्ठा clk		*hclk;
	काष्ठा clk		*mclk;
	काष्ठा reset_control	*rstc;

	काष्ठा completion	करोne;

	स्थिर u8		*tx_buf;
	u8			*rx_buf;
	पूर्णांक			len;
	अचिन्हित दीर्घ		fअगरo_depth;
पूर्ण;

अटल अंतरभूत u32 sun6i_spi_पढ़ो(काष्ठा sun6i_spi *sspi, u32 reg)
अणु
	वापस पढ़ोl(sspi->base_addr + reg);
पूर्ण

अटल अंतरभूत व्योम sun6i_spi_ग_लिखो(काष्ठा sun6i_spi *sspi, u32 reg, u32 value)
अणु
	ग_लिखोl(value, sspi->base_addr + reg);
पूर्ण

अटल अंतरभूत u32 sun6i_spi_get_rx_fअगरo_count(काष्ठा sun6i_spi *sspi)
अणु
	u32 reg = sun6i_spi_पढ़ो(sspi, SUN6I_FIFO_STA_REG);

	वापस FIELD_GET(SUN6I_FIFO_STA_RF_CNT_MASK, reg);
पूर्ण

अटल अंतरभूत u32 sun6i_spi_get_tx_fअगरo_count(काष्ठा sun6i_spi *sspi)
अणु
	u32 reg = sun6i_spi_पढ़ो(sspi, SUN6I_FIFO_STA_REG);

	वापस FIELD_GET(SUN6I_FIFO_STA_TF_CNT_MASK, reg);
पूर्ण

अटल अंतरभूत व्योम sun6i_spi_disable_पूर्णांकerrupt(काष्ठा sun6i_spi *sspi, u32 mask)
अणु
	u32 reg = sun6i_spi_पढ़ो(sspi, SUN6I_INT_CTL_REG);

	reg &= ~mask;
	sun6i_spi_ग_लिखो(sspi, SUN6I_INT_CTL_REG, reg);
पूर्ण

अटल अंतरभूत व्योम sun6i_spi_drain_fअगरo(काष्ठा sun6i_spi *sspi)
अणु
	u32 len;
	u8 byte;

	/* See how much data is available */
	len = sun6i_spi_get_rx_fअगरo_count(sspi);

	जबतक (len--) अणु
		byte = पढ़ोb(sspi->base_addr + SUN6I_RXDATA_REG);
		अगर (sspi->rx_buf)
			*sspi->rx_buf++ = byte;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sun6i_spi_fill_fअगरo(काष्ठा sun6i_spi *sspi)
अणु
	u32 cnt;
	पूर्णांक len;
	u8 byte;

	/* See how much data we can fit */
	cnt = sspi->fअगरo_depth - sun6i_spi_get_tx_fअगरo_count(sspi);

	len = min((पूर्णांक)cnt, sspi->len);

	जबतक (len--) अणु
		byte = sspi->tx_buf ? *sspi->tx_buf++ : 0;
		ग_लिखोb(byte, sspi->base_addr + SUN6I_TXDATA_REG);
		sspi->len--;
	पूर्ण
पूर्ण

अटल व्योम sun6i_spi_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा sun6i_spi *sspi = spi_master_get_devdata(spi->master);
	u32 reg;

	reg = sun6i_spi_पढ़ो(sspi, SUN6I_TFR_CTL_REG);
	reg &= ~SUN6I_TFR_CTL_CS_MASK;
	reg |= SUN6I_TFR_CTL_CS(spi->chip_select);

	अगर (enable)
		reg |= SUN6I_TFR_CTL_CS_LEVEL;
	अन्यथा
		reg &= ~SUN6I_TFR_CTL_CS_LEVEL;

	sun6i_spi_ग_लिखो(sspi, SUN6I_TFR_CTL_REG, reg);
पूर्ण

अटल माप_प्रकार sun6i_spi_max_transfer_size(काष्ठा spi_device *spi)
अणु
	वापस SUN6I_MAX_XFER_SIZE - 1;
पूर्ण

अटल पूर्णांक sun6i_spi_prepare_dma(काष्ठा sun6i_spi *sspi,
				 काष्ठा spi_transfer *tfr)
अणु
	काष्ठा dma_async_tx_descriptor *rxdesc, *txdesc;
	काष्ठा spi_master *master = sspi->master;

	rxdesc = शून्य;
	अगर (tfr->rx_buf) अणु
		काष्ठा dma_slave_config rxconf = अणु
			.direction = DMA_DEV_TO_MEM,
			.src_addr = sspi->dma_addr_rx,
			.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
			.src_maxburst = 8,
		पूर्ण;

		dmaengine_slave_config(master->dma_rx, &rxconf);

		rxdesc = dmaengine_prep_slave_sg(master->dma_rx,
						 tfr->rx_sg.sgl,
						 tfr->rx_sg.nents,
						 DMA_DEV_TO_MEM,
						 DMA_PREP_INTERRUPT);
		अगर (!rxdesc)
			वापस -EINVAL;
	पूर्ण

	txdesc = शून्य;
	अगर (tfr->tx_buf) अणु
		काष्ठा dma_slave_config txconf = अणु
			.direction = DMA_MEM_TO_DEV,
			.dst_addr = sspi->dma_addr_tx,
			.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
			.dst_maxburst = 8,
		पूर्ण;

		dmaengine_slave_config(master->dma_tx, &txconf);

		txdesc = dmaengine_prep_slave_sg(master->dma_tx,
						 tfr->tx_sg.sgl,
						 tfr->tx_sg.nents,
						 DMA_MEM_TO_DEV,
						 DMA_PREP_INTERRUPT);
		अगर (!txdesc) अणु
			अगर (rxdesc)
				dmaengine_terminate_sync(master->dma_rx);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (tfr->rx_buf) अणु
		dmaengine_submit(rxdesc);
		dma_async_issue_pending(master->dma_rx);
	पूर्ण

	अगर (tfr->tx_buf) अणु
		dmaengine_submit(txdesc);
		dma_async_issue_pending(master->dma_tx);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_spi_transfer_one(काष्ठा spi_master *master,
				  काष्ठा spi_device *spi,
				  काष्ठा spi_transfer *tfr)
अणु
	काष्ठा sun6i_spi *sspi = spi_master_get_devdata(master);
	अचिन्हित पूर्णांक mclk_rate, भाग, भाग_cdr1, भाग_cdr2, समयout;
	अचिन्हित पूर्णांक start, end, tx_समय;
	अचिन्हित पूर्णांक trig_level;
	अचिन्हित पूर्णांक tx_len = 0, rx_len = 0;
	bool use_dma;
	पूर्णांक ret = 0;
	u32 reg;

	अगर (tfr->len > SUN6I_MAX_XFER_SIZE)
		वापस -EINVAL;

	reinit_completion(&sspi->करोne);
	sspi->tx_buf = tfr->tx_buf;
	sspi->rx_buf = tfr->rx_buf;
	sspi->len = tfr->len;
	use_dma = master->can_dma ? master->can_dma(master, spi, tfr) : false;

	/* Clear pending पूर्णांकerrupts */
	sun6i_spi_ग_लिखो(sspi, SUN6I_INT_STA_REG, ~0);

	/* Reset FIFO */
	sun6i_spi_ग_लिखो(sspi, SUN6I_FIFO_CTL_REG,
			SUN6I_FIFO_CTL_RF_RST | SUN6I_FIFO_CTL_TF_RST);

	reg = 0;

	अगर (!use_dma) अणु
		/*
		 * Setup FIFO पूर्णांकerrupt trigger level
		 * Here we choose 3/4 of the full fअगरo depth, as it's
		 * the hardcoded value used in old generation of Allwinner
		 * SPI controller. (See spi-sun4i.c)
		 */
		trig_level = sspi->fअगरo_depth / 4 * 3;
	पूर्ण अन्यथा अणु
		/*
		 * Setup FIFO DMA request trigger level
		 * We choose 1/2 of the full fअगरo depth, that value will
		 * be used as DMA burst length.
		 */
		trig_level = sspi->fअगरo_depth / 2;

		अगर (tfr->tx_buf)
			reg |= SUN6I_FIFO_CTL_TF_DRQ_EN;
		अगर (tfr->rx_buf)
			reg |= SUN6I_FIFO_CTL_RF_DRQ_EN;
	पूर्ण

	reg |= (trig_level << SUN6I_FIFO_CTL_RF_RDY_TRIG_LEVEL_BITS) |
	       (trig_level << SUN6I_FIFO_CTL_TF_ERQ_TRIG_LEVEL_BITS);

	sun6i_spi_ग_लिखो(sspi, SUN6I_FIFO_CTL_REG, reg);

	/*
	 * Setup the transfer control रेजिस्टर: Chip Select,
	 * polarities, etc.
	 */
	reg = sun6i_spi_पढ़ो(sspi, SUN6I_TFR_CTL_REG);

	अगर (spi->mode & SPI_CPOL)
		reg |= SUN6I_TFR_CTL_CPOL;
	अन्यथा
		reg &= ~SUN6I_TFR_CTL_CPOL;

	अगर (spi->mode & SPI_CPHA)
		reg |= SUN6I_TFR_CTL_CPHA;
	अन्यथा
		reg &= ~SUN6I_TFR_CTL_CPHA;

	अगर (spi->mode & SPI_LSB_FIRST)
		reg |= SUN6I_TFR_CTL_FBS;
	अन्यथा
		reg &= ~SUN6I_TFR_CTL_FBS;

	/*
	 * If it's a TX only transfer, we don't want to fill the RX
	 * FIFO with bogus data
	 */
	अगर (sspi->rx_buf) अणु
		reg &= ~SUN6I_TFR_CTL_DHB;
		rx_len = tfr->len;
	पूर्ण अन्यथा अणु
		reg |= SUN6I_TFR_CTL_DHB;
	पूर्ण

	/* We want to control the chip select manually */
	reg |= SUN6I_TFR_CTL_CS_MANUAL;

	sun6i_spi_ग_लिखो(sspi, SUN6I_TFR_CTL_REG, reg);

	/* Ensure that we have a parent घड़ी fast enough */
	mclk_rate = clk_get_rate(sspi->mclk);
	अगर (mclk_rate < (2 * tfr->speed_hz)) अणु
		clk_set_rate(sspi->mclk, 2 * tfr->speed_hz);
		mclk_rate = clk_get_rate(sspi->mclk);
	पूर्ण

	/*
	 * Setup घड़ी भागider.
	 *
	 * We have two choices there. Either we can use the घड़ी
	 * भागide rate 1, which is calculated thanks to this क्रमmula:
	 * SPI_CLK = MOD_CLK / (2 ^ cdr)
	 * Or we can use CDR2, which is calculated with the क्रमmula:
	 * SPI_CLK = MOD_CLK / (2 * (cdr + 1))
	 * Wether we use the क्रमmer or the latter is set through the
	 * DRS bit.
	 *
	 * First try CDR2, and अगर we can't reach the expected
	 * frequency, fall back to CDR1.
	 */
	भाग_cdr1 = DIV_ROUND_UP(mclk_rate, tfr->speed_hz);
	भाग_cdr2 = DIV_ROUND_UP(भाग_cdr1, 2);
	अगर (भाग_cdr2 <= (SUN6I_CLK_CTL_CDR2_MASK + 1)) अणु
		reg = SUN6I_CLK_CTL_CDR2(भाग_cdr2 - 1) | SUN6I_CLK_CTL_DRS;
		tfr->effective_speed_hz = mclk_rate / (2 * भाग_cdr2);
	पूर्ण अन्यथा अणु
		भाग = min(SUN6I_CLK_CTL_CDR1_MASK, order_base_2(भाग_cdr1));
		reg = SUN6I_CLK_CTL_CDR1(भाग);
		tfr->effective_speed_hz = mclk_rate / (1 << भाग);
	पूर्ण

	sun6i_spi_ग_लिखो(sspi, SUN6I_CLK_CTL_REG, reg);

	/* Setup the transfer now... */
	अगर (sspi->tx_buf)
		tx_len = tfr->len;

	/* Setup the counters */
	sun6i_spi_ग_लिखो(sspi, SUN6I_BURST_CNT_REG, tfr->len);
	sun6i_spi_ग_लिखो(sspi, SUN6I_XMIT_CNT_REG, tx_len);
	sun6i_spi_ग_लिखो(sspi, SUN6I_BURST_CTL_CNT_REG, tx_len);

	अगर (!use_dma) अणु
		/* Fill the TX FIFO */
		sun6i_spi_fill_fअगरo(sspi);
	पूर्ण अन्यथा अणु
		ret = sun6i_spi_prepare_dma(sspi, tfr);
		अगर (ret) अणु
			dev_warn(&master->dev,
				 "%s: prepare DMA failed, ret=%d",
				 dev_name(&spi->dev), ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Enable the पूर्णांकerrupts */
	reg = SUN6I_INT_CTL_TC;

	अगर (!use_dma) अणु
		अगर (rx_len > sspi->fअगरo_depth)
			reg |= SUN6I_INT_CTL_RF_RDY;
		अगर (tx_len > sspi->fअगरo_depth)
			reg |= SUN6I_INT_CTL_TF_ERQ;
	पूर्ण

	sun6i_spi_ग_लिखो(sspi, SUN6I_INT_CTL_REG, reg);

	/* Start the transfer */
	reg = sun6i_spi_पढ़ो(sspi, SUN6I_TFR_CTL_REG);
	sun6i_spi_ग_लिखो(sspi, SUN6I_TFR_CTL_REG, reg | SUN6I_TFR_CTL_XCH);

	tx_समय = max(tfr->len * 8 * 2 / (tfr->speed_hz / 1000), 100U);
	start = jअगरfies;
	समयout = रुको_क्रम_completion_समयout(&sspi->करोne,
					      msecs_to_jअगरfies(tx_समय));
	end = jअगरfies;
	अगर (!समयout) अणु
		dev_warn(&master->dev,
			 "%s: timeout transferring %u bytes@%iHz for %i(%i)ms",
			 dev_name(&spi->dev), tfr->len, tfr->speed_hz,
			 jअगरfies_to_msecs(end - start), tx_समय);
		ret = -ETIMEDOUT;
	पूर्ण

	sun6i_spi_ग_लिखो(sspi, SUN6I_INT_CTL_REG, 0);

	अगर (ret && use_dma) अणु
		dmaengine_terminate_sync(master->dma_rx);
		dmaengine_terminate_sync(master->dma_tx);
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t sun6i_spi_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sun6i_spi *sspi = dev_id;
	u32 status = sun6i_spi_पढ़ो(sspi, SUN6I_INT_STA_REG);

	/* Transfer complete */
	अगर (status & SUN6I_INT_CTL_TC) अणु
		sun6i_spi_ग_लिखो(sspi, SUN6I_INT_STA_REG, SUN6I_INT_CTL_TC);
		sun6i_spi_drain_fअगरo(sspi);
		complete(&sspi->करोne);
		वापस IRQ_HANDLED;
	पूर्ण

	/* Receive FIFO 3/4 full */
	अगर (status & SUN6I_INT_CTL_RF_RDY) अणु
		sun6i_spi_drain_fअगरo(sspi);
		/* Only clear the पूर्णांकerrupt _after_ draining the FIFO */
		sun6i_spi_ग_लिखो(sspi, SUN6I_INT_STA_REG, SUN6I_INT_CTL_RF_RDY);
		वापस IRQ_HANDLED;
	पूर्ण

	/* Transmit FIFO 3/4 empty */
	अगर (status & SUN6I_INT_CTL_TF_ERQ) अणु
		sun6i_spi_fill_fअगरo(sspi);

		अगर (!sspi->len)
			/* nothing left to transmit */
			sun6i_spi_disable_पूर्णांकerrupt(sspi, SUN6I_INT_CTL_TF_ERQ);

		/* Only clear the पूर्णांकerrupt _after_ re-seeding the FIFO */
		sun6i_spi_ग_लिखो(sspi, SUN6I_INT_STA_REG, SUN6I_INT_CTL_TF_ERQ);

		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक sun6i_spi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा sun6i_spi *sspi = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = clk_prepare_enable(sspi->hclk);
	अगर (ret) अणु
		dev_err(dev, "Couldn't enable AHB clock\n");
		जाओ out;
	पूर्ण

	ret = clk_prepare_enable(sspi->mclk);
	अगर (ret) अणु
		dev_err(dev, "Couldn't enable module clock\n");
		जाओ err;
	पूर्ण

	ret = reset_control_deनिश्चित(sspi->rstc);
	अगर (ret) अणु
		dev_err(dev, "Couldn't deassert the device from reset\n");
		जाओ err2;
	पूर्ण

	sun6i_spi_ग_लिखो(sspi, SUN6I_GBL_CTL_REG,
			SUN6I_GBL_CTL_BUS_ENABLE | SUN6I_GBL_CTL_MASTER | SUN6I_GBL_CTL_TP);

	वापस 0;

err2:
	clk_disable_unprepare(sspi->mclk);
err:
	clk_disable_unprepare(sspi->hclk);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक sun6i_spi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा sun6i_spi *sspi = spi_master_get_devdata(master);

	reset_control_निश्चित(sspi->rstc);
	clk_disable_unprepare(sspi->mclk);
	clk_disable_unprepare(sspi->hclk);

	वापस 0;
पूर्ण

अटल bool sun6i_spi_can_dma(काष्ठा spi_master *master,
			      काष्ठा spi_device *spi,
			      काष्ठा spi_transfer *xfer)
अणु
	काष्ठा sun6i_spi *sspi = spi_master_get_devdata(master);

	/*
	 * If the number of spi words to transfer is less or equal than
	 * the fअगरo length we can just fill the fअगरo and रुको क्रम a single
	 * irq, so करोn't bother setting up dma
	 */
	वापस xfer->len > sspi->fअगरo_depth;
पूर्ण

अटल पूर्णांक sun6i_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा sun6i_spi *sspi;
	काष्ठा resource *mem;
	पूर्णांक ret = 0, irq;

	master = spi_alloc_master(&pdev->dev, माप(काष्ठा sun6i_spi));
	अगर (!master) अणु
		dev_err(&pdev->dev, "Unable to allocate SPI Master\n");
		वापस -ENOMEM;
	पूर्ण

	platक्रमm_set_drvdata(pdev, master);
	sspi = spi_master_get_devdata(master);

	sspi->base_addr = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &mem);
	अगर (IS_ERR(sspi->base_addr)) अणु
		ret = PTR_ERR(sspi->base_addr);
		जाओ err_मुक्त_master;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = -ENXIO;
		जाओ err_मुक्त_master;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, sun6i_spi_handler,
			       0, "sun6i-spi", sspi);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot request IRQ\n");
		जाओ err_मुक्त_master;
	पूर्ण

	sspi->master = master;
	sspi->fअगरo_depth = (अचिन्हित दीर्घ)of_device_get_match_data(&pdev->dev);

	master->max_speed_hz = 100 * 1000 * 1000;
	master->min_speed_hz = 3 * 1000;
	master->use_gpio_descriptors = true;
	master->set_cs = sun6i_spi_set_cs;
	master->transfer_one = sun6i_spi_transfer_one;
	master->num_chipselect = 4;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH | SPI_LSB_FIRST;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->dev.of_node = pdev->dev.of_node;
	master->स्वतः_runसमय_pm = true;
	master->max_transfer_size = sun6i_spi_max_transfer_size;

	sspi->hclk = devm_clk_get(&pdev->dev, "ahb");
	अगर (IS_ERR(sspi->hclk)) अणु
		dev_err(&pdev->dev, "Unable to acquire AHB clock\n");
		ret = PTR_ERR(sspi->hclk);
		जाओ err_मुक्त_master;
	पूर्ण

	sspi->mclk = devm_clk_get(&pdev->dev, "mod");
	अगर (IS_ERR(sspi->mclk)) अणु
		dev_err(&pdev->dev, "Unable to acquire module clock\n");
		ret = PTR_ERR(sspi->mclk);
		जाओ err_मुक्त_master;
	पूर्ण

	init_completion(&sspi->करोne);

	sspi->rstc = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(sspi->rstc)) अणु
		dev_err(&pdev->dev, "Couldn't get reset controller\n");
		ret = PTR_ERR(sspi->rstc);
		जाओ err_मुक्त_master;
	पूर्ण

	master->dma_tx = dma_request_chan(&pdev->dev, "tx");
	अगर (IS_ERR(master->dma_tx)) अणु
		/* Check tx to see अगर we need defer probing driver */
		अगर (PTR_ERR(master->dma_tx) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ err_मुक्त_master;
		पूर्ण
		dev_warn(&pdev->dev, "Failed to request TX DMA channel\n");
		master->dma_tx = शून्य;
	पूर्ण

	master->dma_rx = dma_request_chan(&pdev->dev, "rx");
	अगर (IS_ERR(master->dma_rx)) अणु
		अगर (PTR_ERR(master->dma_rx) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ err_मुक्त_dma_tx;
		पूर्ण
		dev_warn(&pdev->dev, "Failed to request RX DMA channel\n");
		master->dma_rx = शून्य;
	पूर्ण

	अगर (master->dma_tx && master->dma_rx) अणु
		sspi->dma_addr_tx = mem->start + SUN6I_TXDATA_REG;
		sspi->dma_addr_rx = mem->start + SUN6I_RXDATA_REG;
		master->can_dma = sun6i_spi_can_dma;
	पूर्ण

	/*
	 * This wake-up/shutकरोwn pattern is to be able to have the
	 * device woken up, even अगर runसमय_pm is disabled
	 */
	ret = sun6i_spi_runसमय_resume(&pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't resume the device\n");
		जाओ err_मुक्त_dma_rx;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, SUN6I_AUTOSUSPEND_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot register SPI master\n");
		जाओ err_pm_disable;
	पूर्ण

	वापस 0;

err_pm_disable:
	pm_runसमय_disable(&pdev->dev);
	sun6i_spi_runसमय_suspend(&pdev->dev);
err_मुक्त_dma_rx:
	अगर (master->dma_rx)
		dma_release_channel(master->dma_rx);
err_मुक्त_dma_tx:
	अगर (master->dma_tx)
		dma_release_channel(master->dma_tx);
err_मुक्त_master:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक sun6i_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);

	pm_runसमय_क्रमce_suspend(&pdev->dev);

	अगर (master->dma_tx)
		dma_release_channel(master->dma_tx);
	अगर (master->dma_rx)
		dma_release_channel(master->dma_rx);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun6i_spi_match[] = अणु
	अणु .compatible = "allwinner,sun6i-a31-spi", .data = (व्योम *)SUN6I_FIFO_DEPTH पूर्ण,
	अणु .compatible = "allwinner,sun8i-h3-spi",  .data = (व्योम *)SUN8I_FIFO_DEPTH पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun6i_spi_match);

अटल स्थिर काष्ठा dev_pm_ops sun6i_spi_pm_ops = अणु
	.runसमय_resume		= sun6i_spi_runसमय_resume,
	.runसमय_suspend	= sun6i_spi_runसमय_suspend,
पूर्ण;

अटल काष्ठा platक्रमm_driver sun6i_spi_driver = अणु
	.probe	= sun6i_spi_probe,
	.हटाओ	= sun6i_spi_हटाओ,
	.driver	= अणु
		.name		= "sun6i-spi",
		.of_match_table	= sun6i_spi_match,
		.pm		= &sun6i_spi_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun6i_spi_driver);

MODULE_AUTHOR("Pan Nan <pannan@allwinnertech.com>");
MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_DESCRIPTION("Allwinner A31 SPI controller driver");
MODULE_LICENSE("GPL");
