<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * i2c-sपंचांग32.c
 *
 * Copyright (C) M'boumba Cedric Madianga 2017
 * Author: M'boumba Cedric Madianga <cedric.madianga@gmail.com>
 */

#समावेश "i2c-stm32.h"

/* Functions क्रम DMA support */
काष्ठा sपंचांग32_i2c_dma *sपंचांग32_i2c_dma_request(काष्ठा device *dev,
					    dma_addr_t phy_addr,
					    u32 txdr_offset,
					    u32 rxdr_offset)
अणु
	काष्ठा sपंचांग32_i2c_dma *dma;
	काष्ठा dma_slave_config dma_sconfig;
	पूर्णांक ret;

	dma = devm_kzalloc(dev, माप(*dma), GFP_KERNEL);
	अगर (!dma)
		वापस ERR_PTR(-ENOMEM);

	/* Request and configure I2C TX dma channel */
	dma->chan_tx = dma_request_chan(dev, "tx");
	अगर (IS_ERR(dma->chan_tx)) अणु
		ret = PTR_ERR(dma->chan_tx);
		अगर (ret != -ENODEV)
			ret = dev_err_probe(dev, ret,
					    "can't request DMA tx channel\n");
		जाओ fail_al;
	पूर्ण

	स_रखो(&dma_sconfig, 0, माप(dma_sconfig));
	dma_sconfig.dst_addr = phy_addr + txdr_offset;
	dma_sconfig.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	dma_sconfig.dst_maxburst = 1;
	dma_sconfig.direction = DMA_MEM_TO_DEV;
	ret = dmaengine_slave_config(dma->chan_tx, &dma_sconfig);
	अगर (ret < 0) अणु
		dev_err(dev, "can't configure tx channel\n");
		जाओ fail_tx;
	पूर्ण

	/* Request and configure I2C RX dma channel */
	dma->chan_rx = dma_request_chan(dev, "rx");
	अगर (IS_ERR(dma->chan_rx)) अणु
		ret = PTR_ERR(dma->chan_rx);
		अगर (ret != -ENODEV)
			ret = dev_err_probe(dev, ret,
					    "can't request DMA rx channel\n");

		जाओ fail_tx;
	पूर्ण

	स_रखो(&dma_sconfig, 0, माप(dma_sconfig));
	dma_sconfig.src_addr = phy_addr + rxdr_offset;
	dma_sconfig.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	dma_sconfig.src_maxburst = 1;
	dma_sconfig.direction = DMA_DEV_TO_MEM;
	ret = dmaengine_slave_config(dma->chan_rx, &dma_sconfig);
	अगर (ret < 0) अणु
		dev_err(dev, "can't configure rx channel\n");
		जाओ fail_rx;
	पूर्ण

	init_completion(&dma->dma_complete);

	dev_info(dev, "using %s (tx) and %s (rx) for DMA transfers\n",
		 dma_chan_name(dma->chan_tx), dma_chan_name(dma->chan_rx));

	वापस dma;

fail_rx:
	dma_release_channel(dma->chan_rx);
fail_tx:
	dma_release_channel(dma->chan_tx);
fail_al:
	devm_kमुक्त(dev, dma);

	वापस ERR_PTR(ret);
पूर्ण

व्योम sपंचांग32_i2c_dma_मुक्त(काष्ठा sपंचांग32_i2c_dma *dma)
अणु
	dma->dma_buf = 0;
	dma->dma_len = 0;

	dma_release_channel(dma->chan_tx);
	dma->chan_tx = शून्य;

	dma_release_channel(dma->chan_rx);
	dma->chan_rx = शून्य;

	dma->chan_using = शून्य;
पूर्ण

पूर्णांक sपंचांग32_i2c_prep_dma_xfer(काष्ठा device *dev, काष्ठा sपंचांग32_i2c_dma *dma,
			    bool rd_wr, u32 len, u8 *buf,
			    dma_async_tx_callback callback,
			    व्योम *dma_async_param)
अणु
	काष्ठा dma_async_tx_descriptor *txdesc;
	काष्ठा device *chan_dev;
	पूर्णांक ret;

	अगर (rd_wr) अणु
		dma->chan_using = dma->chan_rx;
		dma->dma_transfer_dir = DMA_DEV_TO_MEM;
		dma->dma_data_dir = DMA_FROM_DEVICE;
	पूर्ण अन्यथा अणु
		dma->chan_using = dma->chan_tx;
		dma->dma_transfer_dir = DMA_MEM_TO_DEV;
		dma->dma_data_dir = DMA_TO_DEVICE;
	पूर्ण

	dma->dma_len = len;
	chan_dev = dma->chan_using->device->dev;

	dma->dma_buf = dma_map_single(chan_dev, buf, dma->dma_len,
				      dma->dma_data_dir);
	अगर (dma_mapping_error(chan_dev, dma->dma_buf)) अणु
		dev_err(dev, "DMA mapping failed\n");
		वापस -EINVAL;
	पूर्ण

	txdesc = dmaengine_prep_slave_single(dma->chan_using, dma->dma_buf,
					     dma->dma_len,
					     dma->dma_transfer_dir,
					     DMA_PREP_INTERRUPT);
	अगर (!txdesc) अणु
		dev_err(dev, "Not able to get desc for DMA xfer\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	reinit_completion(&dma->dma_complete);

	txdesc->callback = callback;
	txdesc->callback_param = dma_async_param;
	ret = dma_submit_error(dmaengine_submit(txdesc));
	अगर (ret < 0) अणु
		dev_err(dev, "DMA submit failed\n");
		जाओ err;
	पूर्ण

	dma_async_issue_pending(dma->chan_using);

	वापस 0;

err:
	dma_unmap_single(chan_dev, dma->dma_buf, dma->dma_len,
			 dma->dma_data_dir);
	वापस ret;
पूर्ण
