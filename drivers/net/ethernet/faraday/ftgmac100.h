<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Faraday FTGMAC100 Gigabit Ethernet
 *
 * (C) Copyright 2009-2011 Faraday Technology
 * Po-Yu Chuang <ratbert@faraday-tech.com>
 */

#अगर_अघोषित __FTGMAC100_H
#घोषणा __FTGMAC100_H

#घोषणा FTGMAC100_OFFSET_ISR		0x00
#घोषणा FTGMAC100_OFFSET_IER		0x04
#घोषणा FTGMAC100_OFFSET_MAC_MADR	0x08
#घोषणा FTGMAC100_OFFSET_MAC_LADR	0x0c
#घोषणा FTGMAC100_OFFSET_MAHT0		0x10
#घोषणा FTGMAC100_OFFSET_MAHT1		0x14
#घोषणा FTGMAC100_OFFSET_NPTXPD		0x18
#घोषणा FTGMAC100_OFFSET_RXPD		0x1c
#घोषणा FTGMAC100_OFFSET_NPTXR_BADR	0x20
#घोषणा FTGMAC100_OFFSET_RXR_BADR	0x24
#घोषणा FTGMAC100_OFFSET_HPTXPD		0x28
#घोषणा FTGMAC100_OFFSET_HPTXR_BADR	0x2c
#घोषणा FTGMAC100_OFFSET_ITC		0x30
#घोषणा FTGMAC100_OFFSET_APTC		0x34
#घोषणा FTGMAC100_OFFSET_DBLAC		0x38
#घोषणा FTGMAC100_OFFSET_DMAFIFOS	0x3c
#घोषणा FTGMAC100_OFFSET_REVR		0x40
#घोषणा FTGMAC100_OFFSET_FEAR		0x44
#घोषणा FTGMAC100_OFFSET_TPAFCR		0x48
#घोषणा FTGMAC100_OFFSET_RBSR		0x4c
#घोषणा FTGMAC100_OFFSET_MACCR		0x50
#घोषणा FTGMAC100_OFFSET_MACSR		0x54
#घोषणा FTGMAC100_OFFSET_TM		0x58
#घोषणा FTGMAC100_OFFSET_PHYCR		0x60
#घोषणा FTGMAC100_OFFSET_PHYDATA	0x64
#घोषणा FTGMAC100_OFFSET_FCR		0x68
#घोषणा FTGMAC100_OFFSET_BPR		0x6c
#घोषणा FTGMAC100_OFFSET_WOLCR		0x70
#घोषणा FTGMAC100_OFFSET_WOLSR		0x74
#घोषणा FTGMAC100_OFFSET_WFCRC		0x78
#घोषणा FTGMAC100_OFFSET_WFBM1		0x80
#घोषणा FTGMAC100_OFFSET_WFBM2		0x84
#घोषणा FTGMAC100_OFFSET_WFBM3		0x88
#घोषणा FTGMAC100_OFFSET_WFBM4		0x8c
#घोषणा FTGMAC100_OFFSET_NPTXR_PTR	0x90
#घोषणा FTGMAC100_OFFSET_HPTXR_PTR	0x94
#घोषणा FTGMAC100_OFFSET_RXR_PTR	0x98
#घोषणा FTGMAC100_OFFSET_TX		0xa0
#घोषणा FTGMAC100_OFFSET_TX_MCOL_SCOL	0xa4
#घोषणा FTGMAC100_OFFSET_TX_ECOL_FAIL	0xa8
#घोषणा FTGMAC100_OFFSET_TX_LCOL_UND	0xac
#घोषणा FTGMAC100_OFFSET_RX		0xb0
#घोषणा FTGMAC100_OFFSET_RX_BC		0xb4
#घोषणा FTGMAC100_OFFSET_RX_MC		0xb8
#घोषणा FTGMAC100_OFFSET_RX_PF_AEP	0xbc
#घोषणा FTGMAC100_OFFSET_RX_RUNT	0xc0
#घोषणा FTGMAC100_OFFSET_RX_CRCER_FTL	0xc4
#घोषणा FTGMAC100_OFFSET_RX_COL_LOST	0xc8

/*
 * Interrupt status रेजिस्टर & पूर्णांकerrupt enable रेजिस्टर
 */
#घोषणा FTGMAC100_INT_RPKT_BUF		(1 << 0)
#घोषणा FTGMAC100_INT_RPKT_FIFO		(1 << 1)
#घोषणा FTGMAC100_INT_NO_RXBUF		(1 << 2)
#घोषणा FTGMAC100_INT_RPKT_LOST		(1 << 3)
#घोषणा FTGMAC100_INT_XPKT_ETH		(1 << 4)
#घोषणा FTGMAC100_INT_XPKT_FIFO		(1 << 5)
#घोषणा FTGMAC100_INT_NO_NPTXBUF	(1 << 6)
#घोषणा FTGMAC100_INT_XPKT_LOST		(1 << 7)
#घोषणा FTGMAC100_INT_AHB_ERR		(1 << 8)
#घोषणा FTGMAC100_INT_PHYSTS_CHG	(1 << 9)
#घोषणा FTGMAC100_INT_NO_HPTXBUF	(1 << 10)

