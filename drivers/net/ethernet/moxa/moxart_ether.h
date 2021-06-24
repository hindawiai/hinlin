<शैली गुरु>
/* MOXA ART Ethernet (RTL8201CP) driver.
 *
 * Copyright (C) 2013 Jonas Jensen
 *
 * Jonas Jensen <jonas.jensen@gmail.com>
 *
 * Based on code from
 * Moxa Technology Co., Ltd. <www.moxa.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित _MOXART_ETHERNET_H
#घोषणा _MOXART_ETHERNET_H

#घोषणा TX_REG_OFFSET_DESC0	0
#घोषणा TX_REG_OFFSET_DESC1	4
#घोषणा TX_REG_OFFSET_DESC2	8
#घोषणा TX_REG_DESC_SIZE	16

#घोषणा RX_REG_OFFSET_DESC0	0
#घोषणा RX_REG_OFFSET_DESC1	4
#घोषणा RX_REG_OFFSET_DESC2	8
#घोषणा RX_REG_DESC_SIZE	16

#घोषणा TX_DESC0_PKT_LATE_COL	0x1		/* पात, late collision */
#घोषणा TX_DESC0_RX_PKT_EXS_COL	0x2		/* पात, >16 collisions */
#घोषणा TX_DESC0_DMA_OWN	0x80000000	/* owned by controller */
#घोषणा TX_DESC1_BUF_SIZE_MASK	0x7ff
#घोषणा TX_DESC1_LTS		0x8000000	/* last TX packet */
#घोषणा TX_DESC1_FTS		0x10000000	/* first TX packet */
#घोषणा TX_DESC1_FIFO_COMPLETE	0x20000000
#घोषणा TX_DESC1_INTR_COMPLETE	0x40000000
#घोषणा TX_DESC1_END		0x80000000
#घोषणा TX_DESC2_ADDRESS_PHYS	0
#घोषणा TX_DESC2_ADDRESS_VIRT	4

#घोषणा RX_DESC0_FRAME_LEN	0
#घोषणा RX_DESC0_FRAME_LEN_MASK	0x7FF
#घोषणा RX_DESC0_MULTICAST	0x10000
#घोषणा RX_DESC0_BROADCAST	0x20000
#घोषणा RX_DESC0_ERR		0x40000
#घोषणा RX_DESC0_CRC_ERR	0x80000
#घोषणा RX_DESC0_FTL		0x100000
#घोषणा RX_DESC0_RUNT		0x200000	/* packet less than 64 bytes */
#घोषणा RX_DESC0_ODD_NB		0x400000	/* receive odd nibbles */
#घोषणा RX_DESC0_LRS		0x10000000	/* last receive segment */
#घोषणा RX_DESC0_FRS		0x20000000	/* first receive segment */
#घोषणा RX_DESC0_DMA_OWN	0x80000000
#घोषणा RX_DESC1_BUF_SIZE_MASK	0x7FF
#घोषणा RX_DESC1_END		0x80000000
#घोषणा RX_DESC2_ADDRESS_PHYS	0
#घोषणा RX_DESC2_ADDRESS_VIRT	4

#घोषणा TX_DESC_NUM		64
#घोषणा TX_DESC_NUM_MASK	(TX_DESC_NUM - 1)
#घोषणा TX_NEXT(N)		(((N) + 1) & (TX_DESC_NUM_MASK))
#घोषणा TX_BUF_SIZE		1600
#घोषणा TX_BUF_SIZE_MAX		(TX_DESC1_BUF_SIZE_MASK + 1)
#घोषणा TX_WAKE_THRESHOLD	16

#घोषणा RX_DESC_NUM		64
#घोषणा RX_DESC_NUM_MASK	(RX_DESC_NUM - 1)
#घोषणा RX_NEXT(N)		(((N) + 1) & (RX_DESC_NUM_MASK))
#घोषणा RX_BUF_SIZE		1600
#घोषणा RX_BUF_SIZE_MAX		(RX_DESC1_BUF_SIZE_MASK + 1)

