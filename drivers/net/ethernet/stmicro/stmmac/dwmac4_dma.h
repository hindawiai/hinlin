<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * DWMAC4 DMA Header file.
 *
 * Copyright (C) 2007-2015  STMicroelectronics Ltd
 *
 * Author: Alexandre Torgue <alexandre.torgue@st.com>
 */

#अगर_अघोषित __DWMAC4_DMA_H__
#घोषणा __DWMAC4_DMA_H__

/* Define the max channel number used क्रम tx (also rx).
 * dwmac4 accepts up to 8 channels क्रम TX (and also 8 channels क्रम RX
 */
#घोषणा DMA_CHANNEL_NB_MAX		1

#घोषणा DMA_BUS_MODE			0x00001000
#घोषणा DMA_SYS_BUS_MODE		0x00001004
#घोषणा DMA_STATUS			0x00001008
#घोषणा DMA_DEBUG_STATUS_0		0x0000100c
#घोषणा DMA_DEBUG_STATUS_1		0x00001010
#घोषणा DMA_DEBUG_STATUS_2		0x00001014
#घोषणा DMA_AXI_BUS_MODE		0x00001028
#घोषणा DMA_TBS_CTRL			0x00001050

/* DMA Bus Mode biपंचांगap */
#घोषणा DMA_BUS_MODE_DCHE		BIT(19)
#घोषणा DMA_BUS_MODE_INTM_MASK		GENMASK(17, 16)
#घोषणा DMA_BUS_MODE_INTM_SHIFT		16
#घोषणा DMA_BUS_MODE_INTM_MODE1		0x1
#घोषणा DMA_BUS_MODE_SFT_RESET		BIT(0)

/* DMA SYS Bus Mode biपंचांगap */
#घोषणा DMA_BUS_MODE_SPH		BIT(24)
#घोषणा DMA_BUS_MODE_PBL		BIT(16)
#घोषणा DMA_BUS_MODE_PBL_SHIFT		16
#घोषणा DMA_BUS_MODE_RPBL_SHIFT		16
#घोषणा DMA_BUS_MODE_MB			BIT(14)
#घोषणा DMA_BUS_MODE_FB			BIT(0)

/* DMA Interrupt top status */
#घोषणा DMA_STATUS_MAC			BIT(17)
#घोषणा DMA_STATUS_MTL			BIT(16)
#घोषणा DMA_STATUS_CHAN7		BIT(7)
#घोषणा DMA_STATUS_CHAN6		BIT(6)
#घोषणा DMA_STATUS_CHAN5		BIT(5)
#घोषणा DMA_STATUS_CHAN4		BIT(4)
#घोषणा DMA_STATUS_CHAN3		BIT(3)
#घोषणा DMA_STATUS_CHAN2		BIT(2)
#घोषणा DMA_STATUS_CHAN1		BIT(1)
#घोषणा DMA_STATUS_CHAN0		BIT(0)

/* DMA debug status biपंचांगap */
#घोषणा DMA_DEBUG_STATUS_TS_MASK	0xf
#घोषणा DMA_DEBUG_STATUS_RS_MASK	0xf

/* DMA AXI biपंचांगap */
#घोषणा DMA_AXI_EN_LPI			BIT(31)
#घोषणा DMA_AXI_LPI_XIT_FRM		BIT(30)
#घोषणा DMA_AXI_WR_OSR_LMT		GENMASK(27, 24)
#घोषणा DMA_AXI_WR_OSR_LMT_SHIFT	24
#घोषणा DMA_AXI_RD_OSR_LMT		GENMASK(19, 16)
#घोषणा DMA_AXI_RD_OSR_LMT_SHIFT	16

#घोषणा DMA_AXI_OSR_MAX			0xf
#घोषणा DMA_AXI_MAX_OSR_LIMIT ((DMA_AXI_OSR_MAX << DMA_AXI_WR_OSR_LMT_SHIFT) | \
				(DMA_AXI_OSR_MAX << DMA_AXI_RD_OSR_LMT_SHIFT))

