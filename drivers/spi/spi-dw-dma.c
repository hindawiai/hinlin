<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Special handling क्रम DW DMA core
 *
 * Copyright (c) 2009, 2014 Intel Corporation.
 */

#समावेश <linux/completion.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_data/dma-dw.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/types.h>

#समावेश "spi-dw.h"

#घोषणा RX_BUSY		0
#घोषणा RX_BURST_LEVEL	16
#घोषणा TX_BUSY		1
#घोषणा TX_BURST_LEVEL	16

अटल bool dw_spi_dma_chan_filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा dw_dma_slave *s = param;

	अगर (s->dma_dev != chan->device->dev)
		वापस false;

	chan->निजी = s;
	वापस true;
पूर्ण

अटल व्योम dw_spi_dma_maxburst_init(काष्ठा dw_spi *dws)
अणु
	काष्ठा dma_slave_caps caps;
	u32 max_burst, def_burst;
	पूर्णांक ret;

	def_burst = dws->fअगरo_len / 2;

	ret = dma_get_slave_caps(dws->rxchan, &caps);
	अगर (!ret && caps.max_burst)
		max_burst = caps.max_burst;
	अन्यथा
		max_burst = RX_BURST_LEVEL;

	dws->rxburst = min(max_burst, def_burst);
	dw_ग_लिखोl(dws, DW_SPI_DMARDLR, dws->rxburst - 1);

	ret = dma_get_slave_caps(dws->txchan, &caps);
	अगर (!ret && caps.max_burst)
		max_burst = caps.max_burst;
	अन्यथा
		max_burst = TX_BURST_LEVEL;

	/*
	 * Having a Rx DMA channel serviced with higher priority than a Tx DMA
	 * channel might not be enough to provide a well balanced DMA-based
	 * SPI transfer पूर्णांकerface. There might still be moments when the Tx DMA
	 * channel is occasionally handled faster than the Rx DMA channel.
	 * That in its turn will eventually cause the SPI Rx FIFO overflow अगर
	 * SPI bus speed is high enough to fill the SPI Rx FIFO in beक्रमe it's
	 * cleared by the Rx DMA channel. In order to fix the problem the Tx
	 * DMA activity is पूर्णांकentionally slowed करोwn by limiting the SPI Tx
	 * FIFO depth with a value twice bigger than the Tx burst length.
	 */
	dws->txburst = min(max_burst, def_burst);
	dw_ग_लिखोl(dws, DW_SPI_DMATDLR, dws->txburst);
पूर्ण

अटल व्योम dw_spi_dma_sg_burst_init(काष्ठा dw_spi *dws)
अणु
	काष्ठा dma_slave_caps tx = अणु0पूर्ण, rx = अणु0पूर्ण;

	dma_get_slave_caps(dws->txchan, &tx);
	dma_get_slave_caps(dws->rxchan, &rx);

	अगर (tx.max_sg_burst > 0 && rx.max_sg_burst > 0)
		dws->dma_sg_burst = min(tx.max_sg_burst, rx.max_sg_burst);
	अन्यथा अगर (tx.max_sg_burst > 0)
		dws->dma_sg_burst = tx.max_sg_burst;
	अन्यथा अगर (rx.max_sg_burst > 0)
		dws->dma_sg_burst = rx.max_sg_burst;
	अन्यथा
		dws->dma_sg_burst = 0;
पूर्ण

अटल पूर्णांक dw_spi_dma_init_mfld(काष्ठा device *dev, काष्ठा dw_spi *dws)
अणु
	काष्ठा dw_dma_slave dma_tx = अणु .dst_id = 1 पूर्ण, *tx = &dma_tx;
	काष्ठा dw_dma_slave dma_rx = अणु .src_id = 0 पूर्ण, *rx = &dma_rx;
	काष्ठा pci_dev *dma_dev;
	dma_cap_mask_t mask;

	/*
	 * Get pci device क्रम DMA controller, currently it could only
	 * be the DMA controller of Medfield
	 */
	dma_dev = pci_get_device(PCI_VENDOR_ID_INTEL, 0x0827, शून्य);
	अगर (!dma_dev)
		वापस -ENODEV;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	/* 1. Init rx channel */
	rx->dma_dev = &dma_dev->dev;
	dws->rxchan = dma_request_channel(mask, dw_spi_dma_chan_filter, rx);
	अगर (!dws->rxchan)
		जाओ err_निकास;

	/* 2. Init tx channel */
	tx->dma_dev = &dma_dev->dev;
	dws->txchan = dma_request_channel(mask, dw_spi_dma_chan_filter, tx);
	अगर (!dws->txchan)
		जाओ मुक्त_rxchan;

	dws->master->dma_rx = dws->rxchan;
	dws->master->dma_tx = dws->txchan;

	init_completion(&dws->dma_completion);

	dw_spi_dma_maxburst_init(dws);

	dw_spi_dma_sg_burst_init(dws);

	वापस 0;