#घोषणा REG_INTERRUPT_STATUS	0
#घोषणा REG_INTERRUPT_MASK	4
#घोषणा REG_MAC_MS_ADDRESS	8
#घोषणा REG_MAC_LS_ADDRESS	12
#घोषणा REG_MCAST_HASH_TABLE0	16
#घोषणा REG_MCAST_HASH_TABLE1	20
#घोषणा REG_TX_POLL_DEMAND	24
#घोषणा REG_RX_POLL_DEMAND	28
#घोषणा REG_TXR_BASE_ADDRESS	32
#घोषणा REG_RXR_BASE_ADDRESS	36
#घोषणा REG_INT_TIMER_CTRL	40
#घोषणा REG_APOLL_TIMER_CTRL	44
#घोषणा REG_DMA_BLEN_CTRL	48
#घोषणा REG_RESERVED1		52
#घोषणा REG_MAC_CTRL		136
#घोषणा REG_MAC_STATUS		140
#घोषणा REG_PHY_CTRL		144
#घोषणा REG_PHY_WRITE_DATA	148
#घोषणा REG_FLOW_CTRL		152
#घोषणा REG_BACK_PRESSURE	156
#घोषणा REG_RESERVED2		160
#घोषणा REG_TEST_SEED		196
#घोषणा REG_DMA_FIFO_STATE	200
#घोषणा REG_TEST_MODE		204
#घोषणा REG_RESERVED3		208
#घोषणा REG_TX_COL_COUNTER	212
#घोषणा REG_RPF_AEP_COUNTER	216
#घोषणा REG_XM_PG_COUNTER	220
#घोषणा REG_RUNT_TLC_COUNTER	224
#घोषणा REG_CRC_FTL_COUNTER	228
#घोषणा REG_RLC_RCC_COUNTER	232
#घोषणा REG_BROC_COUNTER	236
#घोषणा REG_MULCA_COUNTER	240
#घोषणा REG_RP_COUNTER		244
#घोषणा REG_XP_COUNTER		248

#घोषणा REG_PHY_CTRL_OFFSET	0x0
#घोषणा REG_PHY_STATUS		0x1
#घोषणा REG_PHY_ID1		0x2
#घोषणा REG_PHY_ID2		0x3
#घोषणा REG_PHY_ANA		0x4
#घोषणा REG_PHY_ANLPAR		0x5
#घोषणा REG_PHY_ANE		0x6
#घोषणा REG_PHY_ECTRL1		0x10
#घोषणा REG_PHY_QPDS		0x11
#घोषणा REG_PHY_10BOP		0x12
#घोषणा REG_PHY_ECTRL2		0x13
#घोषणा REG_PHY_FTMAC100_WRITE	0x8000000
#घोषणा REG_PHY_FTMAC100_READ	0x4000000

/* REG_INTERRUPT_STATUS */
#घोषणा RPKT_FINISH		BIT(0)	/* DMA data received */
#घोषणा NORXBUF			BIT(1)	/* receive buffer unavailable */
#घोषणा XPKT_FINISH		BIT(2)	/* DMA moved data to TX FIFO */
#घोषणा NOTXBUF			BIT(3)	/* transmit buffer unavailable */
#घोषणा XPKT_OK_INT_STS		BIT(4)	/* transmit to ethernet success */
#घोषणा XPKT_LOST_INT_STS	BIT(5)	/* transmit ethernet lost (collision) */
#घोषणा RPKT_SAV		BIT(6)	/* FIFO receive success */
#घोषणा RPKT_LOST_INT_STS	BIT(7)	/* FIFO full, receive failed */
#घोषणा AHB_ERR			BIT(8)	/* AHB error */
#घोषणा PHYSTS_CHG		BIT(9)	/* PHY link status change */

/* REG_INTERRUPT_MASK */
#घोषणा RPKT_FINISH_M		BIT(0)
#घोषणा NORXBUF_M		BIT(1)
#घोषणा XPKT_FINISH_M		BIT(2)
#घोषणा NOTXBUF_M		BIT(3)
#घोषणा XPKT_OK_M		BIT(4)
#घोषणा XPKT_LOST_M		BIT(5)
#घोषणा RPKT_SAV_M		BIT(6)
#घोषणा RPKT_LOST_M		BIT(7)
#घोषणा AHB_ERR_M		BIT(8)
#घोषणा PHYSTS_CHG_M		BIT(9)

/* REG_MAC_MS_ADDRESS */
#घोषणा MAC_MADR_MASK		0xffff	/* 2 MSB MAC address */

/* REG_INT_TIMER_CTRL */
#घोषणा TXINT_TIME_SEL		BIT(15)	/* TX cycle समय period */
#घोषणा TXINT_THR_MASK		0x7000
#घोषणा TXINT_CNT_MASK		0xf00
#घोषणा RXINT_TIME_SEL		BIT(7)	/* RX cycle समय period */
#घोषणा RXINT_THR_MASK		0x70
#घोषणा RXINT_CNT_MASK		0xF

/* REG_APOLL_TIMER_CTRL */
#घोषणा TXPOLL_TIME_SEL		BIT(12)	/* TX poll समय period */
#घोषणा TXPOLL_CNT_MASK		0xf00
#घोषणा TXPOLL_CNT_SHIFT_BIT	8
#घोषणा RXPOLL_TIME_SEL		BIT(4)	/* RX poll समय period */
#घोषणा RXPOLL_CNT_MASK		0xF
#घोषणा RXPOLL_CNT_SHIFT_BIT	0