#घोषणा DMA_SYS_BUS_MB			BIT(14)
#घोषणा DMA_AXI_1KBBE			BIT(13)
#घोषणा DMA_SYS_BUS_AAL			BIT(12)
#घोषणा DMA_SYS_BUS_EAME		BIT(11)
#घोषणा DMA_AXI_BLEN256			BIT(7)
#घोषणा DMA_AXI_BLEN128			BIT(6)
#घोषणा DMA_AXI_BLEN64			BIT(5)
#घोषणा DMA_AXI_BLEN32			BIT(4)
#घोषणा DMA_AXI_BLEN16			BIT(3)
#घोषणा DMA_AXI_BLEN8			BIT(2)
#घोषणा DMA_AXI_BLEN4			BIT(1)
#घोषणा DMA_SYS_BUS_FB			BIT(0)

#घोषणा DMA_BURST_LEN_DEFAULT		(DMA_AXI_BLEN256 | DMA_AXI_BLEN128 | \
					DMA_AXI_BLEN64 | DMA_AXI_BLEN32 | \
					DMA_AXI_BLEN16 | DMA_AXI_BLEN8 | \
					DMA_AXI_BLEN4)

#घोषणा DMA_AXI_BURST_LEN_MASK		0x000000FE

/* DMA TBS Control */
#घोषणा DMA_TBS_FTOS			GENMASK(31, 8)
#घोषणा DMA_TBS_FTOV			BIT(0)
#घोषणा DMA_TBS_DEF_FTOS		(DMA_TBS_FTOS | DMA_TBS_FTOV)

/* Following DMA defines are chanels oriented */
#घोषणा DMA_CHAN_BASE_ADDR		0x00001100
#घोषणा DMA_CHAN_BASE_OFFSET		0x80
#घोषणा DMA_CHANX_BASE_ADDR(x)		(DMA_CHAN_BASE_ADDR + \
					(x * DMA_CHAN_BASE_OFFSET))
#घोषणा DMA_CHAN_REG_NUMBER		17

#घोषणा DMA_CHAN_CONTROL(x)		DMA_CHANX_BASE_ADDR(x)
#घोषणा DMA_CHAN_TX_CONTROL(x)		(DMA_CHANX_BASE_ADDR(x) + 0x4)
#घोषणा DMA_CHAN_RX_CONTROL(x)		(DMA_CHANX_BASE_ADDR(x) + 0x8)
#घोषणा DMA_CHAN_TX_BASE_ADDR_HI(x)	(DMA_CHANX_BASE_ADDR(x) + 0x10)
#घोषणा DMA_CHAN_TX_BASE_ADDR(x)	(DMA_CHANX_BASE_ADDR(x) + 0x14)
#घोषणा DMA_CHAN_RX_BASE_ADDR_HI(x)	(DMA_CHANX_BASE_ADDR(x) + 0x18)
#घोषणा DMA_CHAN_RX_BASE_ADDR(x)	(DMA_CHANX_BASE_ADDR(x) + 0x1c)
#घोषणा DMA_CHAN_TX_END_ADDR(x)		(DMA_CHANX_BASE_ADDR(x) + 0x20)
#घोषणा DMA_CHAN_RX_END_ADDR(x)		(DMA_CHANX_BASE_ADDR(x) + 0x28)
#घोषणा DMA_CHAN_TX_RING_LEN(x)		(DMA_CHANX_BASE_ADDR(x) + 0x2c)
#घोषणा DMA_CHAN_RX_RING_LEN(x)		(DMA_CHANX_BASE_ADDR(x) + 0x30)
#घोषणा DMA_CHAN_INTR_ENA(x)		(DMA_CHANX_BASE_ADDR(x) + 0x34)
#घोषणा DMA_CHAN_RX_WATCHDOG(x)		(DMA_CHANX_BASE_ADDR(x) + 0x38)
#घोषणा DMA_CHAN_SLOT_CTRL_STATUS(x)	(DMA_CHANX_BASE_ADDR(x) + 0x3c)
#घोषणा DMA_CHAN_CUR_TX_DESC(x)		(DMA_CHANX_BASE_ADDR(x) + 0x44)
#घोषणा DMA_CHAN_CUR_RX_DESC(x)		(DMA_CHANX_BASE_ADDR(x) + 0x4c)
#घोषणा DMA_CHAN_CUR_TX_BUF_ADDR(x)	(DMA_CHANX_BASE_ADDR(x) + 0x54)
#घोषणा DMA_CHAN_CUR_RX_BUF_ADDR(x)	(DMA_CHANX_BASE_ADDR(x) + 0x5c)
#घोषणा DMA_CHAN_STATUS(x)		(DMA_CHANX_BASE_ADDR(x) + 0x60)