/* Interrupts we care about in NAPI mode */
#घोषणा FTGMAC100_INT_BAD  (FTGMAC100_INT_RPKT_LOST | \
			    FTGMAC100_INT_XPKT_LOST | \
			    FTGMAC100_INT_AHB_ERR   | \
			    FTGMAC100_INT_NO_RXBUF)

/* Normal RX/TX पूर्णांकerrupts, enabled when NAPI off */
#घोषणा FTGMAC100_INT_RXTX (FTGMAC100_INT_XPKT_ETH  | \
			    FTGMAC100_INT_RPKT_BUF)

/* All the पूर्णांकerrupts we care about */
#घोषणा FTGMAC100_INT_ALL (FTGMAC100_INT_RPKT_BUF  |  \
			   FTGMAC100_INT_BAD)

/*
 * Interrupt समयr control रेजिस्टर
 */
#घोषणा FTGMAC100_ITC_RXINT_CNT(x)	(((x) & 0xf) << 0)
#घोषणा FTGMAC100_ITC_RXINT_THR(x)	(((x) & 0x7) << 4)
#घोषणा FTGMAC100_ITC_RXINT_TIME_SEL	(1 << 7)
#घोषणा FTGMAC100_ITC_TXINT_CNT(x)	(((x) & 0xf) << 8)
#घोषणा FTGMAC100_ITC_TXINT_THR(x)	(((x) & 0x7) << 12)
#घोषणा FTGMAC100_ITC_TXINT_TIME_SEL	(1 << 15)

/*
 * Automatic polling समयr control रेजिस्टर
 */
#घोषणा FTGMAC100_APTC_RXPOLL_CNT(x)	(((x) & 0xf) << 0)
#घोषणा FTGMAC100_APTC_RXPOLL_TIME_SEL	(1 << 4)
#घोषणा FTGMAC100_APTC_TXPOLL_CNT(x)	(((x) & 0xf) << 8)
#घोषणा FTGMAC100_APTC_TXPOLL_TIME_SEL	(1 << 12)

/*
 * DMA burst length and arbitration control रेजिस्टर
 */
#घोषणा FTGMAC100_DBLAC_RXFIFO_LTHR(x)	(((x) & 0x7) << 0)
#घोषणा FTGMAC100_DBLAC_RXFIFO_HTHR(x)	(((x) & 0x7) << 3)
#घोषणा FTGMAC100_DBLAC_RX_THR_EN	(1 << 6)
#घोषणा FTGMAC100_DBLAC_RXBURST_SIZE(x)	(((x) & 0x3) << 8)
#घोषणा FTGMAC100_DBLAC_TXBURST_SIZE(x)	(((x) & 0x3) << 10)
#घोषणा FTGMAC100_DBLAC_RXDES_SIZE(x)	(((x) & 0xf) << 12)
#घोषणा FTGMAC100_DBLAC_TXDES_SIZE(x)	(((x) & 0xf) << 16)
#घोषणा FTGMAC100_DBLAC_IFG_CNT(x)	(((x) & 0x7) << 20)
#घोषणा FTGMAC100_DBLAC_IFG_INC		(1 << 23)

/*
 * DMA FIFO status रेजिस्टर
 */
#घोषणा FTGMAC100_DMAFIFOS_RXDMA1_SM(dmafअगरos)	((dmafअगरos) & 0xf)
#घोषणा FTGMAC100_DMAFIFOS_RXDMA2_SM(dmafअगरos)	(((dmafअगरos) >> 4) & 0xf)
#घोषणा FTGMAC100_DMAFIFOS_RXDMA3_SM(dmafअगरos)	(((dmafअगरos) >> 8) & 0x7)
#घोषणा FTGMAC100_DMAFIFOS_TXDMA1_SM(dmafअगरos)	(((dmafअगरos) >> 12) & 0xf)
#घोषणा FTGMAC100_DMAFIFOS_TXDMA2_SM(dmafअगरos)	(((dmafअगरos) >> 16) & 0x3)
#घोषणा FTGMAC100_DMAFIFOS_TXDMA3_SM(dmafअगरos)	(((dmafअगरos) >> 18) & 0xf)
#घोषणा FTGMAC100_DMAFIFOS_RXFIFO_EMPTY		(1 << 26)
#घोषणा FTGMAC100_DMAFIFOS_TXFIFO_EMPTY		(1 << 27)
#घोषणा FTGMAC100_DMAFIFOS_RXDMA_GRANT		(1 << 28)
#घोषणा FTGMAC100_DMAFIFOS_TXDMA_GRANT		(1 << 29)
#घोषणा FTGMAC100_DMAFIFOS_RXDMA_REQ		(1 << 30)
#घोषणा FTGMAC100_DMAFIFOS_TXDMA_REQ		(1 << 31)