/* REG_DMA_BLEN_CTRL */
#घोषणा RX_THR_EN		BIT(9)	/* RX FIFO threshold arbitration */
#घोषणा RXFIFO_HTHR_MASK	0x1c0
#घोषणा RXFIFO_LTHR_MASK	0x38
#घोषणा INCR16_EN		BIT(2)	/* AHB bus INCR16 burst command */
#घोषणा INCR8_EN		BIT(1)	/* AHB bus INCR8 burst command */
#घोषणा INCR4_EN		BIT(0)	/* AHB bus INCR4 burst command */

/* REG_MAC_CTRL */
#घोषणा RX_BROADPKT		BIT(17)	/* receive broadcast packets */
#घोषणा RX_MULTIPKT		BIT(16)	/* receive all multicast packets */
#घोषणा FULLDUP			BIT(15)	/* full duplex */
#घोषणा CRC_APD			BIT(14)	/* append CRC to transmitted packet */
#घोषणा RCV_ALL			BIT(12)	/* ignore incoming packet destination */
#घोषणा RX_FTL			BIT(11)	/* accept packets larger than 1518 B */
#घोषणा RX_RUNT			BIT(10)	/* accept packets smaller than 64 B */
#घोषणा HT_MULTI_EN		BIT(9)	/* accept on hash and mcast pass */
#घोषणा RCV_EN			BIT(8)	/* receiver enable */
#घोषणा ENRX_IN_HALFTX		BIT(6)	/* enable receive in half duplex mode */
#घोषणा XMT_EN			BIT(5)	/* transmit enable */
#घोषणा CRC_DIS			BIT(4)	/* disable CRC check when receiving */
#घोषणा LOOP_EN			BIT(3)	/* पूर्णांकernal loop-back */
#घोषणा SW_RST			BIT(2)	/* software reset, last 64 AHB घड़ीs */
#घोषणा RDMA_EN			BIT(1)	/* enable receive DMA chan */
#घोषणा XDMA_EN			BIT(0)	/* enable transmit DMA chan */

/* REG_MAC_STATUS */
#घोषणा COL_EXCEED		BIT(11)	/* more than 16 collisions */
#घोषणा LATE_COL		BIT(10)	/* transmit late collision detected */
#घोषणा XPKT_LOST		BIT(9)	/* transmit to ethernet lost */
#घोषणा XPKT_OK			BIT(8)	/* transmit to ethernet success */
#घोषणा RUNT_MAC_STS		BIT(7)	/* receive runt detected */
#घोषणा FTL_MAC_STS		BIT(6)	/* receive frame too दीर्घ detected */
#घोषणा CRC_ERR_MAC_STS		BIT(5)
#घोषणा RPKT_LOST		BIT(4)	/* RX FIFO full, receive failed */
#घोषणा RPKT_SAVE		BIT(3)	/* RX FIFO receive success */
#घोषणा COL			BIT(2)	/* collision, incoming packet dropped */
#घोषणा MCPU_BROADCAST		BIT(1)
#घोषणा MCPU_MULTICAST		BIT(0)

/* REG_PHY_CTRL */
#घोषणा MIIWR			BIT(27)	/* init ग_लिखो sequence (स्वतः cleared)*/
#घोषणा MIIRD			BIT(26)
#घोषणा REGAD_MASK		0x3e00000
#घोषणा PHYAD_MASK		0x1f0000
#घोषणा MIIRDATA_MASK		0xffff

/* REG_PHY_WRITE_DATA */
#घोषणा MIIWDATA_MASK		0xffff

/* REG_FLOW_CTRL */
#घोषणा PAUSE_TIME_MASK		0xffff0000
#घोषणा FC_HIGH_MASK		0xf000
#घोषणा FC_LOW_MASK		0xf00
#घोषणा RX_PAUSE		BIT(4)	/* receive छोड़ो frame */
#घोषणा TX_PAUSED		BIT(3)	/* transmit छोड़ो due to receive */
#घोषणा FCTHR_EN		BIT(2)	/* enable threshold mode. */
#घोषणा TX_PAUSE		BIT(1)	/* transmit छोड़ो frame */
#घोषणा FC_EN			BIT(0)	/* flow control mode enable */

/* REG_BACK_PRESSURE */
#घोषणा BACKP_LOW_MASK		0xf00
#घोषणा BACKP_JAM_LEN_MASK	0xf0
#घोषणा BACKP_MODE		BIT(1)	/* address mode */
#घोषणा BACKP_ENABLE		BIT(0)

/* REG_TEST_SEED */
#घोषणा TEST_SEED_MASK		0x3fff

