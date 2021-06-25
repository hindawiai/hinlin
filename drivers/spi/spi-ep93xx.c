<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Cirrus Logic EP93xx SPI controller.
 *
 * Copyright (C) 2010-2011 Mika Westerberg
 *
 * Explicit FIFO handling code was inspired by amba-pl022 driver.
 *
 * Chip select support using other than built-in GPIOs by H. Hartley Sweeten.
 *
 * For more inक्रमmation about the SPI controller see करोcumentation on Cirrus
 * Logic web site:
 *     https://www.cirrus.com/en/pubs/manual/EP93xx_Users_Guide_UM1.pdf
 */

#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/spi/spi.h>

#समावेश <linux/platक्रमm_data/dma-ep93xx.h>
#समावेश <linux/platक्रमm_data/spi-ep93xx.h>

#घोषणा SSPCR0			0x0000
#घोषणा SSPCR0_SPO		BIT(6)
#घोषणा SSPCR0_SPH		BIT(7)
#घोषणा SSPCR0_SCR_SHIFT	8

#घोषणा SSPCR1			0x0004
#घोषणा SSPCR1_RIE		BIT(0)
#घोषणा SSPCR1_TIE		BIT(1)
#घोषणा SSPCR1_RORIE		BIT(2)
#घोषणा SSPCR1_LBM		BIT(3)
#घोषणा SSPCR1_SSE		BIT(4)
#घोषणा SSPCR1_MS		BIT(5)
#घोषणा SSPCR1_SOD		BIT(6)

#घोषणा SSPDR			0x0008

#घोषणा SSPSR			0x000c
#घोषणा SSPSR_TFE		BIT(0)
#घोषणा SSPSR_TNF		BIT(1)
#घोषणा SSPSR_RNE		BIT(2)
#घोषणा SSPSR_RFF		BIT(3)
#घोषणा SSPSR_BSY		BIT(4)
#घोषणा SSPCPSR			0x0010

#घोषणा SSPIIR			0x0014
#घोषणा SSPIIR_RIS		BIT(0)
#घोषणा SSPIIR_TIS		BIT(1)
#घोषणा SSPIIR_RORIS		BIT(2)
#घोषणा SSPICR			SSPIIR

/* समयout in milliseconds */
#घोषणा SPI_TIMEOUT		5
/* maximum depth of RX/TX FIFO */
#घोषणा SPI_FIFO_SIZE		8

/**
 * काष्ठा ep93xx_spi - EP93xx SPI controller काष्ठाure
 * @clk: घड़ी क्रम the controller
 * @mmio: poपूर्णांकer to ioremap()'d रेजिस्टरs
 * @sspdr_phys: physical address of the SSPDR रेजिस्टर
 * @tx: current byte in transfer to transmit
 * @rx: current byte in transfer to receive
 * @fअगरo_level: how full is FIFO (%0..%SPI_FIFO_SIZE - %1). Receiving one
 *              frame decreases this level and sending one frame increases it.
 * @dma_rx: RX DMA channel
 * @dma_tx: TX DMA channel
 * @dma_rx_data: RX parameters passed to the DMA engine
 * @dma_tx_data: TX parameters passed to the DMA engine
 * @rx_sgt: sg table क्रम RX transfers
 * @tx_sgt: sg table क्रम TX transfers
 * @zeropage: dummy page used as RX buffer when only TX buffer is passed in by
 *            the client
 */
काष्ठा ep93xx_spi अणु
	काष्ठा clk			*clk;
	व्योम __iomem			*mmio;
	अचिन्हित दीर्घ			sspdr_phys;
	माप_प्रकार				tx;
	माप_प्रकार				rx;
	माप_प्रकार				fअगरo_level;
	काष्ठा dma_chan			*dma_rx;
	काष्ठा dma_chan			*dma_tx;
	काष्ठा ep93xx_dma_data		dma_rx_data;
	काष्ठा ep93xx_dma_data		dma_tx_data;
	काष्ठा sg_table			rx_sgt;
	काष्ठा sg_table			tx_sgt;
	व्योम				*zeropage;