/*
 * Feature Register
 */
#घोषणा FTGMAC100_REVR_NEW_MDIO_INTERFACE	BIT(31)

/*
 * Receive buffer size रेजिस्टर
 */
#घोषणा FTGMAC100_RBSR_SIZE(x)		((x) & 0x3fff)

/*
 * MAC control रेजिस्टर
 */
#घोषणा FTGMAC100_MACCR_TXDMA_EN	(1 << 0)
#घोषणा FTGMAC100_MACCR_RXDMA_EN	(1 << 1)
#घोषणा FTGMAC100_MACCR_TXMAC_EN	(1 << 2)
#घोषणा FTGMAC100_MACCR_RXMAC_EN	(1 << 3)
#घोषणा FTGMAC100_MACCR_RM_VLAN		(1 << 4)
#घोषणा FTGMAC100_MACCR_HPTXR_EN	(1 << 5)
#घोषणा FTGMAC100_MACCR_LOOP_EN		(1 << 6)
#घोषणा FTGMAC100_MACCR_ENRX_IN_HALFTX	(1 << 7)
#घोषणा FTGMAC100_MACCR_FULLDUP		(1 << 8)
#घोषणा FTGMAC100_MACCR_GIGA_MODE	(1 << 9)
#घोषणा FTGMAC100_MACCR_CRC_APD		(1 << 10)
#घोषणा FTGMAC100_MACCR_PHY_LINK_LEVEL	(1 << 11)
#घोषणा FTGMAC100_MACCR_RX_RUNT		(1 << 12)
#घोषणा FTGMAC100_MACCR_JUMBO_LF	(1 << 13)
#घोषणा FTGMAC100_MACCR_RX_ALL		(1 << 14)
#घोषणा FTGMAC100_MACCR_HT_MULTI_EN	(1 << 15)
#घोषणा FTGMAC100_MACCR_RX_MULTIPKT	(1 << 16)
#घोषणा FTGMAC100_MACCR_RX_BROADPKT	(1 << 17)
#घोषणा FTGMAC100_MACCR_DISCARD_CRCERR	(1 << 18)
#घोषणा FTGMAC100_MACCR_FAST_MODE	(1 << 19)
#घोषणा FTGMAC100_MACCR_SW_RST		(1 << 31)

/*
 * test mode control रेजिस्टर
 */
#घोषणा FTGMAC100_TM_RQ_TX_VALID_DIS (1 << 28)
#घोषणा FTGMAC100_TM_RQ_RR_IDLE_PREV (1 << 27)
#घोषणा FTGMAC100_TM_DEFAULT                                                   \
	(FTGMAC100_TM_RQ_TX_VALID_DIS | FTGMAC100_TM_RQ_RR_IDLE_PREV)

/*
 * PHY control रेजिस्टर
 */
#घोषणा FTGMAC100_PHYCR_MDC_CYCTHR_MASK	0x3f
#घोषणा FTGMAC100_PHYCR_MDC_CYCTHR(x)	((x) & 0x3f)
#घोषणा FTGMAC100_PHYCR_PHYAD(x)	(((x) & 0x1f) << 16)
#घोषणा FTGMAC100_PHYCR_REGAD(x)	(((x) & 0x1f) << 21)
#घोषणा FTGMAC100_PHYCR_MIIRD		(1 << 26)
#घोषणा FTGMAC100_PHYCR_MIIWR		(1 << 27)

/*
 * PHY data रेजिस्टर
 */
#घोषणा FTGMAC100_PHYDATA_MIIWDATA(x)		((x) & 0xffff)
#घोषणा FTGMAC100_PHYDATA_MIIRDATA(phydata)	(((phydata) >> 16) & 0xffff)

/*
 * Flow control रेजिस्टर
 */
#घोषणा FTGMAC100_FCR_FC_EN		(1 << 0)
#घोषणा FTGMAC100_FCR_FCTHR_EN		(1 << 2)
#घोषणा FTGMAC100_FCR_PAUSE_TIME(x)	(((x) & 0xffff) << 16)

/*
 * Transmit descriptor, aligned to 16 bytes
 */
