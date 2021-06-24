<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * i2c-sपंचांग32.h
 *
 * Copyright (C) M'boumba Cedric Madianga 2017
 * Copyright (C) STMicroelectronics 2017
 * Author: M'boumba Cedric Madianga <cedric.madianga@gmail.com>
 *
 */

#अगर_अघोषित _I2C_STM32_H
#घोषणा _I2C_STM32_H

#समावेश <linux/dma-direction.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>

क्रमागत sपंचांग32_i2c_speed अणु
	STM32_I2C_SPEED_STANDARD, /* 100 kHz */
	STM32_I2C_SPEED_FAST, /* 400 kHz */
	STM32_I2C_SPEED_FAST_PLUS, /* 1 MHz */
	STM32_I2C_SPEED_END,
पूर्ण;

/**
 * काष्ठा sपंचांग32_i2c_dma - DMA specअगरic data
 * @chan_tx: dma channel क्रम TX transfer
 * @chan_rx: dma channel क्रम RX transfer
 * @chan_using: dma channel used क्रम the current transfer (TX or RX)
 * @dma_buf: dma buffer
 * @dma_len: dma buffer len
 * @dma_transfer_dir: dma transfer direction indicator
 * @dma_data_dir: dma transfer mode indicator
 * @dma_complete: dma transfer completion
 */
काष्ठा sपंचांग32_i2c_dma अणु
	काष्ठा dma_chan *chan_tx;
	काष्ठा dma_chan *chan_rx;
	काष्ठा dma_chan *chan_using;
	dma_addr_t dma_buf;
	अचिन्हित पूर्णांक dma_len;
	क्रमागत dma_transfer_direction dma_transfer_dir;
	क्रमागत dma_data_direction dma_data_dir;
	काष्ठा completion dma_complete;
पूर्ण;

काष्ठा sपंचांग32_i2c_dma *sपंचांग32_i2c_dma_request(काष्ठा device *dev,
					    dma_addr_t phy_addr,
					    u32 txdr_offset, u32 rxdr_offset);

व्योम sपंचांग32_i2c_dma_मुक्त(काष्ठा sपंचांग32_i2c_dma *dma);

पूर्णांक sपंचांग32_i2c_prep_dma_xfer(काष्ठा device *dev, काष्ठा sपंचांग32_i2c_dma *dma,
			    bool rd_wr, u32 len, u8 *buf,
			    dma_async_tx_callback callback,
			    व्योम *dma_async_param);

#पूर्ण_अगर /* _I2C_STM32_H */