पूर्ण;

/* converts bits per word to CR0.DSS value */
#घोषणा bits_per_word_to_dss(bpw)	((bpw) - 1)

/**
 * ep93xx_spi_calc_भागisors() - calculates SPI घड़ी भागisors
 * @master: SPI master
 * @rate: desired SPI output घड़ी rate
 * @भाग_cpsr: poपूर्णांकer to वापस the cpsr (pre-scaler) भागider
 * @भाग_scr: poपूर्णांकer to वापस the scr भागider
 */
अटल पूर्णांक ep93xx_spi_calc_भागisors(काष्ठा spi_master *master,
				    u32 rate, u8 *भाग_cpsr, u8 *भाग_scr)
अणु
	काष्ठा ep93xx_spi *espi = spi_master_get_devdata(master);
	अचिन्हित दीर्घ spi_clk_rate = clk_get_rate(espi->clk);
	पूर्णांक cpsr, scr;

	/*
	 * Make sure that max value is between values supported by the
	 * controller.
	 */
	rate = clamp(rate, master->min_speed_hz, master->max_speed_hz);

	/*
	 * Calculate भागisors so that we can get speed according the
	 * following क्रमmula:
	 *	rate = spi_घड़ी_rate / (cpsr * (1 + scr))
	 *
	 * cpsr must be even number and starts from 2, scr can be any number
	 * between 0 and 255.
	 */
	क्रम (cpsr = 2; cpsr <= 254; cpsr += 2) अणु
		क्रम (scr = 0; scr <= 255; scr++) अणु
			अगर ((spi_clk_rate / (cpsr * (scr + 1))) <= rate) अणु
				*भाग_scr = (u8)scr;
				*भाग_cpsr = (u8)cpsr;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ep93xx_spi_chip_setup(काष्ठा spi_master *master,
				 काष्ठा spi_device *spi,
				 काष्ठा spi_transfer *xfer)
अणु
	काष्ठा ep93xx_spi *espi = spi_master_get_devdata(master);
	u8 dss = bits_per_word_to_dss(xfer->bits_per_word);
	u8 भाग_cpsr = 0;
	u8 भाग_scr = 0;
	u16 cr0;
	पूर्णांक err;

	err = ep93xx_spi_calc_भागisors(master, xfer->speed_hz,
				       &भाग_cpsr, &भाग_scr);
	अगर (err)
		वापस err;

	cr0 = भाग_scr << SSPCR0_SCR_SHIFT;
	अगर (spi->mode & SPI_CPOL)
		cr0 |= SSPCR0_SPO;
	अगर (spi->mode & SPI_CPHA)
		cr0 |= SSPCR0_SPH;
	cr0 |= dss;

	dev_dbg(&master->dev, "setup: mode %d, cpsr %d, scr %d, dss %d\n",
		spi->mode, भाग_cpsr, भाग_scr, dss);
	dev_dbg(&master->dev, "setup: cr0 %#x\n", cr0);

	ग_लिखोl(भाग_cpsr, espi->mmio + SSPCPSR);
	ग_लिखोl(cr0, espi->mmio + SSPCR0);

	वापस 0;
पूर्ण

अटल व्योम ep93xx_करो_ग_लिखो(काष्ठा spi_master *master)
अणु
	काष्ठा ep93xx_spi *espi = spi_master_get_devdata(master);
	काष्ठा spi_transfer *xfer = master->cur_msg->state;
	u32 val = 0;

	अगर (xfer->bits_per_word > 8) अणु
		अगर (xfer->tx_buf)
			val = ((u16 *)xfer->tx_buf)[espi->tx];
		espi->tx += 2;
	पूर्ण अन्यथा अणु
		अगर (xfer->tx_buf)
			val = ((u8 *)xfer->tx_buf)[espi->tx];
		espi->tx += 1;
	पूर्ण
	ग_लिखोl(val, espi->mmio + SSPDR);
पूर्ण