/* DMA Control X */
#घोषणा DMA_CONTROL_SPH			BIT(24)
#घोषणा DMA_CONTROL_MSS_MASK		GENMASK(13, 0)

/* DMA Tx Channel X Control रेजिस्टर defines */
#घोषणा DMA_CONTROL_EDSE		BIT(28)
#घोषणा DMA_CONTROL_TSE			BIT(12)
#घोषणा DMA_CONTROL_OSP			BIT(4)
#घोषणा DMA_CONTROL_ST			BIT(0)

/* DMA Rx Channel X Control रेजिस्टर defines */
#घोषणा DMA_CONTROL_SR			BIT(0)
#घोषणा DMA_RBSZ_MASK			GENMASK(14, 1)
#घोषणा DMA_RBSZ_SHIFT			1

/* Interrupt status per channel */
#घोषणा DMA_CHAN_STATUS_REB		GENMASK(21, 19)
#घोषणा DMA_CHAN_STATUS_REB_SHIFT	19
#घोषणा DMA_CHAN_STATUS_TEB		GENMASK(18, 16)
#घोषणा DMA_CHAN_STATUS_TEB_SHIFT	16
#घोषणा DMA_CHAN_STATUS_NIS		BIT(15)
#घोषणा DMA_CHAN_STATUS_AIS		BIT(14)
#घोषणा DMA_CHAN_STATUS_CDE		BIT(13)
#घोषणा DMA_CHAN_STATUS_FBE		BIT(12)
#घोषणा DMA_CHAN_STATUS_ERI		BIT(11)
#घोषणा DMA_CHAN_STATUS_ETI		BIT(10)
#घोषणा DMA_CHAN_STATUS_RWT		BIT(9)
#घोषणा DMA_CHAN_STATUS_RPS		BIT(8)
#घोषणा DMA_CHAN_STATUS_RBU		BIT(7)
#घोषणा DMA_CHAN_STATUS_RI		BIT(6)
#घोषणा DMA_CHAN_STATUS_TBU		BIT(2)
#घोषणा DMA_CHAN_STATUS_TPS		BIT(1)
#घोषणा DMA_CHAN_STATUS_TI		BIT(0)

#घोषणा DMA_CHAN_STATUS_MSK_COMMON	(DMA_CHAN_STATUS_NIS | \
					 DMA_CHAN_STATUS_AIS | \
					 DMA_CHAN_STATUS_CDE | \
					 DMA_CHAN_STATUS_FBE)

#घोषणा DMA_CHAN_STATUS_MSK_RX		(DMA_CHAN_STATUS_REB | \
					 DMA_CHAN_STATUS_ERI | \
					 DMA_CHAN_STATUS_RWT | \
					 DMA_CHAN_STATUS_RPS | \
					 DMA_CHAN_STATUS_RBU | \
					 DMA_CHAN_STATUS_RI | \
					 DMA_CHAN_STATUS_MSK_COMMON)

#घोषणा DMA_CHAN_STATUS_MSK_TX		(DMA_CHAN_STATUS_ETI | \
					 DMA_CHAN_STATUS_TBU | \
					 DMA_CHAN_STATUS_TPS | \
					 DMA_CHAN_STATUS_TI | \
					 DMA_CHAN_STATUS_MSK_COMMON)

/* Interrupt enable bits per channel */
#घोषणा DMA_CHAN_INTR_ENA_NIE		BIT(16)
#घोषणा DMA_CHAN_INTR_ENA_AIE		BIT(15)
#घोषणा DMA_CHAN_INTR_ENA_NIE_4_10	BIT(15)
#घोषणा DMA_CHAN_INTR_ENA_AIE_4_10	BIT(14)
#घोषणा DMA_CHAN_INTR_ENA_CDE		BIT(13)
#घोषणा DMA_CHAN_INTR_ENA_FBE		BIT(12)
#घोषणा DMA_CHAN_INTR_ENA_ERE		BIT(11)
#घोषणा DMA_CHAN_INTR_ENA_ETE		BIT(10)
#घोषणा DMA_CHAN_INTR_ENA_RWE		BIT(9)
#घोषणा DMA_CHAN_INTR_ENA_RSE		BIT(8)
#घोषणा DMA_CHAN_INTR_ENA_RBUE		BIT(7)
#घोषणा DMA_CHAN_INTR_ENA_RIE		BIT(6)
#घोषणा DMA_CHAN_INTR_ENA_TBUE		BIT(2)
#घोषणा DMA_CHAN_INTR_ENA_TSE		BIT(1)
#घोषणा DMA_CHAN_INTR_ENA_TIE		BIT(0)

