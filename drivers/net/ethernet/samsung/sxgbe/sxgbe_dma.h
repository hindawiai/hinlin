<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* 10G controller driver क्रम Samsung SoCs
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Siva Reddy Kallam <siva.kallam@samsung.com>
 */
#अगर_अघोषित __SXGBE_DMA_H__
#घोषणा __SXGBE_DMA_H__

/* क्रमward declaration */
काष्ठा sxgbe_extra_stats;

#घोषणा SXGBE_DMA_BLENMAP_LSHIFT	1
#घोषणा SXGBE_DMA_TXPBL_LSHIFT		16
#घोषणा SXGBE_DMA_RXPBL_LSHIFT		16
#घोषणा DEFAULT_DMA_PBL			8

काष्ठा sxgbe_dma_ops अणु
	/* DMA core initialization */
	पूर्णांक (*init)(व्योम __iomem *ioaddr, पूर्णांक fix_burst, पूर्णांक burst_map);
	व्योम (*cha_init)(व्योम __iomem *ioaddr, पूर्णांक cha_num, पूर्णांक fix_burst,
			 पूर्णांक pbl, dma_addr_t dma_tx, dma_addr_t dma_rx,
			 पूर्णांक t_rzie, पूर्णांक r_rsize);
	व्योम (*enable_dma_transmission)(व्योम __iomem *ioaddr, पूर्णांक dma_cnum);
	व्योम (*enable_dma_irq)(व्योम __iomem *ioaddr, पूर्णांक dma_cnum);
	व्योम (*disable_dma_irq)(व्योम __iomem *ioaddr, पूर्णांक dma_cnum);
	व्योम (*start_tx)(व्योम __iomem *ioaddr, पूर्णांक tchannels);
	व्योम (*start_tx_queue)(व्योम __iomem *ioaddr, पूर्णांक dma_cnum);
	व्योम (*stop_tx)(व्योम __iomem *ioaddr, पूर्णांक tchannels);
	व्योम (*stop_tx_queue)(व्योम __iomem *ioaddr, पूर्णांक dma_cnum);
	व्योम (*start_rx)(व्योम __iomem *ioaddr, पूर्णांक rchannels);
	व्योम (*stop_rx)(व्योम __iomem *ioaddr, पूर्णांक rchannels);
	पूर्णांक (*tx_dma_पूर्णांक_status)(व्योम __iomem *ioaddr, पूर्णांक channel_no,
				 काष्ठा sxgbe_extra_stats *x);
	पूर्णांक (*rx_dma_पूर्णांक_status)(व्योम __iomem *ioaddr, पूर्णांक channel_no,
				 काष्ठा sxgbe_extra_stats *x);
	/* Program the HW RX Watchकरोg */
	व्योम (*rx_watchकरोg)(व्योम __iomem *ioaddr, u32 riwt);
	/* Enable TSO क्रम each DMA channel */
	व्योम (*enable_tso)(व्योम __iomem *ioaddr, u8 chan_num);
पूर्ण;

स्थिर काष्ठा sxgbe_dma_ops *sxgbe_get_dma_ops(व्योम);

#पूर्ण_अगर /* __SXGBE_CORE_H__ */