अटल व्योम ep93xx_करो_पढ़ो(काष्ठा spi_master *master)
अणु
	काष्ठा ep93xx_spi *espi = spi_master_get_devdata(master);
	काष्ठा spi_transfer *xfer = master->cur_msg->state;
	u32 val;

	val = पढ़ोl(espi->mmio + SSPDR);
	अगर (xfer->bits_per_word > 8) अणु
		अगर (xfer->rx_buf)
			((u16 *)xfer->rx_buf)[espi->rx] = val;
		espi->rx += 2;
	पूर्ण अन्यथा अणु
		अगर (xfer->rx_buf)
			((u8 *)xfer->rx_buf)[espi->rx] = val;
		espi->rx += 1;
	पूर्ण
पूर्ण

/**
 * ep93xx_spi_पढ़ो_ग_लिखो() - perक्रमm next RX/TX transfer
 * @master: SPI master
 *
 * This function transfers next bytes (or half-words) to/from RX/TX FIFOs. If
 * called several बार, the whole transfer will be completed. Returns
 * %-EINPROGRESS when current transfer was not yet completed otherwise %0.
 *
 * When this function is finished, RX FIFO should be empty and TX FIFO should be
 * full.
 */
अटल पूर्णांक ep93xx_spi_पढ़ो_ग_लिखो(काष्ठा spi_master *master)
अणु
	काष्ठा ep93xx_spi *espi = spi_master_get_devdata(master);
	काष्ठा spi_transfer *xfer = master->cur_msg->state;

	/* पढ़ो as दीर्घ as RX FIFO has frames in it */
	जबतक ((पढ़ोl(espi->mmio + SSPSR) & SSPSR_RNE)) अणु
		ep93xx_करो_पढ़ो(master);
		espi->fअगरo_level--;
	पूर्ण

	/* ग_लिखो as दीर्घ as TX FIFO has room */
	जबतक (espi->fअगरo_level < SPI_FIFO_SIZE && espi->tx < xfer->len) अणु
		ep93xx_करो_ग_लिखो(master);
		espi->fअगरo_level++;
	पूर्ण

	अगर (espi->rx == xfer->len)
		वापस 0;

	वापस -EINPROGRESS;
पूर्ण

अटल क्रमागत dma_transfer_direction
ep93xx_dma_data_to_trans_dir(क्रमागत dma_data_direction dir)
अणु
	चयन (dir) अणु
	हाल DMA_TO_DEVICE:
		वापस DMA_MEM_TO_DEV;
	हाल DMA_FROM_DEVICE:
		वापस DMA_DEV_TO_MEM;
	शेष:
		वापस DMA_TRANS_NONE;
	पूर्ण
पूर्ण

/**
 * ep93xx_spi_dma_prepare() - prepares a DMA transfer
 * @master: SPI master
 * @dir: DMA transfer direction
 *
 * Function configures the DMA, maps the buffer and prepares the DMA
 * descriptor. Returns a valid DMA descriptor in हाल of success and ERR_PTR
 * in हाल of failure.
 */
अटल काष्ठा dma_async_tx_descriptor *
ep93xx_spi_dma_prepare(काष्ठा spi_master *master,
		       क्रमागत dma_data_direction dir)