मुक्त_rxchan:
	dma_release_channel(dws->rxchan);
	dws->rxchan = शून्य;
err_निकास:
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक dw_spi_dma_init_generic(काष्ठा device *dev, काष्ठा dw_spi *dws)
अणु
	dws->rxchan = dma_request_slave_channel(dev, "rx");
	अगर (!dws->rxchan)
		वापस -ENODEV;

	dws->txchan = dma_request_slave_channel(dev, "tx");
	अगर (!dws->txchan) अणु
		dma_release_channel(dws->rxchan);
		dws->rxchan = शून्य;
		वापस -ENODEV;
	पूर्ण

	dws->master->dma_rx = dws->rxchan;
	dws->master->dma_tx = dws->txchan;

	init_completion(&dws->dma_completion);

	dw_spi_dma_maxburst_init(dws);

	dw_spi_dma_sg_burst_init(dws);

	वापस 0;
पूर्ण

अटल व्योम dw_spi_dma_निकास(काष्ठा dw_spi *dws)
अणु
	अगर (dws->txchan) अणु
		dmaengine_terminate_sync(dws->txchan);
		dma_release_channel(dws->txchan);
	पूर्ण

	अगर (dws->rxchan) अणु
		dmaengine_terminate_sync(dws->rxchan);
		dma_release_channel(dws->rxchan);
	पूर्ण
पूर्ण

