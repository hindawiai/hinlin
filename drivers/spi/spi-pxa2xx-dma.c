<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PXA2xx SPI DMA engine support.
 *
 * Copyright (C) 2013, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/pxa2xx_ssp.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/sizes.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/pxa2xx_spi.h>

#समावेश "spi-pxa2xx.h"

अटल व्योम pxa2xx_spi_dma_transfer_complete(काष्ठा driver_data *drv_data,
					     bool error)
अणु
	काष्ठा spi_message *msg = drv_data->controller->cur_msg;

	/*
	 * It is possible that one CPU is handling ROR पूर्णांकerrupt and other
	 * just माला_लो DMA completion. Calling pump_transfers() twice क्रम the
	 * same transfer leads to problems thus we prevent concurrent calls
	 * by using ->dma_running.
	 */
	अगर (atomic_dec_and_test(&drv_data->dma_running)) अणु
		/*
		 * If the other CPU is still handling the ROR पूर्णांकerrupt we
		 * might not know about the error yet. So we re-check the
		 * ROR bit here beक्रमe we clear the status रेजिस्टर.
		 */
		अगर (!error) अणु
			u32 status = pxa2xx_spi_पढ़ो(drv_data, SSSR)
				     & drv_data->mask_sr;
			error = status & SSSR_ROR;
		पूर्ण

		/* Clear status & disable पूर्णांकerrupts */
		pxa2xx_spi_ग_लिखो(drv_data, SSCR1,
				 pxa2xx_spi_पढ़ो(drv_data, SSCR1)
				 & ~drv_data->dma_cr1);
		ग_लिखो_SSSR_CS(drv_data, drv_data->clear_sr);
		अगर (!pxa25x_ssp_comp(drv_data))
			pxa2xx_spi_ग_लिखो(drv_data, SSTO, 0);

		अगर (error) अणु
			/* In हाल we got an error we disable the SSP now */
			pxa2xx_spi_ग_लिखो(drv_data, SSCR0,
					 pxa2xx_spi_पढ़ो(drv_data, SSCR0)
					 & ~SSCR0_SSE);
			msg->status = -EIO;
		पूर्ण

		spi_finalize_current_transfer(drv_data->controller);
	पूर्ण
पूर्ण

अटल व्योम pxa2xx_spi_dma_callback(व्योम *data)
अणु
	pxa2xx_spi_dma_transfer_complete(data, false);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
pxa2xx_spi_dma_prepare_one(काष्ठा driver_data *drv_data,
			   क्रमागत dma_transfer_direction dir,
			   काष्ठा spi_transfer *xfer)