अणु
	काष्ठा ep93xx_spi *espi = spi_master_get_devdata(master);
	काष्ठा spi_transfer *xfer = master->cur_msg->state;
	काष्ठा dma_async_tx_descriptor *txd;
	क्रमागत dma_slave_buswidth buswidth;
	काष्ठा dma_slave_config conf;
	काष्ठा scatterlist *sg;
	काष्ठा sg_table *sgt;
	काष्ठा dma_chan *chan;
	स्थिर व्योम *buf, *pbuf;
	माप_प्रकार len = xfer->len;
	पूर्णांक i, ret, nents;

	अगर (xfer->bits_per_word > 8)
		buswidth = DMA_SLAVE_BUSWIDTH_2_BYTES;
	अन्यथा
		buswidth = DMA_SLAVE_BUSWIDTH_1_BYTE;

	स_रखो(&conf, 0, माप(conf));
	conf.direction = ep93xx_dma_data_to_trans_dir(dir);

	अगर (dir == DMA_FROM_DEVICE) अणु
		chan = espi->dma_rx;
		buf = xfer->rx_buf;
		sgt = &espi->rx_sgt;

		conf.src_addr = espi->sspdr_phys;
		conf.src_addr_width = buswidth;
	पूर्ण अन्यथा अणु
		chan = espi->dma_tx;
		buf = xfer->tx_buf;
		sgt = &espi->tx_sgt;

		conf.dst_addr = espi->sspdr_phys;
		conf.dst_addr_width = buswidth;
	पूर्ण

	ret = dmaengine_slave_config(chan, &conf);
	अगर (ret)
		वापस ERR_PTR(ret);

	/*
	 * We need to split the transfer पूर्णांकo PAGE_SIZE'd chunks. This is
	 * because we are using @espi->zeropage to provide a zero RX buffer
	 * क्रम the TX transfers and we have only allocated one page क्रम that.
	 *
	 * For perक्रमmance reasons we allocate a new sg_table only when
	 * needed. Otherwise we will re-use the current one. Eventually the
	 * last sg_table is released in ep93xx_spi_release_dma().
	 */

	nents = DIV_ROUND_UP(len, PAGE_SIZE);
	अगर (nents != sgt->nents) अणु
		sg_मुक्त_table(sgt);

		ret = sg_alloc_table(sgt, nents, GFP_KERNEL);
		अगर (ret)
			वापस ERR_PTR(ret);
	पूर्ण

	pbuf = buf;
	क्रम_each_sg(sgt->sgl, sg, sgt->nents, i) अणु
		माप_प्रकार bytes = min_t(माप_प्रकार, len, PAGE_SIZE);

		अगर (buf) अणु
			sg_set_page(sg, virt_to_page(pbuf), bytes,
				    offset_in_page(pbuf));
		पूर्ण अन्यथा अणु
			sg_set_page(sg, virt_to_page(espi->zeropage),
				    bytes, 0);
		पूर्ण

		pbuf += bytes;
		len -= bytes;
	पूर्ण

	अगर (WARN_ON(len)) अणु
		dev_warn(&master->dev, "len = %zu expected 0!\n", len);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	nents = dma_map_sg(chan->device->dev, sgt->sgl, sgt->nents, dir);
	अगर (!nents)
		वापस ERR_PTR(-ENOMEM);

	txd = dmaengine_prep_slave_sg(chan, sgt->sgl, nents, conf.direction,
				      DMA_CTRL_ACK);
	अगर (!txd) अणु
		dma_unmap_sg(chan->device->dev, sgt->sgl, sgt->nents, dir);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	वापस txd;
पूर्ण

/**
 * ep93xx_spi_dma_finish() - finishes with a DMA transfer
 * @master: SPI master
 * @dir: DMA transfer direction
 *
 * Function finishes with the DMA transfer. After this, the DMA buffer is
 * unmapped.
 */
अटल व्योम ep93xx_spi_dma_finish(काष्ठा spi_master *master,
				  क्रमागत dma_data_direction dir)
अणु
	काष्ठा ep93xx_spi *espi = spi_master_get_devdata(master);
	काष्ठा dma_chan *chan;
	काष्ठा sg_table *sgt;

	अगर (dir == DMA_FROM_DEVICE) अणु
		chan = espi->dma_rx;
		sgt = &espi->rx_sgt;
	पूर्ण अन्यथा अणु
		chan = espi->dma_tx;
		sgt = &espi->tx_sgt;
	पूर्ण

	dma_unmap_sg(chan->device->dev, sgt->sgl, sgt->nents, dir);
पूर्ण

अटल व्योम ep93xx_spi_dma_callback(व्योम *callback_param)
अणु
	काष्ठा spi_master *master = callback_param;

	ep93xx_spi_dma_finish(master, DMA_TO_DEVICE);
	ep93xx_spi_dma_finish(master, DMA_FROM_DEVICE);

	spi_finalize_current_transfer(master);
पूर्ण