काष्ठा ftgmac100_txdes अणु
	__le32	txdes0; /* Control & status bits */
	__le32	txdes1; /* Irq, checksum and vlan control */
	__le32	txdes2; /* Reserved */
	__le32	txdes3; /* DMA buffer address */
पूर्ण __attribute__ ((aligned(16)));

#घोषणा FTGMAC100_TXDES0_TXBUF_SIZE(x)	((x) & 0x3fff)
#घोषणा FTGMAC100_TXDES0_CRC_ERR	(1 << 19)
#घोषणा FTGMAC100_TXDES0_LTS		(1 << 28)
#घोषणा FTGMAC100_TXDES0_FTS		(1 << 29)
#घोषणा FTGMAC100_TXDES0_TXDMA_OWN	(1 << 31)

#घोषणा FTGMAC100_TXDES1_VLANTAG_CI(x)	((x) & 0xffff)
#घोषणा FTGMAC100_TXDES1_INS_VLANTAG	(1 << 16)
#घोषणा FTGMAC100_TXDES1_TCP_CHKSUM	(1 << 17)
#घोषणा FTGMAC100_TXDES1_UDP_CHKSUM	(1 << 18)
#घोषणा FTGMAC100_TXDES1_IP_CHKSUM	(1 << 19)
#घोषणा FTGMAC100_TXDES1_LLC		(1 << 22)
#घोषणा FTGMAC100_TXDES1_TX2FIC		(1 << 30)
#घोषणा FTGMAC100_TXDES1_TXIC		(1 << 31)

/*
 * Receive descriptor, aligned to 16 bytes
 */
काष्ठा ftgmac100_rxdes अणु
	__le32	rxdes0; /* Control & status bits */
	__le32	rxdes1;	/* Checksum and vlan status */
	__le32	rxdes2; /* length/type on AST2500 */
	__le32	rxdes3;	/* DMA buffer address */
पूर्ण __attribute__ ((aligned(16)));

#घोषणा FTGMAC100_RXDES0_VDBC		0x3fff
#घोषणा FTGMAC100_RXDES0_MULTICAST	(1 << 16)
#घोषणा FTGMAC100_RXDES0_BROADCAST	(1 << 17)
#घोषणा FTGMAC100_RXDES0_RX_ERR		(1 << 18)
#घोषणा FTGMAC100_RXDES0_CRC_ERR	(1 << 19)
#घोषणा FTGMAC100_RXDES0_FTL		(1 << 20)
#घोषणा FTGMAC100_RXDES0_RUNT		(1 << 21)
#घोषणा FTGMAC100_RXDES0_RX_ODD_NB	(1 << 22)
#घोषणा FTGMAC100_RXDES0_FIFO_FULL	(1 << 23)
#घोषणा FTGMAC100_RXDES0_PAUSE_OPCODE	(1 << 24)
#घोषणा FTGMAC100_RXDES0_PAUSE_FRAME	(1 << 25)
#घोषणा FTGMAC100_RXDES0_LRS		(1 << 28)
#घोषणा FTGMAC100_RXDES0_FRS		(1 << 29)
#घोषणा FTGMAC100_RXDES0_RXPKT_RDY	(1 << 31)

/* Errors we care about क्रम dropping packets */
#घोषणा RXDES0_ANY_ERROR		( \
	FTGMAC100_RXDES0_RX_ERR		| \
	FTGMAC100_RXDES0_CRC_ERR	| \
	FTGMAC100_RXDES0_FTL		| \
	FTGMAC100_RXDES0_RUNT		| \
	FTGMAC100_RXDES0_RX_ODD_NB)

#घोषणा FTGMAC100_RXDES1_VLANTAG_CI	0xffff
#घोषणा FTGMAC100_RXDES1_PROT_MASK	(0x3 << 20)
#घोषणा FTGMAC100_RXDES1_PROT_NONIP	(0x0 << 20)
#घोषणा FTGMAC100_RXDES1_PROT_IP	(0x1 << 20)
#घोषणा FTGMAC100_RXDES1_PROT_TCPIP	(0x2 << 20)
#घोषणा FTGMAC100_RXDES1_PROT_UDPIP	(0x3 << 20)
#घोषणा FTGMAC100_RXDES1_LLC		(1 << 22)
#घोषणा FTGMAC100_RXDES1_DF		(1 << 23)
#घोषणा FTGMAC100_RXDES1_VLANTAG_AVAIL	(1 << 24)
#घोषणा FTGMAC100_RXDES1_TCP_CHKSUM_ERR	(1 << 25)
#घोषणा FTGMAC100_RXDES1_UDP_CHKSUM_ERR	(1 << 26)
#घोषणा FTGMAC100_RXDES1_IP_CHKSUM_ERR	(1 << 27)

#पूर्ण_अगर /* __FTGMAC100_H */
