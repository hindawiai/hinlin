<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*******************************************************************************
  DWMAC DMA Header file.

  Copyright (C) 2007-2009  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#अगर_अघोषित __DWMAC_DMA_H__
#घोषणा __DWMAC_DMA_H__

/* DMA CRS Control and Status Register Mapping */
#घोषणा DMA_BUS_MODE		0x00001000	/* Bus Mode */
#घोषणा DMA_XMT_POLL_DEMAND	0x00001004	/* Transmit Poll Demand */
#घोषणा DMA_RCV_POLL_DEMAND	0x00001008	/* Received Poll Demand */
#घोषणा DMA_RCV_BASE_ADDR	0x0000100c	/* Receive List Base */
#घोषणा DMA_TX_BASE_ADDR	0x00001010	/* Transmit List Base */
#घोषणा DMA_STATUS		0x00001014	/* Status Register */
#घोषणा DMA_CONTROL		0x00001018	/* Ctrl (Operational Mode) */
#घोषणा DMA_INTR_ENA		0x0000101c	/* Interrupt Enable */
#घोषणा DMA_MISSED_FRAME_CTR	0x00001020	/* Missed Frame Counter */

/* SW Reset */
#घोषणा DMA_BUS_MODE_SFT_RESET	0x00000001	/* Software Reset */

/* Rx watchकरोg रेजिस्टर */
#घोषणा DMA_RX_WATCHDOG		0x00001024

/* AXI Master Bus Mode */
#घोषणा DMA_AXI_BUS_MODE	0x00001028

#घोषणा DMA_AXI_EN_LPI		BIT(31)
#घोषणा DMA_AXI_LPI_XIT_FRM	BIT(30)
#घोषणा DMA_AXI_WR_OSR_LMT	GENMASK(23, 20)
#घोषणा DMA_AXI_WR_OSR_LMT_SHIFT	20
#घोषणा DMA_AXI_WR_OSR_LMT_MASK	0xf
#घोषणा DMA_AXI_RD_OSR_LMT	GENMASK(19, 16)
#घोषणा DMA_AXI_RD_OSR_LMT_SHIFT	16
#घोषणा DMA_AXI_RD_OSR_LMT_MASK	0xf

#घोषणा DMA_AXI_OSR_MAX		0xf
#घोषणा DMA_AXI_MAX_OSR_LIMIT ((DMA_AXI_OSR_MAX << DMA_AXI_WR_OSR_LMT_SHIFT) | \
			       (DMA_AXI_OSR_MAX << DMA_AXI_RD_OSR_LMT_SHIFT))
#घोषणा	DMA_AXI_1KBBE		BIT(13)
#घोषणा DMA_AXI_AAL		BIT(12)
#घोषणा DMA_AXI_BLEN256		BIT(7)
#घोषणा DMA_AXI_BLEN128		BIT(6)
#घोषणा DMA_AXI_BLEN64		BIT(5)
#घोषणा DMA_AXI_BLEN32		BIT(4)
#घोषणा DMA_AXI_BLEN16		BIT(3)
#घोषणा DMA_AXI_BLEN8		BIT(2)
#घोषणा DMA_AXI_BLEN4		BIT(1)
#घोषणा DMA_BURST_LEN_DEFAULT	(DMA_AXI_BLEN256 | DMA_AXI_BLEN128 | \
				 DMA_AXI_BLEN64 | DMA_AXI_BLEN32 | \
				 DMA_AXI_BLEN16 | DMA_AXI_BLEN8 | \
				 DMA_AXI_BLEN4)

#घोषणा DMA_AXI_UNDEF		BIT(0)

#घोषणा DMA_AXI_BURST_LEN_MASK	0x000000FE

#घोषणा DMA_CUR_TX_BUF_ADDR	0x00001050	/* Current Host Tx Buffer */
#घोषणा DMA_CUR_RX_BUF_ADDR	0x00001054	/* Current Host Rx Buffer */
#घोषणा DMA_HW_FEATURE		0x00001058	/* HW Feature Register */

/* DMA Control रेजिस्टर defines */
#घोषणा DMA_CONTROL_ST		0x00002000	/* Start/Stop Transmission */
#घोषणा DMA_CONTROL_SR		0x00000002	/* Start/Stop Receive */

/* DMA Normal पूर्णांकerrupt */
#घोषणा DMA_INTR_ENA_NIE 0x00010000	/* Normal Summary */
#घोषणा DMA_INTR_ENA_TIE 0x00000001	/* Transmit Interrupt */
#घोषणा DMA_INTR_ENA_TUE 0x00000004	/* Transmit Buffer Unavailable */
#घोषणा DMA_INTR_ENA_RIE 0x00000040	/* Receive Interrupt */
#घोषणा DMA_INTR_ENA_ERE 0x00004000	/* Early Receive */

#घोषणा DMA_INTR_NORMAL	(DMA_INTR_ENA_NIE | DMA_INTR_ENA_RIE | \
			DMA_INTR_ENA_TIE)

/* DMA Abnormal पूर्णांकerrupt */
#घोषणा DMA_INTR_ENA_AIE 0x00008000	/* Abnormal Summary */
#घोषणा DMA_INTR_ENA_FBE 0x00002000	/* Fatal Bus Error */
#घोषणा DMA_INTR_ENA_ETE 0x00000400	/* Early Transmit */
#घोषणा DMA_INTR_ENA_RWE 0x00000200	/* Receive Watchकरोg */
#घोषणा DMA_INTR_ENA_RSE 0x00000100	/* Receive Stopped */
#घोषणा DMA_INTR_ENA_RUE 0x00000080	/* Receive Buffer Unavailable */
#घोषणा DMA_INTR_ENA_UNE 0x00000020	/* Tx Underflow */
#घोषणा DMA_INTR_ENA_OVE 0x00000010	/* Receive Overflow */
#घोषणा DMA_INTR_ENA_TJE 0x00000008	/* Transmit Jabber */
#घोषणा DMA_INTR_ENA_TSE 0x00000002	/* Transmit Stopped */