अटल पूर्णांक ep93xx_spi_dma_transfer(काष्ठा spi_master *master)
अणु
	काष्ठा ep93xx_spi *espi = spi_master_get_devdata(master);
	काष्ठा dma_async_tx_descriptor *rxd, *txd;

	rxd = ep93xx_spi_dma_prepare(master, DMA_FROM_DEVICE);
	अगर (IS_ERR(rxd)) अणु
		dev_err(&master->dev, "DMA RX failed: %ld\n", PTR_ERR(rxd));
		वापस PTR_ERR(rxd);
	पूर्ण

	txd = ep93xx_spi_dma_prepare(master, DMA_TO_DEVICE);
	अगर (IS_ERR(txd)) अणु
		ep93xx_spi_dma_finish(master, DMA_FROM_DEVICE);
		dev_err(&master->dev, "DMA TX failed: %ld\n", PTR_ERR(txd));
		वापस PTR_ERR(txd);
	पूर्ण

	/* We are पढ़ोy when RX is करोne */
	rxd->callback = ep93xx_spi_dma_callback;
	rxd->callback_param = master;

	/* Now submit both descriptors and start DMA */
	dmaengine_submit(rxd);
	dmaengine_submit(txd);

	dma_async_issue_pending(espi->dma_rx);
	dma_async_issue_pending(espi->dma_tx);

	/* संकेत that we need to रुको क्रम completion */
	वापस 1;
पूर्ण

अटल irqवापस_t ep93xx_spi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_master *master = dev_id;
	काष्ठा ep93xx_spi *espi = spi_master_get_devdata(master);
	u32 val;

	/*
	 * If we got ROR (receive overrun) पूर्णांकerrupt we know that something is
	 * wrong. Just पात the message.
	 */
	अगर (पढ़ोl(espi->mmio + SSPIIR) & SSPIIR_RORIS) अणु
		/* clear the overrun पूर्णांकerrupt */
		ग_लिखोl(0, espi->mmio + SSPICR);
		dev_warn(&master->dev,
			 "receive overrun, aborting the message\n");
		master->cur_msg->status = -EIO;
	पूर्ण अन्यथा अणु
		/*
		 * Interrupt is either RX (RIS) or TX (TIS). For both हालs we
		 * simply execute next data transfer.
		 */
		अगर (ep93xx_spi_पढ़ो_ग_लिखो(master)) अणु
			/*
			 * In normal हाल, there still is some processing left
			 * क्रम current transfer. Let's रुको क्रम the next
			 * पूर्णांकerrupt then.
			 */
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण

	/*
	 * Current transfer is finished, either with error or with success. In
	 * any हाल we disable पूर्णांकerrupts and notअगरy the worker to handle
	 * any post-processing of the message.
	 */
	val = पढ़ोl(espi->mmio + SSPCR1);
	val &= ~(SSPCR1_RORIE | SSPCR1_TIE | SSPCR1_RIE);
	ग_लिखोl(val, espi->mmio + SSPCR1);

	spi_finalize_current_transfer(master);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ep93xx_spi_transfer_one(काष्ठा spi_master *master,
				   काष्ठा spi_device *spi,
				   काष्ठा spi_transfer *xfer)
अणु
	काष्ठा ep93xx_spi *espi = spi_master_get_devdata(master);
	u32 val;
	पूर्णांक ret;

	ret = ep93xx_spi_chip_setup(master, spi, xfer);
	अगर (ret) अणु
		dev_err(&master->dev, "failed to setup chip for transfer\n");
		वापस ret;
	पूर्ण

	master->cur_msg->state = xfer;
	espi->rx = 0;
	espi->tx = 0;

	/*
	 * There is no poपूर्णांक of setting up DMA क्रम the transfers which will
	 * fit पूर्णांकo the FIFO and can be transferred with a single पूर्णांकerrupt.
	 * So in these हालs we will be using PIO and करोn't bother क्रम DMA.
	 */
	अगर (espi->dma_rx && xfer->len > SPI_FIFO_SIZE)
		वापस ep93xx_spi_dma_transfer(master);

	/* Using PIO so prime the TX FIFO and enable पूर्णांकerrupts */
	ep93xx_spi_पढ़ो_ग_लिखो(master);

	val = पढ़ोl(espi->mmio + SSPCR1);
	val |= (SSPCR1_RORIE | SSPCR1_TIE | SSPCR1_RIE);
	ग_लिखोl(val, espi->mmio + SSPCR1);

	/* संकेत that we need to रुको क्रम completion */
	वापस 1;