/* REG_DMA_FIFO_STATE */
#घोषणा TX_DMA_REQUEST		BIT(31)
#घोषणा RX_DMA_REQUEST		BIT(30)
#घोषणा TX_DMA_GRANT		BIT(29)
#घोषणा RX_DMA_GRANT		BIT(28)
#घोषणा TX_FIFO_EMPTY		BIT(27)
#घोषणा RX_FIFO_EMPTY		BIT(26)
#घोषणा TX_DMA2_SM_MASK		0x7000
#घोषणा TX_DMA1_SM_MASK		0xf00
#घोषणा RX_DMA2_SM_MASK		0x70
#घोषणा RX_DMA1_SM_MASK		0xF

/* REG_TEST_MODE */
#घोषणा SINGLE_PKT		BIT(26)	/* single packet mode */
#घोषणा PTIMER_TEST		BIT(25)	/* स्वतःmatic polling समयr test mode */
#घोषणा ITIMER_TEST		BIT(24)	/* पूर्णांकerrupt समयr test mode */
#घोषणा TEST_SEED_SELECT	BIT(22)
#घोषणा SEED_SELECT		BIT(21)
#घोषणा TEST_MODE		BIT(20)
#घोषणा TEST_TIME_MASK		0xffc00
#घोषणा TEST_EXCEL_MASK		0x3e0

/* REG_TX_COL_COUNTER */
#घोषणा TX_MCOL_MASK		0xffff0000
#घोषणा TX_MCOL_SHIFT_BIT	16
#घोषणा TX_SCOL_MASK		0xffff
#घोषणा TX_SCOL_SHIFT_BIT	0

/* REG_RPF_AEP_COUNTER */
#घोषणा RPF_MASK		0xffff0000
#घोषणा RPF_SHIFT_BIT		16
#घोषणा AEP_MASK		0xffff
#घोषणा AEP_SHIFT_BIT		0

/* REG_XM_PG_COUNTER */
#घोषणा XM_MASK			0xffff0000
#घोषणा XM_SHIFT_BIT		16
#घोषणा PG_MASK			0xffff
#घोषणा PG_SHIFT_BIT		0

/* REG_RUNT_TLC_COUNTER */
#घोषणा RUNT_CNT_MASK		0xffff0000
#घोषणा RUNT_CNT_SHIFT_BIT	16
#घोषणा TLCC_MASK		0xffff
#घोषणा TLCC_SHIFT_BIT		0

/* REG_CRC_FTL_COUNTER */
#घोषणा CRCER_CNT_MASK		0xffff0000
#घोषणा CRCER_CNT_SHIFT_BIT	16
#घोषणा FTL_CNT_MASK		0xffff
#घोषणा FTL_CNT_SHIFT_BIT	0

/* REG_RLC_RCC_COUNTER */
#घोषणा RLC_MASK		0xffff0000
#घोषणा RLC_SHIFT_BIT		16
#घोषणा RCC_MASK		0xffff
#घोषणा RCC_SHIFT_BIT		0

/* REG_PHY_STATUS */
#घोषणा AN_COMPLETE		0x20
#घोषणा LINK_STATUS		0x4

काष्ठा moxart_mac_priv_t अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक reg_maccr;
	अचिन्हित पूर्णांक reg_imr;
	काष्ठा napi_काष्ठा napi;
	काष्ठा net_device *ndev;

	dma_addr_t rx_base;
	dma_addr_t rx_mapping[RX_DESC_NUM];
	व्योम *rx_desc_base;
	अचिन्हित अक्षर *rx_buf_base;
	अचिन्हित अक्षर *rx_buf[RX_DESC_NUM];
	अचिन्हित पूर्णांक rx_head;
	अचिन्हित पूर्णांक rx_buf_size;

	dma_addr_t tx_base;
	dma_addr_t tx_mapping[TX_DESC_NUM];
	व्योम *tx_desc_base;
	अचिन्हित अक्षर *tx_buf_base;
	अचिन्हित अक्षर *tx_buf[RX_DESC_NUM];
	अचिन्हित पूर्णांक tx_head;
	अचिन्हित पूर्णांक tx_buf_size;

	spinlock_t txlock;
	अचिन्हित पूर्णांक tx_len[TX_DESC_NUM];
	काष्ठा sk_buff *tx_skb[TX_DESC_NUM];
	अचिन्हित पूर्णांक tx_tail;
पूर्ण;

#अगर TX_BUF_SIZE >= TX_BUF_SIZE_MAX
#त्रुटि MOXA ART Ethernet device driver TX buffer is too large!
#पूर्ण_अगर
#अगर RX_BUF_SIZE >= RX_BUF_SIZE_MAX
#त्रुटि MOXA ART Ethernet device driver RX buffer is too large!
#पूर्ण_अगर

#पूर्ण_अगर