#घोषणा DMA_INTR_ABNORMAL	(DMA_INTR_ENA_AIE | DMA_INTR_ENA_FBE | \
				DMA_INTR_ENA_UNE)

/* DMA शेष पूर्णांकerrupt mask */
#घोषणा DMA_INTR_DEFAULT_MASK	(DMA_INTR_NORMAL | DMA_INTR_ABNORMAL)
#घोषणा DMA_INTR_DEFAULT_RX	(DMA_INTR_ENA_RIE)
#घोषणा DMA_INTR_DEFAULT_TX	(DMA_INTR_ENA_TIE)

/* DMA Status रेजिस्टर defines */
#घोषणा DMA_STATUS_GLPII	0x40000000	/* GMAC LPI पूर्णांकerrupt */
#घोषणा DMA_STATUS_GPI		0x10000000	/* PMT पूर्णांकerrupt */
#घोषणा DMA_STATUS_GMI		0x08000000	/* MMC पूर्णांकerrupt */
#घोषणा DMA_STATUS_GLI		0x04000000	/* GMAC Line पूर्णांकerface पूर्णांक */
#घोषणा DMA_STATUS_EB_MASK	0x00380000	/* Error Bits Mask */
#घोषणा DMA_STATUS_EB_TX_ABORT	0x00080000	/* Error Bits - TX Abort */
#घोषणा DMA_STATUS_EB_RX_ABORT	0x00100000	/* Error Bits - RX Abort */
#घोषणा DMA_STATUS_TS_MASK	0x00700000	/* Transmit Process State */
#घोषणा DMA_STATUS_TS_SHIFT	20
#घोषणा DMA_STATUS_RS_MASK	0x000e0000	/* Receive Process State */
#घोषणा DMA_STATUS_RS_SHIFT	17
#घोषणा DMA_STATUS_NIS	0x00010000	/* Normal Interrupt Summary */
#घोषणा DMA_STATUS_AIS	0x00008000	/* Abnormal Interrupt Summary */
#घोषणा DMA_STATUS_ERI	0x00004000	/* Early Receive Interrupt */
#घोषणा DMA_STATUS_FBI	0x00002000	/* Fatal Bus Error Interrupt */
#घोषणा DMA_STATUS_ETI	0x00000400	/* Early Transmit Interrupt */
#घोषणा DMA_STATUS_RWT	0x00000200	/* Receive Watchकरोg Timeout */
#घोषणा DMA_STATUS_RPS	0x00000100	/* Receive Process Stopped */
#घोषणा DMA_STATUS_RU	0x00000080	/* Receive Buffer Unavailable */
#घोषणा DMA_STATUS_RI	0x00000040	/* Receive Interrupt */
#घोषणा DMA_STATUS_UNF	0x00000020	/* Transmit Underflow */
#घोषणा DMA_STATUS_OVF	0x00000010	/* Receive Overflow */
#घोषणा DMA_STATUS_TJT	0x00000008	/* Transmit Jabber Timeout */
#घोषणा DMA_STATUS_TU	0x00000004	/* Transmit Buffer Unavailable */
#घोषणा DMA_STATUS_TPS	0x00000002	/* Transmit Process Stopped */
#घोषणा DMA_STATUS_TI	0x00000001	/* Transmit Interrupt */
#घोषणा DMA_CONTROL_FTF		0x00100000	/* Flush transmit FIFO */

#घोषणा DMA_STATUS_MSK_COMMON		(DMA_STATUS_NIS | \
					 DMA_STATUS_AIS | \
					 DMA_STATUS_FBI)

#घोषणा DMA_STATUS_MSK_RX		(DMA_STATUS_ERI | \
					 DMA_STATUS_RWT | \
					 DMA_STATUS_RPS | \
					 DMA_STATUS_RU | \
					 DMA_STATUS_RI | \
					 DMA_STATUS_OVF | \
					 DMA_STATUS_MSK_COMMON)

#घोषणा DMA_STATUS_MSK_TX		(DMA_STATUS_ETI | \
					 DMA_STATUS_UNF | \
					 DMA_STATUS_TJT | \
					 DMA_STATUS_TU | \
					 DMA_STATUS_TPS | \
					 DMA_STATUS_TI | \
					 DMA_STATUS_MSK_COMMON)

#घोषणा NUM_DWMAC100_DMA_REGS	9
#घोषणा NUM_DWMAC1000_DMA_REGS	23

व्योम dwmac_enable_dma_transmission(व्योम __iomem *ioaddr);
व्योम dwmac_enable_dma_irq(व्योम __iomem *ioaddr, u32 chan, bool rx, bool tx);
व्योम dwmac_disable_dma_irq(व्योम __iomem *ioaddr, u32 chan, bool rx, bool tx);
व्योम dwmac_dma_start_tx(व्योम __iomem *ioaddr, u32 chan);
व्योम dwmac_dma_stop_tx(व्योम __iomem *ioaddr, u32 chan);
व्योम dwmac_dma_start_rx(व्योम __iomem *ioaddr, u32 chan);
व्योम dwmac_dma_stop_rx(व्योम __iomem *ioaddr, u32 chan);
पूर्णांक dwmac_dma_पूर्णांकerrupt(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_extra_stats *x,
			u32 chan, u32 dir);
पूर्णांक dwmac_dma_reset(व्योम __iomem *ioaddr);

#पूर्ण_अगर /* __DWMAC_DMA_H__ */