पूर्ण

अटल पूर्णांक ep93xx_spi_prepare_message(काष्ठा spi_master *master,
				      काष्ठा spi_message *msg)
अणु
	काष्ठा ep93xx_spi *espi = spi_master_get_devdata(master);
	अचिन्हित दीर्घ समयout;

	/*
	 * Just to be sure: flush any data from RX FIFO.
	 */
	समयout = jअगरfies + msecs_to_jअगरfies(SPI_TIMEOUT);
	जबतक (पढ़ोl(espi->mmio + SSPSR) & SSPSR_RNE) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_warn(&master->dev,
				 "timeout while flushing RX FIFO\n");
			वापस -ETIMEDOUT;
		पूर्ण
		पढ़ोl(espi->mmio + SSPDR);
	पूर्ण

	/*
	 * We explicitly handle FIFO level. This way we करोn't have to check TX
	 * FIFO status using %SSPSR_TNF bit which may cause RX FIFO overruns.
	 */
	espi->fअगरo_level = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_spi_prepare_hardware(काष्ठा spi_master *master)
अणु
	काष्ठा ep93xx_spi *espi = spi_master_get_devdata(master);
	u32 val;
	पूर्णांक ret;

	ret = clk_enable(espi->clk);
	अगर (ret)
		वापस ret;

	val = पढ़ोl(espi->mmio + SSPCR1);
	val |= SSPCR1_SSE;
	ग_लिखोl(val, espi->mmio + SSPCR1);

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_spi_unprepare_hardware(काष्ठा spi_master *master)
अणु
	काष्ठा ep93xx_spi *espi = spi_master_get_devdata(master);
	u32 val;

	val = पढ़ोl(espi->mmio + SSPCR1);
	val &= ~SSPCR1_SSE;
	ग_लिखोl(val, espi->mmio + SSPCR1);

	clk_disable(espi->clk);

	वापस 0;
पूर्ण

अटल bool ep93xx_spi_dma_filter(काष्ठा dma_chan *chan, व्योम *filter_param)
अणु
	अगर (ep93xx_dma_chan_is_m2p(chan))
		वापस false;

	chan->निजी = filter_param;
	वापस true;
पूर्ण

अटल पूर्णांक ep93xx_spi_setup_dma(काष्ठा ep93xx_spi *espi)
अणु
	dma_cap_mask_t mask;
	पूर्णांक ret;

	espi->zeropage = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!espi->zeropage)
		वापस -ENOMEM;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	espi->dma_rx_data.port = EP93XX_DMA_SSP;
	espi->dma_rx_data.direction = DMA_DEV_TO_MEM;
	espi->dma_rx_data.name = "ep93xx-spi-rx";

	espi->dma_rx = dma_request_channel(mask, ep93xx_spi_dma_filter,
					   &espi->dma_rx_data);
	अगर (!espi->dma_rx) अणु
		ret = -ENODEV;
		जाओ fail_मुक्त_page;
	पूर्ण

	espi->dma_tx_data.port = EP93XX_DMA_SSP;
	espi->dma_tx_data.direction = DMA_MEM_TO_DEV;
	espi->dma_tx_data.name = "ep93xx-spi-tx";

	espi->dma_tx = dma_request_channel(mask, ep93xx_spi_dma_filter,
					   &espi->dma_tx_data);
	अगर (!espi->dma_tx) अणु
		ret = -ENODEV;
		जाओ fail_release_rx;
	पूर्ण

	वापस 0;

fail_release_rx:
	dma_release_channel(espi->dma_rx);
	espi->dma_rx = शून्य;
fail_मुक्त_page:
	मुक्त_page((अचिन्हित दीर्घ)espi->zeropage);

	वापस ret;
पूर्ण