अटल irqवापस_t dw_spi_dma_transfer_handler(काष्ठा dw_spi *dws)
अणु
	dw_spi_check_status(dws, false);

	complete(&dws->dma_completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल bool dw_spi_can_dma(काष्ठा spi_controller *master,
			   काष्ठा spi_device *spi, काष्ठा spi_transfer *xfer)
अणु
	काष्ठा dw_spi *dws = spi_controller_get_devdata(master);

	वापस xfer->len > dws->fअगरo_len;
पूर्ण

अटल क्रमागत dma_slave_buswidth dw_spi_dma_convert_width(u8 n_bytes)
अणु
	अगर (n_bytes == 1)
		वापस DMA_SLAVE_BUSWIDTH_1_BYTE;
	अन्यथा अगर (n_bytes == 2)
		वापस DMA_SLAVE_BUSWIDTH_2_BYTES;

	वापस DMA_SLAVE_BUSWIDTH_UNDEFINED;
पूर्ण

अटल पूर्णांक dw_spi_dma_रुको(काष्ठा dw_spi *dws, अचिन्हित पूर्णांक len, u32 speed)
अणु
	अचिन्हित दीर्घ दीर्घ ms;

	ms = len * MSEC_PER_SEC * BITS_PER_BYTE;
	करो_भाग(ms, speed);
	ms += ms + 200;

	अगर (ms > अच_पूर्णांक_उच्च)
		ms = अच_पूर्णांक_उच्च;

	ms = रुको_क्रम_completion_समयout(&dws->dma_completion,
					 msecs_to_jअगरfies(ms));

	अगर (ms == 0) अणु
		dev_err(&dws->master->cur_msg->spi->dev,
			"DMA transaction timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत bool dw_spi_dma_tx_busy(काष्ठा dw_spi *dws)
अणु
	वापस !(dw_पढ़ोl(dws, DW_SPI_SR) & SR_TF_EMPT);
पूर्ण

अटल पूर्णांक dw_spi_dma_रुको_tx_करोne(काष्ठा dw_spi *dws,
				   काष्ठा spi_transfer *xfer)
अणु
	पूर्णांक retry = SPI_WAIT_RETRIES;
	काष्ठा spi_delay delay;
	u32 nents;

	nents = dw_पढ़ोl(dws, DW_SPI_TXFLR);
	delay.unit = SPI_DELAY_UNIT_SCK;
	delay.value = nents * dws->n_bytes * BITS_PER_BYTE;

	जबतक (dw_spi_dma_tx_busy(dws) && retry--)
		spi_delay_exec(&delay, xfer);

	अगर (retry < 0) अणु
		dev_err(&dws->master->dev, "Tx hanged up\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * dws->dma_chan_busy is set beक्रमe the dma transfer starts, callback क्रम tx
 * channel will clear a corresponding bit.
 */
अटल व्योम dw_spi_dma_tx_करोne(व्योम *arg)
अणु
	काष्ठा dw_spi *dws = arg;

	clear_bit(TX_BUSY, &dws->dma_chan_busy);
	अगर (test_bit(RX_BUSY, &dws->dma_chan_busy))
		वापस;

	complete(&dws->dma_completion);
पूर्ण

अटल पूर्णांक dw_spi_dma_config_tx(काष्ठा dw_spi *dws)
अणु
	काष्ठा dma_slave_config txconf;

	स_रखो(&txconf, 0, माप(txconf));
	txconf.direction = DMA_MEM_TO_DEV;
	txconf.dst_addr = dws->dma_addr;
	txconf.dst_maxburst = dws->txburst;
	txconf.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	txconf.dst_addr_width = dw_spi_dma_convert_width(dws->n_bytes);
	txconf.device_fc = false;

	वापस dmaengine_slave_config(dws->txchan, &txconf);
पूर्ण

अटल पूर्णांक dw_spi_dma_submit_tx(काष्ठा dw_spi *dws, काष्ठा scatterlist *sgl,
				अचिन्हित पूर्णांक nents)
अणु
	काष्ठा dma_async_tx_descriptor *txdesc;
	dma_cookie_t cookie;
	पूर्णांक ret;

	txdesc = dmaengine_prep_slave_sg(dws->txchan, sgl, nents,
					 DMA_MEM_TO_DEV,
					 DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!txdesc)
		वापस -ENOMEM;

	txdesc->callback = dw_spi_dma_tx_करोne;
	txdesc->callback_param = dws;

	cookie = dmaengine_submit(txdesc);
	ret = dma_submit_error(cookie);
	अगर (ret) अणु
		dmaengine_terminate_sync(dws->txchan);
		वापस ret;
	पूर्ण

	set_bit(TX_BUSY, &dws->dma_chan_busy);

	वापस 0;
पूर्ण

अटल अंतरभूत bool dw_spi_dma_rx_busy(काष्ठा dw_spi *dws)
अणु
	वापस !!(dw_पढ़ोl(dws, DW_SPI_SR) & SR_RF_NOT_EMPT);
पूर्ण

अटल पूर्णांक dw_spi_dma_रुको_rx_करोne(काष्ठा dw_spi *dws)
अणु
	पूर्णांक retry = SPI_WAIT_RETRIES;
	काष्ठा spi_delay delay;
	अचिन्हित दीर्घ ns, us;
	u32 nents;

	/*
	 * It's unlikely that DMA engine is still करोing the data fetching, but
	 * अगर it's let's give it some reasonable समय. The समयout calculation
	 * is based on the synchronous APB/SSI reference घड़ी rate, on a
	 * number of data entries left in the Rx FIFO, बार a number of घड़ी
	 * periods normally needed क्रम a single APB पढ़ो/ग_लिखो transaction
	 * without PREADY संकेत utilized (which is true क्रम the DW APB SSI
	 * controller).
	 */
	nents = dw_पढ़ोl(dws, DW_SPI_RXFLR);
	ns = 4U * NSEC_PER_SEC / dws->max_freq * nents;
	अगर (ns <= NSEC_PER_USEC) अणु
		delay.unit = SPI_DELAY_UNIT_NSECS;
		delay.value = ns;
	पूर्ण अन्यथा अणु
		us = DIV_ROUND_UP(ns, NSEC_PER_USEC);
		delay.unit = SPI_DELAY_UNIT_USECS;
		delay.value = clamp_val(us, 0, अच_लघु_उच्च);
	पूर्ण

	जबतक (dw_spi_dma_rx_busy(dws) && retry--)
		spi_delay_exec(&delay, शून्य);

	अगर (retry < 0) अणु
		dev_err(&dws->master->dev, "Rx hanged up\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * dws->dma_chan_busy is set beक्रमe the dma transfer starts, callback क्रम rx
 * channel will clear a corresponding bit.
 */
अटल व्योम dw_spi_dma_rx_करोne(व्योम *arg)
अणु
	काष्ठा dw_spi *dws = arg;

	clear_bit(RX_BUSY, &dws->dma_chan_busy);
	अगर (test_bit(TX_BUSY, &dws->dma_chan_busy))
		वापस;

	complete(&dws->dma_completion);
पूर्ण

अटल पूर्णांक dw_spi_dma_config_rx(काष्ठा dw_spi *dws)
अणु
	काष्ठा dma_slave_config rxconf;

	स_रखो(&rxconf, 0, माप(rxconf));
	rxconf.direction = DMA_DEV_TO_MEM;
	rxconf.src_addr = dws->dma_addr;
	rxconf.src_maxburst = dws->rxburst;
	rxconf.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	rxconf.src_addr_width = dw_spi_dma_convert_width(dws->n_bytes);
	rxconf.device_fc = false;

	वापस dmaengine_slave_config(dws->rxchan, &rxconf);
पूर्ण

अटल पूर्णांक dw_spi_dma_submit_rx(काष्ठा dw_spi *dws, काष्ठा scatterlist *sgl,
				अचिन्हित पूर्णांक nents)
अणु
	काष्ठा dma_async_tx_descriptor *rxdesc;
	dma_cookie_t cookie;
	पूर्णांक ret;

	rxdesc = dmaengine_prep_slave_sg(dws->rxchan, sgl, nents,
					 DMA_DEV_TO_MEM,
					 DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!rxdesc)
		वापस -ENOMEM;

	rxdesc->callback = dw_spi_dma_rx_करोne;
	rxdesc->callback_param = dws;

	cookie = dmaengine_submit(rxdesc);
	ret = dma_submit_error(cookie);
	अगर (ret) अणु
		dmaengine_terminate_sync(dws->rxchan);
		वापस ret;
	पूर्ण

	set_bit(RX_BUSY, &dws->dma_chan_busy);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_spi_dma_setup(काष्ठा dw_spi *dws, काष्ठा spi_transfer *xfer)
अणु
	u16 imr, dma_ctrl;
	पूर्णांक ret;

	अगर (!xfer->tx_buf)
		वापस -EINVAL;

	/* Setup DMA channels */
	ret = dw_spi_dma_config_tx(dws);
	अगर (ret)
		वापस ret;

	अगर (xfer->rx_buf) अणु
		ret = dw_spi_dma_config_rx(dws);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Set the DMA handshaking पूर्णांकerface */
	dma_ctrl = SPI_DMA_TDMAE;
	अगर (xfer->rx_buf)
		dma_ctrl |= SPI_DMA_RDMAE;
	dw_ग_लिखोl(dws, DW_SPI_DMACR, dma_ctrl);

	/* Set the पूर्णांकerrupt mask */
	imr = SPI_INT_TXOI;
	अगर (xfer->rx_buf)
		imr |= SPI_INT_RXUI | SPI_INT_RXOI;
	spi_umask_पूर्णांकr(dws, imr);

	reinit_completion(&dws->dma_completion);

	dws->transfer_handler = dw_spi_dma_transfer_handler;

	वापस 0;
पूर्ण

अटल पूर्णांक dw_spi_dma_transfer_all(काष्ठा dw_spi *dws,
				   काष्ठा spi_transfer *xfer)
अणु
	पूर्णांक ret;

	/* Submit the DMA Tx transfer */
	ret = dw_spi_dma_submit_tx(dws, xfer->tx_sg.sgl, xfer->tx_sg.nents);
	अगर (ret)
		जाओ err_clear_dmac;

	/* Submit the DMA Rx transfer अगर required */
	अगर (xfer->rx_buf) अणु
		ret = dw_spi_dma_submit_rx(dws, xfer->rx_sg.sgl,
					   xfer->rx_sg.nents);
		अगर (ret)
			जाओ err_clear_dmac;

		/* rx must be started beक्रमe tx due to spi instinct */
		dma_async_issue_pending(dws->rxchan);
	पूर्ण

	dma_async_issue_pending(dws->txchan);

	ret = dw_spi_dma_रुको(dws, xfer->len, xfer->effective_speed_hz);

err_clear_dmac:
	dw_ग_लिखोl(dws, DW_SPI_DMACR, 0);

	वापस ret;
पूर्ण

/*
 * In हाल अगर at least one of the requested DMA channels करोesn't support the
 * hardware accelerated SG list entries traverse, the DMA driver will most
 * likely work that around by perक्रमming the IRQ-based SG list entries
 * resubmission. That might and will cause a problem अगर the DMA Tx channel is
 * reअक्षरged and re-executed beक्रमe the Rx DMA channel. Due to
 * non-deterministic IRQ-handler execution latency the DMA Tx channel will
 * start pushing data to the SPI bus beक्रमe the Rx DMA channel is even
 * reinitialized with the next inbound SG list entry. By करोing so the DMA Tx
 * channel will implicitly start filling the DW APB SSI Rx FIFO up, which जबतक
 * the DMA Rx channel being reअक्षरged and re-executed will eventually be
 * overflown.
 *
 * In order to solve the problem we have to feed the DMA engine with SG list
 * entries one-by-one. It shall keep the DW APB SSI Tx and Rx FIFOs
 * synchronized and prevent the Rx FIFO overflow. Since in general the tx_sg
 * and rx_sg lists may have dअगरferent number of entries of dअगरferent lengths
 * (though total length should match) let's भवly split the SG-lists to the
 * set of DMA transfers, which length is a minimum of the ordered SG-entries
 * lengths. An ASCII-sketch of the implemented algo is following:
 *                  xfer->len
 *                |___________|
 * tx_sg list:    |___|____|__|
 * rx_sg list:    |_|____|____|
 * DMA transfers: |_|_|__|_|__|
 *
 * Note in order to have this workaround solving the denoted problem the DMA
 * engine driver should properly initialize the max_sg_burst capability and set
 * the DMA device max segment size parameter with maximum data block size the
 * DMA engine supports.
 */

अटल पूर्णांक dw_spi_dma_transfer_one(काष्ठा dw_spi *dws,
				   काष्ठा spi_transfer *xfer)
अणु
	काष्ठा scatterlist *tx_sg = शून्य, *rx_sg = शून्य, tx_पंचांगp, rx_पंचांगp;
	अचिन्हित पूर्णांक tx_len = 0, rx_len = 0;
	अचिन्हित पूर्णांक base, len;
	पूर्णांक ret;

	sg_init_table(&tx_पंचांगp, 1);
	sg_init_table(&rx_पंचांगp, 1);

	क्रम (base = 0, len = 0; base < xfer->len; base += len) अणु
		/* Fetch next Tx DMA data chunk */
		अगर (!tx_len) अणु
			tx_sg = !tx_sg ? &xfer->tx_sg.sgl[0] : sg_next(tx_sg);
			sg_dma_address(&tx_पंचांगp) = sg_dma_address(tx_sg);
			tx_len = sg_dma_len(tx_sg);
		पूर्ण

		/* Fetch next Rx DMA data chunk */
		अगर (!rx_len) अणु
			rx_sg = !rx_sg ? &xfer->rx_sg.sgl[0] : sg_next(rx_sg);
			sg_dma_address(&rx_पंचांगp) = sg_dma_address(rx_sg);
			rx_len = sg_dma_len(rx_sg);
		पूर्ण

		len = min(tx_len, rx_len);

		sg_dma_len(&tx_पंचांगp) = len;
		sg_dma_len(&rx_पंचांगp) = len;

		/* Submit DMA Tx transfer */
		ret = dw_spi_dma_submit_tx(dws, &tx_पंचांगp, 1);
		अगर (ret)
			अवरोध;

		/* Submit DMA Rx transfer */
		ret = dw_spi_dma_submit_rx(dws, &rx_पंचांगp, 1);
		अगर (ret)
			अवरोध;

		/* Rx must be started beक्रमe Tx due to SPI instinct */
		dma_async_issue_pending(dws->rxchan);

		dma_async_issue_pending(dws->txchan);

		/*
		 * Here we only need to रुको क्रम the DMA transfer to be
		 * finished since SPI controller is kept enabled during the
		 * procedure this loop implements and there is no risk to lose
		 * data left in the Tx/Rx FIFOs.
		 */
		ret = dw_spi_dma_रुको(dws, len, xfer->effective_speed_hz);
		अगर (ret)
			अवरोध;

		reinit_completion(&dws->dma_completion);

		sg_dma_address(&tx_पंचांगp) += len;
		sg_dma_address(&rx_पंचांगp) += len;
		tx_len -= len;
		rx_len -= len;
	पूर्ण

	dw_ग_लिखोl(dws, DW_SPI_DMACR, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक dw_spi_dma_transfer(काष्ठा dw_spi *dws, काष्ठा spi_transfer *xfer)
अणु
	अचिन्हित पूर्णांक nents;
	पूर्णांक ret;

	nents = max(xfer->tx_sg.nents, xfer->rx_sg.nents);

	/*
	 * Execute normal DMA-based transfer (which submits the Rx and Tx SG
	 * lists directly to the DMA engine at once) अगर either full hardware
	 * accelerated SG list traverse is supported by both channels, or the
	 * Tx-only SPI transfer is requested, or the DMA engine is capable to
	 * handle both SG lists on hardware accelerated basis.
	 */
	अगर (!dws->dma_sg_burst || !xfer->rx_buf || nents <= dws->dma_sg_burst)
		ret = dw_spi_dma_transfer_all(dws, xfer);
	अन्यथा
		ret = dw_spi_dma_transfer_one(dws, xfer);
	अगर (ret)
		वापस ret;

	अगर (dws->master->cur_msg->status == -EINPROGRESS) अणु
		ret = dw_spi_dma_रुको_tx_करोne(dws, xfer);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (xfer->rx_buf && dws->master->cur_msg->status == -EINPROGRESS)
		ret = dw_spi_dma_रुको_rx_करोne(dws);

	वापस ret;
पूर्ण

अटल व्योम dw_spi_dma_stop(काष्ठा dw_spi *dws)
अणु
	अगर (test_bit(TX_BUSY, &dws->dma_chan_busy)) अणु
		dmaengine_terminate_sync(dws->txchan);
		clear_bit(TX_BUSY, &dws->dma_chan_busy);
	पूर्ण
	अगर (test_bit(RX_BUSY, &dws->dma_chan_busy)) अणु
		dmaengine_terminate_sync(dws->rxchan);
		clear_bit(RX_BUSY, &dws->dma_chan_busy);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा dw_spi_dma_ops dw_spi_dma_mfld_ops = अणु
	.dma_init	= dw_spi_dma_init_mfld,
	.dma_निकास	= dw_spi_dma_निकास,
	.dma_setup	= dw_spi_dma_setup,
	.can_dma	= dw_spi_can_dma,
	.dma_transfer	= dw_spi_dma_transfer,
	.dma_stop	= dw_spi_dma_stop,
पूर्ण;

व्योम dw_spi_dma_setup_mfld(काष्ठा dw_spi *dws)
अणु
	dws->dma_ops = &dw_spi_dma_mfld_ops;
पूर्ण
EXPORT_SYMBOL_GPL(dw_spi_dma_setup_mfld);

अटल स्थिर काष्ठा dw_spi_dma_ops dw_spi_dma_generic_ops = अणु
	.dma_init	= dw_spi_dma_init_generic,
	.dma_निकास	= dw_spi_dma_निकास,
	.dma_setup	= dw_spi_dma_setup,
	.can_dma	= dw_spi_can_dma,
	.dma_transfer	= dw_spi_dma_transfer,
	.dma_stop	= dw_spi_dma_stop,
पूर्ण;

व्योम dw_spi_dma_setup_generic(काष्ठा dw_spi *dws)
अणु
	dws->dma_ops = &dw_spi_dma_generic_ops;
पूर्ण
EXPORT_SYMBOL_GPL(dw_spi_dma_setup_generic);