अणु
	काष्ठा chip_data *chip =
		spi_get_ctldata(drv_data->controller->cur_msg->spi);
	क्रमागत dma_slave_buswidth width;
	काष्ठा dma_slave_config cfg;
	काष्ठा dma_chan *chan;
	काष्ठा sg_table *sgt;
	पूर्णांक ret;

	चयन (drv_data->n_bytes) अणु
	हाल 1:
		width = DMA_SLAVE_BUSWIDTH_1_BYTE;
		अवरोध;
	हाल 2:
		width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		अवरोध;
	शेष:
		width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		अवरोध;
	पूर्ण

	स_रखो(&cfg, 0, माप(cfg));
	cfg.direction = dir;

	अगर (dir == DMA_MEM_TO_DEV) अणु
		cfg.dst_addr = drv_data->ssdr_physical;
		cfg.dst_addr_width = width;
		cfg.dst_maxburst = chip->dma_burst_size;

		sgt = &xfer->tx_sg;
		chan = drv_data->controller->dma_tx;
	पूर्ण अन्यथा अणु
		cfg.src_addr = drv_data->ssdr_physical;
		cfg.src_addr_width = width;
		cfg.src_maxburst = chip->dma_burst_size;

		sgt = &xfer->rx_sg;
		chan = drv_data->controller->dma_rx;
	पूर्ण

	ret = dmaengine_slave_config(chan, &cfg);
	अगर (ret) अणु
		dev_warn(&drv_data->pdev->dev, "DMA slave config failed\n");
		वापस शून्य;
	पूर्ण

	वापस dmaengine_prep_slave_sg(chan, sgt->sgl, sgt->nents, dir,
				       DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
पूर्ण

irqवापस_t pxa2xx_spi_dma_transfer(काष्ठा driver_data *drv_data)
अणु
	u32 status;

	status = pxa2xx_spi_पढ़ो(drv_data, SSSR) & drv_data->mask_sr;
	अगर (status & SSSR_ROR) अणु
		dev_err(&drv_data->pdev->dev, "FIFO overrun\n");

		dmaengine_terminate_async(drv_data->controller->dma_rx);
		dmaengine_terminate_async(drv_data->controller->dma_tx);

		pxa2xx_spi_dma_transfer_complete(drv_data, true);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

पूर्णांक pxa2xx_spi_dma_prepare(काष्ठा driver_data *drv_data,
			   काष्ठा spi_transfer *xfer)
अणु
	काष्ठा dma_async_tx_descriptor *tx_desc, *rx_desc;
	पूर्णांक err;

	tx_desc = pxa2xx_spi_dma_prepare_one(drv_data, DMA_MEM_TO_DEV, xfer);
	अगर (!tx_desc) अणु
		dev_err(&drv_data->pdev->dev,
			"failed to get DMA TX descriptor\n");
		err = -EBUSY;
		जाओ err_tx;
	पूर्ण

	rx_desc = pxa2xx_spi_dma_prepare_one(drv_data, DMA_DEV_TO_MEM, xfer);
	अगर (!rx_desc) अणु
		dev_err(&drv_data->pdev->dev,
			"failed to get DMA RX descriptor\n");
		err = -EBUSY;
		जाओ err_rx;
	पूर्ण

	/* We are पढ़ोy when RX completes */
	rx_desc->callback = pxa2xx_spi_dma_callback;
	rx_desc->callback_param = drv_data;

	dmaengine_submit(rx_desc);
	dmaengine_submit(tx_desc);
	वापस 0;

err_rx:
	dmaengine_terminate_async(drv_data->controller->dma_tx);
err_tx:
	वापस err;
पूर्ण

व्योम pxa2xx_spi_dma_start(काष्ठा driver_data *drv_data)
अणु
	dma_async_issue_pending(drv_data->controller->dma_rx);
	dma_async_issue_pending(drv_data->controller->dma_tx);

	atomic_set(&drv_data->dma_running, 1);
पूर्ण

व्योम pxa2xx_spi_dma_stop(काष्ठा driver_data *drv_data)
अणु
	atomic_set(&drv_data->dma_running, 0);
	dmaengine_terminate_sync(drv_data->controller->dma_rx);
	dmaengine_terminate_sync(drv_data->controller->dma_tx);
पूर्ण

पूर्णांक pxa2xx_spi_dma_setup(काष्ठा driver_data *drv_data)
अणु
	काष्ठा pxa2xx_spi_controller *pdata = drv_data->controller_info;
	काष्ठा device *dev = &drv_data->pdev->dev;
	काष्ठा spi_controller *controller = drv_data->controller;
	dma_cap_mask_t mask;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	controller->dma_tx = dma_request_slave_channel_compat(mask,
				pdata->dma_filter, pdata->tx_param, dev, "tx");
	अगर (!controller->dma_tx)
		वापस -ENODEV;

	controller->dma_rx = dma_request_slave_channel_compat(mask,
				pdata->dma_filter, pdata->rx_param, dev, "rx");
	अगर (!controller->dma_rx) अणु
		dma_release_channel(controller->dma_tx);
		controller->dma_tx = शून्य;
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

व्योम pxa2xx_spi_dma_release(काष्ठा driver_data *drv_data)
अणु
	काष्ठा spi_controller *controller = drv_data->controller;

	अगर (controller->dma_rx) अणु
		dmaengine_terminate_sync(controller->dma_rx);
		dma_release_channel(controller->dma_rx);
		controller->dma_rx = शून्य;
	पूर्ण
	अगर (controller->dma_tx) अणु
		dmaengine_terminate_sync(controller->dma_tx);
		dma_release_channel(controller->dma_tx);
		controller->dma_tx = शून्य;
	पूर्ण
पूर्ण

पूर्णांक pxa2xx_spi_set_dma_burst_and_threshold(काष्ठा chip_data *chip,
					   काष्ठा spi_device *spi,
					   u8 bits_per_word, u32 *burst_code,
					   u32 *threshold)
अणु
	काष्ठा pxa2xx_spi_chip *chip_info = spi->controller_data;
	काष्ठा driver_data *drv_data = spi_controller_get_devdata(spi->controller);
	u32 dma_burst_size = drv_data->controller_info->dma_burst_size;

	/*
	 * If the DMA burst size is given in chip_info we use that,
	 * otherwise we use the शेष. Also we use the शेष FIFO
	 * thresholds क्रम now.
	 */
	*burst_code = chip_info ? chip_info->dma_burst_size : dma_burst_size;
	*threshold = SSCR1_RxTresh(RX_THRESH_DFLT)
		   | SSCR1_TxTresh(TX_THRESH_DFLT);

	वापस 0;
पूर्ण
