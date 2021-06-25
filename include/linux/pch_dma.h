<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2010 Intel Corporation
 */

#अगर_अघोषित PCH_DMA_H
#घोषणा PCH_DMA_H

#समावेश <linux/dmaengine.h>

क्रमागत pch_dma_width अणु
	PCH_DMA_WIDTH_1_BYTE,
	PCH_DMA_WIDTH_2_BYTES,
	PCH_DMA_WIDTH_4_BYTES,
पूर्ण;

काष्ठा pch_dma_slave अणु
	काष्ठा device		*dma_dev;
	अचिन्हित पूर्णांक		chan_id;
	dma_addr_t		tx_reg;
	dma_addr_t		rx_reg;
	क्रमागत pch_dma_width	width;
पूर्ण;

#पूर्ण_अगर