#घोषणा DMA_CHAN_INTR_NORMAL		(DMA_CHAN_INTR_ENA_NIE | \
					 DMA_CHAN_INTR_ENA_RIE | \
					 DMA_CHAN_INTR_ENA_TIE)

#घोषणा DMA_CHAN_INTR_ABNORMAL		(DMA_CHAN_INTR_ENA_AIE | \
					 DMA_CHAN_INTR_ENA_FBE)
/* DMA शेष पूर्णांकerrupt mask क्रम 4.00 */
#घोषणा DMA_CHAN_INTR_DEFAULT_MASK	(DMA_CHAN_INTR_NORMAL | \
					 DMA_CHAN_INTR_ABNORMAL)
#घोषणा DMA_CHAN_INTR_DEFAULT_RX	(DMA_CHAN_INTR_ENA_RIE)
#घोषणा DMA_CHAN_INTR_DEFAULT_TX	(DMA_CHAN_INTR_ENA_TIE)

#घोषणा DMA_CHAN_INTR_NORMAL_4_10	(DMA_CHAN_INTR_ENA_NIE_4_10 | \
					 DMA_CHAN_INTR_ENA_RIE | \
					 DMA_CHAN_INTR_ENA_TIE)

#घोषणा DMA_CHAN_INTR_ABNORMAL_4_10	(DMA_CHAN_INTR_ENA_AIE_4_10 | \
					 DMA_CHAN_INTR_ENA_FBE)
/* DMA शेष पूर्णांकerrupt mask क्रम 4.10a */
#घोषणा DMA_CHAN_INTR_DEFAULT_MASK_4_10	(DMA_CHAN_INTR_NORMAL_4_10 | \
					 DMA_CHAN_INTR_ABNORMAL_4_10)
#घोषणा DMA_CHAN_INTR_DEFAULT_RX_4_10	(DMA_CHAN_INTR_ENA_RIE)
#घोषणा DMA_CHAN_INTR_DEFAULT_TX_4_10	(DMA_CHAN_INTR_ENA_TIE)

/* channel 0 specअगरic fields */
#घोषणा DMA_CHAN0_DBG_STAT_TPS		GENMASK(15, 12)
#घोषणा DMA_CHAN0_DBG_STAT_TPS_SHIFT	12
#घोषणा DMA_CHAN0_DBG_STAT_RPS		GENMASK(11, 8)
#घोषणा DMA_CHAN0_DBG_STAT_RPS_SHIFT	8

पूर्णांक dwmac4_dma_reset(व्योम __iomem *ioaddr);
व्योम dwmac4_enable_dma_irq(व्योम __iomem *ioaddr, u32 chan, bool rx, bool tx);
व्योम dwmac410_enable_dma_irq(व्योम __iomem *ioaddr, u32 chan, bool rx, bool tx);
व्योम dwmac4_disable_dma_irq(व्योम __iomem *ioaddr, u32 chan, bool rx, bool tx);
व्योम dwmac410_disable_dma_irq(व्योम __iomem *ioaddr, u32 chan, bool rx, bool tx);
व्योम dwmac4_dma_start_tx(व्योम __iomem *ioaddr, u32 chan);
व्योम dwmac4_dma_stop_tx(व्योम __iomem *ioaddr, u32 chan);
व्योम dwmac4_dma_start_rx(व्योम __iomem *ioaddr, u32 chan);
व्योम dwmac4_dma_stop_rx(व्योम __iomem *ioaddr, u32 chan);
पूर्णांक dwmac4_dma_पूर्णांकerrupt(व्योम __iomem *ioaddr,
			 काष्ठा sपंचांगmac_extra_stats *x, u32 chan, u32 dir);
व्योम dwmac4_set_rx_ring_len(व्योम __iomem *ioaddr, u32 len, u32 chan);
व्योम dwmac4_set_tx_ring_len(व्योम __iomem *ioaddr, u32 len, u32 chan);
व्योम dwmac4_set_rx_tail_ptr(व्योम __iomem *ioaddr, u32 tail_ptr, u32 chan);
व्योम dwmac4_set_tx_tail_ptr(व्योम __iomem *ioaddr, u32 tail_ptr, u32 chan);

#पूर्ण_अगर /* __DWMAC4_DMA_H__ */