अटल व्योम ep93xx_spi_release_dma(काष्ठा ep93xx_spi *espi)
अणु
	अगर (espi->dma_rx) अणु
		dma_release_channel(espi->dma_rx);
		sg_मुक्त_table(&espi->rx_sgt);
	पूर्ण
	अगर (espi->dma_tx) अणु
		dma_release_channel(espi->dma_tx);
		sg_मुक्त_table(&espi->tx_sgt);
	पूर्ण

	अगर (espi->zeropage)
		मुक्त_page((अचिन्हित दीर्घ)espi->zeropage);
पूर्ण

अटल पूर्णांक ep93xx_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा ep93xx_spi_info *info;
	काष्ठा ep93xx_spi *espi;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक error;

	info = dev_get_platdata(&pdev->dev);
	अगर (!info) अणु
		dev_err(&pdev->dev, "missing platform data\n");
		वापस -EINVAL;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EBUSY;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "unable to get iomem resource\n");
		वापस -ENODEV;
	पूर्ण

	master = spi_alloc_master(&pdev->dev, माप(*espi));
	अगर (!master)
		वापस -ENOMEM;

	master->use_gpio_descriptors = true;
	master->prepare_transfer_hardware = ep93xx_spi_prepare_hardware;
	master->unprepare_transfer_hardware = ep93xx_spi_unprepare_hardware;
	master->prepare_message = ep93xx_spi_prepare_message;
	master->transfer_one = ep93xx_spi_transfer_one;
	master->bus_num = pdev->id;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 16);
	/*
	 * The SPI core will count the number of GPIO descriptors to figure
	 * out the number of chip selects available on the platक्रमm.
	 */
	master->num_chipselect = 0;

	platक्रमm_set_drvdata(pdev, master);

	espi = spi_master_get_devdata(master);

	espi->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(espi->clk)) अणु
		dev_err(&pdev->dev, "unable to get spi clock\n");
		error = PTR_ERR(espi->clk);
		जाओ fail_release_master;
	पूर्ण

	/*
	 * Calculate maximum and minimum supported घड़ी rates
	 * क्रम the controller.
	 */
	master->max_speed_hz = clk_get_rate(espi->clk) / 2;
	master->min_speed_hz = clk_get_rate(espi->clk) / (254 * 256);

	espi->sspdr_phys = res->start + SSPDR;

	espi->mmio = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(espi->mmio)) अणु
		error = PTR_ERR(espi->mmio);
		जाओ fail_release_master;
	पूर्ण

	error = devm_request_irq(&pdev->dev, irq, ep93xx_spi_पूर्णांकerrupt,
				0, "ep93xx-spi", master);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to request irq\n");
		जाओ fail_release_master;
	पूर्ण

	अगर (info->use_dma && ep93xx_spi_setup_dma(espi))
		dev_warn(&pdev->dev, "DMA setup failed. Falling back to PIO\n");

	/* make sure that the hardware is disabled */
	ग_लिखोl(0, espi->mmio + SSPCR1);

	error = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register SPI master\n");
		जाओ fail_मुक्त_dma;
	पूर्ण

	dev_info(&pdev->dev, "EP93xx SPI Controller at 0x%08lx irq %d\n",
		 (अचिन्हित दीर्घ)res->start, irq);

	वापस 0;

fail_मुक्त_dma:
	ep93xx_spi_release_dma(espi);
fail_release_master:
	spi_master_put(master);

	वापस error;
पूर्ण

अटल पूर्णांक ep93xx_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा ep93xx_spi *espi = spi_master_get_devdata(master);

	ep93xx_spi_release_dma(espi);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ep93xx_spi_driver = अणु
	.driver		= अणु
		.name	= "ep93xx-spi",
	पूर्ण,
	.probe		= ep93xx_spi_probe,
	.हटाओ		= ep93xx_spi_हटाओ,
पूर्ण;
module_platक्रमm_driver(ep93xx_spi_driver);

MODULE_DESCRIPTION("EP93xx SPI Controller driver");
MODULE_AUTHOR("Mika Westerberg <mika.westerberg@iki.fi>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ep93xx-spi");
